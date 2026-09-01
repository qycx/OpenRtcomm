


#include	"stdafx.h"
 
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#include	"qmcSound_dx.h"

#include	"qmcVideoCapture_isCli.h"

#include	"qmcCommFunc_isCli.h"
#include	"qmcTaskInfo.h"

//
//int  iitransformTaskAudioPkt_useAudioQ2(  QY_TRANSFORM  *  pTransform,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_AUDIO_DATA  *  pReq,  PKT_info_toDec  *  pPktInfo_toDec,  int  index_pMems_from,  int  index_activeMems_from,  myPLAY_AUDIO_DATA	*	pPkt_dec,  MIS_MSGU  *  pMsgBuf  );
int transformTaskAudioPkt(QY_TRANSFORM* pTransform, TRANSFER_AUDIO_dataMemHead* pMemHead, byte* pInput1, myPLAY_AUDIO_DATA* pPkt_dec, MIS_MSGU* pMsgBuf_unused);




///////////////////////
#if  0  //  2016/12/13
 int  iigetNextAPktInfo_toDec(  PKT_info_toDec  *  pCurPktInfo,  QY_Q2  *	pAudioQ2  )
{
	int  iErr  =  -1;
	MIS_MSGU  *  pMsg  =  (  MIS_MSGU  *  )pCurPktInfo->pMIS_MSGU;
	IM_CONTENTU					*	pContent					=	NULL;

	if  (  !pCurPktInfo->bGot_msg  ||  !pCurPktInfo->info.bGot_pkt  )  {
		
		BOOL  bMsgOk  =  FALSE;
		if  (  pCurPktInfo->bGot_msg  )  {
			switch  (  pMsg->uiType  )  {
					case  CONST_misMsgType_task:
						  pContent		=	(  IM_CONTENTU  *  )pMsg->task.data.buf;
						  switch  (  pContent->uiType  )  {									 
								  case  CONST_imCommType_transferAudioData:  {
									    TRANSFER_AUDIO_DATA  *  pReq  =  &pContent->transferAudioData;
										//
										if  (  pCurPktInfo->info.index_mems  <  0  ||  pCurPktInfo->info.index_mems  >=  pReq->usCnt  )  break;
										//
										int  i  =  pCurPktInfo->info.index_mems;
										TRANSFER_AUDIO_dataMemHead  *  pMem  =  &pReq->mems[i];
										int  iPos  =  pCurPktInfo->info.iPos;
									
										if  (  iPos  +  pReq->mems[i].uiLen  >=  pReq->uiLen  )  break;

										//
										bMsgOk  =  TRUE;

										}
									    break;
								  default:
										  break;
						  }
						  break;
					default:
							break;
			}
		}
		//
		if  (  !bMsgOk  )  pCurPktInfo->bGot_msg  =  FALSE;
		//
		if  (  !pCurPktInfo->bGot_msg  )  {
			//
			unsigned  int  len;
			len  =  sizeof(  pMsg[0]  );			
			if  (  q2GetMsg(  pAudioQ2,  pMsg,  &len  )  )  goto  errLabel;		
			memset(  (  (  char  *  )pMsg  )  +  len,  0,  min(  256,  sizeof(  pMsg[0]  )  -  len  )  );			   
			//
			switch  (  pMsg->uiType  )  {
					case  CONST_misMsgType_task:
						  pContent		=	(  IM_CONTENTU  *  )pMsg->task.data.buf;
						  switch  (  pContent->uiType  )  {									 
								  case  CONST_imCommType_transferAudioData:  {
									    TRANSFER_AUDIO_DATA  *  pReq  =  &pContent->transferAudioData;

									    //
									    pCurPktInfo->bGot_msg  =  TRUE;
										//
										memset(  &pCurPktInfo->info,  0,  sizeof(  pCurPktInfo->info  )  );
										//
										if  (  !pReq->uiLen  )  goto  errLabel;
										//
										pCurPktInfo->info.bGot_pkt  =  TRUE;										
										}								    
									    break;
								  default:
										 break;
						  }		
			}
			//	
			if  (  !pCurPktInfo->bGot_msg  )  goto  errLabel;
			}
		else  {	
			  pContent  =  (  IM_CONTENTU  *  )pMsg->task.data.buf;
			  //	
			  TRANSFER_AUDIO_DATA  *  pReq  =  &pContent->transferAudioData;
			  //			  
			  if  (  pCurPktInfo->info.index_mems  <  0  ||  pCurPktInfo->info.index_mems  >=  pReq->usCnt  )  goto  errLabel;										
			  //
			  int  i  =  pCurPktInfo->info.index_mems;				
			  TRANSFER_AUDIO_dataMemHead  *  pMem  =  &pReq->mems[i];
			  int  iPos  =  pCurPktInfo->info.iPos;
				
			  if  (  iPos  +  pReq->mems[i].uiLen  >=  pReq->uiLen  )  goto  errLabel;
			  //
			  pCurPktInfo->info.iPos  +=  pMem->uiLen;
			  pCurPktInfo->info.index_mems  ++  ;
			  //
			  pCurPktInfo->info.bGot_pkt  =  TRUE;		
		}

		//
		M_set_pktId_getNewPkt(  pCurPktInfo  );
	}
	
	//
	if  (  !pCurPktInfo->info.bGot_pkt  )  {
		goto  errLabel;
	}



	iErr  =  0;

errLabel:

	return  iErr;

}
#endif



