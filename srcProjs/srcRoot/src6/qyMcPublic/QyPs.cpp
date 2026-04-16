// QyPs.cpp : implementation file
//

#include	"stdafx.h"
#ifndef  __WINCE__
	#include	<winsvc.h>
	#include	<vfw.h>
#else
	#include	<mmreg.h>
	#include	"myMSAcm.h"
#endif
//
#include	"qmCommon.h"
#include	"QyPs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CQyPs

IMPLEMENT_DYNAMIC(CQyPs, CPropertySheet)

CQyPs::CQyPs(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CQyPs::CQyPs(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


CQyPs::~CQyPs()
{
}


BEGIN_MESSAGE_MAP(CQyPs, CPropertySheet)
	//{{AFX_MSG_MAP(CQyPs)
	ON_WM_COPYDATA()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
	ON_COMMAND(IDOK, OnOK)
	//  ON_BN_CLICKED(IDOK, OnOK)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQyPs message handlers

 void  CQyPs::OnOK(  )
{
	QY_WMBUF_COMM	wmBuf;
	BOOL			bOk		=	TRUE;
	
	if  (  m_var.iType  ==  CONST_qyPsType_stat  )  {
		wmBuf.uiType  =  CONST_qyWmParam_chkPage;
		if  (  GetActivePage(  )->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  )  !=  CONST_qyWmRc_ok  )  {
			bOk  =  FALSE;
		}
	}

	if  (  bOk  )  {
		Default(  );
		EndDialog(  IDOK  );
	}
		
}




BOOL CQyPs::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	COPYDATASTRUCT		*	pCopyData			=	(  COPYDATASTRUCT  *  )pCopyDataStruct;
	int						iShowType			=	0;
	QNM_WMBUF_SHOWSTRUCT	wmBufShowStruct;
	CPropertyPage		*	pActivePage			=  GetActivePage(  );
	
	if  (  !pActivePage  )  goto  errLabel;
		
	if  (  pCopyData->cbData  >=  sizeof(  (  (  QY_SHOW_STRUCT  *  )0  )->iType  )  )  {
		iShowType  =  (  (  QY_SHOW_STRUCT  *  )pCopyData->lpData  )->iType;
		//  tracelog(  "CQyPs::OnCopyData: iShowType is %d",  iShowType  );
		if  (  (  1  <<  iShowType  )  &  m_var.u.showInfo.iShowFlgs[0]  )  {

			memset(  &wmBufShowStruct,  0,  sizeof(  wmBufShowStruct  )  );
			wmBufShowStruct.uiType  =  CONST_qyWmParam_show;
			memcpy(  &wmBufShowStruct.showStruct,  pCopyData->lpData,  min(  sizeof(  QY_SHOW_STRUCT  ),  pCopyData->cbData  )  );
			pActivePage->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBufShowStruct  );
		}
	}

errLabel:
	
	return  CPropertySheet::OnCopyData(pWnd, pCopyDataStruct);
}


BOOL CQyPs::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	

	if  (  m_var.iType  ==  CONST_qyPsType_show  )  {
		SetTimer(  CONST_qyPsTimerId,  2000,  NULL  );
	}
	
	return  bResult;
}


