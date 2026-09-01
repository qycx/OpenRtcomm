
#include	"stdafx.h"


#include	"qyDecToolCommon.h"

#include	"qmcVideoCapture.h"
#include	"policyAvParams.h"
#include	"taskAv.h"
#include	"tmpGuiOpenFunc.h"
#include	"qyMcMainCommon.h"
#include	"qySyncCommProc.h"
#include	"qyDynLib.h"
#include	"qmcVideoCapture_rtsp.h"

//  2016/04/26
#include	"load_isD3dFunc.h"

//
CQyDecTool::CQyDecTool()
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

}


CQyDecTool::~CQyDecTool()
{
}


 //  2016/04/26
 //
int  CQyDecTool::init(    LPCTSTR  cmdLine  )
{
	int  iErr  =  -1;

	//
	m_var.pQyMcParam  =  new  CCtxQyMc;
	if  (  !m_var.pQyMcParam  )  goto  errLabel;

	//  2016/04/26
	
	//
	QY_MC  *  pQyMc  =  (  QY_MC  *  )m_var.pQyMcParam;
	QY_MC  *  pQM  =  pQyMc;

	//
	pQyMc->iSystemId  =  qyGetSystemId(  );
	 //  g_pQyMc->iAppType   =   CONST_qyAppType_mc;
	 pQyMc->iAppType  =  qyGetAppType(  pQyMc->iSystemId,  _T(  CONST_qyRootKey_mcGui_netMc  )  );		//  2004/05/23ÐÞ¸Ä
	 pQyMc->iCustomId  =  qyGetCustomId(  );
	 pQyMc->iServiceId  =  qyGetServiceId(  pQyMc->iSystemId  );										//  2007/03/07

	 //
	 QY_MC_CFG  *  pCfg  =  &pQyMc->cfg;

	 if  (  !(  pCfg->pSysCfg  =  getQnmSysCfgInfo(  pQyMc->iSystemId,  pQyMc->iAppType  )  )  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  "ÇëÉèÖÃsysCfgInfo"  );  
		 #endif
		 goto  errLabel;
	 }
	 if  (  !(  pCfg->pGuiCfg  =  getQnmGuiCfgInfo(  pQyMc->iSystemId,  pQyMc->iAppType  )  )  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  "ÇëÉèÖÃguiCfgInfo"  );  
		 #endif
		 goto  errLabel;
	 }

	 //
	 safeTcsnCpy(  pCfg->pSysCfg->rootKey_mcGui,  pCfg->rootKey,  mycountof(  pCfg->rootKey  )  );
	 if  (  !qyGetRegCfg(  pCfg->rootKey,  _T(  QY_INSTALLDIR_VALNAME  ),  (  char  *  )pCfg->installDir,  sizeof(  pCfg->installDir  )  )  )  {
		 if  (  tTrailDir(  pCfg->installDir,  mycountof(  pCfg->installDir  )  )  )  goto  errLabel;
		 }
	 else  {
		   traceLogA(  "getQyMcInitialCfg failed: can't get installDir"  );  
		   #ifndef  __WINCE__
				    goto  errLabel;
		   #endif
	 }
	 //
	 if  (  pCfg->installDir[0]  )  {
		 _sntprintf(  pCfg->cusModuleDir,  mycountof(  pCfg->cusModuleDir  ),  _T(  "%s%s"  ),  pCfg->installDir,  CQyString(  CONST_qyCusModuleSubDir  )  );
	 }




	 QY_DYN_LIBS	*	pDynLib					=	NULL;
	 TCHAR				systemDir[MAX_PATH]		=	_T(  ""  );

	 myGetSystemDirectory(  systemDir,  mycountof(  systemDir  )  );
	 tTrailDir(  systemDir,  mycountof(  systemDir  )  );

	 //  if  (  qyInitSnmp(  &ghDll_InetMib1  )  )  goto  errLabel;
	 if  (  initDynLib(  (  void  **  )&pDynLib  )  )  goto  errLabel;	//  2007/01/21
	 if  (  initDynLib_dx(  systemDir,  &pDynLib->pLib_dx  )  )  goto  errLabel;

	 //  2010/07/05
	 if  (  qyTcpStart(  )  )  goto  errLabel;	//  

	 //  È¡»·¾³²ÎÊý,  2005/11/03
	 getQyEnv(  pDynLib,  &pQM->env  );
	 //  pQM->env.pDynLibs  =  pDynLib;
	 pQM->ucbDynLibInited  =  TRUE;

	 //  2009/07/12
	 g_pEnv  =  &pQM->env;




	//
	m_var.pCtx  =  new  CCtxQmcDvt;
	if  (  !m_var.pCtx  )  goto  errLabel;

	//
	m_var.pCtx->pQyMc  =  (  QY_MC  *  )m_var.pQyMcParam;

	//  parse cmdLine
