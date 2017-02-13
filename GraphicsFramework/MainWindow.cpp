#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MyScene.h"
#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new MyScene(this));

    setupButtonGroup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupButtonGroup()
{
    QActionGroup *actionGroup = new QActionGroup(this);

    actionGroup->addAction(ui->rectangleAct);
    actionGroup->addAction(ui->ellipceAct);
}
