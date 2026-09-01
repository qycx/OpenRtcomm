#ifndef CMAINFRAME_H
#define CMAINFRAME_H
#include "WinBasic.h"
#include <QWidget>
#include <QMouseEvent>
#include <QSettings>
#include <QAction>
#include <QtGui>
#include <qpointer.h>
#include "qflags.h"
#include "CDlgTalk_qt.h"
//
//#include <QDesktopWidget>
#include	<qscreen.h>

#include <QStackedWidget>
#include "qyMcMainCommon_qt.h"
#include "qyMcMainWndProc.h" 
#include "QSystemTrayIconEx.h"
#include "WinSystemSetup.h"
#include "SearchListModel.h"
#include "CUserLogin.h"
#include "CDlgPortSetting.h";
#include "CDlgDebug.h"
#include "CDlgP2p.h"
#include "CInfraredDialogMenu.h"
#include "ShareStreamWidget.h"
#include "noticewidget.h"
#include "CDlgOther.h"
#include "CDlgP2pMsg.h"
#include <CQmcLogin.h>

#include "myDb.h"

class CDlgShareDynBmps_qt;

QT_BEGIN_NAMESPACE
namespace Ui { class CMainFrame; }
QT_END_NAMESPACE

//stackedWidgetInfo index
#define INFO_MSG 0
#define INFO_CONTACTS_INFO 1
#define INFO_CONTACTS_GROUP_INFO 2
#define INFO_WINADVANCEDSET 3

//stackedWidgetContact index
#define CONT_TALKLIST 0
#define CONT_CONTACTSLIST 1





//
class CMainFrame : public  WinBasic //QWidget
{
	Q_OBJECT


public:
	struct {
		QY_MC_mainWndVar		common;
		//ZONE_objs_info			wall;
	}var;

	QString m_myName;


protected:
	void OpenRestartShareTimer();
	void CloseRestartShareTimer();

	//
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
public:
	explicit CMainFrame(QWidget* parent = nullptr);
	~CMainFrame();
	/// <summary>
  /// 消息数累加
  /// </summary>
  /// <param name="count"></param>
	void AddNewMsgCount(int count);
	/// 消息数累减
	/// </summary>
	/// <param name="count"></param>
	void UpMsgCount(int count);
	/// <summary>
	/// 清空消息提示
	/// </summary>
	void Clear();
	/// <summary>
	/// 登录后初始化
	/// </summary>
	void Init();

	void AutoStartShare();

	int toContactList();

	void addToContactList_main(CMyDb* pDb, COMMON_PARAM* pCommonParam1, QMEM_qyImObj* pQMem);

	//int  tmpHandler_printContactList_newGroup();
	int switchToContact();
	//播放声音
	static void playReciveSound(int loop = 1);
	//任务栏闪烁
	static void flashTaskWindow();
	bool isMsgSel();
	int getCurIdInfo(QY_MESSENGER_ID* pIdInfo);
	void delContactList(QString idInfo);

	//
	int dbg_testFunc();
	int onLineStatus();

	//调出红外菜单
	//void infraredMenu(QString s_status);
	//红外菜单退出
	//void infraredMenu_quit();

	void updateSearchItem(qint64 idInfo, unsigned  short status);
	//

	bool isShareOpen();

	//自适应背景图片
	void sheetBackgroundImage();
	void system_resolution();

	void ExitMenu();
private:
	//初始化控件
	void initControl();
	//初始化托盘
	void init_tray_icon(QIcon icon);
	int tray_open_session(qint64 userId);
	//判断widgetType是否是stackedWidget中当前widget,如果不是设置为
	bool isCurInStackWidget(const char* widgetType, QStackedWidget* stackWidget);
	//void mouseMoveEvent(QMouseEvent* event);
	//void mouseReleaseEvent(QMouseEvent*);
	//void mousePressEvent(QMouseEvent* event);
	///**
 //  * @brief  根据鼠标的设置鼠标样式，用于拉伸
 //  */
	//void SetMouseCursor(int x, int y);
	///**
	//* @brief  判断鼠标的区域，用于拉伸
	//*/
	//int GetMouseRegion(int x, int y);
	//红点数
	int msgCount = 0;

	//显示共享流窗口
	void showShareStreamWidget();
	//关闭共享流窗口
	void closeShareStreamWidget();

	//
	struct {
		HANDLE		m_hThread_ca = nullptr;
		//
		int			nTimes_noUsrKey = 0;

	}				m_chkUsrKey;
	//
	int chkUsrKey();
	int stopChkingUsrKey();


