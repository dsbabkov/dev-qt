#pragma once

#include <QGraphicsScene>

class QAbstractGraphicsShapeItem;

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MyScene(QObject *parent = {});

    void setColor(const QColor &color);
    QColor color() const;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QAbstractGraphicsShapeItem *current_;
    bool drawingInProgress_;
    QPointF startPoint_;
    QColor color_;
};
