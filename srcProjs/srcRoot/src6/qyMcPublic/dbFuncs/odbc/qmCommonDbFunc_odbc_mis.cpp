
#include	"stdafx.h"
#include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>

#include	"qmCommon.h"
#include	"qyDbCommon.h"
#include	"qyTCharCommProc.h"
#include	"myDb.h"

#ifdef  __isCli__
		#include	"qyMcMainCommon.h"    //  2013/02/08
		#include	"qmcCommFunc_isCli.h"
#endif
//  #include	"qyCusResTemp.h"

#define		CONST_tmpStr						CString(  "1=1"  )

 //  2013/02/19
 //BOOL  bGetImAmRcdBySth_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  LPCTSTR  messengerName,  int  id,  QY_imAm_RCD  *  pObj  )
BOOL  bGetImAmRcdBySth_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  short  usAuthType,  LPCTSTR  messengerName,  int  id,  QY_imAm_RCD  *  pObj  )
{
	 BOOL			bRet						=		FALSE;
	 CString		sqlStr;
	 CString		whereStr;
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index						=		0;
	 char			ip12Buf[128]				=		"";
	 TCHAR			tBuf[256  +  1];
	 char			buf[256  +  1];
	 int			i;

	 
	 if  (  !pDbParam  )  return  FALSE;

				//						  0			   1			2		   3			  4			     5				6				  7				8					9
	 sqlStr  =  CString(  "select id,misServName,idStr,usAuthType,messengerName,messengerPasswd,iPasswdType,salt,iStatus,startTime,tLastModifiedTime"  )
					+  _T(  " from "  )  +  CONST_tabName_qyImAmTab;
	 whereStr  =  CONST_tmpStr;
	 if  (  misServName  &&  pIdInfo  &&  pIdInfo->ui64Id  )  {
		 idInfo2Str(  pIdInfo,  buf,  mycountof(  buf  )  );
		 whereStr  =  whereStr  +  _T(  " and misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  +  _T(  " and idStr='"  )  +  CString(  buf  )  +  _T(  "'"  );
		 }
	 else  if  (  misServName  &&  messengerName  &&  messengerName[0]  )  {
			   whereStr  =  whereStr  +  _T(  " and misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  +  _T(  " and messengerName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_name,  messengerName  );
			   }
	 else  {
		   whereStr  =  whereStr  +  _T(  " and id="  )  +  _ltot(  id,  tBuf,  10  );
	 }
	 
	 if  (  whereStr  ==  CONST_tmpStr  )  {
		 traceLogA(  ""  );  goto  errLabel;
	 }
	 sqlStr  =  sqlStr  +  _T(  " where "  )  +  whereStr;
	 traceLogA(  "sql is [%s]",  sqlStr.GetBuffer(  0  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;
	 
	 if  (  pObj  )  {	
		 //
		 memset(  pObj,  0,  sizeof(  pObj[0]  )  );
		 //
		 index  =  0;	//  id  
		 MACRO_sqlLong(  varVals[index],  pObj->id  );
		 index  ++  ;	//  misServName
		 MACRO_sqlStr(  varVals[index],  pObj->misServName,  mycountof(  pObj->misServName  )  );  
		 index  ++  ;	//  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pObj->idInfo  );
		 //
		 index  ++  ;  //  usAuthType;
		 MACRO_sqlLong(  varVals[index],  pObj->usAuthType  );
		 //
		 index  ++  ;  //  messengerName
		 MACRO_sqlStr(  varVals[index],  pObj->messengerName,  mycountof(  pObj->messengerName  )  );
		 index  ++  ;  //  messengerPasswd
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  (  char  *  )pObj->messengerPasswd,  sizeof(  pObj->messengerPasswd  )  );  
		 index  ++  ;  //  iPasswdType
		 MACRO_sqlLong(  varVals[index],  pObj->iPasswdType  );
		 index  ++  ;  //  salt
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );	myTChar2Str(  tBuf,  pObj->salt,  mycountof(  pObj->salt  )  );
		 index  ++  ;  //  iStatus
		 MACRO_sqlLong(  varVals[index],  pObj->iStatus  );
  		 index  ++  ;  //  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->startTime,  sizeof(  pObj->startTime  )  );
		 index  ++  ;	//  tLastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->tLastModifiedTime,  sizeof(  pObj->tLastModifiedTime  )  );
		 index  ++  ;

		 //  MACRO_qyAssert(  index  ==  10,  "bGetPcInfoByMac0Ex: index错误"  );

	 }
	 	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}

 //  2013/02/04
 BOOL  bGetMessengerRegInfoBySth_odbc(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  )
{
	 BOOL			bRet									=		FALSE;
	 CString		sqlStr;
	 TCHAR			whereBuf[CONST_maxSqlBufLen  +  1]		=		_T(  ""  );
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index									=		0;
	 int			i;
	 char			ip12Buf[128]							=		"";
	 char			idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 TCHAR			tBuf[256  +  1];
	 char			buf[256  +  1]							=		"";
	 long			lVal									=		0;
	 	 
	 if  (  !pTabName  )  return  FALSE;

	 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s"  ),  CONST_tmpStr.GetBuffer(  0  )  );
	 if  (  misServName  &&  pIdInfo  )  {
		 if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
		 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and misServName=%s and idStr='%s'"  ),  whereBuf,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
		}
	 else  {
		   _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and id=%d"  ),  whereBuf,  iRcdId  );
	 }
	 

	 //
	 sqlStr  =  CString(  "select"  )  
	 	 					//			1			2						(  +  30  )												
				+  _T(  " misServName,idStr,regTime,auditTime,tCommitTime,tLastModifiedTime,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,col20,col21,col22,col23,col24,col25,col26,col27,col28,col29"  ) 
				+  _T(  " from "  )  +  pTabName
				+  _T(  " where "  )  +  whereBuf;
	 OutputDebugString(  sqlStr  +  _T(  "\n"  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;
	
	 if  (  pRegInfo  )  {

		 memset(  pRegInfo,  0,  sizeof(  pRegInfo[0]  )  );
		 //
		 pRegInfo->uiType  =  CONST_imCommType_messengerRegInfo;
		 pRegInfo->iCustomId  =  qyGetCustomId(  );
		 //
		 MACRO_setFieldIdInRegInfo(  pRegInfo[0]  );
		 MACRO_setPtrs(  pFieldIdTable,  pRegInfo[0],  pRegInfo->fields  );


		 index  =  0;	//  misServName
		 MACRO_sqlStr(  varVals[index],  pRegInfo->addr.misServName,  mycountof(  pRegInfo->addr.misServName  )  );
		 index  ++  ;	//  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &pRegInfo->addr.idInfo  );
		 index  ++  ;	//  regTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->regTime,  mycountof(  pRegInfo->regTime  )  );  
		 index  ++  ;	//  auditTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->auditTime,  mycountof(  pRegInfo->auditTime  )  );  
		 index  ++  ;	//  tComminTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->tCommitTime,  mycountof(  pRegInfo->tCommitTime  )  );  
		 index  ++  ;	//  lastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->tLastModifiedTime,  mycountof(  pRegInfo->tLastModifiedTime  )  );
		 index  ++  ;
			 
		 for  (  i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
			  MACRO_sqlStr(  varVals[i  +  index],  pRegInfo->fields[i].ptr,  pRegInfo->fields[i].bufSize  );
		 }
		 index  +=  i;
	 
	 }
 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}

 BOOL  bGetImOtherRegInfoBySth_odbc(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  MSGR_ADDR  *  pAddr,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  )
{
	 BOOL			bRet									=		FALSE;
	 CString		sqlStr;
	 TCHAR			whereBuf[CONST_maxSqlBufLen  +  1]		=		_T(  ""  );
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index									=		0;
	 int			i;
	 char			ip12Buf[128]							=		"";
	 char			idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 TCHAR			tBuf[256  +  1];
	 char			buf[256  +  1]							=		"";
	 long			lVal									=		0;
	 	 
	 if  (  !pTabName  )  return  FALSE;

	 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s"  ),  CONST_tmpStr.GetBuffer(  0  )  );
	 if  (  pAddr  )  {
		 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and misServName=%s and uiDevType=%d and wDevIdStr=%s"  ),  whereBuf,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pAddr->misServName  ),  pAddr->uiDevType,  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  pAddr->wDevIdStr  )  );
		}
	 else  {
		   _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and id=%d"  ),  whereBuf,  iRcdId  );
	 }
	 

	 //
	 sqlStr  =  CString(  "select"  )  
	 	 					//			1			2						(  +  30  )												
				+  _T(  " id,misServName,uiDevType,wDevIdStr,regTime,auditTime,tCommitTime,tLastModifiedTime,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,col20,col21,col22,col23,col24,col25,col26,col27,col28,col29"  ) 
				+  _T(  " from "  )  +  pTabName
				+  _T(  " where "  )  +  whereBuf;
	 OutputDebugString(  sqlStr  +  _T(  "\n"  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;
	
	 if  (  pRegInfo  )  {

		 memset(  pRegInfo,  0,  sizeof(  pRegInfo[0]  )  );
		 //
		 pRegInfo->uiType  =  CONST_imCommType_messengerRegInfo;
		 pRegInfo->iCustomId  =  qyGetCustomId(  );
		 //
		 MACRO_setFieldIdInRegInfo(  pRegInfo[0]  );
		 MACRO_setPtrs(  pFieldIdTable,  pRegInfo[0],  pRegInfo->fields  );


		 index  =  0;	//  id
		 MACRO_sqlLong(  varVals[index],  pRegInfo->id  );
		 index  ++  ;	//  misServName
		 MACRO_sqlStr(  varVals[index],  pRegInfo->addr.misServName,  mycountof(  pRegInfo->addr.misServName  )  );
		 index  ++  ;	//  uiDevType
		 MACRO_sqlLong(  varVals[index],  pRegInfo->addr.uiDevType  );
		 index  ++  ;	//  wDevIdStr
		 MACRO_sqlStr(  varVals[index],  pRegInfo->addr.wDevIdStr,  mycountof(  pRegInfo->addr.wDevIdStr  )  );  
		 index  ++  ;	//  regTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->regTime,  mycountof(  pRegInfo->regTime  )  );  
		 index  ++  ;	//  auditTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->auditTime,  mycountof(  pRegInfo->auditTime  )  );  
		 index  ++  ;	//  tComminTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->tCommitTime,  mycountof(  pRegInfo->tCommitTime  )  );  
		 index  ++  ;	//  lastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->tLastModifiedTime,  mycountof(  pRegInfo->tLastModifiedTime  )  );
		 index  ++  ;
			 
		 for  (  i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
			  MACRO_sqlStr(  varVals[i  +  index],  pRegInfo->fields[i].ptr,  pRegInfo->fields[i].bufSize  );
		 }
		 index  +=  i;
	 
	 }
 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}



 //  2013/02/05
 BOOL  bGetMeInfoBySth_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_INFO  *  pObj  )
{
	 BOOL			bRet									=		FALSE;
	 TCHAR			sqlBuf[1024];
	 CDBVariant		varVals[2];
	 int			index;
	 TCHAR			tBuf[256];
	 char			idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";

	 if  (  !misServName  )  misServName  =  _T(  ""  );

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select idStr,uiType from qyImObjTab where misServName=%s and uiType=%d"  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CONST_objType_me  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlBuf,  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;

	 if  (  pObj  )  {
		 memset(  pObj,  0,  sizeof(  pObj[0]  )  );
		 //
		 lstrcpyn(  pObj->misServName,  misServName,  mycountof(  pObj->misServName  )  );

		 index  =  0;  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  idStr,  mycountof(  idStr  )  );  if  (  !idStr2Info(  idStr,  &pObj->idInfo  )  )  goto  errLabel;
		 index  ++  ;  MACRO_sqlLong(  varVals[index],  pObj->uiType  );

	 }

	 bRet  =  TRUE;

errLabel:

	 return  bRet;
}

 //
 //BOOL  bGetMessengerInfoBySth_odbc(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_INFO  *  pObjParam,  QY_MESSENGER_REGINFO  *  pRegInfo,  QY_MESSENGER_REGINFO  *  pRegInfoInTab1,  QY_MESSENGER_phoneInfo  *  pPhoneInfo  )
 BOOL  bGetMessengerInfoBySth_odbc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_INFO  *  pObjParam,  QY_MESSENGER_REGINFO  *  pRegInfo,  QY_MESSENGER_REGINFO  *  pRegInfoInTab1,  QY_MESSENGER_phoneInfo  *  pPhoneInfo  )
{
	//
	if  (  !pDbFuncs  )  return  FALSE;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;

	//
	 BOOL					bRet									=		FALSE;
	 CString				sqlStr;
	 TCHAR					whereBuf[CONST_maxSqlBufLen  +  1]		=		_T(  ""  );
	 CDBVariant				varVals[15  +  CONST_qnmMaxRegFields];
	 int					index									=		0;
	 int					i;
	 char					ip12Buf[128]							=		"";
	 char					idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 TCHAR					tBuf[256  +  1];
	 char					buf[256  +  1]							=		"";
	 long					lVal									=		0;
	 QY_MESSENGER_INFO		tmpObjInfo;
	 QY_MESSENGER_INFO	*	pObj									=		NULL;
	 

	 //
	 if  (  !misServName  )  misServName  =  _T(  ""  );

				//				  0		   1	2		   3			  4			     5				6		  7				8					9          10
	 sqlStr  =  CString(  "select id,uiType,misServName,idStr,ip,detectedIp,usLangId,uiDevType,messengerName,iRole,startTime,usRunningStatus,tLastModifiedTime,iStatus"  )
					+  _T(  " from "  )  +  CONST_tabName_qyImObjTab;
	 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s"  ),  CONST_tmpStr.GetBuffer(  0  )  );
	 if  (  misServName  &&  pIdInfo  )  {
		 if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
		 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and misServName=%s and idStr='%s'"  ),  whereBuf,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
		}
	 else  {
		   _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and id=%d"  ),  whereBuf,  iRcdId  );
	 }

	 sqlStr  =  sqlStr  +  _T(  " where "  )  +  whereBuf;
	 traceLogA(  "sql is [%S]",  sqlStr.GetBuffer(  0  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;
	 
	 pObj  =  pObjParam  ?  pObjParam  :  &tmpObjInfo;	//  注意，这里，因为下面的regInfo都要用到uiType, 所以，这里是一定需要把信息取出来的。
	 
	 if  (  pObj  )  {	
		 //
		 memset(  pObj,  0,  sizeof(  pObj[0]  )  );
		 //
		 index  =  0;	//  id
		 MACRO_sqlLong(  varVals[index],  pObj->iRcdId  );
		 index  ++  ;	//  uiType		 
		 MACRO_sqlLong(  varVals[index],  pObj->uiType  );
		 index  ++  ;	//  misServName
		 MACRO_sqlStr(  varVals[index],  pObj->misServName,  mycountof(  pObj->misServName  )  );  
		 index  ++  ;	//  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  idStr,  mycountof(  idStr  )  );  if  (  !idStr2Info(  idStr,  &pObj->idInfo  )  )  goto  errLabel;
		 index  ++  ;	//  ip
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12Buf,  mycountof(  ip12Buf  )  );  qyIp12ToStd(  ip12Buf,  pObj->ip  );  
		 index  ++  ;	//  detectedIp
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12Buf,  mycountof(  ip12Buf  )  );  qyIp12ToStd(  ip12Buf,  pObj->detectedIp  );  
		 index  ++  ;	//  usLangId
		 MACRO_sqlLong(  varVals[index],  lVal  );  pObj->usLangId  =  (  unsigned  short  )lVal;
		 index  ++  ;	//  uiDevType
		 MACRO_sqlLong(  varVals[index],  pObj->uiDevType  );
		 index  ++  ;	//  messengerName
		 MACRO_sqlStr(  varVals[index],  pObj->messengerName,  mycountof(  pObj->messengerName  )  );  
		 index  ++  ;	//  iRole. 2017/08/14
		 MACRO_sqlLong(  varVals[index],  pObj->iRole  );
		 index  ++  ;	//  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pObj->startTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	//  usRunningStatus
		 MACRO_sqlLong(  varVals[index],  lVal  );  pObj->usRunningStatus  =  (  unsigned  short  )lVal;
		 index  ++  ;	//  tLastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pObj->tLastModifiedTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	//  iStatus
		 MACRO_sqlLong(  varVals[index],  pObj->iStatus  );
		 index  ++  ;

		 //  MACRO_qyAssert(  index  ==  10,  "bGetPcInfoByMac0Ex: index错误"  );

		 //  这2个参数是为下面的
		 if  (  !misServName  )  misServName  =  pObj->misServName;
		 if  (  !idInfo2Str(  &pObj->idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
	 }

	 if  (  !misServName  ||  !bMessengerIdStrValid(  idStr  )  )  goto  errLabel;
	 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s"  ),  CONST_tmpStr.GetBuffer(  0  )  );
	 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and misServName=%s and idStr='%s'"  ),  whereBuf,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );

	 if  (  pRegInfo  )  {
		 //
		 memset(  pRegInfo,  0,  sizeof(  pRegInfo[0]  )  );
		 //
		 pRegInfo->uiType  =  CONST_imCommType_messengerRegInfo;
		 pRegInfo->iCustomId  =  qyGetCustomId(  );
		 //
		 MACRO_setFieldIdInRegInfo(  pRegInfo[0]  );
		 MACRO_setPtrs(  pFieldIdTable,  pRegInfo[0],  pRegInfo->fields  );
		 //
		 sqlStr  =  CString(  "select"  )  
	 	 					//			1			2						(  +  30  )												
				+  _T(  " qyImObjRegInfoTab.regTime,qyImObjRegInfoTab.auditTime,qyImObjRegInfoTab.tLastModifiedTime,qyImObjRegInfoTab.col0,qyImObjRegInfoTab.col1,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4,qyImObjRegInfoTab.col5,qyImObjRegInfoTab.col6,qyImObjRegInfoTab.col7,qyImObjRegInfoTab.col8,qyImObjRegInfoTab.col9,qyImObjRegInfoTab.col10,qyImObjRegInfoTab.col11,qyImObjRegInfoTab.col12,qyImObjRegInfoTab.col13,qyImObjRegInfoTab.col14,qyImObjRegInfoTab.col15,qyImObjRegInfoTab.col16,qyImObjRegInfoTab.col17,qyImObjRegInfoTab.col18,qyImObjRegInfoTab.col19,qyImObjRegInfoTab.col20,qyImObjRegInfoTab.col21,qyImObjRegInfoTab.col22,qyImObjRegInfoTab.col23,qyImObjRegInfoTab.col24,qyImObjRegInfoTab.col25,qyImObjRegInfoTab.col26,qyImObjRegInfoTab.col27,qyImObjRegInfoTab.col28,qyImObjRegInfoTab.col29"  )
				+  _T(  " from qyImObjRegInfoTab"  )
				+  _T(  " where "  )  +  whereBuf;
		 OutputDebugString(  sqlStr  +  _T(  "\n"  )  );
		 if  (  bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  {

			 lstrcpyn(  pRegInfo->addr.misServName,  misServName,  mycountof(  pRegInfo->addr.misServName  )  );
			 pRegInfo->addr.uiObjType  =  pObj->uiType;
			 pRegInfo->addr.idInfo.ui64Id  =  pIdInfo->ui64Id;

			 index  =  0;  //  regTime
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->regTime,  mycountof(  pRegInfo->regTime  )  );  
			 index  ++  ;  //  auditTime
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->auditTime,  mycountof(  pRegInfo->auditTime  )  );  
			 index  ++  ;	//  lastModifiedTime
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->tLastModifiedTime,  mycountof(  pRegInfo->tLastModifiedTime  )  );
			 index  ++  ;
			 

			 for  (  i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
				  //  if  (  varVals[i  +  index].m_dwType  ==  DBVT_STRING  )  myTChar2Str(  varVals[i  +  index].m_pstring->GetBuffer(  0  ),  fields[i].ptr,  fields[i].bufSize  );
				  MACRO_sqlStr(  varVals[i  +  index],  pRegInfo->fields[i].ptr,  pRegInfo->fields[i].bufSize  );
	 	 	 }
	 	 	 index  +=  i;
	 	 }
	 
	 }
	 	 
	 if  (  pRegInfoInTab1  )  {
		 //
		 memset(  pRegInfoInTab1,  0,  sizeof(  pRegInfoInTab1[0]  )  );
		 //
		 pRegInfoInTab1->uiType  =  CONST_imCommType_messengerRegInfo;
		 pRegInfoInTab1->iCustomId  =  qyGetCustomId(  );
		 //
		 MACRO_setFieldIdInRegInfo(  pRegInfoInTab1[0]  );
		 MACRO_setPtrs(  pFieldIdTable,  pRegInfoInTab1[0],  pRegInfoInTab1->fields  );
		 //
		 sqlStr  =  CString(  "select"  )  
	 	 					//			1			2						(  +  30  )												
				+  _T(  " qyImObjRegInfoTab1.regTime,qyImObjRegInfoTab1.auditTime,qyImObjRegInfoTab1.tCommitTime,qyImObjRegInfoTab1.col0,qyImObjRegInfoTab1.col1,qyImObjRegInfoTab1.col2,qyImObjRegInfoTab1.col3,qyImObjRegInfoTab1.col4,qyImObjRegInfoTab1.col5,qyImObjRegInfoTab1.col6,qyImObjRegInfoTab1.col7,qyImObjRegInfoTab1.col8,qyImObjRegInfoTab1.col9,qyImObjRegInfoTab1.col10,qyImObjRegInfoTab1.col11,qyImObjRegInfoTab1.col12,qyImObjRegInfoTab1.col13,qyImObjRegInfoTab1.col14,qyImObjRegInfoTab1.col15,qyImObjRegInfoTab1.col16,qyImObjRegInfoTab1.col17,qyImObjRegInfoTab1.col18,qyImObjRegInfoTab1.col19,qyImObjRegInfoTab1.col20,qyImObjRegInfoTab1.col21,qyImObjRegInfoTab1.col22,qyImObjRegInfoTab1.col23,qyImObjRegInfoTab1.col24,qyImObjRegInfoTab1.col25,qyImObjRegInfoTab1.col26,qyImObjRegInfoTab1.col27,qyImObjRegInfoTab1.col28,qyImObjRegInfoTab1.col29"  )
				+  _T(  " from qyImObjRegInfoTab1"  )
				+  _T(  " where "  )  +  whereBuf;
		 OutputDebugString(  sqlStr  +  _T(  "\n"  )  );
		 if  (  bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  {

			 lstrcpyn(  pRegInfoInTab1->addr.misServName,  misServName,  mycountof(  pRegInfoInTab1->addr.misServName  )  );
			 pRegInfoInTab1->addr.uiObjType  =  pObj->uiType;
			 pRegInfoInTab1->addr.idInfo.ui64Id  =  pIdInfo->ui64Id;

			 index  =  0;	//  regTime
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfoInTab1->regTime,  sizeof(  pRegInfoInTab1->regTime  )  );  
			 index  ++  ;	 //  auditTime	
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfoInTab1->auditTime,  sizeof(  pRegInfoInTab1->auditTime  )  );  
			 index  ++  ;
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfoInTab1->tCommitTime,  sizeof(  pRegInfoInTab1->tCommitTime  )  );  
			 index  ++  ;


			 for  (  i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
				  //  if  (  varVals[i  +  index].m_dwType  ==  DBVT_STRING  )  myTChar2Str(  varVals[i  +  index].m_pstring->GetBuffer(  0  ),  fields[i].ptr,  fields[i].bufSize  );
				  MACRO_sqlStr(  varVals[i  +  index],  pRegInfoInTab1->fields[i].ptr,  pRegInfoInTab1->fields[i].bufSize  );
	 	 	 }
	 	 	 index  +=  i;
		 }

	 }

	 if  (  pPhoneInfo  )  {	//  2008/02/14
		 //
		 if  (  !g_dbFuncs.pf_bGetMessengerPhoneInfoBySth(  pDbParam,  iDbType,  misServName,  0,  0,  pIdInfo,  0,  pPhoneInfo  )  )  memset(  pPhoneInfo,  0,  sizeof(  pPhoneInfo[0]  )  );
	 
	 }


	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}


