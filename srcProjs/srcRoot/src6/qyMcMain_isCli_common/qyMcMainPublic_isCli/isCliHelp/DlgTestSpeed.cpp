// DlgTestSpeed.cpp : implementation file
//

#include "stdafx.h"

#define  __noDbg_new__

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
//  #include	"qyMc.h"
#include	"myresource.h"

#include "DlgTestSpeed.h"
#include "afxdialogex.h"
#include	"ctxQmc.h"
#include	"qmcCommFunc_isCli.h"


//
 __declspec(  dllexport  )  int  viewTestSpeed(  HWND  hParent  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	int						iErr		=		-1;
	QY_MC				*	pQyMc		=		QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProcInfo	=		QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	MIS_CNT				*	pMisCnt		=		getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;
	//
	CDlgTestSpeed			*	pDlg			=		NULL;

	traceLogA(  "testLocalWebcam enters"  );

	if  (  IsWindow(  pProcInfo->hWnd_testSpeed  )  )  {
		MACRO_SetForegroundWindow(  pProcInfo->hWnd_testSpeed  );
		return  0;
	}

	//
#ifndef  __NOTSUPPORT_testLocalAv__
	{
		RECT					rect;
		unsigned  short		usCnt_monPics_row	=	1;
		unsigned  short		usCnt_monPics_col	=	1;
		/*
		unsigned  int		uiInitW				=	pVar->av.localAv.videoCaptureProcInfo.vh_org.bih.biWidth;
		unsigned  int		uiInitH				=	pVar->av.localAv.videoCaptureProcInfo.vh_org.bih.biHeight;
		//
		if  (  uiInitH  <  300  )  {
			uiInitW  =  (  unsigned  int  )(  uiInitW  /  (  uiInitH  *  1.  )  *  300.  );
			uiInitH  =  300;
		}
		*/
		unsigned  int  uiInitW  =  640  +  30;
		unsigned  int  uiInitH  =  480  +  30;
		//  2013/03/06
		int  iResId_menu  =  CONST_resId_menu_dlgTest;
		//
		//  pDlg  =  new  CDlgTestWebcam(  CWnd::GetDesktopWindow(  )  );
		CWnd  *  pParent  =  CWnd::GetDesktopWindow(  );
		pParent  =  CWnd::FromHandle(  hParent  );
		pDlg  =  new  CDlgTestSpeed(  pParent  );	//  CDlgDynBmps(  pParent  );
		if  (  !pDlg  )  goto  errLabel;
		if  (  !pDlg->bSetDlgInfo(  CONST_qyWndContentType_testSpeed,  0,  _T(  "test speed"  ),  iResId_menu  )  )  goto  errLabel;

		if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		
		//
		pDlg->ShowWindow(  SW_SHOW  );
		//
		pProcInfo->hWnd_testSpeed  =  pDlg->m_hWnd;
		
		pDlg  =  NULL;
	}
#endif

	//

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
#ifndef  __NOTSUPPORT_testLocalAv__
		if  (  pDlg  )  delete  pDlg;
#endif
	}

	traceLogA(  "testLocalWebcam leaves with %s",  iErr  ?  "Failed"  :  "OK"  );

	return  iErr;
}




// CDlgTestSpeed dialog

IMPLEMENT_DYNAMIC(CDlgTestSpeed, CDialogEx)

CDlgTestSpeed::CDlgTestSpeed(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTestSpeed::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	
	m_var.m_pParent = pParent;
	m_var.m_nID = CDlgTestSpeed::IDD;

}

CDlgTestSpeed::~CDlgTestSpeed()
{
}


//
BOOL  CDlgTestSpeed::bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_menu  )
{
	BOOL  bRet  =  FALSE;

	bRet  =  TRUE;
	return  bRet;
}


BOOL CDlgTestSpeed::Create(const RECT& rect)
{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	//MC_VAR_isCli				*	pProc		=	NULL;

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): 在创建对话框之前应先设置初始数据"  );
		return  FALSE;
	}
	*/

	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	

	//
	if  (  !CDialog::Create(  this->m_var.m_nID, m_var.m_pParent  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}




BOOL  CDlgTestSpeed::bQuitDlg(  )	
{
	BOOL		bRet	=	FALSE;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	DestroyWindow(  );

	bRet  =  TRUE;
	return  bRet;
}
	





//
void CDlgTestSpeed::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTestSpeed, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CDlgTestSpeed::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_test, &CDlgTestSpeed::OnBnClickedButtontest)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlgTestSpeed message handlers


void CDlgTestSpeed::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PostNcDestroy();
	
	//
	if  (  m_var.bCreated  )  {

		traceLogA(  "CDlgTestSpeed::PostNcDestroy(  ): delete this"  );
		try  {
			 delete  this;		
			}
		catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTestSpeed::PostNcDestroy failed."  )  );
		}

	}

}


