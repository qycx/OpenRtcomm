

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
#include	"funcsforIsCliHelp.h"
#include	"ctxMcThread.h"



 int  selectNextImObjRule_mcProcResp_refreshImObjRulesReq_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  MIS_MSG_INPUT  *  pMsgInput,  void  *  pCtxParam,  QY_MESSENGER_ID	  *  pIdInfo_related  )
{
	 int								iErr													=	-1;
	 MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_SERVICEGUI_INFO  *  pSci																=	(  QY_SERVICEGUI_INFO  *  )pSciParam;
	 MIS_CNT  *  pMisCnt																		=	(  MIS_CNT  *  )pMisCntParam;
	 CTX_MC_scheduler  *  pCtx																	=	(  CTX_MC_scheduler  *  )pCtxParam;

	 TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]						=	_T(  ""  );
	 char								timeBuf[128]											=	"";
	 char								idStr[CONST_qyMessengerIdStrLen  +  1];

	 TCHAR								tBuf[255  +  1]											=	_T(  ""  );
	 //
	 int								len;
	 //
	 int								tmpiRet;
	 //  
	 CDBVariant							varVals[1];
	 QY_MESSENGER_ID					idInfo_tmp;


			  idInfo2Str(  pIdInfo_related,  idStr,  mycountof(  idStr  )  );			
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select idStr_related from %s where idStr_related>'%s' order by idStr_related"  ),  CONST_tabName_qyImObjRuleTab,  CQyString(  idStr  )  );
			  if  (  !bQyGetRcdBySql(  pSubThreadInfo->pDb,  sqlBuf,  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;
			  MACRO_sqlStr(  varVals[0],  tBuf,  mycountof(  tBuf  )  );  myTChar2Utf8(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &idInfo_tmp  );
			  if  (  idInfo_tmp.ui64Id  ==  pIdInfo_related->ui64Id  )  {
				  //  err
				  goto  errLabel;
			  }
			  pIdInfo_related->ui64Id  =  idInfo_tmp.ui64Id;

	 iErr  =  0;

errLabel:
	 return  iErr;
}

 int  tmpHandler_fillImObjs_messenger(  HWND  hDlg,  void  *  pVar,  void  *  pVarValsParam  )
{
	DLG_objs_var	&	m_var	=	*(  DLG_objs_var  *  )pVar;
	CDBVariant		*	varVals	=	(  CDBVariant  *  )pVarValsParam;

	QY_MC					*	pQyMc	=	QY_GET_GBUF(  );
	QY_DMITEM				*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
	MY_REG_DESC					desc;
	QY_MESSENGER_REGINFO		regInfo;
	memset(  &regInfo,  0,  sizeof(  regInfo  )  );

	QY_MESSENGER_REGINFO	*	pRegInfo	=	&regInfo;
	QY_DMITEM  *  pFieldIdTable	=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  );
	MACRO_setFieldIdInRegInfo(  pRegInfo[0]  );
	MACRO_setPtrs(  pFieldIdTable,  pRegInfo[0],  pRegInfo->fields  );

	regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  );


	int		index;
	TCHAR	tBuf[256];
	char	idStr[CONST_qyMessengerIdStrLen  +  1];
	unsigned  int	uiType;

	index  =  0;	//  idStr
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &pRegInfo->addr.idInfo  );
	index  ++  ;	//  uiType
	MACRO_sqlLong(  varVals[index],  uiType  );
	index  ++  ;
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  safeTcsnCpy(  tBuf,  desc.pZb,  mycountof(  regInfo.u.cols[0]  )  );
	index  ++  ;
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  safeTcsnCpy(  tBuf,  desc.pBb,  mycountof(  regInfo.u.cols[0]  )  );
	index  ++  ;
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  safeTcsnCpy(  tBuf,  desc.pDw,  mycountof(  regInfo.u.cols[0]  )  );
	index  ++  ;
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  safeTcsnCpy(  tBuf,  desc.pBm,  mycountof(  regInfo.u.cols[0]  )  );
	index  ++  ;
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  safeTcsnCpy(  tBuf,  desc.pSyr,  mycountof(  regInfo.u.cols[0]  )  );


	HWND	hCtl	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  );
	//  TCHAR	tBuf[256];
	int		tmpiRet;
	TCHAR	talkerDesc[128];
	regInfo2Desc(  0,  &regInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  ); 

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s"  ),  regInfo.addr.idInfo.ui64Id,  talkerDesc  );
	tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d,  %s, idInfo is %I64u, talkerDesc %s"  ),  m_var.usItemCount,  qyGetDesByType1(  pTable,  uiType  ),  regInfo.addr.idInfo.ui64Id,  talkerDesc  );
	OutputDebugString(  tBuf  );
	OutputDebugString(  _T(  "\n"  )  );


	m_var.usItemCount  ++;


	return  0;
}
  int  tmpHandler_fillImObjs_imGrp(  HWND  hDlg,  void  *  pVar,  void  *  pVarValsParam  )
{
	DLG_objs_var	&	m_var	=	*(  DLG_objs_var  *  )pVar;
	CDBVariant		*	varVals	=	(  CDBVariant  *  )pVarValsParam;

	QY_MC					*	pQyMc	=	QY_GET_GBUF(  );
	QY_DMITEM				*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
	IM_GRP_INFO					grpInfo;
	memset(  &grpInfo,  0,  sizeof(  grpInfo  )  );


	int		index;
	TCHAR	tBuf[256];
	char	idStr[CONST_qyMessengerIdStrLen  +  1];
	unsigned  int	uiType;

	index  =  0;	//  idStr
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &grpInfo.idInfo  );
	index  ++  ;	//  uiType
	MACRO_sqlLong(  varVals[index],  uiType  );
	index  ++  ;	//  name
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  safeTcsnCpy(  tBuf,  grpInfo.name,  mycountof(  grpInfo.name  )  );
	index  ++  ;	//  subtype
	MACRO_sqlLong(  varVals[index],  grpInfo.usSubtype  );


	HWND	hCtl	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  );
	//  TCHAR	tBuf[256];
	int		tmpiRet;


	//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s"  ),  grpInfo.idInfo.ui64Id,  grpInfo.name  );
	if  (  grpInfo.usSubtype  ==  CONST_imGrpSubtype_msg  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s(%s)"  ),  grpInfo.idInfo.ui64Id,  grpInfo.name, getResStr(  0,  &pQyMc->cusRes,  CONST_resId_imGrps_msg  )  );
	}
	else  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s(%s)"  ),  grpInfo.idInfo.ui64Id,  grpInfo.name, getResStr(  0,  &pQyMc->cusRes,  CONST_resId_imGrps_av  )  );
	}
	tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d,  %s, idInfo is %I64u, talkerDesc %s"  ),  m_var.usItemCount,  qyGetDesByType1(  pTable,  uiType  ),  grpInfo.idInfo.ui64Id,  grpInfo.name  );
	OutputDebugString(  tBuf  );
	OutputDebugString(  _T(  "\n"  )  );


	m_var.usItemCount  ++;


	return  0;
}
 void  fillImObjs_msgr_odbc(  HWND  hDlg,  void  *  pVar,  void  *  pDb  )
{
	TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	CDBVariant		varVals[10];

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select A.idStr,A.uiType,B.col11,B.col12,B.col2,B.col3,B.col4 from (qyImObjTab as A  left join qyImObjRegInfoTab as B on (A.misServName=B.misServName and A.idStr=B.idStr)) "   )  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where A.uiType not in(%d)"  ),  sqlBuf,  CONST_objType_imGrp  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by A.idStr"  ),  sqlBuf  );

	enumSqlQuery(  pDb,  sqlBuf,  (  PF_commonHandler  )tmpHandler_fillImObjs_messenger,  hDlg,  pVar,  varVals,  mycountof(  varVals  ),  NULL  );	

	return;
}

   void  fillImObjs_grp_odbc(  HWND  hDlg,  void  *  pVar,  void  *  pDb  )
{
	TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	CDBVariant		varVals[10];

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImObjTab.idStr,qyImObjTab.uiType,qyImGrpInfoTab.name,qyImGrpInfoTab.subtype from (qyImObjTab left join qyImGrpInfoTab on(qyImObjTab.misServName=qyImGrpInfoTab.misServName and qyImObjTab.idStr=qyImGrpInfoTab.idStr ) )"  )  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where qyImObjTab.uiType in(%d)"  ),  sqlBuf,  CONST_objType_imGrp  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by qyImObjTab.idStr"  ),  sqlBuf  );

	enumSqlQuery(  pDb,  sqlBuf,  (  PF_commonHandler  )tmpHandler_fillImObjs_imGrp,  hDlg,  pVar,  varVals,  mycountof(  varVals  ),  NULL  );	

	return;
}

 //  2013/02/05
 int  tmpHandler_loadTasks(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int					iErr		=	-1;
	HWND				hDlgTalk	=	(  HWND  )p0;
	PARAM_PROC_ROW	*	pParam		=	(  PARAM_PROC_ROW  *  )p1;
	CDBVariant		*	pVarVals	=	(  CDBVariant  *  )p2;
	//
	if  (  !hDlgTalk  ||  !pParam  ||  !pVarVals  )  return  -1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pm_var		=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pm_var  )  return  -1;
	DLG_TALK_var	&	m_var		=	*pm_var;
	int					i;
	IM_TASK_RCD			rcd;
	TCHAR				tBuf[256]	=	_T(  ""  );
	char				buf[256]	=	"";
	CQyMalloc			mallocObj;


	memset(  &rcd,  0,  sizeof(  rcd  )  );
	i  =  0;	MACRO_sqlLong(  pVarVals[i],  rcd.id  );
	i  ++  ;	MACRO_sqlLong(  pVarVals[i],  rcd.uiType  );	
	i  ++  ;	MACRO_sqlLong(  pVarVals[i],  rcd.uiMode  );	
	i  ++  ;	MACRO_sqlStr(  pVarVals[i],  rcd.subTypeStr,  mycountof(  rcd.subTypeStr  )  );
	i  ++  ;	MACRO_sqlStr(  pVarVals[i],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  rcd.subject,  tBuf,  mycountof(  rcd.subject  )  );
	i  ++  ;	MACRO_sqlStr(  pVarVals[i],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  rcd.content,  tBuf,  mycountof(  rcd.content  )  );
	i  ++  ;	MACRO_sqlStr(  pVarVals[i],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  rcd.tEndTime  =  gettTimeByBuf(  buf  );
	i  ++  ;	MACRO_sqlStr(  pVarVals[i],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &rcd.idInfo_send  );
	i  ++  ;	MACRO_sqlStr(  pVarVals[i],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  rcd.tSendTime  =  gettTimeByBuf(  buf  );
	i  ++  ;	MACRO_sqlLong(  pVarVals[i],  rcd.uiTranNo  );
	i  ++  ;	MACRO_sqlLong(  pVarVals[i],  rcd.uiSerialNo  );
	i  ++  ;	MACRO_sqlLong(  pVarVals[i],  rcd.uiContentType  );
	i  ++  ;	MACRO_sqlStr(  pVarVals[i],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &rcd.idInfo_recv  );
	i  ++  ;	MACRO_sqlStr(  pVarVals[i],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  rcd.tRecvTime  =  gettTimeByBuf(  buf  );
	i  ++  ;	MACRO_sqlLong(  pVarVals[i],  rcd.iStatus  );
	i  ++  ;

	//  
	MIS_MSG_TASK	*	pMsg;
	if  (  !(  pMsg  =  (  MIS_MSG_TASK  *  )mallocObj.mallocf(  sizeof(  MIS_MSG_TASK  )  )  )  )  goto  errLabel;
	//
	if  (  !taskRcd2Msg(  m_var.pMisCnt,  &rcd,  pMsg  )  )  {
		traceLogA(  "taskRcd2Msg failed, skipped"  );
		iErr  =  0;  goto  errLabel;
	}	

	if  (  !bTaskAlive(  rcd.iStatus  )  )  {
		iErr  =  0;  goto  errLabel;
	}

	switch  (  rcd.uiContentType  )  {
			case  CONST_imCommType_transferAvInfo:  
			case  CONST_imCommType_transferGpsInfo:
				{

				  #ifdef  __DEBUG__
						  traceLogA(  "tmpHandler_displayTasks: skiped, rcd.uiContentType is %d,rcd.uiType %d",  rcd.uiContentType,  rcd.uiType  );
				  #endif

				  iErr  =  0;  goto  errLabel;
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
		iErr  =  1;  goto  errLabel;
	}

	iErr  =  0;

errLabel:
	
	return  iErr;
}

 
 int  selectImTask_dlgTalk_loadTasks_odbc(  HWND  hDlgTalk,  void  *  pTmpParam,  void  *  pDbParam  )
{
	 int				iRet  =  -1;
	 QY_MC			 *	pQyMc									=   QY_GET_GBUF(  );

	 PARAM_PROC_ROW  *  pParam									=   (  PARAM_PROC_ROW  *  )pTmpParam;
	 void			 *	pDb										=	(  void  *  )pDbParam;
	 
	 TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]		=  _T(  ""  );
	 char				idStr[CONST_qyMessengerIdStrLen + 1]	=  "";
	 char				idStr_me[CONST_qyMessengerIdStrLen + 1]	=  "";
	 int				tmpiRet									=  -1;
	 CDBVariant			varVals[15];

	 CHelp_getDlgTalkVar	help_getDlgTalkVar;
	 DLG_TALK_var  *  pm_var  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	 if  (  !pm_var  )  return  -1;
	 DLG_TALK_var  &  m_var  =   *pm_var;

	 idInfo2Str(  &m_var.addr.idInfo,  idStr,  mycountof(  idStr  )  );
	 idInfo2Str(  &m_var.pMisCnt->idInfo,  idStr_me, mycountof(  idStr_me  )  );

	//
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,uiType,uiMode,subTypeStr,subject,content0,tEndTime,idStr_send,tSendTime,uiTranNo,uiSerialNo,uiContentType,idStr_recv,tRecvTime,iStatus from %s where iStatus<>%d "  ),  CONST_tabName_qyImTaskTab,  CONST_imTaskStatus_null  );	
	if  (  m_var.addr.uiObjType  ==  CONST_objType_imGrp  )  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and (idStr_send='%s' or idStr_recv='%s')"  ), sqlBuf,  CQyString(  idStr  ),  CQyString(  idStr  )  );	    
	else  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and ((idStr_send='%s' and idStr_recv='%s') or (idStr_send='%s' and idStr_recv='%s'))"  ), sqlBuf,  CQyString(  idStr  ),  CQyString(  idStr_me  ),  CQyString(  idStr_me  ),  CQyString(  idStr  )  );	    	
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and uiType not in(%d,%d,%d)"  ),  sqlBuf,  CONST_imTaskType_shareDynBmp,  CONST_imTaskType_viewDynBmp,  CONST_imTaskType_viewGps  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by tRecvTime "  ),  sqlBuf  );
	tmpiRet  =  enumSqlQuery(  pDb,  sqlBuf,  tmpHandler_loadTasks,  hDlgTalk,  &pParam,  varVals,  mycountof(  varVals  ),  NULL  );

	 iRet =  0;
errLabel:
	 return  iRet;
}

 BOOL  bSelectImTask_storeTaskInDb_odbc(  void  *  pDb,  int  iDbType,  void  *  pMisCntParam,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  )
{
	BOOL					bRet											=	FALSE;
	QY_MC				*	pQyMc											=	QY_GET_GBUF(  );
	MIS_CNT  *  pMisCnt =	(  MIS_CNT  *  )pMisCntParam;
	//
	TCHAR					sqlBuf[CONST_maxSqlBufLen  +  1];
	char					idStr_send[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char					idStr_recv[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char					sendTime[CONST_qyTimeLen  +  1]					=	"";
#if  0
	char					recvTime[CONST_qyTimeLen  + 1]					=	"";
	char					tStartTime_serv[CONST_qyTimeLen  +  1]			=	"";
	char					endTime[CONST_qyTimeLen  +  1]					=	"";
	char					firstTime[CONST_qyTimeLen  +  1]				=	"";
	char					lastTime[CONST_qyTimeLen  +  1]					=	"";
	char					lastModifiedTime[CONST_qyTimeLen  +  1]			=	"";
	char					lastModifiedTime_req[CONST_qyTimeLen  +  1]		=	"";
	CQySyncObj				syncObj;
#endif
	CDBVariant				varVals[5];
	TCHAR				*	pTabName										=	bInHis  ?  CONST_tabName_qyImTaskHisTab  :  CONST_tabName_qyImTaskTab;
	

	if  (  !idInfo2Str(  &pRcd->idInfo_send,  idStr_send,  mycountof(  idStr_send  )  )  )  goto  errLabel;
	if  (  !idInfo2Str(  &pRcd->idInfo_recv,  idStr_recv,  mycountof(  idStr_recv  )  )  )  goto  errLabel;
	if  (  pRcd->tSendTime  )  getTimeStr(  pRcd->tSendTime,  sendTime,  mycountof(  sendTime  )  );
#if  0
	if  (  pRcd->tRecvTime  )  getTimeStr(  pRcd->tRecvTime,  recvTime,  mycountof(  recvTime  )  );
	if  (  pRcd->tEndTime  )  getTimeStr(  pRcd->tEndTime,  endTime,  mycountof(  endTime  )  );
	if  (  pRcd->tLastModifiedTime  )  getTimeStr(  pRcd->tLastModifiedTime,  lastModifiedTime,  mycountof(  lastModifiedTime  )  );
#endif


	//  +misServName;+idStr_send;+tSendTime;+uiTranNo;+idStr_recv
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,iStatus from %s where misServName=%s and idStr_send='%s' and tSendTime='%s' and uiTranNo=%d and uiSerialNo=%d and idStr_recv='%s'"  ),  
													pTabName,
													getDbValStr(  iDbType,  CONST_iDataType_misServName,  pRcd->misServName  ),  
													CQyString(  idStr_send  ),
													CQyString(  sendTime  ),
													pRcd->uiTranNo,
													pRcd->uiSerialNo,
													CQyString(  idStr_recv  )  );

	if  (  !bQyGetRcdBySql(  pDb,  sqlBuf,  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;
		
	traceLogA(  "storeTaskInDb: "  );
	
	MACRO_sqlLong(  varVals[0],  pRcd->id  );		//  
	MACRO_sqlLong(  varVals[1],  pRcd->iStatus  );

	bRet  =  TRUE;
errLabel:

	return  bRet;
}

 int  insertImTask_storeTaskInDb_odbc(  void  *  pDb,  int  iDbType,  void  *  pMisCntParam,  int  iTaskId_suggested,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  )
{
	int						iErr											=	-1;
	QY_MC				*	pQyMc											=	QY_GET_GBUF(  );
	MIS_CNT  *  pMisCnt =	(  MIS_CNT  *  )pMisCntParam;
	//
	TCHAR					sqlBuf[CONST_maxSqlBufLen  +  1];
	char					idStr_send[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char					idStr_recv[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char					sendTime[CONST_qyTimeLen  +  1]					=	"";
	//
	char					recvTime[CONST_qyTimeLen  + 1]					=	"";
	char					tStartTime_serv[CONST_qyTimeLen  +  1]			=	"";
	char					endTime[CONST_qyTimeLen  +  1]					=	"";
	char					firstTime[CONST_qyTimeLen  +  1]				=	"";
	char					lastTime[CONST_qyTimeLen  +  1]					=	"";
	char					lastModifiedTime[CONST_qyTimeLen  +  1]			=	"";
	char					lastModifiedTime_req[CONST_qyTimeLen  +  1]		=	"";

	CDBVariant				varVals[5];
	TCHAR				*	pTabName										=	bInHis  ?  CONST_tabName_qyImTaskHisTab  :  CONST_tabName_qyImTaskTab;
	
	if  (  !idInfo2Str(  &pRcd->idInfo_send,  idStr_send,  mycountof(  idStr_send  )  )  )  goto  errLabel;
	if  (  !idInfo2Str(  &pRcd->idInfo_recv,  idStr_recv,  mycountof(  idStr_recv  )  )  )  goto  errLabel;
	if  (  pRcd->tSendTime  )  getTimeStr(  pRcd->tSendTime,  sendTime,  mycountof(  sendTime  )  );
	if  (  pRcd->tRecvTime  )  getTimeStr(  pRcd->tRecvTime,  recvTime,  mycountof(  recvTime  )  );
	if  (  pRcd->tEndTime  )  getTimeStr(  pRcd->tEndTime,  endTime,  mycountof(  endTime  )  );
	if  (  pRcd->tLastModifiedTime  )  getTimeStr(  pRcd->tLastModifiedTime,  lastModifiedTime,  mycountof(  lastModifiedTime  )  );

	getTimeStr(  pRcd->tStartTime_serv,  tStartTime_serv,  mycountof(  tStartTime_serv  )  );
	getTimeStr(  pRcd->firstTime,  firstTime,  mycountof(  firstTime  )  );
	getTimeStr(  pRcd->lastTime,  lastTime,  mycountof(  lastTime  )  );


	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr_send,senderDesc,tSendTime,uiTranNo,uiSeqNo,uiContentType,tStartTime_serv,uiSerialNo,idStr_recv,receiverDesc,iRole,tRecvTime,usRespCode,ibReply,uiType,uiMode,subTypeStr,subject,content0,ibNeedReply,tEndTime,firstTime,lastTime,iStatus,tLastModifiedTime,propStr0)"  )
															_T(  " values(%s,        '%s',        %s,     '%s',     %d,        %d,     %d,          '%s',         %d,       '%s',       %s,        %d,     '%s',   %d,        %d,       %d,   %d,     %s,          %s,     %s,    %d,          '%s',   '%s',     '%s',     %d,     '%s',             '%s')"  ),
													pTabName,
													getDbValStr(  iDbType,  CONST_iDataType_misServName,  pRcd->misServName  ),  
													CQyString(  idStr_send  ),
													getDbValStr(  iDbType,  CONST_iDataType_desc,  pRcd->senderDesc  ),
													CQyString(  sendTime  ),
													pRcd->uiTranNo,
													(  int  )pRcd->usSeqNo,
													pRcd->uiContentType,
													CQyString(  tStartTime_serv  ),
													pRcd->uiSerialNo,
													CQyString(  idStr_recv  ),
													getDbValStr(  iDbType,  CONST_iDataType_desc,  pRcd->receiverDesc  ),
													pRcd->iRole,
													CQyString(  recvTime  ),
													pRcd->usRespCode,
													pRcd->ibReply,
													pRcd->uiType,
													pRcd->uiMode,
													getDbValStr(  iDbType,  CONST_iDataType_subTypeStr,  pRcd->subTypeStr  ),
													getDbValStr(  iDbType,  CONST_iDataType_subject,  pRcd->subject  ),
													getDbValStr(  iDbType,  CONST_iDataType_content,  pRcd->content  ),
													pRcd->ibNeedReply,
													CQyString(  endTime  ),
													CQyString(  firstTime  ),  
													CQyString(  lastTime  ),
													pRcd->iStatus,
													CQyString(  lastModifiedTime  ),
													CQyString(  pRcd->propStrs[0]  )  );
												
													
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;
}

 //  2013/02/11
 int  tmpHandler_enumMisTasks(  void  *  p0Param,  void  *  p1Param,  void  *  pVarValsParam  )
{
	int						iErr			=	-1;
	COMMON_PARAM		*	pCommonParam	=	(  COMMON_PARAM  *  )p0Param;
	PF_commonHandler		pf				=	(  PF_commonHandler  )pCommonParam->p0;
	void				*	p0				=	pCommonParam->p1;
	void				*	p1				=	pCommonParam->p2;
	IM_TASK_RCD			*	pRcd			=	(  IM_TASK_RCD  *  )p1Param;
	CDBVariant			*	varVals			=	(  CDBVariant  *  )pVarValsParam;
	//
	int						index;
	TCHAR					tBuf[256];
	 char					buf[256];
	 long					lVal;
	 int					i;


	if  (  pRcd  )  {
		 memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

         index  =  0;	MACRO_sqlLong(  varVals[index],  pRcd->id  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_send  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->senderDesc,  mycountof(  pRcd->senderDesc  )  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tSendTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->uiTranNo  );
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->uiContentType  );
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->uiSerialNo  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_recv  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->receiverDesc,  mycountof(  pRcd->receiverDesc  )  );
		 //
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tRecvTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  lVal  );  pRcd->usRespCode  =  (  unsigned  short  )lVal;

		 index  ++  ;	MACRO_sqlLong(  varVals[index],  lVal  );  pRcd->ibReply  =  lVal;
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  lVal  );  pRcd->uiType  =  lVal;
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  lVal  );  pRcd->uiMode  =  lVal;
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->subTypeStr,  mycountof(  pRcd->subTypeStr  )  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->subject,  mycountof(  pRcd->subject  )  );  
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->content,  mycountof(  pRcd->content  )  );  
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->txtContent,  mycountof(  pRcd->txtContent  )  );  
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  lVal  );  pRcd->ibNeedReply  =  lVal;
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tEndTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->issuer,  mycountof(  pRcd->issuer  )  );
		 index  ++	;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tIssueTime  =  gettTimeByBuf(  buf  );
		 //
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tStartTime_req  =  gettTimeByBuf(  buf  );
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->uiTranNo_req  );
		 //
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  lVal  );  pRcd->iStatus  =  lVal;
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeByBuf(  buf  );
		 //
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_auditor  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_replyTo  );
		 //
		 for  (  i  =  0;  i  <  10;  i  ++  )  {
			  index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->iProps[i]  );
		 }
		 for  (  i  =  0;  i  <  10;  i  ++  )  {
			  index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pRcd->propStrs[i],  tBuf,  mycountof(  pRcd->propStrs[i]  )  );  
		 }

		 if  (  pf  )  pf(  p0,  p1,  pRcd  );

	 }
	
	iErr  =  0;

