#pragma once

#include <QGraphicsScene>
#include "MyRect.h"

class QGraphicsRectItem;

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MyScene(QObject *parent = {});

    void setColor(const QColor &color);
    QColor color() const;

signals:
    void penChanged(const QPen &) const;
    void shapeAdded(const MyRect &);

public slots:
    void setPen(const QPen &pen);
    void selectShape(const MyRect &rect);
    void changeShape(const MyRect &rect);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QGraphicsRectItem *current_;
    bool drawingInProgress_;
    QPointF startPoint_;
    QPen pen_;
};
