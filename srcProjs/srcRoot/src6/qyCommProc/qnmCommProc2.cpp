
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

 int  getCfgValFromStr(  LPCTSTR  str,  LPCTSTR  cfg,  TCHAR  *  val,  unsigned  int  size  );


 //
 bool  bUseMySql8()
 {
	 bool  bRet = false;
	 TCHAR  tBuf[128];

	 if (!qyGetRegCfgT(HKEY_LOCAL_MACHINE, _T(CONST_qyRootKey_qnmScheduler_mis), _T("mySqlVersion"), (char*)tBuf, sizeof(tBuf), 0)) {
		 if (_ttol(tBuf) == 8) {
			 bRet = true;
		 }
	 }

	 return  bRet;
 }


 //
 bool  bUse_decD3d_nv(TCHAR* smCfgFile)
 {
	 bool  bRet = false;

	 //	 
	 TCHAR  cfgVal[128] = _T("");

	 //USB Video Device
	 getCfgValByNameT(smCfgFile, (TCHAR*)_T(CONST_cfgName_bUse_decD3d_nv), cfgVal, mycountof(cfgVal));
	 tTrim(cfgVal);
	 int  tmpiRet = _ttol(cfgVal);

	 bRet = tmpiRet;

	 //	 
	 return  bRet;

 }


 //
 bool  get_bCfgVal(TCHAR* smCfgFile,TCHAR  *  cfgName )
 {
	 bool  bRet = false;

	 //	 
	 TCHAR  cfgVal[128] = _T("");

	 //
	 if (!cfgName)  return  false;


	 //USB Video Device
	 getCfgValByNameT(smCfgFile, (TCHAR*)cfgName, cfgVal, mycountof(cfgVal));
	 tTrim(cfgVal);
	 int  tmpiRet = _ttol(cfgVal);

	 bRet = tmpiRet;

	 //	 
	 return  bRet;

 }




