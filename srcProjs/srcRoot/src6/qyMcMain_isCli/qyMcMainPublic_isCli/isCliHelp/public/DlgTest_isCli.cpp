// DlgTest.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"

#include	"myresource.h"

#include	"DlgTest_isCli.h"
#include	"afxdialogex.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"
#include	"qmcVWall.h"
#include	"WallTalkers.h"
//  #include	"DlgDynBmps.h"

#include	"qmcVideoCapture_isCli.h"
//  #include	"DlgCfgVideoConference.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"

#include	"qyCusResTemp.h"

#include	"qyAvRecordPublic.h"

#include	"sp.h"
#include	"objType_tmp.h"

#if  !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )  
	//
	#include	"qyPs.h"
#endif

#include	"dlgTalkProc.h"

#include	"qmcGpsProc.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__
	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>
#include	<dsound.h>

#include	"qmcDmoPublic.h"

#include	"qmcVideoCapture_dx.h"

#include	"myfourcc.h"
#include	"mywmcodecconst.h"

#include	"qmcCmdProc.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"qmcCommFunc_iscli.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


 __declspec(  dllexport  )  int  testLocalAv(  HWND  hParent  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	int						iErr		=		-1;
	QY_MC				*	pQyMc		=		QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProcInfo	=		QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	MIS_CNT				*	pMisCnt		=		getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;
	//
#ifndef  __NOTSUPPORT_testLocalAv__
	//  CDlgDynBmps			*	pDlg		=		NULL;
	CDlgTest_isCli			*	pDlg			=		NULL;
	CWaitCursor				cur;
#endif

	traceLogA(  "testLocalWebcam enters"  );

	if  (  IsWindow(  pProcInfo->hWnd_testWebcam  )  )  {
		MACRO_SetForegroundWindow(  pProcInfo->hWnd_testWebcam  );
		return  0;
	}

	//
#ifndef  __NOTSUPPORT_testLocalAv__
	{
		RECT					rect;
		unsigned  short		usCnt_monPics_row	=	1;
		unsigned  short		usCnt_monPics_col	=	1;
		/*
		unsigned  int		uiInitW				=	pVar->av.localAv.videoCaptureProcInfo.vh_org.bih.biWidth;
		unsigned  int		uiInitH				=	pVar->av.localAv.videoCaptureProcInfo.vh_org.bih.biHeight;
		//
		if  (  uiInitH  <  300  )  {
			uiInitW  =  (  unsigned  int  )(  uiInitW  /  (  uiInitH  *  1.  )  *  300.  );
			uiInitH  =  300;
		}
		*/
		unsigned  int  uiInitW  =  640  +  30;
		unsigned  int  uiInitH  =  480  +  30;
		//  2013/03/06
		int  iResId_menu  =  CONST_resId_menu_dlgTest;
		//
		//  pDlg  =  new  CDlgTestWebcam(  CWnd::GetDesktopWindow(  )  );
		CWnd  *  pParent  =  CWnd::GetDesktopWindow(  );
		pParent  =  CWnd::FromHandle(  hParent  );
		pDlg  =  new  CDlgTest_isCli(  pParent  );	//  CDlgDynBmps(  pParent  );
		if  (  !pDlg  )  goto  errLabel;
		if  (  !pDlg->bSetDlgInfo(  CONST_qyWndContentType_testLocalAv,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_localVideo  ),  iResId_menu  )  )  goto  errLabel;

		if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		
		//
		pDlg->ShowWindow(  SW_SHOW  );
		//
		pProcInfo->hWnd_testWebcam  =  pDlg->m_hWnd;
		
		pDlg  =  NULL;
	}
#endif

	//

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
#ifndef  __NOTSUPPORT_testLocalAv__
		if  (  pDlg  )  delete  pDlg;
#endif
	}

	traceLogA(  "testLocalWebcam leaves with %s",  iErr  ?  "Failed"  :  "OK"  );

	return  iErr;
}


// CDlgTest_isCli dialog

IMPLEMENT_DYNAMIC(CDlgTest_isCli, CDialog)

