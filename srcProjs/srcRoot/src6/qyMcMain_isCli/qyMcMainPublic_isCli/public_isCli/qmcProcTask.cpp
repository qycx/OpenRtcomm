
#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcAcm.h"
#include	"qyVk.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"
#include	"qmcCommFunc_isCli.h"
#include	"qmcTaskInfo.h"


//
__declspec(  dllexport  )  TASK_respInfo  *  get_respInfo(  void   *  pProcInfoParam,  int  index_taskInfo  )
{
	int  iErr  =  -1;
	//
	MC_VAR_isCli   *  pProcInfo  =  (  MC_VAR_isCli  *  )pProcInfoParam;
	//
	TASK_respInfo *  pRespInfo  =  NULL;

	//int  iIndex_sharedObj  =  pTask->iIndex_sharedObj;
	//int  iIndex_sharedObjUsr  =  pTask->iIndex_sharedObjUsr;

	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  index_taskInfo  );
	if  (  !pTaskInfo  )  return  NULL;

	//
	pRespInfo  =  &pTaskInfo->var.taskRespInfo;

	//
	iErr  =  0;

errLabel:
	return  iErr  ?  NULL  :  pRespInfo;

}



//
TASK_respInfo_mem  *  get_respInfoMem(  MC_VAR_isCli  *  pProcInfo,  TASK_respInfo  *  pRespInfo,  QY_MESSENGER_ID  *  pIdInfo_from,  unsigned  int  uiTaskType  )
{
	int  iErr  =  -1;
	TASK_respInfo_mem   *  pMem  =  NULL;
	int  i;

			  //
		  unsigned  short  tmp_usCnt  =  pRespInfo->usCnt;
		  if  (  tmp_usCnt  >  mycountof(  pRespInfo->mems  )  )  tmp_usCnt  =  mycountof(  pRespInfo->mems  );
		  //
		  if  (  uiTaskType  ==  CONST_imTaskType_transferAvInfo  )  {
			  //
			  QY_MESSENGER_ID  idInfo;
			  idInfo.ui64Id  =  pIdInfo_from->ui64Id;
			  pMem  =  (  TASK_respInfo_mem  *  )bsearch(  &idInfo,  pRespInfo->mems,  tmp_usCnt,  sizeof(  TASK_respInfo_mem  ),  bCmp_respInfoMem  ); 
			  if  (  !pMem  )  {
				  goto  errLabel;
			  }


			  }
		  else  {
				//		
			    for  (  i  =  0;  i  <  tmp_usCnt;  i  ++  )  {			   
					 if  (  pRespInfo->mems[i].idInfo.ui64Id  ==  pIdInfo_from->ui64Id  )  break;		  
				}		  
				if  (  i  ==  tmp_usCnt  )  {
								  
					//  			  
					for  (  ;  i  <  mycountof(  pRespInfo->mems  );  i  ++  )  {				   
						 if  (  !pRespInfo->mems[i].idInfo.ui64Id  )  break;			  
					}			  
					if  (  i  ==  mycountof(  pRespInfo->mems  )  )  {				  
						qyShowInfo1(  CONST_qyShowType_debug,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoDataResp: mems_to[] is full. skipped."  )  );  
						goto  errLabel;
					}
					pRespInfo->mems[i].idInfo.ui64Id  =  pIdInfo_from->ui64Id;
		
					pRespInfo->usCnt  =  tmp_usCnt  +  1;
				}
				//		  
				pMem  =  &pRespInfo->mems[i];
		  }


		  iErr  =  0;
errLabel:

		  return  iErr  ?  NULL  :  pMem;

}


//
//
__declspec(  dllexport  )  int __cdecl bCmp_respInfoMem(const void *key, const void *pMem)
{
	QY_MESSENGER_ID  *  pIdInfo  =  (  QY_MESSENGER_ID  *  )key;
	TASK_respInfo_mem  *  pRespInfoMem  =  (  TASK_respInfo_mem  *  )pMem;

	__int64  iDiff  =  0;

	iDiff  =  pIdInfo->ui64Id  -  pRespInfoMem->idInfo.ui64Id;

	if  (  iDiff  <  0  )  return   -1;
	if  (  !iDiff  )  return  0;
	return  1;
}


//
#define		MAX_resp_elapseInS		61

//
__declspec(  dllexport  )  int  get_respInfoMem_state(  MIS_CNT  *  pMisCnt,  time_t  tNow,  TASK_respInfo_mem  *  pMem,  time_t  *  pTime_state  )
{
	int  iErr  =  -1;
	int  iState  =  0;
	time_t  tTime_state  =  0;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	int  iElapseInS  =  0;

	//
	if  (  !pMisCnt  )  return  -1;

	//
	if  (  pMem->idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
		if  (  bMeOnline(   pQyMc  )  )  {
			iState  =  CONST_taskRespInfoMemState_ok;
			tTime_state  =  tNow;
			}
		else  {
			  iState  =  CONST_taskRespInfoMemState_offline;			
			  tTime_state  =  tNow;
		}

		iErr  =  0;  goto  errLabel;
	}

	//
	time_t  last_t;
	
	//
	if  (  pMem->var.taskProcReq_cancel.tRecvTime_lastResp  +  9  >=  pMem->var.video.tRecvTime_lastResp
		&&  pMem->var.taskProcReq_cancel.tRecvTime_lastResp  >=  pMem->var.avReply.tRecvTime_lastResp  )
	{
		iState  =  CONST_taskRespInfoMemState_leave;
		tTime_state  =  pMem->var.taskProcReq_cancel.tRecvTime_lastResp;

		iErr  =  0;  goto  errLabel;
	}

	//
	last_t  =  pMem->var.avReply.tRecvTime_lastResp;
	if  (  last_t  >  pMem->var.video.tRecvTime_lastResp  )  {
		iElapseInS  =  tNow  -  last_t;
		if  (  abs(  iElapseInS  )  <  MAX_resp_elapseInS  )  {
			iState  =  CONST_taskRespInfoMemState_join;
			tTime_state  =  pMem->var.avReply.tRecvTime_lastResp;
			}
		else  {
			  iState  =  CONST_taskRespInfoMemState_notInConf;		
			  tTime_state  =  tNow;
		}

		iErr  =  0;  goto  errLabel;
	}

	//
	if  (  pMem->var.video.lastErr.tRecvTime_lastResp  >=  pMem->var.video.tRecvTime_lastResp  )  {
		iElapseInS  =  tNow  -  pMem->var.video.lastErr.tRecvTime_lastResp;			
		//	
		if  (  abs(  iElapseInS  )  <  MAX_resp_elapseInS  )  {			
			iState  =  CONST_taskRespInfoMemState_warning;
			tTime_state  =  tNow;
			
			iErr  =  0;  goto  errLabel;
		}
	}

	//	
	iElapseInS  =  tNow  -  pMem->var.video.tRecvTime_lastResp;
	if  (  abs(  iElapseInS  )  <  MAX_resp_elapseInS  )  {
		iState  =  CONST_taskRespInfoMemState_ok;
		tTime_state  =  tNow;
	    }		
	else  {
		  iState  =  CONST_taskRespInfoMemState_notInConf;		
		  tTime_state  =  tNow;
	}			 
	
	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
		if  (  pTime_state  )  *pTime_state  =  tTime_state;
	}

	return  iErr  ?  -1  :  iState;
}




