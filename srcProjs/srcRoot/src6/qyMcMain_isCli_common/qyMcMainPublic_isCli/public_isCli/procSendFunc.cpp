

#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcAcm.h"
#include	"qyVk.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"
#include	"qyOpenShellCommon.h"
#include	"dlgTalkProc.h"

#include	"isCliHelpPublic.h"
#include	"qmcTaskInfo.h"
#include	"dynFuncs.h"




//
//int  procSendAvInfoFunc(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType,  VIDEO_CONFERENCE_CFG  *  pVideoConferenceCfg,  AV_COMPRESSOR_CFG  *  pAvCompressor_conf,  QMC_mosaic_maker  *  pMosaic,  COMPRESS_VIDEO  *  pCompressVideo,  COMPRESS_AUDIO  *  pCompressAudio,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  TALKER_dynBmp  *  pTalkerDynBmp,  QY_MESSENGER_ID  *  p_content_idInfo_logicalPeer,  unsigned  int  uiTranNo_avTask_starter,  TASK_av_props  *  pTaskAvProps,  int  *  piTaskId,  MSGR_ADDR  *  pAddr,  O_sendAvInfo_taskInfo  *  pOst  );
int  procSendAvInfoFunc(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType,  VIDEO_CONFERENCE_CFG  *  pVideoConferenceCfg,  TALKER_policy  *  pTalkerPolicy, PARAM_startAvCall  *  pParam,  AV_COMPRESSOR_CFG  *  pAvCompressor_conf,  QMC_mosaic_maker  *  pMosaic,  COMPRESS_VIDEO  *  pCompressVideo,  COMPRESS_AUDIO  *  pCompressAudio,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  TALKER_dynBmp  *  pTalkerDynBmp,  QY_MESSENGER_ID  *  p_content_idInfo_logicalPeer,  unsigned  int  uiTranNo_avTask_starter,  TASK_av_props  *  pTaskAvProps,  int  *  piTaskId,  MSGR_ADDR  *  pAddr,  P_sendAvInfo_taskInfo  *  pPst  );


//
__declspec(  dllexport  )  int  procSendAvInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType, PARAM_startAvCall* pParam,  COMPRESS_VIDEO  *  pCompressVideo,  COMPRESS_AUDIO  *  pCompressAudio,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  TALKER_dynBmp  *  pTalkerDynBmp,  QY_MESSENGER_ID  *  p_content_idInfo_logicalPeer,  int  *  piTaskId,  MSGR_ADDR  *  pAddr,  P_sendAvInfo_taskInfo  *  pOst  )
{
	unsigned  int  uiTranNo_avTask_starter  =  0;
	//
	TASK_av_props  *  pTaskAvProps  =  NULL;

	//  
	return  procSendAvInfoFunc(  pMisCnt,  hWnd_task,  bDlgTalk,  uiTaskType,  NULL,  NULL,  pParam,  NULL,  NULL,  pCompressVideo,  pCompressAudio,  iIndex_sharedObj,  iIndex_sharedObjUsr,  pTalkerDynBmp,  p_content_idInfo_logicalPeer,  uiTranNo_avTask_starter,  pTaskAvProps,  piTaskId,  pAddr,  pOst  );
}


//  2015/03/11
__declspec(  dllexport  )  int  procSendAvInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType,  COMPRESS_VIDEO  *  pCompressVideo,  COMPRESS_AUDIO  *  pCompressAudio,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  TALKER_dynBmp  *  pTalkerDynBmp,  QY_MESSENGER_ID  *  p_content_idInfo_logicalPeer,  TASK_av_props  *  pTaskAvProps,  int  *  piTaskId,  MSGR_ADDR  *  pAddr  )
{
	unsigned  int  uiTranNo_avTask_starter  =  0;
	//
	//TASK_av_props  *  pTaskAvProps  =  NULL;
	P_sendAvInfo_taskInfo  *  pOst  =  NULL;

	//  
	return  procSendAvInfoFunc(  pMisCnt,  hWnd_task,  bDlgTalk,  uiTaskType,  NULL,  NULL,  NULL,  NULL,  NULL,  pCompressVideo,  pCompressAudio,  iIndex_sharedObj,  iIndex_sharedObjUsr,  pTalkerDynBmp,  p_content_idInfo_logicalPeer,  uiTranNo_avTask_starter,  pTaskAvProps,  piTaskId,  pAddr,  pOst  );
}



//
__declspec(  dllexport  )  int  procSendAvInfo_conf(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType,  VIDEO_CONFERENCE_CFG  *  pVideoConferenceCfg,  TALKER_policy  *  pTalkerPolicy, PARAM_startAvCall  *  pParam,  AV_COMPRESSOR_CFG  *  pAvCompressor_conf,  QMC_mosaic_maker  *  pMosaic,  COMPRESS_VIDEO  *  pCompressVideo,  COMPRESS_AUDIO  *  pCompressAudio,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  TALKER_dynBmp  *  pTalkerDynBmp,  QY_MESSENGER_ID  *  p_content_idInfo_logicalPeer,  int  *  piTaskId,  MSGR_ADDR  *  pAddr,  P_sendAvInfo_taskInfo  *  pOst  )
{
	unsigned  int  uiTranNo_avTask_starter  =  0;
	//
	TASK_av_props  *  pTaskAvProps  =  NULL;

	return  procSendAvInfoFunc(  pMisCnt,  hWnd_task,  bDlgTalk,  uiTaskType,  pVideoConferenceCfg,  pTalkerPolicy,  pParam,  pAvCompressor_conf,  pMosaic,  pCompressVideo,  pCompressAudio,  iIndex_sharedObj,  iIndex_sharedObjUsr,  pTalkerDynBmp,  p_content_idInfo_logicalPeer,  uiTranNo_avTask_starter,  pTaskAvProps,  piTaskId,  pAddr,  pOst  );
}

// 2014/11/22
__declspec(  dllexport  )  int  procSendAvInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType,  COMPRESS_VIDEO  *  pCompressVideo,  COMPRESS_AUDIO  *  pCompressAudio,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  TALKER_dynBmp  *  pTalkerDynBmp,  QY_MESSENGER_ID  *  p_content_idInfo_logicalPeer,  unsigned  int  uiTranNo_avTask_starter,  int  *  piTaskId,  MSGR_ADDR  *  pAddr  )
{
	//
	TASK_av_props  *  pTaskAvProps  =  NULL;
	P_sendAvInfo_taskInfo  *  pOst  =  NULL;

	//  
	return  procSendAvInfoFunc(  pMisCnt,  hWnd_task,  bDlgTalk,  uiTaskType,  NULL,  NULL,  NULL,  NULL,  NULL,  pCompressVideo,  pCompressAudio,  iIndex_sharedObj,  iIndex_sharedObjUsr,  pTalkerDynBmp,  p_content_idInfo_logicalPeer,  uiTranNo_avTask_starter,  pTaskAvProps,  piTaskId,  pAddr,  pOst  );
}



//
__declspec(  dllexport  )  int  getMosaicTranInfo(  SHARE_dyn_bmp  *  pShareDynBmp,  MOSAIC_TRAN_INFO  *  p  )
{	
	int  iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	p->resObj.uiObjType  =  pShareDynBmp->resObj.uiObjType;
	p->resObj.usIndex_obj  =  pShareDynBmp->resObj.usIndex_obj;			  
	//			  
	if  (  !pShareDynBmp->var.ucbLocalVideoOpen  )  goto  errLabel;
	QY_SHARED_OBJ* pSharedObj; pSharedObj = getSharedObjByIndex(pProcInfo, pShareDynBmp->var.iIndex_sharedObj);
	if  (  !pSharedObj  )  goto  errLabel;
	int  index_capBmp; index_capBmp = pSharedObj->iIndex_capBmp;
	CAP_procInfo_bmpU* pCapBmp; pCapBmp = getCapBmpBySth(pProcInfo, index_capBmp, 0);
	if  (  !pCapBmp  )  goto  errLabel;
	COMPRESS_VIDEO* pCompressVideo; pCompressVideo = &pCapBmp->common.compressVideo;

	memcpy(  &p->video.compressor,  &pCompressVideo->compressor,  sizeof(  p->video.compressor  )  );
	SHARED_OBJ_USR* pSharedObjUsr; pSharedObjUsr = getSharedObjUsr(pSharedObj, pSharedObj->iIndex_curUsr);
	if  (  !pSharedObjUsr  )  goto  errLabel;
	p->video.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;
	//
	memcpy(  &p->video.vh_compress,  &pCompressVideo->vh_compress,  sizeof(  p->video.vh_compress  )  );		
	memcpy(  &p->video.vh_stream,  &pCompressVideo->vh_stream,  sizeof(  p->video.vh_stream  )  );		//  2014/03/30			
	//
	memcpy(  &p->video.vh_decompress,  &pCompressVideo->vh_decompress,  sizeof(  p->video.vh_decompress  )  );


	iErr  =  0;
errLabel:
			  
	return  iErr;
}


//


