#pragma once

#include <QFrame>
#include <QPen>

class LineExample : public QFrame
{
    Q_OBJECT
public:
    explicit LineExample(QWidget *parent = {});

public slots:
    void setPen(const QPen &pen);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QPen pen_;
};
