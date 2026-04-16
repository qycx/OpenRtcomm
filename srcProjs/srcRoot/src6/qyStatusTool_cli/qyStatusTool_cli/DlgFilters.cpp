// DlgFilters.cpp : implementation file
//

#include	"stdafx.h"
#include	<vfw.h>
#include	"qmCommon.h"
#include	"qystatustool.h"
#include	"qyPs.h"
//#include	"PpQwmCommStatus.h"
#include	"dlgFilters.h"
#include	"qyCusResPublic.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFilters dialog


CDlgFilters::CDlgFilters(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFilters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFilters)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

//
 //BOOL  CDlgFilters::bSetDlgInfo(  int  type,  HWND  hParent,  unsigned  int  ulIp0,  LPCTSTR  filter0,  LPCTSTR  filter1,  LPCTSTR  contentFilter2,  LPCTSTR  contentFilter3  )
BOOL  CDlgFilters::bSetDlgInfo(  int  type,  HWND  hParent,  MY_filters  *  filters  )
{
	 m_var.type  =  type;
	 m_var.hParent  =  hParent;
	 //
#if  0
	 m_var.ulClientIp0  =  ulIp0;
	 //m_var.ulClientIp1  =  ulIp1;
	 if  (  filter0  )  lstrcpyn(  m_var.filter0Buf,  filter0,  mycountof(  m_var.filter0Buf  )  );
	 if  (  filter1  )  lstrcpyn(  m_var.filter1Buf,  filter1,  mycountof(  m_var.filter1Buf  )  );
	 if  (  contentFilter2  )  lstrcpyn(  m_var.contentFilter2Buf,  contentFilter2,  mycountof(  m_var.contentFilter2Buf  )  );
	 if  (  contentFilter3  )  lstrcpyn(  m_var.contentFilter3Buf,  contentFilter3,  mycountof(  m_var.contentFilter3Buf  )  );
#endif
	 if  (  filters  )  m_var.filters  =  *filters;
	 
	 //
	 return  TRUE;
}


void CDlgFilters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFilters)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFilters, CDialog)
	//{{AFX_MSG_MAP(CDlgFilters)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgFilters::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFilters message handlers

//
int procFilter(  TCHAR  *  tBuf,  int  cnt  )
{
	tTrim(  tBuf  );
	CString  str=CString( tBuf  );
	str.MakeUpper(  );
	safeTcsnCpy(  str,  tBuf, cnt  );
	return  0;
}

