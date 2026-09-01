
#include "stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qyMessenger_ts_noMfc.h"

#include	"isCliHelpPublic.h"
#include	"isCliD3dPublic.h"
#include	"qyMc_tsDlg_noMfc.h"

#include	"ctxQmc_gui.h"
#include	"dyn_isCliD3d_public.h"
#include	"qyMessengerHelpPublic.h"
#include	"GuiShare.h"
#include	"tmpFfmpegPublic.h"
//
#include	"qyMcExt_gui.h"


//
extern HINSTANCE	g_hInst;							// current instance



extern StatusQmc g_status_qmc;


//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	BOOL	bRet = FALSE;

	g_hInst = hInstance; // Store instance handle in our global variable

	//
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	//
#ifdef  __USE_oleInit__
	if (S_OK != OleInitialize(NULL)) {
		return  FALSE;
	}
#else
	DWORD dwCoInit = COINIT_APARTMENTTHREADED;	// COINIT_MULTITHREADED. 2013/06/17		
	if (!SUCCEEDED(CoInitializeEx(NULL, dwCoInit))) {
		return  FALSE;
	}
#endif
	g_status_qmc.bCoInited = TRUE;

	//
	set_cur_iResId_sys(CONST_resId_sys_isCli_ts);


	//  2015/07/08
	try {
		g_pQyMc = new  CCtxQyMc;
		if (!g_pQyMc)  goto  errLabel;
		//
		g_pQyMc->m_pQyMcExtTmpl = new QyMcExt_gui();
		if (!g_pQyMc->m_pQyMcExtTmpl)  goto  errLabel;
		g_pQyMc->m_pQyMcExtTmpl->m_var.m_pQyMc = g_pQyMc;

	}
	catch (...) {
		goto  errLabel;
	}
	//
	//  2016/08/12
	PARAM_initQyMc  param;
	memset(&param, 0, sizeof(param));
	param.pfNewVar = newVar_isCli_gui;
	param.pfFreeVar = freeVar_isCli_gui;
	//
	if (initQyMc(g_hInst, &param, g_pQyMc))   goto  errLabel;
	//



	//
	CqyMc_tsDlg* pDlg = NULL;
	RECT							rect;

	pDlg = new  CqyMc_tsDlg;
	pDlg->var.pQyMc = g_pQyMc;
	if (!pDlg->Create(rect))  return  FALSE;



	//
	bRet = TRUE;
errLabel:

	return  bRet;
}

int ExitInstance(HINSTANCE  hInstance)
{
	int		iErr = -1;

	

	//
	exitQyMc(g_pQyMc);
	//  2015/07/08
	if (g_pQyMc) {
		QY_MC* pQyMc = (QY_MC*)g_pQyMc;
		//
		if (pQyMc->m_pQyMcExtTmpl) {
			MACRO_safeDelete(pQyMc->m_pQyMcExtTmpl);
		}
		//
		MACRO_safeDelete(pQyMc);
		g_pQyMc = NULL;
	}


	//
	if (g_status_qmc.bCoInited) {
#ifdef  __USE_oleInit__
		OleUninitialize();
#else
		CoUninitialize();
#endif

		g_status_qmc.bCoInited = FALSE;
	}

	//
	iErr = 0;
errLabel:
	return  iErr;
}

