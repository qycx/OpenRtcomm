
#include	"stdafx.h"
#include	<stdio.h>
#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
	#include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>
#include	<stddef.h>

#include	"qyMcMainCommon.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"

#include	"myDb.h"

#include	"qmcCommFunc_isCli.h"
#include	"qmcTaskInfo.h"
#include    <vector>



bool  canSend(  QY_SHARED_OBJ  *  pSharedObj,  QMC_taskData_conf  *  pTc  )
{
	bool  bRet  =  true;

	switch  (  pSharedObj->uiType1  )  {
			case  0:
				   if  (  pTc->ucbNotSendData  )  {
					   bRet  =  false;
				   }
				   break;
			default:
					break;
	}

	return  bRet;
}



 //  
#if  0
int  old_tmpHandler_findOrgMsgAndProcess_mis_procTaskAudioData(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr,  int  iTaskId,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_AUDIO_DATA  *  pTransferAudioData,  IM_CONTENTU  *  pContentElem,  PROC_TASK_AV  *  pTask  )
{
	int	iErr	=	-1;
	int	index	=	0;
	MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	if  (  !pMisCnt  )  {
		traceLog((TCHAR*)  _T(  "tmpHandler_findOrgMsgAndProcess_mis_procTaskVideoData failed, pMisCnt is null"  )  );
		return  -1;
	}
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	//
	if  (  pTask->ucbVideoConferenceStarter  )  {									
		int	index_activeMems_from	=	0;

		//  search in activeMems_from first
		for  (  index_activeMems_from  =  0;  index_activeMems_from  <  pTc->videoConference.usCntLimit_activeMems_from;  index_activeMems_from  ++  )  {
			if  (  pTc->videoConference.activeMems_from[index_activeMems_from].mem.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id  )  break;						
		}
		//  use searched index to process video
		if  (  index_activeMems_from  <  pTc->videoConference.usCntLimit_activeMems_from  )  {												
			index  =  pTc->videoConference.activeMems_from[index_activeMems_from].mem.usIndex_pMems_from;							
			if  (  index  >=  0  &&  index  <  pTc->videoConference.usCntLimit_mems_from  )  {
				TASK_AV_FROM  *  pFrom  =  &pTc->videoConference.pMems_from[index];
				//
				if  (  pFrom->idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id							
					&&  pFrom->audio.ta_recvd.uiTranNo_openAvDev  ==  pTransferAudioData->uiTranNo_openAvDev  )
				{			
					#ifdef  __DEBUG__
							//  traceLogA(  (char*)  "AudioData: usCntLimit_mems_from %d, usCntLimit_activeMems_from %d, video conference starter",  pTransferAvInfoElem->myTask.usCntLimit_mems_from,  pTransferAvInfoElem->myTask.usCntLimit_activeMems_from  );
					#endif
					//  if  (  procTaskAudio(  pProcInfo,  &pMsgElem->addr_logicalPeer,  pMsgTask,  &pContent->transferAudioData,  &pTransferAvInfoElem->tranInfo,  &pTransferAvInfoElem->myTask,  index,  index_activeMems_from  )  )  goto  errLabel;

					pTransferAudioData->tmpInternal.param.index_pMems_from  =  index;
					pTransferAudioData->tmpInternal.param.index_activeMems_from  =  index_activeMems_from;
														
					/*
					QY_TRANSFORM  *  pTransform  =  MACRO_getTransform(  *pTask,  pTransferAudioData->tmpInternal.param.index_activeMems_from  );
					if  (  pTransform  )  {
						//  qPostMsgAndTrigger_toDo(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->audio  );
						q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->audio.q2  );
					}
					*/
					QIS_DISPATCH	*	pDispatch  =  MACRO_getDispatch(  *pTask,  index_activeMems_from  );
					if  (  pDispatch  )  {
						q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pDispatch->audio.q2  );
					}

					iErr  =  1;  goto  errLabel;												  
				}
			}
		}
		}
	else  if  (  pTask->ucbVideoConference  )  {

			  if  (  pMsgTask->iTaskId  ==  iTaskId  )  {
				  //  2011/01/23				  
				  if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					   //  traceLog((TCHAR*)  _T(  "audio data sent by myself"  )  );

					   q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->mixer.pOutputQ2  );
					   MIS_CHANNEL	*	pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_realTimeMedia  );
					   if  (  pChannel  )  q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2  );

					   //
					   iErr  =  1;  goto  errLabel;				   
				  }
			  }

			  //
#ifdef  __DEBUG__
			  if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  162  )  {
				  int  ii  =  0;
			  }
#endif

			  //
			  if  (  pTask->mem0_from.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id
				  &&  pTask->mem0_from.audio.ta_recvd.uiTranNo_openAvDev  ==  pTransferAudioData->uiTranNo_openAvDev  )
			  {
				   int								i						=	0;
				   int								iPos					=	0;
				   TRANSFER_AUDIO_dataMemHead	*	pMem					=	NULL;
				   int								index_activeMems_from	=	0;
				   unsigned  int					usIndex_pMems_from		=	0;
				   QY_TRANSFORM					*	pTransform				=	NULL;
				   MIS_MSG_TASK					*	pMsgTask_toTransform	=	NULL;
				   TRANSFER_AUDIO_DATA			*	pNew					=	NULL;

				   if  (  !pTask->audio.pMsgTask_toTransform  )  {
					   traceLogA(  (char*)  "findOrgMsg failed. pMsgTask_toTransform is null"  );
					   goto  errLabel;
				   }
				   pMsgTask_toTransform  =  (  MIS_MSG_TASK  *  )pTask->audio.pMsgTask_toTransform;

				   if  (  !pTransferAudioData->usCnt  )  {
					   pTransferAudioData->usCnt  =  1;	//  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
					   pTransferAudioData->mems[0].uiLen  =  pTransferAudioData->uiLen;
				   }
				   if  (  pTransferAudioData->usCnt  >  mycountof(  pTransferAudioData->mems  )  )  goto  errLabel;

				   #ifdef  __DEBUG__
						   //  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: audio len %d"  ),  pTransferAudioData->uiLen  );
				   #endif


				   for  (  iPos  =  0,  i  =  0;  i  <  pTransferAudioData->usCnt;  iPos  =  iPos  +  pTransferAudioData->mems[i].uiLen,  i  ++  )  {
					    pMem  =  &pTransferAudioData->mems[i];
						if  (  !pMem->uiLen  )  {
							//
							#ifdef  __DEBUG__
									//traceLogA(  (char*)  "findOrgMsg: transferAudioMem.uiLen is 0. skipped."  );
							#endif
							//
							continue;
						}

						if  (  iPos  +  pTransferAudioData->mems[i].uiLen  >  pTransferAudioData->uiLen  )  {
							#ifdef  __DEBUG__
									traceLogA(  (char*)  "findOrgMsg failed: iPos + mem.uiLen > data.uiLen"  );
							#endif
							goto  errLabel;
						}

						if  (  !pMem->idInfo.ui64Id  )  pMem->idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;
						for  (  index_activeMems_from  =  0;  index_activeMems_from  <  pTc->videoConference.usCntLimit_activeMems_from;  index_activeMems_from  ++  )  {
							if  (  pMem->idInfo.ui64Id  ==  pTc->videoConference.activeMems_from[index_activeMems_from].mem.idInfo.ui64Id  )  break;
						}
						if  (  index_activeMems_from  ==  pTc->videoConference.usCntLimit_activeMems_from  )  {
							#ifdef  __DEBUG__
									traceLogA(  (char*)  "findOrgMsg_procTaskAudioData: can't get index_activeMems_from, skipped."  );
							#endif
							qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: audio, can't get index_activeMems_from, skipped."  )  );

							//  2009/06/01
							if  (  pTask->ucbVideoConference  &&  !pTask->ucbVideoConferenceStarter  &&  pMsgTask->pMisCnt  )  {
								MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
								pMisCnt->refreshVideoConferenceActiveMems.iTaskId  =  iTaskId;
								pMisCnt->refreshVideoConferenceActiveMems.bNeedRefreshed  =  TRUE;
							}

							continue;
						}
						usIndex_pMems_from  =  pTc->videoConference.activeMems_from[index_activeMems_from].mem.usIndex_pMems_from;
						TASK_AV_FROM  *  pFrom  =  NULL;
#if  0
						if  (  usIndex_pMems_from  >=  pTask->usCntLimit_mems_from  )  {
							traceLogA(  (char*)  "findOrgMsg: index_pMem_from %d too big",  (  int  )usIndex_pMems_from  );
							goto  errLabel;
						}
						pFrom  =  &pTask->pMems_from1[usIndex_pMems_from];
#endif
						pFrom  =  getTaskAvFrom(  pTask,  usIndex_pMems_from,  _T(  ""  )  );
						if  (  !pFrom  )  goto  errLabel;

						//  2014/12/12
						if  (  pFrom->audio.ta_recvd.uiTranNo_openAvDev  !=  pMem->uiTranNo_openAvDev  )  {
							#ifdef  __DEBUG__
									traceLog((TCHAR*)  _T(  "findOrgMsg: audio.tn not matched"  )  );
							#endif
							qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: audio, %I64u, from.tn %d != pMem.%d, skipped."  ),  pFrom->idInfo.ui64Id,  pFrom->audio.ta_recvd.uiTranNo_openAvDev,  pMem->uiTranNo_openAvDev  );

							//  2009/06/01
							if  (  pTask->ucbVideoConference  &&  !pTask->ucbVideoConferenceStarter  &&  pMsgTask->pMisCnt  )  {
								MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
								pMisCnt->refreshVideoConferenceActiveMems.iTaskId  =  iTaskId;
								pMisCnt->refreshVideoConferenceActiveMems.bNeedRefreshed  =  TRUE;
							}

							continue;
						}

						//
						MACRO_memset_misMsgTask(  pMsgTask_toTransform  );
						memcpy(  pMsgTask_toTransform,  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  );
						pMsgTask_toTransform->data.route.idInfo_from.ui64Id  =  pTc->videoConference.activeMems_from[index_activeMems_from].mem.idInfo.ui64Id;
						pMsgTask_toTransform->data.route.idInfo_to.ui64Id  =  pMsgTask->data.route.idInfo_to.ui64Id;
						pNew  =  (  TRANSFER_AUDIO_DATA  *  )pMsgTask_toTransform->data.buf;
						memset(  pNew,  0,  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  );
						pNew->uiType  =  pTransferAudioData->uiType;
						pNew->uiTranNo_openAvDev  =  pFrom->audio.ta_recvd.uiTranNo_openAvDev;
						memcpy(  &pNew->mems[0],  pMem,  sizeof(  pNew->mems[0]  )  );
						pNew->usCnt  =  1;
						pNew->uiLen  =  pMem->uiLen;
						memcpy(  pNew->buf,  pTransferAudioData->buf  +  iPos,  pNew->uiLen  );

						//										
						pNew->tmpInternal.param.index_pMems_from  =  pTc->videoConference.activeMems_from[index_activeMems_from].mem.usIndex_pMems_from;
						pNew->tmpInternal.param.index_activeMems_from  =  index_activeMems_from;

						//
						pMsgTask_toTransform->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  +  pNew->uiLen;

						pTransform  =  MACRO_getTransform(  *pTask,  index_activeMems_from  );
						if  (  pTransform  )  {
							//  qPostMsgAndTrigger_toDo(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->video  );
							q2PostMsgAndTrigger(  pMsgTask_toTransform,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask_toTransform->lenInBytes,  &pTransform->audio.q2  );
						}
				   }

				   iErr  =  1;  goto  errLabel;
			  }
		      
				}
	else  {

		  if  (  pMsgTask->iTaskId  ==  iTaskId  )  {
				  //  2011/01/23				  
				  if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					   //  traceLog((TCHAR*)  _T(  "audio data sent by myself"  )  );

					   q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->mixer.pOutputQ2  );
					   MIS_CHANNEL	*	pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_realTimeMedia  );
					   if  (  pChannel  )  q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2  );

					   //
					   iErr  =  1;  goto  errLabel;				   
				  }		
		  }
		  
		  //  2014/11/21
		  if  (  pTask->applyForProxy.bRecvd_proxyReply  )  {		//  applier for proxy
			  if  (  pTask->applyForProxy.proxyReply.proxy.uiTranNo_openAvDev_a  ==  pTransferAudioData->uiTranNo_openAvDev  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "findOrgMsg: applyForProxy: my pkt is sent back. skipped"  )  );
				  #endif
				  iErr  =  1;  goto  errLabel;
			  }
		  }


		  //  2014/11/21
		  if  (  !pTask->receiver.bRecvd_proxiedTranInfo  )  {  //  一般性的数据包处理，或者是proxy

			  //  search in mems_from directly
			  for  (  index  =  0;  index  <  pTc->videoConference.usCntLimit_mems_from;  index  ++  )  {			
				  TASK_AV_FROM  *  pFrom  =  &pTc->videoConference.pMems_from[index];
				   //
				   if  (  pFrom->idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id                              							
					   &&  pFrom->audio.ta_recvd.uiTranNo_openAvDev  ==  pTransferAudioData->uiTranNo_openAvDev  )													
				   {
						#ifdef  __DEBUG__
								//  traceLogA(  (char*)  "AudioData: usCntLimit_mems_from %d",  pTransferAvInfoElem->myTask.usCntLimit_mems_from  ); 
						#endif
					    //  if  (  procTaskAudio(  pProcInfo,  &pMsgElem->addr_logicalPeer,  pMsgTask,  &pContent->transferAudioData,  &pTransferAvInfoElem->tranInfo,  &pTransferAvInfoElem->myTask,  index,  0  )  )  goto  errLabel;

					   pTransferAudioData->tmpInternal.param.index_pMems_from  =  index;
					   pTransferAudioData->tmpInternal.param.index_activeMems_from  =  0;
					   
					   //  2014/11/21
					   if  (  pTask->doProxy.bExists_avProxy  )  {

						   int	index_activeMems_from	=	0;
					   					   
						   //
						   QIS_DISPATCH	*	pDispatch  =  MACRO_getDispatch(  *pTask,  index_activeMems_from  );
						   if  (  pDispatch  )  {
							   q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pDispatch->audio.q2  );					
						   }
						   iErr  =  1;  goto  errLabel;
					   }

					   //
					   QY_TRANSFORM  *  pTransform  =  MACRO_getTransform(  *pTask,  pTransferAudioData->tmpInternal.param.index_activeMems_from  );
					   if  (  pTransform  )  {
						   //  qPostMsgAndTrigger_toDo(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->audio  );
						   q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->audio.q2  );
					   }

					   iErr  =  1;  goto  errLabel;
				   }
			  }
			  //
			  }
		  else  {  //  receiver from proxy				  			 
			  if  (  pTask->mem0_from.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id
				  &&  pTask->mem0_from.audio.ta_recvd.uiTranNo_openAvDev  ==  pTransferAudioData->uiTranNo_openAvDev  )
			  {
				  //  2014/11/21
				  if  (  pTask->receiver.proxied_from.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					  #ifdef  __DEBUG__
							  traceLog((TCHAR*)  _T(  "findOrgMsg: a receiver: my pkt is sent back. skipped"  )  );
					  #endif
					  iErr  =  1;  goto  errLabel;
				  }
				  	
				  //
				   int								i						=	0;
				   int								iPos					=	0;
				   TRANSFER_AUDIO_dataMemHead	*	pMem					=	NULL;
				   int								index_activeMems_from	=	0;
				   unsigned  int					usIndex_pMems_from		=	0;
				   QY_TRANSFORM					*	pTransform				=	NULL;
				   MIS_MSG_TASK					*	pMsgTask_toTransform	=	NULL;
				   TRANSFER_AUDIO_DATA			*	pNew					=	NULL;

				   if  (  !pTask->video.pMsgTask_toTransform  )  {
					   traceLogA(  (char*)  "findOrgMsg failed. pMsgTask_toTransform is null"  );
					   goto  errLabel;
				   }
				   pMsgTask_toTransform  =  (  MIS_MSG_TASK  *  )pTask->video.pMsgTask_toTransform;

				   if  (  !pTransferAudioData->usCnt  )  {
					   pTransferAudioData->usCnt  =  1;	//  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
					   pTransferAudioData->mems[0].uiLen  =  pTransferAudioData->uiLen;
				   }
				   if  (  pTransferAudioData->usCnt  >  mycountof(  pTransferAudioData->mems  )  )  goto  errLabel;

				   #ifdef  __DEBUG__
						   //  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video len %d"  ),  pTransferVideoData->uiLen  );
				   #endif


				   for  (  iPos  =  0,  i  =  0;  i  <  pTransferAudioData->usCnt;  iPos  =  iPos  +  pTransferAudioData->mems[i].uiLen,  i  ++  )  {
					    pMem  =  &pTransferAudioData->mems[i];
						if  (  !pMem->uiLen  )  {
							traceLogA(  (char*)  "findOrgMsg: transferAudioMem.uiLen is 0. skipped."  );
							continue;
						}

						if  (  iPos  +  pTransferAudioData->mems[i].uiLen  >  pTransferAudioData->uiLen  )  {
							traceLogA(  (char*)  "findOrgMsg failed: iPos + mem.uiLen > data.uiLen"  );
							goto  errLabel;
						}

						//if  (  !pMem->idInfo.ui64Id  )  pMem->idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;

						//											
						usIndex_pMems_from  =  1;
						TASK_AV_FROM  *  pFrom  =  NULL;
						pFrom  =  getTaskAvFrom(  pTask,  usIndex_pMems_from,  _T(  ""  )  );
						if  (  !pFrom  )  goto  errLabel;

												//
						MACRO_memset_misMsgTask(  pMsgTask_toTransform  );
						memcpy(  pMsgTask_toTransform,  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  );
						pMsgTask_toTransform->data.route.idInfo_from.ui64Id  =  pFrom->idInfo.ui64Id;
						pMsgTask_toTransform->data.route.idInfo_to.ui64Id  =  pMsgTask->data.route.idInfo_to.ui64Id;
						pNew  =  (  TRANSFER_AUDIO_DATA  *  )pMsgTask_toTransform->data.buf;
						memset(  pNew,  0,  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  );
						pNew->uiType  =  pTransferAudioData->uiType;
						pNew->uiTranNo_openAvDev  =  pFrom->audio.ta_recvd.uiTranNo_openAvDev;
						memcpy(  &pNew->mems[0],  pMem,  sizeof(  pNew->mems[0]  )  );
						pNew->usCnt  =  1;
						pNew->uiLen  =  pMem->uiLen;
						memcpy(  pNew->buf,  pTransferAudioData->buf  +  iPos,  pNew->uiLen  );

						//										
						pNew->tmpInternal.param.index_pMems_from  =  usIndex_pMems_from;
						pNew->tmpInternal.param.index_activeMems_from  =  index_activeMems_from;

						//
						pMsgTask_toTransform->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  +  pNew->uiLen;

						pTransform  =  MACRO_getTransform(  *pTask,  index_activeMems_from  );
						if  (  pTransform  )  {
							//  
							q2PostMsgAndTrigger(  pMsgTask_toTransform,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask_toTransform->lenInBytes,  &pTransform->audio.q2  );
						}

						//  2014/11/11
						continue;

				   }

				   iErr  =  1;  goto  errLabel;
			  } 

			  //
			  iErr  =  0;  goto  errLabel;		  
		}
	}
	iErr  =  0;
errLabel:
	return  iErr;
											 
}
#endif 


//
int  tmpHandler_findOrgMsgAndProcess_mis_procTaskAudioData(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr,  int  iTaskId,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_AUDIO_DATA  *  pTransferAudioData,  IM_CONTENTU  *  pContentElem,  PROC_TASK_AV  *  pTask  )
{
	int	iErr	=	-1;
	int	index	=	0;
	MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	if  (  !pMisCnt  )  {
		traceLog((TCHAR*)  _T(  "tmpHandler_findOrgMsgAndProcess_mis_procTaskVideoData failed, pMisCnt is null"  )  );
		return  -1;
	}
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	//
	if  (  pTask->ucbVideoConferenceStarter  )  {									
		int	index_activeMems_from	=	0;

		//  search in activeMems_from first
		for  (  index_activeMems_from  =  0;  index_activeMems_from  <  pTc->videoConference.usCntLimit_activeMems_from;  index_activeMems_from  ++  )  {
			DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[index_activeMems_from];
			if  (  pActiveMem_from->avStream.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id
				&&  pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev  ==  pTransferAudioData->uiTranNo_openAvDev  )
				{			
					#ifdef  __DEBUG__
							//  traceLogA(  (char*)  "AudioData: usCntLimit_mems_from %d, usCntLimit_activeMems_from %d, video conference starter",  pTransferAvInfoElem->myTask.usCntLimit_mems_from,  pTransferAvInfoElem->myTask.usCntLimit_activeMems_from  );
					#endif
					//  if  (  procTaskAudio(  pProcInfo,  &pMsgElem->addr_logicalPeer,  pMsgTask,  &pContent->transferAudioData,  &pTransferAvInfoElem->tranInfo,  &pTransferAvInfoElem->myTask,  index,  index_activeMems_from  )  )  goto  errLabel;


					//
					index  =  -1;

					//
					pTransferAudioData->tmpInternal.param.index_pMems_from  =  index;
					pTransferAudioData->tmpInternal.param.index_activeMems_from  =  index_activeMems_from;
														
					/*
					QY_TRANSFORM  *  pTransform  =  MACRO_getTransform(  *pTask,  pTransferAudioData->tmpInternal.param.index_activeMems_from  );
					if  (  pTransform  )  {
						//  qPostMsgAndTrigger_toDo(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->audio  );
						q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->audio.q2  );
					}
					*/
					QIS_DISPATCH	*	pDispatch  =  MACRO_getDispatch(  *pTask,  index_activeMems_from  );
					if  (  pDispatch  )  {
						q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pDispatch->audio.q2,  _T(  "tmp_findOrgMsg_procTaskAudio"  ));
					}

					iErr  =  1;  goto  errLabel;												  
				}
			}
		
		}
	else  if  (  pTask->ucbVideoConference  )  {

			  //
			  if  (  pMsgTask->bFrom_sharedObj  )  {
				  QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pMsgTask->index_sharedObj  );
				  if  (  !pSharedObj  )  goto  errLabel;
				  //
				  int  i;
				  SHARED_OBJ_USR  *  pSou;
				  for  (  i  =  0;  i  <  mycountof(  pSharedObj->usrs  );  i  ++  )  {
					   pSou  =  &pSharedObj->usrs[i];
					   if  ( !pSou->iTaskId  )  continue;  
					   if  (  pSou->iTaskId  !=  iTaskId  )  continue;
					   				  
					   //						
					   if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
							   
						   //  traceLog((TCHAR*)  _T(  "audio data sent by myself"  )  );
						   bool  bSend  =  true;

						   bSend  =  canSend(  pSharedObj,  pTc  );

						   if  (  bSend  )  {
							   q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->mixer.pOutputQ2,  _T(  "tmp_findOrg_procTaskAudio 1"  ));
							   MIS_CHANNEL	*	pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_realTimeMedia  );
							   if  (  pChannel  )  {

								   //
								   chkToApplyForChannel(  pProcInfo,  CONST_channelType_realTimeMedia, false  );

								   //
								   q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2,  _T(  "tmp_findOrg_procTaskAudio 2"  ));
							   }
						   }
						   							
						   //							
						   iErr  =  1;  goto  errLabel;				   						  
						 
					   }						   							
						
					   //						
					   break;					   
				  }
			  }


			  //
#if  0
			  if  (  pMsgTask->iTaskId  ==  iTaskId  )  {
				  //  2011/01/23				  
				  if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					   //  traceLog((TCHAR*)  _T(  "audio data sent by myself"  )  );

					   q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->mixer.pOutputQ2  );
					   MIS_CHANNEL	*	pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_realTimeMedia  );
					   if  (  pChannel  )  {

						   //
						   chkToApplyForChannel(  pProcInfo,  pChannel,  CONST_channelType_realTimeMedia  );

						   //
						   q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2  );
					   }

					   //
					   iErr  =  1;  goto  errLabel;				   
				  }
			  }
#endif

			  //
#ifdef  __DEBUG__
			  if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  162  )  {
				  int  ii  =  0;
			  }
