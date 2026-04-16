// DlgSelectAvCompressor.cpp : implementation file
//

#include "stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include "DlgSelectAvCompressor.h"
#include "afxdialogex.h"

#include	"qyOpenShellCommon.h"
#include	"dlgTalkProc.h"

#include	"isCliHelpPublic.h"
#include	"isCliD3dPublic.h"
//  #include	"funcsForIsCliHelp.h"

#include	"qyCusResTemp.h"
#include	"policyIsClientFunc.h"

#include	"dyn_isCliD3d_public.h"

BOOL  bSetNoPrompt_selectAvCompressor(unsigned  int  uiCapType, unsigned  int  uiSubCapType, BOOL  bNoPrompt);


//  2014/04/27
QY_IDCITEM  CONST_selectAvCompressorCategoryTable[]  =
{
	{	CONST_capType_av,				0,									_T(  "AV"  ),	},
	{	CONST_capType_av,				CONST_subCapType_webcam,			_T(  "Webcam"  ),	},
	{	CONST_capType_screen,			0,									_T(  "Screen"  ),	},
	{	CONST_capType_mediaFile,		0,									_T(  "Media file"  ),	},
	{	CONST_capType_mediaDevice,		0,									_T(  "Media device"  ),	},
	//  2015/03/11
	{	CONST_capType_mediaDevice,		CONST_subCapType_unresizable,		_T(  "Unresizable device"  ),	},	
	//
	{	-1,	},
};


//  2014/05/04
QY_IDCITEM  CONST_idcLevelTable_av[]  =
{
	{	IDC_BUTTON_video4k,		CONST_policyAvLevel_2160p,			(TCHAR*)CONST_resId_avLevel_2160p,		},

	//
	{	IDC_BUTTON_1080p,		CONST_policyAvLevel_1080p,			(  TCHAR  *  )CONST_resId_avLevel_1080p,		},
	{	IDC_BUTTON_720p,		CONST_policyAvLevel_720p,			(  TCHAR  *  )CONST_resId_avLevel_720p,		},
	{	IDC_BUTTON_576p,		CONST_policyAvLevel_576p,			(  TCHAR  *  )CONST_resId_avLevel_576p,		},
	{	IDC_BUTTON_480p,		CONST_policyAvLevel_480p,			(  TCHAR  *  )CONST_resId_avLevel_480p,		},
	{	IDC_BUTTON_240p,		CONST_policyAvLevel_240p,			(  TCHAR  *  )CONST_resId_avLevel_240p,		},
	{	IDC_BUTTON_144p,		CONST_policyAvLevel_256x144,			(TCHAR*)CONST_resId_avLevel_256x144,		},

	//
	{	-1,	},
};

#if 0
QY_IDCITEM  CONST_idcLevelTable_av_conf[]  =
{
	//
	{	IDC_BUTTON_1080p_conf,	CONST_policyAvLevel_1080p,			(  TCHAR  *  )CONST_resId_avLevel_1080p,		},
	{	IDC_BUTTON_720p_conf,	CONST_policyAvLevel_720p,			(  TCHAR  *  )CONST_resId_avLevel_720p,		},
	{	IDC_BUTTON_576p_conf,	CONST_policyAvLevel_576p,			(  TCHAR  *  )CONST_resId_avLevel_576p,		},
	{	IDC_BUTTON_480p_conf,	CONST_policyAvLevel_480p,			(  TCHAR  *  )CONST_resId_avLevel_480p,		},
	{	IDC_BUTTON_240p_conf,	CONST_policyAvLevel_240p,			(  TCHAR  *  )CONST_resId_avLevel_240p,		},

	//
	{	-1,	},
};
#endif



QY_IDCITEM  CONST_idcLevelTable_screen[]  =
{
	{	IDC_BUTTON_1080p,		CONST_policyAvLevel_1080p,			(  TCHAR  *  )CONST_resId_avLevel_1080p,	0,  0,	NULL,	0,	0,0,0,0,	CONST_qyIdcFlgHide,			},
	{	IDC_BUTTON_720p,		CONST_policyAvLevel_dev_5fps2,		(  TCHAR  *  )CONST_resId_avLevel_dev_5fps2,		},
	//
	{	IDC_BUTTON_576p,		CONST_policyAvLevel_dev_5fps1,		(  TCHAR  *  )CONST_resId_avLevel_dev_5fps1,			},
	{	IDC_BUTTON_480p,		CONST_policyAvLevel_dev_5fps,		(  TCHAR  *  )CONST_resId_avLevel_dev_5fps,	},
	{	IDC_BUTTON_240p,		CONST_policyAvLevel_dev_2fps,		(  TCHAR  *  )CONST_resId_avLevel_dev_2fps,	},


	//
	{	-1,	},
};

QY_IDCITEM  CONST_idcLevelTable_screen_conf[]  =
{

	//  2014/08/15
	{	IDC_BUTTON_1080p_conf,	CONST_policyAvLevel_1080p,			(  TCHAR  *  )CONST_resId_avLevel_1080p,	0,  0,	NULL,	0,	0,0,0,0,	CONST_qyIdcFlgHide,			},	
	{	IDC_BUTTON_720p_conf,	CONST_policyAvLevel_720p,			(  TCHAR  *  )CONST_resId_avLevel_720p,		0,  0,	NULL,	0,	0,0,0,0,	CONST_qyIdcFlgHide,			},
	{	IDC_BUTTON_576p_conf,	CONST_policyAvLevel_576p,			(  TCHAR  *  )CONST_resId_avLevel_576p,		0,  0,	NULL,	0,	0,0,0,0,	CONST_qyIdcFlgHide,			},
	{	IDC_BUTTON_480p_conf,	CONST_policyAvLevel_480p,			(  TCHAR  *  )CONST_resId_avLevel_480p,		0,  0,	NULL,	0,	0,0,0,0,	CONST_qyIdcFlgHide,			},
	{	IDC_BUTTON_240p_conf,	CONST_policyAvLevel_240p,			(  TCHAR  *  )CONST_resId_avLevel_240p,		0,  0,	NULL,	0,	0,0,0,0,	CONST_qyIdcFlgHide,			},

	//
	{	-1,	},
};