//
//  2014/11/09
//
int  procSendAvInfoFunc(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType,  VIDEO_CONFERENCE_CFG  *  pVideoConferenceCfg,  TALKER_policy  *  pTalkerPolicy, PARAM_startAvCall  *  pParam,  AV_COMPRESSOR_CFG  *  pAvCompressor_conf,  QMC_mosaic_maker  *  pMosaic,  COMPRESS_VIDEO  *  pCompressVideo,  COMPRESS_AUDIO  *  pCompressAudio,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  TALKER_dynBmp  *  pTalkerDynBmp,  QY_MESSENGER_ID  *  p_content_idInfo_logicalPeer,  unsigned  int  uiTranNo_avTask_starter,  TASK_av_props  *  pTaskAvProps,  int  *  piTaskId,  MSGR_ADDR  *  pAddr,  P_sendAvInfo_taskInfo  *  pPst  )
{
	int					iErr					=	-1;
	MC_VAR_isCli	*	pProcInfo				=	NULL;  
	QY_MC			*	pQyMc					=	NULL;
	TCHAR				tBuf[256]				=	_T(  ""  );
	CQyMalloc			mallocObj;
	QY_SHARED_OBJ  *	pSharedObj				=	NULL;
	//  int				iIndex_sharedObjUsr		=	0;
	SHARED_OBJ_USR	*	pSharedObjUsr			=	NULL;

	BOOL				ucbSendLocalAv			=	FALSE;

	//  2013/02/11
	BOOL				bReSend_viewDynBmp		=	FALSE;
	DYN_BMP_RULE	*	pDynBmp					=	NULL;

	//  2014/10/29
	int					iTaskId_suggested		=	0;

	//
	TALKER_dynBmp  *  pRuleU  =  (  TALKER_dynBmp  *  )pTalkerDynBmp;

	#ifdef  __DEBUG__
			traceLog(  (TCHAR*)_T(  "procSendAvInfo called"  )  );	
	#endif

	//
	if  (  !pMisCnt  )  return  -1;
	pProcInfo  =  QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;
	
	//  2017/08/02
	unsigned  char  ucbVideoConference  =  FALSE;	
	//  2017/07/17
	unsigned  char  ucbAvConsole  =  FALSE;
	//  2017/08/25
	unsigned  short  usConfType  =  0;


	//  2016/03/13
	if  (  pPst  )  {
		//  2017/08/02
		ucbVideoConference  =  pPst->i.ucbVideoConference;
		//  2017/07/17
		ucbAvConsole  =  pPst->i.ucbAvConsole;
		//  2017/08/25
		usConfType  =  pPst->i.usConfType;
		//
		//
		memset(  &pPst->o,  0,  sizeof(  pPst->o  )  );
	}


	//  2013/02/11
	if  (  pRuleU  )  {
		if  (  pRuleU->uiType1  ==  CONST_talkerObjType_dynBmp  )  {
			pDynBmp  =  &pRuleU->dynBmpRule;
			//
			if  (  pRuleU->taskInfo.iTaskId  )  {
				if  (  uiTaskType  ==  CONST_imTaskType_viewDynBmp  )  {
					bReSend_viewDynBmp  =  TRUE;
				}
			}
		}
	}

	//
	int iIndex_taskInfo=-1;

	//  2014/10/29
	if  (  piTaskId  )  {
		if  (  *piTaskId  )  {
			iTaskId_suggested  =  *piTaskId;
		}
	}
	if  (  bReSend_viewDynBmp  )  {
		iTaskId_suggested  =  pRuleU->taskInfo.iTaskId;
	}

		//  2014/09/24
	if  (  !bReSend_viewDynBmp  )  {
		unsigned  int  uiTaskDataType  =  0;
		uiTaskDataType  =  CONST_taskDataType_conf;
		//
		iIndex_taskInfo  =  newTaskInfoIndex(  pProcInfo,  uiTaskDataType,  hWnd_task,  iTaskId_suggested, _T( "procSendAvInfoFunc"  )  );
		if  (  iIndex_taskInfo  <  0  )  {
			traceLogA((char*)"procSendAvInfoFunc faile, newTaskInfoIndex failed" );
			goto  errLabel;
		}
	}
	QMC_TASK_INFO* pTaskInfo; pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, iIndex_taskInfo);
	if  (  pTaskInfo==NULL  )goto errLabel;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
	QMC_taskData_conf* pTc; pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;

	//  2023/01/24
	if (pTalkerPolicy) {
	}
	if  (  pParam  )  {
		pTc->ucb2Streams = pParam->ucb2Streams;
	}

	//
	switch  (  uiTaskType  )  {
		    case  CONST_imTaskType_transferAvInfo:
				  ucbSendLocalAv  =  TRUE;
				  break;
			default:
					break;
	}


	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  {
		if  (  uiTaskType  !=  CONST_imTaskType_viewDynBmp  )  goto  errLabel;
		}
	else  {		//  2010/09/04
		  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  iIndex_sharedObjUsr  );
		  if  (  !pSharedObjUsr  )  goto  errLabel;
		  //
		  if  (  pCompressAudio  &&  pCompressAudio->uiTranNo_openAvDev_org  )  {
			  pSharedObjUsr->uiTranNo_openAvDev_a  =  pCompressAudio->uiTranNo_openAvDev_org  +  iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
		  }
		  if  (  pCompressVideo  &&  pCompressVideo->uiTranNo_openAvDev_org  )  {	//  
			  pSharedObjUsr->uiTranNo_openAvDev_v  =  pCompressVideo->uiTranNo_openAvDev_org  +  iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
		  }
	}

	//  tStartTime, uiTranNo
	MACRO_prepareForTran(  );

	//  2013/02/13
	if  (  bReSend_viewDynBmp  )  {
		tStartTran  =  pRuleU->taskInfo.tStartTran;
		uiTranNo  =  pRuleU->taskInfo.uiTranNo;
	}

	//
	TASK_transferAv  task;
	memset(&task,0,sizeof(task));
	task.m_index_taskInfo=iIndex_taskInfo;

	//  
	MIS_MSG_TASK				*	pMsg;
	//if  (  !(  pMsg  =  (  MIS_MSG_TASK  *  )mallocObj.mallocf(  sizeof(  MIS_MSG_TASK  )  )  )  )  goto  errLabel;
	pMsg=&pTaskInfo->var.pTaskData->msgU.task;
	//
	//TRANSFER_AV_task			*	pContent  =  NULL;
	TRANSFER_AV_INFO* pContent_req; pContent_req = NULL;
	PROC_TASK_AV* pContent_myTask; pContent_myTask = &task.myTask;

	//
	unsigned  int					lenInBytes;
	IM_TASK_RCD						rcd;
	//
	MACRO_memset_misMsgTask(  pMsg  );
	pMsg->uiType  =  CONST_misMsgType_task;
	//
	pMsg->pMisCnt  =  pMisCnt;
	//
	pMsg->ucFlg  =  CONST_commFlg_routeTalkData;
	//
	pMsg->usCode  =  CONST_qyCmd_sendMedia;
	pMsg->tStartTime  =  tStartTran;
	pMsg->uiTranNo  =  uiTranNo;
	//
	if  (  sizeof(  TRANSFER_AV_INFO  )  >  sizeof(  pMsg->data.buf  )  )  goto  errLabel;
	pContent_req  =  (  TRANSFER_AV_INFO  *  )pMsg->data.buf;
	memset(  pContent_req,  0,  sizeof(  pContent_req[0]  )  );
	pContent_req->uiType  =  CONST_imCommType_transferAvInfo;
	//  2016/04/18
	pContent_req->tmp_usSubtype  =  CONST_transferAvInfo_subtype_task;
	//
	pContent_req->uiTaskType  =  uiTaskType;
	//
	if (pTalkerPolicy) {
		pContent_req->shareDevice_grp_index = pTalkerPolicy->shareDevice_grp_index;
	}

	//
	pContent_myTask->ucbSendLocalAv  =  ucbSendLocalAv;									//  2008/06/12
	pContent_myTask->iIndex_sharedObj  =  iIndex_sharedObj;
	//  2014/12/11
	pContent_myTask->iIndex_sharedObjUsr  =  iIndex_sharedObjUsr;							//  2014/12/11

	//  2018/09/08
	pContent_myTask->uiTaskType  =  uiTaskType;
	//
	pContent_myTask->ucbStarter  =  TRUE;												//  2010/08/31
	//  2014/09/23
	if  (  parse_qnmVerStr(  qnmVerStr(  pQyMc->iServiceId  ),  &pContent_req->ass.tranInfo.head.shClientVer,  NULL,  NULL  )  )  goto  errLabel;
	//
	if  (  !pVideoConferenceCfg  )  {
#if 0
		switch  (  uiTaskType  )  {
			    case  CONST_imTaskType_transferAvInfo:
					  //
					  pTc->videoConference.usMaxSpeakers  =  2;
					  //
					  pTc->videoConference.usCntLimit_activeMems_from  =  pTc->videoConference.usMaxSpeakers  +  MAX_resourceMems_taskAv_p2p;

					  //
					  pTc->videoConference.usCntLimit_mems_from  =  2;						//  2010/08/31

					  break;
				default:
						//
						pTc->videoConference.usCntLimit_activeMems_from  =  1;
						
						//
						pTc->videoConference.usCntLimit_mems_from  =  2;					//  2010/09/03

						break;
		}
#endif
		calc_conf_param(false, uiTaskType, &pTc->videoConference.usMaxSpeakers, &pTc->videoConference.usCntLimit_activeMems_from);
		pTc->videoConference.usCntLimit_mems_from = 2;
		//
		}
	else  {
		  memcpy(  &pContent_myTask->videoConferenceCfg,  pVideoConferenceCfg,  sizeof(  pVideoConferenceCfg[0]  )  );
		  //
		  pTc->videoConference.usMaxSpeakers  =  pContent_myTask->videoConferenceCfg.usMaxSpeakers;
		  //
		  //pTc->videoConference.usCntLimit_activeMems_from  =  pContent_myTask->videoConferenceCfg.usMaxSpeakers  +  MAX_mosaicMems_taskAv  +  MAX_resourceMems_taskAv_conf;
		  calc_conf_param(true, uiTaskType, &pTc->videoConference.usMaxSpeakers, &pTc->videoConference.usCntLimit_activeMems_from);
		  
		  //
		  pTc->videoConference.usCntLimit_mems_from  =  pContent_myTask->videoConferenceCfg.iRows  *  pContent_myTask->videoConferenceCfg.iCols;
		  		  
		  //
		  pContent_myTask->ucbVideoConference  =  TRUE;					//  2009/05/30
		  pContent_myTask->ucbVideoConferenceStarter  =  TRUE;
	}
	if  (  !pTc->videoConference.usCntLimit_activeMems_from  ||  pTc->videoConference.usCntLimit_activeMems_from  >  MAX_conf_activeMems  )  {
		showInfo_open0(  0,  0,  _T(  "procSendAvInfoFunc: usCntLimit_activeMems_from err"  )  );
		goto  errLabel;
	}
	if  (  !pTc->videoConference.usCntLimit_mems_from  ||  pTc->videoConference.usCntLimit_mems_from  >  MAX_mems_taskAv  )  {
		showInfo_open0(  0,  0,  _T(  "procSendAvInfoFunc: usCntLimit_mems_from err"  )  );
		goto  errLabel;
	}
	//  2017/08/02
	if  (  pContent_myTask->ucbVideoConference  !=  ucbVideoConference  )  {
		showInfo_open0(  0,  0,  _T(  "procSendAvInfoFunc: ucbVideoConference err"  )  );
		goto  errLabel;
	}

	//
	if  (  pAddr  )  {
		if  (  pAddr->uiObjType  ==  CONST_objType_imGrp  )  {									   
			pContent_req->bGrpTask  =  TRUE; //  2007/09/05, ¸³ÉÏ×é±êÊ¶									   
		}
	}

	//  2017/08/02
	pContent_req->confCfg.usMaxSpeakers  =  pContent_myTask->videoConferenceCfg.usMaxSpeakers;
	pContent_req->confCfg.ucbVideoConference  =  ucbVideoConference;
	//  2017/07/17
	//pContent_req->confCfg.ucbAvConsole  =  ucbAvConsole;
	//  2017/08/25
	pContent_req->confCfg.usConfType  =  usConfType;
	//
	if (pParam) {
		pContent_req->confCfg.conf.conf_ucb100k = pParam->talkerPolicy.conf_ucb100k;
		pContent_req->confCfg.conf.conf_ucAudioCompressors = pParam->talkerPolicy.conf_ucAudioCompressors;
	}

	//  2017/08/26
	if  (  pPst  )  {
		//
		pContent_req->confCfg.idInfo_initiator  =  pPst->i.idInfo_initiator;
		//
#if 0
		pContent_req->confCfg.hgInfo.ui64MeetingId_hg = pPst->i.hgInfo.ui64MeetingId_hg;	//  2023/04/04
		//
		pContent_req->confCfg.hgInfo.iMeetingType_hg = pPst->i.hgInfo.iMeetingType_hg;
#endif
		pContent_req->confCfg.hgInfo = pPst->i.hgInfo;
	}


	// audio
	if  (  !pContent_myTask->ucbVideoConferenceStarter  )  {
		if  (  pCompressVideo  &&  pCompressVideo->uiTranNo_openAvDev_org  )  {	//  ×Ô¼ºÃ»ÓÐÉãÏàÍ¶Ê±£¬ÕâÀïÊÇÓÃÀ´ÇëÇó¿´Ô¶³ÌµÄÊÓÆµÍ·
			if  (  !pSharedObjUsr  )  goto  errLabel;
			//  pContent->tranInfo.video.uiTranNo_openAvDev  =  pCompressVideo->uiTranNo_openAvDev  +  iIndex_sharedObjUsr;
			pContent_req->ass.tranInfo.video.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;

			//			
			//  safeStrnCpy(  pCompressVideo->compressor.fourccStr,  pContent->tranInfo.video.fourccStr,  mycountof(  pContent->tranInfo.video.fourccStr  )  );
			memcpy(  &pContent_req->ass.tranInfo.video.compressor,  &pCompressVideo->compressor,  sizeof(  pContent_req->ass.tranInfo.video.compressor  )  );

			memcpy(  &pContent_req->ass.tranInfo.video.vh_compress,  &pCompressVideo->vh_compress,  sizeof(  pContent_req->ass.tranInfo.video.vh_compress  )  );
			memcpy(  &pContent_req->ass.tranInfo.video.vh_stream,  &pCompressVideo->vh_stream,  sizeof(  pContent_req->ass.tranInfo.video.vh_stream  )  );		//  2014/03/30
			//
			memcpy(  &pContent_req->ass.tranInfo.video.vh_decompress,  &pCompressVideo->vh_decompress,  sizeof(  pContent_req->ass.tranInfo.video.vh_decompress  )  );
		}

		if  (  pCompressAudio  &&  pCompressAudio->uiTranNo_openAvDev_org  )  {
			if  (  !pSharedObjUsr  )  goto  errLabel;
			//  pContent->tranInfo.audio.uiTranNo_openAvDev  =  pCompressAudio->uiTranNo_openAvDev  +  iIndex_sharedObjUsr;
			pContent_req->ass.tranInfo.audio.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_a;
			//
			//  memcpy(  &pContent->tranInfo.audio.wf_compress,  &pCompressAudio->policy.compressor.wf_compress,  sizeof(  pContent->tranInfo.audio.wf_compress  )  );
			//  memcpy(  &pContent->tranInfo.audio.wf_decompress,  &pCompressAudio->waveFormatEx,  sizeof(  pContent->tranInfo.audio.wf_decompress  )  );	//  2009/04/27
			memcpy(  &pContent_req->ass.tranInfo.audio.compressor,  &pCompressAudio->compressor,  sizeof(  pContent_req->ass.tranInfo.audio.compressor  )  );

			memcpy(  &pContent_req->ass.tranInfo.audio.ah_compress,  &pCompressAudio->ah_compress,  sizeof(  pContent_req->ass.tranInfo.audio.ah_compress  )  );
			memcpy(  &pContent_req->ass.tranInfo.audio.ah_stream,  &pCompressAudio->ah_stream,  sizeof(  pContent_req->ass.tranInfo.audio.ah_stream  )  );			//  2016/12/23
			//
			memcpy(  &pContent_req->ass.tranInfo.audio.ah_decompress,  &pCompressAudio->ah_decompress,  sizeof(  pContent_req->ass.tranInfo.audio.ah_decompress  )  );
		}

		if  (  pDynBmp  )  {		//  2009/09/07
			//
			#if  0
				pContent_req->viewDynBmp.resObj.uiObjType  =  pDynBmp->dynBmp.resObj.uiObjType;
				pContent_req->viewDynBmp.resObj.usIndex_obj  =  pDynBmp->dynBmp.resObj.usIndex_obj;
			#endif
			//  2016/07/24
			pContent_req->ass.resObj  =  pDynBmp->dynBmp.resObj;
			//
			//  2014/08/04
			pContent_req->viewDynBmp.ucbSaveVideo  =  pDynBmp->ucbSaveVideo;
		}

		//
		switch  (  uiTaskType  )  {
				case  CONST_imTaskType_viewDynBmp:
					  break;
				default:
					   //pTc->videoConference.activeMems_from[0].avStream.idInfo  =  pMisCnt->idInfo;		
					   //pTc->videoConference.activeMems_from[0].avStream.obj.tranInfo  =  pContent_req->tranInfo;
					   AV_stream_simple  ass  =  {0};
					   ass.tranInfo  =  pContent_req->ass.tranInfo;
					   addTo_activeMems_from(  pMisCnt,  &pMisCnt->idInfo,  &ass,  &pTc->videoConference  );
					   break;
		}

		}
	else  {
		  if  (  !pAvCompressor_conf  )  {
			  #ifdef  __DEBUG__
		  			  traceLogA(  (char*)"procSendAvInfo: pVideoCompressor_conf can't be null for a conference starter"  );
			  #endif
			  goto  errLabel;
		  }
#if  0
		  if  (  !pVideoCompressor  ||  !pAudioCompressor  )  {
			  #ifdef  __DEBUG__
					  traceLogA(  "procSendAvInfo: pVideoConferenceCompressor can't be null for a conference starter"  );
			  #endif
			  goto  errLabel;
		  }
#endif
		  //  2014/11/07
		  if  (  !pCompressAudio  ||  !pCompressVideo  )  {
			  #ifdef  __DEBUG__
					  traceLogA(  (char*)"procSendAvInfo: pVideoConferenceCompressor can't be null for a conference starter"  );
			  #endif
			  goto  errLabel;
		  }

		  //
		  //pContent_req->confCfg.usCntLimit_mems_from  =  pTc->videoConference.usCntLimit_mems_from;				//  2009/05/30
		  //pContent_req->confCfg.usCntLimit_activeMems_from  =  pTc->videoConference.usCntLimit_activeMems_from;	//  2010/06/31
		  //pContent_req->confCfg.usMaxSpeakers  =  pTc->videoConference.usMaxSpeakers;	//  2010/06/31

		  //  2009/04/19
		  pContent_req->confCfg.conf.usMaxFps_toShareBmp_conf  =  pAvCompressor_conf->video.common.usMaxFps_toShareBmp;	//  pProcInfo->cfg.policy.video.usFrames_perSecond_videoConference;
		  //  2014/08/15
		  pContent_req->confCfg.conf.iWidth_pic_conf  =  pAvCompressor_conf->video.common.iWidth_pic;
		  pContent_req->confCfg.conf.iHeight_pic_conf  =  pAvCompressor_conf->video.common.iHeight_pic;
		  //
		  //  2014/11/09
		  //pContent->confCfg.audioPlayCfg  =  pAvCompressor_conf->audio.playCfg;
		  //
		  //  2016/03/26
		  if  (  pTalkerPolicy  )  {

			  //
			  pContent_req->confCfg.conf.conf_iFourcc  =  pTalkerPolicy->conf_iFourcc;
			  pContent_req->confCfg.conf.conf_bitrateInKbps_ul = pTalkerPolicy->conf_bitrateInKbps_ul;
			  
			  //  2017/07/06
			  pContent_req->confCfg.conf.confCtrl.ucbConfCtrl_starter  =  pTalkerPolicy->ucbConfCtrl_starter;
			  
		  }

		  //
		  //  Note: 会议里的tranInfo起的是组优先策略的作用，不是发一个视频信息. 2014/11/13

		  //
		  pContent_req->ass.tranInfo.video.uiTranNo_openAvDev  =  getuiNextTranNo(  0,  0,  0  );	
		  //
#if  0
		  {   //  2014/11/09
			  VIDEO_COMPRESSOR_CFG  *  pVideoCompressor  =  &pCompressVideo->compressor;
			  //
			  memcpy(  &pContent->tranInfo.video.compressor,  pVideoCompressor,  sizeof(  pContent->tranInfo.video.compressor  )  );
		  }
#endif

		  //
		  pContent_req->ass.tranInfo.audio.uiTranNo_openAvDev  =  pContent_req->ass.tranInfo.video.uiTranNo_openAvDev;
		  //
#if  0
		  {   //  2014/11/09
			  AUDIO_COMPRESSOR_CFG  *  pAudioCompressor  =  &pCompressAudio->compressor;
			  //
			  memcpy(  &pContent->tranInfo.audio.compressor,  pAudioCompressor,  sizeof(  pContent->tranInfo.audio.compressor  )  );
			  //
			  memcpy(  &pContent->tranInfo.audio.ah_compress.wfx,  &pAudioCompressor->wf_compress,  sizeof(  pContent->tranInfo.audio.ah_compress.wfx  )  );
			  memcpy(  &pContent->tranInfo.audio.ah_decompress.wfx,  &pAudioCompressor->wf_decompress_default,  sizeof(  pContent->tranInfo.audio.ah_decompress.wfx  )  );		  
		  }
#endif
		  //  2014/11/13
		  AUDIO_PLAY_CFG  *  pAudioPlayCfg_conf  =  &pAvCompressor_conf->audio.playCfg;
		  pContent_req->ass.tranInfo.audio.compressor.playCfg  =  *pAudioPlayCfg_conf;
		  

		  //  2009/06/03
		  if  (  pMosaic  )  {
			  if  (  pMosaic->video.resObj.uiObjType  )  {
				  if  (  getMosaicTranInfo(  &pMosaic->video,  &pContent_req->confMosaicTranInfo_video  )  )  goto  errLabel;
			  }
			  if  (  pMosaic->resource.resObj.uiObjType  )  {
				  if  (  getMosaicTranInfo(  &pMosaic->resource,  &pContent_req->confMosaicTranInfo_resource  )  )  goto  errLabel;
			  }
		  }

	}
	//  2011/12/10

	//  2014/09/27
	if  (  p_content_idInfo_logicalPeer  )  {
		pContent_req->idInfo_logicalPeer.ui64Id  =  p_content_idInfo_logicalPeer->ui64Id;
	}
	//  2014/11/22
	pContent_req->uiTranNo_avTask_starter  =  uiTranNo_avTask_starter;

	//  2015/03/11
	if  (  pTaskAvProps  )  {
		memcpy(  &pContent_req->ass.tranInfo.taskAvProps,  pTaskAvProps,  sizeof(  pContent_req->ass.tranInfo.taskAvProps  )  );
	}

	//  
	pContent_myTask->mem0_from.idInfo.ui64Id  =  pMisCnt->idInfo.ui64Id;		
	pContent_myTask->mem0_from.tStartTime_task  =  tStartTran;
	//
	if  (  pCompressVideo  &&  pCompressVideo->uiTranNo_openAvDev_org  )  {
			//													 
		    if  (  !pSharedObjUsr  )  goto  errLabel;
			//  pContent_myTask->mem0_from.video.uiTranNo_openAvDev  =  pCompressVideo->uiTranNo_openAvDev  +  iIndex_sharedObjUsr;						//  
			pContent_myTask->mem0_from.video.tv_recvd.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;												//  
			//

			//  safeStrnCpy(  pCompressVideo->compressor.fourccStr,  pContent_myTask->mem0_from.video.fourccStr,  mycountof(  pContent_myTask->mem0_from.video.fourccStr  )  );
			memcpy(  &pContent_myTask->mem0_from.video.tv_recvd.compressor,  &pCompressVideo->compressor,  sizeof(  pContent_myTask->mem0_from.video.tv_recvd.compressor  )  );
			
			memcpy(  &pContent_myTask->mem0_from.video.tv_recvd.vh_compress,  &pCompressVideo->vh_compress,  sizeof(  pContent_myTask->mem0_from.video.tv_recvd.vh_compress  )  );
			//  
			if  (  bSupported_sendVhDec(  )  )  {
				memcpy(  &pContent_myTask->mem0_from.video.tv_recvd.vh_decompress.bih,  &pCompressVideo->vh_decompress,  sizeof(  pContent_myTask->mem0_from.video.tv_recvd.vh_decompress.bih  )  );
			}

			//  2014/02/25
			memcpy(  &pContent_myTask->mem0_from.video.tv_recvd.vh_stream,  &pCompressVideo->vh_stream,  sizeof(  pContent_myTask->mem0_from.video.tv_recvd.vh_stream  )  );
	}
	//	
	if  (  pCompressAudio  &&  pCompressAudio->uiTranNo_openAvDev_org  )  {
			if  (  !pSharedObjUsr  )  goto  errLabel;
			//  pContent_myTask->mem0_from.audio.uiTranNo_openAvDev  =  pCompressAudio->uiTranNo_openAvDev  +  iIndex_sharedObjUsr;
			pContent_myTask->mem0_from.audio.ta_recvd.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_a;
			//		
			//  memcpy(  &pContent_myTask->mem0_from.audio.wf_compress_recvd,  &pCompressAudio->policy.compressor.wf_compress,  sizeof(  pContent_myTask->mem0_from.audio.wf_compress_recvd  )  );
			//  memcpy(  &pContent_myTask->mem0_from.audio.wf_decompress_recvd,  &pCompressAudio->waveFormatEx,  sizeof(  pContent_myTask->mem0_from.audio.wf_decompress_recvd  )  );
			memcpy(  &pContent_myTask->mem0_from.audio.ta_recvd.compressor,  &pCompressAudio->compressor,  sizeof(  pContent_myTask->mem0_from.audio.ta_recvd.compressor  )  );
			memcpy(  &pContent_myTask->mem0_from.audio.ta_recvd.ah_compress,  &pCompressAudio->ah_compress,  sizeof(  pContent_myTask->mem0_from.audio.ta_recvd.ah_compress  )  );
			memcpy(  &pContent_myTask->mem0_from.audio.ta_recvd.ah_decompress,  &pCompressAudio->ah_decompress,  sizeof(  pContent_myTask->mem0_from.audio.ta_recvd.ah_decompress  )  );

			//  2016/12/23
			memcpy(  &pContent_myTask->mem0_from.audio.ta_recvd.ah_stream,  &pCompressAudio->ah_stream,  sizeof(  pContent_myTask->mem0_from.audio.ta_recvd.ah_stream  )  );
	}
	
	if  (  !pContent_myTask->ucbVideoConferenceStarter  )  {

		//  2012/01/27
		memcpy(  &pContent_myTask->audio.playCfg,  &pContent_req->ass.tranInfo.audio.compressor.playCfg,  sizeof(  pContent_myTask->audio.playCfg  )  );

		}
	else  {

		  //  2009/06/03		
		  memcpy(  &pContent_myTask->audio.playCfg,  &pContent_req->ass.tranInfo.audio.compressor.playCfg,  sizeof(  pContent_myTask->audio.playCfg  )  );

		  //  2009/06/04
		  pContent_myTask->video.usMaxFps_toShareBmp_conf  =  pContent_req->confCfg.conf.usMaxFps_toShareBmp_conf;
	}
	pContent_myTask->hWnd_task  =  hWnd_task;	//  2009/09/09
	//  2014/11/11
	if  (  pMosaic  )  {
		if  (  pMosaic->video.resObj.uiObjType  )  {
			pContent_myTask->confMosaicMaker.iIndex_sharedObj_video  =  pMosaic->video.var.iIndex_sharedObj;
			pContent_myTask->confMosaicMaker.iIndex_sharedObj_resource  =  pMosaic->resource.var.iIndex_sharedObj;
			//
			pContent_myTask->confMosaicMaker.bExists_confMosaic  =  TRUE;
		}
	}

	//  2007/07/18
	pMsg->uiTaskType  =  uiTaskType;
	//
	pMsg->idInfo_taskSender.ui64Id  =  pMisCnt->idInfo.ui64Id;
	if  (  pAddr  )  {
		pMsg->idInfo_taskReceiver.ui64Id  =  pAddr->idInfo.ui64Id;
		pMsg->addr_logicalPeer.idInfo.ui64Id  =  pAddr->idInfo.ui64Id;
	}
	if  (  p_content_idInfo_logicalPeer  &&  p_content_idInfo_logicalPeer->ui64Id  )  {		//  2014/11/22
		pMsg->addr_logicalPeer.idInfo.ui64Id  =  p_content_idInfo_logicalPeer->ui64Id;
	}
	//
	pMsg->iStatus  =  CONST_imTaskStatus_req;


	//  ÕâÀïµÄ¸³ÖµËÆºõÓ¦ÔÚ·¢ËÍÊ±Ê¹ÓÃ, 2007/07/24
	pMsg->data.route.idInfo_from.ui64Id  =  pMsg->idInfo_taskSender.ui64Id;
	pMsg->data.route.idInfo_to.ui64Id  =  pMsg->idInfo_taskReceiver.ui64Id;
	//

	lenInBytes  =  sizeof(  pContent_req[0]  );
	pMsg->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  lenInBytes;

	memset(  &rcd,  0,  sizeof(  rcd  )  );
	if  (  !msg2TaskRcd(  pMisCnt,  pMsg,  CONST_qyRc_unknown,  &rcd  )  )  goto  errLabel;
	
	{
		void	*	pDb	=	NULL;
		#ifndef  __NOTSUPPORT_DB__
				 CQnmDb		db;
				 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
				 pDb  =  db.m_pDbMem->pDb;
		#endif
		//
		if  (  storeTaskInDb(  pDb,  pQyMc->cfg.db.iDbType,  pMisCnt,  iTaskId_suggested,  &rcd,  FALSE  )  <  0  )  goto  errLabel;
	}

	//  2013/02/13
	if  (  iTaskId_suggested  )  {		//  2014/10/29
		if  (  rcd.id  !=  iTaskId_suggested  )  {
			#ifdef  __DEBUG__
					traceLog(  (TCHAR*)_T(  "procSendAvInfo failed, rcd.id != taskInfo.iTaskId"  )  );
			#endif
			goto  errLabel;
		}
	}
	//
	if  (  uiTaskType  ==  CONST_imTaskType_viewDynBmp  )  {
		if  (  pRuleU  &&  pRuleU->uiType1  ==  CONST_talkerObjType_dynBmp  )  {
			if  (  pRuleU->taskInfo.bNeedProgress  )  {
				startProgress(  &pQyMc->gui.progress,  uiTranNo  );
			}
		}
	}

	//
	pContent_myTask->iIndex_taskInfo=iIndex_taskInfo;
	
	//
	pMsg->iTaskId  =  rcd.id;
	pMsg->uiTaskMode_unused  =  rcd.uiMode;
	pMsg->uiChannelType  =  CONST_channelType_media;		//  2009/10/17

