// DlgEditConsultMem.cpp : implementation file
//

#include "stdafx.h"
#include	"myresource.h"
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
#include	"imgProcessPublic.h"


#include	"sp.h"
#include	"isCliHelp.h"
#include	"isCliHelpPublic.h"

#include "DlgEditConsultMem.h"
#include "afxdialogex.h"

#include	"help_getDlgTalkVar.h"
#include	"dlgtalkproc.h"
#include	"funcsForIsCliHelp.h"


//
#if  0
int  saveConsultMem(  QY_MESSENGER_ID  *pIdInfo_grp,  QY_MESSENGER_ID  *  pIdInfo_mem,  CONSULT_mem  *  pMem  )
{
	int  iErr  =  -1;
	QY_REG				reg;
	unsigned  char		ucCmd;
	TCHAR			*	pRegVal				=	NULL;
	char				buf[256];
	TCHAR				tBuf[256]	=  _T(  ""  );
	TCHAR				rootKeyBuf[256]	=	_T(  ""  );

	int  iCapType  =  CONST_capType_av;
	int  iCapSubType  =  0;
	int  iUsage  =  0;

	//
	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;


	getRegRootKey_qmc(  iCapType,  iCapSubType,  iUsage,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	safeTcsnCpy(  reg.rootKey,  rootKeyBuf,  mycountof(  rootKeyBuf  )  );

	//
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\consultMem\\%I64u.%I64u"  ),  rootKeyBuf,  pIdInfo_grp->ui64Id,  pIdInfo_mem->ui64Id  );


	//
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ksName,  pMem->ksName  );
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ysName,  pMem->ysName  );




	iErr  =  0;
errLabel:
	return  iErr;

}
#endif

//
#if  0
__declspec(  dllexport  )  int  getConsultMem(  QY_MESSENGER_ID  *pIdInfo_grp,  QY_MESSENGER_ID  *  pIdInfo_mem,  CONSULT_mem  *  pMem  )
{
	int  iErr  =  -1;
	QY_REG				reg;
	unsigned  char		ucCmd;
	TCHAR			*	pRegVal				=	NULL;
	char				buf[256];
	TCHAR				tBuf[256]	=  _T(  ""  );
	TCHAR				rootKeyBuf[256]	=	_T(  ""  );


	if  (  !pMem  )  return  -1;
	memset(  pMem,  0,  sizeof(  pMem[0]  )  );


	int  iCapType  =  CONST_capType_av;
	int  iCapSubType  =  0;
	int  iUsage  =  0;
	
	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;


	getRegRootKey_qmc(  iCapType,  iCapSubType,  iUsage,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	safeTcsnCpy(  reg.rootKey,  rootKeyBuf,  mycountof(  rootKeyBuf  )  );

	//
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\consultMem\\%I64u.%I64u"  ),  rootKeyBuf,  pIdInfo_grp->ui64Id,  pIdInfo_mem->ui64Id  );


	//
	qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ksName,  (  char  *  )pMem->ksName,  sizeof(  pMem->ksName  ),  NULL  );
	qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ysName,  (  char  *  )pMem->ysName,  sizeof(  pMem->ysName  ),  NULL  );




	iErr  =  0;
errLabel:
	return  iErr;

}
#endif

