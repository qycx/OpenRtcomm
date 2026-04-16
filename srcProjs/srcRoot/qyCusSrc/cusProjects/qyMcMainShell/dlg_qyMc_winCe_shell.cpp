

#include	"stdafx.h"
#include	"qyCusResPublic.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

 int  displayNotification_mainWnd(  void  *  pDlg,  HWND  hDlg,  LPCTSTR  hint  )
{
	WND_guiData_main	*	pGuiData	=	(  WND_guiData_main  *  )qyWnd_getGuiData(  pDlg  );
	if  (  !pGuiData  )  return  -1;
	SetDlgItemText(  hDlg,  pGuiData->iIDC_BUTTON_status,  hint  );
	return  0;
}

int  dlgLayout_qyMc_winCe(  void  *  pDlg,  HWND  hDlg  )
{
#if  !defined(  __WINCE__  )  ||  defined(  __TEST__  )
		 return  0;
#else

	WND_guiData_main  *  p  =  (  WND_guiData_main  *  )qyWnd_getGuiData(  pDlg  );
	if  (  !p  )  goto  errLabel;

	int	w, h;
	int	w_org,  h_org;
	HDC hScreenDC=::GetDC(NULL);
	int  maxxScreen = GetDeviceCaps(hScreenDC,HORZRES);
	int  maxyScreen = GetDeviceCaps(hScreenDC,VERTRES);
	::ReleaseDC(NULL,hScreenDC);		

	RECT	rc;
	GetWindowRect(  hDlg,  &rc  );
	w_org  =  rc.right  -  rc.left;
	h_org  =  rc.bottom  -  rc.top;

	if  (  !w_org  ||  !h_org  )  goto  errLabel;

	RECT	rcIDC_BUTTON_contact;	
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_contact  ),  &rcIDC_BUTTON_contact  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rcIDC_BUTTON_contact,  2  );

	RECT	rcIDC_BUTTON_group;	
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_group  ),  &rcIDC_BUTTON_group  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rcIDC_BUTTON_group,  2  );

	RECT	rcIDC_BUTTON_status;	
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_status  ),  &rcIDC_BUTTON_status  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rcIDC_BUTTON_status,  2  );

	RECT	rcIDCANCEL;	
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDCANCEL  ),  &rcIDCANCEL  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rcIDCANCEL,  2  );

		
	w  =  maxxScreen;  h  =  maxyScreen;
	MoveWindow(  hDlg,  0,  0,  w,  h,  TRUE  );
	GetClientRect(  hDlg,  &rc  );
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;

	int	idc;
	int  iX,  iY,  iW,  iH;
	float  fx,  fy;
	fx  =  1.  *  w  /  w_org;
	fy  =  1.  *  h  /  h_org;

	idc  =  p->iIDC_BUTTON_contact;
	rc  =  rcIDC_BUTTON_contact;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_group;
	rc  =  rcIDC_BUTTON_group;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_status;
	rc  =  rcIDC_BUTTON_status;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDCANCEL;
	rc  =  rcIDCANCEL;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

errLabel:
	return  0;

