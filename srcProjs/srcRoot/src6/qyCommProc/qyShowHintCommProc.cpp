
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<windows.h>
#include	<stdlib.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommProc.h"
#include	"qyTCharCommProc.h"
#include	"tmpCeLib.h"




#ifndef  __APP_qyMc_touchscreen__

int  WINAPI  myMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType  );

 int  WINAPI  tmpMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType  )
{
#ifdef  __DEBUG__
		traceLog(  (TCHAR*)_T(  "myMessageBox,  test_wince"  )  );
#endif
	//  return  MessageBox(  hWnd ,  lpText,  lpCaption,  uType  );
	return  myMessageBox(  NULL,  lpText,  lpCaption,  uType  |  MB_TASKMODAL  );
}
#else

#define	tmpMessageBox	myMessageBox

 int  WINAPI  myMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType  );

#endif


 extern  "C"  int  qyShowHint(  LPCTSTR  fmt,  ...  )
{
	
	 va_list args;
	 int		errnoBuf;
	 TCHAR		buf[2048]			=	_T(  ""  );
	 int		n					=	0;
			 
	 errnoBuf	=	errno;
	 va_start(  args,  fmt  );

	 n	=  _vsntprintf(  buf,  mycountof(  buf  )  -  2,  fmt, args  );
	 if  ( n >= 0 )  {
		 buf[n]  =  '\n';
		 buf[n + 1]  =  0;			
	 }
		
	 va_end(  args  );

	 if  (  buf[0]  )  {
		 tmpMessageBox(  NULL,  buf,  _T(  "QYCX"  ), MB_OK );
	 }
		
	 errno  =  errnoBuf; 

	 return 0;

}

 extern  "C"  int  qyShowHint1(  HWND  hWnd,  LPCTSTR  fmt,  ...  )
{
	
	 va_list args;
	 int		errnoBuf;
	 TCHAR		buf[2048]			=	_T(  ""  );
	 int		n					=	0;
			 
	 errnoBuf	=	errno;
	 va_start(  args,  fmt  );

	 n	=  _vsntprintf(  buf,  mycountof(  buf  )  -  2,  fmt, args  );
	 if  ( n >= 0 )  {
		 buf[n]  =  '\n';
		 buf[n + 1]  =  0;			
	 }
		
	 va_end(  args  );

	 if  (  buf[0]  )  {
		 tmpMessageBox(  hWnd,  buf,  _T(  "QYCX"  ), MB_OK );
	 }
		
	 errno  =  errnoBuf; 

	 return 0;

}

 extern "C" int qyDebugHint(  LPCTSTR fmt, ... )
{
	#ifndef __DEBUG__
		return 0;
	#else
	 
		va_list args;
		int		errnoBuf;
		TCHAR	buf[2048]			=	_T(  ""  );
		int		n					=	0;
			 
		errnoBuf	=	errno;
		va_start(  args,  fmt  );

		n	=	_vsntprintf(  buf,  mycountof(  buf  )  -  2,  fmt, args  );
		if  ( n >= 0 )  {
			buf[n]  =  '\n';
			buf[n + 1]  =  0;
		}
		
		va_end(  args  );
	
		if  (  buf[0]  )  {
			tmpMessageBox(  NULL, buf, _T(  "QYCX Debug"  ), MB_OK );
		}

		errno  =  errnoBuf; 

		return 0;

	#endif

}