#if  0
	if  (  bDlgTalk  )  {
		CHelp_getDlgTalkVar	help_getDlgTalkVar;
		DLG_TALK_var  *  pm_var  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hWnd_task  );
		if  (  !pm_var  )  goto  errLabel;
		DLG_TALK_var	&	m_var	=	*pm_var;

		if  (  uiTaskType  !=  CONST_imTaskType_viewDynBmp  )  {	//  2014/09/26

			//
			if  (  dlgTalk_qPostMsg(  hWnd_task,  pMsg,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsg->lenInBytes  )  )  goto  errLabel;

			//  2016/02/27
			PARAM_PROC_ROW  param;
			memset(  &param,  0,  sizeof(  param  )  );
			param.bScrollIntoView  =  TRUE;
			if  (  dyn_tmpHandler_showMsg(  hWnd_task,  &param,  pMsg  )  )  goto  errLabel;

			//
			m_var.av.taskInfo.local_avStream.tranInfo.audio  =  pContent_myTask->mem0_from.audio.ta_recvd;
			m_var.av.taskInfo.local_avStream.tranInfo.video  =  pContent_myTask->mem0_from.video.tv_recvd;

		}
	}
#endif


	///////////////
	//

	//  2009/04/28
	if  (  pSharedObj  )  {
		if  (  !pSharedObjUsr  )  goto  errLabel;

		pSharedObjUsr->iTaskId  =  rcd.id;
		//
		if  (  pAddr  )  {
			//pSharedObjUsr->idInfo_to.ui64Id  =  pAddr->idInfo.ui64Id;			//  2010/09/02
			pSharedObjUsr->ucbVideoConferenceStarter  =  pContent_myTask->ucbVideoConferenceStarter;
			pSharedObjUsr->ucbVideoConference  =  pContent_myTask->ucbVideoConference;		//  2018/11/10
			//
			pTc->ucbNotSendData  =  (  ucbSendLocalAv  &&  pAddr->uiObjType  ==  CONST_objType_imGrp  );
		}
	}
	if  (  piTaskId  )  *piTaskId  =  rcd.id;

	//
					//
				if (0!=pProcInfo->processQ_media.qPostMsg(&task, sizeof(task)))
				{
					traceLogA((char*)"procMsgTask_mc_robot: 1. qPostMsg failed");
					goto errLabel;
				}
				if (task.myTask.ucbVideoConferenceStarter)
				{
					//  ÔÙ²éÑ¯Ò»´ÎprocessQ_media, ÒòÎªÊÓÆµ»áÒéµÄbmpInfo_compressµÈ£¬ÊÇÔÚÈë¶ÓÁÐÊ±²ÅÉú³ÉµÄ¡£Òª´ÓÀïÃæÈ¡³öÀ´
					if (pProcInfo->processQ_media.qTraverse(tmpHandler_findOrgMsgAndProc_is, pMsg, 0) <= 0) goto errLabel;
				}


	//  2015/09/06
				unsigned  int  uiChannelType;// = CONST_channelType_media;
	//  
	uiChannelType  =  CONST_channelType_talking;
	//
	if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsg->iTaskId,  pMsg->uiTaskType,  (  char  *  )pContent_req,  lenInBytes,  &pMsg->addr_logicalPeer.idInfo,  &pMsg->idInfo_taskSender,  &pMsg->idInfo_taskReceiver,  (  pAddr  ?  &pAddr->idInfo  :  NULL  ),  uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;

	//  2009/02/20
	if  (  bDlgTalk  )  {

		if  (  //uiTaskType  ==  CONST_imTaskType_transferAvInfo &&  
			pPst  )  
		{
			//
			//  2016/03/14

			//
			pPst->o.iTaskId  =  rcd.id;
			//  m_var.av.taskInfo.iIndex_sharedObj  =  iIndex_sharedObj;
			pPst->o.idInfo_starter.ui64Id  =  rcd.idInfo_send.ui64Id;
		
			pPst->o.tStartTime_org  =  rcd.tSendTime;
			pPst->o.uiTranNo_org  =  rcd.uiTranNo;
			pPst->o.uiContentType_org  =  rcd.uiContentType;

			pPst->o.ucbStarter  =  pContent_myTask->ucbStarter;									//  2010/08/31
			pPst->o.ucbVideoConference  =  pContent_myTask->ucbVideoConference;					//  2010/08/31
			//  m_var.av.taskInfo.ucbVideoConferenceStarter  =  pContent_myTask->ucbVideoConferenceStarter;

			//
			pPst->o.uiInitW  =  pContent_req->ass.tranInfo.video.vh_decompress.bih.biWidth;
			pPst->o.uiInitH  =  pContent_req->ass.tranInfo.video.vh_decompress.bih.biHeight;

			//  2014/09/25
			pPst->o.iIndex_taskInfo  =  pContent_myTask->iIndex_taskInfo;


			//  2010/08/31

			//
			pPst->o.local_avStream.tranInfo.audio  =  pContent_myTask->mem0_from.audio.ta_recvd;
			pPst->o.local_avStream.tranInfo.video  =  pContent_myTask->mem0_from.video.tv_recvd;

		}
	}

	//  2013/02/13
	if  (  uiTaskType  ==  CONST_imTaskType_viewDynBmp  )  {
		if  (  pRuleU  &&  pRuleU->uiType1  ==  CONST_talkerObjType_dynBmp  )  {
			if  (  !bReSend_viewDynBmp  )  {  //  新任务才需要设置
				pRuleU->taskInfo.iTaskId  =  rcd.id;
				pRuleU->taskInfo.tStartTran  =  tStartTran;
				pRuleU->taskInfo.uiTranNo  =  uiTranNo;
			}
		}
	}

	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Start AV:"  )  );
	if  (  pCompressVideo  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s video %d, maxFps %d, minFps %d."  ),  tBuf,  pCompressVideo->uiTranNo_openAvDev_org,  (  int  )pCompressVideo->compressor.common.usMaxFps_toShareBmp,  (  int  )pCompressVideo->compressor.common.usMinFps_toShareBmp  );
	if  (  pCompressAudio  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s audio %d"  ),  tBuf,  pCompressAudio->uiTranNo_openAvDev_org  );
	//qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
	
	iErr  =  0;
errLabel:

	//  2013/02/13
	if  (  iErr  )  {
		if  (  bReSend_viewDynBmp  )  {  //  重发viewDynBmp如果失败
		}
	}

	return  iErr;
}


 // 
#if  0
__declspec(  dllexport  )  int  old_procSendAvReplyInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  MIS_MSG_TASK  *  pMsgTask,  unsigned  char  ucbSendLocalAv,  int  iIndex_sharedObj,  DYN_BMP_rule  *  pDynBmp,  TASK_av_props  *  pTaskAvProps,  MSGR_ADDR  *  pAddr  )
{
	int								iErr								=	-1;
	MC_VAR_isCli					*	pProcInfo							=	NULL;
	QY_MC						*	pQyMc								=	NULL;
	IM_CONTENTU					*	pContent							=	NULL;	

#if  0
	
	if  (  !pMisCnt  )  return  -1;
	pProcInfo  =  QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;

	pContent  =  (  IM_CONTENTU  *  )pMsgTask->data.buf;

	TRANSFER_AV_reply_task	transferAvReplyInfo;
	int						lenInBytes						=	0;
	QY_SHARED_OBJ		*	pSharedObj						=	NULL;
	SHARED_OBJ_USR		*	pSharedObjUsr					=	NULL;
					  		
	pSharedObj  =	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  ucbSendLocalAv  )  {
		if  (  !pSharedObj  )  goto  errLabel;
		pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
		if  (  !pSharedObjUsr  )  goto  errLabel;
		//
		if  (  !pDynBmp  ||  pDynBmp->dynBmp.resObj.uiObjType  !=  CONST_objType_smallStream  )  {
			if  (  pSharedObjUsr->hWnd_starter  !=  hWnd_task  )  {
				showInfo_open0(  0,  0,  _T(  "procSendAvReplyInfo failed, cur_sharedObjUsr.hWnd != hWnd_task"  )  );
				goto  errLabel;
			}
		}
	}
									
	//  ·¢ËÍ½ÓÊÕÔÊÐí¸ø¶Ô·½
	memset(  &transferAvReplyInfo,  0,  sizeof(  transferAvReplyInfo  )  );
	transferAvReplyInfo.req.uiType  =  CONST_imCommType_transferAvReplyInfo;
	//  2016/04/18
	transferAvReplyInfo.req.tmp_usSubtype  =  CONST_transferAvReplyInfo_subtype_task;
	//
	transferAvReplyInfo.req.usOp  =  CONST_imOp_recv_accept;
	transferAvReplyInfo.req.tStartTime_org  =  pMsgTask->tStartTime;
	transferAvReplyInfo.req.uiTranNo_org  =  pMsgTask->uiTranNo;
	//
	if  (  ucbSendLocalAv  )  {	//  ±¾µØÊÓÆµÒ²ÔÊÐí·¢ËÍµÄÇé¿öÏÂ£¬Ò²·¢ËÍ¸ø¶Ô·½¡£
		CAP_procInfo_bmpU	*	pCapBmp  =  getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
		CAP_procInfo_audioU	*	pCapAudio	=	getCapAudioBySth(  pProcInfo,  pSharedObj->iIndex_capAudio,  0  );
		COMPRESS_VIDEO	*	pCompressVideo  =  NULL;	//  &pProcInfo->av.localAv.videoCaptureProcInfo.compressVideo;
		COMPRESS_AUDIO  *	pCompressAudio  =  NULL;	//  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio;

		if  (  pCapBmp  )  pCompressVideo  =  &pCapBmp->common.compressVideo;
		if  (  pCapAudio  )  pCompressAudio  =  &pCapAudio->common.compressAudio;

		if  (  pCompressVideo  )  {
			//  2009/04/19
			if  (  pContent->transferAvInfo.confCfg.conf.usMaxFps_toShareBmp_conf  )  {
				//  pCompressVideo->usMaxFps_toShareBmp  =  min(  pContent->transferAvInfo.tranInfo.video.usMaxFps_toShareBmp_videoConference,  pCompressVideo->usMaxFps_toShareBmp  );    
				//  2009/06/04
				transferAvReplyInfo.myTask.video.usMaxFps_toShareBmp_conf  =  pCompressVideo->compressor.common.usMaxFps_toShareBmp;
			}

			//
			//  transferAvReplyInfo.tranInfo.video.uiTranNo_openAvDev  =  pCompressVideo->uiTranNo_openAvDev;
			transferAvReplyInfo.req.tranInfo.video.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;
			//
			#if  0	//  2014/11/07
				 transferAvReplyInfo.tranInfo.video.usCapDriverIndex  =  pCompressVideo->usCapDriverIndex;
			#endif
			//  safeStrnCpy(  pCompressVideo->compressor.fourccStr,  transferAvReplyInfo.tranInfo.video.fourccStr,  mycountof(  transferAvReplyInfo.tranInfo.video.fourccStr  )  );
			memcpy(  &transferAvReplyInfo.req.tranInfo.video.compressor,  &pCompressVideo->compressor,  sizeof(  transferAvReplyInfo.req.tranInfo.video.compressor  )  );
			memcpy(  &transferAvReplyInfo.req.tranInfo.video.vh_compress,  &pCompressVideo->vh_compress,  sizeof(  transferAvReplyInfo.req.tranInfo.video.vh_compress  )  );
			//  2014/03/31
			memcpy(  &transferAvReplyInfo.req.tranInfo.video.vh_stream,  &pCompressVideo->vh_stream,  sizeof(  transferAvReplyInfo.req.tranInfo.video.vh_stream  )  );
			//  
			memcpy(  &transferAvReplyInfo.req.tranInfo.video.vh_decompress.bih,  &pCompressVideo->vh_decompress.bih,  sizeof(  transferAvReplyInfo.req.tranInfo.video.vh_decompress.bih  )  );

			//  
			
		}
		if  (  pCompressAudio  )  {
			//
			//  transferAvReplyInfo.tranInfo.audio.uiTranNo_openAvDev  =  pCompressAudio->uiTranNo_openAvDev;
			transferAvReplyInfo.req.tranInfo.audio.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_a;
			//  memcpy(  &transferAvReplyInfo.tranInfo.audio.wf_compress,  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio.policy.compressor.wf_compress,  sizeof(  transferAvReplyInfo.tranInfo.audio.wf_compress  )  );
			//  memcpy(  &transferAvReplyInfo.tranInfo.audio.wf_decompress,  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio.waveFormatEx,  sizeof(  transferAvReplyInfo.tranInfo.audio.wf_decompress  )  );
			memcpy(  &transferAvReplyInfo.req.tranInfo.audio.compressor,  &pCompressAudio->compressor,  sizeof(  transferAvReplyInfo.req.tranInfo.audio.compressor  )  );
			memcpy(  &transferAvReplyInfo.req.tranInfo.audio.ah_compress,  &pCompressAudio->ah_compress,  sizeof(  transferAvReplyInfo.req.tranInfo.audio.ah_compress  )  );
			memcpy(  &transferAvReplyInfo.req.tranInfo.audio.ah_decompress,  &pCompressAudio->ah_decompress,  sizeof(  transferAvReplyInfo.req.tranInfo.audio.ah_decompress  )  );
		}
		//  2014/09/04
		if  (  pDynBmp  )  {
			//transferAvReplyInfo.dynBmp.usIndex_obj  =  pDynBmp->usIndex_obj;
			transferAvReplyInfo.req.viewDynBmpReply.ucbSaveVideo  =  pDynBmp->ucbSaveVideo;		//  2014/09/07
		}
		//  2015/10/23
		if  (  pTaskAvProps  )  {
			memcpy(  &transferAvReplyInfo.req.tranInfo.taskAvProps,  pTaskAvProps,  sizeof(  transferAvReplyInfo.req.tranInfo.taskAvProps  )  );
		}
		//
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "AvReply: maxFps %d, video %d, audio %d, ucbSaveVmm %d"  ),  (  pCompressVideo  ?  (  int  )pCompressVideo->compressor.common.usMaxFps_toShareBmp  :  0  ),  transferAvReplyInfo.req.tranInfo.video.uiTranNo_openAvDev,  transferAvReplyInfo.req.tranInfo.audio.uiTranNo_openAvDev,  (  int  )transferAvReplyInfo.req.viewDynBmpReply.ucbSaveVideo  );
	}

	//  2008/06/12
	transferAvReplyInfo.myTask.ucbSendLocalAv  =  ucbSendLocalAv;
	transferAvReplyInfo.myTask.iIndex_sharedObj  =  iIndex_sharedObj;		//  ²»·¢±¾µØÊÓÆµµÄ£¬²»ÐèÒªÓÃsharedObj¿Õ¼ä
								
	//  ½«·¢¹ýÀ´µÄÑ¹ËõÐÅÏ¢´æÈëcontentµÄinternalÀï£¬ÓÃÔÚ½âÑ¹ËõÊ±
	//  int  index;  index  =  0;
	//
	transferAvReplyInfo.myTask.mem0_from.idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;
	transferAvReplyInfo.myTask.mem0_from.tStartTime_task  =  pMsgTask->tStartTime;
	//
	if  (  pMsgTask->uiTaskType  ==  CONST_imTaskType_transferAvInfo  )  {							//  2009/06/01
		if  (  pAddr->uiObjType  ==  CONST_objType_imGrp  )  {									
			transferAvReplyInfo.myTask.ucbVideoConference  =  TRUE;							//  2009/05/30									
			transferAvReplyInfo.myTask.mem0_from.ucbVideoConferenceStarter  =  TRUE;		//  2009/04/02
		}
	}
	//
	transferAvReplyInfo.myTask.mem0_from.video.tv_recvd.uiTranNo_openAvDev  =  pContent->transferAvInfo.tranInfo.video.uiTranNo_openAvDev;