#endif
}


 INT_PTR CALLBACK	dlgProc_qyMc_winCe(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	void	*	pDlg	=	(  void  *  )GetWindowLong(  hDlg,  GWLP_USERDATA  );

	UNREFERENCED_PARAMETER(lParam);
	switch  (  message  ) {
		   	case  WM_INITDIALOG:
				  pDlg  =  (  void  *  )lParam;

				  //  SetWindowLong(  hDlg,  GWLP_USERDATA,  (  LONG )pDlg  );
				  qyWnd_Attach(  pDlg,  hDlg  );

				  //
				  dlgLayout_qyMc_winCe(  pDlg,  hDlg  );
				  //
				  //  myDialogProc_qyMc_winCe(  pDlg,  hDlg,  message,  wParam,  lParam  );
				  if  (  initVar_onCreate_mainFrame(  0,  hDlg,  qyWnd_getVar(  pDlg  )  )  )  {
					  EndDialog(  hDlg,  -1  );
					  return  TRUE;
				  }

				  //
				  if  (  qyShowMainWnd(  hDlg,  qyWnd_getVar(  pDlg  )  )  )  {
					  ShowWindow(  hDlg,  SW_HIDE  );
					  EndDialog(  hDlg,  -1  );
					  return  TRUE;
				  }
				  //
				  SetForegroundWindow(  hDlg  );
				  
				  return (INT_PTR)TRUE;

			case  WM_COMMAND:  {
				  WORD  wNotifyCode = HIWORD(wParam); 
				  WORD  wID = LOWORD(wParam); 
				  HWND  hwndCtl = (HWND) lParam;
				  DLG_guiDataParam_objs	param;

				 if  ( wID == IDCANCEL  )  {
					 //  EndDialog(hDlg, LOWORD(wParam));
					 SendMessage(  hDlg,  WM_CLOSE,  0,  0  );
					 return (INT_PTR)TRUE;
				 }
				 if  (  wID  ==  IDC_BUTTON_contact  )  {
					 memset(  &param,  0,  sizeof(  param  )  );
					 param.uiType  =  CONST_objType_messenger;
					 if  (  showDlgObjs(  g_hInst,  hDlg,  &param  )  )  return  TRUE;
					 talkToMessenger(  param.ui64Id_selected,  FALSE,  TRUE,  NULL  );
					 return  TRUE;
				 }
				 if  (  wID  ==  IDC_BUTTON_group  )  {
					 memset(  &param,  0,  sizeof(  param  )  );
					 param.uiType  =  CONST_objType_imGrp;
					 if  (  showDlgObjs(  g_hInst,  hDlg,  &param  )  )  return  TRUE;
					 talkToMessenger(  param.ui64Id_selected,  FALSE,  TRUE,  NULL  );
					 return  TRUE;
				 }
				 if  (  wID  ==  IDC_BUTTON_status  )  {
					 memset(  &param,  0,  sizeof(  param  )  );
					 param.uiType  =  0;
					 if  (  showDlgObjs(  g_hInst,  hDlg,  &param  )  )  return  TRUE;
					 talkToMessenger(  param.ui64Id_selected,  FALSE,  TRUE,  NULL  );
					 return  TRUE;
				 }
				 if  (  wID  ==  ID_qyQuitMainWnd  )  {
					  mainWnd_OnQyQuitMainWnd(  hDlg,  qyWnd_getVar(  pDlg  )  );
					  return  TRUE;
				  }

				 //
				 }
				 break;

			case  WM_TIMER:
				  mainWnd_OnTimer(  hDlg,  qyWnd_getVar(  pDlg  ),  wParam  );
				  return  TRUE;
				  break;

			case  WM_CLOSE:
				  OutputDebugString(  _T(  "WM_CLOSE\n"  )  );
				  mainWnd_OnQyQuitMainWnd(  hDlg,  qyWnd_getVar(  pDlg  )  );
				  if  (  mainWnd_OnClose(  hDlg,  qyWnd_getVar(  pDlg  )  )  )  return  TRUE;
				  EndDialog(  hDlg,  0  );
				  return  TRUE;
				  break;

			case  WM_DESTROY:

				  exitVar_onDestroy_mainFrame(  0,  hDlg,  qyWnd_getVar(  pDlg  )  );

				  break;

			default:

					if  (  myDialogProc_qyMc_winCe(  pDlg,  hDlg,  message,  wParam,  lParam  )  )  return  TRUE;
					break;
	}

	return (INT_PTR)FALSE;
}



int  showDlg_qyMc_winCe(  HINSTANCE  g_hInst,  void  *  p1,  void  *  p2  )
{
#if  10
	int			iErr	=	-1;
	void	*	pWnd	=	NULL;
 
	pWnd  =  newQyWnd(  CONST_qyWndContentType_qyMc_winCe  );

	if  (  !pWnd  )  goto  errLabel;

	WND_guiData_main	*	p	=	(  WND_guiData_main  *  )qyWnd_getGuiData(  pWnd  );
	p->iIDC_BUTTON_contact  =  IDC_BUTTON_contact;
	p->iIDC_BUTTON_group  =  IDC_BUTTON_group;
	p->iIDC_BUTTON_status  =  IDC_BUTTON_status;

	//
	p->pf_displayNotification_mainWnd  =  displayNotification_mainWnd;


	//
	{
		G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )get_g_guiData(  );

		//
		HDC hScreenDC=::GetDC(NULL);
		int  maxxScreen = GetDeviceCaps(hScreenDC,HORZRES);
		int  maxyScreen = GetDeviceCaps(hScreenDC,VERTRES);
		::ReleaseDC(NULL,hScreenDC);		

		pGuiData->fy  =  maxyScreen  *  1.0  /  480;
		pGuiData->iH_listFont_default  =  30;
		pGuiData->iH_listFont_text_default  =  22;

		LOGFONT	lf;
		memset(  &lf,  0,  sizeof(  lf  )  );
		::lstrcpyn(  lf.lfFaceName,  _T(  "System"  ),  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
		lf.lfHeight  =  pGuiData->iH_listFont_default  *  pGuiData->fy;
		pGuiData->hFont_list  =  CreateFontIndirect(  &lf  );  

		memset(  &lf,  0,  sizeof(  lf  )  );
		::lstrcpyn(  lf.lfFaceName,  _T(  "System"  ),  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
		lf.lfHeight  =  pGuiData->iH_listFont_text_default  *  pGuiData->fy;
		pGuiData->hFont_list_text  =  CreateFontIndirect(  &lf  );
	}

	//
	int  tmpiRet;
	tmpiRet  =  DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_QYMC_WINCE_DIALOG), NULL, dlgProc_qyMc_winCe,  (  LPARAM  )pWnd  );
	if  (  tmpiRet  !=  IDOK  )  goto  errLabel;


	iErr  =  0;
errLabel:

	{
		G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )get_g_guiData(  );
		if  (  pGuiData->hFont_list  )  {
			DeleteObject(  pGuiData->hFont_list  );  pGuiData->hFont_list  =  NULL;
		}
		if  (  pGuiData->hFont_list_text  )  {
			DeleteObject(  pGuiData->hFont_list_text  );  pGuiData->hFont_list_text  =  NULL;
		}
	}

	if  (  pWnd  )  freeQyWnd(  pWnd  );
	return  iErr;
#endif
	return  0;
}
