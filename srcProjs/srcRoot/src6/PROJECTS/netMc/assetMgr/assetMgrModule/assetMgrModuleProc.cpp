
#include	"stdafx.h"
#include	"qyString.h"
#include	"assetMgrModuleDaemon.h"

 CAssetMgrModuleDaemon	gDaemon;

extern  "C"  int  qyModuleExit(  void  *  p1,  void  *  p2  );



  extern  "C"  int  qyModuleGetInitialCfg(  void  *  p1,  void  *  p2  )
 {
	 int						iErr		=	-1;
	 QY_MODULE				*	pModule		=  (  QY_MODULE  *  )p1;
	 pModule->p2							=  &gDaemon;
	 CAssetMgrModuleDaemon	*	pDaemon		=  (  CAssetMgrModuleDaemon  *  )pModule->p2;
	 TCHAR						regBuf[512],  buf[1024];
	 int						cnt;
	 QY_LICENSE_CTX			*	pLicenseCtx		=	NULL;
	 BOOL						bLicenseCtxInited	=	FALSE;
	 unsigned  char				ucbDogOk	=	TRUE;
	 int						iSystemId	=	CONST_qySystemId_assetMgr;	//  这里暂时用这个值顶替一下。2007/06/07


	 
	 pDaemon->var.logCtx.ucbLogOn  =  TRUE;
	 _snprintf(  pDaemon->var.logCtx.filePart,  sizeof(  pDaemon->var.logCtx.filePart  ),  "%s.log",  pModule->info.name  );
	 _sntprintf(  pDaemon->var.logCtx.reg.rootKey,  mycountof(  pDaemon->var.logCtx.reg.rootKey  ),  _T(  "%s"  ),  _T(  CONST_qyRootKey_qnmTemp  )  );
	 _snprintf(  pDaemon->var.logCtx.regValName,  sizeof(  pDaemon->var.logCtx.regValName  ),  "%s : %s",  pModule->info.callerId,  pModule->info.name  );

	 traceInfo(  &pDaemon->var.logCtx,  "qyModuleGetInitialCfg enters"  );

	 if  (  initQnmEnc(  &pDaemon->var.encCtx,  NULL,  NULL,  &pDaemon->var.commEncCtx  )  )  goto  errLabel;
	 pDaemon->var.ucbEncInited  =  TRUE;

	 //
	 if  (  initRnbDog(  &pDaemon->var.licenseCtx  )  )  goto  errLabel;
	 bLicenseCtxInited =  TRUE;
	 
	 //  pLicenseCtx  =  (  QY_LICENSE_CTX  *  )pModuleInfo->pLicenseCtx;
	 pLicenseCtx  =  (  QY_LICENSE_CTX  *  )&pDaemon->var.licenseCtx;
	 #ifndef  __WITHOUT_CHKDOG__
			  if  (  !pLicenseCtx  ||  !pLicenseCtx->bRnbDogInited  )  ucbDogOk  =  FALSE;
			  else  if  (  !bQyDogOk(  pLicenseCtx,  pModule->info.name  )  )  {
				  		AfxMessageBox(  _T(  "assetMgr: cannot find usb key"  )  );  ucbDogOk  =  FALSE;
			  }
	 #endif
	 if  (  !ucbDogOk  )  goto  errLabel;


	 _sntprintf(  regBuf,  mycountof(  regBuf  ),  _T(  "%s\\%s\\%s"  ),  _T(  CONST_qyRootKey_mc  ),  _T(  CONST_qyModulesSubKey  ),  pModule->info.name  );
	 if  (  qyGetRegCfg(  regBuf,  _T(  CONST_regValName_installDir  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
	 if  (  !buf[0]  &&  qyGetRegCfg(  _T(  CONST_qyRootKey_qnmResp  ),  _T(  CONST_regValName_installDir  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  goto  errLabel;
	 lstrcpyn(  pDaemon->var.cfg.installDir,  CString(  buf  ),  mycountof(  pDaemon->var.cfg.installDir  )  );
	 tTrailDir(  pDaemon->var.cfg.installDir,  mycountof(  pDaemon->var.cfg.installDir  )  );

	 setSockTimeout(  &pDaemon->var.cfg.to  );

	 QY_REG	reg;
	 //  safeStrnCpy(  CONST_qyRootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	 lstrcpyn(  reg.rootKey,  _T(  CONST_qyRootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
	 reg.pEncCtx  =  &pDaemon->var.encCtx;
	 //
	 if  (  getQnmDbParams(  &reg,  iSystemId,  FALSE,  _T(  CONST_qyDsn_netMc  ),  &pDaemon->var.cfg.db  )  )  goto  errLabel;
	 //  if  (  !pDaemon->bSetLongProperty(  CONST_qyPropertyId_dbType,  pDaemon->var.cfg.db.iDbType  )  )  goto  errLabel;			//  2006/05/03
	 //  if  (  !pDaemon->bSetStrProperty(  CONST_qyPropertyId_connectStr,  pDaemon->var.cfg.db.connectStr  )  )  goto  errLabel;
	 if  (  !pDaemon->bSetPtrProperty(  CONST_qyPropertyId_logCtx,  &pDaemon->var.logCtx  )  )  goto  errLabel;
	 if  (  !pDaemon->bSetStrProperty(  CONST_qyPropertyId_installDir,  pDaemon->var.cfg.installDir  )  )  goto  errLabel;

	 cnt  =  0;
	 setScanStruct(  CONST_nmsOp_nbtScan,  0,  qnmCommonScanThreadProc,  qnmScanFunc,  pDaemon,  &pDaemon->var.cfg.scanStructs[cnt]  );	cnt  ++  ;
	 MACRO_qyAssert(  cnt  <=  sizeof(  pDaemon->var.cfg.scanStructs  )  /  sizeof(  pDaemon->var.cfg.scanStructs[0]  ),  _T(  "扫描设置越界"  )  );

	 for  (  cnt  =  0;  cnt  <  sizeof(  pDaemon->var.threadProcs  )  /  sizeof(  pDaemon->var.threadProcs[0]  );  cnt  ++  )  {
		  if  (  cnt  >=  sizeof(  pDaemon->var.cfg.scanStructs  )  /  sizeof(  pDaemon->var.cfg.scanStructs[0]  )  )  break;
		  if  (  !pDaemon->var.cfg.scanStructs[cnt].pfThreadProc  )  break;
		  pDaemon->var.threadProcs[cnt]  =  (  QY_THREADPROC  )pDaemon->var.cfg.scanStructs[cnt].pfThreadProc;
		  pDaemon->var.pThreadParams[cnt]  =  &pDaemon->var.cfg.scanStructs[cnt];
	 }	 
	 MACRO_qyAssert(  cnt  <=  sizeof(  pDaemon->var.threadProcs  )  /  sizeof(  pDaemon->var.threadProcs[0]  ),  _T(  "线程函数太多"  )  );

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 if  (  bLicenseCtxInited  )  exitRnbDog(  &pDaemon->var.licenseCtx  );
	 }
	 if  (  !iErr  )  {
		 pModule->info.pLicenseCtx  =  &pDaemon->var.licenseCtx;		//  2007/03/01, 因为圣天狗出了问题，似乎不支持动态DLL共享license, 所以改成局部的
	 }

	 traceInfo(  &pDaemon->var.logCtx,  "qyModuleGetInitialCfg leaves"  );

	 return  iErr;
}


 extern  "C"  int  qyModuleRefreshCfg(  void  *  p1,  void  *  p2  )
{
	 QY_MODULE				*	pModule		=  (  QY_MODULE  *  )p1;
	 CAssetMgrModuleDaemon	*	pDaemon		=  (  CAssetMgrModuleDaemon  *  )pModule->p2;

	 for  (  int  i  =  0;  i  <  sizeof(  pDaemon->var.cfg.scanStructs  )  /  sizeof(  pDaemon->var.cfg.scanStructs[0]  );  i  ++  )  {
		  if  (  pDaemon->var.cfg.scanStructs[i].pRegValName  )  qyRefreshRegCfg_ucb(  _T(  CONST_qyRootKey_qnmScheduler  ),  pDaemon->var.cfg.scanStructs[i].pRegValName,  &pDaemon->var.cfg.scanStructs[i].ucbStopScan  );
	 }

	 qyRefreshRegCfg_ucb(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_startRegScan  ),  &pDaemon->var.cfg.ucbStartRegScan  );
	 qyRefreshRegCfg_ucb(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_startRespForUnreg  ),  &pDaemon->var.cfg.ucbStartRespForUnreg  );

	 return  0;

}



 extern  "C"  int  qyModuleInit(  void  *  p1,  void  *  p2  )
{
	 int							iErr		=	-1;
	 QY_MODULE					*	pModule		=	(  QY_MODULE  *  )p1;
	 CAssetMgrModuleDaemon		*	pDaemon		=	(  CAssetMgrModuleDaemon  *  )pModule->p2;
	 int							index;
	 DWORD							dwThreadId;
	 
	 traceLogA(  "%s: qyModuleInit called.",  pModule->info.name  );

	 if  (  qyModuleRefreshCfg(  p1,  p2  )  )  goto  errLabel;

	 for  (  index  =  0;  pDaemon->var.threadProcs[index];  index  ++  )  {
		  pDaemon->var.hThreads[index]  =  CreateThread(  NULL,  0,  pDaemon->var.threadProcs[index],  (  LPVOID  )pDaemon->var.pThreadParams[index],  0,  &dwThreadId  );
		  if  (  !pDaemon->var.hThreads[index]  )  goto  errLabel;
	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  qyModuleExit(  p1,  p2  );

	 traceLogA(  "%s: qyModuleInit leaves with %s",  pModule->info.name,  iErr  ?  "失败"  :  "成功"  );

	 return  iErr;
}


  extern  "C"  int  qyModuleExit(  void  *  p1,  void  *  p2  )
{
	 int							index;
	 QY_MODULE					*	pModule		=	(  QY_MODULE  *  )p1;
	 CAssetMgrModuleDaemon		*	pDaemon		=	(  CAssetMgrModuleDaemon  *  )pModule->p2;

	 traceLogA(  "%s: qyModuleExit enters",  pModule->info.name  );
	 
	 pDaemon->startToQuit(  );

	 index  =  0;
	 for  (  index  =  0;  index  <  sizeof(  pDaemon->var.hThreads  )  /  sizeof(  pDaemon->var.hThreads[0]  );  index  ++  )  {
		  MACRO_qyNullThread(  pDaemon->var.hThreads[index]  );
	 }

	 exitRnbDog(  &pDaemon->var.licenseCtx  );	//  2007/03/01
	 pModule->info.pLicenseCtx  =  0;

	 if  (  pDaemon->var.ucbEncInited  )  {
		 exitQnmEnc(  &pDaemon->var.encCtx,  NULL,  NULL,  &pDaemon->var.commEncCtx  );  pDaemon->var.ucbEncInited  =  FALSE;
	 }


	 traceLogA(  "%s: qyModuleExit leaves",  pModule->info.name  );

	 return  0;
}

 int  testProc(  void  *  p1,  void  *  p2  )
{
	 traceLogA(  "testProkkkkkkkkkkc"  );

	 return  0;
}

 static  QY_DMITEM  sModuleProcTable[]  =
{
	{	0,	_T(  "qyModuleInit"  ),				(  TCHAR  *  )qyModuleInit,	},
	{	1,	_T(  "qyModuleExit"  ),				(  TCHAR  *  )qyModuleExit,	},
	{	2,	_T(  "qyModuleGetInitialCfg"  ),	(  TCHAR  *  )qyModuleGetInitialCfg,		},
	{	3,	_T(  "qyModuleRefreshCfg"  ),		(  TCHAR  *  )qyModuleRefreshCfg,		},
	{	10,	_T(  "testProc"  ),					(  TCHAR  *  )testProc,		},
	{	-1,	NULL,								},
};
  
 extern  "C"  __declspec( dllexport )  int  qyGetModuleInfo(  void  *  pModuleInfoParam,  void  *  p2  )
{
	 int				iRet			=	-1;
	 QY_MODULE_INFO	*	pModuleInfo		=  (  QY_MODULE_INFO  *  )pModuleInfoParam;
	 TCHAR			*	moduleName		=	_T(  CONST_qyModuleName_assetMgr  );

	 if  (  !pModuleInfo  )  return  -1;

	 //  setDebugLogFileModuleName(  );
	 setErrHintWndCls(  CONST_qnmStatusToolWndClass  );

	 
	 _sntprintf(  pModuleInfo->name,  mycountof(  pModuleInfo->name  ),  _T(  "%s"  ),  moduleName  );

	 //  注意：这里靠对模块安装情况进行功能的防重叠，以后要修改
	 if  (  getQnmModulesLoadedInfo(  &gDaemon.var.cfg.modulesLoadedInfo  )  )  goto  errLabel;
	 
	 if  (  !gDaemon.var.cfg.modulesLoadedInfo.ulbNmsModuleLoaded  &&  !lstrcmpi(  pModuleInfo->callerId,  _T(  CONST_qyModuleName_resp  )  )  )  pModuleInfo->pProcTable  =  sModuleProcTable;
	 else  pModuleInfo->pProcTable  =  CONST_qyNullTable;

	 iRet  =  0;

errLabel:


	 traceLogA(  "%s: qyGetModuleInfo returns %s",  moduleName,  iRet  ?  "失败"  :  "成功"  );
	 
	 return  iRet;

}


