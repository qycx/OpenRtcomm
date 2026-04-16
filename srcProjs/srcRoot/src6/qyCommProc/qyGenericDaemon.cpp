
#include	"stdafx.h"

#include	<stdlib.h>
#include	<memory.h>

//
#define  __noDbg_new__


//
#include	<afxwin.h>         // MFC core and standard components
#include	<afxext.h>         // MFC extensions
#include	<afxcview.h>
#include	<afxdisp.h>        // MFC Automation classes
#include	<afxdb.h>

#include	"qyCommonEx.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"

#include	"qyCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qyLangCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmCommProc1.h"
#include	"qyDaemonPublic.h"
#include	<tchar.h>

CQyGenericDaemon::CQyGenericDaemon( )
{
	memset(  &this->var,  0, sizeof(  this->var  )  );
}


CQyGenericDaemon::~CQyGenericDaemon( )
{
}

 char  *  CQyGenericDaemon::getRootKey(  )
{
	 return  (  char  *  )var.cfg.rootKey;
}

 TCHAR  *  CQyGenericDaemon::getAppDataDir(  )
{
	 return  var.cfg.appDataDir;
}

 TCHAR  *  CQyGenericDaemon::getWorkDir(  )
{
	return  var.cfg.workDir;
}


 TCHAR  *  CQyGenericDaemon::getInstallDir(  )
 {
	 return  var.cfg.installDir;
 }

 /*
 char  *  CQyGenericDaemon::getVer(  )
{
	return  (  char  *  )var.cfg.ver;
}
*/


 void  *  CQyGenericDaemon::getModules(  )
{
	 return  &var.modules;
}



 int  CQyGenericDaemon::getInitialCfg(  )
{	 
	 int	iErr							=	-1;
	 BOOL	bRet							=	FALSE;

	 if  (  !var.cfg.rootKey[0]  )  {
		 traceLogA(  "CQyGenericDaemon( \"%s\" )::getInitialCfg(  ) --- rootKey is not supplied,  will quit.",  var.cfg.daemonName  );
		 goto  errLabel;
	 }
	 if  (  qyGetRegCfgT(  HKEY_LOCAL_MACHINE,  CString(  var.cfg.rootKey  ),  _T(  QY_INSTALLDIR_VALNAME  ),  (  char  *  )var.cfg.installDir,  sizeof(  var.cfg.installDir  ),  0  )  )  {
		 traceLogA(  "CQyGenericDaemon( \"%s\" )::getInitialCfg(  ) ---  getting installDir failed.",  var.cfg.daemonName  );
		 goto  errLabel;
	 }
	 if  (  tTrailDir(  var.cfg.installDir,  mycountof(  var.cfg.installDir  )  )  )  goto  errLabel;

	 //  2007/06/13
	 _sntprintf(  var.cfg.appDataDir,  mycountof(  var.cfg.appDataDir  ),  _T(  "%s"  ),  var.cfg.installDir  );

	 if  (  tQyStrCat(  var.cfg.appDataDir,  _T(  QY_WORKSUBDIRNAME  ),  var.cfg.workDir,  mycountof(  var.cfg.workDir  )  )  )  {
		 goto errLabel;
	 }

	 bRet = CreateDirectory(  CString(  var.cfg.workDir  ).GetBuffer(  0  ), NULL );
	 if ( !bRet && GetLastError( ) != ERROR_ALREADY_EXISTS ) {
		 qyDisplayLastError( "Creating workDir" );
		 goto errLabel;
	 }
	 
	 iErr  =  0;

errLabel:

	 return  iErr;

}

 void  CQyGenericDaemon::clearRestartFlg(  )
{
	 qyDelRegCfg(  CString(  var.cfg.rootKey  ),  _T(  CONST_regValName_restart  )  );
}

 int  CQyGenericDaemon::refreshCfg(  )
{
	 int   iErr  =  -1;
	 TCHAR  buf[255];

	 if  (  !qyGetRegCfg(  CString(  var.cfg.rootKey  ), _T(  QY_QUIT_VALNAME  ), (  char  *  )buf, sizeof( buf ) ) ) {
			if ( _ttol( buf ) == CONST_QYQUITVAL ) {
				 startToQuit(  );
				iErr  =  0;
				goto  errLabel;
			}
	 }
	 if  (  !qyGetRegCfg(  CString(  var.cfg.rootKey  ), _T(  QY_STOP_VALNAME  ), (  char  *  )buf, sizeof( buf ) ) ) {
			if ( _ttol( buf ) == CONST_QYSTOPVAL ) {
				startToStop(  );
				iErr  =  0;
				goto  errLabel;
			}
	 }
	 if  (  !qyGetRegCfg(  CString(  var.cfg.rootKey  ), _T(  CONST_regValName_restart  ), (  char  *  )buf, sizeof( buf ) ) ) {
			if ( _ttol( buf ) == CONST_qyRestartVal ) {
				startToRestart(  );
				iErr  =  0;
				goto  errLabel;
			}
	 }


	 iErr  =  0;

errLabel:

	 return  iErr;

}

 //  通常是被调用的函数或线程或重要的操作未实现而导致此函数被调用
 void  CQyGenericDaemon::notifyPanic(  LPCTSTR  hint  )
{
	if  (  !hint  )  hint  =  _T(  ""  );

	 var.cfg.bPanic  =  TRUE;

	 //
	 showInfo_open0(  0,  hint,  _T(  " notifiPanic"  )  );

	 //
	 return;
}

 int  CQyGenericDaemon::preInit(  QY_ENV  *  pEnv,  char  *  rootKey,  unsigned  int  nInterval,  char  *  daemonName  )
{
	 int  iErr  =  -1;

	 var.pEnv  =  pEnv;
	 if  (  safeStrCpy(  rootKey,  var.cfg.rootKey,  sizeof(  var.cfg.rootKey  )  )  )  goto  errLabel;
	 var.cfg.nInterval  =  nInterval;
	 safeStrnCpy(  daemonName,  var.cfg.daemonName,  sizeof(  var.cfg.daemonName  )  );
	 
	 iErr  =  0;

errLabel:

	 return  iErr;

}

 int  CQyGenericDaemon::preInit(  QY_ENV  *  pEnv,  char  *  rootKey  )
{
	 int  iErr  =  -1;

	 var.pEnv  =  pEnv;
	 if  (  safeStrCpy(  rootKey,  var.cfg.rootKey,  sizeof(  var.cfg.rootKey  )  )  )  goto  errLabel;
	 var.cfg.nInterval  =  3000;
	 
	 iErr  =  0;

errLabel:

	 return  iErr;

}


 BOOL  CQyGenericDaemon::bSetStrProperty(  int  propertyId,  LPCTSTR  val  )
{
	 BOOL  bRet  =  FALSE;

	 switch  (  propertyId  )  {
			 case  CONST_qyPropertyId_installDir:
				   //  if  (  safeStrCpy(  val,  (  char  *  )var.cfg.installDir,  sizeof(  var.cfg.installDir  )  )  )  goto  errLabel;
				   lstrcpyn(  var.cfg.installDir,  val,  mycountof(  var.cfg.installDir  )  );		//  2007/03/05
				   break;
			 case  CONST_qyPropertyId_lckFileName:
				   //  if  (  safeStrCpy(  val,  var.cfg.lckFileName,  sizeof(  var.cfg.lckFileName  )  )  )  goto  errLabel;
				   lstrcpyn(  var.cfg.lckFileName,  val,  mycountof(  var.cfg.lckFileName  )  );	//  2007/03/05
				   break;
			 case  CONST_qyPropertyId_moduleIdName:
				   //  if  (  safeStrCpy(  val,  var.cfg.moduleIdName,  sizeof(  var.cfg.moduleIdName  )  )  )  goto  errLabel;
				   lstrcpyn(  var.cfg.moduleIdName,  val,  mycountof(  var.cfg.moduleIdName  )  );	//  2007/03/05
				   break;
			 default:
					goto  errLabel;
	 }
	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}

 TCHAR  *  CQyGenericDaemon::getStrPtrProperty(  int  propertyId  )
{
	 TCHAR  *  pRet  =  NULL;

	 switch  (  propertyId  )  {
			 case  CONST_qyPropertyId_installDir:		pRet  =  var.cfg.installDir;				break;
			 case  CONST_qyPropertyId_lckFileName:		pRet  =  var.cfg.lckFileName;				break;
			 default:									goto  errLabel;					
	 }
				   
errLabel:

	 return  pRet;

}

 BOOL  CQyGenericDaemon::bSetLongProperty(  int  propertyId,  long  val  )
{
	 BOOL  bRet  =  FALSE;

	 switch  (  propertyId  )  {
			 case  CONST_qyPropertyId_null:
			 default:
					goto  errLabel;
	 }
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


 BOOL  CQyGenericDaemon::bGetLongProperty(  int  propertyId,  long  *  plVal  )
{
	 BOOL  bRet  =  FALSE;

	 switch  (  propertyId  )  {
			 case	CONST_qyPropertyId_nInterval:
					*plVal  =  var.cfg.nInterval;
					break;
			 default:
					goto  errLabel;
					
	 }
	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}


 long  CQyGenericDaemon::unused_getLongProperty(  int  propertyId,  BOOL  *  pbFailed  )
{
	 BOOL	bRet  =  FALSE;
	 long	lVal	=	0;

	 switch  (  propertyId  )  {
			 case	CONST_qyPropertyId_nInterval:
					lVal  =  var.cfg.nInterval;
					break;
			 default:
					goto  errLabel;
					
	 }
	 
	 bRet  =  TRUE;

errLabel:

	 if  (  pbFailed  )  *pbFailed  =  bRet  ?  FALSE  :  TRUE;
	 return  bRet  ?  lVal  :  CONST_qyRet_err;

}


 BOOL  CQyGenericDaemon::bSetPtrProperty(  int  propertyId,  void  *  ptr  )
{
	 BOOL  bRet  =  FALSE;

	 switch  (  propertyId  )  {
			 case  CONST_qyPropertyId_licenseCtx:	var.pLicenseCtx	=  ptr;	break;
			 case  CONST_qyPropertyId_logCtx:		var.pLogCtx		=  ptr;	break;
			 default:								goto  errLabel;
	 }
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}

 //  2007/03/12
 void  *  CQyGenericDaemon::getPtrProperty(  int  propertyId  )
{
	 void  *  ptr  =  NULL;

	 switch  (  propertyId  )  {
			 case  CONST_qyPropertyId_licenseCtx:	ptr  =  var.pLicenseCtx;break;
			 case  CONST_qyPropertyId_logCtx:		ptr  =  var.pLogCtx;	break;
			 case  CONST_qyPropertyId_env:			ptr  =  var.pEnv;	break;		//  2007/01/21
			 default:								goto  errLabel;
	 }
errLabel:
	 return  ptr;
}


 //  2007/03/12
 BOOL  CQyGenericDaemon::bSetSpecialProperty(  int  propertyId,  void  *  pVal,  void  *  p0,  void  *  p1  )
{
	 BOOL	bRet  =  FALSE;
	 int	i;

	 switch  (  propertyId  )  {
			 case  CONST_qyPropertyId_serviceCfg:  {
				   QY_SERVICE_CFG	*	pServiceCfg  =  (  QY_SERVICE_CFG  *  )pVal;
				   //
				   if  (  !pServiceCfg  ||  !pServiceCfg->iServiceId  )  goto  errLabel;
				   if  (  getSpecialPtrProperty(  propertyId,  (  void  *  )pServiceCfg->iServiceId,  0  )  )  goto  errLabel;	//  已经设过了
				   // 
				   for  (  i  =  0;  i  <  mycountof(  var.serviceInfos  );  i  ++  )  {
					    if  (  !var.serviceInfos[i].cfg.iServiceId  )  break;
				   }
				   if  (  i  ==  mycountof(  var.serviceInfos  )  )  {
					   traceLogA(  "serivce已经满了"  );  goto  errLabel;				
				   }
				   //
				   memcpy(  &var.serviceInfos[i].cfg,  pServiceCfg,  sizeof(  var.serviceInfos[i].cfg  )  );
				   //
					}
				   break;
			 default:
					 goto  errLabel;
	 }
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}

 void  *  CQyGenericDaemon::getSpecialPtrProperty(  int  propertyId,  void  *  p0,  void  *  p1  )
{
	 void		*	ptr  =  NULL;
	 int			i;

	 switch  (  propertyId  )  {
		     case  CONST_qyPropertyId_serviceInfo_byServiceId:  {
				   int  iServiceId  =  (  int  )p0;
				   //
				   if  (  !iServiceId  )  goto  errLabel;
				   for  (  i  =  0;  i  <  mycountof(  var.serviceInfos  );  i  ++  )  {
					    if  (  var.serviceInfos[i].cfg.iServiceId  ==  iServiceId  )  {
							ptr  =  &var.serviceInfos[i];
							break;
						}
				   }
					}
				   break;
			 case  CONST_qyPropertyId_serviceInfo_byIndex:  {
				   int	index  =  (  int  )p0;
				   //
				   if  (  index  <  0  ||  index  >=  mycountof(  var.serviceInfos  )  )  goto  errLabel;
				   ptr  =  &var.serviceInfos[index];
					}
				   break;
			 case  CONST_qyPropertyId_serviceCfg:  {
				   QY_SERVICE_INFO  *  pInfo  =  (  QY_SERVICE_INFO  *  )getSpecialPtrProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  p0,  p1  );
				   if  (  !pInfo  )  goto  errLabel;
				   ptr  =  &pInfo->cfg;
					}
				   break;
			 case  CONST_qyPropertyId_mtSock:  {
				   QY_SERVICE_INFO  *  pInfo  =  (  QY_SERVICE_INFO  *  )getSpecialPtrProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  p0,  p1  );
				   if  (  !pInfo  )  goto  errLabel;
				   ptr  =  pInfo->pMtSock;				
					}
				   break;
			 default:
					goto  errLabel;
					
	 }