//
 int getNextPktInfo_toDec( PKT_info_toDec *pCurPktInfoParam, QY_qBuf2 *pDataQ2)
{
	int iErr = -1;

	PKT_info_toDec* pCurPktInfo = pCurPktInfoParam;
	{
		MIS_MSGU* pMsg = (MIS_MSGU*)pCurPktInfo->pMIS_MSGU;
		IM_CONTENTU* pContent = mynull;

		//	
		if (pCurPktInfo->bGot_msg)
		{
			//
			if (!pCurPktInfo->info.bGot_pkt)
			{
#if 0//false
				//
				switch (pMsg->uiType)
				{
				case Consts.CONST_misMsgType_task:
					pContent = (IM_CONTENTU*)pMsg->task.data.buf;
					switch (pContent->uiType)
					{
					case Consts.CONST_imCommType_transferAudioData:
					{
						TRANSFER_AUDIO_DATA* pReq = &pContent->transferAudioData;
						TRANSFER_AUDIO_dataMemHead* pReq_mems = (TRANSFER_AUDIO_dataMemHead*)pReq->buf_TRANSFER_AUDIO_dataMemHead_mems;
						//
						if (pCurPktInfo->info.index_mems >= 0 && pCurPktInfo->info.index_mems + 1 < pReq->usCnt)
						{
							//										
							int i = pCurPktInfo->info.index_mems;
							TRANSFER_AUDIO_dataMemHead* pMem = &pReq_mems[i];
							int iPos = pCurPktInfo->info.iPos;

							if (iPos + pReq_mems[i].uiLen < pReq->uiLen)
							{

								pCurPktInfo->info.iPos += (int)pMem->uiLen;
								pCurPktInfo->info.index_mems++;
								//			  
								pCurPktInfo->info.bGot_pkt = true;

								//		
								M_set_pktId_getNewPkt(pCurPktInfo);

							}
						}
						//
					}
					break;
					default:
						break;
					}
					break;
				case Consts.CONST_misMsgType_input:
					pContent = (IM_CONTENTU*)pMsg->input.data.buf;
					switch (pContent->uiType)
					{
					case Consts.CONST_imCommType_transferAudioData:
					{
						TRANSFER_AUDIO_DATA* pReq = &pContent->transferAudioData;
						TRANSFER_AUDIO_dataMemHead* pReq_mems = (TRANSFER_AUDIO_dataMemHead*)pReq->buf_TRANSFER_AUDIO_dataMemHead_mems;
						int bufSize = Consts.bufSize_TRANSFER_AUDIO_dataMemHead_mems;
						//
						if (pCurPktInfo->info.index_mems >= 0 && pCurPktInfo->info.index_mems + 1 < pReq->usCnt)
						{
							//										
							int i = pCurPktInfo->info.index_mems;
							TRANSFER_AUDIO_dataMemHead* pMem = getMem(pReq_mems, bufSize, i);// &pReq_mems[i];
							int iPos = pCurPktInfo->info.iPos;

							if (iPos + pMem->uiLen < pReq->uiLen)
							{

								pCurPktInfo->info.iPos += (int)pMem->uiLen;
								pCurPktInfo->info.index_mems++;
								//			  
								pCurPktInfo->info.bGot_pkt = true;

								//		
								M_set_pktId_getNewPkt(pCurPktInfo);

							}
						}
						//
					}
					break;
					case Consts.CONST_imCommType_transferVideoData:
					{
						TRANSFER_VIDEO_DATA* pReq = &pContent->transferVideoData;
						TRANSFER_VIDEO_dataMemHead* pReq_mems = (TRANSFER_VIDEO_dataMemHead*)pReq->buf_TRANSFER_VIDEO_dataMemHead_mems;
						int bufSize = Consts.bufSize_TRANSFER_VIDEO_dataMemHead_mems;
						//
						if (pCurPktInfo->info.index_mems >= 0 && pCurPktInfo->info.index_mems + 1 < pReq->usCnt)
						{
							//										
							int i = pCurPktInfo->info.index_mems;
							TRANSFER_VIDEO_dataMemHead* pMem = getMem(pReq_mems, bufSize, i);// &pReq_mems[i];
							int iPos = pCurPktInfo->info.iPos;

							if (iPos + pMem->uiLen < pReq->uiLen)
							{

								pCurPktInfo->info.iPos += (int)pMem->uiLen;
								pCurPktInfo->info.index_mems++;
								//			  
								pCurPktInfo->info.bGot_pkt = true;

								//		
								M_set_pktId_getNewPkt(pCurPktInfo);

							}
						}
						//
					}
					break;

					default:
						break;
					}
					break;

				default:
					break;
				}
#endif

				//
				if (!pCurPktInfo->info.bGot_pkt)
				{
					pCurPktInfo->bGot_msg = false;
				}
			}
		}


		//	
		if (!pCurPktInfo->bGot_msg)
		{
			//
			uint len;
#if false
			len = (uint)sizeof(MIS_MSGU);
			if (0 != q2GetMsg(pDataQ2, (IntPtr)pMsg, &len)) goto errLabel;
			mymemset((IntPtr)(((byte*)pMsg) + len), 0, (int)Math.Min(256, sizeof(MIS_MSGU) - len));
#endif
			void * pHeadData = mynull;
			switch (pDataQ2->cfg.m_qType)
			{
			case CONST_qType_decA:
				pHeadData = &pCurPktInfo->pkt_encA.memHead_a;
				break;
			default:
				showInfo_open0(0, _T(""), _T("getNextPktInfo failed; unprocessed qType"));
				goto errLabel;
			}
			pCurPktInfo->pkt_encA.len = pCurPktInfo->pkt_encA.bufSize;
			if (0 != pDataQ2->q2GetMsg(pHeadData, pCurPktInfo->pkt_encA.buf, (uint*)&pCurPktInfo->pkt_encA.len,_T("getNextPktInfo_toDec a"))) goto errLabel;
			pCurPktInfo->bGot_msg = true;
			pCurPktInfo->info.bGot_pkt = true;
			//
			M_set_pktId_getNewPkt(pCurPktInfo);

		}


		//
		if (!pCurPktInfo->info.bGot_pkt)
		{
			goto errLabel;
		}



		iErr = 0;

	errLabel:

		if (0 != iErr)
		{
			pCurPktInfo->bGot_msg = false;
		}

	}

	return iErr;

}







 //
#if  0  //  2017/10/14
 void  cleanAll_PKT_info_toDec(  PKT_info_toDec  *  p,  LPCTSTR  hint  )
 {
	 p->bGot_msg  =  FALSE;
	 
	 //
	 return;
 }
#endif


 int  doDecodeAudio_default(  QY_TRANSFORM  *  pTransform,  int  index_pMems_from1,  int  index_activeMems_from,  MIS_MSGU  *  pMsgBuf  )
{
	int					iErr	=	-1;
	CCtxQmc  *  pProcInfo  =  (  CCtxQmc  *  )pTransform->pProcInfo;//
	if  (  !pProcInfo  )  return  -1;

	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	if  (  !pAddr  )  return  -1;
	int						iTaskId				=	pTransform->iTaskId;
	//
	AV_TRAN_INFO		*	pTranInfo_unused			=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	if  (  !pTranInfo_unused  )  return  -1;
	//
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	if  (  !pTask  )  return  -1;
		
	//
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  (  CCtxQmc  *  )pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	//
#if  0
	if  (  index_pMems_from  <  0  ||  index_pMems_from  >=  pTc->videoConference.usCntLimit_mems_from  )  {
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "doDecVideo: index_pMems_from err"  )  );
			 #endif
			 return  -1;
	
	}	
	TASK_AV_FROM		*	pFrom				=	NULL;	//  &pTask->pMems_from[index_pMems_from];
		
	pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  pTransform->index_activeMems_from,  _T(  "doDecodeAudio_default"  )  );
	if  (  !pFrom  )  return  -1;
#endif
	if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  return -1;
	DLG_TALK_videoConferenceActiveMemFrom  * pActiveMem_from = &pTc->videoConference.activeMems_from[index_activeMems_from];

