
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"
#include	"qyWmComm.h"
#include	<iphlpapi.h>
#include	"qyCusResTemp.h"
#include	"myDb.h"
#include	"myresource.h"
#include	"qnmMainProc_nm.h"
#include	"pcCommType_defs.h"




 BOOL  bBhbViewLogFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	//  int						i;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpBhbLogQueryStruct  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_bhbLog;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	/*
	MACRO_getnItems(  pQueryStruct->pSql,  type,  tmpSel.u.query.nSqlFields  );
	if  (  tmpSel.u.query.nSqlFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields太大了"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.sqlColumns,  pQueryStruct->pSql,  (  tmpSel.u.query.nSqlFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	MACRO_getnItems(  pQueryStruct->pDisplay,  type,  tmpSel.u.query.nFields  );
	if  (  tmpSel.u.query.nFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.columns,  pQueryStruct->pDisplay,  (  tmpSel.u.query.nFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	*/
	if  (  setQueryColumns( pQyMc, 0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;

	// 
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  _T(  "from onlineComputerTab"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "onlineComputerTab.officeName"  )  );

	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	
	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  _T(  "在线主机列表"  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


  BOOL  bBhbViewOfflineLogFunc(  QY_MC  *  pQyMc,   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpBhbOfflineLogQueryStruct  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_bhbLog;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	/*
	MACRO_getnItems(  pQueryStruct->pSql,  type,  tmpSel.u.query.nSqlFields  );
	if  (  tmpSel.u.query.nSqlFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields太大了"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.sqlColumns,  pQueryStruct->pSql,  (  tmpSel.u.query.nSqlFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	MACRO_getnItems(  pQueryStruct->pDisplay,  type,  tmpSel.u.query.nFields  );
	if  (  tmpSel.u.query.nFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.columns,  pQueryStruct->pDisplay,  (  tmpSel.u.query.nFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	*/
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;

	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from offlineComputerLogTab"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "offlineComputerLogTab.officeName"  )  );

	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	
	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  _T(  "离线主机列表"  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}



 BOOL  bNetMcViewScannedIpListFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpScannedIpListQueryStruct  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcScannedIpList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	/*
	MACRO_getnItems(  pQueryStruct->pSql,  type,  tmpSel.u.query.nSqlFields  );
	if  (  tmpSel.u.query.nSqlFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields太大了"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.sqlColumns,  pQueryStruct->pSql,  (  tmpSel.u.query.nSqlFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	MACRO_getnItems(  pQueryStruct->pDisplay,  type,  tmpSel.u.query.nFields  );
	if  (  tmpSel.u.query.nFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.columns,  pQueryStruct->pDisplay,  (  tmpSel.u.query.nFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	*/
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
		
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from qnmScannedIpTab left join qyPcTab on qnmScannedIptab.tmpIp15=qyPcTab.ip"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qnmScannedIpTab.ip"  )  );

	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	
	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_qyScannedIpList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}

 int  letInScope(  QY_MC  *  pQyMc,  TCHAR  *  wherePart,  unsigned  int  cnt  )
{
	TCHAR		tBuf[CONST_maxSqlClauseLen  +  1]	=	_T(  ""  );
	CString		str, str1;
	TCHAR	*	pTab								=	_T(  "qyPcRegInfoTab"  );

	if  (  pQyMc->curUsrInfo.scope.bRestricted  )  {
		
		if  (  pQyMc->curUsrInfo.scope.zbStr[0]  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.col%d=%s"  ),  pTab,  getRegDbIndexByFieldId(  CONST_fieldId_zb  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  pQyMc->curUsrInfo.scope.zbStr  )  );
		if  (  pQyMc->curUsrInfo.scope.bbStr[0]  )  {
			if  (  tBuf[0]  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s and"  ),  tBuf  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s.col%d=%s"  ),  tBuf,  pTab,  getRegDbIndexByFieldId(  CONST_fieldId_bb  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  pQyMc->curUsrInfo.scope.bbStr  )  );
		}
		if  (  pQyMc->curUsrInfo.scope.dwStr[0]  )  {
			if  (  tBuf[0]  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s and"  ),  tBuf  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s.col%d=%s"  ),  tBuf,  pTab,  getRegDbIndexByFieldId(  CONST_fieldId_dw  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  pQyMc->curUsrInfo.scope.dwStr  )  );
		}
		if  (  pQyMc->curUsrInfo.scope.bmStr[0]  )  {
			if  (  tBuf[0]  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s and"  ),  tBuf  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s.col%d=%s"  ),  tBuf,  pTab,  getRegDbIndexByFieldId(  CONST_fieldId_bm  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  pQyMc->curUsrInfo.scope.bmStr  )  );
		}

		str  =  tBuf;

		//  还要把regInfo为空的情况加进去
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.col%d='' and %s.col%d='' and %s.col%d='' and %s.col%d=''"  ),  
														pTab,  getRegDbIndexByFieldId(  CONST_fieldId_zb  ),
														pTab,  getRegDbIndexByFieldId(  CONST_fieldId_bb  ),
														pTab,  getRegDbIndexByFieldId(  CONST_fieldId_dw  ),
														pTab,  getRegDbIndexByFieldId(  CONST_fieldId_bm  )  );			
		str1  =  tBuf;

		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.col%d is null"  ),  pTab,  getRegDbIndexByFieldId(  CONST_fieldId_bm  )  );
		
		tTrim(  wherePart  );
		if  (  wherePart[0]  )  _sntprintf(  wherePart,  cnt,  _T(  "%s and"  ),  wherePart  );
		_sntprintf(  wherePart,  cnt,  _T(  "%s ((%s) or (%s) or (%s))"  ),  wherePart,  str,  str1,  tBuf  );
	}
	return  0;
}


 int  letInScope_event(  QY_MC  *  pQyMc,  TCHAR  *  wherePart,  unsigned  int  cnt  )
{
	TCHAR		tBuf[CONST_maxSqlClauseLen  +  1]	=	_T(  ""  );
	CString		str, str1;
	TCHAR	*	pTab								=	_T(  "qyPcEventTab"  );

	if  (  pQyMc->curUsrInfo.scope.bRestricted  )  {
		
		if  (  pQyMc->curUsrInfo.scope.zbStr[0]  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.col%d=%s"  ),  pTab,  getEventDbIndexByFieldId(  CONST_fieldId_zb  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  pQyMc->curUsrInfo.scope.zbStr  )  );
		if  (  pQyMc->curUsrInfo.scope.bbStr[0]  )  {
			if  (  tBuf[0]  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s and"  ),  tBuf  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s.col%d=%s"  ),  tBuf,  pTab,  getEventDbIndexByFieldId(  CONST_fieldId_bb  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  pQyMc->curUsrInfo.scope.bbStr  )  );
		}
		if  (  pQyMc->curUsrInfo.scope.dwStr[0]  )  {
			if  (  tBuf[0]  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s and"  ),  tBuf  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s.col%d=%s"  ),  tBuf,  pTab,  getEventDbIndexByFieldId(  CONST_fieldId_dw  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  pQyMc->curUsrInfo.scope.dwStr  )  );
		}
		if  (  pQyMc->curUsrInfo.scope.bmStr[0]  )  {
			if  (  tBuf[0]  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s and"  ),  tBuf  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s.col%d=%s"  ),  tBuf,  pTab,  getEventDbIndexByFieldId(  CONST_fieldId_bm  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  pQyMc->curUsrInfo.scope.bmStr  )  );
		}

		str  =  tBuf;

		//  还要把regInfo为空的情况加进去
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.col%d='' and %s.col%d='' and %s.col%d='' and %s.col%d=''"  ),  
														pTab,  getEventDbIndexByFieldId(  CONST_fieldId_zb  ),
														pTab,  getEventDbIndexByFieldId(  CONST_fieldId_bb  ),
														pTab,  getEventDbIndexByFieldId(  CONST_fieldId_dw  ),
														pTab,  getEventDbIndexByFieldId(  CONST_fieldId_bm  )  );			
		str1  =  tBuf;

		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.col%d is null"  ),  pTab,  getEventDbIndexByFieldId(  CONST_fieldId_bm  )  );
		
		tTrim(  wherePart  );
		if  (  wherePart[0]  )  _sntprintf(  wherePart,  cnt,  _T(  "%s and"  ),  wherePart  );
		_sntprintf(  wherePart,  cnt,  _T(  "%s ((%s) or (%s) or (%s))"  ),  wherePart,  str,  str1,  tBuf  );
	}
	return  0;
}

 int  letInScope_opEvent(  QY_MC  *  pQyMc,  TCHAR  *  wherePart,  unsigned  int  cnt  )
{
	return  0;
}

 BOOL  bNetMcViewPcListFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  pQyMc->iSystemId  ==  CONST_qySystemId_netMc2  ?  CONST_resId_gpPcListQueryStruct_netMc2  :  CONST_resId_gpPcListQueryStruct  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcPcList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	
	//	
	if  (  setQueryColumns(  pQyMc,  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from (qyPcTab left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0) left join qyPcStatusTab on qyPcTab.mac0=qyPcStatusTab.mac0 "  )  );

	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  )  );
	letInScope(  pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  pQyMc->cfg.pGuiCfg->nSubMenuPos_pcList;		//  2003/12/17修改
	//
	tmpSel.u.query.ucbMultiSel				=  TRUE;															//  2008/10/25
	tmpSel.u.query.nSubMenuPos_multiSel		=  CONST_resId_popup_viewPcList_multiSel;							//  34
	tmpSel.u.query.nSubMenuPos_notSel		=	0;																//  2008/10/25	


	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ), getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyPcList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


 BOOL  bNetMcViewPcAssetListFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcAssetListQueryStruct  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcAssetList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	/*
	for  (  tmpSel.u.query.nSqlFields  =  0;  pQueryStruct->pSql[tmpSel.u.query.nSqlFields].type  !=  -1;  tmpSel.u.query.nSqlFields  ++  );
	//MACRO_getnItems(  pQueryStruct->pSql,  type,  tmpSel.u.query.nSqlFields  );
	if  (  tmpSel.u.query.nSqlFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.sqlColumns,  pQueryStruct->pSql,  (  tmpSel.u.query.nSqlFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	MACRO_getnItems(  pQueryStruct->pDisplay,  type,  tmpSel.u.query.nFields  );
	if  (  tmpSel.u.query.nFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.columns,  pQueryStruct->pDisplay,  (  tmpSel.u.query.nFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	*/
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from (qyPcAssetTab left join qyPcRegInfoTab on qyPcAssetTab.mac0=qyPcRegInfoTab.mac0) left join qyPcTab on qyPcAssetTab.mac0=qyPcTab.mac0"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  )  );

	letInScope(  pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col2,qyPcRegInfoTab.col3,qyPcRegInfoTab.col4,qyPcTab.ip,qyPcAssetTab.iType"  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	//  tmpSel.u.query.nSubMenuPos  =  pQyMc->cfg.pGuiCfg->nSubMenuPos_pcList;		//  2003/12/17修改

	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_assetList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


 //  2004/05/14添加
 BOOL  bNetMcViewPcSpListFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet			=	FALSE;
	//QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp			=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcSpListQueryStruct  );
	char					sqlBuf[CONST_qyMaxSqlBufLen  +  1]	=	"";

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcPcSpList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	/*
	for  (  tmpSel.u.query.nSqlFields  =  0;  pQueryStruct->pSql[tmpSel.u.query.nSqlFields].type  !=  -1;  tmpSel.u.query.nSqlFields  ++  );
	//MACRO_getnItems(  pQueryStruct->pSql,  type,  tmpSel.u.query.nSqlFields  );
	if  (  tmpSel.u.query.nSqlFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.sqlColumns,  pQueryStruct->pSql,  (  tmpSel.u.query.nSqlFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	MACRO_getnItems(  pQueryStruct->pDisplay,  type,  tmpSel.u.query.nFields  );
	if  (  tmpSel.u.query.nFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.columns,  pQueryStruct->pDisplay,  (  tmpSel.u.query.nFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	*/
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from ((qyPcTab left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0) left join qyPcSpTab on (qyPcTab.mac0=qyPcSpTab.mac0 )) left join qyCusNameTab on (qyPcSpTab.spName=qyCusNameTab.objName0)"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "(qyCusNameTab.iType=%d or qyCusNameTab.iType is null)"  ),  CONST_cusNameType_pcSp  );
	if  (  wherePart[0]  )  _sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and %s"  ),  CString(  tmpSel.u.query.wherePart  ),  CString(  wherePart  )  );

	letInScope(  pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  19;				

	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_patchList )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


 /*
 BOOL  bNetMcViewUnchkedPcList(  )
{
	BOOL					bRet	=	FALSE;
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	int						i;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	gpUnchkedPcListQueryStruct;
	
	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcPcList;
	//
	//
	if  (  setQueryColumns(  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from (qyPcRuleTab left join qyPcTab on qyPcRuleTab.mac0=qyPcTab.mac0) left join qyPcRegInfoTab on qyPcRuleTab.mac0=qyPcRegInfoTab.mac0"  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRuleTab.bUnchked='1'"  );
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  pQueryStruct->pSql[0].label  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  5;

	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  ""    );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  _T(  "免干扰计算机列表"  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}
*/

/*
 BOOL  bNetMcViewWillAttackPcList(  )
{
	BOOL					bRet	=	FALSE;
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	int						i;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	gpWillAttackPcListQueryStruct;
	
	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcPcList;
	//
	//
	if  (  setQueryColumns(  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from (qyPcRuleTab left join qyPcTab on qyPcRuleTab.mac0=qyPcTab.mac0) left join qyPcRegInfoTab on qyPcRuleTab.mac0=qyPcRegInfoTab.mac0"  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRuleTab.bWillAttack='1'"  );
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  pQueryStruct->pSql[0].label  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  6;

	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  ""    );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  _T(  "阻断计算机列表"  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}
*/


BOOL  bViewPcUsrList_netMc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  );
BOOL  bViewPcUsrInTab1List_netMc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  );
//
BOOL  bViewMessengerRegInfoInTab1List(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  );



