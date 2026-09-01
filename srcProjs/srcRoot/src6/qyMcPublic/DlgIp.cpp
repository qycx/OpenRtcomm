// DlgIp.cpp : implementation file
//

#include	"stdafx.h"
#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#include	<mmreg.h>
	#include	"myMSAcm.h"
#endif

#include	"qmCommon.h"
//	#include	"qyMcMainCommon.h"
//	#include	"qymc.h"
#include	"myresource.h"
#include	"DlgIp.h"
#include	"qnmResDefs.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIp dialog


 CDlgIp::CDlgIp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIp)
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

 BOOL  CDlgIp::bSetDlgInfo(  int  type,  HWND  hParent,  LPCTSTR  title,  LPCTSTR  okName,  LPCTSTR  cancelName  )
{
	 m_var.type  =  type;
	 m_var.hParent  =  hParent;
	 if  (  title  )  _sntprintf(  m_var.title,  mycountof(  m_var.title  ),  _T(  "%s"  ),  title  );
	 if  (  okName  )  lstrcpyn(  m_var.okName,  okName,  mycountof(  m_var.okName  )  );
	 if  (  cancelName  )  lstrcpyn(  m_var.cancelName,  cancelName,  mycountof(  m_var.cancelName  )  );
	 
	 return  TRUE;
}

void CDlgIp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIp)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIp, CDialog)
	//{{AFX_MSG_MAP(CDlgIp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIp message handlers

 BOOL CDlgIp::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	if  (  m_var.title[0]  )  SetWindowText(  CString(  m_var.title  )  );
	if  (  m_var.okName[0]  )  SetDlgItemText(  IDOK,  CString(  m_var.okName  )  );
	if  (  m_var.cancelName[0]  )  SetDlgItemText(  IDCANCEL,  CString(  m_var.cancelName  )  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgIp::OnOK() 
{
	struct  in_addr		tmpInAddr;
	long				hStartIp;

	if  (  4  !=  ::SendMessage(  GetDlgItem(  IDC_IP  )->m_hWnd,  IPM_GETADDRESS,  0,  (  LPARAM  )&hStartIp  )  )  {
		 AfxMessageBox(  _T(  "Invalid IP address"  )  );
		 GetDlgItem(  IDC_IP  )->SetFocus(  );
		 return;
	 }
	 tmpInAddr.s_addr  =  qyhtonl(  hStartIp  );
	 _snprintf(  m_var.ipBuf,  sizeof(  m_var.ipBuf  ),  "%s",  inet_ntoa(  tmpInAddr  )  );
	
	if  (  m_var.type  ==  CONST_qyDlgType_continuousAdd  )  {
		QY_WMBUF_ADDIP		tmpComm;

		tmpComm.uiType  =  CONST_qyWmParam_addIp;
		_snprintf(  tmpComm.ipBuf,  sizeof(  tmpComm.ipBuf  ),  "%s",  m_var.ipBuf  );
		::SendMessage(  m_var.hParent,  CONST_qyWm_comm,  0,  (  LPARAM  )&tmpComm  );
		GetDlgItem(  IDC_IP  )->SendMessage(  IPM_CLEARADDRESS,  0,  0  );
		GetDlgItem(  IDC_IP  )->SendMessage(  IPM_SETFOCUS,  0,  0  );
		return;
	}

	CDialog::OnOK();
}


