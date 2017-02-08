#include "Spider.h"
#include <QIcon>
#include <QPalette>
#include <QMouseEvent>
#include <QToolTip>
#include <QPainter>
#include <functional>

std::unique_ptr<QPixmap> Spider::spiderCursor_;

Spider::Spider(QWidget *parent)
    : QWidget(parent/*, Qt::WindowStaysOnTopHint*/)
{
    setWindowTitle(tr("Spider"));
    setWindowIcon(QIcon(":/spider1.bmp"));

    QPalette palette;
    palette.setColor(QPalette::Active, QPalette::Window, Qt::white);
    const QPixmap pixmap(":/WomanAndDog.jpg");
    palette.setBrush(QPalette::Inactive, QPalette::Window, QBrush(pixmap));
//    setFixedSize(pixmap.size());

    setPalette(palette);
    setWindowOpacity(0.5);

    if (!spiderCursor_){
        spiderCursor_.reset(new QPixmap(":/super_spy.bmp"));
    }
}

Spider::~Spider() = default;

void Spider::mousePressEvent(QMouseEvent *event)
{
    const std::map<Qt::MouseButton, std::function<void()>> methodMap = {
        {Qt::LeftButton, std::bind(&Spider::beginDrawingWeb, this)},
        {Qt::RightButton, [this, event]{if (event->modifiers() & Qt::CTRL){displayPositionTip(event->pos());}}}
    };

    try{
        methodMap.at(event->button())();
    }
    catch (const std::out_of_range &){}
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

void Spider::paintEvent(QPaintEvent *)
{
    if (isDrawing_){
        drawWeb();
    }
}

void Spider::resizeEvent(QResizeEvent *event)
{
    setWindowTitle(tr("Spider") + tr(": width=%1, height=%2")
                   .arg(event->size().width())
                   .arg(event->size().height()));
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

void Spider::beginDrawingWeb()
{
    isDrawing_ = true;
    update();
    setCursor(*spiderCursor_);
}

void Spider::displayPositionTip(const QPoint &localPos)
{
    QToolTip::showText(mapToGlobal(localPos),
                       QStringLiteral("x = %1; y = %2")
                       .arg(localPos.x())
                       .arg(localPos.y()), this);
}
