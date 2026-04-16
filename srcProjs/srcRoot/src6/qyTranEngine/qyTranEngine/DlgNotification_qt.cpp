#include "DlgNotification_qt.h"
#include <qdesktopwidget.h>
#include	<qtimer.h>




#define		CONST_timerId_popWindow					1

#define		CONST_nElapseInMs_popWindow				20

#define     CONST_d_WIDTH							200
#define     CONST_d_HEIGHT							140

__declspec(dllexport)  int  popupNotificationWnd()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int							iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();

	//  if  (  isQmCmd(  )  )  return  -1;  
	//
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;

	if (IsWindow(pProcInfo->hWnd_notification))  return  0;

	DlgNotification_qt* pDlg = NULL;
	RECT					rect;

	pDlg = new  DlgNotification_qt();
	if (!pDlg)  goto  errLabel;

	//WinPromptDlgBox* pBase = pDlg;
	//memset(&pBase->m_var.layoutParam, 0, sizeof(pBase->m_var.layoutParam));
	//pBase->m_var.layoutParam.iH_static = pProcInfo->cfg.policy.notification.iH_static;
	//  pBase->m_var.ucbHideStatic  =  TRUE;

	int  iWndContentType = 0;
	unsigned  int  uiInitW = pProcInfo->cfg.policy.notification.iW_pic;
	unsigned  int  uiInitH = pProcInfo->cfg.policy.notification.iH_pic;
	//if (!pDlg->bSetDlgInfo(iWndContentType, 0, 0, 1, 1, uiInitW, uiInitH))  goto  errLabel;

	//if (!pDlg->Create(rect))  goto  errLabel;

	//  pDlg->ShowWindow(  SW_SHOWNOACTIVATE  );
	pDlg->show();

	//pDlg->EnableWindow(TRUE);

	//Ïú»Ù new
	pProcInfo->hWnd_notification = (HWND)pDlg->winId();

	iErr = 0;

errLabel:

	if (iErr) {
		if (pDlg) {
			delete  pDlg;  pDlg = NULL;
		}
	}
	return  iErr;
}


__declspec(dllexport) int  addNotification(MIS_MSG_taskStatus* pStatus)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iErr = -1;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;

	if (!IsWindow(pProcInfo->hWnd_notification))  return  -1;

	DlgNotification_qt* pDlg = (DlgNotification_qt*)QWidget::find( (WId)pProcInfo->hWnd_notification );

	if (!pDlg->bAddNotification_qt(pStatus))  return  -1;

	iErr = 0;

	return  iErr;
}

DlgNotification_qt::DlgNotification_qt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	memset(&m_var, 0, sizeof(m_var));

	//
	this->setAttribute(Qt::WA_DeleteOnClose);
	
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	//
	m_var.nTimerIntervalInMs = 20;
	m_var.usTimeInMsToPop = pProcInfo->cfg.policy.notification.usTimeInMsToPop;
	if (m_var.usTimeInMsToPop < m_var.nTimerIntervalInMs)  m_var.usTimeInMsToPop = m_var.nTimerIntervalInMs;

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
#if  0   
	QRect rc = QApplication::desktop()->screenGeometry();


	int rx = rc.width() - CONST_d_WIDTH - 60;
	int ry = rc.height() - CONST_d_HEIGHT - 60;

	QRect r = QRect(rx, ry, CONST_d_WIDTH , CONST_d_HEIGHT);
	setGeometry(r);
#endif

	//
	m_pWinTimer = new QTimer(this);
	connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(on_timer_winMethod()));
	m_pWinTimer->setInterval(CONST_nElapseInMs_popWindow);
	m_pWinTimer->start();


}

DlgNotification_qt::~DlgNotification_qt()
{
	if (m_pWinTimer)
	{
		delete m_pWinTimer;
		m_pWinTimer = nullptr;
	}
}

