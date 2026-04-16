// DlgRtspUrl.cpp : implementation file
//

#include "stdafx.h"
#include "myresource.h"
#include	"qyMcMainCommon.h"
#include "DlgRtspUrl.h"
#include "afxdialogex.h"
#include	"dlgShareDynBmpsProc.h"
#include	"isCliHelpPublic.h"

#include	"qyMessengerHelpPublic.h"


//
__declspec(  dllexport  )  int  toEditRtspUrlForConf(  TCHAR  *  url,  unsigned  int  cnt  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int  iErr  =  -1;
		
	CDlgRtspUrl   dlg;

	//  2016/06/16	
	BOOL  bEditRtspUrlForConf  =  TRUE;				  
	dlg.bSetDlgInfo(  bEditRtspUrlForConf  );
				  
	//	
	if  (  dlg.DoModal( )  !=  IDOK  )  {					  	
		return  -1;
	}

	//
	//safeTcsnCpy(  dlg.m_var.itemUrl.tUrl,  url,  cnt  );
	myUtf82TChar(  dlg.m_var.rule.url,  url,  cnt  );

	//
	return  0;
}



// CDlgRtspUrl dialog

IMPLEMENT_DYNAMIC(CDlgRtspUrl, CDialogEx)

CDlgRtspUrl::CDlgRtspUrl(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRtspUrl::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


CDlgRtspUrl::~CDlgRtspUrl()
{
}

void CDlgRtspUrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRtspUrl, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgRtspUrl::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_type, &CDlgRtspUrl::OnCbnSelchangeCombotype)
END_MESSAGE_MAP()



// CDlgRtspUrl message handlers


void CDlgRtspUrl::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	QY_MC		*	pQyMc	=	QY_GET_GBUF();
	if  (  !pQyMc  )  goto  errLabel;

	TCHAR			tCfgName[256]  =  _T(  ""  );
	TCHAR			tVal[256]  =  _T(  ""  );
	QY_REG			reg;
	memset(  &reg,  0,  sizeof(  reg  )  );
	TCHAR			tBuf[256];
	char			buf[128];

	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//safeTcsnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	getRegRootKey_qmc(  m_var.uiCapType,  m_var.uiSubCapType,  0,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	if  (  !m_var.bEditRtspUrlForConf  )  {
		_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"   ),  reg.rootKey,  _T(  CONST_regKeyName_rtspUrl  )  );
	}


	//
	GetDlgItemText(  IDC_COMBO_type,  tBuf,  mycountof(  tBuf  )  );
	m_var.rule.iOnvifRuleType  =  qyGetTypeByDes(  CONST_onvifRuleTypeTable,  tBuf  );

	//
	GetDlgItemText(  IDC_EDIT_rtspUrl,  tBuf,  mycountof(  tBuf  )  );
	tTrim(  tBuf  );
	myTChar2Utf8(  tBuf,  m_var.rule.url,  mycountof(  m_var.rule.url  ) );
	
	GetDlgItemText(  IDC_EDIT_name,  m_var.rule.cusName,  mycountof(  m_var.rule.cusName  )  );	
	tTrim(  m_var.rule.cusName  );

	GetDlgItemText(  IDC_EDIT_usrName,  tBuf,  mycountof(  tBuf  )  );
	myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
	safeStrnCpy(  buf,  m_var.rule.usrName,  mycountof(  m_var.rule.usrName  )  );
	//
	GetDlgItemText(  IDC_EDIT_passwd,  tBuf,  mycountof(  tBuf  )  );
	myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
	safeStrnCpy(  buf,  m_var.rule.passwd,  mycountof(  m_var.rule.passwd  )  );
	//  2016/07/13
	GetDlgItemText(  IDC_EDIT_defToken,  tBuf,  mycountof(  tBuf  )  );
	myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
	safeStrnCpy(  buf,  m_var.rule.defToken,  mycountof(  m_var.rule.defToken  )  );
	

	//
	if  (  m_var.bEditRtspUrlForConf  )  {
		if  (  !m_var.rule.url[0]  )  {
			GetDlgItem(  IDC_EDIT_rtspUrl  )->SetFocus(  );
			return;
		}
		}
	else  {
		  if  (  m_var.rule.iOnvifRuleType  ==  CONST_onvifRuleType_discovery  )  {	
			  m_var.rule.url[0]  =  0;
			  //m_var.itemUrl.cusName[0]  =  0;
			  }
		  else  {
			  if  (  !m_var.rule.url[0]  )  {
				  GetDlgItem(  IDC_EDIT_rtspUrl  )->SetFocus(  );			
				  return;						
			  }
		  }
	}


	//
	if  (  !m_var.bEditRtspUrlForConf  )  {
		m_var.rule.usIndex_obj  =  GetDlgItemInt(  IDC_EDIT_no  );
		if  (  m_var.rule.usIndex_obj  <  MIN_usIndex_obj_rtspUrl  ||  m_var.rule.usIndex_obj  >  MAX_usIndex_obj_rtspUrl  )  {
			qyShowHint(  _T(  "index should be >= 1  and <= 20"  )  );
			return;
		}

	
		_sntprintf(  tCfgName,  mycountof(  tCfgName  ),  _T(  "%d"  ),  (  int  )m_var.rule.usIndex_obj  );
		//  _sntprintf(  tVal,  mycountof(  tVal  ),  _T(  "%s,%s"  ),  m_var.cusName,  m_var.tUrlBuf  );
		getRegVal_webcam_rtspUrl(  &m_var.rule,  tVal,  mycountof(  tVal  )  );
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  tCfgName,  tVal  );

		}
	else  {
		_sntprintf(  tCfgName,  mycountof(  tCfgName  ),  _T(  "%s"  ),  _T(  CONST_regValName_rtspUrl_selected  )  );
		_sntprintf(  tVal,  mycountof(  tVal  ),  _T(  "%s"  ),  CQyString(  m_var.rule.url  )  );
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  tCfgName,  tVal  );
		  
	}