#ifdef  __DEBUG__
#if  0
	//
	safeTcsnCpy(  _T(  "qm1"  ),  m_var.pCtx->m_var.cmdLine.appObjPrefix,  mycountof(  m_var.pCtx->m_var.cmdLine.appObjPrefix  )  );
	traceLog(  _T(  "TEST: appObjPrefix is set to qm12"  )  );
	//
	m_var.pCtx->m_var.cmdLine.tn_cliPipe  =  10;
	traceLog(  _T(  "TEST: tn_rtspCliPipe is set to 10"  )  );
#endif
#endif
	parseCmdLine_qmc(  cmdLine,  &m_var.pCtx->m_var.cmdLine  );

	//  2016/04/26
	if  (  initDynLib_isD3dFunc(  &m_var.pCtx->m_var.pDynLib_isD3dFunc  )  )  {
		showInfo_open0(  0,  0,  _T(  "initDynLib_isD3dFunc failed"  )  );
		goto  errLabel;
	}


	//
	m_var.pCtx->m_var.p_gAvParams  =  get_g_pAvParams(  );//&gAvParams;
	if  (  !m_var.pCtx->m_var.p_gAvParams  )  goto  errLabel;
	memset(  m_var.pCtx->m_var.p_gAvParams,  0,  sizeof(  PolicyAvParams  )  );

	//
	//
	 m_var.pCtx->m_var.qyMc_cfg.rwLockParam.uiMaxCnt_sema			=	CONST_uiInitCnt_sema_q2SyncFlg;
	 m_var.pCtx->m_var.qyMc_cfg.rwLockParam.uiInitCnt_sema			=	m_var.pCtx->m_var.qyMc_cfg.rwLockParam.uiMaxCnt_sema  -  1;
	 m_var.pCtx->m_var.qyMc_cfg.rwLockParam.uiMilliSeconds_mutex_r	=	10000;
	 m_var.pCtx->m_var.qyMc_cfg.rwLockParam.uiMilliSeconds_sema_r	=	10000;
	 m_var.pCtx->m_var.qyMc_cfg.rwLockParam.uiMilliSeconds_mutex_w	=	10000;
	 m_var.pCtx->m_var.qyMc_cfg.rwLockParam.uiMilliSeconds_sema_w	=	10000;

	 MC_VAR_common  *  pProcInfo  =  m_var.pCtx;

	 //
	 //  2016/04/02
	 _sntprintf(  pProcInfo->who_showInfo,  mycountof(  pProcInfo->who_showInfo  ),  _T(  "dvt"  )  );
	 set_who_showInfo(  pProcInfo->who_showInfo  );

	 //
	 TCHAR  tName[128];  //  2015/05/23
	 //_sntprintf(  tName,  mycountof(  tName  ),  _T(  "transQ-%d"  ),  GetCurrentProcessId(  )  );
	  getTransformQName(  tName,  mycountof(  tName  )  );
	 _sntprintf(  m_var.pCtx->m_var.cfg.transformQ.name,  mycountof(  m_var.pCtx->m_var.cfg.transformQ.name  ),  _T(  "%s"  ),  tName  );
	 _sntprintf(  m_var.pCtx->m_var.cfg.transformQ.mutexName_prefix,  mycountof(  m_var.pCtx->m_var.cfg.transformQ.mutexName_prefix  ),  _T(  "%s"  ),  tName  );
	 m_var.pCtx->m_var.cfg.transformQ.uiMaxQNodes  =  CONST_uiMaxQNodes_transformQ;

	 //
	 QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	 if  (  !pQmcCfg  )  goto  errLabel;
	 getPolicyIsClient(  pProcInfo,  &pQmcCfg->policy  );

	 //
	 M_get_evtName_syncQuit(  CONST_evtNamePrefix_rtspCliSyncQuit,  pProcInfo->get_appObjPrefix(  ),  m_var.pCtx->m_var.cmdLine.tn_cliPipe,  m_var.pCtx->m_var.cmdProc.evtName_syncQuit  );
	 m_var.pCtx->m_var.cmdProc.hEvent_syncQuit  =  CreateEvent(  NULL,  FALSE,  FALSE,  m_var.pCtx->m_var.cmdProc.evtName_syncQuit  );
	if  (  !m_var.pCtx->m_var.cmdProc.hEvent_syncQuit  )  goto  errLabel;
	
	//
	 pQM->pRw_syncCusModules  =  new  CMutexRW(  );
	 if  (  !pQM->pRw_syncCusModules  )  goto  errLabel;

	//
	if  (  !loadCusModules(  pQyMc  )  )  {
			pQyMc->bCusModulesLoaded  =  TRUE;
			//
			//  2007/12/31
			if  (  initCusModules(  pQyMc  )  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCusModules failed."  )  );
				goto  errLabel;
			}
			if  (  startCusModules(  pQyMc  )  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "startCusModules failed."  )  );
				goto  errLabel;
			}
			//
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "loadCusModules ok."  )  );		
	}




	//
	MC_VAR_common  *  pProcInfoCommon  =  m_var.pCtx;
	unsigned  int  uiCamCapType  =  CONST_camCapType_rtsp;
	TCHAR  url[256]  =  _T(  ""  );	//  _T(  "rtsp://127.0.0.1:8554/video.264"  );
	VIDEO_COMPRESSOR_CFG	videoCompressor;
	memset(  &videoCompressor,  0,  sizeof(  videoCompressor  )  );
	VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam  =  &videoCompressor;
	TCHAR  tHint[128]  =  _T(  ""  );
	int  iIndex_sharedObj  =  0;

	//
	pQmcCfg->usMaxCnt_pSharedObjs  =  1;

	//
	QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  m_var.pCtx,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;

	//
	if  (  uiCamCapType  ==  CONST_camCapType_rtsp  )  {		//  2014/02/23					  
					  
						  //  2014/03/15
						  int  size  =  sizeof(  TRANSINFO_stream  );		
						  if  (  !pSharedObj->pTransInfo_stream  )  {
							  pSharedObj->pTransInfo_stream  =  mymalloc(  size  );
							  if  (  !pSharedObj->pTransInfo_stream  )  goto  errLabel;
							  memset(  pSharedObj->pTransInfo_stream,  0,  size  );					  		
							  //
							  TRANSINFO_stream  *  pTransInfo  =  (  TRANSINFO_stream  *  )pSharedObj->pTransInfo_stream;
							  //
							  pTransInfo->myTask.ucbLocalSource_rtspStream  =  TRUE;
							  
							  //
							  pTransInfo->myTask.usCntLimit_transforms  =  1;
							  if  (  initTransforms(  pProcInfo,  &pTransInfo->addr_logicalPeer,  0,  0,  &pTransInfo->tranInfo,  &pTransInfo->myTask,  NULL  )  )  goto  errLabel;
							  //
							  pTransInfo->myTask.usCntLimit_mems_from  =  1;
							  size  =  sizeof(  TASK_AV_FROM  )  *  pTransInfo->myTask.usCntLimit_mems_from;
							  pTransInfo->myTask.pMems_from  =  (  TASK_AV_FROM  *  )mymalloc(  size  );
							  if  (  !pTransInfo->myTask.pMems_from  )  goto  errLabel;
							  memset(  pTransInfo->myTask.pMems_from,  0,  size  );
						  }

	}
	

	//  2015/01/28
	unsigned  int  uiRtspType  =  CONST_rtspType_decV;							//  2015/01/28. 用来decTool时，通过pipe从qm里读取，不需要rtspCliHelp;

	//
	_sntprintf(  url,  mycountof(  url  ),  _T(  "rtsp://127.0.0.1/v.264"  )  );
	
	//	
