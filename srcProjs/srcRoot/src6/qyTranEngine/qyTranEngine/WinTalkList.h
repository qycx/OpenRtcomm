#pragma once

#include <QWidget> 
#include "WinContactItem.h"
#include <QListWidgetItem>
#include <QSettings>
#include <QDebug>
//
//#include <QTextCodec> 
//
#include "WinObjUser.h"
#include "MessageSignalCenter.h"
#include <QVariant>;
#include "MessageData.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WinTalkList; }
QT_END_NAMESPACE

//消息界面的联系人
class WinTalkList : public QWidget
{
	Q_OBJECT

public:
	WinTalkList(QWidget *parent = Q_NULLPTR);
	~WinTalkList();


private:
	
	//QWidget* parent = nullptr;

private slots: 
	void on_listWidgetMsg_itemClicked(QListWidgetItem* item);
	//void do_addTalkInfoList(QString idinfo, QString msginfo);
	//收到新消息
	//void  slot_recv_new_message(MIS_MSG_TALK* talk);
	void  slot_recv_new_message(SendData sd);
	void onScrollBarValueChanged(int);

signals:
	void toShowContactMsg(WinObjUser user);
//	void toCDlgTalk(WinObjUser user);
//	void toCDlgTalkInfo(WinObjUser user); 
	

public:
	void addListWidget(WinObjUser user);
	void selListWidget(WinObjUser user);
	void initWinTalkListInfo();
	void load_initList();
	void initControl();
	void doNotify(SendData sd,SessionInfo si, WinContactItem *pContactItem);
	void delListWidget(QString idInfo);
	int  onLineStatusUp();

	void updateTalkItem(qint64 idInfo, unsigned  short status);

private:
	Ui::WinTalkList *ui; 
};
