// qyDecTool.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "qyDecTool.h"
#include	"qyDecToolCommon.h"
#include	"qyDecToolCommon.h"

#include	"qmcVideoCapture.h"
#include	"policyAvParams.h"
#include	"taskAv.h"
#include	"tmpGuiOpenFunc.h"
#include	"qyMcMainCommon.h"
#include	"qySyncCommProc.h"
#include	"qyDynLib.h"
#include	"qmcVideoCapture_rtsp.h"

#include	"load_isD3dFunc.h"

//
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

//
CQyDecTool	g_tool;

//
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	
#ifdef  __DEBUG__
	OutputDebugString(  _T(  "dvt enters\n"  )  );
#endif


	//
	if  (  g_tool.init(  lpCmdLine  )  )  goto  errLabel;

	g_tool.run(  );

errLabel:
	g_tool.exit(  );


#ifdef  __DEBUG__
	OutputDebugString(  _T(  "dvt leaves\n"  )  );
#endif

	//	
	showInfo_open0(  0,  0,  _T(  "ends"  )  );


	return 0;
}




//
//
extern  CQyDecTool	g_tool;


//
void  *  dvt_qoi_getPtrProperty(  void  *  pQdcObjInfoParam,  int  propertyId  )
{
	CCtxQmcDvt  *  pProcInfo  =  g_tool.m_var.pCtx;
	if  (  !pProcInfo  )  return  NULL;

	return  get_ptr_isD3dFunc(  pProcInfo->m_var.pDynLib_isD3dFunc,  propertyId  );

}
