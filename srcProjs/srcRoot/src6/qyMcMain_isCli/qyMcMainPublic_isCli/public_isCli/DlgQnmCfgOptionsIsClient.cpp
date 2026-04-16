// DlgQnmCfgOptionsIsClient.cpp : implementation file
//

#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

#ifdef  __WINCE__
		#ifndef  __TEST__
				 //  #include	<tpcshell.h> 
				 #include	"ceMenubar.h"
		#endif
#endif
#include	"DlgQnmCfgOptionsIsClient.h"
#include	"qyCusResTemp.h"

#include	"ctxQmc.h"



 INT_PTR CALLBACK dlgProc_qnmCfgOptionsIsClient(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
 void dlgQnmCfgOptionsIsClient_OnBnClickedMore(  HWND  hDlg  );

 //
  void  *  newQyWnd_CDlgQnmCfgOptionsIsClient(  )
 {
	 CQyWnd	*	pWnd	=	NULL;

	 int  iWndContentType  =  CONST_qyWndContentType_qnmCfgOptionsIsClient;    

#include	"unDeclareDebugNew.h"
	 pWnd  =  new  CDlgQnmCfgOptionsIsClient(  );
#include	"declareDebugNew.h"
	 
	 if  (  pWnd  )  pWnd->m_var.iWndContentType  =  iWndContentType;
	 	
	 return  pWnd;	 	 
 }


 //
extern  "C"  int getLogonServerCfg(  QY_MC  *  pQyMc,  QNM_CNT_CFG  *  pCntCfg,  int  index,  unsigned short  *  pSeqNo,  TCHAR  *  pCntName,  unsigned int cntNameSize   )
{
	if  (  !pQyMc  )  return  -1;
	//
	HKEY			hKeyRoot0				=	HKEY_CURRENT_USER;
	TCHAR			tQnmSchedulerBuf[256]	=	_T(  ""  );
	int				count					=	0;

	if  (  !pCntCfg  &&  !pSeqNo  &&  !pCntName  )  return  -1;

	//  cntIP, cntAddr[0], cntAddr[1], cntAddr[2],cntPort
	switch  (  index  )  {			
		case  0:	  {		  			  
			  getDynCfg_isClient(  pQyMc,  &pCntCfg[index]  );
			  //
			  _sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  )  );
			  }
			  break;
		case  1:
		case  2:
		case  3:
		default:
			    _sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s\\%d"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  index  );
				getQnmCntCfg(  0,  FALSE,  pQyMc->iServiceId,  hKeyRoot0,  tQnmSchedulerBuf,  &pCntCfg[index]  );
				if  (  !pCntCfg[index].usCntPort  )  pCntCfg[index].usCntPort  =  qnmCntPort(  pQyMc->iServiceId  );
				break;
	}
	
	if  (  pCntCfg[index].cntIp[0]  
		||  pCntCfg[index].cntAddrs[0][0]
		  ||  pCntCfg[index].cntAddrs[1][0]  )  {
			    //  seqNo
				pSeqNo[index]  =  index;
			    //  cntName
				TCHAR					tBuf[256]				=	_T(  ""  );
				qyGetRegCfg1W(  &pQyMc->env,  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_cntName  ),  tBuf,  mycountof(  tBuf  ),  0  );
				if  (  !tBuf[0]  )  {
					if  (  !index  )_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Default server"  )  );
					else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Server%d"  ),  index  );
					qySetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_cntName  ),  tBuf  );
				}
				memcpy(  pCntName,  tBuf,  cntNameSize  );
				//_tcsncpy(  &pCntName[index],  tBuf,  cntNameSize  );
				//
				count  ++;
			}
	else  {
		pSeqNo[index]  =  0;
		qyDelRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_cntName  )  );
	}

	return  count;
}





 CDlgQnmCfgOptionsIsClient::CDlgQnmCfgOptionsIsClient(  HWND  hParent /*=NULL*/)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.qyDlgType  =  CONST_qyDlgType_show;
}


int dlgQnmCfgOptionsIsClient_showServerCfg(  HWND  hDlg,  void  *  pVarParam,  int  iSeqNo  )
{
	if  (  !pVarParam  )  return  -1;
	DLG_qnmCfgOptionsIsClient_var	&	m_var	=	*(  DLG_qnmCfgOptionsIsClient_var  *  )pVarParam;
	TCHAR  tBuf[32]  =  _T(  ""  );

	//  cntAddr[0]
	m_var.guiData.pf_SetDlgItemText(  hDlg,  m_var.guiData.iIDC_cntIp,  CQyString(  m_var.cntCfg[iSeqNo].cntIp  )  );
	if  (  m_var.cntCfg[iSeqNo].ucbSys_cntIp  )  EnableWindow(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_cntIp  ),  FALSE  );
	//  cntAddr[1], cntAddr[2],cntPort
	m_var.guiData.pf_SetDlgItemText(  hDlg,  m_var.guiData.iIDC_EDIT_cntAddr1,  CQyString(  m_var.cntCfg[iSeqNo].cntAddrs[0]  )  );
	if  (  m_var.cntCfg[iSeqNo].ucbSys_cntAddrs[0]  )  EnableWindow(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_EDIT_cntAddr1  ),  FALSE  );
	m_var.guiData.pf_SetDlgItemText(  hDlg,  m_var.guiData.iIDC_EDIT_cntAddr2,  CQyString(  m_var.cntCfg[iSeqNo].cntAddrs[1]  )  );
	if  (  m_var.cntCfg[iSeqNo].ucbSys_cntAddrs[1]  )  EnableWindow(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_EDIT_cntAddr2  ),  FALSE  );

	//  cntName
	m_var.guiData.pf_SetDlgItemText(  hDlg,  m_var.guiData.iIDC_cntName,  m_var.cntName[iSeqNo]  );

	//  cntPort
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  m_var.cntCfg[iSeqNo].usCntPort  );
	m_var.guiData.pf_SetDlgItemText(  hDlg,  m_var.guiData.iIDC_cntPort,  tBuf  );
	if  (  m_var.cntCfg[iSeqNo].ucbSys_cntPort  )  EnableWindow(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_cntPort  ),  FALSE  );

	return 0;

}

