#pragma once

#include <QWidget>
#include "ui_TipViewItem.h"
#include <QStandardItem>
#include <QMenu>
#include "MessageData.h"

class TipViewItem :public QWidget
{
	Q_OBJECT

public:
	TipViewItem(const SessionInfo session, QStandardItem* item, QWidget *parent = Q_NULLPTR);
	~TipViewItem();
	qint64  sId();
	QString  sName();
private:
	//virtual void on_download_finished(QString id, QString spath, DownLoadType type);
private:
	void _set_photo(QString img);
private:
	Ui::TipViewItem ui;
private:
	qint64			_sid;
	QString			_sname;
};
