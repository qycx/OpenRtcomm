
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


//
int AEC_layout_init(int  iTaskId, unsigned  short  usCntLimit_activeMems_from, AEC_layout* pLayout)
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	//
	if (!pLayout)return  -1;
	if (iTaskId == 0)return  -1;
	if (usCntLimit_activeMems_from > mycountof(pLayout->mems)) return  -1;

	//
	memset(pLayout, 0, sizeof(AEC_layout));
	pLayout->iTaskId = iTaskId;
	pLayout->usCntLimit_activeMems_from = usCntLimit_activeMems_from;

	//
	GENERIC_Q_CFG		tmpCfg;
	TCHAR				tName[128];
	Mix_procInfo* pMixProcInfo = &pProcInfo->av.mixProcInfo;

	//
	if (pMixProcInfo->thread.bQInited) {
		showInfo_open0(0, 0, _T("AEC_layout_init failed, mixProcInfo.thread.bQInited true"));
		goto  errLabel;
	}

	//
	tmpCfg = pProcInfo->cfg.mixQ;
	_sntprintf(tName, mycountof(tName), _T("%s"), _T("mixQ"));
	if (initQyQ2(&tmpCfg, &pQyMc->cfg.rwLockParam, mycountof(pMixProcInfo->thread.q2.hEvents), CQyString(pQyMc->appParams.appObjPrefix) + tName, mallocMemory, mymalloc, 0, 0, freeMemory, myfree, NULL, &pMixProcInfo->thread.q2))  goto  errLabel;
	pMixProcInfo->thread.bQInited = true;

	//
#if 0
	if (pQyMc->b__USE_webrtc1__) {
		if (startQThread(mcThreadProc_mix, 0, null, &pMixProcInfo->thread)) {
			goto  errLabel;
		}
	}
#endif

	//
	iErr = 0;
errLabel:

	if (iErr) {
		AEC_layout_exit(pLayout);
	}


	//
	return  iErr;
}

//
int AEC_layout_exit(AEC_layout* pLayout)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	//
	Mix_procInfo* pMixProcInfo = &pProcInfo->av.mixProcInfo;
	//
	stopQThread(&pMixProcInfo->thread, _T(""));

	//
	if (pMixProcInfo->thread.bQInited) {
		exitQyQ2(&pMixProcInfo->thread.q2);  pMixProcInfo->thread.bQInited = false;
	}


	//
	memset(pLayout, 0, sizeof(AEC_layout));

	return  0;
}

//
int AEC_layout_chk(AEC_layout* pLayout)
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	//
	int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, pLayout->iTaskId);
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO  * )getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
	if (pTaskInfo == mynull)  goto  errLabel;
	QMC_taskData_conf* pTc; pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
	if (pTc->common.uiType != CONST_taskDataType_conf)  goto  errLabel;
	DLG_TALK_videoConference* pVc; pVc = &pTc->videoConference;
	if (pVc->usCntLimit_activeMems_from != pLayout->usCntLimit_activeMems_from) {
		showInfo_open0(0, 0, _T("AEC_layout_chk failed, usCntLimit_activeMems_from not matched"));
		goto  errLabel;
	}
	//
	int  i;
	for (i = 0; i < pVc->usCntLimit_activeMems_from; i++) {
		DLG_TALK_videoConferenceActiveMemFrom* pActiveMem = &pVc->activeMems_from[i];
		if (pActiveMem->avStream.idInfo.ui64Id != pLayout->mems[i].idInfo.ui64Id
			|| pActiveMem->avStream.obj.tranInfo.audio.uiTranNo_openAvDev != pLayout->mems[i].tn_a)
		{
			pLayout->mems[i].idInfo = pActiveMem->avStream.idInfo;
			pLayout->mems[i].tn_a = pActiveMem->avStream.obj.tranInfo.audio.uiTranNo_openAvDev;
		}
	}

	//
	for (i = 0; i < pLayout->usCntLimit_activeMems_from; i++) {
		AEC_player_cfg* pMem = &pLayout->mems[i];
		if (pMem->idInfo.ui64Id) {
			if (pMem->idInfo.ui64Id == pMisCnt->idInfo.ui64Id) {
				memset(&pMem->playerId, 0, sizeof(pMem->playerId));
				continue;
			}
			//
			QY_PLAYER* pPlayer = getPlayerByIndex(pProcInfo, pMem->playerId.index_player);
			if (pPlayer
				&& pPlayer->playerId.uiTranNo_player == pMem->playerId.uiTranNo_player
				&&  pPlayer->idInfo_recorder.ui64Id  ==  pMem->idInfo.ui64Id
				&&  pPlayer->audio.uiTranNo  ==  pMem->tn_a
				&& pPlayer->audio.uiPlayType
				&& bPlayerOk(pPlayer,mynull))
			{
				continue;
			}
			//
			memset(&pMem->playerId, 0, sizeof(pMem->playerId));
			//
			int j;
			for (j = 0; j < pProcInfo->av.usCnt_players; j++) {
				pPlayer = getPlayerByIndex(pProcInfo, j);
				if (pPlayer->audio.uiPlayType
					&& bPlayerOk(pPlayer,mynull)
					&&  pPlayer->idInfo_recorder.ui64Id  ==  pMem->idInfo.ui64Id
					&&  pPlayer->audio.uiTranNo  ==  pMem->tn_a
					)
				{
					pMem->playerId.index_player = j;
					pMem->playerId.uiTranNo_player = pPlayer->playerId.uiTranNo_player;
					continue;
				}
			}
			//
			continue;
		}
	}


	//
	iErr = 0;
	errLabel:

	return  iErr;
}


