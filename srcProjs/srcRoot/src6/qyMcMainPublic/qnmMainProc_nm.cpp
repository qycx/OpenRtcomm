

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyWmComm.h"
#include	"myresource.h"
#include	"qyRestrictEdit.h"

#ifndef  __isCli__
#include	"dlgCfgStandardName.h"
#endif

#ifndef  __isCli__
#include	"dlgPropPcNetwork.h"
#endif
#include	"qyOpenShellCommon.h"

#ifndef  __isCli__
	#include	"dlgImGrp.h"
#endif


#ifndef  __isCli__
#include	"dlgWwwQmContact.h"
#include	"dlgCfgIpKnowledge.h"
#include	"dlgPropIpKnowledge.h"

#include	"DlgMessenger.h"

#include	"dlgCfgPhoneMessenger.h"
#include	"dlgCfgGsmModem.h"
#endif


#ifndef  __isCli__
#include	"DlgCfgCustomerService.h"
#endif
//
//#include	"qmcDynBmp.h"
//
#include	"qyCusResTemp.h"
#include	"tmpCeLib.h"

#include	"qyMcDoc.h"
#include	"myDb.h"
#include	"makeDynaMenu.h"

//
 int  getObjStatusInfo(  void  *  p0,  QY_OBJ_DB  *  pObjDb,  OBJ_STATUS_INFO  *  pU  );
  int  netMc_procLvEventFunc(  void  *  pQyMcParam,  void  *  pDocParam,  void  *  pSelParam,  void  *  pEventInfoParam,  unsigned  int  uiCmd,  LPCTSTR  colName  );


 int  netMc_popupMenu(  void  *  pQyMcParam,  void  *  pDocParam,  void  *  pEventInfoParam  )
{
	 int				iErr				=		-1;
	 CMenu				tmpMenu;
	 CMenu			*	tmppPopupMenu		=		NULL;
	 UINT				uCmd				=		0;
	 UINT				uMenuId				=		0;		//	2006/12/31
	 int				nPos				=		0;		//  2006/12/31
	 QY_EVENTINFO	*	pEventInfo			=		(  QY_EVENTINFO  *  )pEventInfoParam;	 
	 CQyMcDoc		*	pDoc				=		(  CQyMcDoc *  )pDocParam;
	 TCHAR				colName[32  +  1]	=		_T(  ""  );
	 char				buf[256]			=		"";
	 TCHAR				tBuf[256];
	 QY_MC			*	pQyMc				=		QY_GET_GBUF(  );
	 QY_DMITEM		*	pItem;
	 QY_OBJ_DB		*	pObjDb				=		NULL;
	 OBJ_STATUS_INFO	objStatusInfoU;
	 
	 QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;

	 if  (  !pDoc  )  goto  errLabel;
	 
	 QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );
	 if  (  !pResMem  )  goto  errLabel;
	 





	 //  2006/02/11,  ÕâÀïÒªÈ¡Ò»ÏÂÒ»Ð©¸÷¸ö¶ÔÏóµÄ×´Ì¬²ÎÊýµÈ£¬¸øÔÚÐÎ³É¶¯Ì¬µÄ²Ëµ¥Ê±Ìá¹©×´Ì¬²ÎÊý
	 memset(  &objStatusInfoU,  0,  sizeof(  objStatusInfoU  )  );
	 if  (  pDoc->m_docStruct.iDocType  ==  CONST_qyDocType_mcQuery  )  {

		 pObjDb  =  getProcedObjDb(  pQyMc,  0,  pDoc->m_docStruct.u.query.iDsnIndex  );	//  2007/01/02
		 if  (  !pObjDb  )  goto  errLabel;
		 
		 if  (  !pEventInfo->ucbNotSelected  &&  !pEventInfo->ucbMultiSelected  )  {
			 switch  (  pDoc->m_docStruct.u.query.type  )  {
					 case  CONST_qyQueryType_netMcPcList:  

						   _sntprintf(  colName,  mycountof(  colName  ),  _T(  "MAC"  )  );
						   if  (  getLvSelColContent(  pEventInfo->hWnd,  0,  colName,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  )  )  goto  errLabel;
						   myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );

						   objStatusInfoU.iObjType  =  CONST_objType_syr;  
						   safeStrnCpy(  buf,  objStatusInfoU.u.pc.mac0,  sizeof(  objStatusInfoU.u.pc.mac0  )  );
						   break;
					 case  CONST_qyQueryType_imObjList:
						   objStatusInfoU.iObjType  =  CONST_objType_messenger;
						   //  
						   _sntprintf(  colName,  mycountof(  colName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_misServName  )  );
						   if  (  getLvSelColContent(  pEventInfo->hWnd,  0,  colName,  tBuf,  mycountof(  tBuf  )  )  )  tBuf[0]  =  0;
						   lstrcpyn(  objStatusInfoU.u.messengerStatus.misServName,  tBuf,  mycountof(  objStatusInfoU.u.messengerStatus.misServName  )  );
						   //
						   _sntprintf(  colName,  mycountof(  colName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_idStr  )  );
						   if  (  getLvSelColContent(  pEventInfo->hWnd,  0,  colName,  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;
						   myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
						   idStr2Info(  buf,  &objStatusInfoU.u.messengerStatus.idInfo  );
						   //
						   break;
					 default:
							break;
			 } 
		 }

		 uMenuId  =  pDoc->m_docStruct.u.query.uPopupMenuId;
		 //
		 if  (  pEventInfo->ucbNotSelected  )  nPos  =  pDoc->m_docStruct.u.query.nSubMenuPos_notSel;
		 else  if  (  pEventInfo->ucbMultiSelected  )  nPos  =  pDoc->m_docStruct.u.query.nSubMenuPos_multiSel;
		 else  nPos  =  pDoc->m_docStruct.u.query.nSubMenuPos;
		 }
	 else  if  (  pDoc->m_docStruct.iDocType  ==  CONST_qyDocType_mcView  )  {
			   uMenuId  =  pDoc->m_docStruct.u.mcView.uPopupMenuId;
			   //
			   if  (  pEventInfo->ucbNotSelected  )  nPos  =  pDoc->m_docStruct.u.mcView.nSubMenuPos_notSel;
			   else  if  (  pEventInfo->ucbMultiSelected  )  nPos  =  pDoc->m_docStruct.u.mcView.nSubMenuPos_multiSel;
			   else  nPos  =  pDoc->m_docStruct.u.mcView.nSubMenuPos;
			   }
	 else  { 
		   #ifdef  __DEBUG__
				   traceLogA(  "docType error"  );  
		   #endif
		   goto  errLabel;		   
	 }
	 //
	 objStatusInfoU.pObjDb  =  pObjDb;		//  2007/01/07
	 getObjStatusInfo(  0,  pObjDb,  &objStatusInfoU  );



	 if  (  !uMenuId  )  goto  errLabel;
	 if  (  nPos  <  0  )  {
		 MACRO_qyAssert(  0,  _T(  "菜单位置信息应  >  0"  )  );  
		 goto  errLabel;
	 }

	 //	 2005/1108
	 //  
	 if  (  !(  tmpMenu.CreatePopupMenu(  )  )  )  goto  errLabel;
	 if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_popupMenu  )  )  )  goto  errLabel;
	 if  (  !(  pItem  =  qyGetDmItemByType(  pItem,  nPos,  sizeof(  QY_DMITEM  )  )  )  )  goto  errLabel;
	 if  (	 makeDynaMenu(  &pQyMc->cusRes,  tmpMenu.m_hMenu,  (  QY_DMITEM  *  )pItem->pData,  getMenuStatus,  pQyMc,  &objStatusInfoU  )  )  goto  errLabel;
	 tmppPopupMenu  = &tmpMenu;


	 if  (  pDoc->m_docStruct.iDocType  ==  CONST_qyDocType_mcQuery  )  {

		 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

		 switch  (  pDoc->m_docStruct.u.query.type  )  {
				 case  CONST_qyQueryType_netMcPcList:  {
					   if  (  !pEventInfo->ucbNotSelected  &&  !pEventInfo->ucbMultiSelected  )  {
						   QNM_PC_RULES		pcRules;

						   _sntprintf(  colName,  mycountof(  colName  ),  _T(  "MAC"  )  );
						   if  (  getLvSelColContent(  pEventInfo->hWnd,  0,  colName,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  )  )  goto  errLabel;
						   myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
						   memset(  &pcRules,  0,  sizeof(  pcRules  )  );
						   if  (  bGetPcRule(  pQyMc->cfg.ucbAdvancedVer,  pObjDb->pDb,  buf,  &pcRules  )  &&  pcRules.secChk.ucbDoSecChk  )  tmppPopupMenu->EnableMenuItem(  ID_doSecChk,  MF_BYCOMMAND  |  MF_GRAYED  );
						   else  tmppPopupMenu->EnableMenuItem(  ID_undoSecChk,  MF_BYCOMMAND  |  MF_GRAYED  );
						   if  (  !bMacValid(  objStatusInfoU.u.pc.regInfo.mac0  )  )  tmppPopupMenu->EnableMenuItem(  ID_qyCfgStandardName,  MF_BYCOMMAND  |  MF_GRAYED  );	//  2006/09/03
						   //  2005/10/02, ½«·¢ËÍÏûÏ¢µÄ²Ëµ¥ÒÆÈ¥£¬ÒÔ±ÜÃâÀÏÓÐÈËÑ¯ÎÊ·¢ËÍÏûÏ¢µÄ¹¦ÄÜ
						   tmppPopupMenu->RemoveMenu(  ID_qySendMsg,  MF_BYCOMMAND  );
						   break;
					   }
					   }
					   break;
 				 case  CONST_qyQueryType_netMcPcSpList:  {
					   char  lastTimeBuf[32  +  1]	=	"",  pcSpBuf[32  +  1]  =	"";
				   			   
					   //  _snprintf(  colName,  sizeof(  colName  ),  "%s",  "×î½ü¼ì²éÊ±¼ä"  );
					   lstrcpyn(  colName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_zuiJinJianCeShiJian  ),  mycountof(  colName  )  );
					   if  (  getLvSelColContent(  pEventInfo->hWnd,  NULL,  colName,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  )  )  goto  errLabel;				   
					   myTChar2Str(  tBuf,  lastTimeBuf,  sizeof(  lastTimeBuf  )  );
					   _sntprintf(  colName,  mycountof(  colName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_buDing  )  );  //  _T(  "²¹¶¡"  )  );
					   if  (  getLvSelColContent(  pEventInfo->hWnd,  NULL,  colName,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  )  )  goto  errLabel;				   
					   myTChar2Str(  tBuf,  pcSpBuf,  sizeof(  pcSpBuf  )  );
					   trim(  lastTimeBuf  );  trim(  pcSpBuf  );
					   if  (  !lastTimeBuf[0]  )  tmppPopupMenu->EnableMenuItem(  ID_qyDelPcSp, MF_BYCOMMAND  |  MF_GRAYED   );
					   if  (  !pcSpBuf[0]  )  {					   
						   tmppPopupMenu->EnableMenuItem(  ID_qySearchPcSp, MF_BYCOMMAND  |  MF_GRAYED   );
						   tmppPopupMenu->EnableMenuItem(  ID_qyCusPcSp, MF_BYCOMMAND  |  MF_GRAYED   );
					   }
				   
						}
					   break;
				 case  CONST_qyQueryType_pcNetDevConnList:  {

					   if  (  pQyMc->curUsrInfo.scope.bRestricted  )  {
						   tmppPopupMenu->EnableMenuItem(  ID_qySearchSwitchPort, MF_BYCOMMAND  |  MF_GRAYED   );
					   }

					   }
					   break;
			     case  CONST_qyQueryType_netDevEventList:  {
					   char  buf[CONST_qyMacLen  +  1]	=	"";
				   	
					   if  (  pQyMc->curUsrInfo.scope.bRestricted  )  {
						   tmppPopupMenu->EnableMenuItem(  ID_qySearchSwitchPort, MF_BYCOMMAND  |  MF_GRAYED   );
					   }

					   lstrcpyn(  colName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_lianJieMAC  ),  mycountof(  colName  )  );
					   if  (  getLvSelColContent(  pEventInfo->hWnd,  NULL,  colName,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  )  )  goto  errLabel;				   
					   myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
					   if  (  !bMacValid(  buf  )  )  {
						   tmppPopupMenu->EnableMenuItem(  ID_qyProperties_viewNetDevConn, MF_BYCOMMAND  |  MF_GRAYED   );
					   }
					   }				   
					   break;
				 case  CONST_qyQueryType_ip:
				 case  CONST_qyQueryType_mac:  {
					   //  char  buf[CONST_qyMacLen  +  1]	=	"";
				   			   
					   lstrcpyn(  colName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_leiXing  )  ,  mycountof(  colName  )  );
					   if  (  getLvSelColContent(  pEventInfo->hWnd,  NULL,  colName,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  )  )  goto  errLabel;				   
					   //  myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
					   if  (  lstrcmpi(  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_wangLuoSheBei  )    )  )  {
						   tmppPopupMenu->EnableMenuItem(  ID_qySearchSwitchPort, MF_BYCOMMAND  |  MF_GRAYED   );
					   }

					   }
					   break;
				 case  CONST_qyQueryType_imObjAuthList:  {
					   int  iLvType  =  pDoc->m_docStruct.u.query.type;
					   if  (  getKeyNameByLvType(  iLvType,  colName,  mycountof(  colName  )  )  )  goto  errLabel;	
					   //
					   if  (  !getLvSelColContent(  pEventInfo->hWnd,  NULL,  colName,  tBuf,  mycountof(  tBuf  )  )  )  {
						   myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
						   //
						   QY_MESSENGER_ID  idInfo;
						   idStr2Info(  buf,  &idInfo  );
						   //
						   QY_MESSENGERAUTH_RCD  rcd;
						   //
						   if  (  bGetMessengerAuthRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  _T(  ""  ),  &idInfo,  NULL,  NULL,  0,  &rcd  )  )  {
							   //
							   if  (  rcd.iRole  ==  CONST_imObjRole_superAdmin  )  {								
								   tmppPopupMenu->EnableMenuItem(  ID_setAsSuperAdmin,  MF_BYCOMMAND  |  MF_GRAYED  );					 								
								   }
							   else  {
								     tmppPopupMenu->EnableMenuItem(  ID_notSuperAdmin,  MF_BYCOMMAND  |  MF_GRAYED  );					 																   
							   }
							   //
							   int  ii  =  0;
						   }

					   }
					   }
					   break;
					   //
				 case  CONST_qyQueryType_imObjList:
					   switch  (  objStatusInfoU.u.messengerStatus.messengerInfo.uiType  )  {
							   case  CONST_objType_me:
							   case  CONST_objType_phoneMessenger:
								     tmppPopupMenu->EnableMenuItem(  ID_qyTalk,  MF_BYCOMMAND  |  MF_GRAYED  );					 
									 break;
							   case  CONST_objType_messenger:
								     //
								     if  (  objStatusInfoU.u.messengerStatus.messengerInfo.iRole  ==  CONST_imObjRole_superAdmin  )  tmppPopupMenu->EnableMenuItem(  ID_setAsSuperAdmin,  MF_BYCOMMAND  |  MF_GRAYED  );
								     else  tmppPopupMenu->EnableMenuItem(  ID_notSuperAdmin,  MF_BYCOMMAND  |  MF_GRAYED  );
									 //
								     break;
							   default:
									  break;
					   }

					   //
					   if  (  !pEventInfo->ucbNotSelected  &&  !pEventInfo->ucbMultiSelected  )  {
                           if  (  !objStatusInfoU.u.messengerStatus.phoneInfo.wDevIdStr[0]  )  tmppPopupMenu->EnableMenuItem(  ID_qySendSm,  MF_BYCOMMAND  |  MF_GRAYED  );
					   }

					   break;