#endif

			  //
			  if  (  pTask->mem0_from.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id
				  &&  pTask->mem0_from.audio.ta_recvd.uiTranNo_openAvDev  ==  pTransferAudioData->uiTranNo_openAvDev  )
			  {
				   int								i						=	0;
				   int								iPos					=	0;
				   TRANSFER_AUDIO_dataMemHead	*	pMem					=	NULL;
				   int								index_activeMems_from	=	0;
				   //unsigned  int					usIndex_pMems_from		=	0;
				   QY_TRANSFORM					*	pTransform				=	NULL;
				   MIS_MSG_TASK					*	pMsgTask_toTransform	=	NULL;
				   TRANSFER_AUDIO_DATA			*	pNew					=	NULL;

				   if  (  !pTask->audio.pMsgTask_toTransform  )  {
					   traceLogA(  (char*)  "findOrgMsg failed. pMsgTask_toTransform is null"  );
					   goto  errLabel;
				   }
				   pMsgTask_toTransform  =  (  MIS_MSG_TASK  *  )pTask->audio.pMsgTask_toTransform;

				   if  (  !pTransferAudioData->usCnt  )  {
					   pTransferAudioData->usCnt  =  1;	//  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
					   pTransferAudioData->mems[0].uiLen  =  pTransferAudioData->uiLen;
				   }
				   if  (  pTransferAudioData->usCnt  >  mycountof(  pTransferAudioData->mems  )  )  goto  errLabel;

				   #ifdef  __DEBUG__
						   //  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: audio len %d"  ),  pTransferAudioData->uiLen  );
				   #endif


				   for  (  iPos  =  0,  i  =  0;  i  <  pTransferAudioData->usCnt;  iPos  =  iPos  +  pTransferAudioData->mems[i].uiLen,  i  ++  )  {
					    pMem  =  &pTransferAudioData->mems[i];
						if  (  !pMem->uiLen  )  {
							//
							#ifdef  __DEBUG__
									//traceLogA(  (char*)  "findOrgMsg: transferAudioMem.uiLen is 0. skipped."  );
							#endif
							//
							continue;
						}

						if  (  iPos  +  pTransferAudioData->mems[i].uiLen  >  pTransferAudioData->uiLen  )  {
							#ifdef  __DEBUG__
									traceLogA(  (char*)  "findOrgMsg failed: iPos + mem.uiLen > data.uiLen"  );
							#endif
							goto  errLabel;
						}

						if  (  !pMem->idInfo.ui64Id  )  pMem->idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;
						for  (  index_activeMems_from  =  0;  index_activeMems_from  <  pTc->videoConference.usCntLimit_activeMems_from;  index_activeMems_from  ++  )  {
							if  (  pMem->idInfo.ui64Id  ==  pTc->videoConference.activeMems_from[index_activeMems_from].avStream.idInfo.ui64Id
								&&  pMem->uiTranNo_openAvDev  ==  pTc->videoConference.activeMems_from[index_activeMems_from].avStream.obj.tranInfo.audio.uiTranNo_openAvDev  )  break;
						}
						if  (  index_activeMems_from  ==  pTc->videoConference.usCntLimit_activeMems_from  )  {
							//
							TCHAR  tBuf[128];
							_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "findOrgMsg: audio, conf%I64u, from %I64u, can't get index_activeMems_from, skipped."  ),  pMsgTask->addr_logicalPeer.idInfo.ui64Id,  pMem->idInfo.ui64Id  );
							#ifdef  __DEBUG__
									traceLog((TCHAR*)  tBuf  );
							#endif
							showInfo_open0(  0,  0,  tBuf  );
							//
							iErr  =  CONST_qyRet_cantGet_index_activeMems_from;  goto  errLabel;

						#if  0
							//  2009/06/01
							if  (  pTask->ucbVideoConference  &&  !pTask->ucbVideoConferenceStarter  &&  pMsgTask->pMisCnt  )  {
								MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
								pMisCnt->refreshVideoConferenceActiveMems.iTaskId  =  iTaskId;
								pMisCnt->refreshVideoConferenceActiveMems.bNeedRefreshed  =  TRUE;
							}

							continue;
						#endif
						}
#if  0
						usIndex_pMems_from  =  -1;//pTc->videoConference.activeMems_from[index_activeMems_from].mem.usIndex_pMems_from;
						TASK_AV_FROM  *  pFrom  =  NULL;
						pFrom  =  getTaskAvFrom(  pTask,  usIndex_pMems_from,  _T(  ""  )  );
						if  (  !pFrom  )  goto  errLabel;
#endif
						DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[index_activeMems_from];
						
						//  2014/12/12
#if  0
						if  (  pFrom->audio.ta_recvd.uiTranNo_openAvDev  !=  pMem->uiTranNo_openAvDev  )  {
							#ifdef  __DEBUG__
									traceLog((TCHAR*)  _T(  "findOrgMsg: audio.tn not matched"  )  );
							#endif
							qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: audio, %I64u, from.tn %d != pMem.%d, skipped."  ),  pFrom->idInfo.ui64Id,  pFrom->audio.ta_recvd.uiTranNo_openAvDev,  pMem->uiTranNo_openAvDev  );

							//  2009/06/01
							if  (  pTask->ucbVideoConference  &&  !pTask->ucbVideoConferenceStarter  &&  pMsgTask->pMisCnt  )  {
								MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
								pMisCnt->refreshVideoConferenceActiveMems.iTaskId  =  iTaskId;
								pMisCnt->refreshVideoConferenceActiveMems.bNeedRefreshed  =  TRUE;
							}

							continue;
						}
#endif

						//
						MACRO_memset_misMsgTask(  pMsgTask_toTransform  );
						memcpy(  pMsgTask_toTransform,  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  );
						pMsgTask_toTransform->data.route.idInfo_from.ui64Id  =  pTc->videoConference.activeMems_from[index_activeMems_from].avStream.idInfo.ui64Id;
						pMsgTask_toTransform->data.route.idInfo_to.ui64Id  =  pMsgTask->data.route.idInfo_to.ui64Id;
						pNew  =  (  TRANSFER_AUDIO_DATA  *  )pMsgTask_toTransform->data.buf;
						memset(  pNew,  0,  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  );
						pNew->uiType  =  pTransferAudioData->uiType;
						pNew->uiTranNo_openAvDev  =  pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev;
						memcpy(  &pNew->mems[0],  pMem,  sizeof(  pNew->mems[0]  )  );
						pNew->usCnt  =  1;
						pNew->uiLen  =  pMem->uiLen;
						memcpy(  pNew->buf,  pTransferAudioData->buf  +  iPos,  pNew->uiLen  );

						//										
						pNew->tmpInternal.param.index_pMems_from  =  -1;//pTc->videoConference.activeMems_from[index_activeMems_from].usIndex_pMems_from;
						pNew->tmpInternal.param.index_activeMems_from  =  index_activeMems_from;

						//
						pMsgTask_toTransform->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  +  pNew->uiLen;

						pTransform  =  MACRO_getTransform(  *pTask,  index_activeMems_from  );
						if  (  pTransform  )  {
							//
							if (pProcInfo->cfg.b_useAudioQ2_toDecA) {
								//  qPostMsgAndTrigger_toDo(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->video  );
								q2PostMsgAndTrigger(pMsgTask_toTransform, offsetof(MIS_MSG_TASK, data) + pMsgTask_toTransform->lenInBytes, &pTransform->audio.q2, _T("tmp_findOrg_procTaskAudio 3"));
							}
							else {
								 pTransform->audio.qBuf2->q2PostMsgAndTrigger(pMem, pNew->buf, pNew->uiLen,_T("tmp_findOrg_procTaskAudio" ));
							}
						}
				   }

				   iErr  =  1;  goto  errLabel;
			  }
		      
				}
	else  {

		  if  (  pMsgTask->bFrom_sharedObj  )  {
			  QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pMsgTask->index_sharedObj  );
			  if  (  !pSharedObj  )  goto  errLabel;
			  int  i;
			  for  (  i  =  0;  i  <  mycountof(  pSharedObj->usrs  );  i  ++  )  {
				   SHARED_OBJ_USR  *  pSou  =  &pSharedObj->usrs[i];
				   if  (  !pSou->iTaskId  )  continue;
				   if  (  pSou->iTaskId  !=  iTaskId  )  continue;
				   //
				   if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					   //  traceLog((TCHAR*)  _T(  "audio data sent by myself"  )  );

					   bool  bSend  =  true;
					   bSend  =  canSend(  pSharedObj,  pTc  );

					   if  (  bSend  )  {

						   q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->mixer.pOutputQ2,  _T(  "tmp_findOrg_procTaskAudio 4"  ));
						   MIS_CHANNEL	*	pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_realTimeMedia  );
						   if  (  pChannel  )  {

							   //
							   chkToApplyForChannel(  pProcInfo,  CONST_channelType_realTimeMedia, false  );

							   //
							   q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2,  _T(  "tmp_findOrg_procTaskAudio 5"  ));
						   }
					   }
					   //
					   iErr  =  1;  goto  errLabel;				   
				  
				   }		


				   break;
			  }
		  }


#if  0
		  if  (  pMsgTask->iTaskId  ==  iTaskId  )  {
				  //  2011/01/23				  
				  if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					   //  traceLog((TCHAR*)  _T(  "audio data sent by myself"  )  );

					   q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->mixer.pOutputQ2  );
					   MIS_CHANNEL	*	pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_realTimeMedia  );
					   if  (  pChannel  )  {

						   //
						   chkToApplyForChannel(  pProcInfo,  pChannel,  CONST_channelType_realTimeMedia  );

						   //
						   q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2  );
					   }

					   //
					   iErr  =  1;  goto  errLabel;				   
				  }		
		  }
#endif
		  
		  //  2014/11/21
		  if  (  pTask->applyForProxy.bRecvd_proxyReply  )  {		//  applier for proxy
			  if  (  pTask->applyForProxy.proxyReply.proxy.uiTranNo_openAvDev_a  ==  pTransferAudioData->uiTranNo_openAvDev  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "findOrgMsg: applyForProxy: my pkt is sent back. skipped"  )  );
				  #endif
				  iErr  =  1;  goto  errLabel;
			  }
		  }


		  //  2014/11/21
		  if  (  !pTask->receiver.bRecvd_proxiedTranInfo  )  {  //  一般性的数据包处理，或者是proxy

			  //  search in mems_from directly
			  for  (  index  =  0;  index  <  pTc->videoConference.usCntLimit_activeMems_from;  index  ++  )  {			
				  DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[index];
				   //
				   if  (  pActiveMem_from->avStream.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id                              							
					   &&  pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev  ==  pTransferAudioData->uiTranNo_openAvDev  )													
				   {
						#ifdef  __DEBUG__
								//  traceLogA(  (char*)  "AudioData: usCntLimit_mems_from %d",  pTransferAvInfoElem->myTask.usCntLimit_mems_from  ); 
						#endif
					    //  if  (  procTaskAudio(  pProcInfo,  &pMsgElem->addr_logicalPeer,  pMsgTask,  &pContent->transferAudioData,  &pTransferAvInfoElem->tranInfo,  &pTransferAvInfoElem->myTask,  index,  0  )  )  goto  errLabel;

					   pTransferAudioData->tmpInternal.param.index_pMems_from  =  -1;
					   pTransferAudioData->tmpInternal.param.index_activeMems_from  =  index;
					   
					   //  2014/11/21
					   if  (  pTask->doProxy.bExists_avProxy  )  {

						   int	index_activeMems_from	=	0;
					   					   
						   //
						   QIS_DISPATCH	*	pDispatch  =  MACRO_getDispatch(  *pTask,  index_activeMems_from  );
						   if  (  pDispatch  )  {
							   q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pDispatch->audio.q2,  _T(  "tmp_findOrg_procTaskAudio 6"  ));
						   }
						   iErr  =  1;  goto  errLabel;
					   }

					   //
					   QY_TRANSFORM  *  pTransform  =  MACRO_getTransform(  *pTask,  pTransferAudioData->tmpInternal.param.index_activeMems_from  );
					   if  (  pTransform  )  {
						   if (pProcInfo->cfg.b_useAudioQ2_toDecA) {
							   //  qPostMsgAndTrigger_toDo(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->audio  );
							   q2PostMsgAndTrigger(pMsgTask, offsetof(MIS_MSG_TASK, data) + pMsgTask->lenInBytes, &pTransform->audio.q2, _T("tmp_findOrg_procTaskAudio 7"));
						   }
						   else {
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
								   pTransform->audio.qBuf2->q2PostMsgAndTrigger(pMem, data, pMem->uiLen,_T("tmp_findOrg_procTaskAudio"));
								   //
							   }

							   //
						   }
					   }

					   iErr  =  1;  goto  errLabel;
				   }
			  }
			  //
			  }
		  else  {  //  receiver from proxy				  			 
			  showInfo_open0(0, _T(""), _T("not supported here"));
			  goto  errLabel;
#if  0
			  if  (  pTask->mem0_from.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id
				  &&  pTask->mem0_from.audio.ta_recvd.uiTranNo_openAvDev  ==  pTransferAudioData->uiTranNo_openAvDev  )
			  {
				  //  2014/11/21
				  if  (  pTask->receiver.proxied_from.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					  #ifdef  __DEBUG__
							  traceLog((TCHAR*)  _T(  "findOrgMsg: a receiver: my pkt is sent back. skipped"  )  );
					  #endif
					  iErr  =  1;  goto  errLabel;
				  }
				  	
				  //
				   int								i						=	0;
				   int								iPos					=	0;
				   TRANSFER_AUDIO_dataMemHead	*	pMem					=	NULL;
				   int								index_activeMems_from	=	0;
				   unsigned  int					usIndex_pMems_from		=	0;
				   QY_TRANSFORM					*	pTransform				=	NULL;
				   MIS_MSG_TASK					*	pMsgTask_toTransform	=	NULL;
				   TRANSFER_AUDIO_DATA			*	pNew					=	NULL;

				   if  (  !pTask->video.pMsgTask_toTransform  )  {
					   traceLogA(  (char*)  "findOrgMsg failed. pMsgTask_toTransform is null"  );
					   goto  errLabel;
				   }
				   pMsgTask_toTransform  =  (  MIS_MSG_TASK  *  )pTask->video.pMsgTask_toTransform;

				   if  (  !pTransferAudioData->usCnt  )  {
					   pTransferAudioData->usCnt  =  1;	//  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
					   pTransferAudioData->mems[0].uiLen  =  pTransferAudioData->uiLen;
				   }
				   if  (  pTransferAudioData->usCnt  >  mycountof(  pTransferAudioData->mems  )  )  goto  errLabel;

				   #ifdef  __DEBUG__
						   //  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video len %d"  ),  pTransferVideoData->uiLen  );
				   #endif


				   for  (  iPos  =  0,  i  =  0;  i  <  pTransferAudioData->usCnt;  iPos  =  iPos  +  pTransferAudioData->mems[i].uiLen,  i  ++  )  {
					    pMem  =  &pTransferAudioData->mems[i];
						if  (  !pMem->uiLen  )  {
							traceLogA(  (char*)  "findOrgMsg: transferAudioMem.uiLen is 0. skipped."  );
							continue;
						}

						if  (  iPos  +  pTransferAudioData->mems[i].uiLen  >  pTransferAudioData->uiLen  )  {
							traceLogA(  (char*)  "findOrgMsg failed: iPos + mem.uiLen > data.uiLen"  );
							goto  errLabel;
						}

						//if  (  !pMem->idInfo.ui64Id  )  pMem->idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;

						//											
						usIndex_pMems_from  =  1;
						TASK_AV_FROM  *  pFrom  =  NULL;
						pFrom  =  getTaskAvFrom(  pTask,  usIndex_pMems_from,  _T(  ""  )  );
						if  (  !pFrom  )  goto  errLabel;

												//
						MACRO_memset_misMsgTask(  pMsgTask_toTransform  );
						memcpy(  pMsgTask_toTransform,  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  );
						pMsgTask_toTransform->data.route.idInfo_from.ui64Id  =  pFrom->idInfo.ui64Id;
						pMsgTask_toTransform->data.route.idInfo_to.ui64Id  =  pMsgTask->data.route.idInfo_to.ui64Id;
						pNew  =  (  TRANSFER_AUDIO_DATA  *  )pMsgTask_toTransform->data.buf;
						memset(  pNew,  0,  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  );
						pNew->uiType  =  pTransferAudioData->uiType;
						pNew->uiTranNo_openAvDev  =  pFrom->audio.ta_recvd.uiTranNo_openAvDev;
						memcpy(  &pNew->mems[0],  pMem,  sizeof(  pNew->mems[0]  )  );
						pNew->usCnt  =  1;
						pNew->uiLen  =  pMem->uiLen;
						memcpy(  pNew->buf,  pTransferAudioData->buf  +  iPos,  pNew->uiLen  );

						//										
						pNew->tmpInternal.param.index_pMems_from  =  usIndex_pMems_from;
						pNew->tmpInternal.param.index_activeMems_from  =  index_activeMems_from;

						//
						pMsgTask_toTransform->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  +  pNew->uiLen;

						pTransform  =  MACRO_getTransform(  *pTask,  index_activeMems_from  );
						if  (  pTransform  )  {
							//  
							q2PostMsgAndTrigger(  pMsgTask_toTransform,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask_toTransform->lenInBytes,  &pTransform->audio.q2,  _T(  "tmp_findOrg_procTaskAudio 8"  ));
						}

						//  2014/11/11
						continue;

				   }

				   iErr  =  1;  goto  errLabel;
			  } 

			  //
			  iErr  =  0;  goto  errLabel;		  
#endif
		}
	}
	iErr  =  0;
errLabel:
	return  iErr;
											 
}
 