BOOL  bViewObjRegInfoList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	//QY_MC  *  pQyMc		=	QY_GET_GBUF(  );

	switch  (  pObjDb->cfg.iSystemId  )  {
		case  CONST_qySystemId_messenger:
			  return  bViewMessengerRegInfoList(  pQyMc,  pObjDb  );
		default:
				break;
	}
	return  bViewPcUsrList_netMc(  pQyMc,  pObjDb  );
}


 BOOL  bViewObjRegInfoInTab1List(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	//QY_MC  *  pQyMc		=	QY_GET_GBUF(  );

	switch  (  pObjDb->cfg.iSystemId  )  {
		case  CONST_qySystemId_messenger:
			  return  bViewMessengerRegInfoInTab1List(  pQyMc,  pObjDb  );
		default:
				break;
	}
	return  bViewPcUsrInTab1List_netMc(  pQyMc,  pObjDb  );

}


 BOOL  bViewPcUsrList_netMc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcUsrListQueryStruct  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcPcList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
													//				0					1					2		  3			 4					5			6			7				8
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from qyPcRegInfoTab left join qyPcTab on qyPcRegInfoTab.mac0=qyPcTab.mac0 "  )  );
	
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  ""  )  );
	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  2;


	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_userInfoList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


 BOOL  bViewPcUsrInTab1List_netMc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcUsrInTab1ListQueryStruct  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcPcList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	/*
	MACRO_getnItems(  pQueryStruct->pSql,  type,  tmpSel.u.query.nSqlFields  );
	if  (  tmpSel.u.query.nSqlFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.sqlColumns,  pQueryStruct->pSql,  (  tmpSel.u.query.nSqlFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	MACRO_getnItems(  pQueryStruct->pDisplay,  type,  tmpSel.u.query.nFields  );
	if  (  tmpSel.u.query.nFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.columns,  pQueryStruct->pDisplay,  (  tmpSel.u.query.nFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	*/
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
													//				0					1					2		  3			 4					5			6			7				8
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from qyPcRegInfoTab1 left join qyPcTab on qyPcRegInfoTab1.mac0=qyPcTab.mac0 "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  ""  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab1.col0"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  7;


	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyPcUsrInTab1List  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}

 	 
 BOOL  bViewClientList_netMc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpClientListQueryStruct_netMc  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_clientList_netMc;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;

	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (qyPcTab left join qyPcRegInfoTab on qyPcRegInfoTab.mac0=qyPcTab.mac0) left join qwmSvrTab on qyPcTab.mac0=qwmSvrTab.mac0 "  )  );
	
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  ""  )  );
	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  0;


	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyClientList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}

 BOOL  bViewClientList_is(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpClientListQueryStruct_is  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_clientList_is;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;

	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  " from (qyImObjTab as A left join qyImObjRegInfoTab as B on (A.misServName=B.misServName and A.idStr=B.idStr)) "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "A.uiType not in(%d)"  ),  CONST_objType_imGrp  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "B.col0"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  0;


	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyClientList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


 BOOL  bViewClientList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	if  (  !pObjDb  )  return  FALSE;

	switch  (  qyGetServiceId(  pObjDb->cfg.iSystemId  )  )  {
			case  CONST_qyServiceId_netMc:
				  return  bViewClientList_netMc(  pQyMc,  pObjDb  );
			case  CONST_qyServiceId_is:
				  return  bViewClientList_is(  pQyMc,  pObjDb  );
			default:
					break;
	}

	return  FALSE;
	
}


 BOOL  bNetMcViewPcSecChkEventList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause1  )
{
	BOOL					bRet					=	FALSE;
	//  CQyMcApp			*	pApp					=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	//QY_MC				*	pQyMc					=	QY_GET_GBUF(  );
	QNM_QUERY_STRUCT	*	pQueryStruct			=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcSecChkEventAllQueryStruct  );
	QY_DMITEM			*	pItem					=	(  QY_DMITEM  *  )getResTable(  0,  &g_pQyMc->cusRes,  CONST_resId_secChkEventTypeTable  );
	TCHAR					whereClause[1024]		=	_T(  ""  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	if  (  pItem  &&  pItem->type  !=  -1  )  {
		 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "eventType in (%d"  ),  pItem->type  );
		 pItem  ++  ;
		 for  (  ;  pItem->type  !=  -1;  pItem  ++  )  {
			  _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s,%d"  ),  whereClause,  pItem->type  );
		 }
		 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s)"  ),  whereClause  );
	}
	tTrim(  whereClause  );
	
	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcSecChkEventList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;

	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (qyPcTab left join qyPcRegInfoTab on qyPcRegInfoTab.mac0=qyPcTab.mac0) left join qyPcSecChkEventTab on qyPcTab.mac0=qyPcSecChkEventTab.mac0 "  )  );
	//
	if  (  whereClause1  )  _sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  whereClause1  );
	tTrim(  tmpSel.u.query.wherePart  );
	if  (  tmpSel.u.query.wherePart[0]  &&  whereClause[0]  )  _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s and "  ),  tmpSel.u.query.wherePart  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s %s"  ),  tmpSel.u.query.wherePart,  whereClause  );
	tTrim(  tmpSel.u.query.wherePart  );

	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );
	//
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  29;

	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pcSecChkEventList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


