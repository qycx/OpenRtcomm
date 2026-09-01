// DlgRemoteStorageSettings.cpp : implementation file
//

#include "stdafx.h"


#include	"qyMcMainCommon.h"
#include	"myresource.h"


#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
//  #include	"DlgTalk.h"
#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"


#include	"isCliHelpPublic.h"

#include "DlgRemoteStorageSettings.h"
#include "afxdialogex.h"



__declspec(  dllexport  )  int  showDlgRemoteStorageSettings(  HWND  hParent  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int			iRet	=	-1;

	CDlgRemoteStorageSettings		dlg(  CWnd::FromHandle(  hParent  )  );
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;

errLabel:
	return  iRet;
}


//
__declspec(  dllexport  )  int  getRemoteStorageCfg(  REMOTE_storage_cfg  *  pCfg  )
{
		QY_MC		*	pQyMc	=	QY_GET_GBUF(  );

		QY_REG			reg;
	TCHAR		*	pRegVal	=	NULL;
	TCHAR			tBuf[256]	=	_T(  ""  );

	if  (  !pCfg  )  return  -1;
	memset(  pCfg,  0,  sizeof(  pCfg[0]  )  );

	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

	pRegVal  =  CONST_regValName_remoteStorageUsers;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  	{
		tBuf[0]  =  0;
	}
	if  (  tBuf[0]  )
	{
		getUi64IdFromReg(  tBuf,  pCfg->idInfos_allowed,  mycountof(  pCfg->idInfos_allowed  )  );
	}

	return  0;
}


// CDlgRemoteStorageSettings dialog

IMPLEMENT_DYNAMIC(CDlgRemoteStorageSettings, CDialogEx)

CDlgRemoteStorageSettings::CDlgRemoteStorageSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRemoteStorageSettings::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgRemoteStorageSettings::~CDlgRemoteStorageSettings()
{
}

void CDlgRemoteStorageSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRemoteStorageSettings, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgRemoteStorageSettings::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgRemoteStorageSettings message handlers

BOOL CDlgRemoteStorageSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  m_hWnd,  IDD_remoteStorageSettings  );

	QY_REG			reg;
	TCHAR		*	pRegVal	=	NULL;
	TCHAR			tBuf[256]	=	_T(  ""  );

	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

	getRemoteStorageCfg(  &m_var.cfg  );  

	tBuf[0]  =  0;	
	getBufFromUi64Id(  m_var.cfg.idInfos_allowed,  mycountof(  m_var.cfg.idInfos_allowed  ),  tBuf,  mycountof(  tBuf  )  );
	SetDlgItemText(  IDC_EDIT_remoteStorageUsers,  tBuf  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRemoteStorageSettings::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	QY_MC						*	pQyMc	  =  QY_GET_GBUF();
	QY_MESSENGER_ID					curIdInfos[10];		//  5
	TCHAR							tBuf[256]  =  _T(  ""  );
	TCHAR						*	pRegVal  =  NULL;
	//
	QY_REG							reg;
	//
	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;	
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
	pRegVal  =  CONST_regValName_remoteStorageUsers;

	memset(  &curIdInfos,  0,  sizeof(  curIdInfos  )  );
	GetDlgItemText(  IDC_EDIT_remoteStorageUsers,  tBuf,  mycountof(  tBuf  )  );

	if  (  tBuf[0]  )  {
		getUi64IdFromReg(  tBuf,  curIdInfos,  mycountof(  curIdInfos  )  );
		tBuf[0]  =  0;
		getBufFromUi64Id(  curIdInfos,  mycountof(  curIdInfos  ),  tBuf,  mycountof(  tBuf  )  );

		if  (  tBuf[0]  )  {
			if  (  memcmp(  curIdInfos,  m_var.cfg.idInfos_allowed,  sizeof(  curIdInfos  )  )  ) {
				memcpy(  &m_var.cfg.idInfos_allowed,  &curIdInfos,  sizeof(  m_var.cfg.idInfos_allowed  )  );
				qySetRegCfgT(  HKEY_CURRENT_USER,  reg.rootKey,  pRegVal,  tBuf  );
			}
		}
	}
	else  {
		qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );
	}

	CDialogEx::OnOK();
}
