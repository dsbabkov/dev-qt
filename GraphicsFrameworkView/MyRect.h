#pragma once

#include <QRectF>
#include <QPen>

class MyRect
{
public:
    MyRect();
    MyRect(const QRectF &rect, const QPen &pen);

    QRectF rect() const;
    void setRect(const QRectF &rect);

    QPen pen() const;
    void setPen(const QPen &pen);

private:
    QRectF rect_;
    QPen pen_;
};
