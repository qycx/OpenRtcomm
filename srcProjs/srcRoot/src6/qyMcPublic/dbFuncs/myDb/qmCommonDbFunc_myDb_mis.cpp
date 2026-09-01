

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


BOOL  bGetImAmRcdBySth_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  short  usAuthType,  LPCTSTR  messengerName,  int  id,  QY_imAm_RCD  *  pObj  )
{
	return  FALSE;
}
#if  0
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
#endif

 BOOL  bGetImOtherRegInfoBySth_myDb(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  MSGR_ADDR  *  pAddr,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  )
 {
	 return  FALSE;
 }
int  tmpHandler_bGetMeInfoBySth_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;

	//  p0
	QY_MESSENGER_INFO  *  pObj  =  (  QY_MESSENGER_INFO  *  )p1;
	QMEM_qyImObj		*	pQMem	=	(  QMEM_qyImObj  *  )p2;

	if  (  pQMem->messengerInfo.uiType  ==  CONST_objType_me  ){
		memcpy(  pObj, &pQMem->messengerInfo,  sizeof(  pObj[0]  )  );
		iRet  =  1;  goto  errLabel;
	}

	iRet  =  0;
errLabel:
	return  iRet;

}

 //  2013/02/05
 BOOL  bGetMeInfoBySth_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_INFO  *  pObj  )
{
	 BOOL			bRet									=		FALSE;
	 CMyDb		*	pDb										=		(  CMyDb  *  )pDbParam;

	 if  (  qTraverse(  pDb->m_var.pQ_qyImObjTab,  tmpHandler_bGetMeInfoBySth_myDb,  NULL,  pObj  )  <=  0  )  goto  errLabel;

#if  0
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

#endif

	 bRet  =  TRUE;

errLabel:

	 return  bRet;
}

int  tmpHandler_bGetMessengerInfoBySth_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int						iErr	=	-1;
	QY_MESSENGER_ID		*	pIdInfo  =  (  QY_MESSENGER_ID  *  )p0;
	QMEM_qyImObj		*	pMem_o	=	(  QMEM_qyImObj  *  )p1;
	QMEM_qyImObj		*	pMem	=	(  QMEM_qyImObj  *  )p2;

	if  (  pIdInfo->ui64Id  ==  pMem->messengerInfo.idInfo.ui64Id  )  {
		memcpy(  pMem_o,  pMem,  sizeof(  pMem_o[0]  )  );
		iErr  =  1;  goto  errLabel;
	}

	iErr  =  0;
	errLabel:
	return  iErr;
}

BOOL  bGetMessengerRegInfoBySth_myDb(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  );
BOOL  bGetMessengerInfoBySth_myDb(  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_INFO  *  pObjParam,  QY_MESSENGER_REGINFO  *  pRegInfo,  QY_MESSENGER_REGINFO  *  pRegInfoInTab1,  QY_MESSENGER_phoneInfo  *  pPhoneInfo  )		//  2008/12/28ÐÞ¸Ä
{
	BOOL					bRet	=	FALSE;
	CMyDb				*	pDb	=	(  CMyDb  *  )pDbParam;
	QMEM_qyImObj			qMem;

	QY_MESSENGER_INFO		tmpObjInfo;	
	QY_MESSENGER_INFO	*	pObj									=		NULL;

	if  (  !misServName  ||  !pIdInfo  ||  !pIdInfo->ui64Id  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "bGetMessengerInfoBySth_myDb failed, param err"  )  );
		#endif
		return  FALSE;
	}

	memset(  &qMem,  0,  sizeof(  qMem  )  );

	if  (  qTraverse(  pDb->m_var.pQ_qyImObjTab,  tmpHandler_bGetMessengerInfoBySth_myDb,  pIdInfo,  &qMem  )  <=  0  )  goto  errLabel;
	

	//
	pObj  =  pObjParam  ?  pObjParam  :  &tmpObjInfo;	//  ×¢Òâ£¬ÕâÀï£¬ÒòÎªÏÂÃæµÄregInfo¶¼ÒªÓÃµ½uiType, ËùÒÔ£¬ÕâÀïÊÇÒ»¶¨ÐèÒª°ÑÐÅÏ¢È¡³öÀ´µÄ¡£

	if  (  pObj  )  {
		memcpy(  pObj,  &qMem.messengerInfo,  sizeof(  pObj[0]  )  );
	}
	if  (  pRegInfo  )  {

		memset(  pRegInfo,  0,  sizeof(  pRegInfo[0]  )  );
		//
		if  (  bGetMessengerRegInfoBySth_myDb(  pDbParam,  iDbType,  pFieldIdTable,  CONST_tabName_qyImObjRegInfoTab,  misServName,  pIdInfo,  0,  pRegInfo  )  )  {

			 lstrcpyn(  pRegInfo->addr.misServName,  misServName,  mycountof(  pRegInfo->addr.misServName  )  );
			 pRegInfo->addr.uiObjType  =  pObj->uiType;
			 pRegInfo->addr.idInfo.ui64Id  =  pIdInfo->ui64Id;
		 }
	}

	bRet  =  TRUE;

errLabel:

	return  bRet;
}

//  要对qyImObjTab对应的队列进行操作. 2013/01/29

int  insertImObj_recoverMessenger_myDb(  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime  )
{
	int						iErr	=	-1;

	CMyDb				*	pDb	=	(  CMyDb  *  )pDbParam;
	QMEM_qyImObj			qMem;

	memset(  &qMem,  0,  sizeof(  qMem  )  );
	memcpy(  &qMem.messengerInfo,  pObj,  sizeof(  qMem.messengerInfo  )  );

	if  (  qPostMsg(  &qMem,  sizeof(  qMem  ),  pDb->m_var.pQ_qyImObjTab,  _T(  "insertImObj-recoverMsgr"  )))  goto  errLabel;

	iErr  =  0;
errLabel:

	return  iErr;
}

int  tmpHandler_updateImObj_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int						iErr	=	-1;
	QY_MESSENGER_INFO	*	pObj  =  (  QY_MESSENGER_INFO  *  )p0;
	//  p1
	QMEM_qyImObj		*	pMem  =  (  QMEM_qyImObj  *  )p2;

	if  (  pMem->messengerInfo.idInfo.ui64Id  ==  pObj->idInfo.ui64Id  )  {
		pMem->messengerInfo.uiType  =  pObj->uiType;
		//
		pMem->messengerInfo.iRole  =  pObj->iRole;	//  2017/08/14
		//
		pMem->messengerInfo.iStatus  =  pObj->iStatus;
		iErr  =  1;  goto  errLabel;
	}

	iErr  =  0;
errLabel:

	return  iErr;
}

