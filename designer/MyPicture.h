#pragma once

#include <QWidget>
#include <QPixmap>

class MyPicture : public QWidget
{
    Q_OBJECT

public:
    explicit MyPicture(QWidget *parent = {});
    Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged)

double scale() const;

signals:
    void scaleChanged(double scale);

public slots:
    void setScale(int scalePercent);
    void setScale(double scale);

protected:
    virtual void paintEvent(QPaintEvent *) override;

private:
    QPixmap pixmap_;
    double scale_;

};