/////////////////////////////////////////////

 BOOL  bNetMcViewPcRuleList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  int  pcListIndex  )
{
	BOOL					bRet			=	FALSE;
	//  CQyMcApp			*	pApp			=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	//QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	int						iResId			=	pcListIndex  ?  CONST_resId_gpPcRuleListQueryStruct1  :  CONST_resId_gpPcRuleListQueryStruct0;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  iResId  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcPcList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
													//				0					1					2		  3			 4					5			6			7				8
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (qyPcRuleTab left join qyPcTab on qyPcTab.mac0=qyPcRuleTab.mac0) left join qyPcRegInfoTab on qyPcRuleTab.mac0=qyPcRegInfoTab.mac0 "  )  );
	
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  ""  )  );
	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  3;


	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pcRuleList2  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


 BOOL  bNetMcViewPcNetworkListFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  QNM_QUERY_STRUCT  *  pQueryStruct,  unsigned  int  uiType,  unsigned  char  ucbRule,  LPCTSTR  title,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	//  QNM_QUERY_STRUCT	*	pQueryStruct	=	gpPcAdapterListQueryStruct;
	//  unsigned  int			uiType			=	CONST_pcNetworkPropType_adapter;

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcPcList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
													//				0					1					2		  3			 4					5			6			7				8
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (qyPcAdapterTab left join qyPcTab on (qyPcTab.mac0=qyPcAdapterTab.mac0)) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  " qyPcAdapterTab.uiType=%d and %s"  ),  uiType,  CString (  ucbRule  ?  "qyPcAdapterTab.ucbRule='1'"  :  "qyPcAdapterTab.ucbRule<>'1'"  )  );
	if  (  wherePart  &&  wherePart[0]  )  _sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and %s"  ),  CString(  tmpSel.u.query.wherePart  ),  CString(  wherePart  )  );

	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );


	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  ); 
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  28;
	tmpSel.u.query.uiDefaultCmd			=  ID_qyProp_pcNetwork;


	//  _sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  _T(  "计算机网络配置的状态列表"  );
	if  (  title  )  _sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  title  );  
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


 BOOL  bNetMcViewPcNetworkPropList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	 return  bNetMcViewPcNetworkListFunc(  pQyMc,  pObjDb,  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcAdapterListQueryStruct  ),  CONST_pcNetworkPropType_adapter,  FALSE,  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcNetworkPropList  ),  wherePart  );
}

 BOOL  bNetMcViewPcNetworkRuleList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	 return  bNetMcViewPcNetworkListFunc(  pQyMc,  pObjDb,  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcAdapterListQueryStruct  ),  CONST_pcNetworkPropType_adapter,  TRUE,  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcNetworkRuleList2  ),  wherePart  );
}


 BOOL  bNetMcViewPcProxyCfgPropList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	 return  bNetMcViewPcNetworkListFunc(  pQyMc,  pObjDb,  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcProxyCfgListQueryStruct  ),  CONST_pcNetworkPropType_proxy,  FALSE,  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcProxyCfgPropList2  ),  wherePart  );
}


 BOOL  bNetMcViewPcProxyCfgRuleList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	 return  bNetMcViewPcNetworkListFunc(  pQyMc,  pObjDb,  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcProxyCfgListQueryStruct  ),  CONST_pcNetworkPropType_proxy,  TRUE,  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcProxyCfgRuleList2  ),  wherePart  );
}

