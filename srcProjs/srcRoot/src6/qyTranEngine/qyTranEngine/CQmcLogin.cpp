
#include "CQmcLogin.h"
#include "ui_CQmcLogin.h"
#include "CMainFrame.h" 
#include	"ctxQmc_qt.h"

#include    <qdir.h>

//
CQmcLogin::CQmcLogin(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::CQmcLogin)
{
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("qmcLogin::CQmcLogin() enters"));
#endif

	ui->setupUi(this);
	
	//
	memset(&m_var, 0, sizeof(m_var));
	memset(&m_tmpCntDisplays, 0, sizeof(m_tmpCntDisplays));

	//
	CCtxQyMc* pQyMc = g_pQyMc;

	//
	initControl();


	connect(ui->loginBtn, SIGNAL(clicked(bool)), this, SLOT(onLoginOkclicked(bool)));
	//connect(winSerConfig, SIGNAL(signal_select_load), this, SLOT());

	this->setWindowIcon(QIcon(":/Resources/Images/Login/qmClient.png"));

	//
	if (pQyMc->appParams.iSeqNoSelected_appObjPrefix) {
		//
		int  i;
		for (i = 0; i < mycountof(m_tmpCntDisplays.mems); i++) {
			if (m_tmpCntDisplays.mems[i].index == pQyMc->appParams.iSeqNoSelected_appObjPrefix) {
				ui->editServer->setCurrentIndex(i);
				break;
			}
		}
	}
	if (pQyMc->appParams.usrName[0]) {
		ui->editUserAccount->setText(QString::fromUtf16((char16_t*)pQyMc->appParams.usrName));
	}
	if (pQyMc->appParams.passwd[0]) {
		ui->editPassword->setText(QString::fromUtf16((char16_t*)pQyMc->appParams.passwd));
	}
	if (pQyMc->appParams.usrName[0] && pQyMc->appParams.passwd[0]) {
		ui->checkBox_autoLogon->setChecked(true);
	}


	//
	m_pWinTimer = new QTimer(this);
	connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(on_timer_winMethod()));
	m_pWinTimer->setInterval(100);
	m_pWinTimer->start();



#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("qmcLogin::CQmcLogin() called"));

	//
	//
	int  ii = 0;

#endif

}

