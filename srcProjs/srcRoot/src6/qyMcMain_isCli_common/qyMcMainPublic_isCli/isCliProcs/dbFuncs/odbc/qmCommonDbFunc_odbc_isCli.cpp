

#include	"stdafx.h"

#include	<stdio.h>

#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
	#include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>

#include	"qyMcMainCommon.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcDynBmp.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	"myresource.h"

#include	"qyOpenShellCommon.h"
//#include	"DlgObjs_ts.h"
#include	"dlgobjsproc.h"
#include	"dlgTalkProc.h"

//  #include	"qwmDynFunc.h"

#include	"qmcCmdProc.h"

#include	"tmpCeLib.h"
#include	"qySqlFunc.h"

#include	"myresource.h"
#include	"myDb.h"

#include	"qyCusResTemp.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
//
#include	"ctxMcThread.h"



BOOL  bRefreshAllContacts(  MIS_CNT  *  pMisCnt  );
BOOL  bMessengerRegInfoSame(  QY_MESSENGER_REGINFO  *  pRegInfo0,  QY_MESSENGER_REGINFO  *  pRegInfo1  );

#if  0
  int  tmpHandler_mcProcCmd_refreshAllImGrps(  void  *  p0,  void  *  p1,  void  *  p2  )
{
#ifdef  __NOTSUPPORT_DB__
		return  -1;
#else
	 int								iErr			=	-1;
	 QY_MC							*	pQyMc			=	QY_GET_GBUF(  );
	 COMMON_PARAM					*	pCommonParam0	=	(  COMMON_PARAM  *  )p0;
	 COMMON_PARAM					*	pCommonParam1	=	(  COMMON_PARAM  *  )p1;
	 CDBVariant						*	pVarVals		=	(  CDBVariant  *  )p2;
	 //
	 MT_SUBTHREADINFO				*	pSubThreadInfo	=	(  MT_SUBTHREADINFO  *  )pCommonParam0->p0;
	 QY_SERVICEGUI_INFO				*	pSci			=	(  QY_SERVICEGUI_INFO  *  )pCommonParam0->p1;
	 MIS_CNT						*	pMisCnt			=	(  MIS_CNT  *  )pCommonParam0->p2;
	 RETRIEVE_IMGRPLIST_RESP		*	pUpdateInfos	=	(  RETRIEVE_IMGRPLIST_RESP  *  )pCommonParam1->p0;
	 TRAN_INFO_MIS					*	pTranInfo		=	(  TRAN_INFO_MIS  *  )pCommonParam1->p1;
	 //  p2
	 //
	 MC_VAR_isCli						*	pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;
	 //
	 TCHAR								tBuf[256];
	 int								index			=	0;
	 char								buf[256];
	 IM_GRP_INFO						updateInfo;
	 int								id;
	 //
	 TCHAR								sqlBuf[1024];
	 int								iStatus;
	 //
	 void							*	pDb					=	NULL;		//  2011/08/02
	 CQnmDb	db;
	 //
	 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
	 pDb  =  db.m_pDbMem->pDb;


	 memset(  &updateInfo,  0,  sizeof(  updateInfo  )  );

	 //  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select A.id,A.idStr,A.iStatus,qyImGrpInfoTab.name"  )

	 index  =  0;
	 MACRO_sqlLong(  pVarVals[index],  id  );
	 index  ++  ;	//  idStr
	 MACRO_sqlStr(  pVarVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &updateInfo.idInfo  );
	 index  ++  ;	//  iStatus
	 MACRO_sqlLong(  pVarVals[index],  iStatus  );
	 index  ++  ;	//  name
	 MACRO_sqlStr(  pVarVals[index],  updateInfo.name,  mycountof(  updateInfo.name  )  );  
	 index  ++  ;
	 
	 //
	 for  (  ;  pUpdateInfos->index  <  pUpdateInfos->usCnt;  pUpdateInfos->index  ++  )  {

			   if  (  pUpdateInfos->mems[pUpdateInfos->index].idInfo.ui64Id  <  updateInfo.idInfo.ui64Id  )  {
				   //  ÐÂÔöµÄ
				   if  (  recoverImGrp(  pDb,  pSci->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_objType_imGrp,  &pUpdateInfos->mems[pUpdateInfos->index],  pMisCnt->refreshContactList.tStartTime  )  )  {
					   traceLogA(  "recoverImGrp(  ) failed"  );  goto  errLabel;
				   }
				   continue;
			   }
			   if  (  pUpdateInfos->mems[pUpdateInfos->index].idInfo.ui64Id  >  updateInfo.idInfo.ui64Id  )  {

				   //  ÕâÀïÓ¦¸ÃÊÇÒªÉ¾³ýµÄimGrp
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyImObjTab set iStatus=%d where id=%d"  ),  CONST_qyStatus_del,  id  );
				   if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  {
					   traceLogA(  "ÉèÖÃmessengerÉ¾³ý±êÖ¾Î»Ê§°Ü"  );  goto  errLabel;
				   }				   
				   iErr  =  0;  goto  errLabel;		//  ÈÃ¼ÇÂ¼Ö¸ÏòÏÂÒ»¸ö
			   }			

			   //  ÒªÊÇÏëÍ¬µÄ»°£¬¾Í¸üÐÂ
			   if  (  lstrcmpi(  updateInfo.name,  pUpdateInfos->mems[pUpdateInfos->index].name  )  ||  iStatus  !=  CONST_qyStatus_ok  )  {
				   if  (  recoverImGrp(  pDb,  pSci->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_objType_imGrp,  &pUpdateInfos->mems[pUpdateInfos->index],  pMisCnt->refreshContactList.tStartTime  )  )  {
					   traceLogA(  "recoverImGrp(  ) failed"  );  goto  errLabel;
				   }
			   }

			   			   
			   pUpdateInfos->index  ++  ;	//  ÈÃ´¦ÀíµÄupdateInfoÖ¸ÏòÏÂÒ»¸ö

			   break;

	 }

	 if  (  pUpdateInfos->index  ==  pUpdateInfos->usCnt  )  {	
		 traceLogA(  "±íÃ÷ÕâÒ»Åú´¦ÀíÍêÁË"  );
		 iErr  =  1;  goto  errLabel;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
#endif
}

 //
int  mcProcResp_refreshImGrps_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_IMGRPLIST_RESP  *  pResp,  void  *  pCtxParam  )
{
	int									iErr													=	-1;
	MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	QY_SERVICEGUI_INFO				*	pSci													=	(  QY_SERVICEGUI_INFO  *  )pSciParam;
	MIS_CNT							*	pMisCnt													=	(  MIS_CNT  *  )pMisCntParam;
	CTX_MC_THREAD					*	pCtx													=	(  CTX_MC_THREAD  *  )pCtxParam;

	QY_MC							*	pQyMc													=	QY_GET_GBUF(  );
	MC_VAR_isCli						*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	 int  i;

#ifdef  __NOTSUPPORT_DB__
	    QY_MESSENGER_INFO			obj;
		QM_OBJQ_MEM					mem;
		QMEM_MESSENGER_CLI	*		pQMem;

		for  (  i  =  0;  i  <  pResp->usCnt;  i  ++  )  {

			 lstrcpyn(  obj.misServName,  pMisCnt->cfg.misServName,  mycountof(  obj.misServName  )  );
			 obj.uiType  =  CONST_objType_imGrp;
			 obj.idInfo.ui64Id  =  pResp->mems[i].idInfo.ui64Id;

			 if  (  procQmObjQ(  pSci,  (  QM_OBJQ  *  )pMisCnt->pObjQ,  NULL,  0,  obj.uiType,  &obj,  &mem  )  )  goto  errLabel;
			 if  (  !mem.pQMemObj  )  goto  errLabel;
		
			 pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
			 if  (  pQMem  )  {
				 grpInfo2Desc(  0,  &pResp->mems[i],  pQMem->talkerDesc,  mycountof(  pQMem->talkerDesc  ),  pQMem->displayName,  mycountof(  pQMem->displayName  )  );
			}

		}			

#else
	TCHAR								sqlBuf[1024];
	 CDBVariant							varVals[50];
	 COMMON_PARAM						commonParam0;
	 COMMON_PARAM						commonParam1;
	 TRAN_INFO_MIS						tranInfo;

	 char								idStr_lastRefreshed[CONST_qyMessengerIdStrLen  +  1]	=	"";
	 int								tmpiRet;

	 unsigned  int						uiObjType	=	CONST_objType_imGrp;

	if  (  pResp->idInfo_lastRefreshed.ui64Id  )  {
		if  (  !idInfo2Str(  &pResp->idInfo_lastRefreshed,  idStr_lastRefreshed,  mycountof(  idStr_lastRefreshed  )  )  )  goto  errLabel;
	}
	
	if  (  !bRefreshAllContacts(  pMisCnt  )  )  {  //  ÕâÀïÊÇÔöÁ¿Ë¢ÐÂ
		//
		for  (  i  =  0;  i  <  pResp->usCnt;  i  ++  )  {

			if  (  recoverImGrp(  pSubThreadInfo->pDb,  pSci->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  uiObjType,  &pResp->mems[i],  pMisCnt->refreshContactList.tStartTime  )  )  {
				 traceLogA(  "recoverImGrp(  ) failed"  );  goto  errLabel;
			 }			   
		}
		//
		}
	else  {  //  È«ÃæË¢ÐÂ
		   
		   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select A.id,A.idStr,A.iStatus,qyImGrpInfoTab.name"  )
													     _T(  " from qyImObjTab as A left join qyImGrpInfoTab on (A.misServName=qyImGrpInfoTab.misServName and A.idStr=qyImGrpInfoTab.idStr) where A.misServName=%s and A.uiType in(%d)"  ),  getDbValStr(  pSci->cfg.iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  uiObjType  );
 
		   if  (  idStr_lastRefreshed[0]  )  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and A.idStr>'%s'"  ),  sqlBuf,  CQyString(  idStr_lastRefreshed  )  );
		   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s %s"  ),  sqlBuf,  _T(  "order by A.idStr"  )  );
		   OutputDebugString(  sqlBuf  );  OutputDebugString(  _T(  "\n"  )  );
	 	 	   
		   memset(  &tranInfo,  0,  sizeof(  tranInfo  )  );
		   MACRO_makeCommonParam3(  pSubThreadInfo,  pSci,  pMisCnt,  commonParam0  );
		   MACRO_makeCommonParam3(  pResp,  &tranInfo,  0,  commonParam1  );
		   tmpiRet  =  enumSqlQuery(  pSubThreadInfo->pDb,  sqlBuf,  tmpHandler_mcProcCmd_refreshAllImGrps,  &commonParam0,  &commonParam1,  varVals,  mycountof(  varVals  ),  NULL  );
		   if  (  tmpiRet  <  0  )  goto  errLabel;
	 	   
		   if  (  !tmpiRet  )  {	//  
			   //  ÕâÀïÒª´¦ÀíÊý¾ÝÖÐÒÑ¾­²éÑ¯ÍêÁË£¬µ«ÊÇÈÔÈ»ÁôÏÂÀ´´óÁ¿µÄÐÂ½Úµã

			   for  (  ;  pResp->index  <  pResp->usCnt;  pResp->index  ++  )  {
			   
				   if  (  recoverImGrp(  pSubThreadInfo->pDb,  pSci->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  uiObjType,  &pResp->mems[pResp->index],  pMisCnt->refreshContactList.tStartTime  )  )  {
						traceLogA(  "recoverImGrp(  ) failed"  );  goto  errLabel;			
					}
					//
			   }
		   }
	}

#endif

	iErr  =  0;

errLabel:

	return  iErr;

}
#endif



