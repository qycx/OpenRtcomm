// DlgChromaKeyCfg.cpp : implementation file
//

#include "stdafx.h"

#include	<stdlib.h>
#include	<math.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"
#include	"qmcVWall.h"
#include	"WallTalkers.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"

#include	"qyCusResTemp.h"

#include	"qyAvRecordPublic.h"

#include	"sp.h"
#include "isCliHelp.h"
#include "DlgImg.h"
#include "afxdialogex.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"qycusResTemp.h"

#include	"myDb.h"

#include	"qyMcMainCommon.h"
#include "isCliHelp.h"
#include "DlgChromaKeyCfg.h"
#include "afxdialogex.h"

#include	"isCliHelpPublic.h"
#include	"DlgImg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

	
 __declspec(  dllexport  )  int  viewChromaKeyCfg(  HWND  hParent,  HWND  hWnd_img,  int  iWndContentType_img,  int  idc_img  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr	=	-1;

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	
	CDlgChromaKeyCfg			*		pDlg					=	NULL;
	RECT							rect;

	if  (  iWndContentType_img  !=  CONST_qyWndContentType_dlgImg  )  return  -1;
	
	CDlgImg  *  pDlgImg  =  (  CDlgImg  *  )CWnd::FromHandle(  hParent  );
	if  (  !pDlgImg  )  goto  errLabel;

	//
	if  (  IsWindow(  pDlgImg->m_var.hTool  )  )  {
		MACRO_SetForegroundWindow(  pDlgImg->m_var.hTool  );
		iErr  =  0;  goto  errLabel;
	}

	pDlgImg->m_var.hTool  =  NULL;

	//
	pDlg  =  new  CDlgChromaKeyCfg(  pDlgImg  );
	if  (  !pDlg  )  goto  errLabel;

	//  2013/02/06
	if  (  !pDlg->bSetDlgInfo(  CONST_qyWndContentType_dlgChromaKeyCfg,  0,  _T(  "Chroma Key"  )  )  )  goto  errLabel;
	pDlg->m_var.hWnd_img  =  hWnd_img;
	pDlg->m_var.idc_img  =  idc_img;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	pDlg->ShowWindow(  SW_SHOW  );

	//  
	pDlgImg->m_var.hTool  =  pDlg->m_hWnd;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
	}

	//  traceLogA(  "viewMediaControl leaves, iErr is %d",  iErr  );

	return  iErr;
}

 int chromaKeyRefreshImgProcessCfg(  HWND  hDlg,  unsigned short usKeyIndex,  IMG_key  *  pKey,  IMG_process_cfg  *  pCfg  )
 { 
	int  iRet  =  -1;
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;

	BYTE	x, y, z;

	convert_rgb_to_key_pixel(  toByte_rgb(  pKey->rgb_key.r  ),  toByte_rgb(  pKey->rgb_key.g  ),  toByte_rgb(  pKey->rgb_key.b  ), &x,  &y,  &z  ); 
	pKey->hsl_key.x  =  toFloat_hsl(  x  );
	pKey->hsl_key.y  =  toFloat_hsl(  y  );
	pKey->hsl_key.z  =  toFloat_hsl(  z  );
	//
	SetDlgItemInt(  hDlg,  IDC_STATIC_key_h,  x,  TRUE  );
	SetDlgItemInt(  hDlg,  IDC_STATIC_key_s,  y,  TRUE  );
	SetDlgItemInt(  hDlg,  IDC_STATIC_key_l,  z,  TRUE  );
	
	if  (  memcmp(  pKey,  &pCfg->keys[usKeyIndex],  sizeof(  pKey  )  )  ){
		memcpy(  &pCfg->keys[usKeyIndex],  &pKey,  sizeof(  pCfg->keys[usKeyIndex]  )  );
		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &pCfg  );
	}

	iRet  =  0;
errLabel:

	 return  iRet;
 }

  int  refreshListBox(  HWND  hDlg,  int  iIdc,  IMG_process_cfg  *  pCfg,  unsigned short  usKeyIndex  )
{
	int  iErr  =  -1;

	TCHAR		tBuf[1024];
	int i,r,g,b;
	int l,  h,  s;	//  y,cb,cr;
	//  float  tola,tolb;
	int tola, tolb;
	HWND		hCtrl		=  ::GetDlgItem( hDlg,  iIdc  );
	::SendMessage(  hCtrl,  LB_RESETCONTENT,  (  WPARAM  )NULL,  (  LPARAM  )NULL  );    
		
	for (  i  =  0; i < pCfg->usCnt;  i ++  ) {
		r =  toByte_rgb(  pCfg->keys[i].rgb_key.r  );
		g =  toByte_rgb(  pCfg->keys[i].rgb_key.g  );
		b =  toByte_rgb(  pCfg->keys[i].rgb_key.b  );
#ifdef  __USE_hsl_chromaKey__
		l =  toByte_hsl(  pCfg->keys[i].hsl_key.z  );
		h =  toByte_hsl(  pCfg->keys[i].hsl_key.x  );
		s =  toByte_hsl(  pCfg->keys[i].hsl_key.y  );
#else
		l = 0;//pCfg->keys[i].cfg.ucY_key;
		h = 0;//pCfg->keys[i].cfg.ucCb_key;
		s = 0;// pCfg->keys[i].cfg.ucCr_key;
#endif
		//  tola  =  pCfg->keys[i].cfg.tola100x  /  100.;
		//  tolb  =  pCfg->keys[i].cfg.tolb100x  /  100.;
		tola  =  pCfg->keys[i].tola;
		tolb  =  pCfg->keys[i].tolb;

		//  int len  =  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d.  RGB:(%d,%d,%d),HSL:(%d,%d,%d),S:%.2f,D:%.2f"),  (i+1),r,g,b,h,s,l,tola,(tolb-tola)  );
		int len  =  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d.  RGB:(%d,%d,%d),HSL:(%d,%d,%d),A:%d,B:%d"),  (i+1),r,g,b,h,s,l,tola,tolb  );

		::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    

		if  (  i  ==  usKeyIndex  )  {
			::SendMessage(  hCtrl,  LB_SETCURSEL,  ( WPARAM)i, 0  );
		}
	}

	 iErr  =  0;
errLabel:
	 return  iErr;
 }

 int  OnPaint_idcColor(  CDlgChromaKeyCfg  *  pParent,  CWnd  *  pCtrl,  CDC  *  pDc_idc  )
{
	//  COLORREF  rgb  =  RGB(  0,  255,  0  );	

#ifdef  __DEBUG__
	traceLog(  _T(  "OnPaint_idcColor: called"  )  );
#endif

	COLORREF  rgb  =  0;
	
	CQyStatic  *  pStatic  =  (  CQyStatic  *  )pCtrl;
	switch  (  pStatic->m_var.idc  )  {
			case  IDC_STATIC_color:
				  rgb  =  RGB(  toByte_rgb(  pParent->m_var.curKey.rgb_key.r  ),  toByte_rgb(  pParent->m_var.curKey.rgb_key.g  ),  toByte_rgb(  pParent->m_var.curKey.rgb_key.b  )  );
				  break;
			case  IDC_STATIC_color_org:
				  rgb  =  pParent->m_var.color_org;
				  break;
			case  IDC_STATIC_color_keyed:
				  rgb  =  pParent->m_var.color_keyed;
				  break;
			default:
					break;
	}

	//
	RECT	rc;
	GetClientRect(  pCtrl->m_hWnd,  &rc  );
	brushDc(  rgb,  pDc_idc->m_hDC,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top  );

	return  0;
}


// CDlgChromaKeyCfg dialog

IMPLEMENT_DYNAMIC(CDlgChromaKeyCfg, CDialogEx)

CDlgChromaKeyCfg::CDlgChromaKeyCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgChromaKeyCfg::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.m_pParent  =  pParent;
	m_var.m_nID  =  this->IDD;

}

CDlgChromaKeyCfg::~CDlgChromaKeyCfg()
{
	//
	::PostMessage(  m_var.hWnd_img,  WM_CLOSE,  0,  0  );
}




BOOL  CDlgChromaKeyCfg::bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title  )
{
	BOOL	bRet	=	FALSE;


	m_var.iWndContentType  =  iWndContentType;
	m_var.iWndContentSubType  =  iSubType;
	safeTcsnCpy(  title,  m_var.title,  mycountof(  m_var.title  )  );


	bRet  =  TRUE;

	return  bRet;
}
	
 BOOL  CDlgChromaKeyCfg::bShowPolicy(  )
{
	BOOL					bRet	=	FALSE;

#if  1  //  2014/04/08
	#ifdef  __DEBUG__
			traceLog(  _T(  "For test"  )  );
	#endif
	return  FALSE;
#endif

	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if (  !pFuncs  )  goto  errLabel;
	
	if  (  pFuncs->imgProcess.pf_getCurImgProcessCfg(  &m_var.cfg,  NULL  )  )  goto  errLabel;

	//
	m_var.usKeyIndex  =  0;
	memcpy(  &m_var.curKey,  &m_var.cfg.keys[m_var.usKeyIndex],  sizeof(  m_var.curKey  )  );

	int  idc  =  IDC_CHECK_useChromaKey;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.cfg.bUseChromaKey  ?  1 : 0  );

	//SetDlgItemText(  IDC_STATIC_hint_chromaKey,  _T(  "提示：应先启动\"测试本地音视频\"的视频,然后调节本窗口key值方可观看实时生效的抠像效果。 "  )  );

	refreshListBox(  m_hWnd,  IDC_LIST_chromaKey,  &m_var.cfg,  m_var.usKeyIndex  );

	TCHAR  tBuf[1024]  =  _T(  ""  );
	SetDlgItemInt(  IDC_EDIT_key_r,  toByte_rgb(  m_var.curKey.rgb_key.r  )  );
	SetDlgItemInt(  IDC_EDIT_key_g,  toByte_rgb(  m_var.curKey.rgb_key.g  )  );
	SetDlgItemInt(  IDC_EDIT_key_b,  toByte_rgb(  m_var.curKey.rgb_key.b  )  );
#ifdef  __USE_hsl_chromaKey__
	SetDlgItemInt(  IDC_STATIC_key_h,  toByte_hsl(  m_var.curKey.hsl_key.x  )  );
	SetDlgItemInt(  IDC_STATIC_key_s,  toByte_hsl(  m_var.curKey.hsl_key.y  )  );
	SetDlgItemInt(  IDC_STATIC_key_l,  toByte_hsl(  m_var.curKey.hsl_key.z  )  );
#else
#if  0
	SetDlgItemInt(  IDC_STATIC_key_y,  m_var.curKey.ucY_key  );
	SetDlgItemInt(  IDC_STATIC_key_cb,  m_var.curKey.ucCb_key  );
	SetDlgItemInt(  IDC_STATIC_key_cr,  m_var.curKey.ucCr_key  );
#endif

#endif
	//
#if 0
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  m_var.curKey.tola100x  /  100.  );
	SetDlgItemText(  IDC_EDIT_key_tola,  tBuf  );
	float  fDistance  =  (  m_var.curKey.tolb100x  -  m_var.curKey.tola100x  )  /  100.;
	if  (  fDistance  <=  0  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "dlgChromaKeyCfg: bShowPolicy failed, fDistance <=  0"  )  );
		#endif
		goto errLabel;
	}
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  fDistance  );
	SetDlgItemText(  IDC_EDIT_key_distance,  tBuf  );
#else
	m_slider_key_tola.SetPos( m_var.curKey.tola);
	SetDlgItemInt(  IDC_STATIC_key_tola_val,  m_var.curKey.tola );
	m_slider_key_tolb.SetPos( m_var.curKey.tolb);
	SetDlgItemInt(  IDC_STATIC_key_tolb_val,  m_var.curKey.tolb );
#endif
	//
	SetDlgItemInt(  IDC_EDIT_minRgb,  m_var.cfg.minVal_r_g_b  );
	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  (  int  )m_var.cfg.usMin_saturation  );
	SetDlgItemText(  IDC_EDIT_minS,  tBuf  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  (  int  )m_var.cfg.usMin_lightness  );
	SetDlgItemText(  IDC_EDIT_minL,  tBuf  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  (  int  )m_var.cfg.usMax_lightness  );
	SetDlgItemText(  IDC_EDIT_maxL,  tBuf  );

