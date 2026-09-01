
#define  __noDbg_new__

#include "CInfraredDialogMenu.h"

#include <QGraphicsDropShadowEffect>
#include <qDebug>
//
//#include <QDesktopWidget>
#include	<qscreen.h>
//
#include <QFile>

#include <CDlgTalk_qt.h>
#include <Windows.h>
#include "CMainFrame.h"
#include <ctxQmc_sm.h>
#include <infraredInstruct.h>
#include <CDeviceBinding.h>
#include	"smProc_qt.h"
#include "powerOffFunc.h"

//
CInfraredDialogMenu::CInfraredDialogMenu(QWidget* parent, QString m_status)
	: QDialog(parent),
	ui(new Ui::CInfraredDialogMenuClass)
{
	//ui.setupUi(this);


	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	ui->setupUi(this);


	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setWindowOpacity(0.9);
	//QCursor::setPos(0, 0);
	ui->menuBtn1->setText(u8"发言");
	ui->btnVideo->setText(u8"开启摄像头");
	ui->btnAudio->setText(u8"开启麦克风");
	ui->menuBtn2->setText(u8"发送辅流");
	ui->menuBtnAmplifier->setText(u8"画面放大");
	ui->menuBtnAmplifierClose->setText(u8"取消画面放大");
	ui->menuBtn3->setText(u8"显示本地视频");
	ui->menuInfo->setText(u8"显示信息窗");
	ui->menuBtn4->setText(u8"退出会议");
	ui->menuBtn5->setText(u8"关闭状态栏");
	ui->menuResolution->setText(u8"分辨率适应");
	ui->btnLogOut->setText(u8"退出登录");
	ui->menuOther->setText(u8"其它设置");
	ui->menuDebug->setText(u8"打开调试窗");
	ui->menuShare->setText(u8"打开共享");
	ui->menuP2p->setText(u8"点对点会议");
	ui->menuChairman->setText(u8"主席布局");


	ui->menuBtn1->setVisible(false);
	ui->btnVideo->setVisible(false);
	ui->btnAudio->setVisible(false);
	ui->menuBtn2->setVisible(false);
	ui->menuBtn3->setVisible(false);
	ui->menuInfo->setVisible(false);
	ui->menuBtn4->setVisible(false);
	ui->menuBtn5->setVisible(false);
	ui->menuBtn6->setVisible(false);
	ui->PortSetting->setVisible(false);
	ui->menuPoint->setVisible(false);
	ui->btnLogOut->setVisible(false);
	ui->menuOther->setVisible(false);
	ui->menuSetting->setVisible(false);
	ui->menuShutdown->setVisible(false);
	ui->menuRestart->setVisible(false);
	ui->menuResolution->setVisible(false);
	ui->menuDebug->setVisible(false);
	ui->menuShare->setVisible(false);
	ui->menuP2p->setVisible(false);
	ui->menuBtnAmplifier->setVisible(false);
	ui->menuBtnAmplifierClose->setVisible(false);
	ui->menuChairman->setVisible(false);


	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return;
	Ctx_sm& ctxSm = *pCtxSm;


	//
	if (m_status == "index") {
		//首页
		ui->PortSetting->setVisible(true);
		//ui->menuPoint->setVisible(false);
		

		if (pProcInfo) {
			if (pProcInfo->cfg.shareProcInitCfg.m_bEnableShare) {
				ui->menuShare->setVisible(true);
			}
			else {
				ui->menuShare->setVisible(false);
			}
		}

		ui->menuSetting->setVisible(true);
		ui->menuShutdown->setVisible(true);
		ui->menuDebug->setVisible(true);
		//其他版本 退出登录按钮做一下隐藏
		if (qyGetCustomId() == CONST_qyCustomId_business)
		{
			ui->btnLogOut->setVisible(true);
		}

		ui->menuOther->setVisible(true);
		ui->btnLogOut->setVisible(true);
		ui->menuRestart->setVisible(true);
		ui->menuResolution->setVisible(true);
		ui->menuP2p->setVisible(true);
		ui->menuSetting->setStyleSheet("border-top-right-radius:10px;border-top-left-radius:10px;");
		ui->menuShutdown->setStyleSheet("border-bottom-right-radius:10px;border-bottom-left-radius:10px;");



		//检测端口管理菜单是否被禁用
		if (ctxSm.hg.menuPower.bPortEnd == CONST_localTermPort_disable) {
			ui->PortSetting->setDisabled(true);
			ui->PortSetting->setText(u8"已禁用端口设置");
		}
	}
	else if (m_status == "cdlgtalk") {
		//会议页面操作菜单项
		ui->menuBtn1->setVisible(true);
		ui->btnVideo->setVisible(true);
		ui->btnAudio->setVisible(true);
		ui->menuBtn2->setVisible(true);

		if (pProcInfo) {
			if (pProcInfo->cfg.shareProcInitCfg.m_bEnableShare) {
				ui->menuShare->setVisible(true);
			}
			else {
				ui->menuShare->setVisible(false);
			}
		}
		//ui->menuBtnAmplifier->setVisible(true);
		//ui->menuBtnAmplifierClose->setVisible(true);
		ui->menuChairman->setVisible(true);
		ui->menuBtn3->setVisible(true);
		ui->menuInfo->setVisible(true);
		ui->menuBtn4->setVisible(true);
		ui->PortSetting->setVisible(true);
		//状态栏又给恢复了又   20240819    
		ui->menuBtn5->setVisible(true);
		ui->menuBtn1->setStyleSheet("border-top-right-radius:10px;border-top-left-radius:10px;");
		ui->menuBtn4->setStyleSheet("border-bottom-right-radius:10px;border-bottom-left-radius:10px;");


		//检测端口管理菜单是否被禁用
		if (ctxSm.hg.menuPower.bPortEnd == CONST_localTermPort_disable) {
			ui->PortSetting->setDisabled(true);
			ui->PortSetting->setText(u8"已禁用端口设置");
		}
	}
	else if (m_status == "login") {
		//登录页面
		//ui->menuIndex->setVisible(true);

		ui->menuSetting->setVisible(true);
		ui->menuShutdown->setVisible(true);
		ui->menuDebug->setVisible(true);
		ui->menuRestart->setVisible(true);
		ui->menuSetting->setStyleSheet("border-top-right-radius:10px;border-top-left-radius:10px;");
		ui->menuShutdown->setStyleSheet("border-bottom-right-radius:10px;border-bottom-left-radius:10px;");
		resize(this->width(), 100);
	}
	else {
		//其它情况
		//ui->menuIndex->setVisible(true);
		//ui->menuPoint->setVisible(true);
		ui->PortSetting->setVisible(true);
		ui->menuDebug->setVisible(true);
		ui->menuShutdown->setVisible(true);
		ui->menuRestart->setVisible(true);

		resize(this->width(), 100);
	}

	//普通终端暂时屏蔽掉，后面sm会议再可以打开
	ui->PortSetting->setVisible(false);
	ui->btnLogOut->setVisible(false);
	ui->menuBtn2->setVisible(false);
	ui->menuP2p->setVisible(false);
	ui->menuShare->setVisible(false);


	//
	sheetBackgroundImage();

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		move(((rc.width() - ui->widget->width()) / 2), this->height() + 200);
		if (m_status == "cdlgtalk" || m_status == "index") {
			int h = this->height() - 250;
			move(((rc.width() - ui->widget->width()) / 2), h);
		}
	}
	else {
		move(((rc.width() - ui->widget->width()) / 2), this->height() + 80);
		if (m_status == "cdlgtalk" || m_status == "index") {
			int h = this->height() - 500;
			move(((rc.width() - ui->widget->width()) / 2), h);
		}
	}

	QScreen* pScreen; pScreen = QApplication::primaryScreen();

	connect(pScreen, &QScreen::geometryChanged, this, &CInfraredDialogMenu::refResolution);

	//
	HWND  hWork = pQyMc->gui.hMainWnd;
	CMainFrame* pMainFrame = (CMainFrame*)CMainFrame::find((WId)pQyMc->gui.hMainWnd);
	if (IsWindow(pMainFrame->hWnd_curWorking)) {
		hWork = pMainFrame->hWnd_curWorking;
	}
	QWidget* pWidget = QWidget::find((WId)hWork);
	if (pWidget) {
		connect(this, SIGNAL(to_showDeviceBinding_signal()), pWidget, SLOT(on_showDeviceBinding_slots()));
		connect(this, SIGNAL(to_showPortSetting_signal()), pWidget, SLOT(on_showPortSetting_slots()));
		connect(this, SIGNAL(to_showDebugDlg_signal()), pWidget, SLOT(on_showDebug_slots()));
		connect(this, SIGNAL(to_openShareDlg_signal()), pWidget, SLOT(on_openShare_slots()));
		connect(this, SIGNAL(to_showP2pDlg_signal()), pWidget, SLOT(on_showP2pDlg_slots()));
		connect(this, SIGNAL(to_showOtherSetting_signal()), pWidget, SLOT(on_showOther_slots()));
	}

	//
	pMainFrame->hWnd_infraredMenu = (HWND)this->winId();


	//
	return;
}

