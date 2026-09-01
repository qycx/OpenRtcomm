
//  #include	"stdAfx.h"
#include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>

#define  __noDbg_new__

#include	"qyCommon.h"
#include	"qyString.h"
#include	"qyDbCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmPcComm.h"
#include	"qySqlFunc.h"
#include	"qnmSqlScripts.h"
#include	"pcCommType_defs.h"




char	*  CONST_dsn_bhb					=	"awmExtDsn";
char	*  CONST_dsn_netMc					=	"qyNetMcDsn";
char	*  CONST_dsn_misClient				=	"qyDsn_misClient";			//  2007/03/10
char	*  CONST_dsn_mis					=	"qyDsn_mis";		//  2007/03/10
//
//  #define		CONST_connectStr_access				"Dsn=qyNetMcDsn;Uid=;Pwd=;"
//  char	*	CONST_connectStr_access			=	"Dsn=qyNetMcDsn;Uid=;Pwd=;";
char	*	CONST_connectStrFmt_access			=	"Dsn=%s;Uid=;Pwd=;";
//
//  #define		CONST_connectStr_oracle				"Driver={Microsoft ODBC for Oracle};Server=qnmDb;Uid=scott;pwd=tiger;"
char	*	CONST_connectStr_oracle			=	"Driver={Microsoft ODBC for Oracle};Server=qnmDb;Uid=scott;pwd=tiger;";
//
//  #define	CONST_connectStr_sqlServer			"PROVIDER=MSDASQL;Dsn=qnmSqlDsn;Uid=;Pwd=;"
//  #define	CONST_connectStr_sqlServer			"DRIVER={SQL Server};SERVER=127.0.0.1;Uid=;Pwd=;DATABASE=pubs;"
char	*	CONST_connectStrFmt_sqlServer	=	"DRIVER={SQL Server};SERVER=%s;Uid=%s;Pwd=%s;DATABASE=%s;";

char	*	CONST_autoincrement_access		=	" autoincrement ";
char	*	CONST_nchar_access				=	" char ";
char	*	CONST_nvarchar_access			=	" varchar ";
//
char	*	CONST_autoincrement_sqlServer	=	" int identity ";
char	*	CONST_nchar_sqlServer			=	" nchar ";
char	*	CONST_nvarchar_sqlServer		=	" nvarchar ";
//
char	*	CONST_autoincrement_mySql		=	" int auto_increment primary key ";
char	*	CONST_nchar_mySql				=	" nchar ";
char	*	CONST_nvarchar_mySql			=	" nvarchar ";
//
char* CONST_autoincrement_oscar = " int auto_increment primary key ";
char* CONST_nchar_oscar = " nchar ";
char* CONST_nvarchar_oscar = " varchar ";





//
 CString  getDataType(  char  *  typeStr,  unsigned  int  len  )
{
	 char	buf[256];
	 _snprintf(  buf,  sizeof(  buf  ),  "%s",  typeStr  );
	 trim(  buf  );
	 _snprintf(  buf,  sizeof(  buf  ),  "%s(%d)",  buf,  len  );
	 return  CString(  buf  );
}


 //  当dbType为access时，dbName为dsnName, 2007/03/10
// BOOL  bDbConnected_netMc(  LPCWSTR  dbTypeName,  char  *  servIp,  LPCWSTR  uid,  LPCWSTR  pwd,  LPCWSTR  dbName  )
 BOOL  bDbConnected_netMc(  LPCWSTR  connectStrBuf  )
{
	 BOOL			bRet				=	FALSE;
	 CDatabase	*	pDb					=	NULL;
	 //  WCHAR			connectStrBuf[512]	=	_T(  ""  );

	 if  (  !connectStrBuf  )  return  FALSE;

#if  0
	 if  (  !wcsicmp(  dbTypeName,  _T(  CONST_dbTypeName_access  )  )  )  _sntprintf(  connectStrBuf,  mycountof(  connectStrBuf  ),  CString(  CONST_connectStrFmt_access  ),  dbName  );
	 else  _sntprintf(  connectStrBuf,  mycountof(  connectStrBuf  ),  CString(  CONST_connectStrFmt_sqlServer  ),  CString(  servIp  ),  uid,  pwd,  dbName  );
#endif
	 
	 try  {
		pDb = new  CDatabase;
		if  (  !pDb  )  goto  errLabel;
		if  (  !pDb->OpenEx(  CString(  connectStrBuf  ),  CONST_qyDbOpenOptions  )  )  goto errLabel;
		
		}
	catch  (  CException  *  e  )  {
		   #ifdef  __DEBUG__
				   e->ReportError(  );
		   #endif
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bDbConnected_netMc failed."  )  );
		   goto  errLabel;
	}

	bRet  =  TRUE;
		
errLabel:

	if  (  pDb  )  delete  pDb;

	 return  bRet;
}