#if  0
 BOOL  bNetMcViewPcComputerPropList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	 return  bNetMcViewPcNetworkListFunc(  pObjDb,  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcComputerPropListQueryStruct  ),  CONST_pcNetworkPropType_computer,  FALSE,  getResStr(  0, &g_pQyMc->cusRes,  CONST_resId_pcComputerPropList2 ),  wherePart  );
}

 BOOL  bNetMcViewPcComputerRuleList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	 return  bNetMcViewPcNetworkListFunc(  pObjDb,  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcComputerRuleListQueryStruct  ),  CONST_pcNetworkPropType_computer,  TRUE,  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcComputerRuleList2  ),  wherePart  );
}
#endif

 BOOL  bNetMcViewPcWindowsUpdatePolicyPropList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	 return  bNetMcViewPcNetworkListFunc(  pQyMc,  pObjDb,  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcWindowsUpdatePolicyListQueryStruct  ),  CONST_pcCommType_windowsUpdatePolicy,  FALSE,  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcWindowsUpdatePolicyPropList  ),  wherePart  );
}


 BOOL  bNetMcViewPcWindowsUpdatePolicyRuleList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	 CString	str;
	 if  (  wherePart  )  str  =  CString(  wherePart  );
	 MACRO_CStringTrim(  str  );
	 //  if  (  str.GetLength(  )  )  str  +=  CString(  " and "  );
	 //  str  +=  CString(  "qyPcAdapterTab.mac0<>'"  )  +  CONST_qyNullMac  +  "'";

	 return  bNetMcViewPcNetworkListFunc(  pQyMc,  pObjDb,  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcWindowsUpdatePolicyListQueryStruct  ),  CONST_pcCommType_windowsUpdatePolicy,  TRUE,  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcWindowsUpdatePolicyRuleList  ),  str  );
}


 BOOL  bNetMcViewPcPrinterPropList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcPrinterPropListQueryStruct  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcPrinterList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
													//				0					1					2		  3			 4					5			6			7				8
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (qyPcPrinterTab left join qyPcTab on (qyPcTab.mac0=qyPcPrinterTab.mac0)) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  ?  wherePart  :  _T(  ""  )  )  );

	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  ); 
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  29;
	tmpSel.u.query.uiDefaultCmd			=  0;


	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcPrinterPropList2  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}


 BOOL  bNetMcViewPcRegistryPropList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{	 
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcRegistryListQueryStruct  );
	CString					whereStr;

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcRegistryList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (( qyPcRegistryValTab left join qyPcRegistryRuleTab on qyPcRegistryValTab.iRuleId=qyPcRegistryRuleTab.id) left join qyPcRegistryKnowledgeTab on (qyPcRegistryValTab.iRootKey=qyPcRegistryKnowledgetab.iRootKey and qyPcRegistryValTab.subKey=qyPcRegistryKnowledgeTab.subKey and qyPcRegistryValTab.cfgName=qyPcRegistryKnowledgeTab.cfgName)) left join (qyPcTab left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0) on qyPcTab.mac0=qyPcRegistryValTab.mac0  "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s qyPcRegistryValTab.uiType=%d   "  ),  tmpSel.u.query.wherePart,  CONST_pcCommType_registryVal  );
	if  (  wherePart  )  whereStr  =  CString(  wherePart  );
	MACRO_CStringTrim(  whereStr  );
	if  (  whereStr.GetLength(  )  )  _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s and (%s)"  ),  tmpSel.u.query.wherePart,  whereStr  );

	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  ); 
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  33;
	tmpSel.u.query.uiDefaultCmd			=  0;


	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcRegistryList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


 BOOL  bNetMcViewPcRegistryRuleStatusList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcRegistryRuleStatusListQueryStruct  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcRegistryList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from ( ( qyPcRegistryValTab left join qyPcRegistryRuleTab on qyPcRegistryValTab.iRuleId=qyPcRegistryRuleTab.id ) left join qyPcTab on (qyPcTab.mac0=qyPcRegistryValTab.mac0)) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  ?  wherePart  :  _T(  ""  )  )  );
	tTrim(  tmpSel.u.query.wherePart  );
	if  (  tmpSel.u.query.wherePart[0]  )  _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s and"  ),  tmpSel.u.query.wherePart  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s qyPcRegistryValTab.uiType<>%d"  ),  tmpSel.u.query.wherePart,  CONST_pcCommType_registryVal  );

	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  ); 
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  29;
	tmpSel.u.query.uiDefaultCmd			=  0;


	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcRegistryRuleStatusList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
}


 BOOL  bNetMcViewPcEventLogList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{	 
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcEventLogListQueryStruct  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcEventLogList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (qyPcEventLogTab left join qyPcTab on (qyPcTab.mac0=qyPcEventLogTab.mac0)) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  ?  wherePart  :  _T(  ""  )  )  );

	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  ); 
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  29;
	tmpSel.u.query.uiDefaultCmd			=  0;


	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcEventLogList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


 BOOL  bNetMcViewPcOsUsrList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{	 
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpPcOsUsrListQueryStruct  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcOsUsrList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (qyPcOsUsrTab left join qyPcTab on (qyPcTab.mac0=qyPcOsUsrTab.mac0)) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  ?  wherePart  :  _T(  ""  )  )  );

	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  ); 
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  29;
	tmpSel.u.query.uiDefaultCmd			=  0;


	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcOsUsrList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


	
 BOOL  bNetMcViewPcNetStatList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{	 
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcNetStatListQueryStruct  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcNetStatList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (qyPcNetStatTab left join qyPcTab on (qyPcTab.mac0=qyPcNetStatTab.mac0)) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  ?  wherePart  :  _T(  ""  )  )  );

	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  ); 
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  29;
	tmpSel.u.query.uiDefaultCmd			=  0;


	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_qyPcNetStatList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


 BOOL  bNetMcViewPcProcessPropList( QY_MC  *  pQyMc, QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{	 
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpPcProcessPropListQueryStruct  );
	CString					str;
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcProcessList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from ((qyPcProcessTab left join qyPcProcessKnowledgeTab on (qyPcProcessTab.myModulePath=qyPcProcessKnowledgeTab.fileName and (qyPcProcessTab.cmdLine=qyPcProcessKnowledgeTab.cmdLine or (qyPcProcesstab.cmdLine<>'' and qyPcProcessKnowledgeTab.cmdLine='')))) left join qyPcTab on ( qyPcTab.mac0=qyPcProcessTab.mac0)) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "qyPcProcessTab.uiType=%d and (qyPcProcessKnowledgeTab.cmdLine is null or not (qyPcProcessTab.cmdLine<>'' and qyPcProcessKnowledgeTab.cmdLine='' and exists( select C.id from qyPcProcessKnowledgeTab as C where  C.fileName=qyPcProcessTab.myModulePath and C.cmdLine=qyPcProcessTab.cmdLine )))"  ),  CONST_pcCommType_process );
	if  (  wherePart  &&  wherePart[0]  )  str  =  CString(  wherePart  );
	MACRO_CStringTrim(  str  );
	if  (  str.GetLength(  )  )  _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s and (%s)"  ),  tmpSel.u.query.wherePart,  str  );		//  200604/23, on里的数据，仅用于限制左联结的数据，并不用来过滤整个数据集。所以，不能用on来过滤左边的数据

	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  ); 
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  30;
	tmpSel.u.query.uiDefaultCmd			=  0;


	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcProcessPropList2  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );
  

