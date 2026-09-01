// DlgWalls.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc_touchscreen.h"

#include	"qyCusResPublic.h"
#include	"qyOpenShellCommon.h"
#include	"qmOpenCommon.h"
//  #include	"qmShell_open.h"

#include	"tmpCeLib.h"

#include	"DlgWalls.h"

//  #include	"DlgMenuIsCli.h"
#include	"myresource.h"

#include	"qyCusResTemp.h"
#include	"ctxQmc.h"

//  #include	"DlgPolicyIsClient.h"
//  #include	"DlgCfgVideoConference.h"
//  #include	"DlgMsgList.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
#include	"qmcCommFunc_isCli.h"
#include	"isCliCorePublic.h"






 //  2015/12/05
 int  layoutWalls(  HWND  hDlgWalls,  int  iWndContentType  )
{
	int					iErr		=	-1;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	CTX_qm_thread  *  pCqt  =  &pQyMc->gui.ctx_gui_thread;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt) return -1;

	//
	int  iZoneObjsType  =  0;

	//
	ZONE_objs  *  pZoneObjs  =  (  ZONE_objs  *  )pFuncs->pf_getZoneObjs(  hDlgWalls,  iWndContentType,  iZoneObjsType  );
	if  (  !pZoneObjs  )  return  -1;
	ZONE_objs_info	*	pVar		=	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  hDlgWalls,  iWndContentType,  iZoneObjsType  );
	if  (  !pVar  )  return  -1;
	int					index;
	unsigned  int	cnt	=	0;


	//  
	//  这里要加getRect_talkers(  ). 2012/04/02.对ts.该函数调用GetClientRect, 对pc,返回zone的rc
	//
	RECT	rc_zone;
	//
	if  (  pFuncs->pf_getRect_talkers(  hDlgWalls,  &rc_zone  )  )  return  -1;

	//  2015/12/19
	chkZoneObjs(  pCqt,  pZoneObjs  );
	//
	if  (  get_zoneObjs_layoutInfo(  pProcInfo,  pZoneObjs,  rc_zone,  TRUE,  pVar  )  )  return  -1;


	//
	if  (  !pVar->guiData.w_org  ||  !pVar->guiData.h_org  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "layoutWalls failed, w_org or h_org is 0"  )  );
		#endif
		return  -1;
	}

	//
	if  (  bApp_ts(  pQyMc  )  )  {  //  
		int  w  =  rc_zone.right  -  rc_zone.left;
		int  h  =  rc_zone.bottom  -  rc_zone.top;
		int  iX,  iY,  iW,  iH;

		//  2011/04/10
		unsigned  char	ucbHidden_bar						=	FALSE;
		if  (  bSupported_devAuth(  )  )  {
			if  (  !pMisCnt->retrieveImObjList.ulbContactExists  &&  !pMisCnt->retrieveImObjList.ulbImGrpExists  )  ucbHidden_bar  =  TRUE;
		}

		//  bar
		int	idc;
		float  fx,  fy;
		fx  =  1.  *  w  /  pVar->guiData.w_org;
		fy  =  1.  *  h  /  pVar->guiData.h_org;

		//
		idc  =  pVar->guiData.iIDC_BUTTON_contact;
		ShowWindow(  GetDlgItem(  hDlgWalls,  idc  ),  SW_HIDE  );
		idc  =  pVar->guiData.iIDC_BUTTON_group;
		ShowWindow(  GetDlgItem(  hDlgWalls,  idc  ),  SW_HIDE  );
		//
		idc  =  pVar->guiData.iIDC_BUTTON_bar;
		if  (  !pVar->guiData.ucbHideBar  &&  !ucbHidden_bar  )  {
			RECT	rc;
			rc  =  pVar->guiData.rcIDC_BUTTON_bar;
			iH  =  rc.bottom  -  rc.top;
			iH  *=  fy;  
			}
		else  {
			  iH  =  0;
		}	
		iW  =  w;  
		iX  =  0;  iY  =  h  -  iH;
		MoveWindow(  GetDlgItem(  hDlgWalls,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
		//

		//  
		w  =  rc_zone.right  -  rc_zone.left;
		h  =  iY  -  rc_zone.top;
	}	//  #endif




	//
	RECT	rc;

	for  (  index  =  0;  index  <  mycountof(  pVar->mems  );  index  ++  )  {
		 //
		 ZONE_obj  *  pZoneObj  =  &pZoneObjs->mems[index];	//  2015/12/05
		 //
		 ZONE_obj_info  *  pMem  =  &pVar->mems[index];
		 if  (  !pZoneObj->hWndWallMem  )  continue;

		 rc.left  =  pMem->rect.iX;
		 rc.top  =  pMem->rect.iY;
		 rc.right  =  pMem->rect.iX  +  pMem->rect.iW;
		 rc.bottom  =  pMem->rect.iY  +  pMem->rect.iH;
		 MapWindowPoints(  hDlgWalls,  NULL,  (  LPPOINT  )&rc,  2  );

		 ::MoveWindow(  pZoneObj->hWndWallMem,  rc.left,  rc.top,  pMem->rect.iW,  pMem->rect.iH,  TRUE  );
		 //  SendMessage(  pMem->hWndWallMem,  WM_COMMAND,  MAKEWPARAM(  ID_refreshLayout,  0  ),  0  );	//  2011/03/15
	}

	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
		//
		setWallsBarPos(  hDlgWalls,  pFuncs->pf_getZoneObjsInfo(  pProcInfo,  hDlgWalls,  iWndContentType,  0  ),  NULL,  0  );
	}

	return  iErr;
}




