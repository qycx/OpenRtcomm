
#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<WinSock2.h>
#include	"qyCommon.h"
#include	"qyWnd.h"

#include	<assert.h>

//  2017/11/01
#include	"qmShellPublic.h"

//
CQyWnd::CQyWnd(  )
{
	this->m_hWnd  =  NULL;
#if  0
	this->iWndContentType  =  0;
	this->iSubType  =  0;
#endif
	memset(  &m_var,  0,  sizeof(  m_var  )  );

}


CQyWnd::~CQyWnd(  )
{
}


int  CQyWnd::getWndContentType(  )
{
	return  m_var.iWndContentType;
}

//  2012/04/02
int  CQyWnd::getWndContentSubtype(  )
{
	return  m_var.iSubtype;
}

#if  0
BOOL CQyWnd::Attach(  HWND hWndNew  )
{
	if  (  !IsWindow(  hWndNew  )  )  return  FALSE;

	SetWindowLong(  hWndNew,  GWL_USERDATA,  (  LONG_PTR  )this  );
	this->m_hWnd  =  hWndNew;

	return  TRUE;
}
#endif

	
CQyWnd* CQyWnd::FromHandle(  HWND  hWnd  )
{
	CQyWnd  *  pWnd  =  (  CQyWnd  *  )GetWindowLongPtr(  hWnd,  GWLP_USERDATA  );
	return  pWnd;
}

