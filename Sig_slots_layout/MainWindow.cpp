#include "MainWindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QSlider>
#include <QLabel>
#include <QIntValidator>
#include <QGridLayout>
#include <QStackedLayout>
#include <QComboBox>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , mainLayout_{new QHBoxLayout(this)}
    , hLayout_{new QHBoxLayout()}
    , vLayout_{new QVBoxLayout()}
    , gridLayout_{new QGridLayout()}
    , stackLayoutWraper_{new QVBoxLayout()}
    , combo{new QComboBox(this)}
    , edit_{new QLineEdit(this)}
    , spin_{new QSpinBox(this)}
    , slider_{new QSlider(Qt::Horizontal, this)}
    , label_{new QLabel(tr("Not set"), this)}
{
    setupHLayout();
    setupVLayout();
    setupGridLayout();
    setupStackLayout();

    setupWidgetsSizePolicy();
    mainLayout_->addLayout(hLayout_);
    addVerticalHorisontalBtns();
    addExitBtn();
    setupEdit();
    setupSpin();
    setupSlider();
    setupLabel();
    mainLayout_->addItem(new QSpacerItem(20, 1, QSizePolicy::Preferred, QSizePolicy::Maximum));
}

MainWindow::~MainWindow()
{
    dumpObjectTree();
}

void MainWindow::setupHLayout() const
{
    setupLayout(hLayout_); // нельзя передавать std::unique?
}

void MainWindow::setupVLayout() const
{
    setupLayout(vLayout_);
}

void MainWindow::setupGridLayout() const
{
    gridLayout_->addWidget(edit_, 0, 0);
    gridLayout_->addWidget(slider_, 1, 0);
    gridLayout_->addWidget(spin_, 0, 1);
    gridLayout_->addWidget(label_, 1, 1);
}

void MainWindow::setupStackLayout()
{
    QStackedLayout *layout = new QStackedLayout(stackLayoutWraper_);
    setupLayout(layout);
    layout->setStackingMode(QStackedLayout::StackAll);

    combo->hide();
    for (int i = 0; i < layout->count(); ++i){
        combo->addItem(QString::number(i + 1));
    }
    connect(combo, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            layout, &QStackedLayout::setCurrentIndex);


    stackLayoutWraper_->addWidget(combo);
    stackLayoutWraper_->addLayout(layout);
}

void MainWindow::setupWidgetsSizePolicy() const
{
    for (QWidget *widget: QList<QWidget *>{edit_, spin_, label_, slider_}){
        widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    }
}

void MainWindow::setupLayout(QLayout *layout) const
{
    layout->addWidget(edit_);
    layout->addWidget(spin_);
    layout->addWidget(slider_);
    layout->addWidget(label_);
}

void MainWindow::addVerticalHorisontalBtns()
{
    QPushButton *verticalBtn = new QPushButton(tr("Vertical"), this);
    QPushButton *horizontalBtn = new QPushButton(tr("Horizontal"), this);
    QPushButton *gridBtn = new QPushButton(tr("Grid"), this);
    QPushButton *stackBtn = new QPushButton(tr("Stack"), this);

    auto replaceLayout = [this](QLayout *layout){
        mainLayout_->removeItem(mainLayout_->itemAt(0));
        mainLayout_->insertItem(0, layout);

        bool isStacked = layout == stackLayoutWraper_;
        for (QWidget *widget: QList<QWidget*>{spin_, edit_, slider_, label_}){
            widget->setVisible(!isStacked );
        }
        combo->setVisible(isStacked);
        QStackedLayout* stackLayout = static_cast<QStackedLayout*>(stackLayoutWraper_->itemAt(0));
        stackLayout->currentWidget()->show();
        stackLayout->setStackingMode(isStacked ? QStackedLayout::StackOne : QStackedLayout::StackAll);
    };

    connect(verticalBtn, &QPushButton::clicked, [replaceLayout, this]{replaceLayout(vLayout_);});
    connect(horizontalBtn, &QPushButton::clicked, [replaceLayout, this]{replaceLayout(hLayout_);});
    connect(gridBtn, &QPushButton::clicked, [replaceLayout, this]{replaceLayout(gridLayout_);});
    connect(stackBtn, &QPushButton::clicked, [replaceLayout, this]{replaceLayout(stackLayoutWraper_);});

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(verticalBtn);
    layout->addWidget(horizontalBtn);
    layout->addWidget(gridBtn);
    layout->addWidget(stackBtn);
    mainLayout_->addLayout(layout);
}

void MainWindow::addExitBtn()
{
    QPushButton *exitBtn = new QPushButton(tr("Exit"), this);
    connect(exitBtn, &QPushButton::clicked, this, &QWidget::close);
    mainLayout_->addWidget(exitBtn);
}

void MainWindow::setupSpin()
{
    spin_->setMaximum(50);

    connect(edit_, &QLineEdit::textChanged, [this](const QString &value){spin_->setValue(value.toInt());}); // почему нельзя [spin_]
    connect(slider_, &QSlider::valueChanged, spin_, &QSpinBox::setValue);
}

void MainWindow::setupSlider() const
{
    slider_->setMaximum(50);
    slider_->setTickPosition(QSlider::TicksAbove);
    connect(spin_, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            slider_, &QSlider::setValue);
}

void MainWindow::setupEdit()
{
    edit_->setValidator(new QIntValidator(0, 50, this));
    connect(spin_, static_cast<void (QSpinBox::*)(const QString &)>(&QSpinBox::valueChanged),
            edit_, &QLineEdit::setText);
}

void MainWindow::setupLabel() const
{
    label_->setFrameStyle(QFrame::Box);
    connect(spin_, static_cast<void (QSpinBox::*)(const QString &)>(&QSpinBox::valueChanged),
            label_, &QLabel::setText);
}