int  updateImObj_refreshImGrps_end_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiObjType,  time_t  tLastModifiedTime  )
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

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyImObjTab set iStatus=%d where misServName=%s and uiType in(%d) and tLastModifiedTime<>'%s'"  ),  
			CONST_qyStatus_del,  
			getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  
			CONST_objType_imGrp,
			CQyString(  tLastModifiedTimeBuf  )  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	iErr =  0;
errLabel:

	return  iErr;

}




 BOOL	bNeedRetrieveImGrpMems_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName  )
{
	BOOL	bRet	=	FALSE;
#ifndef  __NOTSUPPORT_DB__
		 TCHAR								sqlBuf[1024];

		 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(A.idStr) from qyImObjTab as A where A.misServName=%s and A.uiType in (%d) and A.iStatus<>%d"  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CONST_objType_imGrp,  CONST_qyStatus_del  );
		 OutputDebugString(  sqlBuf  );  OutputDebugString(  _T(  "\n"  )  );
		 if  (  bSqlObjExists(  pDb,  sqlBuf  )  )  bRet  =  TRUE;
#else
		 //  暂时在ce里不考虑处理分组成员信息
#endif
	return  bRet;		 
}






//
int  updateImGrpMem_refreshImGrpMems_end_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  time_t  tLastModifiedTime  )
{
	int								iErr											=	-1;
	TCHAR							sqlBuf[CONST_maxSqlBufLen  +  1];
	time_t							t;
	char							startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	char							tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";

	if  (  !tLastModifiedTime  )  time(  &t  );
	else  t  =  tLastModifiedTime;
	getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );

	