int  updateImObj_recoverMessenger_myDb(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime,  int  iRcdId  )
	{
	int		iErr	=	-1;
	CMyDb				*	pDb	=	(  CMyDb  *  )pDbParam;

	if  (  !pObj  ||  !pObj->idInfo.ui64Id  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "updateImObj_recoverMessenger_myDb failed, param err"  )  );
		#endif
		return  -1;
	}

	if  (  qTraverse(  pDb->m_var.pQ_qyImObjTab,  tmpHandler_updateImObj_myDb,  pObj,  0  )  <  0  )  goto  errLabel;
	
	iErr  =  0;
	
errLabel:

	return  iErr;
}

int  updateImObj_recoverMessenger2_myDb(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime,  int  iRcdId  )
{
	return  0;
}

 //
 int  insertImObj_recoverImGrp_myDb(  void  *  pDbParam,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime  )
{

	int				iErr										=  -1;

	CMyDb				*	pDb	=	(  CMyDb  *  )pDbParam;

		 QMEM_qyImObj	mem;
		 memset(  &mem,  0,  sizeof(  mem  )  );
		 mem.messengerInfo.uiType  =  uiObjType;
		 mem.messengerInfo.idInfo.ui64Id  =  pGrpInfo->idInfo.ui64Id;
		 mem.messengerInfo.iStatus  =  CONST_qyStatus_ok;
		 if  (  qPostMsg(  &mem,  sizeof(  mem  ),  pDb->m_var.pQ_qyImObjTab,  _T(  "insertImObj_recoverImGrp"  )))  goto  errLabel;

		 iErr  =  0;

errLabel:
		 return  iErr;

}

 int  tmpHandler_updateImObj_recoverImGrp_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 int	iErr	=	-1;
	 IM_GRP_INFO	*	pGrpInfo	=	(  IM_GRP_INFO  *  )p0;
	 unsigned  int		uiObjType	=	(  unsigned  int  )p1;
	 QMEM_qyImObj		*	pMem		=	(  QMEM_qyImObj  *  )p2;

	 if  (  pMem->messengerInfo.idInfo.ui64Id  ==  pGrpInfo->idInfo.ui64Id  )  {
		 pMem->messengerInfo.uiType  =  uiObjType;
		 pMem->messengerInfo.iStatus  =  CONST_qyStatus_ok;
		 iErr  = 1;  goto  errLabel;
	 }
	 iErr  =  0;
	 errLabel:
	 return  iErr;
 }


  int  updateImObj_recoverImGrp_myDb(  void  *  pDbParam,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  int  iRcdId  )
  {
	  int	iErr	=	-1;
	  CMyDb				*	pDb	=	(  CMyDb  *  )pDbParam;

	  if  (  !pGrpInfo  ||  !pGrpInfo->idInfo.ui64Id  )  {
		  #ifdef  __DEBUG__
				  traceLog(  _T(  "updateImObj_recoverImGrp_myDb failed, param err"  )  );
		  #endif
		  return  -1;
	  }
#if  0

	  TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	  	  
	  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set uiType=%d,iStatus=%d where id=%d"  ),
									CONST_tabName_qyImObjTab,
									uiObjType,
									CONST_qyStatus_ok,
									iRcdId  );
	  if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	  iErr  =  0;
#endif

	  if  (  qTraverse(  pDb->m_var.pQ_qyImObjTab,  tmpHandler_updateImObj_recoverImGrp_myDb,  pGrpInfo,  (  void  *  )uiObjType  )  <  0  )  goto  errLabel;
	  iErr  =  0;
errLabel:			   
	  return  iErr;
  }

    int  updateImObj_recoverImGrp2_myDb(  void  *  pDbParam,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  int  iRcdId  )
	{
		return  0;
	}
  
int  tmpHandler_bGetImGrpInfoBySth_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int					iErr	=	-1;
	QY_MESSENGER_ID	*	pIdInfo  =  (  QY_MESSENGER_ID  *  )p0;
	IM_GRP_INFO		*	pGrpInfo	=	(  IM_GRP_INFO  *  )p1;
	IM_GRP_INFO		*	pMem		=	(  IM_GRP_INFO  *  )p2;

	if  (  pMem->idInfo.ui64Id  ==  pIdInfo->ui64Id  )  {
		memcpy(  pGrpInfo,  pMem,  sizeof(  pGrpInfo[0]  )  );
		iErr  =  1;  goto  errLabel;
	}

	iErr  =  0;
errLabel:
	return  iErr;

}

 BOOL  bGetImGrpInfoBySth_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  IM_GRP_INFO  *  pRcd  )
{
 	 BOOL			bRet									=		FALSE;
	 CMyDb		*	pDb				=	(  CMyDb  *  )pDbParam;

	 if  (  !misServName  ||  !pIdInfo  ||  !pIdInfo->ui64Id  )  {
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "bGetImGrpInfoBySth_myDb failed, param err"  )  );
		 #endif
		 return  FALSE;
	 }

	 if  (  qTraverse(  pDb->m_var.pQ_qyImGrpInfoTab,  tmpHandler_bGetImGrpInfoBySth_myDb,  pIdInfo,  pRcd  )  <=  0  )  goto  errLabel;
	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}


  int  insertImGrp_recoverImGrp_myDb(  void  *  pDbParam,  int  iDbType,  IM_GRP_INFO  *  pGrpInfo  )
{
	int		iErr	=	-1;

	CMyDb		*	pDb				=	(  CMyDb  *  )pDbParam;


	 if  (  !pGrpInfo  )  return  -1;


	 if  (  qPostMsg(  pGrpInfo,  sizeof(  pGrpInfo[0]  ),  pDb->m_var.pQ_qyImGrpInfoTab,  _T(  "insertImGrp_recoverImGrp 1"  )))  goto  errLabel;

		 iErr  =  0;
errLabel:
		 return  iErr;

  }

  int  tmpHandler_updateImGrp_recoverImGrp_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
  {
	  int		iErr  =  -1;
	  IM_GRP_INFO  *  pGrpInfo	=	(  IM_GRP_INFO  *  )p0;
	  //  p1
	  IM_GRP_INFO  *  pMem  =  (  IM_GRP_INFO  *  )p2;

	  if  (  pGrpInfo->idInfo.ui64Id  ==  pMem->idInfo.ui64Id  )  {
		  safeTcsnCpy(  pGrpInfo->name,  pMem->name,  mycountof(  pMem->name  )  );
		  iErr  =  1;  goto  errLabel;
	  }

	  iErr  =  0;
errLabel:
	  return  iErr;
  }

  int  updateImGrp_recoverImGrp_myDb(  void  *  pDbParam,  int  iDbType,  IM_GRP_INFO  *  pGrpInfo,  int  iRcdId  )
  {

	int		iErr	=	-1;

	CMyDb		*	pDb				=	(  CMyDb  *  )pDbParam;

	if  (  !pGrpInfo  ||  !pGrpInfo->idInfo.ui64Id  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "updateImGrp_recoverImGrp_myDb failed, param err"  )  );
		#endif
		return  -1;
	}

