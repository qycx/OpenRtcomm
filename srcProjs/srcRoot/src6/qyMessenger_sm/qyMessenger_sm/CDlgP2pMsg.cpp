#include	<tchar.h>

#define  __noDbg_new__

#include "CDlgP2pMsg.h"
#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc_sm.h"

#include	"CMainFrame.h"
#include	"smProc_qt.h"


CDlgP2pMsg::CDlgP2pMsg(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::CDlgP2pMsgClass)
{
	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

	sheetBackgroundImage();

	//超时关闭
	m_pWinTimer = new QTimer(this);
	connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(on_win_close()));

	m_pWinTimer->setInterval(1000);
	m_pWinTimer->start();


}

void CDlgP2pMsg::sheetBackgroundImage() {
	
	resize(1200, 500);

	ui->lab_txt->setStyleSheet("font-size:50px;color:#fff;font-weight:bold");
	ui->widget->setStyleSheet("QWidget#widget{background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30);}");
	/*ui->btn_consent->setStyleSheet("font-size:23px;color:#fff;background:#A1FB8E;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:green;color:#fff");
	ui->btn_repulse->setStyleSheet("font-size:23px;color:#fff;background:#F06868;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:red;color:#fff");*/

	ui->btn_consent->setStyleSheet("QPushButton{font-size:48px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
	ui->btn_repulse->setStyleSheet("QPushButton{font-size:48px;color:#fff;background:#8dacf6;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
	
	ui->btn_consent->setFixedSize(400, 130);
	ui->btn_repulse->setFixedSize(400, 130);
}

//点击同意
void CDlgP2pMsg::on_btn_consent_clicked() 
{
	int i = 12;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return;
	Ctx_sm& ctxSm = *pCtxSm;
	askforP2p_do();
	

	QString log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"同意" + QString::fromUtf16((char16_t*)ctxSm.hg.p2pMsg.formTermName) + u8"发起的点对点会议";

	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

	do_close();

}


//点击拒绝
void CDlgP2pMsg::on_btn_repulse_clicked() 
{
	//this->close();
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return;
	Ctx_sm& ctxSm = *pCtxSm;
	QString log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"拒绝" + QString::fromUtf16((char16_t*)ctxSm.hg.p2pMsg.formTermName) + u8"发起的点对点会议";

	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);


	do_close();

}


void CDlgP2pMsg::do_close()
{
	CCtxQyMc* pQyMc = g_pQyMc;

	CMainFrame* pMainWnd = (CMainFrame*)CMainFrame::find((WId)pQyMc->gui.hMainWnd);
	if (pMainWnd) {
		pMainWnd->on_P2pMsg_close();
	}

	return;
}


//关闭窗口
void CDlgP2pMsg::on_win_close()
{


	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return;
	Ctx_sm& ctxSm = *pCtxSm;
	QString termName = QString::fromUtf16((char16_t*)ctxSm.hg.p2pMsg.formTermName);

	QString txt_str = termName + u8"发起了会议邀请  " + QString::number(_closeTime) + "s";

	ui->lab_txt->setText(txt_str);
	_closeTime--;

	//
	if (_closeTime < 0) {
		
		//this->close();

		QString log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"与" + QString::fromUtf16((char16_t*)ctxSm.hg.p2pMsg.formTermName) + u8"发起的点对点会议 无人接收，会议自动结束";

		qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);


		do_close();
	}

}

//左右箭头
void CDlgP2pMsg::Infrared_input_left_right(QString name, bool isLeft)
{
	if (chkFocus(this))return;

	if (isLeft) {
		this->focusNextPrevChild(false);
	}
	else {
		this->focusNextPrevChild(true);
	}
}





CDlgP2pMsg::~CDlgP2pMsg()
{
	delete ui;

	if (m_pWinTimer) {
		delete m_pWinTimer;
		m_pWinTimer = 0 ;
	}
}
