// DlgFileTransfer.cpp : implementation file
//

#include "stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"


#include	"myresource.h"

#include	"qyMcMainWndProc.h"

#include	"qyMessenger_help.h"


#include "DlgFileTransfer.h"
#include "afxdialogex.h"

#include	"isCliHelpPublic.h"
#include	"qyMessengerHelpPublic.h"
#include	"dlgtalkproc.h"
#include	"funcsForIsCliHelp.h"
//
#include	<sys/stat.h> 
#include	<sys/types.h>
#include <fcntl.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <io.h>  
#include <stdio.h> 


//
int  viewDlgFileTransfer(  HWND  hParent  )
{
	CDlgFileTransfer  dlg(  CWnd::FromHandle(  hParent  )  );

	dlg.DoModal(  );

	return  0;
}


//
int  init_DFT_sendTasks(  int  maxCnt,  DFT_sendTasks  *  pTasks  )
{
	int  iErr  =  -1;

	if  (  !pTasks  )  return  -1;

	int  size;

	//
	pTasks->usMaxCnt  =  300;
	size  =  sizeof(  DFT_sendTask  )  *  pTasks->usMaxCnt;
	pTasks->pMems  =  (  DFT_sendTask  *  )malloc(  size  );
	if  (  !pTasks->pMems  )  goto  errLabel;
	memset(  pTasks->pMems,  0,  size  );

	iErr  =  0;
errLabel:
	return  iErr;
}

//
void  free_DFT_sendTasks(  DFT_sendTasks  *  pTasks  )
{
	if  (  !pTasks  )  return;
	MACRO_safeFree(  pTasks->pMems  );
	memset(  pTasks,  0,  sizeof(  pTasks[0]  )  );
	return;
}



// CDlgFileTransfer dialog

IMPLEMENT_DYNAMIC(CDlgFileTransfer, CDialogEx)

