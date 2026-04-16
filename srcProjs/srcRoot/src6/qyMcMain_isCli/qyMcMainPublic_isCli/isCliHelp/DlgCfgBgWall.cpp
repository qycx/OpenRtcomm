// DlgCfgBgWall.cpp : implementation file
//

//
#include	"stdafx.h"
#include	<stdlib.h>
#include	<math.h>
#include	<tchar.h>

#define  __noDbg_new__

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"
#include	"qmcVWall.h"
#include	"WallTalkers.h"
#include	"DlgDynBmps.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"

#include	"qyCusResTemp.h"

#include	"qyAvRecordPublic.h"

#include	"sp.h"
#include	"qmcCommFunc_isCli.h"
#include	"qyMessengerHelpPublic.h"

//
#include "DlgCfgBgWall.h"
#include "afxdialogex.h"

//
#include	"isCliHelpPublic.h"

//


//
//
//


//
 __declspec(  dllexport  ) int  saveBgWallCfg(  QY_MESSENGER_ID  * pIdInfo,  BgWall_cfg  *  pCfg  )
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int  iRet=  -1;

	unsigned int uiCapType  =  CONST_capType_av;
	unsigned int uiSubCapType  =  0;  
	int iCapUsage  =  0;  

	//
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	QY_REG				reg;
	TCHAR				tBuf[256]	=	_T(  ""  );
	TCHAR			*	pRegVal		=	NULL;
	TCHAR				regValBuf[256]  =  _T(  ""  );
	unsigned  short		usTmp1		=	0;
	unsigned  short		usTmp2		=	0;
	unsigned  short		usTmp_rows	=	0;
	unsigned  short		usTmp_cols	=	0;

	memset(  &reg,  0,  sizeof(  reg  )  );

	BgWall_cfg	*	pPolicy  =  (  BgWall_cfg  *  )pCfg;
	if  (  !pPolicy  )  goto  errLabel;

	//
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
#if  0
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\av"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
#endif
	get_idRegRootKey_qmc(  pIdInfo,  uiCapType,  uiSubCapType,  iCapUsage,  reg.rootKey,  mycountof(  reg.rootKey  )  );

	//
	//  2014/10/16	
	pRegVal  =  CONST_regValName_useBgWall;
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  pPolicy->useBgWall,  tBuf,  10  )  );
	//
	pRegVal  =  CONST_regValName_ucbAddBgWallToConf;
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  pPolicy->ucbAddBgWallToConf,  tBuf,  10  )  );
	//
	pRegVal  =  CONST_regValName_ucbJoinInBgWall;
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  pPolicy->ucbJoinInBgWall,  tBuf,  10  )  );
	//
	pRegVal  =  CONST_regValName_ucbAutoLayout;
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  pPolicy->ucbAutoLayout,  tBuf,  10  )  );

	//
	pRegVal  =  CONST_regValName_bgWallFileName;
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  pPolicy->bgWallFileName  );
	
	//
	pRegVal  =  CONST_regValName_ucbNeverJoinInBgWall;
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  pPolicy->ucbNeverJoinInBgWall,  tBuf,  10  )  );
	
	pRegVal  =  CONST_regValName_usPollingIntervalInS;
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  pPolicy->usPollingIntervalInS,  tBuf,  10  )  );
	

#define		DEFAULT_bgWall_rows		1
#define		DEFAULT_bgWall_cols		5
	//
	usTmp_rows  =  DEFAULT_bgWall_rows;  //  rows;
	usTmp_cols  =  DEFAULT_bgWall_cols;	//  cols;
	pRegVal  =  CONST_regValName_layout;
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d,%d"  ),  pPolicy->bgWallLayoutCfg.usRows_bg,  pPolicy->bgWallLayoutCfg.usCols_bg  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );
	//	
#if  0
	if  (  fixBgWallPolicy(  pIdInfo,  &usTmp_rows,  &usTmp_cols,  NULL,  0  )  )  {
		usTmp_rows  =  DEFAULT_bgWall_rows;
		usTmp_cols  =  DEFAULT_bgWall_cols;
		//
		int  n_wallMems  =  my_getnGrpMems_isCli(  pIdInfo  )  -  1;
		if  (  n_wallMems  >  0  )  {
			usTmp_cols  =  min(  usTmp_cols,  n_wallMems  );
		}

	}