//  errLabel:

	return  iErr;
}

 __declspec(  dllexport  )  int  enumImTasks(  void  *  pDb,  int  iDbType,  BOOL  bHisTab,  LPCTSTR  misServName,  LPCTSTR  whereClause,  PF_commonHandler  pf,  void  *  p0,  void  *  p1,  unsigned  int  *puiRcdCnt,  IM_TASK_RCD  *  pTaskRcd  )
{
	int					iErr								=	-1;
	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	CDBVariant			varVals[50];
	COMMON_PARAM		commonParam;
	TCHAR			*	pTabName							=	bHisTab  ?  CONST_tabName_qyImTaskHisTab  :  CONST_tabName_qyImTaskTab;

	if  (  !whereClause  )  whereClause  =  CQyString(  "1=1"  );

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,misServName,idStr_send,senderDesc,tSendTime,uiTranNo,uiContentType,uiSerialNo,idStr_recv,receiverDesc"  )
													_T(  ",tRecvTime,usRespCode,ibReply,uiType,uiMode,subTypeStr,subject,content0,txtContent0,ibNeedReply,tEndTime,issuer,tIssueTime"  )
													_T(  ",tStartTime_req,uiTranNo_req"  )
													_T(  ",iStatus,tLastModifiedTime"  )
													_T(  ",idStr_auditor,idStr_replyTo"  )
													_T(  ",iProp0,iProp1,iProp2,iProp3,iProp4,iProp5,iProp6,iProp7,iProp8,iProp9"  )
													_T(  ",propStr0,propStr1,propStr2,propStr3,propStr4,propStr5,propStr6,propStr7,propStr8,propStr9"  )
													_T(  " from %s where %s"  ),  pTabName,  whereClause  );

	MACRO_makeCommonParam3(  pf,  p0,  p1,  commonParam  );
	if  (  enumSqlQuery(  pDb,  sqlBuf,  tmpHandler_enumMisTasks,  &commonParam,  pTaskRcd,  varVals,  mycountof(  varVals  ),  puiRcdCnt  )  )  goto  errLabel;
	
	iErr  =  0;

