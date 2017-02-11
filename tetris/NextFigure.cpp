#include "NextFigure.h"
#include "Figure.h"
#include <QPainter>

NextFigure::NextFigure(QWidget *parent)
    : QWidget(parent)
    , figure_{}
{

}

void NextFigure::setFigure(Figure *figure)
{
    figure_ = figure;
    update();
}

void NextFigure::paintEvent(QPaintEvent */*event*/)
{
    if (!figure_){
        return;
    }

    QPainter painter(this);
    painter.translate((rect().width() - cellSize) / 2, (rect().height() - cellSize) / 2);
    figure_->draw(painter);
}
