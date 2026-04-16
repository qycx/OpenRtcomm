// qyMessenger_ts_noMfc.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qyMcu.h"

#include	"isCliHelpPublic.h"
#include	"isCliD3dPublic.h"
#include	"qyMc_tsDlg_noMfc.h"

#include	"ctxQmc_qyMcu.h"
#include	"dyn_isCliD3d_public.h"
#include	"qyMessengerHelpPublic.h"
#include	"GuiShare.h"
#include	"tmpFfmpegPublic.h"

//
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE	g_hInst  =  NULL;							// current instance
//
struct		{
	BOOL	bCoInited;
}			g_status_qmc;

//  2013/10/05. //  注意: g_usIntervalInMs_myRender在需要的时候是可以设置调节的, 以便实现性能和视频流畅性的平衡
unsigned  short		g_usIntervalInMs_myRender	=	5;		//  1;	


//
TCHAR		szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR		szWindowClass[MAX_LOADSTRING];			// the main window class name

 //  2013/06/10. 每个模块自己定义
 HINSTANCE  get_my_hInst( QY_MC  *  pQyMc )
{
	//QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	return  pQyMc->g_hInst;
}

 //  2013/06/15
 BOOL  bQnmDemo(  )
{
	return  FALSE;
}


// Forward declarations of functions included in this code module:
BOOL				InitInstance(HINSTANCE, int);
int					ExitInstance(  HINSTANCE  hInstance  );

//  LRESULT CALLBACK	DialogProc_ts_main(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	//
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable  =  NULL;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_QYMESSENGER_TS_NOMFC, szWindowClass, MAX_LOADSTRING);

	//
	memset(  &msg,  0,  sizeof(  msg  )  );
	memset(  &g_status_qmc,  0,  sizeof(  g_status_qmc  )  );

	//
	GuiShare_init(  );

	// Perform application initialization:
	if  (  !InitInstance (hInstance, nCmdShow)  )  {
		goto  errLabel;
	}
	//
	CCtxQyMc  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;
	TCHAR tBuf[128];

	//
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QYMESSENGER_TS_NOMFC));

	// Main message loop:
	while (  msg.message  !=  WM_QUIT  )  {
		  BOOL  bActive  =  TRUE;
		  BOOL  bGotMsg  =  FALSE;
		  //
		  if  (  dyn_bD3dUsing(  pProcInfo,  &bActive  )  )  {
#if  0
			  if  (  bActive  )  bGotMsg  =  PeekMessage(&msg, NULL, 0, 0,PM_REMOVE);
			  else  bGotMsg  =  GetMessage(  &msg,  NULL,  0,  0  );
#endif
			  //
			  bGotMsg  =  PeekMessage(&msg, NULL, 0, 0,PM_REMOVE);

			  //
			  if  (  bGotMsg  )  {
				  if  (  !TranslateAccelerator(msg.hwnd, hAccelTable, &msg)  )  {

					  if  (  dll_PreTranslateMessage_isCliHelp(  &msg  )  )  continue;
					  if  (  dll_PreTranslateMessage_qyMessengerHelp(  &msg  )  )  continue;
					  				  
					  //
					  TranslateMessage(&msg);
					  DispatchMessage(&msg);		
				  }
				  }			
			  else  {  //  
				     dyn_myRender(  );			
					 //
					 if  (  pQyMc->appParams.bService  )  {
						 static  DWORD  sdwTickCnt_calcFps  =  0;

						 float  fps_suggested  =  pProcInfo->cfg.render.fps_suggested;						
						 if  (  fps_suggested  <  1  )  fps_suggested  =  1;						
						 float  fps  =  pProcInfo->status.render.fps;

						 if  (  pProcInfo->status.render.dwTickCnt_calcFps  !=  sdwTickCnt_calcFps  )  {
							 sdwTickCnt_calcFps  =  pProcInfo->status.render.dwTickCnt_calcFps;
							 //
							 if  (  fps  >  fps_suggested  +  1  )  {
								 g_usIntervalInMs_myRender  +=  (  1000  /  fps_suggested  -  1000  /  fps  )  /  2;						 
							 }
							 else  if  (  fps  <  fps_suggested  -  1  )  {
								       g_usIntervalInMs_myRender  --  ;
							 }
							 //
							 #if  0
								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "modified: fps_sug %03f, fps %03f, interval %dms"  ),  fps_suggested,  fps,  g_usIntervalInMs_myRender  );							
								  showInfo_open0(  0,  0,  tBuf  );
							 #endif
						 }

						 if  (  g_usIntervalInMs_myRender  <  5  )  {
							   g_usIntervalInMs_myRender  =  5;
						 }
						 //
	 					 #ifdef  __DEBUG__
							#if  0
							_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "fps_sug %03f, fps %03f, interval %dms"  ),  fps_suggested,  fps,  g_usIntervalInMs_myRender  );
							showInfo_open0(  0,  0,  tBuf  );
							#endif
						 #endif
						 }
					 else  {
						   g_usIntervalInMs_myRender  =  5;
					 }
					 //
					 //
					 Sleep(  g_usIntervalInMs_myRender  );	//  Sleep(  1  );	//  2013/09/09

			  }
			  }
		  else  {
			    if (!GetMessage(&msg, NULL, 0, 0))  break;

				//
				if (!IsWindow(msg.hwnd)) {
					continue;
				}

				//
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))  {
					
					if  (  dll_PreTranslateMessage_isCliHelp(  &msg  )  )  continue;					
					if  (  dll_PreTranslateMessage_qyMessengerHelp(  &msg  )  )  continue;
					
					TranslateMessage(&msg);
					DispatchMessage(&msg);		
				}

		  }
	}


