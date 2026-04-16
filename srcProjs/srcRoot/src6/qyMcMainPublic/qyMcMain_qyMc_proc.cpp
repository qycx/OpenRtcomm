




#include	"stdafx.h"
//#include	<stdio.h>

#include	"shlobj.h"
#include	<time.h>
#include	<tchar.h>

#ifndef  __WINCE__
		 #include	"myresource.h"
#endif
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"


#ifndef  __NOTSUPPORT_MULTIDOC__
	//#include	"qyRestrictEdit.h"
	//#include	"qyFile.h"
#endif
#ifdef  __isCli__
		#ifndef  __NOTSUPPORT_qyFile__
				 //#include	"qyFile.h"
		#endif
#endif
#include	"qyCusResTemp.h"
#include	"tmpCeLib.h"
//

#ifndef  __NOTSUPPORT_MULTIDOC__
#ifndef  __useQt__
	#include	"dlgMcHint.h"
	#include	"dlgQnmCfgOptions.h"
	#include	"DlgQnmCfgAdvancedOptions.h"
#endif
#endif 
#include	"qyDynLib.h"


//#include	"qmcVWall.h"
#ifdef  __isCli__
#include	"qmcCmdProc.h"
#endif

#include	"qySqlFunc.h"

#include	"mmDeviceProc.h"			//  2013/05/22

#ifdef  __isCli__
		#include	"isCliHelpPublic.h"			//  2013/06/07
		#include	"qyMessengerHelpPublic.h"	//  2013/07/26
		#include	"isCliD3dPublic.h"	//  2013/07/03
		#include	"qisWallsProc.h"	//  2013/07/11
		#include	"imgProcessPublic.h"
		#include	"funcsForIsCliHelp.h"
		#include	"isCliExPublic.h"
#endif



//  201506/28
#include	"qisGuiPublic_public.h"

//  2016/09/05
#include	"myDb.h"
#include <gpuFunc.h>
//#include	"qmDbFuncs.h"


//
int  setAllHints(  void  *  pResInfoParam,  unsigned  short  usLangId  );
int  getCustomComm(  QNM_CUSTOM_COMM  *  );
extern  QY_DMITEM  CONST_cusMenusTable[];


//
 int  getQyMcInitialCfg(  QY_MC  *  pQyMc,  QY_MC_CFG  *  pCfg  );
 int  qmChkAppType(  QY_MC  *  pQM  );
 
 //
#ifdef  __DEBUG__
 int  kkkk(  )
 {
	 return  0;
 }
#endif


 //
 #define		CONST_maxQNodes_guiProcessQ							400  *  2