//
__declspec(  dllexport  )  int  procTaskAvReply(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr_logicalPeer,  int  iTaskId,  AV_TRAN_INFO  *  pAvTran,  PROC_TASK_AV  *  pTask,  MIS_MSG_TASK  *  pMsgTask  )
 {
	 int				iErr			=	-1;
	 int				index			=	0;
	 IM_CONTENTU	*	pContent		=	(  IM_CONTENTU  *  )pMsgTask->data.buf;
	 //
	 MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMsgTask->pMisCnt;
	 if  (  !pMisCnt  )  {
		 return  -1;
	 }
	 //CCtxQyMc  *  pQyMc  =  g_pQyMc;
	 QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	 if  (  !pTaskInfo  )  return  -1;
	 if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	 QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;


	 //  2015/02/16
#ifdef  __DEBUG__
		#if  0 
			traceLog(  _T(  "TEST: procTaskAvReply is not valid now"  )  );
			showInfo_open0(  0,  0,  _T(  "TEST: procTaskAvReply is not valid now"  )  );
			return  -1;
		#endif
#endif


	 //
	 if  (  pContent->uiType  !=  CONST_imCommType_transferAvReplyInfo  )  return  -1;
	 //
	 if  (  pContent->transferAvReplyInfo.tranInfo.audio.uiTranNo_openAvDev  &&  pAvTran->audio.uiTranNo_openAvDev  )  {
	       
	 }

	 //
	 pMsgTask->addr_logicalPeer.idInfo.ui64Id  =  pAddr_logicalPeer->idInfo.ui64Id;													 
	
	 //
	 if  (  !pTask->ucbVideoConference  )  {
		 int  i;
		 for  (  i  =  0;  i  <  pTc->videoConference.usCntLimit_activeMems_from;  i  ++  )  {
			 if  (  pTc->videoConference.activeMems_from[i].avStream.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id
				 &&  pTc->videoConference.activeMems_from[i].avStream.obj.resObj.uiObjType  ==  0  )  
			 {
				 break;
			 }
		 }
		 if  (  i  <  pTc->videoConference.usCntLimit_activeMems_from  )  {
			 DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[i];
			 if  (  pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev  ==  pContent->transferAvReplyInfo.tranInfo.audio.uiTranNo_openAvDev
				 &&  pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev  ==  pContent->transferAvReplyInfo.tranInfo.video.uiTranNo_openAvDev  )  
			 {

				#ifdef  __DEBUG__
					 traceLogA(  "findOrgMsgAndProcess_mis ."  );
				#endif
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "procTaskAvReply"  ),  _T(  ""  ),  _T(  " %I64u, mem_from'av matched, OK"  ),  pMsgTask->data.route.idInfo_from.ui64Id  );

				iErr  =  0;  goto  errLabel;
			 }		 
			 //
			 pActiveMem_from->avStream.obj.tranInfo  =  pContent->transferAvReplyInfo.tranInfo;
			 //
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "procTaskAvReply"  ),  _T(  ""  ),  _T(  " %I64u, OK"  ),  pMsgTask->data.route.idInfo_from.ui64Id  );
			 iErr  =  0;  goto errLabel;

		 }
		 for  (  i  =  0;  i  <  pTc->videoConference.usCntLimit_activeMems_from;  i  ++  )  {
			  if  (  !pTc->videoConference.activeMems_from[i].avStream.idInfo.ui64Id  )  break;
		 }
		 if  (  i  ==  pTc->videoConference.usCntLimit_activeMems_from  )  {

			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "procTaskAvReply"  ),  _T(  ""  ),  _T(  " %I64u, no free index in mems_from, failed."  ),  pMsgTask->data.route.idInfo_from.ui64Id  );

			 iErr  =  0;  goto  errLabel;
		 }
		
		 DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[i];
		 pActiveMem_from->avStream.idInfo  =  pMsgTask->data.route.idInfo_from;
		 pActiveMem_from->avStream.obj.tranInfo  =  pContent->transferAvReplyInfo.tranInfo;
		 //
		 M_getActiveMemDesc(  pMisCnt,  &pActiveMem_from->avStream.idInfo,  pActiveMem_from->desc,  mycountof(  pActiveMem_from->desc  )  );
		 //		
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "procTaskAvReply"  ),  _T(  ""  ),  _T(  " %I64u, OK"  ),  pMsgTask->data.route.idInfo_from.ui64Id  );
		
		 iErr  =  0;  goto  errLabel;
	 }

	 //
	 //
	 //pTaskInfo->var.curRoute_sendLocalAv.
	 if (pTask->ucbVideoConferenceStarter) {
		 if (addToMsgrs_sendLocalAv(pProcInfo, pMisCnt, &pMsgTask->data.route.idInfo_from, true, &pTaskInfo->var.curRoute_sendLocalAv, true,  _T(  "procTaskAvReply.306"  ))) {
			 showInfo_open0(0, 0, _T("procTaskAvReply: addToMsgrs_sendLocalAv, bConfAv true, failed"));
		 }
	 }



	 //  2015/02/17
	 BOOL  bNewFrom  =  FALSE;

	 //
	 for  (  index  =  0;  index  <  pTc->videoConference.usCntLimit_mems_from;  index  ++  )  {											
		  if  (  pTc->videoConference.pMems_from[index].idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id  )  break;						
	 }
	 if  (  index  <  pTc->videoConference.usCntLimit_mems_from  )  {	//  ÒÑ¾­ÓÐÁË							
		 if  (  pTc->videoConference.pMems_from[index].video.tv_recvd.uiTranNo_openAvDev  ==  pContent->transferAvReplyInfo.tranInfo.video.uiTranNo_openAvDev  					
			 &&  pTc->videoConference.pMems_from[index].audio.ta_recvd.uiTranNo_openAvDev  ==  pContent->transferAvReplyInfo.tranInfo.audio.uiTranNo_openAvDev  )						
		 {
			 #ifdef  __DEBUG__
					 traceLogA(  "findOrgMsgAndProcess_mis ."  );
			 #endif
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "procTaskAvReply"  ),  _T(  ""  ),  _T(  " %I64u, mem_from'av matched, OK"  ),  pMsgTask->data.route.idInfo_from.ui64Id  );

			 iErr  =  0;  goto  errLabel;
		 }

		 //
		 //  stopTransformThreads(  pTask  );
		 //  
		 //  exitTaskAvFrom_video(  pProcInfo,  &pTask->pMems_from[index]  );
		 //  exitTaskAvFrom_audio(  pProcInfo,  &pTask->pMems_from[index]  );
		 
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "procTaskAvReply"  ),  _T(  ""  ),  _T(  " %I64u, mem_from'av not matched, will fix it"  ),  pMsgTask->data.route.idInfo_from.ui64Id  );
		 }
	 else  {
		   //  ÏÂÃæÕÒ¸ö¿ÕµÄÎ»ÖÃ
		   for  (  index  =  0;  index  <  pTc->videoConference.usCntLimit_mems_from;  index  ++  )  {																						
			    if  (  !pTc->videoConference.pMems_from[index].idInfo.ui64Id  )  break;																
		   }
		   if  (  index  ==  pTc->videoConference.usCntLimit_mems_from  )  {									
			   #ifdef  __DEBUG__
					   traceLogA(  "myTask"  );  															  
			   #endif
			   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "procTaskAvReply"  ),  _T(  ""  ),  _T(  " %I64u, no free index in mems_from, failed."  ),  pMsgTask->data.route.idInfo_from.ui64Id  );

			   iErr  =  0;	goto  errLabel;
		   }

		   //  2015/02/18
		   bNewFrom  =  TRUE;
	 }

	 //  2011/07/03
	 //  stopTransformThreads(  pTask  );

	 //  2014/11/12
	 TASK_AV_FROM  *  pFrom  =  &pTc->videoConference.pMems_from[index];

	 {
		 CQySyncObj	syncObj;	
		 TCHAR	mutexName[128];
		 //  2011/07/03
		 //  _sntprintf(  mutexName,  mycountof(  mutexName  ),  _T(  "%s%d"  ),  pProcInfo->cfg.mutexName_syncActiveMem_prefix,  iTaskId  );
		 M_getMutexName_syncActiveMem(  &pProcInfo->cfg,  iTaskId,  mutexName,  mycountof(  mutexName  )  );
		 unsigned  int  uiMilliSeconds  =  1000;
		 //  2015/02/17. 这是个快速处理的函数，不能允许等待
		 uiMilliSeconds  =  0;
		 //
		 if  (  syncObj.sync(  mutexName,  uiMilliSeconds   )  )  {
			 showInfo_open0(  0,  0,  _T(  "procTaskAvReply failed, sync failed"  )  );
			 goto  errLabel;
		 }

		 //  2015/02/18
		 if  (  bNewFrom  )  {
			 if  (  pFrom->idInfo.ui64Id  )  {
				 showInfo_open0(  0,  0,  _T(  "procTaskAvReply failed, from is not a new one"  )  );
				 goto  errLabel;
			 }
		 }

		 //
		 pFrom->idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;			
		 pFrom->tStartTime_task  =  pMsgTask->tStartTime;					//  Æô¶¯Ê±¼ä
		 //
		 pFrom->video.tv_recvd.uiTranNo_openAvDev  =  pContent->transferAvReplyInfo.tranInfo.video.uiTranNo_openAvDev;							//  ½ÓÊÕÊý¾ÝÊ±ÒªÓÃ
		 //
#if  0	//  2014/11/07
		 pFrom->video.usCapDriverIndex  =  0;  //  2014/11/07. pContent->transferAvReplyInfo.tranInfo.video.usCapDriverIndex;
#endif
													 
		 //  safeStrnCpy(  pContent->transferAvReplyInfo.tranInfo.video.fourccStr,  pTransferAvInfoElem->myTask.pMems_from[index].video.fourccStr,  mycountof(  pTransferAvInfoElem->myTask.pMems_from[index].video.fourccStr  )  );
		 memcpy(  &pFrom->video.tv_recvd.compressor,  &pContent->transferAvReplyInfo.tranInfo.video.compressor,  sizeof(  pFrom->video.tv_recvd.compressor  )  );
													 
		 memcpy(  &pFrom->video.tv_recvd.vh_compress,  &pContent->transferAvReplyInfo.tranInfo.video.vh_compress,  sizeof(  pFrom->video.tv_recvd.vh_compress  )  );
		 //  2014/03/31
		 memcpy(  &pFrom->video.tv_recvd.vh_stream,  &pContent->transferAvReplyInfo.tranInfo.video.vh_stream,  sizeof(  pFrom->video.tv_recvd.vh_stream  )  );
		 //
		 if  (  bSupported_sendVhDec(  )  )  {
			 memcpy(  &pFrom->video.tv_recvd.vh_decompress,  &pContent->transferAvReplyInfo.tranInfo.video.vh_decompress,  sizeof(  pFrom->video.tv_recvd.vh_decompress  )  );
		 }
		 //
		 pFrom->audio.ta_recvd.uiTranNo_openAvDev  =  pContent->transferAvReplyInfo.tranInfo.audio.uiTranNo_openAvDev;
		 //
		 memcpy(  &pFrom->audio.ta_recvd.compressor,  &pContent->transferAvReplyInfo.tranInfo.audio.compressor,  sizeof(  pFrom->audio.ta_recvd.compressor  )  );
		 memcpy(  &pFrom->audio.ta_recvd.ah_compress,  &pContent->transferAvReplyInfo.tranInfo.audio.ah_compress,  sizeof(  pFrom->audio.ta_recvd.ah_compress  )  );
		 memcpy(  &pFrom->audio.ta_recvd.ah_decompress,  &pContent->transferAvReplyInfo.tranInfo.audio.ah_decompress,  sizeof(  pFrom->audio.ta_recvd.ah_decompress  )  );							

		 //  2014/09/04
		 //pFrom->video.dynBmp.usIndex_obj  =  pContent->transferAvReplyInfo.dynBmp.usIndex_obj;
		 pFrom->viewDynBmp_reply.ucbSaveVideo_reply  =  pContent->transferAvReplyInfo.viewDynBmpReply.ucbSaveVideo;

		 //  2015/10/23
		 pFrom->taskAvProps  =  pContent->transferAvReplyInfo.tranInfo.taskAvProps;
	 }
	 //
	 /*
	 if  (  initTaskAvFrom(  pProcInfo,  &pTransferAvInfoElem->myTask.pMems_from[index]  )  )  {
		 traceLogA(  "tmpHandler_findOrgMsgAndProc_is: initTaskAvFrom failed"  );
	 }
	 */

	 //  2009/02/22
	 pTc->videoConference.uiTranNo_lastModified_pMems_from  =  getuiNextTranNo(  0,  0,  0  );

	 //
	 TCHAR  tBuf[128];
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  " %I64u, index_pMems_from %d, avReply OK."  ),  pMsgTask->data.route.idInfo_from.ui64Id,  index  );
	 if  (  pFrom->viewDynBmp_reply.ucbSaveVideo_reply  )  {
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s save"  ),  tBuf  );
	 }
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "procTaskAvReply:"  ),  _T(  ""  ),  _T(  " %s"  ),  tBuf  );

	 //  2012/04/01
	 int  i;
	 for  (  i  =  0;  i  <  pTc->videoConference.usCntLimit_activeMems_from;  i  ++  )  {
		 if  (  pTc->videoConference.activeMems_from[i].avStream.idInfo.ui64Id  ==  pFrom->idInfo.ui64Id  )  {		//  当已经申请发言的人中途退出又进入时,需要重新刷新话筒参数
			  PostMessage(  pTask->hWnd_task,  CONST_qyWm_postComm,  CONST_qyWmParam_bNeedRefresh_activeMems_from,  iTaskId  );		 
		  }
	 }

	 //  2010/07/19
	 int  iStatus  =  pContent->transferAvReplyInfo.tranInfo.audio.ah_compress.wfx.wFormatTag  ?  CONST_imTaskStatus_dualByReceiver  :  CONST_imTaskStatus_acceptedByReceiver;
	 showTaskStatus(  pMsgTask->pMisCnt,  &pAddr_logicalPeer->idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  pTask->ucbVideoConference,  CONST_imCommType_transferAvInfo,  iTaskId,  iStatus,  0,  0,  0,  0  );


	 //
	 OutputDebugString(  _T(  "procTaskAvReply ok\n"  )  );

	 //
	 iErr  =  0;  

