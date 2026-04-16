
#include "stdafx.h"
#include "DlgAvAccept.h"
#include "CMainFrame.h"
#include "ctxQmc_qt.h"
#include <QMediaPlayer>
#include <qmediaplaylist.h>

#include	"myDb.h"
#include	"funcsForIsCliHelp.h"


//
#define SHADOW_WIDTH 1 // 阴影边框宽度;
//
int viewDlgAvAccept()
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	HWND  hMainWnd = pQyMc->gui.hMainWnd;
	CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
	if (pMainWnd == null)goto  errLabel;
	QY_MC_mainWndVar& var = pMainWnd->var.common;

	//
	if (IsWindow(var.notifyTaskStatus.hTool_dlgAvAccept)) {
		SetForegroundWindow(var.notifyTaskStatus.hTool_dlgAvAccept);
		iErr = 0;  goto  errLabel;
	}
	int d_WIDTH = 348;
	int d_HEIGHT = 164;
	//
	DlgAvAccept* dlg = new DlgAvAccept();
	QRect rc = QApplication::desktop()->screenGeometry();	
	int rx = rc.width() - d_WIDTH - 60;
	int ry = rc.height() - d_HEIGHT -60;
	QRect r = QRect(rx, ry, d_WIDTH, d_HEIGHT);
	dlg->setGeometry(r);
	dlg->show();

	var.notifyTaskStatus.hTool_dlgAvAccept = (HWND)dlg->winId();

	iErr = 0;
errLabel:
	return  iErr;
}


//
int  closeDlgAvAccept()
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	HWND  hMainWnd = pQyMc->gui.hMainWnd;
	CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
	if (pMainWnd == null)goto  errLabel;
	QY_MC_mainWndVar& var = pMainWnd->var.common;

	//
	if (IsWindow(var.notifyTaskStatus.hTool_dlgAvAccept)) {
		DlgAvAccept* dlg = (DlgAvAccept*)getObjAddr(var.notifyTaskStatus.hTool_dlgAvAccept);
		//
		if (dlg != NULL) {
			//
			delete  dlg;
		}
		//
		var.notifyTaskStatus.hTool_dlgAvAccept = null;
	}

	//
	iErr = 0;
errLabel:
	return  iErr;
}

//
bool  bSoundCardExists()
{
	bool  bRet = false;
	int n = waveOutGetNumDevs();
	if (n != 0) {
		bRet = true;
	}
	//
	if (!bRet) {
		showInfo_open0(0, 0, _T("Note: bSoundCardExists returns false"));
	}
	//
	return  bRet;
}

