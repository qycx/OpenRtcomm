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
#include	<qscreen.h>

//
#include <QPalette>
#include "WinObjUser.h"
#include "qyMcMainCommon_qt.h"
#include <dlgtalkproc.h>
#include <QToolTip>
#include <QSettings>

//#include <QTextCodec>

#include <qtimer.h>
#include "ui_CDlgTalk_qt.h"
#include "WinBasic.h"
#include "CInfraredDialogMenu.h"
#include <defineModels.h>
#include "noticewidget.h"
#include "CDlgPortSetting.h"
#include "CDlgDebug.h"
#include "CDlgVideoAmplifier.h"
#include "CDlgBallheadCamera.h"
#include "CDlgControlPtz.h"
#include "CDlgControlPtzLocal.h"
#include "CDlgChairmanLayout.h"

//
QT_BEGIN_NAMESPACE
namespace Ui { class CDlgTalk_qt; }
QT_END_NAMESPACE

class CDlgTalk_qt : public QWidget
{
	Q_OBJECT
public:
	explicit CDlgTalk_qt(QWidget* parent = nullptr);
	~CDlgTalk_qt();

	//
	bool  m_bOnce = false;


	//显示用户消息
	void ShowMsgInfo(WinObjUser user);
	//消息界面进来
	void hideWidget(WinObjUser user);
	//视频界面进来
	void showWidget(WinObjUser user, bool move = true);
	////接收到QTextEdit上的消息发送到widgetMsgShow去显示  
	void addShowMsg(QString msg, int64_t idinfo, int msgTime = 0, QString msgid = "", int msgtype = 0, int  iTaskId = 0, int fileStatus = 0, int chatType = 0, int isMore = 0, int filesize = 0);
	int do_afterInit();
	int refreshLayout();

	void SetPeerDescPos(QRect& rect);

	//
	int doTimerProc();

	QString formatHHMMSS(qint64 ms); //秒转分秒

	void sxrzStatus();//检测认证状态
	quint64 getDiskSize(QString driver); //磁盘容量变
	//quint64 getDiskSpace(QString iDriver, bool flag);
	//QStringList getDiskName();
	//
	void more_loadFinished(int page, int count);

	DLG_TALK_var* get_pm_var();
	void showFileProgress(QString msgid, QString Progress, int iStatus, qint64 idinfo_to);

	int doTask_av(int iCmd, int iTaskId);

	//关闭
	void closeCDlgTalk_qt();

	//
	void  refreshBtns();



	void mouseDoubleClickEvent(QMouseEvent* event);

	//
	int  do_closeTaskAv_afterTaskClosed();


	//开始屏幕分享
	bool  bEnableScrollBar(bool  bEnable, int  iw_scroll, int  ih_scroll);
	void  clearScrollBar();

	//
	void  doEndAv();


	void showHint(QString msg, QString fontColor = "#f60", qint64 out_time = 3000);


	QWidget* getTalkWidget();

	//装载数据
	void initConfMem(QString searchStr = mynull);
	void initConfSpeakerList();
	int refreshConfSpeakerList();

	//
	int  do_confKeyChanged();

	//待发言人状态改变
	int  do_confMemKeyChanged(HWND hDlgTalk);

	//
	void updateMemStatus(qint64 idInfo, unsigned  short status);

	void sheetBackgroundImage();

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
	int do_shareDevice(bool  bEnable, bool  bSaveSpeakState);
	//
	void system_resolution();

	//
	//void mousePressEvent(QMouseEvent* event);


	//
protected:
	//自己重新实现拖动操作
	QPoint mousePosition;
	bool isMousePressed;

	void GetSpeakerList();
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
	//初始化
	void initControl();
	//联系人信息
	void on_btnContactsInfo_clicked();
	//聊天
	void on_toolBtnChat_clicked();
	//发送消息
	void on_btnSendImg_clicked();
	//发送视频
	void on_sendBtnVideo_clicked();
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

	void on_openShare_slots();

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
	void on_SpeakBtn_click(bool is_fast = false, bool is_speak = false);
	//开启摄像头
	void on_VideoBtn_click(bool is_fast = false);
	//开启麦克风
	void on_AudioBtn_click(bool is_fast = false);

	//本地云台（单向）
	void on_LoadPtzBtn_clicked();

	//画面放大
	void slot_amplifier_click();
	void on_showVideoAmplifier_slots();
	void on_closeVideoAmpLifier_slots();
	void on_closeVideoAmpOff_slots();

	//
	void sendSelVideo(unsigned  short usOp);

	//主席布局
	void slot_chairman_click();
	void on_closeChairman_slots();

	//球机显示
	void on_showBallheadCamera_slots();
	void on_closeBallheadCamera_slots();

	//远程云台控制窗口
	void on_showControlPtz_slots();
	void on_closeControlPtz_slots();

	//本地云台控制窗口
	void on_showControlPtzLocal_slots();
	void on_closeControlPtzLocal_slots();

	//结束会议
	void  on_EndAvBtn_click();
	//屏幕共享
	void on_toolBtnScreen_click();
	//全屏
	void slot_full_screen();
	//本地视频隐藏显示
	void slot_this_video();

