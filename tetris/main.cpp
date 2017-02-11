#include "MainWindow.h"
#include <QApplication>
#include <random>
#include <ctime>


int main(int argc, char *argv[])
{
    srand(time(0));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
