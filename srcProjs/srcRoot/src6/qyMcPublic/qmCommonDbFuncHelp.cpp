

#include	"stdafx.h"
#include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>

#include	"qyCommon.h"
#include	"qwmAllHints.h"

//#include	"qyCusResPublic.h"
//#include	"qyCusResTemp.h"
#include	"qmOpenCommon.h"

#include	"qyString.h"

#include	"qmCommon.h"
#include	"qyDbCommon.h"
#include	"qyTCharCommProc.h"

#include	"qySyncObj.h"

#include	"genericQueue.h"

#include	"myDb.h"

//
 BOOL  bGetSystemInfo_myDb(  void  *  pDbParam,  int  iDbType,  QY_SYSTEMINFO_RCD  *  pSystemInfo  )
{
	BOOL		bRet	=	FALSE;

	if  (  pSystemInfo  )  {
		
		memset(  pSystemInfo,  0,  sizeof(  pSystemInfo[0]  )  );
		
		pSystemInfo->iSystemId  =  qyGetSystemId(  );			
		pSystemInfo->iAppType  =  qyGetAppType(  pSystemInfo->iSystemId,  _T(  CONST_qyRootKey_mcGui_netMc  )  );		//  2004/05/23ÐÞ¸Ä
		pSystemInfo->iServiceId  =  qyGetServiceId(  pSystemInfo->iSystemId  );
		//  mycountof(  pSystemInfo->name  )  );
		safeStrnCpy(  qnmDbVerStr(  pSystemInfo->iServiceId  ),  pSystemInfo->dbVer,  mycountof(  pSystemInfo->dbVer  )  );
	}

	bRet  =  TRUE;
	return  bRet;

}

 BOOL  bGetSystemInfo_odbc(  void  *  pDbParam,  int  iDbType,  QY_SYSTEMINFO_RCD  *  pSystemInfo  )
{
	BOOL			bRet							=		FALSE;
	CString			sqlStr;
	CDBVariant		varVals[10];
	int				index;
	TCHAR			tBuf[255  +  1]					=		_T(  ""  );

	sqlStr  =  CString(  "select iServiceId,iSystemId,iAppType,name,dbVer from qySystemInfoTab"  );
	if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr,  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;

	if  (  pSystemInfo  )  {
		
		memset(  pSystemInfo,  0,  sizeof(  pSystemInfo[0]  )  );

		index  =  0;  MACRO_sqlLong(  varVals[index],  pSystemInfo->iServiceId  );
		index  ++  ;  MACRO_sqlLong(  varVals[index],  pSystemInfo->iSystemId  );
		index  ++  ;  MACRO_sqlLong(  varVals[index],  pSystemInfo->iAppType  );
		index  ++  ;  MACRO_sqlStr(  varVals[index],  pSystemInfo->name,  mycountof(  pSystemInfo->name  )  );
		index  ++  ;  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pSystemInfo->dbVer,  mycountof(  pSystemInfo->dbVer  )  );
		index  ++  ;
	}

	bRet  =  TRUE;
errLabel:
	return  bRet;
}

  __declspec(  dllexport  )  BOOL  bGetSystemInfo(  void  *  pDbParam,  int  iDbType,  QY_SYSTEMINFO_RCD  *  pSystemInfo  )
{
	switch  (  iDbType  )  {
			case  CONST_dbType_myDb:  {
				  return  bGetSystemInfo_myDb(  pDbParam,  iDbType,  pSystemInfo  );
				  }
				  break;
			default:
					break;
	}
	return  bGetSystemInfo_odbc(  pDbParam,  iDbType,  pSystemInfo  );
}


 //  2006/07/16
 //  nValVals
 //  pf
 __declspec(  dllexport  )  int  enumSqlQuery(  void  *  pDb,  LPCTSTR  sqlBuf,  PF_commonHandler  pf,  void  *  p0,  void  *  p1,  void  *  pVarValsParam,  unsigned  int  nVarVals,  unsigned  int  *  puiRcdCnt  )
{
	 int								iRet					=			-1;
	 CDBVariant			*				pVarVals				=			(  CDBVariant  *  )pVarValsParam;
	 unsigned  int						index					=			0;
	 CRecordset							rs;   
	 unsigned  int						nFields					=			0;
	 int								tmpiRet					=			-1;
	 unsigned  int						uiRcdCnt				=			0;

	 if  (  !pDb  ||  !pVarVals  ||  !nVarVals  )  goto  errLabel;

	 try  {		

		  rs.m_pDatabase  =  (  CDatabase  * )pDb;
		  if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
			  traceLogA(  "rs open() failed, sqlBuf is %s",  sqlBuf  );  goto  errLabel;
		  }
					   
		  nFields  =  rs.GetODBCFieldCount(  );
		  if  (  nFields  >  nVarVals  )  {
			  traceLogA(  "bEnumSqlQuery failed: countof pVarVals is not enough"  );  goto  errLabel;
		  }		
		  //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
		  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
		  
			   for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  pVarVals[index]  );

			   uiRcdCnt  ++  ;

			   if  (  pf  &&  (  tmpiRet  =  pf(  p0,  p1,  pVarVals  )  )  )  {
				   iRet  =  tmpiRet;  goto  errLabel;						
			   }
			 
		  }
				 	
			}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  L"Is",  0,  L"",  L"",  L"enumSqlQuery failed."  );
		   goto  errLabel;
	}
		 
	 iRet  =  0;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	 
	 if  (  !iRet  )  {
		 if  (  puiRcdCnt  )  *puiRcdCnt  =  uiRcdCnt;
	 }

	
	 return  iRet;		

}

 __declspec(  dllexport  )  BOOL  bSqlObjExists(  void  *  pDb,  LPCTSTR  sqlBuf  )
{
	 CDBVariant  varVal[1];

	 if  (  bQyGetRcdBySql(  pDb,  sqlBuf,  1,  varVal  )  
		 &&  getCntFromVarVal(  varVal  )  )
	 {
		 return  TRUE;
	 }

	 return  FALSE;

}
