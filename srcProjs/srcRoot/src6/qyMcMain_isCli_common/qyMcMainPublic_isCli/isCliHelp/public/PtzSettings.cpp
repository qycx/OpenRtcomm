// PtzSettings.cpp : implementation file
//
#include	"stdafx.h"

#include	"qyMcMainCommon.h"
#include	"myresource.h"

#include	"PtzSettings.h"

#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
//  #include	"DlgTalk.h"
#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"

#include	"qyComPortEx.h"
#include	"ptzCommProc.h"

#include	"isCliHelpPublic.h"
#include	"ptzFunc.h"



__declspec(  dllexport  )  int  showDlgPtzSettings(  HWND  hParent  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int			iRet	=	-1;

	CPtzSettings		dlg(  CWnd::FromHandle(  hParent  )  );
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;

errLabel:
	return  iRet;
}




// CPtzSettings dialog

IMPLEMENT_DYNAMIC(CPtzSettings, CDialog)

CPtzSettings::CPtzSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CPtzSettings::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

}

CPtzSettings::~CPtzSettings()
{
}

void CPtzSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ptzProtoType, m_combo_protocolType);
	DDX_Control(pDX, IDC_EDIT_ptzAddr, m_edit_addrCode);
	DDX_Control(pDX, IDC_COMBO_comName, m_combo_name);
	DDX_Control(pDX, IDC_COMBO_comRate, m_combo_rate);
	DDX_Control(pDX, IDC_COMBO_comParity, m_combo_parity);
	DDX_Control(pDX, IDC_COMBO_comData, m_combo_data);
	DDX_Control(pDX, IDC_COMBO_comStopBit, m_combo_stopBit);
	DDX_Control(pDX, IDC_EDIT_remotePtzUsers, m_edit_remotePtzUsers);
	DDX_Control(pDX, IDC_EDIT_memoAppending, m_edit_memoAppending);
}


BEGIN_MESSAGE_MAP(CPtzSettings, CDialog)
	ON_BN_CLICKED(IDOK, &CPtzSettings::OnBnClickedOk)
END_MESSAGE_MAP()

//
//  2015/09/18
QY_DMITEM  CONST_ptzTypeTable[]	=	
{
			{	CONST_ptzType_usb,				_T(  "USB PTZ"  ),	},
			{	CONST_ptzType_serialPort,		_T(  "Serial Port PTZ"  ),	},
			{	-1,		},
};


//
QY_DMITEM  CONST_ptzProtoTable[]	=	
{
			{	CONST_ptzProto_PELCO_D,		_T(  "PELCO_D"  ),	},
			{	CONST_ptzProto_PELCO_P,		_T(  "PELCO_P"  ),	},
			{	-1,		},
};

