
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

#include	"myDb.h"
#include	"qnmMainProc_nm.h"
#ifdef  __isCli__
		#include	"ctxQmc.h"
#endif
#include	"makeDynaMenu.h"





 //  µ±×÷ÎªguiÍ¨ÖªdaemonµÄº¯ÊýÊ±£¬Ê¹ÓÃNULL»ò""¸øproxyIp¸³Öµ
 //
 int  qnmTellPolicyChanged(  void  *  pQyMcParam,  char  *  proxyIp  )
{
	 int				iErr	=	-1;
	 QY_MC			*	pQyMc				=	(  QY_MC  *  )pQyMcParam;
	 QY_COMM_SESSION	session;
	 QY_SOCK			sock;
	 SOCK_TIMEOUT		to;
	 QY_COMM_RESP		resp;
	 char			*	ip		=	NULL;
	 unsigned  short	usPort	=	0;
	 unsigned  char		ucCmd;
	 QY_ENC_CTX			encCtx,  commEncCtx;
	 BOOL				bEncInited  =  FALSE;

	 if  (  !pQyMc  )  {
		 traceLogA(  "qnmTellPolicyChanged(  ) failed: pQyMc is null"  );  goto  errLabel;
	 }

	 if  (  !proxyIp  ||  !proxyIp[0]  )  {
		 ip  =  "127.0.0.1";  usPort  =  DEFAULT_qyMcServPort;  ucCmd  =  CONST_qnmAuthCmd_guiTalk;
		}
	 else  {
		   ip  =  proxyIp;  usPort  =  DEFAULT_qyCfgVal_qnmProxyPort;	ucCmd  =  CONST_qnmAuthCmd_startProxySession;
	 }

	 if  (  initQnmEnc(  &encCtx,  0,  0,  &commEncCtx  )  )  goto  errLabel;
	 bEncInited  =  TRUE;

	 memset(  &session,  0,  sizeof(  session  )  );
	 clearQySock(  &sock  );
	 setSockTimeout(  &to  );

	 if  (  !qnmOpenSession(  ip,  usPort,  NULL,  ucCmd,  CONST_qyServiceId_qwm,  qnmVerStr(  pQyMc->iServiceId  ),  &commEncCtx,  &session,  &sock,  &to,  NULL,  NULL  )  )  {
		 if  (  !qySendReq(  &session,  &sock,  &to,  CONST_qyCmd_policyChanged,  NULL,  0  )  )  {
			 qyRecvResp(  &session,  &sock,  &to,  &resp,  NULL,  0  );
			 iErr  =  0;
		 }
		 qnmCloseSession(  &session,  &sock,  &to  );
	 }


errLabel:

	 if  (  bEncInited  )  exitQnmEnc(  &encCtx,  0,  0,  &commEncCtx  );

	 traceLogA(  "Í¨Öª%s%s²ßÂÔË¢ÐÂ%s",  (  (  !proxyIp  ||  !proxyIp[0]  )  ?  "Daemon"  :  "´úÀí"  ),  ip,  iErr  ?  "Ê§°Ü"  :  "³É¹¦"  );
	 return  0;

}


 int  getKeyNameByLvType(  int  iLvType,  TCHAR  *  colName,  unsigned  int  colNameCnt  )
{
	int			iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	TCHAR	*	keyName	=	_T(  ""  );

	switch  (  iLvType  )  {
			case  CONST_qyQueryType_netMcPcList:
				  keyName  =  _T(  "MAC"  );
				  break;
			case  CONST_qyQueryType_imObjAuthList:	//  2017/08/14
			case  CONST_qyQueryType_imObjList:
			case  CONST_qyQueryType_clientList_is:
			case  CONST_qyQueryType_customerServiceList:
			case  CONST_qyQueryType_wwwQmCfgList:
				  keyName  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_idStr  );
				  break;
			default:
				    keyName  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_seqNo  );
					break;
	}

	if  (  colName  )  lstrcpyn(  colName,  keyName,  colNameCnt  );

	iErr  =  0;

//  errLabel:

	return  iErr;

	
}

 int  getLvTypeFromSth_new(  void  *  pm_docStructParam,  void  *  pSelParam,  TCHAR  *  colName,  unsigned  int  colNameCnt,  PF_commonHandler  *  ppfProcCmd  )
{
	int							iErr								=	-1;
	//  CQyMcDoc				*	pDoc								=	(  CQyMcDoc  *  )pDocParam;
	QY_MC_DOCSTRUCT			*	pm_docStruct						=	(  QY_MC_DOCSTRUCT  *  )pm_docStructParam;
	QY_MC_SEL				*	pSel								=	(  QY_MC_SEL  *  )pSelParam;
	QY_MC					*	pQyMc								=	QY_GET_GBUF(  );
	int							iLvType								=	0;
	TCHAR					*	keyName								=	_T(  ""  );


	if  (  pm_docStruct  )  {
		if  (  pm_docStruct->iDocType  ==  CONST_qyDocType_mcQuery  )  {
			iLvType  =  pm_docStruct->u.query.type;			  
		}
		}
	else  if  (  pSel  )  {
			  if  (  pSel->type  ==  CONST_qySelType_mcRootList  )  {				  	  
				  if  (  pSel->u.rootList.leftTreeSel.type  ==  CONST_qyTreeType_imObj  )
					  switch  (  pSel->u.rootList.leftTreeSel.objIndex.objType  )  {
							  case  CONST_objType_unRegGrp:	
							  case  CONST_objType_col3:		
							  case  CONST_objType_pcOpNode: 
							  case  CONST_objType_imGrp:
								    iLvType  =  CONST_qyQueryType_imObjList;		
									break;
							  case  CONST_objType_imGrps:	iLvType  =  CONST_qyQueryType_imGrpList;		break;
						  	  default:
									  break;
					  }					  
				  }
			  else  if  (  pSel->type  ==  CONST_qySelType_mcDlgLv  )  {
				        iLvType  =  pSel->u.mcDlgLv.type;
						}
			  else  if  (  pSel->type  ==  CONST_qySelType_mcView  )  {
						iLvType  =  pSel->u.mcView.type;
						if  (  ppfProcCmd  )  *ppfProcCmd  =  pSel->u.mcView.pfProcCmd;
			  }
		  }		
	else  
		goto  errLabel;


	if  (  getKeyNameByLvType(  iLvType,  colName,  colNameCnt  )  )  goto  errLabel;

	iErr  =  0;

errLabel:
	return  iErr  ?  iErr  :  iLvType;
}






#ifndef  __isCli__



#endif