	//
signals:
	void to_userLogin_signal();

public slots:
	//
	void on_timer_winMethod();
	//消息
	void on_toolBtnMsg_clicked();
	//联系人
	void on_toolBtnContact_clicked();
	//系统设置
	void on_toolBtnSystem_clicked();
	//缩小
	void on_ButtonMin_clicked();
	//关闭
	void on_ButtonClose_clicked();
	//还原
	void on_ButtonRestore_clicked();
	//放大
	void on_ButtonMax_clicked();
	//显示用户消息
	void on_Contact_Msg(WinObjUser user);
	//显示用户信息
	void on_Contacts_Info(WinObjUser user);
	//发送消息
	void on_SendMsg_clicked(WinObjUser user);
	//发起会议
	//void on_SendMeeting_clicked(WinObjUser user);
	//消息视频
	void createCDlgTalk(WinObjUser);
	//点击头像
	void on_headIcoBtn_clicked();
	//托盘菜单
	void on_tray_menu();
	//创建群聊
	void on_newGroupBtn_clicked();
	//菜单
	void trigerMenu(QAction* act);
	//搜索
	void slot_search_text_changed(QString str);
	//选中一个搜索结果
	void slot_list_activated(QModelIndex idx);

	//刷新分辨率
	void refResolution();

	//手动入会
	void on_btnMeeting_clicked(QString objname = nullptr);
	//手动入会第二个会议
	void on_btnMeeting2_clicked(QString objname = nullptr);


	//更新主界面待开会列表数据
	void on_time_upWaitMeetingList();

	//
	void onScrollBarValueChanged(int value);
	int  onLineStatusUp();

	//
	void on_userLoginFinished();

	//系统时间获取
	void on_time_update();

	void sxrzStatus();

	void on_infraredMenu();

	void infraredMenu_quit();

	void Infrared_up();
	void Infrared_down();
	void Infrared_ok(QString objname);
	void Infrared_input_left_right(QString name, bool isLeft); //左右箭头

	void on_showDeviceBinding_slots();

	void on_showPortSetting_slots();
	void on_closePortSetting_slots();

	//其它设置窗口
	void on_showOther_slots();
	void on_closeOther_slots();

	void on_showP2pDlg_slots(); //点对点列表

	void on_showDebug_slots();
	void on_openShare_slots();
	void on_restartShare_slots();

	void doBoxPort(QString objname);

	void doBtnClick(QString objname);

	void doP2pMsg(QString Objname);

	//其它窗口
	void doOtherMsg(QString Objname);


	void showHint(QString msg, QString fontColor = "#f60", qint64 out_time = 3000);

	void on_LogOut_slots(); //注销登录

	void portStatus();

	void on_P2pMsg_close();
	void  on_P2pDlg_close();

	void mousePressEvent(QMouseEvent* event);

	//
signals:
	void to_sendCdlgTalkWork_signal();
	//void to_sendMainFrameWork_signal();
	void to_sendQmcLoginWork_signal();
	void to_sendDeviceBindWork_signal();
	void to_sendUserLoginWork_signal();

	void to_sendCdlgTalkWork_quit_signal();
	//void to_sendMainFrameWork_quit_signal();
	void to_sendQmcLoginWork_quit_signal();
	void to_sendDeviceBindWork_quit_signal();
	void to_sendUserLoginWork_quit_signal();
	void to_sendDevicePort_quit_signal();
	void to_sendNvr_quit_signal();
	void to_sendWifi_quit_signal();
	void to_sendShare_quit_signal();




public:
	bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
	//消息映射
	bool postMessageQt(MSG* message, qintptr* result);

	bool eventFilter(QObject* obj, QEvent* event);
	void closeEvent(QCloseEvent* ev);
	void tray_infrom(SessionInfo si);

	//关闭talk窗口
	void slot_closeTalk(QString idInfo);
	void delTalkerList(QString idInfo);

	void cut_talk_list(WinObjUser user);
	//初始化主界面信息
	int initCMainFrameInfo();
	int m_nContactsIndex = 0;


	//
	int exit(TCHAR* hint);



	//
	int  displayRecentFriends(MIS_MSG_displayRecentFriends_qmc* pMsg);

	//接收红外指令
	//void recvInfraredInstruct(TCHAR *instruct,qint64 port);

	//
	QY_MESSENGER_ID curr_talk_idInfo;
	//
	HWND			hWnd_curWorking;
	HWND			hWnd_infraredMenu;


	//
private:
	Ui::CMainFrame* ui;
	HWND h_cdlgTalkqt;
	//设置按钮图标文本
	void painterMenu(const QString pushBtnName);
	void updateMsgCount();
private:
	QTimer* m_pWinTimer = nullptr;
	QTimer* m_pWaitMeetingTimer = nullptr;//定时更新待开会列表
	WinTitle* m_pWinTitle = nullptr;
	WinSystemSetup* systemSetup = nullptr;