//
void DlgNotification_qt::on_timer_winMethod()
{
	this->OnTimer(CONST_timerId_popWindow);
}




  BOOL DlgNotification_qt::bAddNotification_qt( MIS_MSG_taskStatus* pStatus)
{
	BOOL			bRet = FALSE;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

	//if (!m_var.bInited_q)  return  FALSE;

//	qRemoveMsg(&m_var.tBuf, (PF_bCommonHandler)tmpHandler_findMsgr, 0, &pStatus->idInfo_logicalPeer);

	//if (qPostMsg(pStatus, sizeof(pStatus[0]), &m_var.tBuf, _T("dlgNotification.bAddNot")))  goto  errLabel;
	
	safeTcsnCpy(pStatus->u.notification.tBuf , m_var.tBuf , mycountof(m_var.tBuf));
	//WinPromptDlgBox* pBase = (WinPromptDlgBox*)this;
	ui.labMsg->setText(QString::fromStdWString(m_var.tBuf));

#ifdef  __DEBUG__
	//this->printQ();
#endif

	//GetDlgItem(m_var.idcHint)->Invalidate();


	//this->EnableWindow(FALSE);

	//SetTimer(  CONST_timerId_popWindow,  CONST_nElapseInMs_popWindow,  NULL  );  

	bRet = TRUE;

errLabel:

	return  bRet;
}


  void DlgNotification_qt::OnTimer(UINT_PTR nIDEvent)
  {
	  int		cy = GetSystemMetrics(SM_CYSCREEN);
	  int		cx = GetSystemMetrics(SM_CXSCREEN);
	  RECT	rect;
	  SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	  int		y = rect.bottom - rect.top;
	  int		x = rect.right - rect.left;

	  //CDlgDesktopsMon* pBase = (CDlgDesktopsMon*)this;
	  //int					iW_win = pBase->m_var.uiInitW_pic;
	  //  int					iH_win			=	(  mybVideoExists(  )  ?  pBase->m_var.uiInitH_pic  :  0  )  +  pBase->m_var.layoutParam.iH_static;
	  //int					iH_win = max(pBase->m_var.uiInitH_pic, pBase->m_var.layoutParam.iH_static);
	  int  iW_win = CONST_d_WIDTH;
	  int  iH_win = CONST_d_HEIGHT;
	  //
	  int					nH_oneTime = iH_win * m_var.nTimerIntervalInMs / m_var.usTimeInMsToPop;
	  if (!nH_oneTime)  nH_oneTime = 1;
	  int					nH_oneTime_toClose = nH_oneTime / 3;
	  if (!nH_oneTime_toClose)  nH_oneTime_toClose = 1;

	  //
	  BOOL				bCloseWindow = FALSE;

	  //if (!m_var.bInited_q)  return;

	  x = x - iW_win;

	  HWND  m_hWnd = (HWND)this->winId();
	  EnableWindow(m_hWnd,FALSE);

	  // TODO: Add your message handler code here and/or call default
	  switch (nIDEvent) {
	  case  CONST_timerId_popWindow:
		  //
		  DWORD  dwTickCnt;
		  dwTickCnt = GetTickCount();
		  //
		  if (m_var.bWaiting) {
			  //if (isQEmpty(&m_var.q))
			  if  ( !m_var.tBuf[0])
			  {
				  if (GetTickCount() - m_var.dwTickCnt_initDialog < 100)  goto  errLabel;
				  bCloseWindow = TRUE;
				  goto  errLabel;
			  }
			  m_var.bWaiting = FALSE;
		  }

		  //
		  m_var.bClosing = m_var.tBuf[0]==0 ? TRUE : FALSE;
		  if (!m_var.bClosing) {
			  if (m_var.dwTickCnt_allDisplayed) {
				  int  iDiffInMs = dwTickCnt - m_var.dwTickCnt_allDisplayed;
				  iDiffInMs = abs(iDiffInMs);
				  if (iDiffInMs > 1500) {
					  m_var.bClosing = TRUE;
				  }
			  }
		  }

		  if (!m_var.bClosing) {
			  if (m_var.nHeight < iH_win) {
				  //  m_var.nHeight  ++  ;
				  m_var.nHeight = min(nH_oneTime + m_var.nHeight, iH_win);
				  MoveWindow(m_hWnd,  x, y - m_var.nHeight, iW_win, iH_win,false);
				  //Invalidate(FALSE);
				  //
			  }
			  else {
				  if (!m_var.dwTickCnt_allDisplayed) {
					  m_var.dwTickCnt_allDisplayed = GetTickCount();
				  }
			  }
		  }
		  else {
			  if (m_var.nHeight > 0) {
				  //  m_var.nHeight  --  ;
				  m_var.nHeight = max(0, m_var.nHeight - nH_oneTime_toClose);
				  MoveWindow(m_hWnd,  x, y - m_var.nHeight, iW_win, iH_win,false);
				  //Invalidate(FALSE);
			  }
			  else {
				  //KillTimer(  nIDEvent  );
				  //
				  bCloseWindow = TRUE;
				  goto  errLabel;
			  }
		  }
		  break;
	  default:
		  break;
	  }


  errLabel:

	  EnableWindow(m_hWnd,  TRUE);

	  if (bCloseWindow) {
		  ::SendMessage(m_hWnd, WM_CLOSE, 0, 0);
	  }
	  return;
  }
