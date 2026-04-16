

#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#include	"qmcSound_dx.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qmcTaskInfo.h"

//
int  dispatch_outputConfAudio(  PROC_TASK_AV  *  pTask,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_AUDIO_DATA  *  pReq,  QY_MESSENGER_ID  *  pIdInfo_from,  int  uiTranNo_openAvDev_conf  );


//
#if  0
 int  iiold_dispatchTaskAudio(  QIS_DISPATCH  *  pDispatch,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_AUDIO_DATA  *  pReq,  int  index_pMems_from,  int  index_activeMems_from,  MIS_MSGU  *  pMsgBuf  )
{
#ifdef  __WINCE__
	return  -1;
#else
	int						iErr				=	-1;

	MC_VAR_isCli			*	pProcInfo			=	(  MC_VAR_isCli  *  )pDispatch->pProcInfo;
	MSGR_ADDR			*	pAddr				=	pDispatch->pAddr_logicalPeer;
	int						iTaskId				=	pDispatch->iTaskId;  
	AV_TRAN_INFO		*	pTranInfo			=	(  AV_TRAN_INFO  *  )pDispatch->pTranInfo;
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pDispatch->pTask;

	
	QY_MC				*	pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;
	MIS_CNT				*	pMisCnt				=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	int						tmpiRet				=	0;
	char					timeBuf[32]			=	"";
	TCHAR					tHintBuf[256]		=	_T(  ""  );
	if  (  !pReq  ||  !pReq->usCnt  ||  pReq->usCnt  >  mycountof(  pReq->mems  )  )  return  -1;

	TASK_AV_FROM		*	pFrom				=	NULL;

	//
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;


	//
#if  0
	if  (  index_pMems_from  <  0  ||  index_pMems_from  >=  pTask->usCntLimit_mems_from  )  return  -1;
	pFrom  =  &pTask->pMems_from1[index_pMems_from];
#endif
	pFrom  =  getTaskAvFrom(  pTask,  index_pMems_from,  _T(  "dispatchTaskAudio"  )  );
	if  (  !pFrom  )  return  -1;

	if  (  pTask->ucbVideoConferenceStarter  )  {
		if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  return  -1;
	}

	//
	int						index				=	index_pMems_from;
	DWORD					curTickCnt			=	GetTickCount(  );	

	TCHAR					where_showInfo[32]	=	_T(  ""  );		_sntprintf(  where_showInfo,  mycountof(  where_showInfo  ),  _T(  "dispatchA %d"  ),  index_activeMems_from  );

	if  (  !pAddr  )  return  -1;
	
	if  (  pMsgTask->tStartTime  <  pFrom->tStartTime_task  )  {
		_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tStartTime < tStartTime_task. skipped."  ),  tHintBuf  );  goto  errLabel;
	}
	if  (  pMsgTask->dwTickCnt_start  )  {	//  2009/03/22
		int  iElapse  =  curTickCnt  -  pMsgTask->dwTickCnt_start;
		if  (  iElapse  >  pProcInfo->cfg.policy.usTimeoutInMsToSwitch_rt  )  {
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%I64u,  %dms elapsed, start %u, msg skipped"  ),  pFrom->idInfo.ui64Id,  iElapse,  pMsgTask->dwTickCnt_start  );
			goto  errLabel;
		}
	}


	//  check
	if  (  pMsgTask->data.route.idInfo_from.ui64Id  !=  pFrom->idInfo.ui64Id
		||  pReq->uiTranNo_openAvDev  !=  pFrom->audio.ta_recvd.uiTranNo_openAvDev  )  
	{
		traceLogA(  (char*)  "procTaskAudio: idInfo_from %I64u, audioData.uiTranNo %d !=  pFrom %I64u, %d",  pMsgTask->data.route.idInfo_from.ui64Id,  pReq->uiTranNo_openAvDev,  pFrom->idInfo.ui64Id,  pFrom->audio.ta_recvd.uiTranNo_openAvDev  );  
		goto  errLabel;
	}


	//  
	//
	pFrom->audio.usCnt_pkts  ++  ;
	if  (  pReq->tLastTime_showFrameInfo_020534  )  {
		if  (  !pFrom->audio.tLastTime_showFrameInfo_020534  )  {	//  OK
			pReq->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;

			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "."  )  );

			pFrom->audio.ta_recvd.uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;
			}
		else  if  (  pFrom->audio.ta_recvd.uiTranNo_openAvDev  ==  pReq->uiTranNo_openAvDev
					&&  pFrom->audio.tLastTime_showFrameInfo_020534  ==  pReq->tLastTime_showFrameInfo_020534  
						&&  pFrom->audio.usCnt_pkts  >=  pReq->usCnt_pkts  )  
				{
					pReq->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;

					_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "pkts %d, "  ),  pReq->usCnt_pkts  );
				}
		else  {
			  CQyString	str;
			  CQyString	str_expected;

			  pReq->tmpInternal.result.usRespCode  =  CONST_qyRc_err;

			  getTimelStr(  pFrom->audio.tLastTime_showFrameInfo_020534,  timeBuf,  mycountof(  timeBuf  )  );  str  =  CQyString(  timeBuf  );
			  getTimelStr(  (  time_t  )pReq->tLastTime_showFrameInfo_020534,  timeBuf,  mycountof(  timeBuf  )  );  str_expected  =  CQyString(  timeBuf  );
			  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "Error: ( %d, %s, %d pkts ) != ÆÚÍû  ( %d, %s, %d pkts )."  ),  pFrom->audio.ta_recvd.uiTranNo_openAvDev,  str,  pFrom->audio.usCnt_pkts,  pReq->uiTranNo_openAvDev,  str_expected,  pReq->usCnt_pkts  );

			  pFrom->audio.ta_recvd.uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;			
		}
		pReq->tmpInternal.result.usCnt_pkts  =  pFrom->audio.usCnt_pkts;	//  Òª½«·¢ËÍµÄÖ¡Êý·¢»Ø·¢ËÍ·½¡£

		pFrom->audio.usCnt_pkts  =  0;
		pFrom->audio.tLastTime_showFrameInfo_020534  =  pMsgTask->tStartTime;
	}


#if  0	//  2014/11/22
	//  
	int								i;
	DWORD							dwBytes_pcm;
	TRANSFER_AUDIO_dataMemHead	*	pMem;
	int								iPos;
	WAVEFORMATEX				*	pWfx_toPlay;


	if  (  !pReq->usCnt  ||  pReq->usCnt  >  mycountof(  pReq->mems  )  )  {
		traceLogA(  (char*)  "procTaskAudio failed: pReq->usCnt %d error",  pReq->usCnt  );
		goto  errLabel;
	}

		//  2009/05/31  
	if  (  pTask->ucbVideoConferenceStarter  )  {
					
		#if  0
			myAUDIO_ENC				*	pEnc						=	NULL;

			if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTask->mixer.usCnt_encs  )  goto  errLabel;
			pEnc  =  &pTask->mixer.encs[index_activeMems_from];
		#endif

		unsigned  int				uiChannelType				=	CONST_channelType_realTimeMedia;
		time_t						tStartTran;					time(  &tStartTran  );  
		unsigned  char				ucbNeedShowFrameInfo		=	FALSE;

		//  unsigned  short  usFrames_perSecond;	usFrames_perSecond  =  pProcInfo->cfg.policy.video.usFrames_perSecond_videoConference;

		unsigned  char				ucFlg						=	0;
		unsigned  int	uiTranNo;  if  (  (  uiTranNo  =  getuiNextTranNo(  0,  0,  0  )  )  ==  -1  )  goto  errLabel;
		int							lenInBytes					=	0;

		#if  0
			 unsigned  int  old_uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;
			 pReq->uiTranNo_openAvDev  =  pTranInfo->audio.uiTranNo_openAvDev;			 
		#endif

		//  convert format in order to send to group
		for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
			 pReq->mems[i].idInfo.ui64Id  =  pFrom->idInfo.ui64Id;
			 //  2013/08/04
			 pReq->mems[i].uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;
			 //
			 pReq->mems[i].usIndex_ii  =  index_activeMems_from;
		}


		//				
			 if  (  tmpiRet  =  q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->mixer.pOutputQ2  )  )  {
				 if  (  tmpiRet  !=  CONST_qyRet_qFull  )  goto  errLabel;
				 //  iErr  =  0;  goto  errLabel;		
			 }
			 MIS_CHANNEL	*	pChannel;
			 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  goto  errLabel;
			 q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2  );		//  ´¥·¢Ò»ÏÂ·¢ËÍ


	}