CDlgFileTransfer::CDlgFileTransfer(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgFileTransfer::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgFileTransfer::~CDlgFileTransfer()
{
	free_DFT_sendTasks(  &m_var.send.tasks  );
	free_DFT_sendTasks(  &m_var.sent.tasks  );
}


//
int	CDlgFileTransfer::sizeAllControls(    )
{
	int  iW_dlg,  iH_dlg;

	//
	{
	RECT  rc;
	GetClientRect(  &rc  );

	//
	iW_dlg  =  rc.right  -  rc.left;
	iH_dlg  =  rc.bottom  -  rc.top;
	}

	//
	int  iEdge_l  =  5;
	int  iEdge_t  =  5;
	int  iEdge_r  =  5;
	int  iEdge_b  =  10;

	//
	int  iSpace_x  =  10;
	int  iSpace_y  =  10;

	//
	int  iW_btn  =  50;
	int  iH_btn  =  30;

	int  iW_list  =  iW_dlg  -  iEdge_l  -  iEdge_r;
	int  iH_list  =  iH_dlg  -  iEdge_t  -  iEdge_b  -  iSpace_y  -  iH_btn;

	//
	HDWP			hDwp;
	int  idc;
	int  x,  y,  iW,  iH;
	unsigned  int  uFlags;
	HWND  hDlg  =  m_hWnd;


	//
	hDwp  =  M_BeginDeferWindowPos(  5  );
				   
	if  (  hDwp  )  {
					   int			iW,  iH;
					   	
					   //
		 			   idc  =  IDC_LIST_send;
		 			   x  =  iEdge_l;
		 			   y  =  iEdge_t;
		 			   iW  =  iW_list;
		 			   iH  =  iH_list;
		 			   uFlags  =  SWP_NOZORDER;
					   //
					   if  (  m_var.iType  ==  CONST_dftType_recv  )  uFlags  |=  SWP_HIDEWINDOW;
					   else  uFlags  |=  SWP_SHOWWINDOW;
					   //
		 			   M_DeferWindowPos(  hDwp,  ::GetDlgItem(  hDlg,  idc  ),  HWND_BOTTOM,  x,  y,  iW,  iH,  uFlags  );
		 
		 			   //  1
		 			   idc  =  IDC_RADIO_recv;
		 			   //  x 
					   y  +=  iH  +  iSpace_y;
		 			   iW  =  iW_btn;
		 			   iH  =  iH_btn;
		 			   //
		 			   uFlags  =  SWP_NOZORDER;
		 			   M_DeferWindowPos(  hDwp,  ::GetDlgItem(  hDlg,  idc  ),  HWND_BOTTOM,  x,  y,  iW,  iH,  uFlags  );
		 			   
					   //  2
		 			   idc  =  IDC_RADIO_sent;
					   x  +=  iW  +  iSpace_x;
		 			   //  y;
		 			   iW  =  iW_btn;
		 			   iH  =  iH_btn;
		 			   //
		 			   uFlags  =  SWP_NOZORDER;
		 			   M_DeferWindowPos(  hDwp,  ::GetDlgItem(  hDlg,  idc  ),  HWND_BOTTOM,  x,  y,  iW,  iH,  uFlags  );
		 			   
					   //  3
		 			   idc  =  IDC_RADIO_send;
					   x  +=  iW  +  iSpace_x;
		 			   //  y;
		 			   iW  =  iW_btn;
		 			   iH  =  iH_btn;
		 			   //
		 			   uFlags  =  SWP_NOZORDER;
		 			   M_DeferWindowPos(  hDwp,  ::GetDlgItem(  hDlg,  idc  ),  HWND_BOTTOM,  x,  y,  iW,  iH,  uFlags  );
		 			   
					   //  4
		 			   idc  =  IDCANCEL;
					   x  +=  iW  +  iSpace_x;
		 			   //  y;
		 			   iW  =  iW_btn;
		 			   iH  =  iH_btn;
		 			   //
		 			   uFlags  =  SWP_NOZORDER;
		 			   M_DeferWindowPos(  hDwp,  ::GetDlgItem(  hDlg,  idc  ),  HWND_BOTTOM,  x,  y,  iW,  iH,  uFlags  );
		 			   
					   
					   
					   //
		 			   M_EndDeferWindowPos(  hDwp  );	 
	
	}
	

	//
	switch  (  m_var.iType  )  {
			case  CONST_dftType_recv:  {
				  RECT  rc1;
				  ::GetWindowRect(  ::GetDlgItem(  m_hWnd,  IDC_LIST_send  ),  &rc1  );
				  //
				  ::MoveWindow(  m_var.recv.offlineRes.hTool_offlineRes,  rc1.left,  rc1.top,  rc1.right  -  rc1.left,  rc1.bottom  -  rc1.top,  TRUE  );
				  }
				  break;

			case  CONST_dftType_send:  {
				  RECT  rc1;
				  ::GetWindowRect(  ::GetDlgItem(  m_hWnd,  IDC_LIST_send  ),  &rc1  );
				  //
				  int  iW_list  =  rc1.right  -  rc1.left;
				  int  iH_list  =  rc1.bottom  -  rc1.top;
				  //
				  ::MoveWindow(  m_var.send.offlineRes.hTool_offlineRes,  rc1.left  +  iW_list  /  2,  rc1.top,  iW_list  /  2,  rc1.bottom  -  rc1.top,  TRUE  );
				  }
				  break;

			default:
					break;
	}



	return  0;
}


//
int  CDlgFileTransfer::closeTool_recv(  )
{
	if  (  IsWindow(  m_var.recv.offlineRes.hTool_offlineRes  )  )  {
		SendMessageTimeout(  m_var.recv.offlineRes.hTool_offlineRes,  WM_CLOSE,  0,  0,  0,  1000,  NULL  );
	}
	
	return  0;
}


//
int  CDlgFileTransfer::hideTool_send(  )
{
	if  (  IsWindow(  m_var.send.offlineRes.hTool_offlineRes  )  )  {
		::ShowWindow(  m_var.send.offlineRes.hTool_offlineRes,  SW_HIDE  );
	}

	return  0;
}

//
int  CDlgFileTransfer::displayTasks_func(  DFT_sendTasks  *  pTasks,  BOOL  bDecrement  )
{
	TCHAR  tBuf[1024];
	TCHAR  talkerDesc[128];
	TCHAR  displayDesc[128];

	int  idc  =  IDC_LIST_send;	
	::SendMessage(  ::GetDlgItem(  m_hWnd,  idc  ),  LB_RESETCONTENT,  (  WPARAM  )-1,  (  LPARAM  )0  );    
	
	int  i;
	for  (  i  =  0;  i  <  pTasks->usCnt;  i  ++  )  {
		 DFT_sendTask  *  pMem  =  &pTasks->pMems[i];
		 if  (  bDecrement  )  pMem  =  &pTasks->pMems[pTasks->usCnt  -  i  -  1];
		 //
		 getDescByIdInfo(  0,  &pMem->cfg.idInfo_dst,   talkerDesc,  mycountof(  talkerDesc  ),  0,  0  );  
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d %s( size %I64u )->%s. %s"  ),  i,  pMem->cfg.file_shortName,  pMem->cfg.ui64FileLen,  talkerDesc,  pMem->cfg.file_fullName  );
		 ::SendMessage(  ::GetDlgItem(  m_hWnd,  idc  ),  LB_INSERTSTRING,  -1,  (  LPARAM  )tBuf  );
	}

	return  0;
}


//
int  CDlgFileTransfer::displayTasks(  )
{
	switch  (  m_var.iType  )  {
			case  CONST_dftType_recv:
				  break;
			case  CONST_dftType_send:
				  displayTasks_func(  &m_var.send.tasks,  FALSE  );
				  break;
			case  CONST_dftType_sent:
				  displayTasks_func(  &m_var.sent.tasks,  TRUE  );
				  break;
			default:
					break;
	}

	return  0;

}

//
void CDlgFileTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgFileTransfer, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CDlgFileTransfer::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO_recv, &CDlgFileTransfer::OnBnClickedRadiorecv)
	ON_BN_CLICKED(IDC_RADIO_sent, &CDlgFileTransfer::OnBnClickedRadiosent)
	ON_BN_CLICKED(IDC_RADIO_send, &CDlgFileTransfer::OnBnClickedRadiosend)
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgFileTransfer message handlers