// CPtzSettings message handlers
BOOL CPtzSettings::OnInitDialog()
{
	CDialog::OnInitDialog( );

	int  iErr  =  -1;
	TCHAR		tBuf[256]	=  _T(  "1"  );
	QY_MC	*	pQyMc		=	QY_GET_GBUF(  );
	CQyString			rootKeyStr;
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	rootKeyStr  =  CQyString(  tBuf  );


	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	getPtzSettings(  &m_var.cfg  );

	QY_DMITEM  *  pItem;
	for  (  pItem  =  CONST_ptzProtoTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 m_combo_protocolType.InsertString(  -1,  pItem->des  );		 
	}
	//  m_combo_protocolType.InsertString(  0,  _T(  "PELCO_D"  )  );
	//  m_combo_protocolType.InsertString(  1,  _T(  "PELCO_P"  )  );
	//  m_combo_protocolType.SetCurSel(  m_var.cfg.m_pelcoType  );
	m_combo_protocolType.SelectString(  -1,  qyGetDesByType1(  CONST_ptzProtoTable,  m_var.cfg.m_pelcoType  )  );
	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  m_var.cfg.m_nAddr  );
	m_edit_addrCode.SetWindowTextW(  tBuf  );

	m_combo_name.InsertString(  0,  _T(  "COM  1"  )  );
	m_combo_name.InsertString(  1,  _T(  "COM  2"  )  );
	m_combo_name.InsertString(  2,  _T(  "COM  3"  )  );
	m_combo_name.InsertString(  3,  _T(  "COM  4"  )  );
	m_combo_name.InsertString(  4,  _T(  "COM  5"  )  );
	m_combo_name.InsertString(  5,  _T(  "COM  6"  )  );
	m_combo_name.InsertString(  6,  _T(  "COM  7"  )  );
	m_combo_name.InsertString(  7,  _T(  "COM  8"  )  );
	m_combo_name.InsertString(  8,  _T(  "COM  9"  )  );
	m_combo_name.InsertString(  9,  _T(  "COM  10"  )  );
	m_combo_name.InsertString(  10,  _T(  "COM  11"  )  );
	m_combo_name.InsertString(  11,  _T(  "COM  12"  )  );
	m_combo_name.InsertString(  12,  _T(  "COM  13"  )  );
	m_combo_name.InsertString(  13,  _T(  "COM  14"  )  );
	m_combo_name.InsertString(  14,  _T(  "COM  15"  )  );
	m_combo_name.InsertString(  15,  _T(  "COM  16"  )  );
	m_combo_name.InsertString(  16,  _T(  "COM  17"  )  );
	m_combo_name.InsertString(  17,  _T(  "COM  18"  )  );
	m_combo_name.InsertString(  18,  _T(  "COM  19"  )  );
	m_combo_name.InsertString(  19,  _T(  "COM  20"  )  );
	m_combo_name.SetCurSel(  m_var.cfg.portNo  -  1  );
	//
	m_combo_rate.InsertString(  0,  _T(  "1200"  )  );
	m_combo_rate.InsertString(  1,  _T(  "2400"  )  );
	m_combo_rate.InsertString(  2,  _T(  "4800"  )  );
	m_combo_rate.InsertString(  3,  _T(  "7200"  )  );
	m_combo_rate.InsertString(  4,  _T(  "9600"  )  );
	m_combo_rate.InsertString(  5,  _T(  "14400"  )  );
	m_combo_rate.InsertString(  6,  _T(  "19200"  )  );
	m_combo_rate.InsertString(  7,  _T(  "38400"  )  );
	m_combo_rate.InsertString(  8,  _T(  "57600"  )  );
	m_combo_rate.InsertString(  9,  _T(  "115200"  )  );

	switch  (  m_var.cfg.m_rate  )  {
			case  1200:
				  m_combo_rate.SetCurSel(  0  );
				  break;
			case  2400:
				  m_combo_rate.SetCurSel(  1  );
				  break;
			case  4800:
				  m_combo_rate.SetCurSel(  2  );
				  break;
			case  7200:
				  m_combo_rate.SetCurSel(  3  );
				  break;
			case  9600:
				  m_combo_rate.SetCurSel(  4  );
				  break;
			case  14400:
				  m_combo_rate.SetCurSel(  5  );
				  break;
			case  19200:
				  m_combo_rate.SetCurSel(  6  );
				  break;
			case  38400:
				  m_combo_rate.SetCurSel(  7  );
				  break;
			case  57600:
				  m_combo_rate.SetCurSel(  8  );
				  break;
			case  115200:
				  m_combo_rate.SetCurSel(  9  );
				  break;
			default:
				  m_combo_rate.SetCurSel(  1  );
				  break;
	}

	m_combo_data.InsertString(  0,  _T(  "4"  )  );
	m_combo_data.InsertString(  1,  _T(  "5"  )  );
	m_combo_data.InsertString(  2,  _T(  "6"  )  );
	m_combo_data.InsertString(  3,  _T(  "7"  )  );
	m_combo_data.InsertString(  4,  _T(  "8"  )  );
	m_combo_data.SetCurSel(  m_var.cfg.m_dataBit  -  4  );

	m_combo_parity.InsertString(  0,  _T(  "NONE"  )  );
	m_combo_parity.InsertString(  1,  _T(  "ODD"  )  );
	m_combo_parity.InsertString(  2,  _T(  "EVEN"  )  );
	m_combo_parity.InsertString(  3,  _T(  "MARK"  )  );
	m_combo_parity.InsertString(  4,  _T(  "SPACE"  )  );
	m_combo_parity.SetCurSel(  m_var.cfg.m_parity  );

	m_combo_stopBit.InsertString(  0,  _T(  "1"  )  );
	m_combo_stopBit.InsertString(  1,  _T(  "1.5"  )  );
	m_combo_stopBit.InsertString(  2,  _T(  "2"  )  );
	m_combo_stopBit.SetCurSel(  m_var.cfg.m_stopBit  );

	getBufFromUi64Id(  m_var.cfg.idInfos_allowed,  mycountof(  m_var.cfg.idInfos_allowed  ),  tBuf,  mycountof(  tBuf  )  );
	

	SetDlgItemText(  IDC_EDIT_remotePtzUsers,  tBuf  );

	GetDlgItemText(  IDC_EDIT_memoAppending,  m_var.memoBuf,  mycountof(  m_var.memoBuf  )  );
	if  (  !qyGetRegCfgT(  HKEY_CURRENT_USER,  rootKeyStr,  CONST_regValName_memoAppending,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  
	{
		if  (  memcmp(  m_var.memoBuf,  tBuf,  mycountof(  m_var.memoBuf  )  )  )  {
			_sntprintf(  m_var.memoBuf,  mycountof(  m_var.memoBuf  ),  _T(  "%s"  ),  tBuf  );
		    SetDlgItemText(  IDC_EDIT_memoAppending,  m_var.memoBuf  );
		}
	}
	
	//
	CComboBox  *  pCb_ptzType  =  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_ptzType  );
	if  (  !pCb_ptzType  )  goto  errLabel;
	for  (  pItem  =  CONST_ptzTypeTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 pCb_ptzType->InsertString(  -1,  pItem->des  );
	}
	pCb_ptzType->SelectString(  -1,  qyGetDesByType(  CONST_ptzTypeTable,  m_var.cfg.iPtzType  )  );

	//  2015/09/19
	SetDlgItemText(  IDC_STATIC_hint,  _T(  "Only camera in conference can use USB PTZ ( if possible ). "  )  );

	//
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		PostMessage(  WM_CLOSE  );
	}

	//
	return  TRUE;
}




