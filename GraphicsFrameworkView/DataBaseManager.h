#pragma once

#include <QObject>
#include "MyRect.h"

class DataBaseManager: public QObject
{
    Q_OBJECT
public:
    DataBaseManager(QObject *parent = {});
    ~DataBaseManager() = default;

signals:
    void shapeRead(const MyRect &rect) const;

public slots:
    void createConnection() const;
    void createTable() const;
    void writeTable(const QVector<MyRect> &rects) const;
    void readTable() const;
};
