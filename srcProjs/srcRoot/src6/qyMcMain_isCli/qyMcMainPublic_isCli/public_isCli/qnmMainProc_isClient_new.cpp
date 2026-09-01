
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qyWmComm.h"

#include	"myresource.h"
#include	"qyCusResTemp.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcDynBmp.h"
#include	"qmcVWall.h"
#include	"qyDynLib.h"
#include	"qmcCmdProc.h"
//
#include	"isCmdConst.h"
//
#include	"myDb.h"

#include	"myDb.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
#include	"dlgSelect_isCli_public.h"
#include	"qnmMainProc_nm.h"
#include	"qmcCommFunc_iscli.h"
#include	"objType_tmp.h"
#include	"help_getDlgTalkVar.h"
#include	"dlgtalkproc.h"

 //
 //

 //
 __declspec(  dllexport  )  int  delPcSth(  void  *  pDb,  LPCTSTR  hint,  LPCTSTR  tabName,  LPCTSTR  whereClause  );
 




 int  displayListContent_imObjs(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 int								iRet					=	-1;
	 QY_MC							*	pQyMc					=	QY_GET_GBUF( );

	 iRet  =  0;

errLabel:
	
	
	 return  iRet;		

}














/*
 QY_COLUMNINFO  CONST_realTimeImTaskViewTable[]  =
{
	{	0,	_T(  "ÐòºÅ"  ),						0,	LVCFMT_LEFT,	60,			1	},
	{	0,	_T(  "ÀàÐÍ"  ),						0,	LVCFMT_LEFT,	160,		1	},
	{	0,	_T(  "ÇëÇóID"  ),					0,	LVCFMT_LEFT,	160,		1	},
	{	0,	_T(  "ÏìÓ¦ID"  ),					0,	LVCFMT_LEFT,	160,		1	},
	{	0,	_T(  "±êÊ¶"  ),						0,	LVCFMT_LEFT,	160,		1	},
	{	0,	_T(  "×´Ì¬"  ),						0,	LVCFMT_LEFT,	160,		1	},
	{	0,	_T(  "ÆðÊ¼Ê±¼ä"  ),					0,	LVCFMT_LEFT,	160,		1	},
	{	-1,	_T(  "" ),							0,	LVCFMT_LEFT, 	120,	1  },
};
*/

/*
 int  tmpHandler_displayRealTimeTasks(  CListCtrl  *  pListCtrl,  int  *  piCnt,  MIS_MSGU  *  pMsgElem  )
{
	TCHAR		tBuf[512]							=	_T(  ""  );
	int			index;
	int			i									=	0;
	char		timeBuf[CONST_qyTimeLen  +  1]		=	"";
	char		displayBuf[255  +  1]				=	"";
	int			j;
	QY_MC	*	pQyMc								=	QY_GET_GBUF(  );

	if  (  !pListCtrl  ||  !piCnt  ||  !pMsgElem  )  return  -1;

	index  =  *piCnt;

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
	i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	

	if  (  pMsgElem->uiType  ==  CONST_misMsgType_task  )  {
		IM_CONTENTU		*	pContent		=	(  IM_CONTENTU  *  )pMsgElem->task.data.buf;

		i  ++  ;	pListCtrl->SetItemText(  index,  i,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.idInfo_taskSender.ui64Id  );
		i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.idInfo_taskReceiver.ui64Id  );
		i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
		tBuf[0]  =  0;
		switch  (  pContent->uiType  )  {
				case  CONST_imCommType_transferAvInfo:  {
					  AV_TRAN_INFO  *  pAvTran  =  &pContent->transferAvInfo.tranInfo;
					  PROC_TASK_AV  *  pTask  =  &pContent->transferAvInfo.myTask;

					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "v %d, a %d"  ),  pAvTran->video.uiTranNo_openAvDev,  pAvTran->audio.uiTranNo_openAvDev  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s( "  ),  tBuf  );
					  for  (  j  =  0;  j  <  pTask->usCntLimit_mems_from;  j  ++  )  {  
						   if  (  !pTask->pMems_from[j].idInfo.ui64Id  )  continue;
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%I64u( %d,%d ), "  ),  tBuf,  pTask->pMems_from[j].idInfo.ui64Id,  pTask->pMems_from[j].video.uiTranNo_openAvDev,  pTask->pMems_from[j].audio.uiTranNo_openAvDev  );
					  }
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s )"  ),  tBuf  );

					  }
					  break;
				case  CONST_imCommType_transferAvReplyInfo:  {
					  AV_TRAN_INFO  *  pAvTran  =  &pContent->transferAvReplyInfo.tranInfo;					  
					  PROC_TASK_AV  *  pTask  =  &pContent->transferAvReplyInfo.myTask;

					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "v %d, a %d"  ),  pAvTran->video.uiTranNo_openAvDev,  pAvTran->audio.uiTranNo_openAvDev  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s( "  ),  tBuf  );
					  for  (  j  =  0;  j  <  pTask->usCntLimit_mems_from;  j  ++  )  {  
						   if  (  !pTask->pMems_from[j].idInfo.ui64Id  )  continue;
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%I64u( %d,%d ), "  ),  tBuf,  pTask->pMems_from[j].idInfo.ui64Id,  pTask->pMems_from[j].video.uiTranNo_openAvDev,  pTask->pMems_from[j].audio.uiTranNo_openAvDev  );
					  }
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s )"  ),  tBuf  );
					  }
					  break;
				default:
						break;
		}
		i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
		//  Òª¿ªÊ¼ÃèÐ´×´Ì¬¡£
		i  ++  ;	
		//  _sntprintf(  tBuf,...

		getTimelStr(  pMsgElem->task.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
		qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
		i  ++  ;	pListCtrl->SetItemText(  index,  i,  CString(  displayBuf  )  );		

	}

	(  *piCnt  )  ++  ;

	return  0;
}
*/















//  2013/02/16
__declspec( dllexport  )  BOOL  bViewImTaskListFunc(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart,  BOOL  bHisTab  )
{
	BOOL					bRet			=	FALSE;
	//QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp			=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpImTaskListQueryStruct  );
	TCHAR				*	pTabName		=	bHisTab  ?  CONST_tabName_qyImTaskHisTab  :  CONST_tabName_qyImTaskTab;
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	bHisTab  ?  CONST_qyQueryType_imTaskHisList  :  CONST_qyQueryType_imTaskList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  pQyMc,  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from (%s as T left join qyImObjRegInfoTab as B on (T.misServName=B.misServName and T.idStr_send=B.idStr) )"  ),  pTabName  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s"  ),  CQyString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "B.idStr"  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.pfProcEvent_new  =  is_procEvent_new;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_popup_viewImTaskList_isClient  :  CONST_resId_popup_viewImTaskList_isMgr;		//  2003/12/17ÐÞ¸Ä
	tmpSel.u.query.uiDefaultCmd  =  ID_qyTalkToTaskPeer;

	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  bHisTab  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyTaskHisList  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyTaskList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	if  (  viewDlgListView_db(  pQyMc->gui.hMainWnd,  0,  &tmpSel  )  )  goto  errLabel;

	bRet  =  TRUE;