int  insertImObj_recoverMessenger_odbc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime  )
{
	 int						iErr											=	-1;
	 TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1];
	 char						ip12Buf[CONST_qyMaxIpLen  +  1]					=	"";					//  2007/02/20
	 char						detectedIp12Buf[CONST_qyMaxIpLen  +  1]			=	"";
	 char						idStr[CONST_qyMessengerIdStrLen  +  1]			=	"";

	 time_t						t;
	 char						startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	 char						tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";


	 if  (  !pObj  ||  !bMessengerIdValid(  &pObj->idInfo  )  )  goto  errLabel;
	 if  (  !idInfo2Str(  &pObj->idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
	 	 
	 if  (  !tLastModifiedTime  )  time(  &t  );
	 else  t  =  tLastModifiedTime;
	 getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	 getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );

	 //		    
	 qyStdToIp12(  pObj->ip,  ip12Buf  );	//  2007/02/20
	 qyStdToIp12(  pObj->detectedIp,  detectedIp12Buf  );

	 	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr,uiType,ip,detectedIp,usLangId,uiDevType,messengerName,iRole,startTime,tLastModifiedTime,iStatus,comment0)"  )
																		_T(  "Values(%s,'%s', %d,    '%s', '%s',    %d,      %d,       %s,           %d,  '%s',       '%s',           %d,  '')"  ),
													CONST_tabName_qyImObjTab,
													getDbValStr(  iDbType,  CONST_iDataType_misServName,  pObj->misServName  ),
													CString(  idStr  ),
													pObj->uiType,
													CString(  ip12Buf  ),
													CString(  detectedIp12Buf  ),
													pObj->usLangId,
													pObj->uiDevType,  
													getDbValStr(  iDbType,  CONST_iDataType_messengerName,  pObj->messengerName  ),
													pObj->iRole,  //  2017/08/14
													CString(  startTimeBuf  ),
													CString(  tLastModifiedTimeBuf  ),
													pObj->iStatus  );
	 	 if  (  !bQyExecSql(  pDbParam,  sqlBuf  )  )  goto  errLabel;

		 iErr  =  0;

errLabel:
		 return  iErr;
}


 int  updateImObj_recoverMessenger_odbc(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime,  int  iRcdId  )
{
	 int						iErr											=	-1;
	 TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1];
	 	  time_t						t;
	char						startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	char						tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";

	if  (  !tLastModifiedTime  )  time(  &t  );
	else  t  =  tLastModifiedTime;
	getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );



	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set uiType=%d,iRole=%d,iStatus=%d,tLastModifiedTime='%s' where id=%d"  ),
									CONST_tabName_qyImObjTab,
									pObj->uiType,
									pObj->iRole,
									pObj->iStatus,
									CQyString(  tLastModifiedTimeBuf  ),
									iRcdId  );	
	 if  (  !bQyExecSql(  pDbParam,  sqlBuf  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;
}

  int  updateImObj_recoverMessenger2_odbc(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime,  int  iRcdId  )
  {
	 int						iErr											=	-1;
	 TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1];
	 	  time_t						t;
	char						startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	char						tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";

	if  (  !tLastModifiedTime  )  time(  &t  );
	else  t  =  tLastModifiedTime;
	getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );



	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set tLastModifiedTime='%s' where id=%d"  ),
									CONST_tabName_qyImObjTab,
									CQyString(  tLastModifiedTimeBuf  ),
									iRcdId  );	
	 if  (  !bQyExecSql(  pDbParam,  sqlBuf  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;
	  
  }
 
 //
 int  insertImObj_recoverImGrp_odbc(  void  *  pDb,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime  )
{

	int				iErr										=  -1;
	 TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	 time_t						t;
	 char						startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	 char						tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";

	 //  char				timeBuf[CONST_qyTimeLen  +  1];

	 char				idStr[CONST_qyMessengerIdStrLen  +  1];

	 if  (  !pGrpInfo  )  return  -1;

	 if  (  !idInfo2Str(  &pGrpInfo->idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
	 


	 //
	 if  (  !tLastModifiedTime  )  time(  &t  );
	 else  t  =  tLastModifiedTime;
	 getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	 getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );
	 	 

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr,uiType,iStatus,startTime,tLastModifiedTime)"  )
									_T(  "Values(%s,'%s',%d,%d,'%s','%s')"  ),
									CONST_tabName_qyImObjTab,
									getDbValStr(  iDbType,  CONST_iDataType_misServName,  pGrpInfo->misServName  ),
									CString(  idStr  ),
									uiObjType,
									CONST_qyStatus_ok,
									CString(  startTimeBuf    ),
									CString(  tLastModifiedTimeBuf  )  );		 
		 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

		 iErr  =  0;
errLabel:
		 return  iErr;

}



  int  updateImObj_recoverImGrp_odbc(  void  *  pDb,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  int  iRcdId  )
  {
	  int	iErr	=	-1;
	  TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	  time_t						t;
	char						startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	char						tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";

	if  (  !tLastModifiedTime  )  time(  &t  );
	else  t  =  tLastModifiedTime;
	getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );

	  	  
	  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set uiType=%d,iStatus=%d,tLastModifiedTime='%s' where id=%d"  ),
									CONST_tabName_qyImObjTab,
									uiObjType,
									CONST_qyStatus_ok,
									CQyString(  tLastModifiedTimeBuf  ),
									iRcdId  );
	  if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	  iErr  =  0;
errLabel:			   
	  return  iErr;
  }

  int  updateImObj_recoverImGrp2_odbc(  void  *  pDb,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  int  iRcdId  )
  {
	  int	iErr	=	-1;
	  TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	  time_t						t;
	char						startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	char						tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";

	if  (  !tLastModifiedTime  )  time(  &t  );
	else  t  =  tLastModifiedTime;
	getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );

	  	  
	  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set tLastModifiedTime='%s' where id=%d"  ),
									CONST_tabName_qyImObjTab,
									CQyString(  tLastModifiedTimeBuf  ),
									iRcdId  );
	  if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	  iErr  =  0;
errLabel:			   
	  return  iErr;
  }

  //
 BOOL  bGetImGrpInfoBySth_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  IM_GRP_INFO  *  pRcd  )
{
 	 BOOL			bRet									=		FALSE;
	 CString		sqlStr;
	 CString		whereStr;
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index									=		0;
	 char			ip12Buf[128]							=		"";
	 char			idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 TCHAR			tBuf[256  +  1];
	 char			buf[256  +  1]							=		"";

	 if  (  !misServName  ||  !pIdInfo  )  return  FALSE;

	 if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

				//				   0		   1	2		   3			 4			5	   6		
	 sqlStr  =  CString(  "select id,misServName,idStr,name,subtype,idStr_creator,startTime,tLastModifiedTime"  )
					+  _T(  " from "  )  +  CONST_tabName_qyImGrpInfoTab;
	 whereStr  =  CONST_tmpStr;
	 whereStr  =  whereStr  +  _T(  " and misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  +  _T(  " and idStr="  )  +  getDbValStr(  iDbType,  CONST_iDataType_idStr,  CString(  idStr  )  );
	 if  (  whereStr  ==  CONST_tmpStr  )  {
		 traceLogA(  "条件应该设置"  );  goto  errLabel;
	 }
	 sqlStr  =  sqlStr  +  _T(  " where "  )  +  whereStr;
	 traceLogA(  "sql is [%S]",  sqlStr.GetBuffer(  0  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr,  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;

	 if  (  pRcd  )  {

		 memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

         index  =  0;	 //  id
		 MACRO_sqlLong(  varVals[index],  pRcd->id  );
         index  ++  ;	 //  misServName
		 MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );  
         index  ++  ;	 //  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo  );
		 index  ++  ;	 //  name
		 MACRO_sqlStr(  varVals[index],  pRcd->name,  mycountof(  pRcd->name  )  );  
		 index  ++  ;	//  subtype;
		 MACRO_sqlLong(  varVals[index],  pRcd->usSubtype  );
		 index  ++  ;	 //  idStr_creator
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_creator  );		 
		 index  ++  ;	//  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->startTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	//  tLastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;

	 }
	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}


 int  insertImGrp_recoverImGrp_odbc(  void  *  pDbParam,  int  iDbType,  IM_GRP_INFO  *  pGrpInfo  )
{
	int		iErr	=	-1;

	void  *  pDb  =  pDbParam;
	
	 TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	 char				timeBuf[CONST_qyTimeLen  +  1];
	 char				idStr[CONST_qyMessengerIdStrLen  +  1];

	 if  (  !pGrpInfo  )  return  -1;

	 if  (  !idInfo2Str(  &pGrpInfo->idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

	 getCurTime(  timeBuf  );

	 //
	 char   idStr_creator[CONST_qyMessengerIdStrLen  +  1]  =  "";
	 if  (   pGrpInfo->idInfo_creator.ui64Id  )  {
		 idInfo2Str(  &pGrpInfo->idInfo_creator,  idStr_creator,  mycountof(  idStr_creator  )  );
	 }


	 //	
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr,name,subtype,idStr_creator,startTime,tLastModifiedTime)"  )
									_T(  "Values(%s,'%s',%s,%d,'%s','%s','%s')"  ),
									CONST_tabName_qyImGrpInfoTab,
									getDbValStr(  iDbType,  CONST_iDataType_misServName,  pGrpInfo->misServName  ),
									CString(  idStr  ),
									getDbValStr(  iDbType,  CONST_iDataType_desc,  pGrpInfo->name  ),
									(  int  )pGrpInfo->usSubtype,
									CString(  idStr_creator  ),  
									CString(  timeBuf  ),
									CString(  timeBuf  )  );	 
		 
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  traceLogA(  "err"  );
	
	 iErr  =  0;
errLabel:

	 return  iErr;

  }

  int  updateImGrp_recoverImGrp_odbc(  void  *  pDbParam,  int  iDbType,  IM_GRP_INFO  *  pGrpInfo,  int  iRcdId  )
  {

	int		iErr	=	-1;

	void  *  pDb  =  pDbParam;
			 
	 TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	 char				timeBuf[CONST_qyTimeLen  +  1];
	 char				idStr[CONST_qyMessengerIdStrLen  +  1];

	 if  (  !pGrpInfo  )  return  -1;

	 if  (  !idInfo2Str(  &pGrpInfo->idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

	 //
	 char				idStr_creator[CONST_qyMessengerIdStrLen  +  1]  =  "";
	 if  (  pGrpInfo->idInfo_creator.ui64Id  )  {
		 idInfo2Str(  &pGrpInfo->idInfo_creator,  idStr_creator,  mycountof(  idStr_creator  )  );
	 }

	 //
	 getCurTime(  timeBuf  );
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set name=%s,subtype=%d,idStr_creator='%s',tLastModifiedTime='%s' where id=%d"  ),  
		 CONST_tabName_qyImGrpInfoTab,  
		 getDbValStr(  iDbType,  CONST_iDataType_desc,  pGrpInfo->name  ),  pGrpInfo->usSubtype,  CString(  idStr_creator  ),  CString(  timeBuf  ),  
		 iRcdId  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  traceLogA(  "err"  );
	 
	 iErr  =  0;
errLabel:
	
	 return  iErr;

  }

   //  2013/02/01
 BOOL  bGetImGrpMemBySth_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo_grp,  QY_MESSENGER_ID  *  pIdInfo_mem,  int  iRcdId,  IM_GRP_MEM  *  pRcd  )
{
 	 BOOL			bRet									=		FALSE;
	 CString		sqlStr;
	 CString		whereStr;
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index									=		0;
	 char			ip12Buf[128]							=		"";
	 char			idStr_grp[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 char			idStr_mem[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 TCHAR			tBuf[256  +  1];
	 char			buf[256  +  1]							=		"";

				//				   0		   1	2		   3			 4			     5			
	 sqlStr  =  CString(  "select id,misServName,idStr_grp,idStr_mem,iRole,startTime,tLastModifiedTime,iStatus"  )
					+  _T(  " from "  )  +  CONST_tabName_qyImGrpMemTab;
	 whereStr  =  CONST_tmpStr;
	 if  (  misServName  &&  pIdInfo_grp  &&  pIdInfo_mem  )  {
		 idInfo2Str(  pIdInfo_grp,  idStr_grp,  mycountof(  idStr_grp  )  );
		 idInfo2Str(  pIdInfo_mem,  idStr_mem,  mycountof(  idStr_mem  )  );
		 whereStr  =  whereStr  +  _T(  " and misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  + _T(  " and idStr_grp='"  )  +  CString(  idStr_grp  )  +  _T(  "' and idStr_mem='"  )  +  CString(  idStr_mem  )  +  _T(  "'"  );
		}
	 else  whereStr  =  whereStr  +  _T(  " and id="  )  +  CString(  ltoa(  iRcdId,  buf,  10  )  );
	 if  (  whereStr  ==  CONST_tmpStr  )  {
		 traceLogA(  "条件应该设置"  );  goto  errLabel;
	 }
	 sqlStr  =  sqlStr  +  _T(  " where "  )  +  whereStr;
	 traceLogA(  "sql is [%S]",  sqlStr.GetBuffer(  0  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr,  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;

	 if  (  pRcd  )  {

		 memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

         index  =  0;	 //  id
		 MACRO_sqlLong(  varVals[index],  pRcd->id  );
         index  ++  ;	 //  misServName
		 MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );  
         index  ++  ;	 //  idStr_grp
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_grp  );
		 index  ++  ;	 //  idStr_mem
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_mem  );
		 index  ++  ;	//  iRole
		 MACRO_sqlLong(  varVals[index],  pRcd->iRole  );
		 index  ++  ;	//  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->startTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	//  tLastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	//  iStatus
		 MACRO_sqlLong(  varVals[index],  pRcd->iStatus  );
		 index  ++  ;

	 }
	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}



  //  int  insertImGrpMem_recoverImGrpMem_odbc(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem  )
  int  insertImGrpMem_recoverImGrpMem_odbc(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime  )
{
	int					iErr	=	-1;

	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	time_t						t;
	char						startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	char						tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";
	//  char				timeBuf[CONST_qyTimeLen  +  1];

	 if  (  !pGrpMem  )  return  -1;
	 
	//  getCurTime(  timeBuf  );

 		 char				idStr_grp[CONST_qyMessengerIdStrLen  +  1]	=	"";
		 char				idStr_mem[CONST_qyMessengerIdStrLen  +  1]	=	"";

		 idInfo2Str(  &pGrpMem->idInfo_grp,  idStr_grp,  mycountof(  idStr_grp  )  );
		 idInfo2Str(  &pGrpMem->idInfo_mem,  idStr_mem,  mycountof(  idStr_mem  )  );

	 if  (  !tLastModifiedTime  )  time(  &t  );
	 else  t  =  tLastModifiedTime;
	 getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	 getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr_grp,idStr_mem,iRole,startTime,tLastModifiedTime,iStatus)"  )
									_T(  "Values(%s,'%s','%s',%d,'%s','%s',%d)"  ),
									CONST_tabName_qyImGrpMemTab,
									getDbValStr(  iDbType,  CONST_iDataType_misServName,  pGrpMem->misServName  ),
									CString(  idStr_grp  ),
									CString(  idStr_mem  ),
									pGrpMem->iRole,
									CString(  startTimeBuf  ),					//  2013/06/19,  CString(  timeBuf  ),
									CString(  tLastModifiedTimeBuf  ),			//  2013/06/19,  CString(  timeBuf  ),
									pGrpMem->iStatus  );		 
		 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

		 iErr  =  0;
errLabel:
		 return  iErr;
 }

 int  updateImGrpMem_recoverImGrpMem_odbc(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime,  int  iRcdId  )
 {
	 int				iErr										=  -1;
	 TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	 //  char				timeBuf[CONST_qyTimeLen  +  1];

	 if  (  !pGrpMem  )  return  -1;
	 
	 //  getCurTime(  timeBuf  );
	time_t						t;
	char						startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	char						tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";

	if  (  !tLastModifiedTime  )  time(  &t  );
	else  t  =  tLastModifiedTime;
	getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );

 	
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set iRole=%d,iStatus=%d,tLastModifiedTime='%s' where id=%d"  ),
									CONST_tabName_qyImGrpMemTab,
									pGrpMem->iRole,
									pGrpMem->iStatus,
									CQyString(  tLastModifiedTimeBuf  ),			//  2013/06/19,	CString(  timeBuf  ),
									iRcdId  );
			   if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
			   iErr  =  0;
errLabel:
			   return  iErr;
 }

 int  updateImGrpMem_recoverImGrpMem2_odbc(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime,  int  iRcdId  )
{
	int					iErr													=  -1;
	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]						=	_T(  ""  );

	if  (  !pGrpMem  )  return  -1;
	 
	time_t						t;
	char						startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	char						tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";

	if  (  !tLastModifiedTime  )  time(  &t  );
	else  t  =  tLastModifiedTime;
	getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );
 	
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set tLastModifiedTime='%s' where id=%d"  ),
									CONST_tabName_qyImGrpMemTab,
									CQyString(  tLastModifiedTimeBuf  ),
									iRcdId  );

	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
	iErr  =  0;

