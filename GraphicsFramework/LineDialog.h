#pragma once
#include <QDialog>
#include <QPen>

namespace Ui {
class LineDialog;
}

struct NamedPenStyle{
    QString name;
    Qt::PenStyle style;
};

class LineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LineDialog(QWidget *parent = {});
    ~LineDialog();

signals:
    void penChanged(const QPen &) const;
    void penAccepted(const QPen &) const;

public slots:
    void setPen(const QPen &uiPen);

private:
    QVector<NamedPenStyle> penStyles() const;
    void fillStylerCombo() const;

    QPen uiPen() const;

private:
    Ui::LineDialog *ui;
    QPen pen_;
};
