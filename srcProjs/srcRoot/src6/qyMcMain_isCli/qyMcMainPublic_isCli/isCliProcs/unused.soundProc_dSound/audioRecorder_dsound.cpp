
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qyPlaySound_wave.h"
#include	"QyRecordSound_wave.h"
#include	"module_qisCamCap.h"
#include	"isCliHelpPublic.h"

#include	"qmcCommFunc_isCli.h"
#include	"sqWin32aec.h"
//
#include	"qisWebRtcPublic.h"
#include	"isCliHelpPublic.h"
#include	"qmcFunc.h"

//


 //  2017/06/15
 int  startLocalAudioRecorder(  QY_MC  *  pQyMc,  unsigned  int  uiRecordType,  void  *  pGuid,  LPCTSTR  capDevDesc,  int  iIndex_sharedObj, unsigned  short  usCntLimit_activeMems_from,  AUDIO_COMPRESSOR_CFG  *  pCompressor  )
{
	int						iErr					=		-1;
	//QY_MC				*	pQyMc					=		QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProcInfo				=		QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	DWORD					dwThreadDaemonId		=		0;
	BOOL					bAudioCompressInited	=		FALSE;

	//
#ifdef  __DEBUG__
	traceLogA(  (char*)  (  "startLocalAudio enters.\n"  )  );
#endif

	if  (  !pCompressor  )  {
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "startLocalAudioRecorder failed, pCompressor is null"  )  );
#endif
		return  -1;
	}

	if  (  !pProcInfo->ucb_doInitRecordSound  )  {
		MODULE_camCap	*	pCamCap	=	(  MODULE_camCap  *  )getCusModule(  &pQyMc->cusModules,  CONST_moduleType_camCap  );
		if  (  pCamCap  
			&&  pCamCap->pf_doInitRecordSound
			&&  pCamCap->pf_doExitRecordSound  )
		{
			pCamCap->pf_doInitRecordSound(  );
		}
		pProcInfo->ucb_doInitRecordSound  =  TRUE;
	}
	
	//  2013/08/02
	CAP_procInfo_recordSound  *  pCapAudio  =  NULL;
	pCapAudio  =  &pProcInfo->av.localAv.recordSoundProcInfo;
	QY_qThreadProcInfo_common  *  pRecThread  =  &pProcInfo->av.localAv.recordSoundProcInfo.recThread;
	
	//
#if  0
	waitForQThread(  pRecThread, 0  );
	if  (  bQThreadExists(  *pRecThread  )  )  {
		traceLogA(  (char*)  "startLocalAudioRecorder: thread already active. "  );
		goto  errLabel;
	}
