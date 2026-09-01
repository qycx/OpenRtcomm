
#define  __noDbg_new__

#include "CQmcLogin.h"
#include "ui_CQmcLogin.h"
#include "CMainFrame.h" 

#include    <qdir.h>
#include	<ctxQmc_sm.h>
#include	"myCmdParams_open.h"
#include	"tmpRegFunc_open.h"
#include	"imCommType_defs.h"
#include "CDeviceBinding.h"
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>

//
CQmcLogin::CQmcLogin(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::CQmcLogin)
{
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("qmcLogin::CQmcLogin() enters"));
#endif

	ui->setupUi(this);

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	HWND  hMainWnd = pQyMc->gui.hMainWnd;
	CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);

	connect(pMainWnd, SIGNAL(to_sendQmcLoginWork_signal()),this,SLOT(on_infraredMenu()));
	connect(pMainWnd, SIGNAL(to_sendQmcLoginWork_quit_signal()),this,SLOT(infraredMenu_quit()));
	
	QScreen* pScreen; pScreen = QApplication::primaryScreen();

	connect(pScreen, &QScreen::geometryChanged, this, &CQmcLogin::refResolution);

	//
	memset(&m_var, 0, sizeof(m_var));
	//memset(&m_tmpCntDisplays, 0, sizeof(m_tmpCntDisplays));
	//memset(&this->m_smLoginVar, 0, sizeof(m_smLoginVar));


	//
	if (!pProcInfo->m_var.b_app_showNormal) {
		//默认全屏
		this->showMaximized();
	}


	//
	initControl();


	//connect(ui->loginBtn, SIGNAL(clicked(bool)), this, SLOT(onLoginOkclicked(bool)));
 	//connect(winSerConfig, SIGNAL(signal_select_load), this, SLOT());

	this->setWindowIcon(QIcon(":/Resources/Images/Login/qmClient.png"));

	//
	if (pQyMc->appParams.iSeqNoSelected_appObjPrefix) {
		//
		int  i;
		for (i = 0; i < mycountof(m_var.m_smLoginVar.m_tmpCntDisplays.mems); i++) {
			if (m_var.m_smLoginVar.m_tmpCntDisplays.mems[i].index == pQyMc->appParams.iSeqNoSelected_appObjPrefix) {
				//ui->editServer->setCurrentIndex(i);
				break;
			}
		}
	}
	if (pQyMc->appParams.usrName[0]) {
		//ui->editUserAccount->setText(QString::fromUtf16((char16_t*)pQyMc->appParams.usrName));
	}
	if (pQyMc->appParams.passwd[0]) {
		//ui->editPassword->setText(QString::fromUtf16((char16_t*)pQyMc->appParams.passwd));
	}
	if (pQyMc->appParams.usrName[0] && pQyMc->appParams.passwd[0]) {
		//ui->checkBox_autoLogon->setChecked(true);
	}


	//
	m_pWinTimer = new QTimer(this);
	connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(on_timer_winMethod()));
	m_pWinTimer->setInterval(100);
	m_pWinTimer->start();


	//
	//ui->label_status->setText("");


	//

	traceLog((TCHAR*)_T("qmcLogin::CQmcLogin() called"));



	sheetBackgroundImage();



	ui->label_status->setText(u8"终端设备认证中...");




}



//刷新分辨率
void CQmcLogin::refResolution()
{

	sheetBackgroundImage();
}


void CQmcLogin::sheetBackgroundImage()
{
	QRect rc = QApplication::primaryScreen()->geometry();

	if (rc.width() > 3500) {
		ui->winWidget->setStyleSheet("background-image:url(':/Resources/Images/Sm/t16@2x.png');background-repeat:no-repeat;");
		ui->btn_img->setStyleSheet("background-image:url(':/Resources/Images/Sm/t17@2x.png');background-repeat:no-repeat;border:none");
		ui->label_status->setStyleSheet("font-size:68px;color:#1F3D5B;background:none;font-family: Microsoft YaHei;");
		ui->label_title->setStyleSheet("font-size:136px;color:#2C9AD0;font-weight:bold;background:none;font-family: Microsoft YaHei;");

	}
	else {
		ui->winWidget->setStyleSheet("background-image:url(':/Resources/Images/Sm/t16.png');background-repeat:no-repeat;");
		ui->btn_img->setStyleSheet("background-image:url(':/Resources/Images/Sm/t17.png');background-repeat:no-repeat;border:none");
		ui->label_status->setStyleSheet("font-size:34px;color:#1F3D5B;background:none;font-family: Microsoft YaHei;");
		ui->label_title->setStyleSheet("font-size:68px;color:#2C9AD0;font-weight:bold;background:none;font-family: Microsoft YaHei;");
		
		ui->btn_img->setFixedSize(318,314);
	}
}
//显示提示窗
void CQmcLogin::showHint(QString msg, QString fontColor, qint64 out_time) {

	NoticeWidget::showNotice(this, msg, fontColor, out_time);

}

