
#include	"stdafx.h"
#include	"qyCusResPublic.h"
#include	"qyOpenShellCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qmOpenCommon.h"

#include	"myresource.h"

 int  dlgLayout_MessageBox(  void  *  pGuidata,  HWND  hDlg  )
{
	G_guiData_qyMc		*	pGuiData  =  g_getGuiData(  );

	cusDlgRes(  0,  pGuiData->pCusRes,  hDlg,  IDD_MessageBox  );


#if  !defined(  __WINCE__  )  ||  defined(  __TEST__  )
	return  0
#else

	DLG_guiData_MessageBox  *  p  =  (  DLG_guiData_MessageBox  *  )pGuidata;
	if  (  !p  ) goto  errLabel;

	int  w,  h;
	int  w_org,  h_org;
	HDC  hScreenDC=::GetDC(NULL);
	int  maxxScreen  =  GetDeviceCaps(  hScreenDC,  HORZRES  );
	int  maxyScreen  =  GetDeviceCaps(  hScreenDC,  VERTRES  );
	::ReleaseDC(  NULL,  hScreenDC  );

	RECT  rc;
	GetWindowRect(  hDlg,  &rc  );
	w_org  =  rc.right  -  rc.left;
	h_org  =  rc.bottom  -  rc.top;

	if  (  !w_org  ||  !h_org  )  goto  errLabel;

	RECT  rcIDOK;	
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDOK  ),  &rcIDOK  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rcIDOK,  2  );

	RECT  rcIDCANCEL;	
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDCANCEL  ),  &rcIDCANCEL  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rcIDCANCEL,  2  );

	RECT	rcIDC_STATIC_hint;
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_STATIC_hint  ),  &rcIDC_STATIC_hint  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rcIDC_STATIC_hint,  2  );

	w  =  maxxScreen;  h  =  maxyScreen;
	MoveWindow(  hDlg,  0,  0,  w,  h,  TRUE  );
	GetClientRect(  hDlg,  &rc  );
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;

	int  idc;
	int  iX,  iY,  iW, iH;
	float  fx,  fy;
	fx  =  1.  *  w  /  w_org;
	fy  =  1.  *  h  /  h_org;

	idc  =  p->iIDOK;
	rc  =  rcIDOK;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  ); 

	idc  =  p->iIDCANCEL;
	rc  =  rcIDCANCEL;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  ); 

	idc  =  p->iIDC_STATIC_hint;
	rc  =  rcIDC_STATIC_hint;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  ); 

errLabel:
	return  0;
#endif
}


INT_PTR CALLBACK dlgProc_MessageBox(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	DLG_guiData_MessageBox  *  pGuiData	=	(  DLG_guiData_MessageBox  *  )GetWindowLong(  hDlg,  GWLP_USERDATA  );
	//  void	*	pDlg	=	(  void  *  )pGuiData;

	UNREFERENCED_PARAMETER(lParam);
	switch  (  message  ) {
		   	case  WM_INITDIALOG:
				  pGuiData  =  (  DLG_guiData_MessageBox  *  )lParam;
				  //  pDlg  =  (  void  *  )lParam;

				  SetWindowLong(  hDlg,  GWLP_USERDATA,  (  LONG )pGuiData  );
				  //  SetWindowLong(  hDlg,  GWLP_USERDATA,  (  LONG )pDlg  );

				  dlgLayout_MessageBox(  (  void  *  )pGuiData,  hDlg  );
				  //  dlgLayout_MessageBox(  pDlg,  hDlg  );


				  if  (  pGuiData->lpText  )  pGuiData->pf_SetDlgItemText(  hDlg,  pGuiData->iIDC_STATIC_hint,  pGuiData->lpText  );
				  if  (  pGuiData->lpCaption  )  SetWindowText(  hDlg,  pGuiData->lpCaption  );

				  return (INT_PTR)TRUE;

			case  WM_COMMAND:  {
				  WORD  wNotifyCode = HIWORD(wParam); 
				  WORD  wID = LOWORD(wParam); 
				  HWND  hwndCtl = (HWND) lParam;
				  int	nResult	=	0;

				 if  (  wID  ==  IDCANCEL  )  {
					 if  (  pGuiData->uType  &  MB_YESNO  )  nResult  =  IDNO;
					 else  nResult  =  IDCANCEL;

					 EndDialog(hDlg, nResult);
					 return (INT_PTR)TRUE;
				 }
				 if  (  wID  ==  IDOK  )  {
					 if  (  pGuiData->uType  &  MB_YESNO  )  nResult  =  IDYES;
					 else  nResult  =  IDOK;

					 EndDialog(  hDlg,  nResult  );
					 return  TRUE;
				 }
				 }
				 break;

			default:
					break;
	}

	return (INT_PTR)FALSE;
}



 int  WINAPI  myMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType  )
{
	int			iErr	=	-1;


	DLG_guiData_MessageBox			guiData;
	DLG_guiData_MessageBox		*	p		=	&guiData;
	if  (  !p  )  goto  errLabel;
	p->iIDOK  =  IDOK;
	p->iIDCANCEL  =  IDCANCEL;
	p->iIDC_STATIC_hint  =  IDC_STATIC_hint;

	p->pf_GetDlgItemText  =  GetDlgItemText;
	p->pf_SetDlgItemText  =  mySetDlgItemText;

	p->lpText  =  (  TCHAR  *  )lpText;
	p->lpCaption  =  (  TCHAR  *  )lpCaption;
	p->uType  =  uType;

	if  (  DialogBoxParam(  g_hInst,  MAKEINTRESOURCE(  IDD_MessageBox  ),  hWnd,  dlgProc_MessageBox,  (  LPARAM  )p  )  !=  IDOK  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr  ?  IDCANCEL  :  IDOK;
}