#endif

	BOOL  bOutputA  =  FALSE;
	if  (  pTask->ucbVideoConferenceStarter  )  {
		bOutputA  =  TRUE;
		}
	else  {
		  bOutputA  =  TRUE;
	}

	//
	if  (  bOutputA  )  {
		//  2014/11/11
		if  (  iidispatch_outputConfAudio(  pTask,  pMsgTask,  pReq,  &pFrom->idInfo,  pFrom->audio.ta_recvd.uiTranNo_openAvDev  )  )  {
			goto  errLabel;
		}
	}


	//  2014/11/26
	if  (  pFrom->idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
		#ifdef  __DEBUG__
				//  traceLog((TCHAR*)  _T(  "dispatchA: my pkt, skipped"  )  );
		#endif
		iErr  =  0;  goto  errLabel;
	}
	
	//
	QY_TRANSFORM  *  pTransform  =  MACRO_getTransform(  *pTask,  index_activeMems_from  );
	if  (  pTransform  )  {
		q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->audio.q2  );
	}

	iErr  =  0;  

errLabel:

	if  (  !iErr  )  {
		mySendAvResp(  pProcInfo,  pMsgTask,  pMsgBuf  );
	}

	if  (  iErr  ||  tHintBuf[0]  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "%I64u %s: %s"  ),  pMsgTask->data.route.idInfo_from.ui64Id,  (  iErr  ?  _T(  "failed"  )  :  _T(  ""  )  ),  tHintBuf  );
	
	return  iErr;
#endif
}
#endif


//
int  dispatchTaskAudio(  QIS_DISPATCH  *  pDispatch,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_AUDIO_DATA  *  pReq,  int  index_pMems_from1,  int  index_activeMems_from,  MIS_MSGU  *  pMsgBuf  )
{
#ifdef  __WINCE__
	return  -1;
#else
	int						iErr				=	-1;

	MC_VAR_isCli			*	pProcInfo			=	(  MC_VAR_isCli  *  )pDispatch->pProcInfo;
	MSGR_ADDR			*	pAddr				=	pDispatch->pAddr_logicalPeer;
	int						iTaskId				=	pDispatch->iTaskId;  
	AV_TRAN_INFO		*	pTranInfo			=	(  AV_TRAN_INFO  *  )pDispatch->pTranInfo;
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pDispatch->pTask;

	
	QY_MC				*	pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;
	MIS_CNT				*	pMisCnt				=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	int						tmpiRet				=	0;
	char					timeBuf[32]			=	"";
	TCHAR					tHintBuf[256]		=	_T(  ""  );
	if  (  !pReq  ||  !pReq->usCnt  ||  pReq->usCnt  >  mycountof(  pReq->mems  )  )  return  -1;


	//
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;


	//
#if  0
	TASK_AV_FROM		*	pFrom				=	NULL;
	pFrom  =  getTaskAvFrom(  pTask,  index_pMems_from,  _T(  "dispatchTaskAudio"  )  );
	if  (  !pFrom  )  return  -1;

	if  (  pTask->ucbVideoConferenceStarter  )  {
		if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  return  -1;
	}
#endif

	if  (  !pTask->ucbVideoConferenceStarter  )  {
		return  -1;
	}
	if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  return  -1;
	DLG_TALK_videoConferenceActiveMemFrom * pActiveMem_from = &pTc->videoConference.activeMems_from[index_activeMems_from];


	//
	//int						index				=	index_pMems_from;
	DWORD					curTickCnt			=	GetTickCount(  );	

	TCHAR					where_showInfo[32]	=	_T(  ""  );		_sntprintf(  where_showInfo,  mycountof(  where_showInfo  ),  _T(  "dispatchA %d"  ),  index_activeMems_from  );

	if  (  !pAddr  )  return  -1;
	
#if  0
	if  (  pMsgTask->tStartTime  <  pFrom->tStartTime_task  )  {
		_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tStartTime < tStartTime_task. skipped."  ),  tHintBuf  );  goto  errLabel;
	}
#endif
	if  (  pMsgTask->dwTickCnt_start  )  {	//  2009/03/22
		int  iElapse  =  curTickCnt  -  pMsgTask->dwTickCnt_start;
		if  (  iElapse  >  pProcInfo->cfg.policy.usTimeoutInMsToSwitch_rt  )  {
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%I64u,  %dms elapsed, start %u, msg skipped"  ),  pActiveMem_from->avStream.idInfo.ui64Id,  iElapse,  pMsgTask->dwTickCnt_start  );
			goto  errLabel;
		}
	}


	//  check
	if  (  pMsgTask->data.route.idInfo_from.ui64Id  !=  pActiveMem_from->avStream.idInfo.ui64Id
		||  pReq->uiTranNo_openAvDev  !=  pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev  )  
	{
		traceLogA(  (char*)  "procTaskAudio: idInfo_from %I64u, audioData.uiTranNo %d !=  pFrom %I64u, %d",  pMsgTask->data.route.idInfo_from.ui64Id,  pReq->uiTranNo_openAvDev,  pActiveMem_from->avStream.idInfo.ui64Id,  pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev  );  
		goto  errLabel;
	}


	//  
	//
#if  0
	pFrom->audio.usCnt_pkts  ++  ;
	if  (  pReq->tLastTime_showFrameInfo_020534  )  {
		if  (  !pFrom->audio.tLastTime_showFrameInfo_020534  )  {	//  OK
			pReq->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;

			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "."  )  );

			pFrom->audio.ta_recvd.uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;
			}
		else  if  (  pFrom->audio.ta_recvd.uiTranNo_openAvDev  ==  pReq->uiTranNo_openAvDev
					&&  pFrom->audio.tLastTime_showFrameInfo_020534  ==  pReq->tLastTime_showFrameInfo_020534  
						&&  pFrom->audio.usCnt_pkts  >=  pReq->usCnt_pkts  )  
				{
					pReq->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;

					_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "pkts %d, "  ),  pReq->usCnt_pkts  );
				}
		else  {
			  CQyString	str;
			  CQyString	str_expected;

			  pReq->tmpInternal.result.usRespCode  =  CONST_qyRc_err;

			  getTimelStr(  pFrom->audio.tLastTime_showFrameInfo_020534,  timeBuf,  mycountof(  timeBuf  )  );  str  =  CQyString(  timeBuf  );
			  getTimelStr(  (  time_t  )pReq->tLastTime_showFrameInfo_020534,  timeBuf,  mycountof(  timeBuf  )  );  str_expected  =  CQyString(  timeBuf  );
			  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "Error: ( %d, %s, %d pkts ) != ÆÚÍû  ( %d, %s, %d pkts )."  ),  pFrom->audio.ta_recvd.uiTranNo_openAvDev,  str,  pFrom->audio.usCnt_pkts,  pReq->uiTranNo_openAvDev,  str_expected,  pReq->usCnt_pkts  );

			  pFrom->audio.ta_recvd.uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;			
		}
		pReq->tmpInternal.result.usCnt_pkts  =  pFrom->audio.usCnt_pkts;	//  Òª½«·¢ËÍµÄÖ¡Êý·¢»Ø·¢ËÍ·½¡£

		pFrom->audio.usCnt_pkts  =  0;
		pFrom->audio.tLastTime_showFrameInfo_020534  =  pMsgTask->tStartTime;
	}