errLabel:

	 if  (  !iErr  )  {
		 //  2011/07/03

		 //  2017/09/10
		 TASK_respInfo  *  pRespInfo  =  get_respInfo(  pProcInfo,  pTask->iIndex_taskInfo  );
		 if  (  pRespInfo  )  {
			 TASK_respInfo_mem  *  pRespInfoMem  =  get_respInfoMem(  pProcInfo,  pRespInfo,  &pMsgTask->data.route.idInfo_from,  pTask->uiTaskType  );
			 if  (  pRespInfoMem  )  {
				 pRespInfoMem->var.avReply.tRecvTime_lastResp  =  pMsgTask->tRecvTime;
				 //
				 time_t  tNow;  time(  &tNow  );
				 unsigned  short   usState  =  get_respInfoMem_state(  pMisCnt,  tNow,  pRespInfoMem,  NULL  );
				 //
				 if  (  pRespInfoMem->var.usState_byDlgTalk  !=  usState  )  {
					pRespInfoMem->var.bNeedCalc_byProcTaskDataResp  =  TRUE;
					pRespInfo->bNeedCalc_byProcTaskDataResp  =  TRUE;
				 }
				#if  0
				 time_t  t;  time(&t  );
				 int  iDiff  =  t  -  pMsgTask->tRecvTime;
				 int  ii  =  0;
				#endif
			 }
		 }
	 }

	 //  注意：procTaskAvReply()这里的处理应该移到主界面线程去处理。
	 pProcInfo->AEC_layout_chk(&pProcInfo->av.aecInfo.aecLayout);

	 //
	 return  iErr;
}


