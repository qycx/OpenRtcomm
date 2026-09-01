// DlgMenuIsCli.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

//  #include	"qyMc_touchscreen.h"
#include	"DlgMenuIsCli.h"
#include	"myresource.h"

#include	"DlgWalls.h"
#include	"qyCusResTemp.h"

//  #include	"DlgPolicyIsClient.h"
//  #include	"DlgCfgVideoConference.h"

#include	"funcsForIsCliHelp.h"
#include	"isCliHelpPublic.h"
#include	"qmcCommFunc_isCli.h"



INT_PTR CALLBACK dlgProc_menuIsCli(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);



 __declspec(  dllexport  )  int  showMenu_wallsBar(  HINSTANCE  hInst,  HWND  hParent,  int  iWndContentType_hParent,  void  *  p2  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int			iErr	=	-1;

	if  (  !hInst  )  hInst  =  get_my_hInst(g_pQyMc  );

	CQyWnd	*	pWnd	=	NULL;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	//  2011/03/18
	if  (  IsWindow(  pQyMc->gui.hWnd_menu  )  )  {
		SetForegroundWindow(  pQyMc->gui.hWnd_menu  );
		return  0;
	}

	//
	if  (  IsWindow(  pQyMc->gui.hWnd_popupTool  )  )  {
		SendMessage(  pQyMc->gui.hWnd_popupTool,  WM_CLOSE,  0,  0  );
	}

	//  pWnd  =  newQyWnd(  CONST_qyWndContentType_menu_walls  );
	pWnd  =  new  CDlgMenuIsCli;
	if  (  !pWnd  )  goto  errLabel;
	pWnd->m_var.iWndContentType  =  CONST_qyWndContentType_menu_walls;


	DLG_guiData_menuIsCli  *  p	=	(  DLG_guiData_menuIsCli  *  )qyWnd_getGuiData(  pWnd  );
	if  (  !p  )  goto  errLabel;

	CQyWnd  *  pDlgMenu  =  (  CQyWnd  *  )pWnd;
	p->iWndContentType  =  pDlgMenu->m_var.iWndContentType;


	p->iIDC_BUTTON_contact  =  IDC_BUTTON_contact;
	p->iIDC_BUTTON_group  =  IDC_BUTTON_group;

	//
	p->iIDC_BUTTON_fullScreen  =  IDC_BUTTON_fullScreen;
	//
	p->iIDC_BUTTON_viewOfflineRes  =  IDC_BUTTON_viewOfflineRes;
	//
	p->iIDC_BUTTON_testLocalAv  =  IDC_BUTTON_testLocalAv;
	p->iIDC_BUTTON_playRemoteAudio  =  IDC_BUTTON_playRemoteAudio;
	//
	p->iIDC_BUTTON_policy  =  IDC_BUTTON_policy;
	//
	p->iIDC_BUTTON_openQvw  =  IDC_BUTTON_openQvw;
	p->iIDC_BUTTON_closeQvw  =  IDC_BUTTON_closeQvw;
	//
	p->iIDC_BUTTON_conferenceQuality  =  IDC_BUTTON_conferenceQuality;

	p->iIDC_BUTTON_close  =  IDC_BUTTON_close;
	p->iIDC_BUTTON_about  =  IDC_BUTTON_about;

	p->iIDC_STATIC_meDesc  =  IDC_STATIC_meDesc;

	p->iIDCANCEL  =  IDCANCEL;

	//  2013/07/12
	p->iWndContentType_hParent  =  iWndContentType_hParent;

	//
	HWND hWndParent  =  NULL;		//  2011/02/26
	hWndParent  =  hParent;

	//
	int  iIDD  =  IDD_menu_isCli_walls;
	switch  (  iWndContentType_hParent  )  {
			case  CONST_qyWndContentType_shareDynBmps:
				  iIDD  =  IDD_menu_shareDynBmps;
				  break;
			default:
					break;
	}
	//  2016/03/02
	if  (  bApp_ts(  pQyMc  )  )  {
		iIDD  =  IDD_menu_isCli_walls_ts;
	}

	//
	if  (  DialogBoxParam(  hInst,  MAKEINTRESOURCE(  iIDD  ),  hWndParent,  dlgProc_menuIsCli,  (  LPARAM  )pWnd  )  !=  IDOK  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "showMenu_wallsBar, DialogBoxParam failed"  )  );
		#endif
		goto  errLabel;
	}

	iErr  =  0;
