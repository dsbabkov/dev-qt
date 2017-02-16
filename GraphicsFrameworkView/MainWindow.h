#pragma once
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = {});
    ~MainWindow();

private slots:
    void setColor();

private:
    void createLineEditDialog();

private:
    Ui::MainWindow *ui;
};
