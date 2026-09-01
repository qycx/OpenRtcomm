#pragma once

#include <QWidget>
#include "ui_SearchMsgRecord.h"
#include "WinBasic.h"
#include <MessageData.h>

class SearchMsgRecord : public WinBasic
{
	Q_OBJECT

public:
	SearchMsgRecord( QWidget *parent = Q_NULLPTR);
	~SearchMsgRecord();

	static void getDialog(  );
	static void showWnd(QPoint pt);
	static void setContent(QString userid, QString keyword);
	static void closeDialog();

	void paintEvent(QPaintEvent* event);
	void removeProessAll();
	void showEvent(QShowEvent* event);

public slots:
	void slot_list_item_clicked(QModelIndex idx);
	void on_btnTalker_clicked();
private:
	Ui::SearchMsgRecord* ui;
	QList<MessageData> _msgs;
	QString _idInfo;
};