//
DlgAvAccept::DlgAvAccept(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//
	memset(&m_var, 0, sizeof(m_var));

	//
	this->setAttribute(Qt::WA_DeleteOnClose);

	//设置播放的声音	
	this->m_pMediaPlayer = new QMediaPlayer(this);		

	//QFile* music = new QFile(":/Resources/Sounds/recieve.mp3");
	//music->open(QIODevice::ReadOnly);
	//
	this->m_pMediaPlaylist = new QMediaPlaylist;

	//
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();

	//
	QString installDir = QString::fromUtf16((char16_t*)pProcInfo->m_var.installDir_qt);// getInstallDir_qt();
	QString musicFile = installDir + "resource/Sounds/receive.mp3";
	
	//
	if (!pProcInfo->status.avStatus.bExists_meeting) {
		if (bFileExists((TCHAR*)musicFile.utf16())) {
			//
			if (bSoundCardExists()) {
				//
				bool bRet = m_pMediaPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(musicFile)));// "C:/tttbbb/124/recieve.mp3"));
				//
				//this->m_pMediaPlayer->setMedia(0, music);
				this->m_pMediaPlayer->setPlaylist(this->m_pMediaPlaylist);
				this->m_pMediaPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
				//

				this->m_pMediaPlayer->setVolume(50);
				this->m_pMediaPlayer->play();
			}
		}
	}
	
	
	
	memset(&m_var, 0, sizeof(m_var));

	//
	HWND  m_hWnd = (HWND)this->winId();
	// TODO:  Add extra initialization here
	long  lStyle = 0;
	lStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	lStyle &= ~(WS_CAPTION | WS_THICKFRAME);
	//  lStyle  |=  WS_BORDER;
	SetWindowLong(m_hWnd, GWL_STYLE, lStyle);

	//
	//::ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	SetWindowLong(m_hWnd, GWL_EXSTYLE, WS_EX_TOOLWINDOW);
	SetWindowLong(m_hWnd, GWL_EXSTYLE, WS_EX_APPWINDOW);

	//
	::SetMenu(m_hWnd, NULL);

	//MoveWindow(0, 0, 0, 0);

	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);

	//
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

		//
	QY_MESSENGER_ID  idInfo_logicalPeer;
	QY_MESSENGER_ID  idInfo_from;
	TCHAR  talkerDesc_peer[128];
	TCHAR  talkerDesc_from[128];
	TCHAR  tBuf[128]  =  _T(  ""  );
	TCHAR  tBuf_grp[128] = _T("");

	if  (  0 == getAvCallerInfo(&idInfo_logicalPeer, &idInfo_from)  )  {
		if (idInfo_logicalPeer.ui64Id == idInfo_from.ui64Id) {

			getTalkerDesc( idInfo_from, talkerDesc_from, mycountof(talkerDesc_from), null, 0);
			_sntprintf(tBuf_grp, mycountof(tBuf_grp), _T("%s 视频通话"), talkerDesc_from);
			//
			ui.btnFaceIcon->setIcon(QIcon(":/Resources/Images/WinMain/Av_person.png"));
		}
		else {
			unsigned  int  uiObjType = 0;
			TCHAR grpName[128];
			QY_MESSENGER_ID  idInfo_creator;
			getTalkerDesc( idInfo_logicalPeer, &uiObjType,grpName,mycountof(grpName),&idInfo_creator,null,0,null,0,null,0);
			
			getTalkerDesc(idInfo_from, talkerDesc_from, mycountof(talkerDesc_from), null, 0);
			//_sntprintf(tBuf, mycountof(tBuf), _T("%s: %s 视频通话"), grpName,  talkerDesc_from);
			_sntprintf(tBuf, mycountof(tBuf), _T("邀请你视频通话"));
			_sntprintf(tBuf_grp, mycountof(tBuf_grp), _T("%s: %s "), grpName,talkerDesc_from);
			
			// CONST_objType_imGrp 1101 
			if (uiObjType == CONST_objType_imGrp) {
				ui.btnFaceIcon->setIcon(QIcon(":/Resources/Images/WinMain/Av_Group.png"));
			}
		}
	}
	m_var.id_logicalPeer = idInfo_logicalPeer.ui64Id;

	//
	QString str = QString::fromUtf16((ushort*)tBuf);
	ui.hint->setText(str);
	QString str_grp = QString::fromUtf16((ushort*)tBuf_grp);
	ui.hint_name->setText(str_grp);
	ui.btnAccept->setText("");
	ui.btnCancel->setText(""); 
	ui.btnAccept->setIcon(QIcon(":/Resources/Images/Video/accept.png"));
	ui.btnCancel->setIcon(QIcon(":/Resources/Images/Video/reject.png"));


	


	QFile file(":/Resources/QSS/DlgAvAccept.css");
	if (file.open(QFile::ReadOnly)) {
		QString stylesheet = QLatin1String(file.readAll());
		setStyleSheet(stylesheet);
		file.close();
	}	

	//
	m_pWinTimer = new QTimer(this);
	connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(on_timer_winMethod()));
	m_pWinTimer->setInterval(100);
	m_pWinTimer->start();

}

DlgAvAccept::~DlgAvAccept()
{
	int  ii = 0;

	//
	if (m_pWinTimer)
	{
		delete m_pWinTimer;
		m_pWinTimer = nullptr;
	}

	//释放音频对象
	if (m_pMediaPlayer != nullptr)
	{
		delete m_pMediaPlayer;
		m_pMediaPlayer = nullptr;
	}
	if (m_pMediaPlaylist != nullptr) {
		delete m_pMediaPlaylist;
		m_pMediaPlaylist = nullptr;
	}
}


bool DlgAvAccept::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	Q_UNUSED(eventType);
	MSG* msg = reinterpret_cast<MSG*>(message);
	UINT m = msg->message;
	if (m == WM_COMMAND || m == CONST_qyWm_comm || m == CONST_qyWm_postComm)
	{
		return postMessageQt(msg, result);
	}
	/*else if (m == WM_NCHITTEST)
	{
		return dealHTEvent((MSG*)message,result);
	}*/
	return QWidget::nativeEvent(eventType, message, result);

}

bool DlgAvAccept::postMessageQt(MSG* message, long* result)
{
	//
		if (message->message == CONST_qyWm_comm)
	{
	//
	HWND  hMainWnd = (HWND)this->winId();
	//
	QY_WMBUF_COMM* pWmBuf = (QY_WMBUF_COMM*)message->lParam;
	if (message->wParam == CONST_qyWmParam_getObjAddr)
	{
		pWmBuf->u.getObjAddr.pObjAddr = this;
		*result = CONST_qyWmRc_ok;
		return  true;
	}
	// 
	}

	return  false;

}

bool DlgAvAccept::bQuitDlg(int iVal)
{
	m_var.bQuit = true;

	close();

	return  true;
}

