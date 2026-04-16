// DlgQyCommStatus.cpp : implementation file
//

#include	"stdafx.h"
#include	<winsvc.h>
#include	<vfw.h>
//
#include	"qmCommon.h"
#include	"qyPs.h"
#include	"ctxQmThread.h"

#include	"qyStatusToolCommon.h"
#include	"qystatustool.h"
#include	"DlgQyCommStatus.h"

#include	"DlgFilters.h"
#include ".\dlgqycommstatus.h"
#include	"qyCusResPublic.h"
#include	"qyCusResTemp.h"
#include	"qmUiFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
  int  getLvSel(  HWND  hParent,  int  *  pCurnItem  )
{
	 int						iErr				=	-1;
	 LVITEM						lvItem;
	 unsigned  int				selectedCnt;
	 int						curnItem;
	 int						nCol;
	 
	 selectedCnt  =  ::SendMessage(  hParent,  LVM_GETSELECTEDCOUNT,  0,  0  );
	 if  (  !selectedCnt  )  goto  errLabel;
	 //
	 if  (  selectedCnt  >  1  )  goto  errLabel;	//  ÔÝÊ±²»Ö§³ÖÉ¾³ý¶àÏî¡£
	 
	 if  (  (  curnItem  =  ::SendMessage(  hParent,  LVM_GETSELECTIONMARK,  0,  0  )  )  <  0  )  goto  errLabel;

	 *pCurnItem=curnItem;

	 iErr =  0;
errLabel:
	 return  iErr;
  }



/////////////////////////////////////////////////////////////////////////////
// CDlgQyCommStatus dialog


CDlgQyCommStatus::CDlgQyCommStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQyCommStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQyCommStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQyCommStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQyCommStatus)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQyCommStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgQyCommStatus)
	ON_WM_SIZE()
	ON_WM_COPYDATA()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_select, OnSelchangeCOMBOselect)
	//}}AFX_MSG_MAP
	ON_MESSAGE(  QY_WM_COMM,  OnQyComm  )
	ON_MESSAGE(CONST_qyWm_postComm, OnQyPostComm)
	ON_BN_CLICKED(IDC_RADIO_qwmComm, OnBnClickedRadioqwmcomm)
	ON_BN_CLICKED(IDC_RADIO_qnmChking, OnBnClickedRadioqnmchking)
	ON_BN_CLICKED(IDC_RADIO_scanningIp, OnBnClickedRadioscanningip)
	ON_BN_CLICKED(IDC_CHECK_autoClearup, OnBnClickedCheckautoclearup)
//	ON_COMMAND(ID_MENU_TASK, &CDlgQyCommStatus::OnMenuTask)
ON_COMMAND(ID_MENU_TASKS, &CDlgQyCommStatus::OnMenuTasks)
ON_COMMAND(ID_MENU_PLAYERS, &CDlgQyCommStatus::OnMenuPlayers)
ON_COMMAND(ID_MENU_TALKS, &CDlgQyCommStatus::OnMenuTalks)
ON_COMMAND(ID_QS, &CDlgQyCommStatus::OnQs)
ON_COMMAND(ID_SYS, &CDlgQyCommStatus::OnSys)
ON_COMMAND(ID_OTHERS, &CDlgQyCommStatus::OnOthers)
ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_display, &CDlgQyCommStatus::OnLvnGetdispinfoListdisplay)
ON_NOTIFY(LVN_ODFINDITEM, IDC_LIST_display, &CDlgQyCommStatus::OnLvnOdfinditemListdisplay)
ON_NOTIFY(LVN_ODCACHEHINT, IDC_LIST_display, &CDlgQyCommStatus::OnLvnOdcachehintListdisplay)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQyCommStatus message handlers

 void  sizeDlg(  CDlgQyCommStatus  *  pDlg  )
{	
			   
	int					iWidth				=	0;
	int					iHeight				=	0;

	int					x,  y;
	RECT				rect, rc;
	int					nWidth_autoClearup,  nHeight_autoClearup;
	int					iW,  iH;

	pDlg->GetClientRect(  &rect  );
	iWidth  =  rect.right  -  rect.left;  iHeight  =  rect.bottom  -  rect.top;
	if  (  iWidth  <  10  ||  iHeight  <  10  )  goto  errLabel;
		
	CWnd  *  pCtrl;
	pCtrl  =  pDlg->GetDlgItem(  IDC_CHECK_autoClearup  );
	if  (  !pCtrl  )  goto  errLabel;
	pCtrl->GetWindowRect(  &rc  );
	nWidth_autoClearup  =  rc.right  -  rc.left;
	nHeight_autoClearup  =  rc.bottom  -  rc.top;
	
	pCtrl  =  pDlg->GetDlgItem(  IDC_STATIC_toolStatus  );
	if  (  !pCtrl  )  goto  errLabel;
	pCtrl->GetWindowRect(  &rc  );
	int  nWidth_toolStatus  =  rc.right  -  rc.left;
	int  nHeight_toolStatus  =  rc.bottom  -  rc.top;
	
	
	//
	HDWP			hDwp;
	int				nTotal;	nTotal  =  3;

	hDwp  =  BeginDeferWindowPos(  nTotal  );
	if  (  hDwp  )  {		 
				
		pCtrl  =  pDlg->GetDlgItem(  IDC_LIST_display  );
		x  =  pDlg->m_var.iEdge_list_x;
		y  =  pDlg->m_var.iTop_list  -  50;//23;				//  这个23是因为前面没有把坐标统一成window坐标或者client坐标。混用了，所以用23这个修正参数。
		iW  =  iWidth  -  2  *  pDlg->m_var.iEdge_list_x;
		iH  =  iHeight  -  pDlg->m_var.iTop_list  -  pDlg->m_var.iSpacing_list_autoClearup  -  nHeight_autoClearup  -  pDlg->m_var.iEdge_autoClearup_b  +  23;
		DeferWindowPos(  hDwp,  pCtrl->m_hWnd,  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		//
		int  iRight_display  =  x  +  iW;

		//
		pCtrl  =  pDlg->GetDlgItem(  IDC_CHECK_autoClearup  );		
		x  =  pDlg->m_var.iX_autoClearup;
		y  +=  iH  +  pDlg->m_var.iSpacing_list_autoClearup;
		iW  =  nWidth_autoClearup;
		iH  =  nHeight_autoClearup;
		DeferWindowPos(  hDwp,  pCtrl->m_hWnd,  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		
		pCtrl  =  pDlg->GetDlgItem(  IDC_STATIC_toolStatus  );
		x  =  iRight_display  -  nWidth_toolStatus  +  10;
		iW  =  nWidth_toolStatus;
		DeferWindowPos(  hDwp,  pCtrl->m_hWnd,  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		
		//
		EndDeferWindowPos(  hDwp  );
	}
			
errLabel:
	return;

}

 //
 bool  isFiltersEmpty(  MY_filters  *  pFilters  )
 {
	 int  i;
	 for  (  i  = 0;  i  <  mycountof(  pFilters->mems  );  i  ++  )  {
		 MY_filter  *  pMem  =  &pFilters->mems[i];
		 if  (  pMem->ulClientIp0  
			 ||  pMem->filter0Buf[0]  
			 ||  pMem->filter1Buf[0]
			 ||  pMem->contentFilter2Buf[0]
			 ||  pMem->contentFilter3Buf[0]  )
		{
			 return  false;
		}
			 //
			 continue;
	 }

	 return  true;
 }

 bool  isFilterEmpty_state(  MY_filters  *  pFilters  )
 {
	 int  i;
	 for  (  i  = 0;  i  <  mycountof(  pFilters->mems  );  i  ++  )  {
		 MY_filter  *  pMem  =  &pFilters->mems[i];
		 if  (  pMem->filter0Buf[0]
		 ||  pMem->filter1Buf[0]  )  return  false;
	 }
	 return  true;
 }

 //
#define CONST_qyPsTimerId_10ms	3

 //
BOOL CDlgQyCommStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	BOOL					bRet			=	FALSE;
	QY_STATUS_STRUCT	*	pStatusStruct	=	&this->m_var.u.showInfo.statusStruct;
	
	cusDlgRes(  0,  &pStatusStruct->cusRes,  this->m_hWnd,  this->IDD  );

	//
	m_list=(CListCtrl*)GetDlgItem(IDC_LIST_display);


	//
	DWORD dwStyle;
			
	dwStyle  =  LVS_REPORT  |  LVS_SHOWSELALWAYS;
		dwStyle  |=  LVS_SINGLESEL;		//  2007/08/24, 准备支持多选
		m_list->ModifyStyle(  LVS_TYPEMASK,  dwStyle  );						//  ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
		//
		ListView_SetExtendedListViewStyle( m_list->m_hWnd, LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );



	//
	//ListView_SetExtendedListViewStyle(m_list->m_hWnd, LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES );

		//Create image list
	m_imagelist.Create(IDB_BITMAP, 16, ILC_COLOR4, RGB(255, 255, 255));
	m_imagelistLarge.Create(IDB_BITMAP_LARGE, 32, ILC_COLOR4, RGB(255, 255, 255));
		
	m_list->SetImageList(&m_imagelist, LVSIL_SMALL);
	m_list->SetImageList(&m_imagelistLarge, LVSIL_NORMAL);


	//
	SetDlgItemText(  IDC_RADIO_qwmComm,  _T(  "Comm"  )  );
	SetDlgItemText(  IDC_RADIO_qnmChking,  _T(  "Qnm"  )  );
	SetDlgItemText(  IDC_RADIO_scanningIp,  _T(  "Ip scan"  )  );

	//
	m_list->InsertColumn(0, _T("seqNo"), LVCFMT_LEFT, 0);
	m_list->InsertColumn(1, _T("Str"), LVCFMT_LEFT, 1750);



	//
	GENERIC_Q_CFG	qCfg;
	int				len;


	//
	memset(  &qCfg,  0,  sizeof(  qCfg  )  );
	_sntprintf(  qCfg.name,  mycountof(  qCfg.name  ),  _T(  "qyStatusToolQ"  )  );
	_sntprintf(  qCfg.mutexName_prefix,  mycountof(  qCfg.mutexName_prefix  ),  _T(  "qyStatusToolQ"  )  );
	qCfg.uiMaxQNodes  =  (  qyGetAppType(  0,  0  )  ==  CONST_qyAppType_client  )  ?  CONST_maxnItemsInListBox_client  :  CONST_maxnItemsInListBox_main;
	if  (  initGenericQ(  &qCfg,  malloc,  0,  0,  free,  NULL,  &m_var.infoQ  )  )  goto  errLabel;
	m_var.bInfoQInited  =  TRUE;
	//
	len  =  sizeof(  void  *  )  *  qCfg.uiMaxQNodes;
	m_var.ppInfos_sortedByTime  =  (  void  **  )malloc(  len   );	
	if  (  !m_var.ppInfos_sortedByTime  )  goto  errLabel;	 
	memset(  m_var.ppInfos_sortedByTime,  0,  len  );

	if  (  qyGetAppType(  0,  0  )  ==  CONST_qyAppType_client  )  SetWindowText(  CONST_qnmStatusWndTitle_client  );
	else  SetWindowText(  CONST_qnmStatusWndTitle  );

	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_RESETCONTENT,  0,  0  );
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_communicationStatus  )  );
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_communicationStatusWithFilters  )  );
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_export  )  );
	//
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_SETCURSEL,  m_var.iCurSel,  0  );

	(  (  CButton  *  )GetDlgItem(  IDC_RADIO_qwmComm  )  )->SetCheck(  BST_CHECKED  );
	//
	/*
	this->m_var.u.showInfo.iShowFlgs[0]  =  (  1  <<  CONST_qyShowType_serviceStatus  )
											|  (  1  <<  CONST_qyShowType_qwmComm  )
												|  (  1  <<  CONST_qyShowType_qmdState  )
													|  (  1  <<  CONST_qyShowType_sysInfo  )
														|  (  1  <<  CONST_qyShowType_debug  )
															|  (  1  <<  CONST_qyShowType_debugWarning  )
																|  (  1  <<  CONST_qyShowType_warning  );
																*/
	OnBnClickedRadioqwmcomm(  );


	BOOL	bStopped;		bStopped		=	FALSE;
	BOOL	bNotAllAllowed;	bNotAllAllowed	=	FALSE;
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

	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  ),  _T(  "%d %s"  ),  m_var.infoQ.cfg.uiMaxQNodes,  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_resetWhenUpTo    )  ); 
	SetDlgItemText(  IDC_CHECK_autoClearup,  tBuf  );

	(  (  CButton  *  )GetDlgItem(  IDC_CHECK_autoClearup  )  )->SetCheck(  BST_CHECKED  );
	m_var.bAutoClearup  =  TRUE;



	//
	int		iWidth,  iHeight;
	RECT	rect, rc_list;
	int		iList_b;
	//
	GetWindowRect(  &rect  );
	iWidth  =  rect.right  -  rect.left;
	iHeight  =  rect.bottom  -  rect.top;
	//
	GetDlgItem(  IDC_LIST_display  )->GetWindowRect(  &rc_list  );
	m_var.iEdge_list_x  =  (  iWidth  -  (  rc_list.right  -  rc_list.left  )  )  /  2;
	m_var.iTop_list  =  rc_list.top;
	iList_b  =  rc_list.bottom  -  rect.top;
	//
	GetDlgItem(  IDC_CHECK_autoClearup  )->GetWindowRect(  &rect  );
	m_var.iX_autoClearup  =  rect.left;
	m_var.iEdge_autoClearup_b  =  iHeight  -  rect.bottom;
	m_var.iSpacing_list_autoClearup  =  rect.top  -  iList_b;

	//  2015/09/13
	::SendDlgItemMessage(  m_hWnd,  IDC_LIST_display,  LB_SETHORIZONTALEXTENT,  2500,  0  );


	//
	sizeDlg(  this  );

	if  (  m_var.iType  ==  CONST_qyPsType_show  )  {
		SetTimer(  CONST_qyPsTimerId,  1000,  NULL  );
		//
		SetTimer(CONST_qyPsTimerId_10ms, 200, NULL);
	}


	//
	bRet  =  TRUE;