errLabel:

	CDialogEx::OnOK();
}








BOOL CDlgRtspUrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	TCHAR			tBuf[256]	=	_T(  ""  );
	QY_REG  reg;	
	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//lstrcpyn(  reg.rootKey,  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
	getRegRootKey_qmc(  m_var.uiCapType,  m_var.uiSubCapType,  0,  reg.rootKey,  mycountof(  reg.rootKey  )  );
		
	//
	QY_DMITEM  *  pTable;						
	int  idc;
	CComboBox  *  pCb;
	QY_DMITEM  *  pItem;
	//
	pTable  =  CONST_onvifRuleTypeTable;
	idc  =  IDC_COMBO_type;						
	pCb  =  (  CComboBox  *  )GetDlgItem(  idc  );
	pCb->ResetContent(  );
	for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  pCb->AddString(  CQyString(  pItem->des  )  );

	//
	if  (  !m_var.bEditRtspUrlForConf  )  {
		SetDlgItemInt(  IDC_EDIT_no,  m_var.rule.usIndex_obj  );
		//
		if  (  m_var.bNew  )  {
			pCb->SetCurSel(  0  );
			}
		else  {
			  //		
			  pCb->SelectString(  -1,  qyGetDesByType1(  pTable,  m_var.rule.iOnvifRuleType  )  );		
			  //
			  if  (  m_var.rule.cusName[0]  )  SetDlgItemText(  IDC_EDIT_name,  m_var.rule.cusName  );		
			  if  (  m_var.rule.url[0]  )  SetDlgItemText(  IDC_EDIT_rtspUrl,  CQyString(  m_var.rule.url  )  );
			  if  (  m_var.rule.usrName[0]  )  SetDlgItemText(  IDC_EDIT_usrName,  CQyString(  m_var.rule.usrName  )  );
			  if  (  m_var.rule.passwd[0]  )  SetDlgItemText(  IDC_EDIT_passwd,  CQyString(  m_var.rule.passwd  )  );
			  //
			  if  (  m_var.rule.defToken[0]  )  SetDlgItemText(  IDC_EDIT_defToken,  CQyString(  m_var.rule.defToken  )  );

		}
		//
		OnCbnSelchangeCombotype(  );
		}
	else  {
		  tBuf[0]  = 0;
		  if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_rtspUrl_selected  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  0 )  )  {
			  myTChar2Utf8(  tBuf,  m_var.rule.url,  mycountof(  m_var.rule.url  )  );
			  SetDlgItemText(  IDC_EDIT_rtspUrl,  CQyString(  m_var.rule.url  )  );		
		  }
		  //
		  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_no  ),  SW_HIDE  );
		  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_no  ),  SW_HIDE  );

		  int  nCmdShow;

		  nCmdShow  =  SW_HIDE;			
		  
		  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_type  ),  nCmdShow  );			
		  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_COMBO_type  ),  nCmdShow  );

		  //
		  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_name  ),  SW_HIDE  );
		  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_name  ),  SW_HIDE  );

		  //
		  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_usrName  ),  nCmdShow  );	
		  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_usrName  ),  nCmdShow  );
		  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_passwd  ),  nCmdShow  );
		  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_passwd  ),  nCmdShow  );

		  //
		  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_defToken  ),  nCmdShow  );
		  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_defToken  ),  nCmdShow  );


	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



