#pragma once

#include <QGraphicsScene>

class QAbstractGraphicsShapeItem;

enum FugureType{
    Rectangle,
    Ellipce
};

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MyScene(QObject *parent = {});

    void setColor(const QColor &color);
    QColor color() const;

    void setFigureType(FugureType figureType);

signals:
    void penChanged(const QPen &) const;

public slots:
    void setPen(const QPen &pen);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QAbstractGraphicsShapeItem *current_;
    bool drawingInProgress_;
    QPointF startPoint_;
    QPen pen_;
    FugureType figureType_;
};
