
#include	"stdafx.h"

#include	<stddef.h>
#include	<time.h>
#include	<stdio.h>

#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
	#include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"


//  #include	"qwmDynFunc.h"

#include	"qmcCmdProc.h"

#include	"tmpCeLib.h"
#include	"qySqlFunc.h"

#include	"myresource.h"
#include	"myDb.h"
#include	"isCliHelpPublic.h"

#include	"qmcCommFunc_isCli.h"
#include	"dlgTalkProc.h"
//
#include	"ctxMcThread.h"
#include	"imCommType_defs.h"



//
BOOL  bRefreshAllContacts(  MIS_CNT  *  pMisCnt  )
{
	return  !pMisCnt->refreshContactList.tLastRefreshedTime_misServ;
}



//
 BOOL  bMessengerRegInfoSame(  QY_MESSENGER_REGINFO  *  pRegInfo0,  QY_MESSENGER_REGINFO  *  pRegInfo1  )
{
	int		i;

	//
	for  (  i  =  0;  i  <  mycountof(  pRegInfo0->fields  );  i  ++  )  {
		 if  (  pRegInfo0->uiFieldIds[i]  !=  pRegInfo1->uiFieldIds[i]  )  break;
		 if  (  pRegInfo0->fields[i].bufSize  !=  pRegInfo1->fields[i].bufSize  )  break;
		 if  (  !pRegInfo0->fields[i].ptr  ||  !pRegInfo1->fields[i].ptr  )  break;
		 if  (  lstrcmpi(  pRegInfo0->fields[i].ptr,  pRegInfo1->fields[i].ptr  )  )  break;
		 continue;
	}
	if  (  i  ==  mycountof(  pRegInfo0->fields  )  )  return  TRUE;
	return  FALSE;
}

 