#if 0
	//
	idc  =  IDC_CHECK_smooth;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.cfg.bStartSmooth  ?  1 : 0  );

	idc  =  IDC_CHECK_edgeColor;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.cfg.bEdgeColor  ?  1 : 0  );

	SetDlgItemInt(  IDC_EDIT_edge_distance,  m_var.cfg.ucMax_edge_d  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  m_var.cfg.f_reversoColor10x  /  10.  );
	SetDlgItemText(  IDC_EDIT_f_r,  tBuf  );
#endif



	//
	if  (  m_var.cfg.bUseChromaKey  )  {
		idc  =  IDC_CHECK_keyingAFrame;
		m_var.bKeyingAFrame  =  FALSE;
		(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.bKeyingAFrame  ?  1 : 0  );
		GetDlgItem(  idc  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_x  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_y  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_CHECK_pick  )->ShowWindow(  SW_HIDE  );
	}
	else  {
		if  (  m_var.bKeyingAFrame  )  {
			GetDlgItem(  IDC_EDIT_x  )->EnableWindow(  TRUE  );
			GetDlgItem(  IDC_EDIT_y  )->EnableWindow(  TRUE  );
		}
		else  {
			GetDlgItem(  IDC_EDIT_x  )->EnableWindow(  FALSE  );
			GetDlgItem(  IDC_EDIT_y  )->EnableWindow(  FALSE  );
		}
	}
#if 0
	if  (  m_var.cfg.bEdgeColor  )  {
		GetDlgItem(  IDC_EDIT_edge_distance  )->EnableWindow(  TRUE  );
		GetDlgItem(  IDC_EDIT_f_r  )->EnableWindow(  TRUE  );
	}
	else  {
		GetDlgItem(  IDC_EDIT_edge_distance  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_f_r  )->EnableWindow(  FALSE  );
	}
#endif
	//
	//  if ( m_var.cfg.fSigma_preBlur  )  
		m_slider_preBlur.SetPos( (int )m_var.cfg.fSigma_preBlur  *  20 );
	//  if ( m_var.cfg.fSigma_postBlur  )  
		m_slider_postBlur.SetPos( (int )m_var.cfg.fSigma_postBlur  *  20 );
		//
		m_slider_gamma.SetPos( (int )m_var.cfg.fGamma * 20 );

	//
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_HIDE  );
	//
	GetDlgItem(  IDC_EDIT_key_tola  )->ShowWindow( SW_HIDE );
	GetDlgItem(  IDC_EDIT_key_distance  )->ShowWindow( SW_HIDE );


	bRet  =  TRUE;
errLabel:
	return  bRet;
}	
//
BOOL CDlgChromaKeyCfg::Create(const RECT& rect)
{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	//MC_VAR_isMgr			*	pProc		=	NULL;

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): 在创建对话框之前应先设置初始数据"  );
		return  FALSE;
	}
	*/

	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	if  (  !m_var.iWndContentType  )  return  FALSE;
	

	//
	if  (  !CDialog::Create(  this->m_var.m_nID, m_var.m_pParent  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}



 BOOL  CDlgChromaKeyCfg::bQuitDlg(  )		
{		
	traceLogA(  "CDlgStatusCli(  )::bQuitDlg enters"  );


	//  2009/05/01
	DestroyWindow();				  
		
//  errLabel:

	traceLogA(  "CDlgStatusCli(  )::bQuitDlg leaves"  );

	return  TRUE;
}


 int  CDlgChromaKeyCfg::sizeAllControls(  )
{
errLabel:
	return  0;
}




void CDlgChromaKeyCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_preBlur, m_slider_preBlur);
	DDX_Control(pDX, IDC_SLIDER_postBlur, m_slider_postBlur);
	DDX_Control(pDX, IDC_SLIDER_key_tola, m_slider_key_tola);
	DDX_Control(pDX, IDC_SLIDER_key_tolb, m_slider_key_tolb);
	DDX_Control(pDX, IDC_SLIDER_gamma, m_slider_gamma);
}


BEGIN_MESSAGE_MAP(CDlgChromaKeyCfg, CDialogEx)
	ON_WM_CLOSE()
	ON_LBN_SELCHANGE(IDC_LIST_chromaKey, &CDlgChromaKeyCfg::OnLbnSelchangeListchromakey)
	ON_EN_SETFOCUS(IDC_EDIT_key_r, &CDlgChromaKeyCfg::OnEnSetfocusEditkeyr)
	ON_EN_SETFOCUS(IDC_EDIT_key_g, &CDlgChromaKeyCfg::OnEnSetfocusEditkeyg)
	ON_EN_SETFOCUS(IDC_EDIT_key_b, &CDlgChromaKeyCfg::OnEnSetfocusEditkeyb)
	ON_EN_SETFOCUS(IDC_EDIT_key_tola, &CDlgChromaKeyCfg::OnEnSetfocusEditkeytola)
	ON_EN_SETFOCUS(IDC_EDIT_key_distance, &CDlgChromaKeyCfg::OnEnSetfocusEditkeydistance)
	ON_EN_SETFOCUS(IDC_EDIT_minS, &CDlgChromaKeyCfg::OnEnSetfocusEditmins)
	ON_EN_SETFOCUS(IDC_EDIT_minL, &CDlgChromaKeyCfg::OnEnSetfocusEditminl)
	ON_EN_SETFOCUS(IDC_EDIT_maxL, &CDlgChromaKeyCfg::OnEnSetfocusEditmaxl)
	ON_EN_SETFOCUS(IDC_EDIT_f_r, &CDlgChromaKeyCfg::OnEnSetfocusEditfr)
	ON_EN_SETFOCUS(IDC_EDIT_edge_distance, &CDlgChromaKeyCfg::OnEnSetfocusEditedgedistance)
	ON_EN_CHANGE(IDC_EDIT_key_r, &CDlgChromaKeyCfg::OnEnChangeEditkeyr)
	ON_EN_CHANGE(IDC_EDIT_key_g, &CDlgChromaKeyCfg::OnEnChangeEditkeyg)
	ON_EN_CHANGE(IDC_EDIT_key_b, &CDlgChromaKeyCfg::OnEnChangeEditkeyb)
	ON_EN_CHANGE(IDC_EDIT_key_tola, &CDlgChromaKeyCfg::OnEnChangeEditkeytola)
	ON_EN_CHANGE(IDC_EDIT_key_distance, &CDlgChromaKeyCfg::OnEnChangeEditkeydistance)
	ON_EN_CHANGE(IDC_EDIT_minS, &CDlgChromaKeyCfg::OnEnChangeEditmins)
	ON_EN_CHANGE(IDC_EDIT_minL, &CDlgChromaKeyCfg::OnEnChangeEditminl)
	ON_EN_CHANGE(IDC_EDIT_maxL, &CDlgChromaKeyCfg::OnEnChangeEditmaxl)
#if 0
	ON_EN_CHANGE(IDC_EDIT_f_r, &CDlgChromaKeyCfg::OnEnChangeEditfr)
	ON_EN_CHANGE(IDC_EDIT_edge_distance, &CDlgChromaKeyCfg::OnEnChangeEditedgedistance)
#endif
	ON_EN_CHANGE(IDC_EDIT_x, &CDlgChromaKeyCfg::OnEnChangeEditx)
	ON_EN_CHANGE(IDC_EDIT_y, &CDlgChromaKeyCfg::OnEnChangeEdity)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_plusInt, &CDlgChromaKeyCfg::OnDeltaposSpinplusint)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_plusFloat, &CDlgChromaKeyCfg::OnDeltaposSpinplusfloat)
	ON_BN_CLICKED(IDC_CHECK_useChromaKey, &CDlgChromaKeyCfg::OnBnClickedCheckusechromakey)
	ON_BN_CLICKED(IDC_CHECK_keyingAFrame, &CDlgChromaKeyCfg::OnBnClickedCheckkeyingaframe)
	ON_BN_CLICKED(IDC_CHECK_pick, &CDlgChromaKeyCfg::OnBnClickedCheckpick)
#if 0
	ON_BN_CLICKED(IDC_CHECK_smooth, &CDlgChromaKeyCfg::OnBnClickedChecksmooth)
	ON_BN_CLICKED(IDC_CHECK_edgeColor, &CDlgChromaKeyCfg::OnBnClickedCheckedgecolor)
#endif
	ON_BN_CLICKED(IDC_ADD, &CDlgChromaKeyCfg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DEL, &CDlgChromaKeyCfg::OnBnClickedDel)
	ON_BN_CLICKED(IDC_BUTTON_save, &CDlgChromaKeyCfg::OnBnClickedButtonsave)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT_minRgb, &CDlgChromaKeyCfg::OnEnChangeEditminrgb)
	ON_BN_CLICKED(IDC_BUTTON_restoreDefaultSettings, &CDlgChromaKeyCfg::OnBnClickedButtonrestoredefaultsettings)
	ON_EN_SETFOCUS(IDC_EDIT_minRgb, &CDlgChromaKeyCfg::OnEnSetfocusEditminrgb)
	ON_EN_SETFOCUS(IDC_EDIT_x, &CDlgChromaKeyCfg::OnEnSetfocusEditx)
	ON_EN_SETFOCUS(IDC_EDIT_y, &CDlgChromaKeyCfg::OnEnSetfocusEdity)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_preBlur, &CDlgChromaKeyCfg::OnNMCustomdrawSliderpreblur)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_postBlur, &CDlgChromaKeyCfg::OnNMCustomdrawSliderpostblur)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_key_tola, &CDlgChromaKeyCfg::OnNMCustomdrawSliderkeytola)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_key_tolb, &CDlgChromaKeyCfg::OnNMCustomdrawSliderkeytolb)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_gamma, &CDlgChromaKeyCfg::OnNMCustomdrawSlidergamma)
END_MESSAGE_MAP()


// CDlgChromaKeyCfg message handlers


void CDlgChromaKeyCfg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialogEx::OnClose();
	bQuitDlg(  );
}


void CDlgChromaKeyCfg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//  CDialogEx::OnCancel();
	bQuitDlg(  );
}


void CDlgChromaKeyCfg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PostNcDestroy();

	delete  this;
}


BOOL CDlgChromaKeyCfg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	int  iErr  =  -1;
	int	 idc;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );


#if  10
	//
	CQyStatic  *  pQyStatic  =  &this->m_static_color;
	idc			=	IDC_STATIC_color;
	m_var.idcColor  =  idc;
	pQyStatic->SubclassDlgItem(  idc,  this  );
	pQyStatic->m_var.idc  =  idc;
	pQyStatic->m_var.pf_OnPaint  =  (  PF_commonHandler  )OnPaint_idcColor;
	//		
	pQyStatic  =  &this->m_static_color_org;
	idc			=	IDC_STATIC_color_org;
	m_var.idcColor_org  =  idc;
	pQyStatic->SubclassDlgItem(  idc,  this  );
	pQyStatic->m_var.idc  =  idc;
	pQyStatic->m_var.pf_OnPaint  =  (  PF_commonHandler  )OnPaint_idcColor;
	//
	pQyStatic  =  &this->m_static_color_keyed;
	idc			=	IDC_STATIC_color_keyed;
	m_var.idcColor_keyed  =  idc;
	pQyStatic->SubclassDlgItem(  idc,  this  );
	pQyStatic->m_var.idc  =  idc;
	pQyStatic->m_var.pf_OnPaint  =  (  PF_commonHandler  )OnPaint_idcColor;

	//
	CSpinButtonCtrl  *  pSpin  =  NULL;
	pSpin  =  (  CSpinButtonCtrl  *  )GetDlgItem(  IDC_SPIN_plusInt  );
	if  (  !pSpin  )  goto  errLabel;
	pSpin->SetRange32(  0,  255  );
	
	pSpin  =  NULL;
	pSpin  =  (  CSpinButtonCtrl  *  )GetDlgItem(  IDC_SPIN_plusFloat  );
	if  (  !pSpin  )  goto  errLabel;
	pSpin->SetRange32(  0,  1  );

	CWinApp  *  pApp	=	AfxGetApp(  );
	CButton  *  pBtn;
	idc		=	IDC_CHECK_pick;
	
	pBtn  = ( CButton  *  )GetDlgItem( idc );
	if  (  pBtn->GetBitmap()  ==  NULL  ) {
		m_var.hBmp_btns[0]  =  ::LoadBitmap(  pApp->m_hInstance, MAKEINTRESOURCE(  (  int  )IDB_select  )  );
		pBtn->SetBitmap(  m_var.hBmp_btns[0]  );
	}

	//
	m_slider_preBlur.SetRange( 0, 200);
	m_slider_postBlur.SetRange( 0, 200);
	//
	m_slider_gamma.SetRange( 0, 200 );
	//
	m_slider_key_tolb.SetRange( 1, 101 );