#if  10
	//  2015/10/11
	BOOL  bCapDev  =  TRUE;	//  FALSE;  //  2015/10/11. 最好用false,需要给sharedObj定义一个新的type. 暂时用true来延续老的做法
	//
	if  (  openLocalVideo_rtsp_step0(  pProcInfoCommon,  uiRtspType,  url,  m_var.pCtx->m_var.cmdLine.tn_cliPipe,  pVideoCompressorParam,  tHint,  bCapDev,  iIndex_sharedObj  )  )  goto  errLabel;
	if  (  openLocalVideo_rtsp_step1(  pProcInfoCommon,  url,  TRUE,  tHint,  iIndex_sharedObj  )  )  goto  errLabel;
#endif


	iErr  =  0;
errLabel:

	return  iErr;
}
    

//
int CQyDecTool::run()
{
	int  iErr  =  -1;

	CCtxQmcDvt  *  pCtx  =  m_var.pCtx;
	DWORD  dwRet;
	int  nTimes_errDec  =  0;

	//
	for  (  ;  !pCtx->bCtxQuit(  );  )  {
		 
		  dwRet  =  WaitForSingleObject(  pCtx->m_var.cmdProc.hEvent_syncQuit,  3000  );
		  if  (  dwRet  !=  WAIT_FAILED  &&  dwRet  !=  WAIT_TIMEOUT  )  {
			  tmp_showInfo(  _T(  "rtspCli::cmdProc getCmd Quit"  )  );
			  break;
		  }

		  //
		  int  minBadIntervalInMs  =  1000;
		  //
#ifdef  __DEBUG__
		  //  for test
		  //minBadIntervalInMs  =  10;
#endif
		  //
		  TCHAR  tBuf[123];
		  DWORD  dwTickCnt  =  GetTickCount(  );
		  int  iDiffInMs  =  dwTickCnt  -  m_var.pCtx->m_var.dvtStatus.dwLastTickCnt_writeShm;
		  if  (  abs(  iDiffInMs  )  <  minBadIntervalInMs  )  nTimes_errDec  =  0;
		  else  {
			    nTimes_errDec  ++  ;
				//			
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "elapseInMs from last_writeShm %dms. nTimes_errDec %d"  ),  iDiffInMs,  nTimes_errDec  );
				showInfo_open0(  0,  0,  tBuf  );
				//
				if  (  nTimes_errDec  >  5  )  {			  
					goto  errLabel;		  
				}
		  }

	}

	iErr  =  0;
	
