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
    if (pen_.color() != color){
        pen_.setColor(color);
        emit penChanged(pen_);
    }
}

QColor MyScene::color() const
{
    return pen_.color();
}

void MyScene::setPen(const QPen &pen)
{
    if (pen_ == pen){
        return;
    }

    pen_ = pen;
    emit penChanged(pen);
}

void MyScene::selectShape(const MyRect &rect)
{
    for (QGraphicsItem *item: selectedItems()){
        item->setSelected(false);
    }

    for (QGraphicsItem *item: items()){
        QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem *>(item);
        if (rectItem->rect() == rect.rect()){
            rectItem->setSelected(true);
            return;
        }
    }
}

void MyScene::changeShape(const MyRect &rect)
{
    for (QGraphicsItem *item: items()){
        QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem *>(item);
        if (rectItem->rect() == rect.rect()){
            rectItem->setPen(rect.pen());
            return;
        }
    }
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton){
        startPoint_ = event->scenePos();
        drawingInProgress_ = true;
        current_ = new QGraphicsRectItem({startPoint_, startPoint_});
        current_->setPen(pen_);
        current_->setFlags(QGraphicsItem::ItemIsSelectable);
        addItem(current_);
    }
    QGraphicsScene::mousePressEvent(event);
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (drawingInProgress_){
        const QRectF &newRect = QRectF(startPoint_, event->scenePos()).normalized();
        current_->setRect(newRect);
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton){
        drawingInProgress_ = false;
        emit shapeAdded({current_->rect(), pen_});
        current_ = {};
    }


    QGraphicsScene::mouseReleaseEvent(event);
}