#endif
	//


	iRet  =  0;

errLabel:
	return  iRet;
}



//
//



//
 __declspec(  dllexport  )  int viewDlgCfgBgWall(  HWND  hParent,  HWND  hDlgTalk_mgr,  HWND  *  phWnd  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int								iErr					=	-1;
	QY_MC					*		pQyMc					=	QY_GET_GBUF(  );
	int								iServiceId				=	CONST_qyServiceId_mis;
	MC_VAR_isCli  			*		pProcInfo				=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	CDlgCfgBgWall			*		pDlg					=	NULL;
	RECT							rect;


	//
	CHelp_getDlgTalkVar				help_getDlgTalkVar_mgr;
	DLG_TALK_var			*		pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hDlgTalk_mgr  );
	if  (  !pMgrVar  )  return  -1;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  -1;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;
	


	//
	if  (  IsWindow(  pShadowMgr->bgWall.hTool_cfg  )  )  {
		MACRO_SetForegroundWindow(  pShadowMgr->bgWall.hTool_cfg  );			
		iErr  =  0;  goto  errLabel;		
	}

	
	//
	CWnd  *  pParent  =  CWnd::GetDesktopWindow(  );
	if  (  IsWindow(  hParent  )  )  {
		pParent  =  CWnd::FromHandle(  hParent  );
	}
	pDlg  =  new  CDlgCfgBgWall(  pParent  );
	if  (  !pDlg  )  goto  errLabel;

	//
	if  (  !pDlg->bSetDlgInfo(  hDlgTalk_mgr  )  )  goto  errLabel;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	
	//
	pShadowMgr->bgWall.hTool_cfg  =  pDlg->m_hWnd;
	
	//
	centerWndInParent(  pDlg->m_hWnd,  hParent  );
	//
	pDlg->ShowWindow(  SW_SHOW  );


	//
	if  (  phWnd  )  *phWnd  =  pDlg->m_hWnd;

	//
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




// CDlgCfgBgWall dialog

IMPLEMENT_DYNAMIC(CDlgCfgBgWall, CDialogEx)

CDlgCfgBgWall::CDlgCfgBgWall(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCfgBgWall::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.m_pParent = pParent;
	m_var.m_nID = CDlgCfgBgWall::IDD;

	//
	m_var.guiData.iIDC_EDIT_bgWallFile  =  IDC_EDIT_bgWallFile;
	m_var.guiData.iIDC_BUTTON_bgWallFile  =  IDC_BUTTON_bgWallFile;
	//
	m_var.guiData.iIDC_EDIT_rows  =  IDC_EDIT_rows;
	m_var.guiData.iIDC_EDIT_cols  =  IDC_EDIT_cols;
	m_var.guiData.iIDC_EDIT_pollingInterval  =  IDC_EDIT_pollingInterval;

}


CDlgCfgBgWall::~CDlgCfgBgWall()
{
}


//
BOOL  CDlgCfgBgWall::bSetDlgInfo(  HWND  hDlgTalk_mgr  )
{
	//
	//
	CHelp_getDlgTalkVar				help_getDlgTalkVar_mgr;
	DLG_TALK_var			*		pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hDlgTalk_mgr  );
	if  (  !pMgrVar  )  return  FALSE;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		return  FALSE;
	}

	//
	m_var.hDlgTalk_mgr  =  hDlgTalk_mgr;


	return  TRUE;
}


