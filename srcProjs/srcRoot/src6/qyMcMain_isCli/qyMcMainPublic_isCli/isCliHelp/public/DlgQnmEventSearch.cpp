// DlgQnmEventSearch.cpp : implementation file
//
 
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyRestrictEdit.h"
//  #include	"qyMc.h"
#include	"myresource.h"
#include	"DlgQnmEventSearch.h"
#include	"qyCusResTemp.h"
#include ".\dlgqnmeventsearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




  void  qnmSizeSearchControls(  QNM_CUSRES_INFO  *  pCusRes,  HWND  hDlg,  	 QY_IDCITEM  *  pTable0,	QY_IDCITEM		*	pCurTable  )
{
	HDWP			hdwp; 
	HWND			hWnd,  prevhWnd		=  NULL;
	int				cnt					=	0;
	QY_IDCITEM	*	pItem				=	NULL;
	QY_IDCITEM  *	tmppItem			=	NULL;
	
	if  (  !pCurTable  )  return;

	for  (  pItem  =  pCurTable;  pItem->idc  !=  -1;  pItem  ++  )  {
		 cnt  ++  ;
	}
	// size the tree control accordingly
	hdwp  =  BeginDeferWindowPos(  cnt  ); 
	
	for  (  pItem  =  pCurTable;  pItem->idc  !=  -1;  pItem  ++  )  {

		 hWnd = ::GetDlgItem(  hDlg,  pItem->idc  );             
		 //  MACRO_qyAssert(  hWnd,  (  CString(  pItem->name  ?  pItem->name  :  "未命名控件"  )  +  " is not a controls"  ).GetBuffer(  0  )  );
		 if  (  !hWnd  )  continue;

		 if  (  pCurTable  !=  pTable0  )  {
		 	 tmppItem  =  qyGetIdcItemByIdc(  pTable0,  pItem->idc  );
		 	 if  (  tmppItem  )  tmppItem->flg  =  pItem->flg;
		 }
				 
		 ::DeferWindowPos(  hdwp, 
							hWnd,  prevhWnd  ?  prevhWnd  :  HWND_TOP, 
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->x  ),  
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->y  ),  
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->w  ),  
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->h  ),  
							(  pItem->flg  &  CONST_qyIdcFlgHide  )  ?  SWP_HIDEWINDOW  :  SWP_SHOWWINDOW  );  
		 prevhWnd  =  hWnd;

		 switch  (  pItem->idcType  )  {
				 case  CONST_qyIdcType_static:
		 			   if  (  pItem->des  )  SetWindowText(  hWnd,  CString(  pItem->des  )  );
					   break;
				 case  CONST_qyIdcType_combo:
			 	 case  CONST_qyIdcType_comboDesc:
					   if  (  pItem->iResIdTable  )  {
					   	   QY_DMITEM	*	pDm  =  NULL;
					   
						   SendMessage(  hWnd,  CB_RESETCONTENT,  0,  0  );
						   if  (  pItem->flg  &  CONST_qyIdcFlgAddNullItem  )  SendMessage(  hWnd,  CB_ADDSTRING,  0,  (  LPARAM  )_T(  ""  )  );
					   	   for  (  pDm  =  getResTable(  0,  (  QNM_CUSRES_INFO  *  )pCusRes,   pItem->iResIdTable  );  pDm->type  !=  -1;  pDm  ++  )  {
							    SendMessage(  hWnd,  CB_ADDSTRING,  0,  (  LPARAM  )pDm->des  );								    
					   	   }							   
						   //  if  (  pItem->des  &&  pItem->des[0]  )  SendMessage(  hWnd,  CB_SELECTSTRING,  -1,  (  LPARAM  )pItem->des  );
						   SendMessage(  hWnd,  CB_SETCURSEL,  0,  (  LPARAM  )0  );
				   	   }
				   	   break;
				 case  CONST_qyIdcType_chk:
					   if  (  pItem->des  )  SetWindowText(  hWnd,  CString(  pItem->des  )  );
					   SendMessage(  hWnd,  BM_SETCHECK,  pItem->maxBytes  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
					   break;
			 	 default:
						 break;

		 }
		 EnableWindow(  hWnd,  !(  pItem->flg  &  CONST_qyIdcFlgDisabled  )  );
	}
		
	EndDeferWindowPos(  hdwp  );

	return;

}



/////////////////////////////////////////////////////////////////////////////
// CDlgQnmEventSearch dialog