void CQyPs::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CPropertyPage			*	pActivePage			=  GetActivePage(  );
	if  (  !pActivePage  )  goto  errLabel;


	if  (  m_var.iType  ==  CONST_qyPsType_show  )  {
		DWORD						dwStatus;
		BOOL						bServiceRunning		=  FALSE;
		QNM_WMBUF_SHOWSTRUCT		wmBufShowStruct;
	
		if  (  m_var.u.showInfo.iShowFlgs[0]  &  (  1  <<  CONST_qyShowType_serviceStatus  )  )  {

			MACRO_qyAssert(  m_var.u.showInfo.serviceName_netMc[0],  _T(  "服务名字未填"  )  );
			MACRO_qyAssert(  m_var.u.showInfo.serviceName_is[0],  _T(  "服务名字未填"  )  );

			if  (  !qyGetServiceStatus(  NULL,  CString(  m_var.u.showInfo.serviceName_netMc  ).GetBuffer(  0  ),  &dwStatus  )  
				&&  dwStatus  ==  SERVICE_RUNNING  )  
			{
				bServiceRunning  =  TRUE;
			}

			#if  1
				 if  (  !qyGetServiceStatus(  NULL,  _T(  "awpmService"  ),  &dwStatus  )  
					 &&  dwStatus  ==  SERVICE_RUNNING  )  
				 {
					 bServiceRunning  =  TRUE;
				 }
			#endif

			if  (  bServiceRunning  !=  m_var.u.showInfo.bServiceRunning_netMc  
				||  m_var.u.showInfo.pActivePage  !=  pActivePage  )
			{
				m_var.u.showInfo.bServiceRunning_netMc  =  bServiceRunning;
				memset(  &wmBufShowStruct,  0,  sizeof(  wmBufShowStruct  )  );
				wmBufShowStruct.uiType  =  CONST_qyWmParam_show;
				wmBufShowStruct.showStruct.iType  =  CONST_qyShowType_serviceStatus;
				_sntprintf(  wmBufShowStruct.showStruct.who_from,  mycountof(  wmBufShowStruct.showStruct.who_from  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_qyServiceIdTable,  CONST_qyServiceId_netMc  )  );
				_sntprintf(  wmBufShowStruct.showStruct.what,  mycountof(  wmBufShowStruct.showStruct.what  ),  bServiceRunning  ?  _T(  "service is running"  )  :  _T(  "service stopped"  )  );
				pActivePage->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBufShowStruct  );
			}

			//  下面处理Is服务
			bServiceRunning  =  FALSE;
			if  (  !qyGetServiceStatus(  NULL,  CString(  m_var.u.showInfo.serviceName_is  ).GetBuffer(  0  ),  &dwStatus  )  
				&&  dwStatus  ==  SERVICE_RUNNING  )  
			{
				bServiceRunning  =  TRUE;
			}

			if  (  bServiceRunning  !=  m_var.u.showInfo.bServiceRunning_is
				||  m_var.u.showInfo.pActivePage  !=  pActivePage  )
			{
				m_var.u.showInfo.bServiceRunning_is  =  bServiceRunning;
				memset(  &wmBufShowStruct,  0,  sizeof(  wmBufShowStruct  )  );
				wmBufShowStruct.uiType  =  CONST_qyWmParam_show;
				wmBufShowStruct.showStruct.iType  =  CONST_qyShowType_serviceStatus;
				_sntprintf(  wmBufShowStruct.showStruct.who_from,  mycountof(  wmBufShowStruct.showStruct.who_from  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_qyServiceIdTable,  CONST_qyServiceId_is  )  );
				_sntprintf(  wmBufShowStruct.showStruct.what,  mycountof(  wmBufShowStruct.showStruct.what  ),  bServiceRunning  ?  _T(  "service is running"  )  :  _T(  "service stopped"  )  );
				pActivePage->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBufShowStruct  );
			}

			if  (  m_var.u.showInfo.pActivePage  !=  pActivePage  )  m_var.u.showInfo.pActivePage  =  pActivePage;

		}

		if  (  m_var.u.showInfo.iShowFlgs[0]  &  (  1  <<  CONST_qyShowType_refresh  )  )  {
			memset(  &wmBufShowStruct,  0,  sizeof(  wmBufShowStruct  )  );
			wmBufShowStruct.uiType  =  CONST_qyWmParam_show;
			wmBufShowStruct.showStruct.iType  =  CONST_qyShowType_refresh;
			pActivePage->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBufShowStruct  );
		}

	}

errLabel:

	CPropertySheet::OnTimer(nIDEvent);

}


void CQyPs::OnDestroy() 
{
	BOOL  bRet  =  KillTimer(  CONST_qyPsTimerId  );

	CPropertySheet::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

BOOL CQyPs::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	traceLogA(  "这里将OnHelpInfo给禁止了"  );	//  2004/05/10
	return  TRUE;
	//  return CPropertySheet::OnHelpInfo(pHelpInfo);
}
