// DlgQnmEditPcUsrInfo.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qymc.h"
#include	"myresource.h"
#include	"DlgQnmEditPcUsrInfo.h"
#include	"qwmAllHints.h"
#include	"qyCusResTemp.h"
#include	"myDb.h"
#include	"isCliHelpPublic.h"

#include	"qmcCommFunc_iscli.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

__declspec(  dllexport  )  int  showDlgQnmEditPcUsrInfo(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  MSGR_ADDR  *  pAddr,  int  id,  unsigned  char  ucbInTab1,  unsigned  char  *  pucbChanged  )
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iRet	=	-1;

	CDlgQnmEditPcUsrInfo		dlg(  CWnd::FromHandle(  hParent  )  );

	//	
	if  (  !dlg.bSetDlgInfo(  pObjDb,  pAddr,  id,  ucbInTab1  )  )  goto  errLabel;
					   			
	//	
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
	
	iRet  =  IDOK;
	if  (  pucbChanged  )  *pucbChanged  =  dlg.m_var.ucbChanged;

errLabel:
	return  iRet;
}



 __declspec(  dllexport  )  int  showDlgQnmEditPcUsrInfo(  HWND  hParent,  
										QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  int  iObjType,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  char  ucbInTab1,
										unsigned  char  *  pucbChanged  )
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iRet	=	-1;

	CDlgQnmEditPcUsrInfo		dlg(  CWnd::FromHandle(  hParent  )  );

	//	
	if  (  !dlg.bSetDlgInfo(  pObjDb,  misServName,  iObjType,  pIdInfo,  ucbInTab1  )  )  goto  errLabel;
					   			
	//	
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
	
	iRet  =  IDOK;
	if  (  pucbChanged  )  *pucbChanged  =  dlg.m_var.ucbChanged;

errLabel:
	return  iRet;
}

 __declspec(  dllexport  )  int  showDlgQnmEditPcUsrInfo(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  int  iObjType,  char  *  mac,  unsigned  char  ucbInTab1,  unsigned  char  *  pucbChanged  )
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iRet	=	-1;

	CDlgQnmEditPcUsrInfo		dlg(  CWnd::FromHandle(  hParent  )  );

	//	
	if  (  !dlg.bSetDlgInfo(  pObjDb,  iObjType,  mac,  ucbInTab1  )  )  goto  errLabel;
					   			
	//	
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
	
	iRet  =  IDOK;
	if  (  pucbChanged  )  *pucbChanged  =  dlg.m_var.ucbChanged;

errLabel:
	return  iRet;
}


/////////////////////////////////////////////////////////////////////////////
// CDlgQnmEditPcUsrInfo dialog


CDlgQnmEditPcUsrInfo::CDlgQnmEditPcUsrInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmEditPcUsrInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmEditPcUsrInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	memset(  &m_var,  0,  sizeof(  m_var  )  );

}



void CDlgQnmEditPcUsrInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmEditPcUsrInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmEditPcUsrInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmEditPcUsrInfo)
	ON_CBN_SELCHANGE(IDC_COMBO0, OnSelchangeCombo0)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, OnSelchangeCombo4)
	//}}AFX_MSG_MAP
	ON_MESSAGE(  CONST_qyWm_comm,  OnQyComm  )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmEditPcUsrInfo message handlers

 BOOL  CDlgQnmEditPcUsrInfo::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  int  iObjType,  char  *  mac,  unsigned  char  ucbInTab1  )
{
	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	if  (  !mac  ||  !mac[0]  )  return  FALSE;

	m_var.pObjDb  =  pObjDb;
	m_var.iObjType  =  iObjType;

	safeStrnCpy(  mac,  m_var.u.pc.mac0,  sizeof(  m_var.u.pc.mac0  )  );

	m_var.ucbInTab1  =  ucbInTab1;
	return  TRUE;
}

 BOOL  CDlgQnmEditPcUsrInfo::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  int  iObjType,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  char  ucbInTab1  )
{
	BOOL	bRet	=	FALSE;

	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	if  (  !bMessengerIdValid(  pIdInfo  )  )  return  FALSE;
	
	if  (  iObjType  ==  CONST_objType_imGrp  )  goto  errLabel;
	
	m_var.pObjDb  =  pObjDb;
	m_var.iObjType  =  iObjType;

	lstrcpyn(  m_var.u.messenger.misServName,  misServName,  mycountof(  m_var.u.messenger.misServName  )  );
	m_var.u.messenger.addr.idInfo.ui64Id  =  pIdInfo->ui64Id;

	m_var.ucbInTab1  =  ucbInTab1;

	bRet  =  TRUE;
errLabel:
	return  bRet;

}


 BOOL  CDlgQnmEditPcUsrInfo::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  MSGR_ADDR  *  pAddr,  int  id,  unsigned  char  ucbInTab1  )
{
	BOOL	bRet	=	FALSE;

	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	if  (  !pAddr  )  return  FALSE;
	
	if  (  pAddr->uiObjType  ==  CONST_objType_imGrp  )  goto  errLabel;
	
	m_var.pObjDb  =  pObjDb;
	
	memcpy(  &m_var.u.messenger.addr,  pAddr,  sizeof(  MSGR_ADDR  )  );
	m_var.iObjType  =  pAddr->uiObjType;
	m_var.u.messenger.id  =  id;

	m_var.ucbInTab1  =  ucbInTab1;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}



 extern  "C"  BOOL  bSetDlgRegInfo_mis(  QNM_CUSRES_INFO  *  pCusRes,  QY_MESSENGER_REGINFO  *  pRegInfo,  HWND  hWnd,  BOOL  bEdit  )
{
	BOOL			bRet		=	FALSE;
	QY_IDCITEM	*	pItem		=	NULL;
	QY_IDCITEM	*	tmppItem	=	NULL;
	int				index;
	int				iCurSel;
	QY_IDCITEM  **  ppTables	=	NULL;


	for  (  pItem  =  gpTable0,  index  =  0;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->idcType  !=  CONST_qyIdcType_combo  &&  pItem->idcType  !=  CONST_qyIdcType_edit  )  continue;
		 if  (  pItem->flg  &  CONST_qyIdcFlgUnused  )  continue;
		 if  (  pItem->uiCommSeqNo  ==  -1  )  continue;		//  当传输顺序号为-1时，不作为注册信息传输到服务器上，2003/11/15							  
		 
		 MACRO_qyAssert(  pItem->uiCommSeqNo  <  CONST_qnmMaxRegFields,  _T(  "uiCommSeqNo < qnmMaxRegFields"  )  );
		 if  (  pItem->idcType  ==  CONST_qyIdcType_combo  )  {
			 iCurSel  =  SendMessage(  GetDlgItem(  hWnd,  pItem->idc  ),  CB_FINDSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  getResTable(  0,  pCusRes,  pItem->iResIdTable  ),  _ttol(  pRegInfo->u.cols[pItem->uiCommSeqNo]  )  )  );
			 if  (  iCurSel  !=  CB_ERR  )  {

			 	 SendMessage(  GetDlgItem(  hWnd,  pItem->idc  ),  CB_SETCURSEL,  iCurSel,  0  );
				 ppTables  =  getCbxTables(  pItem->idc  );				
				 procCbSelChange(  pCusRes,  gpTable0,  ppTables,  hWnd,  pItem->idc,  bEdit  );									 

			 }
			}
		 else  
			 SetDlgItemText(  hWnd,  pItem->idc,  (  TCHAR  *  )pRegInfo->u.cols[pItem->uiCommSeqNo]  );
		 
		 index  ++  ;
	}
	
	bRet  =  TRUE;