//
int  CDlgCfgBgWall::get_cfg(  BgWall_cfg  *  pCfg  )
{
	int  iErr  =  -1;
	CHelp_getDlgTalkVar				help_getDlgTalkVar_mgr;
	DLG_TALK_var			*		pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  m_var.hDlgTalk_mgr  );
	if  (  !pMgrVar  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;

	//
	memset(  pCfg,  0,  sizeof(  pCfg[0]  )  );

	//
	pCfg->useBgWall  =  m_var.pBtn_useBgWall->GetCheck(  )  ==  BST_CHECKED;
		 
	//
	pCfg->ucbAddBgWallToConf  =  m_var.pBtn_addBgWallToConf->GetCheck(  )  ==  BST_CHECKED;
				 
	//
	pCfg->ucbJoinInBgWall  =  m_var.pBtn_joinInBgWall->GetCheck(  )  ==  BST_CHECKED;
					 
	//
	pCfg->ucbAutoLayout  =  m_var.pBtn_autoLayout->GetCheck(  )  ==  BST_CHECKED;

	//
	GetDlgItemText(  m_var.guiData.iIDC_EDIT_bgWallFile,  pCfg->bgWallFileName,  mycountof(  pCfg->bgWallFileName  )  );  

	//
	unsigned  short  usTmp1;
	
	usTmp1  =  GetDlgItemInt(  IDC_EDIT_pollingInterval  );
	if  (  pCfg->usPollingIntervalInS  !=  usTmp1  ) {
		pCfg->usPollingIntervalInS  =  usTmp1;
#if  0
		pRegVal  =  CONST_regValName_usPollingIntervalInS;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  usTmp1  );
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );
#endif
	}

	//
	unsigned short usa = 0, usb = 0;
	usa  =  GetDlgItemInt(  IDC_EDIT_rows  );
	usb  =  GetDlgItemInt(  IDC_EDIT_cols  );
	//
	TCHAR	tHint[128]  =  _T(  ""  );
	if  (  fixBgWallPolicy(  &pMgrVar->addr.idInfo,  &usa,  &usb,  tHint,  mycountof(  tHint  )  )  )  {
		qyMessageBox(  this->m_hWnd,  tHint,  _T(  "www.qycx.com"  ),  MB_OK,  10,  NULL  );
		return  -1;
	}
	//
	if  (  pCfg->bgWallLayoutCfg.usRows_bg  !=  usa  ||  pCfg->bgWallLayoutCfg.usCols_bg  !=  usb  )  {
		pCfg->bgWallLayoutCfg.usRows_bg  =  usa;
		pCfg->bgWallLayoutCfg.usCols_bg  =  usb;
		//
#if  0
		pRegVal  =  CONST_regValName_layout;
		_sntprintf(  regValBuf,  mycountof(  regValBuf  ),  _T(  "%s%I64u"  ),  pRegVal,  m_var.idInfo.ui64Id  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d,%d"  ),  usa,  usb  );
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  regValBuf,  tBuf  );
#endif
	}

	iErr  =  0;

errLabel:

	return  iErr;
}