///
 //__declspec(  dllexport  )  int  initQyMc(  HINSTANCE  g_hInst,  BOOL  bCalledByQmd  )
 __declspec(  dllexport  )  int	initQyMc(  HINSTANCE  g_hInst,  void  *  pPARAM_initQyMc,  QY_MC  *  pQyMc  )
{
	 int				iErr					=	-1;
	 
	 //
	 QY_MC  *  g_pQyMc  =  pQyMc;

	 //
	 //  2015/07/08. 调用前，应先new
	 if  (  !g_pQyMc  )  {
		 MACRO_qyAssert(  0,  _T(  "initQyMc failed, g_pQyMc is not newed"  )  );
		 return  -1;
	 }


	 //
	 PARAM_initQyMc  param_initQyMc;
	 memset(  &param_initQyMc,  0,  sizeof(  param_initQyMc  )  );
	 if  (  pPARAM_initQyMc  )  memcpy(  &param_initQyMc,  pPARAM_initQyMc,  sizeof(  param_initQyMc  )  );




	
	 //
	 g_pQyMc->iSystemId  =  qyGetSystemId(  );
	 //  g_pQyMc->iAppType   =   CONST_qyAppType_mc;
	 g_pQyMc->iAppType  =  qyGetAppType(  g_pQyMc->iSystemId,  _T(  CONST_qyRootKey_mcGui_netMc  )  );		//  2004/05/23ÐÞ¸Ä
	 g_pQyMc->iCustomId  =  qyGetCustomId(  );
	 g_pQyMc->iServiceId  =  qyGetServiceId(  g_pQyMc->iSystemId  );										//  2007/03/07
	 //
	 g_pQyMc->g_hInst = g_hInst;																			// Store instance handle in our global variable
	 //
	 //g_pQyMc->usAppAvLevel_default  =  qyGetAppAvLevel_default(  );											//  2013/06/28
	 //
#ifdef  __isCli__
	 g_pQyMc->ucbSupported_remoteStorage_default  =  bSupported_remoteStorage_default(  );					//  2014/08/03
	 g_pQyMc->ucbSupported_fileServer_default  =  bSupported_fileServer_default(  );						//  2015/08/04
	 //
	 g_pQyMc->ucbSupported_gps_default  =  bSupported_gps_default(  );										//  2013/06/28
#endif
	 //  2015/07/17
	 g_pQyMc->pfNewVar  =  param_initQyMc.pfNewVar;
	 g_pQyMc->pfFreeVar  =  param_initQyMc.pfFreeVar;
	 g_pQyMc->bCalledByQmd  =  param_initQyMc.bCalledByQmd;

	 //
	 LPCTSTR		errHintWndCls	=  (  qyGetAppType(  0,  0  )  ==  CONST_qyAppType_client  )  ?  CONST_qnmStatusToolWndClass_client  :  CONST_qnmStatusToolWndClass;

	 setDebugLogFileModuleName(  );
	 //  setErrHintWndCls(  errHintWndCls  );
	 int  iAppType  =  qyGetAppType(  qyGetSystemId(  ),  NULL  );
	 bool  bUsePipe  =  true;
	 bool  bCli  =  bAppClient(  iAppType  );

	 //
	 if  (  0  )  {
		 //initShowInfo(  0,  _T(  "syncQ_showInfo_qmc"  ),  errHintWndCls,  bUsePipe,  bCli,  &g_pQyMc->pShowInfoStruct  );
		 }
	 else  {
		   initShowInfo_cli(  0,  _T(  "syncQ_showInfo_qmc"  ),  (char*)"127.0.0.1",  &g_pQyMc->pShowInfoStruct  );
	 }
	 //  2013/07/31
	 //  g_pQyMc->pShowInfoStruct  =  get_pShowInfoStruct(  );

	 
	 //
	 QY_MC	*	pQM  =  g_pQyMc;
	 int				i;
	 DWORD				dwThreadDaemonId;						//ÓÃÓÚºóÌ¨Ë¢ÐÂ£¬ÔÝ²»Ê¹ÓÃ
	 //  CFile			*	pLckFile				=	NULL;
	 //  CQyString			lckCStr;
	 QY_DMITEM		*	pItem					=	NULL;		//  2005/11/07
	 QY_DYN_LIBS	*	pDynLib					=	NULL;
	 TCHAR				systemDir[MAX_PATH]		=	_T(  ""  );

	 myGetSystemDirectory(  systemDir,  mycountof(  systemDir  )  );
	 tTrailDir(  systemDir,  mycountof(  systemDir  )  );

	 //  if  (  qyInitSnmp(  &ghDll_InetMib1  )  )  goto  errLabel;
	 if  (  initDynLib(  (  void  **  )&pDynLib  )  )  goto  errLabel;	//  2007/01/21
#ifdef  __isCli__
	 if  (  initDynLib_dx(  systemDir,  &pDynLib->pLib_dx  )  )  goto  errLabel;
#endif

	 //  2010/07/05
	 if  (  qyTcpStart(  )  )  goto  errLabel;	//  

	 //  È¡»·¾³²ÎÊý,  2005/11/03
	 getQyEnv(  pDynLib,  &pQM->env  );
	 //  pQM->env.pDynLibs  =  pDynLib;
	 pQM->ucbDynLibInited  =  TRUE;

	 //  2009/07/12
	 g_pEnv  =  &pQM->env;

	 //
	 init_tickCnt();

	 //
	 pQM->dbg.dwTickCnt_start = myGetTickCount(NULL);

	 //
#ifdef  __DEBUG__
#endif




	 //  È¡ÄÚ´æ´óÐ¡. 2008/10/08
	 MEMORYSTATUS	memStatus;
	 memset(  &memStatus,  0,  sizeof(  memStatus  )  );
	 memStatus.dwLength  =  sizeof(  MEMORYSTATUS  );
	 GlobalMemoryStatus(  &memStatus  );
	 pQM->uiTotalPhys_memStatus  =  memStatus.dwTotalPhys;
	 if  (  isMem512(  pQM  )  )  OutputDebugString(  _T(  "Memory is <=  512M\n"  )  );


	 //
#ifdef  __DEBUG__
#endif 


	 //
	 TCHAR* pCmdLine; pCmdLine = GetCommandLine();
	 if (parseCmdLine_qyMc(pCmdLine, &pQM->appParams))  goto  errLabel;	//  2011/05/31


 


	 //  2013/06/13
#ifdef  __APP_qyMc_touchscreen__
		pQM->ucbApp_ts  =  TRUE;  
#endif

#ifdef  __DEBUG__
		pQM->ucbUseNamedShm  =  TRUE;
		pQM->ucbDebugSeparately  =  TRUE;
		traceLogA(  (char*)  "initQyMc: ucbUseNamedShm and ucbDebugSeparately is set for debug"  );

		//
		#if  0
			 pQM->env.iPlatformId  =  CONST_qyPlatform_win7;
			 traceLog((TCHAR*)  _T(  "WARNING: Fake os to be win7"  )  );
			 showInfo_open0(  0,  0,  _T(  "WARNING: Fake os to be win7"  )  );
		#endif

#endif

	 //  2016/02/15
	 if  (  bAppClient(  pQM->iAppType  )  )  {
		 #ifdef  __isCli__
			   set_who_showInfo(  _T(  "998"  )  );
		 #endif
		 }
	 else  {
		   set_who_showInfo(  _T(  "997qyMcMgr"  )  );
	 }

	 //
	 mytime(&pQM->i64StartTime_base);

	 //
	 if  (  getQyMcInitialCfg(  pQM,  &pQM->cfg  )  )  {
		 showInfo_open0(  0,  0,  _T(  "initQyMc: getQyMcInitialCfg failed"  )  );
		 goto errLabel;
	 }


	 //
	 //pQM->b__USE_webrtc1__ = true;
	 //
	 if (pQM->b__USE_webrtc1__) {
		 showInfo_open0(0, 0, _T("b__USE_webrtc1__ is true"));
	 }
	 //
#ifdef  __DEBUG__
	 //pQM->appParams.bNoAec = true;
#endif

	 //  2010/06/24
#ifdef  __SUPPORT_waveformFirst__
	 traceLog((TCHAR*)_T("initQyMc: Waveform is supported first"));
#ifdef  __DEBUG__
	 //  pQM->bUseDirectSound_toRecord  =  bSupported_directSound(  );
	 //  pQM->bUseDirectSound_toPlay  =  bSupported_directSound(  );
#endif
#else
		//
#ifdef  __isCli__
//  pQM->bUseDirectSound_toPlay  =  bSupported_directSound(  );
#if  0
	 if (bSupported_directSound())  pQM->uiAPlayType = CONST_aPlayType_dSound;  //  2017/02/16
	 else  pQM->uiAPlayType = CONST_aPlayType_wave;
#endif
	 pQM->uiAPlayType = getDefaultAPlayType(pQM,(int*)&pQM->uiAPlayType_16kMono16);
#endif
#endif


	 //
	 //  2016/09/04	 
	 extern  QM_dbFuncs		global_dbFuncs;
	 //
	 pQM->p_g_dbFuncs  =  &global_dbFuncs;
	 memset(  pQM->p_g_dbFuncs,  0,  sizeof(  global_dbFuncs  )  );


//  
#define		DEFAULT_uiMaxWarningInS_videoConference					1  *  15  *  60
#define		DEFAULT_uiMaxTimeInS_videoConference_noWarn				3  *  45  *  60			//  1  *  35  *  60
#define		DEFAULT_uiMaxTimeInS_videoConference_noWarn_freeVer		48  *  60  *  60		//  2016/10/16

	 
	 pQM->uiMaxWarningInS_videoConference  =  DEFAULT_uiMaxWarningInS_videoConference;
	 pQM->uiMaxTimeInS_videoConference_general  =  DEFAULT_uiMaxTimeInS_videoConference_noWarn  +  DEFAULT_uiMaxWarningInS_videoConference;	//  
	 pQM->uiMaxTimeInS_videoConference_freeVer  =  DEFAULT_uiMaxTimeInS_videoConference_noWarn_freeVer  +  DEFAULT_uiMaxWarningInS_videoConference;	//  

		//
		//
#if  1	//  2016/04/25
	 {
		 //
#ifdef  __isCli__
		 if  (  b_tttbbbMac(  pQM  )  )  {
			 //
			 pQM->ucb_tttbbbMac  =  TRUE;					//  2016/05/21
			 //
			 showInfo_open0(  0,  0,  _T(  "tttbbb mac"  )  );
			 pQM->uiMaxTimeInS_videoConference_general  =  9  *  60  *  60;
		 }
#endif
	
	 }
#endif
	 //
#ifdef  __DEBUG__
		#if  10
			pQM->uiMaxWarningInS_videoConference  =  2  *  60;
			pQM->uiMaxTimeInS_videoConference_general  =  300  *  60;
			
			//  2016/05/08
			#if  0
				 pQM->uiMaxWarningInS_videoConference  =  0.5  *  60;
				 pQM->uiMaxTimeInS_videoConference_general  =  1.5  *  60;			
			#endif

		#endif

#endif
	//
#ifdef  __DEBUG__
			#if  0
				 pQM->uiMaxWarningInS_videoConference  =  0.5  *  60;
				 pQM->uiMaxTimeInS_videoConference_general  =  3  *  60;			
				 MessageBox(  0,  _T(  "TEST: set small maxTimeInS_videoConf"  ),  _T(  "TEST"  ),  MB_OK  );
			#endif
#endif

	 //  2016/10/15
	 pQM->uiMaxTimeInS_videoConference  =  pQM->uiMaxTimeInS_videoConference_general;

	 //  2005/11/03
	 #ifdef  __DEBUG__
			 traceLogA(  (char*)  "before initQnmRes"  );
	 #endif
			 int  iResId_sys; iResId_sys = pQM->cfg.pGuiCfg->iResId_sys;
	 //
	 if  (  g_pQyMc->bCalledByQmd  )  {
		 iResId_sys  =  CONST_resId_sys_qmdCliHelp;
		 //  2015/07/17
		 //下面是要在cusRes里建立sys_qmdCliHelp对应的资源文件
	 }
	 //  
	 if  (  pQM->initQnmRes(  0,  pQM->env.usLangId,   iResId_sys  )  )  
	 {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "initQyMc failed, initQnmRes failed"  );
		 #endif
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "Client"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initQyMc failed, initQnmRes failed."  )  );
		 goto  errLabel;
	 }
	 pQM->ucbResInited  =  TRUE;
	 //
	 //  2015/06/28
	set_g_pQnmCusResInfo_qisGuiPublic(  &pQM->cusRes  );
	//
	if  (  pQM->addModuleMem_qnmRes(  CONST_resId_sys_qisGuiPublic  )  )  {		 
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "Client"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initQyMc failed, addModuleMem_qnmRes failed."  )  );
		goto  errLabel;
	}
	 //