errLabel:
	return  iErr;
}


 int  tmpHandler_bMoveTask2His(  void  *  p0,  void  *  p1,  void  *  pTaskRcdParam  )
{
#ifdef  __WINCE__
	return  -1;
#else
	int					iErr									=	-1;
	QY_MC			*	pQyMc									=	QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	
	FUNCS_for_isCliHelp	*	pFuncs			=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	//
	COMMON_PARAM	*	pCommonParam							=	(  COMMON_PARAM  *  )p0;
	//  p1
	IM_TASK_RCD	*	pRcd									=	(  IM_TASK_RCD  *  )pTaskRcdParam;
	//
	void			*	pDb										=	pCommonParam->p0;
	int					iDbType									=	(  int  )pCommonParam->p1;
	MIS_CNT			*	pMisCnt									=	(  MIS_CNT  *  )pCommonParam->p2;
	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]		=	_T(  ""  );
	//
	CQnmDb	db;
	//
	if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
	//
#ifdef  __DEBUG__
		traceLog(  _T(  "tmpHandler_bMoveTask2His: rcd.uiType %d"  ),  pRcd->uiType  );
#endif

	switch  (  pRcd->uiType  )  {
			case  CONST_imTaskType_viewDynBmp:
			case  CONST_imTaskType_viewGps:
				  //  这里是自动产生的任务,需要过滤掉
				  iErr  =  0;  goto  errLabel;
				  break;
			default:
					break;
	}

	if  (  pFuncs->pf_storeTaskInDb(  db.m_pDbMem->pDb,  iDbType,  pMisCnt,  0,  pRcd,  TRUE  )  <  0  )  {
		traceLogA(  "tmpHandler_bMoveTask2His: storeTaskInDb failed"  );  goto  errLabel;
	}

	//  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyImTaskTab,  pRcd->id  );
	//  if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;
