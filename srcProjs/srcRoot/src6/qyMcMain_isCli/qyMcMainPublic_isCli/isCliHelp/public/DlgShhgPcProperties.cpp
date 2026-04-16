// DlgShhgPcProperties.cpp : implementation file
//

#include	<tchar.h>
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"
#include	"myresource.h"
#include	"DlgShhgPcProperties.h"
#include	"myDb.h"
#include	"ctxQmc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgShhgPcProperties dialog


CDlgShhgPcProperties::CDlgShhgPcProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShhgPcProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShhgPcProperties)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	memset(  &m_var,  0,  sizeof(  m_var  )  );

}


void CDlgShhgPcProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShhgPcProperties)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShhgPcProperties, CDialog)
	//{{AFX_MSG_MAP(CDlgShhgPcProperties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgShhgPcProperties message handlers

 BOOL  CDlgShhgPcProperties::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  int  iObjType,  char  *  mac  )
{
	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	if  (  !bMacValid(  mac  )  )  return  FALSE;

	m_var.pObjDb  =  pObjDb;
	m_var.iObjType  =  iObjType;
	safeStrnCpy(  mac,  m_var.u.pc.mac,  sizeof(  m_var.u.pc.mac  )  );

	return  TRUE;

}



/*
 QY_IDCITEM	 CONST_pcPropertiesTable0[]  =
{
	{	IDC_pc0_zongBu,				CONST_qyIdcType_static,		_T(  "总部:"  ),				0,	0,	NULL,	64,	  24,  31,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zb,		4,		},
 	{	IDC_pc1,					CONST_qyIdcType_static,	 NULL,					0,	0,	NULL,	64,	  72,  31,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zb,		4,		},
	{	IDC_pc2_benBu,				CONST_qyIdcType_static,		_T(  "本部:"  ),				0,	0,	NULL,	64,	  147, 31,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_bb,		3,		},
 	{	IDC_pc3,					CONST_qyIdcType_static,	 NULL,					0,	0,	NULL,	64,	  201, 31,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_bb,		3,		},
	{	IDC_pc4_danWei,				CONST_qyIdcType_static,		_T(  "单位:"  ),				0,	0,	NULL,	64,	  24,  42,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_dw,		2,		},
	{	IDC_pc5,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,	  71,  42,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_dw,		2,		},
	{	IDC_pc6_qiTaDanWei,			CONST_qyIdcType_static, 	_T(  "其它单位:"  ),			0,	0,	NULL,	64,   147, 42,  48,  9,		CONST_qyIdcFlgHide,		NULL,	NULL,	0,	CONST_fieldId_qtdw,		2,		},
	{   IDC_pc7,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   201, 42,  72,  9,		CONST_qyIdcFlgHide,		NULL,	NULL,	0,	CONST_fieldId_qtdw,		2,		},
	{	IDC_pc8_buMen,				CONST_qyIdcType_static, 	_T(  "部门:"  ),				0,	0,	NULL,	64,   24,  53,  38,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_bm,		1,		},
	{   IDC_pc9,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   71,  53,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_bm,		1,		},
	{	IDC_pc10_shiYongRen,		CONST_qyIdcType_static, 	_T(  "使用人:"  ),				0,	0,	NULL,	64,   147, 53,  48,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_syr,		0,		},
	{   IDC_pc11,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,	  201, 53,  72,	 9, 	0,						NULL,	NULL,	0,	CONST_fieldId_syr,		0,		},
	{	IDC_pc12_jiQiLeiXing,		CONST_qyIdcType_static, 	_T(  "机器类型:"  ),			0,	0,	NULL,	64,   24,  64,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_jqlx,		0,		},
	{   IDC_pc13,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   71,  64,	72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_jqlx,		0,		},
	{	IDC_pc14_ziChanBianHao,		CONST_qyIdcType_static, 	_T(  "资产编号:"  ),			0,	0,	NULL,	64,   147, 64,  48,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zcbh0,	0,		},
	{   IDC_pc15,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   201, 64,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zcbh0,	0,		},
	{	IDC_pc16_zhuYaoYongTu,		CONST_qyIdcType_static, 	_T(  "主要用途:"  ),			0,	0,	NULL,	64,   24,  75,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zyyt,		0,		},
	{   IDC_pc17,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   71,  75,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zyyt,		0,		},
	{	IDC_pc18_lianXiDianHua,		CONST_qyIdcType_static, 	_T(  "联系电话:"  ),			0,	0,	NULL,	64,   147, 75,  48,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_lxdh,		0,		},
	{   IDC_pc19,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   201, 75,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_lxdh,		0,		},
	{	IDC_pc20_shiYongDiDian,		CONST_qyIdcType_static, 	_T(  "使用地点:"  ),			0,	0,	NULL,	64,   24,  86,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_sydd,		0,		},
	{   IDC_pc21,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   71,  86,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_sydd,		0,		},
	{	IDC_pc22_shiYongDiDian,		CONST_qyIdcType_static, 	_T(  "使用地点:"  ),			0,	0,	NULL,	64,   147, 86,  48,  9,		CONST_qyIdcFlgHide,		NULL,	NULL,	0,	CONST_fieldId_null,		0,		},
	{   IDC_pc23,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   201, 86,  72,  9,		CONST_qyIdcFlgHide,		NULL,	NULL,	0,	CONST_fieldId_null,		0,		},
	{	IDC_pc24_ziChanBianHao1,	CONST_qyIdcType_static, 	_T(  "资产编号1:"  ),			0,	0,	NULL,	64,   24,  97,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zcbh1,	1,		},
	{   IDC_pc25,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   71,  97,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zcbh1,	1,		},
	{	IDC_pc26_ziChanShuoMing1,	CONST_qyIdcType_static, 	_T(  "资产说明1:"  ),			0,	0,	NULL,	64,   147, 97,  48,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zcsm1,	1,		},
	{   IDC_pc27,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   201, 97,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zcsm1,	1,		},
	{	IDC_pc28_ziChanBianHao2,	CONST_qyIdcType_static, 	_T(  "资产编号2:"  ),			0,	0,	NULL,	64,   24,  109,  40,  9,	0,						NULL,	NULL,	0,	CONST_fieldId_zcbh2,	2,		},
	{   IDC_pc29,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   71,  109,  72,  9,	0,						NULL,	NULL,	0,	CONST_fieldId_zcbh2,	2,		},
	{	IDC_pc30_ziChanShuoMing2,	CONST_qyIdcType_static, 	_T(  "资产说明2:"  ),			0,	0,	NULL,	64,   147, 109,  48,  9,	0,						NULL,	NULL,	0,	CONST_fieldId_zcsm2,	2,		},
	{   IDC_pc31,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   201, 109,  72,  9,	0,						NULL,	NULL,	0,	CONST_fieldId_zcsm2,	2,		},
	{	-1,																																																							},
};
 */


 
 void  qnmSizePcPropertiesControls(  QNM_CUSRES_INFO  *  pCusRes,  HWND  hDlg,  QNM_REG_INFO  *  pRegInfo  )
{
	HDWP			hdwp; 
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	HWND			hWnd,  prevhWnd  =  NULL;
	int				cnt			=	0;
	QY_IDCITEM	*	pItem		=	NULL;
	QY_IDCITEM  *	tmppItem	=	NULL;
	QY_IDCITEM	*	pTable0		=	(  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_pcPropertiesTable0  );
	QY_IDCITEM	*	pCurTable	=	(  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_pcPropertiesTable0  );
	int				index		=	0;
	if  (  !pCurTable  )  return;

	for  (  pItem  =  pCurTable;  pItem->idc  !=  -1;  pItem  ++  )  cnt  ++  ;
	
	// size the tree control accordingly
	hdwp  =  BeginDeferWindowPos(  cnt  ); 
	
	for  (  pItem  =  pCurTable;  pItem->idc  !=  -1;  pItem  ++  )  {

		 hWnd = ::GetDlgItem(  hDlg,  pItem->idc  );             
		 if  (  !hWnd  )  continue;

		 tmppItem  =  qyGetIdcItemByIdc(  pTable0,  pItem->idc  );
		 if  (  tmppItem  )  tmppItem->flg  =  pItem->flg;
			 
		 ::DeferWindowPos(  hdwp, 
							hWnd,  prevhWnd  ?  prevhWnd  :  HWND_TOP, 
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->x  ),  
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->y  ),  
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->w  ),  
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->h  ),  
							(  pItem->flg  &  CONST_qyIdcFlgHide  )  ?  SWP_HIDEWINDOW  :  SWP_SHOWWINDOW  );  
		 prevhWnd  =  hWnd;
		 if  (  pItem->idcType  ==  CONST_qyIdcType_static  )  {	
			 if  (  pItem->des  )  SetWindowText(  hWnd,  CString(  pItem->des  )  );
			 else  {
				   if  (  (  index  =  getRegIndexByFieldId(  pItem->uiFieldId  )  )  <  0  )  continue;
				   if  (  pRegInfo->uiFieldIds[index]  ==  CONST_fieldId_jqlx  )  SetWindowText(  hWnd,  CString(  qyGetDesByType1(  getResTable(  0,  pCusRes,  CONST_resId_jqlxTable  ),  atol(  pRegInfo->u.cols[index]  )  )  )  );						
				   else  SetWindowText(  hWnd,  CString(  (  TCHAR  *  )pRegInfo->u.cols[index]  )  );
			 }			 
		 }		 
	}
		
	EndDeferWindowPos(  hdwp  );

	return;

}

 void  qisSizePcPropertiesControls(  QNM_CUSRES_INFO  *  pCusRes,  HWND  hDlg,  QY_MESSENGER_REGINFO  *  pRegInfo  )
{
	HDWP			hdwp; 
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	HWND			hWnd,  prevhWnd  =  NULL;
	int				cnt			=	0;
	QY_IDCITEM	*	pItem		=	NULL;
	QY_IDCITEM  *	tmppItem	=	NULL;
	QY_IDCITEM	*	pTable0		=	(  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_pcPropertiesTable0  );
	QY_IDCITEM	*	pCurTable	=	(  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_pcPropertiesTable0  );
	int				index		=	0;
	if  (  !pCurTable  )  return;

	for  (  pItem  =  pCurTable;  pItem->idc  !=  -1;  pItem  ++  )  cnt  ++  ;
	
	// size the tree control accordingly
	hdwp  =  BeginDeferWindowPos(  cnt  ); 
	
	for  (  pItem  =  pCurTable;  pItem->idc  !=  -1;  pItem  ++  )  {

		 hWnd = ::GetDlgItem(  hDlg,  pItem->idc  );             
		 if  (  !hWnd  )  continue;

		 tmppItem  =  qyGetIdcItemByIdc(  pTable0,  pItem->idc  );
		 if  (  tmppItem  )  tmppItem->flg  =  pItem->flg;
			 
		 ::DeferWindowPos(  hdwp, 
							hWnd,  prevhWnd  ?  prevhWnd  :  HWND_TOP, 
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->x  ),  
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->y  ),  
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->w  ),  
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->h  ),  
							(  pItem->flg  &  CONST_qyIdcFlgHide  )  ?  SWP_HIDEWINDOW  :  SWP_SHOWWINDOW  );  
		 prevhWnd  =  hWnd;
		 if  (  pItem->idcType  ==  CONST_qyIdcType_static  )  {	
			 if  (  pItem->des  )  SetWindowText(  hWnd,  CString(  pItem->des  )  );
			 else  {
#if  0
				   if  (  (  index  =  getRegIndexByFieldId(  pItem->uiFieldId  )  )  <  0  )  continue;
				   if  (  pRegInfo->uiFieldIds[index]  ==  CONST_fieldId_jqlx  )  SetWindowText(  hWnd,  CString(  qyGetDesByType1(  getResTable(  0,  pCusRes,  CONST_resId_jqlxTable  ),  _ttol(  pRegInfo->u.cols[index]  )  )  )  );						
				   else  SetWindowText(  hWnd,  CString(  (  TCHAR  *  )pRegInfo->u.cols[index]  )  );
#endif				//  2017/08/29
				   int  i;
				   for  (  i  =  0;  i  <  mycountof(  pRegInfo->uiFieldIds  );  i  ++  )  {
					   if  (  pItem->uiFieldId  ==  pRegInfo->uiFieldIds[i]  )  {
						   if  (  pItem->uiFieldId  ==  CONST_fieldId_jqlx  )  SetWindowText(  hWnd,  CString(  qyGetDesByType1(  getResTable(  0,  pCusRes,  CONST_resId_jqlxTable  ),  _ttol(  pRegInfo->u.cols[index]  )  )  )  );						
						   else  SetWindowText(  hWnd,  pRegInfo->u.cols[i]  );
						   break;
					   }
				   }
			 }			 
		 }		 
	}
		
	EndDeferWindowPos(  hdwp  );

	return;

}




 int  setPcPropertiesLayout(  QNM_CUSTOM_COMM  *  pCustom,  QY_IDCITEM  *  pTable0  )
{
	if  (  !pCustom  )  return  -1;
	if  (  !pTable0  )  return  -1;

	 //
	 QY_IDCITEM	*	pIdcItem	=	NULL;
	 for  (  pIdcItem  =  pTable0;  pIdcItem->idc  !=  -1;  pIdcItem  ++  )  {
		  if  (  bFieldLikeDw(  pIdcItem->uiFieldId  )  )  {
			  if  (  pIdcItem->ucLevel  <  pCustom->nDwLevels  )  pIdcItem->flg  &=  ~CONST_qyIdcFlgHide;
			  else  pIdcItem->flg  |=  CONST_qyIdcFlgHide;
		  }
		  if  (  bFieldLikeZcbh(  pIdcItem->uiFieldId,  0  )  )  {
			  if  (  pIdcItem->ucLevel  <  pCustom->nZcbhs  )  pIdcItem->flg  &=  ~CONST_qyIdcFlgHide;
			  else  pIdcItem->flg  |=  CONST_qyIdcFlgHide;
		  }
	 }
	 return  0;
}


