// DlgOpAvDev.cpp : implementation file
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

#include "DlgOpAvDev.h"
#include "afxdialogex.h"

#include	"qyOpenShellCommon.h"
#include	"dlgTalkProc.h"
#include	"qmcCmdProc.h"

//  #include	"DlgProgress.h"
#include	"tmpCeLib.h"
#include	"funcsForIsCliHelp.h"
#include	"isCliHelpPublic.h"

#include	"wallTalkers.h"
#include	"dlgShareDynBmpsProc.h"

//
int  getWebcamInfo(  unsigned  int  uiObjType,  int  index_obj,  WEBCAM_info  *  pWebcamInfo  )
{
	int  iErr  =  -1;
	//
	int				uiCapType	=	CONST_capType_av;
	int				uiSubCapType	=	CONST_subCapType_webcam;


	QY_REG			reg;
	memset(  &reg,  0,  sizeof(  reg  )  );

	//
	TCHAR  *  pRegKeyName  =  NULL;

	switch  (  uiObjType  )  {
			case  CONST_objType_webcam:
				  pRegKeyName  =  _T(  CONST_regKeyName_webcam  );
				  break;
			case  CONST_objType_screen:
				  pRegKeyName  =  _T(  CONST_regKeyName_screen  );
				  break;
			default:
					return  -1;
	}


	//
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//  _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	getRegRootKey_qmc(  uiCapType,  uiSubCapType,  0,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  pRegKeyName  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%d"  ),  reg.rootKey,  index_obj  );

	//
	memset(  pWebcamInfo,  0,  sizeof(  pWebcamInfo[0]  )  );


	//
	pWebcamInfo->index_obj  =  index_obj;

	//
	TCHAR  tName[256];

	//
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_aName,  (  char  *  )tName,  sizeof(  tName  ), NULL  )  )  tName[0]  =  0;
	tTrim(  tName  );
	safeTcsnCpy(  tName,  pWebcamInfo->aName,  mycountof(  pWebcamInfo->aName  )  );

	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_vName,  (  char  *  )tName,  sizeof(  tName  ), NULL  )  )  tName[0]  =  0;
	tTrim(  tName  );
	safeTcsnCpy(  tName,  pWebcamInfo->vName,  mycountof(  pWebcamInfo->vName  )  );

	//
	unsigned char  ucCmd;
	TCHAR			*	pRegVal				=	NULL;
	char				buf[256];

	//
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_name,  (  char  *  )tName,  sizeof(  tName  ), NULL  )  )  tName[0]  =  0;
	tTrim(  tName  );
	safeTcsnCpy(  tName,  pWebcamInfo->cusName,  mycountof(  pWebcamInfo->cusName  )  );


	//	
	ucCmd  =  FALSE;
	pRegVal  =  (  CONST_regValName_ucbUnresizable  );
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )buf,  sizeof(  buf  ),  0  )  &&  atol(  buf  )  )  ucCmd  =  TRUE;
	pWebcamInfo->ucbUnresizable  =  ucCmd;


	//	
	ucCmd  =  FALSE;
	pRegVal  =  (  CONST_regValName_ucbAutoOpenOnStartup  );
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )buf,  sizeof(  buf  ),  0  )  &&  atol(  buf  )  )  ucCmd  =  TRUE;
	pWebcamInfo->ucbAutoOpenOnStartup  =  ucCmd;

	//  2018/10/30
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )  {
		if  (  index_obj  ==  1  &&  uiObjType  ==  CONST_objType_webcam  )  {
			MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
			//
			if  (  !pWebcamInfo->vName[0]  )  {
				safeTcsnCpy(  pProcInfo->status.vName_1st_webcam,  pWebcamInfo->vName,  mycountof(  pWebcamInfo->vName  )  );
			}
		}
		if  (  index_obj  ==  1  )  {
			pWebcamInfo->ucbAutoOpenOnStartup  =  TRUE;
		}
	}
	if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hbwj  )  {
		if  (  index_obj  ==  1  &&  uiObjType  ==  CONST_objType_screen  )  {
			pWebcamInfo->ucbAutoOpenOnStartup  =  TRUE;
		}
	}


	iErr  =  0;