#endif
}

 BOOL  bMoveTask2His_odbc(  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  )
{
#ifdef  __NOTSUPPORT_DB__
	return  FALSE;
#else
	BOOL				bRet									=	FALSE;
	MIS_CNT			*	pMisCnt									=	(  MIS_CNT  *  )pMisCntParam;
	TCHAR				whereClause[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	char				timeBuf[CONST_qyTimeLen  +  1]			=	"";			
	int					i;
	IM_TASK_RCD			rcd;
	COMMON_PARAM		commonParam;
	CString				sqlStr;
	
	#ifdef  __DEBUG__
	        if  (  0  )  {
				//  myMessageBox(  _T(  "ÕâÀïÔÝÊ±ÏÈ²»ÇåÀíÀúÊ·ÈÎÎñ£¬ÎªÁËµ÷ÊÔ·½±ã¡£"  )  );
				return  TRUE;
			}
	#endif

	getCurTime(  timeBuf  );

	for  (  i  =  8;  i  <  CONST_qyTimeLen;  i  ++  )  timeBuf[i]  =  '0';

	//  ÕâÀï¶ÔÓÚÎÄ¼þ´«ËÍ£¬×ÜÊÇ¹ýÁËÒ»Ìì¶¼ÒÆµ½ÀúÊ·±íÖÐÈ¥ÁË
	_sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "tSendTime<'%s'"  ),  CQyString(  timeBuf  )  );
	_sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s and uiType not in(%d,%d)"  ),  whereClause,  CONST_imTaskType_viewDynBmp,  CONST_imTaskType_viewGps  );
	MACRO_makeCommonParam3(  pDb,  (  void  *  )iDbType,  pMisCnt,  commonParam  );
	if  (  enumImTasks(  pDb,  iDbType,  FALSE,  pMisCnt->cfg.misServName,  whereClause,  tmpHandler_bMoveTask2His,  &commonParam,  0,  0,  &rcd  )  )  goto  errLabel;

	_sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "tSendTime<'%s'"  ),  CQyString(  timeBuf  )  );
	sqlStr  =  CString(  ""  )  +  _T(  "delete from "  )  +  CONST_tabName_qyImTaskTab  + _T(  " where "  )  +  whereClause;
	if  (  !bQyExecSql(  pDb,  sqlStr  )  )  {
		traceLogA(  "Çå³ý¹ýÊ±ÈÎÎñ³ö´í"  );  goto  errLabel;
	}

	bRet  =  TRUE;

errLabel:
	return  bRet;
#endif
}

 BOOL  bClearupDeletedImObjs_isClient_odbc(  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  )
{
#ifdef  __NOTSUPPORT_DB__
		return  FALSE;
#else
	BOOL					bRet									=	FALSE;

	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	
	FUNCS_for_isCliHelp	*	pFuncs			=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMisCntParam;
	TCHAR					sqlBuf[CONST_maxSqlBufLen  +  1]		=	_T(  ""  );
	CDBVariant				varVals[2];
	TCHAR					tBuf[255  +  1];
	char					idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";
	QY_MESSENGER_ID			idInfo;
	BOOL					bClient									=	TRUE;

	//  
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from qyImGrpMemTab where iStatus=%d"  ),  CONST_qyStatus_del  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  {
		traceLogA(  "bClearupDeltedImObjs_isClient: clean qyImGrpMemTab failed."  );  	
		goto  errLabel;
	}

	for  (  ;  ;  )  {
		 //  ÏÂÃæÇå³ýÒªÉ¾³ýµÄ½Úµã
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select idstr from qyImObjTab where misServName=%s and iStatus=%d"  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  CONST_qyStatus_del  );
		if  (  !bQyGetRcdBySql(  pDb,  sqlBuf,  mycountof(  varVals  ),  varVals  )  )  break;
		MACRO_sqlStr(  varVals[0],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &idInfo  );
		if  (  pFuncs->pf_delImObj(  pDb,  iDbType,  bClient,  pMisCnt->cfg.misServName,  &idInfo  )  )  {
			traceLogA(  "bClearupDeletedImObjs_isClient: delImObj failed."  );
			goto  errLabel;
		}
	}

	//  2010/08/31
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from qyImObjRegInfoTab where idStr not in (select idStr from qyImObjTab where uiType not in (%d))"  ),  CONST_objType_imGrp  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  {
		traceLogA(  "bClearupDeltedImObjs_isClient: clean qyImObjRegInfoTab failed."  );  	
		goto  errLabel;
	}

	
	bRet  =  TRUE;
errLabel:

	traceLogA(  "bClearupDeletedImObjs_isClient %s",  bRet  ?  "ok"  :  "failed"  );

	return  bRet;
#endif
}