int  mcProcResp_refreshImGrps(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_IMGRPLIST_RESP  *  pResp,  void  *  pCtxParam  )
{
	int									iErr													=	-1;
	MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	QY_SERVICEGUI_INFO				*	pSci													=	(  QY_SERVICEGUI_INFO  *  )pSciParam;
	MIS_CNT							*	pMisCnt													=	(  MIS_CNT  *  )pMisCntParam;
	CTX_MC_THREAD					*	pCtx													=	(  CTX_MC_THREAD  *  )pCtxParam;

	MC_VAR_isCli					*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	QY_MC							*	pQyMc													=	pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;

	int  i;

	TCHAR								sqlBuf[1024];
	 //  CDBVariant							varVals[50];
	 COMMON_PARAM						commonParam0;
	 COMMON_PARAM						commonParam1;
	 TRAN_INFO_MIS						tranInfo;

	 char								idStr_lastRefreshed[CONST_qyMessengerIdStrLen  +  1]	=	"";
	 int								tmpiRet;

	 unsigned  int						uiObjType	=	CONST_objType_imGrp;

	if  (  pResp->idInfo_lastRefreshed.ui64Id  )  {
		if  (  !idInfo2Str(  &pResp->idInfo_lastRefreshed,  idStr_lastRefreshed,  mycountof(  idStr_lastRefreshed  )  )  )  goto  errLabel;
	}
	
	//  if  (  !bRefreshAllContacts(  pMisCnt  )  )  
	{  //  ÕâÀïÊÇÔöÁ¿Ë¢ÐÂ
		//民粹派ro
		for  (  i  =  0;  i  <  pResp->usCnt;  i  ++  )  {

			if  (  pProcInfo->recoverImGrp(  pQyMc->p_g_dbFuncs,  pSubThreadInfo->pDb,  pSci->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  uiObjType,  &pResp->mems[i],  pMisCnt->refreshContactList.tStartTime,  FALSE  )  )  {
				#ifdef  __DEBUG__
						traceLogA(  (char*)  "recoverImGrp(  ) failed"  );  
				#endif
				goto  errLabel;
			 }			   
		}
		//

	}


	iErr  =  0;

errLabel:

	return  iErr;

}



 //  2013/01/30
 //int  mcProcResp_refreshImGrps_end(  void  *  pSubThreadInfoParam,  QY_SERVICEGUI_INFO  *  pSci,  MIS_CNT  *  pMisCnt,  RETRIEVE_IMGRPLIST_RESP  *  pResp,  CTX_MC_THREAD  *  pCtx  )
 int  mcProcResp_refreshImGrps_end(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_IMGRPLIST_RESP  *  pResp,  void  *  pCtxParam  )
{
	int									iErr													=	-1;
	MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	QY_SERVICEGUI_INFO				*	pSci		=	(  QY_SERVICEGUI_INFO  *  )pSciParam;
	MIS_CNT							*	pMisCnt				=	(  MIS_CNT  *  )pMisCntParam;
	CTX_MC_THREAD					*	pCtx			=	(  CTX_MC_THREAD  *  )pCtxParam;
	MC_VAR_isCli					*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	QY_MC							*	pQyMc													=	pProcInfo->pQyMc;

	TCHAR								sqlBuf[1024];

	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return  -1;// goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	if  (  bRefreshAllContacts(  pMisCnt  )  )  {  //  ±íÃ÷ÊÇÈ«ÃæË¢ÐÂ,ÒªÉ¾³ý´ÓidInfo_lastRefreshedºóµÄËùÓÐµÄ·Ï×é
			 	 
			 char								idStr_lastRefreshed[CONST_qyMessengerIdStrLen  +  1]	=	"";
			 
			 if  (  pResp->idInfo_lastRefreshed.ui64Id  )  {
				 if  (  !idInfo2Str(  &pResp->idInfo_lastRefreshed,  idStr_lastRefreshed,  mycountof(  idStr_lastRefreshed  )  )  )  goto  errLabel;
			 }
				
#if  0
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyImObjTab set iStatus=%d where misServName=%s and uiType in(%d)"  ),  CONST_qyStatus_del,  getDbValStr(  pSci->cfg.iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  CONST_objType_imGrp  );
			 if  (  pResp->usCnt  )  idInfo2Str(  &pResp->mems[pResp->usCnt  -  1].idInfo,  idStr_lastRefreshed,  mycountof(  idStr_lastRefreshed  )  );
			 if  (  idStr_lastRefreshed[0]  )  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and idStr>'%s'"  ),  sqlBuf,  CQyString(  idStr_lastRefreshed  )  );
			 if  (  !bQyExecSql(  pSubThreadInfo->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
			 if  (  g_dbFuncs.pf_updateImObj_refreshImGrps_end(  pSubThreadInfo->pDb,  pSci->cfg.iDbType,  pMisCnt->cfg.misServName,  0,  pMisCnt->refreshContactList.tStartTime  )  )  goto  errLabel;

	}

	iErr  =  0;
errLabel:
	return  iErr;
}


 //  2013/02/01
 //  int  mcProcResp_refreshImGrpMems_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_IMGRPMEMLIST_RESP  *  pResp,  void  *  pCtxParam  )
 int  mcProcResp_refreshImGrpMems(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_IMGRPMEMLIST_RESP  *  pResp,  void  *  pCtxParam  )
{
	int									iErr													=	-1;
	MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	QY_SERVICEGUI_INFO				*  pSci	=	(  QY_SERVICEGUI_INFO  *  )pSciParam;
	MIS_CNT							*  pMisCnt			=	(  MIS_CNT  *  )pMisCntParam;
	CTX_MC_THREAD					*  pCtx		=	(  CTX_MC_THREAD  *  )pCtxParam;

	MC_VAR_isCli					*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	QY_MC							*	pQyMc													=	pProcInfo->pQyMc;


	TCHAR								sqlBuf[1024];
	//  CDBVariant							varVals[50];
	COMMON_PARAM						commonParam0;
	COMMON_PARAM						commonParam1;
	TRAN_INFO_MIS						tranInfo;

	 char								idStr_lastRefreshed[CONST_qyMessengerIdStrLen  +  1]	=	"";
	 char								idStr_grp_lastRefreshed[CONST_qyMessengerIdStrLen  +  1]				=	"";
	 int								tmpiRet;
	 int  i;


	 if  (  !idInfo2Str(  &pResp->idInfo_grp_lastRefreshed,  idStr_grp_lastRefreshed,  mycountof(  idStr_grp_lastRefreshed  )  )  )  goto  errLabel;
	 if  (  !idInfo2Str(  &pResp->idInfo_lastRefreshed,  idStr_lastRefreshed,  mycountof(  idStr_lastRefreshed  )  )  )  goto  errLabel;

	 //  if  (  !bRefreshAllContacts(  pMisCnt  )  )  
	 {  //  ÕâÀïÊÇÔöÁ¿Ë¢ÐÂ
		 //
		 for  (  i  =  0;  i  <  pResp->usCnt;  i  ++  )  {

			 if  (  pProcInfo->recoverImGrpMem(  pQyMc->p_g_dbFuncs,  pSubThreadInfo->pDb,  pSci->cfg.iDbType,  &pResp->mems[i],  pMisCnt->refreshContactList.tStartTime  )  )  {
				  traceLogA(  (char*)  "recoverImGrpMem(  ) failed"  );  
				  goto  errLabel;
			  }			   
		 }
		 //
		 }
#if  0
	 else  {  //  È«ÃæË¢ÐÂ
		   
		    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,idStr_grp,idStr_mem,iRole from qyImGrpMemTab where qyImGrpMemTab.misServName=%s"  ),  getDbValStr(  pSci->cfg.iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  )  );
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and (idStr_grp>'%s' or (idStr_grp='%s' and idStr_mem>'%s'))"  ),  sqlBuf,  CQyString(  idStr_grp_lastRefreshed  ),  CQyString(  idStr_grp_lastRefreshed  ),  CQyString(  idStr_lastRefreshed  )  );
			//  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s %s"  ),  sqlBuf,  _T(  "order by idStr_mem"  )  );
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s %s"  ),  sqlBuf,  _T(  "order by idStr_grp,idStr_mem"  )  );	//  2009/11/18
			OutputDebugString(  sqlBuf  );  OutputDebugString(  _T(  "\n"  )  );
	 	 	   
			memset(  &tranInfo,  0,  sizeof(  tranInfo  )  );
			MACRO_makeCommonParam3(  pSubThreadInfo,  pSci,  pMisCnt,  commonParam0  );
			MACRO_makeCommonParam3(  pResp,  &tranInfo,  0,  commonParam1  );
			tmpiRet  =  enumSqlQuery(  pSubThreadInfo->pDb,  sqlBuf,  tmpHandler_mcProcCmd_refreshAllImGrpMems,  &commonParam0,  &commonParam1,  varVals,  mycountof(  varVals  ),  NULL  );
			if  (  tmpiRet  <  0  )  goto  errLabel;
	 	   
			if  (  !tmpiRet  )  {	//  
				//  ÕâÀïÒª´¦ÀíÊý¾ÝÖÐÒÑ¾­²éÑ¯ÍêÁË£¬µ«ÊÇÈÔÈ»ÁôÏÂÀ´´óÁ¿µÄÐÂ½Úµã

				for  (  ;  pResp->index  <  pResp->usCnt;  pResp->index  ++  )  {
			   
					 if  (  recoverImGrpMem(  pSubThreadInfo->pDb,  pSci->cfg.iDbType,  &pResp->mems[pResp->index]  )  )  {
						 traceLogA(  (char*)  "recoverImGrpMem(  ) failed"  );  goto  errLabel;			
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


  // 2013/02/01
 //  int  mcProcResp_refreshImGrpMems_end_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_IMGRPMEMLIST_RESP  *  pResp,  void  *  pCtxParam  )
 int  mcProcResp_refreshImGrpMems_end(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_IMGRPMEMLIST_RESP  *  pResp,  void  *  pCtxParam  )
{
	int									iErr													=	-1;
	MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	QY_SERVICEGUI_INFO  *  pSci		=   (  QY_SERVICEGUI_INFO *  )pSciParam;
	MIS_CNT  *  pMisCnt				=   (  MIS_CNT  *  )pMisCntParam;
	CTX_MC_THREAD  *  pCtx			=	(  CTX_MC_THREAD  *  )pCtxParam;

	MC_VAR_isCli						*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	QY_MC							*	pQyMc													=	pProcInfo->pQyMc;

	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return -1;// goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

#ifdef  __NOTSUPPORT_DB__
		//  do nothing
#else
	//  TCHAR								sqlBuf[1024];

	if  (  bRefreshAllContacts(  pMisCnt  )  )  {  //  ±íÃ÷ÊÇÈ«ÃæË¢ÐÂ,ÒªÉ¾³ý´ÓidInfo_lastRefreshedºóµÄËùÓÐµÄ·Ï×é
			 char								idStr_lastRefreshed[CONST_qyMessengerIdStrLen  +  1]	=	"";
			 char								idStr_grp_lastRefreshed[CONST_qyMessengerIdStrLen  +  1]				=	"";

			 if  (  pResp->usCnt  )  {
				 idInfo2Str(  &pResp->mems[pResp->usCnt  -  1].idInfo_grp,  idStr_grp_lastRefreshed,  mycountof(  idStr_grp_lastRefreshed  )  );
				 idInfo2Str(  &pResp->mems[pResp->usCnt  -  1].idInfo_mem,  idStr_lastRefreshed,  mycountof(  idStr_lastRefreshed  )  );
				 }
			 else  {	//  2011/08/05
				   idInfo2Str(  &pResp->idInfo_grp_lastRefreshed,  idStr_grp_lastRefreshed,  mycountof(  idStr_grp_lastRefreshed  )  );
				   idInfo2Str(  &pResp->idInfo_lastRefreshed,  idStr_lastRefreshed,  mycountof(  idStr_lastRefreshed  )  );
			 }
			 
#if  0
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyImGrpMemTab set iStatus=%d where misServName=%s and ( idStr_grp>'%s' or (idStr_grp='%s' and idStr_mem>'%s'))"  ),  CONST_qyStatus_del,  getDbValStr(  pSci->cfg.iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  CQyString(  idStr_grp_lastRefreshed  ),  CQyString(  idStr_grp_lastRefreshed  ),  CQyString(  idStr_lastRefreshed  )  );
			 if  (  !bQyExecSql(  pSubThreadInfo->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
			 if  (  g_dbFuncs.pf_updateImGrpMem_refreshImGrpMems_end(  pSubThreadInfo->pDb,  pSci->cfg.iDbType,  getDbValStr(  pSci->cfg.iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  pMisCnt->refreshContactList.tStartTime  )  )  goto  errLabel;

	}
#endif

	iErr  =  0;
errLabel:
	return  iErr;
}


 // 	
 int  mcProcResp_refreshContacts(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_CONTACTLIST_RESP  *  pResp,  void  *  pCtxParam  )
{
	int									iErr													=	-1;
	MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	QY_SERVICEGUI_INFO  *  pSci		=	(  QY_SERVICEGUI_INFO  *  )pSciParam;
	MIS_CNT  *  pMisCnt				=	(  MIS_CNT  *  )pMisCntParam;
	CTX_MC_THREAD  *  pCtx			=	(  CTX_MC_THREAD  *  )pCtxParam;

	MC_VAR_isCli						*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	QY_MC							*	pQyMc													=	pProcInfo->pQyMc;
	
	//
	QM_dbFuncs  *	p_g_dbFuncs  = pQyMc->p_g_dbFuncs;

	 int  i;


	TCHAR								sqlBuf[1024];
	//  CDBVariant							varVals[50];
	COMMON_PARAM						commonParam0;
	COMMON_PARAM						commonParam1;
	TRAN_INFO_MIS						tranInfo;

	 char								idStr_lastRefreshed[CONST_qyMessengerIdStrLen  +  1]	=	"";
	 int								tmpiRet;

	 if  (  pResp->idInfo_lastRefreshed.ui64Id  )  {
		 if  (  !idInfo2Str(  &pResp->idInfo_lastRefreshed,  idStr_lastRefreshed,  mycountof(  idStr_lastRefreshed  )  )  )  goto  errLabel;
	 } 
	 
	 //  if  (  !bRefreshAllContacts(  pMisCnt  )  )  
	 {   //  
		 //  QY_MESSENGER_REGINFO	regInfo;
		 //
		 for  (  i  =  0;  i  <  pResp->usCnt;  i  ++  )  {
			  
			  //
			  RETRIEVE_contact_mem  *  pMem  =  &pResp->mems[i];

			  //
			  QY_MESSENGER_INFO  messengerInfo  =  {0};
			  //
			  lstrcpyn(  messengerInfo.misServName,  pMem->regInfo.addr.misServName,  mycountof(  messengerInfo.misServName  )  );
			  messengerInfo.idInfo.ui64Id  =  pMem->regInfo.addr.idInfo.ui64Id;		 
			  messengerInfo.uiType  =  pMem->regInfo.addr.uiObjType;		//  CONST_objType_messenger;		 
			  messengerInfo.iStatus  =  0;			
			  //
			  messengerInfo.iRole  =  pMem->iRole;
			  //
			  if  (  pMem->regInfo.addr.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
				  messengerInfo.uiType  =  CONST_objType_me;
			  }
			  //
			  if  (  pProcInfo->recoverMessenger(  p_g_dbFuncs,  pSubThreadInfo->pDb,  pSci->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &messengerInfo,  &pResp->mems[i].regInfo,  pMisCnt->refreshContactList.tStartTime,  FALSE,  &pProcInfo->schedulerQ  )  )  {
				  #ifdef  __DEBUG__
						  traceLogA(  (char*)  "recoverMessenger(  ) failed"  );  
				  #endif
				  goto  errLabel;			
			  }

			  if  (  pMem->regInfo.addr.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {	
				  updateMeDisplayInfo(  pProcInfo,  pMisCnt,  &pResp->mems[i].regInfo,  NULL,  NULL  );
			  }

		 }
		 //
		 }


	 iErr  =  0;
errLabel:
	 return  iErr;
		 
}

 //  2013/02/02. 要注意,要清理的时候要把me排除在外.因为me的更新在startchannel里也有.
 int  mcProcResp_refreshContacts_end(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_CONTACTLIST_RESP  *  pResp,  void  *  pCtxParam  )
 {
	int									iErr													=	-1;
	MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	QY_SERVICEGUI_INFO  *  pSci		=		(  QY_SERVICEGUI_INFO  *  )pSciParam;	
	MIS_CNT  *  pMisCnt				=		(  MIS_CNT  *  )pMisCntParam;
	CTX_MC_THREAD  *  pCtx			=		(  CTX_MC_THREAD  *  )pCtxParam;
	MC_VAR_isCli						*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	QY_MC							*	pQyMc													=	pProcInfo->pQyMc;

	TCHAR								sqlBuf[1024];
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if (!pDbFuncs) return  -1;// goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	//  
	if  (  bRefreshAllContacts(  pMisCnt  )  )  {	//  Õâ±íÃ÷ÊÇÈ«ÃæË¢ÐÂ£¬·ÇÔöÁ¿Ë¢ÐÂ£¬ËùÒÔ£¬ÒªÉ¾³ý´ÓidInfo_lastRefreshedºóµÄËùÓÐµÄ·Ïid
			 char								idStr_lastRefreshed[CONST_qyMessengerIdStrLen  +  1]	=	"";
			 
			 if  (  pResp->usCnt  )  {
				 idInfo2Str(  &pResp->mems[pResp->usCnt  -  1].regInfo.addr.idInfo,  idStr_lastRefreshed,  mycountof(  idStr_lastRefreshed  )  );
				}
			 else  {	//  2011/08/05
				   idInfo2Str(  &pResp->idInfo_lastRefreshed,  idStr_lastRefreshed,  mycountof(  idStr_lastRefreshed  )  );
			 }

			 //  if  (  !idStr_lastRefreshed[0]  )  ÔÚ·Ö×éÄ£Ê½µ«ÊÇÎ´¼ÓÈëÄ³¸ö×éÊ±£¬»á³öÏÖÕâÇé¿ö

#if  0
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyImObjTab set iStatus=%d where misServName=%s and uiType not in(%d)"  ),  CONST_qyStatus_del,  getDbValStr(  pSci->cfg.iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  CONST_objType_imGrp  );
			 if  (  idStr_lastRefreshed[0]  )  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and idStr>'%s'"  ),  sqlBuf,  CQyString(  idStr_lastRefreshed  )  );
		 	 if  (  !bQyExecSql(  pSubThreadInfo->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
			 if  (  g_dbFuncs.pf_updateImObj_refreshContacts_end(  pSubThreadInfo->pDb,  pSci->cfg.iDbType,  pMisCnt->cfg.misServName,  pMisCnt->refreshContactList.tStartTime  )  )  goto  errLabel;
	}
	iErr  =  0;
errLabel:
	return  iErr;
}


 //
 int  mcProcResp_retrieveImObjListReq(  void  *  pSubThreadInfoParam,  QY_SERVICEGUI_INFO  *  pSci,  MIS_CNT  *  pMisCnt,  MIS_MSG_INPUT  *  pMsgInput,  CTX_MC_THREAD  *  pCtx  )
{
	 int								iErr													=	-1;
	 MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 MC_VAR_isCli					*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	 QY_MC							*	pQyMc													=	pProcInfo->pQyMc;
	 //  
	 IM_CONTENTU					*	pContent												=	NULL;
	 
	 unsigned  int						size;
	 //  int								tmpiRet;
	 int								i;
	 TCHAR								tBuf[255  +  1]											=	_T(  ""  );

	 RETRIEVE_IMOBJLIST_REQ				req;
	 //  CQyMalloc							mallocObj;
	 if  (  !pCtx  )  {
		 traceLogA(  (char*)  "mcProcResp_retrieveImObjlistReq failed, pCtx is null"  );
		 return  -1;
	 }
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	 if  (  sizeof(  IM_L_STREAM  )  >  sizeof(  MIS_MSGU  )  )  return  -1;
	 IM_L_STREAM				*	pStream													=	(  IM_L_STREAM  *  )pCtx->pMsgBuf_forInput;	//  mallocObj.malloc(  sizeof(  IM_STREAM_CONTENT  )  );
	 if  (  !pStream  )  return  -1;
	 int								len;

	 if  (  isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  )  return  -1;
	 pContent  =  M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );
	 if  (  !pContent  )  return  -1;

	 //  2014/02/11
	 pMisCnt->refreshContactList.dwLastTickCnt_respRecvd  =  GetTickCount(  );
	 
	 //
	 if  (  pContent->uiType  ==  CONST_imCommType_retrieveImGrpListResp  )  {

		 RETRIEVE_IMGRPLIST_RESP		*	pResp		=	&pContent->retrieveImGrpListResp;	
		 unsigned  int						uiObjType	=	CONST_objType_imGrp;

		 /*

		 memset(  &resp,  0,  sizeof(  resp  )  );
		 if  (  stream2Data(  &ptr,  &size,  tmpHandler_stream2RetrieveImGrpListResp,  0,  &resp  )  )  goto  errLabel;
		 */

		 if  (  pResp->usCnt  >  mycountof(  pResp->mems  )  )  goto  errLabel;

		 //  2014/02/06
 		 #ifdef  __DEBUG__
				 printRetrieveImGrpListResp(  pResp  );
		 #endif


		 //
		 for  (  i  =  0;  i  <  pResp->usCnt;  i  ++  )  {	//  Ìî³äÐÅÏ¢
			  lstrcpyn(  pResp->mems[i].misServName,  pMisCnt->cfg.misServName,  mycountof(  pResp->mems[i].misServName  )  );
		 }

		 if  (  pResp->usCnt  )  {

			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d groups retrieved, tn %d"  ),  pResp->usCnt,  pMsgInput->uiTranNo  );
			 #ifndef  __WINCE__
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    %s"  ),  tBuf  );
			 #else
					 showNotification(  pMisCnt,  NULL,  0,  0,  0,  0,  tBuf  );
			 #endif

			 //	 
			 size  =  offsetof(  RETRIEVE_IMGRPLIST_RESP,  pInternal  );	//  
			 memset(  (  (  char  *  )pResp  )  +  size,  0,  sizeof(  pResp[0]  )  -  size  );

			 if  (  mcProcResp_refreshImGrps(  pSubThreadInfoParam,  pSci,  pMisCnt,  pResp,  pCtx  )  )  goto  errLabel;

			 //  2011/04/10
			 pMisCnt->retrieveImObjList.ulbImGrpExists  =  TRUE;

		 }
		 
		 if  (  !pResp->ucbEnd  )  {

			 if  (  !pResp->usCnt  )  goto  errLabel;

			 //  发送请求以获取剩余的分组信息
			 //
			 memset(  &req,  0, sizeof(  req  )  );
			 req.uiType  =  CONST_imCommType_retrieveImGrpListReq;
			 req.ucbNext  =  TRUE;
			 req.idInfo_lastRefreshed.ui64Id  =  pResp->mems[pResp->usCnt  -  1].idInfo.ui64Id;
			 //
			 MACRO_memset_imLStream(  pStream  );
			 pStream->uiType  =  CONST_imCommType_lStream;
			 pStream->uiContentType  =  req.uiType;
			 len  =  sizeof(  pStream->buf  );
			 if  (  retrieveImObjListReq2Stream(  pStream->uiContentType,  &req,  pStream->buf,  (  unsigned  int  *  )&len  )  )  goto  errLabel;
			 pStream->ulStreamLen  =  len;
			 len  +=  offsetof(  IM_L_STREAM,  buf  ); 
			 //
			 if  (  pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_refreshImObjListReq,  pMsgInput->tStartTime,  pMsgInput->uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  NULL,  CONST_channelType_talking,  pCtx->pMsgBuf,  FALSE  )  )  goto  errLabel;

			 iErr  =  0;  goto  errLabel;
		 
		 }

		 //  ±íÃ÷½áÊøÁË£¬Ó¦¸Ã°Ñ´Ó>idInfo_lastRefreshedµÄ¶¼É¾³ý
		 //
		 if  (  mcProcResp_refreshImGrps_end(  pSubThreadInfoParam,  pSci,  pMisCnt,  pResp,  pCtx  )  )  goto  errLabel;
		 		 
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    retrieveGrps end,  %d"  ),  pMsgInput->uiTranNo  );

		 //  ÕâÀïÒªÈ¡Ò»ÏÂ·Ö×é,ÒªÍùÉÏ·¢·Ö×éµÄ³ÉÔ±ÇëÇó
		 BOOL	bNeedRetrieveImGrpMems  =  FALSE;
#if  0
#ifndef  __NOTSUPPORT_DB__
		 TCHAR								sqlBuf[1024];

		 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(A.idStr) from qyImObjTab as A where A.misServName=%s and A.uiType in (%d) and A.iStatus<>%d"  ),  getDbValStr(  pSci->cfg.iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  CONST_objType_imGrp,  CONST_qyStatus_del  );
		 OutputDebugString(  sqlBuf  );  OutputDebugString(  _T(  "\n"  )  );
		 if  (  bSqlObjExists(  pSubThreadInfo->pDb,  sqlBuf  )  )  bNeedRetrieveImGrpMems  =  TRUE;
#else
		 //  暂时在ce里不考虑处理分组成员信息
#endif
#endif
		 bNeedRetrieveImGrpMems  =  g_dbFuncs.pf_bNeedRetrieveImGrpMems(  pSubThreadInfo->pDb,  pSci->cfg.iDbType,  pMisCnt->cfg.misServName  );
		 if  (  !bNeedRetrieveImGrpMems  )  {		//  ÕâÀïÊÇÎÞ×éµÄÇé¿ö£¬Ö±½Ó·¢retrieveContactListReq
			 memset(  &req,  0,  sizeof(  req  )  );
			 req.uiType  =  CONST_imCommType_retrieveContactListReq;
			 req.tLastRefreshedTime_contactList_misServ  =  pMisCnt->refreshContactList.tLastRefreshedTime_misServ;
			 req.usMaxContactUpdateInfosPerSnd  =  pMisCnt->cfg.usMaxContactUpdateInfosPerSnd_contact;			//  2014/02/06
			}
		 else  {						//  ÓÐ×éµÄÇé¿ö£¬·¢ËÍretrieveImGrpMemListReq
			   memset(  &req,  0, sizeof(  req  )  );
			   req.uiType  =  CONST_imCommType_retrieveImGrpMemListReq;
			   req.tLastRefreshedTime_contactList_misServ  =  pMisCnt->refreshContactList.tLastRefreshedTime_misServ;
			   req.usMaxContactUpdateInfosPerSnd  =  pMisCnt->cfg.usMaxContactUpdateInfosPerSnd_grpMem;			//  2014/02/06
		 }
		 //			 
		 MACRO_memset_imLStream(  pStream  );
		 pStream->uiType  =  CONST_imCommType_lStream;
		 pStream->uiContentType  =  req.uiType;
		 len  =  sizeof(  pStream->buf  );
		 if  (  retrieveImObjListReq2Stream(  pStream->uiContentType,  &req,  pStream->buf,  (  unsigned  int  *  )&len  )  )  goto  errLabel;
		 pStream->ulStreamLen  =  len;
		 len  +=  offsetof(  IM_L_STREAM,  buf  ); 
		 //
		 if  (  pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_refreshImObjListReq,  pMsgInput->tStartTime,  pMsgInput->uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  NULL,  CONST_channelType_talking,  pCtx->pMsgBuf,  FALSE  )  )  goto  errLabel;

		 iErr  =  0;  goto  errLabel;		  
	 
	 }
		 
	 if  (  pContent->uiType  ==  CONST_imCommType_retrieveImGrpMemListResp  )  {
	
		 RETRIEVE_IMGRPMEMLIST_RESP		*	pResp		=	&pContent->retrieveImGrpMemListResp;	
		 //  char								idStr_grp_lastRefreshed[CONST_qyMessengerIdStrLen  +  1]				=	"";

		 if  (  pResp->usCnt  >  mycountof(  pResp->mems  )  )  goto  errLabel;

		 #ifdef  __DEBUG__
				 printRetrieveImGrpMemListResp(  pResp  );
		 #endif
		 
		 for  (  i  =  0;  i  <  pResp->usCnt;  i  ++  )  {	//  Ìî³äÐÅÏ¢
			  lstrcpyn(  pResp->mems[i].misServName,  pMisCnt->cfg.misServName,  mycountof(  pResp->mems[i].misServName  )  );
		 }

		 if  (  pResp->usCnt  )  {
		 
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d grpMems retrieved, tn %d"  ),  pResp->usCnt,  pMsgInput->uiTranNo  );
			 #ifndef  __WINCE__
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "   %s"  ),  tBuf  );
			 #else
					  showNotification(  pMisCnt,  NULL,  0,  0,  0,  0,  tBuf  );
			 #endif
	 
			 //
			 if  (  !pResp->usCnt  )  {
				 traceLogA(  (char*)  "no grpMem, resp error"  );  goto  errLabel;
			 }
	 
			 size  =  offsetof(  RETRIEVE_IMGRPMEMLIST_RESP,  pInternal  );	//  
			 memset(  (  (  char  *  )pResp  )  +  size,  0,  sizeof(  pResp[0]  )  -  size  );

			 if  (  mcProcResp_refreshImGrpMems(  pSubThreadInfoParam,  pSci,  pMisCnt,  pResp,  pCtx  )  )  goto  errLabel;

		 }
		 
		 if  (  !pResp->ucbEnd  )  {

			 if  (  !pResp->usCnt  )  goto  errLabel;

			 //  发送请求以获取剩余的分组成员信息
			 //
			 memset(  &req,  0, sizeof(  req  )  );
			 req.uiType  =  CONST_imCommType_retrieveImGrpMemListReq;
			 req.ucbNext  =  TRUE;
			 req.idInfo_grp_lastRefreshed.ui64Id  =  pResp->mems[pResp->usCnt  -  1].idInfo_grp.ui64Id;
			 req.idInfo_lastRefreshed.ui64Id  =  pResp->mems[pResp->usCnt  -  1].idInfo_mem.ui64Id;
			 //
			 MACRO_memset_imLStream(  pStream  );
			 pStream->uiType  =  CONST_imCommType_lStream;
			 pStream->uiContentType  =  req.uiType;
			 len  =  sizeof(  pStream->buf  );
			 if  (  retrieveImObjListReq2Stream(  pStream->uiContentType,  &req,  pStream->buf,  (  unsigned  int  *  )&len  )  )  goto  errLabel;
			 pStream->ulStreamLen  =  len;
			 len  +=  offsetof(  IM_L_STREAM,  buf  ); 
			 //
			 if  (  pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_refreshImObjListReq,  pMsgInput->tStartTime,  pMsgInput->uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  NULL,  CONST_channelType_talking,  pCtx->pMsgBuf,  FALSE  )  )  goto  errLabel;

			 iErr  =  0;  goto  errLabel;

		 }

		 //
		 if  (  mcProcResp_refreshImGrpMems_end(  pSubThreadInfoParam,  pSci,  pMisCnt,  pResp,  pCtx  )  )  goto  errLabel;
		 		 
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    retrieveGrpMems end,  %d"  ),  pMsgInput->uiTranNo  );

		 memset(  &req,  0,  sizeof(  req  )  );
		 req.uiType  =  CONST_imCommType_retrieveContactListReq;
		 req.tLastRefreshedTime_contactList_misServ  =  pMisCnt->refreshContactList.tLastRefreshedTime_misServ;
		 req.usMaxContactUpdateInfosPerSnd  =  pMisCnt->cfg.usMaxContactUpdateInfosPerSnd_contact;		//  2014/02/06
		 //			 
		 MACRO_memset_imLStream(  pStream  );
		 pStream->uiType  =  CONST_imCommType_lStream;
		 pStream->uiContentType  =  req.uiType;
		 len  =  sizeof(  pStream->buf  );
		 if  (  retrieveImObjListReq2Stream(  pStream->uiContentType,  &req,  pStream->buf,  (  unsigned  int  *  )&len  )  )  goto  errLabel;
		 pStream->ulStreamLen  =  len;
		 len  +=  offsetof(  IM_L_STREAM,  buf  ); 
		 //
		 if  (  pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_refreshImObjListReq,  pMsgInput->tStartTime,  pMsgInput->uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  NULL,  CONST_channelType_talking,  pCtx->pMsgBuf,  FALSE  )  )  goto  errLabel;

		 iErr  =  0;  goto  errLabel;		  
	 
	 }
	
	 if  (  pContent->uiType  ==  CONST_imCommType_retrieveContactListResp  )  {

		 RETRIEVE_CONTACTLIST_RESP		*	pResp  =  (  RETRIEVE_CONTACTLIST_RESP  *  )&pContent->retrieveContactListResp;	
	 
	 	 if  (  pResp->usCnt  >  mycountof(  pResp->mems  )  )  goto  errLabel;
	 
		 //  2014/02/06
 		 #ifdef  __DEBUG__
				 printRetrieveContactListResp(  pResp  );
		 #endif

		 //
	 	 for  (  i  =  0;  i  <  pResp->usCnt;  i  ++  )  {
			 lstrcpyn(  pResp->mems[i].regInfo.addr.misServName,  pMisCnt->cfg.misServName,  mycountof(  pResp->mems[i].regInfo.addr.misServName  )  );
			 MACRO_setPtrs(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pResp->mems[i].regInfo,  pResp->mems[i].regInfo.fields  );
		 }

		 if  (  pResp->usCnt  )  {
	 
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d contacts retrieved, tn %d"  ),  pResp->usCnt,  pMsgInput->uiTranNo  );
			 #ifndef  __WINCE__
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    %s"  ),  tBuf  );
			 #else
					  showNotification(  pMisCnt,  NULL,  0,  0,  0,  0,  tBuf  );
			 #endif

			 //
			 if  (  !pResp->usCnt  )  {
				 traceLogA(  (char*)  "no contact, resp error"  );  goto  errLabel;
			 }

			 size  =  offsetof(  RETRIEVE_CONTACTLIST_RESP,  pInternal  );	//  
			 memset(  (  (  char  *  )pResp  )  +  size,  0,  sizeof(  pResp[0]  )  -  size  );

			 if  (  mcProcResp_refreshContacts(  pSubThreadInfoParam,  pSci,  pMisCnt,  pResp,  pCtx  )  )  goto  errLabel;

			 //  2011/04/10
			 pMisCnt->retrieveImObjList.ulbContactExists  =  TRUE;
		 }

		 if  (  !pResp->ucbEnd  )  {
		 
			 if  (  !pResp->usCnt  )  goto  errLabel;

			 //  发送请求以获取剩余的contact
			 //
			 memset(  &req,  0, sizeof(  req  )  );
			 req.uiType  =  CONST_imCommType_retrieveContactListReq;
			 req.ucbNext  =  TRUE;
			 req.idInfo_lastRefreshed.ui64Id  =  pResp->mems[pResp->usCnt  -  1].regInfo.addr.idInfo.ui64Id;
			 //
			 MACRO_memset_imLStream(  pStream  );
			 pStream->uiType  =  CONST_imCommType_lStream;
			 pStream->uiContentType  =  req.uiType;
			 len  =  sizeof(  pStream->buf  );
			 if  (  retrieveImObjListReq2Stream(  pStream->uiContentType,  &req,  pStream->buf,  (  unsigned  int  *  )&len  )  )  goto  errLabel;
			 pStream->ulStreamLen  =  len;
			 len  +=  offsetof(  IM_L_STREAM,  buf  ); 
			 //
			 if  (  pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_refreshImObjListReq,  pMsgInput->tStartTime,  pMsgInput->uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  NULL,  CONST_channelType_talking,  pCtx->pMsgBuf,  FALSE  )  )  goto  errLabel;

			 iErr  =  0;  goto  errLabel;
		 
		 }
	 	 	 
		 //  
		 if  (  mcProcResp_refreshContacts_end(  pSubThreadInfoParam,  pSci,  pMisCnt,  pResp,  pCtx  )  )  goto  errLabel;

		 //  RETRIEVE_IMOBJLISTEND_REQ, tLastRefreshedTime_contactList_misServ
		 //  pMisCnt->refreshContactList.tLastRefreshedTime_misServ  =  (  time_t  )resp.tLastRefreshedTime_contactList_misServ;
		 memset(  &req,  0, sizeof(  req  )  );			 
		 req.uiType  =  CONST_imCommType_retrieveImObjListEndReq;
		 //
		 MACRO_memset_imLStream(  pStream  );
		 pStream->uiType  =  CONST_imCommType_lStream;
		 pStream->uiContentType  =  req.uiType;
		 len  =  sizeof(  pStream->buf  );
		 if  (  retrieveImObjListReq2Stream(  pStream->uiContentType,  &req,  pStream->buf,  (  unsigned  int  *  )&len  )  )  goto  errLabel;
		 pStream->ulStreamLen  =  len;
		 len  +=  offsetof(  IM_L_STREAM,  buf  ); 
		 //
		 if  (  pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_refreshImObjListReq,  pMsgInput->tStartTime,  pMsgInput->uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  NULL,  CONST_channelType_talking,  pCtx->pMsgBuf,  FALSE  )  )  goto  errLabel;
 	
		 iErr  =  0;  goto  errLabel;
	
	 }

	 if  (  pContent->uiType  ==  CONST_imCommType_retrieveImObjListEndResp  )  {

		 RETRIEVE_IMOBJLISTEND_RESP		*	pResp	=	&pContent->retrieveImObjListEndResp;	

		 //  2014/02/10
		 BOOL  bRetrieveAll  =  bRefreshAllContacts(  pMisCnt  );

		 //  tLastRefreshedTime_misServ, 
		 pMisCnt->refreshContactList.tLastRefreshedTime_misServ  =  (  time_t  )pResp->tLastRefreshedTime_contactList_misServ;

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  bRetrieveAll  ?  _T(  "All im objects retrieved. "  )  :  _T(  "ImObjList retrieved"  )  );
		 #ifndef  __WINCE__
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    %s"  ),  tBuf  );
		 #else
				  showNotification(  pMisCnt,  NULL,  0,  0,  0,  0,  tBuf  );
		 #endif

		 #ifdef  __DEBUG__
				  if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
					  traceLogA((char*)"retrieveImObjListEndResp");
				  }
				 //printQmObjQ(  (  QM_OBJQ  *  )pMisCnt->pObjQ  );
		 #endif

		 //
		 pMisCnt->retrieveImObjList.ulbAllContactsRetrieved = TRUE;

		 //
		 if  (  bSupported_devAuth(  )  )  {
#ifndef  __qmdConn__
			 PostMessage(  pQyMc->gui.hMainWnd,  WM_COMMAND,  MAKEWPARAM(  ID_refreshLayout,  0  ),  0  ); 
#endif
		 }

		 //  2013/08/01
#ifndef  __qmdConn__
		 PostMessage(  pQyMc->gui.hMainWnd,  WM_COMMAND,  MAKEWPARAM(  ID_qyRefresh,  0  ),  0  );
#endif
		 
		 //PostMessage(pQyMc->gui.hMainWnd, (WM_USER + 100), (WPARAM)999, NULL);



		 //
		 #ifdef  __DEBUG__
				 //
			 //print_imObjs_isClient_myDb();

				 //
		 if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
			 traceLog((TCHAR*)_T("post ID_qyRefresh to mainWnd"));
		 }
		 #endif


		 //
		 iErr  =  0;  goto  errLabel;

	 }
	
	 traceLogA(  (char*)  "mcProcResp_retrieveImObjListReq: unprocessed uiContentType ( %d )",  pContent->lStream.uiContentType  );  
	 goto  errLabel;
	 	 
	 iErr  =  0;

errLabel:

	 return  iErr;
}


 int  mcProcResp_getCfgs(  void  *  pSubThreadInfoParam,  QY_SERVICEGUI_INFO  *  pSci,  MIS_CNT  *  pMisCnt,  MIS_MSG_INPUT  *  pMsgInput,  CTX_MC_THREAD  *  pCtx  )
{
	 int								iErr													=	-1;
	 MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 MC_VAR_isCli						*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	 QY_MC							*	pQyMc													=	pProcInfo->pQyMc;
	 IM_CONTENTU				*	pContent												=	NULL;
	 
	 TCHAR								tBuf[255  +  1]											=	_T(  ""  );

	 if  (  isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  )  goto  errLabel;
	 //
	 //if  (  isUcFlgTalkData(  pMsgInput->ucFlg  )  )  goto  errLabel;
	 //
	 pContent  =  (  IM_CONTENTU  *  )&pMsgInput->data;

	 if  (  !pContent  )  goto  errLabel;
	 
	 switch  (  pContent->uiType  )  {
			 //  case  CONST_imCommType_intervalParams:
			 case  CONST_imCommType_getCfgsReq:		//  2011/01/30
				   if  (  pContent->getCfgsReq.uiSizePerSnd_media  
					   &&  pContent->getCfgsReq.uiSizePerSnd_media  !=  pMisCnt->cfg.uiSizePerSnd_media  )  
				   {
					   pMisCnt->cfg.uiSizePerSnd_media  =  min(  pProcInfo->cfg.uiSizePerSnd_media,  pContent->getCfgsReq.uiSizePerSnd_media  );
				   }

				   pMisCnt->cfg.usIntervalInS_refreshRecentFriends  =  max(  2,  pContent->getCfgsReq.intervalParams.usIntervalInS_refreshRecentFriends  );
				   pMisCnt->cfg.usIntervalInS_refreshContactList  =  max(  2,  pContent->getCfgsReq.intervalParams.usIntervalInS_refreshContactList  );

				   //  2015/07/28
#if  0  //  2017/08/17
				   if  (  pContent->getCfgsReq.ucbNotUseP2pCall  !=  pMisCnt->cfg.ucbNotUseP2pCall  )  {
					   pMisCnt->cfg.ucbNotUseP2pCall  =  pContent->getCfgsReq.ucbNotUseP2pCall;
				   }

				   //  2015/07/28
				   if  (  pMisCnt->cfg.ucbNotUseP2pCall  )  {
					   showInfo_open0(  0,  0,  _T(  "Note: mcProcResp_getCfgs: ucbNotUseP2pCall is true"  )  );
				   }
#endif

				   //
				   pMisCnt->bIntervalParamsGot  =  TRUE;
				   break;
			 case  CONST_imCommType_retrieveToPaths:
				   //
				   if  (  pContent->retrieveToPaths.usCnt  >  mycountof(  pContent->retrieveToPaths.mems  )  )  goto  errLabel;
				   memcpy(  &pMisCnt->toPaths,  &pContent->retrieveToPaths,  sizeof(  pMisCnt->toPaths  )  );
				   //
				   pMisCnt->bToPathsRetrieved  =  TRUE;
				   //
				   break;
			 default:
					traceLogA(  (char*)  "´íÎóµÄuiContentType ( %d )",  pContent->uiType  );  goto  errLabel;
					break;
	 }
	 	 
	 iErr  =  0;

errLabel:

	 return  iErr;

}

  int  printPhoneMsgrs(  void  **  ppElem,  unsigned  int  uiQNodes,  LPCTSTR  hint  )
{
	RETRIEVE_PHONE_MSGR		*	pMsgr;
	int							i;	
	TCHAR						tBuf[256];
	
	#ifndef  __DEBUG__
			 return  0;
	#endif

	traceLog((TCHAR*)  _T(  "printPhoneMsgrs enters"  )  );
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "printPhoneMsgrs"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  " %s enters"  ),  hint  ?  hint  :  _T(  ""  )  );

	for  (  i  =  0;  i  <  (  int  )uiQNodes;  i  ++  )  {
		 pMsgr  =  (  RETRIEVE_PHONE_MSGR  *  )ppElem[i];
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\tµÚ%d¸öÊÇ%s, %I64u,  %s\n"  ),  i,  pMsgr->wDevIdStr,  pMsgr->idInfo.ui64Id,  pMsgr->displayName  );
		 OutputDebugString(  tBuf  );
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "printPhoneMsgrs"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
	}

	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "printPhoneMsgrs"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  " leave"  ),  tBuf  );
	traceLog((TCHAR*)  _T(  "printPhoneMsgrs leaves"  )  );

	return  0;
}

   int  __cdecl  myCompare_searchPhoneMsgrByIdInfo(  const  void  *  key,  const  void  *  pElemParam  )
{
	RETRIEVE_PHONE_MSGR			*	pMsgr			=	(  RETRIEVE_PHONE_MSGR  *  )key;
	RETRIEVE_PHONE_MSGR			*	pElem			=	*(  RETRIEVE_PHONE_MSGR  **  )pElemParam;
	__int64							i64Diff			=	0;

	//  if  (  pGuest->uiDevType  !=  pElem->uiDevType  )  return  pGuest->uiDevType  -  pElem->uiDevType;

	/*
	TCHAR	tBuf[255];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "msgr is %I64u, elem is %I64u"  ),  pMsgr->idInfo.ui64Id,  pElem->idInfo.ui64Id  );
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "myCompare"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
	*/

	i64Diff  =  (  pMsgr->idInfo.ui64Id  -  pElem->idInfo.ui64Id  );

	if  (  i64Diff  <  0  )  return  -1;
	if  (  !i64Diff  )  return  0;
	return  1;	
}


   //
   int  __cdecl  myCompare_sortPhoneMsgrsByIdInfo(  const  void  *  pElem0Param,  const  void  *  pElem1Param  )
{
	RETRIEVE_PHONE_MSGR			*	pElem0			=	*(  RETRIEVE_PHONE_MSGR  **  )pElem0Param;
	RETRIEVE_PHONE_MSGR			*	pElem1			=	*(  RETRIEVE_PHONE_MSGR  **  )pElem1Param;

	return  myCompare_searchPhoneMsgrByIdInfo(  pElem0,  pElem1Param  );
}

   //
    int  __cdecl  myCompare_searchPhoneMsgrByDevIdStr(  const  void  *  key,  const  void  *  pElemParam  )
{
	RETRIEVE_PHONE_MSGR			*	pMsgr			=	(  RETRIEVE_PHONE_MSGR  *  )key;
	RETRIEVE_PHONE_MSGR			*	pElem			=	*(  RETRIEVE_PHONE_MSGR  **  )pElemParam;

	//  if  (  pGuest->uiDevType  !=  pElem->uiDevType  )  return  pGuest->uiDevType  -  pElem->uiDevType;

	return  _wcsicmp(  pMsgr->wDevIdStr,  pElem->wDevIdStr  );
	
}

	 int  __cdecl  myCompare_sortPhoneMsgrsByDevIdStr(  const  void  *  pElem0Param,  const  void  *  pElem1Param  )
{
	RETRIEVE_PHONE_MSGR			*	pElem0			=	*(  RETRIEVE_PHONE_MSGR  **  )pElem0Param;
	RETRIEVE_PHONE_MSGR			*	pElem1			=	*(  RETRIEVE_PHONE_MSGR  **  )pElem1Param;

	return  myCompare_searchPhoneMsgrByDevIdStr(  pElem0,  pElem1Param  );
}


  int  mcProcResp_retrievePhoneMsgrs(  void  *  pSubThreadInfoParam,  QY_SERVICEGUI_INFO  *  pSci,  MIS_CNT  *  pMisCnt,  MIS_MSG_INPUT  *  pMsgInput,  CTX_MC_THREAD  *  pCtx  )
{
	 int								iErr													=	-1;
	 MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 MC_VAR_isCli						*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	 QY_MC							*	pQyMc													=	pProcInfo->pQyMc;
	 //  
	 IM_CONTENTU				*	pContent												=	NULL;
	 
	 int								i;
	 TCHAR								tBuf[255  +  1]											=	_T(  ""  );
	 //
	 int								len;

	 if  (  isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  )  return  -1;
	 pContent  =  M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );
	 if  (  !pContent  )  return  -1;


	 iErr  =  0;