CInfraredDialogMenu::~CInfraredDialogMenu()
{}

//刷新分辨率
void CInfraredDialogMenu::refResolution()
{

	sheetBackgroundImage();
}


void CInfraredDialogMenu::sheetBackgroundImage()
{
	QRect rc = QApplication::primaryScreen()->geometry();

	if (rc.width() > 3500) {
		int wid = 1600;
		int hid = 180;
		ui->widget->setFixedWidth(wid);
		ui->menuBtn1->setFixedSize(wid, hid);
		ui->btnAudio->setFixedSize(wid, hid);
		ui->btnVideo->setFixedSize(wid, hid);
		ui->menuBtn2->setFixedSize(wid, hid);
		ui->menuBtnAmplifier->setFixedSize(wid, hid);
		ui->menuBtnAmplifierClose->setFixedSize(wid, hid);
		ui->menuBtn3->setFixedSize(wid, hid);
		ui->menuInfo->setFixedSize(wid, hid);
		ui->menuBtn4->setFixedSize(wid, hid);
		ui->menuBtn5->setFixedSize(wid, hid);
		ui->menuBtn6->setFixedSize(wid, hid);
		ui->btnLogOut->setFixedSize(wid, hid);
		ui->menuOther->setFixedSize(wid, hid);
		ui->PortSetting->setFixedSize(wid, hid);
		ui->menuPoint->setFixedSize(wid, hid);
		ui->menuSetting->setFixedSize(wid, hid);
		ui->menuResolution->setFixedSize(wid, hid);
		ui->menuShutdown->setFixedSize(wid, hid);
		ui->menuRestart->setFixedSize(wid, hid);
		ui->menuDebug->setFixedSize(wid, hid);
		ui->menuShare->setFixedSize(wid, hid);
		ui->menuP2p->setFixedSize(wid, hid);
		ui->menuChairman->setFixedSize(wid, hid);

		ui->widget->setStyleSheet("QWidget#widget{border-radius:10px;} QPushButton{border-bottom:2px solid #000;background:#1E2747;font-size:68px;color:#fff;font-family: Microsoft YaHei;}QPushButton:focus {font-family: Microsoft YaHei;background:#1A54F1;color:#fff}");
		//ui->label_title->setStyleSheet("font-size:84px;color:#fff;font-weight:bold;background:none;font-family: Microsoft YaHei;");
		//ui->widget->setContentsMargins(20, 20, 20, 20);

	}
	else {

		ui->widget->setStyleSheet("QWidget#widget{border-radius:10px;} QPushButton{border-bottom:2px solid #000;background:#1E2747;font-size:28px;color:#fff;font-family: Microsoft YaHei;}QPushButton:focus {font-family: Microsoft YaHei;background:#1A54F1;color:#fff}");
		//ui->label_title->setStyleSheet("font-size:42px;color:#fff;font-weight:bold;background:none;font-family: Microsoft YaHei;");
		int hid = 90;
		ui->widget->setFixedWidth(720);
		ui->menuBtn1->setFixedSize(700, hid);
		ui->btnAudio->setFixedSize(700, hid);
		ui->btnVideo->setFixedSize(700, hid);
		ui->menuBtn2->setFixedSize(700, hid);
		ui->menuBtnAmplifier->setFixedSize(700, hid);
		ui->menuBtnAmplifierClose->setFixedSize(700, hid);
		ui->menuChairman->setFixedSize(700, hid);
		ui->btnLogOut->setFixedSize(700, hid);
		ui->menuOther->setFixedSize(700, hid);
		ui->menuBtn3->setFixedSize(700, hid);
		ui->menuInfo->setFixedSize(700, hid);
		ui->menuBtn4->setFixedSize(700, hid);
		ui->menuResolution->setFixedSize(700, hid);
		ui->menuBtn5->setFixedSize(700, hid);
		ui->menuBtn6->setFixedSize(700, hid);
		ui->PortSetting->setFixedSize(700, hid);
		ui->menuPoint->setFixedSize(700, hid);
		ui->menuSetting->setFixedSize(700, hid);
		ui->menuRestart->setFixedSize(700, hid);
		ui->menuShutdown->setFixedSize(700, hid);
		ui->menuDebug->setFixedSize(700, hid);
		ui->menuShare->setFixedSize(700, hid);
		ui->menuP2p->setFixedSize(700, hid);
	}

}