#if  0
 int  tmpHandler_showImGrpMems(  void  *  p0,  void  *  p1,  void  *  p2  )
{
#ifdef  __WINCE__
	    return  -1;
#else
	int							iErr				=	-1;
	HWND						hDlgTalk			=	(  HWND  )p0;
	PARAM_PROC_ROW			*	pParam				=	(  PARAM_PROC_ROW  *  )p1;
	CDBVariant				*	varVals				=	(  CDBVariant  *  )p2;
	//
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var			*	pDlgTalkVar			=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );;
	if  (  !pDlgTalkVar  )  return  -1;
	DLG_TALK_var			&	m_var				=	*pDlgTalkVar;	//  (  DLG_TALK_var	*	)getDlgTalkVar(  pDlgTalk->m_hWnd  );
	QY_MC					*	pQyMc				=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo			=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	//
	int							iRcdId				=	0;
	//
	QY_MESSENGER_REGINFO		regInfo;
	QY_MESSENGER_REGINFO	*	pRegInfo			=	&regInfo;
	TCHAR						tBuf[255  +  1]		=	_T(  ""  );
	char						buf[255  +  1]		=	"";
	int							i;
	int							index;
	HWND						hListCtrl			=	GetDlgItem(  hDlgTalk,  m_var.idcList_members  );
	if  (  !hListCtrl  )  return  -1;
	CListCtrl				*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	//  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImGrpMemTab.id,qyImGrpMemTab.misServName,qyImGrpMemTab.idStr_mem,qyImObjRegInfoTab.regTime,qyImObjRegInfoTab.auditTime,qyImObjRegInfoTab.tLastModifiedTime,qyImObjRegInfoTab.col0,qyImObjRegInfoTab.col1,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4,qyImObjRegInfoTab.col5,qyImObjRegInfoTab.col6,qyImObjRegInfoTab.col7,qyImObjRegInfoTab.col8,qyImObjRegInfoTab.col9,qyImObjRegInfoTab.col10,qyImObjRegInfoTab.col11,qyImObjRegInfoTab.col12,qyImObjRegInfoTab.col13,qyImObjRegInfoTab.col14,qyImObjRegInfoTab.col15,qyImObjRegInfoTab.col16,qyImObjRegInfoTab.col17,qyImObjRegInfoTab.col18,qyImObjRegInfoTab.col19,qyImObjRegInfoTab.col20,qyImObjRegInfoTab.col21,qyImObjRegInfoTab.col22,qyImObjRegInfoTab.col23,qyImObjRegInfoTab.col24,qyImObjRegInfoTab.col25,qyImObjRegInfoTab.col26,qyImObjRegInfoTab.col27,qyImObjRegInfoTab.col28,qyImObjRegInfoTab.col29"  )
 
	if  (  pRegInfo  )  {
		 //
		 memset(  pRegInfo,  0,  sizeof(  pRegInfo[0]  )  );
		 //
		 pRegInfo->uiType  =  CONST_imCommType_messengerRegInfo;
		 pRegInfo->iCustomId  =  qyGetCustomId(  );
		 //
		 MACRO_setFieldIdInRegInfo(  pRegInfo[0]  );
		 MACRO_setPtrs(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),pRegInfo[0],  pRegInfo->fields  );
		 //
		 index  =  0;	//  id
		 //  MACRO_sqlLong(  varVals[index],  pRegInfo->id  );
		 MACRO_sqlLong(  varVals[index],  iRcdId  );
		 index  ++ ;	MACRO_sqlStr(  varVals[index],  pRegInfo->addr.misServName,  mycountof(  pRegInfo->addr.misServName  )  );
		 index  ++ ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRegInfo->addr.idInfo  );

		 index  ++  ;	//  regTime			 
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
	 

		 MY_REG_DESC				desc;
		 TCHAR						talkerDesc[128  +  1];
		 TCHAR						displayName[64  +  1];
		 int						nImage,  nSelectedImage;
		 
		 if  (  regInfo2Desc(  0,  pRegInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  displayName,  mycountof(  displayName  )  )  )  goto  errLabel;

		 nImage  =  pQyMc->cfg.image.nImage_messenger;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedMessenger;

		 {	 //  µ±ÓÐÄÚ´æ¶ÔÁÐÊ±£¬Ó¦¸ÃÈ±Ê¡Îªoffline
			 QM_OBJQ_MEM				mem;
			 QMEM_MESSENGER_CLI		*	pQMem	=	NULL;
			 QY_MESSENGER_INFO			messengerInfo;
			 void					*	pDb		=	NULL;

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
			 
			 i  =  0;  pListCtrl->InsertItem(  pParam->nItem, displayName,  nImage  );
			 i  ++  ;  pListCtrl->SetItemText(  pParam->nItem,  i,  _ltot(  iRcdId,  displayName,  10  )  );
			 i  ++  ;  //  ²»ÐèÒª×´Ì¬Ïî
			 //
			 pListCtrl->SetItemData(  pParam->nItem,  iRcdId  );
			 //
			 pParam->nItem  ++  ;

			 //  2007/06/03 
			 QMOBJQ_PARAM_MISCLIENT		qmObjQParam;
			 //
			 memset(  &qmObjQParam,  0,  sizeof(  qmObjQParam  )  );
			 //  uiType
			 qmObjQParam.pSci  =  (  QY_SERVICEGUI_INFO  *  )pProcInfo->pSgiParam;
			 qmObjQParam.pMisCnt  =  m_var.pMisCnt;
			 qmObjQParam.pDb  =  pDb;
			 qmObjQParam.iDbType  =  pQyMc->cfg.db.iDbType;
			 qmObjQParam.iObjType  =  CONST_objType_messenger;
			 qmObjQParam.pClient  =  &messengerInfo;

			 addToDisplayedObjQ(  &m_var.displayCtx,  &qmObjQParam,  hDlgTalk,  iRcdId  );  
				 
			 if  (  postRecentFriend(  qmObjQParam.pSci,  qmObjQParam.pMisCnt,  &qmObjQParam.pClient->idInfo,  0  )  )  traceLogA(  "postRecentFriend failed"  );  

		 }	 
	}

	iErr  =  0;

errLabel:

	return  iErr;
#endif
}

BOOL  iibSelectImGrpMem_dlgTalk_OnInitDialog_odbc(  HWND  hDlgTalkParam,  void  *  pDbParam,  void  *  pParam  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL				bRet										=   FALSE;
	//  CWnd			*	pDlgTalk									=	(  CWnd  *  )pDlgTalkParam;

	QY_MC			*	pQyMc										=	QY_GET_GBUF(  );
	
	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	char				idStr_grp[CONST_qyMessengerIdStrLen  +  1]	=	"";
	CDBVariant			varVals[50];

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pDlgTalkVar									=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalkParam  );
	if  (  !pDlgTalkVar  )  goto  errLabel;
	DLG_TALK_var	&	m_var										=	*pDlgTalkVar;
	void			*	pDb											=   (  void  *  )pDbParam;
	int					tmpiRet										=	-1;

	idInfo2Str(  &m_var.addr.idInfo,  idStr_grp,  mycountof(  idStr_grp  )  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImGrpMemTab.id,qyImGrpMemTab.misServName,qyImGrpMemTab.idStr_mem,qyImObjRegInfoTab.regTime,qyImObjRegInfoTab.auditTime,qyImObjRegInfoTab.tLastModifiedTime,qyImObjRegInfoTab.col0,qyImObjRegInfoTab.col1,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4,qyImObjRegInfoTab.col5,qyImObjRegInfoTab.col6,qyImObjRegInfoTab.col7,qyImObjRegInfoTab.col8,qyImObjRegInfoTab.col9,qyImObjRegInfoTab.col10,qyImObjRegInfoTab.col11,qyImObjRegInfoTab.col12,qyImObjRegInfoTab.col13,qyImObjRegInfoTab.col14,qyImObjRegInfoTab.col15,qyImObjRegInfoTab.col16,qyImObjRegInfoTab.col17,qyImObjRegInfoTab.col18,qyImObjRegInfoTab.col19,qyImObjRegInfoTab.col20,qyImObjRegInfoTab.col21,qyImObjRegInfoTab.col22,qyImObjRegInfoTab.col23,qyImObjRegInfoTab.col24,qyImObjRegInfoTab.col25,qyImObjRegInfoTab.col26,qyImObjRegInfoTab.col27,qyImObjRegInfoTab.col28,qyImObjRegInfoTab.col29"  )
											_T(  " from qyImGrpMemTab left join qyImObjRegInfoTab on( qyImGrpMemTab.misServName=qyImObjRegInfoTab.misServName and qyImGrpMemTab.idStr_mem=qyImObjRegInfoTab.idStr) where qyImGrpMemTab.misServName=%s and qyImGrpMemTab.idStr_grp='%s'"  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.addr.misServName  ),  CQyString(  idStr_grp  )  );
	//  enumSqlQuery(  pDb->m_pDbMem->pDb,  sqlBuf,  tmpHandler_showImGrpMems,  CWnd::FromHandle(  hDlgTalk  ),  pParam,  varVals,  mycountof(  varVals  ),  NULL  );
	tmpiRet  =  enumSqlQuery(  pDb,  sqlBuf,  tmpHandler_showImGrpMems,  hDlgTalkParam,  pParam,  varVals,  mycountof(  varVals  ),  NULL  );

	bRet  =  TRUE;
errLabel:
	return  bRet;
}
#endif

