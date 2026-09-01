
#include	"stdafx.h"
#include	<afxcview.h>
#include	"resource.h"
#include	"qyVDevProc.h"
 
 //  ÔÚqyMessenger°²×°Ä¿Â¼Àï£¬Ôö¼ÓÒ»¸öcfgÄ¿Â¼ºÍpolicy.cfgµÄÎÄ¼þ¡£¿ÉÒÔÊÖ¹¤±à¼­¡£
 //  ³õÊ¼»¯Ê±£¬¶Á´ËÎÄ¼þ¡£¸ù¾ÝÒªÇó×°ÔØDLL,²¢Ñ°ÕÒºÍÖ´ÐÐÏÂÃæµÄ±ê×¼½Ó¿Ú¡£Í³Ò»ÔËÐÐ£¬Í³Ò»´¦Àí¡£

 CQyVDevComs	gVDev;
 CQyVDevComs  *	pVDev  =  &gVDev;

 
 CQyVDevComs::CQyVDevComs(  )
 {
	 memset(  &this->m_var,  0,  sizeof(  this->m_var  )  );
 }

 CQyVDevComs::~CQyVDevComs(  )
 {
 }



 extern  "C"  __declspec(  dllexport  )  int  qyVDev_getPtrProperty(  void  *  p0,  void  *  propertyIdParam,  void  *  p2  )
{
	 int  propertyId  =  (  int  )propertyIdParam;

	 switch  (  propertyId  )  {
			 case  CONST_qyPropertyId_vDev:
				   return  (  int  )&gVDev.m_var.common;
				   break;
			 default:
					 break;
	 }
	 return  NULL;
}


 
 //È¡Éè±¸×´Ì¬
  extern  "C"  __declspec( dllexport )  int  qyVDev_getInfo(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 return  0;
}



 //È¡Éè±¸ÅäÖÃ
  extern  "C"  __declspec( dllexport )  int  qyVDev_getCfg(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int  iErr  =  -1;

	 traceLogA(  "getQyVDevCfg enters"  );

	 pVDev->m_var.common.uiType  =  0;		//  Õâ¸öÀàÐÍ²»ÖªµÀÓ¦¸Ã¶¨Òå³ÉÊ²Ã´ºÃ¡£2008/02/08
	 //

	 _sntprintf(  pVDev->m_var.cfg.mgrQ.name,  mycountof(  pVDev->m_var.cfg.mgrQ.name  ),  _T(  "mgrQ_vDevComs"  )  );
	 _sntprintf(  pVDev->m_var.cfg.mgrQ.mutexName_prefix,  mycountof(  pVDev->m_var.cfg.mgrQ.mutexName_prefix  ),  _T(  "mgrQ_vDevComs"  )  );
	 pVDev->m_var.cfg.mgrQ.uiMaxCnt_semaTrigger  =  CONST_uiMaxCnt_sema_mgrQ_vDevComs;
	 pVDev->m_var.cfg.mgrQ.uiMaxQNodes  =  CONST_uiMaxQNodes_mgrQ_vDevComs;
	 //
	 _sntprintf(  pVDev->m_var.cfg.dataQ.name,  mycountof(  pVDev->m_var.cfg.dataQ.name  ),  _T(  "dataQ_vDevComs"  )  );
	 _sntprintf(  pVDev->m_var.cfg.dataQ.mutexName_prefix,  mycountof(  pVDev->m_var.cfg.dataQ.mutexName_prefix  ),  _T(  "dataQ_vDevComs"  )  );
	 pVDev->m_var.cfg.dataQ.uiMaxQNodes  =  CONST_uiMaxQNodes_dataQ_vDevComs;
 
	 //

	 pVDev->m_var.cfg.uiMaxComs  =  CONST_maxComs;
	 //
	 pVDev->m_var.cfg.ucbAutoDel  =  TRUE;
	 #ifdef  __DEBUG__
			   //  pVDev->m_var.cfg.ucbAutoDel  =  FALSE;			 
	 #endif
	 //  pVDev->m_var.common.bDebug  =  TRUE;

	 //
	 if  (  !pVDev->m_var.cfg.ucbAutoDel  )  traceLogA(  "qyVDev_getCfg: ²»×Ô¶¯É¾³ý¶ÌÏûÏ¢£¬ÔÚreleaseÊ±£¬Ó¦¸Ã°ÑucbAutoDelÉè³ÉTRUE"  );
	 if  (  pVDev->m_var.cfg.uiMaxComs  >  CONST_maxComs  )  {
		 traceLogA(  "ucMaxComs can't be > CONST_maxComs, ÒòÎªCONST_maxComsÊÇÒ»Ð©Êý×éµÄÈÝÁ¿"  );  goto  errLabel;
	 }

	 iErr  =  0;

errLabel:
	 traceLogA(  "getQyVDevCfg leaves"  );

	 return  iErr;
}


 QY_COLUMNINFO  CONST_comColumns[]  =
{
	{		CONST_qyColumnDisplayType_long,	_T(  "ID"  ),				SQL_CHAR,	LVCFMT_LEFT,	0,			1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "Name"  ),				SQL_CHAR,	LVCFMT_LEFT,	60,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "Model"  ),				SQL_CHAR,	LVCFMT_LEFT,	200,		1,	},
	//  {		CONST_qyColumnDisplayType_str,	_T(  "ºÅÂë"  ),			SQL_CHAR,	LVCFMT_LEFT,	120,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "Service center number"  ),		SQL_CHAR,	LVCFMT_LEFT,	120,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "Statue"  ),				SQL_CHAR,	LVCFMT_LEFT,	100,			1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "Sm manager"  ),		SQL_CHAR,	LVCFMT_LEFT,	80,			1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "Alias"  ),				SQL_CHAR,	LVCFMT_LEFT,	120,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "Last refresh time"  ),		SQL_CHAR,	LVCFMT_LEFT,	120,		1,	},
	{		-1,								_T(  ""  ),					SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
};


 BOOL  bDisplayMcViewContent_coms(  CListView  * pMcView,  void  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 int								i;
	 char								buf[255  +  1];
	 char								buf1[255  +  1];
	 TCHAR								tBuf[256];
	 int								cnt						=			0;
	 int								index;
	 CComPort						*	pPort					=			NULL;
	 BOOL								bOnlyNetSm				=			FALSE;
	 QY_GUI_OPEN_vDev				*	pOpen					=			pVDev->m_var.common.pGuiOpen;


	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pSel->docName  );
	 if  (  pVDev->m_var.defaultSmPolicy.tLastModifiedTime  )  {
		 if  (  pVDev->m_var.defaultSmPolicy.ucbDefaultSmServer  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s - 缺省发送服务器"  ),  tBuf  );
		 if  (  pVDev->m_var.defaultSmPolicy.idInfo_contact.ui64Id  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s - 缺省接收管理员为%I64u"  ),  tBuf,  pVDev->m_var.defaultSmPolicy.idInfo_contact.ui64Id  );
	 }
	 //	
	 if  (  !pOpen->pf_bGetLongProperty(  0,  (  void  *  )CONST_qyPropertyId_ucbOnlyNetSm,  &bOnlyNetSm  )  )  bOnlyNetSm  =  FALSE;
	 if  (  bOnlyNetSm  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s - 禁止本地发送短信"  ),  tBuf  );
	 //
	 pMcView->GetDocument(  )->SetTitle(  tBuf  );

	 //
	 pVDev->m_var.common.pGuiOpen->pf_qyMcView_delAllColumns(  pMcView,  0,  0  );
	 if  (  !pVDev->m_var.common.pGuiOpen->pf_qyMcView_bAddColumns(  pMcView,  CONST_comColumns,  0  )  )  goto  errLabel;
	 
	 ListCtrl.DeleteAllItems(  );
	 
	 for  (  i  =  0;  i  <  CONST_maxComs;  i  ++  )  {
		  
		  pPort  =  &pVDev->m_var.pPorts[i];

		  if  (  !pVDev->m_var.pPorts[i].m_var.ucbComExists  )  continue;

		  index  =  0;	
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  i  );
		  ListCtrl.InsertItem(  cnt,  tBuf,  0  );	
		  index  ++  ;
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "com%d"  ),  i  +  1  );
		  ListCtrl.SetItemText(  cnt,  index,  tBuf  );
		  index  ++  ;
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  CString(  pVDev->m_var.pPorts[i].m_var.modelBuf  ).GetBuffer(  0  )  );
		  ListCtrl.SetItemText(  cnt,  index,  tBuf  );
		  //
		  //  index  ++  , ºÅÂë
		  //
		  index  ++  ;
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  CString(  pVDev->m_var.pPorts[i].m_var.smscBuf  ).GetBuffer(  0  )  );
		  ListCtrl.SetItemText(  cnt,  index,  tBuf  );
		  //
		  index  ++  ;	//  ×´Ì¬
		  if  (  !pPort->m_var.ucbStarted  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  _T(  "Not started"  )  );
		  else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  _T(  "OK"  )  );
		  ListCtrl.SetItemText(  cnt,  index,  tBuf  );

		  //
		  index  ++  ;
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pPort->m_var.smPolicy.idInfo_contact.ui64Id  );
		  ListCtrl.SetItemText(  cnt,  index,  tBuf  );
		  index  ++  ;
		  ListCtrl.SetItemText(  cnt,  index,  pPort->m_var.smPolicy.cusName  );
		  index  ++  ;
		  buf[0]  =  0;  buf1[0]  =  0;
		  getTimeStr(  pPort->m_var.smPolicy.tLastModifiedTime,  buf,  mycountof(  buf  )  );  qyDisplayTime(  buf,  buf1,  mycountof(  buf1  )  );
		  ListCtrl.SetItemText(  cnt,  index,  CString(  buf1  )  );

		  cnt  ++  ;
		  
	 }
	 

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


 //  Õâ¸öÏß³ÌÓÐÖúÓÚ½«test¶Ô»°¿òºÍÆäËû¶Ô»°²Ù×÷²¢ÐÐ½øÐÐ
 extern "C" DWORD WINAPI threadProc_dlg_vDevComs( LPVOID lpParameter )
{
	 HWND	hParent  =  (  HWND  )lpParameter;

	 DialogBox(  pVDev->m_var.common.hModule, (LPCTSTR)IDD_qyTest,  hParent, (DLGPROC)dlgProc_qyTest);			


	 return  0;
}



 int  procLvEventFunc_vDevComs(  QY_EVENTINFO  *  pEventInfo,  void  *  pObjDbParam,  int  iLvType,  int  curnItem,  BOOL  bFirst,  void  *  pParam0  )
{
	 int								iErr											=		-1;
	 HWND								hParent											=		pEventInfo->hWnd;
	 unsigned  int						uiCmd											=		pEventInfo->uiCmd;  
	 TCHAR								tBuf[256]										=		_T(  ""  );
	 TCHAR								colName[256]									=		_T(  "ID"  );
	 
	 if  (  pVDev->m_var.common.pGuiOpen->pf_getLvColContent(  hParent,  pEventInfo->hFrom,  curnItem,  colName,  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;

	 pVDev->m_var.iCurIndex  =  _ttol(  tBuf  );

	 switch  (  pEventInfo->uiCmd  )  {
			 case  ID_qyConfig:
				   MessageBox(  NULL,  _T(  "config"  ),  tBuf,  MB_OK  );
				   pEventInfo->ucbRefreshed  =  TRUE;
				   break;
			 case  ID_qyTest:		
				   if  (  isHandleValid(  pVDev->m_var.hThread_dlg  )  )  {
					   DWORD  dwExitCode  =  0;
					   if  (  GetExitCodeThread(  pVDev->m_var.hThread_dlg,  &dwExitCode  )  &&  dwExitCode  ==  STILL_ACTIVE  )  {
						   iErr  =  0;  goto  errLabel;
					   }
					   //
					   MACRO_qyNullThread(  pVDev->m_var.hThread_dlg  );
				   }
				   //
				   DWORD	dwThreadDaemonId;	
				   pVDev->m_var.hThread_dlg  =  CreateThread(  NULL,  0,  threadProc_dlg_vDevComs,  0,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
				   if  (  !isHandleValid(  pVDev->m_var.hThread_dlg  )  )  goto  errLabel;
				   //				   
	 			   pVDev->m_var.dwThreadId_dlg  =  dwThreadDaemonId;
	 			   if  (  ResumeThread(  pVDev->m_var.hThread_dlg  )  ==  -1  )  goto  errLabel;
				   //
				   break;
			 default:
					break;
					
	 }



	 iErr  =  0;
errLabel:
	 return  iErr;
}

 
 int  procCmd_vDevComs(  void  *  p0,  void  *  pSelParam,  void  *  pEventInfoParam  )
{
	 QY_MCVIEW_SEL	*	pSel		=	(  QY_MCVIEW_SEL  *  )pSelParam;
	 QY_EVENTINFO	*	pEventInfo	=	(  QY_EVENTINFO  *  )pEventInfoParam;

	 if  (  !pSel  ||  !pEventInfo  )  return  -1;

	 pVDev->m_var.common.pGuiOpen->pf_enumLvSelEventFunc(  pEventInfo,  procLvEventFunc_vDevComs,  NULL,  pSel->type,  0  );

	 return  0;
}


  //²Ù×÷Éè±¸
  extern  "C"  __declspec( dllexport )  int  qyVDev_op(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int				iErr  =  -1;
	 QY_MCVIEW_SEL		param;

	 traceLogA(  "opQyVDev enters"  );
	 
	 memset(  &param,  0,  sizeof(  param  )  );
	 param.pfDisplayListContent  =  (  PF_commonHandler  )bDisplayMcViewContent_coms;
	 param.pfProcCmd  =  procCmd_vDevComs;
	 param.pCusRes  =  &gVDev.m_var.cusRes;
	 param.uPopupMenuId  =  IDR_popup_vDevComs;
	 param.nSubMenuPos  =  CONST_resId_popup_vDevCom;
	 param.uiDefaultCmd  =  ID_qyTest;
	 param.ucbMultiSel  =  TRUE;


	 //  ×¢Òâ£º
	 //		  ÕâÀï£¬ÐèÒªÓÐµ¯³ö²Ëµ¥¡£²¢ÐèÒª½«ÏìÓ¦º¯ÊýÔÚÕâÀï¶¨Òå¡£
	 //		  ÔÚnms_popupÀï£¬²Ëµ¥ÊÇ¸ù¾ÝcusResÀ´¶¨ÒåµÄ¡£ËùÒÔ½«cusResÊÊµ±¸Ä±ä¼´¿É¡£
	 //		  ¶Ô²Ëµ¥ÃüÁî£¬ÔòÐèÒªÔÙ¿¼ÂÇÒ»ÏÂ¡£µ½µ×ÄÜ²»ÄÜÖ±½Ó¶¨Òå£¬»¹ÊÇÐèÒª×Ô¼ºÀ´¼ÆËãÉú³É¡£

	 //
	 _sntprintf(  param.docName,  mycountof(  param.docName  ),  _T(  "GSM Modems"  )  );

	 pVDev->m_var.common.pGuiOpen->pf_bQyOpenMcView(  &param,  0,  0  );
	 
	 iErr  =  0;
	 return  iErr;
}


 extern  "C"  __declspec( dllexport )  int  qyVDev_postStr2Dev(  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  LPCTSTR  str,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  WCHAR  *  wForwardPath,  HWND  hWnd_notify,  int  iUsrData  )
{
	 int					iErr						=	-1;
	 char					fullPhoneNo_to[32  +  1]	=	"";
	 unsigned  int			uiComIndex					=	(  unsigned  int  )-1;
	 CComPort			*	pPort;
	 TCHAR				*	pDevName					=	NULL;
	 TCHAR				*	pT;

	 traceLogA(  "qyVDev_sendMsg enters"  );

	 if  (  uiDevType_to  )  {
		 if  (  !wDevIdStr_to  )  goto  errLabel;
		 if  (  wDevIdStr_to[0]  )  {
			 if  (  !(  pDevName  =  _tcschr(  wDevIdStr_to,  _T(  '/'  )  )  )  )  goto  errLabel;
			 pDevName  ++  ;

			 for  (  uiComIndex  =  0;  uiComIndex  <  pVDev->m_var.cfg.uiMaxComs;  uiComIndex  ++  )  {
				  pPort  =  &pVDev->m_var.pPorts[uiComIndex];
				  if  (  !pPort->m_var.ucbStarted  )  continue;
				  if  (  _tcsicmp(  pDevName,  pPort->m_var.szPort  )  )  continue;
				  break;
			 }
			 //  Ö¸¶¨ÁËwDevIdStr_to, ¾Í²»ÄÜ¶ÔÓ¦²»ÉÏ¡£·ñÔò£¬¾Í·¢²»³öÈ¥
			 if  (  !bComIndexValid(  pVDev,  uiComIndex  )  )  goto  errLabel;
		 }
	 }
	 
	 if  (  !wForwardPath  )  goto  errLabel;
	 //
	 if  (  _tcschr(  wForwardPath,  _T(  '|'  )  )  )  {
		 traceLogA(  "failed: ÔÝÊ±Ö»ÔÊÐíÒ»´Î×ª·¢"  );  goto  errLabel;
	 }
	 //
	 if  (  _tcsnicmp(  wForwardPath,  CONST_str_phone,  lstrlen(  CONST_str_phone  )  )  )  {
		 traceLogA(  "wForwarePath [%S] ¸ñÊ½´íÎó£¬²»ÊÇphone:***",  wForwardPath  );
		 goto  errLabel;
	 }
	 if  (  !(  pT  =  _tcschr(  wForwardPath,  _T(  ':'  )  )  )  )  goto  errLabel;
	 pT  ++  ;
	 if  (  !myTChar2Str(  pT,  fullPhoneNo_to,  mycountof(  fullPhoneNo_to  )  )  )  goto  errLabel;



	 if  (  mySendMsg_vDevComs(  str,  fullPhoneNo_to,  uiComIndex,  hWnd_notify,  iUsrData  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;

}

 extern  "C"  __declspec( dllexport )  int  qyVDev_postData2Dev(  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  void  *  pQyVDevData,  unsigned  int  uiDataLen,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  unsigned  int  uiDevIndex  )
{
	 int			iErr						=	-1;
	 unsigned  int	uiComIndex					=	(  unsigned  int  )uiDevIndex;

	 traceLogA(  "qyVDev_postData2Dev enters"  );

	 if  (  postMsg2Mgr_vDevComs(  pVDev,  CONST_misMsgType_input,  uiComIndex,  (  char  *  )pQyVDevData,  uiDataLen  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;

}



  extern  "C"  __declspec( dllexport )  int  qyVDev_chkBeforeInit(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int  iErr  =  -1;

	 traceLogA(  "chkQyVDev_beforeInit enters"  );
	 
	 iErr  =  0;
	 return  iErr;
}

   //  ³õÊ¼»¯Éè±¸ 
 extern  "C"  __declspec( dllexport )  int  qyVDev_init(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int		iErr				=  -1;
	 int		len					=	0;
	 int		i;

	 traceLogA(  "initQyVDev enters"  );

	 gVDev.m_var.usLangId  =  GetSystemDefaultLangID(  );
	 if  (  initQnmRes(  0,  gVDev.m_var.usLangId,  CONST_resId_app_vDevComs,  &gVDev.m_var.cusRes  )  )  goto  errLabel;
     gVDev.m_var.ucbCusResInited  =  TRUE;


	 if  (  initGenericQ(  &pVDev->m_var.cfg.mgrQ,  malloc,  0,  0,  free,  NULL,  &pVDev->m_var.mgrQ  )  )  goto  errLabel; 

	 if  (  initGenericQ(  &pVDev->m_var.cfg.dataQ,  malloc,  0,  0,  free,  NULL,  &pVDev->m_var.dataQ  )  )  goto  errLabel;
	 
	 if  (  !pVDev->m_var.cfg.uiMaxComs  )  goto  errLabel;
	 pVDev->m_var.pPorts  =  new  CComPort[pVDev->m_var.cfg.uiMaxComs];
	 if  (  !pVDev->m_var.pPorts  )  goto  errLabel;

	 len  =  sizeof(  COM_BUF_O  )  *  pVDev->m_var.cfg.uiMaxComs;
	 if  (  !(  pVDev->m_var.pBufOs  =  (  COM_BUF_O  *  )malloc(  len  )  )  )  goto  errLabel;
	 memset(  pVDev->m_var.pBufOs,  0,  len  );

	 len  =  sizeof(  GENERIC_Q  )  *  pVDev->m_var.cfg.uiMaxComs;
	 if  (  !(  pVDev->m_var.pOutputQs  =  (  GENERIC_Q  *  )malloc(  len  )  )  )  goto  errLabel;
	 //
	 memset(  pVDev->m_var.pOutputQs,  0,  len  );
	 for  (  i  =  0;  i  <  (  int  )pVDev->m_var.cfg.uiMaxComs;  i  ++  )  {
		  TCHAR	tBuf[64]	=	_T(  ""  );
		  //
		  _sntprintf(  tBuf,  mycountof(  tBuf ),  _T(  "vDevOutputQ%d"  ),  i  );
		  if  (  initGenericQ(  tBuf,  tBuf,  0,  100,  malloc,  free,  &pVDev->m_var.pOutputQs[i]  )  )  goto  errLabel;
		  //
	 }
	 
	 iErr  =  0;
errLabel:
	 return  iErr;
}


  extern  "C"  __declspec( dllexport )  int  qyVDev_chkAfterInit(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int  iErr  =  -1;

	 traceLogA(  "chkQyVDev_afterInit enters"  );

	 iErr  =  0;
	 return  iErr;
}

 

  // ³õÊ¼»¯GSM×´Ì¬
 int  gsmInit(  HANDLE  hComm,  char  *  smscBuf,  unsigned  int  smscBufSize,  char  *  modelBuf,  unsigned  int  uiModelBufSize,  HWND  hWnd_test,  int  port  )
{
	int			iErr				=	-1;
	char	*	pCmd				=	"";
	char		ans[1024]			=	"";		// Ó¦´ð´®
	char		tmpSmscBuf[128]		=	"";
	char		tmpModelBuf[1024]	=	"";
	char	*	p;

	// ²âÊÔGSM-MODEMµÄ´æÔÚÐÔ
	
	pCmd  =  "AT\r";
	writeComm(  hComm,  pCmd,  strlen(  pCmd  )  );
	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  pCmd  ).GetBuffer(  0  ),  port  ); 
	memset(  ans,  0,  sizeof(  ans  )  );
	readComm(  hComm,  ans, 128);
	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  ans  ).GetBuffer(  0  ),  port  );  
	if (strstr(ans, "OK") == NULL)  goto  errLabel;

	// ECHO OFF
	pCmd  =  "ATE0\r";
	writeComm(  hComm,  pCmd,  strlen(  pCmd  )  );
	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  pCmd  ).GetBuffer(  0  ),  port  );  
	memset(  ans,  0,  sizeof(  ans  )  );
	readComm(  hComm,  ans, 128);
	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  ans  ).GetBuffer(  0  ),  port  );  
	
	// È¡ÐÍºÅ
	pCmd  =  "ATI\r\n";
	writeComm(  hComm,  pCmd,  strlen(  pCmd  )  );
	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  pCmd  ).GetBuffer(  0  ),  port  );  
	memset(  ans,  0,  sizeof(  ans  )  );
	readComm(  hComm,  ans,  sizeof(  ans  )  );
	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  ans  ).GetBuffer(  0  ),  port  );  
	if  (  (  p  =  strstr(  ans,  "OK"  )  )  )  {
		*p  =  0;
		trim(  ans  );  safeStrnCpy(  ans,  tmpModelBuf,  mycountof(  tmpModelBuf  )  );
	}

	// PDUÄ£Ê½
	pCmd  =  "AT+CMGF=0\r";
	writeComm(  hComm,  pCmd,  strlen(  pCmd  )  );
	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  pCmd  ).GetBuffer(  0  ),  port  );  
	memset(  ans,  0,  sizeof(  ans  )  );
	readComm(  hComm,  ans, 128);
	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  ans  ).GetBuffer(  0  ),  port  );  
	//
	//  ×Ô¶¯½ÓÊÕÄ£Ê½
	pCmd  =  "AT+CNMI=2,1\r\n";
	writeComm(  hComm,  pCmd,  strlen(  pCmd  )  );
	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  pCmd  ).GetBuffer(  0  ),  port  );  
	memset(  ans,  0,  sizeof(  ans  )  );
	readComm(  hComm,  ans,  sizeof(  ans  )  );
	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  ans  ).GetBuffer(  0  ),  port  );  

	//
	memset(  ans,  0,  sizeof(  ans  )  );
	//
	pCmd  =  "AT+CSCA?\r";
	writeComm(  hComm,  pCmd,  strlen(  pCmd  )  );
	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  pCmd  ).GetBuffer(  0  ),  port  );  
	memset(  ans,  0,  sizeof(  ans  )  );
	readComm(  hComm,  ans,  sizeof(  ans  )  );
	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  ans  ).GetBuffer(  0  ),  port  );  
	//
	TRACE(  _T(  "%S=[%S]"  ),  pCmd,  ans  );

	p  =  strstr(  ans,  "CSCA:"  );
	if  (  p  )  {
		if  (  (  p  =  strchr(  p,  ':'  )  )  )  {
			p  ++  ;
			for  (  ;  *p;  p  ++  )  {
				 if  (  isdigit(  *p  )  )  break;
			}
			if  (  *p  )  {
				safeStrnCpy(  p,  tmpSmscBuf,  mycountof(  tmpSmscBuf  )  );
				for  (  p  =  tmpSmscBuf;  *p;  p  ++  )  {
					 if  (  *p  !=  '+'  &&  !isdigit(  *p  )  )  break;					  
				}
				if  (  *p  )  *p  =  '\0';
			}

		}

	}

	iErr  =  0;