errLabel:

	return  iErr;
}

 /////////////////////////////



 int  tmpHandler_bGetZcrs(void* p0, void* p1, void* p2)
 {
	 int							iErr = -1;
	 //
	 CONF_hg_info* pReq = (CONF_hg_info*)p1;
	 //
	 CDBVariant* varVals = (CDBVariant*)p2;
	 //

	 TCHAR					tBuf[256] = _T("");
	 char					idStr[CONST_qyMessengerIdStrLen + 1];
	 char					buf[256] = "";
	 IM_GRP_MEM		rcd;
	 IM_GRP_MEM* pRcd = &rcd;
	 int						index;

	 memset(&rcd, 0, sizeof(rcd));

	 memset(pRcd, 0, sizeof(pRcd[0]));

	 index = 0;	 //  id
	 MACRO_sqlLong(varVals[index], pRcd->id);
	 index++;	 //  misServName
	 MACRO_sqlStr(varVals[index], pRcd->misServName, mycountof(pRcd->misServName));
	 index++;	 //  idStr_grp
	 MACRO_sqlStr(varVals[index], tBuf, mycountof(tBuf));  myTChar2Str(tBuf, buf, mycountof(buf));  idStr2Info(buf, &pRcd->idInfo_grp);
	 index++;	 //  idStr_mem
	 MACRO_sqlStr(varVals[index], tBuf, mycountof(tBuf));  myTChar2Str(tBuf, buf, mycountof(buf));  idStr2Info(buf, &pRcd->idInfo_mem);
	 index++;	//  iRole
	 MACRO_sqlLong(varVals[index], pRcd->iRole);
	 index++;	//  startTime
	 MACRO_sqlStr(varVals[index], tBuf, mycountof(tBuf));  myTChar2Str(tBuf, buf, mycountof(buf));  pRcd->startTime = gettTimeByBuf(buf);
	 index++;	//  tLastModifiedTime
	 MACRO_sqlStr(varVals[index], tBuf, mycountof(tBuf));  myTChar2Str(tBuf, buf, mycountof(buf));  pRcd->tLastModifiedTime = gettTimeByBuf(buf);
	 index++;	//  iStatus
	 MACRO_sqlLong(varVals[index], pRcd->iStatus);
	 index++;

	 //
	 pReq->zcrs.mems[pReq->tmpInternal.cnt_zcrs].idInfo.ui64Id = rcd.idInfo_mem.ui64Id;


	 pReq->tmpInternal.cnt_zcrs++;
	 if (pReq->tmpInternal.cnt_zcrs >= mycountof(pReq->zcrs.mems)
		 )
	 {
		 iErr = 1;
		 goto  errLabel;
	 }

	 iErr = 0;
 errLabel:

	 return  iErr;
 }

#include	"qyDefs_open.h"
 //  
 BOOL  bGetZcrs(void* pDbParam, int  iDbType, LPCTSTR  misServName, QY_MESSENGER_ID* pIdInfo_grp, CONF_hg_info  *  pReq)
 {
	 BOOL				bRet = FALSE;
	 CString			sqlStr;
	 char				idStr[CONST_qyMessengerIdStrLen + 1] = "";
	 char				idStr_related[CONST_qyMessengerIdStrLen + 1] = "";
	 int					tmpiRet = -1;
	 CDBVariant			varVals[15];
	 CString			whereStr;
	 char				idStr_grp[CONST_qyMessengerIdStrLen + 1] = "";
	 TCHAR				tBuf[128];

	 //
	 if (!pReq)  return  FALSE;
	 if (!pIdInfo_grp)  return  false;
	 if (!pIdInfo_grp->ui64Id)  return  false;

	 //
	 memset(pReq, 0, sizeof(pReq[0]));

	 //
	 sqlStr = CString("select id,misServName,idStr_grp,idStr_mem,iRole,startTime,tLastModifiedTime,iStatus")
		 + _T(" from ") + CONST_tabName_qyImGrpMemTab;
	 whereStr = CONST_tmpStr;
	 if (misServName && pIdInfo_grp ) {
		 idInfo2Str(pIdInfo_grp, idStr_grp, mycountof(idStr_grp));
		 whereStr = whereStr + _T(" and misServName=") + getDbValStr(iDbType, CONST_iDataType_misServName, misServName) + _T(" and idStr_grp='") + CString(idStr_grp) + _T("'");
	 }
	 //
	 whereStr += CString( _T(" and iRole=")) + _ltot(CONST_imGrpMemRole_mgr, tBuf, 10);
	 //
	 if (whereStr == CONST_tmpStr) {
		 traceLogA("条件应该设置");  goto  errLabel;
	 }
	 sqlStr = sqlStr + _T(" where ") + whereStr;
	 traceLogA("sql is [%S]", sqlStr.GetBuffer(0));

	 sqlStr = sqlStr + CQyString(" order by idStr_mem");

	 OutputDebugString(sqlStr + CQyString("\n"));

	 tmpiRet = enumSqlQuery(pDbParam, sqlStr, tmpHandler_bGetZcrs, 0, pReq, varVals, mycountof(varVals), NULL);
	 if (tmpiRet < 0)  goto  errLabel;

	 bRet = TRUE;

 errLabel:
	 return  bRet;
 }






 /////////////////////////////////////////
 //
 int  updateImObj_me_odbc(  void  *  pDb,  int  iDbType,  QY_MESSENGER_INFO  *  pObj_me  ) 	 
 {
		 int	iErr			=	-1;
		 TCHAR	sqlBuf[1024]	=	_T(  "test"  );;
		 char						idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";

		 if  (  !idInfo2Str(  &pObj_me->idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

		 if  (  pObj_me->uiType  !=  CONST_objType_me  )  {
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyImObjTab set uiType=%d where misServName=%s and idStr='%s'"  ),  CONST_objType_me,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pObj_me->misServName  ),  CString(  idStr  )  );
			 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
		 }
		 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyImObjTab set uiType=%d where misServName=%s and uiType=%d and idStr<>'%s'"  ),  CONST_objType_messenger,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pObj_me->misServName  ),  CONST_objType_me,  CString(  idStr  )  );
		 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

		 iErr  =  0;
errLabel:
		 return  iErr;
	 
 }

 ///////////////////////
 int  insertImObjRule_recoverImObjRules_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime  )
{
	int  iErr  =  -1;
	 char						idStr[CONST_qyMessengerIdStrLen  +  1]			=	"";
	 char						idStr_related[CONST_qyMessengerIdStrLen  +  1]	=	"";
	 TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1];
	 time_t						t;
	 char						startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	 char						tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";

	 if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

	 if  (  !tLastModifiedTime  )  time(  &t  );
	 else  t  =  tLastModifiedTime;
	 getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	 getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );

	 idInfo2Str(  &pReqMem->idInfo_related,  idStr_related,  mycountof(  idStr_related  )  );

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr,uiRuleType,usIndex,idStr_related,uiCmd,startTime,tLastModifiedTime,iStatus,col0)"  )
		         _T(  "Values(%s,        '%s',   %d,  %d,'%s', %d,     '%s',       '%s',           %d,                          %s)"  ),
				 CONST_tabName_qyImObjRuleTab,
				 getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),
				 CString(  idStr  ),
				 pReqMem->uiRuleType,
				 pReqMem->usIndex,
				 CQyString(  idStr_related  ),
				 pReqMem->uiCmd,
				 CString(  startTimeBuf  ),
				 CString(  tLastModifiedTimeBuf  ),
				 0,
				 getDbValStr(  iDbType,  CONST_iDataType_desc,  pReqMem->wDesc  )  );
	#ifdef  __DEBUG__
		    OutputDebugString(  sqlBuf  );  OutputDebugString(  _T(  "\n"  )  );
	#endif
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	iErr =  0;
errLabel:

	return  iErr;

}

 int  deleteImObjRule_recoverImObjRules_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  int  rcdId  )
{
	 int  iErr  =  -1;
	 TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1];

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id =%d"  ),  CONST_tabName_qyImObjRuleTab,  rcdId  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;	

	 iErr =  0;
errLabel:

	return  iErr;

}


int  updateImObjRule_recoverImObjRules_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime,  int  rcdId  )
{
	int  iErr  =  -1;
	TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1];
	time_t						t;
	char						startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	char						tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";

	if  (  !tLastModifiedTime  )  time(  &t  );
	else  t  =  tLastModifiedTime;
	getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set uiCmd=%d,tLastModifiedTime='%s' where id=%d"  ),
			CONST_tabName_qyImObjRuleTab,
			pReqMem->uiCmd,
			CQyString(  tLastModifiedTimeBuf  ),
			rcdId  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	iErr =  0;
errLabel:

	return  iErr;

}

int  updateImObjRule_recoverImObjRules2_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime,  int  rcdId  )
{
	int  iErr  =  -1;
	TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1];
	time_t						t;
	char						startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	char						tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";

	if  (  !tLastModifiedTime  )  time(  &t  );
	else  t  =  tLastModifiedTime;
	getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set tLastModifiedTime='%s' where id=%d"  ),
			CONST_tabName_qyImObjRuleTab,
			CQyString(  tLastModifiedTimeBuf  ),
			rcdId  );

	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	iErr =  0;
errLabel:

	return  iErr;

}

 //  2013/01/02//////
 BOOL  bGetImObjRuleRcdBySth_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem  *  pMem,  int  iRcdId,  QY_imObjRule_rcd  *  pRcd  )
{
	 BOOL			bRet									=		FALSE;
	 CQyString		sqlStr;
	 TCHAR			whereBuf[CONST_maxSqlBufLen  +  1]		=		_T(  ""  );
	 CDBVariant		varVals[15];
	 int			index									=		0;
	 int			i;
	 char			ip12Buf[128]							=		"";
	 char			idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 char			idStr_related[CONST_qyMessengerIdStrLen  +  1]	=	"";
	 TCHAR			tBuf[256  +  1];
	 char			buf[256  +  1]							=		"";
	 long			lVal									=		0;
	 TCHAR		*	pTabName								=		CONST_tabName_qyImObjRuleTab;
	 	 
	 if  (  !pTabName  )  return  FALSE;

	 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s"  ),  CONST_tmpStr.GetBuffer(  0  )  );
	 if  (  misServName  &&  pIdInfo  &&  pMem  )  {
		 idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  );
		 idInfo2Str(  &pMem->idInfo_related,  idStr_related,  mycountof(  idStr_related  )  );
		 //
		 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and misServName=%s and idStr='%s' and idStr_related='%s' and uiRuleType=%d and usIndex=%d"  ),  
			 whereBuf,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CQyString(  idStr  ),
			 CQyString(  idStr_related  ),  pMem->uiRuleType,  pMem->usIndex  );
		}
	 else  {
		   _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and id=%d"  ),  whereBuf,  iRcdId  );
	 }
	 

	 //
	 sqlStr  =  CQyString(  "select"  )  		 
				+	CQyString(  " id,misServName,idStr,uiRuleType,usIndex,idStr_related,uiCmd,startTime,tLastModifiedTime,iStatus,col0"  )
				+  CQyString(  " from "  )  +  CQyString(  pTabName  )
				+  CQyString(  " where "  )  +  CQyString(  whereBuf  );
	 OutputDebugString(  sqlStr  +  "\n"  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;
	
	 if  (  pRcd  )  {
		 memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );
		 //
		 index  =  0;	//  id
		 MACRO_sqlLong(  varVals[index],  pRcd->id  );
		 index  ++  ;	//  misServName
		 MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );
		 index  ++  ;	//  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Utf8(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &pRcd->idInfo  );
		 index  ++  ;	//  uiRuleType
		 MACRO_sqlLong(  varVals[index],  pRcd->uiRuleType  );
		 index  ++  ;	//  usIndex
		 MACRO_sqlLong(  varVals[index],  pRcd->usIndex  );
		 index  ++  ;	//  idStr_related
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &pRcd->idInfo_related  );
		 index  ++  ;	//  uiCmd
		 MACRO_sqlLong(  varVals[index],  pRcd->uiCmd  );
		 index  ++  ;	//  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->startTime  =  gettTimeBylStr(  buf  );
		 index  ++  ;	//  lastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeBylStr(  buf  );
		 index  ++  ;	//  iStatus
		 MACRO_sqlLong(  varVals[index],  pRcd->iStatus  );
		 index  ++  ;	//  col0
		 MACRO_sqlStr(  varVals[index],  pRcd->col0,  mycountof(  pRcd->col0  )  );
		 index  ++  ;
	 
	 }
 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}


 int  tmpHandler_bGetImObjRules(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int							iErr		=	-1;
	REFRESH_imObjRules_req	*	pReq		=	(  REFRESH_imObjRules_req  *  )p1;
	CDBVariant				*	varVals		=	(  CDBVariant  *  )p2;
	//

	TCHAR					tBuf[256]	=	_T(  ""  );
	char					idStr[CONST_qyMessengerIdStrLen  +  1];
	char					buf[256]	=	"";
	QY_imObjRule_rcd		rcd;
	QY_imObjRule_rcd	*	pRcd		=	&rcd;
	int						index;

	memset(  &rcd,  0,  sizeof(  rcd  )  );

	index  =  0;	//  id
	MACRO_sqlLong(  varVals[index],  pRcd->id  );
	index  ++  ;	//  misServName
	MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );
	index  ++  ;	//  idStr
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Utf8(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &pRcd->idInfo  );
	index  ++  ;	//  idStr_related
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &pRcd->idInfo_related  );
	index  ++  ;	//  uiRuleType
	MACRO_sqlLong(  varVals[index],  pRcd->uiRuleType  );
	index  ++  ;	//  usIndex
	MACRO_sqlLong(  varVals[index],  pRcd->usIndex  );
	index  ++  ;	//  uiCmd
	MACRO_sqlLong(  varVals[index],  pRcd->uiCmd  );
	index  ++  ;	//  startTime
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->startTime  =  gettTimeBylStr(  buf  );
	index  ++  ;	//  lastModifiedTime
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeBylStr(  buf  );
	index  ++  ;	//  iStatus
	MACRO_sqlLong(  varVals[index],  pRcd->iStatus  );
	index  ++  ;	//  col0, 2011/11/14
	MACRO_sqlStr(  varVals[index],  pRcd->col0,  mycountof(  pRcd->col0  )  );
	index  ++  ;


	pReq->mems[pReq->usCnt].idInfo_related.ui64Id  =  rcd.idInfo_related.ui64Id;
	pReq->mems[pReq->usCnt].uiRuleType  =  rcd.uiRuleType;
	pReq->mems[pReq->usCnt].uiCmd  =  rcd.uiCmd;
	safeTcsnCpy(  rcd.col0,  pReq->mems[pReq->usCnt].wDesc,  mycountof(  pReq->mems[pReq->usCnt].wDesc  )  );		//  2011/11/14

	pReq->usCnt  ++  ;
	if  (  pReq->usCnt  >=  mycountof(  pReq->mems  )  
		||  (  pReq->usMaxMemsPerSnd  &&  pReq->usCnt  >=  pReq->usMaxMemsPerSnd  )  )  
	{
		iErr  =  1;
		goto  errLabel;
	}

	iErr  =  0;
