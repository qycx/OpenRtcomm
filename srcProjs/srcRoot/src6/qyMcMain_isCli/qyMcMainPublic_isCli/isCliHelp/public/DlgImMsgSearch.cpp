// DlgImMsgSearch.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qymc.h"
#include	"myresource.h"
#include	"DlgImMsgSearch.h"
#include ".\dlgimmsgsearch.h"
//
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

__declspec(  dllexport  )  int  showDlgImMsgSearch(  HWND  hParent,  MY_DB_BUF  *  pDbBufs,  int  iQueryType  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int  iRet  =  -1;
	
	CDlgImMsgSearch		dlg(  CWnd::FromHandle(  hParent  )  );
	if  (  !dlg.bSetDlgInfo(  pDbBufs,  iQueryType  )  )  goto  errLabel;
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
	iRet  =  IDOK;

errLabel:
	return  iRet;

}
/////////////////////////////////////////////////////////////////////////////
// CDlgImMsgSearch dialog


CDlgImMsgSearch::CDlgImMsgSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImMsgSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgImMsgSearch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgImMsgSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgImMsgSearch)
	DDX_Control(pDX, IDC_STARTTIME, m_startTimeCtrl);
	DDX_Control(pDX, IDC_STARTDATE, m_startDateCtrl);
	DDX_Control(pDX, IDC_ENDTIME, m_endTimeCtrl);
	DDX_Control(pDX, IDC_ENDDATE, m_endDateCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgImMsgSearch, CDialog)
	//{{AFX_MSG_MAP(CDlgImMsgSearch)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgImMsgSearch message handlers

 BOOL  CDlgImMsgSearch::bSetDlgInfo(  MY_DB_BUF  *  pDbBufs,  int  iQueryType  )
{
	m_var.pDbBufs  =  pDbBufs;
	m_var.iQueryType  =  iQueryType;
	return  TRUE;
}




 int CDlgImMsgSearch::getWherePart(  int  iDbType  ) 
{
	int						iErr										=		-1;
	CString					str;
	QY_MC				*	pQyMc										=		QY_GET_GBUF(  );
	int						iDataType									=		SQL_WVARCHAR;
	char					buf[255  +  1]								=		"";
	TCHAR					talkerDesc[255  +  1]						=		_T(  ""  );
	TCHAR					content[255  +  1]							=		_T(  ""  );
	QY_MESSENGER_ID			idInfo										=		{	0,	};
	int						i;

	
	GetDlgItemText(  IDC_EDIT_talker,  talkerDesc,  mycountof(  talkerDesc  )  );  
	tTrim(  talkerDesc  );
	GetDlgItemText(  IDC_EDIT_Id,  str  );  myTChar2Str(  str,  buf,  mycountof(  buf  )  );
	trim(  buf  );  if  (  buf[0]  )  idStr2Info(  buf,  &idInfo  );
	buf[0]  =  0;
	if  (  idInfo.ui64Id  )  idInfo2Str(  &idInfo,  buf,  mycountof(  buf  )  );
	GetDlgItemText(  IDC_EDIT_content,  content,  mycountof(  content  )  );  tTrim(  content  );
	//

	m_var.wherePart[0]  =  0;
	if  (  talkerDesc[0]  )  {
		if  (  iDbType  ==  CONST_dbType_access  )
			_sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s (instr(qyImMsgTab.senderDesc,%s) or instr(qyImMsgTab.receiverDesc,%s))"  ),  m_var.wherePart,  (  m_var.wherePart[0]  ?  _T(  "and"  )  :  _T(  ""  )  ),  getDbValStr(  iDbType,  iDataType,  talkerDesc  ),  getDbValStr(  iDbType,  iDataType,  talkerDesc  )  );
		else  
			_sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s (qyImMsgTab.senderDesc like %s or qyImMsgTab.receiverDesc like %s)"  ),  m_var.wherePart,  (  m_var.wherePart[0]  ?  _T(  "and"  )  :  _T(  ""  )  ),  getDbValStr(  iDbType,  iDataType,  CString(  "%"  )  +  talkerDesc  +  _T(  "%"  )  ),  getDbValStr(  iDbType,  iDataType,  CString(  "%"  )  +  talkerDesc  +  _T(  "%"  )  )  );
	}
	if  (  idInfo.ui64Id  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s (qyImMsgTab.idStr_send='%s' or qyImMsgTab.idStr_recv='%s')"  ),  m_var.wherePart,  (  m_var.wherePart[0]  ?  _T(  "and"  )  :  _T(  ""  )),  CString(  buf  ),  CString(  buf  )  );
	if  (  content[0]  )  {
		TCHAR	sqlClause[CONST_maxSqlClauseLen  +  1]	=	_T(  ""  );
		//
		for  (  i  =  0;  i  <  10;  i  ++  )  {
			 if  (  iDbType  ==  CONST_dbType_access  )  _sntprintf(  sqlClause,  mycountof(  sqlClause  ),  _T(  "%s %s instr(qyImMsgTab.content%d,%s) or instr(qyImMsgTab.txtContent%d,%s)"  ),  sqlClause,  (  i  ?  _T(  "or"  )  :  _T(  ""  )  ),  i,  getDbValStr(  iDbType,  iDataType,  content  ),  i,  getDbValStr(  iDbType,  iDataType,  content  )  );
			 else  _sntprintf(  sqlClause,  mycountof(   sqlClause  ),  _T(  "%s %s qyImMsgTab.content%d like %s or qyImMsgTab.txtContent%d like %s"  ),  sqlClause,  (  i  ?  _T(  "or"  )  :  _T(  ""  )  ),  i,  getDbValStr(  iDbType,  iDataType,  CString(  "%"  )  +  content  +  _T(  "%"  )  ),  i,  getDbValStr(  iDbType,  iDataType,  CString(  "%"  )  +  content  +  _T(  "%"  )  )  );
		}
		//
		_sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s (%s)"  ),  m_var.wherePart,  (  m_var.wherePart[0]  ?  _T(  "and"  )  :  _T(  ""  )  ),  sqlClause  );
	}


	char	tStartBuf[256],  tEndBuf[256];
	
	if  (  qnmGetInputTime(  &this->m_startDateCtrl,  &this->m_startTimeCtrl,  &this->m_endDateCtrl,  &this->m_endTimeCtrl,  tStartBuf,  sizeof(  tStartBuf  ),  tEndBuf,  sizeof(  tEndBuf  )  )  )  {
		traceLogA(  (  " startTime must be <= endTime"  )  );  
		goto  errLabel;
	}

	if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s and "  ),  m_var.wherePart  );
	_sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s qyImMsgTab.tLastModifiedTime>'%s' and qyImMsgTab.tLastModifiedTime<'%s'"  ),  m_var.wherePart,  CString(  tStartBuf  ),  CString(  tEndBuf  )  );


	traceLogA(  "m_var.wherePart is [%s]",  m_var.wherePart  );

	iErr  =  0;
errLabel:
	return  iErr;
	
}




BOOL CDlgImMsgSearch::OnInitDialog()
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	CDialog::OnInitDialog();

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );


	// TODO:  在此添加额外的初始化

	
	//  
	DateTime_SetFormat(  this->m_startTimeCtrl.m_hWnd,  _T(  "HH:mm:ss"  )  );
	//
	DateTime_SetFormat(  this->m_endTimeCtrl.m_hWnd,  _T(  "HH:mm:ss"  )  );



	CTime	t  =  CTime::GetCurrentTime( );
	CTimeSpan	ts(  1,  0,  0,  0  );
	CTimeSpan	ts1(  0,  1,  0,  0  ); 
	CTime	tStart(  t  -  ts  ),  tEnd(  t  +  ts1  );

	this->m_startDateCtrl.SetTime(  &tStart  );
	this->m_startTimeCtrl.SetTime(  &tStart  );
	this->m_endDateCtrl.SetTime(  &tEnd  );
	this->m_endTimeCtrl.SetTime(  &tEnd  );

	UpdateData(  FALSE  );


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgImMsgSearch::OnOK()
{
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
