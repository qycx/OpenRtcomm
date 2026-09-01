
#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
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

#include	"qmcVideoCapture_rtsp.h"

#include	"isCliHelpPublic.h"
//#include	"rtspCliHelpPublic.h"
#include	"qmcTaskInfo.h"
#include	"funcsForIsCliHelp.h"
#include	"dlgtalkproc.h"





//
//
int  syncToGetTaskInfo(  DLG_TALK_var  *  pm_var,  CQySyncCnt  &  syncCnt,  PARAM_task_info  &  param  )
{
	int  iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	if  (  !pm_var  )  return  -1;
	DLG_TALK_var  &  m_var  =  *pm_var;


	//  先要判断uiTranNo是否一致。，然后把取到的dynBmp赋到taskInfo的confWallMem里去。然后，再发起viewDynBmp
	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
	if  (  !m_var.av.taskInfo.bTaskExists  )  return  -1;

	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )pProcInfo->getQmcTaskInfoByIndex(  m_var.av.taskInfo.iIndex_taskInfo  );
	if  (  !pTaskInfo  )  goto  errLabel;
	if  (  !pTaskInfo->bUsed  )  goto  errLabel;

	//
	//if  (  syncMtCnt_rLock(  &pTaskInfo->syncMtCnt,  &syncCnt,  _T(  "syncToGetTaskInfo"  )  )  )  goto  errLabel;  

	//
	if  (  pTaskInfo->var.iTaskId  !=  m_var.av.taskInfo.iTaskId  )  {
		showInfo_open0(  0,  0,  _T(  "Error: taskInfo.taskId != av.iTaskId"  )  );
		goto  errLabel;
	}
	
	QMC_taskData_conf* pTaskData; pTaskData = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
	if  (  !pTaskData  )  goto  errLabel;

	if  (  pTaskData->common.uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;

	//if  (  !pTaskData->bInited  )  goto  errLabel;

	memset(  &param,  0,  sizeof(  param  )  );
	param.pTaskInfo  =  pTaskInfo;
	param.pTaskData  =  pTaskData;

	iErr  =  0;
errLabel:
	return  iErr;
}


