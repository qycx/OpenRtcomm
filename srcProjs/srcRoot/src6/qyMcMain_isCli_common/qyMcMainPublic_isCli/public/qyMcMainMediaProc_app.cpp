

#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#include	"qmcCmdProc.h"

//  #include	"qySqlFunc.h"
//#include	"qyAvRecordPublic.h"
//#include	"imgProcessPublic.h"
//#include	"isCliHelpPublic.h"

//#include	"qmcCommFunc_isCli.h"

#include	"vppProc.h"
#include	"qmcCfg.h"


//


//




//
 




 //  2011/07/15, 每次读取若干包然后一次性压缩
 DWORD WINAPI mcThreadProc_app( LPVOID lpParameter )
{
	 int							iIndex_sharedObj			=	(  int  )lpParameter;

	 QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();
	 if  (  !pQyMc  )  {
		 return  -1;
	 }
	 MC_VAR_common				*	pProcInfo					=	(MC_VAR_common*)pQyMc->get_pProcInfo(  );
	 if (  !pProcInfo  )  return  -1;
	 QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	 if  (  !pQmcCfg  )  return  -1;

	 QY_SHARED_OBJ				*	pSharedObj					=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	 if  (  !pSharedObj  )  return  -1;


	 return  0;

}