//

__declspec(  dllexport  )  int  tmp_procTask_recv_cancel(  MC_VAR_isCli  *  pProcInfo,  PROC_TASK_AV  *  pTask,  MIS_MSG_INPUT  *  pMsgInput,  TASK_PROC_REQ  *  pTaskProcReq  )
{
	int  iErr  =  -1;
	MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMsgInput->pMisCnt;
	if  (  !pMisCnt  )  return  -1;


	TASK_respInfo  *  pRespInfo  =  get_respInfo(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pRespInfo  )  return  -1;
	//  
	TASK_respInfo_mem			*	pRespInfoMem										=		NULL;

	pRespInfoMem  =  get_respInfoMem(  pProcInfo,  pRespInfo,  &pMsgInput->data.route.idInfo_from,  pTask->uiTaskType  );
	if  (  !pRespInfoMem   )  return  -1;

	pRespInfoMem->var.taskProcReq_cancel.tRecvTime_lastResp  =  pMsgInput->tRecvTime;
				 //
				 time_t  tNow;  time(  &tNow  );
				 unsigned  short  usState  =  get_respInfoMem_state(  pMisCnt,  tNow,  pRespInfoMem,  NULL  );
				 //
				 if  (  pRespInfoMem->var.usState_byDlgTalk  !=  usState  )  {
					pRespInfoMem->var.bNeedCalc_byProcTaskDataResp  =  TRUE;
					pRespInfo->bNeedCalc_byProcTaskDataResp  =  TRUE;
				 }


	iErr  =  0;
	return  iErr;  
}