CQmcLogin::~CQmcLogin()
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	Var_ca_dev_qmc* pVc = &pProcInfo->m_var.ctxSm.ca_dev;
	//
#if 0
	if (m_smLoginVar.m_hThread_ca) {
		pVc->toolCa.bNeedQuit = true;
		//
		waitForObject(&m_smLoginVar.m_hThread_ca, INFINITE);
	}
#endif
	//
	smLogin_clean(m_var.m_smLoginVar, &pProcInfo->m_var.ctxSm);


	

	//
	delete ui;

	if (m_pWinTimer)
	{
		delete m_pWinTimer;
		m_pWinTimer = nullptr;
	}
	
	if (m_pInfraredMenu)
	{
		delete m_pInfraredMenu;
		m_pInfraredMenu= nullptr;
	}



	if (winTitle)
	{
		delete winTitle;
		winTitle = nullptr;
	}
#if  0
	if (winSerConfig)
	{
		delete winSerConfig;
		winSerConfig = nullptr;
	}
#endif

}

void CQmcLogin::keyPressEvent(QKeyEvent* ev)
{
	if (ev->key() == Qt::Key_Enter || ev->key() == Qt::Key_Return) {
		onLoginOkclicked(true);
	}
	QWidget::keyPressEvent(ev);
}





//显示初始化窗口
void CQmcLogin::on_showDeviceBinding_slots() 
{

	//
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

	//
	setNeedCfgOn_smTerminalInitCfg(true);


	//
	this->accept();
}
	


//显示菜单
void CQmcLogin::on_infraredMenu() 
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



	}


}





//
void CQmcLogin::on_timer_winMethod()
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	Var_ca_dev_qmc* pVc = &pProcInfo->m_var.ctxSm.ca_dev;

	//
	if (!m_var.bDone_AutoLogon) {
		m_var.bDone_AutoLogon = true;
		//
		/*if (ui->checkBox_autoLogon->isChecked()) {
			this->onLoginOkclicked(true);
		}*/
	}

	//
	showStatus(pVc->tStatusBuf);

	bool  bNeedAccept = false;
	smLogin_onTimer((HWND)this->winId(), &m_var,  &pProcInfo->m_var.ctxSm,  &bNeedAccept);
	if (bNeedAccept) {
		this->accept();
	}

	return;
}














void CQmcLogin::onLoginOkclicked(bool b0)
{
	HWND  hWnd = (HWND)this->winId();

	bool bOk_doLogin = false;
	login_do_onLoginOkclicked(hWnd,  m_var,  m_var.m_smLoginVar,  b0, &bOk_doLogin);
	if (!bOk_doLogin) return;

	//	
	this->accept();
}



void CQmcLogin::onSelectBtnClicked(bool)
{
	int  ret = -1;
	this->hide();
	//
#if  0
	if (!winSerConfig) {
		winSerConfig = new WinSerConfig(nullptr);
		winSerConfig->m_var.plogin = this;
		winSerConfig->init();
	}
	winSerConfig->show();
	ret = winSerConfig->exec();
#endif
	WinSerConfig dlg;
	dlg.m_var.plogin = this;
	dlg.init();
	dlg.show();
	dlg.exec();


	//
	load_select();
	//
	this->done(100);
}


