
#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

//  #include	"qyFile.h"

#include	"myresource.h"

#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"

#include	"qyCusResTemp.h"

#include	"isCliHelpPublic.h"


   __declspec(  dllexport  )  unsigned  int  get_uiMaxQNodes_vwRuleQ(  )
{
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	
	//  2014/07/27
	if  (  pQyMc->ucbDaemonDemo  )  {
		return  min(  pProcInfo->cfg.policy.uiMaxQNodes_vwRuleQ,  10  );
	}

	//
	return  pProcInfo->cfg.policy.uiMaxQNodes_vwRuleQ;
}


