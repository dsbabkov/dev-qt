#include "Figure.h"
#include <random>
#include <QPainter>

Figure::Figure()
    : position_{}
    , colors_{}
{
    setRandomColors();
}

int Figure::bottom() const
{
    return position_.y() + length;
}

int Figure::top() const
{
    return position_.y();
}

int Figure::column() const
{
    return position_.x();
}

void Figure::moveLeft()
{
    --position_.rx();
}

void Figure::moveRight()
{
    ++position_.rx();
}

void Figure::setColumn(int column)
{
    position_.setX(column);
}

void Figure::moveDown()
{
    ++position_.ry();
}

void Figure::rotateColorsUp()
{
    const QColor frontColor = colors_.front();
    colors_.pop_front();
    colors_.push_back(frontColor);
}

void Figure::rotateColorsDown()
{
    const QColor backColor = colors_.back();
    colors_.pop_back();
    colors_.push_front(backColor);
}

void Figure::draw(QPainter &painter)
{
    const int figureTopPos = top() * cellSize;
    const int figureLeftPos = column() * cellSize;

    for (int i = 0; i < length; ++i){
        const QRect currentCell({figureLeftPos, figureTopPos + cellSize * i}, cellRect);
        painter.fillRect(currentCell, colors_[i]);
        painter.drawRect(currentCell);
    }
}

QColor Figure::color(int i) const
{
    Q_ASSERT(i >= 0 && i < length);
    return colors_[i];
}

void Figure::setRandomColors()
{
    constexpr Qt::GlobalColor availableColors[] = {
        Qt::red,
        Qt::green,
        Qt::blue,
        Qt::yellow,
        Qt::black
    };

    constexpr size_t colorCount = sizeof(availableColors) / sizeof(*availableColors);

    colors_.clear();
    for (int i = 0; i < length; ++i){
        colors_.push_back(availableColors[rand() % colorCount]);
    }
}