errLabel:
	if  (  pWnd  )  freeQyWnd(  pWnd  );
	return  iErr;
}


// CDlgMenuIsCli dialog

CDlgMenuIsCli::CDlgMenuIsCli(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgMenuIsCli::~CDlgMenuIsCli()
{
}



int  dlgSetFont_menuIsCli(  HWND  hDlg  )
{
	CDlgMenuIsCli	*	pDlg	=	(  CDlgMenuIsCli  *  )CQyWnd::FromHandle(  hDlg  );
	if  (  !pDlg  )  return  -1;
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	DLG_guiData_menuIsCli	*	p	=	&pDlg->m_var.guiData;
		G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )pFuncs->pf_get_g_guiData(  );

		int		idc;
		HWND	hCtrl;


		idc  =  p->iIDC_BUTTON_contact;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_BUTTON_group;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_BUTTON_fullScreen;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		//
		idc  =  p->iIDC_BUTTON_viewOfflineRes;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		//
		idc  =  p->iIDC_BUTTON_policy;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}




		//
		idc  =  p->iIDC_BUTTON_testLocalAv;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_BUTTON_playRemoteAudio;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}


		idc  =  p->iIDC_BUTTON_openQvw;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		idc  =  p->iIDC_BUTTON_closeQvw;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_BUTTON_conferenceQuality;
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
		idc  =  p->iIDC_BUTTON_about;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		idc  =  p->iIDC_STATIC_meDesc;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		idc  =  p->iIDCANCEL;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}


		return  0;

}

int  tmpSetRect(  RECT  &  rc  );



// CDlgMenuIsCli message handlers

int dlgMenuIsCli_OnInitDialog(  HWND  m_hWnd,  void  *  pVarParam  )
{
	int						iErr	=	-1;
	if  (  !pVarParam  )  return  -1;
	DLG_menuIsCli_var	&	m_var	=	*(  DLG_menuIsCli_var  *  )pVarParam;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	//  2010/09/03
	DWORD	dwStyle	=	GetWindowLong(  m_hWnd,  GWL_STYLE  );
	dwStyle  |=  WS_CLIPCHILDREN;
	SetWindowLong(  m_hWnd,  GWL_STYLE,  dwStyle  );

	//  2011/03/12
	::SetWindowPos(  m_hWnd,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOMOVE  |  SWP_NOSIZE  );


	#ifdef  __APP_qyMc_touchscreen__
			//  makeDlgResizable(  m_hWnd  );
	#endif

	//  CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	HWND					hDlg	=	m_hWnd;
	DLG_guiData_menuIsCli	*	p	=	&m_var.guiData;

	switch  (  m_var.guiData.iWndContentType  )  {
			case  CONST_qyWndContentType_menu_walls:  				  
				  cusDlgRes(  0,  &pQyMc->cusRes,  m_hWnd,  IDD_menu_isCli_walls  );
				  break;
			default:
					goto  errLabel;													  
	}


	MIS_CNT	*	pMisCnt	=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  pMisCnt  )  {
		TCHAR	tBuf[256];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u, %s"  ),  pMisCnt->idInfo.ui64Id,  pMisCnt->talkerDesc  );
		SetDlgItemText(  m_hWnd,  IDC_STATIC_meDesc,  tBuf  );
	}


	RECT	rc;
	::GetClientRect(  hDlg,  &rc  );
	p->w_org  =  rc.right  -  rc.left;
	p->h_org  =  rc.bottom  -  rc.top;

	if  (  !p->w_org  ||  !p->h_org  )  goto  errLabel;

	//
