

#include	"stdafx.h"

#include	<stddef.h>
#include	<stdio.h>

//#include	<afxcmn.h>
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
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	"qyCusResTemp.h"		//  2013/02/17

//  #include	"qwmDynFunc.h"

#include	"qmcCmdProc.h"

#include	"tmpCeLib.h"
#include	"qySqlFunc.h"

#include	"myresource.h"
#include	"myDb.h"
#include	"qyOpenShellCommon.h"
//#include	"DlgObjs_ts.h"
#include	"dlgobjsproc.h"
#include	"dlgtalkproc.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"qmcCommFunc_isCli.h"
//
#include	"ctxMcThread.h"

//
BOOL  bMessengerRegInfoSame(  QY_MESSENGER_REGINFO  *  pRegInfo0,  QY_MESSENGER_REGINFO  *  pRegInfo1  );
int  tmpHandler_bGetMessengerRegInfoBySth_myDb(  void  *  p0,  void  *  p1,  void  *  p2  );



 int  mcProcResp_refreshImGrps_end_myDb(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_IMGRPLIST_RESP  *  pResp,  void  *  pCtxParam  )
{
	int									iErr													=	-1;
	MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	QY_SERVICEGUI_INFO  *  pSci		=	(  QY_SERVICEGUI_INFO  *  )pSciParam;
	MIS_CNT  *  pMisCnt				=	(  MIS_CNT  *  )pMisCntParam;
	CTX_MC_THREAD  *  pCtx			=	(  CTX_MC_THREAD  *  )pCtxParam;
	QY_MC							*	pQyMc													=	QY_GET_GBUF(  );
	MC_VAR_isCli						*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;

		//  do nothing

	iErr  =  0;
errLabel:
	return  iErr;
}

 






 int  tmpHandler_fillImObjs_msgr_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	QY_MC	*	pQyMc  =  QY_GET_GBUF(  );

	//  p0;
	COMMON_PARAM		*	pCommonParam1	=		(  COMMON_PARAM  *  )p1;
	//
	HWND					hDlg			=		(  HWND  )pCommonParam1->p0;
	DLG_objs_var		&	m_var			=		*(  DLG_objs_var  *  )pCommonParam1->p1;
	CMyDb				*   pMyDb			=		(  CMyDb  *  )pCommonParam1->p2;
	//
	QMEM_qyImObj		*   pQMem			=		(  QMEM_qyImObj  *  )p2;

	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_DMITEM				*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

	memset(  &regInfo,  0,  sizeof(  regInfo  )  );

	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	if  (  pQMem->messengerInfo.iStatus  ==  CONST_qyStatus_ok
		&&  pQMem->messengerInfo.uiType  !=  CONST_objType_imGrp  )
	{
		//  2015/06/05
		if  (  pQMem->messengerInfo.uiType  ==  CONST_objType_me  )  {
			iRet  =  0;  goto  errLabel;
		}
	
		//
		if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pMyDb,  CONST_dbType_myDb,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  pQMem->messengerInfo.misServName, &pQMem->messengerInfo.idInfo,  0,  &regInfo  )  )  {
			memset(  &regInfo,  0,  sizeof(  regInfo  ) );
		}
		HWND	hCtl	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  );
		int		tmpiRet;
		TCHAR	talkerDesc[128]  =  _T(  ""  );
		regInfo2Desc(  0,  &regInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  ); 

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s"  ),  pQMem->messengerInfo.idInfo.ui64Id,  talkerDesc  );
		tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d,  %s, idInfo is %I64u, talkerDesc %s"  ),  m_var.usItemCount,  qyGetDesByType1(  pTable,  pQMem->messengerInfo.uiType  ),  regInfo.addr.idInfo.ui64Id,  talkerDesc  );
		OutputDebugString(  tBuf  );
		OutputDebugString(  _T(  "\n"  )  );

	}


	iRet  =  0;
errLabel:
	return  iRet;

}

 void  fillImObjs_msgr_myDb(  HWND  hDlg,  void  *  pVar,  void  *  pDb  )
{

	CMyDb  *  pMyDb  =  (  CMyDb  *  )pDb;

	COMMON_PARAM				commonParam1;

	MACRO_makeCommonParam3(  hDlg,  pVar,  pDb,  commonParam1  );	

	qTraverse(  pMyDb->m_var.pQ_qyImObjTab,  tmpHandler_fillImObjs_msgr_myDb,  NULL,  &commonParam1  );

#if 0
	TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	CDBVariant		varVals[10];

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select A.idStr,A.uiType,B.col11,B.col12,B.col2,B.col3,B.col4 from (qyImObjTab as A  left join qyImObjRegInfoTab as B on (A.misServName=B.misServName and A.idStr=B.idStr)) "   )  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where A.uiType not in(%d)"  ),  sqlBuf,  CONST_objType_imGrp  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by A.idStr"  ),  sqlBuf  );

	enumSqlQuery(  pDb,  sqlBuf,  (  PF_commonHandler  )tmpHandler_fillImObjs_messenger,  hDlg,  pVar,  varVals,  mycountof(  varVals  ),  NULL  );	
#endif

errLabel:

	return;

}

 int  tmpHandler_fillImObjs_grp_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;

	QY_MC	*	pQyMc  =  QY_GET_GBUF(  );

	COMMON_PARAM		*	pCommonParam1	=		(  COMMON_PARAM  *  )p1;
	//
	HWND					hDlg			=		(  HWND  )pCommonParam1->p0;
	DLG_objs_var		&	m_var			=		*(  DLG_objs_var  *  )pCommonParam1->p1;
	CMyDb				*   pMyDb			=		(  CMyDb  *  )pCommonParam1->p2;
	//
	QMEM_qyImObj		*   pQMem			=		(  QMEM_qyImObj  *  )p2;

	//  MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	IM_GRP_INFO					grpInfo;

	
	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;



	if  (  pQMem->messengerInfo.uiType  ==  CONST_objType_imGrp  )
	{
		if  (  !g_dbFuncs.pf_bGetImGrpInfoBySth(  pMyDb,  CONST_dbType_myDb,  pQMem->messengerInfo.misServName,  &pQMem->messengerInfo.idInfo,  &grpInfo  )  )  {
			memset(  &grpInfo,  0,  sizeof(  grpInfo  )  );
		}
		
		HWND	hCtl	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  );
		//  TCHAR	tBuf[256];
		int		tmpiRet;

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s"  ),  pQMem->messengerInfo.idInfo.ui64Id,  grpInfo.name  );
#if  0
		if  (  grpInfo.usSubtype  ==  CONST_imGrpSubtype_msg  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%s)"  ),  tBuf, getResStr(  0,  &pQyMc->cusRes,  CONST_resId_imGrps_msg  )  );
		}
		else  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%s)"  ),  tBuf, getResStr(  0,  &pQyMc->cusRes,  CONST_resId_imGrps_av  )  );
		}
#endif
		if  (  grpInfo.usSubtype  )
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%s)"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imGrpSubtypeTable  ),  grpInfo.usSubtype  )  );
		else
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%s)"  ),  tBuf, getResStr(  0,  &pQyMc->cusRes,  CONST_resId_imGrps_av  )  );
		//
		tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    

		//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d,  %s, idInfo is %I64u, talkerDesc %s"  ),  m_var.usItemCount,  qyGetDesByType1(  pTable,  uiType  ),  grpInfo.idInfo.ui64Id,  grpInfo.name  );
		OutputDebugString(  tBuf  );
		OutputDebugString(  _T(  "\n"  )  );
	}

	iRet  =  0;

errLabel:
	return  iRet;
}

  void  fillImObjs_grp_myDb(  HWND  hDlg,  void  *  pVar,  void  *  pDb  )
{
	CMyDb  *  pMyDb  =  (  CMyDb  *  )pDb;

	COMMON_PARAM				commonParam1;

	MACRO_makeCommonParam3(  hDlg,  pVar,  pDb,  commonParam1  );	

	qTraverse(  pMyDb->m_var.pQ_qyImObjTab,  tmpHandler_fillImObjs_grp_myDb,  NULL,  &commonParam1  );

#if  0
	TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	CDBVariant		varVals[10];

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImObjTab.idStr,qyImObjTab.uiType,qyImGrpInfoTab.name from (qyImObjTab left join qyImGrpInfoTab on(qyImObjTab.misServName=qyImGrpInfoTab.misServName and qyImObjTab.idStr=qyImGrpInfoTab.idStr ) )"  )  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where qyImObjTab.uiType in(%d)"  ),  sqlBuf,  CONST_objType_imGrp  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by qyImObjTab.idStr"  ),  sqlBuf  );

	enumSqlQuery(  pDb,  sqlBuf,  (  PF_commonHandler  )tmpHandler_fillImObjs_imGrp,  hDlg,  pVar,  varVals,  mycountof(  varVals  ),  NULL  );	
#endif

errLabel:
	return;
}

int  tmpHandle_selectImTask_dlgTalk_loadTasks_myDb(  void  *  p0,  void  *  P1,  void  *  p2  )
{
	 int				iRet  =  -1;
	 QY_MC			 *	pQyMc									=   QY_GET_GBUF(  );
 	 CQyMalloc			mallocObj;

	 COMMON_PARAM	 *	pCommonParam							=	(  COMMON_PARAM	 *  )p0;
	 //
	 HWND				hDlgTalk								=   (  HWND  )pCommonParam->p0;
	 PARAM_PROC_ROW  *  pParam									=   (  PARAM_PROC_ROW  *  )pCommonParam->p1;
	 //  p1
	 IM_TASK_RCD	 *  pQMem									=   (  IM_TASK_RCD  *  )p2;

	 CHelp_getDlgTalkVar	help_getDlgTalkVar;
	 DLG_TALK_var  *	pm_var  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );  
	 if  (  !pm_var  )  return  -1;
	 DLG_TALK_var  &  m_var  =  *pm_var;

	 if  (  (  m_var.addr.uiObjType  ==  CONST_objType_imGrp  &&  (  pQMem->idInfo_send.ui64Id  ==  m_var.addr.idInfo.ui64Id  ||  pQMem->idInfo_recv.ui64Id  ==  m_var.addr.idInfo.ui64Id  )  )
	     || (  m_var.addr.uiObjType  !=  CONST_objType_imGrp  &&  (  
		      (  pQMem->idInfo_send.ui64Id  ==  m_var.addr.idInfo.ui64Id  &&  pQMem->idInfo_recv.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  )  ||  
			  (  pQMem->idInfo_send.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  &&  pQMem->idInfo_send.ui64Id  ==  m_var.addr.idInfo.ui64Id  )  )  )  )
	 {
		 MIS_MSG_TASK	*	pMsg;
		 if  (  !(  pMsg  =  (  MIS_MSG_TASK  *  )mallocObj.mallocf(  sizeof(  MIS_MSG_TASK  )  )  )  )  goto  errLabel;

		 if  (  !taskRcd2Msg(  m_var.pMisCnt,  pQMem,  pMsg  )  )  {
			 traceLogA(  "taskRcd2Msg failed, skipped"  );
			 iRet  =  0;  goto  errLabel;
		 }

	 	if  (  !bTaskAlive(  pQMem->iStatus  )  )  {
			iRet  =  0;  goto  errLabel;
		}

		switch  (  pQMem->uiContentType  )  {
				case  CONST_imCommType_transferAvInfo:  
				case  CONST_imCommType_transferGpsInfo:
					{

					  #ifdef  __DEBUG__
							  traceLogA(  "tmpHandler_displayTasks: skiped, rcd.uiContentType is %d,rcd.uiType %d",  pQMem->uiContentType,  pQMem->uiType  );
					  #endif

					  iRet  =  0;  goto  errLabel;
					  }
					  break;
				default:
						break;
		}
		
		if  (  dlgTalk_qPostMsg(  hDlgTalk,  pMsg,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsg->lenInBytes  )  )  {
			traceLogA(  "tmpHandler_displayTasks failed: qPostMsg failed."  );
			goto  errLabel;
		}

		//
		if  (  pParam->nItem  >=  m_var.usMaxDisplayedTasks  )  {
			iRet  =  1;  goto  errLabel;
		}
	 }
	 
	 iRet =  0;
