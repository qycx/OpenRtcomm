#ifndef _QSYSTEM_TRAY_ICON_H_
#define _QSYSTEM_TRAY_ICON_H_
#pragma once

#include <QObject>
#include <QAbstractNativeEventFilter>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include "MessageData.h"




class QSystemTrayIconEx : public QObject
{
	Q_OBJECT

public:
	QSystemTrayIconEx(QIcon icon, QObject *parent);
	~QSystemTrayIconEx();
	void AddMenu(QAction* action);
	//控制托盘闪烁
	void tray_time_star(QWidget* parent, bool bstar = false);
	//添加会话
	void add_new_session(SessionInfo session);
	//移除会话
	void remove_session(qint64 userId);
private:
	void iconIsActived(QSystemTrayIcon::ActivationReason res);
Q_SIGNALS:
	void LButton_Click();
	void LButton_DBClick();
	void open_session(qint64 sid, QString sname);
private:
	QMenu*									_m_menu=nullptr;
	QIcon icon_;

	//
	QTimer* m_tray_time = nullptr;

};
#endif

