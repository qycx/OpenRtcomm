
#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"

#define		NUMHOOKS		7 
 
//  Global variables 
 
typedef  struct  __MYHOOKDATA	{ 
				 int			nType; 
    			 HOOKPROC		hkprc; 
    			 HHOOK			hhook; 
}		 MYHOOKDATA; 
 
MYHOOKDATA  myhookdata[NUMHOOKS]; 

LRESULT  CALLBACK  GetMsgProc(  int  nCode,  WPARAM  wParam,  LPARAM  lParam  );

 static  unsigned  int  suiActiveTick	=	0;
 unsigned  int  getLastActiveTickCnt(  )
{
	 return  suiActiveTick;
}


 int  initQyMcMainHook(  )
{
	 int	index  =  0;

	 traceLogA(  (char*)  "启动Main的Hook"  );

	 myhookdata[index].nType = WH_GETMESSAGE; 
     myhookdata[index].hkprc = GetMsgProc; 
            
	 suiActiveTick  =  GetTickCount(  );	//  这里先初始化好

	 myhookdata[index].hhook = SetWindowsHookEx(  myhookdata[index].nType,  myhookdata[index].hkprc,  (  HINSTANCE  )NULL,  GetCurrentThreadId(  )  ); 

	 return  0;
}

 void  exitQyMcMainHook(  )
{
	 int  index  =  0;

	 traceLogA(  (char*)  "停止Main的Hook"  );

	 UnhookWindowsHookEx(  myhookdata[index].hhook  ); 

	 return;
}

 QY_DMITEM  CONST_msgTable[]  =
{
	{	WM_TIMER,		(TCHAR*)_T(  "WM_TIMER"  ),			},
	{	WM_CHAR,		(TCHAR*)_T(  "WM_CHAR"  ),			},
	{	WM_KEYDOWN,		(TCHAR*)_T(  "WM_KEYDOWN"  ),		},
	{	WM_KEYUP,		(TCHAR*)_T(  "WM_KEYUP"  ),			},
	{	WM_MOUSEMOVE,	(TCHAR*)_T(  "WM_MOUSEMOVE"  ),		},
	{	-1,				NULL,				},
};


 LRESULT  CALLBACK  GetMsgProc(  int  nCode,  WPARAM  wParam,  LPARAM  lParam  ) 
{ 
    CHAR				szMSGBuf[256]	=	""; 
    CHAR				szRem[16]		=	""; 
    CHAR				szMsg[16]		=	""; 
    static  int			c				=	0; 
    int					cch				=	0; 
	char			*	p				=	(char*)"";			
 
	// do not process message 
    if  (  nCode  <  0  )  return  CallNextHookEx(  myhookdata[0].hhook,  nCode,  wParam,  lParam  ); 
 
    switch  (  nCode  )  {
			case  HC_ACTION: 
            	  switch  (  wParam  )  {
						  case  PM_REMOVE: 
							    _snprintf(  szRem,  sizeof(  szRem  ),  "%s",  "PM_REMOVE"  );  
								break; 
 						  case  PM_NOREMOVE: 
							    _snprintf(  szRem,  sizeof(  szRem  ),  "%s",  "PM_NOREMOVE"  );
								break; 
 						  default: 
							      _snprintf(  szRem,  sizeof(  szRem  ),  "%s",  "Unknown"); 
                    			  break; 
            	  } 
 
            	  // Call an application-defined function that converts a 
            	  // message constant to a string and copies it to a 
            	  // buffer. 
 
				  //  LookUpTheMessage((PMSG) lParam, szMsg); 


				  switch  (  (  (  PMSG  )lParam  )->message  )  {
						  case  WM_CHAR:
						  case  WM_KEYDOWN:
						  case  WM_KEYUP:
						  case  WM_MOUSEMOVE:
							    suiActiveTick  =  GetTickCount(  );
								break;
						  default:
								 break;
				  }

				  /*
				  _snprintf(  szMsg,  sizeof(  szMsg  ),  "%s",  qyGetDesByType1(  CONST_msgTable,  (  (  PMSG  )lParam  )->message  )  );
 				  cch  =  wsprintf(  szMSGBuf,  "GETMESSAGE - wParam: %s, msg: %s, %d times   ",  szRem,  szMsg,  c  ++  ); 
				  traceLogA(  (char*)  "GetMsgProc: %s",  szMSGBuf  );
				  */
				  
				  break; 
 		  default: 
				  break; 
    } 
 
    return  CallNextHookEx(  myhookdata[0].hhook,  nCode,  wParam,  lParam  ); 
} 