errLabel:
	 return  iRet;
}

 int  selectImTask_dlgTalk_loadTasks_myDb(  HWND  hDlgTalk,  void  *  pTmpParam,  void  *  pDbParam  )
{
	 int				iRet  =  -1;
	 QY_MC			 *	pQyMc									=   QY_GET_GBUF(  );
	 PARAM_PROC_ROW  *  pParam									=   (  PARAM_PROC_ROW  *  )pTmpParam;
	 char				idStr[CONST_qyMessengerIdStrLen + 1]	=  "";
	 char				idStr_me[CONST_qyMessengerIdStrLen + 1]	=  "";
	 CMyDb			 *	pDb										=	(  CMyDb  *  )pDbParam;
	 COMMON_PARAM		commonParam0;

	 MACRO_makeCommonParam3(  hDlgTalk,  pTmpParam,  NULL,  commonParam0  );

	 qTraverse(  pDb->m_var.pQ_qyImTaskTab,  tmpHandle_selectImTask_dlgTalk_loadTasks_myDb,  &commonParam0,  NULL  );


#if  0
	 TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]		=  _T(  ""  );
	 int				tmpiRet									=  -1;
	 CDBVariant			varVals[15];


	 idInfo2Str(  &m_var.addr.idInfo,  idStr,  mycountof(  idStr  )  );
	 idInfo2Str(  &m_var.pMisCnt->idInfo,  idStr_me, mycountof(  idStr_me  )  );

	//
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,uiType,uiMode,subTypeStr,subject,content0,tEndTime,idStr_send,tSendTime,uiTranNo,uiSerialNo,uiContentType,idStr_recv,tRecvTime,iStatus from %s where iStatus<>%d "  ),  CONST_tabName_qyImTaskTab,  CONST_imTaskStatus_null  );	
	if  (  m_var.addr.uiObjType  ==  CONST_objType_imGrp  )  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and (idStr_send='%s' or idStr_recv='%s')"  ), sqlBuf,  CString(  idStr  ),  CString(  idStr  )  );	    
	else  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and ((idStr_send='%s' and idStr_recv='%s') or (idStr_send='%s' and idStr_recv='%s'))"  ), sqlBuf,  CString(  idStr  ),  CString(  idStr_me  ),  CString(  idStr_me  ),  CString(  idStr  )  );	    	
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and uiType not in(%d,%d,%d)"  ),  sqlBuf,  CONST_imTaskType_shareDynBmp,  CONST_imTaskType_viewDynBmp,  CONST_imTaskType_viewGps  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by tRecvTime "  ),  sqlBuf  );
	tmpiRet  =  enumSqlQuery(  db.m_pDbMem->pDb,  sqlBuf,  tmpHandler_loadTasks,  hDlgTalk,  &pParam,  varVals,  mycountof(  varVals  ),  NULL  );
#endif
	 iRet =  0;
errLabel:
	 return  iRet;
}

 


 

 //
int  tmpHandler_bFillImGrpMem_confCtrl_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int					iRet										=  -1;

	COMMON_PARAM	*	pCommonParam								=	(  COMMON_PARAM  *  )p0;
	GRP_confCtrl  *  pConfCtrl  =  (  GRP_confCtrl  *  )p1;
	//
	HWND				hDlgTalk									=	(  HWND  )pCommonParam->p0;
	PARAM_PROC_ROW	*	pParam										=	(  PARAM_PROC_ROW  *  )pCommonParam->p1;
	CMyDb			*	pDb											=	(  CMyDb  *  )pCommonParam->p2;
	//
	IM_GRP_MEM		*	pQMem1										=	(  IM_GRP_MEM  *  )p2;

	//
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	//
	QY_MESSENGER_REGINFO		regInfo;
	QY_MESSENGER_REGINFO	*	pRegInfo			=	&regInfo;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pDlgTalkVar									=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pDlgTalkVar  )  return  -1;
	DLG_TALK_var	&	m_var										=	*pDlgTalkVar;

	if  (  pQMem1->idInfo_grp.ui64Id  ==  m_var.addr.idInfo.ui64Id  )
	{
		//  2014/04/20
		int  id_imGrpMem  =  pQMem1->id;

		//
		
			int  iDbType  =  CONST_dbType_myDb;
			if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  _T(  ""  ),  &pQMem1->idInfo_mem,  0,  &regInfo  )  )  {
				memset(  &regInfo,  0,  sizeof(  regInfo  )  );
			}

		 
			 QY_MC					*	pQyMc				=  QY_GET_GBUF(  );
			 MC_VAR_isCli			*	pProcInfo			=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

			 //
			 MY_REG_DESC				desc;
			 TCHAR						talkerDesc[128  +  1];
			 TCHAR						displayName[64  +  1];
			 int						nImage,  nSelectedImage;
		 
			 if  (  regInfo2Desc(  0,  pRegInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  displayName,  mycountof(  displayName  )  )  )  goto  errLabel;

			 nImage  =  pQyMc->cfg.image.nImage_messenger;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedMessenger;

		   {	 //  
			 QM_OBJQ_MEM				mem;
			 QMEM_MESSENGER_CLI		*	pQMem	=	NULL;
			 QY_MESSENGER_INFO			messengerInfo;
			 void					*	pDb		=	NULL;
			 int						i;

			 CQnmDb						tmpObjDb;						
			 pDb				=		tmpObjDb.getAvailableDb(  pQyMc->iDsnIndex_mainSys  );

			 //  ÏÈÓÃregInfoÌî³äÒ»ÏÂmessengerInfo, ÒòÎªÏÂÃæµÄpClientÖ»ÄÜÖ¸ÏòmessengerInfo
			 memset(  &messengerInfo,  0,  sizeof(  messengerInfo  )  );
			 //
			 lstrcpyn(  messengerInfo.misServName,  regInfo.addr.misServName,  mycountof(  messengerInfo.misServName  )  );
			 messengerInfo.idInfo.ui64Id  =  regInfo.addr.idInfo.ui64Id;

			 //               
			 if  (  procQmObjQ(  pProcInfo->pSgiParam,  (  QM_OBJQ  *  )m_var.pMisCnt->pObjQ,  pDb,  pQyMc->cfg.db.iDbType,  CONST_objType_messenger,  &messengerInfo,  &mem  )  )  goto  errLabel;
			 if  (  !mem.pQMemObj  )  goto  errLabel;

			 pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;

			 //  ÕâÀïÔÝÊ±ÔÚÕâÀï¸üÐÂÏÔÊ¾Ãû³Æ  
			 lstrcpyn(  pQMem->talkerDesc,  talkerDesc,  mycountof(  pQMem->talkerDesc  )  );
			 lstrcpyn(  pQMem->displayName,  displayName,  mycountof(  pQMem->displayName  )  );		//  2007/09/02

			 //
			 getMessengerImages(  pQyMc,  pQMem->usRunningStatus,  &nImage,  &nSelectedImage  );

			 //
			 if  (  pConfCtrl  )  {
				 if  (  pConfCtrl->usCnt  <  pConfCtrl->usMaxCnt  )  {
					 GrpMem_confCtrl  *  pMem  =  &pConfCtrl->pMems[pConfCtrl->usCnt];
					 pMem->idInfo.ui64Id  =  pQMem->idInfo.ui64Id;
					 //
					 pMem->id_imGrpMem  =  id_imGrpMem;
					 //
					 safeTcsnCpy(  displayName,  pMem->displayName,  mycountof(  pMem->displayName  )  );
					 safeTcsnCpy(  talkerDesc,  pMem->talkerDesc,  mycountof(  pMem->talkerDesc  )  );
					 
					 //  2017/08/30
#if  0
					 CONSULT_mem  cm  =  {0};
					 getConsultMem(  &pQMem1->idInfo_grp,  &pMem->idInfo,  &cm  );
					 safeTcsnCpy(  cm.ksName,  pMem->ksName,  mycountof(  pMem->ksName  )  );
					 safeTcsnCpy(  cm.ysName,  pMem->ysName,  mycountof(  pMem->ysName  )  );
#endif


					 //
					 pConfCtrl->usCnt  ++  ;
					 
				 }

			 }

			 //
			 pParam->nItem  ++  ;

		   }
		 

	}

	iRet  =  0;
errLabel:
	return  iRet;
}



//
__declspec(  dllexport  )  BOOL  bFillImGrpMem_confCtrl_myDb(  HWND  hDlgTalkParam,  void  *  pDbParam,  void  *  pParam,  GRP_confCtrl  *  pConfCtrl  )
{
	BOOL				bRet										=   FALSE;
	CMyDb			*	pDb											=	(  CMyDb  *  )pDbParam;
	COMMON_PARAM		commonParam;
	MACRO_makeCommonParam3(  hDlgTalkParam,  pParam,  pDb,  commonParam  );

	//
	qTraverse(  pDb->m_var.pQ_qyImGrpMemTab,  tmpHandler_bFillImGrpMem_confCtrl_myDb,  &commonParam,  pConfCtrl  );
	
	bRet  =  TRUE;
errLabel:
	return  bRet;
}




