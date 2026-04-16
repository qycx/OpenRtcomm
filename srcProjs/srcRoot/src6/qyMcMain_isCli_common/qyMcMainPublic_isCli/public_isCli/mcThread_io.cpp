

#include	"stdafx.h"
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
#include	"qmcCommFunc_isCli.h"
#include	"atMsgFunc.h"



extern "C" DWORD WINAPI mcThreadProc_mis_snd(LPVOID lpParameter)
{
	MIS_CHANNEL* pChannel = (MIS_CHANNEL*)lpParameter;
	if (!pChannel) {
		return  -1;
	}
	MIS_CNT* pMisCnt = pChannel->pMisCnt;
	if (!pMisCnt)  return  -1;
	MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pMisCnt->pProcInfoParam;
	if (!pProcInfo)  return  -1;
	QY_MC* pQyMc = pProcInfo->pQyMc;
	if (!pQyMc)  return  -1;
	//
	int							loopCtrl = 0;
	int							i;
	int							j;
	DWORD							dwThreadId = GetCurrentThreadId();
	DWORD							dwRet;

	unsigned  int					len;
	CQyMalloc						mallocObj;
	MIS_MSGU* pMsg = NULL;

	CQyMalloc						mallocObj_buf_help;
	QY_BUF							buf_help;

	int							iRet;
	//  BOOL							bThreadIdFound				=	FALSE;

	TCHAR							tBuf[256];
	BOOL							bChkTimeoutInSToSwitch = FALSE;
	unsigned  short* pusTimeoutInMsToSwitch = NULL;
	int							iElapse = 0;

#if  1	//  2011/01/22
	DWORD							dwTickCnt_toGetMsg;
	DWORD							dwTickCnt_startToSend;
	DWORD							dwTickCnt_lastEndSending_totalMsg = 0;
#endif

	//LPCTSTR  where_showInfo;	where_showInfo	=  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  );

	TCHAR  where_showInfo[128];
	_sntprintf(where_showInfo, mycountof(where_showInfo), _T("%s_S"), qyGetDesByType1(CONST_channelTypeTable, pChannel->uiType));

	//
	showInfo_open0(0, where_showInfo, _T("starts"));

	//
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("%s: mcThreadProc_mis_snd:  enters"), where_showInfo  );
#endif 

	//
	if (CONST_uiMaxQNodes_outputQ <= MAX_outputQ2Nodes_toPostQ) {
		traceLog((TCHAR*)_T("Serious error"));
		assert(0);
	}

	//
#if  0
	for (i = 0; i < mycountof(pProcInfo->misCnts); i++) {
		pMisCnt = &pProcInfo->misCnts[i];
		if (!pMisCnt->cfg.dynCfg.cnt.usCntPort)  continue;
		//
		for (j = 0; j < mycountof(pMisCnt->channels); j++) {
			pChannel = &pMisCnt->channels[j];
			if (!ctx.dwThreadId_snd)  continue;
			if (ctx.dwThreadId_snd == dwThreadId) {
				bThreadIdFound = TRUE;  break;
			}
		}
		//
		if (bThreadIdFound)  break;
	}

	if (!bThreadIdFound) {
		traceLogA((char*)"Error:  msgCnt not found.");  goto  errLabel;
	}
