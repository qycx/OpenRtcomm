

#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

//#include	"qyMcMainCommon.h"
#include	"ctxQmcTmpl.h"

#include	"qyGuiCommProc.h"

#include	"subtitles.h"

#include	"qmcVideoCapture.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qmcAcm.h"
//#include	"qyAvRecordPublic.h" 
#include	"qyVk.h"
#include	"qyMcMainInternalBak.h"
#include	<assert.h>
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"

#include	"myDb.h"
#include	"qyMcMainCusModule.h"
#include	"taskAv.h"
#include	"qmcTaskInfo.h"



//  2014/11/12
TASK_AV_FROM  *  getTaskAvFrom(    QY_TRANSFORM  *  pTransform,  int  index_pMems_from,  int  index_activeMems_from,  LPCTSTR  hint  )
{
	TASK_AV_FROM  *  pFrom  =  NULL;
	PROC_TASK_AV  *  pTask  =  (  PROC_TASK_AV  *  )pTransform->pTask;
	if  (  !pTask  )  return  NULL;
	//CCtxQyMc  * pQyMc  =  g_pQyMc;
	CCtxQmc  *  pProcInfo  =  (CCtxQmc  *  )pTransform->pProcInfo;
	QMC_TASK_INFO  *  pTaskInfo  =  (QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  NULL;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  NULL;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	//
	if  (  !hint  )  hint  =  _T(  ""  );

	//
	if  (  pTransform->bMosaicVideo  )  {
		//pFrom  =  &pTask->confMosaicTrans.confMosaic_video.taskAvFrom;
		return  mynull;
		}
	else  if  (  pTransform->bMosaicResource  )  {
			  //pFrom  =  &pTask->confMosaicTrans.confMosaic_resource.taskAvFrom;
			  return mynull;
			  }
	else  {
		if  (  index_pMems_from  <  0  ||  index_pMems_from  >=  pTc->videoConference.usCntLimit_mems_from  )  {
			  #ifdef  __DEBUG__
					  traceLog((TCHAR*)  _T(  "getTaskAvFrom failed, index_pMems_from err, %s"  ),  hint  );
			  #endif
			  return  NULL;
		  }
		  //
		  if  (  index_activeMems_from  !=  pTransform->index_activeMems_from  )  {
			  #ifdef  __DEBUG__
					  traceLog((TCHAR*)  _T(  "getTaskAvFrom failed, index_activeMems_from unmatched, %s"  ),  hint  );
			  #endif
			  return  NULL;
		  }
		  //
		  if  (  pTask->ucbVideoConferenceStarter  )  {			
			  //if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTask->usCntLimit_activeMems_from  )  
			  if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  
			  {
	  			  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "getTaskAvFrom failed, index_activeMems_from err, %s"  ),  hint  );
				  #endif
				  return  NULL;
			  }
		  }
		  //
		  pFrom  =  &pTc->videoConference.pMems_from[index_pMems_from];	
	}

	return  pFrom;
}

//
TASK_AV_FROM  *  getTaskAvFrom(    PROC_TASK_AV  *  pTask,  int  index_pMems_from,  LPCTSTR  hint  )
{
	TASK_AV_FROM  *  pFrom  =  NULL;
	CCtxQyMc  *  pQyMc  =  g_pQyMc;
	CCtxQmc  *  pProcInfo  =  (CCtxQmc  *  )pQyMc->get_pProcInfo();
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  NULL;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  mynull;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	//
	if  (  !hint  )  hint  =  _T(  ""  );

	//
	{
		if  (  index_pMems_from  <  0  ||  index_pMems_from  >=  pTc->videoConference.usCntLimit_mems_from  )  {
			  #ifdef  __DEBUG__
					  traceLog((TCHAR*)  _T(  "getTaskAvFrom failed, index_pMems_from err, %s"  ),  hint  );
			  #endif
			  return  NULL;
		  }
		  //
		  pFrom  =  &pTc->videoConference.pMems_from[index_pMems_from];	
	}

	return  pFrom;
}
