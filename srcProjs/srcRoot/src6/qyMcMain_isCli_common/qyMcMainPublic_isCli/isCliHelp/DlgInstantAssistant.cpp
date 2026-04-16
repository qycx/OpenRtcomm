// DlgInstantAssistant.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
#include	"dlgTalkProc.h"
#include	"WallTalkers.h"
#include	"myresource.h"
#include	"DlgInstantAssistant.h"
#include	"qyCusResTemp.h"
#include	"qmcVideoCapture_isCli.h"

#include	"qyAvRecordPublic.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"isclid3dpublic.h"
#include	"qmShellPublic.h"

#include	"smCommProc.h"


//
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
int  dlgInstantAssistant_OnCmd(  HWND  hDlg,  DLG_instantAssistant_var  &  m_var,  WORD  wID  );
 

//  #include	"DlgImObjRule.h"

//  BOOL  LoadBitmapFromBMPFile( LPTSTR szFileName, HBITMAP *phBitmap, HPALETTE *phPalette );

//  #define		CONST_bmp_normal		_T(  "instantAssistantNormal.bmp"  )
//  #define		CONST_bmp_manager		_T(  "instantAssistantManager.bmp"  )

static  DWORD  sdwTickCnt_close_instantAssistant	=	0;


  HWND  findWndAbove(  HWND  hParent  )
{
	return  NULL;
}



 //  2012/04/03
 int  getIDD_instantAssistant(  HWND  hParent,  int  iWndContentType_hParent,  HWND  hCurTalk,  int  *  piStatus_instantAssistant,  BOOL  *  pbMin  )
{
	int					iIDD			=	-1;
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	QY_MC  *  pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;

	CHelp_getDlgTalkVar	help_getCurTalkVar;
	DLG_TALK_var	*	pCurTalkVar		=  (  DLG_TALK_var	*	)help_getCurTalkVar.getVar(  hCurTalk,  _T(  "getIDD_instantAssistant"  )  );
	if  (  !pCurTalkVar  )  return  -1;
	int					iStatus			=	0;
	BOOL				bMin			=	FALSE;

	//
	DLG_TALK_var  *  pMgrVar  =  pCurTalkVar;
	if  (  !isTalkerShadowMgr(  pCurTalkVar->addr  )  )  {
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pCurTalkVar->pShadowInfo;
		if  (  !pShadow  )  goto  errLabel;
		pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pShadow->hMgr,  _T(  "getIDD_instantAssistant,hMgr"  )  );
		if  (  !pMgrVar  )  goto  errLabel;
	}

	//
	int  iZoneObjsType  =  0;
	//
	ZONE_objs  *  pZoneObjs  =  (  ZONE_objs  *  )pFuncs->pf_getZoneObjs(  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall,  iZoneObjsType  );
	ZONE_objs_info	*	pDlgWallsVar	=	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall,  iZoneObjsType  );
	if  (  pZoneObjs  &&  pDlgWallsVar  )  {
		bMin  =  TRUE;
		if  (  isZoneObjIndexValid(  pZoneObjs->iIndex_enlarged1  )  )  {
			ZONE_obj  *  pZoneObj  =  &pZoneObjs->mems[pZoneObjs->iIndex_enlarged1];
			ZONE_obj_info	*	pMem  =  &pDlgWallsVar->mems[pZoneObjs->iIndex_enlarged1];
			if  (  pZoneObj->hWndWallMem  ==  hCurTalk  )  bMin  =  FALSE;
		}
	}

	//  2015/06/07
	if  (  bApp_ts_3d(  pQyMc  )  )  {
		bMin  =  FALSE;
	}


	
	//		
	if  (  bApp_ts(  pQyMc  )  )  {  //  #ifdef  __APP_qyMc_touchscreen__
			  
			  if  (  !pMgrVar->av.taskInfo.bTaskExists  )  {			
				  BOOL	bWait  =  bDlgTalkWaitToAccept(  hCurTalk  );

				  {			
					  if  (  !bWait  )  {		
						  iIDD  =  //bMin  ?  IDD_instantAssistant_start_min  :  
							  IDD_instantAssistant_start;	
						  if  (  pCurTalkVar->guiData.ucbShowMore  )  {
							  if  (  pCurTalkVar->addr.uiObjType  ==  CONST_objType_imGrp  )  iIDD  =  IDD_instantAssistant_start_grp_more;
							  else  iIDD  =  IDD_instantAssistant_start_more;
						  }
						  }
					  else  {
						    iIDD  =  //bMin  ?  IDD_instantAssistant_start_wait_min  :  
								IDD_instantAssistant_start_wait;									
					  }				
				  }			
				  }	
			  else  {
				    iIDD  =  //bMin  ?  IDD_instantAssistant_av_min  :  
						IDD_instantAssistant_av;
					if  (  pCurTalkVar->guiData.ucbShowMore  )  {					
						if  (  pCurTalkVar->addr.uiObjType  ==  CONST_objType_imGrp  )  iIDD  =  IDD_instantAssistant_av_grp_more;							  
						else  iIDD  =  IDD_instantAssistant_av_more;
					}
			  }	

			  if  (  pMgrVar->guiData.usGrpSubtype  ==  CONST_imGrpSubtype_msg  ){
				  iIDD  =  //bMin  ?  IDD_instantAssistant_msg_min  :  
					  IDD_instantAssistant_msg;
			  }
			  }		  
	else  //  #else			  
	{
#if  0
			  iIDD  =  IDD_instantAssistant;
			  if  (  pCurTalkVar->ucbOnGlobalVWall  )  iIDD  =  IDD_instantAssistant_vw;
			  //
			  if  (  !pMgrVar->av.taskInfo.bTaskExists  )  {		
				  BOOL	bWait  =  bDlgTalkWaitToAccept(  hCurTalk  );

				  {	
					  if  (  !bWait  )  {					
					
						  iStatus  =  CONST_iaStatus_start;					
						  }
					  else  {

						    iStatus  =  CONST_iaStatus_start_wait;				
					  }				
				  }			
			  }	
			  else  {
				    iStatus  =  CONST_iaStatus_av;		
			  }
			  //
			  if  ( pMgrVar->guiData.usGrpSubtype  ==  CONST_imGrpSubtype_msg  )  {
				  iStatus  =  CONST_iaStatus_msg;
			  }
#endif
		  
	}	//  #endif
	
	

errLabel:

	if  (  iIDD  >  0  )  {
		if  (  piStatus_instantAssistant  )  *piStatus_instantAssistant  =  iStatus;
		if  (  pbMin  )  *pbMin  =  bMin;
	}

	return iIDD;
}



 //  2012/05/03
 __declspec(  dllexport  )  int  viewInstantAssistant(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hCurTalk,  BOOL  bNoDelayToView  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int								iErr					=	-1;
	QY_MC					*		pQyMc					=	QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	//int								iServiceId				=	CONST_qyServiceId_mis;

	//
	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var			*		pCurVar					=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hCurTalk,  _T(  "viewIa"  )  );
	if  (  !pCurVar  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "viewInstantAssistant failed: getDlgTalkVar returns NULL"  )  );
		#endif
		return  -1;
	}

	//
#if  0
	if  (  pCurVar->syncFlgs.bInSequence  )  
	{
		#ifdef  __DEBUG__
				traceLog(  _T(  "viewInstantAssistant failed, syncFlg locked"  )  );
		#endif
		return  -1;
	}
#endif

	//
	//
	HWND  hMgr  =  hCurTalk;
	DLG_TALK_var		*	pMgrVar  =  pCurVar;
	//
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		//
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pCurVar->pShadowInfo;
		if  (  !pShadow  )  return  -1;
		//
		hMgr  =  pShadow->hMgr;
		pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pShadow->hMgr,  _T(  "viewIa: hMgr"  )  );
		if  (  !pMgrVar  )  return  -1;
	}

	//
	DLG_TALK_var			&		m_var					=	*pCurVar;

	//  2012/05/03. hParent不一定等于hWndEvent. 可以用hWndEvent和iWndContent来判断应该设置hParent是哪个
	HWND							hParent					=	hWndEvent;
	int								iWndContentType_hParent	=	iWndContentType;	

	//
	CDlgInstantAssistant	*		pDlg					=	NULL;
	int								iIDD					=	-1;
	int								iStatus_ia				=	0;
	BOOL							bMin					=	FALSE;

	//  traceLogA(  "viewInstantAssistant enters"  );

#ifdef  __DEBUG__
		int  i  =  sizeof(  CDlgInstantAssistant  );
		//  traceLog(  _T(  "viewIa, xPos %d, yPos %d"  ),  xPos,  yPos  );
#endif

	//
#if  0  //  2017/10/03
	//  2017/08/27
	if  (  pMgrVar->av.taskInfo.bTaskExists
		&&  pMgrVar->av.taskInfo.usConfType  ==  CONST_usConfType_consult
		&&  !pMgrVar->av.taskInfo.ucbStarter  )
	{
		#ifdef  __DEBUG__
				traceLog(  _T(  "viewIa failed, no instantantAssistant for member in consult"  )  );
		#endif
		return  -1;
	}
#endif


	//
	if  (  pProcInfo->status.param_viewInstantAssistant.hParent_ia  !=  hParent  )  {
		SendMessage(  m_var.hWnd_instantAssistant,  WM_CLOSE,  0,  0  );
		if  (  IsWindow(  m_var.hWnd_instantAssistant  )  )  goto  errLabel;
	}


	if  (  !bNoDelayToView  )  {	
		if  (  xPos_screen  ==  pProcInfo->status.param_viewInstantAssistant.xPos_screen  &&  yPos_screen  ==  pProcInfo->status.param_viewInstantAssistant.yPos_screen  )  {
			#ifdef  __DEBUG__
			if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
				traceLog(_T("viewInstantAssistant: mouse pos (%d,%d) has not changed, skipped"), xPos_screen, yPos_screen);
			}
			#endif
			iErr  =  0;  goto  errLabel;
		}
		//  2011/03/26. 这里的防delay似乎没意义，原来是担心在窗口关闭后，又莫名其妙的被触发了一个mousemove事件，现在看来，是xPos_screen, yPos_screen没有过滤造成的。
		//  
	}


	pProcInfo->status.param_viewInstantAssistant.xPos_screen  =  xPos_screen;
	pProcInfo->status.param_viewInstantAssistant.yPos_screen  =  yPos_screen;
	pProcInfo->status.param_viewInstantAssistant.hParent_ia  =  hParent;			//  2012/05/03


	if  (  bApp_ts(  pQyMc  )  )  {	//  #ifdef  __APP_qyMc_touchscreen__
		//
		if  (  pQyMc->gui.hWnd_menu  )  {					//  2011/03/27
			if  (  IsWindow(  pQyMc->gui.hWnd_menu  )  )  goto  errLabel;
			pQyMc->gui.hWnd_menu  =  NULL;
		}
		if  (  pQyMc->gui.hWnd_modal  )  {					//  2011/07/12
			if  (  IsWindow(  pQyMc->gui.hWnd_modal  )  )  goto  errLabel;
			pQyMc->gui.hWnd_modal  =  NULL;
		}
		//
		if  (  !bApp_ts_3d(  pQyMc  )  )  {  //2015/06/06
			pFuncs->pf_viewWallsBar_ts(  hWndEvent,  iWndContentType,  xPos_screen,  yPos_screen,  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall,  bNoDelayToView  );
		}
		//
		}
	else  {	//  #ifdef  __APP_qyMc__	//  2012/04/06
		//  if  (  m_var.ucbOnGlobalVWall  )  
		if  (  pCurVar->ucbOnGlobalVWall  )
		{		
			viewWallsBar(  hWndEvent,  iWndContentType,  xPos_screen,  yPos_screen,  pProcInfo->g_hVWall,  pFuncs->pf_getZoneObjsInfo(  pProcInfo,  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall,  0  ),  bNoDelayToView  );
		}
	}	//  #endif

		//  2012/05/03. 对gps墙上的talker,暂时不增加菜单
		if  (  pCurVar->iTalkerSubType  ==  CONST_talkerSubtype_onVWall  )  goto  errLabel;

		//
		iIDD  =  getIDD_instantAssistant(  hParent,  iWndContentType_hParent,  hCurTalk,  &iStatus_ia,  &bMin  );
		if  (  iIDD  <  0  )  {
			goto  errLabel;
		}


	if  (  IsWindow(  m_var.hWnd_instantAssistant  )  )  {
#ifdef  __SUPPORT_dlgInstantAssistant_mfc__
		pDlg	=	(  CDlgInstantAssistant  *  )CWnd::FromHandle(  m_var.hWnd_instantAssistant  );
		pDlg->m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );
		pDlg  =  NULL;
		if  (  IsIconic(  m_var.hWnd_instantAssistant  )  )  SendMessage(  m_var.hWnd_instantAssistant,  WM_SYSCOMMAND,  SC_RESTORE,  0  );
		//  if  (  !IsWindowVisible(  m_var.hWnd_instantAssistant  )  )  ShowWindow(  m_var.hWnd_instantAssistant,  SW_SHOW  );		
#else
		pDlg	=	(  CDlgInstantAssistant  *  )CQyWnd::FromHandle(  m_var.hWnd_instantAssistant  );
		pDlg->m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );
		pDlg  =  NULL;
		if  (  IsIconic(  m_var.hWnd_instantAssistant  )  )  SendMessage(  m_var.hWnd_instantAssistant,  WM_SYSCOMMAND,  SC_RESTORE,  0  );
#endif
		iErr  =  0;  goto  errLabel;
	}

	m_var.hWnd_instantAssistant  =  NULL;

	//  2011/03/04. 这是为了只有一个功能窗口
	if  (  IsWindow(  pQyMc->gui.hWnd_popupTool  )  )  {	
		SendMessage(  pQyMc->gui.hWnd_popupTool,  WM_CLOSE,  0,  0  );
	}
	//  2013/02/17
	if  (  IsWindow(  pQyMc->gui.hWnd_popupTool  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "viewInstantAssistant failed, hPopupTool exists."  )  );
		goto  errLabel;
	}

	//  2011/03/23
#if  1  //  def  __APP_qyMc_touchscreen__
	if  (  !bApp_ts_3d(  pQyMc  )  )  {
		selectWall(  hCurTalk  );
	}
#endif


//
#ifdef  __SUPPORT_dlgInstantAssistant_mfc__

		 //  2010/12/18
		 HWND	hFore	=	GetForegroundWindow(  );
		 HWND	hAbove  =	findWndAbove(  hParent  );

		 //
		 RECT							rect;

		 pDlg  =  new  CDlgInstantAssistant(  hParent  );
		 if  (  !pDlg  )  goto  errLabel;

		 //  2013/07/16
		 pDlg->m_var.guiData.param.iWndContentType_hParent  =  iWndContentType_hParent;
		 //
		 pDlg->m_var.guiData.param.hMgrTalk  =  hMgr;
		 //  if  (  !isTalkerShadowMgr(  pCurTalkerVar->addr  )  )  pDlg->m_var.guiData.param.hShadow  =  hCurTalker;			//  2012/05/04
		 pDlg->m_var.guiData.param.hCurTalk  =  hCurTalk;
		 //
		 pDlg->m_var.guiData.param.iIDD  =  iIDD;
		 pDlg->m_var.guiData.param.iStatus  =  iStatus_ia;		//  2012/04/04
		 pDlg->m_var.guiData.param.bMin  =  bMin;
		 //
		 pDlg->m_var.guiData.param.xPos_screen  =  xPos_screen;
		 pDlg->m_var.guiData.param.yPos_screen  =  yPos_screen;

		 pDlg->m_var.guiData.iIDC_request  =  IDC_request;
		 pDlg->m_var.guiData.iIDC_BUTTON_joinInBgWall  =  IDC_BUTTON_joinInBgWall;			//  2016/03/26
		 pDlg->m_var.guiData.iIDC_talkerList  =  IDC_talkerList;
		 pDlg->m_var.guiData.iIDC_BUTTON_msgBox  =  IDC_BUTTON_msgBox;
		 pDlg->m_var.guiData.iIDC_BUTTON_offlineRes  =  IDC_BUTTON_offlineRes;				//  2015/07/31
		 //  pDlg->m_var.guiData.iIDC_COMBO_usLayoutType  =  IDC_COMBO_usLayoutType;
		 pDlg->m_var.guiData.iIDC_BUTTON_layoutType  =  IDC_BUTTON_layoutType;
		 pDlg->m_var.guiData.iIDC_STATIC_status  =  IDC_STATIC_status;
		 pDlg->m_var.guiData.iIDC_BUTTON_av  =  IDC_BUTTON_av;
		 pDlg->m_var.guiData.iIDC_BUTTON_shareScreen  =  IDC_BUTTON_shareScreen;
		 pDlg->m_var.guiData.iIDC_BUTTON_rule  =  IDC_BUTTON_rule;
		 pDlg->m_var.guiData.iIDC_BUTTON_close  =  IDC_BUTTON_close;
		 pDlg->m_var.guiData.iIDC_BUTTON_av_accept  =  IDC_BUTTON_av_accept;
		 pDlg->m_var.guiData.iIDC_BUTTON_av_deny  =  IDC_BUTTON_av_deny;
		 pDlg->m_var.guiData.iIDC_BUTTON_more  =  IDC_BUTTON_more;

#ifndef  __APP_qyMc_touchscreen__	//  2011/10/04
		 pDlg->m_var.guiData.iIDC_BUTTON_fullScreen  =  IDC_BUTTON_fullScreen;
		 pDlg->m_var.guiData.iIDC_BUTTON_showDlgMenu  =  IDC_BUTTON_showDlgMenu;			//  2012/04/09
#endif
		 pDlg->m_var.guiData.iIDC_BUTTON_selAvCompressor  =  IDC_BUTTON_selAvCompressor;	//  2014/04/08
		 pDlg->m_var.guiData.iIDC_BUTTON_subtitles  =  IDC_BUTTON_subtitles;				//  2013/04/04
		 pDlg->m_var.guiData.iIDC_BUTTON_remoteVideo  =  IDC_BUTTON_remoteVideo;			//  2013/02/12
		 pDlg->m_var.guiData.iIDC_BUTTON_ptzPanel  =  IDC_BUTTON_ptzPanel;					//  2013/02/15
		 //
		 pDlg->m_var.guiData.iIDC_BUTTON_shareMediaFile  =  IDC_BUTTON_shareMediaFile;
		 pDlg->m_var.guiData.iIDC_BUTTON_closeAndClean  =  IDC_BUTTON_closeAndClean;
		 //
		 //
		 //pDlg->m_var.guiData.iIDC_CHECK_autoHide  =  IDC_CHECK_autoHide;			//  2015/07/30
		 //
		 //
		 pDlg->m_var.guiData.iIDC_BUTTON_sendFile  =  IDC_BUTTON_sendFile;			//  2015/06/14
		 pDlg->m_var.guiData.iIDC_BUTTON_menuBar  =  IDC_BUTTON_menuBar;			//  2015/06/07		
		 

		 //  pDlg->m_var.guiData.iIDC_STATIC_peace  =  IDC_STATIC_peace;		//  peace

		 //  pDlg->m_var.guiData.

		 if  (  !pDlg->Create(  rect  )  )  {			 
			 goto  errLabel;
		 }

		 //	ShowWindow(  pDlg->m_hWnd,  SW_SHOW  );
		 // 
		 if  (  bApp_ts(  pQyMc  )  )  {  //  #ifdef  __APP_qyMc_touchscreen__
			 if  (  !pCurVar->guiData.ucbShowMore  )  {
				 //  traceLog(  _T(  "before AnimateWindow"  )  );
				 DWORD  dwTimeInMs  =  300;
				 DWORD	dwFlags  =  AW_SLIDE  |  AW_VER_NEGATIVE;
				 if  (  !AnimateWindow(  pDlg->m_hWnd,  dwTimeInMs,  dwFlags  )  )  {		
					 traceLog(  _T(  "AnimateWindow failed"  )  );
				 }
				 //  traceLog(  _T(  "after AnimateWindow"  )  );
			 }
		 }	//  #endif
			
		 int  flg  =  SWP_NOMOVE  |  SWP_NOSIZE  |  SWP_NOACTIVATE  |  SWP_SHOWWINDOW;
		 SetWindowPos(  pDlg->m_hWnd,  hAbove,  0,  0,  0,  0,  flg  );
		 //
		 if  (  !bApp_ts(  pQyMc  )  )  {  //  #ifndef  __APP_qyMc_touchscreen__
				  if  (  IsWindow(  hFore  )  )  SetForegroundWindow(  hFore  );
		 }	//  #endif

