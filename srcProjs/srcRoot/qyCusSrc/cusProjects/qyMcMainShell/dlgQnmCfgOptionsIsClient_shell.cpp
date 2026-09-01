

#include	"stdafx.h"
#include	<mmsystem.h>
#include	"qyCusResPublic.h"
#include	"qyOpenShellCommon.h"
#include	"qmOpenCommon.h"
#include	"qmShellPublic.h"
#include	"qyCusResTemp.h"


#include	"myresource.h"

int  tmp_getSth_hideMore(  HWND  hDlg,  DLG_guiData_qnmCfgOptionsIsClient  *  p  )  
{
	int		iErr	=	-1;
	RECT	rc;
	HWND	hCtrl;
	int		iW  =  0,  iH  =  0;
	int		iEdge_h  =  0;
	int		iEdge_v  =  0;

	hCtrl  =  GetDlgItem(  hDlg,  p->iIDC_STATIC_centerAddr  );
	if  (  !hCtrl  )  goto  errLabel;
	GetWindowRect(  hCtrl,  &rc  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rc,  2  );
	iEdge_h  =  rc.left;
	iEdge_v  =  rc.top;
	iW  =  rc.right  +  iEdge_h;

	//
	hCtrl  =  GetDlgItem(  hDlg,  p->iIDC_BUTTON_more  );
	if  (  !hCtrl  )  goto  errLabel;
	GetWindowRect(  hCtrl,  &rc  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rc,  2  );
	iH  =  rc.bottom  +  iEdge_v;

	if  (  !iW  ||  !iH  )  goto  errLabel;

	//  还要加上nonClient的宽高
	GetWindowRect(  hDlg,  &rc  );
	RECT	cliRc;
	GetClientRect(  hDlg,  &cliRc  );

	p->w_org_hideMore  =  iW  +  (  (  rc.right  -  rc.left  )  -  (  cliRc.right  -  cliRc.left  )  );
	p->h_org_hideMore  =  iH  +  (  (  rc.bottom  -  rc.top  )  -  (  cliRc.bottom  -  cliRc.top  )  );

	iErr  =  0;

errLabel:
	if  (  iErr  )  {
		p->w_org_hideMore  =  430;
		p->h_org_hideMore  =  315;
	}
	return  0;
}

int  dlgLayout_qnmCfgOptionsIsClient(  void  *  pDlg,  HWND  hDlg  )
{

	G_guiData_qyMc		*  pGuiData  =  get_g_guiData(  );
#if  defined(  __WINCE__  )  
	cusDlgRes(  0,  pGuiData->pCusRes,  hDlg,  IDD_qnmCfgOptions_isClient_ce  );
#else
	cusDlgRes(  0,  pGuiData->pCusRes,  hDlg,  IDD_qnmCfgOptions_isClient  );
#endif

	DLG_guiData_qnmCfgOptionsIsClient				*	p		=  (  DLG_guiData_qnmCfgOptionsIsClient  * )qyWnd_getGuiData(  pDlg  );  
	if  (  !p  )  goto  errLabel;
	RECT												rc;

	GetWindowRect(  hDlg,  &rc  );
	p->w_org  =  rc.right  -  rc.left;
	p->h_org  =  rc.bottom  -  rc.top;
	//
#if  0
	p->w_org_hideMore  =  430;
	p->h_org_hideMore  =  315;
#endif
	tmp_getSth_hideMore(  hDlg,  p  );	//  2013/04/07

	//
	if  (  !p->w_org  ||  !p->h_org  )  goto  errLabel;
	if  (  !p->w_org_hideMore  ||  !p->h_org_hideMore  )  goto  errLabel;

#if  defined(  __WINCE__  )  ||  defined(  __APP_qyMc_touchscreen__  )



		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_STATIC_centerAddr  ),  &p->rcIDC_STATIC_centerAddr  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_centerAddr,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_STATIC_cntAddr0  ),  &p->rcIDC_STATIC_cntAddr0  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_cntAddr0,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_cntIp  ),  &p->rcIDC_cntIp  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_cntIp,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_STATIC_cntAddr1  ),  &p->rcIDC_STATIC_cntAddr1  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_cntAddr1,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_EDIT_cntAddr1  ),  &p->rcIDC_EDIT_cntAddr1  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_EDIT_cntAddr1,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_STATIC_cntAddr2  ),  &p->rcIDC_STATIC_cntAddr2  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_cntAddr2,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_EDIT_cntAddr2  ),  &p->rcIDC_EDIT_cntAddr2  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_EDIT_cntAddr2,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_STATIC_cntName  ),  &p->rcIDC_STATIC_cntName  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_cntName,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_cntName  ),  &p->rcIDC_cntName  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_cntName,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_STATIC_cntPort  ),  &p->rcIDC_STATIC_cntPort  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_cntPort,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_cntPort  ),  &p->rcIDC_cntPort  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_cntPort,  2  );

		 //RECT  rcIDC_STATIC_centerAddr;
		 // GetWindowRect(  GetDlgItem(  

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_CHECK_useDb  ),  &p->rcIDC_CHECK_useDb  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_CHECK_useDb,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDCANCEL  ),  &p->rcIDCANCEL  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDCANCEL,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDOK  ),  &p->rcIDOK  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDOK,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_more  ),  &p->rcIDC_BUTTON_more  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_more,  2  );


		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_LIST_vcServer  ),  &p->rcIDC_LIST_vcServer  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_LIST_vcServer,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_ADD  ),  &p->rcIDC_ADD  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_ADD,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_MODIFY  ),  &p->rcIDC_MODIFY  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_MODIFY,  2  );

		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_DEL  ),  &p->rcIDC_DEL  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_DEL,  2  );


