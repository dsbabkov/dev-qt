#pragma once

#include <QWidget>
#include <memory>

class Spider : public QWidget
{
    Q_OBJECT

public:
    Spider(QWidget *parent = {});
    ~Spider();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void drawWeb();

private:
    bool isDrawing_ = false;
    static std::unique_ptr<QPixmap> spiderCursor_;
};