	void slot_this_info();
	//点击网盘
	void on_btnDisk_clicked();
	//音视频设备
	void slot_device_select();
	//组成员显示
	void slot_grp_members();

	//会议控制
	void slot_conference_controller();

	void slot_make_list();

	void on_btnRule_clicked();

	int on_btnGrpDel_clicked();

	void on_btnMem_clicked();

	void slot_device_screen(bool is_fast = false); //设备共享

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

	//状态栏显示
	void on_showStatus();

	//搜索
	void on_lineSearch_textChanged(QString str);

	//记录tablewidget
	void tableWidgetDellClick(QTableWidgetItem* item);
	// 
	void speakDellClick(QTableWidgetItem* item);
	//
	void upDownKeyTable(QString record_widget, bool isUp);

	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	
	void onClicked(QMouseEvent* event);
	void onDoubleClicked(QMouseEvent* event);
	

	void on_infraredMenu();

	void infraredMenu_quit();

	void Infrared_up();
	void Infrared_down();
	void Infrared_ok(QString objname);
	void Infrared_input_left_right(QString name, bool isLeft); //左右箭头


	//
	void video_curr_info(void* pContent);

	void doBoxPort(QString objname);
	void doVideoAmpClick(QString objname);
	void doBallheadCameraClick(QString objname);
	void doControlPtzClick(QString objname);
	void doChairmanClick(QString objname);
	void on_showPortSetting_slots();
	void on_closePortSetting_slots();

	//
	void on_showDebug_slots();

	void refResolution();

protected:
	//实时监控消息
	bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
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

	void send_selLayoutType(int x, int y);

signals:
	void to_addTalkInfoList(QString idinfo, QString msgInfo);
	//
	void to_closeTalkInfo(QString idInfo);
	//
	void to_delTalkList(QString idInfo);

	void clicked(QMouseEvent* event);
	void doubleClicked(QMouseEvent* event);
private:

	bool m_mousePressed;
	bool mouse_left_pressed_;
	QPoint mousePoint;
	bool m_WinMove = false;
	void keyPressEvent(QKeyEvent* event);

	void onClickTimeout();
	void onCheckMemTimeout();

	std::unique_ptr<QMouseEvent> m_event;  // 使用智能指针
	//
	bool    m_dbClick = false;

public:
	Ui::CDlgTalk_qt* ui;

	CInfraredDialogMenu* m_pInfraredMenu = nullptr;  //红外菜单
	CDlgPortSetting* m_pPortSetting = nullptr; //端口设置窗口弹出
	CDlgVideoAmplifier* m_pVideoAmplifier = nullptr; //窗口放大 正在发言列表
	CDlgBallheadCamera* m_pBallheadCamera = nullptr; //选择球机列表
	CDlgControlPtz* m_pControlPtz = nullptr; //云台控制窗口
	CDlgControlPtzLocal* m_pControlPtzLocal = nullptr; //云台控制窗口  本地
	CDlgChairmanLayout* m_pChairmanLayout = nullptr; //主席布局

	//
	bool _isSpeak = false;
	bool _isVideo = false;
	bool _isAudio = true;
	bool _isDeviceScreen = false;
	bool _isVideoAmplifier = false;
	bool _isChairmanLayout = false;
	//
	bool _is_infrared = false;  //是否有菜单出现




	QString _sxtTxt = u8"关闭摄像头(on)";
	QString _mkfTxt = u8"开启麦克风(off)";
	QString _flTxt = u8"已禁用辅流";

	QList<MemberInfo> _memList;
	QList<MemberInfo> _memSearchList;


private:
	QAction* m_sendAction;
	QAction* m_ctrlSendAction;
	void mergeFormatOnWordOrSelection(const QTextCharFormat& format);
	//  2015/11/12	
	int iIndex_talkerInfo;						//  2015/11/12
	WinEmotion* m_emotionWindow = nullptr;
	CDlgTalk_qt* tmp_cdlgTalk = nullptr;
	WinTitle* m_pWinTitle = nullptr;
	QTimer* bottom_bar_hide_timer_ = nullptr;
	QTimer* scroll_bar_update_timer_ = nullptr;
	QTimer* infrared_close_timer_ = nullptr;

	QTimer* m_clickTimer = nullptr;

	QTimer* m_checkMemTimer = nullptr;

	QPoint                  last_point_;             //记录放大之前的位置
	QPoint                  last_position_;          //窗口上一次的位置
	bool                      left_button_pressed_ = false;   //鼠标左键按下

	int                     mouse_press_region_ = kMousePositionMid; //鼠标点击的区域
	WinObjUser currentUser;

	//
	QScrollArea* scrollArea_ = nullptr;

	//
	bool				m_bShown_contactInfo = false;

	//记录最后一次操作的控件	
	QString  record_widget;


	//NoticeWidget noticeWin;
	int Audia_close = 0;

	int i_availableSize = 0; // 磁盘可用空间
	int i_zongSize = 0;    //磁盘总容量


	//单向双向热切换，记录最后一次操作
	bool lastFlag;
	

};

//
int  confInitiator_setCompere(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_compere);



//
#endif // CDLGTALK_QT_H
