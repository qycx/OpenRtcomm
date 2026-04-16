#pragma once

#include <QWidget>
#include "ui_MsgRecordItem.h"

class MsgRecordItem : public QWidget
{
	Q_OBJECT

public:
	MsgRecordItem(QWidget *parent = Q_NULLPTR);
	~MsgRecordItem();

	void setName(QString strName);
	void setMsg(QString strMsg);
	void set_on();
	void setCursor();

private:
	Ui::MsgRecordItem ui;
};