//
int  tmpHandler_listObjs_dlgMsgList_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	QY_MC		  *  pQyMc				=  QY_GET_GBUF(  );
	COMMON_PARAM  *  pCommonParam		=  (  COMMON_PARAM  *  )p0;
	//
	//  QY_MC_QUERY	  *  pQuery				=  (  QY_MC_QUERY  *  )pCommonParam->p0;
	CMyDb		  *  pDb				=  (  CMyDb  *  )pCommonParam->p0;
	//  CListCtrl	  *  pListCtrl			=  (  CListCtrl  *  )pCommonParam->p1;
	HWND			 hListCtrl			=	(  HWND  )pCommonParam->p1;
	if  (  !hListCtrl  )  goto  errLabel;
	int			  *  nItem				=  (  int  *  )pCommonParam->p2;
	//
	QY_MESSENGER_ID  *  pIdInfo			=  (  QY_MESSENGER_ID  *  )p1;
	IM_MSG_RCD	  *  pQMem				=  (  IM_MSG_RCD  *  )p2;

	if  (  pQMem->idInfo_send.ui64Id  ==  pIdInfo->ui64Id  ||  pQMem->idInfo_recv.ui64Id  ==  pIdInfo->ui64Id  ||  (  pIdInfo  &&  !pIdInfo->ui64Id  ?  1  :  0  )  )
	{
		int		iItem  =  nItem[0];
		int		index			 =  0;
		TCHAR	tBuf[255  +  1]  =  _T(  ""  );
		QY_MESSENGER_REGINFO    regInfo;
		MY_REG_DESC				desc;
		char		  timeBuf[CONST_qyTimeLen  +  1]  =  "";


			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQMem->id  );
			//  index  =  0;  pListCtrl->InsertItem(  iItem,  tBuf  );
			index  =  0;  myListCtrl_InsertItem(  hListCtrl,  iItem,  tBuf  );


			//  QY_DMITEM		*	pTable;
		    // pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  );
			//   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  pQMem->uiType  )  )  );
			//  index  =  1;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQMem->uiType  );
			//  index  =  1;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
			index  =  1;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

			if  (  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_bGetMessengerRegInfoBySth_myDb,  &pQMem->idInfo_send,  &regInfo  )  >  0  ){
				regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  );
				if  (  desc.pSyr[0]  )  _sntprintf(  pQMem->senderDesc,  mycountof(  pQMem->senderDesc  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );  
			}
			//  index  =  2;  pListCtrl->SetItemText(  iItem,  index,  pQMem->senderDesc  );
			index  =  2;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  pQMem->senderDesc  );

			if  (  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_bGetMessengerRegInfoBySth_myDb,  &pQMem->idInfo_recv,  &regInfo  )  >  0  ){
				regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  );
				if  (  desc.pSyr[0]  )  _sntprintf(  pQMem->receiverDesc,  mycountof(  pQMem->receiverDesc  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );  
			}
			//  index  =  3;  pListCtrl->SetItemText(  iItem,  index,  pQMem->receiverDesc  );
			index  =  3;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  pQMem->receiverDesc  );

			getTimeStr(  pQMem->tSendTime,  timeBuf,  mycountof(  timeBuf  )  );
			//  index  =  4;  pListCtrl->SetItemText(  iItem,  index,  CString(  timeBuf  )  );
			index  =  4;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  CQyString(  timeBuf  )  );

			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQMem->content  );
			//  index  =  5;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
			index  =  5;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
			index  =  6;  //  pListCtrl->SetItemText(  iItem,  index,  pQMem->content1  );
			index  =  7;  //  pListCtrl->SetItemText(  iItem,  index,  pQMem->content2  );
			index  =  8;  //  pListCtrl->SetItemText(  iItem,  index,  pQMem->content3  );
			index  =  9;  //  pListCtrl->SetItemText(  iItem,  index,  pQMem->content4  );

			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->idInfo_send.ui64Id  );
			//  index  =  10;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
			index  =  10;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->idInfo_recv.ui64Id  );
			//  index  =  11;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
			index  =  11;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

			getTimeStr(  pQMem->firstTime,  timeBuf,  mycountof(  timeBuf  )  );
			//  index  =  12;  pListCtrl->SetItemText(  iItem,  index,  CString(  timeBuf  )  );
			index  =  12;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  CQyString(  timeBuf  )  );


			iItem ++;
			nItem[0]  =  iItem;
	}



	iRet  =  0;
errLabel:
	return  iRet;

}

int  listObjs_dlgMsgList_myDb(  void  *  pDbParam,  void  *  pQueryParam,  HWND  hListCtrlParam,  QY_MESSENGER_ID  *  pIdInfoParam  )
{

	CMyDb					*	pDb			=	(  CMyDb  *  )pDbParam;
	int							nItem[1]	=	{0};
	COMMON_PARAM				commonParam;

	MACRO_makeCommonParam3(  pDb,  hListCtrlParam,  nItem,  commonParam  );

	qTraverse(  pDb->m_var.pQ_qyImMsgTab,  tmpHandler_listObjs_dlgMsgList_myDb,  &commonParam,  pIdInfoParam  );
#if  0
 
	QY_MC_QUERY				*	pQuery		=	(  QY_MC_QUERY  *  )pQueryParam;
	CListCtrl				*	pListCtrl	=	(  CListCtrl  *  )pListCtrlParam;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	CRecordset					rs(  ( CDatabase * )pDbParam  );
	int							nFields;
	CDBVariant					varVals[30];
	char					*	tmpPtr		=	NULL;
	int							index;
	int							nItem;
	//  TCHAR						tBuf[256];
	int							i;
	CQyString					sqlStr;
		

	sqlStr  =  CQyString(  pQuery->selectPart  );
	sqlStr  =  sqlStr  +  CQyString(  _T(  " "  )  )  +  CQyString(  pQuery->fromPart  );
	if  (  pQuery->wherePart[0]  )  {
		sqlStr  =  sqlStr  +  CQyString(  _T(  " where "  )  )  +  CQyString(  pQuery->wherePart  );
	}
	if  (  pQuery->sortPart[0]  )  {
		sqlStr  =  sqlStr  +  CQyString(  _T(  " order by "  )  )  +  CQyString(  pQuery->sortPart  );
	}
	
	try  {
		 if  (  !rs.Open(  CRecordset::forwardOnly,  sqlStr  )  )  goto  errLabel;
		 nFields  =  rs.GetODBCFieldCount(  );
		 if  (  nFields  >  sizeof(  varVals  )  /  sizeof(  varVals[0]  )  )  {
			 traceLogA(  "%s: varVal is too small.",  __FILE__  );
			 goto  errLabel;
		 }
		 //  MACRO_qyAssert(  nFields  ==  m_var.nFields,  "CDlgQnmCfgPcGrps×Ö¶ÎÊý²»Æ¥Åä"  );

		 int  cnt  =  rs.GetRecordCount(  );


		 for  (  nItem  =  0;  !rs.IsEOF(  );  rs.MoveNext(  ),  nItem  ++  )  {


			 TCHAR	output[256]	=	_T(  ""  );
			 int	size  =  mycountof(  output  );

			 for  (  index  =  0;  index  <  nFields;  index  ++  )  {

			 	  displayQnmElement_ts(  0,  pQuery,  &rs,  index,  output,  size  );

				  if  (  !index  )  pListCtrl->InsertItem(  nItem,  output  );
				  else  pListCtrl->SetItemText(  nItem,  index,  output  );
			 }

		 }
			  //  if  (  m_var.ucbIdSeletedValid  &&  m_var.idSelected  ==  rcd.id  )  m_var.nItemSelected  =  nItem;
			  
		 
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgCfgStandardNames::listCfgStandardNames failed."  )  );
		   goto  errLabel;
	}

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
#endif	
	 return  0;
}


#ifdef  __DEBUG__

 int  tmpHandler_printQ_imObj(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	QY_MESSENGER_REGINFO  regInfo;
	TCHAR	tBuf[128]  =  _T(  ""  );

	CMyDb	*  pDb	=  (  CMyDb  *  )p0;
	int  *  cnt  =  (  int  *  )p1;
	//  p1
	QMEM_qyImObj  *  pQMem  =  (  QMEM_qyImObj  *  )p2;


	int  index  =  *cnt;


	QY_DMITEM  *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
					
	int  iType  =  pQMem->messengerInfo.uiType;

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );

	traceLog(  _T(  "\t%d, id %I64u,  uiType %d,  %s"  ),  index,  pQMem->messengerInfo.idInfo.ui64Id,  pQMem->messengerInfo.uiType,  tBuf  );
	
	index  ++;

	*cnt  =  index;

	iRet  =  0;
errLabel:
	return  iRet;

}

 
 int  printQ_imObj(  void  *  pDbParam,  int  iDbType,  LPCTSTR  hint  )		//
{
	if  (  !pDbParam  )  return  -1;
	if  (  iDbType  !=  CONST_dbType_myDb  )  return  -1;

	if  (  !hint  )  hint  =  _T(  ""  );
	int  cnt  =  0;

	switch(  iDbType  ){
		
		  case  CONST_dbType_myDb:
		  default:
				CMyDb		*  pDb	=	(  CMyDb  *  )pDbParam;	

				traceLog(  _T(  "%s: printQ_imObj %s starts, %d qNodes"  ),  hint,  pDb->m_var.pQ_qyImObjTab->cfg.name,  pDb->m_var.pQ_qyImObjTab->uiQNodes  );

				qTraverse(  pDb->m_var.pQ_qyImObjTab,  (  PF_commonHandler  )tmpHandler_printQ_imObj,  pDbParam,  (  void  *  )&cnt  );
	
				traceLog(  _T(  "printQ_imObj ends"  )  );

			  break;	
	}

	
	return  0;
}

  int  tmpHandler_printQ_imObjRegInfo(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	QY_MESSENGER_REGINFO  regInfo;
	TCHAR	tBuf[128]  =  _T(  ""  );

	CMyDb	*  pDb	=  (  CMyDb  *  )p0;
	int  *  cnt  =  (  int  *  )p1;
	QMEM_qyImObjRegInfo  *  pQMem  =  (  QMEM_qyImObjRegInfo  *  )p2;


	int  index  =  *cnt;

	//  if  (  pQMem->messengerInfo.uiType  ==  CONST_objType_me  ||  pQMem->messengerInfo.uiType  ==  CONST_objType_messenger  )  
	{
		QY_MC	*	pQyMc		=  QY_GET_GBUF(  );
		MY_REG_DESC		desc;
		int  i  =  0;
		//
		memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		regInfo.uiType  =  CONST_imCommType_messengerRegInfo;
		//  id
		regInfo.iCustomId  =  qyGetCustomId(  );

		memcpy(  &regInfo.addr,  &pQMem->myRegInfo.addr,  sizeof(  regInfo.addr  )  );
		
		memcpy(  regInfo.uiFieldIds,  pQMem->myRegInfo.uiFieldIds,  sizeof(  regInfo.uiFieldIds  )  );
		memcpy(  regInfo.u.cols,  pQMem->myRegInfo.u.cols,  sizeof(  regInfo.u.cols  )  );
		
		//
		MACRO_setPtrs(  CONST_fieldIdTable_en,  regInfo,  regInfo.fields  );

		if  (  !regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  )  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );	
		}	
	}

	traceLog(  _T(  "\t%d, id %I64u,  %s"  ),  index,  pQMem->myRegInfo.addr.idInfo.ui64Id,  tBuf  );
	
	index  ++;

	*cnt  =  index;

	iRet  =  0;