//
__declspec(  dllexport  )  int  procTaskVideoDataResp(  MC_VAR_isCli  *  pProcInfo,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask,  MIS_MSG_INPUT  *  pMsgInput,  TRANSFER_VIDEO_dataResp  *  pResp  )
{															 
	int						iErr									=		-1;
	char					timeBuf[32]								=		"";
	TCHAR					tHintBuf[255  +  1]						=		_T(  "VideoDataResp: "  );
	unsigned  short			usFrames_perSecond_cli					=		pResp->usFps;
	//
	unsigned  char			ucTimeoutInS_showFrameInfoResp			=		0;
	unsigned  short			usFrames_perSecond_expected				=		0;
	time_t					tSelectTime								=		0;
	unsigned  int			uiCnt_pkts_fromSelect					=		0;
	int						i;
	//
	MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMsgInput->pMisCnt;
	if  (  !pMisCnt  )  {
		return  -1;
	}

	//
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	MIS_MSG_TASK  *  pMsgTask  =  &pTaskInfo->var.pTaskData->msgU.task;
	if  (  pMsgTask->uiType  !=  CONST_misMsgType_task  )  return  -1;

	

	//
	TASK_respInfo  *  pRespInfo  =  &pTaskInfo->var.taskRespInfo;//  get_respInfo(  pProcInfo,  pTask->iIndex_sharedObj,  pTask->iIndex_sharedObjUsr  );
	if  (  !pRespInfo  )  return  -1;
	//  
	TASK_respInfo_mem			*	pMem										=		NULL;

	//  
#if  0
	{
		ucTimeoutInS_showFrameInfoResp			=		pCompressVideo->ucTimeoutInS_showFrameInfoResp;
		usFrames_perSecond_expected				=		pCompressVideo->usFrames_perSecond_expected;
		tSelectTime								=		pCompressVideo->tSelectTime;
		uiCnt_pkts_fromSelect					=		pCompressVideo->uiCnt_pkts_fromSelect;
	}
#endif

	getTimelStr(  pMsgInput->tStartTime,  timeBuf,  mycountof(  timeBuf  )  );

	//	
	if  (  pMsgInput->tRecvTime  <  pMsgInput->tStartTime  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoDataResp: error: recvTime < startTime [%s], skipped"  ),  CQyString(  timeBuf  )  );
		iErr  =  0;  goto  errLabel;
	}


	//		
	_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "talker%I64u: VideoDataResp: %I64u, time-consuming %ds, fps %d/s, recvd pkts %d, diff %d. "  ),  pMsgTask->addr_logicalPeer.idInfo.ui64Id,  pMsgInput->data.route.idInfo_from.ui64Id,  (  int  )(  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  ),  (  long  )pResp->usFps,  (  long  )pResp->usCnt_pkts,  (  long  )pResp->usDiff_pkts    );
				
		  //
		  pMem  =  get_respInfoMem(  pProcInfo,  pRespInfo,  &pMsgInput->data.route.idInfo_from,  pTask->uiTaskType  );
		  //
		  if  (  !pMem  )  {
			  TCHAR  tBuf[128];
			  //
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "talker%I64u: VideoDataResp failed: pMem is null. skipped"  ),  pMsgTask->addr_logicalPeer.idInfo.ui64Id  );
			  showInfo_open0(  0,  0,  tBuf  );
			  //
			  iErr =  0;  goto  errLabel;
		  }

		  //	
		  if  (  pMem->var.video.tSelectTime  !=  tSelectTime  )  {
			  //qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoDataResp: selectTime changed"  ),  pCompressVideo->usFrames_perSecond_expected  );
		  }

		  //
		  pMem->var.video.tSelectTime  =  tSelectTime;
		  pMem->var.video.uiCnt_pkts_fromSelect  =  pResp->usCnt_pkts;

				//  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "VideoDataResp: %I64u, time-consuming %ds, fps %d/s, recvd pkts %d, diff %d. "  ),  pMsgInput->data.route.idInfo_from.ui64Id,  (  int  )(  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  ),  (  long  )pResp->usFrames_perSecond,  (  long  )pResp->usCnt_pkts,  (  long  )pResp->usDiff_pkts    );
		