#if  0
	  			   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set name=%s,tLastModifiedTime='%s' where id=%d"  ),  CONST_tabName_qyImGrpInfoTab,  getDbValStr(  iDbType,  CONST_iDataType_desc,  pGrpInfo->name  ),  CString(  timeBuf  ),  iRcdId  );
			   if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  traceLogA(  "err"  );
#endif
			   if  (  qTraverse(  pDb->m_var.pQ_qyImGrpInfoTab,  tmpHandler_updateImGrp_recoverImGrp_myDb,  pGrpInfo,  0  )  <  0  )  goto  errLabel;

			   iErr  =  0;
errLabel:
			   return  iErr;

  }



  int  tmpHandler_bGetImGrpMemBySth_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
  {
	  int	iErr	=	-1;
	  COMMON_PARAM  *  pCommonParam0  =  (  COMMON_PARAM  *  )p0;
	  IM_GRP_MEM  *  pRcd	=	(  IM_GRP_MEM  *  )p1;
	  IM_GRP_MEM  *  pQMem  =  (  IM_GRP_MEM  *  )p2;

	  QY_MESSENGER_ID  *  pIdInfo_grp  =  (  QY_MESSENGER_ID  *  )pCommonParam0->p0;
	  QY_MESSENGER_ID  *  pIdInfo_mem  =  (  QY_MESSENGER_ID  *  )pCommonParam0->p1;
	  int				  iRcdId		=	(  int  )pCommonParam0->p2;
	  //

	  if  (  pIdInfo_grp  &&  pIdInfo_mem  )  {
		  if  (  pQMem->idInfo_grp.ui64Id  ==  pIdInfo_grp->ui64Id  
			  &&  pQMem->idInfo_mem.ui64Id  ==  pIdInfo_mem->ui64Id  )
		  {
			  memcpy(  pRcd,  pQMem,  sizeof(  pRcd[0]  )  );
			  iErr  =  1;  goto  errLabel;
		  }
		  }
	  else  if  (  pQMem->id  ==  iRcdId  )  {
			  memcpy(  pRcd,  pQMem,  sizeof(  pRcd[0]  )  );
			  iErr  =  1;  goto  errLabel;		    
	  }

	  iErr  =  0;
errLabel:
	  return  iErr;
  }

 BOOL  bGetImGrpMemBySth_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo_grp,  QY_MESSENGER_ID  *  pIdInfo_mem,  int  iRcdId,  IM_GRP_MEM  *  pRcd  )
{
	BOOL	bRet	=	FALSE;
		
	CMyDb	*	pDb	=	(  CMyDb  *  )pDbParam;
	COMMON_PARAM	commonParam;

#if  0
	if  (  !pIdInfo_grp  ||  !pIdInfo_grp->ui64Id  ||  !pIdInfo_mem  ||  !pIdInfo_mem->ui64Id  )  {
#ifdef  __DEBUG__
		traceLog(  _T(  "bGetImGrpMemBySth_myDb failed, param err"  )  );
#endif
		return  FALSE;
	}
#endif

	MACRO_makeCommonParam3(  pIdInfo_grp,  pIdInfo_mem,  (  void  *  )iRcdId,  commonParam  );
	if  (  qTraverse(  pDb->m_var.pQ_qyImGrpMemTab,  tmpHandler_bGetImGrpMemBySth_myDb,  &commonParam,  pRcd  )  <=  0  )  goto  errLabel;


	bRet  =  TRUE;
	errLabel:
	return  bRet;
}

   int  insertImGrpMem_recoverImGrpMem_myDb(  void  *  pDbParam,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime  )
{
	int					iErr	=	-1;

	CMyDb	*	pDb	=	(  CMyDb  *  )pDbParam;


	 if  (  !pGrpMem  )  return  -1;
	 
	 //  2014/04/20
	 pGrpMem->id  =  getuiNextTranNo(  0,  0,  0  );

#if  0
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr_grp,idStr_mem,iRole,startTime,tLastModifiedTime,iStatus)"  )
									_T(  "Values(%s,'%s','%s',%d,'%s','%s',%d)"  ),
									CONST_tabName_qyImGrpMemTab,
									getDbValStr(  iDbType,  CONST_iDataType_misServName,  pGrpMem->misServName  ),
									CString(  idStr_grp  ),
									CString(  idStr_mem  ),
									pGrpMem->iRole,
									CString(  timeBuf  ),
									CString(  timeBuf  ),
									pGrpMem->iStatus  );		 
		 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
#endif
		 if  (  qPostMsg(  pGrpMem,  sizeof(  pGrpMem[0]  ),  pDb->m_var.pQ_qyImGrpMemTab,  _T(  "insertImgrpMem_recoverImGrpMem"  )))  goto  errLabel;

		 iErr  =  0;
errLabel:
		 return  iErr;
 }

   int  tmpHandler_updateImGrpMem_recoverImGrpMem_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 int			iErr	=	-1;
	 IM_GRP_MEM  *  pGrpMem  =  (  IM_GRP_MEM  *  )p0;
	 //  p1
	 IM_GRP_MEM  *  pQMem  =  (  IM_GRP_MEM  *  )p2;

	 if  (  pGrpMem->idInfo_grp.ui64Id  ==  pQMem->idInfo_grp.ui64Id  &&  pGrpMem->idInfo_mem.ui64Id  ==  pQMem->idInfo_mem.ui64Id  )  {
		 pQMem->iRole  =  pGrpMem->iRole;
		 pQMem->iStatus  =  pGrpMem->iStatus;
		 iErr  =  1;  goto  errLabel;
	 }

	 iErr  =  0;

errLabel:

	 return  iErr;
   }

 int  updateImGrpMem_recoverImGrpMem_myDb(  void  *  pDbParam,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime,  int  iRcdId  )
 {
	 int				iErr										=  -1;
	 TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	 char				timeBuf[CONST_qyTimeLen  +  1];

	 if  (  !pGrpMem  )  return  -1;
	 if  (  !pGrpMem->idInfo_grp.ui64Id  ||  !pGrpMem->idInfo_mem.ui64Id  )  {
#ifdef  __DEBUG__
		traceLog(  _T(  "updateImGrpMem_recoverImGrpMem_myDb failed, param err"  )  );
#endif
		return  -1;
	 }
	 
	 	CMyDb	*	pDb	=	(  CMyDb  *  )pDbParam;
#if  0
	 getCurTime(  timeBuf  );

 			   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set iRole=%d,iStatus=%d,tLastModifiedTime='%s' where id=%d"  ),
									CONST_tabName_qyImGrpMemTab,
									pGrpMem->iRole,
									pGrpMem->iStatus,
									CString(  timeBuf  ),
									iRcdId  );
			   if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
#endif

			   if  (  qTraverse(  pDb->m_var.pQ_qyImGrpMemTab,  tmpHandler_updateImGrpMem_recoverImGrpMem_myDb,  pGrpMem,  0  )  <  0  )  goto  errLabel;

			   iErr  =  0;
