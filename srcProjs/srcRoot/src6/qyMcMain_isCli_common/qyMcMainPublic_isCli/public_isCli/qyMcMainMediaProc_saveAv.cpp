


#include	"stdafx.h"

#include	<stddef.h>
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#include	"qmcSound_dx.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qmOpenCommon.h"
#include	"saveAvProc_open.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliSaveAvPublic.h"
//
#include	"ctxMcThread.h"
#include	"ctxQmc.h"
#include <saveAvCommProc.h>


//
BOOL  canSave_fourcc(int  iFourcc)
{
	switch (iFourcc) {
	case  CONST_fourcc_h264:
	case  CONST_fourcc_vp80:
		return  TRUE;
		break;
	default:
		break;
	}
	return  FALSE;
}



#ifdef  __DEBUG__

#endif


//
SAVE_av_procInfo* getSaver(int index_saver)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	if (index_saver < 0 || index_saver >= pProcInfo->av.usCnt_saveAvProcInfos) return  nullptr;
	SAVE_av_procInfo* p = nullptr;
	void* pSavers = pProcInfo->av.pSaveAvProcInfos;
	p = (SAVE_av_procInfo*)((char*)pSavers + pProcInfo->av.sizeof_mySaveAvProcInfo * index_saver);

	return  p;
}


//
//
bool  bUse_saveAvTest(TCHAR* smCfgFile)
{
	bool  bRet = false;

	//
	CCtxQyMc* pQyMc = g_pQyMc;


	TCHAR  cfgVal[128]  =  _T("");

	//USB Video Device
	getCfgValByNameT(smCfgFile, (TCHAR*)CONST_cfgName_saveAvTest, cfgVal, mycountof(cfgVal));
	tTrim(cfgVal);
	int  tmpiRet = _ttol(cfgVal);

	bRet = tmpiRet;

	//	 
	return  bRet;

}



