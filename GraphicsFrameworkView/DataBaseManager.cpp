#include "DataBaseManager.h"
#include <QSqlDatabase>
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlError>

DataBaseManager::DataBaseManager(QObject *parent)
    : QObject{parent}
{
}

void DataBaseManager::createConnection() const
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mydb.sqlite");
    qDebug() << "Connection opened: " << db.open();
}

void DataBaseManager::createTable() const
{
    qDebug() << "Table created: " <<
    QSqlQuery().exec("CREATE TABLE rectangle ("
                     "id INTEGER PRIMARY KEY,"
                     "color VARCHAR,"
                     "pen_style UNSIGNED,"
                     "pen_width UNSIGNED,"
                     "left DOUBLE,"
                     "top DOUBLE,"
                     "width DOUBLE,"
                     "height DOUBLE)");
}

void DataBaseManager::writeTable(const QVector<MyRect> &rects) const
{
    if (!rects.isEmpty()){
        QSqlQuery q;
        q.prepare("INSERT INTO rectangle (color, pen_style, pen_width, left, top, width, height) "
                  "VALUES (:color, :pen_style, :pen_width, :left, :top, :width, :height)");

        for (const MyRect &rect: rects){
            q.bindValue(":color", rect.pen().color());
            q.bindValue(":pen_style", static_cast<unsigned>(rect.pen().style()));
            q.bindValue(":pen_width", rect.pen().width());
            q.bindValue(":left", rect.rect().left());
            q.bindValue(":top", rect.rect().top());
            q.bindValue(":width", rect.rect().width());
            q.bindValue(":height", rect.rect().height());

            if (!q.exec()){
                qCritical() << "Unexpected error got:" << q.lastError().text();
                return;
            }
        }
        qDebug() << "Write done";
        return;
    }
    qDebug() << "No data to write";
}
