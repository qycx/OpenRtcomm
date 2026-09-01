

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include	"qyRestrictEdit.h"

#ifndef  __isCli__
#include	"dlgEditSwitchInfo.h"
#include	"DlgQnmEditMacInfo.h"
#include	"DlgQnmSnmpObjPortProperties.h"
#endif
//  #include	"dlgNum.h"
#include	"qyCusResTemp.h"
#include	"qnmMainProc_nm.h"

//
int  qmProcCmd_isCli(  void  *  pQyMcParam,  void  *  pSelParam,  void  *  pEventInfoParam  )
{
	 int							iErr			=		-1;
	 QY_MC						*	pQyMc			=		(  QY_MC  *  )pQyMcParam;
	 QY_MC_SEL					*	pSel			=		(  QY_MC_SEL  *  )pSelParam;
	 QY_EVENTINFO				*	pEventInfo		=		(  QY_EVENTINFO  *  )pEventInfoParam;
	 unsigned  int					uiCmd			=		pEventInfo->uiCmd;						//  char  *  colName  )
	 QY_WMBUF_PROCTV				wmBuf;
	 char							sqlBuf[1024  +  1];
	 char							buf[1024  +  1];
	 QNM_PC_EVENT					nmEvent;
	 char							switchMac[CONST_qyMacLen  +  1];
	 QY_OBJ_DB					*	pObjDb			=		NULL;


	 switch  (  pSel->type  )  {		//  2007/01/02
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

	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	 switch  (  pSel->type  )  {

			 case  QY_SELTYPE_MCROOTTREE:			//  0				  
			 case  QY_SELTYPE_MCROOTLIST:			//  10
				  
				   switch  (  uiCmd  )  {
						   case  ID_secureMac:					
						   case  ID_cancelSecureMac:
						   case  ID_qyProperties:
						   case  ID_qyEdit_portUsrInfo:
						   case  ID_qyCancel_portUsrInfo:
						   case  ID_qyDel_connection:
						   case  ID_qySearch_mac:
						   case  ID_qySearchConnection:
						   case  ID_qyDel:
						   default:
							     if  (  pSel->type  ==  CONST_qySelType_mcRootTree  )  mc_procTvEventFunc(  pQyMc,  NULL,  pSelParam,  pEventInfoParam,  uiCmd,  _T(  ""  )  );
								 else  {
									   TCHAR	*	pColName	=	_T(  "mac"  );
									   //
                                       if  (  pSel->type  ==  CONST_qySelType_mcRootList  )  {
										   switch  (  pSel->u.rootList.leftTreeSel.type  )  {
												   case  CONST_qyTreeType_imObj:
													     pColName  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_idStr  );
														 break;														 
												   default:
														   break;
										   }
									   }
									   netMc_procLvEventFunc(  pQyMc,  NULL,  pSelParam,  pEventInfoParam,  uiCmd,  pColName  );
								 }
								 break;						   	     
				   }
				   //
				   break;
			 case  QY_SELTYPE_MCBARLOG:
#if  0
				   if  (  uiCmd  ==  ID_NEWURLBROWSER || uiCmd == DEFAULT_QYMCCMD )  {
					   bQyMcNewWebView(  pSel  );  break;
				   }
				   if  (  uiCmd  ==  ID_NEWIE  )  {
					   bQyMcNewIe(  pSel  );  break;
				   }
#endif
				   
				   qyDebugHint( _T(  "qyMcProcCmd(  ): selTypeMcLog, uCmd error." )  );
								  	
				   break;
			 case  CONST_qySelType_mcView:
				   netMc_procLvEventFunc(  pQyMc,  NULL,  pSelParam,  pEventInfoParam,  uiCmd,  _T(  "ID"  )  );
				   break;
			 case  CONST_qySelType_mcDlgLv:
				   #ifdef  __isCli__
						   is_procLvEventFunc_new(  pQyMc,  NULL,  pSelParam,  pEventInfoParam,  uiCmd,  _T(  "ID"  )  );
				   #else
						netMc_procLvEventFunc(  pQyMc,  NULL,  pSelParam,  pEventInfoParam,  uiCmd,  _T(  "ID"  )  );
				   #endif
				   break;
			default:
					goto errLabel;
	 }

	 iErr	=	0;

errLabel:
	 
	 return  iErr;

}

