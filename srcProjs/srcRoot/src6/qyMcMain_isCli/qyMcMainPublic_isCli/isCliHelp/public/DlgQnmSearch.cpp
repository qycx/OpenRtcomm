// DlgQnmSearch.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"
#include	"myresource.h"
#include	"qyCusResTemp.h"
#include	"DlgQnmSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

__declspec(  dllexport  )  int  showDlgQnmSearch(  HWND  hParent,  int  *  iType  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int  iRet  =  -1;
	
	CDlgQnmSearch		dlg(  CWnd::FromHandle(  hParent  )  );
	if  (  IDOK  !=  dlg.DoModal(  )  )  goto  errLabel;

	iRet  =  IDOK;
	if  (  iType  )  *iType  =  dlg.m_var.iQueryType;

errLabel:
	return  iRet;

}
/////////////////////////////////////////////////////////////////////////////
// CDlgQnmSearch dialog


CDlgQnmSearch::CDlgQnmSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmSearch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQnmSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmSearch)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmSearch, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmSearch message handlers


BOOL CDlgQnmSearch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CComboBox	*	pCb					=  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_queryType  );
	int				i;
	QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	QY_DMITEM	*	pQueryTypeTable		=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_queryTypeTable  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	MACRO_qyAssert(  pQueryTypeTable,  _T(  "Error: queryTypeTable is null"  )  );

	for  (  i  =  0;  pQueryTypeTable[i].type  !=  -1;  i  ++  )  {
		 pCb->AddString(  CString(  pQueryTypeTable[i].des  )  );
	}
	
	if  (  i  >  0  )  {
		pCb->SelectString(  -1,  CString(  pQueryTypeTable[0].des  )  );
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgQnmSearch::OnOK() 
{
	CComboBox	*	pCb  =  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_queryType  );
	QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	QY_DMITEM	*	pQueryTypeTable		=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_queryTypeTable  );
	CString			str;
	
	pCb->GetLBText(  pCb->GetCurSel(  ),  str  );  
	m_var.iQueryType  =  qyGetTypeByDes(  pQueryTypeTable,  str  );
	
	CDialog::OnOK();
}