//
extern "C" DWORD WINAPI mcThreadProc_saveAv(LPVOID lpParameter)
{
	int								iErr = -1;

	//int  index_saver							=	(  int  )lpParameter;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;

	//	 
	//SAVE_av_procInfo* pSave = getSaver(index_saver);
	SAVE_av_procInfo* pSave = (SAVE_av_procInfo*)lpParameter;// 


	QY_MC* pQyMc = (QY_MC*)pProcInfo->pQyMc;
	DYN_LIB_DX* pDynLib = (DYN_LIB_DX*)((QY_DYN_LIBS*)pQyMc->env.pDynLibs)->pLib_dx;
	//  int								i;

	int								i;


#define		DEFAULT_dwToInMs		5000
	DWORD								dwToInMs = DEFAULT_dwToInMs;

	DWORD								dwTickCnt_lastVideoData = GetTickCount();;						// 

	CQyMalloc							mallocObj_pSvp;
	SAVE_av_pktU* pSp = (SAVE_av_pktU*)mallocObj_pSvp.mallocf(sizeof(SAVE_av_pktU));
	if (!pSp)  return  -1;



	BOOL								bPktsRedirected;

	CQyCoInit							coInit;		//  2010/06/07

	CTX_mc_saveAv					ctx;		//  2014/03/07

	//
	memset(&ctx, 0, sizeof(ctx));

	traceLogA((char*)"mcThreadProc_saveAv enters");

	//MACRO_setStep(  pSave->debugStep,  CONST_threadStep_start  );


	//  2014/05/08
	//_sntprintf(  pSave->debugStep.showInfo.tWhere,  mycountof(  pSave->debugStep.showInfo.tWhere  ),  _T(  "saveAv %d:%d"  ),  pTransform->iTaskId,  pTransform->index_activeMems_from  );
	//pSave->debugStep.showInfo.uiStep  =  0;

	//
	ctx.uiBufSize_pBuf = 1024;
	ctx.pBuf_forSaving = (unsigned  char*)mymalloc(ctx.uiBufSize_pBuf);
	if (!ctx.pBuf_forSaving)  goto  errLabel;

	//
	pSave->bRunning = TRUE;
	//  memset(  &pSave->m_var,  0,  sizeof(  pSave->m_var  )  );

#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("Note: 这里最好能根据情况，将maxMsgs自动调整，对每个transform,分配10个misMsgU, 是很浪费的 "));
#endif

	//
	ctx.bSaveAvTest = bUse_saveAvTest(pQyMc->cfg.smCfgFile);


	//qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  pSave->debugStep.showInfo.tWhere,  _T(  ""  ),  _T(  "%s %d starts"  ),  pSave->q2.cfg.name,  pTransform->index_activeMems_from  );

#if 0
	for (; !pSave->bQuit; ) {

		if (!dwToInMs) {
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Warning: mcThreadProc_transformVideo: dwToInMs %d"), dwToInMs);
			dwToInMs = DEFAULT_dwToInMs;
		}

		//  2009/07/14
		//MACRO_setStep(  pSave->debugStep,  CONST_threadStep_toWait  );

		//
		DWORD  dwTickCnt0 = GetTickCount();
		DWORD  dwTickCnt;
		DWORD  dwEvt = MsgWaitForMultipleObjects(
			pSave->q2.cfg.usCnt_hEvents,		// mycountof(  pSave->hEvents  ),		// Number of events.
			pSave->q2.hEvents,				// Location of handles.
			FALSE,										// Wait for all?
			dwToInMs,									// How long to wait?
			0);										// Any message is an 
		// event.
		if (dwEvt == WAIT_FAILED) {
			iErr = -110;
			goto  errLabel;
		}
		//
		dwTickCnt = GetTickCount();

		if (dwEvt != WAIT_TIMEOUT) {
			dwEvt -= WAIT_OBJECT_0;
			switch (dwEvt) {
			case  0:
				dwTickCnt_lastVideoData = dwTickCnt;		//  audio data received
				break;
			case  1:
				traceLogA((char*)"transformVideo: event 1.");
				break;
			default:
				traceLogA((char*)"unknown event");
				iErr = -120;
				goto  errLabel;
				break;
			}
		}

		if (isQ2Empty(&pSave->q2))  continue;

		BOOL  bExists_svp = FALSE;
		for (; !pSave->bQuit; ) {

			//
			//MACRO_setStep(  pSave->debugStep,  CONST_threadStep_toGetMsg  );


			dyn_doSaveAv(pSave, pSp, &bExists_svp, &ctx);
			if (bExists_svp)  continue;

			if (isQ2Empty(&pSave->q2))  break;

		}
	}
#endif

	//
	BOOL  bExists_svp; bExists_svp = false;
	dyn_doSaveAv(pSave, pSp, &bExists_svp, &ctx);



	//
	iErr = 0;

errLabel:

	//
	//MACRO_setStep(  pSave->debugStep,  CONST_threadStep_toExit  );
	//pSave->debugStep.iErr_thread  =  iErr;

#if  0
	 //  2014/03/04
	qdcExitSplInfo(&g_splInfo);
	bInited_splInfo = FALSE;
#endif

	//
	//qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s %d ends."  ),  pSave->q2.cfg.name,  pTransform->index_activeMems_from  );


	pSave->bRunning = FALSE;

	//  2015/05/09
	MACRO_safeFree(ctx.pBuf_forSaving);

	//
	//MACRO_setStep(  pSave->debugStep,  CONST_threadStep_end  );

	traceLogA((char*)"mcThreadProc_transformVideo %S leaves", pSave->q2.cfg.name);

	return  0;
}


//