CDlgQnmEventSearch::CDlgQnmEventSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmEventSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmEventSearch)
	m_mac = _T("");
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQnmEventSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmEventSearch)
	DDX_Control(pDX, IDC_STARTTIME, m_startTimeCtrl);
	DDX_Control(pDX, IDC_ENDTIME, m_endTimeCtrl);
	DDX_Control(pDX, IDC_ENDDATE, m_endDateCtrl);
	DDX_Control(pDX, IDC_STARTDATE, m_startDateCtrl);
	DDX_Control(pDX, IDC_IP, m_ip);
	DDX_Text(pDX, IDC_EDIT_mac, m_mac);
	DDV_MaxChars(pDX, m_mac, 12);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmEventSearch, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmEventSearch)
	ON_CBN_SELCHANGE(IDC_COMBO0, OnSelchangeCombo0)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmEventSearch message handlers

 BOOL  CDlgQnmEventSearch::bSetDlgInfo(  MY_DB_BUF  *  pDbBufs,  int  iQueryType  )
{
	m_var.pDbBufs  =  pDbBufs;
	m_var.iQueryType  =  iQueryType;
	return  TRUE;
}


 BOOL CDlgQnmEventSearch::OnInitDialog() 
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	CDialog::OnInitDialog();

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  m_var.iQueryType  ==  CONST_qyQueryType_netDevEventList  )  {
		m_var.pEventListSearchTable0  =  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpNetDevEventListSearchTable0  );
		if  (  pQyMc->cfg.pGuiCfg  &&  pQyMc->pQnmEventTypeTable_netDev  )  {
			m_var.pEventTypeTable  =  pQyMc->pQnmEventTypeTable_netDev;
		}
		m_var.pEventListSearchCb0Tables  =  (  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpNetDevEventListSearchCb0Tables  );
		m_var.pEventListSearchCb1Tables  =  (  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpNetDevEventListSearchCb1Tables  );

		//  MoveWindow(  0,  0,  (  int  )(  92  *  1.55  ),  (  int  )(  229  *  1.64  ),  0  );		//  检查工具对话框。2003/11/12	

		}
	else  if  (  m_var.iQueryType  ==  CONST_qyQueryType_opEventList  )  {	//  2006/02/25
		      m_var.pEventListSearchTable0  =  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpOpEventListSearchTable0  );
			  if  (  pQyMc->cfg.pGuiCfg  &&  pQyMc->pQnmEventTypeTable_op  )  {
				  m_var.pEventTypeTable  =  pQyMc->pQnmEventTypeTable_op;
			  }
			  m_var.pEventListSearchCb0Tables  =  (  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpOpEventListSearchCb0Tables  );
			  m_var.pEventListSearchCb1Tables  =  (  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpOpEventListSearchCb1Tables  );
		}
	else  if  (  m_var.iQueryType  ==  CONST_qyQueryType_secChkEventList  )  {
		      m_var.pEventListSearchTable0  =  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  (  pQyMc->iSystemId  ==  CONST_qySystemId_secChk  )  ?  CONST_resId_gpSecChkEventListSearchTable0_secChk  :  CONST_resId_gpSecChkEventListSearchTable0_netMc2  );
			  m_var.pEventTypeTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_secChkEventTypeTable  );
			  m_var.pEventListSearchCb0Tables  =  (  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpSecChkEventListSearchCb0Tables  );
			  m_var.pEventListSearchCb1Tables  =  (  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpSecChkEventListSearchCb1Tables  );
		      
		}
	else  {
		  m_var.pEventListSearchTable0  =  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpEventListSearchTable0  );
		  if  (  pQyMc->cfg.pGuiCfg  &&  pQyMc->pQnmEventTypeTable_pc  )  {
			  m_var.pEventTypeTable  =  pQyMc->pQnmEventTypeTable_pc;
		  }
		  m_var.pEventListSearchCb0Tables  =  (  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpEventListSearchCb0Tables  );
		  m_var.pEventListSearchCb1Tables  =  (  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpEventListSearchCb1Tables  );
	}

	qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  m_var.pEventListSearchTable0,  m_var.pEventListSearchTable0  );

	QY_IDCITEM  *	pItem  =  NULL;
	int				cnt  =  0;

	for  (  pItem  =  m_var.pEventListSearchTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->idcType  ==  CONST_qyIdcType_edit  )  {
			 m_edits[cnt].setType(  CONST_qyEditType_custom,  pItem->flg,  NULL  );
			 m_edits[cnt].SubclassDlgItem(  pItem->idc,  this  );
			 GetDlgItem(  pItem->idc  )->SendMessage(  EM_SETLIMITTEXT,  pItem->maxBytes,  0  );
			 cnt  ++  ;
		 }
	}

	CTime	t  =  CTime::GetCurrentTime( );
	CTimeSpan	ts(  1,  0,  0,  0  );
	CTimeSpan	ts1(  0,  1,  0,  0  ); 
	CTime	tStart(  t  -  ts  ),  tEnd(  t  +  ts1  );

	this->m_startDateCtrl.SetTime(  &tStart  );
	this->m_startTimeCtrl.SetTime(  &tStart  );
	this->m_endDateCtrl.SetTime(  &tEnd  );
	this->m_endTimeCtrl.SetTime(  &tEnd  );

	UpdateData(  FALSE  );
	
	return  TRUE;  // return TRUE unless you set the focus to a control
	               // EXCEPTION: OCX Property Pages should return FALSE
}



 void CDlgQnmEventSearch::OnOK() 
{
	CComboBox	*	pEventTypeCb	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_eventType  );
	int				iEventType		=	-1;
	QY_IDCITEM	*	pItem			=	NULL;
	QY_IDCITEM	*	pTable0			=	m_var.pEventListSearchTable0;
	QY_DMITEM	*	pEventTable		=	NULL;
	QY_MC		*	pQyMc			=	QY_GET_GBUF(  );
	CString			str;
	int				i;

	if  (  !m_var.pDbBufs  )  return;

	UpdateData(  TRUE  );

	char	tStartBuf[256],  tEndBuf[256];
	
	if  (  qnmGetInputTime(  &this->m_startDateCtrl,  &this->m_startTimeCtrl,  &this->m_endDateCtrl,  &this->m_endTimeCtrl,  tStartBuf,  sizeof(  tStartBuf  ),  tEndBuf,  sizeof(  tEndBuf  )  )  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_timeErr  )  );  return;
	}

	for  (  i  =  0;  ;  i  ++  )  {
		 if  (  m_var.pDbBufs[i].iDbType  ==  -1  )  break;
		 m_var.wherePart[0]  =  0;
		 if  (  getWherePart(  m_var.pDbBufs[i].iDbType  )  )  continue;
		 lstrcpyn(  m_var.pDbBufs[i].tBuf,  m_var.wherePart,  mycountof(  m_var.pDbBufs[i].tBuf  )  );
	}

	CDialog::OnOK();


}

 int  CDlgQnmEventSearch::getWherePart(  int  iDbType  ) 
{
	int				iErr			=	-1;
	CComboBox	*	pEventTypeCb	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_eventType  );
	int				nCurSel;
	char			buf[1024];
	int				iEventType		=	-1;
	QY_IDCITEM	*	pItem			=	NULL;
	QY_IDCITEM	*	pTable0			=	m_var.pEventListSearchTable0;
	QY_DMITEM	*	pEventTable		=	NULL;
	QY_MC		*	pQyMc			=	QY_GET_GBUF(  );
	TCHAR			tBuf[1024];
	CString			str;


	pItem  =  qyGetIdcItemByIdc(  m_var.pEventListSearchTable0,  IDC_COMBO_eventType  );
	//MACRO_qyAssert(  pItem,  _T(  "事件列表应加上"  )  );
	pEventTable  =  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  );	//  >pTable;
	//MACRO_qyAssert(  pEventTable,  _T(  "事件列表不对"  )  );

	nCurSel  =  pEventTypeCb->GetCurSel(  );
	if  (  nCurSel  !=  CB_ERR  )  {
		pEventTypeCb->GetLBText(  nCurSel,  tBuf  );  myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
		qyTrim(  buf  );
		if  (  buf[0]  )  {
			if  (  (  iEventType  =  qyGetTypeByDes(  pEventTable,  CString(  buf  )  )  )  !=  -1  )  {
				_sntprintf(  m_var.eventTypeName,  mycountof(  m_var.eventTypeName  ),  _T(  "%s"  ),  CString(  buf  )  );
				if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s and "  ),  m_var.wherePart  );
				_sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s eventType=%d"  ),  m_var.wherePart,  iEventType  );
			}
		}
	}

	//  这里加入了对系统使用事件的限制
	if  (  iEventType  ==  -1  )  {	
		 QY_DMITEM	*	pItem				=	NULL;
	 	 
		 if  (  m_var.pEventTypeTable  )  {
			 pItem  =  m_var.pEventTypeTable;
			 if  (  pItem->type  !=  -1  )  {
				 _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "eventType in (%d"  ),  pItem->type  );
				 pItem  ++  ;
			 	 for  (  ;  pItem->type  !=  -1;  pItem  ++  )  {
		 			  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s,%d"  ),  m_var.wherePart,  pItem->type  );
	 		 	 }
			 	 _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s)"  ),  m_var.wherePart  );
		 	 }
	 	 }	 
	}


	m_var.iEventType  =  iEventType;

	for  (  pItem  =  pTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->idcType  !=  CONST_qyIdcType_combo  
			 &&  pItem->idcType  !=  CONST_qyIdcType_edit  
				&&  pItem->idcType  !=  CONST_qyIdcType_ip  )  continue;
		 if  (  pItem->flg  &  CONST_qyIdcFlgUnused  )  continue;
		 if  (  pItem->flg  &  CONST_qyIdcFlgHide  )  continue;
		 if  (  !pItem->sqlColName  ||  !pItem->sqlColName[0]  )  continue;
		 if  (  pItem->idcType  ==  CONST_qyIdcType_ip  )  {
			 DWORD					dwIp;
			 struct  in_addr		tmpInAddr;

			 if  (  4  ==  ::SendMessage(  GetDlgItem(  pItem->idc  )->m_hWnd,  IPM_GETADDRESS,  0,  (  LPARAM  )&dwIp  )  )  {
				 tmpInAddr.s_addr  =  qyhtonl(  dwIp  );
				 sprintf(  buf,  inet_ntoa(  tmpInAddr  )  );
				 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s and "  ),  m_var.wherePart  );
				 _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s='%s'"  ),  m_var.wherePart,  pItem->sqlColName,  CString(  buf  )  );
			 }
			}
		 else  if  (  pItem->idcType  ==  CONST_qyIdcType_edit  ||  pItem->idcType  ==  CONST_qyIdcType_combo  )  {
				GetDlgItemText(  pItem->idc,  tBuf,  mycountof(   tBuf  )  );  tTrim(  tBuf  );  
				if  (  !tBuf[0]  )  continue;
                //  if  (  !_tcsnicmp(  pItem->name,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_likeSearch  )/*_T(  "模糊查询"  )*/,  lstrlen(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_likeSearch  )/*_T(  "模糊查询"  )*/  )  )  )  		//  added by 2004/10/16
				if  (  pItem->flg  &  CONST_qyIdcFlgSearchUsingLike  )  {	//  2006/05/03, 增加了这个标志位以方便模糊查询
					if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s  and  "  ),  m_var.wherePart  );
					_sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s  like %s"  ),  m_var.wherePart,  pItem->sqlColName,  getDbValStr(  iDbType,  pItem->uiCommSeqNo,  CString(  "%"  )  +  tBuf  +  _T(  "%"  )  )  );
					traceLogA(  "wherePart is [%S]",  m_var.wherePart  );
					}
                else  {
					  if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s and "  ),  m_var.wherePart  );
					  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s=%s"  ),  m_var.wherePart,  pItem->sqlColName,  getDbValStr(  iDbType,  pItem->uiCommSeqNo,  tBuf  )  );
				}				
		 }
		 		 
	}
	
	char	tStartBuf[256],  tEndBuf[256];
	
	if  (  qnmGetInputTime(  &this->m_startDateCtrl,  &this->m_startTimeCtrl,  &this->m_endDateCtrl,  &this->m_endTimeCtrl,  tStartBuf,  sizeof(  tStartBuf  ),  tEndBuf,  sizeof(  tEndBuf  )  )  )  {
		traceLogA(  (  " startTime must be <= endTime"  )  );  
		goto  errLabel;
	}

	if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s and "  ),  m_var.wherePart  );
	_sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s cntEventTime>'%s' and cntEventTime<'%s'"  ),  m_var.wherePart,  CString(  tStartBuf  ),  CString(  tEndBuf  )  );
	
	traceLogA(  "wherePart is [%s]",  m_var.wherePart  );
	iErr  =  0;