	QTimer* m_timerRestartShare = nullptr;

	bool loadInfoFinishInit = FALSE;
	QPoint                  last_point_;             //记录放大之前的位置
	QPoint                  last_position_;          //窗口上一次的位置
	bool                      left_button_pressed_ = false;   //鼠标左键按下

	int                     mouse_press_region_ = kMousePositionMid; //鼠标点击的区域

	QSystemTrayIconEx* mSysTrayIcon_ = nullptr;//托盘
	QListView* searchListView_ = mynull;
	SearchListModel* searchListMoudle_ = nullptr;

	QString _keyword;
	QScrollBar* verticalScrollBar;


	QList<SearchInfoData> _searchList;

	//
	QList<myFriendInfo> _q_grp;

	//多个会议同时开启
	QList<myFriendInfo> _q_grp_ing;

	CDlgShareDynBmps_qt* m_Share = nullptr;


public:
	CUserLogin* m_pUserLogin = nullptr; //假登录页面
public:
	CInfraredDialogMenu* m_pInfraredMenu = nullptr; //红外菜单
	CDlgPortSetting* m_pPortSetting = nullptr; //端口设置窗口弹出
	CDlgP2p* m_pP2pDlg = nullptr; //端口设置窗口弹出
	CDlgOther* m_pOther = nullptr; //其他设置窗口弹出
	CDlgP2pMsg* m_pP2pMsg = nullptr; //入会邀请弹出

	bool b_isMenuDebug = false;//调试窗

public:
	QString _instruct = nullptr; //红外指令
	int _instruct_num = 0; //指令次数
	qint64  _instruct_first_tickCnt = 0;	//  收到第一个指令的时间

	//qint64 _instruct_time = 0; //1接收指令时间


	bool _instruct_is_capsLock = false;  // 大小写切换
	//bool _instruct_is_letter = false;  //数字、字母输入法切换

	qint64 _instruct_interval_time = 1500; //按键重复间隔1.5秒

	qint64 _instruct_one_time = 0;//1接收指令时间
	qint64 _instruct_two_time = 0;//2接收指令时间
	qint64 _instruct_three_time = 0;//3接收指令时间
	qint64 _instruct_four_time = 0;//4接收指令时间
	qint64 _instruct_five_time = 0;//5接收指令时间
	qint64 _instruct_six_time = 0;//6接收指令时间
	qint64 _instruct_seven_time = 0;//7接收指令时间
	qint64 _instruct_eight_time = 0;//8接收指令时间
	qint64 _instruct_nine_time = 0;//9接收指令时间

	int _instruct_one_letter_count = 0;  //1字母按键次数
	int _instruct_two_letter_count = 0;  //2字母按键次数
	int _instruct_three_letter_count = 0;  //3字母按键次数
	int _instruct_four_letter_count = 0;  //4字母按键次数
	int _instruct_five_letter_count = 0;  //5字母按键次数
	int _instruct_sex_letter_count = 0;  //6字母按键次数
	int _instruct_seven_letter_count = 0;  //7字母按键次数
	int _instruct_eight_letter_count = 0;  //8字母按键次数
	int _instruct_nine_letter_count = 0;  //9字母按键次数

	QPointer<ShareStreamWidget> shareStreamWidget = mynull;
	int screenNum = 1;

	int _isDoTaskId = 0; //第一个会议
	int _isDoTaskId_2 = 0; //第二个会议


	QDateTime m_startTime;
	int m_failureCount = 0;

	QMenu* m_moreMenu = mynull;



	//NoticeWidget noticeWin;

	//以下为窗体移动
	/*enum CursorPos { Default, Right, Left, Bottom, Top, TopRight, TopLeft, BottomRight, BottomLeft };
	struct pressWindowsState
	{
		bool   MousePressed;
		bool   IsPressBorder;
		QPoint  MousePos;
		QPoint  WindowPos;
		QSize PressedSize;
	};

	void mouseMoveRect(const QPoint& p);

protected:
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);

	pressWindowsState m_state;
	int m_border;
	CursorPos m_curPos;*/
};



//
void mainWnd_recvInfraredInstruct(CMainFrame* pMainFrame, TCHAR* instruct, qint64 port);
void mainWnd_infraredMenu(CMainFrame* pMainFrame, QString s_status);
void mainWnd_infraredMenu_quit(CMainFrame* pMainFrame);




#endif // CMAINFRAME_H
