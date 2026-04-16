// DlgTalk.cpp : implementation file
//

#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	"qymcMainCommon.h"
#include	"myresource.h"


#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"

#ifdef  __SUPPORT_HTMLEDIT__
	#include	"myHtmlEditCtrl.h"
#endif

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
#include	"DlgTalk.h"
#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"
#include	"DlgInstantAssistant.h"

#include	<assert.h>
#ifndef  __WINCE__
	#include	"qyPs.h"
#endif
#include	"qmcDxSurfacePublic.h"
#include	"qmcConferenceWall.h"
#include	"isCliHelpPublic.h"
#include	"qmcCmdProc.h"
#include	"isCmdConst.h"

#include	"DlgMsgList.h"

#include	"remoteAssistPublic.h"
#include	"qyString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include	"wallTalkers.h"
#include	"dlgDynBmpsproc.h"
#include	"qmcSharePublic.h"
#include	"amCapPublic.h"
#include	"funcsforIsCliHelp.h"

#include	"imgProcessPublic.h"

#include	"isCliD3dPublic.h"
#include	"qmcObjVarInfo.h"
#include	"objType_tmp.h"
//
#include	"DlgPtzControl.h"
#include	"qyVk.h"
#include	"isCliExPublic.h"
#include	"dlgMsgToolProc.h"

//
int  refreshDlg_talk(  HWND  hDlgTalk,  void  *  pGuiDataTalkParam,  HWND  hDlg_instantAssistant  );

 

 //  2013/02/26
 BOOL  dlgTalk_bCtrlsInited(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var  )
 {
	 BOOL	bRet	=	FALSE;
	 int	idc;
	 HWND	hCtrl;

 	 idc  =  pm_var->guiData.iIDC_STATIC_dlgDesc;
	 hCtrl  =  GetDlgItem(  hDlgTalk,  idc  );
	 if  (  !hCtrl  )  goto  errLabel;

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
 }


 //
 int  dlgTalk_fillPeerInfo(  HWND  hCurTalk  )
 {
	 int  iErr  =  -1;
	 	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	
	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	
	
				//
		void					*	pDb				=		NULL;
		//	
		CQnmDb						db;
		if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
		pDb  =  db.m_pDbMem->pDb;
	
		//
		QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
		if  (  !pDbFuncs  )  goto  errLabel;
		QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	
	//
	DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hCurTalk  );
	if  (  !pCurVar  )  return  -1;



	//  2012/05/01
	HWND				hMgr		=	hCurTalk;
	DLG_TALK_var  *		pMgrVar		=	pCurVar;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pCurVar->pShadowInfo;
		if  (  !pTalkerShadow  )  goto  errLabel;
		if  (  !IsWindow(  pTalkerShadow->hMgr  )  )  goto  errLabel;
		hMgr  =  pTalkerShadow->hMgr;		//  2013/02/15
		pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr  );
		if  (  !pMgrVar  )  goto  errLabel;
	}







	 // 
	 HWND  hCtrl  =  GetDlgItem(  hCurTalk,  IDC_LIST_peerInfo  );
	 TCHAR  tBuf[128]  =  _T(  ""  );

	 //
	  ::SendMessage(  hCtrl,  LB_RESETCONTENT,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    

	

	  //
	  if  (  !pMgrVar->av.taskInfo.bTaskExists  )  goto  errLabel;
	  QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pMgrVar->av.taskInfo.iIndex_taskInfo  );
	  if  (  !pTaskInfo  )  goto  errLabel;
	  if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
	  QMC_taskData_conf  * pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	  DLG_TALK_videoConference	*	pVc					=	&pTc->videoConference;

	  //
	  int  i;
	  for  (  i   =  0;  i  <  mycountof(  pVc->activeMems_from  );  i  ++  )  {
		   DLG_TALK_videoConferenceActiveMemFrom  *  pMem  =  &pVc->activeMems_from[i];
		   if  (  !pMem->avStream.idInfo.ui64Id  )  continue;
		   
		   //
		   QY_MESSENGER_ID  *  pIdInfo  =  &pMem->avStream.idInfo;

		   //		
		   QY_MESSENGER_REGINFO  regInfo;
		   //
		   int  iDbType  =  CONST_dbType_myDb;
		   if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  _T(  ""  ),  pIdInfo,  0,  &regInfo  )  )  {
			   memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		   }
		   //
		   MY_REG_DESC  desc;
		   //
		   regInfo2Desc(  0,  &regInfo,  &desc,  0,  0,  0,  0   );  

		   //		
		   ::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )desc.pDw  );
		   ::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )desc.pBm  );
		   ::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )desc.pSyr  );

		   //
#if  0
		   INFO_consult_yz  *  pInfo  =  &pMgrVar->av.taskInfo.info_consult_yz;
		   int  j;
		   for  (  j  =  0;  j  <  mycountof(  pInfo->mems  );  j  ++  )  {
			    if  (  pInfo->mems[j].idInfo.ui64Id  ==  pIdInfo->ui64Id  )  break;
		   }
		   if  (  j  <  mycountof(  pInfo->mems  )  )  {
			   CONSULT_mem  *  pCm  =  &pInfo->mems[j];
			   if  (  pCm->ksName[0]  )  {
				   ::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )pCm->ksName  );
			   }
			   if  (  pCm->ysName[0]  )  {
				   ::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )pCm->ysName  );
			   }
		   }
#endif

		   //
		   ::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )_T(  ""  )  );


		   //
		   continue;
	  }


	  //
	  iErr  =  0;

errLabel:
	 return  iErr;

 }


__declspec(dllexport)  CQyString		getNextRowIdStr(  HWND  hDlgTalk  )  
{	
	TCHAR			tBuf[16]	=  _T(  ""  );
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pm_var		=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk,  _T(  "getNextRowIdStr"  )  );
	if  (  !pm_var  )  return  CQyString(  ""  );

#if  10
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "RowId%u"  ),  pm_var->iRowId_internal  );  
	pm_var->iRowId_internal  ++  ;  
#else
	static  unsigned  int  suiRowId_internal  =  0;

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "RowId%u"  ),  suiRowId_internal  );  
	suiRowId_internal  ++  ;
#endif

	return  CQyString(  tBuf  );  
}


 

__declspec(  dllexport  )  BOOL  dlgTalk_bEnableScrollBar(  HWND  hDlgTalk,  BOOL  bEnable  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL	bRet	=	FALSE;
	CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlgTalk  );
	if  (  !pDlgTalk  )  goto  errLabel;

	if  (  !pDlgTalk->bEnableScrollBar(  bEnable  )  )  goto  errLabel;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


__declspec(  dllexport  )  int  dlgTalk_SetPicRect(  HWND  hDlgTalk,  int  w,  int  h,  BOOL  bMoveWindow  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int	iErr	=	-1;
	CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlgTalk  );
	if  (  !pDlgTalk  )  goto  errLabel;

	pDlgTalk->SetPicRect(  w,  h,  bMoveWindow  );
	iErr  =  0;
errLabel:
	return  iErr;
}


//  2014/11/27
__declspec(  dllexport  )  int  dlgTalk_getLayout(  HWND  hDlgTalk,  DLG_talk_layout  *  pLayout  )
{	
	int	iErr	=	-1;
	CHelp_getDlgTalkVar  help_getDlgTalkVar;
	DLG_talk_var  *  pDlgTalkVar =   (  DLG_talk_var  *  )help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pDlgTalkVar  )  return  -1;

	if  (  !pLayout  )  return  -1;

	memcpy(  pLayout,  &pDlgTalkVar->m_layout,  sizeof(  pLayout[0]  )  );

	return  0;
}



  __declspec(  dllexport  )  int  dlgTalk_doLayout(  HWND  hDlgTalk  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int	iErr	=	-1;
	CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlgTalk  );
	if  (  !pDlgTalk  )  goto  errLabel;
	

	DLG_TALK_var  *  pm_var  =  pDlgTalk->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;


	if  (  m_var.m_scrollInfo.bScrollBarEnabled  )  {
		 pDlgTalk->SetPicRect(  m_var.m_layout.uiW_pic,  m_var.m_layout.uiH_pic,  FALSE  );
	 }

	pDlgTalk->doLayout(  );

	iErr  =  0;

errLabel:
	return  iErr;
}


///////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDlgTalk dialog
#ifndef  __WINCE__

  //  只被help_getDlgTalkVar调用
__declspec(  dllexport  ) void  *  tmp_getDlgTalkVar_mfc(  HWND  hDlgTalk  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if  (  !IsWindow(  hDlgTalk  )  )  return  NULL;
	CWnd  *  pDlgTalk  =  CWnd::FromHandlePermanent(  hDlgTalk  );
	if  (  !pDlgTalk  )  return  NULL;

	//return  &(  (  CDlgTalk  *  )pDlgTalk  )->m_var;
	return  (  (  CDlgTalk  *  )pDlgTalk  )->get_pm_var(  );
}
#endif

#if  0
CDlgTalk::CDlgTalk(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTalk::IDD, pParent)
#endif
//
CDlgTalk::CDlgTalk(QY_MC  *  pQyMc,  HWND hParent /*=NULL*/)
	: CDialog(CDlgTalk::IDD, CWnd::FromHandle(  hParent  )  )
{
	//{{AFX_DATA_INIT(CDlgTalk)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	//  ASSERT(pParent != NULL);

	//
	if (!pQyMc)  return;

	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp		*	pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	//
	this->iIndex_talkerInfo  =  -1;

	//
	int  iTalkerDataType  =  CONST_objVarDataType_dlgTalk;
	this->iIndex_talkerInfo  =  newQmcObjVarInfoIndex(  pProcInfo,  iTalkerDataType,  0  );
	if  (  this->iIndex_talkerInfo  <  0  )  return;
	
	//
	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_TALK_var  &  m_var  =  *pm_var;

	//
	m_var.pQyMc = pQyMc;

	//
	//memset(  &m_var,  0,  sizeof(  m_var  )  );
	
	//  2015/11/15
	m_var.iIndex_talkerInfo  =  this->iIndex_talkerInfo;

	//
	//  m_var.m_hParent = pParent  ?  pParent->m_hWnd  :  NULL;
	m_var.m_hParent = hParent;

	//  2013/03/19
	m_var.bIncludeACap  =  pProcInfo->cfg.policy.audio.uiRecordType  ==  CONST_recordType_directX;

	//
	m_var.loopCtrl_timer  =  9;

	
	//  2011/02/20
	m_var.guiData.iIDC_STATIC_dlgDesc  =  IDC_STATIC_dlgDesc;

	//
	m_var.guiData.iIDC_talkerList  =  IDC_talkerList;
	m_var.guiData.iIDC_LIST_members  =  IDC_LIST_members;
	//
	m_var.guiData.iIDC_BUTTON_micOff  =  IDC_BUTTON_micOff;
	//
	m_var.guiData.iIDC_STATIC_filter  =  IDC_STATIC_filter;
	m_var.guiData.iIDC_EDIT_filter  =  IDC_EDIT_filter;
	//
	m_var.guiData.iIDC_BUTTON_permitToSpeak  =  IDC_BUTTON_permitToSpeak;
	m_var.guiData.iIDC_BUTTON_noSpeaking  =  IDC_BUTTON_noSpeaking;


		
	//  2012/05/18
	//  2014/01/27
	m_var.guiData.iIDC_STATIC_msgTool  =  IDC_STATIC_msgTool;
	
	//
	m_var.guiData.iIDC_STATIC_ptz  =  IDC_STATIC_ptz;				//  2012/09/05
	//
	m_var.guiData.iIDC_STATIC_subtitles  =  IDC_STATIC_subtitles;	//  2013/04/05
	//
	m_var.guiData.iIDC_STATIC_offlineRes  =  IDC_STATIC_offlineRes;		//  2015/08/01
	

	//  2013/02/24
	m_var.guiData.iIDC_STATIC_peerDesc  =  IDC_STATIC_peerDesc;			
	m_var.guiData.iIDC_STATIC_meDesc  =  IDC_STATIC_meDesc;
	m_var.guiData.iIDC_STATIC_otherDesc  =  IDC_STATIC_otherDesc;
	m_var.guiData.iIDC_STATIC_bgWall_conf  =  IDC_STATIC_bgWall_conf;					//  2014/10/01

	//  2017/10/02
	m_var.guiData.iIDC_STATIC_status  =  IDC_STATIC_status;

	//  2017/08/21
	m_var.guiData.iIDC_STATIC_peerInfo  =  IDC_STATIC_peerInfo;
	m_var.guiData.iIDC_LIST_peerInfo  =  IDC_LIST_peerInfo;
	m_var.guiData.iIDC_BUTTON_shareScreen  =  IDC_BUTTON_shareScreen;
	m_var.guiData.iIDC_BUTTON_controlDesktop  =  IDC_BUTTON_controlDesktop;
	
	//		
	m_var.guiData.pf_refreshDlg_talk_ce  =  refreshDlg_talk;

	//
	if  (  bApp_ts(  pQyMc  )  )  {  //  #ifdef  __APP_qyMc_touchscreen__
		m_var.guiData.pf_displayNotification_talk_ce  =  pFuncs->pf_displayNotification_talk_ts;
	}
	else  {  //#else
	}  //  #endif

	//
	memset(  &m_skinProc,  0,  sizeof(  m_skinProc  )  );


	//  m_var.guiData.snmpbShowMsgBox  =  pProcInfo->cfg.policy.dlgTalk.snmpbShowMsgBox;		//  2011/03/29

#ifdef  __DEBUG__	//  2014/11/05

	//qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Messenger: %s"  ),  m_var.tHint  );

#endif

}

CDlgTalk:: ~CDlgTalk()
{
	OutputDebugString(  _T(  "CDlgTalk::~CDlgTalk(  ) enters\n"  )  );
	
	//
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;

	//
	DLG_TALK_var  *  pm_var  =  get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_TALK_var  &  m_var  =  *pm_var;

	//
#if 0
	if  (  m_var.pm_LargeImageList  )  {
			 //  tmpbRet  =  (  (  CImageList  *  )m_var.pm_LargeImageList  )->DeleteImageList(  );
			 //  tmpbRet  =  myImageList_DeleteImageList(  m_var.pm_LargeImageList  );
			 myImageList_free(  m_var.pm_LargeImageList  );
			 m_var.pm_LargeImageList  =  NULL;		
	}
	if  (  m_var.pm_SmallImageList  )  {
			 //  tmpbRet  =  (  (  CImageList  *  )m_var.pm_SmallImageList  )->DeleteImageList(  );		
			 //  tmpbRet  =  myImageList_DeleteImageList(  m_var.pm_SmallImageList  );
			 myImageList_free(  m_var.pm_SmallImageList  );
			 m_var.pm_SmallImageList  =  NULL;
	
	}
#endif
	
	
	//	
	freeQmcObjVarInfoIndex(  pProcInfo,  this->iIndex_talkerInfo  );

	OutputDebugString(  _T(  "CDlgTalk::~CDlgTalk(  ) leaves\n"  )  );	
}



//  2015/11/13
DLG_TALK_var  *  CDlgTalk::get_pm_var()
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  NULL;

	DLG_TALK_var  *  pm_var  =  NULL;
	QMC_objVar_info  *  pTalkerInfo  =  getQmcObjVarInfoByIndex(  pProcInfo,  this->iIndex_talkerInfo  );
	if  (  !pTalkerInfo  )  return  NULL;
	if  (  !pTalkerInfo->bUsed  )  return  NULL;
	
	pm_var  =  (  DLG_TALK_var  *  )pTalkerInfo->var.pData;
	if  (  !pm_var  )  return  NULL;
	if  (  pm_var->uiType  !=  CONST_objVarDataType_dlgTalk  )  return  NULL;

	return  pm_var;
}



BOOL CDlgTalk::Create(const RECT& rect) 
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );

	//
	DLG_TALK_var  *  pm_var  =  get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;

	//
	if  (  !m_var.guiData.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ) failed: bInfoSet is false"  );
		goto  errLabel;
	}

	//
	if  (  !CDialog::Create(  this->IDD, CWnd::FromHandle(  m_var.m_hParent  )  )  )  goto  errLabel;


	m_var.guiData.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


//
 BOOL  CDlgTalk::bQuitDlg(  BOOL  bCancelTasks  )		
{
	void  *  pDlg  =  this;
	return  dlgTalk_bQuitDlg(  m_hWnd,  get_pm_var(),  bCancelTasks  );

}

 BOOL  CDlgTalk::bEnableScrollBar(  BOOL  bEnable  )
{
	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  FALSE;
	DLG_TALK_var  &  m_var  =  *pm_var;

	DLG_scroll_info  &  m_scrollInfo	=	m_var.m_scrollInfo;

	m_scrollInfo.bScrollBarEnabled  =  bEnable;
		
	//  doLayout(  );

	return  TRUE;
}

 int  CDlgTalk::SetPicRect(  int  w,  int  h,  BOOL  bMoveWindow  )
{
	int					iErr		=	-1;

	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;

	DLG_scroll_info  &  m_scrollInfo  =  m_var.m_scrollInfo;
	DLG_layout_param  &  m_layoutParam  =  m_var.m_layoutParam;
	DLG_talk_layout  &  m_layoutInfo  =  m_var.m_layout;

#ifdef  __DEBUG__
		traceLog(  _T(  "dlgTalk::SetPicRect called"  )  );
#endif

	if  (  !w  ||  !h  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "dlgTalk::SetPicRect failed, w or h err"  )  );
		#endif
		return  -1;
	}
	if  (  !m_layoutInfo.usCnt_row  ||  !m_layoutInfo.usCnt_col  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "dlgTalk::SetPicRect failed, layoutInfo err"  )  );
		#endif
		return  -1;
	}

	//
	//  m_layoutInfo.
	m_layoutInfo.uiW_pic  =  w;
	m_layoutInfo.uiH_pic  =  h;


	//
	{
		unsigned  int					uiInitW		=	0;
		unsigned  int					uiInitH		=	0;
		RECT							rect,  clientRect;

		//		
		uiInitW  =  w  *  m_layoutInfo.usCnt_col  +  (  m_layoutInfo.usCnt_col  -  1  )  *  m_layoutParam.iX_spacing  +  m_layoutParam.iEdge_l  +  m_layoutParam.iEdge_r;
		uiInitH  =  h  *  m_layoutInfo.usCnt_row  +  m_layoutParam.iEdge_t  +  m_layoutParam.iEdge_b  +  m_layoutParam.iH_btn  +  m_layoutParam.iY_spacing_static_btn  +  (  m_layoutInfo.usCnt_row  -  1  )  *  m_layoutParam.iY_spacing_static_pic  +  m_layoutInfo.usCnt_row  *  (  m_layoutParam.iH_static  +  m_layoutParam.iY_spacing_pic_static  );
		
		//
		DLG_talk_layout  layout;
		dlgTalk_calculateLayout(  m_hWnd,  &m_var,  NULL,  &layout  );
		uiInitW  +=  layout.iW_memberList  +  layout.iW_taskList  +  layout.iW_ptz  +  layout.iW_peerInfo;
		uiInitH  +=  layout.iH_dlgDesc;
		
		//
		SetRect(  &m_scrollInfo.m_rect,  0,  0,  uiInitW,  uiInitH  );
		  
		//  2012/05/14
		CDlgTalk  *  pDlg  =  this;
		int  index;
		int  i,  j;
		int  iW_pic  =  w;
		int  iH_pic  =  h;
		int  x,  y,  iW,  iH;
		for  (  i  =  0;  i  <  m_layoutInfo.usCnt_row;  i  ++  )  {

			  for  (  j  =  0;  j  <  m_layoutInfo.usCnt_col;  j  ++  )  {
				   index  =  i  *  m_layoutInfo.usCnt_col  +  j;
				   //		 
				   x  =  m_layoutParam.iEdge_l  +  j  *  (  iW_pic  +  m_layoutParam.iX_spacing  );
				   y  =  m_layoutParam.iEdge_t  +  i  *  (  iH_pic  +  m_layoutParam.iY_spacing_pic_static  +  m_layoutParam.iH_static  +  m_layoutParam.iY_spacing_static_pic  );
		 		   //
		 		   iW  =  iW_pic;  iH  =  iH_pic;
				   {	//  2012/04/24
					   m_scrollInfo.mems_org[index].iX  =  x;
					   m_scrollInfo.mems_org[index].iY  =  y;
					   m_scrollInfo.mems_org[index].iW  =  iW;
					   m_scrollInfo.mems_org[index].iH  =  iH;
				   }
			  }
		}
		
	    //
	}

	//  doLayout(  );

	iErr  =  0;
errLabel:

	 return  iErr;
}

//  2012/04/24
int  CDlgTalk::getPicRect(  int  idc,  RECT  *  pRc  )
{
	int					iErr	=	-1;
		DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;

	DLG_scroll_info  &  m_scrollInfo  =  m_var.m_scrollInfo;
	DLG_layout_param  &  m_layoutParam  =  m_var.m_layoutParam;
	DLG_talk_layout  &  m_layoutInfo  =  m_var.m_layout;

	CDlgTalk  *  pBase	=  this;
	int					i;

	for  (  i  =  0;  i  <  m_layoutInfo.usCnt_row  *  m_layoutInfo.usCnt_col;  i  ++  )  {
		 //  QY_DMITEM		*	pItem;
		 //  int					idcHint;

		 //  pItem  =  &pBase->m_var.pIdcTable[i];
		 //  if  (  idc  ==  (  int  )pItem->des  )  
		 {
			 pRc->left  =  m_scrollInfo.mems_org[i].iX;
			 pRc->right  =  m_scrollInfo.mems_org[i].iX  +  m_scrollInfo.mems_org[i].iW;
			 pRc->top  =  m_scrollInfo.mems_org[i].iY;
			 pRc->bottom  =  m_scrollInfo.mems_org[i].iY  +  m_scrollInfo.mems_org[i].iH;

			 iErr  =  0;  goto  errLabel;
		 }
	}

errLabel:
	return  iErr;
}


 int  CDlgTalk::sizeAllControls(  RECT  rc  )
 {
	 	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_TALK_var  &  m_var  =  *pm_var;


	 sizeAllControls_dlgTalk(  this->m_hWnd,  &m_var,  &rc  );

	 //  2011/03/13
	 //  dlgTalk_setLayout(  m_hWnd,  m_var.av.usLayoutType_cur  );


	 return  0;
 }


 //
  void  CDlgTalk::doLayout(    )
{
	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_TALK_var  &  m_var  =  *pm_var;

	DLG_scroll_info  &  m_scrollInfo  =  m_var.m_scrollInfo;
	DLG_layout_param  &  m_layoutParam  =  m_var.m_layoutParam;
	DLG_talk_layout  &  m_layoutInfo  =  m_var.m_layout;

	int			cx,  cy;
	RECT		rc;
	SCROLLINFO	si;
	int			nScrollMax  =  0;

	//  2012/02/27	
	if  (  !dlgTalk_bCtrlsInited(  m_hWnd,  &m_var  )  )  return;

	//
	#ifdef  __DEBUG__
			traceLogA(  "doLayout called."  );
	#endif

	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë
	if  (  !m_scrollInfo.bScrollBarEnabled  )  {	

		si.cbSize  =  sizeof(  SCROLLINFO  );
		si.fMask  =  SIF_ALL;
		si.nMin  =  0;
		si.nMax  =  0;
		si.nPage  =  si.nMax  /  10;
		si.nPos  =  0;
		SetScrollInfo(  SB_HORZ,  &si,  TRUE  );
		SetScrollInfo(  SB_VERT,  &si,  TRUE  );

		//			
		GetClientRect(  &rc  );	//  2008/11/08, ÎªÁËÖ§³Ö¹ö¶¯¡£½«ÏÔÊ¾ÇøÓò´óÐ¡´æÔÚm_rectÀï¡£
					
		//
		sizeAllControls(  rc  );
		return;
	}

	//
	GetClientRect(  &rc  );	//  2008/11/08, ÎªÁËÖ§³Ö¹ö¶¯¡£½«ÏÔÊ¾ÇøÓò´óÐ¡´æÔÚm_rectÀï¡£

	cx  =  rc.right  -  rc.left;
	cy  =  rc.bottom  -  rc.top;

	if  (  !cx  ||  !cy  )  return;

	m_scrollInfo.m_nCurWidth  =  cx;
	m_scrollInfo.m_nCurHeight  =  cy;

	//
	int  m_rect_iW  =  m_scrollInfo.m_rect.right  -  m_scrollInfo.m_rect.left;
	int  m_rect_iH  =  m_scrollInfo.m_rect.bottom  -  m_scrollInfo.m_rect.top;

	//
	nScrollMax  =  0;
	if  (  cx  <  m_rect_iW  )  {
		nScrollMax  =  m_rect_iW  -  cx;
	}
	m_scrollInfo.m_nScrollPos_h  =  0;
	//
	si.cbSize  =  sizeof(  SCROLLINFO  );
	si.fMask  =  SIF_ALL;
	si.nMin  =  0;
	si.nMax  =  nScrollMax;
	si.nPage  =  si.nMax  /  10;
	si.nPos  =  m_scrollInfo.m_nScrollPos_h;
	SetScrollInfo(  SB_HORZ,  &si,  TRUE  );


	nScrollMax  =  0;
	if  (  cy  <  m_rect_iH  )  {
		nScrollMax  =  m_rect_iH  -  cy;
	}
	m_scrollInfo.m_nScrollPos_v  =  0;
	//
	si.cbSize  =  sizeof(  SCROLLINFO  );
	si.fMask  =  SIF_ALL;
	si.nMin  =  0;
	si.nMax  =  nScrollMax;
	si.nPage  =  si.nMax  /  10;
	si.nPos  =  m_scrollInfo.m_nScrollPos_v;
	SetScrollInfo(  SB_VERT,  &si,  TRUE  );

	sizeAllControls(  m_scrollInfo.m_rect  );

	return;
}


  //
 void  CDlgTalk::endFullScreen(  )
{
	DLG_TALK_var  *  pm_var  =  get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_TALK_var  &  m_var  =  *pm_var;

	
	if  (  m_var.m_bFullScreen  )  {
		m_var.m_bFullScreen  =  FALSE;

		//  2012/07/07
		restoreWndBorder(  m_hWnd,  &m_var.m_fullScreenInfo.hOldMenu,  &m_var.m_fullScreenInfo.lOldStyle  );

		//
		ShowWindow(  SW_HIDE  );
		memcpy(  &m_var.m_layoutParam,  &m_var.m_oldLayoutParam,  sizeof(  m_var.m_layoutParam  )  );
		mySetWindowPlacement(  this->GetSafeHwnd(  ),  &m_var.m_oldWndPlacement  );
		ShowWindow(  SW_RESTORE  );				

		//  2011/10/16
		m_var.bDone_endFullscreen  =  TRUE;
	}

	return;
}






 //
void CDlgTalk::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTalk)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


//
 int  CDlgTalk::sendKeyEvent(  unsigned  int  nChar, unsigned  char  ucbDown  ) 
{
	int						iErr			=	-1;
	MC_VAR_isCli			*	pProcInfo		=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;

	//
	DLG_TALK_var  *  pm_var  =  get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_TALK_var  &m_var  =  *pm_var;

	//
	if  (  pm_var->av.peerZone.images.head.usCnt  !=  1  )  return  -1;
	unsigned  int  uiTranNo_openAvDev_remoteAssist  =  pm_var->av.peerZone.images.mems[0].uiTranNo_openAvDev;  
	QY_MESSENGER_ID  idInfo_dst;
	idInfo_dst.ui64Id  =  pm_var->av.peerZone.images.mems[0].idInfo_sender.ui64Id;

	//
	MACRO_prepareForTran(  )
	unsigned  int			uiChannelType	=	CONST_channelType_media;
	REMOTE_ASSIST_REQ		req;



	//
	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_remoteAssistReq;
	req.uiTranNo_openAvDev  =  uiTranNo_openAvDev_remoteAssist;	//  m_var.uiTranNo_openAvDev;
	req.u.usRaType  =  CONST_usRaType_keyEvent;
	req.u.keyEvent.ucbDown  =  ucbDown;
	req.u.keyEvent.key  =  nChar;

	//
	//  2017/08/23
	if  (  m_var.addr.uiObjType  ==  CONST_objType_imGrp  )  {
				req.idInfo_imGrp_related.ui64Id  =  m_var.addr.idInfo.ui64Id;
	}


	//
	if  (  postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_outputTask,  0,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  (  char  *  )&req,  sizeof(  req  ),  0,  &idInfo_dst,  uiChannelType,  NULL,  0  )  )  traceLogA(  "postMsg2Mgr_mc failed"  );

	iErr  =  0;
//  errLabel:
	return  iErr;

}


 int  CDlgTalk::processKeyEvent(  UINT  nChar, DWORD  keyData  )
{
	int					iErr		=	-1;
	MC_VAR_isCli		*	pProcInfo	=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	unsigned  char		ucbDown		=  (  (  keyData  &  0x80000000l  )  ==  0  );

	//
	HWND  hCurTalk  =  m_hWnd;
	//
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hCurTalk  );
		if  (  !pCurVar  )  return  -1;
		//
		CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
		
		//
		HWND  hMgr  =  hCurTalk;
		DLG_TALK_var  *  pMgrVar  =  pCurVar;
		if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
			TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
			hMgr  =  pShadow->hMgr;
			pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
			if  (  !pMgrVar  )  goto  errLabel;
		}
		//
		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
		if  (  !pShadowMgr  )  goto  errLabel;
		//
		DLG_TALK_var  &m_var  =  *pCurVar;
	

	//
	if  (  !pShadowMgr->resourcesInfo.info_recv.bExists_remoteAssist  ||  pCurVar->av.peerZone.images.head.usCnt  !=  1  )  return  -1;

	//
	CAP_IMAGE			*	pImg			=	&pCurVar->av.peerZone.images.mems[0];
	if  (  !pImg->iW_org  ||  !pImg->iH_org  )  goto  errLabel;


	DWORD dwPos = GetMessagePos();

		long  lParam  =  dwPos;			
		POINT	point;
		point.x = GET_X_LPARAM(lParam); 
		point.y = GET_Y_LPARAM(lParam);

	POINT  tmpPnt  =  point;
	HWND  hCtrl  =  ::GetDlgItem(  m_hWnd,  IDC_STATIC_peerDesc  );
	::MapWindowPoints(  NULL,  hCtrl,  &tmpPnt,  1  );

	//
	if  (  tmpPnt.x  <  0  ||  tmpPnt.x  >  pImg->iW_org  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "processKeyEvent failed, tmpPnt.x not in img"  )  );
		#endif
		goto  errLabel;
	}
	if  (  tmpPnt.y  <  0  ||  tmpPnt.y  >  pImg->iH_org  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "processKeyEvent failed, tmpPnt.y not in img"  )  );
		#endif
		goto  errLabel;
	}



	//  if (  ::GetFocus() != m_hWnd) return 0;

	//  traceLogA(  "down %d",  down  );
	#ifdef  __DEBUG__  
			#ifndef  __WINCE__
			TCHAR  keyname[32];
			if  (  GetKeyNameText(  keyData,  keyname,  31  )  )  {
				traceLogA(  "Process key: %S, nChar %d, (keyData %04x): ", keyname,  nChar,  keyData  );
			}
			#endif
	#endif

	KEY_2_SEND  kas;
	kas  =  vk2Send(  nChar,  keyData  );    

	if  (  pProcInfo->av.video.bChannelReady  
		&&  !isQ2Warning(  &pProcInfo->mediaQ2,  CONST_uiQNodes_warningInterval_mediaQ  )		//  ±£³ÖÕâ¸ö±¨¾¯¼ä¸ôÖ÷ÒªÊÇÎªÁË·ÀÖ¹¶ÓÁÐ±»ÊÓÆµÊý¾ÝÕ¼Âú£¬µ¼ÖÂÎÞ·¨½«¿ØÖÆÐÅÏ¢·ÅÈë¶ÓÁÐ¡£
		)
	{		
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_LCONTROL  )  {
			sendKeyEvent(  CONST_qK_LCONTROL,  false  );
		}
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_LALT  )  {
			sendKeyEvent(  CONST_qK_LMENU,  false  );
		}
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_RCONTROL  )  {
			sendKeyEvent(  CONST_qK_RCONTROL,  false  );
		}
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_RALT  )  {
			sendKeyEvent(  CONST_qK_RMENU,  false  );
		}
		
		for  (  int  i  =  0;  kas.keycodes[i]  !=   CONST_voidKeyCode  &&  i  <  CONST_maxKeysPerKey;  i  ++  )  {
			 sendKeyEvent(  kas.keycodes[i],  ucbDown  );
		}
		
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_RALT  )  {
			sendKeyEvent(  CONST_qK_RMENU, true );
		}
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_RCONTROL  )  {
			sendKeyEvent(  CONST_qK_RCONTROL,  true  );
		}
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_LALT  )  {
			sendKeyEvent(  CONST_qK_LMENU,  false  );
		}
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_LCONTROL  )  {
			sendKeyEvent(  CONST_qK_CONTROL,  false  );
		}
		
	}


	iErr  =  0;
errLabel:
	return  iErr;
}



//
 int  CDlgTalk::resetKeyEvent(  )
{
	//
	HWND  hCurTalk  =  m_hWnd;
	//
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hCurTalk  );
		if  (  !pCurVar  )  return  -1;
		//
		CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
		
		//
		HWND  hMgr  =  hCurTalk;
		DLG_TALK_var  *  pMgrVar  =  pCurVar;
		if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
			TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
			hMgr  =  pShadow->hMgr;
			pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
			if  (  !pMgrVar  )  goto  errLabel;
		}
		//
		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
		if  (  !pShadowMgr  )  goto  errLabel;
		//
		DLG_TALK_var  &m_var  =  *pCurVar;
	

	//
	if  (  !pShadowMgr->resourcesInfo.info_recv.bExists_remoteAssist  ||  pCurVar->av.peerZone.images.head.usCnt  !=  1  )  return  -1;

	//
	CAP_IMAGE			*	pImg			=	&pCurVar->av.peerZone.images.mems[0];
	if  (  !pImg->iW_org  ||  !pImg->iH_org  )  goto  errLabel;


	DWORD dwPos = GetMessagePos();

		long  lParam  =  dwPos;			
		POINT	point;
		point.x = GET_X_LPARAM(lParam); 
		point.y = GET_Y_LPARAM(lParam);

	POINT  tmpPnt  =  point;
	HWND  hCtrl  =  ::GetDlgItem(  m_hWnd,  IDC_STATIC_peerDesc  );
	::MapWindowPoints(  NULL,  hCtrl,  &tmpPnt,  1  );

	//
	if  (  tmpPnt.x  <  0  ||  tmpPnt.x  >  pImg->iW_org  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "processKeyEvent failed, tmpPnt.x not in img"  )  );
		#endif
		goto  errLabel;
	}
	if  (  tmpPnt.y  <  0  ||  tmpPnt.y  >  pImg->iH_org  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "processKeyEvent failed, tmpPnt.y not in img"  )  );
		#endif
		goto  errLabel;
	}

		//
#ifdef  __DEBUG__
		traceLogA(  "Losing focus - cancelling modifiers"  );
#endif
	
	//
	sendKeyEvent(  CONST_qK_MENU,		false  );
	sendKeyEvent(  CONST_qK_CONTROL,	false  );
	sendKeyEvent(  CONST_qK_SHIFT,		false  );

	sendKeyEvent(  CONST_qK_LMENU,		false);
	sendKeyEvent(  CONST_qK_LCONTROL,	false);
	sendKeyEvent(  CONST_qK_LSHIFT,		false);
	sendKeyEvent(  CONST_qK_RMENU,		false);
	sendKeyEvent(  CONST_qK_RCONTROL,	false);
	sendKeyEvent(  CONST_qK_RSHIFT,		false);
	

errLabel:

	return  0;
}


 //
 BOOL  CDlgTalk::bRefreshBtns_talkerList(  )
 {
	 DLG_TALK_var  *  pCurVar  =  get_pm_var(  );

	 int  iSel  =  pCurVar->talkerList.iSelectItem;

	 
	 //
	if  (  iSel  >=  0  )  {
		//	
		::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_micOff  ),  TRUE  );				
	}
	else  {
		  ::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_micOff  ),  FALSE  );			
	}

	 return  TRUE;
 }