QY_IDCITEM  *  getIdcLevelTable(  unsigned  int  uiCapType, unsigned  int  uiSubCapType,  BOOL  bConf  )
{
	//
#if 0
	if  (  bConf  )  {
		if  (  uiCapType  ==  CONST_capType_av  &&  uiSubCapType  ==  0  )  return  CONST_idcLevelTable_av_conf;
		return  CONST_idcLevelTable_screen_conf;
	}
#endif

	//
	if  (  uiCapType  ==  CONST_capType_av  &&  uiSubCapType  ==  0  )  return  CONST_idcLevelTable_av;
	//
	if  (  uiCapType  ==  CONST_capType_screen  )  return  CONST_idcLevelTable_screen;
	//  2015/03/11
	if  (  uiCapType  ==  CONST_capType_mediaDevice  &&  uiSubCapType  ==  CONST_subCapType_unresizable  )  {
		return  CONST_idcLevelTable_screen;
	}
	//
	return  CONST_idcLevelTable_av;
}





///////////////////////////
//
__declspec(  dllexport  )  BOOL  bNoPrompt_selectConfCtrl(  unsigned  int  uiCapType,  unsigned  int  uiSubCapType  )
{
	BOOL				bNoPrompt		=	FALSE;

	QY_MC			*	pQyMc	=	QY_GET_GBUF(  );


	TCHAR				tBuf[256]	=  _T(  ""  );
	QY_REG				reg;


	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	lstrcpyn(  reg.rootKey,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  sizeof(  reg.rootKey  )  );

	//  2014/04/08
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_noPrompt_selConfCtrl,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )	&&  _ttol(  tBuf  )  )  {
		bNoPrompt  =  TRUE;
	}

	return  bNoPrompt;
}


BOOL  bSetNoPrompt_selectConfCtrl(  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  BOOL  bNoPrompt  )
{

	QY_MC			*	pQyMc	=	QY_GET_GBUF(  );


	TCHAR				tBuf[256]	=  _T(  ""  );
	QY_REG				reg;


	TCHAR			*	pRegVal		=	NULL;


	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	lstrcpyn(  reg.rootKey,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  sizeof(  reg.rootKey  )  );


	pRegVal  =  CONST_regValName_noPrompt_selConfCtrl;
	//
	if  (  bNoPrompt  )  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _T(  "1"  )  );
	else  qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	return  0;
}





//
//__declspec(  dllexport  )  int  viewDlgSelectAvCompressor(  HWND  hParent,  HWND  hCurTalk,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage,  BOOL  b3D,  unsigned char * pucbShowBgWall_confMem  )
__declspec(  dllexport  ) int  viewDlgSelectAvCompressor_mfc(  HWND  hParent,  QY_MESSENGER_ID idInfo,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage,  BOOL  b3D,  unsigned  short  usConfType  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int  iRet=  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	//
	if  (  dyn_bFullScreen_d3dWnd(  pProcInfo,  NULL  )  )  return  IDOK;

	//
	CDlgSelectAvCompressor	dlg(  CWnd::FromHandle(  hParent  )  );
	dlg.bSetDlgInfo(  idInfo,  uiCapType,  uiSubCapType,  iCapUsage,  b3D,  usConfType  );
	iRet  =  dlg.DoModal(  );

	//
	if  (  iRet  ==  IDOK  )  {
		//if  (  pucbShowBgWall_confMem  ) *pucbShowBgWall_confMem  =  dlg.m_var.policy.ucbShowBgWall_confMem;				//  2014/10/08.mem.
	}

errLabel:

	//
	return  iRet;
}

	//  2014/10/13








//









 //
 


// CDlgSelectAvCompressor dialog

IMPLEMENT_DYNAMIC(CDlgSelectAvCompressor, CDialogEx)

CDlgSelectAvCompressor::CDlgSelectAvCompressor(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSelectAvCompressor::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgSelectAvCompressor::~CDlgSelectAvCompressor()
{
}

BOOL  CDlgSelectAvCompressor::bSetDlgInfo(  QY_MESSENGER_ID idInfo,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage,  BOOL  b3D,  unsigned  short  usConfType  )
{
	//m_var.hCurTalk  =  hCurTalk;

#if  0
	CHelp_getDlgTalkVar		help_getDlgTalkVar;
	DLG_TALK_var		*	pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hCurTalk  );
	if  (  !pDlgTalkVar  )  return  FALSE;
#endif
	if (!idInfo.ui64Id)return false;

	m_var.idInfo.ui64Id = idInfo.ui64Id;// pDlgTalkVar->addr.idInfo.ui64Id;
	m_var.uiCapType  =  uiCapType;
	m_var.uiSubCapType  =  uiSubCapType;
	m_var.iCapUsage  =  iCapUsage;
	//
	m_var.b3D  =  b3D;
	//
	m_var.usConfType  =  usConfType;  //  2017/08/25

	//
	getTalkerDesc(m_var.idInfo, &m_var.uiObjType, mynull, 0, mynull, mynull, 0, mynull, 0, mynull, 0);


	//
	return  TRUE;
}


