// DlgProgress.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qisGuiPublic_public.h"

#include	"myresource.h"
#include	"DlgProgress.h"
//#include	"qmcCmdProc.h"

//
//#include	"ctxQmc.h"





__declspec(dllexport)  int  showProgress(  QY_PROGRESS  *  pProgress,  QNM_CUSRES_INFO  *  pCusResInfo,  HWND  hParent,  LPCTSTR  title,  LPCTSTR  progressTxt,  int  nStep_finished,  int  iIndex_shmCmd,  unsigned  int  uiTranNo,  BOOL  canUsrOk,  PF_commonHandler  pf_doProgress  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if  (  !pProgress  )  return  -1;
	QY_PROGRESS  &  progress  =  *pProgress;

	//
	//MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	//if  (  !pProcInfo  )  return  -1;
	
	//  2014/05/07
	CQySyncFlg	syncFlg;	
	if  (  syncFlg.sync(  &progress.bInSequence_showDlgProgress  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "showProgress failed, bLocked already"  )  );
		return  -1;
	}

	//
	int				iRet	=	-1;
	CDlgProgress	dlg(  CWnd::FromHandle(  hParent  )  );
	
	if  (  !title  )  title  =  _T(  "Please waiting"  );
	if  (  nStep_finished  <=  0  )  nStep_finished  =  30;
	dlg.bSetDlgInfo(  title,  progressTxt,  nStep_finished,  -1,  uiTranNo  ); 
	dlg.m_var.pProgress  =  pProgress;
	dlg.m_var.pCusResInfo  = pCusResInfo;
	
	//  traceLogA(  "if task is not ready, cancel the task by clear shmCmd, and the subprocess will quit when it read the shmCmd."  );	
	iRet  =  dlg.DoModal(  );

errLabel:		
	return  iRet;	
}


// CDlgProgress dialog

IMPLEMENT_DYNAMIC(CDlgProgress, CDialog)

CDlgProgress::CDlgProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProgress::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgProgress::~CDlgProgress()
{
}


BOOL	CDlgProgress::bSetDlgInfo(  LPCTSTR  title,  LPCTSTR  progressTxt,  int  nStep_finished,  int  iIndex_shmCmd,  unsigned  int  uiTranNo,  BOOL  canUsrOk,  PF_commonHandler  pf_doProgress  )
{
	if  (  title  )  lstrcpyn(  m_var.title,  title,  mycountof(  m_var.title  )  );
	if  (  progressTxt  )  lstrcpyn(  m_var.progressTxt,  progressTxt,  mycountof(  m_var.progressTxt  )  );
	m_var.nStep_finished  =  nStep_finished;
	m_var.iIndex_shmCmd  =  iIndex_shmCmd;
	m_var.uiTranNo  =  uiTranNo;
	m_var.canUsrOk  =  canUsrOk;
	m_var.pf_doProgress  =  pf_doProgress;
	
	return  TRUE;
}

BOOL	CDlgProgress::bQuitDlg(  int  nResult  )
{
	EndDialog(  nResult  );
	return  TRUE;
}

void CDlgProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgProgress, CDialog)
	ON_WM_TIMER()
	ON_MESSAGE(CONST_qyWm_postComm, OnQyPostComm)
END_MESSAGE_MAP()


// CDlgProgress message handlers

BOOL CDlgProgress::OnInitDialog()
{
	CDialog::OnInitDialog();
	//QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
#if  0
	MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "dlgProgress::OnInitDialog failed, pProcInfo is null"  )  );
		#endif
		return  FALSE;
	}
#endif

	// TODO:  Add extra initialization here
	if  (  m_var.pCusResInfo  )  {
		cusDlgRes(  0,  m_var.pCusResInfo,  this->m_hWnd,  this->IDD  );
	}
	//
	QY_PROGRESS  &  progress  =  *m_var.pProgress;

