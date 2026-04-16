

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qyWmComm.h"

#include	"myresource.h"

#include	"qyCusResTemp.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcDynBmp.h"
#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"
#include	"dlgDynBmpsProc.h"
//  #include	"dlgTalk.h"
#include	"dlgtalkproc.h"
#include	"qyDynLib.h"
#include	"qmcCmdProc.h"
//
#include	"isCmdConst.h"
//
#include	"myDb.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
#include	"qmcTaskInfo.h"
#include	"isCliD3dPublic.h"
#include	"ctxQmc.h"

#include	"qmcCommFunc_iscli.h"



//
__declspec(  dllexport  )  int  doCmd_test(  int  iMenuId  )
{
	QY_MC  *  pQyMc	=	QY_GET_GBUF(  );
	QM_dbFuncs  &  g_dbFuncs  =  *pQyMc->p_g_dbFuncs;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	switch  (  iMenuId  )  {
				//
			case  ID_activeImObjList:		//  2012/04/21
				  pFuncs->mainWnd.pf_bViewActiveImObjList(  );
				  break;

				  //
 			case  ID_qyRealTimeTaskList:
				  bViewRealTimeImTaskList(  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_taskInfoList:
				  bViewTaskInfoList(  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_sharingObjectList:
				  bViewSharingObjectList(  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_playerList:
				  bViewPlayerList(  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_wallList:
				  bViewWallList(  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_ipCamList:
				  bViewIpCamList(  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_imNetStatList:
				  bViewImNetStatList(  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_talkerList:
				  bViewTalkerList(  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_messengerStatusList:
				  bViewMessengerStatusList(  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_qList:
				  viewStatusCli(  CONST_qyWndContentType_qList,  0,  _T(  "qList"  ),  CONST_resId_qListColumns,  NULL,  NULL    );
				  break;
				  //
			case  ID_myDbStatus:  //  2013/02/22
				  viewStatusCli(  CONST_qyLvType_myDbStatus,  0,  _T(  "MyDb status"  ),  CONST_resId_qListColumns,  NULL,  NULL  );				  
				  break;
				  //
			case  ID_imTaskList_unproced_test:
				  g_dbFuncs.pf_bViewImTaskList_unproced(   pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_imTaskList_cur_test:
				  g_dbFuncs.pf_bViewImTaskList_cur(   pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_current  ),  _T(  ""  )  );
				  break;

			//  2015/10/05
#if 0
			case  ID_notViewAudioStatus:
				  pProcInfo->cfg.debugStatusInfo.ucbViewAudioStatus  =  FALSE;
				  break;
			case  ID_viewAudioStatus:
				  pQyMc->env.bDebugInfo  =  TRUE;
				  pProcInfo->cfg.debugStatusInfo.ucbViewAudioStatus  =  TRUE;
				  break;
			case  ID_notViewVideoStatus:
				  pProcInfo->cfg.debugStatusInfo.ucbViewVideoStatus  =  FALSE;
				  break;
			case  ID_viewVideoStatus:
				  pQyMc->env.bDebugInfo  =  TRUE;
				  pProcInfo->cfg.debugStatusInfo.ucbViewVideoStatus  =  TRUE;
				  break;
			case  ID_notViewIoStatus:
				  pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus  =  FALSE;
				  break;
			case  ID_viewIoStatus:
				  pQyMc->env.bDebugInfo  =  TRUE;
				  pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus  =  TRUE;
				  break;

#endif
			case  ID_notPrintAudioMediaType:  {
				  MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbPrint_a_mt  =  FALSE;
				  }
				  break;
			case  ID_printAudioMediaType:  {
				  MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbPrint_a_mt  =  TRUE;
				  }
				  break;
#if  0
			case  ID_notShowVideoCapStatus:		{											//  2012/11/11
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
		
				  pProcInfo->cfg.debugStatusInfo.ucbShowVideoCapStatus  =  FALSE;
				  }
				  break;
			case  ID_showVideoCapStatus:		{
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
		
				  pProcInfo->cfg.debugStatusInfo.ucbShowVideoCapStatus  =  TRUE;
				  }
				  break;
			case  ID_notShowAudioCapStatus:		{
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
		
				  pProcInfo->cfg.debugStatusInfo.ucbShowAudioCapStatus  =  FALSE;
				  }
				  break;
			case  ID_showAudioCapStatus:		{
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
		
				  pProcInfo->cfg.debugStatusInfo.ucbShowAudioCapStatus  =  TRUE;
				  }
				  break;
			case  ID_notShowPreDrawStatus:  {
				  MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowPreDrawStatus  =  FALSE;
				  }
				  break;
			case  ID_showPreDrawStatus:  {
				  MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowPreDrawStatus  =  TRUE;
				  }
				  break;
			case  ID_notShowToDrawStatus:  {
				  MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowToDrawStatus  =  FALSE;
				  }
				  break;
			case  ID_showToDrawStatus:  {
				  MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowToDrawStatus  =  TRUE;
				  }
				  break;
			case  ID_notShowRenderStatus:
				  pProcInfo->cfg.debugStatusInfo.ucbShowRenderStatus  =  FALSE;				  
				  break;
			case  ID_showRenderStatus:
				  pProcInfo->cfg.debugStatusInfo.ucbShowRenderStatus  =  TRUE;
				  break;
			case  ID_notShowPlayAudioStatus:	{											//  2012/11/11
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  pProcInfo->cfg.debugStatusInfo.ucbShowPlayAudioStatus  =  FALSE;
				  }
				  break;
			case  ID_showPlayAudioStatus:{											//  2012/11/11
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  pProcInfo->cfg.debugStatusInfo.ucbShowPlayAudioStatus  =  TRUE;
				  }
				  break;

			case  ID_notShowDlgTalkStatus:	{  //  2014/05/07
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  =  FALSE;
				  }
				  break;
			case  ID_showDlgTalkStatus:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  =  TRUE;
				  }
				  break;

			case  ID_notShowPktInputInfo:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  pProcInfo->cfg.debugStatusInfo.ucbShowPktInputInfo  =  FALSE;
				  }
				  break;
			case  ID_showPktInputInfo:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowPktInputInfo  =  TRUE;				  
				  }
				  break;
			case  ID_notPrintRtt:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  pProcInfo->cfg.debugStatusInfo.ucbPrint_rtt  =  FALSE;
				  }
				  break;
			case  ID_printRtt:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  pProcInfo->cfg.debugStatusInfo.ucbPrint_rtt  =  TRUE;
				  }
				  break;
			case  ID_notShowOnvifStatus:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  pProcInfo->cfg.debugStatusInfo.ucbShow_onvif  =  FALSE;
				  }
				  break;
			case  ID_showOnvifStatus:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  pProcInfo->cfg.debugStatusInfo.ucbShow_onvif  =  TRUE;
				  }
				  break;
			case  ID_notPrintPtz:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  pProcInfo->cfg.debugStatusInfo.ucbPrint_ptz  =  FALSE;
				  }
				  break;
			case  ID_printPtz:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  pProcInfo->cfg.debugStatusInfo.ucbPrint_ptz  =  TRUE;
				  }
				  break;
			case  ID_notPrintD3d:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  pProcInfo->cfg.debugStatusInfo.ucbPrint_d3d  =  FALSE;
				  }
				  break;
			case  ID_printD3d:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  pProcInfo->cfg.debugStatusInfo.ucbPrint_d3d  =  TRUE;
				  }
				  break;
			case  ID_notShowEncVStatus:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowEncVStatus  =  FALSE;
				  }
				  break;
			case  ID_showEncVStatus:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowEncVStatus  =  TRUE;
				  }
				  break;

				  //  2016/04/13
			case  ID_notShowDec_pipeStatus:
				  pProcInfo->cfg.debugStatusInfo.ucbShowDec_pipeStatus  =  FALSE;
				  break;
			case  ID_showDec_pipeStatus:
				  pProcInfo->cfg.debugStatusInfo.ucbShowDec_pipeStatus  =  TRUE;
				  break;

				  //
			case  ID_notShowPreDecAStatus:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowPreDecAStatus  =  FALSE;
				  }
				  break;
			case  ID_showPreDecAStatus:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowPreDecAStatus  =  TRUE;
				  }
				  break;
			case  ID_notShowPreDecV_pts:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowPreDecV_pts  =  FALSE;
				  }
				  break;
			case  ID_showPreDecV_pts:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowPreDecV_pts  =  TRUE;
				  }
				  break;
			case  ID_notShowPreDecVStatus:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowPreDecVStatus  =  FALSE;
				  }
				  break;
			case  ID_showPreDecVStatus:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowPreDecVStatus  =  TRUE;
				  }
				  break;
			case  ID_notShowPostDecVStatus:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowPostDecVStatus  =  FALSE;
				  }
				  break;
			case  ID_showPostDecVStatus:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  pProcInfo->cfg.debugStatusInfo.ucbShowPostDecVStatus  =  TRUE;
				  }
				  break;
				  //
			case  ID_notShowDec_sharedTexStatus:
				  pProcInfo->cfg.debugStatusInfo.ucbShowDec_sharedTexStatus  =  FALSE;
				  break;
			case  ID_showDec_sharedTexStatus:
				  pProcInfo->cfg.debugStatusInfo.ucbShowDec_sharedTexStatus  =  TRUE;
				  break;

				  //
			case  ID_notTestGps:  {		//  2012/05/15
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  if  (  !pProcInfo->cfg.ucbTestGps  )  break;

				  //
				  exitTestGps(  );

				  pProcInfo->cfg.ucbTestGps  =  FALSE;
				  }
				  break;
			case  ID_testGps:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  if  (  pProcInfo->cfg.ucbTestGps  )  break;

				  //
				  initTestGps(  );

				  pProcInfo->cfg.ucbTestGps  =  TRUE;
				  }
				  break;
			case  ID_notTestStream:{
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  //
				  pProcInfo->cfg.debugStatusInfo.ucbShowRtspCliControl  =  FALSE;
				  }
 				  break;
			case  ID_testStream:{
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  //
				  pProcInfo->cfg.debugStatusInfo.ucbShowRtspCliControl  =  TRUE;				
				  }
 				  break;
