#include "MyDelegate.h"
#include "MyModelColumns.h"
#include <QComboBox>
#include "LineDialog.h"
#include <QMouseEvent>
#include <QColorDialog>

MyDelegate::MyDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

QWidget *MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()){
        return {};
    }

    if (index.column() == static_cast<int>(Column::Style)){
        QComboBox *combo = new QComboBox(parent);
        for (const NamedPenStyle &penStyle: LineDialog::penStyles()){
            combo->addItem(penStyle.name, static_cast<int>(penStyle.style));
        }
        return combo;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void MyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (!index.isValid()){
        return;
    }

    if (index.column() == static_cast<int>(Column::Style)){
        QComboBox *combo = static_cast<QComboBox *>(editor);
        combo->setCurrentText(index.model()->data(index).toString());
        return;
    }

    QStyledItemDelegate::setEditorData(editor, index);
}

void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() == static_cast<int>(Column::Style)){
        model->setData(index, static_cast<QComboBox *>(editor)->currentData().toUInt());
        return;
    }
    QStyledItemDelegate::setModelData(editor, model, index);
}

bool MyDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (index.column() == static_cast<int>(Column::Color) &&
            event->type() == QEvent::MouseButtonDblClick){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

        if (mouseEvent->button() == Qt::LeftButton){
            const QColor &color = QColorDialog::getColor(model->data(index, Qt::EditRole).value<QColor>());
            if (color.isValid()){
                return model->setData(index, color);
            }
            return false;
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