#endif


#if  0	//  2014/11/22
	//  
	int								i;
	DWORD							dwBytes_pcm;
	TRANSFER_AUDIO_dataMemHead	*	pMem;
	int								iPos;
	WAVEFORMATEX				*	pWfx_toPlay;


	if  (  !pReq->usCnt  ||  pReq->usCnt  >  mycountof(  pReq->mems  )  )  {
		traceLogA(  (char*)  "procTaskAudio failed: pReq->usCnt %d error",  pReq->usCnt  );
		goto  errLabel;
	}

		//  2009/05/31  
	if  (  pTask->ucbVideoConferenceStarter  )  {
					
		#if  0
			myAUDIO_ENC				*	pEnc						=	NULL;

			if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTask->mixer.usCnt_encs  )  goto  errLabel;
			pEnc  =  &pTask->mixer.encs[index_activeMems_from];
		#endif

		unsigned  int				uiChannelType				=	CONST_channelType_realTimeMedia;
		time_t						tStartTran;					time(  &tStartTran  );  
		unsigned  char				ucbNeedShowFrameInfo		=	FALSE;

		//  unsigned  short  usFrames_perSecond;	usFrames_perSecond  =  pProcInfo->cfg.policy.video.usFrames_perSecond_videoConference;

		unsigned  char				ucFlg						=	0;
		unsigned  int	uiTranNo;  if  (  (  uiTranNo  =  getuiNextTranNo(  0,  0,  0  )  )  ==  -1  )  goto  errLabel;
		int							lenInBytes					=	0;

		#if  0
			 unsigned  int  old_uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;
			 pReq->uiTranNo_openAvDev  =  pTranInfo->audio.uiTranNo_openAvDev;			 
		#endif

		//  convert format in order to send to group
		for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
			 pReq->mems[i].idInfo.ui64Id  =  pFrom->idInfo.ui64Id;
			 //  2013/08/04
			 pReq->mems[i].uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;
			 //
			 pReq->mems[i].usIndex_ii  =  index_activeMems_from;
		}


		//				
			 if  (  tmpiRet  =  q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->mixer.pOutputQ2  )  )  {
				 if  (  tmpiRet  !=  CONST_qyRet_qFull  )  goto  errLabel;
				 //  iErr  =  0;  goto  errLabel;		
			 }
			 MIS_CHANNEL	*	pChannel;
			 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  goto  errLabel;
			 q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2  );		//  ´¥·¢Ò»ÏÂ·¢ËÍ


	}
#endif

	//
		//  2014/11/26
	if  (  pActiveMem_from->avStream.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
		#ifdef  __DEBUG__
				//  traceLog((TCHAR*)  _T(  "dispatchA: my pkt, skipped"  )  );
		#endif
		}
	else  {
	
		  //
		  QY_TRANSFORM  *  pTransform  =  MACRO_getTransform(  *pTask,  index_activeMems_from  );
		  if  (  pTransform  )  {
			  if (pProcInfo->cfg.b_useAudioQ2_toDecA) {
				  q2PostMsgAndTrigger(pMsgTask, offsetof(MIS_MSG_TASK, data) + pMsgTask->lenInBytes, &pTransform->audio.q2, _T("dispatchTaskAudio"));
			  }
			  else {
				  TRANSFER_AUDIO_DATA* pTransferAudioData = pReq;
				  //
				  TRANSFER_AUDIO_dataMemHead* pMem;
				  int iPos;
				  int i;
				  for (iPos = 0, i = 0; i < pTransferAudioData->usCnt; iPos = (int)(iPos + pMem->uiLen), i++)
				  {
					  pMem = &pTransferAudioData->mems[i];
					  if (pMem == mynull) goto errLabel;
#ifdef DEBUG
					  //ref TRANSFER_AUDIO_dataMemHead tmp_pMem = ref * pMem;
#endif
					  if (0 == pMem->uiLen)
					  {
						  //
#ifdef __DEBUG__
							//traceLogA(  "findOrgMsg: transferAudioMem.uiLen is 0. skipped."  );
#endif
											//
						  continue;
					  }

					  if (iPos + pMem->uiLen > pTransferAudioData->uiLen)
					  {
#ifdef __DEBUG__
						  traceLogA((char*)"findOrgMsg failed: iPos + mem.uiLen > data.uiLen");
#endif
						  goto errLabel;
					  }

					  if (0 == pMem->idInfo.ui64Id) pMem->idInfo.ui64Id = pMsgTask->data.route.idInfo_from.ui64Id;

					  //
					  if (0 == pMem->uiTranNo_openAvDev)pMem->uiTranNo_openAvDev = pTransferAudioData->uiTranNo_openAvDev;
					  byte* data = (byte*)pTransferAudioData->buf + iPos;
					  //
					  pTransform->audio.qBuf2->q2PostMsgAndTrigger(pMem, data, pMem->uiLen, _T("tmp_findOrg_procTaskAudio"));
					  //
				  }

				  //
			  }
		  }
	}

	//
	if (pTask->ucbVideoConferenceStarter) {
		//

		Param_saveAv  param = { 0 };
		int  i;
		param.pSaveAvPktU = &pDispatch->tmpBuf_saveAPkt;
		int  iFourcc = pActiveMem_from->avStream.obj.tranInfo.audio.ah_compress.wfx.wFormatTag;
		//
		char  buf[128];
		if (iFourcc == WAVE_FORMAT_MPEGLAYER3) {
			int  ii = 0;
		}

		//
		
		//
		char* p;
		TRANSFER_AUDIO_dataMemHead* pMem;
		int  iPos = 0;
		for (i = 0; i < pReq->usCnt; i++) {
			pMem = &pReq->mems[i];
			if (pMem->uiLen + iPos > pReq->uiLen)  break;
			p = pReq->buf + iPos;
			//
			postAPktToSave(&param, false, index_activeMems_from, pMem->idInfo.ui64Id,pMem->uiTranNo_openAvDev,  iFourcc, pMem->uiSampleTimeInMs, pMem->uiPts, p, pMem->uiLen);
			//
		}


	}



	//
	BOOL  bOutputA; bOutputA = FALSE;
	if  (  pTask->ucbVideoConferenceStarter  )  {
		bOutputA  =  TRUE;
		}
	else  {
		  bOutputA  =  TRUE;
	}

	//
	if  (  bOutputA  )  {
		//  2014/11/11
		if  (  dispatch_outputConfAudio(  pTask,  pMsgTask,  pReq,  &pActiveMem_from->avStream.idInfo,  pTranInfo->audio.uiTranNo_openAvDev  )  )  {
			goto  errLabel;
		}
	}



	iErr  =  0;  