#if  10
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_contact  ),  &p->rcIDC_BUTTON_contact  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_contact,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_group  ),  &p->rcIDC_BUTTON_group  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_group,  2  );
	//
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_fullScreen  ),  &p->rcIDC_BUTTON_fullScreen  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_fullScreen,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_viewOfflineRes  ),  &p->rcIDC_BUTTON_viewOfflineRes  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_viewOfflineRes,  2  );
	//
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_testLocalAv  ),  &p->rcIDC_BUTTON_testLocalAv  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_testLocalAv,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_playRemoteAudio  ),  &p->rcIDC_BUTTON_playRemoteAudio  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_playRemoteAudio,  2  ); 
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_policy  ),  &p->rcIDC_BUTTON_policy  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_policy,  2  );
	//
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_openQvw  ),  &p->rcIDC_BUTTON_openQvw  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_openQvw,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_closeQvw  ),  &p->rcIDC_BUTTON_closeQvw  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_closeQvw,  2  );
	//
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_conferenceQuality  ),  &p->rcIDC_BUTTON_conferenceQuality  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_conferenceQuality,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_close  ),  &p->rcIDC_BUTTON_close  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_close,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_about  ),  &p->rcIDC_BUTTON_about  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_about,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_meDesc  ),  &p->rcIDC_STATIC_meDesc  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_meDesc,  2  );
	//
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDCANCEL  ),  &p->rcIDCANCEL  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDCANCEL,  2  );
	//