#if  0	//  2014/02/08
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyImGrpMemTab set iStatus=%d where misServName=%s and tLastModifiedTime<>'%s'"  ), 
				CONST_qyStatus_del,  
				getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  
				CQyString(  tLastModifiedTimeBuf  )  );
#endif
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyImGrpMemTab set iStatus=%d where tLastModifiedTime<>'%s'"  ), 
				CONST_qyStatus_del,  
				CQyString(  tLastModifiedTimeBuf  )  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	iErr =  0;
errLabel:

	return  iErr;

}

//
//  2013/02/02. 要注意,要清理的时候要把me排除在外.因为me的更新在startchannel里也有. 
int  updateImObj_refreshContacts_end_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  time_t  tLastModifiedTime  )
{
	int								iErr											=	-1;
	TCHAR							sqlBuf[CONST_maxSqlBufLen  +  1];
	time_t							t;
	char							startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	char							tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";

	if  (  !tLastModifiedTime  )  time(  &t  );
	else  t  =  tLastModifiedTime;
	getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );
	
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyImObjTab set iStatus=%d where misServName=%s and uiType not in(%d,%d)"  ),  CONST_qyStatus_del,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CONST_objType_imGrp,  CONST_objType_me  );	
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and tLastModifiedTime<>'%s'"  ),  sqlBuf,  CQyString(  tLastModifiedTimeBuf  )  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;

}




 int  deleteOldImObjRule_mcProcResp_refreshImObjRulesReq_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  MIS_MSG_INPUT  *  pMsgInput,  void  *  pCtxParam  )
 {
	 int								iErr													=	-1;
	 MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_SERVICEGUI_INFO  *  pSci																=	(  QY_SERVICEGUI_INFO  *  )pSciParam;
	 MIS_CNT  *  pMisCnt																		=	(  MIS_CNT  *  )pMisCntParam;
	 CTX_MC_scheduler  *  pCtx																	=	(  CTX_MC_scheduler  *  )pCtxParam;

	 //  QY_MC							*	pQyMc													=	QY_GET_GBUF(  );
	 //  MC_VAR_isCli					*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	 //  
	 //  IM_CONTENTU					*	pContent												=	NULL;
	 
	 //  int								iDbType													=	pQyMc->cfg.db.iDbType;

	 TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]						=	_T(  ""  );
	 //  CDBVariant							varVals[64];
	 char								timeBuf[128]											=	"";
		 //
	 getTimeStr(  pMisCnt->refreshImObjRules.tStart_toRetrieveAll,  timeBuf,  mycountof(  timeBuf  )  );
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where tLastModifiedTime<>'%s'"  ),  CONST_tabName_qyImObjRuleTab,  CQyString(  timeBuf  )  );
	 if  (  !bQyExecSql(  pSubThreadInfo->pDb,  sqlBuf  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:
	 return  iErr;
}










 //  2013/02/05
 int  updateTaskStatus_odbc(  void  *  pDb,  int  iStatus,  int  iTaskId  )
{
#ifdef  __NOTSUPPORT_DB__
		int			iErr	=	-1;
		QY_MC	*	pQyMc  =  QY_GET_GBUF(  );
		QY_SERVICEGUI_INFO		*	pSci								=	NULL;
		pSci			=	getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
		if  (  !pSci  )  goto  errLabel;
		MC_VAR_isCli  *  pProcInfo		=	(  MC_VAR_isCli  *  )pSci->pVar;
		if  (  !pProcInfo  )  goto  errLabel;

		int				tmpiRet		=	-1;

		tmpiRet  =  qTraverse(  &pProcInfo->memTaskQ,  (  PF_commonHandler  )tmpHandler_updateTaskStatus,  (  void  *  )iStatus,  (  void  *  )iTaskId  );
		if  (  tmpiRet  <  0  )  goto  errLabel;
		iErr  =  0;
errLabel:
		return  iErr;
#else
	TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );

	if  (  !pDb  )  return  -1;

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set iStatus=%d where id=%d"  ),  CONST_tabName_qyImTaskTab,  iStatus,  iTaskId  );
	
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  return  -1;
	return  0;
#endif
}








  //  2013/02/06
 BOOL  bGetImTaskRcdBySth_odbc(  void  *  pDb,  int  iDbType,  BOOL  bHisTab,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  time_t  tSendTime,  unsigned  int  uiTranNo,  int  id,  IM_TASK_RCD  *  pRcd  )
{
	 BOOL			bRet								=	FALSE;
	 TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	 TCHAR			whereClause[256]					=	_T(  ""  );
	 unsigned  int	uiRcdCnt							=	0;


	 if  (  misServName  &&  pIdInfo  )  {
		 char	timeBuf[CONST_qyTimeLen  +  1]	=	"";
		 char	idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";
		 //
		 getTimeStr(  tSendTime,  timeBuf,  mycountof(  timeBuf  )  );
		 idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  );
		 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "misServName=%s and idStr_send='%s' and tSendTime='%s' and uiTranNo=%d"  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CQyString(  idStr  ),  CQyString(  timeBuf  ),  uiTranNo  );
		}
	 else  {
		   _sntprintf(  whereClause,  mycountof(  whereClause ),  _T(  "id =%d"  ),  id  );
	 }

	 if  (  enumImTasks(  pDb,  iDbType,  bHisTab,  misServName,  whereClause,  NULL,  0,  0,  &uiRcdCnt,  pRcd  )  )  goto  errLabel;
	 if  (  !uiRcdCnt  )  goto  errLabel;
	

	 bRet   =  TRUE;

