

#include	"stdafx.h"
#include	<stddef.h>
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

#include	"qyMcMainWndProc.h"
#include	"qyMc_tsDlg_noMfc.h"
#include	"funcsForIsCliHelp.h"
#include	"isCliHelpPublic.h"
#include	"dlgtalkproc.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcCmdProc.h"
#include	"qyAvRecordPublic.h"
#include	"tmpCeLib.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliD3dPublic.h"
#include	"qyMessengerHelpPublic.h"

#include	"avConsole_open.h"
#include	"isCliExPublic.h"

//
int  displayNotification_talk_ts(  HWND  hDlg,  void  *  pGuiDataParam,  LPCTSTR  hint  )
{
	DLG_guiData_talk	*	pGuiData  =  (  DLG_guiData_talk  *  )pGuiDataParam;	//  qyWnd_getGuiData(  pWnd  );
	if  (  !pGuiData  )  return  -1;
	//  SetDlgItemText(  hDlg,  pGuiData->iIDC_BUTTON_status,  hint  );
	
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
#ifndef  __DEBUG__
	SetDlgItemText(  pProcInfo->g_hVWall,  IDC_BUTTON_bar,  hint  );
#endif

	return  0;
}


 void  *  g_pDlgWallsVar_ts  =  NULL;


 #ifdef  __APP_qyMc_touchscreen__

 void  *  getZoneObjsInfo_ts(  HWND  hDlgWalls,  int  iWndContentType  )
{
#if  0

	CqyMc_tsDlg  *  pDlgWalls  =  (  CqyMc_tsDlg  *  )CWnd::FromHandlePermanent(  hDlgWalls  );
	if  (  !pDlgWalls  )  return  NULL;

	return  &pDlgWalls->var.wall;
#endif
	if  (  iWndContentType  !=  CONST_qyWndContentType_ts_main  )  {
#ifdef  __DEBUG__
		traceLog(  _T(  "getDlgWallsVar_ts: iWndContentType err, %d"  ),  iWndContentType  );
#endif
		return  NULL;
	}

	if  (  !IsWindow(  hDlgWalls  )  )  return  NULL;
	return  g_pDlgWallsVar_ts;
}



#endif

 int  sndMsgRetrieveCuctomerServiceObjListReq_qmc(  MIS_CNT  *  pMisCnt  )
{
	int							iErr								=	-1;
#if 0
	QY_MC					*	pQyMc								=	QY_GET_GBUF(  );
	IM_L_STREAM					stream;
	unsigned  int				len;

	//
	pMisCnt->retrieveCustomerServiceObjList.dwLastTickCnt  =  GetTickCount(  );

	//
	RETRIEVE_customerServiceObjList_req		req;
	 
	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_retrieveCustomerServiceObjListReq;
	//  req.usMaxContactUpdateInfosPerSnd  =  1;	//  

	memset(  &stream,  0,  sizeof(  stream  )  );
	stream.uiType  =  CONST_imCommType_lStream;
	stream.uiContentType  =  req.uiType;
	len  =  sizeof(  stream.buf  );
	if  (  retrieveCustomerServiceObjListReq2Stream(  stream.uiContentType,  &req,  stream.buf,  &len  )  )  goto  errLabel;
	stream.ulStreamLen  =  len;
	len  +=  offsetof(  IM_L_STREAM,  buf  ); 

	MACRO_prepareForTran(  );

	if  (  postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_refreshImObjListReq, tStartTran,  uiTranNo,  0,  (  char  *  )&stream,  len,  NULL,  NULL,  CONST_channelType_talking,  NULL,  FALSE  )  )  goto  errLabel;
#endif

	iErr  =  0;
errLabel:
	return  iErr;
}

CqyMc_tsDlg::CqyMc_tsDlg()	// standard constructor
{
	memset(  &var,  0,  sizeof(  var  )  );

	//
	CQyWnd  *  pBase  =  this;
	pBase->m_var.iWndContentType  =  CONST_qyWndContentType_ts_main;
}

CqyMc_tsDlg::~CqyMc_tsDlg(  )
{
}