errLabel:
			   return  iErr;
 }

 int  updateImGrpMem_recoverImGrpMem2_myDb(  void  *  pDbParam,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime,  int  iRcdId  )
{
		return  0;
}



 //  201407/28

  int  tmpHandler_getnGrpMems_isCli_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
  {
	  int	iErr	=	-1;
	  COMMON_PARAM  *  pCommonParam0  =  (  COMMON_PARAM  *  )p0;
	  int			*	pn	=	(  int  *  )p1;
	  IM_GRP_MEM  *  pQMem  =  (  IM_GRP_MEM  *  )p2;

	  QY_MESSENGER_ID  *  pIdInfo_grp  =  (  QY_MESSENGER_ID  *  )pCommonParam0->p0;
	  //

	  if  (  !pIdInfo_grp  )  goto  errLabel;

		  if  (  pQMem->idInfo_grp.ui64Id  ==  pIdInfo_grp->ui64Id  )
		  {
			  (*pn)  ++  ;
		  }
		  
	  

	  iErr  =  0;
errLabel:
	  return  iErr;
  }


  __declspec(  dllexport  )  int  getnGrpMems_isCli(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_ID  *  pIdInfo_grp  )
{
	int	iErr	=	-1;
	int  n  =  -1;
	
	//
	if  (  !pDbParam  )  return  -1;
	if  (  iDbType  !=  CONST_dbType_myDb  )  return  -1;

	CMyDb	*	pDb	=	(  CMyDb  *  )pDbParam;
	COMMON_PARAM	commonParam;

#if  10
	if  (  !pIdInfo_grp  ||  !pIdInfo_grp->ui64Id  )  {
#ifdef  __DEBUG__
		traceLog(  _T(  "bGetImGrpMemBySth_myDb failed, param err"  )  );
#endif
		return  -1;
	}
#endif

	MACRO_makeCommonParam3(  pIdInfo_grp,  0,  (  void  *  )0,  commonParam  );
	n  =  0;
	if  (  qTraverse(  pDb->m_var.pQ_qyImGrpMemTab,  tmpHandler_getnGrpMems_isCli_myDb,  &commonParam,  &n  )  <  0  )  goto  errLabel;

	iErr  =  0;

errLabel:
	return  iErr  ?  iErr  :  n;
}


  //
  int  tmpHandler_enumGrpMems_isCli_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
  {
	  int	iErr	=	-1;
	  COMMON_PARAM  *  pCommonParam0  =  (  COMMON_PARAM  *  )p0;
	  COMMON_PARAM  *  pCommonParam1  =  (  COMMON_PARAM  *  )p1;
	  IM_GRP_MEM  *  pQMem  =  (  IM_GRP_MEM  *  )p2;

	  QY_MESSENGER_ID  *  pIdInfo_grp  =  (  QY_MESSENGER_ID  *  )pCommonParam0->p0;
	  //
	  PF_commonHandler	i_pf  =  (  PF_commonHandler  )pCommonParam1->p0;
	  void  *  i_p0  =  pCommonParam1->p1;
	  void  *  i_p1  =  pCommonParam1->p2;
	  //

	  if  (  !pIdInfo_grp  )  goto  errLabel;

		  if  (  pQMem->idInfo_grp.ui64Id  ==  pIdInfo_grp->ui64Id  )
		  {
			  int  tmpiRet  =  i_pf(  i_p0,  i_p1,  pQMem  );
			  if  (  tmpiRet  )  {
				  iErr  =  tmpiRet;  goto  errLabel;
			  }
		  }
		  
	  

	  iErr  =  0;
errLabel:
	  return  iErr;
  }


  //  2014/09/25
 __declspec(  dllexport  ) int  enumGrpMems_isCli(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_ID  *  pIdInfo_grp,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  )
 {
	int	iErr	=	-1;
	
	//
	if  (  !pDbParam  )  return  -1;
	if  (  iDbType  !=  CONST_dbType_myDb  )  return  -1;

	CMyDb	*	pDb	=	(  CMyDb  *  )pDbParam;
	COMMON_PARAM	commonParam0;
	COMMON_PARAM	commonParam1;


#if  10
	if  (  !pIdInfo_grp  ||  !pIdInfo_grp->ui64Id  )  {
#ifdef  __DEBUG__
		traceLog(  _T(  "bGetImGrpMemBySth_myDb failed, param err"  )  );
#endif
		return  -1;
	}
#endif

	MACRO_makeCommonParam3(  pIdInfo_grp,  0,  0,  commonParam0  );
	MACRO_makeCommonParam3(  pf,  p0,  p1,  commonParam1  );

	int  tmpiRet  =  -1;
	tmpiRet  =  qTraverse(  pDb->m_var.pQ_qyImGrpMemTab,  tmpHandler_enumGrpMems_isCli_myDb,  &commonParam0,  &commonParam1  );
	if  (  tmpiRet  )  {
		iErr  =  tmpiRet;  goto  errLabel;
	}

	iErr  =  0;

errLabel:



	return  iErr;


}



 /////////////
int  tmpHandler_updateImObj_me_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int						iErr	=	-1;
	QY_MESSENGER_INFO	*	pObj_me  =  (  QY_MESSENGER_INFO  *  )p0;
	//  p1
	QMEM_qyImObj		*	pMem  =  (  QMEM_qyImObj  *  )p2;

	if  (  pObj_me->idInfo.ui64Id  ==  pMem->messengerInfo.idInfo.ui64Id  )  {
		if  (  pMem->messengerInfo.uiType  !=  CONST_objType_me  )  {
			pMem->messengerInfo.uiType  =  CONST_objType_me;
		}
	    }
	else  {
		  if  (  pMem->messengerInfo.uiType  ==  CONST_objType_me  )  {
			  pMem->messengerInfo.uiType  =  CONST_objType_messenger;
		  }
	}

	iErr  =  0;
	return  iErr;
}

