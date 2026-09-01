

#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"dlgtalkproc.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qmcDmoPublic.h"

#include	"wallTalkers.h"
#include	"qmcGpsProc.h"
//#include	"msAecCommon.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
#include	"amCapPublic.h"
#include	"isCliD3dPublic.h"
#include	"qyMcMainWndProc.h"
#include	"imgProcessPublic.h"





 unsigned  int	dyn_getuiNextTranNo(  void  *  p0,  long  val,  long  *  puiTranNo  )
 {
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  0;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  0;

	if  (  !pFuncs->isCliHelp.bOk  )  return  0;

	return  pFuncs->isCliHelp.pf_getuiNextTranNo(  p0,  val,  puiTranNo  );
 }



 int  dyn_dlgTalk_getTaskInfo(  void  *  pProcInfo,  HWND  hTalkerMgr,  void  *  pTALKER_task_info  )
 {

	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  (  CCtxQmc  *  )pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliHelp.bOk  )  return  -1;


	return  pFuncs->isCliHelp.pf_dlgTalk_getTaskInfo(  pProcInfo,  hTalkerMgr,  pTALKER_task_info  );
}


 //
 int  dyn_dlgTalk_getTaskList(  void  *  pProcInfoParam,  HWND  hTalkerMgr,  void  *  pTALKER_task_list,  BOOL  *  pbModified  )
 {
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliHelp.bOk  )  return  -1;


	return  pFuncs->isCliHelp.pf_dlgTalk_getTaskList(  pProcInfoParam,  hTalkerMgr,  pTALKER_task_list,  pbModified  );

 }



 //  2014/12/21
 int  dyn_getSubtitlesCfg(  int  iCapType,  int  iCapSubType,  int  iUsage,  SUBTITLES_cfg  *  pSubtitlesCfg  )
 {
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliHelp.bOk  )  return  -1;


	return  pFuncs->isCliHelp.pf_getSubtitlesCfg(  iCapType,  iCapSubType,  iUsage,  pSubtitlesCfg  );

 }


int  dyn_subtitlesCfg_modify(  SUBTITLES_cfg  *  pCfg,  DWORD  dwTickCnt,  BOOL  bForce,  SUBTITLES_cfg  *  pCur,  BOOL  *  pbModified  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliHelp.bOk  )  return  -1;


	return  pFuncs->isCliHelp.pf_subtitlesCfg_modify(  pCfg,  dwTickCnt,  bForce,  pCur,  pbModified  );
}

int  dyn_getSubtitlesCfg_d3dWall(  int  iCapType,  int  iCapSubType,  int  iUsage,  SUBTITLES_cfg  *  pSubtitlesCfg  )   
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliHelp.bOk  )  return  -1;

	return  pFuncs->isCliHelp.pf_getSubtitlesCfg_d3dWall(  iCapType,  iCapSubType,  iUsage,  pSubtitlesCfg  );
}
