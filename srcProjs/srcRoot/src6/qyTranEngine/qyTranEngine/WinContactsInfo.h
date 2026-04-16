#pragma once

#include <QWidget>
#include "ui_WinContactsInfo.h"
#include "WinTitle.h"
#include "WinContactsList.h"
#include "WinObjUser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WinContactsInfo; }
QT_END_NAMESPACE

//
class WinContactsInfo : public QWidget
{
	Q_OBJECT

public:
	WinContactsInfo(QWidget *parent = Q_NULLPTR);
	~WinContactsInfo();

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

signals:
	void toSendMsg(WinObjUser user);
	void toSendMeeting(WinObjUser user);

private:
	Ui::WinContactsInfo* ui; 
};