errLabel:

	if  (  !iErr  )  {
		mySendAvResp(  pProcInfo,  pMsgTask,  pMsgBuf  );
	}

	if  (  iErr  ||  tHintBuf[0]  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "%I64u %s: %s"  ),  pMsgTask->data.route.idInfo_from.ui64Id,  (  iErr  ?  _T(  "failed"  )  :  _T(  ""  )  ),  tHintBuf  );
	
	return  iErr;
#endif
}



//
 extern "C" DWORD WINAPI mcThreadProc_dispatchAudio( LPVOID lpParameter )
{
	 QIS_DISPATCH					*	pDispatch					=	(  QIS_DISPATCH  *  )lpParameter;
	 if  (  !pDispatch  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo					=	(  MC_VAR_isCli  *  )pDispatch->pProcInfo;
	 if (  !pProcInfo  )  return  -1;	 
	 PROC_TASK_AV					*	pTask						=	(  PROC_TASK_AV  *  )pDispatch->pTask;
	 if  (  !pTask  )  return  -1;
	 QIS_DISPATCH_procInfo			*	pDispatchAudio				=	&pDispatch->audio;

	 QY_MC							*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;
	 DYN_LIB_DX						*	pDynLib						=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	 //  int								i;

	 CQyMalloc							mallocObj;
	 MIS_MSGU						*	pMsg						=	NULL;
	 unsigned  int						len;

	 IM_CONTENTU					*	pContent					=	NULL;

	 #define		DEFAULT_dwToInMs		5000
	 DWORD								dwToInMs					=	DEFAULT_dwToInMs;

	 DWORD								dwTickCnt_lastAudioData		=	GetTickCount(  );;						// 

	 CQyMalloc							mallocObj_pMsgBuf;
	 MIS_MSGU						*	pMsgBuf						=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;


#ifdef  __DEBUG__
	 traceLogA(  (char*)  "mcThreadProc_dispatchAudio enters"  );
#endif

	 /*
	 for  (  i  =  0;  i  <  mycountof(  pDispatchAudio->hEvents  );  i  ++  )  {
		  pDispatchAudio->hEvents[i] = CreateEvent( NULL, FALSE, FALSE, NULL );
		  if ( NULL == pDispatchAudio->hEvents[i] ) goto  errLabel;
	 }
	 */

	 pDispatchAudio->bRunning  =  TRUE;
	 //  memset(  &pDispatchAudio->m_var,  0,  sizeof(  pDispatchAudio->m_var  )  );

	 if  (  !(  pMsg  =  (  MIS_MSGU  *  )mallocObj.mallocf(  sizeof(  MIS_MSGU  )  )  )  )  goto  errLabel;

	 //
	 //  2014/11/21
	 BOOL  bNeeded; bNeeded = FALSE;
	 //
	 if  (  pTask->ucbVideoConferenceStarter  )  bNeeded  =  TRUE;
	 if  (  pTask->doProxy.bExists_avProxy  )  bNeeded  =  TRUE;
	 //
	 if  (  !bNeeded  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "dispatchA failed. no needed"  );
		 #endif
		 showInfo_open0(  0,  0,  _T(  "dispatchA failed, no needed"  )  );
		 goto  errLabel;
	 }

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s starts"  ),  pDispatchAudio->q2.cfg.name  );

	
	 for  (  ;  !pDispatchAudio->bQuit;  )  {
		  
		  if  (  !dwToInMs  )  {			  
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: mcThreadProc_transformAudio: dwToInMs %d"  ),  dwToInMs  );
			  dwToInMs  =  DEFAULT_dwToInMs;
		  }

		  DWORD  dwTickCnt0  =  GetTickCount(  );
		  DWORD  dwTickCnt;
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(
							 pDispatchAudio->q2.cfg.usCnt_hEvents,	//  mycountof(  pDispatchAudio->hEvents  ),		// Number of events.
							 pDispatchAudio->q2.hEvents,						// Location of handles.
                             FALSE,										// Wait for all?
                             dwToInMs,									// How long to wait?
                             0  );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  goto  errLabel;
	      //
		  dwTickCnt =   GetTickCount(  );

		  if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
			  dwEvt -= WAIT_OBJECT_0;
			  switch  (  dwEvt  )  {
					  case  0:
						     dwTickCnt_lastAudioData  =  dwTickCnt;		//  audio data received
							 break;
					  case  1:
						     traceLogA(  (char*)  "dispatchAudio: event 1."  );
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
		  }


		  for  (  ;  !pDispatchAudio->bQuit;  )  {

			   len  =  sizeof(  pMsg[0]  );
			   {
				   CQyQ2Help	q2Help;
				   if  (  qGetMsg(  q2Help.getQ_toGetMsg(  &pDispatchAudio->q2,  _T(  "threadProc_dispatchA"  )), pMsg, &len))  break;
			   }
			   memset(  (  (  char  *  )pMsg  )  +  len,  0,  min(  256,  sizeof(  pMsg[0]  )  -  len  )  );			   
			   switch  (  pMsg->uiType  )  {
					   case  CONST_misMsgType_task:
						     pContent		=	(  IM_CONTENTU  *  )pMsg->task.data.buf;
							 switch  (  pContent->uiType  )  {
									 case  CONST_imCommType_transferAudioData:
										   #ifdef  __DEBUG__
												   //  traceLogA(  (char*)  "transferAudioData: here"  );
										   #endif

										   if  (  pDispatch->index_activeMems_from  !=  pContent->transferAudioData.tmpInternal.param.index_activeMems_from  )  {
											   #ifdef  __DEBUG__
													   traceLog((TCHAR*)  _T(  "dispatchAudio err, index_activeMems_from not matched"  )  );
											   #endif											
											   break;											
										   }

										   dispatchTaskAudio(  pDispatch,  &pMsg->task,  &pContent->transferAudioData,  pContent->transferAudioData.tmpInternal.param.index_pMems_from,  pContent->transferAudioData.tmpInternal.param.index_activeMems_from,  pMsgBuf  );
										   break;
									 default:
											break;
							 }
									 
						     break;
					   default:
							   break;
			   }
			   
			   
		  }




	 }

errLabel:


	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s ends."  ),  pDispatchAudio->q2.cfg.name  );
	 

	 pDispatchAudio->bRunning  =  FALSE;


	 traceLogA(  (char*)  "mcThreadProc_dispatchAudio %S leaves",  pDispatchAudio->q2.cfg.name  );

	return  0;
}