errLabel:
	if  (  !bRet  )  {
		EndDialog(  -1  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgQyCommStatus::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	sizeDlg(  this  );
}

//
BOOL  is0_SYSTEMTIME(  SYSTEMTIME  *  p  )
{
	if  (  !p->wYear
		&&  !p->wMonth
		&&  !p->wDayOfWeek
		&&  !p->wDay
		&&  !p->wHour
		&&  !p->wMinute
		&&  !p->wSecond
		&&  !p->wMilliseconds
		)
	{
		return  TRUE;
	}
	return  FALSE;

}

BOOL CDlgQyCommStatus::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	COPYDATASTRUCT		*	pCopyData			=	(  COPYDATASTRUCT  *  )pCopyDataStruct;
	int						iShowType			=	0;
	QNM_WMBUF_SHOWSTRUCT	wmBufShowStruct;
	
#if 0
	if  (  pCopyData->cbData  >=  sizeof(  (  (  QY_SHOW_STRUCT  *  )0  )->iType  )  )  {
		iShowType  =  (  (  QY_SHOW_STRUCT  *  )pCopyData->lpData  )->iType;
		//  tracelog(  "CQyPs::OnCopyData: iShowType is %d",  iShowType  );
		if  (  (  1  <<  iShowType  )  &  m_var.u.showInfo.iShowFlgs[0]  )  {

			memset(  &wmBufShowStruct,  0,  sizeof(  wmBufShowStruct  )  );
			wmBufShowStruct.uiType  =  CONST_qyWmParam_show;
			memcpy(  &wmBufShowStruct.showStruct,  pCopyData->lpData,  min(  sizeof(  QY_SHOW_STRUCT  ),  pCopyData->cbData  )  );
			//
			#ifdef  __DEBUG__
			if  (  is0_SYSTEMTIME(  &wmBufShowStruct.showStruct.when  )  )  {
				int  i;
				i  =  1;
				traceLog(  _T(  "Err: when is 0"  )  );
			}
			#endif

			if  (  !is0_SYSTEMTIME(  &wmBufShowStruct.showStruct.when  )  )  {
				//
				QY_SHOW_STRUCT	*	pShowStruct				=	&wmBufShowStruct.showStruct;
				switch  (  pShowStruct->iType  )  {
						case  CONST_qyShowType_serviceStatus:
						case  CONST_qyShowType_qmdState:
						default:
							  this->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBufShowStruct  );
							  break;
				}

			}

		}
	}
#endif


	
	CDialog::OnCopyData(pWnd, pCopyDataStruct);
	return  TRUE;
}

