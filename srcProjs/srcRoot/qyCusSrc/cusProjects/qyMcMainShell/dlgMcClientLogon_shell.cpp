
#include	"stdafx.h"
#include	<mmsystem.h>

#include	<windows.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCusResPublic.h"
#include	"qyOpenShellCommon.h"
#include	"qmOpenCommon.h"
#include	"qmShellPublic.h"

//#include	"qyCommon.h"
//#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"

#include	"myresource.h"
//  #include	"ceMenuBar.h"
#include	"testOnly.h"
//

//
 int  gGuiData_init(  unsigned short usLangId,  G_guiData_qyMc  *  pGuiData  )
{
	if  (  pGuiData->bInited  )  return  -1;

#if  !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
	pGuiData->pf_MessageBox  =  myMessageBox;
#else
	pGuiData->pf_MessageBox  =  myMessageBox;
#endif
	//  pGuiData->pf_showDlgMcClientLogon  =  showDlgMcClientLogon;
	pGuiData->pf_showDlgQnmCfgOptionsIsClient  =  showDlgQnmCfgOptionsIsClient;
#if  defined(  WINCE  )  ||  defined(  __WINCE__  )
	pGuiData->pf_newDlgTalk_ce  =  newDlgTalk_ce;
#endif
	pGuiData->pf_newDlgInstantAssistant  =  newDlgInstantAssistant;


	//  2013/02/17
	{

		//
		HDC hScreenDC=::GetDC(NULL);
		int  maxxScreen = GetDeviceCaps(hScreenDC,HORZRES);
		int  maxyScreen = GetDeviceCaps(hScreenDC,VERTRES);
		::ReleaseDC(NULL,hScreenDC);		

#ifdef  __WINCE__
		#define		DEFAULT_maxxScreen		640
		#define		DEFAULT_maxyScreen		480
#else
		#define		DEFAULT_maxxScreen		1024
		#define		DEFAULT_maxyScreen		768
#endif
		pGuiData->fx  =  maxxScreen  *  1.0  /  DEFAULT_maxxScreen;
		pGuiData->fy  =  maxyScreen  *  1.0  /  DEFAULT_maxyScreen;


#define		DEFAULT_faceName_list					_T(  "Tahoma"  )
#define		DEFAULT_h_font_list						30
			//
#define		DEFAULT_h_font_dlgTalk_peerInfo			20
			//
#define		DEFAULT_faceName_static					_T(  "Tahoma"  )
#define		DEFAULT_h_font_static					15
#define		DEFAULT_faceName_btn					_T(  "Tahoma"  )
#define		DEFAULT_h_font_btn						15	//  18		//  15
#define		DEFAULT_faceName_bar					_T(  "Tahoma"  )
#define		DEFAULT_h_font_bar						12
#define		DEFAULT_faceName_menu					_T(  "Tahoma"  )
#define		DEFAULT_h_font_menu						8


		pGuiData->iH_listFont_default  =  DEFAULT_h_font_list;
		//
		//pGuiData->iH_listFont_text_default  =  22;
		//
		//  2017/10/01
		pGuiData->iH_listFont_dlgTalk_peerInfo_default  =  DEFAULT_h_font_dlgTalk_peerInfo;
		//
		pGuiData->iH_static_default  =  DEFAULT_h_font_static;  
		pGuiData->iH_btn_default  =  DEFAULT_h_font_btn;
		pGuiData->iH_bar_default  =  DEFAULT_h_font_bar;
		pGuiData->iH_menu_default	=	DEFAULT_h_font_menu;

		LOGFONT	lf;
		memset(  &lf,  0,  sizeof(  lf  )  );
		::lstrcpyn(  lf.lfFaceName,  DEFAULT_faceName_list,  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
		lf.lfHeight  =  pGuiData->iH_listFont_default  *  pGuiData->fy;
		pGuiData->hFont_list  =  CreateFontIndirect(  &lf  );  

#if  0
		memset(  &lf,  0,  sizeof(  lf  )  );
		::lstrcpyn(  lf.lfFaceName,  _T(  "System"  ),  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
		lf.lfHeight  =  pGuiData->iH_listFont_text_default  *  pGuiData->fy;
		pGuiData->hFont_list_text  =  CreateFontIndirect(  &lf  );
#endif
		//  2017/10/01
		memset(  &lf,  0,  sizeof(  lf  )  );
		::lstrcpyn(  lf.lfFaceName,  DEFAULT_faceName_list,  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
		lf.lfHeight  =  pGuiData->iH_listFont_dlgTalk_peerInfo_default  *  pGuiData->fy;
		pGuiData->hFont_list_dlgTalk_peerInfo  =  CreateFontIndirect(  &lf  );  
		

		//
#ifdef  __APP_qyMc_touchscreen__	//  2013/02/17. 对pc客户端, 为保持界面的一致性, btn和static的字体不要变化
		memset(  &lf,  0,  sizeof(  lf  )  );
		::lstrcpyn(  lf.lfFaceName,  DEFAULT_faceName_static,  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
		lf.lfHeight  =  pGuiData->iH_static_default  *  pGuiData->fy;
		pGuiData->hFont_static  =  CreateFontIndirect(  &lf  );  

		memset(  &lf,  0,  sizeof(  lf  )  );
		::lstrcpyn(  lf.lfFaceName,  DEFAULT_faceName_btn,  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
		lf.lfHeight  =  pGuiData->iH_btn_default  *  pGuiData->fy;
		pGuiData->hFont_btn  =  CreateFontIndirect(  &lf  );  
#endif

		memset(  &lf,  0,  sizeof(  lf  )  );
		::lstrcpyn(  lf.lfFaceName,  DEFAULT_faceName_bar,  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
		lf.lfHeight  =  pGuiData->iH_bar_default  *  pGuiData->fy;
		pGuiData->hFont_bar  =  CreateFontIndirect(  &lf  );  

		memset(  &lf,  0,  sizeof(  lf  )  );
		::lstrcpyn(  lf.lfFaceName,  DEFAULT_faceName_menu,  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
		lf.lfHeight  =  pGuiData->iH_menu_default  *  pGuiData->fy;
		pGuiData->hFont_menu  =  CreateFontIndirect(  &lf  );  

	}



	//  2011/07/26
	 LOGFONT	lf;

	 memset(  &lf,  0,  sizeof(  lf  )  );
	 ::lstrcpyn(  lf.lfFaceName,  _T(  "Tahoma"  ),  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
	 lf.lfHeight  =  18;		 //  18;	//  40;	//  50;
	 lf.lfWeight  =  700;
	 pGuiData->lfHeight_videoHint_320x240  =  lf.lfHeight;
	 pGuiData->hFont_videoHint_320x240  =  CreateFontIndirect(  &lf  );  

	 memset(  &lf,  0,  sizeof(  lf  )  );
	 ::lstrcpyn(  lf.lfFaceName,  _T(  "Tahoma"  ),  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
	 lf.lfHeight  =  18;		//  36;	//  40;	//  50;
	 lf.lfWeight  =  700;
	 //  lf.lfQuality  =  CLEARTYPE_NATURAL_QUALITY;
	 pGuiData->lfHeight_videoHint_640x480  =  lf.lfHeight;
	 pGuiData->hFont_videoHint_640x480  =  CreateFontIndirect(  &lf  );  

	 memset(  &lf,  0,  sizeof(  lf  )  );
	 ::lstrcpyn(  lf.lfFaceName,  _T(  "Tahoma"  ),  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
	 lf.lfHeight  =  64;	//  40;	//  50;
	 lf.lfWeight  =  700;
	 pGuiData->lfHeight_videoHint_1280x720  =  lf.lfHeight;
	 pGuiData->hFont_videoHint_1280x720  =  CreateFontIndirect(  &lf  );  

	 memset(  &lf,  0,  sizeof(  lf  )  );
	 ::lstrcpyn(  lf.lfFaceName,  _T(  "Tahoma"  ),  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
	 lf.lfHeight  =  96;	//  40;	//  50;
	 lf.lfWeight  =  700;
	 pGuiData->lfHeight_videoHint_1920x1080  =  lf.lfHeight;
	 pGuiData->hFont_videoHint_1920x1080  =  CreateFontIndirect(  &lf  );  

	 //
	 memset(  &lf,  0,  sizeof(  lf  )  );
	 switch  (  usLangId  )  {
			 case  CONST_langId_PRC:
				   ::lstrcpyn(  lf.lfFaceName,  _T(  "Simhei"  ),  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
				   break;
			 case CONST_langId_tw:		//  msjhbd
				   ::lstrcpyn(  lf.lfFaceName,  _T(  "Tahoma"  ),  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
				   break;
			 default:
				    ::lstrcpyn(  lf.lfFaceName,  _T(  "Tahoma"  ),  sizeof(  lf.lfFaceName  )  /  sizeof(  lf.lfFaceName[0]  )  );
					break;
	 }
	 lf.lfHeight  =  18;		//  36;	//  100;	//  30;	//  40;	//  50;
	 lf.lfWeight  =  1000;
	 pGuiData->lfHeight_demoHint_screen  =  lf.lfHeight;
	 pGuiData->hFont_demoHint_screen  =  CreateFontIndirect(  &lf  );  


	 pGuiData->bInited  =  TRUE;

	return  0;
}

  int  gGuiData_exit(  G_guiData_qyMc  *  pGuiData  )
{
	if  (  !pGuiData->bInited  )  return  0;

	if  (  pGuiData->hFont_demoHint_screen  )  {
		 DeleteObject(  pGuiData->hFont_demoHint_screen  );  pGuiData->hFont_demoHint_screen  =  NULL;
	 }
	if  (  pGuiData->hFont_videoHint_320x240  )  {  //  2011/08/10
		DeleteObject(  pGuiData->hFont_videoHint_320x240  );  pGuiData->hFont_videoHint_320x240  =  NULL;
	}
	if  (  pGuiData->hFont_videoHint_640x480  )  {
		 DeleteObject(  pGuiData->hFont_videoHint_640x480  );  pGuiData->hFont_videoHint_640x480  =  NULL;
	}
	if  (  pGuiData->hFont_videoHint_1280x720  )  {
		 DeleteObject(  pGuiData->hFont_videoHint_1280x720  );  pGuiData->hFont_videoHint_1280x720  =  NULL;
	}
	if  (  pGuiData->hFont_videoHint_1920x1080  )  {
		 DeleteObject(  pGuiData->hFont_videoHint_1920x1080  );  pGuiData->hFont_videoHint_1920x1080  =  NULL;
	}

	//  2013/01/15
	pGuiData->bInited  =  FALSE;

	return  0;
}

//  这里不能直接调用CDlgMcCliengLogon, 只能用newQyWnd(  ), qyWnd_getGuiData(  )等函数
//  应该有一个showMcClientLong(  )的函数，先newQyWnd(  ), 然后调用DialogBox(  )等。最后释放。。。


 int  dlgLayout_mcClientLogon(  void  *  pDlg,  HWND  hDlg  )
{
	G_guiData_qyMc	*	pGuiData	=	get_g_guiData(  );
	
#ifdef  __DEBUG__
		TCHAR	*	pT	=	getResStr(  0,  pGuiData->pCusRes,  CONST_resId_seqNo  );
#endif

	cusDlgRes(  0,  pGuiData->pCusRes,  hDlg,  IDD_mcClient_logon  );


#if  defined(  __WINCE__  )  ||  defined(  __APP_qyMc_touchscreen__  )  

	//  return 0;
	
	DLG_guiData_mcClientLogon  *  p	=	(  DLG_guiData_mcClientLogon  *  )qyWnd_getGuiData(  pDlg  );
	if  (  !p  )  goto  errLabel;

	RECT	rc;
	GetClientRect(  hDlg,  &rc  );
	p->w_org  =  rc.right  -  rc.left;
	p->h_org  =  rc.bottom  -  rc.top;

	if  (  !p->w_org  ||  !p->h_org  )  goto  errLabel;

	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_STATIC_logonServer  ),  &p->rcIDC_STATIC_logonServer  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_logonServer,  2  );
		
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_COMBO_logonServer  ),  &p->rcIDC_COMBO_logonServer  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_COMBO_logonServer,  2  );
		
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_STATIC_usrName  ),  &p->rcIDC_STATIC_usrName  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_usrName,  2  );
	
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_NAME  ),  &p->rcIDC_NAME  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_NAME,  2  );

	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_STATIC_passwd  ),  &p->rcIDC_STATIC_passwd  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_passwd,  2  );

	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_PASSWD  ),  &p->rcIDC_PASSWD  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_PASSWD,  2  );

	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_STATIC_hint  ),  &p->rcIDC_STATIC_hint  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_hint,  2  );

	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDOK  ),  &p->rcIDOK  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDOK,  2  );

	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_option  ),  &p->rcIDC_BUTTON_option  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_option,  2  );

	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDCANCEL  ),  &p->rcIDCANCEL  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDCANCEL,  2  );

	int	w, h;