errLabel:

	return  bRet;
	
}


 BOOL  bNetMcViewPcProcessModulePropList( QY_MC  *  pQyMc, QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{	 
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcProcessModulePropListQueryStruct  );
	CString					str;

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcProcessModuleList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from ( (( qyPcProcessTab as A left join qyPcProcessTab as B on ( B.uiType=%d and A.mac0=B.mac0 and A.uiLangId=B.uiLangId and A.iPlatformId=B.iPlatformId and A.winDir=B.winDir and A.dwPid=B.dwPid )) left join qyPcProcessKnowledgeTab on ( B.myModulePath=qyPcProcessKnowledgeTab.fileName and B.cmdLine=qyPcProcessKnowledgeTab.cmdLine) ) left join qyPcTab on (qyPcTab.mac0=A.mac0) ) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 "  ),  CONST_pcCommType_processModule  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "A.uiType=%d"  ),  CONST_pcCommType_process );
	if  (  wherePart  &&  wherePart[0]  )  str  =  CString(  wherePart  );
	MACRO_CStringTrim(  str  );
	if  (  str.GetLength(  )  )  _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s and (%s)"  ),  tmpSel.u.query.wherePart,  str  );		//  200604/23, on里的数据，仅用于限制左联结的数据，并不用来过滤整个数据集。所以，不能用on来过滤左边的数据

	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  ); 
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  30;
	tmpSel.u.query.uiDefaultCmd			=  0;


	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcProcessModulePropList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );
  

errLabel:

	return  bRet;
	
}


 BOOL  bNetMcViewPcProcessRuleList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )	
{
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpPcProcessRuleListQueryStruct  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcProcessRuleList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (qyPcProcessRuleTab left join qyPcTab on (qyPcTab.mac0=qyPcProcessRuleTab.mac0)) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  ?  wherePart  :  _T(  ""  )  )  );

	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  ); 
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  29;
	tmpSel.u.query.uiDefaultCmd			=  0;

	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0, &g_pQyMc->cusRes,  CONST_resId_pcProcessRuleList2  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );
  

errLabel:

	return  bRet;

}

 BOOL  bNetMcViewPcNetFlowPropList_ethernet(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	 CString	str;
	 TCHAR		tBuf[128];

	 if  (  wherePart  )  str  =  CString(  wherePart  );
	 MACRO_CStringTrim(  str  );
	 if  (  str.GetLength(  )  )  str  =  str  +  CString(  " and "  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qyPcNetFlowTab.dwType=%d"  ),  MIB_IF_TYPE_ETHERNET  ); 
	 str  +=  tBuf;
	 return  bNetMcViewPcNetFlowPropList(  pQyMc,  pObjDb,  str  );
}

 //
 BOOL  bNetMcViewPcNetFlowPropList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpPcNetFlowListQueryStruct  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcNetFlowList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from ((qyPcNetFlowTab left join qyPcAdapterTab on ( qyPcAdapterTab.uiType=%d and qyPcAdapterTab.ucbRule<>'1' and qyPcNetFlowTab.mac0=qyPcAdapterTab.mac0 and qyPcNetFlowTab.bPhysAddr=qyPcAdapterTab.mac) ) left join qyPcTab on (qyPcTab.mac0=qyPcNetFlowTab.mac0)) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 "  ),  CONST_pcCommType_adapter  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  ?  wherePart  :  _T(  ""  )  )  );

	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  ); 
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  29;
	tmpSel.u.query.uiDefaultCmd			=  0;

	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcNetFlowPropList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );
  

errLabel:

	return  bRet;

}


 BOOL  bNetMcViewPcNetSharePropList(  QY_MC  *pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcNetShareListQueryStruct  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcNetShareList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns( pQyMc, 0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (qyPcNetShareTab left join qyPcTab on (qyPcTab.mac0=qyPcNetShareTab.mac0)) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  ?  wherePart  :  _T(  ""  )  )  );

	letInScope(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  ); 
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  29;
	tmpSel.u.query.uiDefaultCmd			=  0;

	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_pcNetSharePropList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );
  