errLabel:


	return  iErr;
}



//
int  getIndex_moniker_byName(  CAP_STUFF	*	pCapStuff,  TCHAR  *  name,  BOOL  bAudio  )
{
	int  index  =  -1;
	CAP_STUFF  &gcap  =  *pCapStuff;
	int  i;
		MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;
	FUNCS_for_isCliHelp	*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;

			  
	TCHAR  tName[256];

	if  (  !bAudio  )  {

		for  (  i  =  0;  i  <  mycountof(  gcap.rgpmVideoMenu  );  i  ++  )  {			
			   if  (  !gcap.rgpmVideoMenu[i]  )  continue;
			   //
			   pFuncs->moniker.pf_getMonikerProp(  gcap.rgpmVideoMenu[i],  CONST_moniker_FriendlyName,  tName,  mycountof(  tName  )  );
			   //
			   tTrim(tName);
			   //
			   if  (  _tcsicmp(  tName,  name  )  )  continue;
			   //
			   break;		     
		  }
		  if  (  i  ==  mycountof(  gcap.rgpmVideoMenu  )  )  goto  errLabel;
		  
		  return  i;
	}

	//
	for  (  i  =  0;  i  <  mycountof(  gcap.rgpmAudioMenu  );  i  ++  )  {			
			   if  (  !gcap.rgpmAudioMenu[i]  )  continue;
			   //
			   pFuncs->moniker.pf_getMonikerProp(  gcap.rgpmAudioMenu[i],  CONST_moniker_FriendlyName,  tName,  mycountof(  tName  )  );
			   //
			   if  (  _tcsicmp(  tName,  name  )  )  continue;
			   //
			   break;		     

	}	
	if  (  i  ==  mycountof(  gcap.rgpmAudioMenu  )  )  goto  errLabel;
		
	return  i;

errLabel:
	return  -1;
}
		  


//
//  __declspec(  dllexport  )  int  showDlgSelectAvDev(  HWND  hParent,  void  *  pCapStuff,  int  iMenuId_selected  )
__declspec(  dllexport  )  int  showDlgOpAvDev(  HWND  hParent,  HWND  hDlg_shareDynBmps,  int  index_obj_selected,  BOOL  *  pbUnresizable  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int	iRet	=	-1;
	CDlgOpAvDev	dlg(  CWnd::FromHandle(  hParent  )  );
	
	//
	dlg.m_var.hDlg_shareDynBmps  =  hDlg_shareDynBmps;
	//dlg.m_var.pCapStuff  =  pCapStuff;
	dlg.m_var.index_obj_selected  =  index_obj_selected;
	if  (  pbUnresizable  )  {
		dlg.m_var.bUnresizable  =  *pbUnresizable;
		}
	else  {
		  dlg.m_var.bHide_idcCheck_unresizable  =  TRUE;
	}
	//
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
	if  (  pbUnresizable  )  {
		*pbUnresizable  =  dlg.m_var.bUnresizable;		
	}

	iRet  =  IDOK;
errLabel:
	return  iRet;
}



// CDlgOpAvDev dialog

IMPLEMENT_DYNAMIC(CDlgOpAvDev, CDialogEx)

