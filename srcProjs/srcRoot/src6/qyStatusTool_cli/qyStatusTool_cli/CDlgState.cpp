// CDlgState.cpp: 实现文件
//

#include	"StdAfx.h"
//#include "pch.h"
#include	"resource.h"

#include	<winsvc.h>
#include	<vfw.h>

#define  __noDbg_new__


#include	"qmCommon.h"
#include	"qnmCommProc.h"

#include	"qyStatusToolCommon.h"


#include "CDlgState.h"
#include "afxdialogex.h"
#include <qyCusResPublic.h>

//
__declspec(dllexport)  int viewDlgState(int stateType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int								iErr = -1;




	CDlgState *pDlg = NULL;
	int								iStatus_ia = 0;
	BOOL							bMin = FALSE;

	//  traceLogA(  "viewInstantAssistant enters"  );

	//
	HWND* phTool = NULL;
	switch  (  stateType  ) {
			case  CONST_stateType_sys:
				  phTool = &g_pStatusStruct->hWnd_sys;
				  break;
			case  CONST_stateType_tasks:
				  phTool = &g_pStatusStruct->hWnd_tasks;
				  break;
			case  CONST_stateType_players:
				phTool = &g_pStatusStruct->hWnd_players;
				break;
			case  CONST_stateType_talks:
				phTool = &g_pStatusStruct->hWnd_talks;
				break;
			case  CONST_stateType_qs:
				phTool = &g_pStatusStruct->hWnd_qs;
				break;
			case  CONST_stateType_others:
				phTool = &g_pStatusStruct->hWnd_others;
				break;
			default:
				goto  errLabel;
	}



#ifdef  __DEBUG__
	int  i = sizeof(int);
	//  traceLog(  _T(  "viewIa, xPos %d, yPos %d"  ),  xPos,  yPos  );
	//  goto  errLabel;
#endif



#if 10
	if (IsWindow(*phTool)) {
		//
		//
		MACRO_SetForegroundWindow(*phTool);
		//
		iErr = 0;  goto  errLabel;
	}
#endif

	

	//

			 //  2010/12/18
	HWND	hFore = GetForegroundWindow();
	HWND	hAbove = NULL;	//  findWndAbove(  hParent  );

	//
	RECT							rect;

	HWND	hParent = ::GetDesktopWindow();// hWndEvent;	//  hDlgWalls;
	pDlg = new  CDlgState(NULL);
	if (!pDlg)  goto  errLabel;


	//
	pDlg->m_var.m_usStateType = stateType;
	pDlg->m_var.m_hParent = hParent;
		

	//
	if (!pDlg->Create(rect))  goto  errLabel;


	//	ShowWindow(  pDlg->m_hWnd,  SW_SHOW  );
	// 

	int  flg = SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW;
	SetWindowPos(pDlg->m_hWnd, hAbove, 0, 0, 0, 0, flg);
	//


	//
	* phTool = pDlg->m_hWnd;


	iErr = 0;

errLabel:

	if (iErr) {
		if (pDlg)  delete  pDlg;
	}
	if (!iErr) {
	}

	//  traceLogA(  "viewInstantAssistant leaves, iErr is %d",  iErr  );

	return  iErr;
}




// CDlgState 对话框

IMPLEMENT_DYNAMIC(CDlgState, CDialog)

CDlgState::CDlgState(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_state, pParent)
{
	memset(&m_var, 0, sizeof(m_var));

}

CDlgState::~CDlgState()
{
	if (m_var.m_pShowStructs) {
		myfree(m_var.m_pShowStructs); m_var.m_pShowStructs = NULL;
	}
}


//
	//
BOOL  CDlgState::bQuitDlg()
{
	DestroyWindow();
	return  true;
  }

BOOL  CDlgState::Create(const RECT& rect)
{
	if (!CDialog::Create(IDD_state, CWnd::FromHandle(m_var.m_hParent)))  goto  errLabel;

	errLabel:
	return true;
}