INT_PTR CALLBACK dlgProc_ts_main(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CqyMc_tsDlg  *  pDlg  =  (  CqyMc_tsDlg  *  )GetWindowLongPtr(  hDlg,  GWLP_USERDATA  );
	QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();


	switch  (  uMsg  )  {
			case  WM_INITDIALOG:  {
				  pDlg  =  (  CqyMc_tsDlg  *  )lParam;
				  if  (  !pDlg  )  goto  errLabel;

				  qyWnd_Attach(  pDlg,  hDlg  );
				  
				  pDlg->OnInitDialog(  );		
			      }
				  return (INT_PTR)TRUE;
				  break;
			case  CONST_qyWm_postComm:  {
				  if  (  !pDlg  )  goto  errLabel;
				  pDlg->OnQyPostComm(  wParam,  lParam  );
				  }
				  return  TRUE;
				  break;
			case  CONST_qyWm_trayNotify:  {
				  if  (  !pDlg  )  goto  errLabel;
				  pDlg->OnQyTrayNotify(  wParam,  lParam  );
				  return  TRUE;
				  }
				  break;
			case  CONST_qyWm_graphNotify_mediaFile:  {
				  if  (  !pDlg  )  goto  errLabel;
				  pDlg->OnQyGraphNotify_mediaFile(  wParam,  lParam  );
				  return  TRUE;
				  }
				  break;
			case  CONST_qyWm_graphNotify_mediaDevice:  {
				  if  (  !pDlg  )  goto  errLabel;
				  pDlg->OnQyGraphNotify_mediaDevice(  wParam,  lParam  );
				  return  TRUE;
				  }
				  break;

			case  WM_SIZE:  {
				  UINT  nType  =  wParam;
				  int  cx  =  LOWORD(  lParam  );
				  int  cy  =  HIWORD(  lParam  );
				  //
				  if  (  !pDlg  )  goto  errLabel;
				  //
				  pDlg->OnSize(  nType,  cx,  cy  );
				  }
				  break;
			case  WM_MOVE:  {
				  int  x  =  LOWORD(  lParam  );
				  int  y  =  HIWORD(  lParam  );
				  if  (  !pDlg  )  goto  errLabel;
				  pDlg->OnMove(  x,  y  );				  
				  }
				  break;
			case  WM_MOVING:  {
				  UINT fwSide  =  0;
				  LPRECT  pRect  =  (  LPRECT  )lParam;
				  if  (  !pDlg  )  goto  errLabel;
				  pDlg->OnMoving(  fwSide,  pRect  );
				  }
				  break;

			case  WM_COMMAND:  {
				  WORD  wNotifyCode = HIWORD(wParam); 
				  WORD  wID = LOWORD(wParam); 
				  HWND  hwndCtl = (HWND) lParam;

				  if  (  !pDlg  )  goto  errLabel;

				  if  (  wID  ==  IDCANCEL  )  {
					  pDlg->OnCancel(  );
					  return  TRUE;
				  }

				  if  (  wID  ==  IDC_BUTTON_contact  )  {
					  pDlg->OnBnClickedButtoncontact(  );
					  return  TRUE;		
				  }
				  if  (  wID  ==  IDC_BUTTON_group  )  {
					  pDlg->OnBnClickedButtongroup(  );
					  return  TRUE;
				  }
				  if  (  wID  ==  IDC_BUTTON_customerServiceOfficer0  )  {
					  pDlg->OnBnClickedButtoncustomerserviceofficer0(  );
					  return  TRUE;
				  }
				  if  (  wID  ==  IDC_BUTTON_bar  )  {
					  pDlg->OnBnClickedButtonbar(  );
					  return  TRUE;
				  }
#if  0  //  2017/01/05
				  if  (  wID  ==  ID_about  )  {
					  HWND  hParent  =  hDlg;
					  if  (  bApp_ts_3d(  pQyMc  )  )  {
						  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
						  if  (  pGBuf  
							  &&  IsWindow(  pGBuf->hWall_d3d  )  )
						  {
							  hParent  =  pGBuf->hWall_d3d;
						  }
					  }
					  myOnAppAbout(  hParent  );
					  return  TRUE;
				  }
#endif
				  
				  //	ON_COMMAND_RANGE(  ID_MENU_isCmd_min,  ID_MENU_isCmd_max,  OnIsCmd  )
				  if  (  wID  >=  ID_MENU_isCmd_min  &&  wID  <=  ID_MENU_isCmd_max  )  {
					  pDlg->OnIsCmd(  wID  );
					  return  TRUE;
				  }


				  traceLog(  _T(  "dlgProc_ts_main: unprocessed id %d"  ),  wID  );

				  return  TRUE;
				  }
				  break;

			case  WM_COPYDATA:  {  //  2017/01/09
				  COPYDATASTRUCT  *  pCopyData  =  (  COPYDATASTRUCT  *  )lParam;
				  AvConsole_req_head	*	pReq  =  (  AvConsole_req_head  *  )pCopyData->lpData;
				  //
#if  0
				  __declspec(  dllexport  )  int  do_avConsole_req(  AvConsole_req_head  *  pReq  );

				  //
				  do_avConsole_req(  pReq  );
#endif
				  //
				  return  847;
				  }
				  break;

			case  WM_TIMER:  {
				  if  (  !pDlg  )  goto  errLabel;
				  UINT  nIDEvent  =  (  UINT  )wParam;
				  pDlg->OnTimer(  nIDEvent  );
				  return  TRUE;				  
				  }
				  break;

			case  WM_CLOSE:  {
				  if  (  !pDlg  )  goto  errLabel;
				  pDlg->OnClose(  );
				  return  TRUE;
				  }
				  break;

			case  WM_NCDESTROY:  {
				  OutputDebugString(  _T(  "WM_NCDESTROY\n"  )  );
				  //  if  (  IsWindow(  hDlg  )  )  OutputDebugString(  _T(  "wnd\n"  )  );
				  //  else  OutputDebugString(  _T(  "false\n"  )  );
				  //
				  pDlg->PostNcDestroy(  );
				  //
				  PostQuitMessage(  0  );
				  }
				  break;
			case  WM_DESTROY:  {
				  OutputDebugString(  _T(  "WM_DESTROY\n"  )  );
				  if  (  !pDlg  )  goto  errLabel;
				  pDlg->OnDestroy(  );
				  }
				  break;
			default:
					break;
	}

errLabel:

	return (INT_PTR)FALSE;
}

