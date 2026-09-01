#pragma once

#include <QWidget>
#include "WinBasic.h"
#include "ui_MsgRecordSon.h"

class MsgRecordSon : public WinBasic
{
	Q_OBJECT

public:
	MsgRecordSon(QWidget *parent = Q_NULLPTR);
	~MsgRecordSon();


	static void closeDialog();
	void paintEvent(QPaintEvent* event);
	static void showWnd(QPoint pt);
	static void setContent(QString userId , QString msgId);
	static void getDialog();
	void removeProessAll();

private:
	void showEvent(QShowEvent* event);
private:
	Ui::MsgRecordSon ui;
};