CDlgOpAvDev::CDlgOpAvDev(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgOpAvDev::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgOpAvDev::~CDlgOpAvDev()
{
}


//
int  CDlgOpAvDev::refreshCtrlStatus(  )
{
	int  idc;
	BOOL  bEnable  =  TRUE;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
		
	//
	if  (  dlgShareDynBmps_bShared(  m_var.hDlg_shareDynBmps,  CONST_objType_webcam,  m_var.index_obj_selected  )  )  {
		bEnable  =  FALSE;
	}

	//		
	idc  =  IDC_COMBO_aDev;
	(  (  CComboBox  *  )GetDlgItem(  idc  )  )->EnableWindow(  bEnable  );				
	idc =  IDC_COMBO_vDev;					
	(  (  CComboBox  *  )GetDlgItem(  idc  )  )->EnableWindow(  bEnable  );
		
	//
	TCHAR  tBuf[128];
	
	//
	TCHAR  vName[256];
	idc  =  IDC_COMBO_vDev;
	GetDlgItemText(  idc,  vName,  mycountof(  vName  )  );

	//
	idc  =  IDC_BUTTON_toShare;
	if  (  bEnable  )  {
		//
		if  (  vName[0]  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_startSharing  )  );
			}
		else  {
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_save  )  );
			
		}
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
void CDlgOpAvDev::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgOpAvDev, CDialogEx)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_aDev, &CDlgOpAvDev::OnCbnSelchangeComboadev)
	ON_CBN_SELCHANGE(IDC_COMBO_vDev, &CDlgOpAvDev::OnCbnSelchangeCombovdev)
	ON_BN_CLICKED(IDC_BUTTON_cfgCaptureFilter_v, &CDlgOpAvDev::OnBnClickedButtoncfgcapturefilterv)
	ON_BN_CLICKED(IDC_BUTTON_cfgCapturePin_v, &CDlgOpAvDev::OnBnClickedButtoncfgcapturepinv)
	ON_BN_CLICKED(IDC_BUTTON_cfgCrossBar_v, &CDlgOpAvDev::OnBnClickedButtoncfgcrossbarv)
	ON_BN_CLICKED(IDC_BUTTON_toShare, &CDlgOpAvDev::OnBnClickedButtontoshare)
	ON_BN_CLICKED(IDC_CHECK_ucbUnresizable, &CDlgOpAvDev::OnBnClickedCheckucbunresizable)
	ON_BN_CLICKED(IDC_CHECK_autoOpenOnStartup, &CDlgOpAvDev::OnBnClickedCheckautoopenonstartup)
	ON_BN_CLICKED(IDCANCEL, &CDlgOpAvDev::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgOpAvDev message handlers





//
BOOL CDlgOpAvDev::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
		int		iErr	=	-1;
	QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;
	FUNCS_for_isCliHelp	*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	 //
	 CAP_STUFF	*	pCapStuff				=	NULL;


	 //
	 pCapStuff  =  (  CAP_STUFF  *  )pFuncs->pf_CAP_STUFF_new(  );
	if  (  !pCapStuff  )  goto  errLabel;
	pFuncs->moniker.pf_addDevicesToMenu(  pCapStuff,  TRUE,  NULL  );

	//
	m_var.pCapStuff  =  pCapStuff;

	//
	if  (  !m_var.pCapStuff  )  goto  errLabel;

    int  i;
	//CAP_STUFF  *  pCapStuff  =  (  CAP_STUFF  *  )m_var.pCapStuff;
	int				idc;
	TCHAR			tBuf[128];
	TCHAR			tName[MAX_monikerDisplayNameLen  +  1];

	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %d"  ),  getResStr( 0, &pQyMc->cusRes,  CONST_resId_opAvDev  ),  m_var.index_obj_selected  );
	SetWindowText(  tBuf  );
	
	WEBCAM_info  webcamInfo;
	getWebcamInfo(  CONST_objType_webcam,  m_var.index_obj_selected,  &webcamInfo  );

	//
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
	//
	if  (  m_var.index_obj_selected  )  {
		
		if  (  webcamInfo.aName[0]  )  {
			int  index_a  =  -1;
			index_a  =  getIndex_moniker_byName(  pCapStuff,  webcamInfo.aName,  TRUE  );

			if  (  index_a  >=  0  &&  index_a  <  mycountof(  pCapStuff->rgpmAudioMenu  )  )  {	
				(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SetCurSel(  index_a  +  1  );	
			}

			this->OnCbnSelchangeComboadev(  );		
		}
	}
	
	//
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
	if  (  m_var.index_obj_selected  )  {
		//
		
		if  (  webcamInfo.vName[0]  )  {
			int  index_v  =  -1;
			index_v  =  getIndex_moniker_byName(  pCapStuff,  webcamInfo.vName,  FALSE  );

			if  (  index_v  >=  0  &&  index_v  <  mycountof(  pCapStuff->rgpmVideoMenu  )  )  {	
				(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SetCurSel(  index_v  +  1  );	
			}

			this->OnCbnSelchangeCombovdev(  );
		}
	}


	//
	SetDlgItemText(  IDC_EDIT_name,  webcamInfo.cusName  );

	//
	idc  =  IDC_CHECK_ucbUnresizable;
	if  (  webcamInfo.ucbUnresizable  )  {
		 (  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  1  );
	}
	idc  =  IDC_CHECK_autoOpenOnStartup;
	if  (  webcamInfo.ucbAutoOpenOnStartup  )  {
		 (  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  1  );
	}

	//
	refreshCtrlStatus(  );


	

	//  2015/10/22
	//  SetDlgItemText(  IDC_CHECK_ucbUnresizable,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unresizable  )  );    //  2015/10/24,  _T(  "Unresizable"  )  );
	if  (  m_var.bHide_idcCheck_unresizable  )  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_CHECK_ucbUnresizable  ),  SW_HIDE  );

	//
	iErr  =  0;

errLabel:

	if  (  iErr  )  PostMessage(  WM_CLOSE,  0,  0  );




	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgOpAvDev::OnDestroy()
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp	*	pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	//
	if  (  m_var.pCapStuff  )  pFuncs->pf_CAP_STUFF_free(  m_var.pCapStuff  );


	//
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


void CDlgOpAvDev::OnCbnSelchangeComboadev()
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


void CDlgOpAvDev::OnCbnSelchangeCombovdev()
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

	//
	refreshCtrlStatus(  );
}