#endif

	//
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//
	if  (  !bShowPolicy(  )  )  goto  errLabel;


	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgChromaKeyCfg::OnLbnSelchangeListchromakey()
{
	// TODO: Add your control notification handler code here
	TCHAR		tBuf[1024]		=  _T("");
	int			iItemSelected;
	HWND		hCtrl			=  ::GetDlgItem( m_hWnd,  IDC_LIST_chromaKey  );
	
	iItemSelected  =  ::SendMessage(  hCtrl,  LB_GETCURSEL,  0,  0  );
	if  (  iItemSelected  ==  LB_ERR  )  goto  errLabel;

	m_var.usKeyIndex  =  iItemSelected;

	memcpy(  &m_var.curKey,  &m_var.cfg.keys[m_var.usKeyIndex],  sizeof(  m_var.curKey  )  );

	SetDlgItemInt(  IDC_EDIT_key_r,  toByte_rgb(  m_var.curKey.rgb_key.r  )  );
	SetDlgItemInt(  IDC_EDIT_key_g,  toByte_rgb(  m_var.curKey.rgb_key.g  )  );
	SetDlgItemInt(  IDC_EDIT_key_b,  toByte_rgb(  m_var.curKey.rgb_key.b  )  );
#ifdef  __USE_hsl_chromaKey__
	SetDlgItemInt(  IDC_STATIC_key_h,  toByte_hsl(  m_var.curKey.hsl_key.x  )  );
	SetDlgItemInt(  IDC_STATIC_key_s,  toByte_hsl(  m_var.curKey.hsl_key.y  )  );
	SetDlgItemInt(  IDC_STATIC_key_l,  toByte_hsl(  m_var.curKey.hsl_key.z  )  );
#else
#if  0
	SetDlgItemInt(  IDC_STATIC_key_y,  m_var.curKey.ucY_key  );
	SetDlgItemInt(  IDC_STATIC_key_cb,  m_var.curKey.ucCb_key  );
	SetDlgItemInt(  IDC_STATIC_key_cr,  m_var.curKey.ucCr_key  );
#endif

#endif

#if  0
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  m_var.curKey.tola100x  /  100.  );
	SetDlgItemText(  IDC_EDIT_key_tola,  tBuf  );
	float  fDistance  =  (  m_var.curKey.tolb100x  -  m_var.curKey.tola100x  )  /  100.;
	if  (  fDistance <= 0  )  fDistance =  1.0;
	if  (  fDistance > 199.0  )  fDistance  =  199.0;
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  fDistance  );
	SetDlgItemText(  IDC_EDIT_key_distance,  tBuf  );
#else
	m_slider_key_tola.SetPos(  m_var.curKey.tola  );
	SetDlgItemInt(  IDC_STATIC_key_tola_val,  m_var.curKey.tola  );
	m_slider_key_tolb.SetPos(  m_var.curKey.tolb  );
	SetDlgItemInt(  IDC_STATIC_key_tolb_val,  m_var.curKey.tolb  );
#endif

#if  10
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  (  int  )m_var.cfg.usMin_saturation  );
	SetDlgItemText(  IDC_EDIT_minS,  tBuf  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  (  int  )m_var.cfg.usMin_lightness  );
	SetDlgItemText(  IDC_EDIT_minL,  tBuf  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  (  int  )m_var.cfg.usMax_lightness  );
	SetDlgItemText(  IDC_EDIT_maxL,  tBuf  );
#endif
	GetDlgItem(  IDC_DEL  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_HIDE  );

	m_static_color.Invalidate(  TRUE  );

errLabel:

	return;
}

void CDlgChromaKeyCfg::OnEnSetfocusEditkeyr()
{
	// TODO: Add your control notification handler code here
	m_var.iCurIdc  =  IDC_EDIT_key_r;
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_HIDE  );
}
void CDlgChromaKeyCfg::OnEnSetfocusEditkeyg()
{
	// TODO: Add your control notification handler code here
	m_var.iCurIdc  =  IDC_EDIT_key_g;
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_HIDE  );
}
void CDlgChromaKeyCfg::OnEnSetfocusEditkeyb()
{
	// TODO: Add your control notification handler code here
	m_var.iCurIdc  =  IDC_EDIT_key_b;
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_HIDE  );
}
void CDlgChromaKeyCfg::OnEnSetfocusEditkeytola()
{
	// TODO: Add your control notification handler code here
	m_var.iCurIdc  =  IDC_EDIT_key_tola;
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_SHOW  );
}


void CDlgChromaKeyCfg::OnEnSetfocusEditkeydistance()
{
	// TODO: Add your control notification handler code here
	m_var.iCurIdc  =  IDC_EDIT_key_distance;
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_SHOW  );
}

void CDlgChromaKeyCfg::OnEnSetfocusEditminrgb()
{
	// TODO: Add your control notification handler code here
	m_var.iCurIdc  =  IDC_EDIT_minRgb;
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_HIDE  );
}

void CDlgChromaKeyCfg::OnEnSetfocusEditmins()
{
	// TODO: Add your control notification handler code here
	m_var.iCurIdc  =  IDC_EDIT_minS;
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_HIDE  );
}

void CDlgChromaKeyCfg::OnEnSetfocusEditminl()
{
	// TODO: Add your control notification handler code here
	m_var.iCurIdc  =  IDC_EDIT_minL;
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_HIDE  );
}


void CDlgChromaKeyCfg::OnEnSetfocusEditmaxl()
{
	// TODO: Add your control notification handler code here
	m_var.iCurIdc  =  IDC_EDIT_maxL;
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_HIDE  );
}

void CDlgChromaKeyCfg::OnEnSetfocusEditfr()
{
	// TODO: Add your control notification handler code here
	m_var.iCurIdc  =  IDC_EDIT_f_r;
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_SHOW  );
}

void CDlgChromaKeyCfg::OnEnSetfocusEditedgedistance()
{
	// TODO: Add your control notification handler code here
	m_var.iCurIdc  =  IDC_EDIT_edge_distance;
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_HIDE  );
}

void CDlgChromaKeyCfg::OnEnSetfocusEditx()
{
	// TODO: Add your control notification handler code here
	m_var.iCurIdc  =  IDC_EDIT_x;
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_HIDE  );
}


void CDlgChromaKeyCfg::OnEnSetfocusEdity()
{
	// TODO: Add your control notification handler code here
	m_var.iCurIdc  =  IDC_EDIT_y;
	GetDlgItem(  IDC_SPIN_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_STATIC_plusInt  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_SPIN_plusFloat  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_plusFloat  )->ShowWindow(  SW_HIDE  );
}

void CDlgChromaKeyCfg::OnEnChangeEditkeyr()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	TCHAR  tBuf[256]  =  _T(  ""  );
	int  length  =  sizeof(  tBuf  );
	length  =  GetDlgItemText(  IDC_EDIT_key_r,  tBuf,  mycountof(  tBuf  )  );
	int  iVal  =  _ttol(  tBuf  );
	if  (  iVal  !=  toByte_rgb(  m_var.curKey.rgb_key.r  )  )  {
		if  (  iVal  <  0  )  {iVal  =  0;  }
		else if  (  iVal  >  255  )  {iVal  =  255;  }
		m_var.curKey.rgb_key.r  =  toFloat_rgb(  iVal  );

		BYTE  ucH  =  0, ucS  =  0, ucL  =  0;
#ifdef  __USE_hsl_chromaKey__
		convert_rgb_to_key_pixel(  toByte_rgb(  m_var.curKey.rgb_key.r  ),  toByte_rgb(  m_var.curKey.rgb_key.g  ),  toByte_rgb(  m_var.curKey.rgb_key.b  ),  &ucH,  &ucS,  &ucL ); 
		SetDlgItemInt(  IDC_STATIC_key_h,  ucH  );
		SetDlgItemInt(  IDC_STATIC_key_s,  ucS  );
		SetDlgItemInt(  IDC_STATIC_key_l,  ucL  );
#else

#if  0
		convert_rgb_to_key_pixel(  m_var.curKey.r_key,m_var.curKey.g_key,m_var.curKey.b_key,&m_var.curKey.ucY_key,&m_var.curKey.ucCb_key,&m_var.curKey.ucCr_key ); 
		SetDlgItemInt(  IDC_STATIC_key_y,  m_var.curKey.ucY_key  );
		SetDlgItemInt(  IDC_STATIC_key_cb,  m_var.curKey.ucCb_key  );
		SetDlgItemInt(  IDC_STATIC_key_cr,  m_var.curKey.ucCr_key  );
#endif

#endif

		if  (  m_var.cfg.usCnt  &&  m_var.usKeyIndex  >=  0  &&  m_var.usKeyIndex  <  m_var.cfg.usCnt  )  {
			memcpy(  &m_var.cfg.keys[m_var.usKeyIndex],  &m_var.curKey,  sizeof(  m_var.cfg.keys[m_var.usKeyIndex]  )  );
		}
		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );

		m_static_color.Invalidate(  TRUE  );

		int  iRet  =  refreshListBox(  m_hWnd,  IDC_LIST_chromaKey,  &m_var.cfg,  m_var.usKeyIndex  );
	}
}


void CDlgChromaKeyCfg::OnEnChangeEditkeyg()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	TCHAR  tBuf[256]  =  _T(  ""  );
	int  length  =  GetDlgItemText(  IDC_EDIT_key_g,  tBuf,  mycountof(  tBuf  )  );
	int  iVal  =  _ttol(  tBuf  );
	if  (  iVal  !=  toByte_rgb(  m_var.curKey.rgb_key.g  )  )  {
		if  (  iVal  <  0  )  {iVal  =  0;  }
		else if  (  iVal  >  255  )  {iVal  =  255;  }
		m_var.curKey.rgb_key.g  =  toFloat_rgb(  iVal  );
#ifdef  __USE_hsl_chromaKey__
		BYTE  ucH  =  0, ucS  =  0, ucL  =  0;
		convert_rgb_to_key_pixel(  toByte_rgb(  m_var.curKey.rgb_key.r  ),  toByte_rgb(  m_var.curKey.rgb_key.g  ),  toByte_rgb(  m_var.curKey.rgb_key.b  ),  &ucH,  &ucS,  &ucL  ); 
		SetDlgItemInt(  IDC_STATIC_key_h, ucH  );
		SetDlgItemInt(  IDC_STATIC_key_s, ucS  );
		SetDlgItemInt(  IDC_STATIC_key_l,  ucL  );
#else
#if  0
		convert_rgb_to_key_pixel(  m_var.curKey.r_key,m_var.curKey.g_key,m_var.curKey.b_key,&m_var.curKey.ucY_key,&m_var.curKey.ucCb_key,&m_var.curKey.ucCr_key ); 
		SetDlgItemInt(  IDC_STATIC_key_y,  m_var.curKey.ucY_key  );
		SetDlgItemInt(  IDC_STATIC_key_cb,  m_var.curKey.ucCb_key  );
		SetDlgItemInt(  IDC_STATIC_key_cr,  m_var.curKey.ucCr_key  );
#endif

#endif

		if  (  m_var.cfg.usCnt  &&  m_var.usKeyIndex  >=  0  &&  m_var.usKeyIndex  <  m_var.cfg.usCnt  )  {
			memcpy(  &m_var.cfg.keys[m_var.usKeyIndex],  &m_var.curKey,  sizeof(  m_var.cfg.keys[m_var.usKeyIndex]  )  );
		}
		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
		m_static_color.Invalidate(  TRUE  );

		int  iRet  =  refreshListBox(  m_hWnd,  IDC_LIST_chromaKey,  &m_var.cfg,  m_var.usKeyIndex  );
	}
}


