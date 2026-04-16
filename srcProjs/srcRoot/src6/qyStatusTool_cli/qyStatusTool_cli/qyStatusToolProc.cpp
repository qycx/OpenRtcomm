

#include	"stdAfx.h"
#include	"qyStatusToolCommon.h"
#include	"qyStatusTool.h"
#include	"qyPs.h"

/*

*/ 

BOOL  bStatusThreadProcQuit  =  FALSE;

 LRESULT CALLBACK myMainWndProc(  HWND  hwnd,  UINT  uMsg,  WPARAM  wParam,  LPARAM  lParam  )    // second message parameter
{ 
 
	//traceLogA(  "myMainWndProc: uMsg is %d",  uMsg  );

    switch  (  uMsg  )  { 
        case WM_CREATE: 
            // Initialize the window. 
			SetTimer(  hwnd,  1,  1000,  0  );		//  奇怪，好象有了timer就可以正常处理了
            return 0; 
 
        case WM_PAINT: 
            // Paint the window's client area. 
            return 0; 
 
        case WM_SIZE: 
            // Set the size and position of the window. 
            return 0; 
 
		case  WM_COPYDATA:  {
			  traceLogA(  "WM_COPYDATA here"  );
			  CWinApp	*	pApp		=	AfxGetApp(  );
			  CWnd		*	pMainWnd	=	NULL;
			  HWND			hWnd		=	NULL;
			  
			  if  (  pApp  )  {
				  CWnd  *  pMainWnd	=	pApp->m_pMainWnd;
				  if  (  pMainWnd  )  {
					  hWnd  =  pMainWnd->m_hWnd;
					  if  (  hWnd  )  SendMessage(  hWnd,  uMsg,  wParam,  lParam  );			
				  }				  
			  }
				
			  }
			  return  0;
		case  WM_TIMER:

			  return  0;
		// 
        // Process other messages. 
        // 
 
        default: 
            return DefWindowProc(hwnd, uMsg, wParam, lParam); 
    } 
    return 0; 
} 


BOOL InitApplication(HINSTANCE hinstance) 
{ 
    WNDCLASSEX wcx; 
 
    // Fill in the window class structure with parameters 
    // that describe the main window. 
 
    wcx.cbSize = sizeof(wcx);          // size of structure 
    wcx.style = 0;                    // redraw if size changes 
    wcx.lpfnWndProc = myMainWndProc;     // points to window procedure 
    wcx.cbClsExtra = 0;                // no extra class memory 
    wcx.cbWndExtra = 0;                // no extra window memory 
    wcx.hInstance = hinstance;         // handle to instance 
    wcx.hIcon = 0;              // predefined app. icon 
    wcx.hCursor = 0;                    // predefined arrow 
    wcx.hbrBackground = 0;                  // white background brush 
    wcx.lpszMenuName =  0;    // name of menu resource 
    wcx.lpszClassName = gStatusToolWndCls;  // name of window class 
    wcx.hIconSm = 0; 
 
    // Register the window class. 

 
    return  RegisterClassEx(&wcx); 
} 

//
HWND  g_statusToolWnd  =  NULL;


//
BOOL InitInstance(HINSTANCE hinstance, int nCmdShow) 
{ 
    HWND hwnd; 
 
    // Save the application-instance handle. 
 
    //  hinst = hinstance; 
 
    // Create the main window. 
 
    hwnd = CreateWindow( 
        gStatusToolWndCls,        // name of window class 
        _T(  "Sample"  ),            // title-bar string 
        WS_OVERLAPPEDWINDOW, // top-level window 
        CW_USEDEFAULT,       // default horizontal position 
        CW_USEDEFAULT,       // default vertical position 
        CW_USEDEFAULT,       // default width 
        CW_USEDEFAULT,       // default height 
        (HWND) NULL,         // no owner window 
        (HMENU) NULL,        // use class menu 
        hinstance,           // handle to application instance 
        (LPVOID) NULL);      // no window-creation data 
 
    if (!hwnd) 
        return FALSE; 
 
    // Show the window and send a WM_PAINT message to the window 
    // procedure. 
	g_statusToolWnd  =  hwnd;
 

	//
    return TRUE; 
 
} 


 DWORD  WINAPI  qyStatusToolThreadProc(  LPVOID  lpParameter  )
{
	int						iErr			=	-1;
	QY_STATUS_STRUCT	*	pStatusStruct	=	(  QY_STATUS_STRUCT  *  )lpParameter;
	HINSTANCE				hinstance		=	GetModuleHandle(  0  );
	MSG						msg; 
	BOOL					bRet;
 
    if  (  !InitApplication(  hinstance  )  )  goto  errLabel;		//  这里没有清理注册的类和窗口，2006/08/16
 
    if  (  !InitInstance(  hinstance,  0  )  )  goto  errLabel;
 
    while  (  (  bRet  =  GetMessage(  &msg,  (  HWND  )NULL,  0,  0  )  )  !=  0  )  { 
			if (  msg.message  ==  WM_QUIT  )  {
				break;
			}
		   
		   if  (  bRet  ==  -1  )  {
			   //AfxMessageBox(  _T(  "GetMessage error"  )  );  
			   break;
		   }
		   if  (  pStatusStruct->bQuit  )  {
			   break;
		   }
        
		   TranslateMessage(  &msg  ); 
		   DispatchMessage(  &msg  ); 
    } 

	iErr  =  0;

errLabel:

    return  iErr; 

}

 
