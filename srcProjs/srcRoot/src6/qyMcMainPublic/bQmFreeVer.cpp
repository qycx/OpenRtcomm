

#include	"stdafx.h"
#include	<tchar.h>
#include	"shlobj.h"
#include	"qyMcMainCommon.h"




//
//


 //  2017/06/21
 int  qyGetSubSystemId_isCli( QY_MC  *  pQyMc )
 {
#ifdef  __isCli__

		//
		#ifdef  __DEBUG__
				#if  10
					 return  CONST_subSystemId_standard;//basic;
				#endif
		#endif

		//
		//QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
		return  pQyMc->usSubSystemId_daemon;		
#endif
		
	 return  0;
 }



 //  2016/10/15
 BOOL  bQmFreeVer(  QY_MC  *  pQyMc  )
 {
	 if  (  !pQyMc  )  return  FALSE;
	 //
	 if  (  pQyMc->ucbDaemonDemo
		 //&&  qyGetAppAvLevel_qyMc(  pQyMc  )  ==  CONST_qyAppAvLevel_mini  
		 )
	 {
		 if  (  pQyMc->ucDays_left  ==  255  )  {
			 return  TRUE;
		 }
	 }

	 //
	 return  FALSE;
 }


