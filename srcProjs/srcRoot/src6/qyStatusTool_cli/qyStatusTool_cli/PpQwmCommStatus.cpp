// PpQwmCommStatus.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyStatusToolCommon.h"
#include	"resource.h"
#include	"qyPs.h"
#include	"PpQwmCommStatus.h"
#include	"dlgFilters.h"
#include	"qyCusResPublic.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPpQwmCommStatus property page

IMPLEMENT_DYNCREATE(CPpQwmCommStatus, CPropertyPage)

CPpQwmCommStatus::CPpQwmCommStatus() : CPropertyPage(CPpQwmCommStatus::IDD)
{
	//{{AFX_DATA_INIT(CPpQwmCommStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CPpQwmCommStatus::~CPpQwmCommStatus()
{
}

void CPpQwmCommStatus::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpQwmCommStatus)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpQwmCommStatus, CPropertyPage)
	//{{AFX_MSG_MAP(CPpQwmCommStatus)
	ON_CBN_SELCHANGE(IDC_COMBO_select, OnSelchangeCOMBOselect)
	ON_BN_CLICKED(IDC_CHECK_autoClearup, OnCHECKautoClearup)
	//}}AFX_MSG_MAP
	ON_MESSAGE(  QY_WM_COMM,  OnQyComm  )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpQwmCommStatus message handlers

 char  *  myDisplayTime(  SYSTEMTIME  *  when,  char  *  displayBuf,  unsigned  int  size  )
{
	char  *  ptr  =  displayBuf;

	if  (  size  <  32  )  return  NULL;

	_snprintf(  displayBuf,  size,  
				"%04d-%02d-%02d %02d:%02d:%02d::%03d", 
					when->wYear,  
						when->wMonth,  
							when->wDay,  
								when->wHour,  
									when->wMinute,  
										when->wSecond,
											when->wMilliseconds  );

	
	return ptr;

}


 LRESULT CPpQwmCommStatus::OnQyComm(  WPARAM wParam,  LPARAM lParam  )
{
	long					lRet				=					-1;
	QY_WMBUF_COMM		*	pComm				=					( QY_WMBUF_COMM * )lParam;
	TCHAR					tBuf[1024];
	int						iCurSel;
	
	if  (  !pComm  )  goto  errLabel;

	traceLogA(  "CPpQwmCommStatus::OnQyComm  enters"  );

	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_show:  {
				  QY_SHOW_STRUCT	*	pShowStruct				=	&(  (  QNM_WMBUF_SHOWSTRUCT  *  )pComm  )->showStruct;
				  char					clientIp[128  +  1]		=	"";
				  char					displayBuf[128];
				  CString				fromStr,  toStr;
				  BOOL					bWatching				=	TRUE;

				  
				  switch  (  pShowStruct->iType  )  {
						  case  CONST_qyShowType_qwmComm:
						  case  CONST_qyShowType_sysInfo:
						  case  CONST_qyShowType_debug:
						  case  CONST_qyShowType_debugWarning:
						  case  CONST_qyShowType_warning:
							  								
							    if  (  m_var.ulClientIp0  ||  m_var.filter0Buf[0]  ||  m_var.filter1Buf[0]  )  {
									fromStr  =  CString(  pShowStruct->who_from  );  fromStr.MakeUpper(  );
									toStr  =  CString(  pShowStruct->who_to  );  toStr.MakeUpper(  );
									//
									bWatching  =  FALSE;
									if  (  m_var.ulClientIp0  )  {
										if  (  pShowStruct->ulClientIp  ==  m_var.ulClientIp0  )  bWatching  =  TRUE;
									}
#if  0
									if  (  m_var.ulClientIp1  )  {
										if  (  pShowStruct->ulClientIp  ==  m_var.ulClientIp1  )  bWatching  =  TRUE;
									}
#endif
									if  (  m_var.filter0Buf[0]  )  {
										if  (  _tcsstr(  fromStr,  m_var.filter0Buf  )  ||  _tcsstr(  toStr,  m_var.filter0Buf  )  )  bWatching  =  TRUE;
									}									
									if  (  m_var.filter1Buf[0]  )  {																				
										if  (  _tcsstr(  fromStr,  m_var.filter1Buf  )  ||  _tcsstr(  toStr,  m_var.filter1Buf  )  )  bWatching  =  TRUE;
									}
							  	}
								if  (  !bWatching  )  break;

							    if  (  m_var.nItems  >=  CONST_maxnItemsInListBox_client  &&  !m_var.bAutoClearup  )  break;
								
								if  (  m_var.nItems  >=  CONST_maxnItemsInListBox_client  )  {
									GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_RESETCONTENT,  0,  0  );
									m_var.nItems  =  0;
								}
								//  
								myDisplayTime(  &pShowStruct->when,  displayBuf,  mycountof(  displayBuf  )  );
								if  (  !pShowStruct->ulClientIp  ||  !ulIp2Str(  pShowStruct->ulClientIp,  clientIp,  mycountof(  clientIp  )  )  )  clientIp[0]  =  0;
								if  (  pShowStruct->who_to[0]  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%S  %-15S %-15s %-6s %s%s"  ),  (  displayBuf  ),  clientIp,  CString(  pShowStruct->who_from  )  +  " -> "  +  pShowStruct->who_to,  pShowStruct->whereBuf,  pShowStruct->doStr,  pShowStruct->what  );
								else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%S  %-15S %-15s %-6s %s%s"  ),  (  displayBuf  ),  clientIp,  pShowStruct->who_from,  pShowStruct->whereBuf,  pShowStruct->doStr,  pShowStruct->what  );
								traceLogA(  "qwmComm:  %S",  tBuf  );
							    //  
								//  注意，要在加入之前先获取iCurSel, 因为排序功能会在加入后，重新调整的, 2007/06/01
								iCurSel  =  GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_GETCURSEL,  0,  0  );
								//
								GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_ADDSTRING,  0,  (  LPARAM  )tBuf  );
								//  2006/04/16
								if  (  iCurSel  ==  LB_ERR  ||  iCurSel  ==  m_var.nItems  -  1  )  {
									GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_SETCURSEL,  m_var.nItems,  0  );
								}
								//
								m_var.nItems  ++  ;
								break;
						  case  CONST_qyShowType_serviceStatus:
						  case  CONST_qyShowType_qmdState:
							    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s%s%s"  ),  pShowStruct->who_from,  pShowStruct->whereBuf,  pShowStruct->doStr,  pShowStruct->what  );
							#if  0
								if  (  !lstrcmpi(  pShowStruct->who_from,  qyGetDesByType1(  CONST_qyServiceIdTable,  CONST_qyServiceId_is  )  )  )  SetDlgItemText(  IDC_STATIC_serviceStatus_is,  tBuf  );
								else  SetDlgItemText(  IDC_STATIC_serviceStatus_netMc,  tBuf  );
							#endif
								switch  (  pShowStruct->iPos_toDisplay  )  {
									    case  0:
											   SetDlgItemText(  IDC_STATIC_serviceStatus_is,  tBuf  );
											   break;
										case  1:
										default:
											   SetDlgItemText(  IDC_STATIC_serviceStatus_netMc,  tBuf  );
											   break;
								}
								//
								break;
						  default:
							      break;
					}
				  				  
					}
				  break;
			default:					
					break;
	}

	lRet  =  0;