errLabel:
	 return  ptr;
}

 int  CQyGenericDaemon::init(  )
{
	 int			iErr		=	-1;
	 CFile		*	pLckFile	=	NULL;
	 CString		lckCStr;
	 
	 if  (  var.status.bInited  )  return  0;
	 
	 if  (  var.cfg.lckFileName[0]  )  {
		 pLckFile	=	new  CFile(  );
		 if  (  !pLckFile  )  goto  errLabel;
		 lckCStr = CString(  getWorkDir(  )  ) + var.cfg.lckFileName;
		 if  (  !pLckFile->Open(  lckCStr,  CFile::modeCreate | CFile::shareExclusive  )  )  {
			 traceLogA(  "CQyGenericDaemon::init: lockFile %S failed",  lckCStr  );
			 goto  errLabel;
		 }
	 }

	 traceLogA(  "2007/03/12"  );
	 /*  
	 if  (  var.cfg.ucbAutoOpenDb  &&  var.cfg.connectStr[0]  )  {
		 TRY  {
			 pDb  =  new  CDatabase;
			 if  (  !pDb  )  goto  errLabel;

			 if  (  !pDb->OpenEx(  CString(  var.cfg.connectStr  ).GetBuffer(  0  ),  CONST_qyDbOpenOptions  )  )  {
				 traceLogA(  "db.OpenEx( %s ) failed.",  var.cfg.connectStr  );
				 goto errLabel;
			 }		
			 }
		 CATCH  ( CDBException,  e  )  {		
				traceLogA(  "db.Open( ) failed: [%s]",  e->m_strError  );
				goto  errLabel;
			 }
		 END_CATCH
	 
	 }
	 */

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 if  (  pLckFile  )  delete  pLckFile;
	 }

	 if  (  !iErr  )  {
		 if  (  pLckFile  )  var.pLckFile  =  pLckFile;
		 var.status.bInited  =  TRUE;
	 }

	 return  iErr;

}

 //
