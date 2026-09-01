
#include	"stdafx.h"
#include "DlgProgress_qt.h"
#include	<qtimer.h>
#include	"qyMcMainCommon_qt.h"
#include <QIcon>



__declspec(dllexport)  int  showProgress(QY_PROGRESS* pProgress, QNM_CUSRES_INFO* pCusResInfo, HWND  hParent, LPCTSTR  title, LPCTSTR  progressTxt, int  nStep_finished, int  iIndex_shmCmd, unsigned  int  uiTranNo, BOOL  canUsrOk, PF_commonHandler  pf_doProgress)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!pProgress)  return  -1;
	QY_PROGRESS& progress = *pProgress;

	//
	//MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	//if  (  !pProcInfo  )  return  -1;

	//  2014/05/07
	CQySyncFlg	syncFlg;
	if (syncFlg.sync(&progress.bInSequence_showDlgProgress)) {
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("showProgress failed, bLocked already"));
		return  -1;
	}

	//
	QWidget* pParent = QWidget::find((WId)hParent);
	if (pParent == NULL) return  -1;

	//
	int				iRet = -1;
#if 10
	DlgProgress_qt	dlg(pParent);

	if (!title)  title = _T("Please waiting");
	if (nStep_finished <= 0)  nStep_finished = 30;
	dlg.bSetDlgInfo(title, progressTxt, nStep_finished, -1, uiTranNo);
	dlg.m_var.pProgress = pProgress;
	dlg.m_var.pCusResInfo = pCusResInfo;
	
	
	//  traceLogA(  "if task is not ready, cancel the task by clear shmCmd, and the subprocess will quit when it read the shmCmd."  );	
	//iRet = dlg.DoModal();
	iRet = dlg.exec();

	if (iRet == QDialog::Accepted) {
		return dlg.m_var.iRet;
	}

#endif

errLabel:
	return  -1;
}



DlgProgress_qt::DlgProgress_qt(QWidget *parent)
	: QDialog(parent)
	,ui(new Ui::DlgProgress_qt)
{
	ui->setupUi(this);
	setWindowIcon(QIcon(":/Resources/Images/Login/qmClient.png"));
	memset(&m_var, 0, sizeof(m_var));
	
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

	//
	m_pWinTimer = new QTimer(this);
	connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(on_timer_winMethod()));
	m_pWinTimer->setInterval(1000);
	m_pWinTimer->start();
}

DlgProgress_qt::~DlgProgress_qt()
{
	delete ui;

	//
	if (m_pWinTimer)
	{
		delete m_pWinTimer;
		m_pWinTimer = nullptr;
	}

}


BOOL	DlgProgress_qt::bSetDlgInfo(LPCTSTR  title, LPCTSTR  progressTxt, int  nStep_finished, int  iIndex_shmCmd, unsigned  int  uiTranNo, BOOL  canUsrOk, PF_commonHandler  pf_doProgress)
{
	if (title)  lstrcpyn(m_var.title, title, mycountof(m_var.title));
	if (progressTxt)  lstrcpyn(m_var.progressTxt, progressTxt, mycountof(m_var.progressTxt));
	m_var.nStep_finished = nStep_finished;
	m_var.iIndex_shmCmd = iIndex_shmCmd;
	m_var.uiTranNo = uiTranNo;
	m_var.canUsrOk = canUsrOk;
	m_var.pf_doProgress = pf_doProgress;
	this->setWindowTitle(QString::fromStdWString(title));
	ui->progressBar->setMaximum(nStep_finished);
	return  TRUE;
}


BOOL	DlgProgress_qt::bQuitDlg(int  nResult)
{
	this->accept();
	m_var.iRet = nResult;
	return  true;
}



bool DlgProgress_qt::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	Q_UNUSED(eventType);
	MSG* msg = reinterpret_cast<MSG*>(message);
	UINT m = msg->message;
	if (m == WM_COMMAND || m == CONST_qyWm_comm || m == CONST_qyWm_postComm)
	{
		return postMessageQt(msg, result);
	}


	return  false;
}


bool DlgProgress_qt::postMessageQt(MSG* message, long* result)
{
	if (message->message == CONST_qyWm_postComm) {
		OnQyPostComm(message->wParam, message->lParam);
	}
	if (message->message == CONST_qyWm_comm) {
		//OnQyComm()
	}
	return true;
}


LRESULT DlgProgress_qt::OnQyPostComm(WPARAM wParam, LPARAM lParam)

	{
		LONG				lRet = -1;

		switch (wParam) {
		case  CONST_qyWmParam_notifyQmShmCmdStatus: {
#if  0
			MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
			if (!pProcInfo)  goto  errLabel;
			QM_SHM_CMD* pShmCmd = getShmCmdByIndex((QM_SHM_CMDS*)pProcInfo->cmdsShm.pBuf, m_var.iIndex_shmCmd);
			if (lParam && lParam == pShmCmd->uiTranNo_sharedObj) {
#if  1
				pProcInfo->debugInfo.nStep_progress = 100;
#endif
				//
				this->bQuitDlg(IDOK);
				return  0;
			}

#endif
		}
												  break;
									
		case  CONST_qyWmParam_notifyProgressEnd:	//  2010/08/14
			if (lParam && lParam == m_var.uiTranNo) {
				bQuitDlg(IDOK);
				return  0;
			}
			break;
		default:
			break;
		}

		lRet = QY_RC_WMOK;

	errLabel:

		return	lRet;

	}


void DlgProgress_qt::on_timer_winMethod()
{
	// TODO: Add your message handler code here and/or call default
	m_var.iProgress++;

	if (m_var.pf_doProgress) {
		if (m_var.pf_doProgress(0, this->parent(), this))  return;
	}

	//
	QY_PROGRESS& progress = *m_var.pProgress;

	//MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	//if  (  pProcInfo  )  


	{
		if (progress.var.uiTranNo
			&& progress.var.uiTranNo == m_var.uiTranNo
			&& progress.var.ucbProgessEnd)
		{
#if  1
			//pProcInfo->debugInfo.nStep_progress  =  53;
#endif
//
			bQuitDlg(IDOK);
			return;
		}
	}

	if (m_var.iProgress >= m_var.nStep_finished) {
		bQuitDlg(IDTIMEOUT);
		return;
	}

	//
	TCHAR* pProgressTxt = m_var.progressTxt;
#ifdef  __DEBUG__
	TCHAR  tBuf[128];
	_sntprintf(tBuf, mycountof(tBuf), _T("%s %d"), m_var.progressTxt, m_var.uiTranNo);
	pProgressTxt = tBuf;
#endif


	//
	//SetDlgItemText(IDC_STATIC_progress, pProgressTxt);

	ui->progressBar->setValue(m_var.iProgress);
	//::SendMessage(GetDlgItem(IDC_PROGRESS)->m_hWnd, PBM_SETPOS, m_var.iProgress, 0);

	//CDialog::OnTimer(nIDEvent);
}


