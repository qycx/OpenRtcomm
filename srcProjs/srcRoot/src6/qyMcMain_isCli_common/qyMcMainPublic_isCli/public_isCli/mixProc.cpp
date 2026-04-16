#include	"stdafx.h"
#include	<stddef.h>

#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>

#include	<string>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#include	"qmcSound_dx.h"

#include	"qmcVideoCapture_isCli.h"
#include	<mmdeviceapi.h>
#include	<Audioclient.h>
#include	"policyAvParams.h"
#include	"qyAvRecordPublic.h"
#include	"ctxMcThread.h"

//#include	"tmpFfmpegPublic.h"
#include	"tmpFfmpegCommon.h"
#include	"GuiShare.h"
#include	"aecProc.h"
#include	"help_webrtc1Public.h"
#include	"ctxQmc.h"
#include	"mixProc.h"
#include <qy_qBuf2_defs.h>


//
int doMix(CCtxQmc  *  pProcInfo,  Mix_procInfo  *  pMixProcInfo,  CTX_mix  *  pCtx)
{
	int  iErr = -1;
	AEC_layout* pAecLayout = &pProcInfo->av.aecInfo.aecLayout;
	int  i;
	char  buf[16000 * 2];
	unsigned  int  len;
	
	len = sizeof(buf);
	dyn_audioMixerObj_doMix(pCtx->pAudioMixerObj, buf, &len);

	int  ii = 0;

	if (len) {
		//
#ifdef  __DEBUG__
		if (pMixProcInfo->fp_debug) {
			//fwrite(buf, len, 1, pMixProcInfo->fp_debug);
		}
#endif


		//
		int iSampleTimeInMs = myGetTickCount(mynull);
		int uiPts = 0;
		playMixerAudioData(pProcInfo, pAecLayout->iTaskId, pMixProcInfo->uiTranNo_openAvDev_a, &pMixProcInfo->wfx, iSampleTimeInMs, uiPts,  (BYTE*)buf, len, pMixProcInfo);
	}




	iErr = 0;
	return  iErr;
}


