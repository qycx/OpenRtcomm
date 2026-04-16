

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#ifdef  __WINCE__
	#ifndef  __TEST__
		#include	"ceMenuBar.h"
	#endif
#endif

#include	"myresource.h"

#include	"DlgMcClientLogon.h"
#include	"DlgQnmCfgOptionsIsClient.h"
#include	"qyCusResTemp.h"


INT_PTR CALLBACK dlgProc_mcClientLogon(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


 int  showDlgMcClientDevAuth(  HINSTANCE  g_hInst,  HWND  hMainWnd,  void  *  pQyMcParam,  PARAM_showDlgMcLogon  *  pParam  )
{
	int			iErr	=	-1;
	void	*	pWnd	=	NULL;

	QY_MC  *  pQyMc  =  (  QY_MC  *  )pQyMcParam;

	if  (  !g_hInst  )  g_hInst  =  get_my_hInst(  pQyMc  );

	pWnd  =  newQyWnd(  CONST_qyWndContentType_mcClientLogon  );
	if  (  !pWnd  )  goto  errLabel;

	DLG_guiData_mcClientLogon  *  p	=	(  DLG_guiData_mcClientLogon  *  )qyWnd_getGuiData(  pWnd  );
	if  (  !p  )  goto  errLabel;
#if  0
	p->iIDC_STATIC_logonServer  =  IDC_STATIC_logonServer;
	p->iIDC_COMBO_logonServer  =  IDC_COMBO_logonServer;
	p->iIDC_STATIC_usrName  =  IDC_STATIC_usrName;
	p->iIDC_NAME  =  IDC_NAME;
	p->iIDC_STATIC_passwd  =  IDC_STATIC_passwd;
	p->iIDC_PASSWD  =  IDC_PASSWD;
#endif

	p->iIDC_STATIC_hint  =  IDC_STATIC_hint;
	p->iIDOK  =  IDOK;
	p->iIDCANCEL  =  IDCANCEL;
	p->iIDC_BUTTON_option  =  IDC_BUTTON_option;

	p->pf_GetDlgItemText  =  GetDlgItemText;
	p->pf_SetDlgItemText  =  mySetDlgItemText;

	HWND hWndParent  =  NULL;		//  2011/02/26
	hWndParent  =  hMainWnd;
	
	if  (  DialogBoxParam(  g_hInst,  MAKEINTRESOURCE(  IDD_mcClient_devAuth  ),  hWndParent,  dlgProc_mcClientLogon,  (  LPARAM  )pWnd  )  !=  IDOK  )  goto  errLabel;

	iErr  =  0;
errLabel:
	if  (  pWnd  )  freeQyWnd(  pWnd  );
	return  iErr;
}