#ifdef  __isCli__
		if  (  pQM->addModuleMem_qnmRes(  CONST_resId_sys_isCliHelp  )  )  goto  errLabel;
		if  (  pQM->addModuleMem_qnmRes(  CONST_resId_sys_qyMessengerHelp  )  )  goto  errLabel;
#endif
#ifndef  __isCli__	//  2013/06/15
		 set_cur_iResId_sys(  pQM->cfg.pGuiCfg->iResId_sys  );
#endif

	 

	 //  2010/10/02

	 //  2013/10/03
#ifdef  __isCli__
	    init_imgProcess( pQM );
#endif

	 //  2009/12/21

	 //  2009/01/04
	 setAllHints(  &pQM->cusRes,  GetSystemDefaultLangID(  )  );
	 //
	 //  2017/01/11
	 if  (  bAppClient(  pQM->iAppType  )  )  {
		 if  (  getCfgValByNameT(  pQM->cfg.iniFullFileName,  (TCHAR*)_T(  CONST_cfgName_qyClientTitle  ),  pQM->cfg.qyMcTitle,  mycountof(  pQM->cfg.qyMcTitle  )  )  )  pQM->cfg.qyMcTitle[0]  =  0;
		 if (getCfgValByNameT(pQM->cfg.iniFullFileName, (TCHAR*)_T(CONST_cfgName_qyClientTitle_part0), pQM->cfg.qyMcTitle_part0, mycountof(pQM->cfg.qyMcTitle_part0)))  pQM->cfg.qyMcTitle_part0[0] = 0;
		 if (getCfgValByNameT(pQM->cfg.iniFullFileName, (TCHAR*)_T(CONST_cfgName_qyClientTitle_part1), pQM->cfg.qyMcTitle_part1, mycountof(pQM->cfg.qyMcTitle_part1)))  pQM->cfg.qyMcTitle_part1[0] = 0;

		 }
	 else  {
		   if  (  getCfgValByNameT(  pQM->cfg.iniFullFileName,  (TCHAR*)_T(  CONST_cfgName_qyMcTitle  ),  pQM->cfg.qyMcTitle,  mycountof(  pQM->cfg.qyMcTitle  )  )  )  pQM->cfg.qyMcTitle[0]  =  0;
	 }

	 //
	 tTrim(  pQM->cfg.qyMcTitle  );
	 if  (  !pQM->cfg.qyMcTitle[0]  )  lstrcpyn(  pQM->cfg.qyMcTitle,  getResStr(  0,  &pQM->cusRes,  pQM->cfg.pGuiCfg->iResId_sys  ),  mycountof(  pQM->cfg.qyMcTitle  )  );
	 if  (  pQM->iServiceId  ==  CONST_qyServiceId_is  )  {
		 if  (  !bAppClient(  pQM->iAppType  )  )  {
			 //
			 _sntprintf(  pQM->cfg.qyMcTitle,  mycountof(  pQM->cfg.qyMcTitle  ),  _T(  "%s %s"  ),  pQM->cfg.qyMcTitle,  getTableResStr(  0,  CONST_subSystemIdTable_en,  &pQM->cusRes,  qyGetSubSystemId_mgr(  )  )  );  

			 //
			 //_sntprintf(  pQM->cfg.qyMcTitle,  mycountof(  pQM->cfg.qyMcTitle  ),  _T(  "%s %s"  ),  pQM->cfg.qyMcTitle,  getTableResStr(  0,  CONST_qyAppAvLevelTable_en,  &pQM->cusRes,  qyGetAppAvLevel_qyMc(  pQM  )  )  );  
			 //
			 if  (  bSupported_devAuth(  )  )  {
				 _sntprintf(  pQM->cfg.qyMcTitle,  mycountof(  pQM->cfg.qyMcTitle  ),  _T(  "%s %s"  ),  pQM->cfg.qyMcTitle,  getResStr(  0,  &pQM->cusRes,  CONST_resId_name_isMgr_plus  )  );
			 }
		 }
		 //
		 if  (  bAppClient(  pQM->iAppType  )  )  {
			 //_sntprintf(  pQM->cfg.qyMcTitle,  mycountof(  pQM->cfg.qyMcTitle  ),  _T(  "%s %s"  ),  pQM->cfg.qyMcTitle,  getTableResStr(  0,  CONST_qyAppAvLevelTable_en,  &pQM->cusRes,  qyGetAppAvLevel_qyMc(  pQM  )  )  );  
		 }
	 }
