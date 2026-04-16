// qyVDevApi.cpp : Defines the entry point for the DLL application.
//

#include	"stdafx.h"
#include	<tchar.h>
#include	<vfw.h>

//
#include	"qyCommon.h"
#include	"qyLangCommProc.h"
#include	"qyTCharCommProc.h"
//
#include	"qyCusResPublic.h"
#include	"qyCusResTemp.h"
//
#include	"qyCusGui.h"
//
#include	"qySyncCommProc.h"
#include	"genericQueue.h"

#include	"qyCommCommon.h"
#include	"qyWmComm.h"

#include	"qyCommProc.h"
#include	"qyVDevCommProc_open.h"
#include	"qyCommProc_open.h"
#include	"qyCusGui.h"


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}



 extern  "C"  __declspec( dllexport )  int  qvdSendSm(  void  *  p0,  WCHAR  *  sm,  char  *  phoneNo,  HWND  hWnd_notify,  int  iUsrData  )
{
	 int			iErr	=	-1;
	 HWND			hWnd	=	NULL;
	 QVD_SM_REQ		smReq;

	 if  (  !sm  ||  !sm[0]  ||  !phoneNo  ||  !phoneNo[0]  )  return  -1;

	 memset(  &smReq,  0,  sizeof(  smReq  )  );
	 lstrcpyn(  smReq.sm,  sm,  mycountof(  smReq.sm  )  );
	 strncpy(  smReq.phoneNo,  phoneNo,  mycountof(  smReq.phoneNo  )  );
	 smReq.hWnd_notify  =  hWnd_notify;
	 smReq.iUsrData  =  iUsrData;
	 
	 hWnd  =  FindWindow(  DEFAULT_qyMcInputWndCls,  NULL  );
	 if  (  !hWnd  )  goto  errLabel;
	 				  
	 COPYDATASTRUCT		tmpCopyData;

	 tmpCopyData.lpData  =  &smReq;	
	 tmpCopyData.cbData  =  sizeof(  smReq  );
	 SendMessage( hWnd,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			

	 iErr  =  0;
errLabel:
	 return  iErr;
}