//
int  addToAecLayout(  void  *  pProcInfoParam,  PLAYER_ID  playerId,  AEC_layout  *  pLayout  )
{
	int  iErr  =  -1;
	int  i;

	CCtxQmc  *  pProcInfo  =  (  CCtxQmc  *  )pProcInfoParam;

	//
	if  (  playerId.index_player  <  0  ||  playerId.index_player  >=  pProcInfo->av.usCnt_players  )  return  -1;
	if  (  !playerId.uiTranNo_player  )  return  -1;
	
	//
	QY_PLAYER* pPlayer = getPlayerByIndex(pProcInfo, playerId.index_player);
	if (!pPlayer)return  -1;


	for  (  i  =  0;  i  <  mycountof(  pLayout->mems  );  i  ++  )  {
		AEC_player_cfg* pMem = &pLayout->mems[i];
		if (pMem->idInfo.ui64Id
			&& pMem->tn_a == pPlayer->audio.uiTranNo)
		{			
			if (isSame_playerId(&pMem->playerId, &playerId))  break;
		
			//
			pLayout->mems[i].playerId = playerId;

			//
			pLayout->usCnt++;

			//
			break;

		}
	}


	//
	pLayout->tn_modified  = getuiNextTranNo(0,0,0);

	//
#ifdef  __DEBUG__
	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "addToAecLayout ok, aec[%d], index_player %d, tn %d"  ),  i,  playerId.index_player,  playerId.uiTranNo_player  );
	traceLog((TCHAR*)  tBuf  );
#endif

	//
	iErr  =  0;
errLabel:

	return  iErr;
}

//
int  removeFromAecLayout(  void  *  pProcInfoParam,  PLAYER_ID  playerId,  AEC_layout  *  pLayout  )
{
	int  iErr =  -1;
	CCtxQmc  *  pProcInfo  =  (  CCtxQmc  *  )pProcInfoParam;

	if  (  playerId.index_player  <  0  ||  playerId.index_player  >=  pProcInfo->av.usCnt_players  )  return  -1;
	if  (  playerId.uiTranNo_player  ==  0  )  return  -1;
	
	QY_PLAYER* pPlayer = getPlayerByIndex(pProcInfo, playerId.index_player);
	if (!pPlayer) return  -1;

	int  i;

	for  (  i  =  0;  i  <  mycountof(  pLayout->mems  );  i  ++  )  {
		AEC_player_cfg* pMem = &pLayout->mems[i];
		if  (  pMem->idInfo.ui64Id  ==  pPlayer->idInfo_recorder.ui64Id
			&&  pMem->tn_a  ==  pPlayer->audio.uiTranNo 
			&&  isSame_playerId(  &pMem->playerId,  &playerId  )  )  
		{
			memset(&pMem->playerId, 0, sizeof(pMem->playerId));
			break;
		}
	}

	//
	pLayout->tn_modified  =  getuiNextTranNo(  0,  0,  0  );

	//
	if  (  pPlayer  )  {
		//emptyQ2(  &pPlayer->audio.aecPlayQ2  );
	}

		//
#ifdef  __DEBUG__
	if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
		TCHAR  tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("removeFromAecLayout ok, aec[%d], index_player %d, tn %d"), i, playerId.index_player, playerId.uiTranNo_player);
		traceLog((TCHAR*)tBuf);
	}