#if  10
	//  2014/05/08
	_sntprintf(  pTransform->audio.debugStep.showInfo.tWhere,  mycountof(  pTransform->audio.debugStep.showInfo.tWhere  ),  _T(  "tt=%d"  ),  iTaskId  );
	pTransform->audio.debugStep.showInfo.uiStep  =  0;
	

	//
	MACRO_setMyStep(  pTransform->audio.debugStep,  21  );

		 //  if  (  !pFrom->video.ucbInited  )  
		 if  (  !pTransform->audio.ucbInited  )  
		 {
			 if  (  initTaskAvFrom_audio(  pProcInfo,  pActiveMem_from,  index_activeMems_from,  pTransform  )  )  goto  errLabel;
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),
				 _T(  "doDecodeAudio_default: initTaskAvFrom_audio %d"  ),  index_activeMems_from  );
		 }
		 if  (  !pTransform->audio.ucbInited  )  {
			 #ifdef  __DEBUG__
					 traceLogA(  (char*)  "doDecodeAudio_default failed: audio is not inited"  );
			 #endif
			 goto  errLabel;
		 }

		 long  old_pktId; old_pktId = 0;
		 //
		 for  (  ;  ;  )  {
			  if  (  bTransformAudioQuit(  pTransform,  0,  0  )  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "doTrans_default failed：quit is true"  )  );
				  #endif
				  goto  errLabel;
			  }
			  //
			  MACRO_setMyStep(  pTransform->audio.debugStep,  100  );	//  2014/07/17
			  //
			  for  (  ;  ;  )  {
				   if  (  bTransformAudioQuit(  pTransform,  0,  0  )  )  goto  errLabel;
				   //
				   MACRO_setMyStep(  pTransform->audio.debugStep,  105  );	//  2014/07/17
				   //
				   if (pProcInfo->cfg.b_useAudioQ2_toDecA) {
					   if (!getNextAPktInfo_toDec(&pTransform->audio.curPktInfo_toDec, &pTransform->audio.q2))  break;
				   }
				   else {
					    if (0 == getNextPktInfo_toDec(&pTransform->audio.curPktInfo_toDec, pTransform->audio.qBuf2)) break;
				   }
				   //
				   MACRO_setMyStep(  pTransform->audio.debugStep,  106  );	//  2014/07/17
				   //
				   #if  0
						Sleep(  40  );
				   #else
					    //
				        int  nWaitInMs  =  40;
						//
						nWaitInMs  =  100;	//  2015/02/06. 是不是放大点能让cpu更悠闲点。但是，不能影响获取包的实时性
						//
						DWORD  dwRet;
						QY_Q2  *  pAudioQ2  =  (  QY_Q2  *  )&pTransform->audio.q2;
						if (pProcInfo->cfg.b_useAudioQ2_toDecA) {
							dwRet = WaitForSingleObject(pAudioQ2->hEvents[0], nWaitInMs);
						}
						else {
							dwRet = WaitForSingleObject(pTransform->audio.qBuf2->hEvent0, nWaitInMs);
						}
						if  (  dwRet  ==  WAIT_FAILED  )  {
							showInfo_open0(  0,  0,  _T(  "SmplBsReader::LoadNextFrame failed, WaitForSingleObject failed"  )  );
							goto  errLabel;			  
						}
						#ifdef  __DEBUG__
								#if  0  					  
								{						  
									CQyString	tmpStr;
									switch  (  dwRet  )  {							  
											case  WAIT_OBJECT_0:
												  tmpStr  =  _T(  "SmplBsReader::LoadNextFrame: waited"  );									
												  break;							  
											case  WAIT_TIMEOUT:								    
												  tmpStr  =  _T(  "SmplBsReader::LoadNextFrame: timeout"  );
												  break;							  
											default:								      
													tmpStr  =  _T(  "SmplBsReader::LoadNextFrame: unknown wait ret"  );									  
													break;					  
									}					  
									showInfo_open0(  0,  0,  tmpStr  );					  
								}
							    #endif
					    #endif

				   #endif
			  }
			  //
			  MACRO_setMyStep(  pTransform->audio.debugStep,  108  );	//  2014/07/17
			  //
			  unsigned  char  *  pInput  =  NULL;
			  unsigned  int  uiInputSize  =  0;
			  unsigned  int  uiSampleTimeInMs  =  0;
			  unsigned  int  uiPts  =  0;	//  2015/02/09
			  //
			  if (pProcInfo->cfg.b_useAudioQ2_toDecA) {
				  if (dec_parseEncAPkt_i_useAudioQ2(CONST_uiTransformType_dec, pTransform, &pTransform->audio.curPktInfo_toDec, &old_pktId, &pInput, &uiInputSize, &uiSampleTimeInMs, &uiPts)) {
#ifdef  __DEBUG__
					  traceLog((TCHAR*)_T("doDecodeAudio_default failed, parsePkt failed"));
#endif
					  goto  errLabel;
				  }
			  }
			  else {
				  if (0 != dec_parseEncAPkt_i(CONST_uiTransformType_dec, pTransform, &pTransform->audio.curPktInfo_toDec, &old_pktId, &pInput, &uiInputSize, &uiSampleTimeInMs, &uiPts))
				  {
#ifdef __DEBUG__
					  traceLog((TCHAR*)_T("doDecodeAudio_default failed, parsePkt failed"));
#endif
					  goto errLabel;
				  }

			  }

			  //			  	
			  MACRO_setMyStep(  pTransform->audio.debugStep,  109  );	//  2014/07/17

			  //
			  pActiveMem_from->dwLastTickCnt_aData  =  myGetTickCount(  NULL  );


			  //
			  PKT_info_toDec  *  pPktInfo_toDec  =  &pTransform->audio.curPktInfo_toDec;
			  PKT_info_toDec* pPktInfo_toDec1 = pPktInfo_toDec;

			  TRANSFER_AUDIO_dataMemHead* pMem = mynull;
			  TRANSFER_AUDIO_dataMemHead tmp_pMem;

#if 0
			  MIS_MSGU  *  pMsg  =  (  MIS_MSGU  *  )pPktInfo_toDec->pMIS_MSGU;
			  if  (  pMsg->uiType  !=  CONST_misMsgType_task  )  goto  errLabel;
			  IM_CONTENTU  *  pContent		=	(  IM_CONTENTU  *  )pMsg->task.data.buf;
			  if  (  pContent->uiType  !=  CONST_imCommType_transferAudioData  )  goto  errLabel;
