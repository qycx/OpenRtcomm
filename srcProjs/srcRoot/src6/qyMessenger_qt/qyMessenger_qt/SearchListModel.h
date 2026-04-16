#pragma once

#include <QAbstractListModel>
#include <QStyledItemDelegate>
#include <QList>
#include <MessageData.h>

struct SearchInfoData
{
    QString userId;
    QString url ;
    QString name;
    bool isGourp=false;
    bool isMsg = false;
    QString msg = "";
};

class SearchListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    SearchListModel(QObject *parent = nullptr);
    ~SearchListModel();
    int rowCount(const QModelIndex &parent) const {
        return m_infoList.size();
    }

    int columnCount(const QModelIndex &parent) const { return 1; }
    void clear();
   QVariant data(const QModelIndex &index, int role) const;

   void setMoudleData(QList<SearchInfoData> data);
    SearchInfoData& at(int index);
private:
    QList<SearchInfoData> m_infoList;


};

class SearchListDelegate :public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SearchListDelegate(SearchListModel *model, QObject *parent = 0);
    ~SearchListDelegate();

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    
private:
    SearchListModel *m_listViewModel;
    //StudentFrame *m_studentFrame;
};
