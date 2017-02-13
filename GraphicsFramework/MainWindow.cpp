#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MyScene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new MyScene(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}