errLabel:

	return  bRet;

}

 ///////

 BOOL  bNetMcCfgPcProcessKnowledge(  QY_MC  *  pQyMc,  LPCTSTR  wherePart  )	
{
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcProcessKnowledgeListQueryStruct  );
	
	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcProcessKnowledgeList;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from qyPcProcessKnowledgeTab"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  ?  wherePart  :  _T(  ""  )  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcProcessKnowledgeTab.fileName"  )  ); 
	
	tmpSel.u.query.data2DisplayProc				=  displayQnmElement;
	tmpSel.u.query.pfProcEvent					=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId					=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos					=  CONST_resId_popup_cfgPcModuleKnowlege;
	tmpSel.u.query.nSubMenuPos_notSel		=  CONST_resId_popup_cfgPcModuleKnowlege_notSel;		//
	tmpSel.u.query.uiDefaultCmd					=  ID_qyProp_pcModuleKnowlege;

	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_qyCfgModuleInfo  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );
  

errLabel:

	return  bRet;

}


 BOOL  bNetMcCfgPcRegistryKnowledge(  QY_MC  *  pQyMc,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcRegistryKnowledgeListQueryStruct  );
	
	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcRegistryKnowledgeList;

	if  (  setQueryColumns( pQyMc, 0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from qyPcRegistryKnowledgeTab"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  wherePart  ?  wherePart  :  _T(  ""  )  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegistryKnowledgeTab.iRootKey,qyPcRegistryKnowLedgeTab.subKey,qyPcRegistryKnowledgeTab.cfgName"  )  ); 
	
	tmpSel.u.query.data2DisplayProc				=  displayQnmElement;
	tmpSel.u.query.pfProcEvent					=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId					=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos					=  CONST_resId_popup_cfgPcModuleKnowlege;
	tmpSel.u.query.nSubMenuPos_notSel			=  CONST_resId_popup_cfgPcModuleKnowlege_notSel;		//
	tmpSel.u.query.uiDefaultCmd					=  ID_qyProp_pcModuleKnowlege;

	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &g_pQyMc->cusRes,  CONST_resId_registryKnowledge  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );
  

errLabel:

	return  bRet;

}



 ///////
#if  0
 BOOL  bNetMcViewPcAutoLogonList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )	
{
	BOOL					bRet	=	FALSE;
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcAutoLogonListQueryStruct  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_pcAutoLogonList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (autoLogonTab left join qyPcTab on (qyPcTab.mac0=autoLogonTab.mac0)) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "autoLogonTab.mac0<>''"  )  );
	if  (  wherePart  &&  wherePart[0]  )  {
		_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and %s"  ),  tmpSel.u.query.wherePart,  wherePart  );
	}
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  ); 
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  29;
	tmpSel.u.query.uiDefaultCmd			=  0;

	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  _T(  "自动登录用户列表"  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );
  

errLabel:

	return  bRet;

}
#endif

 //
 ///////////////////////////////////////////////

 BOOL  bNetMcViewNetDevConnListFunc_unusedConn(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  )
{
	return  bNetMcViewNetDevConnListFunc(  pQyMc,  pObjDb,  CONST_qyQueryType_unusedConn,  docName,  whereClause  );
}


  //  查询网络设备联接的函数
  BOOL  bNetMcViewNetDevConnListFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  int  iQueryType,  LPCTSTR  docName,  LPCTSTR  whereClause  )
{	 
	BOOL					bRet			=	FALSE;
	//QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp			=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpNetDevConnListQueryStruct  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	iQueryType;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	/*
	MACRO_getnItems(  pQueryStruct->pSql,  type,  tmpSel.u.query.nSqlFields  );
	if  (  tmpSel.u.query.nSqlFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.sqlColumns,  pQueryStruct->pSql,  (  tmpSel.u.query.nSqlFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	MACRO_getnItems(  pQueryStruct->pDisplay,  type,  tmpSel.u.query.nFields  );
	if  (  tmpSel.u.query.nFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.columns,  pQueryStruct->pDisplay,  (  tmpSel.u.query.nFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	*/
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from (qySwitchConnectedPcTab left join qySwitchPortTab on (qySwitchConnectedPcTab.switchMac=qySwitchPortTab.switchMac and qySwitchConnectedPcTab.portIfIndex=qySwitchPortTab.portIfIndex)) left join qySnmpObjTab on qySwitchConnectedPcTab.switchMac=qySnmpObjTab.mac"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "qySwitchConnectedPcTab.portIfIndex is not null %s ( %s )"  ),  CString(  whereClause[0]  ?  "and"  :  ""  ),  CString(  whereClause  )  );
	if  (  iQueryType  ==  CONST_qyQueryType_unusedConn  )  _sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  "qySwitchConnectedPcTab.lastTime"  )  );
	else  _sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  "qySnmpObjTab.productName"  )  );
	
	tmpSel.u.query.data2DisplayProc		=	displayQnmElement;
	tmpSel.u.query.pfProcEvent			=	netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=	IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=	14;
	tmpSel.u.query.uiDefaultCmd			=	ID_qyProperties_viewNetDevConn;
	
	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_connDevice  )  );

	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}


 
 //  查询产生临时表的函数
 BOOL  bNetMcViewSearchListFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  int  iQueryType,  LPCTSTR  docName,  LPCTSTR  whereClause  )
{	 
	BOOL					bRet			=	FALSE;
	//QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp			=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpSearchListQueryStruct  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	iQueryType; 
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	/*
	MACRO_getnItems(  pQueryStruct->pSql,  type,  tmpSel.u.query.nSqlFields  );
	if  (  tmpSel.u.query.nSqlFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.sqlColumns,  pQueryStruct->pSql,  (  tmpSel.u.query.nSqlFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	MACRO_getnItems(  pQueryStruct->pDisplay,  type,  tmpSel.u.query.nFields  );
	if  (  tmpSel.u.query.nFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.columns,  pQueryStruct->pDisplay,  (  tmpSel.u.query.nFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	*/
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from qnmTmpTab"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  whereClause  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  "qnmTmpTab.mac"  )  );
	
	tmpSel.u.query.data2DisplayProc		=	displayQnmElement;
	tmpSel.u.query.pfProcEvent			=	netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=	IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=	pQyMc->cfg.pGuiCfg->nSubMenuPos_searchList;		//  2003/12/17修改
	tmpSel.u.query.uiDefaultCmd			=	ID_qyProperties;
	
	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_searchList  )  );

	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}


  //  查应用系统事件的函数
 BOOL  bViewOpEventListFunc_netMc( QY_MC  *  pQyMc, QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause )
{	 
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpOpEventListQueryStruct_netMc  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_opEventList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from qyPcEventTab"  )  );
	
	//  _sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  ""  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  whereClause  )  );
	letInScope_opEvent(  pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcEventTab.cntEventTime desc"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	//  tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	//  tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	//  tmpSel.u.query.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->nSubMenuPos_eventList;

	
	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_logList  )  );

	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}

 BOOL  bViewOpEventListFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause )
{
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );

	switch  (  pQyMc->iServiceId  )  {
			case  CONST_qyServiceId_netMc:
				  return  bViewOpEventListFunc_netMc(  pQyMc,  pObjDb,  docName,  whereClause  );
			case  CONST_qyServiceId_is:
				  return  bViewOpEventListFunc_is(  pQyMc,  pObjDb,  docName,  whereClause  );
			default:
					break;
	}

	return  bRet;

}



 //  查计算机事件的函数
 BOOL  bViewPcEventListFunc_netMc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause )
{	 
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcEventAllQueryStruct  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	//  2003/12/04修改
	//  if  (  qyGetSystemId(  )  ==  CONST_qySystemId_secChk  )  pQueryStruct  =  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpSecChkEventAllQueryStruct  );

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcEventList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from qyPcEventTab left join qyPcRegInfoTab on qyPcEventTab.mac0=qyPcRegInfoTab.mac0"  )  );
	
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  whereClause  )  );
	letInScope_event(  pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );


	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcEventTab.cntEventTime desc"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->nSubMenuPos_eventList;

	
	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  " %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_logList  )  );

	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}

  //  2013/02/20
 __declspec(  dllexport  )  BOOL  bViewImObjRuleList_is(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	BOOL					bRet			=	FALSE;
#if  0
	CQyMcApp			*	pApp			=	(  CQyMcApp  *  )AfxGetApp(  );
#endif
	QY_MC_SEL				tmpSel;
	//QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	int						iResId			=	(  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_gpImObjRuleListQueryStruct_isClient  :  CONST_resId_gpImObjRuleListQueryStruct_isMgr;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  iResId  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_imObjRuleList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	if  (  setQueryColumns( pQyMc, 0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;

	//
	if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
		_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  " from (qyImObjRuleTab as A left join qyImObjRegInfoTab as B on (A.misServName=B.misServName and A.idStr_related=B.idStr)) "  )  );
		_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "B.col0"  )  );
		}
	else  {
		  _sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  " from (qyImObjRuleTab as A left join qyImObjRegInfoTab as B on (A.misServName=B.misServName and A.idStr=B.idStr)) "  )  );
		  _sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "B.col0"  )  );
	}
	
	//
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.pfProcEvent_new		=  is_procEvent_new;
	if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
		tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
		tmpSel.u.query.nSubMenuPos			=  CONST_resId_popup_viewImObjRuleList_isClient;
	}


	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_imObjRuleList  )  );