#if  0  //  2014/11/07
	transferAvReplyInfo.myTask.mem0_from.video.usCapDriverIndex  =  0;	//  2014/11/07. pContent->transferAvInfo.tranInfo.video.usCapDriverIndex;
#endif

	//  safeStrnCpy(  pContent->transferAvInfo.tranInfo.video.fourccStr,  transferAvReplyInfo.myTask.mem0_from.video.fourccStr,  mycountof(  transferAvReplyInfo.myTask.mem0_from.video.fourccStr  )  );
	memcpy(  &transferAvReplyInfo.myTask.mem0_from.video.tv_recvd.compressor,  &pContent->transferAvInfo.tranInfo.video.compressor,  sizeof(  transferAvReplyInfo.myTask.mem0_from.video.tv_recvd.compressor  )  );

	memcpy(  &transferAvReplyInfo.myTask.mem0_from.video.tv_recvd.vh_compress,  &pContent->transferAvInfo.tranInfo.video.vh_compress,  sizeof(  transferAvReplyInfo.myTask.mem0_from.video.tv_recvd.vh_compress  )  );
	if  (  bSupported_sendVhDec(  )  )  {
		memcpy(  &transferAvReplyInfo.myTask.mem0_from.video.tv_recvd.vh_decompress,  &pContent->transferAvInfo.tranInfo.video.vh_decompress,  sizeof(  transferAvReplyInfo.myTask.mem0_from.video.tv_recvd.vh_decompress  )  );
	}
	//  2014/03/31
	memcpy(  &transferAvReplyInfo.myTask.mem0_from.video.tv_recvd.vh_stream,  &pContent->transferAvInfo.tranInfo.video.vh_stream,  sizeof(  transferAvReplyInfo.myTask.mem0_from.video.tv_recvd.vh_stream  )  );
	//
	transferAvReplyInfo.myTask.mem0_from.audio.ta_recvd.uiTranNo_openAvDev  =  pContent->transferAvInfo.tranInfo.audio.uiTranNo_openAvDev;
	//  memcpy(  &transferAvReplyInfo.myTask.mem0_from.audio.wf_compress_recvd,  &pContent->transferAvInfo.tranInfo.audio.wf_compress,  sizeof(  WAVEFORMATEX  )  );
	//  memcpy(  &transferAvReplyInfo.myTask.mem0_from.audio.wf_decompress_recvd,  &pContent->transferAvInfo.tranInfo.audio.wf_decompress,  sizeof(  WAVEFORMATEX  )  );
	memcpy(  &transferAvReplyInfo.myTask.mem0_from.audio.ta_recvd.compressor,  &pContent->transferAvInfo.tranInfo.audio.compressor,  sizeof(  transferAvReplyInfo.myTask.mem0_from.audio.ta_recvd.compressor  )  );
	memcpy(  &transferAvReplyInfo.myTask.mem0_from.audio.ta_recvd.ah_compress,  &pContent->transferAvInfo.tranInfo.audio.ah_compress,  sizeof(  transferAvReplyInfo.myTask.mem0_from.audio.ta_recvd.ah_compress  )  );
	memcpy(  &transferAvReplyInfo.myTask.mem0_from.audio.ta_recvd.ah_decompress,  &pContent->transferAvInfo.tranInfo.audio.ah_decompress,  sizeof(  transferAvReplyInfo.myTask.mem0_from.audio.ta_recvd.ah_decompress  )  );
	//

	if  (  transferAvReplyInfo.myTask.ucbVideoConference  )  transferAvReplyInfo.myTask.usCntLimit_mems_from  =  min(  pContent->transferAvInfo.confCfg.usCntLimit_mems_from,  MAX_mems_taskAv  );
	if  (  !transferAvReplyInfo.myTask.usCntLimit_mems_from  )  transferAvReplyInfo.myTask.usCntLimit_mems_from  =  1;	//  index  +  1;

	if  (  !transferAvReplyInfo.myTask.ucbVideoConference  )  {
		//  2011/08/08
		#if  0
			POLICY_av	policyAv;
			if  (  getPolicyAv(  TRUE,  0,  &policyAv  )  )  goto  errLabel;
		#endif
		AV_COMPRESSOR_CFG	tmpAvCompressor;
		if  (  pMsgTask->uiTaskType  ==  CONST_imTaskType_transferAvInfo  )  {
			if  (  myGetAvCompressorCfg(  CONST_capType_av,  0,  0,  0,  &tmpAvCompressor  )  )  goto  errLabel;
			}
		else  {
			  if  (  myGetAvCompressorCfg(  CONST_capType_mediaFile,  0,  0,  0,  &tmpAvCompressor  )  )  goto  errLabel;
		}

		//
		//  memcpy(  &transferAvReplyInfo.myTask.audio.playCfg,  (  pMsgTask->uiTaskType  ==  CONST_imTaskType_transferAvInfo  )  ?  &policyAv.avCompressor.audio.playCfg  :  &policyAv.mediaFileCompressor.audio.playCfg,  sizeof(  transferAvReplyInfo.myTask.audio.playCfg  )  );
		memcpy(  &transferAvReplyInfo.myTask.audio.playCfg,  &tmpAvCompressor.audio.playCfg,  sizeof(  transferAvReplyInfo.myTask.audio.playCfg  )  );
		}
	else  {	//  2009/05/31
		  transferAvReplyInfo.myTask.usCntLimit_activeMems_from  =  pContent->transferAvInfo.confCfg.usCntLimit_activeMems_from;
		  if  (  !transferAvReplyInfo.myTask.usCntLimit_activeMems_from  )  transferAvReplyInfo.myTask.usCntLimit_activeMems_from  =  min(  transferAvReplyInfo.myTask.usCntLimit_mems_from,  mycountof(  transferAvReplyInfo.myTask.activeMems_from  )  );
										
		  //  2009/06/03					
		  memcpy(  &transferAvReplyInfo.myTask.audio.playCfg,  &pContent->transferAvInfo.tranInfo.audio.compressor.playCfg,  sizeof(  transferAvReplyInfo.myTask.audio.playCfg  )  );
	}
	transferAvReplyInfo.myTask.hWnd_task  =  hWnd_task;		//  2009/09/09

	//
	lenInBytes  =  sizeof(  transferAvReplyInfo  );

	MACRO_prepareForTran(  );
	//
	//  if  (  postMsg2TaskQ_mc(  pQyMc,  pDlg->m_var.pSci,  pDlg->m_var.pMisCnt,  NULL,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  0,  (  char  *  )&transferAvReplyInfo,  lenInBytes,  &pDlg->m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  CONST_channelType_media  )  )  goto  errLabel;  
	//
	if  (  ucbSendLocalAv  )  {	
		if  (  !pSharedObj  ||  !pSharedObjUsr  )  goto  errLabel;

		pSharedObjUsr->ucbNotSendData  =  (  pAddr->uiObjType  ==  CONST_objType_imGrp  );

		if  (  addToMsgrs_sendLocalAv(  pProcInfo,  pMisCnt,  &pMsgTask->idInfo_taskSender,  FALSE,  &pSharedObj->curRoute_sendLocalAv  )  )  goto  errLabel;
	}
	//  2015/09/21
	int  channelType  =  CONST_channelType_media;
	//  2015/09/21
	channelType  =  0;
	//  2012/04/01
	if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  pMsgTask->uiTaskType,  (  char  *  )&transferAvReplyInfo,  lenInBytes,  &pAddr->idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &pMsgTask->idInfo_taskSender,  channelType,  NULL,  FALSE  )  )  goto  errLabel;