//
 void  *  displayQnmElement_ts(  void * pVoid,  void  *  pQueryParam,  void  *  pQyRcdset,  int  nSubItem,  TCHAR * output,  unsigned  int  size  )
{
	 int				iErr		=	-1;
	 QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	 QY_MC_QUERY	*	pQuery		=	(  QY_MC_QUERY  *  )pQueryParam;
	 CRecordset		*	pRecordset  =	(  CRecordset  *  )pQyRcdset;
	 CString			tmpStr;
	 int				iType;
	 TCHAR			*	pStopString;
	 char				buf[1024];
	 char				tmpBuf[1024];
	 QY_DMITEM		*	pTable;

	 QY_MC_QUERY	&	query		=	*pQuery;

	 CDBVariant			varVal;
	 int				lVal;
	 TCHAR				tVal[256];

	 int	index;
	 //  for  (  index  =  0;  index  <  nFields;  index  ++  )  
	 index  =  nSubItem;
	 {

		 
		 pRecordset->GetFieldValue(  index,  varVal  );
			  

				   lVal  =  0;
				   tVal[0]  =  0;
				   output[0]  =  0;
				   switch  (  query.sqlColumns[index].iDataType  )  {
						   case  SQL_INTEGER:
							     MACRO_sqlLong(  varVal,  lVal  );
							     break;
						   case  SQL_CHAR:
							     MACRO_sqlStr(  varVal,  tVal,  mycountof(  tVal  )  );
							     break;
						   default:
								   break;						   
				   }
				   switch  (  query.columns[index].type  )  {
						   case  CONST_qyColumnDisplayType_long:  
							     _sntprintf(  output,  size,  _T(  "%d"  ),  lVal  );
								 break;
						   case  CONST_qyColumnDisplayType_uLong:		//  2005/10/04
							     _sntprintf(  output,  size,  _T(  "%u"  ),  lVal  );
								 break;
						   case  CONST_qyColumnDisplayType_bool:				   
								 tTrim(  tVal  );
								 tmpStr  =  CQyString(  tVal  );
				   				 if  (  !tmpStr.GetLength(  )  )  _sntprintf(  output,  size,  _T(  ""  )  );						
				   				 else  _sntprintf(  output, size,  _T(  "%s"  ),  _tcstol(  tmpStr.GetBuffer(  0  ),  &pStopString,  10  )  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_y  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_n  )  );			   
								 break;
						   case  CONST_qyColumnDisplayType_iBool:  {
							     int		iBool  =	lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  iBool  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_y  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_n  )  );
							     }
							     break;
						   case  CONST_qyColumnDisplayType_dwRegVal:  {
							     DWORD		dwVal  =	lVal;
								 if  (  dwVal  ==  CONST_dwRegVal_invalid  )  _sntprintf(  output,  size,  _T(  ""  )  );
								 else  _sntprintf(  output,  size,  _T(  "%d"  ),  dwVal  );
								 }
								 break;
						   case  CONST_qyColumnDisplayType_eventType:  {
							     long		eventType	=  lVal;
								 TCHAR  *  ptr			=  _T(  ""  );

								 ptr  =  qyGetDesByType1(  pQyMc->pQnmEventTypeTable0,  eventType  );
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  ptr  )  );					
							     }
							     break;
						   case  CONST_qyColumnDisplayType_time:  {
							     CQyString  eventTime;
				
								 eventTime  =  tVal;
								 if  (  eventTime  ==  CQyString(  CONST_qyNullTime  )  )  eventTime  =  CQyString(  ""  );
								 myTChar2Str(  eventTime.GetBuffer(  0  ),  buf,  sizeof(  buf  )  );
								 if  (  !qyDisplayTime(  buf,  tmpBuf,  sizeof(  tmpBuf  )  )  )  tmpBuf[0]  =  0;
								 myStr2TChar(  tmpBuf,  output,  size  ); 
								 }
								 break;
						   case  CONST_qyColumnDisplayType_lTime:  {
							     CQyString  eventTime;
				
								 eventTime  =  tVal;
								 if  (  eventTime  ==  CQyString(  CONST_qyNullTime  )  )  eventTime  =  CQyString(  ""  );
								 myTChar2Str(  eventTime.GetBuffer(  0  ),  buf,  sizeof(  buf  )  );
								 if  (  !qyDisplaylTime(  buf,  tmpBuf,  sizeof(  tmpBuf  )  )  )  tmpBuf[0]  =  0;
								 myStr2TChar(  tmpBuf,  output,  size  ); 
							     }
							     break;
						   case  CONST_qyColumnDisplayType_bOnLine:  {
							     CQyString  eventTime;
								 //
								 eventTime  =  tVal;
								 //
								 if  (  eventTime.GetLength(  )  !=  CONST_qyTimeLen  ||  eventTime  ==  CQyString(  CONST_qyNullTime  )  )  _sntprintf(  output,  size,  _T(  ""  )  );
								 else  {
									   myTChar2Str(  eventTime.GetBuffer(  0  ),  buf,  sizeof(  buf  )  );
									   _sntprintf(  output,  size,  bPcOnline(  buf  )  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_online  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_offline  )  );
								 }				   
								 }				   
								 break;
						   case  CONST_qyColumnDisplayType_ip12:  {
							     char  ipBuf[CONST_qyMaxIpLen  +  1];

								 myTChar2Str(  tVal,  buf,  sizeof(  buf  )  );
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyIp12ToStd(  buf,  ipBuf  )  ?  ipBuf  :  ""  )  );
							     }
								 break;
						   case  CONST_qyColumnDisplayType_mac:  
							     tmpStr  =  tVal;
								 tmpStr.MakeLower(  );
								 _sntprintf(  output,  size,  _T(  "%s"  ),  tmpStr  );			   
								 //  if  (  !strcmpi(  output,  CONST_qyNullMac  )  )  output[0]  =  0;	//  2005/10/10, ½«qyNullMacµÄÏÔÊ¾¸³Îª¿Õ
								 break;
						   case  CONST_qyColumnDisplayType_lwrStr:
							     tmpStr  =  tVal;
								 tmpStr.MakeLower(  );
								 _sntprintf(  output,  size,  _T(  "%s"  ),  tmpStr  );			   
								 break;
						   case  CONST_qyColumnDisplayType_uprStr:
							     tmpStr  =  tVal;
								 tmpStr.MakeUpper(  );
								 _sntprintf(  output,  size,  _T(  "%s"  ),  tmpStr  );			   
								 break;
						   case  CONST_qyColumnDisplayType_pcSp:
							     tmpStr  =  tVal;
								 tmpStr.MakeUpper(  );
								 if  (  tmpStr  ==  CQyString(  CONST_qnmNullPcSp  )  )  tmpStr  =  CQyString(  ""  );
								 _sntprintf(  output,  size,  _T(  "%s"  ),  tmpStr  );			   
								 break;
						   case  CONST_qyColumnDisplayType_rasCmd:  {
							     unsigned  char  ucRasCmd;
								 TCHAR  *  ptr  =  _T(  ""  );

								 if  (  tVal[0]  )  {
									 myTChar2Str( tVal,  buf,  sizeof(  buf  )  ); 
									 ucRasCmd  =  buf[0];
									 ptr  =  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qnmRasCmdTable  ),  ucRasCmd  );
								 }
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  ptr  )  );
								 }
								 break;
						   case  CONST_qyColumnDisplayType_devCmd:  {
							     unsigned  char  ucCmd;
								 TCHAR  *  ptr  =  _T(  ""  ); 
				   
								 if  (  tVal[0]  )  {
									 myTChar2Str( tVal,  buf,  sizeof(  buf  )  ); 
									 ucCmd  =  buf[0];
									 ptr  =  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qnmDevCmdTable0  ),  ucCmd  );
								 }
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  ptr  )  );				
								 }
								 break;	
						   case  CONST_qyColumnDisplayType_netFlowRule:  {	//  Î´Íê³É
							     unsigned  char		ucCmd;
								 TCHAR			*	ptr				=	_T(  ""  ); 
								 unsigned  int		uiWarnPercent	=	0;
				   
								 if  (  lstrlen(  tVal  )  >=  5  )  {
									 myTChar2Str( tVal,  buf,  sizeof(  buf  )  ); 
									 ucCmd  =  buf[5];
									 buf[5]  =  0;
									 ptr  =  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qnmDevCmdTable0  ),  ucCmd  );
									 uiWarnPercent  =  atol(  buf  );
									 _sntprintf(  output,  size,  _T(  "%.3f%% | %s"  ),  uiWarnPercent  /  (  float  )CONST_fakedFactor_percentOfBand,  ptr  );
									 }
								 else  
									 _sntprintf(  output,  size,  _T(  ""  )  );				
								 }
								 break;
						   case  CONST_qyColumnDisplayType_platformId:  {
							     pTable  =  CONST_qyPlatformTable;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  lVal  )  )  );
								 }
								 break;
						   case  CONST_qyColumnDisplayType_assetType:  {
							     pTable  =  CONST_assetTypeTable;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString  (  qyGetDesByType1(  pTable,  lVal  )  )  );
							     }
							     break;
						   case  CONST_qyColumnDisplayType_langId:  {
							     pTable  =  CONST_qyLangTable;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  lVal  )  )  );
								 }
								 break;
						   case  CONST_qyColumnDisplayType_jqlx:  {
							     pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_jqlxTable  );
								 iType  =  _tcstol(  tVal,  &pStopString,  10  );
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
							     }
								 break;
						   case  CONST_qyColumnDisplayType_ruleCmd:  {
							     pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable  );
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 }
								 break;
						   case  CONST_qyColumnDisplayType_adapterType:  
							     pTable  =  CONST_adapterTypeTable;
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%d %s"  ),  iType,  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 break;
						   case  CONST_qyColumnDisplayType_pcNetworkPropType:
							     pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcCommTypeTable  );
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 break;
						   case  CONST_qyColumnDisplayType_snmpBool:  {
							     pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  );
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
							     }
								 break;
						   case  CONST_qyColumnDisplayType_pcAdapterStatus:
							     pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcAdapterStatusTable  );
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 break;
						   case  CONST_qyColumnDisplayType_iRootKey:
							     pTable  =  CONST_iRootKeyTable_abbr;
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 break;
						   case  CONST_qyColumnDisplayType_regType:
							     pTable  =  CONST_regTypeTable;
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 break;
						   case  CONST_qyColumnDisplayType_pcEventLogType:
							     pTable  =  CONST_pcEventLogTypeTable;
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 break;
						   case  CONST_qyColumnDisplayType_pcEventId:
							     iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%d"  ),  iType  &  0xffff  );
								 break;
						   case  CONST_qyColumnDisplayType_pcCommType:
							     pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcCommTypeTable  );
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 break;
						   case  CONST_qyColumnDisplayType_tcpState:
							     pTable  =  CONST_tcpStateTable;
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 break;
						   case  CONST_qyColumnDisplayType_qyStatus:
							     pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyStatusTable  );
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 break;
						   case  CONST_qyColumnDisplayType_withFactor:						//  2006/05/30
							     iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%.3f"  ),  (  float  )iType  /  CONST_fakedFactor_percentOfBand  );
								 break;
						   case  CONST_qyColumnDisplayType_netShareType:
							     pTable  =  CONST_netShareTypeTable;
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 break;
						   case  CONST_qyColumnDisplayType_idStr:
							     _sntprintf(  output,  size,  _T(  "%u"  ),  _tcstol(  tVal,  &pStopString,  10  )  );
								 break;
						   case  CONST_qyColumnDisplayType_objType:				 				   
							     pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 break;
						   case  CONST_qyColumnDisplayType_imTaskType:
							     pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  );
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 break;
						   case  CONST_qyColumnDisplayType_usRunningStatus:
							     pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_usRunningStatusTable  );
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 break;
						   case  CONST_qyColumnDisplayType_ruleType:
							     pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleTypeTable  );
								 iType  =  lVal;
								 _sntprintf(  output,  size,  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );
								 break;
						   default:
							       _sntprintf(  output,  size,  _T(  "%s"  ),  tVal  );
								   unescapeTStr(  output,  size  );
								   break;


	 
			
						}

						}
		
	 iErr  =  0;

