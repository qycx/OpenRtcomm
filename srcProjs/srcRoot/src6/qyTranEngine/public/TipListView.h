#ifndef _IM_TIP_LIST_VIEW_H_
#define _IM_TIP_LIST_VIEW_H_

#pragma once
#include <QList>
#include <QListView>
#include <QStandardItemModel>
#include "MessageData.h"


class TipListView : public QListView
{
	Q_OBJECT

public:
	TipListView(QWidget *parent);
	~TipListView();
	void setTipSession(const QList<SessionInfo> sessions);
Q_SIGNALS:
	void open_session(qint64 sid, QString sname);
private slots:
	void slot_list_activated(QModelIndex idx);
private:
	//void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;
private:
	QStandardItemModel*								_item_module = nullptr;

};
#endif