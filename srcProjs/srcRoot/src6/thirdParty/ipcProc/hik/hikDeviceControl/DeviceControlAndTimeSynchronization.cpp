// DeviceControlAndTimeSynchronization.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DeviceControlAndTimeSynchronization.h"
#include "DeviceControlAndTimeSynchronizationDlg.h"

#include	"dhDeviceControlProc.h"
#include <ctxQmThread.h>
#include <showInfo_open.h>

//
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeviceControlAndTimeSynchronizationApp

BEGIN_MESSAGE_MAP(CDeviceControlAndTimeSynchronizationApp, CWinApp)
	//{{AFX_MSG_MAP(CDeviceControlAndTimeSynchronizationApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeviceControlAndTimeSynchronizationApp construction
CString ConvertString(CString strText)
{
	TCHAR *val = new TCHAR[200];
	CString strIniPath,strRet;
	
	memset(val,0,200);
	GetPrivateProfileString(_T("String"),strText,_T(""),
		val,200,_T("./langchn.ini"));
	strRet = val;
	if(strRet.GetLength()==0)
	{
		//If there is no corresponding string in ini file then set it to be default value(English).
		strRet=strText;
	}
	delete val;
	return strRet;
}
//Set static text in dialogue box (English->current language)
void g_SetWndStaticText(CWnd * pWnd)
{
	CString strCaption,strText;
	
	//Set main window title
	pWnd->GetWindowText(strCaption);
	if(strCaption.GetLength()>0)
	{
		strText=ConvertString(strCaption);
		pWnd->SetWindowText(strText);
	}
	
	//Set small window title
	CWnd * pChild=pWnd->GetWindow(GW_CHILD);
	CString strClassName;
	while(pChild)
	{
		//////////////////////////////////////////////////////////////////////////		
		//Added by Jackbin 2005-03-11
		strClassName = ((CRuntimeClass*)pChild->GetRuntimeClass())->m_lpszClassName;
		if(strClassName == "CEdit")
		{
			//Next small window 
			pChild=pChild->GetWindow(GW_HWNDNEXT);
			continue;
		}
		
		//////////////////////////////////////////////////////////////////////////	
		
		//Set current language text in small window.
		pChild->GetWindowText(strCaption);
		strText=ConvertString(strCaption);
		pChild->SetWindowText(strText);
		
		//Next small window 
		pChild=pChild->GetWindow(GW_HWNDNEXT);
	}
}



CDeviceControlAndTimeSynchronizationApp::CDeviceControlAndTimeSynchronizationApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDeviceControlAndTimeSynchronizationApp object

CDeviceControlAndTimeSynchronizationApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDeviceControlAndTimeSynchronizationApp initialization

BOOL CDeviceControlAndTimeSynchronizationApp::InitInstance()
{
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

		//
	// 
	//
	do {
		//
		init_tickCnt();


		//
		bool  bCli = true;

		//
		bool  bShowInfoInited = false;
		TCHAR* errHintWndCls = (TCHAR*)_T("mmsmsm");//CONST_qnmStatusToolWndClass;
		//if  (  initShowInfo(  0,  _T(  "syncQ_showInfo_qmd"  ),  errHintWndCls,  TRUE,  FALSE,  &mcDaemon.var.pShowInfoStruct  )  )  goto  errLabel;
		if (initShowInfo_func(0, _T("syncQ_showInfo_dh"), errHintWndCls, false, true, (char*)"127.0.0.1", bCli, &gBuf_dhDeviceControl.m_var.pShowInfoStruct)) {
			//goto  errLabel;
			break;
		}
		bShowInfoInited = TRUE;

		//
		set_who_showInfoA(("dhPtz"));

		//
		TCHAR* cmdLine = GetCommandLine();
		parseCmdLine_ipcProc(cmdLine, &gBuf_dhDeviceControl.m_var.appParams);


		//
		//showInfo_openA(0, 0, "dhPtz called");

		//
		{
			//
			if (gBuf_dhDeviceControl.m_var.appParams.nvrIp[0] == 0) {
				showInfo_open0(0, 0, _T("dhPtz: nvrIp is null, failed"));
				break;
			}

			//
			gBuf_dhDeviceControl.m_var.m_bAutoClose_ifToolLongNoRecvd_qm = true;

#ifdef  _DEBUG
			//gBuf_dhListIp.m_var.m_bAutoClose_ifToolLongNoRecvd_dh = false;
#endif

		//
			gBuf_dhDeviceControl.m_var.dwLastTickCnt_recvd = myGetTickCount(nullptr);

			//
			gBuf_dhDeviceControl.m_var.pQisPipe = qisPipeNew();
			if (!gBuf_dhDeviceControl.m_var.pQisPipe)  break;

			//
					  //
			GENERIC_Q_CFG  qCfg = { 0 };
			TCHAR   pipeName[128] = _T("");
			int  tn_rtspCliPipe = 0;// pParams->tn_cliPipe;
			//
			_sntprintf(qCfg.name, mycountof(qCfg.name), _T("qisPipe"));
			_sntprintf(qCfg.mutexName_prefix, mycountof(qCfg.mutexName_prefix), _T("qiqPipe"));
			qCfg.uiMaxQNodes = 100;	//  CONST_uiMaxQNodes_outputQ_256;

			//		  
			M_get_pipeName(CONST_ipcProcPipePrefix, _T(""), CONST_ipcProcPipe_tn_dhDeviceControl, pipeName);


			//
			PARAM_initQisPipe  param = { 0 };
			param.pf_onRead = dhDeviceControl_qisPipe_onRead;
			//
			param.uiMaxToInMs_read = CONST_toInMs_pipe_read;

			//
			initQisPipe(&qCfg, pipeName, false, _T("dhPtz"), &param, gBuf_dhDeviceControl.m_var.pQisPipe);




		}

		//
		bool b = gBuf_dhDeviceControl.m_var.m_bAutoClose_ifToolLongNoRecvd_qm;




		//
		CDeviceControlAndTimeSynchronizationDlg dlg;
		m_pMainWnd = &dlg;
		int nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with OK
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with Cancel
		}

	}  while (false);


	//
	exitQisPipe(gBuf_dhDeviceControl.m_var.pQisPipe);

	//
	exitShowInfo(&gBuf_dhDeviceControl.m_var.pShowInfoStruct);

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}






























