//
  //
  __declspec(  dllexport  )  int  refresh_consult_mem(  HWND  hDlgTalk_mgr,  QY_MESSENGER_ID  *  pIdInfo_toRefresh  )
  {
	  int  iErr  =  -1;
	  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	  if  (  !pFuncs  )  return  -1;

	  CHelp_getDlgTalkVar  help_getDlgTalkVar;
	  DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlgTalk_mgr  );
	  if  (  !pMgrVar  )  return  -1;
	  if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  -1;
	  //
	  if  (  pMgrVar->addr.uiObjType  !=  CONST_objType_imGrp  )  return  -1;
	  //
	  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	  if  (  !pShadowMgr  )  return  -1;
	  GRP_confCtrl  *  p  =  &pShadowMgr->confCtrl.grpConfCtrl;

	  //
	  int  i;
	  for  (  i  =  0;  i  <  p->usCnt;  i  ++  )  {
		   GrpMem_confCtrl  *  pMem  =  &p->pMems[i];
		   if  (  pMem->idInfo.ui64Id  ==  pIdInfo_toRefresh->ui64Id  )  {
#if  0
			   CONSULT_mem  cm  =  {0};
			   getConsultMem(  &pMgrVar->addr.idInfo,  &pMem->idInfo,  &cm  );
			   //
			   safeTcsnCpy(  cm.ksName,  pMem->ksName,  mycountof(  pMem->ksName  )  );
			   safeTcsnCpy(  cm.ysName,  pMem->ysName,  mycountof(  pMem->ysName  )  );
#endif
			   break;
		   }
	  }

	  //
	  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		  TALKER_shadow_mgrMem  *  pShadow  =  &pShadowMgr->shadows[i];
		  if  (  !IsWindow(  pShadow->hShadow  )  )  continue;
		  //
		  {
			  CHelp_getDlgTalkVar  help_getDlgTalkVar;
			  DLG_TALK_var  *  pVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  pShadow->hShadow  );
			  if  (  !pVar   )  continue;
			  //pVar->m_sbsho
			  if  (  !pVar->guiData.ucbShowImGrpMems  )  continue;

			  //
			  TCHAR  tBuf[128];
			  	GetDlgItemText(  pShadow->hShadow,  IDC_EDIT_filter,  tBuf,  mycountof(  tBuf  )  );

				tTrim(  tBuf  );

				//
				dlgTalk_loadGrpMems(  pShadow->hShadow,  pVar,  tBuf  );

								
		  }
	  }

	  return  0;
  }


//
__declspec(  dllexport  )  int  viewDlgEditConsultMem(  HWND  hParent,  QY_MESSENGER_ID  *  pIdInfo_grp,  QY_MESSENGER_ID  *  pIdInfo_mem  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr			=		-1;
	QY_MC				*	pQyMc			=		QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci			=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;	
	MC_VAR_isCli			*	pProcInfo		=		(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;
	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	CDlgEditConsultMem  dlg(  CWnd::FromHandle(  hParent  )  );
	
	dlg.bSetInfo(  pIdInfo_grp,  pIdInfo_mem  );
	
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iErr  =  0;


errLabel:


	return  iErr;
}

// CDlgEditConsultMem dialog

IMPLEMENT_DYNAMIC(CDlgEditConsultMem, CDialogEx)

CDlgEditConsultMem::CDlgEditConsultMem(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgEditConsultMem::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

}

CDlgEditConsultMem::~CDlgEditConsultMem()
{
}


//
int  CDlgEditConsultMem::bSetInfo(  QY_MESSENGER_ID  *  pIdInfo_grp,  QY_MESSENGER_ID  *  pIdInfo_mem  )
{
	m_var.idInfo_grp.ui64Id  =  pIdInfo_grp->ui64Id;
	m_var.idInfo_mem.ui64Id  =  pIdInfo_mem->ui64Id;

	return  TRUE;
}


//
void CDlgEditConsultMem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgEditConsultMem, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgEditConsultMem::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgEditConsultMem message handlers


void CDlgEditConsultMem::OnBnClickedOk()
{
	//
#if  0
	CONSULT_mem  cm  =  {0};
	GetDlgItemText(  IDC_EDIT_ksName,  cm.ksName,  mycountof(  cm.ksName  )  );
	tTrim(  cm.ksName  );
	GetDlgItemText(  IDC_EDIT_ysName,  cm.ysName,  mycountof(  cm.ysName  )  );
	tTrim(  cm.ysName  );
	//
	saveConsultMem(  &m_var.idInfo_grp,  &m_var.idInfo_mem,  &cm  );
#endif

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


BOOL CDlgEditConsultMem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//
	TCHAR  talkerDesc[128]  =  _T(  ""  );

	getDescByIdInfo(  0,  &m_var.idInfo_mem,  talkerDesc,  mycountof(  talkerDesc  ),  0,  0  );
	SetDlgItemText(  IDC_STATIC_memInfo,  talkerDesc  );
	//
#if  0
	CONSULT_mem  cm  =  {0};

	getConsultMem(  &m_var.idInfo_grp,  &m_var.idInfo_mem,  &cm  );
	SetDlgItemText(  IDC_EDIT_ksName,  cm.ksName  );
	SetDlgItemText(  IDC_EDIT_ysName,  cm.ysName  );
#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