#endif

	//  2009/12/18. channel must be found first.
	if (!(pMsg = (MIS_MSGU*)mallocObj.mallocf(CONST_iAllocType_longTimeMsg, sizeof(MIS_MSGU))))  goto  errLabel;
	buf_help.len = sizeof(MIS_MSG_routeTalkData);
	if (!(buf_help.data = (unsigned  char*)mallocObj_buf_help.mallocf(CONST_iAllocType_longTimeMsg, buf_help.len)))  goto  errLabel;


	//
	switch (pChannel->uiType) {		//  2008/11/20
	case  CONST_channelType_media:
		pusTimeoutInMsToSwitch = &pProcInfo->cfg.policy.usTimeoutInMsToSwitch;
		bChkTimeoutInSToSwitch = TRUE;
		break;
	case  CONST_channelType_realTimeMedia:
		pusTimeoutInMsToSwitch = &pProcInfo->cfg.policy.usTimeoutInMsToSwitch_rt;
		bChkTimeoutInSToSwitch = TRUE;
		break;
	case  CONST_channelType_robot:
		pusTimeoutInMsToSwitch = &pProcInfo->cfg.policy.usTimeoutInMsToSwitch_file;
		bChkTimeoutInSToSwitch = TRUE;
		break;
	default:
		break;
	}

	//  pChannel->status.nMsgSent  =  0;

	{
		Param_dbg param;
		param.m_pHint = (TCHAR*)_T("snd.125");
		//
		for (; bChannelOk(pChannel, &param); loopCtrl++) {

			//
			if (isQ2Empty(&pChannel->outputQ2)) {

				//
				q2PostMsgAndTrigger(0, 0, &pChannel->toSendQ2, _T("thread_snd"));

				//
				dwRet = WaitForSingleObject(pChannel->outputQ2.hEvents[0], 3500);	//  µÈ·¢ËÍÖ¸Áî
				if (dwRet == WAIT_FAILED)  goto  errLabel;							//  ÎªÁË·ÀÖ¹¶ª°ü£¬ÕâÀï²»ÅÐ¶Ï³¬Ê±£¬ÒÔoutputQÀïµÄÊý¾Ý°üÎª×¼
				//if  (  dwRet  ==  WAIT_TIMEOUT  )  continue;								//  Ã»ÓÐÈË´¥·¢£¬ËùÒÔ³¬Ê±
#ifdef  __DEBUG__
		//  traceLog((TCHAR*)  _T(  "snd: sth waited"  )  );
#endif
//
				if (pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus) {
					showInfo_open0(0, where_showInfo, _T("after waitForSingleObject"));
				}
			}

			//
			//GENERIC_Q	*	pOutputQ	=	NULL;	//  2011/01/23

			//
			param.m_pHint = (TCHAR*)_T("snd.152");
			//
			for (; bChannelOk(pChannel, &param); ) {

				//
				q2AvoidTriggerTooHigh(0, &pChannel->outputQ2);

				//
				DWORD  dwTickCnt_toWaitForSock = myGetTickCount(NULL);

				//
				iRet = qyWaitForWrite(pChannel->sock.sockFd, pQyMc->cfg.to.iSelect);
				if (iRet < 0) {
					traceLogA((char*)"qyWaitForWrite failed");
					goto  errLabel;		//  ³ö´í
				}
				if (!iRet) {
					//
					DWORD  tmp_tickCnt = myGetTickCount(NULL);
					int  iDiffInMs = tmp_tickCnt - dwTickCnt_toWaitForSock;
					//
					_sntprintf(tBuf, mycountof(tBuf), _T("qyWaitForWrite returns 0. iDiffInMs %dms, continue"), iDiffInMs);
					showInfo_open0(0, where_showInfo, tBuf);
					//
					continue;		//  ³¬Ê±
				}

#if  1		//  2011/01/22
				dwTickCnt_toGetMsg = myGetTickCount(NULL);
#endif

				//
#ifdef  __DEBUG__
#if  0
				if (pChannel->uiType == CONST_channelType_media) {
					int  iDiffInMs = dwTickCnt_toGetMsg - dwTickCnt1;
					if (pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus) {
						_sntprintf(tBuf, mycountof(tBuf), _T("it takes %dms to select"), iDiffInMs);
						showInfo_open0(0, where_showInfo, tBuf);
					}
				}
#endif
#endif


				//
				int  nQNodes = getQ2Nodes(&pChannel->outputQ2);
				//if  (  nQNodes  <  MAX_outputQ2Nodes_toPostQ  )  
				//
				int  nQNodes_toTrigger = 2;
				//
#if  0
				if (pChannel->uiType == CONST_channelType_media
					|| pChannel->uiType == CONST_channelType_realTimeMedia)
				{
					//nQNodes_toTrigger  =  12;
				}
#endif
				//
				if (nQNodes < nQNodes_toTrigger)
				{
					q2PostMsgAndTrigger(0, 0, &pChannel->toSendQ2, _T("thread_snd 1"));
				}

				//  
				len = sizeof(pMsg[0]);
#if  0
				if (!pOutputQ || isQEmpty(pOutputQ)) {
					CQyQ2Help	q2Help_outputQ;
					pOutputQ = q2Help_outputQ.getQ_toGetMsg(&pChannel->outputQ2);
					//
					//q2PostMsgAndTrigger(  0,  0,  &pChannel->toSendQ2  );	
				}
				//
				if (qGetMsg(pOutputQ, pMsg, &len))  break;
#endif
				if (q2GetMsg(&pChannel->outputQ2, pMsg, &len, _T("mcThreadProc_mis_snd")))  break;

				//
				memset(((char*)pMsg) + len, 0, min(256, sizeof(pMsg[0]) - len));

				//  2009/02/25
				dwTickCnt_startToSend = myGetTickCount(NULL);

				//  traceLogA(  (char*)  "mcThreadproc_mis_snd: µÃµ½Ò»ÌõÏûÏ¢[%S]",  qyGetDesByType1(  CONST_misMsgTypeTable,  pMsg->uiType  )  ); 

				switch (pMsg->uiType) {
				case  CONST_misMsgType_req:

					//
					if (pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus) {
						qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("snd: %s,  tn %d"), qyGetDesByType1(CONST_qyCmdTable, pMsg->req.usCode), pMsg->req.uiTranNo);
					}

					//
#ifdef  __DEBUG__
					if (pMsg->req.usCode == CONST_qyCmd_getCfgs) {
						int  ii = 0;
					}
#endif


					//
					if (encryptData(&pChannel->commEncCtx, &buf_help, (char*)&pMsg->req.data, &pMsg->req.lenInBytes, sizeof(pMsg->req.data))) {
						qyShowInfo1(CONST_qyShowType_warning, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("snd req: encryptData failed"));
						goto  errLabel;
					}

					if (qySendMsg(&pChannel->session, &pChannel->sock, &pQyMc->cfg.to, pMsg->req.ucFlg, pMsg->req.usCode, pMsg->req.tStartTime, pMsg->req.uiTranNo, pMsg->req.usSeqNo, (char*)&pMsg->req.data, pMsg->req.lenInBytes)) {
						traceLogA((char*)"qySendMsg failed");
						goto  errLabel;
					}
					//  2009/10/11
					pChannel->status.netStat.ui64MsgDataLenSent += sizeof(QY_MSG_HEAD_n) + pMsg->req.lenInBytes;


					break;
				case  CONST_misMsgType_talk: {

					//  
					if (!isUcFlgResp(pMsg->task.ucFlg))  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("snd: tn %d, %s: len %d"), pMsg->task.uiTranNo, qyGetDesByType1(CONST_qyCmdTable, pMsg->task.usCode), pMsg->task.lenInBytes);
					else  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("snd: tn %d, resp: %s "), pMsg->task.uiTranNo, qyGetDesByType1(CONST_qyRcTable, pMsg->task.usCode));

					if (encryptData(&pChannel->commEncCtx, &buf_help, (char*)&pMsg->talk.data, &pMsg->talk.lenInBytes, sizeof(pMsg->talk.data))) {
						qyShowInfo1(CONST_qyShowType_warning, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("snd talk: encryptData failed"));
						goto  errLabel;
					}

					if (qySendMsg(&pChannel->session, &pChannel->sock, &pQyMc->cfg.to, pMsg->talk.ucFlg, pMsg->talk.usCode, pMsg->talk.tStartTime, pMsg->talk.uiTranNo, pMsg->talk.usSeqNo, (char*)&pMsg->talk.data, pMsg->talk.lenInBytes)) {
						traceLogA((char*)"qySendMsg failed");
						goto  errLabel;
					}
					//  2009/10/11
					pChannel->status.netStat.ui64MsgDataLenSent += sizeof(QY_MSG_HEAD_n) + pMsg->talk.lenInBytes;

				}
										   break;
				case  CONST_misMsgType_task:
				case  CONST_misMsgType_outputTask: {

					//  2008/11/20
					if (bChkTimeoutInSToSwitch) {
						if (pMsg->task.dwTickCnt_start) {
							iElapse = myGetTickCount(NULL) - pMsg->task.dwTickCnt_start;
							if (iElapse > *pusTimeoutInMsToSwitch) {
								BOOL	bTaskFound = FALSE;
								//
#if  0
								if (pMsg->task.iTaskId) {	//  2010/09/23
									if (pChannel->uiType == CONST_channelType_media) {
										int	i;
										for (i = 0; i < pProcInfo->cfg.usMaxCnt_pSharedObjs; i++) {
											QY_SHARED_OBJ* tmppSharedObj = getSharedObjByIndex(pProcInfo, i);
											SHARED_OBJ_USR* pSharedObjUsr = getSharedObjUsr(tmppSharedObj, tmppSharedObj->iIndex_curUsr);
											if (pSharedObjUsr
												&& pSharedObjUsr->iTaskId == pMsg->task.iTaskId)
											{
												CAP_procInfo_bmpU* pCapProcInfo = getCapBmpBySth(pProcInfo, tmppSharedObj->iIndex_capBmp, 0);
												if (pCapProcInfo) {
													COMPRESS_VIDEO* pCompressVideo = &pCapProcInfo->common.compressVideo;
													if (pCompressVideo) {
														pCompressVideo->usTimes_failure += MAX_failures_frames_perSecond + 1;
														bTaskFound = TRUE;
													}
												}
											}
										}
									}
								}
#endif
								//
								_sntprintf(tBuf, mycountof(tBuf), _T("snd: %dms elapsed, skipped. tn %d, %s."), iElapse, pMsg->task.uiTranNo, bTaskFound ? _T("to adjust speed.") : _T(""));
								if (pMsg->task.dwTickCnt_toSend) {
									_sntprintf(tBuf, mycountof(tBuf), _T("%s -2Snd %dms."), tBuf, pMsg->task.dwTickCnt_toSend - pMsg->task.dwTickCnt_start);
								}
								_sntprintf(tBuf, mycountof(tBuf), _T("%s last->s %dms."), tBuf, dwTickCnt_startToSend - pChannel->status.dwTickCnt_lastEndSending);
								qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("%s"), tBuf);
								break;
							}
						}
					}


					//
#ifdef  __DEBUG__
					if (1) {
						if (pChannel->uiType == CONST_channelType_realTimeMedia) {
							int  ii = pMsg->task.lenInBytes;
							//
							printf("kk\n");
						}
					}
#endif 


					//
					if (encryptData(&pChannel->commEncCtx, &buf_help, (char*)&pMsg->task.data, &pMsg->task.lenInBytes, sizeof(pMsg->task.data))) {
						qyShowInfo1(CONST_qyShowType_warning, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("snd task: encryptData failed"));
						goto  errLabel;
					}

					unsigned  int  uiSizePerSnd_media = pMisCnt->cfg.uiSizePerSnd_media;		//  2011/01/30
					if (!uiSizePerSnd_media)  uiSizePerSnd_media = MIN_uiSizePerSnd_media;

					//
#ifdef  __DEBUG__
							 //  获取最大的数据包长度
					static int smaxSendLen = 0;
					if (smaxSendLen < pMsg->task.lenInBytes) {
						smaxSendLen = pMsg->task.lenInBytes;
						//
						int  ii = 0;

					}
					//
					//_sntprintf(tBuf, mycountof(tBuf), _T("Warn: video_snd, uiSizePerSnd %d < task.lenInBytes %d"), uiSizePerSnd_media, pMsg->task.lenInBytes);

#endif
							 //
					if (pChannel->uiType == CONST_channelType_media) {
						if (uiSizePerSnd_media < pMsg->task.lenInBytes) {
							_sntprintf(tBuf, mycountof(tBuf), _T("Warn: video_snd, uiSizePerSnd %d < task.lenInBytes %d"), uiSizePerSnd_media, pMsg->task.lenInBytes);
							showInfo_open0(0, 0, tBuf);
						}
					}


					//
					{		//  
						char* p = NULL;
						unsigned  int		nLeft = 0;
						unsigned  int		uiSeqNo = 0;
						unsigned  int		nSend = uiSizePerSnd_media;
						unsigned  char		ucFlg = 0;
						//  TCHAR				tBuf[255  +  1]		=	_T(  ""  );
						//
						p = (char*)&pMsg->task.data;
						nLeft = pMsg->task.lenInBytes;

						//for  (  uiSeqNo  =  0;  nLeft  &&  bChannelOk(  pChannel  );  uiSeqNo  ++  )  
						for (uiSeqNo = 0; nLeft; uiSeqNo++)
						{
							nSend = min(nSend, nLeft);
							//
							ucFlg = (nLeft > nSend) ? (pMsg->task.ucFlg | CONST_commFlg_moreData) : pMsg->task.ucFlg;
							//
#ifdef  __DEBUG__
							if (0) {
								if (nLeft > nSend) {
									OutputDebugString(_T("\n"));
								}
								_sntprintf(tBuf, mycountof(tBuf), _T("before qySendMsg: uiSeqNo [%d], nSend [%d], lenInBytes [%d]\n"), uiSeqNo, nSend, pMsg->task.lenInBytes);
								OutputDebugString(tBuf);
							}
#endif
							//
							if (pQyMc->env.bDebugInfo && pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus) {
								if (!isUcFlgResp(pMsg->task.ucFlg))  _sntprintf(tBuf, mycountof(tBuf), _T("snd req: tn %d, sn %d. nSend %d."), pMsg->task.uiTranNo, uiSeqNo, nSend);
								else  _sntprintf(tBuf, mycountof(tBuf), _T("snd resp: tn %d, sn %d. nSend %d"), pMsg->task.uiTranNo, uiSeqNo, nSend);
								//
								uint dwTickCnt = myGetTickCount(NULL);
								int  iDiffInMs = dwTickCnt - pChannel->status.dwTickCnt_lastEndSending;
								int  nQNodes_outputQ2 = getQ2Nodes(&pChannel->outputQ2);
								_sntprintf(tBuf, mycountof(tBuf), _T("%s fromLastSend %dms, qNodes %d"), tBuf, iDiffInMs, nQNodes_outputQ2);
								//
								showInfo_open0(0, where_showInfo, tBuf);
							}

							//
							//
							if (qySendMsg(&pChannel->session, &pChannel->sock, &pQyMc->cfg.to, ucFlg, pMsg->task.usCode, pMsg->task.tStartTime, pMsg->task.uiTranNo, uiSeqNo, p, nSend)) {
								traceLogA((char*)"qySendMsg failed");
								goto  errLabel;
							}
							//  2009/10/11
							pChannel->status.netStat.ui64MsgDataLenSent += sizeof(QY_MSG_HEAD_n) + nSend;//pMsg->task.lenInBytes;
							//
							pChannel->status.dwTickCnt_lastEndSending = myGetTickCount(NULL);	//  2011/01/23

							//
#ifdef  __DEBUG__
							//
							if (0) {
								if (pChannel->uiType == CONST_channelType_realTimeMedia) {
									int  nnn = sizeof(QY_MSG_HEAD_n) + nSend;
									_sntprintf(tBuf, mycountof(tBuf), _T("dataLenSent %d"), nnn);
									traceLog((TCHAR*)_T("rtMedia: %s"), tBuf);
								}

							}
#endif 


							//
							nLeft -= nSend;
							p += nSend;
							continue;
						}
					}

					//  2011/01/22
					DWORD	dwTickCnt_endSending = myGetTickCount(NULL);
					if (pQyMc->env.bDebugInfo && pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus) {
						if (!isUcFlgResp(pMsg->task.ucFlg))  _sntprintf(tBuf, mycountof(tBuf), _T("snd req: tn %d, %s. len %d."), pMsg->task.uiTranNo, qyGetDesByType1(CONST_qyCmdTable, pMsg->task.usCode), pMsg->task.lenInBytes);
						else  _sntprintf(tBuf, mycountof(tBuf), _T("snd resp: tn %d, %s. len %d"), pMsg->task.uiTranNo, qyGetDesByType1(CONST_qyRcTable, pMsg->task.usCode), pMsg->task.lenInBytes);
						//  
						if (pMsg->task.dwTickCnt_start) {
							_sntprintf(tBuf, mycountof(tBuf), _T("%s s-snt %d."), tBuf, dwTickCnt_endSending - pMsg->task.dwTickCnt_start);
						}
						if (pMsg->task.dwTickCnt_toSend) {
							_sntprintf(tBuf, mycountof(tBuf), _T("%s -2Snd %u."), tBuf, pMsg->task.dwTickCnt_toSend - pMsg->task.dwTickCnt_start);
						}
						_sntprintf(tBuf, mycountof(tBuf), _T("%s lastSnd-toWaitForSock-toGetMsg-startToSnd-end %d, %d, %d, %d."), tBuf, dwTickCnt_toWaitForSock - dwTickCnt_lastEndSending_totalMsg, dwTickCnt_toGetMsg - dwTickCnt_toWaitForSock, dwTickCnt_startToSend - dwTickCnt_toGetMsg, dwTickCnt_endSending - dwTickCnt_startToSend);
						_sntprintf(tBuf, mycountof(tBuf), _T("%s nQ %d."), tBuf, getQ2Nodes_toGetMsg(&pChannel->outputQ2));

						qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("%s"), tBuf);
					}


				}
												 break;
				default:

					qyShowInfo1(CONST_qyShowType_debug, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("msThreadProc_mis_snd: Î´´¦ÀíµÄÏûÏ¢%S"), qyGetDesByType1(CONST_misMsgTypeTable, pMsg->uiType));
					traceLogA((char*)"err,  [%S]", qyGetDesByType1(CONST_misMsgTypeTable, pMsg->uiType));
					goto  errLabel;
					break;
				}

				//  pChannel->status.netStat.nMsgSent  ++  ;
				pChannel->status.dwTickCnt_lastEndSending = myGetTickCount(NULL);	//  2011/01/23
				dwTickCnt_lastEndSending_totalMsg = pChannel->status.dwTickCnt_lastEndSending;

				//