BOOL CDlgShhgPcProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int				iErr		=		-1;	
	QY_MC		*	pQyMc		=		QY_GET_GBUF(  );
	char			buf[256];
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  goto  errLabel;

	setPcPropertiesLayout(  &pQyMc->cfg.custom,  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_pcPropertiesTable0  )  );


				   if  (  !bMacValid(  m_var.u.pc.mac  )  )  {
					   traceLogA(  "CDlgShhgPcProperties 的输入有错误, 将调用EndDialog"  );
					   goto  errLabel;
				   }
	
				   if  (  !g_dbFuncs.pf_bGetPcInfoByMac(  m_var.pObjDb->pDb,  (  char  *  )m_var.u.pc.mac,  FALSE,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &m_var.u.pc.info,  &m_var.u.pc.regInfo  )  )  {
					   memset(  &m_var.u.pc.info,  0,  sizeof(  m_var.u.pc.info  )  );
					   memset(  &m_var.u.pc.regInfo,  0,  sizeof(  m_var.u.pc.regInfo  )  );
				   }
		
				   qnmSizePcPropertiesControls(  &pQyMc->cusRes,  this->m_hWnd,  &m_var.u.pc.regInfo  );
		
				   SetDlgItemText(  IDC_pcName,  CString(  m_var.u.pc.info.pcName  )  );
				   SetDlgItemText(  IDC_IP,  CString(  m_var.u.pc.info.ip  )  );
				   SetDlgItemText(  IDC_mac0,  CString(  m_var.u.pc.info.macs[0]  )  );	SetDlgItemText(  IDC_ip0,  CString(  bulIpValid(  inet_addr(  m_var.u.pc.info.ips[0]  )  )  ?  m_var.u.pc.info.ips[0]  :  ""  )  );
				   SetDlgItemText(  IDC_mac1,  CString(  m_var.u.pc.info.macs[1]  )  );	SetDlgItemText(  IDC_ip1,  CString(  bulIpValid(  inet_addr(  m_var.u.pc.info.ips[1]  )  )  ?  m_var.u.pc.info.ips[1]  :  ""  )  );
				   SetDlgItemText(  IDC_mac2,  CString(  m_var.u.pc.info.macs[2]  )  );	SetDlgItemText(  IDC_ip2,  CString(  bulIpValid(  inet_addr(  m_var.u.pc.info.ips[2]  )  )  ?  m_var.u.pc.info.ips[2]  :  ""  )  );
				   SetDlgItemText(  IDC_osName,  CString(  m_var.u.pc.info.osName  )  );
				   SetDlgItemText(  IDC_servicePack,  CString(  m_var.u.pc.info.servicePack  )  );
				   SetDlgItemText(  IDC_curUsrName,  CString(  m_var.u.pc.info.curUsrName  )  );
				   SetDlgItemText(  IDC_proxyServer,  CString(  m_var.u.pc.info.proxyServer  )  );
				   if  (  !qyDisplayTime(  m_var.u.pc.info.startTime,  buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   SetDlgItemText(  IDC_STARTTIME,  CString(  buf  )  );
				   if  (  !qyDisplayTime(  m_var.u.pc.info.lastCommTime,  buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   SetDlgItemText(  IDC_lastCommTime,  CString(  buf  )  );
				   if  (  !qyDisplayTime(  m_var.u.pc.regInfo.auditTime,  buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   SetDlgItemText(  IDC_auditTime,  CString(  buf  )  );
				   if  (  !qyDisplayTime(  m_var.u.pc.regInfo.regTime,  buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   SetDlgItemText(  IDC_regTime,  CString(  buf  )  );
				   SetDlgItemText(  IDC_qwmVer,  CString(  m_var.u.pc.info.qwmVer  )  );
  
				   if  (  qyGetSystemId(  )  ==  CONST_qySystemId_nms  )  {
					   GetDlgItem(  IDC_STATIC_startTime  )->ShowWindow(  SW_HIDE  );
					   GetDlgItem(  IDC_STARTTIME  )->ShowWindow(  SW_HIDE  );
					   GetDlgItem(  IDC_lastCommTime  )->ShowWindow(  SW_HIDE  );
					   GetDlgItem(  IDC_STATIC_lastCommTime  )->ShowWindow(  SW_HIDE  );
				   }

	


	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		EndDialog(  FALSE  );
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


