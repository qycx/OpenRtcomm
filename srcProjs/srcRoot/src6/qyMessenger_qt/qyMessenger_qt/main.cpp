

#define  __noDbg_new__

#include <QApplication> 
#include    <tchar.h>  
#include	"reportingHook.h"
#include	"setDebugNew.h" 
#include    "qyMcMainCommon_qt.h"
#include	"ctxQmc_qt.h" 
#include	"GuiShare.h" 
#include "CMainFrame.h"
CMainFrame* g_pMainWndInstance = nullptr;
#include "CQmcLogin.h" 
#include "WinSerConfig.h"
#include "QyApplication.h"
extern float dpi_;
#include <iostream>
#include<Windows.h>
#include <shellscalingapi.h>
#pragma comment(lib, "Shcore.lib")
#ifdef  __DEBUG__
//#include "vld.h"
#endif
#include	"smCommProc.h"
//
BOOL				InitInstance(HINSTANCE, int);
int					ExitInstance(HINSTANCE  hInstance);



int main(int argc, char* argv[])
{
	HDC hdc = GetDC(NULL);
	int hor = GetDeviceCaps(hdc, LOGPIXELSY);
	dpi_ = (float)GetDeviceCaps(hdc, LOGPIXELSY) / 96.0;


	//
	if (dpi_ <= 1)
	{
		dpi_ = 1;
		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1.0");
	}
	else if (dpi_ == 1.75) {
		dpi_ = 1.75;
		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "2");
	}
	else if (dpi_ == 2) {
		dpi_ = 2;
		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
	}
	else if (dpi_ > 2 && dpi_ < 2.5) {
		dpi_ = 2;
		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "2.0");
	}
	else if (dpi_ >= 2.5 && dpi_ <= 3.5) {
		dpi_ = 3;
		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "3.0");
	}
	else {
		dpi_ = 1;
		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1.0");
	}
	//这句非常重要，不加这句后面谜案消息框会出现重影
	//QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
	QyApplication a(argc, argv);
	int  ret = -1;
	a.setQuitOnLastWindowClosed(false);
#if 0
	QTranslator tran;
	bool ok = tran.load("qymessenger_qt_zh.qm", QCoreApplication::applicationDirPath());
	if (ok)
	{
		a.installTranslator(&tran);
	}
#endif 

#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("main, enters"));
#endif

	GuiShare_init();
	CMainFrame* cmainFrame = nullptr;
	
	//
	if (InitInstance(nullptr, 0) == false)goto  errLabel;  
	{
		int i;
		int maxCnt = 1;
#ifdef  __DEBUG__
		//maxCnt = 10000;
#endif
		for (i=0;i<maxCnt;i++ ) {

			//
			CCtxQyMc* pQyMc = g_pQyMc;
			if (pQyMc) {
				//
				pQyMc->bGuiQuit = false;
				pQyMc->bQuit = false;
			}
			CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
			MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
			memset(&pMisCnt->refreshImObjRules, 0, sizeof(pMisCnt->refreshImObjRules));
			memset(&pMisCnt->refreshContactList, 0, sizeof(pMisCnt->refreshContactList));

			//
			int iTickCnt0 = myGetTickCount(mynull);

			//
			cmainFrame = new CMainFrame();
			if (cmainFrame == nullptr) goto errLabel;

			g_pMainWndInstance = cmainFrame;

			//
			int  iTickCnt1 = myGetTickCount(mynull);
			int iDiffInMs0 = iTickCnt1 - iTickCnt0;

			qDebug() << "CMainFrame::iDiffInMs0=" + QString::number(iDiffInMs0);



			// 
			CQmcLogin* login = new CQmcLogin(nullptr);

			int iTickCnt2 = myGetTickCount(mynull);
			int  iDiffInMs2 = iTickCnt2 - iTickCnt1;

			//
			if (login == nullptr) goto errLabel;
			ret = login->exec();
			while (ret == 100) {
				login->show();
				ret = login->exec();
			}
			delete login;
			if (ret != QDialog::Accepted) {
				goto errLabel;
			}
			// 
			cmainFrame->Init();
			cmainFrame->show();

			//
#ifdef  __DEBUG__
			traceLog((TCHAR*)_T("mainFrame.show"));
#endif

			//
			//a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
			ret = a.exec();
						
			//
			qmcLogoff();
						
			//
			if (cmainFrame) {
				g_pMainWndInstance = nullptr;
				delete cmainFrame;
				cmainFrame = nullptr;
			}

			//
			continue;
		}

	}

errLabel: 
	if (cmainFrame) {
		delete cmainFrame;
		cmainFrame = nullptr;
	}

	ExitInstance(nullptr); 

	//
#ifdef  __DEBUG__
	setFilterDebugHook();
#endif


	//
	return ret;
}




HINSTANCE  get_my_hInst(QY_MC*pQyMc)
{
	//QY_MC* pQyMc = QY_GET_GBUF();
	return  pQyMc->g_hInst;
}

//  2013/06/15
BOOL  bQnmDemo()
{
	return  FALSE;
}


//
// 
HINSTANCE	g_hInst = NULL;							// current instance
//
struct {
	BOOL	bCoInited;
}			g_status_qmc;


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



#if  0
	HWND hWnd;

	//
	hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_ts_main), NULL, (DLGPROC)DialogProc_ts_main);
	if (!hWnd) {
		goto  errLabel;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
#endif

	//
#if  0
	CqyMc_tsDlg* pDlg = NULL;
	RECT							rect;

	pDlg = new  CqyMc_tsDlg;
	if (!pDlg->Create(rect))  return  FALSE;
#endif

#if  0
	//
	int  flg = SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW;
	SetWindowPos(pDlg->m_hWnd, NULL, 0, 0, 0, 0, flg);
#endif

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

