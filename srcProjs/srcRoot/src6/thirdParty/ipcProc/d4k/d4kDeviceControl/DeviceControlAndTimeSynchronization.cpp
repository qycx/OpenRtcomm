// DeviceControlAndTimeSynchronization.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DeviceControlAndTimeSynchronization.h"
#include "DeviceControlAndTimeSynchronizationDlg.h"

#include "d4kDeviceControlProc.h"
#include <ctxQmThread.h>
#include <showInfo_open.h>

//
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <stdio.h>
#include <tchar.h>

char* UnicodeToAnsi(const wchar_t* szStr, int& nLen)
{
	nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
	return pResult;
}

#include <chrono>
#include <sstream>
#include <iomanip>

std::string getDT() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	std::tm* now_tm = std::localtime(&now_time);

	std::stringstream ss;

	ss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S.");

	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
	ss << std::setw(3) << std::setfill('0') << millis.count();

	return ss.str();
}



int printLogChar(const char* log) {
	//return 0;
	//if (!gBuf_dhDeviceControl.m_var.appParams.log)
	//	return 0;
	FILE* pf = fopen("D:/qycx/d4kDeviceControl.txt", "a+");
	if (pf == NULL)
	{
		perror("打开文件失败！");
		return 1;
	}

	//TCHAR* pp;


	//fprintf(pf, "%s:%s  - %s \n", __DATE__, __TIME__, log);
	fprintf(pf, "[%s]  - %s \n", getDT().c_str(), log);

	fclose(pf);

	return 0;

}


int printLog(TCHAR* log) {
	//return 0;
	//if (!gBuf_dhDeviceControl.m_var.appParams.log)
	//	return 0;
	FILE* pf = fopen("D:\\qycx\\d4kDeviceControl.txt", "a+");
	if (pf == NULL)
	{
		perror("打开文件失败！");
		return 1;
	}

	//TCHAR* pp;

	char* pBuf = NULL;
	int nLen = 0;

	pBuf = UnicodeToAnsi(log, nLen);

	if (pBuf) {
		fprintf(pf, "[%s]  - %s \n", getDT().c_str(), pBuf);
		delete[] pBuf;
	}

	fclose(pf);

}

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
	printLogChar("------------------InitInstance------------begin---------------");
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
		if (initShowInfo_func(0, _T("syncQ_showInfo_d4k"), errHintWndCls, false, true, (char*)"127.0.0.1", bCli, &gBuf_dhDeviceControl.m_var.pShowInfoStruct)) {
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
				showInfo_open0(0, 0, _T("d4kDeviceControl: nvrIp is null, failed"));
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
			M_get_pipeName(CONST_ipcProcPipePrefix, _T(""), CONST_ipcProcPipe_tn_d4kDeviceControl, pipeName);


			//
			PARAM_initQisPipe  param = { 0 };
			param.pf_onRead = dhDeviceControl_qisPipe_onRead;
			//
			param.uiMaxToInMs_read = CONST_toInMs_pipe_read;

			//
			initQisPipe(&qCfg, pipeName, false, _T("d4k.deviceControl"), &param, gBuf_dhDeviceControl.m_var.pQisPipe);




		}

		//
		bool b = gBuf_dhDeviceControl.m_var.m_bAutoClose_ifToolLongNoRecvd_qm;




		//
		/*
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
		*/

		for (; ; ) {

			//
			if (gBuf_dhDeviceControl.m_var.m_bDone_nvrInfo)	{
				//
				//Sleep(1000);
				//
				break;
			}

			//
			if (gBuf_dhDeviceControl.m_var.m_bAutoClose_ifToolLongNoRecvd_qm) {
				//
				DWORD  dwTickCnt = myGetTickCount(nullptr);
				int iDiffInMs = dwTickCnt - gBuf_dhDeviceControl.m_var.dwLastTickCnt_recvd;
				if (abs(iDiffInMs) > CONST_toInMs_ipcProc) {
					//
					showInfo_open0(0, _T("d4kDeviceControl"), _T("too long to recv, quit now\n"));
					//
					break;
				}
			}


			//
			Sleep(1000);

			//
			continue;
		}

		//
		

	}  while (false);


	//
	exitQisPipe(gBuf_dhDeviceControl.m_var.pQisPipe);

	//
	exitShowInfo(&gBuf_dhDeviceControl.m_var.pShowInfoStruct);

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}






























