#ifndef  __WINCE__
	 if  (  bQnmDemo(  )  )  _sntprintf(  pQM->cfg.qyMcTitle,  mycountof(  pQM->cfg.qyMcTitle  ),  _T(  "%s( Demo )"  ),  pQM->cfg.qyMcTitle  );
#endif

	 //
	 pQM->pQnmEventTypeTable0  =  getResTable(  0,  &pQM->cusRes,  CONST_resId_qnmEventTypeTable0  );
	 pQM->pQnmEventTypeTable_pc  =  getResTable(  0,  &pQM->cusRes,  CONST_resId_qnmEventTypeTable_pc  );
	 pQM->pQnmEventTypeTable_op  =  getResTable(  0,  &pQM->cusRes,  CONST_resId_qnmEventTypeTable_op  );
	 pQM->pQnmEventTypeTable_netDev  =  getResTable(  0,  &pQM->cusRes,  CONST_resId_qnmEventTypeTable_netDev  );
	 if  (  !pQM->pQnmEventTypeTable0  ||  !pQM->pQnmEventTypeTable_pc  )  {
		 traceLogA(  (char*)  "initQyMc failed, eventTypeTable is null"  );  
		 goto  errLabel;
	 }

	 //
	 lstrcpyn(  pQM->cfg.name,  getResStr(  0,  &pQM->cusRes,  CONST_resId_network  ),  mycountof(  pQM->cfg.name  )  );
	 