void CDlgState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgState, CDialog)
	ON_WM_CLOSE()
	ON_WM_SIZE()

	ON_MESSAGE(QY_WM_COMM, OnQyComm)
	ON_MESSAGE(CONST_qyWm_postComm, OnQyPostComm)

END_MESSAGE_MAP()


// CDlgState 消息处理程序


void CDlgState::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::PostNcDestroy();

	delete this;

	//
	traceLog((TCHAR*)_T("CDlgState::PostNcDestroy"));

}




void CDlgState::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialog::OnClose();
	bQuitDlg();
}


void CDlgState::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
	bQuitDlg();

}


void  sizeDlg(CDlgState* pDlg)
{

	int					iWidth = 0;
	int					iHeight = 0;

	int					x, y;
	RECT				rect, rc;
	int					nWidth_autoClearup, nHeight_autoClearup;
	int					iW, iH;

	pDlg->GetClientRect(&rect);
	iWidth = rect.right - rect.left;  iHeight = rect.bottom - rect.top;
	if (iWidth < 10 || iHeight < 10)  goto  errLabel;

	//
	pDlg->m_var.iEdge_list_x = 30;
	pDlg->m_var.iTop_list = 30;


	//
	HDWP			hDwp;
	int				nTotal;	nTotal = 1;

	CWnd* pCtrl;
	pCtrl = pDlg->GetDlgItem(IDC_LIST_display);
	if (pCtrl == NULL) goto errLabel;


	hDwp = BeginDeferWindowPos(nTotal);
	if (hDwp) {

		pCtrl = pDlg->GetDlgItem(IDC_LIST_display);
		x = pDlg->m_var.iEdge_list_x;
		y = pDlg->m_var.iTop_list;//23;				//  这个23是因为前面没有把坐标统一成window坐标或者client坐标。混用了，所以用23这个修正参数。
		iW = iWidth - 2 * pDlg->m_var.iEdge_list_x;
		iH = iHeight - 2  *  pDlg->m_var.iTop_list;
		DeferWindowPos(hDwp, pCtrl->m_hWnd, NULL, x, y, iW, iH, SWP_NOZORDER);

		//
		EndDeferWindowPos(hDwp);
	}

errLabel:
	return;

}


void CDlgState::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CWnd* pCtrl = this->GetDlgItem(IDC_LIST_display);

	// TODO: 在此处添加消息处理程序代码
	sizeDlg(this);
}

//
QY_COLUMNINFO	CONST_stateListColumns[] =										//  2013/02/17
{
	{	0,	_T("ID"),						0,	LVCFMT_LEFT, 80,		1},	//  13  
	{	0,	_T("seqNo"),					0,	LVCFMT_LEFT, 0,			1},	//  13  
	{	0,	_T("taskId"),					0,	LVCFMT_LEFT, 80,		1},	//  13  
	{	0,	_T("content"),					0,	LVCFMT_LEFT, 1430,		1},	//  1
	{	-1,																	},
};



