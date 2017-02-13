#include "LineDialog.h"
#include "ui_LineDialog.h"
#include <QPen>

LineDialog::LineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineDialog)
{
    ui->setupUi(this);
    fillStylerCombo();
    connect(this, &LineDialog::accepted, [this]{emit penAccepted(pen());});
}

LineDialog::~LineDialog()
{
    delete ui;
}

QVector<NamedPenStyle> LineDialog::penStyles() const
{
    return {
        {tr("Solid"), Qt::SolidLine},
        {tr("Dash"), Qt::DashLine},
        {tr("Dot"), Qt::DotLine},
        {tr("Dash dot"), Qt::DashDotLine},
        {tr("Dash dot dot"), Qt::DashDotDotLine}
    };
}

void LineDialog::fillStylerCombo() const
{
    ui->styleCmb->clear();
    for (const NamedPenStyle &style: penStyles()){
        ui->styleCmb->addItem(style.name, static_cast<int>(style.style));
    }
}

QPen LineDialog::pen() const
{
    QPen result;
    result.setColor({ui->redSlider->value(),
                     ui->greenSlider->value(),
                     ui->blueSlider->value()});
    result.setWidth(ui->widthSpn->value());
    result.setStyle(static_cast<Qt::PenStyle>(ui->styleCmb->currentData().toInt()));

    return result;
}

