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
    void syncSpinToEdit(const QString &text);

    void on_actionAbout_triggered();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
};
