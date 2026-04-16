

#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qmcAcm.h"
#include	"qyAvRecordPublic.h" 
#include	"qyVk.h"
#include	"qyMcMainInternalBak.h"
#include	<assert.h>
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"

#include	<WinSock2.h>
#include	<MSWSock.h>
#include	"mtSock_iocp.h"

#include	"qmcCommFunc_isCli.h"
#include	"qmcTaskInfo.h"


//
 int  tmpHandler_toSend(  void  *  p0,  void  *  p1,  void  *  pMsgElemParam  )
{
	int								iErr				=	-1;
	COMMON_PARAM	*				pCommonParam0		=	(  COMMON_PARAM  *  )p0;
	COMMON_PARAM	*				pCommonParam1		=	(  COMMON_PARAM  *  )p1;

	MC_VAR_isCli	*				pProcInfo			=	(  MC_VAR_isCli  *  )pCommonParam0->p0;
	MIS_CNT			*				pMisCnt				=	(  MIS_CNT  *  )pCommonParam0->p1;
	MIS_CHANNEL		*				pChannel			=	(  MIS_CHANNEL  *  )pCommonParam0->p2;
	//
	TRAN_INFO_MIS	*				pTranInfo			=	(  TRAN_INFO_MIS  *  )pCommonParam1->p0;
	MIS_MSG_TASK	*				pMsgTask_o			=	&pTranInfo->pMsg_o->task;

	int								lenInBytes;

	if  (  !pProcInfo  ||  !pMisCnt  ||  !pChannel  ||  !pMsgTask_o  )  {
		showInfo_open0(  0,  0,  _T(  "tmpHandler_toSend failed: pMisCnt or pChannel or pMsgTask_o is null"  )  );
		return  -1;
	}

	LPCTSTR  where_showInfo;	where_showInfo	=  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  );

	switch  (  (  (  MIS_MSGU  *  )pMsgElemParam  )->uiType  )  {
			case  CONST_misMsgType_task:  
			case  CONST_misMsgType_outputTask:  
				{
				  MIS_MSG_TASK			*	pMsgElem		=	(  MIS_MSG_TASK  *  )pMsgElemParam;

				  pMsgElem->nTimes_tryToSend  ++  ;

				  //
				  //  				  
				  if  (  pMsgElem->data.route.debugInfo.dwTickCnt_me_start  )  {	//  2008/11/20
					  pMsgElem->dwTickCnt_start  =  pMsgElem->data.route.debugInfo.dwTickCnt_me_start;
					  pMsgElem->dwTickCnt_toSend  =  GetTickCount(  );		//  2011/01/22
				  }
				  if  (  pMsgElem->data.route.debugInfo.tTime_start  )  {
					  if  (  isUcFlgResp(  pMsgElem->ucFlg  )  )  pMsgElem->data.route.debugInfo.usElapsed_peer_resp_toSend  =  (  unsigned  short  )(  GetTickCount(  )  -  pMsgElem->data.route.debugInfo.dwTickCnt_peer_recved  );
					  else  {
						    pMsgElem->data.route.debugInfo.usElapsed_toSend  =  (  unsigned  short  )(  GetTickCount(  )  -  pMsgElem->data.route.debugInfo.dwTickCnt_me_start  );
					  		//  
					  }
					  //
					  pMsgElem->index_debugInfo  =  pMsgElem->data.route.debugInfo.index;
				  }

				  //  
				  pMsgElem->data.route.idInfo_from.ui64Id  =  pMisCnt->idInfo.ui64Id;

				  #ifdef  __DEBUG__
						  //	printMsgRoute(  pMsgElem->ucFlg,  &pMsgElem->data.route  );
				          IM_CONTENTU  *  tmp_pContent_i  =  (  IM_CONTENTU  * )pMsgElem->data.buf;
						  //
						  if (tmp_pContent_i->uiType == CONST_ancCommType_transferAudioData) {
							  int  ii = 0;
						  }
				  #endif

				  memcpy(  pMsgTask_o,  pMsgElem,  offsetof(  MIS_MSG_TASK,  data  )  );
	 			  lenInBytes  =  sizeof(  pMsgTask_o->data  );	
				  if  (  qyhtonRouteTalkData(  &pMsgElem->data.route,  pMsgElem->data.buf,  0,  TRUE,  pMsgElem->ucFlg,  (  char  *  )&pMsgTask_o->data,  (  unsigned  int  *  )&lenInBytes,  NULL,  0  )  )  {
					  #ifdef  __DEBUG__
							  traceLog((TCHAR*)  _T(  "tmpHandler_toSend: qyhtonRouteTalkData failed"  )  );
					  #endif
					  showInfo_open0(  0,  0,  _T(  "tmpHandler_toSend failed: htonRouteTalkData failed"  )  );
					  goto  errLabel;
				  }
	 			  pMsgTask_o->lenInBytes  =  lenInBytes;
	 			  lenInBytes  +=  offsetof(  MIS_MSG_TASK,  data  );
	
				  //
#ifdef  __DEBUG__
				  //
				  if (0) {
					  //
					  MSG_ROUTE route;
					  CQyMalloc mallocObj;
					  int tmp_size = sizeof(IM_CONTENTU);
					  IM_CONTENTU* tmp_pContent = (IM_CONTENTU*)mallocObj.mallocf(tmp_size);
					  memset(tmp_pContent, 0, tmp_size);
					  qyntohRouteTalkData(pMsgTask_o->ucFlg, (char*) & pMsgTask_o->data, pMsgTask_o->lenInBytes, &route, tmp_pContent, (TCHAR*)_T(""), 0);
					  //
					  if (tmp_pContent->uiType == CONST_ancCommType_transferAudioData) {
						  int  iiii = 0;
					  }
					  //
					  printf("kk\n");
				  }
#endif 



				  //
				  if  (  postMsg2OutputQ_mc(  pMisCnt,  (  MIS_MSGU  *  )pMsgTask_o,  lenInBytes,  pChannel  )  )  {
					  //  
					  #ifdef  __DEBUG__
							  traceLogA(  (char*)  "postMsg2OutputQ_mc failed"  );
					  #endif
					  showInfo_open0(  0,  0,  _T(  "tmpHandler_toSend failed: postMsg2OutputQ_mc failed"  )  );					  
					  goto  errLabel;
				  }


				  pMsgElem->tStartTime_processed  =  pTranInfo->tNow;
				  pMsgElem->uiTranNo_processed  =  pTranInfo->uiTranNo;

				  pTranInfo->nNodes_processed  ++  ;

			
				  iErr  =  0;  goto  errLabel;
				
				}	
				break;
			default:
					qyShowInfo1(  CONST_qyShowType_debug,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHandler_toSend failed: toSendQÀïÓÐÎ´´¦ÀíµÄÏûÏ¢ %s"  ),  qyGetDesByType1(  CONST_misMsgTypeTable,  (  (  MIS_MSGU  *  )pMsgElemParam  )->uiType  )  );					  
					goto  errLabel;
					break;
	}


	unsigned  int  uiMaxSendMsgs; uiMaxSendMsgs = pTranInfo->uiMaxSendMsgs ? pTranInfo->uiMaxSendMsgs : pProcInfo->cfg.uiMaxSendMsgs;	//  2011/01/23
#if  0
	if  (  pTranInfo->nNodes_processed  >=  uiMaxSendMsgs  )  {
		iErr  =  1;  goto  errLabel;	//  
	}
#endif
	//
	if  (  getQ2Nodes_toPostMsg(  &pChannel->outputQ2  )  >  MAX_outputQ2Nodes_toPostQ  )  {
		iErr  =  1;  goto  errLabel;
	}




	iErr  =  0;
errLabel:
	return  iErr;

}

 int  tmpHandler_needRemoveMsg_cli(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int						iErr				=	-1;
	 //  p0	 	 
	 COMMON_PARAM			*	pCommonParam1		=	(  COMMON_PARAM  *  )p1;
	 MIS_MSGU				*	pMsgElem			=	(  MIS_MSGU  *  )p2;
	 //
	 TRAN_INFO_MIS			*	pTranInfo			=	(  TRAN_INFO_MIS  *  )pCommonParam1->p0;
	 
	 switch  (  pMsgElem->uiType  )  {
			 case  CONST_misMsgType_task:
			 case  CONST_misMsgType_outputTask:
				   break;
			 default:
				     traceLogA(  (char*)  "tmpHandler_needRemoveMsg_cli: msgType error."  );
                     goto  errLabel;
					 break;
	 }

	 if  (  pMsgElem->task.nTimes_tryToSend  )  {			//  Õâ¸öÌõ¼þÊÇÎªÁËÈ·±£Ö»ÄÜÉ¾³ýÒÑ·¢¹ýµÄ¡£
		 iErr  =  1;  goto  errLabel;		 
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}



#if  0
int  old_tmpInitMsgMixer(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSG_TASK  *	pMsgTask_av,  AV_TRAN_INFO  *	pAvTranInfo,  PROC_TASK_AV  *	pTask,  int  iContentType,  MIS_MSG_TASK  *  pMsgTask_toBeMixed,  MIS_MSG_TASK  *  pMsgMixer  )
{
	int  iErr  =  -1;

	//
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	
	//
	if  (  pMsgMixer->uiType  )  return  -1;

	pMsgMixer->uiType  =  CONST_misMsgType_task;
	pMsgMixer->pMisCnt  =  pMisCnt;

	pMsgMixer->ucFlg  =  CONST_commFlg_talkData;	//  CONST_commFlg_talkData;
	pMsgMixer->ucFlg  |=  CONST_commFlg_routeTalkData;		//  2011/01/26

	pMsgMixer->usCode  =  CONST_qyCmd_sendMedia;

	MACRO_prepareForTran(  );

	pMsgMixer->tStartTime  =  tStartTran;
	pMsgMixer->uiTranNo  =  uiTranNo;

	//  
	pMsgMixer->uiChannelType  =  pMsgTask_av->uiChannelType;	

	//
	switch  (  iContentType  )  {
			case  CONST_imCommType_transferAudioData:  {
				  TRANSFER_AUDIO_DATA			*	pMixer						=	(  TRANSFER_AUDIO_DATA  *  )pMsgMixer->data.buf;

				  memset(  pMixer,  0,  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  );
				  pMixer->uiType  =  CONST_imCommType_transferAudioData;									   
				  pMixer->uiTranNo_openAvDev  =  pAvTranInfo->audio.uiTranNo_openAvDev;
									   
				  //
				  unsigned  char  ucbNeedShowFrameInfo  =  FALSE;
				  #if  0		
					   if  (  (  int  )(  pMsgMixer->tStartTime  -  pTask->mixer.tLastTime_showFrameInfo  )  >  pProcInfo->cfg.usNeedShowFrameInfoIntervalInS  )  {
						   ucbNeedShowFrameInfo  =  TRUE;
					   }
				  #endif

				  #ifdef  __DEBUG__		
					      //  for test
					      ucbNeedShowFrameInfo  =  TRUE;
				  #endif
#if  0
				  pTask->mixer.usCnt_pkts  ++  ;			
				  if  (  ucbNeedShowFrameInfo  )  {
					  pMsgMixer->data.route.debugInfo.dwTickCnt_me_start  =  GetTickCount(  );
					  time_t	tNow;  mytime(  &tNow  );  pMsgMixer->data.route.debugInfo.tTime_start  =  tNow;
					  pMsgMixer->ucFlg  |=  CONST_commFlg_routeTalkData;
					  pMixer->tLastTime_showFrameInfo_020534  =  pTask->mixer.tLastTime_showFrameInfo;
					  pMixer->usCnt_pkts  =  pTask->mixer.usCnt_pkts;
					  //			
					  pTask->mixer.tLastTime_showFrameInfo  =  pMsgMixer->tStartTime;
					  pTask->mixer.usCnt_pkts  =  0;												  
					  //							  
					  qyShowInfo1(  CONST_qyShowType_debug,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tn %d, %s"  ),  pMsgMixer->uiTranNo,  ucbNeedShowFrameInfo  ?  _T(  "audio showFrameInfo"  )  :  _T(  ""  )  );					
				  }
#endif
													   
				  }
				  break;
			case  CONST_imCommType_transferVideoData:  {
				  TRANSFER_VIDEO_DATA			*	pMixer						=	(  TRANSFER_VIDEO_DATA  *  )pMsgMixer->data.buf;
				  //  2016/03/28
				  IM_CONTENTU			*	pContent_toBeMixed	=	M_getMsgContent(  pMsgTask_toBeMixed->ucFlg,  &pMsgTask_toBeMixed->data  );
				  if  (  pContent_toBeMixed->uiType  !=  iContentType  )  {
					  showInfo_open0(  0,  0,  _T(  "tmpInitMsgMixer failed, content_toBeMixed.type != contentType"  )  );
					  goto  errLabel;
				  }
				  IM_CONTENTU  *  pContent_av  =  M_getMsgContent(  pMsgTask_av->ucFlg,  &pMsgTask_av->data  );

				  //
				  memset(  pMixer,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
				  pMixer->uiType  =  iContentType;									   
				  pMixer->uiTranNo_openAvDev  =  pAvTranInfo->video.uiTranNo_openAvDev;
					
				  //  2016/03/28
				  if  (  pContent_toBeMixed->transferVideoData.uiTranNo_openAvDev  )  {
					  if  (  pMsgTask_av->uiTaskType  ==  CONST_imTaskType_shareDynBmp  )  {
						  if  (  pContent_av->uiType  ==  CONST_imCommType_transferAvInfo  )  {
							  //
							  if  (  pContent_av->transferAvInfo.viewDynBmp.resObj.uiObjType  ==  CONST_objType_smallStream  )  {
								  //			
								  if  (  pContent_toBeMixed->transferVideoData.uiTranNo_openAvDev  !=  pMixer->uiTranNo_openAvDev  )  {
									  pMixer->uiTranNo_openAvDev  =  pContent_toBeMixed->transferVideoData.uiTranNo_openAvDev;					  
								  }
								  //
							  }
						  }
					  }
				  }

				  //
				  unsigned  char  ucbNeedShowFrameInfo  =  FALSE;
				  #if  0		
					   if  (  (  int  )(  pMsgMixer->tStartTime  -  pTask->mixer.tLastTime_showFrameInfo  )  >  pProcInfo->cfg.usNeedShowFrameInfoIntervalInS  )  {
						   ucbNeedShowFrameInfo  =  TRUE;
					   }
				  #endif

				  #ifdef  __DEBUG__		
					      //  for test
					      //  ucbNeedShowFrameInfo  =  TRUE;
				  #endif
	
#if  0
				  pTask->mixer.usCnt_pkts  ++  ;			
				  if  (  ucbNeedShowFrameInfo  )  {
					  pMsgMixer->data.route.debugInfo.dwTickCnt_me_start  =  GetTickCount(  );
					  time_t	tNow;  mytime(  &tNow  );  pMsgMixer->data.route.debugInfo.tTime_start  =  tNow;
					  pMsgMixer->ucFlg  |=  CONST_commFlg_routeTalkData;
					  pMixer->tLastTime_showFrameInfo_020534  =  pTask->mixer.tLastTime_showFrameInfo;
					  pMixer->usCnt_pkts  =  pTask->mixer.usCnt_pkts;
					  //			
					  pTask->mixer.tLastTime_showFrameInfo  =  pMsgMixer->tStartTime;
					  pTask->mixer.usCnt_pkts  =  0;												  
					  //							  
					  qyShowInfo1(  CONST_qyShowType_debug,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tn %d, %s"  ),  pMsgMixer->uiTranNo,  ucbNeedShowFrameInfo  ?  _T(  "video showFrameInfo"  )  :  _T(  ""  )  );					
				  }
#endif
													   
				  }
				  break;
			default:
					break;
	}
	
	//
	if  (  pTask->ucbVideoConference  )  {
		if  (  !pTask->ucbVideoConferenceStarter  )  {
			//pMsgMixer->data.route.idInfo_to.ui64Id  =  pMsgTask_av->data.route.idInfo_to.ui64Id;
			pMsgMixer->data.route.idInfo_to.ui64Id  =  pMsgTask_av->data.route.idInfo_from.ui64Id;
			}
		else  {
			  pMsgMixer->data.route.idInfo_to.ui64Id  =  pMsgTask_av->addr_logicalPeer.idInfo.ui64Id;  
		}
		}
	else  if  (  pTask->doProxy.bExists_avProxy  )  {	//  2014/11/21
			  pMsgMixer->data.route.idInfo_to.ui64Id  =  pMsgTask_av->addr_logicalPeer.idInfo.ui64Id;
			  }
	else  {
		  //memcpy(  &pMsgMixer->data.route,  &pMsgTask_toBeMixed->data.route,  sizeof(  pMsgMixer->data.route  )  );  
		  pMsgMixer->data.route  =  pTaskInfo->var.curRoute_sendLocalAv.route;
	}
	
	//
	if  (  pMsgTask_toBeMixed->data.route.debugInfo.dwTickCnt_me_start  )  {	//  2011/01/24
		pMsgMixer->dwTickCnt_start  =  pMsgTask_toBeMixed->data.route.debugInfo.dwTickCnt_me_start;
		pMsgMixer->dwTickCnt_toSend  =  GetTickCount(  );		//  2011/01/22
	}


	iErr  =  0;
errLabel:
	return  iErr;
}
#endif


//
int  tmpInitMsgMixer(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSG_TASK  *	pMsgTask_av,  AV_TRAN_INFO  *	pAvTranInfo1,  PROC_TASK_AV  *	pTask,  int  iContentType,  MIS_MSG_TASK  *  pMsgTask_toBeMixed,  MIS_MSG_TASK  *  pMsgMixer  )
{
	int  iErr  =  -1;

	//
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	
	//
	if  (  pMsgMixer->uiType  )  return  -1;

	pMsgMixer->uiType  =  CONST_misMsgType_task;
	pMsgMixer->pMisCnt  =  pMisCnt;

	pMsgMixer->ucFlg  =  CONST_commFlg_routeTalkData;	//  CONST_commFlg_talkData;
	pMsgMixer->ucFlg  |=  CONST_commFlg_routeTalkData;		//  2011/01/26

	pMsgMixer->usCode  =  CONST_qyCmd_sendMedia;

	MACRO_prepareForTran(  );

	pMsgMixer->tStartTime  =  tStartTran;
	pMsgMixer->uiTranNo  =  uiTranNo;

	//  
	pMsgMixer->uiChannelType  =  pMsgTask_av->uiChannelType;	

	//
	switch  (  iContentType  )  {
			case  CONST_imCommType_transferAudioData:  {
				  TRANSFER_AUDIO_DATA			*	pMixer						=	(  TRANSFER_AUDIO_DATA  *  )pMsgMixer->data.buf;
				  //
				  IM_CONTENTU			*	pContent_toBeMixed	=	M_getMsgContent(  pMsgTask_toBeMixed->ucFlg,  &pMsgTask_toBeMixed->data  );
				  if  (  pContent_toBeMixed->uiType  !=  iContentType  )  {
					  showInfo_open0(  0,  0,  _T(  "tmpInitMsgMixer failed, content_toBeMixed.type != contentType"  )  );
					  goto  errLabel;
				  }

				  //
				  memset(  pMixer,  0,  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  );
				  pMixer->uiType  =  CONST_imCommType_transferAudioData;									   
				  //
				  //pMixer->uiTranNo_openAvDev  =  pAvTranInfo->audio.uiTranNo_openAvDev;
				  pMixer->uiTranNo_openAvDev  =  pContent_toBeMixed->transferAudioData.uiTranNo_openAvDev;

				  //
				  if  (  !pContent_toBeMixed->transferAudioData.uiTranNo_openAvDev  )  {
					  showInfo_open0(  0,  0,  _T(  "tmpInitMsgMixer err: pContent_toBeMixed->transferAudioData.uiTranNo_openAvDev is 0"  )  );
				  }
									   
				  //
				  unsigned  char  ucbNeedShowFrameInfo  =  FALSE;
				  #if  0		
					   if  (  (  int  )(  pMsgMixer->tStartTime  -  pTask->mixer.tLastTime_showFrameInfo  )  >  pProcInfo->cfg.usNeedShowFrameInfoIntervalInS  )  {
						   ucbNeedShowFrameInfo  =  TRUE;
					   }
				  #endif

				  #ifdef  __DEBUG__		
					      //  for test
					      ucbNeedShowFrameInfo  =  TRUE;
				  #endif
#if  0
				  pTask->mixer.usCnt_pkts  ++  ;			
				  if  (  ucbNeedShowFrameInfo  )  {
					  pMsgMixer->data.route.debugInfo.dwTickCnt_me_start  =  GetTickCount(  );
					  time_t	tNow;  mytime(  &tNow  );  pMsgMixer->data.route.debugInfo.tTime_start  =  tNow;
					  pMsgMixer->ucFlg  |=  CONST_commFlg_routeTalkData;
					  pMixer->tLastTime_showFrameInfo_020534  =  pTask->mixer.tLastTime_showFrameInfo;
					  pMixer->usCnt_pkts  =  pTask->mixer.usCnt_pkts;
					  //			
					  pTask->mixer.tLastTime_showFrameInfo  =  pMsgMixer->tStartTime;
					  pTask->mixer.usCnt_pkts  =  0;												  
					  //							  
					  qyShowInfo1(  CONST_qyShowType_debug,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tn %d, %s"  ),  pMsgMixer->uiTranNo,  ucbNeedShowFrameInfo  ?  _T(  "audio showFrameInfo"  )  :  _T(  ""  )  );					
				  }
#endif
													   
				  }
				  break;
			case  CONST_imCommType_transferVideoData:  {
				  TRANSFER_VIDEO_DATA			*	pMixer						=	(  TRANSFER_VIDEO_DATA  *  )pMsgMixer->data.buf;
				  //  2016/03/28
				  IM_CONTENTU			*	pContent_toBeMixed	=	M_getMsgContent(  pMsgTask_toBeMixed->ucFlg,  &pMsgTask_toBeMixed->data  );
				  if  (  pContent_toBeMixed->uiType  !=  iContentType  )  {
					  showInfo_open0(  0,  0,  _T(  "tmpInitMsgMixer failed, content_toBeMixed.type != contentType"  )  );
					  goto  errLabel;
				  }
				  IM_CONTENTU  *  pContent_av  =  M_getMsgContent(  pMsgTask_av->ucFlg,  &pMsgTask_av->data  );

				  //
				  memset(  pMixer,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
				  pMixer->uiType  =  iContentType;									   
				  //
				  //pMixer->uiTranNo_openAvDev  =  pAvTranInfo->video.uiTranNo_openAvDev;		
				  pMixer->uiTranNo_openAvDev  =  pContent_toBeMixed->transferVideoData.uiTranNo_openAvDev;					  
		
				  //
				  if  (  !pContent_toBeMixed->transferVideoData.uiTranNo_openAvDev  )  {
					  showInfo_open0(  0,  0,  _T(  "tmpInitMsgMixer err: pContent_toBeMixed->transferVideoData.uiTranNo_openAvDev is 0"  )  );
				  }

				  //  2016/03/28
#if  0
				  if  (  pContent_toBeMixed->transferVideoData.uiTranNo_openAvDev  )  {
					  if  (  pMsgTask_av->uiTaskType  ==  CONST_imTaskType_shareDynBmp  )  {
						  if  (  pContent_av->uiType  ==  CONST_imCommType_transferAvInfo  )  {
							  //
							  if  (  pContent_av->transferAvInfo.viewDynBmp.resObj.uiObjType  ==  CONST_objType_smallStream  )  {
								  //			
								  if  (  pContent_toBeMixed->transferVideoData.uiTranNo_openAvDev  !=  pMixer->uiTranNo_openAvDev  )  {
									  pMixer->uiTranNo_openAvDev  =  pContent_toBeMixed->transferVideoData.uiTranNo_openAvDev;					  
								  }
								  //
							  }
						  }
					  }
				  }
#endif

				  //
				  unsigned  char  ucbNeedShowFrameInfo  =  FALSE;
				  #if  0		
					   if  (  (  int  )(  pMsgMixer->tStartTime  -  pTask->mixer.tLastTime_showFrameInfo  )  >  pProcInfo->cfg.usNeedShowFrameInfoIntervalInS  )  {
						   ucbNeedShowFrameInfo  =  TRUE;
					   }
				  #endif

				  #ifdef  __DEBUG__		
					      //  for test
					      //  ucbNeedShowFrameInfo  =  TRUE;
				  #endif
	
#if  0
				  pTask->mixer.usCnt_pkts  ++  ;			
				  if  (  ucbNeedShowFrameInfo  )  {
					  pMsgMixer->data.route.debugInfo.dwTickCnt_me_start  =  GetTickCount(  );
					  time_t	tNow;  mytime(  &tNow  );  pMsgMixer->data.route.debugInfo.tTime_start  =  tNow;
					  pMsgMixer->ucFlg  |=  CONST_commFlg_routeTalkData;
					  pMixer->tLastTime_showFrameInfo_020534  =  pTask->mixer.tLastTime_showFrameInfo;
					  pMixer->usCnt_pkts  =  pTask->mixer.usCnt_pkts;
					  //			
					  pTask->mixer.tLastTime_showFrameInfo  =  pMsgMixer->tStartTime;
					  pTask->mixer.usCnt_pkts  =  0;												  
					  //							  
					  qyShowInfo1(  CONST_qyShowType_debug,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tn %d, %s"  ),  pMsgMixer->uiTranNo,  ucbNeedShowFrameInfo  ?  _T(  "video showFrameInfo"  )  :  _T(  ""  )  );					
				  }
#endif
													   
				  }
				  break;
			default:
					break;
	}
	


	//
	if  (  pTask->ucbVideoConference  )  {
		if  (  !pTask->ucbVideoConferenceStarter  )  {
			//pMsgMixer->data.route.idInfo_to.ui64Id  =  pMsgTask_av->data.route.idInfo_to.ui64Id;
			pMsgMixer->data.route.idInfo_to.ui64Id  =  pMsgTask_av->data.route.idInfo_from.ui64Id;
			}
		else  {
			//
			bool  bConfAv = false;
			switch (pMsgMixer->uiChannelType) {
					case  CONST_channelType_media:
					case  CONST_channelType_realTimeMedia:
						  bConfAv = true;
						  break;
					default:
							break;			
			}
			//
			if (!bConfAv) {
				//
				pMsgMixer->data.route.idInfo_to.ui64Id = pMsgTask_av->addr_logicalPeer.idInfo.ui64Id;
			}
			else {  //  2025/01/21
				 pMsgMixer->data.route = pTaskInfo->var.curRoute_sendLocalAv.route_confAv;
			}
		}
		}
	else  if  (  pTask->doProxy.bExists_avProxy  )  {	//  2014/11/21
			  pMsgMixer->data.route.idInfo_to.ui64Id  =  pMsgTask_av->addr_logicalPeer.idInfo.ui64Id;
			  }
	else  {
		  //memcpy(  &pMsgMixer->data.route,  &pMsgTask_toBeMixed->data.route,  sizeof(  pMsgMixer->data.route  )  );  
		  pMsgMixer->data.route  =  pTaskInfo->var.curRoute_sendLocalAv.route;
	}
	
	//
	if  (  pMsgTask_toBeMixed->data.route.debugInfo.dwTickCnt_me_start  )  {	//  2011/01/24
		pMsgMixer->dwTickCnt_start  =  pMsgTask_toBeMixed->data.route.debugInfo.dwTickCnt_me_start;
		pMsgMixer->dwTickCnt_toSend  =  GetTickCount(  );		//  2011/01/22
	}


	iErr  =  0;
errLabel:
	return  iErr;
}




//
 int  tmpHandler_toMixer_audio(  void  *  p0,  void  *  p1,  void  *  pMsgElemParam  )
{
	int								iErr						=	-1;
	COMMON_PARAM				*	pCommonParam0				=	(  COMMON_PARAM  *  )p0;
	COMMON_PARAM				*	pCommonParam1				=	(  COMMON_PARAM  *  )p1;

	COMMON_PARAM				*	pCommonParam0_toSend		=	(  COMMON_PARAM  *  )pCommonParam0->p0;
	//MIS_MSG_TASK				*	pMsgTask_av					=	(  MIS_MSG_TASK  *  )pCommonParam0->p1;
	TASK_common * taskElem=(TASK_common*)pCommonParam0->p1;
	
	MC_VAR_isCli				*	pProcInfo					=	(  MC_VAR_isCli  *  )pCommonParam0_toSend->p0;
	MIS_CNT						*	pMisCnt						=	(  MIS_CNT  *  )pCommonParam0_toSend->p1;
	MIS_CHANNEL					*	pChannel					=	(  MIS_CHANNEL  *  )pCommonParam0_toSend->p2;

	QY_MC						*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;

	//
	QMC_TASK_INFO * pTaskInfo=(QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo,taskElem->m_index_taskInfo);
	if(pTaskInfo==NULL)return -1;
	MIS_MSG_TASK * pMsgTask_av=&pTaskInfo->var.pTaskData->msgU.task;
	if(pMsgTask_av->uiType!=CONST_misMsgType_task ) {
		return -1;
	}

	
	IM_CONTENTU					*	pContent_av					=	(  IM_CONTENTU  *  )pMsgTask_av->data.buf;
	AV_TRAN_INFO				*	pAvTran						=	NULL;
	PROC_TASK_AV				*	pTask						=	NULL;

	if  (  pContent_av->uiType  ==  CONST_imCommType_transferAvInfo  )  {
		//
		if(!pTaskInfo->var.m_bReplyTask) {
		//
		if  (  pContent_av->transferAvInfo.tmp_usSubtype  !=  CONST_transferAvInfo_subtype_task  )  {
			#ifdef  __DEBUG__
					MACRO_qyAssert(  0,  _T(  "transferAv.subtype err, not task"  )  );
			#endif
			return  -1;
		}
		//
		//TRANSFER_AV_task  *  pTransferAvTask  =  (  TRANSFER_AV_task  *  )pContent_av;
		TASK_transferAv * task=(TASK_transferAv*)taskElem;
		//
		pAvTran  =  &pContent_av->transferAvInfo.ass.tranInfo;
		pTask  =  &task->myTask;//&pTransferAvTask->myTask;
		}
	else  //if (  pContent_av->uiType  ==  CONST_imCommType_transferAvReplyInfo  )  
	{
		TASK_transferAv * task=(TASK_transferAv*)taskElem;
			 pTask  =  &task->myTask;//get_transferAvReplyInfo_pTask(  &pContent_av->transferAvReplyInfo,  _T(  ""  )  );  //  &pContent_av->transferAvReplyInfo.myTask;							
			 if  (  !pTask  )  return  -1;
			 pAvTran  =  &pTask->reply_avTranInfo;//pContent_av->transferAvReplyInfo.tranInfo;					  					  

		}
	}
	if  (  !pAvTran  )  return  -1;


	TRAN_INFO_MIS				*	pTranInfo					=	(  TRAN_INFO_MIS  *  )pCommonParam1->p0;
	MIS_MSG_TASK				*	pMsgTask_o					=	&pTranInfo->pMsg_o->task;
	
	MIS_MSG_TASK				*	pMsgMixer					=	(  MIS_MSG_TASK  *  )pCommonParam1->p1;
	TRANSFER_AUDIO_DATA			*	pMixer						=	(  TRANSFER_AUDIO_DATA  *  )pMsgMixer->data.buf;


	switch  (  (  (  MIS_MSGU  *  )pMsgElemParam  )->uiType  )  {
			case  CONST_misMsgType_task:  {
				  MIS_MSG_TASK			*	pMsgElem		=	(  MIS_MSG_TASK  *  )pMsgElemParam;
				  MIS_CNT				*	pMisCntElem		=	(  MIS_CNT  *  )pMsgElem->pMisCnt;
				  IM_CONTENTU			*	pContentElem	=	(  IM_CONTENTU  *  )pMsgElem->data.buf;

				  pMsgElem->nTimes_tryToSend  ++  ;

				  switch  (  pContentElem->uiType  )  {
						  case  CONST_imCommType_transferAudioData:  {
									   
							    if  (  !pMsgMixer->uiType  )  {
									tmpInitMsgMixer(  pProcInfo,  pMisCnt,  pMsgTask_av,  pAvTran,  pTask,  CONST_imCommType_transferAudioData,  pMsgElem,  pMsgMixer  );
								}
								if  (  pMixer->uiTranNo_openAvDev  !=  pContentElem->transferAudioData.uiTranNo_openAvDev  )  {

										if  (  pMixer->usCnt  )  {
											 if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewAudioStatus  )  {
												 //qyShowInfo1(  CONST_qyShowType_detail,  0,(char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer: flush mixer data. mixer.usCnt %d, mixer.uiLen %d,  mem.len %d."  ),  pMixer->usCnt,  pMixer->uiLen,  pContentElem->transferAudioData.mems[i].uiLen  );
											 }
											 tmpHandler_toSend(  pCommonParam0_toSend,  p1,  pMsgMixer  );
										 }
										 //
										 MACRO_memset_misMsgTask(  pMsgMixer  );
										 if  (  !pMsgMixer->uiType  )  {										 
											 tmpInitMsgMixer(  pProcInfo,  pMisCnt,  pMsgTask_av,  pAvTran,  pTask,  CONST_imCommType_transferAudioData,  pMsgElem,  pMsgMixer  );
										 }

								}

								//  È»ºó°ÑÊý¾Ý¼Óµ½»º³åÀï
								if  (  pMixer->usCnt  >  mycountof(  pMixer->mems  )  )  {						//  Êµ¼ÊÕâÀïÊÇ²»¶ÔµÄ£¬°´Àí²»ÄÜÓÐÕâÑùµÄÇé¿ö³öÏÖ, ÒòÎª
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer failed:  pMixer->usCnt %d >= mems %d."  ),  pMixer->usCnt,  mycountof(  pMixer->mems  )  );
									goto  errLabel;
								}
								if  (  !pContentElem->transferAudioData.usCnt  )  {
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer:  transferAudioData.usCnt is 0."  )  );
									break;
								}
								if  (  pContentElem->transferAudioData.usCnt  >  mycountof(  pContentElem->transferAudioData.mems  )  )  {
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer failed:  transferAudioData.usCnt %d >= mems %d."  ),  pContentElem->transferAudioData.usCnt,  mycountof(  pContentElem->transferAudioData.mems  )  );
									goto  errLabel;
								}	
								if  (  pContentElem->transferAudioData.uiLen  >  sizeof(  pContentElem->transferAudioData.buf  )  )  {
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer failed:  transferAudioData.uiLen %d too big."  ),  pContentElem->transferAudioData.uiLen  );
									goto  errLabel;
								}

								int								i;
								TRANSFER_AUDIO_dataMemHead	*	pMem;
								int								iPos;

								for  (  iPos  =  0,  i  =  0;  i  <  pContentElem->transferAudioData.usCnt;  iPos  +=  pContentElem->transferAudioData.mems[i].uiLen,  i  ++  )  {
									 //
									 if  (  iPos  +  pContentElem->transferAudioData.mems[i].uiLen  >  pContentElem->transferAudioData.uiLen  )  {
										 traceLogA(  (char*)  "tmpHandler_toMixer failed: iPos + mems[i].uiLen > content.uiLen"  );
										 goto  errLabel;
									 }

									 //
									 if  (  pMixer->usCnt  ==  mycountof(  pMixer->mems  )  ||  pContentElem->transferAudioData.mems[i].uiLen  +  pMixer->uiLen  >  sizeof(  pMixer->buf  )  )  {

										 if  (  pMixer->usCnt  )  {
											 if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewAudioStatus  )  {
												 qyShowInfo1(  CONST_qyShowType_detail,  0,(char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer: flush mixer data. mixer.usCnt %d, mixer.uiLen %d,  mem.len %d."  ),  pMixer->usCnt,  pMixer->uiLen,  pContentElem->transferAudioData.mems[i].uiLen  );
											 }
											 tmpHandler_toSend(  pCommonParam0_toSend,  p1,  pMsgMixer  );
										 }
										 //
										 MACRO_memset_misMsgTask(  pMsgMixer  );
										 if  (  !pMsgMixer->uiType  )  {										 
											 tmpInitMsgMixer(  pProcInfo,  pMisCnt,  pMsgTask_av,  pAvTran,  pTask,  CONST_imCommType_transferAudioData,  pMsgElem,  pMsgMixer  );
										 }
									 }

									 //
									 pMem  =  &pMixer->mems[pMixer->usCnt];		
									 //  memset(  pMem,  0,  sizeof(  pMem[0]  )  );
									 //  pMem->idInfo.ui64Id  =  pContentElem->transferAudioData.mems[i].idInfo.ui64Id;									 	
									 memcpy(  pMem,  &pContentElem->transferAudioData.mems[i],  sizeof(  pMem[0]  )  );
									 if  (  pMsgElem->data.route.debugInfo.dwTickCnt_peer_recved  )  {	//  Õâ¸öÌõ¼þÅÅ³ýÁË±¾µØ·¢¹ýÀ´µÄÒôÆµ								
										 pMem->tmpInternal.dwTickCnt_videoConferenceRecved  =  pMsgElem->data.route.debugInfo.dwTickCnt_peer_recved;
										 }												
									 else  {
										   pMem->tmpInternal.dwTickCnt_videoConferenceRecved  =  GetTickCount(  );																		
									 }								
									 pMem->tmpInternal.uiTranNo_org  =  pMsgElem->uiTranNo;
								
									 //  pMem->uiLen  =  min(  sizeof(  pMem->buf  ),  pContentElem->transferAudioData.mems[0].uiLen  );			//  ÕâÀïÔÝÊ±Ö»¿¼ÂÇÖ±½Ó·¢ËÍµÄÇé¿ö£¬ËùÒÔÖ»ÓÐ1¸öÊý¾Ý°ü
									 //  memcpy(  pMem->buf,  pContentElem->transferAudioData.mems[0].buf,  pMem->uiLen  );
									 //
									 memcpy(  pMixer->buf  +  pMixer->uiLen,  pContentElem->transferAudioData.buf  +  iPos,  pMem->uiLen  );
									 pMixer->uiLen  +=  pMem->uiLen;

									 pMixer->usCnt  ++  ;
	
								}

								if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewAudioStatus  )  {
									qyShowInfo1(  CONST_qyShowType_detail,  0,(char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer_a ok: mixer.usCnt %d, mixer.uiLen %d"  ),  pMixer->usCnt,  pMixer->uiLen  );
								}
					  
							}
							break;
					default:
							break;
				  }


				  pMsgElem->tStartTime_processed  =  pTranInfo->tNow;
				  pMsgElem->uiTranNo_processed  =  pTranInfo->uiTranNo;

				  pTranInfo->nNodes_processed  ++  ;

				  }
				  break;
			default:
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "ÔÚtmpHandler_toMixerÀï³öÏÖÁËÎ´´¦ÀíµÄÏûÏ¢ÀàÐÍ, %s"  ),  qyGetDesByType1(  CONST_misMsgTypeTable,  (  (  MIS_MSGU  *  )pMsgElemParam  )->uiType  )  );
					goto  errLabel;
					break;					  
		
	}

#if  0
	if  (  pTranInfo->nNodes_processed  >=  pProcInfo->cfg.uiMaxSendMsgs  )  {
		iErr  =  1;  goto  errLabel;
	}
#endif
	if  (  getQ2Nodes_toPostMsg(  &pChannel->outputQ2  )  >  MAX_outputQ2Nodes_toPostQ  )  {
		iErr  =  1;  goto  errLabel;
	}





	//
	iErr  =  0;
errLabel:
	return  iErr;
}


//
 int  tmpHandler_toMixer_video(  void  *  p0,  void  *  p1,  void  *  pMsgElemParam  )
{
	int								iErr						=	-1;
	COMMON_PARAM				*	pCommonParam0				=	(  COMMON_PARAM  *  )p0;
	COMMON_PARAM				*	pCommonParam1				=	(  COMMON_PARAM  *  )p1;

	COMMON_PARAM				*	pCommonParam0_toSend		=	(  COMMON_PARAM  *  )pCommonParam0->p0;
	//MIS_MSG_TASK				*	pMsgTask_av					=	(  MIS_MSG_TASK  *  )pCommonParam0->p1;
	TASK_common *taskElem=(TASK_common*)pCommonParam0->p1;
	
	MC_VAR_isCli				*	pProcInfo					=	(  MC_VAR_isCli  *  )pCommonParam0_toSend->p0;
	MIS_CNT						*	pMisCnt						=	(  MIS_CNT  *  )pCommonParam0_toSend->p1;
	MIS_CHANNEL					*	pChannel					=	(  MIS_CHANNEL  *  )pCommonParam0_toSend->p2;

	QY_MC						*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;

	//
	QMC_TASK_INFO * pTaskInfo=(QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, taskElem->m_index_taskInfo);
	if(pTaskInfo==NULL)return -1;
	MIS_MSG_TASK *pMsgTask_av=&pTaskInfo->var.pTaskData->msgU.task;
	if(pMsgTask_av->uiType!=CONST_misMsgType_task)return -1;


	//
	IM_CONTENTU					*	pContent_av					=	(  IM_CONTENTU  *  )pMsgTask_av->data.buf;
	AV_TRAN_INFO				*	pAvTran						=	NULL;
	PROC_TASK_AV				*	pTask						=	NULL;

	if  (  pContent_av->uiType  ==  CONST_imCommType_transferAvInfo  )  {
		if(!pTaskInfo->var.m_bReplyTask ) {

		//
		TASK_transferAv * task=(TASK_transferAv*)taskElem;
		//
		pAvTran  =  &pContent_av->transferAvInfo.ass.tranInfo;
		pTask  =  &task->myTask;//get_transferAvInfo_pTask(  &pContent_av->transferAvInfo,  _T(  ""  )  );  //  &pTransferAvTask->myTask;
		if  (  !pTask  )  return  -1;
		}
		else {
		
		//else  if (  pContent_av->uiType  ==  CONST_imCommType_transferAvReplyInfo  )  
			
		TASK_transferAv * task=(TASK_transferAv*)taskElem;
			 pTask  =  &task->myTask;//get_transferAvReplyInfo_pTask(  &pContent_av->transferAvReplyInfo,  _T(  ""  )  );	//  &pContent_av->transferAvReplyInfo.myTask;							
			 if  (  !pTask  )  return  -1;
			 //pAvTran  =  &pContent_av->transferAvReplyInfo.tranInfo;					  					  
			 pAvTran=&pTask->reply_avTranInfo;

	}
	}
	if  (  !pAvTran  )  return  -1;
				
	TRAN_INFO_MIS				*	pTranInfo					=	(  TRAN_INFO_MIS  *  )pCommonParam1->p0;
	MIS_MSG_TASK				*	pMsgTask_o					=	&pTranInfo->pMsg_o->task;
	
	MIS_MSG_TASK				*	pMsgMixer					=	(  MIS_MSG_TASK  *  )pCommonParam1->p1;
	TRANSFER_VIDEO_DATA			*	pMixer						=	(  TRANSFER_VIDEO_DATA  *  )pMsgMixer->data.buf;


	switch  (  (  (  MIS_MSGU  *  )pMsgElemParam  )->uiType  )  {
			case  CONST_misMsgType_task:  {
				  MIS_MSG_TASK			*	pMsgElem		=	(  MIS_MSG_TASK  *  )pMsgElemParam;
				  MIS_CNT				*	pMisCntElem		=	(  MIS_CNT  *  )pMsgElem->pMisCnt;
				  IM_CONTENTU			*	pContentElem	=	(  IM_CONTENTU  *  )pMsgElem->data.buf;

				  pMsgElem->nTimes_tryToSend  ++  ;
				  
				  switch  (  pContentElem->uiType  )  {
						  case  CONST_imCommType_transferVideoData:  {
									   
							    if  (  !pMsgMixer->uiType  )  {
									tmpInitMsgMixer(  pProcInfo,  pMisCnt,  pMsgTask_av,  pAvTran,  pTask,  CONST_imCommType_transferVideoData,  pMsgElem,  pMsgMixer  );
									//
								}
								if  (  pMixer->uiTranNo_openAvDev  !=  pContentElem->transferVideoData.uiTranNo_openAvDev  )  {
									if  (  pMixer->usCnt  )  {										 
											 if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewVideoStatus  )  {
												 //qyShowInfo1(  CONST_qyShowType_detail,  0,(char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer_video: flush mixer data. mixer.usCnt %d, mixer.uiLen %d,  mem.len %d."  ),  pMixer->usCnt,  pMixer->uiLen,  pContentElem->transferVideoData.mems[i].uiLen  );
											 }

											 tmpHandler_toSend(  pCommonParam0_toSend,  p1,  pMsgMixer  );
										 }

										 MACRO_memset_misMsgTask(  pMsgMixer  );
										 if  (  !pMsgMixer->uiType  )  {										 
											 tmpInitMsgMixer(  pProcInfo,  pMisCnt,  pMsgTask_av,  pAvTran,  pTask,  CONST_imCommType_transferVideoData,  pMsgElem,  pMsgMixer  );
										 }
								}

								//  È»ºó°ÑÊý¾Ý¼Óµ½»º³åÀï
								if  (  pMixer->usCnt  >  mycountof(  pMixer->mems  )  )  {						//  Êµ¼ÊÕâÀïÊÇ²»¶ÔµÄ£¬°´Àí²»ÄÜÓÐÕâÑùµÄÇé¿ö³öÏÖ, ÒòÎª
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer_video failed:  pMixer->usCnt %d >= mems %d."  ),  pMixer->usCnt,  mycountof(  pMixer->mems  )  );
									goto  errLabel;
								}
								if  (  !pContentElem->transferVideoData.usCnt  )  {
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer_video:  transferVideoData.usCnt is 0."  )  );
									break;
								}
								if  (  pContentElem->transferVideoData.usCnt  >  mycountof(  pContentElem->transferVideoData.mems  )  )  {
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer_video failed:  transferVideoData.usCnt %d >= mems %d."  ),  pContentElem->transferVideoData.usCnt,  mycountof(  pContentElem->transferVideoData.mems  )  );
									goto  errLabel;
								}	
								if  (  pContentElem->transferVideoData.uiLen  >  sizeof(  pContentElem->transferVideoData.buf  )  )  {
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer_video failed:  transferVideoData.uiLen %d too big."  ),  pContentElem->transferVideoData.uiLen  );
									goto  errLabel;
								}

								int								i;
								TRANSFER_VIDEO_dataMemHead	*	pMem;
								int								iPos;

								for  (  iPos  =  0,  i  =  0;  i  <  pContentElem->transferVideoData.usCnt;  iPos  +=  pContentElem->transferVideoData.mems[i].uiLen,  i  ++  )  {
									 //
									 if  (  iPos  +  pContentElem->transferVideoData.mems[i].uiLen  >  pContentElem->transferVideoData.uiLen  )  {
										 traceLogA(  (char*)  "tmpHandler_toMixer_video failed: iPos + mems[i].uiLen > content.uiLen"  );
										 goto  errLabel;
									 }

									 //
									 if  (  pMixer->usCnt  ==  mycountof(  pMixer->mems  )  
										 ||  pContentElem->transferVideoData.mems[i].uiLen  +  pMixer->uiLen  >  sizeof(  pMixer->buf  )  
										 //||  pContentElem->transferVideoData.stat.tSelectTime		//  2011/01/25. 对需要对方发送响应包的请求包，应改独立发送。所以先发送其他的包，然后独立发送此包
										 )  
									 {
										 if  (  pMixer->usCnt  )  {										 
											 if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewVideoStatus  )  {
												 qyShowInfo1(  CONST_qyShowType_detail,  0,(char*)  (char*)"",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer_video: flush mixer data. mixer.usCnt %d, mixer.uiLen %d,  mem.len %d."  ),  pMixer->usCnt,  pMixer->uiLen,  pContentElem->transferVideoData.mems[i].uiLen  );
											 }

											 tmpHandler_toSend(  pCommonParam0_toSend,  p1,  pMsgMixer  );
										 }

										 MACRO_memset_misMsgTask(  pMsgMixer  );
										 if  (  !pMsgMixer->uiType  )  {										 
											 tmpInitMsgMixer(  pProcInfo,  pMisCnt,  pMsgTask_av,  pAvTran,  pTask,  CONST_imCommType_transferVideoData,  pMsgElem,  pMsgMixer  );
										 }
									 }

									 //
									 pMem  =  &pMixer->mems[pMixer->usCnt];		
									 memcpy(  pMem,  &pContentElem->transferVideoData.mems[i],  sizeof(  pMem[0]  )  );
								
									 //
									 memcpy(  pMixer->buf  +  pMixer->uiLen,  pContentElem->transferVideoData.buf  +  iPos,  pMem->uiLen  );
									 pMixer->uiLen  +=  pMem->uiLen;

									 pMixer->usCnt  ++  ;
	
									 //  2011/01/26
									 #ifdef  __DEBUG__
											 pTask->photomosaic.stat.usCnt_pkts  ++  ;
											 //
											 //
											 if  (  pMem->stat.tSelectTime  )  {
												 int  ii  =  0;
												 //showInfo_open0(  0,  0,  _T(  "mixer: tSelectTime is not 0"  )  );
											 }

									 #endif

									 //								 		
									 //  2011/01/25. 对需要对方发送统计响应包的请求包，单独发送此包
								#if  0
									 if  (  pContentElem->transferVideoData.stat.tSelectTime  )  
									 {
										 #ifdef  __DEBUG__
												#if  0
												 if  (  pTask->photomosaic.stat.tSelectTime  !=  pContentElem->transferVideoData.stat.tSelectTime  )  {
													 pTask->photomosaic.stat.tSelectTime  =  pContentElem->transferVideoData.stat.tSelectTime;
													 pTask->photomosaic.stat.usCnt_pkts  =  1;
												 }

											     if  (  pTask->photomosaic.stat.usCnt_pkts  !=  pContentElem->transferVideoData.stat.usCnt_pkts  )  {
													 traceLog((TCHAR*)  _T(  "usCnt_pkts not same. photomosaic.%d != contentElem.%d"  ),  (  int  )pTask->photomosaic.stat.usCnt_pkts,  (  int  )pContentElem->transferVideoData.stat.usCnt_pkts  );
												 }
												 else  traceLog((TCHAR*)  _T(  "usCnt_pkts is same, %d"  ),  (  int  )pTask->photomosaic.stat.usCnt_pkts  );
												#endif
										 #endif

										 if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewAudioStatus  )  {
											 qyShowInfo1(  CONST_qyShowType_detail,  0,(char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer_video: flush mixer data. mixer.usCnt %d, mixer.uiLen %d,  mem.len %d."  ),  pMixer->usCnt,  pMixer->uiLen,  pContentElem->transferVideoData.mems[i].uiLen  );
										 }

										 //
										 memcpy(  &pMixer->stat,  &pContentElem->transferVideoData.stat,  sizeof(  pMixer->stat  )  );

										 //
										 tmpHandler_toSend(  pCommonParam0_toSend,  p1,  pMsgMixer  );

										 MACRO_memset_misMsgTask(  pMsgMixer  );
										 if  (  !pMsgMixer->uiType  )  {										 
											 tmpInitMsgMixer(  pProcInfo,  pMisCnt,  pMsgTask_av,  pAvTran,  pTask,  CONST_imCommType_transferVideoData,  pMsgElem,  pMsgMixer  );
										 }
									 }
								#endif
									 //
									 continue;
								}

								if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewVideoStatus  )  {
									qyShowInfo1(  CONST_qyShowType_detail,  0,(char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHadler_toMixer_v ok: mixer.usCnt %d, mixer.uiLen %d, tn_openAv_org %d"  ),  pMixer->usCnt,  pMixer->uiLen,  pMixer->uiTranNo_openAvDev  );
								}
					  
							}
							break;
					default:
							break;
				  }


				  pMsgElem->tStartTime_processed  =  pTranInfo->tNow;
				  pMsgElem->uiTranNo_processed  =  pTranInfo->uiTranNo;

				  pTranInfo->nNodes_processed  ++  ;

				  }
				  break;
			default:
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "ÔÚtmpHandler_toMixerÀï³öÏÖÁËÎ´´¦ÀíµÄÏûÏ¢ÀàÐÍ, %s"  ),  qyGetDesByType1(  CONST_misMsgTypeTable,  (  (  MIS_MSGU  *  )pMsgElemParam  )->uiType  )  );
					goto  errLabel;
					break;					  
		
	}


#if  0
	if  (  pTranInfo->nNodes_processed  >=  pProcInfo->cfg.uiMaxSendMsgs  )  {
		iErr  =  1;  goto  errLabel;
	}
#endif
	//
	if  (  getQ2Nodes_toPostMsg(  &pChannel->outputQ2  )  >  MAX_outputQ2Nodes_toPostQ  )  {
		iErr  =  1;  goto  errLabel;
	}


	iErr  =  0;
errLabel:
	return  iErr;
}

 int  tmpHandler_toSendMedia(  QY_MC  *  pQyMc,  void  *  p0,  void  *  p1,  TASK_common  *  taskElemParam  )
{
	int								iErr				=	-1;
	COMMON_PARAM	*				pCommonParam0		=	(  COMMON_PARAM  *  )p0;
	COMMON_PARAM	*				pCommonParam1		=	(  COMMON_PARAM  *  )p1;

	MC_VAR_isCli		*				pProcInfo			=	(  MC_VAR_isCli  *  )pCommonParam0->p0;
	MIS_CNT			*				pMisCnt				=	(  MIS_CNT  *  )pCommonParam0->p1;
	MIS_CHANNEL		*				pChannel			=	(  MIS_CHANNEL  *  )pCommonParam0->p2;
	//
	TRAN_INFO_MIS	*				pTranInfo			=	(  TRAN_INFO_MIS  *  )pCommonParam1->p0;
	MIS_MSG_TASK	*				pMsgTask_o			=	&pTranInfo->pMsg_o->task;

	MIS_MSG_TASK	*				pMsgMixer			=	(  MIS_MSG_TASK  *  )pCommonParam1->p1;
	IM_CONTENTU		*				pContent_mixer		=	(  IM_CONTENTU  *  )pMsgMixer->data.buf;

	COMMON_PARAM					commonParam0;
	int								tmpiRet				=	-1;

	if  (  !pProcInfo  ||  !pMisCnt  ||  !pChannel  ||  !pMsgTask_o  ||  !pMsgMixer  )  {
		traceLogA(  (char*)  "tmpHandler_toSendMedia failed. params error."  );
		return  -1;
	}

	LPCTSTR  where_showInfo;	where_showInfo	=  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  );

	//
	TASK_common * taskElem=(TASK_common*)taskElemParam;
	QMC_TASK_INFO * pTaskInfo=(QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, taskElem->m_index_taskInfo);
	if(pTaskInfo==NULL)return -1;
	MIS_MSGU * pMsgElemParam=&pTaskInfo->var.pTaskData->msgU;

	//
	switch  (  (  (  MIS_MSGU  *  )pMsgElemParam  )->uiType  )  {
			case  CONST_misMsgType_task:  {
				  MIS_MSG_TASK			*	pMsgElem		=	(  MIS_MSG_TASK  *  )pMsgElemParam;
				  MIS_CNT				*	pMisCntElem		=	(  MIS_CNT  *  )pMsgElem->pMisCnt;
				  IM_CONTENTU			*	pContentElem	=	(  IM_CONTENTU  *  )pMsgElem->data.buf;
				  //

				  if  (  pMisCntElem  ==  pMisCnt  )  {
					  if  (  pChannel->uiType  ==  CONST_channelType_realTimeMedia  )  {
						  AV_TRAN_INFO	*	pAvTranInfo  =  NULL;
						  PROC_TASK_AV	*	pTask  =  NULL;

						  if  (  pContentElem->uiType  ==  CONST_imCommType_transferAvInfo  )  {
							  if(!pTaskInfo->var.m_bReplyTask) {
								  TASK_transferAv * task=(TASK_transferAv*)taskElem;
							  pAvTranInfo		=	&pContentElem->transferAvInfo.ass.tranInfo;
							  pTask			=	&task->myTask;//get_transferAvInfo_pTask(  &pContentElem->transferAvInfo,  _T(  "tmpHandler_toSendMedia"  )  );  //  &pContentElem->transferAvInfo.myTask;						  
							  if  (  !pTask  )  goto  errLabel;
							  }
							  else {
							  
						  //else  if  (  pContentElem->uiType  ==  CONST_imCommType_transferAvReplyInfo  )  
								  TASK_transferAv *task=(TASK_transferAv*)taskElem;
									pTask			=	&task->myTask;//get_transferAvReplyInfo_pTask(  &pContentElem->transferAvReplyInfo,  _T(  ""  )  );  //  &pContentElem->transferAvReplyInfo.myTask;						  							        
									if  (  !pTask  )  goto  errLabel;
									pAvTranInfo		=	&pTask->reply_avTranInfo;//&pContentElem->transferAvReplyInfo.tranInfo;

						  }
						  }

						  if  (  pAvTranInfo  )  {
							  CQyQ2Help			q2Help;
							  GENERIC_Q		*	pOutputQ_audio	=	q2Help.getQ_toGetMsg(  pTask->mixer.pOutputQ2,  _T(  "tmpHandler_toSendMedia"  ));

							  if  (  !pOutputQ_audio  )  {				//  ²»ÊÇÊÓÆµ·þÎñÆ÷£¬¾ÍÃ»ÓÐÊä³ö¶ÓÁÐ¡£
								  iErr  =  0;  goto  errLabel;
							  }
							  
							  MACRO_memset_misMsgTask(  pMsgMixer  );	//  Çå¿Õ

							  //MACRO_makeCommonParam3(  p0,  pMsgElem,  0,  commonParam0  );
							  MACRO_makeCommonParam3(  p0,  taskElem,  0,  commonParam0  );
							  tmpiRet  =  qTraverse(  pOutputQ_audio,  tmpHandler_toMixer_audio,  &commonParam0,  p1  );
							  if  (  tmpiRet  <  0  )  {
								  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "tmpHandler_toMixer_audio failed. ½«empty¶ÓÁÐ"  )  );
								  emptyGenericQ(  pOutputQ_audio  );
								  iErr  =  0;  goto  errLabel;
							  }

							  //  ÕâÀï,»¹Òª°ÑÎ´·¢ËÍµÄÊý¾Ý°ü·Åµ½·¢ËÍ¶ÓÁÐÀï."  );
							  if  (  pMsgMixer->uiType  ==  CONST_misMsgType_task
								  &&  pContent_mixer->uiType  ==  CONST_imCommType_transferAudioData
									&&  pContent_mixer->transferAudioData.usCnt  )  
							  {
								  tmpHandler_toSend(  p0,  p1,  pMsgMixer  );
							  }

							  if  (  qRemoveMsg(  pOutputQ_audio,  tmpHandler_needRemoveMsg_cli,  0,  p1  )  <  0  )  {
								  traceLogA(  (char*)  "Çå³ýÀ¬»ø°ü³ö´í¡£skipped."  );			 
							  }
							  
							#if  0
							  if  (  pTranInfo->nNodes_processed  >=  pProcInfo->cfg.uiMaxSendMsgs  )  {
								  iErr  =  1;  goto  errLabel;	//  Õâ±íÃ÷ÒÑ¾­´¦ÀíÍêÁË, Ò»¹²´Õ¹»ÁËÈô¸É°ü·ÅÈë·¢ËÍ¶ÓÁÐ
							  }
							#endif
							  //
							  if  (  getQ2Nodes_toPostMsg(  &pChannel->outputQ2  )  >  MAX_outputQ2Nodes_toPostQ  )  {
								  iErr  =  1;  goto  errLabel;
							  }
							
							  //
							  iErr  =  0;  goto  errLabel;
				
						  }
						  
					  }

					  if  (  pChannel->uiType  ==  CONST_channelType_media  )  {					  
						  AV_TRAN_INFO	*	pAvTranInfo  =  NULL;
						  PROC_TASK_AV	*	pTask  =  NULL;

						  if  (  pContentElem->uiType  ==  CONST_imCommType_transferAvInfo  )  {
							  if(!pTaskInfo->var.m_bReplyTask) {
								  TASK_transferAv *task=(TASK_transferAv*)taskElem;
							  pAvTranInfo		=	&pContentElem->transferAvInfo.ass.tranInfo;
							  pTask			=	&task->myTask;//get_transferAvInfo_pTask(  &pContentElem->transferAvInfo,  _T(  ""  )  );	//  &pContentElem->transferAvInfo.myTask;						  
							  if  (  !pTask  )  goto  errLabel;
							  }
						  else  {
							    //if  (  pContentElem->uiType  ==  CONST_imCommType_transferAvReplyInfo  )  
							  TASK_transferAv * task=(TASK_transferAv*)taskElem;
							        pTask			=	&task->myTask;//get_transferAvReplyInfo_pTask(  &pContentElem->transferAvReplyInfo,  _T(  ""  )  );  //  &pContentElem->transferAvReplyInfo.myTask;						  							        
									if  (  !pTask  )  goto  errLabel;
									pAvTranInfo		=	&pTask->reply_avTranInfo;//&pContentElem->transferAvReplyInfo.tranInfo;
									
						  }
						  }

						  //
						  if  (  pAvTranInfo  )  {
							  CQyQ2Help			q2Help;
							  GENERIC_Q		*	pOutputQ_video	=	q2Help.getQ_toGetMsg(  pTask->photomosaic.pOutputQ2,  _T(  "tmpHandler_toSendMedia 2"  ));

							  if  (  !pOutputQ_video  )  {				//  ²»ÊÇÊÓÆµ·þÎñÆ÷£¬¾ÍÃ»ÓÐÊä³ö¶ÓÁÐ¡£
								  iErr  =  0;  goto  errLabel;
							  }
							  
							  MACRO_memset_misMsgTask(  pMsgMixer  );	//  Çå¿Õ

							  //MACRO_makeCommonParam3(  p0,  pMsgElem,  0,  commonParam0  );
							  MACRO_makeCommonParam3(  p0,  taskElem,  0,  commonParam0  );							  
							  tmpiRet  =  qTraverse(  pOutputQ_video,  tmpHandler_toMixer_video,  &commonParam0,  p1  );
							  if  (  tmpiRet  <  0  )  {
								  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "tmpHandler_toMixer_video failed. ½«empty¶ÓÁÐ"  )  );
								  emptyGenericQ(  pOutputQ_video  );
								  iErr  =  0;  goto  errLabel;
							  }

							  //  ÕâÀï,»¹Òª°ÑÎ´·¢ËÍµÄÊý¾Ý°ü·Åµ½·¢ËÍ¶ÓÁÐÀï."  );
							  if  (  pMsgMixer->uiType  ==  CONST_misMsgType_task
								  &&  pContent_mixer->uiType  ==  CONST_imCommType_transferVideoData
									&&  pContent_mixer->transferVideoData.usCnt  )  
							  {
								  tmpHandler_toSend(  p0,  p1,  pMsgMixer  );
							  }

							  if  (  qRemoveMsg(  pOutputQ_video,  tmpHandler_needRemoveMsg_cli,  0,  p1  )  <  0  )  {
								  traceLogA(  (char*)  "Çå³ýÀ¬»ø°ü³ö´í¡£skipped."  );			 
							  }
							  
							#if  0
							  if  (  pTranInfo->nNodes_processed  >=  pProcInfo->cfg.uiMaxSendMsgs  )  {
								  iErr  =  1;  goto  errLabel;	//  Õâ±íÃ÷ÒÑ¾­´¦ÀíÍêÁË, Ò»¹²´Õ¹»ÁËÈô¸É°ü·ÅÈë·¢ËÍ¶ÓÁÐ
							  }
							#endif
							  //
							  if  (  getQ2Nodes_toPostMsg(  &pChannel->outputQ2  )  >  MAX_outputQ2Nodes_toPostQ  )  {
								  iErr =  1;  goto  errLabel;
							  }

							
							  //
							  iErr  =  0;  goto  errLabel;
				
						  }
					  }
				  }
				
				  iErr  =  0;  goto  errLabel;
				
				}	
				break;
			default:
					break;
	}


	iErr  =  0;
errLabel:
	return  iErr;

}






 //  2008/05/2
 extern "C" DWORD WINAPI mcThreadProc_mis_toSend( LPVOID lpParameter )
{
	 MIS_CHANNEL				*	pChannel			=	(  MIS_CHANNEL  *  )lpParameter;
	 if  (  !pChannel  )  {
		 return  -1;
	 }
	 MIS_CNT					*	pMisCnt				=	pChannel->pMisCnt;
	 if  (  !pMisCnt  )  return  -1;
	 MC_VAR_isCli				*	pProcInfo			=	(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	 if  (  !pProcInfo  )  return  -1;
	 QY_MC						*	pQyMc				=	pProcInfo->pQyMc;
	 if  (  !pQyMc  )  return  -1;
	 //
	 int							loopCtrl			=	0;
	 int							i;
	 int							j;
	 DWORD							dwThreadId			=	GetCurrentThreadId(  );
	 DWORD							dwRet;
	 //  unsigned  int					len;
	 CQyMalloc						mallocObj;
	 MIS_MSGU					*	pMsg_o				=	NULL;
	 //  int							iRet;
	 //  BOOL							bThreadIdFound		=	FALSE;
	 COMMON_PARAM					commonParam0;
	 COMMON_PARAM					commonParam1;
	 //  nNodes_processed
	 int							tmpiRet				=	-1;
	 TRAN_INFO_MIS					tranInfo;
	 //
	 CQyMalloc						mallocObj_mixer;
	 MIS_MSG_TASK				*	pMsgMixer			=	NULL;


	 //LPCTSTR  where_showInfo;	where_showInfo	=  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  );

	 TCHAR  where_showInfo[128];
	 _sntprintf(where_showInfo, mycountof(where_showInfo), _T("%s_toS"), qyGetDesByType1(CONST_channelTypeTable, pChannel->uiType));

	 //
	 showInfo_open0(0, where_showInfo, _T("starts"));

	 //
#ifdef  __DEBUG__
	 traceLog(  (TCHAR*)_T("%s: mcThreadProc_mis_toSend:  enters"  ),  where_showInfo  );
#endif 
 
	 //
#if  0
	 for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  {
		  pMisCnt  =  &pProcInfo->misCnts[i];
		  if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;
		  //
		  for  (  j  =  0;  j  <  mycountof(  pMisCnt->channels  );  j  ++  )  {
			   pChannel  =  &pMisCnt->channels[j];
			   if  (  !pChannel->dwThreadId_toSend  )  continue;
			   if  (  pChannel->dwThreadId_toSend  ==  dwThreadId  )  {
				   bThreadIdFound  =  TRUE;  break;
			   }
		  }
		  //
		  if  (  bThreadIdFound  )  break;
	 }

	 if  (  !bThreadIdFound  )  {
		 traceLogA(  (char*)  "Error:  msgCnt not found."  );  goto  errLabel;
	 }
#endif


	 if  (  !(  pMsg_o  =  (  MIS_MSGU  *  )mallocObj.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  )  )  )  goto  errLabel;
	 switch  (  pChannel->uiType  )  {
			 case  CONST_channelType_realTimeMedia:
			 case  CONST_channelType_media:
				   if  (  !(  pMsgMixer  =  (  MIS_MSG_TASK  *  )mallocObj_mixer.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSG_TASK  )  )  )  )  goto  errLabel;
				   break;
			 default:
					 break;
	 }

	
	 //
	GENERIC_Q* pToSendQ;pToSendQ = NULL;	//  2011/01/23

	{
		Param_dbg param;
		param.m_pHint = (TCHAR*)_T("tosend.1257");
		//
		for (; bChannelOk(pChannel, &param); loopCtrl++) {

			dwRet = WaitForSingleObject(pChannel->toSendQ2.hEvents[0], 3500);	//  µÈ·¢ËÍÖ¸Áî
			if (dwRet == WAIT_FAILED)  goto  errLabel;							//  ÎªÁË·ÀÖ¹¶ª°ü£¬ÕâÀï²»ÅÐ¶Ï³¬Ê±£¬ÒÔoutputQÀïµÄÊý¾Ý°üÎª×¼
			//if  (  dwRet  ==  WAIT_TIMEOUT  )  continue;
#ifdef  __DEBUG__
		//  traceLog((TCHAR*)  _T(  "toSend: sth waited"  )  );
#endif

			q2AvoidTriggerTooHigh(0, &pChannel->toSendQ2);

			if (getQ2Nodes_toPostMsg(&pChannel->outputQ2) > MAX_outputQ2Nodes_toPostQ)  continue;					//  Êä³ö¶ÔÁÐÀï³¬¹ý20¸öÊý¾Ý°ü£¬¾Í²»ÓÃ×ª»»ÁË

			memset(&tranInfo, 0, sizeof(tranInfo));
			tranInfo.uiTranNo = getuiNextTranNo(0, 0, 0);
			if (tranInfo.uiTranNo == -1)  goto  errLabel;
			mytime(&tranInfo.tNow);
			tranInfo.pMsg_o = pMsg_o;

			MACRO_makeCommonParam3(pProcInfo, pMisCnt, pChannel, commonParam0);
			MACRO_makeCommonParam3(&tranInfo, pMsgMixer, 0, commonParam1);

			if (pChannel->uiType == CONST_channelType_realTimeMedia) {

				tmpiRet = pProcInfo->processQ_media.qTraverse(tmpHandler_toSendMedia, &commonParam0, &commonParam1);
				if (tmpiRet < 0) {
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("mcThreadProc_mis_toSend: tmpHandler_toSendMedia failed."));
					goto  errLabel;
				}

			}
			if (pChannel->uiType == CONST_channelType_media) {

				tmpiRet = pProcInfo->processQ_media.qTraverse(tmpHandler_toSendMedia, &commonParam0, &commonParam1);
				if (tmpiRet < 0) {
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("mcThreadProc_mis_toSend: tmpHandler_toSendMedia failed."));
					goto  errLabel;
				}

			}


			//  printQ_mis(  pToSendQ  );

			tranInfo.uiMaxSendMsgs = 4;	//  
			do {
				if (!pToSendQ || isQEmpty(pToSendQ)) {
					CQyQ2Help		q2Help;
					pToSendQ = q2Help.getQ_toGetMsg(&pChannel->toSendQ2, _T("mcThreadProc_mis_toSend"));
					if (!pToSendQ)  break;

					if (isQEmpty(pToSendQ))  break;
				}

				tmpiRet = qTraverse(pToSendQ, tmpHandler_toSend, &commonParam0, &commonParam1);
				if (tmpiRet < 0) {
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("mcThreadProc_mis_toSend: tmpHandler_toSendMedia failed."));
					//goto  errLabel;
				}
				if (qRemoveMsg(pToSendQ, tmpHandler_needRemoveMsg_cli, 0, &commonParam1) < 0) {
					traceLog((TCHAR*)_T("qRemoveMsg pToSendQ failed, skipped."));
				}
				//
				//if  (  !(  tranInfo.nNodes_processed1  <  pProcInfo->cfg.uiMaxSendMsgs  )  )  break;
				if (getQ2Nodes_toPostMsg(&pChannel->outputQ2) > MAX_outputQ2Nodes_toPostQ) {
					break;
				}
			} while (true);

			//  printQ_mis(  &pChannel->toSendQ  );	 

		}
	}

errLabel:

	 //
	 showInfo_open0(  0,  where_showInfo,  _T(  "ends"  )  );

	 //
	 if  (  pMisCnt  )  {
		 pChannel->status.ulbSessionErr  =  TRUE;
		 pChannel->status.ulbToSendQuit  =  TRUE;
	 }

	 //
#ifdef  __DEBUG__
	 traceLog(  (TCHAR*)  _T( "%s: mcThreadProc_mis_toSend:  leaves"  ), where_showInfo );
#endif 

	 //
	 return  0;
}