//  errLabel:
	return  bRet;
}

  extern  "C"  BOOL  bGetRegInfoFromDlg_mis(  QNM_CUSRES_INFO  *  pCusRes,  HWND  hWnd,  unsigned  char  ucbUtf8,  QY_MESSENGER_REGINFO  *  pRegInfo  )
{
	BOOL			bRet		=	FALSE;
	QY_IDCITEM	*	pItem		=  NULL;
	QY_IDCITEM	*	tmppItem	=  NULL;
	char			buf[1024];
	char			hint[1024];
	int				index;
	TCHAR			tBuf[2048];
	
	for  (  pItem  =  gpTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  !(  pItem->flg  &  CONST_qyIdcFlgChkNotNull  )  )  continue;
		 if  (  pItem->idcType  !=  CONST_qyIdcType_edit  &&  pItem->idcType  !=  CONST_qyIdcType_combo  )  continue;
		 GetDlgItemText(  hWnd,  pItem->idc,  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  )  );
		 myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );  trim(  buf  );
		 tmppItem  =  qyGetIdcItemByIdc(  gpTable0,  pItem->lIdc  );
		 MACRO_qyAssert(  tmppItem,  _T(  "tmppItem"  )  );
		 myTChar2Str(  tmppItem->des,  hint,  sizeof(  hint  )  );
		 myTChar2Str(  gAllHints.bt,  hint  +  strlen(  hint  ),  sizeof(  hint  )  -  strlen(  hint  )  );			 
		 //  MACRO_chkNotNull(  pItem->idc,  buf,  hint  );		//  被下面代码所替代	 
		 if  (  !buf[0]  )  {															
			 MessageBeep(  -1  );													
			 if  (  hint  &&  hint[0]  )  MessageBox(  NULL,  myStr2TChar1(  hint,  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  )  ),  _T(  "Qycx"  ),  MB_OK  );						
			 SetFocus(  GetDlgItem( hWnd,  pItem->idc )  );
			 goto  errLabel;
		 }								
	}								 	
		
	SendMessage(  GetDlgItem(  hWnd,  IDOK  ),  WM_ENABLE,  FALSE,  0  );
	
	pRegInfo->iCustomId  =  qyGetCustomId(  );
	memset(  &pRegInfo->u,  0,  sizeof(  pRegInfo->u  )  );		 
	for  (  pItem  =  gpTable0,  index  =  0;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->idcType  !=  CONST_qyIdcType_combo  &&  pItem->idcType  !=  CONST_qyIdcType_edit  )  continue;
		 if  (  pItem->flg  &  CONST_qyIdcFlgUnused  )  continue;
		 if  (  pItem->uiCommSeqNo  ==  -1  )  continue;		//  当传输顺序号为-1时，不作为注册信息传输到服务器上，2003/11/15
		 							  
		 /*
		 if  (  pItem->flg  &  CONST_qyIdcFlgNeeded  ||  !(  pItem->flg  &  CONST_qyIdcFlgHide  )  )  {
		 	 //  GetDlgItemText(  hWnd,  pItem->idc,  pRegInfo->u.cols[index],  min(  sizeof(  pRegInfo->u.cols[index]  ),  pItem->maxBytes  +  1  )  );		 
			 //  trim(  pRegInfo->u.cols[index]  );
			 MACRO_qyAssert(  pItem->uiCommSeqNo  <  CONST_qnmMaxRegFields,  "传输顺序号不能超过CONST_qnmMaxRegFields"  );
			 GetDlgItemText(  hWnd,  pItem->idc,  pRegInfo->u.cols[pItem->uiCommSeqNo],  min(  sizeof(  pRegInfo->u.cols[pItem->uiCommSeqNo]  ),  pItem->maxBytes  +  1  )  );		 
			 trim(  pRegInfo->u.cols[pItem->uiCommSeqNo]  );
			 if  (  pItem->idcType  ==  CONST_qyIdcType_combo  &&  pItem->pTable  )  {		//  2005/02/08将combo的数据由改为由类型来代表，为了使多语言能够使用
				 int	tmpiType  =  qyGetTypeByDes(  pItem->pTable,  pRegInfo->u.cols[pItem->uiCommSeqNo]  );
				 _snprintf(  pRegInfo->u.cols[pItem->uiCommSeqNo],  sizeof(  pRegInfo->u.cols[pItem->uiCommSeqNo]  ),  "%d",  tmpiType  );
			 }
			 pRegInfo->uiFieldIds[pItem->uiCommSeqNo]  =  pItem->uiFieldId;	//  2005/02/07
		 }
		 */  //  2005/09/24，为了将数据从char变为Unicode, 做以下修改 

		 if  (  pItem->flg  &  CONST_qyIdcFlgNeeded  ||  !(  pItem->flg  &  CONST_qyIdcFlgHide  )  )  {
			 MACRO_qyAssert(  pItem->uiCommSeqNo  <  CONST_qnmMaxRegFields,  _T(  "uiCommSeqNo <CONST_qnmMaxRegFields"  )  );
			 GetDlgItemText(  hWnd,  pItem->idc,  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  )  );  
			 //  MessageBox(  NULL,  tBuf,  _T(  ""  ),  MB_OK  );  //  为debug需要
			 if  (  ucbUtf8  )  {
				 myTChar2Utf8(  tBuf,  (  char  *  )pRegInfo->u.cols[pItem->uiCommSeqNo],  min(  sizeof(  pRegInfo->u.cols[pItem->uiCommSeqNo]  ),  pItem->maxBytes  +  1  )  );		 
				 trim(  (  char  *  )pRegInfo->u.cols[pItem->uiCommSeqNo]  );
				}
			 else  {
				   lstrcpyn(  (  TCHAR  *  )pRegInfo->u.cols[pItem->uiCommSeqNo],  tBuf,  min(  sizeof(  pRegInfo->u.cols[pItem->uiCommSeqNo]  ),  pItem->maxBytes  +  1  )  /  sizeof(  TCHAR  )  );		 
			 }
			 if  (  pItem->idcType  ==  CONST_qyIdcType_combo  &&  pItem->iResIdTable  )  {		//  2005/02/08将combo的数据由改为由类型来代表，为了使多语言能够使用
				 int	tmpiType;
				 if  (  ucbUtf8  )  {
					 safeStrnCpy(  (  char  *  )pRegInfo->u.cols[pItem->uiCommSeqNo],  buf,  sizeof(  buf  )  );
				 	 myUtf82Str(  buf,  sizeof(  buf  )  );
				 	 tmpiType  =  qyGetTypeByDes(  getResTable(  0,  pCusRes,  pItem->iResIdTable  ),  myStr2TChar(  buf,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  )  );
					}
				 else  {
					   tmpiType  =  qyGetTypeByDes(  getResTable(  0,  pCusRes,  pItem->iResIdTable  ),  tBuf  );
				 }
				 if  (  ucbUtf8  )  _snprintf(  (  char  *  )pRegInfo->u.cols[pItem->uiCommSeqNo],  sizeof(  pRegInfo->u.cols[pItem->uiCommSeqNo]  ),  "%d",  tmpiType  );
				 else  _sntprintf(  (  TCHAR  *  )pRegInfo->u.cols[pItem->uiCommSeqNo],  sizeof(  pRegInfo->u.cols[pItem->uiCommSeqNo]  )  /  sizeof(  TCHAR  ),  _T(  "%d"  ),  tmpiType  );
			 }
			 pRegInfo->uiFieldIds[pItem->uiCommSeqNo]  =  pItem->uiFieldId;	//  2005/02/07
		 }

		 index  ++  ;
	}
		
	bRet  =  TRUE;