BOOL CDlgFileTransfer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	int  iErr  =  -1;
	int  size;
	
	//
	TCHAR  tBuf[256];
	QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//
	if  (  init_DFT_sendTasks(  300,  &m_var.send.tasks  )  )  goto  errLabel;
	if  (  init_DFT_sendTasks(  1000,  &m_var.sent.tasks  )  )  goto  errLabel;
	
	


	// TODO:  Add extra initialization here
	(  (  CButton  *  )GetDlgItem(  IDC_RADIO_recv  )  )->SetCheck(  TRUE  );
	//
	m_var.iType  =  CONST_dftType_recv;
	//
	PARAM_viewOfflineRes  param  =  {0};
	param.bNoBorder  =  TRUE;
	//
	viewDlgOfflineRes_me(  m_hWnd,  &m_var.recv.offlineRes,  &param  );

	//
	sizeAllControls(  );

	//
	SetTimer(  1,  1000,  NULL  );

	//
	iErr  =  0;

	//
errLabel:
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgFileTransfer::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CDlgFileTransfer::OnBnClickedRadiorecv()
{
	// TODO: Add your control notification handler code here
	int  ii  =  0;

	//
	hideTool_send(  );

	//
	m_var.iType  =  CONST_dftType_recv;

	//
	PARAM_viewOfflineRes  param  =  {0};
	param.bNoBorder  =  TRUE;
	
	//
	viewDlgOfflineRes_me(  m_hWnd,  &m_var.recv.offlineRes,  &param  );

	//
	sizeAllControls(  );
}