int  updateImObj_me_myDb(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj_me  ) 	 
 {	
	int						iErr			=	-1;
	CMyDb				*	pDb	=	(  CMyDb  *  )pDbParam;

	if  (  qTraverse(  pDb->m_var.pQ_qyImObjTab,  tmpHandler_updateImObj_me_myDb,  pObj_me,  0  )  <  0  )  goto  errLabel;

#if  0
		 if  (  pObj_me->uiType  !=  CONST_objType_me  )  {
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyImObjTab set uiType=%d where misServName=%s and idStr='%s'"  ),  CONST_objType_me,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pObj_me->misServName  ),  CString(  idStr  )  );
			 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
		 }
		 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyImObjTab set uiType=%d where misServName=%s and uiType=%d and idStr<>'%s'"  ),  CONST_objType_messenger,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pObj_me->misServName  ),  CONST_objType_me,  CString(  idStr  )  );
		 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
#endif

		 iErr  =  0;
errLabel:
		 return  iErr;
	 
 }

 int  insertImObjRule_recoverImObjRules_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime  )
{
	 int  iErr  =  -1;
	 CMyDb			*  pMyDb		=  (  CMyDb  *  )pDb;

	 if  (  !misServName  ||  !pIdInfo  ||  !pIdInfo->ui64Id  )  return  -1;

	 QMEM_qyImObjRule		qMem;
	 memset(  &qMem,  0,  sizeof(  qMem  )  );

	 _sntprintf(  qMem.ruleRcd.misServName,  mycountof(  qMem.ruleRcd.misServName  ),  _T(  "%s"  ),  misServName  );
	 qMem.ruleRcd.idInfo.ui64Id  =  pIdInfo->ui64Id;
	 qMem.ruleRcd.idInfo_related.ui64Id  =  pReqMem->idInfo_related.ui64Id;
	 qMem.ruleRcd.uiRuleType  =  pReqMem->uiRuleType;
	 qMem.ruleRcd.usIndex  =  pReqMem->usIndex;
	 qMem.ruleRcd.uiCmd  =  pReqMem->uiCmd;
	 safeTcsnCpy(  pReqMem->wDesc,  qMem.ruleRcd.col0,  mycountof(  qMem.ruleRcd.col0  )  );

	 if  (  qPostMsg(  &qMem,  sizeof(  qMem  ),  pMyDb->m_var.pQ_qyImObjRuleTab,  _T(  "insertImObjRule_recoverImObjRules"  )))  goto  errLabel;

#if  0
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
#endif
	iErr =  0;
errLabel:

	return  iErr;

}

 BOOL  tmpHandler_bDeleteImObjRule_recoverImObjRules_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 BOOL  bRet  =  FALSE;

	 QY_MESSENGER_ID			*  pIdInfo	=  (  QY_MESSENGER_ID  *  )p0;
	 REFRESH_imObjRule_reqMem   *  pReqMem	=  (  REFRESH_imObjRule_reqMem  *  )p1;
	 QMEM_qyImObjRule			*  pQMem  =  (  QMEM_qyImObjRule  *  )p2;

	 if  (  pQMem->ruleRcd.idInfo.ui64Id  ==  pIdInfo->ui64Id
		 &&  pQMem->ruleRcd.idInfo_related.ui64Id  ==  pReqMem->idInfo_related.ui64Id
		 &&  pQMem->ruleRcd.uiRuleType  ==  pReqMem->uiRuleType
		 &&  pQMem->ruleRcd.usIndex  ==  pReqMem->usIndex  )
	 {
		 bRet  =  TRUE;  goto  errLabel;
	 }

errLabel:

	 return  bRet;
 }

 int  deleteImObjRule_recoverImObjRules_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  int  rcdId  )
{
	 int  iErr  =  -1;
	 CMyDb		*  pMyDb	=  (  CMyDb  *  )pDb;

	 if  (  !misServName  ||  !pIdInfo  ||  !pIdInfo->ui64Id  )  return  -1;

	 if  (  qRemoveMsg(  pMyDb->m_var.pQ_qyImObjRuleTab,  tmpHandler_bDeleteImObjRule_recoverImObjRules_myDb,  pIdInfo,  pReqMem  )  <  0  )  goto  errLabel;
#if 0
	 TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1];

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id =%d"  ),  CONST_tabName_qyImObjRuleTab,  rcdId  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;	
#endif

	 iErr =  0;
errLabel:

	return  iErr;

}

 int  tmpHandler_updateImObjRule_recoverImObjRules_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 BOOL  iRet  =  -1;

	 QY_MESSENGER_ID			*  pIdInfo  =  (  QY_MESSENGER_ID  *  )p0;
	 REFRESH_imObjRule_reqMem   *  pReqMem	=  (  REFRESH_imObjRule_reqMem  *  )p1;
	 QMEM_qyImObjRule			*  pQMem	=  (  QMEM_qyImObjRule  *  )p2;

	 if  (  pQMem->ruleRcd.idInfo.ui64Id  ==  pIdInfo->ui64Id
		 &&  pQMem->ruleRcd.idInfo_related.ui64Id  ==  pReqMem->idInfo_related.ui64Id
		 &&  pQMem->ruleRcd.uiRuleType  ==  pReqMem->uiRuleType
		 &&  pQMem->ruleRcd.usIndex  ==  pReqMem->usIndex  )
	 {
		 pQMem->ruleRcd.uiCmd  =  pReqMem->uiCmd;
		 iRet  =  1;  goto  errLabel;
	 }

	 iRet  =  0;
errLabel:

	 return  iRet;
 }

int  updateImObjRule_recoverImObjRules_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime,  int  rcdId  )
{
	int  iErr  =  -1;
	CMyDb  *  pMyDb  =  (  CMyDb  *  )pDb;

	if  (  !misServName  ||  !pIdInfo  ||  !pIdInfo->ui64Id  ||  !pReqMem->idInfo_related.ui64Id  )  return  -1;

	if  (  qTraverse(  pMyDb->m_var.pQ_qyImObjRuleTab,  tmpHandler_updateImObjRule_recoverImObjRules_myDb,  pIdInfo,  pReqMem  )  <  0  )  goto  errLabel;

#if  0
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
#endif

	iErr =  0;
errLabel:

	return  iErr;

}

int  updateImObjRule_recoverImObjRules2_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime,  int  rcdId  )
{
	int  iErr  =  0;
	return  iErr;
}

int  updateImObj_refreshImGrps_end_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiObjType,  time_t  tLastModifiedTime  )
{
	return  0;

}

int  updateImGrpMem_refreshImGrpMems_end_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  time_t  tLastModifiedTime  )
 {
	 return  0;
 }


int  updateImObj_refreshContacts_end_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  time_t  tLastModifiedTime  )
{
	return  0;
}

int  tmpHandler_bGetImObjRuleRcdBySth_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;

	COMMON_PARAM		*  pCommonParam		=  (  COMMON_PARAM  *  )p0;
	//
	QY_MESSENGER_ID		*  pIdInfo			=  (  QY_MESSENGER_ID  * )pCommonParam->p0;
	REFRESH_imObjRule_reqMem	*  pReqMem	=  (  REFRESH_imObjRule_reqMem  *  )pCommonParam->p1;
	//
	QY_imObjRule_rcd	*  pRcd				=  (  QY_imObjRule_rcd  *  )p1;
	QMEM_qyImObjRule	*  pQMem			=  (  QMEM_qyImObjRule  *  )p2;


	if  (  pQMem->ruleRcd.idInfo.ui64Id  ==  pIdInfo->ui64Id
		&&  pQMem->ruleRcd.idInfo_related.ui64Id  ==  pReqMem->idInfo_related.ui64Id
		&&  pQMem->ruleRcd.uiRuleType  ==  pReqMem->uiRuleType
		&&  pQMem->ruleRcd.usIndex  ==  pReqMem->usIndex  )
	{
		//  memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

		memcpy(  pRcd,  &pQMem->ruleRcd,  sizeof(  pRcd[0]  )  );

		iRet  =  1;  goto  errLabel;
	}

	iRet  =  0;
