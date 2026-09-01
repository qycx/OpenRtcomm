
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
//


int  loadCusModules(void* pQyMcParam)
{
	//
	return  -1;
}




//
CQyDecTool::CQyDecTool()
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	//

}


//
CQyDecTool::~CQyDecTool()
{
}


//
int  wt_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
{	
	int  iErr = false;
	unsigned  int    dwByte = msgLen;
	//
	CQyDecTool* pTool = (CQyDecTool*)p0;
	//  p1

	//	
	if (dwByte < sizeof(OnvifMsg_common)) {
		showInfo_open0(0, 0, _T("shareDynBmps_qisPipe_onRead err: read too small bytes < sizeof(  Onvif_msg_common  )"));
		return  -1;
	}
	//
	OnvifMsg_common* pMsgCommon = (OnvifMsg_common*)pMsg;


	if (pMsgCommon->uiType != CONST_qisMsgType_onvif)  return  -1;

	//
	TCHAR  tBuf[128];

	//
	switch (pMsgCommon->iSubtype) {
	case  CONST_onvifMsg_subtype_dbg: {
		OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;
		//
		traceLog((TCHAR*)_T("recvd: %S"), pDbg->buf);
		//
	}
									break;
	case  CONST_wgcMsg_subtype_shmOk: {
		WgcMsg_shmOk* pShmOk = (WgcMsg_shmOk*)pMsgCommon;
		//
		traceLog((TCHAR*)_T("shmOk"));
		//
		pTool->m_var.pCtx->m_var.wtStatus.cli_bShmOk = true;
		//
	}
									break;
									
	case  CONST_wgcMsg_subtype_pkt: {
		WgcMsg_pkt* pPkt = (WgcMsg_pkt*)pMsgCommon;
		if (pPkt->ucbResp) {

			//
#ifdef  _DEBUG
			if (0) {
				showInfo_open(0, 0, 0, _T("get resp"));
			}
#endif 

			//
			pTool->m_var.pCtx->m_var.wtStatus.dwLastTickCnt_recvResp = myGetTickCount(mynull);

		}
	}
								  break;
	default:
		//
		traceLog((TCHAR*)_T("unprocessed wgcMsg_subtype"));
		//
		break;
	}


	//
#ifdef  __DEBUG__

#endif



	//
	iErr = true;
errLabel:

	//
	return  iErr;

}



 //  2016/04/26
 //
int  CQyDecTool::init(    LPCTSTR  cmdLine  )
{
	int  iErr  =  -1;

	//
	g_pQyMc = new  CCtxQyMc;
	if (!g_pQyMc)  goto  errLabel;
	//
	m_var.pQyMcParam = g_pQyMc;//

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
	 initShowInfo_cli(0, _T("syncQ_showInfo_qmc"), (char*)"127.0.0.1", &g_pQyMc->pShowInfoStruct);

	 //
#if  0
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
#endif 

	 //
	 showInfo_open(0, 0, 0, _T("anWgcTool starts."));


	 //
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
	m_var.pCtx  =  new  CCtxQmcWt;
	if  (  !m_var.pCtx  )  goto  errLabel;

	//
	m_var.pCtx->pQyMc  =  (  QY_MC  *  )m_var.pQyMcParam;

	//  parse cmdLine
	parseCmdLine_qmc_func(cmdLine, &pQyMc->appParams);

	//
	init_tickCnt();

	//
#ifdef  __DEBUG__

#if  0
	//
	safeTcsnCpy(  _T(  "qm=0"  ),  pQyMc->appParams.appObjPrefix,  mycountof(  pQyMc->appParams.appObjPrefix  )  );
	traceLog(  _T(  "TEST: appObjPrefix is set to qm12"  )  );
	//
	if (0) {
		pQyMc->appParams.tn_cliPipe = 10;
		traceLog(_T("TEST: tn_rtspCliPipe is set to 10"));
	}
#endif
	//
	
#endif

	//
#if  0
	//  2016/04/26
	if  (  initDynLib_isD3dFunc(  &m_var.pCtx->m_var.pDynLib_isD3dFunc  )  )  {
		showInfo_open0(  0,  0,  _T(  "initDynLib_isD3dFunc failed"  )  );
		goto  errLabel;
	}
#endif 


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
	 _sntprintf(  pProcInfo->who_showInfo,  mycountof(  pProcInfo->who_showInfo  ),  _T(  "wgcTool"  )  );
	 set_who_showInfo(  pProcInfo->who_showInfo  );

	 //

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
	 M_get_evtName_syncQuit(  CONST_evtNamePrefix_rtspCliSyncQuit,  pProcInfo->get_appObjPrefix(  ),  pQyMc->appParams.tn_cliPipe,  m_var.pCtx->m_var.cmdProc.evtName_syncQuit  );
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

	do {
		//
		if (10)
		{
			//
			m_var.pCtx->m_var.pQisPipe = qisPipeNew();
			if (!m_var.pCtx->m_var.pQisPipe)  break;

			//
			GENERIC_Q_CFG  qCfg = { 0 };
			TCHAR   pipeName[128] = _T("");
			int  tn_rtspCliPipe = 0;// pParams->tn_cliPipe;
			//
			_sntprintf(qCfg.name, mycountof(qCfg.name), _T("wgcPipe"));
			_sntprintf(qCfg.mutexName_prefix, mycountof(qCfg.mutexName_prefix), _T("wgcPipe"));
			qCfg.uiMaxQNodes = 100;	//  CONST_uiMaxQNodes_outputQ_256;


			//		  
			M_get_pipeName(CONST_wgcPipePrefix, _T(""), CONST_wgcPipe_tn, pipeName);


			//
			PARAM_initQisPipe  param = { 0 };
			param.pf_onRead = wt_qisPipe_onRead;
			param.uiMaxToInMs_read = CONST_toInMs_pipe_read;
			param.p0 = this;

			//
			if (initQisPipe(&qCfg, pipeName, false, _T("wt.pipe"), &param, m_var.pCtx->m_var.pQisPipe)) {
				break;
			}

			//
			showInfo_open(0, 0, 0, _T("wt: initQisPipe ok"));
						
		}


		//
		m_var.pCtx->m_wgc.m_var.pProcInfoTmpl = m_var.pCtx;

		//
#ifdef  __DEBUG__
		//
		if (1) {
			m_var.pCtx->m_wgc.m_var.bDbg_traceRt_wgc = true;
			traceLog((TCHAR*)_T("bDbg_traceRt_wgc set to true"));
		}
		//
#endif 


		//
		if (wgc_initDev(&m_var.pCtx->m_wgc)) {
			showInfo_open(0, 0, 0, _T("wgc_initDev failed"));
			goto  errLabel;
		}



		//
		iErr = 0;
	
	} while (false);

errLabel:

	return  iErr;
}
    

