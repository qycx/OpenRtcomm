

#include	"stdafx.h"

//  #include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>

//#include	"qyMcMainCommon.h"

#include	"qmCommon.h"
#include	"qyDbCommon.h"
#include	"qyTCharCommProc.h"


#include	"myDb.h"

#include	"qyMcMainCommon.h"    //  2013/02/08






//
int  tmpHandler_bGetMessengerRegInfoBySth_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	int  i;
	QY_MC					*  pQyMc		=	 QY_GET_GBUF(  );

	QY_MESSENGER_ID			*  pIdInfo		=    (  QY_MESSENGER_ID  *  )p0;
	QY_MESSENGER_REGINFO	*  pRegInfo		=	 (  QY_MESSENGER_REGINFO  *  )p1;
	QMEM_qyImObjRegInfo		*  pQMem		=	 (  QMEM_qyImObjRegInfo  *  )p2;

	if  (  pQMem->myRegInfo.addr.idInfo.ui64Id  ==  pIdInfo->ui64Id  )  {
		
		memset(  pRegInfo,  0,  sizeof(  pRegInfo[0]  )  );
		pRegInfo->uiType  =  CONST_imCommType_messengerRegInfo;
		//  id
		pRegInfo->iCustomId  =  qyGetCustomId(  );

		memcpy(  &pRegInfo->addr,  &pQMem->myRegInfo.addr,  sizeof(  pRegInfo->addr  )  );
		
		memcpy(  pRegInfo->uiFieldIds,  pQMem->myRegInfo.uiFieldIds,  sizeof(  pQMem->myRegInfo.uiFieldIds  )  );
		memcpy(  pRegInfo->u.cols,  pQMem->myRegInfo.u.cols,  sizeof(  pRegInfo->u.cols  )  );
		
		//
		MACRO_setPtrs(  CONST_fieldIdTable_en,  pRegInfo[0],  pRegInfo->fields  );
		
		//
		iRet  =  1;  goto  errLabel;
	}

	iRet  =  0;
errLabel:
	return  iRet;
}

 //  2013/02/04
 BOOL  bGetMessengerRegInfoBySth_myDb(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  )
{
	 BOOL			bRet									=		FALSE;
	 CMyDb		*	pDb										=		(  CMyDb  *  )pDbParam;

	 if  (  !pTabName  )  return  FALSE;
	 if  (  !misServName  ||  !pIdInfo  ||  !pIdInfo->ui64Id  )  {
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "bGetMessengerRegInfoBySth_myDb failed, param err"  )  );
		 #endif
		 return  FALSE;
	 }

	 if  (  !lstrcmpi(  pTabName,  CONST_tabName_qyImObjRegInfoTab  )  )  {
		 if  (  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_bGetMessengerRegInfoBySth_myDb,  pIdInfo,  pRegInfo  )  <=  0  )  goto  errLabel;
	 }
	 else 
		 goto  errLabel;

#if  0
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
				+  " misServName,idStr,regTime,auditTime,tCommitTime,tLastModifiedTime,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,col20,col21,col22,col23,col24,col25,col26,col27,col28,col29" 
				+  " from "  +  pTabName
				+  " where "  +  whereBuf;
	 OutputDebugString(  sqlStr  +  "\n"  );
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
#endif
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}