errLabel:

	return  iErr;
}


 //  BOOL  bGetImObjRulesReq(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  QY_MESSENGER_ID	*	pIdInfo_related,  REFRESH_imObjRules_req  *  pReq  )
 BOOL  bGetImObjRulesReq_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  QY_MESSENGER_ID	*	pIdInfo_related,  LPCTSTR  condPart,  unsigned  short  usMaxMemsPerSnd,  REFRESH_imObjRules_req  *  pReq  )
{
	BOOL				bRet										=	FALSE;
	CQyString			sqlStr;
	char				idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char				idStr_related[CONST_qyMessengerIdStrLen  +  1]	=	"";
	int					tmpiRet										=	-1;
	CDBVariant			varVals[15];

	if  (  !pReq  )  return  FALSE;

	memset(  pReq,  0,  sizeof(  pReq[0]  )  );

	sqlStr  =  CQyString(  "select"  )  		 
				+	CQyString(  " id,misServName,idStr,idStr_related,uiRuleType,usIndex,uiCmd,startTime,tLastModifiedTime,iStatus,col0"  )
				+  CQyString(  " from "  )  +  CQyString(  CONST_tabName_qyImObjRuleTab  )
				+  CQyString(  " where 1=1"  );
	if  (  pIdInfo  &&  pIdInfo->ui64Id  )  {
		idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  );
		sqlStr  =  sqlStr  +  CQyString(  " and idStr='"  )  +  CQyString(  idStr  )  +  CQyString(  "'"  );
	}
	if  (  pIdInfo_related  &&  pIdInfo_related->ui64Id  )  {
		idInfo2Str(  pIdInfo_related,  idStr_related,  mycountof(  idStr_related  )  );	//  2009/09/08
		sqlStr  =  sqlStr  +  CQyString(  " and idStr_related='"  )  +  CQyString(  idStr_related  )  +  CQyString(  "'"  );
	}
	if  (  condPart  &&  condPart[0]  )  {	//  2011/11/12
		sqlStr  =  sqlStr  +  CQyString(  " and ("  )  +  CQyString(  condPart  )  +  CQyString(  ")"  );
	}
	sqlStr  =  sqlStr  +  CQyString(  " order by idStr,idStr_related,uiRuleType,usIndex"  );

	OutputDebugString(  sqlStr  +  CQyString(  "\n"  )  );
	 
	pReq->usMaxMemsPerSnd  =  usMaxMemsPerSnd;
	tmpiRet  =  enumSqlQuery(  pDbParam,  sqlStr,  tmpHandler_bGetImObjRules,  0,  pReq,  varVals,  mycountof(  varVals  ),  NULL  );
	if  (  tmpiRet  <  0  )  goto  errLabel;

	bRet  =  TRUE;

errLabel:
	return  bRet;
}

BOOL  bIdInfoExistedInImObjRegInfoTab_odbc(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_ID  *  pIdInfo,  LPCTSTR  tabName  )
{
	 int						bRet										=	FALSE;
	 CString					sqlStr;
	 CDBVariant					varVals[5];
	 char						idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";

	 void					*	pDb											=   pDbParam;

 	 if  (  !pIdInfo  )  return  FALSE;

	 if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

	 sqlStr  =  CString(  ""  )  +  _T(  "select idStr from "  ) +  tabName  +  _T(  " where idStr='"  )  +  CString(  idStr  )  +  _T(  "'"  );
	 if  (  !bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  
	 {	
		 goto  errLabel;	
	 }

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}

int  insertImObjRegInfo_qisRegUsrInfoInTab_odbc(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  )
{
	 int						iErr										=	-1;
	 CString					sqlStr;
	 int						i;
	 CDBVariant					varVals[5];
	 char						idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";

	 void					*	pDb											=   pDbParam;

	 if  (  !pRegInfo  )  return  -1;

	 if  (  !idInfo2Str(  &pRegInfo->addr.idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

	 getCurTime(  pRegInfo->regTime  );
	 sqlStr  =  CString(  "insert into "  )  +  tabName  +  _T(  "(misServName,idStr,regTime,auditTime,tLastModifiedTime,tCommitTime,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,comment0)"  )  +
						  _T(  "values("  )  +  
						  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pRegInfo->addr.misServName  )  +  _T(  ","  ) +
						  _T(  "'"  )  +  CString(  idStr  )  +  _T(  "',"  )  +
						  _T(  "'"  )  +  CString(  pRegInfo->regTime  )  +  _T(  "',"  )  +
						  _T(  "'"  )  +  CString(  pRegInfo->auditTime  )  +  _T(  "',"  )  +
						  _T(  "'"  )  +  CString(  pRegInfo->tLastModifiedTime  )  +  _T(  "',"  )  +
						  _T(  "'',"  );
	 for  (  i  =  0;  i  <  20;  i  ++   )  {
		  sqlStr  =  sqlStr  +  getDbValStr(  iDbType,  pRegInfo->fields[i].iDataType,  pRegInfo->fields[i].ptr  )  +  _T(  ","  );
	 }
	 sqlStr  =  sqlStr  +  _T(  "''"  )  +  _T(  ")"  );
	 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
		 traceLogA(  "qnmRegUsrInfo: insert into qyPcRegInfoTab1 failed"  );
		 goto  errLabel;
	 }
		 
	 iErr  =  0;
errLabel:
	 return  iErr;
}

int  updateImObjRegInfo_qisRegUsrInfoInTab_odbc(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  )
{
	 int						iErr										=	-1;
	 CString					sqlStr;
	 int						i;
	 CDBVariant					varVals[5];
	 TCHAR						tBuf[1024];
	 char						idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";

	 void					*	pDb											=   pDbParam;

	 if  (  !pRegInfo  )  return  -1;
	 if  (  !idInfo2Str(  &pRegInfo->addr.idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
	 //  Tab
	 {
		
		 sqlStr  =  CString(  "update "  )  +  tabName  +  _T(  " set "  );
		 if  (  pRegInfo->auditTime[0]  )  sqlStr  +=  CString(  "auditTime='"  )  +  CString(  pRegInfo->auditTime  )  +  _T(  "',"  );
		 if  (  pRegInfo->regTime[0]  )  sqlStr  +=  CString(  "regTime='"  )  +  CString(  pRegInfo->regTime  )  +  _T(  "',"  );
		 sqlStr  +=  CString(  "tLastModifiedTime='"  )  +  CString(  pRegInfo->tLastModifiedTime  )  +  _T(  "',"  );
		 sqlStr  +=  CString(  "tCommitTime='',"  );
		 for  (  i  =  0;  i  <  20;  i  ++  )  {
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "col%d"  ),  i  );
			  sqlStr  =  sqlStr  +  tBuf  +  _T(  "="  )  +  getDbValStr(  iDbType,  pRegInfo->fields[i].iDataType,  pRegInfo->fields[i].ptr  )  +  _T(  ","  );
		 }
		 sqlStr  =  sqlStr  +  _T(  "comment0='' where idStr='"  )  +  CString(  idStr  )  +  _T(  "'"  );
	 	 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			 traceLogA(  "qnmRegUsrInfo: update qyPcRegInfoTab failed"  );
			 goto  errLabel;
		 }
				 
		 iErr  =  0;  goto  errLabel;

	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}

  //  2013/02/02
 BOOL  bGetMessengerPhoneInfoBySth_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiDevType,  LPCTSTR  wDevIdStr,  QY_MESSENGER_ID  *  pIdInfo,  int  id,  QY_MESSENGER_phoneInfo  *  pRcd  )
{
	 BOOL			bRet									=		FALSE;
	 TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1]		=		_T(  ""  );
	 CDBVariant		varVals[30];
	 int			index;
	 TCHAR			tBuf[256];
	 TCHAR			wherePart[CONST_maxSqlClauseLen  +  1]	=		_T(  ""  );
	 char			buf[255  +  1];

	 if  (  !pDbParam  )  return  FALSE;
		
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,misServName,uiDevType,wDevIdStr,messengerPasswd,idStr,iStatus,startTime,tLastModifiedTime from %s"  ),  CONST_tabName_qyMessengerPhoneInfoTab  );
     
	 if  (  misServName  &&  wDevIdStr  &&  wDevIdStr[0]  )  {
		 _sntprintf(  wherePart,  mycountof(  wherePart  ),  _T(  "misServName=%s and uiDevType=%d and wDevIdStr=%s"  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  uiDevType,  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  wDevIdStr  )  );
		 }
	 else  if  (  misServName  &&  pIdInfo  )  {
		       idInfo2Str(  pIdInfo,  buf,  mycountof(  buf  )  );
			   _sntprintf(  wherePart,  mycountof(  wherePart  ),  _T(  "misServName=%s and idStr='%s'"  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  buf  ).GetBuffer(  0  )  );
			   }
	 else  
		 _sntprintf(  wherePart,  mycountof(  wherePart  ),  _T(  "id=%d"  ),  id  ); 
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where %s"  ),  sqlBuf,  wherePart  );

	 traceLogA(  "sql is %S",  sqlBuf  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;

	 if  (  pRcd  )  {
	 	 memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

		 index  =  0;		MACRO_sqlLong(  varVals[index],  pRcd->id  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );
		 index  ++  ;		MACRO_sqlLong(  varVals[index],  pRcd->uiDevType  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  pRcd->wDevIdStr,  mycountof(  pRcd->wDevIdStr  )  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  pRcd->messengerPasswd,  mycountof(  pRcd->messengerPasswd  )  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo  );
		 index  ++  ;		MACRO_sqlLong(  varVals[index],  pRcd->iStatus  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->startTime  =  gettTimeByStr(  buf  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeByStr(  buf  );
		 index  ++  ;

	 }

	 bRet  =  TRUE;
errLabel:
	 return  bRet;

}


// int  recoverMessengerPhoneInfo_odbc(  void  *  pDb,  int  iDbType,  MSGR_ADDR  *  pAddr,  void  *  p1  )
 int  recoverMessengerPhoneInfo_odbc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  MSGR_ADDR  *  pAddr,  void  *  p1  )
{
	//
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &g_dbFuncs  =  *pDbFuncs;

	int							iErr									=		-1;
	QY_MESSENGER_phoneInfo		rcd;
	TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1]		=		_T(  ""  );
	char						timeBuf[CONST_qyTimeLen  +  1]			=		"";
	char						idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";

    
	if  (  !pAddr  )  return  -1;

	if  (  !g_dbFuncs.pf_bGetMessengerPhoneInfoBySth(  pDb,  iDbType,  pAddr->misServName,  0,  0,  &pAddr->idInfo,  0,  &rcd  )  )  memset(  &rcd,  0,  sizeof(  rcd  )  );

	getCurTime(  timeBuf  );
	idInfo2Str(  &pAddr->idInfo,  idStr,  mycountof(  idStr  )  );

	if  (  !pAddr->uiDevType  )  {
		if  (  rcd.id  )  {
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyMessengerPhoneInfoTab,  rcd.id  );
			if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
		}
		}
	else  {
		  if  (  pAddr->uiDevType  !=  rcd.uiDevType  ||  lstrcmpi(  pAddr->wDevIdStr,  rcd.wDevIdStr  )  )  {
	  		  if  (  !rcd.id  )  {
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,uiDevType,wDevIdStr,idStr,iStatus,startTime,tLastModifiedTime) values(%s,%d,%s,'%s',%d,'%s','%s')"  ),  
					  CONST_tabName_qyMessengerPhoneInfoTab,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pAddr->misServName  ),  pAddr->uiDevType,  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  pAddr->wDevIdStr  ),  CString(  idStr  ),  0,  CString(  timeBuf  ),  CString(  timeBuf  )  );
				  if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
				  }
			  else  {
				    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set uiDevType=%d,wDevIdStr=%s,tLastModifiedTime='%s' where id=%d"  ), 
							 CONST_tabName_qyMessengerPhoneInfoTab, pAddr->uiDevType,  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  pAddr->wDevIdStr  ),  CString(  timeBuf  ),  rcd.id  );
					if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
			  }

		  }
	}


	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		traceLogA(  "recoverMessengerPhoneInfo failed"  );
	}
	return  iErr;

}

 //  2013/02/02
 //  pRegInfo->auditTime,qyPcRegInfoTab
 int  qisRegUsrInfo_odbc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pMessengerInfo,  QY_MESSENGER_REGINFO  *  pRegInfo,  BOOL  bLogReRegEvent  )
{
	 int						iErr										=	-1;
	 CString					sqlStr;
	 int						i;
	 int						iQwmVer										=	0;
	 CDBVariant					varVals[5];
	 unsigned  char				ucbAudited									=	FALSE;
	 unsigned  char				ucbReged									=	FALSE;
	 QIS_EVENT					tmpEvent;
	 int						index;
	 TCHAR						tBuf[1024];
	 char						idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";

	 traceLogA(  "qisRegUsrInfo enters"  );

	 if  (  !pRegInfo  )  goto  errLabel;
	 if  (  !pMessengerInfo  )  {
		 if  (  !bMessengerIdValid(  &pRegInfo->addr.idInfo  )  )  goto  errLabel;
		}
	 else  {
		   if  (  !bMessengerIdValid(  &pMessengerInfo->idInfo  )  )  goto errLabel;
		   pRegInfo->addr.idInfo.ui64Id  =  pMessengerInfo->idInfo.ui64Id;
	 }
	 if  (  !idInfo2Str(  &pRegInfo->addr.idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
	 
	 getCurTime(  pRegInfo->tLastModifiedTime  );


	 MACRO_setPtrs(  pFieldIdTable,  pRegInfo[0],  pRegInfo->fields  );
	 for  (  i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
		  if  (  pRegInfo->fields[i].bufSize  )  pRegInfo->fields[i].ptr[pRegInfo->fields[i].bufSize  -  1]  =  0;
	 }

	 sqlStr  =  CString(  "select auditTime from qyImObjRegInfoTab where idStr='"  )  +  CString(  idStr  )  +  _T(  "'"  );
	 if  (  bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  {
		 ucbReged  =  TRUE;
		 index  =  0;
		 MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
		 if  (  lstrlen(  tBuf  )  ==  CONST_qyTimeLen  )  ucbAudited  =  TRUE;		 
	 }

	 memset(  &tmpEvent,  0,  sizeof(  tmpEvent  )  );

	 if  (  !ucbReged  )  {						//  未注册的情况
		 getCurTime(  pRegInfo->regTime  );
		 sqlStr  =  CString(  "insert into qyImObjRegInfoTab(misServName,idStr,regTime,auditTime,tLastModifiedTime,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,comment0)"  )  +
							  _T(  "values("  )  +  
							  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pRegInfo->addr.misServName  )  +  _T(  ","  )  +
							  _T(  "'"  )  +  CString(  idStr  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pRegInfo->regTime  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pRegInfo->auditTime  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pRegInfo->tLastModifiedTime  )  +  _T(  "',"  );
		 for  (  i  =  0;  i  <  20;  i  ++  )  {
			  sqlStr  =  sqlStr  +  getDbValStr(  iDbType,  pRegInfo->fields[i].iDataType,  pRegInfo->fields[i].ptr  )  +  _T(  ","  );
		 }
		 sqlStr  =  sqlStr  +  _T(  "''"  )  +  _T(  ")"  );
		 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			 traceLogA(  "qnmRegUsrInfo: insert into qyPcRegInfoTab failed"  );
			 goto  errLabel;
		 }			 

		 if  (  pMessengerInfo  )  {

			 //  作操作日志	
			 tmpEvent.lEventType  =  CONST_qyEventType_nm_newReg;
		 	 tmpEvent.iCustomId  =  pRegInfo->iCustomId;
		 	 getCurTime(  tmpEvent.localEventTime  );
			 lstrcpyn(  tmpEvent.misServName,  pRegInfo->addr.misServName,  mycountof(  tmpEvent.misServName  )  );
			 tmpEvent.idInfo.ui64Id  =  pMessengerInfo->idInfo.ui64Id;			 
		 	 safeStrnCpy(  pMessengerInfo->ip,  tmpEvent.ip,  sizeof(  tmpEvent.ip  )  );
				
		 	 for  (  i  =  0;  gpRegEventRegColsTable[i].type  !=  -1;  i  ++  )  {
				  if  (  gpRegEventRegColsTable[i].type  ==  CONST_nullColId  )  continue;
			  	  MACRO_qyAssert(  gpRegEventRegColsTable[i].type  <  CONST_qnmMaxRegFields,  _T(  "qpRegEventRegColsTabl[n].type 太大, 不能超过 CONST_qnmMaxRegFields"  )  );
			  	  MACRO_qyAssert(  i  <  CONST_qnmMaxEventRegFields,  _T(  "gpRegEventRegColsTable项数太多，不能超过CONST_qnmMaxEventRegFields"  )  );
			  	  lstrcpyn(  tmpEvent.cols[i],  (  TCHAR  *  )pRegInfo->u.cols[gpRegEventRegColsTable[i].type],  sizeof(  tmpEvent.cols[i]  )  /  sizeof(  TCHAR  )  );
		 	 }
			
			 logEvent_is(  pDbFuncs,  pDb,  iDbType,  pMessengerInfo,  &tmpEvent  );

		 }

		 iErr  =  0;  goto  errLabel;
	
	 }

	 //  下面已注册
	 //

	 //  未审核，或pRegInfo属审核信息
	 if  (  !ucbAudited  ||  pRegInfo->auditTime[0]  )  {
		
		 sqlStr  =  CString(  "update qyImObjRegInfoTab set "  );
		 //  if  (  pRegInfo->auditTime[0]  )  sqlStr  +=  CString(  "auditTime='"  )  +  pRegInfo->auditTime  +  "',";
		 sqlStr  +=  CString(  "auditTime='"  )  +  CString(  pRegInfo->auditTime[0]  ?  pRegInfo->auditTime  :  ""  )  +  _T(  "',"  );
		 if  (  pRegInfo->regTime[0]  )  sqlStr  +=  CString(  "regTime='"  )  +  CString(  pRegInfo->regTime  )  +  _T(  "',"  );
		 sqlStr  +=  CString(  "tLastModifiedTime='"  )  +  CString(  pRegInfo->tLastModifiedTime  )  +  _T(  "',"  );
		 //		 
		 for  (  i  =  0;  i  <  20;  i  ++  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "col%d"  ),  i  );  
			 sqlStr  =  sqlStr  +  tBuf  +  _T(  "="  )  +  getDbValStr(  iDbType,  pRegInfo->fields[i].iDataType,  pRegInfo->fields[i].ptr  )  +  _T(  ","  );
		 }
		 sqlStr  =  sqlStr  +  _T(  "comment0='' where idStr='"  )  +  CString(  idStr  )  +  _T(  "'"  );
		 
	 	 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			 traceLogA(  "qnmRegUsrInfo: update qyPcRegInfoTab failed"  );
			 goto  errLabel;
		 }
		
		 sqlStr  =  CString(  ""  )  +  _T(  "delete from qyImObjRegInfoTab1 where idStr='"  )  +  CString(  idStr  )  +  _T(  "'"  );
		 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			 traceLogA(  "qnmRegUsrInfo: delete from qyPcRegInfoTab1 failed"  );
			 goto  errLabel;
		 }


		 if  (  bLogReRegEvent  )  {  //  2008/02/15
		 	 if  (  pMessengerInfo  )  {
		 
				 tmpEvent.lEventType  =  CONST_qyEventType_nm_reReg;
				 tmpEvent.iCustomId  =  pRegInfo->iCustomId;
				 getCurTime(  tmpEvent.localEventTime  );
				 lstrcpyn(   tmpEvent.misServName,  pRegInfo->addr.misServName,  mycountof(  tmpEvent.misServName  )  );
				 tmpEvent.idInfo.ui64Id  =  pMessengerInfo->idInfo.ui64Id;
				 safeStrnCpy(  pMessengerInfo->ip,  tmpEvent.ip,  sizeof(  tmpEvent.ip  )  );
					
				 for  (  i  =  0;  gpRegEventRegColsTable[i].type  !=  -1;  i  ++  )  {
					  if  (  gpRegEventRegColsTable[i].type  ==  CONST_nullColId  )  continue;
					  MACRO_qyAssert(  gpRegEventRegColsTable[i].type  <  CONST_qnmMaxRegFields,  _T(  "qpRegEventRegColsTabl[n].type 太大, 不能超过CONST_qnmMaxRegFields"  )  );
					  MACRO_qyAssert(  i  <  CONST_qnmMaxEventRegFields,  _T(  "gpRegEventRegColsTable项数太多，不能超过CONST_qnmMaxEventRegFields"  )  );
					  lstrcpyn(  tmpEvent.cols[i],  (  TCHAR  *  )pRegInfo->u.cols[gpRegEventRegColsTable[i].type],  sizeof(  tmpEvent.cols[i]  )  /  sizeof(  TCHAR  )  );
				 }

				 logEvent_is(  pDbFuncs,  pDb,  iDbType,  pMessengerInfo,  &tmpEvent  );					
			 }
		 }
		 
		 iErr  =  0;  goto  errLabel;

	 }
	 
	 //  已审核，且pRegInfo属未审核信息，pRegInfo将更新入qyPcRegInfoTab1中
	 //
	 if  (  qisRegUsrInfoInTab(  pDbFuncs,  pDb,  iDbType,  pFieldIdTable,  pMessengerInfo,  pRegInfo,  CONST_tabName_qyImObjRegInfoTab1  )  )  goto  errLabel;


	 iErr  =  0;

