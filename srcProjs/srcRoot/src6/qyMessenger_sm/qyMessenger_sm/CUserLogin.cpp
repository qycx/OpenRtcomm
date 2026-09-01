

#include	<qtimer.h>

#define  __noDbg_new__

#include "CUserLogin.h"

#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc_sm.h"
#include	"tmpRegFunc_open.h"
#include	"myCmdParams_open.h"

//#include <QDesktopWidget>

#include "CMainFrame.h"
#include	"smProc_qt.h"

//
CUserLogin::CUserLogin(QWidget *parent)
	: QWidget()
	,ui(new Ui::CUserLoginClass)
{
	ui->setupUi(this);

	ui->editUserAccount->installEventFilter(this);  
	ui->editPassword->installEventFilter(this);  
	//setAttribute(Qt::WA_StyledBackground);
	//this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint);
	this->setWindowFlags(Qt::WindowStaysOnTopHint);
	this->setWindowFlags(Qt::FramelessWindowHint);
	memset(&m_var, 0, sizeof(m_var));
	setAttribute(Qt::WA_DeleteOnClose, true);
	//
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

	HWND  hMainWnd = pQyMc->gui.hMainWnd;
	CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);

	connect(pMainWnd, SIGNAL(to_sendUserLoginWork_signal()), this, SLOT(on_infraredMenu()));
	connect(pMainWnd, SIGNAL(to_sendUserLoginWork_quit_signal()), this, SLOT(infraredMenu_quit()));

	QScreen* pScreen; pScreen = QApplication::primaryScreen();

	connect(pScreen, &QScreen::geometryChanged, this, &CUserLogin::refResolution);

	connect(parent, SIGNAL(to_userLogin_signal()), this, SLOT(on_loginUserBtn_clicked()));

	ui->editUserAccount->setFocus();


	//
	if (!pProcInfo->m_var.b_app_showNormal) {
		//
		QRect rc = QApplication::primaryScreen()->geometry();
		//
 		resize(rc.width(),rc.height());
		//this->showMaximized();
	}
	else {
		resize(480, 640);
	}


	

	//
	m_pWinTimer = new QTimer(this);
	connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(on_timer_winMethod()));
	m_pWinTimer->setInterval(100);
	m_pWinTimer->start();


	m_pWinRzStatusTimer = new QTimer(this);
	connect(m_pWinRzStatusTimer, SIGNAL(timeout()), this, SLOT(sxrzStatus()));

	m_pWinRzStatusTimer->setInterval(1000);
	m_pWinRzStatusTimer->start();


	sheetBackgroundImage();

	ui->editUkey->setText(u8"UKEY已插入，请输入密码");

	//ui->prodName->setText(u8"清扬信安硬件视频会议终端 QYXA MBX V1.0");
	ui->prodName->setText(u8"冠群硬件视频会议终端 GQ MBX V1.0");
	

	ui->ukey_img->setEnabled(false);
		
	showUkeyStatus(false);

	//
	if (pProcInfo->cfg.bSkip_sm_usrLogin) {
		ui->editUserAccount->setText("***");
		ui->editPassword->setText("***");
		//
		on_loginUserBtn_clicked();
	}


}

