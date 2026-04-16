// PpQnmClearup.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"
#include	"myresource.h"
#include	"qyPs.h"
#include	"PpQnmClearup.h"
#include ".\ppqnmclearup.h"
#include	"qyCusResTemp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpQnmClearup property page

IMPLEMENT_DYNCREATE(CPpQnmClearup, CPropertyPage)

CPpQnmClearup::CPpQnmClearup() : CPropertyPage(CPpQnmClearup::IDD)
{
	//{{AFX_DATA_INIT(CPpQnmClearup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPpQnmClearup::~CPpQnmClearup()
{
}

void CPpQnmClearup::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpQnmClearup)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpQnmClearup, CPropertyPage)
	//{{AFX_MSG_MAP(CPpQnmClearup)
	ON_BN_CLICKED(IDC_RADIO_clearupScannedIp, OnRADIOclearupScannedIp)
	ON_BN_CLICKED(IDC_RADIO_clearupEvent, OnRADIOclearupEvent)
	ON_BN_CLICKED(IDC_RADIO_procModuleKnowlege, OnRADIOprocModuleKnowlege)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RADIO_procRegistryKnowlege, OnBnClickedRadioprocregistryknowlege)
//	ON_BN_CLICKED(IDC_RADIO_procImMsg, OnBnClickedRadioprocimmsg)
ON_BN_CLICKED(IDC_RADIO_procImMsg, OnBnClickedRadioprocimmsg)
ON_BN_CLICKED(IDC_RADIO_procImHisTask, OnBnClickedRadioprocimhistask)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpQnmClearup message handlers

 BOOL CPpQnmClearup::OnSetActive() 
{
	CQyPs	*	pPs						=  (  CQyPs  *  )GetParent(  );
	QY_MC	*	pQyMc					=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  pPs->m_var.iType  !=  CONST_qyPsType_clearup  )  pPs->PostMessage(  WM_CLOSE,  0,  0  );
	else  {
		  GetDlgItem(  IDC_RADIO_clearupEvent  )->SendMessage(  BM_SETCHECK ,  BST_CHECKED,  0  );
		  pPs->SetWizardButtons(  PSWIZB_NEXT  );
	}

	GetDlgItem(  IDC_RADIO_clearupEvent  )->ShowWindow(  SW_SHOW  );

	if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_netMc  )  {
		//  
		if  (  pQyMc->cfg.pGuiCfg->iSystemId  ==  CONST_qySystemId_netMc2  )  {
			GetDlgItem(  IDC_RADIO_clearupScannedIp  )->ShowWindow(  SW_SHOW  );
			GetDlgItem(  IDC_RADIO_procModuleKnowlege  )->ShowWindow(  SW_SHOW  );
			GetDlgItem(  IDC_RADIO_procRegistryKnowlege  )->ShowWindow(  SW_SHOW  );
		}

		}
	else  {
		  GetDlgItem(  IDC_RADIO_procImMsg  )->ShowWindow(  SW_SHOW  );
		  GetDlgItem(  IDC_RADIO_procImHisTask  )->ShowWindow(  SW_SHOW  );
	}


	return CPropertyPage::OnSetActive();
}

void CPpQnmClearup::OnRADIOclearupScannedIp() 
{
	CQyPs	*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
	
}

void CPpQnmClearup::OnRADIOclearupEvent() 
{
	CQyPs	*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_NEXT  );
	
}

void CPpQnmClearup::OnRADIOprocModuleKnowlege() 
{
	// TODO: Add your control notification handler code here
	CQyPs	*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
	
}


void CPpQnmClearup::OnBnClickedRadioprocregistryknowlege()
{
	// TODO: 在此添加控件通知处理程序代码
	CQyPs	*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );

}

void CPpQnmClearup::OnBnClickedRadioprocimmsg()
{
	// TODO: 在此添加控件通知处理程序代码
	CQyPs	*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_NEXT  );

}

void CPpQnmClearup::OnBnClickedRadioprocimhistask()
{
	// TODO: 在此添加控件通知处理程序代码
	CQyPs	*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_NEXT  );
}


BOOL CPpQnmClearup::OnWizardFinish() 
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	CQyPs	*	pPs		=  (  CQyPs  *  )GetParent(  );
	
	if  (  GetDlgItem(  IDC_RADIO_clearupScannedIp  )->SendMessage(  BM_GETCHECK ,  0,  0  )  ==  BST_CHECKED  )  {
		if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_clearBhbVerify  ),  MB_YESNO  )  !=  IDYES  )  return  FALSE;
		pPs->m_var.u.clearupInfo.iTask  =  CONST_qyPsTask_clearupScannedIp;
		}
	else  if  (  GetDlgItem(  IDC_RADIO_procModuleKnowlege  )->SendMessage(  BM_GETCHECK ,  0,  0  )  ==  BST_CHECKED  )  {
			  pPs->m_var.u.clearupInfo.iTask  =  CONST_qyPsTask_procPcProcessKnowledge;
			}
	else  if  (  GetDlgItem(  IDC_RADIO_procRegistryKnowlege  )->SendMessage(  BM_GETCHECK ,  0,  0  )  ==  BST_CHECKED  )  {
			  pPs->m_var.u.clearupInfo.iTask  =  CONST_qyPsTask_procPcRegistryKnowledge;
	}

	return  CPropertyPage::OnWizardFinish();

}

LRESULT CPpQnmClearup::OnWizardNext() 
{
	// TODO: Add your specialized code here and/or call the base class
	CQyPs	*	pPs  =  (  CQyPs  *  )GetParent(  );
	
	if  (  GetDlgItem(  IDC_RADIO_clearupEvent  )->SendMessage(  BM_GETCHECK ,  0,  0  )  ==  BST_CHECKED  )  {
		      pPs->m_var.u.clearupInfo.iTask  =  CONST_qyPsTask_clearupEvent;
			  }
	else  if  (  GetDlgItem(  IDC_RADIO_procImMsg  )->SendMessage(  BM_GETCHECK ,  0,  0  )  ==  BST_CHECKED  )  {
		      pPs->m_var.u.clearupInfo.iTask  =  CONST_qyPsTask_procImMsg;
			  }
	else  if  (  GetDlgItem(  IDC_RADIO_procImHisTask  )->SendMessage(  BM_GETCHECK ,  0,  0  )  ==  BST_CHECKED  )  {
		      pPs->m_var.u.clearupInfo.iTask  =  CONST_qyPsTask_procImHisTask;
			  
	}

	
	return CPropertyPage::OnWizardNext();
}