void CDlgTestSpeed::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//  CDialogEx::OnCancel();
	bQuitDlg(  );
}


BOOL CDlgTestSpeed::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetWindowText(  _T(  "Test speed"  )  );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgTestSpeed::OnBnClickedButtontest()
{
	// TODO: Add your control notification handler code here

	if  (  !m_var.bTimerStarted  )  {

		//
		m_var.iIntervalInMs_timer  =  100;
		m_var.fTimesPerSecond_timer  =  1000.  /  m_var.iIntervalInMs_timer;

		//
		memset(  &m_var.test,  0,  sizeof(  m_var.test  )  );
		//
		m_var.test.cur.nTotal_perTest  =  min(  5,  mycountof(  m_var.test.cur.repliesInfo.mems  )  );
		if  (  !m_var.test.cur.nTotal_perTest  )  goto  errLabel;
		//
		m_var.test.cur.nB_perSend  =  100  *  1000  /  8.  /  m_var.fTimesPerSecond_timer;
		//
		m_var.test.top.nB_perSend  =  100  *  1000000  /  8.  /  m_var.fTimesPerSecond_timer;
	
		//
		m_var.timerId  =  SetTimer(  1,  m_var.iIntervalInMs_timer,  NULL  );
		m_var.bTimerStarted  =  TRUE;	
		//
		SetDlgItemText(  IDC_BUTTON_test,  _T(  "Stop testing"  )  );
	}
	else  {
		  KillTimer(  m_var.timerId  );
		  m_var.bTimerStarted  =  FALSE;
		  //
		  SetDlgItemText(  IDC_BUTTON_test,  _T(  "Test speed"  )  );
	}

errLabel:
	return;
}



//
 int  sndTestSpeedReq_qmc(  MIS_CNT  *  pMisCnt,  TEST_speed_info  *  pTest,  int  kBPer  )
{
	int							iErr								=	-1;
	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	QY_MC					*	pQyMc								=	pProcInfo->pQyMc;
	CQyMalloc  mallocObj_req;
	int  size  =  sizeof(  TEST_speed_req  );
	TEST_speed_req		*	pReq  =  (  TEST_speed_req  *  )mallocObj_req.mallocf(  size  );
	if  (  !pReq  )  return  -1;
	//
	IM_L_STREAM				*	pStream								=	NULL;
	unsigned  int				len;

	//
	if  (  !kBPer  )  return  -1;
	
	//
	if  (  !(  pStream  =  (  IM_L_STREAM  *  )mymalloc(  sizeof(  IM_L_STREAM  )  )  )  )  {
		#ifdef  __DEBUG__
				traceLogA(  "sndDevInfo_qmc . malloc failed."  );  
		#endif
		goto  errLabel;
	}

	
	//
	memset(  pReq,  0,  offsetof(  TEST_speed_req,  buf  )  );

	pReq->usLen  =  kBPer  *  1000;

	//
	unsigned  int  tn  =  getuiNextTranNo(  0,  0,  0  );
	//
	int  index  =  pTest->cur.nTimes_sent_perTest;
	if  (  index  >=  0  &&  index  <  mycountof(  pTest->cur.repliesInfo.mems  )  )  {
		pTest->cur.repliesInfo.mems[index].tn_perSend  =  tn;
	}
	pReq->tn_perSend  =  tn;

	//
	MACRO_memset_imLStream(  pStream  );
	pStream->uiType  =  CONST_imCommType_lStream;
	pStream->uiContentType  =  CONST_imCommType_testSpeedReq;
	len  =  sizeof(  pStream->buf  );
	if  (  testSpeedReq2Stream(  pStream->uiContentType,  pReq,  pStream->buf,  &len  )  )  goto  errLabel;
	pStream->ulStreamLen  =  len;
	len  +=  offsetof(  IM_L_STREAM,  buf  ); 

	MACRO_prepareForTran(  );

	if  (  pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_mcComm, tStartTran,  uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  NULL,  CONST_channelType_talking,  NULL,  FALSE  )  )  goto  errLabel;


	iErr  =  0;
errLabel:

	if  (  pStream  )  myfree(  pStream  );

	return  iErr;

}

 //
 int  get_nRecvd(  TEST_speed_info  *  pTest  )
 {
	 TEST_speed_info  &  test  =  *pTest;
	 int  i;

 		int  nTotalRecvd  =  0;
		for  (  i  =  0;  i  <  test.cur.nTotal_perTest;  i  ++  )  {
			if  (  test.cur.repliesInfo.mems[i].bReplied  )  nTotalRecvd  ++;
		}

		return  nTotalRecvd;
 }



void CDlgTestSpeed::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	int  iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
	TCHAR  tStatus[128]  =  _T(  ""  );