errLabel:
	 return  iErr;

}

#if  0
    int  tmpHandler_delOld_dynBmpQ(  void  *  p0,  void  *  p1,  void  *  p2  )
{
#ifdef  __NOTSUPPORT_DB__
	return  -1;
#else
	int			iErr	=	-1;
	MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )p0;
	//
	QY_dynBmp_RCD	*	pMem	=	(  QY_dynBmp_RCD  *  )p2;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	
	if  (  !pMem->tmpInternal.ucbFound  )  {
#if  0
		CString		sqlStr;
		char		buf[128];
		sqlStr  =  CString(  "delete from "  )  +  CString(  CONST_tabName_qyDynBmpTab  )  +  CString(  " where id="  )  +  CString(  ltoa(  pMem->id,  buf,  10  )  );
		bQyExecSql(  pSubThreadInfo->pDb,  sqlStr  );
#endif
		g_dbFuncs.pf_deleteDynBmp_tmpHandler_delOld_dynBmpQ(  pSubThreadInfo->pDb,  pMem->id  );
	}

	iErr	=	0;
	return  iErr;
#endif
}
#endif

#if  0
	 int  tmpHandler_find_dynBmpQ(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int					iErr	=	-1;
	QIS_dynBmp_info		*	pInput	=	(  QIS_dynBmp_info  *  )p0;
	QY_dynBmp_RCD	*	pOutput	=	(  QY_dynBmp_RCD  *  )p1;
	QY_dynBmp_RCD	*	pMem	=	(  QY_dynBmp_RCD  *  )p2;
	//

	if  (  pInput->idInfo.ui64Id  ==  pMem->idInfo.ui64Id
		&&  pInput->uiObjType  ==  pMem->uiObjType
			&&  pInput->usIndex  ==  pMem->usIndex  )
	{
		memcpy(  pOutput,  pMem,  sizeof(  pOutput[0]  )  );
		//
		pMem->tmpInternal.ucbFound  =  TRUE;
		//
		iErr  =  1;  goto  errLabel;
	}

	iErr  =  0;

errLabel:
	return  iErr;
}
#endif

	
#if  0  
 int  tmpHandler_printQ_dynBmp(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	QY_dynBmp_RCD	*	pMem	=	(  QY_dynBmp_RCD  *  )p2;
	//
	QY_MC			*	pQyMc	=	NULL;
	QY_DMITEM		*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
	if  (  !pTable  )  goto  errLabel;

	traceLogA(  (char*)  "dynBmpQ: %I64u,%S,%d,%S,%S",  pMem->idInfo.ui64Id,  qyGetDesByType(  pTable,  pMem->uiObjType  ),  pMem->usIndex,  pMem->name,  pMem->cusName  );

errLabel:
	return  0;
}
#endif

 int  mcProcResp_retrieveDynBmps(  void  *  pSubThreadInfoParam,  QY_SERVICEGUI_INFO  *  pSci,  MIS_CNT  *  pMisCnt,  MIS_MSG_INPUT  *  pMsgInput,  CTX_MC_scheduler  *  pCtx  )
{
#ifdef  __NOTSUPPORT_DB__
	return  -1;
#else
	 int								iErr													=	-1;
	 MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 MC_VAR_isCli						*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	 QY_MC							*	pQyMc													=	pProcInfo->pQyMc;
	 //  
	 IM_CONTENTU					*	pContent												=	NULL;
	 
	 int								iDbType													=	pQyMc->cfg.db.iDbType;

	 //  TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]						=	_T(  ""  );
	 char								timeBuf[128]											=	"";

	 int								i;
	 TCHAR								tBuf[255  +  1]											=	_T(  ""  );
	 //
	 int								len;
	 //
	 int								tmpiRet;
	 QY_dynBmp_RCD						rcd;

	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	if  (  isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  )  return  -1;
	 pContent  =  M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );
	 if  (  !pContent  )  return  -1;

	 if  (  pContent->uiType  !=  CONST_imCommType_retrieveDynBmps  )  goto  errLabel;
	 if  (  !pContent->retrieveDynBmps.ucbResp  )  goto  errLabel;
	 
	 //  getCurTime(  timeBuf  );
	 getTimeStr(  pMisCnt->retrieveDynBmps.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );  

#if  0
	 //  if  (  isQEmpty(  &pCtx->dynBmpQ  )  )  
	 if  (  !pProcInfo->bInited_mcProcResp_retrieveDynBmps  )  {	//  2011/10/31

		 if  (  g_dbFuncs.pf_init_mcProcResp_retrieveDynBmps(  pSubThreadInfo->pDb,  pCtx  )  <  0  )  goto  errLabel; 

		 #ifdef  __DEBUG__
				 //qTraverse(  &pCtx->dynBmpQ,  tmpHandler_printQ_dynBmp,  0,  0  );
		 #endif

		 //  2011/10/31
		 pProcInfo->bInited_mcProcResp_retrieveDynBmps  =  TRUE;
	 }