//
int  playMixerAudioData(void *pProcInfoParam, int  iTaskId, unsigned  int  uiTranNo, WAVEFORMATEX* pWf, int  iSampleTimeInMs, unsigned  int  uiPts,  BYTE* pInput, unsigned  int  inputLen, Mix_procInfo  *  pMixProcInfo)
{
	int						iErr = -1;
	CCtxQmc* pProcInfo = (CCtxQmc*)pProcInfoParam;
	QY_MC* pQyMc = (QY_MC*)pProcInfo->pQyMc;

	if (!pWf)  return  -1;
	if (!uiTranNo) {
		traceLogA((char*)"playLocalAudioData failed, uiTranNo is 0");
		return  -1;
	}

	QY_PLAYER* pPlayer = NULL;


	//
	pPlayer = getPlayerByIndex(pProcInfo, pMixProcInfo->iIndex_localPlayer);
	if (pPlayer) {
		if (pPlayer->iTaskId != iTaskId
			|| pPlayer->idInfo_recorder.ui64Id != 0
			|| pPlayer->audio.uiTranNo != uiTranNo)
		{
			traceLogA((char*)"playMixerAudioData: not correct player");
			//
			pMixProcInfo->iIndex_localPlayer = -1;
			pPlayer = NULL;
		}
	}

	if (!pPlayer) {
		int						k;

		for (k = 0; k < pProcInfo->av.usCnt_players; k++) {

			//  2015/05/22
			if (pProcInfo->av.pPlayers[k].iTaskId != iTaskId)  continue;		//  2010/09/07

			//
			if (pProcInfo->av.pPlayers[k].idInfo_recorder.ui64Id == 0
				&& pProcInfo->av.pPlayers[k].audio.uiTranNo == uiTranNo)
			{
				break;
			}
		}

		if (k < pProcInfo->av.usCnt_players) {
			pMixProcInfo->iIndex_localPlayer = k;
			pPlayer = getPlayerByIndex(pProcInfo, k);
			if (!pPlayer)  goto  errLabel;
		}
	}

	//  
	if (!pPlayer || !pPlayer->audio.bRunning) {


		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("playMixerAudioData : mix,%d,%d apply for player"), uiTranNo, 0);

		//  ÕâÀï×é°ü·¢¸øÖ÷Ïß³Ì¡£
		MIS_MSG_applyForPlayer_qmc	msg;
		memset(&msg, 0, sizeof(msg));
		msg.uiType = CONST_misMsgType_applyForPlayer_qmc;
		msg.iTaskId = iTaskId;
		//  msg.idInfo_recorder.ui64Id  =  0;
		msg.audio.uiTranNo = uiTranNo;
		//  msg.audio.usIndex  =  0;
		memcpy(&msg.audio.ah, pWf, min(sizeof(msg.audio.ah), sizeof(WAVEFORMATEX) + pWf->cbSize));
		//
		//memcpy(&msg.audio.playCfg, &pCapAudio->common.compressAudio.compressor.playCfg, sizeof(msg.audio.playCfg));	//  2012/01/04

		//
		msg.bMix = true;

		//
		//					  
		qPostMsg(&msg, sizeof(msg), &pQyMc->gui.processQ, _T("playMixerAudioData"));

		PostMessage(pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);
		iErr = 0;  goto  errLabel;
	}

	if (pQyMc->env.bDebugInfo && pProcInfo->cfg.debugStatusInfo.ucbViewAudioStatus) {
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("playMixerAudioData : mix, %d,%d plays"), uiTranNo, 0);
	}

	//
	if  (  pProcInfo->cfg.b_useQ2_toPlayA)
	{
		CQyMalloc				mallocObj;
		myPLAY_AUDIO_DATA		pkt;
		myPLAY_AUDIO_DATA* pPkt = &pkt;			//  =	(  myPLAY_AUDIO_DATA  *  )mallocObj.malloc(  offsetof(  myPLAY_AUDIO_DATA,  buf  )  +  len  );
		if (!pPkt)  goto  errLabel;
		myPLAY_AUDIO_DATA* p = pPkt;

		if (inputLen > pProcInfo->cfg.uiBufSize_myPlayAudioData) {
			goto  errLabel;
		}

		//
		memset(pPkt, 0, sizeof(myPLAY_AUDIO_DATA));
		pPkt->head.idInfo.ui64Id = 0;
		pPkt->head.uiSampleTimeInMs = iSampleTimeInMs;
		pPkt->head.uiPts = uiPts;

		//
		unsigned  int  uiSize_dec = inputLen;
		unsigned  int  uiSize_enc = 0;
		//
		pPkt->head.uiLen = uiSize_dec + uiSize_enc;
		pPkt->uiSize_dec = uiSize_dec;
		//
		if (!mallocObj.mallocf(p->head.uiLen))  goto  errLabel;
		if (mallocObj.get(&p->memory))  goto  errLabel;
		memcpy(p->memory.m_pBuf, pInput, p->uiSize_dec);  //  p->head.uiLen  );



	//

		DWORD	dwTickCnt_now = GetTickCount();

		//  2009/04/06
		pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd = pPkt->head.uiSampleTimeInMs;
		pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_newRecvd = dwTickCnt_now;

#if  0
		if (pPkt->head.uiSampleTimeInMs && getQ2Nodes_toGetMsg(&pPlayer->audio.q2) > 1) {
			int	iAbs = abs((int)(pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_newRecvd - pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_syncRecv));	//  The iAbs is needed because uiSampleTimeInMs may be a future value.
			if (pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd + iAbs < pPlayer->audio.m_var.uiSampleTimeInMs) {			//  move backward the media file. need to clear up the old media data
				traceLogA((char*)"pkt.uiSampleTimeInMs %d + iAbs %d < player.%d. trigger to empty old data", pPkt->head.uiSampleTimeInMs, iAbs, pPlayer->audio.m_var.uiSampleTimeInMs);
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("playAudioData: pkt.uiSampleTimeInMs %d + abs %d < player.%d. trigger to empty old data"), pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd, iAbs, pPlayer->audio.m_var.uiSampleTimeInMs);

				q2TriggerToProcess(&pPlayer->audio.q2);
			}
			if (pPlayer->audio.m_var.uiSampleTimeInMs) {
				if (pPkt->head.uiSampleTimeInMs > pPlayer->audio.m_var.uiSampleTimeInMs + 10000) {	//  2009/05/25. too old audio data
					traceLogA((char*)"pkt.uiSampleTimeInMs %d > player.%d  +  10000. trigger to empty old data", pPkt->head.uiSampleTimeInMs, pPlayer->audio.m_var.uiSampleTimeInMs);
					q2TriggerToProcess(&pPlayer->audio.q2);
				}
			}
			//  2012/01/26
			if (pPlayer->audio.playCfg.usMaxTimeInMsToPlay)
			{	//  2009/06/03
				TCHAR  tBuf[256] = _T("");
				int  nWaitingInMs_audio = MACRO_getnWaitingInMs_audio_syncRecv(pPlayer->audio, dwTickCnt_now);
				if (nWaitingInMs_audio > 0 && nWaitingInMs_audio > pPlayer->audio.playCfg.usMaxTimeInMsToPlay + pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying) {

#if  10
					_sntprintf(tBuf, mycountof(tBuf), _T("chkFromPlayerIndex_a: nWaitingInMs_audio %d > uiMaxTimeToPlay %d + playing %d. trigger to empty old data"), nWaitingInMs_audio, pPlayer->audio.playCfg.usMaxTimeInMsToPlay, pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying);
#ifdef  __DEBUG__
					traceLogA((char*)"%S", tBuf);
#endif
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s"), tBuf);
#endif

#ifdef  __DEBUG__
#if  0
					if (pPlayer->audio.playCfg.uiMaxTimeInMsToPlay != pTask->audio.playCfg.uiMaxTimeInMsToPlay) {
						traceLogA((char*)"playAudioData err: player.audio.m_var.uiMaxTimeInMsToPlay != task.audio.playCfg.*");
					}
					if (pPlayer->audio.playCfg.uiMaxTimeInMsToBeRemoved != pTask->audio.playCfg.uiMaxTimeInMsToBeRemoved) {
						traceLogA((char*)"playAudioData err: player.audio.m_var.uiMaxTimeInMsToBeRemoved != task.audio.playCfg.*");
					}
#endif
#endif

					q2TriggerToProcess(&pPlayer->audio.q2);
				}
			}
		}
