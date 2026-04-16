
#include	"stdafx.h"

//  #include	<windows.h>
//  #include	<afxdb.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmCommProc1.h"
#include	"qnmCustom.h"
#include	"qyString.h"
#include	"qySqlFunc.h"
#include	"qyModuleFunc.h"
#include	"qyTCharCommProc.h"
#include	"qmCfg.h"
#include	"fileFunc_open.h"

//
int outputVerInfo(TCHAR* filePrefix)
{
	TCHAR  fileName[256];

	if (!filePrefix) return  -1;

	_sntprintf(fileName, mycountof(fileName), _T("d:\\qycx\\log\\%s.ver.%S"), filePrefix, qnmVerStr(CONST_qyServiceId_is));
	FILE* fp;
	fp = _tfopen(fileName, _T("a"));
	if (fp) {
		fclose(fp);
	}

	//
	return  0;
}

//
bool bGetQmInitCfg(TCHAR* smCfgFile, Qm_initCfg* pCfg)
{
	TCHAR  tBuf[128];
	char  buf[128];

	//
	TCHAR  *  cfgFileName =  smCfgFile;

	//
	if  (  !bFileExists(smCfgFile))  return  false;
	if  (  !pCfg  )  return  false;

	//
	memset(pCfg,  0,  sizeof(  pCfg[0]  )  );

	//	  
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_dbServIp), tBuf, mycountof(tBuf))) {
		  tBuf[0] = 0;	 
	}	 
	myTChar2Utf8(tBuf, buf, mycountof(buf));	 
	safeStrnCpy(buf, pCfg->dbServIp, mycountof(pCfg->dbServIp));


	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_dbName), tBuf, mycountof(tBuf))) {
		  tBuf[0] = 0;	 
	}	 
	myTChar2Utf8(tBuf, buf, mycountof(buf));	 
	safeStrnCpy(buf, pCfg->dbName, mycountof(pCfg->dbName));

	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_dbPasswd), tBuf, mycountof(tBuf))) {
		  tBuf[0] = 0;	 
	}	 
	myTChar2Utf8(tBuf, buf, mycountof(buf));	 
	safeStrnCpy(buf, pCfg->dbPasswd, mycountof(pCfg->dbPasswd));

	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bNoEnc_forTest), tBuf, mycountof(tBuf))) {
		  tBuf[0] = 0;	 
	}	 
	pCfg->bNoEnc_forTest=_ttol(tBuf);

	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_ucHardwareAccl), tBuf, mycountof(tBuf))) {
		  tBuf[0] = 0;	 
	}	 
	pCfg->ucHardwareAccl=_ttol(tBuf);

	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_nIntervalInS_qmdXt), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	pCfg->nIntervalInS_qmdXt = _ttol(tBuf);

	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bChannelRedirect), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	pCfg->bChannelRedirect = _ttol(tBuf);





	//
	return  true;
}


//
bool  bGetHgMcuCfg(  TCHAR  *  cfgFileName,  Hg_mcuCfg  *  pCfg  )
{
	bool  bRet  =  false;

	//
	if  (  !pCfg  )  return  false;
	memset(  pCfg,  0,  sizeof(  pCfg[0]  )  );

	TCHAR  tBuf[128];

	do  {

	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_fMinFree_disk), tBuf, mycountof(tBuf))) {
		  tBuf[0] = 0;	 
	}	 
	pCfg->fMinFree_disk=_ttof(tBuf);
	if  (  pCfg->fMinFree_disk  <  0.01  )  {
		pCfg->fMinFree_disk  =  0.8;
	}


	//	
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_iMaxElapseInDay), tBuf, mycountof(tBuf))) {
		  tBuf[0] = 0;	 
	}	 
	pCfg->iMaxElapseInDay=_ttol(tBuf);
	if  (  pCfg->iMaxElapseInDay  <=  0  )  {
		pCfg->iMaxElapseInDay=6  *  30;
	}


		//
		bRet  =  true;
	}  while  (  false  );

	return  bRet;
}


int  saveHgMcuCfg(Hg_mcuCfg  *  pCfg,  TCHAR  *  cfgFileName  )
{
	//
	FILE  *  fp  =  NULL;

	fp  =  _tfopen(  cfgFileName,  _T("w"));
	if  (  !fp  )  return  -1;

	//
	_ftprintf(  fp,  _T(  "%s     %.02f\n"  ),  _T(  CONST_cfgName_fMinFree_disk  ),  pCfg->fMinFree_disk  );
	_ftprintf(  fp,  _T(  "%s     %d\n"  ),  _T(  CONST_cfgName_iMaxElapseInDay  ),  pCfg->iMaxElapseInDay  );


	if  (  fp  )  fclose(  fp  );

	return  0;
}