//
int  CDlgSelectAvCompressor::get_iCapUsage_toDisplay(  )
{
	int  iCapUsage_toDisplay  =  0;
	int  iCapUsage_conf  =  m_var.b3D  ?  CONST_capUsage_3dConf  :  CONST_capUsage_conf;
	
	//  2017/10/10
	if  (  m_var.b3D  )  iCapUsage_toDisplay  =  iCapUsage_conf;
	else  iCapUsage_toDisplay  =  0;

	return  iCapUsage_toDisplay;  
}


//
int  CDlgSelectAvCompressor::get_level_toDisplay(  )
{
	int  tmp_level  =  m_var.level;
	if  (  m_var.uiCapType  ==  CONST_capType_av  )  {
		if (m_var.b3D)  tmp_level = m_var.level;// .level_conf;
	}
	return  tmp_level;
}



	


BOOL  CDlgSelectAvCompressor::bShowInfo(  )
{
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	TCHAR			*	pRegVal		=	NULL;
	
	//
	if  (  !m_var.bInited_buStatus  )  return  FALSE;

	//
	QY_IDCITEM  *  pItem;
		
	//
	for  (  pItem  =  getIdcLevelTable(  m_var.uiCapType,  m_var.uiSubCapType,  FALSE  );  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->flg  &  CONST_qyIdcFlgHide  )  {
			 ::ShowWindow(  ::GetDlgItem(  m_hWnd,  pItem->idc  ),  SW_HIDE  );
			 continue;
		 }
		 ::ShowWindow(  ::GetDlgItem(  m_hWnd,  pItem->idc  ),  SW_SHOW  );
		 switch  (  pItem->idc  )  {
				 case  IDC_BUTTON_1080p:							   	
					   m_buStatus_1080p.m_text  =  getResStr(  0,  &pQyMc->cusRes,  (  int  )pItem->des  );
					   break;
				 case  IDC_BUTTON_720p:							   	
					   m_buStatus_720p.m_text  =  getResStr(  0,  &pQyMc->cusRes,  (  int  )pItem->des  );
					   break;
				 case  IDC_BUTTON_576p:							   	
					   m_buStatus_576p.m_text  =  getResStr(  0,  &pQyMc->cusRes,  (  int  )pItem->des  );
					   break;
				 case  IDC_BUTTON_480p:							   	
					   m_buStatus_480p.m_text  =  getResStr(  0,  &pQyMc->cusRes,  (  int  )pItem->des  );
					   break;
				 case  IDC_BUTTON_240p:							   	
					   m_buStatus_240p.m_text  =  getResStr(  0,  &pQyMc->cusRes,  (  int  )pItem->des  );
					   break;
					   //
				 case  IDC_BUTTON_144p:
					 m_buStatus_144p.m_text = getResStr(0, &pQyMc->cusRes, (int)pItem->des);

					 break;

				 default:
						break;
		 }
	}
	//
	for  (  pItem  =  getIdcLevelTable(  m_var.uiCapType,  m_var.uiSubCapType,  TRUE  );  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->flg  &  CONST_qyIdcFlgHide  )  {
			 ::ShowWindow(  ::GetDlgItem(  m_hWnd,  pItem->idc  ),  SW_HIDE  );
			 continue;
		 }
		 ::ShowWindow(  ::GetDlgItem(  m_hWnd,  pItem->idc  ),  SW_SHOW  );

	}


	//
	int  idc_sel  =  0;
	pItem  =  getIdcLevelTable(  m_var.uiCapType,  m_var.uiSubCapType,  FALSE  );
	for  (  ;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->idcType  ==  m_var.level  )  {
			 idc_sel  =  pItem->idc;
			 break;
		 }
	}
	//
	this->m_buStatus_video4k.m_nFlag = false;
	this->m_buStatus_1080p.m_nFlag = FALSE;
	this->m_buStatus_720p.m_nFlag = FALSE;
	this->m_buStatus_576p.m_nFlag = FALSE;
	this->m_buStatus_480p.m_nFlag = FALSE;
	this->m_buStatus_240p.m_nFlag = false;
	this->m_buStatus_144p.m_nFlag = false;

	//
	switch  (  idc_sel  ) {
			case  IDC_BUTTON_video4k:
				this->m_buStatus_video4k.m_nFlag = TRUE;
				break;
			case  IDC_BUTTON_1080p:
				this->m_buStatus_1080p.m_nFlag  =  TRUE;
				  break;
			case  IDC_BUTTON_720p:
				  this->m_buStatus_720p.m_nFlag  =  TRUE;  
				  break;
			case  IDC_BUTTON_576p:
				  this->m_buStatus_576p.m_nFlag  =  TRUE;
				  break;
			case  IDC_BUTTON_480p:
				  this->m_buStatus_480p.m_nFlag  =  TRUE;
				  break;
			case  IDC_BUTTON_240p:
				  this->m_buStatus_240p.m_nFlag  =  TRUE;
				  break;
			case  IDC_BUTTON_144p:
			default:
				this->m_buStatus_144p.m_nFlag = TRUE;
				//
				break;
	}

	//  2015/08/15		
	idc_sel  =  0;
	pItem  =  getIdcLevelTable(  m_var.uiCapType,  m_var.uiSubCapType,  TRUE  );
	for  (  ;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->idcType  ==  m_var.level  )  {
			 idc_sel  =  pItem->idc;
			 break;
		 }
	}
	//




	//  
	AV_COMPRESSOR_CFG  compressor  =  {0};
	getCompressorCfg(  NULL,  m_var.uiCapType,  m_var.uiSubCapType,  get_iCapUsage_toDisplay(),  get_level_toDisplay(  ),  &compressor  );
	//  
	SetDlgItemText(  IDC_STATIC_avCompressor,  getCompressorDesc(  m_var.uiCapType,  &compressor  )  );
   //
	this->m_buStatus_video4k.InvalidateRect(NULL);
	this->m_buStatus_video4k.UpdateWindow();

	this->m_buStatus_1080p.InvalidateRect(  NULL  );
	this->m_buStatus_1080p.UpdateWindow(  );
	this->m_buStatus_720p.InvalidateRect(  NULL  );
	this->m_buStatus_720p.UpdateWindow();
	this->m_buStatus_576p.InvalidateRect(  NULL  );
	this->m_buStatus_576p.UpdateWindow();
	this->m_buStatus_480p.InvalidateRect(  NULL  );
	this->m_buStatus_480p.UpdateWindow( );
	this->m_buStatus_240p.InvalidateRect(  NULL  );
	this->m_buStatus_240p.UpdateWindow();
	//
	this->m_buStatus_144p.InvalidateRect(NULL);
	this->m_buStatus_144p.UpdateWindow();

	//
	BOOL  bConfSetting  =  FALSE;
	if  (  m_var.uiCapType  ==  CONST_capType_av  &&  !m_var.uiSubCapType  )  {
	}


	//
	if  (  bConfSetting  )  {
		::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_prefer_conf  ),  SW_SHOW  );
		// 2014/10/07
		//
		}
	else  {
		  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_prefer_conf  ),  SW_HIDE  );

		  //  2014/10/07
	}	