#else

	 //  2010/12/18
	 HWND	hFore	=	GetForegroundWindow(  );
	 HWND	hAbove  =	findWndAbove(  hParent  );

	 G_guiData_qyMc			*	pGuiData							=	(  G_guiData_qyMc  *  )get_g_guiData(  );
	 PF_commonHandler			pf_newDlgInstantAssistant			=	(  PF_commonHandler  )pGuiData->pf_newDlgInstantAssistant;
	 if  (  !pf_newDlgInstantAssistant  )  goto  errLabel;
	 
	 DLG_guiDataParam_instantAssistant			guiDataParam;
	 memset(  &guiDataParam,  0,  sizeof(  guiDataParam  )  );
	 guiDataParam.hDlgTalk  =  hDlgTalk;
	 guiDataParam.iIDD  =  iIDD;

	 //  hParent	=	pQyMc->gui.hMainWnd;	//  GetDesktopWindow(  );

	 pDlg  =  (  CDlgInstantAssistant  *  )pf_newDlgInstantAssistant(  pQyMc->g_hInst,  hParent,  &guiDataParam  );
	 if  (  !pDlg  )  goto  errLabel;

	 //  ShowWindow(  pDlg->m_hWnd,  SW_SHOW  );
	 //  
			
#ifndef  __WINCE__
	 int  flg  =  SWP_NOMOVE  |  SWP_NOSIZE  |  SWP_NOACTIVATE  |  SWP_SHOWWINDOW;
	 SetWindowPos(  pDlg->m_hWnd,  hAbove,  0,  0,  0,  0,  flg  );
	 
	 //
	 #ifndef  __APP_qyMc_touchscreen__
			  if  (  IsWindow(  hFore  )  )  SetForegroundWindow(  hFore  );
	 #endif
#endif

	//
#endif

	 //
	 pDlg->m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );

	//  
	m_var.hWnd_instantAssistant  =  pDlg->m_hWnd;
	pQyMc->gui.hWnd_popupTool  =  pDlg->m_hWnd;										//  2011/03/04
	if  (  !isTalkerShadowMgr(  pCurVar->addr  )  )  pCurVar->hWnd_instantAssistant  =  pDlg->m_hWnd;		//  2012/05/03

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
#ifdef  __SUPPORT_dlgInstantAssistant_mfc__
		if  (  pDlg  )  delete  pDlg;
#else
		if  (  pDlg  )  freeQyWnd(  pDlg  );
#endif
	}
	if  (  !iErr  )  {
	}

	//  traceLogA(  "viewInstantAssistant leaves, iErr is %d",  iErr  );

	return  iErr;
}





  __declspec(  dllexport  )  int  closeInstantAssistant(  HWND  hDlgTalk  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var			*		pVar					=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pVar  )  return  -1;
	DLG_TALK_var			&		m_var					=	*pVar;

#ifdef  __DEBUG__
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
		traceLog(_T("closeInstantAssistant called"));
	}
#endif

	 if  (  m_var.hWnd_instantAssistant  )  {
 		 if  (  IsWindow(  m_var.hWnd_instantAssistant  )  )  {
		 	 ::SendMessage(  m_var.hWnd_instantAssistant,  WM_CLOSE,  0,  0  );
			 }
		 else  {
			   OutputDebugString(  _T(  "closeInstantAssistant, kk\n"  )  );
		 }
		 if  (  !IsWindow(  m_var.hWnd_instantAssistant  )  )  {
			 m_var.hWnd_instantAssistant  =  NULL;
		 }

		 //
	 }

	 return  0;
}



  __declspec(  dllexport  )  int  closeMoreIa(  HWND  hDlgTalk  )
{
	CHelp_getDlgTalkVar  help_getDlgTalkVar;
	DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pCurVar  )  return  -1;

	
	if  (  pCurVar->guiData.ucbShowMore  )  {	
		pCurVar->guiData.ucbShowMore  =  false;		
		PostMessage(  pCurVar->hWnd_instantAssistant,  WM_CLOSE,  0,  0  );	
	}

	return  0;
}



  //  int  sizeAllControls_dlgInstantAssistant(  CDlgInstantAssistant  *  pDlg  )
 int  sizeAllControls_dlgInstantAssistant(  HWND  hDlgIa  )
 {

	 int			iErr							=	-1;

	 if  (  !IsWindow(  hDlgIa  )  )  return  -1;
	 CDlgInstantAssistant	*	pDlgIa				=	(  CDlgInstantAssistant  *  )CWnd::FromHandle(  hDlgIa  );
	 if  (  !pDlgIa  )  return  -1;

	 CHelp_getDlgTalkVar	help_getCurTalkVar;
	 DLG_TALK_var	*	pCurTalkVar  =  (  DLG_TALK_var	*	)help_getCurTalkVar.getVar(  pDlgIa->m_var.guiData.param.hCurTalk  );
	 if  (  !pCurTalkVar  )  return  -1;

	 //  if  (  m_var.guiData.param.iIDD  !=  IDD_instantAssistant  )  
	 {

		 PF_commonHandler	pf		=	NULL;
		 pf  =  (  PF_commonHandler  )pCurTalkVar->guiData.pf_refreshDlg_talk_ce;
		 if  (  pf  )  pf(  pDlgIa->m_var.guiData.param.hCurTalk,  &pCurTalkVar->guiData,  hDlgIa  );
		 
	 }


	 iErr  =  0;
//  errLabel:
	 return  iErr;

}

#ifdef  __SUPPORT_dlgInstantAssistant_mfc__



// CDlgInstantAssistant dialog

IMPLEMENT_DYNAMIC(CDlgInstantAssistant, CDialog)

CDlgInstantAssistant::CDlgInstantAssistant(  HWND  hParent /*=NULL*/)
	: CDialog(CDlgInstantAssistant::IDD, CWnd::FromHandle(  hParent  )  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.guiData.param.iIDD  =  CDlgInstantAssistant::IDD;
	m_var.guiData.hParent  =  hParent;

}

CDlgInstantAssistant::~CDlgInstantAssistant()
{
	//  2013/07/04
	if  (  m_var.pm_LargeImageList  )  {
		myImageList_free(  m_var.pm_LargeImageList  );
		m_var.pm_LargeImageList  =  NULL;
	}
	if  (  m_var.pm_SmallImageList  )  {
		myImageList_free(  m_var.pm_SmallImageList  );
		m_var.pm_SmallImageList  =  NULL;
	}

}

 BOOL CDlgInstantAssistant::Create(const RECT& rect) 
{
	BOOL	bRet	=	FALSE;

	if  (  !CDialog::Create(  this->m_var.guiData.param.iIDD,  CWnd::FromHandle(  m_var.guiData.hParent  )  )  )  goto  errLabel;

	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;

errLabel:

	return  bRet;
}

 BOOL  CDlgInstantAssistant::bQuitDlg(  )
{
#ifdef  __DEBUG__
		//  traceLogA(  "CDlgInstantAssistant(  )::bQuitDlg enters"  );
#endif

	//  2013/02/17
	M_syncFlg_bQuitDlg_start(  &m_var.syncFlgs.bInSequence,  m_hWnd,  _T(  "CDlgInstantAssistant::bQuitDlg failed, bLocked already."  )  );

#if  0
	{
		CQySyncFlg  syncFlg;
		if  (  syncFlg.sync(  &m_var.syncFlgs.bInSequence  )  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgInstantAssistant::bQuitDlg failed, subWnd exists."  )  );
			goto  errLabel;
		}
	}
#endif


	//
	DestroyWindow(  );


errLabel:

	//
#ifdef  __DEBUG__
		//  traceLogA(  "CDlgInstantAssistant(  )::bQuitDlg leaves"  );
#endif

	//
	M_syncFlg_bQuitDlg_end

	return  TRUE;
}


 //
 //
 int  CDlgInstantAssistant::fillTalkerList(  )
{
	int								iErr				=	-1;
	QY_MC						*	pQyMc				=	QY_GET_GBUF(  );
	CHelp_getDlgTalkVar				help_getDlgTalkVar;
	DLG_TALK_var				*	pMgrVar			=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  m_var.guiData.param.hMgrTalk,  _T(  "dlgIa::fillTalkerList"  )  );
	if  (  !pMgrVar  )  return  -1;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  -1;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	//
	MC_VAR_isCli				*	pProcInfo			=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )pDlgTalkVar->pMisCnt->pProcInfoParam;
	int								i;
	TCHAR							tBuf[128];
	int								nItems				=	0;
	int								index;
	int								nImage;
	
	//
	if  (  !pMgrVar->av.taskInfo.bTaskExists  )  return  -1;
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pMgrVar->av.taskInfo.iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	DLG_TALK_videoConference	*	pVc					=	&pTc->videoConference;
	QY_SHARED_OBJ				*	pSharedObj;

	//
	if  (  !(  pSharedObj  =	getSharedObjByIndex(  pProcInfo,  pMgrVar->av.iIndex_sharedObj_localAv  )  )  )  goto  errLabel;

	m_var.canSpeak  =  dlgTalk_canSpeak(  m_var.guiData.param.hMgrTalk  );
	if  (  m_var.canSpeak  )  SetDlgItemText(  IDC_request,  getResStr(  0,  &pQyMc->cusRes,  ID_stopSpeaking  )  );
	else  {
		  safeTcsnCpy(  getResStr(  0,  &pQyMc->cusRes,  ID_requestToSpeak  ),  tBuf,  mycountof(  tBuf  )  );
		  //
		  if  (  pMgrVar->av.taskInfo.bTaskExists
			  &&  pMgrVar->addr.uiObjType  ==  CONST_objType_imGrp
			  &&  pMgrVar->av.taskInfo.ucbConfCtrl
			  &&  !pMgrVar->av.taskInfo.ucbStarter
			  &&  !pShadowMgr->av.ucbMeConfMgr
			  )
		  {
			  if  (  !pMgrVar->av.taskInfo.confMem_confCtrl.ucbPermitToSpeak  )  {
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotSpeak  )  );
			  }
		  }
		  //
		  SetDlgItemText(  IDC_request,  tBuf  );
	}

	//
	fillTalkerList_func(  m_var.guiData.param.hMgrTalk,  m_hWnd,  &m_var.videoConferenceStatus,  m_var.idcList  );


	//  2014/12/11
	//refreshBtn_micOff(  );


	iErr  =  0;

errLabel:
	return  iErr;
}


//
__declspec(  dllexport  )  int  fillTalkerList_func(  HWND  hCurTalk,  HWND  hTool,  void  *  pVIDEO_CONFERENCE_STATUS,  int  idcList  )
{
	int								iErr				=	-1;
	QY_MC						*	pQyMc				=	QY_GET_GBUF(  );
	CHelp_getDlgTalkVar				help_getDlgTalkVar;
	DLG_TALK_var				*	pCurVar			=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hCurTalk,  _T(  "dlgIa::fillTalkerList"  )  );
	if  (  !pCurVar  )  return  -1;
	MC_VAR_isCli				*	pProcInfo			=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )pDlgTalkVar->pMisCnt->pProcInfoParam;
	int								i;
	TCHAR							tBuf[128];
	int								nItems				=	0;
	int								index;
	int								nImage;
	QY_SHARED_OBJ				*	pSharedObj;
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;

	//
	HWND  hMgr  =  hCurTalk;
	DLG_TALK_var  *  pMgrVar  =   pCurVar ;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pCurVar->pShadowInfo;
		if  (  !pShadow  )  return  -1;
		hMgr  =  pShadow->hMgr;
		pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		if  (  !pMgrVar  )  return  -1;	
	}

	//
	if  (  !pMgrVar->av.taskInfo.bTaskExists  )  return  -1;
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pMgrVar->av.taskInfo.iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
	DLG_TALK_videoConference	*	pVc					=	&pTc->videoConference;


	//
	CWnd  *  pTool  =  CWnd::FromHandlePermanent(  hTool  );
	if  (  !pTool  )  return  -1;

	//
	CONF_KEY  &  videoConferenceStatus  =  *(  CONF_KEY  *  )pVIDEO_CONFERENCE_STATUS;

	//
	if  (  !(  pSharedObj  =	getSharedObjByIndex(  pProcInfo,  pMgrVar->av.iIndex_sharedObj_localAv  )  )  )  goto  errLabel;

	//
	//
	if  (  mycountof(  videoConferenceStatus.mems  )  !=  mycountof(  pVc->activeMems_from  )  )  goto  errLabel;

	//
	CListCtrl					*	pListCtrl			=	(  CListCtrl  *  )pTool->GetDlgItem(  idcList  );
	if  (  !pListCtrl  )  goto  errLabel;

	//
	LVITEM				lvItem;

	memset(  &lvItem,  0,  sizeof(  lvItem  )  );
	lvItem.mask  =  LVIF_TEXT  |  LVIF_IMAGE  |  LVIF_STATE;
	lvItem.iItem  =  nItems;
	lvItem.pszText  =  tBuf;
	lvItem.cchTextMax  =  mycountof(  tBuf  );
	
	BOOL				bMe;

	for  (  i  =  0;  i  <  mycountof(  pVc->activeMems_from  );  i  ++  )  {
		 if  (  !pVc->activeMems_from[i].avStream.idInfo.ui64Id  )  continue;

		 //
		 bMe  =  (  pVc->activeMems_from[i].avStream.idInfo.ui64Id  ==  pMgrVar->pMisCnt->idInfo.ui64Id
				&&  pVc->activeMems_from[i].avStream.obj.resObj.uiObjType  ==  0  );

		 //  
		 nImage  =  pQyMc->cfg.image.nImage_activeMem;
		 if  (  bMe  )  {
			 if  (  !dlgTalk_canSpeak(  hMgr  )  
				 ||  !dlgTalk_bRecorderOk(  hMgr  )  )				 
			 {
				 nImage  =  pQyMc->cfg.image.nImage_interruptedSpeakingMem;
			 }
		 }
		 
		 //
		 if  (  pVc->activeMems_from[i].avStream.idInfo.ui64Id  ==  videoConferenceStatus.mems[nItems].avStream.idInfo.ui64Id
			 &&  pVc->activeMems_from[i].avStream.obj.resObj.uiObjType  ==  videoConferenceStatus.mems[nItems].avStream.obj.resObj.uiObjType
			 &&  pVc->activeMems_from[i].avStream.obj.resObj.usIndex_obj  ==  videoConferenceStatus.mems[nItems].avStream.obj.resObj.usIndex_obj
			 )  
		 {
			 if  (  bMe  )  {
				 lvItem.iItem  =  nItems;
				 lstrcpyn(  tBuf,  videoConferenceStatus.mems[nItems].desc,  mycountof(  tBuf  )  );
				 lvItem.iImage  =  nImage;
				 pListCtrl->SetItem(  &lvItem  );
			 }

			 nItems  ++  ;  continue;
		 }		 
		 videoConferenceStatus.mems[nItems].avStream  =  pVc->activeMems_from[i].avStream;
		 //videoConferenceStatus.mems[nItems].ucbActive  =  TRUE;
		 lstrcpyn(  videoConferenceStatus.mems[nItems].desc,  pVc->activeMems_from[i].desc,  mycountof(  videoConferenceStatus.mems[nItems].desc  )  );
		 _sntprintf(  videoConferenceStatus.mems[nItems].desc,  mycountof(  videoConferenceStatus.mems[nItems].desc  ),  
			 _T(  "%s %I64u %d %d"  ),  
			 videoConferenceStatus.mems[nItems].desc,  
			 videoConferenceStatus.mems[nItems].avStream.idInfo.ui64Id,
			 videoConferenceStatus.mems[nItems].avStream.obj.resObj.uiObjType,  
			 videoConferenceStatus.mems[nItems].avStream.obj.resObj.usIndex_obj  );

		 if  (  nItems  <  videoConferenceStatus.usCnt  )  {

			 lvItem.iItem  =  nItems;
			 lstrcpyn(  tBuf,  videoConferenceStatus.mems[nItems].desc,  mycountof(  tBuf  )  );
			 lvItem.iImage  =  nImage;
			 pListCtrl->SetItem(  &lvItem  );

			 nItems  ++  ;
			 continue;				 
		 }
		 
		 index  =  0;  pListCtrl->InsertItem(  nItems,  videoConferenceStatus.mems[nItems].desc,  nImage  );

		 nItems  ++  ;
		 videoConferenceStatus.usCnt  ++  ;
		 continue;
	}

	//
	for  (  i  =  nItems;  i  <  videoConferenceStatus.usCnt;  i  ++  )  {
		 memset(  &videoConferenceStatus.mems[i],  0,  sizeof(  videoConferenceStatus.mems[i]  )  );
		 pListCtrl->DeleteItem(  i  );
	}
	videoConferenceStatus.usCnt  =  nItems;
	
	for  (  i  =  nItems;  i  <  pListCtrl->GetItemCount(  );  i  ++  )  {
		 pListCtrl->DeleteItem(  i  );
	}
	memset(  &videoConferenceStatus.requestingMems,  0,  sizeof(  videoConferenceStatus.requestingMems  )  );


#if  10
	int  nItems_req  =  0;
	for  (  i  =  0;  i  <  mycountof(  pVc->requestingMems_from  );  i  ++  )  {
		if  (  !pVc->requestingMems_from[i].avStream.idInfo.ui64Id  )  continue;
		if  (  pVc->requestingMems_from[i].avStream.idInfo.ui64Id  ==  videoConferenceStatus.requestingMems.mems[nItems_req].idInfo.ui64Id
			 //&&  !videoConferenceStatus.mems[nItems].ucbActive  
			 )  	
		 {
			 nItems_req  ++  ;  continue;
		 }		 
		 
		videoConferenceStatus.requestingMems.mems[nItems_req].idInfo.ui64Id  =  pVc->requestingMems_from[i].avStream.idInfo.ui64Id;
		 //videoConferenceStatus.mems[nItems].ucbActive  =  FALSE;
		lstrcpyn(  videoConferenceStatus.requestingMems.mems[nItems_req].desc,  pVc->requestingMems_from[i].desc,  mycountof(  videoConferenceStatus.requestingMems.mems[nItems_req].desc  )  );

		if  (  nItems  <  videoConferenceStatus.requestingMems.usCnt  )  {

			 lvItem.iItem  =  nItems  +  nItems_req;
			 lstrcpyn(  tBuf,  videoConferenceStatus.requestingMems.mems[nItems_req].desc,  mycountof(  tBuf  )  );
			 lvItem.iImage  =  pQyMc->cfg.image.nImage_requestingMem;

			 pListCtrl->SetItem(  &lvItem  );
			 nItems  ++  ;
			 continue;				 
		 }
		 
		 nImage  =  pQyMc->cfg.image.nImage_requestingMem;
		 index  =  0;  pListCtrl->InsertItem(  nItems,  videoConferenceStatus.mems[nItems].desc,  nImage  );
				   
		 nItems_req  ++  ;
		 videoConferenceStatus.requestingMems.usCnt  ++  ;
		 continue;
	}

#endif




	//  2014/12/11
	//refreshBtn_micOff(  );

	//  2017/08/28
	dlgTalk_fillPeerInfo(  hCurTalk  );



	iErr  =  0;

errLabel:
	return  iErr;
}