#endif

	//
	QY_SHARED_OBJ	*	pSharedObj;
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	pSharedObj->bSoundRecorder  =  TRUE;


	//  2013/03/18
	if  (  pProcInfo->av.localAv.recordSoundProcInfo.bCapDevConnected  )  goto  errLabel;
	
	//
	pProcInfo->av.localAv.recordSoundProcInfo.uiType  =  CONST_capType_av;
	pProcInfo->av.localAv.recordSoundProcInfo.iIndex_sharedObj  =  iIndex_sharedObj;
	pProcInfo->av.localAv.recordSoundProcInfo.uiRecordType  =  uiRecordType;
	//
	pProcInfo->av.localAv.recordSoundProcInfo.capDevDesc[0]  =  0;
	pProcInfo->av.localAv.recordSoundProcInfo.aec_rendDevDesc[0]  =  0;
	safeTcsnCpy(  capDevDesc,  pProcInfo->av.localAv.recordSoundProcInfo.capDevDesc,  mycountof(  pProcInfo->av.localAv.recordSoundProcInfo.capDevDesc  )  );


	//  2009/05/24
	//  if  (  !pCompressor  )  pCompressor  =  &pProcInfo->cfg.policy.taskAv_pc.avCompressor.audio;

	WAVEFORMATEX* pWf_input; pWf_input = NULL;
	//  2013/03/18
	switch  (  uiRecordType  )  {
			case  CONST_recordType_directX:
				  TCHAR  *  pDisplayName;
				  pDisplayName  =  (  TCHAR  *  )pGuid;
				  if  (  initAudioCapDev_dx(  NULL,  pDisplayName,  NULL,  pCompressor,  FALSE,  pQyMc->gui.hMainWnd,  iIndex_sharedObj,  &pProcInfo->av.localAv.recordSoundProcInfo.u.dx.pAudioCapDev  )  )  goto  errLabel;
				  pProcInfo->av.localAv.recordSoundProcInfo.bCapDevConnected  =  TRUE;

				  if  (  !bGetCapturePara_audioCapdev(  (  MC_VAR_common  *  )pProcInfo,  pSharedObj->iIndex_capAudio,  sizeof(  MIS_MSGU  ),  pProcInfo->av.localAv.recordSoundProcInfo.u.dx.pAudioCapDev,  &pProcInfo->av.localAv.recordSoundProcInfo.wf_org,  NULL  )  )  goto  errLabel;
				  pWf_input  =  &pProcInfo->av.localAv.recordSoundProcInfo.wf_org;
				  break;
			default:
					break;
	}
	if  (  !pWf_input  )  {
		memcpy(  &pProcInfo->av.localAv.recordSoundProcInfo.wf_org,  &pCompressor->wf_decompress_default,  sizeof(  pProcInfo->av.localAv.recordSoundProcInfo.wf_org  )  );
		pWf_input  =  &pProcInfo->av.localAv.recordSoundProcInfo.wf_org;
	}
	
	//	
	//  2016/12/10
	pCompressor->common.pAudioQ2  =  &pCapAudio->thread.q2;
	pCompressor->common.pParent_transform  =  pCapAudio;
	//
	if  (  initCompressAudio(  pProcInfo,  pWf_input,  pCompressor,  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio  )  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "startLocalAudioRecorder failed, initCompressAudio failed"  )  );
		#endif
		//
		goto  errLabel;
	}
	bAudioCompressInited  =  TRUE;
	

	//  2013/08/02
	GENERIC_Q_CFG		tmpCfg;
	//  DWORD	dwThreadDaemonId;
	TCHAR	tName[128];
			
	if  (  1  )  {
		//
		memcpy(  &tmpCfg,  &pProcInfo->cfg.toShareAudioQ,  sizeof(  tmpCfg  )  );
		_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%d"  ),  tmpCfg.name,  pSharedObj->uiTranNo  );
		_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%d"  ),  tmpCfg.mutexName_prefix,  pSharedObj->uiTranNo  );
		_sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%u"  ),  CONST_evtName_qm_data_a,  pSharedObj->uiTranNo  );
		if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapAudio->thread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myPLAY_AUDIO_DATA,  &pCapAudio->thread.q2  )  )  goto  errLabel;
		pCapAudio->thread.bQInited  =  TRUE;

		//  2017/01/29
		memcpy(  &tmpCfg,  &pProcInfo->cfg.appQ,  sizeof(  tmpCfg  )  );
		_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%d"  ),  tmpCfg.name,  pSharedObj->uiTranNo  );
		_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%d"  ),  tmpCfg.mutexName_prefix,  pSharedObj->uiTranNo  );
		_sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%u"  ),  CONST_evtName_qm_app,  pSharedObj->uiTranNo  );
		if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapAudio->appThread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myPLAY_AUDIO_DATA,  &pCapAudio->appThread.q2  )  )  goto  errLabel;
		pCapAudio->appThread.bQInited  =  TRUE;

		//
		tmpCfg  =  pProcInfo->cfg.aecQ;
		_sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s"  ),  _T(  "aecQ"  )  );
		if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapAudio->aecThread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &pCapAudio->aecThread.q2  )  )  goto  errLabel;
		pCapAudio->aecThread.bQInited  =  true;

		//
		if  (  !pCapAudio->thread.hThread  )  {
			//
			pCapAudio->thread.bQuit  =  FALSE;			
			pCapAudio->thread.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_toShareAudio,  (  LPVOID  )iIndex_sharedObj,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			if  (  !pCapAudio->thread.hThread  )  goto  errLabel;					
			pCapAudio->thread.dwThreadId  =  dwThreadDaemonId;			
			if  (  ResumeThread(  pCapAudio->thread.hThread  )  ==  -1  )  goto  errLabel;									 
		}
		
		//  2017/01/29
		  if  (  !pCapAudio->appThread.hThread  )  {
			  //
			  pCapAudio->appThread.bQuit  =  FALSE;			
			  pCapAudio->appThread.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_app,  (  LPVOID  )iIndex_sharedObj,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			  if  (  !pCapAudio->appThread.hThread  )  goto  errLabel;					
			  pCapAudio->appThread.dwThreadId  =  dwThreadDaemonId;			
			  if  (  ResumeThread(  pCapAudio->appThread.hThread  )  ==  -1  )  goto  errLabel;									 
		  }

	}

	//  2017/06/19
	pRecThread->bQuit  =  FALSE;
	pRecThread->bRunning  =  FALSE;

	//
	switch  (  uiRecordType  )  {
			case  CONST_recordType_dSound:  {	
				  //pRecThread->bQuit  =  FALSE;
				  pRecThread->hThread  =  CreateThread(  NULL,  0,  mcThreadProc_recordSound,  0,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
				  if  (  !pRecThread->hThread  )  goto  errLabel;
				  //
				  if  (  pGuid  )  pProcInfo->av.localAv.recordSoundProcInfo.guid_aDevice  =  *(  GUID  *  )pGuid;		//  2011/10/24
				  else  memset(  &pProcInfo->av.localAv.recordSoundProcInfo.guid_aDevice,  0,  sizeof(  pProcInfo->av.localAv.recordSoundProcInfo.guid_aDevice  )  );
				  //
				  pRecThread->dwThreadId  =  dwThreadDaemonId;
				  if  (  ResumeThread(  pRecThread->hThread  )  ==  -1  )  goto  errLabel;
				  }
				  break;
#ifdef __USE_msAec__
			case  CONST_recordType_msAec:		//  2013/05/22
				{
#if  0
				  AEC_cfg  aecCfg;
				  memset(  &aecCfg,  0,  sizeof(  aecCfg  )  );
				  getAecCfg(  HKEY_CURRENT_USER,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  &aecCfg  );

				  //
				  if  (  aec_snd_StartRecording(  &aecCfg,  pCompressor->wf_decompress_default.nSamplesPerSec,  pCompressor->wf_decompress_default.nChannels  >  1,  0,  (  GUID  *  )pGuid  )  )  goto  errLabel;
#endif
				  //
				  //
				  if  (  pGuid  )  pProcInfo->av.localAv.recordSoundProcInfo.guid_aDevice  =  *(  GUID  *  )pGuid;		//  2011/10/24
				  else  memset(  &pProcInfo->av.localAv.recordSoundProcInfo.guid_aDevice,  0,  sizeof(  pProcInfo->av.localAv.recordSoundProcInfo.guid_aDevice  )  );
				  
#if  10
				  //
				  //CAP_procInfo_recordSound  *  pRecordSoundProcInfo  =  &pProcInfo->av.localAv.recordSoundProcInfo;
				  
				  //  Create  the thread
				  //QY_qThreadProcInfo_common  *  pRecThread  =  &pRecordSoundProcInfo->recThread;
				  //pRecThread->bQuit  =  FALSE;
				  pRecThread->hThread  =  CreateThread(  NULL,  128*1024,  msAecRecThreadFunc,  NULL,  STACK_SIZE_PARAM_IS_A_RESERVATION,  NULL  );
				  if  (  !pRecThread->hThread  )  {
					  //CHECK_START_RECORDING_HR(  E_FAIL,  (  _T(  "Failed: CreateThread() in aec_snd_StartRecording\n"  ),  hr  )  );
					  goto  errLabel;	
				  }

#endif
				  
				  //  2013/05/24. 在aec的情况下,需要自动启动一个player, 以便recorder能建立对render和capture的关联.		
				  if  (  uiRecordType  ==  CONST_recordType_msAec  )  {		
					  startLocalAudioPlayer(  pProcInfo  );					  	
				  }

				}
				  break;
				  //  2017/01/28
#endif
			case  CONST_recordType_coreAudio:  {
				  //
				  if  (  startQThread(  mcThreadProc_aec,  0,  NULL,  &pCapAudio->aecThread  )  )  {
					  goto  errLabel;
				  }
				  //
				  if  (  pGuid  )  pProcInfo->av.localAv.recordSoundProcInfo.guid_aDevice  =  *(  GUID  *  )pGuid;		//  2011/10/24
				  else  memset(  &pProcInfo->av.localAv.recordSoundProcInfo.guid_aDevice,  0,  sizeof(  pProcInfo->av.localAv.recordSoundProcInfo.guid_aDevice  )  );
				  				  
				  //  Create  the thread
				  //pRecThread->bQuit  =  FALSE;
				  pRecThread->hThread  =  CreateThread(  NULL,  128*1024,  coreAudioRecThreadFunc,  NULL,  STACK_SIZE_PARAM_IS_A_RESERVATION,  NULL  );
				  if  (  !pRecThread->hThread  )  {
					  //CHECK_START_RECORDING_HR(  E_FAIL,  (  _T(  "Failed: CreateThread() in aec_snd_StartRecording\n"  ),  hr  )  );
					  goto  errLabel;	
				  }				  

				}
				  break;
			case  CONST_recordType_waveform:  {		//   

				  #if  1	//  2013/08/02
						#ifdef  __DEBUG__
								traceLog((TCHAR*)  _T(  "CRecordSound err: don't use recThread."  )  );
						#endif
						goto  errLabel;
				  #endif

				  //pRecThread->bQuit  =  FALSE;
#include	"undeclareDebugNew.h"
				  if  (  startQThread(  NULL,  0,  new  CQyRecordSound,  pRecThread  )  )  goto  errLabel;
#include	"declareDebugNew.h"
				
				  }
				  break;
			case  CONST_recordType_directX:		//  2013/03/18

				  if  (  startAudioCapDev_dx(  pProcInfo->av.localAv.recordSoundProcInfo.u.dx.pAudioCapDev  )  )  goto  errLabel;

				  break;
			case  CONST_recordType_webRtc:
				  //
				  TCHAR  tBuf[128];
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "startLocalAudioRecorde: before startRecord_webRtc"  )  );
				  showInfo_open0(  0,  0,  tBuf  );
				  //
				  if  (  startRecord_webRtc(usCntLimit_activeMems_from  )  )  goto  errLabel;
				  //
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "startLocalAudioRecorde: after startRecord_webRtc"  )  );
				  showInfo_open0(  0,  0,  tBuf  );
				  //
				  break;

			case  CONST_recordType_custom:
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "Not finished"  )  );
				  #endif
				  goto  errLabel;
				  break;
			default:
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "unknown uiRecordType %d"  ),  uiRecordType  );
					#endif
					goto  errLabel;
	}

	//  2013/05/24