#endif


		//
#if  0	//  2011/11/30, 不想采用触发机制了
		if (q2PostMsgAndTrigger(pPkt, pktLen, &pPlayer->audio.q2))
#else
		if (q2PostMsg(pPkt, sizeof(myPLAY_AUDIO_DATA), &pPlayer->audio.q2, _T("playMixerAudioData 1")))
#endif
		{
			//
			goto  errLabel;
		}
		mallocObj.detach();

	}
	else {
		//
		HeadData_playA headData;
		memset(&headData, 0, sizeof(HeadData_playA));
		headData.uiPts = uiPts;
		headData.uiSize_dec = inputLen;
		if (0 != pPlayer->audio.qBuf2->q2PostMsg(&headData, pInput, inputLen, _T("playAudioData")))
		{
			goto errLabel;
		}

	}



	iErr = 0;
errLabel:
	return  iErr;
}







//
extern "C" DWORD WINAPI mcThreadProc_mix(LPVOID lpParameter)
{
	//int							iIndex_sharedObj			=	(  int  )lpParameter;

	QY_MC* pQyMc = nullptr;// QY_GET_GBUF();
	if (!pQyMc) {
		return  -1;
	}
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return  -1;
	QMC_cfg* pQmcCfg = (QMC_cfg*)pProcInfo->get_qmc_cfg();
	if (!pQmcCfg)  return  -1;

	bool  bDbg = false;
#ifdef  __DEBUG__
	bDbg  =  true;
#endif
	TCHAR  tBuf[128];
	int  i;

	//
	Mix_procInfo* pMixProcInfo = &pProcInfo->av.mixProcInfo;


#if  10

	//  2009/12/24

	//
	DWORD							dwThreadId = GetCurrentThreadId();


	MIS_CNT* pMisCnt = (MIS_CNT*)pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  return  -1;

	CQyMalloc						mallocObj_pMsgBuf;
	MIS_MSGU* pMsgBuf = (MIS_MSGU*)mallocObj_pMsgBuf.mallocf(sizeof(MIS_MSGU));
	if (!pMsgBuf)  return  -1;


	//DWORD							dwTickCnt;

	//  2010/09/18
	//  int							tmpiRet;
	BOOL							tmpbErr;

	uint  tickCnt_last = 0;
	uint  tickCnt0 = 0;
	uint  tickCnt1 = 0;

	CTX_mix						ctx;
	memset(&ctx, 0, sizeof(ctx));

	//
	traceLogA((char*)"mcThreadProc_mix %S enters", pMixProcInfo->thread.q2.cfg.name);

	pMixProcInfo->thread.bQuit = FALSE;
	pMixProcInfo->thread.bRunning = TRUE;


	//  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u starts"  ),  pPlay->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id  );

	//
#ifdef  __DEBUG__
#if  1
	pMixProcInfo->fp_debug = _tfopen(_T("c:\\tttbbb\\124\\mix.pcm"), _T("wb"));
	if (pMixProcInfo->fp_debug == mynull)goto  errLabel;
#endif

#endif


	//
	AEC_layout* pAecLayout; pAecLayout = &pProcInfo->av.aecInfo.aecLayout;
	if (!pAecLayout->iTaskId)  goto  errLabel;
	if (!pAecLayout->usCntLimit_activeMems_from) goto  errLabel;
	//
	if (dyn_initAudioMixerObj(16000, pAecLayout->usCntLimit_activeMems_from, my_inStream4_toMix, pProcInfo, &ctx.pAudioMixerObj)) {
		showInfo_open0(0, 0, _T("mcThreadProc_mix.dyn_initAudioMixerObj failed"));
		goto  errLabel;
	}

	//
	pMixProcInfo->uiTranNo_openAvDev_a = getuiNextTranNo(0, 0, 0);
	makeWaveFormat_pcm(1, 16000, 16, &pMixProcInfo->wfx);


	//
#ifdef  __DEBUG__
	for (i = 0; i < pAecLayout->usCntLimit_activeMems_from; i++) {
		AEC_player_cfg* pMem = &pAecLayout->mems[i];
		MACRO_qyAssert(!pMem->fp_debug, _T("fp_debug is not null"));
		if (!pMem->fp_debug) {
			_sntprintf(tBuf, mycountof(tBuf), _T("c:\\tttbbb\\124\\mem%d.pcm"), i);
			pMem->fp_debug = _tfopen(tBuf, _T("wb"));
			if (pMem->fp_debug == mynull)goto  errLabel;
		}
		
		}
#endif

	//
	DWORD dwTickCnt_start; dwTickCnt_start = myGetTickCount(mynull);
	int  loopCtrl;loopCtrl = 0;
	int  nIntervalInMs_ok; nIntervalInMs_ok = 10;//

	/////////////////
	for (; !pMixProcInfo->thread.bQuit; ) {

		//  2010/12/28
		uint  dwToInMs = 10;	//5000;
		dwToInMs = 9;

		//
		DWORD  dwTickCnt_cur = myGetTickCount(mynull);
		int  iElapseInMs = dwTickCnt_cur - dwTickCnt_start;
		int iElapseInMs_next = loopCtrl * nIntervalInMs_ok;
		if (iElapseInMs_next < iElapseInMs) {
			//
			int  iDiffInMs = iElapseInMs_next - iElapseInMs;
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T("mix: err, iElapseInMs_next < iElapseInMs. iDiffInMs %dms. reset"),  iDiffInMs);
			showInfo_open0(0, 0, tBuf);
			//
			dwTickCnt_start = dwTickCnt_cur;
			loopCtrl = 0;
			//
			dwToInMs = 0;
		}
		else {
			dwToInMs = iElapseInMs_next - iElapseInMs;
			//
			int nAhead = 2;
			if (dwToInMs > nAhead) {
				dwToInMs -= nAhead;
			}
		}
		
		//
#ifdef  __DEBUG__
#if  0
		_sntprintf(tBuf, mycountof(tBuf), _T("mix: dwToInMs %dms, loopCtrl %d"), dwToInMs, loopCtrl);
		showInfo_open0(0, 0, tBuf);
#endif
#endif

		//
		loopCtrl++;



		//
		DWORD  dwEvt = WaitForMultipleObjects(
			pMixProcInfo->thread.q2.cfg.usCnt_hEvents,	//  mycountof(  pPlay->hEvents  ),				// Number of events.
			pMixProcInfo->thread.q2.hEvents,							// Location of handles.
			FALSE,										// Wait for all?
			dwToInMs									// How long to wait?
		);										// Any message is an 
												 // event.
		if (dwEvt == WAIT_FAILED)  goto  errLabel;
		//
		//dwTickCnt = myGetTickCount(null);

		if (dwEvt != WAIT_TIMEOUT) {
			dwEvt -= WAIT_OBJECT_0;
			switch (dwEvt) {
			case  0:
				//  dwTickCnt_lastData  =  dwTickCnt;		//  audio data received
				  //  traceLogA(  (char*)  "mcThreadProcInfo_vpp: event 0."  );
				break;
			case  1:
				traceLogA((char*)"mcThreadProcInfo_mix: event 1.");
				break;
			default:
				traceLogA((char*)"unknown event");
				goto  errLabel;
				break;
			}
		}


		

			//
			if (bDbg) {
				tickCnt0 = myGetTickCount(mynull);
			}
			//
			doMix(pProcInfo, pMixProcInfo, &ctx);

			//
			if (bDbg) {
				tickCnt1 = myGetTickCount(mynull);
			}




			//
			if (bDbg) {
				//
				int  iDiffInMs = tickCnt1 - tickCnt0;
				int  iDiff_last = tickCnt0 - tickCnt_last;
				tickCnt_last = tickCnt0;
				//

				//
				if (iDiffInMs > 5  ||  iDiff_last  >  12) 
				{
					_sntprintf(tBuf, mycountof(tBuf), _T("mix: takes %dms to doMix, diff_last %dms. dwToInMs %d"), iDiffInMs, iDiff_last, dwToInMs);
					showInfo_open0(0, 0, tBuf);
				}

			}


		continue;
	}

	traceLogA((char*)"mcThreadProc_mix will quit");

errLabel:

	//  2010/12/28
	//
	dyn_exitAudioMixerObj(&ctx.pAudioMixerObj);

	//
	if (pMixProcInfo->fp_debug) {
		fclose(pMixProcInfo->fp_debug);
		pMixProcInfo->fp_debug = mynull;
	}
	//
	for (i = 0; i < pAecLayout->usCntLimit_activeMems_from; i++) {
		AEC_player_cfg* pMem = &pAecLayout->mems[i];
		if (pMem->fp_debug) {
			fclose(pMem->fp_debug); pMem->fp_debug = mynull;
		}
	}

	//
	pMixProcInfo->thread.bRunning = FALSE;


	//
	LPCTSTR  tHint = _T("");
	//
	traceLogA((char*)"mcThreadProc_mix %S leaves", pMixProcInfo->thread.q2.cfg.name);

#endif

	return  0;

}