errLabel:

	return  TRUE;

}


void CDlgSelectAvCompressor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSelectAvCompressor, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSelectAvCompressor::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_cfg, &CDlgSelectAvCompressor::OnBnClickedButtoncfg)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_category, &CDlgSelectAvCompressor::OnCbnSelchangeCombocategory)
	ON_BN_CLICKED(IDC_CHECK_useBgWall, &CDlgSelectAvCompressor::OnBnClickedCheckusebgwall)
	ON_BN_CLICKED(IDC_CHECK_noPrompt, &CDlgSelectAvCompressor::OnBnClickedChecknoprompt)
	ON_BN_CLICKED(IDC_CHECK_ucbManuallyConfCtrl, &CDlgSelectAvCompressor::OnBnClickedCheckucbmanuallyconfCtrl)
	ON_CBN_SELCHANGE(IDC_COMBO_videoCodec, &CDlgSelectAvCompressor::OnCbnSelchangeCombovideocodec)
	ON_EN_CHANGE(IDC_EDIT_usMaxSpeakers, &CDlgSelectAvCompressor::OnEnChangeEditusmaxspeakers)
	ON_BN_CLICKED(IDC_CHECK_2Streams, &CDlgSelectAvCompressor::OnBnClickedCheck2streams)
	
	ON_BN_CLICKED(IDC_CHECK_bLyra, &CDlgSelectAvCompressor::OnBnClickedCheckblyra)
	ON_BN_CLICKED(IDC_BUTTON_144p, &CDlgSelectAvCompressor::OnBnClickedButton144p)
	ON_BN_CLICKED(IDC_BUTTON_240p, &CDlgSelectAvCompressor::OnBnClickedButton240p)
END_MESSAGE_MAP()


// CDlgSelectAvCompressor message handlers

//
#define		CONST_str_1fps		_T(  "1"  )
#define		CONST_str_2fps		_T(  "2"  )
//
#define		CONST_str_5fps		_T(  "5"  )
#define		CONST_str_10fps		_T(  "10"  )
#define		CONST_str_15fps		_T(  "15"  )
#define		CONST_str_30fps		_T(  "30"  )
#define		CONST_str_60fps		_T(  "60"  )