int  getNewIndex_rtspUrlList(  )
{
	QY_REG	reg;

	memset(  &reg,  0,  sizeof(  reg  )  );
	TCHAR			tBuf[256];

	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//safeTcsnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	getRegRootKey_qmc(  CONST_capType_av,  CONST_subCapType_webcam,  0,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"   ),  reg.rootKey,  _T(  CONST_regKeyName_rtspUrl  )  );

	int  i;
	for  (  i  =  MIN_usIndex_obj_rtspUrl;  i  <=  MAX_usIndex_obj_rtspUrl;  i  ++  )  {
		TCHAR  tVal[256];
		 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _ltot(  i,  tBuf,  10  ),  (  char  *  )tVal,  sizeof(  tVal  ),  NULL  )  )  break;
	}
	if  (  i  >  MAX_usIndex_obj_rtspUrl  )  return  0;
	return  i;

}


//  2014/06/10
// int  getRegVal_webcam_rtspUrl(  int  iOnvifRuleType,  LPCTSTR  cusName,  LPCTSTR  tUrlBuf,  BOOL  bDel,  TCHAR  *  tVal,  int  cnt  ) 
__declspec(  dllexport  )  int  getRegVal_webcam_rtspUrl(  Onvif_rule  *  pRule,  TCHAR  *  tVal,  int  cnt  )
{
	_sntprintf(  tVal,  cnt,  _T(  "%d;%s;%s;%s;%s;%s;%d"  ),  pRule->iOnvifRuleType,  pRule->cusName,  CQyString(  pRule->url  ),  CQyString(  pRule->usrName  ),  CQyString(  pRule->passwd  ),  CQyString(  pRule->defToken  ),  pRule->status.bDel  );
	return  0;
}

//
 __declspec(  dllexport  )  int  parseRegVal_webcam_rtspUrl(  LPCTSTR  regVal,  Onvif_rule  *  pItemUrl  )
 {
	 int  iErr  =  -1;

	 TCHAR  *  p0, *p1;
	 TCHAR	tBuf[512];
	 BOOL  bDel  =  FALSE;

	 safeTcsnCpy(  regVal,  tBuf,  mycountof(  tBuf  )  );

			int  ch  =  ';';
			//
			p0  =  tBuf;
			p1  =  _tcschr(  p0,  ch  );
			if  (  !p1  )  goto  errLabel;
			
			//
			*p1  =  0;
			pItemUrl->iOnvifRuleType  =  _ttol(  p0  );

			//
			p0  =  p1;
			p0  ++  ;
			p1  =  _tcschr(  p0,  ch  );
			if  (  !p1  )  goto  errLabel;
			//
			*p1  =  0;
			safeTcsnCpy(  p0,  pItemUrl->cusName,  mycountof(  pItemUrl->cusName  )  );

			//
			p0  =  p1;
			p0  ++  ;
			TCHAR  *  pUrl  =  p0;

			p1  =  _tcschr(  pUrl,  ch  );
			if  (  !p1  )  goto  errLabel;			
			*p1  =  0;			
			myTChar2Utf8(  pUrl,  pItemUrl->url,  mycountof(  pItemUrl->url  )  );
			
			//
			p0  =  p1;
			p0  ++  ;
			p1  =  _tcschr(  p0,  ch  );
			if  (  !p1  )  goto  errLabel;
			*p1  =  0;
			myTChar2Utf8(  p0,  pItemUrl->usrName,  mycountof(  pItemUrl->usrName  )  );
			
			//
			p0  =  p1;
			p0  ++  ;
			p1  =  _tcschr(  p0,  ch  );
			if  (  !p1  )  goto  errLabel;
			*p1  =  0;
			myTChar2Utf8(  p0,  pItemUrl->passwd,  mycountof(  pItemUrl->passwd  )  );
			
			//
			p0  =  p1;
			p0  ++  ;
			p1  =  _tcschr(  p0,  ch  );
			if  (  !p1  )  goto  errLabel;
			*p1  =  0;
			myTChar2Utf8(  p0,  pItemUrl->defToken,  mycountof(  pItemUrl->defToken  )  );
			
			//
			p0  =  p1;
			p0  ++  ;
			p1  =  _tcschr(  p0,  ch  );
			if  (  p1  )  {
				*p1  =  0;
			}
			//			
			bDel  =  _ttol(  p0  );
			
			//
			pItemUrl->status.bDel  =  bDel;

			iErr  =  0;
errLabel:
			return  iErr;

 }