//
int  CDlgCfgBgWall::do_get_cfg(  )
{	
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	//
	get_cfg(  &m_var.cfg  );


	//
	{
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  m_var.hDlgTalk_mgr  );
		if  (  !pMgrVar  )  goto  errLabel;

		//
		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
		if  (  !pShadowMgr  )  goto  errLabel;

		//
		//  2018/01/01
		if  (  m_var.cfg.useBgWall  &&  m_var.cfg.ucbAutoLayout  )  {
			m_var.cfg.bgWallLayoutCfg.usRows_bg  =  1;
			m_var.cfg.bgWallLayoutCfg.usCols_bg  =  pShadowMgr->confCtrl.grpConfCtrl.usCnt;
		}
		else  {
			  BgWall_cfg  bgWallCfg  =  {0};
			  getBgWallCfg(  &pMgrVar->addr.idInfo,  &bgWallCfg  );
			  m_var.cfg.bgWallLayoutCfg  =  bgWallCfg.bgWallLayoutCfg;
		}

		//
		if  (  memcmp(  &pShadowMgr->bgWall.bgWallCfg,  &m_var.cfg,  sizeof(  m_var.cfg  )  )  )  {
			pShadowMgr->bgWall.bgWallCfg  =  m_var.cfg;

			//
			if  (  pShadowMgr->bgWall.bgWallCfg.useBgWall  )  {
								
				//				
				if  (  !IsWindow(  pShadowMgr->bgWall.hBgWall  )  )  {
						  QY_OBJ_DB  *  pObjDb  =  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
						  if  (  !pObjDb  )  goto  errLabel;
						  //
						  BOOL  bNeedNotShowWnd  =  TRUE;	//  FALSE;
						  HWND  hWall  =  NULL;
						  //
						  #ifdef  __DEBUG__  //  2017/11/07
								  #if  10
										bNeedNotShowWnd  =  FALSE;
										traceLog(  _T(  "TEST: bNeedNotShowWnd set false"  )  );
								  #endif
						  #endif
						  //
						  viewBgWall(  m_var.hDlgTalk_mgr,  _T(  ""  ),  CONST_vwSubtype_bgWall,  m_var.hDlgTalk_mgr,  NULL,  bNeedNotShowWnd,  &hWall  );   
						  //
						  if  (  IsWindow(  hWall  )  )  {
							  pShadowMgr->bgWall.hBgWall  =  hWall;
							  pShadowMgr->bgWall.iWndContentType_hBgWall  =  CONST_qyWndContentType_vWall;	//  2017/10/05
						  }
						  //  2017/11/05
				}
				//
				if  (  !IsWindow(  pShadowMgr->bgWall.hBgWall  )  )  {
					goto  errLabel;
				}
				//
				if  (  pShadowMgr->bgWall.bgWallCfg.ucbAutoLayout  )  {
					dynBmps_autoLayout(  pShadowMgr->bgWall.hBgWall  );
					}
				else  {
					  dynBmps_openFile(  pShadowMgr->bgWall.bgWallCfg.bgWallFileName,  pShadowMgr->bgWall.hBgWall  );
				}

				//
				}
			else  {
				  //			
				  if  (  IsWindow(  pShadowMgr->bgWall.hBgWall  )  )  {
					  SendMessageTimeout(  pShadowMgr->bgWall.hBgWall,  WM_CLOSE,  0,  0,  0,  1000,  NULL  );
					  if  (  IsWindow(  pShadowMgr->bgWall.hBgWall  )  )  {
						  showNotification(  0,  0,  0,  0,  0,  0,  _T(  "close bgWall failed"  )  );
						  goto  errLabel;
					  }
				  }

			}


			//
			//				
			D3D_talkerData_cfg  *  pTalkerDataCfg  =  (  D3D_talkerData_cfg  *  )&pMgrVar->d3d_talkerData_cfg;				
			if  (  !pTalkerDataCfg  )  goto  errLabel;
			
			//  2017/11/03
			pTalkerDataCfg->layout.ucbShowBgWall  =  pShadowMgr->bgWall.bgWallCfg.useBgWall  ||  pShadowMgr->bgWall.bgWallCfg.ucbAddBgWallToConf;
			pTalkerDataCfg->layout.bgWallLayoutCfg  =  pShadowMgr->bgWall.bgWallCfg.bgWallLayoutCfg;


			//
			dlgTalk_doCmd_joinInBgWall(  m_var.hDlgTalk_mgr  );


			//			
			timestamp_renew(   NULL,  &pTalkerDataCfg->ts_layout,_T("dlgCfgBgWall.do_get_cfg.l444"));
		}

	}

errLabel:

	return  0;
}


//
int  CDlgCfgBgWall::refreshCtrls(  )
{
	BOOL  bEnable  =  FALSE;
	if  (  m_var.pBtn_useBgWall->GetCheck(  )  ==  BST_CHECKED  )  {
		bEnable  =  TRUE;
	}

	//		
	m_var.pBtn_autoLayout->EnableWindow(  bEnable  );		
	m_var.pBtn_useBgWallFile->EnableWindow(  bEnable  );

	//
	bEnable  =  FALSE;
	if  (  m_var.pBtn_useBgWallFile->GetCheck(  )  ==  BST_CHECKED  )  {
		bEnable  =  TRUE;
	}
	
	::EnableWindow(  ::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_EDIT_bgWallFile  ),  bEnable  );
	::EnableWindow(  ::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_BUTTON_bgWallFile  ),  bEnable  );

	//
	

	return  0;
}



//
BOOL CDlgCfgBgWall::Create(const RECT& rect)
{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProc		=	NULL;

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): 在创建对话框之前应先设置初始数据"  );
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


 BOOL  CDlgCfgBgWall::bQuitDlg(  )		
{		
	traceLogA(  "CDlgListView_db(  )::bQuitDlg enters"  );


	//  2009/05/01
	DestroyWindow();				  
		
//  errLabel:

	traceLogA(  "CDlgListView_db(  )::bQuitDlg leaves"  );

	return  TRUE;
}



