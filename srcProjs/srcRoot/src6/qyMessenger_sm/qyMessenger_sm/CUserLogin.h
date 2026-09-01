#pragma once

#include <QWidget>
#include "ui_CUserLogin.h"
#include <CInfraredDialogMenu.h>

#include "WinBasic.h"
#include "noticewidget.h"
#include "CDlgDebug.h"
//
#include	"DlgMcClientLogon.h"



//
class CUserLogin : public QWidget
{
	Q_OBJECT

public:
	CUserLogin(QWidget *parent = nullptr);
	~CUserLogin();

	//
	DLG_mcClientLogon_var  m_var;



	//
	//HANDLE          m_hThread_ca = nullptr;

	//
	bool			is_ukey_login = false;

	//
	QTimer* m_pWinTimer=nullptr;
	QTimer* m_pWinRzStatusTimer=nullptr;

	//
	CInfraredDialogMenu* m_pInfraredMenu = nullptr;
	//
	bool b_isMenuDebug = false;

	QString s_keyStatus = "";
	//
	int  showStatus(TCHAR* str, int iRc_fromHg , TCHAR* tRcDesc_fromHg);

	//
	void Infrared_down();  //下箭头
	void Infrared_up();    //上箭头
	void Infrared_input_left_right(QString name, bool isLeft);
	//
	void sheetBackgroundImage();

	//
	void Infrared_input(QString name, QString value);
	void Infrared_input_leeter(QString name, QString value, bool is_replace);

	//
	void Infrared_input_backspace(QString name);

	void Infrared_ok(QString objname);
	//
	QString doUserStatusText(int iRc_fromHg , TCHAR* tRcDesc_fromHg);

	void showHint(QString msg, QString fontColor = "#f60", qint64 out_time = 3000);

	//
	void showUkeyStatus(bool isIn);

signals:
	void to_userLoginFinished_signal();

private slots:
	void on_timer_winMethod();
	void on_infraredMenu();
	void infraredMenu_quit();
	void on_showDeviceBinding_slots();
	bool eventFilter(QObject*, QEvent*);

	void on_showDebug_slots();

	void refResolution();
	

public slots:
	void on_loginUserBtn_clicked(QString objname = nullptr);

	void sxrzStatus();

private:
	//CMainFrame* m_pCMain = nullptr;
	Ui::CUserLoginClass* ui;
	//NoticeWidget noticeWin;
};