#endif

	if  (  bApp_ts(  pQyMc  )  )  //  #ifdef  __APP_qyMc_touchscreen__
	{
		G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )pFuncs->pf_get_g_guiData(  );

		tmpSetRect(  p->rcIDC_BUTTON_contact  );
		tmpSetRect(  p->rcIDC_BUTTON_group  );
		tmpSetRect(  p->rcIDC_BUTTON_fullScreen  );
		
		tmpSetRect(  p->rcIDC_BUTTON_viewOfflineRes  );		
		tmpSetRect(  p->rcIDC_BUTTON_policy  );
		
		tmpSetRect(  p->rcIDC_BUTTON_testLocalAv  );
		tmpSetRect(  p->rcIDC_BUTTON_playRemoteAudio  );
		//
		tmpSetRect(  p->rcIDC_BUTTON_openQvw  );
		tmpSetRect(  p->rcIDC_BUTTON_closeQvw  );
		//
		tmpSetRect(  p->rcIDC_BUTTON_conferenceQuality  );
		tmpSetRect(  p->rcIDC_BUTTON_close  );
		tmpSetRect(  p->rcIDC_BUTTON_about  );
		tmpSetRect(  p->rcIDC_STATIC_meDesc  );
		tmpSetRect(  p->rcIDCANCEL  );

		p->w_org  *=  pGuiData->fx;
		p->h_org  *=  pGuiData->fy;
	}  //  #endif

	//
	int		w, h;
	HWND	hParent	=	::GetParent(  hDlg  );
	if  (  !hParent  )  goto  errLabel;
	::GetWindowRect(  hParent,  &rc  );
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;

	int  iX,  iY;
	iX  =  (  rc.left  +  rc.right  )  /  2  -  p->w_org  /  2;
	iY  =  (  rc.top  +  rc.bottom  )  /  2  -  p->h_org  /  2;		
	::MoveWindow(  hDlg,  iX,  iY,  p->w_org,  p->h_org,  TRUE  );
		
	//  2014/12/07
	if  (  !bApp_ts(  pQyMc  )  )  {
		SetDlgItemText(  hDlg,  m_var.guiData.iIDC_BUTTON_close,  getResStr( 0,  &pQyMc->cusRes,  CONST_resId_closeWall  )  );
	}
	else  {
		SetDlgItemText(  hDlg,  m_var.guiData.iIDC_BUTTON_close,  getResStr( 0,  &pQyMc->cusRes,  CONST_resId_exit  )  );
	}
	
	//
	switch  (  m_var.guiData.iWndContentType  )  {
			case  CONST_qyWndContentType_menu_walls:  {				  
				  HWND			hDlgWalls	=	hParent;
				  int			iWndContentType_hDlgWalls  =  p->iWndContentType_hParent;	

				  //
				  ZONE_objs_info	*	pDlgWallsVar	=	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  hDlgWalls,  iWndContentType_hDlgWalls,  0  );
				  if  (  !pDlgWallsVar  )  goto  errLabel;
				  //
				  if  (  pFuncs->pf_bFullScreen_wnd(  hDlgWalls,  iWndContentType_hDlgWalls  )  )  {
					  SetDlgItemText(  m_hWnd,  m_var.guiData.iIDC_BUTTON_fullScreen,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_endFullScreen  )  );
					  //
					  //  m_var.guiData.m_bFullScreen_parent  =  TRUE;
				  }
				  //
				  if  (  pProcInfo->cfg.ucbPlayRemoteAudio_viewDynBmp  )  {
					  SetDlgItemText(  m_hWnd,  m_var.guiData.iIDC_BUTTON_playRemoteAudio,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_notPlayRemoteAudio  )  );
				  }
				  else  {
					  SetDlgItemText(  m_hWnd,  m_var.guiData.iIDC_BUTTON_playRemoteAudio,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_playRemoteAudio  )  );
				  }
				  //  2016/07/27
				  SetDlgItemText(  m_hWnd,  m_var.guiData.iIDC_BUTTON_viewOfflineRes,  getResStr(  0,  &pQyMc->cusRes,  ID_viewOfflineRes  )  );

			      }				  
				  break;
			default:
					break;
	}

	//MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;
	if  (  IsWindow(  pQyMc->gui.hWnd_menu  )  )  goto  errLabel;
	pQyMc->gui.hWnd_menu  =  m_hWnd;

	dlgSetFont_menuIsCli(  m_hWnd  );

	//  2011/03/29
	//  m_var.wTimerID  =  ::SetTimer(  m_hWnd,  1,  1000,  NULL  );
	//
	::ShowWindow( ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_conferenceQuality  ),  FALSE  );

	m_var.guiData.bInited  =  TRUE;
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		PostMessage(  m_hWnd,  WM_CLOSE,  0,  0  );
	}

	return iErr;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

 int  dlgMenuIsCli_OnDestroy(  HWND  hDlg,  void  *  pVarParam  )
{
	int						iErr	=	-1;
	if  (  !pVarParam  )  return  -1;
	DLG_menuIsCli_var	&	m_var	=	*(  DLG_menuIsCli_var  *  )pVarParam;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );


	//  if  (  m_var.wTimerID  )  KillTimer(  hDlg,  m_var.wTimerID  );		//  2007/12/22

	return  0;
}

