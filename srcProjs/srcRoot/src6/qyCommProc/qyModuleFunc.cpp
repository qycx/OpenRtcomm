
#include	"stdafx.h"

#include	<windows.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyModuleFunc.h"
#include	<tchar.h>
#include	"qyCommProc.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qyTCharCommProc.h"


//  qyLoadModules可以连续调用，以方便从多个路径中装载模块

 extern  "C"  int  qyLoadModule(  QY_ENV  *  pEnv,  LPCTSTR  callerId,  LPCTSTR  path,  void  *  pLicenseCtx,  QY_MODULES  *  pModules  )
{
	 int			iErr		=	-1;
	 QY_MODULE		module;
	 QY_DMITEM	*	pProcTable	=	NULL;
	 QY_DMITEM	*	pItem		=	NULL;

	 //  搜寻dll并判断是否正确的模块
	 if  (  !path  ||  !pModules  )  goto  errLabel;

	 //  限制装载模块的数量
	 if  (  pModules->uiCnt  >=  sizeof(  pModules->mems  )  /  sizeof(  pModules->mems[0]  )  )  goto  errLabel;
	 
	 memset(  &module,  0,  sizeof(  module  )  );
	 if  (  !(  module.hModule  =  LoadLibrary(  path  )  )  )  goto  errLabel;
	 
	 if  (  !(  module.pfGetModuleInfo  =  (  PF_qyModuleProc  )myGetProcAddress(  module.hModule,  "qyGetModuleInfo"  )  )  )  goto  errLabel;
	 lstrcpyn(  module.info.callerId,  callerId,  sizeof(  module.info.callerId  )  );
	 module.info.pLicenseCtx   =  pLicenseCtx;
	 if  (  (  module.pfGetModuleInfo(  &module.info,  0  )  )  )  goto  errLabel;
	 if  (  module.info.pProcTable  )  {
		 pProcTable  =  (  QY_DMITEM  *  )module.info.pProcTable;
		 
		 if  (  (  pItem  =  qyGetDmItemByDes(  pProcTable,  _T(  "qyModuleInit"  ),  0  )  )  )  module.pfInit  =  (  PF_qyModuleProc  )pItem->pData;
	 	 if  (  (  pItem  =  qyGetDmItemByDes(  pProcTable,  _T(  "qyModuleExit"  ),  0  )  )  )  module.pfExit  =  (  PF_qyModuleProc  )pItem->pData;
	 	 if  (  (  pItem  =  qyGetDmItemByDes(  pProcTable,  _T(  "qyModuleGetInitialCfg"  ),  0  )  )  )  module.pfGetInitialCfg  =  (  PF_qyModuleProc  )pItem->pData;
	 	 if  (  (  pItem  =  qyGetDmItemByDes(  pProcTable,  _T(  "qyModuleRefreshCfg"  ),  0  )  )  )  module.pfRefreshCfg  =  (  PF_qyModuleProc  )pItem->pData;

	 }
	 /*
	 module.pfInit  =  (  PF_qyModuleProc  )GetProcAddress(  module.hModule,  "qyModuleInit"  );
	 module.pfExit  =  (  PF_qyModuleProc  )GetProcAddress(  module.hModule,  "qyModuleExit"  );
	 module.pfGetInitialCfg  =  (  PF_qyModuleProc  )GetProcAddress(  module.hModule,  "qyModuleGetInitialCfg"  );
	 module.pfRefreshCfg  =  (  PF_qyModuleProc  )GetProcAddress(  module.hModule,  "qyModuleRefreshCfg"  );

	 if  (  !module.pfInit  ||  !module.pfExit  )  goto  errLabel;
	 */
		 
	 //  将module加入pModules中
	 memcpy(  &pModules->mems[pModules->uiCnt],  &module,  sizeof(  module  )  );
	 pModules->mems[pModules->uiCnt].p1  =  &pModules->mems[pModules->uiCnt];
	 module.hModule  =  NULL;		//  module将清空

	 pModules->uiCnt  ++  ;

	 iErr  =  0;

errLabel:
	 
	 if  (  iErr  )  {
		 if  (  module.hModule  )  FreeLibrary(  module.hModule  );
	 }

	 return  iErr;

}


 /*
  extern  "C"  int  qyGetRegCfg1W(  HKEY  hKeyRoot0,  LPCWSTR  rootKey,  LPCWSTR  cfgName,  WCHAR  *  cfgVal,  int  size,  unsigned  int  *  puiType  )
{
	int		iRet		=	-1;
	BOOL	bKeyOpen	=	FALSE;
	HKEY	hKey;
	int		lRet		=	0;
	long	cb;
	DWORD	type;
			
	if  (  !rootKey  || !rootKey[0]  )  return  -1;
	if  (  !hKeyRoot0  )  hKeyRoot0  =  HKEY_LOCAL_MACHINE;

	lRet  =  RegOpenKey(  hKeyRoot0,  rootKey,  & hKey  );
	if  (  lRet  !=  ERROR_SUCCESS  )  {
		//  traceLogA(  "qyGetRegCfg(  ):  RegOpenKey( %s )  failed.",  rootKey  );
		goto  errLabel;
	}
	bKeyOpen  =  TRUE;
	
	cb  =  size;
	if  (  RegQueryValueEx(  hKey,  cfgName,  0,  & type,  (  unsigned  char  *  )cfgVal, 
			(  unsigned  long  *  ) & cb  )  !=  ERROR_SUCCESS  ) 
	{
		//  traceLogA(  "qyGetRegCfg(  ):  RegQueryValueEx( %s )  failed.",  cfgName  );
		goto errLabel;
	}
	//  2003/09/12加入了对类型的判断，仅对字符串作结尾
	if  (  type  ==  REG_SZ  ||  type  ==  REG_MULTI_SZ  ||  type  ==  REG_EXPAND_SZ   )  {
		if  (  cb  <  1  )  cfgVal[0]	=	0;
		else  cfgVal[cb - 1] = 0;
	}
	
	iRet  =  0;
	
errLabel:

	if ( bKeyOpen ) RegCloseKey( hKey );

	if  (  !iRet  )  {
		if  (  puiType  )  *  puiType  =  type;		//  2004/08/06加
	}

	return iRet;

}
*/

 extern  "C"  int  qyLoadModuleByKeyName(  QY_ENV  *  pEnv,  LPCTSTR  sysRootKey,  LPCTSTR  moduleIdName,  LPCTSTR  installDir,  void  *  pLicenseCtx,  LPCTSTR  moduleKeyName,  QY_MODULES  *  pModules  )
{
	 int					iErr										=	-1;
	 TCHAR					keyName[512]								=	_T(  ""  );
	 int					len;
	 TCHAR					moduleFileName[CONST_qyMaxPathLen  +  1]	=	_T(  ""  );
		 
	 lstrcpyn(  keyName,  sysRootKey,  mycountof(  keyName  )  );
	 if  (  tTrailDir(  keyName,  mycountof(  keyName  )  )  )  goto  errLabel;
	 lstrcpyn(  keyName  +  lstrlen(  keyName  ),  _T(  CONST_qyModulesSubKey  ),  mycountof(  keyName  )  -  lstrlen(  keyName  )  );
	 if  (  tTrailDir(  keyName,  mycountof(  keyName  )  )  )  goto  errLabel;
	 len  =  lstrlen(  keyName  );

	 lstrcpyn(  keyName  +  len,  moduleKeyName,  mycountof(  keyName  )  -  len  );
	 if  (  qyGetRegCfgT(  HKEY_LOCAL_MACHINE,  keyName,  _T(  CONST_regValName_installDir  ),  (  char  *  )moduleFileName,  sizeof(  moduleFileName  ),  0  )  )  moduleFileName[0]  =  0;
	 if  (  !moduleFileName[0]  )  goto  errLabel;
	 lstrcpyn(  moduleFileName,  installDir,  mycountof(  moduleFileName  )  );
	 if  (  tTrailDir(  moduleFileName,  mycountof(  moduleFileName  )  )  )  goto  errLabel;
	 lstrcpyn(  moduleFileName  +  lstrlen(  moduleFileName  ),  _T(  CONST_qyBinSubDir  ),  mycountof(  moduleFileName  )  -  lstrlen(  moduleFileName  )  );
	 if  (  qyGetRegCfgT(  HKEY_LOCAL_MACHINE,  keyName,  moduleIdName,  (  char  *  )(  moduleFileName  +  lstrlen(  moduleFileName  )  ),  (  mycountof(  moduleFileName  )  -  lstrlen(  moduleFileName  )  )  *  sizeof(  TCHAR  ),  0  )  )  goto  errLabel;
	 if  (  qyLoadModule(  pEnv,  moduleIdName,  moduleFileName,  pLicenseCtx,  pModules  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:
	
	 return  iErr;
}

 extern  "C"  int  qyLoadAllModules(  QY_ENV  *  pEnv,  LPCTSTR  sysRootKey,  LPCTSTR  moduleIdName,  LPCTSTR  installDir,  void  *  pLicenseCtx,  QY_MODULES  *  pModules  )
{
	 int					iErr					=	-1;
	 HKEY					hKey					=	NULL;
	 TCHAR					keyName[512]			=	_T(  ""  );
	 unsigned  char			ucbKeyOpen				=	FALSE;
	 FILETIME				ft;
	 DWORD					dwIndex					=	0;
	 TCHAR					moduleKeyName[512]		=	_T(  ""  );
	 DWORD					dwSize;
	 int					len;
	 TCHAR					moduleFileName[CONST_qyMaxPathLen  +  1]	=	_T(  ""  );

	 if  (  !sysRootKey  ||  !sysRootKey[0]  ||  !moduleIdName  ||  !moduleIdName[0]  ||  !installDir  )  return  0;
	 
	 lstrcpyn(  keyName,  sysRootKey,  mycountof(  keyName  )  );
	 if  (  tTrailDir(  keyName,  mycountof(  keyName  )  )  )  goto  errLabel;
	 lstrcpyn(  keyName  +  lstrlen(  keyName  ),  _T(  CONST_qyModulesSubKey  ),  mycountof(  keyName  )  -  lstrlen(  keyName  )  );
	 if  (  tTrailDir(  keyName,  mycountof(  keyName  )  )  )  goto  errLabel;
	 len  =  lstrlen(  keyName  );
	 
	 if  (  ERROR_SUCCESS  !=  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  keyName,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  goto  errLabel;
	 ucbKeyOpen  =  TRUE;

	 for  (  dwIndex  =  0;  ;  dwIndex  ++  )  {
		  dwSize  =  sizeof(  moduleKeyName  );
		  if  (  ERROR_SUCCESS  !=  RegEnumKeyEx(  hKey,  dwIndex,  moduleKeyName,  &dwSize,  NULL,  NULL,  NULL,  &ft  )  )  break;
		  traceLogA(  (char*)"moduleKeyName %S will be loaded",  moduleKeyName  );
		  lstrcpyn(  keyName  +  len,  moduleKeyName,  mycountof(  keyName  )  -  len  );
		  //  if  (  qyGetRegCfgT(  HKEY_LOCAL_MACHINE,  keyName,  _T(  CONST_regValName_installDir  ),  (  char  *  )moduleFileName,  sizeof(  moduleFileName  ),  0  )  )  moduleFileName[0]  =  0;
		  //  if  (  !moduleFileName[0]  )  continue;
		  lstrcpyn(  moduleFileName,  installDir,  mycountof(  moduleFileName  )  );
		  if  (  tTrailDir(  moduleFileName,  mycountof(  moduleFileName  )  )  )  continue;
		  lstrcpyn(  moduleFileName  +  lstrlen(  moduleFileName  ),  _T(  CONST_qyBinSubDir  ),  mycountof(  moduleFileName  )  -  lstrlen(  moduleFileName  )  );
		  if  (  qyGetRegCfgT(  HKEY_LOCAL_MACHINE,  keyName,  moduleIdName,  (  char  *  )(  moduleFileName  +  lstrlen(  moduleFileName  )  ),  (  mycountof(  moduleFileName  )  -  lstrlen(  moduleFileName  )  )  *  sizeof(  TCHAR  ),  0  )  )  continue;
		  qyLoadModule(  pEnv,  moduleIdName,  moduleFileName,  pLicenseCtx,  pModules  );
	 }	 

	 iErr  =  0;

errLabel:

	 if  (  ucbKeyOpen  )  RegCloseKey(  hKey  );

	 return  iErr;
}



 extern  "C"  void	qyUnloadAllModules(  QY_ENV  *  pEnv,  QY_MODULES  *  pModules  )
{
	 unsigned  int	i  =  0;

	 if  (  !pModules  )  return;

	 for  (  i  =  0;  i  <  pModules->uiCnt;  i  ++  )  {
		  FreeLibrary(  pModules->mems[i].hModule  );
	 }

	 memset(  pModules,  0,  sizeof(  QY_MODULES  )  );

	 return;

}


 extern  "C"  QY_MODULE  *	qyGetModuleByName(  QY_MODULES  *  pModules,  LPCTSTR  name  )
{
	 unsigned  int	i  =  0;

	 if  (  !pModules  ||  !name  )  return  NULL;

	 for  (  i  =  0;  i  <  pModules->uiCnt;  i  ++  )  {
		  if  (  !lstrcmpi(  pModules->mems[i].info.name,  name  )  )  break;
	 }
	 if  (  i  ==  pModules->uiCnt  )  return  NULL;
	 return  &pModules->mems[i];

}

 extern  "C"  PF_qyModuleProc  qyGetModuleProcByName(  QY_MODULE  *  pModule,  LPCTSTR  name  )
{
	 QY_DMITEM	*	pItem  =  NULL;
	 
	 if  (  !pModule  ||  !name  )  return  NULL;

	 if  (  !(  pItem  =  qyGetDmItemByDes(  (  QY_DMITEM  *  )pModule->info.pProcTable,  name,  0  )  )  )  return  NULL;
	 return  (  PF_qyModuleProc  )pItem->pData;
}