#if  0
	if  (  bTestLocalAv  )  {
		startLocalAudioPlayer(  );
	}
#endif



	
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		stopLocalAudioRecorder(  pProcInfo,  iIndex_sharedObj,  1  );
	}

	traceLogA(  (char*)  (  "startLocalAudio leaves.\n"  )  );
	
	return  iErr;

}





//
  int  stopLocalAudioRecorder(  MC_VAR_isCli  *  pProcInfo,  int  index_sharedObj,  int  nTries  )
{
	int						iErr		=		-1;
	QY_MC* pQyMc = pProcInfo->pQyMc;// QY_GET_GBUF();

	if  (  !pProcInfo  )  return  -1;
	
		//
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "stopLocalAudioRecorder enters."  )  );
#endif


	//
	CAP_procInfo_recordSound  *  pCapAudio  =  NULL;
	pCapAudio  =  &pProcInfo->av.localAv.recordSoundProcInfo;

	QY_qThreadProcInfo_common  *  pRecThread  =  &pCapAudio->recThread;


	//
	pRecThread->bQuit  =  TRUE;

	//  2013/03/19
	switch  (  pCapAudio->uiRecordType  )  {
			case  CONST_recordType_dSound:  
			case  CONST_recordType_msAec:		//  2013/05/22
			case  CONST_recordType_waveform:  
			case  CONST_recordType_coreAudio:  //  2017/01/28

				  //  if  (  !nTries  )  nTries  =  10;	
				  nTries  =  30;	//  这里必须停下来

				  int  i;
				  for  (  i  =  0;  i  <  nTries;  i  ++  )  {		 
					   if  (  !bQThreadExists(  *pRecThread  )  )  break;
				 
					   //pRecThread->bQuit  =  TRUE;		
					   //if  (  pProcInfo->av.localAv.recordSoundProcInfo.hEvents[0]  )  SetEvent(  pProcInfo->av.localAv.recordSoundProcInfo.hEvents[0]  );
		 			   if  (  pProcInfo->cfg.policy.audio.uiRecordType  ==  CONST_recordType_waveform  )  PostThreadMessage(  pRecThread->dwThreadId,  CONST_qyWm_postComm,  CONST_qyWmParam_endThread,  0  );
					   		 
					   waitForQThread(  pRecThread,  1000  );	
				  }	
				  if  (  i  ==  nTries  )  {	//  2013/08/02		
					  qyExitProcess(  _T(  "stopLocalAudioRecorder failed"  )  );	
				  }
				  //
				  stopQThread(  &pCapAudio->aecThread,  _T(  "stopLocalAudioRecorder"  )  );
				  //
				  break;
			case  CONST_recordType_directX:  
				  exitAudioCapDev_dx(  &pProcInfo->av.localAv.recordSoundProcInfo.u.dx.pAudioCapDev  );
				  pProcInfo->av.localAv.recordSoundProcInfo.bCapDevConnected  =  FALSE;
				  break;
			case  CONST_recordType_webRtc:
				  stopRecord_webRtc(  );
				  break;
			default:
					break;
	}

	//  2013/08/02
	//CAP_procInfo_audioU  *  pU  =  (  CAP_procInfo_audioU  *  )&pProcInfo->av.localAv.recordSoundProcInfo;
	
	//  2017/01/29
	stopQThread(  &pCapAudio->appThread,  _T(  "stopLocalAudioRecoder"  )  );
	//  2009/12/07	
	stopQThread(  &pCapAudio->thread,  _T(  "stopLocalAudioRecorder"  )  );				 
	
	if  (  pCapAudio->aecThread.bQInited  )  {
		exitQyQ2(  &pCapAudio->aecThread.q2  );  pCapAudio->aecThread.bQInited  =  FALSE;
	}

	//  2017/01/29
	if  (  pCapAudio->appThread.bQInited  )  {
		exitQyQ2(  &pCapAudio->appThread.q2  );  pCapAudio->appThread.bQInited  =  FALSE;
	}
	if  (  pCapAudio->thread.bQInited  )  {
		exitQyQ2(  &pCapAudio->thread.q2  );	pCapAudio->thread.bQInited  =  FALSE;				 
	}


	//
	if  (  !bQThreadExists(  *pRecThread  )  )  {
		exitCompressAudio(  pProcInfo,  &pCapAudio->compressAudio  );
	}

	//  2013/05/24
	stopLocalAudioPlayer(  pProcInfo,  10  );

	//
	traceLog((TCHAR*)  _T(  "stopLocalAudioRecorder leaves."  )  );

	return  0;
}