/*
 int  getPcAssetInfoFromLv(  HWND  hParent,  QY_PCASSET_RCD  *  pPcAsset  )
{
	 int						iErr								=	-1;
	 int						curnItem							=	0;
	 LVITEM						lvItem;

	 if  (  !pPcAsset  )  return  -1;
	 if  (  getLvSelColContent(  hParent,  NULL,  &curnItem,  NULL,  0  )  )  goto  errLabel;
	 memset(  &lvItem,  0,  sizeof(  lvItem  )  );
	 lvItem.mask  =  LVIF_PARAM;
	 lvItem.iItem  =  curnItem;
	 if  (  !SendMessage(  hParent,  LVM_GETITEM,  0,  (  LPARAM  )&lvItem  )  )  goto  errLabel;
	 pPcAsset->id  =  lvItem.lParam;

	 iErr  =  0;
errLabel:
	 return  iErr;
}
*/

 int  getSelIdFromLv(  HWND  hParent,  int  *  pId  )
{
	 int						iErr								=	-1;
	 int						curnItem							=	0;
	 LVITEM						lvItem;

	 if  (  !pId  )  return  -1;
	 if  (  getLvSelColContent(  hParent,  &curnItem,  NULL,  NULL,  0  )  )  goto  errLabel;
	 memset(  &lvItem,  0,  sizeof(  lvItem  )  );
	 lvItem.mask  =  LVIF_PARAM;
	 lvItem.iItem  =  curnItem;
	 if  (  !SendMessage(  hParent,  LVM_GETITEM,  0,  (  LPARAM  )&lvItem  )  )  goto  errLabel;
	 *  pId  =  lvItem.lParam;

	 iErr  =  0;
errLabel:
	 return  iErr;
}



 int  delAllPcInfo(  void  *  pDb,  LPCTSTR  hint,  char  *  mac0  )
{
	 int		iErr	=  -1;
	 CString	sqlStr;

	 if  (  hint  &&  AfxMessageBox(  hint,  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
	
	 {
		 CWaitCursor	cursor;

		 //  2005/10/03
		 sqlStr  =  CString(  "mac0='"  )  +  CString(  mac0  )  +  CString(  "'"  );
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcRegInfoTab"  ),  sqlStr.GetBuffer(  0  )  )   )  goto  errLabel;
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcRegInfoTab1"  ),  sqlStr.GetBuffer(  0  )  )   )  goto  errLabel;
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcRuleTab"  ),  sqlStr.GetBuffer(  0  )  )   )  goto  errLabel;
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcAdapterTab"  ),  sqlStr.GetBuffer(  0  )  )   )  goto  errLabel;
		 //  2006/03/08
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcSecChkEventTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;										   
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcEventLogTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcOsUsrTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcNetStatTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcPrinterTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcProcessTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcSpTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
		 if  (  delPcSth(  pDb,  NULL,  _T(  "autoLogonTab"  ),  sqlStr  )  )  goto  errLabel;  //  2006/01/08
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcAssetTab"  ),  sqlStr  )  )  goto  errLabel;	//  2006/06/12
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qwmSvrTab"  ),  sqlStr  )   )  goto  errLabel;	//  2006/08/13
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcRegistryValTab"  ),  sqlStr  )   )  goto  errLabel;	//  2006/08/13
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcNetFlowTab"  ),  sqlStr  )   )  goto  errLabel;	//  2006/09/13
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcNetShareTab"  ),  sqlStr  )   )  goto  errLabel;	//  2007/02/16
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcOpQTab"  ),  sqlStr  )   )  goto  errLabel;	//  2007/02/16
 
		 //
		 if  (  delPcSth(  pDb,  NULL,  _T(  "qyPcTab"  ),  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;

	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}


 QY_OBJ_DB  *  getObjDbFromSel(  QY_MC_SEL  *  pSel  )
{
	QY_OBJ_DB	*	pObjDb	=	NULL;

	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	if  (  !pSel  )  goto  errLabel;

	switch  (  pSel->type  )  {
		    case  CONST_qySelType_mcRootTree:
				  pObjDb  =  getProcedObjDb(  pQyMc,  0,  pSel->u.rootTree.iDsnIndex  );
				  break;
			case  CONST_qySelType_mcRootList:
				  pObjDb  =  getProcedObjDb(  pQyMc,  0,  pSel->u.rootList.leftTreeSel.iDsnIndex  );
				  break;
			case  CONST_qySelType_mcView:
				  pObjDb  =  getProcedObjDb(  pQyMc,  0,  pSel->u.mcView.iDsnIndex  );
				  break;
			case  CONST_qySelType_mcDlgLv:
				  pObjDb  =  getProcedObjDb(  pQyMc,  0,  pSel->u.mcDlgLv.iDsnIndex  );
				  break;
			default:
					break;
	}

errLabel:
	return  pObjDb;
}








 







				   

/*
 QY_DMITEM  CONST_pcProcessRuleTypeTable[]  =
{
	{	CONST_ruleType_prohibit,		_T(  "½ûÖ¹"  ),				},
	{	CONST_ruleType_prohibitAll,		_T(  "Í³Ò»½ûÖ¹"  ),			},
	{	CONST_ruleType_permit,			_T(  "ÔÊÐí"  ),				},
	{	CONST_ruleType_permitAll,		_T(  "Í³Ò»ÔÊÐí"  ),			},
	{	-1,			NULL,			},
};
*/





 //
 int  getObjStatusInfo(  void  *  p0,  QY_OBJ_DB  *  pObjDb,  OBJ_STATUS_INFO  *  pU  )
{
	 int							iErr				=	0;
	 QY_MC					*		pQyMc				=	QY_GET_GBUF(  );
	 int							iServiceId			=	CONST_qyServiceId_mis;
	 QY_SERVICEGUI_INFO		*		pSci				=	getServiceGuiInfo(  pQyMc,  iServiceId  );
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;


	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;	//  2007/01/02

	 switch  (  pU->iObjType  )  {
			 case  CONST_objType_syr:
				   if  (  getPcStatusInfo(  pDbFuncs,  pObjDb->pDb,  pU->u.pc.mac0,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &pU->u.pc  )  )  goto  errLabel;
				   break;
			 case  CONST_objType_me:
				   if  (  !g_dbFuncs.pf_bGetMeInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  pU->u.messengerStatus.misServName,  &pU->u.messengerStatus.messengerInfo  )  )  {
					   pU->u.messengerStatus.idInfo.ui64Id  =  CONST_invalidMessengerId;
					   pU->u.messengerStatus.misServName[0]  =  0;
				   }
				   break;
			 case  CONST_objType_messenger:
				   if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pU->u.messengerStatus.misServName,  &pU->u.messengerStatus.idInfo,  0,  &pU->u.messengerStatus.messengerInfo,  NULL,  NULL,  &pU->u.messengerStatus.phoneInfo  )  )  {
					   pU->u.messengerStatus.idInfo.ui64Id  =  CONST_invalidMessengerId;
					   pU->u.messengerStatus.misServName[0]  =  0;				 
				   }				   
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}






//
 int  is_popupMenu_new(  void  *  pQyMcParam,  void  *  pDocStructParam,  void  *  pEventInfoParam  )
{
	 int				iErr				=		-1;
	 CMenu				tmpMenu;
	 CMenu			*	tmppPopupMenu		=		NULL;
	 UINT				uCmd				=		0;
	 UINT				uMenuId				=		0;		//	2006/12/31
	 int				nPos				=		0;		//  2006/12/31
	 QY_EVENTINFO	*	pEventInfo			=		(  QY_EVENTINFO  *  )pEventInfoParam;	 
	 //CQyMcDoc		*	pDoc				=		(  CQyMcDoc *  )pDocParam;
	 if  (  !pDocStructParam  )  return  -1;
	 QY_MC_DOCSTRUCT	&	m_docStruct		=		*(  QY_MC_DOCSTRUCT  *  )pDocStructParam;
	 TCHAR				colName[32  +  1]	=		_T(  ""  );
	 char				buf[256]			=		"";
	 TCHAR				tBuf[256];
	 QY_MC			*	pQyMc				=		QY_GET_GBUF(  );
	 QY_DMITEM		*	pItem;
	 QY_OBJ_DB		*	pObjDb				=		NULL;
	 OBJ_STATUS_INFO	objStatusInfoU;

	 //  if  (  !pDoc  )  goto  errLabel;

	 
	 QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );
	 if  (  !pResMem  )  goto  errLabel;


	 //  2006/02/11,  ÕâÀïÒªÈ¡Ò»ÏÂÒ»Ð©¸÷¸ö¶ÔÏóµÄ×´Ì¬²ÎÊýµÈ£¬¸øÔÚÐÎ³É¶¯Ì¬µÄ²Ëµ¥Ê±Ìá¹©×´Ì¬²ÎÊý
	 memset(  &objStatusInfoU,  0,  sizeof(  objStatusInfoU  )  );
	 if  (  m_docStruct.iDocType  ==  CONST_qyDocType_mcQuery  )  {

		 pObjDb  =  getProcedObjDb(  pQyMc,  0,  m_docStruct.u.query.iDsnIndex  );	//  2007/01/02
		 if  (  !pObjDb  )  goto  errLabel;
		 
		 if  (  !pEventInfo->ucbNotSelected  &&  !pEventInfo->ucbMultiSelected  )  {
			 switch  (  m_docStruct.u.query.type  )  {
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
						   HWND	hList;  hList  =  pEventInfo->hFrom;
						   _sntprintf(  colName,  mycountof(  colName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_misServName  )  );
						   if  (  getLvSelColContent(  hList,  0,  colName,  tBuf,  mycountof(  tBuf  )  )  )  tBuf[0]  =  0;
						   lstrcpyn(  objStatusInfoU.u.messengerStatus.misServName,  tBuf,  mycountof(  objStatusInfoU.u.messengerStatus.misServName  )  );
						   //
						   _sntprintf(  colName,  mycountof(  colName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_idStr  )  );
						   if  (  getLvSelColContent(  hList,  0,  colName,  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;
						   myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
						   idStr2Info(  buf,  &objStatusInfoU.u.messengerStatus.idInfo  );
						   //
						   break;
					 default:
							break;
			 } 
		 }

		 uMenuId  =  m_docStruct.u.query.uPopupMenuId;
		 //
		 if  (  pEventInfo->ucbNotSelected  )  nPos  =  m_docStruct.u.query.nSubMenuPos_notSel;
		 else  if  (  pEventInfo->ucbMultiSelected  )  nPos  =  m_docStruct.u.query.nSubMenuPos_multiSel;
		 else  nPos  =  m_docStruct.u.query.nSubMenuPos;
		 }
	 else  if  (  m_docStruct.iDocType  ==  CONST_qyDocType_mcView  )  {
			   uMenuId  =  m_docStruct.u.mcView.uPopupMenuId;
			   //
			   if  (  pEventInfo->ucbNotSelected  )  nPos  =  m_docStruct.u.mcView.nSubMenuPos_notSel;
			   else  if  (  pEventInfo->ucbMultiSelected  )  nPos  =  m_docStruct.u.mcView.nSubMenuPos_multiSel;
			   else  nPos  =  m_docStruct.u.mcView.nSubMenuPos;
			   }
	 else  { 
		   traceLogA(  "docType error"  );  goto  errLabel;		   
	 }
	 //
	 objStatusInfoU.pObjDb  =  pObjDb;		//  2007/01/07
	 getObjStatusInfo(  0,  pObjDb,  &objStatusInfoU  );



	 if  (  !uMenuId  )  goto  errLabel;
	 if  (  nPos  <  0  )  {
		 MACRO_qyAssert(  0,  _T(  "菜单位置信息应  >  0"  )  );  goto  errLabel;
	 }

	 //	 ×¢£ºÕâÀï½«×Ô¶¯Éú³É²Ëµ¥£¬¹Ê½«ÏÂÃæµÄLoad´úÂëÂÔÈ¥£¬2005/1108
	 //  if  (  !tmpMenu.LoadMenu(  uMenuId  )  )  goto errLabel;
	 //  if  ( !(  tmppPopupMenu  =  tmpMenu.GetSubMenu(  nPos  )  )  )  goto  errLabel;
	 //  
	 if  (  !(  tmpMenu.CreatePopupMenu(  )  )  )  goto  errLabel;
	 if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_popupMenu  )  )  )  goto  errLabel;
	 if  (  !(  pItem  =  qyGetDmItemByType(  pItem,  nPos,  sizeof(  QY_DMITEM  )  )  )  )  goto  errLabel;
	 if  (	 makeDynaMenu(  &pQyMc->cusRes,  tmpMenu.m_hMenu,  (  QY_DMITEM  *  )pItem->pData,  getMenuStatus,  pQyMc,  &objStatusInfoU  )  )  goto  errLabel;
	 tmppPopupMenu  = &tmpMenu;


	 if  (  m_docStruct.iDocType  ==  CONST_qyDocType_mcQuery  )  {

		 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

		 switch  (  m_docStruct.u.query.type  )  {
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
				 case  CONST_qyQueryType_imObjList:
					   switch  (  objStatusInfoU.u.messengerStatus.messengerInfo.uiType  )  {
							   case  CONST_objType_me:
							   case  CONST_objType_phoneMessenger:
								     tmppPopupMenu->EnableMenuItem(  ID_qyTalk,  MF_BYCOMMAND  |  MF_GRAYED  );					 
									 break;
							   case  CONST_objType_messenger:
								     break;
							   default:
									  break;
					   }

					   //
					   if  (  !pEventInfo->ucbNotSelected  &&  !pEventInfo->ucbMultiSelected  )  {
                           if  (  !objStatusInfoU.u.messengerStatus.phoneInfo.wDevIdStr[0]  )  tmppPopupMenu->EnableMenuItem(  ID_qySendSm,  MF_BYCOMMAND  |  MF_GRAYED  );
					   }

					   break;
				 case  CONST_qyQueryType_phoneGuestList:  {
#if  0
					   QY_SERVICEGUI_INFO		*	pSci	=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
					   if  (  !pSci  )  goto  errLabel;
					   MC_VAR_isCli				*	pProcInfo;
					   if  (  !(  pProcInfo  =  (  MC_VAR_isCli  *  )pSci->pVar  )  )  goto  errLabel;
					   //
					   if  (  !pProcInfo->bPhoneModuleLoaded  )  tmppPopupMenu->EnableMenuItem(  ID_qySendSm,  MF_BYCOMMAND  |  MF_GRAYED  );
					   
#endif
					   goto  errLabel;
					   }
					   break;
				 case  CONST_qyQueryType_imObjRuleList:  {	//  2011/11/17
					   HWND	hList  =  pEventInfo->hFrom;
					   lstrcpyn(  colName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_idStr_related  )  ,  mycountof(  colName  )  );
					   if  (  getLvSelColContent(  hList,  NULL,  colName,  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;				   
					   //
					   QY_MESSENGER_ID	idInfo_related;
					   myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
					   idStr2Info(  buf,  &idInfo_related  );
					   if  (  !idInfo_related.ui64Id  )  {
						   tmppPopupMenu->EnableMenuItem(  ID_qyRule,  MF_BYCOMMAND  |  MF_GRAYED  );
					   }

					   }
					   break;
				 default:
					    traceLogA(  "netMc_popupMenu: 未特殊处理的queryType: %d",  m_docStruct.u.query.type  );
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






 //  2012/07/21
  int  is_procEvent_new(  void  *  pQyMcParam,  void  *  pm_docStruct,  void  *  pEventInfoParam  )
{
	 int				iErr				=	-1;
	 QY_EVENTINFO	*	pEventInfo			=	(  QY_EVENTINFO  *  )pEventInfoParam;
	 int				iRet;
	 unsigned  int		uCmd;
	 QY_MC			*	pQyMc				=	(  QY_MC  *  )pQyMcParam;
	 TCHAR				colName[255  +  1]	=	_T(  ""  );

	 switch  (  pEventInfo->type  )  {
			 case  CONST_qyEventType_rClick:
				   iRet  =  is_popupMenu_new(  pQyMc,  pm_docStruct, pEventInfo  );
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

#if  10
	 switch  (  uCmd  )  {
			 case  ID_qySendMsg:
				   //  netMc_procSendMsg(  pQyMc,  pDoc,  pEventInfo  );
				   traceLogA(  "Not finished. ID_qySendMsg"  );
				   break;
			 case  ID_qyTalkToTaskPeer:
			 case  ID_qyProp_imTask:
				   is_procLvEventFunc_new(  pQyMc,  pm_docStruct,  NULL,  pEventInfo,  uCmd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_seqNo  )  );  //  CONST_colName_seqNo  );
				   break;
			 default:  {
				   		//
				        switch  (  pQyMc->iServiceId  )  {
								case  CONST_qyServiceId_is:  
									  if  (  getLvTypeFromSth_new(  pm_docStruct,  NULL,  colName,  mycountof(  colName  ),  NULL  )  <  0  )  goto  errLabel;
									  is_procLvEventFunc_new(  pQyMc,  pm_docStruct,  NULL,  pEventInfo,  uCmd,  colName  );
									  break;
								case  CONST_qyServiceId_netMc:
									  is_procLvEventFunc_new(  pQyMc,  pm_docStruct,  NULL,  pEventInfo,  uCmd,  _T(  "MAC"  )  );
									  break;
								default:
										break;
						}
				   }
				   break;				   
	 }
#endif

	 iErr  =  0;

errLabel:

	 return  iErr;
	 
}


 BOOL  bNetMcViewScannedIpList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	 return  bNetMcViewScannedIpListFunc(  pQyMc,  pObjDb,  _T(  ""  ),  _T(  ""  )  );
}

 BOOL  bNetMcViewPcList(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb   )
{
	 return  bNetMcViewPcListFunc(  pQyMc,  pObjDb,  _T(  ""  ),  _T(  ""  )  );
}

 BOOL  bNetMcViewPcSpList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	 return  bNetMcViewPcSpListFunc(  pQyMc,  pObjDb,  _T(  ""  ),  _T(  ""  )  );
}

#if  0	//  2013/02/16

 QY_DMITEM  CONST_qwmDevTypeTable[]  =
{
	{	CONST_qwmDevType_wpd,				_T(  "Portable device"  ),  },
	{	CONST_qwmDevType_mobileDevice,		_T(  "Mobile device"  ),  },
	{	CONST_qwmDevType_usbNetworkCard,	_T(  "Usb network card"  ),  },
	{	-1,										},
};


 void  *  iidisplayQnmElement(  void * pVoid,  void  *  pQueryParam,  void  *  pQyRcdset,  int  nSubItem,  TCHAR * output,  unsigned  int  size  )
{
	 int				iErr		=	-1;
	 QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	 QY_MC_QUERY	*	pQuery		=	(  QY_MC_QUERY  *  )pQueryParam;
	 CQyRcdset		*	pRecordset  =	(  CQyRcdset  *  )pQyRcdset;
	 CString			tmpStr;
	 int				iType;
	 TCHAR			*	pStopString;
	 char				buf[1024];
	 char				tmpBuf[1024];
	 QY_DMITEM		*	pTable;

	 
	 //  traceLogA(  "displayQnmElement: µÚ%d¸öµ¥Ôª",  nSubItem  );
	 //  2004/04/17Ôö¼Ó¶ÔNullÖµµÄÅÐ¶Ï
	 if  (  pRecordset->IsFieldNull(  pRecordset->m_arrayValue[nSubItem]  )  )  {
		 _sntprintf(  output,  size,  _T(  ""  )  );
		 iErr  =  0;  goto  errLabel;
	 }

	 switch  (  pQuery->columns[nSubItem].type  )  {
			 case  CONST_qyColumnDisplayType_long:  
				   _sntprintf(  output,  size,  _T(  "%d"  ),  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  )  );
				   break;
			 case  CONST_qyColumnDisplayType_uLong:		//  2005/10/04
				   _sntprintf(  output,  size,  _T(  "%u"  ),  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  )  );
				   break;
			 case  CONST_qyColumnDisplayType_bool:  
				   tmpStr  =  *(  CString  *  )pRecordset->m_arrayValue[nSubItem];
				   
				   MACRO_CStringTrim(  tmpStr  );
				   if  (  !tmpStr.GetLength(  )  )  _sntprintf(  output,  size,  _T(  ""  )  );						
				   else  _sntprintf(  output, size,  _T(  "%s"  ),  _tcstol(  tmpStr.GetBuffer(  0  ),  &pStopString,  10  )  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_y  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_n  )  );
				   
				   break;
			 case  CONST_qyColumnDisplayType_iBool:  {
				   int		iBool  =	*(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  ); 
				   _sntprintf(  output,  size,  _T(  "%s"  ),  iBool  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_y  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_n  )  );
				   }
				   break;
			 case  CONST_qyColumnDisplayType_dwRegVal:  {
				   DWORD		dwVal  =	*(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  ); 
				   if  (  dwVal  ==  CONST_dwRegVal_invalid  )  _sntprintf(  output,  size,  _T(  ""  )  );
				   else  _sntprintf(  output,  size,  _T(  "%d"  ),  dwVal  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_eventType:  {
	 	 		   long		eventType	=  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  ); 
		 		   TCHAR  *  ptr			=  _T(  ""  );

		 		   ptr  =  qyGetDesByType1(  pQyMc->pQnmEventTypeTable0,  eventType  );
		 		   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  ptr  )  );					
		 			 }
					break;
			 case  CONST_qyColumnDisplayType_time:  {
				   CString  eventTime;
				
				   eventTime  =  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  );
				   if  (  eventTime  ==  CString(  CONST_qyNullTime  )  )  eventTime  =  CString(  ""  );
				   myTChar2Str(  eventTime.GetBuffer(  0  ),  buf,  sizeof(  buf  )  );
				   if  (  !qyDisplayTime(  buf,  tmpBuf,  sizeof(  tmpBuf  )  )  )  tmpBuf[0]  =  0;
				   myStr2TChar(  tmpBuf,  output,  size  ); 
					}
				   break;
			 case  CONST_qyColumnDisplayType_lTime:  {
				   CString  eventTime;
				
				   eventTime  =  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  );
				   if  (  eventTime  ==  CString(  CONST_qyNullTime  )  )  eventTime  =  CString(  ""  );
				   myTChar2Str(  eventTime.GetBuffer(  0  ),  buf,  sizeof(  buf  )  );
				   if  (  !qyDisplaylTime(  buf,  tmpBuf,  sizeof(  tmpBuf  )  )  )  tmpBuf[0]  =  0;
				   myStr2TChar(  tmpBuf,  output,  size  ); 
				   }
				   break;
			 case  CONST_qyColumnDisplayType_bOnLine:  {
				   CString  eventTime;
				   //
				   eventTime  =  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  );
				   //
				   if  (  eventTime.GetLength(  )  !=  CONST_qyTimeLen  ||  eventTime  ==  CString(  CONST_qyNullTime  )  )  _sntprintf(  output,  size,  _T(  ""  )  );
				   else  {
					     myTChar2Str(  eventTime.GetBuffer(  0  ),  buf,  sizeof(  buf  )  );
						 _sntprintf(  output,  size,  bPcOnline(  buf  )  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_online  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_offline  )  );
				   }				   
				    }				   
				   break;
			 case  CONST_qyColumnDisplayType_ip12:  {
				   char  ipBuf[CONST_qyMaxIpLen  +  1];

				   myTChar2Str(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ),  buf,  sizeof(  buf  )  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyIp12ToStd(  buf,  ipBuf  )  ?  ipBuf  :  ""  )  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_mac:  
				   //  myTChar2Str(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ), tmpBuf,  sizeof(  tmpBuf  )  );
				   //  _strlwr(  tmpBuf  );
				   //  myStr2TChar(  tmpBuf,  output,  size  );
				   tmpStr  =  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  );
				   tmpStr.MakeLower(  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  tmpStr  );			   
				   //  if  (  !strcmpi(  output,  CONST_qyNullMac  )  )  output[0]  =  0;	//  2005/10/10, ½«qyNullMacµÄÏÔÊ¾¸³Îª¿Õ
				   break;
			 case  CONST_qyColumnDisplayType_lwrStr:
				   //  lstrcpyn(  output,  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  ),  size  );
				   //  myTChar2Str(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ), output,  size  );
				   //  _strlwr(  output  );
				   tmpStr  =  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  );
				   tmpStr.MakeLower(  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  tmpStr  );			   
				   break;
			 case  CONST_qyColumnDisplayType_uprStr:
				   //  lstrcpyn(  output,  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  ),  size  );
				   //  myTChar2Str(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ), output,  size  );
				   //  _strupr(  output  );
				   tmpStr  =  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  );
				   tmpStr.MakeUpper(  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  tmpStr  );			   
				   break;
			 case  CONST_qyColumnDisplayType_pcSp:
				   //  lstrcpyn(  output,  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  ),  size  );
				   //  myTChar2Str(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ), output,  size  );
				   //  _strupr(  output  );
				   //  if  (  !strcmp(  output,  CONST_qnmNullPcSp  )  )  _snprintf(  output,  size,  ""  );
				   tmpStr  =  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  );
				   tmpStr.MakeUpper(  );
				   if  (  tmpStr  ==  CString(  CONST_qnmNullPcSp  )  )  tmpStr  =  CString(  ""  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  tmpStr  );			   
				   break;
			 case  CONST_qyColumnDisplayType_rasCmd:  {
				   unsigned  char  ucRasCmd;
		 		   TCHAR  *  ptr  =  _T(  ""  );

				   if  (  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetLength(  )  )  {
					   myTChar2Str( (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ),  buf,  sizeof(  buf  )  ); 
				   	   ucRasCmd  =  buf[0];
		 		   	   ptr  =  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qnmRasCmdTable  ),  ucRasCmd  );
		 		   }
		 		   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  ptr  )  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_devCmd:  {
				   unsigned  char  ucCmd;
				   TCHAR  *  ptr  =  _T(  ""  ); 
				   
				   if  (  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetLength(  )  )  {
				   	   myTChar2Str( (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ),  buf,  sizeof(  buf  )  ); 
				   	   ucCmd  =  buf[0];
		 		   	   ptr  =  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qnmDevCmdTable0  ),  ucCmd  );
		 		   }
		 		   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  ptr  )  );				
					}
				   break;	
			 case  CONST_qyColumnDisplayType_netFlowRule:  {	//  Î´Íê³É
				   unsigned  char		ucCmd;
				   TCHAR			*	ptr				=	_T(  ""  ); 
				   unsigned  int		uiWarnPercent	=	0;
				   
				   if  (  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetLength(  )  >=  5  )  {
				   	   myTChar2Str( (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ),  buf,  sizeof(  buf  )  ); 
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
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  )  )  )  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_assetType:  {
				   pTable  =  CONST_assetTypeTable;
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString  (  qyGetDesByType1(  pTable,  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  )  )  )  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_langId:  {
				   pTable  =  CONST_qyLangTable;
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  )  )  )  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_jqlx:  {
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_jqlxTable  );
				   iType  =  _tcstol(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ),  &pStopString,  10  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_ruleCmd:  {
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_adapterType:  
				   pTable  =  CONST_adapterTypeTable;
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%d %s"  ),  iType,  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_pcNetworkPropType:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcCommTypeTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_snmpBool:  {
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   	}
				    break;
			 case  CONST_qyColumnDisplayType_pcAdapterStatus:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcAdapterStatusTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_iRootKey:
				   pTable  =  CONST_iRootKeyTable_abbr;
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_regType:
				   pTable  =  CONST_regTypeTable;
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_pcEventLogType:
				   pTable  =  CONST_pcEventLogTypeTable;
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_pcEventId:
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%d"  ),  iType  &  0xffff  );
				   break;
			 case  CONST_qyColumnDisplayType_pcCommType:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcCommTypeTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_tcpState:
				   pTable  =  CONST_tcpStateTable;
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 //case  CONST_qyColumnDisplayType_pcProcessRuleType:
			//	   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcProcessRuleTypeTable  );
			//	   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
			//	   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
			//	   break;
			 case  CONST_qyColumnDisplayType_qyStatus:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyStatusTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_withFactor:						//  2006/05/30
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%.3f"  ),  (  float  )iType  /  CONST_fakedFactor_percentOfBand  );
				   break;
			 case  CONST_qyColumnDisplayType_netShareType:
				   pTable  =  CONST_netShareTypeTable;
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_qwmDevType:  //  2011/09/21
				   pTable  =  CONST_qwmDevTypeTable;	//  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_jqlxTable  );
				   iType  =  _tcstol(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ),  &pStopString,  10  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_idStr:
				   _sntprintf(  output,  size,  _T(  "%u"  ),  _tcstol(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ),  &pStopString,  10  )  );
				   break;
			 case  CONST_qyColumnDisplayType_objType:				 				   
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_imTaskType:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_usRunningStatus:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_usRunningStatusTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_ruleType:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleTypeTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 default:
				 	 _sntprintf(  output,  size,  _T(  "%s"  ),  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  )  );
					 unescapeTStr(  output,  size  );
					 break;
	 }
		
	 iErr  =  0;