//
#if  0
int  CDlgInstantAssistant::refreshBtn_micOff(  )
{
	QY_MC		*	pQyMc		=		QY_GET_GBUF();
	BOOL			bSel  =  FALSE;
	TCHAR			btnDesc[128]  =  _T(  ""  );
	BOOL			bEnable_micOn  =  FALSE;
	BOOL			bEnable_micOff  =  FALSE;

	//
	if  (  m_var.selection.iSel  >=  0  &&  m_var.selection.iSel  <  m_var.videoConferenceStatus.usCnt  
		&&  m_var.selection.idInfo_sel.ui64Id  )  
	{
		VIDEO_CONFERENCE_MEM  *  pMem  =  &m_var.videoConferenceStatus.mems[m_var.selection.iSel];
		if  (  pMem->mem.idInfo.ui64Id  ==  m_var.selection.idInfo_sel.ui64Id  )  {
			bSel  =  TRUE;
			if  (  pMem->ucbActive  )  {
				bEnable_micOn  =  FALSE;
				bEnable_micOff  =  TRUE;
				//GetDlgItem(  m_var.guiData.iIDC_BUTTON_micOff  )->EnableWindow(  TRUE  );
				//GetDlgItem(  m_var.guiData.iIDC_BUTTON_micOn  )->EnableWindow(  FALSE  );
				}
			else  {
				  bEnable_micOn  =  TRUE;
				  bEnable_micOff  =  TRUE;
				  //  GetDlgItem(  m_var.guiData.iIDC_BUTTON_micOff  )->EnableWindow(  TRUE  );
				  //  GetDlgItem(  m_var.guiData.iIDC_BUTTON_micOn  )->EnableWindow(  TRUE  );
			}
		}
	}
#if  0
	//  if  (  !bSel  )  safeTcsnCpy(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_micOnOff  ),  btnDesc,  mycountof(  btnDesc  )  );
	if  (  !bSel  ) {
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_micOff  )->EnableWindow(  FALSE  );
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_micOn  )->EnableWindow(  FALSE  );
		return  0;
	}
#endif

	//
	::EnableWindow(  ::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_BUTTON_micOn  ),  bEnable_micOn  );
	::EnableWindow(  ::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_BUTTON_micOff  ),  bEnable_micOff  );
	
	return  0;
}
#endif


//
  int  CDlgInstantAssistant::initForTaskAv(  )
{
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pDlgTalkVar	=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  m_var.guiData.param.hMgrTalk,  _T(  "dlgIa::initForTaskAv"  )  );
	if  (  !pDlgTalkVar  )  return  -1;
	
	if  (  m_var.bTaskAvInited  )  return  -1;

	if  (  !pDlgTalkVar->av.taskInfo.bTaskInited  )  {
		if  (  !bMediaTaskExists(  pProcInfo,  pDlgTalkVar->av.taskInfo.iTaskId  )  )  return  -1;
		pDlgTalkVar->av.taskInfo.bTaskInited  =  TRUE;
	}
	

	//  trigger the instantAssistant to refresh													
	//  ::SendMessage(  this->m_hWnd,  CONST_qyWm_comm,  0,  0  );
	fillTalkerList(  );

	m_var.bTaskAvInited  =  TRUE;

	return  0;
}


  //
  int  CDlgInstantAssistant::getInitiatorDesc(  TCHAR  *  desc,  int  cnt  )
  {
	  int  iErr =  -1;
	  CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
		  	DLG_TALK_var	*	pDlgTalkVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  m_var.guiData.param.hMgrTalk,  _T(  "dlgIa::OnInitDialog"  )  );
	if  (  !pDlgTalkVar  )  goto  errLabel;
	MC_VAR_isCli  *  pProcInfo  = QY_GET_procInfo_isCli(  );

  	//
	if  (  pDlgTalkVar->av.taskInfo.bTaskExists  )  {
#if  0
		int  index_taskInfo  =  getQmcTaskInfoIndexBySth(  pProcInfo,  pDlgTalkVar->av.taskInfo.iTaskId  );
		QMC_TASK_INFO  *  pTaskInfo  = (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  index_taskInfo  );
		if  (  pTaskInfo  )  {
			MIS_MSG_TASK  *  pMsgTask  =  &pTaskInfo->var.pTaskData->msgU.task;
			if  (  pMsgTask->uiType  ==  CONST_misMsgType_task  )  {
				IM_CONTENTU  *  pContent  =  M_getMsgContent(  pMsgTask->ucFlg,  &pMsgTask->data  );
				if  (  pContent  )  {
					if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
						if  (  pContent->transferAvInfo.confCfg.idInfo_initiator.ui64Id  )  {
							TCHAR  talkerDesc[128]  =  _T(  ""  );
							getTalkerDesc(  pDlgTalkVar->pMisCnt,  &pContent->transferAvInfo.confCfg.idInfo_initiator,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  );
							//SetDlgItemText(  IDC_STATIC_initiator,  talkerDesc  );
							//safeTcsnCpy(  talkerDesc,  desc,  cnt  );  
							if  (  desc  &&  cnt  )  {
								_sntprintf(  desc,  cnt,  _T(  "%s %I64u"  ),  talkerDesc,  pContent->transferAvInfo.confCfg.idInfo_initiator.ui64Id  );
							}
						}
					}
				}
			}
		}
#endif
		//
							TCHAR  talkerDesc[128]  =  _T(  ""  );
							getTalkerDesc(  pDlgTalkVar->av.taskInfo.idInfo_initiator,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  );
							if  (  desc  &&  cnt  )  {
								_sntprintf(  desc,  cnt,  _T(  "%s %I64u"  ),  talkerDesc,  pDlgTalkVar->av.taskInfo.idInfo_initiator.ui64Id  );
							}
	}


	iErr  =  0;
	errLabel:
	return  iErr;
  }





void CDlgInstantAssistant::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgInstantAssistant, CDialog)
#ifndef  __WINCE__
	ON_WM_NCHITTEST()
#endif
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_request, &CDlgInstantAssistant::OnBnClickedrequest)
	ON_WM_CONTEXTMENU()
//	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(CONST_qyWm_comm, OnQyComm)
	ON_NOTIFY(NM_CLICK, IDC_talkerList, &CDlgInstantAssistant::OnNMClicktalkerlist)
	ON_NOTIFY(NM_RCLICK, IDC_talkerList, &CDlgInstantAssistant::OnNMRClicktalkerlist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_talkerList, &CDlgInstantAssistant::OnLvnItemchangedtalkerlist)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	//  ON_CBN_SELCHANGE(IDC_COMBO_usLayoutType, &CDlgInstantAssistant::OnCbnSelchangeCombouslayouttype)
	ON_BN_CLICKED(IDC_BUTTON_msgBox, &CDlgInstantAssistant::OnBnClickedButtonmsgbox)
	ON_BN_CLICKED(IDC_BUTTON_sendFile, &CDlgInstantAssistant::OnBnClickedButtonsendfile)
	ON_BN_CLICKED(IDC_BUTTON_fullScreen, &CDlgInstantAssistant::OnBnClickedButtonfullscreen)
	ON_BN_CLICKED(IDC_BUTTON_av, &CDlgInstantAssistant::OnBnClickedButtonav)
	ON_BN_CLICKED(IDC_BUTTON_av_accept, &CDlgInstantAssistant::OnBnClickedButtonavaccept)
	ON_BN_CLICKED(IDC_BUTTON_av_deny, &CDlgInstantAssistant::OnBnClickedButtonavdeny)
	ON_BN_CLICKED(IDC_BUTTON_shareScreen, &CDlgInstantAssistant::OnBnClickedButtonsharescreen)
	//  ON_BN_CLICKED(IDC_BUTTON_enlarge, &CDlgInstantAssistant::OnBnClickedButtonenlarge)
	ON_BN_CLICKED(IDC_BUTTON_nonexclusive, &CDlgInstantAssistant::OnBnClickedButtonnonexclusive)
	ON_BN_CLICKED(IDC_BUTTON_close, &CDlgInstantAssistant::OnBnClickedButtonclose)
	ON_BN_CLICKED(IDC_BUTTON_more, &CDlgInstantAssistant::OnBnClickedButtonmore)
	ON_BN_CLICKED(IDC_BUTTON_rule, &CDlgInstantAssistant::OnBnClickedButtonrule)
#if 0
	ON_BN_CLICKED(IDC_BUTTON_msg, &CDlgInstantAssistant::OnBnClickedButtonmsg)
#endif
	ON_BN_CLICKED(IDC_BUTTON_shareMediaFile, &CDlgInstantAssistant::OnBnClickedButtonsharemediafile)
#ifndef  __APP_qyMc_touchscreen__
	ON_BN_CLICKED(IDC_BUTTON_showDlgMenu, &CDlgInstantAssistant::OnBnClickedButtonshowdlgmenu)
#endif
	ON_BN_CLICKED(IDC_BUTTON_remoteVideo, &CDlgInstantAssistant::OnBnClickedButtonremoteVideo)
	ON_BN_CLICKED(IDC_BUTTON_ptzPanel, &CDlgInstantAssistant::OnBnClickedButtonptzPanel)
	ON_BN_CLICKED(IDC_BUTTON_closeAndClean, &CDlgInstantAssistant::OnBnClickedButtoncloseandclean)
	ON_BN_CLICKED(IDC_BUTTON_selAvCompressor, &CDlgInstantAssistant::OnBnClickedButtonselAvCompressor)
	ON_BN_CLICKED(IDC_BUTTON_subtitles, &CDlgInstantAssistant::OnBnClickedButtonsubtitles)
	ON_BN_CLICKED(IDC_BUTTON_layoutType, &CDlgInstantAssistant::OnBnClickedButtonlayouttype)
	ON_BN_CLICKED(IDC_BUTTON_menuBar, &CDlgInstantAssistant::OnBnClickedButtonmenubar)
	ON_BN_CLICKED(IDC_BUTTON_offlineRes, &CDlgInstantAssistant::OnBnClickedButtonofflineres)
	ON_BN_CLICKED(IDC_BUTTON_joinInBgWall, &CDlgInstantAssistant::OnBnClickedButtonjoininbgwall)
	//ON_BN_CLICKED(IDC_BUTTON_confMgr, &CDlgInstantAssistant::OnBnClickedButtonconfmgr)
	ON_BN_CLICKED(IDC_BUTTON_memList, &CDlgInstantAssistant::OnBnClickedButtonmemlist)
	ON_BN_CLICKED(IDC_BUTTON_stat, &CDlgInstantAssistant::OnBnClickedButtonstat)
	ON_BN_CLICKED(IDC_BUTTON_2ndScreen, &CDlgInstantAssistant::OnBnClickedButton2ndscreen)
	ON_BN_CLICKED(IDC_BUTTON_localVideo, &CDlgInstantAssistant::OnBnClickedButtonlocalvideo)
	ON_BN_CLICKED(IDC_CHECK_audio, &CDlgInstantAssistant::OnBnClickedCheckaudio)
	ON_BN_CLICKED(IDC_CHECK_video, &CDlgInstantAssistant::OnBnClickedCheckvideo)
	ON_BN_CLICKED(IDC_BUTTON_ipc, &CDlgInstantAssistant::OnBnClickedButtonipc)
	ON_BN_CLICKED(IDC_CHECK_lLayout, &CDlgInstantAssistant::OnBnClickedCheckllayout)
	ON_BN_CLICKED(IDC_BUTTON_selOneBig, &CDlgInstantAssistant::OnBnClickedButtonselonebig)
	ON_BN_CLICKED(IDC_VIDEORIGHT, &CDlgInstantAssistant::OnBnClickedVideoright)
	ON_BN_CLICKED(IDC_VIDEOLEFT, &CDlgInstantAssistant::OnBnClickedVideoleft)
	ON_BN_CLICKED(IDC_VIDEOTOP, &CDlgInstantAssistant::OnBnClickedVideotop)
	ON_BN_CLICKED(IDC_VIDEOBOTTOM, &CDlgInstantAssistant::OnBnClickedVideobottom)
	ON_BN_CLICKED(IDC_COORDINATE, &CDlgInstantAssistant::OnBnClickedCoordinate)
	ON_BN_CLICKED(IDC_CANCELAMP, &CDlgInstantAssistant::OnBnClickedCancelamp)
END_MESSAGE_MAP()


// CDlgInstantAssistant message handlers
//
 int  locateInstantAssistant(  HWND  hDlg,  DLG_instantAssistant_var  &  m_var  )
{
	int					iErr		=	-1;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	QY_MC  *  pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	DLG_talk_var	*	pMgrTalkVar	=  (  DLG_talk_var  *  )help_getDlgTalkVar_mgr.getVar(  m_var.guiData.param.hMgrTalk  );
	if  (  !pMgrTalkVar  )  return  -1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
	DLG_talk_var  *  pCurTalkVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  m_var.guiData.param.hCurTalk  );
	if  (  !pCurTalkVar  )  return  -1;

	RECT	rc;
	int		iX,  iY;

	//
	int	iW_dlg  =	m_var.oldLayout.iW_dlg;
	int	iH_dlg	=	m_var.oldLayout.iH_dlg;

	//
	if  (  pCurTalkVar->guiData.ucbShowMore  )  {
		//
#if 0
		GetClientRect(  m_var.guiData.hParent,  &rc  );
		int  iW_parent  =  rc.right  -  rc.left;
		int  iH_parent  =  rc.bottom  -  rc.top;
		
		RECT  rc_ia;
		GetWindowRect(  hDlg,  &rc_ia  );
		//
		iW_dlg  =  rc_ia.right  -  rc_ia.left;
		iH_dlg  =  rc_ia.bottom  -  rc_ia.top;
		
		//
		int  iL  =  (  iW_parent  -  iW_dlg  )  /  2;
		if  (  iL  <  0  )  iL  =  0;
		int  iT  =  (  iH_parent  -  iH_dlg  )  /  2;
		if  (  iT  <  0  )  iT  =  0;
		//
		POINT  pnt;
		pnt.x  =  rc.left  +  iL;
		pnt.y  =  rc.top  +  iT;
		//
		MapWindowPoints(  m_var.guiData.hParent,  NULL,  &pnt,  1  );
		//
		MoveWindow(  hDlg,  pnt.x,  pnt.y,  iW_dlg,  iH_dlg,  TRUE  );
#endif
		//
		centerWndInParent(  hDlg,  m_var.guiData.hParent  );  

		return  0;
	}


	//	
	if  (  !bApp_ts(  pQyMc  )  )  {  //  #ifndef  __APP_qyMc_touchscreen__
#if  0
     	 if  (  pCurTalkVar->guiData.ucbShowMore  )  {  iW_dlg  =  m_var.oldLayout.iW_dlg_more;  iH_dlg  =  m_var.oldLayout.iH_dlg_more;  }
		 //
		 {
			   ::GetClientRect(  m_var.guiData.hParent,  &rc  );
			   ::MapWindowPoints(  m_var.guiData.hParent,  NULL,  (  LPPOINT  )&rc,  2  );
			   //
			   //  iX  =  rc.right  -  m_var.oldLayout.iW_dlg;	//  -  10;
			   iX  =  rc.right  -  iW_dlg;			//  2012/04/04
			   iY  =  rc.top;	//    +  40;
			   //
			   //  2014/12/07
			   BOOL  bDone  =  FALSE;
			   if  (  isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  {
				   if  (  pDlgTalkVar->av.taskInfo.bTaskExists
					   &&  pDlgTalkVar->av.taskInfo.ucbVideoConference
					   &&  !pDlgTalkVar->av.taskInfo.ucbStarter
					   &&  pDlgTalkVar->av.taskInfo.mosaicTrans.bExists_confMosaic  )
				   {
#if 0
					   //  2014/12/07. 这里对other的视频是大概估计下。不是很精确的计算。
					   int  iH;
					   calc_other_rect(  &pDlgTalkVar->m_layout,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  NULL,  &iH  );  
					   //
					   if  (  iH  >  480  )  iH  =  480;
					   //
					   iY  +=  iH;
#endif
					   iY  +=  (  rc.bottom  -  rc.top  )  /  2  -  (  iH_dlg  /  2  );

					   //
					   bDone  =  TRUE;
				   }
			   }

			   if  (  !bDone  )  {				
				   if  (  pCurTalkVar->m_layout.usLayoutType_cur  ==  CONST_usLayoutType_training  )  {
					   unsigned  int	uiH_conference;
					   RECT	rc_conference;
					   HWND	hCtrl  =  GetDlgItem(  m_var.guiData.param.hCurTalk,  pCurTalkVar->guiData.iIDC_STATIC_otherDesc  );
					   if  (  hCtrl  )  {
						   GetClientRect(  hCtrl,  &rc_conference  );
						   uiH_conference  =  rc_conference.bottom  -  rc_conference.top;
						   if  (  uiH_conference  >  480  )  uiH_conference  =  480;
						   //  iY  +=  240;
						   iY  +=  uiH_conference;
					   }
				   }
			   }
		 }
#endif
		 }	
	else  {  //  #else

	RECT	rc_ctrl;
	HWND	hCtrl;

	hCtrl  =	::GetDlgItem(  m_var.guiData.param.hMgrTalk,  IDC_STATIC_dlgDesc  );
	::GetWindowRect(  hCtrl,  &rc_ctrl  );
	int	iH_dlgDesc  =  rc_ctrl.bottom  -  rc_ctrl.top;
	int	iY_dlgDesc  =  rc_ctrl.top;

	//
	int  iZoneObjsType  =  0;
	//
	ZONE_objs  *  pZoneObjs  =  (  ZONE_objs  *  )pFuncs->pf_getZoneObjs(  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall,  iZoneObjsType  );
	//ZONE_objs_info  *  pDlgWallsVar  =  (  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall,  iZoneObjsType  );
	//
	BOOL  bEnlarged  =  FALSE;
	CAP_RECT  capRect  =  {0};

	//if  (  getWallMemInfo(  pZoneObjs,  m_var.guiData.param.hDlgTalk,  &bEnlarged  )  )  goto  errLabel;

	//
	::GetClientRect(  m_var.guiData.hParent,  &rc  );
	capRect.iX  =  rc.left;
	capRect.iY  =  rc.top;
	capRect.iW  =  rc.right  -  rc.left;
	capRect.iH  =  rc.bottom  -  rc.top;
	
	//
#if  0
	if  (  1  //  bEnlarged  //  
		&&  (  m_var.guiData.param.xPos_screen  ||  m_var.guiData.param.yPos_screen  )  )	// 这里出现在鼠标下方，方便大屏幕的操作
	{
		  POINT	point;
		  point.x  =  m_var.guiData.param.xPos_screen;
		  point.y  =  m_var.guiData.param.yPos_screen;

		  ::MapWindowPoints(  NULL,  m_var.guiData.hParent,  &point,  1  );

		  int	iY_spacing_ia2dlgDesc	=	25;

		  if  (  point.x  +  iW_dlg  >  capRect.iW  )  point.x  =  capRect.iW  -  iW_dlg;

		  iH_dlg	=	pCurTalkVar->guiData.ucbShowMore  ?  m_var.oldLayout.iH_dlg_more  :  m_var.oldLayout.iH_dlg;
		  
		  if  (  point.y  +  iY_spacing_ia2dlgDesc  +  iH_dlg  +  iH_dlgDesc  >  capRect.iH  )  point.y  =  capRect.iH  -  iH_dlg  -  iH_dlgDesc  -  iY_spacing_ia2dlgDesc;

		  ::MapWindowPoints(  m_var.guiData.hParent,  NULL,  (  LPPOINT  )&point,  1  );
		  //
		  iX  =  point.x;
		  iY  =  point.y  +  iY_spacing_ia2dlgDesc;
		  //
	}
	else  {
		  RECT	rc;	
		  rc.left  =  capRect.iX;
		  rc.top  =  capRect.iY;
		  rc.right  =  capRect.iY  +  capRect.iW;
		  rc.bottom  =  capRect.iY  +  capRect.iH;

		  ::MapWindowPoints(  m_var.guiData.hParent,  NULL,  (  LPPOINT  )&rc,  2  );

		  iX  =  rc.left;
		  //  if  (  pDlgTalkVar->guiData.ucbShowMsgBox  )  
		  if  (  pDlgTalkVar->guiData.snmpbShowMsgBox  ==  CONST_snmpTrue  )  
		  {
			  int  idc  =  pDlgTalkVar->guiData.iIDC_STATIC_msgTool;
			  hCtrl  =  ::GetDlgItem(  m_var.guiData.param.hMgrTalk,  idc  );
			  ::GetWindowRect(  hCtrl,  &rc_ctrl  );
			  iX  =  rc_ctrl.right;
		  }

		  iH_dlg	=	pDlgTalkVar->guiData.ucbShowMore  ?  m_var.oldLayout.iH_dlg_more  :  m_var.oldLayout.iH_dlg;
		  
		  if  (  m_var.oldLayout.iH_dlg  >  rc.bottom  -  rc.top  -  iH_dlgDesc  )  iY  =  (  rc.bottom  +  rc.top  )  /  2;
		  else  iY  =  iY_dlgDesc  -  m_var.oldLayout.iH_dlg;	//  rc.bottom  -  m_var.oldLayout.iH_dlg  -  iH_dlgDesc;
	}
#endif
	//
	::GetClientRect(  m_var.guiData.hParent,  &rc  );
	MapWindowPoints(  m_var.guiData.hParent,  NULL,  (  LPPOINT  )&rc,  2  );
	iX  =  rc.right  -  m_var.oldLayout.iW_dlg;
	iY  =  rc.bottom  -  m_var.oldLayout.iH_dlg;
	
	//
	if  (  pMgrTalkVar->av.taskInfo.bTaskExists  )  {
		iX  -=  pCurTalkVar->m_layout.iW_meDesc  +  2;
		//
		iY  -=  CONST_iH_status;
	}


	}	//  #endif

	

	::MoveWindow(  hDlg,  iX,  iY,  iW_dlg,  iH_dlg,  TRUE  );

	iErr  =  0;
errLabel:
	return  iErr;
}

