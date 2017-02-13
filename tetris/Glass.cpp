#include "Glass.h"
#include <QPainter>
#include <QtDebug>
#include "Figure.h"
#include <functional>
#include <QKeyEvent>
#include <QMessageBox>

Glass::Glass(QWidget *parent)
    : QWidget(parent)
    , rowCount_{}
    , columnCount_{}
    , running_{false}
    , score_{}
    , field_{}
    , currentFigure_{}
    , nextFigure_{}
    , timerId_{}
{
}

Glass::~Glass() = default;

uint Glass::rowCount() const
{
    return rowCount_;
}

uint Glass::columnCount() const
{
    return columnCount_;
}

void Glass::setRowCount(uint rowCount)
{
    rowCount_ = rowCount;
    createEmptyField();
}

void Glass::setColumnCount(uint columnCount)
{
    columnCount_ = columnCount;
    createEmptyField();
}

void Glass::startNewGame()
{
    running_ = true;
    createEmptyField();
    currentFigure_.reset(new Figure());
    nextFigure_.reset(new Figure());
    emit nextFigureChanged(nextFigure_.get());
    setFocus();
    score_ = 0;
    emit scoreChanged(0);

    if (timerId_){
        killTimer(timerId_);
    }

    timerId_ = startTimer(timerInterval);

    qDebug() << "New game started";
}

void Glass::moveFigureDown()
{
    const int column = currentFigure_->column();
    const int obstacle = obstacleRow(column);

    if(currentFigure_->bottom() > obstacle){
        running_ = false;
        killTimer(timerId_);
        timerId_ = {};
        QMessageBox::information(this, tr("Game over"), tr("Time to do some work"));
    }

    if (currentFigure_->bottom() == obstacle){
        dropFigure();
    }
    else{
        currentFigure_->moveDown();
    }
    update();
}

void Glass::debugPause()
{
    qDebug() << "Debug paused";

    for (int i = 0; i < static_cast<int>(rowCount_); ++i){
        QString rowStr;
        for (int j = 0; j < static_cast<int>(columnCount_); ++j){
            const QColor &color = field_.at(i).at(j);
            rowStr += color.name() + " ";
        }
        qDebug() << rowStr;
    }

    removeLines();
}

void Glass::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    for (uint row = 0; row < rowCount_; ++row){
        for (uint col = 0; col < columnCount_; ++col){
            const QRect cell({static_cast<int>(col) * cellSize,
                              static_cast<int>(row) * cellSize},
                             cellRect);

            painter.fillRect(cell, field_.at(row).at(col));
            painter.drawRect(cell);
        }
    }
    if (currentFigure_){
        currentFigure_->draw(painter);
    }
}

void Glass::keyPressEvent(QKeyEvent *event)
{
    if (running_){
        static const std::map<Qt::Key, std::function<void()>> keyMap = {
            {Qt::Key_Left, std::bind(&Glass::moveFigureLeft, this)},
            {Qt::Key_Right, std::bind(&Glass::moveFigureRight, this)},
            {Qt::Key_Down, [this]{currentFigure_->rotateColorsDown();}},
            {Qt::Key_Up, [this]{currentFigure_->rotateColorsUp();}},
            {Qt::Key_Space, std::bind(&Glass::dropFigure, this)}
        };

        try {
            keyMap.at(static_cast<Qt::Key>(event->key()))();
            update();
            return;
        }
        catch (const std::out_of_range &){}
    }

    QWidget::keyPressEvent(event);
}

void Glass::timerEvent(QTimerEvent *)
{
    if (running_){
        moveFigureDown();
    }
}

void Glass::createEmptyField()
{
    field_.fill(Row(columnCount_, emptyCellColor), rowCount_);
}

void Glass::moveFigureLeft() const
{
    if (canMoveHorizontal(-1)){
        currentFigure_->moveLeft();
    }
}

void Glass::moveFigureRight() const
{
    if (canMoveHorizontal(1)){
        currentFigure_->moveRight();
    }
}

void Glass::rotateFigureColorsUp() const
{
    currentFigure_->rotateColorsUp();
}

void Glass::rotateFigureColorsDown() const
{
    currentFigure_->rotateColorsDown();
}