#if  0
	 if  (  getProcedObjsCfg(  )  )  goto  errLabel;
#endif
	 
	 if  (  qmChkAppType(  pQM  )  )  goto  errLabel;


	 pQM->env.iEnvType  =  QY_ENVTYPE_MCGUI;
	 if  (  !bChkQyMcEnv(  pQM  )  )  goto errLabel;
	 
	 
	 //  2008/01/25
#if  0
	 pQM->hSema_syncCusModules  =  CreateSemaphore(  0,  pQM->cfg.cusModules.uiInitCnt_sema,  pQM->cfg.cusModules.uiMaxCnt_sema,  NULL  ); 
	 if  (  !isHandleValid(  pQM->hSema_syncCusModules  )  )  goto  errLabel;
#else
	 #include	"undeclareDebugNew.h"
	 pQM->pRw_syncCusModules  =  new  CMutexRW(  );
	 #include	"declareDebugNew.h"
	 if  (  !pQM->pRw_syncCusModules  )  goto  errLabel;
#endif


	 //  pQM->gui.hMutex  =  CreateMutex(  NULL,  FALSE,  CQyString(  DEFAULT_QY_MC_MUTEX  ).GetBuffer(  0  )  );
	 //  if  (  !pQM->gui.hMutex  )  {
	 // 	 debugLog(  "getAnAvailCtrlInfo( ): CreateMutex( ) failed."  );  goto  errLabel;
	 //  }

	 //
	 pQM->gui.ctx_gui_thread.dwThreadId9  =  GetCurrentThreadId(  );