#ifdef  __DEBUG__
		//
#if  0
				int  kk;
				for (kk = 0; kk < 100; kk++) {
					q2PostMsg("bbb", 3, &pChannel->outputQ2);
				}
				//
				int  nQNodes = getQ2Nodes(&pChannel->outputQ2);
				if (nQNodes > 10) {
					reduceQ2Nodes(5, &pChannel->outputQ2);
				}
				int  iii = getQ2Nodes(&pChannel->outputQ2);
				int  ii = 0;
#endif
#endif

			}

		}

	}

errLabel:

	 //
	 showInfo_open0(  0,  where_showInfo,  _T(  "ends"  )  );

	 //
	 if  (  pMisCnt  )  {
		 pChannel->status.ulbSessionErr  =  TRUE;
		 pChannel->status.ulbSndQuit  =  TRUE;
	 }

	 //
#ifdef  __DEBUG__
	 traceLog(  (TCHAR*)_T("%s: mcThreadProc_mis_snd:  leaves"  ), where_showInfo  );
#endif

	 //
	 return  0;
}



//
extern "C" DWORD WINAPI mcThreadProc_mis_io(LPVOID lpParameter)
{
	int							iErr = -1;
	//QY_SERVICEGUI_INFO	*	pSci				=	(  QY_SERVICEGUI_INFO  *  )lpParameter;
	MIS_CHANNEL* pChannel = (MIS_CHANNEL*)lpParameter;
	if (!pChannel) {
		return  -1;
	}
	MIS_CNT* pMisCnt = (MIS_CNT*)pChannel->pMisCnt;
	if (!pMisCnt)  return  -1;
	MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pMisCnt->pProcInfoParam;
	if (!pProcInfo)  return  -1;
	QY_MC* pQyMc = pProcInfo->pQyMc;
	if (!pQyMc)  return  -1;

	int							i;
	int							j;
	DWORD						dwThreadId = GetCurrentThreadId();
	//BOOL						bThreadIdFound		=	FALSE;
	DWORD						dwThreadDaemonId;
	int							iRet;
	QY_MSG_HEAD_h					msgHead;
	CQyMalloc					mallocObj;
	MIS_MSG_INPUT* pMsg = NULL;
	//
	CQyMalloc					mallocObj_buf_help;
	QY_BUF						buf_help;
	//
	int							tmpiRet = -1;
	BOOL						bCryptInited = FALSE;

	CQyMalloc					mallocObj_pMsgBuf;
	MIS_MSGU* pMsgBuf = (MIS_MSGU*)mallocObj_pMsgBuf.mallocf(CONST_iAllocType_longTimeMsg, sizeof(MIS_MSGU));
	if (!pMsgBuf)  return  -1;

	//
	memset(&pChannel->ctx, 0, sizeof(pChannel->ctx));

	//
	//LPCTSTR  where_showInfo;	where_showInfo	=  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  );
	TCHAR  where_showInfo[128];
	_sntprintf(where_showInfo, mycountof(where_showInfo), _T("%s_R"), qyGetDesByType1(CONST_channelTypeTable, pChannel->uiType));

	//
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("%s: mcThreadProc_mis_io enters"), where_showInfo  );
#endif 

	//
	if (!(pMsg = (MIS_MSG_INPUT*)mallocObj.mallocf(CONST_iAllocType_longTimeMsg, sizeof(MIS_MSG_INPUT))))   goto  errLabel;
	buf_help.len = sizeof(MIS_MSG_routeTalkData);
	if (!(buf_help.data = (unsigned  char*)mallocObj_buf_help.mallocf(CONST_iAllocType_longTimeMsg, buf_help.len)))  goto  errLabel;


	//
	if (pChannel->bSessionOpen) {
#ifdef  __DEBUG__
		traceLogA((char*)"ÕâÀï³ö´íÀ­,ÔõÃ´»á»°ÒÑ¾­´ò¿ªÁËÄØ");
#endif
		goto  errLabel;
	}

	//  ÏÈ½¨Á¢¼ÓÃÜ»·¾³¡£2008/06/09
	memset(&pChannel->commEncCtx, 0, sizeof(pChannel->commEncCtx));
	memcpy(&pChannel->commEncCtx.common, &pMisCnt->commEncCtx.common, sizeof(pChannel->commEncCtx.common));
	bool  bMachineKey; bMachineKey = bUseMachineKey_qmc(pQyMc);
	if (initCrypt_qmc(pProcInfo, pMisCnt, pProcInfo->cspContainer_qmc, get_DEFAULT_cspProvider(), bMachineKey, (pChannel->uiType == CONST_channelType_talking), &pChannel->commEncCtx))  goto  errLabel;
	bCryptInited = TRUE;
	//
	_sntprintf(pChannel->commEncCtx.mutexName_syncCrypt_e, mycountof(pChannel->commEncCtx.mutexName_syncCrypt_e), _T("qmcCrypt%u-%u-e"), GetCurrentProcessId(), getuiNextTranNo(0, 0, 0));
	//_sntprintf(  pChannel->commEncCtx.mutexName_syncCrypt_d,  mycountof(  pChannel->commEncCtx.mutexName_syncCrypt_d  ),  _T(  "qmcCrypt%u-%u-d"), GetCurrentProcessId(), getuiNextTranNo(0, 0, 0));

	//
	pChannel->curServer = pMisCnt->server;

	//  
	for (i = 0; i < CONST_maxTriesToStartSession_mis; i++) {
		if (!tryToStartChannel(pMisCnt, pChannel, NULL, 0))  break;
	}
	if (i == CONST_maxTriesToStartSession_mis) {
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("can't start session"));
		goto  errLabel;
	}
	pChannel->status.ulbSessionErr = FALSE;
	//
	pChannel->status.dwTickCnt_startChannel =
		pChannel->status.dwTickCnt_lastStartToRecv = pChannel->status.dwTickCnt_lastEndSending = myGetTickCount(NULL);		//  2009/02/25

	//
	bChkMessengerChannelsReady(pQyMc);

	//
	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("auth OK"));

	//  
	pChannel->ctx.hThread_toSend = CreateThread(NULL, 0, mcThreadProc_mis_toSend, pChannel, CREATE_SUSPENDED, &dwThreadDaemonId);
	if (!pChannel->ctx.hThread_toSend)  goto  errLabel;
	pChannel->ctx.dwThreadId_toSend = dwThreadDaemonId;
	if (ResumeThread(pChannel->ctx.hThread_toSend) == -1)  goto  errLabel;
	//
	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("Function toSend is ready"));

	//  Æô¶¯·¢ËÍÏß³Ì
	pChannel->ctx.hThread_snd = CreateThread(NULL, 0, mcThreadProc_mis_snd, pChannel, CREATE_SUSPENDED, &dwThreadDaemonId);
	if (!pChannel->ctx.hThread_snd)  goto  errLabel;
	pChannel->ctx.dwThreadId_snd = dwThreadDaemonId;
	if (ResumeThread(pChannel->ctx.hThread_snd) == -1) {
		traceLogA((char*)"ResumeThread snd failed");
		goto  errLabel;
	}
	//
	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("Function send is ready"));

	//
	if (pChannel->uiType == CONST_channelType_talking) {
		//
		static bool sbTriggedScheduer = false;
		if (!sbTriggedScheduer) {
			sbTriggedScheduer = true;
			//
			qPostMsgAndTrigger(NULL, 0, &pProcInfo->schedulerQ, _T("mcThreadProc_io: trig scheduler"));
			showInfo_open0(0, mynull, _T("mcThreadProc_io: trig scheduler to retrieve imObjList"));
		}
	}

	{
		//  pChannel->status.nMsgRecved  =  0;
		Param_dbg param;
		param.m_pHint = (TCHAR*)_T("io.591");
		//
		for (; bChannelOk(pChannel, &param); ) {	//  Õâ¸öÑ­»·ÊÇ°´ÒªÇó¶ÁÒ»¸öÏûÏ¢

			int  iTo_waitForRead = 2500;
			//iTo_waitForRead  =  pQyMc->cfg.to.iSelect;
			iRet = qyWaitForRead(pChannel->sock.sockFd, iTo_waitForRead);
			if (iRet < 0)  goto  errLabel;
			if (!iRet) {
				//
				continue;
			}

			//  2009/02/25
			pChannel->status.dwTickCnt_lastStartToRecv = myGetTickCount(mynull);

			MACRO_memset_misMsgInput(pMsg);
			//  ÕâÀïÊÇÕæÓÐÊý¾ÝÀ´ÁË
			if (qyRecvMsg(&pChannel->session, &pChannel->sock, &pQyMc->cfg.to, &msgHead, (char*)&pMsg->data, sizeof(pMsg->data))) {
				traceLogA((char*)"mcThreadProc_mis_io: qyRecvMsg(  ) failed");
				goto  errLabel;
			}

			//  traceLogA(  (char*)  "mcThreadProc_mis_io: get, ³¤¶È %d, tStartTime is %d, uiTranNo is %d",  pMsg->lenInBytes,  pMsg->tStartTime,  pMsg->uiTranNo  );
			pChannel->status.netStat.ui64MsgDataLenRecvd += sizeof(QY_MSG_HEAD_n) + msgHead.uiLen;		//  2009/10/10


			//
			pMsg->tStartTime = (time_t)msgHead.i64StartTime;
			pMsg->uiTranNo = msgHead.uiTranNo;
			pMsg->usSeqNo = msgHead.usSeqNo;
			pMsg->ucFlg = msgHead.ucFlg;
			pMsg->usCode = msgHead.usCode;
			pMsg->uiChannelType = pChannel->uiType;		//  2008/04/17
			pMsg->lenInBytes = msgHead.uiLen;

			if (pQyMc->env.bDebugInfo && pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus) {
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("recv %s: tn %d, sn %d, len %d"), isUcFlgResp(pMsg->ucFlg) ? _T("resp") : _T("req"), pMsg->uiTranNo, pMsg->usSeqNo, pMsg->lenInBytes);
			}

			if (isUcFlgMoreData(pMsg->ucFlg)) {
				if (procMisMsg_moreData(&pChannel->inCacheQ, pMsg, NULL))  goto  errLabel;
				continue;
			}
			if (pMsg->usSeqNo) {
				BOOL  bMsgSkipped = FALSE;		//  ÊÇ·ñ´Ë°üÐèÒªºöÂÔ?
				//
				if (procMisMsg_moreData(&pChannel->inCacheQ, pMsg, &bMsgSkipped))  goto  errLabel;
				if (bMsgSkipped)  continue;
				//
				//  traceLogA(  (char*)  "µÃµ½Ò»¸ö´ó°ü£¬³¤¶ÈÎª%d, tStartTime is %d, uiTranNo is %d",  pMsg->lenInBytes,  pMsg->tStartTime,  pMsg->uiTranNo  );
			}


			if (decryptData(&pChannel->commEncCtx, &buf_help, (char*)&pMsg->data, &pMsg->lenInBytes)) {
				qyShowInfo1(CONST_qyShowType_warning, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T(""), _T("io: decryptData failed."));
				goto  errLabel;
			}

			//  pChannel->status.netStat.nMsgRecvd  ++  ;

			//
			bool  bShow = false;

#ifdef  __DEBUG__  
			static  int  kk = 0;
			//  traceLogA(  (char*)  "get code %S,  msgHead.usLen %d,  kk  =  %d",  qyGetDesByType1(  CONST_qyCmdTable,  msgHead.usCode  ),  msgHead.usLen,  kk  );
			if (pChannel->uiType == CONST_channelType_media) {
				//bShow = true;
				//
				kk++;
			}
			if (pChannel->uiType == CONST_channelType_realTimeMedia) {
				kk++;
			}
		
#endif
//
			//
			if (pQyMc->env.bDebugInfo && pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus) bShow = true;
			//
			if  (  bShow  )			
			{
				//
				TCHAR  tBuf[128];
				if (isUcFlgResp(msgHead.ucFlg))  _sntprintf(tBuf, mycountof(tBuf), _T("recv resp:  tn %d, sn %d, %s, dataLen %d"), msgHead.uiTranNo, (int)msgHead.usSeqNo, qyGetDesByType1(CONST_qyRcTable, msgHead.usCode), pMsg->lenInBytes);
				else  _sntprintf(tBuf, mycountof(tBuf), _T("recv req: tn %d, sn %d, %s, dataLen %d"), msgHead.uiTranNo, (int)msgHead.usSeqNo, qyGetDesByType1(CONST_qyCmdTable, msgHead.usCode), pMsg->lenInBytes);
#ifdef  __DEBUG__
				_sntprintf(tBuf, mycountof(tBuf), _T("%s kk %d"), tBuf, kk);
#endif
				showInfo_open0(0, where_showInfo, tBuf);
			}

			//
			if ((tmpiRet = pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_input, msgHead.ucFlg, msgHead.usCode, (time_t)msgHead.i64StartTime, msgHead.uiTranNo, 0, (char*)&pMsg->data, pMsg->lenInBytes, 0, 0, pChannel->uiType, pMsgBuf, FALSE))) {
				if (tmpiRet == CONST_qyRet_qFull) {
					switch (pChannel->uiType) {
					case  CONST_channelType_media:
					case  CONST_channelType_realTimeMedia:
						qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("postMsg2Mgr_mc returns qFull, skipped."));
						continue;
					default:
						break;
					}
				}
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("postMsg2Mgr_mc failed."));
				goto  errLabel;
			}

			/*
			dwRet  =  WaitForSingleObject(  pChannel->hSemaTrigger_input,  3000  );
			if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
			*/

		}

	}
	  
	iErr  =  0;