//
int CQyDecTool::run()
{
	int  iErr  =  -1;

	CCtxQmcWt  *  pCtx  =  m_var.pCtx;
	DWORD  dwRet;
	int  nTimes_errDec  =  0;

	//
	for  (  ;  !pCtx->qyMc_bQuit(  );  )  {
		 
		  dwRet  =  WaitForSingleObject(  pCtx->m_var.cmdProc.hEvent_syncQuit,  1000  );
		  if  (  dwRet  !=  WAIT_FAILED  &&  dwRet  !=  WAIT_TIMEOUT  )  {
			  tmp_showInfo(  _T(  "rtspCli::cmdProc getCmd Quit"  )  );
			  break;
		  }

		  //
		  int  minBadIntervalInMs  =  2000;
		  //
#ifdef  __DEBUG__
		  //  for test
		  //minBadIntervalInMs  =  10;
#endif
		  //
		  if (10) {
			  //
			  TCHAR  tBuf[123];
			  DWORD  dwTickCnt = myGetTickCount(mynull);
			  int  iDiffInMs = dwTickCnt - m_var.pCtx->m_var.wtStatus.dwLastTickCnt_recvResp;
			  if (abs(iDiffInMs) < minBadIntervalInMs)  nTimes_errDec = 0;
			  else {
				  nTimes_errDec++;
				  //			
				  _sntprintf(tBuf, mycountof(tBuf), _T("elapseInMs from last_recvResp %dms. nTimes_errDec %d"), iDiffInMs, nTimes_errDec);
				  showInfo_open0(0, 0, tBuf);
				  //
				  if (nTimes_errDec > 5) {
					  goto  errLabel;
				  }
			  }
			  //
		  }

	}

	iErr  =  0;
	
errLabel:

	return  iErr;
}


//
void CQyDecTool::exit()
{
	//
	showInfo_open(0, 0, 0, _T("wgcTool.exit enters"));

	//
	int  iIndex_sharedObj  =  0;
	//
	QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  m_var.pCtx,  iIndex_sharedObj  );
	if  (  pSharedObj  )  {	
		askSharedObjToStop(  m_var.pCtx,  pSharedObj,  NULL,  _T(  ""  )  );
	}

	//
	showInfo_open(0, 0, 0, _T("before wgc_exitDev"));
	//
	wgc_exitDev(&m_var.pCtx->m_wgc);
	//
	showInfo_open(0, 0, 0, _T("wgc_exitDev ok"));

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

		//
		qisPipeFree(&m_var.pCtx->m_var.pQisPipe);

		//
#if  0
		//  2016/04/26
		exitDynLib_isD3dFunc(  &m_var.pCtx->m_var.pDynLib_isD3dFunc  );
#endif 
		
		//
		if  (  m_var.pCtx->m_var.cmdProc.hEvent_syncQuit  )  {
			CloseHandle(  m_var.pCtx->m_var.cmdProc.hEvent_syncQuit  );  m_var.pCtx->m_var.cmdProc.hEvent_syncQuit  =  NULL;
		}
		//
		delete  m_var.pCtx;  m_var.pCtx  =  NULL;
	}




	//
	//
	QY_MC* pQM = (QY_MC*)m_var.pQyMcParam;
	if (pQM) {
		exitShowInfo(&pQM->pShowInfoStruct);
	}


	//  2010/07/05
	 qyTcpEnd(  );

	 //
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

	 //
	 showInfo_open(0, 0, 0, _T("wgcTool.exit leaves"));

	 //
	 return;

}