#endif
			  myPLAY_AUDIO_DATA  *  pPkt_dec  =  (  myPLAY_AUDIO_DATA  *  )pPktInfo_toDec->pPkt_dec_myPLAY_AUDIO_DATA;
			  byte* data = mynull;

			  //
			  if (pProcInfo->cfg.b_useAudioQ2_toDecA)
			  {

				  MIS_MSGU* pMsg = (MIS_MSGU*)pPktInfo_toDec->pMIS_MSGU;
				  if (pMsg->uiType != CONST_misMsgType_task)
				  {
					  traceLogA((char*)"doDecodeAudio_default failed, only task msg accepted");
					  goto errLabel;
				  }
				  IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->task.data.buf;
				  if (pContent->uiType != CONST_imCommType_transferAudioData) goto errLabel;

//#if DEBUG
//				  ref myPLAY_AUDIO_DATA tmp_pPkt = ref * pPkt_dec;
//#endif
				  //
				  //
				  //
				  int iPos = pPktInfo_toDec->info.iPos;
				  TRANSFER_AUDIO_DATA* pReq = &pContent->transferAudioData;
				  if (pPktInfo_toDec1->info.index_mems < 0 || pPktInfo_toDec1->info.index_mems >= pReq->usCnt) goto errLabel;
				  int i;
				  i = pPktInfo_toDec1->info.index_mems;

				  //
				  TRANSFER_AUDIO_dataMemHead* pReq_mems = (TRANSFER_AUDIO_dataMemHead*)pReq->mems;
				  int bufSize = sizeof(TRANSFER_AUDIO_dataMemHead);// Consts.bufSize_TRANSFER_AUDIO_dataMemHead_mems;

				  pMem = &pReq_mems[i];

				  if (iPos + pMem->uiLen > pReq->uiLen)
				  {
					  goto errLabel;
				  }
				  data = (byte*)pReq->buf + iPos;

				  //
				  tmp_pMem = *pMem;
				  //
				  if (tmp_pMem.idInfo.ui64Id == 0)
				  {
					  tmp_pMem.idInfo.ui64Id = pMsg->input.data.route.idInfo_from.ui64Id;
				  }
				  if (tmp_pMem.uiTranNo_openAvDev == 0)
				  {
					  tmp_pMem.uiTranNo_openAvDev = pContent->transferAudioData.uiTranNo_openAvDev;
				  }


			  }
			  else
			  {
				  pMem = &pPktInfo_toDec1->pkt_encA.memHead_a;
				  data = (byte*)pPktInfo_toDec1->pkt_encA.buf;

				  //
				  tmp_pMem = *pMem;

			  }

			  //


			  //
			  int ret = transformTaskAudioPkt(pTransform, &tmp_pMem, data, pPkt_dec, pMsgBuf);
			  if (ret != 0) {
				  goto errLabel;
			  }

			  //
			  //transformTaskAudioPkt_useAudioQ2(  pTransform,  &pMsg->task,  &pContent->transferAudioData,  pPktInfo_toDec,  pContent->transferAudioData.tmpInternal.param.index_pMems_from,  pContent->transferAudioData.tmpInternal.param.index_activeMems_from,  pPkt_dec,  pMsgBuf  );
			  


			  //doDecVideoPkt(  pTransform,  pPkt,  pMsgBuf  );

			  //
			  MACRO_setMyStep(  pTransform->audio.debugStep,  110  );	//  2014/07/17
			  

			  //  2014/08/11
			  if  (  pTransform->audio.status.ucbDecFailed  )  {
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doDecodeAudio_default: decFailed, need to reinited. %d"  ),  index_activeMems_from  );
				  goto  errLabel;
			  }

			  BOOL  bPktsRedirected = FALSE;
		
			  postAPktToRender(pTransform, pPkt_dec, &bPktsRedirected);

			  /*if (bPktsRedirected) {
				  detachAPkt(pPkt_dec, 0);
			  }
			  else {				  
				  clean_myPLAY_AUDIO_DATA(pPkt_dec, _T(""));
			  }*/

			  clean_PKT_info_toDec(pPktInfo_toDec, _T(""));
			  

			  //
			  continue;
		 }
#endif

		 iErr  =  0;
errLabel:

		 exitTaskAvFrom_audio(  pProcInfo,  pTransform  );  

	return  iErr;
}

//  2014/07/21
int  doDecodeAudio_vorbis(  QY_TRANSFORM  *  pTransform,  int  index_pMems_from,  MIS_MSGU  *  pMsgBuf  )
{
	int					iErr	=	-1;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
#if  0
	QY_MC			*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;//QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
#endif
		CUS_MODULES  *  pCusModules  =  (  CUS_MODULES  *  )pProcInfo->getCusModules(  );
	if  (  !pCusModules  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "doDecV_vp8 failed, pCusModules is null"  )  );
		#endif
		return  -1;
	}	

	
	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	if  (  !pAddr  )  return  -1;
	int						iTaskId				=	pTransform->iTaskId;
	//
	AV_TRAN_INFO		*	pTranInfo_unused			=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	if  (  !pTranInfo_unused  )  return  -1;
	//
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	if  (  !pTask  )  return  -1;


#if  0
	TASK_AV_FROM		*	pFrom				=	NULL;

	pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  pTransform->index_activeMems_from,  _T(  "doDecodeVideo_vp8"  )  );
	if  (  !pFrom  )  return  -1;

	//
	exitTaskAvFrom_audio(  pProcInfo,  pTransform  );
	

	MACRO_setMyStep(  pTransform->audio.debugStep,  21  );

		 //  
		 if  (  !pTransform->audio.ucbInited  )  
		 {
			 //unsigned  int  uiModuleType_suggested  =  CONST_moduleType_dec_vp8;
			 //BOOL  bUseDecTool  =  FALSE;
			 //
			 if  (  initTaskAvFrom_audio(  pProcInfo,  pActiveMem_from,  index_pMems_from,  pTransform  )  )  goto  errLabel;
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskAudio: initTaskAvFrom_audio %d"  ),  index_pMems_from  );
		 }
		 if  (  !pTransform->audio.ucbInited  )  {
			 traceLogA(  (char*)  "procTaskAudio failed: audio is not inited"  );
			 goto  errLabel;
		 }

		 //
		 if  (  pTransform->audio.uiModuleType_toDec  !=  CONST_moduleType_qdc_vorbis_dec  )  {
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "doTransformVideo_mediaSdk failed, uiModuleType_toDec is not vorbis"  )  );
			 #endif
			 goto  errLabel;
		 }

		 //
		 if  (  !pCusModules->pQdc_vorbis_dec
			 ||  !pCusModules->pQdc_vorbis_dec->compress.pf_qdcDecompressAudioRun  )
		 {
			 goto  errLabel;
		 }

		 __try  {
				if  (  pCusModules->pQdc_vorbis_dec->compress.pf_qdcDecompressAudioRun(  &pTransform->audio.u.qoi.myQoi.common  )  )  goto  errLabel;
				 }
		 __except  (  1  )  {
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "qdcDecompressAudioRun exception"  )  );
				   #endif
				   goto  errLabel;
		 }
#endif

		 iErr  =  0;