//
//int  initSaver(bool  bResource,  time_t  t,  int index_saver)
int  initSaver(bool  bResource, time_t  t, unsigned  __int64  peerId,  int  iTaskId, int  iSaverType,  int  index_trans, TCHAR* hint, SAVE_av_procInfo* pSave)
{
	int  iErr = -1;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	CCtxQyMc* pQyMc = g_pQyMc;

	if (!hint)  hint = (TCHAR*)_T("");


#if 10
	GENERIC_Q_CFG  tmpCfg;
	//
	//CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	QMC_cfg* pQmcCfg = (QMC_cfg*)pProcInfo->get_qmc_cfg();
	if (!pQmcCfg)  return  -1;
	//
	RW_lock_param* pQyMc_rwLockParam = pProcInfo->get_qyMc_rwLockParam();
	if (!pQyMc_rwLockParam)  return -1;
	GENERIC_Q_CFG* p_cfg_transformQ = &pQmcCfg->transformQ;//Ctx->get_cfg_transformQ(  );
	if (!p_cfg_transformQ)  return  -1;

	//
	//SAVE_av_procInfo* pSave = getSaver(index_saver);//

	//
	pSave->bResource = bResource;

	//
	pSave->peerId = peerId;


	//
	//int  iTaskId = 0;
	//int  i = 0;
	int  i = index_trans;

	//
	pSave->iType = iSaverType;
	pSave->index = i;
	//



	//
	//if (pTask->saveVideo.ucbSaveVideo_req) 
	{
		memcpy(&tmpCfg, p_cfg_transformQ, sizeof(tmpCfg));
		_sntprintf(tmpCfg.name, mycountof(tmpCfg.name), _T("%s-s-%d-%d"), tmpCfg.name, iTaskId, i);
		_sntprintf(tmpCfg.mutexName_prefix, mycountof(tmpCfg.mutexName_prefix), _T("%s-s-%d-%d"), tmpCfg.mutexName_prefix, iTaskId, i);
		//
		tmpCfg.uiMaxQNodes = CONST_uiMaxQNodes_saveQ;
		//  
		//if  (  initQyQ2(  &tmpCfg,  pQyMc_rwLockParam,  mycountof(  p->saveThread.q2.hEvents  ),  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &p->saveThread.q2  )  )  goto  errLabel;
		if (initQyQ2(&tmpCfg, pQyMc_rwLockParam, mycountof(pSave->q2.hEvents), NULL, mallocMemory, mymalloc, 0, 0, freeMemory, myfree, NULL, &pSave->q2))  goto  errLabel;
		pSave->bQInited = TRUE;
	}
#endif

	//
	getSaveAvDir(pSave->tDir, mycountof(pSave->tDir));
	char  timeBuf[32];
	getTimelStr(t, timeBuf, mycountof(timeBuf));
	//_sntprintf(pSave->pureFileName_prefix, mycountof(pSave->pureFileName_prefix), _T("conf%S-%d"), timeBuf, index_saver);
	int  tmp_i_reserved; tmp_i_reserved = 0;
	_sntprintf(pSave->pureFileName_prefix, mycountof(pSave->pureFileName_prefix), _T("conf%S-%d"), timeBuf, tmp_i_reserved);

	//
	Mcu_initCfg  mi;
	memset(&mi, 0, sizeof(mi));
	bGetMcuInitCfg(pQyMc->cfg.smCfgFile, &mi);

	//
	//safeTcsnCpy(_T("c:\\tttbbb\\124\\ffmpeg.exe"), pSave->ffmpegPath, mycountof(pSave->ffmpegPath));
	safeTcsnCpy(mi.tFfmpegPath, pSave->ffmpegPath, mycountof(pSave->ffmpegPath));

	//
	TCHAR  tBuf[256];
	_sntprintf(tBuf, mycountof(tBuf), _T("initSaver: %d: [%s]"), tmp_i_reserved, pSave->tDir);
	showInfo_open0(0, 0, tBuf);
	_sntprintf(tBuf, mycountof(tBuf), _T("initSaver: %d: [%s] "), tmp_i_reserved, pSave->ffmpegPath);
	showInfo_open0(0, 0, tBuf);
	_sntprintf(tBuf, mycountof(tBuf), _T("initSaver: %s, taskId %d, index_trans %d"), hint, iTaskId, index_trans);
	showInfo_open0(0, 0, tBuf);


	//
	iErr = 0;
errLabel:
	return  iErr;

}


//int exitSaver(int index_saver)
int exitSaver(SAVE_av_procInfo* pSave)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	//SAVE_av_procInfo* pSave = getSaver(index_saver);

	if (pSave->bQInited) {
		exitQyQ2(&pSave->q2);
		pSave->bQInited = FALSE;
	}

	return  0;
}