errLabel:

	 traceLogA(  "qisRegUsrInfo leaves"  );

	 return  iErr;

}

 //  pRegInfo->auditTime qyPcRegInfoTab
// int  qnmRegUsrInfo_odbc(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo  )
 int  qnmRegUsrInfo_odbc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo  )
{
	 int						iErr			=	-1;
	 CString					sqlStr;
	 QNM_FIELD					fields[CONST_qnmMaxRegFields];
	 int						i;
	 int						iQwmVer			=	0;
	 CDBVariant					varVals[5];
	 unsigned  char				ucbAudited		=	FALSE;
	 unsigned  char				ucbReged		=	FALSE;
	 QNM_PC_EVENT				tmpEvent;
	 int						index;
	 TCHAR						tBuf[1024];

	 traceLogA(  "qnmRegUsrInfo enters"  );

	 if  (  !pRegInfo  )  goto  errLabel;
	 if  (  !pPcInfo  )  {
		 if  (  !pRegInfo->mac0[0]  ||  strlen(  pRegInfo->mac0  )  !=  CONST_qyMacLen  )  goto  errLabel;
		}
	 else  {
		   if  (  !pPcInfo->nMacs  ||  strlen(  pPcInfo->macs[0]  )  !=  CONST_qyMacLen  )  goto errLabel;
		   safeStrnCpy(  pPcInfo->macs[0],  pRegInfo->mac0,  sizeof(  pRegInfo->mac0  )  );
	 }

	 
	 memset(  (  char  *  )fields,  0,  sizeof(  fields  )  );

	 if  (  qnmSetPtrs(  pFieldIdTable,  pRegInfo,  fields  )  )  goto  errLabel;
	 for  (  i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
		  if  (  fields[i].bufSize  )  fields[i].ptr[fields[i].bufSize  -  1]  =  0;
	 }

	 sqlStr  =  CString(  "select auditTime from qyPcRegInfoTab where mac0='"  )  +  CString(  pRegInfo->mac0  )  +  _T(  "'"  );
	 if  (  bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  {
		 ucbReged  =  TRUE;
		 index  =  0;
		 MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
		 if  (  lstrlen(  tBuf  )  ==  CONST_qyTimeLen  )  ucbAudited  =  TRUE;		 
	 }

	 memset(  &tmpEvent,  0,  sizeof(  tmpEvent  )  );

	 if  (  !ucbReged  )  {						//  未注册的情况
		 getCurTime(  pRegInfo->regTime  );
		 sqlStr  =  CString(  "insert into qyPcRegInfoTab(mac0,regTime,auditTime,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,comment0)"  )  +
							  _T(  "values("  )  +  
							  _T(  "'"  )  +  CString(  pRegInfo->mac0  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pRegInfo->regTime  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pRegInfo->auditTime  )  +  _T(  "',"  );
		 for  (  i  =  0;  i  <  20;  i  ++  )  {
			  sqlStr  =  sqlStr  +  getDbValStr(  iDbType,  fields[i].iDataType,  fields[i].ptr  )  +  _T(  ","  );
		 }
		 sqlStr  =  sqlStr  +  _T(  "''"  )  +  _T(  ")"  );
		 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			 traceLogA(  "qnmRegUsrInfo: insert into qyPcRegInfoTab failed"  );
			 goto  errLabel;
		 }			 

		 if  (  pPcInfo  )  {

			 //  作操作日志	
			 tmpEvent.lEventType  =  CONST_qyEventType_nm_newReg;
		 	 tmpEvent.iCustomId  =  pRegInfo->iCustomId;
		 	 getCurTime(  tmpEvent.localEventTime  );
		 	 safeStrnCpy(  pRegInfo->mac0,  tmpEvent.macs[0],  sizeof(  tmpEvent.macs[0]  )  );
		 	 safeStrnCpy(  pPcInfo->ip,  tmpEvent.ip,  sizeof(  tmpEvent.ip  )  );
				
		 	 for  (  i  =  0;  gpRegEventRegColsTable[i].type  !=  -1;  i  ++  )  {
				  if  (  gpRegEventRegColsTable[i].type  ==  CONST_nullColId  )  continue;
			  	  MACRO_qyAssert(  gpRegEventRegColsTable[i].type  <  CONST_qnmMaxRegFields,  _T(  "qpRegEventRegColsTabl[n].type < CONST_qnmMaxRegFields"  )  );
			  	  MACRO_qyAssert(  i  <  CONST_qnmMaxEventRegFields,  _T(  "gpRegEventRegColsTable < CONST_qnmMaxEventRegFields"  )  );
			  	  lstrcpyn(  tmpEvent.cols[i],  (  TCHAR  *  )pRegInfo->u.cols[gpRegEventRegColsTable[i].type],  sizeof(  tmpEvent.cols[i]  )  /  sizeof(  TCHAR  )  );
		 	 }
			
			 qnmLogPcEvent(  pDbFuncs,  pDb,  iDbType,  pPcInfo,  &tmpEvent  );

		 }

		 iErr  =  0;  goto  errLabel;
	
	 }

	 //  下面已注册
	 //

	 //  未审核，或pRegInfo属审核信息
	 if  (  !ucbAudited  ||  pRegInfo->auditTime[0]  )  {
		
		 sqlStr  =  CString(  "update qyPcRegInfoTab set "  );
		 //  if  (  pRegInfo->auditTime[0]  )  sqlStr  +=  CString(  "auditTime='"  )  +  pRegInfo->auditTime  +  "',";
		 sqlStr  +=  CString(  "auditTime='"  )  +  CString(  pRegInfo->auditTime[0]  ?  pRegInfo->auditTime  :  ""  )  +  _T(  "',"  );
		 if  (  pRegInfo->regTime[0]  )  sqlStr  +=  CString(  "regTime='"  )  +  CString(  pRegInfo->regTime  )  +  _T(  "',"  );
		 /*
		 sqlStr  +=  CString(  ""  )  +		"col0='"  +  fields[0].ptr  +  "',"  +
											"col1='"  +  fields[1].ptr  +  "',"  +
											"col2='"  +  fields[2].ptr  +  "',"  +
											"col3='"  +  fields[3].ptr  +  "',"  +
											"col4='"  +  fields[4].ptr  +  "',"  +
											"col5='"  +  fields[5].ptr  +  "',"  +
											"col6='"  +  fields[6].ptr  +  "',"  +
											"col7='"  +  fields[7].ptr  +  "',"  +
											"col8='"  +  fields[8].ptr  +  "',"  +
											"col9='"  +  fields[9].ptr  +  "',"  +
											"col10='"  +  fields[10].ptr  +  "',"  +
											"col11='"  +  fields[11].ptr  +  "',"  +
											"col12='"  +  fields[12].ptr  +  "',"  +
											"col13='"  +  fields[13].ptr  +  "',"  +
											"col14='"  +  fields[14].ptr  +  "',"  +
											"col15='"  +  fields[15].ptr  +  "',"  +
											"col16='"  +  fields[16].ptr  +  "',"  +
											"col17='"  +  fields[17].ptr  +  "',"  +
											"col18='"  +  fields[18].ptr  +  "',"  +
											"col19='"  +  fields[19].ptr  +  "'"  +
										"where mac0='"  +  pRegInfo->mac0  +  "'";
										*/
		 for  (  i  =  0;  i  <  20;  i  ++  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "col%d"  ),  i  );  
			 sqlStr  =  sqlStr  +  tBuf  +  _T(  "="  )  +  getDbValStr(  iDbType,  fields[i].iDataType,  fields[i].ptr  )  +  _T(  ","  );
		 }
		 sqlStr  =  sqlStr  +  _T(  "comment0='' where mac0='"  )  +  CString(  pRegInfo->mac0  )  +  _T(  "'"  );
		 
	 	 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			 traceLogA(  "qnmRegUsrInfo: update qyPcRegInfoTab failed"  );
			 goto  errLabel;
		 }
		
		 sqlStr  =  CString(  ""  )  +  _T(  "delete from qyPcRegInfoTab1 where mac0='"  )  +  CString(  pRegInfo->mac0  )  +  CString(  "'"  );
		 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			 traceLogA(  "qnmRegUsrInfo: delete from qyPcRegInfoTab1 failed"  );
			 goto  errLabel;
		 }

		 if  (  pPcInfo  )  {

		 	 tmpEvent.lEventType  =  CONST_qyEventType_nm_reReg;
		 	 tmpEvent.iCustomId  =  pRegInfo->iCustomId;
			 getCurTime(  tmpEvent.localEventTime  );
			 safeStrnCpy(  pRegInfo->mac0,  tmpEvent.macs[0],  sizeof(  tmpEvent.macs[0]  )  );
			 safeStrnCpy(  pPcInfo->ip,  tmpEvent.ip,  sizeof(  tmpEvent.ip  )  );
					
			 for  (  i  =  0;  gpRegEventRegColsTable[i].type  !=  -1;  i  ++  )  {
				  if  (  gpRegEventRegColsTable[i].type  ==  CONST_nullColId  )  continue;
			  	  MACRO_qyAssert(  gpRegEventRegColsTable[i].type  <  CONST_qnmMaxRegFields,  _T(  "qpRegEventRegColsTabl[n].type 太大, 不能超过CONST_qnmMaxRegFields"  )  );
			  	  MACRO_qyAssert(  i  <  CONST_qnmMaxEventRegFields,  _T(  "gpRegEventRegColsTable项数太多，不能超过CONST_qnmMaxEventRegFields"  )  );
			  	  lstrcpyn(  tmpEvent.cols[i],  (  TCHAR  *  )pRegInfo->u.cols[gpRegEventRegColsTable[i].type],  sizeof(  tmpEvent.cols[i]  )  /  sizeof(  TCHAR  )  );
		 	 }
				 
			 qnmLogPcEvent(  pDbFuncs,  pDb,  iDbType,  pPcInfo,  &tmpEvent  );					
		 }

		 iErr  =  0;  goto  errLabel;

	 }
	 
	 //  已审核，且pRegInfo属未审核信息，pRegInfo将更新入qyPcRegInfoTab1中
	 //

	 //  Tab1中没有
	 sqlStr  =  CString(  ""  )  +  _T(  "select mac0 from qyPcRegInfoTab1 where mac0='"  )  +  CString(  pRegInfo->mac0  )  +  _T(  "'"  );
	 if  (  !bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  {						//  未注册的情况
		 getCurTime(  pRegInfo->regTime  );
		 sqlStr  =  CString(  "insert into qyPcRegInfoTab1(mac0,regTime,auditTime,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,comment0)"  )  +
							  _T(  "values("  )  +  
							  _T(  "'"  )  +  CString(  pRegInfo->mac0  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pRegInfo->regTime  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pRegInfo->auditTime  )  +  _T(  "',"  );
		 for  (  i  =  0;  i  <  20;  i  ++   )  {
			  sqlStr  =  sqlStr  +  getDbValStr(  iDbType,  fields[i].iDataType,  fields[i].ptr  )  +  _T(  ","  );
		 }
		 sqlStr  =  sqlStr  +  _T(  "''"  )  +  _T(  ")"  );
		 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			 traceLogA(  "qnmRegUsrInfo: insert into qyPcRegInfoTab1 failed"  );
			 goto  errLabel;
		 }			 
		 
		 iErr  =  0;  goto  errLabel;
	
	 }
	
	 //  Tab1中有
	 {
		
		 sqlStr  =  CString(  "update qyPcRegInfoTab1 set "  );
		 if  (  pRegInfo->auditTime[0]  )  sqlStr  +=  CString(  "auditTime='"  )  +  CString(  pRegInfo->auditTime  )  +  _T(  "',"  );
		 if  (  pRegInfo->regTime[0]  )  sqlStr  +=  CString(  "regTime='"  )  +  CString(  pRegInfo->regTime  )  +  _T(  "',"  );
		 for  (  i  =  0;  i  <  20;  i  ++  )  {
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "col%d"  ),  i  );
			  sqlStr  =  sqlStr  +  tBuf  +  _T(  "="  )  +  getDbValStr(  iDbType,  fields[i].iDataType,  fields[i].ptr  )  +  _T(  ","  );
		 }
		 sqlStr  =  sqlStr  +  _T(  "comment0='' where mac0='"  )  +  CString(  pRegInfo->mac0  )  +  _T(  "'"  );
	 	 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			 traceLogA(  "qnmRegUsrInfo: update qyPcRegInfoTab failed"  );
			 goto  errLabel;
		 }
				 
		 iErr  =  0;  goto  errLabel;

	 }


	 iErr  =  0;