//
void CDlgFileTransfer::OnBnClickedRadiosent()
{
	// TODO: Add your control notification handler code here
	//
	closeTool_recv(  );
	hideTool_send(  );

	//
	m_var.iType  =  CONST_dftType_sent;
	//
	displayTasks(  );
	//
	sizeAllControls(  );
}


void CDlgFileTransfer::OnBnClickedRadiosend()
{
	// TODO: Add your control notification handler code here
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	int  ii  =  0;

	//
	closeTool_recv(  );
	//
	m_var.iType  =  CONST_dftType_send;
	
	//
	//CQyString		pathCStr;
	char		fileNameBuf[256  +  1]			=  "";
	
	//
	TCHAR	tFile[MAX_PATH]  =  _T(  ""  );
	{
		LPCTSTR							lpszDefExt  =	TEXT("*\0");		
		//LPCTSTR							lpszFilter	=	CONST_FILE_FILTER_TEXT;
		LPCTSTR							title		=	TEXT("Open File...\0");
		CQyString							pathCStr;
		DWORD								dwFlags     =	OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;
		
		if  (  qyBrowseForFile1(  m_hWnd,  TRUE,  lpszDefExt,  dwFlags,  CONST_FILE_FILTER_allFiles,  title,  NULL,  pQyMc,  tFile,  mycountof(  tFile  )  )  )  goto  errLabel;
		//safeTcsnCpy(  pathCStr,  bkFile,  mycountof(  bkFile  )  );
	}

	//
	struct _stat64 statBuf;
	if  (  _tstat64(  tFile,  &statBuf  )  )  goto  errLabel;
	unsigned  __int64  ui64FileLen  =  statBuf.st_size;


	//
	TMP_usrs  tmpUsrs;
	memset(  &tmpUsrs,  0,  sizeof(  tmpUsrs  )  );
	//
	selectMsgrsToSend(  &tmpUsrs  );

	//
	if  (  tmpUsrs.pMems  &&  tmpUsrs.usCnt  )  {
		int  i;
		for  (  i  =  0;  i  <  tmpUsrs.usCnt;  i  ++  )  {		
			 TMP_usr  *  pMem  =  &tmpUsrs.pMems[i];
			 //
#if  0
			 HWND  hTalk  =  NULL;
			 pFuncs->pf_talkToMessenger(  pMem->idInfo.ui64Id,  TRUE,  FALSE,  &hTalk  );
			 if  (  !IsWindow(  hTalk  )  )  continue;
			 //
			 HWND  hTool  =  NULL;
			 //
			 viewDlgOfflineRes_talk(  m_hWnd,  hTalk,  &hTool  );
			 //
			 m_var.send.offlineRes.hTool_offlineRes  =  hTool;
			 //
			 sizeAllControls(  );
#endif
			 //  ¼ÓÈëtasksÖÐ¡£
			 DFT_sendTasks  *  pTasks  =  &m_var.send.tasks;
			 if  (  pTasks->usCnt  <  pTasks->usMaxCnt  )  {
				 DFT_sendTask  *  pTask  =  &pTasks->pMems[pTasks->usCnt];
				 pTask->cfg.idInfo_dst.ui64Id  =  pMem->idInfo.ui64Id;
				 safeTcsnCpy(  tFile,  pTask->cfg.file_fullName,  mycountof(  pTask->cfg.file_fullName  )  );
				 //
				 TCHAR  *  pT  =  _tcsrchr(  tFile,  _T(  '\\'  )  );
				 if  (  pT  )  {
					 pT  ++  ;
					 safeTcsnCpy(  pT,  pTask->cfg.file_shortName,  mycountof(  pTask->cfg.file_shortName  )  );
				 }
				 //
				 pTask->cfg.ui64FileLen  =  ui64FileLen;
				 //
				 pTasks->usCnt  ++  ;
			 }

			 //
			 int  ii  =  3;
		}


	}


	//
	free_TMP_usrs(  &tmpUsrs  );
	

errLabel:

	//	
	displayTasks(  );  

	//
	sizeAllControls(  );

	return;
}








