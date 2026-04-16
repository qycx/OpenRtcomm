
#include	"stdafx.h"

#include	<windows.h>
#include	<stdio.h>
#include	<string.h>
#include	<lmcons.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmPcComm.h"			//  2006/12/18
#include	"qyTCharCommProc.h"
#include	"fileFunc_open.h"

//
#if  0
 extern  "C"  BOOL  iibDir(  char  *  dir  )
{
	 DWORD  dwFileAttributes  =  0;
	 TCHAR	tBuf[1024];

	 myStr2TChar(  dir,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
 	 if  (  (  dwFileAttributes  =  GetFileAttributes(  tBuf  )  )  !=  -1
		&&  (  dwFileAttributes  &  FILE_ATTRIBUTE_DIRECTORY  )  )
	{
		return  TRUE;
	}
	 return  FALSE;
}
#endif

#if 0
 extern  "C"  BOOL  iibDir(  LPCTSTR  dir  )
{
	 DWORD  dwFileAttributes  =  0;
	 
	 if  (  (  dwFileAttributes  =  GetFileAttributes(  dir  )  )  !=  -1
		&&  (  dwFileAttributes  &  FILE_ATTRIBUTE_DIRECTORY  )  )
	{
		return  TRUE;
	}
	 return  FALSE;
}
#endif



 extern  "C"  int  qwmEnumUsrRootDir(  QY_ENV  *  pEnv,  LPCTSTR  usrsRootDir,  PF_commonHandler  pF,  void  *  p0,  void  *  p1  )
{	
	int							iErr		=		-1;
    TCHAR						scanName[PATHLEN];
    WIN32_FIND_DATA				FindData;
    HANDLE						fh			=		NULL;
	TCHAR				*		p			=		NULL;
	int							iRet		=		-1;
	TCHAR						tBuf[1024];

    /*
     * check to see if filename is a directory 
     */
	if  (  !bDir(  usrsRootDir  )  )  {
		//
		traceLogA(  (char*)  "not dir"  );  
		//
		goto  errLabel;
	}
        
    /*
     * Create the search pattern 
     */
    safeTcsnCpy(  usrsRootDir,  scanName,  mycountof(  scanName  )  );

    if  (  _tcschr(  _T(  "/\\"  ),  *(  scanName  +  lstrlen(  scanName  )  -  1  )  )  ==  NULL  )  p  =  (TCHAR*)_T(  "\\*"  );
    else  p  =  (TCHAR*)_T(  "*"  );
	if  (  tQyStrCat(  scanName,  p,  scanName,  mycountof(  scanName  )  )  )  goto  errLabel;

    /*
     * do the FindFirstFile call 
     */
    fh  =  FindFirstFile(  scanName,  &FindData  );
    if  (  fh  ==  INVALID_HANDLE_VALUE  )  goto  errLabel;
    
	do  {
		safeTcsnCpy(  FindData.cFileName,  scanName,  mycountof(  scanName  )  );
        tTrim(  scanName  );
	    //  traceLogA(  (char*)  "搜索到%s",  FindData.cFileName  );  
			
		if  (  pF  )  {
			iRet  =  pF(  p0,  p1,  scanName  );
			if  (  iRet  >  0  ||  iRet  ==  CONST_qyRet_quit  )  {
				//traceLogA(  (char*)  "得到停止枚举的返回值"  );  
				break;
			}
		}
		
	}  while  (  FindNextFile(  fh,  &FindData  )  ||  GetLastError() != ERROR_NO_MORE_FILES  );

	iErr  =  0;

errLabel:
	
	if  (  isHandleValid(  fh  )  )  FindClose(  fh  );
	 
	return  iErr;

}



 // extern  "C"  int  qwmEnumUsrDirT(  QY_ENV  *  pEnv,  LPCTSTR  usrDir,  PF_commonHandler  pF,  void  *  p0,  void  *  p1  )
 extern  "C"  int  qwmEnumUsrDir(  QY_ENV  *  pEnv,  LPCTSTR  usrDir,  PF_commonHandler  pF,  void  *  p0,  void  *  p1  )
{	
	int							iErr		=		-1;
    TCHAR						scanName[PATHLEN  +  1];
    WIN32_FIND_DATA				FindData;
    HANDLE						fh			=		NULL;
	TCHAR				*		p			=		NULL;
	//  TCHAR						tBuf[PATHLEN  +  1];

    /*
     * check to see if filename is a directory 
     */	
	if  (  !bDir(  usrDir  )  )  {
		//
		traceLogA(  (char*)  "not dir"  );  
		//
		goto  errLabel;
	}
        
    /*
     * Create the search pattern 
     */
	lstrcpyn(  scanName,  usrDir,  mycountof(  scanName  )  );

    if  (  _tcschr(  _T(  "/\\"  ),  *(  scanName  +  lstrlen(  scanName  )  -  1  )  )  ==  NULL  )  p  =  (TCHAR*)_T(  "\\*"  );
    else  p  =  (TCHAR*)_T(  "*"  );
	_sntprintf(  scanName,  mycountof(  scanName  ),  _T(  "%s%s"  ),  scanName,  p  );

    /*
     * do the FindFirstFile call 
     */
	//  myStr2TChar(  scanName,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
    fh  =  FindFirstFile(  scanName,  &FindData  );
    if  (  fh  ==  INVALID_HANDLE_VALUE  )  goto  errLabel;
    
	do  {
        //  trim(  FindData.cFileName  );
		//  traceLogA(  (char*)  "搜索到%s",  FindData.cFileName  );  
		
		if  (  pF  )  {
			int							tmpiRet		=		-1;
			tmpiRet  =  pF(  p0,  p1,  &FindData  );
#if  0
			if  (  iRet  >  0  ||  iRet  ==  CONST_qyRet_quit  )  {
				traceLogA(  (char*)  "得到停止枚举的返回值"  );  break;
			}
#endif
			if  (  tmpiRet  )  {
				iErr  =  tmpiRet;  goto  errLabel;
			}

		}
		
	}  while  (  FindNextFile(  fh,  &FindData  )  ||  GetLastError() != ERROR_NO_MORE_FILES  );

	iErr  =  0;

errLabel:
	
	if  (  isHandleValid(  fh  )  )  FindClose(  fh  );
	 
	return  iErr;

}


  extern  "C"  BOOL  bSkippedSubDir(  TCHAR  *  subDirName  )
{
	 if  (  !_tcsicmp(  subDirName,  _T(  "."  )  )  
		 ||  !_tcsicmp(  subDirName,  _T(  ".."  )  )  
		 	 ||  !_tcsicmp(  subDirName,  _T(  CONST_winUsr_allUsers  )  ) 
		 		 ||  !_tcsicmp(  subDirName,  _T(  CONST_winUsr_defaultUser  )  )
					 ||  !_tcsicmp(  subDirName,  _T(  CONST_winUsr_localService  )  )
						 ||  !_tcsicmp(  subDirName,  _T(  CONST_winUsr_networkService  )  )  )  
	 {
		 return  TRUE;
	 }
	 return  FALSE;
}



    //  2005/05/03修改
 extern  "C"  int  showQwmSvrStatus(  QY_ENV  *  pEnv,  char  *  servIp,  unsigned  short  usPort,  int  iServiceId,  char  *  ver,  void  *  pCommEncCtx,  SOCK_TIMEOUT  *  pTo,  unsigned  int  uiStatus,  void  *  pShowQwmSvrStatus  )
{
	 int								iErr				=		-1;
	 QY_SOCK							sock;
	 QY_COMM_SESSION					session;
	 BOOL								bSessionOpen		=		FALSE;
	 QY_COMM_RESP						tmpResp;
	 QNM_CMDPARAM_showQwmSvrStatus		cmdParam;
	 QWM_MACS_INFO						macsInfo;

	 traceLogA(  (char*)  "showQwmSvrStatus enters."  );

	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 memset(  &macsInfo,  0,  sizeof(  macsInfo  )  );
	 getQwmMacs(  pEnv,  &macsInfo  );
	 
	 if  (  qnmOpenSession(  servIp,  usPort,  &macsInfo,  0,  iServiceId,  ver,  pCommEncCtx,  &session,  &sock,  pTo,  NULL,  NULL  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.usLastRespCode_i  )  )  goto  errLabel;

	 memset(  &cmdParam,  0,  sizeof(  cmdParam  )  );
	 if  (  pShowQwmSvrStatus  )  memcpy(  &cmdParam,  pShowQwmSvrStatus,  sizeof(  cmdParam  )  );
	 cmdParam.uiQwmSvrStatus  =  (  unsigned  char  )uiStatus;
	 qyhtonShowQwmSvrStatus(  &cmdParam  );

	 if  (  qySendReq(  &session,  &sock,  pTo,  CONST_qyCmd_showQwmSvrStatus,  (  char  *  )&cmdParam,  sizeof(  cmdParam  )  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session,  &sock,  pTo,  &tmpResp,  NULL,  0  )  )  goto  errLabel;
	 	 
	 iErr  =  0;

errLabel:

	 if  (  bSessionOpen  )  qnmCloseSession(  &session,  &sock,  pTo  );

	 traceLogA(  (char*)  "showQwmSvrStatus leaves %s",  iErr  ?  "失败"  :  "成功"  );

	 return  iErr;
}


 //  2006/07/18, 尚未完成
 extern  "C"  int  enumReg(  QY_ENV  *  pEnv,  int  iRuleId,  HKEY  hRootKey,  LPCWSTR keyName,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  )
{
	 int					iErr					=	-1;
	 //  QY_W_MON			*	pQwm					=	(  QY_W_MON  *  )pCommonParam->p0;
	 //  QY_REG					reg;
	 //  DWORD					len;
	 DWORD					dwRtn, dwSubKeyLen;
	 unsigned  int			uiRegUsrIndex			=	0;
	 //  char					buf[1024];
	 //  DWORD					dwVal;
	 WCHAR					wSubKey[512]			=	L"";
	 unsigned  char			valueBuf[4096  +  1]	=	"";
	 DWORD					dwValueLenInBytes;
	 QY_PC_REGISTRYVAL		regVal;
	 int					tmpiRet					=	-1;
	 HKEY					hKey					=	NULL;
	 BOOL					bKeyOpen				=	FALSE;
	 DWORD					type;

	 traceLogA(  (char*)  "enumReg enters, keyName is [%S]",  keyName  );

	 if  (  ERROR_SUCCESS  !=  RegOpenKeyEx(  hRootKey,  keyName,  0,  KEY_QUERY_VALUE,  &hKey  )  )  goto  errLabel;
	 bKeyOpen  =  TRUE;

	 for  (  uiRegUsrIndex  =  0;  ;  uiRegUsrIndex  ++  )  {

		  memset(  &regVal,  0,  sizeof(  regVal  )  );
		  
		  regVal.iRuleId  =  iRuleId;
		  wSubKey[0]  =  0;
		  dwSubKeyLen  =  mycountof(  wSubKey  );
     	  dwRtn  =  RegEnumKeyEx(  hKey,  uiRegUsrIndex,  wSubKey,  &dwSubKeyLen,  NULL,  NULL,  NULL,  NULL  );
		  if  (  dwRtn  ==  ERROR_NO_MORE_ITEMS  )  break;	//  检查完毕，等待下一轮检查
		  if  (  dwRtn  ==  ERROR_MORE_DATA  )  {
			  regVal.ucbERROR_MORE_DATA  =  TRUE;
			  }
		  else  if  (  dwRtn  !=  ERROR_SUCCESS  )  break;

		  regVal.ucbKey  =  TRUE;
		  if  (  !regVal.ucbERROR_MORE_DATA  )  {
			  regVal.uiCfgNameLen  =  dwSubKeyLen;
			  safeWcsnCpy(  wSubKey,  regVal.wCfgName,  mycountof(  regVal.wCfgName  )  );
		  }
		  
		  /*
	 	  //  现在开始处理刚被枚举的用户
		  if  (  !usrInfo.szSubKey[0]  )  continue;		//  校验

	 	  //  下面取代理配置,	2003/09/14
	 	  memset(  &reg,  0,  sizeof(  reg  )  );
	 	  reg.hKeyRoot0  =  HKEY_USERS;
	 	  lstrcpyn(  reg.rootKey,  usrInfo.szSubKey,  sizeof(  reg.rootKey  )  );
	 	  len  =  lstrlen(  reg.rootKey  );
	 	  lstrcpyn(  reg.rootKey  +  len,  "\\",  sizeof(  reg.rootKey  )  -  len  );
	 	  len  =  lstrlen(  reg.rootKey  );
	 	  lstrcpyn(  reg.rootKey  +  len,  CONST_qyRootKey_internetSettings,  sizeof(  reg.rootKey  )  -  len  );
	 	 
		  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_enableAutodial,  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
		  usrInfo.ucbEnableAutodial  =  (  unsigned  char  )dwVal;
		  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_noNetAutodial,  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
		  usrInfo.ucbNoNetAutodial  =  (  unsigned  char  )dwVal;
		  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_proxyEnable,  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
		  usrInfo.ucbProxyEnable  =  (  unsigned  char  )dwVal;
		  		
		  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_proxyServer,  usrInfo.proxyServer,  sizeof(  usrInfo.proxyServer  )  )  )  usrInfo.proxyServer[0]  =  0;
		  trim(  usrInfo.proxyServer  );
		  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_proxyOverride,  usrInfo.proxyOverride,  sizeof(  usrInfo.proxyOverride  )  )  )  usrInfo.proxyOverride[0]  =  0;
		  trim(  usrInfo.proxyOverride  );

		  //  下面取DefaultConnectionSettings
		  _snprintf(  reg.rootKey,  sizeof(  reg.rootKey  ),  "%s\\%s",  reg.rootKey,  CONST_qySubKey_connections  );
		  if  (  !qyGetRegCfgEx(  &reg,  CONST_regValName_defaultConnectionSettings,  buf,  sizeof(  buf  )  )  )  {
			  if  (  buf[8]  &  8  )  usrInfo.ucbAutoDetectSettings  =  TRUE;
		  }

	 
	 	  //  下面取用户名,  对NT, 除缺省外，统一为未知用户。
	 	  if  (  !lstrcmpi(  usrInfo.szSubKey,  ".Default"  )  )  lstrcpyn(  usrInfo.name,  "(缺省)",  sizeof(  usrInfo.name  )  );
	 	  else  {
			    if  (  iPlatformId  ==  PLATFORM_NT  )  {
			   		lstrcpyn(  usrInfo.name,  "(未知用户)",  sizeof(  usrInfo.name  )  );
					}
				else  {
					  lstrcpyn(  reg.rootKey,  usrInfo.szSubKey,  sizeof(  reg.rootKey  )  );
					  len  =  lstrlen(  reg.rootKey  );
					  lstrcpyn(  reg.rootKey  +  len,  "\\",  sizeof(  reg.rootKey  )  -  len  );
					  len  =  lstrlen(  reg.rootKey  );
					  lstrcpyn(  reg.rootKey  +  len,  CONST_qyRootKey_explorer,  sizeof(  reg.rootKey  )  -  len  );
					  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_logonUsrName,  usrInfo.name,  sizeof(  usrInfo.name  )  )  )  
						  usrInfo.name[0]  =  0;
				}
		  }
	 
		  //  traceLogA(  (char*)  "detectProxyServer检查到subKey is [%s], usrName is [%s], proxyServer is [%s], index is %d",  usrInfo.szSubKey,  usrInfo.name,  usrInfo.proxyServer,  uiRegUsrIndex  );
		  #ifdef	__DEBUG__
					printQwmUsrInfo(  &usrInfo  );
		  #endif
		  */

		  /*
		  //  这里要过滤到没用的键值  
		  trim(  usrInfo.szSubKey  );  trim(  usrInfo.name  );
		  if  (  !lstrcmpi(  usrInfo.szSubKey,  CONST_subKey_defaultUsr  )  )  continue;
		  if  (  !usrInfo.name[0]  )  continue;

		  if  (  tmpHandler_sndPcNetworkProp(  p0,  NULL,  &usrInfo  )  )  goto  errLabel;
		  */
		  if  (  pf  &&  (  tmpiRet  =  pf(  p0,  p1,  &regVal  )  )  )  {
			  iErr  =  tmpiRet;  goto  errLabel;
		  }

	 }


	 for  (  uiRegUsrIndex  =  0;  ;  uiRegUsrIndex  ++  )  {
		 
		  unsigned  char  ucbERROR_MORE_DATA_valueName	=	FALSE;
		  
		  memset(  &regVal,  0,  sizeof(  regVal  )  );
		  
		  regVal.iRuleId  =  iRuleId;
		  //
		  wSubKey[0]  =  0;
		  dwSubKeyLen  =  mycountof(  wSubKey  );
		  valueBuf[0]  =  0;
		  dwValueLenInBytes   =  sizeof(  valueBuf  );
     	  dwRtn  =  RegEnumValue(  hKey,  uiRegUsrIndex,  wSubKey,  &dwSubKeyLen,  0,  &type,  (  unsigned  char  *  )valueBuf,  &dwValueLenInBytes  );
		  if  (  dwRtn  ==  ERROR_NO_MORE_ITEMS  )  break;	//  检查完毕，等待下一轮检查
		  if  (  dwRtn  ==  ERROR_MORE_DATA  )  {
			  regVal.ucbERROR_MORE_DATA  =  TRUE;
			  //  下面再尝试读取名称，看是否是值超长了
			  DWORD  tmpdwRtn  =  0;		
			  //
			  wSubKey[0]  =  0;
		 	  dwSubKeyLen  =  mycountof(  wSubKey  );
			  dwValueLenInBytes  =  0;
			  tmpdwRtn  =  RegEnumValue(  hKey,  uiRegUsrIndex,  wSubKey,  &dwSubKeyLen,  0,  &type,  0,  &dwValueLenInBytes  );
			  if  (  tmpdwRtn  !=  ERROR_SUCCESS  )  ucbERROR_MORE_DATA_valueName  =  TRUE;

			  }
		  else  if  (  dwRtn  !=  ERROR_SUCCESS  )  break;

		  regVal.ucbKey  =  FALSE;
		  if  (  !ucbERROR_MORE_DATA_valueName  )  {
		  	  regVal.uiCfgNameLen  =  dwSubKeyLen;
	 	  	  safeWcsnCpy(  wSubKey,  regVal.wCfgName,  mycountof(  regVal.wCfgName  )  );
		  	  regVal.iValType  =  type;
		  	  regVal.uiValLenInBytes  =  dwValueLenInBytes;
			  if  (  !regVal.ucbERROR_MORE_DATA  )  {		//  这里才表明value的数据是读出来的
			  	  if  (  type  ==  REG_SZ  ||  type  ==  REG_MULTI_SZ  ||  type  ==  REG_EXPAND_SZ   )  {
					  if  (  dwValueLenInBytes  <  2  )  (  (  WCHAR  *  )valueBuf  )[0]	=	0;
					  else  (  (  WCHAR  *  )valueBuf  )[dwValueLenInBytes  /  2  -  1] = 0;
					  safeWcsnCpy(  (  WCHAR  *  )valueBuf,  regVal.u.wCfgVal,  mycountof(  regVal.u.wCfgVal  )  );
					}
				  else  if  (  type  ==  REG_DWORD  ||  type  ==  REG_DWORD_BIG_ENDIAN  )  {
					        regVal.u.iCfgVal  =  *(  DWORD  *  )valueBuf;
				  }
			  }
		  }
		  
		  if  (  pf  &&  (  tmpiRet  =  pf(  p0,  p1,  &regVal  )  )  )  {
			  iErr  =  tmpiRet;  goto  errLabel;
		  }

	 }


	 iErr  =  0;

errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );

	 traceLogA(  (char*)  "enumReg leaves"  );

	 return  iErr;
}