//
#if  0
int  old_tmpHandler_findOrgMsgAndProcess_mis_procTaskVideoData(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr,  int  iTaskId,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_VIDEO_DATA  *  pTransferVideoData,  IM_CONTENTU  *  pContentElem,  PROC_TASK_AV  *  pTask  )
{
	int			iErr	=	-1;
	int			index	=	0;
	MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	//
	if  (  !pMisCnt  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "tmpHandler_findOrgMsgAndProcess_mis_procTaskVideoData failed, pMisCnt is null"  )  );
		#endif
		return  -1;
	}
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  ( QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;


	//
	if  (  pTask->ucbVideoConferenceStarter  )  {
		
		if  (  pContentElem->uiType  !=  CONST_imCommType_transferAvInfo  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "procTaskVideoData failed, contentType err"  )  );
			#endif
			goto  errLabel;
		}

		//  2014/11/11
		if  (  pMsgTask->iTaskId  ==  iTaskId  )  {
			if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
				if  (  pTransferVideoData->uiTranNo_openAvDev  ==  pContentElem->transferAvInfo.confMosaicTranInfo_video.video.uiTranNo_openAvDev  
					||  pTransferVideoData->uiTranNo_openAvDev  ==  pContentElem->transferAvInfo.confMosaicTranInfo_resource.video.uiTranNo_openAvDev  )  
				{
					//
					dispatch_outputConfVideo(  pTask,  pMsgTask,  pTransferVideoData,  &pMisCnt->idInfo,  pTransferVideoData->uiTranNo_openAvDev  );
					//			
					iErr  =  1;  goto  errLabel;
				}
			}
		}

		//
		int	index_activeMems_from	=	0;

		//  search in activeMems_from first
		for  (  index_activeMems_from  =  0;  index_activeMems_from  <  pTc->videoConference.usCntLimit_activeMems_from;  index_activeMems_from  ++  )  {
			if  (  pTc->videoConference.activeMems_from[index_activeMems_from].mem.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id  )  break;								
		}
		//  use searched index to process video
		if  (  index_activeMems_from  <  pTc->videoConference.usCntLimit_activeMems_from  )  {												
			index  =  pTc->videoConference.activeMems_from[index_activeMems_from].mem.usIndex_pMems_from;							
			if  (  index  >=  0  &&  index  <  pTc->videoConference.usCntLimit_mems_from  )  {		
				TASK_AV_FROM  *  pFrom  =  &pTc->videoConference.pMems_from[index];
				//
				if  (  pFrom->idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id							
					&&  pFrom->video.tv_recvd.uiTranNo_openAvDev  ==  pTransferVideoData->uiTranNo_openAvDev  )							
				{
					#ifdef  __DEBUG__		
							//  traceLogA(  (char*)  "VideoData: usCntLimit_mems_from %d, usCntLimit_activeMems_from %d, video conference starter",  pTransferAvInfoElem->myTask.usCntLimit_mems_from,  pTransferAvInfoElem->myTask.usCntLimit_activeMems_from  );
					#endif
										
					//
					pTransferVideoData->tmpInternal.param.index_pMems_from  =  index;
					pTransferVideoData->tmpInternal.param.index_activeMems_from  =  index_activeMems_from;

					//
					QIS_DISPATCH	*	pDispatch  =  MACRO_getDispatch(  *pTask,  index_activeMems_from  );
					if  (  pDispatch  )  {
						q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pDispatch->video.q2  );
					}

					iErr  =  1;  goto  errLabel;												  															
				}		
			}				
		}
		}
	else  if  (  pTask->ucbVideoConference  )  {

			  //
		      if  (  pMsgTask->iTaskId  ==  iTaskId  )  {
				  //  2011/01/23				  
				  if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					   //  traceLog((TCHAR*)  _T(  "video data sent by myself"  )  );

					   q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->photomosaic.pOutputQ2  );
					   MIS_CHANNEL	*	pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_media  );
					   if  (  pChannel  )  q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2  );

					   //
					   iErr  =  1;  goto  errLabel;				   
				  }
			  }

			  //
			  if  (  pTask->mem0_from.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id
				  &&  pTask->mem0_from.video.tv_recvd.uiTranNo_openAvDev  ==  pTransferVideoData->uiTranNo_openAvDev  )
			  {
				   int								i						=	0;
				   int								iPos					=	0;
				   TRANSFER_VIDEO_dataMemHead	*	pMem					=	NULL;
				   int								index_activeMems_from	=	0;
				   unsigned  int					usIndex_pMems_from		=	0;
				   QY_TRANSFORM					*	pTransform				=	NULL;
				   MIS_MSG_TASK					*	pMsgTask_toTransform	=	NULL;
				   TRANSFER_VIDEO_DATA			*	pNew					=	NULL;

				   if  (  !pTask->video.pMsgTask_toTransform  )  {
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "findOrgMsg failed. pMsgTask_toTransform is null"  );
					   #endif
					   goto  errLabel;
				   }
				   pMsgTask_toTransform  =  (  MIS_MSG_TASK  *  )pTask->video.pMsgTask_toTransform;

				   if  (  !pTransferVideoData->usCnt  )  {
					   pTransferVideoData->usCnt  =  1;	//  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
					   pTransferVideoData->mems[0].uiLen  =  pTransferVideoData->uiLen;
				   }
				   if  (  pTransferVideoData->usCnt  >  mycountof(  pTransferVideoData->mems  )  )  goto  errLabel;

				   #ifdef  __DEBUG__
						#if  0
						   if  (  pTransferVideoData->stat.tSelectTime  )  {
							   TCHAR  tBuf[128];
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "find_procTaskVideodata:  tSelectTime %I64u"  ),  pTransferVideoData->stat.tSelectTime  );
							   showInfo_open0(  0,  _T(  "find_procTaskVideoData"  ),  tBuf  );
						   }
						#endif
						   //  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video len %d"  ),  pTransferVideoData->uiLen  );
				   #endif


				   for  (  iPos  =  0,  i  =  0;  i  <  pTransferVideoData->usCnt;  iPos  =  iPos  +  pTransferVideoData->mems[i].uiLen,  i  ++  )  {
					    pMem  =  &pTransferVideoData->mems[i];
						if  (  !pMem->uiLen  )  {
							//
							#ifdef  __DEBUG__
									//traceLogA(  (char*)  "findOrgMsg: transferVideoMem.uiLen is 0. skipped."  );
							#endif
							//
							continue;
						}

						if  (  iPos  +  pTransferVideoData->mems[i].uiLen  >  pTransferVideoData->uiLen  )  {
							#ifdef  __DEBUG__
									traceLogA(  (char*)  "findOrgMsg failed: iPos + mem.uiLen > data.uiLen"  );
							#endif
							goto  errLabel;
						}

						if  (  !pMem->idInfo.ui64Id  )  pMem->idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;
						//
						if  (  pTask->confMosaicTrans.bExists_confMosaic
							&&  pMem->idInfo.ui64Id  ==  pTask->mem0_from.idInfo.ui64Id  )
						{
							PROC_conf_mosaic  *  pProcConfMosaic  =  NULL;
							//
							if  (  pMem->uiTranNo_openAvDev  ==  pTask->confMosaicTrans.confMosaic_video.taskAvFrom.video.tv_recvd.uiTranNo_openAvDev  )  {
								pProcConfMosaic  =  &pTask->confMosaicTrans.confMosaic_video;
								}
							else  if  (  pMem->uiTranNo_openAvDev  ==  pTask->confMosaicTrans.confMosaic_resource.taskAvFrom.video.tv_recvd.uiTranNo_openAvDev  )  {
									  pProcConfMosaic  =  &pTask->confMosaicTrans.confMosaic_resource;
							}
							if  (  pProcConfMosaic  )  {
								//
								#ifdef  __DEBUG__
										//traceLog((TCHAR*)  _T(  "It's a pkt of mosaic video data"  )  );
								#endif
								//
								MACRO_memset_misMsgTask(  pMsgTask_toTransform  );
								memcpy(  pMsgTask_toTransform,  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  );
								pMsgTask_toTransform->data.route.idInfo_from.ui64Id  =  pMem->idInfo.ui64Id;
								pMsgTask_toTransform->data.route.idInfo_to.ui64Id  =  pMsgTask->data.route.idInfo_to.ui64Id;
								pNew  =  (  TRANSFER_VIDEO_DATA  *  )pMsgTask_toTransform->data.buf;
								memset(  pNew,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
								pNew->uiType  =  pTransferVideoData->uiType;
								pNew->uiTranNo_openAvDev  =  pMem->uiTranNo_openAvDev;
								memcpy(  &pNew->mems[0],  pMem,  sizeof(  pNew->mems[0]  )  );
								pNew->usCnt  =  1;
								pNew->uiLen  =  pMem->uiLen;
								memcpy(  pNew->buf,  pTransferVideoData->buf  +  iPos,  pNew->uiLen  );

								//  2014/11/11
								//
								pMsgTask_toTransform->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  +  pNew->uiLen;

								pTransform  =  &pProcConfMosaic->transform;
								if  (  pTransform  )  {
									//  								
									q2PostMsgAndTrigger(  pMsgTask_toTransform,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask_toTransform->lenInBytes,  &pTransform->v_preTransThread.q2  );						
								}
								//
								continue;
							}
						}
						//
						for  (  index_activeMems_from  =  0;  index_activeMems_from  <  pTc->videoConference.usCntLimit_activeMems_from;  index_activeMems_from  ++  )  {
							if  (  pMem->idInfo.ui64Id  ==  pTc->videoConference.activeMems_from[index_activeMems_from].mem.idInfo.ui64Id  )  break;
						}
						if  (  index_activeMems_from  ==  pTc->videoConference.usCntLimit_activeMems_from  )  {
							#ifdef  __DEBUG__
									traceLogA(  (char*)  "findOrgMsg_procTaskVideoData: can't get index_activeMems_from, skipped."  );
							#endif
							qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video, can't get index_activeMems_from, skipped."  )  );

							//  2009/06/01
							if  (  pTask->ucbVideoConference  &&  !pTask->ucbVideoConferenceStarter  &&  pMsgTask->pMisCnt  )  {
								MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
								pMisCnt->refreshVideoConferenceActiveMems.iTaskId  =  iTaskId;
								pMisCnt->refreshVideoConferenceActiveMems.bNeedRefreshed  =  TRUE;
							}

							continue;
						}
						usIndex_pMems_from  =  pTc->videoConference.activeMems_from[index_activeMems_from].mem.usIndex_pMems_from;
						TASK_AV_FROM  *  pFrom  =  NULL;
#if  0
						if  (  usIndex_pMems_from  >=  pTask->usCntLimit_mems_from  )  {
							#ifdef  __DEBUG__
									traceLogA(  (char*)  "findOrgMsg: index_pMem_from %d too big",  (  int  )usIndex_pMems_from  );
							#endif
							goto  errLabel;
						}
						//  2012/04/01
						pFrom  =  &pTask->pMems_from1[usIndex_pMems_from];
#endif
						pFrom  =  getTaskAvFrom(  pTask,  usIndex_pMems_from,  _T(  ""  )  );
						if  (  !pFrom  )  goto  errLabel;
						//
						if  (  pFrom->video.tv_recvd.uiTranNo_openAvDev  !=  pMem->uiTranNo_openAvDev  )  {
							#ifdef  __DEBUG__
									traceLog((TCHAR*)  _T(  "findOrgMsg: video.tn not matched"  )  );
							#endif
							qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video, %I64u, from.tn %d != pMem.%d, skipped."  ),  pFrom->idInfo.ui64Id,  pFrom->video.tv_recvd.uiTranNo_openAvDev,  pMem->uiTranNo_openAvDev  );

							//  2009/06/01
							if  (  pTask->ucbVideoConference  &&  !pTask->ucbVideoConferenceStarter  &&  pMsgTask->pMisCnt  )  {
								MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
								pMisCnt->refreshVideoConferenceActiveMems.iTaskId  =  iTaskId;
								pMisCnt->refreshVideoConferenceActiveMems.bNeedRefreshed  =  TRUE;
							}

							continue;
						}



						//
						MACRO_memset_misMsgTask(  pMsgTask_toTransform  );
						memcpy(  pMsgTask_toTransform,  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  );
						pMsgTask_toTransform->data.route.idInfo_from.ui64Id  =  pTc->videoConference.activeMems_from[index_activeMems_from].mem.idInfo.ui64Id;
						pMsgTask_toTransform->data.route.idInfo_to.ui64Id  =  pMsgTask->data.route.idInfo_to.ui64Id;
						pNew  =  (  TRANSFER_VIDEO_DATA  *  )pMsgTask_toTransform->data.buf;
						memset(  pNew,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
						pNew->uiType  =  pTransferVideoData->uiType;
						pNew->uiTranNo_openAvDev  =  pFrom->video.tv_recvd.uiTranNo_openAvDev;
						memcpy(  &pNew->mems[0],  pMem,  sizeof(  pNew->mems[0]  )  );
						pNew->usCnt  =  1;
						pNew->uiLen  =  pMem->uiLen;
						memcpy(  pNew->buf,  pTransferVideoData->buf  +  iPos,  pNew->uiLen  );

						//  2017/09/05
					#if  0
						if  (  i  ==  pTransferVideoData->usCnt  -  1  )  {
							pNew->stat  =  pTransferVideoData->stat;
						}
					#endif

						//										
						pNew->tmpInternal.param.index_pMems_from  =  pTc->videoConference.activeMems_from[index_activeMems_from].mem.usIndex_pMems_from;
						pNew->tmpInternal.param.index_activeMems_from  =  index_activeMems_from;

						//
						pMsgTask_toTransform->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  +  pNew->uiLen;

						pTransform  =  MACRO_getTransform(  *pTask,  index_activeMems_from  );
						if  (  pTransform  )  {
							//  
							#if  0	//  2011/12/10
								q2PostMsgAndTrigger(  pMsgTask_toTransform,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask_toTransform->lenInBytes,  &pTransform->video.q2  );
							#else
								q2PostMsgAndTrigger(  pMsgTask_toTransform,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask_toTransform->lenInBytes,  &pTransform->v_preTransThread.q2  );
							#endif
						}

						//  2014/11/11
						continue;
				   }

				   iErr  =  1;  goto  errLabel;
			  }
		      }	//  end of processing confMem
	else  {  //  

		  if  (  pMsgTask->iTaskId  ==  iTaskId  )  {
			  //  2011/01/23				  
			  if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
				   //  traceLog((TCHAR*)  _T(  "video data sent by myself"  )  );

				   q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->photomosaic.pOutputQ2  );
				   MIS_CHANNEL	*	pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_media  );
				   if  (  pChannel  )  q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2  );

				   //
				   iErr  =  1;  goto  errLabel;				   
			  }
		  }

		  //  2014/11/21
		  if  (  pTask->applyForProxy.bRecvd_proxyReply  )  {		//  applier for proxy
			  if  (  pTask->applyForProxy.proxyReply.proxy.uiTranNo_openAvDev_v  ==  pTransferVideoData->uiTranNo_openAvDev  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "findOrgMsg: applyForProxy: my pkt is sent back. skipped"  )  );
				  #endif
				  iErr  =  1;  goto  errLabel;
			  }
		  }

		  //  2014/11/21
		  if  (  !pTask->receiver.bRecvd_proxiedTranInfo  )  {  //  一般性的数据包处理，或者是proxy
		  		  
			  //  search in mems_from directly
			  for  (  index  =  0;  index  <  pTc->videoConference.usCntLimit_mems_from;  index  ++  )  {
				  TASK_AV_FROM  *  pFrom  =  &pTc->videoConference.pMems_from[index];
				   //
				   if  (  pFrom->idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id
					   &&  pFrom->video.tv_recvd.uiTranNo_openAvDev  ==  pTransferVideoData->uiTranNo_openAvDev  )
				   {		
						#ifdef  __DEBUG__
								//  traceLogA(  (char*)  "VideoData: usCntLimit_mems_from %d",  pTransferAvInfoElem->myTask.usCntLimit_mems_from  );
						#endif
					    //  


					   //
					   pTransferVideoData->tmpInternal.param.index_pMems_from  =  index;
					   pTransferVideoData->tmpInternal.param.index_activeMems_from  =  0;

					   //  2014/11/21
					   if  (  pTask->doProxy.bExists_avProxy  )  {

						   int	index_activeMems_from	=	0;
					   					   
						   //
						   QIS_DISPATCH	*	pDispatch  =  MACRO_getDispatch(  *pTask,  index_activeMems_from  );
						   if  (  pDispatch  )  {
							   q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pDispatch->video.q2  );					
						   }
						   iErr  =  1;  goto  errLabel;
					   }

					   //
					   QY_TRANSFORM  *  pTransform  =  MACRO_getTransform(  *pTask,  pTransferVideoData->tmpInternal.param.index_activeMems_from  );
					   if  (  pTransform  )  {
						   //  
						   QY_Q2	*	pQ2	=	&pTransform->v_preTransThread.q2;
						   if  (  !pTransform->v_preTransThread.hThread
							   &&  pTransform->video.hThread  )
						   {
							   pQ2  =  &pTransform->video.q2;
						   }

						   //
						   q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pQ2  );	
					   }
					   iErr  =  1;  goto  errLabel;												  
				   }			  
			  }
			  //
			  }
		  else  {  //  receiver from proxy				  			 
			  if  (  pTask->mem0_from.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id
				  &&  pTask->mem0_from.video.tv_recvd.uiTranNo_openAvDev  ==  pTransferVideoData->uiTranNo_openAvDev  )
			  {
				  //  2014/11/21
				  if  (  pTask->receiver.proxied_from.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					  #ifdef  __DEBUG__
							  traceLog((TCHAR*)  _T(  "findOrgMsg: v receiver: my pkt is sent back. skipped"  )  );
					  #endif
					  iErr  =  1;  goto  errLabel;
				  }
				  	
				  //
				   int								i						=	0;
				   int								iPos					=	0;
				   TRANSFER_VIDEO_dataMemHead	*	pMem					=	NULL;
				   int								index_activeMems_from	=	0;
				   unsigned  int					usIndex_pMems_from		=	0;
				   QY_TRANSFORM					*	pTransform				=	NULL;
				   MIS_MSG_TASK					*	pMsgTask_toTransform	=	NULL;
				   TRANSFER_VIDEO_DATA			*	pNew					=	NULL;

				   if  (  !pTask->video.pMsgTask_toTransform  )  {
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "findOrgMsg failed. pMsgTask_toTransform is null"  );
					   #endif
					   goto  errLabel;
				   }
				   pMsgTask_toTransform  =  (  MIS_MSG_TASK  *  )pTask->video.pMsgTask_toTransform;

				   if  (  !pTransferVideoData->usCnt  )  {
					   pTransferVideoData->usCnt  =  1;	//  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
					   pTransferVideoData->mems[0].uiLen  =  pTransferVideoData->uiLen;
				   }
				   if  (  pTransferVideoData->usCnt  >  mycountof(  pTransferVideoData->mems  )  )  goto  errLabel;

				   #ifdef  __DEBUG__
						   //  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video len %d"  ),  pTransferVideoData->uiLen  );
				   #endif


				   for  (  iPos  =  0,  i  =  0;  i  <  pTransferVideoData->usCnt;  iPos  =  iPos  +  pTransferVideoData->mems[i].uiLen,  i  ++  )  {
					    pMem  =  &pTransferVideoData->mems[i];
						if  (  !pMem->uiLen  )  {
						    #ifdef  __DEBUG__
									traceLogA(  (char*)  "findOrgMsg: transferVideoMem.uiLen is 0. skipped."  );
							#endif
							continue;
						}

						if  (  iPos  +  pTransferVideoData->mems[i].uiLen  >  pTransferVideoData->uiLen  )  {
							#ifdef  __DEBUG__
									traceLogA(  (char*)  "findOrgMsg failed: iPos + mem.uiLen > data.uiLen"  );
							#endif
							goto  errLabel;
						}

						//if  (  !pMem->idInfo.ui64Id  )  pMem->idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;

						//											
						usIndex_pMems_from  =  1;
						TASK_AV_FROM  *  pFrom  =  NULL;
						pFrom  =  getTaskAvFrom(  pTask,  usIndex_pMems_from,  _T(  ""  )  );
						if  (  !pFrom  )  goto  errLabel;

												//
						MACRO_memset_misMsgTask(  pMsgTask_toTransform  );
						memcpy(  pMsgTask_toTransform,  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  );
						pMsgTask_toTransform->data.route.idInfo_from.ui64Id  =  pFrom->idInfo.ui64Id;
						pMsgTask_toTransform->data.route.idInfo_to.ui64Id  =  pMsgTask->data.route.idInfo_to.ui64Id;
						pNew  =  (  TRANSFER_VIDEO_DATA  *  )pMsgTask_toTransform->data.buf;
						memset(  pNew,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
						pNew->uiType  =  pTransferVideoData->uiType;
						pNew->uiTranNo_openAvDev  =  pFrom->video.tv_recvd.uiTranNo_openAvDev;
						memcpy(  &pNew->mems[0],  pMem,  sizeof(  pNew->mems[0]  )  );
						pNew->usCnt  =  1;
						pNew->uiLen  =  pMem->uiLen;
						memcpy(  pNew->buf,  pTransferVideoData->buf  +  iPos,  pNew->uiLen  );

						//										
						pNew->tmpInternal.param.index_pMems_from  =  usIndex_pMems_from;
						pNew->tmpInternal.param.index_activeMems_from  =  index_activeMems_from;

						//
						pMsgTask_toTransform->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  +  pNew->uiLen;

						pTransform  =  MACRO_getTransform(  *pTask,  index_activeMems_from  );
						if  (  pTransform  )  {
							//  
							#if  0	//  2011/12/10
								q2PostMsgAndTrigger(  pMsgTask_toTransform,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask_toTransform->lenInBytes,  &pTransform->video.q2  );
							#else
								q2PostMsgAndTrigger(  pMsgTask_toTransform,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask_toTransform->lenInBytes,  &pTransform->v_preTransThread.q2  );
							#endif
						}

						//  2014/11/11
						continue;

				   }

				   iErr  =  1;  goto  errLabel;
			  } 

			  //
			  iErr  =  0;  goto  errLabel;		  
		}	
	}

	iErr  =  0;
errLabel:											 
	return  iErr;
}
#endif


int  tmpHandler_findOrgMsgAndProcess_mis_procTaskVideoData(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr,  int  iTaskId,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_VIDEO_DATA  *  pTransferVideoData,  IM_CONTENTU  *  pContentElem,  PROC_TASK_AV  *  pTask  )
{
	int			iErr	=	-1;
	int			index	=	0;
	MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	//
	if  (  !pMisCnt  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "tmpHandler_findOrgMsgAndProcess_mis_procTaskVideoData failed, pMisCnt is null"  )  );
		#endif
		return  -1;
	}
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  ( QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;


	//
	if  (  pTask->ucbVideoConferenceStarter  )  {
		
		if  (  pContentElem->uiType  !=  CONST_imCommType_transferAvInfo  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "procTaskVideoData failed, contentType err"  )  );
			#endif
			goto  errLabel;
		}

		//  2014/11/11
		if  (  pMsgTask->iTaskId  ==  iTaskId  )  {
			if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
				if  (  pTransferVideoData->uiTranNo_openAvDev  ==  pContentElem->transferAvInfo.confMosaicTranInfo_video.video.uiTranNo_openAvDev  
					||  pTransferVideoData->uiTranNo_openAvDev  ==  pContentElem->transferAvInfo.confMosaicTranInfo_resource.video.uiTranNo_openAvDev  )  
				{

					//
					//dispatch_outputConfVideo(  pTask,  pMsgTask,  pTransferVideoData,  &pMisCnt->idInfo,  pTransferVideoData->uiTranNo_openAvDev  );
					dispatch_outputConfVideo(  pTask,  pMsgTask,  pTransferVideoData,  &pMisCnt->idInfo,  pContentElem->transferAvInfo.ass.tranInfo.video.uiTranNo_openAvDev  );
					//			
					iErr  =  1;  goto  errLabel;
				}
			}
		}

		//
		int	index_activeMems_from	=	0;

		//  search in activeMems_from first
		for  (  index_activeMems_from  =  0;  index_activeMems_from  <  pTc->videoConference.usCntLimit_activeMems_from;  index_activeMems_from  ++  )  {
			DLG_TALK_videoConferenceActiveMemFrom * pActiveMem_from = &pTc->videoConference.activeMems_from[index_activeMems_from];
			if  (  pActiveMem_from->avStream.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id  
				&&  pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev  ==  pTransferVideoData->uiTranNo_openAvDev  )  
			{
					#ifdef  __DEBUG__		
							//  traceLogA(  (char*)  "VideoData: usCntLimit_mems_from %d, usCntLimit_activeMems_from %d, video conference starter",  pTransferAvInfoElem->myTask.usCntLimit_mems_from,  pTransferAvInfoElem->myTask.usCntLimit_activeMems_from  );
					#endif

					// 
				    index  =  -1;
										
					//
					pTransferVideoData->tmpInternal.param.index_pMems_from  =  index;
					pTransferVideoData->tmpInternal.param.index_activeMems_from  =  index_activeMems_from;

					//
					QIS_DISPATCH	*	pDispatch  =  MACRO_getDispatch(  *pTask,  index_activeMems_from  );
					if  (  pDispatch  )  {
						q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pDispatch->video.q2,  _T(  "tmp_findOrg_procTaskVideo"  ));
					}

					iErr  =  1;  goto  errLabel;												  															
						
			}
			//
			continue;
		}
		}
	else  if  (  pTask->ucbVideoConference  )  {

			  //
			  if  (  pMsgTask->bFrom_sharedObj  )  {
				  QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pMsgTask->index_sharedObj  );
				  if  (  !pSharedObj  )  goto  errLabel;
				  int  i;
				  for  (  i  =  0;  i  <  mycountof(  pSharedObj->usrs  );  i  ++  )  {
					   SHARED_OBJ_USR  *  pSou  =  &pSharedObj->usrs[i];
					   if  (  !pSou->iTaskId  )  continue;
					   if  (  pSou->iTaskId  !=  iTaskId  )  continue;

					   //					   
					   if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
						   //  traceLog((TCHAR*)  _T(  "video data sent by myself"  )  );
						   
						   bool  bSend  =  true;
						   //
						   bSend  =  canSend(  pSharedObj,  pTc  );

						   if  (  bSend  )  {
							   q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->photomosaic.pOutputQ2,  _T(  "tmp_findOrg_procTaskVideo 9"  ));
							   MIS_CHANNEL	*	pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_media  );
							   if  (  pChannel  )  {

								   //
								   chkToApplyForChannel(  pProcInfo,  CONST_channelType_media, false  );

								   //
								   q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2,  _T(  "tmp_findOrg_procTaskVideo 10"  ));
							   }
						   }

						   //
						   iErr  =  1;  goto  errLabel;				   
				  
					   }

					   //
					   break;
				  }
			  }
			  

			  //
#if  0
		      if  (  pMsgTask->iTaskId  ==  iTaskId  )  {
				  //  2011/01/23				  
				  if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					   //  traceLog((TCHAR*)  _T(  "video data sent by myself"  )  );

					   q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->photomosaic.pOutputQ2  );
					   MIS_CHANNEL	*	pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_media  );
					   if  (  pChannel  )  {

						   //
						   chkToApplyForChannel(  pProcInfo,  pChannel,  CONST_channelType_media  );

						   //
						   q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2  );
					   }

					   //
					   iErr  =  1;  goto  errLabel;				   
				  }
			  }
#endif

			  //
			  if  (  pTask->mem0_from.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id
				  &&  pTask->mem0_from.video.tv_recvd.uiTranNo_openAvDev  ==  pTransferVideoData->uiTranNo_openAvDev  )
			  {
				   int								i						=	0;
				   int								iPos					=	0;
				   TRANSFER_VIDEO_dataMemHead	*	pMem					=	NULL;
				   int								index_activeMems_from	=	0;
				   //unsigned  int					usIndex_pMems_from		=	0;
				   QY_TRANSFORM					*	pTransform				=	NULL;
				   MIS_MSG_TASK					*	pMsgTask_toTransform	=	NULL;
				   TRANSFER_VIDEO_DATA			*	pNew					=	NULL;

				   if  (  !pTask->video.pMsgTask_toTransform  )  {
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "findOrgMsg failed. pMsgTask_toTransform is null"  );
					   #endif
					   goto  errLabel;
				   }
				   pMsgTask_toTransform  =  (  MIS_MSG_TASK  *  )pTask->video.pMsgTask_toTransform;

				   if  (  !pTransferVideoData->usCnt  )  {
					   pTransferVideoData->usCnt  =  1;	//  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
					   pTransferVideoData->mems[0].uiLen  =  pTransferVideoData->uiLen;
				   }
				   if  (  pTransferVideoData->usCnt  >  mycountof(  pTransferVideoData->mems  )  )  goto  errLabel;

				   #ifdef  __DEBUG__
						#if  0
						   if  (  pTransferVideoData->stat.tSelectTime  )  {
							   TCHAR  tBuf[128];
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "find_procTaskVideodata:  tSelectTime %I64u"  ),  pTransferVideoData->stat.tSelectTime  );
							   showInfo_open0(  0,  _T(  "find_procTaskVideoData"  ),  tBuf  );
						   }
						#endif
						   //  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video len %d"  ),  pTransferVideoData->uiLen  );
				   #endif


				   for  (  iPos  =  0,  i  =  0;  i  <  pTransferVideoData->usCnt;  iPos  =  iPos  +  pTransferVideoData->mems[i].uiLen,  i  ++  )  {
					    pMem  =  &pTransferVideoData->mems[i];
						if  (  !pMem->uiLen  )  {
							//
							#ifdef  __DEBUG__
									//traceLogA(  (char*)  "findOrgMsg: transferVideoMem.uiLen is 0. skipped."  );
							#endif
							//
							continue;
						}

						if  (  iPos  +  pTransferVideoData->mems[i].uiLen  >  pTransferVideoData->uiLen  )  {
							#ifdef  __DEBUG__
									traceLogA(  (char*)  "findOrgMsg failed: iPos + mem.uiLen > data.uiLen"  );
							#endif
							goto  errLabel;
						}

						if  (  !pMem->idInfo.ui64Id  )  pMem->idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;
						//
#if  0
						if  (  pTask->confMosaicTrans.bExists_confMosaic
							&&  pMem->idInfo.ui64Id  ==  pTask->mem0_from.idInfo.ui64Id  )
						{
							PROC_conf_mosaic  *  pProcConfMosaic  =  NULL;
							//
							if  (  pMem->uiTranNo_openAvDev  ==  pTask->confMosaicTrans.confMosaic_video.taskAvFrom.video.tv_recvd.uiTranNo_openAvDev  )  {
								pProcConfMosaic  =  &pTask->confMosaicTrans.confMosaic_video;
								}
							else  if  (  pMem->uiTranNo_openAvDev  ==  pTask->confMosaicTrans.confMosaic_resource.taskAvFrom.video.tv_recvd.uiTranNo_openAvDev  )  {
									  pProcConfMosaic  =  &pTask->confMosaicTrans.confMosaic_resource;
							}
							if  (  pProcConfMosaic  )  {
								//
								#ifdef  __DEBUG__
										//traceLog((TCHAR*)  _T(  "It's a pkt of mosaic video data"  )  );
								#endif
								//
								MACRO_memset_misMsgTask(  pMsgTask_toTransform  );
								memcpy(  pMsgTask_toTransform,  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  );
								pMsgTask_toTransform->data.route.idInfo_from.ui64Id  =  pMem->idInfo.ui64Id;
								pMsgTask_toTransform->data.route.idInfo_to.ui64Id  =  pMsgTask->data.route.idInfo_to.ui64Id;
								pNew  =  (  TRANSFER_VIDEO_DATA  *  )pMsgTask_toTransform->data.buf;
								memset(  pNew,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
								pNew->uiType  =  pTransferVideoData->uiType;
								pNew->uiTranNo_openAvDev  =  pMem->uiTranNo_openAvDev;
								memcpy(  &pNew->mems[0],  pMem,  sizeof(  pNew->mems[0]  )  );
								pNew->usCnt  =  1;
								pNew->uiLen  =  pMem->uiLen;
								memcpy(  pNew->buf,  pTransferVideoData->buf  +  iPos,  pNew->uiLen  );

								//  2014/11/11
								//
								pMsgTask_toTransform->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  +  pNew->uiLen;

								pTransform  =  &pProcConfMosaic->transform;
								if  (  pTransform  )  {
									//  								
									q2PostMsgAndTrigger(  pMsgTask_toTransform,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask_toTransform->lenInBytes,  &pTransform->v_preTransThread.q2  );						
								}
								//
								continue;
							}
						}
#endif
						//
						for  (  index_activeMems_from  =  0;  index_activeMems_from  <  pTc->videoConference.usCntLimit_activeMems_from;  index_activeMems_from  ++  )  {
							if  (  pMem->idInfo.ui64Id  ==  pTc->videoConference.activeMems_from[index_activeMems_from].avStream.idInfo.ui64Id
								&&  pMem->uiTranNo_openAvDev  ==  pTc->videoConference.activeMems_from[index_activeMems_from].avStream.obj.tranInfo.video.uiTranNo_openAvDev  )  break;
						}
						//
						//
						if  (  index_activeMems_from  ==  pTc->videoConference.usCntLimit_activeMems_from  )  {
							//
							TCHAR  tBuf[128];
							_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "findOrgMsg: video, conf%I64u, from %I64u, can't get index_activeMems_from, skipped."  ),  pMsgTask->addr_logicalPeer.idInfo.ui64Id,  pMem->idInfo.ui64Id  );
							//
							#ifdef  __DEBUG__
									traceLog((TCHAR*)  tBuf  );
							#endif
							showInfo_open0(  0,  0,  tBuf  );

							//
							goto  errLabel;

#if  0
							//  2009/06/01
							if  (  pTask->ucbVideoConference  &&  !pTask->ucbVideoConferenceStarter  &&  pMsgTask->pMisCnt  )  {
								MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
								pMisCnt->refreshVideoConferenceActiveMems.iTaskId  =  iTaskId;
								pMisCnt->refreshVideoConferenceActiveMems.bNeedRefreshed  =  TRUE;
							}

							continue;
#endif
						}
						//usIndex_pMems_from  =  -1;//pTc->videoConference.activeMems_from[index_activeMems_from].usIndex_pMems_from;