#if  0
	bRet  =  pApp->bNewQueryView(  &tmpSel  );
#endif
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}

 //  2013/02/20
 BOOL  bViewEventListFunc_is(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause )
{	 
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
#if 0
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
#endif
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpEventListQueryStruct_is  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	//  2003/12/04修改
	//  if  (  qyGetSystemId(  )  ==  CONST_qySystemId_secChk  )  pQueryStruct  =  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpSecChkEventAllQueryStruct  );

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_imEventList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from qyImEventTab left join qyImObjRegInfoTab as B on (qyImEventTab.misServName=B.misServName and qyImEventTab.idStr=B.idStr)"  )  );
	//  _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  ""  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s"  ),  CQyString(  whereClause  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImEventTab.cntEventTime desc"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.pfProcEvent_new		=  is_procEvent_new;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->nSubMenuPos_eventList;

	
	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  " %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_logList  )  );
#if  0
	bRet  =  pApp->bNewQueryView(  &tmpSel  );
#endif
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}

 //  查应用系统事件的函数
 BOOL  bViewOpEventListFunc_is(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause )
{	 
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
#if  0
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
#endif
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpOpEventListQueryStruct_is  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_opEventList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from qyImEventTab"  )  );
	//  _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  ""  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s"  ),  CQyString(  whereClause  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImEventTab.cntEventTime desc"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	//  tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	//  tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	//  tmpSel.u.query.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->nSubMenuPos_eventList;

	
	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_logList  )  );
#if  0
	bRet  =  pApp->bNewQueryView(  &tmpSel  );
