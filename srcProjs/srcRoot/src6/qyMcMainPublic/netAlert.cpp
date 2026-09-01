

#include	"stdafx.h"
#include	<wtsapi32.h>
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyCusResTemp.h"

#if  0

#ifndef  __WINCE__
 int  WINAPI  myMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType  )
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

#ifdef  __DEBUG__
		traceLog(  _T(  "myMessageBox,  test_wince"  )  );
#endif

#ifndef  __APP_qyMc_touchscreen__
		 return  MessageBox(  hWnd ,  lpText,  lpCaption,  uType  );
		 //  return  MessageBox(  NULL,  lpText,  lpCaption,  uType  |  MB_TASKMODAL  );
#else

		DWORD		toInS		=	10;
		TCHAR		title[64]	=	_T(  ""  );
		_sntprintf(  title,  mycountof(  title  ),  _T(  "%s %d %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_after  ),  toInS,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_seconds  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_automaticallyCanceled  )  );
		int			titleLen  =  lstrlen(  title  )  *  sizeof(  TCHAR  );
		TCHAR	*	hint		=	lpText  ?  lpText  :  _T(  ""  );
		int			msgLen		=	lstrlen(  hint  )  *  sizeof(  TCHAR  );
		DWORD		iResp		=	-1;
		
		if  (  myWTSSendMessage(  g_pEnv,  0,  WTS_CURRENT_SESSION,  title,  titleLen,  hint,  msgLen,  uType  |  MB_TOPMOST,  toInS,  &iResp,  TRUE  )  )  return  iResp;
		
		return  iResp;

#endif

}

#endif

#endif