//  2007/06/13, ÔÚdsnlessµÄ¹¤×÷·½Ê½ÖÐ£¬dbNameÐèÒªÊÇÈ«Â·¾¶µÄÎÄ¼þÃû
// int  constructDbConnectStr(  int  iDbType,  int  iDbConnType,  BOOL  bDsnless,  char  *  dbServName,  unsigned  char  ucbUseWinAuth,  LPCTSTR  dbName,  LPCTSTR  uid,  LPCTSTR  pwd,  TCHAR  *  tmpConnectStr,  unsigned  long  size  )
 int  constructDbConnectStr(  int  iDbType,  int  iDbConnType,  BOOL  bDsnless,  char  *  driver,  char  *  dbServName,  unsigned  char  ucbUseWinAuth,  LPCTSTR  dbName,  LPCTSTR  uid,  LPCTSTR  pwd,  TCHAR  *  tmpConnectStr,  unsigned  long  size  )
{
	int		iErr				=	-1;
	TCHAR	tDbServNameBuf[256]	=	_T(  ""  );

	myStr2TChar(  dbServName,  tDbServNameBuf,  mycountof(  tDbServNameBuf  )  );

	//  2012/07/12
	if  (  iDbType  ==  CONST_dbType_myDb  )  return  0;

	//
	if  (  !uid  ||  !pwd  )  {
		return  -1;
	}

	//
	if  (  iDbConnType  ==  CONST_dbConnType_ado  )  {
 		if  (  iDbType  ==  CONST_dbType_access  )  {
			_sntprintf(  tmpConnectStr,  size,  _T(  "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;User ID=%s;Password=%s;"  ),  dbName,  _T(  CONST_qnmDbUid_access  ),  _T(  CONST_qnmDbPwd_access  )  );
			}
		else  {
			  #ifdef  __DEBUG__
					  traceLog(  (TCHAR*)_T(  "constructDbConnectStr not finished, dbType err"  )  );
			  #endif
			  goto  errLabel;
		}
		}
	else  {

 		  if  (  iDbType  ==  CONST_dbType_access  )  {
			  if  (  !bDsnless  )  _sntprintf(  tmpConnectStr,  size,  (TCHAR*)_T(  "Dsn=%s;Uid=%s;Pwd=%s;"  ),  dbName,  _T(  CONST_qnmDbUid_access  ),  _T(  CONST_qnmDbPwd_access  )  );
			  else  _sntprintf(  tmpConnectStr,  size,  _T(  "Driver={Microsoft Access Driver (*.mdb)};Dbq=%s;Uid=%s;Pwd=%s;"  ),  dbName,  _T(  CONST_qnmDbUid_access  ),  _T(  CONST_qnmDbPwd_access  )  );
			  }
		  else  if  (  iDbType  ==  CONST_dbType_oracle  )  {			      
					//  "Driver={Microsoft ODBC for Oracle};Server=qnmDb;Uid=scott;Pwd=tiger;";	
				    _sntprintf(  tmpConnectStr,  size,  _T(  "Driver={Microsoft ODBC for Oracle};Server=%s;Uid=%s;Pwd=%s;"  ),  dbName,  uid  ?  uid  :  _T(  ""  ),  pwd  ?  pwd  :  _T(  ""  )  );
					}
		  else  if  (  iDbType  ==  CONST_dbType_sqlServer  )  {	  //  "PROVIDER=MSDASQL;Dsn=testSqlDsn;Uid=;Pwd=;";
			    //  _snprintf(  tmpConnectStr,  size,  "PROVIDER=MSDASQL;Dsn=%s;Uid=;Pwd=;",  CONST_qnmDsn_sqlServer  );
			    //  _snprintf(  tmpConnectStr,  size,  "DRIVER={SQL Server};SERVER=(local);Uid=%s;Pwd=%s;DATABASE=pubs;",  uid  ?  uid  :  "",  pwd  ?  pwd  :  ""  );
			    
			    if  (  ucbUseWinAuth  )  {
					//  _sntprintf(  tmpConnectStr,  size,  _T(  "Data Source=%s;Integrated Security=True"  ),  tDbServIpBuf  );
					_sntprintf(  tmpConnectStr,  size,  _T(  "DRIVER={SQL Server};Server=%s;Trusted_connection=Yes"  ),  tDbServNameBuf  );

					}
				else  {
					  _sntprintf(  tmpConnectStr,  size,  _T(  "DRIVER={SQL Server};Server=%s;Uid=%s;Pwd=%s;Database=%s;"  ),  tDbServNameBuf,  uid  ?  uid  :  _T(  ""  ),  pwd  ?  pwd  :  _T(  ""  ),  dbName  );
				}
				}
		  else  if  (  iDbType  ==  CONST_dbType_mySql  )  {
					//
					bool  bUseV8 = bUseMySql8();
					TCHAR* driverStr = (TCHAR*)_T(  CONST_dbDriver_mySql  );
					if (bUseV8)  driverStr = (TCHAR*)_T(CONST_dbDriver_mySql8);

					//
			        _sntprintf(  tmpConnectStr,  size,  _T(  "DRIVER=%s;SERVER=%s;DATABASE=%s;USER=%s;PASSWORD=%s;OPTION=3;"  ),  driverStr,  tDbServNameBuf,  dbName,  uid,  pwd  );
		 		    }
		  else if ( iDbType  ==  CONST_dbType_mariaDb  )  { 
			  int port = 3306;
			     //  SQLWCHAR *ConnStr= L"Driver={MariaDB ODBC 2.0 Driver};Server=localhost;UID=odbc_user;PWD=odbc_pw;DB=odbc_test;Port=3306";
				  _sntprintf(  tmpConnectStr, size, _T(  "DRIVER=%s; TCPIP=1;Server=%s; Port=%d; Database=%s; Uid=%s; Pwd=%s; "  ),
								_T(  CONST_dbDriver_mariaDb  ),  tDbServNameBuf,  port,  dbName,  uid, pwd  );


				  }
		  else  if  (  iDbType  ==  CONST_dbType_oscar  )  {
															//DRIVER={OSCAR ODBC DRIVER};DATABASE=OSRDB;SERVER=localhost;UID=SYSDBA;PWD=szoscar55");
			        _sntprintf(  tmpConnectStr,  size,  _T(  "DRIVER=%s;SERVER=%s;DATABASE=%s;UID=%s;PWD=%s;"  ),  _T(  CONST_dbDriver_oscar  ),  tDbServNameBuf,  dbName,  uid,  pwd  );
					//_sntprintf(  tmpConnectStr,  size,  _T(  "DRIVER=%s;SERVER=%s;DATABASE=%s;UID=%s;PWD=%s;UseStaticCursor=1;"  ),  _T(  CONST_dbDriver_oscar  ),  tDbServNameBuf,  dbName,  uid,  pwd  );



					
		 		    }

		  else  {
			    showInfo_open0(  0,  0,  _T(  "constructDbConnectStr failed, unsupported dbType"  )  );
			    goto  errLabel;
		  }
	}

	iErr  =  0;
errLabel:
	return  iErr;
}


 
 QY_DMITEM  CONST_dbTypeTable[]	=
{
	//  {	CONST_dbType_null,								_T(  ""  ),									},
	{	CONST_dbType_access,								(TCHAR*)_T(  CONST_dbTypeName_access  ),			},
	{	CONST_dbType_sqlServer,								(TCHAR*)_T(  CONST_dbTypeName_sqlServer  ),			},
	//  {	CONST_dbType_oracle,							(TCHAR*)_T(  CONST_dbTypeName_oracle  ),			},
	//
	{	CONST_dbType_mySql,									(TCHAR*)_T(  CONST_dbTypeName_mySql  ),				},
	//
	{	CONST_dbType_mariaDb,								(TCHAR*)_T(  CONST_dbTypeName_mariaDb  ),			},

	//
	{	CONST_dbType_myDb,									(TCHAR*)_T(  CONST_dbTypeName_myDb  ),				},		//  2013/02/20
	//
	{	CONST_dbType_oscar,									(TCHAR*)_T(  CONST_dbTypeName_oscar  ),				},		//  2013/02/20
	
	//
	{	-1,						},
};


 int  parseDbParams(  LPCTSTR  connectInput,  unsigned  long  ulOpenOptions,  QNM_DB_CFG  *  pDb  )
{
	int					iErr								=	-1;
	int					iDbType								=	0;
	TCHAR				tmpDbTypeName[32  +  1]				=	_T(  ""  );
	int					iDbConnType							=	0;
	unsigned  char		ucbDsnless							=	CONST_ucbDsnless_true;			//  È±Ê¡²ÉÓÃÎÞDSNµÄ·½Ê½£¬2007/06/13
	//
	char				tmpDriver[256]						=	(  ""  );
	//
	char				tmpDbServAddr[256  +  1]	=	"";
	TCHAR				tmpDbName[MAX_PATH  +  1]			=	_T(  ""  );
	unsigned  char		ucbUseWinAuth						=	FALSE;
	TCHAR				tmpUid[64  +  1]					=	_T(  ""  );
	TCHAR				tmpPwd[64  +  1]					=	_T(  ""  );
	TCHAR				tmpConnectStr[256  +  1]			=	_T(  ""  );
	//
#if  0
	unsigned  long		ulOpenOptions						=	0;	
						ulOpenOptions  =  get_CONST_qyDbOpenOptions(  );
#endif
						//
	TCHAR				tmpSysName[128]						=	_T(  ""  );
	TCHAR				tmpSystemId[128]					=	_T(  ""  );
	int					iSystemId							=	0;
	TCHAR				tBuf[1024];
	TCHAR			*	pT;

	if  (  !connectInput  ||  !pDb  )  return  -1;

	memset(  pDb,  0,  sizeof(  pDb[0]  )  );

	if  (  getCfgValFromStr(  connectInput,  _T(  CONST_qyCfgName_sysName  ),  tmpSysName,  mycountof(  tmpSysName  )  )  )  goto  errLabel;
	//
	if  (  getCfgValFromStr(  connectInput,  _T(  CONST_qyCfgName_systemId  ),  tmpSystemId,  mycountof(  tmpSystemId  )  )  )  goto errLabel;
	iSystemId  =  _tcstol(  tmpSystemId,  &pT,  10  );

	if  (  getCfgValFromStr(  connectInput,  _T(  CONST_qyCfgName_dbType  ),  tmpDbTypeName,  mycountof(  tmpDbTypeName  )  )  )  goto  errLabel;
	
	iDbType  =  qyGetTypeByDes(  CONST_dbTypeTable,  tmpDbTypeName  );		//  2006/05/03
	if  (  iDbType  <=  0  )  goto  errLabel;

	//  2012/07/12
	iDbConnType  =  getDbConnType(  iDbType  );

	//  2014/02/07
	if  (  getCfgValFromStr(  connectInput,  _T(  "Trusted_connection"  ),  tBuf,  mycountof(  tBuf  )  )  )  tBuf[0]  =  0;
	TCHAR* yesStr; yesStr = (TCHAR*)_T("yes");
	if  (  !_tcsnicmp(  tBuf,  yesStr,  lstrlen(  yesStr  )  )  )  {
		ucbUseWinAuth  =  TRUE;
	}


	//
	if  (  iDbType  ==  CONST_dbType_sqlServer  &&  ucbUseWinAuth  )  {
		if  (  getCfgValFromStr(  connectInput,  _T(  "Server"  ),  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;
		myTChar2Str(  tBuf,  tmpDbServAddr,  mycountof(  tmpDbServAddr  )  );
		}
	else  {

		//
		switch  (  iDbType  )  {
				case  CONST_dbType_access: 
					  if  (  !getCfgValFromStr(  connectInput,  _T(  "Dsn"  ),  tBuf,  mycountof(  tBuf  )  )  )  ucbDsnless  =  FALSE;
					  if  (  !ucbDsnless  )  lstrcpyn(  tmpDbName,  tBuf,  mycountof(  tmpDbName  )  );
					  //
					  if  (  !getCfgValFromStr(  connectInput,  _T(  "Dbq"  ),  tBuf,  mycountof(  tBuf  )  )  )  ucbDsnless  =  CONST_ucbDsnless_true;
					  if  (  ucbDsnless  )  lstrcpyn(  tmpDbName,  tBuf,  mycountof(  tmpDbName  )  );

					  //
					  if  (  getCfgValFromStr(  connectInput,  _T(  "Uid"  ),  tmpUid,  mycountof(  tmpUid  )  )  )  goto  errLabel;
					  if  (  getCfgValFromStr(  connectInput,  _T(  "Pwd"  ),  tmpPwd,  mycountof(  tmpPwd  )  )  )  goto  errLabel;
				  
					  break;
				case  CONST_dbType_sqlServer:
					  if  (  getCfgValFromStr(  connectInput,  _T(  "Server"  ),  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;
					  myTChar2Str(  tBuf,  tmpDbServAddr,  mycountof(  tmpDbServAddr  )  );
					  if  (  getCfgValFromStr(  connectInput,  _T(  "Database"  ),  tmpDbName,  mycountof(  tmpDbName  )  )  )  goto  errLabel;		

					  //
					  if  (  getCfgValFromStr(  connectInput,  _T(  "Uid"  ),  tmpUid,  mycountof(  tmpUid  )  )  )  goto  errLabel;
					  if  (  getCfgValFromStr(  connectInput,  _T(  "Pwd"  ),  tmpPwd,  mycountof(  tmpPwd  )  )  )  goto  errLabel;

					  break;
				case  CONST_dbType_mySql:
					  if  (  getCfgValFromStr(  connectInput,  _T(  "DRIVER"  ),  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;
					  myTChar2Str(  tBuf,  tmpDriver,  mycountof(  tmpDriver  )  );					
					  if  (  getCfgValFromStr(  connectInput,  _T(  "SERVER"  ),  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;
					  myTChar2Str(  tBuf,  tmpDbServAddr,  mycountof(  tmpDbServAddr  )  );
					  if  (  getCfgValFromStr(  connectInput,  _T(  "DATABASE"  ),  tmpDbName,  mycountof(  tmpDbName  )  )  )  goto  errLabel;		
					  //
					  if  (  getCfgValFromStr(  connectInput,  _T(  "USER"  ),  tmpUid,  mycountof(  tmpUid  )  )  )  goto  errLabel;
					  if  (  getCfgValFromStr(  connectInput,  _T(  "PASSWORD"  ),  tmpPwd,  mycountof(  tmpPwd  )  )  )  goto  errLabel;

					  break;
				case  CONST_dbType_mariaDb:
					  if (getCfgValFromStr(connectInput, _T("DRIVER"), tBuf, mycountof(tBuf)))  goto  errLabel;
					  myTChar2Str(tBuf, tmpDriver, mycountof(tmpDriver));
					  if (getCfgValFromStr(connectInput, _T("Server"), tBuf, mycountof(tBuf)))  goto  errLabel;
					  myTChar2Str(tBuf, tmpDbServAddr, mycountof(tmpDbServAddr));
					  if (getCfgValFromStr(connectInput, _T("Database"), tmpDbName, mycountof(tmpDbName)))  goto  errLabel;
					  //
					  if (getCfgValFromStr(connectInput, _T("Uid"), tmpUid, mycountof(tmpUid)))  goto  errLabel;
					  if (getCfgValFromStr(connectInput, _T("Pwd"), tmpPwd, mycountof(tmpPwd)))  goto  errLabel;

					  break;
				case  CONST_dbType_oscar:
					  //
					  if  (  getCfgValFromStr(  connectInput,  _T(  "DRIVER"  ),  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;
					  myTChar2Str(  tBuf,  tmpDriver,  mycountof(  tmpDriver  )  );					
					  if  (  getCfgValFromStr(  connectInput,  _T(  "SERVER"  ),  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;
					  myTChar2Str(  tBuf,  tmpDbServAddr,  mycountof(  tmpDbServAddr  )  );
					  if  (  getCfgValFromStr(  connectInput,  _T(  "DATABASE"  ),  tmpDbName,  mycountof(  tmpDbName  )  )  )  goto  errLabel;		
					  //
					  if  (  getCfgValFromStr(  connectInput,  _T(  "UID"  ),  tmpUid,  mycountof(  tmpUid  )  )  )  goto  errLabel;
					  if  (  getCfgValFromStr(  connectInput,  _T(  "PWD"  ),  tmpPwd,  mycountof(  tmpPwd  )  )  )  goto  errLabel;
					  //
					  break;
				default:
						traceLog(  (TCHAR*)_T(  "parseDbParams failed, unprocessed dbType"  )  );
						goto  errLabel;
		}
	

		//			
		if  (  iDbType  ==  CONST_dbType_access  )
		{					
			//  È±Ê¡Access
			lstrcpyn(  tmpDbTypeName,  _T(  CONST_dbTypeName_access  ),  mycountof(  tmpDbTypeName  )  );

			tmpUid[0]  =  0;
			tmpPwd[0]  =  0;

		}

	}

	if  (  constructDbConnectStr(  iDbType,  iDbConnType,  ucbDsnless,  tmpDriver,  tmpDbServAddr,  ucbUseWinAuth,  tmpDbName,  tmpUid,  tmpPwd,  tmpConnectStr,  mycountof(  tmpConnectStr  )  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
		myTChar2WChar(  tmpSysName,  pDb->sysName,  mycountof(  pDb->sysName  )  );
		pDb->iSystemId  =  iSystemId;
		pDb->iDbType  =  iDbType;
		pDb->iDbConnType  =  iDbConnType;
		pDb->ucbDsnless  =  ucbDsnless;
		safeStrnCpy(  tmpDriver,  pDb->driver,  mycountof(  pDb->driver  )  );
		safeStrnCpy(  tmpDbServAddr,  pDb->dbServAddr,  mycountof(  pDb->dbServAddr  )  );
		pDb->ucbUseWinAuth  =  ucbUseWinAuth;
		myTChar2WChar(  tmpDbName,  pDb->dbName,  mycountof(  pDb->dbName  )  );
		myTChar2WChar(  tmpUid,  pDb->uid,  mycountof(  pDb->uid  )  );
		myTChar2WChar(  tmpPwd,  pDb->pwd,  mycountof(  pDb->pwd  )  );
		myTChar2WChar(  tmpConnectStr,  pDb->connectStr,  mycountof(  pDb->connectStr  )  );
		pDb->ulOpenOptions  =  ulOpenOptions;
	}

	return  iErr;

}


