#pragma once

#include <QGraphicsScene>

class QAbstractGraphicsShapeItem;

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MyScene(QObject *parent = {});

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QAbstractGraphicsShapeItem *current_;
    bool drawingInProgress_;
    QPointF startPoint_;
};