int  dlgSetFont_instantAssistant(  HWND  hDlg  )
{
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	CDlgInstantAssistant	*	pDlg	=	(  CDlgInstantAssistant  *  )CWnd::FromHandle(  hDlg  );
	if  (  !pDlg  )  return  -1;

		DLG_guiData_instantAssistant	*	p	=	&pDlg->m_var.guiData;
		G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )pFuncs->pf_get_g_guiData(  );

		int		idc;
		HWND	hCtrl;


		idc  =  p->iIDC_request;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_BUTTON_joinInBgWall;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

#if 0
		idc  =  p->iIDC_BUTTON_msg;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		//
#endif
		//if (  bApp_ts_3d(  )  )  
		{

			idc  =  p->iIDC_BUTTON_menuBar;
			hCtrl	=	::GetDlgItem(  hDlg,  idc  );
			if  (  hCtrl  )  {
				if  (  pGuiData->hFont_btn  )  {
					::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
				}
			}
		}

		idc  =  p->iIDC_BUTTON_av;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		idc  =  p->iIDC_BUTTON_av_accept;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		idc  =  p->iIDC_BUTTON_av_deny;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		idc  =  p->iIDC_BUTTON_shareScreen;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		idc  =  p->iIDC_BUTTON_msgBox;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_BUTTON_close;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		idc  =  p->iIDC_BUTTON_more;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		idc  =  p->iIDC_BUTTON_rule;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		//
		idc  =  p->iIDC_BUTTON_layoutType;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_BUTTON_offlineRes;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_BUTTON_sendFile;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
#if 0
		idc  =  p->iIDC_BUTTON_nonexclusive;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		idc  =  p->iIDC_BUTTON_confMgr;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
#endif

		idc  =  p->iIDC_BUTTON_shareMediaFile;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_BUTTON_subtitles;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_BUTTON_remoteVideo;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_BUTTON_ptzPanel;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_BUTTON_closeAndClean;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		//
		idc  =  p->iIDC_BUTTON_fullScreen;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		//
		idc  =  IDC_BUTTON_memList;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		
		//
		idc  =  IDC_BUTTON_stat;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		

		//
		idc  =  IDCANCEL;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}




		return  0;

}


//
BOOL CDlgInstantAssistant::OnInitDialog()
{
	CDialog::OnInitDialog();

	int				iErr										=	-1;
	QY_MC		*	pQyMc										=	QY_GET_GBUF(  );
	MC_VAR_isCli*	pProcInfo									=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp  *  pFuncs								=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;
	int				iX  =  0,  iY  =  0;

	int				idc;
	HWND			hWnd;
	RECT			rc;
	CRect			rcDialog;
	HWND			hDlg										=	this->m_hWnd;

#ifdef  __DEBUG__
#endif

	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;

	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;


	//
	if  (  !pQyMc  ||  !pQyMc->cfg.pGuiCfg  )  goto  errLabel;
	if  (  !pProcInfo  )  goto  errLabel;
	if  (  !pFuncs  )  goto  errLabel;
	
	//
	DLG_TALK_var	*	pDlgTalkVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  m_var.guiData.param.hMgrTalk,  _T(  "dlgIa::OnInitDialog"  )  );
	if  (  !pDlgTalkVar  )  goto  errLabel;

	DLG_TALK_var	*	pCurTalkVar	=	NULL;
	//
	pCurTalkVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  m_var.guiData.param.hCurTalk,  _T(  "dlgIa::OnInitDialog, hShadow"  )  );	
	if  (  !pCurTalkVar  )  goto  errLabel;


	//
	cusDlgRes(  0, &pQyMc->cusRes,  hDlg,  m_var.guiData.param.iIDD  );


	//  2010/09/03
#if  10
	DWORD	dwStyle	=	GetWindowLong(  m_hWnd,  GWL_STYLE  );
	dwStyle  |=  WS_CLIPCHILDREN;
	SetWindowLong(  m_hWnd,  GWL_STYLE,  dwStyle  );
#endif

	#define		CONST_bkColor_status		RGB(  255,  255,  0  )

	this->m_brush_bk_status.CreateSolidBrush(  CONST_bkColor_status  );

	//
	if  (  m_var.pm_LargeImageList  ||  m_var.pm_SmallImageList  )  goto  errLabel;
	//
	m_var.pm_LargeImageList  =  myImageList_new( IDB_LARGEICONS, 32, 1, RGB( 255, 255, 255 ) );
	m_var.pm_SmallImageList  =  myImageList_new( IDB_qnmIcons, 16, 1, RGB( 255, 255, 255 ) );
	if  (  !m_var.pm_LargeImageList  ||  !m_var.pm_SmallImageList  )  goto  errLabel;
	CImageList  &m_LargeImageList  =  *(  CImageList  *  )m_var.pm_LargeImageList;
	CImageList  &m_SmallImageList  =  *(  CImageList  *  )m_var.pm_SmallImageList;

	//
	::GetWindowRect(  this->m_hWnd,  &rcDialog  );
	m_var.oldLayout.iW_dlg  =  rcDialog.right  -  rcDialog.left;
	m_var.oldLayout.iH_dlg  =  rcDialog.bottom  -  rcDialog.top;

	int	 nCols_btn;
	int  nRows_btn;


	//			
	//if  (  pDlgTalkVar->av.taskInfo.ucbStarter  &&  pDlgTalkVar->av.taskInfo.ucbVideoConference  )  m_var.bVideoConferenceStarter  =  TRUE;  		
	if  (  pDlgTalkVar->av.taskInfo.bTaskExists  
		&&  pDlgTalkVar->av.taskInfo.ucbVideoConference  )				  
	{
					  CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;					  	
					  //
					  DLG_TALK_var  *  pMgrVar  =  pDlgTalkVar;
					  if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  {
						  TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
						  if  (  !pShadow  )  goto  errLabel;
						  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pShadow->hMgr,  _T(  "getIDD_instantAssistant,hMgr"  )  );
						  if  (  !pMgrVar  )  goto  errLabel;	
					  }
					  //
					  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
					  if  (  !pShadowMgr  )  goto  errLabel;
					  //
					  if  (  pShadowMgr->av.ucbMeConfMgr  )  m_var.ucbConfMgr  =  TRUE;		
					  //  2015/07/30
					  if  (  pMgrVar->av.taskInfo.ucbStarter  )  m_var.ucbConfMgr  =  TRUE;
	}
	

	//  2013/08/05
	//
	idc  =  IDC_STATIC_status;
	hWnd  =  ::GetDlgItem(  hDlg,  idc  );
	if  (  hWnd  )  {
		::GetWindowRect(  hWnd,  &rc  );
		m_var.oldLayout.iW_status  =  rc.right  -  rc.left;
		m_var.oldLayout.iH_status  =  rc.bottom  -  rc.top;
	}

	//
	idc  =  IDC_STATIC_initiator;
	hWnd  =  ::GetDlgItem(  hDlg,  idc  );
	if  (  hWnd  )  {
		::GetWindowRect(  hWnd,  &rc  );
		m_var.oldLayout.iW_initiator  =  rc.right  -  rc.left;
		m_var.oldLayout.iH_initiator  =  rc.bottom  -  rc.top;
	}


	//
	//  
	m_var.idcList  =  IDC_talkerList;
	m_var.pColumns  =  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_instantAssistant_talkerListColumns  );
	//
	CListCtrl  *  pListCtrl;  
	pListCtrl  =  (  CListCtrl  *  )CWnd::FromHandle(  ::GetDlgItem(  hDlg,  m_var.idcList  )  );
	if  (  pListCtrl  )  {
				  //
				  pListCtrl->ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
				  pListCtrl->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );
				  //
				  pListCtrl->SetImageList(  &m_LargeImageList,  LVSIL_NORMAL  );
				  pListCtrl->SetImageList(  &m_SmallImageList,  LVSIL_SMALL  );

				  //  
				  int					i;
				  QY_COLUMNINFO	*	pColumns;

				  LV_COLUMN lvc;
				  lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

				  pColumns  =  m_var.pColumns;
				  for  (  i  =  0;  pColumns[i].type  !=  -1;  i  ++  )  {
					   lvc.iSubItem		=	i;
					   lvc.pszText		=	pColumns[i].label;
					   lvc.cx			=	pColumns[i].width;
					   lvc.fmt			=	pColumns[i].fmt;
					   pListCtrl->InsertColumn(  i,  &lvc  );
				  }

	}

	//
		if  (  !bApp_ts(  pQyMc  )  )  {  //  #ifdef  __APP_qyMc__

		}
		else  
		{  //  #ifdef  __APP_qyMc_touchscreen__

		switch  (  m_var.guiData.param.iIDD  )  {

			case  IDD_instantAssistant_start:  {
		      
				  idc  =  IDC_BUTTON_av;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iEdge_t  =  rc.top  -  rcDialog.top;
				  m_var.oldLayout.iEdge_l  =  rc.left  -  rcDialog.left;
				  m_var.oldLayout.iW_btn  =  rc.right  -  rc.left;
				  m_var.oldLayout.iH_btn  =  rc.bottom  -  rc.top;
				  //
				  idc  =  IDC_BUTTON_av_accept;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iX_spacing  =  rc.left  -  rcDialog.left  -  m_var.oldLayout.iEdge_l  -  m_var.oldLayout.iW_btn;
				  //
				  idc  =  IDC_BUTTON_rule;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iY_spacing  =  rc.top  -  rcDialog.top  -  m_var.oldLayout.iEdge_t  -  m_var.oldLayout.iH_btn;
			  
				  //
#if  0
				  if  (  pCurTalkVar->guiData.bImGrp  )  nCols_btn  =  6;    // + joinInBgWall 
				  else  nCols_btn  =  5;  
#endif
				  nCols_btn  =  4;		//  2019/05/06
				  //
				  m_var.oldLayout.iW_dlg  =  m_var.oldLayout.iEdge_l  *  2  +  m_var.oldLayout.iW_btn  *  nCols_btn  +  m_var.oldLayout.iX_spacing  *  (  nCols_btn  -  1  );
				  m_var.oldLayout.iH_dlg  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn;
				  //
  				  //  more
				  nCols_btn  =  5;
				  if  (  !pCurTalkVar->guiData.bImGrp  )  nCols_btn  =  6;    // + joinInBgWall 				  
				  if  (  !bApp_ts_3d(  pQyMc  )  )  nRows_btn  =  2;
				  else  nRows_btn  =  3;
				  //
				  m_var.oldLayout.iW_dlg_more  =  m_var.oldLayout.iEdge_l  *  2  +  m_var.oldLayout.iW_btn  *  nCols_btn  +  m_var.oldLayout.iX_spacing  *  (  nCols_btn  -  1  );
				  m_var.oldLayout.iH_dlg_more  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn  *  nRows_btn  +  m_var.oldLayout.iY_spacing  *  (  nRows_btn  -  1  );
				  //

				  }
			      break;
#if  0
			case  IDD_instantAssistant_start_min:
				  idc  =  IDC_BUTTON_av;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iEdge_t  =  rc.top  -  rcDialog.top;
				  m_var.oldLayout.iEdge_l  =  rc.left  -  rcDialog.left;
				  m_var.oldLayout.iW_btn  =  rc.right  -  rc.left;
				  m_var.oldLayout.iH_btn  =  rc.bottom  -  rc.top;
				  //
				  idc  =  IDC_BUTTON_av_accept;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iX_spacing  =  rc.left  -  rcDialog.left  -  m_var.oldLayout.iEdge_l  -  m_var.oldLayout.iW_btn;
				  //
#if  0
				  idc  =  IDC_BUTTON_rule;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iY_spacing  =  rc.top  -  rcDialog.top  -  m_var.oldLayout.iEdge_t  -  m_var.oldLayout.iH_btn;
#endif
			  
				  //
				  nCols_btn  =  4;
				  m_var.oldLayout.iW_dlg  =  m_var.oldLayout.iEdge_l  *  2  +  m_var.oldLayout.iW_btn  *  nCols_btn  +  m_var.oldLayout.iX_spacing  *  (  nCols_btn  -  1  );
				  m_var.oldLayout.iH_dlg  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn;
				  //
				  nRows_btn  =  1;
				  m_var.oldLayout.iW_dlg_more  =  m_var.oldLayout.iW_dlg;
				  m_var.oldLayout.iH_dlg_more  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn  *  nRows_btn  +  m_var.oldLayout.iY_spacing  *  (  nRows_btn  -  1  );
				  //

				  //
				  break;
#endif
				  //
			case  IDD_instantAssistant_start_more:  {
				  int  ii  =  0;
				  }
				  break;
			case  IDD_instantAssistant_start_grp_more:  {
				  int  ii  =  0;
				  }
				  break;

			case  IDD_instantAssistant_start_wait:  {
		      
				  idc  =  IDC_BUTTON_av;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iEdge_t  =  rc.top  -  rcDialog.top;
				  m_var.oldLayout.iEdge_l  =  rc.left  -  rcDialog.left;
				  m_var.oldLayout.iW_btn  =  rc.right  -  rc.left;
				  m_var.oldLayout.iH_btn  =  rc.bottom  -  rc.top;
				  //
				  idc  =  IDC_BUTTON_av_accept;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iX_spacing  =  rc.left  -  rcDialog.left  -  m_var.oldLayout.iEdge_l  -  m_var.oldLayout.iW_btn;
				  //
				  idc  =  IDC_BUTTON_rule;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iY_spacing  =  rc.top  -  rcDialog.top  -  m_var.oldLayout.iEdge_t  -  m_var.oldLayout.iH_btn;
			  
				  //

				  if  (  pCurTalkVar->guiData.bImGrp  )  nCols_btn  =  6;    // + joinInBgWall 
				  else  nCols_btn  =  5;  
				  m_var.oldLayout.iW_dlg  =  m_var.oldLayout.iEdge_l  *  2  +  m_var.oldLayout.iW_btn  *  nCols_btn  +  m_var.oldLayout.iX_spacing  *  (  nCols_btn  -  1  );
				  m_var.oldLayout.iH_dlg  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn;
				  //
				  nRows_btn  =  2;
				  m_var.oldLayout.iW_dlg_more  =  m_var.oldLayout.iW_dlg;
				  m_var.oldLayout.iH_dlg_more  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn  *  nRows_btn+  m_var.oldLayout.iY_spacing  *  (  nRows_btn  -  1  );
				  //

				  }
			      break;
#if  0
			case  IDD_instantAssistant_start_wait_min:  {
				  idc  =  IDC_BUTTON_av;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iEdge_t  =  rc.top  -  rcDialog.top;
				  m_var.oldLayout.iEdge_l  =  rc.left  -  rcDialog.left;
				  m_var.oldLayout.iW_btn  =  rc.right  -  rc.left;
				  m_var.oldLayout.iH_btn  =  rc.bottom  -  rc.top;
				  //
				  idc  =  IDC_BUTTON_av_accept;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iX_spacing  =  rc.left  -  rcDialog.left  -  m_var.oldLayout.iEdge_l  -  m_var.oldLayout.iW_btn;
				  //
#if  0
				  idc  =  IDC_BUTTON_rule;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iY_spacing  =  rc.top  -  rcDialog.top  -  m_var.oldLayout.iEdge_t  -  m_var.oldLayout.iH_btn;
#endif
			  
				  //
				  nCols_btn  =  4;
				  m_var.oldLayout.iW_dlg  =  m_var.oldLayout.iEdge_l  *  2  +  m_var.oldLayout.iW_btn  *  nCols_btn  +  m_var.oldLayout.iX_spacing  *  (  nCols_btn  -  1  );
				  m_var.oldLayout.iH_dlg  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn;
				  //
				  nRows_btn  =  1;
				  m_var.oldLayout.iW_dlg_more  =  m_var.oldLayout.iW_dlg;
				  m_var.oldLayout.iH_dlg_more  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn  *  nRows_btn  +  m_var.oldLayout.iY_spacing  *  (  nRows_btn  -  1  );
				  //
				  }
				  //
				  break;
#endif

			case  IDD_instantAssistant_av:  {
				  //
				  idc  =  IDC_request;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iEdge_t  =  rc.top  -  rcDialog.top;
				  m_var.oldLayout.iEdge_l  =  rc.left  -  rcDialog.left;
				  m_var.oldLayout.iW_btn_request  =  rc.right  -  rc.left;
				  m_var.oldLayout.iW_btn  =  rc.right  -  rc.left;
				  m_var.oldLayout.iH_btn  =  rc.bottom  -  rc.top;
				  //
				  //
				  idc  =  IDC_BUTTON_rule;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iY_spacing  =  rc.top  -  rcDialog.top  -  m_var.oldLayout.iEdge_t  -  m_var.oldLayout.iH_btn;

				  //
				  idc  =  IDC_talkerList;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iW_talkerList  =  rc.right  -  rc.left;
				  m_var.oldLayout.iH_talkerList  =  rc.bottom  -  rc.top;

				  //  
				  //if  (  pDlgTalkVar->av.taskInfo.ucbStarter  &&  pDlgTalkVar->av.taskInfo.ucbVideoConference  )  m_var.bVideoConferenceStarter  =  TRUE;  

				  //
				  //  if  (  m_var.bVideoConferenceStarter  )  
				  m_var.oldLayout.iH_talkerList  *=  2;

				  //
				  nCols_btn  =  4;			//  2019/05/06
				  m_var.oldLayout.iW_dlg  =  m_var.oldLayout.iEdge_l  *  2  +  m_var.oldLayout.iW_btn  *  nCols_btn  +  m_var.oldLayout.iX_spacing  *  (  nCols_btn  -  1  );
				  m_var.oldLayout.iH_dlg  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn;
				  //
				  if  (  pCurTalkVar->guiData.bImGrp  )  nCols_btn  =  8;    // + joinInBgWall 
				  else  nCols_btn  =  6; 
				  //  nRows_btn  =  4;
				  m_var.oldLayout.iW_dlg_more  =  m_var.oldLayout.iEdge_l  *  2  +  m_var.oldLayout.iW_btn  *  nCols_btn  +  m_var.oldLayout.iX_spacing  *  (  nCols_btn  -  1  );
				  m_var.oldLayout.iH_dlg_more  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn  +  m_var.oldLayout.iY_spacing  
					  //  +  m_var.oldLayout.iH_usLayoutType  +  m_var.oldLayout.iY_spacing
					  //  +  m_var.oldLayout.iH_btn  +  m_var.oldLayout.iY_spacing
					  +  m_var.oldLayout.iH_talkerList  +  m_var.oldLayout.iY_spacing
					  +  m_var.oldLayout.iH_status;



				  //  sizeAllControls_dlgInstantAssistant(  this->m_hWnd,  m_var  );

#if  10		//  2013/06/24
				  QY_DMITEM	*	pTable;
				  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_usLayoutTypeTable  );
				  idc  =  m_var.guiData.iIDC_BUTTON_layoutType;
				  ::SetDlgItemText(  hDlg,  idc,  qyGetDesByType1(  pTable,  dlgTalk_get_usLayoutType_local(  m_var.guiData.param.hMgrTalk  )  )  );
#endif
				  //
				  m_var.canSpeak  =  dlgTalk_canSpeak(  m_var.guiData.param.hMgrTalk  );
				  if  (  m_var.canSpeak  )  ::SetDlgItemText(  hDlg,  IDC_request,  getResStr(  0,  &pQyMc->cusRes,  ID_stopSpeaking  )  );
				  else  ::SetDlgItemText(  hDlg,  IDC_request,  getResStr(  0,  &pQyMc->cusRes,  ID_requestToSpeak  )  );

				  //
				  initForTaskAv(  );


				  }
				  break;

#if  0
			case  IDD_instantAssistant_av_min:  {
				  //
				  idc  =  IDC_request;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iEdge_t  =  rc.top  -  rcDialog.top;
				  m_var.oldLayout.iEdge_l  =  rc.left  -  rcDialog.left;
				  m_var.oldLayout.iW_btn_request  =  rc.right  -  rc.left;
				  m_var.oldLayout.iW_btn  =  rc.right  -  rc.left;
				  m_var.oldLayout.iH_btn  =  rc.bottom  -  rc.top;
				  //

				  //
				  if  (  m_var.ucbConfMgr  )  m_var.oldLayout.iH_talkerList  *=  2;

				  //
				  nCols_btn  =  4;
				  m_var.oldLayout.iW_dlg  =  m_var.oldLayout.iEdge_l  *  2  +  m_var.oldLayout.iW_btn  *  nCols_btn  +  m_var.oldLayout.iX_spacing  *  (  nCols_btn  -  1  );
				  m_var.oldLayout.iH_dlg  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn;
				  nRows_btn  =  1;	//  4;
				  m_var.oldLayout.iW_dlg_more  =  m_var.oldLayout.iW_dlg;
					  
				  int  iH_dlg_more1  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn  +  m_var.oldLayout.iY_spacing  
					  //  +  m_var.oldLayout.iH_usLayoutType  +  m_var.oldLayout.iY_spacing
					  +  m_var.oldLayout.iH_btn  +  m_var.oldLayout.iY_spacing
					  +  m_var.oldLayout.iH_talkerList  +  m_var.oldLayout.iY_spacing
					  +  m_var.oldLayout.iH_status;
				  int  iH_dlg_more2  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn  *  nRows_btn  +  m_var.oldLayout.iY_spacing  *  (  nRows_btn  -  1  );		
				  m_var.oldLayout.iH_dlg_more  =  max(  iH_dlg_more1,  iH_dlg_more2  );
			

				  //
				  m_var.canSpeak  =  dlgTalk_canSpeak(  m_var.guiData.param.hMgrTalk  );
				  if  (  m_var.canSpeak  )  ::SetDlgItemText(  hDlg,  IDC_request,  getResStr(  0,  &pQyMc->cusRes,  ID_stopSpeaking  )  );
				  else  ::SetDlgItemText(  hDlg,  IDC_request,  getResStr(  0,  &pQyMc->cusRes,  ID_requestToSpeak  )  );

				  //
				  initForTaskAv(  );


				  }
				  break;
#endif
			case  IDD_instantAssistant_av_more:  {
				  int  ii  =  0;
				  }
				  break;
			case  IDD_instantAssistant_av_grp_more:  {
				  int  ii  =  0;
				  }
				  break;

			case  IDD_instantAssistant_msg:  {
		      
				  //  idc  =  IDC_BUTTON_close;
				  idc  =  IDC_BUTTON_sendFile;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iEdge_t  =  rc.top  -  rcDialog.top;
				  m_var.oldLayout.iEdge_l  =  rc.left  -  rcDialog.left;
				  m_var.oldLayout.iW_btn  =  rc.right  -  rc.left;
				  m_var.oldLayout.iH_btn  =  rc.bottom  -  rc.top;
				  //
				  m_var.oldLayout.iX_spacing  =  0;
				  //
				  m_var.oldLayout.iY_spacing  =  0;
				  //
				  //  nCols_btn  =  1;  
				  nCols_btn  =  5;  
				  m_var.oldLayout.iW_dlg  =  m_var.oldLayout.iEdge_l  *  2  +  m_var.oldLayout.iW_btn  *  nCols_btn  +  m_var.oldLayout.iX_spacing  *  (  nCols_btn  -  1  );
				  m_var.oldLayout.iH_dlg  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn;
				  //
				  nRows_btn  =  1;
				  m_var.oldLayout.iW_dlg_more  =  m_var.oldLayout.iW_dlg;
				  m_var.oldLayout.iH_dlg_more  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn  *  nRows_btn  +  m_var.oldLayout.iY_spacing  *  (  nRows_btn  -  1  );
				  //
				  }
			      break;
#if  0
			case  IDD_instantAssistant_msg_min:
				  idc  =  IDC_BUTTON_close;
				  hWnd  =  ::GetDlgItem(  hDlg,  idc  );
				  if  (  !hWnd  )  goto  errLabel;
				  ::GetWindowRect(  hWnd,  &rc  );
				  m_var.oldLayout.iEdge_t  =  rc.top  -  rcDialog.top;
				  m_var.oldLayout.iEdge_l  =  rc.left  -  rcDialog.left;
				  m_var.oldLayout.iW_btn  =  rc.right  -  rc.left;
				  m_var.oldLayout.iH_btn  =  rc.bottom  -  rc.top;
				  //
				  m_var.oldLayout.iX_spacing  =  rc.left  -  rcDialog.left  -  m_var.oldLayout.iEdge_l  -  m_var.oldLayout.iW_btn;
				  m_var.oldLayout.iY_spacing  =  0;
				  //
				  nCols_btn  =  2;
				  m_var.oldLayout.iW_dlg  =  m_var.oldLayout.iEdge_l  *  2  +  m_var.oldLayout.iW_btn  *  nCols_btn  +  m_var.oldLayout.iX_spacing  *  (  nCols_btn  -  1  );
				  m_var.oldLayout.iH_dlg  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn;
				  //
				  nRows_btn  =  1;
				  m_var.oldLayout.iW_dlg_more  =  m_var.oldLayout.iW_dlg;
				  m_var.oldLayout.iH_dlg_more  =  m_var.oldLayout.iEdge_t  *  2  +  m_var.oldLayout.iH_btn  *  nRows_btn  +  m_var.oldLayout.iY_spacing  *  (  nRows_btn  -  1  );
				  //
				  break;
#endif
				  //
			default:  {
					  #ifdef  __DEBUG__
							  traceLog(  _T(  "CDlgInstantAssistant::OnInitDialog failed, IDD err"  )  );
							  goto  errLabel;
					  #endif
					  //
					  }
					  break;

					  	
			}
			
}					  

	::SetDlgItemText(  hDlg,  m_var.guiData.iIDC_STATIC_status,  _T(  ""  )  );
	//
	::SetWindowText(  hDlg,  getResStr(  0,  &pQyMc->cusRes,  this->m_var.guiData.param.iIDD  )  );

	//
	if  (  bApp_ts(  pQyMc  )  )  {	//  #ifdef  __APP_qyMc_touchscreen__
	{
		G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )pFuncs->pf_get_g_guiData(  );

		m_var.oldLayout.iEdge_t  *=  pGuiData->fy;
		m_var.oldLayout.iEdge_l  *=  pGuiData->fx;

		m_var.oldLayout.iW_btn_request  *=  pGuiData->fx;
		m_var.oldLayout.iW_btn  *=  pGuiData->fx;
		m_var.oldLayout.iH_btn  *=  pGuiData->fy;
			
		m_var.oldLayout.iX_spacing  *=  pGuiData->fx;
		m_var.oldLayout.iY_spacing  *=  pGuiData->fy;

		m_var.oldLayout.iW_talkerList  *=  pGuiData->fx;
		m_var.oldLayout.iH_talkerList  *=  pGuiData->fy;
#if  0
		m_var.oldLayout.iW_usLayoutType  *=  pGuiData->fx;
		m_var.oldLayout.iH_usLayoutType  *=  pGuiData->fy;		//  2010/12/21
#endif

		m_var.oldLayout.iW_status  *=  pGuiData->fx;
		m_var.oldLayout.iH_status  *=  pGuiData->fy;					//  2010/12/22

		m_var.oldLayout.iW_dlg  *=  pGuiData->fx;
		m_var.oldLayout.iH_dlg  *=  pGuiData->fy;
		m_var.oldLayout.iW_dlg_more  *=  pGuiData->fx;
		m_var.oldLayout.iH_dlg_more  *=  pGuiData->fy;		
		//

	}

	//
	dlgSetFont_instantAssistant(  m_hWnd  );

	}  //  #endif

	//
	SetDlgItemText(IDC_BUTTON_ipc, _T("select camera"));

	//
	SetDlgItemText(IDC_CHECK_audio, _T("audio"));
	SetDlgItemText(IDC_CHECK_video, _T("video"));
	SetDlgItemText(IDC_CHECK_lLayout, _T("L layout"));
	SetDlgItemText(IDC_BUTTON_selOneBig, _T("sel one big"));
	SetDlgItemText(IDC_VIDEORIGHT, _T("VRight"));
	SetDlgItemText(IDC_VIDEOLEFT, _T("VLeft"));
	SetDlgItemText(IDC_VIDEOTOP, _T("VTop"));
	SetDlgItemText(IDC_VIDEOBOTTOM, _T("VBottom"));
	SetDlgItemText(IDC_COORDINATE, _T("sendCoordinate"));
	SetDlgItemText(IDC_CANCELAMP, _T("cancelAmp"));
	//
	//
	if (!isMkfOff(pProcInfo->av.confLayout.taskInfo.iHkStatus_local)) {
		CButton* pBtn_a = (CButton*)GetDlgItem(IDC_CHECK_audio);
		if (pBtn_a) pBtn_a->SetCheck(true);
	}
	if (!isSxtOff(pProcInfo->av.confLayout.taskInfo.iHkStatus_local)) {
		CButton* pBtn_v = (CButton*)GetDlgItem(IDC_CHECK_video);
		if (pBtn_v) pBtn_v->SetCheck(true);
	}




	//
	locateInstantAssistant(  hDlg,  m_var  );
	sizeAllControls_dlgInstantAssistant(  hDlg  );

	#ifdef  __DEBUG__
	#endif

	//  2010/08/29
	m_var.wTimerID  =  ::SetTimer(  hDlg,  1,  1000,  NULL  );

	//  2011/03/25
	m_var.guiData.bInited  =  TRUE;




	//
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		::PostMessage(  hDlg,  WM_CLOSE,  0,  0  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}