#if  0
						TASK_AV_FROM  *  pFrom  =  NULL;
						pFrom  =  getTaskAvFrom(  pTask,  usIndex_pMems_from,  _T(  ""  )  );
						if  (  !pFrom  )  goto  errLabel;
#endif
						DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[index_activeMems_from];

						//
#if  0
						if  (  pFrom->video.tv_recvd.uiTranNo_openAvDev  !=  pMem->uiTranNo_openAvDev  )  {
							#ifdef  __DEBUG__
									traceLog((TCHAR*)  _T(  "findOrgMsg: video.tn not matched"  )  );
							#endif
							qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video, %I64u, from.tn %d != pMem.%d, skipped."  ),  pFrom->idInfo.ui64Id,  pFrom->video.tv_recvd.uiTranNo_openAvDev,  pMem->uiTranNo_openAvDev  );

							//  2009/06/01
							if  (  pTask->ucbVideoConference  &&  !pTask->ucbVideoConferenceStarter  &&  pMsgTask->pMisCnt  )  {
								MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
								pMisCnt->refreshVideoConferenceActiveMems.iTaskId  =  iTaskId;
								pMisCnt->refreshVideoConferenceActiveMems.bNeedRefreshed  =  TRUE;
							}

							continue;
						}
#endif



						//
						MACRO_memset_misMsgTask(  pMsgTask_toTransform  );
						memcpy(  pMsgTask_toTransform,  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  );
						pMsgTask_toTransform->data.route.idInfo_from.ui64Id  =  pTc->videoConference.activeMems_from[index_activeMems_from].avStream.idInfo.ui64Id;
						pMsgTask_toTransform->data.route.idInfo_to.ui64Id  =  pMsgTask->data.route.idInfo_to.ui64Id;
						pNew  =  (  TRANSFER_VIDEO_DATA  *  )pMsgTask_toTransform->data.buf;
						memset(  pNew,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
						pNew->uiType  =  pTransferVideoData->uiType;
						pNew->uiTranNo_openAvDev  =  pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev;
						memcpy(  &pNew->mems[0],  pMem,  sizeof(  pNew->mems[0]  )  );
						pNew->usCnt  =  1;
						pNew->uiLen  =  pMem->uiLen;
						memcpy(  pNew->buf,  pTransferVideoData->buf  +  iPos,  pNew->uiLen  );

						//  2017/09/05
					#if  0
						if  (  i  ==  pTransferVideoData->usCnt  -  1  )  {
							pNew->stat  =  pTransferVideoData->stat;
						}
					#endif

						//										
						pNew->tmpInternal.param.index_pMems_from  =  -1;//pTc->videoConference.activeMems_from[index_activeMems_from].usIndex_pMems_from;
						pNew->tmpInternal.param.index_activeMems_from  =  index_activeMems_from;

						//
						pMsgTask_toTransform->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  +  pNew->uiLen;

						pTransform  =  MACRO_getTransform(  *pTask,  index_activeMems_from  );
						if  (  pTransform  )  {

							//
							if (isQ2Warning(&pTransform->v_preTransThread.q2,10)) 
							{
								TCHAR  tBuf[128];
								_sntprintf(tBuf, mycountof(tBuf), _T("%s is full, to empty it before postMsg to it"), pTransform->v_preTransThread.q2.cfg.name);
								showInfo_open0(0, 0, tBuf);
								emptyQ2(&pTransform->v_preTransThread.q2);
							}

							//  
							#if  0	//  2011/12/10
								q2PostMsgAndTrigger(  pMsgTask_toTransform,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask_toTransform->lenInBytes,  &pTransform->video.q2  );
							#else
								q2PostMsgAndTrigger(  pMsgTask_toTransform,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask_toTransform->lenInBytes,  &pTransform->v_preTransThread.q2,  _T(  "tmp_findOrg_procTaskVideo 11"  ));
							#endif
						}

						//  2014/11/11
						continue;
				   }

				   iErr  =  1;  goto  errLabel;
			  }
		      }	//  end of processing confMem
	else  {  //  

		  if  (  pMsgTask->bFrom_sharedObj  )  {
			  QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pMsgTask->index_sharedObj  );
			  if  (  !pSharedObj  )  goto  errLabel;
			  int  i;
			  for  (  i  =  0;  i  <  mycountof(  pSharedObj->usrs  );  i  ++  )  {
				   SHARED_OBJ_USR  *  pSou  =  &pSharedObj->usrs[i];
				   if  (  !pSou->iTaskId  )  continue;
				   if  (  pSou->iTaskId  !=  iTaskId  )  continue;
				   
				   if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					   //  traceLog((TCHAR*)  _T(  "video data sent by myself"  )  );				  
				  
					   bool  bSend  =  false;
					   bSend  =  canSend(  pSharedObj,  pTc  );
				   
					   if  (  bSend  )  {
						   if  (  isEmpty_ROUTE_sendLocalAv(  &pTaskInfo->var.curRoute_sendLocalAv)  )  bSend  =  false;
					   }

					   if  (  bSend  )				  
					   {
					  				  
						  //
						   q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->photomosaic.pOutputQ2,  _T(  "tmp_findOrg_procVideo 1"  ));
						   MIS_CHANNEL	*	pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_media  );
						   if  (  pChannel  )  {

							   //
							   chkToApplyForChannel(  pProcInfo,  CONST_channelType_media, false  );

							   //
							   q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2,  _T(  "tmp_findOrg_procVideo 2"  ));
						   }
				  
				  
					   }
					   
					   //				  
					   iErr  =  1;  goto  errLabel;				   			  
				   }


				   break;
			  }
			
		  }

#if  0
		  if  (  pMsgTask->iTaskId  ==  iTaskId  )  {
			  //  2011/01/23				  
			  if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
				   				  
				  //  traceLog((TCHAR*)  _T(  "video data sent by myself"  )  );				  
				  if  (  !isEmpty_ROUTE_sendLocalAv(  &pTaskInfo->var.curRoute_sendLocalAv)  )  {
					  				  
					  //
					   q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->photomosaic.pOutputQ2  );
					   MIS_CHANNEL	*	pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_media  );
					   if  (  pChannel  )  {

						   //
						   chkToApplyForChannel(  pProcInfo,  pChannel,  CONST_channelType_media  );

						   //
						   q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2  );
					   }
				  
				  }
				  				  
				  //				  
				  iErr  =  1;  goto  errLabel;				   
			  }
		  }
#endif

		  //  2014/11/21
		  if  (  pTask->applyForProxy.bRecvd_proxyReply  )  {		//  applier for proxy
			  if  (  pTask->applyForProxy.proxyReply.proxy.uiTranNo_openAvDev_v  ==  pTransferVideoData->uiTranNo_openAvDev  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "findOrgMsg: applyForProxy: my pkt is sent back. skipped"  )  );
				  #endif
				  iErr  =  1;  goto  errLabel;
			  }
		  }

		  //  2014/11/21
		  if  (  !pTask->receiver.bRecvd_proxiedTranInfo  )  {  //  一般性的数据包处理，或者是proxy
		  		  
			  //  search in mems_from directly
			  for  (  index  =  0;  index  <  pTc->videoConference.usCntLimit_activeMems_from;  index  ++  )  {
				  DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[index];
				   //
				   if  (  pActiveMem_from->avStream.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id
					   &&  pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev  ==  pTransferVideoData->uiTranNo_openAvDev  )
				   {		
						#ifdef  __DEBUG__
								//  traceLogA(  (char*)  "VideoData: usCntLimit_mems_from %d",  pTransferAvInfoElem->myTask.usCntLimit_mems_from  );
						#endif
					    //  


					   //
					   pTransferVideoData->tmpInternal.param.index_pMems_from  =  -1;
					   pTransferVideoData->tmpInternal.param.index_activeMems_from  =  index;

					   //  2014/11/21
					   if  (  pTask->doProxy.bExists_avProxy  )  {

						   int	index_activeMems_from	=	0;
					   					   
						   //
						   QIS_DISPATCH	*	pDispatch  =  MACRO_getDispatch(  *pTask,  index_activeMems_from  );
						   if  (  pDispatch  )  {
							   q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pDispatch->video.q2,  _T(  "tmp_findOrg_procVide 3"  ));
						   }
						   iErr  =  1;  goto  errLabel;
					   }

					   //
					   QY_TRANSFORM  *  pTransform  =  MACRO_getTransform(  *pTask,  pTransferVideoData->tmpInternal.param.index_activeMems_from  );
					   if  (  pTransform  )  {
						   //  
						   QY_Q2	*	pQ2	=	&pTransform->v_preTransThread.q2;
						   if  (  !pTransform->v_preTransThread.hThread
							   &&  pTransform->video.hThread  )
						   {
							   pQ2  =  &pTransform->video.q2;
						   }

						   //
						   q2PostMsgAndTrigger(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pQ2,  _T(  "tmp_findOrg_procVideo 4"  ));
					   }
					   iErr  =  1;  goto  errLabel;												  
				   }			  
			  }
			  //
			  }
		  else  {  //  receiver from proxy				  			 
			  if  (  pTask->mem0_from.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id
				  &&  pTask->mem0_from.video.tv_recvd.uiTranNo_openAvDev  ==  pTransferVideoData->uiTranNo_openAvDev  )
			  {
				  //  2014/11/21
				  if  (  pTask->receiver.proxied_from.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					  #ifdef  __DEBUG__
							  traceLog((TCHAR*)  _T(  "findOrgMsg: v receiver: my pkt is sent back. skipped"  )  );
					  #endif
					  iErr  =  1;  goto  errLabel;
				  }
				  	
				  //
				   int								i						=	0;
				   int								iPos					=	0;
				   TRANSFER_VIDEO_dataMemHead	*	pMem					=	NULL;
				   int								index_activeMems_from	=	0;
				   unsigned  int					usIndex_pMems_from		=	0;
				   QY_TRANSFORM					*	pTransform				=	NULL;
				   MIS_MSG_TASK					*	pMsgTask_toTransform	=	NULL;
				   TRANSFER_VIDEO_DATA			*	pNew					=	NULL;

				   if  (  !pTask->video.pMsgTask_toTransform  )  {
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "findOrgMsg failed. pMsgTask_toTransform is null"  );
					   #endif
					   goto  errLabel;
				   }
				   pMsgTask_toTransform  =  (  MIS_MSG_TASK  *  )pTask->video.pMsgTask_toTransform;

				   if  (  !pTransferVideoData->usCnt  )  {
					   pTransferVideoData->usCnt  =  1;	//  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
					   pTransferVideoData->mems[0].uiLen  =  pTransferVideoData->uiLen;
				   }
				   if  (  pTransferVideoData->usCnt  >  mycountof(  pTransferVideoData->mems  )  )  goto  errLabel;

				   #ifdef  __DEBUG__
						   //  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video len %d"  ),  pTransferVideoData->uiLen  );
				   #endif


				   for  (  iPos  =  0,  i  =  0;  i  <  pTransferVideoData->usCnt;  iPos  =  iPos  +  pTransferVideoData->mems[i].uiLen,  i  ++  )  {
					    pMem  =  &pTransferVideoData->mems[i];
						if  (  !pMem->uiLen  )  {
						    #ifdef  __DEBUG__
									traceLogA(  (char*)  "findOrgMsg: transferVideoMem.uiLen is 0. skipped."  );
							#endif
							continue;
						}

						if  (  iPos  +  pTransferVideoData->mems[i].uiLen  >  pTransferVideoData->uiLen  )  {
							#ifdef  __DEBUG__
									traceLogA(  (char*)  "findOrgMsg failed: iPos + mem.uiLen > data.uiLen"  );
							#endif
							goto  errLabel;
						}

						//if  (  !pMem->idInfo.ui64Id  )  pMem->idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;

						//											
						usIndex_pMems_from  =  1;
						TASK_AV_FROM  *  pFrom  =  NULL;
						pFrom  =  getTaskAvFrom(  pTask,  usIndex_pMems_from,  _T(  ""  )  );
						if  (  !pFrom  )  goto  errLabel;

												//
						MACRO_memset_misMsgTask(  pMsgTask_toTransform  );
						memcpy(  pMsgTask_toTransform,  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  );
						pMsgTask_toTransform->data.route.idInfo_from.ui64Id  =  pFrom->idInfo.ui64Id;
						pMsgTask_toTransform->data.route.idInfo_to.ui64Id  =  pMsgTask->data.route.idInfo_to.ui64Id;
						pNew  =  (  TRANSFER_VIDEO_DATA  *  )pMsgTask_toTransform->data.buf;
						memset(  pNew,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
						pNew->uiType  =  pTransferVideoData->uiType;
						pNew->uiTranNo_openAvDev  =  pFrom->video.tv_recvd.uiTranNo_openAvDev;
						memcpy(  &pNew->mems[0],  pMem,  sizeof(  pNew->mems[0]  )  );
						pNew->usCnt  =  1;
						pNew->uiLen  =  pMem->uiLen;
						memcpy(  pNew->buf,  pTransferVideoData->buf  +  iPos,  pNew->uiLen  );

						//										
						pNew->tmpInternal.param.index_pMems_from  =  usIndex_pMems_from;
						pNew->tmpInternal.param.index_activeMems_from  =  index_activeMems_from;

						//
						pMsgTask_toTransform->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  +  pNew->uiLen;

						pTransform  =  MACRO_getTransform(  *pTask,  index_activeMems_from  );
						if  (  pTransform  )  {
							//  
							#if  0	//  2011/12/10
								q2PostMsgAndTrigger(  pMsgTask_toTransform,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask_toTransform->lenInBytes,  &pTransform->video.q2  );
							#else
								q2PostMsgAndTrigger(  pMsgTask_toTransform,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask_toTransform->lenInBytes,  &pTransform->v_preTransThread.q2,  _T(  "tmp_findOrg_procVideo 5"  ));
							#endif
						}

						//  2014/11/11
						continue;

				   }

				   iErr  =  1;  goto  errLabel;
			  } 

			  //
			  iErr  =  0;  goto  errLabel;		  
		}	
	}

	iErr  =  0;
errLabel:											 
	return  iErr;
}


//
//
int  tmpHandler_find_procTaskVideoDataResp(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TASK  *  pMsgElem,  MIS_MSG_INPUT  *  pMsgInput,  TRANSFER_VIDEO_dataResp  *  pResp,  PROC_TASK_AV  *  pTask  )
{
	int  iErr  =  -1;
	IM_CONTENTU		*	pContentElem	=	(  IM_CONTENTU  *  )pMsgElem->data.buf;
	int			index	=	0;
	//
	MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMsgInput->pMisCnt;
	if  (  !pMisCnt  )  {
		return  -1;
	}
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	//
	if  (  pContentElem->uiType  ==  CONST_imCommType_transferAvInfo  )  {
		AV_TRAN_INFO  *  pTranInfo  =  &pContentElem->transferAvInfo.ass.tranInfo;
		//PROC_TASK_AV  *  pTask  =  get_transferAvInfo_pTask(  &pContentElem->transferAvInfo,  _T(  ""  )  );													   
		if  (  !pTask  )  goto  errLabel;
		
		//
		if  (  pTask->ucbVideoConferenceStarter  )  {

			//
			if  (  pResp->idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
				if  (  pResp->uiTranNo_openAvDev  ==  pContentElem->transferAvInfo.confMosaicTranInfo_video.video.uiTranNo_openAvDev
					||  pResp->uiTranNo_openAvDev  ==  pContentElem->transferAvInfo.confMosaicTranInfo_resource.video.uiTranNo_openAvDev  )
				{
					int  ii  =  0;

					if  (  procTaskVideoDataResp(  pProcInfo,  pTranInfo,  pTask,  pMsgInput,  pResp  )  )  goto  errLabel;
					
					iErr  =  1;  goto  errLabel;

				}
			}

			//
			int	index_activeMems_from	=	0;

			//  search in activeMems_from first
			for  (  index_activeMems_from  =  0;  index_activeMems_from  <  pTc->videoConference.usCntLimit_activeMems_from;  index_activeMems_from  ++  )  {
				if  (  pTc->videoConference.activeMems_from[index_activeMems_from].avStream.idInfo.ui64Id  ==  pResp->idInfo.ui64Id  )  break;								
			}
			//  use searched index to process video
			if  (  index_activeMems_from  <  pTc->videoConference.usCntLimit_activeMems_from  )  {											
				index  =  -1;//pTc->videoConference.activeMems_from[index_activeMems_from].usIndex_pMems_from;							
				if  (  index  >=  0  &&  index  <  pTc->videoConference.usCntLimit_mems_from  )  {						
					TASK_AV_FROM  *  pFrom  =  &pTc->videoConference.pMems_from[index];
	
					if  (  pFrom->idInfo.ui64Id  ==  pResp->idInfo.ui64Id
					&&  pFrom->video.tv_recvd.uiTranNo_openAvDev  ==  pResp->uiTranNo_openAvDev  )							
					{
						int  ii  =  0;

						if  (  procTaskVideoDataResp(  pProcInfo,  pTranInfo,  pTask,  pMsgInput,  pResp  )  )  goto  errLabel;

						iErr  =  1;  goto  errLabel;

					}
	
				}
	
			}

		}


		//
		if  (  pMsgElem->data.route.idInfo_from.ui64Id  ==  pMsgInput->data.route.idInfo_to.ui64Id
			&&  pTranInfo->video.uiTranNo_openAvDev  ==  pResp->uiTranNo_openAvDev  )														   
		{															   
															   
			//  OutputDebugString(  _T(  "VideoData Resp\n"  )  );
												   															   
		
			if  (  procTaskVideoDataResp(  pProcInfo,  pTranInfo,  pTask,  pMsgInput,  pResp  )  )  goto  errLabel;

	
			iErr  =  1;  goto  errLabel;
		
		}
	}
	else  if  (  pContentElem->uiType  ==  CONST_imCommType_transferAvReplyInfo  )  {
		  	  AV_TRAN_INFO  *  pTranInfo  =  &pContentElem->transferAvReplyInfo.tranInfo;
			  //PROC_TASK_AV  *  pTask  =  get_transferAvReplyInfo_pTask(  &pContentElem->transferAvReplyInfo,  _T(  ""  )  );
			  if  (  !pTask  )  goto  errLabel;
													   
			  if  (  pMsgElem->data.route.idInfo_to.ui64Id  ==  pMsgInput->data.route.idInfo_from.ui64Id												
				  &&  pTranInfo->video.uiTranNo_openAvDev  ==  pResp->uiTranNo_openAvDev  )														   
			  {															   
				  //  OutputDebugString(  _T(  "VideoData Resp, ½«µ÷ÕûÊÓÆµ·¢ËÍÆµÂÊ\n"  )  );
				  				
				  if  (  procTaskVideoDataResp(  pProcInfo,  pTranInfo,  pTask,  pMsgInput,  pResp  )  )  goto  errLabel;
				  					
				  iErr  =  1;  goto  errLabel;
					
			  }

	}

	
	iErr  =  0;
errLabel:
	return  iErr;
}


 //  2012/05/07
 int  tmpHandler_findOrgMsgAndProcess_mis_procTaskGpsData(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr,  int  iTaskId,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_GPS_DATA  *  pTransferGpsData,  void  *  pTranInfo,  PROC_TASK_GPS  *  pTask  )
{
	int			iErr	=	-1;
	QY_MC* pQyMc = pProcInfo->pQyMc;// QY_GET_GBUF();
	MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;


	QY_PLAYER_gps	*	pPlayer_gps	=	NULL;

	//  校对player
	if  (  pTask->iIndex_player_gps  >=  0  &&  pTask->iIndex_player_gps  <  pProcInfo->gps.usCnt_players  )  {
		pPlayer_gps  =  &pProcInfo->gps.pPlayers[pTask->iIndex_player_gps];
		if  (  pPlayer_gps->idInfo.ui64Id  !=  pAddr->idInfo.ui64Id
			||  pPlayer_gps->iTaskId  !=  iTaskId  )
		{
			pTask->iIndex_player_gps  =  -1;
			pPlayer_gps  =  NULL;
		}
	}

	if  (  !pPlayer_gps  )  {	//  如果无效, 查找是否有合适的player
		int  k;
		for  (  k  =  0;  k  <  pProcInfo->gps.usCnt_players;  k  ++  )  {
			if  (  pProcInfo->gps.pPlayers[k].idInfo.ui64Id  ==  pAddr->idInfo.ui64Id
				&&  pProcInfo->gps.pPlayers[k].iTaskId  ==  iTaskId  )
			{
				break;
			}
		}
		if  (  k  <  pProcInfo->gps.usCnt_players  )  {
			pTask->iIndex_player_gps  =  k;
			pPlayer_gps  =  &pProcInfo->gps.pPlayers[k];

		}
	}
	if  (  !pPlayer_gps  )  {	//  如果没有, 那么申请一个player

		DWORD	dwTickCnt  =  GetTickCount(  );

		if  (  dwTickCnt  -  pTask->dwTickCnt_lastApplyForPlayer  <  200  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: gps, apply for player too quickly, skipped."  )  );
			goto  errLabel;
		}
		pTask->dwTickCnt_lastApplyForPlayer  =  dwTickCnt;

		//
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procGpsData : %I64u apply for player"  ),  pAddr->idInfo.ui64Id  );

		//
		MIS_MSG_applyForPlayer_qmc	msg;
		memset(  &msg,  0,  sizeof(  msg  )  );
		msg.uiType  =  CONST_misMsgType_applyForPlayer_qmc;
		msg.iTaskId  =  iTaskId;								//  2009/09/17
		msg.idInfo_recorder.ui64Id  =  pAddr->idInfo.ui64Id;
		msg.bGps  =  TRUE;

		//					  
		qPostMsg(  &msg,  sizeof(  msg  ),  &pQyMc->gui.processQ,  _T(  "tmp_findOrg_procGps"  ));
		PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
			 
		iErr  =  -2;  goto  errLabel;
	}			



	//  2012/04/26
	if  (  pTransferGpsData->tLastTime_showFrameInfo_020534  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "shall send resp"  )  );
		#endif
		
	}

													 
	//	
	MIS_MSG_procGps_qmc	msg;	
	memset(  &msg,  0,  sizeof(  msg  )  );							
	msg.uiType  =  CONST_misMsgType_procGps_qmc;										
	msg.idInfo_peer.ui64Id  =  pMsgTask->addr_logicalPeer.idInfo.ui64Id;												
	memcpy(  &msg.transferGpsData,  pTransferGpsData,  sizeof(  msg.transferGpsData  )  );
	int  len; len = sizeof(msg);


#if  0
	q2PostMsg(  &msg,  len,  &pQyMc->gui.gpsQ2  );
	PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_gpsMsgArrive,  0  );
#endif

	q2PostMsg(  &msg,  len,  &pPlayer_gps->q2,  _T(  "tmp_findOrg_procGps3"  ));
	PostMessage(  pTask->hWnd_task,  CONST_qyWm_postComm,  CONST_qyWmParam_gpsMsgArrive,  pTask->iIndex_player_gps  );

	//
	pPlayer_gps->dwTickCnt_lastRecvd  =  GetTickCount(  );


	iErr  =  0;
errLabel:
	return  iErr;
 }

//  2014/08/28
  //  int  procTaskProcReq_applyForKeyFrame(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr,  int  iTaskId,  MIS_MSG_TASK  *  pMsgTask,  TASK_PROC_REQ  *  pTaskProcReq,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask  )
 int  procTaskProcReq_applyForKeyFrame(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr,  int  iTaskId,  MIS_MSG_TASK  *  pMsgTask,  TASK_PROC_REQ  *  pTaskProcReq,  IM_CONTENTU  *  pContentElem,  PROC_TASK_AV  *  pTask  )	  
  {
	  int			iErr	=	-1;
	  QY_MC* pQyMc = pProcInfo->pQyMc;// QY_GET_GBUF();
	  MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;


#ifdef  __DEBUG__
	  if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
		  traceLog((TCHAR*)_T("procTaskProcReq_applyForKeyFrame called"));
	  }