errLabel:

	return  iErr;
}

void CQyDecTool::exit()
{
	int  iIndex_sharedObj  =  0;
	//
	QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  m_var.pCtx,  iIndex_sharedObj  );
	if  (  pSharedObj  )  {	
		askSharedObjToStop(  m_var.pCtx,  pSharedObj,  NULL,  _T(  ""  )  );
	}
	//
	if  (  freeSharedObjByIndex(  m_var.pCtx,  iIndex_sharedObj  )  )  {
		showInfo_open0(  0,  0,  _T(  "dvt::exit failed, freeSharedObj failed"  )  );
		return;
	}
	//
	if  (  m_var.pQyMcParam  )  {
		QY_MC  *  pQM  =  (  QY_MC  *  )m_var.pQyMcParam;		
		//  2007/12/30
		if  (  pQM->bCusModulesLoaded  )  {
			unloadCusModules(  pQM  );  pQM->bCusModulesLoaded  =  FALSE;	 
		}
		//
		MACRO_safeDelete(  pQM->pRw_syncCusModules  );
	}


	//
	if  (  m_var.pCtx  )  {

		//  2016/04/26
		exitDynLib_isD3dFunc(  &m_var.pCtx->m_var.pDynLib_isD3dFunc  );
		
		//
		if  (  m_var.pCtx->m_var.cmdProc.hEvent_syncQuit  )  {
			CloseHandle(  m_var.pCtx->m_var.cmdProc.hEvent_syncQuit  );  m_var.pCtx->m_var.cmdProc.hEvent_syncQuit  =  NULL;
		}
		//
		delete  m_var.pCtx;  m_var.pCtx  =  NULL;
	}



	//  2010/07/05
	 qyTcpEnd(  );

	 if  (  m_var.pQyMcParam  )  {
		 QY_MC  *  pQM  =  (  QY_MC  *  )m_var.pQyMcParam;

		 //  if  (  ghDll_InetMib1  )  qyExitSnmp(  &ghDll_InetMib1  );
		 if  (  pQM->ucbDynLibInited  )  {	//  2007/01/21
			 exitDynLib_dx(  &(  (  QY_DYN_LIBS  *  )pQM->env.pDynLibs  )->pLib_dx  );
			 exitDynLib(  &pQM->env.pDynLibs  );	pQM->ucbDynLibInited  =  FALSE;
		 }

		//
		//MACRO_safeFree(  m_var.pQyMcParam  );		 
		 MACRO_safeDelete(  pQM  );
		 m_var.pQyMcParam  =  NULL;
	 }


}