//
 BOOL  CDlgTalk::bRefreshBtns_listMembers(  )
 {
	 DLG_TALK_var  *  pCurVar  =  get_pm_var(  );
	 DLG_TALK_var  &m_var  =  *pCurVar;

	 //
	 int  iSel  =  m_var.listMembers.iSelectItem;


	 	//
	if  (  iSel  >=  0  )

	{		
		//m_var.selection.iSel  =  pNMLV->iItem;
		CListCtrl			*	pListCtrl								=	(  CListCtrl  *  )GetDlgItem(  IDC_LIST_members  );
		TCHAR					rowIdStr[64  +  1]						=	_T(  ""  );
		TCHAR					colName[128]							=	_T(  ""  );
		TCHAR					tBuf[128]								=	_T(  ""  );

		QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

		//
		HWND  hFrom  =  ::GetDlgItem(  m_hWnd,  IDC_LIST_members   );
		int  curnItem  =  -1;


		//		
		_sntprintf(  colName,  mycountof(  colName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_idStr  )  );						
		//if  (  getLvSelColContent(  hFrom,  &curnItem,  colName,  0,  0  )  )  goto  errLabel;			
		curnItem  =  iSel;
		if  (  getLvColContent(  m_hWnd,  hFrom,  curnItem,  colName,  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;

		//
		#ifdef  __DEBUG__
				traceLog(  _T(  "%s"  ),  tBuf  );
		#endif

		//
		char  buf[128]  =  "";
		myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
		QY_MESSENGER_ID  idInfo;
		idStr2Info(  buf,  &idInfo  );
		//
		pCurVar->confMgr_grpMemListInfo.idInfo_sel.ui64Id  =  idInfo.ui64Id;
		//
#if  0
		if  (  idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
			idInfo.ui64Id  =  0;
		}
#endif
		//
		pCurVar->confMgr_grpMemListInfo.idInfo_talkTo  =  idInfo;
		


		  }
	else  {
		  //
		  pCurVar->confMgr_grpMemListInfo.idInfo_sel.ui64Id  =  0;
		  //
		  pCurVar->confMgr_grpMemListInfo.idInfo_talkTo.ui64Id  =  0;
	}




	 //
	 //
	refreshTalkToInfo(  m_hWnd  );


	 //
		if  (  !pCurVar->confMgr_grpMemListInfo.idInfo_sel.ui64Id  )  {
			::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_permitToSpeak  ),  FALSE  );
			::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_noSpeaking  ),  FALSE  );
			}
		else  {
			  ::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_permitToSpeak  ),  TRUE  );			
			  ::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_noSpeaking  ),  TRUE  );			
		}

errLabel:

	 return  TRUE;
 }


//
BEGIN_MESSAGE_MAP(CDlgTalk, CDialog)
	//{{AFX_MSG_MAP(CDlgTalk)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_task, OnItemchangedLISTtask)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_members, OnDblclkLISTmembers)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_members, OnRclickLISTmembers)
	//}}AFX_MSG_MAP
	ON_MESSAGE(CONST_qyWm_comm, OnQyComm)
	ON_MESSAGE(CONST_qyWm_postComm, OnQyPostComm)
	ON_WM_SIZE()
	ON_WM_MOVING()
	ON_WM_INITMENUPOPUP()
#ifndef  __WINCE__
	ON_WM_DROPFILES()
#endif
	ON_WM_DESTROY()
	ON_WM_CLOSE()
#ifndef  __APP_qyMc_touchscreen__
#endif
	ON_COMMAND_RANGE(  ID_MENU_isCmd_min,  ID_MENU_isCmd_max,  OnIsCmd  )
	ON_UPDATE_COMMAND_UI_RANGE(  ID_MENU_isCmd_min,  ID_MENU_isCmd_max,  OnUpdateIsCmd  )

	ON_WM_ACTIVATE()
	ON_WM_NCACTIVATE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
#ifndef  __WINCE__
	//  ON_STN_DBLCLK(IDC_STATIC_peerDesc, OnStnDblclickStaticpeerdesc)
	//  ON_STN_DBLCLK(IDC_STATIC_meDesc, OnStnDblclickStaticmedesc)
#endif
	ON_WM_MOVE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_GETMINMAXINFO()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_DRAWITEM()
	ON_EN_CHANGE(IDC_EDIT_filter, &CDlgTalk::OnEnChangeEditfilter)
	ON_NOTIFY(NM_CLICK, IDC_talkerList, &CDlgTalk::OnNMClicktalkerlist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_talkerList, &CDlgTalk::OnLvnItemchangedtalkerlist)
	ON_BN_CLICKED(IDC_BUTTON_micOff, &CDlgTalk::OnBnClickedButtonmicoff)
	ON_NOTIFY(NM_CLICK, IDC_LIST_members, &CDlgTalk::OnNMClickListmembers)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_members, &CDlgTalk::OnLvnItemchangedListmembers)
	ON_BN_CLICKED(IDC_BUTTON_permitToSpeak, &CDlgTalk::OnBnClickedButtonpermittospeak)
	ON_BN_CLICKED(IDC_BUTTON_noSpeaking, &CDlgTalk::OnBnClickedButtonnospeaking)
	ON_BN_CLICKED(IDC_BUTTON_shareScreen, &CDlgTalk::OnBnClickedButtonsharescreen)
	ON_BN_CLICKED(IDC_BUTTON_controlDesktop, &CDlgTalk::OnBnClickedButtoncontroldesktop)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_NCPAINT()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTalk message handlers







int  chkAvBtnStatus(  DLG_TALK_var  *  pMgrVar,   CDlgInstantAssistant  *  pDlgIa   )
{
	int  iErr  =  -1;

	if  (  !pMgrVar  )  return  -1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	 

	//
	if  (  !pMgrVar->av.taskInfo.bTaskExists  )  {

	   int  iAvBtnStatus  =  getAvBtnStatus(  pMgrVar  );
	   if  (  iAvBtnStatus  <  0  )  goto  errLabel;
	   //
	   if  (  pDlgIa->m_var.iAvBtnStatus  !=  iAvBtnStatus  )  {
		   switch  (  iAvBtnStatus  )  {
				   case  CONST_avBtnStatus_av:
					     SetDlgItemText(  pDlgIa->m_hWnd,  pDlgIa->m_var.guiData.iIDC_BUTTON_av,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_startAV  )  );
						 break;
				   case  CONST_avBtnStatus_re_accept:
					     SetDlgItemText(  pDlgIa->m_hWnd,  pDlgIa->m_var.guiData.iIDC_BUTTON_av,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_re_accept  )  );
						 break;
				   default:
					     SetDlgItemText(  pDlgIa->m_hWnd,  pDlgIa->m_var.guiData.iIDC_BUTTON_av,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_err  )  );
						  break;
		   }
		   pDlgIa->m_var.iAvBtnStatus  =  iAvBtnStatus;
	   }
   }

	iErr  =  0;
errLabel:

	return  iErr;
}
 

//  2017/08/23
//
 int  refreshDlg_talk(  HWND  hDlgTalk,  void  *  pGuiDataTalkParam,  HWND  hDlg_instantAssistant  )
{
	int						iErr			=	-1;
	QY_MC				*	pQyMc			=   QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	
	FUNCS_for_isCliHelp	*	pFuncs			=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	DLG_guiData_talk	*	pGuiData		=	(  DLG_guiData_talk  *  )pGuiDataTalkParam;
	if  (  !pGuiData  )  return -1;
	CHelp_getDlgTalkVar		help_getDlgTalkVar;
	DLG_TALK_var		*	pDlgTalkVar		=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pDlgTalkVar  )  return  -1;
	//
	

	//
	HWND  hCurTalk  =  hDlgTalk;
	DLG_TALK_var  *  pCurTalkerVar  =  pDlgTalkVar;

	//
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	HWND  hMgr  =  hCurTalk;
	 DLG_TALK_var	*	pMgrVar  =  pCurTalkerVar;
	 if  (  !isTalkerShadowMgr(  pCurTalkerVar->addr  )  )  {
		 TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pCurTalkerVar->pShadowInfo;
		 if  (  !pTalkerShadow  )  goto  errLabel;
		 if  (  !IsWindow(  pTalkerShadow->hMgr  )  )  goto  errLabel;
		 hMgr  =  pTalkerShadow->hMgr;
		 pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr,  _T(  "refreshDlg_talk_ts, hMgr"  )  );
		 if  (  !pMgrVar  )  goto  errLabel;
	 }
	 if(  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
	 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	 if  (  !pShadowMgr  )  goto  errLabel;

	//
		//  2017/08/24
	 if  (  pShadowMgr->resourcesInfo.info_send.nScreens  >  0  )  {
		SetDlgItemText(  hCurTalk,  IDC_BUTTON_shareScreen,  _T(  "取消共享"  )  );
		}
	else  {
		  SetDlgItemText(  hCurTalk,  IDC_BUTTON_shareScreen,  _T(  "共享屏幕"  )  );
	}

	//
	QY_MESSENGER_ID  idInfo_peer  =  {0};
	if  (  !get_idInfo_peer_yz(  pMgrVar,  &idInfo_peer  )
		&&  bStarted_remoteAssist(  pShadowMgr,  &idInfo_peer  )  )
	{
		SetDlgItemText(  hCurTalk,  IDC_BUTTON_controlDesktop,  _T(  "取消控制"  )  );		
		}
	else  {
		  SetDlgItemText(  hCurTalk,  IDC_BUTTON_controlDesktop,  _T(  "控制桌面"  )  );		
	}



	//
	if  (  IsWindow(  pDlgTalkVar->hWnd_instantAssistant  )  )  hDlg_instantAssistant  =  pDlgTalkVar->hWnd_instantAssistant;
	else  if  (  !IsWindow(  hDlg_instantAssistant  )  )  return  0;



	//
	 CDlgInstantAssistant	*	pDlgIa  =  (  CDlgInstantAssistant  *  )CWnd::FromHandlePermanent(  hDlg_instantAssistant  );
	if  (  !pDlgIa  )  goto  errLabel;
	//  2017/01/08
	if  (  pDlgIa->m_var.guiData.param.hCurTalk  !=  hCurTalk  )  goto  errLabel;


	int  iIDD;
	int  iStatus_ia;
	BOOL	bMin;
	iIDD  =  getIDD_instantAssistant(  pDlgIa->m_var.guiData.hParent,  pDlgIa->m_var.guiData.param.iWndContentType_hParent,  hDlgTalk,  &iStatus_ia,  &bMin  );
	if  (  iIDD  <  0  )  goto  errLabel;

	if  (  iIDD  !=  pDlgIa->m_var.guiData.param.iIDD  )  {
		PostMessage(  pDlgIa->m_hWnd,  WM_CLOSE,  0,  0  );
		goto  errLabel;
	}



	//
	BOOL			bEnlarged	=	FALSE;
	//		
	//
	{
		int  iZoneObjsType  =  0;
		ZONE_objs  *  pZoneObjs  =  (  ZONE_objs  *  )pFuncs->pf_getZoneObjs(  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall,  iZoneObjsType  );
		if  (  pZoneObjs  )  {
			if  (  isZoneObjIndexValid(  pZoneObjs->iIndex_enlarged1  )  &&  pZoneObjs->mems[pZoneObjs->iIndex_enlarged1].hWndWallMem  ==  hDlgTalk  )  bEnlarged  =  TRUE;
		}
	}

	//
	HWND			hDlg		=	hDlg_instantAssistant;
	HDWP			hDwp;
	int				idc;
	int				x, y;
	int				iW  =  0,  iH  =  0;
	//  2015/06/07
	UINT			uFlags  =  0;
	//
	int				tmpX;
	BOOL			bMore				=	pCurTalkerVar->guiData.ucbShowMore;

	switch  (  pDlgIa->m_var.guiData.param.iIDD  )  {
			case  IDD_instantAssistant_msg:  {
				  BOOL	bWait		=	bDlgTalkWaitToAccept(  hDlgTalk  );
				  
				  //
				  hDwp  =  M_BeginDeferWindowPos(  4  );
				  if  (  hDwp  )  {		 
					  //  0
					  x  =  pDlgIa->m_var.oldLayout.iEdge_l;
					  y  =  pDlgIa->m_var.oldLayout.iEdge_t;
					  //
					  iW  =  pDlgIa->m_var.oldLayout.iW_btn;
					  iH  =  pDlgIa->m_var.oldLayout.iH_btn;					  	  
					  //					  
					  idc  =  IDC_BUTTON_sendFile;	
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
					  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;

					  idc  =  IDC_BUTTON_msgBox;										
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );			  
					  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;

					  idc  =  IDC_BUTTON_close;					
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
					  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;

					  idc  =  IDC_BUTTON_menuBar;					
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
					  //

					  M_EndDeferWindowPos(  hDwp  );				  

				  }
				  }
				  break;
			case  IDD_instantAssistant_start:  
			case  IDD_instantAssistant_start_wait:  {
				  BOOL	bWait		=	bDlgTalkWaitToAccept(  hDlgTalk  );
				  
				  //
				  hDwp  =  M_BeginDeferWindowPos(  16  );
				  if  (  hDwp  )  {		 
					  //  0
					  x  =  pDlgIa->m_var.oldLayout.iEdge_l;
					  y  =  pDlgIa->m_var.oldLayout.iEdge_t;
					  //
					  if  (  bWait  )  {
						  idc  =  IDC_BUTTON_av;
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
						  idc  =  IDC_BUTTON_av_accept;		
						  iW  =  pDlgIa->m_var.oldLayout.iW_btn;
						  iH  =  pDlgIa->m_var.oldLayout.iH_btn;
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );						    
						  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
						  }
					  else  {
						    idc  =  IDC_BUTTON_av;
							iW  =  pDlgIa->m_var.oldLayout.iW_btn;
						    iH  =  pDlgIa->m_var.oldLayout.iH_btn;					  
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
							x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
							idc  =  IDC_BUTTON_av_accept;
						    M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );						    
					  }
					  //  2019/05/06,SWP_SHOWWINDOW,  2016/03/30
					  idc  =  IDC_BUTTON_shareScreen;
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );						    
					  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;

					  //
					  idc  =  IDC_BUTTON_more;
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
					  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;

					  if  (  bWait  )  {
						  idc  =  IDC_BUTTON_av_deny;					  
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );						    
						  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
						  }
					  else  {
							idc  =  IDC_BUTTON_av_deny;					  
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );						    
					  }

					  //
					  if  (  !bWait  )  uFlags  =  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  );
					  else  uFlags  =  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
					  idc  =  pDlgIa->m_var.guiData.iIDC_BUTTON_close;
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  uFlags  );


					  //
					  x  =  pDlgIa->m_var.oldLayout.iEdge_l;
					  y  +=  iH  +  pDlgIa->m_var.oldLayout.iY_spacing;

					  //
					  if  (  bMore  )  {

						  //					  
						  idc  =  IDC_BUTTON_msgBox;										
						  iW  =  pDlgIa->m_var.oldLayout.iW_btn;
						  iH  =  pDlgIa->m_var.oldLayout.iH_btn;
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );			  
						  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
						  
						  //
						  idc  =  pDlgIa->m_var.guiData.iIDC_BUTTON_joinInBgWall;	//  IDC_BUTTON_shareScreen;	
						  if  (  pGuiData->bImGrp  )  {
							  iW  =  pDlgIa->m_var.oldLayout.iW_btn;
							  iH  =  pDlgIa->m_var.oldLayout.iH_btn;					  	  
							  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
							  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
							  }
						  else  {
							  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
						  }


						  //
						  if  (  !bWait  )  {
							  idc  =  IDC_BUTTON_offlineRes;				//  2017/01/09
							  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
							  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;

							  idc  =  IDC_BUTTON_sendFile;				//  2015/06/14
							  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
							  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;

							  idc  =  IDC_BUTTON_subtitles;				//  2013/04/06							
							  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
							  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
					  
							  idc  =  IDC_BUTTON_remoteVideo;
							  if  (  !pGuiData->bImGrp  )  {
								  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
								  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
								  }
							  else  {
								  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
							  }
							  //
							  idc  =  IDC_BUTTON_ptzPanel;		//  2013/02/15
							  if  (  !pGuiData->bImGrp  )  {
								  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
								  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
								  }
							  else  {
								  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
							  }
#if 0
						  idc  =  IDC_BUTTON_msg;
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
						  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
#endif
						  if (  bApp_ts_3d(  pQyMc  )  )  {
							  uFlags  =  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  );

							  //
							  x  =  pDlgIa->m_var.oldLayout.iEdge_l;
							  y  +=  iH  +  pDlgIa->m_var.oldLayout.iY_spacing;
							  }
						  else  {
							    uFlags  =  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
						  }							  
						  idc  =  IDC_BUTTON_rule;							
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  uFlags  );
						  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
						  idc  =  IDC_BUTTON_fullScreen;							
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  uFlags  );
						  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
						  idc  =  IDC_BUTTON_menuBar;							
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_HIDEWINDOW  );
						  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;

							  }					      
						  else  {
								idc  =  IDC_BUTTON_offlineRes;				//  2017/01/09
								M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
								idc  =  IDC_BUTTON_sendFile;
								M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
								idc  =  IDC_BUTTON_subtitles;				//  2013/04/06
							    M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
							    idc  =  IDC_BUTTON_remoteVideo;
								M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
								idc  =  IDC_BUTTON_ptzPanel;
								M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );

								//
								idc  =  IDC_BUTTON_rule;
								M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
								x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
								//
								idc  =  IDC_BUTTON_fullScreen;							
								M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
								x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
								idc  =  IDC_BUTTON_menuBar;							
								M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
								x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
						  }

						  
						  }
					  else  {
						    //
						    //					  
						    idc  =  IDC_BUTTON_msgBox;										
						    M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );			  
					
							idc  =  pDlgIa->m_var.guiData.iIDC_BUTTON_joinInBgWall;	//  IDC_BUTTON_shareScreen;	
						    M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );			  
				
						    //
							idc  =  IDC_BUTTON_offlineRes;				//  2017/01/09
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
							idc  =  IDC_BUTTON_sendFile;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
							idc  =  IDC_BUTTON_subtitles;				//  2013/04/06
						    M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
						    idc  =  IDC_BUTTON_remoteVideo;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
						    idc  =  IDC_BUTTON_ptzPanel;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
						    idc  =  IDC_BUTTON_rule;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
							idc  =  IDC_BUTTON_fullScreen;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
							idc  =  IDC_BUTTON_menuBar;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
					  }
					  M_EndDeferWindowPos(  hDwp  );
				  }

				  }
				  break;
				  			
#if  0
			case  IDD_instantAssistant_msg_min:  {
				  //
				  hDwp  =  M_BeginDeferWindowPos(  1  );
				  if  (  hDwp  )  {		 
					  //  0
					  x  =  pDlgIa->m_var.oldLayout.iEdge_l;
					  y  =  pDlgIa->m_var.oldLayout.iEdge_t;
					  //
					  iW  =  pDlgIa->m_var.oldLayout.iW_btn;
					  iH  =  pDlgIa->m_var.oldLayout.iH_btn;

					  idc  =  IDC_BUTTON_close;					
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );		

					  M_EndDeferWindowPos(  hDwp  );
				  }

				  }
				  break;
#endif
#if  0
			case  IDD_instantAssistant_start_min:  
			case  IDD_instantAssistant_start_wait_min:  {
				  BOOL	bWait  =  bDlgTalkWaitToAccept(  hDlgTalk  );
				  //
				  hDwp  =  M_BeginDeferWindowPos(  4  );
				  if  (  hDwp  )  {		 
					  //  0
					  x  =  pDlgIa->m_var.oldLayout.iEdge_l;
					  y  =  pDlgIa->m_var.oldLayout.iEdge_t;
					  //
					  if  (  bWait  )  {
						  idc  =  IDC_BUTTON_av;
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
						  idc  =  IDC_BUTTON_av_accept;
						  iW  =  pDlgIa->m_var.oldLayout.iW_btn;
						  iH  =  pDlgIa->m_var.oldLayout.iH_btn;
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );						    
						  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
						  }
					  else  {
						    idc  =  IDC_BUTTON_av;
							iW  =  pDlgIa->m_var.oldLayout.iW_btn;
						    iH  =  pDlgIa->m_var.oldLayout.iH_btn;					  
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
							x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
							idc  =  IDC_BUTTON_av_accept;
						    M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );						    
					  }

					  if  (  bWait  )  {
						  idc  =  IDC_BUTTON_av_deny;					  
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );						    
						  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
						  }
					  else  {
							idc  =  IDC_BUTTON_av_deny;					  
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );						    
					  }

					  if  (  !bWait  )  {
						  idc  =  IDC_BUTTON_close;					
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );		
						  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
					  }
					  else  {
							  idc  =  IDC_BUTTON_close;					
							  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );		
					  }
					  //
					  M_EndDeferWindowPos(  hDwp  );
				  }

				  }
				  break;
#endif
			case  IDD_instantAssistant_av:  {

				  //
				  hDwp  =  M_BeginDeferWindowPos(  19  );
				  if  (  hDwp  )  {		 
					  //  0
					  x  =  pDlgIa->m_var.oldLayout.iEdge_l;
					  y  =  pDlgIa->m_var.oldLayout.iEdge_t;
					  //
					  idc  =  pDlgIa->m_var.guiData.iIDC_request;
					  iW  =  pDlgIa->m_var.oldLayout.iW_btn_request;  iH  =  pDlgIa->m_var.oldLayout.iH_btn;
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_SHOWWINDOW  );
					  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;  

					  //  2019/05/06
					  idc  =  IDC_BUTTON_shareScreen;
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
					  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;

					  idc  =  IDC_BUTTON_more;
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
					  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;  

					  idc  =  IDC_BUTTON_av;
					  iW  =  pDlgIa->m_var.oldLayout.iW_btn;
					  iH  =  pDlgIa->m_var.oldLayout.iH_btn;					  
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
					  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;  

					 if  (  !bMore  )  {
						  idc  =  IDC_BUTTON_msgBox;							
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
						  idc  =  IDC_BUTTON_joinInBgWall;						
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );						  	
						  idc  =  pDlgIa->m_var.guiData.iIDC_talkerList;
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
						  idc  =  pDlgIa->m_var.guiData.iIDC_STATIC_status;
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
						  idc  =  pDlgIa->m_var.guiData.iIDC_BUTTON_offlineRes;
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
						  // idc  =  IDC_BUTTON_shareScreen;
						  // M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
						  idc  =  IDC_BUTTON_sendFile;				//  2015/06/14
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
						  idc  =  IDC_BUTTON_subtitles;				//  2013/04/06
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
						  idc  =  IDC_BUTTON_remoteVideo;		//  2013/02/15
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
						  idc  =  IDC_BUTTON_ptzPanel;			//  2013/02/15
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
						  idc  =  IDC_BUTTON_rule;
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
#if 0
						  idc  =  IDC_BUTTON_msg;
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
#endif
						  idc  =  pDlgIa->m_var.guiData.iIDC_BUTTON_layoutType;
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
						  idc  =  IDC_BUTTON_shareMediaFile;
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );

						  idc  =  IDC_BUTTON_menuBar;							
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );						  
						  
						  //						  			
						  idc  =  IDC_BUTTON_fullScreen;
						  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );						  
						  

					  }
					  else  {						    
						    x  =  pDlgIa->m_var.oldLayout.iEdge_l;
							y  =  pDlgIa->m_var.oldLayout.iEdge_t  +  pDlgIa->m_var.oldLayout.iH_btn  +  pDlgIa->m_var.oldLayout.iY_spacing;



							//
							idc  =  pDlgIa->m_var.guiData.iIDC_talkerList;
							iW  =  pDlgIa->m_var.oldLayout.iW_talkerList;  iH  =  pDlgIa->m_var.oldLayout.iH_talkerList + pDlgIa->m_var.oldLayout.iY_spacing;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_SHOWWINDOW  );
							y  +=  iH  +  pDlgIa->m_var.oldLayout.iY_spacing;  

							idc  =  pDlgIa->m_var.guiData.iIDC_STATIC_status;
							iW  =  pDlgIa->m_var.oldLayout.iW_status;  iH  =  pDlgIa->m_var.oldLayout.iH_status;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
							y  +=  iH  +  pDlgIa->m_var.oldLayout.iY_spacing;

							//
							x  =  pDlgIa->m_var.oldLayout.iEdge_l  +  pDlgIa->m_var.oldLayout.iW_btn  +  pDlgIa->m_var.oldLayout.iX_spacing;
							y  =  pDlgIa->m_var.oldLayout.iEdge_t  +  pDlgIa->m_var.oldLayout.iH_btn  +  pDlgIa->m_var.oldLayout.iY_spacing;
							iW  =  pDlgIa->m_var.oldLayout.iW_btn;
							iH  =  pDlgIa->m_var.oldLayout.iH_btn;


							//
							idc  =  IDC_BUTTON_msgBox;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
							x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;  
							
							//
							idc  =  IDC_BUTTON_joinInBgWall;
							if  (  pGuiData->bImGrp  )  {
								iW  =  pDlgIa->m_var.oldLayout.iW_btn;
								iH  =  pDlgIa->m_var.oldLayout.iH_btn;					  	  
								M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
								x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
								}		
							else  {						  
								  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
					  
							}

							//
							idc  =  pDlgIa->m_var.guiData.iIDC_BUTTON_offlineRes;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );	
							x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;							

							idc  =  IDC_BUTTON_shareScreen;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );	
							x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
							
							idc  =  IDC_BUTTON_sendFile;				//  2015/06/14
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );	
							x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;

							idc  =  IDC_BUTTON_subtitles;				//  2013/04/06
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
							x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;		  

							idc  =  IDC_BUTTON_rule;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
							x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;

							//
							x  =  pDlgIa->m_var.oldLayout.iEdge_l  +  pDlgIa->m_var.oldLayout.iW_btn  +  pDlgIa->m_var.oldLayout.iX_spacing;
							y  =  pDlgIa->m_var.oldLayout.iEdge_t  +  pDlgIa->m_var.oldLayout.iH_btn * 2  +  pDlgIa->m_var.oldLayout.iY_spacing * 2;
							iW  =  pDlgIa->m_var.oldLayout.iW_btn;
							iH  =  pDlgIa->m_var.oldLayout.iH_btn;

						    idc  =  IDC_BUTTON_remoteVideo;
						    if  (  !pGuiData->bImGrp  )  {
								M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
								x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
							}
							else  {
								M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
							}

						    idc  =  IDC_BUTTON_ptzPanel;			//  2013/02/15
						    if  (  !pGuiData->bImGrp  )  {
								M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
								x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
							}
							else  {
								M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
							}

							if (  bApp_ts_3d(  pQyMc  )  )  {
								uFlags  =  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  );
								}
							else  {
								  uFlags  =  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  );								
							}
							idc  =  pDlgIa->m_var.guiData.iIDC_BUTTON_layoutType;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );	
							x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;							

							idc  =  IDC_BUTTON_shareMediaFile;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );	
							x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;							
#if 0
							idc  =  IDC_BUTTON_nonexclusive;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
							x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;  
							idc  =  IDC_BUTTON_confMgr;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
							x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;  
#endif

							idc  =  IDC_BUTTON_menuBar;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_HIDEWINDOW  );	
							//x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;
							
							idc  =  IDC_BUTTON_fullScreen;
							M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );	
							x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;

						
					  }

					  //

					  idc  =  pDlgIa->m_var.guiData.iIDC_BUTTON_close;
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
					  
					  M_EndDeferWindowPos(  hDwp  );
				  }


				  }
				  break;

#if  0
			case  IDD_instantAssistant_av_min:  {

				  //
				  hDwp  =  M_BeginDeferWindowPos(  3  );
				  if  (  hDwp  )  {		 
					  //  0
					  x  =  pDlgIa->m_var.oldLayout.iEdge_l;
					  y  =  pDlgIa->m_var.oldLayout.iEdge_t;
					  //
					  idc  =  pDlgIa->m_var.guiData.iIDC_request;
					  iW  =  pDlgIa->m_var.oldLayout.iW_btn_request;  iH  =  pDlgIa->m_var.oldLayout.iH_btn;
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_SHOWWINDOW  );
					  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;  

					  idc  =  IDC_BUTTON_av;
					  iW  =  pDlgIa->m_var.oldLayout.iW_btn;
					  iH  =  pDlgIa->m_var.oldLayout.iH_btn;					  
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
					  x  +=  iW  +  pDlgIa->m_var.oldLayout.iX_spacing;  
					  
					  //
					  idc  =  IDC_BUTTON_close;											
					  M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );

					  //
					  M_EndDeferWindowPos(  hDwp  );
				  }

				  }
				  break;
#endif
			default:
					break;
	}

	//
	TCHAR  tBuf[128]  =  _T(  ""  );
	//
	if  (  pMgrVar->av.taskInfo.bTaskExists  )  {
		SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_av,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cancelAV  )  );
	}
	//
#if  0
	if  (  pMgrVar->av.taskInfo.bTaskExists  &&  pMgrVar->av.taskInfo.ucbStarter  )  {		
		//
		if  (  pMgrVar->m_layout.ucbShowBgWall_starter  )  {			
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hideBgWall  )  );								   
			}
		else  {
			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_showBgWall1  )  );			
		}
		}
	else  {
		  if  (  canJoinInBgWall(  hMgr,  pMgrVar  )  )  {		
			  //
			  safeTcsnCpy(  getResStr(  0,  &pQyMc->cusRes,  	CONST_resId_notJoinInBgWall  ),  tBuf,  mycountof(  tBuf  )  ); 	
			  }
		  else  {
				safeTcsnCpy(  getResStr(  0,  &pQyMc->cusRes,  	CONST_resId_joinInBgWall  ),  tBuf,  mycountof(  tBuf  )  ); 						   	
		  }					
	}
#endif
	safeTcsnCpy(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_bgWall  ),  tBuf,  mycountof(  tBuf  )  );
	SetDlgItemText(  pDlgIa->m_hWnd,  pDlgIa->m_var.guiData.iIDC_BUTTON_joinInBgWall,  tBuf  );



	//
	if  (  pShadowMgr->resourcesInfo.info_send.nScreens  >  0  )  SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_shareScreen,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cancelScreenSharing  )  );
	else  SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_shareScreen,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_screenSharing  )  );
	
	//  SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_msgBox,  pDlgTalkVar->guiData.ucbShowMsgBox  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hideMsgBox  )  :  getResStr(  0, &pQyMc->cusRes,  CONST_resId_showMsgBox  )  );
	if  (  pDlgTalkVar->guiData.snmpbShowMsgBox  )  SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_msgBox,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_resetMsgBox  )  );
	else  {
		  SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_msgBox,  dlgTalk_bMsgBoxShown(  hDlgTalk  )  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hideMsgBox  )  :  getResStr(  0, &pQyMc->cusRes,  CONST_resId_showMsgBox  )  );
	}
	
	if  ( IsWindow(  pDlgTalkVar->ptzControl.hWnd_ptzControl  )  )  SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_ptzPanel,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hidePtz  )  );
	else  SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_ptzPanel,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ptz  )  );

	if  ( IsWindow(  pDlgTalkVar->subtitles.hWnd_subtitles  )  )  SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_subtitles,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hideSubtitles  )  );
	else  SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_subtitles,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_subtitles  )  );

	//  if  (  pDlgIa->m_var.guiData.param.iIDD  ==  IDD_instantAssistant_av  )  
	//SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_confMgr,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_confMgr  )  );
	SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_more,  pDlgTalkVar->guiData.ucbShowMore  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hideMore  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_more  )  );

	//  2017/09/01
	if  (  pCurTalkerVar->guiData.ucbShowImGrpMems  )  SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_memList,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ucbHideImGrpMems  )  );  //_T(  "Hide memList"  )  );
	else  SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_memList,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ucbShowImGrpMems  )  );  //_T(  "Show memList"  )  );


	//  2015/11/28
	{
		HWND		hDlgWalls	=	pDlgIa->m_var.guiData.hParent;				 
		int			iWndContentType_hDlgWalls  =  pDlgIa->m_var.guiData.param.iWndContentType_hParent;	
		int			iZoneObjsType  =  0;
		
		//
		if  (  pFuncs->pf_bFullScreen_wnd(  hDlgWalls,  iWndContentType_hDlgWalls  )  )  {			
			SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_fullScreen,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_endFullScreen  )  );					  
			}
		else  {
			  SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_fullScreen,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fullScreen  )  );					  
		}
	}

	//
	SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_2ndScreen,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_2ndScreen  )  );  //  _T(  "Show 2nd screen"  )  );

	//
	SetDlgItemText(  pDlgIa->m_hWnd,  IDC_BUTTON_localVideo,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_localVideo  )  );
	

	//
	iErr  =  0;
errLabel:


	return  iErr;
}