int  CQyGenericDaemon::start(  )
{
	return  0;
}
	
int  CQyGenericDaemon::stop(  )
{
	return  0;
}

 //
 void  CQyGenericDaemon::exit(  )
{
	 clearRestartFlg(  );

	 if  (  !var.status.bInited  )  return;


	 if  (  var.pLckFile  )  {
		 CFile  *  pLckFile  =  (  CFile  *  )var.pLckFile;
		 delete  pLckFile;
		 var.pLckFile  =  NULL;
	 }


}


 //  检测是否需要退出
 BOOL  CQyGenericDaemon::bQuit(  )
{
	 return  this->var.cfg.bPanic  ||  this->var.cfg.bQuit  ||  this->var.cfg.bRestart;
}


 void  CQyGenericDaemon::startToQuit(  )
{
	 this->var.cfg.bQuit  =  TRUE;
	 return;
}


 BOOL  CQyGenericDaemon::bStop(  )
{
	 return  this->var.cfg.bStop;
}


 void  CQyGenericDaemon::startToStop(  )
{
	 this->var.cfg.bStop  =  TRUE;
	 return;
}


 BOOL  CQyGenericDaemon::bRestart(  )
{
	 return  this->var.cfg.bRestart;
}

 void  CQyGenericDaemon::startToRestart(  )
{
	 this->var.cfg.bRestart  =  TRUE;
}
 
 int  CQyGenericDaemon::runAsApp(  )
{
	 int					iErr					=  -1;
	 BOOL					bGenericDaemonInited	=  FALSE;
	 BOOL					bInited					=  FALSE;
	 unsigned  int			ui;
	 BOOL					bModulesInited			=  FALSE;
	 QY_ENV				*	pEnv					=  (  QY_ENV  *  )this->getPtrProperty(  CONST_qyPropertyId_env  );

	 if  (  CQyGenericDaemon::getInitialCfg(  )  )  goto  errLabel;
	 if  (  getInitialCfg(  )  )  goto  errLabel;
	 //  qyLoadAllModules(  );		//  注意这里装载模块
	 //  if  (  qyLoadAllModules(  pEnv,  var.cfg.sysRootKey,  var.cfg.moduleIdName,  var.cfg.installDir,  var.pLicenseCtx,  &var.modules  )  )  goto  errLabel;
	 for  (  ui  =  0;  ui  <  mycountof(  var.serviceInfos  );  ui  ++  )  {
		  QY_SERVICE_INFO  *  pServiceInfo  =  &var.serviceInfos[ui];
		  if  (  !pServiceInfo->cfg.iServiceId  )  continue;
		  //
		  if  (  qyLoadAllModules(  pEnv,  CString(  pServiceInfo->cfg.sysRootKey  ),  var.cfg.moduleIdName,  var.cfg.installDir,  var.pLicenseCtx,  &var.modules  )  )  goto  errLabel;
	 }
	 for  (  ui  =  0;  ui  <  var.modules.uiCnt;  ui  ++  )  {
		  if  (  var.modules.mems[ui].pfGetInitialCfg  &&  var.modules.mems[ui].pfGetInitialCfg(  var.modules.mems[ui].p1,  var.modules.mems[ui].p2  )  )  {
			  //
			  TCHAR tBuf[128];
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "CQyGenericDaemon::runAsApp failed, module.pfGetInitialCfg failed"  )  );
			  showInfo_open0(  0,  _T(""),  tBuf  );
			  //
			  goto  errLabel;
		  }
	 }

	 if  (  CQyGenericDaemon::init(  )  )  goto  errLabel;
	 bGenericDaemonInited  =  TRUE;
	 if  (  init(  )  )  goto  errLabel;
	 bInited  =  TRUE;
	 for  (  ui  =  0;  ui  <  var.modules.uiCnt;  ui  ++  )  {
		  if  (  var.modules.mems[ui].pfInit  &&  var.modules.mems[ui].pfInit(  var.modules.mems[ui].p1,  var.modules.mems[ui].p2  )  )  goto  errLabel;
	 }
	 bModulesInited  =  TRUE;

	 //
	 if  (  start(  )  )  {
		 goto  errLabel;
	 }

	 //
	 if  (  bUseGui(  )  )  {
		 gui_run(  );
		 }
	 else  {

		   for  (  ;  ;  )  {

				#if  0
					if  (  CQyGenericDaemon::refreshCfg(  )  )  goto  errLabel;
				    if  (  refreshCfg(  )  )	goto  errLabel;
					for  (  ui  =  0;  ui  <  var.modules.uiCnt;  ui  ++  )  {
						 if  (  var.modules.mems[ui].pfRefreshCfg  &&  var.modules.mems[ui].pfRefreshCfg(  var.modules.mems[ui].p1,  var.modules.mems[ui].p2  )  )  goto  errLabel;
					}
				#endif
				//  2015/06/27
				if  (  refreshCfg_app(  )  )  goto  errLabel;

				//
				if  (  this->bQuit(  )  )  break;
		  
				Sleep(  this->var.cfg.nInterval  );

				continue;			
		   }
	 }

	 iErr  =  0;