LRESULT CDlgInstantAssistant::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	UINT  nHitTest	=	0;
#ifndef  __WINCE__
	nHitTest  =  CDialog::OnNcHitTest(point);
#endif
	//  return (nHitTest==HTCLIENT)?HTCAPTION:nHitTest;
	return  nHitTest;
}

void CDlgInstantAssistant::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages


}

BOOL CDlgInstantAssistant::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(rect);

#if  10
	TRIVERTEX        vert[2] ;
	GRADIENT_RECT    gRect;
	vert [0] .x      = 0;
	vert [0] .y      = 0;
	vert [0] .Red    = 0x5100;
	vert [0] .Green  = 0xf500;
	vert [0] .Blue   = 0x0a00;
	vert [0] .Alpha  = 0x0000;

	vert [1] .x      = rect.right;
	vert [1] .y      = rect.bottom; 
	vert [1] .Red    = 0x0700;
	vert [1] .Green  = 0xf800;
	vert [1] .Blue   = 0xf100;
	vert [1] .Alpha  = 0x0000;

	gRect.UpperLeft  = 0;
	gRect.LowerRight = 1;
	GradientFill(  pDC->m_hDC,vert,2,&gRect,1,GRADIENT_FILL_RECT_H);
#endif


	return  TRUE;

}


void CDlgInstantAssistant::OnBnClickedrequest()
{
	// TODO: Add your control notification handler code here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pDlgTalkVar	=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  m_var.guiData.param.hMgrTalk,  _T(  "dlgIa::OnBnClickedrequest"  )  );
	if  (  !pDlgTalkVar  )  return;

	if  (  !pDlgTalkVar->av.taskInfo.bTaskExists  )  return;

	//  2014/07/26
	CWaitCursor	cur;

	//  2010/09/02
	pFuncs->pf_setCurSharedObjUsr_localAv(  pProcInfo,  pDlgTalkVar->av.iIndex_sharedObj_localAv,  pDlgTalkVar->av.iIndex_usr_localAv  );

	//
	//  requestToSpeak(  !m_var.canSpeak  );
	pFuncs->pf_dlgTalk_requestToSpeak(  m_var.guiData.param.hMgrTalk,  !m_var.canSpeak,  true  );

	//

	//
#ifdef  __DEBUG__
	traceLog(  _T(  "m_var.canSpeak %d. dlgTalk.canSpeak %d"  ),  m_var.canSpeak,  dlgTalk_canSpeak(  m_var.guiData.param.hMgrTalk  )  );
#endif

}



 LRESULT CDlgInstantAssistant::OnQyComm(  WPARAM, LPARAM  lParam  )
{
	int								iErr				=	-1;
	QY_MC						*	pQyMc				=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
		
	CHelp_getDlgTalkVar	help_getDlgTalkVar;			
	
	DLG_TALK_var				*	pDlgTalkVar			=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  m_var.guiData.param.hMgrTalk,  _T(  "dlgIa::OnQyComm"  )  );
	if  (  !pDlgTalkVar  )  return  -1;
	
	QY_WMBUF_COMM				*	pComm				=	(  QY_WMBUF_COMM  *  )lParam;

	//traceLogA(  "CDlgInstantAssistant::OnQyComm enters."  );

	if  (  !m_var.guiData.bInited  )  {
		//  MACRO_qyAssert(  0,  _T(  "DlgInstantAssistant::OnQyComm, can't be called before inited"  )  );
		#ifdef  __DEBUG__
				traceLog(  _T(  "DlgInstantAssistant::OnQyComm, can't be called before inited"  )  );
		#endif
		return  -1;
	}

	if  (  !pDlgTalkVar->av.taskInfo.bTaskExists  )  return  -1;
	QMC_TASK_INFO  *  pTaskInfo  = (QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pDlgTalkVar->av.taskInfo.iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
			
	DLG_TALK_videoConference	*	pVc					=	&pTc->videoConference;

	//
	if  (  pComm  )  {
		switch  (  pComm->uiType  )  {
				case  CONST_qyWmParam_requestToSpeak:  {
					  int  curnItem  =  pComm->u.requestToSpeak.curnItem;
					  unsigned  char  ucbActive  =  FALSE;
					  QY_MESSENGER_ID	idInfo;

					  if  (  !pComm->u.requestToSpeak.bManager  )  {
						  //  requestToSpeak(  pComm->u.requestToSpeak.uiCmd  ==  ID_requestToSpeak  );
						  pFuncs->pf_dlgTalk_requestToSpeak(  m_var.guiData.param.hMgrTalk,  pComm->u.requestToSpeak.uiCmd  ==  ID_requestToSpeak,  true  );
						  break;
					  }

					  if  (  !m_var.ucbConfMgr  )  {
						  #ifdef  __DEBUG__
								  traceLog(  _T(  "Only manager supports this function"  )  );  
						  #endif
						  goto  errLabel;
					  }

					  if  (  pComm->u.requestToSpeak.curnItem  <  0  ||  pComm->u.requestToSpeak.curnItem  >=  m_var.videoConferenceStatus.usCnt  )  {
						  #ifdef  __DEBUG__
								  traceLogA(  "curnItem error: %d",  pComm->u.requestToSpeak.curnItem  );  
						  #endif
						  goto  errLabel;
					  }
					  ucbActive  =  true;//m_var.videoConferenceStatus.mems[curnItem].ucbActive;
					  idInfo.ui64Id  =  m_var.videoConferenceStatus.mems[curnItem].avStream.idInfo.ui64Id;

					  if  (  pComm->u.requestToSpeak.uiCmd  ==  ID_stopSpeaking  )  {
						  pProcInfo->confStarter_requestToSpeak(  m_var.guiData.param.hMgrTalk,  &idInfo,  NULL,  NULL,  FALSE  );
						  if  (  !ucbActive  )  pFuncs->pf_sendVideoConferenceStatus(  m_var.guiData.param.hMgrTalk,  idInfo,  _T(  "ia.stopSpeaking"  )  );
						  else  pFuncs->pf_sendVideoConferenceStatus(  m_var.guiData.param.hMgrTalk,  pDlgTalkVar->addr.idInfo,  _T(  "ia.stopSpeaking"  )  );
						  break;						  
					  }
					  if  (  pComm->u.requestToSpeak.uiCmd  ==  ID_requestToSpeak  )  {
						  pProcInfo->confStarter_requestToSpeak(  m_var.guiData.param.hMgrTalk,  &idInfo,  NULL,  NULL,  TRUE  );
						  if  (  isMemFromActive(  pVc,  &idInfo,  mynull,  NULL  )  )  pFuncs->pf_sendVideoConferenceStatus(  m_var.guiData.param.hMgrTalk,  pDlgTalkVar->addr.idInfo,  _T(  "ia.requestToSpeak"  )  );
						  break;
					  }					  
					  }
					  break;
				default:
						break;
		}
		iErr  =  0;  goto  errLabel;
	}


	fillTalkerList(  );

	iErr  =  0;
errLabel:

	traceLogA(  "CDlgInstantAssistant::OnQyComm leaves with iErr %d",  iErr  );

	return  iErr;
}


void CDlgInstantAssistant::PostNcDestroy()
{
	CDialog::PostNcDestroy();

	// TODO: Add your specialized code here and/or call the base class
	if  (  m_var.bCreated  )  {
		#ifdef  __DEBUG__
				MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				if  (  pProcInfo->cfg.debugStatusInfo.ucbDebugIa  )  {
					traceLogA(  "CDlgInstantAssistant::PostNcDestroy, delete this"  );
				}
		#endif

		delete this;
	}

}

void CDlgInstantAssistant::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	//  CDialog::OnCancel();

	//
	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;



	DLG_TALK_var	*	pCurTalkVar	=	NULL;
	//
	pCurTalkVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  m_var.guiData.param.hCurTalk,  _T(  "dlgIa::OnInitDialog, hShadow"  )  );		  	  

	if  (  pCurTalkVar  )  {
		pCurTalkVar->guiData.ucbShowMore  =  FALSE;
	}
	
	//
	bQuitDlg(  );
}

void CDlgInstantAssistant::OnContextMenu(CWnd* pWnd, CPoint point)
{
#ifdef  __WINCE__
		return;
#else
	// TODO: Add your message handler code here
	CMenu				tmpMenu;
	CMenu			*	tmppPopupMenu		=		NULL;
	//
	int					nPos				=		CONST_resId_popup_instantAssistant;		//  2006/12/31
	//
	QY_MC			*	pQyMc				=		QY_GET_GBUF(  );
	QY_DMITEM		*	pItem;
	//
	unsigned  int		uCmd				=		0;

	QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );
	if  (  !pResMem  )  return;

	RECT				rect;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  m_var.idcList  ),  &rect  );
	if  (  point.x  >  rect.left  &&  point.x  <  rect.right  &&  point.y  >  rect.top  &&  point.y  <  rect.bottom  )  return;

	if  (  !(  tmpMenu.CreatePopupMenu(  )  )  )  goto  errLabel;
	if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_popupMenu  )  )  )  goto  errLabel;
	if  (  !(  pItem  =  qyGetDmItemByType(  pItem,  nPos,  sizeof(  QY_DMITEM  )  )  )  )  goto  errLabel;
	if  (	 makeDynaMenu(  &pQyMc->cusRes,  tmpMenu.m_hMenu,  (  QY_DMITEM  *  )pItem->pData,  NULL,  pQyMc,  NULL  )  )  goto  errLabel;
	tmppPopupMenu  = &tmpMenu;

	if (tmppPopupMenu == NULL)  goto  errLabel;

	uCmd  =  ::TrackPopupMenu(  tmppPopupMenu->m_hMenu,  TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON  |  TPM_NONOTIFY,  point.x, point.y, 0,  this->m_hWnd, NULL);

	traceLogA(  "uCmd %d",  uCmd  );

	switch  (  uCmd  )  {
			case  SC_CLOSE:
				  SendMessage(  WM_SYSCOMMAND,  SC_CLOSE,  0  );
				  break;
			default:
					break;
	}


errLabel:
	return;
#endif
}


void CDlgInstantAssistant::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnLButtonDown(nFlags, point);

	//send WM_NCLBUTTONDOWN information
	//then we can move the window
	PostMessage(WM_NCLBUTTONDOWN,
		HTCAPTION,
		MAKELPARAM(point.x,point.y));

	//
#ifdef  __DEBUG__
		traceLog(  _T(  "dlgia: onLButtonDown"  )  );
