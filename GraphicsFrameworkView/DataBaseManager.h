#pragma once

#include <QObject>

class DataBaseManager: public QObject
{
    Q_OBJECT
public:
    DataBaseManager(QObject *parent = {});
    ~DataBaseManager() = default;

public slots:
    void createConnection();
};