#endif


	//
	iErr  =  0;
	errLabel:
	return  iErr;
}

//
int  printAecLayout(  AEC_layout  *  pLayout  )  
{
	int  i;
	int  cnt  =  0;
	TCHAR  tBuf[128];

	for  (  i  =  0;  i  <  mycountof(  pLayout->mems  );  i  ++  )  {
		 if  (  pLayout->mems[i].playerId.uiTranNo_player  ==  0  )  continue;
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d: aec[%d], index_player %d, tn %d"  ),  cnt,  i,  pLayout->mems[i].playerId.index_player,  pLayout->mems[i].playerId.uiTranNo_player  );
		 traceLog((TCHAR*)  tBuf  );
		 cnt  ++  ;
		 continue;
	}
	if (  cnt  !=  pLayout->usCnt  )  {
		traceLog((TCHAR*)  _T(  "Error: aec_layout.usCnt not correct"  )  );
	}
	if  (  !cnt  )  {
		traceLog((TCHAR*)  _T(  "printAecLayout: cnt is 0"  )  );
	}

	return  0;
}




//
int exitAllAecObjs(  CTX_aec  *  pCtx  )
{		 
	if  (  pCtx->pAecObj  )  {
			 dyn_exitAecObj(  &pCtx->pAecObj  );
	
	}	
	
	return  0;
}