//
 __declspec(  dllexport  )  int  addToWalls(  HWND  hDlgTalk,  HWND  hDlgWalls,  int  iWndContentType,  int  *  piIndex_wall  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iErr		=	-1;
	int				i;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	//
	int  iZoneObjsType  =  0;
	//
	ZONE_objs  *  pZoneObjs  =  (  ZONE_objs  *  )pFuncs->pf_getZoneObjs(  hDlgWalls,  iWndContentType,  iZoneObjsType  );
	if  (  !pZoneObjs  )  return  -1;
	ZONE_objs_info	*	pVar	=	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  hDlgWalls,  iWndContentType,  iZoneObjsType  );
	if  (  !pVar  )  return  -1;

	if  (  !IsWindow(  hDlgTalk  )  )  return  -1;

	//  2015/12/04
	if  (  !isTalkerInGZone(  hDlgTalk,  CONST_qyWndContentType_talker,  NULL  )  )  {
		showInfo_open0(  0,  0,  _T(  "addToWalls failed, isTalkerInGZone is false"  )  );
		#ifdef  __DEBUG__
				MACRO_qyAssert(  0,  _T(  "addToWalls faield"  )  );
		#endif
		return  -1;
	}

	//
	for  (  i  =  0;  i  <  mycountof(  pVar->mems  );  i  ++  )  {
		if  (  !IsWindow(  pZoneObjs->mems[i].hWndWallMem  )  )  break;
	}
	if  (  i  ==  mycountof(  pVar->mems  )  )  goto  errLabel;

	pZoneObjs->mems[i].hWndWallMem  =  hDlgTalk;

	if  (  i  ==  0  )  {
		int	j;
		for  (  j  =  1;  j  <  mycountof(  pVar->mems  );  j  ++  )  {
			 if  (  IsWindow(  pZoneObjs->mems[j].hWndWallMem  )  )  break;			 
		}
		if  (  j  ==  mycountof(  pVar->mems  )  )  {		//  说明是第一个成员并是唯一的成员, 则置为放大
			pZoneObjs->iIndex_enlarged1  =  i;
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "addToWalls, enlarge the only one talker"  )  );
		}
	}

	layoutWalls(  hDlgWalls,  iWndContentType  );

	iErr  =  0;
