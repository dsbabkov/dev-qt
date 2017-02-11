#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QIntValidator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(1, 100, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::syncSpinToEdit(const QString &text)
{
    ui->spinBox->setValue(text.toInt());
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "Title", "Text");
}
