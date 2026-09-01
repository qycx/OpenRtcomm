// DlgPropImGrp.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qymc.h"
#include	"myresource.h"
#include	"DlgPropImGrp.h"
#include ".\dlgpropimgrp.h"
#include	"myDb.h"

#include	"ctxQmc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




__declspec(  dllexport  )  int  showDlgPropImGrp(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iRet	=	-1;

	//
	CDlgPropImGrp					dlg(  CWnd::FromHandle(  hParent  )  );	
	if  (  !dlg.bSetDlgInfo(  pObjDb,  misServName,  pIdInfo  )  )  goto  errLabel;
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;

errLabel:
	return  iRet;
}


/////////////////////////////////////////////////////////////////////////////
// CDlgPropImGrp dialog


CDlgPropImGrp::CDlgPropImGrp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPropImGrp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPropImGrp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

BOOL  CDlgPropImGrp::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{
	if  (  !misServName  ||  !pIdInfo  )  return  FALSE;

	traceLogA(  "CDlgPropImGrp: id is %I64u",  pIdInfo->ui64Id  );

	m_var.pObjDb  =  pObjDb;
	lstrcpyn(  m_var.misServName,  misServName,  mycountof(  m_var.misServName  )  );
	m_var.idInfo.ui64Id  =  pIdInfo->ui64Id;
	return  TRUE;
}


void CDlgPropImGrp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPropImGrp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPropImGrp, CDialog)
	//{{AFX_MSG_MAP(CDlgPropImGrp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgPropImGrp::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPropImGrp message handlers

BOOL CDlgPropImGrp::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	IM_GRP_INFO				grpInfo;
	TCHAR					tBuf[128]		=	_T(  ""  );
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return FALSE;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	// TODO:  在此添加额外的初始化
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  !g_dbFuncs.pf_bGetImGrpInfoBySth(  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  m_var.misServName,  &m_var.idInfo,  &grpInfo  )  )  memset(  &grpInfo,  0,  sizeof(  grpInfo  )  );
	
	SetDlgItemText(  IDC_STATIC_name,  grpInfo.name  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  m_var.idInfo.ui64Id  );
	SetDlgItemText(  IDC_STATIC_messengerId,  CString(  tBuf  )  );
	
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  grpInfo.idInfo_creator.ui64Id  );
	SetDlgItemText(  IDC_STATIC_creator,  CString(  tBuf  )  );

	//
	SetDlgItemText(  IDC_STATIC_staticCreator,  _T(  "Creator:"  )  );


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


//


void CDlgPropImGrp::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