errLabel:

	 startToQuit(  );

	 //
	 stop(  );

	 //
	 if  (  bModulesInited  )  {
		  for  (  ui  =  0;  ui  <  var.modules.uiCnt;  ui  ++  )  {
			   if  (  var.modules.mems[ui].pfExit  &&  var.modules.mems[ui].pfExit(  var.modules.mems[ui].p1,  var.modules.mems[ui].p2  )  )  traceLogA(  "模块%s的pfExit failed",  var.modules.mems[ui].info.name  );
		  }
	 }
	 if  (  bInited  )  exit(  );
	 if  (  bGenericDaemonInited  )	 CQyGenericDaemon::exit(  );	//  重启标志在exit(  )中清除

	 qyUnloadAllModules(  pEnv,  &var.modules  );

	 return  iErr;

}


 //  2015/06/27
 int  CQyGenericDaemon::refreshCfg_app(  )
 {
	 int  iErr  =  -1;	 	 
	 unsigned  int			ui;
	
	 if  (  CQyGenericDaemon::refreshCfg(  )  )  goto  errLabel;
	 if  (  refreshCfg(  )  )	goto  errLabel;
	 for  (  ui  =  0;  ui  <  var.modules.uiCnt;  ui  ++  )  {	
		  if  (  var.modules.mems[ui].pfRefreshCfg  &&  var.modules.mems[ui].pfRefreshCfg(  var.modules.mems[ui].p1,  var.modules.mems[ui].p2  )  )  goto  errLabel;		  
	 }

	 iErr  =  0;

errLabel:
	
	 return  iErr;

 }



 BOOL  CQyGenericDaemon::bUseGui(  )
 {
	 return  FALSE;
 }


 int  CQyGenericDaemon::gui_run(  )
{
	return  -1;
}