errLabel:

	return  bRet;

}


 BOOL CDlgQnmEditPcUsrInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int						iErr			=	-1;
	QY_MC			*		pQyMc			=	QY_GET_GBUF(  );
	HWND					hWnd			=	this->m_hWnd;
	BOOL					bRet			=	FALSE;
	HWND					hChild			=	NULL;
	QY_IDCITEM		*		pCurTable		=	NULL;
	QY_IDCITEM		*		pItem			=	NULL;
	TCHAR					wndTitle[256]	=	DEFAULT_qwmRegToolWndTitle;
	TCHAR					tBuf[256];
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	/*
	*/
	setDlgIdcParams(  &m_var.layout  );
	setDlgIdcSize(  IDC_title,  IDC_hint0,  IDC_hint1,  IDC_PROGRESS_reg,  &pQyMc->cfg.custom,  &m_var.layout,  gpTable0  );
#if  0
	int  i  =  MulDiv(  m_var.layout.ulDlgHeight,  CONST_multiplierOfDlgUnit,  CONST_divisorOfDlgUnit  );
	//  ::MoveWindow(  this->m_hWnd,  100,  100,  482,  MulDiv(  m_var.layout.ulDlgHeight,  CONST_multiplierOfDlgUnit,  CONST_divisorOfDlgUnit  ),  0  );  
	::MoveWindow(  hWnd,  100,  100,  MulDiv(  m_var.layout.ulDlgWidth,  CONST_multiplierOfDlgUnit,  CONST_divisorOfDlgUnit  ),  MulDiv(  m_var.layout.ulDlgHeight,  CONST_multiplierOfDlgUnit,  CONST_divisorOfDlgUnit  ),  0  );  