int CDlgQyCommStatus::processInputQ()
{
	char buf[1024];
	int iMax=5000;

	//
#if 0
	test_add();
	return 0;
#endif

	//
	if ( isQEmpty(&g_pStatusStruct->inputQ))  return  0;

	//
	bool bSel_lastLine=false;
	int  iCurSel=-1;					
	if  (  getLvSel(m_list->m_hWnd,&iCurSel  ) < 0  )  {					
		iCurSel =  -1;									  
	}
	if ( iCurSel==m_var.infoQ.uiQNodes-1) {
		bSel_lastLine=true;
	}


	//
	for (;iMax;iMax --) {
		//
		int						iShowType = 0;
		QNM_WMBUF_SHOWSTRUCT	wmBufShowStruct;
		memset(&wmBufShowStruct, 0, sizeof(wmBufShowStruct));
		wmBufShowStruct.uiType = CONST_qyWmParam_show;

		int len = sizeof(buf);
		if (qGetMsg(&g_pStatusStruct->inputQ, buf, (unsigned int *)&len))break;
		//
		memcpy(&wmBufShowStruct.showStruct,buf, sizeof(QY_SHOW_STRUCT));
		//
		{
			// TODO: Add your message handler code here and/or call default

			{
				iShowType = wmBufShowStruct.showStruct.iType;
				//  tracelog(  "CQyPs::OnCopyData: iShowType is %d",  iShowType  );
				if ((1 << iShowType) & m_var.u.showInfo.iShowFlgs[0]) {

					//
#ifdef  __DEBUG__
					if (is0_SYSTEMTIME(&wmBufShowStruct.showStruct.when)) {
						int  i;
						i = 1;
						traceLog(_T("Err: when is 0"));
					}
					//
					if (wmBufShowStruct.showStruct.usStateType == CONST_stateType_sys) {
						int  ii = 0;
					}
#endif

					if (!is0_SYSTEMTIME(&wmBufShowStruct.showStruct.when)) {
						//
						QY_SHOW_STRUCT* pShowStruct = &wmBufShowStruct.showStruct;
						switch (pShowStruct->iType) {
						case  CONST_qyShowType_serviceStatus:
						case  CONST_qyShowType_qmdState:
						default:
							this->SendMessage(CONST_qyWm_comm, 0, (LPARAM)&wmBufShowStruct);
							break;
						}

					}

				}
			}


		}

	}

	//
	m_list->SetItemCount( m_var.infoQ.uiQNodes );

	//
	if ( bSel_lastLine ) {
		//ListView_SetSelectionMark(m_list->m_hWnd,m_var.infoQ.uiQNodes-1);
		int nIndex=m_var.infoQ.uiQNodes-1;
		m_list->SetItemState(nIndex, LVIS_FOCUSED | LVIS_SELECTED,LVIS_FOCUSED | LVIS_SELECTED);   //选中行
		m_list->SetSelectionMark(nIndex);
		//
		m_list->EnsureVisible(nIndex,false);
	}


	return 0;
}


void CDlgQyCommStatus::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
// TODO: Add your message handler code here and/or call default
	QY_STATUS_STRUCT	*	pStatusStruct	=	&this->m_var.u.showInfo.statusStruct;

	//
	if (nIDEvent == CONST_qyPsTimerId_10ms) {

#if 0
		static DWORD sdwTickCnt = 0;
		int dwTickCnt = myGetTickCount(NULL);
		int iDiffInMs = dwTickCnt - sdwTickCnt;
		sdwTickCnt = dwTickCnt;

		//
		traceLog(_T("timer: iDiffInMs %dms"), iDiffInMs);
#endif
		//
		processInputQ();

		//
		return;
	}


	//
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

			if  (  bServiceRunning  !=  m_var.u.showInfo.bServiceRunning_netMc  )  {
				m_var.u.showInfo.bServiceRunning_netMc  =  bServiceRunning;
				memset(  &wmBufShowStruct,  0,  sizeof(  wmBufShowStruct  )  );
				wmBufShowStruct.uiType  =  CONST_qyWmParam_show;
				wmBufShowStruct.showStruct.iType  =  CONST_qyShowType_serviceStatus;
				_sntprintf(  wmBufShowStruct.showStruct.who_from,  mycountof(  wmBufShowStruct.showStruct.who_from  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_qyServiceIdTable,  CONST_qyServiceId_netMc  )  );
				_sntprintf(  wmBufShowStruct.showStruct.what,  mycountof(  wmBufShowStruct.showStruct.what  ),  bServiceRunning  ?  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_serviceIsRunning  )  :  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_serviceHaveStopped  )  );
				this->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBufShowStruct  );
			}

			//  下面处理Is服务
			bServiceRunning  =  FALSE;
			if  (  !qyGetServiceStatus(  NULL,  CString(  m_var.u.showInfo.serviceName_is  ).GetBuffer(  0  ),  &dwStatus  )  
				&&  dwStatus  ==  SERVICE_RUNNING  )  
			{
				bServiceRunning  =  TRUE;
			}

			if  (  bServiceRunning  !=  m_var.u.showInfo.bServiceRunning_is  )  {
				m_var.u.showInfo.bServiceRunning_is  =  bServiceRunning;
				memset(  &wmBufShowStruct,  0,  sizeof(  wmBufShowStruct  )  );
				wmBufShowStruct.uiType  =  CONST_qyWmParam_show;
				wmBufShowStruct.showStruct.iType  =  CONST_qyShowType_serviceStatus;
				_sntprintf(  wmBufShowStruct.showStruct.who_from,  mycountof(  wmBufShowStruct.showStruct.who_from  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_qyServiceIdTable,  CONST_qyServiceId_is  )  );
				_sntprintf(  wmBufShowStruct.showStruct.what,  mycountof(  wmBufShowStruct.showStruct.what  ),  bServiceRunning  ?  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_serviceIsRunning  )  :  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_serviceHaveStopped  )  );
				this->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBufShowStruct  );
			}


		}

		if  (  m_var.u.showInfo.iShowFlgs[0]  &  (  1  <<  CONST_qyShowType_refresh  )  )  {
			memset(  &wmBufShowStruct,  0,  sizeof(  wmBufShowStruct  )  );
			wmBufShowStruct.uiType  =  CONST_qyWmParam_show;
			wmBufShowStruct.showStruct.iType  =  CONST_qyShowType_refresh;
			this->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBufShowStruct  );
		}

	}

	//
	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Pipe %d/%d"  ),  pStatusStruct->pipe.nConnections,  pStatusStruct->pipe.nPipes  );
	if  (  pStatusStruct->sock.usPort  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. Listening on %d, %d/%d"  ),  tBuf,  (int)pStatusStruct->sock.usPort,  pStatusStruct->sock.nConnetions,  pStatusStruct->sock.maxConns  );
	}
	//
	int nQNodes_inputQ = g_pStatusStruct->inputQ.uiQNodes;
	int nQNodes_infoQ = m_var.infoQ.uiQNodes;
	_sntprintf(tBuf, mycountof(tBuf), _T("%s. (%d,%d)"), tBuf, nQNodes_inputQ, nQNodes_infoQ);
	//
	time_t  t;
	mytime(&t);
	char  tmpBuf[128];
	displayShortTime(  t,  tmpBuf,  mycountof(  tmpBuf  )  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. %s"  ),  tBuf,  CString(  tmpBuf  )  );
	SetDlgItemText(  IDC_STATIC_toolStatus,  tBuf  );

//  errLabel:

	CDialog::OnTimer(nIDEvent);
}

 static  char  *  myDisplayTime(  SYSTEMTIME  *  when,  char  *  displayBuf,  unsigned  int  size  )
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