//int startSaver(int index_saver)
int startSaver(SAVE_av_procInfo* pSave)
{
	int  iErr = -1;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	//SAVE_av_procInfo* pSave = getSaver(index_saver);
	DWORD  dwThreadDaemonId;

	//
#if 10
	//if (pTask->saveVideo.ucbSaveVideo_req) 
	{
		if (!pSave->hThread) {
			//
			pSave->bQuit = FALSE;
			//pSave->hThread = CreateThread(NULL, 0, mcThreadProc_saveAv, (void*)index_saver, CREATE_SUSPENDED, &dwThreadDaemonId);
			pSave->hThread = CreateThread(NULL, 0, mcThreadProc_saveAv, (void*)pSave, CREATE_SUSPENDED, &dwThreadDaemonId);
			if (!pSave->hThread)  goto  errLabel;
			pSave->dwThreadId = dwThreadDaemonId;
			if (ResumeThread(pSave->hThread) == -1)  goto  errLabel;

			//  2012/03/25
			//InterlockedIncrement(&pStatus->nThreads_dec);

		}
	}
#endif

	iErr = 0;
errLabel:
	return  iErr;
}


//int stopSaver(int index_saver)
int stopSaver(SAVE_av_procInfo* pSave)
{
	int  iErr = -1;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	//SAVE_av_procInfo* pSave = getSaver(index_saver);
	TCHAR  tBuf[128] = _T("");

	//2014/08/04
#if 10
	if (pSave->hThread) {
		pSave->bQuit = TRUE;
		//
		SetEvent(pSave->q2.hEvents[0]);
		waitForObject(&pSave->hThread, 20000);
		//
		//tmp_getHint_video(pTask, pTask, tBuf, mycountof(tBuf));
		//
		if (pSave->hThread) {
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T("Failed"), tBuf);
		}
		//else  InterlockedDecrement(&pStatus->nThreads_dec);

	}
	if (pSave->hThread) {
		pSave->bQuit = TRUE;
		//
		SetEvent(pSave->q2.hEvents[0]);
		waitForObject(&pSave->hThread, 20000);
		//
		//tmp_getHint_video(pTask, p, tBuf, mycountof(tBuf));
		//
		if (pSave->hThread) {
			qyExitProcess(tBuf);
		}
		//else  InterlockedDecrement(&pStatus->nThreads_dec);
	}
#endif

	iErr = 0;
	return  iErr;

}


//
int initSavers(bool  bRecord_conf,  bool  bRecord_trans, bool bLive, TCHAR* liveUrl, __int64 meetingId, unsigned  __int64  peerId, int iTaskId)
{
	int  iErr = -1;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	TCHAR  tBuf[128];

	if (!liveUrl)  liveUrl = (TCHAR*)_T("");

	//
	_sntprintf(tBuf, mycountof(tBuf), _T("initSavers enters: bRecord_conf %d, bRecord_trans %d, bLive %d, liveUrl %s,  peerId %I64u"), bRecord_conf, bRecord_trans, bLive, liveUrl, peerId);
	showInfo_open0(0, 0, tBuf);

	//
	int  i;

	//
	time_t  t;
	time(&t);

	//
	for (i = 0; i < pProcInfo->av.usCnt_saveAvProcInfos; i++) {
		//
		SAVE_av_procInfo* pSave = getSaver(i);

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("initSavers: i %d"), i);
		if (initSaver(false, t, peerId,  iTaskId, CONST_saverType_conf,  i, tBuf, pSave))  goto  errLabel;

		//
		pSave->bRecord_conf = bRecord_conf;
		pSave->bRecord_trans = bRecord_trans;	//  2026/04/13
		//
		pSave->bLive = bLive;
		safeTcsnCpy(liveUrl, pSave->liveUrl, mycountof(pSave->liveUrl));
		pSave->meetingId = meetingId;

		//
		pSave->peerId = peerId;

		//
		//if (bRecord) 	
		{
			if (startSaver(pSave))  goto  errLabel;
		}
		//
		continue;
	}

	iErr = 0;
errLabel:

	showInfo_open0(0, 0, _T("initSavers leaves"));

	return  iErr;

}

int exitSavers()
{
	int  iErr = -1;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	showInfo_open0(0, 0, _T("exitSavers enters"));

	int  i;
	for (i = 0; i < pProcInfo->av.usCnt_saveAvProcInfos; i++) {
		SAVE_av_procInfo* pSave = getSaver(i);
		stopSaver(pSave);
		exitSaver(pSave);
	}

	//



	//
	iErr = 0;
errLabel:

	showInfo_open0(0, 0, _T("exitSavers leaves"));

	return  iErr;
}