//
int  doAec(  CCtxQmc  *  pProcInfo, CAP_procInfo_recordSound  *  pRec,  ORG_audio_pkt  *  pPkt_mic,  CTX_aec  *  pCtx  )
{
	int  iErr =  -1;
	int  i;
	bool  bDbg  = false;
	TCHAR  tBuf[128];
	
#ifdef  __DEBUG__
	if  (  0  )  {
		//
		//traceLog((TCHAR*)  _T(  "没起作用，真奇怪"  )  );
		//
		return  0;
	}
#endif


	//
	QMC_aec_info  *  pAecInfo  =  &pProcInfo->av.aecInfo;
#if  0
	if  (  pAecInfo->aecLayout.tn_modified  !=  pCtx->layout.tn_modified  )  {
		//
#ifdef  __DEBUG__
		if  (  bDbg  )  {
			traceLog((TCHAR*)  _T(  "doAec: tn_layout changed"  )  );
		}
#endif
		//
		uint tn  =  pAecInfo->aecLayout.tn_modified;
		pCtx->layout=pAecInfo->aecLayout;
		pCtx->layout.tn_modified  =  tn;
		//
		for  (  i  =  0;  i  <  CONST_cntof_aecPlayers;  i  ++  )  {
			if  (  isSame_playerId(  &pCtx->mems[i].cfg.playerId,  &pCtx->layout.mems[i].playerId  )  )  continue;
			//
			dyn_exitAecObj(  &pCtx->mems[i].pObj  );
			//
			pCtx->mems[i].cfg.playerId=pCtx->layout.mems[i].playerId;
		}
		//
		int  cnt  =  0;
		for  (  i  =  0;  i  <  CONST_cntof_aecPlayers;  i  ++  )  {
			if  (  pCtx->mems[i].cfg.playerId.uiTranNo_player  )  cnt  ++  ;			 
		}
		pCtx->usCnt_aecObjs  =  cnt;
	}
#endif


	//
#ifdef  __DEBUG__
		//printAecLayout(  &pCtx->layout  );
#endif
	
	//
	int nQNodes_pRec  =  getQ2Nodes(  &pRec->aecThread.q2  );

	//
	for  (  i  =  0;  i  <  1;  i  ++  )  
	{
#if  0
		 AEC_obj_info  *  pMem  =  &pCtx->mems[i];
		 //
		 if  (  !pMem->cfg.playerId.uiTranNo_player  )  continue;
		 //
		 cnt  --  ;
		 //
		 QY_PLAYER  *  pPlayer  =  getPlayerByIndex(  pProcInfo,  pMem->cfg.playerId.index_player  );
		 if  (  !pPlayer  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doAec failed, getPlayerByIndex failed"  )  );
			 showInfo_open0(  0, 0, tBuf  );
			 traceLog((TCHAR*)  tBuf  );
			 goto  errLabel;
		 }
#endif
		 //
		 //
		 ORG_audio_pkt  pkt_render;
		 uint  len  =  sizeof(  pkt_render  );

		 
		 //
		 int  nQNodes_aecPlay  =  getQ2Nodes(  &pProcInfo->av.aecInfo.aecPlayQ2  );
		 if  (  0  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doAec: nQNodes_aecPlay %d, nQNodes_rec %d"  ),  nQNodes_aecPlay,  nQNodes_pRec  );
			 showInfo_open0(  0,  0,  tBuf  );
		 }
		 if  (  nQNodes_aecPlay  <  pProcInfo->av.aecInfo.aec_var.mql  )  {
			 pProcInfo->av.aecInfo.aec_var.mql  =  nQNodes_aecPlay;
		 }
		 uint  tickCnt  =  myGetTickCount(  mynull  );
		 if  (  abs(  (int)(tickCnt  -  pProcInfo->av.aecInfo.aec_var.dwTgt_start1)  )  >  2000  )  {
			 //
			 if  (  pProcInfo->av.aecInfo.aec_var.mql  >  1  &&  nQNodes_aecPlay  >  nQNodes_pRec  +  1  )  {
				 //
				 len  =  sizeof(  pkt_render  );				
				  q2GetMsg(  &pProcInfo->av.aecInfo.aecPlayQ2,  &pkt_render,  &len,  _T(  "doAec"  ));
				  //
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doAec: remove a aecPlay pkt"  )  );
				  showInfo_open0(  0,  0,  tBuf  );
			 }
			 //
			 pProcInfo->av.aecInfo.aec_var.dwTgt_start1  =  tickCnt;
			 //
			 pProcInfo->av.aecInfo.aec_var.mql  =  nQNodes_aecPlay;
		 }


		 
		 //
		 len  =  sizeof(  pkt_render  );
		 if  (  q2GetMsg(  &pProcInfo->av.aecInfo.aecPlayQ2,  &pkt_render,  &len,  _T(  "doAec2"  ))) {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doAec: q2GetMsg failed"  )  );
			 showInfo_open0(  0,  0,  tBuf  );
			 continue;
		 }

		 //


		 //
#ifdef  __DEBUG__
		 if  (  bDbg  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doAec: render, len %d"  ),  pkt_render.len  );
			 traceLog((TCHAR*)  tBuf  );
		 }
#endif

		 //		
		 if  (  !pCtx->pAecObj  )  {				
			 dyn_initAecObj(  16000,  &pCtx->pAecObj  );			
		 }

		 //
		 if  (  !pCtx->pAecObj  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doAec err: pMem->pObj is null"  )  );
			 showInfo_open0(  0,  0,  tBuf  );
#ifdef  __DEBUG__
			 traceLog((TCHAR*)  tBuf  );
#endif
			 continue;
		 }
		 //
		 dyn_aecObj_doAec(  pCtx->pAecObj,  pkt_render.buf,  pkt_render.len,  pPkt_mic->buf,  pPkt_mic->len  );
		 //
		 continue;
	}


	//
	iErr  =  0;
	errLabel:
	return  iErr;
}