void CDlgQyCommStatus::OnDestroy() 
{
	BOOL  bRet  =  KillTimer(  CONST_qyPsTimerId  );

	//
	::SendMessage(g_pStatusStruct->hWnd_tasks, WM_CLOSE, 0, 0);
	::SendMessage(g_pStatusStruct->hWnd_players, WM_CLOSE, 0, 0);
	::SendMessage(g_pStatusStruct->hWnd_talks, WM_CLOSE, 0, 0);




	//
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

#define FILE_FILTER_TEXT \
    TEXT("Log File (*.txt)\0*.txt\0")\
    TEXT("All Files (*.*)\0*.*;\0\0")

 int  myExportSth(  CDlgQyCommStatus  *  pDlg  )
 {
	 CListCtrl  *  pLb  =  (  CListCtrl  *  )pDlg->GetDlgItem(  IDC_LIST_display  );
	 int		i;
	
	LPCTSTR						lpszDefExt  =	TEXT("*\0");
	LPCTSTR							lpszFilter	=	FILE_FILTER_TEXT;
	LPCTSTR							title		=	TEXT("Open Log File...\0");
	//CQyString						pathCStr;
	TCHAR							pathCStr[MAX_PATH]  =  _T(  ""  );
	DWORD							dwFlags     =	OFN_READONLY;
	FILE				*			fp			=	NULL;

	//
	if  (  qyBrowseForFile1(  pDlg->m_hWnd,  TRUE,  lpszDefExt,  dwFlags,  FILE_FILTER_TEXT,  title,  NULL,  NULL,  pathCStr,  mycountof(  pathCStr  )  )  )  {
		goto  errLabel;
	}
	//if  (  pathCStr.GetLength(  )  ==  0  )  goto  errLabel;

	{
		CWaitCursor	cur;
		fp  =  _tfopen(  pathCStr,  _T(  "a"  )  );  
		if  (  !fp  )  goto  errLabel;

		//
		int  jj = pLb->GetItemCount();


		//
		for  (  i  =  0;  i  <  pLb->GetItemCount(  );  i  ++  )  {
			 //CString		str;
			 CString		str0;
			 CString		str1;

			 str1=pLb->GetItemText(  i,  1  );
			 _ftprintf(  fp,  _T(  "%s\n"  ),  str1  );
		}
	}

errLabel:
	 if  (  fp  )  fclose(  fp  );
	 return  0;
 }

void CDlgQyCommStatus::OnSelchangeCOMBOselect() 
{
	QY_STATUS_STRUCT	*	pStatusStruct	=  &m_var.u.showInfo.statusStruct;
	char					ip[128]			=	"";
	unsigned  long			ulIp0			=	0;
	//unsigned  long			ulIp1			=	0;
	//CString					str0,  str1,  str2,  str3;

	int	 iCurSel  =  GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_GETCURSEL,  0,  0  );
	
	if  (  iCurSel  ==  CB_ERR  )  return;

	switch  (  iCurSel  )  {
			case  0:
					memset(  &m_var.filters,  0,  sizeof(  m_var.filters  )  );
					GetDlgItem(  IDC_STATIC_clientIp0  )->ShowWindow(  SW_HIDE  );
				    GetDlgItem(  IDC_STATIC_filter00  )->ShowWindow(  SW_HIDE  );					
					GetDlgItem(  IDC_STATIC_filter01  )->ShowWindow(  SW_HIDE  );
					GetDlgItem(  IDC_STATIC_contentFilter02  )->ShowWindow(  SW_HIDE  );	
					GetDlgItem(  IDC_STATIC_contentFilter03  )->ShowWindow(  SW_HIDE  );	
					//
					GetDlgItem(  IDC_STATIC_clientIp1  )->ShowWindow(  SW_HIDE  );
				    GetDlgItem(  IDC_STATIC_filter10  )->ShowWindow(  SW_HIDE  );					
					GetDlgItem(  IDC_STATIC_filter11  )->ShowWindow(  SW_HIDE  );
					GetDlgItem(  IDC_STATIC_contentFilter12  )->ShowWindow(  SW_HIDE  );	
					GetDlgItem(  IDC_STATIC_contentFilter13  )->ShowWindow(  SW_HIDE  );	
					//
					GetDlgItem(  IDC_STATIC_clientIp2  )->ShowWindow(  SW_HIDE  );
				    GetDlgItem(  IDC_STATIC_filter20  )->ShowWindow(  SW_HIDE  );					
					GetDlgItem(  IDC_STATIC_filter21  )->ShowWindow(  SW_HIDE  );
					GetDlgItem(  IDC_STATIC_contentFilter22  )->ShowWindow(  SW_HIDE  );	
					GetDlgItem(  IDC_STATIC_contentFilter23  )->ShowWindow(  SW_HIDE  );	
					//
					GetDlgItem(  IDC_STATIC_clientIp3  )->ShowWindow(  SW_HIDE  );
				    GetDlgItem(  IDC_STATIC_filter30  )->ShowWindow(  SW_HIDE  );					
					GetDlgItem(  IDC_STATIC_filter31  )->ShowWindow(  SW_HIDE  );
					GetDlgItem(  IDC_STATIC_contentFilter32  )->ShowWindow(  SW_HIDE  );	
					GetDlgItem(  IDC_STATIC_contentFilter33  )->ShowWindow(  SW_HIDE  );	
					//
					GetDlgItem(  IDC_STATIC_clientIp4  )->ShowWindow(  SW_HIDE  );
				    GetDlgItem(  IDC_STATIC_filter40  )->ShowWindow(  SW_HIDE  );					
					GetDlgItem(  IDC_STATIC_filter41  )->ShowWindow(  SW_HIDE  );
					GetDlgItem(  IDC_STATIC_contentFilter42  )->ShowWindow(  SW_HIDE  );	
					GetDlgItem(  IDC_STATIC_contentFilter43  )->ShowWindow(  SW_HIDE  );	
					//
					GetDlgItem(  IDC_STATIC_clientIp5  )->ShowWindow(  SW_HIDE  );
				    GetDlgItem(  IDC_STATIC_filter50  )->ShowWindow(  SW_HIDE  );					
					GetDlgItem(  IDC_STATIC_filter51  )->ShowWindow(  SW_HIDE  );
					GetDlgItem(  IDC_STATIC_contentFilter52  )->ShowWindow(  SW_HIDE  );	
					GetDlgItem(  IDC_STATIC_contentFilter53  )->ShowWindow(  SW_HIDE  );	

					//
					break;
			case  1:  {
					  CDlgFilters	dlg;
				  
					  dlg.m_var.pStatusStruct  =  &m_var.u.showInfo.statusStruct;

					  //dlg.bSetDlgInfo(  0,  this->m_hWnd,  m_var.ulClientIp0,  m_var.filter0Buf,  m_var.filter1Buf,  m_var.contentFilter2Buf,  m_var.contentFilter3Buf  );
					  dlg.bSetDlgInfo(  0,  this->m_hWnd,  &m_var.filters  );
					  if  (  dlg.DoModal(  )  !=  IDOK  )  {
						  GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_SETCURSEL,  0,  0  );
						  //
						  GetDlgItem(  IDC_STATIC_clientIp0  )->ShowWindow(  SW_HIDE  );
						  GetDlgItem(  IDC_STATIC_filter00  )->ShowWindow(  SW_HIDE  );					
						  GetDlgItem(  IDC_STATIC_filter01  )->ShowWindow(  SW_HIDE  );	
						  GetDlgItem(  IDC_STATIC_contentFilter02  )->ShowWindow(  SW_HIDE  );	
						  GetDlgItem(  IDC_STATIC_contentFilter03  )->ShowWindow(  SW_HIDE  );	
						  //
						  GetDlgItem(  IDC_STATIC_clientIp1  )->ShowWindow(  SW_HIDE  );
						  GetDlgItem(  IDC_STATIC_filter10  )->ShowWindow(  SW_HIDE  );					
						  GetDlgItem(  IDC_STATIC_filter11  )->ShowWindow(  SW_HIDE  );	
						  GetDlgItem(  IDC_STATIC_contentFilter12  )->ShowWindow(  SW_HIDE  );	
						  GetDlgItem(  IDC_STATIC_contentFilter13  )->ShowWindow(  SW_HIDE  );	
						  //						  						  
						  GetDlgItem(  IDC_STATIC_clientIp2  )->ShowWindow(  SW_HIDE  );												  
						  GetDlgItem(  IDC_STATIC_filter20  )->ShowWindow(  SW_HIDE  );					
						  GetDlgItem(  IDC_STATIC_filter21  )->ShowWindow(  SW_HIDE  );	
						  GetDlgItem(  IDC_STATIC_contentFilter22  )->ShowWindow(  SW_HIDE  );	
						  GetDlgItem(  IDC_STATIC_contentFilter23  )->ShowWindow(  SW_HIDE  );	
						  //
						  GetDlgItem(  IDC_STATIC_clientIp3  )->ShowWindow(  SW_HIDE  );
						  GetDlgItem(  IDC_STATIC_filter30  )->ShowWindow(  SW_HIDE  );					
						  GetDlgItem(  IDC_STATIC_filter31  )->ShowWindow(  SW_HIDE  );	
						  GetDlgItem(  IDC_STATIC_contentFilter32  )->ShowWindow(  SW_HIDE  );	
						  GetDlgItem(  IDC_STATIC_contentFilter33  )->ShowWindow(  SW_HIDE  );	
						  //							
						  GetDlgItem(  IDC_STATIC_clientIp4  )->ShowWindow(  SW_HIDE  );
						  GetDlgItem(  IDC_STATIC_filter40  )->ShowWindow(  SW_HIDE  );					
						  GetDlgItem(  IDC_STATIC_filter41  )->ShowWindow(  SW_HIDE  );	
						  GetDlgItem(  IDC_STATIC_contentFilter42  )->ShowWindow(  SW_HIDE  );	
						  GetDlgItem(  IDC_STATIC_contentFilter43  )->ShowWindow(  SW_HIDE  );	
						  //
						  GetDlgItem(  IDC_STATIC_clientIp5  )->ShowWindow(  SW_HIDE  );
						  GetDlgItem(  IDC_STATIC_filter50  )->ShowWindow(  SW_HIDE  );					
						  GetDlgItem(  IDC_STATIC_filter51  )->ShowWindow(  SW_HIDE  );	
						  GetDlgItem(  IDC_STATIC_contentFilter52  )->ShowWindow(  SW_HIDE  );	
						  GetDlgItem(  IDC_STATIC_contentFilter53  )->ShowWindow(  SW_HIDE  );	

						  //
						  memset(  &m_var.filters,  0,  sizeof(  m_var.filters  )  );
						  						  						  
						  //
						  iCurSel  =  0;
						  break;  
					  }
					  MY_filter  *  pMem  =  &dlg.m_var.filters.mems[0];
					  //
					  GetDlgItem(  IDC_STATIC_clientIp0  )->ShowWindow( SW_SHOW  );
					  ulIp0  =  pMem->ulClientIp0;
					  ip[0]  =  0;
					  if  (  ulIp0  &&  !ulIp2Str(  ulIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
					  SetDlgItemText(  IDC_STATIC_clientIp0,  CString(  ip  )  );
					  //
					  //
					  GetDlgItem(  IDC_STATIC_filter00  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter00,  CString(  pMem->filter0Buf  )  );
					  GetDlgItem(  IDC_STATIC_filter01  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter01,  CString(  pMem->filter1Buf  )  );
					  //
					  GetDlgItem(  IDC_STATIC_contentFilter02  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_contentFilter02,  CString(  pMem->contentFilter2Buf  )  );
					  GetDlgItem(  IDC_STATIC_contentFilter03  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_contentFilter03,  CString(  pMem->contentFilter3Buf  )  );
					  //
					  pMem=&dlg.m_var.filters.mems[1];
					  GetDlgItem(  IDC_STATIC_clientIp1  )->ShowWindow( SW_SHOW  );
					  ulIp0  =  pMem->ulClientIp0;
					  ip[0]  =  0;
					  if  (  ulIp0  &&  !ulIp2Str(  ulIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
					  SetDlgItemText(  IDC_STATIC_clientIp1,  CString(  ip  )  );
					  //
					  //
					  GetDlgItem(  IDC_STATIC_filter10  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter10,  CString(  pMem->filter0Buf  )  );
					  GetDlgItem(  IDC_STATIC_filter11  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter11,  CString(  pMem->filter1Buf  )  );
					  //
					  GetDlgItem(  IDC_STATIC_contentFilter12  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_contentFilter12,  CString(  pMem->contentFilter2Buf  )  );
					  GetDlgItem(  IDC_STATIC_contentFilter13  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_contentFilter13,  CString(  pMem->contentFilter3Buf  )  );
					  //
					  pMem=&dlg.m_var.filters.mems[2];
					  GetDlgItem(  IDC_STATIC_clientIp2  )->ShowWindow( SW_SHOW  );
					  ulIp0  =  pMem->ulClientIp0;
					  ip[0]  =  0;
					  if  (  ulIp0  &&  !ulIp2Str(  ulIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
					  SetDlgItemText(  IDC_STATIC_clientIp2,  CString(  ip  )  );
					  //
					  //
					  GetDlgItem(  IDC_STATIC_filter20  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter20,  CString(  pMem->filter0Buf  )  );
					  GetDlgItem(  IDC_STATIC_filter21  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter21,  CString(  pMem->filter1Buf  )  );
					  //
					  GetDlgItem(  IDC_STATIC_contentFilter22  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_contentFilter22,  CString(  pMem->contentFilter2Buf  )  );
					  GetDlgItem(  IDC_STATIC_contentFilter23  )->ShowWindow(  SW_SHOW  );
					  GetDlgItemText(  IDC_STATIC_contentFilter23,  CString(  pMem->contentFilter3Buf  )  );
					  
					  //
					  pMem=&dlg.m_var.filters.mems[3];
					  GetDlgItem(  IDC_STATIC_clientIp3  )->ShowWindow( SW_SHOW  );
					  ulIp0  =  pMem->ulClientIp0;
					  ip[0]  =  0;
					  if  (  ulIp0  &&  !ulIp2Str(  ulIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
					  SetDlgItemText(  IDC_STATIC_clientIp3,  CString(  ip  )  );
					  
					  //
					  GetDlgItem(  IDC_STATIC_filter30  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter30,  CString(  pMem->filter0Buf  )  );
					  GetDlgItem(  IDC_STATIC_filter31  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter31,  CString(  pMem->filter1Buf  )  );
					  //
					  GetDlgItem(  IDC_STATIC_contentFilter32  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_contentFilter32,  CString(  pMem->contentFilter2Buf  )  );
					  GetDlgItem(  IDC_STATIC_contentFilter33  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_contentFilter33,  CString(  pMem->contentFilter3Buf  )  );
					  
					  //
					  pMem=&dlg.m_var.filters.mems[4];
					  GetDlgItem(  IDC_STATIC_clientIp4  )->ShowWindow( SW_SHOW  );
					  ulIp0  =  pMem->ulClientIp0;
					  ip[0]  =  0;
					  if  (  ulIp0  &&  !ulIp2Str(  ulIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
					  SetDlgItemText(  IDC_STATIC_clientIp4,  CString(  ip  )  );
					  
					  //
					  GetDlgItem(  IDC_STATIC_filter40  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter40,  CString(  pMem->filter0Buf  )  );
					  GetDlgItem(  IDC_STATIC_filter41  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter41,  CString(  pMem->filter1Buf  )  );
					  //
					  GetDlgItem(  IDC_STATIC_contentFilter42  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_contentFilter42,  CString(  pMem->contentFilter2Buf  )  );
					  GetDlgItem(  IDC_STATIC_contentFilter43  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_contentFilter43,  CString(  pMem->contentFilter3Buf  )  );
					  
					  //
					  pMem=&dlg.m_var.filters.mems[5];
					  GetDlgItem(  IDC_STATIC_clientIp5  )->ShowWindow( SW_SHOW  );
					  ulIp0  =  pMem->ulClientIp0;
					  ip[0]  =  0;
					  if  (  ulIp0  &&  !ulIp2Str(  ulIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
					  SetDlgItemText(  IDC_STATIC_clientIp5,  CString(  ip  )  );
					  
					  //
					  GetDlgItem(  IDC_STATIC_filter50  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter50,  CString(  pMem->filter0Buf  )  );
					  GetDlgItem(  IDC_STATIC_filter51  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter51,  CString(  pMem->filter1Buf  )  );
					  //
					  GetDlgItem(  IDC_STATIC_contentFilter52  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_contentFilter52,  CString(  pMem->contentFilter2Buf  )  );
					  GetDlgItem(  IDC_STATIC_contentFilter53  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_contentFilter53,  CString(  pMem->contentFilter3Buf  )  );
					  


					  //
					  m_var.filters  =  dlg.m_var.filters;
				
					  //	
					  GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_RESETCONTENT,  0,  0  );		
					  emptyGenericQ(  &m_var.infoQ  );
					  
					  //
					  }
					break;
			case  2:
				   myExportSth(  this  );
				   //
				   GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_SETCURSEL,  m_var.iCurSel,  0  );
				   return;
				   break;
			default:
					break;
	}
	m_var.iCurSel  =  iCurSel;

	
}


 
 int  printInfos(  void  **  ppElem,  unsigned  int  uiQNodes  )
{
	INFO_ELEM	*	pGuest;
	int					i;

	#ifndef  __DEBUG__
			 return  0;
	#endif

	TRACE(  _T(  "printInfos enters\n"  )  );

	for  (  i  =  0;  i  <  (  int  )uiQNodes;  i  ++  )  {
		 pGuest  =  (  INFO_ELEM  *  )ppElem[i];
		 TRACE(  _T(  "\t第%d个info是["  ),  i  );
		 OutputDebugString(  pGuest->wBuf  );
		 OutputDebugString(  _T(  "]\n"  )  );
	}

	TRACE(  _T(  "printInfos leaves\n"  )  );

	return  0;
}

 int  iCmpSystemTime(  SYSTEMTIME  *  t0,  SYSTEMTIME  *  t1  )
{
	int	 iRet	=	-1;

	if  (  t0->wYear  >  t1->wYear  )  return  1;
	if  (  t0->wYear  <  t1->wYear  )  return  -1;
	if  (  t0->wMonth  >  t1->wMonth  )  return  1;
	if  (  t0->wMonth  <  t1->wMonth  )  return  -1;
	if  (  t0->wDay  >  t1->wDay  )  return  1;
	if  (  t0->wDay  <  t1->wDay  )  return  -1;
	if  (  t0->wHour  >  t1->wHour  )  return  1;
	if  (  t0->wHour  <  t1->wHour  )  return  -1;
	if  (  t0->wMinute  >  t1->wMinute  )  return  1;
	if  (  t0->wMinute  <  t1->wMinute  )  return  -1;
	if  (  t0->wSecond  >  t1->wSecond  )  return  1;
	if  (  t0->wSecond  <  t1->wSecond  )  return  -1;
	if  (  t0->wMilliseconds  >  t1->wMilliseconds  )  return  1;
	if  (  t0->wMilliseconds  <  t1->wMilliseconds  )  return  -1;
	return  0;
}

 int  iCmpInfoElem(  INFO_ELEM  *  pElem0,  INFO_ELEM  *  pElem1  )
{
	int		iRet	=	-1;

	iRet  =  iCmpSystemTime(  &pElem0->when,  &pElem1->when  );
	if  (  iRet  )  return  iRet;
	
	return  pElem0->uiStep  -  pElem1->uiStep;
}

 int  __cdecl  myCompare_searchInfoByTime(  const  void  *  key,  const  void  *  pElemParam  )
{
	INFO_ELEM				*	pGuest			=	(  INFO_ELEM  *  )key;
	INFO_ELEM				*	pElem			=	*(  INFO_ELEM  **  )pElemParam;
	int iRet;
	iRet = iCmpInfoElem(  pGuest,  pElem  );
	if (iRet) return iRet;

	//
	return wcsicmp(pGuest->wBuf,pElem->wBuf  );	
}


 //


 //
 LRESULT CDlgQyCommStatus::OnQyComm(  WPARAM wParam,  LPARAM lParam  )
{
	long					lRet				=					-1;
	QY_WMBUF_COMM		*	pComm				=					( QY_WMBUF_COMM * )lParam;
	TCHAR					tBuf[1024];
	int						iCurSel;
	//
	QY_STATUS_STRUCT	*	pStatusStruct	=	&this->m_var.u.showInfo.statusStruct;

	bool bDbg = false;

	//
	if  (  !pComm  )  goto  errLabel;


	if (bDbg) {
		traceLogA("CPpQwmCommStatus::OnQyComm  enters");
	}

	//
	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_show:  {
				  QY_SHOW_STRUCT	*	pShowStruct				=	&(  (  QNM_WMBUF_SHOWSTRUCT  *  )pComm  )->showStruct;
				  char					stepBuf[16  +  1]		=	"    ";
				  char					clientIp[128  +  1]		=	"";
				  char					displayBuf[128]			=	"";
				  CString				fromStr,  toStr;
				  //CString				curSelStr;


				  
				  switch  (  pShowStruct->iType  )  {
						  case  CONST_qyShowType_qwmComm:
						  case  CONST_qyShowType_sysInfo:
						  case  CONST_qyShowType_debug:
						  case  CONST_qyShowType_debugWarning:
						  case  CONST_qyShowType_warning:
						  case  CONST_qyShowType_detail:		//  2009/05/10
						  //
						  case  CONST_qyShowType_qnmChking:
						  case  CONST_qyShowType_qnmProxyChking:
						  //
						  case  CONST_qyShowType_scanningNetworkSegment:
						  case  CONST_qyShowType_scanningIp:
						  case  CONST_qyShowType_bhbScanningNetworkSegment:
							  {
							  	//  2015/08/20
								#ifdef  __DEBUG__
										if  (  lstrlen(  pShowStruct->what  )  >=  200  )  {
											int  ii;
											ii  =  0;
										}
										if  (  0  )
										{
											int  k;
										}
								#endif

							  
							    //
								if  (  isQFull(  &m_var.infoQ  )  )  {
									if  (  !m_var.bAutoClearup  )  break;
									GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_RESETCONTENT,  0,  0  );
									emptyGenericQ(  &m_var.infoQ  );
								}
								
								//
								INFO_ELEM * pInfo_sel=NULL;
								//(INFO_ELEM*)m_var.ppInfos_sortedByTime[i];

								//  注意，要在加入之前先获取iCurSel, 因为排序功能会在加入后，重新调整的, 2007/06/01
								if  (  !m_var.infoQ.uiQNodes  )  iCurSel  =  -1;
								else  {
									  //m_list->GetSelectedCount
									  //
									  iCurSel  =  GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_GETCURSEL,  0,  0  );
									  if  (  iCurSel  ==  m_var.infoQ.uiQNodes  -  1  )  iCurSel  =  -1;
									  if  (  iCurSel  >=  0  )  {		//  未选或选最后一行,都是自动调整.不能跟踪.																										
										  //(  (  CListBox  *  )GetDlgItem(  IDC_LIST_display  )  )->GetText(  iCurSel,  curSelStr  );									
										  pInfo_sel = (INFO_ELEM*)m_var.ppInfos_sortedByTime[iCurSel];
									  }
								}

								//  
								myDisplayTime(  &pShowStruct->when,  displayBuf,  mycountof(  displayBuf  )  );
								if  (  pShowStruct->usStep  )  {
									_snprintf(  stepBuf,  mycountof(  stepBuf  ),  (  "%3d"  ),  (int)pShowStruct->usStep  );
								}
								else  safeStrnCpy(  "   ",  stepBuf,  mycountof(  stepBuf  )  );
								//
								if  (  !pShowStruct->ulClientIp  ||  !ulIp2Str(  pShowStruct->ulClientIp,  clientIp,  mycountof(  clientIp  )  )  )  safeStrnCpy(  "                      ",  clientIp,  mycountof(  clientIp  )  );
								//
								if  (  pShowStruct->who_to[0]  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s  %-17s %-24s %-6s %s%s"  ),  CString(  displayBuf  +  5  ),  CString(  stepBuf  ),  CString(  clientIp  ),  CString(  pShowStruct->who_from  )  +  " -> "  +  pShowStruct->who_to,  pShowStruct->whereBuf,  pShowStruct->doStr,  pShowStruct->what  );
								else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s  %-17s %-24s  %-6s %s%s"  ),  CString(  displayBuf  +  5  ),  CString(  stepBuf  ),  CString(  clientIp  ),  pShowStruct->who_from,  pShowStruct->whereBuf,  pShowStruct->doStr,  pShowStruct->what  );
								_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s       (%d,%d)%d%%"  ),  tBuf,  pShowStruct->dwThreadId,  pShowStruct->dwProcessId,  (int)pShowStruct->ucPercent_showInfoQ  );
								//  OutputDebugString(  CString(  "qwmComm:  [  "  )  +  tBuf  +  "]\n"  );

								//  对内容做一下过滤
								if  (  !isFiltersEmpty(  &m_var.filters  )  )  {

									//									
									fromStr  =  CString(  pShowStruct->who_from  );  fromStr.MakeUpper(  );									
									toStr  =  CString(  pShowStruct->who_to  );  toStr.MakeUpper(  );

									CString		str;									
									str  =  tBuf;									
									str.MakeUpper(  );

									//
									int  i;
									for  (  i  =  0;  i  <  mycountof(  m_var.filters.mems  );  i  ++  )  {
										MY_filter  *  pMem  =  &m_var.filters.mems[i];

										if  (  !pMem->ulClientIp0  
											&&  !pMem->filter0Buf[0]  &&  !pMem->filter1Buf[0]
											&&  !pMem->contentFilter2Buf[0]  &&  !pMem->contentFilter3Buf[0]  )  continue;

										//
										if  (  pMem->ulClientIp0  )  {
											if  (  pShowStruct->ulClientIp  !=  pMem->ulClientIp0  )  continue;
										}
										if  (  pMem->filter0Buf[0]  )  {
											if  (  !_tcsstr(  fromStr,  pMem->filter0Buf  )  &&  !_tcsstr(  toStr,  pMem->filter0Buf  )  )  continue;
										}									
										if  (  pMem->filter1Buf[0]  )  {																				
											if  (  !_tcsstr(  fromStr,  pMem->filter1Buf  )  &&  !_tcsstr(  toStr,  pMem->filter1Buf  )  )  continue;
										}

										//										
										if  (  pMem->contentFilter2Buf[0]  )  {																				
											if  (  !_tcsstr(  str.GetBuffer(  0  ),  pMem->contentFilter2Buf  )  )  continue;
										}
										if  (  pMem->contentFilter3Buf[0]  )  {
											if  (  !_tcsstr(  str.GetBuffer(  0  ),  pMem->contentFilter3Buf  )  )  continue;									
										}

										//
										break;								
									}
									//
									if  (  i  ==  mycountof(  m_var.filters.mems  )  )  break;
								
								}	
								

							    //  
								INFO_ELEM		info;
								INFO_ELEM	*	pElem;
								INFO_ELEM	**	ppElem;
								int				iNewPos,  i;

								//  printInfos(  m_var.ppInfos_sortedByStr,  m_var.infoQ.uiQNodes  );

								memset(  &info,  0,  sizeof(  info  )  );
								memcpy(  &info.when,  &pShowStruct->when,  sizeof(  info.when  )  );
								info.uiStep  =  pShowStruct->usStep;
								lstrcpyn(  info.wBuf,  tBuf,  mycountof(  info.wBuf  )  );

								//  2015/08/20
								#ifdef  __DEBUG__
										if  (  lstrlen(  info.wBuf  )  >=  200  )  {
											int  ii;
											ii  =  0;
										}
										if  (  0  )
										{
											int  k;
											info.wBuf[0]  =  0;
											for  (  k  =  0;  k  <  mycountof(  info.wBuf  );  k  ++  )  {
												 _sntprintf(  info.wBuf,  mycountof(  info.wBuf  ),  _T(  "%s%d"  ),  info.wBuf,  k  %  10  );
											}
											info.wBuf[mycountof(  info.wBuf  )  -  1]  =  0;
										}
								#endif

								/*
								ppElem  =  (  INFO_ELEM  **  )bsearch(  &info,  m_var.ppInfos_sortedByStr,  m_var.infoQ.uiQNodes,  sizeof(  void  *  ),  myCompare_searchInfoByStr  );  
								if  (  ppElem  )  {
									//  traceLogA(  "这表明可能有2条相同的信息,忽略掉了"  );
									break;	//  这表明可能有2条相同的信息,忽略掉了
								}
								*/
								if  (  qPostMsg(  &info,  sizeof(  info  ),  &m_var.infoQ,  _T(  "dlgQyCommStatus.OnQyComm"  )))  goto  errLabel;
								if  (  m_var.infoQ.uiQNodes  <=  1  )  {
									iNewPos  =  0;
									m_var.ppInfos_sortedByTime[iNewPos]  =  m_var.infoQ.pRear->qElemMemory.m_pBuf;
									}
								else  {
									  for  (  i  =  m_var.infoQ.uiQNodes  -  2;  i  >=  0;  i  --  )  {
										   pElem  =  (  INFO_ELEM  *  )m_var.ppInfos_sortedByTime[i];

										   int  iCmp;
										   iCmp  =  iCmpInfoElem(  &info,  pElem  );
										   if  (  iCmp  >=  0  )  {
											   iNewPos  =  i  +  1;
											   m_var.ppInfos_sortedByTime[iNewPos]  =  m_var.infoQ.pRear->qElemMemory.m_pBuf;
											   break;
										   }
										   //  往后移一个
										   m_var.ppInfos_sortedByTime[i  +  1]  =  m_var.ppInfos_sortedByTime[i];									
									  }
									  if  (  i  ==  -1  )  {
										  iNewPos  =  0;
										  //  m_var.ppInfos_sortedByTime[iNewPos]  =  m_var.infoQ.pRear->pQElem;
										  m_var.ppInfos_sortedByTime[iNewPos]  =  m_var.infoQ.pRear->qElemMemory.m_pBuf;
									  }
								}
								GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_INSERTSTRING,  iNewPos,  (  LPARAM  )(  (  INFO_ELEM  *  )m_var.ppInfos_sortedByTime[iNewPos]  )->wBuf  );

								//  2006/04/16
								if  (  iCurSel  >=  0  )  {
#if 0
									memset(  &info,  0,  sizeof(  info  )  );
									//lstrcpyn(  info.wBuf,  curSelStr,  mycountof(  info.wBuf  )  );
									info = *pInfo_sel;

									ppElem  =  (  INFO_ELEM  **  )bsearch(  &info,  m_var.ppInfos_sortedByTime,  m_var.infoQ.uiQNodes,  sizeof(  void  *  ),  myCompare_searchInfoByTime  );  
									if  (  !ppElem  )  break;

									iCurSel  =  (  ppElem  -  (  INFO_ELEM  **  )m_var.ppInfos_sortedByTime  );

									GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_SETCURSEL,  iCurSel,  0  );
#endif
									}
								else  {
									  iCurSel  =  m_var.infoQ.uiQNodes  -  1;
									  GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_SETCURSEL,  iCurSel,  0  );								
								}
								
								}
								//
								break;
						  case  CONST_qyShowType_serviceStatus:
						  case  CONST_qyShowType_qwmState:  {
							    //
							    bool  bCli  =  bAppClient(  qyGetAppType(  0,  NULL  )  );

								//						  
								if (bCli && !isFilterEmpty_state(&m_var.filters)) {
									//
									//																	
									fromStr = CString(pShowStruct->who_from);  fromStr.MakeUpper();
									toStr = CString(pShowStruct->who_to);  toStr.MakeUpper();

									//
									int  i;
									for (i = 0; i < mycountof(m_var.filters.mems); i++) {

										MY_filter* pMem = &m_var.filters.mems[i];

										//
										if (!pMem->filter0Buf[0] && !pMem->filter1Buf[0])  continue;

										//
										if (pMem->filter0Buf[0]) {
											if (!_tcsstr(fromStr, pMem->filter0Buf) && !_tcsstr(toStr, pMem->filter0Buf))  continue;
										}
										if (pMem->filter1Buf[0]) {
											if (!_tcsstr(fromStr, pMem->filter1Buf) && !_tcsstr(toStr, pMem->filter1Buf))  continue;
										}

										//
										break;
									}
									if (i == mycountof(m_var.filters.mems))  break;
								}


								//
								if (pShowStruct->usStateType) {
									switch (pShowStruct->usStateType) {
											case  CONST_stateType_sys:
												  ::SendMessage(g_pStatusStruct->hWnd_sys, CONST_qyWm_comm, wParam, lParam);
												  break;
											case  CONST_stateType_tasks:
												  ::SendMessage(g_pStatusStruct->hWnd_tasks, CONST_qyWm_comm, wParam, lParam);
												  break;
											case  CONST_stateType_players:
												  ::SendMessage(g_pStatusStruct->hWnd_players, CONST_qyWm_comm, wParam, lParam);
												  break;
											case  CONST_stateType_talks:
												  ::SendMessage(g_pStatusStruct->hWnd_talks, CONST_qyWm_comm, wParam, lParam);
												  break;
											case  CONST_stateType_qs:
												  ::SendMessage(g_pStatusStruct->hWnd_qs, CONST_qyWm_comm, wParam, lParam);
												  break;
											case  CONST_stateType_others:
												  ::SendMessage(g_pStatusStruct->hWnd_others, CONST_qyWm_comm, wParam, lParam);
												  break;
												  //
											default:
												traceLog((TCHAR*)_T("unprocessed stateType"));
												break;
									}

									//
									break;
								}


							    //
							    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s%s%s"  ),  pShowStruct->who_from,  pShowStruct->whereBuf,  pShowStruct->doStr,  pShowStruct->what  );
								_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %d:%02d:%02d"  ),  tBuf,  (  int  )pShowStruct->when.wHour,  (  int  )pShowStruct->when.wMinute,  (  int  )pShowStruct->when.wSecond  );
								//
								//_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %d/%d"  ),  tBuf,  pStatusStruct->pipe.nConnections,  pStatusStruct->pipe.nPipes  );
								//
							#if  0
								if  (  !lstrcmpi(  pShowStruct->who_from,  qyGetDesByType1(  CONST_qyServiceIdTable,  CONST_qyServiceId_is  )  )  )  SetDlgItemText(  IDC_STATIC_serviceStatus_is,  tBuf  );
								else  SetDlgItemText(  IDC_STATIC_serviceStatus_netMc,  tBuf  );
							#endif
								//
								switch  (  pShowStruct->iPos_toDisplay  )  {
										case  0:
												SetDlgItemText(  IDC_STATIC_serviceStatus_netMc,  tBuf  );
												break;
										case  1:
										default:
												SetDlgItemText(  IDC_STATIC_serviceStatus_is,  tBuf  );
												break;
								}							
															}
								//
								break;
												
						  case  CONST_qyShowType_addChkingType:
							    OutputDebugString(  _T(  "addChkingType: 这里不用了\n"  )  );
							    /*
								tTrim(  pShowStruct->who_from  );
							    if  (  !pShowStruct->who_from[0]  )  break;
							    if  (	CB_ERR  !=  GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_FINDSTRING,  -1,  (  LPARAM  )pShowStruct->who_from  )  )  break;
								GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )pShowStruct->who_from  );
								*/
							    break;					  							    
						  case  CONST_qyShowType_refresh:
							    OutputDebugString(  _T(  "可以刷新状态, 暂时不用\n"  )  );
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

	if (bDbg) {
		traceLogA("CPpQwmCommStatus::OnQyComm  leaves");
	}

	return  lRet;
}



//
LRESULT CDlgQyCommStatus::OnQyPostComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	QNM_WMBUF_SHOWSTRUCT	wmBufShowStruct;
	unsigned  int  len;
	int  i;


	return  0;
}




//
void CDlgQyCommStatus::OnBnClickedRadioqwmcomm()
{
	// TODO: 在此添加控件通知处理程序代码
		m_var.u.showInfo.iShowFlgs[0]  =  (  1  <<  CONST_qyShowType_serviceStatus  )
											|  (  1  <<  CONST_qyShowType_qwmComm  )
												|  (  1  <<  CONST_qyShowType_qmdState  )
													|  (  1  <<  CONST_qyShowType_sysInfo  )
														|  (  1  <<  CONST_qyShowType_debug  )
															|  (  1  <<  CONST_qyShowType_debugWarning  )
																|  (  1  <<  CONST_qyShowType_warning  )  
																	|  (  1  <<  CONST_qyShowType_detail  );

}

void CDlgQyCommStatus::OnBnClickedRadioqnmchking()
{
	// TODO: 在此添加控件通知处理程序代码

	m_var.u.showInfo.iShowFlgs[0]  =  (  1  <<  CONST_qyShowType_serviceStatus  )
											|  (  1  <<  CONST_qyShowType_qnmChking  )
												|  (  1  <<  CONST_qyShowType_addChkingType  );

}

void CDlgQyCommStatus::OnBnClickedRadioscanningip()
{
	// TODO: 在此添加控件通知处理程序代码

	m_var.u.showInfo.iShowFlgs[0]  =  (  1  <<  CONST_qyShowType_scanningNetworkSegment  )
											|  (  1  <<  CONST_qyShowType_scanningIp  )
												|  (  1  <<  CONST_qyShowType_serviceStatus  )
													|  (  1  <<  CONST_qyShowType_refresh  )
														|  (  1  <<  CONST_qyShowType_bhbScanningNetworkSegment  );

}

void CDlgQyCommStatus::OnBnClickedCheckautoclearup()
{
	// TODO: 在此添加控件通知处理程序代码
	if  (  BST_CHECKED  ==  GetDlgItem(  IDC_CHECK_autoClearup  )->SendMessage(  BM_GETCHECK,  0,  0  )  )  {
		m_var.bAutoClearup  =  TRUE;
		}
	else  m_var.bAutoClearup  =  FALSE;

}

void CDlgQyCommStatus::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::PostNcDestroy();

	if  (  m_var.ppInfos_sortedByTime  )  free(  m_var.ppInfos_sortedByTime  );
	if  (  m_var.bInfoQInited  )  exitGenericQ(  &m_var.infoQ  );
	//  2015/08/22

}


//void CDlgQyCommStatus::OnMenuTask()
//{
//	// TODO: 在此添加命令处理程序代码
//}


void CDlgQyCommStatus::OnMenuTasks()
{
	// TODO: 在此添加命令处理程序代码
	int ii = 0;
	int stateType = CONST_stateType_tasks;
	//
	viewDlgState(stateType);

}


void CDlgQyCommStatus::OnMenuPlayers()
{
	// TODO: 在此添加命令处理程序代码
	int ii = 0;
	int stateType = CONST_stateType_players;
	//
	viewDlgState(stateType);

}


void CDlgQyCommStatus::OnMenuTalks()
{
	// TODO: 在此添加命令处理程序代码
	int ii = 0;
	int stateType = CONST_stateType_talks;
	//
	viewDlgState(stateType);

}


void CDlgQyCommStatus::OnQs()
{
	// TODO: 在此添加命令处理程序代码
	int stateType = CONST_stateType_qs;
	//
	viewDlgState(stateType);
}


void CDlgQyCommStatus::OnSys()
{
	// TODO: 在此添加命令处理程序代码
	int stateType = CONST_stateType_sys;
	//
	viewDlgState(stateType);
}


void CDlgQyCommStatus::OnOthers()
{
	// TODO: 在此添加命令处理程序代码
	int stateType = CONST_stateType_others;
	//
	viewDlgState(stateType);

}


int CDlgQyCommStatus::test_add()
{

#if 0
	for(int i=0; i<1000; i++)
		m_database.push_back( CSampleData() );

	//Resize the list to add the elements to the list
	m_list->SetItemCount( m_database.size() );
#endif


	return 0;
}

void CDlgQyCommStatus::clear()
{
	//m_database.clear();
	emptyGenericQ( &m_var.infoQ);

	m_list->SetItemCount(0);

}


//
void CDlgQyCommStatus::OnLvnGetdispinfoListdisplay(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here


		//Create a pointer to the item
	LV_ITEM* pItem= &(pDispInfo)->item;

	//Which item number?
	int itemid = pItem->iItem;

	//Do the list need text information?
	if (pItem->mask & LVIF_TEXT)
	{
		CString text;

		//Which column?
		if(pItem->iSubItem == 0)
		{
			//Text is name
			TCHAR tBuf[128];
			_sntprintf( tBuf,mycountof( tBuf ),  _T(  "%d"  ),  itemid  );
			//text = m_database[itemid].m_seqNo;
			text=tBuf;
		}
		else if (pItem->iSubItem == 1)
		{
			//Text is slogan
			//text = m_database[itemid].m_str;
			text=(  (  INFO_ELEM  *  )m_var.ppInfos_sortedByTime[itemid]  )->wBuf;
		}

		//Copy the text to the LV_ITEM structure
		//Maximum number of characters is in pItem->cchTextMax
		lstrcpyn(pItem->pszText, text, pItem->cchTextMax);
	}

	//Do the list need image information?
	if( pItem->mask & LVIF_IMAGE) 
	{
		//Set which image to use
		pItem->iImage=0;//m_database[itemid].m_image;
		
		//Show check box?
		
	}




	//
	*pResult = 0;
}


void CDlgQyCommStatus::OnLvnOdfinditemListdisplay(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVFINDITEM pFindInfo = reinterpret_cast<LPNMLVFINDITEM>(pNMHDR);
	// TODO: Add your control notification handler code here
	//*pResult = 0;

		/* pFindInfo->iStart is from which item we should search.
	   We search to bottom, and then restart at top and will stop
	   at pFindInfo->iStart, unless we find an item that match
	 */

	// Set the default return value to -1
	// That means we didn't find any match.
	*pResult = -1;

	//Is search NOT based on string?
	if( (pFindInfo->lvfi.flags & LVFI_STRING) == 0 )
	{
		//This will probably never happend...
		return;
	}

	/*
		Let's look on a sample list;
		
		  Name
		  Anders
		* Anna
		  Annika
		  Bob
		  Emma
		  Emmanuel

		Anna is selected. 
		If "A" is written, Annika should be selected.
		If "AND" is written, Anders should be selected. 
		If "ANNK" is written, the selection should stay on Anna.
		If "E" is written, Emma should be selected.

    */

	//This is the string we search for
	CString searchstr = pFindInfo->lvfi.psz;

//	TRACE(_T("Find: %s\n"), searchstr);
	
	int startPos = pFindInfo->iStart;
	//Is startPos outside the list (happens if last item is selected)
	if(startPos >= m_list->GetItemCount())
		startPos = 0;

	int currentPos=startPos;
	
	//Let's search...
	do
	{
		TCHAR * pT=(  (  INFO_ELEM  *  )m_var.ppInfos_sortedByTime[currentPos]  )->wBuf;

		//Do this word begins with all characters in searchstr?
		if( _tcsnicmp(pT, searchstr, searchstr.GetLength()) == 0)
		{
			//Select this item and stop search.
			*pResult = currentPos;
			break;
		}

		//Go to next item
		currentPos++;

		//Need to restart at top?
		if(currentPos >= m_list->GetItemCount())
			currentPos = 0;

	//Stop if back to start
	}while(currentPos != startPos);		




}


void CDlgQyCommStatus::OnLvnOdcachehintListdisplay(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCACHEHINT pCacheHint = reinterpret_cast<LPNMLVCACHEHINT>(pNMHDR);
	// TODO: Add your control notification handler code here

	/*	TRACE(	_T("Chache item %d to item %d\n"),
			pCacheHint->iFrom,
			pCacheHint->iTo );*/

	//... cache the data pCacheHint->iFrom to pCacheHint->iTo ...



	//
	*pResult = 0;
}
