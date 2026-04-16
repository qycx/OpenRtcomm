


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
		#include	"qyMcMainCommon.h"
		
		#include	"qmcCommFunc_iscli.h"

#endif














//
// 
 static  BOOL  tmpHandler_bProcPcStatus(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 PC_STATUS_INFO		*	pInfo		=	(  PC_STATUS_INFO  *  )p1;
	 CDBVariant			*	pVarVals	=	(  CDBVariant  *  )p2;
	 int					index		=	0;
	 int					iCmd		=	0;
	 int					iStatus		=	0;

	 index  =  0;	MACRO_sqlUcb(  pVarVals[index],  pInfo->ucbOped  );
	 index  ++	;	MACRO_sqlLong(  pVarVals[index],  iCmd  );
	 index  ++	;

	 if  (  iCmd  ==  CONST_opCmd_viewRemoteDesktop  )  pInfo->ucbViewRemoteDesktop  =  TRUE;
	 else  if  (  iCmd  ==  CONST_opCmd_monDesktop  )  pInfo->ucbMonDesktop  =  TRUE;


	 return  TRUE;
}

//
 //
 __declspec(  dllexport  )  int  getPcStatusInfo(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  char  *  mac0,  QY_DMITEM  *  pFieldIdTable,  PC_STATUS_INFO  *  pInfo  )
{
	//  
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;

	 int			iErr	=	-1;
	 TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	 CDBVariant		varVals[5];

	 if  (  !bMacValid(  mac0  )  )  return  -1;

	 safeStrnCpy(  mac0,  pInfo->mac0,  sizeof(  pInfo->mac0  )  );

	 if  (  !g_dbFuncs.pf_bGetPcInfoByMacEx(  pDb,  mac0,  TRUE,  pFieldIdTable,  &pInfo->pcInfo,  &pInfo->regInfo,  NULL  )  )  goto  errLabel;

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyPcStatusTab.bOped,qyPcOpQTab.iCmd from (qyPcTab left join qyPcStatusTab on qyPcTab.mac0=qyPcStatusTab.mac0) left join qyPcOpQTab on (qyPcTab.mac0=qyPcOpQTab.mac0 and (qyPcOpQTab.iStatus=%d or qyPcOpQTab.iStatus=%d)) where qyPcTab.mac0='%s'"   ),  CONST_cmdStatus_start,  CONST_cmdStatus_restart,  CString(  pInfo->mac0  )  );
	 
	 traceLogA(  "sql is [%S]",  sqlBuf  );

	 bEnumSqlQuery(  pDb,  sqlBuf,  tmpHandler_bProcPcStatus,  0,  pInfo,  varVals,  mycountof(  varVals  )  );  

	 iErr  =  0;

errLabel:
	 return  iErr;
}



