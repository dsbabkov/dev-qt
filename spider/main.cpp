#include "Spider.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load(QLocale::system(), "spider", "_");
    a.installTranslator(&translator);

    Spider w;
    w.showMaximized();

    return a.exec();
}