//
BOOL CDlgSelectAvCompressor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	
	//
	int  idc;

	//
	TCHAR  *  pT  =  _T(  ""  );
	switch  (  m_var.usConfType  )  {
			case  CONST_usConfType_consult:
				  pT  =  _T(  "远程会诊"  );
				  break;
			default:
					break;
	}
	SetDlgItemText(  IDC_STATIC_confType,  pT  );


	//
	SetDlgItemText(IDC_CHECK_ucb2Streams, _T("two streams while screen sharing"));

	//
	this->m_buStatus_video4k.m_text=_T("4k");


	//
	idc = IDC_BUTTON_video4k;
	this->m_buStatus_video4k.SubclassDlgItem(idc, this);
	idc  =  IDC_BUTTON_1080p;
	this->m_buStatus_1080p.SubclassDlgItem(  idc,  this  );
	idc  =  IDC_BUTTON_720p;
	this->m_buStatus_720p.SubclassDlgItem(  idc,  this  );
	idc  =  IDC_BUTTON_576p;
	this->m_buStatus_576p.SubclassDlgItem(  idc,  this  );
	idc  =  IDC_BUTTON_480p;
	this->m_buStatus_480p.SubclassDlgItem(  idc,  this  );
	idc  =  IDC_BUTTON_240p;
	this->m_buStatus_240p.SubclassDlgItem(  idc,  this  );
	idc = IDC_BUTTON_144p;
	this->m_buStatus_144p.SubclassDlgItem(idc, this);

	//
	idc = IDC_BUTTON_144p;
	SetDlgItemText(idc, _T("144p"));


	//
	idc = IDC_STATIC_fps;
	SetDlgItemText(idc, _T("fps:"));
	idc = IDC_STATIC_BITRATE;
	SetDlgItemText(idc, _T("bitrate(kbps):"));
	//
	idc = IDC_STATIC_bitrate_ul;
	SetDlgItemText(idc, _T("bitrate_ul(kbps):"));


	//
	idc = IDC_COMBO_fps;
	//
	((CComboBox*)GetDlgItem(idc))->InsertString(-1, CONST_str_1fps);
	((CComboBox*)GetDlgItem(idc))->InsertString(-1, CONST_str_2fps);
	//
	((CComboBox*)GetDlgItem(idc))->InsertString(-1, CONST_str_5fps);
	//
	((CComboBox*)GetDlgItem(idc))->InsertString(-1, CONST_str_10fps);
	((CComboBox*)GetDlgItem(idc))->InsertString(-1, CONST_str_15fps);
	((CComboBox*)GetDlgItem(idc))->InsertString(-1, CONST_str_30fps);
	((CComboBox*)GetDlgItem(idc))->InsertString(-1, CONST_str_60fps);
	//
	((CComboBox*)GetDlgItem(idc))->SelectString(0, CONST_str_30fps);

	//
	idc = IDC_CHECK_bLyra;
	SetDlgItemText(idc, _T("Lyra"));




	//
	this->m_var.bInited_buStatus  =  TRUE;


	//  2014/04/27
	QY_IDCITEM  *  pItem  =  CONST_selectAvCompressorCategoryTable;
	idc  =  IDC_COMBO_category;
	for  (  ;  pItem->idc  !=  -1;  pItem  ++  )  {
		 //
		(  (  CComboBox  *  )GetDlgItem(  idc  )  )->InsertString(  -1,  pItem->des  );
	}


	CQyString		selStr;
	for  (  pItem  =  CONST_selectAvCompressorCategoryTable;  pItem->idc  !=  -1;  pItem  ++  )  {
		if  (  pItem->idc  ==  m_var.uiCapType  &&  pItem->idcType  ==  m_var.uiSubCapType  )  {
			selStr  =  pItem->des;
			break;
		}
	}
	(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SelectString(  -1,  selStr  );


	//
	SetDlgItemText(  IDC_STATIC_videoCodec,  _T(  "Video codec:"  )  );
	//	
	idc  =  IDC_COMBO_videoCodec;
	QY_DMITEM  *  pItem1;  
	for  (  pItem1  =  CONST_conf_fourccTable;  pItem1->type  !=  -1;  pItem1  ++  )  {
		 char  fourccStr[5]  =  "";		
		 iFourcc2Str(  pItem1->type,  fourccStr,  sizeof(  fourccStr  )  );
		 (  (  CComboBox  *  )GetDlgItem(  idc  )  )->InsertString(  -1,  CString(  fourccStr  )  );
	}
	//
	TCHAR  tBuf[128];
	char  buf[128];
	int  conf_iFourcc  =  get_conf_iFourcc(  );
	iFourcc2Str(  conf_iFourcc,  buf,  sizeof(  buf  )  );
	idc  =  IDC_COMBO_videoCodec;
	(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SelectString(  -1,  CString(  buf  )  );
	
	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "最多发言人数"  )  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%d-%d):"  ),  tBuf, 1, MAX_real_speakers_taskAv_h264   );
	SetDlgItemText(  IDC_STATIC_usMaxSpeakers,  tBuf  );
	//
	idc = IDC_EDIT_usMaxSpeakers;
	ushort  usMaxSpeakers  =  get_conf_usMaxSpeakers(  );
	SetDlgItemInt(  idc,  usMaxSpeakers  );



	//
	BOOL   bChecked  =  FALSE;
	bChecked  =  bNoPrompt_selectAvCompressor(  m_var.uiCapType,  m_var.uiSubCapType  );
	if  (  bChecked  )  (  (  CButton  *  )GetDlgItem(  IDC_CHECK_noPrompt  )  )->SetCheck(  bChecked  ?  1  :  0  );

	//  
	m_var.level  =  getPolicyAvLevel(  pQyMc,  m_var.uiCapType,  m_var.uiSubCapType,  0  );
	//
	int  iCapUsage  =  m_var.b3D  ?  CONST_capUsage_3dConf  :  CONST_capUsage_conf;
	//
	m_var.level  =  getPolicyAvLevel(  pQyMc,  m_var.uiCapType,  m_var.uiSubCapType,  iCapUsage  );	//  2014/08/15
	
	
	//
	getTalkerPolicy(  &m_var.idInfo,  &m_var.policy  );
	//
	CHelp_getDlgTalkVar  help_getDlgTalkVar;		
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	
	//
	m_var.ucbStarter = true;
	//
	bShowInfo(  );
	//
	if  (  //!pMgrVar->av.taskInfo.bTaskExists  ||  
		m_var.ucbStarter  )  
	{		
			  //(  ( CButton  * )GetDlgItem(  IDC_CHECK_useBgWall  )  )->SetCheck(  m_var.policy.ucbShowBgWall_starter  ?  1 : 0  );	
			  //
			  (  ( CButton  * )GetDlgItem(  IDC_CHECK_ucbManuallyConfCtrl  )  )->SetCheck(  m_var.policy.ucbConfCtrl_starter  ?  1 : 0  );

			  //
			  ((CButton*)GetDlgItem(IDC_CHECK_ucb2Streams))->SetCheck(m_var.ucb2Streams ? 1 : 0);


			  }	
	else  {
				//(  ( CButton  * )GetDlgItem(  IDC_CHECK_useBgWall  )  )->SetCheck(  m_var.policy.ucbShowBgWall_confMem  ?  1 : 0  );			    
	}

	//
	SetDlgItemText(  IDC_CHECK_ucbManuallyConfCtrl,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_confControl  )  );

	//
	lstrcpyn(tBuf, _T("严格限流"), mycountof(tBuf));
	SetDlgItemText(IDC_CHECK_ucb100k,  tBuf  );

	//
	if  (  m_var.uiObjType  !=  CONST_objType_imGrp  )  {
		//
		::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_usMaxSpeakers  ),  SW_HIDE  );
		::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_usMaxSpeakers  ),  SW_HIDE  );

		//
		::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_CHECK_ucbManuallyConfCtrl  ),  SW_HIDE  );
		::ShowWindow(::GetDlgItem(m_hWnd, IDC_CHECK_ucb2Streams), SW_HIDE);
	}

	//  2017/08/27
	if  (  m_var.uiCapType  !=  CONST_capType_av  )  {
		::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_CHECK_ucbManuallyConfCtrl  ),  SW_HIDE  );
		::ShowWindow(::GetDlgItem(m_hWnd, IDC_CHECK_ucb2Streams), SW_HIDE);
	}

	//
	GetWindowText(  m_var.title,  mycountof(  m_var.title  )  );
	m_var.timeoutInS  =  20;
	m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );
	//
	SetTimer(  1,  1000,  NULL  );

