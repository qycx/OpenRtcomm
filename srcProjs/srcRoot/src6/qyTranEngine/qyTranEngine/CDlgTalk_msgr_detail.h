#pragma once

#include <QWidget>
#include "ui_CDlgTalk_msgr_detail.h"
#include "WinTitle.h"
#include "WinContactsList.h"
#include "WinObjUser.h"
//
#include	"ctxQmc_qt.h"

//
QT_BEGIN_NAMESPACE
namespace Ui { class CDlgTalk_msgr_detail; }
QT_END_NAMESPACE

//
class CDlgTalk_msgr_detail : public QWidget
{
	Q_OBJECT

public:
	CDlgTalk_msgr_detail(QWidget *parent = Q_NULLPTR);
	~CDlgTalk_msgr_detail();

	//显示用户信息
	void ShowContactsListInfo(WinObjUser user);
private:
	//初始化
	void initControl();

private slots:
	//发送消息
	void on_btnSendMsg_clicked();
	//发起会议
	void on_benSendMeeting_clicked();
	void on_setBtn_clicked();

signals:
	void toSendMsg(WinObjUser user);
	//void toSendMeeting(WinObjUser user);

private:
	Ui::CDlgTalk_msgr_detail* ui; 
	//
	WinObjUser m_curUser;

};
