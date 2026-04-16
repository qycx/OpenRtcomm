

#include	<afxdb.h>
#include	<windowsx.h>
#include	"qyString.h"
#include	"qyNmsModule.h"
#include	"qyTCharCommProc.h"

//  
CQnmsModuleDaemon	qyNms;


extern  "C"  int  qyModuleExit(  void  *  p1,  void  *  p2  );


 extern  "C"  int  qyModuleGetInitialCfg(  void  *  p1,  void  *  p2  )
{
	 int					iErr		=	-1;
	 QY_MODULE			*	pModule		=	(  QY_MODULE  *  )p1;
	 pModule->p2						=	&qyNms;
	 CQnmsModuleDaemon	*	pDaemon		=	(  CQnmsModuleDaemon  *  )pModule->p2;
	 QY_NMS_DAEMON		*	pVar		=	NULL;
	 TCHAR					regBuf[512],  buf[1024];
	 int					cnt;
	 QY_LICENSE_CTX		*	pLicenseCtx		=	NULL;
	 unsigned  char			ucbDogOk		=	TRUE;
	 BOOL					bModuleLicenseCtxInted	=	FALSE;

	 
	 pVar  =  &qyNms.var;

	 pVar->logCtx.ucbLogOn  =  TRUE;
	 _snprintf(  pVar->logCtx.filePart,  sizeof(  pVar->logCtx.filePart  ),  "%s.log",  pModule->info.name  );
	 _sntprintf(  pVar->logCtx.reg.rootKey,  mycountof(  pVar->logCtx.reg.rootKey  ),  _T(  "%s"  ),  _T(  CONST_qyRootKey_qnmTemp  )  );
	 _snprintf(  pVar->logCtx.regValName,  sizeof(  pVar->logCtx.regValName  ),  "%s : %s",  pModule->info.callerId,  pModule->info.name  );

	 traceInfo(  &pVar->logCtx,  "qyModuleGetInitialCfg enters"  );

	 if  (  initQnmEnc(  &pVar->encCtx,  NULL,  NULL,  &pVar->commEncCtx  )  )  goto  errLabel;
	 pVar->ucbEncInited  =  TRUE;

	 if  (  initRnbDog(  &pVar->licenseCtx  )  )  goto  errLabel;
	 bModuleLicenseCtxInted =  TRUE;

	 //  pLicenseCtx  =  (  QY_LICENSE_CTX  *  )pModuleInfo->pLicenseCtx;
	 pLicenseCtx  =  &pVar->licenseCtx;
	 #ifndef  __WITHOUT_CHKDOG__
			  if  (  !pLicenseCtx  ||  !pLicenseCtx->bRnbDogInited  )  ucbDogOk  =  FALSE;
			  else  if  (  !bQyDogOk(  pLicenseCtx,  pModule->info.name  )  )  {
				  		AfxMessageBox(  _T(  "nms: cannot find usb key"  )  );  ucbDogOk  =  FALSE;
			  }
	 #endif
	 if  (  !ucbDogOk  )  goto  errLabel;


	 _sntprintf(  regBuf,  mycountof(  regBuf  ),  _T(  "%s\\%s\\%s"  ),  _T(  CONST_qyRootKey_mc  ),  _T(  CONST_qyModulesSubKey  ),  _T(  CONST_qyModuleName_nms  )  );
	 if  (  qyGetRegCfg(  regBuf,  _T(  CONST_regValName_installDir  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
	 if  (  !buf[0]  &&  qyGetRegCfg(  _T(  CONST_qyRootKey_qnmResp  ),  _T(  CONST_regValName_installDir  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  goto  errLabel;
	 lstrcpyn(  pVar->cfg.installDir,  CString(  buf  ),  mycountof(  pVar->cfg.installDir  )  );
	 tTrailDir(  pVar->cfg.installDir,  mycountof(  pVar->cfg.installDir  )  );
	 
	 setSockTimeout(  &pVar->cfg.to  );

	 QY_REG				reg;
	 QY_SERVICE_CFG		serviceCfg;
	 //	 
	 memset(  &reg,  0,  sizeof(  reg  )  );
	 memset(  &serviceCfg,  0,  sizeof(  serviceCfg  )  );
	 //
	 serviceCfg.iServiceId  =  CONST_qyServiceId_qwm;
	 //
	 //  if  (  safeStrCpy(  qnmVerStr(  serviceCfg.iServiceId  ),  serviceCfg.ver,  sizeof(  serviceCfg.ver  )  )  )  goto  errLabel;
	 if  (  safeWcsCpy(  _T(  CONST_qyRootKey_mc  ),  serviceCfg.sysRootKey,  mycountof(  serviceCfg.sysRootKey  )  )  )  goto  errLabel;
	 //
	 //  safeStrnCpy(  CONST_qyRootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	 lstrcpyn(  reg.rootKey,  _T(  CONST_qyRootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
	 reg.pEncCtx  =  &pVar->encCtx;
	 if  (  getQnmDbParams(  &reg,  CONST_qySystemId_nms,  FALSE,  _T(  CONST_qyDsn_netMc  ),  &serviceCfg.db  )  )  goto  errLabel;
	 //
	 if  (  !pDaemon->bSetSpecialProperty(  CONST_qyPropertyId_serviceCfg,  &serviceCfg,  0,  0  )  )  goto  errLabel;
	 //
	 if  (  !pDaemon->bSetPtrProperty(  CONST_qyPropertyId_logCtx,  &pVar->logCtx  )  )  goto  errLabel;
	 if  (  !pDaemon->bSetStrProperty(  CONST_qyPropertyId_installDir,  pVar->cfg.installDir  )  )  goto  errLabel;
	 
	 cnt  =  0; 
	 setScanStruct(  CONST_nmsOp_snmpScan,  0,  qnmCommonScanThreadProc,  qnmScanFunc,  pDaemon,  &pVar->cfg.scanStructs[cnt]  );	cnt  ++  ;
	 setScanStruct(  CONST_nmsOp_nbtScan,  0,  qnmCommonScanThreadProc,  qnmScanFunc,  pDaemon,  &pVar->cfg.scanStructs[cnt]  );	cnt  ++  ;
	 if  (  bQnmModuleInstalled(  CONST_qyRootKey_mc,  CONST_qyModuleName_netFlow  )  )  setScanStruct(  CONST_nmsOp_snmpScan,  CONST_snmpOpCmd_monFlow,  qnmSnmpNetFlowThreadProc,  qnmScanFunc,  pDaemon,  &pVar->cfg.scanStructs[cnt]  );	cnt  ++  ;
	 MACRO_qyAssert(  cnt  <=  sizeof(  pVar->cfg.scanStructs  )  /  sizeof(  pVar->cfg.scanStructs[0]  ),  _T(  "扫描设置越界"  )  );

	 for  (  cnt  =  0;  cnt  <  sizeof(  pVar->threadProcs  )  /  sizeof(  pVar->threadProcs[0]  );  cnt  ++  )  {
		  if  (  cnt  >=  sizeof(  pVar->cfg.scanStructs  )  /  sizeof(  pVar->cfg.scanStructs[0]  )  )  break;
		  if  (  !pVar->cfg.scanStructs[cnt].pfThreadProc  )  break;
		  pVar->threadProcs[cnt]  =  (  QY_THREADPROC  )pVar->cfg.scanStructs[cnt].pfThreadProc;
		  pVar->pThreadParams[cnt]  =  &pVar->cfg.scanStructs[cnt];
	 }	 

	 MACRO_qyAssert(  cnt  <=  sizeof(  pVar->threadProcs  )  /  sizeof(  pVar->threadProcs[0]  ),  _T(  "线程函数太多"  )  );
	 
	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 if  (  bModuleLicenseCtxInted  )  exitRnbDog(  &pVar->licenseCtx  );		 
	 }
	 if  (  !iErr  )  {
		 pModule->info.pLicenseCtx  =  &pVar->licenseCtx;		//  2007/03/01, 因为圣天狗出了问题，似乎不支持动态DLL共享license, 所以改成局部的
	 }


	 traceInfo(  &pVar->logCtx,  "qyModuleGetInitialCfg leaves"  );

	 return  iErr;
}


  extern  "C"  int  qyModuleRefreshCfg(  void  *  p1,  void  *  p2  )
{
	 QY_NMS_DAEMON		*	pVar	=	&qyNms.var;


	 for  (  int  i  =  0;  i  <  sizeof(  pVar->cfg.scanStructs  )  /  sizeof(  pVar->cfg.scanStructs[0]  );  i  ++  )  {
		  if  (  pVar->cfg.scanStructs[i].pRegValName  )  qyRefreshRegCfg_ucb(  _T(  CONST_qyRootKey_qnmScheduler  ),  pVar->cfg.scanStructs[i].pRegValName,  &pVar->cfg.scanStructs[i].ucbStopScan  );
	 }
	 qyRefreshRegCfg_ucb(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_startRegScan  ),  &pVar->cfg.ucbStartRegScan  );
	 qyRefreshRegCfg_ucb(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_startRespForUnreg  ),  &pVar->cfg.ucbStartRespForUnreg  );

	 return  0;

}


 extern  "C"  int  qyModuleInit(  void  *  p1,  void  *  p2  )
{
	 int				iErr		=	-1;
	 QY_MODULE		*	pModule		=	(  QY_MODULE  *  )p1;
	 int				index;
	 DWORD				dwThreadId;
	 QY_NMS_DAEMON	*	pVar		=	&qyNms.var;
	 
	 traceLogA(  "qyNmsModule.dll: qyModuleInit called."  );

	 if  (  qyModuleRefreshCfg(  p1,  p2  )  )  goto  errLabel;

	 for  (  index  =  0;  pVar->threadProcs[index];  index  ++  )  {
		  pVar->hThreads[index]  =  CreateThread(  NULL,  0,  pVar->threadProcs[index],  pVar->pThreadParams[index],  0,  &dwThreadId  );
		  if  (  !pVar->hThreads[index]  )  goto  errLabel;
	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  qyModuleExit(  p1,  p2  );

	 traceLogA(  "qyNmsModule.dll: qyModuleInit leaves with %s",  iErr  ?  "失败"  :  "成功"  );

	 return  iErr;
}

 extern  "C"  int  qyModuleExit(  void  *  p1,  void  *  p2  )
{
	 QY_MODULE		*	pModule		=	(  QY_MODULE  *  )p1;
	 int					index;
	 QY_NMS_DAEMON		*	pVar	=	&qyNms.var;

	 traceLogA(  "qyNmsModule.dll: qyModuleExit enters"  );
	 
	 qyNms.startToQuit(  );

	 index  =  0;
	 for  (  index  =  0;  index  <  sizeof(  pVar->hThreads  )  /  sizeof(  pVar->hThreads[0]  );  index  ++  )  {
		  MACRO_qyNullThread(  pVar->hThreads[index]  );
	 }

	 exitRnbDog(  &pVar->licenseCtx  );	//  2007/03/01
	 pModule->info.pLicenseCtx  =  0;

	 if  (  pVar->ucbEncInited  )  {
		 exitQnmEnc(  &pVar->encCtx,  NULL,  NULL,  &pVar->commEncCtx  );  pVar->ucbEncInited  =  FALSE;
	 }

	 traceLogA(  "qyNmsModule.dll: qyModuleExit leaves"  );

	 return  0;
}



 QY_DMITEM  moduleForDaemonProcTable[]  =  
{
	{	-1,	NULL,		},
};

 QY_DMITEM  moduleForRespProcTable[]  =
{
	{	0,	_T(  "qyModuleInit"  ),				(  TCHAR  *  )qyModuleInit,	},
	{	1,	_T(  "qyModuleExit"  ),				(  TCHAR  *  )qyModuleExit,	},
	{	2,	_T(  "qyModuleGetInitialCfg"  ),	(  TCHAR  *  )qyModuleGetInitialCfg,		},
	{	3,	_T(  "qyModuleRefreshCfg"  ),		(  TCHAR  *  )qyModuleRefreshCfg,		},
	{	-1,	NULL,								},
};
   
 extern  "C"  __declspec( dllexport )  int  qyGetModuleInfo(  void  *  pModuleInfoParam,  void  *  p2  )
{
	 int				iRet		 =	-1;
	 QY_MODULE_INFO	*	pModuleInfo  =  (  QY_MODULE_INFO  *  )pModuleInfoParam;
	 char			*	moduleName		=	CONST_qyModuleName_nms;

	 if  (  !pModuleInfo  )  return  -1;

	 //  setDebugLogFileModuleName(  );
	 setErrHintWndCls(  CONST_qnmStatusToolWndClass  );

	 _sntprintf(  pModuleInfo->name,  mycountof(  pModuleInfo->name  ),  _T(  "%s"  ),  CString(  moduleName  )  );
	 if  (  !lstrcmpi(  pModuleInfo->callerId,  CString(  CONST_qyModuleName_resp  )  )  )  pModuleInfo->pProcTable  =  moduleForRespProcTable;
	 else  pModuleInfo->pProcTable  =  moduleForDaemonProcTable;

	 iRet  =  0;

//  errLabel:

	 traceLogA(  "%s: qyGetModuleInfo returns %s",  moduleName,  iRet  ?  "失败"  :  "成功"  );

	 return  iRet;
}