//
void CDlgFilters::OnOK() 
{
	// TODO: Add extra validation here
	TCHAR	tBuf[255  +  1]		=	_T(  ""  );
	char	buf[255  +  1]		=	"";

	MY_filter  *  pMem  = &m_var.filters.mems[0];

	GetDlgItemText(  IDC_EDIT_clientIp0,  tBuf,  mycountof(  tBuf  )  );
	tTrim(  tBuf  );
	myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
	if  (  buf[0]  &&  bIpValid(  buf  )  )  pMem->ulClientIp0  =  inet_addr(  buf  );
	//
	GetDlgItemText(  IDC_EDIT_filter00,  pMem->filter0Buf,  mycountof(  pMem->filter0Buf  )  );
	GetDlgItemText(  IDC_EDIT_filter01,  pMem->filter1Buf,  mycountof(  pMem->filter1Buf  )  );

	GetDlgItemText(  IDC_EDIT_filter02,  pMem->contentFilter2Buf,  mycountof(  pMem->contentFilter2Buf  )  );
	GetDlgItemText(  IDC_EDIT_filter03,  pMem->contentFilter3Buf,  mycountof(  pMem->contentFilter3Buf  )  );

	//	
	pMem  = &m_var.filters.mems[1];

	GetDlgItemText(  IDC_EDIT_clientIp1,  tBuf,  mycountof(  tBuf  )  );
	tTrim(  tBuf  );
	myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
	if  (  buf[0]  &&  bIpValid(  buf  )  )  pMem->ulClientIp0  =  inet_addr(  buf  );
	//
	GetDlgItemText(  IDC_EDIT_filter10,  pMem->filter0Buf,  mycountof(  pMem->filter0Buf  )  );
	GetDlgItemText(  IDC_EDIT_filter11,  pMem->filter1Buf,  mycountof(  pMem->filter1Buf  )  );

	GetDlgItemText(  IDC_EDIT_filter12,  pMem->contentFilter2Buf,  mycountof(  pMem->contentFilter2Buf  )  );
	GetDlgItemText(  IDC_EDIT_filter13,  pMem->contentFilter3Buf,  mycountof(  pMem->contentFilter3Buf  )  );

	//	
	pMem  = &m_var.filters.mems[2];

	GetDlgItemText(  IDC_EDIT_clientIp2,  tBuf,  mycountof(  tBuf  )  );
	tTrim(  tBuf  );
	myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
	if  (  buf[0]  &&  bIpValid(  buf  )  )  pMem->ulClientIp0  =  inet_addr(  buf  );
	//
	GetDlgItemText(  IDC_EDIT_filter20,  pMem->filter0Buf,  mycountof(  pMem->filter0Buf  )  );
	GetDlgItemText(  IDC_EDIT_filter21,  pMem->filter1Buf,  mycountof(  pMem->filter1Buf  )  );

	GetDlgItemText(  IDC_EDIT_filter22,  pMem->contentFilter2Buf,  mycountof(  pMem->contentFilter2Buf  )  );
	GetDlgItemText(  IDC_EDIT_filter23,  pMem->contentFilter3Buf,  mycountof(  pMem->contentFilter3Buf  )  );

	//	
	pMem  = &m_var.filters.mems[3];

	GetDlgItemText(  IDC_EDIT_clientIp3,  tBuf,  mycountof(  tBuf  )  );
	tTrim(  tBuf  );
	myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
	if  (  buf[0]  &&  bIpValid(  buf  )  )  pMem->ulClientIp0  =  inet_addr(  buf  );
	//
	GetDlgItemText(  IDC_EDIT_filter30,  pMem->filter0Buf,  mycountof(  pMem->filter0Buf  )  );
	GetDlgItemText(  IDC_EDIT_filter31,  pMem->filter1Buf,  mycountof(  pMem->filter1Buf  )  );

	GetDlgItemText(  IDC_EDIT_filter32,  pMem->contentFilter2Buf,  mycountof(  pMem->contentFilter2Buf  )  );
	GetDlgItemText(  IDC_EDIT_filter33,  pMem->contentFilter3Buf,  mycountof(  pMem->contentFilter3Buf  )  );

		//	
	pMem  = &m_var.filters.mems[4];

	GetDlgItemText(  IDC_EDIT_clientIp4,  tBuf,  mycountof(  tBuf  )  );
	tTrim(  tBuf  );
	myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
	if  (  buf[0]  &&  bIpValid(  buf  )  )  pMem->ulClientIp0  =  inet_addr(  buf  );
	//
	GetDlgItemText(  IDC_EDIT_filter40,  pMem->filter0Buf,  mycountof(  pMem->filter0Buf  )  );
	GetDlgItemText(  IDC_EDIT_filter41,  pMem->filter1Buf,  mycountof(  pMem->filter1Buf  )  );

	GetDlgItemText(  IDC_EDIT_filter42,  pMem->contentFilter2Buf,  mycountof(  pMem->contentFilter2Buf  )  );
	GetDlgItemText(  IDC_EDIT_filter43,  pMem->contentFilter3Buf,  mycountof(  pMem->contentFilter3Buf  )  );

		//	
	pMem  = &m_var.filters.mems[5];

	GetDlgItemText(  IDC_EDIT_clientIp5,  tBuf,  mycountof(  tBuf  )  );
	tTrim(  tBuf  );
	myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
	if  (  buf[0]  &&  bIpValid(  buf  )  )  pMem->ulClientIp0  =  inet_addr(  buf  );
	//
	GetDlgItemText(  IDC_EDIT_filter50,  pMem->filter0Buf,  mycountof(  pMem->filter0Buf  )  );
	GetDlgItemText(  IDC_EDIT_filter51,  pMem->filter1Buf,  mycountof(  pMem->filter1Buf  )  );

	GetDlgItemText(  IDC_EDIT_filter52,  pMem->contentFilter2Buf,  mycountof(  pMem->contentFilter2Buf  )  );
	GetDlgItemText(  IDC_EDIT_filter53,  pMem->contentFilter3Buf,  mycountof(  pMem->contentFilter3Buf  )  );


	//str0  =  CString(  dlg.m_var.filter0Buf  );		
	//str0.TrimLeft(  );  str0.TrimRight(   );  str0.MakeUpper(  );

	CString  str;
	int  i;
	for  (  i  =  0;  i  <  mycountof(  m_var.filters.mems  );  i  ++  )  {
		MY_filter  *  pMem  =  &m_var.filters.mems[i];
	
		//
		procFilter(  pMem->filter0Buf,  mycountof(  pMem->filter0Buf  )  );
		procFilter(  pMem->filter1Buf,  mycountof(  pMem->filter1Buf  )  );
		procFilter(  pMem->contentFilter2Buf,  mycountof(  pMem->contentFilter2Buf  )  );
		procFilter(  pMem->contentFilter3Buf,  mycountof(  pMem->contentFilter3Buf  )  );
	}

	CDialog::OnOK();
}

