

#include	"qySvrMgrModule.h"

 CQnmSvrMgrModuleDaemon	gDaemon;

 #define		DEFAULT_qnmProcHhMmSs	"190000"  

 int  qyModuleGetInitialCfg(  QY_MODULE  *  pModule,  void  *  p2  )
{
	 int							iErr		=	-1;
	 pModule->p2								=	&gDaemon;
	 CQnmSvrMgrModuleDaemon		*	pDaemon		=	(  CQnmSvrMgrModuleDaemon  *  )pModule->p2;

	 pDaemon->var.logCtx.ucbLogOn  =  TRUE;
	 _snprintf(  pDaemon->var.logCtx.filePart,  sizeof(  pDaemon->var.logCtx.filePart  ),  "%s.log",  pModule->info.name  );
	 _snprintf(  pDaemon->var.logCtx.reg.rootKey,  sizeof(  pDaemon->var.logCtx.reg.rootKey  ),  "%s",  CONST_qyRootKey_qnmTemp  );
	 _snprintf(  pDaemon->var.logCtx.regValName,  sizeof(  pDaemon->var.logCtx.regValName  ),  "%s : %s",  pModule->info.callerId,  pModule->info.name  );

	 traceInfo(  &pDaemon->var.logCtx,  "qyModuleGetInitialCfg enters"  );

	 if  (  !pDaemon->bSetPtrProperty(  CONST_qyPropertyId_logCtx,  &pDaemon->var.logCtx  )  )  goto  errLabel;

	 safeStrnCpy(  DEFAULT_qnmProcHhMmSs,  pDaemon->var.cfg.procHhMmSs,  sizeof(  pDaemon->var.cfg.procHhMmSs  )  );
	 wcsncpy(  pDaemon->var.cfg.showWho,  CONST_showWho_clearTempFile,  mycountof(  pDaemon->var.cfg.showWho  )  );

	 iErr  =  0;

errLabel:

	 traceInfo(  &pDaemon->var.logCtx,  "qyModuleGetInitialCfg leaves"  );

	 return  iErr;
}


 int  qyModuleInit(  QY_MODULE  *  pModule,  void  *  p2  )
{
	 int							iErr		=	-1;
	 CQnmSvrMgrModuleDaemon		*	pDaemon		=	(  CQnmSvrMgrModuleDaemon  *  )pModule->p2;
	 char						*	p			=	NULL;

	 GetWindowsDirectory(  pDaemon->var.documentsAndSettingsDir,  sizeof(  pDaemon->var.documentsAndSettingsDir  )  );
	 if  (  !(  p  =  strchr(  pDaemon->var.documentsAndSettingsDir,  ':'  )  )  )  goto  errLabel;
	 p[1]  =  '\0';
	 _snprintf(  pDaemon->var.documentsAndSettingsDir,  sizeof(  pDaemon->var.documentsAndSettingsDir  ),  "%s%s",  pDaemon->var.documentsAndSettingsDir,  "\\Documents and Settings\\"  );
	 traceInfo(  &pDaemon->var.logCtx,  "dir is %s",  pDaemon->var.documentsAndSettingsDir  );

	 pDaemon->var.status.ucbInited  =  TRUE;
	 iErr  =  0;  
errLabel:

	 return  iErr;
}

  int  myProcFile(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int						iErr		=	-1;
	 CQnmSvrMgrModuleDaemon	*	pDaemon		=	(  CQnmSvrMgrModuleDaemon  *  )p0;
	 char					*	pRootDir	=	(  char  *  )p1;		
	 char					*	pFileName	=	(  char  *  )p2;
	 CString					tmpFile;

	 if  (  pDaemon->bQuit(  )  )  {				//  系统总退出令
		 traceLogA(  "myProcFile: 得到退出令"  );  
		 iErr  =  CONST_qyRet_quit;				goto  errLabel;
	 }

	 if  (  bSkippedSubDir(  pFileName  )  )  {
		 iErr  =  0;  goto  errLabel;
	 }
	 tmpFile  =  CString(  ""  )  +  pRootDir  +  pFileName;

	 if  (  bDir(  tmpFile.GetBuffer(  0  )  )  )  {
		 iErr  =  0;  goto  errLabel;
	 }
	 qyShowInfo1(  CONST_qyShowType_qnmChking,  L"",  pDaemon->var.cfg.showWho,  L"",  L"",  L"%s",  tmpFile.GetBuffer(  0  )  );

	 traceLogA(  " 准备删除%s",  tmpFile.GetBuffer(  0  )  );
	
	 if  (  !::DeleteFile(  tmpFile.GetBuffer(  0  )  )  )  traceLogA(  "删除文件%s失败",  tmpFile.GetBuffer(  0  )  );

	 iErr  =  0;
errLabel:
	 return  iErr;
}

 int  myProcUsrDir(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int						iErr		=	-1;
	 CQnmSvrMgrModuleDaemon	*	pDaemon		=	(  CQnmSvrMgrModuleDaemon  *  )p0;
	 char					*	pRootDir	=	(  char  *  )p1;		
	 char					*	pFileName	=	(  char  *  )p2;
	 CString					tmpCStr;

	 if  (  pDaemon->bQuit(  )  )  {				//  系统总退出令
		 traceLogA(  "myProcUsrDir: 得到退出令"  );  
		 iErr  =  CONST_qyRet_quit;				goto  errLabel;
	 }

	 if  (  !pFileName  )  return  -1;
	 if  (  bSkippedSubDir(  pFileName  )  )  {
		 iErr  =  0;  goto  errLabel;
	 }

	 tmpCStr  =  CString(  ""  )  +  pRootDir  +  pFileName  +  "\\Local Settings\\Temp\\";

	 qwmEnumUsrRootDir(  &pDaemon->var.env,  tmpCStr.GetBuffer(  0  ),  myProcFile,  pDaemon,  tmpCStr.GetBuffer(  0  )  );    

	 iErr  =  0;
errLabel:
	 return  0;
}

 int  qyModuleRefreshCfg(  QY_MODULE  *  pModule,  void  *  p2  )
{
	 int						iErr		=	-1;
	 CQnmSvrMgrModuleDaemon	*	pDaemon		=	(  CQnmSvrMgrModuleDaemon  *  )pModule->p2;
	 time_t						curT		=	time(  NULL  );
	 struct  tm				*	pTm			=	localtime(  &curT  );
	 char						hhMmSs[CONST_qyTimeLen  +  1];

	 //  traceInfo(  &pDaemon->var.logCtx,  "qyModuleRefreshCfg enters"  );

	 if  (  pDaemon->var.status.ucbInited  )  {

	 	 //  traceInfo(  &pDaemon->var.logCtx,  "hour is %d, minute is %d, second is %d",  pTm->tm_hour,  pTm->tm_min,  pTm->tm_sec  );
	 	 _snprintf(  hhMmSs,  sizeof(  hhMmSs  ),  "%02d%02d%02d",  pTm->tm_hour,  pTm->tm_min,  pTm->tm_sec  );
	 	 if  (  !strnicmp(  pDaemon->var.cfg.procHhMmSs,  hhMmSs,  4  )  )  {
			 qyShowInfo1(  CONST_qyShowType_qnmChking,  L"",  pDaemon->var.cfg.showWho,  L"",  L"",  L"开始..."  );

			 qwmEnumUsrRootDir(  &pDaemon->var.env,  pDaemon->var.documentsAndSettingsDir,  myProcUsrDir,  pDaemon,  pDaemon->var.documentsAndSettingsDir  );    

			 qyShowInfo1(  CONST_qyShowType_qnmChking,  L"",  pDaemon->var.cfg.showWho,  L"",  L"",  L"结束"  );
		 }
	 }
	 
	 iErr  =  0;
//  errLabel:

	 //  traceInfo(  &pDaemon->var.logCtx,  "qyModuleRefreshCfg leaves"  );

	 return  iErr;
}


 int  qyModuleExit(  QY_MODULE  *  pModule,  void  *  p2  )
{
	 int							iErr		=	-1;
	 CQnmSvrMgrModuleDaemon		*	pDaemon		=	(  CQnmSvrMgrModuleDaemon  *  )pModule->p2;
	 char						*	p			=	NULL;

	 iErr  =  0;

	 return  iErr;
}


 QY_DMITEM  CONST_svrMgrProcTable[]  =
{
	{	0,	"qyModuleInit",					(  char  *  )qyModuleInit,	},
	{	1,	"qyModuleExit",					(  char  *  )qyModuleExit,	},
	{	2,	"qyModuleGetInitialCfg",		(  char  *  )qyModuleGetInitialCfg,		},
	{	3,	"qyModuleRefreshCfg",			(  char  *  )qyModuleRefreshCfg,		},
	{	-1,		NULL,		},
};


 extern  "C"  __declspec( dllexport )  int  qyGetModuleInfo(  void  *  pModuleInfoParam,  void  *  p2  )
{
	 int				iRet		 =	-1;
	 QY_MODULE_INFO	*	pModuleInfo  =  (  QY_MODULE_INFO  *  )pModuleInfoParam;
	 unsigned  char		ucbDogOk		=	TRUE;
	 char			*	moduleName		=	CONST_qyModuleName_nms;
	 QY_LICENSE_CTX	*	pLicenseCtx		=	NULL;

	 setDebugLogFileModuleName(  );
	 setErrHintWndCls(  CONST_qnmStatusToolWndClass  );

 	 if  (  !pModuleInfo  )  goto  errLabel;
	 pLicenseCtx  =  (  QY_LICENSE_CTX  *  )pModuleInfo->pLicenseCtx;
	 #ifndef  __WITHOUT_CHKDOG__
			  if  (  !pLicenseCtx  ||  !pLicenseCtx->bRnbDogInited  )  ucbDogOk  =  FALSE;
			  else  if  (  !bQyDogOk(  pLicenseCtx,  moduleName  )  )  {
				  		AfxMessageBox(  "netMc2: cannot find usb key"  );  ucbDogOk  =  FALSE;
			  }
	 #endif
	 if  (  !ucbDogOk  )  goto  errLabel;

	 _snprintf(  pModuleInfo->name,  sizeof(  pModuleInfo->name  ),  "%s",  moduleName  );
	 if  (  !strcmpi(  pModuleInfo->callerId,  CONST_qyModuleName_resp  )  )  pModuleInfo->pProcTable  =  CONST_svrMgrProcTable;
	 else  pModuleInfo->pProcTable  =  CONST_qyNullTable;

	 iRet  =  0;

errLabel:

	 traceLogA(  "%s: qyGetModuleInfo returns %s",  moduleName,  iRet  ?  "失败"  :  "成功"  );

	 return  iRet;
}