BOOL CDlgState::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CWnd* pCtrl = this->GetDlgItem(IDC_LIST_display);
	m_var.m_pListCtrl = (CListCtrl*)pCtrl;
	int i;
	int nFields;

	//
	TCHAR* pTitle = _T("dlgState");
	switch (m_var.m_usStateType) {
	case  CONST_stateType_sys:
		pTitle = _T("sys");
		break;
	case  CONST_stateType_tasks:
		pTitle = _T("tasks");
		break;
	case  CONST_stateType_players:
		pTitle = _T("players");
		break;
	case  CONST_stateType_talks:
		pTitle = _T("talks");
		break;
	case  CONST_stateType_qs:
		pTitle = _T("qs");
		break;
	case  CONST_stateType_others:
		pTitle = _T("others");
		break;
	default:
		break;
	}
	this->SetWindowText(pTitle);

	//
	m_var.m_grp_maxCnt = 50;
	m_var.m_maxCnt = mycountof(m_var.grps)  *  m_var.m_grp_maxCnt;
	int size = m_var.m_maxCnt * sizeof(QY_SHOW_STRUCT);
	m_var.m_pShowStructs = (QY_SHOW_STRUCT*)mymalloc(size);
	if (m_var.m_pShowStructs == NULL)goto errLabel;

	//
	CListCtrl* pListCtrl = m_var.m_pListCtrl;
	if (!pListCtrl)  goto  errLabel;

	//
	pListCtrl->ModifyStyle(LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL);
	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE);

	QY_COLUMNINFO* pColumnInfo;
	pColumnInfo = (QY_COLUMNINFO*)CONST_stateListColumns;
	if (!pColumnInfo)  goto  errLabel;

	//CString			str;
	LV_COLUMN		lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for (i = 0; pColumnInfo[i].type != -1; i++) {
		lvc.iSubItem = i;
		lvc.pszText = pColumnInfo[i].label;
		lvc.cx = pColumnInfo[i].width;
		lvc.fmt = pColumnInfo[i].fmt;
		pListCtrl->InsertColumn(i, &lvc);
	}
	nFields = i;

	pListCtrl->DeleteAllItems();



	//
	sizeDlg(this);

	//
#if 0
	pListCtrl->InsertItem(0, _T("0"));
	pListCtrl->SetItemText(0, 2, _T("00"));
	pListCtrl->InsertItem(1, _T("1"));
	pListCtrl->SetItemText(1, 2, _T("11"));
	pListCtrl->InsertItem(2, _T("2"));
	pListCtrl->SetItemText(2, 2, _T("22"));
#endif


	//
errLabel:

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

bool isSame(SYSTEMTIME* pw0, SYSTEMTIME* pw1)
{
	if (!memcmp(pw0, pw1, sizeof(SYSTEMTIME))) return true;
	return false;
}

bool isSame(QY_SHOW_STRUCT* pss0, QY_SHOW_STRUCT* pss1)
{
	if  (  !_tcsicmp(pss0->who_from,pss1->who_from  )
		&&  pss0->iTaskId == pss1->iTaskId
		&& !_tcscmp(pss0->doStr, pss1->doStr)
		&& !_tcscmp(pss0->what, pss1->what)
		) 
	{
		return true;
	}
	return false;
}

//
int  getShowStr(QY_SHOW_STRUCT* pShowStruct, TCHAR* tStr, int cntof_tStr)
{
	_sntprintf(tStr, cntof_tStr, _T("%s %s"), pShowStruct->doStr, pShowStruct->what);

	return  0;
}


//
int CDlgState::resetItem(int nItem)
{
	if (nItem >= m_var.m_maxCnt) {
		return  -1;
	}
	m_var.m_pListCtrl->SetItemText(nItem, 1, _T(""));
	m_var.m_pListCtrl->SetItemText(nItem, 2, _T(""));
	m_var.m_pListCtrl->SetItemText(nItem, 3, _T(""));
	//
	memset(&m_var.m_pShowStructs[nItem], 0, sizeof(QY_SHOW_STRUCT));

	return  0;
}