// BOOL  bDbInstalled_netMc(  LPCWSTR  dbTypeName,  char  *  servIp,  LPCWSTR  uid,  LPCWSTR  pwd,  LPCWSTR  dbName  )
 BOOL  bDbInstalled_netMc(  LPCWSTR  connectStrBuf  )
{
	 BOOL			bRet				=	FALSE;
	 CDatabase	*	pDb					=	NULL;
	 //  TCHAR			connectStrBuf[512]	=	_T(  ""  );
	 CDBVariant		varVals[1];
	 CString		sqlStr;

	 if  (  !connectStrBuf  )  return  FALSE;

#if  0
	 if  (  !wcsicmp(  dbTypeName,  _T(  CONST_dbTypeName_access  )  )  )  _sntprintf(  connectStrBuf,  mycountof(  connectStrBuf  ),  CString(  CONST_connectStrFmt_access  ),  dbName  );
	 else  _sntprintf(  connectStrBuf,  mycountof(  connectStrBuf  ),  CString(  CONST_connectStrFmt_sqlServer  ),  CString(  servIp  ),  uid,  pwd,  dbName  );
#endif

	 try  {
		pDb = new  CDatabase;
		if  (  !pDb  )  goto  errLabel;
		if  (  !pDb->OpenEx(  CString(  connectStrBuf  ),  CONST_qyDbOpenOptions  )  )  goto errLabel;
		
		sqlStr  =  CString(  "select count(*) from qyTestTab"  );
		if  (  !bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;
		sqlStr  =  CString(  "select count(*) from qyTestEndTab"  );
		if  (  !bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;

		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bDbInstalled_netMc failed."  )  );
		   goto  errLabel;
	}

	bRet  =  TRUE;
		
errLabel:

	if  (  pDb  )  delete  pDb;

	 return  bRet;
}


 int  sqlScripts_qyTestTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt  )
{
	 int	cnt  =  *piCnt;

	 traceLogA(  "建第一个表"  );
 	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyTestTab("
										"col0				varchar(30) primary key,"
										"col_int			int,"
										"col_Integer		Integer"
										")";
	 cnt  ++  ;

	 *piCnt  =  cnt;
	 return  0;
}

 int  sqlScripts_qyTestEndTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt  )
{
	 int	cnt  =  *piCnt;

	 //traceLogA(  "建最后一个测试建库结束的表"  );
	 //
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyTestEndTab("
										"col0				varchar(30) primary key,"
										"col_int			int,"
										"col_Integer		Integer"
										")";
	 cnt  ++  ;

	 *piCnt  =  cnt;
	 return  0;
}



 int  sqlScripts_qySystemInfoTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  int  iServiceId,  int  iSystemId,  int  iAppType,  LPCTSTR  serviceName,  char  *  dbVer  )
{
	 int	cnt			=	*piCnt;
	 TCHAR	sqlBuf[2048];

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qySystemInfoTab("
										"iServiceId			int  not  null,"			//  2007/03/10
										"iSystemId			int  not  null,"			//  2007/09/15
										"iAppType			int	 not  null,"			//  2007/09/15
										"name				varchar(15) not null,"
										"dbVer				varchar(32) not null,"
										"col0				varchar(255),"
										"col1				varchar(255),"
										"col2				varchar(255),"
										"col3				varchar(255),"
										"col4				varchar(255),"
										"col5				varchar(255),"
										"col6				varchar(255),"
										"col7				varchar(255),"
										"col8				varchar(255),"
										"col9				varchar(255),"
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;


	 //  初始化系统信息
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qySystemInfoTab(iServiceId,iSystemId,iAppType,name,dbVer) values(%d,%d,%d,'%s','%s')"  ),  iServiceId,  iSystemId,  iAppType,  serviceName,  CString(  dbVer  )  );
	 sqlStr[cnt]  =  CString(  sqlBuf  );
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
}

 int  sqlScripts_qyUsrTabs(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int	cnt		=	*piCnt;
	 
	 //  建管理端用户组列表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyGrpTab("
 										"name				varchar(30) primary key,"
									    "right0				varchar(255)"
										")";
	 cnt  ++  ;

	 //  建管理端用户列表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyUsrTab("
 										"name				varchar(30) primary key,"
									    "passwd				varchar(32) not null,"
										//
										//  下面为用户登陆后限制操作范围用。2008/09/03
										//
										"zbStr				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255) not null,"
										"bbStr				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255) not null,"
										"dwStr				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255) not null,"
										"bmStr				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255) not null,"
										//
										"comment0			"  +  getDataType(  p_nvarchar,  255  )  +  ""					//  varchar(255) not null,"
										")";
	 cnt  ++  ;

	 //  建用户和用户组关联列表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyGrpUsrRelationTab("
 										"grpName			varchar(30) not null,"
									    "usrName			varchar(30) not null,"
										"constraint grpUsrInd unique(grpName,usrName)"
										")";
	 cnt  ++  ;

	 //  初始化用户和组相关信息
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyUsrTab(name,passwd,zbStr,bbStr,dwStr,bmStr) values('admin','923b56hnw','','','','')";
	 cnt  ++  ;
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyGrpUsrRelationTab(grpName,usrName) values('adminGrp','admin')";
	 cnt  ++  ;
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyUsrTab(name,passwd,zbStr,bbStr,dwStr,bmStr) values('sysadmin','f3f9f3e1e4ede9eeb1b2b3','','','','')";
	 cnt  ++  ;
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyGrpUsrRelationTab(grpName,usrName) values('sysGrp','sysadmin')";
	 cnt  ++  ;
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyUsrTab(name,passwd,zbStr,bbStr,dwStr,bmStr) values('logadmin','ecefe7e1e4ede9eeb1b2b3','','','','')";
	 cnt  ++  ;
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyGrpUsrRelationTab(grpName,usrName) values('logGrp','logadmin')";
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
}


 int  sqlScripts_qyObjIndexTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int	cnt		=	*piCnt;

 	 //  建对象索引的表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyObjIndexTab("
										//  "id					autoincrement,"
										"id	"  +  pAutoincrement  +  ","
										"usageType			int not null,"		//  似乎这个类型没什么用，一般情况下不要使用，2007/08/06
										"usageName			"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"servName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255) not null,"  //  2007/08/06
										"objType  			int not null,"			/*  节点对象  */
										"objId0				int not null,"
										"objId1				int not null,"
										"objId2				int not null,"
										"objIdStr0			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255) not null,"
										"objIdStr1			"  +  getDataType(  p_nvarchar,  128  )  +  " not null,"		//  varchar(255) not null,"
										"objIdStr2			"  +  getDataType(  p_nvarchar,  128  )  +  " not null,"		//  varchar(255) not null,"
										//
										//"constraint objInd unique(usageType,servName,objType,objId0,objId1,objId2,objIdStr0,objIdStr1,objIdStr2),"
										"constraint objInd unique(usageType,servName,objType,objId0,objId1,objId2,objIdStr0,objIdStr1,objIdStr2),"
										//
										"col0				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col1				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col2				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col3				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col4				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"comment0			"  +  getDataType(  p_nvarchar,  255  )  +  ""					//  varchar(255)"
										")";
	 cnt  ++  ;


	 *piCnt  =  cnt;

	 return  0;

	 
}


  int  sqlScripts_qyCusNameTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int	cnt		=	*piCnt;

 	 //  2004/05/15为建立一个容易记忆的别名表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyCusNameTab("
										"id	"  +  pAutoincrement  +  ","
										"iType				int not null,"
										"uiLangId			int not null,"						//  保留
										"objName0			"  +  getDataType(  p_nvarchar,  128  )  +  " not null,"		//  varchar(255) not null,"
										"cusName0			"  +  getDataType(  p_nvarchar,  128  )  +  ","		//  varchar(255),"							
										//					//  从到9都是为了规范用户信息而引入, 2006/09/02
										"objName1			"  +  getDataType(  p_nvarchar,  128  )  +  " not null,"		//  varchar(255),"							
										"cusName1			"  +  getDataType(  p_nvarchar,  128  )  +  ","		//  varchar(255),"							
										"objName2			"  +  getDataType(  p_nvarchar,  128  )  +  " not null,"		//  varchar(255),"							
										"cusName2			"  +  getDataType(  p_nvarchar,  128  )  +  ","		//  varchar(255),"							
										"objName3			"  +  getDataType(  p_nvarchar,  128  )  +  " not null,"		//  varchar(255),"							
										"cusName3			"  +  getDataType(  p_nvarchar,  128  )  +  ","		//  varchar(255),"							
										"objName4			"  +  getDataType(  p_nvarchar,  128  )  +  " not null,"		//  varchar(255),"							
										"cusName4			"  +  getDataType(  p_nvarchar,  128  )  +  ","		//  varchar(255),"							
										"objName5			"  +  getDataType(  p_nvarchar,  128  )  +  " not null,"		//  varchar(255),"							
										"cusName5			"  +  getDataType(  p_nvarchar,  128  )  +  ","		//  varchar(255),"							
										"objName6			"  +  getDataType(  p_nvarchar,  128  )  +  " not null,"		//  varchar(255),"							
										"cusName6			"  +  getDataType(  p_nvarchar,  128  )  +  ","		//  varchar(255),"							
										"objName7			"  +  getDataType(  p_nvarchar,  128  )  +  " not null,"		//  varchar(255),"							
										"cusName7			"  +  getDataType(  p_nvarchar,  128  )  +  ","		//  varchar(255),"							
										//
										//"constraint tmpCusNameIndex unique(iType,uiLangId,objName0,objName1,objName2,objName3,objName4,objName5,objName6,objName7),"
										"constraint tmpCusNameIndex unique(iType,uiLangId,objName0,objName1,objName2,objName3,objName4,objName5),"
										//
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;

	 
}


 int  sqlScripts_qyImObjTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int	cnt		=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyImObjTab;


 	 //  主表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","										
										"idStr				char(20) not null,"
										"misServName		"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr),"										
										//
										"uiType				int not null,"			//  messenger类型, 是我，联系人，还是群等
										//
										"ip					char(12),"
										"detectedIp			char(12),"			//  从服务器端探测到的client ip
										//
										"clientVer			char(8),"			//  2007/09/16, 客户端版本号
										//
										"usLangId			int,"					//  2005/01/22, 语种
										"uiDevType			int,"					//  运行messenger的类型。比如PC
										"messengerName		"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										//
										//
										"iRole				int,"					//  2017/08/14. 角色，如超级管理员
										//
										//
										"usRunningStatus	int,"					//  2007/8/20, 通常在管理端表示在线等状态。客户端是在内存中处理的。
										//
										"startTime			char(14),"
										"tLastModifiedTime	char(14),"
										//
										"tLastGrpDeletedTime	char(14),"				//  2007/08/26, 最后一次从某组中移出发生的时间
										"tLastMemDeletedTime	char(14),"				//  2007/08/26, 最后一次组成员被删除发生的时间
										//
										"iStatus			int not null,"
										//
										"col0				varchar(255),"
										"col1				varchar(255),"
										"col2				varchar(255),"
										"col3				varchar(255),"
										"col4				varchar(255),"
										"col5				varchar(255),"
										"col6				varchar(255),"
										"col7				varchar(255),"
										"col8				varchar(255),"
										"col9				varchar(255),"
										"col10				varchar(255),"
										"col11				varchar(255),"
										"col12				varchar(255),"
										"col13				varchar(255),"
										"col14				varchar(255),"
										"col15				varchar(255),"
										"col16				varchar(255),"
										"col17				varchar(255),"
										"col18				varchar(255),"
										"col19				varchar(255),"
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;
	 
	 *piCnt  =  cnt;

	 return  0;
	 
}




 ///


 int  sqlScripts_qyMessengerPcInfoTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int	cnt		=	*piCnt;

 	 //  主表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyMessengerPcInfoTab("
										"id	"  +  pAutoincrement  +  ","										
										"idStr				char(20) not null,"
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"constraint tmpIndex_qyMessengerPcTab unique(misServName,idStr),"	
										//
										"uiType				int not null,"				//  设备类型, 是PC
										//
										"iPlatformId		int,"						//  2005/01/22，操作系统类型
										//
										"pcName			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										"domainName		"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										"osUsrName		"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										//
										"startTime			char(14),"
										"tLastModifiedTime	char(14),"
										//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}


 int  sqlScripts_qyImObjAuthTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int	cnt		=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyImObjAuthTab;


 	 //  认证信息表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","										
										"idStr				char(20) not null,"
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr),"										
										//
										"uiType				int not null,"		//  messenger type
										//
										"mac0				char(12),"
										"mac1				char(12),"
										"mac2				char(12),"
										"otherMacs			varchar(255),"
										"nMacs				int,"
										"pcName			"  +  getDataType(  p_nvarchar,  255  )  +  ","			//  varchar(255),"							
										"domainName		"  +  getDataType(  p_nvarchar,  255  )  +  ","			//  varchar(255),"							
										"osUsrName		"  +  getDataType(  p_nvarchar,  255  )  +  ","			//  varchar(255),"							
										//
										"messengerName		"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"  //  2010/01/04, not used							
										"messengerPasswd	"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"	//  2010/01/04, not used						
										//
										//
										"ip					char(12),"
										//
										//
										"iRole				int,"				//  2017/08/14. 角色，如超级管理员
										//
										//
										"iStatus			int not null,"
										//																				
										"startTime			char(14) not null,"
										"tLastModifiedTime	char(14) not null,"
										//
										+  "col0		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col0				varchar(255),"
										+  "col1		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col1				varchar(255),"
										+  "col2		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col2				varchar(255),"
										+  "col3		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col3				varchar(255),"
										+  "col4		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col4				varchar(255),"
										+  "col5		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col5				varchar(255),"
										+  "col6		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col6				varchar(255),"
										+  "col7		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col7				varchar(255),"
										+  "col8		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col8				varchar(255),"
										+  "col9		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col9				varchar(255),"
										+  "col10		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col10				varchar(255),"
										+  "col11		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col11				varchar(255),"
										+  "col12		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col12				varchar(255),"
										+  "col13		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col13				varchar(255),"
										+  "col14		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col14				varchar(255),"
										+  "col15		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col15				varchar(255),"
										+  "col16		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col16				varchar(255),"
										+  "col17		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col17				varchar(255),"
										+  "col18		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col18				varchar(255),"
										+  "col19		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col19				varchar(255),"
										+  "col20		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col20				varchar(255),"
										+  "col21		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col21				varchar(255),"
										+  "col22		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col22				varchar(255),"
										+  "col23		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col23				varchar(255),"
										+  "col24		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col24				varchar(255),"
										+  "col25		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col25				varchar(255),"
										+  "col26		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col26				varchar(255),"
										+  "col27		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col27				varchar(255),"
										+  "col28		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col28				varchar(255),"
										+  "col29		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col29				varchar(255)"
										//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}

  int  sqlScripts_qyImObjAuthTmpTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int	cnt		=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyImObjAuthTmpTab;


	 //  认证临时表, 临时表有一些信息放在一个表中更容易处理，所以和正式表的项不能一样
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","
										"idStr				char(20) not null,"
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										//  "constraint tmpIndex_qyMessengerAuthTmpTab unique(misServName,idStr),"										
										//  对临时表，考虑不清楚应不应该放入idStr作为键值。但是要是有人恶意注册，那么要是在临时表里去占用IDSTR，那么会浪费很多IDSTR的
										//
										"uiType				int not null,"		//  messenger类型
										//
										"mac0				char(12),"
										"mac1				char(12),"
										"mac2				char(12),"
										"otherMacs			varchar(255),"
										"nMacs				int,"
										"pcName			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										"domainName			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										"osUsrName		"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										//
										"messengerName		"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										"messengerPasswd	"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										//
										"ip					char(12),"
										//
										"clientVer			char(8),"
										//
										"uiLangId			int,"						//  2005/01/22, 语种
										"iPlatformId		int,"						//  2005/01/22，操作系统类型
										//
										"iStatus			int,"
										//																				
										"startTime			char(14) not null,"
										"tLastModifiedTime	char(14),"
										//
										+  "col0		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col0				varchar(255),"
										+  "col1		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col1				varchar(255),"
										+  "col2		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col2				varchar(255),"
										+  "col3		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col3				varchar(255),"
										+  "col4		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col4				varchar(255),"
										+  "col5		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col5				varchar(255),"
										+  "col6		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col6				varchar(255),"
										+  "col7		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col7				varchar(255),"
										+  "col8		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col8				varchar(255),"
										+  "col9		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col9				varchar(255),"
										+  "col10		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col10				varchar(255),"
										+  "col11		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col11				varchar(255),"
										+  "col12		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col12				varchar(255),"
										+  "col13		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col13				varchar(255),"
										+  "col14		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col14				varchar(255),"
										+  "col15		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col15				varchar(255),"
										+  "col16		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col16				varchar(255),"
										+  "col17		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col17				varchar(255),"
										+  "col18		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col18				varchar(255),"
										+  "col19		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col19				varchar(255),"
										+  "col20		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col20				varchar(255),"
										+  "col21		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col21				varchar(255),"
										+  "col22		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col22				varchar(255),"
										+  "col23		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col23				varchar(255),"
										+  "col24		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col24				varchar(255),"
										+  "col25		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col25				varchar(255),"
										+  "col26		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col26				varchar(255),"
										+  "col27		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col27				varchar(255),"
										+  "col28		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col28				varchar(255),"
										+  "col29		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col29				varchar(255)"
										//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}


 int  sqlScripts_qyImAmTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int			cnt			=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyImAmTab;

	 //  
  	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","										
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"idStr				char(20) not null,"
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr),"										

										//
										"usAuthType					int not null,"
										//
										"messengerName		"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"			//  varchar(255),"  
										"constraint tmpIndex_"  +  pTabName  +  "_name unique(misServName,usAuthType,messengerName),"																				
										
										"messengerPasswd			varchar(255  ) not null,"									//  varchar(255),"	
  										"iPasswdType				int not null,"														//  2010/01/03
										"salt						varchar(255),"												//  2010/01/03
										//	
										"iStatus					int,"
										//
										"startTime					char(14),"
										"tLastModifiedTime			char(14),"
										//
										//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}


 //
  int  sqlScripts_qyLoginTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int			cnt			=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyLoginTab;

	 //  
  	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","										
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"idStr				char(20) not null,"
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr),"										

										//
										"uiLoginId			int not null,"

										//
										"startTime					char(14),"
										"tLastModifiedTime			char(14),"
										//
										//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}




  //  通常，
 int  sqlScripts_qyImObjRegInfoTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar,  BOOL  bTab1  )
{
	 int			cnt			=	*piCnt;
	 TCHAR		*	pTabName	=	bTab1  ?  CONST_tabName_qyImObjRegInfoTab1  :  CONST_tabName_qyImObjRegInfoTab;

	 //  
  	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","										
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"idStr				char(20) not null,"
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr),"										
										//
										"regTime			char(14),"
										"auditTime			char(14),"
										"tLastModifiedTime	char(14),"
										"tCommitTime		char(14),"
										"bOk				varchar(1),"	//  是否确认, 该标记位已废弃，以审核时间为准
										+  "col0		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col0				varchar(255),"
										+  "col1		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col1				varchar(255),"
										+  "col2		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col2				varchar(255),"
										+  "col3		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col3				varchar(255),"
										+  "col4		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col4				varchar(255),"
										+  "col5		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col5				varchar(255),"
										+  "col6		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col6				varchar(255),"
										+  "col7		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col7				varchar(255),"
										+  "col8		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col8				varchar(255),"
										+  "col9		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col9				varchar(255),"
										+  "col10		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col10				varchar(255),"
										+  "col11		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col11				varchar(255),"
										+  "col12		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col12				varchar(255),"
										+  "col13		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col13				varchar(255),"
										+  "col14		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col14				varchar(255),"
										+  "col15		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col15				varchar(255),"
										+  "col16		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col16				varchar(255),"
										+  "col17		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col17				varchar(255),"
										+  "col18		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col18				varchar(255),"
										+  "col19		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col19				varchar(255),"
										+  "col20		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col20				varchar(255),"
										+  "col21		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col21				varchar(255),"
										+  "col22		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col22				varchar(255),"
										+  "col23		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col23				varchar(255),"
										+  "col24		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col24				varchar(255),"
										+  "col25		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col25				varchar(255),"
										+  "col26		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col26				varchar(255),"
										+  "col27		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col27				varchar(255),"
										+  "col28		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col28				varchar(255),"
										+  "col29		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col29				varchar(255)"
										+	"comment0		varchar(255)"
										")";
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}



 ////////  2008/01/14
 int  sqlScripts_qyMessengerPhoneInfoTab_isMgr(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int			cnt			=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyMessengerPhoneInfoTab;


 	 //  认证信息表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","				
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"uiDevType				int not null,"		//  messenger类型
										"wDevIdStr				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,uiDevType,wDevIdStr),"										
										//
										"messengerPasswd	"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										//
										"idStr				char(20) not null,"		//  对应的Messenger
										//
										"iStatus			int not null,"
										//																				
										"startTime			char(14) not null,"
										"tLastModifiedTime	char(14) not null,"
										//
										+  "col0		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col0				varchar(255),"
										+  "col1		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col1				varchar(255),"
										+  "col2		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col2				varchar(255),"
										+  "col3		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col3				varchar(255),"
										+  "col4		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col4				varchar(255),"
										+  "col5		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col5				varchar(255),"
										+  "col6		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col6				varchar(255),"
										+  "col7		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col7				varchar(255),"
										+  "col8		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col8				varchar(255),"
										+  "col9		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col9				varchar(255),"
										+  "col10		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col10				varchar(255),"
										+  "col11		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col11				varchar(255),"
										+  "col12		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col12				varchar(255),"
										+  "col13		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col13				varchar(255),"
										+  "col14		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col14				varchar(255),"
										+  "col15		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col15				varchar(255),"
										+  "col16		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col16				varchar(255),"
										+  "col17		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col17				varchar(255),"
										+  "col18		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col18				varchar(255),"
										+  "col19		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col19				varchar(255),"
										+  "col20		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col20				varchar(255),"
										+  "col21		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col21				varchar(255),"
										+  "col22		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col22				varchar(255),"
										+  "col23		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col23				varchar(255),"
										+  "col24		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col24				varchar(255),"
										+  "col25		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col25				varchar(255),"
										+  "col26		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col26				varchar(255),"
										+  "col27		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col27				varchar(255),"
										+  "col28		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col28				varchar(255),"
										+  "col29		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col29				varchar(255)"
										//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}

 //  因为wDevIdStr不希望被客户端看到。所以，往往下发一个*来替代。因此，就不能用健值来限制。所以和管理端要有区分
 int  sqlScripts_qyMessengerPhoneInfoTab_isClient(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int			cnt			=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyMessengerPhoneInfoTab;


 	 //  认证信息表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","				
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"uiDevType				int not null,"		//  messenger类型
										"wDevIdStr				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										//  "constraint tmpIndex_"  +  pTabName  +  " unique(misServName,uiDevType,wDevIdStr),"										
										//
										"messengerPasswd	"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										//
										"idStr				char(20) not null,"		//  对应的Messenger
										//
										"iStatus			int not null,"
										//																				
										"startTime			char(14) not null,"
										"tLastModifiedTime	char(14) not null,"
										//
										+  "col0		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col0				varchar(255),"
										+  "col1		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col1				varchar(255),"
										+  "col2		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col2				varchar(255),"
										+  "col3		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col3				varchar(255),"
										+  "col4		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col4				varchar(255),"
										+  "col5		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col5				varchar(255),"
										+  "col6		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col6				varchar(255),"
										+  "col7		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col7				varchar(255),"
										+  "col8		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col8				varchar(255),"
										+  "col9		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col9				varchar(255),"
										+  "col10		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col10				varchar(255),"
										+  "col11		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col11				varchar(255),"
										+  "col12		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col12				varchar(255),"
										+  "col13		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col13				varchar(255),"
										+  "col14		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col14				varchar(255),"
										+  "col15		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col15				varchar(255),"
										+  "col16		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col16				varchar(255),"
										+  "col17		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col17				varchar(255),"
										+  "col18		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col18				varchar(255),"
										+  "col19		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col19				varchar(255),"
										+  "col20		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col20				varchar(255),"
										+  "col21		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col21				varchar(255),"
										+  "col22		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col22				varchar(255),"
										+  "col23		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col23				varchar(255),"
										+  "col24		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col24				varchar(255),"
										+  "col25		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col25				varchar(255),"
										+  "col26		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col26				varchar(255),"
										+  "col27		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col27				varchar(255),"
										+  "col28		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col28				varchar(255),"
										+  "col29		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col29				varchar(255)"
										//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}

 ////////  2008/01/14
 int  sqlScripts_qyPhoneGuestTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int			cnt			=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyPhoneGuestTab;


 	 //  认证信息表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","				
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"uiDevType				int not null,"		//  messenger类型
										"wDevIdStr				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,uiDevType,wDevIdStr),"										
										//
										"messengerPasswd	"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										//
										"idStr_owner		char(20),"		//  这条信息的属主
										//
										"iStatus			int not null,"
										//																				
										"startTime			char(14) not null,"
										"tLastModifiedTime	char(14) not null,"
										//
										+  "col0		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col0				varchar(255),"
										+  "col1		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col1				varchar(255),"
										+  "col2		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col2				varchar(255),"
										+  "col3		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col3				varchar(255),"
										+  "col4		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col4				varchar(255),"
										+  "col5		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col5				varchar(255),"
										+  "col6		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col6				varchar(255),"
										+  "col7		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col7				varchar(255),"
										+  "col8		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col8				varchar(255),"
										+  "col9		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col9				varchar(255),"
										+  "col10		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col10				varchar(255),"
										+  "col11		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col11				varchar(255),"
										+  "col12		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col12				varchar(255),"
										+  "col13		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col13				varchar(255),"
										+  "col14		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col14				varchar(255),"
										+  "col15		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col15				varchar(255),"
										+  "col16		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col16				varchar(255),"
										+  "col17		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col17				varchar(255),"
										+  "col18		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col18				varchar(255),"
										+  "col19		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col19				varchar(255),"
										+  "col20		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col20				varchar(255),"
										+  "col21		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col21				varchar(255),"
										+  "col22		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col22				varchar(255),"
										+  "col23		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col23				varchar(255),"
										+  "col24		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col24				varchar(255),"
										+  "col25		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col25				varchar(255),"
										+  "col26		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col26				varchar(255),"
										+  "col27		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col27				varchar(255),"
										+  "col28		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col28				varchar(255),"
										+  "col29		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col29				varchar(255)"
										//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}



  //  通常，
 int  sqlScripts_qyImOtherRegInfoTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int			cnt			=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyImOtherRegInfoTab;

	 //  
  	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","										
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"uiDevType				int not null,"		//  设备类型, 比如：手机
										"wDevIdStr				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"																	
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,uiDevType,wDevIdStr),"										
										//
										"regTime			char(14),"
										"auditTime			char(14),"
										"tLastModifiedTime	char(14),"
										"tCommitTime		char(14),"
										"bOk				varchar(1),"	//  是否确认, 该标记位已废弃，以审核时间为准
										+  "col0		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col0				varchar(255),"
										+  "col1		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col1				varchar(255),"
										+  "col2		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col2				varchar(255),"
										+  "col3		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col3				varchar(255),"
										+  "col4		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col4				varchar(255),"
										+  "col5		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col5				varchar(255),"
										+  "col6		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col6				varchar(255),"
										+  "col7		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col7				varchar(255),"
										+  "col8		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col8				varchar(255),"
										+  "col9		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col9				varchar(255),"
										+  "col10		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col10				varchar(255),"
										+  "col11		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col11				varchar(255),"
										+  "col12		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col12				varchar(255),"
										+  "col13		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col13				varchar(255),"
										+  "col14		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col14				varchar(255),"
										+  "col15		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col15				varchar(255),"
										+  "col16		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col16				varchar(255),"
										+  "col17		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col17				varchar(255),"
										+  "col18		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col18				varchar(255),"
										+  "col19		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col19				varchar(255),"
										+  "col20		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col20				varchar(255),"
										+  "col21		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col21				varchar(255),"
										+  "col22		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col22				varchar(255),"
										+  "col23		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col23				varchar(255),"
										+  "col24		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col24				varchar(255),"
										+  "col25		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col25				varchar(255),"
										+  "col26		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col26				varchar(255),"
										+  "col27		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col27				varchar(255),"
										+  "col28		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col28				varchar(255),"
										+  "col29		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col29				varchar(255)"
										+	"comment0		varchar(255)"
										")";
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}



 //  
 //  qyMessengerTab qyMessengerRegInfoTab
 int  sqlScripts_qyImGrpInfoTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int			cnt			=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyImGrpInfoTab;

	 //  
  	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","										
										"idStr					char(20) not null,"
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr),"										

										//
										"name					"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"	
										//
										"subtype				int,"												//  2014/01/31
										//
										"idStr_creator			char(20),"										//  2017/07/25
										//
										"startTime				char(14),"
										"tLastModifiedTime		char(14),"
										//
										"col0					varchar(255),"
										"col1					varchar(255),"
										"col2					varchar(255),"
										"col3					varchar(255),"
										"col4					varchar(255),"
										+	"comment0			varchar(255)"
										")";
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}




 int  sqlScripts_qyImGrpMemTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int			cnt			=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyImGrpMemTab;

	 //  
  	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","										
										"misServName		"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"idStr_grp				char(20) not null,"
										"idStr_mem				char(20) not null,"									
										"iRole					int not null,"			//  角色，如群主
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr_grp,idStr_mem),"
										//
										"startTime			char(14),"
										"tLastModifiedTime	char(14),"
										//
										"iStatus			int not null,"
										//
										+	"comment0		varchar(255)"
										")";
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}


 //


 //
 //const char* CONST_tabName_qyImGrpInfoTabEx = "qyimgrpinfotabex";

 int  sqlScripts_qyImGrpInfoExTab(CString* sqlStr, unsigned  int  uiMaxCnt, int* piCnt, char* pAutoincrement, char* p_nchar, char* p_nvarchar)
 {
	 int			cnt = *piCnt;
	 TCHAR* pTabName = CONST_tabName_qyImGrpInfoTabEx;

	 //  
	 sqlStr[cnt] = CString("") + "create table " + pTabName + "("
		 "id	" + pAutoincrement + ","
		 "idStr					char(20),"
		 //
		 "name					" + getDataType(p_nvarchar, 255) + ","		//  varchar(255),"	
		 //
		 "type				int,"												//  2014/01/31
		 //
		 "creator			char(20),"										//  2017/07/25
		 //
		 "tt				int "

		 ")";
	 cnt++;

	 *piCnt = cnt;

	 return  0;

 }



 //  2011/04/02
  int  sqlScripts_qyCustomerServiceObjTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int			cnt			=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyCustomerServiceObjTab;

	 //  
  	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","										
										"idStr					char(20) not null,"
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr),"										

										//
										"uiLangId				int not null,"						//  2011/04/03
										"uiCategoryId			int not null,"						//  2011/04/03			

										//
										"startIp				char(15) not null,"
										"endIp					char(15) not null,"

										//
										"startTime				char(14),"
										"tLastModifiedTime		char(14),"
										//
										"col0					varchar(255),"
										"col1					varchar(255),"
										"col2					varchar(255),"
										"col3					varchar(255),"
										"col4					varchar(255),"
										+	"comment0			varchar(255)"
										")";
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}

 //  2007/11/17, 对wwwQm的一些设置。比如：哪些messenger和group是公开的。
 //
 int  sqlScripts_qyWebContactTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int			cnt			=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyWebContactTab;

	 //  
  	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","										
										"misServName		"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"idStr					char(20) not null,"
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr),"
										//
										"ucbPublic				varchar(1),"
										//
										"grpDisplayName			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"									varchar(255),"	
										"displayName			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							varchar(255),"
										//
										"ucbDefault				varchar(1),"		//  是否为缺省联系人
										"ucbImSwitchable		varchar(1),"
										//
										"startTime				char(14),"
										"tLastModifiedTime		char(14),"
										//
										"iStatus				int not null,"
										//
										+	"comment0			varchar(255)"
										")";
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}

