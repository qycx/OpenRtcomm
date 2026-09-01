

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
//  #include	"qyMc_touchscreen.h"

#include	"qyCusResPublic.h"
#include	"qyOpenShellCommon.h"
#include	"qmOpenCommon.h"
//  #include	"qmShell_open.h"

#include	"tmpCeLib.h"

#include	"DlgWalls.h"

//  #include	"DlgMenuIsCli.h"
//#include	"myresource.h"

#include	"qyCusResTemp.h"
#include	"ctxQmc.h"

//  #include	"DlgPolicyIsClient.h"
//  #include	"DlgCfgVideoConference.h"
//  #include	"DlgMsgList.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
#include	"qmcCommFunc_isCli.h"
#include	"isCliCorePublic.h"
#include	"qmcStruct_defs.h"




//
//#define	 QY_GET_FUNCS_for_isCliHelp(  )		(  FUNCS_for_isCliHelp  *  )(  (  (  MC_VAR_isCli  *  )  QY_GET_procInfo_isCli(  )  )->pFuncs_for_isCliHelp  )
//  2016/09/02
__declspec(  dllexport  )  FUNCS_for_isCliHelp  *  QY_GET_FUNCS_for_isCliHelp(  CCtxQmc  *  pProcInfo  )	
{
	//  (  FUNCS_for_isCliHelp  *  )(  (  (  MC_VAR_isCli  *  )  QY_GET_procInfo_isCli(  )  )->pFuncs_for_isCliHelp  )
	if  (  !pProcInfo  )  return  NULL;
	return  (  FUNCS_for_isCliHelp  *  )pProcInfo->pFuncs_for_isCliHelp;
}


//
//  #define  QY_GET_shmCmds(  )		(  QM_SHM_CMDS  *  )(  (  (  MC_VAR_isCli  *  )QY_GET_procInfo_isCli(  )  )->cmdsShm.pBuf  )
//  2016/09/03
__declspec(  dllexport  )  QM_SHM_CMDS  *  QY_GET_shmCmds(  CCtxQmc  *  pProcInfo  )	
{
	if  (  !pProcInfo  )  return  NULL;

	return  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf;
}