errLabel:
	return  iRet;

}


  int  printQ_imObjRegInfo(  void  *  pDbParam,  int  iDbType,  LPCTSTR  hint  )		//
{
	if  (  !pDbParam  )  return  -1;
	if  (  iDbType  !=  CONST_dbType_myDb  )  return  -1;

	if  (  !hint  )  hint  =  _T(  ""  );
	int  cnt  =  0;

	switch(  iDbType  ){
		
		  case  CONST_dbType_myDb:
		  default:
				CMyDb		*  pDb	=	(  CMyDb  *  )pDbParam;	

				traceLog(  _T(  "%s: printQ_imObjRegInfo %s starts, %d qNodes"  ),  hint,  pDb->m_var.pQ_qyImObjRegInfoTab->cfg.name,  pDb->m_var.pQ_qyImObjRegInfoTab->uiQNodes  );

				qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  (  PF_commonHandler  )tmpHandler_printQ_imObjRegInfo,  pDbParam,  (  void  *  )&cnt  );
	
				traceLog(  _T(  "printQ_imObjRegInfo ends"  )  );

			  break;	
	}

	
	return  0;
}

 int  tmpHandler_printQ_imObjRule(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	TCHAR	tBuf[128]  =  _T(  ""  );

	CMyDb	*  pDb	=  (  CMyDb  *  )p0;
	int  *  cnt  =  (  int  *  )p1;
	//  p1
	QMEM_qyImObjRule  *  pQMem  =  (  QMEM_qyImObjRule  *  )p2;


	int  index  =  *cnt;

	QY_DMITEM  *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable_autoAnswer  );
					
	int  iRuleType  =  pQMem->ruleRcd.uiRuleType;

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iRuleType  )  )  );

	traceLog(  _T(  "\t%d, id %I64u,  id %I64u,  uiType %d,  %s"  ),  index,  (   (  pQMem->ruleRcd.idInfo.ui64Id  )  ?  pQMem->ruleRcd.idInfo.ui64Id  :  0  ),  (  pQMem->ruleRcd.idInfo_related.ui64Id  ?  pQMem->ruleRcd.idInfo_related.ui64Id  :  0  ),  pQMem->ruleRcd.uiRuleType,  tBuf  );
	
	index  ++;

	*cnt  =  index;

	iRet  =  0;
errLabel:
	return  iRet;

}

  int  printQ_imObjRule(  void  *  pDbParam,  int  iDbType,  LPCTSTR  hint  )
{
	if  (  !pDbParam  )  return  -1;
	if  (  iDbType  !=  CONST_dbType_myDb  )  return  -1;

	if  (  !hint  )  hint  =  _T(  ""  );
	int  cnt  =  0;

	CMyDb  *  pDb  =  (  CMyDb  *  )pDbParam;
	 
	traceLog(  _T(  "%s: printQ_imObjRuleInfo %s starts, %d qNodes"  ),  hint,  pDb->m_var.pQ_qyImObjRuleTab->cfg.name,  pDb->m_var.pQ_qyImObjRuleTab->uiQNodes  );

	qTraverse(  pDb->m_var.pQ_qyImObjRuleTab,  (  PF_commonHandler  )tmpHandler_printQ_imObjRule,  pDbParam,  (  void  *  )&cnt  );

	traceLog(  _T(  "printQ_imObjRuleInfo ends"  )  );

		return  0;
}

 int  tmpHandler_printQ_imTask(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	TCHAR	tBuf[128]  =  _T(  ""  );

	CMyDb	*  pDb	=  (  CMyDb  *  )p0;
	int  *  cnt  =  (  int  *  )p1;
	//  p1
	IM_TASK_RCD  *  pQMem  =  (  IM_TASK_RCD  *  )p2;

	int  index  =  *cnt;

#if  10
	QY_DMITEM  *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyStatusTable  );
					
	int  iStatus  =  pQMem->iStatus;

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iStatus  )  )  );
#endif
	traceLog(  _T(  "\t%d, id %I64u,  id %I64u,  iStatus %d,  %s"  ),  index,  pQMem->idInfo_send.ui64Id,  pQMem->idInfo_recv.ui64Id,  pQMem->iStatus,  tBuf  );
	
	index  ++;

	*cnt  =  index;

	iRet  =  0;
errLabel:
	return  iRet;

}
  int  printQ_imTask(  void  *  pDbParam,  int  iDbType,  LPCTSTR  hint  )
{
	if  (  !pDbParam  )  return  -1;
	if  (  iDbType  !=  CONST_dbType_myDb  )  return  -1;

	if  (  !hint  )  hint  =  _T(  ""  );
	int  cnt  =  0;

	CMyDb  *  pDb  =  (  CMyDb  *  )pDbParam;
	 
	traceLog(  _T(  "%s: printQ_imTaskInfo %s starts, %d qNodes"  ),  hint,  pDb->m_var.pQ_qyImTaskTab->cfg.name,  pDb->m_var.pQ_qyImTaskTab->uiQNodes  );

	qTraverse(  pDb->m_var.pQ_qyImTaskTab,  (  PF_commonHandler  )tmpHandler_printQ_imTask,  pDbParam,  (  void  *  )&cnt  );

	traceLog(  _T(  "printQ_imTaskInfo ends"  )  );

		return  0;
}

 __declspec(  dllexport  )  int  test_myDb(  LPCTSTR  hint  )
 {
	 QY_MC  *  pQyMc	=	QY_GET_GBUF(  );

				 CQnmDb	db;
				 void  *  pDb;
				 pDb  =  db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  );
				 if  (  pDb  )  {
#if  0
					 printQ_imObj(  pDb,  pQyMc->cfg.db.iDbType,  hint  );
#endif			 //
#if  0
					 printQ_imObjRegInfo(  pDb,  pQyMc->cfg.db.iDbType,  hint  );
#endif			 //
#if  0
					 printQ_imObjRule(  pDb,  pQyMc->cfg.db.iDbType,  hint  );
#endif
#if  0
					 printQ_imTask(  pDb,  pQyMc->cfg.db.iDbType,  hint  );
#endif
				 }

	 return  0;
 }


#endif


  int  tmpHandler_displayImTask_cur(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 int  iRet  =  -1;
	 QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	 COMMON_PARAM	*	pCommonParam	=  (  COMMON_PARAM  *  )p0;
	 //
	 CMyDb			*	pDb				=  (  CMyDb  *  )pCommonParam->p0;
	 //  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
	 HWND				hListCtrl		=	(  HWND  )pCommonParam->p1;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int				iItem			=  (  int  )pCommonParam->p2;
	 //
	 BOOL				bUnprocedOnly	=	(  BOOL  )p1;
	 //
	 IM_TASK_RCD	*	pQMem			=  (  IM_TASK_RCD  *  )p2;
	 int				index			=  0;

	 if  (  bUnprocedOnly  )  {
		 if  (  pQMem->iStatus  ==  CONST_imTaskStatus_req
			 ||  pQMem->iStatus  ==  CONST_imTaskStatus_resp
			 ||  pQMem->iStatus  ==  CONST_imTaskStatus_applyToSend
			 ||  pQMem->iStatus  ==  CONST_imTaskStatus_waitToSend
			 ||  pQMem->iStatus  ==  CONST_imTaskStatus_applyToRecv
			 ||  pQMem->iStatus  ==  CONST_imTaskStatus_waitToRecv
			 ||  pQMem->iStatus  ==  CONST_imTaskStatus_sending
			 ||  pQMem->iStatus  ==  CONST_imTaskStatus_receiving  )
		 {
			  }
		 else  {
			   iRet  =  0;  goto  errLabel;
		 }
	 }

	 //
	 {
		TCHAR	tBuf[255  +  1]  =  _T(  ""  );
		QY_MESSENGER_REGINFO    regInfo;
		MY_REG_DESC				desc;
		char		  timeBuf[CONST_qyTimeLen  +  1]  =  "";

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQMem->id  );
		//  index  =  0;  pListCtrl->InsertItem(  iItem,  tBuf  );
		index  =  0;  myListCtrl_InsertItem(  hListCtrl,  iItem,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pQMem->uiType  )  );
		//  index  =  1;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
		index  =  1;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		if  (  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_bGetMessengerRegInfoBySth_myDb,  &pQMem->idInfo_send,  &regInfo  )  >  0  ){
			regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  );
			if  (  desc.pSyr[0]  )  _sntprintf(  pQMem->senderDesc,  mycountof(  pQMem->senderDesc  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );  
		}
		//  index  =  2;  pListCtrl->SetItemText(  iItem,  index,  pQMem->senderDesc  );
		index  =  2;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  pQMem->senderDesc  );

		if  (  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_bGetMessengerRegInfoBySth_myDb,  &pQMem->idInfo_recv,  &regInfo  )  >  0  ){
			regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  );
			if  (  desc.pSyr[0]  )  _sntprintf(  pQMem->receiverDesc,  mycountof(  pQMem->receiverDesc  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );  
		}
		//  index  =  3;  pListCtrl->SetItemText(  iItem,  index,  pQMem->receiverDesc  );
		index  =  3;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  pQMem->receiverDesc  );

		//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQMem->iStatus  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_qyStatusTable_en,  pQMem->iStatus  )  );
		//  index  =  4;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
		index  =  4;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQMem->subject  );
		//  index  =  5;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
		index  =  5;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		getTimeStr(  pQMem->tSendTime,  timeBuf,  mycountof(  timeBuf  )  );
		//  index  =  6;  pListCtrl->SetItemText(  iItem,  index,  CQyString(  timeBuf  )  );
		index  =  6;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  CQyString(  timeBuf  )  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQMem->uiTranNo  );
		//  index  =  7;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
		index  =  7;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		getTimeStr(  pQMem->tRecvTime,  timeBuf,  mycountof(  timeBuf  )  );
		//  index  =  8;  pListCtrl->SetItemText(  iItem,  index,  CQyString(  timeBuf  )  );
		index  =  8;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  CQyString(  timeBuf  )  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQMem->content  );
		//  index  =  9;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
		index  =  9;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->idInfo_send.ui64Id  );
		//  index  =  10;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
		index  =  10;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->idInfo_recv.ui64Id  );
		//  index  =  11;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
		index  =  11;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		//  2014/07/30
		getTimeStr(  pQMem->tLastModifiedTime,  timeBuf,  mycountof(  timeBuf  )  );
		//  index  =  6;  pListCtrl->SetItemText(  iItem,  index,  CQyString(  timeBuf  )  );
		index  =  12;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  CQyString(  timeBuf  )  );

	 }


	 iRet  =  0;
errLabel:
	 return  iRet;
 }
BOOL  bDisplayMcViewContent_imTaskList_unproced(  CListCtrl  * pListCtrl,  void  *  p1,  void  *  p2  )
 {
	 BOOL  bRet  =  FALSE;
	 QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  FALSE;
	 FUNCS_for_isCliHelp	*pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  goto  errLabel;
#if  0
	 QY_SERVICEGUI_INFO	*	pSgi		=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  goto  errLabel;
	 MC_VAR_isCli		*	pProcInfo	=	(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  goto  errLabel;
#endif
	 //
	 if  (  !pListCtrl  )  goto  errLabel;
	 HWND  hListCtrl  =  pListCtrl->m_hWnd;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int					cnt			=	0;
	 MIS_CNT			*	pMisCnt		=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 CMyDb				*	pDb			=	(  CMyDb  *  )pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )->pDb;

#if  0
	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imTaskListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );
#endif
	 myListCtrl_delAllColumns(  hListCtrl  );
	 if  (  !myListCtrl_bAddColumns(  hListCtrl,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imTaskListColumns  )  )  )  goto  errLabel;

	 myListCtrl_DeleteAllItems(  hListCtrl  );


	 COMMON_PARAM	commonParam;
	 MACRO_makeCommonParam3(  pDb,  hListCtrl,  (  void  *  )cnt,  commonParam  );
	 
	 BOOL  bUnprocedOnly  =  TRUE;
	 qTraverse(  pDb->m_var.pQ_qyImTaskTab,  tmpHandler_displayImTask_cur,  &commonParam,  (  void  *  )bUnprocedOnly  );
	  

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
 }

  //  2013/02/17
 BOOL  bViewImTaskList_unproced_myDb(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet										=	FALSE;
	QY_MC				*	pQyMc										=	QY_GET_GBUF(  );

	viewStatusCli(  CONST_qyLvType_unprocedImTaskList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unfinished  ),  CONST_resId_imTaskListColumns,	 (  PF_commonHandler  )bDisplayMcViewContent_imTaskList_unproced,  NULL   );

	bRet  =  0;
errLabel:
	return  bRet;
}

 BOOL  bDisplayMcViewContent_imTaskList_cur(  CListCtrl  * pListCtrl,  void  *  p1,  void  *  p2  )
 {
	 BOOL  bRet  =  FALSE;
	 QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
	 MC_VAR_isCli		*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  FALSE;
	 FUNCS_for_isCliHelp	*pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  FALSE;
	 //
	 if  (  !pListCtrl  )  goto  errLabel;
	 HWND  hListCtrl  =  pListCtrl->m_hWnd;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int					cnt			=	0;
	 MIS_CNT			*	pMisCnt		=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 CMyDb				*	pDb			=	(  CMyDb  *  )pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )->pDb;

#if  0
	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imTaskListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );
#endif
	 myListCtrl_delAllColumns(  hListCtrl  );
	 if  (  !myListCtrl_bAddColumns(  hListCtrl,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imTaskListColumns  )  )  )  goto  errLabel;

	 myListCtrl_DeleteAllItems(  hListCtrl  );

	 COMMON_PARAM	commonParam;
	 //  MACRO_makeCommonParam3(  pDb,  pListCtrl,  (  void  *  )cnt,  commonParam  );
	 MACRO_makeCommonParam3(  pDb,  hListCtrl,  (  void  *  )cnt,  commonParam  );
	 
	 BOOL  bUnprocedOnly  =  FALSE;
	 qTraverse(  pDb->m_var.pQ_qyImTaskTab,  tmpHandler_displayImTask_cur,  &commonParam,  (  void  *  )bUnprocedOnly  );
	  

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
 }


//  2013/02/16
 BOOL  bViewImTaskList_cur_myDb(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet			=	FALSE;
	QY_MC				*	pQyMc			=	QY_GET_GBUF(  );

	viewStatusCli(  CONST_qyLvType_currentImTaskList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_current  ),  CONST_resId_imTaskListColumns,	 (  PF_commonHandler  )bDisplayMcViewContent_imTaskList_cur,  NULL   );

	bRet  =  TRUE;

errLabel:

	return  bRet;
	
}


  BOOL  bViewImTaskList_his_myDb(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
  {
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bViewImTaskList_his_myDb"  )  );
#endif
	  return  FALSE;
  }

  int  tmpHandler_displayImObjList(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int  iRet  =  -1;
	 COMMON_PARAM	*	pCommonParam	=  (  COMMON_PARAM  *  )p0;
	 //
	 CMyDb			*	pDb				=  (  CMyDb  *  )pCommonParam->p0;
	 //  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
	 HWND				hListCtrl		=	(  HWND  )pCommonParam->p1;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int				iItem			=  (  int  )pCommonParam->p2;
	 //
	 BOOL				bUnprocedOnly	=	(  BOOL  )p1;
	 //
	 QMEM_qyImObj	*	pQMem			=  (  QMEM_qyImObj  *  )p2;
	 int				index			=  0;
	 QY_MC			*	pQyMc			=	QY_GET_GBUF();

	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_DMITEM				*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

	memset(  &regInfo,  0,  sizeof(  regInfo  )  );

	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	if  (  pQMem->messengerInfo.iStatus  ==  CONST_qyStatus_ok
		&&  pQMem->messengerInfo.uiType  !=  CONST_objType_imGrp  )
	{
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQMem->messengerInfo.iRcdId  );
	 index  =  0;  myListCtrl_InsertItem(  hListCtrl,  iItem,  tBuf  );
	
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  pQMem->messengerInfo.uiType  )  );
	index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->messengerInfo.idInfo.ui64Id  );
	index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

#if  0
		if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pMyDb,  CONST_dbType_myDb,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pQMem->messengerInfo.misServName,  &pQMem->messengerInfo.idInfo,  0,  &pQMem->messengerInfo,  &regInfo,  NULL,  NULL  )  )  {
			memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		}
#endif
		if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  CONST_dbType_myDb,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  pQMem->messengerInfo.misServName, &pQMem->messengerInfo.idInfo,  0,  &regInfo  )  )  {
			memset(  &regInfo,  0,  sizeof(  regInfo  ) );
		}
		int		tmpiRet;
		TCHAR	talkerDesc[128]  =  _T(  ""  );
		regInfo2Desc(  0,  &regInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  ); 

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pDw  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pBm  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pSyr  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
		//
		QY_DMITEM  *  pTable;
		pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imObjRoleTable  );
		//		   
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  pTable,  pQMem->messengerInfo.iRole  )  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
	
		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  ( pQMem->messengerInfo.iStatus  ? _T("Del"):_T("Ok"))  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
	}



	 iRet  =  0;
errLabel:
	 return  iRet;
}

  BOOL  bDisplayMcViewContent_imObjList(  CListCtrl  * pListCtrl,  void  *  p1,  void  *  p2  )
{
	 BOOL  bRet  =  FALSE;
	 QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
	 MC_VAR_isCli		*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  goto  errLabel;	 
	 FUNCS_for_isCliHelp	*pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  goto  errLabel;
	 
	 if  (  !pListCtrl  )  goto  errLabel;
	 HWND  hListCtrl  =  pListCtrl->m_hWnd;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int					cnt			=	0;
	 MIS_CNT			*	pMisCnt		=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 CMyDb				*	pDb			=	(  CMyDb  *  )pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )->pDb;

#if  0
	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imObjColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );
#endif
	 myListCtrl_delAllColumns(  hListCtrl  );
	 if  (  !myListCtrl_bAddColumns(  hListCtrl,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imObjListColumns  )  )  )  goto  errLabel;

	 myListCtrl_DeleteAllItems(  hListCtrl  );

	 COMMON_PARAM	commonParam;
	 //  MACRO_makeCommonParam3(  pDb,  pListCtrl,  (  void  *  )cnt,  commonParam  );
	 MACRO_makeCommonParam3(  pDb,  hListCtrl,  (  void  *  )cnt,  commonParam  );
	 
	 qTraverse(  pDb->m_var.pQ_qyImObjTab,  tmpHandler_displayImObjList,  &commonParam,  NULL  );
	  

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}
 
  BOOL  bViewImObjList_myDb(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	  BOOL			bRet		=  FALSE;
	  QY_MC		*	pQyMc		=	QY_GET_GBUF();
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bViewImObjList_myDb"  )  );
#endif

		viewStatusCli(  CONST_qyLvType_imObjList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyMessengerList  ),  CONST_resId_imObjListColumns,	 (  PF_commonHandler  )bDisplayMcViewContent_imObjList,  NULL   );

	  bRet  =  TRUE;
errLabel:

	  return  bRet;
}

  int  tmpHandler_displayImGrpList(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int  iRet  =  -1;
	 COMMON_PARAM	*	pCommonParam	=  (  COMMON_PARAM  *  )p0;
	 //
	 CMyDb			*	pDb				=  (  CMyDb  *  )pCommonParam->p0;
	 //  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
	 HWND				hListCtrl		=	(  HWND  )pCommonParam->p1;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int				iItem			=  (  int  )pCommonParam->p2;
	 //
	 BOOL				bUnprocedOnly	=	(  BOOL  )p1;
	 //
	 IM_GRP_INFO	*	pQMem			=  (  IM_GRP_INFO  *  )p2;
	 int				index			=  0;
	 QY_MC			*	pQyMc			=	QY_GET_GBUF();

	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_DMITEM				*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

	memset(  &regInfo,  0,  sizeof(  regInfo  )  );

	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	//  if  (  pQMem->uiType  ==  CONST_objType_imGrp  )
	{
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  =  0;  myListCtrl_InsertItem(  hListCtrl,  iItem,  tBuf  );
	
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  CONST_objType_imGrp  )  );
	index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->idInfo.ui64Id  );
	index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

#if  0
		if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pMyDb,  CONST_dbType_myDb,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pQMem->messengerInfo.misServName,  &pQMem->messengerInfo.idInfo,  0,  &pQMem->messengerInfo,  &regInfo,  NULL,  NULL  )  )  {
			memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		}
#endif
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQMem->name  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imGrpSubtypeTable  ),  pQMem->usSubtype  )  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->idInfo_creator.ui64Id  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

	}

	 iRet  =  0;
errLabel:
	 return  iRet;
}

  BOOL  bDisplayMcViewContent_imGrpList(  CListCtrl  * pListCtrl,  void  *  p1,  void  *  p2  )
{
	 BOOL  bRet  =  FALSE;
	 QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	 FUNCS_for_isCliHelp	*pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  goto  errLabel;

	 //	 
	 if  (  !pListCtrl  )  goto  errLabel;
	 HWND  hListCtrl  =  pListCtrl->m_hWnd;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int					cnt			=	0;
	 MIS_CNT			*	pMisCnt		=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 CMyDb				*	pDb			=	(  CMyDb  *  )pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )->pDb;

#if  0
	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imObjColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );
#endif
	 myListCtrl_delAllColumns(  hListCtrl  );
	 if  (  !myListCtrl_bAddColumns(  hListCtrl,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imGrpListColumns  )  )  )  goto  errLabel;

	 myListCtrl_DeleteAllItems(  hListCtrl  );

	 COMMON_PARAM	commonParam;
	 //  MACRO_makeCommonParam3(  pDb,  pListCtrl,  (  void  *  )cnt,  commonParam  );
	 MACRO_makeCommonParam3(  pDb,  hListCtrl,  (  void  *  )cnt,  commonParam  );
	 
	 qTraverse(  pDb->m_var.pQ_qyImGrpInfoTab,  tmpHandler_displayImGrpList,  &commonParam,  NULL  );
	  

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}



  BOOL  bViewImGrpList_myDb(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	  BOOL			bRet		=  FALSE;
	  //QY_MC		*	pQyMc		=	QY_GET_GBUF();

		viewStatusCli(  CONST_qyLvType_imGrpList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyImGrpList  ),  CONST_resId_imGrpListColumns,	 (  PF_commonHandler  )bDisplayMcViewContent_imGrpList,  NULL   );

	  bRet  =  TRUE;