errLabel:
	if  (  !iErr  )  {
		if  (  smscBuf  )  safeStrnCpy(  tmpSmscBuf,  smscBuf,  smscBufSize  );
		if  (  modelBuf  )  safeStrnCpy(  tmpModelBuf,  modelBuf,  uiModelBufSize  );
	}
	return  iErr;
}



 BOOL  bInitGsmModem(  CString  m_strPort,  int  nBaudRate,  BOOL  *  pbComExists,  BOOL  *  pbGsmModem,  char  *  smscBuf,  unsigned  int  uiSmscBufSize,  char  *  modelBuf,  unsigned  int  uiModelBufSize,  HWND  hWnd_test,  int  iPortNo  )
{
	BOOL	bRet					=	FALSE;
	HANDLE	hComm					=	NULL;
	char	tmpSmscBuf[128]			=	"";
	char	tmpModelBuf[1024]		=	"";
	BOOL	bComExists				=	FALSE;
	BOOL	bGsmModem				=	FALSE;
	TCHAR	tBuf[255  +  1]			=	_T(  ""  );

	//  2008/03/03
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "ver is %S"  ),  qnmVerStr(  CONST_qyServiceId_is  )  );
	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )tBuf,  -1  );  

	if (  !(  hComm  =  openComm(  m_strPort, nBaudRate)  )  )  goto  errLabel;
	bComExists  =  TRUE;

	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )_T(  "Start init Gsm Modem"  ),  iPortNo  );  

	if  (  gsmInit(  hComm,  tmpSmscBuf,  mycountof(  tmpSmscBuf  ),  tmpModelBuf,  mycountof(  tmpModelBuf  ),  hWnd_test,  iPortNo  )  )  {
		traceLogA("¸Ã¶Ë¿ÚÉÏÃ»ÓÐ·¢ÏÖMODEM!");  

		SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )_T(  "No Gsm Modem"  ),  iPortNo  );  

		bRet  =  TRUE;  goto  errLabel;
	}
	bGsmModem  =  TRUE;

	trim(  tmpSmscBuf  );

	if  (  !tmpSmscBuf[0]  )  {
		traceLogA(  "ÇëÉèÖÃSMSC!");  
		SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )_T(  "SMSC need to be set"  ),  iPortNo  );  
		goto  errLabel;
	}

	SendMessage(  hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )_T(  "Gsm Modem is initialized"  ),  iPortNo  );  

	bRet  =  TRUE;