CDlgTest_isCli::CDlgTest_isCli(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTest_isCli::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	
	m_var.m_pParent = pParent;
	m_var.m_nID = CDlgTest_isCli::IDD;

	//
	m_var.guiData.iIDC_STATIC_pic0  =  IDC_STATIC_pic0;

	m_var.guiData.iIDC_STATIC_testAvHint  =  IDC_STATIC_testAvHint;
	
	m_var.guiData.iIDC_BUTTON_aDev  =  IDC_BUTTON_aDev;
	m_var.guiData.iIDC_STATIC_aDev  =  IDC_STATIC_aDev;
	
	m_var.guiData.iIDC_BUTTON_vDev  =  IDC_BUTTON_vDev;
	m_var.guiData.iIDC_STATIC_vDev  =  IDC_STATIC_vDev;
	
	m_var.guiData.iIDC_BUTTON_cfgCapturePin_v  =  IDC_BUTTON_cfgCapturePin_v;

	m_var.guiData.iIDC_BUTTON_testAv  =  IDC_BUTTON_testAv;
	
	m_var.guiData.iIDCANCEL  =  IDCANCEL;

	

	//  2013/03/19
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	m_var.bIncludeACap  =  pProcInfo->cfg.policy.audio.uiRecordType  ==  CONST_recordType_directX;	

	//  2014/04/06
	m_var.ucbAutoClip  =  FALSE;
}

CDlgTest_isCli::~CDlgTest_isCli()
{
}


BOOL  CDlgTest_isCli::bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_menu  )
{
	BOOL		bRet  =  FALSE;

	m_var.iWndContentType  =  iWndContentType;
	safeTcsnCpy(  title,  m_var.title,  mycountof(  m_var.title  )  );
	m_var.iResId_menu  =  iResId_menu;
	bRet  =  TRUE;

	return  bRet;
}

