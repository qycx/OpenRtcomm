// DlgSelectAvDev.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"

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

#include	"DlgSelectAvDev.h"

//  #include	"DlgShareDynBmps.h"

#include	"qyOpenShellCommon.h"
#include	"dlgTalkProc.h"
#include	"qmcCmdProc.h"

//  #include	"DlgProgress.h"
#include	"tmpCeLib.h"
#include	"funcsForIsCliHelp.h"
#include	"isCliHelpPublic.h"

//  __declspec(  dllexport  )  int  showDlgSelectAvDev(  HWND  hParent,  void  *  pCapStuff,  int  iMenuId_selected  )
__declspec(  dllexport  )  int  showDlgSelectAvDev(  HWND  hParent,  void  *  pCapStuff,  int  iMenuId_selected,  BOOL  *  pbUnresizable  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int	iRet	=	-1;
	CDlgSelectAvDev	dlg(  CWnd::FromHandle(  hParent  )  );
	
	dlg.m_var.pCapStuff  =  pCapStuff;	
	dlg.m_var.iMenuId_selected  =  iMenuId_selected;
	if  (  pbUnresizable  )  {
		dlg.m_var.bUnresizable  =  *pbUnresizable;
		}
	else  {
		  dlg.m_var.bHide_idcCheck_unresizable  =  TRUE;
	}
	//
	if (dlg.DoModal() != IDOK) {
		goto  errLabel;
	}
	if  (  pbUnresizable  )  {
		*pbUnresizable  =  dlg.m_var.bUnresizable;		
	}

	iRet  =  IDOK;
errLabel:
	return  iRet;
}

// CDlgSelectAvDev dialog

IMPLEMENT_DYNAMIC(CDlgSelectAvDev, CDialog)

CDlgSelectAvDev::CDlgSelectAvDev(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectAvDev::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgSelectAvDev::~CDlgSelectAvDev()
{
}

void CDlgSelectAvDev::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSelectAvDev, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgSelectAvDev::OnBnClickedOk)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_aDev, &CDlgSelectAvDev::OnCbnSelchangeComboadev)
	ON_CBN_SELCHANGE(IDC_COMBO_vDev, &CDlgSelectAvDev::OnCbnSelchangeCombovdev)
	ON_BN_CLICKED(IDC_BUTTON_cfgCaptureFilter_v, &CDlgSelectAvDev::OnBnClickedButtoncfgcapturefilterv)
	ON_BN_CLICKED(IDC_BUTTON_cfgCapturePin_v, &CDlgSelectAvDev::OnBnClickedButtoncfgcapturepinv)
	ON_BN_CLICKED(IDC_BUTTON_cfgCrossBar_v, &CDlgSelectAvDev::OnBnClickedButtoncfgcrossbarv)
END_MESSAGE_MAP()


// CDlgSelectAvDev message handlers

void CDlgSelectAvDev::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int  idc  =  IDC_CHECK_ucbUnresizable;
	m_var.bUnresizable  =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  ?  1  :  0;
	
	OnOK();
}

BOOL CDlgSelectAvDev::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int		iErr	=	-1;
	QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;
	FUNCS_for_isCliHelp	*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  !m_var.pCapStuff  )  goto  errLabel;

    int  i;
	CAP_STUFF  *  pCapStuff  =  (  CAP_STUFF  *  )m_var.pCapStuff;
	int				idc;
	TCHAR			tBuf[128];
	TCHAR			tName[MAX_monikerDisplayNameLen  +  1];

	idc  =  IDC_COMBO_aDev;
	(  (  CComboBox  *  )GetDlgItem(  idc  )  )->InsertString(  -1,  _T(  ""  )  );
	for  (  i  =  0;  i  <  mycountof(  pCapStuff->rgpmAudioMenu  );  i  ++  )  {
		 if  (  !pCapStuff->rgpmAudioMenu[i]  )  continue;
		 tName[0]  =  0;
		 //  getMonikerFriendlyName(  pCapStuff->rgpmAudioMenu[i],  tName,  mycountof(  tName  )  );
		 pFuncs->moniker.pf_getMonikerProp(  pCapStuff->rgpmAudioMenu[i],  CONST_moniker_FriendlyName,  tName,  mycountof(  tName  )  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d: %s"  ),  i  +  1,  tName  );
		 (  (  CComboBox  *  )GetDlgItem(  idc  )  )->InsertString(  -1,  tBuf  );
	}

	idc  =  IDC_COMBO_vDev;
	(  (  CComboBox  *  )GetDlgItem(  idc  )  )->InsertString(  -1,  _T(  ""  )  );
	for  (  i  =  0;  i  <  mycountof(  pCapStuff->rgpmVideoMenu  );  i  ++  )  {
		 if  (  !pCapStuff->rgpmVideoMenu[i]  )  continue;
		 tName[0]  =  0;
		 //  getMonikerFriendlyName(  pCapStuff->rgpmVideoMenu[i],  tName,  mycountof(  tName  )  );
		 pFuncs->moniker.pf_getMonikerProp(  pCapStuff->rgpmVideoMenu[i],  CONST_moniker_FriendlyName,  tName,  mycountof(  tName  )  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d: %s"  ),  i  +  1,  tName  );
		 (  (  CComboBox  *  )GetDlgItem(  idc  )  )->InsertString(  -1,  tBuf  );
	}

	//
	if  (  m_var.iMenuId_selected  )  {
		i  =  m_var.iMenuId_selected  -  ID_MENU_VDEVICE0;
		if  (  i  >=  0  &&  i  <  mycountof(  pCapStuff->rgpmVideoMenu  )  )  {
			(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SetCurSel(  i  +  1  );
			//
		}
		this->OnCbnSelchangeCombovdev(  );
		//
		(  (  CComboBox  *  )GetDlgItem(  idc  )  )->EnableWindow(  FALSE  );
	}

	//  2015/10/22
	SetDlgItemText(  IDC_CHECK_ucbUnresizable,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unresizable  )  );    //  2015/10/24,  _T(  "Unresizable"  )  );
	if  (  m_var.bHide_idcCheck_unresizable  )  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_CHECK_ucbUnresizable  ),  SW_HIDE  );

	//
	iErr  =  0;

