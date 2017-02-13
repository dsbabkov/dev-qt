#include "MyRect.h"

MyRect::MyRect()
    : rect_{}
    , pen_{}
{
}

MyRect::MyRect(const QRectF &rect, const QPen &pen)
    : rect_{rect}
    , pen_{pen}
{
}

QRectF MyRect::rect() const
{
    return rect_;
}

void MyRect::setRect(const QRectF &rect)
{
    rect_ = rect;
}

QPen MyRect::pen() const
{
    return pen_;
}

void MyRect::setPen(const QPen &pen)
{
    pen_ = pen;
}