#ifndef  __WINCE__
	 if  (  CQnmDb::initDbPool(  )  )  goto  errLabel;
	 
	 //  2013/06/08
	 QNM_db_pool* pPool; pPool = CQnmDb::getDbPool();
	 if  (  !pPool  )  goto  errLabel;

	 //
	 #ifdef  __isCli__
			 if  (  pQM->set_g_dbPool_isCliHelp(  pPool  )  )  goto  errLabel;
			 //
			 #ifdef  __USE_qyMessengerHelp__
					 if  (  set_g_dbPool_qyMessengerHelp(  pPool  )  )  goto  errLabel;
			 #endif
	 #endif

#endif

#ifndef  __WINCE__
	 if  (  initQyMcMainHook(  )  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "initQyMc: initQyMcMainHook failed"  )  );
		 #endif
		 goto  errLabel;	//  2005/10/01
	 }
	 pQM->gui.ucbMainHooked  =  TRUE;
#endif

	 if  (  initGenericQ(  _T(  "guiProcQ"  ),  CONST_mutexName_guiProcessQ,  0,  CONST_maxQNodes_guiProcessQ,  mymalloc,  myfree,  &pQM->gui.processQ  )  )  goto  errLabel;
	 pQM->gui.ucbProcessQInited  =  TRUE;


	 //
	 //
	 //
#if  1
	 for  (  i  =  0;  i  <  mycountof(  pQM->serviceGuiInfos  );  i  ++  )  {
		  QY_SERVICEGUI_INFO	*	pInfo	=	&pQM->serviceGuiInfos[i];
		  if  (  !pInfo->cfg.iServiceId  )  continue;
		  //
		  _sntprintf(  pInfo->name,  mycountof(  pInfo->name  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_qyServiceIdTable,  pInfo->cfg.iServiceId  )  );
		  
		  //  2016/09/19
		  pInfo->pParent  =  pQM;

		  //  2015/01/20
		  if  (  pInfo->cfg.pfNewVar  )  {
			  if  (  pInfo->cfg.pfNewVar(  pQM,  pInfo,  0  )  )  goto  errLabel;
			  }
		  else  {
			    if  (  pInfo->cfg.uiVarSize  )  {
					pInfo->pVar  =  mymalloc(  pInfo->cfg.uiVarSize  );
					if  (  !pInfo->pVar  )  goto  errLabel;
					memset(  pInfo->pVar,  0,  pInfo->cfg.uiVarSize  );		  
				}
		  }
		  			
		  //	 			
		  if  (  pInfo->cfg.pfInitVar  &&  pInfo->cfg.pfInitVar(  pQM,  pInfo,  0  )  )  {
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "Client"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initQyMc failed, pfInitVar failed."  )  );
			  goto  errLabel;
		  }
		  pInfo->ucbVarInited  =  TRUE;
		  
	 }
#endif

#ifndef  __WINCE__
		//  
		if  (  initInputMgr(  pQM->g_hInst,  &pQM->inputMgr  )  )  goto  errLabel;
		pQM->bInputMgrInited  =  TRUE;
#endif