errLabel:

	return  bRet;
	
}


  //  2013/02/20
  BOOL  bViewImMsgListFunc(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet			=	FALSE;
	//QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
#if  0
	CQyMcApp			*	pApp			=	(  CQyMcApp  *  )AfxGetApp(  );
#endif
	QY_MC_SEL				tmpSel;
	//  QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  (  pObjDb->cfg.iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_gpImMsgListQueryStruct_isClient  :  CONST_resId_gpImMsgListQueryStruct_isMgr  );
	//  TCHAR				*	pTabName		=	CONST_tabName_qyImMsgTab;
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;

#if 0
	tmpSel.u.query.type			=	CONST_qyQueryType_imMsgList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from (%s left join qyImObjRegInfoTab as B on (qyImMsgTab.misServName=B.misServName and qyImMsgTab.idStr_send=B.idStr) )"  ),  pTabName  );
	//
	if  (  wherePart  )  {
		if  (  tmpSel.u.query.wherePart[0]  )  _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s and"  ),  tmpSel.u.query.wherePart  );
		_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s (%s)"  ),  tmpSel.u.query.wherePart,  CQyString(  wherePart  )  );
	}
	//
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImMsgTab.firstTime desc"  )  );
#endif
	fillQyMcQuery( pQyMc, pObjDb,  CONST_qyQueryType_imMsgList,  0,  wherePart,  &tmpSel.u.query  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.pfProcEvent_new  =  is_procEvent_new;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  (  pObjDb->cfg.iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_popup_viewImTaskList_isClient  :  CONST_resId_popup_viewImTaskList_isMgr;		//  2003/12/17ÐÞ¸Ä
	tmpSel.u.query.uiDefaultCmd  =  ID_qyProp_imTask;

	if  (  docName  )  _sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_msgList  )  );
#if  0
	bRet  =  pApp->bNewQueryView(  &tmpSel  );
#endif
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


  BOOL  bViewImMsgToday(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	 //QY_MC		*	pQyMc								=	QY_GET_GBUF(  );
	 TCHAR			eventTypeName[128]					=	_T(  ""  );  lstrcpyn(  eventTypeName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyMsgToday  ),  mycountof(  eventTypeName  )  );
	 TCHAR			whereClause[1024]					=	_T(  ""  );
	 char			timeBuf[CONST_qyTimeLen  +  1]		=	"";
	 int			i;
	 	
	 getCurTime(  timeBuf  );
	 for  (  i  =  8;  i  <  CONST_qyTimeLen;  i  ++  )  timeBuf[i]  =  '0';

	 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "qyImMsgTab.firstTime>'%s'"  ),  CString(  timeBuf  )  );
	 if  (  wherePart  )  _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s and (%s)"  ),  whereClause,  wherePart  );
	
	 return  bViewImMsgListFunc(  pQyMc,  pObjDb,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_today  ),  whereClause  );

}



  //  bPhoneGuest phoneMessenger
 int  getSelectedToPath(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  BOOL  bPhoneGuest,  TCHAR  *  toPath,  unsigned  int  size  )
{

	//
	return  -1;

}


 //
 int  tmpHandler_procLvEventFunc_isCli(  QY_EVENTINFO  *  pEventInfo,  void  *  pObjDbParam,  int  iLvType,  int  curnItem,  BOOL  bFirst,  void  *  pParam0  )
{
	int									iErr											=		-1;
	QY_MC							*	pQyMc											=		QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp				*	pFuncs											=  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs   ) return  -1;
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;

	//
	QY_OBJ_DB						*	pObjDb											=		(  QY_OBJ_DB  *  )pObjDbParam;
	unsigned  char						ucbRefreshed									=		FALSE;
	HWND								hParent											=		pEventInfo->hWnd;
	unsigned  int						uiCmd											=		pEventInfo->uiCmd;  
	unsigned  int						uiType											=		0;
	TCHAR								misServName[CONST_maxMisServNameLen  +  1]		=		_T(  ""  );
	QY_MESSENGER_ID						idInfo;
	char								idStr[CONST_qyMessengerIdStrLen  +  1]			=		"";
	TCHAR								colName[255]									=		_T(  ""  );
	TCHAR								tBuf[255  +  1]									=		_T(  ""  );
	char								buf[255  +  1]									=		"";
	PARAM_procLvEventFunc_is		*	pParam											=		(  PARAM_procLvEventFunc_is  *  )pParam0;
	TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]				=		_T(  ""  );
	TCHAR								displayName[128]								=		_T(  ""  );
	MSGR_ADDR							addr;
	//
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	if  (  curnItem  <  0  )  {		//  µã»÷¿Õ°×´¦µÄ´¦Àí
		switch  (  iLvType  )  {
				case  CONST_qyQueryType_phoneGuestList:
					  //
					  uiType  =  CONST_imCommType_phoneGuest;
					  ucbRefreshed  =  TRUE;
					  //
					  switch  (  uiCmd  )  {
							  case  ID_qyAdd:  {
									#ifndef  __isCli__
								    CDlgCfgPhoneMessenger	dlg;
									if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  NULL,  TRUE,  0,  0  )  )  goto  errLabel;
									if  (  dlg.DoModal(  )  !=  IDOK  )  ucbRefreshed  =  FALSE;
									#endif
									iErr  =  0;  goto  errLabel;
									}
								    break;
							  case  ID_qyImport:
								    if  (  !bImportKnowledge(  uiType  )  )  ucbRefreshed  =  FALSE;
									iErr  =  0;  goto  errLabel;
								    break;
							  case  ID_qyExport:
								    if  (  !bExportKnowledge(  uiType  )  )  ucbRefreshed  =  FALSE;
									iErr  =  0;  goto  errLabel;
								    break;
							  case  ID_qyClearUp:
									if  (  !bClearupKnowledge(  uiType  )  )  ucbRefreshed  =  FALSE;
									iErr  =  0;  goto  errLabel;
								    break;
							  default:
									 break;
					  }
					  //
					  break;
				case  CONST_qyQueryType_phoneMessengerList:
					  //
					  switch  (  uiCmd  )  {
							  case  ID_qyAdd:  {
									#ifndef  __isCli__
								    CDlgCfgPhoneMessenger		dlg;
									if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  NULL,  FALSE,  0,  0  )  )  goto  errLabel;
									if  (  dlg.DoModal(  )  ==  IDOK  )  ucbRefreshed  =  TRUE;
									#endif
									iErr  =  0;  goto  errLabel;
									}
								    break;
							  default:
									 break;
					  }
					  //
					  break;

				case  CONST_qyQueryType_sharedDynBmpList:  
					  //		  
					  switch  (  uiCmd  )  {
						      //  isClient
							  case  ID_retrieveAll:  {
								    MIS_CNT			*	pMisCnt		=	NULL;

									if  (  !(  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  )  )  )  goto  errLabel;
									sndRetrieveDynBmpsReq_qmc(  pMisCnt,  TRUE  );
									}		
									break;
							  default:
									  break;
					  }
					  //					  
					  break;

				default:
						break;
		}

		iErr  =  0;  goto  errLabel;
	}

	//  ÏÂÃæ±íÃ÷ÊÇÑ¡ÖÐÄ³¼¸ÐÐ½øÐÐ´¦Àí¡£
	//
	if  (  getKeyNameByLvType(  iLvType,  colName,  mycountof(  colName  )  )  )  goto  errLabel;	
	
	HWND	hList	=	pEventInfo->hFrom;
	if  (  getLvColContent(  hParent,  hList,  curnItem,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_servName  ),  misServName,  mycountof(  misServName  )  )  )  misServName[0]  =  0;
	if  (  getLvColContent(  hParent,  hList,  curnItem,  colName,  tBuf,  mycountof(  tBuf  )  )  )  {
		#ifdef  __DEBUG__
			    traceLogA(  "netMc_procEventFunc´íÎó: Ã»ÓÐÕÒµ½À¸Ä¿%sÏàÓ¦µÄÄÚÈÝ",  colName  );  
		#endif
		goto  errLabel;
	}
	myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );

	switch  (  iLvType  )  {
			case  CONST_qyQueryType_phoneMessengerList:  {
				  QY_MESSENGER_phoneInfo		rcd;
				  //
				  if  (  !g_dbFuncs.pf_bGetMessengerPhoneInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  0,  0,  0,  0,  atol(  buf  ),  &rcd  )  )  goto  errLabel;
				  //
				  uiType  =  CONST_objType_phoneMessenger;
				  lstrcpyn(  misServName,  rcd.misServName,  mycountof(  misServName  )  );
				  idInfo.ui64Id  =  rcd.idInfo.ui64Id;
				  //
				  switch  (  uiCmd  )  {
						  case  ID_qyDel:
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeletePhoneNumber  )/*_T(  "È·ÊµÒªÉ¾³ýÊÖ»úÐÅÏ¢Âð?"  )*/,  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								}
#if  0
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyMessengerPhoneInfoTab,  atol(  buf  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
								if  (  !g_dbFuncs.pf_bDeleteFromTabById(  pObjDb->pDb,  pObjDb->cfg.iDbType,  CONST_tabName_qyMessengerPhoneInfoTab,  atol(  buf  )  )  )  goto  errLabel;
								ucbRefreshed  =  TRUE;
							    iErr  =  0;  goto  errLabel;
							    break;
						  default:
								 break;
				  }
				  }
				  break;
			case  CONST_qyQueryType_imObjList:  
			case  CONST_qyQueryType_clientList_is:  {
				  QY_MESSENGER_REGINFO		regInfo;
				  QY_MESSENGER_phoneInfo	phoneInfo;
				  MY_REG_DESC				desc;

				  uiType  =  CONST_objType_messenger;
				  //  misServName
				  idStr2Info(  buf,  &idInfo  );
				  //
				  memset(  &addr,  0,  sizeof(  addr  )  );
				  lstrcpyn(  addr.misServName,  misServName,  mycountof(  addr.misServName  )  );
				  addr.uiObjType  =  CONST_objType_messenger;
				  addr.idInfo.ui64Id  =  idInfo.ui64Id;
				  //
				  if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  addr.misServName,  &addr.idInfo,  0,  NULL,  &regInfo,  NULL,  &phoneInfo  )  )  {
					  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
					  memset(  &phoneInfo,  0,  sizeof(  phoneInfo  )  );
					  //
				  }				  
				  regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  addr.displayName,  mycountof(  addr.displayName  )  );
				  //				  
				  switch  (  uiCmd  )  {
						  case  ID_qySendSm:
							    //
							    if  (  phoneInfo.wDevIdStr[0]  )  {		//  
									if  (  qPostMsg(  &addr,  sizeof(  addr  ),  &pParam->tmpGrpMemQ,  _T(  "tmp_procLvEvnetFunc"  )))  goto  errLabel;
								}
								//
								iErr  =  0;  goto  errLabel;
							    break;
						  case  ID_qyRule:  {						//  2010/09/06
#if  0
								#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
								CDlgImObjRule					dlg;
								if  (  !dlg.bSetDlgInfo(  addr.misServName,  &addr.idInfo  )  )  goto  errLabel;
								dlg.DoModal(  );
								#endif
#endif
								showDlgImObjRule(  NULL,  addr.misServName,  &addr.idInfo  );
							    }
							    //
							    iErr  =  0;  goto  errLabel;
								break;
						  default:
								  break;
				  }
				  //
				  }
				  break;
			case  CONST_qyQueryType_customerServiceList:
				  uiType  =  CONST_objType_messenger;
				  //
				  idStr2Info(  buf,  &idInfo  );
				  //
				  switch  (  uiCmd  )  {
						  case  ID_qyDel:
#if  0
 							    if  (  !idInfo2Str(  &idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyCustomerServiceObjTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
								if  (  !g_dbFuncs.pf_bDeleteFromTabByIdInfo(  pObjDb->pDb,  pObjDb->cfg.iDbType,  CONST_tabName_qyCustomerServiceObjTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  &idInfo  )  )  goto  errLabel;

							    ucbRefreshed  =  TRUE;
								iErr  =  0;  goto  errLabel;
							    break;
						  default:
								  break;
				  }
				  break;
			case  CONST_qyQueryType_wwwQmCfgList:  
				  uiType  =  CONST_objType_messenger;
				  //  misServName
				  idStr2Info(  buf,  &idInfo  );
				  //
				  switch  (  uiCmd  )  {
						  case  ID_qyDel:
#if 0
 							    if  (  !idInfo2Str(  &idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyWebContactTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
								if  (  !g_dbFuncs.pf_bDeleteFromTabByIdInfo(  pObjDb->pDb,  pObjDb->cfg.iDbType,  CONST_tabName_qyWebContactTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  &idInfo  )  )  goto  errLabel;
							    ucbRefreshed  =  TRUE;
								iErr  =  0;  goto  errLabel;
							    break;
						  default:
								  break;
				  }
				  break;
			case  CONST_qyQueryType_phoneGuestList:  {
				  PHONE_GUEST_RCD			guest;
				  QY_MESSENGER_REGINFO		regInfo;
				  MY_REG_DESC				desc;
				  //
				  if  (  !bGetPhoneGuestRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  0,  0,  0,  atol(  buf  ),  &guest  )  )  goto  errLabel;
				  //
				  memset(  &addr,  0,  sizeof(  addr  )  );
				  lstrcpyn(  addr.misServName,  misServName,  mycountof(  addr.misServName  )  );
				  addr.uiObjType  =  CONST_objType_phoneGuest;
				  addr.uiDevType  =  guest.uiDevType;
				  lstrcpyn(  addr.wDevIdStr,  guest.wDevIdStr,  mycountof(  addr.wDevIdStr  )  );
				  //  _sntprintf(  addr.displayName,  mycountof(  addr.displayName  ),  _T(  "%s"  ),  guest.
				  //
				  if  (  !g_dbFuncs.pf_bGetImOtherRegInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImOtherRegInfoTab,  &addr,  0,  &regInfo  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
				  //
				  if  (  regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  addr.displayName,  mycountof(  addr.displayName  )  )  )  goto  errLabel;
				  //
				  switch  (  uiCmd  )  {
						  case  ID_qySendSm:
							    //  ¼Óµ½¶ÓÁÐÖÐ£¬ÔÚÑ­»·½áÊøºóÔÙµ÷ÓÃtalkTo...
							    if  (  qPostMsg(  &addr,  sizeof(  addr  ),  &pParam->tmpGrpMemQ,  _T(  "tmp_procLvEventFunc 1"  )))  goto  errLabel;
							    break;
						  case  ID_qyEdit:  {
								#if  0  //  ndef  __isCli__
							    CDlgQnmEditPcUsrInfo		dlg;
					   			//
					   			if  (  !dlg.bSetDlgInfo(  pObjDb,  &addr,  0,  FALSE  )  )  goto  errLabel;
					   			//
					   			if  (  dlg.DoModal(  )  ==  IDOK  &&  dlg.m_var.ucbChanged  )  ucbRefreshed  =  TRUE;							    
								#endif
								unsigned  char  ucbChanged  =  FALSE;
								if  (  showDlgQnmEditPcUsrInfo(  NULL,  pObjDb,  &addr,  0,  FALSE,  &ucbChanged  )  !=  IDOK  )  goto  errLabel;
								if  (  ucbChanged  )  ucbRefreshed  =  TRUE;

							    }
							    break;
						  case  ID_qyDel:
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeleteInfo  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								}
#if  0
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and uiDevType=%d and wDevIdStr=%s"  ),  CONST_tabName_qyImOtherRegInfoTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  addr.uiDevType,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_wDevIdStr,  addr.wDevIdStr  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
								if  (  !g_dbFuncs.pf_bDeleteImOtherRegInfoByAddr(  pObjDb->pDb,  pObjDb->cfg.iDbType,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CONST_tabName_qyImOtherRegInfoTab,  &addr  )  )  goto  errLabel;
#if  0
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyPhoneGuestTab,  atol(  buf  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
								if  (  !g_dbFuncs.pf_bDeleteFromTabById(  pObjDb->pDb,  pObjDb->cfg.iDbType,  CONST_tabName_qyPhoneGuestTab,  atol(  buf  )  )  )  goto  errLabel;
								ucbRefreshed  =  TRUE;
							    break;
						  case  ID_qyProperties:  {
#if  0
							    CDlgPropMessenger		dlg;
					   			//
					   			if  (  !dlg.bSetDlgInfo(  pObjDb,  &addr  )  )  goto  errLabel;
					   			dlg.DoModal(  );
#endif
								if  (  showDlgPropMessenger(  NULL,  pObjDb,  &addr  )  !=  IDOK  )  goto  errLabel;
								}
							    break;
						  default:
								 break;
				  }
				  //
				  }
				  //
				  iErr  =  0;  goto  errLabel;				  
				  //
				  break;
			case  CONST_qyQueryType_gsmModemList:  {
				  //
				  QY_VDEVCOM_RCD		rcd;

				  if  (  !bGetQyVDevComRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  0,  0,  0,  atol(  buf  ),  &rcd  )  )  goto  errLabel;

				  memset(  &addr,  0,  sizeof(  addr  )  );
				  lstrcpyn(  addr.misServName,  misServName,  mycountof(  addr.misServName  )  );
				  addr.idInfo.ui64Id  =  rcd.idInfo.ui64Id;
				  //
				  idInfo2Str(  &addr.idInfo,  idStr,  mycountof(  idStr  )  );
				  //
				  switch  (  uiCmd  )  {
						  case  ID_qyProperties:  {
#if  0
							    CDlgPropMessenger		dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
								//
								if  (  !dlg.bSetDlgInfo(  pObjDb,  &addr  )  )  goto  errLabel;
								dlg.DoModal(  );
#endif
								if  (  showDlgPropMessenger(  pEventInfo->hWnd,  pObjDb,  &addr  )  !=  IDOK  )  goto  errLabel;
							    }
							    break;
						  case  ID_qyCfgSmContact:  {
								#ifndef  __isCli__
							    CDlgCfgGsmModem			dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
								//
								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  addr.misServName,  &addr.idInfo,  rcd.wDevIdStr,  FALSE,  0  )  )  goto  errLabel;
								dlg.DoModal(  );
								#endif
								}
							    break;
						  case  ID_qyCfgDefaultSmContact:  {
								#ifndef  __isCli__
							    CDlgCfgGsmModem			dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
								//
								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  addr.misServName,  &addr.idInfo,  _T(  ""  ),  FALSE,  0  )  )  goto  errLabel;
								dlg.DoModal(  );
								#endif
								}
							    break;
						  case  ID_qyCfgDefaultSmServer:  {
								#ifndef  __isCli__
							    CDlgCfgGsmModem			dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
								//
								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  addr.misServName,  &addr.idInfo,  _T(  ""  ),  TRUE,  0  )  )  goto  errLabel;
								dlg.DoModal(  );
								#endif
								}
							    break;
						  case  ID_qyViewSmContacts:
								#ifndef  __isCli__
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qySmContactTab.misServName=%s and qySmContactTab.idStr='%s'"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u"  ),  addr.idInfo.ui64Id  );
								bViewSmContactList_isMgr(   pObjDb,  displayName,  sqlBuf  );
								#endif
							    break;
						  case  ID_qyDel:  
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  _T(  "Are you sure to delete some information and rules of SM device ?"  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								}
#if  0
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and idStr='%s'"  ),  CONST_tabName_qySmContactTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyVDevComTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
								//
								if  (  !g_dbFuncs.pf_bDeleteFromTabByIdInfo(  pObjDb->pDb,  pObjDb->cfg.iDbType,  CONST_tabName_qySmContactTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  &addr.idInfo  )  )  goto  errLabel;
								if  (  !g_dbFuncs.pf_bDeleteFromTabByIdInfo(  pObjDb->pDb,  pObjDb->cfg.iDbType,  CONST_tabName_qyVDevComTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  &addr.idInfo  )  )  goto  errLabel;
								ucbRefreshed  =  TRUE;
							    break;
						  default:
								 break;
				  }
				  //
				  }
				  iErr  =  0;  goto  errLabel;
				  break;
			case  CONST_qyQueryType_smContactList:  {
				  //
				  QY_SMCONTACT_RCD			rcd;

				  if  (  !bGetQySmContactRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  0,  0,  0,  0,  atol(  buf  ),  &rcd  )  )  goto  errLabel;

				  memset(  &addr,  0,  sizeof(  addr  )  );
				  lstrcpyn(  addr.misServName,  misServName,  mycountof(  addr.misServName  )  );
				  addr.idInfo.ui64Id  =  rcd.idInfo.ui64Id;
				  //
				  switch  (  uiCmd  )  {
						  case  ID_qyProperties:  {
#if  0
							    CDlgPropMessenger		dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
								//
								if  (  !dlg.bSetDlgInfo(  pObjDb,  &addr  )  )  goto  errLabel;
								dlg.DoModal(  );
#endif
								if  (  showDlgPropMessenger(  pEventInfo->hWnd,  pObjDb,  &addr  )  !=  IDOK  )  goto  errLabel;
							    }
							    break;
						  case  ID_qyEdit:  {
								#ifndef  __isCli__
							    CDlgCfgGsmModem			dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
								//
								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  addr.misServName,  &addr.idInfo,  rcd.wDevIdStr,  rcd.ucbDefaultSmServer,  0  )  )  goto  errLabel;
								if  (  dlg.DoModal(  )  ==  IDOK  )  ucbRefreshed  =  TRUE;
								#endif
								}
							    break;						  
						  case  ID_qyDel:  {
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeleteInfo  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								}
#if  0
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qySmContactTab,  atol(  buf  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
								if  (  !g_dbFuncs.pf_bDeleteFromTabById(  pObjDb->pDb,  pObjDb->cfg.iDbType,  CONST_tabName_qySmContactTab,  atol(  buf  )  )  )  goto  errLabel;
								ucbRefreshed  =  TRUE;							    
								}
							    break;
						  default:
								 break;
				  }
				  

				  }
				  //
				  iErr  =  0;  goto  errLabel;
				  break;
			case  CONST_qyQueryType_tmpGrpMemList:  {
				  //
				  memset(  &addr,  0,  sizeof(  addr  )  );
				  lstrcpyn(  addr.misServName,  misServName,  mycountof(  addr.misServName  )  );
				  addr.uiObjType  =  CONST_objType_phoneGuest;
				  addr.uiDevType  =  CONST_objType_phone;
				  lstrcpyn(  addr.wDevIdStr,  tBuf,  mycountof(  addr.wDevIdStr  )  );
				  //  
				  switch  (  uiCmd  )  {
						  case  ID_qyProperties:  {
#if  0
							    CDlgPropMessenger		dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
								//
								if  (  !dlg.bSetDlgInfo(  pObjDb,  &addr  )  )  goto  errLabel;
								dlg.DoModal(  );
#endif
								if  (  showDlgPropMessenger(  pEventInfo->hWnd,  pObjDb,  &addr  )  !=  IDOK  )  goto  errLabel;
								//
							    }
							    break;
						  default:
								  break;				  
				  }
				  //
				  }
				  //
				  iErr  =  0;  goto  errLabel;
				  //
				  break;
			case  CONST_qyQueryType_imGrpList:
				  QY_MESSENGER_INFO			messengerInfo;
				  //
				  if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  0,  NULL,  atol(  buf  ),  &messengerInfo,  NULL,  NULL,  NULL  )  )  goto  errLabel;
				  //
				  uiType  =  messengerInfo.uiType;
				  lstrcpyn(  misServName,  messengerInfo.misServName,  mycountof(  misServName  )  );
				  idInfo.ui64Id  =  messengerInfo.idInfo.ui64Id;
				  break;
			case  CONST_qyQueryType_imObjRegInfoList:
			case  CONST_qyQueryType_imObjRegInfoInTab1List:
				  QY_MESSENGER_REGINFO		regInfo;
				  TCHAR					*	pTabName;
				  pTabName  =  (  iLvType  ==  CONST_qyQueryType_imObjRegInfoList  )  ?  CONST_tabName_qyImObjRegInfoTab  :  CONST_tabName_qyImObjRegInfoTab1;
				  //
				  if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pTabName,  0,  NULL,  atol(  buf  ),  &regInfo  )  )  goto  errLabel;
				  //
				  uiType  =  CONST_objType_messenger;
				  lstrcpyn(  misServName,  regInfo.addr.misServName,  mycountof(  misServName  )  );
				  idInfo.ui64Id  =  regInfo.addr.idInfo.ui64Id;
				  break;
			case  CONST_qyQueryType_talk_imGrpMemList:
				  IM_GRP_MEM						grpMem;

				  //
				  if  (  !g_dbFuncs.pf_bGetImGrpMemBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  NULL,  NULL,  NULL,  atol(  buf  ),  &grpMem  )  )  goto  errLabel;
				  //		  
				  switch  (  uiCmd  )  {
						  case  ID_qyDel:
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfRemoveFromGroup ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
									time(  &pParam->t  );
									pParam->idInfo_grp.ui64Id  =  grpMem.idInfo_grp.ui64Id;
								}
