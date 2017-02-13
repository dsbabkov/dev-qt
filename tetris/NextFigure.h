#pragma once

#include <QWidget>
class Figure;

class NextFigure : public QWidget
{
    Q_OBJECT
public:
    explicit NextFigure(QWidget *parent = {});

public slots:
    void setFigure(Figure *);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    Figure *figure_;
};