int	dlgQnmCfgOptionsIsClient_listVideoConferencingServer(  HWND  hDlg,  void  *  pVarParam  )
{
	HKEY			hKeyRoot0				=	HKEY_CURRENT_USER;
	TCHAR			tBuf[256]				=	_T(  ""  );
	int				i = 0,j;

	if  (  !pVarParam  )  return  -1;
	DLG_qnmCfgOptionsIsClient_var	&	m_var	=	*(  DLG_qnmCfgOptionsIsClient_var  *  )pVarParam;

	//
	QY_MC		*	pQyMc					=	m_var.guiData.pQyMc;
	if  (  !pQyMc  )  return  -1;



#ifdef  __SUPPORT_MULTILOGON__

	if  (  !m_var.usItemCount  )  return 0;

	HWND  m_vcServerList  =  GetDlgItem(  hDlg,  IDC_LIST_vcServer  );
	
	ListView_DeleteAllItems(  m_vcServerList  );
	for  ( i = 0, j = 0; i < CONST_maxOfVideoConferencingServers; i ++  )  {
		 if  (  i && !m_var.seqNo[i]  )  continue;
		 if  (  j <= m_var.usItemCount  )  {
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  m_var.seqNo[i]  );
			  //  m_vcServerList.InsertItem(  j,  tBuf  );
			  LVITEM	lvItem;
			  memset(  &lvItem,  0,  sizeof(  lvItem  )  );
			  lvItem.mask  =  LVIF_TEXT;
			  lvItem.iItem  =  j;
			  lvItem.pszText  =  tBuf;
			  ListView_InsertItem(  m_vcServerList,  &lvItem  );
			  //
			  ListView_SetItemText(  m_vcServerList,  j,  1,  m_var.cntName[i]  );
			  ListView_SetItemText(  m_vcServerList,  j,  2,  myUtf82TChar(  m_var.cntCfg[i].cntIp,  tBuf,  mycountof(  tBuf  )  )  );
			  ListView_SetItemText(  m_vcServerList,  j,  3,  myUtf82TChar(  m_var.cntCfg[i].cntAddrs[0],  tBuf,  mycountof(  tBuf  )  )  );
			  ListView_SetItemText(  m_vcServerList,  j,  4,  myUtf82TChar(  m_var.cntCfg[i].cntAddrs[1],  tBuf,  mycountof(  tBuf  )  )  );
			  //
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  m_var.cntCfg[i].usCntPort  );
			  ListView_SetItemText(  m_vcServerList,  j,  5,  tBuf  );	
			  j ++;
		 }		 
	}
#endif
	return 0;
}

BOOL	dlgQnmCfgOptionsIsClient_bModifyItem(  HWND  hDlg,  void  *  pVarParam  )
{
	char		buf[8]		=	"";
	TCHAR		str[64];
	int			index;
	//
	if  (  !pVarParam  )  return  -1;
	DLG_qnmCfgOptionsIsClient_var	&	m_var	=	*(  DLG_qnmCfgOptionsIsClient_var  *  )pVarParam;
	
	QY_MC	*	pQyMc		=	m_var.guiData.pQyMc;
	if  (  !pQyMc  )  return  FALSE;


#ifdef  __SUPPORT_MULTILOGON__

	HWND m_vcServerList  =  GetDlgItem(  hDlg,  IDC_LIST_vcServer  );

	ListView_GetItemText(  m_vcServerList,  m_var.iItemSelected,  0,  str,  mycountof(  str  )  );
	myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	index  =  atoi(  buf  );

	DLG_guiData_qnmCfgOptionsIsClient	guiData;
	memset(  &guiData,  0,  sizeof(  guiData  )  );
	guiData.iParam_qyDlgType  =  m_var.qyDlgType;
	guiData.iItemSelected  =  index;
	guiData.rc.left  =  m_var.guiData.rc.left;
	guiData.rc.top  =  m_var.guiData.rc.top;
	guiData.rc.right  =  m_var.guiData.rc.left  +  m_var.guiData.rc.bottom  -  m_var.guiData.rc.top;
	guiData.rc.bottom  =  m_var.guiData.rc.bottom;

	showDlgQnmCfgOptionsIsClient(  pQyMc->g_hInst,  hDlg,  &guiData,  pQyMc  );

	//
	m_var.qyDlgType  =  CONST_qyDlgType_modify;

	if  (  getLogonServerCfg(  pQyMc,  m_var.cntCfg,  0,  m_var.seqNo,  m_var.cntName[0],  mycountof(  m_var.cntName[0]  )  )  >  0)  {
		m_var.usItemCount  = 1;
		dlgQnmCfgOptionsIsClient_showServerCfg(  hDlg,  &m_var,  0  );
	}

	for (  int serverIndex = 1;  serverIndex <  CONST_maxOfVideoConferencingServers; serverIndex ++  )  {
		if  (  getLogonServerCfg(  pQyMc,  m_var.cntCfg,  serverIndex,  m_var.seqNo,  m_var.cntName[serverIndex],  mycountof(  m_var.cntName[0]  )  )  >  0)  
			m_var.usItemCount  ++;
	}
	dlgQnmCfgOptionsIsClient_listVideoConferencingServer(  hDlg,  &m_var  );
	ListView_SetItemState(  m_vcServerList,  m_var.iItemSelected,  LVIS_SELECTED,  LVIS_SELECTED  );
#endif
	return TRUE;
}