//  #endif








 //  2013/03/04
 int  mySizeAllControls_dlgTalk_tools(  HWND  hDlg,  DLG_TALK_var  &  m_var,  DLG_talk_layout  *  pLayout,  RECT  *  pRect  )
{
#ifdef  __DEBUG__
		traceLog(  _T(  "mySizeAllControls_dlgTalk_tools called"  )  );
#endif

#ifndef  __SUPPORT_HTMLEDIT__
		return  -1;
#else
	 int			iErr							=	-1;
	 HDWP			hDwp;
	 RECT			rc;
	 //
	 int			iEdge_l							=	CONST_edge_l_dlgTalk_wall;
	 int			iEdge_t							=	CONST_edge_l_dlgTalk_wall;
	 int			iEdge_r							=	CONST_edge_l_dlgTalk_wall;
	 int			iEdge_b							=	CONST_edge_l_dlgTalk_wall;
	 //
	 int			iX_spacing						=	CONST_iX_spacing_dlgTalk_wall;			//  
	 int			iY_spacing						=	CONST_iY_spacing_dlgTalk_wall;			//  
	 
	 //
#ifdef  __APP_qyMc__
		if  (  !m_var.ucbOnGlobalVWall  )  {			
			iEdge_l							=	CONST_edge_l_dlgTalk_desktop;
			iEdge_t							=	CONST_edge_t_dlgTalk_desktop;
			iEdge_r							=	CONST_edge_l_dlgTalk_desktop;
			iEdge_b							=	CONST_edge_b_dlgTalk_desktop;
			//
			iX_spacing						=	CONST_iX_spacing_dlgTalk_desktop;			//  
			iY_spacing						=	CONST_iY_spacing_dlgTalk_desktop;			//  
		}
#endif


	 //
	 int			iW_dlgDesc						=	0;
	 int			iH_dlgDesc						=	0;
	 //
	 int			iW_talkerList					=	10;
	 int			iH_talkerList					=	10;
	 //
	 int			iW_talkerList_micOff			=	10;
	 int			iH_talkerList_micOff			=	10;
	 //
	 int			iW_memberList					=	CONST_iW_memberList;
	 int			iH_memberList					=	10;
	 //
	 int			iW_memberList_static_filter		=	10;
	 int			iH_memberList_static_filter		=	10;
	 //
	 int			iW_memberList_edit_filter		=	10;
	 int			iH_memberList_edit_filter		=	10;
	 //
	 int			iW_memberList_permitToSpeak		=	10;
	 int			iH_memberList_permitToSpeak		=	10;
	 //
	 int			iW_memberList_noSpeaking		=	10;
	 int			iH_memberList_noSpeaking		=	10;	 
	 //
 	 int			iW_taskList						=	10;
	 int			iH_taskList						=	10;
	 //
	 int			iW_instantStatus				=	50;
	 int			iH_instantStatus				=	15;				//  20;		//  2012/05/17, 因为gps墙上小talk的缘故，希望talk标签小一点
	 //
	 int			iW_recentMsgList				=	10;
	 int			iH_recentMsgList				=	10;
	 //
	 int			iW_input						=	10;
	 int			iH_input						=	48;				//  24; 因为超过1行时出现的滑动条会占用这个空间,必须多留1行才可以容纳滑动条
	 //
	 int			iW_ptz							=	0;				//  2012/09/05
	 int			iH_ptz							=	0;
	 BOOL			bShowPtz						=   dlgTalk_bPtzShown(  hDlg  );
	 //
	 int			iW_subtitles					=   0;				//  2013/04/05
	 int			iH_subtitles					=	0;
	 BOOL			bShowSubtitles					=	dlgTalk_bSubtitlesShown(  hDlg  );			//  TRUE;				//  
	 BOOL			bShowOfflineRes					=   dlgTalk_bOfflineResShown(  hDlg  );			//  2015/08/01
	 //
 	 int			iW_peerDesc						=	10;
	 int			iH_peerDesc						=	10;
	 //
	 int			iW_meDesc						=	0;				//  2008/03/27
	 int			iH_meDesc						=	0;
	 //
	 int			iW_otherDesc					=	0;
	 int			iH_otherDesc					=	0;
	 //
	 int			iW_shareScreen					=	0;
	 int			iH_shareScreen					=	0;
	 
	 //
	 int			x, y;
	 //  CWnd		*	pWnd;
	 HWND			hWnd;
	 int			idc;
	 //	 
	 int			iW,  iH;
	 int			tmpiX,tmpiY;

	 //
	 MC_VAR_isCli	*	pProcInfo			=	QY_GET_procInfo_isCli(  );

	 HWND				hCtrl;
	 UINT			uFlags;

	 //
	 HWND  hMgr  =  hDlg;
	 DLG_TALK_var  *  pMgrVar  =  &m_var;
	 CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	 TALKER_shadow_mgr  *  pTalkerShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;	 		 
	 //	
	 if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {	
		 TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
		 if  (  !pShadow  )  goto  errLabel;		 
		 hMgr  =  pShadow->hMgr;
		 pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		 if  (  !pMgrVar  )  goto  errLabel;
		 pTalkerShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	 }
	 if  (  !pTalkerShadowMgr  )  goto  errLabel;  

	 
	 //
	 if  (  !pLayout  )  return  -1;
	 if  (  !pRect  )  return  -1;

	 //
	 idc  =  m_var.guiData.iIDC_STATIC_dlgDesc;
	 hCtrl  =  GetDlgItem(  hDlg,  idc  );
	 if  (  !hCtrl  )  goto  errLabel;
	 

	 //
	 //  GetClientRect(  hDlg,  &rc  );
	 rc  =  *pRect;

	 //
	 DLG_talk_layout  &     layout  =  *pLayout;
#if  0
	 //
	 dlgTalk_calculateLayout(  hDlg,  &m_var,  NULL,  &layout  );
#endif
	 //memcpy(  &layout,  pLayout,  sizeof(  layout  )  );

	 //
	 iW_memberList  =  layout.iW_memberList;
	 iW_talkerList  =  layout.iW_memberList;
	 //
	 iW_taskList  =  layout.iW_taskList;
	 iW_recentMsgList  =  iW_taskList;
	 iW_instantStatus  =  iW_recentMsgList;
	 iW_input  =  iW_recentMsgList;
	 //
	 iW_ptz  =  layout.iW_ptz;
	 //
	 iW_subtitles  =  layout.iW_subtitles;
	 //
	 iW  =  rc.right  -  rc.left  -  iEdge_l  -  iEdge_r;


	 //
	 iW_peerDesc  =  iW  -  iW_taskList  -  iW_memberList  -  iW_ptz  -  iW_subtitles  -  layout.iW_offlineRes;

	 //  2011/03/03
	 if  (  m_var.guiData.ucbShowDlgDesc  )  {
		 iW_dlgDesc  =  iW;
		 iH_dlgDesc  =  CONST_iH_dlgDesc;	//  iH_instantStatus;
	 }


	 //
	 //  memberList
	 iH  =  rc.bottom  -  rc.top  -  iEdge_t  -  iEdge_b  -  iH_dlgDesc;
	 if  (  iH  <  0  )  iH  =  0;

	 //
	 int  tmp_iH1  =  iH;

	 //
	 if  (  bShowPtz  )  iH_ptz  =  iH;
	 else  iH_ptz  =  0;
	 //
	 if  (  bShowSubtitles  )  iH_subtitles  =  iH;
	 else  iH_subtitles  =  0;
	 //
	 iW_talkerList_micOff  =  100;
	 iH_talkerList_micOff  =  20;
	 //
	 iW_memberList_static_filter  =  50;
	 iH_memberList_static_filter  =  20;
	  //
	 iW_memberList_edit_filter  =  100;
	 iH_memberList_edit_filter  =  20;
	 //
	 iW_memberList_permitToSpeak  =  80;
	 iH_memberList_permitToSpeak  =  20;
	 //
	 iW_memberList_noSpeaking  =  iW_memberList_permitToSpeak;
	 iH_memberList_noSpeaking  =  iH_memberList_permitToSpeak;
	 
	 //  2017/08/22
	 iW_shareScreen  =  60;
	 iH_shareScreen  =  pLayout->iH_shareScreen;

	 //
	 int  iY_space_talkerList_micOff  =  0;	//  1;
	 //
	 int  iH_talkerList_memberList  =  iH  -  iH_talkerList_micOff  -  2  *  iY_space_talkerList_micOff  -  iH_memberList_static_filter  -  2  *  iY_space_talkerList_micOff  -  iH_memberList_permitToSpeak  -  2  *  iY_space_talkerList_micOff;
	 if  (  iH_talkerList_memberList  <  0  )  iH_talkerList_memberList  =  0;
	 //
	 iH_talkerList  =  iH_talkerList_memberList  /  3;
	 iH_memberList  =  iH_talkerList_memberList  /  3  *  2;;

	 //  

	 if  (  pLayout->iW_taskList  )  {
	 //  iH_input
	 iH  =  iH  -  (  iH_input  );
	 if  (  iH  <  0  )  iH  =  0;

	 iH  -=  iH_instantStatus;
	 if  (  iH  <  0  )  iH  =  0;

	 //
	 iH_recentMsgList  =  iH  /  2;
	 iH_taskList  =    iH  -  iH_recentMsgList;
	 if  (  iH_taskList  <  0  )  iH_taskList  =  0;
	 }
	 else  {
		 iH_input  =  0;
		 iH_recentMsgList  =  0;
		 iH_instantStatus  =  0;
		 iH_taskList  =  0;
	 }


	 //  
	 {
		 hDwp  =  M_BeginDeferWindowPos(  1  );
		 if  (  hDwp  )  {		 
			 //  0
			 x  =  iEdge_l;
			 y  =  rc.bottom  -  iH_dlgDesc;
			 //
			 idc  =  IDC_STATIC_dlgDesc;
			 if  (  !m_var.guiData.ucbShowDlgDesc  )  {
				 iW  =  0;  iH  =  0;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
				 }
			 else  {
				   iW  =  iW_dlgDesc;  iH  =  iH_dlgDesc;
				   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
			 }
			 //
			 M_EndDeferWindowPos(  hDwp  );
		 }
	 }

	 //
	 {
		 hDwp  =  M_BeginDeferWindowPos(  7  );	
		 if  (  !hDwp  )  {	 	 
			 goto  errLabel;	 
		 }

		 //  1st
		 x  =  iEdge_l;
		 y  =  iEdge_t;
		 		
		 //
		 if  (  !m_var.guiData.ucbShowImGrpMems  )  {  //  所有都隐藏
			 	
			   //
			   idc  =  IDC_talkerList;
			   iW  =  0;  iH  =  0;
			   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
		 		 
			   //		 
			   idc  =  IDC_BUTTON_micOff;
			   iW  =  0;  iH  =  0;
			   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
			   		 
			   //		 
			   idc  =  IDC_LIST_members;
			   iW  =  0;  iH  =  0;
			   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
			   
			   //	
			   idc  =  IDC_STATIC_filter;
			   iW  =  0;  iH  =  0;
			   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
			   		 
			   //	
			   idc  =  IDC_EDIT_filter;
			   iW  =  0;  iH  =  0;
			   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
			   		 
			   //		
			   idc  =  IDC_BUTTON_permitToSpeak;
			   iW  =  0;  iH  =  0;
			   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );

			   //
			   idc  =  IDC_BUTTON_noSpeaking;
			   iW  =  0;  iH  =  0;
			   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );

			   			   
			   }		 
		 else  if  (  !pMgrVar->av.taskInfo.bTaskExists  )  {  //  没有会议				 
				 		 
			   //		 
			   idc  =  IDC_talkerList;
			   iW  =  0;  iH  =  0;
			   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
		 		 
			   //		 
			   idc  =  IDC_BUTTON_micOff;
			   iW  =  0;  iH  =  0;
			   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
			   		 
			   //		 
			   idc  =  IDC_LIST_members;	
			   iW  =  iW_memberList;  iH  =  tmp_iH1;			 
			   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
			 
			   //	
			   idc  =  IDC_STATIC_filter;
			   iW  =  0;  iH  =  0;
			   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
			   		 
			   //		 
			   idc  =  IDC_EDIT_filter;
			   iW  =  0;  iH  =  0;
			   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
			   		 
			   //		 
			   idc  =  IDC_BUTTON_permitToSpeak;
			   iW  =  0;  iH  =  0;
			   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );

			   //		 
			   idc  =  IDC_BUTTON_noSpeaking;
			   iW  =  0;  iH  =  0;
			   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );

		    }		
		 else  {
			   if  (  pMgrVar->av.taskInfo.ucbVideoConference  				 
					 &&  (  pTalkerShadowMgr->av.ucbMeConfMgr  ||  pMgrVar->av.taskInfo.ucbStarter  )  )		 			 				
			   {				 
				 //
				 idc  =  IDC_talkerList;			 
				 iW  =  iW_talkerList;  iH  =  iH_talkerList;			 
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
		 			 
				 //		
				 idc  =  IDC_BUTTON_micOff;
				 tmpiX  =  x;				
				 x  +=  (  iW_talkerList  -  iW_talkerList_micOff  )  /  2;			 
				 y  +=  iH  +  iY_space_talkerList_micOff;
				 iW  =  iW_talkerList_micOff;  iH  =  iH_talkerList_micOff;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
				 x  =  tmpiX;
		 
				 //
				 idc  =  IDC_LIST_members;
				 y  +=  iH  +  iY_space_talkerList_micOff;
				 iW  =  iW_memberList;  iH  =  iH_memberList;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );

				 //
				 idc  =  IDC_STATIC_filter;
				 y  +=  iH  +  iY_space_talkerList_micOff;
				 iW  =  iW_memberList_static_filter;  iH  =  iH_memberList_static_filter;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );

				 //
				 idc  =  IDC_EDIT_filter;
				 tmpiX  =  x;
				 x  +=  iW;
				 iW  =  iW_memberList_edit_filter;  iH  =  iH_memberList_edit_filter;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
				 x  =  tmpiX;

				 //
				 idc  =  IDC_BUTTON_permitToSpeak;
				 tmpiX  =  x;
				 x  +=  (  iW_memberList  -  iW_memberList_permitToSpeak  *  2  )  /  3;
				 y  +=  iH  +  iY_space_talkerList_micOff;
				 iW  =  iW_memberList_permitToSpeak;  iH  =  iH_memberList_permitToSpeak;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
				 
				 //
				 idc  =  IDC_BUTTON_noSpeaking;
				 x  +=  iW_memberList_permitToSpeak  +  (  iW_memberList  -  iW_memberList_permitToSpeak  *  2  )  /  3;
				 iW  =  iW_memberList_noSpeaking;  iH  =  iH_memberList_noSpeaking;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
				 x  =  tmpiX;

				 
				 }
				
			   else  {
				 //
				 idc  =  IDC_talkerList;			 
				 iW  =  iW_talkerList;  iH  =  iH_talkerList;			 
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
		 			 
				 //		
				 idc  =  IDC_BUTTON_micOff;
				 tmpiX  =  x;				
				 x  +=  (  iW_talkerList  -  iW_talkerList_micOff  )  /  2;			 
				 y  +=  iH  +  iY_space_talkerList_micOff;
				 iW  =  iW_talkerList_micOff;  iH  =  iH_talkerList_micOff;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
				 x  =  tmpiX;
		 
				 //
				 idc  =  IDC_LIST_members;
				 y  +=  iH  +  iY_space_talkerList_micOff;
				 iW  =  iW_memberList;  iH  =  iH_memberList;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );

				 //
				 idc  =  IDC_STATIC_filter;
				 y  +=  iH  +  iY_space_talkerList_micOff;
				 iW  =  iW_memberList_static_filter;  iH  =  iH_memberList_static_filter;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );

				 //
				 idc  =  IDC_EDIT_filter;
				 tmpiX  =  x;
				 x  +=  iW;
				 iW  =  iW_memberList_edit_filter;  iH  =  iH_memberList_edit_filter;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
				 x  =  tmpiX;

				 //
				 idc  =  IDC_BUTTON_permitToSpeak;
				 iW  =  0;  iH  =  0;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );

				 //
				 idc  =  IDC_BUTTON_noSpeaking;
				 iW  =  0;  iH  =  0;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
		 
				
			   }
				
		 }		 
			
		 //
		 M_EndDeferWindowPos(  hDwp  );
		 
	}
		 


		
	{

		 hDwp  =  M_BeginDeferWindowPos(  4  );
		 if  (  !hDwp  )  goto  errLabel;


		 //  2nd
		 if  (  !m_var.guiData.ucbShowImGrpMems  )  {
			 x  =  iEdge_l;
			 }
		 else  {
			   x  =  iEdge_l  +  iW_memberList  +  iX_spacing;			   
		 }		 
		 y  =  iEdge_t;		//  +  iH_dlgDesc;		 		 
		 //
		 m_var.msgTool.rc.left  =  x;
		 m_var.msgTool.rc.top  =  y;
		 m_var.msgTool.rc.right  =  x  +  iW_taskList;
		 iH  =  rc.bottom  -  rc.top  -  iEdge_t  -  iEdge_b  -  iH_dlgDesc;
		 if  (  iH  <  0  )  iH  =  0;
		 m_var.msgTool.rc.bottom  =  y  +  iH;
		 //
		 //  2014/01/27
		 idc  =  m_var.guiData.iIDC_STATIC_msgTool;
		 iW  =  iW_taskList;  
		 //  uFlags  =  SWP_NOZORDER  |  SWP_SHOWWINDOW;
		 uFlags  =  SWP_NOZORDER  |  SWP_HIDEWINDOW;
		 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  uFlags  );


		 //  6, 2012/09/05
		 y  =  iEdge_t;
		 idc  =  m_var.guiData.iIDC_STATIC_ptz;
		 x  =  iEdge_l  +  iW_memberList  +  iW_recentMsgList;
		 iW  =  iW_ptz;  iH  =  iH_ptz;
		 if  (  bShowPtz  )  
		 {
			 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_SHOWWINDOW  );
		 }
		 else  
		 {
			 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
		 }
		 //  7, 2013/04/05
		 y  =  iEdge_t;
		 idc  =  m_var.guiData.iIDC_STATIC_subtitles;
		 x  =  iEdge_l  +  iW_memberList  +  iW_recentMsgList  +  iW_ptz;
		 iW  =  iW_subtitles;  iH  =  iH_subtitles;
		 if  (  bShowSubtitles  )  
		 {
			 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_SHOWWINDOW  );
		 }
		 else  
		 {
			 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
		 }

		 //  8,  2015/08/01
		 idc  =  m_var.guiData.iIDC_STATIC_offlineRes;
		 x  +=  iW;
		 iW  =  layout.iW_offlineRes;
		 iH  =  rc.bottom  -  rc.top  -  iEdge_t  -  iEdge_b  -  iH_dlgDesc;
		 if  (  bShowOfflineRes  )  
		 {
			 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_SHOWWINDOW  );
		 }
		 else  
		 {
			 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
		 }

		 //
		 M_EndDeferWindowPos(  hDwp  );
	 }

	//  2017/08/21
	{
		 hDwp  =  M_BeginDeferWindowPos(  4  );
		 if  (  hDwp  )  {		 
			 //  0
			 x  =  rc.right  -  layout.iW_peerInfo;
			 y  =  iEdge_t;
			 //
			 int  iH_static_peerInfo  =  0;
			 if  (  layout.ucbShow_peer_tool  )  iH_static_peerInfo  =  CONST_iH_static_peerInfo;
			 //
			 idc  =  IDC_STATIC_peerInfo;
			 if  (  !layout.ucbShow_peer_tool  )  {
				 iW  =  0;  iH  =  0;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
				 }
			 else  {
				   iW  =  layout.iW_peerInfo;  
				   iH  =  iH_static_peerInfo;
				   //		 
				   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
			 }
			 

			 //
			 idc  =  IDC_LIST_peerInfo;
			 //
			 y  +=  iH;
			 //
			 if  (  !layout.ucbShow_peer_tool  )  {
				 iW  =  0;  iH  =  0;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
				 }
			 else  {
				   iW  =  layout.iW_peerInfo;  
				   iH  =  rc.bottom  -  rc.top  -  iEdge_t  -  iEdge_b  -  iH_dlgDesc  -  iH_static_peerInfo;
				   iH  *=  0.7;
				   //		 
				   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
			 }

			 //
			 idc  =  IDC_BUTTON_shareScreen;
			 //
			 x  +=  (  layout.iW_peerInfo  -  iW_shareScreen  *  2  )  /  3;  
			 y  +=  iH;
			 //
			 if  (  !layout.ucbShow_peer_tool  )  {
				 iW  =  0;  iH  =  0;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
				 }
			 else  {
				   iW  =  iW_shareScreen;  
				   iH  =  iH_shareScreen;
				   //		 
				   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
			 }

			 //
			 idc  =  IDC_BUTTON_controlDesktop;
			 //
			 x  +=  iW_shareScreen  +  (  layout.iW_peerInfo  -  iW_shareScreen  *  2  )  /  3;
			 //
			 if  (  !layout.ucbShow_peer_tool  )  {
				 iW  =  0;  iH  =  0;
				 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
				 }
			 else  {
				   iW  =  iW_shareScreen;  
				   iH  =  iH_shareScreen;
				   //		 
				   M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
			 }





			 //
			 M_EndDeferWindowPos(  hDwp  );
		 }
	 }




	 //  2014/01/26
	 setMsgToolPos(  hDlg  );

	 //  2013/03/01
	 setRemotePtzPos(  hDlg  );
	 
	 //  2013/04/05
	 setSubtitlesPos_talk(  hDlg  );

	 //  2015/08/01
	 setOfflineResPos_talk(  hDlg  );

	 //
	 iErr  =  0;
errLabel:
	 return  iErr;
#endif
}


//
 BOOL  setMsgToolPos(  HWND  hCurTalker  )
{
	BOOL			bRet							=	FALSE;


	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurTalker  );
	if  (  !pCurTalkerVar  )  return  FALSE;

	DLG_TALK_var  &  m_var  =  *pCurTalkerVar;

	
	if  (  !IsWindow(  pCurTalkerVar->msgTool.hWnd_msgTool  )  )  return  FALSE;

	RECT	rc;
	rc  =  pCurTalkerVar->msgTool.rc;
	MapWindowPoints(  hCurTalker,  NULL,  (  LPPOINT  )&rc,  2  );
	//
	//  MoveWindow(  pCurTalkerVar->msgTool.hWnd_msgTool,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  TRUE  );
	UINT  uFlags;
	uFlags  =  m_var.guiData.bFinished_createCtrls  ?  SWP_SHOWWINDOW  |  SWP_NOZORDER  :  SWP_HIDEWINDOW;
	SetWindowPos(  pCurTalkerVar->msgTool.hWnd_msgTool,  0,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  uFlags  );

	//
	if  (  IsWindow(  m_var.hWnd_instantAssistant  )  )  {
		SetForegroundWindow(  m_var.hWnd_instantAssistant  );
	}

	//
	 bRet  =  TRUE;
	 return  bRet;
}


 //
 __declspec(  dllexport  )  int  refreshTalkToInfo(  HWND  hCurTalk  )
 {
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hCurTalk  );
	if  (  !pCurVar  )  return  -1;
	
	
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	HWND  hMgr  =  hCurTalk;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)pCurVar;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
		if  (  !pShadow  )  return  -1;
		hMgr  =  pShadow->hMgr;
		pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		if  (  !pMgrVar  )  return  -1;
	}
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;

	QY_MC  *  pQyMc  =  QY_GET_GBUF( );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;
	int  i;

	//
	TCHAR  tBuf_confStatus[128]  =  _T(  ""  );
	TCHAR  tBuf_instantStatus[128]  =  _T(  ""  );

	//
	if  (  pMgrVar->addr.uiObjType  ==  CONST_objType_imGrp  )  {
		//
		if  (  pMgrVar->av.taskInfo.bTaskExists  )  {
			if  (  pMgrVar->av.taskInfo.ucbConfCtrl  )  {
				_sntprintf(  tBuf_confStatus,  mycountof(  tBuf_confStatus  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_confManaging  )  );  //_T(  "会议管理中："  )  );
				if  (  pMgrVar->av.taskInfo.ucbStarter  )  _sntprintf(  tBuf_confStatus,  mycountof(  tBuf_confStatus  ),  _T(  "%s%s"  ),  tBuf_confStatus,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_confStarter  )  );  //_T(  "发起人"  )  );
				else  if  (  pShadowMgr->av.ucbMeConfMgr  )  _sntprintf(  tBuf_confStatus,  mycountof(  tBuf_confStatus  ),  _T(  "%s%s"  ),  tBuf_confStatus,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_confManager  )  );  //_T(  "主持人"  )  );
				else  _sntprintf(  tBuf_confStatus,  mycountof(  tBuf_confStatus  ),  _T(  "%s%s"  ),  tBuf_confStatus,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_confMember  )  );  //_T(  "参会人"  )  );
				}
			else  {
				_sntprintf(  tBuf_confStatus,  mycountof(  tBuf_confStatus  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_conferencing  )  );  //_T(  "会议中："  )  );
				if  (  pMgrVar->av.taskInfo.ucbStarter  )  _sntprintf(  tBuf_confStatus,  mycountof(  tBuf_confStatus  ),  _T(  "%s%s"  ),  tBuf_confStatus,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_confStarter  )  );  //_T(  "发起人"  )  );
				else  _sntprintf(  tBuf_confStatus,  mycountof(  tBuf_confStatus  ),  _T(  "%s%s"  ),  tBuf_confStatus,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_confMember  )  );  //_T(  "参会人"  )  );
			}
		}
	}

	//
	
			 //
			 //			
			 if  (  pMgrVar->av.taskInfo.bTaskExists  )  {				
				 if  (  pMgrVar->av.taskInfo.ucbConfCtrl  )  {					
					 if  (  pMgrVar->av.taskInfo.ucbStarter  ||  pShadowMgr->av.ucbMeConfMgr  )  {
						//
						if  (  pCurVar->confMgr_grpMemListInfo.idInfo_talkTo.ui64Id  )  {
							//
							if  (  pCurVar->confMgr_grpMemListInfo.idInfo_talkTo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
								_sntprintf(  tBuf_instantStatus,  mycountof(  tBuf_instantStatus  ),  _T(  "Me, can't talk to"  )  );
								}
							else  {
								  //							
								  _sntprintf(  tBuf_instantStatus,  mycountof(  tBuf_instantStatus  ),  _T(  "@%I64u"  ),  pCurVar->confMgr_grpMemListInfo.idInfo_talkTo.ui64Id  );
								  for  (  i  =  0;  i  <  pShadowMgr->confCtrl.grpConfCtrl.usCnt;  i  ++  )  {
									   GrpMem_confCtrl  *  pMem  =  &pShadowMgr->confCtrl.grpConfCtrl.pMems[i];
									   if  (  pMem->idInfo.ui64Id  ==  pCurVar->confMgr_grpMemListInfo.idInfo_talkTo.ui64Id  )  {
										   _sntprintf(  tBuf_instantStatus,  mycountof(  tBuf_instantStatus  ),  _T(  "%s %s"  ),  tBuf_instantStatus,  pMem->displayName  );
										   break;
									   }							
								  }		
							}
							//
							}					
						else  {
							  safeTcsnCpy(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_2all  ), /*_T(  "@all"  ),*/  tBuf_instantStatus,  mycountof(  tBuf_instantStatus  )  );					
						}
						
					
						}									
					 else  {
						  safeTcsnCpy(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_2manager  ),/*_T(  "@manager"  ),*/  tBuf_instantStatus,  mycountof(  tBuf_instantStatus  )  );									
					 }							
				 }					
			 }


			 //
			 SetDlgItemText(  pCurVar->msgTool.hWnd_msgTool,  IDC_STATIC_confStatus,  tBuf_confStatus  );
			 //
			 SetDlgItemText(  pCurVar->msgTool.hWnd_msgTool,  IDC_STATIC_instantStatus,  tBuf_instantStatus  );
		 
 

	
errLabel:

	 return  0;
}



 //
  //
 __declspec(  dllexport  )  int  refreshTalkToInfo_mgr(  HWND  hDlgTalk_mgr  )
 {
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk_mgr  );
	if  (  !pMgrVar  )  goto  errLabel;

	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	int  i;


	//
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		 TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
		 if  (  pMem->hShadow  )  {			 
			 refreshTalkToInfo(  pMem->hShadow  );
		 }	
	}

	//
	refreshTalkToInfo(  hDlgTalk_mgr  );

	
errLabel:

	 return  0;
}





 //  2013/03/04
 int  mySizeAllControls_dlgTalk_peer(  HWND  hDlg,  DLG_TALK_var  &  m_var,  DLG_talk_layout  *  pLayout,  RECT  *  pRect  )
{
#ifdef  __DEBUG__
		traceLog(  _T(  "mySizeAllControls_dlgTalk_peer called"  )  );
#endif

#ifndef  __SUPPORT_HTMLEDIT__
		return  -1;
#else
	 int			iErr							=	-1;
	 HDWP			hDwp;
	 RECT			cliRc;
	 //
	 int			iEdge_l							=	CONST_edge_l_dlgTalk_wall;
	 int			iEdge_t							=	CONST_edge_l_dlgTalk_wall;
	 int			iEdge_r							=	CONST_edge_l_dlgTalk_wall;
	 int			iEdge_b							=	CONST_edge_l_dlgTalk_wall;
	 //
	 int			iX_spacing						=	CONST_iX_spacing_dlgTalk_wall;			//  
	 int			iY_spacing						=	CONST_iY_spacing_dlgTalk_wall;			//  
	 //

#ifdef  __APP_qyMc__
		if  (  !m_var.ucbOnGlobalVWall  )  {			
			iEdge_l							=	CONST_edge_l_dlgTalk_desktop;
			iEdge_t							=	CONST_edge_t_dlgTalk_desktop;
			iEdge_r							=	CONST_edge_l_dlgTalk_desktop;
			iEdge_b							=	CONST_edge_b_dlgTalk_desktop;
			//
			iX_spacing						=	CONST_iX_spacing_dlgTalk_desktop;			//  
			iY_spacing						=	CONST_iY_spacing_dlgTalk_desktop;			//  
		}
#endif





	 int			iW_dlgDesc						=	0;
	 int			iH_dlgDesc						=	0;
	 //
	 int			iW_memberList					=	CONST_iW_memberList;
	 int			iH_memberList					=	10;
	 //
 	 int			iW_taskList						=	10;
	 int			iH_taskList						=	10;
	 //
	 int			iW_instantStatus				=	50;
	 int			iH_instantStatus				=	15;			//  20;		//  2012/05/17, 因为gps墙上小talk的缘故，希望talk标签小一点
	 //
	 int			iW_recentMsgList				=	10;
	 int			iH_recentMsgList				=	10;
	 //
	 int			iW_input						=	10;
	 int			iH_input						=	24;
	 //
	 int			iW_ptz							=	0;				//  2012/09/05
	 int			iH_ptz							=	0;
	 BOOL			bShowPtz						=   dlgTalk_bPtzShown(  hDlg  );
	 //
 	 int			iW_peerDesc						=	10;
	 int			iH_peerDesc						=	10;
	 //
	 int			iW_meDesc						=	0;			//  2008/03/27
	 int			iH_meDesc						=	0;
	 //
	 int			iW_otherDesc					=	0;
	 int			iH_otherDesc					=	0;
	 //
	 int			x, y;
	 //  CWnd		*	pWnd;
	 HWND			hWnd;
	 int			idc;
	 //	 
	 int			iW_pRect,  iH_pRect;
	 int			iW_cliRc,  iH_cliRc;
	 //  int			tmpiX,tmpiY;

	 //
	 MC_VAR_isCli	*	pProcInfo			=	QY_GET_procInfo_isCli(  );

	 HWND				hCtrl;
	 UINT			uFlags;

	 
	 //
	 if  (  !pLayout  )  return  -1;
	 if  (  !pRect  )  return  -1;

	 //
	 idc  =  m_var.guiData.iIDC_STATIC_dlgDesc;
	 hCtrl  =  GetDlgItem(  hDlg,  idc  );
	 if  (  !hCtrl  )  goto  errLabel;
	 

	 //
	 GetClientRect(  hDlg,  &cliRc  );
	 //  rc  =  *pRect;

	 DLG_talk_layout  &     layout  =  *pLayout;
	 //
	 //  dlgTalk_calculateLayout(  hDlg,  &m_var,  NULL,  &layout  );
	 //memcpy(  &layout,  pLayout,  sizeof(  layout  )  );

	 //
	 iW_memberList  =  layout.iW_memberList;
	 //
	 iW_taskList  =  layout.iW_taskList;
	 iW_recentMsgList  =  iW_taskList;
	 iW_instantStatus  =  iW_recentMsgList;
	 iW_input  =  iW_recentMsgList;
	 //
	 iW_ptz  =  layout.iW_ptz;

	 //
	 iW_cliRc  =  cliRc.right  -  cliRc.left  -  iEdge_l  -  iEdge_r;
	 iW_pRect  =  pRect->right  -  pRect->left  -  iEdge_l  -  iEdge_r;


	 //
	 iW_peerDesc  =  iW_pRect  -  iW_taskList  -  iW_memberList  -  iW_ptz  -  layout.iW_subtitles  - layout.iW_offlineRes  -  layout.iW_peerInfo;
	 if  (  iW_peerDesc  <  0  )  iW_peerDesc  =  0;

	 //  2011/03/03
	 if  (  m_var.guiData.ucbShowDlgDesc  )  {
		 iW_dlgDesc  =  iW_cliRc;
		 iH_dlgDesc  =  CONST_iH_dlgDesc;	//  iH_instantStatus;
	 }

	 
#if  10
	 //
	 //  peerDesc meDesc
#if  0	//  2013/04/09
	 iH_cliRc  =  cliRc.bottom  -  cliRc.top  -  iEdge_t  -  iEdge_b  -  iH_dlgDesc;
	 iH_pRect  =  pRect->bottom  -  pRect->top  -  iEdge_t  -  iEdge_b  -  iH_dlgDesc;
#endif
	 iH_cliRc  =  cliRc.bottom  -  cliRc.top  -  iEdge_t  -  iEdge_b;
	 iH_pRect  =  pRect->bottom  -  pRect->top  -  iEdge_t  -  iEdge_b;
	 //
	 if  (  iH_pRect  <  0  )  iH_pRect  =  0;

#ifdef  __DEBUG__		
#if  0
	    TCHAR	tBuf[128]  =  _T(  ""  );
		static  BOOL  bShow  =  FALSE;
		if  (  !bShow  )  {
			if  (  iH_cliRc  &&  iH_pRect  )  {
			bShow  =  TRUE;
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "iH_cliRc %d, iH_pRect %d,  iEdge_t %d, iEdge_b %d"  ),  iH_cliRc,  iH_pRect,  iEdge_t,  iEdge_b  );
			myMessageBox(  hDlg,  tBuf,  _T(  "qycx.com"  ),  MB_OK  );
			bShow  =  FALSE;
			}
		}
#endif
#endif


	 //
	 if  (  layout.ucbShowMeDesc  )  {
#if  0
		 if  (  dlgTalk_bShowMsgBox(  hDlg  )  )  iH_peerDesc  =  iH_pRect  *  3  /  4;
		 else  iH_peerDesc  =  iH_pRect;
#else
		 iH_peerDesc  =  iH_pRect;
#endif
		 //  iW_meDesc	=  (  m_var.guiData.ucbShowDynBmps  )  ?  iW_peerDesc  *  1  /  2  :  iW_peerDesc  *  1  /  3;			//  
		 iW_meDesc	=  (  iW_cliRc  -  iW_taskList  -  iW_memberList  -  iW_ptz  )  /  3;			//  
		 iH_meDesc  =  iH_cliRc  *  1  /  4;

		 float  fx  =  iW_meDesc  /  320.;
		 float  fy  =  iH_meDesc  /  240.;
		 float  f  =  min(  fx,  fy  );	
	 
		 iW_meDesc  =  f  *  320;
		 iH_meDesc  =  f  *  240;
		 }
	 else  {
		   iH_peerDesc  =  iH_pRect;
		   iW_meDesc  =  0;
		   iH_meDesc  =  0;
	 }
	 //  iH_peerDesc  =  rc.bottom  -  iEdge_t  -  iEdge_b  -  iH_meDesc  -  (  iH_meDesc  ?  iY_spacing  : 0  );
	 //  if  (  iH_peerDesc  <  0  )  iH_peerDesc  =  0;
	 //
#endif


	 //  2013/03/14
	 //  redrawImage(  hDlg,  0,  m_var.guiData.peerCapRect.iX,  m_var.guiData.peerCapRect.iY,  m_var.guiData.peerCapRect.iW,  m_var.guiData.peerCapRect.iH  );
	 hCtrl  =  GetDlgItem(  hDlg,  m_var.guiData.iIDC_STATIC_peerDesc  );
	 if  (  !hCtrl  )  goto  errLabel;
	 //  InvalidateRect(  hCtrl,  NULL,  TRUE  );
	 int  idc_dst  =  0;	//  m_var.guiData.iIDC_STATIC_peerDesc;
	 old_freeCapImages(  hDlg,  m_var.guiData.iIDC_STATIC_peerDesc,  &m_var.av.peerZone.images,  old_M_GetDlgItem(  hDlg,  idc_dst  ),  &m_var.av.hDc_peer,  _T(  "mySizeAllControls_dlgTalk_peer.3104"  ));		//  2013/02/28. 最好能根据me,other,peer的任何size变化来决定是否free
	 
	 //  
	 hDwp  =  M_BeginDeferWindowPos(  1  );
	 if  (  hDwp  )  {
		 int			iW,  iH;

		 //  7
		 idc  =  IDC_STATIC_peerDesc;
		 x  =  iEdge_l  +  layout.iW_memberList  +  layout.iW_taskList  +  layout.iW_ptz  +  layout.iW_subtitles  +  layout.iW_offlineRes;
		 y  =  iEdge_t;
		 iW  =  iW_peerDesc;  iH  =  iH_peerDesc;
		 //
		 uFlags  =  SWP_NOZORDER  |  SWP_HIDEWINDOW;
		 if  (  layout.ucbShowPeerDesc  )  uFlags  =  SWP_SHOWWINDOW;
		 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  HWND_BOTTOM,  x,  y,  iW,  iH,  uFlags  );
		 //
		 //m_var.guiData.peerCapRect.iX  =  x;  m_var.guiData.peerCapRect.iY  =  y;
		 //m_var.guiData.peerCapRect.iW  =  iW;  m_var.guiData.peerCapRect.iH  =  iH;
		 m_var.av.peerZone.iX  =  x;  m_var.av.peerZone.iY  =  y;
		 m_var.av.peerZone.iW  =  iW;  m_var.av.peerZone.iH  =  iH;
		 //
		 M_EndDeferWindowPos(  hDwp  );
	 }
	 
	 //
	 m_var.av.idc_peer  =  m_var.guiData.iIDC_STATIC_peerDesc;
	 m_var.av.hCtrl_peer = GetDlgItem(hDlg, m_var.av.idc_peer);
	 m_var.av.hWnd_dst_peer = hDlg;
	 //m_var.guiData.peerCapRect.iX  =  0;  m_var.guiData.peerCapRect.iY  =  0;
	 m_var.av.peerZone.iX  =  0;  m_var.av.peerZone.iY  =  0;

	 //
	 getCapImages(  m_var.ucbAutoClip,  m_var.av.peerZone.iX,  m_var.av.peerZone.iY,  m_var.av.peerZone.iW,  m_var.av.peerZone.iH,  NULL,  &m_var.av.peerZone.images  );

	 //
	 iErr  =  0;
errLabel:
	 return  iErr;
