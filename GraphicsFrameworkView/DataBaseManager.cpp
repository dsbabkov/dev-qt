#include "DataBaseManager.h"
#include <QSqlDatabase>
#include <QtDebug>

DataBaseManager::DataBaseManager(QObject *parent)
    : QObject{parent}
{
}

void DataBaseManager::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mydb.sqlite");
    qDebug() << "Connection opened: " << db.open();
}