//
 BOOL	CqyMc_tsDlg::Create(const RECT& rect)
{
	BOOL	bRet	=	FALSE;

	HINSTANCE	hInst  =  NULL;
	hInst  =  get_my_hInst(var.pQyMc  );
	HWND hWndParent  =  NULL;		//  2011/02/26
	hWndParent  =  NULL;	//  hParent;

#if  0
	if  (  DialogBoxParam(  hInst,  MAKEINTRESOURCE(  IDD_ts_main  ),  hWndParent,  dlgProc_ts_main,  (  LPARAM  )this  )  !=  IDOK  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "showMenu_wallsBar, DialogBoxParam failed"  )  );
		#endif
		goto  errLabel;
	}
#endif

	HWND  hWnd  =  NULL;
		
	hWnd = CreateDialogParam(  hInst,  MAKEINTRESOURCE(IDD_ts_main), hWndParent,  dlgProc_ts_main,  (  LPARAM  )this   );
	if  (  !hWnd  )  goto  errLabel;



	bRet  =  TRUE;

errLabel:
	return  bRet;
}

BOOL	CqyMc_tsDlg::bQuitDlg(  )
{
	BOOL		bRet	=	FALSE;
	QY_MC* pQyMc = var.pQyMc;// QY_GET_GBUF();

	HWND  hMainWnd  =  m_hWnd;
	
	if  (  !pQyMc->bGuiQuit  )  {	
		mainWnd_OnQyQuitMainWnd(  hMainWnd,  &var  );	
		return  FALSE;		
	}

	if  (  mainWnd_OnClose(  hMainWnd,  &var  )  )  return  FALSE;

	::DestroyWindow(  m_hWnd  );
	bRet  =  TRUE;	
errLabel:
	return  bRet;
}

 void  CqyMc_tsDlg::endFullScreen(  )
 {

	 ZONE_objs_info	&	m_var	=	var.wall;

	if  (  m_var.m_bFullScreen  )  {
		m_var.m_bFullScreen  =  FALSE;
		

		//  2012/07/07
		restoreWndBorder(  m_hWnd,  &m_var.m_fullScreenInfo.hOldMenu,  &m_var.m_fullScreenInfo.lOldStyle  );

		//
		ShowWindow(  m_hWnd,  SW_HIDE  );
		memcpy(  &m_var.layoutParam,  &m_var.m_oldLayoutParam,  sizeof(  m_var.layoutParam  )  );
		mySetWindowPlacement(  m_hWnd,  &m_var.m_oldWndPlacement  );
		ShowWindow(  m_hWnd,  SW_RESTORE  );				

	}

 }
 
 BOOL CqyMc_tsDlg::OnInitDialog()
{

	// Add "About..." menu item to system menu.

#if  0
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
#endif
#if  10
	HINSTANCE  hInst  =  get_my_hInst(var.pQyMc  );
	HICON  hIcon  =  LoadIcon(  hInst,  MAKEINTRESOURCE(  IDI_SMALL  )  );
	SetClassLongPtr(  m_hWnd,  GCLP_HICON,  (  LONG  )hIcon  );
#endif

	// TODO: Add extra initialization here
	//
	//  set_m_pMainWnd(  this  );

	// TODO: Add extra initialization here
	int  iErr  =  -1;
	QY_MC* pQyMc = var.pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//
	var.common.pQyMc  =  pQyMc;

	//
	if  (  initVar_onCreate_mainFrame(  0,  this->m_hWnd,  &this->var  )  )  {
		goto  errLabel;
	}

#if  0
	DWORD	dwStyle	=	GetWindowLong(  m_hWnd,  GWL_STYLE  );
	dwStyle  |=  WS_CLIPCHILDREN;
	SetWindowLong(  m_hWnd,  GWL_STYLE,  dwStyle  );
#endif

	//  WND_guiData_main	*	p	=	&var.common.guiData;
	DLG_guiData_wall	*	p	=	&var.wall.guiData;
	p->iIDC_BUTTON_contact  =  IDC_BUTTON_contact;
	p->iIDC_BUTTON_group  =  IDC_BUTTON_group;
	p->iIDC_BUTTON_customerServiceOfficer0  =  IDC_BUTTON_customerServiceOfficer0;
	p->iIDC_BUTTON_bar  =  IDC_BUTTON_bar;

	//
	//  p->pf_displayNotification_mainWnd  =  displayNotification_mainWnd;



	HWND	hDlg  =  this->m_hWnd;
	RECT	rc;
	//  ::GetWindowRect(  hDlg,  &rc  );
	::GetClientRect(  hDlg,  &rc  );
	p->w_org  =  rc.right  -  rc.left;
	p->h_org  =  rc.bottom  -  rc.top;

	if  (  !p->w_org  ||  !p->h_org  )  goto  errLabel;

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_contact  ),  &p->rcIDC_BUTTON_contact  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_contact,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_group  ),  &p->rcIDC_BUTTON_group  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_group,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_customerServiceOfficer0  ),  &p->rcIDC_BUTTON_customerServiceOfficer0  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_customerServiceOfficer0,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_bar  ),  &p->rcIDC_BUTTON_bar  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_bar,  2  );

	//
	var.wall.oldLayout.iEdge_l  =  p->rcIDC_BUTTON_contact.left;
	var.wall.oldLayout.iEdge_t  =  p->rcIDC_BUTTON_contact.top;
	var.wall.oldLayout.iW_btn  =  p->rcIDC_BUTTON_contact.right  -  p->rcIDC_BUTTON_contact.left;
	var.wall.oldLayout.iH_btn  =  p->rcIDC_BUTTON_contact.bottom  -  p->rcIDC_BUTTON_contact.top;
	var.wall.oldLayout.iY_spacing  =  p->rcIDC_BUTTON_group.top  -  p->rcIDC_BUTTON_contact.bottom;

	//
	{
		G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )get_g_guiData(  );

		HWND	hCtrl;
		int		idc;
		idc  =  p->iIDC_BUTTON_contact;
		hCtrl  =  ::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		idc  =  p->iIDC_BUTTON_group;
		hCtrl  =  ::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		idc  =  p->iIDC_BUTTON_customerServiceOfficer0;
		hCtrl  =  ::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}
		idc  =  p->iIDC_BUTTON_bar;
		hCtrl  =  ::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_bar,  TRUE  );
			}
		}
	}


