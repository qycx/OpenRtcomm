// qyStatusTool.cpp : Defines the class behaviors for the application.
//

#include	"stdafx.h"
#include	"qyStatusToolCommon.h"
#include	"qyStatusTool.h"
#include	"qyPs.h"
/*
#include	"ppScanningIpStatus.h"
#include	"ppQwmCommStatus.h"
#include	"ppQnmChkingStatus.h"
*/
#include	"DlgQyCommStatus.h"
//#include	"qyCusResPublic.h"
#include	"qnmResDefs.h"
#include	"qyStatusDaemon.h"
#include <ctxQmThread.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQyStatusToolApp

BEGIN_MESSAGE_MAP(CQyStatusToolApp, CWinApp)
	//{{AFX_MSG_MAP(CQyStatusToolApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQyStatusToolApp construction

CQyStatusToolApp::CQyStatusToolApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CQyStatusToolApp object

CQyStatusToolApp  theApp;

/////////////////////////////////////////////////////////////////////////////
// CQyStatusToolApp initialization

//
 
TCHAR		gStatusToolWndCls[256]	=	CONST_qnmStatusToolWndClass;
//
QY_STATUS_STRUCT  *  g_pStatusStruct  =  NULL;



//
int  setModalWnd_func(  HWND  hDlg,  BOOL  bFileDialog  )
{
	return  0;
}

BOOL CQyStatusToolApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	
	CDlgQyCommStatus dlg;

	DWORD					dwThreadId;
	int						index;
	QY_STATUS_STRUCT	*	pStatusStruct	=  NULL;
	CQyStatusDaemon		*	pDaemon			=	NULL;

	//
	setDebugLogFileModuleName(  );	//  设置DebogLog文件名

	if  (  qyGetAppType(  0,  NULL  )  ==  CONST_qyAppType_client  )  _sntprintf(  gStatusToolWndCls,  mycountof(  gStatusToolWndCls  ),  _T(  "%s"  ),  CONST_qnmStatusToolWndClass_client  );

	if  (  FindWindow(  gStatusToolWndCls,  0  )  )  {
		traceLogA(  "StatusTool already exists."  );
		goto  errLabel;
	}
	
	//
	init_tickCnt();

	
	//
	dlg.m_var.iType  =  CONST_qyPsType_show;
	_snprintf(  dlg.m_var.u.showInfo.serviceName_netMc,  sizeof(  dlg.m_var.u.showInfo.serviceName_netMc  ),  "%s",  CONST_qyMgrServiceName  );
	_snprintf(  dlg.m_var.u.showInfo.serviceName_is,  sizeof(  dlg.m_var.u.showInfo.serviceName_is  ),  "%s",  CONST_qyServiceName_is  );
	pStatusStruct  =  (  QY_STATUS_STRUCT  *  )&dlg.m_var.u.showInfo.statusStruct;
	g_pStatusStruct  =  pStatusStruct;

	//
	pStatusStruct->usLangId  =  GetSystemDefaultLangID(  );
	if  (  initQnmRes(  0,  pStatusStruct->usLangId,  CONST_resId_app_statusTool,  &pStatusStruct->cusRes  )  )  goto  errLabel;
    pStatusStruct->ucbCusResInited  =  TRUE;
	set_cur_iResId_sys(  CONST_resId_app_statusTool  );		//  2013/06/17

	//
	GENERIC_Q_CFG	qCfg;
	int				len;


	//
	memset(&qCfg, 0, sizeof(qCfg));
	_sntprintf(qCfg.name, mycountof(qCfg.name), _T("inputQ"));
	_sntprintf(qCfg.mutexName_prefix, mycountof(qCfg.mutexName_prefix), _T("inputQ"));
	qCfg.uiMaxQNodes = 10000;
	if (initGenericQ(&qCfg, malloc, 0, 0, free, NULL, &pStatusStruct->inputQ))  goto  errLabel;
	pStatusStruct->bInited_inputQ = TRUE;


	//
	index  =  0;
	if  (  !(  pStatusStruct->hThreads[index]  =  ::CreateThread(  NULL,  0,  qyStatusToolThreadProc,  (  LPVOID  )pStatusStruct,  0,  &dwThreadId  )  )  )  goto  errLabel;
	index  ++  ;
	//if  (  qyGetAppType(  0,  NULL  )  !=  CONST_qyAppType_client  )  
	{
		if  (  !(  pStatusStruct->hThreads[index]  =  ::CreateThread(  NULL,  0,  statusPipeServThreadProc,  (  LPVOID  )pStatusStruct,  0,  &dwThreadId  )  )  )  goto  errLabel;
		index  ++  ;
	}
	MACRO_qyAssert(  index  <=  sizeof(  pStatusStruct->hThreads  )  /  sizeof(  pStatusStruct->hThreads[0]  ),  _T(  "m_var.hThreads越界"  )  );

	//
	//  (  bAppClient(  qyGetAppType(  0,  NULL  )  )  )  
	{
		pDaemon  =  new  CQyStatusDaemon(  );
		if  (  !pDaemon  )  goto  errLabel;

		//
		if  (  pDaemon->getInitialCfg(  )  )  goto  errLabel;
		if  (  pDaemon->init(  )  )  goto  errLabel;
		if  (  pDaemon->start(  )  )  goto  errLabel;
	}

	//
	m_pMainWnd = &dlg;
	dlg.DoModal();
	

	//
errLabel:
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.

	//
	traceLogA(  "CQyStatusToolApp ready to quit"  );

	//
	if  (  pStatusStruct  )  {
		pStatusStruct->bQuit  =  true;

		//
		extern  HWND  g_statusToolWnd;
		//
		traceLog(  _T(  "to close statusToolWnd"  )  );
		PostMessage(  g_statusToolWnd,  WM_QUIT,  0,  0  );
		traceLog(  _T(  "statusToolWnd closed"  )  );

	}

	//
	if  (  pDaemon  )  {
		pDaemon->startToQuit();
		//
		pDaemon->stop(  );
		pDaemon->exit(  );
		delete  pDaemon;  pDaemon =  NULL;
	}


	//
	if  (  pStatusStruct  )  {
		pStatusStruct->bQuit  =  TRUE;
	
		//
		for  (  index  =  0;  index  <  sizeof(  pStatusStruct->hThreads  )  /  sizeof(  pStatusStruct->hThreads[0]  );  index  ++  )  {
			 //
			 traceLog(  _T(  "to clean threads[%d]"  ),  index  );
			 //
			 MACRO_qyNullThread(  pStatusStruct->hThreads[index]  );
			 //
			 traceLog(  _T(  "hThread[%d] is null"  ),  index  );
		}
		//
		if (pStatusStruct->bInited_inputQ) {
			exitGenericQ(&pStatusStruct->inputQ);  pStatusStruct->bInited_inputQ = false;
		}


		//
		if  (  pStatusStruct->ucbCusResInited  )  {
			exitQnmRes(  0,  &pStatusStruct->cusRes  );  pStatusStruct->ucbCusResInited  =  FALSE;
		}
	}

	traceLogA(  "CQyStatusToolApp quit"  );

	return  FALSE;

}