errLabel:
	if  (  !iErr  )  {
		if  (  piIndex_wall  )  *piIndex_wall  =  i;
	}
	return  iErr;
}


 //  2014/01/01
 int  getWallMemInfo(  ZONE_objs  *  pZoneObjs,  HWND  hDlgTalk,  BOOL  *  pbEnlared  )
{
	int  iErr  =  -1;
	BOOL  bEnlared  =  FALSE;

	if  (  !pZoneObjs  )  return  -1;
	//if  (  !pDlgWallsVar  )  return  -1;
	if  (  !IsWindow(  hDlgTalk  )  )  return  -1;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pZoneObjs->mems  );  i  ++  )  {
		if  (  pZoneObjs->mems[i].hWndWallMem  ==  hDlgTalk  )  break;
	}
	if  (  i  ==  mycountof(  pZoneObjs->mems  )  )  goto  errLabel;
	
	//ZONE_obj_info  *  pMem  =  &pDlgWallsVar->mems[i];

	if  (  i  ==  pZoneObjs->iIndex_enlarged1  )  {
		bEnlared  =  TRUE;
	}


	iErr  =  0;
errLabel:

	if  (  !iErr  )  {
		if  (  pbEnlared  )  *pbEnlared  =  bEnlared;
#if  0
		if  (  pRect  )  {
			memcpy(  pRect,  &pMem->rect,  sizeof(  pRect[0]  )  );	
		}
#endif
	}

	return  iErr;

 }

	
 //  2012/05/18
 int  closeWallMems(  HWND  hDlgWalls,  int  iWndContentType  )
 {
	 int				iErr	=	-1;
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	//
	int  iZoneObjsType  =  0;
	//
	ZONE_objs  *  pZoneObjs  =  (  ZONE_objs  *  )pFuncs->pf_getZoneObjs(  hDlgWalls,  iWndContentType,  iZoneObjsType  );
	if  (  !pZoneObjs  )  return  -1;
	ZONE_objs_info	*	pVar	=	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  hDlgWalls,  iWndContentType,  iZoneObjsType  );
	if  (  !pVar  )  return  -1;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pVar->mems  );  i  ++  )  {
		if  (  !IsWindow(  pZoneObjs->mems[i].hWndWallMem  )  )  continue;
		SendMessage(  pZoneObjs->mems[i].hWndWallMem,  WM_CLOSE,  0,   0  );
	}

	iErr  =  0;
//  errLabel:

	 return  iErr;
 }

  BOOL  bExists_wallMem(  HWND  hDlgWalls,  int  iWndContentType  )
  {
	  BOOL	bRet	=	FALSE;
	  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	  if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	//
	int  iZoneObjsType  =  0;
	//
	ZONE_objs  *  pZoneObjs  =  (  ZONE_objs  *  )pFuncs->pf_getZoneObjs(  hDlgWalls,  iWndContentType,  iZoneObjsType  );
	if  (  !pZoneObjs  )  return  FALSE;
	  ZONE_objs_info	*	pVar	=	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  hDlgWalls,  iWndContentType,  iZoneObjsType  );	
	  if  (  !pVar  )  return  FALSE;

	  int  i;
	  for  (  i  =  0;  i  <  mycountof(  pVar->mems  );  i  ++  )  {
		   if  (  IsWindow(  pZoneObjs->mems[i].hWndWallMem  )  )  {
			   bRet  =  TRUE;
			   break;
		   }
	  }

	  return  bRet;
  }

 //