#ifdef  __DEBUG__

#endif

	BOOL  bShow  =  TRUE;
	//
	if  (  bApp_ts_3d(  pQyMc  )  )  {
		bShow  =  FALSE;
	}
	//
	if  (  pProcInfo->qyShowMainWndFunc(  this->m_hWnd,  &var,  bShow  )  )  {
		::ShowWindow(  this->m_hWnd,  SW_HIDE  );
		goto  errLabel;
	}
	//
	if  (  !bUse_imObjView_as_guiWnd(  )  )  {
		if  (  bApp_ts_3d(  pQyMc  )  )  {
			dyn_createConsoleWall(  pQyMc->pGBuf_d3d  );
			//
			GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
			if  (  !pGBuf  )  goto  errLabel;

			HWND  hWnd  =  pGBuf->hWall_d3d;
			if  (  !IsWindow(  hWnd  )  )  {
				goto  errLabel;
			}

			//
			pQyMc->gui.hGuiWnd  =  hWnd;
			  pQyMc->gui.iWndContentType_hGuiWnd  =  CONST_qyWndContentType_consoleWall;
			}
		}
	else  {

		  //	
		  HWND  hParent  =  NULL;	
		  //	
		  if  (  !bViewImObjView_isCli(  hParent  )  )  goto  errLabel;
		  //
		  pQyMc->gui.hGuiWnd  =  pProcInfo->hWnd_imObjView;
		  pQyMc->gui.iWndContentType_hGuiWnd  =  CONST_qyWndContentType_imObjView_cli;
	}

	//  2011/03/23
	MIS_CNT	*	pMisCnt	=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	TCHAR		tBuf[128];
#if  0
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u, %s. ( Menu )"  ),  pMisCnt->idInfo.ui64Id,  pMisCnt->talkerDesc  );
	::SetDlgItemText(  m_hWnd,  p->iIDC_BUTTON_bar,  tBuf  );
	if  (  bSupported_devAuth(  )  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMisCnt->idInfo.ui64Id  );
		if  (  pMisCnt->talkerDesc[0]  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s"  ),  tBuf,  pMisCnt->talkerDesc  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  pQyMc->cfg.qyMcTitle  );
		}
	else  {
		  safeWcsnCpy(  pQyMc->cfg.qyMcTitle,  tBuf,  mycountof(  tBuf  )  );
	}
#endif
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%d"  ),  CONST_wndTitle_qisTsMain_prefix,  pQyMc->appParams.iSeqNoSelected_appObjPrefix  );
	if  (  tBuf[0]  )  {
		::SetWindowText(  m_hWnd,  tBuf  );
	}

	//
	::SetForegroundWindow(  this->m_hWnd  );

	//		
	// TODO:  Add extra initialization here
	//  this->m_brush_fullScreen_dlg.CreateSolidBrush(  CONST_bkColor_fullScreen_walls  );

	//
	p->bInited  =  TRUE;

	//  2013/06/14
	g_pDlgWallsVar_ts  =  &var.wall;

	//
	//MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;
#if  0
	pProcInfo->g_hVWall  =  m_hWnd;
	pProcInfo->iWndContentType_g_hVWall  =  this->getWndContentType(  );
#endif

	//  2011/04/04
	if  (  bSupported_devAuth(  )  )  {
		traceLog(  _T(  "to sndMsgRetrieveCuctomerServiceObjListReg_qmc"  )  );
		if  (  sndMsgRetrieveCuctomerServiceObjListReq_qmc(  pMisCnt  )  )  goto  errLabel;

	}

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		::PostMessage(  m_hWnd,  WM_CLOSE,  0,  0  );
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CqyMc_tsDlg::OnCancel()
{
	//  bQuitDlg(  );
#ifdef  __DEBUG__
	traceLog(  _T(  "CQyMc_tsDlg::OnCancel"  )  );
#endif
}


void CqyMc_tsDlg::OnClose()
{
	if  (  mainWnd_OnClose(  this->m_hWnd,  &var  )  )  return;

	//
	bQuitDlg(  );
}