void CQmcLogin::initControl()
{
	CCtxQyMc* pQyMc = g_pQyMc;

	//
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground, true);
	getRegName();
	ui->winWidget->installEventFilter(this);
	QFile file(":/Resources/QSS/CQmcLogin111.css");
	file.open(QFile::ReadOnly);
	if (file.isOpen())
	{
		this->setStyleSheet("");
		QString qsstyleSheet = QLatin1String(file.readAll());
		this->setStyleSheet(qsstyleSheet);
	}
	file.close();
	//connect(ui->selectBtn, &QPushButton::clicked, this, &CQmcLogin::onSelectBtnClicked);

	//

	//ui->icoBtn->setIconSize(QSize(80, 200));
	//
	winTitle = new WinTitle(this);
	winTitle->setButtonType(MIN_BUTTON);
	winTitle->move(0, 0);
	connect(winTitle, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
	connect(winTitle, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));
	//
	//ui->editServer->clear();
	const QString&& pathConf = QApplication::applicationDirPath() + "/" + QString("qyconf.ini");
	QSettings settingsConf(pathConf, QSettings::IniFormat);
	QStringList groupList = settingsConf.childGroups();
	
	//
	if (pQyMc->appParams.serverAddr[0] && pQyMc->appParams.port) {
		if (pQyMc->appParams.iSeqNoSelected_appObjPrefix >= 0 && pQyMc->appParams.iSeqNoSelected_appObjPrefix < CONST_maxOfVideoConferencingServers) {
			int  index = pQyMc->appParams.iSeqNoSelected_appObjPrefix;
			//
			if  (  !m_var.cntCfgs.mems[index].cntName[0]) {
				_sntprintf(m_var.cntCfgs.mems[index].cntName, mycountof(m_var.cntCfgs.mems[index].cntName), _T("%d"), index);
			}
			//
			safeStrnCpy(pQyMc->appParams.serverAddr, m_var.cntCfgs.mems[index].cntAddr, mycountof(m_var.cntCfgs.mems[index].cntAddr));
			m_var.cntCfgs.mems[index].port = pQyMc->appParams.port;
		}
	}


	//
	load_select();

	

	
	//
	HKEY			hKeyRoot0 = HKEY_CURRENT_USER;
	TCHAR			tQnmSchedulerBuf[256] = _T("");
	TCHAR			tBuf[128];
	//
	if (!m_var.iSeqNoSelected)
		_sntprintf(tQnmSchedulerBuf, mycountof(tQnmSchedulerBuf), _T("%s"), CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler));
	else
		_sntprintf(tQnmSchedulerBuf, mycountof(tQnmSchedulerBuf), _T("%s\\%d"), CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), m_var.iSeqNoSelected);

	//
	if (qyGetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_ucbSavePasswd), (char*)tBuf, sizeof(tBuf), mynull))  tBuf[0] = 0;
	//if (_ttol(tBuf))  ui->checkBox_savePasswd->setChecked(true);

	//
	if (qyGetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_ucbAutoLogon), (char*)tBuf, sizeof(tBuf), mynull))  tBuf[0] = 0;
	//if (_ttol(tBuf))  ui->checkBox_autoLogon->setChecked(true);


	if (qyGetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_usr), (char*)tBuf, sizeof(tBuf), mynull))tBuf[0] = 0;
	//ui->editUserAccount->setText(QString::fromUtf16((char16_t*)tBuf));

	/*if (ui->checkBox_savePasswd->isChecked()) {
		if (qyGetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_passwd), (char*)tBuf, sizeof(tBuf), null))tBuf[0] = 0;
		ui->editPassword->setText(QString::fromUtf16((char16_t*)tBuf));
	}*/

	return;
}




void CQmcLogin::onButtonMinClicked()
{
	showMinimized();
}