errLabel:

	 traceLogA(  "qnmRegUsrInfo leaves"  );

	 return  iErr;

}

 BOOL  bSelectImMsg_logImMsg_odbc(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  )
{
	BOOL			bRet											=	FALSE;
	TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1]				=	_T(  ""  );
	char			idStr_send[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char			sendTime[CONST_qyTimeLen  +  1]					=	"";
	CDBVariant		varVals[2];
#if  0
	char			tStartTime_serv[CONST_qyTimeLen  +  1]			=	"";
	char			idStr_recv[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char			recvTime[CONST_qyTimeLen  +  1]					=	"";
	char			firstTime[CONST_qyTimeLen  +  1]				=	"";
	char			lastTime[CONST_qyTimeLen  +  1]					=	"";
	char			lastModifiedTime[CONST_qyTimeLen  +  1]			=	"";
	//
	TCHAR			contents[10][120  +  1];
	TCHAR			txtContents[10][120  +  1];
	int				i;
	TCHAR		*	pT;
	int				len;
	int				len1;
	unsigned  int	uiContentType;
#endif

	if  (  !idInfo2Str(  &pRcd->idInfo_send,  idStr_send,  mycountof(  idStr_send  )  )  )  goto  errLabel;
	getTimeStr(  pRcd->tSendTime,  sendTime,  mycountof(  sendTime  )  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id from %s where misServName=%s and idStr_send='%s' and tSendTime='%s' and uiTranNo=%d and uiSeqNo=%d"  ),  
		                                          CONST_tabName_qyImMsgTab,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pRcd->misServName  ),  CString(  idStr_send  ),  CString(  sendTime  ),  pRcd->uiTranNo,  pRcd->usSeqNo  );
	if  (  !bQyGetRcdBySql(  pDb,  sqlBuf,  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;
    
	bRet  =  TRUE;
errLabel:
	return  bRet;

}

 //
 int  insertImMsg_logImMsg_odbc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  )
{
	int				iErr											=	-1;
	TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1]				=	_T(  ""  );
	char			idStr_send[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char			sendTime[CONST_qyTimeLen  +  1]					=	"";
	CDBVariant		varVals[2];
	char			tStartTime_serv[CONST_qyTimeLen  +  1]			=	"";
	char			idStr_recv[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char			recvTime[CONST_qyTimeLen  +  1]					=	"";
	char			firstTime[CONST_qyTimeLen  +  1]				=	"";
	char			lastTime[CONST_qyTimeLen  +  1]					=	"";
	char			lastModifiedTime[CONST_qyTimeLen  +  1]			=	"";
	//
	TCHAR			contents[10][120  +  1];
	TCHAR			txtContents[10][120  +  1];
	int				i;
	TCHAR		*	pT;
	int				len;
	int				len1;
	unsigned  int	uiContentType;


	//
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &g_dbFuncs  =  *pDbFuncs;



	if  (  !idInfo2Str(  &pRcd->idInfo_send,  idStr_send,  mycountof(  idStr_send  )  )  )  goto  errLabel;
	getTimeStr(  pRcd->tSendTime,  sendTime,  mycountof(  sendTime  )  );

	//
	if  (  !pRcd->senderDesc[0]  &&  !pRcd->receiverDesc[0]  )  {	//  如果没有用户信息，则补充用户信息. 这是记流水帐的需要
		QY_MESSENGER_REGINFO	regInfo;
		MY_REG_DESC				desc;
		//
		if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pDb,  iDbType,  pFieldIdTable,  pRcd->misServName,  &pRcd->idInfo_send,  0,  NULL,  &regInfo,  NULL,  NULL  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		if  (  regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  )  )  goto  errLabel;
		if  (  desc.pSyr[0]  )  _sntprintf(  pRcd->senderDesc,  mycountof(  pRcd->senderDesc  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );  
		if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pDb,  iDbType,  pFieldIdTable,  pRcd->misServName,  &pRcd->idInfo_recv,  0,  NULL,  &regInfo,  NULL,  NULL  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		if  (  regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  )  )  goto  errLabel;
		if  (  desc.pSyr[0]  )  _sntprintf(  pRcd->receiverDesc,  mycountof(  pRcd->receiverDesc  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );  
	}


	//
	getTimeStr(  pRcd->tStartTime_serv,  tStartTime_serv,  mycountof(  tStartTime_serv  )  );
	if  (  !idInfo2Str(  &pRcd->idInfo_recv,  idStr_recv,  mycountof(  idStr_recv  )  )  )  goto  errLabel;
	getTimeStr(  (  time_t  )pRcd->tRecvTime,  recvTime,  mycountof(  recvTime  )  );
	getTimeStr(  pRcd->firstTime,  firstTime,  mycountof(  firstTime  )  );
	getTimeStr(  pRcd->lastTime,  lastTime,  mycountof(  lastTime  )  );
	getTimeStr(  pRcd->tLastModifiedTime,  lastModifiedTime,  mycountof(  lastModifiedTime  )  );


	//  2008/10/24, 这里要过滤下，不能让内容里有 ' 
	escapeTStr(  pRcd->content,  mycountof(  pRcd->content  )  );
	escapeTStr(  pRcd->txtContent,  mycountof(  pRcd->txtContent  )  );

	//
	uiContentType  =  pRcd->uiType;

	memset(  contents,  0,  sizeof(  contents  )  );
	if  (  pRcd->content[0]  )  {
		//
		//
		pT  =  pRcd->content;
		len  =  lstrlen(  pT  );
		traceLogA(  "mycountof(  contents  )  is %d,  mycountof(  contents[i]  ) is %d",  mycountof(  contents  ),  mycountof(  contents[0]  )  );
		for  (  i  =  0;  len  &&  i<  mycountof(  contents  );  i  ++  )  {
			 lstrcpyn(  contents[i],  pT,  mycountof(  contents[i]  )  );
			 len1  =  lstrlen(  contents[i]  );
			 pT  +=  len1;  len  -=  len1;  
		}
	}

	memset(  txtContents,  0,  sizeof(  txtContents  )  );
	if  (  pRcd->txtContent[0]  )  {
			
		//
		pT  =  pRcd->txtContent;
		len  =  lstrlen(  pT  );
		for  (  i  =  0;  len  &&  i<  mycountof(  txtContents  );  i  ++  )  {
			 lstrcpyn(  txtContents[i],  pT,  mycountof(  txtContents[i]  )  );
			 len1  =  lstrlen(  txtContents[i]  );
			 pT  +=  len1;  len  -=  len1;  
		}
	}

	//
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr_send,senderDesc,tSendTime,uiTranNo,uiSeqNo,tStartTime_serv,uiSerialNo,idStr_recv,receiverDesc,iRole,tRecvTime,usRespCode,uiType,content0,content1,content2,content3,content4,content5,content6,content7,content8,content9,txtContent0,txtContent1,txtContent2,txtContent3,txtContent4,txtContent5,txtContent6,txtContent7,txtContent8,txtContent9,firstTime,lastTime,tLastModifiedTime,iStatus)"  )
													_T(  " values(       %s,        '%s',      %s,        '%s',    %d,       %d,      '%s',           %d,      '%s',       %s,          %d,    '%s',      %d,        %d,    %s,      %s,       %s,     %s,       %s,     %s,      %s,       %s,     %s,      %s,     %s,        %s,          %s,         %s,         %s,         %s,         %s,         %s,         %s,         %s,       '%s',     '%s',    '%s',             %d)"  ),
												CONST_tabName_qyImMsgTab, 
												getDbValStr(  iDbType,  CONST_iDataType_misServName,  pRcd->misServName  ),  CString(  idStr_send  ),  getDbValStr(  iDbType,  CONST_iDataType_desc,  pRcd->senderDesc  ),  CString(  sendTime  ),  pRcd->uiTranNo,  (  int  )pRcd->usSeqNo,  
												CString(  tStartTime_serv  ),  pRcd->uiSerialNo,
												CString(  idStr_recv  ),  getDbValStr(  iDbType,  CONST_iDataType_desc,  pRcd->receiverDesc  ),  pRcd->iRole,  CString(  recvTime  ),  pRcd->usRespCode,  pRcd->uiType,  
												getDbValStr(  iDbType,  CONST_iDataType_content,  contents[0]  ),  
												getDbValStr(  iDbType,  CONST_iDataType_content,  contents[1]  ),  
                                                getDbValStr(  iDbType,  CONST_iDataType_content,  contents[2]  ),  
                                                getDbValStr(  iDbType,  CONST_iDataType_content,  contents[3]  ),  
                                                getDbValStr(  iDbType,  CONST_iDataType_content,  contents[4]  ),  
                                                getDbValStr(  iDbType,  CONST_iDataType_content,  contents[5]  ),  
                                                getDbValStr(  iDbType,  CONST_iDataType_content,  contents[6]  ),  
                                                getDbValStr(  iDbType,  CONST_iDataType_content,  contents[7]  ),  
                                                getDbValStr(  iDbType,  CONST_iDataType_content,  contents[8]  ),  
                                                getDbValStr(  iDbType,  CONST_iDataType_content,  contents[9]  ),  
												//
												getDbValStr(  iDbType,  CONST_iDataType_content,  txtContents[0]  ),  
												getDbValStr(  iDbType,  CONST_iDataType_content,  txtContents[1]  ),  
												getDbValStr(  iDbType,  CONST_iDataType_content,  txtContents[2]  ),  
												getDbValStr(  iDbType,  CONST_iDataType_content,  txtContents[3]  ),  
												getDbValStr(  iDbType,  CONST_iDataType_content,  txtContents[4]  ),  
												getDbValStr(  iDbType,  CONST_iDataType_content,  txtContents[5]  ),  
												getDbValStr(  iDbType,  CONST_iDataType_content,  txtContents[6]  ),  
												getDbValStr(  iDbType,  CONST_iDataType_content,  txtContents[7]  ),  
												getDbValStr(  iDbType,  CONST_iDataType_content,  txtContents[8]  ),  
												getDbValStr(  iDbType,  CONST_iDataType_content,  txtContents[9]  ),  
												//
												CString(  firstTime  ),  CString(  lastTime  ),  CString(  lastModifiedTime  ),  pRcd->iStatus  );
	OutputDebugString(  sqlBuf  );  OutputDebugString(  _T(  "\n"  )  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;

}

 BOOL  bGetImMsgRcdBySth_odbc(  void  *  pDbParam,  int  iDbType,  int  id,  IM_MSG_RCD  *  pObj  )
{
	 BOOL			bRet									=		FALSE;
	 TCHAR			sqlBuf[1024];
	 CDBVariant		varVals[40];
	 int			index;
	 TCHAR			tBuf[256];
	 char			buf[255  +  1]							=		"";
	 CString		str;
	 int			i;
	 char			idStr_send[CONST_qyMessengerIdStrLen  +  1]		=	"";
	 char			tSendTime[CONST_qyTimeLen  +  1]				=	"";
	 

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,misServName,idStr_send,senderDesc,tSendTime,uiTranNo,uiSeqNo,uiType,tStartTime_serv,uiSerialNo,idStr_recv,receiverDesc,iRole,content0,content1,content2,content3,content4,content5,content6,content7,content8,content9,txtContent0,txtContent1,txtContent2,txtContent3,txtContent4,txtContent5,txtContent6,txtContent7,txtContent8,txtContent9 from %s where id=%d"  ),  CONST_tabName_qyImMsgTab,  id  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlBuf,  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;

	 if  (  pObj  )  {
		 memset(  pObj,  0,  sizeof(  pObj[0]  )  );
		 //
		 index  =  0;	MACRO_sqlLong(  varVals[index],  pObj->id  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pObj->misServName,  mycountof(  pObj->misServName  )  ); 
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,   mycountof(  buf  )  );  idStr2Info(  buf,  &pObj->idInfo_send  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pObj->senderDesc,  mycountof(  pObj->senderDesc  )  ); 
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,   mycountof(  buf  )  );  pObj->tSendTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  pObj->uiTranNo  );
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  pObj->usSeqNo  );
		 index  ++	;	MACRO_sqlLong(  varVals[index],  pObj->uiType  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,   mycountof(  buf  )  );  pObj->tStartTime_serv  =  gettTimeByBuf(  buf  );
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  pObj->uiSerialNo  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,   mycountof(  buf  )  );  idStr2Info(  buf,  &pObj->idInfo_recv  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pObj->receiverDesc,  mycountof(  pObj->receiverDesc  )  ); 
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  pObj->iRole  );	 
		 //				
		 str  =  CString(  ""  );
		 for  (  i  =  0;  i  <  10;  i  ++  )  {
			  index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  str  +=  tBuf;
		 }
		 lstrcpyn(  pObj->content,  str,  mycountof(  pObj->content  )  );

		 str  =  CString(  ""  );
		 for  (  i  =  0;  i  <  10;  i  ++  )  {
			  index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  str  +=  tBuf;
		 }
		 lstrcpyn(  pObj->txtContent,  str,  mycountof(  pObj->txtContent  )  );

	 }

	 bRet  =  TRUE;

errLabel:

	 if  (  bRet  )  {
		 if  (  pObj  )  {
			 unescapeTStr(  pObj->content,  mycountof(  pObj->content  )  );
			 unescapeTStr(  pObj->txtContent,  mycountof(  pObj->txtContent  )  );
		 }
	 }

	 return  bRet;

}


 BOOL  bGetQyDynBmpRcdBySth_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex,  int  id,  QY_dynBmp_RCD  *  pRcd  )
{
	BOOL		bRet										=	FALSE;
	CString		sqlStr;
	char		idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";
	TCHAR		whereClause[CONST_maxSqlClauseLen  +  1]	=	_T(  ""  );
	char		buf[128];
	CDBVariant	varVals[32];
	int			index;
	TCHAR		tBuf[255  +  1];
		
	sqlStr  =  CString(  ""  )  +  _T(  "select id,misServName,idStr,uiObjType,usIndex,name,cusname,iStatus,startTime,endTime from "  )  +  CONST_tabName_qyDynBmpTab;

	if  (  misServName  &&  bMessengerIdValid(  pIdInfo  )  &&  uiObjType  )  {
		idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  );
        sqlStr  =  sqlStr  +  _T(  " where misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  +  _T(  " and idStr='"  )  +  CString(  idStr  )  +  _T(  "' and uiObjType="  )  +  CString(  ltoa(  uiObjType,  buf,  10  )  );
		sqlStr  =  sqlStr  +  _T(  " and usIndex="  )  +  CString( ltoa(  usIndex,  buf,  10  )  );
		}
	else  {
		  sqlStr  =  sqlStr  +  _T(  " where id="  )  +  CString(  ltoa(  id,  buf,  10  )  );
	}

	if  (  !bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;

	if  (  pRcd  )  {
		memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

		index  =  0;	MACRO_sqlLong(  varVals[index],  pRcd->id  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );  
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo  );
		index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->uiObjType  );
		index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->usIndex  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->name,  mycountof(  pRcd->name  )  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->cusName,  mycountof(  pRcd->cusName  )  );
		index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->iStatus  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRcd->startTime,  mycountof(  pRcd->startTime  )  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRcd->endTime,  mycountof(  pRcd->endTime  )  );
		index  ++  ;

	}

	bRet  =  TRUE;
