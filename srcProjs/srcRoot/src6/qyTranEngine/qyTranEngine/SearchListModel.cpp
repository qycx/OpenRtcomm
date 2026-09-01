#include "SearchListModel.h"
#include <QPainter>
#include <QDebug>

SearchListModel::SearchListModel(QObject* parent)
    : QAbstractListModel(parent)
{

}

SearchListModel::~SearchListModel()
{
}

QVariant SearchListModel::data(const QModelIndex& index, int role) const
{
    return QVariant();
}

void SearchListModel::clear()
{
    m_infoList.clear();
    emit layoutChanged();
}

void SearchListModel::setMoudleData(QList<SearchInfoData> data)
{
    m_infoList.clear();
    m_infoList.append(data);
    emit layoutChanged();
}

SearchInfoData& SearchListModel::at(int index)
{
    return m_infoList[index];
}

SearchListDelegate::SearchListDelegate(SearchListModel* model, QObject* parent /*= 0*/)
    :QStyledItemDelegate(parent)
{
    m_listViewModel = model;
}

SearchListDelegate::~SearchListDelegate()
{

}

void SearchListDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index.column() == 0)
    {
        SearchInfoData data = m_listViewModel->at(index.row());
        QRect rect = option.rect;
        int lf = 12;
        QFont font;
        font.setFamily("Microsoft YaHei");
        font.setPixelSize(17);
        painter->setPen(QColor("#000"));//字体颜色
        painter->setFont(font);
        
        

        if (data.isGourp)
        {
            QRect txtRec(rect.left() + lf, rect.top(), rect.width() - lf, rect.height());
            painter->drawText(txtRec, Qt::AlignVCenter | Qt::AlignLeft, data.name);
            return;
        }

        if (data.isMsg) {
            painter->save();
            QFont font1; // 需要设置的字体
            font1.resolve(QFont::AllPropertiesResolved);
            font1.setFamily("Microsoft YaHei");
            // painter->setFont(font1);//设置字体
            font1.setPixelSize(15);
            painter->setFont(font1);
            painter->setPen(QColor("#888"));//字体颜色
            
            QRect txtRec(rect.height() , rect.top() +rect.height() * 0.6 , rect.width() - rect.height(), rect.height() * 0.4 - 6);
            painter->drawText(txtRec, Qt::AlignVCenter | Qt::AlignLeft, data.msg);//位置和内容
            painter->restore();
        }

        if (!data.url.isEmpty())
        {
            painter->drawPixmap(rect.left() + lf, rect.top() + lf, QPixmap(data.url).scaled(rect.height() - lf * 2, rect.height() - lf * 2));
        }
        QRect txtRec(rect.height(), rect.top() + 6, rect.width() - rect.height(), rect.height() * (data.isMsg ? 0.6 : 1) - 6);
        painter->drawText(txtRec, Qt::AlignVCenter | Qt::AlignLeft, data.name);
        qDebug() << option.rect;
    }
    QStyledItemDelegate::paint(painter, option, index);

}




QSize SearchListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QSize sz = QStyledItemDelegate::sizeHint(option, index);
    SearchInfoData data = m_listViewModel->at(index.row());
    if (data.isGourp)
    {
        sz.setHeight(30);
    }
    else
    {
        sz.setHeight(64);
    }

    return sz;
}