#ifdef  __WINCE__
	HDC hScreenDC=::GetDC(NULL);
	int  maxxScreen = GetDeviceCaps(hScreenDC,HORZRES);
	int  maxyScreen = GetDeviceCaps(hScreenDC,VERTRES);
	::ReleaseDC(NULL,hScreenDC);		

	w  =  maxxScreen;  h  =  maxyScreen;
	MoveWindow(  hDlg,  0,  0,  w,  h,  TRUE  );
#else
	HWND	hParent	=	GetParent(  hDlg  );
	if  (  !hParent  )  goto  errLabel;
	GetWindowRect(  hParent,  &rc  );
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;
	//MoveWindow(  hDlg,  rc.left,  rc.top,  w,  h,  TRUE  );
#endif


#endif

errLabel:
	return  0;

}

 int  sizeAllControls_dlgMcClientLogon(  HWND  hDlg,  DLG_guiData_mcClientLogon  *  p  )
{
	RECT	rc;
	int		w,  h;

	if  (  !p->w_org  ||  !p->h_org  )  return  -1;

	//
	GetClientRect(  hDlg,  &rc  );
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;

	int	idc;
	int  iX,  iY,  iW,  iH;
	float  fx,  fy;
	fx  =  1.  *  w  /  p->w_org;
	fy  =  1.  *  h  /  p->h_org;

	//
	BOOL	bMultiLogon  =  FALSE;	//  TRUE;
#ifdef  __APP_qyMc_touchscreen__
		bMultiLogon  =  TRUE;
#endif

	//
	idc  =  p->iIDC_STATIC_logonServer;
	if  (  bMultiLogon  )  {	
		rc  =  p->rcIDC_STATIC_logonServer;	
		iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  	
		MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
		}
	else  {
		  ShowWindow(  GetDlgItem(  hDlg,  idc  ),  SW_HIDE  );
	}


	idc  =  p->iIDC_COMBO_logonServer;
	if  (  bMultiLogon  )  {		
		rc  =  p->rcIDC_COMBO_logonServer;	
		iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;	
		iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  		
		MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
		}
	else  {
		  ShowWindow(  GetDlgItem(  hDlg,  idc  ),  SW_HIDE  );
	}

	//
	idc  =  p->iIDC_STATIC_usrName;
	rc  =  p->rcIDC_STATIC_usrName;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_NAME;
	rc  =  p->rcIDC_NAME;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_passwd;
	rc  =  p->rcIDC_STATIC_passwd;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_PASSWD;
	rc  =  p->rcIDC_PASSWD;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_hint;
	rc  =  p->rcIDC_STATIC_hint;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  ); 

	idc  =  p->iIDOK;
	rc  =  p->rcIDOK;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  ); 

	idc  =  p->iIDC_BUTTON_option;
	rc  =  p->rcIDC_BUTTON_option;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  ); 

	idc  =  p->iIDCANCEL;
	rc  =  p->rcIDCANCEL;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  ); 

	return  0;
}