#endif
	 
	 for  (  i  =  0;  i  <  pContent->retrieveDynBmps.usCnt;  i  ++  )  {
		  QIS_dynBmp_info	*	pMem  =  &pContent->retrieveDynBmps.mems[i];

#if  0
		  char								idStr[CONST_qyMessengerIdStrLen  +  1];
		  idInfo2Str(  &pMem->idInfo,  idStr,  mycountof(  idStr  )  );
#endif

#if  0
		  tmpiRet  =  qTraverse(  &pCtx->dynBmpQ,  tmpHandler_find_dynBmpQ,  pMem,  &rcd  );
		  if  (  tmpiRet  <  0  )  goto  errLabel;
		  if  (  !tmpiRet  )  
#endif
			  if  (  !g_dbFuncs.pf_bGetQyDynBmpRcdBySth(  pSubThreadInfo->pDb,  iDbType,  pMisCnt->cfg.misServName,  &pMem->qisResObj.idInfo,  pMem->qisResObj.resObj.uiObjType,  pMem->qisResObj.resObj.usIndex_obj,  0,  &rcd  )  )  
		  {
#if  0
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr,uiObjType,usIndex,name,cusname,iStatus,startTime,endTime) values(%s,'%s',%d,%d,%s,%s,%d,'%s','%s')"  ),  
					  CONST_tabName_qyDynBmpTab,
					  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),
					  CString(  idStr  ).GetBuffer(  0  ),
					  pMem->uiObjType,
					  pMem->usIndex,
					  getDbValStr(  iDbType,  CONST_iDataType_name,  pMem->name  ),
					  getDbValStr(  iDbType,  CONST_iDataType_name,  pMem->cusName  ),
					  0,
					  CString(  timeBuf  ).GetBuffer(  0  ),
					  CString(  timeBuf  ).GetBuffer(  0  )  );				  
			  if  (  !bQyExecSql(  pSubThreadInfo->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
			  if  (  !g_dbFuncs.pf_bInsertDynBmp_mcProcResp_retrieveDynBmps(  pSubThreadInfo->pDb,  pMisCnt,  pMem,  timeBuf  )  )  goto  errLabel;
			  continue;
		  }

		  if  (  !lstrcmpi(  pMem->name,  rcd.name  )  &&  !lstrcmpi(  pMem->cusName,  rcd.cusName  )  )  {
			  if  (  !g_dbFuncs.pf_bUpdateDynBmp_mcProcResp_retrieveDynBmps2(  pSubThreadInfo->pDb,  pMem,  timeBuf, rcd.id  )  )  goto  errLabel;
			  continue;
		  }
#if  0
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set name=%s,cusName=%s where id=%d"  ),  
					  CONST_tabName_qyDynBmpTab,  
					  getDbValStr(  iDbType,  CONST_iDataType_name,  pMem->name  ),
					  getDbValStr(  iDbType,  CONST_iDataType_name,  pMem->cusName  ),
					  rcd.id  );
		  if  (  !bQyExecSql(  pSubThreadInfo->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
		  if  (  !g_dbFuncs.pf_bUpdateDynBmp_mcProcResp_retrieveDynBmps(  pSubThreadInfo->pDb,  pMem,  timeBuf, rcd.id  )  )  goto  errLabel;

		  continue;
	 }


	 if  (  !pContent->retrieveDynBmps.u.resp.ucbEnd  &&  pContent->retrieveDynBmps.usCnt  )  {
		 RETRIEVE_DYN_BMPS	req;
		 MACRO_prepareForTran(  );

		 memset(  &req,  0,  sizeof(  req  )  );
		 req.uiType  =  CONST_imCommType_retrieveDynBmps;

		 req.u.req.ucbNext  =  TRUE;

		 QIS_dynBmp_info	*	pMem  =  &pContent->retrieveDynBmps.mems[pContent->retrieveDynBmps.usCnt  -  1];

		 req.u.req.idInfo.ui64Id  =  pMem->qisResObj.idInfo.ui64Id;
		 req.u.req.uiObjType  =  pMem->qisResObj.resObj.uiObjType;
		 req.u.req.usIndex_obj  =  pMem->qisResObj.resObj.usIndex_obj;
		 //
		 len  =  offsetof(  RETRIEVE_DYN_BMPS,  mems  )  +  req.usCnt  *  sizeof(  req.mems[0]  );
		 //
		 pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_sendVDevReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&req,  len,  NULL,  0,  0,  NULL,  0  ); 

		 iErr  =  0;  goto  errLabel;
	 }


#if  0
	 tmpiRet  =  qTraverse(  &pCtx->dynBmpQ,  tmpHandler_delOld_dynBmpQ,  pSubThreadInfo,  0  );	
#endif
	 g_dbFuncs.pf_deleteOldDynBmp_mcProcResp_retrieveDynBmps(  pSubThreadInfo->pDb,  iDbType,  timeBuf  );


	 pProcInfo->tLastRefreshedTime_misServ_sharedDynBmps  =  pContent->retrieveDynBmps.tLastRefreshedTime_misServ;

#if  0
	 emptyGenericQ(  &pCtx->dynBmpQ  );
#endif

	 //  trigger dymBmpList to refresh
	 PostMessage(  pProcInfo->hWnd_status_dynBmpList,  CONST_qyWm_postComm,  CONST_qyWmParam_refreshContent,  0  );

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
#if  0
		 emptyGenericQ(  &pCtx->dynBmpQ  );
#endif
	 }
	 return  iErr;
#endif  
}


 int  imObjRulesReq2ImRules(  REFRESH_imObjRules_req  *  pReq,  QY_im_rules  *  pRules  )
{
	char	buf[128];

	memset(  pRules,  0,  sizeof(  pRules[0]  )  );

	for  (  int  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {  
		 if  (  pReq->mems[i].idInfo_related.ui64Id  !=  0  )  continue;
		 switch  (  pReq->mems[i].uiRuleType  )  {		
				 case  CONST_ruleType_conferenceId_shareWebcam:
					   myTChar2Utf8(  pReq->mems[i].wDesc,  buf,  mycountof(  buf  )  );
					   idStr2Info(  buf,  &pRules->conferenceId_shareWebcam  );
					   break;
				 case  CONST_ruleType_ucbNoLocalVideoInThisConference:		//  是否在这个会议中启动视频. 2011/10/22
					   pRules->ucbNoLocalVideoInThisConference  =  pReq->mems[i].uiCmd  ==  CONST_ruleCmd_permit;
					   break;
				 case  CONST_ruleType_ucbDistinguishSharedWebcams:			//  是否区分被共享的摄像机，（是否使用序号）
					   pRules->ucbDistinguishSharedWebcams  =  pReq->mems[i].uiCmd  ==  CONST_ruleCmd_permit;
					   break;
				 default:
						 break;	
		 }		
	}

	return  0;
}


 int  imObjRulesReq2Rules(  REFRESH_imObjRules_req  *  pReq,  QY_MESSENGER_ID  *  pIdInfo_related,  QY_imObj_rules  *  pRules  )
{
	if  (  !pIdInfo_related  ||  !pIdInfo_related->ui64Id  )  {
		traceLog((TCHAR*)  _T(  "imObjRulesReq2Rules failed, idInfo_related error"  )  );
		return  -1;
	}

	memset(  pRules,  0,  sizeof(  pRules[0]  )  );

	for  (  int  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {  
		 if  (  pReq->mems[i].idInfo_related.ui64Id  !=  pIdInfo_related->ui64Id  )  continue;
		 switch  (  pReq->mems[i].uiRuleType  )  {		
				 case  CONST_ruleType_autoAnswer_av:
					   pRules->uiCmd_autoAnswer_av  =  pReq->mems[i].uiCmd;
					   break;
				 case  CONST_ruleType_autoAnswer_screen:
					   pRules->uiCmd_autoAnswer_screen  =  pReq->mems[i].uiCmd;
					   break;
				 case  CONST_ruleType_autoAnswer_mediaFile:
					   pRules->uiCmd_autoAnswer_mediaFile  =  pReq->mems[i].uiCmd;
					   break;
				 default:
						 break;	
		 }		
	}

	return  0;
}




 int  mcProcResp_refreshImObjRulesReq(  void  *  pSubThreadInfoParam,  QY_SERVICEGUI_INFO  *  pSci,  MIS_CNT  *  pMisCnt,  MIS_MSG_INPUT  *  pMsgInput,  CTX_MC_scheduler  *  pCtx  )
{
	 int								iErr													=	-1;
	 MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 MC_VAR_isCli					*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	 QY_MC							*	pQyMc													=	pProcInfo->pQyMc;
	 //  
	 IM_CONTENTU					*	pContent												=	NULL;
	 
	 int								iDbType													=	pQyMc->cfg.db.iDbType;

	 TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]						=	_T(  ""  );
	 //  CDBVariant							varVals[64];
	 char								timeBuf[128]											=	"";
	 char								idStr[CONST_qyMessengerIdStrLen  +  1];

	 int								i;
	 TCHAR								tBuf[255  +  1]											=	_T(  ""  );
	 //
	 int								len;
	 //
	 int								tmpiRet;
	 //  
	 REFRESH_imObjRules_req				req;
	 //  CDBVariant							varVals[1];
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;


	 if  (  isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  )  return  -1;
	 pContent  =  M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );
	 if  (  !pContent  )  return  -1;
	 
	 if  (  pContent->uiType  !=  CONST_imCommType_refreshImObjRulesReq  )  goto  errLabel;
	 if  (  !pContent->refreshImObjRulesReq.ucbResp  )  goto  errLabel;
	 //
#if  1
	 for  (  i  =  0;  i  <  pContent->refreshImObjRulesReq.usCnt;  i  ++  )  {
		 if  (  !pContent->refreshImObjRulesReq.mems[i].uiRuleType  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "mcProcResp_refreshImObjRulesReq failed, req.uiRuleType error"  )  );
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    %s"  ),  tBuf  );
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "%s"  ),  tBuf  );
			 #endif
			 goto  errLabel;
		 }
		 #ifdef  __DEBUG__
				 REFRESH_imObjRule_reqMem	*  pMem  =  &pContent->refreshImObjRulesReq.mems[i];
				 traceLog((TCHAR*)  _T(  "rules[%d], idInfo_related %I64u, Rule %d, uiCmd %d"  ),  i,  pMem->idInfo_related.ui64Id,  pMem->uiRuleType,  pMem->uiCmd  );
		 #endif
	 }
	 #ifdef  __DEBUG__
			 traceLog((TCHAR*)  _T(  "mcProcResp_refreshImObjRulesReq: get %d rules"  ),  pContent->refreshImObjRulesReq.usCnt  );
	 #endif
#endif

	 
	 if  (  pContent->refreshImObjRulesReq.usCnt  
		 ||  pContent->refreshImObjRulesReq.ucbRetrieveAll  )  {

#ifdef  __NOTSUPPORT_DB__
		traceLog((TCHAR*)  _T(  "Not finished: mcProcResp_refreshImObjRulesReq"  )  );
#else
	  
		 pProcInfo->recoverImObjRules(  pDbFuncs,  pSubThreadInfo->pDb,  iDbType,  _T(  ""  ),  &pMisCnt->idInfo,  &pContent->refreshImObjRulesReq,  pMisCnt->refreshImObjRules.tStart_toRetrieveAll  );

#endif

	 }


	 if  (  pContent->refreshImObjRulesReq.ucbRetrieveAll  )  {
		 if  (  !pContent->refreshImObjRulesReq.ucbEnd
			 &&  pContent->refreshImObjRulesReq.usCnt  )
		 {
			 IM_L_STREAM		*		pStream		=	NULL;
			   
			 MACRO_prepareForTran(  );

			 memset(  &req,  0,  sizeof(  req  )  );
			 req.uiType  =  CONST_imCommType_refreshImObjRulesReq;
			 req.ucbRetrieveAll  =  TRUE;
			 req.usMaxMemsPerSnd  =  mycountof(  req.mems  );

			 req.u.req.ucbNext  =  TRUE;
			 REFRESH_imObjRule_reqMem  *  pMem  =  &pContent->refreshImObjRulesReq.mems[pContent->refreshImObjRulesReq.usCnt  -  1];
			 req.u.req.idInfo_related.ui64Id  =  pMem->idInfo_related.ui64Id;
			 req.u.req.uiRuleType  =  pMem->uiRuleType;
			 req.u.req.usIndex  =  pMem->usIndex;
		
			 if  (  sizeof(  IM_L_STREAM  )  >  sizeof(  pCtx->common.pMsgBuf_forInput[0]  )  )  goto  errLabel;
			 pStream  =  (  IM_L_STREAM  *  )pCtx->common.pMsgBuf_forInput;	//  tmpMallocObj.malloc(  sizeof(  IM_STREAM_CONTENT  )  );
			 MACRO_memset_imLStream(  pStream  );
			 pStream->uiType  =  CONST_imCommType_lStream;
			 pStream->uiContentType  =  req.uiType;
			 len  =  sizeof(  pStream->buf  );
			 if  (  refreshImObjRulesReq2Stream(  pStream->uiContentType,  &req,  pStream->buf,  (  unsigned  int  *  )&len  )  )  goto  errLabel;
			 pStream->ulStreamLen  =  len;
			 len  +=  offsetof(  IM_L_STREAM,  buf  ); 

			 //
			 pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_refreshImObjListReq,  tStartTran,  uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  0,  0,  NULL,  0  ); 

			 iErr  =  0;  goto  errLabel;
		 }

		 if  (  g_dbFuncs.pf_deleteOldImObjRule_mcProcResp_refreshImObjRulesReq(  pSubThreadInfoParam,  pSci,  pMisCnt,  pMsgInput,  pCtx  )  )  goto  errLabel;
		 //
#ifdef  __DEBUG__
		//  traceLog((TCHAR*)  _T(  "Not finished, 未完成，要从数据库里一次性读出所有的策略，然后，更新到内存messenger里"  )  );
#endif
		
		 //
		 QY_MESSENGER_ID	idInfo_related;
		 QY_im_rules		imRules;
		 QY_imObj_rules		rules;
		 QY_MESSENGER_ID	idInfo_tmp;

		 //  先读取全局策略，更新到misCnt里
		 idInfo_related.ui64Id  =  0;
		 if  (  g_dbFuncs.pf_bGetImObjRulesReq(  pSubThreadInfo->pDb,  pQyMc->cfg.db.iDbType,  _T(  ""  ),  0,  &idInfo_related,  NULL,  0,  &req  )  )  {
			 imObjRulesReq2ImRules(  &req,  &imRules  );
			 //
			 memcpy(  &pMisCnt->imRules,  &imRules,  sizeof(  pMisCnt->imRules  )  );
		 }

		 for  (  ;  ;  )  {
			  //  再顺序读取每个messenger的rules
			  if  (  g_dbFuncs.pf_selectNextImObjRule_mcProcResp_refreshImObjRulesReq(  pSubThreadInfo,  pSci,  pMisCnt,  pMsgInput,  pCtx,  &idInfo_related  )  )  break;
			  //
			  if  (  g_dbFuncs.pf_bGetImObjRulesReq(  pSubThreadInfo->pDb,  pQyMc->cfg.db.iDbType,  _T(  ""  ),  0,  &idInfo_related,  NULL,  0,  &req  )  )  {				

				  imObjRulesReq2Rules(  &req,  &idInfo_related,  &rules  );
				  //
				  QM_OBJQ_MEM				mem;		
				  QMEM_MESSENGER_CLI	*	pQMem;
				  if  (  !findQMemByKey(  0,  pMisCnt->pObjQ,  &idInfo_related,  &mem  )  )  {
					  pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
					  if  (  pQMem  )  {
						  memcpy(  &pQMem->rules,  &rules,  sizeof(  pQMem->rules  )  );				  
					  }			  
				  }
			  }			
		 }

		 //
		 pMisCnt->refreshImObjRules.tLastRefreshedTime  =  pMisCnt->refreshImObjRules.tStart_toRetrieveAll;

		 //  2014/04/28
#ifdef  __DEBUG__
		 traceLog((TCHAR*)_T("All imObjRules retrieved"));
#endif
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "All imObjRules retrieved"  )  );
		 
		 //  2012/07/17. 这里需要让mainFrame刷新下用户信息
#ifndef  __qmdConn__
		 PostMessage(  pQyMc->gui.hMainWnd,  WM_COMMAND,  MAKEWPARAM(  ID_qyRefresh,  0  ),  0  );
#endif

		 //
		 iErr  =  0;  goto  errLabel;
	 }

	 notifyProgressEnd(  &pQyMc->gui.progress,  pMsgInput->uiTranNo,  0  );

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "mcProcResp_refreshImObjRulesReq failed"  )  );
		 #endif
	 }
	 return  iErr;
}

//  2015/08/01
 int  mcProcResp_procOfflineRes(  void  *  pSubThreadInfoParam,  QY_SERVICEGUI_INFO  *  pSci,  MIS_CNT  *  pMisCnt,  MIS_MSG_INPUT  *  pMsgInput,  CTX_MC_scheduler  *  pCtx  )
{
	 int								iErr													=	-1;
	 MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 MC_VAR_isCli					*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	 QY_MC							*	pQyMc													=	pProcInfo->pQyMc;
	 //  
	 IM_CONTENTU					*	pContent												=	NULL;
	 
	 int								iDbType													=	pQyMc->cfg.db.iDbType;

	 TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]						=	_T(  ""  );
	 //  CDBVariant							varVals[64];
	 char								timeBuf[128]											=	"";
	 char								idStr[CONST_qyMessengerIdStrLen  +  1];

	 int								i;
	 TCHAR								tBuf[255  +  1]											=	_T(  ""  );
	 //
	 int								len;
	 //
	 int								tmpiRet;
	 //  
	 REFRESH_imObjRules_req				req;
	 //  CDBVariant							varVals[1];
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;


	 if  (  isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  )  return  -1;
	 pContent  =  M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );
	 if  (  !pContent  )  return  -1;
	 
	 if  (  pContent->uiType  !=  CONST_imCommType_procOfflineRes  )  goto  errLabel;
	 if  (  !pContent->procOfflineResU.common.ucbResp  )  goto  errLabel;
	 //

	 if  (  !pContent->procOfflineResU.getCfgs.resp.idInfo_resServ.ui64Id  )  {
		 showInfo_open0(  0,  0,  _T(  "Warning: mcProcResp_procOfflineRes, idInfo_res is 0"  )  );
	 }

	 //
	 pMisCnt->procOfflineRes.idInfo_resServ.ui64Id  =  pContent->procOfflineResU.getCfgs.resp.idInfo_resServ.ui64Id;
	 
		 //
#ifdef  __DEBUG__
		//  