#endif

	iErr  =  0;
errLabel:
	return  iErr;								
}
#endif


//
__declspec(  dllexport  )  int  procSendAvReplyInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  MIS_MSG_TASK  *  pMsgTask,  unsigned  char  ucbSendLocalAv,  int  iIndex_sharedObj,  int  iTaskId,  DYN_BMP_rule  *  pDynBmp,  TASK_av_props  *  pTaskAvProps,  MSGR_ADDR  *  pAddr  )
{
	int								iErr								=	-1;
	MC_VAR_isCli					*	pProcInfo							=	NULL;
	QY_MC						*	pQyMc								=	NULL;
	IM_CONTENTU					*	pContent							=	NULL;	

#if  10
	
	if  (  !pMisCnt  )  return  -1;
	pProcInfo  =  QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;

	pContent  =  (  IM_CONTENTU  *  )pMsgTask->data.buf;

	//
	int  index_taskInfo  =  getQmcTaskInfoIndexBySth(  pProcInfo,  iTaskId  );
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  index_taskInfo  );
	if  (  !pTaskInfo  )  goto  errLabel;
	QMC_taskData_conf* pTc; pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
	if  (  pTc->common.uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
	

	//TRANSFER_AV_reply_task	transferAvReplyInfo;
	TRANSFER_AV_replyInfo  transferAvReplyInfo_req;
	int						lenInBytes; lenInBytes = 0;
	QY_SHARED_OBJ* pSharedObj; pSharedObj = NULL;
	SHARED_OBJ_USR* pSharedObjUsr; pSharedObjUsr = NULL;
					  		
	pSharedObj  =	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  ucbSendLocalAv  )  {
		if  (  !pSharedObj  )  goto  errLabel;
		pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
		if  (  !pSharedObjUsr  )  goto  errLabel;
		//
		if  (  !pDynBmp  ||  pDynBmp->dynBmp.resObj.uiObjType  !=  CONST_objType_smallStream  )  {
			if  (  pSharedObjUsr->hWnd_starter  !=  hWnd_task  )  {
				showInfo_open0(  0,  0,  _T(  "procSendAvReplyInfo failed, cur_sharedObjUsr.hWnd != hWnd_task"  )  );
				goto  errLabel;
			}
		}
	}

	//
	{

		//
		TASK_transferAv  task;
		memset(&task, 0, sizeof(task));
		PROC_TASK_AV& transferAvReplyInfo_myTask = task.myTask;



		//  ·¢ËÍ½ÓÊÕÔÊÐí¸ø¶Ô·½
		memset(&transferAvReplyInfo_req, 0, sizeof(transferAvReplyInfo_req));
		transferAvReplyInfo_req.uiType = CONST_imCommType_transferAvReplyInfo;
		//  2016/04/18
		transferAvReplyInfo_req.tmp_usSubtype = CONST_transferAvReplyInfo_subtype_task;
		//
		transferAvReplyInfo_req.usOp = CONST_imOp_recv_accept;
		transferAvReplyInfo_req.tStartTime_org = pMsgTask->tStartTime;
		transferAvReplyInfo_req.uiTranNo_org = pMsgTask->uiTranNo;
		//
		if (ucbSendLocalAv) {	//  ±¾µØÊÓÆµÒ²ÔÊÐí·¢ËÍµÄÇé¿öÏÂ£¬Ò²·¢ËÍ¸ø¶Ô·½¡£
			CAP_procInfo_bmpU* pCapBmp = getCapBmpBySth(pProcInfo, pSharedObj->iIndex_capBmp, 0);
			CAP_procInfo_audioU* pCapAudio = getCapAudioBySth(pProcInfo, pSharedObj->iIndex_capAudio, 0);
			COMPRESS_VIDEO* pCompressVideo = NULL;	//  &pProcInfo->av.localAv.videoCaptureProcInfo.compressVideo;
			COMPRESS_AUDIO* pCompressAudio = NULL;	//  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio;

			if (pCapBmp)  pCompressVideo = &pCapBmp->common.compressVideo;
			if (pCapAudio)  pCompressAudio = &pCapAudio->common.compressAudio;

			if (pCompressVideo) {
				//  2009/04/19
				if (pContent->transferAvInfo.confCfg.conf.usMaxFps_toShareBmp_conf) {
					//  pCompressVideo->usMaxFps_toShareBmp  =  min(  pContent->transferAvInfo.tranInfo.video.usMaxFps_toShareBmp_videoConference,  pCompressVideo->usMaxFps_toShareBmp  );    
					//  2009/06/04
					transferAvReplyInfo_myTask.video.usMaxFps_toShareBmp_conf = pCompressVideo->compressor.common.usMaxFps_toShareBmp;
				}

				//
				//  transferAvReplyInfo.tranInfo.video.uiTranNo_openAvDev  =  pCompressVideo->uiTranNo_openAvDev;
				transferAvReplyInfo_req.tranInfo.video.uiTranNo_openAvDev = pSharedObjUsr->uiTranNo_openAvDev_v;
				//
#if  0	//  2014/11/07
				transferAvReplyInfo.tranInfo.video.usCapDriverIndex = pCompressVideo->usCapDriverIndex;
#endif
				//  safeStrnCpy(  pCompressVideo->compressor.fourccStr,  transferAvReplyInfo.tranInfo.video.fourccStr,  mycountof(  transferAvReplyInfo.tranInfo.video.fourccStr  )  );
				memcpy(&transferAvReplyInfo_req.tranInfo.video.compressor, &pCompressVideo->compressor, sizeof(transferAvReplyInfo_req.tranInfo.video.compressor));
				memcpy(&transferAvReplyInfo_req.tranInfo.video.vh_compress, &pCompressVideo->vh_compress, sizeof(transferAvReplyInfo_req.tranInfo.video.vh_compress));
				//  2014/03/31
				memcpy(&transferAvReplyInfo_req.tranInfo.video.vh_stream, &pCompressVideo->vh_stream, sizeof(transferAvReplyInfo_req.tranInfo.video.vh_stream));
				//  
				memcpy(&transferAvReplyInfo_req.tranInfo.video.vh_decompress.bih, &pCompressVideo->vh_decompress.bih, sizeof(transferAvReplyInfo_req.tranInfo.video.vh_decompress.bih));

				//  

			}
			if (pCompressAudio) {
				//
				//  transferAvReplyInfo.tranInfo.audio.uiTranNo_openAvDev  =  pCompressAudio->uiTranNo_openAvDev;
				transferAvReplyInfo_req.tranInfo.audio.uiTranNo_openAvDev = pSharedObjUsr->uiTranNo_openAvDev_a;
				//  memcpy(  &transferAvReplyInfo.tranInfo.audio.wf_compress,  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio.policy.compressor.wf_compress,  sizeof(  transferAvReplyInfo.tranInfo.audio.wf_compress  )  );
				//  memcpy(  &transferAvReplyInfo.tranInfo.audio.wf_decompress,  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio.waveFormatEx,  sizeof(  transferAvReplyInfo.tranInfo.audio.wf_decompress  )  );
				memcpy(&transferAvReplyInfo_req.tranInfo.audio.compressor, &pCompressAudio->compressor, sizeof(transferAvReplyInfo_req.tranInfo.audio.compressor));
				memcpy(&transferAvReplyInfo_req.tranInfo.audio.ah_compress, &pCompressAudio->ah_compress, sizeof(transferAvReplyInfo_req.tranInfo.audio.ah_compress));
				memcpy(&transferAvReplyInfo_req.tranInfo.audio.ah_decompress, &pCompressAudio->ah_decompress, sizeof(transferAvReplyInfo_req.tranInfo.audio.ah_decompress));
			}
			//  2014/09/04
			if (pDynBmp) {
				//transferAvReplyInfo.dynBmp.usIndex_obj  =  pDynBmp->usIndex_obj;
				transferAvReplyInfo_req.viewDynBmpReply.ucbSaveVideo = pDynBmp->ucbSaveVideo;		//  2014/09/07
			}
			//  2015/10/23
			if (pTaskAvProps) {
				memcpy(&transferAvReplyInfo_req.tranInfo.taskAvProps, pTaskAvProps, sizeof(transferAvReplyInfo_req.tranInfo.taskAvProps));
			}
			//
			//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("AvReply: maxFps %d, video %d, audio %d, ucbSaveVmm %d"), (pCompressVideo ? (int)pCompressVideo->compressor.common.usMaxFps_toShareBmp : 0), transferAvReplyInfo_req.tranInfo.video.uiTranNo_openAvDev, transferAvReplyInfo_req.tranInfo.audio.uiTranNo_openAvDev, (int)transferAvReplyInfo_req.viewDynBmpReply.ucbSaveVideo);
		}

		//  2008/06/12
		transferAvReplyInfo_myTask.ucbSendLocalAv = ucbSendLocalAv;
		transferAvReplyInfo_myTask.iIndex_sharedObj = iIndex_sharedObj;		//  ²»·¢±¾µØÊÓÆµµÄ£¬²»ÐèÒªÓÃsharedObj¿Õ¼ä

		//  ½«·¢¹ýÀ´µÄÑ¹ËõÐÅÏ¢´æÈëcontentµÄinternalÀï£¬ÓÃÔÚ½âÑ¹ËõÊ±
		//  int  index;  index  =  0;
		//
		transferAvReplyInfo_myTask.mem0_from.idInfo.ui64Id = pMsgTask->data.route.idInfo_from.ui64Id;
		transferAvReplyInfo_myTask.mem0_from.tStartTime_task = pMsgTask->tStartTime;
		//
		if (pMsgTask->uiTaskType == CONST_imTaskType_transferAvInfo) {							//  2009/06/01
			if (pAddr->uiObjType == CONST_objType_imGrp) {
				transferAvReplyInfo_myTask.ucbVideoConference = TRUE;							//  2009/05/30									
				transferAvReplyInfo_myTask.mem0_from.ucbVideoConferenceStarter = TRUE;		//  2009/04/02
			}
		}
		//
		transferAvReplyInfo_myTask.mem0_from.video.tv_recvd.uiTranNo_openAvDev = pContent->transferAvInfo.ass.tranInfo.video.uiTranNo_openAvDev;
#if  0  //  2014/11/07
		transferAvReplyInfo.myTask.mem0_from.video.usCapDriverIndex = 0;	//  2014/11/07. pContent->transferAvInfo.tranInfo.video.usCapDriverIndex;
#endif

		//  safeStrnCpy(  pContent->transferAvInfo.tranInfo.video.fourccStr,  transferAvReplyInfo.myTask.mem0_from.video.fourccStr,  mycountof(  transferAvReplyInfo.myTask.mem0_from.video.fourccStr  )  );
		memcpy(&transferAvReplyInfo_myTask.mem0_from.video.tv_recvd.compressor, &pContent->transferAvInfo.ass.tranInfo.video.compressor, sizeof(transferAvReplyInfo_myTask.mem0_from.video.tv_recvd.compressor));

		memcpy(&transferAvReplyInfo_myTask.mem0_from.video.tv_recvd.vh_compress, &pContent->transferAvInfo.ass.tranInfo.video.vh_compress, sizeof(transferAvReplyInfo_myTask.mem0_from.video.tv_recvd.vh_compress));
		if (bSupported_sendVhDec()) {
			memcpy(&transferAvReplyInfo_myTask.mem0_from.video.tv_recvd.vh_decompress, &pContent->transferAvInfo.ass.tranInfo.video.vh_decompress, sizeof(transferAvReplyInfo_myTask.mem0_from.video.tv_recvd.vh_decompress));
		}
		//  2014/03/31
		memcpy(&transferAvReplyInfo_myTask.mem0_from.video.tv_recvd.vh_stream, &pContent->transferAvInfo.ass.tranInfo.video.vh_stream, sizeof(transferAvReplyInfo_myTask.mem0_from.video.tv_recvd.vh_stream));
		//
		transferAvReplyInfo_myTask.mem0_from.audio.ta_recvd.uiTranNo_openAvDev = pContent->transferAvInfo.ass.tranInfo.audio.uiTranNo_openAvDev;
		//  memcpy(  &transferAvReplyInfo.myTask.mem0_from.audio.wf_compress_recvd,  &pContent->transferAvInfo.tranInfo.audio.wf_compress,  sizeof(  WAVEFORMATEX  )  );
		//  memcpy(  &transferAvReplyInfo.myTask.mem0_from.audio.wf_decompress_recvd,  &pContent->transferAvInfo.tranInfo.audio.wf_decompress,  sizeof(  WAVEFORMATEX  )  );
		memcpy(&transferAvReplyInfo_myTask.mem0_from.audio.ta_recvd.compressor, &pContent->transferAvInfo.ass.tranInfo.audio.compressor, sizeof(transferAvReplyInfo_myTask.mem0_from.audio.ta_recvd.compressor));
		memcpy(&transferAvReplyInfo_myTask.mem0_from.audio.ta_recvd.ah_compress, &pContent->transferAvInfo.ass.tranInfo.audio.ah_compress, sizeof(transferAvReplyInfo_myTask.mem0_from.audio.ta_recvd.ah_compress));
		memcpy(&transferAvReplyInfo_myTask.mem0_from.audio.ta_recvd.ah_decompress, &pContent->transferAvInfo.ass.tranInfo.audio.ah_decompress, sizeof(transferAvReplyInfo_myTask.mem0_from.audio.ta_recvd.ah_decompress));
		//

	//	if  (  transferAvReplyInfo_myTask.ucbVideoConference  )  transferAvReplyInfo_myTask.usCntLimit_mems_from  =  min(  pContent->transferAvInfo.confCfg.usCntLimit_mems_from,  MAX_mems_taskAv  );
	//	if  (  !transferAvReplyInfo_myTask.usCntLimit_mems_from  )  transferAvReplyInfo_myTask.usCntLimit_mems_from  =  1;	//  index  +  1;

		if (!transferAvReplyInfo_myTask.ucbVideoConference) {
			//  2011/08/08
#if  0
			POLICY_av	policyAv;
			if (getPolicyAv(TRUE, 0, &policyAv))  goto  errLabel;
#endif
			AV_COMPRESSOR_CFG	tmpAvCompressor;
			if (pMsgTask->uiTaskType == CONST_imTaskType_transferAvInfo) {
				if (myGetAvCompressorCfg(CONST_capType_av, 0, 0, 0, &tmpAvCompressor))  goto  errLabel;
			}
			else {
				if (myGetAvCompressorCfg(CONST_capType_mediaFile, 0, 0, 0, &tmpAvCompressor))  goto  errLabel;
			}

			//
			//  memcpy(  &transferAvReplyInfo.myTask.audio.playCfg,  (  pMsgTask->uiTaskType  ==  CONST_imTaskType_transferAvInfo  )  ?  &policyAv.avCompressor.audio.playCfg  :  &policyAv.mediaFileCompressor.audio.playCfg,  sizeof(  transferAvReplyInfo.myTask.audio.playCfg  )  );
			memcpy(&transferAvReplyInfo_myTask.audio.playCfg, &tmpAvCompressor.audio.playCfg, sizeof(transferAvReplyInfo_myTask.audio.playCfg));
		}
		else {	//  2009/05/31
			//		  transferAvReplyInfo_myTask.usCntLimit_activeMems_from  =  pContent->transferAvInfo.confCfg.usCntLimit_activeMems_from;
			//		  if  (  !transferAvReplyInfo_myTask.usCntLimit_activeMems_from  )  transferAvReplyInfo.myTask.usCntLimit_activeMems_from  =  min(  transferAvReplyInfo.myTask.usCntLimit_mems_from,  mycountof(  transferAvReplyInfo.myTask.activeMems_from  )  );

					  //  2009/06/03					
			memcpy(&transferAvReplyInfo_myTask.audio.playCfg, &pContent->transferAvInfo.ass.tranInfo.audio.compressor.playCfg, sizeof(transferAvReplyInfo_myTask.audio.playCfg));
		}
		transferAvReplyInfo_myTask.hWnd_task = hWnd_task;		//  2009/09/09

		//
		lenInBytes = sizeof(transferAvReplyInfo_req);

		MACRO_prepareForTran();
		//
		//  if  (  postMsg2TaskQ_mc(  pQyMc,  pDlg->m_var.pSci,  pDlg->m_var.pMisCnt,  NULL,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  0,  (  char  *  )&transferAvReplyInfo,  lenInBytes,  &pDlg->m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  CONST_channelType_media  )  )  goto  errLabel;  
		//
		if (ucbSendLocalAv) {
			if (!pSharedObj || !pSharedObjUsr)  goto  errLabel;

			pTc->ucbNotSendData = (pAddr->uiObjType == CONST_objType_imGrp);

			if (addToMsgrs_sendLocalAv(pProcInfo, pMisCnt, &pMsgTask->idInfo_taskSender, FALSE, &pTaskInfo->var.curRoute_sendLocalAv, false, _T("procSendAvReplyInfo.1239")))  goto  errLabel;
		}
		//  2015/09/21
		int  channelType; channelType = CONST_channelType_media;
		//  2015/09/21
		channelType = 0;
		//  2012/04/01
		if (postMsgTask2Mgr_mc(pMisCnt, CONST_misMsgType_task, 0, CONST_qyCmd_sendMedia, tStartTran, uiTranNo, 0, pMsgTask->iTaskId, pMsgTask->uiTaskType, (char*)&transferAvReplyInfo_req, lenInBytes, &pAddr->idInfo, &pMsgTask->idInfo_taskSender, &pMsgTask->idInfo_taskReceiver, &pMsgTask->idInfo_taskSender, channelType, NULL, FALSE))  goto  errLabel;

#endif

	}

	iErr  =  0;