void CUserLogin::sheetBackgroundImage() 
{
	QRect rc = QApplication::primaryScreen()->geometry();

	if (rc.width() > 3500) {
		ui->bodywidget->setStyleSheet("#bodywidget{border-image:url(':/Resources/Images/Sm/t12@2x.png');}");
		ui->widget_2->setStyleSheet("#widget_2{border-image:url(':/Resources/Images/Sm/t14@2x.png');background-repeat:no-repeat;}");
		ui->lab_title->setStyleSheet("font-size:92px;color:#fff;font-weight:bold;background:none;font-family: Microsoft YaHei;");
		/*ui->editUserAccount->setStyleSheet("background:#192036;border-radius:10px;font-size:50px;color:#fff");
		ui->editPassword->setStyleSheet("background:#192036;border-radius:10px;font-size:50px;color:#fff");*/

		ui->editUkey->setStyleSheet("QLineEdit{padding-left:30px;background:#102145;border-radius:10px;font-size:50px;color:#fff}QLineEdit:focus{border:2px solid #fff;border-radius:10px;font-size:50px;color:#fff}");
		ui->editUserAccount->setStyleSheet("QLineEdit{padding-left:30px;background:#102145;border-radius:10px;font-size:50px;color:#fff}QLineEdit:focus{border:2px solid #fff;border-radius:10px;font-size:50px;color:#fff}");
		ui->editPassword->setStyleSheet("QLineEdit{padding-left:30px;background:#102145;border-radius:10px;font-size:50px;color:#fff}QLineEdit:focus{border:2px solid #fff;border-radius:10px;font-size:50px;color:#fff}");

		QPalette palet = ui->editPassword->palette();
		QPalette editUserAccount = ui->editUserAccount->palette();
		palet.setColor(QPalette::Normal, QPalette::PlaceholderText, "#fff");
		ui->editPassword->setPalette(palet);
		ui->editUserAccount->setPalette(palet);
		//ui->loginUserBtn->setStyleSheet("color:#fff;font-size:59px;font-weight:bold;background:#4AABFE;border-radius:10px;font-family: Microsoft YaHei;");
		//ui->loginUserBtn->setStyleSheet("QPushButton{font-size:59px;font-weight:bold;color:#fff;background:#404041;border-radius:10px;font-family: Microsoft YaHei;border-radius:10px}QPushButton:hover{font-family: Microsoft YaHei;background:#2C9AD0;color:#fff}QPushButton:focus {font-family: Microsoft YaHei;background:#2C9AD0;color:#fff}");
		ui->loginUserBtn->setStyleSheet("QPushButton{font-size:59px;font-weight:bold;color:#fff;background:#5C8CFC;border-radius:10px;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		//错误提示
		//ui->label_err->setStyleSheet("font-size:36px;color:red");
			
		ui->ukeyStatus->setStyleSheet("font-family: Microsoft YaHei;font-size:30px;color:#1F3D5B;font-weight:bold");
		//ui->ukeyStatusText->setStyleSheet("font-family: Microsoft YaHei;font-size:36px;color:#1F3D5B;font-weight:bold");

		ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t9@2x.png');background-repeat:no-repeat;");
		ui->label_status->setStyleSheet("font-size:32px;color:#2C9AD0;");
		ui->label_status->setText(u8"认证正常");
		ui->prodName->setStyleSheet("font-size:32px;color:#fff");
		ui->widget_2->setContentsMargins(7, 50, 7, 100);
	}
	else {

		ui->bodywidget->setStyleSheet("#bodywidget{background-image:url(':/Resources/Images/Sm/t12.png');}");
		ui->widget_2->setStyleSheet("#widget_2{background-image:url(':/Resources/Images/Sm/t14.png');background-repeat:no-repeat;}");
		ui->lab_title->setStyleSheet("font-size:45px;color:#fff;font-weight:bold;background:none;font-family: Microsoft YaHei;");
		/*ui->editUserAccount->setStyleSheet("background:#192036;border-radius:10px;font-size:25px;color:#fff");
		ui->editPassword->setStyleSheet("background:#192036;border-radius:10px;font-size:25px;color:#fff");*/
		ui->editUkey->setStyleSheet("QLineEdit{padding-left:15px;background:#102145;border-radius:10px;font-size:25px;color:#fff;font-weight:bold}");
		ui->editUserAccount->setStyleSheet("QLineEdit{padding-left:15px;background:#102145;border-radius:10px;font-size:25px;color:#fff}QLineEdit:focus{border:2px solid #fff;border-radius:10px;font-size:25px;color:#fff}");
		ui->editPassword->setStyleSheet("QLineEdit{padding-left:15px;background:#102145;border-radius:10px;font-size:25px;color:#fff}QLineEdit:focus{border:2px solid #fff;border-radius:10px;font-size:25px;color:#fff}");
		QPalette palet = ui->editPassword->palette();
		QPalette editUserAccount = ui->editUserAccount->palette();
		palet.setColor(QPalette::Normal, QPalette::PlaceholderText, "#999aaa");
		ui->editPassword->setPalette(palet);
		ui->editUserAccount->setPalette(palet);
		//ui->loginUserBtn->setStyleSheet("color:#fff;font-size:29px;font-weight:bold;background:#4AABFE;border-radius:10px;font-family: Microsoft YaHei;");
		ui->loginUserBtn->setStyleSheet("QPushButton{font-size:29px;font-weight:bold;color:#fff;background:#5C8CFC;border-radius:10px;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		//错误提示
	//	ui->label_err->setStyleSheet("font-size:18px;color:red");

		ui->ukeyStatus->setStyleSheet("font-family: Microsoft YaHei;font-size:18px;color:#1F3D5B;font-weight:bold");
		//ui->ukeyStatusText->setStyleSheet("font-family: Microsoft YaHei;font-size:25px;color:#1F3D5B;font-weight:bold");

		ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t9.png');background-repeat:no-repeat;");
		ui->label_status->setStyleSheet("font-size:16px;color:#2C9AD0;");
		ui->label_status->setText(u8"认证正常");

		//ui->prodName->setStyleSheet("font-size:16px;color:#fff");



		ui->lab_img2->setFixedSize(23, 23);
		ui->editUkey->setFixedSize(548,86);
		ui->editUserAccount->setFixedSize(548,86);
		ui->editPassword->setFixedSize(548,86);
		ui->loginUserBtn->setFixedSize(548,86);
		//ui->widget_err->setFixedSize(548,60);
		ui->ukeyStatuswidget->setFixedSize(548,50);

		ui->widget_1->setFixedSize(548,50);

		ui->ukey_img->setFixedSize(35,35);
		ui->widget_2->setFixedSize(642,586);
		ui->widget_2->setContentsMargins(7,50,7,30);
		
		
	}
}

CUserLogin::~CUserLogin()
{
	delete ui;

	//
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	Var_ca_usr_qmc* pVc = &pProcInfo->m_var.ctxSm.ca_usr;
	
	//
	showInfo_open0(0, 0, _T("~CUserLogin enters"));
	
	//
#if  0
	if (m_hThread_ca) {
		pVc->toolCa.bNeedQuit = true;
		//
		waitForObject(&m_hThread_ca, INFINITE);
	}
#endif
	smUsrLogin_clean(m_var.m_smUsrLoginVar, pProcInfo->getCtxSm());


	//
	if (this->m_pWinTimer) {
		delete  m_pWinTimer;
	}
	
	if (this->m_pWinRzStatusTimer) {
		delete  m_pWinRzStatusTimer;
		m_pWinRzStatusTimer = nullptr;
	}


	//
	if (m_pInfraredMenu) {
		delete m_pInfraredMenu;
		m_pInfraredMenu = nullptr;
	}

	/*if (m_pCMain)
	{
		delete m_pCMain;
		m_pCMain = nullptr;
	}*/

	//
	CMainFrame* pMainFrame = (CMainFrame*)CMainFrame::find((WId)pQyMc->gui.hMainWnd);
	if (pMainFrame) {
		if (pMainFrame->m_pUserLogin == this) {
			pMainFrame->m_pUserLogin = mynull;
		}
	}

	//	
	emit to_userLoginFinished_signal();

	//
	showInfo_open0(0, 0, _T("~CUserLogin leaves"));

}

//刷新分辨率
void CUserLogin::refResolution()
{

	sheetBackgroundImage();
}

//认证状态检测
void CUserLogin::sxrzStatus()
{
	//检测分辨率变化
	//sheetBackgroundImage();

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	//
	QRect rc = QApplication::primaryScreen()->geometry();
	//
	if (rc.width() > 3500) {

		if (pProcInfo->xt.nTimes_waitForXtResp <= 1)
		{
			ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t9@2x.png');background-repeat:no-repeat;");
			ui->label_status->setStyleSheet("font-size:32px;color:#2C9AD0;");
			ui->label_status->setText(u8"认证正常");
		}
		else if (pProcInfo->xt.nTimes_waitForXtResp == 2) {
			ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t20@2x.png');background-repeat:no-repeat;");
			ui->label_status->setStyleSheet("font-size:32px;color:red;");
			ui->label_status->setText(u8"认证异常,正在重连!");
		}
		else if (pProcInfo->xt.nTimes_waitForXtResp == 3) {
			ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t20@2x.png');background-repeat:no-repeat;");
			ui->label_status->setStyleSheet("font-size:32px;color:red;");
			ui->label_status->setText(u8"认证失败,即将退出!");
		}

	}
	else {

		if (pProcInfo->xt.nTimes_waitForXtResp <= 1)
		{
			ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t9.png');background-repeat:no-repeat;");
			ui->label_status->setStyleSheet("font-size:16px;color:#2C9AD0;");
			ui->label_status->setText(u8"认证正常");
		}
		else if (pProcInfo->xt.nTimes_waitForXtResp == 2) {
			ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t20.png');background-repeat:no-repeat;");
			ui->label_status->setStyleSheet("font-size:16px;color:red;");
			ui->label_status->setText(u8"认证异常,正在重连!");
		}
		else if (pProcInfo->xt.nTimes_waitForXtResp == 3) {
			ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t20.png');background-repeat:no-repeat;");
			ui->label_status->setStyleSheet("font-size:16px;color:red;");
			ui->label_status->setText(u8"认证失败,即将退出!"	);
		}


	}

}



//显示提示窗
void CUserLogin::showHint(QString msg, QString fontColor, qint64 out_time) {



	
	//NoticeWidget* noticeWin = new NoticeWidget();
	//noticeWin->show();
	NoticeWidget::showNotice(this, msg, fontColor, out_time);

}

void CUserLogin::infraredMenu_quit() 
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

	return;
}

//红外菜单
void CUserLogin::on_infraredMenu() 
{
	//
	if (!m_pInfraredMenu)
	{
		m_pInfraredMenu = new CInfraredDialogMenu(this, "login");
	}

	//
//	if  (  m_pInfraredMenu->winId()  !=  pQyMc)

	//
	if (!m_pInfraredMenu->isVisible()) {
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

//显示调试窗
void CUserLogin::on_showDebug_slots() {
	
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




//确认键
void CUserLogin::Infrared_ok(QString objname)
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
		//显示调试窗
		if (objname == "menuDebug") {
			m_pInfraredMenu->on_menuDebug_clicked();
		}
		return;
}
	return;
}

//ukey插拔显示
void CUserLogin::showUkeyStatus(bool isIn) 
{

	QRect rc = QApplication::primaryScreen()->geometry();

	if (rc.width() > 3500) {
		if (isIn) {
			ui->ukey_img->setStyleSheet("border:none;background-image:url(':/Resources/Images/WinMain/ukey_inx2.png');background-repeat:no-repeat;");

		}
		else {
			ui->ukey_img->setStyleSheet("border:none;background-image:url(':/Resources/Images/WinMain/ukey_outx2.png');background-repeat:no-repeat;");
		}
	}
	else {
		if (isIn) {
			ui->ukey_img->setStyleSheet("border:none;background-image:url(':/Resources/Images/WinMain/ukey_in.png');background-repeat:no-repeat;");

		}
		else {
			ui->ukey_img->setStyleSheet("border:none;background-image:url(':/Resources/Images/WinMain/ukey_out.png');background-repeat:no-repeat;");
		}
	}


	
}



//
int  CUserLogin::showStatus(TCHAR* str, int iRc_fromHg, TCHAR* tRcDesc_fromHg)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	Var_ca_usr_qmc* pVc = &pProcInfo->m_var.ctxSm.ca_usr;

	if (!str)str = (TCHAR*)_T("");

	//
	//ui->label_status->setText(QString::fromUtf16((const char16_t*)str));

	QString tmp_keyStatus = "";
	//
	QRect rc = QApplication::primaryScreen()->geometry();
	if (pVc->bExists_usrKey) {

		tmp_keyStatus = u8"检测到UKEY已插入";
		showUkeyStatus(true);

		

		if (rc.width() > 3500) {
			//#1A54F1
			ui->ukeyStatus->setStyleSheet("font-family: Microsoft YaHei;font-size:30px;color:#1A54F1;font-weight:bold");
		}
		else {
			//#1A54F1
			ui->ukeyStatus->setStyleSheet("font-family: Microsoft YaHei;font-size:18px;color:#1A54F1;font-weight:bold");
		}

		
#if 0
		ui->ukeyStatus->setText(u8"已启用UKEY登陆");
#endif
	}
	else {
		if (rc.width() > 3500) {
			//
			ui->ukeyStatus->setStyleSheet("font-family: Microsoft YaHei;font-size:30px;color:#1F3D5B;font-weight:bold");
		}
		else {
			//
			ui->ukeyStatus->setStyleSheet("font-family: Microsoft YaHei;font-size:18px;color:#1F3D5B;font-weight:bold");
		}
		
#if  0
		ui->ukeyStatus->setText(u8"未启用UKEY登录");
#endif
		showUkeyStatus(false);
		tmp_keyStatus = u8"检测到UKEY已拔出";
	}

	//判断ukey插入变化 记录一条日志
	if (s_keyStatus != "" && s_keyStatus != tmp_keyStatus) {

		//
		QString log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + tmp_keyStatus;

		//清空输入框内容
		ui->editPassword->setText("");
		ui->editUserAccount->setText("");

		qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

		showHint(tmp_keyStatus, "red", 1000);
	}
	
	s_keyStatus = tmp_keyStatus;


	
		//ui->ukeyStatusText->setVisible(true);
	QString ukeyStatusValue = tmp_keyStatus;// ui->ukeyStatus->text();
	QString new_str = QString::fromUtf16((const char16_t*)str);
	if (iRc_fromHg) {
		new_str = doUserStatusText(iRc_fromHg , tRcDesc_fromHg);
	}

	//ui->ukeyStatus->setText(ukeyStatusValue + QString(". ") + new_str);
	ui->ukeyStatus->setText(new_str);
	//}
	

	return  0;
}


//
void CUserLogin::on_timer_winMethod()
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	Var_ca_usr_qmc* pVc = &pProcInfo->m_var.ctxSm.ca_usr;
	int  ii = 0;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	

	//
	static uint suiLastTickCnt = 0;
	uint uiTickCnt = myGetTickCount(mynull);
	int iDiffInMs = 0;
	DWORD  dwThreadDaemonId;


	//
	if (pProcInfo->xt.nTimes_waitForXtResp > 2) {
		safeTcsnCpy(_T("长时间没收到心跳响应包"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
		showStatus(pVc->tStatusBuf, pVc->usrLogin.iRc, pVc->usrLogin.tRcDesc);
	}
	//
	showStatus(pVc->tStatusBuf, pVc->usrLogin.iRc , pVc->usrLogin.tRcDesc);

	//
	iDiffInMs = uiTickCnt - suiLastTickCnt;
	if (abs(iDiffInMs) > 1000) {
		suiLastTickCnt = uiTickCnt;

		//‘
		//切换ukey插入效果
		if (pVc->bExists_usrKey) {
			ui->editUkey->setVisible(true);
			ui->editUserAccount->setVisible(false);

		}
		else {
			ui->editUkey->setVisible(false);
			ui->editUserAccount->setVisible(true);

		}
	}



	//
	HWND  hDlg = (HWND)this->winId();
	bool  bNeedShowLogon = false;
	bool  bNeedClose = false;
	smUsrLogin_onTimer(hDlg, &m_var, pProcInfo->getCtxSm(), bNeedShowLogon, bNeedClose, pProcInfo->uiTerminalType);
	//
#ifdef  __DEBUG__
	if (1) {
		traceLog((TCHAR*)_T("TEST: after smUsrLogin_onTimer: bSkip_sm_usrLogin is true. needClose "));
		if (pProcInfo->cfg.bSkip_sm_usrLogin) {
			bNeedClose = true;
		}		
	}
#endif 
	//
	if (bNeedShowLogon) {
		ui->loginUserBtn->setEnabled(true);
		ui->loginUserBtn->setText(u8"登录");
	}
	if (bNeedClose) {
		closeWnd_qt(this, _T(""));
		return;
	}



	//
	if (pProcInfo->cfg.bSkip_sm_usrLogin) {
		ui->editUserAccount->setText("1");
		ui->editPassword->setText("1");
		//
		on_loginUserBtn_clicked();
	}




errLabel:
	return;
}







//显示初始化窗口
void CUserLogin::on_showDeviceBinding_slots()
{
	int i = 1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	Var_ca_usr_qmc* pVc = &pProcInfo->m_var.ctxSm.ca_usr;





	//
	setNeedCfgOn_smTerminalInitCfg(true);

	//
	this->close();

	//
	//emit to_userLoginFinished_signal();

}

//点击登录
void CUserLogin::on_loginUserBtn_clicked(QString objname) 
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
	CCtxQmc_sm  * pProcInfo  =  (  CCtxQmc_sm*)pQyMc->get_pProcInfo();
	Var_ca_usr_qmc* pVc = &pProcInfo->m_var.ctxSm.ca_usr;


	//

	HWND  hMainWnd = pQyMc->gui.hMainWnd;
	CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
	pMainWnd->on_time_upWaitMeetingList();

	//
	if (m_var.m_bStartToUsrLogin) {
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("already startToUsrLogin"));
#endif
		return;
	}

	//
	char  buf[256];
	safeStrnCpy(ui->editPassword->text().toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (!buf[0]) {
		safeTcsnCpy(_T("密码不能为空"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
		return;
	}


	//如果是插ukey登录了 长度不能低于6位

	if (pVc->bExists_usrKey) 
	{
		if (ui->editPassword->text().length() < 6 ) {

			safeTcsnCpy(_T("密码最少6位，不超过16位！"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

			

			qmcLogForHg(0, (wchar_t*)pVc->tStatusBuf, false);

			return;
		}
	
	}

	//
	smUsrLogin_clean(m_var.m_smUsrLoginVar, &pProcInfo->m_var.ctxSm);
#if 0
	pVc->toolCa.bNeedQuit = true;
	waitForObject(&m_var.m_smUsrLoginVar.m_hThread_ca, INFINITE);
	pVc->toolCa.bNeedQuit = false;
#endif

	//
	memset(&pVc->usrLogin, 0, sizeof(pVc->usrLogin));

	//
	if (!pVc->bExists_usrKey) {
		safeTcsnCpy((TCHAR*)ui->editUserAccount->text().utf16(), pVc->usrLogin.loginUsingName.tUsrName, mycountof(pVc->usrLogin.loginUsingName.tUsrName));
		safeStrnCpy(ui->editPassword->text().toUtf8().data(), pVc->usrLogin.loginUsingName.passwd, mycountof(pVc->usrLogin.loginUsingName.passwd));
	}
	else {
		 safeStrnCpy(ui->editPassword->text().toUtf8().data(), pVc->usrLogin.keyPasswd, mycountof(pVc->usrLogin.keyPasswd));
	}

	//
	showInfo_open0(0, 0, _T("start to usrLogin"));
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("start to usrLogin"));
#endif

	//
	TCHAR  tBuf[128];
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	_sntprintf(tBuf, mycountof(tBuf), _T("登录 %S ..."), pMisCnt->server.ip);

	//
	ui->loginUserBtn->setEnabled(false);
	ui->loginUserBtn->setText(QString::fromUtf16((const char16_t*)tBuf));

	//
	m_var.m_bStartToUsrLogin = true;
	m_var.dwTickCnt_startToUsrLogin = myGetTickCount(mynull);

	//
	return;

}


//下箭头
void CUserLogin::Infrared_down()
{
	if (m_pInfraredMenu) {
		m_pInfraredMenu->Infrared_down();
		return;
	}
	//
	if (chkFocus(this)) return;

	//
	this->focusNextPrevChild(true);
	ui->editUserAccount->deselect();
	ui->editPassword->deselect();
}
//上箭头
void CUserLogin::Infrared_up()
{
	if (m_pInfraredMenu) {
		m_pInfraredMenu->Infrared_up();
		return;
	}
	//
	if (chkFocus(this))return;

	//
	this->focusNextPrevChild(false);
	ui->editUserAccount->deselect();
	ui->editPassword->deselect();
}

//
bool CUserLogin::eventFilter(QObject * watched , QEvent * event) 
{
	if (watched == ui->editPassword) {

		if (event->type() == QEvent::FocusIn) 
		{
			ui->editPassword->setEchoMode(QLineEdit::Normal);
			
		}
		else if (event->type() == QEvent::FocusOut) {
			ui->editPassword->setEchoMode(QLineEdit::Password);
		
		}

	}
	return QWidget::eventFilter(watched, event);
}


//左右光标移动
void CUserLogin::Infrared_input_left_right(QString name, bool isLeft)
{


	if (isLeft) {

		if (name == "editUserAccount") {
			int cur_index = ui->editUserAccount->cursorPosition();
			ui->editUserAccount->setCursorPosition(cur_index - 1);
		}
		else if (name == "editPassword") {
			int cur_index = ui->editPassword->cursorPosition();
			ui->editPassword->setCursorPosition(cur_index - 1);
		}

	}
	else {
		if (name == "editUserAccount") {
			int cur_index = ui->editUserAccount->cursorPosition();
			ui->editUserAccount->setCursorPosition(cur_index + 1);
		}
		else if (name == "editPassword") {
			int cur_index = ui->editPassword->cursorPosition();
			ui->editPassword->setCursorPosition(cur_index + 1);
		}

	}
}


//表单输入
void CUserLogin::Infrared_input(QString name, QString value)
{
	if (name == "editUserAccount") {
		ui->editUserAccount->insert(value);
	}
	else if (name == "editPassword") {
		ui->editPassword->insert(value);
	}
}

//表单输入字母
void CUserLogin::Infrared_input_leeter(QString name, QString value, bool is_replace)
{
	if (name == "editUserAccount") {
		if (is_replace) {
			ui->editUserAccount->backspace();
		}
		ui->editUserAccount->insert(value);
	}
	else if (name == "editPassword") {
		if (is_replace) {
			ui->editPassword->backspace();
		}
		ui->editPassword->insert(value);
	}
}

//退格键
void CUserLogin::Infrared_input_backspace(QString name)
{

	if (name == "editUserAccount") {
		ui->editUserAccount->backspace();
	}
	else if (name == "editPassword") {
		ui->editPassword->backspace();
	}
}

//错误码
QString CUserLogin::doUserStatusText(int iRc_fromHg,TCHAR* tRcDesc_fromHg)
{
	QString err_text = "";
	if (iRc_fromHg == 10108 || iRc_fromHg == 10105 || iRc_fromHg == 10103) {

		err_text = QString::fromUtf16((const char16_t*)tRcDesc_fromHg);
		//
		ui->loginUserBtn->setEnabled(true);
		ui->loginUserBtn->setText(u8"登录");
	}

	//10106  认证 
	if (iRc_fromHg == 10106) {
		err_text = u8"登录失败，请更换登录方式";
		//
		ui->loginUserBtn->setEnabled(true);
		ui->loginUserBtn->setText(u8"登录");
	}


	
	return err_text;
}