#if  0
 int  enlargeWall(  HWND  hDlgWall  )
{
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return  -1;
	MC_VAR_isCli  *  pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	if  (  !IsWindow(  hDlgWall  )  )  return  -1;
	
	ZONE_objs  *  pZoneObjs  =  (  ZONE_objs  *  )pFuncs->pf_getZoneObjs(  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall  );
	if  (  !pZoneObjs  )  return  -1;

	ZONE_objs_info	*	pVar	=	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall  );
	if  (  !pVar  )  return  -1;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pVar->mems  );  i  ++  )  {
		 if  (  pZoneObjs->mems[i].hWndWallMem  ==  hDlgWall  )  break;
	}
	if  (  i  ==  mycountof(  pVar->mems  )  )  return  -1;

	pZoneObjs->iIndex_enlarged  =  i;

	layoutWalls(  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall  );

	return  0;
}
#endif


 //
  int  selectWall(  HWND  hDlgWall  )
{
	MC_VAR_isCli  *  pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;


	if  (  !IsWindow(  hDlgWall  )  )  return  -1;

	//
	int  iZoneObjsType  =  0;
	//
	ZONE_objs  *  pZoneObjs  =  (  ZONE_objs  *  )pFuncs->pf_getZoneObjs(  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall,  iZoneObjsType  );
	if  (  !pZoneObjs  )  return  -1;
	ZONE_objs_info	*	pVar	=	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall,  iZoneObjsType  );
	if  (  !pVar  )  return  -1;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pVar->mems  );  i  ++  )  {
		 if  (  pZoneObjs->mems[i].hWndWallMem  ==  hDlgWall  )  break;
	}
	if  (  i  ==  mycountof(  pVar->mems  )  )  return  -1;

	if  (  pVar->iIndex_selected  ==  i  )  return  0;

	pVar->iIndex_selected  =  i;

	layoutWalls(  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall  );

	return  0;
}

  //
 BOOL  isWallEnlarged(  HWND  hDlgWall  )
{
	BOOL				bRet		=	FALSE;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;
	 
	//
	int  iZoneObjsType  =  0;
	//
	ZONE_objs  *  pZoneObjs  =  (  ZONE_objs  *  )pFuncs->pf_getZoneObjs(  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall,  iZoneObjsType  );
	if  (  !pZoneObjs  )  goto  errLabel;
	ZONE_objs_info  *  pDlgWallsVar  =  (  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall,  iZoneObjsType  );
	if  (  !pDlgWallsVar  )  goto  errLabel;
	if  (  !isZoneObjIndexValid(  pZoneObjs->iIndex_enlarged1  )  )  goto  errLabel;
	ZONE_obj  *  pMem  =  &pZoneObjs->mems[pZoneObjs->iIndex_enlarged1];
	if  (  hDlgWall  !=  pMem->hWndWallMem  )  goto  errLabel;

	bRet  =  TRUE;
errLabel:
	return  bRet;
 }

  BOOL  isWallSelected(  HWND  hDlgWall  )
{
	BOOL				bRet		=	FALSE;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;
	
	//
	int  iZoneObjsType  =  0;
	//		
	ZONE_objs  *  pZoneObjs  =  (  ZONE_objs  *  )pFuncs->pf_getZoneObjs(  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall,  iZoneObjsType  );
	if  (  !pZoneObjs  )  goto  errLabel;

	ZONE_objs_info  *  pDlgWallsVar  =  (  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall,  iZoneObjsType  );
	if  (  !pDlgWallsVar  )  goto  errLabel;
	if  (  !isZoneObjIndexValid(  pDlgWallsVar->iIndex_selected  )  )  goto  errLabel;
	ZONE_obj  *  pMem  =  &pZoneObjs->mems[pDlgWallsVar->iIndex_selected];
	if  (  hDlgWall  !=  pMem->hWndWallMem  )  goto  errLabel;

	bRet  =  TRUE;
errLabel:
	return  bRet;
 }


 //  #if  defined(  __APP_qyMc_touchscreen__  )  //  ||  defined(  __isCli__  )
 //  int  viewWallsBar(  int  xPos_screen,  int  yPos_screen,  HWND  hDlgWalls,  BOOL  bNoDelayToView  )
 __declspec(  dllexport  )  int  viewWallsBar_ts(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgWalls,  int  iWndContentType_hDlgWalls,  BOOL  bNoDelayToView  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iErr		=	-1;
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );

	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	//
	ZONE_objs_info	*	pVar	=	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  hDlgWalls,  iWndContentType_hDlgWalls,  0  );
	if  (  !pVar  )  return  -1;
	ZONE_objs_info	&	m_var	=	*pVar;

	m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );

	#ifdef  __DEBUG__
			//  traceLog(  _T(  "mousemove"  )  );
	#endif

	if  (  !m_var.guiData.ucbHideBar  )  return  0;



	if  (  !bNoDelayToView  )  {	
		if  (  xPos_screen  ==  m_var.param_viewBar.xPos_screen  &&  yPos_screen  ==  m_var.param_viewBar.yPos_screen  )  {
			iErr  =  0;  goto  errLabel;
		}
#if  0
		if  (  GetTickCount(  )  -  m_var.dwTickCnt_hide_bar  <  pQyMc->cfg.usDelayInMsToViewToolbar  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "viewInstantAssistant: mouse pos has not changed, skipped"  )  );
			#endif
			iErr  =  0;  goto  errLabel;
		}
