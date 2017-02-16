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
    void showSqlTableView();
    void showSqlQueryView();

private:
    void createLineEditDialog();
    void createDatabaseManager();

private:
    Ui::MainWindow *ui;
};
