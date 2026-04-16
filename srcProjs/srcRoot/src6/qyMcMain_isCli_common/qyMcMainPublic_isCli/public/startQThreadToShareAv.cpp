
#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>


#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//  #include	"qmcVideoCapture_isCli.h"
//#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

//#include	"isCliHelpPublic.h"
//#include	"dlgShareDynBmpsProc.h"
//#include	"isClid3dpublic.h"
#include	"qmcTaskPublic.h"

//#include	"qmcCommFunc_isCli.h"
#include	"qmcCfg.h"
#include	"shareAv.h"

//#include	"qmcVideoCapture_isCli.h"


//  2015/10/11
 int  newstartQThreadToShareAv(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj,  BOOL  bAudio  )
{
	int			iErr	=	-1;
	if(  !pProcInfo  )  return  -1;
	QY_MC	*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;//QY_GET_GBUF(  );
	QMC_cfg  *  pCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pCfg  )  return  -1;

	//
	QY_SHARED_OBJ	*	pSharedObj	=	NULL;

	//  2011/07/27	
	TCHAR				tName[128];
	GENERIC_Q_CFG		tmpCfg;
	GENERIC_Q_cfgEx		qCfgEx;
	DWORD				dwThreadDaemonId;

	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;	

	if  (  bAudio  )  {
		CAP_procInfo_audioCommon  *  pCapAudio  =  NULL;

		pCapAudio  =  (  CAP_procInfo_audioCommon  *  )getCapAudioBySth(  pProcInfo,  pSharedObj->iIndex_capAudio,  0  );
		if  (  !pCapAudio  )  goto  errLabel;

		//  2015/10/11
		if  (  pCapAudio->thread.bQInited  )  {
			#ifdef  __DEBUG__
				    //  2015/10/11
					MACRO_qyAssert(  0,  _T(  "startQThreadToShareAv failed, capA.bQInited is already true"  )  );
			#endif
			showInfo_open0(  0,  0,  _T(  "startQThreadToShareAv failed, capA.bQInited is already true"  )  );
			goto  errLabel;
		}

		//
		memcpy(  &tmpCfg,  &pCfg->toShareAudioQ,  sizeof(  tmpCfg  )  );
		_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%d"  ),  tmpCfg.name,  pSharedObj->uiTranNo  );
		_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%d"  ),  tmpCfg.mutexName_prefix,  pSharedObj->uiTranNo  );
		_sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%u"  ),  CONST_evtName_qm_data_a,  pSharedObj->uiTranNo  );
		if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapAudio->thread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myPLAY_AUDIO_DATA,  &pCapAudio->thread.q2  )  )  goto  errLabel;
		pCapAudio->thread.bQInited  =  TRUE;

		//
		if  (  !pCapAudio->thread.hThread  )  {
			//
			pCapAudio->thread.bQuit  =  FALSE;			
			pCapAudio->thread.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_toShareAudio,  (  LPVOID  )iIndex_sharedObj,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			if  (  !pCapAudio->thread.hThread  )  goto  errLabel;					
			pCapAudio->thread.dwThreadId  =  dwThreadDaemonId;			
			if  (  ResumeThread(  pCapAudio->thread.hThread  )  ==  -1  )  goto  errLabel;									 
		}
	}

	//
	{
		  CAP_procInfo_bmpCommon  *  pCapBmp	=	NULL;

		  pCapBmp  =  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
		  if  (  !pCapBmp  )  goto  errLabel;


		  //////////////////////////////////

		  //  2011/12/06
		  memcpy(  &tmpCfg,  &pCfg->toShareVideo_postQ,  sizeof(  tmpCfg  )  );
		  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%d"  ),  tmpCfg.name,  pSharedObj->uiTranNo  );
		  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%d"  ),  tmpCfg.mutexName_prefix,  pSharedObj->uiTranNo  );
		  _sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%u"  ),  CONST_evtName_qm_toShareVideo_post,  pSharedObj->uiTranNo  );
		  if  (  pCapBmp->postThread.bQInited  )  {
			  #ifdef  __DEBUG__  
					  //  2015/10/11
					  MACRO_qyAssert(  0,  _T(  "startQThreadToShareAv failed, capV.bQInited is  already true."  )  );
			  #endif
			  showInfo_open0(  0,  0,  _T(  "startQThreadToShareAv failed, capV.bQInited is  already true."  )  );
			  goto  errLabel;
		  }
		  //  if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapBmp->postThread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &pCapBmp->postThread.q2  )  )  goto  errLabel;
		  memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );
		  memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );
		  qCfgEx.pfQElemNewEx  =  mallocMemory;
		  qCfgEx.pfQElemNew  =  mymalloc;
		  qCfgEx.pfQElemFreeEx  =  freeMemory;
		  qCfgEx.pfQElemFree  =  myfree;
		  qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myDRAW_VIDEO_DATA;
		  if  (  initQyQ2(  &qCfgEx,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapBmp->postThread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  &pCapBmp->postThread.q2  )  )  goto  errLabel;
		  pCapBmp->postThread.bQInited  =  TRUE;

		  //  2010/12/29
		  pCapBmp->compressVideo.debugInfo.nStep  =  35;

		  
		  //
		  memcpy(  &tmpCfg,  &pCfg->toShareVideoQ,  sizeof(  tmpCfg  )  );
		  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%d"  ),  tmpCfg.name,  pSharedObj->uiTranNo  );
		  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%d"  ),  tmpCfg.mutexName_prefix,  pSharedObj->uiTranNo  );
		  _sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%u"  ),  CONST_evtName_qm_data_v,  pSharedObj->uiTranNo  );
		  if  (  pCapBmp->thread.bQInited  )  {
			  traceLog((TCHAR*)  _T(  "startQThreadToShareAv failed, bQInited is  already true."  )  );
			  goto  errLabel;
		  }
		  //  if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapBmp->thread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &pCapBmp->thread.q2  )  )  goto  errLabel;
		  memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );
		  memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );
		  qCfgEx.pfQElemNewEx  =  mallocMemory;
		  qCfgEx.pfQElemNew  =  mymalloc;
		  qCfgEx.pfQElemFreeEx  =  freeMemory;
		  qCfgEx.pfQElemFree  =  myfree;
		  qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myDRAW_VIDEO_DATA;
		  if  (  initQyQ2(  &qCfgEx,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapBmp->thread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  &pCapBmp->thread.q2  )  )  goto  errLabel;
		  pCapBmp->thread.bQInited  =  TRUE;

		  //  2010/12/29
		  pCapBmp->compressVideo.debugInfo.nStep  =  37;


		  //  2011/12/04
		  memcpy(  &tmpCfg,  &pCfg->vppQ,  sizeof(  tmpCfg  )  );
		  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%d"  ),  tmpCfg.name,  pSharedObj->uiTranNo  );
		  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%d"  ),  tmpCfg.mutexName_prefix,  pSharedObj->uiTranNo  );
		  _sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%u"  ),  CONST_evtName_qm_vpp,  pSharedObj->uiTranNo  );
		  if  (  pCapBmp->vppThread.bQInited  )  {
			  traceLog((TCHAR*)  _T(  "startQThreadToShareAv failed, vppThread.bQInited is  already true."  )  );
			  goto  errLabel;
		  }
		  //  if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapBmp->vppThread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &pCapBmp->vppThread.q2  )  )  goto  errLabel;
		  memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );
		  memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );
		  qCfgEx.pfQElemNewEx  =  mallocMemory;
		  qCfgEx.pfQElemNew  =  mymalloc;
		  qCfgEx.pfQElemFreeEx  =  freeMemory;
		  qCfgEx.pfQElemFree  =  myfree;
		  qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myDRAW_VIDEO_DATA;
		  if  (  initQyQ2(  &qCfgEx,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapBmp->vppThread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  &pCapBmp->vppThread.q2  )  )  goto  errLabel;
		  pCapBmp->vppThread.bQInited  =  TRUE;
		  //


		  

		  //
		  if  (  !pCapBmp->postThread.hThread  )  {
			  //
			  pCapBmp->postThread.bQuit  =  FALSE;			
			  pCapBmp->postThread.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_toShareVideo_post,  (  LPVOID  )iIndex_sharedObj,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			  if  (  !pCapBmp->postThread.hThread  )  goto  errLabel;					
			  pCapBmp->postThread.dwThreadId  =  dwThreadDaemonId;			
			  if  (  ResumeThread(  pCapBmp->postThread.hThread  )  ==  -1  )  goto  errLabel;									 
		  }

		  //
		  if  (  !pCapBmp->thread.hThread  )  {
			  //
			  pCapBmp->thread.bQuit  =  FALSE;			
			  pCapBmp->thread.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_encVideo,  (  LPVOID  )iIndex_sharedObj,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			  if  (  !pCapBmp->thread.hThread  )  goto  errLabel;					
			  pCapBmp->thread.dwThreadId  =  dwThreadDaemonId;			
			  if  (  ResumeThread(  pCapBmp->thread.hThread  )  ==  -1  )  goto  errLabel;									 
		  }

		  //  2010/12/29
		  pCapBmp->compressVideo.debugInfo.nStep  =  38;

		  //
		  if  (  !pCapBmp->vppThread.hThread  )  {
			  //
			  pCapBmp->vppThread.bQuit  =  FALSE;			
			  pCapBmp->vppThread.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_vpp,  (  LPVOID  )iIndex_sharedObj,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			  if  (  !pCapBmp->vppThread.hThread  )  goto  errLabel;					
			  pCapBmp->vppThread.dwThreadId  =  dwThreadDaemonId;			
			  if  (  ResumeThread(  pCapBmp->vppThread.hThread  )  ==  -1  )  goto  errLabel;									 
		  }




	}

	iErr  =  0;

errLabel:

	return  iErr;
}


