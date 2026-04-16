// qyMessenger_ts_noMfc.cpp : Defines the entry point for the application.
//

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
//#include	"tmpFfmpegPublic.h"

//
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE	g_hInst  =  NULL;							// current instance

StatusQmc g_status_qmc;


//  2013/10/05. //  注意: g_usIntervalInMs_myRender在需要的时候是可以设置调节的, 以便实现性能和视频流畅性的平衡
unsigned  short		g_usIntervalInMs_myRender = 0;// 5;		//  1;	


//
TCHAR		szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR		szWindowClass[MAX_LOADSTRING];			// the main window class name

 //  2013/06/10. 每个模块自己定义
 HINSTANCE  get_my_hInst(  CCtxQyMc  *  pQyMc  )
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
#ifdef  __DEBUG__
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif 

	//
	GuiShare_init(  );

	// Perform application initialization:
	if  (  !InitInstance (hInstance, nCmdShow)  )  {
		goto  errLabel;
	}
	//
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;

	//
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QYMESSENGER_TS_NOMFC));

	// Main message loop:
	while (  msg.message  !=  WM_QUIT  )  {
		  BOOL  bActive  =  TRUE;
		  BOOL  bGotMsg  =  FALSE;
		  //
		  if  (  dyn_bD3dUsing(  pProcInfo,  &bActive  )  )  {
			  //
			  if (pProcInfo->bUse_dx11()) {
				  if (bActive)  bGotMsg = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
				  else  bGotMsg = GetMessage(&msg, NULL, 0, 0);
			  }
			  else {
				  bGotMsg = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
			  }
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
			  else  {  
				    //				  
				    //if (pProcInfo->bUse_dx11()) 
					{					
						dyn_myRender();
						if (g_usIntervalInMs_myRender) {
							Sleep(g_usIntervalInMs_myRender);	//  Sleep(  1  );	//  2013/09/09
						}
				    }				  
					//
			  }
			  //
			  }
		  else  {
			    if (!GetMessage(&msg, NULL, 0, 0))  break;

				if (!IsWindow(msg.hwnd)) {
					continue;
				}
	
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))  {
					
					if  (  dll_PreTranslateMessage_isCliHelp(  &msg  )  )  continue;					
					if  (  dll_PreTranslateMessage_qyMessengerHelp(  &msg  )  )  continue;
					
					TranslateMessage(&msg);
					DispatchMessage(&msg);		
				}

		  }

		  //
		  continue;
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