//
 int  getQnmDbParams(  QY_REG  *  pReg,  LPCTSTR  smCfgFile,  int  iDefaultSystemId,  unsigned  char  ucbDefaultDsnless,  LPCTSTR  defaultDbName,  unsigned  long  ulOpenOptions,  QNM_DB_CFG  *  pDb  )
{
	int					iErr								=	-1;
	WCHAR			*	hint								=	NULL;
	WCHAR			*	p0									=	NULL;
	WCHAR			*	p1									=	NULL;
	//  BOOL				bDefault							=	FALSE;
	int					iDbType								=	0;
	WCHAR				tmpDbTypeName[32  +  1]				=	L"";
	BOOL				bDsnless							=	FALSE;
	char				tmpDbServIp[CONST_qyMaxIpLen  +  1]	=	"";
	unsigned  char		ucbUseWinAuth						=	FALSE;
	WCHAR				tmpDbName[64  +  1]					=	L"";
	WCHAR				tmpUid[64  +  1]					=	L"";
	WCHAR				tmpPwd[64  +  1]					=	L"";
	TCHAR				tmpConnectStr[256  +  1]			=	_T(  ""  );
	//
#if  0
	unsigned  long		ulOpenOptions						=	0;
						ulOpenOptions  =  get_CONST_qyDbOpenOptions(  );
#endif
	//
	unsigned  long		len;
	char				buf[2048];

	if  (  !pReg  ||  !defaultDbName  ||  !pDb  )  return  -1;
	
	if  (  qyGetRegCfg(  pReg->rootKey,  _T(  CONST_regValName_dbTypeName  ),  (  char  *  )tmpDbTypeName,  sizeof(  tmpDbTypeName  )  )  )  {
		tmpDbTypeName[0]  =  0;
		//  bDefault  =  TRUE;
	}
	tTrim(  tmpDbTypeName  );

	iDbType  =  qyGetTypeByDes(  CONST_dbTypeTable,  tmpDbTypeName  );		//  2006/05/03
	if  (  iDbType  <=  0  )  {
		iDbType  =  getDefaultDbType(  );
	}
	if  (  !bUseDb(  )  )  {		//  2013/02/21
		iDbType  =  CONST_dbType_myDb;
	}

	//
	len  =  sizeof(  buf  );
	if  (  qyGetRegDataEx(  pReg,  _T(  CONST_regValName_connectStr  ),  (  char  *  )buf,  &len  )  )  buf[0]  =  0;
	else  buf[len]  =  0;
	myUtf82TChar(  buf,  tmpConnectStr,  mycountof(  tmpConnectStr  )  );
	
	//
	if  (  !parseDbParams(  tmpConnectStr,  ulOpenOptions,  pDb  )  &&  pDb->iDbType  ==  iDbType  )  {
		//
		Qm_initCfg  qmInitCfg  =  {0};
		if  (  bGetQmInitCfg((TCHAR*)smCfgFile, &qmInitCfg)  )  {
			//
			if  (  bIpValid(qmInitCfg.dbServIp))  {
				safeStrnCpy(  qmInitCfg.dbServIp,  pDb->dbServAddr,  mycountof(  pDb->dbServAddr  )  );
			}
			myUtf82TChar(  qmInitCfg.dbName,  pDb->dbName,  mycountof(  pDb->dbName  )  );
			myUtf82TChar(  qmInitCfg.dbPasswd,  pDb->pwd,  mycountof(  pDb->pwd  )  );
		}
		//
		tmpConnectStr[0]  =  0;
		if  (  constructDbConnectStr(  pDb->iDbType,  pDb->iDbConnType,  pDb->ucbDsnless,  pDb->driver,  pDb->dbServAddr,  ucbUseWinAuth,  pDb->dbName,  pDb->uid,  pDb->pwd,  tmpConnectStr,  mycountof(  tmpConnectStr  )  )  )  goto  errLabel;
		myTChar2WChar(  tmpConnectStr,  pDb->connectStr,  mycountof(  pDb->connectStr  )  );
		//
		iErr  =  0;  goto  errLabel;
	}

	//  ÒªÊÇÃ»ÓÐ·ÖÎö³öÀ´£¬¾ÍÒªÓÃÈ±Ê¡µÄ
	memset(  pDb,  0,  sizeof(  pDb[0]  )  );
	//
	pDb->iSystemId  =  iDefaultSystemId;
	//
	pDb->bDefault  =  TRUE;
	pDb->iDbType  =  getDefaultDbType(  );
	if  (  !bUseDb(  )  )  {	//  2013/02/21
		pDb->iDbType  =  CONST_dbType_myDb;
	}

	//
	pDb->iDbConnType  =  getDbConnType(  pDb->iDbType  );	//  2012/07/12
	//
	pDb->ucbDsnless  =  ucbDefaultDsnless;
	//
	myTChar2WChar(  defaultDbName,  pDb->dbName,  mycountof(  pDb->dbName  )  );

	pDb->ulOpenOptions  =  ulOpenOptions;	//  get_CONST_qyDbOpenOptions(  );

	tmpConnectStr[0]  =  0;
	if  (  constructDbConnectStr(  pDb->iDbType,  pDb->iDbConnType,  pDb->ucbDsnless,  pDb->driver,  pDb->dbServAddr,  ucbUseWinAuth,  pDb->dbName,  pDb->uid,  pDb->pwd,  tmpConnectStr,  mycountof(  tmpConnectStr  )  )  )  goto  errLabel;
	myTChar2WChar(  tmpConnectStr,  pDb->connectStr,  mycountof(  pDb->connectStr  )  );
	
	iErr  =  0;
errLabel:

	return  iErr;

}