CQyWnd* CQyWnd::FromHandlePermanent(HWND hWnd)
{
	CQyWnd  *  pWnd  =  (  CQyWnd  *  )GetWindowLongPtr(  hWnd,  GWLP_USERDATA  );
	return  pWnd;
}




 //
 __declspec(  dllexport  )  int  centerWnd(  HWND  hWnd  )
{
	RECT	rc;
	int		cx,  cy;

	GetWindowRect(  hWnd,  &rc  );
	cx  =  rc.right  -  rc.left;
	cy  =  rc.bottom  -  rc.top;

	SetWindowPos(  hWnd,  HWND_TOP,  GetSystemMetrics(  SM_CXSCREEN  )  /  2  -  cx  /  2,  GetSystemMetrics(  SM_CYSCREEN  )  /  2  -  cy  /  2,  0,  0,  SWP_NOSIZE  );
	
	return  0;
}


 //
 __declspec(  dllexport  )  int  centerWndInParent(  HWND  hWnd,  HWND  hParent  )
 {
	    if  (  !IsWindow(  hWnd  )  )  return  -1;
		if  (  !IsWindow(  hParent  )  )  return  -1;

		HWND  hDlg  =  hWnd;

		RECT  rc;
		int  iW_dlg,  iH_dlg;

		GetClientRect(  hParent,  &rc  );
		int  iW_parent  =  rc.right  -  rc.left;
		int  iH_parent  =  rc.bottom  -  rc.top;
		
		RECT  rc_ia;
		GetWindowRect(  hDlg,  &rc_ia  );
		//
		iW_dlg  =  rc_ia.right  -  rc_ia.left;
		iH_dlg  =  rc_ia.bottom  -  rc_ia.top;
		
		//
		int  iL  =  (  iW_parent  -  iW_dlg  )  /  2;
		if  (  iL  <  0  )  iL  =  0;
		int  iT  =  (  iH_parent  -  iH_dlg  )  /  2;
		if  (  iT  <  0  )  iT  =  0;
		//
		POINT  pnt;
		pnt.x  =  rc.left  +  iL;
		pnt.y  =  rc.top  +  iT;
		//
		MapWindowPoints(  hParent,  NULL,  &pnt,  1  );
		//
		MoveWindow(  hDlg,  pnt.x,  pnt.y,  iW_dlg,  iH_dlg,  TRUE  );

		return  0;
 }


 //
 __declspec(  dllexport  )  int  makeDlgResizable(  HWND  hDlg  )
{
	DWORD	dwStyle;  dwStyle  =  GetWindowLong(  hDlg,  GWL_STYLE  );
	if  (  !(  dwStyle  &  WS_THICKFRAME  )  )  {		  
		dwStyle  |=  WS_THICKFRAME;
		SetWindowLong(  hDlg,  GWL_STYLE,  dwStyle  );
		//
		HMENU	hMenu  =  GetSystemMenu(  hDlg,  FALSE  );
		if  (  hMenu  )  {
			InsertMenu(  hMenu,  0,  MF_BYPOSITION  |  MF_STRING,  SC_SIZE,  _T(  "&Size"  )  );
		}
	}
	return  0;
 }


 __declspec(  dllexport  )  int  makeWndNoBorder(  HWND  hWnd,  BOOL  bThin,  HMENU  *  phMenu,  long  *  plStyle  ) 
{
	long  lStyle	=	0;
	lStyle  =  GetWindowLong(  hWnd,  GWL_STYLE  );
	//  2012/07/07
	if  (  plStyle  )  *plStyle  =  lStyle;
	//
	lStyle  &=  ~(  WS_CAPTION  |  WS_THICKFRAME  );
	if  (  bThin  )  lStyle  |=  WS_BORDER;
	SetWindowLong(  hWnd,  GWL_STYLE,  lStyle  );


	HMENU	hMenu	=	GetMenu(  hWnd  );
	//
	::SetMenu(  hWnd,  NULL  );
	if  (  !phMenu  )  {
		if  (  hMenu  )  DestroyMenu(  hMenu  );
		}
	else  {
		  *phMenu  =  hMenu;
	}

	return  0;
}

 int  restoreWndBorder(  HWND  hWnd,  HMENU  *  phMenu,  long  *  plStyle  )
{
	 if  (  !phMenu  ||  !plStyle  )  return  -1;

	 long	lStyle  =  *plStyle;
	 SetWindowLong(  hWnd,  GWL_STYLE,  lStyle  );


	 //
	 BOOL	bRet;	 
	 bRet  =  ::SetMenu(  hWnd,  *phMenu  );
	 if  (  bRet  )  {
		 *phMenu  =  NULL;		
	 }
					  
	 return  0;
 }


 void  SetClientSize(  HWND  hWnd,  int  clientWidth,  int  clientHeight  )
{
	if  (  IsWindow(  hWnd  )  )
	{
		DWORD  dwStyle  =  GetWindowLongPtr(  hWnd,  GWL_STYLE  );
		DWORD  dwExStyle  =  GetWindowLongPtr(  hWnd,  GWL_EXSTYLE  );
		HMENU  menu  =  GetMenu(  hWnd  );

		RECT  rc  =  {  0,  0,  clientWidth,  clientHeight  };

		if  (  !AdjustWindowRectEx(  &rc,  dwStyle,  menu  ?  TRUE  :FALSE,  dwExStyle  )  )
			MessageBox(  NULL,  L"AdjustWindowRectEx Failed",  L"error",  MB_OK  );

		SetWindowPos(  hWnd,  NULL,  0,  0,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  SWP_NOZORDER  |  SWP_NOMOVE  );

#ifdef  _DEBUG
		RECT  newClientRC;
		GetClientRect(  hWnd,  &newClientRC  );
		//
		if (!(newClientRC.right - newClientRC.left) == clientWidth) {
			traceLog((TCHAR*)_T("SetClientSize error: w not ok"));
		}
		if (!(newClientRC.bottom - newClientRC.top) == clientHeight) {
			traceLog((TCHAR*)_T("SetClientSize error: h not ok"));
		}
#endif
	}
}


 void  SetClientSizeAndPos(  HWND  hWnd,  int  clientWidth,  int  clientHeight,  int  xPos,  int  yPos  )
{
	if  (  IsWindow(  hWnd  )  )
	{
		DWORD  dwStyle  =  GetWindowLongPtr(  hWnd,  GWL_STYLE  );
		DWORD  dwExStyle  =  GetWindowLongPtr(  hWnd,  GWL_EXSTYLE  );
		HMENU  menu  =  GetMenu(  hWnd  );

		RECT  rc  =  {  0,  0,  clientWidth,  clientHeight  };

		if  (  !AdjustWindowRectEx(  &rc,  dwStyle,  menu  ?  TRUE  :FALSE,  dwExStyle  )  )
			MessageBox(  NULL,  _T("AdjustWindowRectEx Failed"),  _T("error"),  MB_OK  );

		SetWindowPos(  hWnd,  NULL,  xPos,  yPos,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  SWP_NOZORDER  );

#ifdef  _DEBUG
		RECT  newClientRC;
		GetClientRect(  hWnd,  &newClientRC  );
		assert(  (  newClientRC.right  -  newClientRC.left  )  ==  clientWidth  );
		assert(  (  newClientRC.bottom  -  newClientRC.top  )  ==  clientHeight  );
#endif
	}
}