errLabel:

		 exitTaskAvFrom_audio(  pProcInfo,  pTransform  );  

	return  iErr;
}


 //
 int  doDecodeAudio(  QY_TRANSFORM  *  pTransform,  MIS_MSGU  *  pMsgBuf  )
{
	int		iErr	=	-1;	 

	int	i;
	MC_VAR_common		*				pProcInfo					=	(  MC_VAR_common  *  )pTransform->pProcInfo;//
	if (  !pProcInfo  )  return  -1;	 
#if  0
	QY_MC				*				pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;//
	if  (  !pQyMc  )  return  -1;
#endif

	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;
	

	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	if  (  !pAddr  )  return  -1;
	int						iTaskId				=	pTransform->iTaskId;
	//
	AV_TRAN_INFO		*	pTranInfo_unused			=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	if  (  !pTranInfo_unused  )  return  -1;
	//
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	if  (  !pTask  )  return  -1;

	//
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  (  CCtxQmc  *  )pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;


#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "Not finished:  doDecodeAudio"  )  );
#endif

#if  10
	TRANSFORM_AUDIO_procInfo		*	pTransformAudio				=	&pTransform->audio;

#if 0
	//myDRAW_VIDEO_DATA  *     pPkt  =  pTransformVideo->pCurPkt;
	if  (  !pTransformAudio->curPktInfo_toDec.bGot_msg
		||  !pTransformAudio->curPktInfo_toDec.info.bGot_pkt  )  
	{
		return  -1;
	}
	MIS_MSGU  *  pMsg_curPkt  =  (  MIS_MSGU  *  )pTransformAudio->curPktInfo_toDec.pMIS_MSGU;
	if  (  pMsg_curPkt->uiType  !=  CONST_misMsgType_task  )  return  -1;
	IM_CONTENTU  *  pContent  =  (  IM_CONTENTU  *  )pMsg_curPkt->task.data.buf;
	if  (  pContent->uiType  !=  CONST_imCommType_transferAudioData  )  return  -1;
	TRANSFER_AUDIO_DATA  *  pReq  =  &pContent->transferAudioData;
	if  (  pReq->tmpInternal.param.index_activeMems_from  !=  pTransform->index_activeMems_from  )  {	
		traceLogA(  (char*)  "mcThreadProc_transformAudio: transferAudio.index_activeMems_from %d != transform.%d",  pReq->tmpInternal.param.index_activeMems_from,  pTransform->index_activeMems_from  );
		return  -1;
	}
#endif

	
	int  index_activeMems_from  =  pTransform->index_activeMems_from;
		 

#if  0
	int  index_pMems_from  =  pReq->tmpInternal.param.index_pMems_from;
		 //
		 TASK_AV_FROM		*	pFrom				=	NULL;

		 //  2014/11/12
		 pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  index_activeMems_from,  _T(  "doDecodeAudio"  )  );
		 if  (  !pFrom  )  return  -1;
#endif
		 if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  return  -1;
		 DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[index_activeMems_from];


		 //
		 unsigned  int  uiModuleType_toDec  =  0;
		 switch  (  pActiveMem_from->avStream.obj.tranInfo.audio.compressor.common.ucCompressors  )  {
				 case  CONST_audioCompressors_ipp:
					   uiModuleType_toDec  =  CONST_moduleType_ipp;					   
					   break;
				 case  CONST_audioCompressors_vorbis:							//  2014/07/21
					   uiModuleType_toDec  =  CONST_moduleType_qdc_vorbis_dec;
					   break;
				 default:
						break;
		 }
		 
		 //
		 adjustModuleType_decA(&uiModuleType_toDec);


		 //
#if  0
		 switch  (  uiModuleType_toDec  )  {
				 case  CONST_moduleType_qdc_vorbis_dec:
					   return  doDecodeAudio_vorbis(  pTransform,  index_pMems_from,  pMsgBuf  );
					   break;
				 default:
						break;
		 }
#endif

		 //
		  doDecodeAudio_default(  pTransform,  -1,  index_activeMems_from,  pMsgBuf  );

		  

#endif

	iErr  =  0;

errLabel:

	//  exit
	
	return  iErr;
}