//下箭头
void CInfraredDialogMenu::Infrared_down()
{
	//
	if (chkFocus(this))return;

	//
	this->focusNextPrevChild(true);
}

//下箭头
void CInfraredDialogMenu::Infrared_up()
{
	if (chkFocus(this))return;

	//
	this->focusNextPrevChild(false);
}

//点击申请发言
void CInfraredDialogMenu::on_menuBtn1_clicked()
{
	emit to_speak_signal();

	//
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";
	/*
	if (ui->menuBtn1->text() == u8"发言(off)")
	{
		ui->menuBtn1->setText(u8"停止发言(on)");

		//
		qmcLogForHg(0, (TCHAR*)_T("终端开启发言"), false);
		log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启发言";
	}
	else {
		ui->menuBtn1->setText(u8"发言(off)");
		//
		log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭发言";
	}*/

	if (pProcInfo->xt.bSpeak)
	{

		ui->menuBtn1->setText(u8"停止发言(on)");

		//
		qmcLogForHg(0, (TCHAR*)_T("终端开启发言"), false);
		log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启发言";
	}
	else {
		ui->menuBtn1->setText(u8"发言(off)");
		//
		log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭发言";
	}

	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);
}

//点击开启摄像头
void CInfraredDialogMenu::on_btnVideo_clicked()
{
	emit to_video_signal();

	//
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	if (ui->btnVideo->text() == u8"开启摄像头(off)")
	{
		ui->btnVideo->setText(u8"关闭摄像头(on)");
		//
		log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"打开摄像头";
	}
	else {
		ui->btnVideo->setText(u8"开启摄像头(off)");
		////
		log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭摄像头";
	}

	//
	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);
}

