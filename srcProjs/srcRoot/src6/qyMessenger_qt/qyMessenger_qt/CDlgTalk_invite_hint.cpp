#include "CDlgTalk_invite_hint.h"
#include <QDebug>
#include "CMainFrame.h"
#include "ctxQmc_qt.h"
#include <QMediaPlayer>

//
//#include <qmediaplaylist.h>
#include	"customPlaylist.h"

#include	"myDb.h"
#include	"funcsForIsCliHelp.h"
#include <qmcVideoCapture.h>

//
#define SHADOW_WIDTH 8 // 阴影边框宽度;

int viewInviteHint(HWND  hDlgTalk)
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	HWND  hMainWnd = pQyMc->gui.hMainWnd;
	CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
	if (pMainWnd == mynull)return -1;// goto  errLabel;
	QY_MC_mainWndVar& var = pMainWnd->var.common;

	//
	if (IsWindow(var.hintTaskStatus.hTool_dlgHintAccept)) {
		SetForegroundWindow(var.hintTaskStatus.hTool_dlgHintAccept);
		iErr = 0;  goto  errLabel;
	}

	CDlgTalk_qt* pTalk; pTalk = (CDlgTalk_qt*)getObjAddr(hDlgTalk);
	if (pTalk == mynull)goto  errLabel;

	int d_WIDTH; d_WIDTH = 324;
	int d_HEIGHT; d_HEIGHT = 167;
	DLG_TALK_var* pm_var; pm_var = pTalk->get_pm_var();
	if (!pm_var)return  -1;

	int  iTalkSubtype; iTalkSubtype = CONST_talkerSubtype_video;
	HWND  m_hWnd_shadow;

	if (findTalker_shadow(pQyMc, pm_var->addr.idInfo.ui64Id, iTalkSubtype, &m_hWnd_shadow))
	{
		return -1;
	}
	CDlgTalk_qt* video_cdlgTalkqt; video_cdlgTalkqt = (CDlgTalk_qt*)getObjAddr(m_hWnd_shadow);
	if (!video_cdlgTalkqt)
	{
		return -1;
	}
	//
	{
		//
		CDlgTalk_invite_hint* dlg = new CDlgTalk_invite_hint();

		QRect rect; rect = video_cdlgTalkqt->geometry();
		////计算显示原点
		int x; x = rect.x() + rect.width() / 2 - d_WIDTH / 2;
		int y; y = rect.y() + rect.height() / 2 - d_HEIGHT / 2;
		dlg->move(x, y);
		dlg->show();
		dlg->_hDlgTalk = hDlgTalk;

		var.notifyTaskStatus.hTool_dlgAvAccept = (HWND)dlg->winId();
	}

	iErr = 0;
errLabel:
	return  iErr;	
}

int  closeInviteHint()
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	HWND  hMainWnd = pQyMc->gui.hMainWnd;
	CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
	if (pMainWnd == mynull) return -1;// goto  errLabel;
	QY_MC_mainWndVar& var = pMainWnd->var.common;

	//
	if (IsWindow(var.hintTaskStatus.hTool_dlgHintAccept)) {
		CDlgTalk_invite_hint* dlg = (CDlgTalk_invite_hint*)getObjAddr(var.hintTaskStatus.hTool_dlgHintAccept);
		//
		if (dlg != NULL) {
			//
			delete  dlg;
		}
		//
		var.hintTaskStatus.hTool_dlgHintAccept = mynull;
	}

	//
	iErr = 0;
errLabel:
	return  iErr;
}