//
BOOL CDlgRtspUrl::bSetDlgInfo(  BOOL  bNew,  unsigned  int  usIndex_obj,  int  iOnvifRuleType,  LPCTSTR  cusName,  char  *  url,  char  *  usrName,  char  *  passwd,  char  *  defToken  )
{
	BOOL	bRet	=	FALSE;
	//
	//m_var.bInWebcamList  =  bInWebcamList;
	//			
	//m_var.bEditRtspUrlForConf  =  !bInWebcamList;	
	//
	m_var.bNew  =  bNew;
	if  (  !bNew  )  {
		m_var.rule.usIndex_obj  =  usIndex_obj;
		//
		//
		m_var.rule.iOnvifRuleType  =  iOnvifRuleType;
		safeTcsnCpy(  cusName,  m_var.rule.cusName,  mycountof(  m_var.rule.cusName  )  );
		//
		safeStrnCpy(  url,  m_var.rule.url,  mycountof(  m_var.rule.url  )  );
		//
		safeStrnCpy(  usrName,  m_var.rule.usrName,  mycountof(  m_var.rule.usrName  )  );
		safeStrnCpy(  passwd,  m_var.rule.passwd,  mycountof(  m_var.rule.passwd  )  );
		//
		safeStrnCpy(  defToken,  m_var.rule.defToken,  mycountof(  m_var.rule.defToken  )  );
		
		}
	else  {
		  m_var.rule.usIndex_obj  =  getNewIndex_rtspUrlList(  );
	}

	//
	if  (  !m_var.bEditRtspUrlForConf  )  {
		m_var.uiCapType  =  CONST_capType_av;
		m_var.uiSubCapType  =  CONST_subCapType_webcam;
	}

	bRet  =  TRUE;

errLabel:

	return  bRet;
}

//
BOOL  CDlgRtspUrl::bSetDlgInfo(  BOOL  bEditRtspUrlForConf  )
{
	m_var.bEditRtspUrlForConf  =  bEditRtspUrlForConf;
	return  TRUE;
}



//
void CDlgRtspUrl::OnCbnSelchangeCombotype()
{
	// TODO: Add your control notification handler code here
	TCHAR  tBuf[128]  =  _T(  ""  );
	GetDlgItemText(  IDC_COMBO_type,  tBuf,  mycountof(  tBuf  )  );
	int  iType  =  qyGetTypeByDes(  CONST_onvifRuleTypeTable,  tBuf  );
	if  (  iType  <  0  )  return;
	//
	BOOL  bShow_name  =  TRUE;
	BOOL  bShow_url  =  TRUE;
	BOOL  bShow_usrName  =  FALSE;
	//
	switch  (  iType  )  {
			case  CONST_onvifRuleType_discovery:
				  bShow_url  =  FALSE;
				  bShow_usrName  =  TRUE;
				  break;
			case  CONST_onvifRuleType_probe:
				  bShow_usrName  =  TRUE;
				  break;
			default:
					break;
	}
	//
	int  nCmdShow  =  SW_SHOW;

	//
	//
	nCmdShow  =  bShow_name  ?  SW_SHOW  :  SW_HIDE;
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_name  ),  nCmdShow  );	
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_name  ),  nCmdShow  );	


	//
	nCmdShow  =  bShow_url  ?  SW_SHOW  :  SW_HIDE;
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_rtspUrl  ),  nCmdShow  );	
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_rtspUrl  ),  nCmdShow  );	
	
	//
	if  (  iType  ==  CONST_onvifRuleType_probe  )  {
		::SetDlgItemText(  m_hWnd,  IDC_STATIC_rtspUrl,  _T(  "URI:"  )  );
		}
	else  {
		  ::SetDlgItemText(  m_hWnd,  IDC_STATIC_rtspUrl,  _T(  "Rtsp Url:"  )  );
	}
	

	//
	nCmdShow  =  bShow_usrName  ?  SW_SHOW  :  SW_HIDE;			
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_usrName  ),  nCmdShow  );	
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_usrName  ),  nCmdShow  );
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_passwd  ),  nCmdShow  );
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_passwd  ),  nCmdShow  );


	return;
}