errLabel:

	  return  bRet;
}



  //////////////////

   int  tmpHandler_displayImGrpMemList(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int  iRet  =  -1;
	 COMMON_PARAM	*	pCommonParam	=  (  COMMON_PARAM  *  )p0;
	 //
	 CMyDb			*	pDb				=  (  CMyDb  *  )pCommonParam->p0;
	 //  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
	 HWND				hListCtrl		=	(  HWND  )pCommonParam->p1;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int				iItem			=  (  int  )pCommonParam->p2;
	 //
	 BOOL				bUnprocedOnly	=	(  BOOL  )p1;
	 
#if  10
	 
	 //
	 IM_GRP_MEM	*	pQMem			=  (  IM_GRP_MEM  *  )p2;
	 int				index			=  0;
	 QY_MC			*	pQyMc			=	QY_GET_GBUF();


	 	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;


	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_DMITEM				*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

	memset(  &regInfo,  0,  sizeof(  regInfo  )  );



	//  if  (  pQMem->uiType  ==  CONST_objType_imGrp  )
	{
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  =  0;  myListCtrl_InsertItem(  hListCtrl,  iItem,  tBuf  );
	
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  CONST_objType_imGrp  )  );
	index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->idInfo_grp.ui64Id  );
	index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

	//
	IM_GRP_INFO  grpInfo;
	if  (  !g_dbFuncs.pf_bGetImGrpInfoBySth(  pDb,  pQyMc->cfg.db.iDbType,  _T(  ""  ),  &pQMem->idInfo_grp,  &grpInfo  )  )  memset(  &grpInfo,  0,  sizeof(  grpInfo  )  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  grpInfo.name  );	
	index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
		
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->idInfo_mem.ui64Id  );	
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  CONST_dbType_myDb,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  pQMem->misServName,  &pQMem->idInfo_mem,  0,  &regInfo  )  )  {
			memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		}

		MY_REG_DESC  desc;
		regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  );  

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pDw  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pBm  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pSyr  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imGrpMemRoleTable  ),  pQMem->iRole  )  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );


		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );


		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  ( pQMem->iStatus  ? _T("Del"):_T("Ok"))  );		
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

	}

#endif

	 iRet  =  0;
errLabel:
	 return  iRet;
}


  BOOL  bDisplayMcViewContent_imGrpMemList(  CListCtrl  * pListCtrl,  void  *  p1,  void  *  p2  )
{
	 BOOL  bRet  =  FALSE;
	 QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
	
	 MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	
	 FUNCS_for_isCliHelp	*pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  goto  errLabel;

	 
	 if  (  !pListCtrl  )  goto  errLabel;
	 HWND  hListCtrl  =  pListCtrl->m_hWnd;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int					cnt			=	0;
	 MIS_CNT			*	pMisCnt		=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 CMyDb				*	pDb			=	(  CMyDb  *  )pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )->pDb;

#if  0
	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imObjColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );
#endif
	 myListCtrl_delAllColumns(  hListCtrl  );
	 if  (  !myListCtrl_bAddColumns(  hListCtrl,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imGrpMemListColumns  )  )  )  goto  errLabel;

	 myListCtrl_DeleteAllItems(  hListCtrl  );

	 COMMON_PARAM	commonParam;
	 //  MACRO_makeCommonParam3(  pDb,  pListCtrl,  (  void  *  )cnt,  commonParam  );
	 MACRO_makeCommonParam3(  pDb,  hListCtrl,  (  void  *  )cnt,  commonParam  );
	 
	 qTraverse(  pDb->m_var.pQ_qyImGrpMemTab,  tmpHandler_displayImGrpMemList,  &commonParam,  NULL  );
	  

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


 BOOL  bViewImGrpMemList_isClient_myDb(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
 {
	  BOOL			bRet		=  FALSE;
	  //QY_MC		*	pQyMc		=	QY_GET_GBUF();
	  	
	  viewStatusCli(  CONST_qyLvType_imGrpMemList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyImGrpMemList  ),  CONST_resId_imGrpMemListColumns,	 (  PF_commonHandler  )bDisplayMcViewContent_imGrpMemList,  NULL   );

	  bRet  =  TRUE;
errLabel:

	  return  bRet;
 }

 ///////////////////////


  int  tmpHandler_displayImObjRuleList(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int  iRet  =  -1;
	 COMMON_PARAM	*	pCommonParam	=  (  COMMON_PARAM  *  )p0;
	 //
	 CMyDb			*	pDb				=  (  CMyDb  *  )pCommonParam->p0;
	 //  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
	 HWND				hListCtrl		=	(  HWND  )pCommonParam->p1;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int				iItem			=  (  int  )pCommonParam->p2;
	 //
	 BOOL				bUnprocedOnly	=	(  BOOL  )p1;
	 
#if  10
	 
	 //
	 QMEM_qyImObjRule	*	pQMem			=  (  QMEM_qyImObjRule  *  )p2;
	 int				index			=  0;
	 QY_MC			*	pQyMc			=	QY_GET_GBUF();


	 	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;


	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_DMITEM				*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

	memset(  &regInfo,  0,  sizeof(  regInfo  )  );




	//  if  (  pQMem->uiType  ==  CONST_objType_imGrp  )
	{
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  =  0;  myListCtrl_InsertItem(  hListCtrl,  iItem,  tBuf  );
	 
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->ruleRcd.idInfo.ui64Id  );
	index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

	if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  CONST_dbType_myDb,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  pQMem->ruleRcd.misServName,  &pQMem->ruleRcd.idInfo_related,  0,  &regInfo  )  )  {
			memset(  &regInfo,  0,  sizeof(  regInfo  )  );
	}

		MY_REG_DESC  desc;
		regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  );  

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pDw  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pBm  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pSyr  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->ruleRcd.idInfo_related.ui64Id  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		//

		//		
		QY_DMITEM  *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleTypeTable  );			
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  pTable,  pQMem->ruleRcd.uiRuleType  )  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
		

		pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  pTable,  pQMem->ruleRcd.uiCmd  )  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
		
		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQMem->ruleRcd.col0  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
		

		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  _T(  ""  )  );		
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

	}

#endif

	 iRet  =  0;
errLabel:
	 return  iRet;
}

  BOOL  bDisplayMcViewContent_imObjRuleList(  CListCtrl  * pListCtrl,  void  *  p1,  void  *  p2  )
{
	 BOOL  bRet  =  FALSE;
	 QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  FALSE;
	 FUNCS_for_isCliHelp	*pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  goto  errLabel;
	 QY_SERVICEGUI_INFO	*	pSgi		=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  goto  errLabel;
	 if  (  !pListCtrl  )  goto  errLabel;
	 HWND  hListCtrl  =  pListCtrl->m_hWnd;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int					cnt			=	0;
	 MIS_CNT			*	pMisCnt		=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 CMyDb				*	pDb			=	(  CMyDb  *  )pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )->pDb;

#if  0
	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imObjColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );
#endif
	 myListCtrl_delAllColumns(  hListCtrl  );
	 if  (  !myListCtrl_bAddColumns(  hListCtrl,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imObjRuleListColumns  )  )  )  goto  errLabel;

	 myListCtrl_DeleteAllItems(  hListCtrl  );

	 COMMON_PARAM	commonParam;
	 //  MACRO_makeCommonParam3(  pDb,  pListCtrl,  (  void  *  )cnt,  commonParam  );
	 MACRO_makeCommonParam3(  pDb,  hListCtrl,  (  void  *  )cnt,  commonParam  );
	 
	 qTraverse(  pDb->m_var.pQ_qyImObjRuleTab,  tmpHandler_displayImObjRuleList,  &commonParam,  NULL  );
	  

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


  BOOL  bViewImObjRuleList_is_myDb(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
  {
	  BOOL			bRet		=  FALSE;
	  //QY_MC		*	pQyMc		=	QY_GET_GBUF();
	  	
	  viewStatusCli(  CONST_qyLvType_imObjRuleList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyImObjRuleList  ),  CONST_resId_imObjRuleListColumns,	 (  PF_commonHandler  )bDisplayMcViewContent_imObjRuleList,  NULL   );

	  bRet  =  TRUE;
errLabel:

	  return  bRet;
  }


    int  tmpHandler_displayDynBmpList(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int  iRet  =  -1;
	 COMMON_PARAM	*	pCommonParam	=  (  COMMON_PARAM  *  )p0;
	 //
	 CMyDb			*	pDb				=  (  CMyDb  *  )pCommonParam->p0;
	 //  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
	 HWND				hListCtrl		=	(  HWND  )pCommonParam->p1;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int				iItem			=  (  int  )pCommonParam->p2;
	 //
	 BOOL				bUnprocedOnly	=	(  BOOL  )p1;
	 
#if  10
	 
	 //
	 QMEM_qyDynBmp	*	pQMem			=  (  QMEM_qyDynBmp  *  )p2;
	 int				index			=  0;
	 QY_MC			*	pQyMc			=	QY_GET_GBUF();


	 	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;


	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_DMITEM				*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

	memset(  &regInfo,  0,  sizeof(  regInfo  )  );




	//  if  (  pQMem->uiType  ==  CONST_objType_imGrp  )
	{
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  =  0;  myListCtrl_InsertItem(  hListCtrl,  iItem,  tBuf  );
	 

	 if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  CONST_dbType_myDb,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  pQMem->dynBmpRcd.misServName,  &pQMem->dynBmpRcd.idInfo,  0,  &regInfo  )  )  {
			memset(  &regInfo,  0,  sizeof(  regInfo  )  );
	}

		MY_REG_DESC  desc;
		regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  );  

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pDw  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pBm  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pSyr  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );


	//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->dynBmpRcd.idInfo.ui64Id  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		//

		//		
		QY_DMITEM  *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );			
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  pTable,  pQMem->dynBmpRcd.uiObjType  )  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
		
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQMem->dynBmpRcd.usIndex  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQMem->dynBmpRcd.name  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );	

		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  _T(  ""  )  );		
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

	}

#endif

	 iRet  =  0;
errLabel:
	 return  iRet;
}



  ///////////////

  int  tmpHandler_displayRegInfoList(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int  iRet  =  -1;
	 COMMON_PARAM	*	pCommonParam	=  (  COMMON_PARAM  *  )p0;
	 //
	 CMyDb			*	pDb				=  (  CMyDb  *  )pCommonParam->p0;
	 //  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
	 HWND				hListCtrl		=	(  HWND  )pCommonParam->p1;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int				iItem			=  (  int  )pCommonParam->p2;
	 //
	 BOOL				bUnprocedOnly	=	(  BOOL  )p1;
	 //
	 QMEM_qyImObjRegInfo	*	pQMem			=  (  QMEM_qyImObjRegInfo  *  )p2;
	 int				index			=  0;
	 QY_MC			*	pQyMc			=	QY_GET_GBUF();

	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_DMITEM				*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

	memset(  &regInfo,  0,  sizeof(  regInfo  )  );

	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	if  (  pQMem->myRegInfo.uiType  !=  CONST_objType_imGrp  )
	{
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  =  0;  myListCtrl_InsertItem(  hListCtrl,  iItem,  tBuf  );
	
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->myRegInfo.addr.idInfo.ui64Id  );
	index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

	if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  CONST_dbType_myDb,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  pQMem->myRegInfo.addr.misServName, &pQMem->myRegInfo.addr.idInfo,  0,  &regInfo  )  )  {
		memset(  &regInfo,  0,  sizeof(  regInfo  ) );
	}
		int		tmpiRet;
		TCHAR	talkerDesc[128]  =  _T(  ""  );
		regInfo2Desc(  0,  &regInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  ); 

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pDw  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pBm  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pSyr  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
		index++;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
	}



	 iRet  =  0;
