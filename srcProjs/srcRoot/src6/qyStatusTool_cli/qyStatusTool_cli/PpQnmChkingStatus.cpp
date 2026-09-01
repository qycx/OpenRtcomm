// PpQnmChkingStatus.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyStatusToolCommon.h"
#include	"resource.h"
#include	"PpQnmChkingStatus.h"
#include	"qyPs.h"
#include	"dlgIp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpQnmChkingStatus property page

IMPLEMENT_DYNCREATE(CPpQnmChkingStatus, CPropertyPage)

 CPpQnmChkingStatus::CPpQnmChkingStatus() : CPropertyPage(CPpQnmChkingStatus::IDD)
{
	//{{AFX_DATA_INIT(CPpQnmChkingStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CPpQnmChkingStatus::~CPpQnmChkingStatus()
{
}

void CPpQnmChkingStatus::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpQnmChkingStatus)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpQnmChkingStatus, CPropertyPage)
	//{{AFX_MSG_MAP(CPpQnmChkingStatus)
	ON_BN_CLICKED(IDC_CHECK_autoClearup, OnCHECKautoClearup)
	ON_CBN_SELCHANGE(IDC_COMBO_select, OnSelchangeCOMBOselect)
	//}}AFX_MSG_MAP
	ON_MESSAGE(  CONST_qyWm_comm,  OnQyComm  )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpQnmChkingStatus message handlers

 BOOL CPpQnmChkingStatus::OnSetActive() 
{

	CQyPs				*	pPs				=  (  CQyPs  *  )GetParent(  );
	QY_STATUS_STRUCT	*	pStatusStruct	=  &pPs->m_var.u.showInfo.statusStruct;

	cusDlgRes(  0,  &pStatusStruct->cusRes,  this->m_hWnd,  this->IDD  );

	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_RESETCONTENT,  0,  0  );
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )CONST_showWho_all  );
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )CONST_showWho_nbtScan  );
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )CONST_showWho_snmpScan  );
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_SETCURSEL,  m_var.iCurSel,  0  );
	
	pPs->m_var.u.showInfo.iShowFlgs[0]  =  (  1  <<  CONST_qyShowType_serviceStatus  )
											|  (  1  <<  CONST_qyShowType_qnmChking  )
												|  (  1  <<  CONST_qyShowType_addChkingType  );
	
	
	BOOL	bRegScanStarted			=  FALSE;
	BOOL	bRespForUnregStarted	=  FALSE;
	char	buf[128];
	TCHAR	tBuf[128];
	
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_startRegScan  ),  buf,  sizeof(  buf  )  )  )  {
		if  (  atol(  buf  )  ==  1  )  bRegScanStarted  =  TRUE;
	}
	if  (  bRegScanStarted  )  {
		if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_startRespForUnreg  ),  buf,  sizeof(  buf  )  )  )  {
			if  (  atol(  buf  )  ==  1  )  bRespForUnregStarted  =  TRUE;
		}
	}
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  bRegScanStarted  ?  _T(  "启动注册检查"  )  :  _T(  "停止注册检查"  )  );
	if  (  bRegScanStarted  &&  bRespForUnregStarted  )  _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  ),  _T(  "%s, %s"  ),  tBuf,  bRespForUnregStarted  ?  _T(  "启动阻断未注册主机"  )  :  _T(  "停止阻断未注册主机"  )  );

	SetDlgItemText(  IDC_STATIC_nm,  tBuf  );

	//  GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_RESETCONTENT,  0,  0  );

	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  ),  _T(  "满%d条自动清空"  ),  CONST_maxnItemsInListBox_client  );
	SetDlgItemText(  IDC_CHECK_autoClearup,  tBuf  );

	return  CPropertyPage::OnSetActive();
}