errLabel:

	traceLogA(  "CPpQwmCommStatus::OnQyComm  leaves"  );

	return  lRet;
}


 BOOL  CPpQwmCommStatus::OnSetActive() 
{
	CQyPs  *  pPs	=  (  CQyPs  *  )GetParent(  );
	QY_STATUS_STRUCT	*	pStatusStruct	=  &pPs->m_var.u.showInfo.statusStruct;

	cusDlgRes(  0,  &pStatusStruct->cusRes,  this->m_hWnd,  this->IDD  );

	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_RESETCONTENT,  0,  0  );
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_communicationStatus  )  );
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_communicationStatusWithFilters  )  );
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_SETCURSEL,  m_var.iCurSel,  0  );

	pPs->m_var.u.showInfo.iShowFlgs[0]  =  (  1  <<  CONST_qyShowType_serviceStatus  )
											|  (  1  <<  CONST_qyShowType_qwmComm  )
												|  (  1  <<  CONST_qyShowType_qmdState  )
													|  (  1  <<  CONST_qyShowType_sysInfo  )
														|  (  1  <<  CONST_qyShowType_debug  )
															|  (  1  <<  CONST_qyShowType_debugWarning  )
																|  (  1  <<  CONST_qyShowType_warning  );


	BOOL	bStopped		=	FALSE;
	BOOL	bNotAllAllowed	=	FALSE;
	char	buf[128];
	TCHAR	tBuf[128];
	
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_stopMon  ),  buf,  sizeof(  buf  )  )  )  {
		if  (  atol(  buf  )  ==  1  )  bStopped  =  TRUE;
	}
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),   _T(  CONST_regValName_bNotAllAllowed  ),  buf,  sizeof(  buf  )  )  )  {
		if  (  atol(  buf  )  ==  1  )  bNotAllAllowed  =  TRUE;		
	}
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  bStopped  ?  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_uninstallClient  )  :  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_allClientsAllowed  )  );  
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  ),  _T(  "%s,%s"  ),  tBuf,  bNotAllAllowed  ?  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_onlyMgrRegList  )  :  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_mgrAnyOne  )  );
	
	SetDlgItemText(  IDC_STATIC_nm,  tBuf  );

	//  GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_RESETCONTENT,  0,  0  );

	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  ),  _T(  "%d %s"  ),  CONST_maxnItemsInListBox_client,  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_hintToEmpty  )  );
	SetDlgItemText(  IDC_CHECK_autoClearup,  tBuf  );

	return  CPropertyPage::OnSetActive();
}

 void  CPpQwmCommStatus::OnSelchangeCOMBOselect() 
{
  	CQyPs				*	pPs				=  (  CQyPs  *  )GetParent(  );
	QY_STATUS_STRUCT	*	pStatusStruct	=  &pPs->m_var.u.showInfo.statusStruct;
	char					ip[128]			=	"";
	unsigned  long			ulIp0			=	0;
	unsigned  long			ulIp1			=	0;
	CString					str0,  str1;

	int	 iCurSel  =  GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_GETCURSEL,  0,  0  );
	
	if  (  iCurSel  ==  CB_ERR  )  return;

	switch  (  iCurSel  )  {
			case  0:
					GetDlgItem(  IDC_STATIC_clientIp0  )->ShowWindow(  SW_HIDE  );
					GetDlgItem(  IDC_STATIC_clientIp1  )->ShowWindow(  SW_HIDE  );
				    GetDlgItem(  IDC_STATIC_filter0  )->ShowWindow(  SW_HIDE  );					
					GetDlgItem(  IDC_STATIC_filter1  )->ShowWindow(  SW_HIDE  );
					break;
			case  1:  {
					  CDlgFilters	dlg;
				  

					  //dlg.bSetDlgInfo(  0,  this->m_hWnd,  m_var.ulClientIp0,  m_var.filter0Buf,  m_var.filter1Buf,  _T(  ""  ),  _T(  ""  )  );
					  dlg.bSetDlgInfo(  0,  this->m_hWnd,  &m_var.filters  );
					  if  (  dlg.DoModal(  )  !=  IDOK  )  {
						  GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_SETCURSEL,  0,  0  );
						  GetDlgItem(  IDC_STATIC_clientIp0  )->ShowWindow(  SW_HIDE  );
						  GetDlgItem(  IDC_STATIC_clientIp1  )->ShowWindow(  SW_HIDE  );
						  GetDlgItem(  IDC_STATIC_filter0  )->ShowWindow(  SW_HIDE  );					
						  GetDlgItem(  IDC_STATIC_filter1  )->ShowWindow(  SW_HIDE  );					
						  iCurSel  =  0;
						  break;  
					  }
					  //
					  GetDlgItem(  IDC_STATIC_clientIp0  )->ShowWindow( SW_SHOW  );
					  //ulIp0  =  dlg.m_var.ulClientIp0;
					  ip[0]  =  0;
					  if  (  ulIp0  &&  !ulIp2Str(  ulIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
					  SetDlgItemText(  IDC_STATIC_clientIp0,  CString(  ip  )  );
					  //
#if  0
					  GetDlgItem(  IDC_STATIC_clientIp1  )->ShowWindow( SW_SHOW  );
					  ulIp1  =  dlg.m_var.ulClientIp1;
					  ip[0]  =  0;
					  if  (  ulIp1  &&  !ulIp2Str(  ulIp1,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
					  SetDlgItemText(  IDC_STATIC_clientIp1,  CString(  ip  )  );
#endif
					  //
#if  0
					  GetDlgItem(  IDC_STATIC_filter0  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter0,  CString(  dlg.m_var.filter0Buf  )  );
					  GetDlgItem(  IDC_STATIC_filter1  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter1,  CString(  dlg.m_var.filter1Buf  )  );
					  //
					  str0  =  CString(  dlg.m_var.filter0Buf  );
					  str0.TrimLeft(  );  str0.TrimRight(   );  str0.MakeUpper(  );
					  str1  =  CString(  dlg.m_var.filter1Buf  );
					  str1.TrimLeft(  );  str1.TrimRight(  );  str1.MakeUpper(  );
#endif
					  }
					break;
			default:
					break;
	}
	m_var.iCurSel  =  iCurSel;

	if  (  ulIp0  !=  m_var.ulClientIp0  ||  str0  !=  CString(  m_var.filter0Buf  )  ||  str1  !=  CString(  m_var.filter1Buf  )  )  {
		m_var.ulClientIp0  =  ulIp0;
		//m_var.ulClientIp1  =  ulIp1;
		lstrcpyn(  m_var.filter0Buf,  str0,  mycountof(  m_var.filter0Buf  )  );
		lstrcpyn(  m_var.filter1Buf,  str1,  mycountof(  m_var.filter1Buf  )  );
		//
		GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_RESETCONTENT,  0,  0  );
		m_var.nItems  =  0;
	}
	
}



void CPpQwmCommStatus::OnCHECKautoClearup() 
{

	if  (  BST_CHECKED  ==  GetDlgItem(  IDC_CHECK_autoClearup  )->SendMessage(  BM_GETCHECK,  0,  0  )  )  {
		m_var.bAutoClearup  =  TRUE;
		}
	else  m_var.bAutoClearup  =  FALSE;
}