BOOL CDlgTest_isCli::Create(const RECT& rect)
{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProc		=	NULL;

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): ÔÚ´´½¨¶Ô»°¿òÖ®Ç°Ó¦ÏÈÉèÖÃ³õÊ¼Êý¾Ý"  );
		return  FALSE;
	}
	*/

	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	

	//
	if  (  !CDialog::Create(  this->m_var.m_nID, m_var.m_pParent  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  CDlgTest_isCli::bQuitDlg(  )		
{		
	BOOL		bRet	=	FALSE;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	DestroyWindow(  );

	bRet  =  TRUE;
	return  bRet;
 }

  int  CDlgTest_isCli::sizeAllControls(  )
{

	RECT	rc;
	GetClientRect(  &rc  );
	int  w,  h;
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;


	DLG_guiData_test_isCli  *  p  =  &m_var.guiData;
	HWND						hDlg	=	m_hWnd;
	
	//  
	int	idc;
	int  iX,  iY,  iW,  iH;
	float  fx,  fy;
	fx  =  1.  *  w  /  p->iw_org;
	fy  =  1.  *  h  /  p->ih_org;

		
	idc  =  p->iIDC_STATIC_pic0;	
	rc  =  p->rcIDC_STATIC_pic0;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
			
	idc  =  p->iIDC_STATIC_testAvHint;
	rc  =  p->rcIDC_STATIC_testAvHint;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_aDev;	
	rc  =  p->rcIDC_BUTTON_aDev;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
		
	idc  =  p->iIDC_STATIC_aDev;	
	rc  =  p->rcIDC_STATIC_aDev;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
	
	idc  =  p->iIDC_BUTTON_vDev;	
	rc  =  p->rcIDC_BUTTON_vDev;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_vDev;	
	rc  =  p->rcIDC_STATIC_vDev;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
		

	idc  =  p->iIDC_BUTTON_cfgCapturePin_v;	
	rc  =  p->rcIDC_BUTTON_cfgCapturePin_v;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  


	idc  =  p->iIDC_BUTTON_testAv;	
	rc  =  p->rcIDC_BUTTON_testAv;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
	
	idc  =  p->iIDCANCEL;	
	rc  =  p->rcIDCANCEL;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  


	//
	CWnd  *  pCtrl;

	pCtrl  =  GetDlgItem(  m_var.idc  );
	if  (  !pCtrl  )  goto  errLabel;
	pCtrl->Invalidate(  TRUE  );
	//  pCtrl->UpdateWindow(  );

	pCtrl->GetClientRect(  &rc  );

	m_var.iW_pic  =  rc.right  -  rc.left;
	m_var.iH_pic  =  rc.bottom  -  rc.top;

	//
	getCapImages(  m_var.ucbAutoClip,  0,  0,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  NULL,  &m_var.images  );

errLabel:
	return  0;
}

void CDlgTest_isCli::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTest_isCli, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_aDev, &CDlgTest_isCli::OnBnClickedButtonadev)
	ON_BN_CLICKED(IDC_BUTTON_vDev, &CDlgTest_isCli::OnBnClickedButtonvdev)
	ON_BN_CLICKED(IDC_BUTTON_cfgCapturePin_v, &CDlgTest_isCli::OnBnClickedButtoncfgcapturepinv)
	ON_BN_CLICKED(IDC_BUTTON_testAv, &CDlgTest_isCli::OnBnClickedButtontestav)
	ON_WM_DESTROY()
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
	ON_MESSAGE(  CONST_qyWm_postComm,  OnQyPostComm  )
	ON_WM_SIZE()
	ON_COMMAND_RANGE(  ID_MENU_isCmd_min,  ID_MENU_isCmd_max,  OnIsCmd  )
	ON_UPDATE_COMMAND_UI_RANGE(  ID_MENU_isCmd_min,  ID_MENU_isCmd_max,  OnUpdateIsCmd  )
	ON_WM_INITMENUPOPUP()
END_MESSAGE_MAP()


// CDlgTest_isCli message handlers


BOOL CDlgTest_isCli::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	//
	int						iErr				=	-1;
	QY_MC				*	pQyMc				=	QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo			=	QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp	*	pFuncs				=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;


	QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );	
	if  (  !pResMem  )  goto  errLabel;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//
	RECT	rc;

	::GetClientRect(  m_hWnd,  &rc  );

	DLG_guiData_test_isCli  *  p  =  &m_var.guiData;

	p->iw_org  =  rc.right  -  rc.left;  
	p->ih_org  =  rc.bottom  -  rc.top;

	if  (  !p->iw_org  ||  !p->ih_org  )  goto  errLabel;

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_STATIC_pic0  ),  &p->rcIDC_STATIC_pic0  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_STATIC_pic0,  2  );

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_STATIC_testAvHint  ),  &p->rcIDC_STATIC_testAvHint  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_STATIC_testAvHint,  2  );

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_BUTTON_aDev  ),  &p->rcIDC_BUTTON_aDev  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_BUTTON_aDev,  2  );

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_STATIC_aDev  ),  &p->rcIDC_STATIC_aDev  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_STATIC_aDev,  2  );

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_BUTTON_vDev  ),  &p->rcIDC_BUTTON_vDev  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_BUTTON_vDev,  2  );
	
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_STATIC_vDev  ),  &p->rcIDC_STATIC_vDev  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_STATIC_vDev,  2  );
		
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_BUTTON_cfgCapturePin_v  ),  &p->rcIDC_BUTTON_cfgCapturePin_v  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_BUTTON_cfgCapturePin_v,  2  );

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_BUTTON_testAv  ),  &p->rcIDC_BUTTON_testAv  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_BUTTON_testAv,  2  );

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDCANCEL  ),  &p->rcIDCANCEL  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDCANCEL,  2  );
	

	//  m_var.iResId_menu  =

	if  (  m_var.iResId_menu  )  {		
		CMenu			*	pMenu	=	this->GetMenu(  );
		QY_DMITEM		*	pItem;
		unsigned  int		nPos	=	m_var.iResId_menu;		//  CONST_resId_menu_dlgVideos;

		if  (  !pMenu  )  goto  errLabel;
#if  1  //  def  __SUPPORT_wndMenu__
		if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_popupMenu  )  )  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "CDlgDesktopsMon::OnInitDialog failed, pItem CONST_resId_popupMenu is null"  )  );
			#endif
			goto  errLabel;
		}
		if  (  !(  pItem  =  qyGetDmItemByType(  pItem,  nPos,  sizeof(  QY_DMITEM  )  )  )  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "DlgDesktopsMon::OnInitDialog: qyGetDmItemByType failed, nPos %d"  ),  nPos  );
			#endif
			goto  errLabel;
		}
		if  (	 makeDynaMenu(  &pQyMc->cusRes,  pMenu->m_hMenu,  (  QY_DMITEM  *  )pItem->pData,  0,  pQyMc,  0  )  )  goto  errLabel;		
#endif

	}


#ifdef  __APP_qyMc_touchscreen__
	{
		RECT	rc;
		int		w, h;
		HWND	hFrame	=	pQyMc->gui.hMainWnd;
		if  (  !hFrame  )  goto  errLabel;
		::GetWindowRect(  hFrame,  &rc  );
		w  =  rc.right  -  rc.left;
		h  =  rc.bottom  -  rc.top;
		::MoveWindow(  m_hWnd,  rc.left,  rc.top,  w,  h,  TRUE  );		
	}