//
 extern "C" DWORD WINAPI mcThreadProc_aec( LPVOID lpParameter )
{
	 //int							iIndex_sharedObj			=	(  int  )lpParameter;

	 QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();
	 if  (  !pQyMc  )  {
		 return  -1;
	 }
	 CCtxQmc					*	pProcInfo					=	(CCtxQmc  *  )pQyMc->get_pProcInfo(  );
	 if (  !pProcInfo  )  return  -1;
	 QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	 if  (  !pQmcCfg  )  return  -1;

	 bool  bDbg  =  false;
#ifdef  __DEBUG__
		//bDbg  =  true;
#endif
	TCHAR  tBuf[128];

	//	 
	CAP_procInfo_recordSound  *  pRec  =  &pProcInfo->av.localAv.recordSoundProcInfo;


#if  10

	 //  2009/12/24

	 //
	 DWORD							dwThreadId					=	GetCurrentThreadId(  );


	 MIS_CNT					*	pMisCnt						=	(  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;	 	 

	 CQyMalloc						mallocObj_pMsgBuf;
	 MIS_MSGU					*	pMsgBuf						=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;


	 DWORD							dwTickCnt;

	 //  2010/09/18
	 //  int							tmpiRet;
	 BOOL							tmpbErr;

	 uint  tickCnt_last  =  0;
	 uint  tickCnt0  =  0;
	 uint  tickCnt1  =  0;

	 CTX_aec						ctx;
	 memset(  &ctx,  0,  sizeof(  ctx  )  );

	 //
	 traceLogA(  (char*)  "mcThreadProc_aec %S enters",  pRec->aecThread.q2.cfg.name  );

	 pRec->aecThread.bQuit  =  FALSE;
	 pRec->aecThread.bRunning  =  TRUE;

	 
	 //  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u starts"  ),  pPlay->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id  );
	 
	 /////////////////
	 for  (  ;  !pRec->aecThread.bQuit;  )  {
		  
		  //  2010/12/28
		  uint  dwToInMs  =  10;	//5000;
		  dwToInMs  =  9;

		  //
		  DWORD  dwEvt  =  WaitForMultipleObjects(
			  pRec->aecThread.q2.cfg.usCnt_hEvents,	//  mycountof(  pPlay->hEvents  ),				// Number of events.
			  pRec->aecThread.q2.hEvents,							// Location of handles.
                             FALSE,										// Wait for all?
							 dwToInMs									// How long to wait?
                               );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  goto  errLabel;
	      //
		  dwTickCnt  =  GetTickCount(  );

		  if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
			  dwEvt -= WAIT_OBJECT_0;
			  switch  (  dwEvt  )  {
					  case  0:
						     //  dwTickCnt_lastData  =  dwTickCnt;		//  audio data received
						       //  traceLogA(  (char*)  "mcThreadProcInfo_vpp: event 0."  );
							 break;
					  case  1:
						     traceLogA(  (char*)  "mcThreadProcInfo_vpp: event 1."  );
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
		  }

	
		  for  (  ;  !pRec->aecThread.bQuit;  )  {
			  					  
			  //  2014/04/10
			  ORG_audio_pkt pkt;
			  unsigned  int  len = sizeof( pkt  );
			  if  (  q2GetMsg(  &pRec->aecThread.q2,  (  void  *  )&pkt,  &len,  _T(  "mcThreadProc_aec"  ))) {
				  break;			   						  				
			  }

			  //
			  if  (  bDbg  )  {			  
				  tickCnt0  =  myGetTickCount(  mynull  );
			  }
			  //
			  doAec(  pProcInfo,  pRec,  &pkt,  &ctx  );

			  //
			  if  (  bDbg  )  {
				  tickCnt1  =  myGetTickCount(  mynull  );
			  }


			  int  nAvgBytesPerSec  =  pRec->compressAudio.ah_decompress.wfx.nAvgBytesPerSec;
			  //
			  processInput_post(  pProcInfo,  nAvgBytesPerSec,  (byte  *  )pkt.buf,  pkt.len,  pMsgBuf  );
			  
			  //
			  if  (  bDbg  )  {
				  int  iDiffInMs  =  tickCnt1  -  tickCnt0;
				  int  iDiff_last  =  tickCnt0  -  tickCnt_last;
				  tickCnt_last  =  tickCnt0;
				  traceLog((TCHAR*)  _T(  "aec: takes %dms to doAec, diff_last %dms"  ),  iDiffInMs,  iDiff_last  ); 

			  }

			  //
			  continue;
		  }

		  continue;
	 }

	 traceLogA(  (char*)  "mcThreadProc_aec will quit"  );

errLabel:

	 //  2010/12/28
	 exitAllAecObjs(  &ctx  );
	 
	 //
	 pRec->aecThread.bRunning  =  FALSE;


	 //
	 LPCTSTR  tHint  =  _T(  ""  );
	 //
	 traceLogA(  (char*)  "mcThreadProc_aec %S leaves",  pRec->aecThread.q2.cfg.name  );
	
#endif

	 return  0;

}