void CDlgChromaKeyCfg::OnEnChangeEditkeyb()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	TCHAR  tBuf[256]  =  _T(  ""  );
	int  length  =  GetDlgItemText(  IDC_EDIT_key_b,  tBuf,  mycountof(  tBuf  )  );
	int  iVal  =  _ttol(  tBuf  );
	if  (  iVal  !=  toByte_rgb(  m_var.curKey.rgb_key.b  )  )  {
		if  (  iVal  <  0  )  {iVal  =  0;  }
		else if  (  iVal  >  255  )  {iVal  =  255;  }
		m_var.curKey.rgb_key.b  =  toFloat_rgb(  iVal  );
#ifdef  __USE_hsl_chromaKey__
		BYTE  ucH  =  0, ucS  =  0, ucL  =  0;
		convert_rgb_to_key_pixel(  toByte_rgb(  m_var.curKey.rgb_key.r  ),  toByte_rgb(  m_var.curKey.rgb_key.g  ),  toByte_rgb(  m_var.curKey.rgb_key.b  ),  &ucH,  &ucS,  &ucL );
		SetDlgItemInt(  IDC_STATIC_key_h, ucH  );
		SetDlgItemInt(  IDC_STATIC_key_s, ucS  );
		SetDlgItemInt(  IDC_STATIC_key_l, ucL  );
#else
#if 0
		convert_rgb_to_key_pixel(  m_var.curKey.r_key,m_var.curKey.g_key,m_var.curKey.b_key,&m_var.curKey.ucY_key,&m_var.curKey.ucCb_key,&m_var.curKey.ucCr_key ); 
		SetDlgItemInt(  IDC_STATIC_key_y,  m_var.curKey.ucY_key  );
		SetDlgItemInt(  IDC_STATIC_key_cb,  m_var.curKey.ucCb_key  );
		SetDlgItemInt(  IDC_STATIC_key_cr,  m_var.curKey.ucCr_key  );
#endif

#endif
		if  (  m_var.cfg.usCnt  &&  m_var.usKeyIndex  >=  0  &&  m_var.usKeyIndex  <  m_var.cfg.usCnt  )  {
			memcpy(  &m_var.cfg.keys[m_var.usKeyIndex],  &m_var.curKey,  sizeof(  m_var.cfg.keys[m_var.usKeyIndex]  )  );
		}
		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
		m_static_color.Invalidate(  TRUE  );

		int  iRet  =  refreshListBox(  m_hWnd,  IDC_LIST_chromaKey,  &m_var.cfg,  m_var.usKeyIndex  );
	}
}


void CDlgChromaKeyCfg::OnEnChangeEditkeytola()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
#if 0
	// TODO:  Add your control notification handler code here
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return;
	//  2013/10/06
	TCHAR  tBuf[1024]  =  _T(  ""  );
	float  fDistance  =  (  m_var.curKey.tolb100x  -  m_var.curKey.tola100x  )  /  100.  ;
	int  length  =  GetDlgItemText(  IDC_EDIT_key_tola,  tBuf,  mycountof(  tBuf  )  );
	float  fa  =  _ttof(  tBuf  );
	unsigned  int  fa100x  =  fa  *  100;
	if  (  fa100x  !=  m_var.curKey.tola100x  )  {
		if  (  fa  <=  0  )  {fa  =  1.0;  }
		else if  (  fa  >  200  )  {fa  =  200.;  }
		m_var.curKey.tola100x  =  fa100x;
		m_var.curKey.tolb100x  =  (  fa + fDistance  )  *  100;							//  2013/09/28
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  fa  );
		SetDlgItemText(  IDC_EDIT_key_tola,  tBuf  );				//   fa可能会调整,所以需要设置下.

		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );

		int  iRet  =  refreshListBox(  m_hWnd,  IDC_LIST_chromaKey,  &m_var.cfg,  m_var.usKeyIndex  );
	}
#endif
}


void CDlgChromaKeyCfg::OnEnChangeEditkeydistance()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
#if 0
	// TODO:  Add your control notification handler code here
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return;
	//  2013/10/06
	TCHAR  tBuf[128]  =  _T(  ""  ),  tBuf2[128]  =  _T(  ""  );
	unsigned int  uia100x  =  m_var.curKey.tola100x;
	int  length  =  GetDlgItemText(  IDC_EDIT_key_distance,  tBuf,  mycountof(  tBuf  )  );
	unsigned int  uiDistance100x  =  _ttof(  tBuf  ) * 100;
	if  (  uiDistance100x   >  20000  )  return;
		
	unsigned int  uib100x  =  uia100x  +  uiDistance100x;				//  2013/09/28
	
	if  (  uib100x  <=  uia100x  )  {uiDistance100x  =  100;  uib100x  =  uia100x  +  uiDistance100x; }
	else if  (  uib100x  >  20000  )  {uib100x  =  20000;  uiDistance100x  =  (uib100x  -  uia100x  >  0) ?  (uib100x - uia100x) : 100; }

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  uib100x / 100.  );	
	_sntprintf(  tBuf2,  mycountof(  tBuf2  ),  _T(  "%.2f"  ),  m_var.curKey.tolb100x / 100.  );
	//  
	if  (  uib100x  !=  m_var.curKey.tolb100x  )
	{
		m_var.curKey.tolb100x  =  uib100x;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  uiDistance100x  /  100.  );
		SetDlgItemText(  IDC_EDIT_key_distance,  tBuf  );

		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );

		int  iRet  =  refreshListBox(  m_hWnd,  IDC_LIST_chromaKey,  &m_var.cfg,  m_var.usKeyIndex  );
	}
#endif
}




void CDlgChromaKeyCfg::OnEnChangeEditminrgb()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	TCHAR  tBuf[256]  =  _T(  ""  );
	int  length  =  sizeof(  tBuf  );
	length  =  GetDlgItemText(  IDC_EDIT_minRgb,  tBuf,  mycountof(  tBuf  )  );
	int  iVal  =  _ttol(  tBuf  );
	BYTE  minRgb  =  m_var.cfg.minVal_r_g_b;
	if  (  iVal  !=  minRgb  )  {
		if  (  iVal  <  0  )  {iVal  =  0;  }
		else if  (  iVal  >  255  )  {iVal  =  255;  }
		m_var.cfg.minVal_r_g_b  =  iVal;

		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );

	}
}

void CDlgChromaKeyCfg::OnEnChangeEditmins()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	TCHAR  tBuf[1024]  =  _T(  ""  );
	unsigned  short  usfs  =  m_var.cfg.usMin_saturation;
	int  length  =  GetDlgItemText(  IDC_EDIT_minS,  tBuf,  mycountof(  tBuf  )  );
	usfs  =  _ttol(  tBuf  );
	if  (  usfs  !=  m_var.cfg.usMin_saturation  )  {
		if  (  usfs  <=  0  )  {usfs  =  1.0;  }
		else if  (  usfs  >  240  )  {usfs  =  240.;  }
		m_var.cfg.usMin_saturation  =  usfs;  
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  (  int  )usfs  );		
		SetDlgItemText(  IDC_EDIT_minS,  tBuf  );

		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
	}

}


void CDlgChromaKeyCfg::OnEnChangeEditminl()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	TCHAR  tBuf[1024]  =  _T(  ""  );
	unsigned  short  usfl  =  m_var.cfg.usMin_lightness;
	int  length  =  GetDlgItemText(  IDC_EDIT_minL,  tBuf,  mycountof(  tBuf  )  );
	usfl  =  _ttol(  tBuf  );
	if  (  usfl  !=  m_var.cfg.usMin_lightness  )  {
		if  (  usfl  <=  0  )  {  usfl  =  1.0;  }
		else if  (  usfl  >  240  )  {usfl  =  240.;  }

		//
		m_var.cfg.usMin_lightness  =  usfl;  

		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  (  int  )usfl  );		
		SetDlgItemText(  IDC_EDIT_minL,  tBuf  );
		
		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
	}
}


void CDlgChromaKeyCfg::OnEnChangeEditmaxl()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	TCHAR  tBuf[1024]  =  _T(  ""  );
	unsigned  short  usfl  =  m_var.cfg.usMax_lightness;
	int  length  =  GetDlgItemText(  IDC_EDIT_maxL,  tBuf,  mycountof(  tBuf  )  );
	usfl  =  _ttol(  tBuf  );
	if  (  usfl  !=  m_var.cfg.usMax_lightness  )  {
		if  (  usfl  <=  0.  )  {usfl  =  1.0;  }
		else if  (  usfl  >  240.  )  {usfl  =  240.;  }
		m_var.cfg.usMax_lightness  =  usfl;  
		_sntprintf(  tBuf,  mycountof(  tBuf ),  _T(  "%d"),  (  int  )usfl  );  
		SetDlgItemText(  IDC_EDIT_maxL,  tBuf  );

		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
	}
}

#if 0
void CDlgChromaKeyCfg::OnEnChangeEditfr()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return;

	TCHAR  tBuf[1024]  =  _T(  ""  );
	BYTE  f_r10x  =  m_var.cfg.f_reversoColor10x / 10.;
	int  length  =  GetDlgItemText(  IDC_EDIT_f_r,  tBuf,  mycountof(  tBuf  )  );
	f_r10x  =  _ttof(  tBuf  )  *  10;
	if  (  f_r10x  !=  m_var.cfg.f_reversoColor10x  )  {
		if  (  f_r10x  <=  0  )  {  f_r10x  =  0.5  *  10;  }
		else if  (  f_r10x  >  25  *  10  )  {f_r10x  =  25.0  *  10;  }
		m_var.cfg.f_reversoColor10x  =  f_r10x;  
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  f_r10x  /  10.  );		
		SetDlgItemText(  IDC_EDIT_f_r,  tBuf  );

		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
	}

}


void CDlgChromaKeyCfg::OnEnChangeEditedgedistance()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return;

	TCHAR  tBuf[1024]  =  _T(  ""  );
	GetDlgItemText(  IDC_EDIT_edge_distance,  tBuf,  mycountof(  tBuf  )  );
	int  iVal  =  _ttol(  tBuf  );
	if  (  iVal  >  200  )  iVal  =  200;
    if  (  iVal  <  0  )  iVal  =  0;
	if  (  iVal  !=  m_var.cfg.ucMax_edge_d  )  {
		m_var.cfg.ucMax_edge_d  =  iVal;
		SetDlgItemInt(  IDC_EDIT_edge_distance,  iVal  );

		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
	}
}
#endif
void CDlgChromaKeyCfg::OnEnChangeEditx()
{
	int  x;
	x  =  GetDlgItemInt(  IDC_EDIT_x  );
#ifdef  __DEBUG__
	traceLog(  _T(  "x:%d"  ),  x  );
#endif
	if  (  x  !=  m_var.x  )  m_var.x  =  x;

	dlgImg_xyColor(  m_var.hWnd_img,  m_var.x,  m_var.y  );

	return;
}
void CDlgChromaKeyCfg::OnEnChangeEdity()
{
	int  y;
	y  =  GetDlgItemInt(  IDC_EDIT_y  );
#ifdef  __DEBUG__
	traceLog(  _T(  "y:%d"  ),  y  );
#endif
	if  (  y  !=  m_var.y  )  m_var.y  =  y;

	dlgImg_xyColor(  m_var.hWnd_img,  m_var.x,  m_var.y  );

	return;
}


