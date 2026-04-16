

#include	"stdafx.h"
#include	<mmsystem.h>
#include	"qyMcMainCommon.h"
#include	"qyCusResPublic.h"
#include	"qyOpenShellCommon.h"
#include	"qmOpenCommon.h"

#include	"myresource.h"

#ifdef  __WINCE__
#else
	#include	"dlgObjs_ts.h"
#endif

#include	"funcsForIsCliHelp.h"
#include	"ctxQmc.h"


int  dlgLayout_objs(  HWND  hDlg,  DLG_guiData_objs  *  p  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs		=  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	//
	G_guiData_qyMc	*  pGuiData   =  pFuncs->pf_get_g_guiData(  );
	cusDlgRes(  0,  pGuiData->pCusRes,  hDlg,  IDD_objs  );  


#if  1	//  defined(  __WINCE__  )  ||  defined(  __APP_qyMc_touchscreen__  )  
     //  return 0;
	if  (  !p  )  goto  errLabel;

	RECT	rc;
	GetClientRect(  hDlg,  &rc  );
	p->w_org  =  rc.right  -  rc.left;
	p->h_org  =  rc.bottom  -  rc.top;

	if  (  !p->w_org  ||  !p->h_org  )  goto  errLabel;

	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_LIST0  ),  &p->rcIDC_LIST0  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_LIST0,  2  );
		
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_contact  ),  &p->rcIDC_BUTTON_contact  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_contact,  2  );
		
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_group  ),  &p->rcIDC_BUTTON_group  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_group,  2  );
	
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_status  ),  &p->rcIDC_BUTTON_status  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_status,  2  );
	
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDCANCEL  ),  &p->rcIDCANCEL  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDCANCEL,  2  );

	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDOK  ),  &p->rcIDOK  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDOK,  2  );

	int	w, h;

#ifdef  __WINCE__		//  这个移动，其实应该移到dlg_OnInitDialog(  )中去
	HDC hScreenDC=::GetDC(NULL);
	int  maxxScreen = GetDeviceCaps(hScreenDC,HORZRES);
	int  maxyScreen = GetDeviceCaps(hScreenDC,VERTRES);
	::ReleaseDC(NULL,hScreenDC);		


	w  =  maxxScreen;  h  =  maxyScreen;
	MoveWindow(  hDlg,  0,  0,  w,  h,  TRUE  );
#endif

	//
	//  G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )get_g_guiData(  );
	HWND	hCtrl;
	hCtrl  =  GetDlgItem(  hDlg,  p->iIDC_LIST0  );
	if  (  hCtrl  )  {
		if  (  pGuiData->hFont_list  )  {
			SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_list,  TRUE  );
		}
	}
	hCtrl	=	GetDlgItem(  hDlg,  p->iIDOK  );
	if  (  hCtrl  )  {
		if  (  pGuiData->hFont_btn  )  {
			SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
		}
	}
	hCtrl  =  GetDlgItem(  hDlg,  p->iIDCANCEL  );
	if  (  hCtrl  )  {
		if  (  pGuiData->hFont_btn  )  {
			SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
		}
	}

#endif

errLabel:

	return  0;

}

 int  sizeAllControls_dlgObjs(  HWND  hDlg,  DLG_guiData_objs  *  p  )
 {
	 if  (  !p->w_org  ||  !p->h_org  )  return  -1;

	 RECT	rc;
	 int	w,  h;

	GetClientRect(  hDlg,  &rc  );
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;

	int	idc;
	int  iX,  iY,  iW,  iH;
	float  fx,  fy;
	fx  =  1.  *  w  /  p->w_org;
	fy  =  1.  *  h  /  p->h_org;

	idc  =  p->iIDC_LIST0;
	rc  =  p->rcIDC_LIST0;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_contact;
	rc  =  p->rcIDC_BUTTON_contact;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  	
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_group;
	rc  =  p->rcIDC_BUTTON_group;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  	
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_status;
	rc  =  p->rcIDC_BUTTON_status;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  	
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDCANCEL;
	rc  =  p->rcIDCANCEL;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  	
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDOK;
	rc  =  p->rcIDOK;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  	
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	 return  0;
}

