#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MyScene.h"
#include <QActionGroup>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new MyScene(this));

    connect(ui->setColorAct, &QAction::triggered, this, &MainWindow::setColor);

    setupButtonGroup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setColor()
{
    MyScene *scene = static_cast<MyScene *>(ui->graphicsView->scene());
    const QColor &color = QColorDialog::getColor(scene->color(), this,
                           tr("Color for scene pen"));

    if (color.isValid()){
        scene->setColor(color);
    }
}

void MainWindow::setupButtonGroup()
{
    QActionGroup *actionGroup = new QActionGroup(this);

    actionGroup->addAction(ui->rectangleAct);
    actionGroup->addAction(ui->ellipceAct);
}