#endif


	//
	m_var.idc  =  IDC_STATIC_pic0;

	sizeAllControls(  );

	//
	m_var.pCapStuff  =  pFuncs->pf_CAP_STUFF_new(  );		//  2009/09/16		
	if  (  !m_var.pCapStuff  )  goto  errLabel;
	pFuncs->moniker.pf_addDevicesToMenu(  m_var.pCapStuff,  m_var.bIncludeACap,  NULL  );		
	//
	TCHAR	recorder_sel[MAX_monikerDisplayNameLen  +  1]  =  _T(  ""  );		
	TCHAR	webcam_sel[MAX_monikerDisplayNameLen  +  1]	=  _T(  ""  );
	pFuncs->pf_getChosenDevice(  recorder_sel,  mycountof(  recorder_sel  ),  webcam_sel,  mycountof(  webcam_sel  ),  m_var.pCapStuff,  m_var.bIncludeACap,  &m_var.iMenuId_selectedAudio,  &m_var.iMenuId_selectedVideo  );  
#if  0
	if  (  !m_var.iMenuId_selectedAudio  )  {	
		m_var.iMenuId_selectedAudio  =  ID_MENU_ADEVICE0;
	}
#endif
	if  (  !m_var.iMenuId_selectedVideo  )  {	
		m_var.iMenuId_selectedVideo  =  ID_MENU_VDEVICE0;		 
	}

	//
	CAP_STUFF  *  pCapStuff  =  (  CAP_STUFF  *  )m_var.pCapStuff;
	int  index  =  m_var.iMenuId_selectedVideo  -  ID_MENU_VDEVICE0;
	if  (  index  <  0  ||  index  >=  mycountof(  pCapStuff->rgpmVideoMenu  )  )  goto  errLabel;
	//  ChooseDevices(  *pCapStuff,  pCapStuff->rgpmVideoMenu[index],  pCapStuff->pmAudio  );
	pFuncs->pf_myChooseDevices(  pCapStuff,  pCapStuff->rgpmVideoMenu[index],  pCapStuff->pmAudio  );

	//
	TCHAR	tBuf[256]  =  _T(  ""  );
	if  (  pProcInfo->cfg.policy.audio.ucbNot_selectDefaultRecorder  )  {
		pFuncs->moniker.pf_getADevFriendlyName(  m_var.pCapStuff,  m_var.bIncludeACap,  m_var.iMenuId_selectedAudio,  tBuf,  mycountof(  tBuf  )  );
		}
	else  {
		  int  i;
		  for  (  i  =  0;  i  <  pCapStuff->old_audioDevices.iNumADevices;  i  ++  )  {
			   if  (  pCapStuff->old_audioDevices.default_guid_audio  ==  pCapStuff->old_audioDevices.mems[i].guid_audio  )  {
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_useDefault  ),  pCapStuff->old_audioDevices.mems[i].names_audio  );
				   break;		
			   }
		  }

	}
	SetDlgItemText(  IDC_STATIC_aDev,  tBuf  );
	tBuf[0]  =  0;
	//  getMonikerFriendlyName(  getMoniker_v(  m_var.pCapStuff,  m_var.iMenuId_selectedVideo  ),  tBuf,  mycountof(  tBuf  )  );
	pFuncs->moniker.pf_getMonikerProp(  pFuncs->moniker.pf_getMoniker_v(  m_var.pCapStuff,  m_var.iMenuId_selectedVideo  ),  CONST_moniker_FriendlyName,  tBuf,  mycountof(  tBuf  )  );
	SetDlgItemText(  IDC_STATIC_vDev,  tBuf  );

	//
	m_var.pMsgBuf_doWnd_guiMsgArrive  =  (  MIS_MSGU  *  )mymalloc(  sizeof(  MIS_MSGU  )  );	
	if  (  !m_var.pMsgBuf_doWnd_guiMsgArrive  )  goto  errLabel;


	SetWindowText(  m_var.title  );
	//
	SetDlgItemText(  m_var.guiData.iIDC_STATIC_testAvHint,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_testAvHint  )  );

	//  2014/07/31
	//::EnableWindow(  ::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_BUTTON_aDev  ),  FALSE  );

	//
	m_var.bInited  =  TRUE;

	//
	iErr  =  0;

errLabel:
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgTest_isCli::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();

	//
	if  (  m_var.bCreated  )  {

		traceLogA(  "CDlgTest_isCli::PostNcDestroy(  ): delete this"  );
		try  {
			 delete  this;		
			}
		catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTest_isCli::PostNcDestroy failed."  )  );
		}

	}

	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	qmcApplyForChkingTasks_gui(  pQyMc  );	//  2009/09/10

}


void CDlgTest_isCli::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//  CDialog::OnCancel();
	bQuitDlg(  );
}


void CDlgTest_isCli::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialog::OnClose();
	bQuitDlg(  );
}