#endif
}

 //  2013/03/04
 int  mySizeAllControls_dlgTalk_me_other(  HWND  hDlg,  DLG_TALK_var  &  m_var,  DLG_talk_layout  *  pLayout,  RECT  *  pRect  )
{
#ifdef  __DEBUG__
		traceLog(  _T(  "mySizeAllControls_dlgTalk_me_other called"  )  );
#endif

#ifndef  __SUPPORT_HTMLEDIT__
		return  -1;
#else
	 int			iErr							=	-1;
	 HDWP			hDwp;
	 RECT			cliRc;
	 //
	 int			iEdge_l							=	CONST_edge_l_dlgTalk_wall;
	 int			iEdge_t							=	CONST_edge_l_dlgTalk_wall;
	 int			iEdge_r							=	CONST_edge_l_dlgTalk_wall;
	 int			iEdge_b							=	CONST_edge_l_dlgTalk_wall;
	 //
	 int			iX_spacing						=	CONST_iX_spacing_dlgTalk_wall;			//  
	 int			iY_spacing						=	CONST_iY_spacing_dlgTalk_wall;			//  
	 //

#ifdef  __APP_qyMc__
		if  (  !m_var.ucbOnGlobalVWall  )  {			
			iEdge_l							=	CONST_edge_l_dlgTalk_desktop;
			iEdge_t							=	CONST_edge_t_dlgTalk_desktop;
			iEdge_r							=	CONST_edge_l_dlgTalk_desktop;
			iEdge_b							=	CONST_edge_b_dlgTalk_desktop;
			//
			iX_spacing						=	CONST_iX_spacing_dlgTalk_desktop;			//  
			iY_spacing						=	CONST_iY_spacing_dlgTalk_desktop;			//  
		}
#endif





	 int			iW_dlgDesc						=	0;
	 int			iH_dlgDesc						=	0;
	 //
	 int			iW_memberList					=	CONST_iW_memberList;
	 int			iH_memberList					=	10;
	 //
 	 int			iW_taskList						=	10;
	 int			iH_taskList						=	10;
	 //
	 int			iW_instantStatus				=	50;
	 int			iH_instantStatus				=	15;			//  20;		//  2012/05/17, 因为gps墙上小talk的缘故，希望talk标签小一点
	 //
	 int			iW_recentMsgList				=	10;
	 int			iH_recentMsgList				=	10;
	 //
	 int			iW_input						=	10;
	 int			iH_input						=	24;
	 //
	 int			iW_ptz							=	0;				//  2012/09/05
	 int			iH_ptz							=	0;
	 BOOL			bShowPtz						=   dlgTalk_bPtzShown(  hDlg  );
	 int			iW_subtitles					=   0;											//  2014/10/03
	 int			iH_subtitles					=	0;
	 BOOL			bShowSubtitles					=	dlgTalk_bSubtitlesShown(  hDlg  );			//  TRUE;				//  
	 BOOL			bShowOfflineRes					=	dlgTalk_bOfflineResShown(  hDlg  );			//  2015/08/01
	 //
 	 int			iW_peerDesc						=	10;
	 int			iH_peerDesc						=	10;
	 //
	 int			iW_meDesc						=	0;				//  2008/03/27
	 int			iH_meDesc						=	0;
	 //  2017/10/02
	 int			iW_status						=	0;
	 int			iH_status						=	0;
	 //
	 int			iW_bgWall						=	0;				//  2014/10/01
	 int			iH_bgWall						=	0;				//  2014/10/01
	 //
	 //int			iW_bg							=	0;				//  2014/10/01
	 //int			iH_bg							=	0;				//  2014/10/01
	 //
	 int			iW_otherDesc					=	0;
	 int			iH_otherDesc					=	0;
	 //
	 int			x, y;
	 //  CWnd		*	pWnd;
	 HWND			hWnd;
	 int			idc;
	 //	 
	 int			iW_pRect,  iH_pRect;
	 int			iW_cliRc,  iH_cliRc;
	 //  int			tmpiX,tmpiY;
	 int			iW_right						=	0;
	 //
	 MC_VAR_isCli	*	pProcInfo			=	QY_GET_procInfo_isCli(  );

	 HWND				hCtrl;
	 UINT			uFlags;

	 
	 //
	 if  (  !pLayout  )  return  -1;
	 if  (  !pRect  )  return  -1;

	 //
	 idc  =  m_var.guiData.iIDC_STATIC_dlgDesc;
	 hCtrl  =  GetDlgItem(  hDlg,  idc  );
	 if  (  !hCtrl  )  goto  errLabel;
	 

	 //
	 GetClientRect(  hDlg,  &cliRc  );
	 //  rc  =  *pRect;

	 DLG_talk_layout  &     layout  =  *pLayout;

	 //
	 iW_memberList  =  layout.iW_memberList;
	 //
	 iW_taskList  =  layout.iW_taskList;
	 iW_recentMsgList  =  iW_taskList;
	 iW_instantStatus  =  iW_recentMsgList;
	 iW_input  =  iW_recentMsgList;
	 //
	 iW_ptz  =  layout.iW_ptz;
	 iW_subtitles  =  layout.iW_subtitles;

	 //
	 iW_cliRc  =  cliRc.right  -  cliRc.left  -  iEdge_l  -  iEdge_r;
	 iW_pRect  =  pRect->right  -  pRect->left  -  iEdge_l  -  iEdge_r;


	 //
	 iW_peerDesc  =  iW_pRect  -  iW_taskList  -  iW_memberList  -  iW_ptz  -  iW_subtitles  - pLayout->iW_offlineRes;
	 if  (  iW_peerDesc  <  0  )  iW_peerDesc  =  0;

	 //  2011/03/03
	 if  (  m_var.guiData.ucbShowDlgDesc  )  {
		 iW_dlgDesc  =  iW_cliRc;
		 iH_dlgDesc  =  CONST_iH_dlgDesc;	//  iH_instantStatus;
	 }

	 
	 //
	 //  peerDesc meDesc
	 iH_cliRc  =  cliRc.bottom  -  cliRc.top  -  iEdge_t  -  iEdge_b  -  iH_dlgDesc;
	 iH_pRect  =  pRect->bottom  -  pRect->top  -  iEdge_t  -  iEdge_b  -  iH_dlgDesc;

	 if  (  iH_cliRc  <  0  )  iH_cliRc  =  0;
	 
	 iW_right  =  (  iW_cliRc  -  iW_taskList  -  iW_memberList  -  iW_ptz  -  iW_subtitles  -  pLayout->iW_offlineRes  );

	 //  2014/12/03
	 calc_me_bgWall_rect(  &layout,  iW_right,  iH_cliRc,  &iW_meDesc,  &iH_meDesc,  &iW_bgWall,  &iH_bgWall  );
	 
	 //  2017/08/22
	 if  (  layout.ucbShow_peer_tool  )  {
		 iW_meDesc  =  layout.iW_peerInfo;
		 iH_meDesc  =  iH_cliRc  -  layout.iH_staticPeerInfo  -  layout.iH_peerInfo  -  layout.iH_shareScreen; 
	 }

	 //  2017/10/02
	 if  (  layout.ucbShowMeDesc  )  {
		 iW_status  =  max(  iW_meDesc,  MIN_iW_status  );
		 iH_status  =  CONST_iH_status;
		 //
		 iH_meDesc  -=  iH_status;
	 }

	 //  2017/08/31
	 m_var.m_layout.iW_meDesc  =  iW_meDesc;
	 m_var.m_layout.iH_meDesc  =  iH_meDesc;
	 

	 //
	 if  (  layout.ucbShowOtherDesc  )  {
		 float  fVal  =  3;
		 //
		 fVal  =  4;
		 //
		 iW_otherDesc  =  (  iW_cliRc  -  iW_taskList  -  iW_memberList  -  iW_ptz  -  iW_subtitles  -  pLayout->iW_offlineRes  )  /  fVal;
		 iH_otherDesc  =  iH_cliRc  /  fVal;
	
		 //
		 float  fW  =  1024.;
		 float  fH  =  768.;
		 //
		 fW  =  1280;
		 fH  =  720;
		 //
		 float  fx  =  iW_otherDesc  /  fW;
		 float  fy  =  iH_otherDesc  /  fH;
		 float  f  =  min(  fx,  fy  );	
	 
		 iW_otherDesc  =  f  *  fW;
		 iH_otherDesc  =  f  *  fH;
		 }
	 else  {
		   iW_otherDesc  =  0;
		   iH_otherDesc  =  0;
	 }

	 //  2010/09/10

	 //  
	 hDwp  =  M_BeginDeferWindowPos(  4  );
	 if  (  hDwp  )  {
		 int			iW,  iH;

		 //  8
		 idc  =  IDC_STATIC_meDesc;			//  
		 x  =  cliRc.right  -  cliRc.left  -  iEdge_r  -  iEdge_l  -  iW_meDesc;  //  -  layout.iW_peer_tool;
		 y  =  cliRc.bottom  -  cliRc.top  -  iEdge_b  -  iH_meDesc  -  iH_dlgDesc  -  iH_status;
		 iW  =  iW_meDesc;  iH  =  iH_meDesc;
		 //
		 uFlags  =  SWP_NOZORDER  |  SWP_HIDEWINDOW;
		 if  (  layout.ucbShowMeDesc  )  uFlags  =  SWP_SHOWWINDOW;
		 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  uFlags  );
		 //
		 //m_var.guiData.meCapRect.iX  =  x;  m_var.guiData.meCapRect.iY  =  y;
		 //m_var.guiData.meCapRect.iW  =  iW;  m_var.guiData.meCapRect.iH  =  iH;
		 m_var.av.meZone.iX  =  x;  m_var.av.meZone.iY  =  y;
		 m_var.av.meZone.iW  =  iW;  m_var.av.meZone.iH  =  iH;
		 
		 //  2017/10/02
		 idc  =  IDC_STATIC_status;
		 x  =  cliRc.right  -  cliRc.left  -  iEdge_r  -  iEdge_l  -  iW_status;  //  -  layout.iW_peer_tool;
		 y  =  cliRc.bottom  -  cliRc.top  -  iEdge_b  -  iH_dlgDesc  -  iH_status;
		 iW  =  iW_status;  iH  =  iH_status;
		 //
		 uFlags  =  SWP_NOZORDER  |  SWP_HIDEWINDOW;
		 if  (  layout.ucbShowMeDesc  )  uFlags  =  SWP_SHOWWINDOW;
		 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  uFlags  );

		 
		 //  2014/09/30
		 //  9
		 idc  =  IDC_STATIC_bgWall_conf;			//  
		 //x  =  cliRc.right  -  cliRc.left  -  iEdge_r  -  iEdge_l  -  iW_meDesc  -  iW_bgWall;
		 x  =  iEdge_l  +  layout.iW_memberList  +  layout.iW_taskList  +  layout.iW_ptz  +  layout.iW_subtitles  +  layout.iW_offlineRes;
		 y  =  cliRc.bottom  -  cliRc.top  -  iEdge_b  -  iH_bgWall  -  iH_dlgDesc;
		 iW  =  iW_bgWall;  iH  =  iH_bgWall;
		 //
		 uFlags  =  SWP_NOZORDER  |  SWP_HIDEWINDOW;
		 //if  (  layout.ucbShowBgWall_starter  )  
		 if  (  dlgTalk_bShowBgWall(  hDlg  )  )
		 {
			 uFlags  =  SWP_SHOWWINDOW;
		 }
		 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  uFlags  );
		 //
		 //m_var.guiData.bgWallCapRect.iX  =  x;  m_var.guiData.bgWallCapRect.iY  =  y;
		 //m_var.guiData.bgWallCapRect.iW  =  iW;  m_var.guiData.bgWallCapRect.iH  =  iH;
		 m_var.av.bgWall.iX  =  x;  m_var.av.bgWall.iY  =  y;
		 m_var.av.bgWall.iW  =  iW;  m_var.av.bgWall.iH  =  iH;
		 			 
		 
		 //  10
		 idc  =  IDC_STATIC_otherDesc;
		 if  (  layout.ucbShowOtherDesc  )  {
			 x  =  cliRc.right  -  cliRc.left  -  iEdge_r  -  iEdge_l  -  iW_otherDesc  -  layout.iW_peerInfo;
			 y  =  iEdge_t;
			 iW  =  iW_otherDesc;  iH  =  iH_otherDesc;
			 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_SHOWWINDOW  );
		     }
		 else  {
			 y  +=  iH;
			 iW  =  iW_otherDesc;  iH  =  iH_otherDesc;
			 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_HIDEWINDOW  );
		 }
		 //
		 //m_var.guiData.otherCapRect.iX  =  x;  m_var.guiData.otherCapRect.iY  =  y;
		 //m_var.guiData.otherCapRect.iW  =  iW;  m_var.guiData.otherCapRect.iH  =  iH;
		 m_var.av.otherZone.iX  =  x;  m_var.av.otherZone.iY  =  y;
		 m_var.av.otherZone.iW  =  iW;  m_var.av.otherZone.iH  =  iH;
		 //
		 M_EndDeferWindowPos(  hDwp  );
	 }
	 
	 //
	 m_var.av.idc_me  =  m_var.guiData.iIDC_STATIC_meDesc;
	 m_var.av.hCtrl_me = GetDlgItem(hDlg, m_var.av.idc_me);
	 hCtrl  =  GetDlgItem(  hDlg,  m_var.av.idc_me  );
	 if  (  !hCtrl  )  goto  errLabel;
	 InvalidateRect(  hCtrl,  NULL,  TRUE  );
	 //  2013/02/23. 注意,peer当背景画,直接画在对话框上. me画控件上. 所以要把meCapRect转成控件坐标
	 //m_var.guiData.meCapRect.iX  =  0;  m_var.guiData.meCapRect.iY  =  0;
	 m_var.av.meZone.iX  =  0;  m_var.av.meZone.iY  =  0;
	 //
	 unsigned  char  ucbAutoClip  =  m_var.ucbAutoClip_me;	//  2016/02/17
	 //
	 getCapImages(  ucbAutoClip,  m_var.av.meZone.iX,  m_var.av.meZone.iY,  m_var.av.meZone.iW,  m_var.av.meZone.iH,  NULL,  &m_var.av.meZone.images  );

	 //  2014/10/01
	 m_var.av.idc_bgWall_conf  =  m_var.guiData.iIDC_STATIC_bgWall_conf;
	 m_var.av.hCtrl_bgWall_conf = GetDlgItem(hDlg, m_var.av.idc_bgWall_conf);
	 hCtrl  =  GetDlgItem(  hDlg,  m_var.av.idc_bgWall_conf  );
	 if  (  !hCtrl  )  goto  errLabel;
	 InvalidateRect(  hCtrl,  NULL,  TRUE  );
	 //m_var.guiData.bgWallCapRect.iX  =  0;  m_var.guiData.bgWallCapRect.iY  =  0;
	 m_var.av.bgWall.iX  =  0;  m_var.av.bgWall.iY  =  0;
	 getCapImages_bgWall(  hDlg,  &m_var,  m_var.ucbAutoClip,  m_var.av.bgWall.iX,  m_var.av.bgWall.iY,  m_var.av.bgWall.iW,  m_var.av.bgWall.iH,  &pLayout->bgWallLayoutCfg,  &pLayout->bgWallLayout  );
	 //
	 memcpy(  &m_var.m_layout.bgWallLayout,  &pLayout->bgWallLayout,  sizeof(  m_var.m_layout.bgWallLayout  )  );
	 

	 //  2013/02/25
	 m_var.av.idc_other  =  m_var.guiData.iIDC_STATIC_otherDesc;
	 m_var.av.hCtrl_other = GetDlgItem(hDlg, m_var.av.idc_other);
	 hCtrl  =  GetDlgItem(  hDlg,  m_var.av.idc_other  );	 	 
	 if  (  !hCtrl  )  goto  errLabel;	 
	 InvalidateRect(  hCtrl,  NULL,  TRUE  );
	 //m_var.guiData.otherCapRect.iX  =  0;  m_var.guiData.otherCapRect.iY  =  0;
	 m_var.av.otherZone.iX  =  0;  m_var.av.otherZone.iY  =  0;
	 getCapImages(  m_var.ucbAutoClip,  m_var.av.otherZone.iX,  m_var.av.otherZone.iY,  m_var.av.otherZone.iW,  m_var.av.otherZone.iH,  NULL,  &m_var.av.otherZone.images  );

	 //
	 iErr  =  0;
errLabel:
	 return  iErr;
#endif
}



//
  __declspec(  dllexport  )  int  sizeAllControls_dlgTalk(  HWND  hDlg,  void  *  pDLG_TALK_var,  RECT  *  pRect  )
 {
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iErr	=	-1;

	DLG_TALK_var	&	m_var	=	*(  DLG_TALK_var  *  )pDLG_TALK_var;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	 //  注意: dlgTalk没做完, 滚动没生效. 

	 if  (  !pRect  )  {
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "sizeAllControls_dlgTalk failed, pRect is null"  )  );

		 #endif
		 return  -1;
	 }

#ifndef  __SUPPORT_HTMLEDIT__
		return  -1;
#else

	 if  (  m_var.ucbUseHtmlEdit  )  {
#if  0
		 if  (  !m_var.msgToolCommon.m_pHtmlEdit_recentMsgList  ||  !m_var.msgToolCommon.m_pHtmlEdit_input  )  {
			 #ifdef  __DEBUG__
					 traceLog(  _T(  "sizeAllControls_dlgTalk failed, pHtmlEdit is null"  )  );
			 #endif
			 return  -1;
		 }
#endif
	 }


	 {	 //  2011/10/05
		 PF_commonHandler	pf		=	NULL;
		 pf  =  (  PF_commonHandler  )m_var.guiData.pf_refreshDlg_talk_ce;
		 if  (  pf  )  pf(  hDlg,  &m_var.guiData,  m_var.hWnd_instantAssistant  );		 
	 }

	 //  2012/04/18
	 DLG_talk_layout	layout;
	 RECT				rc;
	 GetClientRect(  hDlg,  &rc  );
	 if  (  dlgTalk_calculateLayout(  hDlg,  &m_var,  &rc,  &layout  )  )  goto  errLabel;
	 if  (  mySizeAllControls_dlgTalk_peer(  hDlg,  m_var,  &layout,  pRect  )  )  goto  errLabel;
	 if  (  mySizeAllControls_dlgTalk_tools(  hDlg,  m_var,  &layout,  &rc  )  )  goto  errLabel;
	 if  (  mySizeAllControls_dlgTalk_me_other(  hDlg,  m_var,  &layout,  &rc  )  )  goto  errLabel;

	 //
	 if  (  layout.ucbShowPeerDesc  )  {  //  2017/01/08
		 InvalidateRect(  GetDlgItem(  hDlg,  IDC_STATIC_peerDesc  ),  NULL,  TRUE  );
		 UpdateWindow(  GetDlgItem(  hDlg,  IDC_STATIC_peerDesc  )  );	 
		 {	 	
			 CHelp_getDlgTalkVar			help_getDlgTalkVar_mgr;
			 
			 DLG_TALK_var	*	pMgrVar	=	&m_var;
			 if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {		
				 TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
				 if  (  !pShadow  )  goto  errLabel;
				 pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pShadow->hMgr,  _T(  "dlgTalk_refresh_usLayoutType_cur,hMgr"  )  );
				 if  (  !pMgrVar  )  goto  errLabel;	
			 }	
			 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
			 if  (  pShadowMgr->shareScreen.ucbExists_localScreenSharing  )  {		
				 SetDlgItemText(  hDlg,  IDC_STATIC_peerDesc,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_sharingLetWinBeSmaller  )  );	
			 }	 
		 }
	 }

	 //  2014/11/20
#ifdef  __DEBUG__
#endif

	 //
	 iErr  =  0;
errLabel:
	 return  iErr;
#endif
}


#if  0
 __declspec(  dllexport  )  int  getTaskItem(  CListCtrl  *  pListCtrl,  int  iTaskId  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	LVFINDINFO		info;
	TCHAR			tBuf[64]	=	_T(  ""  );

	if  (  !pListCtrl  )  return  -1;

	//
	info.flags  =  LVFI_PARAM;	//  ÕâÀï°Ñ²éÑ¯µÄ·½Ê½ÓÉ×Ö·û´®¸Ä³ÉÁËÊý×Ö, 2007/07/17
	info.lParam  =  iTaskId;

	return  pListCtrl->FindItem(  &info,  -1  );

}
#endif

 __declspec(  dllexport  )  int  getTaskItem(  HWND  hListCtrl,  int  iTaskId  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	LVFINDINFO		info;
	TCHAR			tBuf[64]	=	_T(  ""  );

	if  (  !IsWindow(  hListCtrl  )  )  return  -1;

	//
	memset(  &info,  0,  sizeof(  info  )  );
	info.flags  =  LVFI_PARAM;	//  ÕâÀï°Ñ²éÑ¯µÄ·½Ê½ÓÉ×Ö·û´®¸Ä³ÉÁËÊý×Ö, 2007/07/17
	info.lParam  =  iTaskId;

	//  return  ListCtrl_FindItem(  hListCtr,  -1,  &info  );
	return  SendMessage(  hListCtrl,  LVM_FINDITEM,  (  WPARAM  )-1,  (  LPARAM  )&info  );  

}



 //




//
   __declspec(  dllexport  )  int  dlgTalk_processPointerEvent(  HWND  hCurTalk,  int  x,  int  y,  UINT nFlags,  BOOL  bMouseMove,  BOOL  bSendForce  )
{
		int						iErr			=	-1;

		//
		MC_VAR_isCli		*		pProcInfo		=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
		if  (  !pProcInfo  )  return  -1;
		FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
		if  (  !pFuncs  )  return  -1;
		MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
		if  (  !pMisCnt  )  return  -1;

		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hCurTalk  );
		if  (  !pCurVar  )  return  -1;
		//
		CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
		
		//
		HWND  hMgr  =  hCurTalk;
		DLG_TALK_var  *  pMgrVar  =  pCurVar;
		if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
			TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
			hMgr  =  pShadow->hMgr;
			pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
			if  (  !pMgrVar  )  goto  errLabel;
		}
		//
		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
		if  (  !pShadowMgr  )  goto  errLabel;
		//
		DLG_TALK_var  &m_var  =  *pCurVar;
		
		//
		int  x_img,  y_img;
		HWND  hCtrl  =  ::GetDlgItem(  hCurTalk,  m_var.guiData.iIDC_STATIC_peerDesc  );
		POINT  pnt;
		pnt.x  =  x;
		pnt.y  =  y;
		::MapWindowPoints(  hCurTalk,  hCtrl,  &pnt,  1  );
		x_img  =  pnt.x;
		y_img  =  pnt.y;

		//
#ifdef  __DEBUG__
		if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
			traceLog(_T("x_img %d, y_img %d"), x_img, y_img);
		}
#endif

		//
		if  (  !pShadowMgr->resourcesInfo.info_recv.bExists_remoteAssist  ||  m_var.av.peerZone.images.head.usCnt  !=  1  )  return  -1;

		//  if (  ::GetFocus() != m_hWnd) return 0;

		MACRO_prepareForTran(  )
		unsigned  int			uiChannelType	=	CONST_channelType_rtOp;	//  2016/12/26	//  CONST_channelType_media;
		MIS_CHANNEL			*	pChannel		=	NULL;
		if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  goto  errLabel;

		REMOTE_ASSIST_REQ		req;
		int						mask;
		CAP_IMAGE			*	pImg			=	&m_var.av.peerZone.images.mems[0];
		if  (  !pImg->iW_org  ||  !pImg->iH_org  )  goto  errLabel;

		//
		if  (  x_img  <  0  ||  x_img  >  pImg->iW_org  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "dlgTalk.processPointerEvent: err. x_img %d"  ),  x_img  );
			#endif
			goto  errLabel;
		}
		if  (  y_img  <  0  ||  y_img  >  pImg->iH_org  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "dlgTalk.processPointerEvent: err. y_img %d"  ),  y_img  );
			#endif
			goto  errLabel;
		}
		

		//
		if  (  m_var.bSwapMouse  )  {
    		mask  =  (  (  (  nFlags  &  MK_LBUTTON  )  ?  CONST_button1Mask  :  0  ) 
					|  (  (  nFlags  &  MK_MBUTTON  )  ?  CONST_button3Mask  :  0  ) 
					|  (  (  nFlags  &  MK_RBUTTON  )  ?  CONST_button2Mask  :  0  )  );
			} 
		else {
			 mask  =  (  (  (  nFlags  &  MK_LBUTTON  )  ?   CONST_button1Mask  :  0  ) 
					|  (  (  nFlags  &  MK_MBUTTON  )  ?  CONST_button2Mask  :  0  ) 
					|  (  (  nFlags  &  MK_RBUTTON  )  ?  CONST_button3Mask  :  0  )  );
		}
 
		memset(  &req,  0,  sizeof(  req  )  );
		req.uiType  =  CONST_imCommType_remoteAssistReq;
		req.uiTranNo_openAvDev  =  pImg->uiTranNo_openAvDev;
		req.u.usRaType  =  CONST_usRaType_pointerEvent;
		req.u.pointerEvent.ucButtonMask  =  mask;
#if  0
		req.u.pointerEvent.x  =  (  unsigned  short  )(  x  +  pBase->m_var.m_nScrollPos_h  );  
		req.u.pointerEvent.y  =  (  unsigned  short  )(  y  +  pBase->m_var.m_nScrollPos_v  );  
		//  È·±£ÔÚ²¶»ñ·¶Î§ÄÚ
		if  (  req.u.pointerEvent.x  <  pBase->m_var.layoutParam.iEdge_l  ||  req.u.pointerEvent.y  <  pBase->m_var.layoutParam.iEdge_t  )  goto  errLabel;
		//  È¥µô±ß½ç²¿·Ö     
		req.u.pointerEvent.x  -=  pBase->m_var.layoutParam.iEdge_l;
		req.u.pointerEvent.y  -=  pBase->m_var.layoutParam.iEdge_t;
#endif
		//
		req.u.pointerEvent.x  =  x_img;
		req.u.pointerEvent.y  =  y_img;

#if  10
		//  1¡£Î´Íê³É¡£Êó±ê¹ý¿ì£¬Òª´ÓÍ¼Ïñ´ø»Ø¸ö±êÊ¶µ±ÏìÓ¦¡£
		//  2¡£ÓÐºÃ¼¸¸öµØ·½ÊÇÍ¨¹ý¶ÔmediaQµÄwarningInterval½øÐÐÏÞËÙ£¬ÕâÊµ¼ÊºÜ¶àÊÇ´íµÄ¡£Ó¦¸Ã¶ÔtoSendQ ½øÐÐÅÐ¶Ï¡£×¢Òâ¡£¡£¡£¡£


		//  ½«ÊÂ¼þ¼ÇÂ¼ÏÂÀ´¡£Èç¹ûÃ»·¢ËÍ³öÈ¥£¬¿ÉÒÔÔÚOnTimerÀï·¢ËÍ
		m_var.remoteAssist.lastMouseEvent.x  =  x;
		m_var.remoteAssist.lastMouseEvent.y  =  y;
		m_var.remoteAssist.lastMouseEvent.nFlags  =  nFlags;
		m_var.remoteAssist.lastMouseEvent.bMouseMove  =  bMouseMove;
		//
		m_var.remoteAssist.bNeedSend_lastMouseEvent  =  TRUE;

		//  ÕâÀïÒª¸ÄÎª´ÓmousemoveÀï°ÑdwTickCnt´øÉÏ£¬ÓÐ±»Ð­Öú¶Ë°Ñ´ËÖµ´ÓÍ¼ÏñÀú´ø»Ø¡£È»ºó£¬¼ÌÐø·¢ËÍmousemove¡£ÆäËû°ü²»ÏÞ
		if  (  !bSendForce  &&  bMouseMove  )  {
		}									

		//
		if  (  !pProcInfo->av.rtOp.bChannelReady  )  {
			static  DWORD	sdwTickCnt_applyForChkChannels	=	0;
		//
			{
					   MIS_CNT							*	pMisCnt		=	NULL;
					   MIS_MSG_applyForChkChannels_qmc		msg_applyForChkChannels;
					   int	dwTickCnt;						dwTickCnt  =  GetTickCount(  );
					   int									i;
					   //  CQyQ2Help								q2Help;

					   if  (  dwTickCnt  -  sdwTickCnt_applyForChkChannels  >  4000  )  {
						   //  for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
						   for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
						   {
							   pMisCnt  =  pProcInfo->getMisCntByIndex(  i  );  //  &pProcInfo->misCnts[i];
							   if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;

							   //  traceLogA(  "toShareBmp: applyForChkChannels"  );
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgVideo.processPointerEvent: rtOp Channel not Ready, applyForChkChannels"  )  );

							   //
							   memset(  &msg_applyForChkChannels,  0,  sizeof(  msg_applyForChkChannels  )  );
							   msg_applyForChkChannels.uiType  =  CONST_misMsgType_applyForChkChannels_qmc;
							   msg_applyForChkChannels.pMisCnt  =  pMisCnt;
							   //
							   if  (  q2PostMsgAndTrigger(  &msg_applyForChkChannels,  sizeof(  msg_applyForChkChannels  ),  &pProcInfo->rtOpQ2,  _T(  "dlgTalk_processPointerEvent"  ))) {
								   showNotification(  0,  0,  0,  0,  0,  0,  _T(  "toShareBmp: applyForChkChannels failed"  )  );
							   }
						   }
						   sdwTickCnt_applyForChkChannels  =  dwTickCnt;
					   }		
			}		  
	
			//  2015/05/12
			#ifdef  __DEBUG__
				traceLog(  _T(  "dlgVideo.processPointerEvent: bRtOpChannelReady false. skipped"  )  );
			#endif

			//  
			iErr  =  0;  goto  errLabel;	
		}

		//

		if  (  isQ2Warning(  &pChannel->toSendQ2,  CONST_uiQNodes_warningInterval_toSendQ  )  )  {
			goto  errLabel;
		}

		//
		{			
			if  (  bMouseMove  )  {
				m_var.remoteAssist.dwTickCnt_sendLastMouseMove  =  GetTickCount(  );
				//  2016/12/26
				//req.u.pointerEvent.uiEventId  =  m_var.dwTickCnt_sendLastMouseMove;
				//
				#ifdef  __DEBUG__
						traceLogA(  "mouseMove sending."  );
				#endif
			}

			//
			m_var.remoteAssist.bNeedSend_lastMouseEvent  =  FALSE;


			//  2017/08/24
			QY_MESSENGER_ID  idInfo_dst;
			idInfo_dst.ui64Id  =  pImg->idInfo_sender.ui64Id;

			//  2017/08/23
			if  (  m_var.addr.uiObjType  ==  CONST_objType_imGrp  )  {
				req.idInfo_imGrp_related.ui64Id  =  m_var.addr.idInfo.ui64Id;
			}

			//
			if  (  postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_outputTask,  0,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  (  char  *  )&req,  sizeof(  req  ),  0,  &idInfo_dst,  uiChannelType,  NULL,  FALSE  )  )  traceLogA(  "postMsg2Mgr_mc failed"  );
		}

#endif

		iErr  =  0;

errLabel:
		return  iErr;
}




//
BOOL CDlgTalk::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int  iErr  =  -1;

	cusDlgRes(  0,  &g_pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//  #define		CONST_bkColor_hangingUp		RGB(  255,  255,  0  )
	//  #define		CONST_bkColor_hangingUp		RGB(  0,  0,  0  )
	#define		CONST_bkColor_hangingUp		RGB(  255,  255,  128  )

	this->m_brush_hangingUp_dlg.CreateSolidBrush(  CONST_bkColor_hangingUp  );

	//  2011/03/16
	//  #define		CONST_bkColor_dlgDesc		RGB(  192,  192,  192  )
	#define		CONST_bkColor_dlgDesc		RGB(  152,  181,  212  )
	this->m_brush_dlgDesc.CreateSolidBrush(  CONST_bkColor_dlgDesc  );

	//  2011/03/28
	#define		CONST_bkColor_applyToRecv_dlgDesc	RGB(  255,  0,  255  )
	this->m_brush_applyToRecv_dlgDesc.CreateSolidBrush(  CONST_bkColor_applyToRecv_dlgDesc  );

	//  2011/03/12
	//  #define		CONST_bkColor_av_dlgDesc		RGB(  0,  255,  240  )
	//  #define		CONST_bkColor_av_dlgDesc		RGB(  128,  255,  0  )
	#define		CONST_bkColor_av_dlgDesc		RGB(  168,  230,  29  )
	this->m_brush_av_dlgDesc.CreateSolidBrush(  CONST_bkColor_av_dlgDesc  );

	//  #define		CONST_bkColor_hangingUp_dlgDesc		RGB(  255,  249,  189  )
	#define		CONST_bkColor_hangingUp_dlgDesc		RGB(  255,  194,  14  )
	this->m_brush_hangingUp_dlgDesc.CreateSolidBrush(  CONST_bkColor_hangingUp_dlgDesc  );

	//
	this->m_brush_meDesc.CreateSolidBrush(  CONST_bkColor_meDesc  );

	//  2011/03/16
	this->m_brush_fullScreen_dlg.CreateSolidBrush(  CONST_bkColor_fullScreen_walls  );
	
	//
	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;


#if  10
	m_var.pm_LargeImageList  =  myImageList_new(  IDB_LARGEICONS, 32, 1, RGB( 255, 255, 255 ) );
	m_var.pm_SmallImageList  =  myImageList_new(  IDB_qnmIcons, 16, 1, RGB( 255, 255, 255 ) );
#endif
	if  (  !m_var.pm_LargeImageList  ||  !m_var.pm_SmallImageList  )  goto  errLabel;


	// TODO: Add extra initialization here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  pFuncs  )  {
		pFuncs->pf_dlgTalk_OnInitDialog(  this->m_hWnd,  &m_var  );
	}


	//  2014/10/11
	CWnd  *  pCtrl  =  NULL;
	pCtrl  =  GetDlgItem(  m_var.av.idc_bgWall_conf  );
	if  (  pCtrl  )  {
		pCtrl->ModifyStyle(  SS_TYPEMASK,  SS_OWNERDRAW  );
	}


	//  2014/04/14. xp容易最小化后，窗口不能恢复，所以禁用最小化菜单
	if  (  bLikeXp( )  )  {
		LONG  style  =  ::GetWindowLong(  m_hWnd,  GWL_STYLE  );

		style  &=  ~(  WS_MINIMIZEBOX  );
		::SetWindowLong(  m_hWnd,  GWL_STYLE,  style  );

		CRect	rc;
		GetWindowRect(  &rc  );
		::SetWindowPos(  m_hWnd,  HWND_NOTOPMOST,  rc.left,  rc.top,  rc.right-rc.left,  rc.bottom - rc.top,  SWP_DRAWFRAME  );
	}

	//
	G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )pFuncs->pf_get_g_guiData(  );
	if  (  !pGuiData  )  goto  errLabel;
	//
	HWND	hCtrl;
	hCtrl  =  ::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_LIST_peerInfo  );
	if  (  hCtrl  )  {
		if  (  pGuiData->hFont_list_dlgTalk_peerInfo  )  {
			::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_list_dlgTalk_peerInfo,  TRUE  );
		}
	}


	//
	iErr  =  0;

errLabel:
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}

	return  TRUE;
}


//
void CDlgTalk::OnOK() 
{
	// TODO: Add extra validation here
	#ifdef  __DEBUG__
			traceLogA(  "dlgTalk OnOK"  );
	#endif
	//  CDialog::OnOK();

}


//
void CDlgTalk::OnCancel() 
{
	// TODO: Add extra cleanup here
	#ifdef  __DEBUG__
			traceLogA(  "CDlgTalk::OnCancel(  )"  );
	#endif
	//  CDialog::OnCancel();

	bQuitDlg(  TRUE  );

}


//
void CDlgTalk::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();

	DLG_TALK_var* pm_var = get_pm_var();
	if (!pm_var)  return;
	DLG_TALK_var& m_var = *pm_var;

	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	//
	void  *  pDlgTalk  =  this;
	dlgTalk_PostNcDestroy(  pm_var  );
	
	
#if  10
	if (!m_var.guiData.bCreated)  traceLogA("DlgTalk::PostNcDestroy(  ): don't need delete");

	if (m_var.guiData.bCreated) {

#ifdef  __DEBUG__
		traceLog(_T("DlgTalk::PostNcDestroy(  ): delete this, %I64u"), m_var.addr.idInfo.ui64Id);
#endif
		//
		if (pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus) {
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("CDlgTalk::PostNcDestroy:to delete this, %I64u,%u"), m_var.addr.idInfo.ui64Id, m_var.addr.uiTranNo_shadow);
		}

		//
		try {
			delete  this;  //pDlgTalk = NULL;
		}
#ifndef  __WINCE__
		catch (CException* e) {
			e->Delete();
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("CDlgTalk::PostNcDestroy failed."));
		}
#endif
		catch (...) {
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("CDlgTalk::PostNcDestroy failed."));
		}
	}
#endif

}


//
  void CDlgTalk::OnDestroy()
{
#ifdef  __DEBUG__
	 traceLogA(  "CDlgTalk::OnDestroy(  ):  enters"  );
#endif
	 //
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return;
	 FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  pFuncs  )  {
		 pFuncs->pf_dlgTalk_OnDestroy(  this->m_hWnd,  get_pm_var()  );
	 }

	 //	 
		//
	 DLG_TALK_var* pm_var = get_pm_var();
	 if (!pm_var)  return;
	 DLG_TALK_var& m_var = *pm_var;

	 //		
	 if (m_var.pm_LargeImageList) {
		 //  tmpbRet  =  (  (  CImageList  *  )m_var.pm_LargeImageList  )->DeleteImageList(  );
		 //  tmpbRet  =  myImageList_DeleteImageList(  m_var.pm_LargeImageList  );
		 myImageList_free(m_var.pm_LargeImageList);
		 m_var.pm_LargeImageList = NULL;
	 }
	 if (m_var.pm_SmallImageList) {
		 //  tmpbRet  =  (  (  CImageList  *  )m_var.pm_SmallImageList  )->DeleteImageList(  );		
		 //  tmpbRet  =  myImageList_DeleteImageList(  m_var.pm_SmallImageList  );
		 myImageList_free(m_var.pm_SmallImageList);
		 m_var.pm_SmallImageList = NULL;

	 }


	 //
	 CDialog::OnDestroy();
	 
#ifdef  __DEBUG__
	 traceLogA(  "CDlgTalk::OnDestroy(  ) leaves"  );
#endif

 }


void CDlgTalk::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	showInfo_open0(  0,  0,   _T(  "dlgTalk.OnClose called"  )  );

	//  CDialog::OnClose();
	bQuitDlg(  TRUE  );

}



 LRESULT CDlgTalk::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	return  pFuncs->pf_dlgTalk_OnQyComm(  this->m_hWnd,  get_pm_var(),  wParam,  lParam  );
}