void CqyMc_tsDlg::OnDestroy()
{
	{
		G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )get_g_guiData(  );
		if  (  pGuiData->hFont_list  )  {
			DeleteObject(  pGuiData->hFont_list  );  pGuiData->hFont_list  =  NULL;
		}
#if  0
		if  (  pGuiData->hFont_list_text  )  {
			DeleteObject(  pGuiData->hFont_list_text  );  pGuiData->hFont_list_text  =  NULL;
		}
#endif
		//  2017/10/01
		if  (  pGuiData->hFont_list_dlgTalk_peerInfo  )  {
			DeleteObject(  pGuiData->hFont_list_dlgTalk_peerInfo  );  pGuiData->hFont_list_dlgTalk_peerInfo  =  NULL;
		}
		//
		if  (  pGuiData->hFont_static  )  {
			DeleteObject(  pGuiData->hFont_static  );  pGuiData->hFont_static  =  NULL;
		}
		if  (  pGuiData->hFont_btn  )  {
			DeleteObject(  pGuiData->hFont_btn  );  pGuiData->hFont_btn  =  NULL;
		}
		if  (  pGuiData->hFont_bar  )  {
			DeleteObject(  pGuiData->hFont_bar  );  pGuiData->hFont_bar  =  NULL;
		}
		if  (  pGuiData->hFont_menu  )  {
			DeleteObject(  pGuiData->hFont_menu  );  pGuiData->hFont_menu  =  NULL;
		}
	}

	exitVar_onDestroy_mainFrame(  0,  this->m_hWnd,  &var  );

	//  CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}

void CqyMc_tsDlg::OnSize(UINT nType, int cx, int cy)
{
	//  CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

#ifdef  __DEBUG__
		RECT	rc;
		::GetWindowRect(  m_hWnd,  &rc  );
		RECT	cliRc;
		::GetClientRect(  m_hWnd,  &cliRc  );
		traceLog(  _T(  "CqyMc_touchscreenDlg: OnSize, w %d, h %d, cliRc.w %d, cliRc.h %d"  ),  rc.right  -  rc.left,  rc.bottom  -  rc.top,  cliRc.right  -  cliRc.left,  cliRc.bottom  -  cliRc.top  );

#endif

	//
	clearNotification(  );

	// TODO: Add your message handler code here
	//  sizeAllControls_dlg_qyMc(  this->m_hWnd,  var.common  );

	//
	sizeAllControls_dlgWalls(  this->m_hWnd,  this->getWndContentType(  ),  &var.wall  );

}


void CqyMc_tsDlg::Onfullscreen()
 {
	 // TODO: Add your command handler code here
	 ZONE_objs_info	&	m_var	=	var.wall;

	 if  (  m_var.m_bFullScreen  )  return;

	 //  2012/07/07
	 makeWndNoBorder(  m_hWnd,  FALSE,  &m_var.m_fullScreenInfo.hOldMenu,  &m_var.m_fullScreenInfo.lOldStyle  );

	 //
	 myGetWindowPlacement(  m_hWnd,  &m_var.m_oldWndPlacement  );
	 memcpy(  &m_var.m_oldLayoutParam,  &m_var.layoutParam,  sizeof(  m_var.m_oldLayoutParam  )  );
	 memset(  &m_var.layoutParam,  0,  sizeof(  m_var.layoutParam  )  );
	 //
	 RECT	wndRect;
	 GetWindowRect(  m_hWnd,  &wndRect  );
	 RECT	clientRect;
	 //  RepositionBars(  0,  0xffff,  AFX_IDW_PANE_FIRST,  reposQuery,  &clientRect  );
	 GetClientRect(  m_hWnd,  &clientRect  );
	 //  ClientToScreen(  m_hWnd,  &clientRect  );
	 MapWindowPoints(  m_hWnd,  NULL,  (  LPPOINT  )&clientRect,  2  );
	 //
	 int  nFullWidth  =  GetSystemMetrics(  SM_CXSCREEN  );
	 int  nFullHeight  =  GetSystemMetrics(  SM_CYSCREEN  );

	 //
	 HMONITOR	hMonitor;
	 POINT		point;
	 point.x  =  (  wndRect.left  +  wndRect.right  )  /  2;
	 point.y  =  (  wndRect.top  +  wndRect.bottom  )  /  2;
	 hMonitor  =  MonitorFromPoint(  point,  MONITOR_DEFAULTTONEAREST  );

	 MONITORINFO mi;
	 mi.cbSize = sizeof(mi);
	 GetMonitorInfo(hMonitor, &mi);

	 RECT	rc;
#if  0
    if (flags & MONITOR_WORKAREA)
		 rc = mi.rcWork;
		 tBuf[0]  =  0;
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "mi.rcWork:l-%d,t-%d,r-%d,b-%d"  ),  rc.left,  rc.top,  rc.right,  rc.bottom  );
		 myMessageBox(  NULL,  tBuf,  _T( "mi.rcWork"  ),  MB_YESNO  );
	else