errLabel:

	 return  bRet;
}
 






  //  2013/02/17
 BOOL  bViewImTaskList_unproced_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet										=	FALSE;
	QY_MC				*	pQyMc										=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp	*	pFuncs										=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;
	TCHAR					whereClause[CONST_maxSqlBufLen  +  1]		=	_T(  ""  );

	_sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "(T.iStatus in(%d,%d,%d,%d,%d,%d,%d,%d))"  ), 
															CONST_imTaskStatus_req,
															CONST_imTaskStatus_resp,
															CONST_imTaskStatus_applyToSend,
															CONST_imTaskStatus_waitToSend,
															CONST_imTaskStatus_applyToRecv,
															CONST_imTaskStatus_waitToRecv,
															CONST_imTaskStatus_sending,
															CONST_imTaskStatus_receiving
															);
	if  (  wherePart  &&  wherePart[0]  )  _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s and (%s)"  ),  whereClause,  wherePart  );

	bRet  =  pFuncs->pf_bViewImTaskListFunc(  pQyMc,  pObjDb,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unfinished  ),  whereClause,  FALSE  );

	return  bRet;
}


 BOOL  bViewImTaskList_cur_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
 {
	 BOOL	bRet	=	FALSE;
	QY_MC				*	pQyMc										=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp	*	pFuncs										=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	 bRet  =  pFuncs->pf_bViewImTaskListFunc(  pQyMc, pObjDb,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unfinished  ),  wherePart,  FALSE  );

	 return  bRet;
 }

  BOOL  bViewImTaskList_his_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
 {
	 BOOL	bRet	=	FALSE;
	QY_MC				*	pQyMc										=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp	*	pFuncs										=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	 bRet  =  pFuncs->pf_bViewImTaskListFunc(  pQyMc,  pObjDb,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unfinished  ),  wherePart,  TRUE  );

	 return  bRet;
 }

 BOOL  bViewImObjList_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )		//  2014/04/17
{
	 BOOL	bRet	=	FALSE;
	QY_MC				*	pQyMc										=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp	*	pFuncs										=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	bRet  =  pFuncs->pf_bViewImObjListFunc(  pQyMc,  pObjDb,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyMessengerList  ),  wherePart  );

	 return  bRet;
}

  BOOL  bViewRegInfoList_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )		//  2014/04/17
{
	 BOOL	bRet	=	FALSE;
	QY_MC				*	pQyMc										=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp	*	pFuncs										=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	bRet  =  pFuncs->pf_bViewMessengerRegInfoList(  pQyMc,  pObjDb  );

	 return  bRet;
}


 BOOL  bViewImGrpList_odbc(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )		//  2014/04/17
{
	 BOOL	bRet	=	FALSE;
	//QY_MC				*	pQyMc										=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp	*	pFuncs										=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	bRet  =  pFuncs->pf_bViewImGrpList(  pQyMc,  pObjDb,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyImGrpList  ),  wherePart  );

	 return  bRet;
}
 BOOL  bViewImGrpMemList_isClient_odbc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
 {
	 BOOL	bRet	=	FALSE;
	QY_MC				*	pQyMc										=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp	*	pFuncs										=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	bRet  =  pFuncs->pf_bViewImGrpMemList_isClient(   pQyMc,  pObjDb,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyImGrpList  ),  wherePart  );

	 return  bRet;
 }


 BOOL  bViewImObjRuleList_is_odbc(  QY_OBJ_DB  *  pObjDb  )
 {
	BOOL	bRet	=	FALSE;
	QY_MC				*	pQyMc										=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp	*	pFuncs										=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	bRet  =  pFuncs->pf_bViewImObjRuleList_is(   pQyMc,  pObjDb  );

	 return  bRet;

 }


 //
 BOOL  bInsertPhoneGuest_procMsgTalk_work_odbc(  void  *  pDb,  int  iDbType,  void  *  pQyMcParam,  MIS_MSG_TALK  *  pMsg,  void  *  pGuestParam  )
{
	BOOL  bRet  =  FALSE;
	QY_MC			*	pQyMc								=	(  QY_MC  *  )pQyMcParam;
	MIS_CNT			*	pMisCnt								=	(  MIS_CNT  *  )pMsg->pMisCnt;
	char				timeBuf[CONST_qyTimeLen  +  1]		=	"";

	IS_GUEST_ELEM	*	pGuest								=  (  IS_GUEST_ELEM  *  )pGuestParam;

	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1];
	