#endif

		 //  2012/02/20
		 p->bMore  =  FALSE;

		 int  w,  h;
#ifdef  __WINCE__
		 HDC  hScreenDC  =  ::GetDC(  NULL  );
		 int  maxxScreen  =  GetDeviceCaps(  hScreenDC,  HORZRES  );
		 int  maxyScreen  =  GetDeviceCaps(  hScreenDC,  VERTRES  );
		 ::ReleaseDC(  NULL,  hScreenDC  );

		 w  =  maxxScreen;  h  =  maxyScreen;
		 MoveWindow(  hDlg,  0,  0,  w,  h,  TRUE  );
#elif  defined(  __APP_qyMc_touchscreen__  )

		 HWND	hParent	=	GetParent(  hDlg  );
		 if  (  !hParent  )  goto  errLabel;
		 GetWindowRect(  hParent,  &rc  );
		 w  =  rc.right  -  rc.left;
		 h  =  rc.bottom  -  rc.top;
		 MoveWindow(  hDlg,  rc.left,  rc.top,  w,  h,  TRUE  );

#else
		 if  (  !p->iParam_qyDlgType  )  {		 
			 GetWindowRect(  hDlg,  &rc  );
			 MoveWindow(  hDlg,  rc.left,  rc.top,  p->w_org_hideMore,  p->h_org_hideMore,  FALSE  );
		 }

#endif 