int  dispatch_outputConfAudio(  PROC_TASK_AV  *  pTask,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_AUDIO_DATA  *  pReq,  QY_MESSENGER_ID  *  pIdInfo_from,  int  uiTranNo_openAvDev_conf  )
{
	int  iErr  =  -1;
	
	MIS_CNT				*	pMisCnt				=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	int  tmpiRet;

	//  2014/11/22
	//  
	int								i;
	DWORD							dwBytes_pcm;
	TRANSFER_AUDIO_dataMemHead	*	pMem;
	int								iPos;
	WAVEFORMATEX				*	pWfx_toPlay;

	//
	TRANSFER_AUDIO_DATA  *  pTransferAudioData  =  pReq;


	if  (  !pReq->usCnt  ||  pReq->usCnt  >  mycountof(  pReq->mems  )  )  {
		traceLogA(  (char*)  "procTaskAudio failed: pReq->usCnt %d error",  pReq->usCnt  );
		return  -1; //		goto  errLabel;
	}

		//  2009/05/31  
	//if  (  pTask->ucbVideoConferenceStarter  )  
	
					
		#if  0
			myAUDIO_ENC				*	pEnc						=	NULL;

			if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTask->mixer.usCnt_encs  )  goto  errLabel;
			pEnc  =  &pTask->mixer.encs[index_activeMems_from];
		#endif

		unsigned  int				uiChannelType				=	CONST_channelType_realTimeMedia;
		time_t						tStartTran;					time(  &tStartTran  );  
		unsigned  char				ucbNeedShowFrameInfo		=	FALSE;

		//  unsigned  short  usFrames_perSecond;	usFrames_perSecond  =  pProcInfo->cfg.policy.video.usFrames_perSecond_videoConference;

		unsigned  char				ucFlg						=	0;
		unsigned  int	uiTranNo;  if  (  (  uiTranNo  =  getuiNextTranNo(  0,  0,  0  )  )  ==  -1  )  goto  errLabel;
		int							lenInBytes; lenInBytes = 0;

		#if  0
			 unsigned  int  old_uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;
			 pReq->uiTranNo_openAvDev  =  pTranInfo->audio.uiTranNo_openAvDev;			 
		#endif


		if  (  pTask->ucbVideoConferenceStarter  )  {
			//  convert format in order to send to group
			for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
				 pReq->mems[i].idInfo.ui64Id  =  pIdInfo_from->ui64Id;	//  pFrom->idInfo.ui64Id;
				 //  2013/08/04
				 pReq->mems[i].uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;
				 //
				 //pReq->mems[i].usIndex_ii  =  0;  // index_activeMems_from;
			}
			//
			pReq->uiTranNo_openAvDev  =  uiTranNo_openAvDev_conf;

			}
		else  if  (  pTask->doProxy.bExists_avProxy  )  {	//  2014/11/21
				  //  convert format in order to send to group
				  for  (  i  =  0;  i  <  pTransferAudioData->usCnt;  i  ++  )  {
					  pTransferAudioData->mems[i].idInfo.ui64Id  =  0;		//  pIdInfo_from->ui64Id;  //pFrom->idInfo.ui64Id;
					  //pTransferAudioData->mems[i].usIndex_ii  =  0;			//  index_activeMems_from;
					  //  2012/01/09
					  pTransferAudioData->mems[i].uiTranNo_openAvDev  =  0;	//  uiTranNo_openAvDev_from;	//  pFrom->video.tv_recvd.uiTranNo_openAvDev;		 			
				  }
			      
				  }
		else  {
			  #ifdef  __DEBUG__
					  traceLog((TCHAR*)  _T(  "dispatch_outputConfAudio failed, serious err"  )  );
			  #endif
			  goto  errLabel;
		}





		//				
			 if  (  tmpiRet  =  q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->mixer.pOutputQ2,  _T(  "dispatch_outputConfAudio"  ))) {
				 if  (  tmpiRet  !=  CONST_qyRet_qFull  )  goto  errLabel;
				 //  iErr  =  0;  goto  errLabel;		
			 }
			 MIS_CHANNEL	*	pChannel;
			 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  goto  errLabel;

			 //
			 chkToApplyForChannel(  (CCtxQmc*)pMisCnt->pProcInfoParam,  uiChannelType, false  );
			 
			 //
			 q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2,  _T(  "dispatch_outputConfAudio"  ));		//  ´¥·¢Ò»ÏÂ·¢ËÍ


	


	iErr  =  0;
errLabel:
	return  iErr;
}




//
#if  0
  int  iiold_dispatchTaskVideo(  QIS_DISPATCH  *  pDispatch,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_VIDEO_DATA  *  pTransferVideoData,  int  index_pMems_from,  int  index_activeMems_from,  MIS_MSGU  *  pMsgBuf  )
{
	int						iErr				=	-1;

	MC_VAR_isCli			*	pProcInfo			=	(  MC_VAR_isCli  *  )pDispatch->pProcInfo;  
	MSGR_ADDR			*	pAddr				=	pDispatch->pAddr_logicalPeer;
	int						iTaskId				=	pDispatch->iTaskId;
	AV_TRAN_INFO		*	pTranInfo			=	(  AV_TRAN_INFO  *  )pDispatch->pTranInfo;
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pDispatch->pTask;

	QY_MC				*	pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;
	MIS_CNT				*	pMisCnt				=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	int						tmpiRet				=	0;
	//  QY_WMBUF_COMM			wmBuf;
	char					timeBuf[32]			=	"";
	TCHAR					tHintBuf[256]		=	_T(  ""  );
	//
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo ,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	//
	if  (  pTask->ucbVideoConferenceStarter  )  {
		if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  return  -1;
	}
	else  {
		int ii  =  0;
	}
	TASK_AV_FROM		*	pFrom				=	NULL;
#if  0
	if  (  index_pMems_from  <  0  ||  index_pMems_from  >=  pTask->usCntLimit_mems_from  )  return  -1;
	pFrom  =  &pTask->pMems_from1[index_pMems_from];
#endif
	pFrom  =  getTaskAvFrom(  pTask,  index_pMems_from,  _T(  "dispatchTaskVideo"  )  );
	if  (  !pFrom  )  return  -1;
	//
	int						i;
	DWORD					curTickCnt			=	GetTickCount(  );	

	TCHAR					where_showInfo[32]	=	_T(  ""  );		_sntprintf(  where_showInfo,  mycountof(  where_showInfo  ),  _T(  "dispatchV %d"  ),  index_activeMems_from  );

	//  BYTE				*	pData_allocated		=	NULL;

	if  (  !pAddr  )  return  -1;

	//  2011/12/08
	DEBUG_myDRAW_VIDEO_DATA	*	pDebugPkt  =  &pMsgTask->data.route.debugInfo.debug_myDRAW_VIDEO_DATA;
	if  (  pDebugPkt->dwTickCnt_start  )  {
		pDebugPkt->usToDispatchInMs  =  curTickCnt  -  pDebugPkt->dwTickCnt_start;
	}

	//
	if  (  pMsgTask->tStartTime  <  pFrom->tStartTime_task  )  {
		_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tStartTime < tStartTime_task. skipped."  ),  tHintBuf  );  goto  errLabel;
	}
	if  (  pMsgTask->dwTickCnt_start  )  {	//  2009/03/22
		int  iElapse  =  curTickCnt  -  pMsgTask->dwTickCnt_start;
		if  (  iElapse  >  pProcInfo->cfg.policy.usTimeoutInMsToSwitch  )  {
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%I64u,  %dms elapsed, start %u, msg skipped"  ),  pFrom->idInfo.ui64Id,  iElapse,  pMsgTask->dwTickCnt_start  );
			goto  errLabel;
		}
	}

		

	//  check
	if  (  pMsgTask->data.route.idInfo_from.ui64Id  !=  pFrom->idInfo.ui64Id
		||  pTransferVideoData->uiTranNo_openAvDev  !=  pFrom->video.tv_recvd.uiTranNo_openAvDev  )  
	{
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "procTaskVideo: idInfo_from %I64u, videoData.uiTranNo %d !=  pFrom %I64u, %d",  pMsgTask->data.route.idInfo_from.ui64Id,  pTransferVideoData->uiTranNo_openAvDev,  pFrom->idInfo.ui64Id,  pFrom->video.tv_recvd.uiTranNo_openAvDev  );  
		#endif
		goto  errLabel;
	}

	//  2017/09/04
#ifdef  __DEBUG__
		if  (  0  )  {
			TCHAR  tBuf[128];
			//_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "transferVideo.tSelectTime %I64u, uiLen %d, usCnt %d, iVal_dbg %d"  ),  pTransferVideoData->stat.tSelectTime,  pTransferVideoData->uiLen,  (  int  )pTransferVideoData->usCnt,  pTransferVideoData->stat.iVal_dbg  );
			showInfo_open0(  0,  _T(  "dispatchVideo"  ),  tBuf  );
		}