#endif

		if  (  pTask->ucbVideoConferenceStarter  )  {
			#ifdef  __DEBUG__
			if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
				traceLog((TCHAR*)_T("Not finished. for conf starter"));
			}
			#endif
			//
#if  0
			if  (  pTaskProcReq->vStream.idInfo_src.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
				if  (  pTaskProcReq->vStream.uiTranNo_openAvDev_src  !=  pTask->mem0_from.video.uiTranNo_openAvDev  )  {
					showInfo_open0(  0,  0,  _T(  "procTaskProcReq_applyForKeyFrame failed, confStarter, tn_openAvDev_src not matched"  )  );
					goto  errLabel;
				}
				//
				setFlg_forceKeyFrame(  pTask->iIndex_sharedObj  );
				//
				iErr  =  0;  goto  errLabel;
			}
#endif
			if  (  pTaskProcReq->vStream.uiTranNo_openAvDev  ==  pTask->mem0_from.video.tv_recvd.uiTranNo_openAvDev  )  {
				//
				setFlg_forceKeyFrame(  pProcInfo,  pTask->iIndex_sharedObj  );
				//
				iErr  =  0;  goto  errLabel;
			}

			//  2014/12/06
			if  (  pContentElem->uiType  !=  CONST_imCommType_transferAvInfo  )  {
				goto  errLabel;
			}
			TRANSFER_AV_INFO  *  pTransferAvInfo  =  &pContentElem->transferAvInfo;
			//
			if  (  pTaskProcReq->vStream.uiTranNo_openAvDev  ==  pTransferAvInfo->confMosaicTranInfo_video.video.uiTranNo_openAvDev  )  {
				//
				setFlg_forceKeyFrame(  pProcInfo,  pTask->confMosaicMaker.iIndex_sharedObj_video  );
				//
				iErr  =  0;  goto  errLabel;
			}
			//
			if  (  pTaskProcReq->vStream.uiTranNo_openAvDev  ==  pTransferAvInfo->confMosaicTranInfo_resource.video.uiTranNo_openAvDev  )  {
				//
				setFlg_forceKeyFrame(  pProcInfo,  pTask->confMosaicMaker.iIndex_sharedObj_resource  );
				//
				iErr  =  0;  goto  errLabel;
			}

			// others
		    #ifdef  __DEBUG__
					if  (  pProcInfo->cfg.debugStatusInfo.bDbgDetail){
				    traceLog((TCHAR*)  _T(  "Not finished. for conf starter"  )  );
					}
			#endif					
			showInfo_open0(  0,  0,  _T(  "Not finished: procTaskProcReq_applyForKeyFrame, conf starter: for others"  )  );
			goto  errLabel;

			}
		else  if  (  pTask->ucbVideoConference  )  {
				  setFlg_forceKeyFrame(  pProcInfo,  pTask->iIndex_sharedObj  );
				  }
		else  {
			  setFlg_forceKeyFrame(  pProcInfo,  pTask->iIndex_sharedObj  );
		}


	  iErr  =  0;
errLabel:
	  return  iErr;

  }

 //
 int  tmpHandler_findOrgMsgAndProc_is(QY_MC* pQyMc, void* pMsg_toBeSearchedParam, void* p1, TASK_common* taskElemParam)
 {

	 int					iErr = -1;
	 MIS_MSGU* pMsg_toBeSearched = (MIS_MSGU*)pMsg_toBeSearchedParam;
	 //  p1
	 //
	 //QY_MC				*	pQyMc				=	QY_GET_GBUF(  );
	 QY_SERVICEGUI_INFO* pSgi = getServiceGuiInfo(pQyMc, CONST_qyServiceId_is);
	 if (!pSgi)  return  -1;
	 MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pSgi->pVar;
	 if (!pProcInfo)  return  -1;
	 int					tmpiRet = 0;
	 QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	 if (!pDbFuncs)  return  -1;// goto  errLabel;
	 QM_dbFuncs& g_dbFuncs = *pDbFuncs;

	 //
	 TASK_common* taskElem = (TASK_common*)taskElemParam;
	 QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, taskElem->m_index_taskInfo);
	 if (pTaskInfo == NULL) goto errLabel;

	 MIS_MSGU* pMsgElemParam; pMsgElemParam = &pTaskInfo->var.pTaskData->msgU;

	 //
	 bool  bDbg; bDbg = false;
#ifdef  __DEBUG__
	 //bDbg  =  true;