#if  0
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyImGrpMemTab,  atol(  buf  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
								if  (  !g_dbFuncs.pf_bDeleteFromTabById(  pObjDb->pDb,  pObjDb->cfg.iDbType,  CONST_tabName_qyImGrpMemTab,  atol(  buf  )  )  )  goto  errLabel;
								//
								//  É¾³ý³ÉÔ±ÒªÍ¨Öª·þÎñÆ÷Ë¢ÐÂ
								PARAM_applyForServWork		tmpParam;							
								memset(  &tmpParam,  0,  sizeof(  tmpParam  )  );
								tmpParam.uiType  =  CONST_imCommType_refreshImGrp;
								tmpParam.p0  =  &pParam->idInfo_grp;
								if  (  memcmp(  &tmpParam,  &pParam->param_applyForServWork,  sizeof(  tmpParam  )  )  )  {
									if  (  pParam->param_applyForServWork.uiType  )  {
										if  (  applyForServWork(  pParam->param_applyForServWork.uiType,  pParam->param_applyForServWork.usOp,  pParam->param_applyForServWork.p0,  pParam->param_applyForServWork.p1,  pParam->param_applyForServWork.p2  )  )  goto  errLabel;
									}
									memcpy(  &pParam->param_applyForServWork,  &tmpParam,  sizeof(  pParam->param_applyForServWork  )  );
								}								
								//
								ucbRefreshed  =  TRUE;
								iErr  =  0;  goto  errLabel;
							    break;
						  case  ID_yz_shareScreen:  {
							    HWND  hTalk  =  NULL;
								if  (  findTalker(  pQyMc,  &grpMem.idInfo_grp,  &hTalk  )  )  goto  errLabel;
								//
								requestToControlDesktop_yz(  hTalk,  &grpMem.idInfo_mem,  TRUE  );
								}
							    iErr  =  0;  goto  errLabel;
							    break;
						  case  ID_yz_stopShareScreen:  {
							    HWND  hTalk  =  NULL;
								if  (  findTalker(  pQyMc,  &grpMem.idInfo_grp,  &hTalk  )  )  goto  errLabel;
								//
								requestToControlDesktop_yz(  hTalk,  &grpMem.idInfo_mem,  FALSE  );
								}
							    iErr  =  0;  goto  errLabel;
							    break;
						  case  ID_menuItemIdc_remotePtzControl:  {
							    HWND  hParent  =  pEventInfo->hWnd;
							    //
								HWND  hTalk_mem  =  NULL;
								if  (  talkToMessenger(  grpMem.idInfo_mem.ui64Id,  0,  TRUE,  FALSE,  &hTalk_mem  )  )  goto  errLabel;
							    //
								viewRemotePtzControl(  hParent,  hTalk_mem  );
								}
								iErr  =  0;  goto  errLabel;
							    break;
						  case  ID_qyEdit:  {
							    HWND  hParent  =  pEventInfo->hWnd;
							    
								if  (  !viewDlgEditConsultMem(  hParent,  &grpMem.idInfo_grp,  &grpMem.idInfo_mem  )  )  {

									HWND  hTalk  =  NULL;								
									if  (  findTalker(  pQyMc,  &grpMem.idInfo_grp,  &hTalk  )  )  goto  errLabel;
									//								
									
									refresh_consult_mem(  hTalk,  &grpMem.idInfo_mem  );  

								}
								}
								iErr  =  0;  goto  errLabel;
								break;
								//
						  case  ID_qyImGrpList:
						  case  ID_qyAddTo:
						  case  ID_qyProperties:  
						  case  ID_qyTalk:
						  default:
							    uiType  =  CONST_objType_messenger;
								lstrcpyn(  misServName,  grpMem.misServName,  mycountof(  misServName  )  );
								idInfo.ui64Id  =  grpMem.idInfo_mem.ui64Id;
								break;
				  }	
				  break;
			case  CONST_qyQueryType_imMsgList:
				  IM_MSG_RCD					imMsg;
				  //
				  if  (  !g_dbFuncs.pf_bGetImMsgRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  atol(  buf  ),  &imMsg  )  )  goto  errLabel;
								
				  switch  (  uiCmd  )  {
						  case  ID_qyTalkToTaskPeer:
							    QY_MESSENGER_INFO				messenger_send,  messenger_recv;
							    QY_MESSENGER_ID					idInfo_peer;
							    // 
								if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  imMsg.misServName,  &imMsg.idInfo_send,  0,  &messenger_send,  NULL,  NULL,  NULL  )  )  goto  errLabel;
								if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  imMsg.misServName,  &imMsg.idInfo_recv,  0,  &messenger_recv,  NULL,  NULL,  NULL  )  )  goto  errLabel;
								//
								idInfo_peer.ui64Id  =  0;
								if  (  messenger_recv.uiType  ==  CONST_objType_imGrp  )  idInfo_peer.ui64Id  =  messenger_recv.idInfo.ui64Id;
								else  if  (  messenger_send.uiType  !=  CONST_objType_me  )  idInfo_peer.ui64Id  =  messenger_send.idInfo.ui64Id;
								else  if  (  messenger_recv.uiType  !=  CONST_objType_me  )  idInfo_peer.ui64Id  =  messenger_recv.idInfo.ui64Id;
								else  goto  errLabel;
				  
								memset(  &addr,  0,  sizeof(  addr  )  );
								lstrcpyn(  addr.misServName,  imMsg.misServName,  mycountof(  addr.misServName  )  );
								addr.idInfo.ui64Id  =  idInfo_peer.ui64Id;
								//
								//  if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;
								if  (  pFuncs->pf_tryToTalkToMessenger(  mynull,&addr,  0,  0,  TRUE,  NULL,  0,  NULL  )  )  goto  errLabel;
								//
                                break;
						  case  ID_qyProp_imTask:  {
#if  0
							    CDlgPropImMsg			dlg;

								if  (  !dlg.bSetDlgInfo(  pObjDb,  atol(  buf  )  )  )  goto  errLabel;
								dlg.DoModal(  );
#endif
								if  (  showDlgPropImMsg(  NULL,  pObjDb,  atol(  buf  )  )  !=  IDOK  )  goto  errLabel;
								}
							    break;
						  default:
								 break;
				  }
				  break;
			case  CONST_qyQueryType_imTaskList:
			case  CONST_qyQueryType_imTaskHisList:
				  //
				  switch  (  uiCmd  )  {
						  case  ID_qyTalkToTaskPeer:  {
					     	    IM_TASK_RCD			imTask;
								QY_MESSENGER_ID		idInfo_peer;
								BOOL				bHisTab		=	FALSE;
								HWND				hWnd		=	NULL;
								QY_WMBUF_COMM		wmBuf;
								MIS_CNT			*	pMisCnt		=	NULL;
								//
								ucbRefreshed  =  FALSE;
								//						 					     
								bHisTab  =  iLvType  ==  CONST_qyQueryType_imTaskHisList;
								//
								if  (  !g_dbFuncs.pf_bGetImTaskRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  bHisTab,  NULL,  NULL,  0,  0,  atol(  buf  ),  &imTask  )  )  goto  errLabel;
								if  (  !(  pMisCnt  =  getMisCntByName(  pProcInfo,  imTask.misServName  )  )  )  goto  errLabel;
								if  (  !pMisCnt->idInfo.ui64Id  )  goto  errLabel;
								if  (  pMisCnt->idInfo.ui64Id  ==  imTask.idInfo_send.ui64Id  )  idInfo_peer.ui64Id  =  imTask.idInfo_recv.ui64Id;
								else  idInfo_peer.ui64Id  =  imTask.idInfo_send.ui64Id;

								/*
								switch  (  imTask.uiType  )  {
										case  CONST_imTaskType_sendFile:
										//  case  CONST_imTaskType_req:
											  idInfo_peer.ui64Id  =  imTask.idInfo_recv.ui64Id;		   
									   		  break;
										case  CONST_imTaskType_recvFile:
										case  CONST_imTaskType_resp:
											  idInfo_peer.ui64Id  =  imTask.idInfo_send.ui64Id;
											  break;
										default:
												traceLogA(  "netMc_procLvEventFunc: Î´´¦ÀíµÄimTaskType, %d",  imTask.uiType  );
												goto  errLabel;
												break;
								}
								*/

								memset(  &addr,  0,  sizeof(  addr  )  );
								lstrcpyn(  addr.misServName,  imTask.misServName,  mycountof(  addr.misServName  )  );
								addr.idInfo.ui64Id  =  idInfo_peer.ui64Id;
								//
								//  if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  FALSE,  TRUE,  &hWnd  )  )  goto  errLabel;
								if  (  pFuncs->pf_tryToTalkToMessenger(  mynull,&addr,  0,  0,  TRUE,  NULL,  0,  &hWnd  )  )  goto  errLabel;

								memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
								wmBuf.uiType  =  CONST_qyWmParam_activateImTask;
								wmBuf.u.activateImTask.iTaskId_activated  =  atol(  buf  );
								SendMessage(  hWnd,  CONST_qyWm_comm,  NULL,  (  LPARAM  )&wmBuf  );
							    }
					     	    break;
				   		  case  ID_qyProp_imTask:  {
							    #if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
						 		BOOL				bHisTab		=	FALSE;
								//
								ucbRefreshed  =  FALSE;
								//						 					     
								bHisTab  =  iLvType  ==  CONST_qyQueryType_imTaskHisList;
								//
#if  0
							    CDlgPropImTask		dlg;
								if  (  !dlg.bSetDlgInfo(  pObjDb,  bHisTab,  atol(  buf  )  )  )  goto  errLabel;
								dlg.DoModal(  );
#endif
								showDlgPropImTask(  NULL,  pObjDb,  bHisTab,  atol(  buf  )  );
								#endif
							    }
							    break;
						  default:
								 break;
				  }

				  iErr  =  0;  goto  errLabel;
				  break;
				
			case  CONST_qyQueryType_instantAssistantMemList:  {
				  QY_WMBUF_COMM  wmBuf;
				  memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
				  wmBuf.uiType  =  CONST_qyWmParam_requestToSpeak;
				  wmBuf.u.requestToSpeak.uiCmd  =  uiCmd;
				  wmBuf.u.requestToSpeak.bManager  =  TRUE;
				  wmBuf.u.requestToSpeak.curnItem  =  curnItem;

				  SendMessage(  pEventInfo->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
				  }
				  iErr  =  0;  goto  errLabel;
				  break;

#if  0	//  2017/01/10
			case  CONST_qyQueryType_sharedDynBmpList:  {
				  QY_dynBmp_RCD						dynBmp;
				  //
				  if  (  !g_dbFuncs.pf_bGetQyDynBmpRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  NULL,  NULL,  NULL,  0,  atol(  buf  ),  &dynBmp  )  )  goto  errLabel;
				  //		  
				  switch  (  uiCmd  )  {
								//  isClient
						  case  ID_viewDynBmp:
							    //  traceLogA(  "Cmd: viewDynBmp"  );
							    viewDynBmp(  ::GetDesktopWindow(  ),  pObjDb,  dynBmp.misServName,  &dynBmp.idInfo,  dynBmp.uiObjType,  dynBmp.usIndex,  dynBmp.cusName[0]  ?  dynBmp.cusName  :  dynBmp.name  );
							    break;
						  case  ID_retrieveAll:  {
							    MIS_CNT			*	pMisCnt		=	NULL;

								if  (  !(  pMisCnt  =  getMisCntByName(  pProcInfo,  dynBmp.misServName  )  )  )  goto  errLabel;
								sndRetrieveDynBmpsReq_qmc(  pMisCnt,  TRUE  );
								}
							    break;

						  default:
								  break;
				  }

				  }
				  iErr  =  0;  goto  errLabel;				  
				  break;
#endif

			case  CONST_qyQueryType_sharedDynBmpRuleList:  {
#if  0
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyDynBmpRuleTab,  atol(  buf  )  );
				  if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;				  
#endif
				  if  (  !g_dbFuncs.pf_bDeleteFromTabById(  pObjDb->pDb,  pObjDb->cfg.iDbType,  CONST_tabName_qyDynBmpRuleTab,  atol(  buf  )  )  )  goto  errLabel;
				  ucbRefreshed  =  TRUE;
				  }
				  iErr  =  0;  goto  errLabel;
				  break;

			case  CONST_qyQueryType_imObjRuleList:  {
				  QY_imObjRule_rcd	rcd;

				  if  (  !g_dbFuncs.pf_bGetImObjRuleRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  NULL,  NULL,  NULL,  atol(  buf  ),  &rcd  )  )  goto  errLabel;

				  if  (  isIsMgr(  pQyMc  )  )  {
					  #ifdef  __DEBUG__
							  traceLog(  _T(  "Warning: not supported"  )  );
					  #endif
					  goto  errLabel;
				  }

#if  0
				  #if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
				  CDlgImObjRule		dlg;
				  if  (  !dlg.bSetDlgInfo(  rcd.misServName,  &rcd.idInfo_related  )  )  goto  errLabel;

				  if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
				  #endif
#endif
				  if  (  showDlgImObjRule(  NULL,  rcd.misServName,  &rcd.idInfo_related  )  !=  IDOK  )  goto  errLabel;

				  ucbRefreshed  =  TRUE;
				  }
				  iErr  =  0;  goto  errLabel;
				  break;

			default:
				    traceLogA(  "tmpHandler_procLvEventFunc_is failed. iLvType [%d] err",  iLvType  );
					goto  errLabel;
			  
	}


	if  (  !idInfo2Str(  &idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
	_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u"  ),  idInfo.ui64Id  );

	//
	switch  (  uiType  )  {
			case  CONST_objType_me:
			case  CONST_objType_admin:
			case  CONST_objType_messenger:
			case  CONST_objType_phoneMessenger:
				  switch  (  uiCmd  )  {
			              case  ID_imTaskList_unproced:
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s and (T.idStr_send='%s' or T.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  ),  CString(  idStr  )  );
								g_dbFuncs.pf_bViewImTaskList_unproced(  pObjDb,  _T(  ""  ),  sqlBuf  );
								break;
						  case  ID_imTaskList_cur:
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s and (T.idStr_send='%s' or T.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  ),  CString(  idStr  )  );
								//  bViewImTaskListFunc(  pObjDb,  _T(  ""  ),  sqlBuf,  FALSE  );
								g_dbFuncs.pf_bViewImTaskList_cur(  pObjDb,  _T(  ""  ),  sqlBuf  );
								break;
						  case  ID_imTaskList_his:
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s and (T.idStr_send='%s' or T.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  ),  CString(  idStr  )  );
								//  bViewImTaskListFunc(  pObjDb,  _T(  ""  ),  sqlBuf,  TRUE  );
								g_dbFuncs.pf_bViewImTaskList_his(  pObjDb,  _T(  ""  ),  sqlBuf  );
								break;
						  case  ID_qyMsgToday:
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImMsgTab.misServName=%s and (qyImMsgTab.idStr_send='%s' or qyImMsgTab.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  ),  CString(  idStr  )  );
								bViewImMsgToday(  pQyMc,  pObjDb,  sqlBuf  );
								break;
						  case  ID_qyMsgList:				   
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImMsgTab.misServName=%s and (qyImMsgTab.idStr_send='%s' or qyImMsgTab.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  ),  CString(  idStr  )  );
								bViewImMsgListFunc(  pQyMc,  pObjDb,  _T(  ""  ),  sqlBuf  );
								break;
								//
				 		  case  ID_qyEdit:  {
								#if  0  //  ndef  __isCli__
							    CDlgQnmEditPcUsrInfo		dlg;
					   			//
					   			if  (  !dlg.bSetDlgInfo(  pObjDb,  misServName,  uiType,  &idInfo,  FALSE  )  )  goto  errLabel;
					   			//
					   			if  (  dlg.DoModal(  )  ==  IDOK  &&  dlg.m_var.ucbChanged  )  ucbRefreshed  =  TRUE;							    
								#endif
								unsigned  char  ucbChanged  =  FALSE;
								if  (  showDlgQnmEditPcUsrInfo(  NULL,    pObjDb,  misServName,  uiType,  &idInfo,  FALSE,  &ucbChanged  )  !=  IDOK  )  goto  errLabel;
								if  (  ucbChanged  )  ucbRefreshed  =  TRUE;
								}
								break;
						  case  ID_qyEditPcUsrInTab1:  {
								#if  0  //  ndef  __isCli__
							    CDlgQnmEditPcUsrInfo		dlg;
					   			//
					   			if  (  !dlg.bSetDlgInfo(  pObjDb,  misServName,  uiType,  &idInfo,  TRUE  )  )  goto  errLabel;
					   			// 
				   	   			if  (  dlg.DoModal(  )  ==  IDOK  &&  dlg.m_var.ucbChanged  )  ucbRefreshed  =  TRUE;
								#endif

								unsigned  char  ucbChanged  =  FALSE;
								if  (  showDlgQnmEditPcUsrInfo(  NULL,    pObjDb,  misServName,  uiType,  &idInfo,  TRUE,  &ucbChanged  )  !=  IDOK  )  goto  errLabel;
								if  (  ucbChanged  )  ucbRefreshed  =  TRUE;
								
							    }
							    break;
				 		  case  ID_qyProperties:  {
#if  0
							    CDlgPropMessenger		dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
					   			//
					   			if  (  !dlg.bSetDlgInfo(  pObjDb,  misServName,  uiType,  &idInfo  )  )  goto  errLabel;
					   			dlg.DoModal(  );
#endif
								if  (  showDlgPropMessenger(  pEventInfo->hWnd,  pObjDb,  misServName,  uiType,  &idInfo  )  !=  IDOK  )  goto  errLabel;
					   		    }
					   		    break;

				 		  case  ID_qyDel:
							    if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeleteContact  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								delImObj(  pObjDb->pDb,  pObjDb->cfg.iDbType,  pQyMc->iAppType  ==  CONST_qyAppType_client,  misServName,  &idInfo  );
								ucbRefreshed  =  TRUE;
					   			break;
						  case  ID_qyDelPcUsr:
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeleteRegInfo  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
									time(  &pParam->t  );
								}
#if  0
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyImObjRegInfoTab,  atol(  buf  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
								if  (  !g_dbFuncs.pf_bDeleteFromTabById(  pObjDb->pDb,  pObjDb->cfg.iDbType,  CONST_tabName_qyImObjRegInfoTab,  atol(  buf  )  )  )  goto  errLabel;
								//
								ucbRefreshed  =  TRUE;
								iErr  =  0;  goto  errLabel;
							    break;
						  case  ID_qyDelPcUsrInTab1:  
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeleteTmpRegInfo  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
									time(  &pParam->t  );
								}