#if  0
	QM_SHM_CMD	*	pShmCmd	=	getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  m_var.iIndex_shmCmd  );
	if  (  pShmCmd  )  {
		pShmCmd->hWnd_progress  =  this->m_hWnd;
		//
		if  (  pShmCmd->ucbShmCmdInited  )  
		{
			this->bQuitDlg(  IDOK  );  return  FALSE;
		}
	}
#endif
	if  (  progress.var.uiTranNo  &&  progress.var.uiTranNo  ==  m_var.uiTranNo  )  {
		progress.var.hWnd  =  this->m_hWnd;
	}

	SetWindowText(  m_var.title  );				//  È±Ê¡£ºregTool
			
	if  (  !m_var.nStep_finished  )  m_var.nStep_finished  =  100;
	::SendMessage(  GetDlgItem(  IDC_PROGRESS  )->m_hWnd,  PBM_SETRANGE,  0,  myMAKELPARAM(  0,  m_var.nStep_finished  )  );
	::SendMessage(  GetDlgItem(  IDC_PROGRESS  )->m_hWnd,  PBM_SETSTEP,  1,  0  );

	m_var.uiTimerId  =  SetTimer(  1,  1000,  NULL  );

	if  (  !m_var.canUsrOk  )  {
		GetDlgItem(  IDOK  )->EnableWindow(  FALSE  );
	}

	if  (  m_var.pf_doProgress  )  m_var.pf_doProgress(  0,  GetParent(  ),  this  );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgProgress::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	m_var.iProgress  ++  ;

	if  (  m_var.pf_doProgress  )  {
		if  (  m_var.pf_doProgress(  0,  GetParent(  ),  this  )  )  return;
	}

	//
	QY_PROGRESS  &  progress  =  *m_var.pProgress;

	//MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	//if  (  pProcInfo  )  
	{
		if  (  progress.var.uiTranNo  
			&&  progress.var.uiTranNo  ==  m_var.uiTranNo  
			&&  progress.var.ucbProgessEnd  )  
		{
			#if  1
				 //pProcInfo->debugInfo.nStep_progress  =  53;
			#endif
			//
			bQuitDlg(  IDOK  );
			return;
		}
	}

	if  (  m_var.iProgress  >=  m_var.nStep_finished  )  {
		bQuitDlg(  IDTIMEOUT  );
		return;
	}

	//
	TCHAR  *  pProgressTxt  =  m_var.progressTxt;
#ifdef  __DEBUG__
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %d"  ),  m_var.progressTxt,  m_var.uiTranNo  );
		pProgressTxt  =  tBuf;
#endif


	//
	SetDlgItemText(  IDC_STATIC_progress,  pProgressTxt  );
	::SendMessage(  GetDlgItem(  IDC_PROGRESS  )->m_hWnd,  PBM_SETPOS,  m_var.iProgress,  0  );							   

	CDialog::OnTimer(nIDEvent);
}

LRESULT CDlgProgress::OnQyPostComm(  WPARAM  wParam, LPARAM  lParam  )
{
	LONG				lRet			=	-1;

	switch  (  wParam  )  {
			case  CONST_qyWmParam_notifyQmShmCmdStatus:  {
#if  0
				  MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  goto  errLabel;
				  QM_SHM_CMD	*	pShmCmd	=	getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  m_var.iIndex_shmCmd  );
				  if  (  lParam  &&  lParam  ==  pShmCmd->uiTranNo_sharedObj  )  {
					  #if  1
							pProcInfo->debugInfo.nStep_progress  =  100;
					  #endif
					  //
					  this->bQuitDlg(  IDOK  );
					  return  0;
				  }
				  
#endif
				  }
				  break;
			case  CONST_qyWmParam_notifyProgressEnd:	//  2010/08/14
				  if  (  lParam  &&  lParam  ==  m_var.uiTranNo  )  {
					  bQuitDlg(  IDOK  );
					  return  0;
				  }
				  break;
			default:
					break;
	}

	lRet  =  QY_RC_WMOK;

errLabel:

	return	lRet;

}
