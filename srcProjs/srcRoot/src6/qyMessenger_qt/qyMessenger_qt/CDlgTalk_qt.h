#ifndef CDLGTALK_QT_H
#define CDLGTALK_QT_H
#include "stdafx.h"
#include <QWidget>  
#include <QFile>
#include "WinTitle.h"
#include <QDebug>
#include <QListWidgetItem>
#include "WinMsgShow.h" 
#include "WinEmotion.h"

//
//#include <QDesktopWidget>
#include <QScreen>

//
#include <QPalette>
#include "WinObjUser.h"
#include "qyMcMainCommon_qt.h"
#include <dlgtalkproc.h>
#include <QToolTip>
#include <QSettings>
//
//#include <QTextCodec>
//
#include <qtimer.h>
#include "ui_CDlgTalk_qt.h"
#include "WinBasic.h"

#include <defineModels.h>
//
QT_BEGIN_NAMESPACE
namespace Ui { class CDlgTalk_qt; }
QT_END_NAMESPACE

class CDlgBallheadCamera;
class CDlgControlPtz;
class CDlgRemoteVideo;
class CDlgRemoteVideoMix;

class CDlgTalk_qt : public WinBasic
{
	Q_OBJECT
public:
	explicit CDlgTalk_qt(QWidget* parent = nullptr);
	~CDlgTalk_qt();

	//显示用户消息
	void ShowMsgInfo(WinObjUser user);
	//消息界面进来
	void hideWidget(WinObjUser user);
	//视频界面进来
	void showWidget(WinObjUser user,bool move=true);
	////接收到QTextEdit上的消息发送到widgetMsgShow去显示  
	void addShowMsg(QString msg, int64_t idinfo , int msgTime = 0 , QString msgid = "" , int msgtype = 0 , int  iTaskId = 0,int fileStatus = 0, int chatType = 0, int isMore =0 , int filesize = 0);
	int do_afterInit();
	int refreshLayout();

	//
	int doTimerProc();

	//
	void more_loadFinished(int page, int count);
	
	DLG_TALK_var* get_pm_var();
	void showFileProgress(QString msgid, QString Progress, int iStatus, qint64 idinfo_to);

	int doTask_av(int iCmd, int iTaskId);

	void video_curr_info(void* pContent);

	//关闭
	void closeCDlgTalk_qt();

	//
	void  refreshBtns();


	//void mouseDoubleClickEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

	//
	int  do_closeTaskAv_afterTaskClosed();


	//开始屏幕分享
	bool  bEnableScrollBar(bool  bEnable,  int  iw_scroll,  int  ih_scroll);
	void  clearScrollBar();

	//
	void  doEndAv();



	QWidget* getTalkWidget();
	
	//装载数据
	void initConfMem( QString searchStr = mynull );
	void initConfSpeakerList();
	int refreshConfSpeakerList();

	//
	int  do_confKeyChanged();

	//待发言人状态改变
	int  do_confMemKeyChanged(HWND hDlgTalk);

	//
	void updateMemStatus(qint64 idInfo, unsigned  short status);

	

	//
	void updateMenuComper();
	
	//
	void updateMemTable(QList<MemberInfo> memData);

	//
	void viewCompereControl();

	//
	QList<MemberInfo> reloadMemList(QList<MemberInfo> memDat);

	//
	void reloadMemsDoSpeak();

	//
	int  sendRemotePtzCmd_3ddw(PTZ_cmdParam_3ddw  *  pParam);

	//
	bool _is_device_screen = false;

protected:
	//自己重新实现拖动操作
	QPoint mousePosition;
	bool isMousePressed;
private:
	enum MousePosition
	{
		kMousePositionLeftTop = 11,
		kMousePositionTop = 12,
		kMousePositionRightTop = 13,
		kMousePositionLeft = 21,
		kMousePositionMid = 22,
		kMousePositionRight = 23,
		kMousePositionLeftButtom = 31,
		kMousePositionButtom = 32,
		kMousePositionRightButtom = 33,
	};
	enum SendType
	{
		Text,
		Image
	};
	struct SendContent
	{
		SendContent(SendType t, QString c)
		{
			type = t;
			content = c;
		}
		SendType type;
		QString content;
	};
public slots:
	void on_remotevideo_resize();
	void on_remotevideo_close();
	//初始化
	void initControl();
	//联系人信息
	void on_btnContactsInfo_clicked();
	//聊天
	void on_toolBtnChat_clicked();
	//发送消息
	void on_btnSendImg_clicked();
	//发送视频
	void on_btnVideo_clicked();
	//笑脸
	void on_btnFace_clicked();
	//发送文件
	void on_btnFileSend_clicked();
	//笑脸传到消息发送区
	void onEmotionItemClicked(QString code);
	//远程视频
	void on_toolBtnRemoteVideo_clicked(bool checked);
	void onEnterAction();
	void onEnterCtrlAction();
	//
	void procSendFile_qt(QString strFileName);
	void onFontSizecurrentIndexChanged(const QString& size);
	void currentCharFormatChanged(const QTextCharFormat& format);

	//浏览器加载完成
	void slot_web_loadFinished(bool successed);

	//最小化
	void onButtonMinClicked();
	//关闭窗体
	void onButtonCloseClicked();
	//还原
	void onButtonRestoreClicked();
	//最大化
	void onButtonMaxClicked();