#if  0
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyImObjRegInfoTab1,  atol(  buf  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
								if  (  !g_dbFuncs.pf_bDeleteFromTabById(  pObjDb->pDb,  pObjDb->cfg.iDbType,  CONST_tabName_qyImObjRegInfoTab1,  atol(  buf  )  )  )  goto  errLabel;
								//
								ucbRefreshed  =  TRUE;
								iErr  =  0;  goto  errLabel;
							    break;
						  case  ID_qyImGrpList:
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImObjTab.idStr in (select idStr_grp from qyImGrpMemTab where qyImGrpMemTab.misServName=%s and qyImGrpMemTab.idStr_mem='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  idInfo.ui64Id  );
                                bViewImGrpList(  pQyMc,  pObjDb,  CString(  tBuf  ),  sqlBuf  );
								break;
						  case  ID_qyTalk:
							    if  (  uiType  ==  CONST_objType_me  ||  uiType  ==  CONST_objType_admin  )  break;	
								//
								memset(  &addr,  0,  sizeof(  addr  )  );
								addr.uiObjType  =  uiType;
								addr.idInfo.ui64Id  =  idInfo.ui64Id;
								//
							    //  if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;
								if  (  pFuncs->pf_tryToTalkToMessenger(  mynull,&addr,  0,  0,  TRUE,  NULL,  0,  NULL  )  )  goto  errLabel;
							    break;
						  case  ID_qySendSm:
							    memset(  &addr,  0,  sizeof(  addr  )  );
								lstrcpyn(  addr.misServName,  misServName,  mycountof(  addr.misServName  )  );
								addr.uiObjType  =  uiType;
								addr.idInfo.ui64Id  =  idInfo.ui64Id;
								addr.uiDevType  =  CONST_objType_phone;
								//
								if  (  getSelectedToPath(  pObjDb,  _T(  ""  ),  FALSE,  addr.wPath,  mycountof(  addr.wPath  )  )  )  goto  errLabel;
								addr.bInNoticeMode  =  TRUE;
								//
								//  if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;
								if  (  pFuncs->pf_tryToTalkToMessenger(  mynull,&addr,  0,  0,  TRUE,  NULL,  0,  NULL  )  )  goto  errLabel;
								//
							    break;
						  case  ID_qyCfgStandardName:  {
								#ifndef  __isCli__
							    CDlgCfgStandardName		dlg;
								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  misServName,  &idInfo,  0  )  )  goto  errLabel;
								dlg.DoModal(  );
								#endif
							    }				
				   			    break;
						  case  ID_qyPhoneMessengerList:
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyMessengerPhoneInfoTab.misServName=%s and qyMessengerPhoneInfoTab.idStr='%s'"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								bViewPhoneMessengerList(  pQyMc,  pObjDb,  displayName,  sqlBuf  );
							    break;
						  case  ID_qyAddPhone:  {
								#ifndef  __isCli__
							    CDlgCfgPhoneMessenger		dlg;

								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  NULL,  FALSE,  &idInfo,  0  )  )  goto  errLabel;
								if  (  dlg.DoModal(  )  ==  IDOK  )  ucbRefreshed  =  TRUE;
								#endif
								iErr  =  0;  goto  errLabel;
								}		    
							    break;
						  case  ID_qyDelPhone:  {
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr( 0,  &pQyMc->cusRes,  CONST_resId_askIfDeletePhoneNumber  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								}
#if  0
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyMessengerPhoneInfoTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
								if  (  !g_dbFuncs.pf_bDeleteFromTabByIdInfo(  pObjDb->pDb,  pObjDb->cfg.iDbType,  CONST_tabName_qyMessengerPhoneInfoTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  &idInfo  )  )  goto  errLabel;

								ucbRefreshed  =  TRUE;
								}
							    break;
						  case  ID_cfgCustomerService:  {
								#ifndef  __isCli__
							    CDlgCfgCustomerService	dlg;

								if  (  uiType  !=  CONST_objType_messenger  )  goto  errLabel;
								if  (  !dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  pObjDb,  misServName,  &idInfo,  0  )  )  goto  errLabel;
								if  (  dlg.DoModal(  )  !=  IDOK  )  break;
								#endif
								//
								ucbRefreshed  =  TRUE;
								}
							    break;
				 		  default:
								 #ifdef  __DEBUG__
										 traceLogA(  "messenger: unprocessed cmd: %d",  uiCmd  );
								 #endif
								 goto  errLabel;
								 break;				   
				  }
				  break;
			case  CONST_objType_imGrp:
				  switch  (  uiCmd  )  {
						  case  ID_qyProperties:   {
#if  0
						   	    CDlgPropImGrp		dlg;

								if  (  !dlg.bSetDlgInfo(  pObjDb,  _T(  ""  ),  &idInfo  )  )  break;
									
								dlg.DoModal(  );
#endif
								if  (  showDlgPropImGrp(  NULL,  pObjDb,  _T(  ""  ),  &idInfo  )  !=  IDOK  )  break;
								}
							    break;
						  case  ID_qyDiscuss:												   
							    //  
							    if  (  pFuncs->pf_tryToTalkToMessenger_id(  mynull,idInfo.ui64Id,  0,  TRUE,  NULL,  0,  NULL  )  )  goto  errLabel;
								break;
						  case  ID_qyRule:  {
								#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
#if  0
							    CDlgImObjRule	dlg;
								if  (  !dlg.bSetDlgInfo(  _T(  ""  ),  &idInfo  )  )  goto  errLabel;
								if  (  dlg.DoModal(  )  !=  IDOK  )  break;
#endif
								if  (  showDlgImObjRule(  NULL,  _T(  ""  ),  &idInfo  )  !=  IDOK  )  break;
								//
								ucbRefreshed  =  TRUE;
								#endif
								}							    
							    break;
						  case  ID_qyImGrpMemList:  {
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImGrpMemTab.misServName=%s and qyImGrpMemTab.idStr_grp='%s'"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								bViewImGrpMemList_isClient(  pQyMc,  pObjDb,  displayName,  sqlBuf  );
								}
							    break;
						  case  ID_qyDel:
							    if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_reallyToDelete ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								delImObj(  pObjDb->pDb,  pObjDb->cfg.iDbType,  pQyMc->iAppType  ==  CONST_qyAppType_client,  misServName,  &idInfo  );
								ucbRefreshed  =  TRUE;
								//
								//  É¾³ý×éÒªÍ¨Öª·þÎñÆ÷Ë¢ÐÂ
								if  (  applyForServWork(  CONST_imCommType_refreshImGrp,  CONST_imOp_refresh,  &idInfo,  0,  0  )  )  goto  errLabel;
								//
					   			break;
						  case  ID_qyEdit:  {
								#ifndef  __isCli__
							    CDlgImGrp			dlg;

								if  (  !dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  pObjDb,  misServName,  &idInfo  )  )  goto  errLabel;
								if  (  dlg.DoModal(  )  !=  IDOK  )  break;
								//
								ucbRefreshed  =  TRUE;
								#endif
								}
							    break;
						  default:
								 #ifdef  __DEBUG__
										 traceLogA(  "imGrp: unprocessed cmd: %d",  uiCmd  );
								 #endif
								 goto  errLabel;
								 break;
				  }
				  iErr  =  0;  goto  errLabel;							  
				  break;

			default:
					#ifdef  __DEBUG__
							traceLogA(  "procLvEventFunc_imObj:  Î´´¦ÀíµÄuiType is %d",  uiType  );
					#endif
					break;
		
	 }

	iErr  =  0;  
		 
errLabel:
		 if  (  !iErr  )  {
			 pEventInfo->ucbRefreshed  =  ucbRefreshed;
		 }
		 return  iErr;
		 
}

  //  2013/02/20
  int  procLvEventFunc_isCli(  QY_OBJ_DB  *  pObjDb,  QY_EVENTINFO  *  pEventInfo,  int  iLvType  )
{
	int								iErr			=		-1;
	QY_MC						*	pQyMc			=		QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp			*	pFuncs			=  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs   ) return  -1;
	//
	PARAM_procLvEventFunc_is		param;
				   
	memset(  &param,  0,  sizeof(  param  )  );
	if  (  initGenericQ(  _T(  "procLv_tmpQ"  ),  NULL,  0,  CONST_uiMaxQNodes_tmpGrpMemQ,  mymalloc,  myfree,  &param.tmpGrpMemQ  )  )  goto  errLabel;
	param.bTmpQInited  =  TRUE;

	enumLvSelEventFunc(  pEventInfo,  tmpHandler_procLvEventFunc_isCli,  pObjDb,  iLvType,  (  void  *  )&param  );

	//  
	if  (  pEventInfo->uiCmd  ==  ID_qySendSm  )  {
		if  (  !isQEmpty(  &param.tmpGrpMemQ  )  )  {
			MSGR_ADDR	addr;
			BOOL		bPhoneGuest	=	FALSE;

			switch  (  iLvType  )  {
					case  CONST_qyQueryType_phoneGuestList:
						  bPhoneGuest  =  TRUE;
						  break;
					default:
							break;
			}

			//
			MACRO_prepareForTran(  );
			//
			memset(  &addr,  0,  sizeof(  addr  )  );
			addr.uiObjType  =  CONST_objType_tmpGrp;
			if  (  getSelectedToPath(  pObjDb,  _T(  ""  ),  bPhoneGuest,  addr.wPath,  mycountof(  addr.wPath  )  )  )  goto  errLabel;
			addr.bInNoticeMode  =  TRUE;
			addr.tStartTime_notice  =  tStartTran;
			addr.uiTranNo_notice  =  uiTranNo;
			//
			//  if  (  talkToMessenger(  pQyMc,  &addr,  &param.tmpGrpMemQ,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;      
			if  (  pFuncs->pf_tryToTalkToMessenger(  mynull,&addr,  0,  0,  TRUE,  NULL,  0,  NULL  )  )  goto  errLabel;      
		}
		}
	else  {
		  if  (  param.param_applyForServWork.uiType  )  {
			  if  (  applyForServWork(  param.param_applyForServWork.uiType,  param.param_applyForServWork.usOp,  param.param_applyForServWork.p0,  param.param_applyForServWork.p1,  param.param_applyForServWork.p2  )  )  goto  errLabel;
		  }
	}

	iErr  =  0;