errLabel:
	
	//if  (  bThreadIdFound  )  
	{

		pChannel->status.ulbSessionErr  =  TRUE;	//  ´Ë±êÖ¾Î»Í¨ÖªrecvºÍsndÁ½Ïß³ÌÍË³ö

		MACRO_qyNullThread(  pChannel->ctx.hThread_toSend  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "Function toSend is closed"  )  );							   
		MACRO_qyNullThread(  pChannel->ctx.hThread_snd  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "Function send is closed"  )  );							   

		if  (  pChannel->bSessionOpen  )  {
			//
#ifdef  __DEBUG__
			traceLog(  (TCHAR*)  _T("%s: to close session"  ), where_showInfo  );			
#endif 
			//
			CTX_caller ctxCaller(where_showInfo);
			qnmCloseSession_msg(  &ctxCaller,&pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to,  _T("mcThreadProc_mis_io.l773"));
			pChannel->bSessionOpen  =  FALSE;
			//
#ifdef  __DEBUG__
			traceLog(  (TCHAR*)_T(  "%s: session closed"  ),  where_showInfo  );	
#endif 

			//
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "Session is closed"  )  );

		}
		if  (  bCryptInited  )  exitCrypt_qmc(  pProcInfo,  pMisCnt,  &pChannel->commEncCtx  );
	
		pChannel->status.ulbIoQuit  =  TRUE;
	}

	//
#ifdef  __DEBUG__
	traceLog(  (TCHAR*)  _T(" %s: mcThreadProc_mis_io leaves"  ), where_showInfo  );
#endif 

	//
	return  iErr;
}