//  2015/02/14
//
 extern "C" DWORD WINAPI mcThreadProc_decAudio( LPVOID lpParameter )
{
	 QY_TRANSFORM					*	pTransform					=	(  QY_TRANSFORM  *  )lpParameter;
	 if  (  !pTransform  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo					=	(  MC_VAR_isCli  *  )pTransform->pProcInfo;
	 if (  !pProcInfo  )  return  -1;	
#if  0
	 PROC_TASK_AV					*	pTask						=	(  PROC_TASK_AV  *  )pTransform->pTask;
	 if  (  !pTask  )  return  -1;
#endif
	 TRANSFORM_AUDIO_procInfo		*	pTransformAudio				=	&pTransform->audio;

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

	 CQyMalloc							mallocObj_pkt_dec_pBuf;
	 myPLAY_AUDIO_DATA					pkt_dec;
	 
	 CQyMalloc							mallocObj_pMsgBuf;
	 MIS_MSGU						*	pMsgBuf						=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;

	 QY_SHARED_OBJ					*	pSharedObj					=	NULL;

	 CQyCoInit							coInit;		//  2010/06/07


	 traceLogA(  (char*)  "mcThreadProc_transformAudio enters"  );

	 MACRO_setStep(  pTransformAudio->debugStep,  CONST_threadStep_start  );

	 //
	 pTransformAudio->bRunning  =  TRUE;
	 //  memset(  &pTransformAudio->m_var,  0,  sizeof(  pTransformAudio->m_var  )  );

	 if  (  !(  pMsg  =  (  MIS_MSGU  *  )mallocObj.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  )  )  )  goto  errLabel;
	 //
	 //  2015/02/14
	 memset(  &pkt_dec,  0,  sizeof(  pkt_dec  )  );
	 //
	 unsigned  int  uiBufSize_pkt_dec; uiBufSize_pkt_dec = pProcInfo->cfg.uiBufSize_myPlayAudioData;  //  offsetof(  myPLAY_AUDIO_DATA,  buf  )  +  pProcInfo->cfg.uiBufSize_myPlayAudioData;	//  
	 int	iAllocType; iAllocType = 0;	//  CONST_iAllocType_audio
	 //  if  (  !(  pTransform->audio.pPkt_dec  =  (  myPLAY_AUDIO_DATA  *  )mallocObj_pPkt_dec.mallocf(  iAllocType,  uiBufSize_pPkt_dec  )  )  )  goto  errLabel;
	 //
	 if  (  !mallocObj_pkt_dec_pBuf.mallocf(  iAllocType,  uiBufSize_pkt_dec  )  )  goto  errLabel;
	 if  (  mallocObj_pkt_dec_pBuf.get(  &pkt_dec.memory  )  )  goto  errLabel;  
	 //
	 //if  (  pTask->ucbVideoConferenceStarter  )  
	 {
		 //  if  (  !(  pTransform->audio.pMsgTask_toCompress_videoConference  =  (  MIS_MSG_TALK  *  )mallocObj_pMsgTask_toCompress.malloc(  sizeof(  MIS_MSG_TALK  )  )  )  )  goto  errLabel;
	 }

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s %d starts"  ),  pTransformAudio->q2.cfg.name,  pTransform->index_activeMems_from  );

	 ///////////////////////////
	 //  2016/12/10
	 	 //
	 //  2014/03/23	 	
	 GENERIC_Q_cfgEx	qCfgEx;	//  2012/11/10
	 GENERIC_Q_CFG		tmpCfg;

	TCHAR	tBuf[128];
#define		CONST_mutexNamePrefix_decA_inDataCacheQ	_T(  "decA_in"  )
#define		CONST_mutexNamePrefix_decA_tmpDataQ		_T(  "decA_tmp"  )
	//
	int		tn; tn = GetTickCount();
	int		iTaskId; iTaskId = pTransform->iTaskId;
	int		index_activeMems_from; index_activeMems_from = pTransform->index_activeMems_from;
	//
	int size; size = 0;

	
	//
	size  =  sizeof(  myPLAY_AUDIO_DATA  );
	pTransformAudio->pCurPkt  =  (  myPLAY_AUDIO_DATA  *  )mymalloc(  size  );
	if  (  !pTransformAudio->pCurPkt  )  goto  errLabel;
	memset(  pTransformAudio->pCurPkt,  0,  size  );





	 //////////////////////////

	 //
	 memset(  &pTransformAudio->curPktInfo_toDec,  0,  sizeof(  pTransformAudio->curPktInfo_toDec  )  );
	 pTransformAudio->curPktInfo_toDec.pMIS_MSGU  =  pMsg;
	 pTransformAudio->curPktInfo_toDec.pPkt_dec_myPLAY_AUDIO_DATA  =  &pkt_dec;
	 pMsg->uiType  =  0;	
	 pTransformAudio->curPktInfo_toDec.pkt_encA.bufSize = CONST_bufSize_tmpPktEncA;



	 //
	 for  (  ;  !pTransformAudio->bQuit;  )  {
		  
		  if  (  !dwToInMs  )  {			  
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: mcThreadProc_transformAudio: dwToInMs %d"  ),  dwToInMs  );
			  dwToInMs  =  DEFAULT_dwToInMs;
		  }

		  //  2009/07/14
		  MACRO_setStep(  pTransformAudio->debugStep,  CONST_threadStep_toWait  );

		  //
		  DWORD  dwTickCnt0  =  GetTickCount(  );
		  DWORD  dwTickCnt;

		  DWORD  dwEvt;
		  if (pProcInfo->cfg.b_useAudioQ2_toDecA) {
			  dwEvt = MsgWaitForMultipleObjects(
				  pTransformAudio->q2.cfg.usCnt_hEvents,	//  mycountof(  pTransformAudio->hEvents  ),		// Number of events.
				  pTransformAudio->q2.hEvents,						// Location of handles.
				  FALSE,										// Wait for all?
				  dwToInMs,									// How long to wait?
				  0);										// Any message is an 
															 // event.
		  }
		  else {
			  dwEvt = MsgWaitForMultipleObjects(
				  1,	//  mycountof(  pTransformAudio->hEvents  ),		// Number of events.
				  &pTransformAudio->qBuf2->hEvent0,						// Location of handles.
				  FALSE,										// Wait for all?
				  dwToInMs,									// How long to wait?
				  0);										// Any message is an 
															 // event.
		  }
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
						     traceLogA(  (char*)  "transformAudio: event 1."  );
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
		  					 goto  errLabel;
						 break;
			  }
		  }


		  for  (  ;  !pTransformAudio->bQuit;  )  {

#if  0
			   //
			   MACRO_setStep(  pTransformAudio->debugStep,  CONST_threadStep_toGetMsg  );

			   //
			   len  =  sizeof(  pMsg[0]  );
			   {
				   CQyQ2Help	q2Help;
				   if  (  qGetMsg(  q2Help.getQ_toGetMsg(  &pTransformAudio->q2  ),  pMsg,  &len  )  )  break;
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
										   if  (  pContent->transferAudioData.tmpInternal.param.index_activeMems_from  !=  pTransform->index_activeMems_from  )  {
											   traceLogA(  (char*)  "mcThreadProc_transformAudio: transferAudio.index_activeMems_from %d != transform.%d",  pContent->transferAudioData.tmpInternal.param.index_activeMems_from,  pTransform->index_activeMems_from  );
											   break;
										   }

										   //  2010/09/02
										   BOOL  bNoSharedObj;  bNoSharedObj  =  FALSE;
										   if  (  pTask->doProxy.bExists_avProxy  )  bNoSharedObj  =  TRUE;

										   //
										   if  (  !bNoSharedObj  )  {
											   pSharedObj  =	getSharedObjByIndex(  pProcInfo,  pTask->iIndex_sharedObj  );
											   if  (  pSharedObj  )  {	
												   SHARED_OBJ_USR	*	pSharedObjUsr	=	getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
												   if  (  pSharedObjUsr  )  {
													   if  (  pSharedObjUsr->iTaskId  !=  pTransform->iTaskId  )  {
														   #ifdef  __DEBUG__
																   traceLog((TCHAR*)  _T(  "thread_transformAudio: sharedObjUsr isnt matched. skipped"  )  );
														   #endif
														   continue;				
													   }												   
												   }
											   }
										   }

										   //
										   MACRO_setStep(  pTransformAudio->debugStep,  CONST_threadStep_msgGot  );

										   //
										   transformTaskAudio(  pTransform,  &pMsg->task,  &pContent->transferAudioData,  pContent->transferAudioData.tmpInternal.param.index_pMems_from,  pContent->transferAudioData.tmpInternal.param.index_activeMems_from,  &pkt_dec,  pMsgBuf  );

										   //
										   MACRO_setStep(  pTransformAudio->debugStep,  CONST_threadStep_msgProced  );

										   break;
									 default:
											break;
							 }
									 
						     break;
					   default:
							   break;
			   }
#endif
			   //
			   //
			   //if  (  getNextAPktInfo_toDec(  &pTransformAudio->curPktInfo_toDec,  &pTransformAudio->q2  )  )  break;
			   if (pProcInfo->cfg.b_useAudioQ2_toDecA)
			   {
				   if (isQ2Empty(&pTransformAudio->q2)) break;
			   }
			   else
			   {
				   if (pTransformAudio->qBuf2->is_Q2Empty()) break;
			   }

			   //
			   if  (  !pTransform->audio.curPktInfo_toDec.lPktId_getNewPkt  )  {
				   //MACRO_qyAssert(  0,  _T(  "decAudio: id_pkt is 0"  )  );
			   }
			   //
			   long		old_pktId  =  pTransform->audio.curPktInfo_toDec.lPktId_getNewPkt;
			   doDecodeAudio(  pTransform,  pMsgBuf  );
			   if  (  pTransform->audio.curPktInfo_toDec.lPktId_getNewPkt  ==  old_pktId  )  {	//  如果没有处理掉就需要释放
				   clean_PKT_info_toDec(  &pTransform->audio.curPktInfo_toDec,  _T(  ""  )  );						  
			   }


			   
			   
		  }




	 }