#endif

	//
	 switch (((MIS_MSGU*)pMsgElemParam)->uiType) {
	 case  CONST_misMsgType_req: {
		 MIS_MSG_REQ* pMsgElem = (MIS_MSG_REQ*)pMsgElemParam;
		 MIS_CNT* pMisCntElem = (MIS_CNT*)pMsgElem->pMisCnt;
		 IM_CONTENTU* pContentElem = M_getMsgContent(pMsgElem->ucFlg, &pMsgElem->data);
		 //
		 switch (pMsg_toBeSearched->uiType) {
		 case  CONST_misMsgType_input: {
			 MIS_MSG_INPUT* pMsgInput = &pMsg_toBeSearched->input;
			 //
			 if (pMsgElem->tStartTime == pMsgInput->tStartTime
				 && pMsgElem->uiTranNo == pMsgInput->uiTranNo)
			 {
				 pMsgInput->usCode_org = pMsgElem->usCode;
				 iErr = 1;  goto  errLabel;		//  ÕÒµ½ÁË
			 }
			 //
		 }
									 break;
		 default:
			 break;
		 }
		 //
	 }
							   break;
	 case  CONST_misMsgType_task: {
		 MIS_MSG_TASK* pMsgElem = (MIS_MSG_TASK*)pMsgElemParam;
		 MIS_CNT* pMisCntElem = (MIS_CNT*)pMsgElem->pMisCnt;
		 IM_CONTENTU* pContentElem = (IM_CONTENTU*)pMsgElem->data.buf;
		 //
		 switch (pMsg_toBeSearched->uiType) {
		 case  CONST_misMsgType_task: {
			 MIS_MSG_TASK* pMsgTask = &pMsg_toBeSearched->task;
			 IM_CONTENTU* pContent = (IM_CONTENTU*)pMsgTask->data.buf;

			 //
#ifdef  __DEBUG__	//  2014/08/28
			 if (pContent->uiType == CONST_imCommType_taskProcReq) {
				 if (pContent->taskProcReq.usOp == CONST_imOp_recv_applyForKeyFrame) {
					 int  i;
					 i = 9;
				 }
				 //
				 if (pContent->taskProcReq.usOp == CONST_imOp_recv_applyForOrgReq) {
					 int  ii = 0;
				 }
			 }
#endif

			 //
			 if (!isUcFlgResp(pMsgTask->ucFlg)) {
				 if (pContentElem->uiType == CONST_imCommType_transferFileReq) {
					 if (pContent->uiType == CONST_imCommType_transferFileReq) {
						 if (pMsgElem->tStartTime == pMsgTask->tStartTime
							 && pMsgElem->uiTranNo == pMsgTask->uiTranNo)
						 {
							 //
#ifdef  __DEBUG__
							 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is: fileReq matched");
#endif
							 //
							 iErr = 1;  goto  errLabel;
						 }

					 }
					 if (pContent->uiType == CONST_imCommType_transferFileReplyReq) {	//  ÕâÊÇÔÚfile·¢ËÍ¶Ë£¬½ÓÊÕ»Ø¸´À´Ê±µÄ¼ìË÷
						 if (pMsgElem->tStartTime == pContent->transferFileReplyReq.tStartTime_org
							 && pMsgElem->uiTranNo == pContent->transferFileReplyReq.uiTranNo_org)
						 {
							 //
#ifdef  __DEBUG__
							 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is: msg - replyReq is matched");
#endif
							 //
							 pMsgTask->addr_logicalPeer.idInfo.ui64Id = pMsgElem->addr_logicalPeer.idInfo.ui64Id;
							 //
							 iErr = 1;  goto  errLabel;
						 }
					 }
					 if (pContent->uiType == CONST_imCommType_taskProcReq) {	//  file·¢ËÍ¶Ë£¬×Ô¼ºÓÖ×·¼ÓÁË±ÈÈçÈ¡ÏûµÈ²Ù×÷ºóµÄ¹¤×÷  
						 if (pMsgElem->tStartTime == pContent->taskProcReq.tStartTime_org
							 && pMsgElem->uiTranNo == pContent->taskProcReq.uiTranNo_org)
						 {
							 //
#ifdef  __DEBUG__
							 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is: msg - procReq is matched");
#endif
							 //
							 iErr = 1;  goto  errLabel;
						 }
					 }
				 }
				 if (pContentElem->uiType == CONST_imCommType_transferFileReplyReq) {	//  file½ÓÊÕ¶Ë
					 if (pContent->uiType == CONST_imCommType_taskProcReq) {
						 if (pContentElem->transferFileReplyReq.tStartTime_org == pContent->taskProcReq.tStartTime_org
							 && pContentElem->transferFileReplyReq.uiTranNo_org == pContent->taskProcReq.uiTranNo_org)
						 {
#ifdef  __DEBUG__
							 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is: msg - procReq matched");
#endif
							 iErr = 1;  goto  errLabel;
						 }
					 }
				 }
				 //  
				 if (pContentElem->uiType == CONST_imCommType_transferAvInfo) {								//  media
					 if (!pTaskInfo->var.m_bReplyTask) {
						 TASK_transferAv* task = (TASK_transferAv*)taskElem;
						 TRANSFER_AV_INFO* pTransferAvInfoElem = &pContentElem->transferAvInfo;
						 PROC_TASK_AV* pTaskElem = &task->myTask;//get_transferAvInfo_pTask(  pTransferAvInfoElem,  _T(  ""  )  );
						 if (!pTaskElem)  goto  errLabel;
						 int					index = 0;

						 if (pContent->uiType == CONST_imCommType_transferAvInfo) {								//  
							 TRANSFER_AV_INFO* pTransferAvInfo = &pContent->transferAvInfo;
							 //
							 if (pMsgElem->tStartTime == pMsgTask->tStartTime
								 && pMsgElem->uiTranNo == pMsgTask->uiTranNo)
							 {
								 BOOL  canGet = FALSE;
								 //
								 if (pTaskElem->ucbVideoConferenceStarter)  canGet = TRUE;
								 else  if (bApplyForAvProxy(pMisCntElem, pTransferAvInfoElem))  canGet = TRUE;
								 else {
#ifdef  __DEBUG__
									 //  traceLog((TCHAR*)  _T(  "findOrgMsg: 
									 //  让talk来校验
#endif
									 canGet = TRUE;
								 }
								 //
#ifdef  __DEBUG__
								 if (!canGet) {
									 traceLog((TCHAR*)_T("findOrgMsg: can't get req again, canGot is false"));
								 }
#endif
								 //
								 if (canGet) {
									 //  note: 2014/11/21. 这里不再直接覆盖输入内容了，而是要求一定要用param_findOrgMsg来输出. 不知道对原来的有没有影响 
									 //  memcpy(  &pContent->transferAvInfo.tranInfo,  &pTransferAvInfoElem->tranInfo,  sizeof(  pContent->transferAvInfo.tranInfo  )  );
									 //
#ifdef  __DEBUG__
									 if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
										 traceLogA((char*)"findOrgMsgAndProc_mis: get req again");
									 }
#endif																 
									 PARAM_findOrgMsg* pParam = (PARAM_findOrgMsg*)p1;
									 if (pParam) {
										 if (pParam->pMsgTask_o) {
											 int  len = offsetof(MIS_MSG_TASK, data) + pMsgElem->lenInBytes;

											 memcpy(pParam->pMsgTask_o, pMsgElem, len);
										 }
									 }
								 }

								 iErr = 1;  goto  errLabel;
							 }
							 //  2014/11/21
							 if (pMsgElem->iTaskId == pMsgTask->iTaskId) {
								 if (pTransferAvInfoElem->proxiedTranInfo.idInfo.ui64Id && pTransferAvInfoElem->proxiedTranInfo.uiObjType) {
									 if (pTransferAvInfoElem->proxiedTranInfo.idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id) {
										 if (pTransferAvInfoElem->proxiedTranInfo.ti.audio.uiTranNo_openAvDev || pTransferAvInfoElem->proxiedTranInfo.ti.video.uiTranNo_openAvDev) {
											 BOOL  bNotMatched = FALSE;
											 if (pTransferAvInfoElem->proxiedTranInfo.ti.audio.uiTranNo_openAvDev) {
												 if (pTransferAvInfoElem->proxiedTranInfo.ti.audio.uiTranNo_openAvDev != pTransferAvInfo->ass.tranInfo.audio.uiTranNo_openAvDev)  bNotMatched = TRUE;
											 }
											 if (pTransferAvInfoElem->proxiedTranInfo.ti.video.uiTranNo_openAvDev) {
												 if (pTransferAvInfoElem->proxiedTranInfo.ti.video.uiTranNo_openAvDev != pTransferAvInfo->ass.tranInfo.video.uiTranNo_openAvDev)  bNotMatched = TRUE;
											 }
											 if (!bNotMatched) {
#ifdef  __DEBUG__
												 traceLog((TCHAR*)_T("findOrgMsgAndProc_mis: get req content"));
#endif
												 PARAM_findOrgMsg* pParam = (PARAM_findOrgMsg*)p1;
												 if (pParam) {
													 if (pParam->pMsgTask_o) {
														 int  len = offsetof(MIS_MSG_TASK, data) + pMsgElem->lenInBytes;

														 memcpy(pParam->pMsgTask_o, pMsgElem, len);
													 }
												 }
												 iErr = 1;  goto  errLabel;
											 }
										 }
									 }
								 }
							 }
							 //  2014/11/21
							 if (bApplyForAvProxy(pMisCntElem, pTransferAvInfoElem)
								 && pTransferAvInfo->proxiedTranInfo.idInfo.ui64Id
								 && pTransferAvInfo->proxiedTranInfo.uiObjType)
							 {
								 if (pTransferAvInfo->proxiedTranInfo.idInfo.ui64Id == pMisCntElem->idInfo.ui64Id) {
									 if (pTransferAvInfo->proxiedTranInfo.ti.audio.uiTranNo_openAvDev || pTransferAvInfo->proxiedTranInfo.ti.video.uiTranNo_openAvDev) {
										 BOOL  bNotMatched = FALSE;
										 if (pTransferAvInfo->proxiedTranInfo.ti.audio.uiTranNo_openAvDev) {
											 if (pTransferAvInfo->proxiedTranInfo.ti.audio.uiTranNo_openAvDev != pTransferAvInfoElem->ass.tranInfo.audio.uiTranNo_openAvDev)  bNotMatched = TRUE;
										 }
										 if (pTransferAvInfo->proxiedTranInfo.ti.video.uiTranNo_openAvDev) {
											 if (pTransferAvInfo->proxiedTranInfo.ti.video.uiTranNo_openAvDev != pTransferAvInfoElem->ass.tranInfo.video.uiTranNo_openAvDev)  bNotMatched = TRUE;
										 }
										 if (!bNotMatched) {
#ifdef  __DEBUG__
											 traceLog((TCHAR*)_T("proxy reply returned"));
#endif
											 PARAM_findOrgMsg* pParam = (PARAM_findOrgMsg*)p1;
											 if (pParam) {
												 if (pParam->bNeedUpdate) {
													 pTaskElem->applyForProxy.bRecvd_proxyReply = TRUE;
													 //
													 pTaskElem->applyForProxy.proxyReply.proxy.uiTranNo_openAvDev_a = pTransferAvInfo->ass.tranInfo.audio.uiTranNo_openAvDev;
													 pTaskElem->applyForProxy.proxyReply.proxy.uiTranNo_openAvDev_v = pTransferAvInfo->ass.tranInfo.video.uiTranNo_openAvDev;
												 }
											 }
											 iErr = 1;  goto  errLabel;
										 }
									 }
								 }
							 }

						 }

						 if (pContent->uiType == CONST_imCommType_transferAvReplyInfo) {
							 MIS_CNT* pMisCnt = (MIS_CNT*)pMsgElem->pMisCnt;
							 if (!pMisCnt) {
								 showInfo_open0(0, 0, _T("findOrgMsg failed, pMsgElem->pMisCnt is null, content.uiType is avReply"));
								 goto  errLabel;
							 }
							 //
							 if (pMsgElem->tStartTime == pContent->transferAvReplyInfo.tStartTime_org
								 && pMsgElem->uiTranNo == pContent->transferAvReplyInfo.uiTranNo_org)
							 {
								 OutputDebugString(_T("tmpHandler_findOrgMsgAndProc_is . msg - reply is matched\n"));			//  

								 procTaskAvReply(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, &pTransferAvInfoElem->ass.tranInfo, pTaskElem, pMsgTask);

								 //
								 iErr = 1;  goto  errLabel;
							 }
							 //
							 if (pMsgElem->data.route.idInfo_from.ui64Id == pMisCnt->idInfo.ui64Id
								 && pMsgTask->data.route.idInfo_from.ui64Id == pMisCnt->idInfo.ui64Id
								 && pContentElem->transferAvInfo.uiTaskType == CONST_imTaskType_shareDynBmp
								 && pContentElem->transferAvInfo.ass.tranInfo.video.uiTranNo_openAvDev == pContent->transferAvReplyInfo.tranInfo.video.uiTranNo_openAvDev)
							 {
								 showInfo_open0(0, 0, _T("findOrgMsg: shareDynBmp task is matched with avReply"));
								 //
								 iErr = 1;  goto  errLabel;
							 }

						 }

						 //  											 
						 if (pContent->uiType == CONST_imCommType_transferVideoData) {							//  
							 //
							 tmpiRet = tmpHandler_findOrgMsgAndProcess_mis_procTaskVideoData(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgTask, &pContent->transferVideoData, pContentElem, pTaskElem);
							 if (tmpiRet) {
								 iErr = tmpiRet;  goto  errLabel;
							 }
						 }
						 if (pContent->uiType == CONST_imCommType_transferAudioData) {
							 //
							 tmpiRet = tmpHandler_findOrgMsgAndProcess_mis_procTaskAudioData(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgTask, &pContent->transferAudioData, pContentElem, pTaskElem);
							 if (tmpiRet) {
								 iErr = tmpiRet;  goto  errLabel;
							 }
						 }
						 if (pContent->uiType == CONST_imCommType_remoteAssistReq) {
							 if (pMsgElem->addr_logicalPeer.idInfo.ui64Id == pMsgTask->addr_logicalPeer.idInfo.ui64Id
								 && pTransferAvInfoElem->ass.tranInfo.video.uiTranNo_openAvDev == pContent->remoteAssistReq.uiTranNo_openAvDev)
							 {
#ifdef  __DEBUG__
								 traceLog((TCHAR*)_T("RemoteAssist: "));
#endif

								 if (procTaskRemoteAssist(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgTask, &pContent->remoteAssistReq, &pTransferAvInfoElem->ass.tranInfo, pTaskElem, index))  goto  errLabel;

								 iErr = 1;  goto  errLabel;
							 }
						 }

						 if (pContent->uiType == CONST_imCommType_taskProcReq) {	//  file·
							 if (pMsgElem->iTaskId && pMsgElem->iTaskId == pMsgTask->iTaskId) {
#ifdef  __DEBUG__
								 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is: msg - procReq.iTaskId [%d] is matched", pMsgTask->iTaskId);
#endif
								 //
								 iErr = 1;  goto  errLabel;
							 }

							 if (pMsgElem->tStartTime == pContent->taskProcReq.tStartTime_org
								 && pMsgElem->uiTranNo == pContent->taskProcReq.uiTranNo_org)
							 {
#ifdef  __DEBUG__
								 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is: msg - procReq is matched");
#endif
								 //
								 iErr = 1;  goto  errLabel;
							 }
						 }
					 }
					 else {
						 int ii = 0;

						 //  ÒÔÉÏÎªmedia·¢Æð¶Ë

					   //if  (  pContentElem->uiType  ==  CONST_imCommType_transferAvReplyInfo  )  
												  //  media»Ø¸´¶Ë

						 TASK_transferAv* task = (TASK_transferAv*)taskElem;

						 //TRANSFER_AV_replyInfo	*	pTransferAvReplyInfoElem	=	&pContentElem->transferAvReplyInfo;
						 TRANSFER_AV_INFO* pTransferAvInfoElem = &pContentElem->transferAvInfo;
						 PROC_TASK_AV* pTaskElem = &task->myTask;//get_transferAvReplyInfo_pTask(  pTransferAvReplyInfoElem,  _T(  ""  )  );
						 if (!pTaskElem)  goto  errLabel;
						 int						index = 0;

						 //  ÒòÎªaudio¶ÔÊµÊ±ÐÔÒªÇó×î¸ß£¬ËùÒÔ·ÅÔÚµÚÒ»Î»±È½Ï
						 if (pContent->uiType == CONST_imCommType_transferAudioData) {
							 //
							 tmpiRet = tmpHandler_findOrgMsgAndProcess_mis_procTaskAudioData(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgTask, &pContent->transferAudioData, pContentElem, pTaskElem);
							 if (tmpiRet) {
								 iErr = tmpiRet;  goto  errLabel;
							 }

						 }
						 if (pContent->uiType == CONST_imCommType_transferVideoData) {							//  ¶Ô·½µÄÊý¾Ý
							 //
							 tmpiRet = tmpHandler_findOrgMsgAndProcess_mis_procTaskVideoData(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgTask, &pContent->transferVideoData, pContentElem, pTaskElem);
							 if (tmpiRet) {
								 iErr = tmpiRet;  goto  errLabel;
							 }

						 }

						 if (pContent->uiType == CONST_imCommType_transferAvInfo) {		//  ÖØ·¢Ê±ÕâÀïÒªÐ£ÑéµÄ
							 if (pMsgElem->data.route.idInfo_from.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id
								 && pMsgElem->tStartTime == pMsgTask->tStartTime
								 && pMsgElem->uiTranNo == pMsgTask->uiTranNo)
							 {
								 //
#ifdef  __DEBUG__
								 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is: msg - req is matched");
#endif
								 //
								 if (pContent->confKey.usCnt) {

								 }
								 //
								 iErr = 1;  goto  errLabel;
							 }
						 }
						 if (pContent->uiType == CONST_imCommType_transferAvReplyInfo) {							//  ´¦Àí
							 if (
								 //pContentElem->transferAvReplyInfo.tStartTime_org  ==  pContent->transferAvReplyInfo.tStartTime_org
								 //&&  pContentElem->transferAvReplyInfo.uiTranNo_org  ==  pContent->transferAvReplyInfo.uiTranNo_org  
								 pMsgElem->tStartTime == pContent->transferAvReplyInfo.tStartTime_org
								 && pMsgElem->uiTranNo == pContent->transferAvReplyInfo.uiTranNo_org
								 )
							 {
								 //
#ifdef  __DEBUG__
								 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is . msg - procReq matched.");
#endif
								 //
								 iErr = 1;  goto  errLabel;
							 }
						 }
						 if (pContent->uiType == CONST_imCommType_taskProcReq) {	//  
							 if (pContentElem->transferAvReplyInfo.tStartTime_org == pContent->taskProcReq.tStartTime_org
								 && pContentElem->transferAvReplyInfo.uiTranNo_org == pContent->taskProcReq.uiTranNo_org)
							 {
								 //
#ifdef  __DEBUG__
								 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is: msg - procReq is matched");
#endif
								 //
								 iErr = 1;  goto  errLabel;
							 }
						 }

					 }  //  ÒÔÉÏÎªmedia»Ø¸´¶Ë¡£

				 }

				 //  2012/04/19
				 if (pContentElem->uiType == CONST_imCommType_transferGpsInfo) {								//  media·¢Æð¶Ë
					 TRANSFER_GPS_INFO* pTransferGpsInfoElem = &pContentElem->transferGpsInfo;
					 int					index = 0;

					 if (pContent->uiType == CONST_imCommType_transferGpsInfo) {								//  ¶ÔÓÚÆ´½ÓÍ¼ÏóÀ´Ëµ£¬ÓÃÍ¬ÑùµÄtStartTimeºÍuiTranNo¿ÉÒÔ°ÑÆ´½ÓrgbºÍÑ¹Ëõ¸ñÊ½¿¼Èë
						 if (pMsgElem->tStartTime == pMsgTask->tStartTime
							 && pMsgElem->uiTranNo == pMsgTask->uiTranNo)
						 {
							 iErr = 1;  goto  errLabel;
						 }
					 }

					 //											 			
					 if (pContent->uiType == CONST_imCommType_transferGpsReplyInfo) {
						 if (pMsgElem->tStartTime == pContent->transferGpsReplyInfo.tStartTime_org
							 && pMsgElem->uiTranNo == pContent->transferGpsReplyInfo.uiTranNo_org)
						 {
							 OutputDebugString(_T("tmpHandler_findOrgMsgAndProc_is . msg - gpsReply is matched\n"));			//  »Ø¸´´¦ÀíÊ±

							 //
							 iErr = 1;  goto  errLabel;
						 }
					 }

					 //
					 if (pContent->uiType == CONST_imCommType_transferGpsData) {		//  2012/04/20
						 if (pMsgElem->addr_logicalPeer.idInfo.ui64Id == pMsgTask->addr_logicalPeer.idInfo.ui64Id) {
							 //
#if  0
							 OutputDebugString(_T("tmpHandler_findOrgMsg, gpsData matched\n"));
#endif

							 //  2012/05/07
							 tmpiRet = tmpHandler_findOrgMsgAndProcess_mis_procTaskGpsData(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgTask, &pContent->transferGpsData, NULL, &pTransferGpsInfoElem->myTask);

							 //
							 iErr = 1;  goto  errLabel;
						 }
					 }

					 //
				 }

			 }
			 //
		 }
									break;
		 case  CONST_misMsgType_input: {
			 MIS_MSG_INPUT* pMsgInput = &pMsg_toBeSearched->input;
			 IM_CONTENTU* pContent = M_getMsgContent(pMsgInput->ucFlg, &pMsgInput->data);
			 //
			 if (pMsgInput->pMisCnt != pMisCntElem)  break;

			 //									 
#ifdef  __DEBUG__	//  2014/08/28
			 if (pContent->uiType == CONST_imCommType_taskProcReq) {
				 switch (pContent->taskProcReq.usOp) {
				 case  CONST_imOp_recv_applyForKeyFrame: {
					 int  i;
					 i = 9;
				 }
													   break;
				 case  CONST_imOp_recv_cancel: {
					 int  ii;
					 ii = 9;
				 }
											 break;
				 default:
					 break;
				 }

			 }
#endif

			 //
			 if (isUcFlgResp(pMsgInput->ucFlg) && !isUcFlgResp(pMsgElem->ucFlg)) {	//  ½ÓÊÕÎÄ¼þµÄ´¦Àí
				 switch (pContentElem->uiType) {
				 case  CONST_imCommType_transferAvInfo: {
					 TRANSFER_AV_INFO* pTransferAvInfoElem = &pContentElem->transferAvInfo;
					 TASK_transferAv* task = (TASK_transferAv*)taskElem;
					 PROC_TASK_AV* pTaskElem = &task->myTask;//get_transferAvInfo_pTask(  pTransferAvInfoElem,  _T(  ""  )  );
					 if (!pTaskElem)  goto  errLabel;
					 //
					 if (pContent->uiType == CONST_imCommType_transferVideoDataResp) {
#if  0
						 if (pMsgElem->data.route.idInfo_from.ui64Id == pMsgInput->data.route.idInfo_to.ui64Id
							 && pTransferAvInfoElem->tranInfo.video.uiTranNo_openAvDev == pContent->transferVideoDataResp.uiTranNo_openAvDev)
						 {
							 //  OutputDebugString(  _T(  "VideoData Resp, ½«µ÷ÕûÊÓÆµ·¢ËÍÆµÂÊ\n"  )  );

							 if (procTaskVideoDataResp(pProcInfo, pMsgInput, &pContent->transferVideoDataResp, &pTransferAvInfoElem->tranInfo, pTaskElem))  goto  errLabel;

							 iErr = 1;  goto  errLabel;
						 }
#endif
						 tmpiRet = tmpHandler_find_procTaskVideoDataResp(pProcInfo, pMsgElem, pMsgInput, &pContent->transferVideoDataResp, &task->myTask);
						 if (tmpiRet) {
							 iErr = tmpiRet;  goto  errLabel;
						 }
					 }
					 if (pContent->uiType == CONST_imCommType_transferAudioDataResp) {
						 if (pMsgElem->data.route.idInfo_from.ui64Id == pMsgInput->data.route.idInfo_to.ui64Id
							 && pTransferAvInfoElem->ass.tranInfo.audio.uiTranNo_openAvDev == pContent->transferAudioDataResp.uiTranNo_openAvDev)
						 {
							 //  OutputDebugString(  _T(  "AudioData Resp, ½«µ÷ÕûÒôÆµ·¢ËÍÆµÂÊ\n"  )  );

							 if (procTaskAudioDataResp(pProcInfo, &pTransferAvInfoElem->ass.tranInfo, pTaskElem, pMsgInput, &pContent->transferAudioDataResp))  goto  errLabel;

							 iErr = 1;  goto  errLabel;
						 }
					 }
					 //
				 }
													  break;
				 case  CONST_imCommType_transferAvReplyInfo: {
					 TRANSFER_AV_replyInfo* pTransferAvProcInfoElem = &pContentElem->transferAvReplyInfo;
					 TASK_transferAv* task = (TASK_transferAv*)taskElem;
					 PROC_TASK_AV* pTaskElem = &task->myTask;//get_transferAvReplyInfo_pTask(  pTransferAvProcInfoElem,  _T(  ""  )  );
					 if (!pTaskElem)  goto  errLabel;
					 //
					 if (pContent->uiType == CONST_imCommType_transferVideoDataResp) {
#if  0
						 if (pMsgElem->data.route.idInfo_to.ui64Id == pMsgInput->data.route.idInfo_from.ui64Id
							 && pTransferAvProcInfoElem->tranInfo.video.uiTranNo_openAvDev == pContent->transferVideoDataResp.uiTranNo_openAvDev)
						 {
							 //  OutputDebugString(  _T(  "VideoData Resp, ½«µ÷ÕûÊÓÆµ·¢ËÍÆµÂÊ\n"  )  );

							 if (procTaskVideoDataResp(pProcInfo, pMsgInput, &pContent->transferVideoDataResp, &pTransferAvProcInfoElem->tranInfo, pTaskElem))  goto  errLabel;

							 iErr = 1;  goto  errLabel;
						 }
#endif
						 tmpiRet = tmpHandler_find_procTaskVideoDataResp(pProcInfo, pMsgElem, pMsgInput, &pContent->transferVideoDataResp, &task->myTask);
						 if (tmpiRet) {
							 iErr = tmpiRet;  goto  errLabel;
						 }
					 }
					 if (pContent->uiType == CONST_imCommType_transferAudioDataResp) {
						 if (pMsgElem->data.route.idInfo_to.ui64Id == pMsgInput->data.route.idInfo_from.ui64Id
							 && pTransferAvProcInfoElem->tranInfo.audio.uiTranNo_openAvDev == pContent->transferAudioDataResp.uiTranNo_openAvDev)
						 {
							 //  OutputDebugString(  _T(  "AudioDataResp, ½«µ÷ÕûÒôÆµ·¢ËÍÆµÂÊ\n"  )  );

							 if (procTaskAudioDataResp(pProcInfo, &pTransferAvProcInfoElem->tranInfo, pTaskElem, pMsgInput, &pContent->transferAudioDataResp))  goto  errLabel;

							 iErr = 1;  goto  errLabel;
						 }
					 }
					 //
				 }
														   break;
				 case  CONST_imCommType_transferGpsInfo: {
					 TRANSFER_GPS_INFO* pTransferGpsInfoElem = &pContentElem->transferGpsInfo;
					 if (pContent->uiType == CONST_imCommType_transferGpsDataResp) {
						 if (pMsgElem->data.route.idInfo_from.ui64Id == pMsgInput->data.route.idInfo_to.ui64Id) {
							 //
#ifdef  __DEBUG__
							 traceLog((TCHAR*)_T("findOrgMsgAndprocess: gpsDataResp"));
#endif
							 if (procTaskGpsDataResp(pProcInfo, NULL, &pTransferGpsInfoElem->myTask, pMsgInput, &pContent->transferGpsDataResp))  goto  errLabel;
							 //
							 iErr = 1;  goto  errLabel;
						 }
					 }
				 }
													   break;
				 case  CONST_imCommType_transferFileReq: {
					 TASK_transferFile* task = (TASK_transferFile*)taskElem;
					 if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_transferFile)  goto  errLabel;
					 QMC_taskData_transferFile* pTt = (QMC_taskData_transferFile*)pTaskInfo->var.pTaskData;



					 if ((pMsgInput->tStartTime == task->myTask.reply_info.tStartTime_reply
						 && pMsgInput->uiTranNo == task->myTask.reply_info.uiTranNo_reply)
						 || (pMsgInput->tStartTime == task->myTask.reply_info.tStartTime_lastFileDataReq
							 && pMsgInput->uiTranNo == task->myTask.reply_info.uiTranNo_lastFileDataReq)
						 )
					 {
						 traceLogA((char*)"");



						 if (p1
							 //&&  pContentElem->uiType  ==  CONST_imCommType_transferFileReplyReq
							 && pContent->uiType == CONST_imCommType_simpleResp
							 && pContent->simpleResp.uiContentType_org == task->myTask.reply_info.replyReq.uiType)
						 {
							 TRANSFER_FILE_REPLYREQ* pFileReplyReq = &task->myTask.reply_info.replyReq;//pContentElem->transferFileReplyReq;
							 TRANSFER_FILEDATA_REQ* pFileDataReq_o = (TRANSFER_FILEDATA_REQ*)p1;

							 if (!pFileDataReq_o || !task->myTask.ui64FileLen || !task->myTask.uiSizePerSnd_internal) {
#ifdef  __DEBUG__
								 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is failed: mmyÐ£ÑéÌõ¼þ²»Âú×ã1");
#endif
								 goto  errLabel;
							 }

							 //  ÏÈ½«uiSizePerSndºÍÇëÇó±êÊ¶¸ø¸³ÉÏdataReq
							 pFileDataReq_o->uiSizePerSnd = task->myTask.uiSizePerSnd_internal;
							 pFileDataReq_o->tStartTime_org = pFileReplyReq->tStartTime_org;
							 pFileDataReq_o->uiTranNo_org = pFileReplyReq->uiTranNo_org;
							 pFileDataReq_o->uiSerialNo_org = pFileReplyReq->uiSerialNo_org;
							 //
							 pFileDataReq_o->uiDataBlockIndex = 0;	//  Õâ±íÃ÷ÊÇ´ÓÍ·¿ªÊ¼

							 int uiBlocks = (task->myTask.ui64FileLen - 1) / task->myTask.uiSizePerSnd_internal + 1;
							 pFileDataReq_o->us_nBlocks = min(task->myTask.MAX_FILE_SEND_BLOCK_internal, uiBlocks);
							 task->myTask.reqBlock = pFileDataReq_o->us_nBlocks;
							 //
							 task->myTask.reply_info.tStartTime_lastFileDataReq = pFileDataReq_o->tmpInternal.tStartTime_new;
							 task->myTask.reply_info.uiTranNo_lastFileDataReq = pFileDataReq_o->tmpInternal.uiTranNo_new;

							 //								 
							 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""),
								 _T(""), _T("findOrgMsg: start to retrieve file. total %I64u bytes. perSnd %d"),
								 task->myTask.ui64FileLen, pFileDataReq_o->uiSizePerSnd);

							 //
							 iErr = 1;  goto  errLabel;

						 }
						 if (p1
							 //&&  pContentElem->uiType  ==  CONST_imCommType_transferFileReplyReq  
							 && pContent->uiType == CONST_imCommType_transferFileDataResp)
						 {
							 //
							 TRANSFER_FILE_REPLYREQ* pFileReplyReq = &task->myTask.reply_info.replyReq;//pContentElem->transferFileReplyReq;
							 TRANSFER_FILEDATA_RESP* pFileDataResp = &pContent->transferFileDataResp;
							 IM_CONTENTU* pContent_o = (IM_CONTENTU*)p1;
							 DWORD64							ui64offset = 0;
							 int								nWrite = 0;


							 if (!pContent_o || !task->myTask.ui64FileLen || !task->myTask.uiSizePerSnd_internal || sizeof(pFileDataResp->buf) < task->myTask.uiSizePerSnd_internal) {
#ifdef  __DEBUG__
								 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is failed: ");
#endif
								 goto  errLabel;
							 }

							 if (pContent_o->uiType == CONST_imCommType_transferFileEndReq) {
								 TRANSFER_FILEEND_REQ* pFileEndReq_o = &pContent_o->transferFileEndReq;

								 //  2015/09/08
								 if (pFileEndReq_o->tmpInternal.bChkToRemove_i) {
									 //pFileReplyReq->myTask.bNeedRemoved  =  TRUE;
									 pTaskInfo->var.bNeedRemoved = TRUE;
									 //  2015/09/08
									 pFileEndReq_o->tmpInternal.bNeedRemoved_o = TRUE;
								 }

								 //  
								 pFileEndReq_o->tStartTime_org = pFileReplyReq->tStartTime_org;
								 pFileEndReq_o->uiTranNo_org = pFileReplyReq->uiTranNo_org;
								 pFileEndReq_o->uiSerialNo_org = pFileReplyReq->uiSerialNo_org;

								 iErr = 1;  goto  errLabel;
							 }

							 if (pContent_o->uiType == CONST_imCommType_transferFileDataReq) {

								 TRANSFER_FILEDATA_REQ* pFileDataReq_o = &pContent_o->transferFileDataReq;

								 //  ÏÈ½«uiSizePerSndºÍÇëÇó±êÊ¶¸ø¸³ÉÏdataReq
								 pFileDataReq_o->uiSizePerSnd = task->myTask.uiSizePerSnd_internal;
								 pFileDataReq_o->tStartTime_org = pFileReplyReq->tStartTime_org;
								 pFileDataReq_o->uiTranNo_org = pFileReplyReq->uiTranNo_org;
								 pFileDataReq_o->uiSerialNo_org = pFileReplyReq->uiSerialNo_org;

#if  0
								 if (pFileDataResp->uiDataBlockIndex > pFileReplyReq->uiLastDataBlockIndex + 1) {
									 pFileReplyReq->usErrors++;	//  ÕâÀïÊÇÓÃÔÚ¶ÔÓÚÀûÓÃÐ­Òé½øÐÐ¹¥»÷Ê±£¬ÅÐ¶Ï´íÎóµ½Ò»¶¨³Ì¶È£¬¼´ÖÕÖ¹´«Êä
									 //  ÖØÐÂ½«uiLastDataBlockIndex¸³¸øreq, ·¢¸ø¿Í»§¶Ë
									 pFileDataReq_o->uiDataBlockIndex = pFileReplyReq->uiLastDataBlockIndex;
									 iErr = 1;  goto  errLabel;

								 }
#endif	//  2009/10/20

								 //
								 if (pProcInfo->cfg.debugStatusInfo.ucbViewFileStatus) {
									 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("get pFileDataResp->uiDataBlockIndex %d, %d bytes. tn %d"), pFileDataResp->uiDataBlockIndex, pFileDataResp->uiLen, pMsgInput->uiTranNo);
								 }


								 //
								 {	 //  2009/10/20. check whether resp is ok												 
									 BOOL	bRespOk = TRUE;
									 if (!pFileDataResp->uiDataBlockIndex) {
										 if (task->myTask.uiLastDataBlockIndex)  bRespOk = FALSE;
									 }
									 else {
										 if (pFileDataResp->uiDataBlockIndex != task->myTask.uiLastDataBlockIndex + 1)  bRespOk = FALSE;
									 }
									 if (!bRespOk) {
										 //
#ifdef  __DEBUG__
										 traceLogA((char*)"pFileDataResp->uiDataBlockIndex err");
#endif
										 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""),
											 _T("Err: pFileDataResp->uiDataBlockIndex %d, fileReplyReq.uiLastDataBlockIndex %d"),
											 pFileDataResp->uiDataBlockIndex, task->myTask.uiLastDataBlockIndex);
										 //															 
										 task->myTask.usErrors++;
										 //
										 goto  errLabel;
									 }
								 }


								 ui64offset = ((DWORD64)pFileDataResp->uiDataBlockIndex) * task->myTask.uiSizePerSnd_internal;
								 if (ui64offset >= task->myTask.ui64FileLen) {
									 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""),
										 _T(""), _T("ui64offset >= pFileReplyReq->ui64FileLen err"));
									 goto  errLabel;
								 }

								 //  ÕâÀïÎª½«µÃµ½µÄÊý¾Ý±£´æ³ÉÎÄ¼þ
								 if (!task->myTask.fp) {
									 TCHAR	tmpFilePath[MAX_PATH + 1] = _T("");
									 //
									 _sntprintf(tmpFilePath, mycountof(tmpFilePath), _T("%s.tmp"), task->myTask.fullFilePath_save);
									 //
									 task->myTask.fp = _tfopen(tmpFilePath, _T("wb"));
									 if (!task->myTask.fp) {
#ifdef  __DEBUG__
										 traceLogA((char*)"ÎÄ¼þ½¨Á¢Ê§°Ü");
#endif
										 //
										 TCHAR  tBuf[128];
										 _sntprintf(tBuf, mycountof(tBuf), _T("fileDataResp: fopen %s failed"), tmpFilePath);
										 showInfo_open0(0, 0, tBuf);
										 showNotification(0, 0, 0, 0, 0, 0, tBuf);
										 //
										 goto  errLabel;
									 }
									 //
									 pTt->dwStartTickCnt = GetTickCount();
									 pTt->dwLastReportTickCnt = pTt->dwStartTickCnt;
									 task->myTask.ucPercent = 0;
									 //
									 //  
									 //
									 showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, FALSE, CONST_imCommType_transferFileReq, pMsgElem->iTaskId, CONST_imTaskStatus_receiving, 0, 0, NULL, NULL);

								 }

								 //  
								 //  if  (  fseek(  pFileReplyReq->fp,  (  long  )ui64offset,  SEEK_SET  )  )  
								 if (my_fseeki64(task->myTask.fp, ui64offset, SEEK_SET))
								 {
									 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is failed:  _fseeki64 err");
									 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("_fseeki64 err"));
									 goto  errLabel;
								 }

								 nWrite = (int)min(task->myTask.ui64FileLen - ui64offset, task->myTask.uiSizePerSnd_internal);
								 if (pFileDataResp->uiLen != nWrite) {
									 traceLogA((char*)"pFileDataResp->uiLen  !=  nWrite");
									 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("pFileDataResp->uiLen!=nWrite err,%d,%I64u,%I64u,%d,%d"), nWrite, task->myTask.ui64FileLen, ui64offset, task->myTask.uiSizePerSnd_internal, pFileDataResp->uiLen);
									 goto  errLabel;
								 }

								 if (1 != fwrite(pFileDataResp->buf, pFileDataResp->uiLen, 1, task->myTask.fp)) {
									 traceLogA((char*)"fwite failed");
									 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("fwite err"));
									 goto  errLabel;
								 }



								 //
								 task->myTask.uiLastDataBlockIndex = pFileDataResp->uiDataBlockIndex;


								 //  
								 DWORD	dwCurTickCnt;
								 //
								 dwCurTickCnt = GetTickCount();
								 if (dwCurTickCnt > pTt->dwLastReportTickCnt + 1000) {	//  
									 pTt->dwLastReportTickCnt = dwCurTickCnt;
									 //
									 float	f = 0;
									 unsigned  char  ucPercent;
									 //
									 f = (float)task->myTask.uiLastDataBlockIndex * task->myTask.uiSizePerSnd_internal;
									 f = f / task->myTask.ui64FileLen;
									 ucPercent = (unsigned  char)(f * 100);

									 //  if  (  ucPercent  !=  pFileReplyReq->ucPercent  )  
									 {	//  ±¨¸æ×´Ì¬
#ifdef  __DEBUG__
										 traceLog((TCHAR*)_T("ucPercent %d"), (int)ucPercent);
#endif

										 showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, FALSE, CONST_imCommType_transferFileReq, pMsgElem->iTaskId, CONST_imTaskStatus_receiving, ucPercent, task->myTask.uiLastDataBlockIndex * task->myTask.uiSizePerSnd_internal, NULL, NULL);

									 }
								 }


								 pFileDataReq_o->uiDataBlockIndex = task->myTask.uiLastDataBlockIndex + 1;

								 unsigned long long last = (unsigned long long)pFileDataReq_o->uiDataBlockIndex * task->myTask.uiSizePerSnd_internal;


								 if (last >= task->myTask.ui64FileLen) {
									 //  Òª°ÑÁÙÊ±ÎÄ¼þÒÆ³ÉÕýÊ½ÎÄ¼þ
									 TCHAR		tmpFilePath[MAX_PATH + 1] = _T("");


									 //
									 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("all file data received. %I64u bytes. to copyfile"), task->myTask.ui64FileLen);
									 //
									 if (task->myTask.fp) {
#ifdef  __DEBUG__
										 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is: before fclose");
#endif
										 fclose(task->myTask.fp);  task->myTask.fp = NULL;
#ifdef  __DEBUG__
										 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is: after fclose");
#endif
									 }
									 //
									 _sntprintf(tmpFilePath, mycountof(tmpFilePath), _T("%s.tmp"), task->myTask.fullFilePath_save);
									 //
									 if (!CopyFile(tmpFilePath, task->myTask.fullFilePath_save, FALSE)) {
										 TCHAR  tBuf[256] = _T("");
#ifdef  __DEBUG__
										 traceLog((TCHAR*)_T("CopyFile %s->%s failed"), tmpFilePath, task->myTask.fullFilePath_save);
#endif
										 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("copyfile failed. %s->%s"), tmpFilePath, task->myTask.fullFilePath_save);
										 _sntprintf(tBuf, mycountof(tBuf), _T("Copy failed. %s"), task->myTask.fileName_transferred);
										 showNotification(0, 0, 0, 0, 0, 0, tBuf);
										 goto errLabel;
									 }


									 DeleteFile(tmpFilePath);

									 {
										 void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
										 CQnmDb  db;
										 if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
										 pDb = db.m_pDbMem->pDb;
#endif 

										 if (g_dbFuncs.pf_updateTaskStatus(pDb, CONST_imTaskStatus_recvFinished, pMsgElem->iTaskId))  goto  errLabel;
									 }

									 showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, FALSE, CONST_imCommType_transferFileReq, pMsgElem->iTaskId, CONST_imTaskStatus_recvFinished, 100, task->myTask.ui64FileLen, task->myTask.fileName_transferred, task->myTask.fullFilePath_save);

									 //

									 pFileDataReq_o->tmpInternal.ucbFileEnd = TRUE;
									 traceLogA((char*)"bFileEnd is true");

									 //
									 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Transfering file ends."));

								 }

								 //
								 if (!pFileDataReq_o->tmpInternal.ucbFileEnd) {


#ifdef ORG_FILE_SEND_LOGIC
									 task->myTask.reqBlock--;

									 if (task->myTask.reqBlock <= 0) {


										 unsigned long long uiFileLen = (unsigned long long)task->myTask.ui64FileLen;
										 unsigned  int uiBlocks = (uiFileLen - last - 1) / task->myTask.uiSizePerSnd_internal + 1;


										 pFileDataReq_o->us_nBlocks = min(task->myTask.MAX_FILE_SEND_BLOCK_internal, uiBlocks);
										 task->myTask.reqBlock = pFileDataReq_o->us_nBlocks;

										 task->myTask.reply_info.tStartTime_lastFileDataReq = pFileDataReq_o->tmpInternal.tStartTime_new;
										 task->myTask.reply_info.uiTranNo_lastFileDataReq = pFileDataReq_o->tmpInternal.uiTranNo_new;
									 }

#endif
								 }

								 //
								 iErr = 1;  goto  errLabel;
							 }

							 traceLogA((char*)"");

						 }

						 iErr = 1;  goto  errLabel;
					 }
					 //
				 }
													   break;
				 default:
					 break;
				 }

				 if (pMsgInput->tStartTime == pMsgElem->tStartTime
					 && pMsgInput->uiTranNo == pMsgElem->uiTranNo)
				 {
					 traceLogA((char*)"");

					 if (p1
						 && pContentElem->uiType == CONST_imCommType_transferFileReq // CONST_imCommType_transferFileReplyReq
						 && pTaskInfo->var.m_bReplyTask
						 && pContent->uiType == CONST_imCommType_simpleResp
						 && pContent->simpleResp.uiContentType_org == CONST_imCommType_transferFileReplyReq // pContentElem->uiType  
						 )
					 {
						 TASK_transferFile* task = (TASK_transferFile*)taskElem;
						 //
						 TRANSFER_FILE_REPLYREQ* pFileReplyReq = &task->myTask.reply_info.replyReq;//  transferFileReplyReq;
						 TRANSFER_FILEDATA_REQ* pFileDataReq_o = (TRANSFER_FILEDATA_REQ*)p1;

						 if (!pFileDataReq_o || !task->myTask.ui64FileLen || !task->myTask.uiSizePerSnd_internal) {
#ifdef  __DEBUG__
							 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is failed: iiiÐ£ÑéÌõ¼þ²»Âú×ã1");
#endif
							 goto  errLabel;
						 }

						 //  ÏÈ½«uiSizePerSndºÍÇëÇó±êÊ¶¸ø¸³ÉÏdataReq
						 pFileDataReq_o->uiSizePerSnd = task->myTask.uiSizePerSnd_internal;
						 pFileDataReq_o->tStartTime_org = pFileReplyReq->tStartTime_org;
						 pFileDataReq_o->uiTranNo_org = pFileReplyReq->uiTranNo_org;
						 pFileDataReq_o->uiSerialNo_org = pFileReplyReq->uiSerialNo_org;
						 //
						 pFileDataReq_o->uiDataBlockIndex = 0;	//  Õâ±íÃ÷ÊÇ´ÓÍ·¿ªÊ¼

						 iErr = 1;  goto  errLabel;

					 }

					 if (p1
						 && pContentElem->uiType == CONST_imCommType_transferFileReplyReq
						 && pContent->uiType == CONST_imCommType_transferFileDataResp)
					 {
						 TASK_transferFile* task = (TASK_transferFile*)taskElem;
						 QMC_taskData_transferFile* pTt = (QMC_taskData_transferFile*)pTaskInfo->var.pTaskData;
						 //
						 TRANSFER_FILE_REPLYREQ* pFileReplyReq = &pContentElem->transferFileReplyReq;
						 TRANSFER_FILEDATA_RESP* pFileDataResp = &pContent->transferFileDataResp;
						 IM_CONTENTU* pContent_o = (IM_CONTENTU*)p1;
						 DWORD64							ui64offset = 0;
						 int								nWrite = 0;

						 if (!pContent_o || !task->myTask.ui64FileLen || !task->myTask.uiSizePerSnd_internal || sizeof(pFileDataResp->buf) < task->myTask.uiSizePerSnd_internal) {
#ifdef  __DEBUG__
							 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is failed: ");
#endif
							 goto  errLabel;
						 }

						 if (pContent_o->uiType == CONST_imCommType_transferFileEndReq) {
							 TRANSFER_FILEEND_REQ* pFileEndReq_o = &pContent_o->transferFileEndReq;

							 //  2015/09/08
							 if (pFileEndReq_o->tmpInternal.bChkToRemove_i) {
								 //pFileReplyReq->myTask.bNeedRemoved  =  TRUE;
								 pTaskInfo->var.bNeedRemoved = TRUE;
								 //  2015/09/08
								 pFileEndReq_o->tmpInternal.bNeedRemoved_o = TRUE;
							 }

							 //  
							 pFileEndReq_o->tStartTime_org = pFileReplyReq->tStartTime_org;
							 pFileEndReq_o->uiTranNo_org = pFileReplyReq->uiTranNo_org;
							 pFileEndReq_o->uiSerialNo_org = pFileReplyReq->uiSerialNo_org;

							 iErr = 1;  goto  errLabel;
						 }

						 if (pContent_o->uiType == CONST_imCommType_transferFileDataReq) {

							 TRANSFER_FILEDATA_REQ* pFileDataReq_o = &pContent_o->transferFileDataReq;

							 //  ÏÈ½«uiSizePerSndºÍÇëÇó±êÊ¶¸ø¸³ÉÏdataReq
							 pFileDataReq_o->uiSizePerSnd = task->myTask.uiSizePerSnd_internal;
							 pFileDataReq_o->tStartTime_org = pFileReplyReq->tStartTime_org;
							 pFileDataReq_o->uiTranNo_org = pFileReplyReq->uiTranNo_org;
							 pFileDataReq_o->uiSerialNo_org = pFileReplyReq->uiSerialNo_org;

#if  0
							 if (pFileDataResp->uiDataBlockIndex > pFileReplyReq->uiLastDataBlockIndex + 1) {
								 pFileReplyReq->usErrors++;	//  ÕâÀïÊÇÓÃÔÚ¶ÔÓÚÀûÓÃÐ­Òé½øÐÐ¹¥»÷Ê±£¬ÅÐ¶Ï´íÎóµ½Ò»¶¨³Ì¶È£¬¼´ÖÕÖ¹´«Êä
								 //  ÖØÐÂ½«uiLastDataBlockIndex¸³¸øreq, ·¢¸ø¿Í»§¶Ë
								 pFileDataReq_o->uiDataBlockIndex = pFileReplyReq->uiLastDataBlockIndex;
								 iErr = 1;  goto  errLabel;

							 }
#endif	//  2009/10/20

							 //
#ifdef  __DEBUG__
		//qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "pFileDataResp->uiDataBlockIndex %d"  ),  pFileDataResp->uiDataBlockIndex  );															 
#endif


//
							 {	 //  2009/10/20. check whether resp is ok												 
								 BOOL	bRespOk = TRUE;
								 if (!pFileDataResp->uiDataBlockIndex) {
									 if (task->myTask.uiLastDataBlockIndex)  bRespOk = FALSE;
								 }
								 else {
									 if (pFileDataResp->uiDataBlockIndex != task->myTask.uiLastDataBlockIndex + 1)  bRespOk = FALSE;
								 }
								 if (!bRespOk) {
									 //
#ifdef  __DEBUG__
									 traceLogA((char*)"pFileDataResp->uiDataBlockIndex err");
#endif
									 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""),
										 _T("Err: pFileDataResp->uiDataBlockIndex %d, fileReplyReq.uiLastDataBlockIndex %d"),
										 pFileDataResp->uiDataBlockIndex, task->myTask.uiLastDataBlockIndex);
									 //															 
									 task->myTask.usErrors++;
									 //
									 goto  errLabel;
								 }
							 }


							 ui64offset = ((DWORD64)pFileDataResp->uiDataBlockIndex) * task->myTask.uiSizePerSnd_internal;
							 if (ui64offset >= task->myTask.ui64FileLen) {
								 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("ui64offset >= pFileReplyReq->ui64FileLen err"));
								 goto  errLabel;
							 }

							 //  ÕâÀïÎª½«µÃµ½µÄÊý¾Ý±£´æ³ÉÎÄ¼þ
							 if (!task->myTask.fp) {
								 TCHAR	tmpFilePath[MAX_PATH + 1] = _T("");
								 //
								 _sntprintf(tmpFilePath, mycountof(tmpFilePath), _T("%s.tmp"), task->myTask.fullFilePath_save);
								 //
								 task->myTask.fp = _tfopen(tmpFilePath, _T("wb"));
								 if (!task->myTask.fp) {
#ifdef  __DEBUG__
									 traceLogA((char*)"ÎÄ¼þ½¨Á¢Ê§°Ü");
#endif
									 goto  errLabel;
								 }
								 //
								 pTt->dwStartTickCnt = GetTickCount();
								 pTt->dwLastReportTickCnt = pTt->dwStartTickCnt;
								 task->myTask.ucPercent = 0;
								 //
								 //  
								 //
								 showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, FALSE, CONST_imCommType_transferFileReq, pMsgElem->iTaskId, CONST_imTaskStatus_receiving, 0, 0, NULL, NULL);

							 }

							 //  
							 //  if  (  fseek(  pFileReplyReq->fp,  (  long  )ui64offset,  SEEK_SET  )  )  
							 if (my_fseeki64(task->myTask.fp, ui64offset, SEEK_SET))
							 {
								 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is failed:  _fseeki64 err");
								 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("_fseeki64 err"));
								 goto  errLabel;
							 }

							 nWrite = (int)min(task->myTask.ui64FileLen - ui64offset, task->myTask.uiSizePerSnd_internal);
							 if (pFileDataResp->uiLen != nWrite) {
								 traceLogA((char*)"pFileDataResp->uiLen  !=  nWrite");
								 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("pFileDataResp->uiLen!=nWrite err,%d,%I64u,%I64u,%d,%d"), nWrite, task->myTask.ui64FileLen, ui64offset, task->myTask.uiSizePerSnd_internal, pFileDataResp->uiLen);
								 goto  errLabel;
							 }

							 if (1 != fwrite(pFileDataResp->buf, pFileDataResp->uiLen, 1, task->myTask.fp)) {
								 traceLogA((char*)"fwite failed");
								 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("fwite err"));
								 goto  errLabel;
							 }

							 //
							 task->myTask.uiLastDataBlockIndex = pFileDataResp->uiDataBlockIndex;


							 //  
							 DWORD	dwCurTickCnt;
							 //
							 dwCurTickCnt = GetTickCount();
							 if (dwCurTickCnt > pTt->dwLastReportTickCnt + 3000) {	//  
								 pTt->dwLastReportTickCnt = dwCurTickCnt;
								 //
								 float	f = 0;
								 unsigned  char  ucPercent;
								 //
								 f = (float)task->myTask.uiLastDataBlockIndex * task->myTask.uiSizePerSnd_internal;
								 f = f / task->myTask.ui64FileLen;
								 ucPercent = (unsigned  char)(f * 100);

								 //  if  (  ucPercent  !=  pFileReplyReq->ucPercent  )  
								 {	//  ±¨¸æ×´Ì¬

									 showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, FALSE, CONST_imCommType_transferFileReq, pMsgElem->iTaskId, CONST_imTaskStatus_receiving, ucPercent, task->myTask.uiLastDataBlockIndex * task->myTask.uiSizePerSnd_internal, NULL, NULL);

								 }
							 }


							 pFileDataReq_o->uiDataBlockIndex = task->myTask.uiLastDataBlockIndex + 1;


							 if (pFileDataReq_o->uiDataBlockIndex * task->myTask.uiSizePerSnd_internal >= task->myTask.ui64FileLen) {
								 //  Òª°ÑÁÙÊ±ÎÄ¼þÒÆ³ÉÕýÊ½ÎÄ¼þ
								 TCHAR		tmpFilePath[MAX_PATH + 1] = _T("");
								 //
								 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("all file data received. to copyfile"));
								 //
								 if (task->myTask.fp) {
#ifdef  __DEBUG__
									 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is: before fclose");
#endif
									 fclose(task->myTask.fp);  task->myTask.fp = NULL;
#ifdef  __DEBUG__
									 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is: after fclose");
#endif
								 }
								 //
								 _sntprintf(tmpFilePath, mycountof(tmpFilePath), _T("%s.tmp"), task->myTask.fullFilePath_save);
								 //
								 if (!CopyFile(tmpFilePath, task->myTask.fullFilePath_save, FALSE)) {
									 TCHAR  tBuf[256] = _T("");
#ifdef  __DEBUG__
									 traceLog((TCHAR*)_T("CopyFile %s->%s failed"), tmpFilePath, task->myTask.fullFilePath_save);
#endif
									 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("copyfile failed. %s->%s"), tmpFilePath, task->myTask.fullFilePath_save);
									 _sntprintf(tBuf, mycountof(tBuf), _T("Copy failed. %s"), task->myTask.fileName_transferred);
									 showNotification(0, 0, 0, 0, 0, 0, tBuf);
									 goto errLabel;
								 }
								 DeleteFile(tmpFilePath);

								 {
									 void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
									 CQnmDb  db;
									 if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
									 pDb = db.m_pDbMem->pDb;
#endif 

									 if (g_dbFuncs.pf_updateTaskStatus(pDb, CONST_imTaskStatus_recvFinished, pMsgElem->iTaskId))  goto  errLabel;
								 }

								 showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, FALSE, CONST_imCommType_transferFileReq, pMsgElem->iTaskId, CONST_imTaskStatus_recvFinished, 100, task->myTask.ui64FileLen, task->myTask.fileName_transferred, task->myTask.fullFilePath_save);

								 //
								 pFileDataReq_o->tmpInternal.ucbFileEnd = TRUE;
								 traceLogA((char*)"bFileEnd is true");

								 //
								 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Transfering file ends."));

							 }

							 iErr = 1;  goto  errLabel;
						 }

						 traceLogA((char*)"");

					 }

					 iErr = 1;  goto  errLabel;
				 }
			 }
			 if (!isUcFlgResp(pMsgInput->ucFlg) && !isUcFlgResp(pMsgElem->ucFlg)) {		//  ·¢ËÍÎÄ¼þ
				 switch (pContent->uiType) {
				 case  CONST_imCommType_transferFileDataReq:
#ifndef ORG_FILE_SEND_LOGIC
					 if (pContentElem->uiType == CONST_imCommType_transferFileReq
						 && pContent->transferFileDataReq.tStartTime_org == pMsgElem->tStartTime
						 && pContent->transferFileDataReq.uiTranNo_org == pMsgElem->uiTranNo)
					 {
						 TASK_transferFile* task = (TASK_transferFile*)taskElem;
						 if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_transferFile)  goto  errLabel;
						 QMC_taskData_transferFile* pTt = (QMC_taskData_transferFile*)pTaskInfo->var.pTaskData;

						 //
						 TRANSFER_FILE_REQ* pFileReq = &pContentElem->transferFileReq;
						 TRANSFER_FILEDATA_REQ* pFileDataReq = &pContent->transferFileDataReq;
						 TRANSFER_FILEDATA_RESP* pFileDataResp_o = (TRANSFER_FILEDATA_RESP*)p1;
						 DWORD64						ui64offset = 0;
						 int							nRead = 0;

						 //pFileDataReq->us_nBlocks;

						 if (!pFileDataResp_o || !pFileReq->ui64FileLen || !pFileDataReq->uiSizePerSnd || sizeof(pFileDataResp_o->buf) < pFileDataReq->uiSizePerSnd) {
#ifdef  __DEBUG__
							 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is failed: sizeof(  buf  )  <  uiSizePerSnd");
#endif
							 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("findOrgMsg error: fileDataReq, sizeof(  buf  ) %d < sizePerSnd [%d]"), sizeof(pFileDataResp_o->buf), pFileDataReq->uiSizePerSnd);
							 goto  errLabel;
						 }

						 ui64offset = ((DWORD64)pFileDataReq->uiDataBlockIndex) * pFileDataReq->uiSizePerSnd;
						 if (ui64offset >= pFileReq->ui64FileLen) {
#ifdef  __DEBUG__
							 traceLog((TCHAR*)_T("findOrgMsg error: fileDataReq, blockIndex [%d] * sizePerSnd [%d] > fileLen [%I64u]"), pFileDataReq->uiDataBlockIndex, pFileDataReq->uiSizePerSnd, pFileReq->ui64FileLen);
#endif
							 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("findOrgMsg error: fileDataReq, blockIndex [%d] * sizePerSnd [%d] > fileLen [%I64u]"), pFileDataReq->uiDataBlockIndex, pFileDataReq->uiSizePerSnd, pFileReq->ui64FileLen);
							 goto  errLabel;
						 }


						 //  ÕâÀï¼ÆËãÒ»ÏÂÒÑ¾­·¢ËÍµÄ°Ù·Ö±È
						 DWORD	dwCurTickCnt;
						 //
						 dwCurTickCnt = GetTickCount();
						 if (dwCurTickCnt > pTt->dwLastReportTickCnt + 1000) {	//  ÎªÁË²»Ó°Ïì½çÃæ²Ù×÷£¬Òª¹ý3Ãë²ÅÄÜ¼ÆËãÒ»´Î
							 pTt->dwLastReportTickCnt = dwCurTickCnt;
							 //
							 float	f = 0;
							 unsigned  char  ucPercent;
							 //
							 f = (float)pFileDataReq->uiDataBlockIndex * pFileDataReq->uiSizePerSnd;
							 f = f / pFileReq->ui64FileLen;
							 ucPercent = (unsigned  char)(f * 100);

							 //  if  (  ucPercent  !=  pFileReq->ucPercent  )  
							 {	//  ±¨¸æ×´Ì¬

								 showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgInput->data.route.idInfo_from, FALSE, CONST_imCommType_transferFileReq, pMsgElem->iTaskId, CONST_imTaskStatus_sending, ucPercent, pFileDataReq->uiDataBlockIndex * pFileDataReq->uiSizePerSnd, NULL, NULL);

							 }
						 }

