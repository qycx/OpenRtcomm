#pragma once

#include <QWidget>
#include "ui_WinContactsGroupInfo.h"
#include "WinContactItem.h"
#include "WinObjUser.h"
#include <QDebug>
#include <QFile>
#include <QScrollBar>
#include	"stdafx.h"
#include	"qyMcMainCommon_qt.h"
#include    "qyMcMainWndProc.h"  
#include	"ctxQmc.h"
#include	"myDb.h"


QT_BEGIN_NAMESPACE
namespace Ui { class WinContactsGroupInfo; }
QT_END_NAMESPACE

//群组信息
class WinContactsGroupInfo : public QWidget
{
	Q_OBJECT

public:
	WinContactsGroupInfo(QWidget* parent = Q_NULLPTR);
	~WinContactsGroupInfo();

	//显示群组信息
	void ShowContactsGroupInfo(WinObjUser user);
private:
	void initControl();

public:
	void showGroupContactList(CMyDb* pDb, IM_GRP_MEM* pQMem, int64_t* idinfo);
	int toGetGroupByIdInfo(int64_t idinfo, QString name);

private slots:
	//发送消息
	void on_btnSendMsg_clicked();
	//发送视频会议
	void on_benSendMeeting_clicked();

signals:
	void toSendMsg(WinObjUser);
	void toSendMeeting(WinObjUser);

private:
	Ui::WinContactsGroupInfo* ui;
	QWidget* grpWidget = nullptr;
	WinObjUser m_curUser;
};