errLabel:
	return  iErr;								
}




//  2014/08/28.
//__declspec(  dllexport  )  int  procSendTaskProcReq(  MIS_CNT  *  pMisCnt,  unsigned  short  usCode,  unsigned  short  usOp,  time_t  tStartTime_org,  unsigned  int  uiTranNo_org,  unsigned  int  uiContentType_org,  int  iTaskId,  unsigned  int  uiTaskType,  QIS_res_obj  *  pDynBmp,  unsigned  int  uiChannelType,  BOOL  bOutputDirectly,  LPCTSTR  pHint,  MSGR_ADDR  *  pAddr  )
__declspec(dllexport)  int  procSendTaskProcReq(MIS_CNT* pMisCnt, unsigned  short  usCode, unsigned  short  usOp, time_t  tStartTime_org, unsigned  int  uiTranNo_org, unsigned  int  uiContentType_org, QY_MESSENGER_ID idInfo_imGrp_related, int  iTaskId, unsigned  int  uiTaskType, QIS_res_obj* pDynBmp, unsigned  int  uiChannelType, BOOL  bOutputDirectly, LPCTSTR  pHint, MSGR_ADDR* pAddr)
{
	int					iErr		=	-1;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	if  (  !pMisCnt  )  return  -1;
	MC_VAR_isCli		*	pProcInfo	=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	TASK_PROC_REQ		taskProcReq;
	int					lenInBytes;

#ifdef  __DEBUG__
		#if  0
			 if  (  CONST_imOp_stopSending  ==  usOp  )  {			
				 showInfo_open0(  0,  0,  _T(  "TEST: req stopSendIng skipped"  )  );
				 return  -1;		
			 }
		#endif
#endif

	//
	memset(  &taskProcReq,  0,  sizeof(  taskProcReq  )  );
	taskProcReq.uiType  =  CONST_imCommType_taskProcReq;
	taskProcReq.usOp  =  usOp;
	taskProcReq.tStartTime_org  =  tStartTime_org;
	taskProcReq.uiTranNo_org  =  uiTranNo_org;
	//  taskProcReq.uiSerialNo_org  =  uiSerialNo_org;
	taskProcReq.uiContentType_org  =  uiContentType_org;
	//
	taskProcReq.idInfo_imGrp_related = idInfo_imGrp_related;
	//
	taskProcReq.uiTaskType  =  uiTaskType;
	if  (  pDynBmp  )  {
		taskProcReq.viewDynBmp.ros.uiObjType  =  pDynBmp->resObj.uiObjType;
		taskProcReq.viewDynBmp.ros.usIndex_obj  =  pDynBmp->resObj.usIndex_obj;
	}
	//
	lenInBytes  =  sizeof(  taskProcReq  );			
	//					
	MACRO_prepareForTran(  );						
	//
	unsigned  int  uiMisMsgType  =  CONST_misMsgType_task;
	if  (  bOutputDirectly  )  uiMisMsgType  =  CONST_misMsgType_outputTask;
	
	//
	QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );	
	if  (  !pHint  )  pHint  =  _T(  ""  );
	//qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  pHint,  _T(  ""  ),  _T(  "sendTaskProcReq: %s %s %d. -> %I64u. tn %d"  ),  qyGetDesByType1(  CONST_imOpTable_en,  taskProcReq.usOp  ),  qyGetDesByType1(  pTable,  taskProcReq.viewDynBmp.ros.uiObjType  ),  taskProcReq.viewDynBmp.ros.usIndex_obj,  pAddr->idInfo.ui64Id,  uiTranNo  );

	//
	if  (  postMsgTask2Mgr_mc(  pMisCnt,  uiMisMsgType,  0,  usCode,  tStartTran,  uiTranNo,  0,  iTaskId,  uiTaskType,  (  char  *  )&taskProcReq,  lenInBytes,  &pAddr->idInfo,  NULL,  NULL,  &pAddr->idInfo,  uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;


	//
	iErr  =  0;
errLabel:
	return  iErr;
}





 ////////////////////////////////////////////////////
 //  2012/04/19
 __declspec(  dllexport  )  int  procSendGpsInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  void  *  pReserved,  int  *  piTaskId,  MSGR_ADDR  *  pAddr  )
 {
	int					iErr					=	-1;
	MC_VAR_isCli		*	pProcInfo				=	NULL;  
	QY_MC			*	pQyMc					=	NULL;
	TCHAR				tBuf[256]				=	_T(  ""  );
	CQyMalloc			mallocObj;
	QY_SHARED_OBJ  *	pSharedObj				=	NULL;
	//  int				iIndex_sharedObjUsr		=	0;
	SHARED_OBJ_USR	*	pSharedObjUsr			=	NULL;

	#ifdef  __DEBUG__
			traceLog(  (TCHAR*)_T(  "procSendGpsInfo called"  )  );	
	#endif

			/*
	if  (  !pMisCnt  )  return  -1;
	pProcInfo  =  QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;



	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  {
		if  (  uiTaskType  !=  CONST_imTaskType_viewGps  )  goto  errLabel;
		}
	else  {		//  2010/09/04
		  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  iIndex_sharedObjUsr  );
		  if  (  !pSharedObjUsr  )  goto  errLabel;
		  //
	}

	//  tStartTime, uiTranNo
	MACRO_prepareForTran(  );

	//  
	MIS_MSG_TASK				*	pMsg;
	if  (  !(  pMsg  =  (  MIS_MSG_TASK  *  )mallocObj.mallocf(  sizeof(  MIS_MSG_TASK  )  )  )  )  goto  errLabel;
	TRANSFER_GPS_INFO			*	pContent;
	unsigned  int					lenInBytes;
	IM_TASK_RCD						rcd;
	//
	MACRO_memset_misMsgTask(  pMsg  );
	pMsg->uiType  =  CONST_misMsgType_task;
	//
	pMsg->pMisCnt  =  pMisCnt;
	//
	pMsg->ucFlg  =  CONST_commFlg_talkData;
	//
	pMsg->usCode  =  CONST_qyCmd_sendMedia;
	pMsg->tStartTime  =  tStartTran;
	pMsg->uiTranNo  =  uiTranNo;
	//
	pContent  =  (  TRANSFER_GPS_INFO  *  )pMsg->data.buf;
	memset(  pContent,  0,  sizeof(  pContent[0]  )  );
	pContent->uiType  =  CONST_imCommType_transferGpsInfo;
	pContent->uiTaskType  =  uiTaskType;

	//
	pContent_myTask->iIndex_sharedObj  =  iIndex_sharedObj;
	//
	pContent_myTask->hWnd_task  =  hWnd_task;	//  2009/09/09

	//  2007/07/18
	pMsg->uiTaskType  =  uiTaskType;
	//
	pMsg->idInfo_taskSender.ui64Id  =  pMisCnt->idInfo.ui64Id;
	if  (  pAddr  )  {
		pMsg->idInfo_taskReceiver.ui64Id  =  pAddr->idInfo.ui64Id;
		pMsg->addr_logicalPeer.idInfo.ui64Id  =  pAddr->idInfo.ui64Id;
	}
	//
	pMsg->iStatus  =  CONST_imTaskStatus_req;


	//  ÕâÀïµÄ¸³ÖµËÆºõÓ¦ÔÚ·¢ËÍÊ±Ê¹ÓÃ, 2007/07/24
	pMsg->data.route.idInfo_from.ui64Id  =  pMsg->idInfo_taskSender.ui64Id;
	pMsg->data.route.idInfo_to.ui64Id  =  pMsg->idInfo_taskReceiver.ui64Id;
	//

	lenInBytes  =  sizeof(  pContent[0]  );
	pMsg->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  lenInBytes;

	memset(  &rcd,  0,  sizeof(  rcd  )  );
	if  (  !msg2TaskRcd(  pMisCnt,  pMsg,  CONST_qyRc_unknown,  &rcd  )  )  goto  errLabel;
	
	{
		void	*	pDb	=	NULL;
		#ifndef  __NOTSUPPORT_DB__
				 CQnmDb		db;
				 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
				 pDb  =  db.m_pDbMem->pDb;
		#endif
		//
		if  (  storeTaskInDb(  pDb,  pQyMc->cfg.db.iDbType,  pMisCnt,  0,  &rcd,  FALSE  )  <  0  )  goto  errLabel;
	}
		
	pMsg->iTaskId  =  rcd.id;
	pMsg->uiTaskMode_unused  =  rcd.uiMode;
	pMsg->uiChannelType  =  CONST_channelType_media;		//  2009/10/17


	///////////////
	//
#if  0	//  2010/09/09
	if  (  pAddr  &&  pSharedObj  &&  pSharedObjUsr  )  {
		pSharedObjUsr->ucbNotSendData  =  (  ucbSendLocalAv  &&  pAddr->uiObjType  ==  CONST_objType_imGrp  );
		if  (  setROUTE_sendLocalAv(  pProcInfo,  pMisCnt,  &pAddr->idInfo,  pContent_myTask->ucbVideoConferenceStarter,  pSharedObj  )  )  {
			traceLogA(  "Onstartavcall: setROUTE_sendLocalAv failed."  );		//  
		}
	}
#endif

	//  2009/04/28
	if  (  pSharedObj  )  {
		if  (  !pSharedObjUsr  )  goto  errLabel;

		pSharedObjUsr->iTaskId  =  rcd.id;
		//
		if  (  pAddr  )  {
			pSharedObjUsr->idInfo_to.ui64Id  =  pAddr->idInfo.ui64Id;			//  2010/09/02
			//
		}
	}
	if  (  piTaskId  )  *piTaskId  =  rcd.id;

	//
	if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsg->iTaskId,  pMsg->uiTaskType,  (  char  *  )pContent,  lenInBytes,  (  pAddr  ?  &pAddr->idInfo  :  NULL  ),  &pMsg->idInfo_taskSender,  &pMsg->idInfo_taskReceiver,  (  pAddr  ?  &pAddr->idInfo  :  NULL  ),  CONST_channelType_media,  NULL,  FALSE  )  )  goto  errLabel;

	//  2009/02/20

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Start GPS:"  )  );
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
	
	*/

	iErr  =  0;
errLabel:
	return  iErr;
}