//
void CDlgCfgBgWall::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCfgBgWall, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgCfgBgWall::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgCfgBgWall::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_useBgWall, &CDlgCfgBgWall::OnBnClickedCheckusebgwall)
	ON_BN_CLICKED(IDC_CHECK_addBgWallToConf, &CDlgCfgBgWall::OnBnClickedCheckaddbgwalltoconf)
	ON_BN_CLICKED(IDC_CHECK_joinInBgWall, &CDlgCfgBgWall::OnBnClickedCheckjoininbgwall)
	ON_BN_CLICKED(IDC_RADIO_autoLayout, &CDlgCfgBgWall::OnBnClickedRadioautolayout)
	ON_BN_CLICKED(IDC_RADIO_useBgWallFile, &CDlgCfgBgWall::OnBnClickedRadiousebgwallfile)
	ON_BN_CLICKED(IDC_BUTTON_bgWallFile, &CDlgCfgBgWall::OnBnClickedButtonbgwallfile)
END_MESSAGE_MAP()


// CDlgCfgBgWall message handlers





BOOL CDlgCfgBgWall::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	int  iErr  =  -1;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	//
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	// TODO:  Add extra initialization here
	m_var.pBtn_useBgWall  =  (  CButton  *  )GetDlgItem(  IDC_CHECK_useBgWall  );
	m_var.pBtn_addBgWallToConf  =  (  CButton  *  )GetDlgItem(  IDC_CHECK_addBgWallToConf  );
	m_var.pBtn_joinInBgWall  =  (  CButton  *  )GetDlgItem(  IDC_CHECK_joinInBgWall  );
	//
	m_var.pBtn_autoLayout  =  (  CButton  *  )GetDlgItem(  IDC_RADIO_autoLayout  );
	m_var.pBtn_useBgWallFile  =  (  CButton  *  )GetDlgItem(  IDC_RADIO_useBgWallFile  );

	//
	CHelp_getDlgTalkVar				help_getDlgTalkVar_mgr;
	DLG_TALK_var			*		pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  m_var.hDlgTalk_mgr  );
	if  (  !pMgrVar  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	
	//
	m_var.pBtn_useBgWall->SetCheck(  pShadowMgr->bgWall.bgWallCfg.useBgWall  ?  BST_CHECKED  :  BST_UNCHECKED  );
	m_var.pBtn_addBgWallToConf->SetCheck(  pShadowMgr->bgWall.bgWallCfg.ucbAddBgWallToConf  ?  BST_CHECKED  :  BST_UNCHECKED  );
	m_var.pBtn_joinInBgWall->SetCheck(  pShadowMgr->bgWall.bgWallCfg.ucbJoinInBgWall  ?  BST_CHECKED  :  BST_UNCHECKED  );
	//
	if  (  pShadowMgr->bgWall.bgWallCfg.useBgWall  )  {
		if  (  pShadowMgr->bgWall.bgWallCfg.ucbAutoLayout  )  m_var.pBtn_autoLayout->SetCheck(  BST_CHECKED  );
		else  {
			  m_var.pBtn_useBgWallFile->SetCheck(  BST_CHECKED  );
		}
		}
	else  {
		  //
		  m_var.pBtn_autoLayout->SetCheck(  BST_CHECKED  );
	}
	SetDlgItemText(  IDC_EDIT_bgWallFile,  pShadowMgr->bgWall.bgWallCfg.bgWallFileName  );

	//	
	//
	SetDlgItemInt(  IDC_EDIT_pollingInterval,  pShadowMgr->bgWall.bgWallCfg.usPollingIntervalInS  );
	SetDlgItemInt(  IDC_EDIT_rows,  pShadowMgr->bgWall.bgWallCfg.bgWallLayoutCfg.usRows_bg  );
	SetDlgItemInt(  IDC_EDIT_cols,  pShadowMgr->bgWall.bgWallCfg.bgWallLayoutCfg.usCols_bg  );

	//
	refreshCtrls(  );

	//
	//  2018/01/01
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_RADIO_useBgWallFile  ),  SW_HIDE  );
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_bgWallFile  ),  SW_HIDE  );
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_bgWallFile  ),  SW_HIDE  );
	//
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_CHECK_joinInBgWall  ),  SW_HIDE  );
	
	
	//  2018/01/02. 32位不能使用查看所有人的功能
	if  (  !bAppX64(  )  )  {
		m_var.pBtn_useBgWall->EnableWindow(  FALSE  ); 
	}


	//
	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		PostMessage(  WM_CLOSE  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgCfgBgWall::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PostNcDestroy();

	//
	delete  this;

}


