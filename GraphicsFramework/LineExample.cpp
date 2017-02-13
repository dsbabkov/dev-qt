#include "LineExample.h"
#include <QPainter>

LineExample::LineExample(QWidget *parent)
    : QFrame{parent}
    , pen_{}
{
}

void LineExample::setPen(const QPen &pen)
{
    pen_ = pen;
    update();
}

void LineExample::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(pen_);
    painter.drawLine({0, 0}, rect().bottomRight());

    QFrame::paintEvent(event);
}