	//点击更多菜单
	void on_MoreBtn_clicked();
	//申请发言
	void on_SpeakBtn_click();
	//结束会议
	void  on_EndAvBtn_click();
	//主页
	void on_toolBtnHome_click();
	//球机
	void on_toolBtnBall_click();
	//云台
	void on_toolBtnControl_click();
	//屏幕共享
	void on_toolBtnScreen_click();
	//设备共享
	void slot_device_screen();
	//设备屏幕共享
	void slot_devic_screen_select();
	//全屏
	void slot_full_screen();
	//本地视频隐藏显示
	void slot_this_video();
	//点击网盘
	void on_btnDisk_clicked();
	void on_btnRemoteVideo_clicked();
	//音视频设备
	void slot_device_select();
	//组成员显示
	void slot_grp_members();

	//球机显示
	void on_showBallheadCamera_slots();
	void on_closeBallheadCamera_slots();

	//云台控制窗口
	void on_showControlPtz_slots(const QString& name);
	void on_closeControlPtz_slots();
	void on_click3dPtz_slots(bool state);


	//会议控制
	void slot_conference_controller();
	
	void slot_make_list();

	void on_btnRule_clicked();

	int on_btnGrpDel_clicked();

	void on_btnMem_clicked();

	void RightShowMenu();
	void CopyAction();
	void PasteAction();
	//table 菜单
	void contextMenuRequest(QPoint pos);
	//list 菜单
	void listMenuRequest(QPoint pos);

	//

	//设为主持人
	void setCompere();
	//邀请发言
	void confCompere_inviteToSpeak();
	//停止发言
	void confCompere_stopSpeaking();

	void onMyScrollMoved(int a);

	//对话切换
	void cut_talk();

	//搜索
	void on_lineSearch_textChanged(QString str);

	//记录tablewidget
	void tableWidgetDellClick(QTableWidgetItem* item);
	// 
	void speakDellClick(QTableWidgetItem* item);
	//
	void upDownKeyTable(QString record_widget , bool isUp);

	void send_selLayoutType(QString str);

	void onClicked(QMouseEvent* event);
	void onDoubleClicked(QMouseEvent* event);

	//点击进入会议
	void on_video_in_do_clicked();

protected:
	//实时监控消息
	bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override ;
	//界面尺寸变化重绘
	virtual void resizeEvent(QResizeEvent* event) override;
	int  sizeAllControls_dlgTalk(HWND  hDlg, void* pDLG_TALK_var, RECT* pRect);
	int  mySizeAllControls_dlgTalk_peer(HWND  hDlg, DLG_TALK_var& m_var, DLG_talk_layout* pLayout, RECT* pRect);
	int  mySizeAllControls_dlgTalk_me_other(HWND  hDlg, DLG_TALK_var& m_var, DLG_talk_layout* pLayout, RECT* pRect);
	//按键抓取
	bool eventFilter(QObject* target, QEvent* event);
	bool event(QEvent* ev);
	void sizeOriginalVideo();
	QString separateEmotion(QString allmsg);

	void moveEvent(QMoveEvent* event) override;

	void onClickTimeout();

signals:
	void to_addTalkInfoList(QString idinfo, QString msgInfo);
	//
	void to_closeTalkInfo(QString idInfo);
	//
	void to_delTalkList(QString idInfo);

	void clicked(QMouseEvent* event);
	void doubleClicked(QMouseEvent* event);

	//
	void to_device_screen_status(bool is_open);
private:

	bool m_mousePressed;
	bool mouse_left_pressed_;
	QPoint mousePoint;
	bool m_WinMove = false;
	void keyPressEvent(QKeyEvent* event);

	void send_selLayoutType(int x, int y);

	void send_selLayoutTypeCancel();

	void ShowListMenu();

public:
	Ui::CDlgTalk_qt* ui;

	CDlgBallheadCamera* m_pBallheadCamera = nullptr; //选择球机列表
	CDlgControlPtz* m_pControlPtz = nullptr; //云台控制窗口

	CDlgRemoteVideo* m_pRemoteVideo = nullptr;
	CDlgRemoteVideoMix* m_pRemoteVideoMix = nullptr;

	bool _isVideoAmplifier = false;

	QList<MemberInfo> _memList;
	QList<MemberInfo> _memSearchList;

	QTimer* m_clickTimer;
	//
	//QMouseEvent m_event;
	std::unique_ptr<QMouseEvent> m_event;  // 使用智能指针
	//
	bool    m_dbClick = false;

	bool  m_b3ddw = false;

private:
	QAction* m_sendAction;
	QAction* m_ctrlSendAction;
	void mergeFormatOnWordOrSelection(const QTextCharFormat & format);
	//  2015/11/12	
	int iIndex_talkerInfo;						//  2015/11/12
	WinEmotion* m_emotionWindow = nullptr;
	CDlgTalk_qt* tmp_cdlgTalk = nullptr;
	WinTitle* m_pWinTitle = nullptr;
	QTimer* bottom_bar_hide_timer_ = nullptr;
	QTimer* scroll_bar_update_timer_ = nullptr;
	QPoint                  last_point_;             //记录放大之前的位置
	QPoint                  last_position_;          //窗口上一次的位置
	bool                      left_button_pressed_ = false;   //鼠标左键按下

	int                     mouse_press_region_ = kMousePositionMid; //鼠标点击的区域
	WinObjUser currentUser;

	QMenu* m_menuBall;

	QTimer* video_ing_list_timer_ = nullptr;
	//
	QScrollArea* scrollArea_ = nullptr;

	//
	bool				m_bShown_contactInfo = false;

	//记录最后一次操作的控件	
	QString  record_widget;

	//实时监测视频通话状态
	QTimer* video_ing_timer_ = nullptr;

	/*int m_iX_dst = 0;
	int m_iY_dst = 0;
	int m_iW_dst = 0;
	int m_iH_dst = 0;
	int m_iH_org = 0;
	int m_iW_org = 0;*/


	
};

//
int  confInitiator_setCompere(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_compere);



//
#endif // CDLGTALK_QT_H