#endif
		

	 notifyProgressEnd(  &pQyMc->gui.progress,  pMsgInput->uiTranNo,  0  );

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "mcProcResp_procOfflineRes failed"  )  );
		 #endif
	 }
	 return  iErr;
}

 //
 int  filePrefix2tTime(  char  *  filePrefix,  time_t  *  pt  );

 //
 int  fileName2Res(  LPCTSTR  fileName0,  QIS_offline_res  *  pRes  )
{
	if  (  !fileName0  )  return  -1;

	TCHAR  *  pT0;
	TCHAR  *  pT;

	pT0  =  (  TCHAR  *  )_tcschr(  fileName0,  _T(  '_'  )  );
	if  (  !pT0  )  return  -1;
	if  (  pT0  -  fileName0  !=  CONST_qyTimeLen  )  return  -1;
	//
	TCHAR  tBuf[128]  =  _T(  ""  );
	char  buf[128]  =  "";
	safeTcsnCpy(  fileName0,  tBuf,  CONST_qyTimeLen  +  1  );
	myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
	//
	if  (  filePrefix2tTime(  buf,  &pRes->tCreationTime  )  )  return  -1;

	//
#ifdef  __DEBUG__
	{
		char  buff[128];
		getTimeStr(  pRes->tCreationTime,  buff,  mycountof(  buff  )  );
		int  ii  =  9;
	}
#endif

	//
	TCHAR  *  fileName  =  pT0  +  1;
	//
	pT  =  (  TCHAR  *  )_tcschr(  fileName,  _T(  '_'  )  );
	if  (  !pT  )  return  -1;

	if  (  fileName[0]  !=  'q'
		||  fileName[1]  !=  'm'  )
	{
		return  -1;
	}

	QY_MESSENGER_ID  idInfo  =  {0};
	//idInfo.ui64Id  =  _ttol(  fileName  +  2  );
	char  idStr[CONST_qyMessengerIdStrLen  +  1]  =  "";
	safeTcsnCpy(  fileName  +  2,  tBuf,  pT  -  (  fileName  +  2  )  +  1  );
	myTChar2Utf8(  tBuf,  idStr, mycountof(  idStr  )  );
	idStr2Info(  idStr,  &idInfo  );

	pT  ++  ;
	safeTcsnCpy(  pT,  pRes->name,  mycountof(  pRes->name  )  );
	pRes->res.idInfo.ui64Id  =  idInfo.ui64Id;

	return  0;
}

 //
 typedef  struct  __param_enumOfflineFile_t  {
				  unsigned  char	ucbP2p1;
				  
				  //
				  unsigned char		ucbMe;
		  		  QY_MESSENGER_ID	idInfo_from;
		  		  QY_MESSENGER_ID	idInfo_peer;

				  //
				  unsigned  int		nSkipped;
				  TCHAR				keyword[128];

 }		 PARAM_enumOfflineFile;

 //
 int  tmpHandler_enumOfflineFile(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int					iErr			=	-1;
	 PARAM_enumOfflineFile  *  pParam		=	(  PARAM_enumOfflineFile  *  )p0;
	 PROC_offlineRes_u	*	pResp			=	(  PROC_offlineRes_u  *  )p1;
	 WIN32_FIND_DATA	*	pData			=	(  WIN32_FIND_DATA  *  )p2;
	 //

	 if  (  pResp->common.usSubtype  !=  CONST_procOfflineResSubtype_retrieve  )  return  -1;
	 PROC_offlineRes_retrieve  *  pRetrieve  =  &pResp->retrieve;

	 //  traceLogA(  (char*)  "得到%s",  pData->cFileName  );
	 if  (  bDir(  pData->cFileName  )  )  return  0;

	 //
	 if  (  pRetrieve->resp.usCnt  >=  mycountof(  pRetrieve->resp.mems  )  )  {
		 iErr  =  1;  goto  errLabel;
	 }
	 QIS_offline_res* pMem; pMem = &pRetrieve->resp.mems[pRetrieve->resp.usCnt];
	 memset(  pMem,  0,  sizeof(  pMem[0]  )  );

	 //
	 BOOL  bOk;bOk = FALSE;
		
	 //
	 do  {
	     if  (  fileName2Res(  pData->cFileName,  pMem  )  )  {		 
			 //  skipped
			 break;
		 }
		 
		 //
		 pMem->ui64FileLen  =   ( pData->nFileSizeHigh * ( MAXDWORD+1)) + pData->nFileSizeLow;		   
		 //
		 if  (  !pParam  )  {
			 bOk  =  TRUE;
			 break;			   
		 }

		 //
		 if  (    !pParam->ucbP2p1  )  {			
			 bOk  =  TRUE;
			 break;
		 }					 

		 //  p2p		
		 if  (  pParam->ucbMe  )		{    //  发给我的				 				
			 if  (  pMem->res.idInfo.ui64Id  ==  pParam->idInfo_peer.ui64Id  )  {   //  peer发给我的
				 bOk  =  TRUE;				   					 
			 }			   					 
			 }			
		 else  {    //  我发给peer的				
			   if  (  pMem->res.idInfo.ui64Id  ==  pParam->idInfo_from.ui64Id  )  {					   
				   bOk  =  TRUE;				   					  
			   }			   		   
		 }
	 
	 }  while  (  FALSE  );


	 
	 //	
	 if  (  bOk  )  {	
		 //
		 BOOL  bSkipped  =  FALSE;
		 //
		 if  (  pParam->nSkipped  )  {			
			 bSkipped  =  TRUE;
			 pParam->nSkipped  --  ;
		 }			 		
		 if  (  pParam->keyword[0]  )  {
			 if  (  !_tcsstr(  pMem->name,  pParam->keyword  )  )  {			
				 bSkipped  =  TRUE;						 
			 }
		 }
		 //
		 if  (  !bSkipped  )  {
			 pRetrieve->resp.usCnt  ++  ;		
		 }
	 }

	 //  else  traceLogA(  (char*)  "%s is no out tmp file",  pData->cFileName  );

	 iErr  =  0;
errLabel:

	 return  iErr;		// 这里要防止中途退出，这样将使文件不能顺利清理完毕
}

 //
 //  2015/08/01
 int  mcProcReq_procOfflineRes(  void  *  pSubThreadInfoParam,  QY_SERVICEGUI_INFO  *  pSci,  MIS_CNT  *  pMisCnt,  MIS_MSG_INPUT  *  pMsgInput,  CTX_MC_scheduler  *  pCtx  )
{
	 int								iErr													=	-1;
	 MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 MC_VAR_isCli					*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;
	 QY_MC							*	pQyMc													=	pProcInfo->pQyMc;
	 //  
	 IM_CONTENTU					*	pContent												=	NULL;
	 
	 int								iDbType													=	pQyMc->cfg.db.iDbType;

	 TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]						=	_T(  ""  );
	 //  CDBVariant							varVals[64];
	 char								timeBuf[128]											=	"";
	 char								idStr[CONST_qyMessengerIdStrLen  +  1];

	 int								i;
	 TCHAR								tBuf[255  +  1]											=	_T(  ""  );
	 //
	 int								len;
	 //
	 int								tmpiRet;
	 //  
	 REFRESH_imObjRules_req				req;
	 //  CDBVariant							varVals[1];
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;


	 if  (  isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  )  return  -1;
	 pContent  =  M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );
	 if  (  !pContent  )  return  -1;
	 
	 if  (  pContent->uiType  !=  CONST_imCommType_procOfflineRes  )  goto  errLabel;
	 if  (  pContent->procOfflineResU.common.ucbResp  )  goto  errLabel;
	 //
	 PROC_offlineRes_u* pReq; pReq = &pContent->procOfflineResU;
	 
	 
	 //  2015/08/10
	 if  (  !bSupported_fileServer(  pQyMc )  )  {
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "req of procOfflineRes not supported because this is not fileServer"  )  );
		 showInfo_open0(  0,  0,  tBuf  );
		 showNotification(  0,  0,  0,  0,  0,  0,  tBuf  );
		 goto  errLabel;
	 }
	 
	 
	 //
	 if  (  pReq->common.usSubtype  ==  CONST_procOfflineResSubtype_retrieve  )  {

		 //
		 if (!isUcFlgRouteTalkData(pMsgInput->ucFlg) 
			 //&& !isUcFlgTalkData(pMsgInput->ucFlg)
			 ) 
		 {
			 goto  errLabel;
		 }

		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "Not finished: If this is a group, req should be sent to server to verify whether the idInfo_from is a valid grpMem"  )  );
		#endif
				 

		 //
		 int  lenInBytes  =  0;
		 unsigned  char  ucFlg  =  0;

		 //
		 PROC_offlineRes_u  resp;		
		 memset(  &resp,  0,  sizeof(  resp  )  );		
		 resp.common.uiType  =  CONST_imCommType_procOfflineRes;
		 resp.common.usSubtype  =  pReq->common.usSubtype;
		 //

		 //
		 TCHAR  *  pDir  =  (TCHAR*)_T(  "C:\\Users\\t1650\\Documents\\qmFileServer\\113\\"  );
		 TCHAR		tFileBuf[256]  =  _T(  ""  );
		 QY_MESSENGER_ID  idInfo_peer;

		 //
		 PARAM_enumOfflineFile  param;
		 memset(  &param,  0,  sizeof(  param  )  );
		 //
		 unsigned  short  max_usCnt_page  =  min(  pContent->procOfflineResU.retrieve.req.max_usCnt,  mycountof(  pContent->procOfflineResU.retrieve.resp.mems  )  );
		 param.nSkipped  =  max_usCnt_page  *  pContent->procOfflineResU.retrieve.req.usIndex_page;
		 safeTcsnCpy(  pContent->procOfflineResU.retrieve.req.keyword,  param.keyword,  mycountof(  param.keyword  )  );
		 tTrim(  param.keyword  );

		 //
		 if  (  pContent->procOfflineResU.retrieve.req.ucbP2p  )  {			 

			 //
			 if  (  !pContent->procOfflineResU.retrieve.req.idInfo_logicalPeer.ui64Id  )  {
				 showInfo_open0(  0,  0,  _T(  "myProcReq_procOfflineRes failed: p2p, logicalPeer is 0"  )  );
				 goto  errLabel;
			 }
			 			
			 //
			 idInfo_peer.ui64Id  =  pContent->procOfflineResU.retrieve.req.idInfo_logicalPeer.ui64Id;				
			 getPath_fileServer(  pQyMc,  &pMsgInput->data.route.idInfo_from,  &idInfo_peer,  tFileBuf,  mycountof(  tFileBuf  )  );				 
			 //
			 param.ucbP2p1  =  TRUE;
			 //
			 param.ucbMe  =  FALSE;				
			 param.idInfo_from.ui64Id  =  pMsgInput->data.route.idInfo_from.ui64Id;
			 param.idInfo_peer.ui64Id  =  pContent->procOfflineResU.retrieve.req.idInfo_logicalPeer.ui64Id;				 
			 //
			 qwmEnumUsrDir(  &pQyMc->env,  tFileBuf,  tmpHandler_enumOfflineFile,  &param,  &resp  );  			 
			 }
		 else  {
			   if  (  pContent->procOfflineResU.retrieve.req.idInfo_logicalPeer.ui64Id  )  idInfo_peer.ui64Id  =  pContent->procOfflineResU.retrieve.req.idInfo_logicalPeer.ui64Id;
			   else  idInfo_peer.ui64Id  =  pMsgInput->data.route.idInfo_from.ui64Id;			 
			   //
			   getPath_fileServer(  pQyMc,&pMsgInput->data.route.idInfo_from,  &idInfo_peer,  tFileBuf,  mycountof(  tFileBuf  )  );
							 
			   //
			   qwmEnumUsrDir(  &pQyMc->env,  tFileBuf,  tmpHandler_enumOfflineFile,  &param,  &resp  );  
		 }

#ifdef  __DEBUG__
		 if  (  resp.retrieve.resp.usCnt  <  mycountof(  resp.retrieve.resp.mems  )  )  {
			 QIS_offline_res  *  pMem  =  &resp.retrieve.resp.mems[resp.retrieve.resp.usCnt];
			 pMem->res.resObj.uiObjType  =  CONST_objType_offlineFile;
			 _sntprintf(  pMem->name,  mycountof(  pMem->name  ),  _T(  "射雕英雄传.txt"  )  );
			 resp.retrieve.resp.usCnt  ++  ;
		 }
#endif
		 
		 
		 //		
		 lenInBytes  =  sizeof(  resp  );			
		 //
		 ucFlg  =  0;			
		 ucFlg  |=  CONST_commFlg_resp;		//  ×¢Òâ£¬ÕâÀïÊÇÏìÓ¦
		 					 
		 if  (  pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_outputTask,  ucFlg,  CONST_qyRc_ok,  pMsgInput->tStartTime,  pMsgInput->uiTranNo,  0,  (  char  *  )&resp,  lenInBytes,  &pMsgInput->addr_logicalPeer.idInfo,  &pMsgInput->data.route.idInfo_from,  pMsgInput->uiChannelType,  pCtx->common.pMsgBuf,  FALSE  )  )  goto  errLabel;


	 }
	 else  if  (  pReq->common.usSubtype  ==  CONST_procOfflineResSubtype_del  )  {

		 //
		 if (!isUcFlgRouteTalkData(pMsgInput->ucFlg) 
			 //&& !isUcFlgTalkData(pMsgInput->ucFlg)
			 ) 
		 {
			 goto  errLabel;
		 }

		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "Not finished: If this is a group, req should be sent to server to verify whether the idInfo_from is a valid grpMem"  )  );
		#endif
				 

		 //
		 int  lenInBytes  =  0;
		 unsigned  char  ucFlg  =  0;
		 unsigned  short  usCode  =  CONST_qyRc_ok;

		 //
		 PROC_offlineRes_u  resp;		
		 memset(  &resp,  0,  sizeof(  resp  )  );		
		 resp.common.uiType  =  CONST_imCommType_procOfflineRes;
		 resp.common.usSubtype  =  pReq->common.usSubtype;
		 resp.common.ucbResp  =  TRUE;

		 //
		 TCHAR  *  pDir  =  (TCHAR*)_T(  "C:\\Users\\t1650\\Documents\\qmFileServer\\113\\"  );
		 TCHAR		tFileBuf[256]  =  _T(  ""  );
		 QY_MESSENGER_ID  idInfo_peer;
		 QY_MESSENGER_ID  idInfo_sender;

		 
		
		 idInfo_peer.ui64Id  =  pContent->procOfflineResU.del.idInfo_logicalPeer.ui64Id;		
		 if  (  !idInfo_peer.ui64Id  )  idInfo_peer.ui64Id  =  pMsgInput->data.route.idInfo_from.ui64Id;
		 idInfo_sender.ui64Id  =  pContent->procOfflineResU.del.idInfo_sender.ui64Id;
		 if  (  !idInfo_sender.ui64Id  )  idInfo_sender.ui64Id  =  pMsgInput->data.route.idInfo_from.ui64Id;

		 //
		 if  (  getPath_fileServer(  pQyMc,  &pMsgInput->data.route.idInfo_from,  &idInfo_peer,  tFileBuf,  mycountof(  tFileBuf  )  )  )  {		
			 goto  errLabel;			
		 }			 
		 //		
		 char  filePrefix[128]  =  "";
		 if  (  getFilePrefix_fileServer(  pReq->del.tCreationTime,  filePrefix,  mycountof(  filePrefix  )  )  )  goto  errLabel;
#if  10
		 _sntprintf(  tFileBuf,  mycountof(  tFileBuf  ),  _T(  "%s\\%S_qm%I64u_%s"  ),  tFileBuf,  filePrefix,  idInfo_sender.ui64Id,  pReq->del.fileName  );
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  tFileBuf  );
		 #endif

		 //
		 BOOL  bDel  =  DeleteFile(  tFileBuf  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tFileBuf,  bDel  ?  _T(  "deleted"  )  :  _T(  "can't be delelted"  )  );
		 showInfo_open0(  0,  0,  tBuf  );

		 //
		 if  (  !bDel  )  usCode  =  CONST_qyRc_err;
#endif



#ifdef  __DEBUG__
#endif
		 
		 
		 //		
		 lenInBytes  =  sizeof(  resp  );			
		 //
		 ucFlg  =  0;			
		 ucFlg  |=  CONST_commFlg_resp;		//  ×¢Òâ£¬ÕâÀïÊÇÏìÓ¦
		 					 
		 if  (  pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_outputTask,  ucFlg,  usCode,  pMsgInput->tStartTime,  pMsgInput->uiTranNo,  0,  (  char  *  )&resp,  lenInBytes,  &pMsgInput->addr_logicalPeer.idInfo,  &pMsgInput->data.route.idInfo_from,  pMsgInput->uiChannelType,  pCtx->common.pMsgBuf,  FALSE  )  )  goto  errLabel;


		 }
	 else  {
		   #ifdef  __DEBUG__
				   traceLog((TCHAR*)  _T(  "mcProcReq_procOfflineRes failed, unprocessed subtype %d"  ),  (  int  )pReq->common.usSubtype  );
		   #endif
		   goto  errLabel;
	 }


	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "mcProcResp_procOfflineRes failed"  )  );
		 #endif
	 }
	 return  iErr;
}


//
  int  procMsgInput_scheduler_req(  MT_SUBTHREADINFO  *  pSubThreadInfo,  QY_SERVICEGUI_INFO  *  pSci,  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSG_INPUT  *  pMsgInput,  unsigned  int  lenInBytes_input,  CTX_MC_THREAD  *  pCtx  )
{
	 int						iErr									=	-1;
	 IM_CONTENTU		*	pContent								=	NULL;
	 TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1]		=	_T(  ""  );
	 char						timeBuf[CONST_qyTimeLen  +  1]			=	"";
	 //
	 if  (  !pProcInfo  )  return  -1;
	 QY_MC  *  pQyMc  =  pProcInfo->pQyMc;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	 
	 if  (  !pMisCnt  )  return  -1;

	 #ifdef  __DEBUG__
			 traceLogA(  (char*)  "procMsgInput_scheduler_req called"  );
	 #endif

	 if  (  isUcFlgResp(  pMsgInput->ucFlg  )  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "procMsgInput_scheduler_req failed, not req"  );
		 #endif
		 goto  errLabel;
	 }
	 if  (  !pMsgInput->ucbConvrted  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "procMsgInput_scheduler_req: not converted"  );  
		 #endif
		 goto  errLabel;
	 }
	 pContent  =  M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );
	 

	 switch  (  pContent->uiType  )  {

				   //  2015/08/01
			 case  CONST_imCommType_procOfflineRes:
				   if  (  mcProcReq_procOfflineRes(  pSubThreadInfo,  pSci,  pMisCnt,  pMsgInput,  (  CTX_MC_scheduler  *  )pCtx  )  )  goto  errLabel;
				   break;
				   //
			 default:
					 #ifdef  __DEBUG__
							 traceLogA(  (char*)  "procMsgInput_scheduler_req: unprocessed contentType, %s",  pContent->uiType  );
					 #endif
					 break;
	
	 }
	
	 iErr  =  0;