errLabel:
	//
	ExitInstance(  hInstance  );

	//
	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//

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
	BOOL	bRet	=	FALSE;
	
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
	if  (  S_OK  !=  OleInitialize(  NULL  )  )  {
		return  FALSE;
	}
#else
	DWORD dwCoInit  =  COINIT_APARTMENTTHREADED;	// COINIT_MULTITHREADED. 2013/06/17		
	if  (  !SUCCEEDED(  CoInitializeEx(  NULL,  dwCoInit  )  )  )  {
		return  FALSE;
	}
#endif
	g_status_qmc.bCoInited  =  TRUE;
	
	//
	set_cur_iResId_sys(  CONST_resId_sys_isCli_ts  );


	//  2015/07/08
	try  {
		 g_pQyMc  =  new  CCtxQyMc;
		 if  (  !g_pQyMc  )  goto  errLabel;
		 }
	catch  (  ...  )  {
		   goto  errLabel;
	}
	//
	//  2016/08/12
	PARAM_initQyMc  param;
	memset(  &param,  0,  sizeof(  param  )  );
	param.pfNewVar  =  newVar_isCli_gui;
	param.pfFreeVar  =  freeVar_isCli_gui;
	//
	if  (  initQyMc(  g_hInst,  &param,  g_pQyMc  )  )   goto  errLabel;



#if  0
		HWND hWnd;

   //
   hWnd = CreateDialog(hInstance,  MAKEINTRESOURCE(IDD_ts_main), NULL,  (DLGPROC)DialogProc_ts_main);
   if (!hWnd)  {
	   goto  errLabel;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
#endif

    //
   	CqyMc_tsDlg  *  pDlg  =  NULL;
	RECT							rect;

	pDlg  =  new  CqyMc_tsDlg;
	if  (  !pDlg->Create(  rect  )  )  return  FALSE;

#if  0
	//
	int  flg  =  SWP_NOMOVE  |  SWP_NOSIZE  |  SWP_NOACTIVATE  |  SWP_SHOWWINDOW;	
	SetWindowPos(  pDlg->m_hWnd,  NULL,  0,  0,  0,  0,  flg  );
#endif

   bRet  =  TRUE;
errLabel:

   return  bRet;
}

 int ExitInstance(  HINSTANCE  hInstance  )
{
	int		iErr	=	-1;


	//
	exitQyMc(  g_pQyMc );
	//  2015/07/08
	if  (  g_pQyMc  )  {
		QY_MC  *  pQyMc  =  (  QY_MC  *  )g_pQyMc;
		MACRO_safeDelete(  pQyMc  );
		g_pQyMc  =  NULL;
	}

	
	//
	if  (  g_status_qmc.bCoInited  )  {
		#ifdef  __USE_oleInit__
				OleUninitialize(  );
		#else
				CoUninitialize(  );  
		#endif
		
		g_status_qmc.bCoInited  =  FALSE;
	}

	//
	iErr  =  0;
errLabel:
	return  iErr;
}

#if  0
LRESULT CALLBACK DialogProc_ts_main(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetWindowPos(hWnd,NULL, 200,200,0,0,SWP_NOSIZE);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if  (  LOWORD(  wParam  )  ==  IDC_BUTTON_contact  )  {
			#ifdef  __DEBUG__
					showProgress(  hWnd,  _T(  "Waiting..."  ),  _T(  ""  ),  30,  0,  50  );
			#endif
			return  TRUE;
		}
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			//  PostQuitMessage(0);
			DestroyWindow(  hWnd  );
			OutputDebugString(  _T(  "kkd\n"  )  );
			
			//
			PostQuitMessage(0);

			return (INT_PTR)TRUE;
		}
		break;
	case  WM_NCDESTROY:
		  OutputDebugString(  _T(  "kk\n"  )  );
		  if  (  IsWindow(  hWnd  )  )  OutputDebugString(  _T(  "wnd\n"  )  );
		  else  OutputDebugString(  _T(  "false\n"  )  );

		  break;
	case WM_DESTROY:
		//  PostQuitMessage(0);
		OutputDebugString(  _T(  "WM_DESTROY\n"  )  );
		break;
	//default:
		//return DefWindowProc(hWnd, uMsg, wParam, lParam);	
	}
	return (INT_PTR)FALSE;
}
#endif