void CDlgOpAvDev::OnBnClickedButtoncfgcapturefilterv()
{
	// TODO: Add your control notification handler code here
		MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	// TODO: Add your control notification handler code here
	pFuncs->pf_cfgCaptureFilter(  m_var.pCapStuff,  this->m_hWnd  );

}


void CDlgOpAvDev::OnBnClickedButtoncfgcapturepinv()
{
	// TODO: Add your control notification handler code here
		MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	pFuncs->pf_cfgCapturePin(  m_var.pCapStuff,  this->m_hWnd  );

}


void CDlgOpAvDev::OnBnClickedButtoncfgcrossbarv()
{
	// TODO: Add your control notification handler code here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	pFuncs->pf_cfgCrossBar(  m_var.pCapStuff,  this->m_hWnd  );

}




void CDlgOpAvDev::OnBnClickedButtontoshare()
{
	// TODO: Add your control notification handler code here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	int  idc;
	TCHAR  tBuf[256];
	int  index_a;
	CAP_STUFF  *  pCapStuff  =  (  CAP_STUFF  *  )m_var.pCapStuff;

	//
	int				uiCapType	=	CONST_capType_av;
	int				uiSubCapType	=	CONST_subCapType_webcam;


	QY_REG			reg;
	memset(  &reg,  0,  sizeof(  reg  )  );

	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//  _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	getRegRootKey_qmc(  uiCapType,  uiSubCapType,  0,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  _T(  CONST_regKeyName_webcam  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%d"  ),  reg.rootKey,  m_var.index_obj_selected  );

	//
	TCHAR  tName[128];



	//
	idc  =  IDC_COMBO_aDev;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );
	if  (  tBuf[0]  )  {
		index_a  =  _ttol(  tBuf  )  -  1;
		//  ChooseDevices(  *pCapStuff,  pCapStuff->pmVideo,  pCapStuff->rgpmAudioMenu[index]  );
		pFuncs->pf_myChooseDevices(  pCapStuff,  pCapStuff->pmVideo,  pCapStuff->rgpmAudioMenu[index_a]  );
		
		//
		tName[0]  =  0;
		 //  getMonikerFriendlyName(  pCapStuff->rgpmAudioMenu[i],  tName,  mycountof(  tName  )  );
		 pFuncs->moniker.pf_getMonikerProp(  pCapStuff->rgpmAudioMenu[index_a],  CONST_moniker_FriendlyName,  tName,  mycountof(  tName  )  );

		 //
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_aName,  tName  );  

	}
	else  {
		  //  ChooseDevices(  *pCapStuff,  pCapStuff->pmVideo,  NULL  );
		  pFuncs->pf_myChooseDevices(  pCapStuff,  pCapStuff->pmVideo,  NULL  );

		  //
		  qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_aName  );
	}

	//
	int  index_v  =  0;
	int  iMenuId_v  =  0;

	//
	idc  =  IDC_COMBO_vDev;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );
	if  (  tBuf[0]  )  {
		index_v  =  _ttol(  tBuf  )  -  1;
		//  ChooseDevices(  *pCapStuff,  pCapStuff->rgpmVideoMenu[index],  pCapStuff->pmAudio  );
		pFuncs->pf_myChooseDevices(  pCapStuff,  pCapStuff->rgpmVideoMenu[index_v],  pCapStuff->pmAudio  );

		//
		tName[0]  =  0;
		 //  getMonikerFriendlyName(  pCapStuff->rgpmAudioMenu[i],  tName,  mycountof(  tName  )  );
		 pFuncs->moniker.pf_getMonikerProp(  pCapStuff->rgpmVideoMenu[index_v],  CONST_moniker_FriendlyName,  tName,  mycountof(  tName  )  );

		 //
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_vName,  tName  );  

		 //
		 iMenuId_v  =  index_v  +  ID_MENU_VDEVICE0;


	}
	else  {
		  //  ChooseDevices(  *pCapStuff,  NULL,  pCapStuff->pmAudio  );
		  pFuncs->pf_myChooseDevices(  pCapStuff,  NULL,  pCapStuff->pmAudio  );
		  
		  //
		  qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_vName  );
	}

	//
	idc  =  IDC_EDIT_name;
	GetDlgItemText(  idc,  tName,  mycountof(  tName  )  );
	tTrim(  tName  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_name,  tName  );  
	
	//
	idc  =  IDC_CHECK_ucbUnresizable;
	m_var.bUnresizable  =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  ?  1  :  0;
	if  (  m_var.bUnresizable  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbUnresizable,  _T(  "1"  )  );  
		}
	else  {
		qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbUnresizable  );
	}


	

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
	if  (  !iMenuId_v  )  {	
		if  (  	!dlgShareDynBmps_bShared(  m_var.hDlg_shareDynBmps,  CONST_objType_webcam,  m_var.index_obj_selected  )  )  {
			//qyShowHint(  _T(  "%s"  ),  _T(  "Camera must be selected"  )  );
			return;
		}
	}


	//
	//