errLabel:

	 if  (  iErr  )  {
	 }


	 return  iErr;
}

//
 int  procMsgInput_scheduler_resp(  MT_SUBTHREADINFO  *  pSubThreadInfo,  QY_SERVICEGUI_INFO  *  pSci,  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSG_INPUT  *  pMsgInput,  unsigned  int  lenInBytes_input,  CTX_MC_THREAD  *  pCtx  )
{
	 int						iErr									=	-1;
	 IM_CONTENTU		*	pContent								=	NULL;
	 TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1]		=	_T(  ""  );
	 char						timeBuf[CONST_qyTimeLen  +  1]			=	"";
	 //
	 if  (  !pProcInfo  )  return  -1;
	 QY_MC  *  pQyMc  =  pProcInfo->pQyMc;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	 
	 if  (  !pMisCnt  )  return  -1;

	 #ifdef  __DEBUG__
	 if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
		 traceLogA((char*)"procMsgInput_scheduler_resp called");
	 }
	 #endif

	 if  (  !isUcFlgResp(  pMsgInput->ucFlg  )  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "procMsgInput_scheduler_resp failed, not resp"  );
		 #endif
		 goto  errLabel;
	 }
	 if  (  !pMsgInput->ucbConvrted  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "procMsgInput_scheduler_resp: not converted"  );  
		 #endif
		 goto  errLabel;
	 }
	 if  (  isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  
		 //||  isUcFlgTalkData(  pMsgInput->ucFlg  )  
		 )  {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "procMsgInput_scheduler_resp: not addrTalkData or talkData"  );  
		 #endif
		 goto  errLabel;
	 }
	 pContent  =  (  IM_CONTENTU  *  )&pMsgInput->data;
	 

	 switch  (  pContent->uiType  )  {

			 case  CONST_imCommType_simpleResp:  
				   switch  (  pContent->simpleResp.uiContentType_org  )  {
						   case  CONST_imCommType_messengerRegInfo:  {
							     traceLogA(  (char*)  "messengerRegInfo"  );
								 
							#if  0
								 char						idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";	
								 if  (  !idInfo2Str(  &pMisCnt->idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
							#endif

							#ifndef  __NOTSUPPORT_DB__
#if  0
								 getCurTime(  timeBuf  );
								 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set tCommitTime='%s' where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyImObjRegInfoTab1,  CString(  timeBuf  ),  getDbValStr(  pSci->cfg.iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  CString(  idStr  )  );
								 if  (  !bQyExecSql(  pSubThreadInfo->pDb,  sqlBuf  )  )  {
									 traceLogA(  (char*)  ""  );  goto  errLabel;
								 }
#endif
								 if  (  !g_dbFuncs.pf_bUpdateImObjRegInfo_procMsgInput_scheduler(  pSubThreadInfo->pDb,  pSci,  pMisCnt,  &pMisCnt->idInfo  )  )  goto  errLabel;  
							#endif
								 //
								 }
								 break;
						   case  CONST_imCommType_messengerPcInfo:
							     traceLogA(  (char*)  "procMsgInput_scheduler: resp, messengerPcInfo"  );
								 //
								 pMisCnt->ucbNeedSndDevInfo  =  FALSE;
								 break;
						   case  CONST_imCommType_messengerAccount:
							     traceLogA(  (char*)  "procMsgInput_scheduler: resp, messengerAccount"  );
								 //
							     //  pProcInfo->bInProgress_toSetPasswd  =  FALSE;
								 notifyProgressEnd(  &pQyMc->gui.progress,  pMsgInput->uiTranNo,  0  );
							     break;
						   default:
							       break;
				       
				   }
				   //
				   break;		   

			 case  CONST_imCommType_retrieveImGrpListResp:
			 case  CONST_imCommType_retrieveImGrpMemListResp:
			 case  CONST_imCommType_retrieveContactListResp:
			 case  CONST_imCommType_retrieveImObjListEndResp:
				   if  (  mcProcResp_retrieveImObjListReq(  pSubThreadInfo,  pSci,  pMisCnt,  pMsgInput,  pCtx  )  )  goto  errLabel;
				   break;
			 //  case  CONST_imCommType_intervalParams:
			 case  CONST_imCommType_getCfgsReq:
			 case  CONST_imCommType_retrieveToPaths:
				   if  (  mcProcResp_getCfgs(  pSubThreadInfo,  pSci,  pMisCnt,  pMsgInput,  pCtx  )  )  goto  errLabel;
				   break;
			 case  CONST_imCommType_retrievePhoneMsgrs:
				   if  (  mcProcResp_retrievePhoneMsgrs(  pSubThreadInfo,  pSci,  pMisCnt,  pMsgInput,  pCtx  )  )  goto  errLabel;
				   break;
			 case  CONST_imCommType_retrieveDynBmps:
				   if  (  mcProcResp_retrieveDynBmps(  pSubThreadInfo,  pSci,  pMisCnt,  pMsgInput,  (  CTX_MC_scheduler  *  )pCtx  )  )  goto  errLabel;
				   break;
			 case  CONST_imCommType_refreshImObjRulesReq:
				   if  (  mcProcResp_refreshImObjRulesReq(  pSubThreadInfo,  pSci,  pMisCnt,  pMsgInput,  (  CTX_MC_scheduler  *  )pCtx  )  )  goto  errLabel;
				   break;
				   //  2015/08/01
			 case  CONST_imCommType_procOfflineRes:
				   if  (  mcProcResp_procOfflineRes(  pSubThreadInfo,  pSci,  pMisCnt,  pMsgInput,  (  CTX_MC_scheduler  *  )pCtx  )  )  goto  errLabel;
				   break;
				   //
			 default:
					 #ifdef  __DEBUG__
							 traceLogA(  (char*)  "procMsgInput_scheduler_resp: unprocessed contentType, %s",  pContent->uiType  );
					 #endif
					 break;
	
	 }
	
	 iErr  =  0;
errLabel:

	 if  (  iErr  )  {
	 }


	 return  iErr;
}

#ifndef  __NOTSUPPORT_DB__
 int  procImMsgLogQ_scheduler(  MT_SUBTHREADINFO  *  pSubThreadInfo,  MC_VAR_isCli  *  pProcInfo,  void * pDBManager,  MIS_MSGU  *  pMsg  )
{
	int				iErr	=	-1;
	QY_MC		*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;
	int				i;
	unsigned  int	len;

	IM_MSG_RCD		rcd;
	IM_CONTENTU	*	pContent;

	for  (  i  =  0;  i  <  3;  i  ++  )  {				  
		 len  =  sizeof(  pMsg[0]  );
		 if  (  qGetMsg(  &pProcInfo->imMsgLogQ,  pMsg,  &len  )  )  break;
		 memset(  (  (  char  *  )pMsg  )  +  len,  0,  min(  256,  sizeof(  pMsg[0]  )  -  len  )  );
		 switch  (  pMsg->uiType  )  {
				 case  CONST_misMsgType_talk:
					   pContent  =  (  IM_CONTENTU  *  )pMsg->talk.data.buf;

					   if  (  pContent->uiType  ==  CONST_imCommType_htmlContent  )  {
						   memset(  &rcd,  0,  sizeof(  rcd  )  );
						   rcd.idInfo_send.ui64Id  =  pMsg->talk.data.route.idInfo_from.ui64Id;
						   rcd.tSendTime  =  pMsg->talk.tStartTime;
						   rcd.uiTranNo  =  pMsg->talk.uiTranNo;
						   //  uiSeqNo
						   //
						   rcd.idInfo_logicalPeer = pMsg->talk.addr_logicalPeer.idInfo;
						   //
						   rcd.idInfo_recv.ui64Id  =  pMsg->talk.data.route.idInfo_to.ui64Id;
						   //
						   rcd.uiType  =  pContent->uiType;
						   //
						   lstrcpyn(  rcd.content,  pContent->html.wBuf,  mycountof(  rcd.content  )  );
						   lstrcpyn(rcd.logMsgContent, pContent->html.wBuf, mycountof(rcd.logMsgContent));
						   //
						   rcd.tRecvTime  =  pMsg->talk.tRecvTime;
						   mytime(  &rcd.firstTime  );
						   mytime(  &rcd.lastTime  );
						   mytime(  &rcd.tLastModifiedTime  );

						   logImMsg(  pQyMc->p_g_dbFuncs,  pSubThreadInfo->pDb,  pQyMc->cfg.db.iDbType,  pDBManager,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &rcd  );

					   }
									 
					   break;
				 case  CONST_misMsgType_task:						     
					   pContent  =  (  IM_CONTENTU  *  )pMsg->task.data.buf;

					   if  (  1  )  {
						   memset(  &rcd,  0,  sizeof(  rcd  )  );
						   rcd.idInfo_send.ui64Id  =  pMsg->talk.data.route.idInfo_from.ui64Id;
						   rcd.tSendTime  =  pMsg->talk.tStartTime;
						   rcd.uiTranNo  =  pMsg->talk.uiTranNo;
						   //  uiSeqNo
						   //
						   rcd.idInfo_logicalPeer = pMsg->task.addr_logicalPeer.idInfo;
						   rcd.iTaskId = pMsg->task.iTaskId;
						   //
						   rcd.idInfo_recv.ui64Id  =  pMsg->task.data.route.idInfo_to.ui64Id;
						   //
						   rcd.uiType  =  pContent->uiType;
						   //  lstrcpyn(  rcd.content,  pContent->html.wBuf,  mycountof(  rcd.content  )  );
						   switch  (  rcd.uiType  )  {
								   case  CONST_imCommType_transferFileReq:
									     lstrcpyn(  rcd.content,  pContent->transferFileReq.fileName,  mycountof(  rcd.content  )  );							
										 lstrcpyn(rcd.logMsgContent, pContent->transferFileReq.fileName, mycountof(rcd.logMsgContent));
										 rcd.ui64FileLen = pContent->transferFileReq.ui64FileLen;
										 rcd.uiSizePerSnd_suggest = pContent->transferFileReq.uiSizePerSnd_suggest;
										 break;
								   case  CONST_imCommType_transferAvInfo:
									     if  (  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biWidth  &&  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biHeight  )  {
											 _sntprintf(  rcd.content,  mycountof(  rcd.content  ),  _T(  "%d * %d"  ),  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biWidth,  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biHeight  );
											 _sntprintf(rcd.logMsgContent, mycountof(rcd.logMsgContent), _T("%d * %d"), pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biWidth, pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biHeight);
										 }
										 rcd.idInfo_initiator = pContent->transferAvInfo.confCfg.idInfo_initiator;
										 break;
								   default:
									       break;
						   }
						   rcd.tRecvTime  =  pMsg->talk.tRecvTime;
						   mytime(  &rcd.firstTime  );
						   mytime(  &rcd.lastTime  );
						   mytime(  &rcd.tLastModifiedTime  );

						   logImMsg(  pQyMc->p_g_dbFuncs,  pSubThreadInfo->pDb,  pQyMc->cfg.db.iDbType,  pDBManager,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &rcd  );
					   }
					   break;

				 default:
				         traceLog((TCHAR*)  _T(  "scheduler: unprocessed msgType %d"  ),  pMsg->uiType  );						
						 break;
				  
		 }				   

	}

	iErr  =  0;
errLabel:
	return  iErr;
 }
#endif



  BOOL  bMeInfoNeedReg(  void  *  pDb,  int  iDbType,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_REGINFO  *  pRegInfo  )
{	
#ifdef  __NOTSUPPORT_DB__
	return  FALSE;
#else
	if  (  !pMisCnt  )  return  FALSE;
	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  FALSE;
	if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )   return  FALSE;
	QY_MC				*	pQyMc		=	pProcInfo->pQyMc;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  FALSE;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	if  (  !pRegInfo  )  return  FALSE;

	if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pMisCnt->cfg.misServName,  &pMisCnt->idInfo,  0,  NULL,  NULL,  pRegInfo,  NULL  )  )  return  FALSE;

	if  (  !bQyTimeValid(  pRegInfo->regTime  )  )  return  FALSE;	//  Õâ±íÃ÷¸Ã¼ÍÂ¼²»´æÔÚ

	if  (  bQyTimeValid(  pRegInfo->tCommitTime  )  )  return  FALSE;
	
	return  TRUE;
#endif
}


 int  sndMsgNeedReg_qmc(  MT_SUBTHREADINFO  *  pSubThreadInfo,  QY_SERVICEGUI_INFO  *  pSci,  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt  )
{
	int							iErr								=	-1;
	if  (  !pProcInfo  )  return  -1;
	QY_MC					*	pQyMc								=	pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;
	QY_MESSENGER_REGINFO		regInfo;
	unsigned  int				len;

	if  (  !bMeInfoNeedReg(  pSubThreadInfo->pDb,  pQyMc->cfg.db.iDbType,  pMisCnt,  &regInfo  )  )  {
		if  (  pMisCnt->ucTriesToReg  )  pMisCnt->ucTriesToReg  --  ;  //  Ã»ÓÐ¼ì²âµ½¼ÇÂ¼£¬¾Í°ÑÕâ¸ö³¢ÊÔ¼õÉÙÒ»´Î¡£
		iErr  =  0;  goto  errLabel;
	}


	{
		CQyMalloc					mallocObj_pStream;
		IM_L_STREAM				*	pStream				=	(  IM_L_STREAM  *  )mallocObj_pStream.mallocf(  sizeof(  IM_L_STREAM  )  );
		if  (  !pStream  )  return  -1;
		IM_L_STREAM				&	stream				=	*pStream;

		memset(  &stream,  0,  sizeof(  stream  )  );
		stream.uiType  =  CONST_imCommType_lStream;
		stream.uiContentType  =  CONST_imCommType_messengerRegInfo;
		len  =  sizeof(  stream.buf  );
		if  (  messengerRegInfo2Stream(  stream.uiContentType,  &regInfo,  stream.buf,  &len  )  )  goto  errLabel;
		stream.ulStreamLen  =  len;
		len  +=  offsetof(  IM_L_STREAM,  buf  ); 

		MACRO_prepareForTran(  );

		if  (  pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_refreshImObjListReq, tStartTran,  uiTranNo,  0,  (  char  *  )&stream,  len,  NULL,  NULL,  CONST_channelType_talking,  NULL,  FALSE  )  )  goto  errLabel;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}

 int  sndDevInfo_qmc(  MT_SUBTHREADINFO  *  pSubThreadInfo,  QY_SERVICEGUI_INFO  *  pSci,  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt  )
{
	int							iErr								=	-1;
	if  (  !pProcInfo  )  return  -1;
	QY_MC					*	pQyMc								=	pProcInfo->pQyMc;
	QY_MESSENGER_PCINFO			rcd;
	IM_L_STREAM				*	pStream								=	NULL;
	unsigned  int				len;

	if  (  !(  pStream  =  (  IM_L_STREAM  *  )mymalloc(  sizeof(  IM_L_STREAM  )  )  )  )  {
		traceLogA(  (char*)  "sndDevInfo_qmc . malloc failed."  );  goto  errLabel;
	}

	memset(  &rcd,  0,  sizeof(  rcd  )  );
	//
	rcd.uiType  =  pProcInfo->uiDevType;
	//
	//
	rcd.iPlatformId  =  pQyMc->env.iPlatformId;

	lstrcpyn(  rcd.pcName,  pProcInfo->authInfo.pcName,  mycountof(  rcd.pcName  )  );
	lstrcpyn(  rcd.domainName,  pProcInfo->authInfo.domainName,  mycountof(  rcd.domainName  )  );
	lstrcpyn(  rcd.osUsrName,  pProcInfo->authInfo.osUsrName,  mycountof(  rcd.osUsrName  )  );


	//
	MACRO_memset_imLStream(  pStream  );
	pStream->uiType  =  CONST_imCommType_lStream;
	pStream->uiContentType  =  CONST_imCommType_messengerPcInfo;
	len  =  sizeof(  pStream->buf  );
	if  (  messengerPcInfo2Stream(  pStream->uiContentType,  &rcd,  pStream->buf,  &len  )  )  goto  errLabel;
	pStream->ulStreamLen  =  len;
	len  +=  offsetof(  IM_L_STREAM,  buf  ); 

	MACRO_prepareForTran(  );

	if  (  pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_refreshImObjListReq, tStartTran,  uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  NULL,  CONST_channelType_talking,  NULL,  FALSE  )  )  goto  errLabel;


	iErr  =  0;