//  2007/11/17, 建一个guestTab, 以记忆来访guest的一些信息，比如：detectedIp, 标识。所使用的messengerId, 对应的序号。来访时间，结束时间。
//
//  对于guest, 是以seqNoStr_guest来标识的。因为，难以获得精确的身份。每次会话时，seqNoStr_guest建立和某临时idStr_tmp的对应
//  seqNoStr_guest是一个流水账, 不停的增1
//  seqNoStr_guest在browser支持cookie时，仍可以通过seqNoStr_guest来关联起来。所以browser应将seqNoStr_guest记入cookie
//  seqNoStr_guest取值范围和idStr一致，是为了方便重用imMsgTab
//  
//
 int  sqlScripts_qyWebGuestTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int			cnt			=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyWebGuestTab;

	 //  
  	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","										
										"misServName		"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"detectedIp				char(15),"
										"displayName		"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"										varchar(255),"			//  标识
										"idStr_tmp				char(20) not null,"	//  临时使用的messengerId
										"seqNoStr_guest			varchar(20) not null,"	//  对应的序号。
										"secretStr				varchar(255),"			//  这里为了将来能支持密码或其他，设立此字段。暂时不用
										//
										"idStr_owner			char(20),"			//  2008/01/16, 这条信息的属主, 可利用属主属性来决定信息的共享或禁止访问等
										//
										"startTime				char(14),"
										"endTime				char(14),"
										"tLastModifiedTime		char(14),"
										//
										"iStatus				int not null,"
										//
										+	"comment0			varchar(255)"
										")";
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}


 int  sqlScripts_qyIpKnowledgeTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int			cnt			=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyIpKnowledgeTab;

	 //  
  	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","										
										"uiType					int not null,"
										"startIp				char(15) not null,"
										"endIp					char(15) not null,"
										"constraint tmpIndex_"  +  pTabName  +  " unique(uiType,startIp,endIp),"
										//
										"wLocation		"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"											varchar(255) not null,"			//  标识
										"iWeight				int not null,"					//  优先级
										//
										"startTime				char(14),"
										"endTime				char(14),"
										"tLastModifiedTime		char(14),"
										//
										"iStatus				int,"
										//
										+	"comment0			varchar(255)"
										")";
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}



 int  sqlScripts_qyImEventTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int	cnt		=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyImEventTab;


	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","
										"helpRand			int	not null,"			//  辅助随机数, 非常重要，2003/11/15
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"idStr				char(20) not null,"
										"detectedIp			char(15) not null,"	//  通信检测到的客户端IP
										"ip					char(15) not null,"	//  客户端自己通报的IP
										"eventType			int	not null,"										
										"cntEventTime		char(14) not null,"		//  传入管理中心的管理中心的时间
										"localCntEventTime	char(14),"			//  传入管理中心的本地的时间
										"localEventTime		char(14) not null,"		//  事件发生的本地的时间
										"comment0			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col0				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"			//  col0-col9含行为者信息
										"col1				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col2				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col3				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col4				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col5				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col6				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col7				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col8				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col9				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										//
										"usrName			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"			//  操作系统里的用户名，2003/11/16加
										//															
										"des0				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"			//  des0-des9含事件本身属性的描述
										"des1				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"
										"des2				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des3				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des4				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des5				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des6				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des7				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des8				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des9				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										//
										"dsnName			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"			//  2007/01/02, 因为远程数据源而引入的字段
										"iStatus			int,"																			//  2006/06/01, 由于要适当的处理事件，而不是简单的进行存储，比如，在报警窗时，故增加了这个功能。							
										//
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr,eventType,localEventTime,helpRand,des0,des1)"
										")";	
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}


  //  这里还没作完，2007/06/23
 int  sqlScripts_qyImMsgTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int	cnt		=	*piCnt;

	 //  消息纪录表
 	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyImMsgTab("
										"id	"  +  pAutoincrement  +  ","
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"idStr_send				char(20) not null,"		//  发送人
										"senderDesc				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"							
										//
										"tSendTime				char(14) not null,"		//  发送时间
										"uiTranNo				int not null,"				//  发送的交易号 
										"uiSeqNo				int not null,"
										//
										"uiType					int  not null,"				//  文件传送等
										//
										"constraint tmpIndex_qyImMsgTab unique(misServName,idStr_send,tSendTime,uiTranNo,uiSeqNo,uiType),"										
										//
										"tStartTime_serv		char(14) not null,"		//  缺省可填"", 在讨论组时有用
										"uiSerialNo				int not null,"				//  缺省为0，在讨论组来发送时，应使用tServTime和uiSerialNo来保证顺序和一些任务的不可分割性。
										//	
										"idStr_recv				char(20) not null,"		//  接收方
										"receiverDesc			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"							
										"iRole					int not null,"				//  接收方可能为讨论组。那么用户接收下来时，应该是作为讨论组的成员才可以。非讨论组讨论时，为0
										//
										"tRecvTime				char(14) not null,"		//  接收时间
										"usRespCode				int not null,"				//  通信的响应码, 在没有时用未定这样的来表示

										//

										//										
										"content0				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content1				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content2				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content3				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content4				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content5				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content6				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content7				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content8				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content9				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										//
										"txtContent0			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent1			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent2			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent3			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent4			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent5			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent6			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent7			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent8			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent9			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										//
										"firstTime					char(14) not null,"		//  此参数，对消息的先后排序，至关重要
										"lastTime					char(14),"
										//
										"iStatus					int,"						//  未绑定，绑定，或未执行，或无法执行
										"tLastModifiedTime			char(14) not null,"		//  最后执行动作的发生时间
										+	"comment0		varchar(255)"
										")";
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}

 //  这里还没作完，2007/06/23
 int  sqlScripts_qyImTaskTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar,  BOOL  bHisTab  )
{
	 int			cnt			=	*piCnt;
	 TCHAR	*		pTabName	=	bHisTab  ?  _T(  "qyImTaskHisTab"  )  :  _T(  "qyImTaskTab"  );

	 //  任务表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"idStr_send				char(20) not null,"		//  发送人
										"senderDesc				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"							
										//
										"tSendTime				char(14) not null,"		//  发送时间
										"uiTranNo				int not null,"				//  发送的交易号 
										"uiSeqNo				int not null,"
										//
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr_send,tSendTime,uiTranNo,uiSeqNo),"										
										//
										"uiContentType			int not null,"				//  2008/05/29, 用在发起者的数据报的uiContentType
										//
										"tStartTime_serv		char(14) not null,"		//  缺省可填"", 在讨论组时有用
										"uiSerialNo				int not null,"				//  缺省为0，在讨论组来发送时，应使用tServTime和uiSerialNo来保证顺序和一些任务的不可分割性。
										//	
										"idStr_recv				char(20) not null,"		//  接收方
										"receiverDesc			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"							
										"iRole					int not null,"				//  接收方可能为讨论组。那么用户接收下来时，应该是作为讨论组的成员才可以。非讨论组讨论时，为0
										//
										"tRecvTime				char(14) not null,"		//  接收时间
										"usRespCode				int not null,"				//  通信的响应码, 在没有时用未定这样的来表示

										
				 						//
										"ibReply				int  not null,"				//  是否回复, 取0或1
										//
										"uiType					int  not null,"				//  文件传送等
										//
										"uiMode					int  not null,"				//  协同模式，比方：发送文件，接收文件, 留言，通知，要回复的通知，可取消和修改的通知（只能在线提交状态）
										//
										"subTypeStr				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  自定义任务类型, 或回复类型。回复类型指 知道。拒绝。等待。。。
										//
										"subject				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  主题
										//
										"content0				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content1				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content2				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content3				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content4				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content5				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content6				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content7				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content8				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"content9				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										//
										"txtContent0			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent1			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent2			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent3			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent4			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent5			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent6			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent7			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent8			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										"txtContent9			"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  [2048];			//  详细内容，以后将逐渐考虑如何将数据有效的分散到若干个表中字段的文件。因为不同的数据库的字段长度不同。不过，分段存储也会造成查询不方便。
										//
										"ibNeedReply			int  not  null,"			//  是否需要回复
										"tEndTime				char(14),"				//  截止时间
										//
										"issuer					"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  发布人
										"tIssueTime				char(14),"											//  发布时间
										//										
										"tStartTime_req			char(14),"				//  对响应时的请求包的对应值
										"uiTranNo_req			int,"
										//
										"firstTime				char(14) not null,"		//  此参数，对消息的先后排序，至关重要
										"lastTime				char(14),"
										//
										"iStatus				int not null,"				//  执行的状态，比如：草稿，未阅，已阅，已回复
										"tLastModifiedTime		char(14) not null,"		//  最后执行动作的发生时间
										//
										"idStr_auditor			char(20),"				//  审核人
										"idStr_replyTo			char(20),"				//  请回复至
										//
										"iProp0					int,"
										"iProp1					int,"
										"iProp2					int,"
										"iProp3					int,"
										"iProp4					int,"
										"iProp5					int,"
										"iProp6					int,"
										"iProp7					int,"
										"iProp8					int,"
										"iProp9					int,"
										//
										"propStr0				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  
										"propStr1				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  
										"propStr2				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  
										"propStr3				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  
										"propStr4				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  
										"propStr5				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  
										"propStr6				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  
										"propStr7				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  
										"propStr8				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	//  
										"propStr9				"  +  getDataType(  p_nvarchar,  255  )  +  " ,"		//  varchar(255),"	// 
										//										
										//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
	 
}


 ///////  2010/08/12

  int  sqlScripts_qyImObjRuleTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int	cnt		=	*piCnt;
	 TCHAR		*	pTabName	=	CONST_tabName_qyImObjRuleTab;


 	 //  主表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","										
										"idStr				char(20) not null,"
										"misServName		"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										//
										"idStr_related		char(20) not null,"
										"uiRuleType			int not null,"													//  
										"usIndex			int not null,"
										//
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr,idStr_related,uiRuleType,usIndex),"		//  2011/01/12								
										//
										"uiCmd				int not null,"
										//
										"startTime			char(14),"
										"tLastModifiedTime	char(14),"
										//
										"iStatus			int not null,"
										//
										"iCol0				int,"
										"iCol1				int,"
										"iCol2				int,"
										"iCol3				int,"
										"iCol4				int,"
										"iCol5				int,"
										"iCol6				int,"
										"iCol7				int,"
										"iCol8				int,"
										"iCol9				int,"
										"col0				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//				varchar(255),"
										"col1				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//				varchar(255),"
										"col2				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//				varchar(255),"
										"col3				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//				varchar(255),"
										"col4				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//				varchar(255),"
										"col5				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//				varchar(255),"
										"col6				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//				varchar(255),"
										"col7				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//				varchar(255),"
										"col8				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//				varchar(255),"
										"col9				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//				varchar(255),"
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;
	 
	 *piCnt  =  cnt;

	 return  0;
	 
}



    //  这里时用来内部处理的计划性表. 由gui等将计划存入数据库, 由某线程取出, 并做处理, 处理完即可删除. 2007/09/03
	//  临时用, 格式不固定. 进用于内部处理
	//  比如:可以提交一个要求10秒后刷新一下成员变量的组.
	//
 int  sqlScripts_qyImInternalSchedulerTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int	cnt		=	*piCnt;

	 //  计划表,  比如
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyImInternalSchedulerTab("
										"id	"  +  pAutoincrement  +  ","
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"idStr					char(20) not null,"		//  发送人
										"uiType					int not null,"				//  类型										
										"tSchedulerTime			char(14) not null,"
										//										
										"firstTime				char(14) not null,"		//  此参数，对消息的先后排序，至关重要
										"lastTime				char(14),"
										//
										"iStatus				int not null,"				//  执行的状态，比如：草稿，未阅，已阅，已回复
										"tLastModifiedTime		char(14) not null,"		//  最后执行动作的发生时间
										//																				//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
}


  //  2009/01/29. 视频会议的运行信息缓存。用于视频活动的异常恢复. 用在isClient
 //
 int  sqlScripts_qyTmpAvTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int	cnt		=	*piCnt;

	 //  任务表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyTmpAvTab("
										"id	"  +  pAutoincrement  +  ","
										"iTaskId				int not null,"
										"uiType					int not null,"				//  类型
										"index_taskAvFrom		int not null,"				//	PROC_TASK_AV中的TASK_AV_FROM的索引
										"name					varchar(255) not null,"		//  
										"val0					varchar(254),"
										"val1					varchar(254),"
										"val2					varchar(254),"
										"val3					varchar(254),"
										"val4					varchar(254),"
										"val5					varchar(254),"
										"val6					varchar(254),"
										"val7					varchar(254),"
										"val8					varchar(254),"
										"val9					varchar(254),"
										"val10					varchar(254),"
										"val11					varchar(254),"
										"val12					varchar(254),"
										"val13					varchar(254),"
										"val14					varchar(254),"
										"val15					varchar(254),"
										"val16					varchar(254),"
										"val17					varchar(254),"
										"val18					varchar(254),"
										"val19					varchar(254),"
										//
										"qnmVerStr				char(8),"				//  2009/01/31. messenger的版本号。不同的版本号不能互用，要及时清除非自己版本号的临时记录。
										//
										"firstTime				char(14) not null,"		//  此参数，对消息的先后排序，至关重要
										"tLastModifiedTime		char(14) not null,"		//  最后执行动作的发生时间
										//																				//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
}



 //  这里还没作完，2007/06/23
 int  sqlScripts_qyImStatusTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int	cnt		=	*piCnt;

	 //  任务表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyImStatusTab("
										"id	"  +  pAutoincrement  +  ","
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"idStr					char(20) not null,"		//  发送人
										"uiType					int not null,"				//  类型
										"tLastRefreshedTime		char(14) not null,"		//  发送时间
										//										
										"constraint tmpIndex_qyImStatusTab unique(misServName,idStr),"										
										//																				//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
}





  //  GSM虚拟设备状态表，2008/01/24
 int  sqlScripts_qyVDevComTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int		cnt			=	*piCnt;
	 TCHAR	*	pTabName	=	CONST_tabName_qyVDevComTab;


	 //  任务表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"idStr					char(20) not null,"		//  该设备的代表
										"wDevIdStr				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  设备标识。dev/COM1，dev/COM2。。。
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr,wDevIdStr),"										
										"name					"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  设备名称。COM1，COM2。。。
										"model					"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										"smsc					varchar(255),"
										"iStatus				int,"
										//
										"startTime			char(14),"						//  首次记录时间
										"endTime			char(14),"						//  最近记录时间
										//																				//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
}

  //  GSM虚拟设备状态表，2008/01/24
 int  sqlScripts_qySmContactTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int		cnt			=	*piCnt;
	 TCHAR	*	pTabName	=	CONST_tabName_qySmContactTab;


	 //  任务表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"idStr					char(20) not null,"
										"wDevIdStr				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  设备标识。dev/COM1，dev/COM2。。。
										"ucbDefaultSmServer		varchar(1) not null,"											//  是否为缺省Sm发送服务器
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr,wDevIdStr,ucbDefaultSmServer),"										
										"cusName				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  别名，给管理员自己看							
										//
										"ucbPublic				varchar(1),"
										//
										"idStr_contact			char(20) not null,"											//  messenger id
										//
										"displayName			"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  对外显示名.
										//
										"ucbDefault				varchar(1),"		//  是否为缺省联系人
										"ucbImSwitchable		varchar(1),"
										//
										//
										"iStatus				int,"
										//
										"startTime				char(14),"													//  首次记录时间
										"endTime				char(14),"													//  最近记录时间
										//																						//
										"comment0				varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
}


 //////////////

 int  sqlScripts_qyDynBmpTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int		cnt			=	*piCnt;
	 TCHAR	*	pTabName	=	CONST_tabName_qyDynBmpTab;


	 //  任务表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"idStr					char(20) not null,"		//  该设备的代表
										"uiObjType				int not null,"
										"usIndex				int not null,"
										"constraint tmpIndex_"  +  pTabName  +  " unique(misServName,idStr,uiObjType,usIndex),"										
										"name					"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  设备名称。COM1，COM2。。。
										"cusname				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  设备名称。COM1，COM2。。。
										"iStatus				int,"
										//
										"startTime			char(14),"						//  首次记录时间
										"endTime			char(14),"						//  最近记录时间
										//																				//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
}


  int  sqlScripts_qyDynBmpRuleTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  )
{
	 int		cnt			=	*piCnt;
	 TCHAR	*	pTabName	=	CONST_tabName_qyDynBmpRuleTab;


	 //  任务表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table "  +  pTabName  +  "("
										"id	"  +  pAutoincrement  +  ","
										//
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"idStr					char(20) not null,"				//  
										//
										"idStr_visitor			char(20) not null,"
										//
										"constraint tmpIndex_qyDynBmpRuleTab unique(misServName,idStr,idStr_visitor),"										
										//
										//  "uiRuleType				int not null,"					//  2009/09/17
										"uiRuleCmd				int not null,"						//  2009/09/17
										//										
										"iStatus				int,"
										//
										"startTime				char(14),"						//  
										"endTime				char(14),"						//  
										//																				//
										"comment0				varchar(255)"										
										")";	 
	 cnt  ++  ;

	 *piCnt  =  cnt;

	 return  0;
}


 ////////////



 int  makeDb_netMc(  LPCWSTR  dbTypeName,  char  *  servIp,  LPCWSTR  uid,  LPCWSTR  pwd,  LPCWSTR  dbName,  int  iServiceId,  char  *  dbVer  )
{
	 int			iErr				=	-1;
	 CDatabase	*	pDb					=	NULL;
	 //  char	*	dsnName				=	"testDsn";
	 //  char	*	dsnName				=	CONST_netMcDsn;
	 TCHAR			connectStrBuf[512]	=	_T(  ""  );
	 char		*	pAutoincrement		=	NULL;
	 char		*	p_nchar				=	NULL;
	 char		*	p_nvarchar			=	NULL;
	 CString		sqlStr[512];
	 int			cnt					=  0;
	 int			i;
	 int			iDbType				=	0;
	 TCHAR			sqlBuf[4096];
	 char			buf[1024];

	 if  (  !wcsicmp(  dbTypeName,  CString(  CONST_dbTypeName_access  )  )  )  {
		 _sntprintf(  connectStrBuf,  mycountof(  connectStrBuf  ),  CString(  CONST_connectStrFmt_access  ),  dbName  );
		 pAutoincrement		=  CONST_autoincrement_access;
		 p_nchar			=  CONST_nchar_access;
		 p_nvarchar			=  CONST_nvarchar_access;
		}
	 else  {
			_sntprintf(  connectStrBuf,  mycountof(  connectStrBuf  ),  CString(  CONST_connectStrFmt_sqlServer  ),  CString(  servIp  ),  uid,  pwd,  dbName  );
			pAutoincrement  =  CONST_autoincrement_sqlServer;
			p_nchar			=  CONST_nchar_sqlServer;
			p_nvarchar		=  CONST_nvarchar_sqlServer;
			iDbType			=  CONST_dbType_sqlServer;	
	 }


	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyTestTab("
										"col0				varchar(30) primary key,"
										"col_int			int,"
										"col_Integer		Integer"
										")";
	 cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyMcTab("
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyMcUsrLogTab("
										"usrName			varchar(30) not null,"
										"op					varchar(255) not null,"
										"opTime				char(14) not null,"
										"result				varchar(2) not null"
										")";
	 cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyMcUsrTab("
										"name				varchar(30) primary key,"
										"passwd				varchar(32),"
										"grpNames			varchar(255) not null"
										")";
	 cnt  ++  ;
	 	 
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcGrpCfgTab("
										"startIp			char(15) primary key,"
										"endIp				char(15) not null,"
										"grpNames			varchar(255) not null"
										")";
	 cnt  ++  ;


	 //  以下是Oracle数据库前的建库工作
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcTab("
										"mac0				char(12) primary key,"
										"mac1				char(12),"
										"mac2				char(12),"
										"otherMacs			varchar(255),"
										"nMacs				varchar(4) not null,"
										"ip					char(15) not null,"
										"ip0				char(15),"
										"ip1				char(15),"
										"ip2				char(15),"										
										"qwmVer				char(8),"
										"startTime			char(14) not null,"
										"lastCommTime		char(14) not null,"
										"uiLangId			int,"						//  2005/01/22, 语种
										"iPlatformId		int,"						//  2005/01/22，操作系统类型
										"winDir				varchar(255),"				//  2005/01/22, Windows目录
										"osName				varchar(64),"
										"servicePack		varchar(64),"				//  2003/09/12
										"pcName				varchar(64),"
										"curUsrName			varchar(255),"
										"proxyServer		varchar(255),"
										"ucbAddedManually	varchar(1),"				//  表是否手工添加，2004/04/11加入	
										"col0				varchar(255),"
										"col1				varchar(255),"
										"col2				varchar(255),"
										"col3				varchar(255),"
										"col4				varchar(255),"
										"col5				varchar(255),"
										"col6				varchar(255),"
										"col7				varchar(255),"
										"col8				varchar(255),"
										"col9				varchar(255),"
										"col10				varchar(255),"
										"col11				varchar(255),"
										"col12				varchar(255),"
										"col13				varchar(255),"
										"col14				varchar(255),"
										"col15				varchar(255),"
										"col16				varchar(255),"
										"col17				varchar(255),"
										"col18				varchar(255),"
										"col19				varchar(255),"
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;


	 //  2004/05/15为了存放操作系统补丁而加
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcSpTab("
										"mac0				char(12) not null,"
										"uiLangId			int,"						//  2005/01/22, 语种
										"iPlatformId		int,"						//  2005/01/22，操作系统类型
										"winDir				varchar(255),"				//  2005/01/22, Windows目录
										"osName				varchar(64) not null,"
										"servicePack		varchar(64),"				//  2003/09/12
										"spName				varchar(32) not null,"
										"firstTime			char(14) not null,"
										"lastTime			char(14) not null,"
										"comment0			varchar(255),"
										"constraint tmpPcSpIndex unique(mac0,osName,spName)"
										")";
	 cnt  ++  ;


	 //  2004/05/15为建立一个容易记忆的别名表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyCusNameTab("
										"id	"  +  pAutoincrement  +  ","
										"iType				int not null,"
										"uiLangId			int not null,"						//  保留
										"objName0			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255) not null,"
										"cusName0			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										//					//  从到9都是为了规范用户信息而引入, 2006/09/02
										"objName1			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"cusName1			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										"objName2			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"cusName2			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										"objName3			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"cusName3			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										"objName4			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"cusName4			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										"objName5			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"cusName5			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										"objName6			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"cusName6			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										"objName7			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"cusName7			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"							
										"constraint tmpCusNameIndex unique(iType,uiLangId,objName0,objName1,objName2,objName3,objName4,objName5,objName6,objName7),"
										//
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;


	 //  2005/01/22为补丁管理建立补丁安装标准的表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyOsSpTab("
										 "id	"  +  pAutoincrement  +  ","
										"iType				int  not  null,"
										"iPlatformId		int not null,"
										"prog				varchar(255),"
										"servicePack		varchar(255),"
										"spName				varchar(255),"
										"uiLangId			int,"
										"cusName			varchar(255),"
										"des0				varchar(255),"
										"url				varchar(255),"
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;


	 /*
	 //  2006/05/21,  {
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcWindowsUpdatePolicyTab("
										 "id	"  +  pAutoincrement  +  ","
										 "ucbRule					varchar(1),"	//  是否规则
										"mac0								char(12) primary key,"
										"RescheduleWaitTime					int,"
										"RescheduleWaitTimeEnabled			int,"
										"NoAutoRebootWithLoggedOnUsers		int,"
										"NoAutoUpdate						int,"
										"AUOptions							int,"
										"ScheduledInstallDay				int,"
										"ScheduledInstallTime				int,"
										"UseWUServer						int,"
										//
										"WUServer							varchar(255),"
										"WUStatusServer						varchar(255),"
										"ElevateNonAdmins					int,"
										"TargetGroupEnabled					int,"
										"TargetGroup						varchar(255),"
										//
										"AutoUpdate_AUOptions				int,"
										"AutoUpdate_ScheduledInstallDay		int,"
										"AutoUpdate_ScheduledInstallTime	int,"
										"firstTime							char(14) not null,"
										"lastTime							char(14) not null,"
										"iStatus							int,"				//  未绑定，绑定，或未执行，或无法执行
										//
										"iCol0								int,"
										"iCol1								int,"
										"iCol2								int,"
										"iCol3								int,"
										"iCol4								int,"
										"iCol5								int,"
										"iCol6								int,"
										"iCol7								int,"
										"iCol8								int,"
										"iCol9								int,"
										"col0								varchar(255),"
										"col1								varchar(255),"
										"col2								varchar(255),"
										"col3								varchar(255),"
										"col4								varchar(255),"
										"col5								varchar(255),"
										"col6								varchar(255),"
										"col7								varchar(255),"
										"col8								varchar(255),"
										"col9								varchar(255),"
										"comment0							varchar(255)"
										")";
	 cnt  ++  ;


	 //  }
	 */


	 //  2005/6/25
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qwmSvrTab("
										"mac0				char(12) primary key,"
										"qwmVer				char(8),"
										"seqNo				varchar(255),"
										"firstTime			char(14),"
										"lastTime			char(14),"
										"iCol0				int,"
										"iCol1				int,"
										"iCol2				int,"
										"iCol3				int,"
										"iCol4				int,"
										"iCol5				int,"
										"iCol6				int,"
										"iCol7				int,"
										"iCol8				int,"
										"iCol9				int,"
										"col0				varchar(255),"
										"col1				varchar(255),"
										"col2				varchar(255),"
										"col3				varchar(255),"
										"col4				varchar(255),"
										"col5				varchar(255),"
										"col6				varchar(255),"
										"col7				varchar(255),"
										"col8				varchar(255),"
										"col9				varchar(255),"
										 "comment0			varchar(255)"
										 ")";
	 cnt  ++  ;


	 //  2004/04/11添加此表为存放已扫描出的端口上显示的手工指定的设备
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qnmMacDesTab("
										"mac				char(12) primary key,"
										"ip					char(15),"
										"devType			varchar(64),"
										"des0				varchar(255),"
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;
	 
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcEventTab("
										//  "id					autoincrement,"
										"id	"  +  pAutoincrement  +  ","
										"helpRand			int	not null,"			//  辅助随机数, 非常重要，2003/11/15
										"mac0				char(12) not null,"
										"mac1				char(12),"
										"mac2				char(12),"
										"ip					char(15) not null,"
										"productName		"  +  getDataType(  p_nvarchar,  128  )  +  ","		//	varchar(128),"			//  网络设备型号，2004/03/01增加
										"ownerName			"  +  getDataType(  p_nvarchar,  64  )  +  ","		//	varchar(64),"
										"officeName			"  +  getDataType(  p_nvarchar,  64  )  +  ","		//  varchar(64),"
										"subOfficeName		"  +  getDataType(  p_nvarchar,  64  )  +  ","		//  varchar(64),"
										"eventType			int	not null,"										
										"cntEventTime		char(14) not null,"		//  传入管理中心的管理中心的时间
										"localCntEventTime	char(14),"			//  传入管理中心的本地的时间
										"localEventTime		char(14) not null,"		//  事件发生的本地的时间
										"comment0			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col0				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"			//  col0-col9含行为者信息
										"col1				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col2				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col3				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col4				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col5				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col6				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col7				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col8				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col9				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"usrName			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"			//  操作系统里的用户名，2003/11/16加
										"connectedMac		char(12),"			//  为了增加对网络设备事件的描述，增加这两项，2004/04/14
										"portIfIndex		int,"					//  以前的定义："portIfIndex		varchar(32),"										
										"des0				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"			//  des0-des9含事件本身属性的描述
										"des1				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"
										"des2				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des3				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des4				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des5				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des6				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des7				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des8				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des9				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										//
										"dsnName			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"			//  2007/01/02, 因为远程数据源而引入的字段
										"iStatus			int,"																			//  2006/06/01, 由于要适当的处理事件，而不是简单的进行存储，比如，在报警窗时，故增加了这个功能。							
										//
										"constraint tmpPcEventIndex unique(mac0,eventType,localEventTime,helpRand,des0,des1)"
										")";
	
	 cnt  ++  ;

	 
	 //  {  //  2006/03/07, 为了方便安检结果的处理，故复制了一个专用的表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcSecChkEventTab("
										//  "id					autoincrement,"
										"id	"  +  pAutoincrement  +  ","
										"helpRand			int	not null,"			//  辅助随机数, 非常重要，2003/11/15
										"mac0				char(12) not null,"
										"mac1				char(12),"
										"mac2				char(12),"
										"ip					char(15) not null,"
										"productName		"  +  getDataType(  p_nvarchar,  128  )  +  ","		//  varchar(128),"			//  网络设备型号，2004/03/01增加
										"ownerName			"  +  getDataType(  p_nvarchar,  64  )  +  ","		//  varchar(64),"
										"officeName			"  +  getDataType(  p_nvarchar,  64  )  +  ","		//  varchar(64),"
										"subOfficeName		"  +  getDataType(  p_nvarchar,  64  )  +  ","		//  varchar(64),"
										"eventType			int	not null,"										
										"cntEventTime		char(14) not null,"		//  传入管理中心的管理中心的时间
										"localCntEventTime	char(14),"			//  传入管理中心的本地的时间
										"localEventTime		char(14) not null,"		//  事件发生的本地的时间
										"comment0			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col0				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"			//  col0-col9含行为者信息
										"col1				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col2				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col3				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col4				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col5				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col6				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col7				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col8				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"col9				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"usrName			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"			//  操作系统里的用户名，2003/11/16加
										"connectedMac		char(12),"			//  为了增加对网络设备事件的描述，增加这两项，2004/04/14
										"portIfIndex		int,"					//  以前的定义："portIfIndex		varchar(32),"										
										"des0				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"			//  des0-des9含事件本身属性的描述
										"des1				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des2				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des3				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des4				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des5				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des6				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des7				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des8				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										"des9				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"
										//
										"dsnName			"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"			//  2007/01/02, 因为远程数据源而引入的字段
										"iStatus			int,"																			//  2006/06/01, 由于要适当的处理事件，而不是简单的进行存储，比如，在报警窗时，故增加了这个功能。							
										//
										"constraint tmpPcSecChkEventIndex unique(mac0,eventType,localEventTime,helpRand)"
										")";
	
	 cnt  ++  ;
	 //  }

	 
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qnmIpScanTab("
										"startIp			char(15) primary key,"
										"endIp				char(15) not null,"
										"officeName			varchar(64),"
										"subOfficeName		varchar(64),"
										"flg				varchar(2)"
										")";
	 cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qnmScannedIpTab("
										"ip					char(15) primary key,"
										"tmpIp15			char(15),"
										"officeName			varchar(64),"
										"subOfficeName		varchar(64),"
										"mac				char(12),"
										"firstScannedTime	char(14) not null,"
										"lastScannedTime	char(14) not null"
										")";
	 cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qnmPcGrpTab("
										"startIp			char(15) primary key,"		//  ip12格式
										"endIp				char(15) not null,"			//  ip12格式
										"officeName			varchar(64),"
										"subOfficeName		varchar(64),"
										"lanName			varchar(16),"
										"ucbStopSnmpScan	varchar(1),"					//  是否Snmp扫描, 2004/04/21
										"ucbStopMacScan		varchar(1),"					//  是否Mac扫描, 2004/04/21
										"glCntIp			char(15),"					//  ip12格式
										"mac				char(12),"
										"fBwd				varchar(1),"					//  非本网段
										"flg				varchar(2)"										
										")";
	 cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcRegInfoTab("
										"mac0				char(12) primary key,"
										"regTime			char(14),"
										"auditTime			char(14),"
										"bOk				varchar(1),"	//  是否确认, 该标记位已废弃，以审核时间为准
										"ownerName			varchar(64),"
										"officeName			varchar(64),"
										"subOfficeName		varchar(64),"
										+  "col0		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col0				varchar(255),"
										+  "col1		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col1				varchar(255),"
										+  "col2		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col2				varchar(255),"
										+  "col3		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col3				varchar(255),"
										+  "col4		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col4				varchar(255),"
										+  "col5		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col5				varchar(255),"
										+  "col6		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col6				varchar(255),"
										+  "col7		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col7				varchar(255),"
										+  "col8		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col8				varchar(255),"
										+  "col9		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col9				varchar(255),"
										+  "col10		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col10				varchar(255),"
										+  "col11		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col11				varchar(255),"
										+  "col12		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col12				varchar(255),"
										+  "col13		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col13				varchar(255),"
										+  "col14		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col14				varchar(255),"
										+  "col15		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col15				varchar(255),"
										+  "col16		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col16				varchar(255),"
										+  "col17		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col17				varchar(255),"
										+  "col18		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col18				varchar(255),"
										+  "col19		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col19				varchar(255),"
										+  "col20		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col20				varchar(255),"
										+  "col21		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col21				varchar(255),"
										+  "col22		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col22				varchar(255),"
										+  "col23		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col23				varchar(255),"
										+  "col24		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col24				varchar(255),"
										+  "col25		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col25				varchar(255),"
										+  "col26		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col26				varchar(255),"
										+  "col27		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col27				varchar(255),"
										+  "col28		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col28				varchar(255),"
										+  "col29		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col29				varchar(255)"
										+	"comment0		varchar(255)"
										")";
	 cnt  ++  ;


	 //  qyPcRegInfoTab1为提供已审核的重复注册信息的存储空间，和qyPcRegInfoTab完全雷同
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcRegInfoTab1("
										"mac0				char(12) primary key,"
										"regTime			char(14),"
										"auditTime			char(14),"
										"bOk				varchar(1),"	//  是否确认, 该标记位已废弃，以审核时间为准
										"ownerName			varchar(64),"
										"officeName			varchar(64),"
										"subOfficeName		varchar(64),"
										+  "col0		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col0				varchar(255),"
										+  "col1		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col1				varchar(255),"
										+  "col2		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col2				varchar(255),"
										+  "col3		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col3				varchar(255),"
										+  "col4		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col4				varchar(255),"
										+  "col5		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col5				varchar(255),"
										+  "col6		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col6				varchar(255),"
										+  "col7		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col7				varchar(255),"
										+  "col8		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col8				varchar(255),"
										+  "col9		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col9				varchar(255),"
										+  "col10		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col10				varchar(255),"
										+  "col11		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col11				varchar(255),"
										+  "col12		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col12				varchar(255),"
										+  "col13		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col13				varchar(255),"
										+  "col14		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col14				varchar(255),"
										+  "col15		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col15				varchar(255),"
										+  "col16		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col16				varchar(255),"
										+  "col17		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col17				varchar(255),"
										+  "col18		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col18				varchar(255),"
										+  "col19		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col19				varchar(255),"
										+  "col20		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col20				varchar(255),"
										+  "col21		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col21				varchar(255),"
										+  "col22		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col22				varchar(255),"
										+  "col23		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col23				varchar(255),"
										+  "col24		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col24				varchar(255),"
										+  "col25		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col25				varchar(255),"
										+  "col26		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col26				varchar(255),"
										+  "col27		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col27				varchar(255),"
										+  "col28		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col28				varchar(255),"
										+  "col29		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  "col29				varchar(255)"
										+	"comment0		varchar(255)"
										")";
	 cnt  ++  ;


	 //  2004/07/26加
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcAssetTab("
 										"id	"  +  pAutoincrement  +  ","
										"mac0				char(12) not null,"				//  	
										"uiLangId			int,"								//  2005/01/24, 语种
										"iPlatformId		int not null,"						//  操作系统类型
										"winDir				varchar(255) not null,"				//  Windows目录
										"startTime			char(14),"						//  首次记录时间
										"endTime			char(14),"						//  最近记录时间
										"lastUsrName		"	+	getDataType(  p_nvarchar,  64  )	+  ","		//  varchar(64),"						//  最近检查的登录用户名
										"iType				int not null,"						//  组件类型
										"name				"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"						//  名称
										"maker				"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"						//  制造商
				 						"makeTime			char(14),"						//  出厂时间
										"idStr				"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"						//  序号
				 						"installTime		char(14),"						//  安装时间
										"iSessionId			int not null,"						//  会话Id, 2004/09/11加
										"iParam0			int,"
										"iParam1			int,"
										"iParam2			int,"
										"iParam3			int,"
										"iParam4			int,"
										"iParam5			int,"
										"iParam6			int,"
										"iParam7			int,"
										"iParam8			int,"
										"iParam9			int,"
										"iParam10			int,"
										"iParam11			int,"
										"iParam12			int,"
										"iParam13			int,"
										"iParam14			int,"
										"iParam15			int,"
										"iParam16			int,"
										"iParam17			int,"
										"iParam18			int,"
										"iParam19			int,"
										"paramStr0			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"paramStr1			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"paramStr2			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"paramStr3			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"paramStr4			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"paramStr5			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"paramStr6			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"paramStr7			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"paramStr8			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"paramStr9			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"locationInfo		"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"	//  locationInformation
										"iProp0				int,"
										"iProp1				int,"
										"iProp2				int,"
										"iProp3				int,"
										"iProp4				int,"
										"iProp5				int,"
										"iProp6				int,"
										"iProp7				int,"
										"iProp8				int,"
										"iProp9				int,"
										"propStr0			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"propStr1			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"propStr2			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"propStr3			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"propStr4			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"propStr5			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"propStr6			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"propStr7			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"propStr8			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"propStr9			"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"
										"des0				"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"						//  描述
										"des1				"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"						//  描述
										"des2				"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"						//  描述
										"des3				"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"						//  描述
										"des4				"	+	getDataType(  p_nvarchar,  255  )	+  ","		//  varchar(255),"						//  描述
										"comment0			varchar(255)"						//  备注
										")";
	 cnt  ++  ;


	 //  2005/05/24
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcAdapterTab("
										"id	"  +  pAutoincrement  +  ","
										"ucbRule					varchar(1),"	//  是否规则
										"uiType						int not null,"	//  区分代理服务器和网卡配置等类型
										//
										"mac0						char(12) not null,"
										//										
										"des0						varchar(255),"	//  "connectionName				varchar(32),"
										"des1						varchar(255),"
										"des2						varchar(255),"
										//										
										"devIdStr					varchar(255),"	//  2005/05/29
										"devIndex					int,"			//  2005/05/29
										"devDesc					varchar(255),"	//  2005/05/29,  设备名称
										//
										"uiAdapterType				int,"
										"mac						char(12),"
										"ipBuf						varchar(64),"
										"ipMaskBuf					varchar(64),"
										"gatewayBuf					varchar(64),"
										"gatewayMetricBuf			varchar(32),"	//  2005/06/07
										//
										"ucbDhcpEnabled				varchar(1),"
										"dhcpServerIp				char(15),"
										"lLeaseObtained				int,"
										"ucbHaveWins				varchar(1),"
										"primaryWinsServerIp		char(15),"
										"secondaryWinsServerIp		char(15),"
										//
										"ucbAutoDns					varchar(1),"		//  2005/06/15
										"dnsBuf						varchar(64),"
										//
										"curUsrName					varchar(64),"
										"proxyBuf					varchar(128),"
										//
										"iParam0			int,"
										"iParam1			int,"
										"iParam2			int,"
										"iParam3			int,"
										"iParam4			int,"
										"iParam5			int,"
										"iParam6			int,"
										"iParam7			int,"
										"iParam8			int,"
										"iParam9			int,"
										"iParam10			int,"
										"iParam11			int,"
										"iParam12			int,"
										"iParam13			int,"
										"iParam14			int,"
										"iParam15			int,"
										"iParam16			int,"
										"iParam17			int,"
										"iParam18			int,"
										"iParam19			int,"
										"paramStr0			varchar(255),"
										"paramStr1			varchar(255),"
										"paramStr2			varchar(255),"
										"paramStr3			varchar(255),"
										"paramStr4			varchar(255),"
										"paramStr5			varchar(255),"
										"paramStr6			varchar(255),"
										"paramStr7			varchar(255),"
										"paramStr8			varchar(255),"
										"paramStr9			varchar(255),"
										"locationInfo		varchar(255),"	//  locationInformation
										"iProp0				int,"
										"iProp1				int,"
										"iProp2				int,"
										"iProp3				int,"
										"iProp4				int,"
										"iProp5				int,"
										"iProp6				int,"
										"iProp7				int,"
										"iProp8				int,"
										"iProp9				int,"
										//  2006/05/21，增加下面10项
										"iProp10				int,"
										"iProp11				int,"
										"iProp12				int,"
										"iProp13				int,"
										"iProp14				int,"
										"iProp15				int,"
										"iProp16				int,"
										"iProp17				int,"
										"iProp18				int,"
										"iProp19				int,"
										//
										"propStr0			varchar(255),"
										"propStr1			varchar(255),"
										"propStr2			varchar(255),"
										"propStr3			varchar(255),"
										"propStr4			varchar(255),"
										"propStr5			varchar(255),"
										"propStr6			varchar(255),"
										"propStr7			varchar(255),"
										"propStr8			varchar(255),"
										"propStr9			varchar(255),"
										//  2006/05/21，增加下面10项
										"propStr10			varchar(255),"
										"propStr11			varchar(255),"
										"propStr12			varchar(255),"
										"propStr13			varchar(255),"
										"propStr14			varchar(255),"
										"propStr15			varchar(255),"
										"propStr16			varchar(255),"
										"propStr17			varchar(255),"
										"propStr18			varchar(255),"
										"propStr19			varchar(255),"
										//
										"firstTime					char(14),"
										"lastTime					char(14),"
										"iStatus					int,"				//  未绑定，绑定，或未执行，或无法执行
										//
										//  "iCol0						int,"
										//  "iCol1						int,"
										//  "iCol2						int,"
										//  "iCol3						int,"
										//  "iCol4						int,"
										//  "iCol5						int,"
										//  "iCol6						int,"
										//  "iCol7						int,"
										//  "iCol8						int,"
										//  "iCol9						int,"
										//  "colStr0					varchar(255),"
										//  "colStr1					varchar(255),"
										//  "colStr2					varchar(255),"
										//  "colStr3					varchar(255),"
										//  "colStr4					varchar(255),"
										//  "colStr5					varchar(255),"
										//  "colStr6					varchar(255),"
										//  "colStr7					varchar(255),"
										//  "colStr8					varchar(255),"
										//  "colStr9					varchar(255),"
										//
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;

	 //  2005/07/07
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcProcessTab("
										"id	"  +  pAutoincrement  +  ","
										"uiType						int not null,"	//  区分代理服务器和网卡配置等类型
										"mac0						char(12) not null,"			//  	
										"uiLangId					int,"							//  2005/01/24, 语种
										"iPlatformId				int not null,"					//  操作系统类型
										"winDir						varchar(255) not null,"			//  Windows目录
										"dwPid						int not null,"
										"moduleName					"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"					//  程序名
										"modulePath					"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"					//  运行路径	
										"myModulePath				"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"					//  供分析用的路径, 2006/04/16
										"cmdLine					"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"					//  命令行参数, 2006/09/06
										"dwPpid						int,"							//  父进程
										"dwCpuPercent				int,"							//  CPU占有率
										"dwCpuTime					int,"							//  CPU时间
										"dwMemInK					int,"							//  内存大小
										"dwVmemInK					int,"							//  虚存大小
										"dwHandles					int,"							//  句柄数
										"dwThreads					int,"							//  线程数
										//
										"iProp0						int,"
										"iProp1						int,"
										"iProp2						int,"
										"iProp3						int,"
										"iProp4						int,"
										"iProp5						int,"
										"iProp6						int,"
										"iProp7						int,"
										"iProp8						int,"
										"iProp9						int,"
										"propStr0					varchar(255),"
										"propStr1					varchar(255),"
										"propStr2					varchar(255),"
										"propStr3					varchar(255),"
										"propStr4					varchar(255),"
										"propStr5					varchar(255),"
										"propStr6					varchar(255),"
										"propStr7					varchar(255),"
										"propStr8					varchar(255),"
										"propStr9					varchar(255),"
										//
										"firstTime					char(14),"
										"lastTime					char(14),"
										"iStatus					int,"				//  未绑定，绑定，或未执行，或无法执行
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;


	 /////////////
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcNetFlowTab("
										"id	"  +  pAutoincrement  +  ","
										"uiType						int not null,"	//  区分代理服务器和网卡配置等类型
										"mac0						char(12) not null,"			//  	
										"uiLangId					int,"							//  2005/01/24, 语种
										"iPlatformId				int not null,"					//  操作系统类型
										"winDir						varchar(255) not null,"			//  Windows目录
										//
										"dwIndex					int,"							//  很多成员摘自MIB_IFROW
										"dwType						int,"
										"dwSpeed					int,"
										"dwInSpeed					int,"							//  入流量, 自定义
										"dwOutSpeed					int,"							//  出流量, 自定义
										"dwPhysAddrLen				int,"
										"bPhysAddr					varchar(255),"					//  BYTE  bPhysAddr[CONST_myMAXLEN_PHYSADDR];
				 						//								
										"dwMtu						int,"
										"dwAdminStatus				int,"
										"dwOperStatus				int,"
										"dwLastChange				int,"
										"dwInOctets					int,"
										"dwInUcastPkts				int,"
										"dwInNUcastPkts				int,"
										"dwInDiscards				int,"
										"dwInErrors					int,"
										"dwInUnknownProtos			int,"
										"dwOutOctets				int,"
										"dwOutUcastPkts				int,"
										"dwOutNUcastPkts			int,"
										"dwOutDiscards				int,"
										"dwOutErrors				int,"
										"dwOutQLen					int,"
										//
										"ucWarnCnt					int,"
										//
										"firstTime					char(14),"
										"lastTime					char(14),"
										"iStatus					int,"				//  未绑定，绑定，或未执行，或无法执行
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;
	 //////////////


	 //  2007/02/14
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcNetShareTab("
										"id	"  +  pAutoincrement  +  ","
										"uiType						int not null,"	//  区分代理服务器和网卡配置等类型
										"mac0						char(12) not null,"			//  	
										"uiLangId					int,"							//  2005/01/24, 语种
										"iPlatformId				int not null,"					//  操作系统类型
										"winDir						varchar(255) not null,"			//  Windows目录
										//
										"shi502_netname				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"					//  					
										"shi502_path				"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"					//  
										"shi502_type				int,"
										//
										"firstTime					char(14),"
										"lastTime					char(14),"
										"iStatus					int,"				
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;
	

	 ///////////////

	 /*
 	 //  2006/04/14, 存储进程调用的模块
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcProcessModuleTab("
										"id	"  +  pAutoincrement  +  ","
										"uiType						int not null,"	//  区分代理服务器和网卡配置等类型
										"mac0						char(12) not null,"			//  	
										"uiLangId					int,"							//  2005/01/24, 语种
										"iPlatformId				int not null,"					//  操作系统类型
										"winDir						varchar(255) not null,"			//  Windows目录
										"dwPid						int,"
										"moduleName					varchar(255),"					//  程序名
										"modulePath					varchar(255),"					//  运行路径
										"myModulePath				varchar(255),"					//  供分析用的路径
										"dwMemInK					int,"							//  内存大小
										//
										"iProp0						int,"
										"iProp1						int,"
										"iProp2						int,"
										"iProp3						int,"
										"iProp4						int,"
										"iProp5						int,"
										"iProp6						int,"
										"iProp7						int,"
										"iProp8						int,"
										"iProp9						int,"
										"propStr0					varchar(255),"
										"propStr1					varchar(255),"
										"propStr2					varchar(255),"
										"propStr3					varchar(255),"
										"propStr4					varchar(255),"
										"propStr5					varchar(255),"
										"propStr6					varchar(255),"
										"propStr7					varchar(255),"
										"propStr8					varchar(255),"
										"propStr9					varchar(255),"
										//
										"firstTime					char(14),"
										"lastTime					char(14),"
										"iStatus					int,"				//  未绑定，绑定，或未执行，或无法执行
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;
	 */


	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcProcessRuleTab("
										"id	"  +  pAutoincrement  +  ","
										"uiType						int not null,"	//  区分统一允许，单机允许，统一禁止，单机允许
										"mac0						char(12) not null,"			//  	
										"moduleName					"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"					//  程序名
										"modulePath					"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"					//  运行路径	
										//
										"iProp0						int,"
										"iProp1						int,"
										"iProp2						int,"
										"iProp3						int,"
										"iProp4						int,"
										"iProp5						int,"
										"iProp6						int,"
										"iProp7						int,"
										"iProp8						int,"
										"iProp9						int,"
										"propStr0					varchar(255),"
										"propStr1					varchar(255),"
										"propStr2					varchar(255),"
										"propStr3					varchar(255),"
										"propStr4					varchar(255),"
										"propStr5					varchar(255),"
										"propStr6					varchar(255),"
										"propStr7					varchar(255),"
										"propStr8					varchar(255),"
										"propStr9					varchar(255),"
										//
										"firstTime					char(14),"
										"lastTime					char(14),"
										"iStatus					int,"				
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;
										


	 ////////////////////////	
	 //  2006/04/16

	 
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcProcessKnowledgeTab("
										"id	"  +  pAutoincrement  +  ","
										"uiType						int not null,"
										"fileName					"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255) primary key,"		//  文件名
										"cmdLine					"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"					//  命令行参数, 2006/09/06
										"constraint tmpPcProcessKnowledgeIndex unique(fileName,cmdLine),"
										"name						"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  名称
										"des0						"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  描述
										"company					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  公司
										"product					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  产品
										"ucbSys						varchar(255),"					//  是否系统文件
										"ucbDaemon					varchar(255),"					//  是否后台程序
										"ucbUseNet					varchar(255),"					//  是否使用网络
										"ucbHardware				varchar(255),"					//  是否硬件相关
										"commonErr					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  常见错误
										"memInfo					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  内存使用
										"securityLevel				int,"							//  安全等级
										"ucbSpy						varchar(255),"					//  是否间谍软件
										"ucbAdvertisement			varchar(255),"					//  是否广告软件
										"ucbVirus					varchar(255),"					//  是否病毒
										"ucbBackDoor				varchar(255),"					//  是否后门
										//
										"iProp0						int,"
										"iProp1						int,"
										"iProp2						int,"
										"iProp3						int,"
										"iProp4						int,"
										"iProp5						int,"
										"iProp6						int,"
										"iProp7						int,"
										"iProp8						int,"
										"iProp9						int,"
										"propStr0					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr1					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr2					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr3					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr4					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr5					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr6					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr7					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr8					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr9					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										//
										"provider					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  提交者
										"providerAddr				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  提交者联系方式
										"providerTime				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  提交时间
										//
										"auditTime					char(14),"					//  审核时间
										"firstTime					char(14),"					//
										"lastTime					char(14),"
										"iStatus					int,"				
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;

	 ///////////
	 	
	 //  2006/08/10, 增加注册表知识库
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcRegistryKnowledgeTab("
										"id	"  +  pAutoincrement  +  ","
										"uiType						int not null,"
										"iRootKey					int not null,"
										"subKey						"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"					//  名称
										"cfgName					"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"					//  描述
										"suggestedVal				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  建议值
										"name						"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  名称
										"des0						"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  描述
										"company					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  公司
										"product					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  产品
										"ucbSys						varchar(255),"					//  是否系统文件
										"ucbDaemon					varchar(255),"					//  是否后台程序
										"ucbUseNet					varchar(255),"					//  是否使用网络
										"ucbHardware				varchar(255),"					//  是否硬件相关
										"commonErr					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  常见错误
										"memInfo					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  内存使用
										"securityLevel				int,"							//  安全等级
										"ucbSpy						varchar(255),"					//  是否间谍软件
										"ucbAdvertisement			varchar(255),"					//  是否广告软件
										"ucbVirus					varchar(255),"					//  是否病毒
										"ucbBackDoor				varchar(255),"					//  是否后门
										//
										"constraint tmpPcRegistryKnowledgeIndex unique(uiType,iRootKey,subKey,cfgName),"
										//
										"iProp0						int,"
										"iProp1						int,"
										"iProp2						int,"
										"iProp3						int,"
										"iProp4						int,"
										"iProp5						int,"
										"iProp6						int,"
										"iProp7						int,"
										"iProp8						int,"
										"iProp9						int,"
										"propStr0					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr1					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr2					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr3					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr4					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr5					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr6					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr7					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr8					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr9					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										//
										"provider					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  提交者
										"providerAddr				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  提交者联系方式
										"providerTime				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"					//  提交时间
										//
										"auditTime					char(14),"					//  审核时间
										"firstTime					char(14),"					//
										"lastTime					char(14),"
										"iStatus					int,"				
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;

  
	 /////////////

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcRegistryRuleTab("			//  2006/07/07,增加
										"id	"  +  pAutoincrement  +  ","
										"uiType						int not null,"	//  区分代理服务器和网卡配置等类型
										//
										"mac0						char(12) not null,"
										"uiLangId					int not null,"						//  2005/01/24, 语种
										"iPlatformId				int not null,"						//  操作系统类型
										"winDir						varchar(255) not null,"				//  Windows目录
										//										
										"iRootKey					int not null,"						//  HKEY_CLASSES_ROOT等预定值，或者对应的自定义的值
										"usrName					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"subkey						"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"
										"ucbKey						varchar(1),"
										"uiCfgNameLen				int,"
										"cfgName					"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"
										"iValType					int,"
										"uiValLenInBytes			int,"								//  值的长度
										"iCfgVal					int,"
										"cfgVal						"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										//
										//										
										"nIntervals					int,"								//  每N个周期发一次
										"constraint tmpPcRegistryRuleIndex unique(uiType,mac0,uiLangId,iPlatformId,winDir,iRootKey,subKey,cfgName),"
										//
										"unsupport98				varchar(1),"
										"unsupportMe				varchar(1),"
										"unsupportNt				varchar(1),"
										"unsupport2k				varchar(1),"
										"unsupportXp				varchar(1),"
										"unsupport2003				varchar(1),"
										"unsupportVista				varchar(1),"
										"unsupportOs10				varchar(1),"
										"unsupportOs11				varchar(1),"
										"unsupportOs12				varchar(1),"
										"unsupportOs13				varchar(1),"
										"unsupportOs14				varchar(1),"
										//
										"ucbNotLogAdd				varchar(1),"
										"ucbNotLogDel				varchar(1),"
										"ucbNotLogModify			varchar(1),"
										//
										"iProp0						int,"
										"iProp1						int,"
										"iProp2						int,"
										"iProp3						int,"
										"iProp4						int,"
										"iProp5						int,"
										"iProp6						int,"
										"iProp7						int,"
										"iProp8						int,"
										"iProp9						int,"
										//
										"propStr0					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr1					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr2					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr3					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr4					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr5					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr6					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr7					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr8					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr9					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										//
										"firstTime					char(14),"
										"lastTime					char(14),"
										"iStatus					int,"				//  未绑定，绑定，或未执行，或无法执行
										//
										//
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;

	 /////////
	 ////////

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcRegistryValTab("			//  2006/07/07,增加
										"id	"  +  pAutoincrement  +  ","
										"uiType						int not null,"	//  区分代理服务器和网卡配置等类型, 因为需要有一条记录来表明是否是已读取了此规则, 用不同的类型来区分
										//
										"mac0						char(12) not null,"
										"uiLangId					int not null,"						//  2005/01/24, 语种
										"iPlatformId				int not null,"						//  操作系统类型
										"winDir						varchar(255) not null,"				//  Windows目录
										//
										//
										"iRuleId					int not null,"
										//
											"iRootKey					int,"							//  HKEY_CLASSES_ROOT等预定值，或者对应的自定义的值, 辅助性用，在iRuleId中已包含了这个信息，2006/09/28
										"szSidKey				varchar(255),"												//								
										"usrName					"  +  getDataType(  p_nvarchar,  255  )  +  ","			//  varchar(255),"
											"subkey						"  +  getDataType(  p_nvarchar,  255  )  +  ","		//  varchar(255),"，辅助性用，在iRuleId中已包含了这个信息，2006/09/28
										"ucbKey						varchar(1) not null,"
										"uiCfgNameLen				int not null,"
										"cfgName					"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"
										"ucbERROR_MORE_DATA			varchar(1),"
										"iValType					int,"
										"uiValLenInBytes			int,"								//  值的长度
										"iCfgVal					int,"
										"cfgVal						"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										//
										//
										"iProp0						int,"
										"iProp1						int,"
										"iProp2						int,"
										"iProp3						int,"
										"iProp4						int,"
										"iProp5						int,"
										"iProp6						int,"
										"iProp7						int,"
										"iProp8						int,"
										"iProp9						int,"
										//  2006/05/21，增加下面10项
										"iProp10					int,"
										"iProp11					int,"
										"iProp12					int,"
										"iProp13					int,"
										"iProp14					int,"
										"iProp15					int,"
										"iProp16					int,"
										"iProp17					int,"
										"iProp18					int,"
										"iProp19					int,"
										//
										"propStr0					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr1					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr2					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr3					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr4					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr5					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr6					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr7					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr8					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr9					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										//  2006/05/21，增加下面10项
										"propStr10					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr11					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr12					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr13					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr14					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr15					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr16					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr17					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr18					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"propStr19					"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										//
										"firstTime					char(14),"
										"lastTime					char(14),"
										"iSessionId					int not null,"		// 2006/08/05
										"iStatus					int,"				//  未绑定，绑定，或未执行，或无法执行
										//
										//
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;


	 /////////////////////



	 //  2005/09/01
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcEventLogTab("
										"id	"  +  pAutoincrement  +  ","
										"uiType						int not null,"	//  区分代理服务器和网卡配置等类型
										"mac0						char(12) not null,"			//  	
										"uiLangId					int,"							//  2005/01/24, 语种
										"iPlatformId				int not null,"					//  操作系统类型
										"winDir						varchar(255) not null,"			//  Windows目录
										//
										"dwRecordNumber				int,"							// Absolute record number
										"timeGeneratedBuf			char(14),"
										"constraint tmpEventLogIndex unique(mac0,uiLangId,iPlatformId,winDir,dwRecordNumber,timeGeneratedBuf),"
										//
										"wEventType					int,"
										"sourceName					varchar(32),"
										"wEventCategory				int,"
										"dwEventID					int,"
										"accountName				varchar(32),"
										"computerName				varchar(32),"
										"eventLogDesc				varchar(255),"
										//
										"firstTime					char(14),"
										"lastTime					char(14),"
										"iStatus					int,"				//  未绑定，绑定，或未执行，或无法执行
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;

	 //  计算机的操作系统帐户名, 2005/09/05
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcOsUsrTab("
										"id	"  +  pAutoincrement  +  ","
										"uiType						int not null,"	//  区分代理服务器和网卡配置等类型
										"mac0						char(12) not null,"			//  	
										"uiLangId					int,"							//  2005/01/24, 语种
										"iPlatformId				int not null,"					//  操作系统类型
										"winDir						varchar(255) not null,"			//  Windows目录
										"usrName					varchar(255),"
										"constraint tmpPcUsrIndex unique(mac0,uiLangId,iPlatformId,winDir,usrName),"
										"ucbDisabled				varchar(1),"
										//
										"iProp0						int,"
										"iProp1						int,"
										"iProp2						int,"
										"iProp3						int,"
										"iProp4						int,"
										"iProp5						int,"
										"iProp6						int,"
										"iProp7						int,"
										"iProp8						int,"
										"iProp9						int,"
										"propStr0					varchar(255),"
										"propStr1					varchar(255),"
										"propStr2					varchar(255),"
										"propStr3					varchar(255),"
										"propStr4					varchar(255),"
										"propStr5					varchar(255),"
										"propStr6					varchar(255),"
										"propStr7					varchar(255),"
										"propStr8					varchar(255),"
										"propStr9					varchar(255),"
										//
										"firstTime					char(14),"
										"lastTime					char(14),"
										"iStatus					int,"				//  未绑定，绑定，或未执行，或无法执行
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;

	 //  计算机的打印机信息, 2005/09/18
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcPrinterTab("
										"id	"  +  pAutoincrement  +  ","
										"uiType						int not null,"	//  区分代理服务器和网卡配置等类型
										"mac0						char(12) not null,"			//  	
										"uiLangId					int,"							//  2005/01/24, 语种
										"iPlatformId				int not null,"					//  操作系统类型
										"winDir						varchar(255) not null,"			//  Windows目录
										"name						varchar(255),"
										"constraint tmpPcPrinterIndex unique(mac0,uiLangId,iPlatformId,winDir,name),"
										//
										"iProp0						int,"
										"iProp1						int,"
										"iProp2						int,"
										"iProp3						int,"
										"iProp4						int,"
										"iProp5						int,"
										"iProp6						int,"
										"iProp7						int,"
										"iProp8						int,"
										"iProp9						int,"
										"propStr0					varchar(255),"
										"propStr1					varchar(255),"
										"propStr2					varchar(255),"
										"propStr3					varchar(255),"
										"propStr4					varchar(255),"
										"propStr5					varchar(255),"
										"propStr6					varchar(255),"
										"propStr7					varchar(255),"
										"propStr8					varchar(255),"
										"propStr9					varchar(255),"
										//
										"firstTime					char(14),"
										"lastTime					char(14),"
										"iStatus					int,"				//  未绑定，绑定，或未执行，或无法执行
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;


	 //  计算机的连接信息，2005/09/17
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcNetStatTab("
										"id	"  +  pAutoincrement  +  ","
										"uiType						int not null,"	//  区分代理服务器和网卡配置等类型
										"mac0						char(12) not null,"			// 
										//
										"dwState					int,"
										"localIp					char(12),"
										"dwLocalPort				int,"
										"remoteIp					char(12),"
										"dwRemotePort				int,"	
										//
										"firstTime					char(14),"
										"lastTime					char(14),"
										"iStatus					int,"				//  未绑定，绑定，或未执行，或无法执行
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;


	 //
	 //////////////////////////////////////////////

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyRasPermittedPhoneNumTab("
										"phoneNum			varchar(16)  primary key"
										")";
	 cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcRuleTab("
										"mac0				char(12)  primary key,"
										"stopMon			varchar(1),"
										"rasCmd				varchar(1),"
										"delProxy			varchar(1),"
										"startProxy			varchar(1),"
										"bUnchked			varchar(1),"
										"bWillAttack		varchar(1),"
										"bDoSecChk			varchar(1),"
										"floppyCmd			varchar(1),"		//  2005/01/05
										"cdromCmd			varchar(1),"		//  2005/01/05
										"usbCmd				varchar(1),"		//  2005/01/05
										"col0				varchar(255),"
										"col1				varchar(255),"
										"col2				varchar(255),"
										"col3				varchar(255),"
										"col4				varchar(255),"
										"col5				varchar(255),"
										"col6				varchar(255),"
										"col7				varchar(255),"
										"col8				varchar(255),"
										"col9				varchar(255),"
										"col10				varchar(255),"
										"col11				varchar(255),"
										"col12				varchar(255),"
										"col13				varchar(255),"
										"col14				varchar(255),"
										"col15				varchar(255),"
										"col16				varchar(255),"
										"col17				varchar(255),"
										"col18				varchar(255),"
										"col19				varchar(255),"
										//  2011/08/27
										"col20				varchar(255),"
										"col21				varchar(255),"
										"col22				varchar(255),"
										"col23				varchar(255),"
										"col24				varchar(255),"
										"col25				varchar(255),"
										"col26				varchar(255),"
										"col27				varchar(255),"
										"col28				varchar(255),"
										"col29				varchar(255),"
										
										"col30				varchar(255),"
										"col31				varchar(255),"
										"col32				varchar(255),"
										"col33				varchar(255),"
										"col34				varchar(255),"
										"col35				varchar(255),"
										"col36				varchar(255),"
										"col37				varchar(255),"
										"col38				varchar(255),"
										"col39				varchar(255),"

										"col40				varchar(255),"
										"col41				varchar(255),"
										"col42				varchar(255),"
										"col43				varchar(255),"
										"col44				varchar(255),"
										"col45				varchar(255),"
										"col46				varchar(255),"
										"col47				varchar(255),"
										"col48				varchar(255),"
										"col49				varchar(255),"


										//
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;
	 

	 //  {  //  2006/03/04

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcMonRuleTab("
 										"id	"  +  pAutoincrement  +  ","
										"mac0				char(12)  primary key,"
										"capScreenCmd		varchar(1),"					//  抓屏
										"imMonCmd			varchar(1),"					//  即时通讯
										"ieMonCmd			varchar(1),"					//  监控IE
										"col0				varchar(255),"
										"col1				varchar(255),"
										"col2				varchar(255),"
										"col3				varchar(255),"
										"col4				varchar(255),"
										"col5				varchar(255),"
										"col6				varchar(255),"
										"col7				varchar(255),"
										"col8				varchar(255),"
										"col9				varchar(255),"
										"col10				varchar(255),"
										"col11				varchar(255),"
										"col12				varchar(255),"
										"col13				varchar(255),"
										"col14				varchar(255),"
										"col15				varchar(255),"
										"col16				varchar(255),"
										"col17				varchar(255),"
										"col18				varchar(255),"
										"col19				varchar(255),"
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;


	 //  2006/03/21
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcFileMonRuleTab("
 										"id	"  +  pAutoincrement  +  ","
										"mac0				char(12) not null,"
										"uiType				int not null,"
										"col0				varchar(255),"
										"col1				varchar(255),"
										"col2				varchar(255),"
										"col3				varchar(255),"
										"col4				varchar(255),"
										"col5				varchar(255),"
										"col6				varchar(255),"
										"col7				varchar(255),"
										"col8				varchar(255),"
										"col9				varchar(255),"
										"iCol0				int,"
										"iCol1				int,"
										"iCol2				int,"
										"iCol3				int,"
										"iCol4				int,"
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;



	 //  }





	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qnmUnchkedIpTab("
										 "startIp			char(15) primary key,"		//  ip12格式
										 "endIp				char(15),"					//  ip12格式
										 "ip				char(15),"					//  已废弃
										 "bTmp				varchar(1),"
										 "startTime			char(14)"
										 ")";
	 cnt  ++  ;
 


	 ////  2006/02/10

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcStatusTab("							//  操作命令队列
 										"id	"  +  pAutoincrement  +  ","
										"mac0				char(12)  primary key,"
										"bOped				varchar(1),"						//  是否处于操作状态
										"startTime			char(14),"
										"endTime			char(14),"
										"iStatus0			int,"
										"iStatus1			int,"
										"iStatus2			int,"
										"iStatus3			int,"
										"iStatus4			int,"
										"iStatus5			int,"
										"iStatus6			int,"
										"iStatus7			int,"
										"iStatus8			int,"
									    "iStatus9			int,"
									    "comment0			varchar(255)"
										")";
	 cnt  ++  ;


	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPcOpQTab("							//  操作命令队列
 										"id	"  +  pAutoincrement  +  ","
										"mac0				char(12)  not null,"
										"iCmd				int  not  null,"
										"iParam0			int,"
										"iParam1			int,"
										"paramStr0			varchar(255),"
										"paramStr1			varchar(255),"
										"iStatus			int not null,"					//  这个状态位不能为空
										"startTime			char(14),"
										"endTime			char(14),"
									    "comment0			varchar(255)"
										")";
	 cnt  ++  ;


	 //


	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qnmChkedIpTmpTab("
									    "mac				char(12) primary key,"
									    "ip				char(15) not null,"				//	ip12格式
									    "lastCommTime		char(14),"
									    "startTime			char(14) not null,"
									    "endTime			char(14) not null,"
									    "fBwd				varchar(1),"					//  '1'时表非本网段
									    "bAttacked			varchar(1),"
									    "col0				varchar(255),"
									    "col1				varchar(255),"
									    "col2				varchar(255),"
									    "col3				varchar(255),"
									    "col4				varchar(255)"
									    ")";
	 cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qnmProxyTab("
 										"mac0				char(12) primary key,"
									    "ip					char(15),"				//  ip12格式
										"qnmProxyVer		char(8),"
										"startTime			char(14) not null,"
										"lastCommTime		char(14) not null,"
									    "lanName			varchar(16),"
									    "col0				varchar(255),"
									    "col1				varchar(255),"
									  	"col2				varchar(255),"
									    "col3				varchar(255),"
									    "col4				varchar(255)"
									    ")";
	 cnt  ++  ;

 
	 if  (  sqlScripts_qyObjIndexTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 /*
	 //  建对象索引的表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyObjIndexTab("
										//  "id					autoincrement,"
										"id	"  +  pAutoincrement  +  ","
										"usageType			int not null,"
										"usageName			"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"objType  			int not null,"			//  节点对象  
										"objId0				int not null,"
										"objId1				int not null,"
										"objId2				int not null,"
										"objIdStr0			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255) not null,"
										"objIdStr1			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255) not null,"
										"objIdStr2			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255) not null,"
										"constraint objInd unique(usageType,objType,objId0,objId1,objId2,objIdStr0,objIdStr1,objIdStr2),"
										"col0				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col1				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col2				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col3				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col4				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"comment0			"  +  getDataType(  p_nvarchar,  255  )  +  ""					//  varchar(255)"
										")";
	 cnt  ++  ;
	 */


	 //  建表示snmpObj的表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qySnmpObjTab("
										"iIpForwarding						varchar(32),"
										"ucbBridge							varchar(32),"
										"ucbHost							varchar(32),"
										"sysDescr							varchar(255),"
										"iMaker								varchar(32),"
										"maker								varchar(128),"
										"productName						varchar(128),"
										"lNetDevType						int,"				//  设备类型，
										"ip									char(15),"		//  ip12格式
										"mac								char(12) primary key,"
										"dot1dBaseNumPorts					int,"				//  以前的定义："dot1dBaseNumPorts	varchar(32),"
										"iManagementDomainLocalMode			int,"				//  vtp client 1, server 2, transparent 3, 2004/06/06加
										"iCpsGlobalMaxSecureAddress			int,"				//  2004/06/06加
										"iCpsGlobalTotalSecureAddress		int,"
										"iCpsGlobalPortSecurityEnable		int,"				//  true(1), false(2)				

										"lStatus							int,"				//  网络设备在线离线状态
										"cusName							varchar(64),"		//  别名
										"place								varchar(255),"		//  使用地点

										"firstTime							char(14),"		//  最先扫描到的时间
										"lastTime							char(14),"		//  最新扫描到的时间
										"auditTime							char(14),"			//  审核时间，2004/04/09
										"comment0							varchar(255)"
										")";
	 cnt  ++  ;

	 //  建表示switchPortTab的表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qySwitchPortTab("
										"switchMac			char(12) not null,"
										"portIfIndex		int not null,"		//  以前的定义："portIfIndex		varchar(32) not null,"										
										"portIfDescr		varchar(255),"
										"portIfType			int,"
										"portIfSpeedInK		int,"				//  带宽，以k为单位
										"portIfPhysAddress	varchar(32),"
										"portIfAdminStatus	varchar(32),"
										"portIfOperStatus	varchar(32),"
										"portIfInOctets		int,"				//  入字节数
										"portIfOutOctets	int,"				//  出字节数
										"portIfInSpeedInK	int,"				//  入流量
				 						"portIfOutSpeedInK	int,"				//  出流量				 
										"bridgePort			int,"				//  以前的定义："bridgePort			varchar(32),"
										"constraint switchPortInd unique(  switchMac,  portIfIndex  ),"
										"vlanId				int,"
										"vlanName			varchar(255),"		//  暂时不用
										"iVmVlanType		int,"				//  static 1, dynamic 2, multiVlan 3, 2004/06/06

										"firstTime			char(14),"		//  最先扫描到的时间
										"lastTime			char(14),"		//  最新扫描到的时间
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;


	 //  建vlan表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyVlanTab("
										"id					int primary key,"
										"name				varchar(255),"
										"status				int,"
										"type				int,"
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;
	 

	 //  建与switch相关联的MAC(大半是主机)信息的表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qySwitchConnectedPcTab("
										"switchMac			char(12) not null,"
										"connectedMac		char(12) not null,"
										"constraint pcInd unique(  switchMac,  connectedMac  ),"
										"connectedIp		char(15),"			//  ip12格式
										"portIfIndex		int,"					//  以前的定义："portIfIndex		varchar(32),"										
										"firstTime			char(14),"			//  最先扫描到的时间
										"lastTime			char(14),"			//  最新扫描到的时间
										"auditTime			char(14),"				//  审核时间，2004/04/09
										"ucbDirectConn		varchar(1),"			//  是否直接接入
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;

	 //  2005/03/07
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qnmConflictConnTab("
										 "id	"  +  pAutoincrement  +  ","
										 "iType							int not null,"
										 "switchMac						char(12) not null,"
										 "connectedMac					char(12) not null,"
										 "constraint conlictConnInd unique(  iType,  switchMac,  connectedMac  ),"
										 "portIfIndex					int not null,"
										 "firstTime						char(14),"
										 "ucbLocked						varchar(1),"
										 "iFlg							int,"
										 "comment0						varchar(255)"
										 ")";
	 cnt  ++  ;


	 //  建与switch相关联的静态MAC表,  2004/06/13
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qySwitchStaticMacTab("
										"switchMac						char(12) not null,"
										"connectedMac					char(12) not null,"
										"vlanId							int not null,"
										"constraint staticMacInd unique(  switchMac,  vlanId,  connectedMac  ),"
										//  "connectedIp		char(15),"			//  ip12格式
										"iDot1dStaticReceivePort  		int,"
										"dot1dStaticAllowedToGoTo		varchar(255),"
										"iDot1dStaticStatus				int,"						//  other(1), invalid(2), permanent(3), deleteOnReset(4), deleteOnTimeout(5)  
										"firstTime						char(14),"				//  最先扫描到的时间
										"lastTime						char(14),"				//  最新扫描到的时间
										"comment0						varchar(255)"
										")";
	 cnt  ++  ;


	 //  建与switch相关联的设备信息的表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qySwitchConnectedDevTab("
										"switchMac			char(12) not null,"
										"portIfIndex		int not null,"			//  以前的定义: "portIfIndex		varchar(32) not null,"								
										"deviceIndex		int not null,"
										"constraint devInd unique(  switchMac,  portIfIndex,  deviceIndex  ),"
										"addressType		int,"
										"address			varchar(255),"			//  如果是ip的话，则用ip12格式
										"version			varchar(255),"
										"devicePortDescr	varchar(255),"
										"platform			varchar(255),"
										"firstTime			char(14),"			//  最先扫描到的时间
										"lastTime			char(14),"			//  最新扫描到的时间
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;


	 //  建switch的端口绑定的端口策略表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qySwitchIfPortSecurityTab("
										"switchMac							char(12) not null,"
										"portIfIndex						int not null,"
										"constraint  ifPortSecurityInd  unique(  switchMac,  portIfIndex  ),"
										"iCpsIfPortSecurityEnable			int,"					//  true(1), false(2)
										"iCpsIfPortSecurityStatus			int,"					//  secureup(1), securedown(2), shutdown(3)
										"iCpsIfMaxSecureMacAddr				int,"
										"iCpsIfCurrentSecureMacAddrCount	int,"
										"iCpsIfViolationAction				int,"					//  shutdown(1), dropNotify(2), drop(3)
										"lastTime							char(14),"			//  最新扫描到的时间
										"comment0							varchar(255)"
										")";
	 cnt  ++  ;


	 //  建switch的绑定mac表, 2004/06/05
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qySwitchSecureMacTab("
										"switchMac							char(12) not null,"
										"portIfIndex						int not null,"			
										"secureMac							char(12)  not null,"
										"constraint  secureMacInd  unique(  switchMac,  portIfIndex,  secureMac  ),"
										"iCpsSecureMacAddrType				int,"					//  static(1), dynamic(2)
										"iCpsSecureMacAddrRowStatus			int,"					//  active(1), notInService(2), notReady(3), createAndGo(4), createAndWait(5), destroy(6)
										"lastTime							char(14),"			//  最新扫描到的时间
										"comment0							varchar(255)"
										")";
	 cnt  ++  ;


	 //  建switch的流量表, 2004/07/11
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPortIfFlowTab("
										"switchMac		char(12) not null,"
										"sysStartTime	char(14) not null,"
										"portIfIndex	int not null,"		
										"vlanId			int,"
										"iType			int,"			//  iType为		0或NULL，	表即时数据，
																		//				1,			表5分钟取样
																		//				2，			表一天取样
																		//				3，			表一周取样
																		//				4，			表一月取样
																		//				5，			表一年取样
										"portIfInOctets		int,"		//  入字节数
										"portIfOutOctets	int,"		//  出字节数
										"portIfInSpeedInK	int,"		//  入流量
										"portIfOutSpeedInK	int,"		//  出流量				 
										"iDataType		int,"			//  iDataType	0或NULL,	表瞬时值
																		//				1，			表平均值
																		//				2，			表最大值
										"firstTime		char(14),"		//  最先扫描到的时间
										"lastTime		char(14),"		//  最新扫描到的时间
										"comment0		varchar(255)"
										")";
	 cnt  ++  ;


	 //  建switch的流量历史表, 2004/07/11
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyPortIfFlowHisTab("
										"switchMac		char(12) not null,"
										"sysStartTime	char(14) not null,"
										"portIfIndex	int not null,"		
										"vlanId			int,"
										"iType			int,"			//  iType为		0或NULL，	表即时数据，
																		//				1,			表5分钟取样
																		//				2，			表一天取样
																		//				3，			表一周取样
																		//				4，			表一月取样
																		//				5，			表一年取样
										"portIfInOctets		int,"		//  入字节数
										"portIfOutOctets	int,"		//  出字节数
										"portIfInSpeedInK	int,"		//  入流量
										"portIfOutSpeedInK	int,"		//  出流量				 
										"iDataType		int,"			//  iDataType	0或NULL,	表瞬时值
																		//				1，			表平均值
																		//				2，			表最大值
										"firstTime		char(14),"		//  最先扫描到的时间
										"lastTime		char(14),"		//  最新扫描到的时间
										"comment0		varchar(255)"
										")";
	 cnt  ++  ;

	 //  建交换机管理规则表, 2004/08/20
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qySnmpObjRuleTab("
		 								"id	"  +  pAutoincrement  +  ","
										"iType						int  not null,"		//  规则类型
										"switchMac					char(12),"
										"portIfIndex				int,"
										"ibDirectConn				int,"				//  是否接入层交换机, 2005/03/05
										"ibDownPortIfMacChanged		int,"				//  是否阻止端口如果mac的接入新增时, 2005/03/05
										"ibDownPortIfMacChangePort	int,"				//  是否阻止端口如果mac的接入更换端口时, 2006/04/28
										"ibNotLogIfMacChanged		int,"				//  不记录联接MAC变化事件, 2006/04/28
										"warnPercentOfBand			int,"
										"iProcType					int,"				//  处理动作
										"comment0					varchar(255)"
										")";
	 cnt  ++  ;



	 //  建交换机访问策略组表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qySnmpPolicyGrpTab("
										"name				varchar(64) not null primary key,"
										"snmpVer			varchar(32) not null,"
										"getCommunity		varchar(255) not null,"
										"setCommunity		varchar(255),"
										"usmName			varchar(255),"
										"securityLevel		char(8),"			//  0 表noAuthPriv, 
																					//	1 表authNoPriv,
																					//	2 表authPriv
										"authMethod			varchar(32),"
										"authStr			varchar(128),"
										"privMethod			varchar(32),"
										"privStr			varchar(128),"
										"engineId			varchar(128),"

										"col0				varchar(255),"
										"col1				varchar(255),"
										"col2				varchar(255),"
										"col3				varchar(255),"
										"col4				varchar(255),"
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;


	 //  建交换机访问策略表，
	 //  要么交换机属于某一组，或者也可以用自己单独的策略(此时grpName is null 或 '')
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qySnmpObjPolicyTab("
										"ip					char(15) not null primary key,"
										"cusName			varchar(64),"
										"grpName			varchar(64),"
										"snmpVer			varchar(32),"
										"getCommunity		varchar(255),"
										"setCommunity		varchar(255),"
										"usmName			varchar(255),"
										"securityLevel		char(8),"			//  0 表noAuthPriv, 
																					//	1 表authNoPriv,
																					//	2 表authPriv
										"authMethod			varchar(32),"
										"authStr			varchar(128),"
										"privMethod			varchar(32),"
										"privStr			varchar(128),"
										"engineId			varchar(128),"

										"col0				varchar(255),"
										"col1				varchar(255),"
										"col2				varchar(255),"
										"col3				varchar(255),"
										"col4				varchar(255),"
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;


	 //  建任务列表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qnmTaskTab("
										"iTaskType			int primary key,"
										"objId0				int not null,"
										"objId1				int not null,"
										"objId2				int not null,"
										"objIdStr0			varchar(255) not null,"			//  switchMac
										"objIdStr1			varchar(255) not null,"			//  connectedMac
										"objIdStr2			varchar(255) not null,"
										"comment0			varchar(255)"
										")";
	 cnt  ++  ;


	 //  建临时表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qnmTmpTab("
										"iType				int not null,"
										"queryTime			char(14) not null,"
										"mac				char(12),"
										"ip					char(15),"
										"col0				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col1				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col2				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col3				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col4				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"		//  以下2005/01/25
										"col5				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col6				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col7				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col8				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col9				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col10				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col11				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col12				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col13				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col14				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col15				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col16				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col17				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col18				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"col19				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"										
										"des0				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des1				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des2				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des3				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des4				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"		//  以下2005/01/25
										"des5				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des6				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des7				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des8				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des9				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des10				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des11				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des12				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des13				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des14				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des15				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des16				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des17				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des18				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"des19				"  +  getDataType(  p_nvarchar,  255  )  +  ","					//  varchar(255),"
										"comment0			"  +  getDataType(  p_nvarchar,  255  )  +  ""					//  varchar(255)"
										")";
	 cnt  ++  ;


	 //  2006/01/07, 建自动登陆用户的设置
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table autoLogonTab("
										"id	"  +  pAutoincrement  +  ","
										"mac0				char(12),"				//  对规则来说，则MAC0为""则为规则；否则就是终端登陆的审计
										"domainName			varchar(255),"				//  
										"logonName			varchar(255),"
										"logonPasswd		varchar(255),"
										"procedTime			char(14),"
										"col0				varchar(255),"
										"col1				varchar(255),"
										"col2				varchar(255),"
										"col3				varchar(255),"
										"col4				varchar(255)"										
										")";
	 cnt  ++  ;
	 //  
	 //


	 //  建awmExt系统的表  {  
	 //

	 //  awmInterMonLogProcInfoTab
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table awmInterMonLogProcInfoTab("
										"procedIndex		int not null,"
										"procedTime			char(14)"
										")";
	 cnt  ++  ;

	 //  offlineComputerLogTab
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table offlineComputerLogTab("
										//  "index0				autoincrement,"
										"index0	"  +  pAutoincrement  +  ","
										"officeName			char(8) not null,"
										"subOfficeName		char(8),"
										"ip					char(15) not null,"
										"mac				char(12),"				//  2004/05/22
										"compName			varchar(16),"				//  2004/05/23
										"usrName			varchar(16),"				//  2004/05/23
										"is_server			varchar(1),"				//  2004/05/23
										"firstRecvdTime		char(14) not null,"
										"lastRecvdTime		char(14) not null"
										")";
	 cnt  ++  ;

	 //  onlineComputerTab
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table onlineComputerTab("
										"officeName			char(8) not null,"
										"subOfficeName		char(8),"
										"ip					char(15) not null,"
										//  "constraint computerInd unique(  officeName,  subOfficeName,  ip  ),"										
										"constraint computerInd unique(  ip  ),"										
										"mac				char(12),"				//  2004/05/22
										"compName			varchar(16),"				//  2004/05/23
										"usrName			varchar(16),"				//  2004/05/23
										"is_server			varchar(1),"				//  2004/05/23
										"firstRecvdTime		char(14) not null,"
										"lastRecvdTime		char(14) not null"										
										")";
	 cnt  ++  ;
	
	 //  originalLogTab
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table originalLogTab("
										//  "index0				autoincrement primary key,"
										"index0	"  +  pAutoincrement  +  " primary key,"
										"recvdTime			char(14) not null,"
										"computerInfo		varchar(255) not null"		//  2004/05/22修改了将大小从31改为255
										")";
	 cnt  ++  ;

	 //  scannedIpTab
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table scannedIpTab("
										"interMonIp			char(15) not null,"
										"officeName			char(8),"
										"subOfficeName		char(8),"
										"startIp			char(15) not null,"
										"endIp				char(15),"
										"constraint scannedInd unique(  officeName,  subOfficeName,  startIp  )"																				
										")";
	 cnt  ++  ;

	 //  scanningLogTab,  该表似乎已经不用了
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table scanningLogTab("
										//  "index0				autoincrement primary key,"
										"index0	"  +  pAutoincrement  +  " primary key,"
										"scannedIp			char(15) not null,"
										"recvdTime			char(14) not null,"
										"officeName			char(8),"
										"subOfficeName		char(8)"
										")";
	 cnt  ++  ;

	 //  }  如上是awmExt系统的表  

	 //  建立系统信息表
	 /*

	 //  建管理端用户组列表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyGrpTab("
 										"name				varchar(30) primary key,"
									    "right0				varchar(255)"
										")";
	 cnt  ++  ;

	 //  建管理端用户列表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyUsrTab("
 										"name				varchar(30) primary key,"
									    "passwd				varchar(32) not null"
										")";
	 cnt  ++  ;

	 //  建用户和用户组关联列表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyGrpUsrRelationTab("
 										"grpName			varchar(30) not null,"
									    "usrName			varchar(30) not null,"
										"constraint grpUsrInd unique(grpName,usrName)"
										")";
	 cnt  ++  ;


	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qySystemInfoTab("
										"iServiceId			int  not  null,"			//  2007/03/10
										"name				char(15) not null,"
										"dbVer				varchar(32) not null,"
										"col0				varchar(255),"
										"col1				varchar(255),"
										"col2				varchar(255),"
										"col3				varchar(255),"
										"col4				varchar(255),"
										"col5				varchar(255),"
										"col6				varchar(255),"
										"col7				varchar(255),"
										"col8				varchar(255),"
										"col9				varchar(255),"
										"comment0			varchar(255)"
										")";	
	 cnt  ++  ;

  	 //  初始化系统信息
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qySystemInfoTab(iServiceId,name,dbVer) values(%d,'%s','%s')"  ),  iServiceId,  CString(  "qyNetMc"  ),  CString(  dbVer  )  );
	 sqlStr[cnt]  =  CString(  sqlBuf  );
	 cnt  ++  ;


	 //  初始化用户和组相关信息
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyUsrTab(name,passwd) values('admin','923b56hnw')";
	 cnt  ++  ;
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyGrpUsrRelationTab(grpName,usrName) values('adminGrp','admin')";
	 cnt  ++  ;
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyUsrTab(name,passwd) values('sysadmin','f3f9f3e1e4ede9eeb1b2b3')";
	 cnt  ++  ;
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyGrpUsrRelationTab(grpName,usrName) values('sysGrp','sysadmin')";
	 cnt  ++  ;
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyUsrTab(name,passwd) values('logadmin','ecefe7e1e4ede9eeb1b2b3')";
	 cnt  ++  ;
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyGrpUsrRelationTab(grpName,usrName) values('logGrp','logadmin')";
	 cnt  ++  ;

	 */	 

	 if  (  sqlScripts_qyUsrTabs(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 if  (  sqlScripts_qySystemInfoTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  iServiceId,  0,  0,  CString(  "qyNetMc"  ),  dbVer  )  )  goto  errLabel;

	 
	 //  初始化awmExt系统的表  
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into awmInterMonLogProcInfoTab(procedIndex,procedTime) values(0,'00000000000000')";
	 cnt  ++  ;


	 int	iDataType;
	 iDataType  =  SQL_WVARCHAR;
	 //  初始化进程知识库，提供几个案例, 2006/05/07
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcProcessKnowledgeTab(uiType,fileName,cmdLine,name,des0,company,product,ucbSys,ucbSpy,ucbAdvertisement,ucbVirus,ucbBackDoor,provider,providerAddr)"
										" values("	+  _ltoa(  CONST_pcCommType_pcProcessKnowledge,  buf,  10  )
													+  ","  +	getDbValStr(  iDbType,  iDataType,  _T(  "\\systemroot\\system32\\notepad.exe"  )  )  
													+  ","  +	getDbValStr(  iDbType,  iDataType,  _T(  ""  )  )  
													+  ","	+	getDbValStr(  iDbType,  iDataType,  _T(  "Notepad"  )  )
													+  ","  +	getDbValStr(  iDbType,  iDataType,  _T(  "Text Editer"  )  )
													+  ","  +	getDbValStr(  iDbType,  iDataType,  _T(  "Microsoft"  )  )
													+  ","  +	getDbValStr(  iDbType,  iDataType,  _T(  "Windows"  )  )
													+  ","  +	"'1'"
													+  ","  +	"''"
													+  ","  +	"''"
													+  ","  +	"''"
													+  ","  +	"''"
													+  ","	+	getDbValStr(  iDbType,  iDataType,  _T(  "Beijing Qycx Co., Ltd"  )  )
													+  ","  +	getDbValStr(  iDbType,  iDataType,  _T(  "www.qycx.com"  )  )
													+  ")";
	 cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcProcessKnowledgeTab(uiType,fileName,cmdLine,name,des0,company,product,ucbSys,ucbSpy,ucbAdvertisement,ucbVirus,ucbBackDoor,provider,providerAddr)"
										" values("	+  _ltoa(  	CONST_pcCommType_pcProcessKnowledge,  buf,  10  )
													+  ","  +	getDbValStr(  iDbType,  iDataType,  _T(  "\\systemroot\\Explorer.exe"  )  )  
													+  ","  +	getDbValStr(  iDbType,  iDataType,  _T(  ""  )  )  
													+  ","	+	getDbValStr(  iDbType,  iDataType,  _T(  "Explorer"  )  )
													+  ","  +	getDbValStr(  iDbType,  iDataType,  _T(  "Resource Manager"  )  )
													+  ","  +	getDbValStr(  iDbType,  iDataType,  _T(  "Microsoft"  )  )
													+  ","  +	getDbValStr(  iDbType,  iDataType,  _T(  "Windows"  )  )
													+  ","  +	"'1'"
													+  ","  +	"''"
													+  ","  +	"''"
													+  ","  +	"''"
													+  ","  +	"''"
													+  ","	+	getDbValStr(  iDbType,  iDataType,  _T(  "Beijing Qycx Co., Ltd"  )  )
													+  ","  +	getDbValStr(  iDbType,  iDataType,  _T(  "www.qycx.com"  )  )
													+  ")";
	 cnt  ++  ;


	 //  输入几个注册表规则，2006/09/13
	 {
		 int			iRootKey;
		 TCHAR		*	subKey  =  _T(  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"  );
	 	 TCHAR		*	cfgName  =  _T(  ""  );
	 	 int			nIntervals  =  0;
	 	 unsigned  char  ucbUnsupport98  =  TRUE,  ucbUnsupportMe  =  TRUE,  ucbUnsupportNt  =  TRUE,  ucbUnsupport2k  =  FALSE, ucbUnsupportXp  =  FALSE,  ucbUnsupport2003  =  FALSE,  ucbUnsupportVista  =  FALSE;
		 unsigned  char  ucbNotLogAdd  =  FALSE,  ucbNotLogDel  =  FALSE,  ucbNotLogModify  =  FALSE;
		 iRootKey  =  (  int  )HKEY_LOCAL_MACHINE;	
		 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcRegistryRuleTab(uiType,mac0,uiLangId,iPlatformId,winDir,iRootKey,subKey,cfgName,nIntervals,unsupport98,unsupportMe,unsupportNt,unsupport2k,unsupportXp,unsupport2003,unsupportVista,ucbNotLogAdd,ucbNotLogDel,ucbNotLogModify) values(%d,'%s',0,0,'',%d,%s,%s,%d,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"  ),  CONST_pcCommType_registryRule,  CString(CONST_qyNullMac),  iRootKey,  getDbValStr(  iDbType,  SQL_WVARCHAR,  subKey  ),  getDbValStr(  iDbType,  SQL_WVARCHAR,  cfgName  ),  nIntervals,  
							MACRO_ucbStr(  ucbUnsupport98  ),    
							MACRO_ucbStr(  ucbUnsupportMe  ),    
							MACRO_ucbStr(  ucbUnsupportNt  ),    
							MACRO_ucbStr(  ucbUnsupport2k  ),    
							MACRO_ucbStr(  ucbUnsupportXp  ),    
							MACRO_ucbStr(  ucbUnsupport2003  ),
							MACRO_ucbStr(  ucbUnsupportVista  ),
							MACRO_ucbStr(  ucbNotLogAdd  ),  
							MACRO_ucbStr(  ucbNotLogDel  ),  
							MACRO_ucbStr(  ucbNotLogModify  )
							);

		 sqlStr[cnt]  =  CString(  sqlBuf  );
		 cnt  ++  ;

		 iRootKey  =  (  int  )HKEY_USERS;	
		 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcRegistryRuleTab(uiType,mac0,uiLangId,iPlatformId,winDir,iRootKey,subKey,cfgName,nIntervals,unsupport98,unsupportMe,unsupportNt,unsupport2k,unsupportXp,unsupport2003,unsupportVista,ucbNotLogAdd,ucbNotLogDel,ucbNotLogModify) values(%d,'%s',0,0,'',%d,%s,%s,%d,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"  ),  CONST_pcCommType_registryRule,  CString(CONST_qyNullMac),  iRootKey,  getDbValStr(  iDbType,  SQL_WVARCHAR,  subKey  ),  getDbValStr(  iDbType,  SQL_WVARCHAR,  cfgName  ),  nIntervals,  
							MACRO_ucbStr(  ucbUnsupport98  ),    
							MACRO_ucbStr(  ucbUnsupportMe  ),    
							MACRO_ucbStr(  ucbUnsupportNt  ),    
							MACRO_ucbStr(  ucbUnsupport2k  ),    
							MACRO_ucbStr(  ucbUnsupportXp  ),    
							MACRO_ucbStr(  ucbUnsupport2003  ),
							MACRO_ucbStr(  ucbUnsupportVista  ),
							MACRO_ucbStr(  ucbNotLogAdd  ),  
							MACRO_ucbStr(  ucbNotLogDel  ),  
							MACRO_ucbStr(  ucbNotLogModify  )
							);

		 sqlStr[cnt]  =  CString(  sqlBuf  );
		 cnt  ++  ;


	 }


	 //  建最后一个测试建库结束的表
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyTestEndTab("
										"col0				varchar(30) primary key,"
										"col_int			int,"
										"col_Integer		Integer"
										")";
	 cnt  ++  ;


	 try  {
		pDb = new  CDatabase;
		if  (  !pDb  )  goto  errLabel;
		if  (  !pDb->OpenEx(  CString(  connectStrBuf  ),  CONST_qyDbOpenOptions  )  )  goto errLabel;
		
		OutputDebugString(  _T(  "make db start \n"  )  );
		for  (  i  =  0;  i  <  cnt;  i  ++  )  {
			 OutputDebugString(  sqlStr[i].GetBuffer(  0  )  );  OutputDebugString(  _T(  "\n"  )  );
			 pDb->ExecuteSQL(  sqlStr[i]  );
		}
		OutputDebugString(  _T(  "make db ok \n"  )  );
		//  AfxMessageBox(  "建库结束"  );
		
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "makeDb_netMc failed."  )  );
		   goto  errLabel;
	}


	iErr  =  0;
		
errLabel:

	if  (  pDb  )  delete  pDb;

	return  iErr;
	 	
}



 int  makeTestData_netMc(  ) 
{
	 CDatabase  *	pDb				=  NULL;
	 char		*	dsnName			=  CONST_dsn_netMc;
	 CString		sqlStr[128];
	 int			cnt				=  0;
	 int			i;

	 //  sqlStr[cnt]  =  CString(  ""  )  +  "delete from qyPcTab";	 cnt  ++  ;  // 2004/03/25

	 //  sqlStr[cnt]  =  CString(  ""  )  +  "delete from qyPcRegInfoTab";	 cnt  ++  ;  // 2004/03/25
	 
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcTab(mac0,nMacs,ip,qwmVer,startTime,lastCommTime) values('121212121212','1','1.1.1.1','nt','12345678901234','12345678901234')";	 cnt  ++  ;
 
	 /*
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcTab(mac0,nMacs,ip,qwmVer,startTime,lastCommTime) values('222','1','2.2.2.2','98','12345678901234','12345678901234')";	 cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcTab ( mac0,nMacs,mac1,ip,starttime,lastcommtime) values ('1212121212aa','2','qwqwqwqwqwqw','121212121212','12','12')";	  cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcTab ( mac0 ,nMacs,mac1,ip,startTime,lastCommTime) values ('001212121212','2','232323233333','123123123123','99','11')";		cnt  ++;

	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcTab ( mac0,nMacs,ip,startTime,lastCommTime) values ('121212121212','1','192168103001','001','002')";	cnt  ++  ;
	 
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcTab ( mac0,nMacs,ip,startTime,lastCommTime) values ('aa1234567890','1','192168103003','003','004')";	cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcTab ( mac0,nMacs,ip,startTime,lastCommTime) values ('bb1234567890','1','192168103005','005','006')";	cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcTab ( mac0,nMacs,ip,startTime,lastCommTime) values ('cc1234567890','1','192168103007','007','008')";	cnt  ++	 ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcTab ( mac0,nMacs,ip,osName,startTime,lastCommTime) values ('dd1234567890','1','192168103009','Win98','009','010')";	cnt  ++	 ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcRegInfoTab ( mac0,col0,col1,col2,col3,col4) values ('121212121212','本单位用户','','网监处','计算机科','赵大有')";	cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcRegInfoTab ( mac0,col0,col1,col2,col3,col4) values ('aa1234567890','本单位用户','','网监处','网侦科','孙大有')";	cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcRegInfoTab ( mac0,col0,col1,col2,col3,col4) values ('bb1234567890','本单位用户','','信通处','计算机科','孙大有')";  cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcRegInfoTab ( mac0,col0,col1,col2,col3,col4) values ('cc1234567890','本单位用户','','网监处','计算机科','孙大有')";	cnt  ++  ;

	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcRegInfoTab ( mac0,col0,col1,col2,col3,col4) values ('dd1234567890','外单位临时用户','','网监处','计算机科','李大有')";	cnt  ++	 ;
*/
	 sqlStr[cnt]  =  CString(  ""  )  +  "insert into qyPcRegInfoTab ( mac0,col0,col1,col2,col3,col4) values ('121212121212','外单位临时用户','','"  +  CString(  _T(  "你好"  )  ) +  "','门','人深刻')";	cnt  ++	 ;

	 try  {
		pDb = new  CDatabase;
		if  (  !pDb  )  goto  errLabel;
		if  (  !pDb->Open(  CString(  dsnName  )  )  )  {
			goto errLabel;
		}
		{
			CRecordset	rs(  pDb  );
			if  (  !rs.Open(  CRecordset::snapshot,  CString(  "select col2 from qyPcRegInfoTab"  )  )  )  goto  errLabel;

			rs.Close(  );

		}

		for  (  i  =  0;  i  <  cnt;  i  ++  )  {
			 pDb->ExecuteSQL(  sqlStr[i]  );
		}
		
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "makeTestData_netMc failed."  )  );
		   goto  errLabel;
	}
	
	
errLabel:

	if  (  pDb  )  delete  pDb;

	return  0;
	
}