errLabel:
	return  iRet;


}

 //  2013/01/02//////
 BOOL  bGetImObjRuleRcdBySth_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem  *  pMem,  int  iRcdId,  QY_imObjRule_rcd  *  pRcd  )
{
	 BOOL			bRet		=		FALSE;
	 CMyDb		*   pDb			=  (  CMyDb  *  )pDbParam;
	 COMMON_PARAM  commonParam;

	 if  (  !misServName  ||  !pIdInfo  ||  !pIdInfo->ui64Id  ||  !pMem  ||  !pMem->idInfo_related.ui64Id  ||  !pRcd  )  return  FALSE;

	 MACRO_makeCommonParam3(  pIdInfo,  pMem,  NULL,  commonParam  );

	 if  (  qTraverse(  pDb->m_var.pQ_qyImObjRuleTab,  tmpHandler_bGetImObjRuleRcdBySth_myDb,  &commonParam,  pRcd  )  <=  0  )  goto  errLabel;


#if  0
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
				+	" id,misServName,idStr,uiRuleType,usIndex,idStr_related,uiCmd,startTime,tLastModifiedTime,iStatus,col0"
				+  " from "  +  pTabName
				+  " where "  +  whereBuf;
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
#endif
 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;
}

int  tmpHandler_bGetImObjRulesReq_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	COMMON_PARAM  *  pCommonParam  =  (  COMMON_PARAM  *  )p0;
	//
	QY_MESSENGER_ID  *  pIdInfo  =  (  QY_MESSENGER_ID  *  )pCommonParam->p0;
	QY_MESSENGER_ID  *  pIdInfo_related  =  (  QY_MESSENGER_ID  *  )pCommonParam->p1;
	//
	REFRESH_imObjRules_req		*  pReq  =  (  REFRESH_imObjRules_req  *  )p1;
	QMEM_qyImObjRule  *  pQMem  =  (  QMEM_qyImObjRule  *  )p2;

	if  (  (  pIdInfo  &&  pIdInfo->ui64Id  ?  pQMem->ruleRcd.idInfo.ui64Id  ==  pIdInfo->ui64Id  :  0  )
		||  (  pIdInfo_related  &&  pIdInfo_related->ui64Id  ?  pQMem->ruleRcd.idInfo_related.ui64Id  ==  pIdInfo_related->ui64Id  :  0   )
		||  (  (  pIdInfo_related  &&  pIdInfo_related->ui64Id  == 0  )  ?  1  :  0  )	 )
	{
		pReq->mems[pReq->usCnt].idInfo_related.ui64Id  =  pQMem->ruleRcd.idInfo_related.ui64Id;
		pReq->mems[pReq->usCnt].uiRuleType  =  pQMem->ruleRcd.uiRuleType;
		pReq->mems[pReq->usCnt].uiCmd  =  pQMem->ruleRcd.uiCmd;
		safeTcsnCpy(  pQMem->ruleRcd.col0,  pReq->mems[pReq->usCnt].wDesc,  mycountof(  pReq->mems[pReq->usCnt].wDesc  )  );

		pReq->usCnt  ++;
		if  (  pReq->usCnt  >=  mycountof(  pReq->mems  )  ||  (  pReq->usMaxMemsPerSnd  &&  pReq->usCnt  >=  pReq->usMaxMemsPerSnd  )  )
		{
			iRet  =  1;  goto  errLabel;
		}
	}

	iRet  =  0;
errLabel:
	return  iRet;

}

BOOL  bGetImObjRulesReq_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  QY_MESSENGER_ID	*	pIdInfo_related,  LPCTSTR  condPart,  unsigned  short  usMaxMemsPerSnd,  REFRESH_imObjRules_req  *  pReq  )
{
	 BOOL			bRet		=		FALSE;
	 CMyDb		*   pDb			=  (  CMyDb  *  )pDbParam;
	 COMMON_PARAM  commonParam;

	 if  (  !misServName  ||  !pReq  )  return  FALSE;

	 MACRO_makeCommonParam3(  pIdInfo,  pIdInfo_related,  NULL,  commonParam  );

	 memset(  pReq,  0,  sizeof(  pReq[0]  )  );
	 pReq->usMaxMemsPerSnd  =  usMaxMemsPerSnd;

	 if  (  qTraverse(  pDb->m_var.pQ_qyImObjRuleTab,  tmpHandler_bGetImObjRulesReq_myDb,  &commonParam,  pReq  )  <  0  )  goto  errLabel;

	 
	 bRet  =  TRUE;
errLabel:

	 return  bRet;
}

int  tmpHandler_idInfoExistedInImObjRegInfoTab_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iErr  =  -1;

	QY_MESSENGER_ID  *  pIdInfo  =  (  QY_MESSENGER_ID  *  )p0;
	// p1
	QMEM_qyImObjRegInfo  *  pQMem  =  (  QMEM_qyImObjRegInfo  *  )p2;

	if  (  pQMem->myRegInfo.addr.idInfo.ui64Id  ==  pIdInfo->ui64Id  ){

		iErr  =  1;  goto  errLabel;
	 }

	iErr  =  0;
errLabel:
	return  iErr;
}

BOOL  bIdInfoExistedInImObjRegInfoTab_myDb(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_ID  *  pIdInfo,  LPCTSTR  tabName  )
{
	 int						bRet										=	FALSE;
	 CMyDb					*	pDb											=	(  CMyDb  *  )pDbParam;

	 if  (  !pIdInfo  ||  !pIdInfo->ui64Id  )  return  FALSE;

	 if  (  !_tcsicmp(  pDb->m_var.pQ_qyImObjRegInfoTab->cfg.name,  tabName  )  )  {
		 if  (  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_idInfoExistedInImObjRegInfoTab_myDb,  pIdInfo,  0  )  <=  0  )  goto  errLabel;
	 }
	 else  if  (  !_tcscmp(  pDb->m_var.pQ_qyImObjRegInfoTab1->cfg.name,  tabName  )  )  {
		 if  (  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab1,  tmpHandler_idInfoExistedInImObjRegInfoTab_myDb,  pIdInfo,  0  )  <=  0  )  goto  errLabel;
	 }
	 else  goto  errLabel;

