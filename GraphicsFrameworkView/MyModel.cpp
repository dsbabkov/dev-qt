#include "MyModel.h"
#include <functional>
#include "LineDialog.h"
#include "MyModelColumns.h"

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel{parent}
    , scetch_{}
{
    initializeHeaderData();
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    if (parent != QModelIndex()){
        return 0;
    }
    return scetch_.size();
}

int MyModel::columnCount(const QModelIndex &parent) const
{
    if (parent != QModelIndex()){
        return 0;
    }

    return static_cast<int>(Column::ColumnCount);
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return {};
    }

    using namespace std::placeholders;
    const std::map<Column, std::function<QVariant (int, int)>> dataMap = {
        {Column::Color, std::bind(&MyModel::colorData, this, _1, _2)},
        {Column::Style, std::bind(&MyModel::styleData, this, _1, _2)},
        {Column::Width, std::bind(&MyModel::widthData, this, _1, _2)}
    };

    Q_ASSERT(dataMap.size() == static_cast<size_t>(Column::ColumnCount));

    const std::function<QVariant (int, int)> &dataFunction = dataMap.at(static_cast<Column>(index.column()));
    return dataFunction(index.row(), role);
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole){
        return {};
    }

    if (orientation == Qt::Horizontal &&
            section < static_cast<int>(Column::ColumnCount)){
        return headerData_.at(section);
    }

    if (orientation == Qt::Vertical &&
            section < scetch_.size()){
        return section;
    }

    return {};
}

bool MyModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (parent != QModelIndex()){
        return false;
    }

    beginInsertRows({}, row, row + count - 1);
    scetch_.insert(row, count, {});
    endInsertRows();
    return true;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()){
        return {};
    }

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole){
        return false;
    }

    using namespace std::placeholders;
    const std::map<Column, std::function<bool (int, const QVariant &)>> setDataMap = {
        {Column::Color, std::bind(&MyModel::setColorData, this, _1, _2)},
        {Column::Style, std::bind(&MyModel::setStyleData, this, _1, _2)},
        {Column::Width, std::bind(&MyModel::setWidthData, this, _1, _2)}
    };

    Q_ASSERT(setDataMap.size() == static_cast<size_t>(Column::ColumnCount));

    const std::function<bool (int, const QVariant &)> setFunction = setDataMap.at(static_cast<Column>(index.column()));

    if (setFunction(index.row(), value)){
        emit dataChanged(index, index);
        emit shapeChanged(scetch_.at(index.row()));
        return true;
    }
    return false;
}

MyRect MyModel::rectAt(int id) const
{
    return scetch_.at(id);
}

void MyModel::addShape(const MyRect &rect)
{
    const int index = rowCount();
    insertRow(index);
    scetch_[index] = rect;
}

void MyModel::initializeHeaderData()
{
    const std::map<Column, QString> headerMap = {
        {Column::Color, tr("Color")},
        {Column::Style, tr("Style")},
        {Column::Width, tr("Width")}
    };

    Q_ASSERT (headerMap.size() == static_cast<int>(Column::ColumnCount));

    headerData_.clear();
    for (const auto &headerPair: headerMap) {
        headerData_ << headerPair.second;
    }
}

QVariant MyModel::colorData(int row, int role) const
{
    const QColor &color= scetch_.at(row).pen().color();

    if (role == Qt::DecorationRole){
        QPixmap px(32, 32);
        px.fill(color);
        return px;
    }
    else if (role == Qt::DisplayRole ||
             role == Qt::EditRole){
        return color;
    }

    return {};
}

QVariant MyModel::styleData(int row, int role) const
{
    const Qt::PenStyle penStyle = scetch_.at(row).pen().style();

    if (role == Qt::DisplayRole){
        for (const NamedPenStyle &style: LineDialog::penStyles()){
            if (style.style == penStyle){
                return style.name;
            }
        }
    }

    else if (role == Qt::EditRole){
        return static_cast<uint>(penStyle);
    }

    return {};
}

QVariant MyModel::widthData(int row, int role) const
{
    if (role == Qt::EditRole ||
            role == Qt::DisplayRole){
        return scetch_.at(row).pen().width();
    }

    return {};
}

bool MyModel::setColorData(int row, const QVariant &value)
{
    MyRect &rect = scetch_[row];
    QPen newPen = rect.pen();
    newPen.setColor(value.value<QColor>());
    rect.setPen(newPen);

    return true;
}

bool MyModel::setStyleData(int row, const QVariant &value)
{
    MyRect &rect = scetch_[row];
    QPen newPen = rect.pen();

    bool ok;
    Qt::PenStyle style = static_cast<Qt::PenStyle>(value.toInt(&ok));
    if (!ok){
        return false;
    }

    newPen.setStyle(style);
    rect.setPen(newPen);

    return true;

}

bool MyModel::setWidthData(int row, const QVariant &value)
{
    MyRect &rect = scetch_[row];
    QPen newPen = rect.pen();

    bool ok;
    int width = value.toInt(&ok);
    if (!ok){
        return false;
    }
    newPen.setWidth(width);
    rect.setPen(newPen);

    return true;
}