#endif

	//	
	//
	for  (  i  =  0;  i  <  pTransferVideoData->usCnt;  i  ++  )  {
		 TRANSFER_VIDEO_dataMemHead  *  pMem  =  &pTransferVideoData->mems[i];		
		 //
		 pFrom->video.usCnt_pkts  ++  ;
		 if  (  pMem->stat.tSelectTime  )  {
			if  (  //pFrom->video.tv_recvd.uiTranNo_openAvDev  !=  pTransferVideoData->uiTranNo_openAvDev  ||  
				!pFrom->video.tSelectTime  ||  pFrom->video.tSelectTime  !=  pMem->stat.tSelectTime  )  
			{
				pTransferVideoData->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;

				_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tSelectTime changed."  ),  tHintBuf  );

				//
				//pFrom->video.tv_recvd.uiTranNo_openAvDev  =  pTransferVideoData->uiTranNo_openAvDev;
				pFrom->video.tSelectTime  =  (  time_t  )pMem->stat.tSelectTime;
				pFrom->video.dwTickCnt_selectTime  =  curTickCnt;
				pFrom->video.usCnt_pkts  =  1;
				//		
				}
			else  {
				  if  (  pFrom->video.dwTickCnt_selectTime  !=  curTickCnt  )  {
					  pTransferVideoData->tmpInternal.result.fFps  =  (  float  )(  pFrom->video.usCnt_pkts  *  1000.  /  (  curTickCnt  -  pFrom->video.dwTickCnt_selectTime  )  );
				  }

				  pTransferVideoData->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;
			}		
			pTransferVideoData->tmpInternal.result.tSelectTime  =  pFrom->video.tSelectTime;	//  ½«ÕâÐ©·¢»Ø¡£2008/12/05
			pTransferVideoData->tmpInternal.result.usCnt_pkts  =  pFrom->video.usCnt_pkts;

			//
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s, %I64u, %d, recvd.pkts %d, expected %d"  ),  tHintBuf,  pFrom->idInfo.ui64Id,  pFrom->video.tv_recvd.uiTranNo_openAvDev,  (  long  )pFrom->video.usCnt_pkts,  (  long  )pMem->stat.usCnt_pkts  );
			//
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s, recvd.fps %.2f, expected %d"  ),  tHintBuf,  pTransferVideoData->tmpInternal.result.fFps,  (  long  )pMem->stat.usFps  );
			//
			if  (  pMem->stat.usCnt_pkts  ==  (  unsigned  short  )pFrom->video.usCnt_pkts  )  {
					  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s. ok."  ),  tHintBuf  );
					  }			  
				  else  {
						_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s err: "  ),  tHintBuf  );
				  }			  

			//		
			pTransferVideoData->tmpInternal.result.usDiff_pkts  =  pMem->stat.usCnt_pkts  -  pFrom->video.usCnt_pkts;

		//
		}
	}

	//
	BOOL  bOutputV  =  FALSE;
	if  (  pTask->ucbVideoConferenceStarter  )  {
		if  (  !pTask->confMosaicMaker.bExists_confMosaic  )  bOutputV  =  TRUE;
		}
	else  {
		  if  (  !pTask->doProxy.bExists_avProxy  )  bOutputV  =  TRUE;
	}

	//
	if  (  bOutputV  )  {
		//  2014/11/11
		if  (  dispatch_outputConfVideo(  pTask,  pMsgTask,  pTransferVideoData,  &pFrom->idInfo,  pFrom->video.tv_recvd.uiTranNo_openAvDev  )  )  {
			goto  errLabel;
		}
	}


	//  2011/12/08
	if  (  pDebugPkt->dwTickCnt_start  )  {
		pDebugPkt->usOutputInMs  =  GetTickCount(  )  -  pDebugPkt->dwTickCnt_start;
	}

	//  2014/11/26
	if  (  pFrom->idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
		#ifdef  __DEBUG__
				//  traceLog((TCHAR*)  _T(  "dispatchV: my pkt, skipped"  )  );
		#endif
		iErr  =  0;  goto  errLabel;
	}

	//
#if  10
	QY_TRANSFORM  *  pTransform  =  MACRO_getTransform(  *pTask,  index_activeMems_from  );
	if  (  pTransform  )  {
		//
		#if  0
			q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->video.q2  );
		#else
			q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->v_preTransThread.q2  );
		#endif
	}
#endif
	 

	iErr  =  0;  

errLabel:

	//  if  (  pData_allocated  )  free(  pData_allocated  );

	if  (  !iErr  )  {		
		mySendAvResp(  pProcInfo,  pMsgTask,  pMsgBuf  );		
	}

	if  (  iErr  ||  tHintBuf[0]  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "tn %d, %s. %s"  ),  pMsgTask->uiTranNo,  (  iErr  ?  _T(  "failed."  )  :  _T(  "OK"  )  ),  tHintBuf  );
	
	return  iErr;

}
#endif

//
  int  dispatchTaskVideo(  QIS_DISPATCH  *  pDispatch,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_VIDEO_DATA  *  pTransferVideoData,  int  index_pMems_from,  int  index_activeMems_from,  MIS_MSGU  *  pMsgBuf  )
{
	int						iErr				=	-1;

	MC_VAR_isCli			*	pProcInfo			=	(  MC_VAR_isCli  *  )pDispatch->pProcInfo;  
	MSGR_ADDR			*	pAddr				=	pDispatch->pAddr_logicalPeer;
	int						iTaskId				=	pDispatch->iTaskId;
	AV_TRAN_INFO		*	pTranInfo			=	(  AV_TRAN_INFO  *  )pDispatch->pTranInfo;
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pDispatch->pTask;

	QY_MC				*	pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;
	MIS_CNT				*	pMisCnt				=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	int						tmpiRet				=	0;
	//  QY_WMBUF_COMM			wmBuf;
	char					timeBuf[32]			=	"";
	TCHAR					tHintBuf[256]		=	_T(  ""  );
	//
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo ,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	//
	/*
	if  (  pTask->ucbVideoConferenceStarter  )  {
		if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  return  -1;
	}
	else  {
		int ii  =  0;
	}
	*/
	if  (  !pTask->ucbVideoConferenceStarter  )  {
		return  -1;
	}
	if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  return  -1;
	DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[index_activeMems_from];

#if  0
	TASK_AV_FROM		*	pFrom				=	NULL;
	pFrom  =  getTaskAvFrom(  pTask,  index_pMems_from,  _T(  "dispatchTaskVideo"  )  );
	if  (  !pFrom  )  return  -1;
#endif
	//
	int						i;
	DWORD					curTickCnt			=	GetTickCount(  );	

	TCHAR					where_showInfo[32]	=	_T(  ""  );		_sntprintf(  where_showInfo,  mycountof(  where_showInfo  ),  _T(  "dispatchV %d"  ),  index_activeMems_from  );

	//  BYTE				*	pData_allocated		=	NULL;

	if  (  !pAddr  )  return  -1;

	//  2011/12/08
	DEBUG_myDRAW_VIDEO_DATA	*	pDebugPkt  =  &pMsgTask->data.route.debugInfo.debug_myDRAW_VIDEO_DATA;
	if  (  pDebugPkt->dwTickCnt_start  )  {
		pDebugPkt->usToDispatchInMs  =  curTickCnt  -  pDebugPkt->dwTickCnt_start;
	}

	//
#if  0
	if  (  pMsgTask->tStartTime  <  pFrom->tStartTime_task  )  {
		_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tStartTime < tStartTime_task. skipped."  ),  tHintBuf  );  goto  errLabel;
	}
#endif
	if  (  pMsgTask->dwTickCnt_start  )  {	//  2009/03/22
		int  iElapse  =  curTickCnt  -  pMsgTask->dwTickCnt_start;
		if  (  iElapse  >  pProcInfo->cfg.policy.usTimeoutInMsToSwitch  )  {
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%I64u,  %dms elapsed, start %u, msg skipped"  ),  pActiveMem_from->avStream.idInfo.ui64Id,  iElapse,  pMsgTask->dwTickCnt_start  );
			goto  errLabel;
		}
	}

		

	//  check
	if  (  pMsgTask->data.route.idInfo_from.ui64Id  !=  pActiveMem_from->avStream.idInfo.ui64Id
		||  pTransferVideoData->uiTranNo_openAvDev  !=  pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev  )  
	{
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "procTaskVideo: idInfo_from %I64u, videoData.uiTranNo %d !=  pFrom %I64u, %d",  pMsgTask->data.route.idInfo_from.ui64Id,  pTransferVideoData->uiTranNo_openAvDev,  pActiveMem_from->avStream.idInfo.ui64Id,  pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev  );  
		#endif
		goto  errLabel;
	}

	//  2017/09/04