#if  0
	 CString					sqlStr;
	 CDBVariant					varVals[5];

	 void					*	pDb											=   pDbParam;

	 sqlStr  =  CString(  ""  )  +  _T(  "select idStr from "  ) +  tabName  +  _T(  " where idStr='"  )  +  CString(  idStr  )  +  _T(  "'"  );
	 if  (  !bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  
	 {	
		 iErr  =  0;  goto  errLabel;	
	 }
	 else  {
		 goto  errLabel;	
	 }
#endif
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


int  insertImObjRegInfo_qisRegUsrInfoInTab_myDb(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  )
{
	 int						iErr										=	-1;
	 CMyDb					*	pDb											=   (  CMyDb  *  )pDbParam;
	 QMEM_qyImObjRegInfo		qMem;

	 if  (  !pRegInfo  )  return  -1;

	 memset(  &qMem,  0,  sizeof(  qMem  )  );

	 qMem.myRegInfo.uiType  =  pRegInfo->uiType;
	 //  id
	 qMem.myRegInfo.iCustomId  =  pRegInfo->iCustomId;
	 
	 memcpy(  &qMem.myRegInfo.addr,  &pRegInfo->addr,  sizeof(  qMem.myRegInfo.addr  )  );
	 memcpy(  qMem.myRegInfo.uiFieldIds,  pRegInfo->uiFieldIds,  sizeof(  qMem.myRegInfo.uiFieldIds  )  );
	 memcpy(  qMem.myRegInfo.u.cols,  pRegInfo->u.cols,  sizeof(  qMem.myRegInfo.u.cols  )  );
	 
	 if  (  !_tcsicmp(  pDb->m_var.pQ_qyImObjRegInfoTab->cfg.name,  tabName  )  )  {
		 if  (  qPostMsg(  &qMem,  sizeof(  qMem  ),  pDb->m_var.pQ_qyImObjRegInfoTab,_T(  "insertImObjRegInfo_qisRegUsrInfoInTab"  )))  goto  errLabel;
	 }
	 else  if  (  !_tcscmp(  pDb->m_var.pQ_qyImObjRegInfoTab1->cfg.name,  tabName  )  )  {
		 if  (  qPostMsg(  &qMem,  sizeof(  qMem  ),  pDb->m_var.pQ_qyImObjRegInfoTab1,  _T(  "insertImObjRegInfo_qisRegUsrInfoInTab1"  )))  goto  errLabel;
	 }
	 else  goto  errLabel;

#if  0
	 CString					sqlStr;
	 int						i;
	 int						iQwmVer										=	0;
	 CDBVariant					varVals[5];
	 unsigned  char				ucbAudited									=	FALSE;
	 unsigned  char				ucbReged									=	FALSE;
	 TCHAR						tBuf[1024];
	 char						idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";

	 {
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

		 
		 iErr  =  0;  goto  errLabel;
	
	 }
#endif

	 iErr  =  0;
errLabel:
	 return  iErr;
}

int  tmpHandler_updateImObjRegInfo_qisRegUsrInfoInTab_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int						iErr	=	-1;

	QY_MESSENGER_REGINFO  *  pRegInfo  =  (  QY_MESSENGER_REGINFO  *  )p0;
	// p1
	QMEM_qyImObjRegInfo  *  pQMem  =  (  QMEM_qyImObjRegInfo  *  )p2;

	if  (  pQMem->myRegInfo.addr.idInfo.ui64Id  ==  pRegInfo->addr.idInfo.ui64Id  ){

		memcpy(  pQMem->myRegInfo.uiFieldIds,  pRegInfo->uiFieldIds,  sizeof(  pQMem->myRegInfo.uiFieldIds  )  );
		memcpy(  pQMem->myRegInfo.u.cols,  pRegInfo->u.cols,  sizeof(  pQMem->myRegInfo.u.cols  )  );

		iErr  =  1;  goto  errLabel;
	 }

	iErr  =  0;
errLabel:
	return  iErr;

}

int  updateImObjRegInfo_qisRegUsrInfoInTab_myDb(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  )
{
	 int						iErr										=	-1;
	 CMyDb					*	pDb											=   (  CMyDb  *  )pDbParam;

	 if  (  !pRegInfo  )  return  -1;

	 if  (  !_tcsicmp(  pDb->m_var.pQ_qyImObjRegInfoTab->cfg.name,  tabName  )  )  {
		 if  (  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_updateImObjRegInfo_qisRegUsrInfoInTab_myDb,  pRegInfo,  0  )  <  0  )  goto  errLabel;
	 }
	 else  if  (  !_tcscmp(  pDb->m_var.pQ_qyImObjRegInfoTab1->cfg.name,  tabName  )  )  {
		 if  (  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab1,  tmpHandler_updateImObjRegInfo_qisRegUsrInfoInTab_myDb,  pRegInfo,  0  )  <  0  )  goto  errLabel;
	 }
	 else  goto  errLabel;

#if  0
	 CString					sqlStr;
	 int						i;
	 int						iQwmVer										=	0;
	 CDBVariant					varVals[5];
	 unsigned  char				ucbAudited									=	FALSE;
	 unsigned  char				ucbReged									=	FALSE;
	 TCHAR						tBuf[1024];
	 char						idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";

	 void					*	pDb											=   pDbParam;
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
#endif
	 iErr  =  0;