__declspec(  dllexport  )  BOOL myDialogProc_qnmCfgOptionsIsClient(  void  *  pDlgParam,  HWND hDlg,  UINT uMsg,  WPARAM wParam,  LPARAM lParam  )
{
	CDlgQnmCfgOptionsIsClient	*	pDlg	=	(  CDlgQnmCfgOptionsIsClient  *  )pDlgParam;	//  GetWindowLong(  hDlg,  GWLP_USERDATA  );

	UNREFERENCED_PARAMETER(lParam);
	switch  (  uMsg  ) {
			#if  0
		   	case  WM_INITDIALOG:
				  pDlg  =  (  CDlgQnmCfgOptionsIsClient  *  )lParam;
				  //  pDlg->Attach(  hDlg  );
				  qyWnd_Attach(  pDlg,  hDlg  );
				  if  (  dlgQnmCfgOptionsIsClient_OnInitDialog(  hDlg,  qyWnd_getVar(  pDlg  )  )  )  {
					  EndDialog(  hDlg,  -1  );
				  }
				  return (INT_PTR)TRUE;
			#endif

			case WM_COMMAND:  {
				 WORD  wNotifyCode = HIWORD(wParam); 
    			 WORD  wID = LOWORD(wParam); 

				 if ( wID == IDCANCEL)
				 {
					 EndDialog(hDlg, LOWORD(wParam));
					 return (INT_PTR)TRUE;
				 }
				 if  (  wID == IDOK  )  {
					 dlgQnmCfgOptionsIsClient_OnOK(  hDlg  );
					 return  TRUE;
				 }
#ifdef  __SUPPORT_MULTILOGON__
				 if  (  wID  ==  IDC_ADD  ){
					 pDlg->OnBnClickedAdd(  );
					 return  TRUE;
				 }
				 if  (  wID  ==  IDC_DEL  ){
					 pDlg->OnBnClickedDel(  );
					 return  TRUE;
				 }
				 if  (  wID  ==  IDC_MODIFY  )  {
					 pDlg->OnBnClickedModify(  );
					 return  TRUE;
				 }
				 if  (  wID  ==  IDC_BUTTON_more  )  {
					 dlgQnmCfgOptionsIsClient_OnBnClickedMore(  hDlg  );
					 return  TRUE;
				 }
#endif
				 }
				 break;

			case  WM_NOTIFY:  {
				  WORD		wID = (  int  )wParam; 
				  LPNMHDR	pnmh  =  (  LPNMHDR  )lParam;
				  LRESULT	lResult	=	0;

				 //
				 if  (  pnmh->code  ==  NM_DBLCLK  ){
					 pDlg->OnNMDblclkListvcserver(  pnmh,  &lResult  );
					 return TRUE;
				 }
				 if  (  pnmh->code  ==  LVN_ITEMCHANGED   ){
					 pDlg->OnLvnItemchangedListvcserver(  pnmh,  &lResult  );
					 return  TRUE;
				 }
				 }
				 break;

			default:
					break;
	}

	return (INT_PTR)FALSE;
}

 __declspec(  dllexport  )  int dlgQnmCfgOptionsIsClient_OnInitDialog(  HWND  hDlg,  void  *  pVarParam  )
{
	int							iErr	=	-1;
	if  (  !pVarParam  )  return  -1;
	DLG_qnmCfgOptionsIsClient_var	&	m_var	=	*(  DLG_qnmCfgOptionsIsClient_var  *  )pVarParam;
	QY_MC					*	pQyMc	=	m_var.guiData.pQyMc;
	if  (  !pQyMc  )  return  -1;
	QY_SERVICEGUI_INFO		*	pSci	=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  goto  errLabel;
	MC_VAR_isCli				*	pProcInfo;
	int							count;
	char						buf[32]; buf[0] = 0;// = "";


	if  (  !(  pProcInfo  =	(  MC_VAR_isCli  *  )pSci->pVar  )  )  goto  errLabel;
	if  (  !m_var.guiData.pf_GetDlgItemText
		||  !m_var.guiData.pf_SetDlgItemText  )
	{
		traceLog((TCHAR*)  _T(  "DlgQnmCfgOptionsIsClient failed: pf_GetDlgItemText or pf_SetDlgItemText is null"  )  );
		goto  errLabel;
	}

#ifdef  IDD_qnmCfgOptions_isClient_ce
		cusDlgRes(  0,  &pQyMc->cusRes,  hDlg,  IDD_qnmCfgOptions_isClient_ce  );
#else
		cusDlgRes(  0,  &pQyMc->cusRes,  hDlg,  IDD_qnmCfgOptions_isClient  );
#endif
	
	
		//  2011/08/15  
		if  (  !pQyMc->bLogon  )  {
			TCHAR	tTitle[128]	=	_T(  ""  );
			char	verBuf[128]	=	"";
			BOOL		bDebug	=	FALSE;
			int			iVer	=	0;

			GetWindowText(  hDlg,  tTitle,  mycountof(  tTitle  )  );

			_sntprintf(  tTitle,  mycountof(  tTitle  ),  _T(  "%s (%s"  ),  tTitle,  pQyMc->cfg.qyMcTitle  );

			_snprintf(  verBuf,  sizeof(  verBuf  ),  "%s",  qnmVerStr(  pQyMc->iServiceId  )  );
			if  (  verBuf[0]  &&  verBuf[strlen(  verBuf  )  -  1]  ==  'd'  )  bDebug  =  TRUE;
			iVer  =  atol(  verBuf  );
			//  _sntprintf(  tTitle,  mycountof(  tTitle  ),  _T(  "%s V%d.%02d.%02d%s"  ),  tTitle,  iVer  /  10000,  (  iVer  /  100  )  %  100,  iVer  %  100,  bDebug  ?  _T(  "Debug"  )  :  _T(  ""  )  );
			_sntprintf(  tTitle,  mycountof(  tTitle  ),  _T(  "%s V%d.%02d.%02d.%02d%s"  ),  tTitle,  iVer  /  1000000,  (  iVer  /  10000  )  %  100,  (  iVer  /  100  )  %  100,  iVer  %  100,  bDebug  ?  _T(  "Debug"  )  :  _T(  ""  )  );

			_sntprintf(  tTitle,  mycountof(  tTitle  ),  _T(  "%s)"  ),  tTitle  );
			SetWindowText(  hDlg,  tTitle  );
		}

		//
#ifdef  __SUPPORT_MULTILOGON__

		HWND  m_vcServerList  =  GetDlgItem(  hDlg,  IDC_LIST_vcServer  );
#endif

	//
	if  (  m_var.guiData.iParam_qyDlgType  )  {
		m_var.qyDlgType  =  m_var.guiData.iParam_qyDlgType;

		if  (  m_var.guiData.iItemSelected  <  0  ||  m_var.guiData.iItemSelected  >=  CONST_maxOfVideoConferencingServers  )  goto  errLabel;
		m_var.iItemSelected  =  m_var.guiData.iItemSelected;

	}

	switch  (  m_var.qyDlgType  )  {
			case  CONST_qyDlgType_add:{
				  #ifdef  __SUPPORT_MULTILOGON__
						   ShowWindow(  m_vcServerList,  SW_HIDE  );
						   _snprintf(  buf,  sizeof(  buf  ),  "%d",  pQyMc->cfg.dynCfg.cnt.usCntPort  );
						   SetDlgItemText(  hDlg,  IDC_cntPort,  CQyString(  buf  )  );
						   //  EnableWindow(  GetDlgItem(  this->m_hWnd,  IDC_cntPort  ),  FALSE  );
						   //  GetDlgItem(  IDOK  )->MoveWindow(  75,  14,  75,  14,  TRUE  );
						   ShowWindow(  GetDlgItem(  hDlg,  IDC_ADD  ),  SW_HIDE  );
						   ShowWindow(  GetDlgItem(  hDlg,  IDC_MODIFY  ),  SW_HIDE  );
						   ShowWindow(  GetDlgItem(  hDlg,  IDC_DEL  ),  SW_HIDE  );
						   ShowWindow(  GetDlgItem(  hDlg,  IDC_STATIC_centerAddr  ),  SW_HIDE  );
						   MoveWindow(  hDlg,  m_var.guiData.rc.left,  m_var.guiData.rc.top,  430,  315,  TRUE  );
						   //
						   ShowWindow(  GetDlgItem(  hDlg,  IDC_BUTTON_more  ),  SW_HIDE  );
				  #endif
				  }
				  break;
			case  CONST_qyDlgType_modify:{
				  #ifdef  __SUPPORT_MULTILOGON__

						   getLogonServerCfg(  pQyMc,  m_var.cntCfg,  m_var.iItemSelected,  m_var.seqNo,  m_var.cntName[m_var.iItemSelected],  mycountof(  m_var.cntName[0]  )  );
					   
						   ShowWindow(  m_vcServerList,  SW_HIDE  );

						   _snprintf(  buf,  sizeof(  buf  ),  "%d",  pQyMc->cfg.dynCfg.cnt.usCntPort  );
						   SetDlgItemText(  hDlg,  IDC_cntPort,  CQyString(  buf  )  );
						   //  EnableWindow(  GetDlgItem(  hDlg,  IDC_cntPort  ),  FALSE  );
						   ShowWindow(  GetDlgItem(  hDlg,  IDC_ADD  ),  SW_HIDE  );
						   ShowWindow(  GetDlgItem(  hDlg,  IDC_MODIFY  ),  SW_HIDE  );
						   ShowWindow(  GetDlgItem(  hDlg,  IDC_DEL  ),  SW_HIDE  );
						   ShowWindow(  GetDlgItem(  hDlg,  IDC_STATIC_centerAddr  ),  SW_HIDE  );
						   MoveWindow(  hDlg,  m_var.guiData.rc.left,  m_var.guiData.rc.top,  430,  315,  TRUE  );
						   //
						   ShowWindow(  GetDlgItem(  hDlg,  IDC_BUTTON_more  ),  SW_HIDE  );
						   //
						   dlgQnmCfgOptionsIsClient_showServerCfg(  hDlg,  &m_var,  m_var.iItemSelected  );
				  #endif
				  }
				  break;		
		case  CONST_qyDlgType_show: 
		default:	
			    GetWindowRect(  hDlg,  &m_var.guiData.rc  );
			    if  (  getLogonServerCfg(  pQyMc,  m_var.cntCfg,  0,  m_var.seqNo,  m_var.cntName[0],  mycountof(  m_var.cntName[0]  )  )  >  0)  {
					m_var.usItemCount  = 1;
					dlgQnmCfgOptionsIsClient_showServerCfg(  hDlg,  &m_var,  0  );
				}
				#ifdef  __SUPPORT_MULTILOGON__
				        for (  int serverIndex = 1;  serverIndex <  CONST_maxOfVideoConferencingServers; serverIndex ++  )  {
 							if  (  getLogonServerCfg(  pQyMc,  m_var.cntCfg,  serverIndex,  m_var.seqNo,  m_var.cntName[serverIndex],  mycountof(  m_var.cntName[0]  )  )  >  0)  
								m_var.usItemCount  ++;
						}
						/*
						if  (  getLogonServerCfg(  m_var.cntCfg,  2,  m_var.seqNo,  m_var.cntName[2],  mycountof(  m_var.cntName[0]  )  )  >  0)
							m_var.usItemCount  ++;
						if  (  getLogonServerCfg(  m_var.cntCfg,  3,  m_var.seqNo,  m_var.cntName[3],  mycountof(  m_var.cntName[0]  )  )  >  0)
							m_var.usItemCount  ++;
						*/
				#endif

			    #ifdef  __SUPPORT_MULTILOGON__
						 ListView_SetExtendedListViewStyle(  m_vcServerList,  LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE  );
						 QY_COLUMNINFO  CONST_vcServerColumns[]  =
						 {
							 {	CONST_qyColumnDisplayType_str,	_T(  "No."  ),					SQL_WVARCHAR,	LVCFMT_LEFT,	30,		1,	},
							 {	CONST_qyColumnDisplayType_str,	_T(  "Server name"  ),			SQL_WVARCHAR,	LVCFMT_LEFT,	100,	1,	},
							 {	CONST_qyColumnDisplayType_str,  _T(  "Addr 0"  ),				SQL_WVARCHAR,	LVCFMT_LEFT,	120,	1,	},
							 {	CONST_qyColumnDisplayType_str,	_T(  "Addr 1"  ),				SQL_WVARCHAR,	LVCFMT_LEFT,	120,	1,	},
							 {	CONST_qyColumnDisplayType_str,	_T(  "Addr 2"  ),				SQL_WVARCHAR,	LVCFMT_LEFT,	120,	1,	},
							 {	CONST_qyColumnDisplayType_str,	_T(  "Port"	 ),					SQL_WVARCHAR,	LVCFMT_LEFT,	60,		1,	},
							 {	-1,								_T(  ""  ),						SQL_WVARCHAR,	LVCFMT_LEFT,	0,		1,	},
						 };
						 m_var.pColumn  =  CONST_vcServerColumns;
						 int i = 0;
						 LV_COLUMN  lvc;
						 lvc.mask  =  LVCF_SUBITEM | LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
						 for  (  ; m_var.pColumn[i].type  != -1;  i ++  )  {
							 lvc.iSubItem  =  i;
							 lvc.fmt  =  m_var.pColumn[i].fmt;
							 lvc.cx  =  m_var.pColumn[i].width;
							 lvc.pszText  =  m_var.pColumn[i].label;
							 ListView_InsertColumn(  m_vcServerList,  i,  &lvc  );  
						 }
						 m_var.usColumnCount  =  i;
						 //
						 // GetDlgItem(  IDCANCEL  )->ShowWindow(  SW_HIDE  );
						 //
						 dlgQnmCfgOptionsIsClient_listVideoConferencingServer(  hDlg,  &m_var  );
						 //
						 #ifndef  __WINCE__
								  SetDlgItemText(  hDlg,  m_var.guiData.iIDC_BUTTON_more,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_more  )  );
						 #endif

				#endif
			    break;
	
	}