#ifdef  __DEBUG__
		if  (  0  )  {
			TCHAR  tBuf[128];
			//_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "transferVideo.tSelectTime %I64u, uiLen %d, usCnt %d, iVal_dbg %d"  ),  pTransferVideoData->stat.tSelectTime,  pTransferVideoData->uiLen,  (  int  )pTransferVideoData->usCnt,  pTransferVideoData->stat.iVal_dbg  );
			showInfo_open0(  0,  _T(  "dispatchVideo"  ),  tBuf  );
		}
#endif

	//	
	//
#if  0
	for  (  i  =  0;  i  <  pTransferVideoData->usCnt;  i  ++  )  {
		 TRANSFER_VIDEO_dataMemHead  *  pMem  =  &pTransferVideoData->mems[i];		
		 //
		 pFrom->video.usCnt_pkts  ++  ;
		 if  (  pMem->stat.tSelectTime  )  {
			if  (  //pFrom->video.tv_recvd.uiTranNo_openAvDev  !=  pTransferVideoData->uiTranNo_openAvDev  ||  
				!pFrom->video.tSelectTime  ||  pFrom->video.tSelectTime  !=  pMem->stat.tSelectTime  )  
			{
				pTransferVideoData->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;

				_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tSelectTime changed."  ),  tHintBuf  );

				//
				//pFrom->video.tv_recvd.uiTranNo_openAvDev  =  pTransferVideoData->uiTranNo_openAvDev;
				pFrom->video.tSelectTime  =  (  time_t  )pMem->stat.tSelectTime;
				pFrom->video.dwTickCnt_selectTime  =  curTickCnt;
				pFrom->video.usCnt_pkts  =  1;
				//		
				}
			else  {
				  if  (  pFrom->video.dwTickCnt_selectTime  !=  curTickCnt  )  {
					  pTransferVideoData->tmpInternal.result.fFps  =  (  float  )(  pFrom->video.usCnt_pkts  *  1000.  /  (  curTickCnt  -  pFrom->video.dwTickCnt_selectTime  )  );
				  }

				  pTransferVideoData->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;
			}		
			pTransferVideoData->tmpInternal.result.tSelectTime  =  pFrom->video.tSelectTime;	//  ½«ÕâÐ©·¢»Ø¡£2008/12/05
			pTransferVideoData->tmpInternal.result.usCnt_pkts  =  pFrom->video.usCnt_pkts;

			//
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s, %I64u, %d, recvd.pkts %d, expected %d"  ),  tHintBuf,  pFrom->idInfo.ui64Id,  pFrom->video.tv_recvd.uiTranNo_openAvDev,  (  long  )pFrom->video.usCnt_pkts,  (  long  )pMem->stat.usCnt_pkts  );
			//
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s, recvd.fps %.2f, expected %d"  ),  tHintBuf,  pTransferVideoData->tmpInternal.result.fFps,  (  long  )pMem->stat.usFps  );
			//
			if  (  pMem->stat.usCnt_pkts  ==  (  unsigned  short  )pFrom->video.usCnt_pkts  )  {
					  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s. ok."  ),  tHintBuf  );
					  }			  
				  else  {
						_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s err: "  ),  tHintBuf  );
				  }			  

			//		
			pTransferVideoData->tmpInternal.result.usDiff_pkts  =  pMem->stat.usCnt_pkts  -  pFrom->video.usCnt_pkts;

		//
		}
	}
#endif

	//
	BOOL  bOutputV; bOutputV = FALSE;
	if  (  pTask->ucbVideoConferenceStarter  )  {
		if  (  !pTask->confMosaicMaker.bExists_confMosaic  )  bOutputV  =  TRUE;
		}
	else  {
		  if  (  !pTask->doProxy.bExists_avProxy  )  bOutputV  =  TRUE;
	}

	//
	if  (  bOutputV  )  {
		//  2014/11/11
		if  (  dispatch_outputConfVideo(  pTask,  pMsgTask,  pTransferVideoData,  &pActiveMem_from->avStream.idInfo,  pTranInfo->video.uiTranNo_openAvDev  )  )  {
			goto  errLabel;
		}
	}


	//  2011/12/08
	if  (  pDebugPkt->dwTickCnt_start  )  {
		pDebugPkt->usOutputInMs  =  GetTickCount(  )  -  pDebugPkt->dwTickCnt_start;
	}

	//  2014/11/26
	if  (  pActiveMem_from->avStream.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
		#ifdef  __DEBUG__
				//  traceLog((TCHAR*)  _T(  "dispatchV: my pkt, skipped"  )  );
		#endif
		iErr  =  0;  goto  errLabel;
	}

	//
#if  10
	QY_TRANSFORM* pTransform; pTransform = MACRO_getTransform(*pTask, index_activeMems_from);
	if  (  pTransform  )  {
		//
		#if  0
			q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->video.q2  );
		#else
			q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->v_preTransThread.q2,  _T(  "dispatchTaskVideo"  ));
		#endif
	}
#endif
	 

	iErr  =  0;  