errLabel:
	 return  iErr;
}

  //  2013/02/02
 BOOL  bGetMessengerPhoneInfoBySth_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiDevType,  LPCTSTR  wDevIdStr,  QY_MESSENGER_ID  *  pIdInfo,  int  id,  QY_MESSENGER_phoneInfo  *  pRcd  )
{
	 BOOL			bRet									=		FALSE;

	 if  (  !pDbParam  )  return  FALSE;
		

	//   bRet  =  TRUE;
errLabel:
	 return  bRet;

}
 int  recoverMessengerPhoneInfo_myDb(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  MSGR_ADDR  *  pAddr,  void  *  p1  )
{
	int							iErr									=		-1;

	//  iErr  =  0;
errLabel:

	if  (  iErr  )  {
#ifdef  __DEBUG__
		//traceLogA(  "recoverMessengerPhoneInfo failed"  );
#endif
	}
	return  iErr;

}

 //  2013/02/02
 //  pRegInfo->auditTime,qyPcRegInfoTab
 int  qisRegUsrInfo_myDb(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pMessengerInfo,  QY_MESSENGER_REGINFO  *  pRegInfo,  BOOL  bLogReRegEvent  )
{
	 int						iErr										=	-1;

	 if  (  qisRegUsrInfoInTab(  pDbFuncs,  pDb,  iDbType,  pFieldIdTable,  pMessengerInfo,  pRegInfo,  CONST_tabName_qyImObjRegInfoTab  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

#ifdef  __DEBUG__
	 //traceLogA(  "qisRegUsrInfo leaves"  );
#endif

	 return  iErr;

}



 //int  qnmRegUsrInfo_myDb(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo  )
 int  qnmRegUsrInfo_myDb(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo  )
 {
	 return  -1;

 }

 //
 int  tmpHandler_selectImMsg_logImMsg_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;

	IM_MSG_RCD  *  pRcd  =  (  IM_MSG_RCD  *  )p1;
	IM_MSG_RCD  *  pQMem  =  (  IM_MSG_RCD  *  )p2;

	if  (  pQMem->idInfo_send.ui64Id  ==  pRcd->idInfo_send.ui64Id
		&&  pQMem->tSendTime  ==  pRcd->tSendTime
		&&  pQMem->uiTranNo  ==  pRcd->uiTranNo
		&&  pQMem->uiSerialNo  ==  pRcd->uiSerialNo  )
	{
		pRcd->id  =  pQMem->id;
		iRet  =  1;  goto  errLabel;
	}


	iRet  =  0;
errLabel:
	return  iRet;
}

 BOOL  bSelectImMsg_logImMsg_myDb(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  )
{
	BOOL			bRet											=	FALSE;
	CMyDb		*	pMyDb											=  (  CMyDb  *  )pDb;

	if  (  qTraverse(  pMyDb->m_var.pQ_qyImMsgTab,  tmpHandler_selectImMsg_logImMsg_myDb,  NULL,  pRcd  )  <=  0  )  goto  errLabel;
#if  0
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
	if  (  bQyGetRcdBySql(  pDb,  sqlBuf,  mycountof(  varVals  ),  varVals  )  )  {
		iErr  =  0;  goto  errLabel;
	}	
#endif
	bRet  =  TRUE;
errLabel:
	return  bRet;

}


 int  insertImMsg_logImMsg_myDb(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  )
{
	int				iErr											=	-1;
	CMyDb		*	pMyDb											=	(  CMyDb  *  )pDb;

	if  (  qPostMsg(  pRcd,  sizeof(  pRcd[0]  ),  pMyDb->m_var.pQ_qyImMsgTab,  _T(  "insertImMsg_logImMsg"  )))  goto  errLabel;
#if  0
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

	if  (  !idInfo2Str(  &pRcd->idInfo_send,  idStr_send,  mycountof(  idStr_send  )  )  )  goto  errLabel;
	getTimeStr(  pRcd->tSendTime,  sendTime,  mycountof(  sendTime  )  );


	getTimeStr(  pRcd->tStartTime_serv,  tStartTime_serv,  mycountof(  tStartTime_serv  )  );
	if  (  !idInfo2Str(  &pRcd->idInfo_recv,  idStr_recv,  mycountof(  idStr_recv  )  )  )  goto  errLabel;
	getTimeStr(  (  time_t  )pRcd->tRecvTime,  recvTime,  mycountof(  recvTime  )  );
	getTimeStr(  pRcd->firstTime,  firstTime,  mycountof(  firstTime  )  );
	getTimeStr(  pRcd->lastTime,  lastTime,  mycountof(  lastTime  )  );
	getTimeStr(  pRcd->tLastModifiedTime,  lastModifiedTime,  mycountof(  lastModifiedTime  )  );

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
#endif
	iErr  =  0;
errLabel:
	return  iErr;

}
  BOOL  bGetImMsgRcdBySth_myDb(  void  *  pDbParam,  int  iDbType,  int  id,  IM_MSG_RCD  *  pObj  )
 {
	 return FALSE;
 }


  ///
  int  tmpHandler_bGetQyDynBmpRcdBySth_myDb(  void  *  p0,  void  *  p1,  QMEM_qyDynBmp  *  pMem  )
  {
	  int	iErr	=	-1;
	  QY_dynBmp_RCD  *  pInput  =  (  QY_dynBmp_RCD  *  )p0;
	  QY_dynBmp_RCD  *  pOutput  =  (  QY_dynBmp_RCD  *  )p1;

	  if  (  pMem->dynBmpRcd.idInfo.ui64Id  ==  pInput->idInfo.ui64Id
		  &&  pMem->dynBmpRcd.uiObjType  ==  pInput->uiObjType
		  &&  pMem->dynBmpRcd.usIndex  ==  pInput->usIndex  )
	  {
		  memcpy(  pOutput,  pMem,  sizeof(  QY_dynBmp_RCD  )  );
		  iErr  =  1;  goto  errLabel;
	  }

	  iErr  =  0;
errLabel:
	  return  iErr;
  }

 BOOL  bGetQyDynBmpRcdBySth_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex,  int  id,  QY_dynBmp_RCD  *  pRcd  )
 {
	 BOOL  bRet  =  FALSE;
	 CMyDb				*	pDb	=	(  CMyDb  *  )pDbParam;
	 
	 QMEM_qyDynBmp			qMem;
	 QY_dynBmp_RCD			input;
	 
	 
	 memset(  &input,  0,  sizeof(  input  )  );	 
	 if  (  misServName  &&  bMessengerIdValid(  pIdInfo  )  &&  uiObjType  )  {
		 input.idInfo.ui64Id  =  pIdInfo->ui64Id;
		 input.uiObjType  =  uiObjType;
		 input.usIndex  =  usIndex;
		 }
	 else  {
		   input.id  =  id;
	 }
	 
	 //
	 if  (  qTraverse(  pDb->m_var.pQ_qyDynBmpTab,  (  PF_commonHandler  )tmpHandler_bGetQyDynBmpRcdBySth_myDb,  &input,  &qMem  )  <=  0  )  goto  errLabel;

	 bRet  =  TRUE;

errLabel:

	 return  bRet;
 }


int  auditNewMessenger_myDb(  void  *  pReserved,  QY_MESSENGER_ID  *  pLastIdInfo,  void  *  pLicenseCtx,  void  *  pDb,  int  iDbType,  POLICY_imAuthCond  *  pAuthCond,  QY_MESSENGERAUTHTMP_RCD  *  pNewMessenger  )
{
	return  -1;
}



BOOL  bGetPcInfoByMac_myDb(  void  *  pDbParam,  char  *  mac,  unsigned  char  ucbMac0,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo  )
{
	 return FALSE;
}

BOOL  bGetPcInfoByMacEx_myDb(  void  *  pDbParam,  char  *  mac,  unsigned  char  ucbMac0,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo,  QNM_REG_INFO  *  pRegInfoInTab1  )
{
	 return FALSE;
}
 BOOL  bLogEventFunc_is_myDb(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QIS_EVENT  *  pEvent  )
{
	 return FALSE;
}
 int  getEventInfoBySth_myDb(  void  *  pDbParam,  int  iDbType,  QIS_EVENT  *  pEvent  )
{
	return  -1;
}
  int  getPcEventInfoByMac0_myDb(  void  *  pDbParam,  QNM_PC_EVENT  *  pEvent  )
{
	return  -1;
}
 BOOL  bLogPcEventFunc_myDb(  void  *  pDb,  int  iDbType,  QNM_PC_EVENT  *  pEvent  )
{
	 return FALSE;
}
 int  qisRegOtherInfoInTab_myDb(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  MSGR_ADDR  *  pAddr,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  )
{
	return  -1;
}