void CDlgCfgBgWall::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	TCHAR  tFile[MAX_PATH]  =  _T(  ""  );

	//
	if  (  m_var.pBtn_useBgWall->GetCheck(  )  ==  BST_CHECKED  )  {
		if  (  m_var.pBtn_useBgWallFile->GetCheck(  )  ==  BST_CHECKED  )  {
			GetDlgItemText(  IDC_EDIT_bgWallFile,  tFile,  mycountof(  tFile  )  );
			tTrim(  tFile  );
			if  (  !bFileExists(  tFile  )  )  {
				qyShowHint(  _T(  "%s"  ),  _T(  "Error: bg file doesnot exist."  )  );
				::SetFocus(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_bgWallFile  )  );
				return;
			}
		}
	}

	//
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  m_var.hDlgTalk_mgr  );
	if  (  !pMgrVar  )  return;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	
	//
	saveBgWallCfg(  &pMgrVar->addr.idInfo,  &pShadowMgr->bgWall.bgWallCfg  );
	

	//CDialogEx::OnOK();
	bQuitDlg(  );

	return;
}


void CDlgCfgBgWall::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
	bQuitDlg(  );
}


void CDlgCfgBgWall::OnBnClickedCheckusebgwall()
{
	// TODO: Add your control notification handler code here
	//
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	//
	if  (  m_var.pBtn_useBgWall->GetCheck(  )  ==  BST_CHECKED  )  {
		//
		m_var.pBtn_addBgWallToConf->SetCheck(  BST_UNCHECKED  );

		//
		if  (  m_var.pBtn_autoLayout->GetCheck(  )  ==  BST_UNCHECKED  
			&&  m_var.pBtn_useBgWallFile->GetCheck(  )  ==  BST_UNCHECKED  )
		{
			m_var.pBtn_autoLayout->SetCheck(  BST_CHECKED  );
		}
		
	}

	//
	refreshCtrls(  );
	
	//
	do_get_cfg(  );

errLabel:
	return;
}



void CDlgCfgBgWall::OnBnClickedCheckaddbgwalltoconf()
{
	// TODO: Add your control notification handler code here
	//
	if  (  m_var.pBtn_addBgWallToConf->GetCheck(  )  ==  BST_CHECKED  )  {
		//
		m_var.pBtn_useBgWall->SetCheck(  BST_UNCHECKED  );

	}

	//
	do_get_cfg(  );

	return;
}


void CDlgCfgBgWall::OnBnClickedCheckjoininbgwall()
{
	// TODO: Add your control notification handler code here
	//
	do_get_cfg(  );


}


void CDlgCfgBgWall::OnBnClickedRadioautolayout()
{
	// TODO: Add your control notification handler code here
	if  (  m_var.pBtn_autoLayout->GetCheck(  )  ==  BST_CHECKED  )  {
		::EnableWindow(  ::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_EDIT_bgWallFile  ),  FALSE  );
		::EnableWindow(  ::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_BUTTON_bgWallFile  ),  FALSE  );

	}

	//
	do_get_cfg(  );

}


void CDlgCfgBgWall::OnBnClickedRadiousebgwallfile()
{
	// TODO: Add your control notification handler code here
	if  (  m_var.pBtn_useBgWallFile->GetCheck(  )  ==  BST_CHECKED  )  {
		::EnableWindow(  ::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_EDIT_bgWallFile  ),  TRUE  );
		::EnableWindow(  ::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_BUTTON_bgWallFile  ),  TRUE  );
	}

	//
	do_get_cfg(  );

}


void CDlgCfgBgWall::OnBnClickedButtonbgwallfile()
{
	// TODO: Add your control notification handler code here
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	//
	CQyString  csPath;

	qyBrowseForFile(  m_hWnd,  TRUE,  _T(  "qvw\0"  ),  OFN_FILEMUSTEXIST,  _T(  "QY V-Wall Module(&.qvw)\0*.qvw\0\0"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectFilenameFormat  ),  NULL,  pQyMc,  csPath  );
	if  (  !csPath.GetLength(  )  )  return;

	//
	int  idc  =  IDC_EDIT_bgWallFile;
	SetDlgItemText(  idc,  csPath  );

	//
	do_get_cfg(  );


errLabel:
	return;
}