errLabel:
	return  bRet;
}

  int  auditNewMessenger_odbc(  void  *  pReserved,  QY_MESSENGER_ID  *  pLastIdInfo,  void  *  pLicenseCtx,  void  *  pDb,  int  iDbType,  POLICY_imAuthCond  *  pAuthCond,  QY_MESSENGERAUTHTMP_RCD  *  pNewMessenger  )
{
#if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
	 int				iErr										=  -1;
	 //  QMD_VAR_MIS	*	pVar										=	(  QMD_VAR_MIS  *  )pVarParam;
	 CString			sqlStr;
	 char				timeBuf[CONST_qyTimeLen  +  1]				=	"";
	 char				nMacsBuf[32]								=	"";
	 char				ip12Buf[12  +  1]							=	"";
	 int				iDataType_pcName							=	SQL_WVARCHAR;
	 int				iDataType_osUsrName							=	SQL_WVARCHAR;
	 int				iDataType_domainName						=	SQL_WVARCHAR;
	 int				iDataType_messengerName						=	SQL_WVARCHAR;
	 char				idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";
	 TCHAR				misServName[32]								=	_T(  ""  );
	 char				imObjTypeBuf[32]							=	"";

	 if  (  pAuthCond  )  {
		 if  (  pAuthCond->ucbUseMac  )  {
			 //  处理一下是否在messenger中有相同的MAC，如果有，就要
			 //		if  (  !pAuthCond->ucbAutoAudited  )  弹出框问一下，是否这个Messenger要被删除。
			 //		esle  {  自动删除有相同MAC的Messenger, 并生成日志  }
		 }
		 if  (  pAuthCond->ucbUsePcName  )  {
			 //  处理一下是否在messenger中有相同的PCNAME。。。
			 //  要记住要根据pAuthCond->ucbUseDomainName区分pcName@domainName或只有pcName
		 }
		 if  (  pAuthCond->ucbUseOsUsrName  )  {
			 //  同上
		 }
	 }

	 //  把
 	 //  if  (  qnmGetnMessengers(  pDb  )  >=  qnmMaxMessengers(  (  QY_LICENSE_CTX  *  )pLicenseCtx  )  +  2  )  {
	 if  (  qnmGetnMessengers(  pDb  )  >=  qnmMaxMessengers1(  (  QY_LICENSE_CTX  *  )pLicenseCtx  )  +  0  )  {
		 iErr  =  CONST_qyRet_needMoreLicense;  goto  errLabel;
	 }

	 if  (  getNextMessengerId(  0,  pDb,  pLastIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

	 getCurTime(  timeBuf  );
	 qyStdToIp12(  pNewMessenger->ip,  ip12Buf  ); 
	 ltoa(  pNewMessenger->uiType,  imObjTypeBuf,  10  );

	 sqlStr  =  CString(  ""  )  +  "insert into "  +  CONST_tabName_qyImObjAuthTab  +  "(misServName,idStr,uiType,mac0,mac1,mac2,nMacs,ip,pcName,osUsrName,domainName,messengerName,iStatus,startTime,tLastModifiedTime)"
									"Values("  +
									getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  +  ","  +
									"'"  +  idStr  +  "',"  +
									imObjTypeBuf  +  ","  +
									"'"  +  pNewMessenger->macsInfo.macs[0]  +  "',"  +
									"'"  +  pNewMessenger->macsInfo.macs[1]  +  "',"  +
									"'"  +  pNewMessenger->macsInfo.macs[2]  +  "',"  +
									ltoa(  pNewMessenger->macsInfo.nMacs,  nMacsBuf,  10  )  +  ","  +
									"'"  +  ip12Buf  +  "',"  +
									getDbValStr(  iDbType,  iDataType_pcName,  pNewMessenger->pcName  )  +  ","  +
									getDbValStr(  iDbType,  iDataType_osUsrName,  pNewMessenger->osUsrName  )  +  ","  +
									getDbValStr(  iDbType,  iDataType_domainName,  pNewMessenger->domainName  )  +  ","  +
									getDbValStr(  iDbType,  iDataType_messengerName,  pNewMessenger->messengerName  )  +  ","  +
									"0,"  +
									"'"  +  timeBuf  +  "',"  +
									"'"  +  timeBuf  +  "')";
	 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;
#else
	return  -1;
#endif
}


  //  nValVals pVarVals, pf FALSE
 BOOL  bEnumSqlQuery(  void  *  pDb,  LPCTSTR  sqlBuf,  PF_bCommonHandler  pfb,  void  *  p0,  void  *  p1,  void  *  pVarValsParam,  unsigned  int  nVarVals  )
{
	 BOOL								bRet					=			FALSE;
	 CDBVariant			*				pVarVals				=			(  CDBVariant  *  )pVarValsParam;
	 unsigned  int						index					=			0;
	 CRecordset							rs;   
	 unsigned  int						nFields					=			0;

	 if  (  !pDb  ||  !pVarVals  ||  !nVarVals  )  goto  errLabel;

	 try  {		

		  rs.m_pDatabase  =  (  CDatabase  * )pDb;
		  if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
			  traceLogA(  "rs open() failed, sqlBuf is %s",  sqlBuf  );  goto  errLabel;
		  }
					   
		  nFields  =  rs.GetODBCFieldCount(  );
		  if  (  nFields  >  nVarVals  )  {
			  traceLogA(  "bEnumSqlQuery failed: sizeof pVarVals is not enough"  );  goto  errLabel;
		  }		
		  //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
		  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
		  
			   for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  pVarVals[index]  );

			   if  (  pfb  &&  !pfb(  p0,  p1,  pVarVals  )  )  goto  errLabel;						
			 
		  }
				 	
			}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  L"Is",  0,  L"",  L"",  L"bEnumSqlQuery failed."  );
		   goto  errLabel;
	}
		 
	 bRet  =  TRUE;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  bRet;		

}






 #define				CONST_nPcInfoItems					17
 BOOL  bGetPcInfoByMac_odbc(  void  *  pDbParam,  char  *  mac,  unsigned  char  ucbMac0,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo  )
{
	 BOOL			bRet						=		FALSE;
	 CString		sqlStr;
	 CDBVariant		varVals[20  +  CONST_qnmMaxRegFields];
	 int			index						=		0;
	 QNM_FIELD		fields[CONST_qnmMaxRegFields];
	 int			i;
	 char			mac0[CONST_qyMacLen  +  1]	=		"";
	 TCHAR		*	pStopString;
	 char			ip12[128];
	 TCHAR			tBuf[1024];
	 
	 if  (  !mac  ||  !mac[0]  )  return  FALSE;
				//						  0			   1			2		   3			  4			  5			  6			  7			  8			     9				10                  11			       12					13			           14			   15			    16	
	 sqlStr  =  CString(  "select qyPcTab.mac0,qyPcTab.mac1,qyPcTab.mac2,qyPcTab.nMacs,qyPcTab.ip,qyPcTab.ip0,qyPcTab.ip1,qyPcTab.ip2,qyPcTab.pcName,qyPcTab.osName,qyPcTab.servicePack,qyPcTab.curUsrName,qyPcTab.proxyServer,qyPcTab.ucbAddedManually,qyPcTab.qwmVer,qyPcTab.startTime,qyPcTab.lastCommTime,"
				//			     17						18						(  +  30  )												
				" qyPcRegInfoTab.regTime,qyPcRegInfoTab.auditTime,qyPcRegInfoTab.col0,qyPcRegInfoTab.col1,qyPcRegInfoTab.col2,qyPcRegInfoTab.col3,qyPcRegInfoTab.col4,qyPcRegInfoTab.col5,qyPcRegInfoTab.col6,qyPcRegInfoTab.col7,qyPcRegInfoTab.col8,qyPcRegInfoTab.col9,qyPcRegInfoTab.col10,qyPcRegInfoTab.col11,qyPcRegInfoTab.col12,qyPcRegInfoTab.col13,qyPcRegInfoTab.col14,qyPcRegInfoTab.col15,qyPcRegInfoTab.col16,qyPcRegInfoTab.col17,qyPcRegInfoTab.col18,qyPcRegInfoTab.col19,qyPcRegInfoTab.col20,qyPcRegInfoTab.col21,qyPcRegInfoTab.col22,qyPcRegInfoTab.col23,qyPcRegInfoTab.col24,qyPcRegInfoTab.col25,qyPcRegInfoTab.col26,qyPcRegInfoTab.col27,qyPcRegInfoTab.col28,qyPcRegInfoTab.col29"  )
				+  _T(  " from qyPcTab left join qyPcRegInfoTab On qyPcTab.mac0=qyPcRegInfoTab.mac0"  )
				+  _T(  " where qyPcTab.mac0='"  )  +  CString(  mac  )  +  _T(  "'"  );
	 if  (  !ucbMac0  )  sqlStr  =  sqlStr  +  _T(  " or mac1='"  )  +  CString(  mac  )  +  _T(  "' or mac2='"  )  +  CString(  mac  )  +  _T(  "'"  );
	 //  traceLogA(  "sql is [%s]",  sqlStr.GetBuffer(  0  )  );

	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;
	 
	 MACRO_sqlStr(  varVals[0],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	 myTChar2Str(  tBuf,  mac0,  sizeof(  mac0  )  );
	
	 if  (  !pPcInfo  )  index  =  CONST_nPcInfoItems;
	 else  {
		    index  =  0;  //  mac0
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pPcInfo->macs[0],  sizeof(  pPcInfo->macs[0]  )  );
			index  ++  ;  //  mac1
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pPcInfo->macs[1],  sizeof(  pPcInfo->macs[1]  )  );
			index  ++  ;  //  mac2
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pPcInfo->macs[2],  sizeof(  pPcInfo->macs[2]  )  );
			index  ++  ;  //  nMacs
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  pPcInfo->nMacs  =  _tcstol(  tBuf,  &pStopString,  10  );
			index  ++  ;  //  ip
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  pPcInfo->ip  );
			index  ++  ;  //  ip0
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  pPcInfo->ips[0]  );  
			index  ++  ;  //  ip1
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  pPcInfo->ips[1]  );  
			index  ++  ;  //  ip2
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  pPcInfo->ips[2]  );  
			index  ++  ;  //  pcName
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pPcInfo->pcName,  sizeof(  pPcInfo->pcName  )  );
			index  ++  ;  //  osName 
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pPcInfo->osName,  sizeof(  pPcInfo->osName  )  );
			index  ++  ;  //  servicePack
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pPcInfo->servicePack,  sizeof(  pPcInfo->servicePack  )  );
			index  ++  ;  //  curUsrName
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pPcInfo->curUsrName,  sizeof(  pPcInfo->curUsrName  )  );
			index  ++  ;  //  proxyServer
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pPcInfo->proxyServer,  sizeof(  pPcInfo->proxyServer  )  );
			index  ++  ;  //  ucbAddedManually, 2004/04/11加
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  pPcInfo->ucbAddedManually  =  _tcstol(  tBuf,  &pStopString,  10  )  ?  TRUE  :  FALSE;
			index  ++  ;  //  qwmVer
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pPcInfo->qwmVer,  sizeof(  pPcInfo->qwmVer  )  );
			index  ++  ;  //  startTime
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pPcInfo->startTime,  sizeof(  pPcInfo->startTime  )  );
			index  ++  ;  //  lastCommTime
			MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pPcInfo->lastCommTime,  sizeof(  pPcInfo->lastCommTime  )  );
			index  ++  ;  
	 }
	 MACRO_qyAssert(  index  ==  CONST_nPcInfoItems,  _T(  "bGetPcInfoByMac0: index"  )  );
	 if  (  pRegInfo  )  {

	 	 safeStrnCpy(  mac0,  pRegInfo->mac0,  sizeof(  pRegInfo->mac0  )  );
		
		 pRegInfo->iCustomId  =  qyGetCustomId(  );
		 qnmSetFieldIdInRegInfo(  pRegInfo  );
		 memset(  fields,  0,  sizeof(  fields  )  );
		 if  (  qnmSetPtrs(  pFieldIdTable,  pRegInfo,  fields  )  )  goto  errLabel;

		 //  regTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pRegInfo->regTime,  sizeof(  pRegInfo->regTime  )  );  
		 index  ++  ;
		 //  auditTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pRegInfo->auditTime,  sizeof(  pRegInfo->auditTime  )  );  
		 index  ++  ;

		 for  (  i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
			  //  if  (  varVals[i  +  index].m_dwType  ==  DBVT_STRING  )  myTChar2Str(  varVals[i  +  index].m_pstring->GetBuffer(  0  ),  fields[i].ptr,  fields[i].bufSize  );
			  MACRO_sqlStr(  varVals[i  +  index],  fields[i].ptr,  fields[i].bufSize  );
	 	 }
	 	 index  +=  i;
	 }
	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}


 BOOL  bGetPcInfoByMacEx_odbc(  void  *  pDbParam,  char  *  mac,  unsigned  char  ucbMac0,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo,  QNM_REG_INFO  *  pRegInfoInTab1  )
{
	 BOOL			bRet						=		FALSE;
	 CString		sqlStr;
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index						=		0;
	 QNM_FIELD		fields[CONST_qnmMaxRegFields];
	 int			i;
	 char			mac0[CONST_qyMacLen  +  1]	=		"";
	 TCHAR			tBuf[256];
	 char			ip12Buf[128]				=		"";
	 
	 if  (  !bMacValid(  mac  )  )  return  FALSE;

				//						  0			   1			2		   3			  4			     5				6				  7				8					9
	 sqlStr  =  CString(  "select qyPcTab.mac0,qyPcTab.mac1,qyPcTab.mac2,qyPcTab.ip,qyPcTab.iPlatformId,qyPcTab.pcName,qyPcTab.osName,qyPcTab.qwmVer,qyPcTab.startTime,qyPcTab.lastCommTime"  )
					+  _T(  " from qyPcTab where qyPcTab.mac0='"  ) +  CString(  mac  )  +  _T(  "'"  );
	 if  (  !ucbMac0  )  sqlStr  =  sqlStr  +  _T(  " or mac1='"  )  +  CString(  mac  )  +  _T(  "' or mac2='"  )  +  CString(  mac  )  +  _T(  "'"  );
	 traceLogA(  "sql is [%s]",  sqlStr.GetBuffer(  0  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;

	 MACRO_sqlStr(  varVals[0],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  mac0,  sizeof(  mac0  )  );

	 if  (  pPcInfo  )  {	
		 index  =  0;  //  mac0
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPcInfo->macs[0],  sizeof(  pPcInfo->macs[0]  )  );
		 index  ++  ;  //  mac1
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPcInfo->macs[1],  sizeof(  pPcInfo->macs[1]  )  );  pPcInfo->nMacs  ++  ;  
		 index  ++  ;  //  mac2
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPcInfo->macs[2],  sizeof(  pPcInfo->macs[2]  )  );  pPcInfo->nMacs  ++  ;  
		 index  ++  ;  //  ip
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12Buf,  sizeof(  ip12Buf  )  );  qyIp12ToStd(  ip12Buf,  pPcInfo->ip  );
		 index  ++  ;  //  iPlatformId
		 MACRO_sqlLong(  varVals[index],  pPcInfo->iPlatformId  );
		 index  ++  ;  //  pcName
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPcInfo->pcName,  sizeof(  pPcInfo->pcName  )  );
		 index  ++  ;  //  osName 
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPcInfo->osName,  sizeof(  pPcInfo->osName  )  );
		 index  ++  ;  //  qwmVer
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPcInfo->qwmVer,  sizeof(  pPcInfo->qwmVer  )  );
		 index  ++  ;  //  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPcInfo->startTime,  sizeof(  pPcInfo->startTime  )  );
		 index  ++  ;  //  lastCommTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPcInfo->lastCommTime,  sizeof(  pPcInfo->lastCommTime  )  );
		 index  ++  ;

		 MACRO_qyAssert(  index  ==  10,  _T(  "bGetPcInfoByMac0Ex: index错误"  )  );

		 //  对qwmVer计算一下版本号。
		 if  (  strlen(  pPcInfo->qwmVer  )  <  6  )  pPcInfo->lhQwmVer  =  atol(  pPcInfo->qwmVer  );
		 else  {		//  2005/05/23, 将版本号升级为6位，还有可能后面跟个d
				pPcInfo->lhQwmVer  =  atol(  pPcInfo->qwmVer  )  /  100;								//  2003/09/13
				pPcInfo->llQwmVer  =  atol(  pPcInfo->qwmVer  )  %  100;								//  2005/05/23
		 }

	 }

	 if  (  pRegInfo  )  {

		 sqlStr  =  CString(  "select"  )  
	 	 					//			1			2						(  +  30  )												
				+  _T(  " qyPcRegInfoTab.regTime,qyPcRegInfoTab.auditTime,qyPcRegInfoTab.col0,qyPcRegInfoTab.col1,qyPcRegInfoTab.col2,qyPcRegInfoTab.col3,qyPcRegInfoTab.col4,qyPcRegInfoTab.col5,qyPcRegInfoTab.col6,qyPcRegInfoTab.col7,qyPcRegInfoTab.col8,qyPcRegInfoTab.col9,qyPcRegInfoTab.col10,qyPcRegInfoTab.col11,qyPcRegInfoTab.col12,qyPcRegInfoTab.col13,qyPcRegInfoTab.col14,qyPcRegInfoTab.col15,qyPcRegInfoTab.col16,qyPcRegInfoTab.col17,qyPcRegInfoTab.col18,qyPcRegInfoTab.col19,qyPcRegInfoTab.col20,qyPcRegInfoTab.col21,qyPcRegInfoTab.col22,qyPcRegInfoTab.col23,qyPcRegInfoTab.col24,qyPcRegInfoTab.col25,qyPcRegInfoTab.col26,qyPcRegInfoTab.col27,qyPcRegInfoTab.col28,qyPcRegInfoTab.col29"  ) 
				+  _T(  " from qyPcRegInfoTab"  )
				+  _T(  " where qyPcRegInfoTab.mac0='"  )  +  CString(  mac0  )  +  _T(  "'"  );
		 traceLogA(  "sql is [%s]",  sqlStr.GetBuffer(  0  )  );		 
		 if  (  bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  {
		 	 		
			 safeStrnCpy(  mac0,  pRegInfo->mac0,  sizeof(  pRegInfo->mac0  )  );
		
			 pRegInfo->iCustomId  =  qyGetCustomId(  );
			 qnmSetFieldIdInRegInfo(  pRegInfo  );
			 memset(  fields,  0,  sizeof(  fields  )  );
			 if  (  qnmSetPtrs(  pFieldIdTable,  pRegInfo,  fields  )  )  goto  errLabel;
		
			 index  =  0;  //  regTime
			 MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pRegInfo->regTime,  sizeof(  pRegInfo->regTime  )  );  
			 index  ++  ;  //  auditTime
			 MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pRegInfo->auditTime,  sizeof(  pRegInfo->auditTime  )  );  
			 index  ++  ;

			 for  (  i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
				  //  if  (  varVals[i  +  index].m_dwType  ==  DBVT_STRING  )  myTChar2Str(  varVals[i  +  index].m_pstring->GetBuffer(  0  ),  fields[i].ptr,  fields[i].bufSize  );
				  MACRO_sqlStr(  varVals[i  +  index],  fields[i].ptr,  fields[i].bufSize  );
	 	 	 }
	 	 	 index  +=  i;
	 	 }
	 
	 }


	 if  (  pRegInfoInTab1  )  {

		 sqlStr  =  CString(  "select"  )  
	 	 					//			1			2						(  +  30  )												
				+  _T(  " qyPcRegInfoTab1.regTime,qyPcRegInfoTab1.auditTime,qyPcRegInfoTab1.col0,qyPcRegInfoTab1.col1,qyPcRegInfoTab1.col2,qyPcRegInfoTab1.col3,qyPcRegInfoTab1.col4,qyPcRegInfoTab1.col5,qyPcRegInfoTab1.col6,qyPcRegInfoTab1.col7,qyPcRegInfoTab1.col8,qyPcRegInfoTab1.col9,qyPcRegInfoTab1.col10,qyPcRegInfoTab1.col11,qyPcRegInfoTab1.col12,qyPcRegInfoTab1.col13,qyPcRegInfoTab1.col14,qyPcRegInfoTab1.col15,qyPcRegInfoTab1.col16,qyPcRegInfoTab1.col17,qyPcRegInfoTab1.col18,qyPcRegInfoTab1.col19,qyPcRegInfoTab1.col20,qyPcRegInfoTab1.col21,qyPcRegInfoTab1.col22,qyPcRegInfoTab1.col23,qyPcRegInfoTab1.col24,qyPcRegInfoTab1.col25,qyPcRegInfoTab1.col26,qyPcRegInfoTab1.col27,qyPcRegInfoTab1.col28,qyPcRegInfoTab1.col29"  )  
				+  _T(  " from qyPcRegInfoTab1"  )
				+  _T(  " where qyPcRegInfoTab1.mac0='"  )  +  CString(  mac0  )  +  _T(  "'"  );
		 traceLogA(  "sql is [%s]",  sqlStr.GetBuffer(  0  )  );
		 if  (  bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  {
		 			 
			 safeStrnCpy(  mac0,  pRegInfoInTab1->mac0,  sizeof(  pRegInfoInTab1->mac0  )  );
				 
			 pRegInfoInTab1->iCustomId  =  qyGetCustomId(  );
			 qnmSetFieldIdInRegInfo(  pRegInfoInTab1  );
			 memset(  fields,  0,  sizeof(  fields  )  );
			 if  (  qnmSetPtrs(  pFieldIdTable,  pRegInfoInTab1,  fields  )  )  goto  errLabel;
		
			 index  =  0;	 //  regTime
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfoInTab1->regTime,  sizeof(  pRegInfoInTab1->regTime  )  );  
			 index  ++  ;	 //  auditTime	
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfoInTab1->auditTime,  sizeof(  pRegInfoInTab1->auditTime  )  );  
			 index  ++  ;

			 for  (  i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
				  //  if  (  varVals[i  +  index].m_dwType  ==  DBVT_STRING  )  myTChar2Str(  varVals[i  +  index].m_pstring->GetBuffer(  0  ),  fields[i].ptr,  fields[i].bufSize  );
				  MACRO_sqlStr(  varVals[i  +  index],  fields[i].ptr,  fields[i].bufSize  );
	 	 	 }
	 	 	 index  +=  i;
		 }

	 }
	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}

