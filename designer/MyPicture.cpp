#include "MyPicture.h"
#include <QPainter>

MyPicture::MyPicture(QWidget *parent)
    : QWidget(parent)
    , pixmap_{":/MyImages/Images/WomenAndDog.jpg"}
    , scale_{1}
{
    connect(this, &MyPicture::scaleChanged, static_cast<void (QWidget::*)()>(&QWidget::update));
}

double MyPicture::scale() const
{
    return scale_;
}

void MyPicture::setScale(int scalePercent)
{
    setScale(scalePercent / 100.0);
}

void MyPicture::setScale(double scale)
{
    if (scale_ == scale)
        return;

    scale_ = scale;
    emit scaleChanged(scale);
}

void MyPicture::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
//    painter.drawPixmap(rect(), pixmap_.scaled(pixmap_.width() * scale_, pixmap_.height() * scale_));
    painter.drawPixmap(0, 0, pixmap_.scaled(pixmap_.width() * scale_, pixmap_.height() * scale_));
}