void CDlgChromaKeyCfg::OnDeltaposSpinplusint(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	TCHAR  tBuf[1024]  =  _T(  ""  );
	BOOL  bChanged  =  FALSE, bColorChanged  =  FALSE;
	int  r,g,b,iIdc, iDelta, iVal;
	float fa,fb,fDistance,fm;
	unsigned int xy;
	iIdc  =  m_var.iCurIdc;
	switch  (  iIdc  )  {
			case  IDC_EDIT_key_r:
				  r  =  toByte_rgb(  m_var.curKey.rgb_key.r  );
				  if  (  pNMUpDown->iDelta  >  0  )  {
					  r ++  ;
					  }
				  else  if  (  pNMUpDown->iDelta  <  0  )  {
					  r  --;
				  }
				  if  (  r  !=  toByte_rgb(  m_var.curKey.rgb_key.r  )  )  {
					  bColorChanged  =  TRUE;
					  m_var.curKey.rgb_key.r = toFloat_rgb(  r  );
					  SetDlgItemInt(  IDC_EDIT_key_r,  r  );
				  }
				  break;
			case  IDC_EDIT_key_g:
				  g  =  toByte_rgb(  m_var.curKey.rgb_key.g  );
				  if  (  pNMUpDown->iDelta  >  0  )  {
					  g ++  ;
					  }
				  else  if  (  pNMUpDown->iDelta  <  0  )  {
					  g  --;
				  }
				  if  (  g  !=  toByte_rgb(  m_var.curKey.rgb_key.g  )  )  {
					  bColorChanged  =  TRUE;
					  m_var.curKey.rgb_key.g  =  toFloat_rgb(  g  );
					  SetDlgItemInt(  IDC_EDIT_key_g,  g  );
				  }
				  break;
			case  IDC_EDIT_key_b:
				  b  =  toByte_rgb(  m_var.curKey.rgb_key.b  );
				  if  (  pNMUpDown->iDelta  >  0  )  {
					  b ++  ;
					  }
				  else  if  (  pNMUpDown->iDelta  <  0  )  {
					  b  --;
				  }
				  if  (  b  !=  toByte_rgb(  m_var.curKey.rgb_key.b  )  )  {
					  bColorChanged  =  TRUE;
					  m_var.curKey.rgb_key.b  =  toFloat_rgb(  b  );
					  SetDlgItemInt(  IDC_EDIT_key_b,  b  );
				  }
				  break;
#if 0
			case  IDC_EDIT_key_tola:
				  iDelta  =  0;  
				  fa  =  m_var.curKey.tola100x  /  100.;
				  fDistance  =  (  m_var.curKey.tolb100x  -  m_var.curKey.tola100x  )  /  100.;
				  if  (  pNMUpDown->iDelta  >  0  )  {
					  iDelta ++  ;
					  }
				  else  if  (  pNMUpDown->iDelta  <  0  )  {
					  iDelta  --;
				  }
				  fa +=  ( float  )iDelta;
				  if  (  fa  <=  0  )  fa  =  1.0;
				  if  (  fa  >  200.  )  fa  =  200.0;
				  if  (  fa  !=  m_var.curKey.tola100x  /  100.  )  {
					  bChanged  =  TRUE;
					  m_var.curKey.tola100x  =  fa  *  100; 
					  m_var.curKey.tolb100x  =  (  fa  +  fDistance  )  *  100;
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  fa  );
					  SetDlgItemText(  IDC_EDIT_key_tola,  tBuf  );
				  }
				  break;
			case  IDC_EDIT_key_distance:
				  iDelta  =  0;
				  fDistance  =  (  m_var.curKey.tolb100x  -  m_var.curKey.tola100x  )  /  100.;
				  if  (  pNMUpDown->iDelta  >  0  )  {
					  iDelta ++  ;
					  }
				  else  if  (  pNMUpDown->iDelta  <  0  )  {
					  iDelta  --;
				  }
				  fDistance  +=  (float)iDelta;
				  fb  =  fDistance  +  m_var.curKey.tola100x  /  100.;
				  if  (  fb  !=  	m_var.curKey.tolb100x  /  100.  )  {
					  bChanged  =  TRUE;
					  if  (  fb  <=  m_var.curKey.tola100x  /  100.  )  {  fDistance  =  1.0;  fb  =  fDistance  +  m_var.curKey.tola100x  /  100.;  }
					  if  (  fb  >  201.  )  { fb  =  201.0;  fDistance  =  ((  fb  -  m_var.curKey.tola100x  /  100. > 0)  ?  (  fb  -  m_var.curKey.tola100x  /  100. ) : 1.0  ); }
					  m_var.curKey.tolb100x  =  fb  *  100;
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  fDistance  );
					  SetDlgItemText(  IDC_EDIT_key_distance,  tBuf  );
				  }
				  break;
#endif
			case  IDC_EDIT_minRgb:
				  iDelta  =  m_var.cfg.minVal_r_g_b;
				  if  (  pNMUpDown->iDelta  >  0  )  {  iDelta ++  ;  }
				  else  if  (  pNMUpDown->iDelta  <  0  )  {  iDelta  --;  }
				  //
				  if  (  iDelta  !=  m_var.cfg.minVal_r_g_b  )  {
					  bChanged  =  TRUE;
					  m_var.cfg.minVal_r_g_b  =  iDelta;
					  SetDlgItemInt(  IDC_EDIT_minRgb,  iDelta    );
				  }
				  break;
			case  IDC_EDIT_minS:
				  iDelta  =  0;  
				  fm  =  m_var.cfg.usMin_saturation;
				  if  (  pNMUpDown->iDelta  >  0  )  {
					  iDelta ++  ;
					  }
				  else  if  (  pNMUpDown->iDelta  <  0  )  {
					  iDelta  --;
				  }
				  fm +=  ( float  )iDelta;
				  if  (  fm  <=  0  )  fm  =  1.0;
				  if  (  fm  >  240.  )  fm  =  240.0;
				  if  (  (  (  unsigned  short  )fm  )  !=  m_var.cfg.usMin_saturation  )  {
					  bChanged  =  TRUE;
					  m_var.cfg.usMin_saturation  =  fm; 
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  fm  );
					  SetDlgItemText(  IDC_EDIT_minS,  tBuf  );
				  }
				  break;
			case  IDC_EDIT_minL:
				  iDelta  =  0;  
				  fm  =  m_var.cfg.usMin_lightness;
				  if  (  pNMUpDown->iDelta  >  0  )  {
					  iDelta ++  ;
					  }
				  else  if  (  pNMUpDown->iDelta  <  0  )  {
					  iDelta  --;
				  }
				  fm +=  ( float  )iDelta;
				  if  (  fm  <=  0  )  fm  =  1.0;
				  if  (  fm  >  240.  )  fm  =  240.0;
				  if  (  (  unsigned  short  )fm  !=  m_var.cfg.usMin_lightness  )  {
					  bChanged  =  TRUE;
					  m_var.cfg.usMin_lightness  =  fm; 
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  fm  );
					  SetDlgItemText(  IDC_EDIT_minL,  tBuf  );
				  }
				  break;
			case  IDC_EDIT_maxL:
				  iDelta  =  0;  
				  fm  =  m_var.cfg.usMax_lightness;
				  if  (  pNMUpDown->iDelta  >  0  )  {
					  iDelta ++  ;
					  }
				  else  if  (  pNMUpDown->iDelta  <  0  )  {
					  iDelta  --;
				  }
				  fm +=  ( float  )iDelta;
				  if  (  fm  <=  0  )  fm  =  1.0;
				  if  (  fm  >  240.  )  fm  =  240.0;
				  if  (  (  (  unsigned  short  )fm  )  !=  m_var.cfg.usMax_lightness  )  {
					  bChanged  =  TRUE;
					  m_var.cfg.usMax_lightness  =  fm; 
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  fm  );
					  SetDlgItemText(  IDC_EDIT_maxL,  tBuf  );
				  }
				  break;
#if 0
			case  IDC_EDIT_edge_distance:
				  //
				  iVal  =  m_var.cfg.ucMax_edge_d;
				  iDelta  =  0;
				  if  (  pNMUpDown->iDelta  >  0  )  {  iDelta ++  ;  }
				  else  if  (  pNMUpDown->iDelta  <  0  )  {  iDelta  --;  }
				  iVal  += iDelta;
				  if  (  iVal  >  200  )  iVal  =  200;
				  if  (  iVal <  0  )  iVal  =  0;
				  //
				  if  (  iVal  !=  m_var.cfg.ucMax_edge_d  )  {
					  m_var.cfg.ucMax_edge_d  =  iVal;
					  bChanged  =  TRUE;
					  SetDlgItemInt(  IDC_EDIT_edge_distance,  iVal  );
				  }
				  break;
#endif
			case  IDC_EDIT_x:
				  iDelta  =  0;  
				  xy  =  m_var.x;
				  if  (  pNMUpDown->iDelta  >  0  )  {
					  iDelta ++  ;
					  }
				  else  if  (  pNMUpDown->iDelta  <  0  )  {
					  iDelta  --;
				  }
				  xy +=  ( float  )iDelta;
				  if  (  xy  !=  m_var.x  )  {
					  m_var.x  =  xy; 
					  SetDlgItemInt(  IDC_EDIT_x,  xy  );
				  }
				  break;
			case  IDC_EDIT_y:
				  iDelta  =  0;  
				  xy  =  m_var.y;
				  if  (  pNMUpDown->iDelta  >  0  )  {
					  iDelta ++  ;
					  }
				  else  if  (  pNMUpDown->iDelta  <  0  )  {
					  iDelta  --;
				  }
				  xy +=  ( float  )iDelta;
				  if  (  xy  !=  m_var.y  )  {
					  m_var.y  =  xy; 
					  SetDlgItemInt(  IDC_EDIT_y,  xy  );
				  }
				  break;
			default:
				break;				  	
	}

	if  (  bColorChanged  )  {
		m_static_color.Invalidate(  TRUE  );
#ifdef  __USE_hsl_chromaKey__
		BYTE  ucH  =  0, ucS  =  0, ucL  =  0;
		convert_rgb_to_key_pixel(  toByte_rgb(  m_var.curKey.rgb_key.r  ),  toByte_rgb(  m_var.curKey.rgb_key.g  ),  toByte_rgb(  m_var.curKey.rgb_key.b  ),  &ucH,  &ucS,  &ucL );
		SetDlgItemInt(  IDC_STATIC_key_h, ucH  );
		SetDlgItemInt(  IDC_STATIC_key_s, ucS  );
		SetDlgItemInt(  IDC_STATIC_key_l, ucL  );
#else
#if  0
		convert_rgb_to_key_pixel(  m_var.curKey.r_key,m_var.curKey.g_key,m_var.curKey.b_key,&m_var.curKey.ucY_key,&m_var.curKey.ucCb_key,&m_var.curKey.ucCr_key ); 
		SetDlgItemInt(  IDC_STATIC_key_y,  m_var.curKey.ucY_key  );
		SetDlgItemInt(  IDC_STATIC_key_cb,  m_var.curKey.ucCb_key  );
		SetDlgItemInt(  IDC_STATIC_key_cr,  m_var.curKey.ucCr_key  );
#endif

#endif
	}

	if  (  bChanged  ||  bColorChanged  )  {
		if  (  m_var.cfg.usCnt  &&  m_var.usKeyIndex  >=  0  &&  m_var.usKeyIndex  <  m_var.cfg.usCnt  )  
		{
			memcpy(  &m_var.cfg.keys[m_var.usKeyIndex],  &m_var.curKey,  sizeof(  m_var.cfg.keys[m_var.usKeyIndex]  )  );
		}
		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
		dlgImg_testKeying(  m_var.hWnd_img  );
		SetDlgItemInt(  IDC_EDIT_x,  m_var.x  );			//  2013/10/12
		SetDlgItemInt(  IDC_EDIT_y,  m_var.y  );
		//
		bChanged  =  FALSE;
		bColorChanged  =  FALSE;


		refreshListBox(  m_hWnd,  IDC_LIST_chromaKey,  &m_var.cfg,  m_var.usKeyIndex  );

	}

	*pResult = 0;
}