//分辨率设置
void CInfraredDialogMenu::on_menuResolution_clicked() {
	DEVMODE devMode;
	devMode.dmSize = sizeof(DEVMODE);
	devMode.dmPelsWidth = 1920;
	devMode.dmPelsHeight = 1080;
	devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

	QRect rc = QApplication::primaryScreen()->geometry();
	//
	if ((int) & devMode.dmPelsWidth != rc.width()) {
		LONG result = ChangeDisplaySettings(&devMode, CDS_TEST);
		if (result == DISP_CHANGE_SUCCESSFUL) {
			result = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
			if (result != DISP_CHANGE_SUCCESSFUL) {
				// 恢复原来的显示设置
				ChangeDisplaySettings(NULL, 0);
				this->close();
				return;
			}
			this->close();

			return;
		}
	}
	this->close();
	return;
}


//点击开启麦克风
void CInfraredDialogMenu::on_btnAudio_clicked()
{
	emit to_audio_signal();

	//
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	if (ui->btnAudio->text() == u8"开启麦克风(off)")
	{
		ui->btnAudio->setText(u8"关闭麦克风(on)");
		//
		log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"打开麦克风";
	}
	else {
		ui->btnAudio->setText(u8"开启麦克风(off)");
		//
		log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭麦克风";
	}

	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

}