#include	"DlgMsgTool.h"

 __declspec(  dllexport  )  int  activateImTask(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  int  iTaskId_activated  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#ifndef  __SUPPORT_HTMLEDIT__
		return  -1;
#else
	int								iErr					=	-1;
	DLG_TALK_var				*	pDlgTalkVar				=	(  DLG_TALK_var  *  )pDLG_TALK_var;

	//
	CDlgMsgTool  *  pDlg  =  (  CDlgMsgTool  *  )CWnd::FromHandle(  pDlgTalkVar->msgTool.hWnd_msgTool  );
	if  (  !pDlg  )  return  -1;
	DLG_msgTool_var  &m_var  =  pDlg->m_var;

	CListCtrl					*	pListCtrl				=	(  CListCtrl  *  )pDlg->GetDlgItem(  m_var.msgToolCommon.idcList_task  );
	if  (  !pListCtrl  )  return  -1;
	int								nItem;
	TCHAR							rowIdStr[255  +  1]		=	_T(  ""  );

	//  2013/01/17
	if  (  !m_var.msgToolCommon.m_pHtmlEdit_recentMsgList  )  return  -1;

	if  (  !m_var.msgToolCommon.m_pHtmlEdit_recentMsgList->m_bDisplayInited  )  {
		pDlgTalkVar->iTaskId_activated  =  iTaskId_activated;
		pDlgTalkVar->ucbTaskIdSet  =  TRUE;
		iErr  =  0;  goto  errLabel;
	}

	//
	nItem  =  getTaskItem(  pListCtrl->m_hWnd,  iTaskId_activated  );				  
	if  (  nItem  <  0  )  {					  
		traceLogA(  "CDlgTalk::OnQyComm(  ): "  );  goto  errLabel;				  
	}	
	
	pListCtrl->SetItemState(  nItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
	pListCtrl->Update(  nItem  );

	//  
	pListCtrl->GetItemText(  nItem,  CONST_nSubItem_rowId_cur,  rowIdStr,  mycountof(  rowIdStr  )  );  
	//
	if  (  activateRowByRowId(  hDlgTalk,  rowIdStr  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	return  iErr;
#endif
}


 LRESULT CDlgTalk::OnQyPostComm(  WPARAM  wParam,  LPARAM  lParam  )
{
		MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	return  pFuncs->pf_dlgTalk_OnQyPostComm(  this->m_hWnd,  get_pm_var(),  wParam,  lParam  );
}





 
 





 



 void CDlgTalk::OnSize(UINT nType, int cx, int cy)
 {
	 CDialog::OnSize(nType, cx, cy);

	 // TODO: Add your message handler code here
#ifdef  __DEBUG__
		RECT	rc;
		::GetWindowRect(  m_hWnd,  &rc  );
		RECT	cliRc;
		::GetClientRect(  m_hWnd,  &cliRc  );
		traceLog(  _T(  "dlgTalk: OnSize, w %d, h %d, cliRc.w %d, cliRc.h %d"  ),  rc.right  -  rc.left,  rc.bottom  -  rc.top,  cliRc.right  -  cliRc.left,  cliRc.bottom  -  cliRc.top  );

#endif


	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;


	 //
	 //  if  (  m_var.ucbNewMsgArrives  )  
	 if  (  dlgTalk_bNewMsgArrives(  m_hWnd,  get_pm_var()  )  )
	 {
		 //  m_var.ucbNewMsgArrives  =  FALSE;	//  ÕâÊÇÎªÁËÈ¡ÏûÉÁË¸¡£2008/10/22
		 dlgTalk_set_newMsgArrives(  m_hWnd,  get_pm_var(),  FALSE  );	//  2014/07/14
		 removeNotification(  &m_var.addr.idInfo  );
	 }

	 if  (  m_var.m_scrollInfo.bScrollBarEnabled  )  {
		 this->SetPicRect(  m_var.m_layout.uiW_pic,  m_var.m_layout.uiH_pic,  FALSE  );
	 }
	 //
	 doLayout(  );

	 //
	 InvalidateRect(  NULL,  FALSE  );
	 UpdateWindow(  );
errLabel:

	 return;

 }

#if  0	//  2012/06/26
 void CDlgTalk::Onfullscreen()
 {
	 // TODO: Add your command handler code here
#ifdef  __APP_qyMc_touchscreen__		//  只对pc版的支持
		return;
#endif

	 if  (  m_var.m_bFullScreen  )  return;

	 myGetWindowPlacement(  this->GetSafeHwnd(  ),  &m_var.m_oldWndPlacement  );
	 memcpy(  &m_var.m_oldLayoutParam,  &m_var.layoutParam,  sizeof(  m_var.m_oldLayoutParam  )  );
	 memset(  &m_var.layoutParam,  0,  sizeof(  m_var.layoutParam  )  );
	 //
	 CRect	wndRect;
	 GetWindowRect(  &wndRect  );
	 CRect	clientRect;
	 RepositionBars(  0,  0xffff,  AFX_IDW_PANE_FIRST,  reposQuery,  &clientRect  );
	 ClientToScreen(  &clientRect  );
	 //
	 int  nFullWidth  =  GetSystemMetrics(  SM_CXSCREEN  );
	 int  nFullHeight  =  GetSystemMetrics(  SM_CYSCREEN  );
	 m_var.m_fullScreenRect.left  =  wndRect.left  -  clientRect.left;
	 m_var.m_fullScreenRect.top  =  wndRect.top  -  clientRect.top;
	 m_var.m_fullScreenRect.right  =  wndRect.right  -  clientRect.right  +  nFullWidth;
	 m_var.m_fullScreenRect.bottom  =  wndRect.bottom  -  clientRect.bottom  +  nFullHeight;
	 //
	 m_var.m_bFullScreen  =  TRUE;
	 //
	 WINDOWPLACEMENT	wndPl;
	 wndPl.length  =  sizeof(  WINDOWPLACEMENT  );
	 wndPl.flags  =  0;
	 wndPl.showCmd  =  SW_SHOWNORMAL;
	 wndPl.rcNormalPosition  =  m_var.m_fullScreenRect;
	 mySetWindowPlacement(  this->GetSafeHwnd(  ),  &wndPl  ); 

	 //
	 Invalidate(  TRUE  );	 
}
#endif

  //  2012/06/26
 void CDlgTalk::Onfullscreen()
 {
	 // TODO: Add your command handler code here
#ifdef  __APP_qyMc_touchscreen__		//  只对pc版的支持
		return;
#endif


	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_TALK_var  &  m_var  =  *pm_var;


	 if  (  m_var.m_bFullScreen  )  return;

	 //  2012/07/07
	 makeWndNoBorder(  m_hWnd,  FALSE,  &m_var.m_fullScreenInfo.hOldMenu,  &m_var.m_fullScreenInfo.lOldStyle  );

	 //
	 myGetWindowPlacement(  this->GetSafeHwnd(  ),  &m_var.m_oldWndPlacement  );
	 memcpy(  &m_var.m_oldLayoutParam,  &m_var.m_layoutParam,  sizeof(  m_var.m_oldLayoutParam  )  );
	 memset(  &m_var.m_layoutParam,  0,  sizeof(  m_var.m_layoutParam  )  );
	 //
	 CRect	wndRect;
	 GetWindowRect(  &wndRect  );
	 CRect	clientRect;
	 RepositionBars(  0,  0xffff,  AFX_IDW_PANE_FIRST,  reposQuery,  &clientRect  );
	 ClientToScreen(  &clientRect  );
	 //
	 int  nFullWidth  =  GetSystemMetrics(  SM_CXSCREEN  );
	 int  nFullHeight  =  GetSystemMetrics(  SM_CYSCREEN  );

	 //
	 HMONITOR	hMonitor;
	 POINT		point;
	 point.x  =  (  wndRect.left  +  wndRect.right  )  /  2;
	 point.y  =  (  wndRect.top  +  wndRect.bottom  )  /  2;
	 hMonitor  =  MonitorFromPoint(  point,  MONITOR_DEFAULTTONEAREST  );

	 MONITORINFO mi;
	 mi.cbSize = sizeof(mi);
	 GetMonitorInfo(hMonitor, &mi);

	 RECT	rc;
#if  0
    if (flags & MONITOR_WORKAREA)
		 rc = mi.rcWork;
		 tBuf[0]  =  0;
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "mi.rcWork:l-%d,t-%d,r-%d,b-%d"  ),  rc.left,  rc.top,  rc.right,  rc.bottom  );
		 myMessageBox(  NULL,  tBuf,  _T( "mi.rcWork"  ),  MB_YESNO  );
	else
#endif   
	 rc = mi.rcMonitor;

	 nFullWidth  =  rc.right  -  rc.left;
	 nFullHeight  =  rc.bottom  -  rc.top;

	 //
	 m_var.m_fullScreenRect.left  =  wndRect.left  -  clientRect.left  +  rc.left;
	 m_var.m_fullScreenRect.top  =  wndRect.top  -  clientRect.top;
	 m_var.m_fullScreenRect.right  =  wndRect.right  -  clientRect.right  +  rc.left  +  nFullWidth;
	 m_var.m_fullScreenRect.bottom  =  wndRect.bottom  -  clientRect.bottom  +  nFullHeight;
	 //
	 m_var.m_bFullScreen  =  TRUE;
	 //
	 WINDOWPLACEMENT	wndPl;
	 wndPl.length  =  sizeof(  WINDOWPLACEMENT  );
	 wndPl.flags  =  0;
	 wndPl.showCmd  =  SW_SHOWNORMAL;
	 wndPl.rcNormalPosition  =  m_var.m_fullScreenRect;
	 mySetWindowPlacement(  this->GetSafeHwnd(  ),  &wndPl  ); 

	 //
	 Invalidate(  TRUE  );	 
}



void CDlgTalk::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDialog::OnMoving(fwSide, pRect);

	// TODO: Add your message handler code here
	#ifdef  __DEBUG__
			//traceLog(  _T(  "dlgTalk::OnMoving"  )  );
	#endif
	 //  2011/10/02
	 setMsgToolPos(  m_hWnd  );
	 //
	 setRemotePtzPos(  m_hWnd  );
	 //
	 setSubtitlesPos_talk(  m_hWnd  );
	 //
	 setOfflineResPos_talk(  m_hWnd  );
}



 void CDlgTalk::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë		
	ASSERT(pPopupMenu != NULL);
	
	// check the enabled state of various menu items

	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// determine if menu is popup in top-level menu and set m_pOther to
	//  it if so (m_pParentMenu == NULL indicates that it is secondary popup)
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;    // parent == child for tracking popup
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = GetTopLevelParent();
			// child windows don't have menus -- need to go to the top!
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					// when popup is found, m_pParentMenu is containing menu
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	  state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // menu separator or invalid cmd - ignore it

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// possibly a popup menu, route to first item of that popup
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // first item of popup can't be routed to
			}
			state.DoUpdate(this, FALSE);    // popups are never auto disabled
		}
		else
		{
			// normal menu item
			// Auto enable/disable if frame window has 'm_bAutoMenuEnable'
			//    set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			//  state.DoUpdate(this, m_bAutoMenuEnable && state.m_nID < 0xF000);	//  2007/10/04
			state.DoUpdate(  this,  state.m_nID  <  0xF000  );
		}

		// adjust for menu deletions and additions
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}

}



 void CDlgTalk::OnDropFiles(HDROP hDropInfo)
 {
	 // TODO: Add your message handler code here and/or call default
#ifdef  __WINCE__
		return;
#else
	 //
	 DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_TALK_var  &  m_var  =  *pm_var;


	 //
	 int  iDropCnt  =  DragQueryFile(  hDropInfo,  -1,  NULL,  0  );
	 for  (  int  i  =  0;  i  <  iDropCnt;  i  ++  )  {
		  unsigned  int		nameSize	=  DragQueryFile(  hDropInfo,  i,  NULL,  0  )  +  1;
		  TCHAR  *  pName				=  (  TCHAR  *  )mymalloc(  nameSize  *  sizeof(  TCHAR  )  );
		  if  (  pName  )  {
			  memset(  pName,  0,  nameSize  *  sizeof(  TCHAR  )  );
			  DragQueryFile(  hDropInfo,  i,  pName,  nameSize  );
			  //
			  traceLogA(  "OnDropFiles: %S",  pName  );
			  
			  HWND	hMgr  =  NULL;
			  if  (  isTalkerShadowMgr(  m_var.addr  )  )  hMgr  =  m_hWnd;
			  else  {
				  if  (  isTalkerSubtype_canInput(  m_var.iTalkerSubType  )  )  {
					  TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
					  if  (  pShadow  )  {
						  hMgr  =  pShadow->hMgr;
					  }
				  }
			  }
			  if  (  IsWindow(  hMgr  )  )  {
				  CHelp_getDlgTalkVar	help_getDlgTalkVar;
				  procSendFile(  pName,  NULL,  NULL,  hMgr,  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hMgr  ),  NULL  );
			  }

			  //
			  free(  pName  );
		  }
	 }
	 DragFinish(  hDropInfo  );

	 CDialog::OnDropFiles(hDropInfo);
#endif
 }






void CDlgTalk::OnDblclkLISTmembers(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	traceLogA(  "Dblclick"  );
	QY_MC			*	pQyMc		=		QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	QY_MC_SEL			curSel;

	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_TALK_var  &  m_var  =  *pm_var;

	CListCtrl		*	pListCtrl	=		(  CListCtrl  *  )GetDlgItem(  m_var.idcList_members  );
	int					iCurItem;
	QY_EVENTINFO		tmpEventInfo;


	DWORD dwPos = GetMessagePos();

	/* Convert the co-ords into a CPoint structure */
	CPoint point( GET_X_LPARAM( dwPos ), GET_Y_LPARAM( dwPos ) ), spt;
	spt = point;
	
	/* Convert to screen co-ords for hittesting */
	pListCtrl->ScreenToClient( &spt );

	UINT test;
	iCurItem = pListCtrl->HitTest( spt, &test );
	
	/* Did the click occur on an item */
	if ( iCurItem < 0 || !( test & ( TVHT_ONITEM | TVHT_ONITEMRIGHT ) ) )  goto errLabel;
	
	memset(  &curSel,  0,  sizeof(  curSel  )  );
	curSel.type  =  CONST_qySelType_mcDlgLv;
	curSel.u.mcDlgLv.type  =  m_var.iLvType_memList;
	curSel.u.mcDlgLv.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;
	curSel.u.mcDlgLv.uiDefaultCmd  =  m_var.uiDefaultCmd_memList;

	
	memset(  &tmpEventInfo,  0,  sizeof(  tmpEventInfo  )  );
	tmpEventInfo.type  =  CONST_qyEventType_dblClick;
	tmpEventInfo.hWnd  =  this->m_hWnd;
	tmpEventInfo.hFrom  =  pNMHDR->hwndFrom;
	tmpEventInfo.bDlg  =  TRUE;

	tmpEventInfo.click.x  =  point.x;
	tmpEventInfo.click.y  =  point.y;

	//  
#if  0  //  2017/08/27
	pFuncs->pf_netMc_procTreeEvent(  pQyMc,  &curSel,  &tmpEventInfo  );
#endif

errLabel:
	
	*pResult = 0;
}

void CDlgTalk::OnRclickLISTmembers(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	QY_MC			*	pQyMc		=		QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	QY_MC_SEL			curSel;
	
	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_TALK_var  &  m_var  =  *pm_var;

	CListCtrl		*	pListCtrl	=		(  CListCtrl  *  )GetDlgItem(  m_var.idcList_members  );
	int					iCurItem;
	QY_EVENTINFO		tmpEventInfo;


	DWORD dwPos = GetMessagePos();

	/* Convert the co-ords into a CPoint structure */
	CPoint point( GET_X_LPARAM( dwPos ), GET_Y_LPARAM( dwPos ) ), spt;
	spt = point;
	
	/* Convert to screen co-ords for hittesting */
	pListCtrl->ScreenToClient( &spt );

	UINT test;
	iCurItem = pListCtrl->HitTest( spt, &test );
	
	/* Did the click occur on an item */
	if ( iCurItem < 0 || !( test & ( TVHT_ONITEM | TVHT_ONITEMRIGHT ) ) )  goto errLabel;

	memset(  &curSel,  0,  sizeof(  curSel  )  );
	curSel.type  =  CONST_qySelType_mcDlgLv;
	curSel.u.mcDlgLv.type  =  m_var.iLvType_memList;
	curSel.u.mcDlgLv.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;


	memset(  &tmpEventInfo,  0,  sizeof(  tmpEventInfo  )  );
	tmpEventInfo.type  =  CONST_qyEventType_rClick;
	tmpEventInfo.hWnd  =  this->m_hWnd;
	tmpEventInfo.hFrom  =  pNMHDR->hwndFrom;
	tmpEventInfo.bDlg  =  TRUE;
	tmpEventInfo.click.x  =  point.x;
	tmpEventInfo.click.y  =  point.y;

	pFuncs->pf_netMc_procTreeEvent(  pQyMc,  &curSel,  &tmpEventInfo  );
		
errLabel:	
	
	*pResult = 0;
}


BOOL  b24Fps_av(  int  level  )
{
	BOOL	bRet  =  FALSE;

	AV_COMPRESSOR_CFG	avCompressor_req;
	if  (  myGetAvCompressorCfg(  CONST_capType_av,  0,  0,  level,  &avCompressor_req  )  )  goto  errLabel;

	//  2012/04/09. 这里要校验一下, 要求24帧的都只能在4核以上电脑使用.仅限于demo
	if  (  avCompressor_req.video.common.usMaxFps_toShareBmp  <  24  )  goto  errLabel;
	
	bRet  =  TRUE;

errLabel:

	return  bRet;	
}



 
  void doSelLayoutType(  unsigned  short  usLayoutType_unused,  ConfLayoutParam  *  pParam,  HWND  hDlgTalk_mgr  )
 {
	 // TODO: Add your control notification handler code here
	 QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
 	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	 FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return;
	 QY_DMITEM	*	pTable		=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_usLayoutTypeTable  );
	
#if  0
	 CString	str;
	 GetDlgItemText(  IDC_COMBO_usLayoutType,  str  );

	 //  traceLog(  _T(  "%s"  ),  str  );
	 
	 unsigned  short	usLayoutType	=	qyGetTypeByDes(  pTable,  str  );
#endif

	 CHelp_getDlgTalkVar	help_getDlgTalkVar;
	 DLG_TALK_var	*	pDlgTalkVar	=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk_mgr  );
	 if  (  !pDlgTalkVar  )  goto  errLabel;

	 //  2010/12/27. send usLayoutType to imGrpMems
	 if (pDlgTalkVar->av.taskInfo.bTaskExists) {
		 //
		 if (pDlgTalkVar->av.taskInfo.ucbStarter)
		 {
			 //pFuncs->pf_sendVideoConferenceLayout(usLayoutType_unused, CONST_ pParam, hDlgTalk_mgr, pDlgTalkVar->addr.idInfo, _T("doSelLayoutType"));
		 }
		 else {
			 //
			 QY_MESSENGER_ID idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
			 QY_MESSENGER_ID idInfo_requester; idInfo_requester.ui64Id = pMisCnt->idInfo.ui64Id;
			  //
			 pFuncs->pf_sendVideoConferenceLayout(false ,usLayoutType_unused, CONST_imOp_enlargeImg,  pParam, idInfo_imGrp_related, idInfo_requester, pDlgTalkVar->av.taskInfo.idInfo_starter, _T("doSelLayoutType"));
		 }
	 }

#if  0
	 HWND	hCurTalk  =  NULL;

	 if  (  IsWindow(  m_var.guiData.param.hShadow  )  )  hCurTalk  =  m_var.guiData.param.hShadow;
	 else  hCurTalk  =  m_var.guiData.param.hDlgTalk;

	 ::PostMessage(  hCurTalk,  CONST_qyWm_postComm,  CONST_qyWmParam_setLayout,  usLayoutType  );
#endif

	 //  2012/05/19
	 //  pDlgTalkVar->av.usLayoutType_local  =  usLayoutType;


	 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pDlgTalkVar->pShadowInfo;
	 if  (  !pShadowMgr  )  goto  errLabel;

	 //  2013/02/28
	 pShadowMgr->av.usLayoutType_local  =  usLayoutType_unused;

	 //
#if  0
	 int  i;	 
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		  if  (  !pShadowMgr->shadows[i].hShadow  )  continue;
		  if  (  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
			  DLG_TALK_var  *  pVar  =  getDlgTalkVar(  pShadowMgr->shadows[i].hShadow  );
			  if  (  pVar  )  {
				  pVar->av.usLayoutType_local  =  usLayoutType;
			  }
		  }
	 }
#endif

	 pFuncs->pf_askToRefreshLayout_mgr(  hDlgTalk_mgr  );