//
 int  resumeLocalAudioRecorder(  QY_MC  *  pQyMc,  int  iIndex_sharedObj  )
{
	int						iErr					=		-1;
	//QY_MC				*	pQyMc					=		QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProcInfo				=		QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	DWORD					dwThreadDaemonId		=		0;
	BOOL					bAudioCompressInited	=		FALSE;

	showInfo_open0(  0,  0,  _T(  "resumeLocalAudioRecorder enters"  )  );
#ifdef  __DEBUG__
	traceLogA(  (char*)  (  "resumeLocalAudio enters.\n"  )  );
#endif

	//
	QY_SHARED_OBJ		*	pSharedObj				=		getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;

	if  (  pSharedObj->uiType1  ==  CONST_sharedObjType_mediaFile  )  return  -1;
	if  (  pSharedObj->uiType1  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "resumeLocalAudioRecorder: not used, sharedObjType %d"  ),  pSharedObj->uiType1  );
		#endif
		return  -1;
	}

	if  (  !pProcInfo->av.localAv.recordSoundProcInfo.compressAudio.bCompressInited  )  return  0;

	//
	QY_qThreadProcInfo_common  *  pRecThread  =  &pProcInfo->av.localAv.recordSoundProcInfo.recThread;

	
	
	//
	unsigned  int  uiRecordType  =  pProcInfo->av.localAv.recordSoundProcInfo.uiRecordType;
	//
	switch  (  uiRecordType  )  {
				case  CONST_recordType_dSound:
					  //
					  if  (  !pRecThread->bRunning  )  {		
						  waitForQThread(  pRecThread,  0  );	
					  }
					  if  (  bQThreadExists(  *pRecThread  )  )  break;

					  //
					  pRecThread->hThread  =  CreateThread(  NULL,  0,  mcThreadProc_recordSound,  0,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
					  if  (  !pRecThread->hThread  )  goto  errLabel;
					  pRecThread->dwThreadId  =  dwThreadDaemonId;
					  if  (  ResumeThread(  pRecThread->hThread  )  ==  -1  )  goto  errLabel;
					  break;
				case  CONST_recordType_waveform:  {
					  //
					  if  (  !pRecThread->bRunning  )  {		
						  waitForQThread(  pRecThread,  0  );	
					  }
					  if  (  bQThreadExists(  *pRecThread  )  )  break;
					 
					  //
					  #if  0

							#include	"undeclareDebugNew.h"
								if  (  startQThread(  NULL,  0,  new  CQyRecordSound,  &pProcInfo->av.localAv.recordSoundProcInfo.thread  )  )  goto  errLabel;
							#include	"declareDebugNew.h"
					  #endif			
					  }
					  break;
				case  CONST_recordType_directX:
					  break;
#ifdef  __USE_msAec__
				case  CONST_recordType_msAec:  {				  
					  //
					  if  (  !pRecThread->bRunning  )  {		
						  waitForQThread(  pRecThread,  0  );	
					  }
					  if  (  bQThreadExists(  *pRecThread  )  )  break;

					  //
					  pRecThread->hThread  =  CreateThread(  NULL,  128*1024,  msAecRecThreadFunc,  NULL,  STACK_SIZE_PARAM_IS_A_RESERVATION,  NULL  );
					  if  (  !pRecThread->hThread  )  {
						  //CHECK_START_RECORDING_HR(  E_FAIL,  (  _T(  "Failed: CreateThread() in aec_snd_StartRecording\n"  ),  hr  )  );
						  goto  errLabel;					  
					  }
					  				  
					  //  2013/05/24. 在aec的情况下,需要自动启动一个player, 以便recorder能建立对render和capture的关联.						  
					  //if  (  uiRecordType  ==  CONST_recordType_msAec  )  				  
					  {		
						  startLocalAudioPlayer(  pProcInfo  );					  					  
					  }

					  }
					  break;
#endif
				case  CONST_recordType_webRtc:  //  2017/06/15
					  //  not finished					
#if 0
					  if  (  !bRecordRunning(  &pProcInfo->av.localAv.recordSoundProcInfo  )  )  {
						  stopRecord_webRtc(  );					  
						  startRecord_webRtc(  );					
					  }
#endif
					  break;

				default:
						//
						#ifdef  __DEBUG__
								traceLog((TCHAR*)  _T(  "resumeLocalAudioRecorder: unknown uiRecordType"  )  );
						#endif
						//
						break;
		
	}
	
	
	//
	iErr  =  0;

errLabel:

		//
#ifdef  __DEBUG__
	traceLogA(  (char*)  (  "resumeLocalAudio leaves.\n"  )  );
#endif
	showInfo_open0(  0,  0,  _T(  "resumeLocalAudioRecorder leaves"  )  );

	
	return  iErr;

}