#ifdef  __WINCE__
		ShowWindow(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_STATIC_centerAddr  ),  SW_HIDE  );

#ifndef  __TEST__
#if  0
		if  (  m_menuBar.bCreate(  this->m_hWnd,  IDR_MENU,  g_hInst  )  )  {		
			HideButton(  m_menuBar.getMenuBar(  ),  TRUE,  FALSE  );
			HideButton(  m_menuBar.getMenuBar(  ),  TRUE,  TRUE  );
			OverrideKey(  m_menuBar.getMenuBar(  )  );
		}
#endif
#endif
#endif

	//  2013/02/21
	m_var.ucbUseDb  =  bUseDb(  );
	
	HWND  hCtrl; hCtrl = GetDlgItem(hDlg, IDC_CHECK_useDb);
	SendMessage(  hCtrl,  BM_SETCHECK,  m_var.ucbUseDb  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );

	//  2015/06/23. 对isCli, 暂时不用数据库了
	//  2016/08/22
	BOOL  bDisable_useDb; bDisable_useDb = TRUE;

	//
	if  (  bDisable_useDb  )  {
		EnableWindow(  hCtrl,  FALSE  );
	}
			
	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		//  EndDialog(  this->m_hWnd,  -1  );
	}

	return iErr;
}

 int  sizeAllControls_dlgQnmCfgOptionsIsClient(  HWND  hDlg,  DLG_guiData_qnmCfgOptionsIsClient  *  p  );

 void dlgQnmCfgOptionsIsClient_OnBnClickedMore(  HWND  hDlg  )
 {
	CDlgQnmCfgOptionsIsClient	*	pDlg	=	(  CDlgQnmCfgOptionsIsClient  *  )CQyWnd::FromHandle(  hDlg  );
	DLG_qnmCfgOptionsIsClient_var  &  m_var  =  pDlg->m_var;
	HWND	m_hWnd  =  hDlg;
	RECT	rc;

	//
	QY_MC					*	pQyMc	=	m_var.guiData.pQyMc;
	if  (  !pQyMc  )  return;


	//
	GetWindowRect(  hDlg,  &rc  );

	 m_var.guiData.bMore  =  !m_var.guiData.bMore;
#ifdef  __APP_qyMc_touchscreen__

	    sizeAllControls_dlgQnmCfgOptionsIsClient(  hDlg,  (  DLG_guiData_qnmCfgOptionsIsClient  *  )qyWnd_getGuiData(  pDlg  )  );  
		if  (  m_var.guiData.bMore  )  {
			SetDlgItemText(  m_hWnd,  IDC_BUTTON_more,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hideMore  )  );
			}
		else  {
		      //  显示缩小窗口
			  SetDlgItemText(  m_hWnd,  IDC_BUTTON_more,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_more  )  );
		}