errLabel:
	 return  iRet;
}

  BOOL  bDisplayMcViewContent_regInfoList(  CListCtrl  * pListCtrl,  void  *  p1,  void  *  p2  )
{
	 BOOL  bRet  =  FALSE;
	 QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  FALSE;
	 FUNCS_for_isCliHelp	*pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  goto  errLabel;
	 QY_SERVICEGUI_INFO	*	pSgi		=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  goto  errLabel;
	 if  (  !pListCtrl  )  goto  errLabel;
	 HWND  hListCtrl  =  pListCtrl->m_hWnd;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int					cnt			=	0;
	 MIS_CNT			*	pMisCnt		=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 CMyDb				*	pDb			=	(  CMyDb  *  )pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )->pDb;

#if  0
	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imObjColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );
#endif
	 myListCtrl_delAllColumns(  hListCtrl  );
	 if  (  !myListCtrl_bAddColumns(  hListCtrl,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_regInfoListColumns  )  )  )  goto  errLabel;

	 myListCtrl_DeleteAllItems(  hListCtrl  );

	 COMMON_PARAM	commonParam;
	 //  MACRO_makeCommonParam3(  pDb,  pListCtrl,  (  void  *  )cnt,  commonParam  );
	 MACRO_makeCommonParam3(  pDb,  hListCtrl,  (  void  *  )cnt,  commonParam  );
	 
	 qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_displayRegInfoList,  &commonParam,  NULL  );
	  

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


  BOOL  bViewRegInfoList_myDb(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	  BOOL			bRet		=  FALSE;
	  QY_MC		*	pQyMc		=	QY_GET_GBUF();
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bViewImObjList_myDb"  )  );
#endif

		viewStatusCli(  CONST_qyLvType_regInfoList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyPcUsrList2  ),  CONST_resId_regInfoListColumns,	 (  PF_commonHandler  )bDisplayMcViewContent_regInfoList,  NULL   );

	  bRet  =  TRUE;
errLabel:

	  return  bRet;
}


BOOL  bInsertPhoneGuest_procMsgTalk_work_myDb(  void  *  pDbParam,  int  iDbType,  void  *  pQyMcParam,  MIS_MSG_TALK  *  pMsg,  void  *  pGuestParam  )
{
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bInsertPhoneGuest_procMsgTalk_work_myDb"  )  );
#endif
	  return  FALSE;
}

BOOL  bUpdateImTask_bChkQyMcEnv_mis_myDb(  void  *  pDb,  int  iStatus_set,  int  iStatus_0,  int  iStatus_1  )
{
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bUpdateImTask_bChkQyMcEnv_mis_myDb"  )  );
#endif
	  return  TRUE;
}

//  int  deleteDynBmp_tmpHandler_delOld_dynBmpQ_myDb(  void  *  pDb,  int  id  )
int  deleteOldDynBmp_mcProcResp_retrieveDynBmps_myDb(  void  *  pDb,  int  iDbType,  char  *  pTimeBuf  )
{
	return  0;
}

#if  0
int  init_mcProcResp_retrieveDynBmps_myDb(  void  *  pDb,  void  *  pCtxParam  )
{
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: iSelectDynBmp_mcProcResp_retrieveDynBmps_myDb"  )  );
#endif
	return  -1;
}
#endif

BOOL  bInsertDynBmp_mcProcResp_retrieveDynBmps_myDb(  void  *  pDb,  void  *  pMisCntParam,  QIS_dynBmp_info  *  pMem,  char  *  pTimeBuf  )
{
	BOOL  bRet  =  FALSE;
	CMyDb		*	pMyDb								=	(  CMyDb  *  )pDb;
	
	QMEM_qyDynBmp  qMem;

	memset(  &qMem,  0,  sizeof(  qMem  )  );
	
	qMem.dynBmpRcd.idInfo.ui64Id  =  pMem->qisResObj.idInfo.ui64Id;
	qMem.dynBmpRcd.uiObjType  =  pMem->qisResObj.resObj.uiObjType;
	qMem.dynBmpRcd.usIndex  =  pMem->qisResObj.resObj.usIndex_obj;
	safeTcsnCpy(  pMem->name,  qMem.dynBmpRcd.name,  mycountof(  qMem.dynBmpRcd.name  )  );
	safeTcsnCpy(  pMem->cusName,  qMem.dynBmpRcd.cusName,  mycountof(  qMem.dynBmpRcd.cusName  )  );

	if  (  qPostMsg(  &qMem,  sizeof(  qMem  ),  pMyDb->m_var.pQ_qyDynBmpTab,  _T(  "bInsertDynBmp_mcProcResp"  )))  goto  errLabel;

	bRet  =  TRUE;
errLabel:

	  return  bRet;
}


int  tmpHandler_bUpdateDynBmp_mcProcResp_retrieveDynBmps_myDb(  void  *  p0,  void  *  p1,  QMEM_qyDynBmp  *  pQMem  )
{
	int  iErr  =  -1;
	QIS_dynBmp_info  *  pMem  =  (  QIS_dynBmp_info  *  )p0;
	char  *  pTimeBuf  =  (  char  *  )p1;
	//
	if  (  pQMem->dynBmpRcd.idInfo.ui64Id  ==  pMem->qisResObj.idInfo.ui64Id
		&&  pQMem->dynBmpRcd.uiObjType  ==  pMem->qisResObj.resObj.uiObjType
		&&  pQMem->dynBmpRcd.usIndex  ==  pMem->qisResObj.resObj.usIndex_obj  )
	{
		safeTcsnCpy(  pMem->name,  pQMem->dynBmpRcd.name,  mycountof(  pQMem->dynBmpRcd.name  )  );
		safeTcsnCpy(  pMem->cusName,  pQMem->dynBmpRcd.cusName,  mycountof(  pQMem->dynBmpRcd.cusName  )  );
		safeStrnCpy(  pTimeBuf,  pQMem->dynBmpRcd.startTime,  mycountof(  pQMem->dynBmpRcd.startTime  )  );
		safeStrnCpy(  pTimeBuf,  pQMem->dynBmpRcd.endTime,  mycountof(  pQMem->dynBmpRcd.endTime  )  );
		iErr  =  1;  goto  errLabel;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}


BOOL  bUpdateDynBmp_mcProcResp_retrieveDynBmps_myDb(  void  *  pDb,  QIS_dynBmp_info  *  pMem,  char  *  pTimeBuf,  int  rcdId  )
{
	BOOL			bRet								=	FALSE;
	CMyDb		*	pMyDb								=	(  CMyDb  *  )pDb;


	if  (  qTraverse(  pMyDb->m_var.pQ_qyDynBmpTab,  (  PF_commonHandler  )tmpHandler_bUpdateDynBmp_mcProcResp_retrieveDynBmps_myDb,  (  void  *  )pMem,  (  void  *  )pTimeBuf  )  <=  0  )  goto  errLabel;

	bRet  =  TRUE;
	errLabel:
	
	return  bRet;
}

BOOL  bUpdateDynBmp_mcProcResp_retrieveDynBmps2_myDb(  void  *  pDb,  QIS_dynBmp_info  *  pMem,  char  *  pTimeBuf,  int  rcdId  )
{
	BOOL			bRet								=	FALSE;
	CMyDb		*	pMyDb								=	(  CMyDb  *  )pDb;


	if  (  qTraverse(  pMyDb->m_var.pQ_qyDynBmpTab,  (  PF_commonHandler  )tmpHandler_bUpdateDynBmp_mcProcResp_retrieveDynBmps_myDb,  (  void  *  )pMem,  (  void  *  )pTimeBuf  )  <=  0  )  goto  errLabel;

	bRet  =  TRUE;
	errLabel:
	
	return  bRet;

}


BOOL  bUpdateImObjRegInfo_procMsgInput_scheduler_myDb(  void  *  pDb,  void  *  pSciParam,  void  *  pMisCntParam,  QY_MESSENGER_ID  *  pIdInfo  )
{
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bUpdateImObjRegInfo_procMsgInput_scheduler_myDb"  )  );
#endif
	  return  FALSE;
}


 BOOL  bStatImTasks_myDb(  void  *  pProcInfoParam,  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  )
{
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bStatImTasks_myDb"  )  );
#endif
	  return  FALSE;
}

 BOOL  bDeleteFromTabById_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  pTabName,  int  id  )
{
	  return  FALSE;
}
 BOOL  bDeleteFromTabByIdInfo_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{
	  return  FALSE;
}
BOOL  bDeleteImOtherRegInfoByAddr_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  LPCTSTR  pTabName,  MSGR_ADDR  *  pAddr  )
{
	  return  FALSE;
}

int  iSelectImGrpMem_dlgSelect_isCli_myDb(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  HWND  idc_hWnd  )
{
	return  -1;
}

int  tmpHandler_iSelectImObj_dlgSelect_isCli_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;

	COMMON_PARAM	*	pCommonParam	=	(  COMMON_PARAM  *  )p0;
	//
	CMyDb			*	pMyDb			=	(  CMyDb  *  )pCommonParam->p0;
	int					iDbType			=	(  int  )pCommonParam->p1;
	LPCTSTR				misServName		=	(  LPCTSTR  )pCommonParam->p2;
	//
	HWND				hCombo			=	(  HWND  )p1;
	//
	QMEM_qyImObj	*	pQMem	=	(  QMEM_qyImObj  *  )p2;

	QY_MC			*	pQyMc	=   QY_GET_GBUF(  );
	TCHAR	talkerDesc[255 + 1] =  _T(  ""  );
	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	

	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	if  (  pQMem->messengerInfo.uiType  ==  CONST_objType_messenger  )  {

		memset(  &regInfo,  0,  sizeof(  regInfo  )  );

		if  (  g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pMyDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  misServName,  &pQMem->messengerInfo.idInfo,  0,  &regInfo  )  )  {
			regInfo2Desc(  0,  &regInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  );
		}
		else  {
			memset(  &regInfo,  0,  sizeof(  regInfo  )  );
			memset(  &desc,  0,  sizeof(  desc  )  );
		}

		_sntprintf(  talkerDesc,  mycountof(  talkerDesc  ),  _T(  "%I64u - %s %s %s"  ),  pQMem->messengerInfo.idInfo.ui64Id,  desc.pDw,  desc.pBm,  desc.pSyr  );
		SendMessage(  hCombo,  CB_ADDSTRING,  0,  (  LPARAM  )talkerDesc  );		
		
	}

	iRet  =  0;
