

#include	"stdafx.h"
#include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>

#include	"qmCommon.h"
#include	"qyDbCommon.h"
#include	"qyTCharCommProc.h"
#include	"myDb.h"


//

  __declspec(  dllexport  )  int  delPcSth(  void  *  pDb,  LPCTSTR  hint,  LPCTSTR  tabName,  LPCTSTR  whereClause  )
{
	 int		iErr		=	-1;
	 TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1];
	 //  char	*	hint		=	"ÊÇ·ñÉ¾³ý¸ÃPCµÄÏµÍ³ÈÕÖ¾?";

	 //if  (  hint  &&  myMessageBox(  NULL,  hint,  _T(  ""  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
	 //
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s"  ),  CQyString(  tabName  )  );
	 if  (  whereClause  &&  whereClause[0]  )  {
		 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where %s"  ),  sqlBuf,  whereClause  );
	 }
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
	 iErr  =  0;

errLabel:
	 return  iErr;
}


 __declspec(  dllexport  )  int  delImObj(  void  *  pDb,  int  iDbType,  BOOL  bClient,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{
	int			iErr									=	-1;
	char		idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";
	CQyString		whereClause;

	if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  return  -1;

	//  ÏÈÉ¾³ýimGrpMemTab
	whereClause  =  CQyString(  "misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )
		+  CQyString(  " and idStr_mem='"  )  +  CQyString(  idStr  )  +  CQyString(  "'"  );
	if  (  delPcSth(  pDb,  NULL,  _T(  "qyImGrpMemTab"  ),  whereClause  )  )  goto  errLabel;
	whereClause  =  CQyString(  "misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )
		+  CQyString(  " and idStr_grp='"  )  +  CQyString(  idStr  )  +  CQyString(  "'"  );
	if  (  delPcSth(  pDb,  NULL,  _T(  "qyImGrpMemTab"  ),  whereClause  )  )  goto  errLabel;

	//  2009/09/17
	if  (  !bClient  )  {
		whereClause  =  CQyString(  "misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )
			+  CQyString(  " and (idStr='"  )  +  CQyString(  idStr  )  +  CQyString(  "' or idStr_visitor='"  )  +  CQyString(  idStr  )  +  CQyString(  "')"  );
		if  (  delPcSth(  pDb,  NULL,  CONST_tabName_qyDynBmpRuleTab,  whereClause  )  )  goto  errLabel;
	}

	whereClause  =  CQyString(  "misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )
		+  CQyString(  " and (idStr='"  )  +  CQyString(  idStr  )  +  CQyString(  "')"  );
	if  (  delPcSth(  pDb,  NULL,  CONST_tabName_qyDynBmpTab,  whereClause  )  )  goto  errLabel;

	//
	whereClause  =  CQyString(  "misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )
		+  CQyString(  " and idStr='"  )  +  CQyString(  idStr  )  +  CQyString(  "'"  );
	
	if  (  delPcSth(  pDb,  NULL,  _T(  "qyImGrpInfoTab"  ),  whereClause  )  )  goto  errLabel;
	
	if  (  delPcSth(  pDb,  NULL,  _T(  "qyImObjRegInfoTab"  ),  whereClause  )  )  goto  errLabel;
	if  (  delPcSth(  pDb,  NULL,  _T(  "qyImObjRegInfoTab1"  ),  whereClause  )  )  goto  errLabel;
	if  (  delPcSth(  pDb,  NULL,  _T(  "qyImObjTab"  ),  whereClause  )  )  goto  errLabel;
	
	if  (  !bClient  )  {
		if  (  delPcSth(  pDb,  NULL,  CONST_tabName_qyWebContactTab,  whereClause  )  )  goto  errLabel;
	}
	if  (  delPcSth(  pDb,  NULL,  CONST_tabName_qyMessengerPhoneInfoTab,  whereClause  )  )  goto  errLabel;
	
	if  (  !bClient  )  {  //  2010/01/05
		if  (  delPcSth(  pDb,  NULL,  CONST_tabName_qyImAmTab,  whereClause  )  )  goto  errLabel;
	}

	if  (  !bClient  )  {
		whereClause  =  CQyString(  "misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )
			+  CQyString(  " and (idStr='"  )  +  CQyString(  idStr  )  +  CQyString(  "' or idStr_related='"  )  +  CQyString(  idStr  )  +  CQyString(  "')"  );
		//  2010/08/16
		if  (  delPcSth(  pDb,  NULL,  CONST_tabName_qyImObjRuleTab,  whereClause  )  )  goto  errLabel;
	}

	//
	whereClause  =  CQyString(  "misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )
		+  CQyString(  " and idStr='"  )  +  CQyString(  idStr  )  +  CQyString(  "'"  );
	if  (  delPcSth(  pDb,  NULL,  _T(  "qyImObjAuthTab"  ),  whereClause  )  )  goto  errLabel;
	
	iErr  =  0;
errLabel:
	return  iErr;
}