errLabel:
	//
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//  
void CDlgSelectAvCompressor::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int					iErr		=	-1;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	TCHAR			*	pRegVal		=	NULL;
	TCHAR				regValBuf[256]		=	_T( "" );
	//
	QY_REG				reg;
	TCHAR				tBuf[256]	=  _T(  ""  );
	unsigned int		uiCapType;



	//
	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	
	//
	//

	// 
	//m_var.level_conf = m_var.level;

	//
	//bool  b60 = false;
	CString str;
	GetDlgItemText(IDC_COMBO_fps, str);
	//if (!lstrcmpi(str, CONST_str_60fps))  b60 = true;
	int fps = _ttol(str);
	if (fps <= 0 || fps > 120)  fps = 30;
	qySetRegCfgT(reg.hKeyRoot0, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, _T(CONST_regValName_conf_usMaxFps_toShareBmp), _ltot(fps, tBuf, 10));
	


	//
	GetDlgItemText(IDC_EDIT_bitrate, str);
	int bitrate = _ttol(str);
	if (bitrate < 0)bitrate = 0;	
	qySetRegCfgT(reg.hKeyRoot0, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, _T(CONST_regValName_conf_bitrateInKbps_dl), _ltot(bitrate, tBuf, 10));
	//
	GetDlgItemText(IDC_EDIT_bitrate_ul, str);	   //IDC_EDIT_bitrate_ul
	bitrate = _ttol(str);
	if (bitrate < 0)bitrate = 0;
	qySetRegCfgT(reg.hKeyRoot0, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, _T(CONST_regValName_conf_bitrateInKbps_ul), _ltot(bitrate, tBuf, 10));


	
	//
	if  (  m_var.uiCapType  ==  CONST_capType_av  &&  m_var.uiSubCapType  ==  0  )  {
		//
		int  iCapUsage  =  m_var.b3D  ?  CONST_capUsage_3dConf  :  CONST_capUsage_conf;
		//
		getRegRootKey_qmc(  m_var.uiCapType,  m_var.uiSubCapType,  iCapUsage,  reg.rootKey,  mycountof(  reg.rootKey  )  );
		pRegVal  =  CONST_regValName_policyAvLevel_req;
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  m_var.level,  tBuf,  10  )  );		//  level_conf和原来的reply当一个用
	}
	getRegRootKey_qmc(  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	//
	pRegVal  =  CONST_regValName_policyAvLevel_req;
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  m_var.level,  tBuf,  10  )  );

	//
	if  (  m_var.ucbStarter  )  {
	int  conf_iFourcc  =  get_conf_iFourcc(  );
		switch  (  conf_iFourcc  )  {
				case  CONST_fourcc_vp80:
					  if  (  m_var.level  >=  CONST_policyAvLevel_720p  )  {
						  //  qyShowHint(  _T(  "vp8 can't support hd"  )  );
						  qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_vp8  )  );
						  goto  errLabel;
					  }
					  break;
				default:
						break;
		}
	}



	//
	bool  bChecked  =  FALSE;
	pRegVal  =  CONST_regValName_noPrompt_selAvCompressor;
	bChecked  =  (((  CButton  *  )GetDlgItem(  IDC_CHECK_noPrompt  ) )->GetCheck(  ) ==  BST_CHECKED  ) ?  TRUE :  FALSE;
	//
	bSetNoPrompt_selectAvCompressor(  m_var.uiCapType,  m_var.uiSubCapType,  bChecked  );



	//
	unsigned  short usTmp2_ucbConfCtrl  =  1;
	usTmp2_ucbConfCtrl  =  (  (  (  CButton  *  )GetDlgItem(  IDC_CHECK_ucbManuallyConfCtrl  )  )->GetCheck(  )  ==  BST_CHECKED  ) ;

	//
	if  (  m_var.uiObjType  !=  CONST_objType_imGrp  )  {
		usTmp2_ucbConfCtrl  =  0;
	}

	//
	unsigned  short  usTmp2_ucb2Streams = 0;
	usTmp2_ucb2Streams = (((CButton*)GetDlgItem(IDC_CHECK_ucb2Streams))->GetCheck() == BST_CHECKED);

	//
	unsigned  short  usTmp2_ucb100k = 0;
	usTmp2_ucb100k = (((CButton*)GetDlgItem(IDC_CHECK_ucb100k))->GetCheck() == BST_CHECKED);

	//
	unsigned  short  usTmp2_bLyra = 0;
	usTmp2_bLyra= (((CButton*)GetDlgItem(IDC_CHECK_bLyra))->GetCheck() == BST_CHECKED);


	//  2017/07/19