void CDlgChromaKeyCfg::OnDeltaposSpinplusfloat(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	TCHAR  tBuf[1024]  =  _T(  ""  );
	BOOL  bChanged  =  FALSE;
	int  iIdc,iDelta;
	float fa,fb,fDistance,fm;
	iIdc  =  m_var.iCurIdc;
	switch  (  iIdc  )  {
#if 0
			case  IDC_EDIT_key_tola:
				  fa  =  m_var.curKey.tola100x  /  100.;
				  fDistance  =  (  m_var.curKey.tolb100x  -  m_var.curKey.tola100x  )  /  100.;
				  if  (  pNMUpDown->iDelta  >  0  )  fa +=  0.1;
				  else  if  (  pNMUpDown->iDelta  <  0  )  fa -=  0.1;
				  if  (  fa  <  0  )  fa  =  0.1;
				  if  (  fa  >  200.  )  fa  =  200.0;
				  if  (  fa  !=  m_var.curKey.tola100x  /  100.  )  {
					  bChanged  =  TRUE;
					  m_var.curKey.tola100x  =  fa  *  100; 
					  m_var.curKey.tolb100x  =  (  fa  +  fDistance  )  *  100;
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  fa  );
					  SetDlgItemText(  IDC_EDIT_key_tola,  tBuf  );
				  }
				  break;
			case  IDC_EDIT_key_distance:
				  fDistance  =  (  m_var.curKey.tolb100x  -  m_var.curKey.tola100x  )  /  100.;
				  if  (  pNMUpDown->iDelta  >  0  )  fDistance +=  0.1;
				  else  if  (  pNMUpDown->iDelta  <  0  )  fDistance -=  0.1;
				  if  (  fDistance  <  0  )  fDistance  =  0.1;
				  if  (  fDistance  >  199.  )  fDistance  =  199.0;
				  fb  =  fDistance  +  m_var.curKey.tola100x  /  100.;
				  if  (  fb  !=  	m_var.curKey.tolb100x  /  100.  )  {
					  bChanged  =  TRUE;
					  if  (  fb  <=  m_var.curKey.tola100x  /  100.  )  {  fDistance  =  1.0;  fb  =  fDistance  +  m_var.curKey.tola100x  /  100.;  }
					  if  (  fb  >  201.  )  { fb  =  201.0;  fDistance  =  ((  fb  -  m_var.curKey.tola100x  /  100. > 0)  ?  (  fb  -  m_var.curKey.tola100x  /  100. ) : 1.0  ); }
					  m_var.curKey.tolb100x  =  fb  *  100;
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  fDistance  );
					  SetDlgItemText(  IDC_EDIT_key_distance,  tBuf  );
				  }
				  break;
			case  IDC_EDIT_f_r:  {
				  unsigned int ui10x  =  m_var.cfg.f_reversoColor10x;
				  iDelta  =  0;
				  if  (  pNMUpDown->iDelta  >  0  )  iDelta  ++;  //  fm +=  0.1;
				  else  if  (  pNMUpDown->iDelta  <  0  )  iDelta --;  //  fm -=  0.1;
				  ui10x  +=  iDelta;
				  if  (  ui10x  <  0  )  ui10x  =  250;
				  else  if  (  ui10x  >  250  )  ui10x  =  0;
				  if  (  ui10x  !=  m_var.cfg.f_reversoColor10x  )  {
					  bChanged  =  TRUE;
					  m_var.cfg.f_reversoColor10x  =  ui10x; 
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  ( float )ui10x /  10.  );
					  SetDlgItemText(  IDC_EDIT_f_r,  tBuf  );
				  }}
				  break;
#endif
#if  0
			case  IDC_EDIT_minS:
				  fm  =  m_var.cfg.usMin_saturation;
				  if  (  pNMUpDown->iDelta  >  0  )  fm +=  0.1;
				  else  if  (  pNMUpDown->iDelta  <  0  )  fm -=  0.1;
				  if  (  fm  <  0  )  fm  =  0.1;
				  if  (  fm  >  240.  )  fm  =  240.0;
				  if  (  (  (  unsigned  short  )fm  )  !=  m_var.cfg.usMin_saturation  )  {
					  bChanged  =  TRUE;
					  m_var.cfg.usMin_saturation  =  fm; 
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  fm  );
					  SetDlgItemText(  IDC_EDIT_minS,  tBuf  );
				  }
				  break;
			case  IDC_EDIT_minL:
				  fm  =  m_var.cfg.usMin_lightness;
				  if  (  pNMUpDown->iDelta  >  0  )  fm +=  0.1;
				  else  if  (  pNMUpDown->iDelta  <  0  )  fm -=  0.1;
				  if  (  fm  <  0  )  fm  =  0.1;
				  if  (  fm  >  240.  )  fm  =  240.0;
				  if  (  ((  unsigned  short  )fm  )  !=  m_var.cfg.usMin_lightness  )  {
					  bChanged  =  TRUE;
					  m_var.cfg.usMin_lightness  =  fm; 
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  fm  );
					  SetDlgItemText(  IDC_EDIT_minL,  tBuf  );
				  }
				  break;
			case  IDC_EDIT_maxL:
				  fm  =  m_var.cfg.usMax_lightness;
				  if  (  pNMUpDown->iDelta  >  0  )  fm +=  0.1;
				  else  if  (  pNMUpDown->iDelta  <  0  )  fm -=  0.1;
				  if  (  fm  <  0  )  fm  =  0.1;
				  if  (  fm  >  240.  )  fm  =  240.0;
				  if  (  ((  unsigned  short  )fm  )  !=  m_var.cfg.usMax_lightness  )  {
					  bChanged  =  TRUE;
					  m_var.cfg.usMax_lightness  =  fm; 
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  fm  );
					  SetDlgItemText(  IDC_EDIT_maxL,  tBuf  );
				  }
				  break;
#endif
			default:
				break;				  	
	}

	if  (  bChanged  ){
		memcpy(  &m_var.cfg.keys[m_var.usKeyIndex],  &m_var.curKey,  sizeof(  m_var.cfg.keys[m_var.usKeyIndex]  )  );

		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
		dlgImg_testKeying(  m_var.hWnd_img  );
		SetDlgItemInt(  IDC_EDIT_x,  m_var.x  );			//  2013/10/12
		SetDlgItemInt(  IDC_EDIT_y,  m_var.y  );

		bChanged  =  FALSE;

		refreshListBox(  m_hWnd,  IDC_LIST_chromaKey,  &m_var.cfg,  m_var.usKeyIndex  );

	}

	*pResult = 0;
}

void CDlgChromaKeyCfg::OnBnClickedCheckusechromakey()
{
	// TODO: Add your control notification handler code here
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	int  idc  =  IDC_CHECK_useChromaKey;
	if  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  {
		m_var.cfg.bUseChromaKey  =  TRUE;

		idc  =  IDC_CHECK_keyingAFrame;
		m_var.bKeyingAFrame  =  FALSE;	
		(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.bKeyingAFrame  ?  1 : 0  );
		GetDlgItem(  idc  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_x  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_y  )->EnableWindow(  FALSE  );
		idc		=	IDC_CHECK_pick;
		GetDlgItem(  idc  )->ShowWindow(  SW_HIDE  );
	}
	else  {
		m_var.cfg.bUseChromaKey  =  FALSE;

		idc  =  IDC_CHECK_keyingAFrame;
		m_var.bKeyingAFrame  =  TRUE;	
		(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.bKeyingAFrame  ?  1 : 0  );
		GetDlgItem(  idc  )->EnableWindow(  TRUE  );
		GetDlgItem(  IDC_EDIT_x  )->EnableWindow(  TRUE  );
		GetDlgItem(  IDC_EDIT_y  )->EnableWindow(  TRUE  );
		idc		=	IDC_CHECK_pick;
		GetDlgItem(  idc  )->ShowWindow(  SW_SHOW  );
	}
	

	QY_MC		*	pQyMc	=  QY_GET_GBUF(  );
	if  (  !pQyMc  )  traceLog(  _T(  "CDlgChromaKeyCfg::OnBnClickedCheckusechromakey error!"  )  );

	QY_REG  reg;
	TCHAR	*	pRegVal  =  NULL;
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	_sntprintf(  reg.rootKey,  sizeof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );

	TCHAR  tBuf[128]  =  _T(  ""  );
	pRegVal  =  CONST_regValName_keyCfg_bUseKey;
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  m_var.cfg.bUseChromaKey,  tBuf,  10  )  );

	pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
}

void CDlgChromaKeyCfg::OnBnClickedCheckkeyingaframe()
{
	// TODO: Add your control notification handler code here
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	int  idc  =  IDC_CHECK_keyingAFrame;
	if  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  {
		m_var.bKeyingAFrame  =  TRUE;
		GetDlgItem(  IDC_EDIT_x  )->EnableWindow(  TRUE  );
		GetDlgItem(  IDC_EDIT_y  )->EnableWindow(  TRUE  );
	}
	else  {
		m_var.bKeyingAFrame  =  FALSE;
		GetDlgItem(  IDC_EDIT_x  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_y  )->EnableWindow(  FALSE  );
	}

	pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );

	idc		=	IDC_CHECK_pick;
	GetDlgItem(  idc  )->ShowWindow(  SW_SHOW  );

}

void CDlgChromaKeyCfg::OnBnClickedCheckpick()
{
	// TODO: Add your control notification handler code here
	if ( m_var.bPickColor ) m_var.bPickColor =  FALSE;
	else m_var.bPickColor = TRUE;

	CWnd  *  pCtrl;
	pCtrl  =  GetDlgItem(  IDC_CHECK_pick  );
	(  (  CButton  *  )pCtrl  )->SetCheck(  m_var.bPickColor  ?  BST_CHECKED  :  BST_UNCHECKED  );

	//
	if  (  m_var.bPickColor  )  {
		SetCapture(  );
		#ifdef  __DEBUG__
				traceLog(  _T(  "pick: SetCapture"  )  );
		#endif
	}

}
#if 0
void CDlgChromaKeyCfg::OnBnClickedChecksmooth()
{
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return;

	int  iIdc  =  IDC_CHECK_smooth;
	if  (  ((  CButton  *  )GetDlgItem(  iIdc  ))->GetCheck(  )  ==  BST_CHECKED  )  {
		m_var.cfg.bStartSmooth  =  TRUE;
	}
	else  {
		m_var.cfg.bStartSmooth  =  FALSE;
	}

	pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
	dlgImg_testKeying(  m_var.hWnd_img  );

	return;
}
void CDlgChromaKeyCfg::OnBnClickedCheckedgecolor()
{
	// TODO: Add your control notification handler code here
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return;

	int  iIdc  =  IDC_CHECK_edgeColor;
	if  (  ((  CButton  *  )GetDlgItem(  iIdc  ))->GetCheck(  )  ==  BST_CHECKED  )  {
		m_var.cfg.bEdgeColor  =  TRUE;
		GetDlgItem(  IDC_EDIT_edge_distance  )->EnableWindow(  TRUE  );
		GetDlgItem(  IDC_EDIT_f_r  )->EnableWindow(  TRUE  );
	}
	else  {
		m_var.cfg.bEdgeColor  =  FALSE;
		GetDlgItem(  IDC_EDIT_edge_distance  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_f_r  )->EnableWindow(  FALSE  );
	}

	pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
	dlgImg_testKeying(  m_var.hWnd_img  );
}
#endif