#ifdef  __SUPPORT_childFrmMenu__
		if  (  !(  pQM->gui.hMenuChildFrm =  LoadMenu(  AfxGetApp(  )->m_hInstance,  MAKEINTRESOURCE(  IDR_DOCTYPE_QYMC  )  )  )  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "initQyMc failed, LoadMenu IDR_DOCTYPE_QYMC failed"  )  );
			#endif
			goto  errLabel;
		}
	 
		//  
		if  (  !pQM->cfg.ucbAdvancedVer  )  {
			//  if  (  pQM->iSystemId  ==  CONST_qySystemId_netMc2  )  RemoveMenu(  pQM->gui.hSubMenuMcMgr,  8,  MF_BYPOSITION  );
		}
	 
		QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQM->cusRes  );	 
		if  (  !pResMem  )  goto  errLabel;

		//  
		if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_childFrmMenu  )  )  )  goto  errLabel;
		if  (  makeDynaMenu(  &pQM->cusRes,  pQM->gui.hMenuChildFrm,  pItem,  getMenuStatus_frame,  0  )  )  goto  errLabel;	//  2005/11/06
#endif
		//  2017/06/21


	 //  2010/08/03
		G_guiData_qyMc* pGuiData; pGuiData = get_g_guiData();
	 pGuiData->pCusRes  =  &pQM->cusRes;

	 //
	 if  (  gGuiData_init(  pQM->env.usLangId,  pGuiData  )  )  goto  errLabel;

	 //
	 #ifdef  __DEBUG__
			 testInMain(  pQM  );
	 #endif


	 iErr  =  0;