CQmcLogin::~CQmcLogin()
{
	delete ui;

	if (m_pWinTimer)
	{
		delete m_pWinTimer;
		m_pWinTimer = nullptr;
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

//
void CQmcLogin::on_timer_winMethod()
{
	if (!m_var.bDone_AutoLogon) {
		m_var.bDone_AutoLogon = true;
		//
		if (ui->checkBox_autoLogon->isChecked()) {
			this->onLoginOkclicked(true);
		}
	}
	return;
}



void CQmcLogin::onLoginOkclicked(bool)
{
	//
	 int curIndex = ui->editServer->currentIndex();
	//
	QString serviceNameLogin = ui->editServer->currentText();
	QString UserName = ui->editUserAccount->text();
	QString Password = ui->editPassword->text();
	if (UserName.trimmed().isEmpty()) {
		ui->loginTip->setText(u8"请输入用户名!");
		//QToolTip::showText(this->mapToGlobal(QPoint(400, 168)), QStringLiteral("请输入用户名!"), this, QRect(0, 0, 120, 100), 2000);  
		return;
	}
	if (Password.trimmed().isEmpty()) {
		ui->loginTip->setText(u8"请输入密码!");
		//QToolTip::showText(this->mapToGlobal(QPoint(400, 204)), QStringLiteral("请输入密码!"), this, QRect(0, 0, 120, 100), 2000); 
		return;
	}

#if  0
	QString ServerIp = "";
	QString port = "8768";

	const QString&& pathConf = QApplication::applicationDirPath() + "/" + QString("qyconf.ini");
	QSettings settingsConf(pathConf, QSettings::IniFormat);
	QStringList groupList = settingsConf.childGroups();
	foreach(QString group, groupList)
	{
		QString serviceName = settingsConf.value(QString("/%1/%2").arg(group).arg("serviceName")).toString();
		if (serviceNameLogin == serviceName) {
			QString ipAddr = settingsConf.value(QString("/%1/%2").arg(group).arg("ipAddr")).toString();
			QString addr1 = settingsConf.value(QString("/%1/%2").arg(group).arg("addr1")).toString();
			QString addr2 = settingsConf.value(QString("/%1/%2").arg(group).arg("addr2")).toString();
			QString portConfig = settingsConf.value(QString("/%1/%2").arg(group).arg("port")).toString();
			if (!ipAddr.trimmed().isEmpty()) {
				ServerIp = ipAddr.trimmed();
			}
			else if (addr1.trimmed().isEmpty()) {
				ServerIp = addr1.trimmed();
			}
			else if (addr2.trimmed().isEmpty()) {
				ServerIp = addr2.trimmed();
			}
			if (!portConfig.isEmpty()) {
				port = portConfig;
			}
			break;
		}
	}
#endif

	int i = 1;
	//
	char servIp[128];
	int  port;
	//myTChar2Utf8(QStringToTCHAR(ServerIp), servIp, mycountof(servIp));

	if (curIndex < 0 || curIndex >= CONST_maxOfVideoConferencingServers)  return;
	int  tmpIndex = this->m_tmpCntDisplays.mems[curIndex].index;
	m_var.iSeqNoSelected = tmpIndex;
	safeStrnCpy(m_var.cntCfgs.mems[tmpIndex].cntAddr, servIp, mycountof(servIp));
	port = m_var.cntCfgs.mems[tmpIndex].port;
	//
#ifdef  __DEBUG__
	//safeStrnCpy((char*)"bbs.qycx.com", servIp, mycountof(servIp));
#endif

	//
	//safeStrnCpy(servIp, m_var.cntCfg[m_var.iSeqNoSelected].cntIp, mycountof(m_var.cntCfg[m_var.iSeqNoSelected].cntIp));
	safeStrnCpy(servIp, m_var.cntCfg[m_var.iSeqNoSelected].cntAddrs[0], mycountof(m_var.cntCfg[m_var.iSeqNoSelected].cntAddrs[0]));
	m_var.cntCfg[m_var.iSeqNoSelected].usCntPort = port;

	//
	if (ui->checkBox_autoLogon->isChecked()) {
		m_var.ucbAutoLogon = true;
	}
	else {
		m_var.ucbAutoLogon = false;
	}

	if (ui->checkBox_savePasswd->isChecked()) {
		m_var.ucbSavePasswd = true;
	}
	else {
		m_var.ucbSavePasswd = false;
	}
	//
#if 0
	if (dlgMcClientLogon_OnOK_qt(this, QStringToTCHAR(UserName), QStringToTCHAR(Password)) != 0) {
		return;
	}
#endif
	if (0 != doMcClientLogonOK(this, servIp,  QStringToTCHAR(UserName), QStringToTCHAR(Password))) {
		QString serverTip = u8"登录失败,可能是用户名或密码错误 IP:" + QString::fromUtf8(servIp) + " :" + QString::number(port);
		ui->loginTip->setText(serverTip);
		ui->loginTip->setWordWrap(true);
		//QToolTip::showText(this->mapToGlobal(QPoint(60, 234)), serverTip, this, QRect(0, 0, 120, 100), 2000);
		return;
	}
	
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
	QFile file(":/Resources/QSS/CQmcLogin.css");
	file.open(QFile::ReadOnly);
	if (file.isOpen())
	{
		this->setStyleSheet("");
		QString qsstyleSheet = QLatin1String(file.readAll());
		this->setStyleSheet(qsstyleSheet);
	}
	file.close();
	connect(ui->selectBtn, &QPushButton::clicked, this, &CQmcLogin::onSelectBtnClicked);
	//
	QString part0 = QString::fromUtf16((char16_t*)pQyMc->cfg.qyMcTitle_part0);
	ui->LabelTitle2->setText(part0);
	if (part0.size() == 6) {
		ui->LabelTitle2->setStyleSheet(" font-size:40px;color:#ffffff;font - weight: bold;");
	}
	else if (part0.size()  == 5) {
		ui->LabelTitle2->setStyleSheet(" font-size:45px;color:#ffffff;font - weight: bold;");
	}
	else if (part0.size()  == 4) {
		ui->LabelTitle2->setStyleSheet(" font-size:50px;color:#ffffff;font - weight: bold;");
	}
	else if (part0.size()  == 3) {
		ui->LabelTitle2->setStyleSheet(" font-size:55px;color:#ffffff;font - weight: bold;");
	}
	else if (part0.size()  == 2) {
		ui->LabelTitle2->setStyleSheet(" font-size:60px;color:#ffffff;font - weight: bold;");
	}

	QString part1 = QString::fromUtf16((char16_t*)pQyMc->cfg.qyMcTitle_part1);
	ui->LabelTitle->setText(part1);
	if (part1.size() == 6) {
		ui->LabelTitle->setStyleSheet(" font-size:40px;color:#ffffff;font - family:  KaiTi;font - weight: bold;");
	}
	else if (part1.size() == 5) {
		ui->LabelTitle->setStyleSheet(" font-size:45px;color:#ffffff;font - family:  KaiTi;font - weight: bold;");
	}
	else if (part1.size() == 4) {
		ui->LabelTitle->setStyleSheet(" font-size:50px;color:#ffffff;font - family:  KaiTi;font - weight: bold;");
	}
	else if (part1.size() == 3) {
		ui->LabelTitle->setStyleSheet(" font-size:55px;color:#ffffff;font - family:  KaiTi;font - weight: bold;");
	}
	else if (part1.size() == 2) {
		ui->LabelTitle->setStyleSheet(" font-size:60px;color:#ffffff;font - family:  KaiTi;font - weight: bold;");
	}

	
	
	
	//
	ui->icoBtn->setIcon(QIcon(":/Resources/Images/Login/qmLogin.png"));
	//ui->icoBtn->setIconSize(QSize(80, 200));
	//
	winTitle = new WinTitle(this);
	winTitle->setButtonType(MIN_BUTTON);
	winTitle->move(0, 0);
	connect(winTitle, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
	connect(winTitle, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));
	//
	ui->editServer->clear();
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
	if (qyGetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_ucbSavePasswd), (char*)tBuf, sizeof(tBuf), null))  tBuf[0] = 0;
	if (_ttol(tBuf))  ui->checkBox_savePasswd->setChecked(true);

	//
	if (qyGetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_ucbAutoLogon), (char*)tBuf, sizeof(tBuf), null))  tBuf[0] = 0;
	if (_ttol(tBuf))  ui->checkBox_autoLogon->setChecked(true);


	if (qyGetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_usr), (char*)tBuf, sizeof(tBuf), null))tBuf[0] = 0;
	ui->editUserAccount->setText(QString::fromUtf16((char16_t*)tBuf));

	if (ui->checkBox_savePasswd->isChecked()) {
		if (qyGetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_passwd), (char*)tBuf, sizeof(tBuf), null))tBuf[0] = 0;
		ui->editPassword->setText(QString::fromUtf16((char16_t*)tBuf));
	}

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
	if (m_mousePressed && (e->buttons() == Qt::LeftButton))
	{
		if (mousePoint != QPoint(0, 0))
		{
			move(e->globalPos() - mousePoint);
		}
		e->accept();
	}
}
void CQmcLogin::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton)
	{
		m_mousePressed = true;
		mousePoint = e->globalPos() - this->pos();
		e->accept();
	}
}
void CQmcLogin::mouseReleaseEvent(QMouseEvent*)
{
	m_mousePressed = false;
}