#endif
	}
	m_var.param_viewBar.xPos_screen  =  xPos_screen;
	m_var.param_viewBar.yPos_screen  =  yPos_screen;


#ifdef  __DEBUG__
		traceLog(  _T(  "to show WallsBar"  )  );
#endif

	m_var.guiData.ucbHideBar  =  FALSE;

	sizeAllControls_dlgWalls(  hDlgWalls,  iWndContentType_hDlgWalls,  &m_var  );

	iErr  =  0;
errLabel:
	return  iErr;
}


// CDlgWalls dialog



 __declspec(  dllexport  )  int  sizeAllControls_dlgWalls(  HWND  hDlg,  int  iWndContentType,  ZONE_objs_info  *  pVar  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr	=	-1;
	ZONE_objs_info  &  m_var  =  *pVar;

	RECT	rc;
	int		w,  h;

	GetClientRect(  hDlg,  &rc  );
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;

	DLG_guiData_wall	*	p	=	&m_var.guiData;
	MC_VAR_isCli		*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	MIS_CNT				*	pMisCnt		=	getMisCntByName(  pProcInfo,  _T(  ""  )  );

	int						idc;
	int						iX  =  0,  iY  =  0,  iW  =  0,  iH  =  0;
	
	//
	if  (  !p->w_org  ||  !p->h_org  )  return  -1;

	//  traceLog(  _T(  "t is %d,  hb is  %d,  y  is  %d"  ),  p->rcIDC_BUTTON_contact.top, (  p->rcIDC_BUTTON_contact.bottom  -  p->rcIDC_BUTTON_contact.top  ),  (  p->rcIDC_BUTTON_group.top  -  p->rcIDC_BUTTON_contact.bottom  )  );

	if  (  isQEmpty(  &pMisCnt->talkingFriendQ  )  )  {

		float  fx,  fy;
		fx  =  1.  *  w  /  p->w_org;
		fy  =  1.  *  h  /  p->h_org;

		
		if  (  !m_var.oldLayout.iH_btn  )  return  -1;

		int		iEdge_l,  iEdge_t;
		int		iW_btn,  iH_btn;
		int		iY_spacing;
		int		iH_bar;
		unsigned  char	ucbHidden_contact	=	0;
		unsigned  char	ucbHidden_grp		=	0;
		unsigned  char	ucbHidden_bar						=	FALSE;
		unsigned  char	ucbHidden_customerServiceOfficer0	=	FALSE;
		int		nBtns	=	0;

		if  (  bSupported_devAuth(  )  )  {
			if  (  !pMisCnt->retrieveImObjList.ulbContactExists  )  ucbHidden_contact  =  TRUE;
			if  (  !pMisCnt->retrieveImObjList.ulbImGrpExists  )  ucbHidden_grp  =  TRUE;
			if  (  !pMisCnt->retrieveImObjList.ulbContactExists  &&  !pMisCnt->retrieveImObjList.ulbImGrpExists  )  ucbHidden_bar  =  TRUE;
		}
		if  (  !pProcInfo->customerService.objs[0].idInfo.ui64Id  )  ucbHidden_customerServiceOfficer0  =  TRUE;

		if  (  !ucbHidden_contact  )  nBtns  ++  ;
		if  (  !ucbHidden_grp  )  nBtns  ++  ;
		if  (  !ucbHidden_customerServiceOfficer0  )  nBtns  ++  ;

		//  if  (  !nBtns  )  return  -1;

		float	ft  =  m_var.oldLayout.iEdge_t  *  1.0  /  m_var.oldLayout.iH_btn;
		float	fys  =  m_var.oldLayout.iY_spacing  *  1.0  /  m_var.oldLayout.iH_btn;

		iEdge_l  =  m_var.oldLayout.iEdge_l  *  fx;
		if  (  ucbHidden_bar  )  iH_bar  =  0;
		else  iH_bar  =  (  p->rcIDC_BUTTON_bar.bottom  -  p->rcIDC_BUTTON_bar.top  )  *  fy;
		iW_btn  =  m_var.oldLayout.iW_btn  *  fx;		
		if  (  !nBtns  )  iH_btn  =  0;
		else  iH_btn  =  (  h  -  iH_bar  )  *  1.  /  (  2  *  ft  +  nBtns  +  fys  *  (  nBtns  -  1  )  );
		iEdge_t	=  ft  *  iH_btn;
		iY_spacing	=	fys  *  iH_btn;


		//  traceLog(  _T(  "t is %d,  hb is  %d,  y  is  %d"  ),  iEdge_t, iH_btn,  iY_spacing  );


		iX  =  iEdge_l;
		iY  =  iEdge_t;
		idc  =  p->iIDC_BUTTON_contact;
		if  (  ucbHidden_contact  )  {
			SetWindowPos(  GetDlgItem(  hDlg,  idc  ),  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  |  SWP_HIDEWINDOW  );
			}
		else  {
			  iW  =  iW_btn;	iH  =  iH_btn;
			  SetWindowPos(  GetDlgItem(  hDlg,  idc  ),  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  |  SWP_SHOWWINDOW  );
			  iY  +=  iH  +  iY_spacing;
		}

		idc  =  p->iIDC_BUTTON_group;
		if  (  ucbHidden_grp  )  {
			SetWindowPos(  GetDlgItem(  hDlg,  idc  ),  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  |  SWP_HIDEWINDOW  );
			}
		else  {
			  iW  =  iW_btn;	iH  =  iH_btn;
			  SetWindowPos(  GetDlgItem(  hDlg,  idc  ),  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  |  SWP_SHOWWINDOW  );
			  iY  +=  iH  +  iY_spacing;
		}

		idc  =  p->iIDC_BUTTON_customerServiceOfficer0;
		if  (  ucbHidden_customerServiceOfficer0  )  {
			SetWindowPos(  GetDlgItem(  hDlg,  idc  ),  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  |  SWP_HIDEWINDOW  );
			}
		else  {
			  iW  =  iW_btn;	iH  =  iH_btn;
			  SetWindowPos(  GetDlgItem(  hDlg,  idc  ),  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  |  SWP_SHOWWINDOW  );
			  iY  +=  iH  +  iY_spacing;
		}

		idc  =  p->iIDC_BUTTON_bar;
		rc  =  p->rcIDC_BUTTON_bar;
		iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		if  (  ucbHidden_bar  )  {
			SetWindowPos(  GetDlgItem(  hDlg,  idc  ),  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  |  SWP_HIDEWINDOW  );
			}
		else  {			
			  iW  =  w;  
			  iH  *=  fy;  
			  iX  =  0;  iY  =  h  -  iH;
			  SetWindowPos(  GetDlgItem(  hDlg,  idc  ),  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  |  SWP_SHOWWINDOW  );
		}

		//
		if  (  pProcInfo->customerService.objs[0].idInfo.ui64Id  )  SetDlgItemText(  hDlg,  p->iIDC_BUTTON_customerServiceOfficer0,  pProcInfo->customerService.objs[0].displayName  );

		}
	else  {


		  idc  =  p->iIDC_BUTTON_contact;
		  SetWindowPos(  GetDlgItem(  hDlg,  idc  ),  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  |  SWP_HIDEWINDOW  );
		  idc  =  p->iIDC_BUTTON_group;
		  SetWindowPos(  GetDlgItem(  hDlg,  idc  ),  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  |  SWP_HIDEWINDOW  );
		  idc  =  p->iIDC_BUTTON_customerServiceOfficer0;
		  SetWindowPos(  GetDlgItem(  hDlg,  idc  ),  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  |  SWP_HIDEWINDOW  );
		  
		  //
		  layoutWalls(  hDlg,  iWndContentType  );
	}

	iErr  =  0;
errLabel:
	return  iErr;
}