#endif
			
	pCurTable  =  gpTable0;
	qnmSizeRegToolControls(  &pQyMc->cusRes,  this->m_hWnd,  gpTable0,  gpTable0,  TRUE  );

	for  (  pItem  =  gpTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
		if  (  pItem->idcType  ==  CONST_qyIdcType_edit  )  {
			hChild  =  ::GetDlgItem(  hWnd,  pItem->idc  );
			if  (  hChild  )  {
				//  gQyOldEditProc  =  SetWindowLong(  hChild,  GWL_WNDPROC,  (  LONG  )qyRestrictEditProc  );
				gQyOldEditProc  =  SetWindowLong(  hChild,  GWLP_WNDPROC,  (  LONG  )qyRestrictEditProc  );
				::SendMessage(  hChild,  EM_SETLIMITTEXT,  pItem->maxBytes,  0  );
			}
		}
	}

	MACRO_qyAssert(  qyCustomInfo.title[0],  _T(  "qyCustomInfo.title"  )  );

	if  (  qyCustomInfo.wndTitle  )  lstrcpyn(  wndTitle,  qyCustomInfo.wndTitle,  mycountof(  wndTitle  )  );
				   
	//  //  注意：由于需要用窗口题头来判断窗口实例的唯一性，故原有的题头不能=DEFAULT_wndTitle
	//  if  (  FindWindow(  NULL,  wndTitle  )  )  {
	//  	traceLogA(  "对话框已存在"  );  
	//  	::EndDialog(  hWnd,  -1  );
	//  	bRet  =  TRUE;  goto  errLabel;
	//  }
	::SetWindowText(  hWnd,  CString(  wndTitle  )  );
				   					  
	//  myStr2TChar(  qyCustomInfo.title,  tBuf,  mycountof(  tBuf  )  );
	lstrcpyn(  tBuf,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_pcRegistration  ),  mycountof(  tBuf  )  );	//  2006/04/22
	::SetDlgItemText(  hWnd,  IDC_title,  tBuf  );

	//  if  (  pQyMc->gui.hHt  )  ::SendMessage(  ::GetDlgItem(  hWnd,  IDC_title  ),  WM_SETFONT,  (  WPARAM  )pQyMc->gui.hHt,  (  LPARAM  )MAKELONG(  (  WORD  )TRUE,  0  )  );

	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  {
		traceLogA(  "CDlgQnmEditPcUsrInfo::OnInitDialog: pObjDb not available"  );  goto  errLabel;
	}

	switch  (  m_var.iObjType  )  {
		    case  CONST_objType_me:
			case  CONST_objType_admin:
			case  CONST_objType_messenger:
			case  CONST_objType_phoneMessenger:
				  if  (  (  !m_var.ucbInTab1  &&  g_dbFuncs.pf_bGetMessengerRegInfoBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  m_var.u.messenger.misServName,  &m_var.u.messenger.addr.idInfo,  0,  &m_var.u.messenger.regInfo  )  )
					  ||  (  m_var.ucbInTab1  &&  g_dbFuncs.pf_bGetMessengerRegInfoBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab1,  m_var.u.messenger.misServName,  &m_var.u.messenger.addr.idInfo,  0,  &m_var.u.messenger.regInfo  )  )  )
				  {
					  bSetDlgRegInfo_mis(  &pQyMc->cusRes,  &m_var.u.messenger.regInfo,  this->m_hWnd,  TRUE  );
				  }
				  break;
			case  CONST_objType_phoneGuest:
				  if  (  g_dbFuncs.pf_bGetImOtherRegInfoBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImOtherRegInfoTab,  &m_var.u.messenger.addr,  m_var.u.messenger.id,  &m_var.u.messenger.regInfo  )  )  {
					  bSetDlgRegInfo_mis(  &pQyMc->cusRes,  &m_var.u.messenger.regInfo,  this->m_hWnd,  TRUE  );
				  }				
				  //
				  for  (  pItem  =  gpTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
					   if  (  pItem->uiFieldId  ==  CONST_fieldId_jqlx  )  break;
				  }
				  if  (  pItem->idc  !=  -1  )  {
					  CWnd  *  pCtrl  =  NULL;
					  if  (  (  pCtrl  =  GetDlgItem(  pItem->lIdc  )  )  )  pCtrl->ShowWindow(  SW_HIDE  );
					  if  (  (  pCtrl  =  GetDlgItem(  pItem->idc  )  )  )  pCtrl->ShowWindow(  SW_HIDE  );
				  }
				  break;
			default:
				  if  (  (  !m_var.ucbInTab1  &&  g_dbFuncs.pf_bGetPcInfoByMacEx(  m_var.pObjDb->pDb,  m_var.u.pc.mac0,  TRUE,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  NULL,  &m_var.u.pc.regInfo,  NULL  )  )
					  ||  (  m_var.ucbInTab1  &&  g_dbFuncs.pf_bGetPcInfoByMacEx(  m_var.pObjDb->pDb,  m_var.u.pc.mac0,  TRUE,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  NULL,  NULL,  &m_var.u.pc.regInfo  )  )  )
				  {
					  bSetDlgRegInfo(  &pQyMc->cusRes,  &m_var.u.pc.regInfo,  this->m_hWnd,  gpTable0,  TRUE  );
				  }
				  break;
	}

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		EndDialog(  FALSE  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


 LRESULT CDlgQnmEditPcUsrInfo::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	 LONG				lRet		=	-1;
	 QY_WMBUF_COMM	*	pComm		=	(  QY_WMBUF_COMM  *  )lParam;

		 switch  (  pComm->uiType  )  {
	 		 case  CONST_qyWmParam_getIdcInfo:  {

				   QY_WMBUF_GETIDCINFO	*	pGetIdcInfo		=	(  QY_WMBUF_GETIDCINFO  *  )lParam;
				   QY_IDCITEM			*	pItem			=	gpTable0;
				 						   
				   for  (  pItem  =  gpTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
					    if  (  ::GetDlgItem(  this->m_hWnd,  pItem->idc  )  ==  pGetIdcInfo->hCtrl  )  break;
				   }
					   
				   if  (  pItem->idc  !=  -1  )  {
					   pGetIdcInfo->flg  =  pItem->flg;
					   lRet  =  CONST_qyWmRc_ok;
				   }				   			   

				   }

		default:
			goto errLabel;
	 }
	

	 lRet  =  QY_RC_WMOK;

errLabel:
	 
	 return  lRet;

}


 BOOL  bRegInfoCorrect(  void  *  pDb,  QNM_CUSTOM_COMM  *  pCustom,  QNM_REG_INFO  *  pRegInfo,  TCHAR  *  errBuf,  unsigned  int  size  )
{
	 BOOL		bRet  =  FALSE;
	 int		i,  j;
	 TCHAR		sqlBuf[1024];
	 int		zcbh0Index  =  getRegIndexByFieldId(  CONST_fieldId_zcbh0  );
	 int		zcbh1Index  =  getRegIndexByFieldId(  CONST_fieldId_zcbh1  );
	 int		zcbh2Index  =  getRegIndexByFieldId(  CONST_fieldId_zcbh2  );
	 BOOL		bRealZcbh	=	FALSE;

	 for  (  i  =  0;  i  <  sizeof(  pRegInfo->uiFieldIds  )  /  sizeof(  pRegInfo->uiFieldIds[0]  );  i  ++  )  {
		  if  (  bFieldLikeZcbh(  pRegInfo->uiFieldIds[i],  &bRealZcbh  )  &&  bRealZcbh  &&  (  (  TCHAR  *  )pRegInfo->u.cols[i]  )[0]  )  {
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(mac0) from qyPcRegInfoTab where qyPcRegInfoTab.mac0<>'%s' and (qyPcRegInfoTab.auditTime is not null and qyPcRegInfoTab.auditTime<>'') and (qyPcRegInfoTab.col%d='%s' or qyPcRegInfoTab.col%d='%s' or qyPcRegInfoTab.col%d='%s')"  ),  CString(  pRegInfo->mac0  ),  zcbh0Index,  (  TCHAR  *  )pRegInfo->u.cols[i],  zcbh1Index,  (  TCHAR  *  )pRegInfo->u.cols[i],  zcbh2Index,  (  TCHAR  *  )pRegInfo->u.cols[i]  );
			  if  (  bSqlObjExists(  pDb,  CString(  sqlBuf  )  )  )  {
				  _sntprintf(  errBuf,  size,  _T(  "the content of asset no. [ %s ] has already existed"  ),  (  TCHAR  *  )pRegInfo->u.cols[i]  ); 
				  goto  errLabel;
			  }
			  for  (  j  =  0;  j  <  sizeof(  pRegInfo->uiFieldIds  )  /  sizeof(  pRegInfo->uiFieldIds[0]  );  j  ++  )  {
				  if  (  bFieldLikeZcbh(  pRegInfo->uiFieldIds[j],  &bRealZcbh  )  &&  bRealZcbh  &&  i  !=  j  &&  !lstrcmpi(  (  TCHAR  *  )pRegInfo->u.cols[i],  (  TCHAR  *  )pRegInfo->u.cols[j]  )  )  {
					  _sntprintf(  errBuf,  size,  _T(  "the content of asset no. has already existed"  )  );  
					  goto  errLabel;
				  }
			  }
		  }
	 }
	 
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}

 BOOL  bRegInfoCorrect_mis(  void  *  pDb,  QNM_CUSTOM_COMM  *  pCustom,  QY_MESSENGER_REGINFO  *  pRegInfo,  TCHAR  *  errBuf,  unsigned  int  size  )
{
	 BOOL		bRet										=  FALSE;
	 int		i,  j;
	 TCHAR		sqlBuf[1024];
	 int		zcbh0Index									=  getRegIndexByFieldId(  CONST_fieldId_zcbh0  );
	 int		zcbh1Index									=  getRegIndexByFieldId(  CONST_fieldId_zcbh1  );
	 int		zcbh2Index									=  getRegIndexByFieldId(  CONST_fieldId_zcbh2  );
	 BOOL		bRealZcbh									=	FALSE;
	 char		idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";

	 for  (  i  =  0;  i  <  sizeof(  pRegInfo->uiFieldIds  )  /  sizeof(  pRegInfo->uiFieldIds[0]  );  i  ++  )  {
		  if  (  bFieldLikeZcbh(  pRegInfo->uiFieldIds[i],  &bRealZcbh  )  &&  bRealZcbh  &&  (  (  TCHAR  *  )pRegInfo->u.cols[i]  )[0]  )  {
			  if  (  !idInfo2Str(  &pRegInfo->addr.idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(idStr) from qyImObjRegInfoTab where qyImObjRegInfoTab.idStr<>'%s' and (qyImObjRegInfoTab.auditTime is not null and qyImObjRegInfoTab.auditTime<>'') and (qyImObjRegInfoTab.col%d='%s' or qyImObjRegInfoTab.col%d='%s' or qyImObjRegInfoTab.col%d='%s')"  ),  CString(  idStr  ),  zcbh0Index,  (  TCHAR  *  )pRegInfo->u.cols[i],  zcbh1Index,  (  TCHAR  *  )pRegInfo->u.cols[i],  zcbh2Index,  (  TCHAR  *  )pRegInfo->u.cols[i]  );
			  if  (  bSqlObjExists(  pDb,  CString(  sqlBuf  )  )  )  {
				  _sntprintf(  errBuf,  size,  _T(  "the content of asset no. [ %s ] has already existed"  ),  (  TCHAR  *  )pRegInfo->u.cols[i]  ); 
				  goto  errLabel;
			  }
			  for  (  j  =  0;  j  <  sizeof(  pRegInfo->uiFieldIds  )  /  sizeof(  pRegInfo->uiFieldIds[0]  );  j  ++  )  {
				  if  (  bFieldLikeZcbh(  pRegInfo->uiFieldIds[j],  &bRealZcbh  )  &&  bRealZcbh  &&  i  !=  j  &&  !lstrcmpi(  (  TCHAR  *  )pRegInfo->u.cols[i],  (  TCHAR  *  )pRegInfo->u.cols[j]  )  )  {
					  _sntprintf(  errBuf,  size,  _T(  "the content of asset no. has already existed"  )  );  
					  goto  errLabel;
				  }
			  }
		  }
	 }
	 
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}





 void CDlgQnmEditPcUsrInfo::OnOK() 
{
	 QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	TCHAR				errBuf[128]	=	_T(  ""  );

	 switch  (  m_var.iObjType  )  {
		 case  CONST_objType_me:
		 case  CONST_objType_admin:
		 case  CONST_objType_messenger:
		 case  CONST_objType_phoneMessenger:  {
			   QY_MESSENGER_REGINFO		regInfo;
			   //
			   memset(  &regInfo,  0,  sizeof(  regInfo  )  );
			   if  (  !bGetRegInfoFromDlg_mis(  &pQyMc->cusRes,  this->m_hWnd,  0,  &regInfo  )  )  return;
			   //
			   lstrcpyn(  m_var.u.messenger.misServName,  regInfo.addr.misServName,  mycountof(  m_var.u.messenger.misServName  )  );
			   regInfo.addr.idInfo.ui64Id  =  m_var.u.messenger.addr.idInfo.ui64Id;
			   //
			   errBuf[0]  =  0;
			   if  (  !bRegInfoCorrect_mis(  m_var.pObjDb->pDb,  &pQyMc->cfg.custom,  &regInfo,  errBuf,  mycountof(  errBuf  )  )  )  {
				   if  (  errBuf[0]  )  qyShowHint(  _T(  "Error: %s ,please retype again"  ),  CString(  errBuf  )  );  return;
			   }

			   if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {		//  在isClient系统里，这个临时表用来存储个人的信息。正式表都从管理端下载
				   if  (  memcmp(  &m_var.u.messenger.regInfo.u,  &regInfo.u,  sizeof(  m_var.u.messenger.regInfo.u  )  )  )  {
					   if  (  !qisRegUsrInfoInTab(  pDbFuncs,  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  NULL,  &regInfo,  CONST_tabName_qyImObjRegInfoTab1  )  )  {
						   MIS_CNT				*	pMisCnt		=	NULL;

						   pMisCnt  =  getMisCntByName(  pProcInfo,  m_var.u.messenger.misServName  );
						   //
						   if  (  pMisCnt  ) pMisCnt->ucTriesToReg  +=  5;
						   

						   m_var.ucbChanged  =  TRUE;
					   }
				   }
				   break;
			   }

			   if  (  m_var.ucbInTab1  ||  !bQyTimeValid(  m_var.u.messenger.regInfo.auditTime  )  ||  memcmp(  &m_var.u.messenger.regInfo.u,  &regInfo.u,  sizeof(  m_var.u.messenger.regInfo.u  )  )  )  {
				   getCurTime(  regInfo.auditTime  );
				   if  (  !g_dbFuncs.pf_qisRegUsrInfo(  pDbFuncs,  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  NULL,  &regInfo,  FALSE  )  )  {
					   m_var.ucbChanged  =  TRUE;
				   }
			   }

			   }
			   break;
		 case  CONST_objType_phoneGuest:{
			   QY_MESSENGER_REGINFO		regInfo;
			   //
			   memset(  &regInfo,  0,  sizeof(  regInfo  )  );
			   if  (  !bGetRegInfoFromDlg_mis(  &pQyMc->cusRes,  this->m_hWnd,  0,  &regInfo  )  )  return;
			   //
			   lstrcpyn(  m_var.u.messenger.misServName,  regInfo.addr.misServName,  mycountof(  m_var.u.messenger.misServName  )  );
			   memcpy(  &regInfo.addr,  &m_var.u.messenger.addr,  sizeof(  regInfo.addr  )  );
			   //
			   errBuf[0]  =  0;
			   if  (  !bRegInfoCorrect_mis(  m_var.pObjDb->pDb,  &pQyMc->cfg.custom,  &regInfo,  errBuf,  mycountof(  errBuf  )  )  )  {
				   if  (  errBuf[0]  )  qyShowHint(  _T(  "Error: %s ,please retype again"  ),  CString(  errBuf  )  );  return;
			   }

			   if  (  m_var.ucbInTab1  ||  !bQyTimeValid(  m_var.u.messenger.regInfo.auditTime  )  ||  memcmp(  &m_var.u.messenger.regInfo.u,  &regInfo.u,  sizeof(  m_var.u.messenger.regInfo.u  )  )  )  {
				   getCurTime(  regInfo.auditTime  );
				   if  (  !g_dbFuncs.pf_qisRegOtherInfoInTab(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  NULL,  &regInfo,  CONST_tabName_qyImOtherRegInfoTab  )  )  {
					   m_var.ucbChanged  =  TRUE;
				   }
			   }

			   }
			   break;
		 default:	{
				 	QNM_REG_INFO		tmpRegInfo;

					memset(  &tmpRegInfo,  0,  sizeof(  tmpRegInfo  )  );
					if  (  !bGetRegInfoFromDlg(  &pQyMc->cusRes,  this->m_hWnd,  gpTable0,  0,  &tmpRegInfo  )  )  return;
					//  这里将regInfo由utf8格式转换为普通的str
					//  
					safeStrnCpy(  m_var.u.pc.mac0,  tmpRegInfo.mac0,  sizeof(  tmpRegInfo.mac0  )  );
	 
					errBuf[0]  =  0;
					if  (  !bRegInfoCorrect(  m_var.pObjDb->pDb,  &pQyMc->cfg.custom,  &tmpRegInfo,  errBuf,  mycountof(  errBuf  )  )  )  {
						if  (  errBuf[0]  )  qyShowHint(  _T(  "Error: %s ,please retype again"  ),  CString(  errBuf  )  );  return;
					}

					if  (  m_var.ucbInTab1  ||  !bQyTimeValid(  m_var.u.pc.regInfo.auditTime  )  ||  memcmp(  &m_var.u.pc.regInfo.u,  &tmpRegInfo.u,  sizeof(  m_var.u.pc.regInfo.u  )  )  )  {
						getCurTime(  tmpRegInfo.auditTime  );
						if  (  !g_dbFuncs.pf_qnmRegUsrInfo(  pDbFuncs,  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  NULL,  &tmpRegInfo  )  )  {
							m_var.ucbChanged  =  TRUE;
						}
					}
					}
					break;
	 }


	CDialog::OnOK();
}




 void CDlgQnmEditPcUsrInfo::OnSelchangeCombo0() 
{
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	int				idc			=	IDC_COMBO0;
	QY_IDCITEM  **  ppTables	=	getCbxTables(  idc  );

	procCbSelChange(  &pQyMc->cusRes,  gpTable0,  ppTables,  this->m_hWnd,  idc,  TRUE );									 

}

 void CDlgQnmEditPcUsrInfo::OnSelchangeCombo1() 
{
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	int				idc			=	IDC_COMBO1;
	QY_IDCITEM  **  ppTables	=	getCbxTables(  idc  );

	procCbSelChange(  &pQyMc->cusRes,  gpTable0,  ppTables,  this->m_hWnd,  idc,  TRUE  );									 
	
}

 void CDlgQnmEditPcUsrInfo::OnSelchangeCombo2() 
{
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	int				idc			=	IDC_COMBO2;
	QY_IDCITEM  **  ppTables	=	getCbxTables(  idc  );

	procCbSelChange(  &pQyMc->cusRes,  gpTable0,  ppTables,  this->m_hWnd,  idc,  TRUE  );									 
	
}

 void CDlgQnmEditPcUsrInfo::OnSelchangeCombo3() 
{
 	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	int				idc			=	IDC_COMBO3;
	QY_IDCITEM  **  ppTables	=	getCbxTables(  idc  );

	procCbSelChange(  &pQyMc->cusRes,  gpTable0,  ppTables,  this->m_hWnd,  idc,  TRUE  );									 
	
}

 void CDlgQnmEditPcUsrInfo::OnSelchangeCombo4() 
{
 	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	int				idc			=	IDC_COMBO4;
	QY_IDCITEM  **  ppTables	=	getCbxTables(  idc  );

	procCbSelChange(  &pQyMc->cusRes,  gpTable0,  ppTables,  this->m_hWnd,  idc,  TRUE  );									 
	
}