void CDlgChromaKeyCfg::OnBnClickedAdd()
{
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

 
	TCHAR  tBuf[256]  =  _T(  ""  );
	int r,g,b,y,cb,cr,tola,tolb;
	float  fTa= 0,  fTb=0, fDistance=0,fm = 0;
	GetDlgItemText(  IDC_EDIT_key_r,  tBuf,  mycountof(  tBuf  )  );
	r  =  _ttol(  tBuf  );
	GetDlgItemText(  IDC_EDIT_key_g,  tBuf,  mycountof(  tBuf  )  );
	g  =  _ttol(  tBuf  );
	GetDlgItemText(  IDC_EDIT_key_b,  tBuf,  mycountof(  tBuf  )  );
	b  =  _ttol(  tBuf  );
	//
#if 0
    GetDlgItemText(  IDC_EDIT_key_tola,  tBuf,  mycountof(  tBuf  )  );
	fTa  =  _ttof(  tBuf  );
	if  (  fTa  <  0  )   fTa  =  1.0;
	if  (  fTa  >  200.  )  fTa  =  200.0;
	if  (  fTa  ==  0  )  fTa  =  5.1;
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f" ),  fTa  );
	if  (  fTa  !=  key.tola100x  /  100.  )  {  key.tola100x  =  fTa  *  100;  }
	
	GetDlgItemText(  IDC_EDIT_key_distance,  tBuf,  mycountof(  tBuf  )  );
	fDistance  =  _ttof(  tBuf  );
	if  (  fDistance  <  0  )  fDistance  =  1.0;
	if  (  fDistance  >  200.  )  fDistance  =  199.0;
	if  (  fDistance  ==  0  )  fDistance  =  0.2;
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f" ),  fDistance  );
	fTb  =  fDistance  +  key.tola100x  /  100.;
	if  (  fTb  !=  key.tolb100x  /  100.  )  {  key.tolb100x  =  fTb  *  100;  }
#endif
	tola = CONST_key_tola;
	tolb = CONST_key_tolb;
	//
    GetDlgItemText(  IDC_EDIT_minS,  tBuf,  mycountof(  tBuf  )  );
	fm  =  _ttof(  tBuf  );
	if  (  fm  <  0  )   fm  =  1.0;
	if  (  fm  >  240.  )  fm  =  240.0;
	if  (  fm  ==  0  )  fm  =  36.00;
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f" ),  fm  );
	if  (  (  (  unsigned  short  )fm  )  !=  m_var.cfg.usMin_saturation  )  {  m_var.cfg.usMin_saturation  =  fm;  }
	//
    GetDlgItemText(  IDC_EDIT_minL,  tBuf,  mycountof(  tBuf  )  );
	fm  =  _ttof(  tBuf  );
	if  (  fm  <=  0  )   fm  =  1.0;
	if  (  fm  >  240.  )  fm  =  240.0;
	if  (  fm  ==  0  )  fm  =  28.8;
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f" ),  fm  );
	if  (  (  unsigned  short  )fm  !=  m_var.cfg.usMin_lightness  )  {  m_var.cfg.usMin_lightness  =  fm;  }

    GetDlgItemText(  IDC_EDIT_maxL,  tBuf,  mycountof(  tBuf  )  );
	fm  =  _ttof(  tBuf  );
	if  (  fm  <=  0  )   fm  =  1.0;
	if  (  fm  >  240.  )  fm  =  240.0;
	if  (  fm  ==  0  )  fm  =  192.00;
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f" ),  fm  );
	if  (  (  (  unsigned  short  )fm  )  !=  m_var.cfg.usMax_lightness  )  {  m_var.cfg.usMax_lightness  =  fm;  }
	//
	if  (  pFuncs->imgProcess.pf_addColorKey(  r,  g,  b,  tola,  tolb,  TRUE,  &m_var.cfg  )  )  {
		goto  errLabel;
	}
	pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );

	if  (  !m_var.cfg.usCnt  )  goto  errLabel;
	m_var.usKeyIndex  =  m_var.cfg.usCnt -  1;

	if  (  memcmp(  &m_var.curKey,  &m_var.cfg.keys[m_var.usKeyIndex],  sizeof(  m_var.curKey )  )  )  {
		memcpy(  &m_var.curKey,  &m_var.cfg.keys[m_var.usKeyIndex],  sizeof(  m_var.curKey )  );
	}

	refreshListBox(  m_hWnd,  IDC_LIST_chromaKey,  &m_var.cfg,  m_var.usKeyIndex  );

errLabel:

	return;
}

void CDlgChromaKeyCfg::OnBnClickedDel()
{
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	TCHAR		tBuf[1024];
	//
	if  (  m_var.usKeyIndex  <  0  &&  m_var.usKeyIndex >= m_var.cfg.usCnt )  return;
	pFuncs->imgProcess.pf_delColorKey(  m_var.usKeyIndex,  &m_var.cfg  );
	pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
	dlgImg_testKeying(  m_var.hWnd_img  );

	//
	HWND  hCtrl  =  ::GetDlgItem(  m_hWnd,  IDC_LIST_chromaKey  );
	int  i;
	::SendMessage(  hCtrl,  LB_RESETCONTENT,  (  WPARAM  )NULL,  (  LPARAM  )NULL  );    

	if  (  !m_var.cfg.usCnt  )  {
		return;
	}
	if  (  m_var.usKeyIndex  <  0  )m_var.usKeyIndex  =  0;
	if  (  m_var.usKeyIndex  >=  m_var.cfg.usCnt  )  m_var.usKeyIndex  =  m_var.cfg.usCnt -1;
	memcpy(  &m_var.curKey,  &m_var.cfg.keys[m_var.usKeyIndex],  sizeof(  m_var.curKey  )  );


		int  iRet  =  refreshListBox(  m_hWnd,  IDC_LIST_chromaKey,  &m_var.cfg,  m_var.usKeyIndex  );

		i =  m_var.usKeyIndex;
		SetDlgItemInt(  IDC_EDIT_key_r,  toByte_rgb(  m_var.curKey.rgb_key.r  )  );
		SetDlgItemInt(  IDC_EDIT_key_g,  toByte_rgb(  m_var.curKey.rgb_key.g  )  );
		SetDlgItemInt(  IDC_EDIT_key_b,  toByte_rgb(  m_var.curKey.rgb_key.b  )  );
#ifdef  __USE_hsl_chromaKey__
		SetDlgItemInt(  IDC_STATIC_key_h,  toByte_hsl(  m_var.curKey.hsl_key.x  )  );
		SetDlgItemInt(  IDC_STATIC_key_s,  toByte_hsl(  m_var.curKey.hsl_key.y  )  );
		SetDlgItemInt(  IDC_STATIC_key_l,  toByte_hsl(  m_var.curKey.hsl_key.z  )  );
#else
#if  0
		SetDlgItemInt(  IDC_STATIC_key_y,  m_var.curKey.ucY_key  );
		SetDlgItemInt(  IDC_STATIC_key_cb,  m_var.curKey.ucCb_key  );
		SetDlgItemInt(  IDC_STATIC_key_cr,  m_var.curKey.ucCr_key  );
#endif

#endif
#if  0
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  m_var.curKey.tola100x  /  100.  );
		SetDlgItemText(  IDC_EDIT_key_tola,  tBuf  );
	    float  fDistance  =  (  m_var.curKey.tolb100x  -  m_var.curKey.tola100x  )  /  100.;
		if  (  fDistance <= 0  )  fDistance =  1.0;
		if  (  fDistance > 199.0  )  fDistance  =  199.0;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  fDistance  );
		SetDlgItemText(  IDC_EDIT_key_distance,  tBuf  );
#endif
	

	return;
}

void CDlgChromaKeyCfg::OnBnClickedButtonsave()
{
	// TODO: Add your control notification handler code here
	QY_MC		*  pQyMc	=	QY_GET_GBUF(  );
	if  (  !pQyMc  )  {
		traceLog(  _T(  "CDlgChromaKeyCfg::OnBnClickedButtonsave failed: pQyMc is null"  )  );
		return;
	}

	QY_REG				reg;
	TCHAR			*	pRegVal		=  NULL;
	int					i;
	TCHAR				tBuf[256]	=	_T(  ""  );
	TCHAR				tRegBuf[256]	=	_T(  ""  );

	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	_sntprintf(  reg.rootKey,  sizeof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );

	pRegVal  =  CONST_regValName_keyCfg_usCnt;
	_sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "%d"  ),  m_var.cfg.usCnt  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

	pRegVal  =  CONST_regValName_keyCfg_bUseKey;
	_sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "%d"  ),  m_var.cfg.bUseChromaKey  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

	pRegVal  =  CONST_regValName_keyCfg_minRgb;
	_sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "%d"  ),  m_var.cfg.minVal_r_g_b  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

	pRegVal  =  CONST_regValName_keyCfg_minS;
	_sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "%d"  ),  (  int  )m_var.cfg.usMin_saturation  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

	pRegVal  =  CONST_regValName_keyCfg_minL;
	_sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "%d"  ),  (  int  )m_var.cfg.usMin_lightness  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

	pRegVal  =  CONST_regValName_keyCfg_maxL;
	_sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "%d"  ),  (  int  )m_var.cfg.usMax_lightness  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );
#if 0
	pRegVal  =  CONST_regValName_keyCfg_bStartSmooth;
	_sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "%d"  ),  m_var.cfg.bStartSmooth  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

	pRegVal  =  CONST_regValName_keyCfg_bEdgeColor;
	_sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "%d"  ),  m_var.cfg.bEdgeColor  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

	pRegVal  =  CONST_regValName_keyCfg_r_f;
	_sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "%.2f"  ),  m_var.cfg.f_reversoColor10x  /  10.  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

	pRegVal  =  CONST_regValName_keyCfg_r_rgb;
	_sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "%d"  ),  m_var.cfg.reverseColor  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );
#endif
	pRegVal  =  CONST_regValName_keyCfg_preBlur;
	_sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "%.2f"  ),  m_var.cfg.fSigma_preBlur  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

	pRegVal  =  CONST_regValName_keyCfg_postBlur;
	_sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "%.2f"  ),  m_var.cfg.fSigma_postBlur  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

	pRegVal  =  CONST_regValName_keyCfg_gamma;
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  m_var.cfg.fGamma  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );


	_sntprintf(  tRegBuf,  mycountof(  tRegBuf  ),  _T(  "%s"  ),  reg.rootKey  );

	for (  i =  0;  i <  m_var.cfg.usCnt;  i ++  )  {
	
		_sntprintf(  reg.rootKey,  sizeof(  reg.rootKey  ),  _T(  "%s\\key%d"  ),  tRegBuf,  i  );

		pRegVal  =  CONST_regValName_key_r;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  toByte_rgb(  m_var.cfg.keys[i].rgb_key.r  )  );
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

		pRegVal  =  CONST_regValName_key_g;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  toByte_rgb(  m_var.cfg.keys[i].rgb_key.g  )  );
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

		pRegVal  =  CONST_regValName_key_b;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  toByte_rgb(  m_var.cfg.keys[i].rgb_key.b  )  );
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

#if 0
		pRegVal  =  CONST_regValName_key_tola;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  m_var.cfg.keys[i].cfg.tola100x  /  100.  );
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

		pRegVal  =  CONST_regValName_key_tolb;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f"  ),  m_var.cfg.keys[i].cfg.tolb100x  /  100.  );
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );
#else
		pRegVal  =  CONST_regValName_key_tola;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  m_var.cfg.keys[i].tola );
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );

		pRegVal  =  CONST_regValName_key_tolb;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  m_var.cfg.keys[i].tolb  );
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );
#endif

	}


	return;

}

 int  pickColor(HWND  hWnd,  COLORREF  *  pColor  )
{
	int  iErr  =  -1;
	HDC hdcWindow =  NULL;
	COLORREF  color  =  0;


    hdcWindow = GetDC(hWnd);
	if  (  !hdcWindow  )  goto  errLabel;

	TCHAR  tBuf[1024]  =  _T(  ""  );
	POINT  mouse;
	GetCursorPos(  &mouse  );
	MapWindowPoints(  NULL,  hWnd,  (  LPPOINT  )&mouse,  1  );
	_sntprintf(  tBuf,  sizeof(  tBuf  )/sizeof(  tBuf[0]  ),  _T(  "mouse.x:%d,mouse.y:%d\n"  ),  mouse.x,  mouse.y  );
	OutputDebugString(  tBuf  );
	
	RECT  rc;
	GetClientRect(  hWnd,  &rc  );

	if  (  mouse.x  >  rc.left  &&  mouse.x  <  rc.right  &&  mouse.y  >  rc.top  &&  mouse.y  <  rc.bottom  ){

		//  color  =  GetPixel(  hdcMemDC,  mouse.x,  mouse.y  );
		color  =  GetPixel(  hdcWindow,  mouse.x,  mouse.y  );
		_sntprintf(  tBuf,  sizeof(  tBuf  ) /  sizeof(  tBuf[0]  ),  _T(  "color:%x\n"  ),  color  );
		OutputDebugString(  tBuf  );
	
		}
	else  {
		  goto  errLabel;
	}


	iErr  =  0;

errLabel:

	if  (  hdcWindow  )  {
		ReleaseDC(hWnd,hdcWindow);
	}

	if  (  !iErr  )  {
		if  (  pColor  )  *pColor  =  color;
	}

    return iErr;

}