#if 0
	if  (  usTmp2_ucbConfCtrl  )  {
		if  (  !bNoPrompt_selectConfCtrl(  m_var.uiCapType,  m_var.uiSubCapType  )  )  {
			PARAM_qyMessengeBox  param  =  {0};
			param.bShow_noPrompt  =  1;
			if  (  ID_qyOk  !=  qyMessageBox_custom(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectedConfManage  ),  _T(  ""  ),  MB_OKCANCEL,  10000,  NULL,  &param  )  )  {
				return;
			}
			//
			bSetNoPrompt_selectConfCtrl(  m_var.uiCapType,  m_var.uiSubCapType,  param.bCheck_noPropmt  );
		}
	}
#endif

	//
	if  (   m_var.ucbStarter  )  {
		//
		//  2017/06/25
		if  (  m_var.policy.ucbConfCtrl_starter  !=  usTmp2_ucbConfCtrl  )  {
			m_var.policy.ucbConfCtrl_starter  =  usTmp2_ucbConfCtrl;
			pRegVal  =  CONST_regValName_ucbConfCtrl_starter;
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  usTmp2_ucbConfCtrl   );
			qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  tBuf  );  
		}
		if (m_var.ucb2Streams != usTmp2_ucb2Streams) {
			m_var.ucb2Streams = usTmp2_ucb2Streams;
			pRegVal = CONST_regValName_ucb2Streams;
			_sntprintf(tBuf, mycountof(tBuf), _T("%d"), usTmp2_ucb2Streams);
			qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, tBuf);
		}
		//
		pRegVal = CONST_regValName_ucb100k;
		_sntprintf(tBuf, mycountof(tBuf), _T("%d"), usTmp2_ucb100k);
		qySetRegCfgT(reg.hKeyRoot0, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, pRegVal, tBuf);

		//
		pRegVal = CONST_regValName_bLyra;
		_sntprintf(tBuf, mycountof(tBuf), _T("%d"), usTmp2_bLyra);
		qySetRegCfgT(reg.hKeyRoot0, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, pRegVal, tBuf);


		//		
		}
	else  {
	}



	iErr  =  0;


errLabel:

	if  (  iErr  )  {
		return;
	}


	CDialogEx::OnOK();
}


BOOL CDlgSelectAvCompressor::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	UINT  nID  =  LOWORD(  wParam  );
	HWND  hWndCtrl  =  (  HWND  )lParam;
	int  nCode  =  HIWORD(  wParam  );

	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );

	QY_IDCITEM  *  pItem;
	pItem  =  getIdcLevelTable(  m_var.uiCapType,  m_var.uiSubCapType,  FALSE  );
	for  (  ;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->idc  ==  nID  )  {
			 m_var.level  =  pItem->idcType;
			 break;
		 }
	}

	//
	bShowInfo(  );
	
	//
	return CDialogEx::OnCommand(wParam, lParam);
}


void CDlgSelectAvCompressor::OnBnClickedButtoncfg()
{
	// TODO: Add your control notification handler code here

	//  unsigned int			uiCapType  =  CONST_capType_av;
	int						idc;

	idc  =  IDC_STATIC_avCompressor;


	//  
	AV_COMPRESSOR_CFG  compressor  =  {0};
	getCompressorCfg(  NULL,  m_var.uiCapType,  m_var.uiSubCapType,  get_iCapUsage_toDisplay(  ),  get_level_toDisplay(  ),  &compressor  );

	if  (  showDlgVideoCompressors(  m_hWnd,  &compressor,  m_var.uiCapType,  m_var.uiSubCapType,  get_iCapUsage_toDisplay(  ),  get_level_toDisplay(  ),  &compressor  )  ==  IDOK  )  {
	
		//		
		SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &compressor  )  );
			
		
	}

}


void CDlgSelectAvCompressor::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
#ifdef  __DEBUG__
		traceLog(  _T(  "dlgSelectAvCompressor::Timer"  )  );
#endif

		// TODO: Add your message handler code here and/or call default		
		if  (  GetTickCount(  )  -  m_var.dwTickCnt_lastMouseMove  >  m_var.timeoutInS  *  1000  )  {
			  #ifdef  __DEBUG__
					  traceLog(  _T(  "CDlgSelectAvCompressor: OnTimer: before close"  )  );
			  #endif
			  ::PostMessage(  m_hWnd,  WM_CLOSE,  0,  0  );
			  #ifdef  __DEBUG__
					  traceLog(  _T(  "CDlgSelectAvCompressor: OnTimer: after close"  )  );
			  #endif
			  return;		  
		}

		//
		TCHAR	tBuf[256];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ... Auto canceled in %d seconds."  ),  m_var.title,  m_var.timeoutInS  -  (  GetTickCount(  )  -  m_var.dwTickCnt_lastMouseMove  )  /  1000  );
		SetWindowText(  tBuf  );


	CDialogEx::OnTimer(nIDEvent);
}