errLabel:
	return  iErr;
	
}

void CDlgQnmEventSearch::OnSelchangeCombo0() 
{
	 QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	 int				iCurSel		=	-1;
	 QY_IDCITEM		*	pTable0		=	m_var.pEventListSearchTable0;
	 QY_IDCITEM		**	pTables		=	m_var.pEventListSearchCb0Tables;
	 int				nTables		=	getnTables(  pTables  );
	 QY_IDCITEM		*	pCurTable	=	NULL;
	 
	 if  (  (  iCurSel  =  GetDlgItem(  IDC_COMBO0  )->SendMessage(  CB_GETCURSEL,  0,  0  )  )  ==  CB_ERR  )  return;
	 if  (  iCurSel  >=  nTables  )  return;
	 pCurTable  =  pTables[iCurSel];
	 if  (  !pCurTable  )  return;
	
	 qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  pTable0,  pCurTable  );
	
}

void CDlgQnmEventSearch::OnSelchangeCombo1() 
{	
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	int					iCurSel		=	-1;
	QY_IDCITEM		*	pTable0		=	m_var.pEventListSearchTable0;
	QY_IDCITEM		**	pTables		=	m_var.pEventListSearchCb1Tables;
	int					nTables		=	getnTables(  pTables  );
	QY_IDCITEM		*	pCurTable	=	NULL;
	 
	if  (  (  iCurSel  =  GetDlgItem(  IDC_COMBO1  )->SendMessage(  CB_GETCURSEL,  0,  0  )  )  ==  CB_ERR  )  return;
	if  (  iCurSel  >=  nTables  )  return;
	pCurTable  =  pTables[iCurSel];
	if  (  !pCurTable  )  return;

	qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  pTable0,  pCurTable  );
	
}

void CDlgQnmEventSearch::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