#if  0  //  临时处理一下
	//dlgShareDynBmps_toShareWebcam_func(  m_var.hDlg_shareDynBmps,  m_var.index_obj_selected  -  1,  &m_var.pCapStuff,  iMenuId_v,  m_var.bUnresizable  );
	int objType = CONST_objType_webcam;  //
	dlgShareDynBmps_toShareWebcam_func(m_var.hDlg_shareDynBmps, objType, m_var.index_obj_selected - 1, &m_var.pCapStuff, iMenuId_v, m_var.bUnresizable);
#endif 

	//
	if  (  !m_var.pCapStuff  )  {			 
		CAP_STUFF	*	pCapStuff				=	NULL;
			 
		//	 
		pCapStuff  =  (  CAP_STUFF  *  )pFuncs->pf_CAP_STUFF_new(  );	
		if  (  !pCapStuff  )  goto  errLabel;	
		pFuncs->moniker.pf_addDevicesToMenu(  pCapStuff,  TRUE,  NULL  );
			
		//
		m_var.pCapStuff  =  pCapStuff;

	}

	//
	refreshCtrlStatus(  );


errLabel:
	return;

}


void CDlgOpAvDev::OnBnClickedCheckucbunresizable()
{
	// TODO: Add your control notification handler code here




	return;
}


void CDlgOpAvDev::OnBnClickedCheckautoopenonstartup()
{
	// TODO: Add your control notification handler code here
}


void CDlgOpAvDev::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