BOOL CDlgSelectAvCompressor::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	switch  (  pMsg->message  )  {
			case  WM_MOUSEMOVE:
			case  WM_LBUTTONDOWN:
			case  WM_RBUTTONDOWN:  {
				  POINT	point;	
				  long  lParam  =  pMsg->lParam;
				  point.x = GET_X_LPARAM(lParam); 
				  point.y = GET_Y_LPARAM(lParam);
				  //
				  ::MapWindowPoints(  pMsg->hwnd,  NULL,  &point,  1  );

				  //						  				  
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  if  (  m_var.param_mousemove.xPos_screen  ==  point.x  &&  m_var.param_mousemove.yPos_screen  ==  point.y  )  break;

				  m_var.param_mousemove.xPos_screen  =  point.x;
				  m_var.param_mousemove.yPos_screen  =  point.y;
						  
				  //  只有鼠标位置移动时，才能认为是鼠标真的移动了
				  m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );	

#ifdef  __DEBUG__
				  //traceLog(  _T(  "dlgSelectAvCompressor: mouse move"  )  );
#endif
				  }

				  break;
			default:
					break;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgSelectAvCompressor::OnCbnSelchangeCombocategory()
{
	// TODO: Add your control notification handler code here
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	QY_IDCITEM  *  pItem;
	
	//
#if  10
	int  idc  =  IDC_COMBO_category;
	CString	str;
	GetDlgItemText(  idc,  str  );
	pItem  =  CONST_selectAvCompressorCategoryTable;
	for  (  ;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  !_tcsicmp(  str,  pItem->des  )  )  break;
	}
	if  (  pItem->idc  ==  -1  )  return;
	//
	m_var.uiCapType  =  pItem->idc;
	m_var.uiSubCapType  =  pItem->idcType;
	//
	m_var.level  =  getPolicyAvLevel(  pQyMc,  m_var.uiCapType,  m_var.uiSubCapType,  0  );
	//
	bShowInfo(  );
#endif

	return;
}


void CDlgSelectAvCompressor::OnBnClickedCheckusebgwall()
{
	// TODO: Add your control notification handler code here
	if  (  (  (  CButton *  )GetDlgItem(  IDC_CHECK_useBgWall  )  )->GetCheck()  ==  BST_UNCHECKED  )  
	{
		GetDlgItem(  IDC_EDIT_rows  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_rows  )->Invalidate(  );
		GetDlgItem(  IDC_EDIT_cols  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_cols  )->Invalidate(  );
		GetDlgItem(  IDC_EDIT_pollingInterval  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_pollingInterval  )->Invalidate(  );
	}
	else  
	{
		GetDlgItem(  IDC_EDIT_rows  )->EnableWindow(  TRUE  );
		GetDlgItem(  IDC_EDIT_rows  )->Invalidate(  );
		GetDlgItem(  IDC_EDIT_cols  )->EnableWindow(  TRUE  );
		GetDlgItem(  IDC_EDIT_cols  )->Invalidate(  );
		GetDlgItem(  IDC_EDIT_pollingInterval  )->EnableWindow(  TRUE  );
		GetDlgItem(  IDC_EDIT_pollingInterval  )->Invalidate(  );
	}
}


//
void CDlgSelectAvCompressor::OnBnClickedChecknoprompt()
{
	// TODO: Add your control notification handler code here
}




void CDlgSelectAvCompressor::OnBnClickedCheckucbmanuallyconfCtrl()
{
	// TODO: Add your control notification handler code here


}


void CDlgSelectAvCompressor::OnBnClickedCheck2streams()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgSelectAvCompressor::OnCbnSelchangeCombovideocodec()
{
	// TODO: Add your control notification handler code here

	//
	CCtxQyMc  *  pQyMc  =  QY_GET_GBUF();

	TCHAR  tBuf[128];
	
	//
	int  idc;
	idc  =  IDC_COMBO_videoCodec;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );
	char  buf[128];
	myTChar2Utf8(  tBuf,  buf,  sizeof(  buf  )  );
	qySetRegCfgT(  HKEY_CURRENT_USER,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  _T(  CONST_regValName_conf_fourcc  ),  tBuf  );
	
	//
	return;
}


void CDlgSelectAvCompressor::OnEnChangeEditusmaxspeakers()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.


	// TODO:  Add your control notification handler code here
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	TCHAR  tBuf[128];
	
	//
	int  idc;
	idc  =  IDC_EDIT_usMaxSpeakers;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );
	int  iVal = _ttol(tBuf  );
	if  (  iVal  >0  &&  iVal  <=  MAX_real_speakers_taskAv_h264  )  {
		qySetRegCfgT(  HKEY_CURRENT_USER,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  _T(  CONST_regValName_conf_usMaxSpeakers  ),  tBuf  );
	}




	return;
}






void CDlgSelectAvCompressor::OnBnClickedCheckblyra()
{
	// TODO: 在此添加控件通知处理程序代码
	int  ii = 9;
}

void CDlgSelectAvCompressor::OnBnClickedButton144p()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgSelectAvCompressor::OnBnClickedButton240p()
{
	// TODO: 在此添加控件通知处理程序代码
}