errLabel:

	 //  if  (  pLckFile  )  delete  pLckFile;
	 if  (  iErr  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "initQyMc failed"  )  );
		 #endif
		 exitQyMc(  pQyMc  );
	 }
	 	 
	 return  iErr;
}



 __declspec(  dllexport  )  void  exitQyMc(  QY_MC  *  pQyMc  )
{
	traceLogA(  (char*)  "exitQyMc enters"  );

	 QY_MC  *  pQM  =  pQyMc;
	 if ( !pQM ) return;

	 pQM->bQuit  =  TRUE;

	 if  (  pQM->gui.hProcessStatusTool  )  {  
		 if  (  TerminateProcess(  pQM->gui.hProcessStatusTool,  1  )  )  {
			 CloseHandle(  pQM->gui.hProcessStatusTool  );  pQM->gui.hProcessStatusTool  =  NULL;
		 }
	 }

	 //
	 if  (  pQM->bLogon  )  old_qyMcLogoff(  pQM  );

	 //
	 stopCusModules(  pQM  );

	 exitAllDaemonThreads(  pQM  );

	 //  2011/07/26
	 G_guiData_qyMc	*	pGuiData	=	get_g_guiData(  );
	 gGuiData_exit(  pGuiData  );

	 //
	 if  (  pQM->gui.hMenuChildFrm  )  {  DestroyMenu(  pQM->gui.hMenuChildFrm  );  pQM->gui.hMenuChildFrm  =  NULL;  }

	 //  2008/11/22
	 if  (  pQM->bInputMgrInited  )  {  exitInputMgr(  &pQM->inputMgr  );  pQM->bInputMgrInited  =  FALSE;  }

	 //
	 int  i;
	 for  (  i  =  0;  i  <  mycountof(  pQM->serviceGuiInfos  );  i  ++  )  {
		  QY_SERVICEGUI_INFO	*	pInfo	=	&pQM->serviceGuiInfos[i];
		  if  (  !pInfo->cfg.iServiceId  )  continue;

		  //
		  if  (  pInfo->ucbVarInited  )  {
			  if  (  pInfo->cfg.pfExitVar  )  pInfo->cfg.pfExitVar(  pQM,  pInfo,  0  );  
			  pInfo->ucbVarInited  =  FALSE;
		  }			  
		  if  (  pInfo->pVar  )  {
			  if  (  pInfo->cfg.pfFreeVar  )  {  //  2015/01/20
				  pInfo->cfg.pfFreeVar(  pQM,  pInfo,  0  );
				  }	
			  else  {
				    free(  pInfo->pVar  );  pInfo->pVar  =  NULL;
			  }
		  }
	
		  //
	 }

	 //  2007/12/30
	 if  (  pQM->bCusModulesLoaded  )  {
		 unloadCusModules(  pQM  );  pQM->bCusModulesLoaded  =  FALSE;
	 }

	 //
#if  0
	 if  (  pQM->gui.ucbGuiQInited  )  exitQyQ2(  &pQM->gui.guiQ2  );				//  2009/03/24
#endif
#if  0
	 if  (  pQM->gui.ucbGpsQ2Inited  )  exitQyQ2(  &pQM->gui.gpsQ2  );				//  2012/04/20
#endif

	 if  (  pQM->gui.ucbProcessQInited  )  exitGenericQ(  &pQM->gui.processQ  );	//  2007/06/01

#ifndef  __NOTSUPPORT_DB__

	 if  (  pQM->gui.ucbMainHooked  )  {  exitQyMcMainHook(  );	 pQM->gui.ucbMainHooked  =  FALSE;  }	//  2005/10/01

	 //  if  (  pQM->gui.pDb  )  {  exitQyMcDb(  pQM,  pQM->gui.pDb  );  pQM->gui.pDb  =  NULL;  }
	 exitProcedObjDbs(  pQM  );	//  2006/12/24, ÒÔºó£¬gui.pDb²»ÔÙ×÷ÎªÖ÷±äÁ¿£¬½öÎªÁË¼æÈÝÆð¼û£¬±£ÁôÏÂÀ´£¬Ö¸ÏòprocedObjs[iMainSysIndex].pDb.Êý¾Ý¿â¾ä±ú¿¿procedObjsÀ´¹ÜÀíºÍÊÍ·Å

	 CQnmDb::exitDbPool(  );
#endif
     
	 //  if  (  pQM->gui.hMutex  )  {  CloseHandle(  pQM->gui.hMutex  );  pQM->gui.hMutex  =  NULL;  }

	 //  2008/01/26
#if  0
	 if  (  isHandleValid(  pQM->hSema_syncCusModules  )  )  {  CloseHandle(  pQM->hSema_syncCusModules  );  pQM->hSema_syncCusModules  =  NULL;	}
#else
	 MACRO_safeDelete(  pQM->pRw_syncCusModules  );
#endif

#if  0
	 if  (  pQM->gui.pLckFile  )  {
		 CFile	*	pLckFile  =  (  CFile  *  )pQM->gui.pLckFile;
		 delete  pLckFile;		pQM->gui.pLckFile  =  NULL;
	 }
#endif
	 if  (  pQM->gui.hMutex_singleInstance  )  {
		 CloseHandle(  pQM->gui.hMutex_singleInstance  );
		 pQM->gui.hMutex_singleInstance  =  NULL;
	 }

#ifdef  __isCli__	//  2013/10/03
		exit_imgProcess(  );
#endif


	 //
	 if  (  pQM->ucbResInited  )  {  
		 //  exitQnmRes(  0,  &pQM->cusRes  );  
		 pQM->exitQnmRes(  0  );  
		 pQM->ucbResInited  =  FALSE;  
	 }	//  2005/11/03

	 
	 //
#ifndef  __WINCE__
	 if  (  pQM->iAppType  !=  CONST_qyAppType_client  )  {
#if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
	 	 exitRnbDog(  &pQM->licenseCtx  );	 //  2005/06/27
#endif
	 }
#endif
	 
	 //
	 if  (  pQM->ucbEncInited  )  {  exitQnmEnc(  &pQM->encCtx,  NULL,  NULL,  NULL  );  pQM->ucbEncInited  =  FALSE;  }
	 
	 //
	 //qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pQM->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "All exit."  )  );
	 showInfo_open0(0, 0, _T("all exit."));

	 //
	 exitShowInfo(  &pQM->pShowInfoStruct  );

	 //  2010/07/05
	 qyTcpEnd(  );

	 //  if  (  ghDll_InetMib1  )  qyExitSnmp(  &ghDll_InetMib1  );
	 if  (  pQM->ucbDynLibInited  )  {	//  2007/01/21
#ifdef  _isCli__
		 exitDynLib_dx(  &(  (  QY_DYN_LIBS  *  )pQM->env.pDynLibs  )->pLib_dx  );
#endif
		 exitDynLib(  &pQM->env.pDynLibs  );	pQM->ucbDynLibInited  =  FALSE;
	 }


	 //  2015/07/08
#if  0
	 //MACRO_safeFree(  g_pQyMc  );
	 if  (  g_pQyMc  )  {
		 QY_MC  *  pQyMc  =  (  QY_MC  *  )g_pQyMc;
		 MACRO_safeDelete(  pQyMc  );
		 g_pQyMc  =  NULL;
	 }
#endif

	 //
	 traceLogA(  (char*)  "exitQyMc( ) leaves."  );

	 return;
}
