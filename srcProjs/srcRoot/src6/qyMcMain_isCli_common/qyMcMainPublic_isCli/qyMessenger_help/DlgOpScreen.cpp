// DlgOpScreen.cpp : implementation file
//

#include "stdafx.h"

#include	"qyMcMainCommon.h"

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

#include	"qmcDmoPublic.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif
#include	"myfourcc.h"

#include	"qyCusResTemp.h"

//  #include	"qyMc.h"
#include	"qyGuiCommProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecordPublic.h"



#include	"myresource.h"

#include "DlgOpScreen.h"
#include "afxdialogex.h"


//
#include	"wallTalkers.h"
#include	"dlgShareDynBmpsProc.h"



//
__declspec(  dllexport  )  int  showDlgOpScreen(  HWND  hParent,  HWND  hDlg_shareDynBmps,  int  index_obj_selected  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int	iRet	=	-1;
	CDlgOpScreen	dlg(  CWnd::FromHandle(  hParent  )  );
	
	//
	dlg.m_var.hDlg_shareDynBmps  =  hDlg_shareDynBmps;
	//dlg.m_var.pCapStuff  =  pCapStuff;
	dlg.m_var.index_obj_selected  =  index_obj_selected;
	//
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;
errLabel:
	return  iRet;
}


// CDlgOpScreen dialog

IMPLEMENT_DYNAMIC(CDlgOpScreen, CDialogEx)

CDlgOpScreen::CDlgOpScreen(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgOpScreen::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

}

CDlgOpScreen::~CDlgOpScreen()
{
}

//
int  CDlgOpScreen::refreshCtrlStatus(  )
{
	int  idc;
	BOOL  bEnable  =  TRUE;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	TCHAR  tBuf[256];

	//
	if  (  dlgShareDynBmps_bShared(  m_var.hDlg_shareDynBmps,  CONST_objType_screen,  m_var.index_obj_selected  )  )  {
		bEnable  =  FALSE;
	}


	//
	idc  =  IDC_BUTTON_toShare;
	if  (  bEnable  )  {
		//
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_startSharing  )  );
	}
	else  {
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_stopSharing  )  );
	}
	//
	::SetDlgItemText(  m_hWnd,  idc,  tBuf  );
				

	//
	return  0;
}


//
void CDlgOpScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgOpScreen, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_toShare, &CDlgOpScreen::OnBnClickedButtontoshare)
	ON_BN_CLICKED(IDCANCEL, &CDlgOpScreen::OnBnClickedCancel)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgOpScreen message handlers


void CDlgOpScreen::OnBnClickedButtontoshare()
{
	// TODO: Add your control notification handler code here
		MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	int  idc;
	TCHAR  tBuf[256];

	//
	int				uiCapType	=	CONST_capType_av;
	int				uiSubCapType	=	CONST_subCapType_webcam;


	QY_REG			reg;
	memset(  &reg,  0,  sizeof(  reg  )  );

	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//  _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	getRegRootKey_qmc(  uiCapType,  uiSubCapType,  0,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  _T(  CONST_regKeyName_screen  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%d"  ),  reg.rootKey,  m_var.index_obj_selected  );

	//
	TCHAR  tName[128];

	//
		//
	idc  =  IDC_EDIT_name;
	GetDlgItemText(  idc,  tName,  mycountof(  tName  )  );
	tTrim(  tName  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_name,  tName  );  
	

	

	//
	idc  =  IDC_CHECK_autoOpenOnStartup;
	BOOL  bVal    =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  ?  1  :  0;
	if  (  bVal  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbAutoOpenOnStartup,  _T(  "1"  )  );  
		
		}
	else  {
		qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbAutoOpenOnStartup  );
	}




	//
	dlgShareDynBmps_toShareScreen_func(  m_var.hDlg_shareDynBmps,  m_var.index_obj_selected  -  1  );

	//
	refreshCtrlStatus();
}


void CDlgOpScreen::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


BOOL CDlgOpScreen::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//
	TCHAR  tBuf[256];
	QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//
		//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %d"  ),  getResStr( 0, &pQyMc->cusRes,  CONST_resId_opScreen  ),  m_var.index_obj_selected  );
	SetWindowText(  tBuf  );
	SetWindowText(  tBuf  );
	
	WEBCAM_info  webcamInfo;
	getWebcamInfo(  CONST_objType_screen,  m_var.index_obj_selected,  &webcamInfo  );


	//	
	//
	SetDlgItemText(  IDC_EDIT_name,  webcamInfo.cusName  );

	int  idc;

	idc  =  IDC_CHECK_autoOpenOnStartup;
	if  (  webcamInfo.ucbAutoOpenOnStartup  )  {
		 (  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  1  );
	}



	refreshCtrlStatus(  );

	//
	SetTimer( 1,  1000,  NULL  );


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgOpScreen::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	refreshCtrlStatus(  );


	CDialogEx::OnTimer(nIDEvent);
}
