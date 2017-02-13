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

    connect(ui->widthSpn, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this]{emit penChanged(pen());});
    connect(ui->styleCmb, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this]{emit penChanged(pen());});
    connect(ui->redSlider, &QSlider::valueChanged, [this]{emit penChanged(pen());});
    connect(ui->greenSlider, &QSlider::valueChanged, [this]{emit penChanged(pen());});
    connect(ui->blueSlider, &QSlider::valueChanged, [this]{emit penChanged(pen());});

    connect(this, &LineDialog::penChanged, ui->example, &LineExample::setPen);
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
    result.setColor(QColor(ui->redSlider->value(),
                     ui->greenSlider->value(),
                     ui->blueSlider->value()));
    result.setWidth(ui->widthSpn->value());
    result.setStyle(static_cast<Qt::PenStyle>(ui->styleCmb->currentData().toInt()));

    return result;
}