// 2013/02/19
 BOOL  bLogEventFunc_is_odbc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QIS_EVENT  *  pEvent  )
{
	 int		iErr									=	-1;
	 CString	sqlStr;
	 char		helpRandBuf[32]							=	"";
	 char		buf[128]								=	"";
	 char		idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";
	 char		detectedIp12[128]						=	"";
	 char		ip12[128]								=	"";

	 qyStdToIp12(  pEvent->detectedIp,  detectedIp12  );
	 qyStdToIp12(  pEvent->ip,  ip12  );

	 idInfo2Str(  &pEvent->idInfo,  idStr,  mycountof(  idStr  )  );
	 sqlStr  =  CString(  ""  )  +  _T(  "insert into qyImEventTab("  )
							  _T(  "helpRand,misServName,idStr,detectedIp,ip,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,usrName,des0,des1,des2,des3,des4,des5,des6,des7,des8,des9,eventType,cntEventTime,localCntEventTime,localEventTime,dsnName,comment0)"  )
							  _T(  " Values("  )  +  
							  CString(  _ltoa(  pEvent->lHelpRand,  helpRandBuf,  10  )  )  +  _T(  ","  )  +
							  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pEvent->misServName  )  +  _T(  ","  )  +
							  _T(  "'"  )  +  CString(  idStr  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  detectedIp12  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  ip12  )  +  _T(  "',"  )  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[0]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[0]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[1]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[1]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[2]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[2]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[3]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[3]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[4]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[4]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[5]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[5]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[6]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[6]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[7]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[7]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[8]  )  +  _T(  ","  )	 	+	//  "'"  +  pEvent->cols[8]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[9]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[9]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->usrName  )  +  _T(  ","  )		+	//  "'"  +  pEvent->usrName  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[0]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[0]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[1]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[1]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[2]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[2]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[3]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[3]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[4]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[4]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[5]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[5]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[6]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[6]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[7]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[7]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[8]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[8]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[9]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[9]  +  "',"  +							  
							  CString(  _ltoa(  pEvent->lEventType,  buf,  10  )  )  +  _T(  ","  )  +
							  _T(  "'"  )  +  CString(  pEvent->cntEventTime  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pEvent->localCntEventTime  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pEvent->localEventTime  )  +  _T(  "',"  )  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->dsnName  )  +  _T(  ","  )		+		//  2007/01/02
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->comment  )  +  _T(  ")"  );			//  "'"  +  pEvent->comment  +  "')";
				   traceLogA(  "sql is [%S]",  sqlStr  );

	return  bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  );
	
}

 int  getEventInfoBySth_odbc(  void  *  pDbParam,  int  iDbType,  QIS_EVENT  *  pEvent  )
{
	 int			iErr			=  -1;
	 CDatabase  *	pDb				=	(  CDatabase  *  )pDbParam;
	 CString		sqlStr;
	 CDBVariant		varVal[CONST_qnmMaxEventRegFields];
	 int			cnt				=  0,  i;
	 TCHAR			sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	 TCHAR			tBuf[256];
	 int			index;
	 char			ip12Buf[128]	=	"";
	 char			idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";

	 if  (  !pEvent  )  return  -1;

	 if  (  !idInfo2Str(  &pEvent->idInfo,  idStr,  mycountof(  idStr  )  )  )  return  -1;

	 sqlStr  =  CString(  ""  )  +  _T(  "select ip from qyImObjTab where misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pEvent->misServName  )  +  _T(  " and idStr='"  )  +  CString(  idStr  )  +  _T(  "'"  );
	 traceLogA(  "getPcEventInfoByMac0, %s",  sqlStr.GetBuffer(  0  )  );


	 bool  bExcept  =  false;
	 if  (  !bQyGetRcdBySql1(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVal  )  /  sizeof(  varVal[0]  ),  varVal,  &bExcept,  _T("l2714"))) {
		 //
		 if  (  bExcept  )  {
			 set_bConnectionTimeout(  _T(  "getEventInfoBySth.bQyGetRcdBySql failed"  )  );
		 }
		 //
		 goto  errLabel;
	 }

	 index  =  0;	MACRO_sqlStr(  varVal[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12Buf,  sizeof(  ip12Buf  )  );  qyIp12ToStd(  ip12Buf,  pEvent->ip  );
	 	 
	 sqlBuf[0]  =  0;
	 for  (  cnt  =  0,  i  =  0;  gpEventRegColsTable[i].type  !=  -1;  i  ++  )  {
		  if  (  gpEventRegColsTable[i].type  ==  CONST_nullColId  )  continue;
		  if  (  gpEventRegColsTable[i].type  >=  CONST_qnmMaxRegFields  )  {
			  MACRO_qyAssert(  0,  _T(  "gpEventRegColsTable[n].type应小于CONST_qnmMaxEventRegFields"  )  );  
			  goto  errLabel;
		  }
		  if  (  !sqlBuf[0]  )  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select col%d"  ),  gpEventRegColsTable[i].type  );
		  else  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s,col%d"  ),  sqlBuf,  gpEventRegColsTable[i].type  );
		  cnt  ++  ;
	 }
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s from qyImObjRegInfoTab where misServName=%s and idStr='%s'"  ),  sqlBuf,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pEvent->misServName  ),  CString(  idStr  )  );
	 if  (  cnt  >=  CONST_qnmMaxEventRegFields  )  {
		 MACRO_qyAssert(  0,  _T(  "index 应小于 CONST_qnmMaxEventRegFields"  )  );  goto  errLabel;
	 }

	 if  (  bQyGetRcdBySql(  pDb,  sqlBuf,  cnt,  varVal  )  )  {
		 for  (  i  =  0,  cnt  =  0;  gpEventRegColsTable[i].type  !=  -1;  i  ++  )  {
			  if  (  gpEventRegColsTable[i].type  ==  CONST_nullColId  )  continue;
			  //  
			  MACRO_sqlStr(  varVal[cnt],  pEvent->cols[i],  mycountof(  pEvent->cols[i]  )  );
			  cnt  ++  ;
		 }		 
	 }
	 
	 iErr  =  0;

errLabel:

	 return  iErr;
}

  int  getPcEventInfoByMac0_odbc(  void  *  pDbParam,  QNM_PC_EVENT  *  pEvent  )
{
	 int			iErr			=  -1;
	 CDatabase  *	pDb				=	(  CDatabase  *  )pDbParam;
	 CString		sqlStr;
	 CDBVariant		varVal[CONST_qnmMaxEventRegFields];
	 int			cnt				=  0,  i;
	 char			buf[CONST_qyMaxSqlBufLen  +  1];
	 TCHAR			tBuf[256];
	 int			index;
	 char			ip12Buf[128]	=	"";

	 if  (  !pEvent  )  return  -1;

	 sqlStr  =  CString(  ""  )  +  _T(  "select mac1,mac2,ip from qyPcTab where mac0='"  )  +  CString(  pEvent->macs[0]  )  +  _T(  "'"  );
	 traceLogA(  "getPcEventInfoByMac0, %s",  sqlStr.GetBuffer(  0  )  );

	 if  (  !bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVal  )  /  sizeof(  varVal[0]  ),  varVal  )  )  goto  errLabel;

	 index  =  0;	MACRO_sqlStr(  varVal[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pEvent->macs[1],  sizeof(  pEvent->macs[1]  )  );
	 index  ++  ;	MACRO_sqlStr(  varVal[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pEvent->macs[2],  sizeof(  pEvent->macs[2]  )  );
	 index  ++  ;	MACRO_sqlStr(  varVal[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12Buf,  sizeof(  ip12Buf  )  );  qyIp12ToStd(  ip12Buf,  pEvent->ip  );
	 	 
	 buf[0]  =  0;
	 for  (  cnt  =  0,  i  =  0;  gpEventRegColsTable[i].type  !=  -1;  i  ++  )  {
		  if  (  gpEventRegColsTable[i].type  ==  CONST_nullColId  )  continue;
		  if  (  gpEventRegColsTable[i].type  >=  CONST_qnmMaxRegFields  )  {
			  MACRO_qyAssert(  0,  _T(  "gpEventRegColsTable[n].type >= CONST_qnmMaxEventRegFields"  )  );  
			  goto  errLabel;
		  }
		  if  (  !buf[0]  )  _snprintf(  buf,  sizeof(  buf  ),  "select col%d",  gpEventRegColsTable[i].type  );
		  else  _snprintf(  buf,  sizeof(  buf  ),  "%s,col%d",  buf,  gpEventRegColsTable[i].type  );
		  cnt  ++  ;
	 }
	 _snprintf(  buf,  sizeof(  buf  ),  "%s from qyPcRegInfoTab where mac0='%s'",  buf,  pEvent->macs[0]  );
	 if  (  cnt  >=  CONST_qnmMaxEventRegFields  )  {
		 MACRO_qyAssert(  0,  _T(  "index  >= CONST_qnmMaxEventRegFields"  )  );  goto  errLabel;
	 }

	 if  (  bQyGetRcdBySql(  pDb,  CString(  buf  ).GetBuffer(  0  ),  cnt,  varVal  )  )  {
		 for  (  i  =  0,  cnt  =  0;  gpEventRegColsTable[i].type  !=  -1;  i  ++  )  {
			  if  (  gpEventRegColsTable[i].type  ==  CONST_nullColId  )  continue;
			  //  if  (  varVal[cnt].m_dwType  ==  DBVT_STRING  )  {
			  //	  myTChar2Str(  varVal[cnt].m_pstring->GetBuffer(  0  ),  pEvent->cols[i],  sizeof(  pEvent->cols[i]  )  );
			  //  }
			  MACRO_sqlStr(  varVal[cnt],  pEvent->cols[i],  sizeof(  pEvent->cols[i]  )  /  sizeof(  TCHAR  )  );
			  cnt  ++  ;
		 }		 
	 }
	 
	 iErr  =  0;

errLabel:

	 return  iErr;
}

 //  2013/02/19
 BOOL  bLogPcEventFunc_odbc(  void  *  pDb,  int  iDbType,  QNM_PC_EVENT  *  pEvent  )
{
	 int		iErr				=	-1;
	 CString	sqlStr;
	 char		helpRandBuf[32]		=	"";
	 char		buf[128]			=	"";
	 char		portIfIndexBuf[32]	=	"";

	 switch  (  pEvent->iCustomId  )  {
	 		 case  CONST_qyCustomId_shhg:
			 default:

				   sqlStr  =  CString(  ""  )  +  _T(  "insert into qyPcEventTab("  )  +
							  _T(  "helpRand,mac0,mac1,mac2,ip,productName,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,usrName,connectedMac,portIfIndex,des0,des1,des2,des3,des4,des5,des6,des7,des8,des9,eventType,cntEventTime,localCntEventTime,localEventTime,dsnName,comment0)"  )  +
							  _T(  " Values("  )  +  
							  CString(  _ltoa(  pEvent->lHelpRand,  helpRandBuf,  10  )  )  +  _T(  ","  )  +
							  _T(  "'"  )  +  CString(  pEvent->macs[0]  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pEvent->macs[1]  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pEvent->macs[2]  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pEvent->ip  )    +  _T(  "',"  )  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->productName  )  +  _T(  ","  )  +		//  "'"  +  pEvent->productName  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[0]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[0]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[1]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[1]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[2]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[2]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[3]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[3]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[4]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[4]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[5]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[5]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[6]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[6]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[7]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[7]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[8]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[8]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->cols[9]  )  +  _T(  ","  )		+	//  "'"  +  pEvent->cols[9]  +  "',"  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->usrName  )  +  _T(  ","  )		+	//  "'"  +  pEvent->usrName  +  "',"  +
							  _T(  "'"  )  +  CString(  pEvent->connectedMac  )  +  _T(  "',"  )  +
							  CString(  _ltoa(  pEvent->iPortIfIndex,  portIfIndexBuf,  10  )  )  +  _T(  ","  )  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[0]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[0]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[1]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[1]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[2]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[2]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[3]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[3]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[4]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[4]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[5]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[5]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[6]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[6]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[7]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[7]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[8]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[8]  +  "',"  +							  
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->deses[9]  )  +  _T(  ","  )	+		//  "'"  +  pEvent->deses[9]  +  "',"  +							  
							  CString(  _ltoa(  pEvent->lEventType,  buf,  10  )  )  +  _T(  ","  )  +
							  _T(  "'"  )  +  CString(  pEvent->cntEventTime  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pEvent->localCntEventTime  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pEvent->localEventTime  )  +  _T(  "',"  )  +
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->dsnName  )  +  _T(  ","  )		+		//  2007/01/02
							  getDbValStr(  iDbType,  SQL_WVARCHAR,  pEvent->comment  )  +  _T(  ")"  );			//  "'"  +  pEvent->comment  +  "')";
				   traceLogA(  "sql is [%S]",  sqlStr  );
				   break;
	
	}

	return  bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  );
	
}


 int  qisRegOtherInfoInTab_odbc(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  MSGR_ADDR  *  pAddr,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  )
{
	 int						iErr										=	-1;
	 CString					sqlStr;
	 int						i;
	 int						iQwmVer										=	0;
	 CDBVariant					varVals[5];
	 unsigned  char				ucbAudited									=	FALSE;
	 unsigned  char				ucbReged									=	FALSE;
	 TCHAR						tBuf[1024];
	 int						id											=	0;

	 traceLogA(  "qisRegOtherInfoInTab enters"  );

	 if  (  !pRegInfo  )  goto  errLabel;
	 if  (  pAddr  )  {
		 memcpy(  &pRegInfo->addr,  pAddr,  sizeof(  pRegInfo->addr  )  );
	 }

	 getCurTime(  pRegInfo->tLastModifiedTime  );

	 MACRO_setPtrs(  pFieldIdTable,  pRegInfo[0],  pRegInfo->fields  );
	 for  (  i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
		  if  (  pRegInfo->fields[i].bufSize  )  pRegInfo->fields[i].ptr[pRegInfo->fields[i].bufSize  -  1]  =  0;
	 }

	 
	 //  已审核，且pRegInfo属未审核信息，pRegInfo将更新入qyPcRegInfoTab1中
	 //

	 //  Tab1中没有
	 sqlStr  =  CString(  ""  )  +  _T(  "select id from "  )  +  tabName  +  _T(  " where misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pRegInfo->addr.misServName  )  +  _T(  " and uiDevType="  )  +  _ltot(  pRegInfo->addr.uiDevType,  tBuf,  10  )  +  _T(  " and wDevIdStr="  )  +  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  pRegInfo->addr.wDevIdStr  )  +  _T(  ""  );
	 if  (  !bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  {						//  未注册的情况
		 getCurTime(  pRegInfo->regTime  );
		 sqlStr  =  CString(  "insert into "  )  +  tabName  +  _T(  "(misServName,uiDevType,wDevIdStr,regTime,auditTime,tLastModifiedTime,tCommitTime,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,comment0)"  )  +
							  _T(  "values("  )  +  
							  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pRegInfo->addr.misServName  )  +  _T(  ","  )  +
							  _ltot(  pRegInfo->addr.uiDevType,  tBuf,  10  )  +  _T(  ","  )  +
							  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  pRegInfo->addr.wDevIdStr  )  +  _T(  ","  )  +
							  _T(  "'"  )  +  CString(  pRegInfo->regTime  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pRegInfo->auditTime  )  +  _T(  "',"  )  +
							  _T(  "'"  )  +  CString(  pRegInfo->tLastModifiedTime  )  +  _T(  "',"  )  +
							  _T(  "'',"  );
		 for  (  i  =  0;  i  <  20;  i  ++   )  {
			  sqlStr  =  sqlStr  +  getDbValStr(  iDbType,  pRegInfo->fields[i].iDataType,  pRegInfo->fields[i].ptr  )  +  _T(  ","  );
		 }
		 sqlStr  =  sqlStr  +  _T(  "''"  )  +  _T(  ")"  );
		 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			 traceLogA(  "qnmRegUsrInfo: insert into qyPcRegInfoTab1 failed"  );
			 goto  errLabel;
		 }			 
		 
		 iErr  =  0;  goto  errLabel;
	
	 }

	 MACRO_sqlLong(  varVals[0],  id  );
	
	 //  Tab1中有
	 {
		
		 sqlStr  =  CString(  "update "  )  +  tabName  +  _T(  " set "  );
		 if  (  pRegInfo->auditTime[0]  )  sqlStr  +=  CString(  "auditTime='"  )  +  CString(  pRegInfo->auditTime  )  +  _T(  "',"  );
		 if  (  pRegInfo->regTime[0]  )  sqlStr  +=  CString(  "regTime='"  )  +  CString(  pRegInfo->regTime  )  +  _T(  "',"  );
		 sqlStr  +=  CString(  "tLastModifiedTime='"  )  +  CString(  pRegInfo->tLastModifiedTime  )  +  _T(  "',"  );
		 sqlStr  +=  CString(  "tCommitTime='',"  );
		 for  (  i  =  0;  i  <  20;  i  ++  )  {
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "col%d"  ),  i  );
			  sqlStr  =  sqlStr  +  tBuf  +  _T(  "="  )  +  getDbValStr(  iDbType,  pRegInfo->fields[i].iDataType,  pRegInfo->fields[i].ptr  )  +  _T(  ","  );
		 }
		 sqlStr  =  sqlStr  +  _T(  "comment0='' where id="  )  +  _ltot(  id,  tBuf,  10  )  +  _T(  ""  );
	 	 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			 traceLogA(  "qnmRegUsrInfo: update qyPcRegInfoTab failed"  );
			 goto  errLabel;
		 }
				 
		 iErr  =  0;  goto  errLabel;

	 }


	 iErr  =  0;

errLabel:

	 traceLogA(  "qisRegOtherInfoInTab leaves"  );

	 return  iErr;

}