errLabel:

	
	 return  !iErr  ?  output  :  NULL;

}
#endif






 /*
 extern  "C"  char  *  qyGetQyMcAppName(  )
{
	 char			*	pAppName			=	NULL;
	 static  char		defaultAppName[128]	=	"QyMc";
	 int				iSystemId			=	qyGetSystemId(  );
	 QY_DMITEM		*	pAppNameTable		=	NULL;

	 if  (  !pAppName  )  {
		 //  LoadString(  GetModuleHandle(  NULL  ),  IDR_MAINFRAME,  defaultAppName,  sizeof(  defaultAppName  )  );
		 pAppName  =  defaultAppName;
	 }
	 return  pAppName;
}
*/


 BOOL  bViewAllOpEventList(  QY_MC  *pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	 //QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	 TCHAR			eventTypeName[128]  =	_T(  "" );
	 TCHAR			whereClause[1024]	=	_T(  ""  );
	 QY_DMITEM	*	pItem				=	NULL;

	 _sntprintf(  eventTypeName,  mycountof(  eventTypeName  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_allSystemEvent  )  );
	 
	 if  (  pQyMc->cfg.pGuiCfg  &&  pQyMc->pQnmEventTypeTable_op  )  {
		 pItem  =  pQyMc->pQnmEventTypeTable_op;
		 if  (  pItem->type  !=  -1  )  {
			 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "eventType in (%d"  ),  pItem->type  );
			 pItem  ++  ;
			 for  (  ;  pItem->type  !=  -1;  pItem  ++  )  {
		 		  _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s,%d"  ),  whereClause,  pItem->type  );
	 		 }
			 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s)"  ),  whereClause  );
		 }
	 }	 

	 bViewOpEventListFunc(  pQyMc,  pObjDb,  eventTypeName,  whereClause  );
	 return  FALSE;
}

 BOOL  bViewAllEventList_is(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	 //QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	 TCHAR			eventTypeName[128]  =	_T(  ""  );
	 TCHAR			whereClause[1024]	=	_T(  ""  );
	 QY_DMITEM	*	pItem				=	NULL;

	 //  lstrcpyn(  eventTypeName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_computer  ),  mycountof(  eventTypeName  )  );
	 _sntprintf(  eventTypeName,  mycountof(  eventTypeName  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_computer  )  );

	 
	 if  (  pQyMc->cfg.pGuiCfg  &&  pQyMc->pQnmEventTypeTable_pc  )  {
		 pItem  =  pQyMc->pQnmEventTypeTable_pc;
		 if  (  pItem->type  !=  -1  )  {
			 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "eventType in (%d"  ),  pItem->type  );
			 pItem  ++  ;
			 for  (  ;  pItem->type  !=  -1;  pItem  ++  )  {
		 		  _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s,%d"  ),  whereClause,  pItem->type  );
	 		 }
			 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s)"  ),  whereClause  );
		 }
	 }	 

	 return  bViewEventListFunc_is(  pQyMc,  pObjDb,  eventTypeName,  whereClause  );
}

 
  BOOL  bViewAllEventList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
 {
	 if  (  !pObjDb  )  return  FALSE;

	 switch  (  qyGetServiceId(  pObjDb->cfg.iSystemId  )  )  {
		     case  CONST_qyServiceId_netMc:
				   return  bViewAllPcEventList_netMc(  pObjDb  );
			 case  CONST_qyServiceId_is:
				   return  bViewAllEventList_is(  pQyMc,  pObjDb  );
			 default:
					break;
	 }
	 return  FALSE;
 }


 BOOL  bNetMcViewAllNetDevEventList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb )
{
	 //QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	 TCHAR			eventTypeName[128]  =	_T(  ""  );
	 TCHAR			whereClause[1024]	=	_T(  ""  );
	 QY_DMITEM	*	pItem				=	NULL;

	 _sntprintf(  eventTypeName,  mycountof(  eventTypeName  ),  _T(  "%s " ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_wangLuoSheBei  )  );
	 
	 if  (  pQyMc->cfg.pGuiCfg  &&  pQyMc->pQnmEventTypeTable_netDev  )  {
		 pItem  =  pQyMc->pQnmEventTypeTable_netDev;
		 if  (  pItem->type  !=  -1  )  {
			 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "eventType in (%d"  ),  pItem->type  );
			 pItem  ++  ;
			 for  (  ;  pItem->type  !=  -1;  pItem  ++  )  {
		 		  _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s,%d"  ),  whereClause,  pItem->type  );
	 		 }
			 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s)"  ),  whereClause  );
		 }
	 }	 

	 return  bNetMcViewNetDevEventListFunc(  pQyMc,  pObjDb,  eventTypeName,  whereClause  );
}

 BOOL  bNetMcViewRasEventList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	 TCHAR			eventTypeName[128]  =	_T(  ""  );
	 TCHAR			whereClause[1024];

	 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "eventType in (%d,%d,%d)"  ),  CONST_qyEventType_nm_rasStart,  CONST_qyEventType_nm_rasEnd,  CONST_qyEventType_nm_rasProhibited  );
	
	 return  bNetMcViewRasEventListFunc(  pQyMc,  pObjDb,  eventTypeName,  whereClause  );

}

 BOOL  bNetMcViewDevChangedEventList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	 //QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	 TCHAR			eventTypeName[128]  =	_T(  ""  );
	 TCHAR			whereClause[1024];

	 lstrcpyn(  eventTypeName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_macChanged  ),  mycountof(  eventTypeName  )  );

	 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "eventType=%d"  ),  CONST_qyEventType_nm_macsModified  );
	
	 return  bViewPcEventListFunc_netMc(  pQyMc,  pObjDb,  eventTypeName,  whereClause  );

}


 BOOL  bNetMcViewQwmDelEventList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	 //QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	 TCHAR			eventTypeName[128]  =	_T(  ""  );
	 TCHAR			whereClause[1024];

	 lstrcpyn(  eventTypeName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_invalidQwm  ),  mycountof(  eventTypeName  )  );
	 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "eventType in(%d,%d,%d)"  ),  CONST_qyEventType_nm_qwmDel,  CONST_qyEventType_nm_qwmDelRecovery,  CONST_qyEventType_nm_qwmDelOffline  );
	
	 return  bViewPcEventListFunc_netMc(  pQyMc,  pObjDb,  eventTypeName,  whereClause  );

}

 BOOL  bNetMcViewProxyServerEventList( QY_MC  *  pQyMc, QY_OBJ_DB  *  pObjDb  )
{
	 //QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	 TCHAR			eventTypeName[128]  =	_T(  ""  );
	 TCHAR			whereClause[1024];

	 lstrcpyn(  eventTypeName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_checkForProxyServer  ),  mycountof(  eventTypeName  )  );
	 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "eventType in(%d,%d)"  ),  CONST_qyEventType_nm_proxyServerSet,  CONST_qyEventType_nm_proxyServerClear  );
	
	 return  bViewPcEventListFunc_netMc(  pQyMc,  pObjDb,  eventTypeName,  whereClause  );

}


 BOOL  bNetMcViewIntraConnEventList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	 //QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	 TCHAR			eventTypeName[128]  =	_T(  ""  );
	 TCHAR			whereClause[1024];

	 lstrcpyn(  eventTypeName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyIntraConn  ),  mycountof(  eventTypeName  )  );
	 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "eventType in(%d,%d,%d)"  ),  CONST_qyEventType_nm_strangePc,  CONST_qyEventType_nm_strangePcUnderCtrl,  CONST_qyEventType_nm_strangePcOffline  );

	 return  bViewPcEventListFunc_netMc(  pQyMc,  pObjDb,  eventTypeName,  whereClause  );

}

 BOOL  bNetMcViewOnInternetEventList( QY_MC  *  pQyMc, QY_OBJ_DB  *  pObjDb  )
{
	 //QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	 TCHAR			eventTypeName[128]  =	_T(  ""  );
	 TCHAR			whereClause[1024];

	 lstrcpyn(  eventTypeName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyOnInternet  ),  mycountof(  eventTypeName  )  );
	 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "eventType in(%d,%d)"  ),  CONST_qyEventType_nm_onInternet,  CONST_qyEventType_nm_offInternet  );

	 return  bViewPcEventListFunc_netMc(  pQyMc,  pObjDb,  eventTypeName,  whereClause  );

}



 //  ÏÖÔÚÊ¹ÓÃ½»»»»úÊÓÍ¼£¬ÒÔºóÓÃÍØÆËÊÓÍ¼Ìæ»»
 BOOL  bNetMcViewNetwork(  QY_OBJ_DB  *  pObjDb  )
{
	 return  bNetMcViewSwitchFunc(  pObjDb,  _T(  ""  ),  "", ""  );
}


 //  ÍøÂç½»»»»úÊÓÍ¼
 BOOL  bNetMcViewSwitchFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart,  char  *  selectedSwitchMac,  char  *  selectedMac  )
{
	 QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	 QY_MC_SEL	sel;

	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	 //  2008/09/07
	 if  (  g_pQyMc->curUsrInfo.scope.bRestricted  )  return  FALSE;
	 
	 memset(  &sel,  0,  sizeof(  sel  )  );
	 sel.type				=  CONST_qySelType_mcRootTree;
	 _sntprintf(  sel.u.rootTree.wherePart,  mycountof(  sel.u.rootTree.wherePart  ),  _T(  "%s"  ),  wherePart  ?  wherePart  :  _T(  ""  )  );
	 _snprintf(  sel.u.rootTree.selectedSwitchMac,  sizeof(  sel.u.rootTree.selectedSwitchMac  ),  "%s",  selectedSwitchMac  ?  selectedSwitchMac  :  ""  );
	 _snprintf(  sel.u.rootTree.selectedMac,  sizeof(  sel.u.rootTree.selectedMac  ),  "%s",  selectedMac  ?  selectedMac  :  ""  );
	 sel.u.rootTree.pfProcTreeSel  =  netMc_procTreeSel;
	 sel.u.rootTree.pfProcEvent  =  netMc_procTreeEvent;
	 sel.u.rootTree.bRoot	=  TRUE;
	 sel.u.rootTree.type	=  CONST_qyTreeType_switch;
	 sel.u.rootTree.iDsnIndex	=	pObjDb->iDsnIndex;
	 _sntprintf(  sel.u.rootTree.docName,  mycountof(  sel.u.rootTree.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyNetworkView )  );
	 if  (  bMacValid(  selectedMac  )  )  sel.u.rootTree.ucbSetFocusOnRightView  =  TRUE;
	 
	 return  bQyMcNewTreeListView(  &sel  );

}


 //  ÓÃ»§½ÓÈë¹ÜÀíÊÓÍ¼
 BOOL  bNetMcViewUsrConnection(  QY_OBJ_DB  *  pObjDb )
{	 
	 QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	 QY_MC_SEL	sel;

	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	 //  2008/09/07
	 if  (  g_pQyMc->curUsrInfo.scope.bRestricted  )  return  FALSE;

	 memset(  &sel,  0,  sizeof(  sel  )  );
	 sel.type				=  CONST_qySelType_mcRootTree;
	 sel.u.rootTree.pfProcTreeSel  =  netMc_procTreeSel;
	 sel.u.rootTree.pfProcEvent  =  netMc_procTreeEvent;
	 sel.u.rootTree.bRoot	=  TRUE;
	 sel.u.rootTree.type	=  CONST_qyTreeType_usrConnection;
	 sel.u.rootTree.iDsnIndex	=	pObjDb->iDsnIndex;
	 _sntprintf(  sel.u.rootTree.docName,  mycountof(  sel.u.rootTree.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyConnectionView  )  );
	 
	 return  bQyMcNewTreeListView(  &sel  );

}

 BOOL  bNetMcViewNetworkSpeed(  QY_OBJ_DB  *  pObjDb  )
{
	 QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	 QY_MC_SEL	sel;

	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	 //  2008/09/07
	 if  (  g_pQyMc->curUsrInfo.scope.bRestricted  )  return  FALSE;

	 memset(  &sel,  0,  sizeof(  sel  )  );
	 sel.type				=  CONST_qySelType_mcRootTree;
	 sel.u.rootTree.pfProcTreeSel  =  netMc_procTreeSel;
	 sel.u.rootTree.pfProcEvent  =  netMc_procTreeEvent;
	 sel.u.rootTree.bRoot	=  TRUE;
	 sel.u.rootTree.type	=  CONST_qyTreeType_networkSpeed;
	 sel.u.rootTree.iDsnIndex	=	pObjDb->iDsnIndex;
	 _sntprintf(  sel.u.rootTree.docName,  mycountof(  sel.u.rootTree.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyNetworkSpeedView  )  );
	 
	 return  bQyMcNewTreeListView(  &sel  );

}


 BOOL  bNetMcViewSnmpObjRuleList(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpSnmpObjRuleListQueryStruct  );
	int						i;

	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_snmpObjRuleList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;

	for  (  i  =  0;  i  <  tmpSel.u.query.nSqlFields;  i  ++  )  {
		 if  (  !i  )  _sntprintf(  tmpSel.u.query.selectPart,  sizeof(  tmpSel.u.query.selectPart  )  /  sizeof(  TCHAR  ),  _T(  "select %s"  ),  CString(  tmpSel.u.query.sqlColumns[0].label  )  );
		 else  _sntprintf(  tmpSel.u.query.selectPart,  sizeof(  tmpSel.u.query.selectPart  )  /  sizeof(  TCHAR  ),  _T(  "%s,%s"  ),  CString(  tmpSel.u.query.selectPart  ),  CString(  tmpSel.u.query.sqlColumns[i].label  )  );
	}	
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (  (qySnmpObjRuleTab left join qySnmpObjTab on qySnmpObjRuleTab.switchMac=qySnmpObjTab.mac) left join qySwitchPortTab on (  qySnmpObjRuleTab.switchMac=qySwitchPortTab.switchMac and qySnmpObjRuleTab.portIfIndex=qySwitchPortTab.portIfIndex  )  )  left join qySnmpObjPolicyTab on qySnmpObjTab.ip=qySnmpObjPolicyTab.ip "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  ""  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qySnmpObjTab.productName,qySnmpObjRuleTab.iType,qySwitchPortTab.portIfIndex"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  26;


	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_snmpObjRuleList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}

 BOOL  bNetMcViewConflictConnList( QY_MC  *  pQyMc, QY_OBJ_DB  *  pObjDb  )
{
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpConflictConnListQueryStruct  );
	int						i;

	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_conflictConnList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;

	for  (  i  =  0;  i  <  tmpSel.u.query.nSqlFields;  i  ++  )  {
		 if  (  !i  )  _sntprintf(  tmpSel.u.query.selectPart,  sizeof(  tmpSel.u.query.selectPart  )  /  sizeof(  TCHAR  ),  _T(  "select %s"  ),  CString(  tmpSel.u.query.sqlColumns[0].label  )  );
		 else  _sntprintf(  tmpSel.u.query.selectPart,  sizeof(  tmpSel.u.query.selectPart  )  /  sizeof(  TCHAR  ),  _T(  "%s,%s"  ),  CString(  tmpSel.u.query.selectPart  ),  CString(  tmpSel.u.query.sqlColumns[i].label  )  );
	}	
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (  (qnmConflictConnTab left join qySnmpObjTab on qnmConflictConnTab.switchMac=qySnmpObjTab.mac) left join qySwitchPortTab on (  qnmConflictConnTab.switchMac=qySwitchPortTab.switchMac and qnmConflictConnTab.portIfIndex=qySwitchPortTab.portIfIndex  )  )  left join qyPcTab on (qnmConflictConnTab.connectedMac=qyPcTab.mac0 or qnmConflictConnTab.connectedMac=qyPcTab.mac1 or qnmConflictConnTab.connectedMac=qyPcTab.mac2)"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  ""  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qySnmpObjTab.productName,qySwitchPortTab.portIfIndex"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  27;


	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_conflictConnList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


 BOOL  bNetMcViewDirectConnList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	BOOL					bRet	=	FALSE;
	//QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	//  CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpDirectConnListQueryStruct  );
	int						i;

	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	tmpSel.u.query.type			=	CONST_qyQueryType_directConnList;
	if  (  setQueryColumns(  pQyMc,  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;

	for  (  i  =  0;  i  <  tmpSel.u.query.nSqlFields;  i  ++  )  {
		 if  (  !i  )  _sntprintf(  tmpSel.u.query.selectPart,  sizeof(  tmpSel.u.query.selectPart  )  /  sizeof(  TCHAR  ),  _T(  "select %s"  ),  CString(  tmpSel.u.query.sqlColumns[0].label  )  );
		 else  _sntprintf(  tmpSel.u.query.selectPart,  sizeof(  tmpSel.u.query.selectPart  )  /  sizeof(  TCHAR  ),  _T(  "%s,%s"  ),  CString(  tmpSel.u.query.selectPart  ),  CString(  tmpSel.u.query.sqlColumns[i].label  )  );
	}	
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  " from (((qySwitchConnectedPcTab left join qySnmpObjTab on qySwitchConnectedPcTab.switchMac=qySnmpObjTab.mac) left join qySwitchPortTab on (  qySwitchConnectedPcTab.switchMac=qySwitchPortTab.switchMac and qySwitchConnectedPcTab.portIfIndex=qySwitchPortTab.portIfIndex  )  )  left join qyPcTab on (qySwitchConnectedPcTab.connectedMac=qyPcTab.mac0 or qySwitchConnectedPcTab.connectedMac=qyPcTab.mac1 or qySwitchConnectedPcTab.connectedMac=qyPcTab.mac2)) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  ""  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "qySnmpObjTab.productName,qySwitchPortTab.portIfIndex"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  0;


	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_directConnList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


 //  ·µ»Ø£º-1£¬		Ê§°Ü
 //		   uiCmd,	´¥·¢µÄ²Ëµ¥ÃüÁî  
 int  netMc_procLvDblClick(  void  *  pQyMcParam,  void  *  pCurSelParam,  void  *  pEventInfoParam  )
{
	 int						iRet				=		-1;
	 QY_MC					*	pQyMc				=		(  QY_MC  *  )pQyMcParam;
	 QY_MC_SEL				*	pSel				=		(  QY_MC_SEL  *  )pCurSelParam;		
	 QY_EVENTINFO			*	pEventInfo			=		(  QY_EVENTINFO  *  )pEventInfoParam;

	 if  (  pSel->type  ==  CONST_qySelType_mcRootList  )  {

	 	 if  (  pSel->u.rootList.leftTreeSel.bRoot  )  {
			 iRet  =  ID_dblClickToFocusOnItem;  goto  errLabel;
		 }

		 switch  (  pSel->u.rootList.leftTreeSel.objIndex.objType  )  {
				 case  CONST_objType_qySwitch:
				 case  CONST_objType_qySwitchPort:
				 case  CONST_objType_pcEnv:  
					   iRet  =  ID_qyProperties;  break;
				 default:  
						 iRet  =  ID_dblClickToFocusOnItem;  break;
		 }
		}
	 else  if  (  pSel->type  ==  CONST_qySelType_mcRootTree  )  {

		       if  (  pSel->u.rootTree.bRoot  )  goto  errLabel;

			   switch  (  pSel->u.rootTree.objIndex.objType  )  {
					   case  CONST_objType_me:				iRet  =  ID_qyProperties;  //ID_imTaskList_unproced;  
															break;
					   case  CONST_objType_syr:
					   case  CONST_objType_messenger:		iRet  =  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  ID_qyTalk  :  ID_qyProperties;		break;
					   case  CONST_objType_imGrp:			iRet  =  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  ID_qyDiscuss  :  ID_qyProperties;	break;
					   default:
								goto  errLabel;
			   }
		}
	 else  if  (  pSel->type  ==  CONST_qySelType_mcDlgLv  )  {
			   iRet  =  pSel->u.mcDlgLv.uiDefaultCmd;
			   }
	 else  if  (  pSel->type  ==  CONST_qySelType_mcView  )  {		//  2008/01/02
		       iRet  =  pSel->u.mcView.uiDefaultCmd;
			   }
	 else  goto  errLabel;

	 
errLabel:
	 
	 return  iRet;
 
}

 int  dblClickToOpenItem(  void  *  pQyMcParam,  void  *  pCurSelParam,  void  *  pEventInfoParam  )  
{
	 int						iRet				=		-1;
	 QY_MC					*	pQyMc				=		(  QY_MC  *  )pQyMcParam;
	 QY_MC_SEL				*	pSel				=		(  QY_MC_SEL  *  )pCurSelParam;		
	 QY_EVENTINFO			*	pEventInfo			=		(  QY_EVENTINFO  *  )pEventInfoParam;
	 QY_WMBUF_FOCUSONITEM		wmBuf;
	 TCHAR						tBuf[256];

	 if  (  pSel->type  !=  CONST_qySelType_mcRootList  )  goto  errLabel;
	 memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
	 wmBuf.uiType		=  CONST_qyWmParam_focusOnItem;
	 wmBuf.bRoot	=  pSel->u.rootList.leftTreeSel.bRoot;	
	 wmBuf.htItem	=  pSel->u.rootList.leftTreeSel.hItem;
	 if  (  getLvSelColContent(  pEventInfo->hWnd,  NULL,  NULL,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  )  )  goto  errLabel;
	 lstrcpyn(  wmBuf.name,  tBuf,  sizeof(  wmBuf.name  )  /  sizeof(  TCHAR  )  );
	 
	 if  (  SendMessage(  pEventInfo->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  )  !=  CONST_qyWmRc_ok  )  goto  errLabel;
	 
	 iRet  =  0;
errLabel:
	 return  iRet;
}


 //  2004/07/26
 BOOL  bNetMcViewAssets(  QY_OBJ_DB  *  pObjDb  )
{
	 QY_MC_SEL	sel;
	 QY_MC		*	pQyMc	=  QY_GET_GBUF( );

	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	 memset(  &sel,  0,  sizeof(  sel  )  );
	 sel.type								=  CONST_qySelType_mcRootTree;
	 sel.u.rootTree.pfProcTreeSel			=  netMc_procTreeSel;
	 sel.u.rootTree.pfProcEvent				=  netMc_procTreeEvent;
	 sel.u.rootTree.pfDisplayContent		=  displayContent_assets;
	 sel.u.rootTree.pfRefreshItem			=  refreshItem_assets;
	 sel.u.rootTree.pfDisplayListContent	=  displayListContent_assets;
	 sel.u.rootTree.bRoot					=  TRUE;
	 sel.u.rootTree.type					=  CONST_qyTreeType_pc;
	 sel.u.rootTree.iDsnIndex				=  pObjDb->iDsnIndex;		//  2007/01/03
	 _sntprintf(  sel.u.rootTree.docName,  mycountof(  sel.u.rootTree.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyAssetsView  )  );
	 
	 return  bQyMcNewTreeListView(  &sel  );

}

  //  2006/06/12
 BOOL  bNetMcViewPcView(  QY_OBJ_DB  *  pObjDb  )
{
	 QY_MC_SEL	sel;
	 QY_MC		*	pQyMc	=  QY_GET_GBUF( );

	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	 memset(  &sel,  0,  sizeof(  sel  )  );
	 sel.type								=  CONST_qySelType_mcRootTree;
	 sel.u.rootTree.pfProcTreeSel			=  netMc_procTreeSel;
	 sel.u.rootTree.pfProcEvent				=  netMc_procTreeEvent;
	 sel.u.rootTree.pfDisplayContent		=  displayContent_assets;
	 sel.u.rootTree.pfRefreshItem			=  refreshItem_assets;
	 sel.u.rootTree.pfDisplayListContent	=  displayListContent_assets;
	 sel.u.rootTree.bRoot					=  TRUE;
	 sel.u.rootTree.type					=  CONST_qyTreeType_pc;
	 sel.u.rootTree.iDsnIndex				=  pObjDb->iDsnIndex;
	 _sntprintf(  sel.u.rootTree.docName,  mycountof(  sel.u.rootTree.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyPcView  )  );
	 
	 return  bQyMcNewTreeListView(  &sel  );

}


#if  0
 //  2005/01/23¼Ó£¬ÓÃÓëÅäÖÃ°²×°²¹¶¡
 BOOL  bNetMcCfgSp(  )
{
	 QY_MC_SEL	sel;

	 memset(  &sel,  0,  sizeof(  sel  )  );
	 sel.type								=  CONST_qySelType_mcRootTree;
	 sel.u.rootTree.pfProcTreeSel			=  netMc_procTreeSel;
	 sel.u.rootTree.pfProcEvent				=  netMc_procTreeEvent;
	 sel.u.rootTree.pfDisplayContent		=  displayContent_cfgSp;
	 sel.u.rootTree.pfRefreshItem			=  refreshItem_cfgSp;
	 sel.u.rootTree.pfDisplayListContent	=  displayListContent_cfgSp;
	 sel.u.rootTree.bRoot					=  TRUE;
	 sel.u.rootTree.type					=  CONST_qyTreeType_cfgSp;
	 _sntprintf(  sel.u.rootTree.docName,  mycountof(  sel.u.rootTree.docName  ),  _T(  "%s"  ),  _T(  "补丁库配置"  )  );
	 
	 return  bQyMcNewTreeListView(  &sel  );

}
#endif




 __declspec(  dllexport  ) int  netMc_procTreeSel(  void  *  pQyMcParam,  void  *  p0,  void  *  p1  )
{
	 int			iErr	=	-1;
	 QY_MC		*	pQyMc	=	(  QY_MC  *  )pQyMcParam;
	 QY_MC_SEL	*	pSel	=	(  QY_MC_SEL  *  )p0;
	 QY_OBJ_DB	*	pObjDb	=	NULL;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	 
	 if  (  !pQyMc  ||  !p0  )  goto  errLabel;

	 MACRO_qyAssert(  pSel->type  ==  CONST_qySelType_mcRootTree,  _T(  "netMc_procTreeSel类型不对"  )  );
	 pObjDb  =  getProcedObjDb(  pQyMc,  0,  pSel->u.rootTree.iDsnIndex  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	 if  (  pSel->u.rootTree.bRoot  )  {
		 iErr  =  0;  goto  errLabel;
	 }
	 if  (  g_dbFuncs.pf_getObjIndex(  pObjDb,  pSel->u.rootTree.iHelpId,  &pSel->u.rootTree.objIndex  )  )  goto  errLabel;
	 //
	 switch  (  pSel->u.rootTree.objIndex.objType  )  {
			 case  CONST_objType_qySwitchPort:  {
				   char  switchMac[CONST_qyMacLen  +  1];
		 		   myTChar2Str(  pSel->u.rootTree.objIndex.objIdStr0,  switchMac,  sizeof(  switchMac  )  );
		 		   //
		 		   if  (  !bGetPortInfoBySth(  pObjDb->pDb,  switchMac,  pSel->u.rootTree.objIndex.objId0,  0,  0,  &pSel->u.rootTree.u.switchPort,  NULL  )  )  goto  errLabel;
	 			   }
				   break;
			 case  CONST_objType_imGrp:  {  //  2017/07/29
				   QY_MESSENGER_ID  idInfo;  
				   char  buf[128];
				   myTChar2Utf8(  pSel->u.rootTree.objIndex.objIdStr0,  buf,  mycountof(  buf  )  );idStr2Info(  buf,  &idInfo  );
				   if  (  !pDbFuncs->pf_bGetImGrpInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  _T(  ""  ),  &idInfo,  &pSel->u.rootTree.u.imGrpInfo   )  )  goto  errLabel;
				   }
				   break;
			 default:
					break;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}




//
 int  netMc_procMcViewEvent(  void  *  pQyMc,  void  *  pSel,  void  *  pEventInfoParam  )
{
	 return  netMc_procTreeEvent(  pQyMc,  pSel,  pEventInfoParam  );
}



 //
#ifdef  __isCli__
	    int  nms_popupMenu_isCli(  void  *  pQyMcParam,  int  x,  int  y,  void  *  pCurSelParam,  void  *  pEventInfoParam,  void  *  pMenuContext  );
#else
	    int  nms_popupMenu_isMgr(  void  *  pQyMcParam,  int  x,  int  y,  void  *  pCurSelParam,  void  *  pEventInfoParam,  void  *  pMenuContext  );
#endif


 //
 __declspec(  dllexport  )  int  netMc_procTreeEvent(  void  *  pQyMcParam,  void  *  pSel,  void  *  pEventInfoParam  )
{
	 int				iErr				=	-1;
	 QY_MC			*	pQyMc				=	(  QY_MC  *  )pQyMcParam;
	 QY_EVENTINFO	*	pEventInfo			=	(  QY_EVENTINFO  *  )pEventInfoParam;
	 int				iRet;
	 unsigned  int		uCmd;


	 switch  (  pEventInfo->type  )  {
			 case  CONST_qyEventType_rClick:
				   #ifdef  __isCli__
						   iRet  =  nms_popupMenu_isCli(  pQyMc,  pEventInfo->click.x,  pEventInfo->click.y,  pSel,  pEventInfo,  0  );
				   #else
						   iRet  =  nms_popupMenu_isMgr(  pQyMc,  pEventInfo->click.x,  pEventInfo->click.y,  pSel,  pEventInfo,  0  );
				   #endif
				   if  (  iRet  <  0  )  goto  errLabel;
				   uCmd  =  iRet;
				   break;
			 case  CONST_qyEventType_dblClick:
				   if  (  (  iRet  =  netMc_procLvDblClick(  pQyMc,  pSel,  pEventInfo  )  )  <  0  )  goto  errLabel;
				   uCmd  =  iRet;
				   break;
			 case  CONST_qyEventType_cmd:
				   uCmd  =  pEventInfo->uiCmd;
				   break;
			 default:
					goto  errLabel;
	 }

	 pEventInfo->uiCmd  =  uCmd;		//  2008/01/02

#ifndef  __isCli__
	 if  (  qmProcCmd_mgr(  pQyMc,  pSel,  pEventInfo  )  )  goto  errLabel;
#else
	 if  (  qmProcCmd_isCli(  pQyMc,  pSel,  pEventInfo  )  )  goto  errLabel;
#endif
	 
	 iErr  =  0;

errLabel:

	 return  iErr;
	 
}

 BOOL  bGetMacDesByMac(  void  *  pDbParam,  char  *  mac,  QNM_MACDES_RCD  *  pMacDes  )
{
	 BOOL			bRet			=		FALSE;
	 CDBVariant		varVals[10];
	 CString		sqlStr;
	 int			index			=		0;
	 char			ip12[256  +  1];
	 TCHAR			tBuf[1024];

	 sqlStr  =  CString(  "select ip,devType,des0 from qnmMacDesTab where mac='"  )  +  CString(  mac  )  +  CString(  "'"  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;

	 memset(  pMacDes,  0,  sizeof(  pMacDes[0]  )  );

	 //  mac
	 safeStrnCpy(  mac,  pMacDes->mac,  sizeof(  pMacDes->mac  )  );
	 index  =  0;	//  ip
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  pMacDes->ip  );  
	 index  ++  ;	//  devType
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pMacDes->devType,  tBuf,  mycountof(  pMacDes->devType  )  );  
	 index  ++  ;  //  des0
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pMacDes->des0,  tBuf,  mycountof(  pMacDes->des0  )  );  
	 index  ++  ;	//  

	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}