#if  0
					  getCurTime(  timeBuf  );
					  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,uiDevType,wDevIdStr,iStatus,startTime,tLastModifiedTime) values(%s,%d,%s,%d,'%s','%s')"  ),
																		CONST_tabName_qyPhoneGuestTab,
																		getDbValStr(  iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  
																		guest.uiDevType,  
																		getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  guest.wDevIdStr  ),
																		0,
																		CQyString(  timeBuf  ),
																		CQyString(  timeBuf  )  );
					  if  (  !bQyExecSql(  db.m_pDbMem->pDb,  sqlBuf  )  )  goto  errLabel;
#endif 

	getCurTime(  timeBuf  );					  
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,uiDevType,wDevIdStr,iStatus,startTime,tLastModifiedTime) values(%s,%d,%s,%d,'%s','%s')"  ),
														CONST_tabName_qyPhoneGuestTab,
														getDbValStr(  iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  
														pGuest->uiDevType,  
														getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  pGuest->wDevIdStr  ),
														0,
														CQyString(  timeBuf  ),
														CQyString(  timeBuf  )  );

	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
	
	bRet  =  TRUE;
errLabel:
	 return  bRet;
}


BOOL  bUpdateImTask_bChkQyMcEnv_mis_odbc(  void  *  pDb,  int  iStatus_set,  int  iStatus_0,  int  iStatus_1  )
{
	BOOL  bRet  =  FALSE;
	TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );

#if  0
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set iStatus=%d where iStatus=%d or iStatus=%d"  ),  CONST_tabName_qyImTaskTab,  CONST_imTaskStatus_sendBreak,  CONST_imTaskStatus_applyToSend,  CONST_imTaskStatus_waitToSend  );
	if  (  !bQyExecSql(  db.m_pDbMem->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set iStatus=%d where iStatus=%d or iStatus=%d"  ),  CONST_tabName_qyImTaskTab,  iStatus_set,  iStatus_0,  iStatus_1  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	bRet  =  TRUE;

errLabel:
	return  bRet;
}

//int  deleteDynBmp_tmpHandler_delOld_dynBmpQ_odbc(  void  *  pDb,  int  id  )
int  deleteOldDynBmp_mcProcResp_retrieveDynBmps_odbc(  void  *  pDb,  int  iDbType,  char  *  pTimeBuf  )
{
	int  iRet  =  -1;
	CQyString		sqlStr;
	char		buf[128];

	sqlStr  =  CQyString(  "delete from "  )  +  CQyString(  CONST_tabName_qyDynBmpTab  )  +  CQyString(  " where endTime<>'"  );
	sqlStr  +=    pTimeBuf;
	sqlStr  +=  _T(  "'"  );
	
	if  (  !bQyExecSql(  pDb,  sqlStr  )  )  goto  errLabel;

	iRet  =  0;
errLabel:
	return  iRet;
}



 BOOL  bInsertDynBmp_mcProcResp_retrieveDynBmps_odbc(  void  *  pDb,  void  *  pMisCntParam,  QIS_dynBmp_info  *  pMem,  char  *  pTimeBuf  )
{
	 BOOL  bRet  =  FALSE;
	 MIS_CNT						*	pMisCnt													=	(  MIS_CNT  *  )pMisCntParam;
	 QY_MC							*	pQyMc													=	QY_GET_GBUF(  );
	 int								iDbType													=	pQyMc->cfg.db.iDbType;
	 TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]						=	_T(  ""  );
	 
	 char								idStr[CONST_qyMessengerIdStrLen  +  1];

	 idInfo2Str(  &pMem->qisResObj.idInfo,  idStr,  mycountof(  idStr  )  );


#if  0
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr,uiObjType,usIndex,name,cusname,iStatus,startTime,endTime) values(%s,'%s',%d,%d,%s,%s,%d,'%s','%s')"  ),  
					  CONST_tabName_qyDynBmpTab,
					  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),
					  CQyString(  idStr  ).GetBuffer(  0  ),
					  pMem->uiObjType,
					  pMem->usIndex,
					  getDbValStr(  iDbType,  CONST_iDataType_name,  pMem->name  ),
					  getDbValStr(  iDbType,  CONST_iDataType_name,  pMem->cusName  ),
					  0,
					  CQyString(  timeBuf  ).GetBuffer(  0  ),
					  CQyString(  timeBuf  ).GetBuffer(  0  )  );				  
			  if  (  !bQyExecSql(  pSubThreadInfo->pDb,  sqlBuf  )  )  goto  errLabel;