#endif

}

void CDlgInstantAssistant::OnNMClicktalkerlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	//
	LPNMITEMACTIVATE pNMLV  =  pNMItemActivate;

	//
	if  (  (  pNMLV->iItem  >= 0  )  )  {
			 m_var.selection.iSel  =  pNMLV->iItem;
		}
	else  m_var.selection.iSel  =  -1;

	//
	if  (  m_var.selection.iSel  >=  0  &&  m_var.selection.iSel  <  m_var.videoConferenceStatus.usCnt  )  {
		m_var.selection.idInfo_sel.ui64Id  =  m_var.videoConferenceStatus.mems[m_var.selection.iSel].avStream.idInfo.ui64Id;
	}

	//
	//refreshBtn_micOff(  );


	//
	*pResult = 0;
}


void CDlgInstantAssistant::OnNMRClicktalkerlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	//  LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	QY_MC			*	pQyMc		=		QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
		FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	QY_MC_SEL			curSel;
	CListCtrl		*	pListCtrl	=		(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
	if  (  !pListCtrl  )  return;
	int					iCurItem;
	QY_EVENTINFO		tmpEventInfo;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;


	DWORD dwPos = GetMessagePos();

	/* Convert the co-ords into a CPoint structure */
	CPoint point( GET_X_LPARAM( dwPos ), GET_Y_LPARAM( dwPos ) ), spt;
	spt = point;
	
	/* Convert to screen co-ords for hittesting */
	pListCtrl->ScreenToClient( &spt );

	UINT test;
	iCurItem = pListCtrl->HitTest( spt, &test );
	
	/* Did the click occur on an item */
	if ( iCurItem < 0 || !( test & ( TVHT_ONITEM | TVHT_ONITEMRIGHT ) ) )  goto errLabel;

	memset(  &curSel,  0,  sizeof(  curSel  )  );
	curSel.type  =  CONST_qySelType_mcDlgLv;
	curSel.u.mcDlgLv.type  =  CONST_qyQueryType_instantAssistantMemList;
	curSel.u.mcDlgLv.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;


	memset(  &tmpEventInfo,  0,  sizeof(  tmpEventInfo  )  );
	tmpEventInfo.type  =  CONST_qyEventType_rClick;
	tmpEventInfo.hWnd  =  this->m_hWnd;
	tmpEventInfo.hFrom  =  pNMHDR->hwndFrom;
	tmpEventInfo.bDlg  =  TRUE;
	tmpEventInfo.click.x  =  point.x;
	tmpEventInfo.click.y  =  point.y;

	
	DLG_TALK_var	*	pDlgTalkVar	=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  m_var.guiData.param.hMgrTalk  );
	if  (  !pDlgTalkVar  )  goto  errLabel;

	if  (  pDlgTalkVar->av.taskInfo.ucbStarter  &&  pDlgTalkVar->av.taskInfo.ucbVideoConference  )  {
		pFuncs->pf_netMc_procTreeEvent(  pQyMc,  &curSel,  &tmpEventInfo  );
	}
		
errLabel:	

	*pResult = 0;
}



void CDlgInstantAssistant::OnLvnItemchangedtalkerlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	//@TN		*pResult = 0;
	// TODO: Add your control notification handler code here

	//traceLog(  _T(  "iSel %d, state %d"  ),  pNMLV->iItem,  pNMLV->uNewState  );

	if  (  (  pNMLV->iItem  >= 0  )
		 &&	 (  pNMLV->uNewState  ==  (  LVIS_SELECTED | LVIS_FOCUSED  )  )  )  {
			 m_var.selection.iSel  =  pNMLV->iItem;
	 }
	else  m_var.selection.iSel  =  -1;

	//
	if  (  m_var.selection.iSel  >=  0  &&  m_var.selection.iSel  <  m_var.videoConferenceStatus.usCnt  )  {
		m_var.selection.idInfo_sel.ui64Id  =  m_var.videoConferenceStatus.mems[m_var.selection.iSel].avStream.idInfo.ui64Id;
	}

	//
	//refreshBtn_micOff(  );


	//
	*pResult = 0;
}



 void CDlgInstantAssistant::OnTimer(UINT_PTR nIDEvent)
{
 #ifndef  __WINCE__

		  MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );		 
		  HWND	hDlg	=	this->m_hWnd;
		  TCHAR				tBuf[255];

		  //		  	
		  CHelp_getDlgTalkVar	help_getDlgTalkVar;
		  
		  if  (  !pProcInfo  )  return;
		  QY_MC  *  pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMc;
		  if  (  !pQyMc  )  return;
	
		  //	
		  DLG_TALK_var	*	pDlgTalkVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  m_var.guiData.param.hMgrTalk,  _T(  "dlgIa::OnInitDialog"  )  );
		  if  (  !pDlgTalkVar  )  goto  errLabel;
		  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pDlgTalkVar->pShadowInfo;
		  if  (  !pShadowMgr  )  goto  errLabel;


		  // TODO: Add your message handler code here and/or call default
		  //if  (  !pShadowMgr->ucbNotAutoHide_instantAssistant  )  
		  {
			  int  maxIdleInMs  =  10000;
			  if  (  GetTickCount(  )  -  m_var.dwTickCnt_lastMouseMove  >  maxIdleInMs
				  &&  GetTickCount  (  )  -  m_var.dwTickCnt_lastLBtnDown  >  maxIdleInMs  )  
			  {
				  //  2017/11/01
				  if  (  IsWindow(  m_var.hTool  )  )  {
					  goto  errLabel;
				  }

				  //
				  #ifdef  __DEBUG__
						  if  (  pProcInfo->cfg.debugStatusInfo.ucbDebugIa  )  {						
							  traceLog(  _T(  "dlgIa: OnTimer: before close"  )  );
						  }
				  #endif
				  ::PostMessage(  hDlg,  WM_CLOSE,  0,  0  );
				  #ifdef  __DEBUG__
						  if  (  pProcInfo->cfg.debugStatusInfo.ucbDebugIa  )  {
							  traceLog(  _T(  "dlgIa: OnTimer: after close"  )  );
						  }
				  #endif
				  return;
			  }
		  }


		  //
		  int  chkAvBtnStatus(  DLG_TALK_var  *  pMgrVar,   CDlgInstantAssistant  *  pDlgIa   );

		  chkAvBtnStatus(  pDlgTalkVar,  this  );


		  //
		  if  (  !bApp_ts(  pQyMc  )  )  {		//  #ifdef  __APP_qyMc__

			  }
		  else  
		  {  //  #ifdef  __APP_qyMc_touchscreen__

			    switch  (  m_var.guiData.param.iIDD  )  {


				  case  IDD_instantAssistant_start:
				  //case  IDD_instantAssistant_start_min:
				  case  IDD_instantAssistant_start_wait:
				  //case  IDD_instantAssistant_start_wait_min:
				  case  IDD_instantAssistant_msg:
				  //case  IDD_instantAssistant_msg_min:
					  {
						
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d, %dkb"  ),  pProcInfo->status.netStat.ins.uiInSpeedInKbps,  pProcInfo->status.netStat.ins.uiOutSpeedInKbps  );
						CWnd	*	pCtrl  =  CWnd::FromHandle(  ::GetDlgItem(  hDlg,  m_var.guiData.iIDC_STATIC_status  )  );
						if  (  !pCtrl  )  goto  errLabel;
						pCtrl->Invalidate(  TRUE  );
						pCtrl->UpdateWindow(  );
						CClientDC	dc_status(  pCtrl  );
						//  dc_status.SetBkMode(  TRANSPARENT  );
						dc_status.SetBkColor(  CONST_bkColor_status  );
						CRect	rect;
						rect.SetRect(  0,  0,  m_var.oldLayout.iW_status,  m_var.oldLayout.iH_status  );
						dc_status.DrawText(  tBuf,  -1,  &rect,  DT_CENTER  |  DT_SINGLELINE  |  DT_VCENTER  );

						}
						break;
				  case  IDD_instantAssistant_av:  
				  //case  IDD_instantAssistant_av_min:
				  case  IDD_instantAssistant_av_more:
				  case  IDD_instantAssistant_av_grp_more:

					  {
					  	//  2010/08/31
					    if  (  !m_var.bTaskAvInited  )  initForTaskAv(  );
						//  2010/09/16
						if  (  m_var.canSpeak  !=  dlgTalk_canSpeak(  m_var.guiData.param.hMgrTalk  )  )  {
							#ifdef  __DEBUG__
									traceLog(  _T(  "ia.timer: m_var.canSpeak != dlgTalk_canSpeak"  )  );
							#endif
							::SendMessage(  this->m_hWnd,  CONST_qyWm_comm,  0,  0  );
							
						}

						//
						{
							_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d, %dkb"  ),  pProcInfo->status.netStat.ins.uiInSpeedInKbps,  pProcInfo->status.netStat.ins.uiOutSpeedInKbps  );
							CWnd	*	pCtrl  =  CWnd::FromHandle(  ::GetDlgItem(  hDlg,  m_var.guiData.iIDC_STATIC_status  )  );
							if  (  !pCtrl  )  goto  errLabel;
							pCtrl->Invalidate(  TRUE  );
							pCtrl->UpdateWindow(  );
							CClientDC	dc_status(  pCtrl  );
							//  dc_status.SetBkMode(  TRANSPARENT  );
							dc_status.SetBkColor(  CONST_bkColor_status  );
							CRect	rect;
							rect.SetRect(  0,  0,  m_var.oldLayout.iW_status,  m_var.oldLayout.iH_status  );
							//dc_status.DrawText(  tBuf,  -1,  &rect,  DT_CENTER  |  DT_SINGLELINE  |  DT_VCENTER  );
							dc_status.DrawText(  tBuf,  -1,  &rect,  DT_LEFT  |  DT_SINGLELINE  |  DT_VCENTER  );
						}
						//
						{
							tBuf[0]  =  0;
							//_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d, %dkb"  ),  pProcInfo->status.netStat.ins.uiInSpeedInKbps,  pProcInfo->status.netStat.ins.uiOutSpeedInKbps  );
							this->getInitiatorDesc(  tBuf,  mycountof(  tBuf  )  );
							CWnd	*	pCtrl  =  CWnd::FromHandle(  ::GetDlgItem(  hDlg,  IDC_STATIC_initiator  )  );
							if  (  !pCtrl  )  goto  errLabel;
							pCtrl->Invalidate(  TRUE  );
							pCtrl->UpdateWindow(  );
							CClientDC	dc_status(  pCtrl  );
							//  dc_status.SetBkMode(  TRANSPARENT  );
							dc_status.SetBkColor(  CONST_bkColor_status  );
							CRect	rect;
							rect.SetRect(  0,  0,  m_var.oldLayout.iW_initiator,  m_var.oldLayout.iH_initiator  );
							//dc_status.DrawText(  tBuf,  -1,  &rect,  DT_CENTER  |  DT_SINGLELINE  |  DT_VCENTER  );
							dc_status.DrawText(  tBuf,  -1,  &rect,  DT_LEFT  |  DT_SINGLELINE  |  DT_VCENTER  );
						}

						}
					    break;					
				  default:
						  #ifdef  __DEBUG__
								  traceLog(  _T(  "CDlgInstantAssistant::OnTimer: unknown  IDD %d"  ),  m_var.guiData.param.iIDD  );
						  #endif
						  break;
		  }
		  }


	 //  CDialog::OnTimer(nIDEvent);
errLabel:
		  return;
 #endif

}



 BOOL CDlgInstantAssistant::PreTranslateMessage(MSG* pMsg)
 {
	 // TODO: Add your specialized code here and/or call the base class
	 switch  (  pMsg->message  )  {
			case  WM_MOUSEMOVE:
			case  WM_LBUTTONDOWN:
			case  WM_RBUTTONDOWN:  {
				  POINT	point;	
				  long  lParam  =  pMsg->lParam;
				  point.x = GET_X_LPARAM(lParam); 
				  point.y = GET_Y_LPARAM(lParam);
				  //
				  ::MapWindowPoints(  pMsg->hwnd,  NULL,  &point,  1  );

				  #ifdef  __DEBUG__
						  //  traceLog(  _T(  "ia::PreTranslateMessage, message %d"  ),  pMsg->message  );
				  #endif
				  #if  1  //  def  __APP_qyMc__
						  if  (  pMsg->message  ==  WM_LBUTTONDOWN  )  {	//  2014/12/23
							  m_var.dwTickCnt_lastLBtnDown  =  GetTickCount(  );
						  }
				  #endif


				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  if  (  pProcInfo->status.param_viewInstantAssistant.xPos_screen  ==  point.x  &&  pProcInfo->status.param_viewInstantAssistant.yPos_screen  ==  point.y  )  break;

				  pProcInfo->status.param_viewInstantAssistant.xPos_screen  =  point.x;
				  pProcInfo->status.param_viewInstantAssistant.yPos_screen  =  point.y;

				  //  只有鼠标位置移动时，才能认为是鼠标真的移动了
				  m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );				  
				  }
				  break;
			default:
					break;
	}

	 //
	 return CDialog::PreTranslateMessage(pMsg);
 }

 void CDlgInstantAssistant::OnDestroy()
 {
	 //
	 //  2013/07/04
	 if (m_var.pm_LargeImageList) {
		 myImageList_free(m_var.pm_LargeImageList);
		 m_var.pm_LargeImageList = NULL;
	 }
	 if (m_var.pm_SmallImageList) {
		 myImageList_free(m_var.pm_SmallImageList);
		 m_var.pm_SmallImageList = NULL;
	 }

	 //
	 CDialog::OnDestroy();

	 // TODO: Add your message handler code here
	 sdwTickCnt_close_instantAssistant  =  GetTickCount(  );
 }

 void CDlgInstantAssistant::OnClose()
 {
	 // TODO: Add your message handler code here and/or call default
	 //  CDialog::OnClose();
	 bQuitDlg(  );
 }

 HBRUSH CDlgInstantAssistant::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
 {
	 HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	 // TODO:  Change any attributes of the DC here
	 if  (  m_var.guiData.iIDC_STATIC_status  )  {
		  if  (  pWnd->GetDlgCtrlID(  )  ==  m_var.guiData.iIDC_STATIC_status  )  {
			  return  (  HBRUSH  )this->m_brush_bk_status;
		  }
	  }
	 if  (  pWnd->GetDlgCtrlID()  ==  IDC_STATIC_initiator  )  {
		  return  (  HBRUSH  )this->m_brush_bk_status;
	 }


	 // TODO:  Return a different brush if the default is not desired
	 return hbr;
 }

 void CDlgInstantAssistant::OnBnClickedButtonjoininbgwall()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_joinInBgWall  );
}

 void CDlgInstantAssistant::OnBnClickedButtonmsgbox()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_msgBox  );

}

 void CDlgInstantAssistant::OnBnClickedButtonsendfile()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_sendFile  );

}

 void CDlgInstantAssistant::OnBnClickedButtonfullscreen()
{
	// TODO: Add your control notification handler code here
#ifndef  __APP_qyMc_touchscreen__
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_fullScreen  );
#endif

}

void CDlgInstantAssistant::OnBnClickedButtonmore()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_more  );

}

#endif



//
__declspec(  dllexport  )  int  dlgTalk_OnCmd_shareScreen(  HWND  hCurTalk,  BOOL  bRemoteAssist  )
{
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );

	//
	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
	DLG_TALK_var	*	pCurVar		=	NULL;

	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	HWND  hMgr  =  NULL;
	DLG_TALK_var  *  pMgrVar  =  NULL;

	//
	pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_cur.getVar(  hCurTalk  );
	if  (  !pCurVar  )  return  -1;

	//
	hMgr  =  hCurTalk;
	pMgrVar  =  pCurVar;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
		if  (  !pShadow  )  goto  errLabel;
		hMgr  =  pShadow->hMgr;
		pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		if  (  !pMgrVar  )  goto  errLabel;
	}

	TCHAR  tBuf[128]  =  _T(  ""  );

	//
	MIS_MSG_TASK	*	pMsgTask	=	pFuncs->pf_findTaskInProcessQ(  pMgrVar,  0,  0,  TRUE  );
	if  (  !pMsgTask  )  {
					  //
					  BOOL				bNoPrompt		=	bNoPrompt_selectAvCompressor(  CONST_capType_screen,  0  );
					  
					  //  2017/08/24
					  if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_bjyz  )  {
						  bNoPrompt  =  TRUE;						  
						  //
						  if  (  pMgrVar->av.taskInfo.bTaskExists
							  &&  pMgrVar->av.taskInfo.usConfType  ==  CONST_usConfType_consult  )
						  {
							  HWND  tmphShadow  =  NULL;
							  getTalker_inputShadow(  hCurTalk,  &tmphShadow  );
							  //
							  CHelp_getDlgTalkVar  help_tmp;
							  DLG_TALK_var  *  pTmpVar  =  (  DLG_TALK_var  *  )help_tmp.getVar(  tmphShadow  );
							  if  (  !pTmpVar  )  goto  errLabel;
							  //
							  if  (  pTmpVar->m_bFullScreen  )  {
								  //showNotification(  0,  0,  0,  0,  0,  0,  _T(  "FullScreen"  )  );
							  }
							  //
							  PostMessage(tmphShadow, WM_SYSCOMMAND, SC_MINIMIZE, 0);
						  }
					  }
					  
					  //  2014/05/05
					  if  (  !bNoPrompt  )  {		
						  if  (  pProcInfo->viewDlgSelectAvCompressor(  hCurTalk,  pMgrVar->addr.idInfo, CONST_capType_screen,  0,  FALSE, FALSE,  0   )  !=  IDOK  )  goto  errLabel;
					  }
					  //
					  pFuncs->pf_toSelectRegion1(  hMgr,  TRUE,  bRemoteAssist,  FALSE,  0,  -1  );

					  //
					  #ifdef  __DEBUG__
							  pMgrVar->av.taskInfo.bDbgFlg  =  FALSE;
					  #endif
					  }				  
	else  {
					    PARAM_dlgTalk_procTask  param;				  
						memset(  &param,  0,  sizeof(  param  )  );

					    pFuncs->pf_dlgTalk_procTask1(  hMgr,  pMsgTask->iTaskId,  CONST_imOp_send_cancel,  NULL,  &param  );		

						//
						if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_bjyz  )  {
						  //
						  if  (  pMgrVar->av.taskInfo.bTaskExists
							  &&  pMgrVar->av.taskInfo.usConfType  ==  CONST_usConfType_consult  )
						  {
							  HWND  tmphShadow  =  NULL;
							  getTalker_inputShadow(  hCurTalk,  &tmphShadow  );
							  //
							  CHelp_getDlgTalkVar  help_tmp;
							  DLG_TALK_var  *  pTmpVar  =  (  DLG_TALK_var  *  )help_tmp.getVar(  tmphShadow  );
							  if  (  !pTmpVar  )  goto  errLabel;
							  //
							  if  (  pTmpVar->m_bFullScreen  )  {
								  //
								  SendMessageTimeout(  tmphShadow,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0,  0,  1000,  NULL  );								  
							  }
							  //								
							  PostMessage(tmphShadow, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
						  }
						}

						//
						#ifdef  __DEBUG__
								pMgrVar->av.taskInfo.bDbgFlg  =  TRUE;
								//
								{
								HWND  tmphShadow  =  NULL;
							    getTalker_inputShadow(  hCurTalk,  &tmphShadow  );
								CHelp_getDlgTalkVar  help_getDlgTalkVar;
								DLG_TALK_var  *  pCurVar =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  tmphShadow  );
								if  (  !pCurVar  )  goto  errLabel;
								int  ii  =  0;
								ii  =  pCurVar->av.peerZone.images.head.usCnt;
								}
						#endif
				  
	}
	
	//
	iErr  =  0;


errLabel:
	return  iErr;

}