#if  0
				if  (  !isRcOk(  pMsgInput->usCode  )  )  {
					pCompressVideo->usTimes_failure  ++  ;
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoDataResp: rc %d not ok, startTime [%s], error"  ),  pMsgInput->usCode,  CQyString(  timeBuf  )  );
					}
				else  if  (  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  >  ucTimeoutInS_showFrameInfoResp  )  {	//  
					      pCompressVideo->usTimes_failure  ++  ;
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoDataResp: time-consuming %d > ucTimeoutInS %d, error"  ),  (  int  )(  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  ),  (  int  )ucTimeoutInS_showFrameInfoResp  );
						  }
				else  if  (  pResp->usDiff_pkts  >  pMem->var.video.iDiff_pkts_fromSelect  )  {
						  pCompressVideo->usTimes_failure  ++  ;
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoDataResp: diff increases, startTime %s, error"  ),  CQyString(  timeBuf  )  );
		 				  }
				else  {
					  pCompressVideo->usTimes_ok  ++  ;					
				}
#endif
				
				pMem->var.video.iDiff_pkts_fromSelect  =  pResp->usDiff_pkts;	
				pMem->var.video.usDelay  =  pMsgInput->tRecvTime  -  pMsgInput->tStartTime;			//  2009/09/11
				pMem->var.video.tRecvTime_lastResp  =  pMsgInput->tRecvTime;						//  2009/09/11
				
				//
				if  (  pResp->usDiff_pkts  )  {
					pMem->var.video.lastErr.idInfo.ui64Id  =  pResp->idInfo.ui64Id;
					pMem->var.video.lastErr.uiTran_openAvDev  =  pResp->uiTranNo_openAvDev;
					pMem->var.video.lastErr.tSelectTime  =  pResp->tSelectTime;
					pMem->var.video.lastErr.uiCnt_pkts_fromSelect  =  pResp->usCnt_pkts;
					pMem->var.video.lastErr.iDiff_pkts_fromSelect  =  pResp->usDiff_pkts;
					pMem->var.video.lastErr.tRecvTime_lastResp  =  pMsgInput->tRecvTime;
				}

				//
				time_t  tNow;  time(  &tNow  );
				unsigned  short  usState  =  get_respInfoMem_state(  pMisCnt,  tNow,  pMem,  NULL  );
				if  (  usState  !=  pMem->var.usState_byDlgTalk  )  {
					pMem->var.bNeedCalc_byProcTaskDataResp  =  TRUE;
					pRespInfo->bNeedCalc_byProcTaskDataResp  =  TRUE;
				}
				

				////////////////////////////
				//  2009/09/11
				if  (  !pTaskInfo->var.curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {
					ROUTE_sendLocalAv	*	pRoute  =  &pTaskInfo->var.curRoute_sendLocalAv;
					if  (  pRoute->route.idInfo_to.ui64Id  ==  pMem->idInfo.ui64Id  )  pTaskInfo->var.curRoute_sendLocalAv.routeInfo.tRecvTime_lastResp  =  pMsgInput->tRecvTime;
					else  {
						  for  (  i  =  0;  i  <  mycountof(  pRoute->route.mems_to  );  i  ++  )  {
							   if  (  !pRoute->route.mems_to[i].idInfo.ui64Id  )  continue;
							   if  (  pRoute->route.mems_to[i].idInfo.ui64Id  ==  pMem->idInfo.ui64Id  )  {
								   pTaskInfo->var.curRoute_sendLocalAv.routeInfo.mems[i].tRecvTime_lastResp  =  pMsgInput->tRecvTime;
								   break;
							   }
						  }
					}
				}

				//
				#ifdef  __DEBUG__
						#if  0
						TCHAR  tBuf[128];
						_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "procTaskVideodataResp: %I64u, for %I64u,%d"  ),  pMem->idInfo.ui64Id,  pResp->idInfo.ui64Id,  pResp->uiTranNo_openAvDev  );
						showInfo_open0(  0,  0,  tBuf  );
						#endif
				#endif
		  
	
	//
	//pCompressVideo->ucTimeoutInS_showFrameInfoResp  =  (  ucTimeoutInS_showFrameInfoResp  +  (  unsigned  char  )(  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  )  +  3  )  /  2;	
	//
	//pCompressVideo->tRecvTime_resp_fromCli  =  pMsgInput->tRecvTime;	//  
	
	iErr  =  0;