void CQmcLogin::onButtonCloseClicked()
{
	close();
}
void CQmcLogin::mouseMoveEvent(QMouseEvent* e)
{
	/*if (m_mousePressed && (e->buttons() == Qt::LeftButton))
	{
		if (mousePoint != QPoint(0, 0))
		{
			move(e->globalPos() - mousePoint);
		}
		e->accept();
	}*/
}
void CQmcLogin::mousePressEvent(QMouseEvent* e)
{
	/*if (e->button() == Qt::LeftButton)
	{
		m_mousePressed = true;
		mousePoint = e->globalPos() - this->pos();
		e->accept();
	}*/

	if (e->button() == Qt::RightButton)
	{
		//
		if (!m_pInfraredMenu)
		{
			m_pInfraredMenu = new CInfraredDialogMenu(this, "login");
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
void CQmcLogin::mouseReleaseEvent(QMouseEvent*)
{
	//m_mousePressed = false;
}

void CQmcLogin::Infrared_up()
{
	if (m_pInfraredMenu)
	{
		m_pInfraredMenu->Infrared_up();
		return;
	}
	return;
}

void CQmcLogin::Infrared_down()
{
	if (m_pInfraredMenu) 
	{
		m_pInfraredMenu->Infrared_down();
		return;
	}
	return;
}

//菜单关闭
void CQmcLogin::infraredMenu_quit() 
{
	if (!m_pInfraredMenu)
	{
		return;
	}

	

		m_pInfraredMenu->close();
		if (m_pInfraredMenu)
		{
			delete m_pInfraredMenu;
			m_pInfraredMenu = nullptr;
		}

	

	return;
}

//确认键
void CQmcLogin::Infrared_ok(QString objname) 
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
		//调试窗
		if (objname == "menuDebug") {
			m_pInfraredMenu->on_menuDebug_clicked();
		}
		return;
	}
	return;
}

//显示调试窗
void CQmcLogin::on_showDebug_slots() {
	
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





void CQmcLogin::load_select() {

	//ui->editServer->clear();
//TMP_cnt_displays cntDisplay;
	int  i;
	//
	int  cnt = 0;
	memset(&m_var.m_smLoginVar.m_tmpCntDisplays,0,sizeof(m_var.m_smLoginVar.m_tmpCntDisplays));
	for (i = 0; i < CONST_maxOfVideoConferencingServers; i++) {
		if (m_var.cntCfgs.mems[i].cntName[0] != _T('\0')) {
			safeTcsnCpy(m_var.cntCfgs.mems[i].cntName, m_var.m_smLoginVar.m_tmpCntDisplays.mems[cnt].displayName,mycountof(m_var.m_smLoginVar.m_tmpCntDisplays.mems[cnt].displayName));
			m_var.m_smLoginVar.m_tmpCntDisplays.mems[cnt].index = i;
			cnt++;
		}
		continue;		
	}



	//
	for (int i = 0; i < CONST_maxOfVideoConferencingServers; i++) {

		if (m_var.m_smLoginVar.m_tmpCntDisplays.mems[i].displayName[0] == _T('\0')) {
			break;
		}
		//ui->editServer->addItem(QString::fromStdWString(m_tmpCntDisplays.mems[i].displayName));
	}
}


//
void CQmcLogin::on_editServer_currentIndexChanged(int index)
{
	int  ii = 0;

	//
	CCtxQyMc* pQyMc = g_pQyMc;
	HKEY			hKeyRoot0 = HKEY_CURRENT_USER;
	TCHAR			tQnmSchedulerBuf[256] = _T("");
	TCHAR			tBuf[128];

	//
	m_var.iSeqNoSelected = index;

	//
	if (!m_var.iSeqNoSelected)
		_sntprintf(tQnmSchedulerBuf, mycountof(tQnmSchedulerBuf), _T("%s"), CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler));
	else
		_sntprintf(tQnmSchedulerBuf, mycountof(tQnmSchedulerBuf), _T("%s\\%d"), CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), m_var.iSeqNoSelected);

	//
	if (qyGetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_usr), (char*)tBuf, sizeof(tBuf), mynull))tBuf[0] = 0;
	//ui->editUserAccount->setText(QString::fromUtf16((char16_t*)tBuf));

	/*if (ui->checkBox_savePasswd->isChecked()) {
		if (qyGetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_passwd), (char*)tBuf, sizeof(tBuf), null))tBuf[0] = 0;
		ui->editPassword->setText(QString::fromUtf16((char16_t*)tBuf));
	}*/

	return;
}



void CQmcLogin::getRegName() {

	QY_MC* pQyMc = g_pQyMc;
	HKEY		hKeyRoot0 = HKEY_CURRENT_USER;
	TCHAR		tQnmSchedulerBuf[256] = _T("");
	TCHAR		tBuf1[256] = _T("");
	TCHAR		tBuf2[256] = _T("");
	TCHAR		tBuf3[256] = _T("");
	TCHAR		tBuf4[256] = _T("");
	char		buf[256] = "";
	int			i = 0;

	TMP_cntCfgs  cntCfgs;
	memset(&cntCfgs, 0, sizeof(cntCfgs));

	for (i = 0; i < CONST_maxOfVideoConferencingServers; i++) {
		if (!i)  _sntprintf(tQnmSchedulerBuf, mycountof(tQnmSchedulerBuf), _T("%s"), CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler));

		else  _sntprintf(tQnmSchedulerBuf, mycountof(tQnmSchedulerBuf), _T("%s\\%d"), CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), i);

		tBuf2[0] = 0;
		tBuf3[0] = 0;
		tBuf4[0] = 0;
		qyGetRegCfg1W(&pQyMc->env, hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_cntName), tBuf2, mycountof(tBuf2), 0);
		qyGetRegCfg1W(&pQyMc->env, hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_cntPort), tBuf3, mycountof(tBuf3), 0);
		qyGetRegCfg1W(&pQyMc->env, hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_cntAddr), tBuf4, mycountof(tBuf4), 0);
		safeTcsnCpy(tBuf2, cntCfgs.mems[i].cntName, mycountof(cntCfgs.mems[i].cntName));
		myTChar2Utf8(tBuf4, cntCfgs.mems[i].cntAddr, mycountof(cntCfgs.mems[i].cntAddr));
		cntCfgs.mems[i].port = _ttol(tBuf3);

	}
	m_var.cntCfgs = cntCfgs;
}


//
int  CQmcLogin::showStatus(TCHAR* str)
{
	if (!str)str = (TCHAR*)_T("");

	//
	ui->label_status->setText(QString::fromUtf16((const char16_t*)str));

	//
	return  0;
}