void CQmcLogin::load_select() {

	ui->editServer->clear();
//TMP_cnt_displays cntDisplay;
	int  i;
	//
	int  cnt = 0;
	memset(&m_tmpCntDisplays,0,sizeof(m_tmpCntDisplays));
	for (i = 0; i < CONST_maxOfVideoConferencingServers; i++) {
		if (m_var.cntCfgs.mems[i].cntName[0] != _T('\0')) {
			safeTcsnCpy(m_var.cntCfgs.mems[i].cntName, m_tmpCntDisplays.mems[cnt].displayName,mycountof(m_tmpCntDisplays.mems[cnt].displayName));
			m_tmpCntDisplays.mems[cnt].index = i;
			cnt++;
		}
		continue;		
	}



	//
	for (int i = 0; i < CONST_maxOfVideoConferencingServers; i++) {

		if (m_tmpCntDisplays.mems[i].displayName[0] == _T('\0')) {
			break;
		}
		ui->editServer->addItem(QString::fromStdWString(m_tmpCntDisplays.mems[i].displayName));
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
	if (qyGetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_usr), (char*)tBuf, sizeof(tBuf), null))tBuf[0] = 0;
	ui->editUserAccount->setText(QString::fromUtf16((char16_t*)tBuf));

	if (ui->checkBox_savePasswd->isChecked()) {
		if (qyGetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_passwd), (char*)tBuf, sizeof(tBuf), null))tBuf[0] = 0;
		ui->editPassword->setText(QString::fromUtf16((char16_t*)tBuf));
	}

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