void CDlgTest_isCli::OnBnClickedButtonadev()
{
	// TODO: Add your control notification handler code here
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp		*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	DLG_guiDataParam_objs		param;
	
	memset(  &param,  0,  sizeof(  param  )  );	
	param.uiType  =  CONST_objType_selectADev;
	param.p0  =  m_var.pCapStuff;
	param.iMenuId_selectedDev  =  m_var.iMenuId_selectedAudio;
				  		
	if  (  showDlgObjs(  pQyMc->g_hInst,  m_hWnd,  &param  )  )  goto  errLabel;
		
	CAP_STUFF  *  pCapStuff  =  (  CAP_STUFF  *  )m_var.pCapStuff;
	//
	if  (  param.o.iSel  <  0  ||  param.o.iSel  >=  mycountof(  pCapStuff->old_audioDevices.mems  )  )  goto  errLabel;

	int  iMenuId  =  pCapStuff->old_audioDevices.mems[param.o.iSel].iMenuIds_audio;

	if  (  iMenuId  !=  m_var.iMenuId_selectedAudio  )  {


		if  (  iMenuId  >=  ID_MENU_ADEVICE0  &&  iMenuId  <=  ID_MENU_ADEVICE9  )  {
			//			
			QY_REG  reg;		
							
			//
			memset(  &reg,  0,  sizeof(  reg  )  );
			
			reg.hKeyRoot0  =  HKEY_CURRENT_USER;
			lstrcpyn(  reg.rootKey,  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

			qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_ucbNot_selectDefaultRecorder  ),  _T(  "1"  )  );
			pProcInfo->cfg.policy.audio.ucbNot_selectDefaultRecorder  =  TRUE;

			//
			m_var.iMenuId_selectedAudio  =  iMenuId;
			pFuncs->pf_saveChosenDevice(  m_var.pCapStuff,  m_var.bIncludeACap,  iMenuId  );
			//  getChosenDevice(  pProcInfo->av.localAv.recorder_selected,  mycountof(  pProcInfo->av.localAv.recorder_selected  ),  NULL,  0  );
		}
		if  (  iMenuId  >=  ID_MENU_VDEVICE0  &&  iMenuId  <=  ID_MENU_VDEVICE9  )  {
			m_var.iMenuId_selectedVideo  =  iMenuId;
			pFuncs->pf_saveChosenDevice(  m_var.pCapStuff,  m_var.bIncludeACap,  iMenuId  );
			//  getChosenDevice(  NULL,  0,  pProcInfo->av.localAv.webcam_selected,  mycountof(  pProcInfo->av.localAv.webcam_selected  )  );
		}

		//
		TCHAR	tBuf[256]  =  _T(  ""  );
		pFuncs->moniker.pf_getADevFriendlyName(  m_var.pCapStuff,  m_var.bIncludeACap,  m_var.iMenuId_selectedAudio,  tBuf,  mycountof(  tBuf  )  );
		SetDlgItemText(  IDC_STATIC_aDev,  tBuf  );

	}

errLabel:
	return;
}


void CDlgTest_isCli::OnBnClickedButtonvdev()
{
	// TODO: Add your control notification handler code here
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp		*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	DLG_guiDataParam_objs		param;
	
	memset(  &param,  0,  sizeof(  param  )  );	
	param.uiType  =  CONST_objType_selectVDev;
	param.p0  =  m_var.pCapStuff;
	param.iMenuId_selectedDev  =  m_var.iMenuId_selectedVideo;
				  		
	if  (  showDlgObjs(  pQyMc->g_hInst,  m_hWnd,  &param  )  )  goto  errLabel;
	
	CAP_STUFF  *  pCapStuff  =  (  CAP_STUFF  *  )m_var.pCapStuff;
	//
	if  (  param.o.iSel  <  0  ||  param.o.iSel  >=  mycountof(  pCapStuff->rgpmVideoMenu  )  )  goto  errLabel;

	int  iMenuId  =  ID_MENU_VDEVICE0  +  param.o.iSel;

	if  (  iMenuId  !=  m_var.iMenuId_selectedVideo  )  {

		//
		pFuncs->pf_myChooseDevices(  pCapStuff,  pCapStuff->rgpmVideoMenu[param.o.iSel],  pCapStuff->pmAudio  );

		//
		if  (  iMenuId  >=  ID_MENU_ADEVICE0  &&  iMenuId  <=  ID_MENU_ADEVICE9  )  {
			m_var.iMenuId_selectedAudio  =  iMenuId;
			pFuncs->pf_saveChosenDevice(  m_var.pCapStuff,  m_var.bIncludeACap,  iMenuId  );
			//  getChosenDevice(  pProcInfo->av.localAv.recorder_selected,  mycountof(  pProcInfo->av.localAv.recorder_selected  ),  NULL,  0  );
		}
		if  (  iMenuId  >=  ID_MENU_VDEVICE0  &&  iMenuId  <=  ID_MENU_VDEVICE9  )  {
			m_var.iMenuId_selectedVideo  =  iMenuId;
			pFuncs->pf_saveChosenDevice(  m_var.pCapStuff,  m_var.bIncludeACap,  iMenuId  );
			//  getChosenDevice(  NULL,  0,  pProcInfo->av.localAv.webcam_selected,  mycountof(  pProcInfo->av.localAv.webcam_selected  )  );
		}

		//
		TCHAR  tBuf[256]  =  _T(  ""  );
		//  getMonikerFriendlyName(  getMoniker_v(  m_var.pCapStuff,  m_var.iMenuId_selectedVideo  ),  tBuf,  mycountof(  tBuf  )  );
		pFuncs->moniker.pf_getMonikerProp(  pFuncs->moniker.pf_getMoniker_v(  m_var.pCapStuff,  m_var.iMenuId_selectedVideo  ),  CONST_moniker_FriendlyName,  tBuf,  mycountof(  tBuf  )  );
		SetDlgItemText(  IDC_STATIC_vDev,  tBuf  );

	}

errLabel:
	return;
}