//



 //  0表示处理完毕，-1表示出错，1表示没有处理
 int  dlgInstantAssistant_OnCmd(  HWND  hDlg,  DLG_instantAssistant_var  &  m_var,  WORD  wID  )  
{
	int		iErr	=	-1;
	QY_MC			*	pQyMc			=   QY_GET_GBUF(  );
	//
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	//
#ifdef  __SUPPORT_dlgInstantAssistant_mfc__
	CDlgInstantAssistant	*	pDlg	=	(  CDlgInstantAssistant  *  )CWnd::FromHandle(  hDlg  );
#else
	CDlgInstantAssistant	*	pDlg	=	(  CDlgInstantAssistant  *  )CQyWnd::FromHandle(  hDlg  );
#endif
	if  (  !pDlg  )  return  -1;
	HWND	hDlgTalk	=	m_var.guiData.param.hMgrTalk;
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pDlgTalkVar	=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pDlgTalkVar  )  return  -1;
	if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  {
		return  -1;
	}
	HWND  hMgr  =  hDlgTalk;
	DLG_TALK_var  *  pMgrVar =  pDlgTalkVar;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pDlgTalkVar->pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;

	//
	HWND				hCurTalk	=	hDlgTalk;
	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
	DLG_TALK_var	*	pCurVar		=	pDlgTalkVar;
	//
	hCurTalk  =  m_var.guiData.param.hCurTalk;
	pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_cur.getVar(  hCurTalk  );
	if  (  !pCurVar  )  return  -1;
	TCHAR  tBuf[128]  =  _T(  ""  );

	//  2013/02/17
	CQySyncFlg	syncFlg;
	if  (  syncFlg.sync(  &m_var.syncFlgs.bInSequence  )  )  return  -1;
	
	//
	switch  (  wID  )  {
			case  IDC_request:			
				  pDlg->OnBnClickedrequest(  );
				  break;
			case  IDC_BUTTON_joinInBgWall:{

				   //
				   //
				   if  (  IsWindow(  m_var.hTool  )  )  {
					   SendMessageTimeout(  m_var.hTool,  WM_CLOSE,  0,  0,  0,  1000,  NULL  );
					   if  (  IsWindow(  m_var.hTool  )  )  goto  errLabel;
				   }

				   //
				   viewDlgCfgBgWall(  hDlg,  hDlgTalk,  &m_var.hTool  );

				   //
				   //PostMessage(  hDlg,  WM_CLOSE,  0,  0  );
				  }				  
				  break;
			case  IDC_BUTTON_msgBox:

				  //
				  PostMessage(  hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_msgBox,  0  ),  0  );

				  //  2015/06/11
				  //PostMessage(  hDlg,  WM_CLOSE,  0,  0  );

				  break;
			case  IDC_BUTTON_sendFile:  //  2015/06/15
				  //
				  PostMessage(  hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_sendFile,  0  ),  0  );
				  //
				  //  2015/06/11
				  PostMessage(  hDlg,  WM_CLOSE,  0,  0  );

				  break;

		#if  1  //  ndef  __APP_qyMc_touchscreen__
			case  IDC_BUTTON_fullScreen:
				  if  (  bApp_ts(  pQyMc  )  )  {
					  PostMessage(  m_var.guiData.hParent,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );
					  break;
				  }

				  PostMessage(  hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );

				  break;
			case  IDC_BUTTON_showDlgMenu:			//  2012/04/09
				  if  (  bApp_ts(  pQyMc  )  )  goto  errLabel;

				  //
				  PostMessage(  hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_showDlgMenu,  0  ),  0  );				  

				  break;
		#endif
			case  IDC_BUTTON_av:
				  if  (  !pDlgTalkVar->av.taskInfo.bTaskExists  )  {
					  //
					  DLG_TALK_var  *  pMgrVar  =  pDlgTalkVar;						
					  if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;

					  int  iAvBtnStatus  =  getAvBtnStatus(  pMgrVar  );
					  //
					  if  (  iAvBtnStatus  ==  CONST_avBtnStatus_re_accept  )  {
						
						  //
						  int  iTaskId  =  pMgrVar->guiData.av.canceledTask_av.iTaskId;

						  dlgTalk_re_acceptTask(  hDlgTalk,  iTaskId  );  
						  
						  }						  
					  else  {
						    //
						    PostMessage(  m_var.guiData.param.hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_startAvCall,  0  ),  0  );				  
					  }
					  }
				  else  {
					    int  iTaskId  =  pDlgTalkVar->guiData.av.iTaskId;
						int  iStatus  =  pDlgTalkVar->guiData.av.iStatus;				
						switch  (  iStatus  )  {
								case  CONST_imTaskStatus_req:
								case  CONST_imTaskStatus_acceptedByReceiver:
								case  CONST_imTaskStatus_dualByReceiver:  {
									  G_guiData_qyMc	*	pGuiData	=	pFuncs->pf_get_g_guiData(  );
									  PF_MessageBox	pf  =  (  PF_MessageBox  )pGuiData->pf_MessageBox;
									  MACRO_qyAssert(  pf,  _T(  "pf_MessageBox is null"  )  );
									  if  (  pf(  hDlg,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_areYouSure  ),  _T(  "www.qycx.com"  ),  MB_OKCANCEL  )  !=  IDOK  )  goto  errLabel;

									  PARAM_dlgTalk_procTask  param;
									  memset(  &param,  0,  sizeof(  param  )  );
									  pFuncs->pf_dlgTalk_procTask1(  hDlgTalk,  iTaskId,  CONST_imOp_send_cancel,  NULL,  &param  );  
									  }
									  break;
								case  CONST_imTaskStatus_applyToRecv:
								case  CONST_imTaskStatus_waitToRecv:
								case  CONST_imTaskStatus_resp:  {
									  G_guiData_qyMc	*	pGuiData	=	pFuncs->pf_get_g_guiData(  );
									  PF_MessageBox	pf  =  (  PF_MessageBox  )pGuiData->pf_MessageBox;
									  MACRO_qyAssert(  pf,  _T(  "pf_MessageBox is null"  )  );
									  if  (  pf(  hDlg,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_areYouSure  ),  _T(  "www.qycx.com"  ),  MB_OKCANCEL  )  !=  IDOK  )  goto  errLabel;

									  PARAM_dlgTalk_procTask  param;
									  memset(  &param,  0,  sizeof(  param  )  );
									  pFuncs->pf_dlgTalk_procTask1(  hDlgTalk,  iTaskId,  CONST_imOp_recv_cancel,  NULL,  &param  );  								    						    
									  }
									  break;
								default:
									    break;
					  
						}						
				  }
				  //  2013/02/23
				  PostMessage(  hDlg,  WM_CLOSE,  0,  0  );
				  break;
			case  IDC_BUTTON_av_accept:  {
				  PARAM_dlgTalk_procTask  param;
				  memset(  &param,  0,  sizeof(  param  )  );
				  param.bManualCmd  =  TRUE;		//  2017/02/12
				  //pFuncs->pf_dlgTalk_procTask1(  hDlgTalk,  pDlgTalkVar->guiData.av.iTaskId,  CONST_imOp_dual_permit,  NULL,  &param  );  
				  pFuncs->pf_dlgTalk_procTask1(  hCurTalk,  pDlgTalkVar->guiData.av.iTaskId,  CONST_imOp_dual_permit,  NULL,  &param  );  
				  //
				  //  sizeAllControls_dlgInstantAssistant(  hDlg  );		//  2013/03/08
				  PostMessage(  hDlg,  WM_CLOSE,  0,  0  );
				  //  2013/04/08
				  pFuncs->pf_askToRefreshLayout_mgr(  hDlgTalk  );
				  }
				  break;
			case  IDC_BUTTON_av_deny:  {
				  PARAM_dlgTalk_procTask  param;
				  memset(  &param,  0,  sizeof(  param  )  );				  
				  pFuncs->pf_dlgTalk_procTask1(  hDlgTalk,  pDlgTalkVar->guiData.av.iTaskId,  CONST_imOp_recv_deny,  NULL,  &param  );  
				  sizeAllControls_dlgInstantAssistant(  hDlg  );		//  2013/03/08
				  }
				  break;
			case  IDC_BUTTON_shareScreen:  {
				  //
				  if  (  !pMgrVar->av.taskInfo.bTaskExists  )  {
					  //  qyMessageBox(  hDlg,  _T(  "Please start meeting, before sharing screen"  ),  _T(  "qyMessenger"  ),  MB_OK,  5,  NULL  );
					  qyMessageBox(  hDlg,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_startMeetingFirstly  ),  _T(  "qyMessenger"  ),  MB_OK,  5,  NULL  );
					  break;
				  }

				  //
				  if (pQyMc->appParams.bUse_forTest_mediaDivceAsScreen) {
					  
					  //
					  int iMenuId = ID_startShareMediaDevice_unresizable;

					  //
					  if (!pShadowMgr->resourcesInfo.info_send.nMediaFiles_unresizable) {						  

						  //	
						  TCHAR  tBuf[128];
						  if (isActiveMemsFull(pMgrVar->av.taskInfo.iTaskId, false))
						  {
							  _sntprintf(tBuf, mycountof(tBuf), _T("too many speakers. you cant share screen now"));
							  showNotification(0, 0, 0, 0, 0, 0, tBuf);
							  goto  errLabel;
						  }

						  //
						  TCHAR  tDev[256];  tDev[0] = 0;
						  getCfgValByNameT(pQyMc->cfg.smCfgFile, CONST_cfgName_sm_devAsScreen, tDev, mycountof(tDev));
						  tTrim(tDev);
						  

						  //
						  dlgTalk_shareMediaDevice(hDlgTalk, 0, CONST_subCapType_unresizable,tDev);

					  }
					  else {
						  PARAM_dlgTalk_procTask  param;
						  memset(&param, 0, sizeof(param));

						  //pFuncs->pf_dlgTalk_procTask1(  hDlgTalk,  pMsgTask->iTaskId,  CONST_imOp_send_cancel,  NULL,  &param  );						
						  pFuncs->pf_dlgTalk_procCmd(hDlgTalk, iMenuId, 0, CONST_imOp_send_cancel, NULL, &param);
					  }


					  //
					  break;
				  }


				  //
				  if  (  !pShadowMgr->resourcesInfo.info_send.nScreens  )  {

					  //
					  
					  //	
					  TCHAR  tBuf[128];
					  if  (  isActiveMemsFull(  pMgrVar->av.taskInfo.iTaskId,false  )  )
					  {
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "too many speakers. you cant share screen now"  )  );
						  showNotification(  0,  0,  0,  0,  0,  0,  tBuf  );
						  goto  errLabel;
					  }

					  //
					  BOOL				bNoPrompt		=	bNoPrompt_selectAvCompressor(  CONST_capType_screen,  0  );				  	
					  //  2014/05/05
					  if  (  !bNoPrompt  )  {		
						  //if  (  pProcInfo->viewDlgSelectAvCompressor(  hCurTalk,  pMgrVar->addr.idInfo, CONST_capType_screen,  0,  FALSE, FALSE,  0   )  !=  IDOK  )  goto  errLabel;
					  }
					  //
					  pFuncs->pf_toSelectRegion1(  hDlgTalk,  TRUE,  FALSE,  FALSE,  0,  -1  );
					  //  2019/05/06
					  PostMessage(  hCurTalk,  WM_SYSCOMMAND,  SC_MINIMIZE,  NULL  );
					  PostMessage(  pQyMc->gui.hGuiWnd,  WM_CLOSE,  0,  NULL  );
					  }
				  else  {
					    PARAM_dlgTalk_procTask  param;				  
						memset(  &param,  0,  sizeof(  param  )  );

					    //pFuncs->pf_dlgTalk_procTask1(  hDlgTalk,  pMsgTask->iTaskId,  CONST_imOp_send_cancel,  NULL,  &param  );						
						pFuncs->pf_dlgTalk_procCmd(  hDlgTalk,  ID_menuItemIdc_shareFullScreen,  0,  CONST_imOp_send_cancel,  NULL,  &param  );
				  }

				  //
				  }
				  break;
			case  IDC_BUTTON_close:
				  //  2015/06/05
				  //
				  //  PostMessage(  hDlgTalk,  WM_CLOSE,  0,  0  );
				  PostMessage(  hCurTalk,  WM_CLOSE,  0,  0  );
				  break;
			case  IDC_BUTTON_closeAndClean:	//  2012/05/16
				  PostMessage(  hDlgTalk,  WM_CLOSE,  0,  0  );				  
				  break;
			case  IDC_BUTTON_more:
				  //  pDlgTalkVar->guiData.ucbShowMore  =  !pDlgTalkVar->guiData.ucbShowMore;
				  pCurVar->guiData.ucbShowMore  =  !pCurVar->guiData.ucbShowMore;
#if  0
				  RECT	rc;
				  GetWindowRect(  hDlg,  &rc  );
				  int  iW_dlg,  iH_dlg;
				  //  if  (  pDlgTalkVar->guiData.ucbShowMore  )  
				  if  (  pCurVar->guiData.ucbShowMore  )  
				  {
					  //  rc.left  -=  m_var.oldLayout.iW_dlg;
					  iW_dlg  =  m_var.oldLayout.iW_dlg_more;
					  iH_dlg  =  m_var.oldLayout.iH_dlg_more;						
					  }
				  else  {
					    //  rc.left  +=  m_var.oldLayout.iW_dlg;
					    iW_dlg  =  m_var.oldLayout.iW_dlg;
						iH_dlg  =  m_var.oldLayout.iH_dlg;						
				  }
				  if  (  !bApp_ts(  pQyMc  )  )  {  //  #ifdef  __APP_qyMc__
						   rc.left  =  rc.right  -  iW_dlg;
				  }		//  #endif

				  MoveWindow(  hDlg,  rc.left,  rc.top,  iW_dlg,  iH_dlg,  TRUE  );
				  sizeAllControls_dlgInstantAssistant(  hDlg  );
#endif
				  //	
				  PostMessage(  hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_showMoreIa,  0  ),  0  );
				  PostMessage(  hDlg,  WM_CLOSE,  0,  0  );
				  break;

			case  IDC_BUTTON_selAvCompressor:				//  2014/04/08
				  PostMessage(  hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_selAvCompressor,  0  ),  0  );
				  PostMessage(  hDlg,  WM_CLOSE,  0,  0  );	//  2014/04/09
				  break;
			case  IDC_BUTTON_subtitles:				//  2013/04/05
				  PostMessage(  hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_subtitles,  0  ),  0  );
				  break;
			case  IDC_BUTTON_offlineRes:  //  2015/08/01
				  PostMessage(  hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_offlineRes,  0  ),  0  );
				  PostMessage(  hDlg,  WM_CLOSE,  0,  0  );
				  break;
			case  IDC_BUTTON_remoteVideo:			//  2013/02/13
				  PostMessage(  hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_remoteVideo,  0  ),  0  );
				  break;
			case  IDC_BUTTON_ptzPanel:			//  2013/02/13
#if 0
				  if  (  !canRemotePtzControl(  pProcInfo  )  )  {
					  myMessageBox(   NULL,  _T(  "Remote ptz control is not supported if no remote video exists"  ),  _T(  "www.qycx.com"  ),  MB_OK  );
					  goto  errLabel;
				  }
#endif
				  //
				  PostMessage(  hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_remotePtzControl,  0  ),  0  );
				  break;
			case  IDC_BUTTON_rule:  {
				#if  0
				  CDlgImObjRule	dlg;
				  if  (  !dlg.bSetDlgInfo(  _T(  ""  ),  &pDlgTalkVar->addr.idInfo  )  )  goto  errLabel;
				  dlg.DoModal(  );
				#endif
				  PostMessage(  hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_rule,  0  ),  0  );
				  }				  
				  break;
			case  IDC_BUTTON_shareMediaFile:  {		//  2011/07/12
				  PostMessage(  hDlgTalk,  WM_COMMAND,  MAKEWPARAM(  ID_startShareMediaFile,  0  ),  0  );
				  }
				  break;
			case  IDC_BUTTON_layoutType:  {		//  2013/06/24
				  PostMessage(  hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_layoutType,  0  ),  0  );				  
				  //
				  PostMessage(  hDlg,  WM_CLOSE,  0,  0  );
				  }
				  break;
			case  IDC_BUTTON_ipc: {
				  PostMessage(  hCurTalk,  WM_COMMAND,  MAKEWPARAM(ID_ipc,0),0);
				  //
				  PostMessage(hDlg, WM_CLOSE, 0, 0);
				  }
				  break;
			case  IDC_BUTTON_selOneBig: {
				  PostMessage(hCurTalk, WM_COMMAND, MAKEWPARAM(ID_selOneBig, 0), 0);
				  //
				  PostMessage(hDlg, WM_CLOSE, 0, 0);
				  }
				  break;
			case  IDC_BUTTON_menuBar:  //  2015/06/06
				  if  (  !bApp_ts_3d(  pQyMc  )  )  goto  errLabel;
				  //
				  if  (  !pProcInfo->bUse_imObjView_as_guiWnd(  )  )  {
					  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
					  if  (  !pGBuf  )  goto  errLabel;
					  if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  goto  errLabel;
					  PostMessage(  pGBuf->hWall_d3d,  WM_COMMAND,  MAKEWPARAM(  ID_showMenu_wallsBar,  0  ),  0  );
				  }
				  //
				  PostMessage(  hDlg,  WM_CLOSE,  0,  0  );				  
				  break;
			default:
					iErr  =  1;
					goto  errLabel;
					break;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}



void CDlgInstantAssistant::OnBnClickedButtonav()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_av  );
	//
#ifdef  __DEBUG__
	traceLog(  _T(  "av"  )  );
#endif

}

void CDlgInstantAssistant::OnBnClickedButtonavaccept()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_av_accept  );
}

void CDlgInstantAssistant::OnBnClickedButtonavdeny()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_av_deny  );
	//
#ifdef  __DEBUG__
	traceLog(  _T(  "deny"  )  );
#endif
}

void CDlgInstantAssistant::OnBnClickedButtonsharescreen()
{
	// TODO: Add your control notification handler code here

	//
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_shareScreen  );
}


void CDlgInstantAssistant::OnBnClickedButtonnonexclusive()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_nonexclusive  );
}


void CDlgInstantAssistant::OnBnClickedButtonclose()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_close  );

}

void CDlgInstantAssistant::OnBnClickedButtonrule()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_rule  );

}

#if  0
void CDlgInstantAssistant::OnBnClickedButtonmsg()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_msg  );
}
#endif

void CDlgInstantAssistant::OnBnClickedButtonsharemediafile()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_shareMediaFile  );
}


#ifndef  __APP_qyMc_touchscreen__

void CDlgInstantAssistant::OnBnClickedButtonshowdlgmenu()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_showDlgMenu  );

}
#endif

void CDlgInstantAssistant::OnBnClickedButtonselAvCompressor()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_selAvCompressor  );
}

void CDlgInstantAssistant::OnBnClickedButtonsubtitles()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_subtitles  );
}


void CDlgInstantAssistant::OnBnClickedButtonofflineres()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_offlineRes  );

}

void CDlgInstantAssistant::OnBnClickedButtonremoteVideo()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_remoteVideo  );

}
void CDlgInstantAssistant::OnBnClickedButtonptzPanel()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_ptzPanel  );

}
void CDlgInstantAssistant::OnBnClickedButtoncloseandclean()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_closeAndClean  );
}

void CDlgInstantAssistant::OnBnClickedButtonlayouttype()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_layoutType  );
}


