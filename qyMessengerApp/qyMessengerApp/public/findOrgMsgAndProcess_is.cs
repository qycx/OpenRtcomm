using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

partial class Consts
{
	public const int cntof_filePath = Consts.MAX_PATH + 1;
}

namespace qy
{
	unsafe struct TMP_filePath {
		fixed char filePath[Consts.cntof_filePath];
	};

	partial class qyFuncs
{
		public static unsafe bool canSend(QY_SHARED_OBJ pSharedObj, QMC_taskData_conf pTc)
		{
			bool bRet = true;

			switch (pSharedObj.var.uiType)
			{
				case 0:
					if (pTc.ucbNotSendData)
					{
						bRet = false;
					}
					break;
				default:
					break;
			}

			return bRet;
		}


		//  int  tmpHandler_findOrgMsgAndProcess_mis_procTaskAudioData(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr,  int  iTaskId,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_AUDIO_DATA  *  pTransferAudioData,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask  )
		public static unsafe int tmpHandler_findOrgMsgAndProcess_mis_procTaskAudioData(ref CTX_caller ctxCaller, CCtxQmc pProcInfo, MSGR_ADDR* pAddr, int iTaskId, MIS_MSG_TASK* pMsgTask, TRANSFER_AUDIO_DATA* pTransferAudioData, IM_CONTENTU* pContentElem, ref PROC_TASK_AV pTask)
		{
			int iErr = -1;
			int index = 0;
			MIS_CNT pMisCnt = pProcInfo.pMisCnt;

			//
			QMC_TASK_INFO pTaskInfo = (QMC_TASK_INFO)getQmcTaskInfoByIndex(ctxCaller, pProcInfo, pTask.iIndex_taskInfo,"findOrgMsg_procTaskAudioData");
			if (null==pTaskInfo) return -1;
			QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
			if (pTaskData == null) goto errLabel;
			if (pTaskData.uiType != Consts.CONST_taskDataType_conf) return -1;
			QMC_taskData_conf pTc = (QMC_taskData_conf)pTaskData;
			DLG_TALK_videoConference videoConference = pTc.getVideoConference();


			//
			TRANSFER_AUDIO_dataMemHead* pTransferAudioData_mems = (TRANSFER_AUDIO_dataMemHead*)pTransferAudioData->buf_TRANSFER_AUDIO_dataMemHead_mems;
		
			//
			if (pTask.ucbVideoConferenceStarter)
			{
				/*
				int index_activeMems_from = 0;

				//  search in activeMems_from first
				for (index_activeMems_from = 0; index_activeMems_from < pTask.usCntLimit_activeMems_from; index_activeMems_from++)
				{
					if (pTask.activeMems_from[index_activeMems_from].idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id) break;
				}
				//  use searched index to process video
				if (index_activeMems_from < pTask.usCntLimit_activeMems_from)
				{
					index = pTask.activeMems_from[index_activeMems_from].usIndex_pMems_from;
					if (index >= 0 && index < pTask.usCntLimit_mems_from)
					{
						TASK_AV_FROM* pFrom = &pTask.pMems_from[index];
						//
						if (pFrom->idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id
							&& pFrom->audio.ta_recvd.uiTranNo_openAvDev == pTransferAudioData->uiTranNo_openAvDev)
						{
# if  __DEBUG__
							//  traceLogA(  "AudioData: usCntLimit_mems_from %d, usCntLimit_activeMems_from %d, video conference starter",  pTransferAvInfoElem->myTask.usCntLimit_mems_from,  pTransferAvInfoElem->myTask.usCntLimit_activeMems_from  );
#endif
							//  if  (  procTaskAudio(  pProcInfo,  &pMsgElem->addr_logicalPeer,  pMsgTask,  &pContent->transferAudioData,  &pTransferAvInfoElem->tranInfo,  &pTransferAvInfoElem->myTask,  index,  index_activeMems_from  )  )  goto  errLabel;

							pTransferAudioData->tmpInternal.param.index_pMems_from = index;
							pTransferAudioData->tmpInternal.param.index_activeMems_from = index_activeMems_from;

							QIS_DISPATCH* pDispatch = MACRO_getDispatch(*pTask, index_activeMems_from);
							if (pDispatch)
							{
								q2PostMsgAndTrigger(pMsgTask, offsetof(MIS_MSG_TASK, data) + pMsgTask->lenInBytes, &pDispatch->audio.q2);
							}

							iErr = 1; goto errLabel;
						}
					}
				}
				*/
			}
			else if (pTask.ucbVideoConference)
			{
				//
				if (pMsgTask->bFrom_sharedObj)
				{
					QY_SHARED_OBJ pSharedObj = getSharedObjByIndex(pProcInfo, pMsgTask->index_sharedObj);
					if (null==pSharedObj) goto errLabel;
					//
					int i;
					SHARED_OBJ_USR pSou;
					for (i = 0; i < (pSharedObj.usrs.Length); i++)
					{
						pSou = pSharedObj.usrs[i];
						if (0==pSou.iTaskId) continue;
						if (pSou.iTaskId != iTaskId) continue;

						//						
						if (pMsgTask->data.route.idInfo_from.ui64Id == pMisCnt.idInfo.ui64Id)
						{

							//  traceLog(  _T(  "audio data sent by myself"  )  );
							bool bSend = true;

							bSend = canSend(pSharedObj, pTc);

							if (bSend)
							{
								q2PostMsg((IntPtr)pMsgTask, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgTask->lenInBytes, pTask.mixer.pOutputQ2);
								MIS_CHANNEL pChannel = getChannelByType(pMisCnt, Consts.CONST_channelType_realTimeMedia);
								if (null!=pChannel)
								{

									//
									chkToApplyForChannel(pProcInfo, pChannel, Consts.CONST_channelType_realTimeMedia);

									//
									q2PostMsgAndTrigger(IntPtr.Zero, 0, pChannel.outputQ2);
								}
							}

							//							
							iErr = 1; goto errLabel;

						}

						//						
						break;
					}
				}



#if false
				if (pMsgTask->iTaskId == iTaskId)
				{
					//  2011/01/23				  
					if (pMsgTask->data.route.idInfo_from.ui64Id == pMisCnt.idInfo.ui64Id)
					{
						//  traceLog(  _T(  "audio data sent by myself"  )  );

						q2PostMsg((IntPtr)pMsgTask, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgTask->lenInBytes, pTask.mixer.pOutputQ2);
						MIS_CHANNEL pChannel = getChannelByType(pMisCnt, Consts.CONST_channelType_realTimeMedia);
						if (pChannel!=null) q2PostMsgAndTrigger(IntPtr.Zero, 0, pChannel.outputQ2);

						//
						iErr = 1; goto errLabel;
					}
				}
#endif


				//
				if (pTask.mem0_from.idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id
					&& pTask.mem0_from.audio.ta_recvd.uiTranNo_openAvDev == pTransferAudioData->uiTranNo_openAvDev)
				{
					int i = 0;
					int iPos = 0;
					TRANSFER_AUDIO_dataMemHead* pMem = null;
					int index_activeMems_from = 0;
					uint usIndex_pMems_from = 0;
					QY_TRANSFORM pTransform = null;
					MIS_MSG_TASK* pMsgTask_toTransform = null;
					TRANSFER_AUDIO_DATA* pNew = null;

					if (null==pTask.audio.pMsgU_toTransform)
					{
						traceLogA("findOrgMsg failed. pMsgU_toTransform is null");
						goto errLabel;
					}
					pMsgTask_toTransform = (MIS_MSG_TASK*)pTask.audio.pMsgU_toTransform;

					if (0==pTransferAudioData->usCnt)
					{
						pTransferAudioData->usCnt = 1;  //  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
						pTransferAudioData_mems[0].uiLen = pTransferAudioData->uiLen;
					}
					if (pTransferAudioData->usCnt > Consts.CONST_maxTransferAvDataMems) goto errLabel;

#if __DEBUG__
					//  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: audio len %d"  ),  pTransferAudioData->uiLen  );
#endif


					for (iPos = 0, i = 0; i < pTransferAudioData->usCnt; iPos = (int)(iPos + pTransferAudioData_mems[i].uiLen), i++)
					{
						pMem = &pTransferAudioData_mems[i];
						if (0==pMem->uiLen)
						{
							//
#if __DEBUG__
							//traceLogA(  "findOrgMsg: transferAudioMem.uiLen is 0. skipped."  );
#endif
							//
							continue;
						}

						if (iPos + pTransferAudioData_mems[i].uiLen > pTransferAudioData->uiLen)
						{
#if __DEBUG__
							traceLogA("findOrgMsg failed: iPos + mem.uiLen > data.uiLen");
#endif
							goto errLabel;
						}

						if (0==pMem->idInfo.ui64Id) pMem->idInfo.ui64Id = pMsgTask->data.route.idInfo_from.ui64Id;
						for (index_activeMems_from = 0; index_activeMems_from < videoConference.usCntLimit_activeMems_from; index_activeMems_from++)
						{
							if (pMem->idInfo.ui64Id == videoConference.activeMems_from[index_activeMems_from].avStream.idInfo.ui64Id
								&&  pMem->uiTranNo_openAvDev  ==videoConference.activeMems_from[index_activeMems_from].avStream.obj.tranInfo.audio.uiTranNo_openAvDev) break;
						}
						if (index_activeMems_from == videoConference.usCntLimit_activeMems_from)
						{
#if __DEBUG__
							traceLogA("findOrgMsg_procTaskAudioData: can't get index_activeMems_from, skipped.");
#endif
							qyShowInfo1(Consts.CONST_qyShowType_qwmComm, null, (""), pProcInfo.str_who_showInfo, null, _T(""), _T(""), _T("findOrgMsg: audio, can't get index_activeMems_from, skipped."));

							//  2009/06/01
							if (pTask.ucbVideoConference && !pTask.ucbVideoConferenceStarter )
							{
								//MIS_CNT* pMisCnt = (MIS_CNT*)pMsgTask->pMisCnt;
								pMisCnt.refreshVideoConferenceActiveMems.iTaskId = iTaskId;
								pMisCnt.refreshVideoConferenceActiveMems.bNeedRefreshed = true;
							}

							continue;
						}
						//
						DLG_TALK_videoConferenceActiveMemFrom pActiveMem_from = videoConference.activeMems_from[index_activeMems_from];
						//  2014/12/12

						//
						MACRO_memset_misMsgTask(pMsgTask_toTransform);
						mymemcpy((IntPtr)pMsgTask_toTransform, (IntPtr)pMsgTask, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data"));
						pMsgTask_toTransform->data.route.idInfo_from.ui64Id = videoConference.activeMems_from[index_activeMems_from].avStream.idInfo.ui64Id;
						pMsgTask_toTransform->data.route.idInfo_to.ui64Id = pMsgTask->data.route.idInfo_to.ui64Id;
						pNew = (TRANSFER_AUDIO_DATA*)pMsgTask_toTransform->data.buf;
						TRANSFER_AUDIO_dataMemHead* pNew_mems = (TRANSFER_AUDIO_dataMemHead*)pNew->buf_TRANSFER_AUDIO_dataMemHead_mems;
						mymemset((IntPtr)pNew, 0, (int)Marshal.OffsetOf<TRANSFER_AUDIO_DATA>("buf"));
						pNew->uiType = pTransferAudioData->uiType;
						pNew->uiTranNo_openAvDev = pActiveMem_from.avStream.obj.tranInfo.audio.uiTranNo_openAvDev;
						mymemcpy((IntPtr)(byte*)&pNew_mems[0], (IntPtr)pMem, (uint)sizeof(TRANSFER_AUDIO_dataMemHead)  );
					pNew->usCnt = 1;
					pNew->uiLen = pMem->uiLen;
					mymemcpy((IntPtr)pNew->buf, (IntPtr)(pTransferAudioData->buf + iPos), pNew->uiLen);

						//										
						pNew->tmpInternal.param.index_pMems_from = -1;// pTask.activeMems_from[index_activeMems_from].usIndex_pMems_from;
					pNew->tmpInternal.param.index_activeMems_from = index_activeMems_from;

					//
					pMsgTask_toTransform->lenInBytes = (uint)Marshal.OffsetOf<MIS_MSG_routeTalkData>("buf") + (uint)Marshal.OffsetOf<TRANSFER_AUDIO_DATA>("buf") + pNew->uiLen;

					pTransform = MACRO_getTransform(ref pTask, index_activeMems_from);
					if (null!=pTransform)
					{
						//  qPostMsgAndTrigger_toDo(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->video  );
						q2PostMsgAndTrigger((IntPtr)pMsgTask_toTransform, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgTask_toTransform->lenInBytes, pTransform.audio.q2);
					}
				}

				iErr = 1; goto errLabel;
			}

		}
	else  {
				//
				if (pMsgTask->bFrom_sharedObj)
				{
					QY_SHARED_OBJ pSharedObj = getSharedObjByIndex(pProcInfo, pMsgTask->index_sharedObj);
					if (null==pSharedObj) goto errLabel;
					int i;
					for (i = 0; i < pSharedObj.usrs.Length; i++)
					{
						SHARED_OBJ_USR pSou = pSharedObj.usrs[i];
						if (0==pSou.iTaskId) continue;
						if (pSou.iTaskId != iTaskId) continue;
						//
						if (pMsgTask->data.route.idInfo_from.ui64Id == pMisCnt.idInfo.ui64Id)
						{
							//  traceLog(  _T(  "audio data sent by myself"  )  );

							bool bSend = true;
							bSend = canSend(pSharedObj, pTc);

							if (bSend)
							{

								q2PostMsg((IntPtr)pMsgTask, (uint)((int)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgTask->lenInBytes), pTask.mixer.pOutputQ2);
								MIS_CHANNEL pChannel = getChannelByType(pMisCnt, Consts.CONST_channelType_realTimeMedia);
								if (null!=pChannel)
								{

									//
									chkToApplyForChannel(pProcInfo, pChannel, Consts.CONST_channelType_realTimeMedia);

									//
									q2PostMsgAndTrigger(IntPtr.Zero, 0, pChannel.outputQ2);
								}
							}
							//
							iErr = 1; goto errLabel;

						}


						break;
					}
				}





				//
#if false
				if  (pMsgTask->iTaskId  ==  iTaskId  )  {
				  //  2011/01/23				  
				  if  (pMsgTask->data.route.idInfo_from.ui64Id  ==  pMisCnt.idInfo.ui64Id  )  {
					   //  traceLog(  _T(  "audio data sent by myself"  )  );

					   q2PostMsg((IntPtr)pMsgTask, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data")  +  pMsgTask->lenInBytes, pTask.mixer.pOutputQ2  );
		MIS_CHANNEL pChannel = getChannelByType(pMisCnt, Consts.CONST_channelType_realTimeMedia);
					   if  (null!=pChannel  ) q2PostMsgAndTrigger(  IntPtr.Zero,  0,  pChannel.outputQ2  );

		//
		iErr  =  1;  goto  errLabel;				   
				  }
}
#endif

				//  2014/11/21
				if (pTask.applyForProxy.bRecvd_proxyReply)
{       //  applier for proxy
	if (pTask.applyForProxy.proxyReply.proxy.uiTranNo_openAvDev_a == pTransferAudioData->uiTranNo_openAvDev)
	{
#if __DEBUG__
		traceLog(_T("findOrgMsg: applyForProxy: my pkt is sent back. skipped"));
#endif
		iErr = 1; goto errLabel;
	}
}


//  2014/11/21
if (!pTask.receiver.bRecvd_proxiedTranInfo)
{  //  一般性的数据包处理，或者是proxy

	//  search in mems_from directly
	for (index = 0; index < videoConference.usCntLimit_activeMems_from; index++)
	{
		DLG_TALK_videoConferenceActiveMemFrom pActiveMem_from = videoConference.activeMems_from[index];

		//
		if (pActiveMem_from.avStream.idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id
			&& pActiveMem_from.avStream.obj.tranInfo.audio.uiTranNo_openAvDev == pTransferAudioData->uiTranNo_openAvDev)
		{
#if __DEBUG__
			//  traceLogA(  "AudioData: usCntLimit_mems_from %d",  pTransferAvInfoElem->myTask.usCntLimit_mems_from  ); 
#endif
			//  if  (  procTaskAudio(  pProcInfo,  &pMsgElem->addr_logicalPeer,  pMsgTask,  &pContent->transferAudioData,  &pTransferAvInfoElem->tranInfo,  &pTransferAvInfoElem->myTask,  index,  0  )  )  goto  errLabel;

			pTransferAudioData->tmpInternal.param.index_pMems_from = index;
			pTransferAudioData->tmpInternal.param.index_activeMems_from = 0;

			//  2014/11/21
			if (pTask.doProxy.bExists_avProxy)
			{

				int index_activeMems_from = 0;

				//
				QIS_DISPATCH pDispatch = MACRO_getDispatch(ref pTask, index_activeMems_from);
				if (null!=pDispatch)
				{
					q2PostMsgAndTrigger((IntPtr)pMsgTask, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgTask->lenInBytes, pDispatch.audio.q2);
				}
				iErr = 1; goto errLabel;
			}

			//
			QY_TRANSFORM pTransform = MACRO_getTransform(ref pTask, pTransferAudioData->tmpInternal.param.index_activeMems_from);
			if (null!=pTransform)
			{
				//  qPostMsgAndTrigger_toDo(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->audio  );
				q2PostMsgAndTrigger((IntPtr)pMsgTask, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgTask->lenInBytes, pTransform.audio.q2);
			}

			iErr = 1; goto errLabel;
		}
	}
	//
}
else
{  //  receiver from proxy				  			 
	if (pTask.mem0_from.idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id
		&& pTask.mem0_from.audio.ta_recvd.uiTranNo_openAvDev == pTransferAudioData->uiTranNo_openAvDev)
	{
		//  2014/11/21
		if (pTask.receiver.proxied_from.idInfo.ui64Id == pMisCnt.idInfo.ui64Id)
		{
#if __DEBUG__
			traceLog(_T("findOrgMsg: a receiver: my pkt is sent back. skipped"));
#endif
			iErr = 1; goto errLabel;
		}

		//
		int i = 0;
		int iPos = 0;
		TRANSFER_AUDIO_dataMemHead* pMem = null;
		int index_activeMems_from = 0;
		uint usIndex_pMems_from = 0;
		QY_TRANSFORM pTransform = null;
		MIS_MSG_TASK* pMsgTask_toTransform = null;
		TRANSFER_AUDIO_DATA* pNew = null;

		if (null==pTask.video.pMsgU_toTransform)
		{
			traceLogA("findOrgMsg failed. pMsgTask_toTransform is null");
			goto errLabel;
		}
		pMsgTask_toTransform = (MIS_MSG_TASK*)pTask.video.pMsgU_toTransform;

		if (0==pTransferAudioData->usCnt)
		{
			pTransferAudioData->usCnt = 1;  //  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
			pTransferAudioData_mems[0].uiLen = pTransferAudioData->uiLen;
		}
		if (pTransferAudioData->usCnt > Consts.CONST_maxTransferAvDataMems) goto errLabel;

#if __DEBUG__
		//  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video len %d"  ),  pTransferVideoData->uiLen  );
#endif


		for (iPos = 0, i = 0; i < pTransferAudioData->usCnt; iPos = (int)(iPos + pTransferAudioData_mems[i].uiLen), i++)
		{
			pMem = &pTransferAudioData_mems[i];
			if (0==pMem->uiLen)
			{
				traceLogA("findOrgMsg: transferAudioMem.uiLen is 0. skipped.");
				continue;
			}

			if (iPos + pTransferAudioData_mems[i].uiLen > pTransferAudioData->uiLen)
			{
				traceLogA("findOrgMsg failed: iPos + mem.uiLen > data.uiLen");
				goto errLabel;
			}

			//if  (  !pMem->idInfo.ui64Id  )  pMem->idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;

			//											
			usIndex_pMems_from = 1;
			TASK_AV_FROM pFrom = null;
			pFrom = getTaskAvFrom(ref pTask, (int)usIndex_pMems_from, _T(""));
			if (null==pFrom) goto errLabel;

			//
			MACRO_memset_misMsgTask(pMsgTask_toTransform);
			mymemcpy((IntPtr)pMsgTask_toTransform, (IntPtr)pMsgTask, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data"));
			pMsgTask_toTransform->data.route.idInfo_from.ui64Id = pFrom.idInfo.ui64Id;
			pMsgTask_toTransform->data.route.idInfo_to.ui64Id = pMsgTask->data.route.idInfo_to.ui64Id;
			pNew = (TRANSFER_AUDIO_DATA*)pMsgTask_toTransform->data.buf;
							TRANSFER_AUDIO_dataMemHead* pNew_mems = (TRANSFER_AUDIO_dataMemHead*)pNew->buf_TRANSFER_AUDIO_dataMemHead_mems;
			mymemset((IntPtr)pNew, 0, (int)Marshal.OffsetOf<TRANSFER_AUDIO_DATA>("buf"));
			pNew->uiType = pTransferAudioData->uiType;
			pNew->uiTranNo_openAvDev = pFrom.audio.ta_recvd.uiTranNo_openAvDev;
			mymemcpy((IntPtr)(byte*)&pNew_mems[0], (IntPtr)pMem, (uint)sizeof(TRANSFER_AUDIO_dataMemHead)  );
		pNew->usCnt = 1;
		pNew->uiLen = pMem->uiLen;
		mymemcpy((IntPtr)pNew->buf, (IntPtr)(pTransferAudioData->buf + iPos), pNew->uiLen);

		//										
		pNew->tmpInternal.param.index_pMems_from = (int)usIndex_pMems_from;
		pNew->tmpInternal.param.index_activeMems_from = index_activeMems_from;

		//
		pMsgTask_toTransform->lenInBytes = (uint)Marshal.OffsetOf<MIS_MSG_routeTalkData>("buf") + (uint)Marshal.OffsetOf<TRANSFER_AUDIO_DATA>("buf") + pNew->uiLen;

		pTransform = MACRO_getTransform(ref pTask, index_activeMems_from);
		if (null!=pTransform)
		{
			//  
			q2PostMsgAndTrigger((IntPtr)pMsgTask_toTransform, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgTask_toTransform->lenInBytes, pTransform.audio.q2);
		}

		//  2014/11/11
		continue;

	}

	iErr = 1; goto errLabel;
}

//
iErr = 0; goto errLabel;		  
		}
	}

	

	iErr = 0;
errLabel:
return iErr;
											 
}

		//
		public static unsafe int tmpHandler_findOrgMsgAndProcess_mis_procInputAudioData( CTX_caller ctxCaller,CCtxQmc pProcInfo, MSGR_ADDR* pAddr, int iTaskId, MIS_MSG_INPUT* pMsgInput, TRANSFER_AUDIO_DATA* pTransferAudioData, IM_CONTENTU* pContentElem, ref PROC_TASK_AV pTask)
		{
			int iErr = -1;
			int index = 0;
			MIS_CNT pMisCnt = pProcInfo.pMisCnt;
			//
			bool bDbg = true;
			string str;

			//
			QMC_TASK_INFO pTaskInfo = (QMC_TASK_INFO)getQmcTaskInfoByIndex(ctxCaller,pProcInfo, pTask.iIndex_taskInfo,"findOrgMsg_procInputAudioData");
			if (null == pTaskInfo) return -1;
			QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
			if (pTaskData == null) return -1;
			if (pTaskData.uiType != Consts.CONST_taskDataType_conf) return -1;
			QMC_taskData_conf pTc = (QMC_taskData_conf)pTaskData;
			DLG_TALK_videoConference videoConference = pTc.getVideoConference();

			//
#if DEBUG
			chkTc(pTc,"find_procInputAudioData enters");
#endif

			//
			TRANSFER_AUDIO_dataMemHead* pTransferAudioData_mems = (TRANSFER_AUDIO_dataMemHead*)pTransferAudioData->buf_TRANSFER_AUDIO_dataMemHead_mems;
			int bufSize = Consts.bufSize_TRANSFER_AUDIO_dataMemHead_mems;

			//
			if (pTask.ucbVideoConferenceStarter)
			{
				/*
				int index_activeMems_from = 0;

				//  search in activeMems_from first
				for (index_activeMems_from = 0; index_activeMems_from < pTask.usCntLimit_activeMems_from; index_activeMems_from++)
				{
					if (pTask.activeMems_from[index_activeMems_from].idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id) break;
				}
				//  use searched index to process video
				if (index_activeMems_from < pTask.usCntLimit_activeMems_from)
				{
					index = pTask.activeMems_from[index_activeMems_from].usIndex_pMems_from;
					if (index >= 0 && index < pTask.usCntLimit_mems_from)
					{
						TASK_AV_FROM* pFrom = &pTask.pMems_from[index];
						//
						if (pFrom->idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id
							&& pFrom->audio.ta_recvd.uiTranNo_openAvDev == pTransferAudioData->uiTranNo_openAvDev)
						{
#if __DEBUG__
							//  traceLogA(  "AudioData: usCntLimit_mems_from %d, usCntLimit_activeMems_from %d, video conference starter",  pTransferAvInfoElem->myTask.usCntLimit_mems_from,  pTransferAvInfoElem->myTask.usCntLimit_activeMems_from  );
#endif
							//  if  (  procTaskAudio(  pProcInfo,  &pMsgElem->addr_logicalPeer,  pMsgTask,  &pContent->transferAudioData,  &pTransferAvInfoElem->tranInfo,  &pTransferAvInfoElem->myTask,  index,  index_activeMems_from  )  )  goto  errLabel;

							pTransferAudioData->tmpInternal.param.index_pMems_from = index;
							pTransferAudioData->tmpInternal.param.index_activeMems_from = index_activeMems_from;

							QIS_DISPATCH* pDispatch = MACRO_getDispatch(*pTask, index_activeMems_from);
							if (pDispatch)
							{
								q2PostMsgAndTrigger(pMsgTask, offsetof(MIS_MSG_TASK, data) + pMsgTask->lenInBytes, &pDispatch->audio.q2);
							}

							iErr = 1; goto errLabel;
						}
					}
				}
				*/
			}
			else if (pTask.ucbVideoConference)
			{

				if (pMsgInput->iTaskId == iTaskId)
				{
					//  2011/01/23				  
					if (pMsgInput->data.route.idInfo_from.ui64Id == pMisCnt.idInfo.ui64Id)
					{
						//  traceLog(  _T(  "audio data sent by myself"  )  );

						q2PostMsg((IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + pMsgInput->lenInBytes, pTask.mixer.pOutputQ2);
						MIS_CHANNEL pChannel = getChannelByType(pMisCnt, Consts.CONST_channelType_realTimeMedia);
						if (pChannel != null) q2PostMsgAndTrigger(IntPtr.Zero, 0, pChannel.outputQ2);

						//
						iErr = 1; goto errLabel;
					}
				}

				if (pTask.mem0_from.idInfo.ui64Id == pMsgInput->data.route.idInfo_from.ui64Id
					&& pTask.mem0_from.audio.ta_recvd.uiTranNo_openAvDev == pTransferAudioData->uiTranNo_openAvDev)
				{
					int i = 0;
					int iPos = 0;
					TRANSFER_AUDIO_dataMemHead* pMem = null;
					int index_activeMems_from = 0;
					uint usIndex_pMems_from = 0;
					QY_TRANSFORM pTransform = null;
					MIS_MSG_INPUT* pMsgInput_toTransform = null;
					TRANSFER_AUDIO_DATA* pNew = null;

					if (null == pTask.audio.pMsgU_toTransform)
					{
						traceLogA("findOrgMsg failed. pMsgTask_toTransform is null");
						goto errLabel;
					}
					pMsgInput_toTransform = (MIS_MSG_INPUT*)pTask.audio.pMsgU_toTransform;

					if (0 == pTransferAudioData->usCnt)
					{
						pTransferAudioData->usCnt = 1;  //  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
						pTransferAudioData_mems[0].uiLen = pTransferAudioData->uiLen;
					}
					if (pTransferAudioData->usCnt > Consts.CONST_maxTransferAvDataMems) goto errLabel;

#if __DEBUG__
					//  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: audio len %d"  ),  pTransferAudioData->uiLen  );
#endif


					for (iPos = 0, i = 0; i < pTransferAudioData->usCnt; iPos = (int)(iPos + pMem->uiLen), i++)
					{
						pMem = getMem(pTransferAudioData_mems, bufSize, i);// &pTransferAudioData_mems[i];
						if (0 == pMem->uiLen)
						{
							//
#if __DEBUG__
							//traceLogA(  "findOrgMsg: transferAudioMem.uiLen is 0. skipped."  );
#endif
							//
							continue;
						}

						if (iPos + pMem->uiLen > pTransferAudioData->uiLen)
						{
#if __DEBUG__
							traceLogA("findOrgMsg failed: iPos + mem.uiLen > data.uiLen");
#endif
							goto errLabel;
						}

						if (0 == pMem->idInfo.ui64Id) pMem->idInfo.ui64Id = pMsgInput->data.route.idInfo_from.ui64Id;
						for (index_activeMems_from = 0; index_activeMems_from < videoConference.usCntLimit_activeMems_from; index_activeMems_from++)
						{
							if (pMem->idInfo.ui64Id == videoConference.activeMems_from[index_activeMems_from].avStream.idInfo.ui64Id
								&& pMem->uiTranNo_openAvDev == videoConference.activeMems_from[index_activeMems_from].avStream.obj.tranInfo.audio.uiTranNo_openAvDev)
							{
								break;
							}
						}
						if (index_activeMems_from == videoConference.usCntLimit_activeMems_from)
						{
#if __DEBUG__
							traceLogA("findOrgMsg_procTaskAudioData: can't get index_activeMems_from, skipped.");
#endif
							qyShowInfo1(Consts.CONST_qyShowType_qwmComm, null, (""), pProcInfo.str_who_showInfo, null, _T(""), _T(""), _T("findOrgMsg: audio, can't get index_activeMems_from, skipped."));

							//
							iErr = Consts.CONST_qyRet_cantGet_index_activeMems_from; goto errLabel;

#if false
							//  2009/06/01
							if (pTask.ucbVideoConference && !pTask.ucbVideoConferenceStarter)
							{
								//MIS_CNT* pMisCnt = (MIS_CNT*)pMsgTask->pMisCnt;
								pMisCnt.refreshVideoConferenceActiveMems.iTaskId = iTaskId;
								pMisCnt.refreshVideoConferenceActiveMems.bNeedRefreshed = true;
							}

							continue;
#endif
						}
						DLG_TALK_videoConferenceActiveMemFrom pActiveMem_from = videoConference.activeMems_from[index_activeMems_from];



						//
						MACRO_memset_misMsgInput(pMsgInput_toTransform);
						mymemcpy((IntPtr)pMsgInput_toTransform, (IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data"));
						pMsgInput_toTransform->data.route.idInfo_from.ui64Id = videoConference.activeMems_from[index_activeMems_from].avStream.idInfo.ui64Id;
						pMsgInput_toTransform->data.route.idInfo_to.ui64Id = pMsgInput->data.route.idInfo_to.ui64Id;
						pNew = (TRANSFER_AUDIO_DATA*)pMsgInput_toTransform->data.buf;
						TRANSFER_AUDIO_dataMemHead* pNew_mems = (TRANSFER_AUDIO_dataMemHead*)pNew->buf_TRANSFER_AUDIO_dataMemHead_mems;
						mymemset((IntPtr)pNew, 0, (int)Marshal.OffsetOf<TRANSFER_AUDIO_DATA>("buf"));
						pNew->uiType = pTransferAudioData->uiType;
						pNew->uiTranNo_openAvDev = pActiveMem_from.avStream.obj.tranInfo.audio.uiTranNo_openAvDev;
						mymemcpy((IntPtr)(byte*)&pNew_mems[0], (IntPtr)pMem, (uint)sizeof(TRANSFER_AUDIO_dataMemHead));
						pNew->usCnt = 1;
						pNew->uiLen = pMem->uiLen;
						mymemcpy((IntPtr)pNew->buf, (IntPtr)(pTransferAudioData->buf + iPos), pNew->uiLen);

						//										
						pNew->tmpInternal.param.index_pMems_from = -1;// pTask.activeMems_from[index_activeMems_from].usIndex_pMems_from;
						pNew->tmpInternal.param.index_activeMems_from = index_activeMems_from;

						//
						pMsgInput_toTransform->lenInBytes = (uint)Marshal.OffsetOf<MIS_MSG_routeTalkData>("buf") + (uint)Marshal.OffsetOf<TRANSFER_AUDIO_DATA>("buf") + pNew->uiLen;

						pTransform = MACRO_getTransform(ref pTask, index_activeMems_from);
						if (null != pTransform)
						{
							//  qPostMsgAndTrigger_toDo(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->video  );
							q2PostMsgAndTrigger((IntPtr)pMsgInput_toTransform, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + pMsgInput_toTransform->lenInBytes, pTransform.audio.q2);
						}
					}

					iErr = 1; goto errLabel;
				}

			}
			else
			{

				if (pMsgInput->iTaskId == iTaskId)
				{
					//  2011/01/23				  
					if (pMsgInput->data.route.idInfo_from.ui64Id == pMisCnt.idInfo.ui64Id)
					{
						//  traceLog(  _T(  "audio data sent by myself"  )  );

						q2PostMsg((IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + pMsgInput->lenInBytes, pTask.mixer.pOutputQ2);
						MIS_CHANNEL pChannel = getChannelByType(pMisCnt, Consts.CONST_channelType_realTimeMedia);
						if (null != pChannel) q2PostMsgAndTrigger(IntPtr.Zero, 0, pChannel.outputQ2);

						//
						iErr = 1; goto errLabel;
					}
				}

				//  2014/11/21
				if (pTask.applyForProxy.bRecvd_proxyReply)
				{       //  applier for proxy
					if (pTask.applyForProxy.proxyReply.proxy.uiTranNo_openAvDev_a == pTransferAudioData->uiTranNo_openAvDev)
					{
#if __DEBUG__
		traceLog(_T("findOrgMsg: applyForProxy: my pkt is sent back. skipped"));
#endif
						iErr = 1; goto errLabel;
					}
				}


				//  2014/11/21
				if (!pTask.receiver.bRecvd_proxiedTranInfo)
				{  //  一般性的数据包处理，或者是proxy

					//  search in mems_from directly
					for (index = 0; index < videoConference.usCntLimit_activeMems_from; index++)
					{
						DLG_TALK_videoConferenceActiveMemFrom pActiveMem_from =  videoConference.activeMems_from[index];

						//
						if (pActiveMem_from.avStream.idInfo.ui64Id == pMsgInput->data.route.idInfo_from.ui64Id
							&& pActiveMem_from.avStream.obj.tranInfo.audio.uiTranNo_openAvDev == pTransferAudioData->uiTranNo_openAvDev)
						{
#if DEBUG
							/*
							//  traceLogA(  "AudioData: usCntLimit_mems_from %d",  pTransferAvInfoElem->myTask.usCntLimit_mems_from  ); 
							int ii;
							if(pTransferAudioData->usCnt==0)
                            {
								traceLog("transAudioData.usCnt is 0");
                            }

							for (ii = 0;ii< pTransferAudioData->usCnt;ii++)
                            {
								str = string.Format("findOrg: audio.mems[{0}], pts {1}", ii, pTransferAudioData_mems[ii].uiPts); 
								traceLog(str);

                            }
							*/
#endif
							//  if  (  procTaskAudio(  pProcInfo,  &pMsgElem->addr_logicalPeer,  pMsgTask,  &pContent->transferAudioData,  &pTransferAvInfoElem->tranInfo,  &pTransferAvInfoElem->myTask,  index,  0  )  )  goto  errLabel;

							pTransferAudioData->tmpInternal.param.index_pMems_from = -1;
							pTransferAudioData->tmpInternal.param.index_activeMems_from = index;

							//  2014/11/21
							if (pTask.doProxy.bExists_avProxy)
							{

								int index_activeMems_from = 0;

								//
								QIS_DISPATCH pDispatch = MACRO_getDispatch(ref pTask, index_activeMems_from);
								if (null != pDispatch)
								{
									q2PostMsgAndTrigger((IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + pMsgInput->lenInBytes, pDispatch.audio.q2);
								}
								iErr = 1; goto errLabel;
							}

							//
							QY_TRANSFORM pTransform = MACRO_getTransform(ref pTask, pTransferAudioData->tmpInternal.param.index_activeMems_from);
							if (null != pTransform)
							{
								//  qPostMsgAndTrigger_toDo(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  &pTransform->audio  );
								q2PostMsgAndTrigger((IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + pMsgInput->lenInBytes, pTransform.audio.q2);
							}

							iErr = 1; goto errLabel;
						}
					}
					//
				}
				else
				{  //  receiver from proxy				  			 
					if (pTask.mem0_from.idInfo.ui64Id == pMsgInput->data.route.idInfo_from.ui64Id
						&& pTask.mem0_from.audio.ta_recvd.uiTranNo_openAvDev == pTransferAudioData->uiTranNo_openAvDev)
					{
						//  2014/11/21
						if (pTask.receiver.proxied_from.idInfo.ui64Id == pMisCnt.idInfo.ui64Id)
						{
#if __DEBUG__
			traceLog(_T("findOrgMsg: a receiver: my pkt is sent back. skipped"));
#endif
							iErr = 1; goto errLabel;
						}

						//
						int i = 0;
						int iPos = 0;
						TRANSFER_AUDIO_dataMemHead* pMem = null;
						int index_activeMems_from = 0;
						uint usIndex_pMems_from = 0;
						QY_TRANSFORM pTransform = null;
						MIS_MSG_INPUT* pMsgInput_toTransform = null;
						TRANSFER_AUDIO_DATA* pNew = null;

						if (null == pTask.video.pMsgU_toTransform)
						{
							traceLogA("findOrgMsg failed. pMsgTask_toTransform is null");
							goto errLabel;
						}
						pMsgInput_toTransform = (MIS_MSG_INPUT*)pTask.video.pMsgU_toTransform;

						if (0 == pTransferAudioData->usCnt)
						{
							pTransferAudioData->usCnt = 1;  //  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
							pTransferAudioData_mems[0].uiLen = pTransferAudioData->uiLen;
						}
						if (pTransferAudioData->usCnt > Consts.CONST_maxTransferAvDataMems) goto errLabel;

#if __DEBUG__
		//  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video len %d"  ),  pTransferVideoData->uiLen  );
#endif


						for (iPos = 0, i = 0; i < pTransferAudioData->usCnt; iPos = (int)(iPos + pTransferAudioData_mems[i].uiLen), i++)
						{
							pMem = &pTransferAudioData_mems[i];
							if (0 == pMem->uiLen)
							{
								traceLogA("findOrgMsg: transferAudioMem.uiLen is 0. skipped.");
								continue;
							}

							if (iPos + pTransferAudioData_mems[i].uiLen > pTransferAudioData->uiLen)
							{
								traceLogA("findOrgMsg failed: iPos + mem.uiLen > data.uiLen");
								goto errLabel;
							}

							//if  (  !pMem->idInfo.ui64Id  )  pMem->idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;
#if DEBUG
							str = string.Format("audioData.mems[{0}] pts {1}", i, pMem->uiPts);
							traceLog(str);
#endif

							//											
							usIndex_pMems_from = 1;
							TASK_AV_FROM pFrom = null;
							pFrom = getTaskAvFrom(ref pTask, (int)usIndex_pMems_from, _T(""));
							if (null == pFrom) goto errLabel;

							//
							MACRO_memset_misMsgInput(pMsgInput_toTransform);
							mymemcpy((IntPtr)pMsgInput_toTransform, (IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data"));
							pMsgInput_toTransform->data.route.idInfo_from.ui64Id = pFrom.idInfo.ui64Id;
							pMsgInput_toTransform->data.route.idInfo_to.ui64Id = pMsgInput->data.route.idInfo_to.ui64Id;
							pNew = (TRANSFER_AUDIO_DATA*)pMsgInput_toTransform->data.buf;
							TRANSFER_AUDIO_dataMemHead* pNew_mems = (TRANSFER_AUDIO_dataMemHead*)pNew->buf_TRANSFER_AUDIO_dataMemHead_mems;
							mymemset((IntPtr)pNew, 0, (int)Marshal.OffsetOf<TRANSFER_AUDIO_DATA>("buf"));
							pNew->uiType = pTransferAudioData->uiType;
							pNew->uiTranNo_openAvDev = pFrom.audio.ta_recvd.uiTranNo_openAvDev;
							mymemcpy((IntPtr)(byte*)&pNew_mems[0], (IntPtr)pMem, (uint)sizeof(TRANSFER_AUDIO_dataMemHead));
							pNew->usCnt = 1;
							pNew->uiLen = pMem->uiLen;
							mymemcpy((IntPtr)pNew->buf, (IntPtr)(pTransferAudioData->buf + iPos), pNew->uiLen);

							//										
							pNew->tmpInternal.param.index_pMems_from = (int)usIndex_pMems_from;
							pNew->tmpInternal.param.index_activeMems_from = index_activeMems_from;

							//
							pMsgInput_toTransform->lenInBytes = (uint)Marshal.OffsetOf<MIS_MSG_routeTalkData>("buf") + (uint)Marshal.OffsetOf<TRANSFER_AUDIO_DATA>("buf") + pNew->uiLen;

							pTransform = MACRO_getTransform(ref pTask, index_activeMems_from);
							if (null != pTransform)
							{
								//  
								q2PostMsgAndTrigger((IntPtr)pMsgInput_toTransform, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + pMsgInput_toTransform->lenInBytes, pTransform.audio.q2);
							}

							//  2014/11/11
							continue;

						}

						iErr = 1; goto errLabel;
					}

					//
					iErr = 0; goto errLabel;
				}
			}



			iErr = 0;
		errLabel:

#if DEBUG
			chkTc(pTc, "find_procInputAudioData leaves");
#endif

			return iErr;

		}


		//
		public static unsafe int tmpHandler_findOrgMsgAndProcess_mis_procTaskVideoData(ref CTX_caller ctxCaller,CCtxQmc pProcInfo, MSGR_ADDR* pAddr, int iTaskId, MIS_MSG_TASK* pMsgTask, TRANSFER_VIDEO_DATA* pTransferVideoData, IM_CONTENTU* pContentElem, ref PROC_TASK_AV pTask)
{
	int iErr = -1;
	int index = 0;
	MIS_CNT pMisCnt = pProcInfo.pMisCnt;



			TRANSFER_VIDEO_dataMemHead* pTransferVideoDataMems = (TRANSFER_VIDEO_dataMemHead*)pTransferVideoData->buf_TRANSFER_VIDEO_dataMemHead_mems;
			TRANSFER_VIDEO_dataMemHead* pNewMems = null;
			//
			bool bDbg = false;
			string str;

			//
			QMC_TASK_INFO pTaskInfo = (QMC_TASK_INFO)getQmcTaskInfoByIndex(ctxCaller,pProcInfo, pTask.iIndex_taskInfo,"findOrgMsg_procTaskVideoData");
			if (null == pTaskInfo) return -1;
			QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
			if (pTaskData == null) return -1;
			if (pTaskData.uiType != Consts.CONST_taskDataType_conf) return -1;
			QMC_taskData_conf pTc = (QMC_taskData_conf)pTaskData;
			DLG_TALK_videoConference videoConference = pTc.getVideoConference();

			//
			if (pTask.ucbVideoConferenceStarter)
	{
				/*

		if (pContentElem->uiType != CONST_imCommType_transferAvInfo)
		{
#if __DEBUG__
			traceLog(_T("procTaskVideoData failed, contentType err"));
#endif
			goto errLabel;
		}

		//  2014/11/11
		if (pMsgTask->iTaskId == iTaskId)
		{
			if (pMsgTask->data.route.idInfo_from.ui64Id == pMisCnt.idInfo.ui64Id)
			{
				if (pTransferVideoData->uiTranNo_openAvDev == pContentElem->transferAvInfo.confMosaicTranInfo_video.video.uiTranNo_openAvDev
					|| pTransferVideoData->uiTranNo_openAvDev == pContentElem->transferAvInfo.confMosaicTranInfo_resource.video.uiTranNo_openAvDev)
				{
					//
					dispatch_outputConfVideo(pTask, pMsgTask, pTransferVideoData, &pMisCnt.idInfo, pTransferVideoData->uiTranNo_openAvDev);
					//			
					iErr = 1; goto errLabel;
				}
			}
		}

		//
		int index_activeMems_from = 0;

		//  search in activeMems_from first
		for (index_activeMems_from = 0; index_activeMems_from < pTask.usCntLimit_activeMems_from; index_activeMems_from++)
		{
			if (pTask.activeMems_from[index_activeMems_from].idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id) break;
		}
		//  use searched index to process video
		if (index_activeMems_from < pTask.usCntLimit_activeMems_from)
		{
			index = pTask.activeMems_from[index_activeMems_from].usIndex_pMems_from;
			if (index >= 0 && index < pTask.usCntLimit_mems_from)
			{
				TASK_AV_FROM* pFrom = &pTask.pMems_from[index];
				//
				if (pFrom->idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id
					&& pFrom->video.tv_recvd.uiTranNo_openAvDev == pTransferVideoData->uiTranNo_openAvDev)
				{
# ifdef  __DEBUG__		
					//  traceLogA(  "VideoData: usCntLimit_mems_from %d, usCntLimit_activeMems_from %d, video conference starter",  pTransferAvInfoElem->myTask.usCntLimit_mems_from,  pTransferAvInfoElem->myTask.usCntLimit_activeMems_from  );
#endif

				//
				pTransferVideoData->tmpInternal.param.index_pMems_from = index;
					pTransferVideoData->tmpInternal.param.index_activeMems_from = index_activeMems_from;

					//
					QIS_DISPATCH* pDispatch = MACRO_getDispatch(*pTask, index_activeMems_from);
					if (pDispatch)
					{
						q2PostMsgAndTrigger(pMsgTask, offsetof(MIS_MSG_TASK, data) + pMsgTask->lenInBytes, &pDispatch->video.q2);
					}

					iErr = 1; goto errLabel;
				}
			}
		}
				*/
	}
	else if (pTask.ucbVideoConference)
	{
				//
				//
				if (pMsgTask->bFrom_sharedObj)
				{
					QY_SHARED_OBJ pSharedObj = getSharedObjByIndex(pProcInfo, pMsgTask->index_sharedObj);
					if (null==pSharedObj) goto errLabel;
					int i;
					for (i = 0; i < (pSharedObj.usrs.Length); i++)
					{
						SHARED_OBJ_USR pSou = pSharedObj.usrs[i];
						if (0==pSou.iTaskId) continue;
						if (pSou.iTaskId != iTaskId) continue;

						//					   
						if (pMsgTask->data.route.idInfo_from.ui64Id == pMisCnt.idInfo.ui64Id)
						{
							//  traceLog(  _T(  "video data sent by myself"  )  );

							bool bSend = true;
							//
							bSend = canSend(pSharedObj, pTc);

							if (bSend)
							{
								q2PostMsg((IntPtr)pMsgTask, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgTask->lenInBytes, pTask.photomosaic.pOutputQ2);
								MIS_CHANNEL pChannel = getChannelByType(pMisCnt, Consts.CONST_channelType_media);
								if (null!=pChannel)
								{

									//
									chkToApplyForChannel(pProcInfo, pChannel, Consts.CONST_channelType_media);

									//
									q2PostMsgAndTrigger(IntPtr.Zero, 0, pChannel.outputQ2);
								}
							}

							//
							iErr = 1; goto errLabel;

						}

						//
						break;
					}
				}



				//
#if false
				if (pMsgTask->iTaskId == iTaskId)
		{
			//  2011/01/23				  
			if (pMsgTask->data.route.idInfo_from.ui64Id == pMisCnt.idInfo.ui64Id)
			{
				//  traceLog(  _T(  "video data sent by myself"  )  );

				q2PostMsg((IntPtr)pMsgTask, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgTask->lenInBytes, pTask.photomosaic.pOutputQ2);
				MIS_CHANNEL pChannel = getChannelByType(pMisCnt, Consts.CONST_channelType_media);
				if (null!=pChannel) q2PostMsgAndTrigger(IntPtr.Zero, 0, pChannel.outputQ2);

				//
				iErr = 1; goto errLabel;
			}
		}
#endif

				//
				if (pTask.mem0_from.idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id
			&& pTask.mem0_from.video.tv_recvd.uiTranNo_openAvDev == pTransferVideoData->uiTranNo_openAvDev)
		{
			int i = 0;
			int iPos = 0;
			TRANSFER_VIDEO_dataMemHead* pMem = null;
			int index_activeMems_from = 0;
			uint usIndex_pMems_from = 0;
			QY_TRANSFORM pTransform = null;
			MIS_MSG_TASK* pMsgTask_toTransform = null;
			TRANSFER_VIDEO_DATA* pNew = null;

			if (null==pTask.video.pMsgU_toTransform)
			{
#if __DEBUG__
				traceLogA("findOrgMsg failed. pMsgTask_toTransform is null");
#endif
				goto errLabel;
			}
			pMsgTask_toTransform = (MIS_MSG_TASK*)pTask.video.pMsgU_toTransform;

			if (0==pTransferVideoData->usCnt)
			{
				pTransferVideoData->usCnt = 1;  //  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
				pTransferVideoDataMems[0].uiLen = pTransferVideoData->uiLen;
			}
			if (pTransferVideoData->usCnt > Consts.CONST_maxTransferAvDataMems) goto errLabel;

#if __DEBUG__
			//  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video len %d"  ),  pTransferVideoData->uiLen  );
#endif


			for (iPos = 0, i = 0; i < pTransferVideoData->usCnt; iPos = (int)(iPos + pTransferVideoDataMems[i].uiLen), i++)
			{
				pMem = &pTransferVideoDataMems[i];
				if (0==pMem->uiLen)
				{
					//
#if __DEBUG__
					//traceLogA(  "findOrgMsg: transferVideoMem.uiLen is 0. skipped."  );
#endif
					//
					continue;
				}

				if (iPos + pTransferVideoDataMems[i].uiLen > pTransferVideoData->uiLen)
				{
#if __DEBUG__
					traceLogA("findOrgMsg failed: iPos + mem.uiLen > data.uiLen");
#endif
					goto errLabel;
				}

				if (0==pMem->idInfo.ui64Id) pMem->idInfo.ui64Id = pMsgTask->data.route.idInfo_from.ui64Id;
				//
				
						//
						for (index_activeMems_from = 0; index_activeMems_from < videoConference.usCntLimit_activeMems_from; index_activeMems_from++)
{
	if (pMem->idInfo.ui64Id == videoConference.activeMems_from[index_activeMems_from].avStream.idInfo.ui64Id
								&&  pMem->uiTranNo_openAvDev==videoConference.activeMems_from[index_activeMems_from].avStream.obj.tranInfo.video.uiTranNo_openAvDev) break;
}
if (index_activeMems_from == videoConference.usCntLimit_activeMems_from)
{
#if __DEBUG__
	traceLogA("findOrgMsg_procTaskVideoData: can't get index_activeMems_from, skipped.");
#endif
	//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("findOrgMsg: video, can't get index_activeMems_from, skipped."));

	//  2009/06/01
	if (pTask.ucbVideoConference && !pTask.ucbVideoConferenceStarter )
	{
		//MIS_CNT* pMisCnt = (MIS_CNT*)pMsgTask->pMisCnt;
		pMisCnt.refreshVideoConferenceActiveMems.iTaskId = iTaskId;
		pMisCnt.refreshVideoConferenceActiveMems.bNeedRefreshed = true;
	}

	continue;
}

						//
						DLG_TALK_videoConferenceActiveMemFrom pActiveMem_from = videoConference.activeMems_from[index_activeMems_from];

	


//
MACRO_memset_misMsgTask(pMsgTask_toTransform);
mymemcpy((IntPtr)pMsgTask_toTransform, (IntPtr)pMsgTask, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data"));
pMsgTask_toTransform->data.route.idInfo_from.ui64Id = videoConference.activeMems_from[index_activeMems_from].avStream.idInfo.ui64Id;
pMsgTask_toTransform->data.route.idInfo_to.ui64Id = pMsgTask->data.route.idInfo_to.ui64Id;
pNew = (TRANSFER_VIDEO_DATA*)pMsgTask_toTransform->data.buf;
mymemset((IntPtr)pNew, 0, (int)Marshal.OffsetOf<TRANSFER_VIDEO_DATA>("buf"));
pNew->uiType = pTransferVideoData->uiType;
pNew->uiTranNo_openAvDev = pActiveMem_from.avStream.obj.tranInfo.video.uiTranNo_openAvDev;
						 pNewMems = (TRANSFER_VIDEO_dataMemHead*)pNew->buf_TRANSFER_VIDEO_dataMemHead_mems;
mymemcpy((IntPtr)(byte*)&pNewMems[0], (IntPtr)pMem, (uint)sizeof(TRANSFER_VIDEO_dataMemHead)  );
pNew->usCnt = 1;
pNew->uiLen = pMem->uiLen;
mymemcpy((IntPtr)pNew->buf, (IntPtr)(pTransferVideoData->buf + iPos), pNew->uiLen);

						//  2017/09/05

						//										
						pNew->tmpInternal.param.index_pMems_from = -1;// pTask.activeMems_from[index_activeMems_from].usIndex_pMems_from;
pNew->tmpInternal.param.index_activeMems_from = index_activeMems_from;

//
pMsgTask_toTransform->lenInBytes = (uint)Marshal.OffsetOf<MIS_MSG_routeTalkData>("buf") + (uint)Marshal.OffsetOf<TRANSFER_VIDEO_DATA>("buf") + pNew->uiLen;

pTransform = MACRO_getTransform(ref pTask, index_activeMems_from);
if (pTransform!=null)
{
	//  
	q2PostMsgAndTrigger((IntPtr)pMsgTask_toTransform, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgTask_toTransform->lenInBytes, pTransform.v_preTransThread.q2);
}

//  2014/11/11
continue;
				   }

				   iErr = 1; goto errLabel;
			  }
		      }	//  end of processing confMem
	else
{  //
   // 
				if (pMsgTask->bFrom_sharedObj)
				{
					QY_SHARED_OBJ pSharedObj = getSharedObjByIndex(pProcInfo, pMsgTask->index_sharedObj);
					if (null==pSharedObj) goto errLabel;
					int i;
					for (i = 0; i < pSharedObj.usrs.Length; i++)
					{
						SHARED_OBJ_USR pSou = pSharedObj.usrs[i];
						if (0==pSou.iTaskId) continue;
						if (pSou.iTaskId != iTaskId) continue;

						if (pMsgTask->data.route.idInfo_from.ui64Id == pMisCnt.idInfo.ui64Id)
						{
							//  traceLog(  _T(  "video data sent by myself"  )  );				  

							bool bSend = false;
							bSend = canSend(pSharedObj, pTc);

							if (bSend)
							{
								if (isEmpty_ROUTE_sendLocalAv(ref pTaskInfo.var.curRoute_sendLocalAv)) bSend = false;
							}

							if (bSend)
							{

								//
								q2PostMsg((IntPtr)pMsgTask, (uint)(Marshal.OffsetOf<MIS_MSG_TASK>("data")) + pMsgTask->lenInBytes, pTask.photomosaic.pOutputQ2);
								MIS_CHANNEL pChannel = getChannelByType(pMisCnt, Consts.CONST_channelType_media);
								if (null!=pChannel)
								{

									//
									chkToApplyForChannel(pProcInfo, pChannel, Consts.CONST_channelType_media);

									//
									q2PostMsgAndTrigger(IntPtr.Zero, 0, pChannel.outputQ2);
								}


							}

							//				  
							iErr = 1; goto errLabel;
						}


						break;
					}

				}


#if false
				if (pMsgTask->iTaskId == iTaskId)
	{
		//  2011/01/23				  
		if (pMsgTask->data.route.idInfo_from.ui64Id == pMisCnt.idInfo.ui64Id)
		{
						//  traceLog(  _T(  "video data sent by myself"  )  );
						if (bDbg)
						{
							int nQNodes = getQ2Nodes(pTask.photomosaic.pOutputQ2);
							str = string.Format("tmp_find_procTaskVideo: to send video data, task.outputQ2.nQNodes {0} ", nQNodes);
							traceLog(str);
						}

			//
			q2PostMsg((IntPtr)pMsgTask, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgTask->lenInBytes, pTask.photomosaic.pOutputQ2);
			MIS_CHANNEL pChannel = getChannelByType(pMisCnt, Consts.CONST_channelType_media);
						if (pChannel != null)
						{
							//q2PostMsgAndTrigger(IntPtr.Zero, 0, pChannel.outputQ2);
							q2PostMsgAndTrigger(IntPtr.Zero, 0, pChannel.toSendQ2);
						}

			//
			iErr = 1; goto errLabel;
		}
	}
#endif

				//  2014/11/21
				if (pTask.applyForProxy.bRecvd_proxyReply)
	{       //  applier for proxy
		if (pTask.applyForProxy.proxyReply.proxy.uiTranNo_openAvDev_v == pTransferVideoData->uiTranNo_openAvDev)
		{
#if __DEBUG__
			traceLog(_T("findOrgMsg: applyForProxy: my pkt is sent back. skipped"));
#endif
			iErr = 1; goto errLabel;
		}
	}

	//  2014/11/21
	if (!pTask.receiver.bRecvd_proxiedTranInfo)
	{  //  一般性的数据包处理，或者是proxy

		//  search in mems_from directly
		for (index = 0; index < videoConference.usCntLimit_activeMems_from; index++)
		{

						DLG_TALK_videoConferenceActiveMemFrom pActiveMem_from = videoConference.activeMems_from[index];

						//
						if (pActiveMem_from.avStream.idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id
				&& pActiveMem_from.avStream.obj.tranInfo.video.uiTranNo_openAvDev == pTransferVideoData->uiTranNo_openAvDev)
			{
#if __DEBUG__
				//  traceLogA(  "VideoData: usCntLimit_mems_from %d",  pTransferAvInfoElem->myTask.usCntLimit_mems_from  );
#endif
				//  


				//
				pTransferVideoData->tmpInternal.param.index_pMems_from = -1;
				pTransferVideoData->tmpInternal.param.index_activeMems_from = index;

				//  2014/11/21
				if (pTask.doProxy.bExists_avProxy)
				{

					int index_activeMems_from = 0;

					//
					QIS_DISPATCH pDispatch = MACRO_getDispatch(ref pTask, index_activeMems_from);
					if (pDispatch!=null)
					{
						q2PostMsgAndTrigger((IntPtr)pMsgTask, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgTask->lenInBytes, pDispatch.video.q2);
					}
					iErr = 1; goto errLabel;
				}

				//
				QY_TRANSFORM pTransform = MACRO_getTransform(ref pTask, pTransferVideoData->tmpInternal.param.index_activeMems_from);
				if (pTransform!=null)
				{
					//  
					QY_Q2 pQ2 = pTransform.v_preTransThread.q2;
					if (null==pTransform.v_preTransThread.hThread
						&& null!=pTransform.video.hThread)
					{
						pQ2 = pTransform.video.q2;
					}

					//
					q2PostMsgAndTrigger((IntPtr)pMsgTask, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgTask->lenInBytes, pQ2);
				}
				iErr = 1; goto errLabel;
			}
		}
		//
	}
	else
	{  //  receiver from proxy				  			 
		if (pTask.mem0_from.idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id
			&& pTask.mem0_from.video.tv_recvd.uiTranNo_openAvDev == pTransferVideoData->uiTranNo_openAvDev)
		{
			//  2014/11/21
			if (pTask.receiver.proxied_from.idInfo.ui64Id == pMisCnt.idInfo.ui64Id)
			{
#if __DEBUG__
				traceLog(_T("findOrgMsg: v receiver: my pkt is sent back. skipped"));
#endif
				iErr = 1; goto errLabel;
			}

			//
			int i = 0;
			int iPos = 0;
			TRANSFER_VIDEO_dataMemHead* pMem = null;
			int index_activeMems_from = 0;
			uint usIndex_pMems_from = 0;
			QY_TRANSFORM pTransform = null;
			MIS_MSG_TASK* pMsgTask_toTransform = null;
			TRANSFER_VIDEO_DATA* pNew = null;

			if (null==pTask.video.pMsgU_toTransform)
			{
#if __DEBUG__
				traceLogA("findOrgMsg failed. pMsgTask_toTransform is null");
#endif
				goto errLabel;
			}
			pMsgTask_toTransform = (MIS_MSG_TASK*)pTask.video.pMsgU_toTransform;

			if (0==pTransferVideoData->usCnt)
			{
				pTransferVideoData->usCnt = 1;  //  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
				pTransferVideoDataMems[0].uiLen = pTransferVideoData->uiLen;
			}
			if (pTransferVideoData->usCnt > Consts.CONST_maxTransferAvDataMems) goto errLabel;

#if __DEBUG__
			//  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video len %d"  ),  pTransferVideoData->uiLen  );
#endif


			for (iPos = 0, i = 0; i < pTransferVideoData->usCnt; iPos = (int)(iPos + pTransferVideoDataMems[i].uiLen), i++)
			{
				pMem = &pTransferVideoDataMems[i];
				if (0==pMem->uiLen)
				{
#if __DEBUG__
					traceLogA("findOrgMsg: transferVideoMem.uiLen is 0. skipped.");
#endif
					continue;
				}

				if (iPos + pTransferVideoDataMems[i].uiLen > pTransferVideoData->uiLen)
				{
#if __DEBUG__
					traceLogA("findOrgMsg failed: iPos + mem.uiLen > data.uiLen");
#endif
					goto errLabel;
				}

				//if  (  !pMem->idInfo.ui64Id  )  pMem->idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;

				//											
				usIndex_pMems_from = 1;
				TASK_AV_FROM pFrom = null;
				pFrom = getTaskAvFrom(ref pTask, (int)usIndex_pMems_from, _T(""));
				if (null==pFrom) goto errLabel;

				//
				MACRO_memset_misMsgTask(pMsgTask_toTransform);
				mymemcpy((IntPtr)pMsgTask_toTransform, (IntPtr)pMsgTask, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data"));
				pMsgTask_toTransform->data.route.idInfo_from.ui64Id = pFrom.idInfo.ui64Id;
				pMsgTask_toTransform->data.route.idInfo_to.ui64Id = pMsgTask->data.route.idInfo_to.ui64Id;
				pNew = (TRANSFER_VIDEO_DATA*)pMsgTask_toTransform->data.buf;
				mymemset((IntPtr)pNew, 0, (int)Marshal.OffsetOf<TRANSFER_VIDEO_DATA>("buf"));
				pNew->uiType = pTransferVideoData->uiType;
				pNew->uiTranNo_openAvDev = pFrom.video.tv_recvd.uiTranNo_openAvDev;
							pNewMems = (TRANSFER_VIDEO_dataMemHead*)pNew->buf_TRANSFER_VIDEO_dataMemHead_mems;
				mymemcpy((IntPtr)(byte*)&pNewMems[0], (IntPtr)pMem, (uint)sizeof(TRANSFER_VIDEO_dataMemHead)  );
			pNew->usCnt = 1;
			pNew->uiLen = pMem->uiLen;
			mymemcpy((IntPtr)pNew->buf, (IntPtr)(pTransferVideoData->buf + iPos), pNew->uiLen);

			//										
			pNew->tmpInternal.param.index_pMems_from = (int)usIndex_pMems_from;
			pNew->tmpInternal.param.index_activeMems_from = index_activeMems_from;

			//
			pMsgTask_toTransform->lenInBytes = (uint)Marshal.OffsetOf<MIS_MSG_routeTalkData>("buf") + (uint)Marshal.OffsetOf<TRANSFER_VIDEO_DATA>("buf") + pNew->uiLen;

			pTransform = MACRO_getTransform(ref pTask, index_activeMems_from);
			if (pTransform!=null)
			{
				//  
				q2PostMsgAndTrigger((IntPtr)pMsgTask_toTransform, (uint)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgTask_toTransform->lenInBytes, pTransform.v_preTransThread.q2);
			}

			//  2014/11/11
			continue;

		}

		iErr = 1; goto errLabel;
	}

	//
	iErr = 0; goto errLabel;
}	
	}

			

	iErr = 0;
errLabel:
return iErr;
}



		//
		public static unsafe int tmpHandler_findOrgMsgAndProcess_mis_procInputVideoData( CTX_caller ctxCaller,CCtxQmc pProcInfo, MSGR_ADDR* pAddr, int iTaskId, MIS_MSG_INPUT* pMsgInput, TRANSFER_VIDEO_DATA* pTransferVideoData, IM_CONTENTU* pContentElem, ref PROC_TASK_AV pTask)
		{
			int iErr = -1;
			int index = 0;
			MIS_CNT pMisCnt = pProcInfo.pMisCnt;
			TRANSFER_VIDEO_dataMemHead* pTransferVideoDataMems = (TRANSFER_VIDEO_dataMemHead*)pTransferVideoData->buf_TRANSFER_VIDEO_dataMemHead_mems;
			int bufSize = Consts.bufSize_TRANSFER_VIDEO_dataMemHead_mems;
			TRANSFER_VIDEO_dataMemHead* pNewMems = null;
			//
			bool bDbg = false;
			string str;

			QMC_TASK_INFO pTaskInfo = (QMC_TASK_INFO)getQmcTaskInfoByIndex(ctxCaller, pProcInfo, pTask.iIndex_taskInfo,"findOrgMsg_procInputVideoData");
			if (null == pTaskInfo) return -1;
			QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
			if (pTaskData == null) return -1;
			if (pTaskData.uiType != Consts.CONST_taskDataType_conf) return -1;
			QMC_taskData_conf pTc = (QMC_taskData_conf)pTaskData;
			DLG_TALK_videoConference videoConference = pTc.getVideoConference();

			//
#if DEBUG
			chkTc(pTc, "find_procInputVideoData enters");
#endif

			//
			if (pTask.ucbVideoConferenceStarter)
			{
				/*

		if (pContentElem->uiType != CONST_imCommType_transferAvInfo)
		{
#if __DEBUG__
			traceLog(_T("procTaskVideoData failed, contentType err"));
#endif
			goto errLabel;
		}

		//  2014/11/11
		if (pMsgTask->iTaskId == iTaskId)
		{
			if (pMsgTask->data.route.idInfo_from.ui64Id == pMisCnt.idInfo.ui64Id)
			{
				if (pTransferVideoData->uiTranNo_openAvDev == pContentElem->transferAvInfo.confMosaicTranInfo_video.video.uiTranNo_openAvDev
					|| pTransferVideoData->uiTranNo_openAvDev == pContentElem->transferAvInfo.confMosaicTranInfo_resource.video.uiTranNo_openAvDev)
				{
					//
					dispatch_outputConfVideo(pTask, pMsgTask, pTransferVideoData, &pMisCnt.idInfo, pTransferVideoData->uiTranNo_openAvDev);
					//			
					iErr = 1; goto errLabel;
				}
			}
		}

		//
		int index_activeMems_from = 0;

		//  search in activeMems_from first
		for (index_activeMems_from = 0; index_activeMems_from < pTask.usCntLimit_activeMems_from; index_activeMems_from++)
		{
			if (pTask.activeMems_from[index_activeMems_from].idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id) break;
		}
		//  use searched index to process video
		if (index_activeMems_from < pTask.usCntLimit_activeMems_from)
		{
			index = pTask.activeMems_from[index_activeMems_from].usIndex_pMems_from;
			if (index >= 0 && index < pTask.usCntLimit_mems_from)
			{
				TASK_AV_FROM* pFrom = &pTask.pMems_from[index];
				//
				if (pFrom->idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id
					&& pFrom->video.tv_recvd.uiTranNo_openAvDev == pTransferVideoData->uiTranNo_openAvDev)
				{
# ifdef  __DEBUG__		
					//  traceLogA(  "VideoData: usCntLimit_mems_from %d, usCntLimit_activeMems_from %d, video conference starter",  pTransferAvInfoElem->myTask.usCntLimit_mems_from,  pTransferAvInfoElem->myTask.usCntLimit_activeMems_from  );
#endif

				//
				pTransferVideoData->tmpInternal.param.index_pMems_from = index;
					pTransferVideoData->tmpInternal.param.index_activeMems_from = index_activeMems_from;

					//
					QIS_DISPATCH* pDispatch = MACRO_getDispatch(*pTask, index_activeMems_from);
					if (pDispatch)
					{
						q2PostMsgAndTrigger(pMsgTask, offsetof(MIS_MSG_TASK, data) + pMsgTask->lenInBytes, &pDispatch->video.q2);
					}

					iErr = 1; goto errLabel;
				}
			}
		}
				*/
			}
			else if (pTask.ucbVideoConference)
			{

				//
				if (pMsgInput->iTaskId == iTaskId)
				{
					//  2011/01/23				  
					if (pMsgInput->data.route.idInfo_from.ui64Id == pMisCnt.idInfo.ui64Id)
					{
						//  traceLog(  _T(  "video data sent by myself"  )  );

						q2PostMsg((IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + pMsgInput->lenInBytes, pTask.photomosaic.pOutputQ2);
						MIS_CHANNEL pChannel = getChannelByType(pMisCnt, Consts.CONST_channelType_media);
						if (null != pChannel) q2PostMsgAndTrigger(IntPtr.Zero, 0, pChannel.outputQ2);

						//
						iErr = 1; goto errLabel;
					}
				}

				//
				if (pTask.mem0_from.idInfo.ui64Id == pMsgInput->data.route.idInfo_from.ui64Id
					&& pTask.mem0_from.video.tv_recvd.uiTranNo_openAvDev == pTransferVideoData->uiTranNo_openAvDev)
				{
					int i = 0;
					int iPos = 0;
					TRANSFER_VIDEO_dataMemHead* pMem = null;
					int index_activeMems_from = 0;
					uint usIndex_pMems_from = 0;
					QY_TRANSFORM pTransform = null;
					MIS_MSG_INPUT* pMsgInput_toTransform = null;
					TRANSFER_VIDEO_DATA* pNew = null;

					if (null == pTask.video.pMsgU_toTransform)
					{
#if __DEBUG__
				traceLogA("findOrgMsg failed. pMsgTask_toTransform is null");
#endif
						goto errLabel;
					}
					pMsgInput_toTransform = (MIS_MSG_INPUT*)pTask.video.pMsgU_toTransform;

					if (0 == pTransferVideoData->usCnt)
					{
						pTransferVideoData->usCnt = 1;  //  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
						pTransferVideoDataMems[0].uiLen = pTransferVideoData->uiLen;
					}
					if (pTransferVideoData->usCnt > Consts.CONST_maxTransferAvDataMems) goto errLabel;

#if __DEBUG__
			//  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video len %d"  ),  pTransferVideoData->uiLen  );
#endif


					for (iPos = 0, i = 0; i < pTransferVideoData->usCnt; iPos = (int)(iPos + pMem->uiLen), i++)
					{
						pMem = getMem(pTransferVideoDataMems, bufSize,i);// &pTransferVideoDataMems[i];
						if (0 == pMem->uiLen)
						{
							//
#if __DEBUG__
					//traceLogA(  "findOrgMsg: transferVideoMem.uiLen is 0. skipped."  );
#endif
							//
							continue;
						}

						if (iPos + pMem->uiLen > pTransferVideoData->uiLen)
						{
#if __DEBUG__
					traceLogA("findOrgMsg failed: iPos + mem.uiLen > data.uiLen");
#endif
							goto errLabel;
						}

						if (0 == pMem->idInfo.ui64Id) pMem->idInfo.ui64Id = pMsgInput->data.route.idInfo_from.ui64Id;
						
						//
						if (videoConference.usCntLimit_activeMems_from > videoConference.activeMems_from.Length)
                        {
							str = string.Format("usCntLimit_activeMems_from {0}, activeMems.length {1}", videoConference.usCntLimit_activeMems_from, videoConference.activeMems_from.Length);
							int ii = 0;
                        }
						
						//
						for (index_activeMems_from = 0; index_activeMems_from < videoConference.usCntLimit_activeMems_from; index_activeMems_from++)
						{
							if (pMem->idInfo.ui64Id == videoConference.activeMems_from[index_activeMems_from].avStream.idInfo.ui64Id
								&&pMem->uiTranNo_openAvDev==videoConference.activeMems_from[index_activeMems_from].avStream.obj.tranInfo.video.uiTranNo_openAvDev) break;
						}
						if (index_activeMems_from == videoConference.usCntLimit_activeMems_from)
						{
							//pAddr->idInfo.ui64Id;
							str =string.Format("findOrgMsg: video, conf{0}, from {1}, can't get index_activeMems_from, skipped.", pAddr->idInfo.ui64Id, pMem->idInfo.ui64Id);
							//
							showInfo_open(0, null, str);

							//
							iErr = Consts.CONST_qyRet_cantGet_index_activeMems_from; goto errLabel;
						}
						//
						DLG_TALK_videoConferenceActiveMemFrom pActiveMem_from = videoConference.activeMems_from[index_activeMems_from];


						//
						MACRO_memset_misMsgInput(pMsgInput_toTransform);
						mymemcpy((IntPtr)pMsgInput_toTransform, (IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data"));
						pMsgInput_toTransform->data.route.idInfo_from.ui64Id = videoConference.activeMems_from[index_activeMems_from].avStream.idInfo.ui64Id;
						pMsgInput_toTransform->data.route.idInfo_to.ui64Id = pMsgInput->data.route.idInfo_to.ui64Id;
						pNew = (TRANSFER_VIDEO_DATA*)pMsgInput_toTransform->data.buf;
						mymemset((IntPtr)pNew, 0, (int)Marshal.OffsetOf<TRANSFER_VIDEO_DATA>("buf"));
						pNew->uiType = pTransferVideoData->uiType;
						pNew->uiTranNo_openAvDev = pActiveMem_from.avStream.obj.tranInfo.video.uiTranNo_openAvDev;
						pNewMems = (TRANSFER_VIDEO_dataMemHead*)pNew->buf_TRANSFER_VIDEO_dataMemHead_mems;
						mymemcpy((IntPtr)(byte*)&pNewMems[0], (IntPtr)pMem, (uint)sizeof(TRANSFER_VIDEO_dataMemHead));
						pNew->usCnt = 1;
						pNew->uiLen = pMem->uiLen;
						mymemcpy((IntPtr)pNew->buf, (IntPtr)(pTransferVideoData->buf + iPos), pNew->uiLen);

						//  2017/09/05

						//										
						pNew->tmpInternal.param.index_pMems_from = -1;// pTask.activeMems_from[index_activeMems_from].usIndex_pMems_from;
						pNew->tmpInternal.param.index_activeMems_from = index_activeMems_from;

						//
						pMsgInput_toTransform->lenInBytes = (uint)Marshal.OffsetOf<MIS_MSG_routeTalkData>("buf") + (uint)Marshal.OffsetOf<TRANSFER_VIDEO_DATA>("buf") + pNew->uiLen;

						pTransform = MACRO_getTransform(ref pTask, index_activeMems_from);
						if (pTransform != null)
						{
							//  
							q2PostMsgAndTrigger((IntPtr)pMsgInput_toTransform, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + pMsgInput_toTransform->lenInBytes, pTransform.v_preTransThread.q2);
						}

						//  2014/11/11
						continue;
					}

					iErr = 1; goto errLabel;
				}
			}   //  end of processing confMem
			else
			{  //  

				if (pMsgInput->iTaskId == iTaskId)
				{
					//  2011/01/23				  
					if (pMsgInput->data.route.idInfo_from.ui64Id == pMisCnt.idInfo.ui64Id)
					{
						//  traceLog(  _T(  "video data sent by myself"  )  );
						if (bDbg)
						{
							int nQNodes = getQ2Nodes(pTask.photomosaic.pOutputQ2);
							str = string.Format("tmp_find_procTaskVideo: to send video data, task.outputQ2.nQNodes {0} ", nQNodes);
							traceLog(str);
						}

						//
						q2PostMsg((IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + pMsgInput->lenInBytes, pTask.photomosaic.pOutputQ2);
						MIS_CHANNEL pChannel = getChannelByType(pMisCnt, Consts.CONST_channelType_media);
						if (pChannel != null)
						{
							//q2PostMsgAndTrigger(IntPtr.Zero, 0, pChannel.outputQ2);
							q2PostMsgAndTrigger(IntPtr.Zero, 0, pChannel.toSendQ2);
						}

						//
						iErr = 1; goto errLabel;
					}
				}

				//  2014/11/21
				if (pTask.applyForProxy.bRecvd_proxyReply)
				{       //  applier for proxy
					if (pTask.applyForProxy.proxyReply.proxy.uiTranNo_openAvDev_v == pTransferVideoData->uiTranNo_openAvDev)
					{
#if __DEBUG__
			traceLog(_T("findOrgMsg: applyForProxy: my pkt is sent back. skipped"));
#endif
						iErr = 1; goto errLabel;
					}
				}

				//  2014/11/21
				if (!pTask.receiver.bRecvd_proxiedTranInfo)
				{  //  一般性的数据包处理，或者是proxy
#if DEBUG
					//DLG_TALK_videoConference vc = pTc.videoConference;
#endif

					//  search in mems_from directly
					for (index = 0; index < videoConference.usCntLimit_activeMems_from; index++)
					{
						DLG_TALK_videoConferenceActiveMemFrom pActiveMem_from = videoConference.activeMems_from[index];

						//
						if (pActiveMem_from.avStream.idInfo.ui64Id == pMsgInput->data.route.idInfo_from.ui64Id
							&& pActiveMem_from.avStream.obj.tranInfo.video.uiTranNo_openAvDev == pTransferVideoData->uiTranNo_openAvDev)
						{
#if __DEBUG__
				//  traceLogA(  "VideoData: usCntLimit_mems_from %d",  pTransferAvInfoElem->myTask.usCntLimit_mems_from  );
#endif
							//  


							//
							pTransferVideoData->tmpInternal.param.index_pMems_from = -1;// index;
							pTransferVideoData->tmpInternal.param.index_activeMems_from = index;

							//  2014/11/21
							if (pTask.doProxy.bExists_avProxy)
							{

								int index_activeMems_from = 0;

								//
								QIS_DISPATCH pDispatch = MACRO_getDispatch(ref pTask, index_activeMems_from);
								if (pDispatch != null)
								{
									q2PostMsgAndTrigger((IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + pMsgInput->lenInBytes, pDispatch.video.q2);
								}
								iErr = 1; goto errLabel;
							}

							//
							QY_TRANSFORM pTransform = MACRO_getTransform(ref pTask, pTransferVideoData->tmpInternal.param.index_activeMems_from);
							if (pTransform != null)
							{
								//  
								QY_Q2 pQ2 = pTransform.v_preTransThread.q2;
								//
#if false
								if (null == pTransform.v_preTransThread.hThread
									&& null != pTransform.video.hThread)
								{
									pQ2 = pTransform.video.q2;
								}
#endif

								//
								q2PostMsgAndTrigger((IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + pMsgInput->lenInBytes, pQ2);
							}
							iErr = 1; goto errLabel;
						}
					}
					//
				}
				else
				{  //  receiver from proxy				  			 
					if (pTask.mem0_from.idInfo.ui64Id == pMsgInput->data.route.idInfo_from.ui64Id
						&& pTask.mem0_from.video.tv_recvd.uiTranNo_openAvDev == pTransferVideoData->uiTranNo_openAvDev)
					{
						//  2014/11/21
						if (pTask.receiver.proxied_from.idInfo.ui64Id == pMisCnt.idInfo.ui64Id)
						{
#if __DEBUG__
				traceLog(_T("findOrgMsg: v receiver: my pkt is sent back. skipped"));
#endif
							iErr = 1; goto errLabel;
						}

						//
						int i = 0;
						int iPos = 0;
						TRANSFER_VIDEO_dataMemHead* pMem = null;
						int index_activeMems_from = 0;
						uint usIndex_pMems_from = 0;
						QY_TRANSFORM pTransform = null;
						MIS_MSG_INPUT* pMsgInput_toTransform = null;
						TRANSFER_VIDEO_DATA* pNew = null;

						if (null == pTask.video.pMsgU_toTransform)
						{
#if __DEBUG__
				traceLogA("findOrgMsg failed. pMsgTask_toTransform is null");
#endif
							goto errLabel;
						}
						pMsgInput_toTransform = (MIS_MSG_INPUT*)pTask.video.pMsgU_toTransform;

						if (0 == pTransferVideoData->usCnt)
						{
							pTransferVideoData->usCnt = 1;  //  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
							pTransferVideoDataMems[0].uiLen = pTransferVideoData->uiLen;
						}
						if (pTransferVideoData->usCnt > Consts.CONST_maxTransferAvDataMems) goto errLabel;

#if __DEBUG__
			//  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "findOrgMsg: video len %d"  ),  pTransferVideoData->uiLen  );
#endif


						for (iPos = 0, i = 0; i < pTransferVideoData->usCnt; iPos = (int)(iPos + pTransferVideoDataMems[i].uiLen), i++)
						{
							pMem = &pTransferVideoDataMems[i];
							if (0 == pMem->uiLen)
							{
#if __DEBUG__
					traceLogA("findOrgMsg: transferVideoMem.uiLen is 0. skipped.");
#endif
								continue;
							}

							if (iPos + pTransferVideoDataMems[i].uiLen > pTransferVideoData->uiLen)
							{
#if __DEBUG__
					traceLogA("findOrgMsg failed: iPos + mem.uiLen > data.uiLen");
#endif
								goto errLabel;
							}

							//if  (  !pMem->idInfo.ui64Id  )  pMem->idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;

							//											
							usIndex_pMems_from = 1;
							TASK_AV_FROM pFrom = null;
							pFrom = getTaskAvFrom(ref pTask, (int)usIndex_pMems_from, _T(""));
							if (null == pFrom) goto errLabel;

							//
							MACRO_memset_misMsgInput(pMsgInput_toTransform);
							mymemcpy((IntPtr)pMsgInput_toTransform, (IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data"));
							pMsgInput_toTransform->data.route.idInfo_from.ui64Id = pFrom.idInfo.ui64Id;
							pMsgInput_toTransform->data.route.idInfo_to.ui64Id = pMsgInput->data.route.idInfo_to.ui64Id;
							pNew = (TRANSFER_VIDEO_DATA*)pMsgInput_toTransform->data.buf;
							mymemset((IntPtr)pNew, 0, (int)Marshal.OffsetOf<TRANSFER_VIDEO_DATA>("buf"));
							pNew->uiType = pTransferVideoData->uiType;
							pNew->uiTranNo_openAvDev = pFrom.video.tv_recvd.uiTranNo_openAvDev;
							pNewMems = (TRANSFER_VIDEO_dataMemHead*)pNew->buf_TRANSFER_VIDEO_dataMemHead_mems;
							mymemcpy((IntPtr)(byte*)&pNewMems[0], (IntPtr)pMem, (uint)sizeof(TRANSFER_VIDEO_dataMemHead));
							pNew->usCnt = 1;
							pNew->uiLen = pMem->uiLen;
							mymemcpy((IntPtr)pNew->buf, (IntPtr)(pTransferVideoData->buf + iPos), pNew->uiLen);

							//										
							pNew->tmpInternal.param.index_pMems_from = (int)usIndex_pMems_from;
							pNew->tmpInternal.param.index_activeMems_from = index_activeMems_from;

							//
							pMsgInput_toTransform->lenInBytes = (uint)Marshal.OffsetOf<MIS_MSG_routeTalkData>("buf") + (uint)Marshal.OffsetOf<TRANSFER_VIDEO_DATA>("buf") + pNew->uiLen;

							pTransform = MACRO_getTransform(ref pTask, index_activeMems_from);
							if (pTransform != null)
							{
								//  
								q2PostMsgAndTrigger((IntPtr)pMsgInput_toTransform, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + pMsgInput_toTransform->lenInBytes, pTransform.v_preTransThread.q2);
							}

							//  2014/11/11
							continue;

						}

						iErr = 1; goto errLabel;
					}

					//
					iErr = 0; goto errLabel;
				}
			}



			iErr = 0;
		errLabel:

#if DEBUG
			chkTc(pTc, "find_procInputVideoData leaves");
#endif

			return iErr;
		}






		//
		public static unsafe int procTaskProcReq_applyForKeyFrame(CCtxQmc pProcInfo, MSGR_ADDR* pAddr, int iTaskId, MIS_MSG_TASK* pMsgTask, TASK_PROC_REQ* pTaskProcReq, IM_CONTENTU* pContentElem, ref PROC_TASK_AV pTask)
		{
			int iErr = -1;
			CCtxQyMc pQyMc = g.g_pQyMc;
			MIS_CNT pMisCnt = pProcInfo.pMisCnt;

			

#if DEBUG
			traceLog(_T("procTaskProcReq_applyForKeyFrame called"));
#endif

			
			if (pTask.ucbVideoConferenceStarter)
			{
#if false
#if __DEBUG__
				traceLog(_T("Not finished. for conf starter"));
#endif
				//
				if (pTaskProcReq->vStream.uiTranNo_openAvDev == pTask.mem0_from.video.tv_recvd.uiTranNo_openAvDev)
				{
					//
					setFlg_forceKeyFrame(pProcInfo, pTask.iIndex_sharedObj);
					//
					iErr = 0; goto errLabel;
				}

				//  2014/12/06
				if (pContentElem->uiType != CONST_imCommType_transferAvInfo)
				{
					goto errLabel;
				}
				TRANSFER_AV_INFO* pTransferAvInfo = &pContentElem->transferAvInfo;
				//
				if (pTaskProcReq->vStream.uiTranNo_openAvDev == pTransferAvInfo->confMosaicTranInfo_video.video.uiTranNo_openAvDev)
				{
					//
					setFlg_forceKeyFrame(pProcInfo, pTask.confMosaicMaker.iIndex_sharedObj_video);
					//
					iErr = 0; goto errLabel;
				}
				//
				if (pTaskProcReq->vStream.uiTranNo_openAvDev == pTransferAvInfo->confMosaicTranInfo_resource.video.uiTranNo_openAvDev)
				{
					//
					setFlg_forceKeyFrame(pProcInfo, pTask.confMosaicMaker.iIndex_sharedObj_resource);
					//
					iErr = 0; goto errLabel;
				}

				// others
#if __DEBUG__
				traceLog(_T("Not finished. for conf starter"));
#endif
				showInfo_open(0, 0, _T("Not finished: procTaskProcReq_applyForKeyFrame, conf starter: for others"));
				goto errLabel;
#endif
			}
			else if (pTask.ucbVideoConference)
			{
				setFlg_forceKeyFrame(pProcInfo, pTask.iIndex_sharedObj);
			}
			else
			{
				setFlg_forceKeyFrame(pProcInfo, pTask.iIndex_sharedObj);
			}

			

			iErr = 0;
		errLabel:
			return iErr;

		}

		public static unsafe int tmpHandler_find_procTaskVideoDataResp(CCtxQmc pProcInfo, MIS_MSG_TASK* pMsgElem, MIS_MSG_INPUT* pMsgInput, TRANSFER_VIDEO_dataResp* pResp)
		{
			int iErr = -1;
			IM_CONTENTU* pContentElem = (IM_CONTENTU*)pMsgElem->data.buf;
			int index = 0;
			//
			MIS_CNT pMisCnt = pProcInfo.pMisCnt;


			/*
			//
			if (pContentElem->uiType == CONST_imCommType_transferAvInfo)
			{
				AV_TRAN_INFO* pTranInfo = &pContentElem->transferAvInfo.tranInfo;
				PROC_TASK_AV* pTask = get_transferAvInfo_pTask(&pContentElem->transferAvInfo, _T(""));
				if (!pTask) goto errLabel;

				//
				if (pTask.ucbVideoConferenceStarter)
				{

					//
					if (pResp->idInfo.ui64Id == pMisCnt.idInfo.ui64Id)
					{
						if (pResp->uiTranNo_openAvDev == pContentElem->transferAvInfo.confMosaicTranInfo_video.video.uiTranNo_openAvDev
							|| pResp->uiTranNo_openAvDev == pContentElem->transferAvInfo.confMosaicTranInfo_resource.video.uiTranNo_openAvDev)
						{
							int ii = 0;

							if (procTaskVideoDataResp(pProcInfo, pTranInfo, pTask, pMsgInput, pResp)) goto errLabel;

							iErr = 1; goto errLabel;

						}
					}

					//
					int index_activeMems_from = 0;

					//  search in activeMems_from first
					for (index_activeMems_from = 0; index_activeMems_from < pTask.usCntLimit_activeMems_from; index_activeMems_from++)
					{
						if (pTask.activeMems_from[index_activeMems_from].idInfo.ui64Id == pResp->idInfo.ui64Id) break;
					}
					//  use searched index to process video
					if (index_activeMems_from < pTask.usCntLimit_activeMems_from)
					{
						index = pTask.activeMems_from[index_activeMems_from].usIndex_pMems_from;
						if (index >= 0 && index < pTask.usCntLimit_mems_from)
						{
							TASK_AV_FROM* pFrom = &pTask.pMems_from[index];

							if (pFrom->idInfo.ui64Id == pResp->idInfo.ui64Id
							&& pFrom->video.tv_recvd.uiTranNo_openAvDev == pResp->uiTranNo_openAvDev)
							{
								int ii = 0;

								if (procTaskVideoDataResp(pProcInfo, pTranInfo, pTask, pMsgInput, pResp)) goto errLabel;

								iErr = 1; goto errLabel;

							}

						}

					}

				}


				//
				if (pMsgElem->data.route.idInfo_from.ui64Id == pMsgInput->data.route.idInfo_to.ui64Id
					&& pTranInfo->video.uiTranNo_openAvDev == pResp->uiTranNo_openAvDev)
				{

					//  OutputDebugString(  _T(  "VideoData Resp\n"  )  );


					if (procTaskVideoDataResp(pProcInfo, pTranInfo, pTask, pMsgInput, pResp)) goto errLabel;


					iErr = 1; goto errLabel;

				}
			}
			else if (pContentElem->uiType == CONST_imCommType_transferAvReplyInfo)
			{
				AV_TRAN_INFO* pTranInfo = &pContentElem->transferAvReplyInfo.tranInfo;
				PROC_TASK_AV* pTask = get_transferAvReplyInfo_pTask(&pContentElem->transferAvReplyInfo, _T(""));
				if (!pTask) goto errLabel;

				if (pMsgElem->data.route.idInfo_to.ui64Id == pMsgInput->data.route.idInfo_from.ui64Id
					&& pTranInfo->video.uiTranNo_openAvDev == pResp->uiTranNo_openAvDev)
				{
					//  OutputDebugString(  _T(  "VideoData Resp, ½«µ÷ÕûÊÓÆµ·¢ËÍÆµÂÊ\n"  )  );

					if (procTaskVideoDataResp(pProcInfo, pTranInfo, pTask, pMsgInput, pResp)) goto errLabel;

					iErr = 1; goto errLabel;

				}

			}
			*/



			iErr = 0;
		errLabel:
			return iErr;
		}


		//
		public static bool bInActiveMems(CCtxQmc pProcInfo, QY_MESSENGER_ID idInfo, uint tn_a, uint tn_v, TASK_transferAv task)
        {
			bool bRet = false;
			//task.myTask.ucbVideoConference
			QMC_TASK_INFO pTaskInfo = getQmcTaskInfoByIndex(null, pProcInfo, task.m_index_taskInfo, "");
			if (pTaskInfo == null) goto errLabel;
			QMC_taskData_conf pTc = (QMC_taskData_conf)pTaskInfo.getTaskData();
			if (pTc == null) goto errLabel;
			DLG_TALK_videoConference videoConference = pTc.getVideoConference();
			if (videoConference == null) goto errLabel;

			int i;
			for (i = 0; i < videoConference.usCntLimit_activeMems_from; i++)
			{
				DLG_TALK_videoConferenceActiveMemFrom activeMem = videoConference.activeMems_from[i];
				if (idInfo.ui64Id == activeMem.avStream.idInfo.ui64Id)
				{
					if (tn_a != 0
						&& tn_a == activeMem.avStream.obj.tranInfo.audio.uiTranNo_openAvDev)
					{
						bRet = true; goto errLabel;
					}
					if ( tn_v!=0
						&& tn_v==activeMem.avStream.obj.tranInfo.video.uiTranNo_openAvDev)
                    {
						bRet = true; goto errLabel;
                    }
				}
				//
				continue;
			}

			//
			errLabel:
			return bRet;
        }


		//
		public static unsafe int tmpHandler_findOrgMsgAndProc_is( CTX_caller ctxCaller, object pMsg_toBeSearchedParam, object p1Param, object taskElemParam)
		{

			int iErr = -1;

			bool bDbg = false;
			string str;

#if DEBUG
			//bDbg = true;
#endif

			//
			MIS_MSGU* pMsg_toBeSearched = (MIS_MSGU*)(IntPtr)pMsg_toBeSearchedParam;
			IntPtr p1 = (IntPtr)p1Param;
			//  p1
			//
			CCtxQyMc pQyMc = g.g_pQyMc;
			CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
			if (null==pProcInfo) return -1;
			int tmpiRet = 0;
			QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;
			if (null==pDbFuncs) goto errLabel;
			QM_dbFuncs  g_dbFuncs = pDbFuncs;
			MIS_CNT pMisCntElem = pProcInfo.pMisCnt;
			MIS_CNT pMisCnt = pProcInfo.pMisCnt;

	
			//
			TASK_common taskElem = (TASK_common)taskElemParam;
			QMC_TASK_INFO pTaskInfo = getQmcTaskInfoByIndex(ctxCaller,pProcInfo, taskElem.m_index_taskInfo,"findOrgMsg");
			if (pTaskInfo == null) goto errLabel;
			QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
			if (pTaskData == null) goto errLabel;

			//
			if (pProcInfo.cfg.ucb_USE_specialDbg)
            {
				//traceLog("for test, tmpHandler_findOrgMsgAndProc_is return 0");
				return 0;
            }
#if DEBUG
			if (pProcInfo.cfg.mSpecialDbg.bTrace_tmpHandler_findOrgMsgAndProc_is)
            {
				bDbg = true;
            }
#endif

			//
			if (bDbg)
            {
				fixed (char* pName = ctxCaller.tNameBuf.tNameBuf)
				{
					str = string.Format("tmpHandler_findOrgMsg enters, {0}", new string(pName));
				}
				qyFuncs.showInfo_open(0, null, str);
				qyFuncs.showAllTc(ctxCaller,str);
            }


			//
			fixed (MIS_MSGU* pMsgElemParam = &pTaskData.msgU)
			{

				switch (((MIS_MSGU*)pMsgElemParam)->uiType)
				{
					case Consts.CONST_misMsgType_req:
						{
							MIS_MSG_REQ* pMsgElem = (MIS_MSG_REQ*)pMsgElemParam;
							IM_CONTENTU* pContentElem = M_getMsgContent(pMsgElem->ucFlg, &pMsgElem->data);
							//
							switch (pMsg_toBeSearched->uiType)
							{
								case Consts.CONST_misMsgType_input:
									{
										MIS_MSG_INPUT* pMsgInput = &pMsg_toBeSearched->input;
										//
										if (pMsgElem->tStartTime == pMsgInput->tStartTime
											&& pMsgElem->uiTranNo == pMsgInput->uiTranNo)
										{
											pMsgInput->usCode_org = pMsgElem->usCode;
											iErr = 1; goto errLabel;        //  ÕÒµ½ÁË
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
					case Consts.CONST_misMsgType_task:
						{
							MIS_MSG_TASK* pMsgElem = (MIS_MSG_TASK*)pMsgElemParam;
							IM_CONTENTU* pContentElem = (IM_CONTENTU*)pMsgElem->data.buf;
							//
#if DEBUG
							ref IM_CONTENTU tmp_pContentElem = ref *pContentElem;
#endif
							//
							switch (pMsg_toBeSearched->uiType)
							{
								case Consts.CONST_misMsgType_task:
									{
										MIS_MSG_TASK* pMsgTask = &pMsg_toBeSearched->task;
										IM_CONTENTU* pContent = (IM_CONTENTU*)pMsgTask->data.buf;

										//
#if __DEBUG__   //  2014/08/28
										if (pContent->uiType == CONST_imCommType_taskProcReq)
										{
											if (pContent->taskProcReq.usOp == CONST_imOp_recv_applyForKeyFrame)
											{
												int i;
												i = 9;
											}
										}
#endif

										//
										if (!isUcFlgResp(pMsgTask->ucFlg))
										{
											if (pContentElem->uiType == Consts.CONST_imCommType_transferFileReq)
											{
												if (pContent->uiType == Consts.CONST_imCommType_transferFileReplyReq)
												{   //  ÕâÊÇÔÚfile·¢ËÍ¶Ë£¬½ÓÊÕ»Ø¸´À´Ê±µÄ¼ìË÷
													if (pMsgElem->tStartTime == pContent->transferFileReplyReq.tStartTime_org
														   && pMsgElem->uiTranNo == pContent->transferFileReplyReq.uiTranNo_org)
													{
														//
#if __DEBUG__
														traceLogA("tmpHandler_findOrgMsgAndProc_is: msg - replyReq is matched");
#endif
														//
														pMsgTask->addr_logicalPeer.idInfo.ui64Id = pMsgElem->addr_logicalPeer.idInfo.ui64Id;
														//
														iErr = 1; goto errLabel;
													}
												}
												if (pContent->uiType == Consts.CONST_imCommType_taskProcReq)
												{   //  file·¢ËÍ¶Ë£¬×Ô¼ºÓÖ×·¼ÓÁË±ÈÈçÈ¡ÏûµÈ²Ù×÷ºóµÄ¹¤×÷  
													if (pMsgElem->tStartTime == pContent->taskProcReq.tStartTime_org
														&& pMsgElem->uiTranNo == pContent->taskProcReq.uiTranNo_org)
													{
														//
#if __DEBUG__
														traceLogA("tmpHandler_findOrgMsgAndProc_is: msg - procReq is matched");
#endif
														//
														iErr = 1; goto errLabel;
													}
												}
											}
											if (pContentElem->uiType == Consts.CONST_imCommType_transferFileReplyReq)
											{   //  file½ÓÊÕ¶Ë
												if (pContent->uiType == Consts.CONST_imCommType_taskProcReq)
												{
													if (pContentElem->transferFileReplyReq.tStartTime_org == pContent->taskProcReq.tStartTime_org
														&& pContentElem->transferFileReplyReq.uiTranNo_org == pContent->taskProcReq.uiTranNo_org)
													{
#if __DEBUG__
														traceLogA("tmpHandler_findOrgMsgAndProc_is: msg - procReq matched");
#endif
														iErr = 1; goto errLabel;
													}
												}
											}
											//  
											if (pContentElem->uiType == Consts.CONST_imCommType_transferAvInfo)
											{                               //  media
												if (!pTaskInfo.var.m_bReplyTask)
												{
													TASK_transferAv task = (TASK_transferAv)taskElem;
													TRANSFER_AV_INFO* pTransferAvInfoElem = &pContentElem->transferAvInfo;
													ref PROC_TASK_AV pTaskElem = ref task.myTask;// get_transferAvInfo_pTask(pTransferAvInfoElem, _T(""));
																								 //if (!pTaskElem) goto errLabel;
													int index = 0;

													if (pContent->uiType == Consts.CONST_imCommType_transferAvInfo)
													{                               //  
														TRANSFER_AV_INFO* pTransferAvInfo = &pContent->transferAvInfo;
														//
														if (pMsgElem->tStartTime == pMsgTask->tStartTime
															&& pMsgElem->uiTranNo == pMsgTask->uiTranNo)
														{
															bool canGet = false;
															//
															if (pTaskElem.ucbVideoConferenceStarter) canGet = true;
															else if (bApplyForAvProxy(pMisCntElem, ref *pTransferAvInfoElem)) canGet = true;
															else
															{
#if __DEBUG__
															//  traceLog(  _T(  "findOrgMsg: 
															//  让talk来校验
#endif
																canGet = true;
															}
															//
#if __DEBUG__
														if (!canGet)
														{
															traceLog(_T("findOrgMsg: can't get req again, canGot is false"));
														}
#endif
															//
															if (canGet)
															{
																//  note: 2014/11/21. 这里不再直接覆盖输入内容了，而是要求一定要用param_findOrgMsg来输出. 不知道对原来的有没有影响 
																//  memcpy(  &pContent->transferAvInfo.tranInfo,  &pTransferAvInfoElem->tranInfo,  sizeof(  pContent->transferAvInfo.tranInfo  )  );
																//
#if __DEBUG__
															traceLogA("findOrgMsgAndProc_mis: get req again");
#endif
																//
																PARAM_findOrgMsg* pParam = (PARAM_findOrgMsg*)(IntPtr)p1;
																if (pParam != null)
																{
																	if (pParam->pMsgTask_o != null)
																	{
																		int len = (int)((uint)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgElem->lenInBytes);

																		mymemcpy((IntPtr)pParam->pMsgTask_o, (IntPtr)pMsgElem, (uint)len);
																	}
																}
															}

															iErr = 1; goto errLabel;
														}
														//  2014/11/21
														if (pMsgElem->iTaskId == pMsgTask->iTaskId)
														{
															if (pTransferAvInfoElem->proxiedTranInfo.idInfo.ui64Id != 0 && pTransferAvInfoElem->proxiedTranInfo.uiObjType != 0)
															{
																if (pTransferAvInfoElem->proxiedTranInfo.idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id)
																{
																	if (pTransferAvInfoElem->proxiedTranInfo.ti.audio.uiTranNo_openAvDev != 0 || 0 != pTransferAvInfoElem->proxiedTranInfo.ti.video.uiTranNo_openAvDev)
																	{
																		bool bNotMatched = false;
																		if (pTransferAvInfoElem->proxiedTranInfo.ti.audio.uiTranNo_openAvDev != 0)
																		{
																			if (pTransferAvInfoElem->proxiedTranInfo.ti.audio.uiTranNo_openAvDev != pTransferAvInfo->ass.tranInfo.audio.uiTranNo_openAvDev) bNotMatched = true;
																		}
																		if (pTransferAvInfoElem->proxiedTranInfo.ti.video.uiTranNo_openAvDev != 0)
																		{
																			if (pTransferAvInfoElem->proxiedTranInfo.ti.video.uiTranNo_openAvDev != pTransferAvInfo->ass.tranInfo.video.uiTranNo_openAvDev) bNotMatched = true;
																		}
																		if (!bNotMatched)
																		{
#if __DEBUG__
																		traceLog(_T("findOrgMsgAndProc_mis: get req content"));
#endif
																			PARAM_findOrgMsg* pParam = (PARAM_findOrgMsg*)(IntPtr)p1;
																			if (pParam != null)
																			{
																				if (pParam->pMsgTask_o != null)
																				{
																					int len = (int)((int)Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsgElem->lenInBytes);

																					mymemcpy((IntPtr)pParam->pMsgTask_o, (IntPtr)pMsgElem, (uint)len);
																				}
																			}
																			iErr = 1; goto errLabel;
																		}
																	}
																}
															}
														}
														//  2014/11/21
														if (bApplyForAvProxy(pMisCntElem, ref *pTransferAvInfoElem)
															&& pTransferAvInfo->proxiedTranInfo.idInfo.ui64Id != 0
															&& pTransferAvInfo->proxiedTranInfo.uiObjType != 0)
														{
															if (pTransferAvInfo->proxiedTranInfo.idInfo.ui64Id == pMisCntElem.idInfo.ui64Id)
															{
																if (pTransferAvInfo->proxiedTranInfo.ti.audio.uiTranNo_openAvDev != 0 || pTransferAvInfo->proxiedTranInfo.ti.video.uiTranNo_openAvDev != 0)
																{
																	bool bNotMatched = false;
																	if (pTransferAvInfo->proxiedTranInfo.ti.audio.uiTranNo_openAvDev != 0)
																	{
																		if (pTransferAvInfo->proxiedTranInfo.ti.audio.uiTranNo_openAvDev != pTransferAvInfoElem->ass.tranInfo.audio.uiTranNo_openAvDev) bNotMatched = true;
																	}
																	if (pTransferAvInfo->proxiedTranInfo.ti.video.uiTranNo_openAvDev != 0)
																	{
																		if (pTransferAvInfo->proxiedTranInfo.ti.video.uiTranNo_openAvDev != pTransferAvInfoElem->ass.tranInfo.video.uiTranNo_openAvDev) bNotMatched = true;
																	}
																	if (!bNotMatched)
																	{
#if __DEBUG__
																	traceLog(_T("proxy reply returned"));
#endif
																		PARAM_findOrgMsg* pParam = (PARAM_findOrgMsg*)(IntPtr)p1;
																		if (pParam != null)
																		{
																			if (pParam->bNeedUpdate)
																			{
																				pTaskElem.applyForProxy.bRecvd_proxyReply = true;
																				//
																				pTaskElem.applyForProxy.proxyReply.proxy.uiTranNo_openAvDev_a = pTransferAvInfo->ass.tranInfo.audio.uiTranNo_openAvDev;
																				pTaskElem.applyForProxy.proxyReply.proxy.uiTranNo_openAvDev_v = pTransferAvInfo->ass.tranInfo.video.uiTranNo_openAvDev;
																			}
																		}
																		iErr = 1; goto errLabel;
																	}
																}
															}
														}

													}

													if (pContent->uiType == Consts.CONST_imCommType_transferAvReplyInfo)
													{
														if (pMsgElem->tStartTime == pContent->transferAvReplyInfo.tStartTime_org
															&& pMsgElem->uiTranNo == pContent->transferAvReplyInfo.uiTranNo_org)
														{
															//OutputDebugString(_T("tmpHandler_findOrgMsgAndProc_is . msg - reply is matched\n"));            //  

															old_procTaskAvReply(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, &pTransferAvInfoElem->ass.tranInfo, ref pTaskElem, pMsgTask);

															//
															iErr = 1; goto errLabel;
														}
													}

													//  											 
													if (pContent->uiType == Consts.CONST_imCommType_transferVideoData)
													{                           //  
																				//
														tmpiRet = tmpHandler_findOrgMsgAndProcess_mis_procTaskVideoData(ref ctxCaller,pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgTask, &pContent->transferVideoData, pContentElem, ref pTaskElem);
														if (0 != tmpiRet)
														{
															iErr = tmpiRet; goto errLabel;
														}
													}
													if (pContent->uiType == Consts.CONST_imCommType_transferAudioData)
													{
														//
														tmpiRet = tmpHandler_findOrgMsgAndProcess_mis_procTaskAudioData(ref ctxCaller,pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgTask, &pContent->transferAudioData, pContentElem, ref pTaskElem);
														if (0 != tmpiRet)
														{
															iErr = tmpiRet; goto errLabel;
														}
													}
													if (pContent->uiType == Consts.CONST_imCommType_remoteAssistReq)
													{
														/*
														if (pMsgElem->addr_logicalPeer.idInfo.ui64Id == pMsgTask->addr_logicalPeer.idInfo.ui64Id
															&& pTransferAvInfoElem->tranInfo.video.uiTranNo_openAvDev == pContent->remoteAssistReq.uiTranNo_openAvDev)
														{
#if __DEBUG__
															traceLog(_T("RemoteAssist: "));
#endif

															if (procTaskRemoteAssist(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgTask, &pContent->remoteAssistReq, &pTransferAvInfoElem->tranInfo, pTaskElem, index)) goto errLabel;

															iErr = 1; goto errLabel;
														}
														*/
													}

													if (pContent->uiType == Consts.CONST_imCommType_taskProcReq)
													{   //  file·
														if (pMsgElem->iTaskId != 0 && pMsgElem->iTaskId == pMsgTask->iTaskId)
														{
#if __DEBUG__
														traceLogA("tmpHandler_findOrgMsgAndProc_is: msg - procReq.iTaskId [%d] is matched", pMsgTask->iTaskId);
#endif
															//
															iErr = 1; goto errLabel;
														}

														if (pMsgElem->tStartTime == pContent->taskProcReq.tStartTime_org
															&& pMsgElem->uiTranNo == pContent->taskProcReq.uiTranNo_org)
														{
#if __DEBUG__
														traceLogA("tmpHandler_findOrgMsgAndProc_is: msg - procReq is matched");
#endif
															//
															iErr = 1; goto errLabel;
														}
													}
												}
												else
												{

													//  ÒÔÉÏÎªmedia·¢Æð¶Ë

													//if (pContentElem->uiType == Consts.CONST_imCommType_transferAvReplyInfo)
													{                           //  media»Ø¸´¶Ë
														TASK_transferAv task = (TASK_transferAv)taskElem;
														//TRANSFER_AV_replyInfo* pTransferAvReplyInfoElem = &pContentElem->transferAvReplyInfo;
														TRANSFER_AV_INFO* pTransferAvInfoElem = &pContentElem->transferAvInfo;

														ref PROC_TASK_AV pTaskElem = ref task.myTask;// get_transferAvReplyInfo_pTask(pTransferAvReplyInfoElem, _T(""));
																									 //if (!pTaskElem) goto errLabel;
														int index = 0;

														//  ÒòÎªaudio¶ÔÊµÊ±ÐÔÒªÇó×î¸ß£¬ËùÒÔ·ÅÔÚµÚÒ»Î»±È½Ï
														if (pContent->uiType == Consts.CONST_imCommType_transferAudioData)
														{
															//
															tmpiRet = tmpHandler_findOrgMsgAndProcess_mis_procTaskAudioData(ref ctxCaller,pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgTask, &pContent->transferAudioData, pContentElem, ref pTaskElem);
															if (0 != tmpiRet)
															{
																iErr = tmpiRet; goto errLabel;
															}

														}
														if (pContent->uiType == Consts.CONST_imCommType_transferVideoData)
														{                           //  ¶Ô·½µÄÊý¾Ý
																					//
															tmpiRet = tmpHandler_findOrgMsgAndProcess_mis_procTaskVideoData(ref ctxCaller,pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgTask, &pContent->transferVideoData, pContentElem, ref pTaskElem);
															if (0 != tmpiRet)
															{
																iErr = tmpiRet; goto errLabel;
															}

														}

														if (pContent->uiType == Consts.CONST_imCommType_transferAvInfo)
														{       //  ÖØ·¢Ê±ÕâÀïÒªÐ£ÑéµÄ
															if (pMsgElem->data.route.idInfo_to.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id
																&& pContentElem->transferAvReplyInfo.tStartTime_org == pMsgTask->tStartTime
																&& pContentElem->transferAvReplyInfo.uiTranNo_org == pMsgTask->uiTranNo)
															{
																//
#if __DEBUG__
														traceLogA("tmpHandler_findOrgMsgAndProc_is: msg - req is matched");
#endif
																//
																iErr = 1; goto errLabel;
															}
														}
														if (pContent->uiType == Consts.CONST_imCommType_transferAvReplyInfo)
														{                           //  ´¦Àí
															if(pMsgElem->tStartTime== pContent->transferAvReplyInfo.tStartTime_org
																&& pMsgElem->uiTranNo==pContent->transferAvReplyInfo.uiTranNo_org )
															//if (pContentElem->transferAvReplyInfo.tStartTime_org == pContent->transferAvReplyInfo.tStartTime_org
															//	&& pContentElem->transferAvReplyInfo.uiTranNo_org == pContent->transferAvReplyInfo.uiTranNo_org)
															{
																//
#if DEBUG
														traceLogA("tmpHandler_findOrgMsgAndProc_is . msg - avReplyInfo matched.");
#endif
																//
																iErr = 1; goto errLabel;
															}
														}
														if (pContent->uiType == Consts.CONST_imCommType_taskProcReq)
														{   //  
															if (pContentElem->transferAvReplyInfo.tStartTime_org == pContent->taskProcReq.tStartTime_org
																&& pContentElem->transferAvReplyInfo.uiTranNo_org == pContent->taskProcReq.uiTranNo_org)
															{
																//
#if __DEBUG__
														traceLogA("tmpHandler_findOrgMsgAndProc_is: msg - procReq is matched");
#endif
																//
																iErr = 1; goto errLabel;
															}
														}

													}  //  ÒÔÉÏÎªmedia»Ø¸´¶Ë¡£
												}
											}
											//  2012/04/19
											if (pContentElem->uiType == Consts.CONST_imCommType_transferGpsInfo)
											{                               //  media·¢Æð¶Ë
												/*
												TRANSFER_GPS_INFO* pTransferGpsInfoElem = &pContentElem->transferGpsInfo;
												int index = 0;

												if (pContent->uiType == CONST_imCommType_transferGpsInfo)
												{                               //  ¶ÔÓÚÆ´½ÓÍ¼ÏóÀ´Ëµ£¬ÓÃÍ¬ÑùµÄtStartTimeºÍuiTranNo¿ÉÒÔ°ÑÆ´½ÓrgbºÍÑ¹Ëõ¸ñÊ½¿¼Èë
													if (pMsgElem->tStartTime == pMsgTask->tStartTime
														&& pMsgElem->uiTranNo == pMsgTask->uiTranNo)
													{
														iErr = 1; goto errLabel;
													}
												}

												//											 			
												if (pContent->uiType == CONST_imCommType_transferGpsReplyInfo)
												{
													if (pMsgElem->tStartTime == pContent->transferGpsReplyInfo.tStartTime_org
														&& pMsgElem->uiTranNo == pContent->transferGpsReplyInfo.uiTranNo_org)
													{
														OutputDebugString(_T("tmpHandler_findOrgMsgAndProc_is . msg - gpsReply is matched\n"));         //  »Ø¸´´¦ÀíÊ±

														//
														iErr = 1; goto errLabel;
													}
												}

												//
												if (pContent->uiType == CONST_imCommType_transferGpsData)
												{       //  2012/04/20
													if (pMsgElem->addr_logicalPeer.idInfo.ui64Id == pMsgTask->addr_logicalPeer.idInfo.ui64Id)
													{
														//

														//  2012/05/07
														tmpiRet = tmpHandler_findOrgMsgAndProcess_mis_procTaskGpsData(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgTask, &pContent->transferGpsData, null, &pTransferGpsInfoElem->myTask);

														//
														iErr = 1; goto errLabel;
													}
												}
												*/
												//
											}

										}
										//
									}
									break;
								case Consts.CONST_misMsgType_input:
									{
										MIS_MSG_INPUT* pMsgInput = &pMsg_toBeSearched->input;
										IM_CONTENTU* pContent = M_getMsgContent(pMsgInput->ucFlg, &pMsgInput->data);
										//
										//if (pMsgInput->pMisCnt != pMisCntElem) break;

										//									 
#if DEBUG   //  2014/08/28
										ref IM_CONTENTU tmp_pContent = ref *pContent;


										if (pContent->uiType == Consts.CONST_imCommType_taskProcReq)
										{
											if (pContent->taskProcReq.usOp == Consts.CONST_imOp_recv_applyForKeyFrame)
											{
												int i;
												i = 9;
											}
											if ( pContent->taskProcReq.usOp==Consts.CONST_imOp_recv_applyForOrgReq)
                                            {
												int i;
												i = 9;
                                            }
										}
#endif

										//
										if (isUcFlgResp(pMsgInput->ucFlg) && !isUcFlgResp(pMsgElem->ucFlg))
										{   //  ½ÓÊÕÎÄ¼þµÄ´¦Àí
											switch (pContentElem->uiType)
											{
												case Consts.CONST_imCommType_transferAvInfo:
													{
														if (!pTaskInfo.var.m_bReplyTask)
														{
															TRANSFER_AV_INFO* pTransferAvInfoElem = &pContentElem->transferAvInfo;
															TASK_transferAv task = (TASK_transferAv)taskElem;
															ref PROC_TASK_AV pTaskElem = ref task.myTask;// get_transferAvInfo_pTask(pTransferAvInfoElem, _T(""));
																										 //if (!pTaskElem) goto errLabel;
																										 //
															if (pContent->uiType == Consts.CONST_imCommType_transferVideoDataResp)
															{
																tmpiRet = tmpHandler_find_procTaskVideoDataResp(pProcInfo, pMsgElem, pMsgInput, &pContent->transferVideoDataResp);
																if (0 != tmpiRet)
																{
																	iErr = tmpiRet; goto errLabel;
																}
															}
															if (pContent->uiType == Consts.CONST_imCommType_transferAudioDataResp)
															{
																if (pMsgElem->data.route.idInfo_from.ui64Id == pMsgInput->data.route.idInfo_to.ui64Id
																	&& pTransferAvInfoElem->ass.tranInfo.audio.uiTranNo_openAvDev == pContent->transferAudioDataResp.uiTranNo_openAvDev)
																{
																	//  OutputDebugString(  _T(  "AudioData Resp, ½«µ÷ÕûÒôÆµ·¢ËÍÆµÂÊ\n"  )  );

																	if (0 != procTaskAudioDataResp(pProcInfo, &pTransferAvInfoElem->ass.tranInfo, ref pTaskElem, pMsgInput, &pContent->transferAudioDataResp)) goto errLabel;

																	iErr = 1; goto errLabel;
																}
															}
															//
														}
														else
														{
															//case Consts.CONST_imCommType_transferAvReplyInfo:
															TASK_transferAv task = (TASK_transferAv)taskElem;
															TRANSFER_AV_replyInfo* pTransferAvReplyInfoElem1 = &pContentElem->transferAvReplyInfo;
															ref PROC_TASK_AV pTaskElem = ref task.myTask;// get_transferAvReplyInfo_pTask(pTransferAvProcInfoElem, _T(""));
																										 //if (!pTaskElem) goto errLabel;
															AV_TRAN_INFO tmp_avTranInfo = pTaskElem.reply_avTranInfo;
															AV_TRAN_INFO* pAvTranInfoElem = &tmp_avTranInfo;// &pTransferAvReplyInfoElem1->tranInfo;
																										 
															//
															if (pContent->uiType == Consts.CONST_imCommType_transferVideoDataResp)
															{
																tmpiRet = tmpHandler_find_procTaskVideoDataResp(pProcInfo, pMsgElem, pMsgInput, &pContent->transferVideoDataResp);
																if (0 != tmpiRet)
																{
																	iErr = tmpiRet; goto errLabel;
																}
															}
															if (pContent->uiType == Consts.CONST_imCommType_transferAudioDataResp)
															{
																if (pMsgElem->data.route.idInfo_to.ui64Id == pMsgInput->data.route.idInfo_from.ui64Id
																	&& pAvTranInfoElem->audio.uiTranNo_openAvDev == pContent->transferAudioDataResp.uiTranNo_openAvDev)
																{
																	//  OutputDebugString(  _T(  "AudioDataResp, ½«µ÷ÕûÒôÆµ·¢ËÍÆµÂÊ\n"  )  );

																	if (0 != procTaskAudioDataResp(pProcInfo, pAvTranInfoElem, ref pTaskElem, pMsgInput, &pContent->transferAudioDataResp)) goto errLabel;

																	iErr = 1; goto errLabel;
																}
															}
															//
														}
													}
													break;
												case Consts.CONST_imCommType_transferGpsInfo:
													{
														/*
														TRANSFER_GPS_INFO* pTransferGpsInfoElem = &pContentElem->transferGpsInfo;
														if (pContent->uiType == CONST_imCommType_transferGpsDataResp)
														{
															if (pMsgElem->data.route.idInfo_from.ui64Id == pMsgInput->data.route.idInfo_to.ui64Id)
															{
																//
#if __DEBUG__
																traceLog(_T("findOrgMsgAndprocess: gpsDataResp"));
#endif
																if (procTaskGpsDataResp(pProcInfo, null, &pTransferGpsInfoElem->myTask, pMsgInput, &pContent->transferGpsDataResp)) goto errLabel;
																//
																iErr = 1; goto errLabel;
															}
														}
														*/
													}
													break;
												default:
													break;
											}

											if (pMsgInput->tStartTime == pMsgElem->tStartTime
												&& pMsgInput->uiTranNo == pMsgElem->uiTranNo)
											{
												traceLogA("");

												/*
												if (p1!=null
													&& pContentElem->uiType == Consts.CONST_imCommType_transferFileReplyReq
													   && pContent->uiType == Consts.CONST_imCommType_simpleResp
														   && pContent->simpleResp.uiContentType_org == pContentElem->uiType)
												{
													TRANSFER_FILE_REPLYREQ* pFileReplyReq = &pContentElem->transferFileReplyReq;
													TRANSFER_FILEDATA_REQ* pFileDataReq_o = (TRANSFER_FILEDATA_REQ*)(IntPtr)p1;

													if (null==pFileDataReq_o || 0==pFileReplyReq->ui64FileLen || 0==pFileReplyReq->uiSizePerSnd_internal)
													{
#if __DEBUG__
														traceLogA("tmpHandler_findOrgMsgAndProc_is failed: Ð£ÑéÌõ¼þ²»Âú×ã1");
#endif
														goto errLabel;
													}

													//  ÏÈ½«uiSizePerSndºÍÇëÇó±êÊ¶¸ø¸³ÉÏdataReq
													pFileDataReq_o->uiSizePerSnd = pFileReplyReq->uiSizePerSnd_internal;
													pFileDataReq_o->tStartTime_org = pFileReplyReq->tStartTime_org;
													pFileDataReq_o->uiTranNo_org = pFileReplyReq->uiTranNo_org;
													pFileDataReq_o->uiSerialNo_org = pFileReplyReq->uiSerialNo_org;
													//
													pFileDataReq_o->uiDataBlockIndex = 0;   //  Õâ±íÃ÷ÊÇ´ÓÍ·¿ªÊ¼

													iErr = 1; goto errLabel;

												}

												if (p1!=null
													&& pContentElem->uiType == Consts.CONST_imCommType_transferFileReplyReq
													   && pContent->uiType == Consts.CONST_imCommType_transferFileDataResp)
												{
													TRANSFER_FILE_REPLYREQ* pFileReplyReq = &pContentElem->transferFileReplyReq;
													TRANSFER_FILEDATA_RESP* pFileDataResp = &pContent->transferFileDataResp;
													IM_CONTENTU* pContent_o = (IM_CONTENTU*)(IntPtr)p1;
													UInt64 ui64offset = 0;
													int nWrite = 0;

													if (null==pContent_o || 0==pFileReplyReq->ui64FileLen || 0==pFileReplyReq->uiSizePerSnd_internal || Consts.bufSize_transferFileDataResp  < pFileReplyReq->uiSizePerSnd_internal  )  {
#if __DEBUG__
														traceLogA("tmpHandler_findOrgMsgAndProc_is failed: ");
#endif
														goto errLabel;
													}

													if (pContent_o->uiType == Consts.CONST_imCommType_transferFileEndReq)
													{
														TRANSFER_FILEEND_REQ* pFileEndReq_o = &pContent_o->transferFileEndReq;

														//  2015/09/08
														if (pFileEndReq_o->tmpInternal_bChkToRemove_i)
														{
															pFileReplyReq->myTask.bNeedRemoved = true;
															//  2015/09/08
															pFileEndReq_o->tmpInternal_bNeedRemoved_o = true;
														}

														//  
														pFileEndReq_o->tStartTime_org = pFileReplyReq->tStartTime_org;
														pFileEndReq_o->uiTranNo_org = pFileReplyReq->uiTranNo_org;
														pFileEndReq_o->uiSerialNo_org = pFileReplyReq->uiSerialNo_org;

														iErr = 1; goto errLabel;
													}

													if (pContent_o->uiType == Consts.CONST_imCommType_transferFileDataReq)
													{

														TRANSFER_FILEDATA_REQ* pFileDataReq_o = &pContent_o->transferFileDataReq;

														//  ÏÈ½«uiSizePerSndºÍÇëÇó±êÊ¶¸ø¸³ÉÏdataReq
														pFileDataReq_o->uiSizePerSnd = pFileReplyReq->uiSizePerSnd_internal;
														pFileDataReq_o->tStartTime_org = pFileReplyReq->tStartTime_org;
														pFileDataReq_o->uiTranNo_org = pFileReplyReq->uiTranNo_org;
														pFileDataReq_o->uiSerialNo_org = pFileReplyReq->uiSerialNo_org;


														//
#if __DEBUG__
														//qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "pFileDataResp->uiDataBlockIndex %d"  ),  pFileDataResp->uiDataBlockIndex  );															 
#endif


														//
														{    //  2009/10/20. check whether resp is ok												 
															bool bRespOk = true;
															if (0==pFileDataResp->uiDataBlockIndex)
															{
																if (0!=pFileReplyReq->uiLastDataBlockIndex) bRespOk = false;
															}
															else
															{
																if (pFileDataResp->uiDataBlockIndex != pFileReplyReq->uiLastDataBlockIndex + 1) bRespOk = false;
															}
															if (!bRespOk)
															{
																//
#if __DEBUG__
																traceLogA("pFileDataResp->uiDataBlockIndex err");
#endif
																//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""),_T("Err: pFileDataResp->uiDataBlockIndex %d, fileReplyReq.uiLastDataBlockIndex %d"),pFileDataResp->uiDataBlockIndex, pFileReplyReq->uiLastDataBlockIndex);
																//															 
																pFileReplyReq->usErrors++;
																//
																goto errLabel;
															}
														}


														ui64offset = ((UInt64)pFileDataResp->uiDataBlockIndex) * pFileReplyReq->uiSizePerSnd_internal;
														if (ui64offset >= pFileReplyReq->ui64FileLen)
														{
															//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("ui64offset >= pFileReplyReq->ui64FileLen err"));
															goto errLabel;
														}

														
														 
														//  ÕâÀïÎª½«µÃµ½µÄÊý¾Ý±£´æ³ÉÎÄ¼þ
														if (null==pFileReplyReq->fp)
														{
															
															//TCHAR tmpFilePath[MAX_PATH + 1] = _T("");
															TMP_filePath tmpFilePath;
															//
															_sntprintf(tmpFilePath, mycountof(tmpFilePath), _T("%s.tmp"), pFileReplyReq->fullFilePath_save);
															//
															pFileReplyReq->fp = _tfopen(tmpFilePath, _T("wb"));
															if (!pFileReplyReq->fp)
															{
#if __DEBUG__
																traceLogA("ÎÄ¼þ½¨Á¢Ê§°Ü");
#endif
																goto errLabel;
															}
															//
															pFileReplyReq->dwStartTickCnt = GetTickCount();
															pFileReplyReq->dwLastReportTickCnt = pFileReplyReq->dwStartTickCnt;
															pFileReplyReq->ucPercent = 0;
															//
															//  
															//
															showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, false, CONST_imCommType_transferFileReq, pMsgElem->iTaskId, CONST_imTaskStatus_receiving, 0, 0, null, null);
															
														}

														//  
														//  if  (  fseek(  pFileReplyReq->fp,  (  long  )ui64offset,  SEEK_SET  )  )  
														if (my_fseeki64(pFileReplyReq->fp, ui64offset, SEEK_SET))
														{
															traceLogA("tmpHandler_findOrgMsgAndProc_is failed:  _fseeki64 err");
															qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("_fseeki64 err"));
															goto errLabel;
														}

														nWrite = (int)min(pFileReplyReq->ui64FileLen - ui64offset, pFileReplyReq->uiSizePerSnd_internal);
														if (pFileDataResp->uiLen != nWrite)
														{
															traceLogA("pFileDataResp->uiLen  !=  nWrite");
															qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("pFileDataResp->uiLen!=nWrite err,%d,%I64u,%I64u,%d,%d"), nWrite, pFileReplyReq->ui64FileLen, ui64offset, pFileReplyReq->uiSizePerSnd_internal, pFileDataResp->uiLen);
															goto errLabel;
														}

														if (1 != fwrite(pFileDataResp->buf, pFileDataResp->uiLen, 1, pFileReplyReq->fp))
														{
															traceLogA("fwite failed");
															qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("fwite err"));
															goto errLabel;
														}

														//
														pFileReplyReq->uiLastDataBlockIndex = pFileDataResp->uiDataBlockIndex;


														//  
														uint dwCurTickCnt;
														//
														dwCurTickCnt = GetTickCount();
														if (dwCurTickCnt > pFileReplyReq->dwLastReportTickCnt + 3000)
														{   //  
															pFileReplyReq->dwLastReportTickCnt = dwCurTickCnt;
															//
															float f = 0;
															byte ucPercent;
															//
															f = (float)pFileReplyReq->uiLastDataBlockIndex * pFileReplyReq->uiSizePerSnd_internal;
															f = f / pFileReplyReq->ui64FileLen;
															ucPercent = (byte  )(f * 100);

															//  if  (  ucPercent  !=  pFileReplyReq->ucPercent  )  
															{   //  ±¨¸æ×´Ì¬

																showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, false, CONST_imCommType_transferFileReq, pMsgElem->iTaskId, CONST_imTaskStatus_receiving, ucPercent, pFileReplyReq->uiLastDataBlockIndex * pFileReplyReq->uiSizePerSnd_internal, null, null);

															}
														}


														pFileDataReq_o->uiDataBlockIndex = pFileReplyReq->uiLastDataBlockIndex + 1;


														if (pFileDataReq_o->uiDataBlockIndex * pFileReplyReq->uiSizePerSnd_internal >= pFileReplyReq->ui64FileLen)
														{
															//  Òª°ÑÁÙÊ±ÎÄ¼þÒÆ³ÉÕýÊ½ÎÄ¼þ
															//TCHAR tmpFilePath[MAX_PATH + 1] = _T("");
															TMP_filePath tmpFilePath;
															//
															//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("all file data received. to copyfile"));
															//
															if (pFileReplyReq->fp)
															{
#if __DEBUG__
																traceLogA("tmpHandler_findOrgMsgAndProc_is: before fclose");
#endif
																fclose(pFileReplyReq->fp); pFileReplyReq->fp = null;
#if __DEBUG__
																traceLogA("tmpHandler_findOrgMsgAndProc_is: after fclose");
#endif
															}
															//
															_sntprintf(tmpFilePath, mycountof(tmpFilePath), _T("%s.tmp"), pFileReplyReq->fullFilePath_save);
															//
															if (!myCopyFile(tmpFilePath, pFileReplyReq->fullFilePath_save, false))
															{
																//TCHAR tBuf[256] = _T("");
#if __DEBUG__
																traceLog(_T("CopyFile %s->%s failed"), tmpFilePath, pFileReplyReq->fullFilePath_save);
#endif
																//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("copyfile failed. %s->%s"), tmpFilePath, pFileReplyReq->fullFilePath_save);
																//_sntprintf(tBuf, mycountof(tBuf), _T("Copy failed. %s"), pFileReplyReq->fileName_transferred);
																str= string.Format("Copy failed. {0}", new string(pFileReplyReq->fileName_transferred));
																showNotification(0, 0, 0, 0, 0, 0, str);
																goto errLabel;
															}
															myDeleteFile(tmpFilePath);

															{
																void* pDb = null;
																CQnmDb db;
																if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys)) goto errLabel;
																pDb = db.m_pDbMem->pDb;

																if (g_dbFuncs.pf_updateTaskStatus(pDb, CONST_imTaskStatus_recvFinished, pMsgElem->iTaskId)) goto errLabel;
															}

															showTaskStatus(pMsgElem->pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, false, CONST_imCommType_transferFileReq, pMsgElem->iTaskId, CONST_imTaskStatus_recvFinished, 100, pFileReplyReq->ui64FileLen, pFileReplyReq->fileName_transferred, pFileReplyReq->fullFilePath_save);

															//
															pFileDataReq_o->ucbFileEnd = true;
															traceLogA("bFileEnd is true");

															//
															qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Transfering file ends."));

														
														}
														

														iErr = 1; goto errLabel;
													}

													traceLogA("");

												}

												*/

												/////////////////////////
												iErr = 1; goto errLabel;
											}
										}
										if (!isUcFlgResp(pMsgInput->ucFlg) && !isUcFlgResp(pMsgElem->ucFlg))
										{
                                            switch (pContentElem->uiType)
                                            {
													case Consts.CONST_imCommType_transferAvInfo:
													{
														if (!pTaskInfo.var.m_bReplyTask)
														{
															TRANSFER_AV_INFO* pTransferAvInfoElem = &pContentElem->transferAvInfo;
															TASK_transferAv task = (TASK_transferAv)taskElem;
															ref PROC_TASK_AV pTaskElem = ref task.myTask;// get_transferAvInfo_pTask(pTransferAvInfoElem, _T(""));

															if (pContent->uiType == Consts.CONST_imCommType_transferAvReplyInfo)
															{
																if (pMsgElem->tStartTime == pContent->transferAvReplyInfo.tStartTime_org
																	&& pMsgElem->uiTranNo == pContent->transferAvReplyInfo.uiTranNo_org)
																{
																	//OutputDebugString(_T("tmpHandler_findOrgMsgAndProc_is . msg - reply is matched\n"));            //  

																	procTaskAvReply(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, &pTransferAvInfoElem->ass.tranInfo, ref pTaskElem, pMsgInput);

																	//
																	iErr = 1; goto errLabel;
																}
															}
															if (pContent->uiType == Consts.CONST_imCommType_transferVideoData)
															{                           //  
																						//
																tmpiRet = tmpHandler_findOrgMsgAndProcess_mis_procInputVideoData(ctxCaller,pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgInput, &pContent->transferVideoData, pContentElem, ref pTaskElem);
																if (0 != tmpiRet)
																{
																	iErr = tmpiRet; goto errLabel;
																}
															}
															//////////////////////////
															///
															if (pContent->uiType == Consts.CONST_imCommType_transferAudioData)
															{
																//
																tmpiRet = tmpHandler_findOrgMsgAndProcess_mis_procInputAudioData(ctxCaller,pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgInput, &pContent->transferAudioData, pContentElem, ref pTaskElem);
																if (0 != tmpiRet)
																{
																	iErr = tmpiRet; goto errLabel;
																}
															}

														}
                                                        else { 
														//case Consts.CONST_imCommType_transferAvReplyInfo:
														//if (pContentElem->uiType == Consts.CONST_imCommType_transferAvReplyInfo)
														                           //  media»Ø¸´¶Ë
															TASK_transferAv task = (TASK_transferAv)taskElem;
															//TRANSFER_AV_replyInfo* pTransferAvReplyInfoElem = &pContentElem->transferAvReplyInfo;
															ref PROC_TASK_AV pTaskElem = ref task.myTask;// get_transferAvReplyInfo_pTask(pTransferAvReplyInfoElem, _T(""));
																										 //if (!pTaskElem) goto errLabel;
															int index = 0;

															//  ÒòÎªaudio¶ÔÊµÊ±ÐÔÒªÇó×î¸ß£¬ËùÒÔ·ÅÔÚµÚÒ»Î»±È½Ï
															if (pContent->uiType == Consts.CONST_imCommType_transferAudioData)
															{
																//
																tmpiRet = tmpHandler_findOrgMsgAndProcess_mis_procInputAudioData(ctxCaller,pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgInput, &pContent->transferAudioData, pContentElem, ref pTaskElem);
																if (0 != tmpiRet)
																{
																	iErr = tmpiRet; goto errLabel;
																}

															}
															if (pContent->uiType == Consts.CONST_imCommType_transferVideoData)
															{                           //  ¶Ô·½µÄÊý¾Ý
																						//
																tmpiRet = tmpHandler_findOrgMsgAndProcess_mis_procInputVideoData(ctxCaller,pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgInput, &pContent->transferVideoData, pContentElem, ref pTaskElem);
																if (0 != tmpiRet)
																{
																	iErr = tmpiRet; goto errLabel;
																}

															}

															if (pContent->uiType == Consts.CONST_imCommType_transferAvInfo)
															{       //  ÖØ·¢Ê±ÕâÀïÒªÐ£ÑéµÄ
																if (pMsgElem->data.route.idInfo_to.ui64Id == pMsgInput->data.route.idInfo_from.ui64Id
																	&& pContentElem->transferAvReplyInfo.tStartTime_org == pMsgInput->tStartTime
																	&& pContentElem->transferAvReplyInfo.uiTranNo_org == pMsgInput->uiTranNo)
																{
																	//
#if __DEBUG__
														traceLogA("tmpHandler_findOrgMsgAndProc_is: msg - req is matched");
#endif
																	//
																	iErr = 1; goto errLabel;
																}
															}
															if (pContent->uiType == Consts.CONST_imCommType_transferAvReplyInfo)
															{                           //  ´¦Àí
																if (pContentElem->transferAvReplyInfo.tStartTime_org == pContent->transferAvReplyInfo.tStartTime_org
																	&& pContentElem->transferAvReplyInfo.uiTranNo_org == pContent->transferAvReplyInfo.uiTranNo_org)
																{
																	//
#if __DEBUG__
														traceLogA("tmpHandler_findOrgMsgAndProc_is . msg - procReq matched.");
#endif
																	//
																	iErr = 1; goto errLabel;
																}
															}
															if (pContent->uiType == Consts.CONST_imCommType_taskProcReq)
															{   //
																//
																if(pMsgElem->tStartTime==pContent->taskProcReq.tStartTime_org
																	&&pMsgElem->uiTranNo==pContent->taskProcReq.uiTranNo_org )
																//if (pContentElem->transferAvReplyInfo.tStartTime_org == pContent->taskProcReq.tStartTime_org
																	//&& pContentElem->transferAvReplyInfo.uiTranNo_org == pContent->taskProcReq.uiTranNo_org)
																{
																	//
#if DEBUG
																	traceLogA("tmpHandler_findOrgMsgAndProc_is: msg - procReq is matched");
#endif
																	//
																	iErr = 1; goto errLabel;
																}
															}

														}  //  ÒÔÉÏÎªmedia»Ø¸´¶Ë¡£
													}
													break;
												default:
													break;

                                            }
											
											//  ·¢ËÍÎÄ¼þ
											switch (pContent->uiType)
											{
												/*
												case Consts.CONST_imCommType_transferFileDataReq:
													if (pContentElem->uiType == Consts.CONST_imCommType_transferFileReq
														&& pContent->transferFileDataReq.tStartTime_org == pMsgElem->tStartTime
															 && pContent->transferFileDataReq.uiTranNo_org == pMsgElem->uiTranNo)
													{
														TRANSFER_FILE_REQ* pFileReq = &pContentElem->transferFileReq;
														TRANSFER_FILEDATA_REQ* pFileDataReq = &pContent->transferFileDataReq;
														TRANSFER_FILEDATA_RESP* pFileDataResp_o = (TRANSFER_FILEDATA_RESP*)(IntPtr)p1;
														UInt64 ui64offset = 0;
														int nRead = 0;

														if (null==pFileDataResp_o || 0==pFileReq->ui64FileLen || 0==pFileDataReq->uiSizePerSnd || Consts.bufSize_transferFileDataResp  < pFileDataReq->uiSizePerSnd  )  {
#if __DEBUG__
															traceLogA("tmpHandler_findOrgMsgAndProc_is failed: sizeof(  buf  )  <  uiSizePerSnd");
#endif
															//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("findOrgMsg error: fileDataReq, sizeof(  buf  ) %d < sizePerSnd [%d]"), sizeof(pFileDataResp_o->buf),  pFileDataReq->uiSizePerSnd  );
															goto errLabel;
														}

														ui64offset = ((UInt64)pFileDataReq->uiDataBlockIndex) * pFileDataReq->uiSizePerSnd;
														if (ui64offset >= pFileReq->ui64FileLen)
														{
#if __DEBUG__
															traceLog(_T("findOrgMsg error: fileDataReq, blockIndex [%d] * sizePerSnd [%d] > fileLen [%I64u]"), pFileDataReq->uiDataBlockIndex, pFileDataReq->uiSizePerSnd, pFileReq->ui64FileLen);
#endif
															//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("findOrgMsg error: fileDataReq, blockIndex [%d] * sizePerSnd [%d] > fileLen [%I64u]"), pFileDataReq->uiDataBlockIndex, pFileDataReq->uiSizePerSnd, pFileReq->ui64FileLen);
															goto errLabel;
														}


														//  ÕâÀï¼ÆËãÒ»ÏÂÒÑ¾­·¢ËÍµÄ°Ù·Ö±È
														uint dwCurTickCnt;
														//
														dwCurTickCnt = myGetTickCount();
														if (dwCurTickCnt > pFileReq->dwLastReportTickCnt + 3000)
														{   //  ÎªÁË²»Ó°Ïì½çÃæ²Ù×÷£¬Òª¹ý3Ãë²ÅÄÜ¼ÆËãÒ»´Î
															pFileReq->dwLastReportTickCnt = dwCurTickCnt;
															//
															float f = 0;
															byte ucPercent;
															//
															f = (float)pFileDataReq->uiDataBlockIndex * pFileDataReq->uiSizePerSnd;
															f = f / pFileReq->ui64FileLen;
															ucPercent = (byte  )(f * 100);

															//  if  (  ucPercent  !=  pFileReq->ucPercent  )  
															{   //  ±¨¸æ×´Ì¬

																showTaskStatus(pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, false, Consts.CONST_imCommType_transferFileReq, pMsgElem->iTaskId, Consts.CONST_imTaskStatus_sending, ucPercent, pFileDataReq->uiDataBlockIndex * pFileDataReq->uiSizePerSnd, null, null);

															}
														}

#if __DEBUG__
														traceLogA("");
#endif

														if (null==pContentElem->transferFileReq.fp)
														{
															pContentElem->transferFileReq.fp = _tfopen(pContentElem->transferFileReq.fullFilePath, _T("rb"));
															if (!pContentElem->transferFileReq.fp)
															{
#if __DEBUG__
																traceLogA("tmpHandler_findOrgMsgAndProc_is failed: _tfopen {%S} err", pContentElem->transferFileReq.fullFilePath);
#endif
																goto errLabel;
															}
														}
														//  ÕâÀïÓ¦¸ÃÓÃ64Î»µÄ²Ù×÷ÒÔ¿ÉÒÔ²Ù×÷´óÎÄ¼þ£¬µ«ÊÇÔÝÊ±ÏÈÓÃ32Î»µÄ
														//  if  (  fseek(  pFileReq->fp,  (  long  )ui64offset,  SEEK_SET  )  )  
														if (_fseeki64(pFileReq->fp, ui64offset, SEEK_SET))
														{
#if __DEBUG__
															traceLogA("tmpHandler_findOrgMsgAndProc_is failed:  _fseeki64 err");
#endif
															goto errLabel;
														}
														nRead = (int)min(pFileReq->ui64FileLen - ui64offset, pFileDataReq->uiSizePerSnd);
														if (1 != fread(pFileDataResp_o->buf, nRead, 1, pFileReq->fp)) goto errLabel;
														pFileDataResp_o->uiLen = nRead;
														//
														pFileDataResp_o->uiDataBlockIndex = pFileDataReq->uiDataBlockIndex;

														iErr = 1; goto errLabel;
													}
													break;
												case Consts.CONST_imCommType_transferFileEndReq:
													if (pContentElem->uiType == Consts.CONST_imCommType_transferFileReq                    //  ·¢ËÍ·½´¦Àí
														&& pContent->transferFileEndReq.tStartTime_org == pMsgElem->tStartTime
															 && pContent->transferFileEndReq.uiTranNo_org == pMsgElem->uiTranNo)
													{
														IM_CONTENTU* pContent_o = (IM_CONTENTU*)(IntPtr)p1;
														int iStatus = Consts.CONST_imTaskStatus_sendFinished;
														//
#if __DEBUG__
														traceLogA("transferFileEnd ");
#endif
														//
														if (pContent_o!=null)
														{
															if (pContent_o->uiType == Consts.CONST_imCommType_transferFileEndResp)
															{
																TRANSFER_FILEEND_RESP* pFileEndResp_o = &pContent_o->transferFileEndResp;
																//														   
																if (!pContentElem->transferFileReq.bGrpTask)
																{
																	//  2015/09/08
																	if (pFileEndResp_o->tmpInternal_bChkToRemove_i)
																	{
																		pContentElem->transferFileReq.myTask.bNeedRemoved = true;
																		//
																		pFileEndResp_o->tmpInternal.bNeedRemoved_o = true;
																	}
																	//
																	object pDb = null;
																	using (CQnmDb db = new CQnmDb())
																	{
																		;

																		if (null==db.getAvailableDb(pQyMc.iDsnIndex_mainSys)) goto errLabel;
																		pDb = db.m_pDbMem.pDb;
																		if (0!=g_dbFuncs.pf_updateTaskStatus(pDb, iStatus, pMsgElem->iTaskId)) goto errLabel;
																	}
																	//
																	showTaskStatus(pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgElem->idInfo_taskReceiver, false, Consts.CONST_imCommType_transferFileReq, pMsgElem->iTaskId, iStatus, 100, pContentElem->transferFileReq.ui64FileLen, new string(pContentElem->transferFileReq.fullFilePath), new string(pContentElem->transferFileReq.fullFilePath));

																}
																else
																{   //  ¶Ô·Ö×é£¬ÓÐÊ²Ã´ÈËÊÕµ½ÁËÎÄ¼þ£¬Ò²ÏÔÊ¾Ò»ÏÂ
																	showTaskStatus(pMisCnt, &pMsgElem->addr_logicalPeer.idInfo, &pMsgElem->idInfo_taskSender, &pMsgInput->addr_logicalPeer.idInfo, true, Consts.CONST_imCommType_transferFileReq, pMsgElem->iTaskId, iStatus, 100, pContentElem->transferFileReq.ui64FileLen, pContentElem->transferFileReq.fullFilePath, pContentElem->transferFileReq.fullFilePath);

																}

															}
														}
														//
														iErr = 1; goto errLabel;
													}
													break;
												*/
												case Consts.CONST_imCommType_taskProcReq:
													if (pContentElem->uiType == Consts.CONST_imCommType_transferFileReplyReq       //  ½ÓÊÕ·½´¦Àí
														&& pContent->taskProcReq.tStartTime_org == pContentElem->transferFileReplyReq.tStartTime_org
															 && pContent->taskProcReq.uiTranNo_org == pContentElem->transferFileReplyReq.uiTranNo_org)
													{
														IM_CONTENTU* pContent_o = (IM_CONTENTU*)(IntPtr)p1;
														int iStatus = Consts.CONST_imTaskStatus_canceledBySender;
														//	
#if __DEBUG__
														traceLogA("transferFileProcReq ");
#endif
														//
														if (pContent_o!=null)
														{
															if (pContent_o->uiType == Consts.CONST_imCommType_taskProcResp)
															{
																TASK_PROC_RESP* pFileProcResp = &pContent_o->taskProcResp;

																pFileProcResp->bNeedRemoved = true;

																//									
																object pDb = null;
																using (CQnmDb db = new CQnmDb())
																{
																	;

																	if (null==db.getAvailableDb(pQyMc.iDsnIndex_mainSys)) goto errLabel;
																	pDb = db.m_pDbMem.pDb;
																	if (0!=g_dbFuncs.pf_updateTaskStatus(pDb, iStatus, pMsgElem->iTaskId)) goto errLabel;
																}
																//
																showTaskStatus(pMisCnt, pMsgElem->addr_logicalPeer.idInfo, pMsgElem->idInfo_taskSender, null,false, Consts.CONST_imCommType_transferFileReq, pMsgElem->iTaskId, iStatus, 0, pContentElem->transferFileReplyReq.ui64FileLen, new string(pContentElem->transferFileReplyReq.fileName_transferred), new string(pContentElem->transferFileReplyReq.fullFilePath_save));
															}
														}
														//
														iErr = 1; goto errLabel;
													}
													if (pContentElem->uiType == Consts.CONST_imCommType_transferFileReq)
													{       //  ·¢ËÍ·½´¦Àí
														if (pContent->taskProcReq.tStartTime_org == pMsgElem->tStartTime
															&& pContent->taskProcReq.uiTranNo_org == pMsgElem->uiTranNo)
														{
															IM_CONTENTU* pContent_o = (IM_CONTENTU*)(IntPtr)p1;
															int iStatus = Consts.CONST_imTaskStatus_canceledByReceiver;
															//
#if __DEBUG__
															traceLogA("tmpHandler_findOrgMsgAndProc_is: msg - procReq found");
#endif
															//
															if (pContent_o!=null)
															{
																if (pContent_o->uiType == Consts.CONST_imCommType_taskProcResp)
																{
																	TASK_PROC_RESP* pFileProcResp = &pContent_o->taskProcResp;

																	if (!pContentElem->transferFileReq.bGrpTask)
																	{
																		pFileProcResp->bNeedRemoved = true;

																		//
																		object pDb = null;
																		using (CQnmDb db = new CQnmDb())
																		{
																			;
																			if (null==db.getAvailableDb(pQyMc.iDsnIndex_mainSys)) goto errLabel;
																			pDb = db.m_pDbMem.pDb;
																			if (0!=g_dbFuncs.pf_updateTaskStatus(pDb, iStatus, pMsgElem->iTaskId)) goto errLabel;
																		}
																		//
																		showTaskStatus(pMisCnt, pMsgElem->addr_logicalPeer.idInfo, pMsgElem->idInfo_taskSender, null, false, Consts.CONST_imCommType_transferFileReq, pMsgElem->iTaskId, iStatus, 0, 0, new string(pContentElem->transferFileReq.fileName), new string(pContentElem->transferFileReq.fullFilePath));
																	}
																}
															}
															//
															iErr = 1; goto errLabel;
														}
													}
													//
													//  transferAvInfo, 
													//
													if (pContentElem->uiType == Consts.CONST_imCommType_transferAvReplyInfo)
													{       //  ½ÓÊÕ·½´¦Àí
														TASK_transferAv task = (TASK_transferAv)taskElem;
														ref PROC_TASK_AV pTaskElem = ref task.myTask;// get_transferAvReplyInfo_pTask(&pContentElem->transferAvReplyInfo, _T(""));
														//if (!pTaskElem) goto errLabel;
														//
														if (pContent->taskProcReq.tStartTime_org == pContentElem->transferAvReplyInfo.tStartTime_org
															 && pContent->taskProcReq.uiTranNo_org == pContentElem->transferAvReplyInfo.uiTranNo_org)
														{
															IM_CONTENTU* pContent_o = (IM_CONTENTU*)(IntPtr)p1;
															int iStatus = Consts.CONST_imTaskStatus_canceledBySender;
															//
#if __DEBUG__
															traceLogA("taskProcReq ");
#endif
															//
															if (pContent_o!=null)
															{
																if (pContent_o->uiType == Consts.CONST_imCommType_taskProcResp)
																{
																	TASK_PROC_RESP* pFileProcResp = &pContent_o->taskProcResp;

																	pFileProcResp->bNeedRemoved = true;

																	//															   
																	object pDb = null;
																	using (CQnmDb db = new CQnmDb())
																	{
																		;

																		if (null==db.getAvailableDb(pQyMc.iDsnIndex_mainSys)) goto errLabel;
																		pDb = db.m_pDbMem.pDb;
																		if (0!=g_dbFuncs.pf_updateTaskStatus(pDb, iStatus, pMsgElem->iTaskId)) goto errLabel;
																	}
																	//
																	showTaskStatus(pMisCnt, pMsgElem->addr_logicalPeer.idInfo, pMsgElem->idInfo_taskSender, null, false, Consts.CONST_imCommType_transferAvInfo, pMsgElem->iTaskId, iStatus, 0, 0, null, null);
																}
															}
															//
															iErr = 1; goto errLabel;
														}

														//  2014/08/26
														if (pContent->taskProcReq.usOp == Consts.CONST_imOp_recv_applyForKeyFrame)
														{

															//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("recv applyforKeyFrame from %I64u."), pMsgInput->data.route.idInfo_from.ui64Id);

															//
															if (pContent->taskProcReq.vStream.uiTranNo_openAvDev == pContentElem->transferAvReplyInfo.tranInfo.video.uiTranNo_openAvDev)
															{

#if DEBUG
																traceLogA("findOrgMsgAndProcess_mis: get a applyForKeyFrame msg");
#endif

																//
																tmpiRet = procTaskProcReq_applyForKeyFrame(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgElem, &pContent->taskProcReq, pContentElem, ref pTaskElem);
																if (0!=tmpiRet)
																{
																	iErr = tmpiRet; goto errLabel;
																}

																iErr = 1; goto errLabel;
															}
														}

													}
													if (pContentElem->uiType == Consts.CONST_imCommType_transferAvInfo)
													{       //  ·¢ËÍ·½´¦Àí
															//
														if (!pTaskInfo.var.m_bReplyTask)
														{
															TASK_transferAv task = (TASK_transferAv)taskElem;
															ref PROC_TASK_AV pTaskElem = ref task.myTask;// get_transferAvInfo_pTask(&pContentElem->transferAvInfo, _T(""));
																										 //if (!pTaskElem) goto errLabel;
																										 //
															if (pContent->taskProcReq.tStartTime_org == pMsgElem->tStartTime
																&& pContent->taskProcReq.uiTranNo_org == pMsgElem->uiTranNo)
															{
																IM_CONTENTU* pContent_o = (IM_CONTENTU*)(IntPtr)p1;
																//
#if DEBUG
																traceLogA("tmpHandler_findOrgMsgAndProc_is: msg - taskProcReq. task found");
#endif

																//
																if (pContent_o != null)
																{
																	if (pContent_o->uiType == Consts.CONST_imCommType_taskProcResp)
																	{
																		TASK_PROC_RESP* pFileProcResp = &pContent_o->taskProcResp;

																		pFileProcResp->idInfo_logicalPeer.ui64Id = pMsgElem->addr_logicalPeer.idInfo.ui64Id;

																		if (pContent->taskProcReq.usOp == Consts.CONST_imOp_recv_applyForChkTaskAlive)
																		{
																			//
																			qyFuncs.traceLog("findOrgMsgAndProc: taskProcReq. usOp recv_applyForChkTaskAlive, task found");
																			//
																			iErr = 1; goto errLabel;
																		}

																		int iStatus = Consts.CONST_imTaskStatus_canceledByReceiver;

																		//  2014/12/03
																		bool bCanCancel = true;
																		if (pContentElem->transferAvInfo.bGrpTask)
																		{
																			bCanCancel = false;
																		}
																		if (pTaskElem.doProxy.bExists_avProxy)
																		{
																			bCanCancel = false;
																		}

																		//  2017/09/11
																		if (pContent->taskProcReq.usOp == Consts.CONST_imOp_recv_cancel)
																		{
																			tmp_procTask_recv_cancel(pProcInfo, ref pTaskElem, pMsgInput, &pContent->taskProcReq);
																		}

																		//
																		//if  (  !pContentElem->transferAvInfo.bGrpTask  )  
																		if (bCanCancel)
																		{
																			pFileProcResp->bNeedRemoved = true;

																			//  2014/12/03
#if false
																		TCHAR tBuf[128] = _T("");
																		_sntprintf(tBuf, mycountof(tBuf), _T("findOrgMsg: taskProcReq from receiver %I64u, to cancel transferAvInfo"), pMsgInput->data.route.idInfo_from.ui64Id);
#if __DEBUG__
																		traceLog(_T("%s"), tBuf);
#endif
																		showInfo_open(0, 0, tBuf);
#endif
																			//
																			object pDb = null;
																			using (CQnmDb db = new CQnmDb())
																			{
																				;

																				if (null == db.getAvailableDb(pQyMc.iDsnIndex_mainSys)) goto errLabel;
																				pDb = db.m_pDbMem.pDb;
																				if (0 != g_dbFuncs.pf_updateTaskStatus(pDb, iStatus, pMsgElem->iTaskId)) goto errLabel;
																			}
																			//
																			showTaskStatus(pMisCnt, pMsgElem->addr_logicalPeer.idInfo, pMsgElem->idInfo_taskSender, null, false, pContentElem->uiType, pMsgElem->iTaskId, iStatus, 0, 0, null, null);
																		}
																	}
																}
																//
																iErr = 1; goto errLabel;
															}
															//  2014/08/26
															if (pContent->taskProcReq.usOp == Consts.CONST_imOp_recv_applyForKeyFrame)
															{

																//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("recv applyforKeyFrame from %I64u, tn_openAvDev %d. matched iTaskId %d"), pMsgInput->data.route.idInfo_from.ui64Id, pContent->taskProcReq.vStream.uiTranNo_openAvDev, pMsgElem->iTaskId);

																bool tmp_bFound = false;
																//
																if (pTaskElem.ucbVideoConferenceStarter)
																{
																	//  2014/08/28. 暂时采用直接模式
																	if (pContent->taskProcReq.vStream.uiTranNo_openAvDev == pTaskElem.mem0_from.video.tv_recvd.uiTranNo_openAvDev)
																	{
																		tmp_bFound = true;
																	}
																	//  2014/12/06
																	if (pContent->taskProcReq.vStream.uiTranNo_openAvDev == pContentElem->transferAvInfo.confMosaicTranInfo_video.video.uiTranNo_openAvDev
																		|| pContent->taskProcReq.vStream.uiTranNo_openAvDev == pContentElem->transferAvInfo.confMosaicTranInfo_resource.video.uiTranNo_openAvDev)
																	{
																		tmp_bFound = true;

																	}
																}
																else
																{
																	if (pContent->taskProcReq.vStream.uiTranNo_openAvDev == pContentElem->transferAvInfo.ass.tranInfo.video.uiTranNo_openAvDev)
																	{
																		tmp_bFound = true;
																	}
																}
																//
																if (tmp_bFound)
																{

#if __DEBUG__
																traceLogA("findOrgMsgAndProcess_mis: get a applyForKeyFrame msg");
#endif

																	//
																	tmpiRet = procTaskProcReq_applyForKeyFrame(pProcInfo, &pMsgElem->addr_logicalPeer, pMsgElem->iTaskId, pMsgElem, &pContent->taskProcReq, pContentElem, ref pTaskElem);
																	if (tmpiRet != 0)
																	{
																		iErr = tmpiRet; goto errLabel;
																	}

																	iErr = 1; goto errLabel;
																}
																//
															}
															//  2014/10/09
															if (pContent->taskProcReq.usOp == Consts.CONST_imOp_stopSending
																|| pContent->taskProcReq.usOp == Consts.CONST_imOp_requestToSend)
															{
																if (0 != pContent->taskProcReq.viewDynBmp.uiObjType)
																{
																	if (pContentElem->transferAvInfo.ass.resObj.uiObjType == pContent->taskProcReq.viewDynBmp.uiObjType
																		&& pContentElem->transferAvInfo.ass.resObj.usIndex_obj == pContent->taskProcReq.viewDynBmp.usIndex_obj)
																	{
#if __DEBUG__
																	traceLog(_T("findOrgMsgAndProc: get taskProcReq msg"));
#endif

																		pMsgInput->iTaskId = pMsgElem->iTaskId;
																		pMsgInput->addr_logicalPeer.idInfo.ui64Id = pMsgElem->addr_logicalPeer.idInfo.ui64Id;

																		//
																		//pContent->taskProcReq.hWnd_task = pTaskElem.hWnd_task;

																		//
																		qPostMsg((IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + (uint)Marshal.OffsetOf<MIS_MSG_routeTalkData>("buf") + (uint)sizeof(TASK_PROC_REQ), pQyMc.gui.processQ);
																		GuiShare.pf_PostMessage(pQyMc.gui.hMainWnd, Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_msgArrive, 0);

																		iErr = 1; goto errLabel;
																	}
																}
															}
															//  2009/10/18
															if (pContent->taskProcReq.usOp == Consts.CONST_imOp_recv_applyForOrgReq)
															{

																//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("recv applyforOrgReq from %I64u. _tn %d"), pMsgInput->data.route.idInfo_from.ui64Id, pMsgInput->uiTranNo);
																//task.myTask.ucbVideoConference

																bool tmp_bMatched=false;
																if (pContent->taskProcReq.uiContentType_org == Consts.CONST_imCommType_transferAudioData) {
																	if (task.myTask.ucbVideoConference)
																	{
																		if (pContent->taskProcReq.uiTranNo_org == pContentElem->transferAvInfo.ass.tranInfo.audio.uiTranNo_openAvDev)
																		{
																			tmp_bMatched = true;
																		}
																	}
																	else
                                                                    {
																		if (bInActiveMems(pProcInfo, pMisCnt.idInfo, pContent->taskProcReq.uiTranNo_org, 0, task))
                                                                        {
																			tmp_bMatched = true;
                                                                        }
                                                                    }
																	if(tmp_bMatched)
																{
#if DEBUG
																		traceLogA("findOrgMsgAndProcess_mis: get a applyForOrgReq msg");
#endif
																		pMsgInput->iTaskId = pMsgElem->iTaskId;
																		//  2014/11/18
																		if (pContentElem->transferAvInfo.idInfo_logicalPeer.ui64Id != 0)
																		{
																			pMsgInput->addr_logicalPeer.idInfo.ui64Id = pContentElem->transferAvInfo.idInfo_logicalPeer.ui64Id;
																		}
																		else
																		{
																			pMsgInput->addr_logicalPeer.idInfo.ui64Id = pMsgElem->addr_logicalPeer.idInfo.ui64Id;
																		}

																		//
																		//
																		traceLog("post req applyForOrgReq for audioData to gui");

																		//
																		qPostMsg((IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + (uint)Marshal.OffsetOf<MIS_MSG_routeTalkData>("buf") + (uint)sizeof(TASK_PROC_REQ), pQyMc.gui.processQ);
																		GuiShare.pf_PostMessage(pQyMc.gui.hMainWnd, Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_msgArrive, 0);

																		iErr = 1; goto errLabel;
																	}
																}
																//  2010/12/27
																if (pContent->taskProcReq.uiContentType_org == Consts.CONST_imCommType_transferVideoData)
																{
																	if (task.myTask.ucbVideoConference)
																	{
																		if (pContent->taskProcReq.uiTranNo_org == pContentElem->transferAvInfo.ass.tranInfo.video.uiTranNo_openAvDev)
																		{
																			tmp_bMatched = true;
																		}
																	}
																	else
																	{
																		if (bInActiveMems(pProcInfo, pMisCnt.idInfo, 0, pContent->taskProcReq.uiTranNo_org, task))
																		{
																			tmp_bMatched = true;
																		}
																	}
																	if (tmp_bMatched)
																	{
#if DEBUG
																		traceLogA("findOrgMsgAndProcess_mis: get a applyForOrgReq msg. taskFound");
#endif
																		//
																		if (pMsgElem->uiTaskType == Consts.CONST_imTaskType_shareDynBmp)
																		{
																			if (pTaskElem.iIndex_sharedObj != 0)
																			{
																				QY_SHARED_OBJ pSharedObj = getSharedObjByIndex(pProcInfo, pTaskElem.iIndex_sharedObj);
																				if (pSharedObj != null)
																				{
																					removeFromMsgrs_sendLocalAv(pProcInfo, pMisCnt, ref pMsgInput->data.route.idInfo_from, ref pTaskInfo.var.curRoute_sendLocalAv);
																					//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("findOrgMsgAndProc: shareDynBmp, index_sharedObj %d, removeFromMsgrs_sendLocalAv, %I64u"), pTaskElem->iIndex_sharedObj, pMsgInput->data.route.idInfo_from);
																					iErr = 1; goto errLabel;
																				}
																			}
																		}

																		//
																		pMsgInput->iTaskId = pMsgElem->iTaskId;
																		//  2014/11/18
																		if (pContentElem->transferAvInfo.idInfo_logicalPeer.ui64Id != 0)
																		{
																			pMsgInput->addr_logicalPeer.idInfo.ui64Id = pContentElem->transferAvInfo.idInfo_logicalPeer.ui64Id;
																		}
																		else
																		{
																			pMsgInput->addr_logicalPeer.idInfo.ui64Id = pMsgElem->addr_logicalPeer.idInfo.ui64Id;
																		}

																		//
																		traceLog("post req applyForOrgReq for videoData to gui");

																		//
																		qPostMsg((IntPtr)pMsgInput, (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data") + (uint)Marshal.OffsetOf<MIS_MSG_routeTalkData>("buf") + (uint)sizeof(TASK_PROC_REQ), pQyMc.gui.processQ);
																		GuiShare.pf_PostMessage(pQyMc.gui.hMainWnd, Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_msgArrive, 0);

																		iErr = 1; goto errLabel;
																	}
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
			}

			


			iErr = 0;
		errLabel:

			//
			if (bDbg)
			{
				fixed (char* pName = ctxCaller.tNameBuf.tNameBuf)
				{
					str = string.Format("tmpHandler_findOrgMsg leaves, {0}", new string(pName));
				}
				qyFuncs.showAllTc(ctxCaller, str);
				qyFuncs.showInfo_open(0, null, str);

			}


			return iErr;
		}
		

	}
}
