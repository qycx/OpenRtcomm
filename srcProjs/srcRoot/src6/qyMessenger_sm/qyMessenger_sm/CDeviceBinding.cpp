
#include	<tchar.h>

#define  __noDbg_new__

#include	"tmpDefs_open.h"
#include "CDeviceBinding.h"
#include <qdebug.h>
#include<QTextCursor>
#include "CMainFrame.h"

#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc_sm.h"

//#include <QDesktopWidget>
#include	<qscreen.h>

#include <QSettings>
#include "tmpRegFunc_open.h"
#include "myCmdParams_open.h"
#include "..\include\ctxQmc_sm.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include <qmcShareIc.h>

//
//
int disableCa(bool  bDisableCa)
{
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)QY_GET_procInfo_isCli();

	//
	pProcInfo->m_var.ctxSm.ca_dev.toolCa.m_bDisableCa = bDisableCa;
	pProcInfo->m_var.ctxSm.ca_usr.toolCa.m_bDisableCa = bDisableCa;


	//
	return  0;
}


bool  bCaDisabled()
{
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)QY_GET_procInfo_isCli();

	return  pProcInfo->m_var.ctxSm.ca_usr.toolCa.m_bDisableCa;


}

bool  bUseWireless(TCHAR* smCfgFile)
{
	bool  bRet = false;

	//
	CCtxQyMc* pQyMc = g_pQyMc;


	TCHAR  cfgVal[128] = { '\0' };

	//USB Video Device
	getCfgValByNameT(smCfgFile, (TCHAR*)CONST_cfgName_useWireless, cfgVal, mycountof(cfgVal));
	tTrim(cfgVal);
	int  tmpiRet = _ttol(cfgVal);

	bRet = tmpiRet;

	//	 
	return  bRet;

}

bool  bUseSelectVideo(TCHAR* smCfgFile)
{
	bool  bRet = false;

	//
	CCtxQyMc* pQyMc = g_pQyMc;


	TCHAR  cfgVal[128] = { '\0' };

	//USB Video Device
	getCfgValByNameT(smCfgFile, (TCHAR*)CONST_cfgName_useSelectVideo, cfgVal, mycountof(cfgVal));
	tTrim(cfgVal);
	int  tmpiRet = _ttol(cfgVal);

	bRet = tmpiRet;

	//	 
	return  bRet;

}

bool  bUseShare(TCHAR* smCfgFile)
{
	bool  bRet = false;

	//
	CCtxQyMc* pQyMc = g_pQyMc;


	TCHAR  cfgVal[128] = {'\0'};

	//USB Video Device
	getCfgValByNameT(smCfgFile, (TCHAR*)CONST_cfgName_useShare, cfgVal, mycountof(cfgVal));
	tTrim(cfgVal);
	int  tmpiRet = _ttol(cfgVal);

	bRet = tmpiRet;

	//	 
	return  bRet;

}

//
CDeviceBinding::CDeviceBinding(QWidget *parent)
	: QDialog(parent)
	,m_pWifiConfig(nullptr)
	,ui(new Ui::CDeviceBindingClass)
{
	ui->setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint);

	//
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

	Sm_terminal_initCfg  initCfg;
	memset(&initCfg, 0, sizeof(initCfg));
	
	HWND  hMainWnd = pQyMc->gui.hMainWnd;
	CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);

	connect(pMainWnd, SIGNAL(to_sendDeviceBindWork_signal()), this, SLOT(on_infraredMenu()));
	connect(pMainWnd, SIGNAL(to_sendDeviceBindWork_quit_signal()), this, SLOT(infraredMenu_quit()));
	connect(pMainWnd, SIGNAL(to_sendDevicePort_quit_signal()), this, SLOT(on_closePortSetting_slots()));
	connect(pMainWnd, SIGNAL(to_sendNvr_quit_signal()), this, SLOT(on_closeNvr_slots()));
	connect(pMainWnd, SIGNAL(to_sendShare_quit_signal()), this, SLOT(on_closeShare_slots()));
	connect(pMainWnd, SIGNAL(to_sendWifi_quit_signal()), this, SLOT(on_closeWifi_slots()));

	//connect(pMainWnd, SIGNAL(to_showPortSetting_signal()), this, SLOT(on_showPortSetting_slots()));
	
	//ui->btnCancel->setVisible(false);

	//nvr按钮点击事件
	connect(ui->btn_nvr, SIGNAL(clicked()), this, SLOT(on_showNvr_slots()));
	connect(ui->pushButton_wireless, SIGNAL(clicked()), this, SLOT(on_showWifi_slots()));
	connect(ui->pushButton_check, SIGNAL(clicked()), this, SLOT(on_showCheck_slots()));
	connect(ui->pushButton_share, SIGNAL(clicked()), this, SLOT(on_showShare_slots()));
	connect(ui->pushButton_selectVideo, SIGNAL(clicked()), this, SLOT(on_showSelectVideo_slots()));

	QCursor::setPos(0, 0);

	//QDesktopWidget* desktopwidget = QApplication::desktop();
	/*QScreen* desktopwidget = QApplication::primaryScreen();

	connect(desktopwidget, SIGNAL(resized(int)), this, SLOT(refResolution()));*/
	QScreen* pScreen; pScreen = QApplication::primaryScreen();

	connect(pScreen, &QScreen::geometryChanged, this, &CDeviceBinding::refResolution);


	if (bUseWireless(pQyMc->cfg.smCfgFile)) {
		ui->widget_yt_wireless->setVisible(true);
	}
	else {
		ui->widget_yt_wireless->setVisible(false);
	}

	if (bUseShare(pQyMc->cfg.smCfgFile)) {
		ui->widget_yt_share->setVisible(true);
	}
	else {
		ui->widget_yt_share->setVisible(false);
	}	

	if (bUseSelectVideo(pQyMc->cfg.smCfgFile)) {
		ui->widget_yt_selectVideo->setVisible(true);
	}
	else {
		ui->widget_yt_selectVideo->setVisible(false);
	}

	//
	memset(&m_var, 0, sizeof(m_var));
	
	//
	bGetSmTerminalInitCfg(pQyMc->cfg.tmInitFile, &m_var.initCfg);


	//connect(ui->checkBox_cert, SIGNAL(clicked(bool)), this, SLOT(slot_checkBoxCert_click(QString)));
	//connect(ui->checkBox_cert, SIGNAL(stateChanged(int)), this, SLOT(slot_checkBoxCert_change(int)));
	//
	sheetBackgroundImage();
	//
	//if (false) {
	if (!pProcInfo->m_var.b_app_showNormal) {
		//
	//	this->showMaximized();
		QRect rc = QApplication::primaryScreen()->geometry();
		
		this->setMaximumSize(rc.width(), rc.height());
		this->setMinimumSize(rc.width(), rc.height());
	}
	else {

		//尺寸
		//ui->label_t1->setFixedWidth(120);
		this->setMaximumSize(1200,800);
		this->setMinimumSize(1200,800);
		ui->label_t2->setFixedWidth(140);
		ui->label_t3->setFixedWidth(140);
		ui->label_t4->setFixedWidth(140);
		ui->label_t5->setFixedWidth(140);
		ui->label_t6->setFixedWidth(140);
		ui->label_t7->setFixedWidth(140);
		ui->label_t8->setFixedWidth(140);
		ui->label_t9->setFixedWidth(140);
		//ui->label_t10->setFixedWidth(140);
		//ui->terminal_title->setFixedHeight(80);
		ui->terminal_ip->setFixedHeight(30);
		ui->terminal_mask->setFixedHeight(30);
		ui->terminal_gateway->setFixedHeight(30);
		ui->terminal_mcu->setFixedHeight(30);
		ui->terminal_dns->setFixedHeight(30);
		ui->terminal_sqm->setFixedHeight(30);
		ui->btn->setFixedHeight(30);
		ui->btn->setFixedWidth(230);
		ui->btnCancel->setFixedHeight(30);
		ui->btnCancel->setFixedWidth(230);
		//ui->btnGetTag->setFixedSize(30,280);
		
		//
		int iW = 550;
		ui->terminal_ip->setFixedWidth(iW);
		ui->terminal_mask->setFixedWidth(iW);
		ui->terminal_gateway->setFixedWidth(iW);
		ui->terminal_mcu->setFixedWidth(iW);
		ui->terminal_mcu2->setFixedWidth(iW);
		ui->terminal_dns->setFixedWidth(iW);
		ui->terminal_sqm->setFixedWidth(iW);

		//ui->btnGetTag->setFixedWidth(200);
		//ui->btnGetTag->setFixedHeight(50);

		//
	}


	//
	// 
	//initCfg.authType = m_var.initCfg.authType;
	//safeTcsnCpy(m_var.initCfg.fake_talkerDesc, initCfg.fake_talkerDesc, mycountof(initCfg.fake_talkerDesc));
	//safeTcsnCpy(m_var.initCfg.fake_devLoginName, initCfg.fake_devLoginName, mycountof(initCfg.fake_devLoginName));
	//safeStrnCpy(m_var.initCfg.fake_devLoginPasswd, initCfg.fake_devLoginPasswd, mycountof(initCfg.fake_devLoginPasswd));
	//



	ui->terminal_username->setText(QString::fromWCharArray(m_var.initCfg.fake_devLoginName));
	ui->terminal_pwd->setText(QString::fromUtf8((const char*)m_var.initCfg.fake_devLoginPasswd));
	ui->terminal_ip->setText(QString::fromUtf8((const char*)m_var.initCfg.terminal_ip));
	ui->terminal_mask->setText(QString::fromUtf8((const char*)m_var.initCfg.terminal_mask));
	ui->terminal_gateway->setText(QString::fromUtf8((const char*)m_var.initCfg.terminal_gateway));
	ui->terminal_dns->setText(QString::fromUtf8((const char*)m_var.initCfg.terminal_dns));
	ui->terminal_mcu->setText(QString::fromUtf8((const char*)m_var.initCfg.terminal_mcu));
	ui->terminal_mcu2->setText(QString::fromUtf8((const char*)m_var.initCfg.terminal_mcu2));
	ui->terminal_sqm->setText(QString::fromUtf8((const char*)m_var.initCfg.terminal_sqm));

	

	ui->lab_err->setVisible(false);

	
	//
	m_pWinTimer = new QTimer(this);
	connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(on_timer_winMethod()));
	m_pWinTimer->setInterval(100);
	m_pWinTimer->start();

	//设置true  sm项目   false 零信任项目

	
		
		//隐藏注册码这栏
		ui->widget_sm->setVisible(false);

		//显示其它设置
		ui->widget_yt->setVisible(true);

		//显示登录名、密码
		ui->widget_11->setVisible(true);
		ui->widget_12->setVisible(true);
	

	//只有sm版才要这个注册码显示
	if(qyGetCustomId() == CONST_qyCustomId_business)
	{
		//显示注册码这栏
		ui->widget_sm->setVisible(true);
		//隐藏其它设置
		ui->widget_yt->setVisible(false);
	
		//隐藏登录名、密码
		ui->widget_11->setVisible(false);
		ui->widget_12->setVisible(false);

	}
	

}