#if  0
				 case  CONST_qyQueryType_phoneGuestList:  {
					   QY_SERVICEGUI_INFO		*	pSci	=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
					   if  (  !pSci  )  goto  errLabel;
					   MC_VAR_isCli				*	pProcInfo;
					   if  (  !(  pProcInfo  =  (  MC_VAR_isCli  *  )pSci->pVar  )  )  goto  errLabel;
					   //
					   if  (  !pProcInfo->bPhoneModuleLoaded  )  tmppPopupMenu->EnableMenuItem(  ID_qySendSm,  MF_BYCOMMAND  |  MF_GRAYED  );
					   }
					   break;
#endif
				 case  CONST_qyQueryType_imObjRuleList:  {	//  2011/11/17
					   lstrcpyn(  colName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_idStr_related  )  ,  mycountof(  colName  )  );
					   if  (  getLvSelColContent(  pEventInfo->hWnd,  NULL,  colName,  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;				   
					   //
					   QY_MESSENGER_ID	idInfo_related;
					   myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
					   idStr2Info(  buf,  &idInfo_related  );
					   if  (  !idInfo_related.ui64Id  )  {
						   tmppPopupMenu->EnableMenuItem(  ID_qyRule,  MF_BYCOMMAND  |  MF_GRAYED  );
					   }

					   }
					   break;
				 case  CONST_qyQueryType_imGrpMemList:  {  //  2015/07/28
					   int  iLvType  =  pDoc->m_docStruct.u.query.type;
					   if  (  getKeyNameByLvType(  iLvType,  colName,  mycountof(  colName  )  )  )  goto  errLabel;	
					   //
					   if  (  !getLvSelColContent(  pEventInfo->hWnd,  NULL,  colName,  tBuf,  mycountof(  tBuf  )  )  )  {
						   myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
						   //
						   IM_GRP_MEM						grpMem;				
						   //
						   if  (  !g_dbFuncs.pf_bGetImGrpMemBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  NULL,  NULL,  NULL,  atol(  buf  ),  &grpMem  )  )  goto  errLabel;
						   //
						   if  (  grpMem.iRole  ==  CONST_imGrpMemRole_mgr  )  {
							   tmppPopupMenu->EnableMenuItem(  ID_setAsMgr,  MF_BYCOMMAND  |  MF_GRAYED  );
							   }
						   else  {
							     tmppPopupMenu->EnableMenuItem(  ID_notMgr,  MF_BYCOMMAND  |  MF_GRAYED  );						      
						   }					   								
					   }
					   //
					   }
					   break;
				 default:
					    #ifdef  __DEBUG__
								traceLogA(  "netMc_popupMenu: 未特殊处理的queryType: %d",  pDoc->m_docStruct.u.query.type  );
						#endif
						break;					
		}
	 }
	 
	 uCmd = ::TrackPopupMenu( tmppPopupMenu->m_hMenu,  TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON  |  TPM_NONOTIFY,  pEventInfo->click.x,  pEventInfo->click.y, 0,  pEventInfo->hWnd, NULL );
	 
	 if  (  !uCmd  )  goto  errLabel;
	 
	 iErr = 0;
	 