errLabel:

	if  (  hComm  )  CloseHandle(  hComm  );
	
	if  (  bRet  )  {
		if  (  pbComExists  )  *pbComExists  =  bComExists;
		if  (  pbGsmModem  )  *pbGsmModem  =  bGsmModem;
		if  (  smscBuf  )  safeStrnCpy(  tmpSmscBuf,  smscBuf,  uiSmscBufSize  );
		if  (  modelBuf  )  safeStrnCpy(  tmpModelBuf,  modelBuf,  uiModelBufSize  );
	}
	
	return  bRet;
}


 //  char	*	ÎÒµÄÊÖ»ú¡£smscBuf  =  "+8613800100500";

int  mySendCmd(  int  uiComIndex,  char  *  cmd,  char  *  pdu,  char  *  phoneNo_to_sending  );

 //  Æô¶¯Éè±¸
  extern  "C"  __declspec( dllexport )  int  qyVDev_start(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int								iErr					=	-1;
	 int								i;
	 TCHAR								tBuf[256]				=	_T(  ""  );
	 CString							str;
	 CComPort						*	pPort;
	 BOOL								bComExists				=	FALSE;
	 BOOL								bGsmModem				=	FALSE;
	 char								smscBuf[128]			=	"";
	 char								modelBuf[1024]			=	"";
	 COM_BUF_O						*	pO						=	NULL;
	 DWORD								dwThreadDaemonId		=	0;
	 unsigned  int						baud					=	0;
	 QY_GUI_OPEN_vDev					*	pOpen					=			pVDev->m_var.common.pGuiOpen;


	 traceLogA(  "qyVDev_start enters"  );

	 //  ¶ÁÈ¡²¨ÌØÂÊ
	 if  (  !pOpen->pf_bGetLongProperty(  0,  (  void  *  )CONST_qyPropertyId_baud,  &baud  )  )  goto  errLabel;
	 if  (  !baud  )  baud  =  9600;
	 

	 //
	 pVDev->m_var.bStop  =  FALSE;

	 // init the ports
	 for  (  i  =  0;  i  <  CONST_maxComs;  i  ++  )  {
		  pPort  =  &pVDev->m_var.pPorts[i];
		  //  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "COM%d"  ),  i  +  1  );

		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\\\\.\\COM%d"  ),  i  +  1  );

		  if  (  !bInitGsmModem(  tBuf,  baud,  &bComExists,  &bGsmModem,  smscBuf,  mycountof(  smscBuf  ),  modelBuf,  mycountof(  modelBuf  ),  0,  0  )  )  continue;
		  if  (  !bGsmModem  )  continue;
		  traceLogA(  "initGsmModem %S ok",  tBuf  );

		  //		  
		  if  (  !pPort->InitPort(  pVDev,  i,  NULL,  smscBuf,  i + 1, baud  )  )  {
			  traceLogA(  "com%d NOT FOUND",  i  +  1  );
			  continue;
		  }
		  safeStrnCpy(  modelBuf,  pPort->m_var.modelBuf,  mycountof(  pPort->m_var.modelBuf  )  );
		  //	    
		  traceLogA(  "comPort.initPort %S ok",  tBuf  );

	 }

	 // ÕâÀïÆô¶¯¹ÜÀíÏß³Ì
	 
	 pVDev->m_var.hThread_mgr  =  CreateThread(  NULL,  0,  threadProc_mgr_vDevComs,  0,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
	 if  (  !pVDev->m_var.hThread_mgr  )  goto  errLabel;
	 pVDev->m_var.dwThreadId_mgr  =  dwThreadDaemonId;
	 if  (  ResumeThread(  pVDev->m_var.hThread_mgr  )  ==  -1  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 traceLogA(  "qyVDev_start leaves"  );

	 return  iErr;
}

 //  Í£Ö¹Éè±¸
  extern  "C"  __declspec( dllexport )  int  qyVDev_stop(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int  iErr  =  -1;

	 traceLogA(  "stopQyVDev enters"  );

	 //  pVDev->m_var.bStop  =  TRUE;

	 iErr  =  0;
	 return  iErr;


}

 //  Ð¶ÔØÉè±¸
  extern  "C"  __declspec( dllexport )  int  qyVDev_exit(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int	i;

	 traceLogA(  "exitQyVDev enters"  );

	 pVDev->m_var.bQuit  =  TRUE;

	 if  (  isHandleValid(  pVDev->m_var.hThread_dlg  )  )  {
		 PostThreadMessage(  pVDev->m_var.dwThreadId_dlg,  WM_QUIT,  0,  0  );
		 MACRO_qyNullThread(  pVDev->m_var.hThread_dlg  );
	 }

	 MACRO_qyNullThread(  pVDev->m_var.hThread_mgr  );

	 if  (  pVDev->m_var.pOutputQs  )  {
		 for  (  i  =  0;  i  <  (  int  )pVDev->m_var.cfg.uiMaxComs;  i  ++  )  {
			  exitGenericQ(  &pVDev->m_var.pOutputQs[i]  );
		 }
		 free(  pVDev->m_var.pOutputQs  );
	 }


	 if  (  pVDev->m_var.pBufOs  )  free(  pVDev->m_var.pBufOs  );
	 if  (  pVDev->m_var.pPorts  )  delete [] pVDev->m_var.pPorts;

	 exitGenericQ(  &pVDev->m_var.mgrQ  );

	 if  (  gVDev.m_var.ucbCusResInited  )  {
		 exitQnmRes(  0,  &gVDev.m_var.cusRes  );  gVDev.m_var.ucbCusResInited  =  FALSE;
	 }

	 traceLogA(  "exitQyVDev leave"  );

	 return  0;
}


 // 
 extern  "C"  __declspec( dllexport )  BOOL  qyVDev_isSendable(  void  *  p0,  void  *  uiObjTypeParam,  void  *  wDevIdStrParam  )
{
	BOOL				bRet		=	FALSE;
	unsigned  int		uiObjType	=	(  unsigned  int  )uiObjTypeParam;
	WCHAR			*	pwDevIdStr	=	(  WCHAR  *  )wDevIdStrParam;
	
	if  (  !uiObjType  &&  !pwDevIdStr  )  return  FALSE;

	//  
	//  ÕâÀï£¬Êµ¼ÊÓ¦¸Ã½«uiObjTypeÀ´×öÅÐ¶Ï£¬½«wDevIdStr´ÓcomsÀïËÑË÷¡£ÈçÓÐ£¬¾Í·µ»ØTRUE¡£ÈçÎÞ£¬¾Í·µ»ØFALSE
	//
	
	if  (  uiObjType  )  {
		switch  (   uiObjType  )  {
				case  CONST_objType_phoneGuest:
				case  CONST_objType_phoneMessenger:
					  break;
				default:
						goto  errLabel;
		}
	}
	
	bRet  =  TRUE;

errLabel:
	return  bRet;
}





  