errLabel:

	
	 return  !iErr  ?  output  :  NULL;

}

__declspec(  dllexport  )  int  listObjs_dlgMsgList_odbc(  void  *  pDbParam,  void  *  pQueryParam,  HWND  hListCtrlParam,  QY_MESSENGER_ID  *  pIdInfoParam  )
{
 
	QY_MC_QUERY				*	pQuery		=	(  QY_MC_QUERY  *  )pQueryParam;
	CListCtrl				*	pListCtrl	=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrlParam  );
	if  (  !pListCtrl  )  return  -1;
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
	
	 return  0;
}

#if 0 
  int  tmpHandler_enumDynBmps_isClient(  void  *  p0,  void  *  p1,  void  *  p2  )
{
#ifdef  __WINCE__
	return  -1;
#else
	int							iErr					=		-1;
	//  p0
	CTX_MC_scheduler		*	pCtx					=		(  CTX_MC_scheduler  *  )p1;
	CDBVariant				*	pVarVals				=		(  CDBVariant  *  )p2;
	//
	int							index;
	TCHAR						tBuf[255  +  1];
	char						buf[255  +  1];
	QY_dynBmp_RCD				mem;
	//
	//  int							i;
	
	
	//  _T(  "select idStr,uiObjType,usIndex,name,cusname,iStatus from %s"  ),  CONST_tabName_qyDynBmpTab  );
	
	memset(  &mem,  0,  sizeof(  mem  )  );

	index  =  0;	MACRO_sqlLong(  pVarVals[index],  mem.id  );	//
	index  ++  ;	MACRO_sqlStr(  pVarVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &mem.idInfo  );
	index  ++  ;	MACRO_sqlLong(  pVarVals[index],  mem.uiObjType  );
	index  ++  ;	MACRO_sqlLong(  pVarVals[index],  mem.usIndex  );
	index  ++  ;	MACRO_sqlStr(  pVarVals[index],  mem.name,  mycountof(  mem.name  )  );
	index  ++  ;	MACRO_sqlStr(  pVarVals[index],  mem.cusName,  mycountof(  mem.cusName  )  );
	index  ++  ;	

	if  (  !pCtx->bDynBmpQInited  )  goto  errLabel;
	if  (  qPostMsg(  &mem,  sizeof(  mem  ),  &pCtx->dynBmpQ  )  )  goto  errLabel;

	//
	iErr  =  0;
errLabel:
	return  iErr;
#endif
}
#endif

#if  0
 __declspec(  dllexport  )  int  init_mcProcResp_retrieveDynBmps_odbc(  void  *  pDb,  void  *  pCtxParam  )
{
	 int  iRet  =  -1;
	 CTX_MC_scheduler				*   pCtx													=	(  CTX_MC_scheduler  *  )pCtxParam;	
	 QY_MC							*	pQyMc													=	QY_GET_GBUF(  );
	 int								iDbType													=	pQyMc->cfg.db.iDbType;
	 TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]						=	_T(  ""  );
	 CDBVariant							varVals[64];

#if  0
		 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,idStr,uiObjType,usIndex,name,cusname,iStatus from %s"  ),  CONST_tabName_qyDynBmpTab  );
		 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by idStr,uiObjType,usIndex"  ),  sqlBuf  );
		 //
		 if  (  enumSqlQuery(  pSubThreadInfo->pDb,  sqlBuf,  tmpHandler_enumDynBmps_isClient,  0,  pCtx,  varVals,  mycountof(  varVals  ),  NULL  )  <  0  )  goto  errLabel;
#endif

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,idStr,uiObjType,usIndex,name,cusname,iStatus from %s"  ),  CONST_tabName_qyDynBmpTab  );
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by idStr,uiObjType,usIndex"  ),  sqlBuf  );

	 //
#if  0
	 iRet  =  enumSqlQuery(  pDb,  sqlBuf,  tmpHandler_enumDynBmps_isClient,  0,  pCtx,  varVals,  mycountof(  varVals  ),  NULL  );
#endif

	 return  iRet;
}
#endif

  //  2013/02/21
 __declspec(  dllexport  )  BOOL  bStatImTasks_odbc(  void  *  pProcInfoParam,  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  )
{
#ifdef  __NOTSUPPORT_DB__
		return  FALSE;
#else
	BOOL				bRet									=	FALSE;
	
	MC_VAR_isCli	*   pProcInfo								=	(  MC_VAR_isCli  *  )pProcInfoParam;
	if  (  !pProcInfo  )  return  FALSE;

	FUNCS_for_isCliHelp			*	pFuncs													=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	
	MIS_CNT			*	pMisCnt									=	(  MIS_CNT  *  )pMisCntParam;
	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]		=	_T(  ""  );
	CDBVariant			varVals[2];
	IM_TASK_STAT		stat;


	memset(  &stat,  0,  sizeof(  stat  )  );

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(*) from %s where misServName=%s and iStatus in(%d,%d,%d,%d)"  ),  
															CONST_tabName_qyImTaskTab,
															getDbValStr(  iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  
															CONST_imTaskStatus_applyToSend,		
                                                            CONST_imTaskStatus_waitToSend,
                                                            CONST_imTaskStatus_applyToRecv,			
                                                            CONST_imTaskStatus_waitToRecv  );
	if  (  bQyGetRcdBySql(  pDb,  sqlBuf,  mycountof(  varVals  ),  varVals  )  &&  varVals[0].m_dwType  ==  DBVT_LONG  )  {
		stat.uiCnt_unprocedTasks  =  varVals[0].m_lVal;
	}
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(*) from %s where misServName=%s and iStatus in(%d,%d)"  ),  
															CONST_tabName_qyImTaskTab,
															getDbValStr(  iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  
															CONST_imTaskStatus_sending,  CONST_imTaskStatus_receiving  );
	if  (  bQyGetRcdBySql(  pDb,  sqlBuf,  mycountof(  varVals  ),  varVals  )  &&  varVals[0].m_dwType  ==  DBVT_LONG  )  {
		stat.uiCnt_processingTasks  =  varVals[0].m_lVal;
	}
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(*) from %s where misServName=%s and iStatus in(%d,%d)"  ),  
															CONST_tabName_qyImTaskTab,
															getDbValStr(  iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  
															CONST_imTaskStatus_sendBreak,  CONST_imTaskStatus_recvBreak  );
	if  (  bQyGetRcdBySql(  pDb,  sqlBuf,  mycountof(  varVals  ),  varVals  )  &&  varVals[0].m_dwType  ==  DBVT_LONG  )  {
		stat.uiCnt_processBreakTasks  =  varVals[0].m_lVal;
	}

	if  (  memcmp(  &stat,  &pMisCnt->taskStat,  sizeof(  stat  )  )  )  {
		memcpy(  &pMisCnt->taskStat,  &stat,  sizeof(  pMisCnt->taskStat  )  );
		//
		pFuncs->pf_updateMeDisplayInfo(  pProcInfo,  pMisCnt,  NULL,  NULL,  NULL  );

	}

	bRet  =  TRUE;
	return  bRet;
#endif
}