BOOL CDlgFilters::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//  CQyPs  *  pPs  =  (  CQyPs  *  )GetParent(  );
	//  QY_STATUS_STRUCT	*	pStatusStruct	=  &pPs->m_var.u.showInfo.statusStruct;
	QY_STATUS_STRUCT		*  pStatusStruct  =  m_var.pStatusStruct;

	char	ip[15  +  1]	=	"";

	cusDlgRes(  0,  &pStatusStruct->cusRes,  this->m_hWnd,  this->IDD  );

	MY_filter  *  pMem  =  &m_var.filters.mems[0];
	ip[0]  =  0;
	if  (  pMem->ulClientIp0  &&  !ulIp2Str(  pMem->ulClientIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
	SetDlgItemText(  IDC_EDIT_clientIp0,  CString(  ip  )  );
	//
	SetDlgItemText(  IDC_EDIT_filter00,  pMem->filter0Buf  );
	SetDlgItemText(  IDC_EDIT_filter01,  pMem->filter1Buf  );
	SetDlgItemText(  IDC_EDIT_filter02,  pMem->contentFilter2Buf  );
	SetDlgItemText(  IDC_EDIT_filter03,  pMem->contentFilter3Buf  );

	//
	pMem  =  &m_var.filters.mems[1];
	ip[0]  =  0;
	if  (  pMem->ulClientIp0  &&  !ulIp2Str(  pMem->ulClientIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
	SetDlgItemText(  IDC_EDIT_clientIp1,  CString(  ip  )  );
	//
	SetDlgItemText(  IDC_EDIT_filter10,  pMem->filter0Buf  );
	SetDlgItemText(  IDC_EDIT_filter11,  pMem->filter1Buf  );
	SetDlgItemText(  IDC_EDIT_filter12,  pMem->contentFilter2Buf  );
	SetDlgItemText(  IDC_EDIT_filter13,  pMem->contentFilter3Buf  );
	
	//
	pMem  =  &m_var.filters.mems[2];
	ip[0]  =  0;
	if  (  pMem->ulClientIp0  &&  !ulIp2Str(  pMem->ulClientIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
	SetDlgItemText(  IDC_EDIT_clientIp2,  CString(  ip  )  );
	//
	SetDlgItemText(  IDC_EDIT_filter20,  pMem->filter0Buf  );
	SetDlgItemText(  IDC_EDIT_filter21,  pMem->filter1Buf  );
	SetDlgItemText(  IDC_EDIT_filter22,  pMem->contentFilter2Buf  );
	SetDlgItemText(  IDC_EDIT_filter23,  pMem->contentFilter3Buf  );

	//
	pMem  =  &m_var.filters.mems[3];
	ip[0]  =  0;
	if  (  pMem->ulClientIp0  &&  !ulIp2Str(  pMem->ulClientIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
	SetDlgItemText(  IDC_EDIT_clientIp3,  CString(  ip  )  );
	//
	SetDlgItemText(  IDC_EDIT_filter30,  pMem->filter0Buf  );
	SetDlgItemText(  IDC_EDIT_filter31,  pMem->filter1Buf  );
	SetDlgItemText(  IDC_EDIT_filter32,  pMem->contentFilter2Buf  );
	SetDlgItemText(  IDC_EDIT_filter33,  pMem->contentFilter3Buf  );

	//
	pMem  =  &m_var.filters.mems[4];
	ip[0]  =  0;
	if  (  pMem->ulClientIp0  &&  !ulIp2Str(  pMem->ulClientIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
	SetDlgItemText(  IDC_EDIT_clientIp4,  CString(  ip  )  );
	//
	SetDlgItemText(  IDC_EDIT_filter40,  pMem->filter0Buf  );
	SetDlgItemText(  IDC_EDIT_filter41,  pMem->filter1Buf  );
	SetDlgItemText(  IDC_EDIT_filter42,  pMem->contentFilter2Buf  );
	SetDlgItemText(  IDC_EDIT_filter43,  pMem->contentFilter3Buf  );

	//
	pMem  =  &m_var.filters.mems[5];
	ip[0]  =  0;
	if  (  pMem->ulClientIp0  &&  !ulIp2Str(  pMem->ulClientIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
	SetDlgItemText(  IDC_EDIT_clientIp5,  CString(  ip  )  );
	//
	SetDlgItemText(  IDC_EDIT_filter50,  pMem->filter0Buf  );
	SetDlgItemText(  IDC_EDIT_filter51,  pMem->filter1Buf  );
	SetDlgItemText(  IDC_EDIT_filter52,  pMem->contentFilter2Buf  );
	SetDlgItemText(  IDC_EDIT_filter53,  pMem->contentFilter3Buf  );




	//	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgFilters::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
