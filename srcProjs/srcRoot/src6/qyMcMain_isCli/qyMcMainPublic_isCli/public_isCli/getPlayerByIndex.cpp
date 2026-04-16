

#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>


#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//  #include	"qmcVideoCapture_isCli.h"
//#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

//#include	"isCliHelpPublic.h"
//#include	"dlgShareDynBmpsProc.h"
//#include	"isClid3dpublic.h"
#include	"qmcTaskPublic.h"

#include	"qmcCommFunc_isCli.h"
#include	"qmcCfg.h"

#include	"qmcVideoCapture_isCli.h"



//

 __declspec(  dllexport  )  QY_PLAYER  *  getPlayerByIndex(  MC_VAR_isCli  *  pProcInfo,  int  index  )
{
	if  (  index  <  0  ||  index  >=  pProcInfo->av.usCnt_players  )  return  NULL;
	//  if  (  !index  )  return  &pProcInfo->av.localAv.player;	//  2009/06/02
	return  &pProcInfo->av.pPlayers[index];
}