void CDlgTest_isCli::OnBnClickedButtoncfgcapturepinv()
{
	// TODO: Add your control notification handler code here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	pFuncs->pf_cfgCapturePin(  m_var.pCapStuff,  this->m_hWnd  );
}


void CDlgTest_isCli::OnBnClickedButtontestav()
{
	// TODO: Add your control notification handler code here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	
	QY_MC		*	pQyMc	=	QY_GET_GBUF();

	//  2014/06/04				
	if  (  pProcInfo->cfg.policy.video.uiCamCapType  ==  CONST_camCapType_rtsp  )  {	
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_notSupportRtsp  )  );
		return;
	}


	//  2013/03/19
	TCHAR	displayName[MAX_monikerDisplayNameLen  +  1]  =  _T(  ""  );
	if  (  m_var.bIncludeACap  )  {
		pFuncs->moniker.pf_getMonikerDisplayName(  pFuncs->moniker.pf_getMoniker_a(  m_var.pCapStuff,  m_var.iMenuId_selectedAudio  ),  displayName,  mycountof(  displayName  )  );
	}
	TCHAR  capDevDesc[64]  =  _T(  ""  );
	void  *  pADev  =  m_var.bIncludeACap  ?    displayName  :  pFuncs->moniker.pf_getADeviceGuid(  m_var.pCapStuff,  m_var.iMenuId_selectedAudio,  capDevDesc, mycountof(  capDevDesc  )  );
	if  (  pFuncs->pf_testLocalAv_openLocalVideo(  this->m_hWnd,  pADev,  capDevDesc,  pFuncs->moniker.pf_getMoniker_v(  m_var.pCapStuff,  m_var.iMenuId_selectedVideo  ),  &m_var.bGot_sharedObjIndex_localAv,  &m_var.iIndex_sharedObj_localAv  )  )  {
					  //  goto  errLabel;
	
	}

	//  只操作一次
	GetDlgItem(  IDC_BUTTON_testAv  )->EnableWindow(  FALSE  );
}


