#pragma once

#include <QDialog>

#include "CInfraredDialogMenu.h"
#include "ui_CDeviceBinding.h"
#include "noticewidget.h"
#include "cdlgportsetting.h"
//
#include	"smProc.h"
#include "CDlgDebug.h"
#include <CDlgNvrConfig.h>
#include <CDlgShareConfig.h>
#include <CDlgWifiConfig.h>
#include <CDlgCheck.h>
#include <CDlgSelectVideo.h>

//
class CDeviceBinding : public QDialog
{
	Q_OBJECT

public:
	CDeviceBinding(QWidget *parent = nullptr);
	~CDeviceBinding();
	void Infrared_down();  //下箭头
	void Infrared_up();    //上箭头

	void Infrared_ok(QString objname = nullptr);		//确认键

	void Infrared_input(QString name ,QString value); //表单输入

	void Infrared_input_leeter(QString name ,QString value , bool is_replace); //表单输入字母

	void Infrared_input_left_right(QString name , bool isLeft); //左右箭头

	void Infrared_input_backspace(QString name);

	void sheetBackgroundImage();

	void showHint(QString msg, QString fontColor = "#f60", qint64 out_time = 3000);

	//
	int  showStatus(TCHAR* str);
	
	//鼠標右鍵
	void mousePressEvent(QMouseEvent * event);


	//
	QTimer* m_pWinTimer = nullptr;

	//
	CInfraredDialogMenu* m_pInfraredMenu = nullptr;
	CDlgPortSetting* m_pPortSetting = nullptr; //端口设置窗口弹出
	CDlgNvrConfig* m_pNvrConfig = nullptr; //nvr窗口弹出
	CDlgShareConfig* m_pShareConfig = nullptr; //nvr窗口弹出
	CDlgWifiConfig* m_pWifiConfig = nullptr;
	CDlgCheck* m_pCheck = nullptr;
	CDlgSelectVideo* m_pSelectVideo = nullptr;
	QStringList _uiList;
	QString _DoUi = nullptr;
	//char _strarray[];
	
	struct {
		Sm_terminal_initCfg	initCfg;

	}  m_var;

	//
	HANDLE          m_hThread_ca = nullptr;

	bool b_isMenuDebug = false;


public slots:
	void on_timer_winMethod();
	void on_btn_clicked(QString objname = nullptr);
	void on_btnCancel_clicked(QString objname = nullptr);
	void on_btnGetTag_clicked(QString objname = nullptr);
	void infraredMenu_quit();
    void on_infraredMenu();
	void slot_checkBoxCert_change(int change);
	void slot_checkBoxCert_click(QString objname);
	void doBoxPort(QString objname);
	void doBoxNvr(QString objname);
	void on_showPortSetting_slots();
	void on_closePortSetting_slots();
	void on_showDebug_slots();
	void refResolution();
	void on_showNvr_slots();
	void on_showShare_slots();
	void on_showSelectVideo_slots();
	void on_showWifi_slots();
	void on_showCheck_slots();
	void on_showWired_slots();
	void on_closeNvr_slots();
	void on_closeCheck_slots();
	void on_closeWifi_slots();
	void on_closeShare_slots();
	void on_closeSelectVideo_slots();
public:
	Ui::CDeviceBindingClass* ui;
	
};