#endif

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr,uiObjType,usIndex,name,cusname,iStatus,startTime,endTime) values(%s,'%s',%d,%d,%s,%s,%d,'%s','%s')"  ),  
					  CONST_tabName_qyDynBmpTab,
					  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),
					  CQyString(  idStr  ).GetBuffer(  0  ),
					  pMem->qisResObj.resObj.uiObjType,
					  pMem->qisResObj.resObj.usIndex_obj,
					  getDbValStr(  iDbType,  CONST_iDataType_name,  pMem->name  ),
					  getDbValStr(  iDbType,  CONST_iDataType_name,  pMem->cusName  ),
					  0,
					  CQyString(  pTimeBuf  ).GetBuffer(  0  ),
					  CQyString(  pTimeBuf  ).GetBuffer(  0  )  );				  
			  
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;


	 bRet  =  TRUE;

errLabel:
	 return  bRet;
}

 BOOL  bUpdateDynBmp_mcProcResp_retrieveDynBmps_odbc(  void  *  pDb,  QIS_dynBmp_info  *  pMemParam,  char  *  pTimeBuf,  int  rcdId  )
{
	 BOOL  bRet  =  FALSE;
	 QIS_dynBmp_info					*	pMem													=	(  QIS_dynBmp_info	*	)pMemParam;
	 QY_MC							*	pQyMc													=	QY_GET_GBUF(  );
	 int								iDbType													=	pQyMc->cfg.db.iDbType;
	 TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]						=	_T(  ""  );

#if  0
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set name=%s,cusName=%s where id=%d"  ),  
					  CONST_tabName_qyDynBmpTab,  
					  getDbValStr(  iDbType,  CONST_iDataType_name,  pMem->name  ),
					  getDbValStr(  iDbType,  CONST_iDataType_name,  pMem->cusName  ),
					  rcd.id  );
		  if  (  !bQyExecSql(  pSubThreadInfo->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
	  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set name=%s,cusName=%s,endTime='%s' where id=%d"  ),  
					  CONST_tabName_qyDynBmpTab,  
					  getDbValStr(  iDbType,  CONST_iDataType_name,  pMem->name  ),
					  getDbValStr(  iDbType,  CONST_iDataType_name,  pMem->cusName  ),
					  CQyString(  pTimeBuf  ).GetBuffer(  0  ),
					  rcdId  );

	  if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;


	 bRet  =  TRUE;

errLabel:
	 return  bRet;
}


 BOOL  bUpdateDynBmp_mcProcResp_retrieveDynBmps2_odbc(  void  *  pDb,  QIS_dynBmp_info  *  pMemParam,  char  *  pTimeBuf,  int  rcdId  )
{
	 BOOL  bRet  =  FALSE;
	 QIS_dynBmp_info					*	pMem													=	(  QIS_dynBmp_info	*	)pMemParam;
	 QY_MC							*	pQyMc													=	QY_GET_GBUF(  );
	 int								iDbType													=	pQyMc->cfg.db.iDbType;
	 TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]						=	_T(  ""  );

#if  0
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set name=%s,cusName=%s where id=%d"  ),  
					  CONST_tabName_qyDynBmpTab,  
					  getDbValStr(  iDbType,  CONST_iDataType_name,  pMem->name  ),
					  getDbValStr(  iDbType,  CONST_iDataType_name,  pMem->cusName  ),
					  rcd.id  );
		  if  (  !bQyExecSql(  pSubThreadInfo->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
	  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set endTime='%s' where id=%d"  ),  
					  CONST_tabName_qyDynBmpTab,  
					  CQyString(  pTimeBuf  ).GetBuffer(  0  ),
					  rcdId  );

	  if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;


	 bRet  =  TRUE;

errLabel:
	 return  bRet;
}