void CDlgTest_isCli::OnDestroy()
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	MACRO_qyAssert(  pFuncs,  _T(  "FUNCS err"  )  );
	
	//
	if  (  m_var.bGot_sharedObjIndex_localAv  )  {
		pFuncs->pf_freeSharedObjUsr_localAv(  pProcInfo,  m_var.iIndex_sharedObj_localAv,  this->m_hWnd  );				  
	}				  
	//	
	pFuncs->pf_stopLocalAudioPlaying(  pProcInfo  );


	//	
	MACRO_safeFree(  m_var.pMsgBuf_doWnd_guiMsgArrive  );		//  2009/12/10

	//
	int  idc_dst  =  m_var.idc;
	old_freeCapImages(  this->m_hWnd,  m_var.idc,  &m_var.images,  old_M_GetDlgItem(  m_hWnd,  idc_dst  ),  &m_var.hDc,  _T(  "dlgTest.OnDestroy.794"  ));
	
	//
	pFuncs->pf_CAP_STUFF_free(  m_var.pCapStuff  );		//  2009/09/16


	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}


 LRESULT  CDlgTest_isCli::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	long				lRet				=					-1;
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	//  int					iWndContentType		=					getWndContentType(  );
	MC_VAR_isCli		*	pProcInfo			=				QY_GET_procInfo_isCli(  );	//  	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	if  (  !pComm  )  return  -1;

	switch  (  pComm->uiType  )  {
			case  CONST_misMsgType_procVideo_qmc:  {
				  MIS_MSG_procVideo_qmc		*	pMsg			=	(  MIS_MSG_procVideo_qmc  *  )pComm;
				  BOOL							bUseDxSurface	=	FALSE;	//  m_var.bUseDirectX;
				
				  #ifdef  __DEBUG__
						  //  bUseDxSurface  =  FALSE;
				  #endif

				  //  2013/09/25  
				  if  (  pProcInfo->chromaKey.hWnd_dlgImg  )  {
					  if  (  ::SendMessage(  pProcInfo->chromaKey.hWnd_dlgImg,  CONST_qyWm_comm,  wParam,  lParam  )  !=  CONST_qyWmRc_ok  )  {
						  if  (  !IsWindow(  pProcInfo->chromaKey.hWnd_dlgImg  )  )  {
							  pProcInfo->chromaKey.hWnd_dlgImg  =  NULL;
						  }
					  }
				  }

				  //
#ifdef  __DEBUG__
				  if (0) {
					  BITMAPINFOHEADER bih = pMsg->bih;
					  if (bih.biCompression == 0) {
						  //mySaveBitmap(&bih, pMsg->pkt.memory.m_pBuf, false, _T("d:\\tttbbb\\1.bmp"));
					  }
				  }
#endif 
					
				  //  2011/11/27. 在全高清视频时，在笔记本上显示不了了，不能使用dx.					
				  bUseDxSurface  =  FALSE;
				  
				  //
				  ZONE_PARAM  *  pZoneParam  =  &m_var.zoneParam;
				  //  if  (  drawCapImages(  this->m_hWnd,  m_var.idc,  &m_var.hDc,  NULL,  FALSE,  m_var.ucbAutoClip,  pMsg,  0,  0,  m_var.iW_pic,  m_var.iH_pic,  NULL,  pZoneParam,  &m_var.images,  bUseDxSurface,  FALSE  )  )  goto  errLabel;
				  HWND  hWnd_src  =  old_M_GetDlgItem(  m_hWnd,  m_var.idc  );
				  HWND  hWnd_dst  =  hWnd_src;
				  if  (  drawCapImages(  pProcInfo->pQyMc,  hWnd_src,  m_var.ucbAutoClip,  pMsg,  0,  0,  m_var.iW_pic,  m_var.iH_pic,  NULL,  pZoneParam,  &m_var.images,  hWnd_dst,  &m_var.hDc,  NULL  )  )  goto  errLabel;

				  }
												   
				  break;
			default:
					break;
	}

		lRet  =  QY_RC_WMOK;

errLabel:

	return  lRet;
 }


  LRESULT  CDlgTest_isCli::OnQyPostComm( WPARAM wParam, LPARAM lParam )
{
	long				lRet			=		-1;
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );

	switch  (  wParam  )  {
			case  CONST_qyWmParam_guiMsgArrive:  
				  doWnd_guiMsgArrive(  pProcInfo,  lParam,  this->m_hWnd,  TRUE,  m_var.pMsgBuf_doWnd_guiMsgArrive  );
				  break;
			default:
					break;
	}
	
	lRet  =  QY_RC_WMOK;
	