#endif
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}


 //  查网络设备事件的函数
 BOOL  bNetMcViewNetDevEventListFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause )
{	 
	BOOL					bRet			=	FALSE;
	//QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp			=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpNetDevEventAllQueryStruct  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_netDevEventList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	/*
	MACRO_getnItems(  pQueryStruct->pSql,  type,  tmpSel.u.query.nSqlFields  );
	if  (  tmpSel.u.query.nSqlFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.sqlColumns,  pQueryStruct->pSql,  (  tmpSel.u.query.nSqlFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	MACRO_getnItems(  pQueryStruct->pDisplay,  type,  tmpSel.u.query.nFields  );
	if  (  tmpSel.u.query.nFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.columns,  pQueryStruct->pDisplay,  (  tmpSel.u.query.nFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	*/
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from qyPcEventTab left join qyPcRegInfoTab on qyPcEventTab.mac0=qyPcRegInfoTab.mac0"  )  );
	//  _sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  ""  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  whereClause  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qyPcEventTab.cntEventTime desc"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->nSubMenuPos_netDevEventList;
	
	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  " %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_logList  )  );

	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}


 //  查询拨号事件的函数
 BOOL  bNetMcViewRasEventListFunc( QY_MC  *  pQyMc, QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause )
{	 
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcRasEventQueryStruct  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcEventList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	/*
	MACRO_getnItems(  pQueryStruct->pSql,  type,  tmpSel.u.query.nSqlFields  );
	if  (  tmpSel.u.query.nSqlFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.sqlColumns,  pQueryStruct->pSql,  (  tmpSel.u.query.nSqlFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	MACRO_getnItems(  pQueryStruct->pDisplay,  type,  tmpSel.u.query.nFields  );
	if  (  tmpSel.u.query.nFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.columns,  pQueryStruct->pDisplay,  (  tmpSel.u.query.nFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	*/
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from qyPcEventTab"  )  );
	//  _sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  ""  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  whereClause  )  );

	letInScope_event(  g_pQyMc,  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  )  );

	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "cntEventTime desc"  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	
	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_dialUpLogList  )  );

	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}


 //  显示统计信息
 BOOL  bNetMcStatScannedIpFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause,  LPCTSTR  groupClause,  LPCTSTR  havingClause,  QNM_QUERY_STRUCT  *  pQueryStruct  )
{	 
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcPcList;
	/*
	MACRO_getnItems(  pQueryStruct->pSql,  type,  tmpSel.u.query.nSqlFields  );
	if  (  tmpSel.u.query.nSqlFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.sqlColumns,  pQueryStruct->pSql,  (  tmpSel.u.query.nSqlFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	MACRO_getnItems(  pQueryStruct->pDisplay,  type,  tmpSel.u.query.nFields  );
	if  (  tmpSel.u.query.nFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.columns,  pQueryStruct->pDisplay,  (  tmpSel.u.query.nFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	*/
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from qnmScannedIpTab %s %s %s %s %s %s"  ),  CString(  whereClause[0]  ?  "where"  :  ""  ),  CString(  whereClause  ),  CString(  groupClause[0]  ?  "group by"  :  ""  ),  CString(  groupClause  ),  CString(  havingClause[0]  ?  "having"  :  ""  ),  CString(  havingClause  )  );
	//  _sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s",  whereClause  );
	//  _sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  groupClause  );
	
	//  showMcSel(  &tmpSel  );

	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	
	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_statIpScanList  )  );

	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}

 BOOL  bNetMcStatPcInfoFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause,  LPCTSTR  groupClause,  LPCTSTR  havingClause,  QNM_QUERY_STRUCT  *  pQueryStruct  )
{	 
	BOOL					bRet									=	FALSE;
	//QY_MC				*	pQyMc									=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp									=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcPcList;

	if  (  setQueryColumns( pQyMc, 0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	TCHAR					wherePart[CONST_maxSqlClauseLen  +  1]	=	_T(  ""  );
	if  (  whereClause  )  _sntprintf(  wherePart,  mycountof(  wherePart  ),  _T(  "%s"  ),  whereClause  );
	letInScope(  g_pQyMc,  wherePart,  mycountof(  wherePart  )  );

	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from qyPcTab left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 %s %s %s %s %s %s"  ),  CString(  wherePart[0]  ?  "where"  :  ""  ),  CString(  wherePart  ),  CString(  groupClause[0]  ?  "group by"  :  ""  ),  CString(  groupClause  ),  CString(  havingClause[0]  ?  "having"  :  ""  ),  CString(  havingClause  )  );
	
	//  _sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s",  whereClause  );
	//  _sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  groupClause  );
	
	showMcSel(  &tmpSel  );

	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	
	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_statPcInfoList  )  );

	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}

 BOOL  bStatMessengerInfoFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClauseParam,  LPCTSTR  groupClause,  LPCTSTR  havingClause,  QNM_QUERY_STRUCT  *  pQueryStruct  )
{	 
	BOOL					bRet									=	FALSE;
	//QY_MC				*	pQyMc									=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp									=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	TCHAR					whereClause[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	tmpSel.u.query.type			=	CONST_qyQueryType_imObjList;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	
	if  (  whereClauseParam  )  lstrcpyn(  whereClause,  whereClauseParam,  mycountof(  whereClause  )  );
	tTrim(  whereClause  );
	if  (  whereClause[0]  )  _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s and"  ),  whereClause  );
	_sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s (qyImObjTab.uiType in(%d,%d))"  ),  whereClause,  CONST_objType_me,  CONST_objType_messenger  );

	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from qyImObjTab left join qyImObjRegInfoTab on (qyImObjTab.misServName=qyImobjRegInfoTab.misServName and qyImObjTab.idStr=qyImObjRegInfoTab.idStr) %s %s %s %s %s %s"  ),  CString(  whereClause[0]  ?  "where"  :  ""  ),  CString(  whereClause  ),  CString(  groupClause[0]  ?  "group by"  :  ""  ),  CString(  groupClause  ),  CString(  havingClause[0]  ?  "having"  :  ""  ),  CString(  havingClause  )  );
	//  _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s",  whereClause  );
	//  _sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  groupClause  );
	
	showMcSel(  &tmpSel  );

	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	
	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_statMessengerInfoList  )  );

	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}

 BOOL  bNetMcStatUsrInfoFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause,  LPCTSTR  groupClause,  LPCTSTR  havingClause,  QNM_QUERY_STRUCT  *  pQueryStruct  )
{	 
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcPcList;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	

	TCHAR					wherePart[CONST_maxSqlClauseLen  +  1]	=	_T(  ""  );
	if  (  whereClause  )  _sntprintf(  wherePart,  mycountof(  wherePart  ),  _T(  "%s"  ),  whereClause  );
	letInScope(  g_pQyMc,  wherePart,  mycountof(  wherePart  )  );

	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from qyPcTab left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 %s %s %s %s %s %s"  ),  CString(  wherePart[0]  ?  "where"  :  ""  ),  CString(  wherePart  ),  CString(  groupClause[0]  ?  "group by"  :  ""  ),  CString(  groupClause  ),  CString(  havingClause[0]  ?  "having"  :  ""  ),  CString(  havingClause  )  );
	//  _sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s",  whereClause  );
	//  _sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  groupClause  );
	
	showMcSel(  &tmpSel  );

	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	
	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_statUsrInfoList  )  );

	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}


 BOOL  bNetMcStatGeneralFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause,  LPCTSTR  groupClause,  LPCTSTR  havingClause,  QNM_QUERY_STRUCT  *  pQueryStruct  )
{	 
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcEventList;

	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;

	
	TCHAR					wherePart[CONST_maxSqlClauseLen  +  1]	=	_T(  ""  );
	if  (  whereClause  )  _sntprintf(  wherePart,  mycountof(  wherePart  ),  _T(  "%s"  ),  whereClause  );
	letInScope_event(  g_pQyMc,  wherePart,  mycountof(  wherePart  )  );
	

	//
	//  _sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from qyPcEventTab  left join qyPcRegInfoTab on qyPcEventTab.mac0=qyPcRegInfoTab.mac0 %s %s %s %s %s %s"  ),  CString(  whereClause[0]  ?  "where"  :  ""  ),  CString(  whereClause  ),  CString(  groupClause[0]  ?  "group by"  :  ""  ),  CString(  groupClause  ),  CString(  havingClause[0]  ?  "having"  :  ""  ),  CString(  havingClause  )  );
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from qyPcEventTab %s %s %s %s %s %s"  ),  CString(  wherePart[0]  ?  "where"  :  ""  ),  CString(  wherePart  ),  CString(  groupClause[0]  ?  "group by"  :  ""  ),  CString(  groupClause  ),  CString(  havingClause[0]  ?  "having"  :  ""  ),  CString(  havingClause  )  );

	//  _sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s",  whereClause  );
	//  _sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  groupClause  );
	
	showMcSel(  &tmpSel  );

	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	
	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_statGeneralList  )  );

	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}


 BOOL  bNetMcStatOthersFunc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause,  LPCTSTR  groupClause,  LPCTSTR  havingClause,  QNM_QUERY_STRUCT  *  pQueryStruct  )
{	 
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcEventList;
	/*
	MACRO_getnItems(  pQueryStruct->pSql,  type,  tmpSel.u.query.nSqlFields  );
	if  (  tmpSel.u.query.nSqlFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.sqlColumns,  pQueryStruct->pSql,  (  tmpSel.u.query.nSqlFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	MACRO_getnItems(  pQueryStruct->pDisplay,  type,  tmpSel.u.query.nFields  );
	if  (  tmpSel.u.query.nFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.columns,  pQueryStruct->pDisplay,  (  tmpSel.u.query.nFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	*/
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;

	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from qyPcEventTab %s %s %s %s %s %s"  ),  CString(  whereClause[0]  ?  "where"  :  ""  ),  CString(  whereClause  ),  CString(  groupClause[0]  ?  "group by"  :  ""  ),  CString(  groupClause  ),  CString(  havingClause[0]  ?  "having"  :  ""  ),  CString(  havingClause  )  );
	//  _sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s",  whereClause  );
	//  _sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  groupClause  );
	
	showMcSel(  &tmpSel  );

	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	
	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_statOthersList  )  );

	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;

}