void CPpQnmChkingStatus::OnCHECKautoClearup() 
{
	if  (  BST_CHECKED  ==  GetDlgItem(  IDC_CHECK_autoClearup  )->SendMessage(  BM_GETCHECK,  0,  0  )  )  {
		m_var.bAutoClearup  =  TRUE;
		}
	else  m_var.bAutoClearup  =  FALSE;
}

 char  *  myDisplayTime(  SYSTEMTIME  *  when,  char  *  displayBuf,  unsigned  int  size  );

 LRESULT CPpQnmChkingStatus::OnQyComm(  WPARAM wParam,  LPARAM lParam  )
{
	long					lRet				=					-1;
	QY_WMBUF_COMM		*	pComm				=					( QY_WMBUF_COMM * )lParam;
	int						iCurSel;
	
	if  (  !pComm  )  goto  errLabel;

	//  traceLogA(  "CPpQwmChkingStatus::OnQyComm  enters"  );

	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_show:  {
				  QY_SHOW_STRUCT	*	pShowStruct  =  &(  (  QNM_WMBUF_SHOWSTRUCT  *  )pComm  )->showStruct;
				  char					buf[1024]  =  "";
				  //  char					timeBuf[CONST_qyTimeLen  +  1];
				  char					displayBuf[128];
				  TCHAR					tBuf[1024]	=	_T(  ""  );
				  
				  switch  (  pShowStruct->iType  )  {
						  case  CONST_qyShowType_addChkingType:
							    tTrim(  pShowStruct->who_from  );
							    if  (  !pShowStruct->who_from[0]  )  break;
							    if  (	CB_ERR  !=  GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_FINDSTRING,  -1,  (  LPARAM  )pShowStruct->who_from  )  )  break;
								GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )pShowStruct->who_from  );
							    break;
						  case  CONST_qyShowType_qnmChking:
						  case  CONST_qyShowType_qnmProxyChking:
							  							    
							    if  (  m_var.nItems  >=  CONST_maxnItemsInListBox_client  &&  !m_var.bAutoClearup  )  break;
								
								if  (  m_var.nItems  >=  CONST_maxnItemsInListBox_client  )  {
									GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_RESETCONTENT,  0,  0  );
									m_var.nItems  =  0;
								}
								if  (  m_var.selectedWho[0]  &&  lstrcmpi(  m_var.selectedWho,  pShowStruct->who_from  )  )  break;

								//  getCurTime(  timeBuf  );  qyDisplayTime(  timeBuf,  displayBuf,  sizeof(  displayBuf  )  );
								myDisplayTime(  &pShowStruct->when,  displayBuf,  mycountof(  displayBuf  )  );
								_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  ),  _T(  "%s  %-15s  %s%s%s"  ),  CString(  displayBuf  ),  pShowStruct->who_from,  pShowStruct->whereBuf,  pShowStruct->doStr,  pShowStruct->what  );
								//  traceLogA(  "qnmChking:  %s",  buf  );
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
							    if  (  !lstrcmpi(  pShowStruct->who_from,  qyGetDesByType1(  CONST_qyServiceIdTable,  CONST_qyServiceId_is  )  )  )  break;
								_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s%s%s"  ),  pShowStruct->who_from,  pShowStruct->whereBuf,  pShowStruct->doStr,  pShowStruct->what  );
								SetDlgItemText(  IDC_STATIC_serviceStatus_netMc,  tBuf  );
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

	//  traceLogA(  "CPpQwmChkingStatus::OnQyComm  leaves"  );

	return  lRet;
}

 void CPpQnmChkingStatus::OnSelchangeCOMBOselect() 
{	
	int	 iCurSel  =  GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_GETCURSEL,  0,  0  );
	
	traceLogA(  "CPpQnmChkingStatus::OnSelchangeCOMBOselect enters"  );

	if  (  iCurSel  ==  CB_ERR  )  return;
	
	GetDlgItemText(  IDC_COMBO_select,  m_var.selectedWho,  sizeof(  m_var.selectedWho  )  );
	if  (  !lstrcmp(  m_var.selectedWho,  CONST_showWho_all  )  )  m_var.selectedWho[0]  =  0;

	m_var.iCurSel  =  iCurSel;


}


