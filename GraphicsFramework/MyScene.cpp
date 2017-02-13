#include "MyScene.h"

MyScene::MyScene(QObject *parent)
    : QGraphicsScene(parent)
    , current_{}
    , drawingInProgress_{}
    , startPoint_{}
{
    setSceneRect(0, 0, 500, 500);
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