errLabel:

	if  (  tHintBuf[0]  )  	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tHintBuf  );

	return  iErr;

}



//
__declspec(  dllexport  )  int  procTaskAudioDataResp(  MC_VAR_isCli  *  pProcInfo,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask,  MIS_MSG_INPUT  *  pMsgInput,  TRANSFER_AUDIO_dataResp  *  pResp  )
{															 
	int					iErr									=		-1;
	char				timeBuf[32]								=		"";
	TCHAR				tHintBuf[255  +  1]						=		_T(  "AudioDataResp:"  );
	//
	time_t				tSelectTime								=		0;
	int					i;
	unsigned  short		usDelay									=		0;

	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;

	//
	TASK_respInfo  *  pRespInfo  =  &pTaskInfo->var.taskRespInfo;
	TASK_respInfo_mem  *  pMem  =  NULL;
	
	//
	//tSelectTime  =  pCompressAudio->tSelectTime;

	//  showDebugInfo(  pProcInfo,  _T(  "AudioResp"  ),  pMsgInput  );


	//
	getTimelStr(  pMsgInput->tStartTime,  timeBuf,  mycountof(  timeBuf  )  );

	//	
	if  (  pMsgInput->tRecvTime  <  pMsgInput->tStartTime  )  {
		qyShowInfo1(  CONST_qyShowType_debug,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskAudioDataResp: recvTime < startTime [%s], skipped"  ),  CQyString(  timeBuf  )  );
		iErr  =  0;  goto  errLabel;
	}
	if  (  pMsgInput->tStartTime  <  tSelectTime  )  {
		pProcInfo->av.localAv.recordSoundProcInfo.usTimes_failure  ++  ;
		qyShowInfo1(  CONST_qyShowType_debug,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskAudioDataResp: startTime [%s] < selectTime, skipped"  ),  CQyString(  timeBuf  )  );
		iErr  =  0;  goto  errLabel;		
	}
	
	_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "AudioDataResp: %I64u, time-consuming %ds, usCnt_pkts %d"  ),  pMsgInput->data.route.idInfo_from.ui64Id,  pMsgInput->tRecvTime  -  pMsgInput->tStartTime,  pResp->usCnt_pkts  );
	//  traceLogA(  (  "Audio: tn %d, time-consuming %ds, usCnt_pkts %d"  ),  pResp->uiTranNo_openAvDev,  pMsgInput->tRecvTime  -  pMsgInput->tStartTime,  pResp->usCnt_pkts  );


	if  (  !isRcOk(  pMsgInput->usCode  )  )  {
			  pProcInfo->av.localAv.recordSoundProcInfo.usTimes_failure  ++  ;
			  qyShowInfo1(  CONST_qyShowType_debug,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "AudioDataResp: rc %d not ok, startTime [%s], error"  ),  pMsgInput->usCode,  CQyString(  timeBuf  )  );
			}
	else  {
	
		  usDelay  =  (  unsigned  short  )(  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  );

		  //
		  pMem  =  get_respInfoMem(  pProcInfo,  pRespInfo,  &pMsgInput->data.route.idInfo_from,  pTask->uiTaskType  );
		  //
		  if  (  !pMem  )  {
			  showInfo_open0(  0,  _T(  "AudioDataResp"  ),  _T(  "failed: pMem is null"  )  );
			  goto  errLabel;
		  }

		  //
		  if  (  usDelay  !=  pMem->var.audio.usDelay  )  {
			  if  (  pMem->var.audio.usDelay  
				  &&  usDelay  >  pMem->var.audio.usDelay  +  1  )  
			  {
				  pProcInfo->av.localAv.recordSoundProcInfo.usTimes_failure  ++  ;

				  qyShowInfo1(  CONST_qyShowType_debug,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "AudioDataResp: time-consuming [%d] increases, error"  ),  usDelay  );
			  }
		
			  pMem->var.audio.usDelay  =  usDelay;
		  }
	}

	//pCompressAudio->ucTimeoutInS_showFrameInfoResp  =  (  pCompressAudio->ucTimeoutInS_showFrameInfoResp  +  (  unsigned  char  )(  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  )  +  3  )  /  2;	
	//
	//pCompressAudio->tRecvTime_resp_fromCli  =  pMsgInput->tRecvTime;
	
	iErr  =  0;