errLabel:

	 if  (  iErr  <  0 )  return  iErr;

	 return  uCmd;

}


 int  netMc_procEvent(  void  *  pQyMcParam,  void  *  pDoc,  void  *  pEventInfoParam  )
{
	 int				iErr				=	-1;
	 QY_EVENTINFO	*	pEventInfo			=	(  QY_EVENTINFO  *  )pEventInfoParam;
	 int				iRet;
	 unsigned  int		uCmd;
	 QY_MC			*	pQyMc				=	(  QY_MC  *  )pQyMcParam;
	 TCHAR				colName[255  +  1]	=	_T(  ""  );

	 switch  (  pEventInfo->type  )  {
			 case  CONST_qyEventType_rClick:
				   iRet  =  netMc_popupMenu(  pQyMc,  pDoc, pEventInfo  );
				   if  (  iRet  <  0  )  goto  errLabel;
				   uCmd  =  iRet;
				   break;
			 case  CONST_qyEventType_dblClick:
				   uCmd  =  pEventInfo->uiDefaultCmd  ?  pEventInfo->uiDefaultCmd  :  ID_qyProperties;
				   break;
			 case  CONST_qyEventType_cmd:
				   uCmd  =  pEventInfo->uiCmd;
				   break;
			 default:
					goto  errLabel;
	 }


	 switch  (  uCmd  )  {
			 case  ID_qySendMsg:
				   //  netMc_procSendMsg(  pQyMc,  pDoc,  pEventInfo  );
				   traceLogA(  "Not finished. ID_qySendMsg"  );
				   break;
			 case  ID_qyRefreshVlanPolicy:
				   netMc_procLvEventFunc(  pQyMc,  pDoc,  NULL,  pEventInfo,  uCmd,  _T(  "IP"  )  );
				   break;			 
			 case  ID_qyProperties_viewNetDevConn:
				   netMc_procLvEventFunc(  pQyMc,  pDoc,  NULL,  pEventInfo,  uCmd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_lianJieMAC  )  );  //  _T(  "Áª½ÓMAC"  )  );
				   break;
			 case  ID_qyProp_pcNetwork:  
			 case  ID_qyEdit_pcNetwork:		
			 case  ID_qyDel_pcNetwork:		
			 case  ID_editModuleKnowlege:
			 case  ID_delModuleKnowlege:
			 case  ID_qyProp_pcModuleKnowlege:
				   netMc_procLvEventFunc(  pQyMc,  pDoc,  NULL,  pEventInfo,  uCmd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_seqNo  )  );  //  CONST_colName_seqNo  );
				   break;
			 case  ID_addModuleKnowlege:
				   netMc_procLvEventFunc(  pQyMc,  pDoc,  NULL,  pEventInfo,  uCmd,  NULL  );
				   break;
			 case  ID_qyTalkToTaskPeer:
			 case  ID_qyProp_imTask:
				   netMc_procLvEventFunc(  pQyMc,  pDoc,  NULL,  pEventInfo,  uCmd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_seqNo  )  );  //  CONST_colName_seqNo  );
				   break;
			 default:  {
				   		//
				        switch  (  pQyMc->iServiceId  )  {
								case  CONST_qyServiceId_is:  
									  CQyMcDoc  *  pDoc1;
									  pDoc1  =  (  CQyMcDoc  *  )pDoc;
									  if  (  !pDoc1  )  goto  errLabel;
									  if  (  getLvTypeFromSth_new(  &pDoc1->m_docStruct,  NULL,  colName,  mycountof(  colName  ),  NULL  )  <  0  )  goto  errLabel;
									  netMc_procLvEventFunc(  pQyMc,  pDoc,  NULL,  pEventInfo,  uCmd,  colName  );
									  break;
								case  CONST_qyServiceId_netMc:
									  netMc_procLvEventFunc(  pQyMc,  pDoc,  NULL,  pEventInfo,  uCmd,  _T(  "MAC"  )  );
									  break;
								default:
										break;
						}
				   }
				   break;				   
	 }

	 iErr  =  0;

errLabel:

	 return  iErr;
	 
}

 int  showCfgView(  void  *  p0,  void  *  p1,  void  *  pbStop  )
{
	 CQyMcDoc  *  pDoc  =  (  CQyMcDoc  *  )p1;
	 QY_MC_DOCSTRUCT  *  pDocStruct  =  (  QY_MC_DOCSTRUCT  *  )&pDoc->m_docStruct;

	 switch  (  pDocStruct->iDocType  )  {
			 case  CONST_qyDocType_mcRootTree:
				   if  (  pDocStruct->u.treeList.tree.type  !=  (  int  )p0  )  return  -1;
				   break;
			 case  CONST_qyDocType_mcQuery:
				   if  (  pDocStruct->u.query.type  !=  (  int  )p0  )  return  -1;
				   break;
			 default:
				     return  -1;
	 }
	 POSITION  pos  =  pDoc->GetFirstViewPosition(  );
	 CString  title;
	 if  (  pos  )  pDoc->GetNextView(  pos  )->GetParentFrame(  )->BringWindowToTop(  );  
	 if  (  pbStop  )  (  *(  BOOL  *  )pbStop  )  =  TRUE;
	 
	 return  0;
}