void CPtzSettings::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	QY_MC			*	pQyMc		=  QY_GET_GBUF(  );
	CQyString			rootKeyStr;
	TCHAR			*	pRegVal;
	TCHAR				tBuf[256]	=  _T(  ""  );
	TCHAR				checkedBuf[256]	= _T(  ""  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	rootKeyStr  =  CQyString(  tBuf  );
	//
	COM_PORT_cfg	    curCfg;
	//  BOOL				bHaveValidId			=  FALSE;
	//  BOOL				bRemotePtzUsersEmpty	=  FALSE;
	//
	UpdateData(  TRUE  );

	//  2015/09/20
	GetDlgItemText(  IDC_COMBO_ptzType,  tBuf,  mycountof(  tBuf  )  );
	curCfg.iPtzType  =  qyGetTypeByDes(  CONST_ptzTypeTable,  tBuf  );

	//  curCfg.m_pelcoType  =  m_combo_protocolType.GetCurSel(  );
	//  m_combo_protocolType.getcurs
	GetDlgItemText(  IDC_COMBO_ptzProtoType,  tBuf,  mycountof(  tBuf  )  );
	curCfg.m_pelcoType  =  qyGetTypeByDes(  CONST_ptzProtoTable,  tBuf  );

	curCfg.m_nAddr  =  GetDlgItemInt(  IDC_EDIT_ptzAddr  );
	//
	curCfg.portNo  =  m_combo_name.GetCurSel(  )  +  1;

	switch  (  m_combo_rate.GetCurSel(  )  )  {
			case  0:
				  curCfg.m_rate  =  1200;
				  break;
			case  1:
				  curCfg.m_rate  =  2400;
				  break;
			case  2:
				  curCfg.m_rate  =  4800;
				  break;
			case  3:
				  curCfg.m_rate  =  7200;
				  break;
			case  4:
				  curCfg.m_rate  =  9600;
				  break;
			case  5:
				  curCfg.m_rate  =  14400;
				  break;
			case  6:
				  curCfg.m_rate  =  19200;
				  break;
			case  7:
				  curCfg.m_rate  =  38400;
				  break;
			case  8:
				  curCfg.m_rate  =  57600;
				  break;
			case  9:
				  curCfg.m_rate  =  115200;
				  break;
			default:
				  curCfg.m_rate  =  2400;
				  break;
	}
	curCfg.m_parity  =  m_combo_parity.GetCurSel(  );
	curCfg.m_dataBit  =  m_combo_data.GetCurSel(  )  +  4;
	curCfg.m_stopBit  =  m_combo_stopBit.GetCurSel(  );


	GetDlgItemText(  IDC_EDIT_remotePtzUsers,  tBuf,  mycountof(  tBuf  )  );

	//  getUi64IdFromInput(  tBuf,  bHaveValidId,  bRemotePtzUsersEmpty,  curCfg.idInfos_allowed,  mycountof(  curCfg.idInfos_allowed  )  );
	getUi64IdFromReg(  tBuf,  curCfg.idInfos_allowed,  mycountof(  curCfg.idInfos_allowed  )  );

	//
	getBufFromUi64Id(  curCfg.idInfos_allowed,  mycountof(  curCfg.idInfos_allowed  ),  checkedBuf,  mycountof(  checkedBuf  )  );

errLabel:

	//  2015/09/20
	if  (  curCfg.iPtzType  !=  m_var.cfg.iPtzType  )  {
		m_var.cfg.iPtzType  =  curCfg.iPtzType;
		qySetRegCfgT(  HKEY_CURRENT_USER,  rootKeyStr,  CONST_regValName_ptzType,  CQyString(  _ltot(  m_var.cfg.iPtzType,  tBuf,  10  )  )  );
	}

	//
	if  (  memcmp(  curCfg.idInfos_allowed,  m_var.cfg.idInfos_allowed,  sizeof(  curCfg.idInfos_allowed  )  )  ) {
		memcpy(  &m_var.cfg.idInfos_allowed,  &curCfg.idInfos_allowed,  sizeof(  m_var.cfg.idInfos_allowed  )  );
		qySetRegCfgT(  HKEY_CURRENT_USER,  rootKeyStr,  CONST_regValName_remotePtzUsers,  checkedBuf  );
	}

	if  (  m_var.cfg.m_nAddr  !=  curCfg.m_nAddr  )  {
		m_var.cfg.m_nAddr  =  curCfg.m_nAddr;
		qySetRegCfgT(  HKEY_CURRENT_USER,  rootKeyStr,  CONST_regValName_ptzAddr,  CQyString(  _ltot(  m_var.cfg.m_nAddr,  tBuf,  10  )  )  );
	}

	if  (  m_var.cfg.m_dataBit  !=  curCfg.m_dataBit  )  {
		m_var.cfg.m_dataBit  =  curCfg.m_dataBit;
		qySetRegCfgT(  HKEY_CURRENT_USER,  rootKeyStr,  CONST_regValName_comData,  CQyString(  _ltot(  m_var.cfg.m_dataBit,  tBuf,  10  )  )  );
	}

	if  (  m_var.cfg.m_parity  !=  curCfg.m_parity  )  {
		m_var.cfg.m_parity  =  curCfg.m_parity;
		qySetRegCfgT(  HKEY_CURRENT_USER,  rootKeyStr,  CONST_regValName_comParity,  CQyString(  _ltot(  m_var.cfg.m_parity,  tBuf,  10  )  )  );
	}

	if  (  m_var.cfg.m_pelcoType  !=  curCfg.m_pelcoType  ) {
		m_var.cfg.m_pelcoType  =  curCfg.m_pelcoType;
		qySetRegCfgT(  HKEY_CURRENT_USER,  rootKeyStr,  CONST_regValName_ptzProtoType,  CQyString(  _ltot(  m_var.cfg.m_pelcoType,  tBuf,  10  )  )  );
	}
	if  (  m_var.cfg.m_rate  !=  curCfg.m_rate  )  {
		m_var.cfg.m_rate  =  curCfg.m_rate;
		qySetRegCfgT(  HKEY_CURRENT_USER,  rootKeyStr,  CONST_regValName_comBaud,  CQyString(  _ltot(  m_var.cfg.m_rate,  tBuf,  10  )  )  );
	}

	if  (  m_var.cfg.m_stopBit  !=  curCfg.m_stopBit  )  {
		m_var.cfg.m_stopBit  =  curCfg.m_stopBit;
		qySetRegCfgT(  HKEY_CURRENT_USER,  rootKeyStr,  CONST_regValName_comStopBit,  CQyString(  _ltot(  m_var.cfg.m_stopBit,  tBuf,  10  )  )  );
	}

	if  (  m_var.cfg.portNo  !=  curCfg.portNo  )  {
		m_var.cfg.portNo  =  curCfg.portNo;
		qySetRegCfgT(  HKEY_CURRENT_USER,  rootKeyStr,  CONST_regValName_comName,  CQyString(  _ltot(  m_var.cfg.portNo,  tBuf,  10  )  )  );
	}

	memset(  tBuf, 0,  sizeof(  tBuf  )  );
	GetDlgItemText(  IDC_EDIT_memoAppending,  tBuf,  mycountof(  tBuf  )  );
	if  (  _tcscmp(  m_var.memoBuf,  tBuf  )  )  {
		//
		TCHAR  tBuf1[256]  =  _T(  ""  );
		TCHAR  tmpBuf[256]	= _T(  ""  );
		TCHAR  *p, *p1;
		p  =  tBuf;
		int		len;
	
		for  (  ;  p[0];  )
		{
			if  (  !(  p1  =  _tcschr(  p,  '\n'  )  )  &&  !tBuf1[0]  )  {
				_sntprintf(  tBuf1,  mycountof(  tBuf1  ),  _T(  "%s"  ),  p  );
				break;
			}
			if  (  !p1  )  
			{		
				_sntprintf(  tBuf1,  mycountof(  tBuf1  ),  _T(  "%s;%s"  ),  tBuf1,  p  );
				break;
			}

			len  =  min(  p1  -  p  -1,  mycountof(  tmpBuf  )  -  1  );
			_tcsncpy(  tmpBuf,  p,  len  );
			tmpBuf[len]  =  0;
		
			if  (  !tBuf1[0]  )  
			{
				_sntprintf(  tBuf1,  mycountof(  tBuf1  ),  _T(  "%s"  ),  tmpBuf  );
			}
			else  
			{
				_sntprintf(  tBuf1,  mycountof(  tBuf1  ),  _T(  "%s;%s"  ),  tBuf1,  tmpBuf  );

			}
			p  =  p1  +  1;
			if  (  !p[0]  )  break;
		}

		qySetRegCfgT(  HKEY_CURRENT_USER,  rootKeyStr,  CONST_regValName_memoAppending,  tBuf1  );
	}

//  errLabel2:
	OnOK();
}