#endif   
	 rc = mi.rcMonitor;

	 nFullWidth  =  rc.right  -  rc.left;
	 nFullHeight  =  rc.bottom  -  rc.top;


	 //
	 m_var.m_fullScreenRect.left  =  wndRect.left  -  clientRect.left  +  rc.left;
	 m_var.m_fullScreenRect.top  =  wndRect.top  -  clientRect.top;
	 m_var.m_fullScreenRect.right  =  wndRect.right  -  clientRect.right  +  rc.left  +  nFullWidth;
	 m_var.m_fullScreenRect.bottom  =  wndRect.bottom  -  clientRect.bottom  +  nFullHeight;
	 //
	 m_var.m_bFullScreen  =  TRUE;
	 //
	 WINDOWPLACEMENT	wndPl;
	 wndPl.length  =  sizeof(  WINDOWPLACEMENT  );
	 wndPl.flags  =  0;
	 wndPl.showCmd  =  SW_SHOWNORMAL;
	 wndPl.rcNormalPosition  =  m_var.m_fullScreenRect;
	 mySetWindowPlacement(  m_hWnd,  &wndPl  ); 

	 //
	 InvalidateRect(  m_hWnd,  NULL,  TRUE  );	 
}


void CqyMc_tsDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	//  CDialogEx::OnMoving(fwSide, pRect);

	// TODO: Add your message handler code here
	sizeAllControls_dlgWalls(  this->m_hWnd,  this->getWndContentType(  ),  &var.wall  );

}


void CqyMc_tsDlg::OnMove(int x, int y)
{
	//  CDialogEx::OnMove(x, y);

	// TODO: Add your message handler code here
	sizeAllControls_dlgWalls(  this->m_hWnd,  this->getWndContentType(  ),  &var.wall  );

}



void CqyMc_tsDlg::OnTimer(UINT_PTR nIDEvent)
{
	//
#ifdef  __DEBUG__
	//
	//traceLog((TCHAR*)_T("before mainWnd_OnTimer.l775"));
	//
#endif 

	// TODO: Add your message handler code here and/or call default
	if  (  mainWnd_OnTimer(  this->m_hWnd,  &var,  nIDEvent  )  )  return;

	//
	if  (  !var.wall.guiData.ucbHideBar  )  {
		if  (  var.wall.m_bFullScreen  )  
		{
			if  (  GetTickCount(  )  -  var.wall.dwTickCnt_lastMouseMove  >  10000  )  {
				traceLog(  _T(  "OnTimer: before hideBar"  )  );
				var.wall.guiData.ucbHideBar  =  TRUE;
				var.wall.dwTickCnt_hide_bar  =  GetTickCount(  );

				sizeAllControls_dlgWalls(  this->m_hWnd,  this->getWndContentType(  ),  &var.wall  );

				traceLog(  _T(  "OnTimer: after hideBar"  )  );
			}
		}
	}


	//  2015/06/03
	QY_MC* pQyMc = var.pQyMc;// QY_GET_GBUF();
	if  (  !bUse_imObjView_as_guiWnd(  )  )  {
		if  (  bApp_ts_3d(  pQyMc  )  )  {
			GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
			if  (  !pGBuf  )  goto  errLabel;
	
			HWND  hWnd  =  pGBuf->hWall_d3d;	
			if  (  hWnd  &&  !IsWindow(  hWnd  )  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tsMain: no walld3d, quit now"  )  );
				::PostMessage(  m_hWnd,  WM_COMMAND,  MAKEWPARAM(  ID_qyQuitMainWnd,  0  ),  0  );					
				goto  errLabel;		
			}
		}
	}


	//
		//  2018/10/30  
		if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )  {
			if (  pQyMc->bLogon   )  {
				MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
				//					
				if  (  pMisCnt->refreshImObjRules.tLastRefreshedTime  )  {

					static  BOOL  bDone  =  FALSE;
					if  (  !bDone  )  {
						bDone  =  TRUE;
						  int  iWndContentType;
						  iWndContentType  =  CONST_qyWndContentType_vWall;
						  //viewVWall(  ::GetDesktopWindow(  ),  _T(  ""  ),  0,  TRUE,  NULL,  FALSE,  NULL  );
						  viewVWall(  ::GetDesktopWindow(  ),  _T(  ""  ),  0,  FALSE,  NULL,  FALSE,  NULL  );
					}

				}
			}
		}


errLabel:
			
		//  CDialogEx::OnTimer(nIDEvent);

		//
		return;
}



LRESULT  CqyMc_tsDlg::OnQyPostComm( WPARAM  wParam, LPARAM  lParam )
{
	return  mainWnd_OnQyPostComm(  this->m_hWnd,  &this->var,  wParam,  lParam  );
}

 LRESULT CqyMc_tsDlg::OnQyTrayNotify(  WPARAM  wParam,  LPARAM  lParam  )
{

	mainWnd_OnQyTrayNotify(  m_hWnd,  &var,  wParam,  lParam  );

	return  0;
}


   LRESULT CqyMc_tsDlg::OnQyGraphNotify_mediaFile(  WPARAM  wParam,  LPARAM  lParam  )
{
	int						iErr			=	-1;
	QY_MC* pQyMc = var.pQyMc;// QY_GET_GBUF();
	QY_SERVICEGUI_INFO	*	pSci			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;
	MC_VAR_isCli			*	pProcInfo		=	(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;

	int						iIndex_sharedObj	=	(  int  )lParam;

	QY_SHARED_OBJ		*	pSharedObj	=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	CAP_procInfo_bmpU	*	pCapBmp	=	getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  CONST_capType_mediaFile  );
	if  (  !pCapBmp  )  goto  errLabel;
#if  0
	QM_SHM_CMD			*	pShmCmd	=	getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pSharedObj->iIndex_shmCmd  );
	if  (  !pShmCmd  )  goto  errLabel;