// Message handler for about box.
INT_PTR CALLBACK dlgProc_mcClientLogon(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	//  void	*	pDlg	=	(  void  *  )GetWindowLong(  hDlg,  GWLP_USERDATA  );
	void	*	pDlg	=	(  void  *  )GetWindowLongPtr(  hDlg,  GWLP_USERDATA  );

	UNREFERENCED_PARAMETER(lParam);
	switch  (  message  ) {
		   	case  WM_INITDIALOG:
				  pDlg  =  (  void  *  )lParam;
				  //  SetWindowLong(  hDlg,  GWLP_USERDATA,  (  LONG )pDlg  );
				  qyWnd_Attach(  pDlg,  hDlg  );
				  //
				  #ifdef  __APP_qyMc_touchscreen__
						  makeDlgResizable(  hDlg  );
				  #endif
				  //
				  dlgLayout_mcClientLogon(  pDlg,  hDlg  );
				  sizeAllControls_dlgMcClientLogon(  hDlg,  (  DLG_guiData_mcClientLogon  *  )qyWnd_getGuiData(  pDlg  )  );
				  //
				  //  myDialogProc_mcClientLogon(  pDlg,  hDlg,  message,  wParam,  lParam  );

				  if  (  dlgMcClientLogon_OnInitDialog(  hDlg,  qyWnd_getVar(  pDlg  )  )  )  {
					  EndDialog(  hDlg,  -1  );
				  }
				  return (INT_PTR)TRUE;
				  break;

			case  WM_TIMER:

				  dlgMcClientLogon_OnTimer(  hDlg,  wParam  );

				  return  (  INT_PTR  )TRUE;
				  break;

			case  WM_COMMAND:  {
				  WORD  wNotifyCode = HIWORD(wParam); 
				  WORD  wID = LOWORD(wParam); 
				  HWND  hwndCtl = (HWND) lParam;

				 if  ( wID == IDCANCEL  )  {
					 EndDialog(hDlg, LOWORD(wParam));
					 return (INT_PTR)TRUE;
				 }
				 
				 DLG_guiData_mcClientLogon  *  pGuiData  =  (  DLG_guiData_mcClientLogon  *  )qyWnd_getGuiData(  pDlg  );

				 if  (  wID == IDOK  )  {
					 TCHAR	name[64]	=	_T(  ""  );
					 TCHAR	passwd[64]	=	_T(  ""  );
					 //
					 pGuiData->pf_GetDlgItemText(  hDlg,  pGuiData->iIDC_NAME,  name,  mycountof(  name  )  );  
					 pGuiData->pf_GetDlgItemText(  hDlg,  pGuiData->iIDC_PASSWD,  passwd,  mycountof(  passwd  )  );  
					 //
					 if  (  !dlgMcClientLogon_OnOK(  hDlg,  name,  passwd  )  )  {
						 EndDialog(  hDlg,  LOWORD(  wParam  )  );
					 }
					 return  TRUE;
				 }
				 if  (  wID  ==  pGuiData->iIDC_BUTTON_option  )  {

					 showDlgQnmCfgOptionsIsClient(  NULL,  hDlg,  0,  pGuiData->pQyMc  );

					 dlgMcClientLogon_refresh(  hDlg  );

					 return  TRUE;
				 }

				 //
				 if  (  wNotifyCode  ==  CBN_SELCHANGE  )  {
					 dlgMcClientLogon_OnCbnSelchangeCombologonserver(  hDlg,  qyWnd_getVar(  pDlg  )  );
					 return  TRUE;
				 }

				 }
				 break;

			case  WM_MOVING:  {
				  #ifdef  __APP_qyMc_touchscreen__
						  DLG_guiData_mcClientLogon  *  pGuiData  =  (  DLG_guiData_mcClientLogon  *  )qyWnd_getGuiData(  pDlg  );
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
						  DLG_guiData_mcClientLogon  *  pGuiData  =  (  DLG_guiData_mcClientLogon  *  )qyWnd_getGuiData(  pDlg  );
						  if  (  pGuiData->bInited  )  {
							  RECT	rc;
							  GetWindowRect(  hDlg,  &rc  );
							  HWND	hParent  =  GetParent(  hDlg  );
							  MoveWindow(  hParent,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  TRUE  );
						  }
			      #endif
				  sizeAllControls_dlgMcClientLogon(  hDlg,  (  DLG_guiData_mcClientLogon  *  )qyWnd_getGuiData(  pDlg  )  );
				  }
				  break;

			case  WM_DESTROY:
				  dlgMcClientLogon_OnDestroy(  hDlg,  qyWnd_getVar(  pDlg  )  );
				  break;
			case  WM_PAINT:  {
								
				  HDC	hDc	=	GetDC(  hDlg  );
				  if  (  hDc  )  {
					  RECT rect;
					  GetClientRect(  hDlg,  &rect);

					  #if  10
					  //RGB(29,157,38));
					  TRIVERTEX        vert[2] ;
					  GRADIENT_RECT    gRect;
					  vert [0] .x      = 0;
					  vert [0] .y      = 0;
					  vert [0] .Red    = 0x1d00;	//0x5100;
					  vert [0] .Green  = 0x9d00;	//0xf500;
					  vert [0] .Blue   = 0x2600;	//0x0a00;
					  vert [0] .Alpha  = 0x0000;

					  vert [1] .x      = rect.right;
					  vert [1] .y      = 35;//rect.bottom; 
					  vert [1] .Red    = 0x1d00;	//0x0700;
					  vert [1] .Green  = 0x9d00;	//0xf800;
					  vert [1] .Blue   = 0x2600;	//0xf100;
					  vert [1] .Alpha  = 0x0000;

					  gRect.UpperLeft  = 0;
					  gRect.LowerRight = 1;
					  GradientFill(  hDc,vert,2,&gRect,1,GRADIENT_FILL_RECT_H);

					  #endif

					  ReleaseDC(  hDlg,  hDc  );
				  }

			      }
				  
				  break;
				  		case  WM_NCACTIVATE:
			case  WM_NCPAINT:
#if  0
				  HWND  hwnd;  hwnd   =  hDlg;
				  RECT  rw,rc;
				  POINT  pt;
				  HDC  hdc;
				  		
				  ::GetWindowRect(hwnd, &rw);
        		  ::GetClientRect(hwnd, &rc);
        		  pt.x = rc.left;
        		  pt.y = rc.top;
        		  ::ClientToScreen(hwnd, &pt);
        		  OffsetRect(&rc, pt.x - rw.left, pt.y - rw.top);
				          
				  hdc = ::GetWindowDC(hwnd);
        		  ExcludeClipRect(hdc, rc.left, rc.top, rc.right, rc.bottom);
				          
				  OffsetRect(&rw, -rw.left, -rw.top);
        		  // 使用这个方式比使用fillrect函数填充效果好，不闪烁
        		  //SetBkColor(hdc, 0xBF7B18);
				  SetBkColor( hdc, RGB(29,157,38)  );
        		  ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rw, 0, 0, 0);
				          
				  ::ReleaseDC(hwnd, hdc);
        
				 return TRUE;//ret;
#endif


			default:

					//  if  (  myDialogProc_mcClientLogon(  pDlg,  hDlg,  message,  wParam,  lParam  )  )  return  TRUE;

					break;
	}




	return (INT_PTR)FALSE;
}


 BOOL WINAPI  mySetDlgItemText( HWND hDlg, int nIDDlgItem, LPCTSTR lpString  )
{
	SetDlgItemText(  hDlg,  nIDDlgItem,  lpString  );
	UpdateWindow(  GetDlgItem(  hDlg,  nIDDlgItem  )  );
	return  TRUE;
}


 //
 int  showDlgMcClientLogon(  HINSTANCE  g_hInst,  HWND  hMainWnd,  void  *  pQyMcParam,  PARAM_showDlgMcLogon  *  pParam  )
{
	int			iErr	=	-1;
	void	*	pWnd	=	NULL;
	QY_MC  *  pQyMc  =  (  QY_MC  *  )pQyMcParam;

	//
	if  (  !pQyMc  )  {
		return  -1;
	}
	
	//
	if  (  !g_hInst  )  g_hInst  =  get_my_hInst( pQyMc );

	//  2014/10/15
#ifdef  __TEST_ONLY__
		if  (  b__TEST_ON__(  )  )  {
			myMessageBox(  NULL,  _T(  "TEST ON"  ),  _T(  "HAHA"  ),  MB_OK  );
		}
#endif

	//
	//  pWnd  =  newQyWnd(  CONST_qyWndContentType_mcClientLogon  );
	pWnd  =  newQyWnd_CDlgMcClientLogon(  );
	if  (  !pWnd  )  goto  errLabel;

	DLG_guiData_mcClientLogon  *  p	=	(  DLG_guiData_mcClientLogon  *  )qyWnd_getGuiData(  pWnd  );
	if  (  !p  )  goto  errLabel;

	//  2016/09/16
	p->pQyMc  =  pQyMc;

	//
	p->iIDC_STATIC_logonServer  =  IDC_STATIC_logonServer;
	p->iIDC_COMBO_logonServer  =  IDC_COMBO_logonServer;
	p->iIDC_STATIC_usrName  =  IDC_STATIC_usrName;
	p->iIDC_NAME  =  IDC_NAME;
	p->iIDC_STATIC_passwd  =  IDC_STATIC_passwd;
	p->iIDC_PASSWD  =  IDC_PASSWD;
	p->iIDC_STATIC_hint  =  IDC_STATIC_hint;
	p->iIDOK  =  IDOK;
	p->iIDCANCEL  =  IDCANCEL;
	p->iIDC_BUTTON_option  =  IDC_BUTTON_option;
	p->iIDC_CHECK_autoLogon  =  IDC_CHECK_autoLogon;
	p->iIDC_CHECK_savePasswd  =  IDC_CHECK_savePasswd;

	p->pf_GetDlgItemText  =  GetDlgItemText;
	p->pf_SetDlgItemText  =  mySetDlgItemText;

	HWND hWndParent  =  NULL;		//  2011/02/26
	hWndParent  =  hMainWnd;

	if  (  DialogBoxParam(  g_hInst,  MAKEINTRESOURCE(  IDD_mcClient_logon  ),  hWndParent,  dlgProc_mcClientLogon,  (  LPARAM  )pWnd  )  !=  IDOK  )  {
		#ifdef  _DEBUG
				int  tt  =  GetLastError(  );
				TCHAR  tBuf[128];
				//  1814 ERROR_RESOURCE_NAME_NOT_FOUND
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "showDlgMcClientLogon failed, DialogBoxParam failed, lastErr %d\n"  ),  tt  );
				OutputDebugString(  tBuf  );
		#endif
		goto  errLabel;
	}

	iErr  =  0;
errLabel:
	if  (  pWnd  )  freeQyWnd(  pWnd  );
	return  iErr;
}