errLabel:
		 return  0;
}


 int  sizeAllControls_dlgQnmCfgOptionsIsClient(  HWND  hDlg,  DLG_guiData_qnmCfgOptionsIsClient  *  p  )
{
	if  (  !p->w_org  ||  !p->h_org  )  return  -1;

#if  !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
	return  0;
#endif


	RECT	rc;
	int		w, h;

		 GetClientRect(  hDlg,  &rc  );
		 w  =  rc.right  -  rc.left;
		 h  =  rc.bottom  -  rc.top;

		 int	idc;

		 int  iX,  iY,  iW,  iH;
		 float  fx,  fy;
		 if  (  p->bMore  )  {
			 fx  =  1.  *  w  /  p->w_org;
			 fy  =  1.  *  h  /  p->h_org;
		 }
		 else  {
			   fx  =  1.  *  w  /  p->w_org_hideMore;
			   fy  =  1.  *  h  /  p->h_org_hideMore;
		 }

		 idc  =  p->iIDC_STATIC_centerAddr;
		 rc  =  p->rcIDC_STATIC_centerAddr;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_STATIC_cntAddr0;
		 rc  =  p->rcIDC_STATIC_cntAddr0;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_cntIp;
		 rc  =  p->rcIDC_cntIp;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_STATIC_cntAddr1;
		 rc  =  p->rcIDC_STATIC_cntAddr1;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_EDIT_cntAddr1;
		 rc  =  p->rcIDC_EDIT_cntAddr1;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_STATIC_cntAddr2;
		 rc  =  p->rcIDC_STATIC_cntAddr2;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_EDIT_cntAddr2;
		 rc  =  p->rcIDC_EDIT_cntAddr2;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_STATIC_cntName;
		 rc  =  p->rcIDC_STATIC_cntName;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_cntName;
		 rc  =  p->rcIDC_cntName;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_STATIC_cntPort;
		 rc  =  p->rcIDC_STATIC_cntPort;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_cntPort;
		 rc  =  p->rcIDC_cntPort;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

#if  0
		 idc  =  p->iIDC_STATIC_centerAddr;
		 rc  =  p->rcIDC_STATIC_centerAddr;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
#endif

		 //  2013/02/20
		 idc  =  p->iIDC_CHECK_useDb;
		 rc  =  p->rcIDC_CHECK_useDb;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  


		 //
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

		 idc  =  p->iIDC_BUTTON_more;
		 rc  =  p->rcIDC_BUTTON_more;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 if  (  !p->bMore  )  {
			 idc  =  p->iIDC_LIST_vcServer;
			 ShowWindow(  GetDlgItem(  hDlg,  idc  ),  SW_HIDE  );
			 idc  =  p->iIDC_ADD;
			 ShowWindow(  GetDlgItem(  hDlg,  idc  ),  SW_HIDE  );
			 idc  =  p->iIDC_MODIFY;
			 ShowWindow(  GetDlgItem(  hDlg,  idc  ),  SW_HIDE  );
			 idc  =  p->iIDC_DEL;
			 ShowWindow(  GetDlgItem(  hDlg,  idc  ),  SW_HIDE  );
		 }
		 else  {

			 idc  =  p->iIDC_LIST_vcServer;
			 ShowWindow(  GetDlgItem(  hDlg,  idc  ),  SW_SHOW  );
			 idc  =  p->iIDC_ADD;
			 ShowWindow(  GetDlgItem(  hDlg,  idc  ),  SW_SHOW  );
			 idc  =  p->iIDC_MODIFY;
			 ShowWindow(  GetDlgItem(  hDlg,  idc  ),  SW_SHOW  );
			 idc  =  p->iIDC_DEL;
			 ShowWindow(  GetDlgItem(  hDlg,  idc  ),  SW_SHOW  );

			 idc  =  p->iIDC_LIST_vcServer;
			 rc  =  p->rcIDC_LIST_vcServer;
			 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
			 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
			 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

			 idc  =  p->iIDC_ADD;
			 rc  =  p->rcIDC_ADD;
			 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
			 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
			 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

			 idc  =  p->iIDC_MODIFY;
			 rc  =  p->rcIDC_MODIFY;
			 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
			 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
			 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

			 idc  =  p->iIDC_DEL;
			 rc  =  p->rcIDC_DEL;
			 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
			 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
			 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 }


	return  0;
}


INT_PTR CALLBACK dlgProc_qnmCfgOptionsIsClient(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	void	*	pDlg	=	(  void  *  )GetWindowLongPtr(  hDlg,  GWLP_USERDATA  );

	UNREFERENCED_PARAMETER(lParam);
	switch  (  message  ) {
			case  WM_INITDIALOG:  {
				  pDlg  =  (  void  *  )lParam;
				  //
				  qyWnd_Attach(  pDlg,  hDlg  );

				  DLG_guiData_qnmCfgOptionsIsClient	*	pGuiData;  pGuiData	=	(  DLG_guiData_qnmCfgOptionsIsClient  *  )qyWnd_getGuiData(  pDlg  );

  				  #ifdef  __APP_qyMc_touchscreen__
						  makeDlgResizable(  hDlg  );
				  #endif
				  //
				  dlgLayout_qnmCfgOptionsIsClient(  pDlg,  hDlg  );
				  sizeAllControls_dlgQnmCfgOptionsIsClient(  hDlg,  pGuiData  );
				  //
				  if  (  dlgQnmCfgOptionsIsClient_OnInitDialog(  hDlg,  qyWnd_getVar(  pDlg  )  )  )  {
					  EndDialog(  hDlg,  -1  );
				  }
				  pGuiData->bInited  =  TRUE;
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
				 if  (  myDialogProc_qnmCfgOptionsIsClient(  pDlg,  hDlg,  message,  wParam,  lParam  )  )  return  TRUE;
				 }
				 break;
			case  WM_MOVING:  {
				  #ifdef  __APP_qyMc_touchscreen__
						  DLG_guiData_qnmCfgOptionsIsClient	*	pGuiData;  pGuiData	=	(  DLG_guiData_qnmCfgOptionsIsClient  *  )qyWnd_getGuiData(  pDlg  );
						  if  (  pGuiData->bInited  )  {
							  RECT	rc;
							  GetWindowRect(  hDlg,  &rc  );
							  HWND	hParent  =  GetParent(  hDlg  );
							  MoveWindow(  hParent,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  TRUE  );
						  }
			      #endif
				  }
				  break;
			case  WM_SIZE:  {
				  #ifdef  __APP_qyMc_touchscreen__
						  DLG_guiData_qnmCfgOptionsIsClient	*	pGuiData;  pGuiData	=	(  DLG_guiData_qnmCfgOptionsIsClient  *  )qyWnd_getGuiData(  pDlg  );
						  if  (  pGuiData->bInited  )  {
							  RECT	rc;
							  GetWindowRect(  hDlg,  &rc  );
							  HWND	hParent  =  GetParent(  hDlg  );
							  MoveWindow(  hParent,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  TRUE  );
						  }
				  #endif
				  sizeAllControls_dlgQnmCfgOptionsIsClient(  hDlg,  (  DLG_guiData_qnmCfgOptionsIsClient  *  )qyWnd_getGuiData(  pDlg  )  );  
				  }
				  break;

			default:
				    if  (  myDialogProc_qnmCfgOptionsIsClient(  pDlg,  hDlg,  message,  wParam,  lParam  )  )  return  TRUE;
					break;
	}

	return (INT_PTR)FALSE;
}