#ifdef  __DEBUG__
						 traceLogA((char*)"");
						 int  iThreadId = GetCurrentThreadId();
#endif

						 if (!task->myTask.fp) {
							 task->myTask.fp = _tfopen(pContentElem->transferFileReq.fullFilePath, _T("rb"));
							 if (!task->myTask.fp) {
#ifdef  __DEBUG__
								 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is failed: _tfopen {%S} err", pContentElem->transferFileReq.fullFilePath);
#endif
								 goto  errLabel;
							 }
						 }
						 //  ÕâÀïÓ¦¸ÃÓÃ64Î»µÄ²Ù×÷ÒÔ¿ÉÒÔ²Ù×÷´óÎÄ¼þ£¬µ«ÊÇÔÝÊ±ÏÈÓÃ32Î»µÄ
						 //  if  (  fseek(  pFileReq->fp,  (  long  )ui64offset,  SEEK_SET  )  )  
						 if (_fseeki64(task->myTask.fp, ui64offset, SEEK_SET))
						 {
#ifdef  __DEBUG__
							 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is failed:  _fseeki64 err");
#endif
							 goto  errLabel;
						 }
						 nRead = (int)min(pFileReq->ui64FileLen - ui64offset, pFileDataReq->uiSizePerSnd);
						 if (1 != fread(pFileDataResp_o->buf, nRead, 1, task->myTask.fp))  goto  errLabel;
						 pFileDataResp_o->uiLen = nRead;
						 //
						 pFileDataResp_o->uiDataBlockIndex = pFileDataReq->uiDataBlockIndex;

						 iErr = 1;  goto  errLabel;
					 }
					 break;
#else //ORG_FILE_SEND_LOGIC
					 if (pContentElem->uiType == CONST_imCommType_transferFileReq
						 && pContent->transferFileDataReq.tStartTime_org == pMsgElem->tStartTime
						 && pContent->transferFileDataReq.uiTranNo_org == pMsgElem->uiTranNo)
					 {
						 TASK_transferFile* task = (TASK_transferFile*)taskElem;
						 if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_transferFile)  goto  errLabel;
						 QMC_taskData_transferFile* pTt = (QMC_taskData_transferFile*)pTaskInfo->var.pTaskData;

						 //
						 TRANSFER_FILE_REQ* pFileReq = &pContentElem->transferFileReq;
						 TRANSFER_FILEDATA_REQ* pFileDataReq = &pContent->transferFileDataReq;
						 //TRANSFER_FILEDATA_RESP	*	pFileDataResp_o			=	(  TRANSFER_FILEDATA_RESP  *  )p1;
						 std::vector<TRANSFER_FILEDATA_RESP>* pFileDataResp_o_list = (std::vector<TRANSFER_FILEDATA_RESP>*)p1;
						 DWORD64						ui64offset = 0;
						 int							nRead = 0;




						 if (!pFileDataResp_o_list || !pFileReq->ui64FileLen || !pFileDataReq->uiSizePerSnd
							 || CONST_bufSize_transferFileDataResp < pFileDataReq->uiSizePerSnd) {
#ifdef  __DEBUG__
							 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is failed: sizeof(  buf  )  <  uiSizePerSnd");
#endif

							 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""),
								 _T("findOrgMsg error: fileDataReq, sizeof(  buf  ) %d < sizePerSnd [%d]"), CONST_bufSize_transferFileDataResp,
								 pFileDataReq->uiSizePerSnd);

							 goto  errLabel;
						 }

						 if (pFileDataReq->us_nBlocks <= 0) {
#ifdef  __DEBUG__
							 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is failed: us_nBlocks <= 0");
#endif

							 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""),
								 _T("findOrgMsg error:  pFileDataReq->us_nBlocks %d < 0"), pFileDataReq->us_nBlocks);

							 goto  errLabel;
						 }


						 //
#if  10  //  这里
														   //
						 for (int i = 0; i < pFileDataReq->us_nBlocks; ++i) {
							 unsigned  int uiDataBlockIndex = pFileDataReq->uiDataBlockIndex + i;
							 CQyMalloc  mallocObj_resp;
							 TRANSFER_FILEDATA_RESP* tmp_pResp = (TRANSFER_FILEDATA_RESP*)mallocObj_resp.mallocf(sizeof(TRANSFER_FILEDATA_RESP));
							 if (!tmp_pResp)  goto  errLabel;
							 TRANSFER_FILEDATA_RESP& resp = *tmp_pResp;
							 memset(&resp, 0, sizeof(resp));
							 resp.uiType = CONST_imCommType_transferFileDataResp;

							 ui64offset = ((DWORD64)uiDataBlockIndex) * pFileDataReq->uiSizePerSnd;
							 if (ui64offset >= pFileReq->ui64FileLen) {
#ifdef  __DEBUG__
								 traceLog((TCHAR*)_T("findOrgMsg error: fileDataReq, blockIndex [%d] * sizePerSnd [%d] > fileLen [%I64u]"),
									 uiDataBlockIndex, pFileDataReq->uiSizePerSnd, pFileReq->ui64FileLen);
#endif
								 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""),
									 _T("findOrgMsg error: fileDataReq, blockIndex [%d] * sizePerSnd [%d] > fileLen [%I64u]"),
									 uiDataBlockIndex, pFileDataReq->uiSizePerSnd, pFileReq->ui64FileLen);
								 goto  errLabel;
							 }


							 //  ÕâÀï¼ÆËãÒ»ÏÂÒÑ¾­·¢ËÍµÄ°Ù·Ö±È
							 DWORD	dwCurTickCnt;
							 //
							 dwCurTickCnt = GetTickCount();
							 if (dwCurTickCnt > pTt->dwLastReportTickCnt + 1000) {	//  ÎªÁË²»Ó°Ïì½çÃæ²Ù×÷£¬Òª¹ý3Ãë²ÅÄÜ¼ÆËãÒ»´Î
								 pTt->dwLastReportTickCnt = dwCurTickCnt;
								 //
								 float	f = 0;
								 unsigned  char  ucPercent;
								 //
								 f = (float)uiDataBlockIndex * pFileDataReq->uiSizePerSnd;
								 f = f / pFileReq->ui64FileLen;
								 ucPercent = (unsigned  char)(f * 100);

								 //  if  (  ucPercent  !=  pFileReq->ucPercent  )  
								 {	//  ±¨¸æ×´Ì¬

									 showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender,
										 &pMsgInput->data.route.idInfo_from, FALSE, CONST_imCommType_transferFileReq, pMsgElem->iTaskId,
										 CONST_imTaskStatus_sending, ucPercent, uiDataBlockIndex * pFileDataReq->uiSizePerSnd,
										 NULL, NULL);

								 }
							 }

#ifdef  __DEBUG__
							 traceLogA((char*)"");
							 int  iThreadId = GetCurrentThreadId();
#endif

							 if (!task->myTask.fp) {
								 task->myTask.fp = _tfopen(pContentElem->transferFileReq.fullFilePath, _T("rb"));
								 if (!task->myTask.fp) {
#ifdef  __DEBUG__
									 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is failed: _tfopen {%S} err",
										 pContentElem->transferFileReq.fullFilePath);
#endif
									 goto  errLabel;
								 }
							 }
							 //  ÕâÀïÓ¦¸ÃÓÃ64Î»µÄ²Ù×÷ÒÔ¿ÉÒÔ²Ù×÷´óÎÄ¼þ£¬µ«ÊÇÔÝÊ±ÏÈÓÃ32Î»µÄ
							 //  if  (  fseek(  pFileReq->fp,  (  long  )ui64offset,  SEEK_SET  )  )  
							 if (_fseeki64(task->myTask.fp, ui64offset, SEEK_SET))
							 {
#ifdef  __DEBUG__
								 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is failed:  _fseeki64 err");
#endif
								 goto  errLabel;
							 }
							 nRead = (int)min(pFileReq->ui64FileLen - ui64offset, pFileDataReq->uiSizePerSnd);

							 DWORD  dwTickCnt = myGetTickCount(NULL);
							 if (1 != fread(resp.buf, nRead, 1, task->myTask.fp))  goto  errLabel;
							 DWORD  dwTickCntEnd = myGetTickCount(NULL);


							 resp.uiLen = nRead;
							 //
							 resp.uiDataBlockIndex = uiDataBlockIndex;

							 pFileDataResp_o_list->push_back(resp);
						 }
#endif

						 iErr = 1;  goto  errLabel;
					 }
					 break;
