#pragma once
#include <QDialog>

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

private:
    QVector<NamedPenStyle> penStyles() const;
    void fillStylerCombo() const;

    QPen pen() const;

private:
    Ui::LineDialog *ui;
};