//辅流
void CInfraredDialogMenu::on_menuBtn2_clicked()
{
	emit to_device_screen_signal();

	//
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	if (ui->menuBtn2->text() == u8"发送辅流(off)")
	{
		ui->menuBtn2->setText(u8"停止辅流(on)");

		//
		log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"打开辅流";

	}
	else {
		ui->menuBtn2->setText(u8"发送辅流(off)");
		//
		log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭辅流";
	}

	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

}
//显示本地视频
void CInfraredDialogMenu::on_menuBtn3_clicked()
{

	//
	if (ui->menuBtn3->text() == u8"显示本地视频(off)") {
		ui->menuBtn3->setText(u8"关闭本地视频(on)");
	}
	else {
		ui->menuBtn3->setText(u8"显示本地视频(off)");
	}

	emit to_this_video_signal();

}

void CInfraredDialogMenu::on_menuInfo_clicked()
{
	//
	if (ui->menuInfo->text() == u8"显示信息窗(off)") {
		ui->menuInfo->setText(u8"关闭信息窗(on)");
	}
	else {
		ui->menuInfo->setText(u8"显示信息窗(off)");
	}

	emit to_this_info_signal();
}
//结束会议
void CInfraredDialogMenu::on_menuBtn4_clicked()
{
	emit to_EndAvBtn_signal();


}

//画面放大
void CInfraredDialogMenu::on_menuBtnAmplifier_clicked()
{

	emit to_amplifier_signal();

}

//取消画面放大
void CInfraredDialogMenu::on_menuBtnAmplifier_close_clicked()
{

	emit to_amplifier_close_signal();

}

//主席布局
void CInfraredDialogMenu::on_menuChairman_clicked()
{
	emit to_chairman_signal();
}

//显示隐藏状态栏
void CInfraredDialogMenu::on_menuBtn5_clicked()
{


	//
	if (ui->menuBtn5->text() == u8"显示状态栏") {
		ui->menuBtn5->setText(u8"关闭状态栏");
	}
	else {
		ui->menuBtn5->setText(u8"显示状态栏");
	}

	emit to_showStatus_signal();
}

//初始化设置
void CInfraredDialogMenu::on_menuSetting_clicked()
{
	emit to_showDeviceBinding_signal();
}

//点对点会议
void CInfraredDialogMenu::on_menuP2p_clicked()
{


	emit to_showP2pDlg_signal();

}


//端口设置
void CInfraredDialogMenu::on_PortSetting_clicked()
{
	//
	emit to_showPortSetting_signal();

}

//退出登录
void CInfraredDialogMenu::on_btnLogOut_clicked()
{
	emit to_LogOut_signal();
	//
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;

	//判断登录方式
	QString loginType = "";
	if (pProcInfo->m_var.ctxSm.usrLogin_sm.loginState.bExists_usrKey) {
		loginType = u8"UKEY登录";
	}
	else {
		loginType = u8"用户名密码登录";
	}

	//
	QString log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"主动退出登录；登录方式：" + loginType;

	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

}

//其他设置
void CInfraredDialogMenu::on_menuOther_clicked() {
	//
	emit to_showOtherSetting_signal();
}

//关闭开启调试窗
void CInfraredDialogMenu::on_menuDebug_clicked() {


	//
	if (ui->menuDebug->text() == u8"打开调试窗") {
		ui->menuDebug->setText(u8"关闭调试窗");
	}
	else {
		ui->menuDebug->setText(u8"打开调试窗");
	}

	//
	emit to_showDebugDlg_signal();
}

void CInfraredDialogMenu::on_menuShare_clicked() {


	//
	if (ui->menuShare->text() == u8"打开共享") {
		ui->menuShare->setText(u8"关闭共享");
	}
	else {
		ui->menuShare->setText(u8"打开共享");
	}

	//
	emit to_openShareDlg_signal();
}

//重启
void CInfraredDialogMenu::on_menuRestart_clicked()
{
	//
//
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;

	//
	QString log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：设备重启";

	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

	system("shutdown -r -t 00 -f");
}

//关机
void CInfraredDialogMenu::on_menuShutdown_clicked()
{
	//
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;

	//
	QString log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：设备关机";

	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

	//关机命令
	powerOffProc();

	//system("shutdown -s -t 00 -f");
}