errLabel:
	 return;

}



 
  //
   //
  int  doSelIpc(ConfLayoutParam  * pConfLayoutParam, HWND  hTalk_mgr)
  {
	  int  iErr = -1;
	  CCtxQyMc* pQyMc = g_pQyMc;
	  CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	  MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	  if (!pMisCnt)  return  -1;


	  do {
		  CHelp_getDlgTalkVar help_getDlgTalkVar;
		  DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hTalk_mgr);
		  if (!pDlgTalkVar)break;
		  if (!isTalkerShadowMgr(pDlgTalkVar->addr)) break;
		  if (!pDlgTalkVar->av.taskInfo.bTaskExists) break;

		  QY_MESSENGER_ID  idInfo_to = pDlgTalkVar->av.taskInfo.idInfo_starter;	

		  //
		  QY_MESSENGER_ID  idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
		  QY_MESSENGER_ID  idInfo_requester = pMisCnt->idInfo;

		  //
		  sendConfLayout(false,0, CONST_imOp_enlargeChannel,  pConfLayoutParam, idInfo_imGrp_related, idInfo_requester, idInfo_to, _T(""));

		  //
		  iErr = 0;
	  } while (false);

	  return  iErr;
  }


  //
  int  doSelOneBig(ConfLayoutParam* pConfLayoutParam, HWND  hTalk_mgr)
  {
	  int  iErr = -1;
	  CCtxQyMc* pQyMc = g_pQyMc;
	  CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	  MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	  if (!pMisCnt)  return  -1;


	  do {
		  CHelp_getDlgTalkVar help_getDlgTalkVar;
		  DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hTalk_mgr);
		  if (!pDlgTalkVar)break;
		  if (!isTalkerShadowMgr(pDlgTalkVar->addr)) break;
		  if (!pDlgTalkVar->av.taskInfo.bTaskExists) break;

		  QY_MESSENGER_ID  idInfo_to = pDlgTalkVar->av.taskInfo.idInfo_starter;

		  //
		  QY_MESSENGER_ID  idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
		  QY_MESSENGER_ID  idInfo_requester = pMisCnt->idInfo;

		  //
		  sendConfLayout(false,0, CONST_imOp_setOneBig, pConfLayoutParam, idInfo_imGrp_related, idInfo_requester, idInfo_to, _T(""));

		  //
		  iErr = 0;
	  } while (false);

	  return  iErr;
  }





  //
  __declspec(  dllexport  )  void  dlgTalk_OnIsCmd_noSync(  HWND  m_hWnd,  DLG_TALK_var  *  pm_var,  UINT  iMenuId,  QY_wmBuf_command  *  pWmBuf  )
 {	 
	 AFX_MANAGE_STATE(AfxGetStaticModuleState());


#ifdef  __WINCE__
	return;
#else
    int					iErr		=	-1;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	
	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;


	if  (  !pm_var  )  return;
	if  (  !pWmBuf  )  return;


	//  2016/05/24
#if  0
	CQySyncFlg	syncFlg;	
	if  (  syncFlg.sync(  &pm_var->syncFlgs.bInSequence  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_OnIsCmd failed, bLocked already"  )  );
		return;
	}
#endif
	
	//  2012/05/01
	HWND				hCurTalk	=	m_hWnd;
	DLG_TALK_var  *		pCurVar		=  pm_var;
	//
	HWND				hMgr		=	m_hWnd;
	DLG_TALK_var  *		pMgrVar		=	pm_var;
	if  (  !isTalkerShadowMgr(  pm_var->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pm_var->pShadowInfo;
		if  (  !pTalkerShadow  )  goto  errLabel;
		if  (  !IsWindow(  pTalkerShadow->hMgr  )  )  goto  errLabel;
		hMgr  =  pTalkerShadow->hMgr;		//  2013/02/15
		pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr  );
		if  (  !pMgrVar  )  goto  errLabel;

	}

	//
	switch  (  iMenuId  )  {
			case  ID_fullScreen:  {				  
				  CDlgTalk		*	pDlg		=	(  CDlgTalk  *  )CWnd::FromHandle(  m_hWnd  );
				  if  (  !pDlg  )  goto  errLabel;

				  if  (  pm_var->m_bFullScreen  )  pDlg->endFullScreen(  );
				  else  pDlg->Onfullscreen(  );
				  iErr  =  0;  goto  errLabel;
				  }
				  break;
#if  0
			case  ID_stopScrollBar:  {		//  2013/02/26
				  CDlgTalk		*	pDlg		=	(  CDlgTalk  *  )CWnd::FromHandle(  m_hWnd  );
				  if  (  !pDlg  )  goto  errLabel;

				  pDlg->bEnableScrollBar(  FALSE  );
				  pDlg->doLayout(  );
				  iErr  =  0;  goto  errLabel;
				  }
				  break;
			case  ID_startScrollBar:  {		//  2013/02/26
				  CDlgTalk		*	pDlg		=	(  CDlgTalk  *  )CWnd::FromHandle(  m_hWnd  );
				  if  (  !pDlg  )  goto  errLabel;
				  
				  pDlg->bEnableScrollBar(  TRUE  );
				  pDlg->doLayout(  );
				  iErr  =  0;  goto  errLabel;
				  }
				  break;
#endif

			case  ID_msgBox:  {
				  HWND  hDlgTalk	=	m_hWnd;
				  DLG_TALK_var  *  pDlgTalkVar  =  pm_var;

				  //  2014/01/27
				  if  (  !dlgTalk_bMsgBoxShown(  hDlgTalk  )  )  {
					  HWND  hParent  =  hDlgTalk;
					  //  2016/05/24
					  if  (  IsWindow(  pWmBuf->hParent_expected  )  )  {
						  hParent  =  pWmBuf->hParent_expected;
					  }
					  //  2015/06/06
					  if  (  !pProcInfo->bUse_imObjView_as_guiWnd(  )  )  {
						  if  (  bApp_ts_3d(  pQyMc  )  )  {
							  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
							  if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  {
								  goto  errLabel;
							  }
							  hParent  =  pGBuf->hWall_d3d;
						  }
					  }
					  //
					  viewDlgMsgTool_talk(  hParent,  hDlgTalk,  TRUE  );
					  

					  }
				  else  {
					    if  (  pDlgTalkVar->msgTool.hWnd_msgTool  )  {
							if  (  IsWindow(  pDlgTalkVar->msgTool.hWnd_msgTool  )  )  {							
								SendMessageTimeout(  pDlgTalkVar->msgTool.hWnd_msgTool,  WM_CLOSE,  0,  0,  0,  200,  NULL  );						
							}
							if  (  !IsWindow(  pDlgTalkVar->msgTool.hWnd_msgTool  )  )  {
								pDlgTalkVar->msgTool.hWnd_msgTool  =  0;
							}				  
						}
				  }

				  //
				  //  sizeAllControls_dlgTalk(  hDlgTalk,  *pDlgTalkVar,  NULL  );
				  dlgTalk_doLayout(  hDlgTalk  );


				  //  2015/06/08
				  if  (  bApp_ts_3d(  pQyMc  )  )  {
					  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
					  if  (  !pGBuf  )  goto  errLabel;
					  pFuncs->isCliD3d.pf_d3dWall_doLayout(  pGBuf->hWall_d3d  );
				  }
				  //  2016/04/07
				  dyn_d3dWall_askToRefreshMenu(  );

				  //
				  iErr  =  0;  goto  errLabel;
				  }
				  break;
			case  ID_sendFile:  {
				  LPCTSTR							lpszDefExt  =	TEXT("*\0");
				  LPCTSTR							lpszFilter	=	CONST_FILE_FILTER_allFiles;
				  LPCTSTR							title		=	TEXT("Send File...\0");
				  CQyString							pathCStr;
				  DWORD								dwFlags     =	OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;

				  //
				  HWND  hParent  =  m_hWnd;				
				  
				  //  2015/06/06			
				  if  (  !pProcInfo->bUse_imObjView_as_guiWnd(  )  )  {
					  if  (  bApp_ts_3d(  pQyMc  )  )  {
						  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
						  if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  goto  errLabel;
						  hParent  =  pGBuf->hWall_d3d;					  					
					  }
				  }


				  //
				  if  (  qyBrowseForFile(  hParent,  TRUE,  lpszDefExt,  dwFlags,  CONST_FILE_FILTER_allFiles,  title,  NULL,  pQyMc,  pathCStr  )  )  break;

				  //
				  HWND  hDlgTalk	=	m_hWnd;
				  if  (  !pm_var  )  goto  errLabel;
				  DLG_TALK_var  &  m_var  =  *pm_var;

				  //
				  HWND	hMgr  =  NULL;
				  if  (  isTalkerShadowMgr(  m_var.addr  )  )  hMgr  =  m_hWnd;
				  else  {
					    if  (  isTalkerSubtype_canInput(  m_var.iTalkerSubType  )  )  {
							TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
							if  (  pShadow  )  {
								hMgr  =  pShadow->hMgr;					  
							}				  
						}			  
				  }

				  //
				  if  (  IsWindow(  hMgr  )  )  {
					  CHelp_getDlgTalkVar	help_getDlgTalkVar;
					  procSendFile(  pathCStr,  NULL,  NULL,  hMgr,  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hMgr  ),  NULL  );
				  }

				  //
				  iErr  =  0;  goto  errLabel;
				  }				  
				  break;

			case  ID_showDlgMenu:  {
				  HWND  hDlgTalk	=	m_hWnd;
				  BOOL	bRet		=	0;

				  //  2012/07/07
				  if  (  pm_var->m_bFullScreen  )  {
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::bFullScreen is true, ID_showDlgMenu not supported"  )  );
					  goto  errLabel;
				  }

				  //
				  if  (  pm_var->hMenu  )  {
					  bRet  =  ::SetMenu(  hDlgTalk,  pm_var->hMenu  );
					  if  (  bRet  )  {
						  pm_var->hMenu  =  NULL;
					  }
					  }
				  else  {
					    pm_var->hMenu  =  ::GetMenu(  hDlgTalk  );
						bRet  =  ::SetMenu(  hDlgTalk,  NULL  );
				  }

				  //
				  iErr  =  0;  goto  errLabel;

				  }
				  break;

			case  ID_cfgRasOptions:  {	//  2012/07/22
				  showDlgPolicyIsClient(  m_hWnd  );
				  }
				  break;

			case  ID_ucbShowImGrpMems:  
				  switch  (  pm_var->addr.uiObjType  )  {
						  case  CONST_objType_imGrp:
						  case  CONST_objType_tmpGrp:
							    if  (  pm_var->guiData.ucbShowImGrpMems  )  break;
								pm_var->guiData.ucbShowImGrpMems  =  TRUE;
								//
								{
									CWaitCursor	cur;
									//  2014/02/10
									dlgTalk_loadGrpMems(  m_hWnd,  pm_var,  _T(  ""  )  );

									//
									refreshTalkerList(  hMgr  );

								}

								//
								//  sizeAllControls_dlgTalk(  m_hWnd,  *pm_var,  NULL  );
								dlgTalk_doLayout(  m_hWnd  );
							    break;
						  default:
								  break;
				  }
				  //
				  iErr  =  0;  goto  errLabel;
				  break;
			case  ID_ucbHideImGrpMems:
				  switch  (  pm_var->addr.uiObjType  )  {
						  case  CONST_objType_imGrp:
						  case  CONST_objType_tmpGrp:
							    if  (  !pm_var->guiData.ucbShowImGrpMems  )  break;
								pm_var->guiData.ucbShowImGrpMems  =  FALSE;
								//
								//  sizeAllControls_dlgTalk(  m_hWnd,  *pm_var,  NULL  );
								dlgTalk_doLayout(  m_hWnd  );
							    break;
						  default:
							      break;
				  }
				  //
				  iErr  =  0;  goto  errLabel;
				  break;

			case  ID_about:		//  2016/12/30
				  myOnAppAbout(  m_hWnd  );
				  //
				  iErr  =  0;  goto  errLabel;
				  break;

			case  ID_showMoreIa:  //  2017/08/30
				  viewInstantAssistant(  hCurTalk,  CONST_qyWndContentType_talker,  0,  0,  hCurTalk,  TRUE  );
				  iErr  =  0;  goto  errLabel;
				  break;
			case  ID_promptToClose:  {
				  CQyString  hintStr  =  pCurVar->promptToClose.tHint;
				  if  (  !pCurVar->promptToClose.tHint[0]  )  {
					  showInfo_open0(  0,  0,  _T(  "Err: promptToClose.tHint[0] is 0"  )  );
					  goto  errLabel;
				  }
				  pCurVar->promptToClose.tHint[0]  =  0;
				  
				  //
				  HWND  tmp_hWnd;
				  if  (  dlgTalk_findWndForPrompt(  hMgr,  pMgrVar,  &tmp_hWnd,  NULL  )  )  goto  errLabel;
				  //
				  //
				  int  nStep_finished  =  10;
				  if  (  bSupported_fileServer(  pQyMc  )  )  {  //  2015/08/10
					  nStep_finished  =  3;
				  }
				  if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_bjyz  )  {
					  nStep_finished  =  3;
				  }
				  //
				  int  tmpiRet;
				  tmpiRet  =  showProgress(  &pQyMc->gui.progress,  &pQyMc->cusRes,  tmp_hWnd,  hintStr,  NULL,  nStep_finished,  -1,  0  );
				  if  (  tmpiRet  !=  IDOK  &&  tmpiRet  !=  IDTIMEOUT  )  {					
					  goto  errLabel;					  
				  }
				  qyShowInfo1(  CONST_qyShowType_warning,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_OnIsCmd: close window"  )  );
				  PostMessage(  m_hWnd,  WM_CLOSE,  0,  0  );
				  //
				  iErr  =  0;  goto  errLabel;
				  }
				  break;
			case  ID_2dVWall_new:  {  //  2018/12/18
				  //
				  if  (  IsWindow(  pMgrVar->av.hWall  )  )  {
					  MACRO_SetForegroundWindow(  pMgrVar->av.hWall  );
					  iErr  =  0;  goto  errLabel;			
				  }

				  //
				  if  (  !pMgrVar->av.taskInfo.bTaskExists  )  {
					  MessageBox(  m_hWnd,  _T(  "请先启动会议，然后再打开虚拟墙 "  ),  _T(  "qycx.com"  ),  MB_OK  );
					  goto  errLabel;
				  }
				  
				  //  Onnewvirtualwall(  );
				  int  iWndContentType;
				  iWndContentType  =  CONST_qyWndContentType_vWall;
				  //viewVWall(  ::GetDesktopWindow(  ),  _T(  ""  ),  0,  TRUE,  NULL,  FALSE,  NULL  );
				  HWND  hParent  = ::GetDesktopWindow(  );
				  hParent  =  m_hWnd;
				  //
				  HWND  hWall  =  0;
				  viewVWall_hbwj(  hParent,  _T(  ""  ),  CONST_vwSubtype_avStream,  FALSE,  &pm_var->addr.idInfo,  NULL,  FALSE,  &hWall  );
				  pMgrVar->av.hWall  =  hWall;
				  }
				  iErr  =  0;  goto  errLabel;
				  break;

			 default:
					break;
	}

	//
	//
	m_hWnd  =  hMgr;
	pm_var  =  pMgrVar;


	//
	if  (  !IsWindow(  m_hWnd  )  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;
	//CDlgTalk		*	pDlg		=	(  CDlgTalk  *  )CWnd::FromHandle(  m_hWnd  );


	//  2014/05/30
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;	
	if  (  !pShadowMgr  )  goto  errLabel;


	//  traceLogA(  "OnIsCmd, nID %d",  iMenuId  );
	
	if  (  iMenuId  >=  ID_MENU_VDEVICE0  &&  iMenuId  <=  ID_MENU_maxAvCmd  )  {
		switch  (  iMenuId  )  {
				case  ID_MENU_cfgCaptureFilter_v:  {
					  if  (  pProcInfo->av.localAv.videoCaptureProcInfo.bCapDevConnected  )  return;

					  pFuncs->pf_cfgCaptureFilter(  m_var.pCapStuff,  hCurTalk  );
	
					  }
					  return;
					  break;
				case  ID_MENU_cfgCapturePin_v:  {
					  BITMAPINFOHEADER		bih;
	
					  if  (  pProcInfo->av.localAv.videoCaptureProcInfo.bCapDevConnected  )  return;
	
					  TCHAR	displayName[MAX_monikerDisplayNameLen  +  1]	=	_T(  ""  );	
					  if  (  pFuncs->moniker.pf_getMonikerDisplayName(  pFuncs->moniker.pf_getMoniker_v(  m_var.pCapStuff,  m_var.iMenuId_selectedVideo  ),  displayName,  mycountof(  displayName  )  )  )  displayName[0]  =  0;

					  if  (  !pFuncs->pf_cfgCapturePin(  m_var.pCapStuff,  hCurTalk  )  )  {
						  //  memcpy(  &pProcInfo->av.localAv.videoCaptureProcInfo.policy.bih,  &bih,  sizeof(  pProcInfo->av.localAv.videoCaptureProcInfo.policy.bih  )  );
					  }					  

					  }				  
					  return;
					  break;
				case  ID_MENU_cfgCrossBar_v:{
					  void				*	pVideoCapDev  =  NULL;
					  BITMAPINFOHEADER		bih;
	
					  if  (  pProcInfo->av.localAv.videoCaptureProcInfo.bCapDevConnected  )  return;
	
					  TCHAR	displayName[MAX_monikerDisplayNameLen  +  1]	=	_T(  ""  );	
					  if  (  pFuncs->moniker.pf_getMonikerDisplayName(  pFuncs->moniker.pf_getMoniker_v(  m_var.pCapStuff,  m_var.iMenuId_selectedVideo  ),  displayName,  mycountof(  displayName  )  )  )  displayName[0]  =  0;

					  pFuncs->pf_cfgCrossBar(  m_var.pCapStuff,  m_hWnd  );


					  }
					  return;
					  break;

				case  ID_MENU_useWebcam_vfw:
					  //  pProcInfo->cfg.policy.video.ucbUseVfwWebcam  =  TRUE;
					  pProcInfo->cfg.policy.video.uiCamCapType  =  CONST_camCapType_vfw;			//  2010/07/26
					  return;
					  break;
				case  ID_MENU_useWebcam_directX:
					  //  pProcInfo->cfg.policy.video.ucbUseVfwWebcam  =  FALSE;
					  pProcInfo->cfg.policy.video.uiCamCapType  =  CONST_camCapType_directX;		//  2010/07/26
					  return;
					  break;
				case  ID_MENU_useWebcam_custom:
					  //  pProcInfo->cfg.policy.video.ucbUseVfwWebcam  =  FALSE;
					  pProcInfo->cfg.policy.video.uiCamCapType  =  CONST_camCapType_custom;		//  2010/07/26
					  return;
					  break;

				default:
						break;
		}

		
		QY_REG  reg;		
		TCHAR				tBuf[256] =  _T(  ""  );

		if  (  iMenuId  >=  ID_MENU_ADEVICE0  &&  iMenuId  <=  ID_MENU_ADEVICE9  )  {
			
			//				
				int				idc		=	ID_MENU_selectDefaultRecorder;
				unsigned  char  uCheck  =  MF_UNCHECKED;										
				//
				CheckMenuItem(  GetMenu(  hCurTalk  ), idc,  uCheck  );


			//
			memset(  &reg,  0,  sizeof(  reg  )  );
			
			reg.hKeyRoot0  =  HKEY_CURRENT_USER;
			lstrcpyn(  reg.rootKey,  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

			qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_ucbNot_selectDefaultRecorder  ),  _T(  "1"  )  );
			pProcInfo->cfg.policy.audio.ucbNot_selectDefaultRecorder  =  TRUE;
			//
			m_var.iMenuId_selectedAudio  =  iMenuId;
			pFuncs->pf_saveChosenDevice(  m_var.pCapStuff,  m_var.bIncludeACap,  iMenuId  );
			//  getChosenDevice(  pProcInfo->av.localAv.recorder_selected,  mycountof(  pProcInfo->av.localAv.recorder_selected  ),  NULL,  0  );
		}
		if  (  iMenuId  >=  ID_MENU_VDEVICE0  &&  iMenuId  <=  ID_MENU_VDEVICE9  )  {
			
			//
			if  (  pProcInfo->cfg.policy.video.uiCamCapType  ==  CONST_camCapType_rtsp  )  {

				//				
				int				idc		=	ID_MENU_selectRtsp;
				unsigned  char  uCheck  =  MF_UNCHECKED;										
				//
				CheckMenuItem(  GetMenu(  hCurTalk  ), idc,  uCheck  );

			}
			
			//
			memset(  &reg,  0,  sizeof(  reg  )  );
			
			reg.hKeyRoot0  =  HKEY_CURRENT_USER;
			lstrcpyn(  reg.rootKey,  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

			qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_camCapType  ),  CString(  _ltot(  CONST_camCapType_directX,  tBuf,  10  ) ) );
			pProcInfo->cfg.policy.video.uiCamCapType  =  CONST_camCapType_directX;

			//
			m_var.iMenuId_selectedVideo  =  iMenuId;
			pFuncs->pf_saveChosenDevice(  m_var.pCapStuff,  m_var.bIncludeACap,  iMenuId  );
			//  getChosenDevice(  NULL,  0,  pProcInfo->av.localAv.webcam_selected,  mycountof(  pProcInfo->av.localAv.webcam_selected  )  );
		}

		//
		pFuncs->pf_chooseAvDevice_mgr(  m_var.pCapStuff,  m_hWnd,  0,  iMenuId  );
		
		return;
	}




	//
	switch  (  iMenuId  )  {

				  //
			case  ID_ucbNotViewGps:
				  if  (  !pShadowMgr->vwRuleCmd.ucbViewGps  )  break;
				  pShadowMgr->vwRuleCmd.ucbViewGps  =  FALSE;				  
				  break;
			case  ID_ucbViewGps:
				  if  (  pShadowMgr->vwRuleCmd.ucbViewGps  )  break;
				  pShadowMgr->vwRuleCmd.ucbViewGps  =  TRUE;
				  break;

				  //
			case  ID_notShowGpsData:
				  if  (  !pShadowMgr->ucbShowGpsData  )  break;
				  pShadowMgr->ucbShowGpsData  =  FALSE;
				  break;
			case  ID_showGpsData:
				  if  (  pShadowMgr->ucbShowGpsData  )  break;
				  pShadowMgr->ucbShowGpsData  =  TRUE;
				  break;
			case  ID_startShareScreen:  {
				  #ifndef  __WINCE__
						 pFuncs->pf_toSelectRegion1(  m_hWnd,  FALSE,  FALSE,  FALSE,  0,  -1  );
				  #endif
				  }
				  break;
			case  ID_startShareFullScreen:  {
				  //
				  BOOL				bNoPrompt		=	bNoPrompt_selectAvCompressor(  CONST_capType_screen,  0  );				  	
				  //
				  if  (  !bNoPrompt  )  {		
					  if  (  pProcInfo->viewDlgSelectAvCompressor(  hCurTalk,  m_var.addr.idInfo, CONST_capType_screen,  0,  FALSE,  FALSE,  0   )  !=  IDOK  )  goto  errLabel;
				  }
				  //
				  #ifndef  __WINCE__
				 		   pFuncs->pf_toSelectRegion1(  m_hWnd,  TRUE,  FALSE,  FALSE,  0,  -1  );
				  #endif
				  }
				  break;

			case  ID_stopShareScreen:{
				  #ifndef  __WINCE__
				           if  (  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ifStopScreenSharingRemoteAssist  ),  _T(  "www.qycx.com"  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  
							   break;
						   pFuncs->pf_stopAll_avRecord(  );
                  #endif
				  }
				  break;
				  //
			case  ID_stopRemoteAssist:  {
				  #ifndef  __WINCE__
						   if  (  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ifStopScreenSharingRemoteAssist  ),  _T(  "www.qycx.com"  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  
							   break;
						   pFuncs->pf_stopAll_avRecord(  );
				  #endif
				  }
				  break;
			case  ID_startRemoteAssist:  {
				  //
				  #ifndef  __WINCE__
						   pFuncs->pf_toSelectRegion1(  m_hWnd,  FALSE,  TRUE,  FALSE,  0,  -1  );
				  #endif
				  }
				  break;
			case  ID_startFullScreenRemoteAssist:  {
				  //				  
				  BOOL				bNoPrompt		=	bNoPrompt_selectAvCompressor(  CONST_capType_screen,  0  );				  						
				  //  2014/05/05
				  if  (  !bNoPrompt  )  {		
					  if  (  pProcInfo->viewDlgSelectAvCompressor(  hCurTalk,  m_var.addr.idInfo, CONST_capType_screen,  0,  FALSE,  FALSE,  0  )  !=  IDOK  )  goto  errLabel;					  
				  }
				  //
				  #ifndef  __WINCE__
						   pFuncs->pf_toSelectRegion1(  m_hWnd,  TRUE,  TRUE,  FALSE,  0,  -1  );
				  #endif
				  }
				  break;

			case  ID_startShareMediaFile:  {
				  LPCTSTR							lpszDefExt  =	TEXT("*\0");
				  LPCTSTR							lpszFilter	=	CONST_FILE_FILTER_TEXT;
				  LPCTSTR							title		=	TEXT("Open Media File...\0");
				  CQyString							pathCStr;
				  DWORD								dwFlags     =	OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;

				  if  (  qyBrowseForFile(  hCurTalk,  TRUE,  lpszDefExt,  dwFlags,  CONST_FILE_FILTER_TEXT,  title,  NULL,  pQyMc,  pathCStr  )  )  break;

				  //  2012/11/03
				  int	level  =  0;				  
				  
				  //
				  BOOL				bNoPrompt		=	bNoPrompt_selectAvCompressor(  CONST_capType_mediaFile,  0  );
				  	
				  //
				  if  (  !bNoPrompt  )  {		
					  if  (  pProcInfo->viewDlgSelectAvCompressor(  hCurTalk,  m_var.addr.idInfo, CONST_capType_mediaFile,  0,  FALSE,  FALSE,  0  )  !=  IDOK  )  goto  errLabel;
				  }

				  pFuncs->pf_doCmd_startShareMediaFile(  pQyMc,  m_hWnd,  CONST_qyWndContentType_talker,  level,  pathCStr.GetBuffer(  0  ),  NULL,  NULL  );
				  dlgTalk_doLayout(  hCurTalk  );	//  2013/03/14

				  }
				  break;

			case  ID_startShareMediaDevice:  
				  {				
#if 0
				  dlgTalk_shareMediaDevice(  hCurTalk,  iMenuId,  0  );
				  dlgTalk_doLayout(  hCurTalk  );	//  2013/03/14
#endif
				  }
				  break;
			case  ID_startShareMediaDevice_unresizable:
				  {				
#if  0
				  dlgTalk_shareMediaDevice(  hCurTalk,  iMenuId,  CONST_subCapType_unresizable  );
				  dlgTalk_doLayout(  hCurTalk  );	//  2013/03/14
#endif
				  }
				  break;
			case  ID_shareDevice_grp1:
			case  ID_shareDevice_grp2:
			case  ID_shareDevice_grp3:
			case  ID_shareDevice_grp4:

				  {
					//int  doCmd_startAvCall(HWND  hParent, HWND  hCurTalk, int  level, BOOL  b3D, unsigned  char  ucbAvConsole, PARAM_startAvCall* pParam)

					if  (  !isImGrp(  pm_var->addr.uiObjType)  )  break;

					//
					PARAM_startAvCall  param = { 0 };
					int  level = 0;
					bool  b3D = true;
					unsigned  char  ucbAvConsole = true;
					
					//
					param.bNoPrompt = true;
					param.talkerPolicy.uiTaskType = CONST_imTaskType_shareDevice_grp;
					//
					switch  (  iMenuId  )  {
							case  ID_shareDevice_grp1:
								  param.talkerPolicy.shareDevice_grp_index = 1;
								  break;
							case  ID_shareDevice_grp2:
								param.talkerPolicy.shareDevice_grp_index = 2;
								break;
							case  ID_shareDevice_grp3:
								param.talkerPolicy.shareDevice_grp_index = 3;
								break;
							case  ID_shareDevice_grp4:
								param.talkerPolicy.shareDevice_grp_index = 4;
								break;
							default:
									break;
									
					}
					if (!param.talkerPolicy.shareDevice_grp_index)  break;


					//
#ifdef  __DEBUG__
					param.talkerPolicy.conf_iFourcc = pQyMc->appParams.conf_iFourcc_forDbg;
					//
					char  fourccStr[5];
					iFourcc2Str(param.talkerPolicy.conf_iFourcc, fourccStr, mycountof(fourccStr));
					//
					param.conf_usMaxSpeakers = 25;
					//
					if (10) {
						//level = CONST_policyAvLevel_720p;
						level = CONST_policyAvLevel_480p;

						//
						level = CONST_policyAvLevel_1080p; //
						//
						//level = CONST_policyAvLevel_1080p60;
						//
						//level = CONST_policyAvLevel_2160p;
						//
						//level = CONST_policyAvLevel_2160p60;



					}
#endif
					//
					//level = CONST_policyAvLevel_2160p60;


					//
					pProcInfo->doCmd_startAvCall(hCurTalk, hCurTalk, level, b3D, ucbAvConsole, &param);


				  }
				  break;


			case  ID_selAvCompressor:{
				  //
				  if  (  pProcInfo->viewDlgSelectAvCompressor(  hCurTalk,  m_var.addr.idInfo,  CONST_capType_av,  0,  FALSE,  FALSE,  0  )  !=  IDOK  )  goto  errLabel;
				  				
				  TALKER_policy  policy;
				  getTalkerPolicy(  &pm_var->addr.idInfo,  &policy  );
				  //
#if  0
				  pm_var->m_layout.ucbShowBgWall_starter  =  policy.ucbShowBgWall_starter;
				  //
				  pm_var->m_layout.ucbNeverJoinInBgWall  =  policy.ucbNeverJoinInBgWall;
				  pm_var->m_layout.ucbShowBgWall_confMem  =  ucbShowBgWall_confMem;
#endif
				  //pm_var->m_layout.usPollingIntervalInS  =  policy.usPollingIntervalInS;
				  //
#if  0
				  pm_var->m_layout.bgWallLayout.usRows_bg  =  policy.bgWallLayout.usRows_bg;
				  pm_var->m_layout.bgWallLayout.usCols_bg  =  policy.bgWallLayout.usCols_bg;
#endif
				  if  (  !pm_var->av.taskInfo.ucbStarter  )  {
#if  0
					  if  (  pm_var->av.taskInfo.bTaskExists  &&  !pm_var->m_layout.ucbNeverJoinInBgWall  )  {
						  if  (  pm_var->m_layout.ucbShowBgWall_confMem  )  {
							  pShadowMgr->av.joinInBgWall.idcRet_joinInBgWall  =  ID_qyOk;
							  pFuncs->pf_setCurSharedObjUsr_localAv(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv,  hMgr  );  
						  }
						  else  {
								  pShadowMgr->av.joinInBgWall.idcRet_joinInBgWall  =  ID_qyCancel;
						  }
					  }
#endif
				  }
				  //
				  dlgTalk_doLayout(  hCurTalk  );
				  }				  
				  break;
			case  ID_subtitles:  {
				  CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
				  DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurTalk  );
				  if  (  !pCurVar  )  goto  errLabel;

				  //  2015/06/06
				  HWND  hParent  =  hCurTalk;
				  //  2016/05/24
				  if  (  IsWindow(  pWmBuf->hParent_expected  )  )  {
					  hParent  =  pWmBuf->hParent_expected;
				  }
				  //
				  if  (  !bUse_imObjView_as_guiWnd(  )  )  {
					  if  (  bApp_ts_3d(  pQyMc  )  )  {
						  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
						  if  (  !pGBuf  )  goto  errLabel;
						  if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  goto  errLabel;
						  hParent  =  pGBuf->hWall_d3d;
					  }
				  }
				  
				  //  2014/12/15					
				  if  (  pCurVar->addr.uiObjType  !=  CONST_objType_imGrp  )  {
					  myMessageBox(  hParent,  _T(  "Only group can use subtiltes"  ),  _T(  ""  ),  MB_OK  );
					  goto  errLabel;						
				  }				  

				  //
				  if  (  IsWindow(  pCurVar->subtitles.hWnd_subtitles  )  )  {
					  PostMessage(  pCurVar->subtitles.hWnd_subtitles,  WM_CLOSE,  0,  0  );
					  break;
				  }
				  
				  //
				  int  iCapType  =  CONST_capType_mosaic;	//  CONST_capType_av
				  viewDlgSubtitles_talk(  CONST_sharedObjType_av,  iCapType,  0,  0,  hParent,  hCurTalk,  pCurVar,  pMgrVar  );   				  				  
				  
				  //
				  dlgTalk_doLayout(  hCurTalk  );

				  //  2016/04/07
				  dyn_d3dWall_askToRefreshMenu(  );

				  }
				  break;
			case  ID_offlineRes:  {
				  CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
				  DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurTalk  );
				  if  (  !pCurVar  )  goto  errLabel;


				  //
				  if  (  IsWindow(  pCurVar->offlineRes.hTool_offlineRes  )  )  {
					  PostMessage(  pCurVar->offlineRes.hTool_offlineRes,  WM_CLOSE,  0,  0  );
					  break;
				  }

				  //  2015/06/06
				  HWND  hParent  =  hCurTalk;
				  //  2016/05/24
				  if  (  IsWindow(  pWmBuf->hParent_expected  )  )  {
					  hParent  =  pWmBuf->hParent_expected;
				  }
				  //
				  if  (  !bUse_imObjView_as_guiWnd()  )  {
					  if  (  bApp_ts_3d(  pQyMc  )  )  {
						  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
						  if  (  !pGBuf  )  goto  errLabel;
						  if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  goto  errLabel;
						  hParent  =  pGBuf->hWall_d3d;
					}
				  }

				  //
				  viewDlgOfflineRes_talk(  hParent,  hCurTalk,  FALSE,  TRUE,  NULL  );   				  				  
				  
				  //
				  dlgTalk_doLayout(  hCurTalk  );
				  }
				  break;
				  //
			case  ID_remotePtzControl:  {		//  2012/08/05
				  CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
				  DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurTalk  );
				  if  (  !pCurVar  )  goto  errLabel;

				  if  (  IsWindow(  pCurVar->ptzControl.hWnd_ptzControl  )  )  {
					  PostMessage(  pCurVar->ptzControl.hWnd_ptzControl,  WM_CLOSE,  0,  0  );
					  break;
				  }
				  

				  //  2015/06/06
				  HWND  hParent  =  hCurTalk;
				  //  2016/05/24
				  if  (  IsWindow(  pWmBuf->hParent_expected  )  )  {
					  hParent  =  pWmBuf->hParent_expected;
				  }
				  //
				  if  (  !bUse_imObjView_as_guiWnd()  )  {
					  if  (  bApp_ts_3d(  pQyMc  )  )  {
						  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
						  if  (  !pGBuf  )  goto  errLabel;
						  if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  goto  errLabel;
						  hParent  =  pGBuf->hWall_d3d;
					}
				  }
				  
				  //
				  viewRemotePtzControl(  hParent,  hCurTalk  );
				  
				  //
				  //  sizeAllControls_dlgTalk(  hCurTalker,  *pCurVar,  NULL  );					
				  dlgTalk_doLayout(  hCurTalk  );

				  }
				  //
				  break;
			case  ID_remoteVideo:{				
				
				  CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
				  DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurTalk  );
				  if  (  !pCurVar  )  goto  errLabel;


				  DLG_guiDataParam_objs		param;
				  DYN_BMP_RULE				dynBmpRule_selected;
				  
				  //
				  memset(  &dynBmpRule_selected,  0,  sizeof(  dynBmpRule_selected  )  );

				  //
				  memset(  &param,  0,  sizeof(  param  )  );
				  param.uiType  =  CONST_objType_selectRemoteVideo;
				  param.hCurTalk  =  hCurTalk;
				  param.pCurVar  =  pCurVar;							//  2013/06/10
				  param.pMgrVar  =  pMgrVar;
				  param.pObjBuf_selected  =  &dynBmpRule_selected.dynBmp;			//  2014/05/15
				  param.uiSize_pObjBuf_selected  =  sizeof(  dynBmpRule_selected  );
				  
				  //  2015/06/05
				  HWND  hParent  =  hCurTalk;
				  //  2016/05/24
				  if  (  IsWindow(  pWmBuf->hParent_expected  )  )  {
					  hParent  =  pWmBuf->hParent_expected;
				  }
				  //
				  if  (  !bUse_imObjView_as_guiWnd()  )  {
					  if  (  bApp_ts_3d(  pQyMc  )  )  {
						  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
						  if  (  !pGBuf  )  goto  errLabel;
						  if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  goto  errLabel;
						  hParent  =  pGBuf->hWall_d3d;
					}
				  }

				  //
				  if  (  showDlgObjs(  pQyMc->g_hInst,  hParent,  &param  )  )  {
					  goto  errLabel;
				  }

				  #ifdef  __DEBUG__
						  traceLog(  _T(  "dlgTalk_OnIsCmd: showDlgObjs returns, %d,%d"  ),  dynBmpRule_selected.dynBmp.resObj.uiObjType,  (  int  )dynBmpRule_selected.dynBmp.resObj.usIndex_obj  );
				  #endif
				  //
				  if  (  !dynBmpRule_selected.dynBmp.resObj.uiObjType  )  {
					  #ifdef  __DEBUG__
							  traceLog(  _T(  "Select dynBmp failed, uiObjType is 0"  )  );
					  #endif
					  goto  errLabel;
				  }

				  //
				  BOOL  bView  =  FALSE;


				  bView  =  tmpF_bViewRemoteVideo(  &pShadowMgr->vwRuleCmd_manual,  dynBmpRule_selected.dynBmp.resObj.uiObjType,  dynBmpRule_selected.dynBmp.resObj.usIndex_obj,  dynBmpRule_selected.dynBmp.resObj.usHelp_subIndex  );					
				  tmpF_setViewRemoteVideo(  &dynBmpRule_selected,  !bView,  &pShadowMgr->vwRuleCmd_manual  );
				  //  2016/08/03
				  BOOL  bCurView  =  !bView;
				  if  (  !bCurView  )  {
					  if  (  IsWindow(  pCurVar->ptzControl.hWnd_ptzControl  )  )  {
						  CDlgPtzControl  *  pDlgPtzControl  =  (  CDlgPtzControl  *  )CWnd::FromHandlePermanent(  pCurVar->ptzControl.hWnd_ptzControl  );
						  if  (  pDlgPtzControl  )  {
							  if  (  pDlgPtzControl->m_var.bRemote  
								  &&  isSame_resObj(  &pDlgPtzControl->m_var.remote.remoteCamera.qisResObj.resObj,  &dynBmpRule_selected.dynBmp.resObj  )  )
							  {
								  PostMessage(  pCurVar->ptzControl.hWnd_ptzControl,  WM_CLOSE,  0,  0  );
							  }
						  }
					  }
				  }


				  //
				  chkTalkerRules(  hMgr,  pMgrVar  );
				  
				  //
				  unsigned  int		uiObjType			=  0;
				  unsigned  short	usIndex_dynBmp		=  0;
				  int				talkerRuleIndex		=	0;
				  int  i;


				  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->vwRuleCmd.dynBmpRules  );  i  ++  )  {					
					  if  (  pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.uiObjType  ==  dynBmpRule_selected.dynBmp.resObj.uiObjType  
						  &&  pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.usIndex_obj  ==  dynBmpRule_selected.dynBmp.resObj.usIndex_obj  
						  &&  pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.usHelp_subIndex  ==  dynBmpRule_selected.dynBmp.resObj.usHelp_subIndex
						   )  						   
					   {							  
						   break;					  
					   }
				  }
				  if  (  i  ==  mycountof(  pShadowMgr->talkerDynBmps  )  )  goto  errLabel;					
				  talkerRuleIndex  =  i;


				  BOOL			bNeedProgress		=					TRUE;
				  BOOL			bImgRestarted		=					FALSE;

				  //				  	
				  uiObjType  =  dynBmpRule_selected.dynBmp.resObj.uiObjType;
				  usIndex_dynBmp  =  dynBmpRule_selected.dynBmp.resObj.usIndex_obj;
				  unsigned  short  usHelp_subIndex  =  dynBmpRule_selected.dynBmp.resObj.usHelp_subIndex;
				  if  (  tmpF_bViewRemoteVideo(  &pShadowMgr->vwRuleCmd_manual,  uiObjType,  usIndex_dynBmp,  usHelp_subIndex  )  )  {	
					  if  (  tmpF_bViewRemoteVideo(  &pShadowMgr->vwRuleCmd,  uiObjType,  usIndex_dynBmp,  usHelp_subIndex  )  )  {						  
						  //
						  chkToViewDynBmp(  hMgr,  pMgrVar,  talkerRuleIndex,  bNeedProgress,  &bImgRestarted  );										
					  }					
				  }

									
				  if  (  bImgRestarted  )  {

					  TALKER_dynBmp  *  pRule  =  NULL;
					  unsigned  int		uiTranNo			=  0;

					  pRule  =  &pShadowMgr->talkerDynBmps[talkerRuleIndex];
					  uiTranNo  =  pRule->taskInfo.uiTranNo;
											
					  //
					  if  (  showProgress(  &pQyMc->gui.progress,  &pQyMc->cusRes,  hCurTalk,  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo  )  !=  IDOK  )  {
						  goto  errLabel;
					  }

					  //
					  #ifdef  __DEBUG__
							  int  ii;
							  ii  =  9;
					  #endif
				  }
					
				  //
				  closeMoreIa(  hCurTalk  );

				  }
				  //
				  break;
				  
			case  ID_layoutType:  {		//  2013/06/24

				  CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
				  DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurTalk  );
				  if  (  !pCurVar  )  goto  errLabel;


				  DLG_guiDataParam_objs		param;
				  
				  memset(  &param,  0,  sizeof(  param  )  );
				  param.uiType  =  CONST_objType_selectLayoutType;
				  param.hCurTalk  =  hCurTalk;
				  param.pCurVar  =  pCurVar;							//  2013/06/10
				  param.pMgrVar  =  pMgrVar;
				  
				  //
				  //  2015/06/06
				  HWND  hParent  =  hCurTalk;
				  if  (  !bUse_imObjView_as_guiWnd()  )  {
					  if  (  bApp_ts_3d(  pQyMc  )  )  {
						  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
						  if  (  !pGBuf  )  goto  errLabel;
						  if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  goto  errLabel;
						  hParent  =  pGBuf->hWall_d3d;
					}
				  }
				  //
				  if  (  showDlgObjs(  pQyMc->g_hInst,  hParent,  &param  )  )  goto  errLabel;

				  //
				  unsigned  short  usLayoutType = 0;// (unsigned  short)param.o.iVal_selected;
				  ConfLayoutParam confLayoutParam = { 0 };
				  confLayoutParam.enlargeParam.usEnlargeType = CONST_enlargeType_img;
				  confLayoutParam.enlargeParam.ui64Id = param.o.ui64Id_selected;
				  confLayoutParam.enlargeParam.tn_v = param.o.iVal_selected;
				  
				  //
				  pProcInfo->m_ipcProc.op.idInfo.ui64Id = confLayoutParam.enlargeParam.ui64Id;

				  //
				  doSelLayoutType(  usLayoutType,  &confLayoutParam,  hMgr  );

				  
				  }
				  //
				  break;

				  //
			case  ID_ipc: {		//  2013/06/24

				CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
				DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar_cur.getVar(hCurTalk);
				if (!pCurVar)  goto  errLabel;


				DLG_guiDataParam_objs		param;

				memset(&param, 0, sizeof(param));
				param.uiType = CONST_objType_selectIpc;
				param.hCurTalk = hCurTalk;
				param.pCurVar = pCurVar;							//  2013/06/10
				param.pMgrVar = pMgrVar;

				//
				//  2015/06/06
				HWND  hParent = hCurTalk;
				if (!bUse_imObjView_as_guiWnd()) {
					if (bApp_ts_3d(pQyMc)) {
						GBuf_d3d_isCli* pGBuf = (GBuf_d3d_isCli*)pQyMc->pGBuf_d3d;
						if (!pGBuf)  goto  errLabel;
						if (!IsWindow(pGBuf->hWall_d3d))  goto  errLabel;
						hParent = pGBuf->hWall_d3d;
					}
				}
				//
				if (showDlgObjs(pQyMc->g_hInst, hParent, &param))  goto  errLabel;

				//
				// 这里应该触发解码器，使只显示param.o.iVal_sel通道的视频
				pProcInfo->m_ipcProc.op.iChannel = param.o.iVal_selected;
				
				//
				do {
					if (!pMgrVar->av.taskInfo.bTaskExists)  break;
					QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, pMgrVar->av.taskInfo.iIndex_taskInfo);
					if (!pTaskInfo || !pTaskInfo->bUsed)break;
					QMC_taskData_common* pTaskData = (QMC_taskData_common*)pTaskInfo->var.pTaskData;
					if (pTaskData->uiType != CONST_taskDataType_conf)break;
					QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskData;
										
					
					// do sth					
					ConfLayoutParam  confLayoutParam = { 0 };
					//confLayoutParam = pTc->videoConference.confLayoutParam;
					//if (!confLayoutParam.ui64Id)  break;
					//
					confLayoutParam.enlargeParam.usEnlargeType  =  CONST_enlargeType_img;
					confLayoutParam.enlargeParam.ui64Id = pProcInfo->m_ipcProc.op.idInfo.ui64Id;
					confLayoutParam.ipcParam.iChannel = pProcInfo->m_ipcProc.op.iChannel;
					doSelIpc( &confLayoutParam, hMgr);

				} while (false);
				//
				int  ii = 0;

			}

							   break;

							   //
			case  ID_selOneBig: {		//  2013/06/24

				CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
				DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar_cur.getVar(hCurTalk);
				if (!pCurVar)  goto  errLabel;


				DLG_guiDataParam_objs		param;

				memset(&param, 0, sizeof(param));
				param.uiType = CONST_objType_selOneBig;
				param.hCurTalk = hCurTalk;
				param.pCurVar = pCurVar;							//  2013/06/10
				param.pMgrVar = pMgrVar;

				//
				//  2015/06/06
				HWND  hParent = hCurTalk;
				if (!bUse_imObjView_as_guiWnd()) {
					if (bApp_ts_3d(pQyMc)) {
						GBuf_d3d_isCli* pGBuf = (GBuf_d3d_isCli*)pQyMc->pGBuf_d3d;
						if (!pGBuf)  goto  errLabel;
						if (!IsWindow(pGBuf->hWall_d3d))  goto  errLabel;
						hParent = pGBuf->hWall_d3d;
					}
				}
				//
				if (showDlgObjs(pQyMc->g_hInst, hParent, &param))  goto  errLabel;

				//
				QY_MESSENGER_ID  idInfo_sel;
				idInfo_sel.ui64Id = param.o.ui64Id_selected;
				
				//
				do {
					if (!pMgrVar->av.taskInfo.bTaskExists)  break;
					QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, pMgrVar->av.taskInfo.iIndex_taskInfo);
					if (!pTaskInfo || !pTaskInfo->bUsed)break;
					QMC_taskData_common* pTaskData = (QMC_taskData_common*)pTaskInfo->var.pTaskData;
					if (pTaskData->uiType != CONST_taskDataType_conf)break;
					QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskData;


					// do sth					
					ConfLayoutParam  confLayoutParam = { 0 };
					//confLayoutParam = pTc->videoConference.confLayoutParam;
					//if (!confLayoutParam.ui64Id)  break;
					//
					confLayoutParam.oneBigLayoutParam.ucbOneBigLayout = true;
					confLayoutParam.oneBigLayoutParam.ui64Id = idInfo_sel.ui64Id;
					doSelOneBig(&confLayoutParam, hMgr);

				} while (false);
				//
				int  ii = 0;

			}

						break;






			case  ID_rule:  {
				  //

				  //  2015/06/05
				  HWND  hParent  =  hCurTalk;
				  //
				  if  (  IsWindow(  pWmBuf->hParent_expected  )  )  {
					  hParent  =  pWmBuf->hParent_expected;
				  }
				  //
				  if  (  !bUse_imObjView_as_guiWnd(  )  )  {
					  if  (  bApp_ts_3d(  pQyMc  )  )  {
						  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
						  if  (  !pGBuf  )  goto  errLabel;
						  if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  goto  errLabel;
						  hParent  =  pGBuf->hWall_d3d;
					  }
				  }
				  //
				  //  showDlgImObjRule(  hParent,  _T(  ""  ),  &m_var.addr.idInfo  );
				  showDlgImObjRule(  hParent,  m_hWnd  );
				  }
				  break;
			case  ID_msg:  {
				  if  (  bApp_ts(  pQyMc  )  )  {  //  #ifdef  __APP_qyMc_touchscreen__
					  //
					  HWND  hParent  =  hCurTalk;
					  if  (  bApp_ts_3d(  pQyMc  )  )  {
						  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
						  if  (  !pGBuf  )  goto  errLabel;
						  if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  goto  errLabel;
						  hParent  =  pGBuf->hWall_d3d;
					  }
					  					  	
					  //CDlgTalk		*	pDlg		=	(  CDlgTalk  *  )CWnd::FromHandle(  m_hWnd  );
					  CWnd  *  pDlg  =  CWnd::FromHandle(  hParent  );

					  //					
					  CDlgMsgList	dlg(  pDlg  );						 
						
					  if  (  !dlg.bSetDlgInfo(  _T(  ""  ),  &m_var.addr.idInfo  )  )  goto  errLabel;			  						
					  dlg.DoModal(  );
				  }  //  #endif
				  }
				  break;

			case  ID_popupASpecialPrompt:  {
				  //  ::MessageBox(  pQyMc->gui.hMainWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_conferenceTimeout  ),  _T(  "www.qycx.com"  ),  MB_OK  );
				  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_conferenceTimeout  ),  _T(  "www.qycx.com"  ),  MB_OK  );
				  }
				  break;
			case  ID_MENU_selectRtsp:		{
#if  0
				  CDlgRtspUrl   dlg;
				  //  2016/06/16
				  BOOL  bEditRtspUrlForConf  =  TRUE;
				  dlg.bSetDlgInfo(  bEditRtspUrlForConf  );
				  //
				  if  (  dlg.DoModal( )  ==  IDOK  )  
#endif
				  TCHAR  tUrl[256]  =  _T(  ""  );
				  if  (  !pFuncs->messenger_help.pf_toEditRtspUrlForConf  )  goto  errLabel;
				  if  (  pFuncs->messenger_help.pf_toEditRtspUrlForConf(  tUrl,  mycountof(  tUrl  )  )  )  {
					  goto  errLabel;
				  }
				  {					  	
					  TCHAR  tBuf[256]  =  _T(  ""  );
					  HMENU  hMenu  =  GetMenu(  hCurTalk  );
						
					  if  (  pProcInfo->cfg.policy.video.uiCamCapType  ==  CONST_camCapType_directX  )  {					  
						  if  (  m_var.iMenuId_selectedVideo  )  CheckMenuItem(  hMenu,  m_var.iMenuId_selectedVideo,  MF_UNCHECKED  );
					  }

					  //
					  QY_REG  reg;
					  memset(  &reg,  0,  sizeof(  reg  )  );
					  
					  reg.hKeyRoot0  =  HKEY_CURRENT_USER;
					  lstrcpyn(  reg.rootKey,  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
					  
					  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_camCapType  ),  CString(  _ltot(  CONST_camCapType_rtsp,  tBuf,  10  ) ) );
					  //  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_rtspUrl_selected  ),  dlg.m_var.tUrlBuf  );
					  pProcInfo->cfg.policy.video.uiCamCapType  =  CONST_camCapType_rtsp;
					  m_var.iMenuId_selectedVideo  =  0;

					  //
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  _T(  "Rtsp stream: "  ),  tUrl  );						
					  ModifyMenu(  hMenu,  iMenuId,  MF_BYCOMMAND | MF_STRING,  iMenuId,  tBuf  );
					  CheckMenuItem(  hMenu, iMenuId,  MF_CHECKED  );
						

				  }
				  }
				  break;
			case  ID_MENU_selectDefaultRecorder:  {	//  2014/7/31

					  HMENU  hMenu  =  GetMenu(  hCurTalk  );

					  //
					  if  (  pProcInfo->cfg.policy.audio.ucbNot_selectDefaultRecorder  )  {
						  if  (  m_var.iMenuId_selectedAudio  )  CheckMenuItem(  hMenu,  m_var.iMenuId_selectedAudio,  MF_UNCHECKED  );
					  }
					  				  
					  //
					  QY_REG  reg;
					  memset(  &reg,  0,  sizeof(  reg  )  );
					  
					  reg.hKeyRoot0  =  HKEY_CURRENT_USER;
					  lstrcpyn(  reg.rootKey,  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
					  
					  qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_ucbNot_selectDefaultRecorder  ) );
					  pProcInfo->cfg.policy.audio.ucbNot_selectDefaultRecorder  =  FALSE;

					  //
					  CheckMenuItem(  hMenu, iMenuId,  MF_CHECKED  );

				  }
				  break;

			case  ID_startAvCall:		{
				  CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
				  DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurTalk  );
				  if  (  !pCurVar  )  goto  errLabel;

				  //  
				  BOOL  b3D  =  FALSE;
				  //  2017/07/17
				  unsigned  char  ucbAvConsole  =  FALSE;
				  
				  //  2015/06/04
				  if  (  !bUse_imObjView_as_guiWnd(  )  )  {
					  if  (  bApp_ts_3d(  pQyMc  )  )  {
						  b3D  =  TRUE;
						  //
						  //  2015/06/05
						  if  (  pCurVar->addr.uiObjType  !=  CONST_objType_imGrp  )  {
							  b3D  =  FALSE;
						  }
						  //
						  GBuf_d3d_isCli  *  pGBuf		=  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
						  if  (  !pGBuf  )  goto  errLabel;

						  HWND  hWall_d3d  =  pGBuf->hWall_d3d;
						  if  (  !IsWindow(  hWall_d3d  )  )  goto  errLabel;
						  //
						  pProcInfo->doCmd_startAvCall(  hWall_d3d,  hMgr,  0,  b3D,  ucbAvConsole,  mynull  );
						  //
						  break;					  
					  }
				  }

				  //
				  if  (  pCurVar->iTalkerSubType  ==  CONST_talkerSubtype_3dTool  )  {
					  b3D  =  TRUE;
					  //  2015/06/05
					  if  (  pCurVar->addr.uiObjType  !=  CONST_objType_imGrp  )  {
						  b3D  =  FALSE;
					  }
					  //
					  HWND  hWall_d3d  =  GetParent(  hCurTalk  );
					  //
					  pProcInfo->doCmd_startAvCall(  hWall_d3d,  hMgr,  0,  b3D,  ucbAvConsole,  mynull  );
					  //
					  break;					  
				  }

				  //
				  if (pQyMc->appParams.bConfServer) {
					  b3D = TRUE;
					  //  2015/06/05
					  if (pCurVar->addr.uiObjType != CONST_objType_imGrp) {
						  b3D = FALSE;
					  }
				  }

				  PARAM_startAvCall  param = { 0 };
				  int  level = 0;
				  //