int  tmpHandler_displayMessenger(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	HWND				hCombo				=  (  HWND  )p0;
	//  p1
	CDBVariant	*		varVals				=	(  CDBVariant  *  )p2;
	//
	int					index				=	0;
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );
	TCHAR				dw[255  +  1]		=	_T(  ""  );
	TCHAR				bm[255  +  1]		=	_T(  ""  );
	TCHAR				syr[255  +  1]		=	_T(  ""  );
	char				buf[255  +  1]		=	"";
	QY_MESSENGER_ID		idInfo;
	TCHAR				displayName[255  +  1]	=	_T(  ""  );

	index  =  0;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &idInfo  );
	index  ++  ;	MACRO_sqlStr(  varVals[index],  dw,  mycountof(  dw  )  );  
	index  ++  ;	MACRO_sqlStr(  varVals[index],  bm,  mycountof(  bm  )  );  
	index  ++  ;	MACRO_sqlStr(  varVals[index],  syr,  mycountof(  syr  )  );  

	_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u - %s %s %s"  ),  idInfo.ui64Id,  dw,  bm,  syr  );
	SendMessage(  hCombo,  CB_ADDSTRING,  0,  (  LPARAM  )displayName  );

	return  0;

}

int  tmpHandler_displayImGrp(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	HWND				hCombo				=  (  HWND  )p0;
	//  p1
	CDBVariant	*		varVals				=	(  CDBVariant  *  )p2;
	//
	int					index				=	0;
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );
	char				buf[255  +  1]		=	"";
	QY_MESSENGER_ID		idInfo;
	TCHAR				displayName[255  +  1]	=	_T(  ""  );

	index  =  0;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &idInfo  );
	index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  

	_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u - %s"  ),  idInfo.ui64Id,  tBuf  );
	SendMessage(  hCombo,  CB_ADDSTRING,  0,  (  LPARAM  )displayName  );

	return  0;

}

int  tmpHandler_displayDynBmp(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	HWND				hCombo				=  (  HWND  )p0;
	//  p1
	CDBVariant	*		varVals				=	(  CDBVariant  *  )p2;
	//
	QY_MC		*		pQyMc				=	QY_GET_GBUF(  );
	int					index				=	0;
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );
	TCHAR				dw[255  +  1]		=	_T(  ""  );
	TCHAR				bm[255  +  1]		=	_T(  ""  );
	TCHAR				syr[255  +  1]		=	_T(  ""  );
	char				buf[255  +  1]		=	"";
	QY_MESSENGER_ID		idInfo;
	unsigned  int		uiObjType			=	0;
	unsigned  short		usIndex				=	0;
	TCHAR				displayName[255  +  1]	=	_T(  ""  );

	index  =  0;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &idInfo  );
	index  ++  ;	MACRO_sqlLong(  varVals[index],  uiObjType  );
	index  ++  ;	MACRO_sqlLong(  varVals[index],  usIndex  );
	index  ++  ;	MACRO_sqlStr(  varVals[index],  dw,  mycountof(  dw  )  );  
	index  ++  ;	MACRO_sqlStr(  varVals[index],  bm,  mycountof(  bm  )  );  
	index  ++  ;	MACRO_sqlStr(  varVals[index],  syr,  mycountof(  syr  )  );  

	_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u - %s %s %s, %s, %d"  ),  idInfo.ui64Id,  dw,  bm,  syr,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  uiObjType  ),  usIndex  );
	SendMessage(  hCombo,  CB_ADDSTRING,  0,  (  LPARAM  )displayName  );

	return  0;

}

__declspec(  dllexport  )  int  iSelectImGrpMem_dlgSelect_isCli_odbc(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  HWND  idc_hWnd  )
{
	int  iRet  =  -1;
	TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	TCHAR		tBuf[255  +  1]						=	_T(  ""  );
	CDBVariant		varVals[10];

	char  idStr_grp[CONST_qyMessengerIdStrLen  +  1];

#if  0
				  char  idStr_grp[CONST_qyMessengerIdStrLen  +  1];
				  idInfo2Str(  &m_var.inputU.selectImGrpMem.idInfo_grp,  idStr_grp,  mycountof(  idStr_grp  )  );
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImGrpMemTab.idStr_mem,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4 from qyImGrpMemTab left join qyImObjRegInfoTab on( qyImGrpMemTab.misServName=qyImObjRegInfoTab.misServName and qyImGrpMemTab.idStr_mem=qyImObjRegInfoTab.idStr) where qyImGrpMemTab.misServName=%s and qyImGrpMemTab.idStr_grp='%s'"  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.misServName  ),  CQyString(  idStr_grp  )  );
				  if  (  enumSqlQuery(  m_var.pObjDb->pDb,  sqlBuf,  tmpHandler_displayMessenger,  GetDlgItem(  IDC_COMBO_objList  )->m_hWnd,  0,  varVals,  mycountof(  varVals  ),  NULL  )  <  0  )  goto  errLabel;
#endif				  

	
	idInfo2Str(  pIdInfo,  idStr_grp,  mycountof(  idStr_grp  )  );

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImGrpMemTab.idStr_mem,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4 from qyImGrpMemTab left join qyImObjRegInfoTab on( qyImGrpMemTab.misServName=qyImObjRegInfoTab.misServName and qyImGrpMemTab.idStr_mem=qyImObjRegInfoTab.idStr) where qyImGrpMemTab.misServName=%s and qyImGrpMemTab.idStr_grp='%s'"  ),  misServName,  CQyString(  idStr_grp  )  );
	iRet  =  enumSqlQuery(  pDb,  sqlBuf,  tmpHandler_displayMessenger,  idc_hWnd,  0,  varVals,  sizeof(  varVals  ),  NULL  );

errLabel:
	return  iRet;
}

__declspec(  dllexport  )  int  iSelectImObj_dlgSelect_isCli_odbc(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  )
{
	int  iRet  =  -1;
	TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	TCHAR		tBuf[255  +  1]						=	_T(  ""  );
	CDBVariant		varVals[10];

#if  0
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImObjTab.idStr,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4 from qyImObjTab left join qyImObjRegInfoTab on (qyImObjTab.misServName=qyImObjRegInfoTab.misServName and qyImObjTab.idStr=qyImObjRegInfoTab.idStr) where qyImObjTab.misServName=%s and qyImObjTab.uiType in (%d) order by qyImObjTab.idStr"  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.u.selectImGrp.misServName  ),  CONST_objType_messenger  );					  
				  if  (  enumSqlQuery(  m_var.pObjDb->pDb,  sqlBuf,  tmpHandler_displayMessenger,  GetDlgItem(  IDC_COMBO_objList  )->m_hWnd,  0,  varVals,  mycountof(  varVals  ),  NULL  )  <  0  )  goto  errLabel;
#endif				  

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImObjTab.idStr,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4 from qyImObjTab left join qyImObjRegInfoTab on (qyImObjTab.misServName=qyImObjRegInfoTab.misServName and qyImObjTab.idStr=qyImObjRegInfoTab.idStr) where qyImObjTab.misServName=%s and qyImObjTab.uiType in (%d) order by qyImObjTab.idStr"  ),  misServName,  CONST_objType_messenger  );
	iRet  =  enumSqlQuery(  pDb,  sqlBuf,  tmpHandler_displayMessenger,  idc_hWnd,  0,  varVals,  sizeof(  varVals  ),  NULL  );

errLabel:
	return  iRet;
}

__declspec(  dllexport  )  int  iSelectDynBmp_dlgSelect_isCli_odbc(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  )
{
	int  iRet  =  -1;
	TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	TCHAR		tBuf[255  +  1]						=	_T(  ""  );
	CDBVariant		varVals[10];

#if  0
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyDynBmpTab.idStr,qyDynBmpTab.uiObjType,qyDynBmpTab.usIndex,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4 "  )  );
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s from qyDynBmpTab left join qyImObjRegInfoTab on (qyDynBmpTab.misServName=qyImObjRegInfoTab.misServName and qyDynBmpTab.idStr=qyImObjRegInfoTab.idStr)"  ),  sqlBuf  );
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by qyImObjRegInfoTab.col0,qyDynBmpTab.idStr,qyDynBmpTab.usIndex"  ),  sqlBuf  );
				  if  (  enumSqlQuery(  m_var.pObjDb->pDb,  sqlBuf,  tmpHandler_displayDynBmp,  GetDlgItem(  IDC_COMBO_objList  )->m_hWnd,  0,  varVals,  mycountof(  varVals  ),  NULL  )  <  0  )  goto  errLabel;
#endif				  

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyDynBmpTab.idStr,qyDynBmpTab.uiObjType,qyDynBmpTab.usIndex,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4 "  )  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s from qyDynBmpTab left join qyImObjRegInfoTab on (qyDynBmpTab.misServName=qyImObjRegInfoTab.misServName and qyDynBmpTab.idStr=qyImObjRegInfoTab.idStr)"  ),  sqlBuf  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by qyImObjRegInfoTab.col0,qyDynBmpTab.idStr,qyDynBmpTab.usIndex"  ),  sqlBuf  );

	iRet  =  enumSqlQuery(  pDb,  sqlBuf,  tmpHandler_displayDynBmp,  idc_hWnd,  0,  varVals,  sizeof(  varVals  ),  NULL  );

errLabel:
	return  iRet;
}