errLabel:

	 //
	 MACRO_setStep(  pTransformAudio->debugStep,  CONST_threadStep_toExit  );

	 //  2009/05/28
	 exitTaskAvFrom_audio(  pProcInfo,  pTransform  );


	 //  2016/12/10
	 //  2014/03/25
	 clean_myPLAY_AUDIO_DATA(  pTransformAudio->pCurPkt,  _T(  "decAudio"  )  );
	 MACRO_safeFree(  pTransformAudio->pCurPkt  );

	 //  2014/03/24
#if  0
	 if  (  pTransformAudio->pInDataCacheQ  )  {
		 genericQFree(  pTransformAudio->pInDataCacheQ  );  pTransformAudio->pInDataCacheQ  =  NULL;
	 }
	 if  (  pTransformAudio->pTmpDataQ  )  {
		 genericQFree(  pTransformAudio->pTmpDataQ  );  pTransformAudio->pTmpDataQ  =  NULL;
	 }
#endif



	 //
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s %d ends."  ),  pTransformAudio->q2.cfg.name,  pTransform->index_activeMems_from  );

	 pTransformAudio->bRunning  =  FALSE;

	 MACRO_setStep(  pTransformAudio->debugStep,  CONST_threadStep_end  );

	 traceLogA(  (char*)  "mcThreadProc_transformAudio %S leaves",  pTransformAudio->q2.cfg.name  );

	 return  0;
}