errLabel:

	return  lRet;

  }

  void CDlgTest_isCli::OnSize(UINT nType, int cx, int cy)
  {
	  CDialog::OnSize(nType, cx, cy);

	  // TODO: Add your message handler code here
	sizeAllControls(  );
  }

 
  void CDlgTest_isCli::OnIsCmd(  UINT iMenuId  )
{
	int					iErr		=	-1;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	
	//  2013/02/06
	//if  (  iMenuId  >=  ID_dlgTest_min  &&  iMenuId  <=  ID_dlgTest_max  )  
	{
		pFuncs->pf_doCmd_test(  iMenuId  );
		iErr  =  0;  goto  errLabel;
	}

	iErr  =  0;
	errLabel:
	return;
  }


  void CDlgTest_isCli::OnUpdateIsCmd(CCmdUI *pCmdUI)
{
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );

	if  (  !pProcInfo  )  return;
	BOOL				bState		=	TRUE;

	//  traceLogA(  "OnUpdateIsCmd: %d",  pCmdUI->m_nID  );
	switch  (  pCmdUI->m_nID  )  {
				  //
#if  0
			case  ID_notViewAudioStatus:
 				  if  (  !pQyMc->env.bDebugInfo  ||  !pProcInfo->cfg.debugStatusInfo.ucbViewAudioStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_viewAudioStatus:
				  if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewAudioStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notViewVideoStatus:
				  if  (  !pQyMc->env.bDebugInfo  ||  !pProcInfo->cfg.debugStatusInfo.ucbViewVideoStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_viewVideoStatus:
				  if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewVideoStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notViewIoStatus:
				  if  (  !pQyMc->env.bDebugInfo  ||  !pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_viewIoStatus:
  				  if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
#endif
			case  ID_notPrintAudioMediaType:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbPrint_a_mt  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_printAudioMediaType:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_a_mt  )  pCmdUI->Enable(  FALSE  );
				  break;

#if  0
			case  ID_notShowVideoCapStatus:				//  2012/11/11
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowVideoCapStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showVideoCapStatus:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowVideoCapStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowAudioCapStatus:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowAudioCapStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showAudioCapStatus:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowAudioCapStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowPreDrawStatus:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowPreDrawStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showPreDrawStatus:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPreDrawStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowToDrawStatus:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowToDrawStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showToDrawStatus:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowToDrawStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowRenderStatus:  //  2015/10/07
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowRenderStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showRenderStatus:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowRenderStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowPlayAudioStatus:				//  2012/11/11
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowPlayAudioStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showPlayAudioStatus:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPlayAudioStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowDlgTalkStatus:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  )  pCmdUI->Enable(  FALSE  );				  
				  break;
			case  ID_showDlgTalkStatus:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowPktInputInfo:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowPktInputInfo  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showPktInputInfo:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPktInputInfo  )  pCmdUI->Enable(  FALSE  );
				  break;				  
			case  ID_notPrintRtt:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbPrint_rtt  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_printRtt:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_rtt  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowOnvifStatus:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShow_onvif  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showOnvifStatus:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShow_onvif  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notPrintPtz:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbPrint_ptz  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_printPtz:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_ptz  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notPrintD3d:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbPrint_d3d  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_printD3d:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_d3d  )  pCmdUI->Enable(  FALSE  );
				  break;
				  
			case  ID_notShowEncVStatus:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowEncVStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showEncVStatus:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowEncVStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
				  //
				  //  2016/04/08
			case  ID_notShowDec_pipeStatus:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowDec_pipeStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showDec_pipeStatus:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowDec_pipeStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
				  //
			case  ID_notShowPreDecAStatus:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowPreDecAStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showPreDecAStatus:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPreDecAStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowPreDecV_pts:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowPreDecV_pts  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showPreDecV_pts:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPreDecV_pts  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowPreDecVStatus:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowPreDecVStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showPreDecVStatus:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPreDecVStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowPostDecVStatus:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowPostDecVStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showPostDecVStatus:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPostDecVStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
				  //  2016/04/08
			case  ID_notShowDec_sharedTexStatus:
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowDec_sharedTexStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showDec_sharedTexStatus:
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowDec_sharedTexStatus  )  pCmdUI->Enable(  FALSE  );
				  break;

				  //
			case  ID_notTestGps:
				  if  (  !pProcInfo->cfg.ucbTestGps  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_testGps:
				  if  (  pProcInfo->cfg.ucbTestGps  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notTestStream:{
				  if  (  !pProcInfo->cfg.debugStatusInfo.ucbShowRtspCliControl  )  pCmdUI->Enable(  FALSE  );
				  }
 				  break;
			case  ID_testStream:{
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowRtspCliControl  )  pCmdUI->Enable(  FALSE  );
				  }
 				  break;
#endif

			default:
					break;
	}	

errLabel:

	return;
}


void CDlgTest_isCli::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	// TODO: Add your message handler code here
	ASSERT(pPopupMenu != NULL);
	
	// check the enabled state of various menu items

	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// determine if menu is popup in top-level menu and set m_pOther to
	//  it if so (m_pParentMenu == NULL indicates that it is secondary popup)
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;    // parent == child for tracking popup
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = GetTopLevelParent();
			// child windows don't have menus -- need to go to the top!
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					// when popup is found, m_pParentMenu is containing menu
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	  state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // menu separator or invalid cmd - ignore it

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// possibly a popup menu, route to first item of that popup
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // first item of popup can't be routed to
			}
			state.DoUpdate(this, FALSE);    // popups are never auto disabled
		}
		else
		{
			// normal menu item
			// Auto enable/disable if frame window has 'm_bAutoMenuEnable'
			//    set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			//  state.DoUpdate(this, m_bAutoMenuEnable && state.m_nID < 0xF000);	//  2007/10/04
			state.DoUpdate(  this,  state.m_nID  <  0xF000  );
		}

		// adjust for menu deletions and additions
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}

}