#if  0
void iiCDlgInstantAssistant::OnBnClickedButtonmicOff()
{
	// TODO: Add your control notification handler code here
		int								iErr				=	-1;
	QY_MC						*	pQyMc				=	QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
		
	CHelp_getDlgTalkVar	help_getDlgTalkVar;			
	
	DLG_TALK_var				*	pDlgTalkVar			=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  m_var.guiData.param.hDlgTalk,  _T(  "dlgIa::OnQyComm"  )  );
	if  (  !pDlgTalkVar  )  return;

	DLG_TALK_videoConference	*	pVc					=	&pDlgTalkVar->videoConference;

	
	int  curnItem  =  m_var.selection.iSel;
	unsigned  char  ucbActive  =  FALSE;
	QY_MESSENGER_ID	idInfo;
	

	if  (  !m_var.ucbConfMgr  )  {	
		traceLog(  _T(  "Only manager supports this function"  )  );  
		goto  errLabel;		
	}
						 
	if  (  curnItem  <  0  ||  curnItem  >=  m_var.videoConferenceStatus.usCnt  )  {	
		traceLogA(  "curnItem error: %d",  curnItem  );  
		goto  errLabel;		
	}

	ucbActive  =  m_var.videoConferenceStatus.mems[curnItem].ucbActive;	
	idInfo.ui64Id  =  m_var.videoConferenceStatus.mems[curnItem].mem.idInfo.ui64Id;
	if  (  idInfo.ui64Id  !=  m_var.selection.idInfo_sel.ui64Id  )  goto  errLabel;

	unsigned  int  uiCmd  =  ID_stopSpeaking;//  ucbActive  ?  ID_stopSpeaking  :  ID_requestToSpeak;

	//
	//  2015/07/30
	if  (  !pDlgTalkVar->av.taskInfo.ucbStarter  )  {
		pFuncs->pf_requestToSpeak_videoConferenceMgr(  m_var.guiData.param.hDlgTalk,  &idInfo,  FALSE  );
		iErr  =  0;  goto  errLabel;
	}

	//
	if  (  uiCmd  ==  ID_stopSpeaking  )  {
	
		pFuncs->pf_requestToSpeak_videoConferenceStarter(  m_var.guiData.param.hDlgTalk,  &idInfo,  FALSE  );
						  
		if  (  !ucbActive  )  pFuncs->pf_sendVideoConferenceStatus(  m_var.guiData.param.hDlgTalk,  &idInfo  );		
		else  pFuncs->pf_sendVideoConferenceStatus(  m_var.guiData.param.hDlgTalk,  &pDlgTalkVar->addr.idInfo  );

		iErr  =  0;  goto  errLabel;					  					  
	}
					  
					  
	iErr  =  0;

errLabel:
				
	return;
}


void iiCDlgInstantAssistant::OnBnClickedButtonmicon()
{
	// TODO: Add your control notification handler code here
		int								iErr				=	-1;
	QY_MC						*	pQyMc				=	QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
		
	CHelp_getDlgTalkVar	help_getDlgTalkVar;			
	
	DLG_TALK_var				*	pDlgTalkVar			=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  m_var.guiData.param.hDlgTalk,  _T(  "dlgIa::OnQyComm"  )  );
	if  (  !pDlgTalkVar  )  return;

	DLG_TALK_videoConference	*	pVc					=	&pDlgTalkVar->videoConference;

	
	int  curnItem  =  m_var.selection.iSel;
	unsigned  char  ucbActive  =  FALSE;
	QY_MESSENGER_ID	idInfo;
	

	if  (  !m_var.ucbConfMgr  )  {	
		traceLog(  _T(  "Only manager supports this function"  )  );  
		goto  errLabel;		
	}
						 
	if  (  curnItem  <  0  ||  curnItem  >=  m_var.videoConferenceStatus.usCnt  )  {	
		traceLogA(  "curnItem error: %d",  curnItem  );  
		goto  errLabel;		
	}

	ucbActive  =  m_var.videoConferenceStatus.mems[curnItem].ucbActive;	
	idInfo.ui64Id  =  m_var.videoConferenceStatus.mems[curnItem].mem.idInfo.ui64Id;
	if  (  idInfo.ui64Id  !=  m_var.selection.idInfo_sel.ui64Id  )  goto  errLabel;

	unsigned  int  uiCmd  =  ID_requestToSpeak;	//  ucbActive  ?  ID_stopSpeaking  :  ID_requestToSpeak;

	//  2015/07/30
	if  (  !pDlgTalkVar->av.taskInfo.ucbStarter  )  {
		pFuncs->pf_requestToSpeak_videoConferenceMgr(  m_var.guiData.param.hDlgTalk,  &idInfo,  TRUE  );
		iErr  =  0;  goto  errLabel;
	}
	
	//
	if  (  uiCmd  ==  ID_requestToSpeak  )  {			
		pFuncs->pf_requestToSpeak_videoConferenceStarter(  m_var.guiData.param.hDlgTalk,  &idInfo,  TRUE  );
		if  (  isMemFromActive(  pVc,  &idInfo,  NULL  )  )  pFuncs->pf_sendVideoConferenceStatus(  m_var.guiData.param.hDlgTalk,  &pDlgTalkVar->addr.idInfo  );
		iErr  =  0;  goto  errLabel;					  
	}					  
					  
	iErr  =  0;

errLabel:
				
	return;
}
#endif


//
void CDlgInstantAssistant::OnBnClickedButtonmenubar()
{
	// TODO: Add your control notification handler code here
	dlgInstantAssistant_OnCmd(  m_hWnd,  m_var,  IDC_BUTTON_menuBar  );

}






void CDlgInstantAssistant::OnBnClickedButtonmemlist()
{
	// TODO: Add your control notification handler code here
	CHelp_getDlgTalkVar   help_getDlgTalkVar;
	DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  m_var.guiData.param.hCurTalk  );
	if  (  !pCurVar  )  return;
	if  (  pCurVar->guiData.ucbShowImGrpMems  )  {	
		::PostMessage(  m_var.guiData.param.hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_ucbHideImGrpMems,  0  ),  0  );
	}
	else  {
		::PostMessage(  m_var.guiData.param.hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_ucbShowImGrpMems,  0  ),  0  );
	}



}


void CDlgInstantAssistant::OnBnClickedButtonstat()
{
	// TODO: Add your control notification handler code here
	//
		int  iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;

	//
	TCHAR  *  pDir  =  NULL;
	TCHAR  fileName[MAX_PATH]  =  _T(  ""  );


	_sntprintf(  fileName,  mycountof(  fileName  ),  _T(  "%s%s"  ),  pProcInfo->cfg.policy.dirToSaveMsg,  _T(  CONST_subDir_conf  )  );

	//
	pDir  =  fileName;
	
	//
	if  (  bDir(  pDir  )  )  {		//  
		ShellExecute(  NULL,  _T(  "open"  ),  pDir,  _T(  ""  ),  NULL,  SW_SHOW  );			
	}

	iErr  =  0;

errLabel:
	return;

}


void CDlgInstantAssistant::OnBnClickedButton2ndscreen()
{
	// TODO: Add your control notification handler code here
	int  iErr  =  -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	//
	HWND  hCurTalk  =  m_var.guiData.param.hCurTalk;
	HWND  hMgr  =  m_var.guiData.param.hMgrTalk;
	CHelp_getDlgTalkVar  help_mgr;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )help_mgr.getVar(  hMgr  );
	if  (  !pMgrVar  )  return;
	if (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  return;
	
					  unsigned  short			usCnt_monPics_row	=		1;
					  unsigned  short			usCnt_monPics_col	=		1;
					  unsigned  int				uiInitW				=		640;
					  unsigned  int				uiInitH				=		480;
					  BOOL						bScrollBarEnabled	=		FALSE;
					  BOOL						bVideoConference	=		FALSE;
					  BOOL						bRemoteAssist		=		FALSE;

					//
					//  uiInitW  =  pImg->iW_org;
					 // uiInitH  =  pImg->iH_org;

					  PARAM_dlgVideos	params  =  {0};
					  //
					  //params.m_var.iTaskId  =  pImg->iTaskId;
					  //params.m_var.pImgs  =  &pZone->images;
					  //params.m_var.iIndex_capImage  =  j;
					  params.usCnt_monPics_row  =  usCnt_monPics_row;
					  params.usCnt_monPics_col  =  usCnt_monPics_col;
					  params.uiInitW  =  uiInitW;
					  params.uiInitH  =  uiInitH;
					  params.bScrollBarEnabled  =  bScrollBarEnabled;
					  params.bVideoConference  =  bVideoConference;
					  params.bRemoteAssist  =  bRemoteAssist;
	
					  //  2012/05/27
					  //params.hParent  =  m_hWnd;
					  
					  //
					  if  (  IsWindow(  pProcInfo->dlg2ndScreen.hWnd_2ndScreen  )  )  {
						  MACRO_SetForegroundWindow(  pProcInfo->dlg2ndScreen.hWnd_2ndScreen  );
						  goto  errLabel;
					  }

					  //
					  HWND  hWnd  =  NULL;
					  HWND  hParent  =  NULL;	//hCurTalk;
					  //
					  showDlgVideos(  hParent,  hMgr,  TRUE,  &params,  &pMgrVar->pMisCnt->subWnds,  &hWnd  );
					  //
					  if  (  !IsWindow(  hWnd  )  )  goto  errLabel;
					  pProcInfo->dlg2ndScreen.hWnd_2ndScreen  =  hWnd;
					  
					  iErr  =  0;
errLabel:
					  return;
}


void CDlgInstantAssistant::OnBnClickedButtonlocalvideo()
{
	// TODO: Add your control notification handler code here
	int  iErr  =  -1;
	HWND  hCurTalk  =  m_var.guiData.param.hCurTalk;
	HWND  hMgr  =  m_var.guiData.param.hMgrTalk;
	CHelp_getDlgTalkVar  help_mgr;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )help_mgr.getVar(  hMgr  );
	if  (  !pMgrVar  )  return;
	if (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  return;

	//
	if ( !pMgrVar->av.taskInfo.bTaskExists  )  return;
	pMgrVar->av.taskInfo.bNeedShowMeDesc  = !pMgrVar->av.taskInfo.bNeedShowMeDesc;

	//
	askToRefreshSize_mgr(hMgr);

	//
	return;
}


void CDlgInstantAssistant::OnBnClickedCheckaudio()
{
	// TODO: 在此添加控件通知处理程序代码
	int  ii = 0;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	CButton* pBtn_a = (CButton*)GetDlgItem(IDC_CHECK_audio);
	if (!pBtn_a) return;

	if (pBtn_a->GetCheck() == BST_CHECKED) {
		pProcInfo->av.confLayout.taskInfo.iHkStatus_local  &=  ~CONST_hkFlg_mkfOff;
	}
	else {
		pProcInfo->av.confLayout.taskInfo.iHkStatus_local  |=  CONST_hkFlg_mkfOff;
	}
	//
	confOthers_sendStreamInfo();

	//
	return;
}





void CDlgInstantAssistant::OnBnClickedCheckvideo()
{
	// TODO: 在此添加控件通知处理程序代码
	int  ii = 0;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	CButton* pBtn_v = (CButton*)GetDlgItem(IDC_CHECK_video);
	if (!pBtn_v) return;

	if (pBtn_v->GetCheck() == BST_CHECKED) {
		//unsigned  int ll = ~(CONST_hkFlg_sxtOff);
		pProcInfo->av.confLayout.taskInfo.iHkStatus_local &= ~CONST_hkFlg_sxtOff;
	}
	else {
		pProcInfo->av.confLayout.taskInfo.iHkStatus_local|= CONST_hkFlg_sxtOff;
	}
	//
	confOthers_sendStreamInfo();

	return;
}


void CDlgInstantAssistant::OnBnClickedButtonipc()
{
	// TODO: 在此添加控件通知处理程序代码
	dlgInstantAssistant_OnCmd(m_hWnd, m_var, IDC_BUTTON_ipc);

}


void CDlgInstantAssistant::OnBnClickedCheckllayout()
{
	// TODO: 在此添加控件通知处理程序代码
	int iErr = -1;
	HWND  hTalk_mgr = m_var.guiData.param.hMgrTalk;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	CButton* pBtn_l = (CButton*)GetDlgItem(IDC_CHECK_lLayout);
	if (!pBtn_l) return;

	//
	unsigned  char  ucbOneBigLayout = false;
	if (pBtn_l->GetCheck() == BST_CHECKED) {
		ucbOneBigLayout = true;
	}

	//
	do {
		CHelp_getDlgTalkVar help_getDlgTalkVar;
		DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hTalk_mgr);
		if (!pDlgTalkVar)break;
		if (!isTalkerShadowMgr(pDlgTalkVar->addr)) break;
		if (!pDlgTalkVar->av.taskInfo.bTaskExists) break;

		QY_MESSENGER_ID  idInfo_to = pDlgTalkVar->av.taskInfo.idInfo_starter;

		//
		QY_MESSENGER_ID  idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
		QY_MESSENGER_ID  idInfo_requester = pMisCnt->idInfo;

		ConfLayoutParam  confLayoutParam = { 0 };
		confLayoutParam.oneBigLayoutParam.ucbOneBigLayout = ucbOneBigLayout;

		//
		sendConfLayout(false,0, CONST_imOp_setOneBig, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, idInfo_to, _T(""));

		//
		iErr = 0;
	} while (false);

	//
	return;
}


void CDlgInstantAssistant::OnBnClickedButtonselonebig()
{
	// TODO: 在此添加控件通知处理程序代码
	int  ii = 0;

	dlgInstantAssistant_OnCmd(m_hWnd, m_var, IDC_BUTTON_selOneBig);


	//
	return;
}


void CDlgInstantAssistant::OnBnClickedVideoright()
{
	// TODO: 在此添加控件通知处理程序代码
	//右
	int i = 0;
	HWND  hTalk_mgr = m_var.guiData.param.hMgrTalk;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return;
	QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_usLayoutTypeTable);


	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hTalk_mgr);
	if (!pDlgTalkVar) return;

	//  2010/12/27. send usLayoutType to imGrpMems
	if (pDlgTalkVar->av.taskInfo.bTaskExists) {
		//
		if (pDlgTalkVar->av.taskInfo.ucbStarter)
		{
			//pFuncs->pf_sendVideoConferenceLayout(usLayoutType_unused, CONST_ pParam, hDlgTalk_mgr, pDlgTalkVar->addr.idInfo, _T("doSelLayoutType"));
		}
		else {
			//
			QY_MESSENGER_ID idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
			QY_MESSENGER_ID idInfo_requester;
			idInfo_requester.ui64Id = pMisCnt->idInfo.ui64Id;
			//
			pFuncs->pf_sendVideoConferenceLayout(false, 0, CONST_imOp_videoRight, 0, idInfo_imGrp_related, idInfo_requester, pDlgTalkVar->av.taskInfo.idInfo_starter, _T("doSelLayoutType"));
		}
	}
}


void CDlgInstantAssistant::OnBnClickedVideoleft()
{
	// TODO: 在此添加控件通知处理程序代码  
	//左
	int i = 0;
	HWND  hTalk_mgr = m_var.guiData.param.hMgrTalk;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return;
	QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_usLayoutTypeTable);


	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hTalk_mgr);
	if (!pDlgTalkVar) return;

	//  2010/12/27. send usLayoutType to imGrpMems
	if (pDlgTalkVar->av.taskInfo.bTaskExists) {
		//
		if (pDlgTalkVar->av.taskInfo.ucbStarter)
		{
			//pFuncs->pf_sendVideoConferenceLayout(usLayoutType_unused, CONST_ pParam, hDlgTalk_mgr, pDlgTalkVar->addr.idInfo, _T("doSelLayoutType"));
		}
		else {
			//
			QY_MESSENGER_ID idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
			QY_MESSENGER_ID idInfo_requester;
			idInfo_requester.ui64Id = pMisCnt->idInfo.ui64Id;
			//
			pFuncs->pf_sendVideoConferenceLayout(false, 0, CONST_imOp_videoLeft, 0, idInfo_imGrp_related, idInfo_requester, pDlgTalkVar->av.taskInfo.idInfo_starter, _T("doSelLayoutType"));
		}
	}
}


void CDlgInstantAssistant::OnBnClickedVideotop()
{
	// TODO: 在此添加控件通知处理程序代码
	//上
	int i = 0;
	HWND  hTalk_mgr = m_var.guiData.param.hMgrTalk;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return;
	QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_usLayoutTypeTable);


	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hTalk_mgr);
	if (!pDlgTalkVar) return;

	//  2010/12/27. send usLayoutType to imGrpMems
	if (pDlgTalkVar->av.taskInfo.bTaskExists) {
		//
		if (pDlgTalkVar->av.taskInfo.ucbStarter)
		{
			//pFuncs->pf_sendVideoConferenceLayout(usLayoutType_unused, CONST_ pParam, hDlgTalk_mgr, pDlgTalkVar->addr.idInfo, _T("doSelLayoutType"));
		}
		else {
			//
			QY_MESSENGER_ID idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
			QY_MESSENGER_ID idInfo_requester;
			idInfo_requester.ui64Id = pMisCnt->idInfo.ui64Id;
			//
			pFuncs->pf_sendVideoConferenceLayout(false, 0, CONST_imOp_videoTop, 0, idInfo_imGrp_related, idInfo_requester, pDlgTalkVar->av.taskInfo.idInfo_starter, _T("doSelLayoutType"));
		}
	}
}


void CDlgInstantAssistant::OnBnClickedVideobottom()
{
	// TODO: 在此添加控件通知处理程序代码
	//下
	int i = 0;
	HWND  hTalk_mgr = m_var.guiData.param.hMgrTalk;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return;
	QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_usLayoutTypeTable);


	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hTalk_mgr);
	if (!pDlgTalkVar) return;

	//  2010/12/27. send usLayoutType to imGrpMems
	if (pDlgTalkVar->av.taskInfo.bTaskExists) {
		//
		if (pDlgTalkVar->av.taskInfo.ucbStarter)
		{
			//pFuncs->pf_sendVideoConferenceLayout(usLayoutType_unused, CONST_ pParam, hDlgTalk_mgr, pDlgTalkVar->addr.idInfo, _T("doSelLayoutType"));
		}
		else {
			//
			QY_MESSENGER_ID idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
			QY_MESSENGER_ID idInfo_requester;
			idInfo_requester.ui64Id = pMisCnt->idInfo.ui64Id;
			//
			pFuncs->pf_sendVideoConferenceLayout(false, 0, CONST_imOp_videoBottom, 0, idInfo_imGrp_related, idInfo_requester, pDlgTalkVar->av.taskInfo.idInfo_starter, _T("doSelLayoutType"));
		}
	}
}


void CDlgInstantAssistant::OnBnClickedCoordinate()
{
	// TODO: 在此添加控件通知处理程序代码
	int ii = 0;
	HWND  hTalk_mgr = m_var.guiData.param.hMgrTalk;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return;
	QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_usLayoutTypeTable);

	ConfLayoutParam confLayoutParam = { 0 };
	confLayoutParam.phoneEnlargeParam.usEnlargeType = CONST_enlargeType_img;
	confLayoutParam.phoneEnlargeParam.x = 100;
	confLayoutParam.phoneEnlargeParam.y = 1000;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hTalk_mgr);
	if (!pDlgTalkVar) return;

	//  2010/12/27. send usLayoutType to imGrpMems
	if (pDlgTalkVar->av.taskInfo.bTaskExists) {
		//
		if (pDlgTalkVar->av.taskInfo.ucbStarter)
		{
			//pFuncs->pf_sendVideoConferenceLayout(usLayoutType_unused, CONST_ pParam, hDlgTalk_mgr, pDlgTalkVar->addr.idInfo, _T("doSelLayoutType"));
		}
		else {
			//
			QY_MESSENGER_ID  idInfo_imGrp_related;  idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
			QY_MESSENGER_ID idInfo_requester; idInfo_requester.ui64Id = pMisCnt->idInfo.ui64Id;

			//
			pFuncs->pf_sendVideoConferenceLayout(false, 0, CONST_imOp_phone_enlargeImg, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, pDlgTalkVar->av.taskInfo.idInfo_starter, _T("doSelLayoutType_phone"));
		}
	}

}


void CDlgInstantAssistant::OnBnClickedCancelamp()
{
	// TODO: 在此添加控件通知处理程序代码
	int ii = 0;
	HWND  hTalk_mgr = m_var.guiData.param.hMgrTalk;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return;
	QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_usLayoutTypeTable);

	ConfLayoutParam confLayoutParam = { 0 };

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hTalk_mgr);
	if (!pDlgTalkVar) return;

	//  2010/12/27. send usLayoutType to imGrpMems
	if (pDlgTalkVar->av.taskInfo.bTaskExists) {
		//
		if (pDlgTalkVar->av.taskInfo.ucbStarter)
		{
			//pFuncs->pf_sendVideoConferenceLayout(usLayoutType_unused, CONST_ pParam, hDlgTalk_mgr, pDlgTalkVar->addr.idInfo, _T("doSelLayoutType"));
		}
		else {
			//
			QY_MESSENGER_ID  idInfo_imGrp_related;  idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
			QY_MESSENGER_ID idInfo_requester; idInfo_requester.ui64Id = pMisCnt->idInfo.ui64Id;

			//
			pFuncs->pf_sendVideoConferenceLayout(false, 0, CONST_imOp_phone_cancelEnlargeImg, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, pDlgTalkVar->av.taskInfo.idInfo_starter, _T("doSelLayoutType_phone"));
		}
	}

}
