#include "MyScene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

MyScene::MyScene(QObject *parent)
    : QGraphicsScene(parent)
    , current_{}
    , drawingInProgress_{}
    , startPoint_{}
    , pen_{}
{
    setSceneRect(0, 0, 500, 500);
}

void MyScene::setColor(const QColor &color)
{
    pen_.setColor(color);
}

QColor MyScene::color() const
{
    return pen_.color();
}

void MyScene::setPen(const QPen &pen)
{
    pen_ = pen;
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton){
        startPoint_ = event->scenePos();
        drawingInProgress_ = true;
        current_ = new QGraphicsRectItem({startPoint_, startPoint_});
        current_->setPen(pen_);
        current_->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        addItem(current_);
    }
    QGraphicsScene::mousePressEvent(event);
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (drawingInProgress_){
        static_cast<QGraphicsRectItem *> (current_)->setRect(QRectF(startPoint_, event->scenePos()).normalized());
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton){
        drawingInProgress_ = false;
        current_ = {};
    }
    QGraphicsScene::mouseReleaseEvent(event);
}