//
 int  showDlgQnmCfgOptionsIsClient(  HINSTANCE  g_hInst,  HWND  hParent,  DLG_guiData_qnmCfgOptionsIsClient  *  pParam,  QY_MC  *  pQyMc  )
{
	int			iErr	=	-1;
	void	*	pWnd	=	NULL;

	//
	if  (  !pQyMc  )  {
		return  -1;
	}

	//
	if  (  !g_hInst  )  g_hInst  =  get_my_hInst( pQyMc );

	//
	//  pWnd  =  newQyWnd(  CONST_qyWndContentType_qnmCfgOptionsIsClient  );
	pWnd  =  newQyWnd_CDlgQnmCfgOptionsIsClient(  );
	if  (  !pWnd  )  goto  errLabel;

	DLG_guiData_qnmCfgOptionsIsClient  *  p	=	(  DLG_guiData_qnmCfgOptionsIsClient  *  )qyWnd_getGuiData(  pWnd  );
	if  (  !p  )  goto  errLabel;
	//
	p->pQyMc  =  pQyMc;
	//
	p->iIDC_STATIC_centerAddr  =  IDC_STATIC_centerAddr;
	p->iIDC_STATIC_cntAddr0  =  IDC_STATIC_cntAddr0;
	p->iIDC_cntIp  =  IDC_cntIp;
	p->iIDC_STATIC_cntAddr1  =  IDC_STATIC_cntAddr1;
	p->iIDC_EDIT_cntAddr1  =  IDC_EDIT_cntAddr1;
	p->iIDC_STATIC_cntAddr2  =  IDC_STATIC_cntAddr2;
	p->iIDC_EDIT_cntAddr2  =  IDC_EDIT_cntAddr2;
	p->iIDC_STATIC_cntName  =  IDC_STATIC_cntName;
	p->iIDC_cntName  =  IDC_cntName;
	p->iIDC_STATIC_cntPort  =  IDC_STATIC_cntPort;
	p->iIDC_cntPort  =  IDC_cntPort;
	//
	p->iIDC_CHECK_useDb  =  IDC_CHECK_useDb;	//  2013/02/20
	//
	p->iIDCANCEL  =  IDCANCEL;
	p->iIDOK  =  IDOK;
	p->iIDC_BUTTON_more  =  IDC_BUTTON_more;
	p->iIDC_LIST_vcServer  =  IDC_LIST_vcServer;
	p->iIDC_ADD  =  IDC_ADD;
	p->iIDC_MODIFY  =  IDC_MODIFY;
	p->iIDC_DEL  =  IDC_DEL;


	p->pf_SetDlgItemText  =  mySetDlgItemText;
	p->pf_GetDlgItemText  =  GetDlgItemText;

	if  (  pParam  )  {
		p->iParam_qyDlgType  =  pParam->iParam_qyDlgType;
		p->iItemSelected  =  pParam->iItemSelected;
		p->rc  =  pParam->rc;
	}
 
#ifdef  IDD_qnmCfgOptions_isClient_ce
	if  (  DialogBoxParam(  g_hInst,  MAKEINTRESOURCE(  IDD_qnmCfgOptions_isClient_ce  ),  hParent,  dlgProc_qnmCfgOptionsIsClient,  (  LPARAM  )pWnd  )  !=  IDOK  )  goto  errLabel;
#else
	if  (  DialogBoxParam(  g_hInst,  MAKEINTRESOURCE(  IDD_qnmCfgOptions_isClient  ),  hParent,  dlgProc_qnmCfgOptionsIsClient,  (  LPARAM  )pWnd  )  !=  IDOK  )  goto  errLabel;
#endif

	iErr  =  0;
errLabel:
	if  (  pWnd  )  freeQyWnd(  pWnd  );
	return  iErr;
}