#else
	 if  (  m_var.guiData.bMore  )  {
		 //  显示放大窗口
		 MoveWindow(  hDlg,  rc.left,  rc.top,  m_var.guiData.w_org,  m_var.guiData.h_org,  TRUE  );
		 SetDlgItemText(  m_hWnd,  IDC_BUTTON_more,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hideMore  )  );
		 }
	 else  {
		   //  显示缩小窗口
		   MoveWindow(  hDlg,  rc.left,  rc.top,  430,  315,  TRUE  );
		   SetDlgItemText(  m_hWnd,  IDC_BUTTON_more,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_more  )  );
	 }
#endif

 }



 __declspec(  dllexport  )  void dlgQnmCfgOptionsIsClient_OnOK(  HWND  hDlg  )
{
	CDlgQnmCfgOptionsIsClient	*	pDlg	=	(  CDlgQnmCfgOptionsIsClient  *  )CQyWnd::FromHandle(  hDlg  );
	DLG_qnmCfgOptionsIsClient_var  &  m_var  =  pDlg->m_var;


	// TODO: Add your control notification handler code here
	QY_MC			*	pQyMc		=	m_var.guiData.pQyMc;
	if  (  !pQyMc  )  return;
	//
	char				buf[1024];
	TCHAR				str[256];
	unsigned short		usPort;
	int					index;
	char			*	pRegValName;
	int					idc;
	HKEY				hKeyRoot0	=	HKEY_CURRENT_USER;
	unsigned  char		ucbAsked	=	FALSE;
	unsigned  char		ucbFilled	=	FALSE;

	switch  (  m_var.qyDlgType  )  {
		case  CONST_qyDlgType_add:
		case  CONST_qyDlgType_modify:{
#ifdef  __SUPPORT_MULTILOGON__
			  TCHAR		tQnmSchedulerBuf[256]	=  _T(  ""  );
			  if  (  m_var.iItemSelected  )_sntprintf(  tQnmSchedulerBuf,  sizeof(  tQnmSchedulerBuf  ),  _T(  "%s\\%d"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  m_var.iItemSelected  );
			  else  _sntprintf(  tQnmSchedulerBuf,  sizeof(  tQnmSchedulerBuf  ),  _T(  "%s"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  )  );

			  pRegValName  =  CONST_regValName_cntIp;  idc  =  IDC_cntIp;
			  GetDlgItemText(  pDlg->m_hWnd,  idc,  str,  mycountof(  str  )  );
			  myTChar2Str(  str,  buf,  sizeof(  buf  )  );  trim(  buf  );
			  if  (  !m_var.cntCfg[m_var.iItemSelected].ucbSys_cntIp  )  {
				  if  (  buf[0]  &&  !bIpValid(  buf  )  )  {
					  myMessageBox(  pDlg->m_hWnd,  _T(  "Invalid IP address format,please fill in the default blank in IP address format"  ),  _T(  "www.qycx.com"  ),  MB_OK  );
					  SetFocus(  GetDlgItem(  pDlg->m_hWnd,  idc  )  );  return;
				  }
			  }
			  if  (  _stricmp(  m_var.cntCfg[m_var.iItemSelected].cntIp,  buf  )  )  {
				  if  (  !ucbAsked  &&  myMessageBox(  pDlg->m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  "www.qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  //
				  if  (  buf[0]  )  qySetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  CQyString(  pRegValName  ),  CQyString(  buf  )  );
				  else  qyDelRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  CQyString(  pRegValName  )  );
			  }

			  index  =  0;  pRegValName  =  CONST_regValName_cntAddr1;  idc  =  IDC_EDIT_cntAddr1;
			  GetDlgItemText(  pDlg->m_hWnd,  idc,  str,  mycountof(  str  )  );
			  myTChar2Str(  str,  buf,  sizeof(  buf  )  );  trim(  buf  );
			  if  (  _stricmp(  m_var.cntCfg[m_var.iItemSelected].cntAddrs[index],  buf  )  )  {
				  if  (  !ucbAsked  &&  myMessageBox(  pDlg->m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  "www.qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  //
				  if  (  buf[0]  )  qySetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  CQyString(  pRegValName  ),  CQyString(  buf  )  );			
				  else  qyDelRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  CQyString(  pRegValName  )  );
			  }

			  index  =  1;  pRegValName  =  CONST_regValName_cntAddr2;  idc  =  IDC_EDIT_cntAddr2;
			  GetDlgItemText(  pDlg->m_hWnd,  idc,  str,  mycountof(  str  )  );
			  myTChar2Str(  str,  buf,  sizeof(  buf  )  );  trim(  buf  );
			  if  (  _stricmp(  m_var.cntCfg[m_var.iItemSelected].cntAddrs[index],  buf  )  )  {
				  if  (  !ucbAsked  &&  myMessageBox(  pDlg->m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  "www.qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  //
				  if  (  buf[0]  )  qySetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  CQyString(  pRegValName  ),  CQyString(  buf  )  );			
				  else  qyDelRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  CQyString(  pRegValName  )  );
			  }

			  //  2010/09/24
			  pRegValName  =  CONST_regValName_cntPort;  idc  =  IDC_cntPort;
			  GetDlgItemText(  pDlg->m_hWnd,  idc,  str,  mycountof(  str  )  );
			  usPort  =  (  unsigned short  )_ttol(  str  );
			  if  (  !usPort  )  usPort  =  qnmCntPort(  pQyMc->iServiceId  );
			  if  (  m_var.cntCfg[m_var.iItemSelected].usCntPort  !=  usPort  )  {
				  m_var.cntCfg[m_var.iItemSelected].usCntPort  =  usPort;
				  qySetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  CQyString(  pRegValName  ),  str  );			
				  if  (  !ucbAsked  &&  myMessageBox(  pDlg->m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  "www.qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
			  }

			  pRegValName  =  CONST_regValName_cntName;  idc  =  IDC_cntName;
			  GetDlgItemText(  pDlg->m_hWnd,  idc,  str,  mycountof(  str  )  );
			  tTrim(  str  );
			  if  (  _tcsicmp(  m_var.cntName[m_var.iItemSelected],  str  )  )  {
				  if  (  !ucbAsked  &&  myMessageBox(  pDlg->m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  "www.qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  //
				  if  (  str[0]  )  qySetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  CQyString(  pRegValName  ),  str  );
				  else  qyDelRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  CQyString(  pRegValName  )  );
			  }
			  break;
#endif
		}
		case  CONST_qyDlgType_show:
		default:
				pRegValName  =  (char*)CONST_regValName_cntIp;  idc  =  m_var.guiData.iIDC_cntIp;
				m_var.guiData.pf_GetDlgItemText(  pDlg->m_hWnd,  idc,  str,  mycountof(  str  )  );
				myTChar2Str(  str,  buf,  sizeof(  buf  )  );  trim(  buf  );
				if  (  buf[0]  )  ucbFilled  =  TRUE;
				if  (  !m_var.cntCfg[0].ucbSys_cntIp  )  {
					if  (  buf[0]  &&  !bIpValid(  buf  )  )  {
						myMessageBox(  pDlg->m_hWnd,  _T(  "Invalid IP address format,please fill in the default blank in IP address format"  ),  _T(  "www.qycx.com"  ),  MB_OK  );
						SetFocus(  GetDlgItem(  pDlg->m_hWnd,  idc  )  );  return;
					}
				}

				if  (  _stricmp(  m_var.cntCfg[0].cntIp,  buf  )  )  {
					if  (  !ucbAsked  &&  myMessageBox(  pDlg->m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  "www.qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  return;
					ucbAsked  =  TRUE;
					//
					if  (  buf[0]  )  qySetRegCfgT(  hKeyRoot0,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  CQyString(  pRegValName  ),  CQyString(  buf  )  );			
					else  qyDelRegCfgT(  hKeyRoot0,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  CQyString(  pRegValName  )  );
				}

				index  =  0;  pRegValName  =  (char*)CONST_regValName_cntAddr1;  idc  =  m_var.guiData.iIDC_EDIT_cntAddr1;
				m_var.guiData.pf_GetDlgItemText(  pDlg->m_hWnd,  idc,  str,  mycountof(  str  )  );
				myTChar2Str(  str,  buf,  sizeof(  buf  )  );  trim(  buf  );
				if  (  buf[0]  )  ucbFilled  =  TRUE;
				if  (  _stricmp(  m_var.cntCfg[0].cntAddrs[index],  buf  )  )  {
					if  (  !ucbAsked  &&  myMessageBox(  pDlg->m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  "www.qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  return;
					ucbAsked  =  TRUE;
					//
					if  (  buf[0]  )  qySetRegCfgT(  hKeyRoot0,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  CQyString(  pRegValName  ),  CQyString(  buf  )  );			
					else  qyDelRegCfgT(  hKeyRoot0,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  CQyString(  pRegValName  )  );
				}

				//
				index  ++  ;  pRegValName  =  (char*)CONST_regValName_cntAddr2;  idc  =  m_var.guiData.iIDC_EDIT_cntAddr2;
				m_var.guiData.pf_GetDlgItemText(  pDlg->m_hWnd,  idc,  str,  mycountof(  str  )  );
				myTChar2Str(  str,  buf,  sizeof(  buf  )  );  trim(  buf  );
				if  (  buf[0]  )  ucbFilled  =  TRUE;
				if  (  _stricmp(  m_var.cntCfg[0].cntAddrs[index],  buf  )  )  {
					if  (  !ucbAsked  &&  myMessageBox(  pDlg->m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  "www.qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  return;
					ucbAsked  =  TRUE;
					//
					if  (  buf[0]  )  qySetRegCfgT(  hKeyRoot0,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  CQyString(  pRegValName  ),  CQyString(  buf  )  );			
					else  qyDelRegCfgT(  hKeyRoot0,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  CQyString(  pRegValName  )  );
				}

				//
				pRegValName  =  (char*)CONST_regValName_cntPort;  idc  =  m_var.guiData.iIDC_cntPort;
				m_var.guiData.pf_GetDlgItemText(  pDlg->m_hWnd,  idc,  str,  mycountof(  str  )  );
				usPort  =  (  unsigned short  )_ttol(  str  );
				if  (  !usPort  )  usPort  =  qnmCntPort(  pQyMc->iServiceId  );
				if  (  m_var.cntCfg[0].usCntPort  !=  usPort  )  {
					m_var.cntCfg[0].usCntPort  =  usPort;
					qySetRegCfgT(  hKeyRoot0,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  CQyString(  pRegValName  ),  str  );
					if  (  !ucbAsked  &&  myMessageBox(  pDlg->m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  "www.qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  return;
					ucbAsked  =  TRUE;
				}

				//////////////////



				/////////////////

				pRegValName  =  (char*)CONST_regValName_cntName;  idc  =  m_var.guiData.iIDC_cntName;
			  	m_var.guiData.pf_GetDlgItemText(  pDlg->m_hWnd,  idc,  str,  mycountof(  str  )  );
			  	tTrim(  str  );
			  	if  (  _tcsicmp(  m_var.cntName[m_var.iItemSelected],  str  )  )  {
					if  (  !ucbAsked  &&  myMessageBox(  pDlg->m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  "www.qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  return;
					ucbAsked  =  TRUE;
					//
					if  (  str[0]  )  qySetRegCfgT(  hKeyRoot0,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  CQyString(  pRegValName  ),  str  );
					else  qyDelRegCfgT(  hKeyRoot0,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  CQyString(  pRegValName  )  );
				}


				if  (  ucbAsked  )  {
					if  (  pQyMc->bLogon  )  qyShowHint1(  pDlg->m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hintToRestartProgram  )  );
					else  getDynCfg_isClient(  pQyMc,  &pQyMc->cfg.dynCfg.cnt  );
				}

				if  (  !ucbFilled  )  {
					myMessageBox(  pDlg->m_hWnd,  _T(  "please fill in the blank!"  ),  _T(  "www.qycx.com"  ),  MB_OK  );
					SetFocus(  GetDlgItem(  pDlg->m_hWnd,  m_var.guiData.iIDC_cntIp  )  );  return;
				}
				break;
		}

		//
		int  iBST_CHECKED;
		HWND  hCtrl;
		hCtrl  =  GetDlgItem(  pDlg->m_hWnd,  IDC_CHECK_useDb  );
		iBST_CHECKED  =  SendMessage(  hCtrl,  BM_GETSTATE,  0,  0  ); 
		unsigned  char  tmpucbUseDb  =  iBST_CHECKED  ==  BST_CHECKED;
		if  (  tmpucbUseDb  !=  m_var.ucbUseDb  )  {
			qySetRegCfgT(  hKeyRoot0,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  CQyString(  (char*)CONST_regValName_bNotUseDb  ),  tmpucbUseDb  ?  _T(  "0"  )  :  _T(  "1"  )  );
		}

		//  OnOK();  
		EndDialog(  pDlg->m_hWnd,  IDOK  );
}

 void CDlgQnmCfgOptionsIsClient::OnLvnItemchangedListvcserver(NMHDR *pNMHDR, LRESULT *pResult)
 {
	 LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	 // TODO: Add your control notification handler code here

#ifdef  __SUPPORT_MULTILOGON__

	 HWND  m_vcServerList  =  GetDlgItem(  this->m_hWnd,  IDC_LIST_vcServer  );

	 if  (  (  pNMLV->iItem  >= 0  )
		 &&	 (  pNMLV->uNewState  ==  (  LVIS_SELECTED | LVIS_FOCUSED  )  )  )  {
			 m_var.iItemSelected  =  pNMLV->iItem;
	 }
	 else  m_var.iItemSelected  =  -1;
	 SetFocus(  m_vcServerList  );

	 //  GetDlgItem(  IDC_MODIFY  )->EnableWindow(  m_var.iItemSelected  >=  0  );
	 //  GetDlgItem(  IDC_DEL  )->EnableWindow(  m_var.iItemSelected  >=  0  );
#endif
	 *pResult = 0;
 }

 void CDlgQnmCfgOptionsIsClient::OnNMDblclkListvcserver(NMHDR *pNMHDR, LRESULT *pResult)
 {
	 // LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	 // TODO: Add your control notification handler code here
	 if  (  m_var.iItemSelected  >=  0  )  {
		 m_var.qyDlgType  =  CONST_qyDlgType_modify;
		 dlgQnmCfgOptionsIsClient_bModifyItem(  this->m_hWnd,  &m_var  );
	 }
	 *pResult = 0;
 }

  void CDlgQnmCfgOptionsIsClient::OnBnClickedAdd()
 {
	 // TODO: Add your control notification handler code here
	 QY_MC	*	pQyMc			=		m_var.guiData.pQyMc;
	 if  (  !pQyMc  )  return;

	 TCHAR		tBuf[64]		=		_T(  ""  );
	 int		index;
#ifdef  __SUPPORT_MULTILOGON__
	 HWND		m_vcServerList  =		GetDlgItem(  this->m_hWnd,  IDC_LIST_vcServer  );

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s : %d"  ),  _T(  "The maximum Of Servers is"  ),  CONST_maxOfVideoConferencingServers  );
	 if  (  m_var.usItemCount  >=  CONST_maxOfVideoConferencingServers  )  { myMessageBox(  this->m_hWnd,  tBuf,  _T(  "Qycx"  ),  MB_OK  ); return; }
	 m_var.qyDlgType  =  CONST_qyDlgType_add;

	 for  (  index = 0; index < CONST_maxOfVideoConferencingServers;  index ++  )  {
		  if  (  !m_var.usItemCount  )  {
			  m_var.iItemSelected  =  index;
			  break;
		  }
		  if  (  index && !m_var.seqNo[index]  )  {
			  m_var.iItemSelected  =  index;
			  break;
		  }
	 }

	 //
	 DLG_guiData_qnmCfgOptionsIsClient	guiData;
	 memset(  &guiData,  0,  sizeof(  guiData  )  );
	 guiData.iParam_qyDlgType  =  m_var.qyDlgType;
	 guiData.iItemSelected  =  m_var.iItemSelected;
	 guiData.rc.left  =  m_var.guiData.rc.left;
	 guiData.rc.top  =  m_var.guiData.rc.top;
	 guiData.rc.right  =  m_var.guiData.rc.left  +  (  m_var.guiData.rc.bottom  -  m_var.guiData.rc.top  );
	 guiData.rc.bottom  =  m_var.guiData.rc.bottom;

	 showDlgQnmCfgOptionsIsClient(  pQyMc->g_hInst,  this->m_hWnd,  &guiData,  pQyMc  );

	 //
	 m_var.qyDlgType  =  CONST_qyDlgType_show;

	 if  (  getLogonServerCfg(  pQyMc,  m_var.cntCfg,  0,  m_var.seqNo,  m_var.cntName[0],  mycountof(  m_var.cntName[0]  )  )  >  0)  {
		 m_var.usItemCount  =  1;
		 dlgQnmCfgOptionsIsClient_showServerCfg(  this->m_hWnd,  &m_var,  0  );
	 }

	 for (  int serverIndex = 1;  serverIndex <  CONST_maxOfVideoConferencingServers; serverIndex ++  )  {
		 if  (  getLogonServerCfg(  pQyMc,  m_var.cntCfg,  serverIndex,  m_var.seqNo,  m_var.cntName[serverIndex],  mycountof(  m_var.cntName[0]  )  )  >  0)  
			 m_var.usItemCount  ++;
	 }

	 dlgQnmCfgOptionsIsClient_listVideoConferencingServer(  this->m_hWnd,  &m_var  );

	 ListView_SetItemState(  m_vcServerList,  m_var.iItemSelected,  LVIS_SELECTED,  LVIS_SELECTED  );
#endif

 }

 void CDlgQnmCfgOptionsIsClient::OnBnClickedModify()
 {
	 // TODO: Add your control notification handler code here
	 if  (  m_var.iItemSelected  <  0  )  return;

	 m_var.qyDlgType  =  CONST_qyDlgType_modify;
	 dlgQnmCfgOptionsIsClient_bModifyItem(  this->m_hWnd,  &m_var  );
 }

 void CDlgQnmCfgOptionsIsClient::OnBnClickedDel()
 {
	 // TODO: Add your control notification handler code here
	 QY_MC		*	pQyMc			=	m_var.guiData.pQyMc;
	 if  (  !pQyMc  )  return;

	 TCHAR			str[64];
	 char			buf[8]			=	"";
	 int			index;

#ifdef  __SUPPORT_MULTILOGON__
	 
	 HWND  m_vcServerList  =  GetDlgItem(  this->m_hWnd,  IDC_LIST_vcServer  );

	 if  (  m_var.iItemSelected  <  0  )  return;
	 if  (  !m_var.iItemSelected  )  {  myMessageBox(  this->m_hWnd,  _T(  "You cannot delete the default server item"  ),  _T(  "Qycx"  ),  MB_OK  ); return;  }
	 if  (  myMessageBox(  this->m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_reallyToDelete  ),  _T(  "www.qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  return;
	 ListView_GetItemText(  m_vcServerList,  m_var.iItemSelected,  0,  str,  mycountof(  str  )  );
	 myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	 index  =  atoi(  buf  );

	 HKEY			hKeyRoot0		=	HKEY_CURRENT_USER;
	 TCHAR		tQnmSchedulerBuf[256]	=  _T(  ""  ) ;
	 _sntprintf(  tQnmSchedulerBuf,  sizeof(  tQnmSchedulerBuf  ),  _T(  "%s\\%d"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  index  );

	 RegDeleteKey(  hKeyRoot0,  tQnmSchedulerBuf  );
	 m_var.seqNo[index]  = 0;


	 if  (  getLogonServerCfg(  pQyMc,  m_var.cntCfg,  0,  m_var.seqNo,  m_var.cntName[0],  mycountof(  m_var.cntName[0]  )  )  >  0)  {
		 m_var.usItemCount  =  1;
		 dlgQnmCfgOptionsIsClient_showServerCfg(  this->m_hWnd,  &m_var,  0  );
	 }

	 for (  int serverIndex = 1;  serverIndex <  CONST_maxOfVideoConferencingServers; serverIndex ++  )  {
		 if  (  getLogonServerCfg(  pQyMc,  m_var.cntCfg,  serverIndex,  m_var.seqNo,  m_var.cntName[serverIndex],  mycountof(  m_var.cntName[0]  )  )  >  0)  
			 m_var.usItemCount  ++;
	 }

	 m_var.iItemSelected  =  0;
	 dlgQnmCfgOptionsIsClient_listVideoConferencingServer(  this->m_hWnd,  &m_var  );
#endif
 }

