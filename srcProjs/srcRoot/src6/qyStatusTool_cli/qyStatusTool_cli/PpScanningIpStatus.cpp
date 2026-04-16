// PpScanningIpStatus.cpp : implementation file
//

#include	"stdafx.h"
//  #include	"qyMcMainCommon.h"
//  #include	"qymc.h"
#include	"qyStatusToolCommon.h"
#include	"resource.h"
#include	"qyPs.h"
#include	"PpScanningIpStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpScanningIpStatus property page

IMPLEMENT_DYNCREATE(CPpScanningIpStatus, CPropertyPage)

CPpScanningIpStatus::CPpScanningIpStatus() : CPropertyPage(CPpScanningIpStatus::IDD)
{
	//{{AFX_DATA_INIT(CPpScanningIpStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPpScanningIpStatus::~CPpScanningIpStatus()
{
}

void CPpScanningIpStatus::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpScanningIpStatus)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpScanningIpStatus, CPropertyPage)
	//{{AFX_MSG_MAP(CPpScanningIpStatus)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_MESSAGE(  QY_WM_COMM,  OnQyComm  )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpScanningIpStatus message handlers

 LRESULT CPpScanningIpStatus::OnQyComm(  WPARAM wParam,  LPARAM lParam  )
{
	long					lRet				=					-1;
	QY_WMBUF_COMM		*	pComm				=					( QY_WMBUF_COMM * )lParam;
	TCHAR					tBuf[1024];
	
	if  (  !pComm  )  goto  errLabel;

	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_show:  {
				  QY_SHOW_STRUCT	*	pShowStruct  =  &(  (  QNM_WMBUF_SHOWSTRUCT  *  )pComm  )->showStruct;
				  
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s%s%s"  ),  pShowStruct->who_from,  pShowStruct->whereBuf,  pShowStruct->doStr,  pShowStruct->what  );
				  switch  (  pShowStruct->iType  )  {
						  case  CONST_qyShowType_scanningNetworkSegment:
					  		    SetDlgItemText(  IDC_STATIC_scanningNetworkSegment,  tBuf  );
								break;
						  case  CONST_qyShowType_scanningIp:
							    SetDlgItemText(  IDC_STATIC_scanningIp,  tBuf  );
								break;
						  case  CONST_qyShowType_serviceStatus:
							    if  (  !lstrcmpi(  pShowStruct->who_from,  qyGetDesByType1(  CONST_qyServiceIdTable,  CONST_qyServiceId_is  )  )  )  break;
							    SetDlgItemText(  IDC_STATIC_serviceStatus_netMc,  tBuf  );
								break;
						  case  CONST_qyShowType_refresh:
							    traceLogA(  "¿ÉÒÔË¢ÐÂ×´Ì¬"  );
							    break;
						  case  CONST_qyShowType_bhbScanningNetworkSegment:
							    SetDlgItemText(  IDC_STATIC_bhbScanningNetworkSegment,  tBuf  );
								break;
						  default:
							      break;
					}
				  				  
					}
				  break;
			default:					
					break;
	}

errLabel:
	return  lRet;
}


BOOL CPpScanningIpStatus::OnSetActive() 
{
	CQyPs  *  pPs  =  (  CQyPs  *  )GetParent(  );
	QY_STATUS_STRUCT	*	pStatusStruct	=  &pPs->m_var.u.showInfo.statusStruct;

	cusDlgRes(  0,  &pStatusStruct->cusRes,  this->m_hWnd,  this->IDD  );



	pPs->m_var.u.showInfo.iShowFlgs[0]  =  (  1  <<  CONST_qyShowType_scanningNetworkSegment  )
											|  (  1  <<  CONST_qyShowType_scanningIp  )
												|  (  1  <<  CONST_qyShowType_serviceStatus  )
													|  (  1  <<  CONST_qyShowType_refresh  )
														|  (  1  <<  CONST_qyShowType_bhbScanningNetworkSegment  );
	
	BOOL	bStarted  =  FALSE;
	char	buf[128];
	
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_startIpScan  ),  buf,  sizeof(  buf  )  )  )  {
		if  (  atol(  buf  )  ==  1  )  bStarted  =  TRUE;
	}

	SetDlgItemText(  IDC_STATIC_ipScan,  bStarted  ?  _T(  "Æô¶¯IPÉ¨Ãè¼ì²â"  )  :  _T(  "Í£Ö¹IPÉ¨Ãè¼ì²â"  )  );

	return CPropertyPage::OnSetActive();
}