CDlgTalk_invite_hint::CDlgTalk_invite_hint(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//
	memset(&m_var, 0, sizeof(m_var));

	ui.labText->setText(u8"主持人邀请你发言");

	//设置窗口顶置: 一直在最前面. 

	this->setWindowTitle(u8"邀请提示");
	setWindowIcon(QIcon(":/Resources/Images/Login/qmClient.png"));
	setWindowFlags(Qt::FramelessWindowHint);
	timer = new QTimer();
	QIcon syscloseI(":/Resources/Images/Title/sysbtn_close_normal.png");
	ui.closeBtn->setIcon(syscloseI);

	//边框圆角
	QBitmap bmp(this->size());
	bmp.fill();
	QPainter p(&bmp);
	p.setPen(Qt::NoPen);
	p.setBrush(Qt::black);
	p.drawRoundedRect(bmp.rect(), 8, 8);
	setMask(bmp);

	ui.invitedIcon->setIcon(QIcon(":/Resources/Images/WinMain/invited_speak.png"));
	this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
	this->showNormal();

//	connect(timer,SIGNAL(timeout(),this,SLOT(onTimeout())));
	connect(timer, &QTimer::timeout, this, [=]() {this->close(); });

	m_time = 18;
	ui.labTime->setText(QString::number(m_time) + "s");
	time_timer = new QTimer(this);
	connect(time_timer, &QTimer::timeout, this, [=]() {
		
		ui.labTime->setText(QString::number(m_time)+"s");
		m_time--;

		});

	time_timer->start(1000);
	timer->start(20000);
}

CDlgTalk_invite_hint::~CDlgTalk_invite_hint()
{
	if (timer) {
		delete timer;
		timer = nullptr;
	}
	if (time_timer) {
		delete time_timer;
		time_timer = nullptr;
	}

}

//
void CDlgTalk_invite_hint::closeEvent(QCloseEvent* ev)
{
	if (!m_var.bQuit) {
		this->hide();
		ev->ignore();
	}
}

//
bool CDlgTalk_invite_hint::bQuitDlg(int iVal)
{
	m_var.bQuit = true;

	close();

	return  true;
}



//点击同意
void  CDlgTalk_invite_hint::on_btnConsent_clicked()
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	if (!_hDlgTalk) return;
	
	//
	HWND  hCur = (HWND)_hDlgTalk;
	CHelp_getDlgTalkVar  getDlgTalkVar_cur;
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;

	CDlgTalk_qt* pTalk = (CDlgTalk_qt*)getObjAddr(_hDlgTalk);
	if (pTalk == mynull) return ;
	DLG_TALK_var* pCurVar = (DLG_TALK_var*)getDlgTalkVar_cur.getVar(hCur);
	if (!pCurVar)  return ;
	HWND  hMgr;  hMgr = hCur;
	DLG_TALK_var* pMgrVar = pCurVar;
	if (!isTalkerShadowMgr(pCurVar->addr)) {
		TALKER_shadow* pShadowInfo = (TALKER_shadow*)pCurVar->pShadowInfo;
		if (!pShadowInfo) return ;
		hMgr = pShadowInfo->hMgr;
		pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
		if (!pMgrVar) return ;
	}

	
	if (pProcInfo->cfg.policy.avRules.ucbLetConfMgrSetMicOn) {
	
		//  2017/07/13
		setCurSharedObjUsr_localAv(pProcInfo, pMgrVar->av.iIndex_sharedObj_localAv, pMgrVar->av.iIndex_usr_localAv);

		dlgTalk_requestToSpeak(hMgr, TRUE);
		
		//
		pTalk->ui->toolBtnSpeak->setText(u8"静音");
	}
	//
	bQuitDlg(0);
}

//点击拒绝
void CDlgTalk_invite_hint::on_btnRefuse_clicked()
{
	//
	bQuitDlg(-1);

}

//拖拽操作
void CDlgTalk_invite_hint::mousePressEvent(QMouseEvent* event)
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

void CDlgTalk_invite_hint::mouseMoveEvent(QMouseEvent* event)
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

void CDlgTalk_invite_hint::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bDrag = false;
	}
}

void CDlgTalk_invite_hint::paintEvent(QPaintEvent* event)
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
	//	painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
		// 圆角阴影边框;
		painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
	}
}