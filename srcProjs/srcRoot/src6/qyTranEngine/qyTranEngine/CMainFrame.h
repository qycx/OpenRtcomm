#ifndef CMAINFRAME_H
#define CMAINFRAME_H
#include "WinBasic.h"
#include <QWidget>
#include <QMouseEvent>
#include <QSettings>
#include <QAction>
#include <QtGui>
#include "qflags.h"
#include "CDlgTalk_qt.h"
#include <QDesktopWidget>
#include <QStackedWidget>
#include "qyMcMainCommon_qt.h"
#include "qyMcMainWndProc.h" 
#include "QSystemTrayIconEx.h"
#include "WinSystemSetup.h"
#include "SearchListModel.h"

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

class CMainFrame : public WinBasic
{
	Q_OBJECT


public:		
	struct {
		QY_MC_mainWndVar		common;
		//ZONE_objs_info			wall;
	}var;

	QString m_myName;

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

	void auto_do();
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

	//int  tmpHandler_printContactList_newGroup();
	int switchToContact();
	//播放声音
	static void playReciveSound(int loop=1);
	//任务栏闪烁
	static void flashTaskWindow();
	bool isMsgSel();
	int getCurIdInfo(QY_MESSENGER_ID* pIdInfo);
	void delContactList(QString idInfo);

	//
	int dbg_testFunc();
	int onLineStatus();

	void autoSet();

	void updateSearchItem(qint64 idInfo, unsigned  short status);
	//
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

private slots:
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

	//
	void onScrollBarValueChanged(int value);
	int  onLineStatusUp();

public:
	bool nativeEvent(const QByteArray& eventType, void* message, long* result);
	//消息映射
	bool postMessageQt(MSG* message, long* result);

	bool eventFilter(QObject *obj,QEvent * event);
	void closeEvent(QCloseEvent* ev);
	void tray_infrom(SessionInfo si);

	//关闭talk窗口
	void slot_closeTalk(QString idInfo);
	void delTalkerList(QString idInfo);

	void CMainFrame::cut_talk_list(WinObjUser user);
	//初始化主界面信息
	int initCMainFrameInfo();
	int m_nContactsIndex = 0;

	//
	int  displayRecentFriends(MIS_MSG_displayRecentFriends_qmc* pMsg );



private:
	Ui::CMainFrame* ui;
	//设置按钮图标文本
	void painterMenu(const QString pushBtnName);
	void updateMsgCount();
private:
	QTimer* m_pWinTimer=nullptr;
	WinTitle* m_pWinTitle=nullptr;
	WinSystemSetup* systemSetup = nullptr;
	HWND h_cdlgTalkqt;
	bool loadInfoFinishInit = FALSE;
	QPoint                  last_point_;             //记录放大之前的位置
	QPoint                  last_position_;          //窗口上一次的位置
	bool                      left_button_pressed_ = false;   //鼠标左键按下

	int                     mouse_press_region_ = kMousePositionMid; //鼠标点击的区域

	QSystemTrayIconEx* mSysTrayIcon_ = nullptr;//托盘
	QListView* searchListView_ = null;
	SearchListModel* searchListMoudle_= nullptr;
	
	QString _keyword;
	QScrollBar* verticalScrollBar;

	
	QList<SearchInfoData> _searchList;

	
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

#endif // CMAINFRAME_H