errLabel:

	if  (  pStream  )  myfree(  pStream  );

	return  iErr;

}


 
#define		MACRO_ft2Li(  ft, li  )	{	li.HighPart  =  ft.dwHighDateTime;  li.LowPart  =  ft.dwLowDateTime;	}

 int  getCpuUsage(  QY_ENV  *	pEnv,  MC_VAR_isCli  *  pProcInfo  )
{
	int							iErr						=	-1;
			
#ifndef  __WINCE__
	FILETIME			idleTime;
	FILETIME			kernelTime;
	FILETIME			usrTime;
	LARGE_INTEGER		liIdleTime;
	LARGE_INTEGER		liKernelTime;
	LARGE_INTEGER		liUsrTime;

	if  (  !myGetSystemTimes(  pEnv,  &idleTime,  &kernelTime,  &usrTime  )  )  goto  errLabel;

	MACRO_ft2Li(  idleTime,  liIdleTime  );
	MACRO_ft2Li(  kernelTime,  liKernelTime  );
	MACRO_ft2Li(  usrTime,  liUsrTime  );

	if  (  pProcInfo->status.cpu.oldIdleTime.QuadPart  )  {
		LARGE_INTEGER	mySysTime;
		LARGE_INTEGER	myIdleTime;

		mySysTime.QuadPart  =  liKernelTime.QuadPart  -  pProcInfo->status.cpu.oldKernelTime.QuadPart  +  liUsrTime.QuadPart  -  pProcInfo->status.cpu.oldUsrTime.QuadPart;
		myIdleTime.QuadPart  =  liIdleTime.QuadPart  -  pProcInfo->status.cpu.oldIdleTime.QuadPart;

		if  (  !mySysTime.QuadPart  )  goto  errLabel;

		int  iCpuUsage  =  (  int  )(  100.  *  (  mySysTime.QuadPart  -  myIdleTime.QuadPart  )  /  mySysTime.QuadPart  +  0.5  );
		//  traceLogA(  (char*)  "iCpuUsage %d",  iCpuUsage  );
		pProcInfo->status.cpu.iCpuUsage  =  iCpuUsage;
	}
	pProcInfo->status.cpu.oldIdleTime.QuadPart  =  liIdleTime.QuadPart;
	pProcInfo->status.cpu.oldKernelTime.QuadPart  =  liKernelTime.QuadPart;
	pProcInfo->status.cpu.oldUsrTime.QuadPart  =  liUsrTime.QuadPart;
#else

	DWORD	dwTickCnt,  dwIdleTime;
	dwTickCnt  =  GetTickCount(  );
	#ifndef  __TEST__
			 dwIdleTime  =  GetIdleTime(  );
	#else
			dwIdleTime  =  MAXDWORD;
	#endif
	if  (  dwIdleTime  ==  MAXDWORD  )  goto  errLabel;

	if  (  dwTickCnt  !=  pProcInfo->status.cpu.dwTickCnt_start_ce  )  {
		pProcInfo->status.cpu.iCpuUsage  =  100  -  100  *  (  dwIdleTime  -  pProcInfo->status.cpu.dwIdleTime_start_ce  )  /  (  dwTickCnt  -  pProcInfo->status.cpu.dwTickCnt_start_ce  );
	}

	pProcInfo->status.cpu.dwTickCnt_start_ce  =  dwTickCnt;
	pProcInfo->status.cpu.dwIdleTime_start_ce  =  dwIdleTime;

#endif

	iErr  =  0;
errLabel:
	return  iErr;
}


 int  getNetStat_isCli(  MC_VAR_isCli  * pProcInfo,  unsigned  int  nIntervalInMs  )
{
	int				iErr		=	-1;

	if  (  !pProcInfo  )  return  -1;
	//
	MIS_CNT		*	pMisCnt	=	getMisCntByIndex(  0,  pProcInfo,  0  );//&pProcInfo->misCnts[0];
	if  (  !pMisCnt  )  return  -1;
	//
	IM_NET_STAT		netStat;
	int				i;
	__int64			i64InOctets;
	__int64			i64OutOctets;

	if  (  !nIntervalInMs  )  return  -1;

	//
#ifdef  __DEBUG__
	//traceLog((TCHAR*)_T("getNetStat_isCli: nIntervalInMs %dms"), nIntervalInMs);
#endif 


	//
	memset(  &netStat,  0,  sizeof(  netStat  )  );
	for  (  i  =  0;  i  <  mycountof(  pMisCnt->channels  );  i  ++  )  {
		 MIS_CHANNEL  *  pChannel  =  &pMisCnt->channels[i];
		 //
		 i64InOctets  =  pChannel->status.netStat.ui64MsgDataLenRecvd  -  pChannel->status.oldNetStat.ui64MsgDataLenRecvd;
		 i64OutOctets  =  pChannel->status.netStat.ui64MsgDataLenSent  -  pChannel->status.oldNetStat.ui64MsgDataLenSent;
		 if  (  i64InOctets  <  0  ||  i64OutOctets  <  0  )  {
			 memcpy(  &pChannel->status.oldNetStat,  &pChannel->status.netStat,  sizeof(  pChannel->status.oldNetStat  )  );
			 goto  errLabel;
		 }

		 pChannel->status.netStat.uiInSpeedInKbps  =  i64InOctets  *  8.  /  nIntervalInMs;
		 pChannel->status.netStat.uiOutSpeedInKbps  =  i64OutOctets  *  8.  /  nIntervalInMs;
		 //
		 memcpy(  &pChannel->status.oldNetStat,  &pChannel->status.netStat,  sizeof(  pChannel->status.oldNetStat  )  );

		 //
		 netStat.ui64MsgDataLenRecvd  +=  pChannel->status.netStat.ui64MsgDataLenRecvd;
		 netStat.ui64MsgDataLenSent  +=  pChannel->status.netStat.ui64MsgDataLenSent;

		 //
		 switch  (  pChannel->uiType  )  {
				 case  CONST_channelType_media:
					   pProcInfo->status.netStat.uiInSpeedInKbps_v  =  pChannel->status.netStat.uiInSpeedInKbps;
					   pProcInfo->status.netStat.uiOutSpeedInKbps_v  =  pChannel->status.netStat.uiOutSpeedInKbps;
					   break;
				 case  CONST_channelType_realTimeMedia:
					   pProcInfo->status.netStat.uiInSpeedInKbps_a  =  pChannel->status.netStat.uiInSpeedInKbps;
					   pProcInfo->status.netStat.uiOutSpeedInKbps_a  =  pChannel->status.netStat.uiOutSpeedInKbps;
					   break;
				 case  CONST_channelType_robot:
					   pProcInfo->status.netStat.uiInSpeedInKbps_f  =  pChannel->status.netStat.uiInSpeedInKbps;
					   pProcInfo->status.netStat.uiOutSpeedInKbps_f  =  pChannel->status.netStat.uiOutSpeedInKbps;
					   break;
				 default:
						break;
		 }

		 //
#ifdef  __DEBUG__
		 TCHAR* pName = qyGetDesByType1(CONST_channelTypeTable, pChannel->uiType);
		 if (0) {
			 switch (pChannel->uiType) {
			 case  CONST_channelType_media:
			 case  CONST_channelType_realTimeMedia:

				 TCHAR  tBuf[128];
				 _sntprintf(tBuf, mycountof(tBuf), _T("%s: in %dkbps, out %dkbps. i64OutOctets %d, l2451"), pName, pChannel->status.netStat.uiInSpeedInKbps, pChannel->status.netStat.uiOutSpeedInKbps, i64OutOctets);
				 traceLog((TCHAR*)tBuf);
				 break;
			 default:
				 break;
			 }
		 }
#endif
	}

	i64InOctets		=	netStat.ui64MsgDataLenRecvd  -  pProcInfo->status.netStat.ins.ui64MsgDataLenRecvd;
	i64OutOctets	=	netStat.ui64MsgDataLenSent  -  pProcInfo->status.netStat.ins.ui64MsgDataLenSent;
	if  (  i64InOctets  <  0  ||  i64OutOctets  <  0  )  {
		//memcpy(  &pProcInfo->status.netStat,  &netStat,  sizeof(  pProcInfo->status.netStat  )  );
		pProcInfo->status.netStat.ins  =  netStat;
		goto  errLabel;
	}
	netStat.uiInSpeedInKbps  =  i64InOctets  *  8.  /  nIntervalInMs;
	netStat.uiOutSpeedInKbps  =  i64OutOctets  *  8.  /  nIntervalInMs;

	pProcInfo->status.netStat.ins  =  netStat;

	//
	iErr  =  0;
errLabel:
	return  iErr;
}


 //
 int  getPtsStat_isCli(  MC_VAR_isCli  * pProcInfo,  unsigned  int  nIntervalInMs  )
 {
	int				iErr		=	-1;

	if  (  !pProcInfo  )  return  -1;
	MIS_CNT		*	pMisCnt	=	getMisCntByIndex(  0,  pProcInfo,  0  );//&pProcInfo->misCnts[0];
	if  (  !pMisCnt  )  return  -1;
		 
	if  (  !nIntervalInMs  )  return  -1;

	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;
	QMC_status  *  pQmcStatus  =  pProcInfo->get_qmc_status(  );
	if  (  !pQmcStatus  )  return  -1;

	int  iDiff  =  0;
	iDiff  =  pProcInfo->status.ptsStat.transPtsInfo_sum.v.uiCnt_ptsErr  -  pProcInfo->status.ptsStat.transPtsInfo_sum_last.v.uiCnt_ptsErr;  
	if  (  iDiff  >  1  )  {
		DWORD  dwTickCnt  =  GetTickCount(  );

		//
		pQmcStatus->ptsStat.bTooManyPtsErr  =  TRUE;
		if  (  pQmcStatus->ptsStat.ucCnt_bTooManyPtsErr  <  5  )  {
			pQmcStatus->ptsStat.ucCnt_bTooManyPtsErr  ++  ;
		}
		pQmcStatus->ptsStat.dwTickCnt_lastModified_bTooManyPtsErr  =  dwTickCnt;
		}
	else  {
		  if  (  pQmcStatus->ptsStat.bTooManyPtsErr  )  {
			  if  (  pQmcStatus->ptsStat.ucCnt_bTooManyPtsErr  )  {
				  pQmcStatus->ptsStat.ucCnt_bTooManyPtsErr  --  ;
			  }
		  }
		  if  (  !pQmcStatus->ptsStat.ucCnt_bTooManyPtsErr  )  {
			  pQmcStatus->ptsStat.bTooManyPtsErr  =  FALSE;
		  }
	}
	//
	pProcInfo->status.ptsStat.transPtsInfo_sum_last  =  pProcInfo->status.ptsStat.transPtsInfo_sum;
	//
	if  (  pQmcStatus->ptsStat.bTooManyPtsErr  
		&&  pQmcStatus->ptsStat.ucCnt_bTooManyPtsErr  >  1  )
	{
		pQmcStatus->ptsStat.bWarning  =  TRUE;
		}
	else  {
		  pQmcStatus->ptsStat.bWarning  =  FALSE;
	}

	//
	if  (  pQmcCfg->debugStatusInfo.ucbShowPreDecV_pts  )  {
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "ptsStat: %s, cnt_ptsErr %d"  ),  pQmcStatus->ptsStat.bWarning  ?  _T(  "Warning"  )  :  _T(  "OK"  ),  (  int  )pQmcStatus->ptsStat.ucCnt_bTooManyPtsErr  );
		showInfo_open0(  0,  0,  tBuf  );
	}
	//
#if  0
	if  (  pQmcStatus->ptsStat.bWarning  )  {
			TCHAR  tBuf[128];
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "ptsStat: %s, cnt_ptsErr %d"  ),  pQmcStatus->ptsStat.bWarning  ?  _T(  "Warning"  )  :  _T(  "OK"  ),  (  int  )pQmcStatus->ptsStat.ucCnt_bTooManyPtsErr  );
			showNotification_open(  0,  0,  0,  tBuf  );		
	}
#endif

	 return  0;
 }


 //
 int  testSendMsg(  QY_MC  *  pQyMc,  QY_SERVICEGUI_INFO  *  pSci  )
{
	 int				loopCtrl	=	0;
	 MC_VAR_isCli		*	pProcInfo	=	(  MC_VAR_isCli  *  )pSci->pVar;
	 MIS_CNT		*	pMisCnt		=	(  MIS_CNT  *  )getMisCntByIndex(  0,  pProcInfo,  0  );//&pProcInfo->misCnts[0];
	 MIS_CHANNEL	*	pChannel	=	NULL;
	 
	 return  0;		//  2007/05/12

	 /*
	 pChannel  =  pMisCnt->pTalkingChannel;

	 for  (  ;  loopCtrl  <  3000;    )  {

		 if  (  pProcInfo->mgrQ.uiQNodes  >  90  )  {
		 	 traceLogA(  (char*)  "¶ÔÁÐÖÐÊý¾ÝÌ«¶àÁË£¬ÒªµÄµÈÒ»»áÔÙ¼Ó"  );
		 	 Sleep(  1000  );  continue;
	 	 }

		 if  (  pChannel->status.nMsgSent  >  150  +  pChannel->status.nMsgRecved  )  {
			 traceLogA(  (char*)  "Ì«¿ìÀ­£¬ÒªµÈËüÀ´µÃ¼°ÊÕ°¡"  );
			 Sleep(  2000  );  continue;
		 }
		 
		 {

			  char	buf[1024];
			  _snprintf(  buf,  sizeof(  buf  ),  "hehe %d times",  loopCtrl  );

			  loopCtrl  ++  ;

			  //  ÔÚÕâÀï,¿ÉÒÔ³é¿Õ×öÐ©ÐèÒªÖÜÆÚÐÔ×öµÄÊÂÇé, ±ÈÈçÒªÇó·þÎñÆ÷¸üÐÂÓÃ»§ÐÅÏ¢
			  traceLogA(  (char*)  "testSendMsg: ×¼±¸·¢ËÍ[%s]",  buf  );

			  //  test,  ÕâÀïÓ¦¸ÃÏÈÅÐ¶ÏÊÇ·ñ
			  QY_MESSENGER_ID	dst;
			  memset(  &dst,  0, sizeof(  dst  )  );
			  dst.ui64Id  =  1;
			  unsigned  int				uiTranNo;
			  uiTranNo  =  getNextuiTranNo(  0,  0,  0  );
			  if  (  uiTranNo  !=  -1  )  {
				  postMsg2Mgr_mc(  pQyMc,  pSci,  pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_talkTo,  0,  uiTranNo,  0,  buf,  strlen(  buf  ),  0,  0,  0  );  //  test
			  }

			  //  Sleep(  50  );
			
		
		 }
		 
	 }
	 */

//  errLabel:
		 return  0;

}


  extern "C" DWORD WINAPI mcThreadProc_mis_scheduler( LPVOID lpParameter )
{
	 QY_SERVICEGUI_INFO			*	pSci						=	(  QY_SERVICEGUI_INFO  *  )lpParameter;
	 MC_VAR_isCli					*	pProcInfo					=	(  MC_VAR_isCli  *  )pSci->pVar;
 	 QY_MC						*	pQyMc						=	pProcInfo->pQyMc;

	 int							loopCtrl					=	0;
	 DWORD							dwThreadId					=	GetCurrentThreadId(  );
	 CQyMalloc						mallocObj;
	 MIS_MSGU					*	pMsg						=	NULL;
	 unsigned  int					len;
	 DWORD							dwRet;
#ifndef  __NOTSUPPORT_DB__
		 CQnmDb						db;
#endif
	 MT_SUBTHREADINFO				subThreadInfo;
	 DWORD							dwCurTickCnt				=	0;
	 int							i;
	 CTX_MC_scheduler				ctx;
	 CQyMalloc						mallocObj_pMsgBuf_forInput;
	 CQyMalloc						mallocObj_pMsgBuf;
	 //
	 unsigned  int					uiChannelType				=	CONST_channelType_talking;


	 //
	 traceLogA(  (char*)  "mcThreadProc_mis_scheduler:  enters"  );
#ifdef  __DEBUG__
		//showInfo_open0(0, null, _T("scheduelr enters"));
#endif

	 //
	 memset(  &subThreadInfo,  0,  sizeof(  subThreadInfo  )  );
	 memset(  &ctx,  0,  sizeof(  ctx  )  );
	 ctx.common.pMsgBuf_forInput  =  (  MIS_MSGU  *  )mallocObj_pMsgBuf_forInput.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 if  (  !ctx.common.pMsgBuf_forInput  )  goto  errLabel;
	 ctx.common.pMsgBuf  =  (  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 if  (  !ctx.common.pMsgBuf  )  goto  errLabel;

	 if  (  !(  pMsg  =  (  MIS_MSGU  *  )mallocObj.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  )  )  )  goto  errLabel;
	 
#if  0
	 if  (  initGenericQ(  &pProcInfo->cfg.dynBmpQ,  mymalloc,  0,  0,  myfree,  NULL,  &ctx.dynBmpQ  )  )  goto  errLabel;
	 ctx.bDynBmpQInited  =  TRUE;
#endif

#ifndef  __NOTSUPPORT_DB__
	 if  (  !bObjDbAvail(  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )  )  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "thread_scheduler failed, bObjDbAvail failed"  )  );
		 #endif
		 goto  errLabel;
	 }
	 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
#endif

	 subThreadInfo.pParentParam  =  pQyMc;
	 subThreadInfo.iServiceId  =  pSci->cfg.iServiceId;
#ifndef  __NOTSUPPORT_DB__
	 subThreadInfo.pDb  =  db.m_pDbMem->pDb;
#endif
	 
	 //
#if 10
	 if (pProcInfo->bAppQt()) {
		 ctx.pDBManager = pProcInfo->DBManager_new();
		 if (ctx.pDBManager == mynull)goto  errLabel;
		 if (pProcInfo->initDBManager(ctx.pDBManager))goto  errLabel;
	 }
#endif


#ifdef  __DEBUG__
		testSendMsg(  pQyMc,  pSci  );	