#ifdef  __DEBUG__
				  param.ucb2Streams = pQyMc->appParams.ucb2Streams_forDbg;
				  param.talkerPolicy.conf_iFourcc = pQyMc->appParams.conf_iFourcc_forDbg;

				  //
				  //param.talkerPolicy.uiTaskType = CONST_imTaskType_shareDevice_grp;
				  //param.talkerPolicy.shareDevice_grp_index = 1;
				  //
				  //param.talkerPolicy.gpu_usIndex =  2; 


				  //
				  char  fourccStr[5];
				  iFourcc2Str(param.talkerPolicy.conf_iFourcc, fourccStr, mycountof(fourccStr));
				  //
				  param.conf_usMaxSpeakers = 25;
				  //
				  if (10) {
					  //level = CONST_policyAvLevel_720p;
					  level = CONST_policyAvLevel_480p;


					  //
					  //level = CONST_policyAvLevel_1080p; //
					  //
					  //level = CONST_policyAvLevel_1080p60;
					  //
					  //level = CONST_policyAvLevel_2160p;
					  //
					  //level = CONST_policyAvLevel_2160p60;

					  //
					  //param.talkerPolicy.conf_bitrateInKbps_dl = 4000;
					  //param.talkerPolicy.conf_bitrateInKbps_ul = 4000;


					  
				  }
#endif
				  //
				  //level = CONST_policyAvLevel_2160p60;


				  //
				  pProcInfo->doCmd_startAvCall(  hCurTalk,  hCurTalk,  level,  b3D,  ucbAvConsole,  &param  );
				  
				  }
				  break;

			case  ID_stopAvCall:
				  break;
			case  ID_qyTest:
				  #ifdef  __DEBUG__
						  //
				{
						  //viewTestSpeed(  hCurTalker  );

#if  10
					//
					if  (  !IsWindow(  pShadowMgr->bgWall.hBgWall  )  )  {
						  QY_OBJ_DB  *  pObjDb  =  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
						  if  (  !pObjDb  )  goto  errLabel;
						  //
						  BOOL  bNeedNotShowWnd  =  FALSE;
						  HWND  hWall  =  NULL;
						  //
						  viewBgWall(  hCurTalk,  _T(  ""  ),  CONST_vwSubtype_bgWall,  hMgr,  NULL,  bNeedNotShowWnd,  &hWall  );   
						  //
						  if  (  IsWindow(  hWall  )  )  {
							  pShadowMgr->bgWall.hBgWall  =  hWall;
							  pShadowMgr->bgWall.iWndContentType_hBgWall  =  CONST_qyWndContentType_vWall;	//  2017/10/05
					
							  //
							  D3D_talkerData_cfg  *  pTalkerDataCfg  =  (  D3D_talkerData_cfg  *  )&pMgrVar->d3d_talkerData_cfg;
							  if  (  !pTalkerDataCfg  )  goto  errLabel;

							  //
							  timestamp_renew(   NULL,  &pTalkerDataCfg->ts_layout,  _T("dlgTalk_OnIsCmd_noSync.l6175"));


						  }
						  //

					}
#endif
					//
#if  0

					  unsigned  short			usCnt_monPics_row	=		1;
					  unsigned  short			usCnt_monPics_col	=		1;
					  unsigned  int				uiInitW				=		640;
					  unsigned  int				uiInitH				=		480;
					  BOOL						bScrollBarEnabled	=		FALSE;
					  BOOL						bVideoConference	=		FALSE;
					  BOOL						bRemoteAssist		=		FALSE;

					//
					//  uiInitW  =  pImg->iW_org;
					 // uiInitH  =  pImg->iH_org;

					  PARAM_dlgVideos	params  =  {0};
					  //
					  //params.m_var.iTaskId  =  pImg->iTaskId;
					  //params.m_var.pImgs  =  &pZone->images;
					  //params.m_var.iIndex_capImage  =  j;
					  params.usCnt_monPics_row  =  usCnt_monPics_row;
					  params.usCnt_monPics_col  =  usCnt_monPics_col;
					  params.uiInitW  =  uiInitW;
					  params.uiInitH  =  uiInitH;
					  params.bScrollBarEnabled  =  bScrollBarEnabled;
					  params.bVideoConference  =  bVideoConference;
					  params.bRemoteAssist  =  bRemoteAssist;
	
					  //  2012/05/27
					  //params.hParent  =  m_hWnd;
					  
					  //
					  if  (  IsWindow(  pShadowMgr->secondView.hWnd_dlgVideos  )  )  {
						  goto  errLabel;
					  }

					  //
					  HWND  hWnd  =  NULL;
					  //
					  showDlgVideos(  hCurTalk,  hMgr,  TRUE,  &params,  &m_var.pMisCnt->subWnds,  &hWnd  );
					  //
					  if  (  !IsWindow(  hWnd  )  )  goto  errLabel;
					  pShadowMgr->secondView.hWnd_dlgVideos  =  hWnd;
#endif
					  
				}
				  #endif
				  break;

			default:
					break;
	}	
errLabel:
	return;
#endif
}




//
void CDlgTalk::OnIsCmd(  UINT iMenuId  )
{
	DLG_TALK_var  *  pm_var  =  get_pm_var(  );
	if  (  !pm_var  )  return;

	//  2016/05/24
	CQySyncFlg	syncFlg;	
	if  (  syncFlg.sync(  &pm_var->syncFlgs.bInSequence  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_OnIsCmd failed, bLocked already"  )  );
		return;
	}

	QY_wmBuf_command  wmBuf  =  {0};
	dlgTalk_OnIsCmd_noSync(  m_hWnd,  get_pm_var(),  iMenuId,  &wmBuf  );
}



void dlgTalk_OnUpdateIsCmd(  HWND  m_hWnd,  DLG_TALK_var  *  pm_var,  CCmdUI *pCmdUI)
{	
#ifdef  __WINCE__
	return;
#else
	int					iErr		=	-1;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
  	BOOL				bEnable	=	TRUE;
	QY_MC			*	pQyMc	=	QY_GET_GBUF(  );
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	
	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;

	if  (  !pm_var  )  return;

	switch  (  pCmdUI->m_nID  )  {
			case  ID_ucbHideImGrpMems:
				  if  (  !pm_var->guiData.ucbShowImGrpMems  )  pCmdUI->Enable(  FALSE  );
				  iErr  =  0;  goto  errLabel;
				  break;
			case  ID_ucbShowImGrpMems:
				  if  (  pm_var->guiData.ucbShowImGrpMems  )  pCmdUI->Enable(  FALSE  );
				  iErr  =  0;  goto  errLabel;
				  break;
#if  0
			case  ID_stopScrollBar:
				  if  (  !pm_var->m_scrollInfo.bScrollBarEnabled  )  pCmdUI->Enable(  FALSE  );
				  iErr  =  0;  goto  errLabel;
				  break;
			case  ID_startScrollBar:
				  if  (  pm_var->m_scrollInfo.bScrollBarEnabled  )  pCmdUI->Enable(  FALSE  );
				  iErr  =  0;  goto  errLabel;
				  break;
#endif

			default:
					break;
	}

	//  2012/05/01
	if  (  !isTalkerShadowMgr(  pm_var->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pm_var->pShadowInfo;
		if  (  !pTalkerShadow  )  goto  errLabel;
		if  (  !IsWindow(  pTalkerShadow->hMgr  )  )  goto  errLabel;
		DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr  );
		if  (  !pMgrVar  )  goto  errLabel;

		pm_var =  pMgrVar;
	}

	DLG_TALK_var  &  m_var  =  *pm_var;
	
	//  2014/05/30
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;	
	if  (  !pShadowMgr  )  goto  errLabel;

	//
	if  (  pCmdUI->m_nID  >=  ID_MENU_VDEVICE0  &&  pCmdUI->m_nID  <=  ID_MENU_maxAvCmd  )  {
		switch  (  pCmdUI->m_nID  )  {
				case  ID_MENU_cfgCaptureFilter_v:		
				case  ID_MENU_cfgCapturePin_v:
				case  ID_MENU_cfgPreviewPin_v:
				case  ID_MENU_cfgCrossBar_v:
					  if  (  pProcInfo->av.localAv.videoCaptureProcInfo.bCapDevConnected  )  pCmdUI->Enable(  FALSE  );
					  break;
				case  ID_MENU_useWebcam_vfw:
					  if  (  pProcInfo->av.localAv.videoCaptureProcInfo.bCapDevConnected  )  pCmdUI->Enable(  FALSE  );
					  if  (  pProcInfo->cfg.policy.video.uiCamCapType  ==  CONST_camCapType_vfw  )  pCmdUI->Enable(  FALSE  );
					  break;
				case  ID_MENU_useWebcam_directX:
					  if  (  pProcInfo->av.localAv.videoCaptureProcInfo.bCapDevConnected  )  pCmdUI->Enable(  FALSE  );
					  if  (  pProcInfo->cfg.policy.video.uiCamCapType  ==  CONST_camCapType_directX  )  pCmdUI->Enable(  FALSE  );
					  break;
				case  ID_MENU_useWebcam_custom:
					  if  (  pProcInfo->av.localAv.videoCaptureProcInfo.bCapDevConnected  )  pCmdUI->Enable(  FALSE  );
					  if  (  pProcInfo->cfg.policy.video.uiCamCapType  ==  CONST_camCapType_custom  )  pCmdUI->Enable(  FALSE  );
					  break;
				default:
					    if  (  pCmdUI->m_nID  >=  ID_MENU_ADEVICE0  &&  pCmdUI->m_nID  <=  ID_MENU_ADEVICE9  )  {
							if  (  m_var.bIncludeACap  )  {
								if  (  pFuncs->pf_bRecorderUsing(  pProcInfo,  pFuncs->moniker.pf_getMoniker_a(  m_var.pCapStuff,  pCmdUI->m_nID  ),  NULL,  NULL  )  )  pCmdUI->Enable(  FALSE  );
							}
							else  {
								  if  (  pProcInfo->av.localAv.recordSoundProcInfo.thread.bRunning  )  pCmdUI->Enable(  FALSE  );	
							}
							}
						else  {
							  if  (  pFuncs->pf_bWebcamUsing(  pProcInfo,  0,  pFuncs->moniker.pf_getMoniker_v(  m_var.pCapStuff,  pCmdUI->m_nID  ),  NULL,  NULL,  NULL  )  )  pCmdUI->Enable(  FALSE  );  
						}
						break;
		}
		return;
	}
	


	//
	switch  (  pCmdUI->m_nID  )  {
			//  2014/07/31
			case  ID_MENU_selectRtsp:
				  if  (  pProcInfo->av.localAv.videoCaptureProcInfo.bCapDevConnected  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_MENU_selectDefaultRecorder:
				  if  (  pProcInfo->av.localAv.recordSoundProcInfo.thread.bRunning  )  pCmdUI->Enable(  FALSE  );  
				  break;

			case  ID_ucbNotViewGps:
				  if  (  !pShadowMgr->vwRuleCmd.ucbViewGps  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_ucbViewGps:
				  if  (  pShadowMgr->vwRuleCmd.ucbViewGps  )  pCmdUI->Enable(  FALSE  );
				  break;

				  //
			case  ID_notShowGpsData:
				  if  (  !pShadowMgr->ucbShowGpsData  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showGpsData:
				  if  (  pShadowMgr->ucbShowGpsData  )  pCmdUI->Enable(  FALSE  );
				  break;

			case  ID_startShareScreen:  {
				  #ifndef  __WINCE__
						   if  (  !canShareScreen(  pProcInfo  )  )  pCmdUI->Enable(  FALSE  );
				  #endif				  
				  }
				  break;
			case  ID_startShareFullScreen:  {
				  #ifndef  __WINCE__
						   if  (  !canShareScreen(  pProcInfo  )  )  pCmdUI->Enable(  FALSE  );
				  #endif
				  }
				  break;

			case  ID_stopShareScreen:{
				  }
				  break;
				  //
			case  ID_stopRemoteAssist:  {
				  }
				  break;
			case  ID_startRemoteAssist:  {
				  if  (  !canRemoteAssist(  pProcInfo  )  )  pCmdUI->Enable(  FALSE  );
				  }
				  break;
			case  ID_startFullScreenRemoteAssist:  {
				  if  (  !canRemoteAssist(  pProcInfo  )  )  pCmdUI->Enable(  FALSE  );
				  }
				  break;
			case  ID_startShareMediaFile:
				  break;
			case  ID_startShareMediaDevice:
				  break;				 
			case  ID_remotePtzControl:  {
				  if  (  !canRemotePtzControl(  pProcInfo  )  )  pCmdUI->Enable(  FALSE  );
				  }
				  break;
			case  ID_qyTest:  {
				  #ifdef  __DEBUG__
						  pCmdUI->Enable(  TRUE  );
				  #endif
				  }
				  break;
			case  ID_stopAvCall:
			default:
					break;
	}

errLabel:

	return;

#endif
}


void CDlgTalk::OnUpdateIsCmd(CCmdUI *pCmdUI)
{
	dlgTalk_OnUpdateIsCmd(  m_hWnd,  get_pm_var(),  pCmdUI  );
}









 BOOL  setRemotePtzPos(  HWND  hCurTalker  )
{		
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );	
	if  (  !pProcInfo  )  return  FALSE;

	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurTalker  );
	if  (  !pCurTalkerVar  )  return  FALSE;

	if  (  !IsWindow(  pCurTalkerVar->ptzControl.hWnd_ptzControl  )  )  return  FALSE;

	RECT	rc;
	GetWindowRect(  GetDlgItem(  hCurTalker,  pCurTalkerVar->guiData.iIDC_STATIC_ptz  ),  &rc  );
	//
	MoveWindow(  pCurTalkerVar->ptzControl.hWnd_ptzControl,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  TRUE  );

	return  TRUE;
}

 BOOL  setSubtitlesPos_talk(  HWND  hCurTalker  )
{		
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );	
	if  (  !pProcInfo  )  return  FALSE;

	CHelp_getDlgTalkVar		help_getDlgTalkVar_cur;
	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurTalker  );
	if  (  !pCurTalkerVar  )  return  FALSE;

	if  (  !IsWindow(  pCurTalkerVar->subtitles.hWnd_subtitles  )  )  return  FALSE;

	RECT	rc;
	GetWindowRect(  GetDlgItem(  hCurTalker,  pCurTalkerVar->guiData.iIDC_STATIC_subtitles  ),  &rc  );
	//
	//MoveWindow(  pCurTalkerVar->subtitles.hWnd_subtitles,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  TRUE  );
	UINT  uFlags;
	uFlags  =  1  ?  SWP_SHOWWINDOW  :  SWP_HIDEWINDOW;
	SetWindowPos(  pCurTalkerVar->subtitles.hWnd_subtitles,  NULL,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  uFlags  );


	return  TRUE;
}

 BOOL  setOfflineResPos_talk(  HWND  hCurTalker  )
{		
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );	
	if  (  !pProcInfo  )  return  FALSE;

	CHelp_getDlgTalkVar		help_getDlgTalkVar_cur;
	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurTalker  );
	if  (  !pCurTalkerVar  )  return  FALSE;

	if  (  !IsWindow(  pCurTalkerVar->offlineRes.hTool_offlineRes  )  )  return  FALSE;

	RECT	rc;
	GetWindowRect(  GetDlgItem(  hCurTalker,  pCurTalkerVar->guiData.iIDC_STATIC_offlineRes  ),  &rc  );
	//
	UINT  uFlags;
	uFlags  =  1  ?  SWP_SHOWWINDOW  :  SWP_HIDEWINDOW;
	SetWindowPos(  pCurTalkerVar->offlineRes.hTool_offlineRes,  NULL,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  uFlags  );


	return  TRUE;
}




#ifdef  __DEBUG__
#if  0
	DMO_info_vmr	tmp_gDmoInfo;
	BOOL	bInited  =  FALSE;
#endif
#endif

	

void dlgTalk_qyTest()
{
	// TODO: Add your command handler code here
#ifndef  __DEBUG__
		 return;
#else



	//  startToParse(  );

	//  test 代码写在下面
	int  i  =  0;
#if  0
	if  (  !bInited  )  {

		memset(  &tmp_gDmoInfo,  0,  sizeof(  tmp_gDmoInfo  )  );

		OpenClip(  this->m_hWnd,  &bih_in,  rect,  &tmpCfg,  &pQyMc->cfg.rwLockParam,  &tmp_gDmoInfo  );
		bInited  =  TRUE;
	}
	else  {
		  CloseClip(  &tmp_gDmoInfo  );
		  bInited  =  FALSE;
	}
#endif

	//
#if  0
	//__declspec(  dllexport  ) int  viewVwf(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  fileName  );
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	QY_OBJ_DB  *  pObjDb  =  pFuncs->pf_getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  );
	TCHAR  *  fileName  =  _T(  "C:\tttbbb\\1\\20150510\\1.qvcf"  );
	viewQvcf(  m_hWnd,  pObjDb,  fileName  );  
#endif



#endif





}


void CDlgTalk::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);


	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_TALK_var  &  m_var  =  *pm_var;


	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë
	if  (  nState  !=  WA_INACTIVE  )  {
		BOOL	bFore	=	(  ::GetForegroundWindow(  )  ==  this->m_hWnd  );
		//  traceLog(  _T(  "DlgTalk::OnActivate  ... , nState %d, bInited %d, bFore %d, bMin %d"  ),  nState,  m_var.guiData.bInited,  bFore,  bMinimized  );
		if  (  m_var.guiData.bFinished_createCtrls  &&  bFore  &&  !bMinimized  )  {
			//  if  (  m_var.ucbNewMsgArrives  )  
			if  (  dlgTalk_bNewMsgArrives(  m_hWnd,  &m_var  )  )
			{
				//  m_var.ucbNewMsgArrives  =  FALSE;
				dlgTalk_set_newMsgArrives(  m_hWnd,  &m_var,  FALSE  );
				removeNotification(  &m_var.addr.idInfo  );
			}
		}
	}
}

BOOL CDlgTalk::OnNcActivate(BOOL bActive)
{
	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;


	// TODO: Add your message handler code here and/or call default
	//  traceLog(  _T(  "DlgTalk::OnNcActivate  ... , bActivate %d, bInited %d"  ),  bActive,  m_var.guiData.bInited  );
	if  (  m_var.guiData.bFinished_createCtrls  &&  bActive  )  {
		BOOL	bFore	=	(  ::GetForegroundWindow(  )  ==  this->m_hWnd  );
		if  (  bFore  )  {
			//  if  (  m_var.ucbNewMsgArrives  )  
			if  (  dlgTalk_bNewMsgArrives(  m_hWnd,  &m_var  )  )
			{
				//  m_var.ucbNewMsgArrives  =  FALSE;
				dlgTalk_set_newMsgArrives(  m_hWnd,  &m_var,  FALSE  );
				removeNotification(  &m_var.addr.idInfo  );
			}
		}
	}

	//
#ifdef  __USE_skin__
	M_myOnNcPaint(  this,  (&m_skinProc)  );
#else
	return CDialog::OnNcActivate(bActive);
#endif

errLabel:

	return  TRUE;
	
}


void CDlgTalk::OnBnClickedCancel()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	OnCancel();
}





 //  2012/05/05

 int  OnMove_resourcesWnd(  HWND  hDlg,  int  x,  int  y  )
{
#if  0
	CDlgVideos	*	pDlg	=	(  CDlgVideos  *  )CWnd::FromHandle(  hDlg  );
	if  (  !pDlg  )  return  -1;
#endif

	/*
	locateVideoWnd_training_default(  pDlg->m_var.hDlgTalk  );
	*/

	return  0;
}










#ifdef  __DEBUG__

int  myPrintMsg(  MSG  *  pMsg  )
{

	TCHAR	*	pT	=	_T(  ""  );
	switch  (  pMsg->message  )  {
		    case  WM_MOUSEMOVE:  {
				  long  lParam  =  pMsg->lParam;
				  int  xPos = GET_X_LPARAM(lParam); 
				  int  yPos = GET_Y_LPARAM(lParam);

				  switch  (  pMsg->wParam  )  {
						  case  MK_CONTROL:
							    pT  =  _T(  "c"  );
								break;
						  case  MK_LBUTTON:
							    pT  =  _T(  "l"  );
								break;
						  case  MK_MBUTTON:
							    pT  =  _T(  "m"  );
								break;
						  case  MK_RBUTTON:
							    pT  =  _T(  "r"  );
								break;
						  case  MK_SHIFT:
							    pT  =  _T(  "s"  );
								break;
						  case  MK_XBUTTON1:
							    pT  =  _T(  "x1"  );
								break;
						  case  MK_XBUTTON2:
							    pT  =  _T(  "x2"  );
								break;
				  }

				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::mousemove, x %d, y %d. %s"  ),  xPos,  yPos,  pT  );
				  }
				  break;
			case  WM_LBUTTONDOWN:{
				  long  lParam  =  pMsg->lParam;
				  int  xPos = GET_X_LPARAM(lParam); 
				  int  yPos = GET_Y_LPARAM(lParam); 
				  switch  (  pMsg->wParam  )  {
						  case  MK_CONTROL:
							    pT  =  _T(  "c"  );
								break;
						  case  MK_LBUTTON:
							    pT  =  _T(  "l"  );
								break;
						  case  MK_MBUTTON:
							    pT  =  _T(  "m"  );
								break;
						  case  MK_RBUTTON:
							    pT  =  _T(  "r"  );
								break;
						  case  MK_SHIFT:
							    pT  =  _T(  "s"  );
								break;
						  case  MK_XBUTTON1:
							    pT  =  _T(  "x1"  );
								break;
						  case  MK_XBUTTON2:
							    pT  =  _T(  "x2"  );
								break;
				  }
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::WM_LBUTTONDOWN, x %d, y %d. %s"  ),  xPos,  yPos,  pT  );
				  }
				  break;
			case  WM_LBUTTONUP:{
				  long  lParam  =  pMsg->lParam;
				  int  xPos = GET_X_LPARAM(lParam); 
				  int  yPos = GET_Y_LPARAM(lParam); 
				  switch  (  pMsg->wParam  )  {
						  case  MK_CONTROL:
							    pT  =  _T(  "c"  );
								break;
						  case  MK_MBUTTON:
							    pT  =  _T(  "m"  );
								break;
						  case  MK_RBUTTON:
							    pT  =  _T(  "r"  );
								break;
						  case  MK_SHIFT:
							    pT  =  _T(  "s"  );
								break;
						  case  MK_XBUTTON1:
							    pT  =  _T(  "x1"  );
								break;
						  case  MK_XBUTTON2:
							    pT  =  _T(  "x2"  );
								break;
				  }
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::WM_LBUTTONUP, x %d, y %d. %s"  ),  xPos,  yPos,  pT  );
				  }
                  break;
			case  WM_LBUTTONDBLCLK:{
				  long  lParam  =  pMsg->lParam;
				  int  xPos = GET_X_LPARAM(lParam); 
				  int  yPos = GET_Y_LPARAM(lParam); 
				  switch  (  pMsg->wParam  )  {
						  case  MK_CONTROL:
							    pT  =  _T(  "c"  );
								break;
						  case  MK_LBUTTON:
							    pT  =  _T(  "l"  );
								break;
						  case  MK_MBUTTON:
							    pT  =  _T(  "m"  );
								break;
						  case  MK_RBUTTON:
							    pT  =  _T(  "r"  );
								break;
						  case  MK_SHIFT:
							    pT  =  _T(  "s"  );
								break;
						  case  MK_XBUTTON1:
							    pT  =  _T(  "x1"  );
								break;
						  case  MK_XBUTTON2:
							    pT  =  _T(  "x2"  );
								break;
				  }
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::WM_LBUTTONDBLCLK, x %d, y %d. %s"  ),  xPos,  yPos,  pT  );
				  }
				  break;
			case  WM_RBUTTONDOWN:{
				  long  lParam  =  pMsg->lParam;
				  int  xPos = GET_X_LPARAM(lParam); 
				  int  yPos = GET_Y_LPARAM(lParam); 
				  switch  (  pMsg->wParam  )  {
						  case  MK_CONTROL:
							    pT  =  _T(  "c"  );
								break;
						  case  MK_LBUTTON:
							    pT  =  _T(  "l"  );
								break;
						  case  MK_MBUTTON:
							    pT  =  _T(  "m"  );
								break;
						  case  MK_RBUTTON:
							    pT  =  _T(  "r"  );
								break;
						  case  MK_SHIFT:
							    pT  =  _T(  "s"  );
								break;
						  case  MK_XBUTTON1:
							    pT  =  _T(  "x1"  );
								break;
						  case  MK_XBUTTON2:
							    pT  =  _T(  "x2"  );
								break;
				  }
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::WM_RBUTTONDOWN, x %d, y %d. %s"  ),  xPos,  yPos,  pT  );
				  }
				  break;
			case  WM_RBUTTONUP:{
				  long  lParam  =  pMsg->lParam;
				  int  xPos = GET_X_LPARAM(lParam); 
				  int  yPos = GET_Y_LPARAM(lParam); 
				  switch  (  pMsg->wParam  )  {
						  case  MK_CONTROL:
							    pT  =  _T(  "c"  );
								break;
						  case  MK_LBUTTON:
							    pT  =  _T(  "l"  );
								break;
						  case  MK_MBUTTON:
							    pT  =  _T(  "m"  );
								break;
						  case  MK_RBUTTON:
							    pT  =  _T(  "r"  );
								break;
						  case  MK_XBUTTON1:
							    pT  =  _T(  "x1"  );
								break;
						  case  MK_XBUTTON2:
							    pT  =  _T(  "x2"  );
								break;
				  }
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::WM_RBUTTONUP, x %d, y %d. %s"  ),  xPos,  yPos,  pT  );
				  }
				  break;
			case  WM_RBUTTONDBLCLK:{
				  long  lParam  =  pMsg->lParam;
				  int  xPos = GET_X_LPARAM(lParam); 
				  int  yPos = GET_Y_LPARAM(lParam); 
				  switch  (  pMsg->wParam  )  {
						  case  MK_CONTROL:
							    pT  =  _T(  "c"  );
								break;
						  case  MK_LBUTTON:
							    pT  =  _T(  "l"  );
								break;
						  case  MK_MBUTTON:
							    pT  =  _T(  "m"  );
								break;
						  case  MK_RBUTTON:
							    pT  =  _T(  "r"  );
								break;
						  case  MK_SHIFT:
							    pT  =  _T(  "s"  );
								break;
						  case  MK_XBUTTON1:
							    pT  =  _T(  "x1"  );
								break;
						  case  MK_XBUTTON2:
							    pT  =  _T(  "x2"  );
								break;
				  }
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::WM_RBUTTONDBLCLK, x %d, y %d. %s"  ),  xPos,  yPos,  pT  );
				  }
				  break;
			case  WM_MBUTTONDOWN:{
				  long  lParam  =  pMsg->lParam;
				  int  xPos = GET_X_LPARAM(lParam); 
				  int  yPos = GET_Y_LPARAM(lParam); 
				  switch  (  pMsg->wParam  )  {
						  case  MK_CONTROL:
							    pT  =  _T(  "c"  );
								break;
						  case  MK_LBUTTON:
							    pT  =  _T(  "l"  );
								break;
						  case  MK_MBUTTON:
							    pT  =  _T(  "m"  );
								break;
						  case  MK_RBUTTON:
							    pT  =  _T(  "r"  );
								break;
						  case  MK_SHIFT:
							    pT  =  _T(  "s"  );
								break;
						  case  MK_XBUTTON1:
							    pT  =  _T(  "x1"  );
								break;
						  case  MK_XBUTTON2:
							    pT  =  _T(  "x2"  );
								break;
				  }
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::WM_MBUTTONDOWN, x %d, y %d. %s"  ),  xPos,  yPos,  pT  );
				  }
				  break;
			case  WM_MBUTTONUP:{
				  long  lParam  =  pMsg->lParam;
				  int  xPos = GET_X_LPARAM(lParam); 
				  int  yPos = GET_Y_LPARAM(lParam); 
				  switch  (  pMsg->wParam  )  {
						  case  MK_CONTROL:
							    pT  =  _T(  "c"  );
								break;
						  case  MK_LBUTTON:
							    pT  =  _T(  "l"  );
								break;
						  case  MK_MBUTTON:
							    pT  =  _T(  "m"  );
								break;
						  case  MK_RBUTTON:
							    pT  =  _T(  "r"  );
								break;
						  case  MK_SHIFT:
							    pT  =  _T(  "s"  );
								break;
						  case  MK_XBUTTON1:
							    pT  =  _T(  "x1"  );
								break;
						  case  MK_XBUTTON2:
							    pT  =  _T(  "x2"  );
								break;
				  }
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::WM_MBUTTONUP, x %d, y %d. %s"  ),  xPos,  yPos,  pT  );
				  }
				  break;
			case  WM_MBUTTONDBLCLK:{
				  long  lParam  =  pMsg->lParam;
				  int  xPos = GET_X_LPARAM(lParam); 
				  int  yPos = GET_Y_LPARAM(lParam); 
				  switch  (  pMsg->wParam  )  {
						  case  MK_CONTROL:
							    pT  =  _T(  "c"  );
								break;
						  case  MK_LBUTTON:
							    pT  =  _T(  "l"  );
								break;
						  case  MK_MBUTTON:
							    pT  =  _T(  "m"  );
								break;
						  case  MK_RBUTTON:
							    pT  =  _T(  "r"  );
								break;
						  case  MK_SHIFT:
							    pT  =  _T(  "s"  );
								break;
						  case  MK_XBUTTON1:
							    pT  =  _T(  "x1"  );
								break;
						  case  MK_XBUTTON2:
							    pT  =  _T(  "x2"  );
								break;
				  }
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::WM_MBUTTONDBLCLK, x %d, y %d. %s"  ),  xPos,  yPos,  pT  );
				  }
				  break;
			default:
				break;
		}
		return  0;
}
#endif







void CDlgTalk::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	// TODO: Add your message handler code here
	#ifdef  __DEBUG__
			//  traceLog(  _T(  "dlgTalk: OnMove"  )  );
	#endif
	
	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;

	if  (  m_var.hWnd_instantAssistant  )  {
		closeInstantAssistant(  this->m_hWnd  );
	}

	 //  2011/10/02
	 setMsgToolPos(  m_hWnd  );
	//  
	setRemotePtzPos(  m_hWnd  );
	//
	setSubtitlesPos_talk(  m_hWnd  );

	 //
	 setOfflineResPos_talk(  m_hWnd  );

errLabel:
	 return;
}

HBRUSH CDlgTalk::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;

	MC_VAR_isCli		*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;


	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;


	DLG_TALK_var  *  pMgrVar  =  &m_var;
	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
		if  (  !pShadow  )  goto  errLabel;
		pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pShadow->hMgr,  _T(  "dlgTalk::OnCtlColor"  )  );
		if  (  !pMgrVar  )  goto  errLabel;
	}

#ifdef  __DEBUG__
		if  (  nCtlColor  ==  CTLCOLOR_DLG  )  {
			int  i;
			i  =  8;
		}
#endif


	//  2011/03/12
	if  (  nCtlColor  ==  CTLCOLOR_STATIC  )  {
		int	idc  =  pWnd->GetDlgCtrlID(  );
		//
		//  2014/11/18
		if  (  idc  ==  IDC_STATIC_peerDesc  )  {
			return  hbr;
		}
		//
		if  (  idc  ==  IDC_STATIC_dlgDesc  )  {

			pDC->SetBkMode(  TRANSPARENT  );

			if  (  pMgrVar->av.taskInfo.bTaskExists  )  {
				QY_SHARED_OBJ		*	pSharedObj	=	getSharedObjByIndex( pProcInfo,  pMgrVar->av.iIndex_sharedObj_localAv  );
				if  (  pSharedObj  &&  pSharedObj->iIndex_curUsr  !=  pMgrVar->av.iIndex_usr_localAv  )  return  this->m_brush_hangingUp_dlgDesc;
				return  this->m_brush_av_dlgDesc;
				}
			else  {
				  switch  (  pMgrVar->guiData.av.iStatus  )  {
						  case  CONST_imTaskStatus_resp:  
						  case  CONST_imTaskStatus_applyToRecv:
							    return  this->m_brush_applyToRecv_dlgDesc;
							    break;
						  default:
								  break;
				  }
			}

			return  this->m_brush_dlgDesc;
		}
	}

	//  2013/02/23
#if  0
	switch  (  m_var.m_layout.usLayoutType_cur  )  {
			case  CONST_usLayoutType_conference:
			case  CONST_usLayoutType_training:
			case  CONST_usLayoutType_videoOnly:
			case  CONST_usLayoutType_resourceOnly:
				  if  (  nCtlColor  ==  CTLCOLOR_STATIC  )  {
					  pDC->SetBkColor(  TRANSPARENT  );
					  pDC->SetTextColor(  RGB(  255,  255,  255  )  );
					  return  this->m_brush_fullScreen_dlg;				
				  }
				  //
				  return  this->m_brush_fullScreen_dlg;
				  break;
			default:
					break;
	}
#endif


	// TODO:  Change any attributes of the DC here
	if  (  pMgrVar->av.taskInfo.bTaskExists  )  {
		QY_SHARED_OBJ		*	pSharedObj	=	getSharedObjByIndex( pProcInfo,  pMgrVar->av.iIndex_sharedObj_localAv  );
		if  (  pSharedObj  &&  pSharedObj->iIndex_curUsr  !=  pMgrVar->av.iIndex_usr_localAv  )  {
			int	idc  =  pWnd->GetDlgCtrlID(  );
				
			if  (  nCtlColor  ==  CTLCOLOR_DLG  )  return  this->m_brush_hangingUp_dlg;

			if  (  nCtlColor  ==  CTLCOLOR_STATIC  )  {
				pDC->SetBkMode(TRANSPARENT);
				return  this->m_brush_hangingUp_dlg;
			}
		}
	}

	//  2013/03/01
	if  (  m_var.m_bFullScreen  )  {
		if  (  nCtlColor  ==  CTLCOLOR_DLG  )  return  this->m_brush_fullScreen_dlg;

		if  (  nCtlColor  ==  CTLCOLOR_STATIC  )  {		
			//pDC->SetBkColor(  TRANSPARENT  );
			pDC->SetBkMode(  TRANSPARENT  );
			pDC->SetTextColor(  RGB(  255,  255,  255  )  );
			return  this->m_brush_fullScreen_dlg;					
		}
		
	}


	//  2014/10/03
	if  (  nCtlColor  ==  CTLCOLOR_STATIC  )  {		
		int	idc  =  pWnd->GetDlgCtrlID(  );
		if  (  idc  ==  IDC_STATIC_meDesc  
			||  idc  ==  IDC_STATIC_bgWall_conf  )  
		{
			return  this->m_brush_meDesc;
		}
	}


	//


errLabel:
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