//显示提示窗
void CDeviceBinding::showHint(QString msg, QString fontColor, qint64 out_time) {

	NoticeWidget::showNotice(this, msg, fontColor, out_time);

}

void CDeviceBinding::sheetBackgroundImage()
{
	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		ui->widget->setStyleSheet("QWidget#widget{background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)}");
		ui->label_title->setStyleSheet("font-size:84px;font-weight:bold;color:#2C9AD0;font-family: Microsoft YaHei;");
		//ui->label_t1->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_net->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_share->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_selectVideo->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		//ui->label_check->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->pushButton_wireless->setStyleSheet("QPushButton{font-size:48px;color:#fff;background:#8dacf6;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->pushButton_share->setStyleSheet("QPushButton{font-size:48px;color:#fff;background:#8dacf6;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->pushButton_selectVideo->setStyleSheet("QPushButton{font-size:48px;color:#fff;background:#8dacf6;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->pushButton_check->setStyleSheet("QPushButton{font-size:48px;color:#fff;background:#8dacf6;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->label_t2->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t3->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t4->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t5->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t6->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t8->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t9->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t20->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t21->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t22->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		//ui->label_t10->setStyleSheet("font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		//ui->btn->setStyleSheet("font-size:48px;color:#fff;background:#2C9AD0;font-family: Microsoft YaHei;border-radius:10px");
		//ui->btn->setStyleSheet("QPushButton{font-size:48px;color:#fff;background:#404041;font-family: Microsoft YaHei;border-radius:10px}QPushButton:hover{font-family: Microsoft YaHei;background:#2C9AD0;color:#fff}QPushButton:focus {font-family: Microsoft YaHei;background:#2C9AD0;color:#fff}");
		ui->btn->setStyleSheet("QPushButton{font-size:48px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->btnCancel->setStyleSheet("QPushButton{font-size:48px;color:#fff;background:#8dacf6;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->btn_nvr->setStyleSheet("QPushButton{font-size:48px;color:#fff;background:#8dacf6;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		
		//ui->btnGetTag->setStyleSheet("QPushButton{font-size:48px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		//ui->terminal_title->setStyleSheet("background:#030F1B;border:2px solid #2D9BD1;color:#fff;font-size:48px;border-radius:10px");
		/*ui->terminal_ip->setStyleSheet("QLineEdit{padding-left:30px;font-family: Microsoft YaHei;background:#192036;border:2px solid #2D9BD1;color:#fff;font-size:48px;border-radius:10px;}QLineEdit:focus{background:#192036;color:#fff;font-size:48px;border-radius:10px;}");
		ui->terminal_mcu->setStyleSheet("QLineEdit{padding-left:30px;font-family: Microsoft YaHei;background:#192036;border:2px solid #2D9BD1;color:#fff;font-size:48px;border-radius:10px;}QLineEdit:focus{background:#192036;color:#fff;font-size:48px;border-radius:10px;}");
		ui->terminal_gateway->setStyleSheet("QLineEdit{padding-left:30px;font-family: Microsoft YaHei;background:#192036;border:2px solid #2D9BD1;color:#fff;font-size:48px;border-radius:10px;}QLineEdit:focus{background:#192036;color:#fff;font-size:48px;border-radius:10px;}");
		ui->terminal_mask->setStyleSheet("QLineEdit{padding-left:30px;font-family: Microsoft YaHei;background:#192036;border:2px solid #2D9BD1;color:#fff;font-size:48px;border-radius:10px;}QLineEdit:focus{background:#192036;color:#fff;font-size:48px;border-radius:10px;}");
		ui->terminal_id->setStyleSheet("QLineEdit{padding-left:30px;font-family: Microsoft YaHei;background:#192036;border:2px solid #2D9BD1;color:#fff;font-size:48px;border-radius:10px;}QLineEdit:focus{background:#192036;color:#fff;font-size:48px;border-radius:10px;}");*/
		//ui->checkBox_cert->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->terminal_username->setStyleSheet("QLineEdit{padding-left:30px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:48px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_pwd->setStyleSheet("QLineEdit{padding-left:30px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:48px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_ip->setStyleSheet("QLineEdit{padding-left:30px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:48px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_dns->setStyleSheet("QLineEdit{padding-left:30px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:48px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_mcu->setStyleSheet("QLineEdit{padding-left:30px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:48px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_mcu2->setStyleSheet("QLineEdit{padding-left:30px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:48px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_gateway->setStyleSheet("QLineEdit{padding-left:30px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:48px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_mask->setStyleSheet("QLineEdit{padding-left:30px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:48px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_sqm->setStyleSheet("QLineEdit{padding-left:30px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:48px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		
		ui->lab_err->setStyleSheet("font-size:48px;color:red;font-weight:bold;");
		ui->btnCancel->setFixedSize(500,134);

	}
	else {
		ui->widget->setStyleSheet("QWidget#widget{background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)}");
		ui->label_title->setStyleSheet("border-bottom:5px solid  #fff;font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		//ui->label_t1->setStyleSheet("font-size:24px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_net->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");	
		ui->label_share->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_selectVideo->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		//ui->label_check->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->pushButton_wireless->setStyleSheet("QPushButton{font-size:32px;color:#fff;background:#8dacf6;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->pushButton_share->setStyleSheet("QPushButton{font-size:32px;color:#fff;background:#8dacf6;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->pushButton_selectVideo->setStyleSheet("QPushButton{font-size:32px;color:#fff;background:#8dacf6;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->pushButton_check->setStyleSheet("QPushButton{font-size:32px;color:#fff;background:#8dacf6;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->label_t2->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t3->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t4->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t5->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t6->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t8->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t9->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t20->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t21->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t22->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		//ui->label_t10->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");

		//ui->only_tag->setStyleSheet("font-size:26px;color:#fff;font-family: Microsoft YaHei;font-weight:bold");

		//ui->checkBox_cert->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		
		//ui->btnGetTag->setStyleSheet("QPushButton{font-size:24px;color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		
		ui->btn->setStyleSheet("QPushButton{font-size:32px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->btnCancel->setStyleSheet("QPushButton{font-size:32px;color:#fff;background:#8dacf6;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->btn_nvr->setStyleSheet("QPushButton{font-size:32px;color:#fff;background:#8dacf6;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");


		//ui->terminal_title->setStyleSheet("background:#030F1B;border:1px solid #2D9BD1;color:#fff;font-size:24px;border-radius:10px;font-family: Microsoft YaHei;");
		/*ui->terminal_ip->setStyleSheet("background:#192036;color:#fff;font-size:24px;border-radius:10px;font-family: Microsoft YaHei;");
		ui->terminal_mcu->setStyleSheet("background:#192036;color:#fff;font-size:24px;border-radius:10px;font-family: Microsoft YaHei;");
		ui->terminal_gateway->setStyleSheet("background:#192036;color:#fff;font-size:24px;border-radius:10px;font-family: Microsoft YaHei;");
		ui->terminal_mask->setStyleSheet("background:#192036;color:#fff;font-size:24px;border-radius:10px;font-family: Microsoft YaHei;");*/
		
		ui->terminal_username->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_pwd->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_ip->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_dns->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_mcu->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_mcu2->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_gateway->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_mask->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->terminal_sqm->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->lab_err->setStyleSheet("font-size:28px;color:red;font-weight:bold;");

		//尺寸
		//ui->label_t1->setFixedWidth(120);
		ui->label_t2->setFixedWidth(140);
		ui->label_t3->setFixedWidth(140);
		ui->label_t4->setFixedWidth(140);
		ui->label_t5->setFixedWidth(140);
		ui->label_t6->setFixedWidth(140);
		ui->label_t7->setFixedWidth(140);
		ui->label_t8->setFixedWidth(140);
		ui->label_t9->setFixedWidth(140);
		ui->label_t20->setFixedWidth(140);
		ui->label_t21->setFixedWidth(140);
		ui->label_t22->setFixedWidth(140);
		ui->label_net->setFixedWidth(140);
		ui->label_share->setFixedWidth(140);
		ui->label_selectVideo->setFixedWidth(140);
		
		ui->pushButton_wireless->setFixedHeight(60);
		ui->pushButton_share->setFixedHeight(60);
		ui->pushButton_selectVideo->setFixedHeight(60);
		ui->pushButton_check->setFixedHeight(60);
		//ui->pushButton_wireless->setFixedHeight(32);
		//ui->label_t10->setFixedWidth(140);
		int iW = 70;
		//ui->terminal_title->setFixedHeight(80);
		ui->terminal_username->setFixedHeight(iW);
		ui->terminal_pwd->setFixedHeight(iW);
		ui->terminal_ip->setFixedHeight(iW);
		ui->terminal_gateway->setFixedHeight(iW);
		ui->terminal_dns->setFixedHeight(iW);
		ui->terminal_mcu->setFixedHeight(iW);
		ui->terminal_mcu2->setFixedHeight(iW);
		ui->terminal_mask->setFixedHeight(iW);
		ui->terminal_sqm->setFixedHeight(iW);
		//
		ui->btn_nvr->setFixedHeight(60);
		ui->btn->setFixedHeight(60);
		ui->btn->setFixedWidth(230);
		ui->btnCancel->setFixedHeight(60);
		ui->btnCancel->setFixedWidth(230);

		
		//ui->btnGetTag->setFixedSize(200,50);
		
		ui->widget->setContentsMargins(0,50,0,20);
	}

}

//遥控器按下 勾选
void CDeviceBinding::slot_checkBoxCert_click(QString objname)
{

	
}

//监听复选框选中状态
void CDeviceBinding::slot_checkBoxCert_change(int box_change)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

	if ( box_change == 0) 
	{
		//未选
		int aa = 1;
		pProcInfo->m_var.ctxSm.ca_dev.toolCa.m_bDisableCa = true;
		pProcInfo->m_var.ctxSm.ca_usr.toolCa.m_bDisableCa = true;

	}
	else if ( box_change == 2 ) 
	{
		//已选
		int aaa = 1;
		pProcInfo->m_var.ctxSm.ca_dev.toolCa.m_bDisableCa = false;
		pProcInfo->m_var.ctxSm.ca_usr.toolCa.m_bDisableCa = false;
	}
}

//
void CDeviceBinding::mousePressEvent(QMouseEvent * event) 
{
	if (event->button() == Qt::RightButton)
	{
		//
		if (!m_pInfraredMenu)
		{
			m_pInfraredMenu = new CInfraredDialogMenu(this, "CdeviceBind");
		}

		//
	//	if  (  m_pInfraredMenu->winId()  !=  pQyMc)

		//
		if (!m_pInfraredMenu->isVisible())
		{
			//窗口只打开一次

			m_pInfraredMenu->show();

			//判断状态栏
			if (b_isMenuDebug)
			{
				m_pInfraredMenu->ui->menuDebug->setText(u8"关闭调试窗");
			}
			else {
				m_pInfraredMenu->ui->menuDebug->setText(u8"打开调试窗");
			}

			return;

		}
		else {
			m_pInfraredMenu->close();
			if (m_pInfraredMenu)
			{
				delete m_pInfraredMenu;
				m_pInfraredMenu = nullptr;
			}
		}
	}
	

}

//刷新分辨率
void CDeviceBinding::refResolution()
{

	sheetBackgroundImage();
}

CDeviceBinding::~CDeviceBinding()
{
	if (this->m_pWinTimer) {
		delete this->m_pWinTimer;
		this->m_pWinTimer = nullptr;
	}
	//
	if (this->m_pPortSetting)
	{
		delete  this->m_pPortSetting;
		this->m_pPortSetting = nullptr;
	}	
	//
	if (this->m_pNvrConfig)
	{
		delete  this->m_pNvrConfig;
		this->m_pNvrConfig = nullptr;
	}

	if (this->m_pWifiConfig)
	{
		delete  this->m_pWifiConfig;
		this->m_pWifiConfig = nullptr;
	}

	if (this->m_pCheck)
	{
		delete  this->m_pCheck;
		this->m_pCheck = nullptr;
	}

	if (this->m_pShareConfig)
	{
		delete  this->m_pShareConfig;
		this->m_pShareConfig = nullptr;
	}

	if (this->m_pSelectVideo)
	{
		delete  this->m_pSelectVideo;
		this->m_pSelectVideo = nullptr;
	}
	//
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	Var_ca_dev_qmc* pVc = &pProcInfo->m_var.ctxSm.ca_dev;
	//
	if (m_hThread_ca) {
		pVc->toolCa.bNeedQuit = true;
		//
		waitForObject(&m_hThread_ca, INFINITE);
	}


}


//
	//
int  CDeviceBinding::showStatus(TCHAR* str)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	Var_ca_dev_qmc* pVc = &pProcInfo->m_var.ctxSm.ca_dev;

	if (!str)str = (TCHAR*)_T("");

	if (!pVc->dev.bStart_toGetUsrName)  return  0;

	//
	//ui->only_tag->setText(QString::fromStdWString(str));
	//ui->only_tag->setStyleSheet("font-size:26px;color:#fff;font-family: Microsoft YaHei;font-weight:bold");


	return  0;
}



void CDeviceBinding::on_timer_winMethod()
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	Var_ca_dev_qmc* pVc = &pProcInfo->m_var.ctxSm.ca_dev;

	//
	//
	showStatus(pVc->tStatusBuf);

	//检测分辨率变化
	sheetBackgroundImage();

	//
	uint curTickCnt = myGetTickCount(nullptr);

	//
	waitForObject(&m_hThread_ca, 0);

	//
	if (!m_hThread_ca) {
		if (pVc->dev.bStart_toGetUsrName) {
			if (!pVc->dev.bGot_ca_usrName) {
				safeTcsnCpy(_T("获取设备注册码失败"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
			}
			else {
				 //
				safeTcsnCpy(pVc->dev.tUsrName, pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
			}
			showStatus(pVc->tStatusBuf);
			pVc->dev.bStart_toGetUsrName = false;
		}
	}



	return;
}


//红外菜单
void CDeviceBinding::on_infraredMenu() 
{

	//
	if (!m_pInfraredMenu)
	{
		m_pInfraredMenu = new CInfraredDialogMenu(this, "CdeviceBind");
	}

	//
//	if  (  m_pInfraredMenu->winId()  !=  pQyMc)

	//
	if (!m_pInfraredMenu->isVisible()) 
	{
		//窗口只打开一次

		m_pInfraredMenu->show();

		//判断状态栏
		if (b_isMenuDebug)
		{
			m_pInfraredMenu->ui->menuDebug->setText(u8"关闭调试窗");
		}
		else {
			m_pInfraredMenu->ui->menuDebug->setText(u8"打开调试窗");
		}

		return;
		
	}
}

//菜单关闭
void CDeviceBinding::infraredMenu_quit() 
{
	if (!m_pInfraredMenu)
	{
		return;
	}

	//if (m_pInfraredMenu->isVisible()) 
	{

		m_pInfraredMenu->close();
		if (m_pInfraredMenu)
		{
			delete m_pInfraredMenu;
			m_pInfraredMenu = nullptr;
		}

	}
	if (!m_pPortSetting) {
	//	ui->btnMeeting->setFocus();
	}
	else 
	{
		m_pPortSetting->activateWindow();
		m_pPortSetting->ui->boxVga->setFocus();
	}

	return;

}


//显示端口设置窗口
void CDeviceBinding::on_showPortSetting_slots()
{
	//
	if (!m_pPortSetting)
	{
		m_pPortSetting = new CDlgPortSetting(this);

	}

	//
	if (!m_pPortSetting->isVisible()) {

		//窗口只打开一次
		m_pPortSetting->show();




	}
	else {


		on_closePortSetting_slots();
	}

	//
	infraredMenu_quit();
}

//关闭端口设置窗口
void CDeviceBinding::on_closePortSetting_slots()
{
	if (!m_pPortSetting)
	{
		return;
	}

	{
		m_pPortSetting->close();
		if (m_pPortSetting)
		{
			delete m_pPortSetting;
			m_pPortSetting = nullptr;
		}

	}

	return;
}


//显示调试窗
void CDeviceBinding::on_showDebug_slots() {
	//
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)QY_GET_procInfo_isCli();

	if (!IsWindow(pProcInfo->m_var.hWnd_dbg)) {
		viewDlgDbg((HWND)this->winId());
		b_isMenuDebug = true;
	}
	else {
		closeDlgDbg();
		b_isMenuDebug = false;
	}

	infraredMenu_quit();

}


//显示nvr窗口
void CDeviceBinding::on_showNvr_slots() {
	//
	if (!m_pNvrConfig)
	{
		m_pNvrConfig = new CDlgNvrConfig(this);

	}

	//
	if (!m_pNvrConfig->isVisible()) {

		//窗口只打开一次
		m_pNvrConfig->show();

	}
	else {


		on_closePortSetting_slots();
	}

	//
	infraredMenu_quit();
}

void CDeviceBinding::on_showShare_slots() {
	//
	if (!m_pShareConfig)
	{
		m_pShareConfig = new CDlgShareConfig(this);

	}

	//
	if (!m_pShareConfig->isVisible()) {

		//窗口只打开一次
		m_pShareConfig->show();

	}
	else {


		
	}

	//
	infraredMenu_quit();
}

void CDeviceBinding::on_showSelectVideo_slots() {
	//
	if (!m_pSelectVideo)
	{
		m_pSelectVideo = new CDlgSelectVideo(this);

	}

	//
	if (!m_pSelectVideo->isVisible()) {

		//窗口只打开一次
		m_pSelectVideo->show();

	}
	else {



	}

	//
	infraredMenu_quit();
}

void CDeviceBinding::on_showCheck_slots() {
	if (!m_pCheck)
	{
		
		m_pCheck = new CDlgCheck(ui->terminal_ip->text().toStdString(), ui->terminal_mcu->text().toStdString(), this);

	}
	
	if (!m_pCheck->isVisible()) {

		//窗口只打开一次
		m_pCheck->show();

	}

	infraredMenu_quit();
}

void CDeviceBinding::on_showWifi_slots() {
	//
	if (!m_pWifiConfig)
	{
		m_pWifiConfig = new CDlgWifiConfig(this);

	}

	if (!m_pWifiConfig->isVisible()) {

		//窗口只打开一次
		m_pWifiConfig->show();

	}

	//ui->radioButton_wired->setStyleSheet("QRadioButton::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
	//ui->radioButton_wireless->setStyleSheet("QRadioButton::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

	//ui->radioButton_wireless->setChecked(true);

	//ui->terminal_ip->setEnabled(false);
	//ui->terminal_mask->setEnabled(false);
	//ui->terminal_gateway->setEnabled(false);

}

void CDeviceBinding::on_showWired_slots() {

	//ui->radioButton_wired->setStyleSheet("QRadioButton::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
	//ui->radioButton_wireless->setStyleSheet("QRadioButton::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

	//ui->radioButton_wired->setChecked(true);

	ui->terminal_ip->setEnabled(true);
	ui->terminal_mask->setEnabled(true);
	ui->terminal_gateway->setEnabled(true);
}

//关闭nvr窗口
void CDeviceBinding::on_closeNvr_slots()
{
	if (!m_pNvrConfig)
	{
		return;
	}

	{
		m_pNvrConfig->close();
		if (m_pNvrConfig)
		{
			delete m_pNvrConfig;
			m_pNvrConfig = nullptr;
		}

	}

	return;
}

void CDeviceBinding::on_closeCheck_slots()
{
	if (!m_pCheck)
	{
		return;
	}

	{
		m_pCheck->close();
		if (m_pCheck)
		{
			delete m_pCheck;
			m_pCheck = nullptr;
		}

	}

	return;
}

void CDeviceBinding::on_closeWifi_slots()
{
	if (!m_pWifiConfig)
	{
		return;
	}

	{
		m_pWifiConfig->close();
		if (m_pWifiConfig)
		{
			delete m_pWifiConfig;
			m_pWifiConfig = nullptr;
		}

	}

	return;
}

void CDeviceBinding::on_closeShare_slots()
{
	if (!m_pShareConfig)
	{
		return;
	}

	{
		m_pShareConfig->close();
		if (m_pShareConfig)
		{
			delete m_pShareConfig;
			m_pShareConfig = nullptr;
		}

	}

	return;
}


void CDeviceBinding::on_closeSelectVideo_slots()
{
	if (!m_pSelectVideo)
	{
		return;
	}

	{
		m_pSelectVideo->close();
		if (m_pSelectVideo)
		{
			delete m_pSelectVideo;
			m_pSelectVideo = nullptr;
		}

	}

	return;
}


//端口开关遥控器控制
void CDeviceBinding::doBoxPort(QString objname) {
	if (m_pPortSetting) {

		if (objname == "boxVga")
		{
			m_pPortSetting->slot_boxVga_click(objname);
		}
		else if (objname == "boxHdmi")
		{
			m_pPortSetting->slot_boxHdmi_click(objname);
		}
		else if (objname == "boxDvi")
		{
			m_pPortSetting->slot_boxDvi_click(objname);
		}
		else if (objname == "boxUsb1")
		{
			m_pPortSetting->slot_boxUsb1_click(objname);
		}
		else if (objname == "boxUsb2")
		{
			m_pPortSetting->slot_boxUsb2_click(objname);
		}
		else if (objname == "boxAudioOut")
		{
			m_pPortSetting->slot_boxAudioOut_click(objname);
		}
		else if (objname == "boxUsb3")
		{
			m_pPortSetting->slot_boxUsb3_click(objname);
		}
		else if (objname == "boxLan")
		{
			m_pPortSetting->slot_boxLan_click(objname);
		}

	}
}

extern bool compareSpecalObjName(const QString& objName);
//nvr开关遥控控制 
void CDeviceBinding::doBoxNvr(QString objname) {
	if (m_pNvrConfig) {

		if (objname == "boxNvrEna")
		{
			m_pNvrConfig->slot_boxNvrEna_click(objname);
		}
		else if (objname == "boxNvrDh")
		{
			m_pNvrConfig->slot_boxNvrDh_click(objname);
		}
		else if (objname == "boxNvrHik")
		{
			m_pNvrConfig->slot_boxNvrHik_click(objname);
		}
		else if (objname == "boxNvrD4k")
		{
			m_pNvrConfig->slot_boxNvrD4k_click(objname);
		}
		else if (objname == "btnOk")
		{
			m_pNvrConfig->slot_btnOk_click();
		}

	}
	else if (m_pWifiConfig) {
		if (objname == "pushButton_detect")
		{
			m_pWifiConfig->slot_pushButton_detect_click();
		}
		else if (objname == "pushButton_conn")
		{
			m_pWifiConfig->slot_pushButton_conn_click();
		}
		else if (objname == "treeWidget_wifi")
		{
			m_pWifiConfig->slot_wifi_enter();
		}	
		else if (objname == "btnOk")
		{
			m_pWifiConfig->slot_btnOk_click();
		}
	}
	else if (m_pShareConfig) {

		if (objname == "boxNvrEna")
		{
			m_pShareConfig->slot_boxEnableShare_click(objname);
		}
		else if (objname == "boxAutoShare")
		{
			m_pShareConfig->slot_boxAutoShare_click(objname);
		}		
		else if (objname == "btnOk")
		{
			m_pShareConfig->slot_btnOk_click();
		}

	}
	else if (m_pSelectVideo) {

		if (objname == "boxNvrEna")
		{
			m_pSelectVideo->slot_boxEnableShare_click(objname);
		}
		else if (objname == "boxRtsp")
		{
			m_pSelectVideo->slot_boxRtsp_click(objname);
		}
		else if (objname == "btnOk")
		{
			m_pSelectVideo->slot_btnOk_click();
		}
		else if (compareSpecalObjName(objname)) {
			m_pSelectVideo->slot_checkBox_click(objname);
		}

	}
	else if (m_pCheck) {
		if (objname == "btnOk")
		{
			m_pCheck->slot_btnOk_click();
		}
	}
}


//
DWORD  tmpThreadProc_dev_ca_getUsrName(LPVOID pParam)
{
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("tmpThreadProc_ca_dev_getUsrName enters"));
#endif

	//
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	Var_ca_dev_qmc* pVc = &pProcInfo->m_var.ctxSm.ca_dev;
	TCHAR	tBuf[128];

	//
	DWORD  dwTickCnt_start = myGetTickCount(mynull);

	//
	pVc->toolCa.tn_process_ca = getuiNextTranNo(nullptr, 0, &pProcInfo->m_var.ctxSm.tn0_ca);

	//
	bool  bSys = false;
	bool  bDev = true;// false;
	HKEY  hKeyRoot0 = HKEY_CURRENT_USER;
	//
	TCHAR  cfgName_req[128];
	_sntprintf(cfgName_req, mycountof(cfgName_req), _T("%s%d"), _T(CONST_regValName_ca_sendData_prefix), pVc->toolCa.tn_process_ca);

	TCHAR  cfgName_resp[128];
	_sntprintf(cfgName_resp, mycountof(cfgName_resp), _T("%s%d"), _T(CONST_regValName_ca_sendDataResp_prefix), pVc->toolCa.tn_process_ca);
	qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp);

	TCHAR  cfgName_resp_chkUsrKey[128];
	_sntprintf(cfgName_resp_chkUsrKey, mycountof(cfgName_resp_chkUsrKey), _T("%s%d"), _T(CONST_regValName_ca_chkUsrKeyResp_prefix), pVc->toolCa.tn_process_ca);
	qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_chkUsrKey);



	int caToolType = CONST_caToolType_bjca;
	TCHAR* who = (TCHAR*)_T("bjca.usr");

	int  iCmd = 0;
#if 0
	if (pVc->bTryToChkUsrKey) {
		iCmd = CONST_caCmd_chkUsrKey;
		//
		safeTcsnCpy(_T("正在检测Key"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

	}
	else
#endif
	{
		iCmd = CONST_caCmd_usrData;
		//
		safeTcsnCpy(_T("启动读取设备注册码"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

	}


	//
	bool  bFullCmp = false;
	if (createTool_ca(pQyMc->cfg.installDir, caToolType, who, iCmd, bSys, nullptr,  bDev, bFullCmp,  pProcInfo->m_var.ctxSm.caGwIp,  pProcInfo->m_var.ctxSm.caGwPort,  nullptr,  pQyMc->cfg.qmcLogFile,  &pVc->toolCa))  goto  errLabel;

	//
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("createTool_ca ok"));
#endif

	//
	int  i;
	for (i = 0; i < 1000; i++)
	{
		if (pVc->toolCa.bNeedQuit)  goto  errLabel;

		//
		waitForObject(&pVc->toolCa.hProcess_ca, 100);
		if (!pVc->toolCa.hProcess_ca) {
#ifdef  __DEBUG__
			traceLog((TCHAR*)_T("tool_ca waited"));
#endif
			//
			unsigned  int  uiType = 0;
			char  buf_resp[4096] = "";
			char  buf_resp_chkUsrKey[4096];
			unsigned  int bufLen = 0;

			//
			bufLen = sizeof(buf_resp_chkUsrKey);
			if (tmpGetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_chkUsrKey, &uiType, buf_resp_chkUsrKey, &bufLen)) {
				bufLen = 0;
			}
			buf_resp_chkUsrKey[bufLen] = 0;


			//
			bufLen = sizeof(buf_resp);
			if (tmpGetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp, &uiType, buf_resp, &bufLen)) {
				bufLen = 0;
			}
			buf_resp[bufLen] = 0;

			//
			qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_req);
			qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp);
			qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_chkUsrKey);



			TMP_caTool_result  result;



			//
#if 0
			if (pVc->bTryToChkUsrKey) {

				//
				memset(&result, 0, sizeof(result));
				parse_sendDataResp(buf_resp_chkUsrKey, &result);

				//
				pVc->bExists_usrKey = result.bExists_usrKey;

				//
				_sntprintf(tBuf, mycountof(tBuf), _T("threadProc_ca_usr: bExists_usrKey %d"), pVc->bExists_usrKey);
#ifdef  __DEBUG__
				traceLog(tBuf);
#endif
				safeTcsnCpy(tBuf, pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

				//
				break;
			}
#endif

			//
			memset(&result, 0, sizeof(result));
			parse_sendDataResp(buf_resp, &result);

			//
			if (!result.tUsrName[0]) {
				goto  errLabel;
			}

			//
			_sntprintf(tBuf, mycountof(tBuf), _T("threadProc_dev_ca_getUsrName: get tUsrName [%s]"), result.tUsrName);
			showInfo_open0(0, 0, tBuf);
#ifdef  __DEBUG__
			traceLog(tBuf);
#endif
			//
			safeTcsnCpy(tBuf, pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

			//
			safeTcsnCpy(result.tUsrName, pVc->dev.tUsrName, mycountof(pVc->dev.tUsrName));

			//
			pVc->dev.bGot_ca_usrName = true;

			//
			break;
		}
		//
		continue;
	}



	//
	iErr = 0;

	//
errLabel:

	//
	closeTool_ca(&pVc->toolCa);

#ifdef  __DEBUG__
	//
	DWORD  dwTickCnt_end = myGetTickCount(mynull);
	int  nElapseInMs = dwTickCnt_end - dwTickCnt_start;
	_sntprintf(tBuf, mycountof(tBuf), _T("tmpThreadProc_ca_usr leaves, nElapseInMs %dms"), nElapseInMs);
	traceLog(tBuf);
	//
#endif
	safeTcsnCpy(_T("结束"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

	//
	return  0;
}



//点击获取证书唯一标识符
void CDeviceBinding::on_btnGetTag_clicked(QString objname)
{
	if (m_pInfraredMenu) {
		//按钮1
		if (objname == "menuBtn1") {
			m_pInfraredMenu->on_menuBtn1_clicked();
		}
		//按钮2
		if (objname == "menuBtn2") {
			m_pInfraredMenu->on_menuBtn2_clicked();
		}
		//按钮3
		if (objname == "menuBtn3") {
			m_pInfraredMenu->on_menuBtn3_clicked();
		}
		//按钮4
		if (objname == "menuBtn4") {
			m_pInfraredMenu->on_menuBtn4_clicked();
		}
		//显示隐藏状态栏
		if (objname == "menuBtn5") {
			m_pInfraredMenu->on_menuBtn5_clicked();
		}
		//关机
		if (objname == "menuShutdown") {
			m_pInfraredMenu->on_menuShutdown_clicked();
		}
		//重启
		if (objname == "menuRestart") {
			m_pInfraredMenu->on_menuRestart_clicked();
		}
		//初始化设置
		if (objname == "menuSetting") {
			m_pInfraredMenu->on_menuSetting_clicked();
		}
		//端口设置
		if (objname == "PortSetting") {
			m_pInfraredMenu->on_PortSetting_clicked();
		}
		return;
	}

	//获取ip
	QString terminal_ip = ui->terminal_ip->text();


	//获取网关
	QString terminal_gateway = ui->terminal_gateway->text();

	//获取子网掩码
	QString terminal_mask = ui->terminal_mask->text();

	//获取dns
	QString terminal_dns = ui->terminal_dns->text();

	//获取mcu
	QString terminal_mcu = ui->terminal_mcu->text();

	//获取mcu2
	QString terminal_mcu2 = ui->terminal_mcu2->text();

	Sm_terminal_initCfg  initCfg;
	memset(&initCfg, 0, sizeof(initCfg));

	//
	char  buf[256];
	safeStrnCpy(terminal_ip.toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (!bIpValid(buf)) {

		//
		//ui->only_tag->setText(u8"IP地址输入无效，\n有效格式 xxx.xxx.xxx.xxx！");
		//ui->only_tag->setStyleSheet("font-size:28px;color:red;font-weight:bold;");
		//
		ui->terminal_ip->setFocus();

		return;
	}
	safeStrnCpy(buf, initCfg.terminal_ip, mycountof(initCfg.terminal_ip));
	//
	safeStrnCpy(terminal_mask.toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (!bMaskValid(buf)) {
		//ui->only_tag->setText(u8"子网掩码输入无效，\n有效格式 xxx.xxx.xxx.xxx！");
		//ui->only_tag->setStyleSheet("font-size:28px;color:red;font-weight:bold;");
		ui->terminal_mask->setFocus();
		return;
	}
	safeStrnCpy(buf, initCfg.terminal_mask, mycountof(initCfg.terminal_mask));
	//
	safeStrnCpy(terminal_gateway.toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (!bIpValid(buf)) {
		//ui->only_tag->setText(u8"网关地址输入无效，\n有效格式 xxx.xxx.xxx.xxx！");
		//ui->only_tag->setStyleSheet("font-size:28px;color:red;font-weight:bold;");
		//
		ui->terminal_gateway->setFocus();
		return;
	}
	safeStrnCpy(buf, initCfg.terminal_gateway, mycountof(initCfg.terminal_gateway));

	//
	safeStrnCpy(terminal_dns.toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (!bIpValid(buf)) {
		buf[0] = 0;
	}
	safeStrnCpy(buf, initCfg.terminal_dns, mycountof(initCfg.terminal_dns));

	//
	safeStrnCpy(terminal_mcu.toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (!bIpValid(buf)) {

		//ui->only_tag->setText(u8"MCU地址输入无效，\n有效格式 xxx.xxx.xxx.xxx！");
		//ui->only_tag->setStyleSheet("font-size:28px;color:red;font-weight:bold;");
		//
		ui->terminal_mcu->setFocus();
		return;
	}
	safeStrnCpy(buf, initCfg.terminal_mcu, mycountof(initCfg.terminal_mcu));

	//


	//
	if (m_hThread_ca) return;

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	Var_ca_dev_qmc* pVc = &pProcInfo->m_var.ctxSm.ca_dev;

	DWORD  dwThreadDaemonId;

	if (!m_hThread_ca) {

		//
		pVc->dev.bGot_ca_usrName = false;
		//
		pVc->dev.bStart_toGetUsrName = true;

		//int i
		//iDiffInMs = uiTickCnt - pVc->dwTickCnt_lastChkUsrKey;
		//if (abs(iDiffInMs) > 2000) 
		{
			//
			//pVc->bTryToChkUsrKey = true;
			//  启动检测key
			m_hThread_ca = CreateThread(NULL, 0, tmpThreadProc_dev_ca_getUsrName, 0, CREATE_SUSPENDED, &dwThreadDaemonId);
			if (!m_hThread_ca)  goto  errLabel;
			//gBuf_rtspCliHelp.dwThreadId_spl = dwThreadDaemonId;
			if (ResumeThread(m_hThread_ca) == -1)  goto  errLabel;
		}

	}



	//拿到识别码
#if 0
	ui->only_tag->setText(u8"识别码：asdf-asdfasdf-asdf");
	ui->only_tag->setStyleSheet("font-size:26px;color:#fff;font-family: Microsoft YaHei;font-weight:bold");
#endif

errLabel:
	return;
}


//点击确认
void CDeviceBinding::on_btn_clicked(QString objname) 
{
	if (m_pInfraredMenu) {
		//按钮1
		if (objname == "menuBtn1") {
			m_pInfraredMenu->on_menuBtn1_clicked();
		}
		//按钮2
		if (objname == "menuBtn2") {
			m_pInfraredMenu->on_menuBtn2_clicked();
		}
		//按钮3
		if (objname == "menuBtn3") {
			m_pInfraredMenu->on_menuBtn3_clicked();
		}
		//按钮4
		if (objname == "menuBtn4") {
			m_pInfraredMenu->on_menuBtn4_clicked();
		}
		//显示隐藏状态栏
		if (objname == "menuBtn5") {
			m_pInfraredMenu->on_menuBtn5_clicked();
		}
		//关机
		if (objname == "menuShutdown") {
			m_pInfraredMenu->on_menuShutdown_clicked();
		}
		//重启
		if (objname == "menuRestart") {
			m_pInfraredMenu->on_menuRestart_clicked();
		}
		//初始化设置
		if (objname == "menuSetting") {
			m_pInfraredMenu->on_menuSetting_clicked();
		}
		//显示调试窗
		if (objname == "menuDebug") {
			m_pInfraredMenu->on_menuDebug_clicked();
		}
		return;
	}


	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

	//
	//QString rootKey_sm_init = CONST_rootKey_sm_init;
	//QSettings* reg = new QSettings(rootKey_sm_init, QSettings::NativeFormat);
	
	//获取登录账户名
	QString terminal_username = ui->terminal_username->text();

	//获取密码
	QString terminal_pwd = ui->terminal_pwd->text();

	//获取ip
	QString terminal_ip = ui->terminal_ip->text();
	

	//获取网关
	QString terminal_gateway = ui->terminal_gateway->text();
	
	//获取子网掩码
	QString terminal_mask = ui->terminal_mask->text();

	//获取dns
	QString terminal_dns = ui->terminal_dns->text();

	//获取mcu
	QString terminal_mcu = ui->terminal_mcu->text();

	//获取mcu2
	QString terminal_mcu2 = ui->terminal_mcu2->text();

	//获取识别码
	QString terminal_sqm = ui->terminal_sqm->text();

	Sm_terminal_initCfg  initCfg;
	memset(&initCfg, 0, sizeof(initCfg));

	//
	char  buf[256];
	TCHAR  tBuf[256];
	//判断只有专用才加处理
	if (!pQyMc->appParams.bSmZy) {

		
		//
		QByteArray ba = terminal_username.toUtf8();
		char* data = ba.data(); //以上两步不能直接简化为“char *data = str.toUtf8().data();”
		int charLen = strlen(data);
		int len = MultiByteToWideChar(CP_ACP, 0, data, charLen, NULL, 0);
		TCHAR* tmp_buf = new TCHAR[len + 1];
		MultiByteToWideChar(CP_ACP, 0, data, charLen, tmp_buf, len);
		tmp_buf[len] = '\0';
		safeTcsnCpy(tmp_buf, tBuf, mycountof(tBuf));
		tTrim(tBuf);
		if (!tBuf[0]) {

			//
			ui->lab_err->setText(u8"登录账号输入无效！");
			ui->lab_err->setVisible(true);
			//
			ui->terminal_username->setFocus();

			return;
		}

		//char char_fake_devLoginName[256];

		//myTChar2Utf8(char_fake_devLoginName, initCfg.fake_devLoginName, mycountof(initCfg.fake_devLoginName));

		safeTcsnCpy(tBuf, initCfg.fake_devLoginName, mycountof(initCfg.fake_devLoginName));

		//
		safeStrnCpy(terminal_pwd.toUtf8().data(), buf, mycountof(buf));
		trim(buf);
		if (!buf[0]) {

			//
			ui->lab_err->setText(u8"登录密码输入无效！");
			ui->lab_err->setVisible(true);
			//
			ui->terminal_pwd->setFocus();

			return;
		}
		safeStrnCpy(buf, initCfg.fake_devLoginPasswd, mycountof(initCfg.fake_devLoginPasswd));

	}
	//
	safeStrnCpy(terminal_ip.toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (!bIpValid(buf)) {
		
		//
		ui->lab_err->setText(u8"IP地址输入无效，\n有效格式 xxx.xxx.xxx.xxx！");
		ui->lab_err->setVisible(true);
		//
		ui->terminal_ip->setFocus();

		return;
	}
	safeStrnCpy(buf, initCfg.terminal_ip, mycountof(initCfg.terminal_ip));
	//
	safeStrnCpy(terminal_mask.toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (!bMaskValid(buf)) {
		ui->lab_err->setText(u8"子网掩码输入无效，\n有效格式 xxx.xxx.xxx.xxx！");
		ui->lab_err->setVisible(true);
		ui->terminal_mask->setFocus();
		return;
	}
	safeStrnCpy(buf, initCfg.terminal_mask, mycountof(initCfg.terminal_mask));
	//
	safeStrnCpy(terminal_gateway.toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (!bIpValid(buf)) {
		ui->lab_err->setText(u8"网关地址输入无效，\n有效格式 xxx.xxx.xxx.xxx！");
		ui->lab_err->setVisible(true);
		//
		ui->terminal_gateway->setFocus();
		return;
	}
	safeStrnCpy(buf, initCfg.terminal_gateway, mycountof(initCfg.terminal_gateway));

	//
	safeStrnCpy(terminal_dns.toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (!bIpValid(buf)) {
		buf[0] = 0;
	}
	safeStrnCpy(buf, initCfg.terminal_dns, mycountof(initCfg.terminal_dns));

	//
	safeStrnCpy(terminal_mcu.toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (!bIpValid(buf)) {

		ui->lab_err->setText(u8"MCU地址输入无效，\n有效格式 xxx.xxx.xxx.xxx！");
		ui->lab_err->setVisible(true);
		//
		ui->terminal_mcu->setFocus();
		return;
	}
	safeStrnCpy(buf, initCfg.terminal_mcu, mycountof(initCfg.terminal_mcu));

	//
	safeStrnCpy(terminal_mcu2.toUtf8().data(), buf, mycountof(buf));
	trim(buf);

	string tmpBuf = buf;

	if (tmpBuf == "weixiu.qycx.com") {
		std::ofstream file("D:/qycx/tools/weixiu.d");
		if (file.is_open()) {
			file.close();
		}
	}
	else if (tmpBuf == "weixiu.qycx.com.ok") {
		const char* filePath = "D:/qycx/tools/weixiu.d";
		std::ifstream fileToCheck(filePath);
		if (fileToCheck.good()) {
			fileToCheck.close();
			BOOL ret = ::DeleteFile(L"D:\\qycx\\tools\\weixiu.d");
			/*if (std::remove(filePath)) {

			}*/
		}		
	}


	if (!bIpValid(buf)) {
		buf[0] = 0;
	}
	safeStrnCpy(buf, initCfg.terminal_mcu2, mycountof(initCfg.terminal_mcu2));

	//
	safeStrnCpy(terminal_sqm.toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (!buf[0]) {

		
		//只有sm要
		if(qyGetCustomId() == CONST_qyCustomId_business)
		{
			ui->lab_err->setText(u8"授权码不能为空！");
			ui->lab_err->setVisible(true);
			//
			ui->terminal_sqm->setFocus();
			return;
		
		}
		  
		//忽略
		buf[0] = 0;

		
	}
	safeStrnCpy(buf, initCfg.terminal_sqm, mycountof(initCfg.terminal_sqm));



	//双向认证这里
	//其它版本先隐藏  
	if (qyGetCustomId() != CONST_qyCustomId_business) {
		initCfg.authType = 1;
	}

	//initCfg.terminal_type = pProcInfo->m_var.ctxSm.smTerminalInitCfg.terminal_type;

	//
	if (memcmp(&initCfg, &pProcInfo->m_var.ctxSm.smTerminalInitCfg, sizeof(initCfg))) {
		if (saveSmTerminalInitCfg(&initCfg, pQyMc->cfg.tmInitFile)) {
			//
			ui->lab_err->setText(u8"save initCfg failed");
			ui->lab_err->setVisible(true);
			//
			return;
		}
	}


	this->close();
}

//点击取消
void CDeviceBinding::on_btnCancel_clicked(QString objname) {

	if (m_pInfraredMenu) {
		//按钮1
		if (objname == "menuBtn1") {
			m_pInfraredMenu->on_menuBtn1_clicked();
		}
		//按钮2
		if (objname == "menuBtn2") {
			m_pInfraredMenu->on_menuBtn2_clicked();
		}
		//按钮3
		if (objname == "menuBtn3") {
			m_pInfraredMenu->on_menuBtn3_clicked();
		}
		//按钮4
		if (objname == "menuBtn4") {
			m_pInfraredMenu->on_menuBtn4_clicked();
		}
		//显示隐藏状态栏
		if (objname == "menuBtn5") {
			m_pInfraredMenu->on_menuBtn5_clicked();
		}
		//关机
		if (objname == "menuShutdown") {
			m_pInfraredMenu->on_menuShutdown_clicked();
		}
		//重启
		if (objname == "menuRestart") {
			m_pInfraredMenu->on_menuRestart_clicked();
		}
		//初始化设置
		if (objname == "menuSetting") {
			m_pInfraredMenu->on_menuSetting_clicked();
		}
		//显示调试窗
		if (objname == "menuDebug") {
			m_pInfraredMenu->on_menuDebug_clicked();
		}
		return;
	}


	//获取ip
	QString terminal_ip = ui->terminal_ip->text();


	//获取网关
	QString terminal_gateway = ui->terminal_gateway->text();

	//获取子网掩码
	QString terminal_mask = ui->terminal_mask->text();

	//获取dns
	QString terminal_dns = ui->terminal_dns->text();

	//获取mcu
	QString terminal_mcu = ui->terminal_mcu->text();

	//获取mcu2
	QString terminal_mcu2 = ui->terminal_mcu2->text();

	//获取识别码
	QString terminal_sqm = ui->terminal_sqm->text();




	trim(terminal_ip.toUtf8().data());
	if (!bIpValid(terminal_ip.toUtf8().data())) {
		//
		ui->lab_err->setText(u8"IP地址输入无效，\n有效格式 xxx.xxx.xxx.xxx！");
		ui->lab_err->setVisible(true);
		//
		ui->terminal_ip->setFocus();

		return;
	}

	trim(terminal_mask.toUtf8().data());
	if (!bMaskValid(terminal_mask.toUtf8().data())) {
		ui->lab_err->setText(u8"子网掩码输入无效，\n有效格式 xxx.xxx.xxx.xxx！");
		ui->lab_err->setVisible(true);
		ui->terminal_mask->setFocus();
		return;
	}

	//
	trim(terminal_gateway.toUtf8().data());
	if (!bIpValid(terminal_gateway.toUtf8().data())) {
		ui->lab_err->setText(u8"网关地址输入无效，\n有效格式 xxx.xxx.xxx.xxx！");
		ui->lab_err->setVisible(true);
		//
		ui->terminal_gateway->setFocus();
		return;
	}


	trim(terminal_mcu.toUtf8().data());
	if (!bIpValid(terminal_mcu.toUtf8().data())) {

		ui->lab_err->setText(u8"MCU地址输入无效，\n有效格式 xxx.xxx.xxx.xxx！");
		ui->lab_err->setVisible(true);
		//
		ui->terminal_mcu->setFocus();
		return;
	}


	if (terminal_sqm.isEmpty() ) {

		//只有sm要
		if (qyGetCustomId() == CONST_qyCustomId_business)
		{
			ui->lab_err->setText(u8"授权码不能为空！");
			ui->lab_err->setVisible(true);
			//
			ui->terminal_sqm->setFocus();
			return;

		}
		//ui->lab_err->setText(u8"授权码不能为空！");
		//ui->lab_err->setVisible(true);
		////
		//ui->terminal_sqm->setFocus();
		//return;
	}
	

	this->close();

}



//确认键
void CDeviceBinding::Infrared_ok(QString objname)
{
	if (m_pInfraredMenu) {
		//按钮1
		if (objname == "menuBtn1") {
			m_pInfraredMenu->on_menuBtn1_clicked();
		}
		//按钮2
		if (objname == "menuBtn2") {
			m_pInfraredMenu->on_menuBtn2_clicked();
		}
		//按钮3
		if (objname == "menuBtn3") {
			m_pInfraredMenu->on_menuBtn3_clicked();
		}
		//按钮4
		if (objname == "menuBtn4") {
			m_pInfraredMenu->on_menuBtn4_clicked();
		}
		//
		if (objname == "btnVideo") {
			m_pInfraredMenu->on_btnVideo_clicked();
		}
		if (objname == "btnAudio") {
			m_pInfraredMenu->on_btnAudio_clicked();
		}
		//显示隐藏状态栏
		if (objname == "menuBtn5") {
			m_pInfraredMenu->on_menuBtn5_clicked();
		}
		//关机
		if (objname == "menuShutdown") {
			m_pInfraredMenu->on_menuShutdown_clicked();
		}
		//重启
		if (objname == "menuRestart") {
			m_pInfraredMenu->on_menuRestart_clicked();
		}
		//初始化设置
		if (objname == "menuSetting") {
			m_pInfraredMenu->on_menuSetting_clicked();
		}
		//端口设置
		if (objname == "PortSetting") {
			m_pInfraredMenu->on_PortSetting_clicked();
		}
		//显示调试窗
		if (objname == "menuDebug") {
			m_pInfraredMenu->on_menuDebug_clicked();
		}
		return;
	}

	
		if (objname == "btn_nvr") {
			on_showNvr_slots();
		} else if (objname == "pushButton_wireless") {
			on_showWifi_slots();
		} else if (objname == "pushButton_share") {
			on_showShare_slots();
		} else if (objname == "pushButton_check") {
			on_showCheck_slots();
		}
		else if (objname == "pushButton_selectVideo") {
			on_showSelectVideo_slots();
		}
		

	return;
}


//下箭头
void CDeviceBinding::Infrared_down() 
{
	if (m_pInfraredMenu) {
		m_pInfraredMenu->Infrared_down();
		return;
	}
	if (m_pPortSetting) {
		m_pPortSetting->Infrared_down();
		return;
	}
	if (m_pNvrConfig) {
		m_pNvrConfig->Infrared_down();
		return;
	}
	if (m_pCheck) {
		m_pCheck->Infrared_down();
		return;
	}
	if (m_pWifiConfig) {
		m_pWifiConfig->Infrared_down();
		return;
	}

	if (m_pShareConfig) {
		m_pShareConfig->Infrared_down();
		return;
	}

	if (m_pSelectVideo) {
		m_pSelectVideo->Infrared_down();
		return;
	}

	this->focusNextPrevChild(true);
	ui->terminal_username->deselect();
	ui->terminal_pwd->deselect();
	ui->terminal_ip->deselect();
	ui->terminal_mask->deselect();
	ui->terminal_gateway->deselect();
	ui->terminal_dns->deselect();
	ui->terminal_mcu->deselect();
	ui->terminal_mcu2->deselect();
	ui->terminal_sqm->deselect();
}
//上箭头
void CDeviceBinding::Infrared_up()
{
	if (m_pInfraredMenu) {
		m_pInfraredMenu->Infrared_up();
		return;
	}
	if (m_pPortSetting) {
		m_pPortSetting->Infrared_up();
		return;
	}
	if (m_pNvrConfig) {
		m_pNvrConfig->Infrared_up();
		return;
	}
	if (m_pCheck) {
		m_pCheck->Infrared_up();
		return;
	}
	if (m_pWifiConfig) {
		m_pWifiConfig->Infrared_up();
		return;
	}
	if (m_pShareConfig) {
		m_pShareConfig->Infrared_up();
		return;
	}
	if (m_pSelectVideo) {
		m_pSelectVideo->Infrared_up();
		return;
	}
	this->focusNextPrevChild(false);
	ui->terminal_username->deselect();
	ui->terminal_pwd->deselect();
	ui->terminal_ip->deselect();
	ui->terminal_mask->deselect();
	ui->terminal_dns->deselect();
	ui->terminal_gateway->deselect();
	ui->terminal_mcu->deselect();
	ui->terminal_mcu2->deselect();
	ui->terminal_sqm->deselect();
}

//左右光标移动
void CDeviceBinding::Infrared_input_left_right(QString name, bool isLeft)
{
	if (m_pNvrConfig) {
		m_pNvrConfig->Infrared_input_left_right(name ,isLeft);
		return;
	}

	if (m_pWifiConfig) {
		m_pWifiConfig->Infrared_input_left_right(name, isLeft);
		return;
	}

	if (m_pShareConfig) {
		m_pShareConfig->Infrared_input_left_right(name, isLeft);
		return;
	}

	if (m_pSelectVideo) {
		m_pSelectVideo->Infrared_input_left_right(name, isLeft);
		return;
	}

	if (isLeft) {
		if (name == "terminal_username") {
			int cur_index = ui->terminal_username->cursorPosition();
			ui->terminal_username->setCursorPosition(cur_index - 1);
			//ui->terminal_ip->cursorBackward(true);
		}
		else
		if (name == "terminal_pwd") {
			int cur_index = ui->terminal_pwd->cursorPosition();
			ui->terminal_pwd->setCursorPosition(cur_index - 1);
			//ui->terminal_ip->cursorBackward(true);
		}else
		if (name == "terminal_ip") {
			int cur_index = ui->terminal_ip->cursorPosition();
			ui->terminal_ip->setCursorPosition(cur_index - 1);
			//ui->terminal_ip->cursorBackward(true);
		}
		else if (name == "terminal_gateway") {
			int cur_index = ui->terminal_gateway->cursorPosition();
			ui->terminal_gateway->setCursorPosition(cur_index - 1);
			//ui->terminal_gateway->cursorBackward(true);
		}
		else if (name == "terminal_mask") {
			int cur_index = ui->terminal_mask->cursorPosition();
			ui->terminal_mask->setCursorPosition(cur_index - 1);
			//ui->terminal_mask->cursorBackward(true);
		}
		else if (name == "terminal_dns") {
			int cur_index = ui->terminal_dns->cursorPosition();
			ui->terminal_dns->setCursorPosition(cur_index - 1);
			//ui->terminal_mask->cursorBackward(true);
		}
		else if (name == "terminal_mcu") {
			int cur_index = ui->terminal_mcu->cursorPosition();
			ui->terminal_mcu->setCursorPosition(cur_index - 1);
			//ui->terminal_mcu->cursorBackward(true);
		}
		else if (name == "terminal_mcu2") {
			int cur_index = ui->terminal_mcu2->cursorPosition();
			ui->terminal_mcu2->setCursorPosition(cur_index - 1);
		
		}
		else if (name == "terminal_sqm") {
			int cur_index = ui->terminal_sqm->cursorPosition();
			ui->terminal_sqm->setCursorPosition(cur_index - 1);
			
		}
		else if (name == "btnCancel") {
			this->focusNextPrevChild(false);
		}
	
	}
	else {
		if (name == "terminal_username") {
			int cur_index = ui->terminal_username->cursorPosition();
			ui->terminal_username->setCursorPosition(cur_index + 1);
			//ui->terminal_ip->cursorForward(true);
		}
		else
		if (name == "terminal_pwd") {
			int cur_index = ui->terminal_pwd->cursorPosition();
			ui->terminal_pwd->setCursorPosition(cur_index + 1);
			//ui->terminal_ip->cursorForward(true);
		}else
		if (name == "terminal_ip") {
			int cur_index = ui->terminal_ip->cursorPosition();
			ui->terminal_ip->setCursorPosition(cur_index + 1);
			//ui->terminal_ip->cursorForward(true);
		}
		else if (name == "terminal_gateway") {
			int cur_index = ui->terminal_gateway->cursorPosition();
			ui->terminal_gateway->setCursorPosition(cur_index + 1);
			//ui->terminal_gateway->cursorForward(true);
		}
		else if (name == "terminal_dns") {
			int cur_index = ui->terminal_dns->cursorPosition();
			ui->terminal_dns->setCursorPosition(cur_index + 1);
			//ui->terminal_gateway->cursorForward(true);
		}
		else if (name == "terminal_mask") {
			int cur_index = ui->terminal_mask->cursorPosition();
			ui->terminal_mask->setCursorPosition(cur_index + 1);
			//ui->terminal_mask->cursorForward(true);
		}
		else if (name == "terminal_mcu") {
			int cur_index = ui->terminal_mcu->cursorPosition();
			ui->terminal_mcu->setCursorPosition(cur_index + 1);
			//ui->terminal_mcu->cursorForward(true);
		}
		else if (name == "terminal_mcu2") {
			int cur_index = ui->terminal_mcu2->cursorPosition();
			ui->terminal_mcu2->setCursorPosition(cur_index + 1);
			//ui->terminal_mcu->cursorForward(true);
		}
		else if (name == "terminal_sqm") {
			int cur_index = ui->terminal_sqm->cursorPosition();
			ui->terminal_sqm->setCursorPosition(cur_index + 1);
			//ui->terminal_mcu->cursorBackward(true);
		}
		else if (name == "btn") {
				this->focusNextPrevChild(true);
		}
	}
}


//表单输入
void CDeviceBinding::Infrared_input(QString name , QString value) 
{
	if (m_pNvrConfig) {
		m_pNvrConfig->Infrared_input(name,value);
		return;
	}

	if (m_pWifiConfig) {
		m_pWifiConfig->Infrared_input(name, value);
		return;
	}

	if (m_pShareConfig) {
		m_pShareConfig->Infrared_input(name, value);
		return;
	}

	if (m_pSelectVideo) {
		m_pSelectVideo->Infrared_input(name, value);
		return;
	}

	if (name == "terminal_username") {
		//QString tmp_str = ui->terminal_ip->text();
		ui->terminal_username->insert(value);
	}
	else
	if (name == "terminal_pwd") {
		//QString tmp_str = ui->terminal_ip->text();
		ui->terminal_pwd->insert(value);
	}else
	if (name == "terminal_ip") {
		//QString tmp_str = ui->terminal_ip->text();
		ui->terminal_ip->insert(value);
	}
	else if (name == "terminal_gateway") {
		//QString tmp_str = ui->terminal_gateway->text();
		ui->terminal_gateway->insert(value);
	}
	else if (name == "terminal_dns") {
		//QString tmp_str = ui->terminal_gateway->text();
		ui->terminal_dns->insert(value);
	}
	else if (name == "terminal_mask") {
		//QString tmp_str = ui->terminal_mask->text();
		ui->terminal_mask->insert(value);
	}
	else if (name == "terminal_mcu") {
		//QString tmp_str = ui->terminal_mcu->text();
		ui->terminal_mcu->insert(value);
	}
	else if (name == "terminal_mcu2") {
		//QString tmp_str = ui->terminal_mcu->text();
		ui->terminal_mcu2->insert(value);
	}
	else if (name == "terminal_sqm") {
		ui->terminal_sqm->insert(value);
	}
}

//表单输入字母
void CDeviceBinding::Infrared_input_leeter(QString name, QString value,bool is_replace)
{
	if (m_pNvrConfig) {
		m_pNvrConfig->Infrared_input_leeter(name , value , is_replace);
		return;
	}

	if (m_pWifiConfig) {
		m_pWifiConfig->Infrared_input_leeter(name, value, is_replace);
		return;
	}

	if (m_pShareConfig) {
		m_pShareConfig->Infrared_input_leeter(name, value, is_replace);
		return;
	}

	if (m_pSelectVideo) {
		m_pSelectVideo->Infrared_input_leeter(name, value, is_replace);
		return;
	}

	if (name == "terminal_username") {
		if (is_replace) {
			ui->terminal_username->backspace();
		}
		ui->terminal_username->insert(value);
	}
	else
	if (name == "terminal_pwd") {
		if (is_replace) {
			ui->terminal_pwd->backspace();
		}
		ui->terminal_pwd->insert(value);
	}else
	if (name == "terminal_ip") {
		if (is_replace) {
			ui->terminal_ip->backspace();
		}
		ui->terminal_ip->insert(value);
	}
	else if (name == "terminal_gateway") {
		if (is_replace) {
			ui->terminal_gateway->backspace();
		}
		ui->terminal_gateway->insert(value);
	}
	else if (name == "terminal_dns") {
		if (is_replace) {
			ui->terminal_dns->backspace();
		}
		ui->terminal_dns->insert(value);
	}
	else if (name == "terminal_mask") {
		if (is_replace) {
			ui->terminal_mask->backspace();
		}
		ui->terminal_mask->insert(value);
	}
	else if (name == "terminal_mcu") {
		if (is_replace) {
			ui->terminal_mcu->backspace();
		}
		ui->terminal_mcu->insert(value);
	}
	else if (name == "terminal_mcu2") {
		if (is_replace) {
			ui->terminal_mcu2->backspace();
		}
		ui->terminal_mcu2->insert(value);
	}
	else if (name == "terminal_sqm") {
		if (is_replace) {
			ui->terminal_sqm->backspace();
		}
		ui->terminal_sqm->insert(value);
	}
}

//退格键
void CDeviceBinding::Infrared_input_backspace(QString name) 
{
	if (m_pNvrConfig) {
		m_pNvrConfig->Infrared_input_backspace(name);
		return;
	}

	if (m_pWifiConfig) {
		m_pWifiConfig->Infrared_input_backspace(name);
		return;
	}

	if (m_pShareConfig) {
		m_pShareConfig->Infrared_input_backspace(name);
		return;
	}

	if (m_pSelectVideo) {
		m_pSelectVideo->Infrared_input_backspace(name);
		return;
	}

	if (name == "terminal_username") {
		ui->terminal_username->backspace();
	}
	else
	if (name == "terminal_pwd") {
		ui->terminal_pwd->backspace();
	}
	else
		if (name == "terminal_ip") {
		ui->terminal_ip->backspace();
	}
	else if (name == "terminal_gateway") {
		ui->terminal_gateway->backspace();
	}
	else if (name == "terminal_dns") {
		ui->terminal_dns->backspace();
	}
	else if (name == "terminal_mask") {
		ui->terminal_mask->backspace();
	}
	else if (name == "terminal_mcu") {
		ui->terminal_mcu->backspace();
	}
	else if (name == "terminal_mcu2") {
		ui->terminal_mcu2->backspace();
	}
	else if (name == "terminal_sqm") {
		ui->terminal_sqm->backspace();
	}
}