BOOL CDlgChromaKeyCfg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	

	switch  (  pMsg->message  )  {
			case  WM_LBUTTONDOWN:
				  OutputDebugString(  _T(  "lbtnDown\n"  )  );
				  if  (  m_var.bPickColor  )  {
					  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
					  if  (  !pFuncs  )  break;

					  ReleaseCapture(  );
					  m_var.bPickColor  =  FALSE;
					  
					  OutputDebugString(  _T(  "ReleaseCapture\n"  )  );

					  CWnd  *  pCtrl;
					  pCtrl  =  GetDlgItem(  IDC_CHECK_pick  );
					  (  (  CButton  *  )pCtrl  )->SetCheck(  m_var.bPickColor  ?  BST_CHECKED  :  BST_UNCHECKED  );

					  //
					  COLORREF	color;
					  HWND  hCtrl  =  ::GetDlgItem(  m_var.hWnd_img,  m_var.idc_img  );
					  //  if  (  !pickColor(  hCtrl,  &color  )  )  
					  if  (  !dlgImg_pickColor(  m_var.hWnd_img  )  )  {

						  color  =  m_var.color_org;

						  TCHAR  tBuf[1024]  =  _T(  ""  );
						  int r,g,b,tola,tolb;
						  float  fTa= 0,  fDistance=0;

						  r  =  GetRValue(  color  );
						  g  =  GetGValue(  color  );
						  b  =  GetBValue(  color  );
						  tola  =  CONST_key_tola;
						  tolb  =  CONST_key_tolb;
						  //
#ifdef  __DEBUG__						  
						  traceLog(  _T(  "key:r,g,b %d,%d,%d"  ),  (  int  )r,  (  int  )g,  (  int  )b  );
						  //  traceLog(  _T(  "cfgKey[0]:r,g,b %d,%d,%d"  ),  (  int  )m_var.cfg.keyCfgs[0].r_key,  (  int  )m_var.cfg.keyCfgs[0].g_key,  (  int  )m_var.cfg.keyCfgs[0].b_key  );
#endif
						  
						  if (  pFuncs->imgProcess.pf_addColorKey(  r,  g,  b,  tola,  tolb,  FALSE,  &m_var.cfg  )  ) break;
						  pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
						  dlgImg_testKeying(  m_var.hWnd_img  );
						  dlgImg_xyColor( m_var.hWnd_img,  m_var.x,  m_var.y  );
						  
						  m_var.usKeyIndex  =  m_var.cfg.usCnt -  1;

						  if  (  memcmp(  &m_var.curKey,  &m_var.cfg.keys[m_var.usKeyIndex],  sizeof(  m_var.curKey )  )  )  {
							  memcpy(  &m_var.curKey,  &m_var.cfg.keys[m_var.usKeyIndex],  sizeof(  m_var.curKey )  );
						  }
						
						  SetDlgItemInt(  IDC_EDIT_key_r,  toByte_rgb(  m_var.curKey.rgb_key.r  )  );
						  SetDlgItemInt(  IDC_EDIT_key_g,  toByte_rgb(  m_var.curKey.rgb_key.g  )  );
						  SetDlgItemInt(  IDC_EDIT_key_b,  toByte_rgb(  m_var.curKey.rgb_key.b  )  );
#ifdef  __USE_hsl_chromaKey__
						  SetDlgItemInt(  IDC_STATIC_key_h,  toByte_hsl(  m_var.curKey.hsl_key.x  )  );
						  SetDlgItemInt(  IDC_STATIC_key_s,  toByte_hsl(  m_var.curKey.hsl_key.y  )  );
						  SetDlgItemInt(  IDC_STATIC_key_l,  toByte_hsl(  m_var.curKey.hsl_key.z  )  );
#else
#if  0
						  SetDlgItemInt(  IDC_STATIC_key_y,  m_var.curKey.ucY_key  );
						  SetDlgItemInt(  IDC_STATIC_key_cb,  m_var.curKey.ucCb_key  );
						  SetDlgItemInt(  IDC_STATIC_key_cr,  m_var.curKey.ucCr_key  );
#endif

#endif
						  //
#if  0
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f" ),  m_var.curKey.tola100x  /  100.  );
						  SetDlgItemText(  IDC_EDIT_key_tola,  tBuf  );
						  fDistance  =  (  m_var.curKey.tolb100x  -  m_var.curKey.tola100x  )  /  100.;
						  if  (  fDistance <= 0  )  fDistance =  1.0;
						  if  (  fDistance > 199.0  )  fDistance  =  199.0;
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.2f" ),  fDistance  );
						  SetDlgItemText(  IDC_EDIT_key_distance,  tBuf  );
#else
						  m_slider_key_tola.SetPos( m_var.curKey.tola  );
						  SetDlgItemInt(  IDC_STATIC_key_tola_val, m_var.curKey.tola );
						  m_slider_key_tolb.SetPos( m_var.curKey.tolb  );
						  SetDlgItemInt(  IDC_STATIC_key_tolb_val, m_var.curKey.tolb );
#endif				  
						  int  iRet  =  refreshListBox(  m_hWnd,  IDC_LIST_chromaKey,  &m_var.cfg,  m_var.usKeyIndex  );
					  }          
				  



          
				  }
				  break;
			default:
					break;
	}

    

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDlgChromaKeyCfg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	int  i;
	for  (  i  =  0;  i  <  mycountof(  m_var.hBmp_btns  );  i  ++  )  {
		 if  (  m_var.hBmp_btns[i]  )  DeleteObject(  m_var.hBmp_btns[i]  );
	}

}

 int  deleteCfgOfChromaKey(  unsigned short usCnt  )
{
	int					iErr			=	-1;
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	if  (  !pQyMc  )  goto  errLabel;

	QY_REG		reg;
	TCHAR	*	pRegVal  =  NULL;
	TCHAR		tRegBuf[256]  =  _T(  ""  );

	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	_sntprintf(  reg.rootKey,  sizeof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	

	//  2013/10/03
	pRegVal  =  CONST_regValName_keyCfg_usCnt;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_keyCfg_bUseKey;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_keyCfg_minRgb;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_keyCfg_minS;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_keyCfg_minL;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_keyCfg_maxL;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
#if 0
	pRegVal  =  CONST_regValName_keyCfg_bStartSmooth;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_keyCfg_bEdgeColor;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_keyCfg_r_f;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_keyCfg_r_rgb;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
#endif
	if  (  !usCnt  )  {  iErr  =  0;  goto  errLabel;  }

	int  i;

	_sntprintf(  tRegBuf,  mycountof(  tRegBuf  ),  _T(  "%s"  ),  reg.rootKey  );

	for ( i = 0; i < usCnt;  i++  )  {
		_sntprintf(  reg.rootKey,  sizeof(  reg.rootKey  ),  _T(  "%s\\key%d"  ),  tRegBuf,  i  );

	   if  (  ERROR_SUCCESS  !=  RegDeleteKey(  reg.hKeyRoot0,  reg.rootKey  )  )  iErr  =  -1;
	   else  iErr  =  0;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}

void CDlgChromaKeyCfg::OnBnClickedButtonrestoredefaultsettings()
{
	QY_MC* pQyMc = g_pQyMc;

	// TODO: Add your control notification handler code here
	deleteCfgOfChromaKey(  m_var.cfg.usCnt  );
	getImgProcessCfg(  pQyMc,  &m_var.cfg  );
	this->bShowPolicy(  );

	return;
}

void CDlgChromaKeyCfg::OnNMCustomdrawSliderpreblur(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto errLabel;;


	float  f  =  m_slider_preBlur.GetPos( )  /  20.;
	if  (  f !=  m_var.cfg.fSigma_preBlur  )  {
		m_var.cfg.fSigma_preBlur  =  f;

		TCHAR  tBuf[32];
		_sntprintf(  tBuf, mycountof( tBuf ), _T( "%.2f"  ),  f  );
		SetDlgItemText(  IDC_STATIC_preBlur_val,  tBuf  );

		//
		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
		dlgImg_testKeying(  m_var.hWnd_img  );

		dlgImg_xyColor( m_var.hWnd_img,  m_var.x,  m_var.y  );
	}

#ifdef  __DEBUG__
		traceLog(  _T(  "preBlur: fSigma %f"  ),  m_var.cfg.fSigma_preBlur  );
#endif

errLabel:

	*pResult = 0;
}

void CDlgChromaKeyCfg::OnNMCustomdrawSliderpostblur(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto errLabel;;


	float  f  =  m_slider_postBlur.GetPos( )  /  20.;
	if  (  f !=  m_var.cfg.fSigma_postBlur  )  {
		m_var.cfg.fSigma_postBlur  =  f;

		TCHAR  tBuf[32];
		_sntprintf(  tBuf, mycountof( tBuf ), _T( "%.2f"  ),  f  );
		SetDlgItemText(  IDC_STATIC_postBlur_val,  tBuf  );

		//
		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
		dlgImg_testKeying(  m_var.hWnd_img  );

		dlgImg_xyColor( m_var.hWnd_img,  m_var.x,  m_var.y  );
	}

#ifdef  __DEBUG__
		traceLog(  _T(  "postBlur: fSigma %f"  ),  m_var.cfg.fSigma_postBlur  );
#endif

errLabel:

	*pResult = 0;
}

void CDlgChromaKeyCfg::OnNMCustomdrawSliderkeytola(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto errLabel;;

	int  t  =  m_slider_key_tola.GetPos( );
	if  (  t !=  m_var.curKey.tola  )  {
		m_var.curKey.tola  =  t;
		SetDlgItemInt(  IDC_STATIC_key_tola_val,  t );
		
		if ( m_var.curKey.tola >= m_var.curKey.tolb  &&  m_var.curKey.tolb  &&  m_var.curKey.tola  )  {
			m_var.curKey.tolb  =  m_var.curKey.tola + 1;
			m_slider_key_tolb.SetPos( m_var.curKey.tolb );
			SetDlgItemInt(  IDC_STATIC_key_tolb_val,  m_var.curKey.tolb );
		}

		//
		if  (  m_var.cfg.usCnt  &&  m_var.usKeyIndex  >=  0  &&  m_var.usKeyIndex  <  m_var.cfg.usCnt  )  
		{
			memcpy(  &m_var.cfg.keys[m_var.usKeyIndex],  &m_var.curKey,  sizeof(  m_var.cfg.keys[m_var.usKeyIndex]  )  );
		}
		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
		dlgImg_testKeying(  m_var.hWnd_img  );

		dlgImg_xyColor( m_var.hWnd_img,  m_var.x,  m_var.y  );

	}
#ifdef  __DEBUG__
	    traceLog(  _T(  "tola:  %d"  ),  m_var.curKey.tola );
#endif
errLabel:

	*pResult = 0;
}

void CDlgChromaKeyCfg::OnNMCustomdrawSliderkeytolb(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here

	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto errLabel;;

	int  t  =  m_slider_key_tolb.GetPos( );
	if  (  t !=  m_var.curKey.tolb  )  {
		m_var.curKey.tolb  =  t;
		SetDlgItemInt(  IDC_STATIC_key_tolb_val,  t );

		if ( m_var.curKey.tolb <= m_var.curKey.tola  &&  m_var.curKey.tolb  &&  m_var.curKey.tola )  {
			m_var.curKey.tola  =  ( m_var.curKey.tolb - 1 );
			m_slider_key_tola.SetPos( m_var.curKey.tola );
			SetDlgItemInt(  IDC_STATIC_key_tola_val,  m_var.curKey.tola );
		}
		//
		//
		if  (  m_var.cfg.usCnt  &&  m_var.usKeyIndex  >=  0  &&  m_var.usKeyIndex  <  m_var.cfg.usCnt  )  
		{
			memcpy(  &m_var.cfg.keys[m_var.usKeyIndex],  &m_var.curKey,  sizeof(  m_var.cfg.keys[m_var.usKeyIndex]  )  );
		}
		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
		dlgImg_testKeying(  m_var.hWnd_img  );
		dlgImg_xyColor( m_var.hWnd_img,  m_var.x,  m_var.y  );
	}
#ifdef  __DEBUG__
	    traceLog(  _T(  "tolb:  %d"  ),  m_var.curKey.tolb );
#endif

errLabel:

	*pResult = 0;
}

void CDlgChromaKeyCfg::OnNMCustomdrawSlidergamma(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here

	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto errLabel;;

	float  f  =  m_slider_gamma.GetPos( )  /  20.;
	if  (  f !=  m_var.cfg.fGamma  )  {
		m_var.cfg.fGamma  =  f;

		TCHAR  tBuf[32];
		_sntprintf(  tBuf, mycountof( tBuf ), _T( "%.2f"  ),  f  );
		SetDlgItemText(  IDC_STATIC_gamma_val,  tBuf  );

		//
		pFuncs->imgProcess.pf_refreshCurImgProcessCfg(  &m_var.cfg  );
		dlgImg_testKeying(  m_var.hWnd_img  );
		
		dlgImg_xyColor( m_var.hWnd_img,  m_var.x,  m_var.y  );
	}

#ifdef  __DEBUG__
	    traceLog(  _T(  "gamma:  %f"  ),  m_var.cfg.fGamma  );
#endif

errLabel:

	*pResult = 0;
}