#endif

			default:
					break;
	}

	return  0;
}


//
#include	"dlgShareDynBmps.h"


//
 //
  BOOL  bDisplayMcViewContent_ipCams(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 if  (  !pListCtrl  )  return  FALSE;
	 //  CListCtrl						*	pListCtrl				=			&pMcView->GetListCtrl();
	 int								i;
	 //  QY_OBJ_DB						*	pObj;
	 TCHAR								tBuf[256];
	 int								cnt						=			0;
	 int								index;
	 MIS_CNT						*	pMisCnt					=			getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 int								nWaitingInMs			=			0;

	traceLogA(  "bDisplayMcViewContent_ipCams not finished.................."  );

	
	myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_ipCamListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );

	 //
	 HWND					hDlg  =  pProcInfo->hWnd_shareDynBmps;		
	 CDlgShareDynBmps  *  pDlg  =  (  CDlgShareDynBmps  *  )CWnd::FromHandlePermanent(  hDlg  );
	 if  (  !pDlg  )  goto  errLabel;
	 DLG_shareDynBmps_var	*	pVar  =  &pDlg->m_var;
	 DLG_shareDynBmps_var  &  m_var  =  *pVar;
	 
	 int  j,  k, l;	
	 TCHAR  displayBuf[512];
	 		  
	 //	
	 DlgShareDynBmps_onvif  *  pF_onvif  =  &m_var.onvif;		
	 ShareDynBmps_onvif_rulesInfo  *  prulesInfo  =  &pF_onvif->rulesInfo;
	 ShareDynBmps_ipDevsInfo  *  pdevsInfo  =  &pF_onvif->ipDevsInfo;	  				   

	 //				
	 for  (  l  =  0;  l  <  min(  mycountof(  prulesInfo->mems  ),  prulesInfo->usCnt  );  l  ++  )  {

			  Onvif_rule  *  pRule  =  &prulesInfo->mems[l];
			  if  (  !pRule->usIndex_obj  )  continue;
			  					
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "f"  )  );				
			  index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		

			  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s %d: %s,%s,%s,%s:*,%s"  ),  CONST_str_rule,  (  int  )pRule->usIndex_obj,  qyGetDesByType1(  CONST_onvifRuleTypeTable,  pRule->iOnvifRuleType  ),  pRule->cusName,  CQyString(  pRule->url  ),  CQyString(  pRule->usrName  ),  CQyString(  pRule->defToken  )  );
			  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  displayBuf  );	
			  			
			  //
			  cnt  ++  ;		  
	 }

	 //
	 for  (  i  =  0;  i  <  mycountof(  pdevsInfo->mems  );  i  ++  )  {
		  IP_dev  *  pIpDev  =  &pdevsInfo->mems[i];
		  if  (  !pIpDev->iType  )  continue;


				 
		  //			
		  unsigned  char  ucCnt_urls  =  min(  pIpDev->ucCnt_urls,  mycountof(  pIpDev->urls  )  );			
		  int  k;
		  for  (  k  =  0;  k  <  ucCnt_urls;  k  ++  )  {

			  //
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "f"  )  );							
			  index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	

			  //				
			  displayBuf[0]  =  0;				
			  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s %d"  ),  CONST_str_ipCam,  (  int  )pIpDev->rule.usIndex_obj  );
			  if  (  pIpDev->usHelp_subIndex  )  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s.%d"  ),  displayBuf,  (  int  )pIpDev->usHelp_subIndex  );
			  
			  //if  (  pIpDev->subIndex  )  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s %d"  ),  displayBuf,  (  int  )pIpDev->subIndex  );
				  
				
			  //										
			  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s: %s %s"  ),  displayBuf,  CQyString(  pIpDev->urls[k].token  ),  CQyString(  pIpDev->urls[k].rtspUrl.url  )  );			 
			  
			  //				
			  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  displayBuf  );	
				
			  //
			  cnt  ++  ;
		  }


	 }

	 //
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "f"  )  );							
	 index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	

	 //
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "ts.rule %u, ts.dev %u"  ),  prulesInfo->ts_rulesInfo.dwModifiedTickCnt,  pdevsInfo->ts_ipDevsInfo.dwModifiedTickCnt  );
			  //				
			  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );	
				
			  //
			  cnt  ++  ;



	 ///////////////////////////////
	 ShareDynBmpsThread_onvif  *  pB_onvif  =  &m_var.shareDynBmpsThreadInfo.onvif;
	 prulesInfo  =  &pB_onvif->rulesInfo;
	 pdevsInfo  =  &pB_onvif->ipDevsInfo;	  				   

	 //				
	 for  (  l  =  0;  l  <  min(  mycountof(  prulesInfo->mems  ),  prulesInfo->usCnt  );  l  ++  )  {

			  Onvif_rule  *  pRule  =  &prulesInfo->mems[l];
			  if  (  !pRule->usIndex_obj  )  continue;
			  					
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "b"  )  );				
			  index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		

			  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s %d: %s,%s,%s,%s:*,%s"  ),  CONST_str_rule,  (  int  )pRule->usIndex_obj,  qyGetDesByType1(  CONST_onvifRuleTypeTable,  pRule->iOnvifRuleType  ),  pRule->cusName,  CQyString(  pRule->url  ),  CQyString(  pRule->usrName  ),  CQyString(  pRule->defToken  )  );
			  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  displayBuf  );	
			  			
			  //
			  cnt  ++  ;		  
	 }

	 //
	 for  (  i  =  0;  i  <  mycountof(  pdevsInfo->mems  );  i  ++  )  {
		  IP_dev  *  pIpDev  =  &pdevsInfo->mems[i];
		  if  (  !pIpDev->iType  )  continue;


				 
		  //			
		  unsigned  char  ucCnt_urls  =  min(  pIpDev->ucCnt_urls,  mycountof(  pIpDev->urls  )  );			
		  int  k;
		  for  (  k  =  0;  k  <  ucCnt_urls;  k  ++  )  {

			  //
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "b"  )  );							
			  index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	

			  //				
			  displayBuf[0]  =  0;				
			  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s %d"  ),  CONST_str_ipCam,  (  int  )pIpDev->rule.usIndex_obj  );
			  if  (  pIpDev->usHelp_subIndex  )  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s.%d"  ),  displayBuf,  (  int  )pIpDev->usHelp_subIndex  );
			  
			  //if  (  pIpDev->subIndex  )  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s %d"  ),  displayBuf,  (  int  )pIpDev->subIndex  );
				  
				
			  //										
			  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s: %s %s"  ),  displayBuf,  CQyString(  pIpDev->urls[k].token  ),  CQyString(  pIpDev->urls[k].rtspUrl.url  )  );			 
			  
			  //				
			  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  displayBuf  );	
				
			  //
			  cnt  ++  ;
		  }


	 }

	 //
	 	 //
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "b"  )  );							
	 index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	

	 //
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "ts.rule %u, ts.dev %u"  ),  prulesInfo->ts_rulesInfo.dwModifiedTickCnt,  pdevsInfo->ts_ipDevsInfo.dwModifiedTickCnt  );
			  //				
			  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );	
				
			  //
			  cnt  ++  ;

			   


	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


__declspec(  dllexport  )    BOOL  bViewIpCamList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewIpCamList enters."  );

	traceLogA(  "bViewIpCamList not finished.................."  );

	viewStatusCli(  CONST_qyLvType_ipCamList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ipCamList  ),  CONST_resId_ipCamListColumns,  (  PF_commonHandler  )bDisplayMcViewContent_ipCams,  NULL  );

	traceLogA(  "bViewIpCamList leaves."  );

	return  bRet;
}