errLabel:
	return  iRet;
}

int  iSelectImObj_dlgSelect_isCli_myDb(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  )
{
	int				iRet  =  -1;
	CMyDb		*	pMyDb  =  (  CMyDb  *  )pDb;
	COMMON_PARAM	commonParam;

	MACRO_makeCommonParam3(  pMyDb,  (  void  *  )iDbType,  (  void  *  )misServName,  commonParam  ); 

	iRet  =  qTraverse(  pMyDb->m_var.pQ_qyImObjTab,  tmpHandler_iSelectImObj_dlgSelect_isCli_myDb,  &commonParam,  idc_hWnd  );
#if  0
	TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	TCHAR		tBuf[255  +  1]						=	_T(  ""  );

				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImObjTab.idStr,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4 from qyImObjTab left join qyImObjRegInfoTab on (qyImObjTab.misServName=qyImObjRegInfoTab.misServName and qyImObjTab.idStr=qyImObjRegInfoTab.idStr) where qyImObjTab.misServName=%s and qyImObjTab.uiType in (%d) order by qyImObjTab.idStr"  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.u.selectImGrp.misServName  ),  CONST_objType_messenger  );
				  if  (  enumSqlQuery(  m_var.pObjDb->pDb,  sqlBuf,  tmpHandler_displayMessenger,  GetDlgItem(  IDC_COMBO_objList  )->m_hWnd,  0,  varVals,  mycountof(  varVals  ),  NULL  )  <  0  )  goto  errLabel;

#endif				  

errLabel:
	return  iRet;
}

#if  0
int  iSelectImObjAuth2_dlgSelect_isCli_myDb(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  )
{
	return  -1;
}
#endif


int  tmpHandler_iSelectDynBmp_dlgSelect_isCli_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;

	COMMON_PARAM	*	pCommonParam	=	(  COMMON_PARAM  *  )p0;
	//
	CMyDb			*	pMyDb			=	(  CMyDb  *  )pCommonParam->p0;
	int					iDbType			=	(  int  )pCommonParam->p1;
	LPCTSTR				misServName		=	(  LPCTSTR  )pCommonParam->p2;
	//
	HWND				hCombo			=	(  HWND  )p1;
	//
	QMEM_qyDynBmp	*	pQMem	=	(  QMEM_qyDynBmp  *  )p2;

	QY_MC			*	pQyMc	=   QY_GET_GBUF(  );

	//
	TCHAR	talkerDesc[255 + 1] =  _T(  ""  );
	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	//
	TCHAR				dw[255  +  1]		=	_T(  ""  );
	TCHAR				bm[255  +  1]		=	_T(  ""  );
	TCHAR				syr[255  +  1]		=	_T(  ""  );
	//
	QY_MESSENGER_ID		idInfo;
	unsigned  int		uiObjType			=	0;
	unsigned  short		usIndex				=	0;
	TCHAR				displayName[255  +  1]	=	_T(  ""  );

	

	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	//  if  (  pQMem->messengerInfo.uiType  ==  CONST_objType_messenger  )  
	{

		memset(  &regInfo,  0,  sizeof(  regInfo  )  );

		if  (  g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pMyDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  pQMem->dynBmpRcd.misServName,  &pQMem->dynBmpRcd.idInfo,  0,  &regInfo  )  )  {
			regInfo2Desc(  0,  &regInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  );
			safeTcsnCpy(  desc.pDw,  dw,  mycountof(  dw  )  );
			safeTcsnCpy(  desc.pBm,  bm,  mycountof(  bm  )  );
			safeTcsnCpy(  desc.pSyr,  syr,  mycountof(  syr  )  );
		}

		idInfo.ui64Id  =  pQMem->dynBmpRcd.idInfo.ui64Id;
		uiObjType  =  pQMem->dynBmpRcd.uiObjType;
		usIndex  =  pQMem->dynBmpRcd.usIndex;

		_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u - %s %s %s, %s, %d"  ),  idInfo.ui64Id,  dw,  bm,  syr,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  uiObjType  ),  usIndex  );
		SendMessage(  hCombo,  CB_ADDSTRING,  0,  (  LPARAM  )displayName  );		
	}

	iRet  =  0;
errLabel:
	return  iRet;
}

int  iSelectDynBmp_dlgSelect_isCli_myDb(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  )
{
	int				iRet								=	FALSE;
	CMyDb		*	pMyDb								=	(  CMyDb  *  )pDb;
	COMMON_PARAM	commonParam;

	MACRO_makeCommonParam3(  pMyDb,  (  void  *  )iDbType,  (  void  *  )misServName,  commonParam  ); 

	iRet  =  qTraverse(  pMyDb->m_var.pQ_qyDynBmpTab,  (  PF_commonHandler  )tmpHandler_iSelectDynBmp_dlgSelect_isCli_myDb,  &commonParam,  idc_hWnd  );


errLabel:

	return  iRet;
}


//
int  tmpHandler_enumTalkingFriend_bUsed(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int		iErr	=	-1;
	int		iTaskId	=	(  int  )p0;
	//  BOOL  *  pbUsed  =  (  BOOL  *  )p1;
	MIS_MSG_TALKINGFRIEND_QMC  *  pFriend  =  (  MIS_MSG_TALKINGFRIEND_QMC  *  )p2;

	if  (  !isTalkerShadowMgr(  pFriend->addr  )  )  {
		iErr  =  0;  goto  errLabel;
	}

	QY_WMBUF_COMM  wmBuf;		
	memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );						
	wmBuf.uiType  =  CONST_qyWmParam_chkTask;
	wmBuf.u.chkTask.iTaskId  =  iTaskId;

	SendMessage(  pFriend->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
	if  (  !wmBuf.u.chkTask.bChked  )  goto  errLabel;
	
	if  (  !wmBuf.u.chkTask.bNotExists  )  {
		iErr  =  1;  goto  errLabel;
	}

	iErr  =  0;
errLabel:


	return  iErr;
}

BOOL  tmpHandler_bNotUsed_imTask(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	BOOL			bRet	=	FALSE;
	MIS_CNT		*	pMisCnt	=	(  MIS_CNT  *  )p0;
	//  p1
	IM_TASK_RCD  *  pRcd  =  (  IM_TASK_RCD  *  )p2;

	MC_VAR_isCli  *	pProcInfo	=	QY_GET_procInfo_isCli(  );
	BOOL			bUsed	=	FALSE;
	

	if  (  qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_enumTalkingFriend_bUsed,  (  void  *  )pRcd->id,  0  )  )  {
		//  bUsed  =  TRUE;
		goto  errLabel;
	}

	//
	if  (  IsWindow(  pProcInfo->hWnd_shareDynBmps  )  )  {
		QY_WMBUF_COMM  wmBuf;		

		memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );						
		wmBuf.uiType  =  CONST_qyWmParam_chkTask;
		wmBuf.u.chkTask.iTaskId  =  pRcd->id;
		
		SendMessage(  pProcInfo->hWnd_shareDynBmps,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
		if  (  !wmBuf.u.chkTask.bChked  )  goto  errLabel;
		if  (  wmBuf.u.chkTask.bChked  )  goto  errLabel;
	}

	//
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHandler_bNotUsed_imTask: task %d not used, will be removed"  ),  pRcd->id  );

	bRet  =  TRUE;

errLabel:
	return  bRet;
}

BOOL  tmpHandler_bTooManyImMsg(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	BOOL	bRet	=	FALSE;
	//  p0
	int  *  piCnt		=	(  int  *  )p1;
	IM_MSG_RCD	*	pRcd  =  (  IM_MSG_RCD  *  )p2;

	if  (  (  *piCnt  )  >  0  )  {
		(  *piCnt    )  --  ;
		bRet  =  TRUE;  goto  errLabel;
	}

errLabel:

	return  bRet;
}

 //  2013/03/07
 __declspec(  dllexport  )  int  qisChkDb_gui_myDb(  )			
{
	 int			iErr	=	-1;
	 QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;

	 void		*	pDbParam		=	NULL;	
	 int			iDbType								=	pQyMc->cfg.db.iDbType;
	 
	 //
	 if  (  iDbType  !=  CONST_dbType_myDb  )  return  -1;

	 //
	 DWORD  dwTickCnt  =  GetTickCount(  );
	 
	 //
	 CQnmDb							db;
	
	 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
	 pDbParam  =  db.m_pDbMem->pDb;


	 CMyDb  *  pDb  =  (  CMyDb  *  )pDbParam;
	 GENERIC_Q	*	pQ;
	 MIS_CNT	*	pMisCnt	=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 if  (  !pMisCnt  )  goto  errLabel;

#ifdef  __DEBUG__
		//traceLog(  _T(  "qisChkDb_gui_myDb called"  )  );
#endif

	 //
	 BOOL  bNeedChk  =  FALSE;
	 //
	 pQ  =  pDb->m_var.pQ_qyImTaskTab;		
	 if  (  isQFull(  pQ  )  )  {
		 bNeedChk  =  TRUE;
	 }
	 //
	 if  (  dwTickCnt  -  pProcInfo->status.dwTickCnt_chkDb  >  5  *  60  *  1000  )  {
		 bNeedChk  =  TRUE;
	 }
	 //
	 if  (  !bNeedChk  )  {
		 return  0;		 
	 }


#ifdef  __DEBUG__
		traceLog(  _T(  "qisChkDb_gui_myDb, start to chk"  )  );
#endif

	 //
	 pProcInfo->status.dwTickCnt_chkDb  =  dwTickCnt;


 	#ifdef  __DEBUG__
			_ASSERT(  pProcInfo->processQ_media.m_var.dwThreadId_gui  ==  GetCurrentThreadId(  )  );
	#endif
			
	 
	 pQ  =  pDb->m_var.pQ_qyImTaskTab;
	 if  (  pQ->uiQNodes  >  pQ->cfg.uiMaxQNodes  /  2  ||  pQ->uiQNodes  >  200  )  {
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qisChkDb_gui_myDb, start to chk and clean imTaskTab, qNodes %d"  ),  pQ->uiQNodes  );

		 qRemoveMsg(  pQ,  tmpHandler_bNotUsed_imTask,  pMisCnt,  0  );

		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qisChkDb_gui_myDb, chking imTaskTab ends, qNodes %d"  ),  pQ->uiQNodes  );
	 }

	 //
	 pQ  =  pDb->m_var.pQ_qyImMsgTab;
	 int  iInterval  =  min(  pQ->cfg.uiMaxQNodes  /  10,  100  );
	 if  (  isQWarning(  pQ,  iInterval  )  )  {
		 int	cnt  =  iInterval;
		 if  (  cnt  <=  0  )  goto  errLabel;

		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qisChkDb_gui_myDb, start to chk and clean imMsgTab, qNodes %d"  ),  pQ->uiQNodes  );

		 qRemoveMsg(  pQ,  tmpHandler_bTooManyImMsg,  0,  &cnt  );

		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qisChkDb_gui_myDb, start to chk imMsgTab, qNodes %d"  ),  pQ->uiQNodes  );
	 }
	 
errLabel:

	 return  iErr;
 }