BOOL CDlgTalk::OnEraseBkgnd(CDC* pDC)
{
	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;

	// TODO: Add your message handler code here and/or call default
	if  (  m_var.iTalkerSubType  ==  CONST_talkerSubtype_onVWall  )  {
		//  CDlgDynBmps  *  pDlgWall  =  (  CDlgDynBmps  *  )CWnd::FromHandle(  m_var.m_hParent  );
		DLG_dynBmps_var  *  pDynBmpsVar  =  (  DLG_dynBmps_var  *  )getDlgDynBmpsVar(  m_var.m_hParent  );
		if  (  pDynBmpsVar  )  {
			if  (  pDynBmpsVar->wallGpsMgr.bMoving  )  {
				#ifdef  __DEBUG__
						traceLog(  _T(  "dlgTalk OnEraseBkgnd: bMoving"  )  );
				#endif
				//
				int  x,  y,  iW,  iH;
#if  0
				x  =  m_var.guiData.peerCapRect.iX;
				y  =  m_var.guiData.peerCapRect.iY;
				iW  =  m_var.guiData.peerCapRect.iW;
				if  (  m_var.av.peerZone.images.head.usCnt  )  {
					iH  =  m_var.av.peerZone.images.mems[0].iY_dst  -  y;
				}
				else  {
					  iH  =  m_var.guiData.peerCapRect.iH;
				}
#endif
				//
				x  =  m_var.av.peerZone.iX;
				y  =  m_var.av.peerZone.iY;
				iW  =  m_var.av.peerZone.iW;
				if  (  m_var.av.peerZone.images.head.usCnt  )  {
					iH  =  m_var.av.peerZone.images.mems[0].iY_dst  -  y;
				}
				else  {
					  iH  =  m_var.av.peerZone.iH;
				}
		
				//
				if  (  iH  >  0  )  {
					PatBlt( pDC->m_hDC, x, y, iW, iH, PATCOPY );
				}
				
				//
				return  TRUE;

				//  return  FALSE;
			}
		}
	}

	if  (  !CDialog::OnEraseBkgnd(pDC)  )  {
		return  FALSE;
	}

	GetDlgItem(  m_var.guiData.iIDC_STATIC_dlgDesc  )->InvalidateRect(  NULL  );
#if  0
	GetDlgItem(  m_var.guiData.iIDC_STATIC_instantStatus  )->InvalidateRect(  NULL  );
	GetDlgItem(  m_var.guiData.iIDC_STATIC_peerDesc  )->InvalidateRect(  NULL  );
	GetDlgItem(  m_var.guiData.iIDC_STATIC_meDesc  )->InvalidateRect(  NULL  );
	GetDlgItem(  m_var.guiData.iIDC_STATIC_otherDesc  )->InvalidateRect(  NULL  );
#endif
	//  2015/02/18
	if  (  IsWindow(  m_var.msgTool.hWnd_msgTool  )  )  
	{
		::InvalidateRect(  ::GetDlgItem(  m_var.msgTool.hWnd_msgTool,  IDC_STATIC_instantStatus  ),  NULL,  TRUE  );
	}


errLabel:

	return  TRUE;
}




void CDlgTalk::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{	
	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;


	// TODO: Add your message handler code here and/or call default
	if  (  m_var.m_bFullScreen  )  {
		 lpMMI->ptMaxSize.x  =  m_var.m_fullScreenRect.right  -  m_var.m_fullScreenRect.left;
		 lpMMI->ptMaxSize.y  =  m_var.m_fullScreenRect.bottom  -  m_var.m_fullScreenRect.top;

		 lpMMI->ptMaxPosition.x  =  m_var.m_fullScreenRect.right  -  m_var.m_fullScreenRect.left;
		 lpMMI->ptMaxPosition.y  =  m_var.m_fullScreenRect.bottom  -  m_var.m_fullScreenRect.top;

		 lpMMI->ptMaxTrackSize.x  =  m_var.m_fullScreenRect.right  -  m_var.m_fullScreenRect.left;
		 lpMMI->ptMaxTrackSize.y  =  m_var.m_fullScreenRect.bottom  -  m_var.m_fullScreenRect.top;
	 }

errLabel:


#ifndef  __WINCE__
	 CDialog::OnGetMinMaxInfo(lpMMI);
#endif
}
void CDlgTalk::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialog::OnWindowPosChanged(lpwndpos);

	// TODO: Add your message handler code here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	#ifdef  __DEBUG__
			//  traceLog(  _T(  "DlgTalk::OnWindowPosChanged"  )  );
	#endif
							// TODO: Add your message handler code here
#if  0
	if  (  m_var.ucbOnGlobalVWall  )  {
		ZONE_objs_info	*	pDlgWallsVar  =  (  ZONE_objs_info  *  )getDlgWallsVar(  pProcInfo->g_hVWall  );
		if  (  pDlgWallsVar  )  {
			if  (  bDlgTalkAbove_wall(  pProcInfo->g_hVWall,  pDlgWallsVar->hBar  )  )  {
				#ifdef  __DEBUG__
						traceLog(  _T(  "DlgTalk::OnWindowPosChanged: to change zorder"  )  );
				#endif

			    ::SetWindowPos(  pDlgWallsVar->hBar,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOSIZE  |  SWP_NOMOVE  |  SWP_NOACTIVATE    );
				::SetWindowPos(  pDlgWallsVar->hBar,  HWND_NOTOPMOST,  0,  0,  0,  0,  SWP_NOSIZE  |  SWP_NOMOVE  |  SWP_NOACTIVATE  );
			}
		}
	}
#endif

}

void CDlgTalk::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;


	// TODO: Add your message handler code here and/or call default
	DLG_scroll_info  &  m_scrollInfo  =  m_var.m_scrollInfo;
	DLG_layout_param  &  m_layoutParam  =  m_var.m_layoutParam;
	DLG_talk_layout  &  m_layoutInfo  =  m_var.m_layout;

	//
	int		nDelta;
	int		m_rect_iW  =  m_scrollInfo.m_rect.right  -  m_scrollInfo.m_rect.left;
	int		nMaxPos  =  m_rect_iW  -  m_scrollInfo.m_nCurWidth;

	switch  (  nSBCode  )  {
			case  SB_LINEDOWN:
				  if  (  m_scrollInfo.m_nScrollPos_h  >=  nMaxPos  )  return;
				  nDelta  =  min(  nMaxPos  /  100,  nMaxPos  -  m_scrollInfo.m_nScrollPos_h  );
				  break;
			case  SB_LINEUP:
				  if  (  m_scrollInfo.m_nScrollPos_h  <=  0  )  return;
				  nDelta  =  -min(  nMaxPos  /  100,  m_scrollInfo.m_nScrollPos_h  );
				  break;
			case  SB_PAGEDOWN:
				  if  (  m_scrollInfo.m_nScrollPos_h  >=  nMaxPos  )  return;
				  nDelta  =  min(  nMaxPos  /  10,  nMaxPos  -  m_scrollInfo.m_nScrollPos_h  );
				  break;
			case  SB_PAGEUP:
				  if  (  m_scrollInfo.m_nScrollPos_h  <=  0  )  return;
				  nDelta  =  -min(  nMaxPos  /  10,  m_scrollInfo.m_nScrollPos_h  );
				  break;
			case  SB_THUMBPOSITION:
				  nDelta  =  (  int  )nPos  -  m_scrollInfo.m_nScrollPos_h;
				  break;
			default:
					return;
	}
	m_scrollInfo.m_nScrollPos_h  +=  nDelta;
	SetScrollPos(  SB_HORZ,  m_scrollInfo.m_nScrollPos_h,  TRUE  );
	ScrollWindow(  -nDelta,  0  );


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	//
	 int				iErr	=	-1;
	 HWND				hDlg	=	m_hWnd;
	 DLG_talk_layout	layout;
	 RECT	rc;
	 ::GetClientRect(  hDlg,  &rc  );
	 if  (  dlgTalk_calculateLayout(  hDlg,  &m_var,  &rc,  &layout  )  )  goto  errLabel;
	 if  (  mySizeAllControls_dlgTalk_tools(  hDlg,  m_var,  &layout,  &rc  )  )  goto  errLabel;
	 if  (  mySizeAllControls_dlgTalk_me_other(  hDlg,  m_var,  &layout,  &rc  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return;
}


void CDlgTalk::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;

	// TODO: Add your message handler code here and/or call default
	DLG_scroll_info  &  m_scrollInfo  =  m_var.m_scrollInfo;
	DLG_layout_param  &  m_layoutParam  =  m_var.m_layoutParam;
	DLG_talk_layout  &  m_layoutInfo  =  m_var.m_layout;
	
	// 
	int		nDelta;
	int		m_rect_iH  =  m_scrollInfo.m_rect.bottom  -  m_scrollInfo.m_rect.top;
	int		nMaxPos  =  m_rect_iH  -  m_scrollInfo.m_nCurHeight;

	switch  (  nSBCode  )  {
			case  SB_LINEDOWN:
				  if  (  m_scrollInfo.m_nScrollPos_v  >=  nMaxPos  )  return;
				  nDelta  =  min(  nMaxPos  /  100,  nMaxPos  -  m_scrollInfo.m_nScrollPos_v  );
				  break;
			case  SB_LINEUP:
				  if  (  m_scrollInfo.m_nScrollPos_v  <=  0  )  return;
				  nDelta  =  -min(  nMaxPos  /  100,  m_scrollInfo.m_nScrollPos_v  );
				  break;
			case  SB_PAGEDOWN:
				  if  (  m_scrollInfo.m_nScrollPos_v  >=  nMaxPos  )  return;
				  nDelta  =  min(  nMaxPos  /  10,  nMaxPos  -  m_scrollInfo.m_nScrollPos_v  );
				  break;
			case  SB_PAGEUP:
				  if  (  m_scrollInfo.m_nScrollPos_v  <=  0  )  return;
				  nDelta  =  -min(  nMaxPos  /  10,  m_scrollInfo.m_nScrollPos_v  );
				  break;
			case  SB_THUMBPOSITION:
				  nDelta  =  (  int  )nPos  -  m_scrollInfo.m_nScrollPos_v;
				  break;
			default:
					return;
	}
	m_scrollInfo.m_nScrollPos_v  +=  nDelta;
	SetScrollPos(  SB_VERT,  m_scrollInfo.m_nScrollPos_v,  TRUE  );
	ScrollWindow(  0,  -nDelta  );



	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);

	//
	 int				iErr	=	-1;
	 HWND				hDlg	=	m_hWnd;
	 DLG_talk_layout	layout;
	 RECT	rc;
	 ::GetClientRect(  hDlg,  &rc  );
	 if  (  dlgTalk_calculateLayout(  hDlg,  &m_var,  &rc,  &layout  )  )  goto  errLabel;
	 if  (  mySizeAllControls_dlgTalk_tools(  hDlg,  m_var,  &layout,  &rc  )  )  goto  errLabel;
	 if  (  mySizeAllControls_dlgTalk_me_other(  hDlg,  m_var,  &layout,  &rc  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return;
}





void CDlgTalk::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	DLG_TALK_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_TALK_var  &  m_var  =  *pm_var;


	// TODO: Add your message handler code here and/or call default
	if  (  nIDCtl  ==  m_var.av.idc_bgWall_conf  )  {
		MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
		if  (  !pProcInfo  )  return;
		FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
		if  (  !pFuncs  )  return;
	
		
		HDC  hDc  =  NULL;	
		hDc  =  lpDrawItemStruct->hDC;

		//
		dlgTalk_drawItem_bgWall(  m_hWnd,  &m_var,  hDc  );		
	
		return;
	}

errLabel:

	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}





void CDlgTalk::OnEnChangeEditfilter()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.


	// TODO:  Add your control notification handler code here
	//
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	TCHAR  tBuf[128]  =  _T(  ""  );
	DLG_TALK_var  *  pm_var  =  get_pm_var(  );
	if  (  !pm_var  )  return;
	

	GetDlgItemText(  IDC_EDIT_filter,  tBuf,  mycountof(  tBuf  )  );
	tTrim(  tBuf  );
	//
	dlgTalk_loadGrpMems(  m_hWnd,  pm_var,  tBuf  );


}


//
void CDlgTalk::OnNMClicktalkerlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	//
	DLG_TALK_var  *  pCurVar  =  get_pm_var(  );
	if  (  !pCurVar  )  return;
	DLG_TALK_var  &  m_var  =  *pCurVar;

	
	//
	LPNMITEMACTIVATE pNMLV  =  pNMItemActivate;

	int  iSel  =  -1;

	//
	if  (  (  pNMLV->iItem  >= 0  )  )  {
		iSel  =  pNMLV->iItem;
	}

	//
	m_var.talkerList.iSelectItem  =  iSel;


	//
	//
	if  (  iSel  >=  0  &&  iSel  <  pCurVar->av.videoConferenceStatus.usCnt  )  {
		pCurVar->confMgr_talkerListInfo.idInfo_sel.ui64Id  =  pCurVar->av.videoConferenceStatus.mems[iSel].avStream.idInfo.ui64Id;
		}
	else  {
		  pCurVar->confMgr_talkerListInfo.idInfo_sel.ui64Id  =  0;		
	}


	//
	bRefreshBtns_talkerList(  );
	
	//
	*pResult = 0;
}




//
void CDlgTalk::OnLvnItemchangedtalkerlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	//
	DLG_TALK_var  *  pCurVar  =  get_pm_var(  );
	if  (  !pCurVar  )  return;
	DLG_TALK_var  &  m_var  =  *pCurVar;

	//
	int  iSel  =  -1;

	//
	CListCtrl  *  pListCtrl  =  (  CListCtrl  *  )GetDlgItem(  m_var.guiData.iIDC_talkerList  );		
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if  (  pos  ==  NULL  )   {
		TRACE0("No items were selected!\n");
		iSel  =  -1;
		}
	else  {			     
		  int  nItem  =  pListCtrl->GetNextSelectedItem(pos);
		  iSel    =  nItem;
	}

	//
	m_var.talkerList.iSelectItem  =  iSel;

	//
	if  (  iSel  >=  0  &&  iSel  <  pCurVar->av.videoConferenceStatus.usCnt  )  {
		pCurVar->confMgr_talkerListInfo.idInfo_sel.ui64Id  =  pCurVar->av.videoConferenceStatus.mems[iSel].avStream.idInfo.ui64Id;
		}
	else  {
		  pCurVar->confMgr_talkerListInfo.idInfo_sel.ui64Id  =  0;		
	}

	//
	bRefreshBtns_talkerList(  );


	// TODO: Add your control notification handler code here
	*pResult = 0;
}


//
void CDlgTalk::OnBnClickedButtonmicoff()
{
	// TODO: Add your control notification handler code here
	//
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	//
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	//
	DLG_TALK_var  *  pCurVar  =  get_pm_var(  );
	DLG_TALK_var  *  pMgrVar  =  pCurVar;
	HWND  hMgr  =  m_hWnd;

	//
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
		hMgr  =  pTalkerShadow->hMgr;
		pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		if  (  !pMgrVar  )  goto  errLabel;
	}
	//
	if  (  !pCurVar->confMgr_talkerListInfo.idInfo_sel.ui64Id  )  goto  errLabel;
	//
	QY_MESSENGER_ID  idInfo_sel;
	idInfo_sel.ui64Id  =  pCurVar->confMgr_talkerListInfo.idInfo_sel.ui64Id;

	if  (  idInfo_sel.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {

		dlgTalk_requestToSpeak(  hMgr,  FALSE  );

		}
	else  {
		  //
		  if  (  pMgrVar->av.taskInfo.ucbStarter  )  {
			  pProcInfo->confStarter_requestToSpeak(  hMgr,  &idInfo_sel,  NULL,  mynull ,  FALSE  );
			  pProcInfo->sendConfKey(  hMgr,  pMgrVar->addr.idInfo,  _T(  "micoff"  )  );
			  }
		  else  {
			    confMgr_requestToSpeak(  hMgr,  &idInfo_sel,  FALSE  );
			  
		  }

		  //	
		  confMgr_permitToSpeak(  hMgr,  &idInfo_sel,  FALSE  );

	}

errLabel:
	return;
}



void CDlgTalk::OnNMClickListmembers(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	//
	DLG_TALK_var  *  pCurVar  =  get_pm_var(  );
	if  (  !pCurVar  )  return;
	DLG_TALK_var  &  m_var  =  *pCurVar;

	
	//
	LPNMITEMACTIVATE pNMLV  =  pNMItemActivate;

	int  iSel  =  -1;

	//
	if  (  (  pNMLV->iItem  >= 0  )  )  {
		iSel  =  pNMLV->iItem;
	}

	//
	m_var.listMembers.iSelectItem  =  iSel;




	//
	bRefreshBtns_listMembers(  );
	



	*pResult = 0;
}


//
void CDlgTalk::OnLvnItemchangedListmembers(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	// TODO: Add your control notification handler code here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
			
		//
		CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
		HWND  hMgr  =  NULL;
		//
		DLG_TALK_var  *  pCurVar  =  get_pm_var(  );
		//
		hMgr  =  m_hWnd;
		DLG_TALK_var  *  pMgrVar  =  pCurVar;
		if  (  !pMgrVar  )  goto  errLabel;
		if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
			TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
			if  (  !pShadow  )  goto  errLabel;
			hMgr  =  pShadow->hMgr;
			pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  pShadow->hMgr  );
			if  (  !pMgrVar  )  goto  errLabel;
		}
		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;

		if  (  !pMgrVar->av.taskInfo.bTaskExists  )  goto  errLabel;
		if  (  !pMgrVar->av.taskInfo.ucbConfCtrl  )  goto  errLabel;
		if  (  !pMgrVar->av.taskInfo.ucbStarter
			&&  !pShadowMgr->av.ucbMeConfMgr  )
		{
			goto  errLabel;
		}

		//
		DLG_TALK_var  &m_var  =  *pCurVar;

		
		//
	int  iSel  =  -1;

	//
	CListCtrl  *  pListCtrl  =  (  CListCtrl  *  )GetDlgItem(  m_var.guiData.iIDC_talkerList  );		
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if  (  pos  ==  NULL  )   {
		TRACE0("No items were selected!\n");
		iSel  =  -1;
		}
	else  {			     
		  int  nItem  =  pListCtrl->GetNextSelectedItem(pos);
		  iSel    =  nItem;
	}

	//
	m_var.listMembers.iSelectItem  =  iSel;




		//
		bRefreshBtns_listMembers(  );
	

errLabel:


	//
	*pResult = 0;
}



//
void CDlgTalk::OnBnClickedButtonpermittospeak()
{
	// TODO: Add your control notification handler code here
	//
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	//
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	//
	DLG_TALK_var  *  pCurVar  =  get_pm_var(  );
	DLG_TALK_var  *  pMgrVar  =  pCurVar;
	HWND  hMgr  =  m_hWnd;

	//
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
		hMgr  =  pTalkerShadow->hMgr;
		pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		if  (  !pMgrVar  )  goto  errLabel;
	}
	//
	if  (  !pCurVar->confMgr_grpMemListInfo.idInfo_sel.ui64Id  )  goto  errLabel;
	//
	QY_MESSENGER_ID  idInfo_sel;
	idInfo_sel.ui64Id  =  pCurVar->confMgr_grpMemListInfo.idInfo_sel.ui64Id;

	if  (  idInfo_sel.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {

		if  (  pMgrVar->av.taskInfo.ucbStarter  )  {
			pProcInfo->confStarter_requestToSpeak(  hMgr,  &idInfo_sel,  NULL,  NULL, TRUE  );
			}
		else  {
			  //
			confOthers_requestToSpeak(  hMgr,  pMgrVar->av.iIndex_sharedObj_localAv,  mynull,  TRUE  );

		}

		}
	else  {
		  //	
		  confMgr_permitToSpeak(  hMgr,  &idInfo_sel,  TRUE  );
	}

errLabel:
	return;
}



void CDlgTalk::OnBnClickedButtonnospeaking()
{
	// TODO: Add your control notification handler code here
	//
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	//
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	//
	DLG_TALK_var  *  pCurVar  =  get_pm_var(  );
	DLG_TALK_var  *  pMgrVar  =  pCurVar;
	HWND  hMgr  =  m_hWnd;

	//
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
		hMgr  =  pTalkerShadow->hMgr;
		pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		if  (  !pMgrVar  )  goto  errLabel;
	}
	//
	if  (  !pCurVar->confMgr_grpMemListInfo.idInfo_sel.ui64Id  )  goto  errLabel;
	//
	QY_MESSENGER_ID  idInfo_sel;
	idInfo_sel.ui64Id  =  pCurVar->confMgr_grpMemListInfo.idInfo_sel.ui64Id;

	if  (  idInfo_sel.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {

#if  0
		if  (  pMgrVar->av.taskInfo.ucbStarter  )  {
			pFuncs->pf_confStarter_requestToSpeak(  hMgr,  &idInfo_sel,  FALSE  );
			}
		else  {
			  //
			  confOthers_requestToSpeak(  hMgr,  FALSE  );

		}
#endif
		//
		dlgTalk_requestToSpeak(  hMgr,  FALSE  );

		}
	else  {
		  //	
		  confMgr_permitToSpeak(  hMgr,  &idInfo_sel,  FALSE  );
	}

errLabel:
	return;
}





void CDlgTalk::OnBnClickedButtonsharescreen()
{
	// TODO: Add your control notification handler code here
	//
	BOOL  bRemoteAssist  =  TRUE;
	//
	dlgTalk_OnCmd_shareScreen(  m_hWnd,  bRemoteAssist  );

}



//
int  get_idInfo_peer_yz(  DLG_TALK_var  *  pMgrVar,  QY_MESSENGER_ID  *  pIdInfo_peer  )
{
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;
	
	if  (  !pMgrVar  )  return  -1;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  -1;
	//
	if  (  !pMgrVar->av.taskInfo.bTaskExists  )  return  -1;
	if  (  pMgrVar->av.taskInfo.ucbStarter  )  return  -1;

	//
#if  0
	INFO_consult_yz  *  pInfo  =  &pMgrVar->av.taskInfo.info_consult_yz;

	//
	int  i;
	for  (  i  =  0;  i  <  mycountof(  pInfo->mems  );  i  ++  )  {
		 //
		 if  (  !pInfo->mems[i].idInfo.ui64Id  )  continue;
		 if  (  pInfo->mems[i].idInfo.ui64Id  ==  pMgrVar->av.taskInfo.idInfo_starter.ui64Id  )  continue;
		 if  (  pInfo->mems[i].idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  continue;
		 break;
	}
	if  (  i  ==  mycountof(  pInfo->mems  )  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "no idInfo_peer"  )  );
		#endif
		goto  errLabel;
	}
#endif
	//
	QY_MESSENGER_ID  idInfo_peer;
	idInfo_peer.ui64Id  =  0;//pInfo->mems[i].idInfo.ui64Id;

	//
	if  (  pIdInfo_peer  )  *pIdInfo_peer  =  idInfo_peer;

	iErr  =  0;
errLabel:
	return  iErr;

}

//
BOOL  bStarted_remoteAssist(  TALKER_shadow_mgr  *  pShadowMgr,  QY_MESSENGER_ID  *  pIdInfo  )  
{
	BOOL  bStarted  =  FALSE;
	int  i;
	
	QY_MESSENGER_ID   idInfo_peer;
	idInfo_peer.ui64Id  =  pIdInfo->ui64Id;

	//
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->resourcesInfo.info_recv.screenTasks  );  i  ++  )  {
		if  (  pShadowMgr->resourcesInfo.info_recv.screenTasks[i].idInfo_sender.ui64Id  ==  idInfo_peer.ui64Id  )  {
			bStarted  =  TRUE;
			break;
		}
	}

	return  bStarted;
}


//
__declspec(  dllexport  )  int  dlgTalk_OnCmd_controlDesktop(  HWND  hCurTalk  )
{
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;

	//
	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
	DLG_TALK_var	*	pCurVar		=	NULL;

	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	HWND  hMgr  =  NULL;
	DLG_TALK_var  *  pMgrVar  =  NULL;

	//
	pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_cur.getVar(  hCurTalk  );
	if  (  !pCurVar  )  return  -1;

	//
	hMgr  =  hCurTalk;
	pMgrVar  =  pCurVar;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
		if  (  !pShadow  )  goto  errLabel;
		hMgr  =  pShadow->hMgr;
		pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		if  (  !pMgrVar  )  goto  errLabel;
	}
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	//
	TCHAR  tBuf[128]  =  _T(  ""  );

	//
	if  (  !pMgrVar->av.taskInfo.bTaskExists  )  goto  errLabel;
	if  (  pMgrVar->av.taskInfo.usConfType  !=  CONST_usConfType_consult  )  goto  errLabel;
	if  (  pMgrVar->av.taskInfo.ucbStarter  )  goto  errLabel;

	QY_MESSENGER_ID  idInfo_peer;
	if  (  get_idInfo_peer_yz(  pMgrVar,  &idInfo_peer  )  )  {
		showInfo_open0(  0,  0,  _T(  "dlgTalk_OnCmd_controlDesktop failed, get_idInfo_peer_yz failed"  )  );
		goto  errLabel;
	}

	//
	#ifdef  __DEBUG__
			traceLog(  _T(  "idInfo-peer is %I64u"  ),  idInfo_peer.ui64Id  );
	#endif

	int  i;
	BOOL  bStarted  =  FALSE;
	//
	bStarted  =  bStarted_remoteAssist(  pShadowMgr,  &idInfo_peer  );

	//
	requestToControlDesktop_yz(  hMgr,  &idInfo_peer,  !bStarted  );

	
	//
	iErr  =  0;


errLabel:
	return  iErr;

}




//
void CDlgTalk::OnBnClickedButtoncontroldesktop()
{
	// TODO: Add your control notification handler code here
	//
	HWND  hCurTalk  =  m_hWnd;


	//
	dlgTalk_OnCmd_controlDesktop(  hCurTalk  );


	return;
}


//
void CDlgTalk::OnLButtonDblClk(UINT nFlags, CPoint pointParam)
{
	// TODO: Add your message handler code here and/or call default
#ifdef  __DEBUG__
	traceLog(  _T(  "dlgTalk::DblClk"  )  );
#endif
	
	// TODO: 
	int						iErr				=		-1;
	QY_MC				*	pQyMc				=		QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo			=		QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	

	unsigned  short			usCnt_monPics_row	=		1;
	unsigned  short			usCnt_monPics_col	=		1;
	unsigned  int			uiInitW				=		640;
	unsigned  int			uiInitH				=		480;
	BOOL					bScrollBarEnabled	=		FALSE;	//  TRUE;
	BOOL					bVideoConference	=		FALSE;
	BOOL					bRemoteAssist		=		FALSE;

	BOOL					bPeerImage			=		FALSE;
	BOOL					bMeImage			=		FALSE;
	BOOL					bOtherImage			=		FALSE;
	BOOL					bBgWallImage		=		FALSE;	//  2014/10/11

	int						i;
	CAP_IMAGES			*	pImages				=		NULL;	//  &m_var.av.peerImages;
	CAP_IMAGE			*	pImg;

	//
	HWND  hCurTalk  =  m_hWnd;
	DLG_TALK_var  *  pCurVar  =  get_pm_var(  );
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;

			//
		HWND  hMgr  =  hCurTalk;
		DLG_TALK_var  *  pMgrVar  =  pCurVar;
		if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
			TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
			hMgr  =  pShadow->hMgr;
			pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
			if  (  !pMgrVar  )  goto  errLabel;
		}
		//
		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
		if  (  !pShadowMgr  )  goto  errLabel;



	//  2017/08/24
	dlgTalk_processPointerEvent(  m_hWnd,  pointParam.x,  pointParam.y,  nFlags  );

	//
	if  (  pShadowMgr->resourcesInfo.info_recv.bExists_remoteAssist  )  return;

	//
	::PostMessage(  hCurTalk,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );

	//  2011/03/26
	if  (  pQyMc->cfg.ucbNotSupported_dblClk  )  return;



	iErr  =  0;

errLabel:
	if  (  iErr  )  {

	}

	CDialog::OnLButtonDblClk(nFlags, pointParam);
}




void CDlgTalk::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
		
	{
	
		DWORD dwPos = GetMessagePos();
	
		long  lParam  =  dwPos;			
		POINT	point;
		point.x = GET_X_LPARAM(lParam); 
		point.y = GET_Y_LPARAM(lParam);


		//
		#ifdef  __DEBUG__
				//traceLog(  _T(  "dlgTalk: mouseMove: x,y %d,%d"  ),  point.x,  point.y  );
				//
						
		#endif

	
		//  ::MapWindowPoints(  m_hWnd,  NULL,  &point,  1  );	
		viewInstantAssistant(  this->m_hWnd,  CONST_qyWndContentType_talker,  point.x,  point.y,  this->m_hWnd,  TRUE  );
	
	}


	//  2017/08/24
	dlgTalk_processPointerEvent(  m_hWnd,  point.x,  point.y,  nFlags  );


	CDialog::OnLButtonDown(nFlags, point);
}


void CDlgTalk::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
		//  2017/08/24
	dlgTalk_processPointerEvent(  m_hWnd,  point.x,  point.y,  nFlags  );

	//
#ifdef  __USE_skin__
	M_myOnLButtonUp(  this,  nFlags,  point,  (&this->m_skinProc)  );
#else

	//
	CDialog::OnLButtonUp(nFlags, point);
#endif
}


void CDlgTalk::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
		//  2017/08/24
	dlgTalk_processPointerEvent(  m_hWnd,  point.x,  point.y,  nFlags  );

	CDialog::OnMButtonDblClk(nFlags, point);
}


void CDlgTalk::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
		//  2017/08/24
	dlgTalk_processPointerEvent(  m_hWnd,  point.x,  point.y,  nFlags  );

	CDialog::OnMButtonDown(nFlags, point);
}


void CDlgTalk::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
		//  2017/08/24
	dlgTalk_processPointerEvent(  m_hWnd,  point.x,  point.y,  nFlags  );

	CDialog::OnMButtonUp(nFlags, point);
}




void CDlgTalk::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
		//  2017/08/24
	dlgTalk_processPointerEvent(  m_hWnd,  point.x,  point.y,  nFlags  );

	CDialog::OnRButtonDblClk(nFlags, point);
}


void CDlgTalk::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
		//  2017/08/24
	dlgTalk_processPointerEvent(  m_hWnd,  point.x,  point.y,  nFlags  );

	CDialog::OnRButtonDown(nFlags, point);
}


void CDlgTalk::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
		//  2017/08/24
	dlgTalk_processPointerEvent(  m_hWnd,  point.x,  point.y,  nFlags  );

	CDialog::OnRButtonUp(nFlags, point);
}


void CDlgTalk::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
#if  0
	{
		DWORD dwPos = GetMessagePos();
	
		long  lParam  =  dwPos;			
		POINT	point;
		point.x = GET_X_LPARAM(lParam); 
		point.y = GET_Y_LPARAM(lParam);


		//
		#ifdef  __DEBUG__
				//traceLog(  _T(  "dlgTalk: mouseMove: x,y %d,%d"  ),  point.x,  point.y  );
				//
						
		#endif

	
		//  ::MapWindowPoints(  m_hWnd,  NULL,  &point,  1  );	
		viewInstantAssistant(  this->m_hWnd,  CONST_qyWndContentType_talker,  point.x,  point.y,  this->m_hWnd,  FALSE  );
	
	}
#endif

	//
	dlgTalk_processPointerEvent(  m_hWnd,  point.x,  point.y,  nFlags,  TRUE  );  


	CDialog::OnMouseMove(nFlags, point);
}


BOOL CDlgTalk::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	//
	switch  (  pMsg->message  )  {
			case  WM_KEYDOWN:
			case  WM_KEYUP:
			case  WM_SYSKEYDOWN:
			case  WM_SYSKEYUP:
				  processKeyEvent(  pMsg->wParam,  pMsg->lParam  );
				  break;
			case  WM_CHAR:
			case  WM_SYSCHAR:
				  break;
			case  WM_KILLFOCUS:
				  resetKeyEvent(  );
				  break;
			case  WM_MOUSEMOVE:  {
				  //
				  DWORD dwPos = GetMessagePos();
			
				  long  lParam  =  dwPos;			
				  POINT	point;
				  point.x = GET_X_LPARAM(lParam); 
				  point.y = GET_Y_LPARAM(lParam);
				  
				  //
				  #ifdef  __DEBUG__
						  //traceLog(  _T(  "dlgTalk: mouseMove: x,y %d,%d"  ),  point.x,  point.y  );
						  //
						
				  #endif
				  
				  //
				  if  (  !::IsWindowVisible(  this->m_hWnd  )  )  break;

				  //  ::MapWindowPoints(  m_hWnd,  NULL,  &point,  1  );			
				  viewInstantAssistant(  this->m_hWnd,  CONST_qyWndContentType_talker,  point.x,  point.y,  this->m_hWnd,  FALSE  );
	
				  //
				  }
				  break;
			default:
					break;
	}





	//
	return CDialog::PreTranslateMessage(pMsg);
}


///////////////////////////


//
 //
 //  2014/10/01
//
int  getCapImages_bgWall(  HWND  hCurTalk,  void  *  pCurDLG_TALK_var,  unsigned  int  ucbAutoClip,  int  iX_desc,  int  iY_desc,  int  iW_desc,  int  iH_desc,  BG_wall_layout_cfg  *  pCfg,  BG_wall_layout  *  pConfBgLayout  )
{
	DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )pCurDLG_TALK_var;


	//
	int		iErr	=	-1;
	int  i;	
	CAP_RECT  *  pCapRect;
	CAP_IMAGE  *  pImg;
	int  iX,  iY,  iW,  iH;		
	//
	unsigned  int  iW_i,  iH_i;	
	int  iX_src_i,  iY_src_i;
	int  iX_dst,  iY_dst;					
	unsigned  int  iW_dst,  iH_dst;


	//unsigned  short  usCols_me  =  pConfBgLayout->usCols_me;
	unsigned  short  usRows_bg  =  pCfg->usRows_bg;
	unsigned  short  usCols_bg  =  pCfg->usCols_bg;

	iW  =  pConfBgLayout->iW_bgWallMem;
	iH  =  pConfBgLayout->iH_bgWallMem;

	//
	//if  (  !usCols_me  )  usCols_me  =  1;
	if  (  !usRows_bg  )  usRows_bg  =  1;
	if  (  !usCols_bg  )  usCols_bg  =  1;

	//
	int  iCols  =  usCols_bg;
	int  iRows  =  usRows_bg;

	//
	int  nTotal  =  usRows_bg  *  usCols_bg;
	if  (  nTotal  >  mycountof(  pCurVar->av.bgWall.mems  )  )  nTotal  =  mycountof(  pCurVar->av.bgWall.mems  );
	for  (  i  =  0;  i  <  nTotal;  i  ++  )  {
		 myZONE  *  pZone  =  &pCurVar->av.bgWall.mems[i];
		 //
		 	  int  iRow,  iCol;
			  iRow  =  i  /  iCols;
			  iCol  =  i  %  iCols;

			  //  int  iX,  iY;
			  iX  =  iX_desc  +  (  iCol  *  iW  );
			  iY  =  iY_desc  +  (  iRow  *  iH  );

			  //
			  pZone->iX  =  iX;
			  pZone->iY  =  iY;
			  pZone->iW  =  iW;
			  pZone->iH  =  iH;

			  //  2017/10/03
			  pZone->images.head.bResized  =  TRUE;

	}
	pCurVar->av.bgWall.usCnt  =  nTotal;


	//
#if  0
	//  if  (  iRows  ==  1  )  
	{
		 for  (  i  =  0;  i  <  uiMaxCnt_imgMems;  i  ++  )  {
			  pCapRect  =  &pLocationMems[i].rect;
			  pImg  =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );//  &pImages->mems[i];

			  int  iRow,  iCol;
			  iRow  =  i  /  iCols;
			  iCol  =  i  %  iCols;

			  //  int  iX,  iY;
			  iX  =  iX_desc  +  (  iCol  *  iW  );
			  iY  =  iY_desc  +  (  iRow  *  iH  );

			  //  2014/10/11
#if  10
			  if  (  pCapRect->iX  !=  iX
				  ||  pCapRect->iY  !=  iY
				  ||  pCapRect->iW  !=  iW
				  ||  pCapRect->iH  !=  iH  )
			  {
				  pCapRect->iX  =  iX;
				  pCapRect->iY  =  iY;
				  pCapRect->iW  =  iW;
				  pCapRect->iH  =  iH;
			  }
#endif


			  //
			  if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;
			  
			  //
			  myGetImageInfo_2d(  0,  ucbAutoClip,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  
				  &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
				  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );
			  
			  if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}
		 }
	 }
#endif

	iErr  =  0;

	return  iErr;
}









void CDlgTalk::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CDialog::OnNcPaint() for painting messages

#ifdef  __USE_skin__
	M_myOnNcPaint(  this,  (&m_skinProc)  );
#else
	CDialog::OnNcPaint();
#endif

}


LRESULT CDlgTalk::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default

#ifdef  __USE_skin__
	M_myOnNcHitTest(  this,  point,  (&this->m_skinProc)  );
#else
	return CDialog::OnNcHitTest(point);
#endif

}


void CDlgTalk::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

#ifdef  __USE_skin__
	M_myOnNcLButtonDown(  this,  nHitTest, point,(&this->m_skinProc  )  );
#else
	CDialog::OnNcLButtonDown(nHitTest, point);
#endif
	
	
}


void CDlgTalk::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages


	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
 
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
 
		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
 
		// 绘制图标
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rc;
		GetClientRect(&rc);
		CImage mImage;
		//
		CString  str;
		QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
		str  =  CString(  pQyMc->cfg.installDir  )  +  _T(  "resource\\"  )  +  _T(  "talker_bg.bmp"  );
		//
		if(mImage.Load(str) == S_OK)
		{
			dc.SetStretchBltMode(COLORONCOLOR);
			//这里让图片绘制区域和窗口大小一致
			mImage.Draw(dc.m_hDC, CRect(0,0,rc.Width(),rc.Height()));
		}
	}


}