INT_PTR CALLBACK dlgProc_objs(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	void	*	pDlg	=	(  void  *  )GetWindowLong(  hDlg,  GWLP_USERDATA  );

	UNREFERENCED_PARAMETER(lParam);
	switch  (  message  ) {
			case  WM_INITDIALOG:  {
				  pDlg  =  (  void  *  )lParam;
				  //  SetWindowLong(  hDlg,  GWLP_USERDATA,  (  LONG )pDlg  );
				  qyWnd_Attach(  pDlg,  hDlg  );
				  //
				  dlgLayout_objs(  hDlg,  (  DLG_guiData_objs  *  )qyWnd_getGuiData(  pDlg  )  );
				  sizeAllControls_dlgObjs(  hDlg,  (  DLG_guiData_objs  *  )qyWnd_getGuiData(  pDlg  )  );
				  //
				  //  myDialogProc_objs(  pDlg,  hDlg,  message,  wParam,  lParam  );				  
				  centerWnd(  hDlg  );

				  // TODO:  Add extra initialization here
				  DLG_guiData_objs  *  pGuiData  =  (  DLG_guiData_objs  *  )qyWnd_getGuiData(  pDlg  );
				  dlgObjs_bFillContent(  hDlg,  qyWnd_getVar(  pDlg  ),  pGuiData->param.uiType  );

				  }
				  return (INT_PTR)TRUE;

			case  WM_COMMAND:  {
				  WORD  wNotifyCode = HIWORD(wParam); 
				  WORD  wID = LOWORD(wParam); 
				  HWND  hwndCtl = (HWND) lParam;

				 if  ( wID == IDCANCEL  )  {
					 EndDialog(hDlg, LOWORD(wParam));
					 return (INT_PTR)TRUE;
				 }
				 if  (  wID  ==  IDOK  )  {
					 if  (  !dlgObjs_OnOK(  hDlg,  qyWnd_getVar(  pDlg  )  )  )  {
						 EndDialog(  hDlg,  LOWORD(  wParam  )  );
					 }
					 return  TRUE;
				 }
				 DLG_guiData_objs  *  pGuiData  =  (  DLG_guiData_objs  *  )qyWnd_getGuiData(  pDlg  );
				 if  (  wID  ==  pGuiData->iIDC_BUTTON_contact  )  {
					  dlgObjs_bFillContent(  hDlg,  qyWnd_getVar(  pDlg  ),  CONST_objType_messenger  );
					  return  TRUE;
				  }
				 if  (  wID  ==  pGuiData->iIDC_BUTTON_group  )  {
					  dlgObjs_bFillContent(  hDlg,  qyWnd_getVar(  pDlg  ),  CONST_objType_imGrp  );
					  return  TRUE;
				  }
				  if  (  wID  ==  pGuiData->iIDC_BUTTON_status  )  {
					  dlgObjs_bFillContent(  hDlg,  qyWnd_getVar(  pDlg  ),  0  );
					  return  TRUE;
				  }


				 }
				 break;

			case  WM_SIZE:

				  sizeAllControls_dlgObjs(  hDlg,  (  DLG_guiData_objs  *  )qyWnd_getGuiData(  pDlg  )  );
				  break;

			default:
					break;
	}


	//  if  (  myDialogProc_objs(  pDlg,  hDlg,  message,  wParam,  lParam  )  )  return  TRUE;


	return (INT_PTR)FALSE;
}

 __declspec(  dllexport  )  int  showDlgObjs(  HINSTANCE  g_hInst,  HWND  hParent,  void  *  pDLG_guiDataParam_objs  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	DLG_guiDataParam_objs  *  pParam  =  (  DLG_guiDataParam_objs  *  )pDLG_guiDataParam_objs;

#ifdef  __WINCE__
	int			iErr	=	-1;
	void	*	pWnd	=	NULL;

	pWnd  =  newQyWnd(  CONST_qyWndContentType_objs  );
	if  (  !pWnd  )  goto  errLabel;

	DLG_guiData_objs  *  p	=	(  DLG_guiData_objs  *  )qyWnd_getGuiData(  pWnd  );
	if  (  !p  )  goto  errLabel;

	if  (  pParam  )  {
		//  p->param.uiType  =  pParam->param.uiType;			
		memcpy(  &p->param,  pParam,  sizeof(  p->param  )  );
	}

	p->iIDC_LIST0  =  IDC_LIST0;
	p->iIDC_BUTTON_contact  =  IDC_BUTTON_contact;
	p->iIDC_BUTTON_group  =  IDC_BUTTON_group;
	p->iIDC_BUTTON_status  =  IDC_BUTTON_status;
	p->iIDCANCEL  =  IDCANCEL;
	p->iIDOK  =  IDOK;


	if  (  DialogBoxParam(  g_hInst,  MAKEINTRESOURCE(  IDD_objs  ),  hParent,  dlgProc_objs,  (  LPARAM  )pWnd  )  !=  IDOK  )  goto  errLabel;

	if  (  pParam  )  {
		pParam->ui64Id_selected  =  p->param.ui64Id_selected;
	}

	iErr  =  0;
errLabel:
	if  (  pWnd  )  freeQyWnd(  pWnd  );
	return  iErr;
#else
	int		iErr	=	-1;
	CDlgObjs_ts	dlg(  CWnd::FromHandle(  hParent  )  );

	DLG_guiData_objs  *  p	=	(  DLG_guiData_objs  *  )&dlg.m_var.guiData;
	if  (  !p  )  goto  errLabel;

	if  (  pParam  )  {
		//  p->param.uiType  =  pParam->param.uiType;
		memcpy(  &p->param,  pParam,  sizeof(  p->param  )  );
	}

	p->iIDC_LIST0  =  IDC_LIST0;
#if  0  //  ndef  __DEBUG__
	p->iIDC_BUTTON_contact  =  IDC_BUTTON_contact;
	p->iIDC_BUTTON_group  =  IDC_BUTTON_group;
	p->iIDC_BUTTON_status  =  IDC_BUTTON_status;
#endif
	p->iIDCANCEL  =  IDCANCEL;
	p->iIDOK  =  IDOK;

	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	if  (  pParam  )  {
		//  pParam->ui64Id_selected  =  p->param.ui64Id_selected;
		memcpy(  &pParam->o,  &p->param.o,  sizeof(  pParam->o  )  );
		//
		memcpy(  pParam->pObjBuf_selected,  p->param.pObjBuf_selected,  pParam->uiSize_pObjBuf_selected  );
	}

	iErr  =  0;
errLabel:
	return  iErr;
#endif
}