//
int CDlgState::procShowInfo(QY_SHOW_STRUCT* pShowStruct)
{
	int  iErr = -1;
	int  i;
	TCHAR tId[20] = _T("");
	TCHAR tSeqNo[10] = _T("");
	TCHAR tBuf[128];
	TCHAR tShowStr[1024]=_T("");
	int nSubItem_seqNo = 1;
	int nSubItem_taskId = 2;
	int nSubItem_content = 3;
	
	//
	QY_MESSENGER_ID		idInfo;
	idInfo.ui64Id  = _ttol(pShowStruct->who_from);
	if (idInfo.ui64Id == 0) {
		return  -1;
	}
	int  j;
	for (j = 0; j < mycountof(m_var.grps); j++) {
		if (idInfo.ui64Id == m_var.grps[j].idInfo.ui64Id)  break;
	}
	STATE_grp* pGrp = NULL;
	int index_grp = 0;
	int nItem;
	if (j < mycountof(m_var.grps)) {
		pGrp = &m_var.grps[j];
		index_grp = j;
	}
	else  {

		int  k;
		for (k = 0; k < mycountof(m_var.grps); k++) {
			if (m_var.grps[k].idInfo.ui64Id == 0)break;
		}
		if (k == mycountof(m_var.grps)) {
			goto  errLabel;
		}
		pGrp = &m_var.grps[k];
		pGrp->idInfo.ui64Id = idInfo.ui64Id;
		index_grp = k;
		//
		for (i = 0; i < m_var.m_grp_maxCnt; i++) {
			nItem = index_grp * m_var.m_grp_maxCnt + i;
			m_var.m_pListCtrl->InsertItem(nItem, _ltot(pGrp->idInfo.ui64Id, tId, 10));
		}
	}

	//
	if (pShowStruct->iPos_toDisplay == -1) {
		if (!isSame(&pShowStruct->when, &pGrp->m_when)) {
			for  (  i  =  0;i<m_var.m_grp_maxCnt;i++){
				nItem = index_grp * m_var.m_grp_maxCnt + i;					  
				resetItem(nItem);
			}
			pGrp->m_cnt = 0;
			iErr = 0;  goto  errLabel;
		}
		for (i = pGrp->m_last_iPos  +  1; i < m_var.m_grp_maxCnt;i++) {
			nItem = index_grp * m_var.m_grp_maxCnt + i;
			resetItem(nItem);
		}
		pGrp->m_cnt = pGrp->m_last_iPos + 1;
		//
		iErr = 0;  goto  errLabel;
	}
	if (pShowStruct->iPos_toDisplay >= m_var.m_grp_maxCnt) goto errLabel;
	if (pShowStruct->iPos_toDisplay == 0) {
		pGrp->m_when = pShowStruct->when;
	}
	if (!isSame(&pShowStruct->when, &pGrp->m_when)) goto  errLabel;
	//
	if (!isSame(pShowStruct, &m_var.m_pShowStructs[pShowStruct->iPos_toDisplay])) {
		nItem = index_grp * m_var.m_grp_maxCnt + pShowStruct->iPos_toDisplay;
		m_var.m_pListCtrl->SetItemText(nItem, nSubItem_seqNo, _ltot(pShowStruct->iPos_toDisplay, tBuf, 10));
		m_var.m_pListCtrl->SetItemText(nItem, nSubItem_taskId, _ltot(pShowStruct->iTaskId, tBuf, 10));
		getShowStr(pShowStruct, tShowStr, mycountof(tShowStr));
		m_var.m_pListCtrl->SetItemText(nItem, nSubItem_content, tShowStr);
		//
		m_var.m_pShowStructs[nItem] = *pShowStruct;
	}
	pGrp->m_last_iPos = pShowStruct->iPos_toDisplay;
	//
	iErr = 0;  goto  errLabel;

errLabel:
	return  iErr;

}


//
LRESULT CDlgState::OnQyComm(WPARAM  wParam, LPARAM  lParam)
{
	QY_WMBUF_COMM* pComm = (QY_WMBUF_COMM*)lParam;

	switch (pComm->uiType) {
			case  CONST_qyWmParam_show: {
				  QY_SHOW_STRUCT* pShowStruct = &((QNM_WMBUF_SHOWSTRUCT*)pComm)->showStruct;
				  if (pShowStruct->usStateType != m_var.m_usStateType)  goto  errLabel;
				  //
				  int  ii = 0;
				  //
				  procShowInfo(pShowStruct);

				  }
				  break;
			default:
				break;
	
	}

errLabel:

	return 0;
}


LRESULT CDlgState::OnQyPostComm(WPARAM  wParam, LPARAM  lParam)
{
	return 0;
}