void Glass::dropFigure()
{
    const int storageCol = currentFigure_->column();
    int storageRow = obstacleRow(storageCol) - 1;
    for (int i = currentFigure_->length - 1; i >= 0; --i, --storageRow){
        field_[storageRow][storageCol] = currentFigure_->color(i);
    }

    qDebug() << field_[19][0];

    currentFigure_ = std::move(nextFigure_);
    nextFigure_.reset(new Figure());
    emit nextFigureChanged(nextFigure_.get());
    removeLines();
}

QVector<QPoint> Glass::findLineToRemove() const
{
    //columns
    for (int j = 0; j < static_cast<int>(columnCount_); ++j){
        QColor lastColor = field_.first().at(j);
        int lastColorRow = 0;
        for (int i = 1; i < static_cast<int>(rowCount_); ++i){
            const QColor &cellColor = field_.at(i).at(j);
            if (cellColor == lastColor){
                continue;
            }

            if (i - lastColorRow >= 3 && lastColor != emptyCellColor){
                QVector<QPoint> result;
                for (int k = lastColorRow; k < i; ++k){
                    result.append({k, j});
                }
                return result;
            }
            lastColor = cellColor;
            lastColorRow = i;
        }
        if (rowCount_ - lastColorRow >= 3 && lastColor != emptyCellColor){
            QVector<QPoint> result;
            for (int k = lastColorRow; k < static_cast<int>(rowCount_); ++k){
                result.append({k, j});
            }
            return result;
        }
    }

    //rows
    for (int i = 0; i < static_cast<int>(rowCount_); ++i){
        QColor lastColor = field_.at(i).first();
        int lastColorColumn = 0;
        for (int j = 1; j < static_cast<int>(columnCount_); ++j){
            const QColor &cellColor = field_.at(i).at(j);
            if (cellColor == lastColor){
                continue;
            }

            if (j - lastColorColumn >= 3 && lastColor != emptyCellColor){
                QVector<QPoint> result;
                for (int k = lastColorColumn; k < j; ++k){
                    result.append({i, k});
                }
                return result;
            }
            lastColor = cellColor;
            lastColorColumn = j;
        }
        if (columnCount_ - lastColorColumn >= 3 && lastColor != emptyCellColor){
            QVector<QPoint> result;
            for (int k = lastColorColumn; k < static_cast<int>(columnCount_); ++k){
                result.append({i, k});
            }
            return result;
        }
    }

    return {};
}

void Glass::removeLines()
{
    while (true){
        const QVector<QPoint> &removeCells = findLineToRemove();
        for (const QPoint &cell: removeCells){
            field_[cell.x()][cell.y()] = emptyCellColor;
        }

        if (removeCells.isEmpty()){
            break;
        }
        else{
            score_ += removeCells.count();
            emit scoreChanged(score_);
        }
        for (const QPoint &cell: removeCells){
            field_[cell.x()][cell.y()] = emptyCellColor;
        }
        squeezeField();
    }
}

void Glass::squeezeField()
{
    for (int j = 0; j < static_cast<int>(columnCount_); ++j){
        for (int i = static_cast<int>(rowCount_ - 1); i > 0; --i){
            QColor &cell = field_[i][j];
            if (cell == emptyCellColor){
                QColor *nextCell = {};
                for (int k = i - 1; k >= 0; --k){
                    QColor &cell2 = field_[k][j];
                    if (cell2 != emptyCellColor){
                        nextCell = &cell2;
                        break;
                    }
                }
                if (nextCell){
                    std::swap(cell, *nextCell) ;
                }
            }
        }
    }
}

int Glass::obstacleRow(int column) const
{
    int result = 0;
    for (; result < static_cast<int>(rowCount_) && field_.at(result).at(column) == emptyCellColor; ++result);
    return result;
}

bool Glass::canMoveHorizontal(int steps) const
{
    const int destColumn = currentFigure_->column() + steps;
    if (0 <= destColumn && destColumn < static_cast<int>(columnCount_)){
        for (int i = currentFigure_->top(); i < currentFigure_->bottom(); ++i){
            if (field_.at(i).at(destColumn) != emptyCellColor){
                return false;
            }
        }
        return true;
    }
    return false;
}

