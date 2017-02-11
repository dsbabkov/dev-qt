#pragma once

#include <QWidget>
#include <QColor>
#include <QSize>
#include <memory>
#include "Global.h"

class Figure;

class Glass : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(uint rowCount READ rowCount WRITE setRowCount)
    Q_PROPERTY(uint columnCount READ columnCount WRITE setColumnCount)

    using Row = QVector<QColor>;
    using Field = QVector<Row>;

public:
    explicit Glass(QWidget *parent = {});
    ~Glass();

    uint rowCount() const;
    uint columnCount() const;

public slots:
    void setRowCount(uint rowCount);
    void setColumnCount(uint columnCount);
    void startNewGame();
    void moveFigureDown();

protected:
    virtual void paintEvent(QPaintEvent *) override;
    virtual void keyPressEvent(QKeyEvent *) override;
    virtual void timerEvent(QTimerEvent *) override;

private:
    void createEmptyField();

    void moveFigureLeft() const;
    void moveFigureRight() const;
    void rotateFigureColorsUp() const;
    void rotateFigureColorsDown() const;
    void dropFigure();

    QVector<QPoint> findLineToRemove() const;
    void removeLines();
    void squeezeField();

    int obstacleRow(int column) const;
    bool canMoveHorizontal(int steps) const;

private:
    static constexpr int timerInterval = 200;

    uint rowCount_;
    uint columnCount_;

    bool running_;
    uint score_;
    Field field_;

    std::unique_ptr<Figure> currentFigure_;
    std::unique_ptr<Figure> nextFigure_;
    int timerId_;
};