BOOL  bUpdateImObjRegInfo_procMsgInput_scheduler_odbc(  void  *  pDb,  void  *  pSciParam,  void  *  pMisCntParam,  QY_MESSENGER_ID  *  pIdInfo  )
{
	BOOL   bRet  =  FALSE;
	QY_SERVICEGUI_INFO  *  pSci										=  (  QY_SERVICEGUI_INFO  *  )pSciParam;
	MIS_CNT				*  pMisCnt									=  (  MIS_CNT  *  )pMisCntParam;
	TCHAR				   sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	char				   timeBuf[CONST_qyTimeLen  +  1]			=	"";
								 

	char						idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";		
	if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

	getCurTime(  timeBuf  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set tCommitTime='%s' where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyImObjRegInfoTab1,  CQyString(  timeBuf  ),  getDbValStr(  pSci->cfg.iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  CQyString(  idStr  )  );
	
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  {
		traceLogA(  ""  );  goto  errLabel;
	}

	bRet  =  TRUE;
errLabel:
	return  bRet;

}



 BOOL  bDeleteFromTabById_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  pTabName,  int  id  )
{
	BOOL  bRet  =  FALSE;
	TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]				=		_T(  ""  );

#if  0
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyMessengerPhoneInfoTab,  atol(  buf  )  );
	if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyMessengerPhoneInfoTab,  id  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}

 BOOL  bDeleteFromTabByIdInfo_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{
	BOOL  bRet  =  FALSE;
	TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]				=		_T(  ""  );
	char								idStr[CONST_qyMessengerIdStrLen  +  1]			=		"";
 #if  0
 							    if  (  !idInfo2Str(  &idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyCustomerServiceObjTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CQyString(  idStr  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
#endif

	if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyCustomerServiceObjTab,  misServName,  CQyString(  idStr  )  );

	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}

BOOL  bDeleteImOtherRegInfoByAddr_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  LPCTSTR  pTabName,  MSGR_ADDR  *  pAddr  )
{
	BOOL  bRet  =  FALSE;
	TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]				=		_T(  ""  );
	char								idStr[CONST_qyMessengerIdStrLen  +  1]			=		"";

#if  0
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and uiDevType=%d and wDevIdStr=%s"  ),  CONST_tabName_qyImOtherRegInfoTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  addr.uiDevType,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_wDevIdStr,  addr.wDevIdStr  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
#endif

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and uiDevType=%d and wDevIdStr=%s"  ),  pTabName,  misServName,  pAddr->uiDevType,  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  pAddr->wDevIdStr  )  );
	
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;



	bRet  =  TRUE;
errLabel:
	return  bRet;
}


////  dlgSelect_isCli  ///////////////////////////////////////////////////







#if  0
int  iSelectImObjAuth2_dlgSelect_isCli_odbc(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd,  void  *  pVarVals,  int  iVarValSize  )
{
	int  iRet  =  -1;
	TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	TCHAR		tBuf[255  +  1]						=	_T(  ""  );

#if  0
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImObjAuthTab.idStr,qyImGrpInfoTab.name from qyImObjAuthTab left join qyImGrpInfoTab on (qyImObjAuthTab.misServName=qyImGrpInfoTab.misServName and qyImObjAuthTab.idStr=qyImGrpInfoTab.idStr) where qyImObjAuthTab.misServName=%s and qyImObjAuthTab.uiType in (%d) order by qyImObjAuthTab.idStr"  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.u.selectImGrp.misServName  ),  CONST_objType_imGrp  );
				  if  (  enumSqlQuery(  m_var.pObjDb->pDb,  sqlBuf,  tmpHandler_displayImGrp,  GetDlgItem(  IDC_COMBO_objList  )->m_hWnd,  0,  varVals,  mycountof(  varVals  ),  NULL  )  <  0  )  goto  errLabel;
#endif
				  
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImObjAuthTab.idStr,qyImGrpInfoTab.name from qyImObjAuthTab left join qyImGrpInfoTab on (qyImObjAuthTab.misServName=qyImGrpInfoTab.misServName and qyImObjAuthTab.idStr=qyImGrpInfoTab.idStr) where qyImObjAuthTab.misServName=%s and qyImObjAuthTab.uiType in (%d) order by qyImObjAuthTab.idStr"  ),  misServName,  CONST_objType_imGrp  );
	iRet  =  enumSqlQuery(  pDb,  sqlBuf,  tmpHandler_displayImGrp,  idc_hWnd,  0,  pVarVals,  iVarValSize,  NULL  );

errLabel:
	return  iRet;
}
#endif