errLabel:
	if  (  param.bTmpQInited  )  exitGenericQ(  &param.tmpGrpMemQ  );
	return  iErr;
}



 //
 int  is_procLvEventFunc_new(  void  *  pQyMcParam,  void  *  pm_docStructParam,  void  *  pSelParam,  void  *  pEventInfoParam,  unsigned  int  uiCmd,  LPCTSTR  colName  )
{
	 int						iErr								=	-1;
	 QY_MC					*	pQyMc								=	(  QY_MC  *  )pQyMcParam;
	 //  CQyMcDoc				*	pDoc								=	(  CQyMcDoc  *  )NULL;	//  pDocParam;
	 QY_MC_DOCSTRUCT		*	pm_docStruct						=	(  QY_MC_DOCSTRUCT  *  )pm_docStructParam;
 	 QY_MC_SEL				*	pSel								=	(  QY_MC_SEL  *  )pSelParam;
	 QY_EVENTINFO			*	pEventInfo							=	(  QY_EVENTINFO  *  )pEventInfoParam;
	 HWND						hParent								=	pEventInfo->hWnd;
	 char						buf[255];
	 TCHAR						tBuf[256];
	 char						tmpBuf[256];
	 int						curnItem							=	0;
	 QY_WMBUF_COMM				tmpComm;
	 CString					sqlStr;
	 TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	 CDBVariant					varVals[10];
	 unsigned  char				ucbRefreshed						=	TRUE;
	 QNM_CHKEDIP_STRUCT			chkedPc;
	 QNM_EVENT					nmEvent;
	 int						iSelId								=	-1;
	 unsigned  int				uiType;
	 QY_OBJ_DB				*	pObjDb								=	NULL;
	 int						iLvType								=	0;
	 PF_commonHandler			pfProcCmd							=	NULL;

	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	 if  (  !pm_docStruct  )  pObjDb  =  getObjDbFromSel(  pSel  );
	 else  {
		   if  (  pm_docStruct->iDocType  ==  CONST_qyDocType_mcQuery  )  pObjDb  =  getProcedObjDb(  pQyMc,  0,  pm_docStruct->u.query.iDsnIndex  );		 
	 }
	 

	 if  (  pSel  )  {
		 if  (  pSel->type  ==  CONST_qySelType_mcRootList  )  {

			 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

			 QY_OBJINDEX_RCD	*	pObjIndex	=	&pSel->u.rootList.leftTreeSel.objIndex;
			 switch  (  pSel->u.rootList.leftTreeSel.objIndex.objType  )  {
					 default:
							//  2005/01/31ÐÞ¸Ä£¬ÎªÊ¹Ë«»÷ÄÜÓÅÏÈÌø×ªµ½ÏàÓ¦µÄ½Úµã
			 				if  (  uiCmd  ==  ID_dblClickToFocusOnItem  )  {
								dblClickToOpenItem(  pQyMc,  pSel,  pEventInfo  );
								iErr  =  0;  goto  errLabel;
							}
							if  (  pSel->u.rootList.leftTreeSel.objIndex.objType  ==  CONST_objType_cfgSpOs  )  {
								if  (  getSelIdFromLv(  hParent,  &iSelId  )  )  goto  errLabel;
								if  (  uiCmd  ==  ID_qyProperties  )  {
									//  showOsSpInfo(  pObjDb->pDb,  iSelId  );  
									ucbRefreshed  =  FALSE;
									iErr  =  0;  goto  errLabel;
								}
							}

							break;
		   
			 }
		 }
	 }


	 if  (  (  iLvType  =  getLvTypeFromSth_new(  pm_docStruct,  pSel,  NULL,  0,  &pfProcCmd  )  )  <  0  )  goto  errLabel;
	 if  (  pfProcCmd  )  {
		 if  (  pfProcCmd(  0,  pSel,  pEventInfo  )  )  goto  errLabel;
		 ucbRefreshed  =  pEventInfo->ucbRefreshed;
		 iErr  =  0;  goto  errLabel;
	 }
	 //
	 switch  (  iLvType  )  {
			 case  CONST_qyQueryType_imObjAuthList:
			 case  CONST_qyQueryType_imAmList:
			 case  CONST_qyQueryType_imObjList:
			 case  CONST_qyQueryType_imGrpAuthList:
			 case  CONST_qyQueryType_imGrpList:
			 case  CONST_qyQueryType_imGrpMemList:
			 case  CONST_qyQueryType_imObjRegInfoList:
			 case  CONST_qyQueryType_imObjRegInfoInTab1List:
			 case  CONST_qyQueryType_imObjAuthNeedAuditedList:
			 case  CONST_qyQueryType_imGrpAuthNeedAuditedList:
			 case  CONST_qyQueryType_clientList_is:
			 case  CONST_qyQueryType_customerServiceList:
			 case  CONST_qyQueryType_wwwQmCfgList:
			 case  CONST_qyQueryType_ipKnowledgeList:
			 case  CONST_qyQueryType_phoneGuestList:
			 case  CONST_qyQueryType_tmpGrpMemList:
			 case  CONST_qyQueryType_imTaskList:
			 case  CONST_qyQueryType_imTaskHisList:
			 case  CONST_qyQueryType_imMsgList:
			 case  CONST_qyQueryType_gsmModemList:
			 case  CONST_qyQueryType_smContactList:
			 case  CONST_qyQueryType_phoneMessengerList:
			 case  CONST_qyQueryType_instantAssistantMemList:
			 case  CONST_qyQueryType_sharedDynBmpList:
			 case  CONST_qyQueryType_sharedDynBmpRuleList:
			 case  CONST_qyQueryType_imObjRuleList:
			 case  CONST_qyQueryType_talk_imGrpMemList:
				   pEventInfo->uiCmd  =  uiCmd;
				   //
				   if  (  procLvEventFunc_isCli(  pObjDb,  pEventInfo,  iLvType  )  )  goto  errLabel;
				   //
				   ucbRefreshed  =  pEventInfo->ucbRefreshed;
				   iErr  =  0;  goto  errLabel;
				   break;
			 default:
					break;
	 }




	 //  2004/04/11, ½«ÉÏÃæµÄÄÚÈÝÓÃÏÂÃæµÄº¯ÊýÀ´Ìæ»»
	 if  (  getLvSelColContent(  hParent,  &curnItem,  colName,  tBuf,  mycountof(  tBuf  )  )  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  "netMc_procEventFunc´íÎó: Ã»ÓÐÕÒµ½À¸Ä¿%sÏàÓ¦µÄÄÚÈÝ",  colName  );  
		 #endif
		 goto  errLabel;
	 }
	 myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
 	
	 if  (  !buf[0]  )  {
		 ucbRefreshed  =  FALSE;
		 iErr  =  0;  goto  errLabel;
	 }
	 
	 if  (  pSel  &&  pSel->type  ==  CONST_qySelType_mcView  &&  pSel->u.mcView.type  ==  CONST_qyLvType_procedObjList  )  {

		 switch  (  uiCmd  )  {
                 case  ID_loadProcedObj:
					   if  (  loadProcedObj(  pQyMc,  0,  (  void  *  )atol(  buf  )  )  )  {
						   qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_loadDataSourceFailed  )  );  goto  errLabel;
					   }
					   iErr  =  0;  goto  errLabel;
					   break;
				 case  ID_unloadProcedObj:  {
					   qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unloadDataSourceFailed  )  );  goto  errLabel;
					   }
					   iErr  =  0;  goto  errLabel;
					   break;
				 default:
					    break;
		 }

		 pObjDb  =  getProcedObjDb(  pQyMc,  0,  atol(  buf  )  );
		 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

		 if  (  pObjDb->cfg.iSystemId  ==  CONST_qySystemId_messenger  )  {
			 switch  (  uiCmd  )  {
					 case  ID_qyMessengerView:
						   bViewImObjView(  pObjDb  );  
						   break;
					 case  ID_qyMessengerAuthList:
						   #ifndef		__isCli__
						   bViewImObjAuthList_isMgr(  pObjDb,  _T(  ""  ),  _T(  ""  )  );
						   #endif
						   break;
					 case  ID_qyMessengerAuthList_needAudited:
						   #ifndef		__isCli__
						   bViewImObjAuthNeedAuditedList_isMgr(  pObjDb,  _T(  ""  ),  _T(  ""  )  );
						   #endif
						   break;
				     case  ID_qyMessengerList:
					   	   bViewMessengerList(  pQyMc,  pObjDb,  _T(  ""  ),  _T(  ""  )  );
						   break;
					 case  ID_qyPcUsrList:
						   bViewObjRegInfoList(  pQyMc,  pObjDb  );						   
						   break;
					 case  ID_qyPcUsrInTab1List:	
						   bViewObjRegInfoInTab1List(  pQyMc,  pObjDb  );						   
						   break;
					 case  ID_qyImGrpAuthList:		
						   bViewImGrpAuthList(  pObjDb,  _T(  ""  ),  _T(  ""  )  );  
						   break;
					 case  ID_qyImGrpList:
						   bViewImGrpList(  pQyMc,  pObjDb,  _T(  ""  ),  _T(  ""  )  );
						   break;
					 case  ID_qyImGrpMemList:
						   bViewImGrpMemList_isClient(  pQyMc,  pObjDb,  _T(  ""  ),  _T(  ""  )  );
						   break;
					 case  ID_qwmSvrList:
						   bViewClientList(  pQyMc,  pObjDb  );
						   break;
					 case  ID_imTaskList_unproced:
						   g_dbFuncs.pf_bViewImTaskList_unproced(  pObjDb,  _T(  ""  ),  _T(  ""  )  );
						   break;
					 case  ID_imTaskList_cur:
						   //  bViewImTaskListFunc(   pObjDb,  _T(  "当前"  ),  _T(  ""  ),  FALSE  );
						   g_dbFuncs.pf_bViewImTaskList_cur(  pObjDb,  _T(  "当前"  ),  _T(  ""  )  );
						   break;
					 case  ID_imTaskList_his:
						   //  bViewImTaskListFunc(  pObjDb,  _T(  "历史"  ),  _T(  ""  ),  TRUE  );
						   g_dbFuncs.pf_bViewImTaskList_his(  pObjDb,  _T(  "历史"  ),  _T(  ""  )  );
						   break;
					 case  ID_qyMsgToday:
						   bViewImMsgToday(  pQyMc,pObjDb,  NULL  );		
						   break;
					 case  ID_qyMsgList:
						   bViewImMsgListFunc(  pQyMc,  pObjDb,  NULL,  NULL  );
						   break;
					 case  ID_qyEventAll:
						   bViewAllEventList(  pQyMc,  pObjDb  );
						   break;
					 case  ID_qyOpEventAll:
						   bViewAllOpEventList(  pQyMc,  pObjDb  );
						   break;
					 default:
							break;
			 }

			 iErr  =  0;  goto  errLabel;
		 }

		 switch  (  uiCmd  )  {

				 case  ID_qyScannedIpList:
					   if  (  !bNetMcViewScannedIpList(  pQyMc,  pObjDb  )  )  goto  errLabel;					     
					   break;
				 case  ID_qyPcView:
					   if  (  !bNetMcViewPcView(  pObjDb  )  )  goto  errLabel;					     
					   break;
				 case  ID_qyAssetsView:
					   if  (  !bNetMcViewAssets(  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_qyPcList:
					   if  (  !bNetMcViewPcList(  pQyMc,  pObjDb  )  )  goto  errLabel;		
					   break;
				 case  ID_qyPcUsrList:
					   if  (  !bViewObjRegInfoList(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_qyPcUsrInTab1List:
					   if  (  !bViewObjRegInfoInTab1List(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_qwmSvrList:
					   if  (  !bViewClientList(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_pcRuleList0:
					   if  (  !bNetMcViewPcRuleList(  pQyMc,  pObjDb,  0  )  )  goto  errLabel;
					   break;
				 case  ID_pcRuleList1:
					   if  (  !bNetMcViewPcRuleList(  pQyMc,  pObjDb,  1  )  )  goto  errLabel;
					   break;
				 case  ID_pcSecChkEventList:
					   if  (  !bNetMcViewPcSecChkEventList(  pQyMc,  pObjDb,  _T(  ""  ),  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcRegistryList:
					   if  (  !bNetMcViewPcRegistryPropList(  pQyMc,  pObjDb,  _T(  ""  ),  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcRegistryRuleStatusList:
					   if  (  !bNetMcViewPcRegistryRuleStatusList(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcEventLogList:
					   if  (  !bNetMcViewPcEventLogList(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcOsUsrList:
					   if  (  !bNetMcViewPcOsUsrList(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_qyPcNetStatList:
					   if  (  !bNetMcViewPcNetStatList(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcPrinterPropList:
					   if  (  !bNetMcViewPcPrinterPropList(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;

				 case  ID_pcNetworkPropList:
					   if  (  !bNetMcViewPcNetworkPropList(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcNetworkRuleList:
					   if  (  !bNetMcViewPcNetworkRuleList(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcProxyCfgPropList:
					   if  (  !bNetMcViewPcProxyCfgPropList(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcProxyCfgRuleList:
					   if  (  !bNetMcViewPcProxyCfgRuleList(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
			#if  0
				 case  ID_pcComputerPropList:
					   if  (  !bNetMcViewPcComputerPropList(  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcComputerRuleList:
					   if  (  !bNetMcViewPcComputerRuleList(  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
			#endif
				 case  ID_qyPcSpList:
					   if  (  !bNetMcViewPcSpList(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_pcWindowsUpdatePolicyPropList:
					   if  (  !bNetMcViewPcWindowsUpdatePolicyPropList(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcWindowsUpdatePolicyRuleList:
					   if  (  !bNetMcViewPcWindowsUpdatePolicyRuleList(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcProcessPropList:
					   if  (  !bNetMcViewPcProcessPropList(  pQyMc,  pObjDb,  _T(  ""  ),  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcProcessModulePropList:
					   if  (  !bNetMcViewPcProcessModulePropList(  pQyMc,  pObjDb,  _T(  ""  ),  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcProcessRuleList:
					   if  (  !bNetMcViewPcProcessRuleList(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcNetFlowPropList_ethernet:
					   if  (  !bNetMcViewPcNetFlowPropList_ethernet(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcNetFlowPropList:
					   if  (  !bNetMcViewPcNetFlowPropList(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
				 case  ID_pcNetSharePropList:
					   if  (  !bNetMcViewPcNetSharePropList(  pQyMc,  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
#if  0
				 case  ID_autoLogonList:
					   //  if  (  !bNetMcViewPcAutoLogonList(  pObjDb,  _T(  ""  )  )  )  goto  errLabel;
					   break;
#endif
				 case  ID_qyEventAll:
					   if  (  !bViewAllPcEventList_netMc(  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_qyNetDevEventAll:
					   if  (  !bNetMcViewAllNetDevEventList(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_qyRas:
					   if  (  !bNetMcViewRasEventList(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_qyProxyServer:
					   if  (  !bNetMcViewProxyServerEventList(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_qyOnInternet:
					   if  (  !bNetMcViewOnInternetEventList(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_qyIntraConn:
					   if  (  !bNetMcViewIntraConnEventList(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_qyDevChanged:
					   if  (  !bNetMcViewDevChangedEventList(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_qyQwmDel:
					   if  (  !bNetMcViewQwmDelEventList(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_qyOpEventAll:
					   if  (  !bViewAllOpEventList(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
#if  0
				 case  ID_qyReportAssetsInfo_byMac:
					   if  (  !bNetMcViewPcAssetReport(  pObjDb,  CONST_langId_PRC,  TRUE  )  )  goto  errLabel;
					   break;
				 case  ID_qyReportAssetsInfo_byOs:
					   if  (  !bNetMcViewPcAssetReport(  pObjDb,  CONST_langId_PRC,  FALSE  )  )  goto  errLabel;
					   break;
				 case  ID_qyReportAssetsInfo_en_byMac:
					   if  (  !bNetMcViewPcAssetReport(  pObjDb,  CONST_langId_US,  TRUE  )  )  goto  errLabel;
					   break;
				 case  ID_qyReportAssetsInfo_en_byOs:
					   if  (  !bNetMcViewPcAssetReport(  pObjDb,  CONST_langId_US,  FALSE  )  )  goto  errLabel;
					   break;
#endif
				 case  ID_qyNetworkView:
					   if  (  !bNetMcViewNetwork(  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_qyConnectionView:
					   if  (  !bNetMcViewUsrConnection(  pObjDb )  )  goto  errLabel;	
					   break;
				 case  ID_qyNetworkSpeedView:
					   if  (  !bNetMcViewNetworkSpeed(  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_snmpObjRuleList:
					   if  (  !bNetMcViewSnmpObjRuleList(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_conflictConnList:
					   if  (  !bNetMcViewConflictConnList(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_directConnList:
					   if  (  !bNetMcViewDirectConnList(  pQyMc,  pObjDb  )  )  goto  errLabel;
					   break;
				 case  ID_qySearch_netDevEvent:
					   doQnmSearch(  CONST_qyQueryType_netDevEventList  );
					   break;
				 case  ID_qySearch_pcEvent:
					   doQnmSearch(  CONST_qyQueryType_netMcEventList  );
					   break;
				 case  ID_qySearch_pcList:
					   doQnmSearch(  CONST_qyQueryType_netMcPcList  );
					   break;
				 case  ID_qySearch_pcSpList:
					   doQnmSearch(  CONST_qyQueryType_netMcPcSpList  );	
					   break;
				 case  ID_qySearch_mac:
					   doQnmSearch(  CONST_qyQueryType_mac  );
					   break;
				 case  ID_qySearch_ip:
					   doQnmSearch(  CONST_qyQueryType_ip  );
					   break;
				 case  ID_qySearch_unusedConn:
					   doQnmSearch(  CONST_qyQueryType_unusedConn  );
					   break;
			     //
				 default:
					    traceLogA(  "mcViewÀïÎ´Ö§³ÖµÄÃüÁî: %d",  uiCmd  );
					    goto  errLabel;
		 }

		 iErr  =  0;  goto  errLabel;

	 }


	 switch  (  uiCmd  )  {
			 case  ID_qyCfgPcRule:  {
#if  0
			 	   CDlgQnmCfgPcRule		dlg;
				
				   if  (  !dlg.bSetDlgInfo(  pObjDb,  buf  )  )  goto  errLabel;
				   dlg.DoModal(  );
#endif
	
					}
				   break;
			 case  ID_qyCfgStandardName:  {
#if  0
			       CDlgCfgStandardName	dlg;
				   if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  buf,  0  )  )  goto  errLabel;
				   dlg.DoModal(  );
#endif
				   }				
				   break;
			 case  ID_viewRemoteDesktop:  {
#if  0
				   QNM_PC_INFO  pcInfo;  QNM_REG_INFO  regInfo;
			
				   viewRemoteDesktop(  pObjDb->pDb,  0,  buf,  0  );
				   memset(  &pcInfo,  0,  sizeof(  pcInfo  )  );  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
				   if  (  !bGetPcInfoByMacEx(  pObjDb->pDb,  buf,  TRUE,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &pcInfo,  &regInfo,  0  )  )  {
					   memset(  &pcInfo,  0,  sizeof(  pcInfo  )  );  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
				   }
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %s"  ),  CString(  pcInfo.pcName  ),  CString(  pcInfo.ip  ),  CString(  pcInfo.macs[0]  )  );
				   qnmLogOpEvent(  pQyMc->iServiceId,  pObjDb,  CONST_qyEventType_nm_viewRemoteDesktop,  tBuf  );
				   //
#endif
				   }
				   break;
			 case  ID_cancelRemoteDesktop:  {
#if  0
				   QNM_PC_INFO  pcInfo;  QNM_REG_INFO  regInfo;

				   cancelRemoteDesktop(  pObjDb->pDb,  0,  buf,  0  );
				   if  (  !bGetPcInfoByMacEx(  pObjDb->pDb,  buf,  TRUE,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &pcInfo,  &regInfo,  0  )  )  {
					   memset(  &pcInfo,  0,  sizeof(  pcInfo  )  );  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
				   }
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %s"  ),  CString(  pcInfo.pcName  ),  CString(  pcInfo.ip  ),  CString(  pcInfo.macs[0]  )  );
				   qnmLogOpEvent(  pQyMc->iServiceId,  pObjDb,  CONST_qyEventType_nm_cancelRemoteDesktop,  tBuf  );
#endif
				   }
				   break;
			 case  ID_monDesktop:  {						//  2006/03/06
#if  0
				   QNM_PC_INFO  pcInfo;  QNM_REG_INFO  regInfo;
				   
				   memset(  &pcInfo,  0,  sizeof(  pcInfo  )  );  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
				   if  (  !bGetPcInfoByMacEx(  pObjDb->pDb,  buf,  TRUE,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &pcInfo,  &regInfo,  0  )  )  {
					    memset(  &pcInfo,  0,  sizeof(  pcInfo  )  );  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
				   }
				   if  (  (  (  TCHAR  *  )regInfo.u.cols[getRegIndexByFieldId(  CONST_fieldId_syr  )]  )[0]  )  {
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s-%s-%s"  ),  regInfo.u.cols[getRegIndexByFieldId(  CONST_fieldId_dw  )],  regInfo.u.cols[getRegIndexByFieldId(  CONST_fieldId_bm  )],  regInfo.u.cols[getRegIndexByFieldId(  CONST_fieldId_syr  )]  );
				   }
				   else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  CString(  pcInfo.ip  )  );

				   if  (  startDesktopMon(  0,  buf,  tBuf  )  )  goto  errLabel;
				   //
				   viewRemoteDesktop(  pObjDb->pDb,  0,  buf,  TRUE  );
				   //
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %s"  ),  CString(  pcInfo.pcName  ),  CString(  pcInfo.ip  ),  CString(  pcInfo.macs[0]  )  );
				   qnmLogOpEvent(  pQyMc->iServiceId,  pObjDb,  CONST_qyEventType_nm_monDesktop,  tBuf  );
				   //
#endif
				   }						
				   break;
			 case  ID_cancelMonDesktop:  {				//  2006/03/06
#if  0
				   QNM_PC_INFO  pcInfo;  QNM_REG_INFO  regInfo;
				
				   cancelRemoteDesktop(  pObjDb->pDb,  0,  buf,  TRUE  );
				   //
				   stopDesktopMon(  0,  buf,  0  );
				   //
				   if  (  !bGetPcInfoByMacEx(  pObjDb->pDb,  buf,  TRUE,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &pcInfo,  &regInfo,  0  )  )  {
					   memset(  &pcInfo,  0,  sizeof(  pcInfo  )  );  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
				   }
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %s"  ),  CString(  pcInfo.pcName  ),  CString(  pcInfo.ip  ),  CString(  pcInfo.macs[0]  )  );
				   qnmLogOpEvent(  pQyMc->iServiceId,  pObjDb,  CONST_qyEventType_nm_cancelMonDesktop,  tBuf  );
#endif
				   }
				   break;
			 case  ID_queryNetworkProp:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcNetworkPropList(  pQyMc,  pObjDb,  sqlBuf  );
				   break;
			 case  ID_queryProxyCfg:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcProxyCfgPropList(  pQyMc,  pObjDb,  sqlBuf  );
				   break;
#if  0
			 case  ID_queryComputerInfo:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcComputerPropList(  pObjDb,  sqlBuf  );
				   break;
#endif
			 case  ID_queryPcWindowsUpdatePolicyProp:			//  2006/05/23
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcWindowsUpdatePolicyPropList(  pQyMc,  pObjDb,  sqlBuf  );
				   break;
			       //  {  ÏÂÃæÊÇ¼à¿ØÓëÉó¼Æ
			 case  ID_pcSecChkEventList:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcSecChkEventList(  pQyMc,  pObjDb,  _T(  ""  ),  sqlBuf  );
				   break;
			 case  ID_pcRegistryList:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcRegistryPropList(  pQyMc,  pObjDb,  _T(  ""  ),  sqlBuf  );					
				   break;
			 case  ID_pcRegistryRuleStatusList:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcRegistryRuleStatusList(  pQyMc, pObjDb,  sqlBuf  );					
				   break;
			 case  ID_pcEventLogList:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcEventLogList(  pQyMc,  pObjDb,  sqlBuf  );					     
				   break;
			 case  ID_pcOsUsrList:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcOsUsrList(  pQyMc,  pObjDb,  sqlBuf  );
				   break;
			 case  ID_qyPcNetStatList:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcNetStatList(  pQyMc,  pObjDb,  sqlBuf  );
				   break;
			 case  ID_pcPrinterPropList:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcPrinterPropList(  pQyMc,  pObjDb,  sqlBuf  );
				   break;
			 case  ID_pcProcessPropList:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcProcessPropList(  pQyMc,  pObjDb,  _T(  ""  ),  sqlBuf  );
				   break;
			 case  ID_pcProcessModulePropList:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcProcessModulePropList(  pQyMc,  pObjDb,  _T(  ""  ),  sqlBuf  );
				   break;
			 case  ID_pcNetFlowPropList:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcNetFlowPropList(  pQyMc,  pObjDb,  sqlBuf  );
				   break;
			 case  ID_pcNetFlowPropList_ethernet:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcNetFlowPropList_ethernet(  pQyMc,  pObjDb,  sqlBuf  );					   
				   break;
			 case  ID_pcNetSharePropList:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   if  (  !bNetMcViewPcNetSharePropList(  pQyMc,  pObjDb,  sqlBuf  )  )  goto  errLabel;
				   break;
			 case  ID_qyPcSpList:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyPcTab.mac0='%s'"  ),  CString(  buf  )  );
				   bNetMcViewPcSpListFunc(  pQyMc,  pObjDb,  _T(  ""  ),  sqlBuf  );
				   break;
				   //  }
			 case  ID_qyEdit:  {
#if  0
				   CDlgQnmEditPcUsrInfo		dlg;
				   //
				   if  (  !dlg.bSetDlgInfo(  pObjDb,  0,  buf,  FALSE  )  )  goto  errLabel;
				   //
				   if  (  dlg.DoModal(  )  !=  IDOK  ||  !dlg.m_var.ucbChanged  )  {
					   ucbRefreshed  =  FALSE;
				   }
#endif
				   unsigned  char  ucbChanged  =  FALSE;
				   if  (  showDlgQnmEditPcUsrInfo(  NULL,  pObjDb,  0,  buf,  FALSE,  &ucbChanged  )  !=  IDOK  ||  !ucbChanged  )  {
					   ucbRefreshed  =  FALSE;
				   }

				   }
				   break;
			 case  ID_qyEditPcUsrInTab1:  {
#if  0
				   CDlgQnmEditPcUsrInfo		dlg;

				   dlg.bSetDlgInfo(  pObjDb,  0,  buf,  TRUE  );
				   if  (  dlg.DoModal(  )  !=  IDOK  ||  !dlg.m_var.ucbChanged  )  {
					   ucbRefreshed  =  FALSE;
				   }
#endif
				   unsigned  char  ucbChanged  =  FALSE;
				   if  (  showDlgQnmEditPcUsrInfo(  NULL,  pObjDb,  0,  buf,  TRUE,  &ucbChanged  )  !=  IDOK  ||  !ucbChanged  )  {
					   ucbRefreshed  =  FALSE;
				   }

				   }
				   break;
			 case  ID_qyDel:						   			 			     
				   if  (  pm_docStruct  &&  pm_docStruct->iDocType  ==  CONST_qyDocType_mcQuery  )  {

					#if  0
					   if  (  pDoc->m_docStruct.u.query.type  ==  CONST_qyQueryType_pcAutoLogonList  )  {
							
						   TCHAR  seqNo[32]  =  _T(  ""  );
						   if  (  getLvSelColContent(  hParent,  &curnItem,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_seqNo  )/*_T(  "ÐòºÅ"  )*/,  seqNo,  mycountof(  seqNo  )  )  )  {
							   ucbRefreshed  =  FALSE;  break;
						   }
						   sqlStr  =  CString(  "id="  )  +  seqNo;
						   if  (  delPcSth(  pObjDb->pDb,  NULL,  _T(  "autoLogonTab"  ),  sqlStr  )  )  goto  errLabel;
						   iErr  =  0;  goto  errLabel;
						   break;
					   }
					#endif

					   if  (  pm_docStruct->u.query.type  ==  CONST_qyQueryType_imObjList  )  {
						   QY_MESSENGER_ID	idInfo;
						   char				idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";
						   //
						   idInfo.ui64Id  =  (  DWORD64  )atof(  buf  );
						   idInfo2Str(  &idInfo,  idStr,  mycountof(  idStr  )  );
						   //
						   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "idStr='%s'"  ),  CString(  idStr  )  );
						   if  (  delPcSth(  pObjDb->pDb,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeleteId  ),  _T(  "qyImObjAuthTab"  ),  sqlBuf  )  )  goto  errLabel;
						   if  (  delPcSth(  pObjDb->pDb,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeleteTmpId  ),  _T(  "qyImObjAuthTmpTab"  ),  sqlBuf  )  )  goto  errLabel;
						   if  (  delPcSth(  pObjDb->pDb,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeleteMsgr  ),  _T(  "qyImObjTab"  ),  sqlBuf  )  )  goto  errLabel;
						   iErr  =  0;  goto  errLabel;
						   break;
					   }
				
					   sqlStr  =  CString(  "mac0='"  )  +  CString(  buf  )  +  CString(  "'"  );
					   switch  (  pm_docStruct->u.query.type  )  {
#if  0
							   case  CONST_qyQueryType_pcSecChkEventList:
								     if  (  delPcSth(  pObjDb->pDb,  _T(  "是否删除该PC的上网网址记录?"  ),  _T(  "qyPcSecChkEventTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
									 iErr  =  0;  goto  errLabel;
									 break;
							   case  CONST_qyQueryType_pcRegistryList:
								     if  (  delPcSth(  pObjDb->pDb,  _T(  "是否删除该PC的注册表记录?"  ),  _T(  "qyPcRegistryValTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
									 iErr  =  0;  goto  errLabel;
									 break;
							   case  CONST_qyQueryType_pcEventLogList:
								     if  (  delPcSth(  pObjDb->pDb,  _T(  "是否删除该PC的操作系统日志信息?"  ),  _T(  "qyPcEventLogTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
									 iErr  =  0;  goto  errLabel;
									 break;
							   case  CONST_qyQueryType_pcOsUsrList:
								     if  (  delPcSth(  pObjDb->pDb,  _T(  "是否删除该PC的操作系统帐户信息?"  ),  _T(  "qyPcOsUsrTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
									 iErr  =  0;  goto  errLabel;
									 break;
							   case  CONST_qyQueryType_pcNetStatList:
								     if  (  delPcSth(  pObjDb->pDb,  _T(  "是否删除该PC的NetStat记录?"  ),  _T(  "qyPcNetStatTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
									 iErr  =  0;  goto  errLabel;										   
									 break;
							   case  CONST_qyQueryType_pcPrinterList:
								     if  (  delPcSth(  pObjDb->pDb,  _T(  "是否删除该PC的打印审计记录?"  ),  _T(  "qyPcPrinterTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
									 iErr  =  0;  goto  errLabel;										   
									 break;
							   case  CONST_qyQueryType_pcProcessList:		//  É¾³ý½ø³ÌÐÅÏ¢
							   case  CONST_qyQueryType_pcProcessModuleList:
								     if  (  delPcSth(  pObjDb->pDb,  _T(  "是否删除该PC的进程或进程模块信息?"  ),  _T(  "qyPcProcessTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
									 iErr  =  0;  goto  errLabel;										   
									 break;
							   case  CONST_qyQueryType_pcProcessRuleList:  {
								     TCHAR		seqNo[32]	=	_T(  ""  );
									 if  (  getLvSelColContent(  hParent,  &curnItem,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_seqNo  ),  seqNo,  sizeof(  seqNo  )  /  sizeof(  seqNo[0]  )  )  )  goto  errLabel;
									 sqlStr  =  CString(  ""  )  +  "id="  +  seqNo  +  "";
									 if  (  delPcSth(  pObjDb->pDb,  _T(  "是否删除该策略?"  ),  _T(  "qyPcProcessRuleTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
									 iErr  =  0;  goto  errLabel;
									 }
									 break;
							   case  CONST_qyQueryType_pcNetFlowList:  {
								     if  (  delPcSth(  pObjDb->pDb,  _T(  "是否删除该PC的流量信息?"  ),  _T(  "qyPcNetFlowTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
									 iErr  =  0;  goto  errLabel;											 
								     }
								     break;
							   case  CONST_qyQueryType_pcNetShareList:  {
								     if  (  delPcSth(  pObjDb->pDb,  _T(  "是否删除该PC的网络共享信息?"  ),  _T(  "qyPcNetShareTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
									 iErr  =  0;  goto  errLabel;		
									}
								     break;
							   case  CONST_qyQueryType_netMcPcList:
								     break;
#endif
							   default:
										traceLogA(  "queryType err"  );
										break;
							 
					   }						 
				   }
				   if  (  delAllPcInfo(  pObjDb->pDb,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyHint_netMcDelPcs  ),  buf  )  )  goto  errLabel;
				   break;
			 case  ID_qyProperties:  
				   showMacInfo(  pObjDb,  buf,  FALSE  );
				   ucbRefreshed  =  FALSE;
				   break;
#if  0
			 case  ID_qyProperties_viewNetDevConn:   
				   showMacInfo(  pObjDb,  buf,  TRUE  );
				   ucbRefreshed  =  FALSE;
				   break;
			 case  ID_qyDelPcUsr:
				   if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyHint_netMcDelPcUsr  ),  MB_YESNO  )  ==  IDYES  )  {
					   sqlStr  =  CString(  "delete from qyPcRegInfoTab where mac0='" )  +  CString(  buf  )  +  CString(  "'"  );
					   if  (  !bQyExecSql(  pObjDb->pDb,  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
				   }
				   break;
			 case  ID_qyDelPcUsrInTab1:
				   if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyHint_netMcDelPcUsrInTab1  ),  MB_YESNO  )  ==  IDYES  )  {
					   sqlStr  =  CString(  "delete from qyPcRegInfoTab1 where mac0='" )  +  CString(  buf  )  +  CString(  "'"  );
					   if  (  !bQyExecSql(  pObjDb->pDb,  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
				   }
				   break;
			 case  ID_qyDelPcRule:
				   if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyHint_netMcDelPcRule  ),  MB_YESNO  )  ==  IDYES  )  {
					   sqlStr  =  CString(  "delete from qyPcRuleTab where mac0='"  )  +  CString(  buf  )  +  CString(  "'"  );
					   if  (  !bQyExecSql(  pObjDb->pDb,  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
				   }
				   break;					   
#endif
			default:
					       traceLogA(  "未支持的命令: %d",  uiCmd  );
						   goto  errLabel;
	 	}
	 
		 
	 iErr  =  0;

errLabel:


	 if  (  !iErr  &&  ucbRefreshed  )  {
		 curnItem  =  ::SendMessage(  hParent,  LVM_GETSELECTIONMARK,  0,  0  );
		 //
		 memset(  &tmpComm,  0,  sizeof(  tmpComm  )  );
		 tmpComm.uiType  =  QY_WMPARAM_REFRESHDATA;
		 tmpComm.u.refreshData.curnRow  =  curnItem;								//2003/9/5
		 ::SendMessage(  hParent,  QY_WM_COMM,  0,  ( LPARAM  )&tmpComm  );
	 } 

	 return  iErr;

}









//
 int  procTvEventFunc_isCli(  void  *  pQyMcParam,  void  *  pDocParamReserved,  void  *  pSelParam,  void  *  pEventInfoParam,  unsigned  int  uiCmd,  LPCTSTR  colName  )
{
	 int						iErr										=	-1;
	 QY_MC					*	pQyMc										=	(  QY_MC  *  )pQyMcParam;
	 MC_VAR_isCli			*	pProcInfo									=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp	*	pFuncs										=  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs   ) return  -1;
 	 QY_MC_SEL				*	pSel										=	(  QY_MC_SEL  *  )pSelParam;
	 QY_EVENTINFO			*	pEventInfo									=	(  QY_EVENTINFO  *  )pEventInfoParam;
	 HWND						hParent										=	pEventInfo->hWnd;
	 TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	 QY_WMBUF_PROCTV			wmBuf;
	 TCHAR						misServName[CONST_maxMisServNameLen  +  1]	=	_T(  ""  );
	 char						idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";
	 QY_OBJ_DB				*	pObjDb										=	NULL;
	 int						iServiceId									=	pQyMc->iServiceId;
	 QY_MESSENGER_INFO			messengerInfo;
	 MSGR_ADDR					addr;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	 if  (  pSel->type  !=  CONST_qySelType_mcRootTree  )  goto  errLabel;
	 
	 pObjDb  =  getProcedObjDb(  pQyMc,  0,  pSel->u.rootTree.iDsnIndex  );	//  2007/01/02
	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	 memset(  &messengerInfo,  0, sizeof(  messengerInfo  )  );
	 switch  (  pSel->u.rootTree.objIndex.objType  )  {				
		     case  CONST_objType_me:	//  Me½ÚµãµÄÌØÊâµãÊÇÊµ¼ÊËüÊÇ´¦ÀíÈ«¾ÖµÄ¡£ÆäËû½ÚµãÊ«´¦Àí¸ö±ðµÄmessengerµÈ¡£
				   if  (  !g_dbFuncs.pf_bGetMeInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  pSel->u.rootTree.objIndex.servName,  &messengerInfo  )  )  goto  errLabel;
				   //
				   switch  (  uiCmd  )  {
						   case  ID_qySendSm:
							     memset(  &addr,  0,  sizeof(  addr  )  );
								 lstrcpyn(  addr.misServName,  messengerInfo.misServName,  mycountof(  addr.misServName  )  );
								 addr.uiObjType  =  messengerInfo.uiType;
								 addr.idInfo.ui64Id  =  messengerInfo.idInfo.ui64Id;
								 addr.uiDevType  =  CONST_objType_phone;
								 //
								 if  (  getSelectedToPath(  pObjDb,  _T(  ""  ),  FALSE,  addr.wPath,  mycountof(  addr.wPath  )  )  )  goto  errLabel;
								 addr.bInNoticeMode  =  TRUE;
								 //
								 //  if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;
								 if  (  pFuncs->pf_tryToTalkToMessenger(  mynull,&addr,  0,  0,  TRUE,  NULL,  0,  NULL  )  )  goto  errLabel;
							     break;
			               case  ID_imTaskList_unproced:
				   			     _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  )  );
				   				 g_dbFuncs.pf_bViewImTaskList_unproced(  pObjDb,  _T(  ""  ),  sqlBuf  );
				   				 break;
								 //
						   case  ID_imTaskList_cur:
							     _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  )  );
							     //  bViewImTaskListFunc(  pObjDb,  _T(  ""  ),  sqlBuf,  FALSE  );
								 g_dbFuncs.pf_bViewImTaskList_cur(  pObjDb,  _T(  ""  ),  sqlBuf  );
				   				 break;
								 //
						   case  ID_qyMsgToday:
							     _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImMsgTab.misServName=%s"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  )  );
							     bViewImMsgToday(  pQyMc,  pObjDb,  sqlBuf  );
				   				 break;
						   case  ID_qyMsgList:
							     _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImMsgTab.misServName=%s"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  )  );
								 bViewImMsgListFunc(  pQyMc,  pObjDb,  _T(  ""  ),  sqlBuf  );
								 break;
						   case  ID_qyEdit:  {
								 #if  10  //  ndef  __isCli__
								 QY_MESSENGER_REGINFO		regInfo;
								 BOOL						ucbInTab1	=	FALSE;

								 if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  messengerInfo.misServName,  &messengerInfo.idInfo,  0,  NULL,  &regInfo,  NULL,  NULL  )  
									 ||  !bQyTimeValid(  regInfo.tLastModifiedTime  )  )
								 {
									 ucbInTab1  =  TRUE;
								 }
								 //
								 unsigned  char  ucbChanged  =  FALSE;
								 if  (  showDlgQnmEditPcUsrInfo(  pEventInfo->hWnd,  pObjDb,  messengerInfo.misServName,  messengerInfo.uiType,  &messengerInfo.idInfo,  ucbInTab1,  &ucbChanged  )  !=  IDOK  )  goto  errLabel;
								 #endif
								 }
								 break;		
						   case  ID_qyProperties:  {
								 //
								 if  (  showDlgPropMessenger(  NULL,  pObjDb,  messengerInfo.misServName,  messengerInfo.uiType,  &messengerInfo.idInfo  )  !=  IDOK  )  goto  errLabel;
							     }				   
				   			     break;
						   case  ID_viewOfflineRes:  {
								 viewDlgOfflineRes_me(  hParent,  &pProcInfo->offlineRes,  NULL  );
							     }				   
				   			     break;
						   default:
								   #ifdef  __DEBUG__
										   traceLogA(  "procTvEventFunc_isCli 's cmd is  %d",  uiCmd  );
								   #endif
								   goto  errLabel;
				   }
				   
				   iErr  =  0;  goto  errLabel;
				   break;
			 case  CONST_objType_syr:
			 case  CONST_objType_messenger:
				   messengerInfo.uiType  =  CONST_objType_messenger;
				   lstrcpyn(  messengerInfo.misServName,  pSel->u.rootTree.objIndex.servName,  mycountof(  messengerInfo.misServName  )  );
				   myTChar2Str(  pSel->u.rootTree.objIndex.objIdStr0,  idStr,  mycountof(  idStr  )  );
				   if  (  !idStr2Info(  idStr,  &messengerInfo.idInfo  )  )  goto  errLabel;
				   break;
			 case  CONST_objType_imGrp:
				   messengerInfo.uiType  =  CONST_objType_imGrp;
				   lstrcpyn(  messengerInfo.misServName,  pSel->u.rootTree.objIndex.servName,  mycountof(  messengerInfo.misServName  )  );
				   myTChar2Str(  pSel->u.rootTree.objIndex.objIdStr0,  idStr,  mycountof(  idStr  )  );
				   if  (  !idStr2Info(  idStr,  &messengerInfo.idInfo  )  )  goto  errLabel;
				   //
				   MIS_CNT  *  pMisCnt;
				   pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
				   if  (  !pMisCnt  )  goto  errLabel;
				   //
				   switch  (  uiCmd  )  {
						   case  ID_qyDel:  {
							     //				   
							     if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_reallyToDelete  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
							     
								 //
								 //
								 MACRO_prepareForTran(  );
	
								 //
								 IM_GRP_EX	req  =  {0};
								 {
									 CQyMalloc					mallocObj;
									 IM_L_STREAM				*	pStream								=	NULL;

									 if  (  !(  pStream  =  (  IM_L_STREAM  *  )mallocObj.mallocf(  sizeof(  IM_L_STREAM  )  )  )  )  {
										 traceLogA(  "sndDevInfo_qmc . malloc failed."  );  
										 goto  errLabel;
									 }

									 unsigned  int		len;
									 char				buf[256];

									 //
									 IM_GRP_INFO  *  pReq  =  &req.common;

									 //
									 memset(  &req,  0,  sizeof(  req  )  );
									 req.common.uiType  =  CONST_imCommType_imGrp;
									 req.common.idInfo.ui64Id  =  messengerInfo.idInfo.ui64Id;
									 //
									 req.usOp  =  CONST_imOp_del;
									 
									 //  2010/08/14
									 pFuncs->pf_startProgress(  &pQyMc->gui.progress,  uiTranNo  );

									 //
									 MACRO_memset_imLStream(  pStream  );
									 pStream->uiType  =  CONST_imCommType_lStream;
									 pStream->uiContentType  =  req.common.uiType;
									 len  =  sizeof(  pStream->buf  );
									 if  (  imGrpEx2Stream(  pStream->uiContentType,  &req,  pStream->buf,  &len  )  )  goto  errLabel;
									 pStream->ulStreamLen  =  len;
									 len  +=  offsetof(  IM_L_STREAM,  buf  ); 
									 //
									 postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_refreshImObjListReq,  tStartTran,  uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  0,  0,  NULL,  0  ); 
	
								 }

								 //  pProcInfo->bInProgress_toSetPasswd  =  TRUE;
								 if  (  showProgress(  &pQyMc->gui.progress,  &pQyMc->cusRes,  hParent,  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo  )  !=  IDOK  )  {
									 goto  errLabel;
								 }

								 //
								 del_imGrp_isCli(  pQyMc,  &req.common.idInfo  );

								 //
								 memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
				   				 wmBuf.uiType  =  CONST_qyWmParam_delItem;
				   				 wmBuf.hItem  =  pSel->u.rootTree.hItem;
				   				 SendMessage(  pEventInfo->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
								 
								 //
								 iErr  =  0;  goto  errLabel;
								 }
								 break;
						   default:
								  break;
				   }
				   //
				   break;
			 default:
					break;
	 }

	 if  (  !idInfo2Str(  &messengerInfo.idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

	 switch  (  uiCmd  )  {
			 case  ID_qyTalk:  
			 case  ID_qyDiscuss:	 				//  2007/05/17
				   memset(  &addr,  0,  sizeof(  addr  )  );
				   lstrcpyn(  addr.misServName,  messengerInfo.misServName,  mycountof(  addr.misServName  )  );
				   addr.uiObjType  =  messengerInfo.uiType;
				   addr.idInfo.ui64Id  =  messengerInfo.idInfo.ui64Id;
				   //
				   //  if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;
				   if  (  pFuncs->pf_tryToTalkToMessenger(  mynull,&addr,  0,  0,  TRUE,  NULL,  0,  NULL  )  )  goto  errLabel;
				   break;
			 case  ID_qySendSm:
				   memset(  &addr,  0,  sizeof(  addr  )  );
				   lstrcpyn(  addr.misServName,  messengerInfo.misServName,  mycountof(  addr.misServName  )  );
				   addr.uiObjType  =  messengerInfo.uiType;
				   addr.idInfo.ui64Id  =  messengerInfo.idInfo.ui64Id;
				   addr.uiDevType  =  CONST_objType_phone;
				   //
				   if  (  getSelectedToPath(  pObjDb,  _T(  ""  ),  FALSE,  addr.wPath,  mycountof(  addr.wPath  )  )  )  goto  errLabel;
				   addr.bInNoticeMode  =  TRUE;
				   //
				   //  if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;
				   if  (  pFuncs->pf_tryToTalkToMessenger(  mynull,&addr,  0,  0,  TRUE,  NULL,  0,  NULL  )  )  goto  errLabel;
				   break;
			 case  ID_qyRule:  {    
				   //
				   showDlgImObjRule(  NULL,  messengerInfo.misServName,  &messengerInfo.idInfo  );
				   }
				   break;
			 case  ID_qyProperties:  
				   if  (    messengerInfo.uiType  ==  CONST_objType_imGrp  )  {
					   //
					   if  (  showDlgPropImGrp(  NULL,  pObjDb,  messengerInfo.misServName,  &messengerInfo.idInfo  ) !=  IDOK  )  goto  errLabel;
					   }
				   else  {
						 //
						 if  (  showDlgPropMessenger(  NULL,  pObjDb,  messengerInfo.misServName,  messengerInfo.uiType,  &messengerInfo.idInfo  )  !=  IDOK  )  goto  errLabel;
				   }				   
				   break;
			 case  ID_qyEdit:  {
				   #ifndef  __isCli__
				   CDlgQnmEditPcUsrInfo		dlg;
				   BOOL						ucbInTab1	=	FALSE;	//  MeÔÚÉÏÃæ´¦Àí¡£messenger¶¼Ö»Ð´½øÕýÊ½±í

				   if  (  !dlg.bSetDlgInfo(  pObjDb,  messengerInfo.misServName,  messengerInfo.uiType,  &messengerInfo.idInfo,  ucbInTab1  )  )  goto  errLabel;
				   dlg.DoModal(  );
				   #endif
				   }
				   break;		
			 case  ID_imTaskList_unproced:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s and (T.idStr_send='%s' or T.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  ),  CString(  idStr  ),  CString(  idStr  )  );
				   g_dbFuncs.pf_bViewImTaskList_unproced(  pObjDb,  _T(  ""  ),  sqlBuf  );
				   break;
			 case  ID_imTaskList_cur:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s and (T.idStr_send='%s' or T.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  ),  CString(  idStr  ),  CString(  idStr  )  );
				   //  bViewImTaskListFunc(  pObjDb,  _T(  ""  ),  sqlBuf,  FALSE  );
				   g_dbFuncs.pf_bViewImTaskList_cur(  pObjDb,  _T(  ""  ),  sqlBuf  );
				   break;
			 case  ID_imTaskList_his:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s and (T.idStr_send='%s' or T.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  ),  CString(  idStr  ),  CString(  idStr  )  );
				   //  bViewImTaskListFunc(  pObjDb,  _T(  ""  ),  sqlBuf,  TRUE  );
				   g_dbFuncs.pf_bViewImTaskList_his(  pObjDb,  _T(  ""  ),  sqlBuf  );
				   break;
			 case  ID_qyMsgToday:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImMsgTab.misServName=%s and (qyImMsgTab.idStr_send='%s' or qyImMsgTab.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  ),  CString(  idStr  ),  CString(  idStr  )  );
				   bViewImMsgToday(  pQyMc,  pObjDb,  sqlBuf  );
				   break;
			 case  ID_qyMsgList:				   
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImMsgTab.misServName=%s and (qyImMsgTab.idStr_send='%s' or qyImMsgTab.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  ),  CString(  idStr  ),  CString(  idStr  )  );
				   bViewImMsgListFunc(  pQyMc,  pObjDb,  _T(  ""  ),  sqlBuf  );
				   break;
			 case  ID_qyDel:
				   //
				   if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_reallyToDelete  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
				   //
				   if  (  delImObj(  pObjDb->pDb,  pObjDb->cfg.iDbType,  pQyMc->iAppType  ==  CONST_qyAppType_client,  messengerInfo.misServName,  &messengerInfo.idInfo  )  )  goto  errLabel;
				   //
				   //  
				   memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
				   wmBuf.uiType  =  CONST_qyWmParam_delItem;
				   wmBuf.hItem  =  pSel->u.rootTree.hItem;
				   SendMessage(  pEventInfo->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
				   //
				   break;
			 default:
					//  traceLogA(  "netMc_procTvEventFunc: Î´ÊµÏÖµÄÃüÁî"  );
					break;
	 }
	 

	 iErr  =  0;
errLabel:

	 return  iErr;
}



 int  mc_procTvEventFunc(  void  *  pQyMcParam,  void  *  pDocParamReserved,  void  *  pSelParam,  void  *  pEventInfoParam,  unsigned  int  uiCmd,  LPCTSTR  colName  )
{
	 QY_MC	*	pQyMc  =  (  QY_MC  *  )pQyMcParam;

	 switch  (  pQyMc->iServiceId  )  {
#if  0
			 case  CONST_qyServiceId_netMc:
				   return  procTvEventFunc_netMc(  pQyMcParam,  pDocParamReserved,  pSelParam,  pEventInfoParam,  uiCmd,  colName  );
#endif
			 case  CONST_qyServiceId_mis:
				   return  procTvEventFunc_isCli(  pQyMcParam,  pDocParamReserved,  pSelParam,  pEventInfoParam,  uiCmd,  colName  );
			 default:
					break;					
	 }

	 return  -1;
}



//
 //
  int  nms_popupMenu_isCli(  void  *  pQyMcParam,  int  x,  int  y,  void  *  pCurSelParam,  void  *  pEventInfoParam,  void  *  pMenuContext  )
{
	 int						iErr				=		-1;
	 QY_MC					*	pQyMc				=		(  QY_MC  *  )pQyMcParam;
	 QY_MC_SEL				*	pCurSel				=		(  QY_MC_SEL  *  )pCurSelParam;		
	 QY_EVENTINFO			*	pEventInfo			=		(  QY_EVENTINFO  *  )pEventInfoParam;
	 if  (  !pEventInfo  )  return  -1;
	 HWND						hWnd				=		pEventInfo->hWnd;
	 UINT						uMenuId				=		0;
	 CMenu						tmpMenu;
	 CMenu					*	tmppPopupMenu		=		NULL;
	 UINT						uCmd				=		0;
	 int						nPos				=		-1;
	 int						iSelId				=		0;
	 TCHAR						tBuf[1024];
	 TCHAR						colName[128];
	 char						buf[255  +  1]		=		"";
	 char						switchMac[CONST_qyMacLen  +  1];
	 QY_DMITEM				*	pItem;
	 OBJ_STATUS_INFO			objStatusInfoU;
	 QY_OBJ_DB				*	pObjDb				=		NULL;
	 QNM_CUSRES_INFO		*	pCusRes				=		&pQyMc->cusRes;		//  2008/01/02

	 /////////////////
	 
	 QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );
	 if  (  !pResMem  )  goto  errLabel;
	 QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	 if  (  !pDbFuncs  )  goto  errLabel;
	 QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	 //
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	 if  (  !pMisCnt  )  goto  errLabel;


	 //  2006/02/11
	 memset(  &objStatusInfoU,  0,  sizeof(  objStatusInfoU  )  );
	 //

	 uMenuId  =  IDR_QYMCPOPUP;

	 switch  (  pCurSel->type  )  {
			case  QY_SELTYPE_MCROOTTREE:			//  0
				  
				  pObjDb  =  getProcedObjDb(  pQyMc,  0,  pCurSel->u.rootTree.iDsnIndex  );	//  2007/01/02

				  if  (  pCurSel->u.rootTree.bRoot  )  break;
				  
				  switch  (  pCurSel->u.rootTree.objIndex.objType  )  {
						  case  CONST_objType_qySwitch:			nPos  =  10;	break;
						  case  CONST_objType_qySwitchPort:		nPos  =  11;	break;
						  case  CONST_objType_otherPc:
						  case  CONST_objType_unRegPc:			nPos  =  21;	break;
						  case  CONST_objType_os:				nPos  =  22;	break;
						  case  CONST_objType_cfgSpOs:			nPos  =  23;	break;
						  case  CONST_objType_cfgSpServicePack:	nPos  =  24;	break;
						  //							  
						  case  CONST_objType_syr:				{
							    if  (  pCurSel->u.rootTree.type  !=  CONST_qyTreeType_imObj  )  {
									objStatusInfoU.iObjType  =  CONST_objType_pc;
									nPos  =  CONST_resId_popup_pc;	
									}
								else  {
									  objStatusInfoU.iObjType  =  CONST_objType_messenger;
									  lstrcpyn(  objStatusInfoU.u.messengerStatus.misServName,  pCurSel->u.rootTree.objIndex.servName,  mycountof(  objStatusInfoU.u.messengerStatus.misServName  )  );
									  myTChar2Str(  pCurSel->u.rootTree.objIndex.objIdStr0,  buf,  mycountof(  buf  )  );
									  if  (  !idStr2Info(  buf,  &objStatusInfoU.u.messengerStatus.idInfo  )  )  goto  errLabel;
									  //
									  nPos  =  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_popup_messenger_isClient  :  CONST_resId_popup_messenger_isMgr;									
								}
								//								
								}																
								break;								
						  case  CONST_objType_me:				{
							    objStatusInfoU.iObjType  =  pCurSel->u.rootTree.objIndex.objType;
								lstrcpyn(  objStatusInfoU.u.messengerStatus.misServName,  pCurSel->u.rootTree.objIndex.servName,  mycountof(  objStatusInfoU.u.messengerStatus.misServName  )  );
								//
							    nPos  =  CONST_resId_popup_me;									//  2007/05/16
								}
								break;
						  case  CONST_objType_messenger:		{
							    objStatusInfoU.iObjType  =  pCurSel->u.rootTree.objIndex.objType;
								lstrcpyn(  objStatusInfoU.u.messengerStatus.misServName,  pCurSel->u.rootTree.objIndex.servName,  mycountof(  objStatusInfoU.u.messengerStatus.misServName  )  );
								myTChar2Str(  pCurSel->u.rootTree.objIndex.objIdStr0,  buf,  mycountof(  buf  )  );
								if  (  !idStr2Info(  buf,  &objStatusInfoU.u.messengerStatus.idInfo  )  )  goto  errLabel;
							    //
							    nPos  =  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_popup_messenger_isClient  :  CONST_resId_popup_messenger_isMgr;			
								break;
								}
						  case  CONST_objType_imGrp:  {
							    if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
									nPos  =  CONST_resId_popup_imGrp_isClient;
									}
								else  {
									  nPos  =  CONST_resId_popup_imGrp_isMgr;	 
								}
								break;
								}
						  //
						  default:
							      break;
				  }
				  break;
			case  QY_SELTYPE_MCROOTLIST:			// 

				  pObjDb  =  getProcedObjDb(  pQyMc,  0,  pCurSel->u.rootList.leftTreeSel.iDsnIndex  );	//  2007/01/02

				  if  (  pCurSel->u.rootList.leftTreeSel.type  ==  CONST_qyTreeType_pc  )  {	//  2006/06/12
					  if  (  pCurSel->u.rootList.leftTreeSel.bRoot  )  break;
					  switch  (  pCurSel->u.rootList.leftTreeSel.objIndex.objType  )  {
							  case  CONST_objType_othersGrp:			nPos  =  0;		break;
							  case  CONST_objType_col3:
							  case  CONST_objType_unRegGrp:	  
								    //  2006/08/12, 
									//
								    _sntprintf(  colName,  mycountof(  colName  ),  _T(  "MAC"  )  );
									if  (  getLvSelColContent(  hWnd,  0,  colName,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  )  )  goto  errLabel;
									myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
									objStatusInfoU.iObjType  =  CONST_objType_syr;  
									safeStrnCpy(  buf,  objStatusInfoU.u.pc.mac0,  sizeof(  objStatusInfoU.u.pc.mac0  )  );
								    //
								    if  (  pQyMc->iSystemId  ==  CONST_qySystemId_netMc2  )  nPos  =  pQyMc->cfg.pGuiCfg->nSubMenuPos_pcList;
									else  nPos  =  0;		
									break;
							  case  CONST_objType_pcOpNode:		//  2006/08/15
								    myTChar2Str(  pCurSel->u.rootList.leftTreeSel.objIndex.objIdStr0,  buf,  sizeof(  buf  )  );
									objStatusInfoU.iObjType  =  CONST_objType_syr;
									safeStrnCpy(  buf,  objStatusInfoU.u.pc.mac0,  sizeof(  objStatusInfoU.u.pc.mac0  )  );
									nPos  =  pQyMc->cfg.pGuiCfg->nSubMenuPos_pcList;
								    break;
							  case  CONST_objType_pcEnv:				nPos  =  21;	break;
							  default:		break;					  
					  }
					  break;
				  }				  				  
				  if  (  pCurSel->u.rootList.leftTreeSel.type  ==  CONST_qyTreeType_imObj  )  {
					  if  (  pCurSel->u.rootList.leftTreeSel.bRoot  )  break;
					  switch  (  pCurSel->u.rootList.leftTreeSel.objIndex.objType  )  {
							  case  CONST_objType_col3:					
							  case  CONST_objType_unRegGrp:
							  case  CONST_objType_pcOpNode:
							  case  CONST_objType_imGrp:
									nPos  =  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_popup_viewMessengerList_isClient  :  CONST_resId_popup_viewMessengerList_isMgr;
									break;
							  case  CONST_objType_imGrps:
								    nPos  =  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_popup_viewImGrpList_isClient  :  CONST_resId_popup_viewImGrpList_isMgr;
								    break;
							  default:
									 break;								    
					  }
					  break;		
				  }
				  if  (  pCurSel->u.rootList.leftTreeSel.type  ==  CONST_qyTreeType_cfgSp  )  {
					  if  (  pCurSel->u.rootList.leftTreeSel.bRoot  )  break;
					  switch  (  pCurSel->u.rootList.leftTreeSel.objIndex.objType  )  {
							  case  CONST_objType_cfgSpOs:				nPos  =  0;		break;
							  case  CONST_objType_cfgSpServicePack:		nPos  =  25;	break;
							  default:		break;
					  }
					  break;
				  }
				  if  (  pCurSel->u.rootList.leftTreeSel.bRoot  )  {
					  nPos  =  0;  break;
				  }
				  if  (  pCurSel->u.rootList.leftTreeSel.type  !=  CONST_qyTreeType_networkSpeed  )  {
					  nPos  =  12;	break;	//  2003/11/01, ÔÝÊ±²»Ìá¹©×è¶Ï¹¦ÄÜ
				  }
				  break;
			case  CONST_qySelType_mcView:				
				  
				  if  (  pCurSel->u.mcView.pCusRes  )  pCusRes  =  (  QNM_CUSRES_INFO  *  )pCurSel->u.mcView.pCusRes;		//  2008/01/02
				  //
				  uMenuId  =  pCurSel->u.mcView.uPopupMenuId;
			      nPos  =  pCurSel->u.mcView.nSubMenuPos;

				  if  (   pCurSel->u.mcView.type  ==  CONST_qyLvType_procedObjList  )  {
				  	  _sntprintf(  colName,  mycountof(  colName  ),  _T(  "ID"  )  );
				  	  if  (  getLvSelColContent(  hWnd,  0,  colName,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  )  )  goto  errLabel;
				  	  myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
					  //
					  pObjDb  =  getProcedObjDb(  pQyMc,  0,  atol(  buf  )  );
					  if  (  !pObjDb  )  goto  errLabel;
					  //
					  objStatusInfoU.iObjType  =  CONST_objType_procedObj;
					  objStatusInfoU.u.procedObj.ucbLoaded  =  pObjDb->ucbLoaded;

					  if  (  !pObjDb->ucbLoaded  )  {					//  2007/09/16
						  nPos  =  CONST_resId_popup_viewProcedObj_load;  break;
					  }

					  QNM_GUICFG_INFO	*	pGuiCfg  =  NULL;

					  #ifndef  __isCli__
							   pGuiCfg  =  getQnmGuiCfgInfo(  pObjDb->cfg.iSystemId,  pObjDb->cfg.iAppType  );
					  #endif
					  if  (  !pGuiCfg  )  {
						  #ifdef  __DEBUG__
								  traceLogA(  "systemId is %d, getQnmGuiCfgInfo(  ) failed",  pObjDb->cfg.iSystemId  );
						  #endif
						  goto  errLabel;
					  }
					  nPos  =  pGuiCfg->iResId_popupMenu_procedObj;  break;
				  }
				  break;
			case  CONST_qySelType_mcDlgLv:

				  pObjDb  =  getProcedObjDb(  pQyMc,  0,  pCurSel->u.mcDlgLv.iDsnIndex  );	//  2007/01/02

				  switch  (  pCurSel->u.mcDlgLv.type  )  {
						  case  CONST_qyQueryType_talk_imGrpMemList:	 {
							    int								curnItem	=	-1;
							    IM_GRP_MEM						grpMem;
								//
								_sntprintf(  colName,  mycountof(  colName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_seqNo  )  );
								if  (  getLvSelColContent(  pEventInfo->hFrom,  &curnItem,  0,  NULL,  0  )  )  goto  errLabel;
								if  (  getLvColContent(  pEventInfo->hWnd,  pEventInfo->hFrom,  curnItem,  colName,  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;

								//							
								if  (  !g_dbFuncs.pf_bGetImGrpMemBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  NULL,  NULL,  NULL,  _ttol(  tBuf  ),  &grpMem  )  )  {
									#ifdef  __DEBUG__
											traceLog(  _T(  "nms_popupMenu: bGetImGrpMemBySth failed"  )  );
									#endif
									goto  errLabel;
								}
								//
								objStatusInfoU.iObjType  =  CONST_objType_imGrpMem;
								objStatusInfoU.u.imGrpMem.grpMem  =  grpMem;
								
								//
								if  (  bAppClient(  pQyMc->iAppType  )  )  {
									nPos  =  CONST_resId_popup_messenger_isClient;
									//
									if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_bjyz  )  {
										nPos  =  CONST_resId_popup_imGrpMem_isCli_yz;
									}
									//
									}
								else  {
									  nPos  =  CONST_resId_popup_viewMessengerList_isMgr;
								}
								
								//

								}
								//
								break;
						  case  CONST_qyQueryType_tmpGrpMemList:
							    nPos  =   CONST_resId_popup_phoneGuest_isClient;
							    break;
						  case  CONST_qyQueryType_instantAssistantMemList:
							    nPos  =  CONST_resId_popup_instantAssistantMem;
							    break;
						  default:
								  break;
				  }
				  break;
			default:
				     goto errLabel;
	 }

	 if  (  !pCusRes  ||  !uMenuId  ||  nPos  <  0  )  goto  errLabel;

	 //  2006/08/12¼Ó
	 objStatusInfoU.pObjDb  =  pObjDb;
	 getObjStatusInfo(  0,  pObjDb,  &objStatusInfoU  );

	 //	 2005/1109
	 //
	 if  (  !(  tmpMenu.CreatePopupMenu(  )  )  )  goto  errLabel;
	 if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_popupMenu  )  )  )  goto  errLabel;
	 if  (  !(  pItem  =  qyGetDmItemByType(  pItem,  nPos,  sizeof(  QY_DMITEM  )  )  )  )  goto  errLabel;
	 if  (	 makeDynaMenu(  pCusRes,  tmpMenu.m_hMenu,  (  QY_DMITEM  *  )pItem->pData,  getMenuStatus,  pQyMc,  &objStatusInfoU  )  )  goto  errLabel;
	 tmppPopupMenu  = &tmpMenu;

	 
	 //  
	 switch  (  pCurSel->type  )  {
			 case  QY_SELTYPE_MCROOTTREE:			//  0
				   
				   if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;	//  2007/01/03

				   if  (  pCurSel->u.rootTree.bRoot  )  break;
				   switch  (  pCurSel->u.rootTree.objIndex.objType  )  {
					       case  CONST_objType_qySwitch:		{
							     QY_SNMPOBJ_HEAD				snmpObjHead;

								 myTChar2Str(  pCurSel->u.rootTree.objIndex.objIdStr0,  switchMac,  sizeof(  switchMac  )  );
								 memset(  &snmpObjHead,  0,  sizeof(  snmpObjHead  )  );
								 if  (  !bGetSnmpObjHeadInfoBySth(  pObjDb->pDb,  switchMac,  NULL,  &snmpObjHead  )  )  goto  errLabel;
								 if  (  snmpObjHead.auditTime[0]  )  tmppPopupMenu->EnableMenuItem(  ID_qyEdit_switchInfo, MF_BYCOMMAND  |  MF_GRAYED   );
								 else  {
									   tmppPopupMenu->EnableMenuItem(  ID_qyCancel_switchAndAllConns, MF_BYCOMMAND  |  MF_GRAYED   );
									   tmppPopupMenu->EnableMenuItem(  ID_qyCancel_allConns, MF_BYCOMMAND  |  MF_GRAYED   );
								 }
								 							     
								 }
							     break;
						   case  CONST_objType_qySwitchPort:	{
							     QY_SNMPOBJ_HEAD				snmpObjHead;
							     QY_SWITCHIFPORTSECURITY_RCD	portSecurity;
							   
								 if  (  !bGetSnmpObjHeadInfoBySth(  pObjDb->pDb,  pCurSel->u.rootTree.u.switchPort.switchMac,  NULL,  &snmpObjHead  )  )  goto  errLabel;

								 if  (  pCurSel->u.rootTree.u.switchPort.iPortIfAdminStatus  ==  1  )  tmppPopupMenu->EnableMenuItem(  ID_qyStopWillAttack, MF_BYCOMMAND  |  MF_GRAYED   );
								 else  tmppPopupMenu->EnableMenuItem(  ID_qyWillAttack, MF_BYCOMMAND  |  MF_GRAYED   );

								 //  2004/06/13 cisco,  2004/08/21
								 if  (  bQnmDemo(  )  ||  snmpObjHead.iMaker  !=  CONST_enterpriseId_cisco  ||  !snmpObjHead.ucbCpsGlobalPortSecurityEnable  )  {
									 tmppPopupMenu->EnableMenuItem(  ID_beStaticAccessModeAndEnablePortSecurity,  MF_BYCOMMAND  |  MF_GRAYED  );
									 tmppPopupMenu->EnableMenuItem(  ID_disablePortSecurity,  MF_BYCOMMAND  |  MF_GRAYED  );
									 tmppPopupMenu->EnableMenuItem(  ID_setCpsIfMaxSecureMacAddr,  MF_BYCOMMAND  |  MF_GRAYED  );
									}
								 else  {

								 	   if  (  !bGetPortInfoBySth(  pObjDb->pDb,  pCurSel->u.rootTree.u.switchPort.switchMac,  pCurSel->u.rootTree.u.switchPort.iPortIfIndex,  -1,  NULL,  NULL,  &portSecurity  )  )  memset(  &portSecurity,  0,  sizeof(  &portSecurity  )  );
									   if  (  portSecurity.ucbCpsIfPortSecurityEnable  )  tmppPopupMenu->EnableMenuItem(  ID_beStaticAccessModeAndEnablePortSecurity,  MF_BYCOMMAND  |  MF_GRAYED  );
									   else  {
										     tmppPopupMenu->EnableMenuItem(  ID_disablePortSecurity,  MF_BYCOMMAND  |  MF_GRAYED  );
										   	 tmppPopupMenu->EnableMenuItem(  ID_setCpsIfMaxSecureMacAddr,  MF_BYCOMMAND  |  MF_GRAYED  );
									   }
																 
								 }
								 
								 //  2004/07/12
								 if  (  pQyMc->cfg.modulesLoadedInfo.ulbNetFlowModuleLoaded  )  {
									 tmppPopupMenu->InsertMenu(  0,  MF_BYPOSITION  |  MF_SEPARATOR  );
									 #ifndef  __isCli__
											  tmppPopupMenu->InsertMenu(  0,  MF_BYPOSITION,  ID_qyMonIf,  _T(  "实时流量监控(&J)"  )  ); //
									 #endif
								 }


								 }
							     break;
						   case  CONST_objType_cfgSpOs:
							     switch  (  pCurSel->u.rootTree.objIndex.objId0  )  {
										 case  CONST_qyPlatform_win32:
										 case  CONST_qyPlatform_win95:
										 case  CONST_qyPlatform_win98:
										 case  CONST_qyPlatform_winme:
											   tmppPopupMenu->EnableMenuItem(  ID_addServicePack,  MF_BYCOMMAND  |  MF_GRAYED  );
											   break;
										 default:	break;
								 }
							     break;
						   case  CONST_objType_cfgSpServicePack:
							     if  (  !pCurSel->u.rootTree.objIndex.objIdStr0[0]  )  {
								     tmppPopupMenu->EnableMenuItem(  ID_qyEdit,  MF_BYCOMMAND  |  MF_GRAYED  );
									 tmppPopupMenu->EnableMenuItem(  ID_qyProperties,  MF_BYCOMMAND  |  MF_GRAYED  );
								 }
							     break;
						   case  CONST_objType_me:
							     if  (  !bMessengerIdValid(  &objStatusInfoU.u.messengerStatus.idInfo  )  )  {
									 tmppPopupMenu->EnableMenuItem(  ID_qyEdit,  MF_BYCOMMAND  |  MF_GRAYED  );
								 }							     
								 tmppPopupMenu->EnableMenuItem(  ID_qyDelPcUsr,  MF_BYCOMMAND  |  MF_GRAYED  );
							     break;
						   case  CONST_objType_messenger:
							     if  (  objStatusInfoU.u.messengerStatus.messengerInfo.uiType  ==  CONST_objType_me  )  tmppPopupMenu->EnableMenuItem(  ID_qyTalk,  MF_BYCOMMAND  |  MF_GRAYED  );
								 //
							     break;
						   case  CONST_objType_syr:
							     if  (  objStatusInfoU.iObjType  ==  CONST_objType_messenger  )  {
									 switch  (  objStatusInfoU.u.messengerStatus.messengerInfo.uiType  )  {
										     case  CONST_objType_me:
											 case  CONST_objType_phoneMessenger:
												   tmppPopupMenu->EnableMenuItem(  ID_qyTalk,  MF_BYCOMMAND  |  MF_GRAYED  );
												   tmppPopupMenu->EnableMenuItem(  ID_qyRule,  MF_BYCOMMAND  |  MF_GRAYED  );
												   break;
											 default:
													break;
									 }
									 //
									 if  (  !objStatusInfoU.u.messengerStatus.phoneInfo.wDevIdStr[0]  )  tmppPopupMenu->EnableMenuItem(  ID_qySendSm,  MF_BYCOMMAND  |  MF_GRAYED  );
								 }
								 break;
						   case  CONST_objType_imGrp:
							     if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
									 #ifdef  __isCli__
											 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
											 if  (  !pProcInfo  )  goto  errLabel;
											 MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
											 if  (  !pMisCnt  )  goto  errLabel;
											 //
											 if  (  pCurSel->u.rootTree.u.imGrpInfo.idInfo_creator.ui64Id  !=  pMisCnt->idInfo.ui64Id  )  {
												 tmppPopupMenu->EnableMenuItem(  ID_qyDel,  MF_BYCOMMAND  |  MF_GRAYED  );
											 }
									 #endif
								 }
							     break;
						   default:
								  break;
				   }
				   break;
			 case  CONST_qySelType_mcRootList:  

 				   if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;	//  2007/01/03

				   if  (  pCurSel->u.rootList.leftTreeSel.type  ==  CONST_qyTreeType_pc  )  {
					   if  (  objStatusInfoU.iObjType  ==  CONST_objType_syr  )  {				//  2006/08/13, ¼ÓÈë¶Ô°²¼ì×´Ì¬µÄÅÐ¶Ï
						   QNM_PC_RULES		pcRules;
						   //
						   memset(  &pcRules,  0,  sizeof(  pcRules  )  );
						   if  (  bGetPcRule(  pQyMc->cfg.ucbAdvancedVer,  pObjDb->pDb,  objStatusInfoU.u.pc.mac0,  &pcRules  )  &&  pcRules.secChk.ucbDoSecChk  )  tmppPopupMenu->EnableMenuItem(  ID_doSecChk,  MF_BYCOMMAND  |  MF_GRAYED  );
						   else  tmppPopupMenu->EnableMenuItem(  ID_undoSecChk,  MF_BYCOMMAND  |  MF_GRAYED  );
						   if  (  !bMacValid(  objStatusInfoU.u.pc.regInfo.mac0  )  )  tmppPopupMenu->EnableMenuItem(  ID_qyCfgStandardName,  MF_BYCOMMAND  |  MF_GRAYED  );
					   }
					   break;
				   }
				   if  (  pCurSel->u.rootList.leftTreeSel.type  ==  CONST_qyTreeType_imObj  )  {
					   break;
				   }
				   if  (  pCurSel->u.rootList.leftTreeSel.type  ==  CONST_qyTreeType_cfgSp  )  {
					   if  (  getSelIdFromLv(  hWnd,  &iSelId  )  )  goto  errLabel;
					   if  (  !iSelId  )  tmppPopupMenu->EnableMenuItem(  ID_qyProperties,  MF_BYCOMMAND  |  MF_GRAYED  );
					   break;
				   }
				   //				   				   
				   if  (  !pCurSel->u.rootList.leftTreeSel.bRoot  )  {
				   	   TCHAR							colName[128]				=	_T(  "mac"  );
				   	   char								buf[CONST_qyMacLen  +  1]	=	"";
					   QY_SNMPOBJ_HEAD					snmpObjHead;
					   QY_SWITCHIFPORTSECURITY_RCD		portSecurity;
				   	   QY_SWITCHCONNECTEDPC_RCD			connInfo;
					   QY_SWITCHSECUREMAC_RCD			secureMacInfo;
										   
				   	   if  (  getLvSelColContent(  hWnd,  NULL,  colName,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  )  )  goto  errLabel;				   
					   myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
				   	   if  (  !bMacValid(  buf  )  )  goto  errLabel;
					   myTChar2Str(  pCurSel->u.rootList.leftTreeSel.objIndex.objIdStr0,  switchMac,  sizeof(  switchMac  )  );
					   //
					   if  (  !bGetConnectedPcInfoBySth(  pObjDb->pDb,  switchMac,  buf,  NULL,  &connInfo,  &secureMacInfo  )  )  goto  errLabel;
					   if  (  !connInfo.auditTime[0]  )  tmppPopupMenu->EnableMenuItem(  ID_qyCancel_portUsrInfo, MF_BYCOMMAND  |  MF_GRAYED   );
					   //  ÏÂÃæÅÐ¶ÏMAC°ó¶¨µÄ²Ëµ¥Ïî
					   if  (  !bGetSnmpObjHeadInfoBySth(  pObjDb->pDb,  switchMac,  NULL,  &snmpObjHead  )  )  goto  errLabel;
					   if  (  !bGetPortInfoBySth(  pObjDb->pDb,  connInfo.switchMac,  connInfo.iPortIfIndex,  0,  NULL,  NULL,  &portSecurity  )  )  goto  errLabel;
					   if  (  snmpObjHead.iMaker  !=  CONST_enterpriseId_cisco  ||  !snmpObjHead.ucbCpsGlobalPortSecurityEnable  ||  !portSecurity.ucbCpsIfPortSecurityEnable  )  {
						   tmppPopupMenu->EnableMenuItem(  ID_secureMac,  MF_BYCOMMAND  |  MF_GRAYED  );
						   tmppPopupMenu->EnableMenuItem(  ID_cancelSecureMac,  MF_BYCOMMAND  |  MF_GRAYED  );
							}
					   else  if  (  bMacValid(  secureMacInfo.secureMac  )  &&  secureMacInfo.iCpsSecureMacAddrType  ==  1  )  {
						         tmppPopupMenu->EnableMenuItem(  ID_secureMac,  MF_BYCOMMAND  |  MF_GRAYED  );
								}
					   else  if  (  !bMacValid(  secureMacInfo.secureMac  )  ||  !secureMacInfo.iCpsSecureMacAddrType  )  {
								 tmppPopupMenu->EnableMenuItem(  ID_cancelSecureMac,  MF_BYCOMMAND  |  MF_GRAYED  );
					   }
					   
				   }
				   break;
			 case  CONST_qySelType_mcDlgLv:
				   if  (  objStatusInfoU.iObjType  ==  CONST_objType_messenger  )  {
					   switch  (  objStatusInfoU.u.messengerStatus.messengerInfo.uiType  )  {
							   case  CONST_objType_me:
							   case  CONST_objType_phoneMessenger:
								     tmppPopupMenu->EnableMenuItem(  ID_qyTalk,  MF_BYCOMMAND  |  MF_GRAYED  );
								     break;
							   default:
									   break;
					   }
					   //					   	
					   if  (  !objStatusInfoU.u.messengerStatus.phoneInfo.wDevIdStr[0]  )  tmppPopupMenu->EnableMenuItem(  ID_qySendSm,  MF_BYCOMMAND  |  MF_GRAYED  );
					   //
				   }

				   //
				   if  (  pCurSel->u.mcDlgLv.type  ==  CONST_qyQueryType_instantAssistantMemList  )  {	//  2009/02/24
					   int	curnItem  =  -1;
					   if  (  getLvSelColContent(  pEventInfo->hFrom,  &curnItem,  0,  NULL,  0  )  )  goto  errLabel;

					   LVITEM				lvItem;
					   memset(  &lvItem,  0,  sizeof(  lvItem  )  );
					   lvItem.mask  =  LVIF_IMAGE  |  LVIF_STATE;
					   lvItem.iItem  =  curnItem;

					   if  (  !SendMessage(  pEventInfo->hFrom,  LVM_GETITEM,  0,  (  LPARAM  )&lvItem  )  )  goto  errLabel;
					   
					   if  (  lvItem.iImage  ==  pQyMc->cfg.image.nImage_activeMem  )  tmppPopupMenu->EnableMenuItem(  ID_requestToSpeak,  MF_BYCOMMAND  |  MF_GRAYED  );

					   }
				   else  if  (  pCurSel->u.mcDlgLv.type  ==  CONST_qyQueryType_talk_imGrpMemList  )  {
							 if  (  objStatusInfoU.iObjType  ==  CONST_objType_imGrpMem  )  {
								 if  (  pMisCnt->idInfo.ui64Id  ==  objStatusInfoU.u.imGrpMem.grpMem.idInfo_mem.ui64Id  )  {
									 //
									 tmppPopupMenu->EnableMenuItem(  ID_qyTalk,  MF_BYCOMMAND  |  MF_GRAYED  );
								     //
									 tmppPopupMenu->EnableMenuItem(  ID_yz_shareScreen,  MF_BYCOMMAND  |  MF_GRAYED  );
									 tmppPopupMenu->EnableMenuItem(  ID_yz_stopShareScreen,  MF_BYCOMMAND  |  MF_GRAYED  );
									 //
									 tmppPopupMenu->EnableMenuItem(  ID_menuItemIdc_remotePtzControl,  MF_BYCOMMAND  |  MF_GRAYED  );
									 
								 }	
								 //
								 CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
								 HWND  hTalk  =  NULL;
								 if  (  findTalker(  pQyMc,  &objStatusInfoU.u.imGrpMem.grpMem.idInfo_grp,  &hTalk  )  )  goto  errLabel;
								 DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hTalk  );
								 if  (  !pMgrVar  )  goto  errLabel;
								 if (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
								 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr *  )pMgrVar->pShadowInfo;
								 if  (  !pShadowMgr  )  goto  errLabel;
								 if  (  !pMgrVar->av.taskInfo.bTaskExists  )  {
									 tmppPopupMenu->EnableMenuItem(  ID_yz_shareScreen,  MF_BYCOMMAND  |  MF_GRAYED  );
								 }
								 //
								 {
									   BOOL  bExists_screen  =  FALSE;
									   int  i;
									   for  (  i  =  0;  i  <  mycountof(  pShadowMgr->resourcesInfo.info_recv.screenTasks  );  i  ++  )  {
										    INFO_recv_screenTask  *  pMem  =  &pShadowMgr->resourcesInfo.info_recv.screenTasks[i];
											if  (  pMem->idInfo_sender.ui64Id  ==  objStatusInfoU.u.imGrpMem.grpMem.idInfo_mem.ui64Id)  {
												bExists_screen  =  TRUE;
												break;
											}
									   }
									   if  (  bExists_screen  )  {
										   tmppPopupMenu->EnableMenuItem(  ID_yz_shareScreen,  MF_BYCOMMAND  |  MF_GRAYED  );
										   }
									   else  {
											 tmppPopupMenu->EnableMenuItem(  ID_yz_stopShareScreen,  MF_BYCOMMAND  |  MF_GRAYED  );										   
									   } 
									   
									   //
									   if  (  pMgrVar->av.taskInfo.bTaskExists  )  {
										   tmppPopupMenu->EnableMenuItem(  ID_qyEdit,  MF_BYCOMMAND  |  MF_GRAYED  );
									   }


								 }
					   
							 }
				   }

				   break;
		     default:
					break;
					
	 }
	
	 
	 uCmd = ::TrackPopupMenu( tmppPopupMenu->m_hMenu,  TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON  |  TPM_NONOTIFY,  x,  y, 0,  hWnd, NULL );
	 
	 if  (  !uCmd  )  goto  errLabel;
	 
	 iErr = 0;
	 
errLabel:

	 if  (  iErr  <  0 )  return  iErr;

	 return  uCmd;
	 
}




