#pragma once

#include "WinBaseDialog.h"
#include <QCloseEvent>
#include "ui_TipViewIM.h"
#include "MessageData.h"

class TipViewIM : public WinBaseDialog
{
	Q_OBJECT

public:
	~TipViewIM();
	static TipViewIM* ShowTipView(QRect rect);
	static void CloseTipView();
	static QList<SessionInfo> listSessions();
	static void ClearSessions();
	static void addListSession(SessionInfo session);
	static void removeSession(qint64 sid);
private Q_SLOTS:
	void button_lose();
Q_SIGNALS:
	void lose();
	void open_session(qint64 sid, QString sname);
private:
	TipViewIM();
	virtual void closeEvent(QCloseEvent * event);
	virtual void enterEvent(QEvent *event);
	virtual void leaveEvent(QEvent *event);
private:
	Ui::TipViewIM ui;
	bool											_bMouseEnter = false;
	static 	QList<SessionInfo>						_list_sessions;
};
