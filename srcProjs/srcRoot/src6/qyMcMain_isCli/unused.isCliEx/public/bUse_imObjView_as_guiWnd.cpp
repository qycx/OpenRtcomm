

#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>
#include	<WinSock2.h>
//
#include	"qyCommon.h"




 //
extern  "C"  __declspec(  dllexport  )  BOOL  bUse_imObjView_as_guiWnd(  )
{
#ifdef  __DEBUG__
		#if  0
			 return  FALSE;	//  TRUE;
		#endif
#endif
#if  10
			 return  TRUE;
#endif

	 return  FALSE;

 }



 //  2017/06/06
extern  "C"  __declspec(  dllexport  )   BOOL  bSupport_ts(  )
 {
#if  1
	 return  TRUE;
#endif

	 //
	 return  FALSE;
 }