#ifdef  __DEBUG__
	traceLog(  _T(  "Ontimer"  )  );
#endif

	//
	int  i;
	
	//
	if  (  m_var.test.bStopped  )  {
		return;
	}

	//
	if  (  !m_var.test.bottom.nB_perSend  )  {
		if  (  !m_var.test.cur.nTimes_sent_perTest  )  {
			m_var.test.cur.nB_perSend  =  100  *  1000  /  8  /  m_var.fTimesPerSecond_timer;

			//
			_sntprintf(  tStatus,  mycountof(  tStatus  ),  _T(  "start test %dkbps"  ),  m_var.test.cur.nB_perSend  /  1000.  );
			SetDlgItemText(  IDC_STATIC_status,  tStatus  );
		}
		sndTestSpeedReq_qmc(  pMisCnt,  &m_var.test,  m_var.test.cur.nB_perSend  );
		m_var.test.cur.nTimes_sent_perTest  ++  ;
		if  (  m_var.test.cur.nTimes_sent_perTest  <  m_var.test.cur.nTotal_perTest  )  {
			iErr  =  0;  goto  errLabel;
		}
		//
		int  nTotalRecvd  =  get_nRecvd(  &m_var.test  );
		//
		if  (  nTotalRecvd  ==  m_var.test.cur.nTotal_perTest  )  {
			m_var.test.bottom.nB_perSend  =  m_var.test.cur.nB_perSend;
			m_var.test.cur.nTimes_sent_perTest  =  0;
			
			_sntprintf(  tStatus,  mycountof(  tStatus  ),  _T(  "test ok. %dkbps"  ),  m_var.test.cur.nB_perSend  /  1000.  );					
			SetDlgItemText(  IDC_STATIC_status,  tStatus  );

			//
			iErr  =  0;  goto  errLabel;
		}
		m_var.test.top.nB_perSend  =  m_var.test.cur.nB_perSend;
		m_var.test.bStopped  =  TRUE;
		

		//		
		_sntprintf(  tStatus,  mycountof(  tStatus  ),  _T(  "test stopped. < %dkbps"  ),  (  int  )(  m_var.test.cur.nB_perSend  *  m_var.fTimesPerSecond_timer  *  8  /  1000.  )  );			
		SetDlgItemText(  IDC_STATIC_status,  tStatus  );

		//
		iErr  =  0;  goto  errLabel;
	}

	//
	if  (  !m_var.test.cur.nTimes_sent_perTest  )  {
		//
		int  iDiff  =  m_var.test.top.nB_perSend  -  m_var.test.bottom.nB_perSend;
		if  (  abs(  iDiff  )  <  100000  /  8  /  10  )  {		
			//stop
			m_var.test.bStopped  =  TRUE;
			//		
			_sntprintf(  tStatus,  mycountof(  tStatus  ),  _T(  "test stopped. %dkbps"  ),  m_var.test.bottom.nB_perSend  /  1000.  );			
			SetDlgItemText(  IDC_STATIC_status,  tStatus  );

			iErr  =  0;  goto  errLabel;	
		}


		memset(  &m_var.test.cur.repliesInfo,  0,  sizeof(  m_var.test.cur.repliesInfo  )  );
		//
		m_var.test.cur.nB_perSend  =  (  m_var.test.top.nB_perSend  +  m_var.test.bottom.nB_perSend  )  /  2; 

		//		
		_sntprintf(  tStatus,  mycountof(  tStatus  ),  _T(  "start test %dkbps"  ),  m_var.test.cur.nB_perSend  /  1000.  );			
		SetDlgItemText(  IDC_STATIC_status,  tStatus  );
	}
	sndTestSpeedReq_qmc(  pMisCnt,  &m_var.test,  m_var.test.cur.nB_perSend  );
	m_var.test.cur.nTimes_sent_perTest  ++  ;
	if  (  m_var.test.cur.nTimes_sent_perTest  <  m_var.test.cur.nTotal_perTest  )  {
		iErr  =  0;  goto  errLabel;
	}
	//
	int  nTotalRecvd  =  get_nRecvd(  &m_var.test  );
	//
	if  (  nTotalRecvd  ==  m_var.test.cur.nTotal_perTest  )  {
		m_var.test.bottom.nB_perSend  =  m_var.test.cur.nB_perSend;
		m_var.test.cur.nTimes_sent_perTest  =  0;
		iErr  =  0;  goto  errLabel;
	}
	m_var.test.top.nB_perSend  =  m_var.test.cur.nB_perSend;
	m_var.test.cur.nTimes_sent_perTest  =  0;
	iErr  =  0;  goto  errLabel;

errLabel:

	CDialogEx::OnTimer(nIDEvent);
}


void CDlgTestSpeed::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	if  (  m_var.bTimerStarted  )  KillTimer(  m_var.timerId  );
}
