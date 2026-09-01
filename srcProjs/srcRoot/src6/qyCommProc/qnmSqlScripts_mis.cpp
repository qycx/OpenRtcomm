
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
#include	"qnmSqlScripts.h"
#include	"qnmCommProc1.h"


//
extern  char  *  CONST_connectStrFmt_access;
extern  char  *  CONST_connectStrFmt_sqlServer;
//
extern  char	*	CONST_autoincrement_access;
extern  char	*	CONST_nchar_access;
extern  char	*	CONST_nvarchar_access;
//
extern  char	*	CONST_autoincrement_sqlServer;
extern  char	*	CONST_nchar_sqlServer;
extern  char	*	CONST_nvarchar_sqlServer;
//
extern  char	*	CONST_autoincrement_mySql;
extern  char	*	CONST_nchar_mySql;
extern  char	*	CONST_nvarchar_mySql;
//
extern  char* CONST_autoincrement_oscar;
extern  char* CONST_nchar_oscar;
extern  char* CONST_nvarchar_oscar;


//
extern  CString  getDataType(  char  *  typeStr,  unsigned  int  len  );


 int  sqlScripts_qyTestTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt  );
 int  sqlScripts_qyTestEndTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt  );
 //
 int  sqlScripts_qySystemInfoTab(  CString  *  pSqlStrs,  unsigned  int  uiMaxCnt,  int  *  piCnt,  int  iServiceId,  int  iSystemId,  int  iAppType,  LPCTSTR  name,  char  *  dbVer  );
 int  sqlScripts_qyUsrTabs(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 //
 int  sqlScripts_qyObjIndexTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 //
 int  sqlScripts_qyCusNameTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 //

 int  sqlScripts_qyImObjTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 int  sqlScripts_qyImObjAuthTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 int  sqlScripts_qyImObjAuthTmpTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 int  sqlScripts_qyImMsgTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 int  sqlScripts_qyImTaskTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar,  BOOL  bHisTab  );
 
 //
 int  sqlScripts_qyImObjRuleTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );

 //
 int  sqlScripts_qyImAmTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );

 //
 int  sqlScripts_qyLoginTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );


 //
 int  sqlScripts_qyMessengerPcInfoTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 int  sqlScripts_qyImObjRegInfoTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar,  BOOL  bTab1  );
 int  sqlScripts_qyImEventTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );

 int  sqlScripts_qyImGrpInfoTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 int  sqlScripts_qyImGrpMemTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );

 int  sqlScripts_qyImGrpInfoExTab(CString* sqlStr, unsigned  int  uiMaxCnt, int* piCnt, char* pAutoincrement, char* p_nchar, char* p_nvarchar);


 //
 int  sqlScripts_qyCustomerServiceObjTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );

 //
 int  sqlScripts_qyIpKnowledgeTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );

 //  2007/11/17
 int  sqlScripts_qyWebContactTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 //
 int  sqlScripts_qyWebGuestTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 //
 int  sqlScripts_qyMessengerPhoneInfoTab_isMgr(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 int  sqlScripts_qyMessengerPhoneInfoTab_isClient(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 //
 int  sqlScripts_qyPhoneGuestTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 //
 int  sqlScripts_qyImOtherRegInfoTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );


 int  sqlScripts_qyImInternalSchedulerTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );

 //
 int  sqlScripts_qyTmpAvTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );

 //
 int  sqlScripts_qyImStatusTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );

 int  sqlScripts_qyVDevComTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 int  sqlScripts_qySmContactTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );

 int  sqlScripts_qyDynBmpTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 int  sqlScripts_qyDynBmpRuleTab(  CString  *  sqlStr,  unsigned  int  uiMaxCnt,  int  *  piCnt,  char  *	pAutoincrement,  char  *  p_nchar,  char  *  p_nvarchar  );
 
 	 


 int  makeDb_isClient(  LPCWSTR  dbTypeName,  char  *  servIp,  LPCWSTR  uid,  LPCWSTR  pwd,  LPCWSTR  dbName,  int  iServiceId,  int  iSystemId,  int  iAppType,  char  *  dbVer  )
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
	 //  TCHAR			sqlBuf[4096];
	 //  char			buf[1024];

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


	 if  (  sqlScripts_qyTestTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt  )  )  goto  errLabel;

	 //  主表
	 if  (  sqlScripts_qyImObjTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  认证信息表
	 if  (  sqlScripts_qyImObjAuthTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;


	 //  认证临时表, 临时表有一些信息放在一个表中更容易处理，所以和正式表的项不能一样
	 if  (  sqlScripts_qyImObjAuthTmpTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  消息历史表, 2007/08/09
	 if  (  sqlScripts_qyImMsgTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  任务表，2007/06/25
	 if  (  sqlScripts_qyImTaskTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar,  FALSE  )  )  goto  errLabel;


	 //  任务历史表，2007/08/09
	 if  (  sqlScripts_qyImTaskTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar,  TRUE  )  )  goto  errLabel;

	 //  2010/08/12
	 if  (  sqlScripts_qyImObjRuleTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //
	 if  (  sqlScripts_qyImStatusTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  2007/08/03
	 if  (  sqlScripts_qyMessengerPcInfoTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 if  (  sqlScripts_qyImObjRegInfoTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar,  FALSE  )  )  goto  errLabel;

	 if  (  sqlScripts_qyImObjRegInfoTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar,  TRUE  )  )  goto  errLabel;

	 if  (  sqlScripts_qyImEventTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  2007/08/22
	 if  (  sqlScripts_qyImGrpInfoTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 if  (  sqlScripts_qyImGrpMemTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;


	 //  2007/11/17
	 if  (  sqlScripts_qyWebGuestTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;
	 
	 //
	 if  (  sqlScripts_qyMessengerPhoneInfoTab_isClient(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;
	 if  (  sqlScripts_qyPhoneGuestTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //
	 if  (  sqlScripts_qyImOtherRegInfoTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  2009/09/03
	 if  (  sqlScripts_qyDynBmpTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //
	 //
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyMessengerStatusTab("
										"id	"  +  pAutoincrement  +  ","
										"idStr				char(20) not null,"
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"constraint tmpIndex_qyMessengerStatusTab unique(misServName,idStr),"										
										//
										"ip					char(15) not null,"
										"clientVer			char(8),"
										"startTime			char(14) not null,"
										"lastCommTime		char(14) not null,"
										"uiLangId			int,"						//  2005/01/22, 语种
										"iPlatformId		int,"						//  2005/01/22，操作系统类型
										//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;



	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyMessengerSessionTab("
										"id	"  +  pAutoincrement  +  ","
										"idStr_from				char(20) not null,"
										"idStr_to				char(20) not null,"
										"firstTime					char(14),"
										"lastTime					char(14),"
										"iStatus					int,"				//  未绑定，绑定，或未执行，或无法执行
										+	"comment0		varchar(255)"
										")";
	 cnt  ++  ;


	 if  (  sqlScripts_qyImInternalSchedulerTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  2009/01/29
	 if  (  sqlScripts_qyTmpAvTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //
	 if  (  sqlScripts_qyObjIndexTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  2007/09/15
	 if  (  sqlScripts_qyCusNameTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  2007/03/11, 对msg_qwm的mdb, 可能暂时把用户的认证取消掉
	 if  (  sqlScripts_qyUsrTabs(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 if  (  sqlScripts_qySystemInfoTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  iServiceId,  iSystemId,  iAppType,  CString(  "qyMsg"  ),  dbVer  )  )  goto  errLabel;


	 //  建最后一个测试建库结束的表
	 if  (  sqlScripts_qyTestEndTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt  )  )  goto  errLabel;

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
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "makeDb_isClient failed."  )  );
		   goto  errLabel;
	}

	iErr  =  0;
		
errLabel:

	if  (  pDb  )  delete  pDb;

	return  iErr;
	 	
}
 
//
 int  getDbConnType(  int  iDbType  );

 //
 int  makeDb_isMgr(  LPCWSTR  dbTypeName,  bool  bDsnless,  char  *  driver,  char  *  servName,  unsigned  char  ucbUseWinAuth,  LPCWSTR  uid,  LPCWSTR  pwd,  LPCWSTR  dbName,  int  iServiceId,  int  iSystemId,  int  iAppType,  char  *  dbVer  )
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
	 //  TCHAR			sqlBuf[4096];
	 //  char			buf[1024];

	 //
	 iDbType  =  qyGetTypeByDes(  CONST_dbTypeTable,  dbTypeName  );
	 
	 //	 
	 int  iDbConnType  =  getDbConnType(  iDbType  );  
	 //unsigned  char  ucbDsnless =  true;
	 //
	 if  (  constructDbConnectStr(  iDbType,  iDbConnType,  bDsnless,  driver,  servName,  ucbUseWinAuth,  dbName,  uid,  pwd,  connectStrBuf,  mycountof(  connectStrBuf  )  )  )  {
		 goto  errLabel;
	 }

	 //
	 if  (  iDbType  ==  CONST_dbType_access  )  {

		 //
		 pAutoincrement		=  CONST_autoincrement_access;
		 p_nchar			=  CONST_nchar_access;
		 p_nvarchar			=  CONST_nvarchar_access;
		}
	 else  if  (  iDbType  ==  CONST_dbType_sqlServer  )  {
		   //
			pAutoincrement  =  CONST_autoincrement_sqlServer;
			p_nchar			=  CONST_nchar_sqlServer;
			p_nvarchar		=  CONST_nvarchar_sqlServer;
	 }
	 else  if  (  iDbType  ==  CONST_dbType_mySql
		 ||  iDbType  ==  CONST_dbType_mariaDb  )  
	 {
		   //
			pAutoincrement  =  CONST_autoincrement_mySql;
			p_nchar			=  CONST_nchar_mySql;
			p_nvarchar		=  CONST_nvarchar_mySql;
			   }
	 else  if (iDbType == CONST_dbType_oscar) {
		 //
#if 10
		 pAutoincrement = CONST_autoincrement_oscar;
		 p_nchar = CONST_nchar_oscar;
		 p_nvarchar = CONST_nvarchar_oscar;
#endif
		 //

	 }
	 else  {
		   traceLog(  _T(  "makeDb_isMgr failed, unsupported dbType"  )  );
		   goto  errLabel;
	 }




	 //
	 if  (  sqlScripts_qyTestTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt  )  )  goto  errLabel;

	 //  以下是Oracle数据库前的建库工作
	 
	 //  主表
	 if  (  sqlScripts_qyImObjTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  认证信息表
	 if  (  sqlScripts_qyImObjAuthTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  认证临时表, 临时表有一些信息放在一个表中更容易处理，所以和正式表的项不能一样
	 if  (  sqlScripts_qyImObjAuthTmpTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  2010/01/04
	 if  (  sqlScripts_qyImAmTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  存储的是临时的信息
	 if  (  sqlScripts_qyLoginTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;


	 //  消息历史表, 2007/08/09
	 if  (  sqlScripts_qyImMsgTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  任务表，2007/06/25
	 if  (  sqlScripts_qyImTaskTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar,  FALSE  )  )  goto  errLabel;

	 //  任务历史表，2007/08/09
	 if  (  sqlScripts_qyImTaskTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar,  TRUE  )  )  goto  errLabel;

	 //  2010/08/12
	 if  (  sqlScripts_qyImObjRuleTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //
	 if  (  sqlScripts_qyImStatusTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  2007/08/03
	 if  (  sqlScripts_qyMessengerPcInfoTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 if  (  sqlScripts_qyImObjRegInfoTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar,  FALSE  )  )  goto  errLabel;

	 if  (  sqlScripts_qyImObjRegInfoTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar,  TRUE  )  )  goto  errLabel;

	 if  (  sqlScripts_qyImEventTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  2007/08/22
	 if  (  sqlScripts_qyImGrpInfoTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 if  (  sqlScripts_qyImGrpMemTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //
	 if (sqlScripts_qyImGrpInfoExTab(sqlStr, mycountof(sqlStr), &cnt, pAutoincrement, p_nchar, p_nvarchar))  goto  errLabel;



	 //  2011/04/02
	 if  (  sqlScripts_qyCustomerServiceObjTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  2007/12/23
	 if  (  sqlScripts_qyIpKnowledgeTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  2007/11/17		 
	 if  (  sqlScripts_qyWebContactTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;
	 //
	 if  (  sqlScripts_qyWebGuestTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //
	 if  (  sqlScripts_qyMessengerPhoneInfoTab_isMgr(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;
	 //
	 if  (  sqlScripts_qyPhoneGuestTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //
	 if  (  sqlScripts_qyImOtherRegInfoTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;
	 
	 //
	 if  (  sqlScripts_qyVDevComTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;
	 if  (  sqlScripts_qySmContactTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 // 
	 if  (  sqlScripts_qyDynBmpTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;
	 if  (  sqlScripts_qyDynBmpRuleTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;
	 
	 
	 //
	 //
	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyMessengerStatusTab("
										"id	"  +  pAutoincrement  +  ","
										"idStr				char(20) not null,"
										"misServName			"  +  getDataType(  p_nvarchar,  255  )  +  " not null,"		//  varchar(255),"							
										"constraint tmpIndex_qyMessengerStatusTab unique(misServName,idStr),"										
										"ip					char(15) not null,"
										"clientVer			char(8),"
										"startTime			char(14) not null,"
										"lastCommTime		char(14) not null,"
										"uiLangId			int,"						//  2005/01/22, 语种
										"iPlatformId		int,"						//  2005/01/22，操作系统类型
										//
										"comment0			varchar(255)"										
										")";	 
	 cnt  ++  ;

	 
	 //  qyPcRegInfoTab1为提供已审核的重复注册信息的存储空间，和qyPcRegInfoTab完全雷同

	 sqlStr[cnt]  =  CString(  ""  )  +  "create table qyMessengerSessionTab("
										"id	"  +  pAutoincrement  +  ","
										"idStr_from				char(20) not null,"
										"idStr_to				char(20) not null,"
										"firstTime					char(14),"
										"lastTime					char(14),"
										"iStatus					int,"				//  未绑定，绑定，或未执行，或无法执行
										+	"comment0		varchar(255)"
										")";
	 cnt  ++  ;



	 //  2007/09/03
	 if  (  sqlScripts_qyImInternalSchedulerTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 if  (  sqlScripts_qyObjIndexTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //  2007/09/15
	 if  (  sqlScripts_qyCusNameTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 //
	 if  (  sqlScripts_qyUsrTabs(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  pAutoincrement,  p_nchar,  p_nvarchar  )  )  goto  errLabel;

	 if  (  sqlScripts_qySystemInfoTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt,  iServiceId,  iSystemId,  iAppType,  CString(  "qyMsg"  ),  dbVer  )  )  goto  errLabel;

	 if  (  sqlScripts_qyTestEndTab(  sqlStr,  mycountof(  sqlStr  ),  &cnt  )  )  goto  errLabel;


	 try  {
		pDb = new  CDatabase;
		if  (  !pDb  )  goto  errLabel;
		if  (  !pDb->OpenEx(  CString(  connectStrBuf  ),  CONST_qyDbOpenOptions  )  )  goto errLabel;
		
		OutputDebugString(  _T(  "make db start\n"  )  );
		for  (  i  =  0;  i  <  cnt;  i  ++  )  {
			 OutputDebugString(  sqlStr[i].GetBuffer(  0  )  );  OutputDebugString(  _T(  "\n"  )  );
			 pDb->ExecuteSQL(  sqlStr[i]  );
		}
		OutputDebugString(  _T(  "make db ok \n"  )  );
		//  AfxMessageBox(  "建库结束"  );
		
		}
	catch  (  CException  *  e  )  {
		   #ifdef  __DEBUG__
				   e->ReportError(  );
		   #endif
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "makeDb_isMgr failed."  )  );
		   goto  errLabel;
	}

	iErr  =  0;
		
errLabel:

	if  (  pDb  )  delete  pDb;

	return  iErr;
	 	
}