//
__declspec(  dllexport  )  int  procSendGpsReplyInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  MIS_MSG_TASK  *  pMsgTask,  unsigned  char  ucbSendLocalAv,  int  iIndex_sharedObj,  MSGR_ADDR  *  pAddr  )
{
	int								iErr								=	-1;
	MC_VAR_isCli					*	pProcInfo							=	NULL;
	QY_MC						*	pQyMc								=	NULL;
	IM_CONTENTU					*	pContent							=	NULL;	

#if  0
	
	if  (  !pMisCnt  )  return  -1;
	pProcInfo  =  QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;

	pContent  =  (  IM_CONTENTU  *  )pMsgTask->data.buf;

	TRANSFER_GPS_replyInfo	replyInfo;
	int						lenInBytes						=	0;
	QY_SHARED_OBJ		*	pSharedObj						=	NULL;
	SHARED_OBJ_USR		*	pSharedObjUsr					=	NULL;
					  		
	pSharedObj  =	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  ucbSendLocalAv  )  {
		if  (  !pSharedObj  )  goto  errLabel;
		pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
		if  (  !pSharedObjUsr  )  goto  errLabel;
	}
									
	//  ·¢ËÍ½ÓÊÕÔÊÐí¸ø¶Ô·½
	memset(  &replyInfo,  0,  sizeof(  replyInfo  )  );
	replyInfo.uiType  =  CONST_imCommType_transferGpsReplyInfo;
	replyInfo.usOp  =  CONST_imOp_recv_accept;
	replyInfo.tStartTime_org  =  pMsgTask->tStartTime;
	replyInfo.uiTranNo_org  =  pMsgTask->uiTranNo;
	//

	//  2008/06/12
	//  replyInfo.myTask.ucbSendLocalAv  =  ucbSendLocalAv;
	replyInfo.myTask.iIndex_sharedObj  =  iIndex_sharedObj;		//  ²»·¢±¾µØÊÓÆµµÄ£¬²»ÐèÒªÓÃsharedObj¿Õ¼ä
								
	//  ½«·¢¹ýÀ´µÄÑ¹ËõÐÅÏ¢´æÈëcontentµÄinternalÀï£¬ÓÃÔÚ½âÑ¹ËõÊ±
	//  int  index;  index  =  0;
	//
	//
	if  (  pMsgTask->uiTaskType  ==  CONST_imTaskType_viewGps  )  {							//  2009/06/01
	}
	//


	replyInfo.myTask.hWnd_task  =  hWnd_task;		//  2009/09/09

	//
	lenInBytes  =  sizeof(  replyInfo  );

	MACRO_prepareForTran(  );
	//
	//  if  (  postMsg2TaskQ_mc(  pQyMc,  pDlg->m_var.pSci,  pDlg->m_var.pMisCnt,  NULL,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  0,  (  char  *  )&replyInfo,  lenInBytes,  &pDlg->m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  CONST_channelType_media  )  )  goto  errLabel;  
	//
	if  (  ucbSendLocalAv  )  {	
		if  (  !pSharedObj  ||  !pSharedObjUsr  )  goto  errLabel;

		pSharedObjUsr->ucbNotSendData  =  (  pAddr->uiObjType  ==  CONST_objType_imGrp  );

		if  (  addToMsgrs_sendLocalAv(  pProcInfo,  pMisCnt,  &pMsgTask->idInfo_taskSender,  FALSE,  &pSharedObj->curRoute_sendLocalAv  )  )  goto  errLabel;
	}
	//  2012/04/01
	//  if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  0,  (  char  *  )&replyInfo,  lenInBytes,  &pAddr->idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &pMsgTask->idInfo_taskSender,  CONST_channelType_media,  NULL,  FALSE  )  )  goto  errLabel;
	if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  pMsgTask->uiTaskType,  (  char  *  )&replyInfo,  lenInBytes,  &pAddr->idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &pMsgTask->idInfo_taskSender,  CONST_channelType_media,  NULL,  FALSE  )  )  goto  errLabel;

#endif

	iErr  =  0;
errLabel:
	return  iErr;								
}