errLabel:

	//  if  (  pData_allocated  )  free(  pData_allocated  );

	if  (  !iErr  )  {		
		mySendAvResp(  pProcInfo,  pMsgTask,  pMsgBuf  );		
	}

	if  (  iErr  ||  tHintBuf[0]  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "tn %d, %s. %s"  ),  pMsgTask->uiTranNo,  (  iErr  ?  _T(  "failed."  )  :  _T(  "OK"  )  ),  tHintBuf  );
	
	return  iErr;

}




 //  2011/12/08
  extern "C" DWORD WINAPI mcThreadProc_dispatchVideo( LPVOID lpParameter )
{
	 QIS_DISPATCH					*	pDispatch					=	(  QIS_DISPATCH  *  )lpParameter;
	 if  (  !pDispatch  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo					=	(  MC_VAR_isCli  *  )pDispatch->pProcInfo;
	 if (  !pProcInfo  )  return  -1;	 
	 PROC_TASK_AV					*	pTask						=	(  PROC_TASK_AV  *  )pDispatch->pTask;
	 if  (  !pTask  )  return  -1;
	 QIS_DISPATCH_procInfo			*	pDispatchVideo				=	&pDispatch->video;

	 QY_MC							*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;
	 DYN_LIB_DX						*	pDynLib						=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	 //  int								i;

	 CQyMalloc							mallocObj_msgs;
	 MIS_MSGU						*	msgs							=	NULL;
	 //  unsigned  int						len;

	 MIS_MSGU						*	pMsgs[CONST_pMsgs_dispatchVideo];
	 int								msgLens[CONST_pMsgs_dispatchVideo];

	 int								maxMsgs							=	CONST_pMsgs_dispatchVideo;			//  一次最多处理的包数。
	 int								nMsgs;
	 int								i;

	 //
	 IM_CONTENTU					*	pContent						=	NULL;

	 #define		DEFAULT_dwToInMs		5000
	 DWORD								dwToInMs						=	DEFAULT_dwToInMs;

	 DWORD								dwTickCnt_lastVideoData			=	GetTickCount(  );;						// 

	 CQyMalloc							mallocObj_pMsgBuf;
	 MIS_MSGU						*	pMsgBuf							=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;

	 #ifdef  __DEBUG__
			 traceLogA(  (char*)  "mcThreadProc_dispatchVideo enters"  );
	 #endif
	 /*
	 for  (  i  =  0;  i  <  mycountof(  pTransformVideo->hEvents  );  i  ++  )  {
		  pTransformVideo->hEvents[i] = CreateEvent( NULL, FALSE, FALSE, NULL );
		  if ( NULL == pTransformVideo->hEvents[i] ) goto  errLabel;
	 }
	 */

	 pDispatchVideo->bRunning  =  TRUE;
	 //  memset(  &pTransformVideo->m_var,  0,  sizeof(  pTransformVideo->m_var  )  );

#ifdef  __DEBUG__
		//traceLog((TCHAR*)  _T(  "Note: 这里最好能根据情况，将maxMsgs自动调整，对每个dispatch,分配10个misMsgU, 是很浪费的"  )  );
#endif

	
	 if  (  !(  msgs  =  (  MIS_MSGU  *  )mallocObj_msgs.mallocf(  CONST_iAllocType_longTimeMsg,  maxMsgs  *  sizeof(  MIS_MSGU  )  )  )  )  goto  errLabel;
	 for  (  i  =  0;  i  <  maxMsgs;  i  ++  )  {
		  pMsgs[i]  =  &msgs[i];
	 }
	 
	 //  2014/11/21
	 BOOL  bNeeded; bNeeded = FALSE;
	 //
	 if  (  pTask->ucbVideoConferenceStarter  )  bNeeded  =  TRUE;
	 if  (  pTask->doProxy.bExists_avProxy  )  bNeeded  =  TRUE;
	 //
	 if  (  !bNeeded  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "dispatchVideo failed. not videoConferenceStarter"  );
		 #endif
		 showInfo_open0(  0,  0,  _T(  "dispatchV failed, no needed"  )  );
		 goto  errLabel;
	 }

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s starts"  ),  pDispatchVideo->q2.cfg.name  );
	
	 for  (  ;  !pDispatchVideo->bQuit;  )  {
		  
		  if  (  !dwToInMs  )  {			  
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: mcThreadProc_dispatchVideo: dwToInMs %d"  ),  dwToInMs  );
			  dwToInMs  =  DEFAULT_dwToInMs;
		  }

		  DWORD  dwTickCnt0  =  GetTickCount(  );
		  DWORD  dwTickCnt;
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(
			  				 pDispatchVideo->q2.cfg.usCnt_hEvents,		// mycountof(  pTransformVideo->hEvents  ),		// Number of events.
							 pDispatchVideo->q2.hEvents,				// Location of handles.
                             FALSE,										// Wait for all?
                             dwToInMs,									// How long to wait?
                             0  );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  goto  errLabel;
	      //
		  dwTickCnt =   GetTickCount(  );

		  if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
			  dwEvt -= WAIT_OBJECT_0;
			  switch  (  dwEvt  )  {
					  case  0:
						     dwTickCnt_lastVideoData  =  dwTickCnt;		//  audio data received
							 break;
					  case  1:
						     traceLogA(  (char*)  "dispatchVideo: event 1."  );
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
		  }


		  for  (  ;  !pDispatchVideo->bQuit;  )  {

			   //  2011/12/06
			   if  (  isQ2Empty(  &pDispatchVideo->q2  )  )  break;

			   for  (  i  =  0;  i  <  maxMsgs;  i  ++  )  {
				    msgLens[i]  =  sizeof(  msgs[0]  );
			   }
			   nMsgs  =  maxMsgs;
			   //  len  =  sizeof(  pMsg[0]  );
			   {
				   CQyQ2Help	q2Help;			  
				   if  (  qGetMsgs(  q2Help.getQ_toGetMsg(  &pDispatchVideo->q2,  _T(  "threadProc_dispatchV")), (void**)pMsgs, (unsigned  int*)msgLens, (unsigned  int*)&nMsgs))  break;
			   }
			   if  (  !nMsgs  )  break;

			   for  (  i  =  0;  i  <  nMsgs;  i  ++  )  {
				    memset(  (  (  char  *  )(  pMsgs[i]  )  )  +  msgLens[i],  0,  min(  256,  sizeof(  msgs[0]  )  -  msgLens[i]  )  );			   
			   }
   			   #ifdef  __DEBUG__
					   //  traceLog((TCHAR*)  _T(  "dispatchV: nMsgs %d"  ),  nMsgs  );
					   //
			   #endif

			   
			   //
			   for  (  i  =  0;  i  <  nMsgs;  i  ++  )  {
					    //  MIS_MSGU  *  pMsg  =  pMsgs[i];
					    MIS_MSGU  *  pMsg  =  (  MIS_MSGU  *  )pMsgs[i];
						if  (  !pMsg  )  break;
			   
						switch  (  pMsg->uiType  )  {
					            case  CONST_misMsgType_task:
									  pContent		=	(  IM_CONTENTU  *  )pMsg->task.data.buf;
									  switch  (  pContent->uiType  )  {
											  case  CONST_imCommType_transferVideoData:
												    #ifdef  __DEBUG__
															//  traceLogA(  (char*)  "transferVideoData: here"  );
													#endif
												    if  (  pDispatch->index_activeMems_from  !=  pContent->transferVideoData.tmpInternal.param.index_activeMems_from  )  {
														#ifdef  __DEBUG__
																traceLog((TCHAR*)  _T(  "dispatchVideo err, index_activeMems_from not matched"  )  );
														#endif
														break;
													}
										   
													//
												    dispatchTaskVideo(  pDispatch,  &pMsg->task,  &pContent->transferVideoData,  pContent->transferVideoData.tmpInternal.param.index_pMems_from,  pContent->transferVideoData.tmpInternal.param.index_activeMems_from,  pMsgBuf  );
													
												    break;
											  default:
													  #ifdef  __DEBUG__
		  													  traceLogA(  (char*)  "mcThreadProc_dispatchVideo: unknown uiContentType %d",  pContent->uiType  );
													  #endif
													  break;
									  }									 
									  break;
								default:
									   break;		
						}			   
			   }

			   //
			   continue;
			   
		  }

	 }

errLabel:

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s ends."  ),  pDispatchVideo->q2.cfg.name  );
	 

	 pDispatchVideo->bRunning  =  FALSE;

	 #ifdef  __DEBUG__
			 traceLogA(  (char*)  "mcThreadProc_dispatchVideo %S leaves",  pDispatchVideo->q2.cfg.name  );
	 #endif

	return  0;
}