extern "C" DWORD WINAPI mcThreadProc_decAudioRtsp(LPVOID lpParameter)
{
	QY_TRANSFORM* pTransform = (QY_TRANSFORM*)lpParameter;
	if (!pTransform)  return  -1;
	MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pTransform->pProcInfo;
	if (!pProcInfo)  return  -1;
#if  0
	PROC_TASK_AV* pTask = (PROC_TASK_AV*)pTransform->pTask;
	if (!pTask)  return  -1;
#endif
	TRANSFORM_AUDIO_procInfo* pTransformAudio = &pTransform->audio;

	QY_MC* pQyMc = (QY_MC*)pProcInfo->pQyMc;
	DYN_LIB_DX* pDynLib = (DYN_LIB_DX*)((QY_DYN_LIBS*)pQyMc->env.pDynLibs)->pLib_dx;
	//  int								i;

	CQyMalloc							mallocObj;
	MIS_MSGU* pMsg = NULL;
	unsigned  int						len;

	IM_CONTENTU* pContent = NULL;

#define		DEFAULT_dwToInMs		5000
	DWORD								dwToInMs = DEFAULT_dwToInMs;

	DWORD								dwTickCnt_lastAudioData = GetTickCount();;						// 

	CQyMalloc							mallocObj_pkt_dec_pBuf;
	myPLAY_AUDIO_DATA					pkt_dec;

	CQyMalloc							mallocObj_pMsgBuf;
	MIS_MSGU* pMsgBuf = (MIS_MSGU*)mallocObj_pMsgBuf.mallocf(sizeof(MIS_MSGU));
	if (!pMsgBuf)  return  -1;

	QY_SHARED_OBJ* pSharedObj = NULL;

	CQyCoInit							coInit;		//  2010/06/07


	traceLogA((char*)"mcThreadProc_transformAudio enters");

	MACRO_setStep(pTransformAudio->debugStep, CONST_threadStep_start);

	//
	pTransformAudio->bRunning = TRUE;
	//  memset(  &pTransformAudio->m_var,  0,  sizeof(  pTransformAudio->m_var  )  );

	if (!(pMsg = (MIS_MSGU*)mallocObj.mallocf(CONST_iAllocType_longTimeMsg, sizeof(MIS_MSGU))))  goto  errLabel;
	//
	//  2015/02/14
	memset(&pkt_dec, 0, sizeof(pkt_dec));
	//
	unsigned  int  uiBufSize_pkt_dec; uiBufSize_pkt_dec = pProcInfo->cfg.uiBufSize_myPlayAudioData;  //  offsetof(  myPLAY_AUDIO_DATA,  buf  )  +  pProcInfo->cfg.uiBufSize_myPlayAudioData;	//  
	int	iAllocType; iAllocType = 0;	//  CONST_iAllocType_audio
	//  if  (  !(  pTransform->audio.pPkt_dec  =  (  myPLAY_AUDIO_DATA  *  )mallocObj_pPkt_dec.mallocf(  iAllocType,  uiBufSize_pPkt_dec  )  )  )  goto  errLabel;
	//
	if (!mallocObj_pkt_dec_pBuf.mallocf(iAllocType, uiBufSize_pkt_dec))  goto  errLabel;
	if (mallocObj_pkt_dec_pBuf.get(&pkt_dec.memory))  goto  errLabel;
	//
	//if  (  pTask->ucbVideoConferenceStarter  )  
	{
		//  if  (  !(  pTransform->audio.pMsgTask_toCompress_videoConference  =  (  MIS_MSG_TALK  *  )mallocObj_pMsgTask_toCompress.malloc(  sizeof(  MIS_MSG_TALK  )  )  )  )  goto  errLabel;
	}

	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", _T("IsClient"), 0, _T(""), _T(""), _T("%s %d starts"), pTransformAudio->q2.cfg.name, pTransform->index_activeMems_from);

	///////////////////////////
	//  2016/12/10
		//
	//  2014/03/23	 	
	GENERIC_Q_cfgEx	qCfgEx;	//  2012/11/10
	GENERIC_Q_CFG		tmpCfg;

	TCHAR	tBuf[128];
#define		CONST_mutexNamePrefix_decA_inDataCacheQ	_T(  "decA_in"  )
#define		CONST_mutexNamePrefix_decA_tmpDataQ		_T(  "decA_tmp"  )
	//
	int		tn; tn = GetTickCount();
	int		iTaskId; iTaskId = pTransform->iTaskId;
	int		index_activeMems_from; index_activeMems_from = pTransform->index_activeMems_from;
	//
	int size; size = 0;


	//
	size = sizeof(myPLAY_AUDIO_DATA);
	pTransformAudio->pCurPkt = (myPLAY_AUDIO_DATA*)mymalloc(size);
	if (!pTransformAudio->pCurPkt)  goto  errLabel;
	memset(pTransformAudio->pCurPkt, 0, size);





	//////////////////////////

	//
	memset(&pTransformAudio->curPktInfo_toDec, 0, sizeof(pTransformAudio->curPktInfo_toDec));
	pTransformAudio->curPktInfo_toDec.pMIS_MSGU = pMsg;
	pTransformAudio->curPktInfo_toDec.pPkt_dec_myPLAY_AUDIO_DATA = &pkt_dec;
	pMsg->uiType = 0;
	pTransformAudio->curPktInfo_toDec.pkt_encA.bufSize = CONST_bufSize_tmpPktEncA;



	//
	for (; !pTransformAudio->bQuit; ) {

		if (!dwToInMs) {
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Warning: mcThreadProc_transformAudio: dwToInMs %d"), dwToInMs);
			dwToInMs = DEFAULT_dwToInMs;
		}

		//  2009/07/14
		MACRO_setStep(pTransformAudio->debugStep, CONST_threadStep_toWait);

		//
		DWORD  dwTickCnt0 = GetTickCount();
		DWORD  dwTickCnt;

		DWORD  dwEvt;
		pProcInfo->cfg.b_useAudioQ2_toDecA = true;
		if (pProcInfo->cfg.b_useAudioQ2_toDecA) {
			dwEvt = MsgWaitForMultipleObjects(
				pTransformAudio->q2.cfg.usCnt_hEvents,	//  mycountof(  pTransformAudio->hEvents  ),		// Number of events.
				pTransformAudio->q2.hEvents,						// Location of handles.
				FALSE,										// Wait for all?
				dwToInMs,									// How long to wait?
				0);										// Any message is an 
			// event.
		}
		else {
			dwEvt = MsgWaitForMultipleObjects(
				1,	//  mycountof(  pTransformAudio->hEvents  ),		// Number of events.
				&pTransformAudio->qBuf2->hEvent0,						// Location of handles.
				FALSE,										// Wait for all?
				dwToInMs,									// How long to wait?
				0);										// Any message is an 
			// event.
		}
		if (dwEvt == WAIT_FAILED)  goto  errLabel;
		//
		dwTickCnt = GetTickCount();

		if (dwEvt != WAIT_TIMEOUT) {
			dwEvt -= WAIT_OBJECT_0;
			switch (dwEvt) {
			case  0:
				dwTickCnt_lastAudioData = dwTickCnt;		//  audio data received
				break;
			case  1:
				traceLogA((char*)"transformAudio: event 1.");
				break;
			default:
				traceLogA((char*)"unknown event");
				goto  errLabel;
				break;
			}
		}


		for (; !pTransformAudio->bQuit; ) {

#if  0
			//
			MACRO_setStep(pTransformAudio->debugStep, CONST_threadStep_toGetMsg);

			//
			len = sizeof(pMsg[0]);
			{
				CQyQ2Help	q2Help;
				if (qGetMsg(q2Help.getQ_toGetMsg(&pTransformAudio->q2), pMsg, &len))  break;
			}
			memset(((char*)pMsg) + len, 0, min(256, sizeof(pMsg[0]) - len));
			switch (pMsg->uiType) {
			case  CONST_misMsgType_task:
				pContent = (IM_CONTENTU*)pMsg->task.data.buf;
				switch (pContent->uiType) {
				case  CONST_imCommType_transferAudioData:
#ifdef  __DEBUG__
					//  traceLogA(  (char*)  "transferAudioData: here"  );
#endif
					if (pContent->transferAudioData.tmpInternal.param.index_activeMems_from != pTransform->index_activeMems_from) {
						traceLogA((char*)"mcThreadProc_transformAudio: transferAudio.index_activeMems_from %d != transform.%d", pContent->transferAudioData.tmpInternal.param.index_activeMems_from, pTransform->index_activeMems_from);
						break;
					}

					//  2010/09/02
					BOOL  bNoSharedObj;  bNoSharedObj = FALSE;
					if (pTask->doProxy.bExists_avProxy)  bNoSharedObj = TRUE;

					//
					if (!bNoSharedObj) {
						pSharedObj = getSharedObjByIndex(pProcInfo, pTask->iIndex_sharedObj);
						if (pSharedObj) {
							SHARED_OBJ_USR* pSharedObjUsr = getSharedObjUsr(pSharedObj, pSharedObj->iIndex_curUsr);
							if (pSharedObjUsr) {
								if (pSharedObjUsr->iTaskId != pTransform->iTaskId) {
#ifdef  __DEBUG__
									traceLog((TCHAR*)_T("thread_transformAudio: sharedObjUsr isnt matched. skipped"));
#endif
									continue;
								}
							}
						}
					}

					//
					MACRO_setStep(pTransformAudio->debugStep, CONST_threadStep_msgGot);

					//
					transformTaskAudio(pTransform, &pMsg->task, &pContent->transferAudioData, pContent->transferAudioData.tmpInternal.param.index_pMems_from, pContent->transferAudioData.tmpInternal.param.index_activeMems_from, &pkt_dec, pMsgBuf);

					//
					MACRO_setStep(pTransformAudio->debugStep, CONST_threadStep_msgProced);

					break;
				default:
					break;
				}

				break;
			default:
				break;
			}
#endif
			//
			//
			//if  (  getNextAPktInfo_toDec(  &pTransformAudio->curPktInfo_toDec,  &pTransformAudio->q2  )  )  break;
			if (pProcInfo->cfg.b_useAudioQ2_toDecA)
			{
				if (isQ2Empty(&pTransformAudio->q2)) break;
			}
			else
			{
				if (pTransformAudio->qBuf2->is_Q2Empty()) break;
			}

			//
			if (!pTransform->audio.curPktInfo_toDec.lPktId_getNewPkt) {
				//MACRO_qyAssert(  0,  _T(  "decAudio: id_pkt is 0"  )  );
			}
			//
			long		old_pktId = pTransform->audio.curPktInfo_toDec.lPktId_getNewPkt;
			doDecodeAudio(pTransform, pMsgBuf);
			if (pTransform->audio.curPktInfo_toDec.lPktId_getNewPkt == old_pktId) {	//  如果没有处理掉就需要释放
				clean_PKT_info_toDec(&pTransform->audio.curPktInfo_toDec, _T(""));
			}




		}




	}

errLabel:

	//
	MACRO_setStep(pTransformAudio->debugStep, CONST_threadStep_toExit);

	//  2009/05/28
	exitTaskAvFrom_audio(pProcInfo, pTransform);


	//  2016/12/10
	//  2014/03/25
	clean_myPLAY_AUDIO_DATA(pTransformAudio->pCurPkt, _T("decAudio"));
	MACRO_safeFree(pTransformAudio->pCurPkt);

	//  2014/03/24
#if  0
	if (pTransformAudio->pInDataCacheQ) {
		genericQFree(pTransformAudio->pInDataCacheQ);  pTransformAudio->pInDataCacheQ = NULL;
	}
	if (pTransformAudio->pTmpDataQ) {
		genericQFree(pTransformAudio->pTmpDataQ);  pTransformAudio->pTmpDataQ = NULL;
	}
#endif



	//
	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", _T("IsClient"), 0, _T(""), _T(""), _T("%s %d ends."), pTransformAudio->q2.cfg.name, pTransform->index_activeMems_from);

	pTransformAudio->bRunning = FALSE;

	MACRO_setStep(pTransformAudio->debugStep, CONST_threadStep_end);

	traceLogA((char*)"mcThreadProc_transformAudio %S leaves", pTransformAudio->q2.cfg.name);

	return  0;
}


//

