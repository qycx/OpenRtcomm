
#include	"stdafx.h"
#include	<stddef.h>
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"tmpCeLib.h"
#ifndef  __WINCE__
//  #include	"DlgVideos.h"
#endif
#include	"qmcVideoCapture_isCli.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#ifndef  __WINCE__

#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"
//  #include	"dlgtest_isCli.h"

#endif
#include	"qmcCmdProc.h"

#include	"qySqlFunc.h"
#include	"qyAvRecordPublic.h"

//  #include	"DlgProgress.h"

#include	"myDb.h"

#include	"isCliHelpPublic.h"
#include	"isCliD3dPublic.h"
#include	"qmcCommFunc_isCli.h"
#include	"ctxMcThread.h"


//
//  2016/12/13
__declspec(dllexport) int  getNextAPktInfo_toDec(PKT_info_toDec* pCurPktInfo, QY_Q2* pAudioQ2)
{
	int  iErr = -1;
	MIS_MSGU* pMsg = (MIS_MSGU*)pCurPktInfo->pMIS_MSGU;
	IM_CONTENTU* pContent = NULL;

	//	
	if (pCurPktInfo->bGot_msg) {
		//
		if (!pCurPktInfo->info.bGot_pkt) {
			//
			switch (pMsg->uiType) {
			case  CONST_misMsgType_task:
				pContent = (IM_CONTENTU*)pMsg->task.data.buf;
				switch (pContent->uiType) {
				case  CONST_imCommType_transferAudioData: {
					TRANSFER_AUDIO_DATA* pReq = &pContent->transferAudioData;
					//
					if (pCurPktInfo->info.index_mems >= 0 && pCurPktInfo->info.index_mems + 1 < pReq->usCnt) {
						//										
						int  i = pCurPktInfo->info.index_mems;
						TRANSFER_AUDIO_dataMemHead* pMem = &pReq->mems[i];
						int  iPos = pCurPktInfo->info.iPos;

						if (iPos + pReq->mems[i].uiLen < pReq->uiLen) {

							pCurPktInfo->info.iPos += pMem->uiLen;
							pCurPktInfo->info.index_mems++;
							//			  
							pCurPktInfo->info.bGot_pkt = TRUE;

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

			//
			if (!pCurPktInfo->info.bGot_pkt) {
				pCurPktInfo->bGot_msg = FALSE;
			}
		}
	}


	//	
	if (!pCurPktInfo->bGot_msg) {
		//
		unsigned  int  len;
		len = sizeof(pMsg[0]);
		if (q2GetMsg(pAudioQ2, pMsg, &len, _T("getNextAPktInfo_toDec")))  goto  errLabel;
		memset(((char*)pMsg) + len, 0, min(256, sizeof(pMsg[0]) - len));
		//
		switch (pMsg->uiType) {
		case  CONST_misMsgType_task:
			pContent = (IM_CONTENTU*)pMsg->task.data.buf;
			switch (pContent->uiType) {
			case  CONST_imCommType_transferAudioData: {
				TRANSFER_AUDIO_DATA* pReq = &pContent->transferAudioData;

				//
				pCurPktInfo->bGot_msg = TRUE;
				//
				memset(&pCurPktInfo->info, 0, sizeof(pCurPktInfo->info));
				//
				if (!pReq->uiLen)  goto  errLabel;
				//
				pCurPktInfo->info.bGot_pkt = TRUE;

				//		
				M_set_pktId_getNewPkt(pCurPktInfo);

				//  2017/10/13
#ifdef  __DEBUG__
				if (pReq->usCnt > 1) {
					int  ii = 0;
				}
#endif

			}
													break;
			default:
				break;
			}
		}
		//	
		if (!pCurPktInfo->bGot_msg)  goto  errLabel;

	}


	//
	if (!pCurPktInfo->info.bGot_pkt) {
		goto  errLabel;
	}



	iErr = 0;

errLabel:

	if (iErr) {
		pCurPktInfo->bGot_msg = FALSE;
	}


	return  iErr;

}


//
__declspec(dllexport) void  clean_PKT_info_toDec(PKT_info_toDec* p, LPCTSTR  hint)
{
	if (!p)  return;

	p->info.bGot_pkt = FALSE;


}


//  2011/07/03
__declspec(dllexport ) int  chkFromPlayerIndex_a(unsigned  int  uiTransformType, void* pQY_TRANSFORM, myPLAY_AUDIO_DATA* p, void* p2)
{
	int						iErr = -1;

	//
	if (uiTransformType != CONST_uiTransformType_dec) {
		return  -1;
	}

	QY_TRANSFORM* pTransform = (QY_TRANSFORM*)pQY_TRANSFORM;
	if (!pTransform)  return  -1;

	MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pTransform->pProcInfo;
	if (!pProcInfo)  return  -1;
	int  iTaskId = pTransform->iTaskId;

	PROC_TASK_AV* pTask = (PROC_TASK_AV*)pTransform->pTask;
	if (!pTask)  return  -1;

	//
	WAVEFORMATEX* pWf = &pTransform->audio.ta.ah_decompress.wfx;

	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  return  -1;

	QY_MC* pQyMc = (QY_MC*)pProcInfo->pQyMc;
	QY_MESSENGER_ID			idInfo_recorder;
	unsigned  int			uiTranNo = 0;
	unsigned  short			usIndex = 0;
	int						iPos = 0;
	TCHAR					tBuf[256] = _T("");


	if (!pWf)  return  -1;

	/*
	//  idInfo_recorder.ui64Id  =  pReq->mems[i].idInfo.ui64Id  ?  pReq->mems[i].idInfo.ui64Id  :  pIdInfo_from->ui64Id;
	if  (  pReq->mems[i].idInfo.ui64Id  )  {
		idInfo_recorder.ui64Id  =  pReq->mems[i].idInfo.ui64Id;

		 if  (  idInfo_recorder.ui64Id  ==  pIdInfo_from->ui64Id  )  uiTranNo  =  pReq->uiTranNo_openAvDev;
		 else  uiTranNo  =  0;
		}
	else  {
		   idInfo_recorder.ui64Id  =  pIdInfo_from->ui64Id;
		   uiTranNo  =  pReq->uiTranNo_openAvDev;
	}
	*/
	idInfo_recorder.ui64Id = p->head.idInfo.ui64Id;
	uiTranNo = p->head.uiTranNo_openAvDev;		//  2016/12/16   
	if (!uiTranNo)  uiTranNo = p->head.tmpInternal.uiTranNo_org;		//  2016/12/16

	//  skip myself
	if (idInfo_recorder.ui64Id == pMisCnt->idInfo.ui64Id) {
		//
#ifdef  __DEBUG__  //  2017/08/16
		//traceLog((TCHAR*)  _T(  "chkFromPlayerIndex_a: idInfo_recorder is myslef, skipped"  )  );
#endif
//
//  iErr  =  0;  
		goto  errLabel;
	}
	//  2015/05/19
	if (pTransform->uiTaskType == CONST_imTaskType_viewDynBmp) {
		if (!pProcInfo->cfg.ucbPlayRemoteAudio_viewDynBmp) {
			//  skipped
			goto  errLabel;
		}
	}


	//
	//


#if  10		//  2016/02/15
			//PROC_TASK_AV  *  pTask  =  (  PROC_TASK_AV  *  )pTransform->pTask;
	if (!pTask)  goto  errLabel;


	if (pQyMc->iCustomId != CONST_qyCustomId_hzj) {

		//  2015/02/18							
		//  2010/09/02							
		BOOL  bNoSharedObj;  bNoSharedObj = FALSE;
		if (pTask->doProxy.bExists_avProxy)  bNoSharedObj = TRUE;

		//			
		if (!bNoSharedObj) {
			QY_SHARED_OBJ* pSharedObj = NULL;
			pSharedObj = getSharedObjByIndex(pProcInfo, pTask->iIndex_sharedObj);
			if (pSharedObj) {
				SHARED_OBJ_USR* pSharedObjUsr = getSharedObjUsr(pSharedObj, pSharedObj->iIndex_curUsr);
				if (pSharedObjUsr) {
					if (pSharedObjUsr->iTaskId != pTransform->iTaskId) {
#ifdef  __DEBUG__
						traceLog((TCHAR*)_T("chkFromPlayerIndex_a: sharedObjUsr isnt matched. skipped"));
#endif
						goto  errLabel;
					}
				}
			}
		}

		//
	}
#endif



	//
	QY_PLAYER* pPlayer;
	pPlayer = getPlayerByIndex(pProcInfo, pTransform->iIndex_player);
	if (pPlayer) {
		if (pPlayer->iTaskId != iTaskId
			|| pPlayer->idInfo_recorder.ui64Id != idInfo_recorder.ui64Id
			|| pPlayer->audio.uiTranNo != uiTranNo)
		{
			traceLogA((char*)"drawVideoData: not correct player");
			pTransform->iIndex_player = -1;
			pPlayer = NULL;
		}
	}

	if (!pPlayer) {
		int						k;
		//  
		for (k = 0; k < pProcInfo->av.usCnt_players; k++) {

			if (pProcInfo->av.pPlayers[k].iTaskId != iTaskId)  continue;		//  2010/09/07

			if (pProcInfo->av.pPlayers[k].idInfo_recorder.ui64Id == idInfo_recorder.ui64Id
				&& pProcInfo->av.pPlayers[k].audio.uiTranNo == uiTranNo)
			{
				if (!pTransform->video.tv.uiTranNo_openAvDev)  break;

				if (pProcInfo->av.pPlayers[k].idInfo_recorder.ui64Id == idInfo_recorder.ui64Id
					&& pProcInfo->av.pPlayers[k].video.uiTranNo == pTransform->video.tv.uiTranNo_openAvDev)
				{
					break;
				}
			}
		}
		if (k < pProcInfo->av.usCnt_players) {
			pTransform->iIndex_player = k;
			pPlayer = getPlayerByIndex(pProcInfo, k);
			if (!pPlayer)  goto  errLabel;
		}
	}
	//  2017/07/03
	if (!pPlayer || !pPlayer->audio.uiPlayType || !pPlayer->audio.bRunning) {


		//  ÕâÀï×é°ü·¢¸øÖ÷Ïß³Ì¡£
		MIS_MSG_applyForPlayer_qmc	msg;
		memset(&msg, 0, sizeof(msg));
		msg.uiType = CONST_misMsgType_applyForPlayer_qmc;
		msg.iTaskId = iTaskId;								//  2009/09/17
		msg.idInfo_recorder.ui64Id = idInfo_recorder.ui64Id;
		msg.audio.uiTranNo = uiTranNo;
		memcpy(&msg.audio.ah, pWf, min(sizeof(msg.audio.ah), sizeof(WAVEFORMATEX) + pWf->cbSize));

#if  0	//  2011/12/25
		memcpy(&msg.audio.playCfg, &pTask->audio.playCfg, sizeof(msg.audio.playCfg));	//  2009/06/14
#else
		tmpGetMaxAudioPlayCfg(&pTask->audio.playCfg, &pTransform->audio.ta.compressor.playCfg, &msg.audio.playCfg);
#endif

		if (pTransform->video.tv.uiTranNo_openAvDev) {
			msg.video.uiTranNo = pTransform->video.tv.uiTranNo_openAvDev;
			memcpy(&msg.video.vh.bih, &pTransform->video.tv.vh_decompress.bih, sizeof(msg.video.vh.bih));
			//msg.video.ucbFlippedImg  =  pTransform->video.tv.compressor.common.ucbOutputFlippedImg;		//  2011/12/11
			msg.video.usFps = pTransform->video.tv.compressor.common.usMaxFps_toShareBmp;					//  2015/02/20

			//  2015/05/20
			if (!msg.video.vh.bih.biWidth || !msg.video.vh.bih.biHeight) {
				if (!msg.idInfo_recorder.ui64Id) {
					_sntprintf(tBuf, mycountof(tBuf), _T("chkFromPlayerIndex_a failed, idInfo 0, trans.v.tv.vh_dec.bih: %dX%d"), msg.video.vh.bih.biWidth, msg.video.vh.bih.biHeight);
					showInfo_open0(0, 0, tBuf);
					goto  errLabel;
				}
			}
		}

		//  2009/09/17
		//  msg.iTaskId  =
#ifdef  __DEBUG__
		if (!msg.video.vh.bih.biWidth) {
			int  ii;
			ii = 0;
		}
#endif
		//
		DWORD  dwTickCnt = myGetTickCount(mynull);
		int  iDiffInMs = dwTickCnt - pTransform->dwLastTickCnt_doApplyForPlayer_a;
		if (abs(iDiffInMs) < 1000) {
#ifdef  __DEBUG__
			if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
				traceLog((TCHAR*)_T("chkFromPlayerIndex_a. can't applyForPlayer_a too quickly. skipped"));
			}
#endif
			iErr = -3;  goto  errLabel;
		}
		pTransform->dwLastTickCnt_doApplyForPlayer_a = dwTickCnt;

		//
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("chkFromPlayerIndex_a : %I64u,%d,%d apply for player"), idInfo_recorder.ui64Id, msg.audio.uiTranNo, msg.video.uiTranNo);

		//					  
		qPostMsg(&msg, sizeof(msg), &pQyMc->gui.processQ, _T("chkFromPlayerIndex_a"));
		PostMessage(pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);

		iErr = -2;  goto  errLabel;
	}

	if (pQyMc->env.bDebugInfo && pProcInfo->cfg.debugStatusInfo.ucbViewAudioStatus) {
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("playAudioData : %I64u plays"), idInfo_recorder.ui64Id);
	}

	TRANSFER_AUDIO_dataMemHead* pPkt;
	pPkt = &p->head;
	//

	DWORD	dwTickCnt_now; dwTickCnt_now = GetTickCount();

	//  2009/04/06
	pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd = pPkt->uiSampleTimeInMs;
	pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_newRecvd = dwTickCnt_now;

	if (pPkt->uiSampleTimeInMs && getQ2Nodes_toGetMsg(&pPlayer->audio.q2) > 1) {
		int	iAbs = abs((int)(pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_newRecvd - pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_syncRecv));	//  The iAbs is needed because uiSampleTimeInMs may be a future value.
		if (pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd + iAbs < pPlayer->audio.m_var.uiSampleTimeInMs) {			//  move backward the media file. need to clear up the old media data
			traceLogA((char*)"pkt.uiSampleTimeInMs %d  +  iAbs %d < player.%d. trigger to empty old data", pPkt->uiSampleTimeInMs, iAbs, pPlayer->audio.m_var.uiSampleTimeInMs);
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("playAudioData: pkt.uiSampleTimeInMs %d + abs %d < player.%d. trigger to empty old data"), pPkt->uiSampleTimeInMs, iAbs, pPlayer->audio.m_var.uiSampleTimeInMs);

			q2TriggerToProcess(&pPlayer->audio.q2);
		}
		if (pPlayer->audio.m_var.uiSampleTimeInMs) {
			if (pPkt->uiSampleTimeInMs > pPlayer->audio.m_var.uiSampleTimeInMs + 10000) {	//  2009/05/25. too old audio data
				_sntprintf(tBuf, mycountof(tBuf), _T("playAudioData: pkt.uiSampleTimeInMs %d > player.%d  +  10000. trigger to empty old data"), pPkt->uiSampleTimeInMs, pPlayer->audio.m_var.uiSampleTimeInMs);
				traceLogA((char*)"%S", tBuf);
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s"), tBuf);

				q2TriggerToProcess(&pPlayer->audio.q2);
			}
		}

		//  if  (  pTask->audio.playCfg.uiMaxTimeInMsToPlay  )  
		if (pPlayer->audio.playCfg.usMaxTimeInMsToPlay)
		{	//  2009/06/03
			int  nWaitingInMs_audio = MACRO_getnWaitingInMs_audio_syncRecv(pPlayer->audio, dwTickCnt_now);
			if (nWaitingInMs_audio > 0 && nWaitingInMs_audio > pPlayer->audio.playCfg.usMaxTimeInMsToPlay + pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying) {

#if  0
				_sntprintf(tBuf, mycountof(tBuf), _T("chkFromPlayerIndex_a: nWaitingInMs_audio %d > uiMaxTimeToPlay %d + playing %d. trigger to empty old data"), nWaitingInMs_audio, pPlayer->audio.playCfg.usMaxTimeInMsToPlay, pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying);
#ifdef  __DEBUG__
#if  0
				traceLogA((char*)"%S", tBuf);
#endif
#endif
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s"), tBuf);
#endif

#ifdef  __DEBUG__
				if (pPlayer->audio.playCfg.usMaxTimeInMsToPlay != pTask->audio.playCfg.usMaxTimeInMsToPlay) {
					traceLogA((char*)"playAudioData err: player.audio.m_var.uiMaxTimeInMsToPlay != task.audio.playCfg.*");
				}
				if (pPlayer->audio.playCfg.usMaxTimeInMsToBeRemoved != pTask->audio.playCfg.usMaxTimeInMsToBeRemoved) {
					traceLogA((char*)"playAudioData err: player.audio.m_var.uiMaxTimeInMsToBeRemoved != task.audio.playCfg.*");
				}
#endif

				q2TriggerToProcess(&pPlayer->audio.q2);
			}
		}
	}

	iErr = 0;
errLabel:
	return  iErr;

}