#endif
	bool  bLooping  =  true;
	bool  bPlayThrough  =  true;

	handleGraphEvent_mediaFile(  pSharedObj->pShareMediaObj,  TRUE,  bLooping,  bPlayThrough  );

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		traceLogA(  "CMainFrame::OnQyGraphNotify failed"  );
	}

	return  0;
}

 LRESULT CqyMc_tsDlg::OnQyGraphNotify_mediaDevice(  WPARAM  wParam,  LPARAM  lParam  )
{
	return  mainWnd_OnQyGraphNotify_mediaDevice(  var.pQyMc,m_hWnd,  &var,  wParam,  lParam  );
}

void CqyMc_tsDlg::OnIsCmd(  UINT nID  )
{
	QY_MC* pQyMc = var.pQyMc;// QY_GET_GBUF();
	
	//
	if  (  nID  ==  ID_qyRefresh  )  {
		qyMcRefreshAll(  );
		return;
	}

	switch  (  nID  )  {
			case  ID_qyShowWnd:
				  //mainWnd_OnQyShowMainWnd(  this->m_hWnd  );
				  PostMessage(  pQyMc->gui.hGuiWnd,  WM_COMMAND,  MAKEWPARAM(  nID,  0  ),  0  );
				  break;
			case  ID_about:  {
				  //
				  //  myOnAppAbout(  m_hWnd  );
				  PostMessage(  pQyMc->gui.hGuiWnd,  WM_COMMAND,  MAKEWPARAM(  nID,  0  ),  0  );
				  }
				  break;
			case  ID_qyQuitMainWnd:
				  mainWnd_OnQyQuitMainWnd(  this->m_hWnd,  &var  );				  
				  break;
			case  ID_selectContact:  {
				#if  0
				  DLG_guiDataParam_objs		param;
				  memset(  &param,  0,  sizeof(  param  )  );
				  param.uiType  =  CONST_objType_messenger;
				  if  (  !showDlgObjs(  pQyMc->g_hInst,  m_hWnd,  &param  )  )  {
					  talkToMessenger(  param.o.ui64Id_selected,  FALSE,  TRUE,  NULL  );					 
				  }
				#endif
				  //  2015/06/02
				  this->OnBnClickedButtoncontact(  );
				  }
				  break;
			case  ID_selectGroup:  {
				#if  0
				  DLG_guiDataParam_objs	param;
				  memset(  &param,  0,  sizeof(  param  )  );
				  param.uiType  =  CONST_objType_imGrp;
				  if  (  !showDlgObjs(  pQyMc->g_hInst,  m_hWnd,  &param  )  )  {
					  talkToMessenger(  param.o.ui64Id_selected,  FALSE,  TRUE,  NULL  );
				  }				  
				#endif
				  //  2015/06/02
				  this->OnBnClickedButtongroup(  );
				  }
				  break;
			case  ID_testLocalAv:
				  testLocalAv(  m_hWnd  );
				  break;
			case  ID_policy:  {
#if  0
				  CDlgPolicyIsClient	dlg;				
				  dlg.DoModal(  );
#endif
				  showDlgPolicyIsClient(  m_hWnd  );
				  }
				  break;
			case  ID_conferenceQuality:  {
#if  0
				  CDlgPolicyAv		dlg(  this  );
				  dlg.bSetDlgInfo(  CONST_capType_av,  0,  TRUE  );
				  if  (  dlg.DoModal(  )  ==  IDOK  )  {
				  }
#endif
				  if  (  showDlgPolicyAv(  m_hWnd,  CONST_capType_av,  0,  CONST_capUsage_conf  )  ==  IDOK  ){
				  }
				  }
				  break;
			case  ID_msg:  {
#if  0
				  CDlgMsgList	dlg(  this  );
				  dlg.DoModal(  );
#endif
				  showDlgMsgList(  m_hWnd,  NULL,  NULL  );
				  }
				  break;

				  //				  	
			case  ID_fullScreen:
				  if  (  var.wall.m_bFullScreen  )  this->endFullScreen(  );
				  else  this->Onfullscreen(  );
				  break;
			case  ID_applyForChkingWalls:  {
				  qisChkWalls(  );
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  MIS_CNT	*	pMisCnt	=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
				  if  (  isQEmpty(  &pMisCnt->talkingFriendQ  )  )  {
					  InvalidateRect(  m_hWnd,  NULL,  TRUE  );  
				  }
				  //  layoutWalls(  this->m_hWnd  );
				  sizeAllControls_dlgWalls(  this->m_hWnd,  this->getWndContentType(  ),  &var.wall  );
				  }
				  break;
			case  ID_refreshLayout:
				  sizeAllControls_dlgWalls(  this->m_hWnd,  this->getWndContentType(  ),  &var.wall  );
				  break;


			default:
					break;
	}
}

#if  0
void CqyMc_tsDlg::OnUpdateIsCmd(CCmdUI *pCmdUI)
{
}
#endif



void CqyMc_tsDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	//  CDialogEx::PostNcDestroy();

	OutputDebugString(  _T(  "tsDlg::PostNcDestroy: delete this\n"  )  );

	delete  this;
}