#if  10
int  sizeAllControls_dlgMenuIsCli(  HWND  hWnd,  void  *  pGuiDataParam  )
{
	DLG_guiData_menuIsCli  *  p  =  (  DLG_guiData_menuIsCli  *  )pGuiDataParam;
	
	if  (  !p->w_org  ||  !p->h_org  )  return  -1;

	RECT	rc;
	GetClientRect(  hWnd,  &rc  );
	int  w,  h;
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;


	//  
	int	idc;
	int  iX,  iY,  iW,  iH;
	float  fx,  fy;
	fx  =  1.  *  w  /  p->w_org;
	fy  =  1.  *  h  /  p->h_org;

	//	
	idc  =  p->iIDC_BUTTON_contact;
	rc  =  p->rcIDC_BUTTON_contact;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_group;
	rc  =  p->rcIDC_BUTTON_group;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_fullScreen;
	rc  =  p->rcIDC_BUTTON_fullScreen;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	//
	//  2016/07/27
	idc  =  p->iIDC_BUTTON_viewOfflineRes;
	rc  =  p->rcIDC_BUTTON_viewOfflineRes;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  


	//
	idc  =  p->iIDC_BUTTON_policy;
	rc  =  p->rcIDC_BUTTON_policy;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  


	//
	idc  =  p->iIDC_BUTTON_testLocalAv;
	rc  =  p->rcIDC_BUTTON_testLocalAv;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_playRemoteAudio;
	rc  =  p->rcIDC_BUTTON_playRemoteAudio;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  


	idc  =  p->iIDC_BUTTON_openQvw;
	rc  =  p->rcIDC_BUTTON_openQvw;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_closeQvw;
	rc  =  p->rcIDC_BUTTON_closeQvw;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

#if  0
	idc  =  p->iIDC_BUTTON_conferenceQuality;
	rc  =  p->rcIDC_BUTTON_conferenceQuality;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
#endif

	idc  =  p->iIDC_BUTTON_close;
	rc  =  p->rcIDC_BUTTON_close;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_about;
	rc  =  p->rcIDC_BUTTON_about;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_meDesc;
	rc  =  p->rcIDC_STATIC_meDesc;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  


#if  10
	idc  =  p->iIDCANCEL;
	rc  =  p->rcIDCANCEL;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
#endif

	if  (  p->iIDC_BUTTON_fullScreen  )  
	{
#if  0
		idc  =  p->iIDC_BUTTON_fullScreen;
		rc  =  p->rcIDC_BUTTON_fullScreen;
		iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		MoveWindow(  GetDlgItem(  hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
#endif
	}


	return  0;
}
#endif




INT_PTR CALLBACK dlgProc_menuIsCli(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	void	*	pDlg	=	(  void  *  )GetWindowLongPtr(  hDlg,  GWLP_USERDATA  );

	UNREFERENCED_PARAMETER(lParam);
	switch  (  message  ) {
		   	case  WM_INITDIALOG:
				  pDlg  =  (  void  *  )lParam;
				  //  SetWindowLong(  hDlg,  GWLP_USERDATA,  (  LONG )pDlg  );
				  qyWnd_Attach(  pDlg,  hDlg  );
				  //
				  #ifdef  __APP_qyMc_touchscreen__
						  //  makeDlgResizable(  hDlg  );
				  #endif
				  //
#if  0
				  dlgLayout_mcClientLogon(  pDlg,  hDlg  );
				  sizeAllControls_dlgMcClientLogon(  hDlg,  (  DLG_guiData_mcClientLogon  *  )qyWnd_getGuiData(  pDlg  )  );
#endif
				  //
				  //  myDialogProc_mcClientLogon(  pDlg,  hDlg,  message,  wParam,  lParam  );

				  if  (  dlgMenuIsCli_OnInitDialog(  hDlg,  qyWnd_getVar(  pDlg  )  )  )  {
					  EndDialog(  hDlg,  -1  );
				  }
				  return (INT_PTR)TRUE;

			case  WM_ERASEBKGND:  {

				  HDC	hDc	=	GetDC(  hDlg  );
				  if  (  hDc  )  {
					  CRect rect;
					  GetClientRect(  hDlg,  rect);

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
					  GradientFill(  hDc,vert,2,&gRect,1,GRADIENT_FILL_RECT_H);

					  #endif

					  ReleaseDC(  hDlg,  hDc  );
				  }
				  }
				  return  TRUE;
				  break;

			case  WM_CTLCOLORSTATIC:  {
				  HDC	hDcStatic  =  (  HDC  )wParam;
				  HWND	hCtrl		=	(  HWND  )lParam;

				  DLG_guiData_menuIsCli  *  pGuiData  =  (  DLG_guiData_menuIsCli  *  )qyWnd_getGuiData(  pDlg  );

#if  0
				  if  (  pGuiData->iIDC_STATIC_meDesc  )  {
					  int  id  =  GetWindowLong(  hCtrl,  GWL_ID  );
					  #ifndef  __WINCE__
							   if  (  id  ==  pGuiData->iIDC_STATIC_meDesc  )  {
								   //  return  (  INT_PTR  )(  HBRUSH  )pDlg->m_brush_bk_status;								   						
								   SetBkColor(  hDcStatic,  TRANSPARENT  );
							   }
					  #endif
				  }
#endif
				  }
				  break;

			case  WM_CLOSE:  
				  EndDialog(  hDlg,  0  );				  
				  return  (  INT_PTR  )TRUE;
				  break;
			case  WM_DESTROY:
				  dlgMenuIsCli_OnDestroy(  hDlg,  qyWnd_getVar(  pDlg  )  );
				  break;
			case  WM_COMMAND:  {
				  WORD  wNotifyCode = HIWORD(wParam); 
				  WORD  wID = LOWORD(wParam); 
				  HWND  hwndCtl = (HWND) lParam;

				  HWND	hParent	=	GetParent(  hDlg  );

				  if  ( wID == IDCANCEL  )  {
					  EndDialog(hDlg, LOWORD(wParam));
					  return (INT_PTR)TRUE;
				  }
				 
				  QY_MC					*	pQyMc	=	QY_GET_GBUF(  );
				  DLG_guiData_menuIsCli  *  pGuiData  =  (  DLG_guiData_menuIsCli  *  )qyWnd_getGuiData(  pDlg  );

				  if  (  wID  ==  pGuiData->iIDC_BUTTON_contact  )  {

					 EndDialog(  hDlg,  IDOK  );

					 PostMessage(  hParent,  WM_COMMAND,  MAKEWPARAM(  ID_selectContact,  0  ),  0  );

					 return  TRUE;
				 }
				 if  (  wID  ==  pGuiData->iIDC_BUTTON_group  )  {

					 EndDialog(  hDlg,  IDOK  );

					 PostMessage(  hParent,  WM_COMMAND,  MAKEWPARAM(  ID_selectGroup,  0  ),  0  );
					 return  TRUE;
				 }
				 if  (  pGuiData->iIDC_BUTTON_fullScreen  )  {
					 if  (  wID  ==  pGuiData->iIDC_BUTTON_fullScreen  )  {
						 EndDialog(  hDlg,  IDOK  );
						 PostMessage(  hParent,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );
						 return  TRUE;
					 }
				 }
				 //  2016/07/27				 				 
				 if  (  pGuiData->iIDC_BUTTON_viewOfflineRes  )  {					 
					 if  (  wID  ==  pGuiData->iIDC_BUTTON_viewOfflineRes  )  {
						 EndDialog(  hDlg,  IDOK  );
						 PostMessage(  hParent,  WM_COMMAND,  MAKEWPARAM(  ID_viewOfflineRes,  0  ),  0  );
						 return  TRUE;
					 }
				 }
				 //
				 if  (  pGuiData->iIDC_BUTTON_policy  )  {
					 if  (  wID  ==  pGuiData->iIDC_BUTTON_policy  )  {
						 EndDialog(  hDlg,  IDOK  );
						 PostMessage(  hParent,  WM_COMMAND,  MAKEWPARAM(  ID_policy,  0  ),  0  );
						 return  TRUE;
					 }
				 }

				 //
				 if  (  pGuiData->iIDC_BUTTON_testLocalAv  )  {
					 if  (  wID  ==  pGuiData->iIDC_BUTTON_testLocalAv  )  {
						 EndDialog(  hDlg,  IDOK  );
						 //  testLocalAv(  );
						 PostMessage(  hParent,  WM_COMMAND,  MAKEWPARAM(  ID_testLocalAv,  0  ),  0  );
						 return  TRUE;
					 }
				 }
				 if  (  pGuiData->iIDC_BUTTON_playRemoteAudio  )  {
					 if  (  wID  ==  IDC_BUTTON_playRemoteAudio  )  {
						 EndDialog(  hDlg,  IDOK  );
						 PostMessage(  hParent,  WM_COMMAND,  MAKEWPARAM(  ID_playRemoteAudio,  0  ),  0  );
						 return  TRUE;
					 }
				 }
				 if  (  pGuiData->iIDC_BUTTON_conferenceQuality  )  {
					 if  (  wID  ==  pGuiData->iIDC_BUTTON_conferenceQuality  )  {
						 EndDialog(  hDlg,  IDOK  );
						 PostMessage(  hParent,  WM_COMMAND,  MAKEWPARAM(  ID_conferenceQuality,  0  ),  0  );
						 return  TRUE;
					 }
				 }
				 if  (  pGuiData->iIDC_BUTTON_close  )  {
					 if  (  wID  ==  pGuiData->iIDC_BUTTON_close  )  {
						 EndDialog(  hDlg,  IDOK  );

						 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
						 BOOL		bRet	=	TRUE;
						 
						 //  2014/12/12
						 if  (  bApp_ts(  pQyMc  )  )  {
						 #if  10	//  def  __APP_qyMc__
								int			tmpiRet; 

								if  (  !pQyMc->bGuiQuit  )  {
									if  (  !pQyMc->bQuitVerified  )  {
										if  (  pQyMc->bAskingToQuit  )  return  bRet;
										pQyMc->bAskingToQuit  =  TRUE;
										tmpiRet  =  myMessageBox(  hParent,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_doYouWantToExit  ),  _T(  "www.qycx.com"  ),  MB_YESNO  |  MB_DEFBUTTON2  );
										pQyMc->bAskingToQuit  =  FALSE;
										if  (  tmpiRet  !=  IDYES  )  return  bRet;
										pQyMc->bQuitVerified  =  TRUE;
									}
								}

								PostMessage(  pQyMc->gui.hMainWnd,  WM_COMMAND,  MAKEWPARAM(  ID_qyQuitMainWnd,  0  ),  0  );

								return  TRUE;
						 #endif
						 }

						 PostMessage(  hParent,  WM_CLOSE,  0,  0  );
						 return  TRUE;
					 }
				 }
				 if  (  pGuiData->iIDC_BUTTON_about  )  {
					 if  (  wID  ==  pGuiData->iIDC_BUTTON_about  )  {
						 EndDialog(  hDlg,  IDOK  );

						 if  (  !bApp_ts(  pQyMc  )  )  {  //   #ifdef  __APP_qyMc__								 
							 PostMessage(  hParent,  WM_COMMAND,  MAKEWPARAM(  ID_about,  0  ),  0  );
							 return  TRUE;
						 }  //  #endif

						 PostMessage(  pQyMc->gui.hMainWnd,  WM_COMMAND,  MAKEWPARAM(  ID_about,  0  ),  0  );
						 return  TRUE;
					 }
				 }
				 //  2015/11/30
				 if  (  pGuiData->iIDC_BUTTON_openQvw  )  {
					 if  (  wID  ==  pGuiData->iIDC_BUTTON_openQvw  )  {
						 EndDialog(  hDlg,  IDOK  );
						 PostMessage(  hParent,  WM_COMMAND,  MAKEWPARAM(  ID_openQvw,  0  ),  0  );
						 return  TRUE;
					 }
				 }
				 if  (  pGuiData->iIDC_BUTTON_closeQvw  )  {
					 if  (  wID  ==  pGuiData->iIDC_BUTTON_closeQvw  )  {
						 EndDialog(  hDlg,  IDOK  );
						 PostMessage(  hParent,  WM_COMMAND,  MAKEWPARAM(  ID_closeQvw,  0  ),  0  );
						 return  TRUE;
					 }
				 }

				 }
				 break;

			case  WM_SIZE:  {
				  sizeAllControls_dlgMenuIsCli(  hDlg,  qyWnd_getGuiData(  pDlg  )  );
				  }
				  break;

			default:

					break;
	}




	return (INT_PTR)FALSE;
}
