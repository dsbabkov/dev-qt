#pragma once

#include "Global.h"
#include <QColor>
#include <QPoint>
#include <deque>

class QPainter;

class Figure
{
public:
    static constexpr int length = 3;

public:
    Figure();

    int bottom() const;
    int top() const;
    int column() const;

    void moveLeft();
    void moveRight();
    void setColumn(int column);
    void moveDown();

    void rotateColorsUp();
    void rotateColorsDown();

    void draw(QPainter &painter);
    QColor color(int i) const;

private:
    void setRandomColors();

private:
    QPoint position_;
    std::deque<QColor> colors_;
};