errLabel:

	if  (  tHintBuf[0]  )  	qyShowInfo1(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tHintBuf  );

	return  iErr;

}


//
__declspec(  dllexport  )  int  procTaskGpsDataResp(  MC_VAR_isCli  *  pProcInfo,  void  *  pTranInfo,  PROC_TASK_GPS  *  pTask,  MIS_MSG_INPUT  *  pMsgInput,  TRANSFER_GPS_dataResp  *  pResp  )
{															 
	int					iErr									=		-1;
	char				timeBuf[32]								=		"";
	TCHAR				tHintBuf[255  +  1]						=		_T(  "AudioDataResp:"  );
	//
	time_t				tSelectTime								=		0;
	int					i;
	unsigned  short		usDelay									=		0;

	QY_SHARED_OBJ		*	pSharedObj							=		getSharedObjByIndex(  pProcInfo,  pTask->iIndex_sharedObj  );		//  ÕâÀïÓ¦¸ÃÓÃindexÀ´»ñÈ¡
	if  (  !pSharedObj  )  return  -1;

#if  0

	getTimelStr(  pMsgInput->tStartTime,  timeBuf,  mycountof(  timeBuf  )  );

	//	
	if  (  pMsgInput->tRecvTime  <  pMsgInput->tStartTime  )  {
		qyShowInfo1(  CONST_qyShowType_debug,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskAudioDataResp: recvTime < startTime [%s], skipped"  ),  CQyString(  timeBuf  )  );
		iErr  =  0;  goto  errLabel;
	}
	
	_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "gpsDataResp: %I64u, time-consuming %ds"  ),  pMsgInput->data.route.idInfo_from.ui64Id,  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  );
	//  traceLogA(  (  "Audio: tn %d, time-consuming %ds, usCnt_pkts %d"  ),  pResp->uiTranNo_openAvDev,  pMsgInput->tRecvTime  -  pMsgInput->tStartTime,  pResp->usCnt_pkts  );


	if  (  !isRcOk(  pMsgInput->usCode  )  )  {
			  qyShowInfo1(  CONST_qyShowType_debug,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "AudioDataResp: rc %d not ok, startTime [%s], error"  ),  pMsgInput->usCode,  CQyString(  timeBuf  )  );
			}
	else  {
	
		  usDelay  =  (  unsigned  short  )(  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  );

	}

	//  2009/09/11
	if  (  !pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {
		ROUTE_sendLocalAv	*	pRoute  =  &pSharedObj->curRoute_sendLocalAv;
		if  (  pRoute->route.idInfo_to.ui64Id  ==  pMsgInput->data.route.idInfo_from.ui64Id  )  pSharedObj->curRoute_sendLocalAv.routeInfo.tRecvTime_lastResp  =  pMsgInput->tRecvTime;
		else  {
			  for  (  i  =  0;  i  <  mycountof(  pRoute->route.mems_to  );  i  ++  )  {
				   if  (  !pRoute->route.mems_to[i].idInfo.ui64Id  )  continue;				
				   if  (  pRoute->route.mems_to[i].idInfo.ui64Id  ==  pMsgInput->data.route.idInfo_from.ui64Id  )  {
					   pSharedObj->curRoute_sendLocalAv.routeInfo.mems[i].tRecvTime_lastResp  =  pMsgInput->tRecvTime;
					   break;
				   }
			  }
		}
	}

#endif
	
	iErr  =  0;
errLabel:

	if  (  tHintBuf[0]  )  	qyShowInfo1(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tHintBuf  );

	return  iErr;

}