void CDlgFileTransfer::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	//
	RECT  rc;
	GetClientRect(  &rc  );

	// TODO: Add your message handler code here
	sizeAllControls(  );

	return;
}


void CDlgFileTransfer::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: Add your message handler code here
	sizeAllControls(  );
}



void CDlgFileTransfer::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return;
	//
	static  int  i  =  0;  i  ++  ;
	TCHAR  tBuf[128];
	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d\n"  ),  i  );
	//
	OutputDebugString(  tBuf  );

	//
	DFT_sendTasks  *  pTasks  =  &m_var.send.tasks;
	if  (  pTasks->usCnt  )  {
		//
		if  (  memcmp(  &pTasks->pMems[0].cfg,  &m_var.send.curTask.cfg,  sizeof(  DFT_sendTask_cfg  )  )  )  {
			if  (  IsWindow(  m_var.send.offlineRes.hTool_offlineRes  )  )  {
				SendMessageTimeout(  m_var.send.offlineRes.hTool_offlineRes,  WM_CLOSE,  0,  0,  0,  1000,  NULL  );
			}
			if  (  IsWindow(  m_var.send.offlineRes.hTool_offlineRes  )  )  {
				goto  errLabel;
			}
			//
			memset(  &m_var.send.curTask,  0,  sizeof(  m_var.send.curTask  )  );
			memcpy(  &m_var.send.curTask.cfg,  &pTasks->pMems[0].cfg,  sizeof(  DFT_sendTask_cfg  )  );
		}
		//
	}
	else  {
		  memset(  &m_var.send.curTask,  0,  sizeof(  m_var.send.curTask  )  );
	}

	//
	if  (  m_var.send.curTask.cfg.idInfo_dst.ui64Id  )  {
		//
			 HWND  hTalk  =  NULL;
			 if  (  findTalker(  pQyMc,  &m_var.send.curTask.cfg.idInfo_dst,  &hTalk  )  )  {
				 pFuncs->pf_talkToMessenger(  m_var.send.curTask.cfg.idInfo_dst.ui64Id,  0,  TRUE,  FALSE,  &hTalk  );
			 }
			 if  (  !IsWindow(  hTalk  )  )  goto  errLabel;
			 //
			 HWND  hTool  =  NULL;
			 //
			 BOOL  bNeedNotShowWnd  =  TRUE;
			 if  (  m_var.iType  ==  CONST_dftType_send  )  bNeedNotShowWnd  =  FALSE;
			 //
			 viewDlgOfflineRes_talk(  m_hWnd,  hTalk,  bNeedNotShowWnd,  FALSE,  &hTool  );
			 //
			 if  (  m_var.send.offlineRes.hTool_offlineRes  !=  hTool  )  {
				 SendMessageTimeout(  m_var.send.offlineRes.hTool_offlineRes,  WM_CLOSE,  0,  0,  0,  1000,  NULL  );
				 //
				 if  (  IsWindow(  m_var.send.offlineRes.hTool_offlineRes  )  )  goto  errLabel;
				 //
				 m_var.send.offlineRes.hTool_offlineRes  =  hTool;
				 //
				 dlgOfflineRes_upload(  m_hWnd,  hTool,  m_var.send.curTask.cfg.file_fullName  );
				 //
				 m_var.send.curTask.dwTickCnt_modified  =  GetTickCount(  );
			 }
			 //
			 getOfflineResTaskStatus(  m_var.send.offlineRes.hTool_offlineRes,  &m_var.send.curTask  );
			 //
			 int  nElapse  =  GetTickCount(  )  -  m_var.send.curTask.dwTickCnt_modified;
			 //
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "send.task iStatus %d, nElase %fs\n"  ),  m_var.send.curTask.iStatus,  nElapse  /  1000.  );
			 OutputDebugString(  tBuf  );
			 //showInfo_open0(  0,  0,  tBuf  );
	
			 //