int DlgAvAccept::tryToAutoAccept()
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	QM_dbFuncs& g_dbFuncs = *pQyMc->p_g_dbFuncs;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	FUNCS_for_isCliHelp* pFuncs = (FUNCS_for_isCliHelp*)pProcInfo->get_pFuncs_for_isCliHelp();

	CQnmDb db;
	if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))goto  errLabel;

		//
		//
		REFRESH_imObjRules_req	req;
		QY_MESSENGER_ID			idInfo_related;
		QY_im_rules imRules;
		QY_imObj_rules rules;

		//  先取全局策略
		idInfo_related.ui64Id = 0;
		if (g_dbFuncs.pf_bGetImObjRulesReq(db.m_pDbMem->pDb, pQyMc->cfg.db.iDbType, _T(""), 0, &idInfo_related, NULL, 0, &req)) {
			pFuncs->pf_imObjRulesReq2ImRules(&req, &imRules);
		}

		QY_MESSENGER_ID idInfo;
		idInfo.ui64Id = m_var.id_logicalPeer;
	//  再取messenger的策略
	if (g_dbFuncs.pf_bGetImObjRulesReq(db.m_pDbMem->pDb, pQyMc->cfg.db.iDbType, _T(""), 0, &idInfo, NULL, 0, &req)) {
		pFuncs->pf_imObjRulesReq2Rules(&req, &idInfo, &rules);
	}

	if (rules.uiCmd_autoAnswer_av == CONST_ruleCmd_permit) {
		this->on_btnAccept_clicked(true);
	}


	iErr = 0;
	errLabel:
	return  iErr;
}


//
	//
void DlgAvAccept::on_timer_winMethod()
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	if (!m_var.bDone_tryToAutoAccept) {
		m_var.bDone_tryToAutoAccept = true;

		tryToAutoAccept();

	}

	//
	if (pProcInfo->status.avStatus.bExists_meeting) {
		if (this->m_pMediaPlayer) {
			this->m_pMediaPlayer->stop();
		}
	}



	//
	return;
}



void DlgAvAccept::on_btnAccept_clicked(bool)
{
	int  ii = 0;
	m_pMediaPlayer->stop();
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();
	HWND  hMainWnd = pQyMc->gui.hMainWnd;
	CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
	QY_MC_mainWndVar& var = pMainWnd->var.common;

	//
	HWND  hTool = (HWND)this->winId();

	//
	int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, var.notifyTaskStatus.iTaskId);
	if (index_taskInfo < 0)  return;

	//
	int  iTaskId_activeTaskAv = 0;
	if (bExists_activeTaskAv(pQyMc,&iTaskId_activeTaskAv,null)) {
		if (iTaskId_activeTaskAv != var.notifyTaskStatus.iTaskId) {
			//
			qyMessageBox(hTool, _T("已有一个会议在进行，不能开始新会议"), _T("qycx.com"), MB_OK, 3, null);
			return;
		}		
		return;
	}
	//
	acceptTaskAv(var.notifyTaskStatus.iTaskId);

	//
	bQuitDlg(0);

	//
	memset(&var.notifyTaskStatus, 0, sizeof(var.notifyTaskStatus));

	//
	return;
}

void DlgAvAccept::on_btnCancel_clicked(bool)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	HWND  hMainWnd = pQyMc->gui.hMainWnd;
	CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
	if (pMainWnd == null)return;
	QY_MC_mainWndVar& var = pMainWnd->var.common;

	int  ii = 0;
	//
	do_cancelTask1(var.notifyTaskStatus.iTaskId, false, _T("gui_notify_doCmd"));


	//
	bQuitDlg(-1);

	//
	memset(&var.notifyTaskStatus, 0, sizeof(var.notifyTaskStatus));

	return;
}


void DlgAvAccept::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QBrush(Qt::white));

	QColor color(0, 0, 0, 30);
	for (int i = 0; i < SHADOW_WIDTH; i++)
	{
		color.setAlpha(120 - qSqrt(i) * 40);
		painter.setPen(color);
		// 方角阴影边框;
	  painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
		// 圆角阴影边框;
		//painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
	}
}

//
void DlgAvAccept::closeEvent(QCloseEvent* ev)
{
	if (!m_var.bQuit) {
		this->hide();
		ev->ignore();
	}
}

//拖拽操作
void DlgAvAccept::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bDrag = true;
		//获得鼠标的初始位置
		mouseStartPoint = event->globalPos();
		//mouseStartPoint = event->pos();
		//获得窗口的初始位置
		windowTopLeftPoint = this->frameGeometry().topLeft();
	}
}

void DlgAvAccept::mouseMoveEvent(QMouseEvent* event)
{
	if (m_bDrag)
	{
		//获得鼠标移动的距离
		QPoint distance = event->globalPos() - mouseStartPoint;
		//QPoint distance = event->pos() - mouseStartPoint;
		//改变窗口的位置
		this->move(windowTopLeftPoint + distance);
	}
}

void DlgAvAccept::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bDrag = false;
	}
}