#endif //ORG_FILE_SEND_LOGIC
				 case  CONST_imCommType_transferFileEndReq:
					 if (pContentElem->uiType == CONST_imCommType_transferFileReq					//  ·¢ËÍ·½´¦Àí
						 && pContent->transferFileEndReq.tStartTime_org == pMsgElem->tStartTime
						 && pContent->transferFileEndReq.uiTranNo_org == pMsgElem->uiTranNo)
					 {
						 TASK_transferFile* task = (TASK_transferFile*)taskElem;
						 //
						 IM_CONTENTU* pContent_o = (IM_CONTENTU*)p1;
						 int		iStatus = CONST_imTaskStatus_sendFinished;
						 //
#ifdef  __DEBUG__
						 traceLogA((char*)"transferFileEnd ");
#endif	
						 //
						 if (pContent_o) {
							 if (pContent_o->uiType == CONST_imCommType_transferFileEndResp) {
								 TRANSFER_FILEEND_RESP* pFileEndResp_o = &pContent_o->transferFileEndResp;
								 //														   
								 if (!pContentElem->transferFileReq.bGrpTask) {
									 //  2015/09/08
									 if (pFileEndResp_o->tmpInternal.bChkToRemove_i) {
										 //pContentElem->transferFileReq.myTask.bNeedRemoved  =  TRUE;
										 pTaskInfo->var.bNeedRemoved = TRUE;
										 //
										 pFileEndResp_o->tmpInternal.bNeedRemoved_o = TRUE;
									 }
									 //
									 void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
									 CQnmDb	db;

									 if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
									 pDb = db.m_pDbMem->pDb;
#endif
									 if (g_dbFuncs.pf_updateTaskStatus(pDb, iStatus, pMsgElem->iTaskId))  goto  errLabel;
									 //
									 showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, FALSE, CONST_imCommType_transferFileReq, pMsgElem->iTaskId, iStatus, 100, pContentElem->transferFileReq.ui64FileLen, pContentElem->transferFileReq.fullFilePath, pContentElem->transferFileReq.fullFilePath);

								 }
								 else {	//  ¶Ô·Ö×é£¬ÓÐÊ²Ã´ÈËÊÕµ½ÁËÎÄ¼þ£¬Ò²ÏÔÊ¾Ò»ÏÂ
									 showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgInput->addr_logicalPeer.idInfo, TRUE, CONST_imCommType_transferFileReq, pMsgElem->iTaskId, iStatus, 100, pContentElem->transferFileReq.ui64FileLen, pContentElem->transferFileReq.fullFilePath, pContentElem->transferFileReq.fullFilePath);

								 }

							 }
						 }
						 //
						 iErr = 1;  goto  errLabel;
					 }
					 break;
				 case  CONST_imCommType_taskProcReq:
					 if (pContentElem->uiType == CONST_imCommType_transferFileReq
						 && pTaskInfo->var.m_bReplyTask  //  CONST_imCommType_transferFileReplyReq		//  ½ÓÊÕ·½´¦Àí
						 && pContent->taskProcReq.tStartTime_org == pMsgElem->tStartTime//pContentElem->transferFileReplyReq.tStartTime_org
						 && pContent->taskProcReq.uiTranNo_org == pMsgElem->uiTranNo//pContentElem->transferFileReplyReq.uiTranNo_org  
						 )
					 {
						 TASK_transferFile* task = (TASK_transferFile*)taskElem;
						 //
						 IM_CONTENTU* pContent_o = (IM_CONTENTU*)p1;
						 int		iStatus = CONST_imTaskStatus_canceledBySender;
						 //	
#ifdef  __DEBUG__
						 traceLogA((char*)"transferFileProcReq ");
#endif
						 //
						 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Transfering file canceled by sender."));

						 //
						 if (pContent_o) {
							 if (pContent_o->uiType == CONST_imCommType_taskProcResp) {
								 TRANSFER_FILE_PROCRESP* pFileProcResp = &pContent_o->taskProcResp;

								 //
								 pTaskInfo->var.bNeedRemoved = true;
								 pFileProcResp->tmpInternal.bNeedRemoved_o = TRUE;

								 //									
								 void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
								 CQnmDb	db;

								 if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
								 pDb = db.m_pDbMem->pDb;
#endif
								 if (g_dbFuncs.pf_updateTaskStatus(pDb, iStatus, pMsgElem->iTaskId))  goto  errLabel;
								 //
								 showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, FALSE, CONST_imCommType_transferFileReq, pMsgElem->iTaskId, iStatus, 0, task->myTask.ui64FileLen, task->myTask.fileName_transferred, task->myTask.fullFilePath_save);
							 }
						 }
						 //
						 iErr = 1;  goto  errLabel;
					 }
					 if (pContentElem->uiType == CONST_imCommType_transferFileReq) {		//  ·¢ËÍ·½´¦Àí
						 if (pContent->taskProcReq.tStartTime_org == pMsgElem->tStartTime
							 && pContent->taskProcReq.uiTranNo_org == pMsgElem->uiTranNo)
						 {
							 IM_CONTENTU* pContent_o = (IM_CONTENTU*)p1;
							 int		iStatus = CONST_imTaskStatus_canceledByReceiver;
							 //
#ifdef  __DEBUG__
							 if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
								 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is: msg - procReq found");
							 }
#endif
							 //
							 if (pContent_o) {
								 if (pContent_o->uiType == CONST_imCommType_taskProcResp) {
									 TRANSFER_FILE_PROCRESP* pFileProcResp = &pContent_o->taskProcResp;

									 if (!pContentElem->transferFileReq.bGrpTask) {

										 //
										 pFileProcResp->tmpInternal.bNeedRemoved_o = TRUE;

										 //
										 void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
										 CQnmDb	db;
										 if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
										 pDb = db.m_pDbMem->pDb;
#endif
										 if (g_dbFuncs.pf_updateTaskStatus(pDb, iStatus, pMsgElem->iTaskId))  goto  errLabel;
										 //
										 showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, FALSE, CONST_imCommType_transferFileReq, pMsgElem->iTaskId, iStatus, 0, 0, pContentElem->transferFileReq.fileName, pContentElem->transferFileReq.fullFilePath);
									 }
								 }
							 }
							 //
							 iErr = 1;  goto  errLabel;
						 }
					 }
					 //
					 //  transferAvInfo, 
					 //
					 if (pContentElem->uiType == CONST_imCommType_transferAvReplyInfo) {		//  ½ÓÊÕ·½´¦Àí
						 TASK_transferAv* task = (TASK_transferAv*)taskElem;
						 PROC_TASK_AV* pTaskElem = &task->myTask;//get_transferAvReplyInfo_pTask(  &pContentElem->transferAvReplyInfo,  _T(  ""  )  );
						 if (!pTaskElem)  goto errLabel;
						 //
						 if (pContent->taskProcReq.tStartTime_org == pContentElem->transferAvReplyInfo.tStartTime_org
							 && pContent->taskProcReq.uiTranNo_org == pContentElem->transferAvReplyInfo.uiTranNo_org)
						 {
							 IM_CONTENTU* pContent_o = (IM_CONTENTU*)p1;
							 int		iStatus = CONST_imTaskStatus_canceledBySender;
							 //
#ifdef  __DEBUG__
							 traceLogA((char*)"taskProcReq ");
#endif
							 //
							 if (pContent_o) {
								 if (pContent_o->uiType == CONST_imCommType_taskProcResp) {
									 TASK_PROC_RESP* pFileProcResp = &pContent_o->taskProcResp;

									 pFileProcResp->tmpInternal.bNeedRemoved_o = TRUE;

									 //															   
									 void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
									 CQnmDb	db;

									 if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
									 pDb = db.m_pDbMem->pDb;
#endif
									 if (g_dbFuncs.pf_updateTaskStatus(pDb, iStatus, pMsgElem->iTaskId))  goto  errLabel;
									 //
									 showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, FALSE, CONST_imCommType_transferAvInfo, pMsgElem->iTaskId, iStatus, 0, 0, 0, 0);
								 }
							 }
							 //
							 iErr = 1;  goto  errLabel;
						 }

						 //  2014/08/26
						 if (pContent->taskProcReq.usOp == CONST_imOp_recv_applyForKeyFrame) {

							 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("recv applyforKeyFrame from %I64u."), pMsgInput->data.route.idInfo_from.ui64Id);

							 //
							 if (pContent->taskProcReq.vStream.uiTranNo_openAvDev == pContentElem->transferAvReplyInfo.tranInfo.video.uiTranNo_openAvDev) {

#ifdef  __DEBUG__
								 if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
									 traceLogA((char*)"findOrgMsgAndProcess_mis: get a applyForKeyFrame msg");
								 }
#endif

								 //
								 tmpiRet = procTaskProcReq_applyForKeyFrame(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgElem, &pContent->taskProcReq, pContentElem, pTaskElem);
								 if (tmpiRet) {
									 iErr = tmpiRet;  goto  errLabel;
								 }

								 iErr = 1;  goto  errLabel;
							 }
						 }

					 }
					 if (pContentElem->uiType == CONST_imCommType_transferAvInfo) {		//  ·¢ËÍ·½´¦Àí
						 //
						 TASK_transferAv* task = (TASK_transferAv*)taskElem;
						 PROC_TASK_AV* pTaskElem = &task->myTask;//get_transferAvInfo_pTask(  &pContentElem->transferAvInfo,  _T(  ""  )  );
						 if (!pTaskElem)  goto  errLabel;
						 QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
						 if (pTc->common.uiType != CONST_taskDataType_conf) {
							 goto  errLabel;
						 }
						 MIS_CNT* pMisCnt = (MIS_CNT*)pMsgElem->pMisCnt;
						 if (!pMisCnt)  goto  errLabel;

						 //
						 TCHAR  tBuf[128];
						 if (pContent->taskProcReq.usOp == CONST_imOp_recv_cancel) {
							 _sntprintf(tBuf, mycountof(tBuf), _T("hahahaha findOrgMsg: msgElem: av (st %I64u,tn %d) "), pMsgElem->tStartTime, pMsgElem->uiTranNo);
							 showInfo_open0(0, 0, tBuf);
						 }

						 //
						 if (pContent->taskProcReq.tStartTime_org == pMsgElem->tStartTime
							 && pContent->taskProcReq.uiTranNo_org == pMsgElem->uiTranNo)
						 {
							 IM_CONTENTU* pContent_o = (IM_CONTENTU*)p1;
							 //
#ifdef  __DEBUG__
							 if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
								 traceLogA((char*)"tmpHandler_findOrgMsgAndProc_is: msg - procReq found");
							 }
#endif															   

							 //
							 if (pContent_o) {
								 if (pContent_o->uiType == CONST_imCommType_taskProcResp) {
									 TASK_PROC_RESP* pFileProcResp = &pContent_o->taskProcResp;

									 pFileProcResp->idInfo_logicalPeer.ui64Id = pMsgElem->addr_logicalPeer.idInfo.ui64Id;

									 if (pContent->taskProcReq.usOp == CONST_imOp_recv_applyForChkTaskAlive) {
										 //
										 addToMsgrs_sendLocalAv(pProcInfo, pMisCnt, &pMsgInput->data.route.idInfo_from, task->myTask.ucbVideoConferenceStarter, &pTaskInfo->var.curRoute_sendLocalAv, true, _T("findOrgMsg.taskProcReq.chkTaskAlive"));
										 //
										 iErr = 1;  goto  errLabel;
									 }

									 if (pContent->taskProcReq.usOp == CONST_imOp_ping) {
										 //
										 pTaskInfo->var.dwTickCnt_recv_lastRefreshed = myGetTickCount(mynull);
										 //
										 iErr = 1;  goto  errLabel;
									 }

									 //
									 if (pQyMc->appParams.bConfServer) {
										 if (pContent->taskProcReq.usOp == CONST_imOp_recv_applyForOrgReq) {
											 pMsgInput->iTaskId = pMsgElem->iTaskId;
											 //  2014/11/18
											 if (pContentElem->transferAvInfo.idInfo_logicalPeer.ui64Id) {
												 pMsgInput->addr_logicalPeer.idInfo.ui64Id = pContentElem->transferAvInfo.idInfo_logicalPeer.ui64Id;
											 }
											 else {
												 pMsgInput->addr_logicalPeer.idInfo.ui64Id = pMsgElem->addr_logicalPeer.idInfo.ui64Id;
											 }
											 //
											 pContent->taskProcReq.hWnd_task = pTaskElem->hWnd_task;

											 //
											 qPostMsg(pMsgInput, offsetof(MIS_MSG_INPUT, data) + offsetof(MIS_MSG_routeTalkData, buf) + sizeof(TASK_PROC_REQ), &pQyMc->gui.processQ, _T("tmp_findOrg 5"));
											 PostMessage(g_pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);

											 iErr = 1;  goto  errLabel;
										 }
										 if (pContent->taskProcReq.usOp == CONST_imOp_recv_cancel) {
											 removeFromMsgrs_sendLocalAv(pProcInfo, pMisCnt, &pMsgInput->data.route.idInfo_from, &pTaskInfo->var.curRoute_sendLocalAv, true,  _T(  "findOrgMsg:taskProcReq.recv_cancel.4063"  ));
										 }
									 }

									 //
									 int					iStatus = CONST_imTaskStatus_canceledByReceiver;

									 //  2014/12/03
									 BOOL  bCanCancel = TRUE;
									 if (pContentElem->transferAvInfo.bGrpTask) {
										 //
										 if (pTc->grp.idInfo_initiator.ui64Id == pMsgInput->data.route.idInfo_from.ui64Id) {
											 int  ii = 0;
											 //
										 }
										 else  if (pContentElem->transferAvInfo.confCfg.hgInfo.iMeetingType_hg == CONST_meetingType_p2p) {
											 int  ii = 0;
											 //
											 showInfo_open0(0, 0, _T("canceled if p2p"));
											 //
										 }
										 else {
											 //
											 bCanCancel = FALSE;
										 }
									 }
									 if (pTaskElem->doProxy.bExists_avProxy) {
										 bCanCancel = FALSE;
									 }

									 //  2017/09/11
									 if (pContent->taskProcReq.usOp == CONST_imOp_recv_cancel) {
										 tmp_procTask_recv_cancel(pProcInfo, pTaskElem, pMsgInput, &pContent->taskProcReq);
									 }

									 //
									 //if  (  !pContentElem->transferAvInfo.bGrpTask  )  
									 if (bCanCancel)
									 {
										 pFileProcResp->tmpInternal.bNeedRemoved_o = TRUE;

										 //  2014/12/03
										 TCHAR  tBuf[128] = _T("");
										 _sntprintf(tBuf, mycountof(tBuf), _T("findOrgMsg: taskProcReq from receiver %I64u, to cancel transferAvInfo"), pMsgInput->data.route.idInfo_from.ui64Id);
#ifdef  __DEBUG__
										 traceLog((TCHAR*)_T("%s"), tBuf);
#endif
										 showInfo_open0(0, 0, tBuf);

										 //
										 void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
										 CQnmDb				db;

										 if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
										 pDb = db.m_pDbMem->pDb;
#endif
										 if (g_dbFuncs.pf_updateTaskStatus(pDb, iStatus, pMsgElem->iTaskId))  goto  errLabel;
										 //
										 showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, FALSE, pContentElem->uiType, pMsgElem->iTaskId, iStatus, 0, 0, 0, 0);
									 }
								 }

								 //
							 }



							 //
							 iErr = 1;  goto  errLabel;
						 }
						 //  2014/08/26
						 if (pContent->taskProcReq.usOp == CONST_imOp_recv_applyForKeyFrame) {

							 TCHAR  tBuf[128];
							 _sntprintf(tBuf, mycountof(tBuf), _T("findOrgMsg: talker%I64u, recv applyforKeyFrame from %I64u, tn_openAvDev %d. matched iTaskId %d"), pMsgElem->addr_logicalPeer.idInfo.ui64Id, pMsgInput->data.route.idInfo_from.ui64Id, pContent->taskProcReq.vStream.uiTranNo_openAvDev, pMsgElem->iTaskId);
							 showInfo_open0(0, 0, tBuf);

							 //
							 BOOL  tmp_bFound = FALSE;
							 //
							 if (pTaskElem->ucbVideoConferenceStarter) {
#if  0	//  这是以后要使用的代理模式，暂时不用。2014/08/28
								 if (pContent->taskProcReq.vStream.uiTranNo_openAvDev == pContentElem->transferAvInfo.tranInfo.video.uiTranNo_openAvDev) {
									 tmp_bFound = TRUE;
								 }
#endif
								 //  2014/08/28. 暂时采用直接模式
								 if (pContent->taskProcReq.vStream.uiTranNo_openAvDev == pTaskElem->mem0_from.video.tv_recvd.uiTranNo_openAvDev) {
									 tmp_bFound = TRUE;
								 }
								 //  2014/12/06
								 if (pContent->taskProcReq.vStream.uiTranNo_openAvDev == pContentElem->transferAvInfo.confMosaicTranInfo_video.video.uiTranNo_openAvDev
									 || pContent->taskProcReq.vStream.uiTranNo_openAvDev == pContentElem->transferAvInfo.confMosaicTranInfo_resource.video.uiTranNo_openAvDev)
								 {
									 tmp_bFound = TRUE;

								 }
							 }
							 else {
								 if (!pTaskInfo->var.m_bReplyTask) {
									 if (pContent->taskProcReq.vStream.uiTranNo_openAvDev == pContentElem->transferAvInfo.ass.tranInfo.video.uiTranNo_openAvDev) {
										 tmp_bFound = TRUE;
									 }
								 }
								 else {
									 if (pContent->taskProcReq.vStream.uiTranNo_openAvDev == task->myTask.reply_avTranInfo.video.uiTranNo_openAvDev) {
										 tmp_bFound = TRUE;
									 }
								 }
							 }
							 
							 //  2026/04/02. 已经matched, 可以用遍历的方式来获取keyFrame. 下面的tmp_bFound的括号里的处理似乎不要也行
							 doAll_setFlg_forceKeyFrame(pProcInfo);
							 
							 //
							 if (tmp_bFound) {

#ifdef  __DEBUG__
								 if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
									 traceLogA((char*)"findOrgMsgAndProcess_mis: get a applyForKeyFrame msg");
								 }
#endif

								 //
								 tmpiRet = procTaskProcReq_applyForKeyFrame(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgElem, &pContent->taskProcReq, pContentElem, pTaskElem);
								 if (tmpiRet) {
									 iErr = tmpiRet;  goto  errLabel;
								 }

								 iErr = 1;  goto  errLabel;
							 }
							 //
						 }
						 //  2014/10/09
						 if (pContent->taskProcReq.usOp == CONST_imOp_stopSending
							 || pContent->taskProcReq.usOp == CONST_imOp_requestToSend)
						 {
							 if (pContent->taskProcReq.viewDynBmp.ros.uiObjType) {
								 if (pContentElem->transferAvInfo.ass.resObj.uiObjType == pContent->taskProcReq.viewDynBmp.ros.uiObjType
									 && pContentElem->transferAvInfo.ass.resObj.usIndex_obj == pContent->taskProcReq.viewDynBmp.ros.usIndex_obj)
								 {
#ifdef  __DEBUG__
									 traceLog((TCHAR*)_T("findOrgMsgAndProc: get taskProcReq msg"));
#endif

									 pMsgInput->iTaskId = pMsgElem->iTaskId;
									 pMsgInput->addr_logicalPeer.idInfo.ui64Id = pMsgElem->addr_logicalPeer.idInfo.ui64Id;

									 //
									 pContent->taskProcReq.hWnd_task = pTaskElem->hWnd_task;

									 //
									 qPostMsg(pMsgInput, offsetof(MIS_MSG_INPUT, data) + offsetof(MIS_MSG_routeTalkData, buf) + sizeof(TASK_PROC_REQ), &pQyMc->gui.processQ, _T("tmp_findOrg_3  "));
									 PostMessage(g_pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);

									 iErr = 1;  goto  errLabel;
								 }
							 }
						 }
						 //
						 if (pContent->taskProcReq.uiContentType_org == CONST_imCommType_transferVideoData) {
							 bool  bMatched = false;

							 //
							 if (task->myTask.ucbVideoConference) {
								 if (pContent->taskProcReq.uiTranNo_org == pContentElem->transferAvInfo.ass.tranInfo.video.uiTranNo_openAvDev) {
									 bMatched = true;
								 }
							 }
							 else {
								 if (isVideoActive(pMisCnt, &pTc->videoConference, &pMisCnt->idInfo, pContent->taskProcReq.uiTranNo_org, mynull)) {
									 bMatched = true;
								 }
							 }

							 //																
							 if (bMatched) {
								 if (pContent->taskProcReq.usOp == CONST_imOp_recv_cancel) {
									 bool  bConfAv = true;
									 //
									 if (pContentElem->transferAvInfo.uiTaskType == CONST_imTaskType_shareDynBmp) {
										 bConfAv = false;
									 }
									 //
									 removeFromMsgrs_sendLocalAv(pProcInfo, pMisCnt, &pMsgInput->data.route.idInfo_from, &pTaskInfo->var.curRoute_sendLocalAv, bConfAv, _T("findOrgMsg:taskProcReq. tvd, recv_cancel"));
								 }
							 }
						 }
						 //  2009/10/18
						 if (pContent->taskProcReq.usOp == CONST_imOp_recv_applyForOrgReq) {

							 if (pContent->taskProcReq.uiContentType_org == CONST_imCommType_transferAudioData
								 && pContent->taskProcReq.uiTranNo_org == pContentElem->transferAvInfo.ass.tranInfo.audio.uiTranNo_openAvDev)
							 {
								 //
								 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("recv applyforOrgReq from %I64u. audio _tn %d"), pMsgInput->data.route.idInfo_from.ui64Id, pMsgInput->uiTranNo);

								 //
#ifdef  __DEBUG__
								 if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
									 traceLogA((char*)"findOrgMsgAndProcess_mis: get a applyForOrgReq msg");
								 }
								 //
								 pContent->taskProcReq.bTestFlg_a = true;
#endif
								 pMsgInput->iTaskId = pMsgElem->iTaskId;
								 //  2014/11/18
								 if (pContentElem->transferAvInfo.idInfo_logicalPeer.ui64Id) {
									 pMsgInput->addr_logicalPeer.idInfo.ui64Id = pContentElem->transferAvInfo.idInfo_logicalPeer.ui64Id;
								 }
								 else {
									 pMsgInput->addr_logicalPeer.idInfo.ui64Id = pMsgElem->addr_logicalPeer.idInfo.ui64Id;
								 }
								 //
								 pContent->taskProcReq.hWnd_task = pTaskElem->hWnd_task;

								 //
								 qPostMsg(pMsgInput, offsetof(MIS_MSG_INPUT, data) + offsetof(MIS_MSG_routeTalkData, buf) + sizeof(TASK_PROC_REQ), &pQyMc->gui.processQ, _T("tmp_findOrg 5"));
								 PostMessage(g_pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);

								 iErr = 1;  goto  errLabel;
							 }
							 //
							 //  2010/12/27
							 if (pContent->taskProcReq.uiContentType_org == CONST_imCommType_transferVideoData) {
								 bool  bMatched = false;

								 //
								 if (task->myTask.ucbVideoConference) {
									 if (pContent->taskProcReq.uiTranNo_org == pContentElem->transferAvInfo.ass.tranInfo.video.uiTranNo_openAvDev) {
										 bMatched = true;
									 }
								 }
								 else {
									 if (isVideoActive(pMisCnt, &pTc->videoConference, &pMisCnt->idInfo, pContent->taskProcReq.uiTranNo_org, mynull)) {
										 bMatched = true;
									 }
								 }

								 //																
								 if (bMatched) {
									 //
									 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("recv applyforOrgReq from %I64u. video org_tn %d"), pMsgInput->data.route.idInfo_from.ui64Id, pContent->taskProcReq.uiTranNo_org);

									 //
#ifdef  __DEBUG__
									 if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
										 traceLogA((char*)"findOrgMsgAndProcess_mis: get a applyForOrgReq msg");
									 }
									 //
									 pContent->taskProcReq.bTestFlg_v = true;

#endif
									 //
									 if (pMsgElem->uiTaskType == CONST_imTaskType_shareDynBmp) {
										 if (pTaskElem->iIndex_sharedObj) {
											 QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, pTaskElem->iIndex_sharedObj);
											 if (pSharedObj) {
												 MIS_CNT* pMisCnt = getMisCntByName(pProcInfo, _T(""));
												 removeFromMsgrs_sendLocalAv(pProcInfo, pMisCnt, &pMsgInput->data.route.idInfo_from, &pTaskInfo->var.curRoute_sendLocalAv,false,_T("findOrgMsg:shareDynBmp.4290"));
												 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("findOrgMsgAndProc: shareDynBmp, index_sharedObj %d, removeFromMsgrs_sendLocalAv, %I64u"), pTaskElem->iIndex_sharedObj, pMsgInput->data.route.idInfo_from);
												 iErr = 1;  goto  errLabel;
											 }
										 }
									 }

									 //
									 pMsgInput->iTaskId = pMsgElem->iTaskId;
									 //  2014/11/18
									 if (pContentElem->transferAvInfo.idInfo_logicalPeer.ui64Id) {
										 pMsgInput->addr_logicalPeer.idInfo.ui64Id = pContentElem->transferAvInfo.idInfo_logicalPeer.ui64Id;
									 }
									 else {
										 pMsgInput->addr_logicalPeer.idInfo.ui64Id = pMsgElem->addr_logicalPeer.idInfo.ui64Id;
									 }
									 //
									 pContent->taskProcReq.hWnd_task = pTaskElem->hWnd_task;

									 //
									 qPostMsg(pMsgInput, offsetof(MIS_MSG_INPUT, data) + offsetof(MIS_MSG_routeTalkData, buf) + sizeof(TASK_PROC_REQ), &pQyMc->gui.processQ, _T("tmp_findOrg 4"));
									 PostMessage(g_pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);

									 iErr = 1;  goto  errLabel;
								 }
							 }
						 }
					 }

					 break;
				 default:
					 break;
				 }
			 }
			 //
		 }
									 break;
		 default:
			 break;

		 }
		 //
	 }
								break;
	 default:
		 break;
	 }



	 iErr = 0;
 errLabel:
	 return  iErr;
 }



