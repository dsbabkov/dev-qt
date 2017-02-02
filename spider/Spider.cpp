#include "Spider.h"
#include <QIcon>
#include <QPalette>
#include <QMouseEvent>
#include <QToolTip>
#include <QPainter>

std::unique_ptr<QPixmap> Spider::spiderCursor_;

Spider::Spider(QWidget *parent)
    : QWidget(parent, Qt::WindowStaysOnTopHint)
{
    setWindowTitle(tr("Spider"));
    setWindowIcon(QIcon(":/spider1.bmp"));

    QPalette palette;
    palette.setColor(QPalette::Active, QPalette::Window, Qt::white);
    const QPixmap pixmap(":/WomanAndDog.jpg");
    palette.setBrush(QPalette::Inactive, QPalette::Window, QBrush(pixmap));
    setMaximumSize(pixmap.size());
    resize(pixmap.size());

    setPalette(palette);
    setWindowOpacity(0.5);

    if (!spiderCursor_){
        spiderCursor_.reset(new QPixmap(":/super_spy.bmp"));
    }
}

Spider::~Spider()
{

}

void Spider::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()){
    case Qt::LeftButton:{
        isDrawing_ = true;
        update();
        setCursor(*spiderCursor_);
    }
    case Qt::RightButton:{
        if (event->modifiers() & Qt::CTRL){
            QToolTip::showText(event->globalPos(),
                               QStringLiteral("x = %1; y = %2")
                               .arg(event->x())
                               .arg(event->y()), this);
        }
    }
    }
}

void Spider::mouseMoveEvent(QMouseEvent *event)
{
    update();
    if (isDrawing_){
        if(rect().contains(event->pos())){
            setCursor(*spiderCursor_);
        }
        else{
            unsetCursor();
        }
    }
}

void Spider::mouseReleaseEvent(QMouseEvent *event)
{
    isDrawing_ = event->buttons() & Qt::LeftButton;

    if(!isDrawing_){
        update();
        unsetCursor();
    }
}

void Spider::paintEvent(QPaintEvent *event)
{
    if (isDrawing_){
        drawWeb();
    }
}

void Spider::drawWeb()
{
    const QPoint &pos = mapFromGlobal(QCursor::pos());

    QPainter painter(this);
    const QRect &rect = this->rect();
    const QPoint &center = rect.center();
    painter.drawLines(QVector<QPoint>{
                          pos, {},
                          pos, rect.topRight(),
                          pos, rect.bottomRight(),
                          pos, rect.bottomLeft(),
                          pos, {0, center.y()},
                          pos, {rect.width(), center.y()},
                          pos, {center.x(), 0},
                          pos, {center.x(), rect.height()}
                      });
}
