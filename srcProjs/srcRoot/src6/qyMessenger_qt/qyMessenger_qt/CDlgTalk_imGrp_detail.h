#pragma once

#include <QWidget>
#include "ui_CDlgTalk_imGrp_detail.h"
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
#include	"ctxQmc_qt.h"


QT_BEGIN_NAMESPACE
namespace Ui { class CDlgTalk_imGrp_detail; }
QT_END_NAMESPACE

//群组信息
class CDlgTalk_imGrp_detail : public QWidget
{
	Q_OBJECT

public:
	CDlgTalk_imGrp_detail(QWidget* parent = Q_NULLPTR);
	~CDlgTalk_imGrp_detail();

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
	//点击规则设置
	void on_setBtn_clicked();
signals:
	void toSendMsg(WinObjUser);
	//void toSendMeeting(WinObjUser);

private:
	Ui::CDlgTalk_imGrp_detail* ui;
	QWidget* grpWidget = nullptr;
	//
	WinObjUser m_curUser;
};