#if  10
			 if  (  m_var.send.curTask.iStatus  ==  CONST_imTaskStatus_sendFinished  )  {
				 //  add to sent
				 if  (  m_var.sent.tasks.usCnt  <  m_var.sent.tasks.usMaxCnt  )  {
					 m_var.sent.tasks.pMems[m_var.sent.tasks.usCnt]  =  m_var.send.tasks.pMems[0];
					 m_var.sent.tasks.usCnt  ++  ;
				 }
				 //
				 if  (  m_var.send.tasks.usCnt  >  1  )  {
					 memcpy(  &m_var.send.tasks.pMems[0],  &m_var.send.tasks.pMems[1],  (  m_var.send.tasks.usCnt  -  1  )  *  sizeof(  DFT_sendTask  )  );
				 }
				 if  (  m_var.send.tasks.usCnt  >=  1  )  {
					 m_var.send.tasks.usCnt  --  ;					
				 }
				 //
				 this->displayTasks(  );
				 // 
				}
			 else  {
				   //
				   if  (  m_var.send.curTask.iStatus  ==  CONST_imTaskStatus_sending  )  {
					   //
					   if  (  m_var.iType  ==  CONST_dftType_send  )  {
						   if  (  m_var.send.tasks.usCnt  )  {
							   TCHAR  tBuf_status[128]  =  _T(  ""  );
							   M_getTransferFileStatus_str(  m_var.send.curTask.transferFileStatus,  tBuf_status,  mycountof(  tBuf_status  )  );  //  2015/08/06
							   //
							   DFT_sendTask  *  pMem  =  &m_var.send.tasks.pMems[0];
							   TCHAR  talkerDesc[128]  =  _T(  ""  );					   
							   getDescByIdInfo(  0,  &pMem->cfg.idInfo_dst,   talkerDesc,  mycountof(  talkerDesc  ),  0,  0  );  		 
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d %s %s( size %I64u )->%s. %s"  ),  0,  tBuf_status,  pMem->cfg.file_shortName,  pMem->cfg.ui64FileLen,  talkerDesc,  pMem->cfg.file_fullName  );
							   int  idc  =  IDC_LIST_send;
							   ::SendMessage(  ::GetDlgItem(  m_hWnd,  idc  ),  LB_INSERTSTRING,  0,  (  LPARAM  )tBuf  );
							   ::SendMessage(  ::GetDlgItem(  m_hWnd,  idc  ),  LB_DELETESTRING,  1,  (  LPARAM  )tBuf  );

						   }
					   }
				   }
				   //
				   nElapse  =  abs(  nElapse  );
				   if  (  nElapse  >  35000  )  {
					   
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "close tool to restart sending: send.task iStatus %d, nElase %fs\n"  ),  m_var.send.curTask.iStatus,  nElapse  /  1000.  );
					   showInfo_open0(  0,  0,  tBuf  );				
					   SendMessageTimeout(  m_var.send.offlineRes.hTool_offlineRes,  WM_CLOSE,  0,  0,  0,  1000,  NULL  );
				    }
			 }
#endif

			 //
			 sizeAllControls(  );
	}
	else  {
		  if  (  m_var.send.offlineRes.hTool_offlineRes  )  {
			  if  (  IsWindow(  m_var.send.offlineRes.hTool_offlineRes  )  )  {
			  	   SendMessageTimeout(  m_var.send.offlineRes.hTool_offlineRes,  WM_CLOSE,  0,  0,  0,  1000,  NULL  );
				}
			  else  {
				    m_var.send.offlineRes.hTool_offlineRes  =  0;
			  }
		  }
	}


errLabel:

	//
	CDialogEx::OnTimer(nIDEvent);
}
