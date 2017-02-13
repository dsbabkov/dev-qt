#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Figure.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->glass, &Glass::scoreChanged, ui->scoreLCD, static_cast<void (QLCDNumber::*)(int)>(&QLCDNumber::display));
    connect(ui->glass, &Glass::nextFigureChanged, ui->nextFigure, &NextFigure::setFigure);
}

MainWindow::~MainWindow()
{
    delete ui;
}