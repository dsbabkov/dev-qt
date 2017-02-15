#pragma once

#include <QAbstractTableModel>
#include "MyRect.h"

class MyModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    MyModel(QObject *parent = {});

    virtual int rowCount(const QModelIndex &parent = {}) const override;
    virtual int columnCount(const QModelIndex &parent = {}) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    virtual bool insertRows(int row, int count, const QModelIndex &parent = {}) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent = {}) override;

    MyRect rectAt(int id) const;

public slots:
    void addShape(const MyRect &rect);
    void clear();

signals:
    void shapeChanged(const MyRect &);
    void cleared();

private:
    void initializeHeaderData();

    QVariant colorData(int row, int role) const;
    QVariant styleData(int row, int role) const;
    QVariant widthData(int row, int role) const;

    bool setColorData(int row, const QVariant &value);
    bool setStyleData(int row, const QVariant &value);
    bool setWidthData(int row, const QVariant &value);

private:
    QVector<MyRect> scetch_;
    QStringList headerData_;
};