errLabel:

#if  0
	if (iErr) {
		//PostMessage(WM_CLOSE, 0, 0);
	}
#endif

	//
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSelectAvDev::OnDestroy()
{

	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

void CDlgSelectAvDev::OnCbnSelchangeComboadev()
{
	// TODO: Add your control notification handler code here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp	*	pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	int		idc;
	TCHAR	tBuf[256];
	int		index;
	CAP_STUFF  *  pCapStuff  =  (  CAP_STUFF  *  )m_var.pCapStuff;

	idc  =  IDC_COMBO_aDev;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );
	if  (  tBuf[0]  )  {
		index  =  _ttol(  tBuf  )  -  1;
		//  ChooseDevices(  *pCapStuff,  pCapStuff->pmVideo,  pCapStuff->rgpmAudioMenu[index]  );
		pFuncs->pf_myChooseDevices(  pCapStuff,  pCapStuff->pmVideo,  pCapStuff->rgpmAudioMenu[index]  );
	}
	else  {
		  //  ChooseDevices(  *pCapStuff,  pCapStuff->pmVideo,  NULL  );
		  pFuncs->pf_myChooseDevices(  pCapStuff,  pCapStuff->pmVideo,  NULL  );
	}

}

void CDlgSelectAvDev::OnCbnSelchangeCombovdev()
{
	// TODO: Add your control notification handler code here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp	*	pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	int		idc;
	TCHAR	tBuf[256];
	int		index;
	CAP_STUFF  *  pCapStuff  =  (  CAP_STUFF  *  )m_var.pCapStuff;

	idc  =  IDC_COMBO_vDev;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );
	if  (  tBuf[0]  )  {
		index  =  _ttol(  tBuf  )  -  1;
		//  ChooseDevices(  *pCapStuff,  pCapStuff->rgpmVideoMenu[index],  pCapStuff->pmAudio  );
		pFuncs->pf_myChooseDevices(  pCapStuff,  pCapStuff->rgpmVideoMenu[index],  pCapStuff->pmAudio  );
	}
	else  {
		  //  ChooseDevices(  *pCapStuff,  NULL,  pCapStuff->pmAudio  );
		  pFuncs->pf_myChooseDevices(  pCapStuff,  NULL,  pCapStuff->pmAudio  );
	}

}

void CDlgSelectAvDev::OnBnClickedButtoncfgcapturefilterv()
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	// TODO: Add your control notification handler code here
	pFuncs->pf_cfgCaptureFilter(  m_var.pCapStuff,  this->m_hWnd  );
}

void CDlgSelectAvDev::OnBnClickedButtoncfgcapturepinv()
{
	// TODO: Add your control notification handler code here
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	pFuncs->pf_cfgCapturePin(  m_var.pCapStuff,  this->m_hWnd  );
}

void CDlgSelectAvDev::OnBnClickedButtoncfgcrossbarv()
{
	// TODO: Add your control notification handler code here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	pFuncs->pf_cfgCrossBar(  m_var.pCapStuff,  this->m_hWnd  );
}