#endif
	 

	 //
	 for  (  ;  !pQyMc->bQuit;  loopCtrl  ++  )  {
		 if (!pQyMc->bLogon) {
			 break;
		 }
		 if (pQyMc->bScheduler_dontWork) {
			 Sleep(1000);
			 continue;
		 }

		 //
		  dwRet  =  WaitForSingleObject(  pProcInfo->schedulerQ.hSemaTrigger,  1000  );
		  if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
	
		  //
#ifdef  __DEBUG__
		  //showInfo_open0(0, null, _T("scheduer after wait"));
#endif

		  //
		  for  (  ;  !pQyMc->bQuit;  )  {
			   
			   len  =  sizeof(  pMsg[0]  );
			   if  (  qGetMsg(  &pProcInfo->schedulerQ,  pMsg,  &len  )  )  break;
			   memset(  (  (  char  *  )pMsg  )  +  len,  0,  min(  256,  sizeof(  pMsg[0]  )  -  len  )  );
	
			   switch  (  pMsg->uiType  )  {
					   case  CONST_misMsgType_input:

						   if  (  !isUcFlgResp(  pMsg->input.ucFlg  )  )  {
							   procMsgInput_scheduler_req(  &subThreadInfo,  pSci,  pProcInfo,  (  MIS_CNT  *  )pMsg->input.pMisCnt,  &pMsg->input,  len,  &ctx.common  );
								 }
							 else  {
								   procMsgInput_scheduler_resp(  &subThreadInfo,  pSci,  pProcInfo,  (  MIS_CNT  *  )pMsg->input.pMisCnt,  &pMsg->input,  len,  &ctx.common  );
							 }
							 //
						     break;
#if  0
					   case  CONST_misMsgType_imMsgRcd:
							 #ifndef  __WINCE__
									  logImMsg(  subThreadInfo.pDb,  pSci->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &pMsg->imMsgRcd.rcd  );
						     #else
						   			  logImMsg_ce(  subThreadInfo.pDb,  pSci->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &pMsg->imMsgRcd.rcd  );						    
							 #endif
						     break;
#endif
					   case  CONST_misMsgType_event:
							 #ifndef  __NOTSUPPORT_DB__
								      logEvent_is(  pQyMc->p_g_dbFuncs,  subThreadInfo.pDb,  pSci->cfg.iDbType,  NULL,  &pMsg->event.event  );
							 #endif
						     break;
					   default:
								break;
			   }

#if  0
			   dwRet  =  WaitForSingleObject(  pProcInfo->schedulerQ.hSemaTrigger,  50  );
			   if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
#endif

		  }

#ifndef  __NOTSUPPORT_DB__
		  //  to log imMsg in db
		  if  (  !isQEmpty(  &pProcInfo->imMsgLogQ  )  )  {
			  procImMsgLogQ_scheduler(  &subThreadInfo,  pProcInfo,  ctx.pDBManager,  pMsg  );
		  }
#endif



		  //
		  //dwCurTickCnt  =  GetTickCount(  );
		  dwCurTickCnt = myGetTickCount(mynull);

		  //
		  //for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
		  for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
		  {
			   MIS_CNT		*	pMisCnt		=	getMisCntByIndex(  0,  pProcInfo,  i  );//&pProcInfo->misCnts[i];
			   MIS_CHANNEL	*	pChannel	=	NULL;
			   //
			   if  (  !pMisCnt  )  continue;
			   //
			   if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;
			   //
			   if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  continue;

			   Param_dbg param;
			   param.m_pHint=(TCHAR*)_T("scheduler.2744");
			   param.m_bShowInfo = false;
			   //
			   if  (  !bChannelOk(  pChannel,  &param  )  )  continue;
			   //
			   if  (  !pMisCnt->bIntervalParamsGot  &&  dwCurTickCnt  >  pMisCnt->dwLastTickCnt_getIntervalParams  +  pMisCnt->cfg.usIntervalInS_getIntervalParams  *  1000  )  {
				   MACRO_prepareForTran(  );
				   QIS_getCfgs_req						req;
				   //
				   memset(  &req,  0,  sizeof(  req  )  );
				   req.uiType  =  CONST_imCommType_getCfgsReq;
				   req.uiSizePerSnd_media  =  pProcInfo->cfg.uiSizePerSnd_media;
				   //
				   len  =  sizeof(  req  );				
				   pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_getCfgs,  tStartTran,  uiTranNo,  0,  (  char  *  )&req,  len,  NULL,  0,  0,  NULL,  FALSE  );
				   //
				   pMisCnt->dwLastTickCnt_getIntervalParams  =  dwCurTickCnt;
			   }
			     
			   #ifndef  __WINCE__
						if  (  pMisCnt->bIntervalParamsGot  &&  !pMisCnt->bToPathsRetrieved  &&  dwCurTickCnt  >  pMisCnt->dwLastTickCnt_retrieveToPaths  +  pMisCnt->cfg.usIntervalInS_getIntervalParams  *  1000  )  {
							MACRO_prepareForTran(  );
							RETRIEVE_TO_PATHS			req;
							//
							memset(  &req,  0,  sizeof(  req  )  );
							req.uiType  =  CONST_imCommType_retrieveToPaths;
							req.usMaxMemsPerSnd  =  mycountof(  req.mems  );
							//
							len  =  offsetof(  RETRIEVE_TO_PATHS,  mems  )  +  req.usCnt  *  sizeof(  req.mems[0]  );
							pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_getCfgs,  tStartTran,  uiTranNo,  0,  (  char  *  )&req,  len,  NULL,  0,  0,  NULL,  0  );
							pMisCnt->dwLastTickCnt_retrieveToPaths  =  dwCurTickCnt;				   
						}
			   #endif
			   
			   unsigned  int  usIntervalInS_refreshContactList  =  pMisCnt->cfg.usIntervalInS_refreshContactList;
			   #if  1	//  2014/05/03. def  __WINCE__
					   if  (  !pMisCnt->refreshContactList.tLastRefreshedTime_misServ  )  usIntervalInS_refreshContactList  =  20;
					   else  usIntervalInS_refreshContactList  =  pMisCnt->cfg.usIntervalInS_refreshContactList;
					   #ifdef  __DEBUG__
							   #if  0
									traceLog((TCHAR*)  _T(  "for test."  )  );
									usIntervalInS_refreshContactList  =  20;
							   #endif
					   #endif
			   #endif
			   //  2014/02/11. 需要考虑正在处理中的retrieve, 当下载的messenger非常多时，就下载过程会很长。判断下dwLastTickCnt_respRecvd可以避免重复发起请求
			   if  (  dwCurTickCnt  -  pMisCnt->refreshContactList.dwLastTickCnt_respRecvd  >  20000  
				   &&  dwCurTickCnt  >  pMisCnt->refreshContactList.dwLastTickCnt_startToRetrieve  +  usIntervalInS_refreshContactList  *  1000  )  
			   {
				   RETRIEVE_IMOBJLIST_REQ			req;
				   IM_L_STREAM		*		pStream		=	NULL;
				   
				   MACRO_prepareForTran(  );
				   //
				   #ifdef  __DEBUG__
				   if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
					   traceLogA((char*)"scheduler: start to refreshContactList");
				   }
				   #endif						   
				   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Start to retrieveImObjList, tn %d, %s"  ),  uiTranNo,  bRefreshAllContacts(  pMisCnt  )  ?  _T(  "全面"  )  :  _T(  "增量"  )  );
				   #ifdef  __WINCE__
						   showNotification(  pMisCnt,  NULL,  0,  0,  0,  0,  _T(  "Start to refresh contact list"  )  );
				   #endif
				   
				   //
				   pMisCnt->refreshContactList.tStartTime  =  tStartTran;
				   pMisCnt->refreshContactList.uiTranNo  =  uiTranNo;
				   pMisCnt->refreshContactList.idInfo_lastRefreshed.ui64Id  =  0;	//  ±íÃ÷ÊÇ´ÓÍ·¿ªÊ¼Ë¢ÐÂ
				   //
				   memset(  &req,  0,  sizeof(  req  )  );
				   req.uiType  =  CONST_imCommType_retrieveImGrpListReq;
				   req.tLastRefreshedTime_contactList_misServ  =  pMisCnt->refreshContactList.tLastRefreshedTime_misServ;
				   req.usMaxContactUpdateInfosPerSnd  =  pMisCnt->cfg.usMaxContactUpdateInfosPerSnd_grp;
				   //				   
				   if  (  sizeof(  IM_L_STREAM  )  >  sizeof(  ctx.common.pMsgBuf_forInput[0]  )  )  goto  errLabel;
				   pStream  =  (  IM_L_STREAM  *  )ctx.common.pMsgBuf_forInput;	//  tmpMallocObj.malloc(  sizeof(  IM_STREAM_CONTENT  )  );
				   if  (  pStream  )  {
					   MACRO_memset_imLStream(  pStream  );
					   pStream->uiType  =  CONST_imCommType_lStream;
					   pStream->uiContentType  =  req.uiType;
					   len  =  sizeof(  pStream->buf  );
					   if  (  retrieveImObjListReq2Stream(  pStream->uiContentType,  &req,  pStream->buf,  &len  )  )  goto  errLabel;
					   pStream->ulStreamLen  =  len;
					   len  +=  offsetof(  IM_L_STREAM,  buf  ); 
					   //
					   pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_refreshImObjListReq,  tStartTran,  uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  0,  0,  ctx.common.pMsgBuf,  FALSE  ); 
				   }
				   //
				   pMisCnt->refreshContactList.dwLastTickCnt_startToRetrieve  =  dwCurTickCnt;
		  	   }

			   if  (  pMisCnt->refreshContactList.tLastRefreshedTime_misServ  )  {
				   if  (  !pMisCnt->refreshImObjRules.tLastRefreshedTime  )  {
					   if  (  dwCurTickCnt  >  pMisCnt->refreshImObjRules.dwLastTickCnt  +  20000  )  {
						   pMisCnt->refreshImObjRules.dwLastTickCnt  =  dwCurTickCnt;
						   //
						   mytime(  &pMisCnt->refreshImObjRules.tStart_toRetrieveAll  );		//  2011/11/12
						   //
						   MACRO_prepareForTran(  );

						   //
		   				   #ifdef  __DEBUG__
								   traceLog((TCHAR*)  _T(  "scheduler: start to refreshImObjRules"  )  );						   
						   #endif
						   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Start to refreshImObjRules, tn %d"  ),  uiTranNo  );
						   #ifdef  __WINCE__
									showNotification(  pMisCnt,  NULL,  0,  0,  0,  0,  _T(  "Start to refresh rules"  )  );
						   #endif
						   
						   //
						   REFRESH_imObjRules_req	req;
						   IM_L_STREAM		*		pStream		=	NULL;
			   

						   memset(  &req,  0,  sizeof(  req  )  );
						   req.uiType  =  CONST_imCommType_refreshImObjRulesReq;
						   req.ucbRetrieveAll  =  TRUE;
						   req.usMaxMemsPerSnd  =  mycountof(  req.mems  );

						   if  (  sizeof(  IM_L_STREAM  )  >  sizeof(  ctx.common.pMsgBuf_forInput[0]  )  )  goto  errLabel;
						   pStream  =  (  IM_L_STREAM  *  )ctx.common.pMsgBuf_forInput;	//  tmpMallocObj.malloc(  sizeof(  IM_STREAM_CONTENT  )  );
						   MACRO_memset_imLStream(  pStream  );
						   pStream->uiType  =  CONST_imCommType_lStream;
						   pStream->uiContentType  =  req.uiType;
						   len  =  sizeof(  pStream->buf  );
						   if  (  refreshImObjRulesReq2Stream(  pStream->uiContentType,  &req,  pStream->buf,  (  unsigned  int  *  )&len  )  )  goto  errLabel;
						   pStream->ulStreamLen  =  len;
						   len  +=  offsetof(  IM_L_STREAM,  buf  ); 

						   //
						   pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_refreshImObjListReq,  tStartTran,  uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  0,  0,  NULL,  0  ); 

					   }
				   }
			   }

			   #ifndef  __WINCE__
						if  (  pMisCnt->ucTriesToReg  )  {
							if  (  dwCurTickCnt  >  pMisCnt->dwLastTickCnt_tryToReg  +  pMisCnt->cfg.usIntervalInS_tryToReg  *  1000  )  {
								sndMsgNeedReg_qmc(  &subThreadInfo,  pSci,  pProcInfo,  pMisCnt  );
								pMisCnt->dwLastTickCnt_tryToReg  =  dwCurTickCnt;				   
							}
						}
			   #endif

			   if  (  pMisCnt->ucbNeedSndDevInfo  )  {
				   if  (  dwCurTickCnt  >  pMisCnt->dwLastTickCnt_tryToSndDevInfo  +  pMisCnt->cfg.usIntervalInS_tryToSndDevInfo  *  1000  )  {
					   sndDevInfo_qmc(  &subThreadInfo,  pSci,  pProcInfo,  pMisCnt  );
					   pMisCnt->dwLastTickCnt_tryToSndDevInfo  =  dwCurTickCnt;
				   }
			   }

#if  0		   //  2010/12/04
			   if  (  dwCurTickCnt  >  pMisCnt->dwLastTickCnt_chkChannels  +  16000  )  {		//  2008/06/01
				   MIS_MSG_applyForChkChannels_qmc	msg_applyForChkChannels_qmc;

				   //  ¼ì²érobotÍ¨µÀ
				   memset(  &msg_applyForChkChannels_qmc,  0,  sizeof(  msg_applyForChkChannels_qmc  )  );
				   msg_applyForChkChannels_qmc.uiType  =  CONST_misMsgType_applyForChkChannels_qmc;
				   msg_applyForChkChannels_qmc.pMisCnt  =  pMisCnt;
				   if  (  bRobotTaskExists(  pProcInfo,  pMisCnt,  &msg_applyForChkChannels_qmc  )  )  {
					   MIS_CHANNEL  *  pChannel_robot;

					   pChannel_robot  =  getChannelByType(  pMisCnt,  CONST_channelType_robot  );
					   if  (  !pChannel_robot->hThread_io  ||  msg_applyForChkChannels_qmc.bTaskNeedRestart  )  {
						   //
						   qPostMsgAndTrigger(  &msg_applyForChkChannels_qmc,  sizeof(  msg_applyForChkChannels_qmc  ),  &pProcInfo->robotQ  );
					   }
				   }

                   //
				   pMisCnt->dwLastTickCnt_chkChannels  =  dwCurTickCnt;
			   }
#endif

			#ifndef  __WINCE__
#if  0  //  2016/06/15
			   if  (  pProcInfo->bPhoneModuleLoaded  )  {				//  2008/02/01
				   if  (  !pProcInfo->bSmServiceProhibited  )  {			  
					   if  (  (  !pProcInfo->bPhoneMsgrListDownloaded  &&  dwCurTickCnt  >  pMisCnt->retrievePhoneMsgrs.dwLastTickCnt  +  60  *  1000  )
						   ||  pProcInfo->bPhoneMsgrListNeedRefreshed  )
					   {
						   //  Çå¿ÕÖØÐÂÏÂÔØ±êÖ¾
						   pProcInfo->bPhoneMsgrListNeedRefreshed  =  FALSE;

						   //  ÏÈÇå¿Õ¶ÓÁÐ¡£Õâ·½±ãÖØÐÂÏÂÔØ
						   emptyGenericQ(  &pProcInfo->phoneMsgrQ  );

						   //  Ïò·þÎñÆ÷·¢ÆðÒªÇó¿ªÊ¼ÏÂÔØÊÖ»úÁÐ±íµÄÇëÇó
						   RETRIEVE_PHONE_MSGRS		req;
						   MACRO_prepareForTran(  );
						   //
						   memset(  &req,  0,  sizeof(  req  )  );
						   req.uiType  =  CONST_imCommType_retrievePhoneMsgrs;
						   req.usMaxPhoneMsgrsPerSnd  =  mycountof(  req.mems  );
						   //
						   len  =  offsetof(  RETRIEVE_PHONE_MSGRS,  mems  )  +  req.usCnt  *  sizeof(  req.mems[0]  );
						   //
						   postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_sendVDevReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&req,  len,  NULL,  0,  0,  NULL,  0  ); 
						   //
						   pMisCnt->retrievePhoneMsgrs.dwLastTickCnt  =  dwCurTickCnt;				   
					   }
				   }
				   //
				   if  (  pProcInfo->bPhoneMsgrListDownloaded  &&  !pProcInfo->bPhoneMsgrListVerified  &&  dwCurTickCnt  >  pProcInfo->dwTickCnt_toVerifyPhoneMsgrList  +  30  *  1000  )  {
					   //
					   //  CWnd					*		pMainWnd						=	AfxGetApp(  )->m_pMainWnd;
					   HWND								hMainWnd						=	pQyMc->gui.hMainWnd;
					   //
					   if  (  IsWindow(  hMainWnd  )  )  {
#if  0  //  2015/07/03
                           PostMessage(  hMainWnd,  WM_COMMAND,  MAKELONG(  ID_qyVerifiedPhoneList,  0  ),  0  );
#endif
					   }
					   //
					   pProcInfo->dwTickCnt_toVerifyPhoneMsgrList  =  dwCurTickCnt;
				   }
				   //
			   }
#endif
			#endif

		  }
	
		  //
		  //traceLog((TCHAR*)_T("scheduler: before getNetStat_isCli"));

		  //  
		  if  (  dwCurTickCnt  >  pProcInfo->status.dwTickCnt_toStat  +  1000  )  {
			  //
			  getCpuUsage(  &pQyMc->env,  pProcInfo  );
			  //
			  getNetStat_isCli(  pProcInfo,  dwCurTickCnt  -  pProcInfo->status.dwTickCnt_toStat  );
			  //  2015/06/18
			  getPtsStat_isCli(  pProcInfo,  dwCurTickCnt  -  pProcInfo->status.dwTickCnt_toStat  );
			  //
			  GlobalMemoryStatus(  &pProcInfo->status.memory  );

			  #ifdef  __DEBUG__
					  //  printShmMemory(  );
			  #endif

			  //
			  pProcInfo->status.dwTickCnt_toStat  =  dwCurTickCnt;
		  }

		  //
		  if ( dwCurTickCnt > pProcInfo->status.dwTickCnt_diskToStat + 15000) {

			  DWORD		dwTotalClusters; //总的簇
			  DWORD		dwFreeClusters; //可用的簇
			  DWORD		dwSectPerClust;	//每个簇有多少个扇区
			  DWORD		dwBytesPerSect;  //每个扇区有多少个字节
			  GetDiskFreeSpaceW(TEXT("C:") , &dwSectPerClust,&dwBytesPerSect,&dwFreeClusters,&dwTotalClusters);

			  __int64 nTotal = dwTotalClusters;
			  nTotal *= dwSectPerClust;
			  nTotal *= dwBytesPerSect;

			  __int64 nFree = dwFreeClusters;
			  nFree *= dwSectPerClust;
			  nFree *= dwBytesPerSect;


			  pProcInfo->status.iDiskUsage.availableDiskSize = nFree / 1024 / 1024;
			  pProcInfo->status.iDiskUsage.sumDiskSize = nTotal / 1024 / 1024;
			  
			  pProcInfo->status.dwTickCnt_diskToStat = dwCurTickCnt;
		  }

	
		  //  if  (  !(  loopCtrl  %  20  )  )  traceLogA(  (char*)  "ÕâÀï»¹Ó¦¸ÃÓÐÒ»¸ö¶¨ÆÚ£¨±ÈÈç30·ÖÖÓÒ»´ÎµÄ£¬ÇåÀíprocessQµÄ¹¤×÷£¬ÒÔ·ÀÖ¹processQÀïÓÐµÄ½ÚµãÊ§È¥±»´¦ÀíµÄ¿ÉÄÜµÄ¡£¾ÍÒª°ÑÕâÐ©À¬»ø½ÚµãÇåµô"  );

		  //
		  continue;
	 }

	 //  traceLogA(  (char*)  "mcThreadProc_mis_scheduler:  Î´Íê³É"  );

 errLabel:

	 if (ctx.pDBManager) pProcInfo->DBManager_free(&ctx.pDBManager);

#if  0
	 if  (  ctx.bDynBmpQInited  )  exitGenericQ(  &ctx.dynBmpQ  );
#endif

	 pProcInfo->status.threadsStatus.ulbSchedulerQuit  =  TRUE;

	 traceLogA(  (char*)  "mcThreadProc_mis_scheduler:  leaves"  );

	 return  0;
}






