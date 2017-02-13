#include "LineDialog.h"
#include "ui_LineDialog.h"
#include <QPen>

LineDialog::LineDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LineDialog)
    , pen_{}
{
    ui->setupUi(this);
    fillStylerCombo();

    connect(this, &LineDialog::accepted, [this]{emit penAccepted(uiPen());});

    connect(ui->widthSpn, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this]{emit penChanged(uiPen());});
    connect(ui->styleCmb, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this]{emit penChanged(uiPen());});
    connect(ui->redSlider, &QSlider::valueChanged, [this]{emit penChanged(uiPen());});
    connect(ui->greenSlider, &QSlider::valueChanged, [this]{emit penChanged(uiPen());});
    connect(ui->blueSlider, &QSlider::valueChanged, [this]{emit penChanged(uiPen());});

    connect(this, &LineDialog::penChanged, ui->example, &LineExample::setPen);
    connect(this, &LineDialog::penAccepted, [this]{setPen(uiPen());});
    connect(this, &LineDialog::rejected, [this]{setPen(pen_);});
}

LineDialog::~LineDialog()
{
    delete ui;
}

void LineDialog::setPen(const QPen &pen)
{
    ui->widthSpn->setValue(pen.width());

    const QColor &color = pen.color();
    ui->redSlider->setValue(color.red());
    ui->greenSlider->setValue(color.green());
    ui->blueSlider->setValue(color.blue());

    int index = 0;
    for (const NamedPenStyle &style: penStyles()){
        if (style.style == pen.style()){
            break;
        }
        ++index;
    }
    ui->styleCmb->setCurrentIndex(index);

    pen_ = pen;
}

QVector<NamedPenStyle> LineDialog::penStyles()
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

QPen LineDialog::uiPen() const
{
    QPen result;
    result.setColor(QColor(ui->redSlider->value(),
                     ui->greenSlider->value(),
                     ui->blueSlider->value()));
    result.setWidth(ui->widthSpn->value());
    result.setStyle(static_cast<Qt::PenStyle>(ui->styleCmb->currentData().toInt()));

    return result;
}