void CqyMc_tsDlg::OnBnClickedButtoncontact()
{
	// TODO: Add your control notification handler code here		
	QY_MC* pQyMc = var.pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	DLG_guiDataParam_objs	param;
	memset(  &param,  0,  sizeof(  param  )  );
	param.uiType  =  CONST_objType_messenger;
	if  (  showDlgObjs(  pQyMc->g_hInst,  this->m_hWnd,  &param  )  )  return;

	//  2015/06/02
	if  (  bApp_ts_3d(  pQyMc  )  )  {
		dyn_createConsoleWall(  pQyMc->pGBuf_d3d  );
		//
		QY_MESSENGER_ID	idInfo;			
		idInfo.ui64Id  =  param.o.ui64Id_selected;
		dyn_tryToTalkToMessenger_d3dWall(  pProcInfo,  &idInfo,  0,  FALSE,  NULL  );					 
		return;
	}

	//
	talkToMessenger(  param.o.ui64Id_selected,  0,  FALSE,  TRUE,  NULL  );
	return;

}


void CqyMc_tsDlg::OnBnClickedButtongroup()
{
	// TODO: Add your control notification handler code here	
	QY_MC* pQyMc = var.pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	DLG_guiDataParam_objs	param;
	memset(  &param,  0,  sizeof(  param  )  );
	param.uiType  =  CONST_objType_imGrp;
	if  (  showDlgObjs(  pQyMc->g_hInst,  this->m_hWnd,  &param  )  )  return;

	//  2015/06/02
	if  (  bApp_ts_3d(  pQyMc  )  )  {
		dyn_createConsoleWall(  pQyMc->pGBuf_d3d  );
		//
		QY_MESSENGER_ID	idInfo;			
		idInfo.ui64Id  =  param.o.ui64Id_selected;
		dyn_tryToTalkToMessenger_d3dWall(  pProcInfo,  &idInfo,  0,  FALSE,  NULL  );					 
		return;
	}

	//
	talkToMessenger(  param.o.ui64Id_selected,  0,  FALSE,  TRUE,  NULL  );
	return;

}


void CqyMc_tsDlg::OnBnClickedButtoncustomerserviceofficer0()
{
	// TODO: Add your control notification handler code here
		//  先发送咨询请求到客服分组，
	//  等待回复。

	//  客服分组组播到每个成员
	//  某成员发送回复到该请求者。
	//  请求者选择其中之一作为被咨询方，发送已接收到客服分组
	//  客服分组再组播到每个成员。

	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	MIS_CNT			*	pMisCnt	=	getMisCntByName(  pProcInfo,  _T(  ""  )  );

	
	int							iErr								=	-1;
	QY_MC* pQyMc = var.pQyMc;// QY_GET_GBUF();
	unsigned  int				lenInBytes;

	QUERY_customerServiceOfficer_req		req;
	 
	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_queryCustomerServiceOfficerReq;
	getTalkerDesc(  pMisCnt->idInfo,  req.talkerDesc,  mycountof(  req.talkerDesc  ),  NULL,  0  );

	lenInBytes  =  sizeof(  req  );

	MACRO_prepareForTran(  );

	startProgress(  &pQyMc->gui.progress,  uiTranNo  );

	QY_MESSENGER_ID	*	pIdInfo_to	=	&pProcInfo->customerService.objs[0].idInfo;

	if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&req,  lenInBytes,  NULL,  NULL,  NULL,  pIdInfo_to,  0,  NULL,  FALSE  )  )  goto  errLabel;

#if  0	//  2013/06/07
	{
		CDlgProgress	dlg(  this  );
		dlg.bSetDlgInfo(  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo  ); 

		//  traceLogA(  "if task is not ready, cancel the task by clear shmCmd, and the subprocess will quit when it read the shmCmd."  );
		if  (  dlg.DoModal(  )  !=  IDOK  )  {
			goto  errLabel;
		}

	}
#endif
	if  (  showProgress(  &pQyMc->gui.progress,  &pQyMc->cusRes,  this->m_hWnd,  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo  )  !=  IDOK  )  {
		goto  errLabel;
	}

	//
	traceLog(  _T(  "queryCustomerServiceOfficer ok"  )  );

	HWND	hDlgTalk;

	if  (  talkToMessenger(  pProcInfo->customerService.called.idInfo.ui64Id,  0,  FALSE,  TRUE,  &hDlgTalk  )  )  goto  errLabel;

	MIS_MSG_applyForWork	msg;
	//
	memset(  &msg,  0,  sizeof(  msg  )  );
	msg.uiType  =  CONST_misMsgType_applyForWork;
	msg.uiContentType  =  CONST_imCommType_queryCustomerServiceOfficerReplyReq;

	dlgTalk_qPostMsg(  hDlgTalk,  &msg,  sizeof(  msg  )  );

	::PostMessage(  hDlgTalk,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );

errLabel:
	return;

}


void CqyMc_tsDlg::OnBnClickedButtonbar()
{
	// TODO: Add your control notification handler code here		
	QY_MC* pQyMc = var.pQyMc;// QY_GET_GBUF();
			
	showMenu_wallsBar(  NULL,  this->m_hWnd,  this->getWndContentType(  ),  0  );

}
