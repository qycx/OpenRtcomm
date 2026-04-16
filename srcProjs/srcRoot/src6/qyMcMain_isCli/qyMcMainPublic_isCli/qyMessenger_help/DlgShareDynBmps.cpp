// DlgSharedDynBmps.cpp : implementation file
//

#include	"stdafx.h"

#include	<string.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__

	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>

#include	"qmcDmoPublic.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif
#include	"myfourcc.h"

#include	"qyCusResTemp.h"

//  #include	"qyMc.h"
#include	"qyGuiCommProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecordPublic.h"

#include	"myresource.h"

#include	"DlgShareDynBmps.h"

#include	"qyOpenShellCommon.h"
#include	"dlgTalkProc.h"
#include	"qmcCmdProc.h"

//  #include	"DlgProgress.h"
#include	"tmpCeLib.h"

#include	"qyComPortEx.h"
#include	"qmcGpsProc.h"

#include	"myDb.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"dlgRtspUrl.h"
#include	"wallTalkers.h"
#include	"remoteStorageCfg.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliExPublic.h"
#include	"GuiShare.h"

 //  BOOL  bGetWebcamNameByMenuId(  int  iMenuId,  TCHAR  *  name,  unsigned  int  len  );

//
int  getIndex_moniker_byName(  CAP_STUFF	*	pCapStuff,  TCHAR  *  name,  BOOL  bAudio  );


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


 static  QY_DMITEM  CONST_controls_table_screen[]  =
{
	{	1,  (  TCHAR  *  )IDC_STATIC_sharingScreen0,	(  TCHAR  *  )IDC_BUTTON_sharingScreen0,	},
	{	-1,		},
 };

 static  QY_DMITEM  CONST_controls_table_webcam[]  =
{
	{	1,	(  TCHAR  *  )IDC_STATIC_webcam0,		(  TCHAR  *  )IDC_BUTTON_webcam0,	},
	{	2,	(  TCHAR  *  )IDC_STATIC_webcam1,		(  TCHAR  *  )IDC_BUTTON_webcam1,	},
	{	3,	(  TCHAR  *  )IDC_STATIC_webcam2,		(  TCHAR  *  )IDC_BUTTON_webcam2,	},	
	{	-1,		},
};



__declspec(  dllexport  )  int  viewDlgShareDynBmps_isCli(  BOOL  bNeed_shareWebcamInConference  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int								iErr					=	-1;
	QY_MC					*		pQyMc					=	QY_GET_GBUF(  );
	int								iServiceId				=	CONST_qyServiceId_mis;
	QY_SERVICEGUI_INFO		*		pSci					=	getServiceGuiInfo(  pQyMc,  iServiceId  );
	if  (  !pSci  )  return  -1;
	MC_VAR_isCli				*		pProcInfo				=	(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;

	CDlgShareDynBmps		*		pDlg					=	NULL;
	RECT							rect;

	//  2014/09/22
	if  (  !pProcInfo->cfg.ucb__SUPPORT_shareDynBmps__  )  {
		 traceLog(  _T(  "shareDynBmps_isClient not supported"  )  );
		 return  -1;
	}

	//  2014/09/22
#if  0	//  暂时不启用shareDynBmpsEx. 先去做多流和会议中3d的背景。
	__declspec(  dllexport  )  int  viewDlgShareDynBmpsEx_isCli(  BOOL  bNeed_shareWebcamInConference  );

	return  viewDlgShareDynBmpsEx_isCli(  bNeed_shareWebcamInConference  );
#endif

	//
	traceLogA(  "viewSharedWebcams enters"  );
	
	if  (  IsWindow(  pProcInfo->hWnd_shareDynBmps  )  )  {
		MACRO_SetForegroundWindow(  pProcInfo->hWnd_shareDynBmps  );
		iErr  =  0;  goto  errLabel;
	}

	pProcInfo->hWnd_shareDynBmps  =  NULL;

	HWND  hParent  =  ::GetDesktopWindow(  );
	pDlg  =  new  CDlgShareDynBmps(  hParent  );
	if  (  !pDlg  )  goto  errLabel;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;

	//
	BOOL  bShow  =  TRUE;
	//
	if  (  pProcInfo->cfg.policy.ucbDlgShareDynBmps_autopopupandhideOnStartup  )  {	 
		 //
		 if  (  !pProcInfo->ucbAutoHideOnStartup  )  {
			 pProcInfo->ucbAutoHideOnStartup  =  TRUE;
			 //
			 bShow  =  FALSE;
		 }
	 }


	//
	if  (  bShow  )  {
		pDlg->ShowWindow(  SW_SHOW  );
	}

	//  2011/10/15
	//pDlg->m_var.bNeed_shareWebcamInConference  =  bNeed_shareWebcamInConference;

	//
	pProcInfo->hWnd_shareDynBmps  =  pDlg->m_hWnd;

	//
	pDlg  =  NULL;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
	}

	traceLogA(  "viewSharedWebcams leaves, iErr is %d",  iErr  );

	return  iErr;
}



// CDlgShareDynBmps dialog

IMPLEMENT_DYNAMIC(CDlgShareDynBmps, CDialog)

#if  0
CDlgShareDynBmps::CDlgShareDynBmps(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShareDynBmps::IDD, pParent)
#endif
CDlgShareDynBmps::CDlgShareDynBmps(  HWND  hParent /*=NULL*/)
	: CDialog(CDlgShareDynBmps::IDD, CWnd::FromHandle(  hParent  )  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	//
	m_var.m_hParent = hParent;
	m_var.m_nID = CDlgShareDynBmps::IDD;

	//  2013/07/01
	m_var.guiData.iIDC_BUTTON_gps  =  IDC_BUTTON_gps;
	m_var.guiData.iIDC_STATIC_gpsStatus  =  IDC_STATIC_gpsStatus;
	m_var.guiData.iIDC_STATIC_pic0  =  IDC_STATIC_pic0;
	//
	m_var.guiData.iIDC_BUTTON_hide  =  IDC_BUTTON_hide;
	m_var.guiData.iIDCANCAL = IDCANCEL;
	m_var.guiData.iIDC_BUTTON_add  =  IDC_BUTTON_add;
	m_var.guiData.iIDC_BUTTON_procRtsp  =  IDC_BUTTON_procRtsp;
	m_var.guiData.iIDC_BUTTON_del  =  IDC_BUTTON_del;
	m_var.guiData.iIDC_BUTTON_selfTest  =  IDC_BUTTON_selfTest;
	m_var.guiData.iIDC_BUTTON_ptz		=  IDC_BUTTON_ptz;
	m_var.guiData.iIDC_BUTTON_remoteStorageSettings  =  IDC_BUTTON_remoteStorageSettings;
	m_var.guiData.iIDC_CHECK_autoPopupAndHideOnStartup  =  IDC_CHECK_autoPopupAndHideOnStartup;
	//
	m_var.guiData.iIDC_BUTTON_playLocalAudio  =  IDC_BUTTON_playLocalAudio;

	//  2014/04/06
	m_var.ucbAutoClip  =  TRUE;

}

CDlgShareDynBmps::~CDlgShareDynBmps()
{
}


BOOL CDlgShareDynBmps::Create(const RECT& rect)
{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProc		=	QY_GET_procInfo_isCli(  );

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): ÔÚ´´½¨¶Ô»°¿òÖ®Ç°Ó¦ÏÈÉèÖÃ³õÊ¼Êý¾Ý"  );
		return  FALSE;
	}
	*/

	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	
	m_var.pMisCnt  =	getMisCntByName(  pProc,  _T(  ""  )  );
	if  (  !m_var.pMisCnt  )  goto  errLabel;

	//
	if  (  !CDialog::Create(  this->m_var.m_nID, CWnd::FromHandle(  m_var.m_hParent  )  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  CDlgShareDynBmps::bQuitDlg(  )		
{		
	BOOL		bRet	=	FALSE;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	traceLogA(  "CDlgSharedWebcams(  )::bQuitDlg enters"  );

	HWND		tmph  =  m_hWnd;
	if  (  m_var.syncFlgs.bInSequence  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgSharedWebcams::bQuitDlg failed, bLocked already."  )  );
		return  FALSE;
	}
	m_var.syncFlgs.bInSequence  =  TRUE;

	
	//  2012/11/27
	if  (  !pQyMc->bGuiQuit  )  {
		HWND  hParent  =  m_hWnd;
		if  (  ::IsWindowVisible(  hParent  )  )  {
			if  (  myMessageBox(  hParent,  _T(  "Are you sure?"  ),  _T(  "To close shareDynBmps"  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
		}
	}

	//
	if  (  m_var.uiTimerId  )  {
		 KillTimer(  m_var.uiTimerId  );  m_var.uiTimerId  =  0;
	}

	//
	if  (  m_var.uiTimerId_test  )  {
		KillTimer(  m_var.uiTimerId_test  );  m_var.uiTimerId_test  =  0;
	}

	//  2012/04/17
	 if  (  m_var.pComPort_gps  )  {
		 CComPortEx	*	pPort	=	(  CComPortEx  *  )m_var.pComPort_gps;
		 delete  pPort;  m_var.pComPort_gps  =  NULL;
	 }


	//  2009/05/01
	DestroyWindow();				  
		
	bRet  =  TRUE;

errLabel:

	if  (  IsWindow(  tmph  )  )  {
		m_var.syncFlgs.bInSequence  =  FALSE;
	}

	traceLogA(  "CDlgSharedWebcams(  )::bQuitDlg leaves"  );

	return  bRet;
}

 int  CDlgShareDynBmps::sizeAllControls(  )
{
	//CWnd  *  pCtrl;
	//
	//pCtrl  =  GetDlgItem(  m_var.idc  );
	//if  (  !pCtrl  )  goto  errLabel;
	//pCtrl->Invalidate(  TRUE  );
	////  pCtrl->UpdateWindow(  );

	//RECT	rc;
	//pCtrl->GetClientRect(  &rc  );
	 RECT	rc;
	 ::GetClientRect(m_var.hWndIDC, &rc);

	m_var.iW_pic  =  rc.right  -  rc.left;
	m_var.iH_pic  =  rc.bottom  -  rc.top;

	//
	getCapImages(  m_var.ucbAutoClip,  0,  0,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  NULL,  &m_var.images  );

errLabel:
	return  0;
}



  SHARE_dynBmps	*	CDlgShareDynBmps::getShareDynBmpsBySth(  int  uiObjType  )
  {

	  MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	  if  (  !pProcInfo  )  return  NULL;
	  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	  if  (  !pFuncs  )  return  NULL;

	  //  return   (  SHARE_dynBmps  *  )pFuncs->shareDynBmps.pf_dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  uiObjType  );
	  return   (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  uiObjType  );
  }


  int  CDlgShareDynBmps::refreshShareStatus(  unsigned  int  uiObjType  )
  {
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	return  pFuncs->shareDynBmps.pf_dlgShareDynBmps_refreshShareStatus(  g_pQyMc,  m_hWnd,  &m_var,  uiObjType  );
  }


  //
   int  CDlgShareDynBmps::refreshShareCfg_screen(  unsigned  int  uiObjType,  int  index_obj  )
  {
	  int  iErr  =  -1;

	  MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;


	  CHelp_shareDynBmp  help_shareDynBmpMem;

	  if  (  uiObjType  !=  CONST_objType_screen  )  return  -1;

	  //
	  SHARE_dynBmps  *  pShare  =  this->getShareDynBmpsBySth(  uiObjType  );
	  if  (  !pShare  )  return  -1;

	  //
	  WEBCAM_info  webcamInfo;
	  getWebcamInfo(  uiObjType,  index_obj,  &webcamInfo  );

	  int  index_pShare_mem  =  index_obj  -  1;

	  //
  	 SHARE_dyn_bmp  *  pDynBmpMem  =  help_shareDynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  index_pShare_mem  );
	 if  (  !pDynBmpMem  )  goto  errLabel;

	 TCHAR  tBuf[256];

	 //  pDynBmpMem->name
	 //
	 safeTcsnCpy(  webcamInfo.cusName,  pDynBmpMem->cusName,  mycountof(  pDynBmpMem->cusName  )  );

	 		  //

		  //
		  QY_DMITEM  *  pItem  =  qyGetDmItemByType(  pShare->pTable_ctrls,  index_obj,  sizeof(  QY_DMITEM  )  );
		  if  (  pItem  )  {
			  SetDlgItemText(  (  int  )pItem->des,  pDynBmpMem->name  );
		  }


	 iErr  =  0;
errLabel:

	  return  iErr;

  }
 


  //
  int  CDlgShareDynBmps::refreshShareCfg_webcam(  unsigned  int  uiObjType,  int  index_obj  )
  {
	  int  iErr  =  -1;

	  MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;


	  CHelp_shareDynBmp  help_shareDynBmpMem;

	  if  (  uiObjType  !=  CONST_objType_webcam  )  return  -1;

	  //
	  SHARE_dynBmps  *  pShare  =  this->getShareDynBmpsBySth(  uiObjType  );
	  if  (  !pShare  )  return  -1;

	  //
	  WEBCAM_info  webcamInfo;
	  getWebcamInfo(  uiObjType,  index_obj,  &webcamInfo  );

	  int  index_pShare_mem  =  index_obj  -  1;

	  //
  	 SHARE_dyn_bmp  *  pDynBmpMem  =  help_shareDynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  index_pShare_mem  );
	 if  (  !pDynBmpMem  )  goto  errLabel;

	 TCHAR  tBuf[256];
	 safeTcsnCpy(  webcamInfo.vName,  pDynBmpMem->name,  mycountof(  pDynBmpMem->name  )  );
	 if  (  webcamInfo.aName[0]  )  _sntprintf(  pDynBmpMem->name,  mycountof(  pDynBmpMem->name  ),  _T(  "%s (%s)"  ),  pDynBmpMem->name,  webcamInfo.aName  );
	 //
	 safeTcsnCpy(  webcamInfo.cusName,  pDynBmpMem->cusName,  mycountof(  pDynBmpMem->cusName  )  );

	 //
	 CAP_STUFF  & gcap  =  *(  CAP_STUFF  *  )m_var.pCapStuff1;
	 		  //
		  TCHAR  tName[256];
		  int  i;
		  for  (  i  =  0;  i  <  mycountof(  gcap.rgpmVideoMenu  );  i  ++  )  {			
			   if  (  !gcap.rgpmVideoMenu[i]  )  continue;
			   //
			   pFuncs->moniker.pf_getMonikerProp(  gcap.rgpmVideoMenu[i],  CONST_moniker_FriendlyName,  tName,  mycountof(  tName  )  );
			   //
			   if  (  _tcsicmp(  tName,  webcamInfo.vName  )  )  continue;
			   //
			   break;		     
		  }
		  if  (  i  <=  mycountof(  gcap.rgpmVideoMenu  )  )  {
			  //			  
			  pDynBmpMem->iMenuId  =  ID_MENU_VDEVICE0  +  i;
		  }

		  //
		  QY_DMITEM  *  pItem  =  qyGetDmItemByType(  pShare->pTable_ctrls,  index_obj,  sizeof(  QY_DMITEM  )  );
		  if  (  pItem  )  {
			  SetDlgItemText(  (  int  )pItem->des,  pDynBmpMem->name  );
		  }


	 iErr  =  0;
errLabel:

	  return  iErr;

  }
 


  //
#if 0
   int  CDlgShareDynBmps::iitoShareScreen(  int  index_pShare_mem  )
{
	int					iErr	=	-1;
	SHARE_dynBmps	*	pShare;
	unsigned  int  uiObjType  =  CONST_objType_screen;
	pShare  =  getShareDynBmpsBySth(  CONST_objType_screen  );
	if  (  !pShare  )  return  -1;
	CHelp_shareDynBmp  help_dynBmpMem;
	SHARE_dyn_bmp  *  pDynBmpMem  =  NULL;

	//if  (  index_pShare_mem  <  0  ||  index_pShare_mem  >=  pShare->usCnt  )  return  -1;
	pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  index_pShare_mem  );
	if  (  !pDynBmpMem  )  return  -1;

	//  2012/05/11 在点击启动共享后，就可以不必保持置前状态了
	if  (  m_var.bNeed_shareWebcamInConference  )  {
		m_var.bNeed_shareWebcamInConference  =  FALSE;
	}


	//
	//if  (  pShare->mems[index_pShare_mem].var.ucbLocalVideoOpen  )  
	if  (  pDynBmpMem->var.ucbLocalVideoOpen  )
	{
		closeTaskAv(  uiObjType,  index_pShare_mem  );

		mytime(  &m_var.tLastModifiedTime  );

		this->refreshShareStatus(  CONST_objType_screen  );  
	
		iErr  =  0;  goto  errLabel;
	}

	int  iParam  =  index_pShare_mem;
	toSelectRegion(  m_hWnd,  TRUE,  FALSE,  FALSE,  iParam  );

	int  n;
	n  =  getnItems(  pShare->pTable_ctrls  );
	if  (  n  >  index_pShare_mem  )  {
		CWnd	*	p	=	GetDlgItem(  (  int  )pShare->pTable_ctrls[index_pShare_mem].pData  );
		if  (  p  )  p->EnableWindow(  FALSE  );
	}

	iErr  =  0;
errLabel:

	
	return  iErr;
}
#endif

   //
   int  CDlgShareDynBmps::toShareScreen(  int  index_pShare_mem  )
   {
	   showDlgOpScreen(  m_hWnd,  m_hWnd,  index_pShare_mem  +  1  );

	   //
	   this->refreshShareCfg_screen(  CONST_objType_screen,  index_pShare_mem  +  1  );

	   return  0;
   }


   //
   //
int  dlgShareDynBmps_toShareScreen_func(  HWND  hDlg_shareDynBmps,  int  index_pShare_mem  )
{
	CDlgShareDynBmps  *  pDlg  =  (  CDlgShareDynBmps  *  )CDlgShareDynBmps::FromHandlePermanent(  hDlg_shareDynBmps  );
	if  (  !pDlg  )  return  -1;

	pDlg->toShareScreen_func(  index_pShare_mem  );

	
	return  0;
}


   //   
   int  CDlgShareDynBmps::toShareScreen_func(  int  index_pShare_mem  )
{
	int					iErr	=	-1;
	SHARE_dynBmps	*	pShare;
	unsigned  int  uiObjType  =  CONST_objType_screen;
	pShare  =  getShareDynBmpsBySth(  CONST_objType_screen  );
	if  (  !pShare  )  return  -1;
	CHelp_shareDynBmp  help_dynBmpMem;
	SHARE_dyn_bmp  *  pDynBmpMem  =  NULL;

	//if  (  index_pShare_mem  <  0  ||  index_pShare_mem  >=  pShare->usCnt  )  return  -1;
	pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  index_pShare_mem  );
	if  (  !pDynBmpMem  )  return  -1;

	//  2012/05/11 在点击启动共享后，就可以不必保持置前状态了
#if  0
	if  (  m_var.bNeed_shareWebcamInConference  )  {
		m_var.bNeed_shareWebcamInConference  =  FALSE;
	}
#endif


	//
	//if  (  pShare->mems[index_pShare_mem].var.ucbLocalVideoOpen  )  
	if  (  pDynBmpMem->var.ucbLocalVideoOpen  )
	{
		closeTaskAv(  uiObjType,  index_pShare_mem  );

		mytime(  &m_var.tLastModifiedTime  );

		this->refreshShareStatus(  CONST_objType_screen  );  
	
		iErr  =  0;  goto  errLabel;
	}

	int  iParam  =  index_pShare_mem;
	toSelectRegion1(  m_hWnd,  TRUE,  FALSE,  FALSE,  0,  iParam  );

	int  n;
	n  =  getnItems(  pShare->pTable_ctrls  );
	if  (  n  >  index_pShare_mem  )  {
		CWnd	*	p	=	GetDlgItem(  (  int  )pShare->pTable_ctrls[index_pShare_mem].pData  );
		if  (  p  )  p->EnableWindow(  FALSE  );
	}

	iErr  =  0;
errLabel:

	
	return  iErr;
}




   //
#if  0
int  CDlgShareDynBmps::iitoShareWebcam(  int  index_pShare_mem  )
{
	 int  iErr  =  -1;

	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;

	 //
	 void	*	pCapStuff				=	NULL;

	 //
	 unsigned  int  uiObjType  =  CONST_objType_webcam;

	 CHelp_shareDynBmp  help_shareDynBmpMem;
	 SHARE_dyn_bmp  *  pDynBmpMem  =  help_shareDynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  index_pShare_mem  );
	 if  (  !pDynBmpMem  )  return  -1;
	 
	 if  (  pDynBmpMem->var.ucbLocalVideoOpen  )  {

	 		pFuncs->shareDynBmps.pf_dlgShareDynBmps_closeTaskAv(  m_hWnd,  &m_var,  uiObjType,  index_pShare_mem  );
			return  0;
	 }

	 if  (  !pDynBmpMem->iMenuId  )  goto  errLabel;
	 
	 //
	 pCapStuff  =  pFuncs->pf_CAP_STUFF_new(  );
	if  (  !pCapStuff  )  goto  errLabel;
	pFuncs->moniker.pf_addDevicesToMenu(  pCapStuff,  TRUE,  NULL  );

	 
	 //
	 //  这里要选择音频和视频设备					
	
	 //  2015/10/22	
	 BOOL  bUnresizable  = TRUE; 

	 //
	 int  tmpiRet;
	 //tmpiRet  =  showDlgSelectAvDev(  m_hWnd,  pCapStuff,  pDynBmpMem->iMenuId,  &bUnresizable  );
	 int  index_obj_sel  =  index_pShare_mem  +  1;
	 tmpiRet  =  showDlgOpAvDev(  m_hWnd,  m_hWnd,  pCapStuff,  index_obj_sel,  &bUnresizable  );
	 if  (  tmpiRet  !=  IDOK  )  goto  errLabel;

	 
	 //
	 AV_COMPRESSOR_CFG	*	pAvCompressor  =  NULL;
	 TASK_av_props  avProps;
	 memset(  &avProps,  0,  sizeof(  avProps  )  );

	 //
	 AV_COMPRESSOR_CFG		mediaDeviceCompressor;
	 if  (  bUnresizable  )  {
		 unsigned  int  uiSubCapType  =  CONST_subCapType_unresizable;
		 int  level  =  0;
		 if  (  myGetAvCompressorCfg(  CONST_capType_mediaDevice,  uiSubCapType,  0,  level,  &mediaDeviceCompressor  )  )  goto  errLabel;
		 //
		 pAvCompressor  =  &mediaDeviceCompressor;
		 //
		 avProps.v.ucAvFlg  |=  CONST_avFlg_unresizable;
	 }
	 //

	 //
	 if  (  pFuncs->shareDynBmps.pf_dlgShareDynBmps_toShareDynBmp(  m_hWnd,  &m_var,  CONST_objType_webcam,  index_pShare_mem,  &pCapStuff,  pAvCompressor,  &avProps  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 //
	 if  (  pCapStuff  )  pFuncs->pf_CAP_STUFF_free(  pCapStuff  );
	 
	 return  iErr;
}
#endif

//
int  CDlgShareDynBmps::toShareWebcam(  int objType,  int  index_pShare_mem  )
{
	 int  iErr  =  -1;

	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;

	 
	 //
	 //  这里要选择音频和视频设备					
	
	 //  2015/10/22	
	 BOOL  bUnresizable  = TRUE; 

	 //
	 int  tmpiRet;
	 //tmpiRet  =  showDlgSelectAvDev(  m_hWnd,  pCapStuff,  pDynBmpMem->iMenuId,  &bUnresizable  );
	 int  index_obj_sel  =  index_pShare_mem  +  1;
	 tmpiRet  =  showDlgOpAvDev(  m_hWnd,  m_hWnd,  objType,  index_obj_sel,  &bUnresizable  );

	 //
	 //this->refreshShareCfg_webcam(  CONST_objType_webcam,  index_obj_sel  );
	 this->refreshShareCfg_webcam(objType, index_obj_sel);

	 //	 
	 iErr  =  0;

errLabel:

	 return  iErr;
}


//
BOOL  dlgShareDynBmps_bShared(  HWND  hDlg_shareDynBmps,  unsigned int  uiObjType,  int  index_obj  )
{
	BOOL  bRet  =  FALSE;
	CHelp_shareDynBmp  help_shareDynBmpMem;

	CDlgShareDynBmps  *  pDlg  =  (  CDlgShareDynBmps  *  )CDlgShareDynBmps::FromHandlePermanent(  hDlg_shareDynBmps  );
	if  (  !pDlg  )  goto  errLabel;

	//
	int  index_pShare_mem  =  0;

	//
	switch  (  uiObjType  )  {
			case  CONST_objType_screen:
			case  CONST_objType_webcam:
			case  CONST_objType_ic:
				  index_pShare_mem  =  index_obj  -  1;
				  break;
			default:
					goto  errLabel;
	}

	//
	 SHARE_dyn_bmp  *  pDynBmpMem  =  help_shareDynBmpMem.getMemByIndex(  hDlg_shareDynBmps,  &pDlg->m_var,  uiObjType,  index_pShare_mem  );
	 if  (  !pDynBmpMem  )  goto  errLabel;
	 
	 if  (  !bShared(  pDynBmpMem  )  )  goto  errLabel;


	bRet  =  TRUE;
	
errLabel:
	return  bRet;

}

//
int  dlgShareDynBmps_toShareWebcam_func(  HWND  hDlg_shareDynBmps,  unsigned  int  uiObjType,  int  index_pShare_mem,  void  **  ppCapStuff,  int  iMenuId_v,  BOOL  bUnresizable  )
{
	CDlgShareDynBmps  *  pDlg  =  (  CDlgShareDynBmps  *  )CDlgShareDynBmps::FromHandlePermanent(  hDlg_shareDynBmps  );
	if  (  !pDlg  )  return  -1;

	pDlg->toShareWebcam_func(  uiObjType,  index_pShare_mem,  ppCapStuff,  iMenuId_v,  bUnresizable  );

	
	return  0;
}


//
int  CDlgShareDynBmps::toShareWebcam_func(  int  objType,  int  index_pShare_mem,  void  **  ppCapStuff,   int  iMenuId_v,  BOOL  bUnresizable  )
{
	 int  iErr  =  -1;

	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;

	 
	 //
	 unsigned  int  uiObjType = objType;// CONST_objType_webcam;

	 CHelp_shareDynBmp  help_shareDynBmpMem;
	 SHARE_dyn_bmp  *  pDynBmpMem  =  help_shareDynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  index_pShare_mem  );
	 if  (  !pDynBmpMem  )  return  -1;
	 
	 if  (  pDynBmpMem->var.ucbLocalVideoOpen  )  {

	 		pFuncs->shareDynBmps.pf_dlgShareDynBmps_closeTaskAv(  m_hWnd,  &m_var,  uiObjType,  index_pShare_mem  );
			return  0;
	 }

	 //
	 if  (  iMenuId_v  )  pDynBmpMem->iMenuId  =  iMenuId_v;

	 //
	 if  (  !pDynBmpMem->iMenuId  )  goto  errLabel;
	 
	
	 
	 //
	 //  这里要选择音频和视频设备					
	
	 //  2015/10/22	
	

	 
	 //
	 AV_COMPRESSOR_CFG	*	pAvCompressor  =  NULL;
	 TASK_av_props  avProps;
	 memset(  &avProps,  0,  sizeof(  avProps  )  );

	 //
	 AV_COMPRESSOR_CFG		mediaDeviceCompressor;
	 if  (  bUnresizable  )  {
		 unsigned  int  uiSubCapType  =  CONST_subCapType_unresizable;
		 int  level  =  0;
		 if  (  myGetAvCompressorCfg(  CONST_capType_mediaDevice,  uiSubCapType,  0,  level,  &mediaDeviceCompressor  )  )  goto  errLabel;
		 
		 //
		 if (objType == CONST_objType_ic) {
			 mediaDeviceCompressor.video.common.ucCompressors = CONST_videoCompressors_hwAccl;
			 iFourcc2Str(CONST_fourcc_HEVC, mediaDeviceCompressor.video.common.fourccStr, mycountof(mediaDeviceCompressor.video.common.fourccStr));
		 }

		 //
		 pAvCompressor  =  &mediaDeviceCompressor;
		 //
		 avProps.v.ucAvFlg  |=  CONST_avFlg_unresizable;



	 }
	 //

	 //
	 if  (  pFuncs->shareDynBmps.pf_dlgShareDynBmps_toShareDynBmp(  g_pQyMc,  m_hWnd,  &m_var,  objType,  index_pShare_mem,  ppCapStuff,  pAvCompressor,  &avProps  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 
	 return  iErr;
}





//
int  CDlgShareDynBmps::closeTaskAv(  unsigned  int  uiObjType,  int  index_pShare_mem  )
{
	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;

	 return  pFuncs->shareDynBmps.pf_dlgShareDynBmps_closeTaskAv(  m_hWnd,  &m_var,  uiObjType,  index_pShare_mem  );
}





int  CDlgShareDynBmps::toShareGps(  )
{
	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;

	 return  pFuncs->shareDynBmps.pf_dlgShareDynBmps_toShareGps(  g_pQyMc,  m_hWnd,  &m_var  );
}




int  CDlgShareDynBmps::chkShareGps(  )
{
	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;

	 return  pFuncs->shareDynBmps.pf_dlgShareDynBmps_chkShareGps(  m_hWnd,  &m_var  );
}




int  CDlgShareDynBmps::refreshShareStatus_gps(  )
{
	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;

	 return  pFuncs->shareDynBmps.pf_dlgShareDynBmps_refreshShareStatus_gps(  g_pQyMc,  m_hWnd,  &m_var  );
}





//
//  2016/06/27
int  CDlgShareDynBmps::reloadOnvifList()
{
	int  iRet  =  -1;

	QY_MC		*	pQyMc		=	QY_GET_GBUF();
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	//
	CTX_qm_thread  *  pCtx_thread  =  &pQyMc->gui.ctx_gui_thread;


	//
	TCHAR			tName[64]  =  _T(  ""  );
	TCHAR			tBuf[255]  =  _T(  ""  );
	
	TCHAR		*	p;
	char		*	p1;
	TCHAR		*	pName;
	TCHAR		*	pUrl;

	int				uiCapType	=	CONST_capType_av;
	int				uiSubCapType	=	CONST_subCapType_webcam;


	QY_REG			reg;
	memset(  &reg,  0,  sizeof(  reg  )  );

	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//  _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	getRegRootKey_qmc(  uiCapType,  uiSubCapType,  0,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  _T(  CONST_regKeyName_rtspUrl  )  );


	{
		
		//
		int  tmp_ruleIndex;
		int				index_obj  =  0;
		//
		ShareDynBmps_onvif_rulesInfo  new_rulesInfo  =  {0};

		//
		for  (  index_obj  =  MIN_usIndex_obj_rtspUrl;  index_obj  <=  MAX_usIndex_obj_rtspUrl;  index_obj  ++  )  {
			//
			if  (  new_rulesInfo.usCnt >=  mycountof(  new_rulesInfo.mems  )  )  break;
			//
			_sntprintf(  tName,  mycountof(  tName  ),  _T(  "%d"  ),  index_obj  );
			if  (  qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  tName,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  continue;

			//
			tTrim(  tBuf  );
			if  (  !tBuf[0]  )  continue;
				
			//
			Onvif_rule  tmpRule  =  {0};
			//
			tmpRule.usIndex_obj  = index_obj;
			parseRegVal_webcam_rtspUrl(  tBuf,  &tmpRule  );

			//
			tmp_ruleIndex  =  getOnvifRuleIndex(  &new_rulesInfo,  index_obj  );
			if  (  tmp_ruleIndex  <  0  )  {
				if  (  new_rulesInfo.usCnt  >=  mycountof(  new_rulesInfo.mems  )  )  {
					break;
				}
				//					
				new_rulesInfo.mems[new_rulesInfo.usCnt]  =  tmpRule;	
				new_rulesInfo.usCnt  ++  ;
				}
			else  if  (  !isSame_onvifRule(  &tmpRule,  &new_rulesInfo.mems[tmp_ruleIndex]  )  )  {
					  //						
				      new_rulesInfo.mems[tmp_ruleIndex]  =  tmpRule;			
			}
		
			//
			continue;

		}

		BOOL  bChanged  =  FALSE;


		//
		// 应该是在new_rulesinfo的mems遍历，对每个成员，都看原来的m_var.onvif.rulesInfo有没有同样的index_obj和内容，如果一样，就把该成员的tranNo设成和原来一样。如果不一样，就取一个新的值。
		// 最后如果有不一样的，就把new_rulesinfo赋给m_var.onvif.rulesInfo. 同时更新ts_rulesInfo.
		//
		int  i;
		for  (  i  =  0;  i  <  new_rulesInfo.usCnt;  i  ++  )  {
			 Onvif_rule  *  pRule  =  &new_rulesInfo.mems[i];
			 index_obj  =  pRule->usIndex_obj;
			 //
			 tmp_ruleIndex  =  getOnvifRuleIndex(  &m_var.onvif.rulesInfo,  index_obj  );  
			 if  (  tmp_ruleIndex  <  0  )  {
				 pRule->status.uiTranNo_changeContent  =  pFuncs->isCliHelp.pf_getuiNextTranNo(  0,  0,  0  );
				 bChanged  =  TRUE;
				 //
				 continue;
			 }			 
			 //
			 if  (  isSame_onvifRule(  pRule,  &m_var.onvif.rulesInfo.mems[tmp_ruleIndex]  )  )  {
				 pRule->status.uiTranNo_changeContent  =  m_var.onvif.rulesInfo.mems[tmp_ruleIndex].status.uiTranNo_changeContent;
				 }
			 else  {
				   pRule->status.uiTranNo_changeContent  =  pFuncs->isCliHelp.pf_getuiNextTranNo(  0,  0,  0  );
				   bChanged  =  TRUE;				 
			 }
			 continue;
		}
		//
		if  (  new_rulesInfo.usCnt  !=  m_var.onvif.rulesInfo.usCnt  )  {
			bChanged  =  TRUE;
		}
		//
		if  (  bChanged  )  {
			timestamp_renew(  pCtx_thread,  &new_rulesInfo.ts_rulesInfo,_T("dlgShareDynBmps.reloadOnvifList.l1060"));
			//
			CQySyncObj  syncObj;
					
			//
			if  (  syncMtCnt_wLock_wait(  &m_var.onvif.syncMtCnt_cur_rulesInfo,  _T(  ""  ),  &syncObj,  NULL,  _T(  ""  )  )  )  {
				goto  errLabel;		
			}

			//
			m_var.onvif.rulesInfo  =  new_rulesInfo;
			
			//		
			syncMtCnt_start(  &m_var.onvif.syncMtCnt_cur_rulesInfo,  pFuncs->isCliHelp.pf_getuiNextTranNo  );
		}
	}

	//
	//dlgShareDynBmps_chkOnvifRules(  m_hWnd,  m_var,  &m_var.onvif.rulesInfo,  &m_var.onvif.ipDevsInfo  );


	//
#if  0
	//
	::SendMessage(  m_var.hCtrl_onvifList,  LB_RESETCONTENT,  0,  0  );

	//
	int  i;
	//
	for  (  i  =  0;  i  <  m_var.onvif.rulesInfo.usCnt;  i  ++  )  {
		 Onvif_rule  *  pRule  =  &m_var.onvif.rulesInfo.mems[i];
		 
		 //
		TCHAR  displayBuf[1024];
		_sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%d,%s,%s,%s"  ),  pRule->usIndex_obj,  qyGetDesByType1(  CONST_onvifRuleTypeTable,  pRule->iOnvifRuleType  ),  pRule->cusName,  CQyString(  pRule->url  )  );
		if  (  pRule->status.bDel  )  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s,Del"  ),  displayBuf  );
		if  (  m_var.onvif.selfTest.bSelfTest  )  {
			if  (  pRule->usIndex_obj  ==  m_var.onvif.selfTest.usIndex_obj_selfTest  )  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s,selTest"  ),  displayBuf  );
		}
		//
		//  2014/09/09
		{
				CHelp_shareDynBmp	help_mem;
				SHARE_dyn_bmp  *  pMem  =  help_mem.getMemByIndex_obj(  m_hWnd,  &m_var,  CONST_objType_rtspStream,  pRule->usIndex_obj  );
				if  (  pMem  )  {
					_sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s,Used"  ),  displayBuf  );
					}			
				else  {
					  //  2016/06/25. 删除的操作在这里。
					  if  (  pRule->status.bDel  )  {
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareDynBmp::rtsp index_obj %d will be removed."  ),  (  int  )pRule->usIndex_obj  );
						  //					  					  					  
						  qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  tName  );
						  continue;				  
					  }			
				}
		}
		 //
		 IP_dev  *  pIpDev  =  getIpDevBy_index_obj(  &m_var.onvif.ipDevsInfo,  pRule->usIndex_obj  );
		 if  (  pIpDev  )  {
			 if  (  pIpDev->ucCnt_urls  )  {
				 _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s. ( realUrl %s )"  ),  displayBuf,  CQyString(  pIpDev->urls[0].url  )  );
			 }
		 }
		 //
		 //
		::SendMessage(  m_var.hCtrl_onvifList,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )displayBuf  );    
		if  (  pRule->usIndex_obj  ==  m_var.onvif.usIndex_obj_sel  )  {
			//
			::SendMessage(  m_var.hCtrl_onvifList,  LB_SETCURSEL,  (  WPARAM  )i,  (  LPARAM  )0  );    
		}
		//
		continue;		 
	}
#endif
	//
	displayOnvifList(  );


	iRet  =  0;
errLabel:
	return  iRet;
}



//
int  CDlgShareDynBmps::displayOnvifList(  )
{
	int  iRet  =  -1;

	QY_MC		*	pQyMc		=	QY_GET_GBUF();
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	//
	CTX_qm_thread  *  pCtx_thread  =  &pQyMc->gui.ctx_gui_thread;


	//
	TCHAR			tName[64]  =  _T(  ""  );
	TCHAR			tBuf[255]  =  _T(  ""  );
	
	TCHAR		*	p;
	char		*	p1;
	TCHAR		*	pName;
	TCHAR		*	pUrl;

	int				uiCapType	=	CONST_capType_av;
	int				uiSubCapType	=	CONST_subCapType_webcam;

#if  10
	QY_REG			reg;
	memset(  &reg,  0,  sizeof(  reg  )  );

	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//  _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	getRegRootKey_qmc(  uiCapType,  uiSubCapType,  0,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  _T(  CONST_regKeyName_rtspUrl  )  );
#endif
	//
	::SendMessage(  m_var.hCtrl_onvifList,  LB_RESETCONTENT,  0,  0  );

	

	//
	//  dlgShareDynBmps_chkOnvifRules(  m_hWnd,  m_var,  &m_var.onvif.rulesInfo,  &m_var.onvif.ipDevsInfo  );

	//
	TCHAR  displayBuf[1024];
	int  i;
	int  nPos;

	//
	for  (  i  =  0;  i  <  m_var.onvif.rulesInfo.usCnt;  i  ++  )  {
		 Onvif_rule  *  pRule  =  &m_var.onvif.rulesInfo.mems[i];
		 
		 //	
		 _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s %d: %s,%s,%s,%s:*,%s"  ),  CONST_str_rule,  (  int  )pRule->usIndex_obj,  qyGetDesByType1(  CONST_onvifRuleTypeTable,  pRule->iOnvifRuleType  ),  pRule->cusName,  CQyString(  pRule->url  ),  CQyString(  pRule->usrName  ),  CQyString(  pRule->defToken  )  );
		 if  (  pRule->status.bDel  )  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s,Del"  ),  displayBuf  );
		 if  (  m_var.onvif.selfTest.bSelfTest  )  {			
			 if  (  pRule->usIndex_obj  ==  m_var.onvif.selfTest.usIndex_obj_selfTest  )  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s,selTest"  ),  displayBuf  );		
		 }		
		 //		
		 //  2014/09/09		
		 //
		 IP_dev  *  pIpDev  =  NULL;//getIpDevBy_index_obj(  &m_var.onvif.ipDevsInfo,  pRule->usIndex_obj  );
		 //
		 if  (  pRule->iOnvifRuleType  ==  CONST_onvifRuleType_rtspUrl  )  {
			 int  j;
			 for  (  j  =  0;  j  <  mycountof(  m_var.onvif.ipDevsInfo.mems  );  j  ++  )  {
				  pIpDev  =  &m_var.onvif.ipDevsInfo.mems[j];
				  if  (  !pIpDev->iType  )  continue;
				  if  (  pIpDev->rule.usIndex_obj  !=  pRule->usIndex_obj  )  continue;
				  break;
			 }
			 //
			 if  (  j  <  mycountof(  m_var.onvif.ipDevsInfo.mems  )  )  {
				 //
				 if  (  pIpDev->rule.status.uiTranNo_changeContent  ==  pRule->status.uiTranNo_changeContent  )  {				 
					 _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s rule ok."  ),  displayBuf  );			 
				 }

				 //
				 CHelp_shareDynBmp	help_mem;
				 SHARE_dyn_bmp  *  pMem  =  help_mem.getMemByIndex_obj(  m_hWnd,  &m_var,  CONST_objType_rtspStream,  pRule->usIndex_obj,  pIpDev->usHelp_subIndex  );
				 if  (  pMem  )  {
					_sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s,Used"  ),  displayBuf  );
					}			
				 else  {
					  //  2016/06/25. 删除的操作在这里。
					  if  (  pIpDev->status.toBeStopped  )  {
						  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s,toBeStopped"  ),  displayBuf  );
					  }			
				}		

			 }
		 }
		 //
		 nPos  =  ::SendMessage(  m_var.hCtrl_onvifList,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )displayBuf  );    
		 if  (  pRule->usIndex_obj  ==  m_var.onvif.sel.usIndex_obj_sel  )  {
			//
			::SendMessage(  m_var.hCtrl_onvifList,  LB_SETCURSEL,  (  WPARAM  )nPos,  (  LPARAM  )0  );    		
		 }
		 //		 	
		 //
		 if  (  pRule->iOnvifRuleType  !=  CONST_onvifRuleType_rtspUrl  )  {
			 int  j;
			 for  (  j  =  0;  j  <  mycountof(  m_var.onvif.ipDevsInfo.mems  );  j  ++  )  {
				  pIpDev  =  &m_var.onvif.ipDevsInfo.mems[j];
				  if  (  !pIpDev->iType  )  continue;
				  if  (  pIpDev->rule.usIndex_obj  !=  pRule->usIndex_obj  )  continue;
				  //
				  if  (  pRule->iOnvifRuleType  ==  CONST_onvifRuleType_discovery  )  {  //  2016/08/15
					  displayBuf[0]  =  0;
					  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s %d"  ),  CONST_str_ipCam,  (  int  )pIpDev->rule.usIndex_obj  );
					  if  (  pIpDev->usHelp_subIndex  )  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s.%d"  ),  displayBuf,  (  int  )pIpDev->usHelp_subIndex  );
					  //
					  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s: URI: %s"  ),  displayBuf,  CQyString(  pIpDev->deviceServiceAddr  )  );			 
					  //
					  nPos  =  ::SendMessage(  m_var.hCtrl_onvifList,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )displayBuf  );    					  
				  }
				  //
				  unsigned  char  ucCnt_urls  =  min(  pIpDev->ucCnt_urls,  mycountof(  pIpDev->urls  )  );
				  int  k;
				  for  (  k  =  0;  k  <  ucCnt_urls;  k  ++  )  {
					  displayBuf[0]  =  0;
					  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s %d"  ),  CONST_str_ipCam,  (  int  )pIpDev->rule.usIndex_obj  );
					  if  (  pIpDev->usHelp_subIndex  )  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s.%d"  ),  displayBuf,  (  int  )pIpDev->usHelp_subIndex  );

					  //if  (  pIpDev->subIndex  )  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s %d"  ),  displayBuf,  (  int  )pIpDev->subIndex  );
					  
					  //						
					  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s: %s %s"  ),  displayBuf,  CQyString(  pIpDev->urls[k].token  ),  CQyString(  pIpDev->urls[k].rtspUrl.url  )  );			 
					  
					  //
					  //
					  CHelp_shareDynBmp	help_mem;
					  SHARE_dyn_bmp  *  pMem  =  help_mem.getMemByIndex_obj(  m_hWnd,  &m_var,  CONST_objType_rtspStream,  pRule->usIndex_obj,  pIpDev->usHelp_subIndex  );
					  if  (  pMem  )  {
						_sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s,Used"  ),  displayBuf  );
						}			
					  else  {
						  //  2016/06/25. 删除的操作在这里。
						  if  (  pIpDev->status.toBeStopped  )  {
							  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s, toBeStopped"  ),  displayBuf  );
						  }							
					  }		
					  //		 
					  nPos  =  ::SendMessage(  m_var.hCtrl_onvifList,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )displayBuf  );    
				  }
			 }
		 }
		 //

		//
		continue;		 
	}

	//
	for  (  i  =  0;  i  <  mycountof(  m_var.onvif.ipDevsInfo.mems  );  i  ++  )  {
		 IP_dev  *  pIpDev  =  &m_var.onvif.ipDevsInfo.mems[i];
		 //
		 if  (  !pIpDev->iType  )  continue;
		 //
		 int  ruleIndex  =  getOnvifRuleIndex(  &m_var.onvif.rulesInfo,  pIpDev->rule.usIndex_obj  );
		 if  (  ruleIndex  <  0  )  {				  
			 displayBuf[0]  =  0;
			 _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "Invalid IpCam %d"  ),  pIpDev->rule.usIndex_obj  );
			 if  (  pIpDev->usHelp_subIndex  )  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s %d"  ),  displayBuf,  (  int  )pIpDev->usHelp_subIndex  );
			 if  (  pIpDev->ucCnt_urls  )  {
				 _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s: %s"  ),  displayBuf,  CQyString(  pIpDev->urls[0].rtspUrl.url  )  );			 				  
			 }
			 //
				  CHelp_shareDynBmp	help_mem;
				  SHARE_dyn_bmp  *  pMem  =  help_mem.getMemByIndex_obj(  m_hWnd,  &m_var,  CONST_objType_rtspStream,  pIpDev->rule.usIndex_obj,  pIpDev->usHelp_subIndex  );
				  if  (  pMem  )  {
					_sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s,Used"  ),  displayBuf  );
					}			
				  else  {
					  //  2016/06/25. 删除的操作在这里。
					  if  (  pIpDev->status.toBeStopped  )  {
						  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s, toBeStopped"  ),  displayBuf  );
					  }							
				  }		
				  //		 
				  nPos  =  ::SendMessage(  m_var.hCtrl_onvifList,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )displayBuf  );    


		 }

	}


	iRet  =  0;
errLabel:
	return  iRet;
}






//
#ifdef  __DEBUG__
IP_dev  *  getIpDevBy_index_obj(  ShareDynBmps_ipDevsInfo  *  pIpDevsInfo,  int  index_obj  )
{
	int  i;

	if  (  !pIpDevsInfo  )  return  NULL;
	if  (  !index_obj  )  return  NULL;

	//
	ShareDynBmps_ipDevsInfo  &  ipDevsInfo  =  *pIpDevsInfo;

	//
	for  (  i  =  0;  i  <  mycountof(  ipDevsInfo.mems  );  i  ++  )  {
		 IP_dev  *  pMem  =  &ipDevsInfo.mems[i];
		 if  (  pMem->rule.usIndex_obj  ==  index_obj  )  return  pMem;
	}

	return  NULL;
}
#endif





//
int  CDlgShareDynBmps::refreshIpDevs(  )
{
	int  iErr  =  -1;
	
	//
	ShareDynBmps_ipDevsInfo  *  pIpDevs_src  =  &m_var.shareDynBmpsThreadInfo.onvif.ipDevsInfo;
	ShareDynBmps_ipDevsInfo  *  pIpDevs_dst  =  &m_var.onvif.ipDevsInfo;

	//
	QY_timestamp  ts_src  =  pIpDevs_src->ts_ipDevsInfo;
	
	//
	if  (  timestamp_isSame(  &pIpDevs_dst->ts_ipDevsInfo,  &pIpDevs_src->ts_ipDevsInfo  )  )  return  0;

			 
	//
	CQySyncCnt  syncCnt;		
	if  (  syncMtCnt_rLock(  &m_var.shareDynBmpsThreadInfo.onvif.syncMtCnt_ipDevsInfo,  &syncCnt,  _T(  ""  )  )  )  {
		showInfo_open0(  0,  0,  _T(  "refreshIpDevs: rLock failed"  )  );
		goto  errLabel;		
	}
		 
	//	
	//m_var.onvif.ipDevsInfo  =  m_var.shareDynBmpsThreadInfo.onvif.ipDevsInfo;


	int  i;
	//
	for  (  i  =  0;  i  <  mycountof(  m_var.shareDynBmpsThreadInfo.onvif.ipDevsInfo.mems  );  i  ++  )  {
		 IP_dev  *  pIpDev_src  =  &m_var.shareDynBmpsThreadInfo.onvif.ipDevsInfo.mems[i];
		 IP_dev  *  pIpDev_dst  =  &m_var.onvif.ipDevsInfo.mems[i];

		 //
		 if  (  !pIpDev_src->iType  )  {
			 if  (  !pIpDev_dst->iType  )  continue;
			 //
			 pIpDev_dst->status.toBeStopped  =  TRUE;
			 continue;
		 }
		 //
		 if  (  !pIpDev_dst->iType  )  {
			 //
			 memcpy(  pIpDev_dst,  pIpDev_src,  sizeof(  pIpDev_dst[0]  )  );
			 continue;
		 }
		 //		 
		 if  (  pIpDev_dst->rule.status.uiTranNo_changeContent  !=  pIpDev_src->rule.status.uiTranNo_changeContent  )  {			
			 pIpDev_dst->status.toBeStopped  =  TRUE;
			 continue;
		 }
		 //  2016/11/10
#ifdef  __DEBUG__
		#if  1
		#endif
#endif
		 //
#if  0	 //  2016/11/11
		 if  (  pIpDev_dst->rule.iOnvifRuleType  ==  CONST_onvifRuleType_probe
			 &&  pIpDev_dst->usHelp_subIndex  )  
		 {
			 //
			 TCHAR  tBuf[128];
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Err: usHelp_subIndex of probed ipDev is %d, ( must be 0 ). so remove the result"  ),  (  int  )pIpDev_dst->usHelp_subIndex  );
			 showInfo_open0(  0,  0,  tBuf  );
			 //
			 pIpDev_dst->status.toBeStopped  =  TRUE;
			 continue;
		 }
#endif


		 //
		 //
		 if  (  isSame_ipDev(  pIpDev_src,  pIpDev_dst  )  )  {
			 continue;
		 }
		 //
		 pIpDev_dst->status.toBeStopped  =  TRUE;
		 //
		 continue;
	}

	//
	BOOL  bExists_toDel  =  FALSE;
	//
	for  (  i  =  0;  i  <  mycountof(  m_var.onvif.ipDevsInfo.mems  );  i  ++  )  {
		 IP_dev  *  pIpDev_dst  =  &m_var.onvif.ipDevsInfo.mems[i];
		 //
		 if  (  !pIpDev_dst->status.toBeStopped  )  continue;

		 //  2016/08/09
		 bExists_toDel  =  TRUE;

		 //
		 {
				CHelp_shareDynBmp	help_mem;
				SHARE_dyn_bmp  *  pMem  =  help_mem.getMemByIndex_obj(  m_hWnd,  &m_var,  CONST_objType_rtspStream,  pIpDev_dst->rule.usIndex_obj,  pIpDev_dst->usHelp_subIndex  );
				if  (  pMem  )  {
					// _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s,Used"  ),  displayBuf  );
					}			
				else  {
					  //  2016/06/25. 删除的操作在这里。
					  //if  (  pRule->status.bDel  )  
					  {
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareDynBmp::ipDev index_obj %d will be removed."  ),  (  int  )pIpDev_dst->rule.usIndex_obj  );
						  memset(  pIpDev_dst,  0,  sizeof(  IP_dev  )  );
						  //	
						  continue;				  
					  }			
				}		
		 }

		 //
		 continue;
	}

	//
	if  (  !bExists_toDel  )  {
		pIpDevs_dst->ts_ipDevsInfo  =  ts_src;
	}

	//	
	this->reloadOnvifList(  );

	iErr  =  0;
errLabel:

	return  iErr;
}


//
int  CDlgShareDynBmps::chkAutoOpen(  )
{
	unsigned  int  uiObjType  =  CONST_objType_webcam;

	  SHARE_dynBmps  *  pShare  =  this->getShareDynBmpsBySth(  uiObjType  );
	  if  (  !pShare  )  return  -1;

	  int  i;

	  for  (  i  =  0;  i  <  pShare->usCnt;  i  ++  )  {
		   //	
		   WEBCAM_info  webcamInfo;

		   int  index_obj  =  i  +  1;
	  
		   getWebcamInfo(  uiObjType,  index_obj,  &webcamInfo  );
		   	  
		   int  index_pShare_mem  =  index_obj  -  1;

		   //
		   if  (  !webcamInfo.ucbAutoOpenOnStartup  )  continue;
		   //
		   if  (  !webcamInfo.vName[0]  )  continue;
		   //
		   doAutoOpen_webcam(  uiObjType,  index_pShare_mem,  &webcamInfo  );

	  }


	  //
	  uiObjType  =  CONST_objType_screen;

	  pShare  =  this->getShareDynBmpsBySth(  uiObjType  );
	  if  (  !pShare  )  return  -1;

	  for  (  i  =  0;  i  <  pShare->usCnt;  i  ++  )  {
		   //	
		   WEBCAM_info  webcamInfo;

		   int  index_obj  =  i  +  1;
	  
		   getWebcamInfo(  uiObjType,  index_obj,  &webcamInfo  );
		   	  
		   int  index_pShare_mem  =  index_obj  -  1;

		   //
		   if  (  !webcamInfo.ucbAutoOpenOnStartup  )  continue;
		   //
		   doAutoOpen_screen(  index_pShare_mem,  &webcamInfo  );

	  }




	return  0;
}


//
int  CDlgShareDynBmps::doAutoOpen_webcam(  int  objType,  int  index_pShare_mem,  WEBCAM_info  *  p  )
{
	int  iErr  =  -1;

		 MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  FALSE;
	 FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return FALSE;



	//
	 CAP_STUFF	*	pCapStuff				=	NULL;


	 //
	 pCapStuff  =  (  CAP_STUFF  *  )pFuncs->pf_CAP_STUFF_new(  );
	if  (  !pCapStuff  )  goto  errLabel;
	pFuncs->moniker.pf_addDevicesToMenu(  pCapStuff,  TRUE,  NULL  );


	//
	int  index_a;
	index_a  =  getIndex_moniker_byName(  pCapStuff,  p->aName,  TRUE  );
	if  (  index_a  >=  0  &&  index_a  <  mycountof(  pCapStuff->rgpmAudioMenu  )  )  {
				pFuncs->pf_myChooseDevices(  pCapStuff,  pCapStuff->pmVideo,  pCapStuff->rgpmAudioMenu[index_a]  );
	}
	else  {
				  pFuncs->pf_myChooseDevices(  pCapStuff,  pCapStuff->pmVideo,  NULL  );

	}

	//
	int  iMenuId_v  =  0;
	//
	int  index_v;
	index_v  =  getIndex_moniker_byName(  pCapStuff,  p->vName,  FALSE  );
	if  (  index_v  >=  0  &&  index_v  <  mycountof(  pCapStuff->rgpmVideoMenu  )  )  {
				pFuncs->pf_myChooseDevices(  pCapStuff,  pCapStuff->rgpmVideoMenu[index_v],  pCapStuff->pmAudio  );
				//
					 iMenuId_v  =  index_v  +  ID_MENU_VDEVICE0;


	}
	else  {
				pFuncs->pf_myChooseDevices(  pCapStuff,  NULL,  pCapStuff->pmAudio  );
				//
	}


	//
	if  (  !iMenuId_v  )  goto  errLabel;

	//
	dlgShareDynBmps_toShareWebcam_func(  m_hWnd,  objType,  index_pShare_mem,  (  void  **  )&pCapStuff,  iMenuId_v,  p->ucbUnresizable  );



	iErr  =  0;
errLabel:

	if  (  pCapStuff  )  pFuncs->pf_CAP_STUFF_free(  pCapStuff  );

	return  iErr;
}


//
int  CDlgShareDynBmps::doAutoOpen_screen(  int  index_pShare_mem,  WEBCAM_info  *  p  )
{
	int  iErr  =  -1;

		 MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  FALSE;
	 FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return FALSE;



	//
	dlgShareDynBmps_toShareScreen_func(  m_hWnd,  index_pShare_mem  );



	iErr  =  0;
errLabel:


	return  iErr;
}




//
LRESULT  CDlgShareDynBmps::OnQyComm( WPARAM wParam, LPARAM lParam )
 {
	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;

	 return  pFuncs->shareDynBmps.pf_dlgShareDynBmps_OnQyComm(  g_pQyMc,  m_hWnd,  &m_var,  wParam,  lParam  );
 }

 
 LRESULT  CDlgShareDynBmps::OnQyPostComm( WPARAM wParam, LPARAM lParam )
{
	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;

	 return  pFuncs->shareDynBmps.pf_dlgShareDynBmps_OnQyPostComm(  g_pQyMc,  m_hWnd,  &m_var,  wParam,  lParam  );
}



void CDlgShareDynBmps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgShareDynBmps, CDialog)
	ON_WM_SIZE()
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
	ON_MESSAGE(  CONST_qyWm_postComm,  OnQyPostComm  )
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, &CDlgShareDynBmps::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDlgShareDynBmps::OnBnClickedOk)
	ON_WM_INITMENUPOPUP()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_sharingScreen0, &CDlgShareDynBmps::OnBnClickedButtonsharingscreen0)
	ON_BN_CLICKED(IDC_BUTTON_webcam0, &CDlgShareDynBmps::OnBnClickedButtonwebcam0)
	ON_BN_CLICKED(IDC_BUTTON_webcam1, &CDlgShareDynBmps::OnBnClickedButtonwebcam1)
	ON_BN_CLICKED(IDC_BUTTON_webcam2, &CDlgShareDynBmps::OnBnClickedButtonwebcam2)
	ON_BN_CLICKED(IDC_BUTTON_gps, &CDlgShareDynBmps::OnBnClickedButtongps)
	ON_BN_CLICKED(IDC_BUTTON_procRtsp, &CDlgShareDynBmps::OnBnClickedButtonEdit)
	ON_LBN_SELCHANGE(IDC_LIST1, &CDlgShareDynBmps::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON_add, &CDlgShareDynBmps::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTON_del, &CDlgShareDynBmps::OnBnClickedButtondel)
	ON_BN_CLICKED(IDC_BUTTON_selfTest, &CDlgShareDynBmps::OnBnClickedButtonselftest)
	ON_BN_CLICKED(IDC_BUTTON_playLocalAudio, &CDlgShareDynBmps::OnBnClickedButtonplaylocalaudio)
	ON_BN_CLICKED(IDC_BUTTON_remoteStorageSettings, &CDlgShareDynBmps::OnBnClickedButtonremotestoragesettings)
	ON_BN_CLICKED(IDC_BUTTON_ptz, &CDlgShareDynBmps::OnBnClickedButtonptz)
	ON_BN_CLICKED(IDC_CHECK_autoPopupAndHideOnStartup, &CDlgShareDynBmps::OnBnClickedCheckautopopupandhideOnStartup)
	ON_BN_CLICKED(IDC_BUTTON_hide, &CDlgShareDynBmps::OnBnClickedButtonhide)
END_MESSAGE_MAP()


// CDlgShareDynBmps message handlers

void CDlgShareDynBmps::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();

	if  (  m_var.bCreated  )  {

		traceLogA(  "CDlgSharedWebcams::PostNcDestroy(  ): delete this"  );
		try  {
			 delete  this;		
			}
		catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgSharedWebcams::PostNcDestroy failed."  )  );
		}

	}

	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	qmcApplyForChkingTasks_gui(  pQyMc  );	//  2009/09/10

	//  ×¢Òâ£ºÔÚdelete thisÖ®ºó£¬²»ÄÜµ÷ÓÃÈÎºÎ³ÉÔ±¡£Ô­À´½«!m_var.bCreate·ÅÔÚÕâÀï£¬¾­³£³ö´í¡£
	traceLogA(  "CDlgSharedWebcams::PostNcDestroy(  ) leaves"  );
	
}

void CDlgShareDynBmps::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//  CDialog::OnOK();
}

void CDlgShareDynBmps::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//  CDialog::OnCancel();
	bQuitDlg(  );
}


void CDlgShareDynBmps::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	sizeAllControls(  );
}



 

 BOOL CDlgShareDynBmps::OnInitDialog()
{
	 CDialog::OnInitDialog();

#ifdef  __WINCE__
		return  FALSE;
#else

	 int						iErr	=	-1;
	 QY_MC					*	pQyMc	=	QY_GET_GBUF(  );
	 MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  FALSE;
	 FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return FALSE;

	 cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	 TCHAR	tBuf[128];
	 MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  0  );
	 if  (  !pMisCnt  )  goto  errLabel;
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: %s"  ),  pMisCnt->displayName,  getResStr(  0,  &pQyMc->cusRes,  this->IDD  )  );
	 SetWindowText(  tBuf  );

	 //
	 m_var.bUseDirectX  =  pQyMc->cfg.bUseDxSurface;
	 //m_var.idc  =  IDC_STATIC_pic0;
	 m_var.hWndIDC = ::GetDlgItem(this->m_hWnd, IDC_STATIC_pic0);


	 //
	 this->sizeAllControls(  );

	 //
	 if  (  pProcInfo->cfg.policy.ucbDlgShareDynBmps_autopopupandhideOnStartup  )  {
		 int  idc  =  IDC_CHECK_autoPopupAndHideOnStartup;
		 (  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  1  );
	
	 }

	 //
	 SHARE_dynBmps	*	pShare;

	 pShare  =  getShareDynBmpsBySth(  CONST_objType_screen  );
	 if  (  pShare  )  {
		 //pShare->uiObjType  =  CONST_objType_screen;
		 pShare->pTable_ctrls  =  CONST_controls_table_screen;
		 pShare->usCnt  =  mycountof(  pShare->mems_internal  );
	 }
	 pShare  =  getShareDynBmpsBySth(  CONST_objType_webcam  );
	 if  (  pShare  )  {
		 //pShare->uiObjType  =  CONST_objType_webcam;
		 pShare->pTable_ctrls  =  CONST_controls_table_webcam;
		 pShare->usCnt  =  mycountof(  pShare->mems_internal  );
	 }
	 pShare  =  getShareDynBmpsBySth(  CONST_objType_rtspStream  );
	 if  (  pShare  )  {
		 //pShare->uiObjType  =  CONST_objType_rtspStream;
		 pShare->usCnt  =  mycountof(  pShare->mems_internal  );
	 }
	 pShare  =  getShareDynBmpsBySth(  CONST_objType_smallStream  );
	 if  (  pShare  )  {	 
		 pShare->usCnt  =  mycountof(  pShare->mems_internal  );
	 }
	 pShare = getShareDynBmpsBySth(CONST_objType_ic);
	 if (pShare) {
		 pShare->usCnt = mycountof(pShare->mems_internal);
	 }


	 //
	 unsigned  int  uiObjType  =  CONST_objType_screen;
	 pShare  =  getShareDynBmpsBySth(  CONST_objType_screen  );
	 if  (  !pShare  )  goto  errLabel;
	 if  (  pShare->usCnt  )  {
#if  0
		 pShare->mems_internal[0].usIndex_obj  =  CONST_usIndex_screen0;	//  2014/05/31
		 //
		 lstrcpyn(  pShare->mems_internal[0].name,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fullScreenSharing  ),  mycountof(  pShare->mems_internal[0].name  )  );
#endif
		 CHelp_shareDynBmp  help_dynBmpMem;
		 SHARE_dyn_bmp  *  pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  0  );
		 if  (  pDynBmpMem  )  {
			 pDynBmpMem->resObj.uiObjType  =  uiObjType;
			 pDynBmpMem->resObj.usIndex_obj  =  CONST_usIndex_screen0;
			 //
			 lstrcpyn(  pDynBmpMem->name,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fullScreenSharing  ),  mycountof(  pDynBmpMem->name  )  );

			 //
			 refreshShareCfg_screen( uiObjType,  pDynBmpMem->resObj.usIndex_obj  );
		 }
	 }

	 //
	 uiObjType  =  CONST_objType_smallStream;
	 pShare  =  getShareDynBmpsBySth(  uiObjType  );
	 if  (  !pShare  )  goto  errLabel;
	 if  (  pShare->usCnt  )  {
#if  0
		 pShare->mems_internal[0].usIndex_obj  =  CONST_usIndex_screen0;	//  2014/05/31
		 //
		 lstrcpyn(  pShare->mems_internal[0].name,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fullScreenSharing  ),  mycountof(  pShare->mems_internal[0].name  )  );
#endif
		 CHelp_shareDynBmp  help_dynBmpMem;
		 SHARE_dyn_bmp  *  pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  0  );
		 if  (  pDynBmpMem  )  {
			 pDynBmpMem->resObj.uiObjType  =  uiObjType;
			 pDynBmpMem->resObj.usIndex_obj  =  CONST_usIndex_avStream_slave;
			 //
			 lstrcpyn(  pDynBmpMem->name,  _T(  "smallStream"  ),  mycountof(  pDynBmpMem->name  )  );

			 //
			 //refreshShareCfg_avStream( uiObjType,  pDynBmpMem->resObj.usIndex_obj  );
			 pDynBmpMem->var.ucbLocalVideoOpen  =  TRUE;
		 }
	 }


	 //
	 m_var.pCapStuff1  =  pFuncs->pf_CAP_STUFF_new(  );
	 if  (  !m_var.pCapStuff1  )  goto  errLabel;
	 pFuncs->moniker.pf_addDevicesToMenu(  m_var.pCapStuff1,  TRUE,  NULL  );

	 //  traceLogA(  "sizeof gcap %d",  sizeof(  gcap  )  );
	 uiObjType  =  CONST_objType_webcam;
	 pShare  =  getShareDynBmpsBySth(  uiObjType  );
	 if  (  !pShare  )  goto  errLabel;

	 CAP_STUFF	&	gcap	=	*(  CAP_STUFF  *  )m_var.pCapStuff1;
	 
	 //
	 if  (  !gcap.rgpmVideoMenu[0]  )  pProcInfo->status.vName_1st_webcam[0]  =  0;
	 else  pFuncs->moniker.pf_getMonikerProp(  gcap.rgpmVideoMenu[0],  CONST_moniker_FriendlyName,  pProcInfo->status.vName_1st_webcam,  mycountof(  pProcInfo->status.vName_1st_webcam  )  );
	

	 //
	 int  i,  j;
#if  0  //  2017/06/08
	 for  (  i  =  0,  j  =  0;  i  <  mycountof(  gcap.rgpmVideoMenu  );  i  ++  )  {
		  CHelp_shareDynBmp  help_dynBmpMem;
		  SHARE_dyn_bmp  *  pDynBmpMem  =  NULL;

		  if  (  !gcap.rgpmVideoMenu[i]  )  continue;
		  
		  //
		  pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  j  );
		  if  (  !pDynBmpMem  )  continue;
		  //
		  pDynBmpMem->resObj.uiObjType  =  uiObjType;
		  pDynBmpMem->resObj.usIndex_obj  =  j  +  1;	//  2014/05/31
		  //
		  pDynBmpMem->iMenuId  =  ID_MENU_VDEVICE0  +  i;	//  gcap.iMenuIds_video[i];
		  //  lstrcpyn(  pShare->mems[j].name,  gcap.names_video[i],  mycountof(  pShare->mems[j].name  )  );
		  //  getMonikerFriendlyName(  gcap.rgpmVideoMenu[i],  pShare->mems[j].name,  mycountof(  pShare->mems[j].name  )  );
		  pFuncs->moniker.pf_getMonikerProp(  gcap.rgpmVideoMenu[i],  CONST_moniker_FriendlyName,  pDynBmpMem->name,  mycountof(  pDynBmpMem->name  )  );
		  j  ++  ;
		  if  (  j  >=  pShare->usCnt  )  break;
	 }
#endif
	 //  2017/06/08
	 for  (  j  =  0;  j  <  pShare->usCnt;  j  ++  )  {
		  CHelp_shareDynBmp  help_dynBmpMem;
		  SHARE_dyn_bmp  *  pDynBmpMem  =  NULL;
		  
		  //
		  pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  j  );
		  if  (  !pDynBmpMem  )  continue;
		  //
		  pDynBmpMem->resObj.uiObjType  =  uiObjType;
		  pDynBmpMem->resObj.usIndex_obj  =  j  +  1;	//  2014/05/31
		  //
#if 0
		  WEBCAM_info  webcamInfo;
		  getWebcamInfo(  pDynBmpMem->resObj.usIndex_obj,  &webcamInfo  );
		  //
		  safeTcsnCpy(  webcamInfo.vName,  pDynBmpMem->name,  mycountof(  pDynBmpMem->name  )  );
		  if  (  webcamInfo.aName[0]  )  _sntprintf(  pDynBmpMem->name,  mycountof(  pDynBmpMem->name  ),  _T(  "%s (%s)"  ),  pDynBmpMem->name,  webcamInfo.aName  );
		  

		  //
		  TCHAR  tName[256];
		  for  (  i  =  0;  i  <  mycountof(  gcap.rgpmVideoMenu  );  i  ++  )  {			
			   if  (  !gcap.rgpmVideoMenu[i]  )  continue;
			   //
			   pFuncs->moniker.pf_getMonikerProp(  gcap.rgpmVideoMenu[i],  CONST_moniker_FriendlyName,  tName,  mycountof(  tName  )  );
			   //
			   if  (  _tcsicmp(  tName,  webcamInfo.vName  )  )  continue;
			   //
			   break;		     
		  }
		  if  (  i  ==  mycountof(  gcap.rgpmVideoMenu  )  )  continue;
		  //
		  pDynBmpMem->iMenuId  =  ID_MENU_VDEVICE0  +  i;
#endif
		  //
		  this->refreshShareCfg_webcam(  uiObjType,  pDynBmpMem->resObj.usIndex_obj  );
		  //
		  continue;
	 }

	 //
	 uiObjType = CONST_objType_ic;
	 pShare = getShareDynBmpsBySth(uiObjType);
	 if (!pShare)  goto  errLabel;

	 for (j = 0; j < pShare->usCnt; j++) {
		 CHelp_shareDynBmp  help_dynBmpMem;
		 SHARE_dyn_bmp* pDynBmpMem = NULL;

		 //
		 pDynBmpMem = help_dynBmpMem.getMemByIndex(m_hWnd, &m_var, uiObjType, j);
		 if (!pDynBmpMem)  continue;
		 //
		 pDynBmpMem->resObj.uiObjType = uiObjType;
		 pDynBmpMem->resObj.usIndex_obj = j + 1;	//  2014/05/31
		 //

	 }

	 //
	 mytime(  &m_var.tLastModifiedTime  );

	 this->refreshShareStatus(  0  );

#if  1
	 	 
	 //  2014/05/02
	 if  (  !bSupported_rtsp(  )  )  {
		 ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_rtsp  ),  SW_HIDE  );
		 ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_LIST1  ),  SW_HIDE  );
		 ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_add  ),  SW_HIDE  );
		 ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_procRtsp  ),  SW_HIDE  );
		 ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_del  ),  SW_HIDE  );
		 ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_selfTest  ),  SW_HIDE  );
	 }
	 else  {
#if  0
		   int idc  =  IDC_BUTTON_selfTest;
		   GetDlgItem(  idc  )->EnableWindow(  FALSE  );
#endif
	 }
	 
	 //  2012/05/23
	 if  (  !bSupported_gps(  pQyMc  )  )  {
		 GetDlgItem(  IDC_STATIC_gps  )->ShowWindow(  SW_HIDE  );
		 GetDlgItem(  IDC_STATIC_gpsStatus  )->ShowWindow(  SW_HIDE  );
		 GetDlgItem(  IDC_BUTTON_gps  )->ShowWindow(  SW_HIDE  );
	 }
	 
	 //  2014/08/03
#if  0  //  为了允许正式版客户端视频被远程存储，所以需要开放这个设置
	 if  (  !bSupported_remoteStorage(  )  )  {
		 ::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_remoteStorageSettings  ),  FALSE  );
	 }
#endif

#endif

	 if  (  bQnmDemo(  )  )  {
		 SetDlgItemText(  IDC_STATIC_pic0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_warning_restrictSharedDymBmps  )  );
	 }

	 //  2009/12/10
	 m_var.pMsgBuf_doWnd_guiMsgArrive  =  (  MIS_MSGU  *  )mymalloc(  sizeof(  MIS_MSGU  )  );
	 if  (  !m_var.pMsgBuf_doWnd_guiMsgArrive  )  goto  errLabel;

	 //  2011/10/31
	 for  (  i  =  0;  i  <  mycountof(  m_var.recvdReqs  );  i  ++  )  {
		  m_var.recvdReqs[i].pMsg  =  (  MIS_MSGU  *  )mymalloc(  sizeof(  MIS_MSGU  )  );
		  if  (  !m_var.recvdReqs[i].pMsg  )  goto  errLabel;
	 }

	 //  2012/05/6
	 if  (  bTEST_shareScreen(  0,  0  )  )  {
		 showNotification(  0,  0,  0,  0,  0,  0,  _T(  "TEST share screen"  )  );
	 }
	 
	 //
	 m_var.hCtrl_onvifList	=	::GetDlgItem(  m_hWnd,  IDC_LIST1  );
	 reloadOnvifList(  );

	 //  2014/08/06
	 getRemoteStorageCfg(  &m_var.saveVideo.cfg  );

	 //  2016/06/16
	 if  (  initShareDynBmpsThread(  pProcInfo,  m_hWnd,  &m_var,  &m_var.shareDynBmpsThreadInfo  )  )  {
		 goto  errLabel;
	 }

	 //
	 if  (  pProcInfo->cfg.policy.ucbDlgShareDynBmps_autopopupandhideOnStartup  )  {
		 if  (  !pProcInfo->ucbAutoOpenChked  )  {
			 pProcInfo->ucbAutoOpenChked  =  TRUE;
			 //
			 chkAutoOpen(  );
		 }

	 }
	 
	 //
	 m_var.nElapseInMs  =  1000;	//  5000;
	 m_var.uiTimerId  =  SetTimer(  1,  m_var.nElapseInMs,  NULL  );

	 //  2012/04/29
	 if  (  pProcInfo->cfg.ucbTestGps  )  {
		 m_var.nElapseInMs_test  =  1000;
		 m_var.uiTimerId_test  =  SetTimer(  2,  m_var.nElapseInMs_test,  NULL  );
	 }


	 //
	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 PostMessage(  WM_CLOSE,  0,  0  );
	 }
	 return TRUE;  // return TRUE unless you set the focus to a control
	 // EXCEPTION: OCX Property Pages should return FALSE

#endif
 }



 void CDlgShareDynBmps::OnDestroy()
 {
	 QY_MC			*	pQyMc	=	QY_GET_GBUF(  );
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return;
	 FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return;

	 int				i,  j;

	 MACRO_qyAssert(  !m_var.uiTimerId,  _T(  "dlgShareDynBmps, OnDestroy uiTimeId"  )  );

	 MACRO_qyAssert(  !m_var.uiTimerId_test,  _T(  "dlgShareDynBmps, OnDestroy uiTimeId_test"  )  );

	 //  2012/04/17
	 MACRO_qyAssert(  !m_var.pComPort_gps,  _T(  "dlgShareDynBmps, OnDestroy, pComPort_gps"  )  );

	 //  2016/06/16
	 exitShareDynBmsThread(  pProcInfo,  &m_var.shareDynBmpsThreadInfo  );


	 //  2011/10/31
	 for  (  i  =  0;  i  <  mycountof(  m_var.recvdReqs  );  i  ++  )  {
		  MACRO_safeFree(  m_var.recvdReqs[i].pMsg  );
	 }

	 //
	 MACRO_safeFree(  m_var.pMsgBuf_doWnd_guiMsgArrive  );		//  2009/12/10

	 SHARE_dynBmps	*	pShare;
	 for  (  j  =  0;  j  <  mycountof(  m_var.shares  );  j  ++  )  {
		  pShare  =  &m_var.shares[j];
		  //
		 for  (  i  =  0;  i  <  pShare->usCnt;  i  ++  )  {
			  //CHelp_shareDynBmp  help_dynBmpMem;
			  SHARE_dyn_bmp  *  pDynBmpMem  =  &pShare->mems_internal[i];	//  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  pShare->uiObjType,  i  );
			  if  (  !pDynBmpMem  )  continue;
			  //
			  if  (  pDynBmpMem->var.ucbLocalVideoOpen  )  {
				  //  closeTaskAv(  pShare->uiObjType,  i  ); 
				  closeTaskAv(  pDynBmpMem->resObj.uiObjType,  i  );
			  }
		 }
	 }

	 //int  idc_dst  =  m_var.idc;
	 old_freeCapImages(  this->m_hWnd,  m_var.hWndIDC,  &m_var.images, m_var.hWndIDC ? m_var.hWndIDC : m_hWnd/*old_M_GetDlgItem(  m_hWnd,  idc_dst  )*/,  &m_var.hDc,  _T(  "dlgShareDynBmps.OnDestroy.2105"  ));

	 mytime(  &m_var.tLastModifiedTime  );
	 pFuncs->shareDynBmps.pf_dlgShareDynBmps_sndDynBmpsInfo(  m_hWnd,  &m_var  );

	 pFuncs->pf_CAP_STUFF_free(  m_var.pCapStuff1  );

	 CDialog::OnDestroy();

	 // TODO: Add your message handler code here
 }

 void CDlgShareDynBmps::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialog::OnClose();
	bQuitDlg(  );
}


 void CDlgShareDynBmps::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CDlgShareDynBmps::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//  OnOK();
	OnCancel(  );
}

void CDlgShareDynBmps::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
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

  

void CDlgShareDynBmps::OnTimer(UINT_PTR nIDEvent)
{
	 QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	 if  (  !pProcInfo  )  return;
	 FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return;


	 //




	if  (  nIDEvent  ==  m_var.uiTimerId_test  )  {

		m_var.nCtrls_test  ++  ;

		#if  1	//  def  __DEBUG__
		#if  10	
			//  测试数据
			traceLog(  _T(  "for test"  )  );
			if  (  !m_var.pComPort_gps  )  {
				m_var.pComPort_gps  =  new  CComPortEx;
			}
			CComPortEx  *  pPort  =  (  CComPortEx  *  )m_var.pComPort_gps;
			if  (  !pPort  )  goto  errLabel;

			//
			myGPS_POSITION	pos;
			memset(  &pos,  0,  sizeof(  pos  )  );
		#if  0
			pos.dblLatitude  =  40.2;
			pos.dblLongitude  =  116.6;
		#else
			myTestData_gps(  &m_var.pMisCnt->idInfo,  m_var.nCtrls_test,  &pos  );
		#endif

			GetSystemTime(  &pos.stUTCTime  );

			//
			setGpsPos(  m_var.pComPort_gps,  &pos  );
			if  (  !IsWindow(  pPort->m_var.hWndOwner  )  )  {
				::PostMessage(  m_hWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_gps,  0  );
			}

			//
			QY_SHARED_OBJ	*	pSharedObj	=	NULL;
			int					iIndex_sharedObj	=	m_var.share_gps.var.iIndex_sharedObj;
			if  (  iIndex_sharedObj  )  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
			//
			if  (  pSharedObj  )  {
				//  ::toShareGps(  pProcInfo,  pPort,  0,  &pos,  pSharedObj,  NULL,  (  MIS_MSGU  *  )pPort->m_var.pMsgBuf  );
				pFuncs->gps.pf_toShareGps(  pProcInfo,  pPort,  0,  &pos,  pSharedObj,  NULL,  (  MIS_MSGU  *  )pPort->m_var.pMsgBuf  );
			}

			//
		#endif
	#endif

		return;
	}

	 // TODO: Add your message handler code here and/or call default
	 m_var.nCtrls  ++  ;


#ifdef  __DEBUG__
		//traceLog(  _T(  "dlgShareDynBmps::OnTimer called. %d"  ),  m_var.nCtrls  );
#endif


	 //
	 if  (  !(  m_var.nCtrls  %  (  5000  /  m_var.nElapseInMs  )  )  )  {
		 refreshShareStatus(  0  );
	 }

	 if  (  !(  m_var.nCtrls  %  2  )  )  {
		 this->chkShareGps(  );
	 }


	 //  2011/10/15
#if  0
	 if  (  m_var.bNeed_shareWebcamInConference  )  {		 
		 MACRO_SetForegroundWindow(  this->m_hWnd  );	
		 if  (  pFuncs->pf_bDlgTalkAbove(  pProcInfo->hWnd_shareDynBmps  )  )  {
			 ::SetWindowPos(  pProcInfo->hWnd_shareDynBmps,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOSIZE  |  SWP_NOMOVE  );
			 ::SetWindowPos(  pProcInfo->hWnd_shareDynBmps,  HWND_NOTOPMOST,  0,  0,  0,  0,  SWP_NOSIZE  |  SWP_NOMOVE  );
		
			 //  ::SetForegroundWindow(  pProcInfo->hWnd_shareDynBmps  );

			 #ifdef  __DEBUG__
					 if  (  pFuncs->pf_bDlgTalkAbove(  pProcInfo->hWnd_shareDynBmps  )  )  {
						 traceLog(  _T(  "kk: dlgTalkAbove"  )  );
					 }
			 #endif
	 
		 }

		 return;
	 }
#endif

	 //
	 if  (  !(  m_var.nCtrls  %  (  5000  /  m_var.nElapseInMs  )  )  )  {
		 if  (  m_var.tLastModifiedTime  !=  m_var.tLastModifiedTime_ok  )  {
			 pFuncs->shareDynBmps.pf_dlgShareDynBmps_sndDynBmpsInfo(  m_hWnd,  &m_var  );
		 }
	 }


	 //  2014/09/11
	 if  (  m_var.internalProcess.bNeedProcess  )  {
		 pFuncs->shareDynBmps.pf_dlgShareDynBmps_internalProcess(  g_pQyMc,  m_hWnd,  &m_var  );
	 }

	 
	 //
	 if  (  m_var.onvif.selfTest.bSelfTest  )  {
		 //
		 int  max_nElapseInS  =  100;
		 //
		 int  nElapseInS  =  (  GetTickCount(  )  -  m_var.onvif.selfTest.dwTickCnt_startSelfTest  )  /  1000;
		 TCHAR  tBuf[128];
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %d"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_stop  ),  max_nElapseInS  -  nElapseInS  );		 			
		 SetDlgItemText(  m_var.guiData.iIDC_BUTTON_selfTest,  tBuf  );

		 //
		 if  (  nElapseInS  >  max_nElapseInS  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareDynBmp::rtsp: selfTest too long."  )  );
			 showNotification(  0,  0,  0,  0,  0,  0,  _T(  "selfTest too long"  )  );
			 m_var.onvif.selfTest.bSelfTest  =  FALSE;
			 m_var.onvif.selfTest.bNeedChkRtsp  =  TRUE;
		 }
	 }
	 BOOL  bNeedChk  =  FALSE;
	 if  (  !m_var.onvif.selfTest.bSelfTest  )  {
		 if  (  !(  m_var.nCtrls  %  (  120000  /  m_var.nElapseInMs  )  )
		 ||  m_var.onvif.selfTest.bNeedChkRtsp  )  
		 {
			 bNeedChk  =  TRUE;
		 }
	 }
	 if  (  bNeedChk  )  {
		 if  (  m_var.onvif.selfTest.bNeedChkRtsp  )  {
			 m_var.onvif.selfTest.bNeedChkRtsp  =  FALSE;
		 }

		 //
		 int				i;
		 int				index;


		 //  share_dynBmps
		 for  (  index  =  0;  index  <  mycountof(  m_var.shares  );  index  ++  )  {
			  SHARE_dynBmps	*	pShare;

			  //  
			  pShare  =  &m_var.shares[index];
			  if  (  !pShare  )  goto  errLabel;

#if  0	//  2014/09/09
			  for  (  i  =  0;  i  <  pShare->usCnt;  i  ++  )  {
				  
				   //
				   if  (  !pShare->mems[i].usIndex_obj  )  continue;

				   //  
				   if  (  pShare->mems[i].var.bShared  )  {
					
					   //
					   pFuncs->shareDynBmps.pf_dlgShareDynBmps_chkSharedObj(  m_hWnd,  &m_var,  pShare->mems[i].var.iIndex_sharedObj  );

					   //  2014/0/04
					   if  (  pShare->uiObjType  ==  CONST_objType_rtspStream  )  {
						   QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pShare->mems[i].var.iIndex_sharedObj  );
						   if  (  pSharedObj  )  {
							   ROUTE_sendLocalAv  *  pRoute  =  &pSharedObj->route_sendLocalAv;
							   if  (  isEmpty_ROUTE_sendLocalAv(  pRoute  )  )  {
								   //
								   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareDynBmp::rtsp: route is empty, so close taskAv."  )  );
								   //
								   pFuncs->shareDynBmps.pf_dlgShareDynBmps_closeTaskAv(  m_hWnd,  &m_var,  pShare->uiObjType,  i  );
								   //
								   m_var.onvif.bNeedRefreshed  =  TRUE;
							   }
						   }
					   }

				   }

				   //  2014/06/10
				   if  (  !pShare->mems[i].var.bShared  )  {
					   if  (  pShare->uiObjType  ==  CONST_objType_rtspStream  )  {
						   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareDynBmp::rtsp index_obj %d need to be cleared."  ),  (  int  )pShare->mems[i].usIndex_obj  );
						   memset(  &pShare->mems[i],  0,  sizeof(  pShare->mems[i]  )  );
						   //
						   m_var.onvif.bNeedRefreshed  =  TRUE;
					   }
				   }

			  }
#endif

			 
#if  10	//  2014/09/09
			  for  (  i  =  0;  i  <  pShare->usCnt;  i  ++  )  {
				    CHelp_shareDynBmp  help_dynBmpMem;
					SHARE_dyn_bmp  *  pDynBmpMem  =  NULL;
					pDynBmpMem  =  &pShare->mems_internal[i];	//  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  pShare->uiObjType,  i  );
					if  (  !pDynBmpMem  )  continue;
				  
				   //
				   if  (  !pDynBmpMem->resObj.usIndex_obj  )  continue;

				   //  2021/03/13
				   if  (  !pDynBmpMem->var.iTaskId ) {
					   continue;
				   }

				   //  
				   //  if  (  pDynBmpMem->var.bShared  )  
				   if  (  bShared(  pDynBmpMem  )  )  
				   {
					
					   //
					   pFuncs->shareDynBmps.pf_dlgShareDynBmps_chkTask(  m_hWnd,  &m_var,  pDynBmpMem->var.iTaskId  );

					   //  2014/0/04
					   if  (  pDynBmpMem->resObj.uiObjType  ==  CONST_objType_rtspStream  )  {
						   int  index_taskInfo  =  GuiShare.pf_getQmcTaskInfoIndexBySth(  pProcInfo,  pDynBmpMem->var.iTaskId  );
						   QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )GuiShare.pf_getQmcTaskInfoByIndex(  pProcInfo,  index_taskInfo  );
						   if  (  pTaskInfo  )  {
							   ROUTE_sendLocalAv  *  pRoute  =  &pTaskInfo->var.curRoute_sendLocalAv;
							   if  (  isEmpty_ROUTE_sendLocalAv(  pRoute  )  )  {
								   //
								   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareDynBmp::rtsp: route is empty, so close taskAv."  )  );
								   //
								   pFuncs->shareDynBmps.pf_dlgShareDynBmps_closeTaskAv(  m_hWnd,  &m_var,  pDynBmpMem->resObj.uiObjType,  i  );
								   //
								   m_var.onvif.bNeedRefreshed  =  TRUE;
							   }
						   }
					   }

				   }

				   //  2014/06/10
				   if  (  !bShared(  pDynBmpMem  )  )  {
					   if  (  GetTickCount(  )  -  pDynBmpMem->var.dwTickCnt_start  >  10000  )  {
						   if  (  pDynBmpMem->resObj.uiObjType  ==  CONST_objType_rtspStream  )  {
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareDynBmp::rtsp index_obj %d need to be cleared."  ),  (  int  )pDynBmpMem->resObj.usIndex_obj  );
							   if  (  help_dynBmpMem.clear(  pDynBmpMem  )  )  
							   {
								   MACRO_qyAssert(  0,  _T(  "dynBmpMem.clear failed"  )  );
							   }
							   //
							   m_var.onvif.bNeedRefreshed  =  TRUE;
						   }
					   }
				   }

			  }
#endif

		 }

		 //  share_gps
		 if  (  m_var.share_gps.bShare  )  {
			 pFuncs->shareDynBmps.pf_dlgShareDynBmps_chkTask(  m_hWnd,  &m_var,  m_var.share_gps.var.iTaskId  );
		 }

	 }
	 //
	 //  2016/07/07
	 if  (  !timestamp_isSame(  &m_var.onvif.ipDevsInfo.ts_ipDevsInfo,  &m_var.shareDynBmpsThreadInfo.onvif.ipDevsInfo.ts_ipDevsInfo  )  )  {
		 //
		 showInfo_open0(  0,  0,  _T(  "shareDynBmps.timer: refresh ipDevsInfo"  )  );		
		 //
		 this->refreshIpDevs(  );
	 }
	 //  2014/06/10
	 if  (  m_var.onvif.bNeedRefreshed  )  {
		 DWORD  dwTickCnt  =  GetTickCount(  );
		 if  (  dwTickCnt  -  m_var.onvif.dwLastTickCnt_refreshed  >  5000  )  {
			 m_var.onvif.dwLastTickCnt_refreshed  =  dwTickCnt;
			 m_var.onvif.bNeedRefreshed  =  FALSE;
			 //
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareDynBmps::reload onvif list."  )  );
			 this->reloadOnvifList(  );
		 }
	 }

errLabel:

	 CDialog::OnTimer(nIDEvent);
 }





void CDlgShareDynBmps::OnBnClickedButtonsharingscreen0()
{
	// TODO: Add your control notification handler code here
	toShareScreen(  0  );
}



void CDlgShareDynBmps::OnBnClickedButtonwebcam0()
{
	// TODO: Add your control notification handler code here
	toShareWebcam(  CONST_objType_webcam,  0  );
}

void CDlgShareDynBmps::OnBnClickedButtonwebcam1()
{
	// TODO: Add your control notification handler code here
	toShareWebcam(  CONST_objType_webcam,  1  );
}

void CDlgShareDynBmps::OnBnClickedButtonwebcam2()
{
	// TODO: Add your control notification handler code here
	//toShareWebcam(  2  );
	toShareWebcam(CONST_objType_ic, 0);
}

void CDlgShareDynBmps::OnBnClickedButtongps()
{
	// TODO: Add your control notification handler code here
	toShareGps(  );
}


//
int  getOnvifRuleIndex(  ShareDynBmps_onvif_rulesInfo  *  pRulesInfo,  unsigned  short  usIndex_obj  )
{
	if  (  !pRulesInfo  )  return  -1;
	ShareDynBmps_onvif_rulesInfo  &  rulesInfo  =  *pRulesInfo;

	//
	int  i;
	for  (  i  =  0;  i  <  mycountof(  rulesInfo.mems  );  i  ++  )  {
		if  (  rulesInfo.mems[i].usIndex_obj  ==  usIndex_obj  )  break;
	}
	if  (  i  ==  mycountof(  rulesInfo.mems  )  )  return  -1;

	return  i;
}

void CDlgShareDynBmps::OnBnClickedButtonEdit()
{
	// TODO: Add your control notification handler code here  
	CDlgRtspUrl   dlg;
	//BOOL  bList  =  TRUE;
	BOOL  bNew  =  FALSE;
	TCHAR	tBuf[256]  =  _T(  ""  );

	//
	ShareDynBmps_onvif_rulesInfo  &  rulesInfo  =  m_var.onvif.rulesInfo;

	//
	int  urlIndex  =  getOnvifRuleIndex(  &rulesInfo,  m_var.onvif.sel.usIndex_obj_sel  );
	if  (  urlIndex  <  0  )  return;


	//		
	Onvif_rule  *  pItemUrl  =  &rulesInfo.mems[urlIndex];
	dlg.bSetDlgInfo(  bNew,  pItemUrl->usIndex_obj,  pItemUrl->iOnvifRuleType,  pItemUrl->cusName,  pItemUrl->url,  pItemUrl->usrName,  pItemUrl->passwd,  pItemUrl->defToken  );	

	//dlg.bSetDlgInfo(  bList  );
	if  (  dlg.DoModal()  ==  IDOK  )  
	{		
		m_var.onvif.sel.usIndex_obj_sel  =  dlg.m_var.rule.usIndex_obj;

		//
		this->reloadOnvifList(  );
		
	}

errLabel:
	return;
}

void CDlgShareDynBmps::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
	TCHAR		tBuf[1024]  =  _T(  ""  );
	TCHAR	*	pT  =  NULL;
	int			iItem;

	TCHAR	*	p;

	iItem  =  ::SendMessage(  m_var.hCtrl_onvifList,  LB_GETCURSEL,  0,  0  );

	if  (  iItem  ==  LB_ERR  )  goto errLabel;

	int  len  =  ::SendMessage(  m_var.hCtrl_onvifList,  LB_GETTEXTLEN,  iItem,  0  );
	if  (  len  <=  0  )  goto  errLabel;

	if  (  len  >=  mycountof(  tBuf  )  )  goto  errLabel;

	pT  =  tBuf;
	if  (  !pT  )  goto  errLabel;
	::SendMessage(  m_var.hCtrl_onvifList,  LB_GETTEXT,  iItem,  (  LPARAM  )pT  );
	pT[len]  =  0;

	//
	BOOL  bIpCam  =  FALSE;
	unsigned  short  usIndex_obj  =  0;
	unsigned  short  usSubIndex  =  0;
	
	//
	if  (  !_tcsnicmp(  pT,  CONST_str_rule,  lstrlen(  CONST_str_rule  )   )  )  {
		pT  +=  lstrlen(  CONST_str_rule  );
		}
	else  if  (  !_tcsnicmp(  pT,  CONST_str_ipCam,  lstrlen(  CONST_str_ipCam  )  )  )  {
			  bIpCam  =  TRUE;	
			  pT  +=  lstrlen(  CONST_str_ipCam  );	
			  }
	else  {
		  goto  errLabel;
	}
	tTrim(  pT  );
	//
	usIndex_obj  =  _ttol(  pT  );
	if  (  bIpCam  )  {
		int			ch  =  '.';
				  
		//		
		p  =  _tcschr(  pT,  ch  );
		if  (  p  )  {
			*p  =  0;
			p  ++  ;
			usSubIndex  =  _ttol(  p  );
		}		  
	}

	//
	ShareDynBmps_onvif_rulesInfo  &  rulesInfo  =  m_var.onvif.rulesInfo;

	//
	int  i;
	for  (  i  =  0;  i  <  mycountof(  rulesInfo.mems  );  i  ++  )  {
		 if  (  rulesInfo.mems[i].usIndex_obj  ==  usIndex_obj  )  {
			 //
			 m_var.onvif.sel.bIpCam  =  bIpCam;
			 m_var.onvif.sel.usIndex_obj_sel  =  usIndex_obj;
			 m_var.onvif.sel.usHelp_subIndex  =  usSubIndex;
			 //
			 break;
		 }
	}
	//

	//
    int idc  =  IDC_BUTTON_selfTest;
	GetDlgItem(  idc  )->EnableWindow(  TRUE  );


errLabel:
	return;


}

void CDlgShareDynBmps::OnBnClickedButtonadd()
{
	// TODO: Add your control notification handler code here
	TCHAR  tBuf[256]  =  _T(  ""  );
	CDlgRtspUrl  dlg;

	//BOOL  bList  =  TRUE;
	BOOL  bNew  =  TRUE;

	//
	dlg.bSetDlgInfo(  bNew,  0,  0,  NULL,  NULL,  NULL,  NULL,  NULL  );

	//
	if  (  dlg.DoModal()  ==  IDOK  )  
	{
		m_var.onvif.sel.usIndex_obj_sel  =  dlg.m_var.rule.usIndex_obj;

		//
		this->reloadOnvifList(  );

	}

}


void CDlgShareDynBmps::OnBnClickedButtondel()
{
	// TODO: Add your control notification handler code here
	//
	ShareDynBmps_onvif_rulesInfo  &  rulesInfo  =  m_var.onvif.rulesInfo;

	int  urlIndex  =  getOnvifRuleIndex(  &rulesInfo,  m_var.onvif.sel.usIndex_obj_sel  );
	if  (  urlIndex  <  0  )  return;

	Onvif_rule  *  pRule  =  &rulesInfo.mems[urlIndex];
	if  (  !pRule->usIndex_obj  )  return;

	
	int				uiCapType	=	CONST_capType_av;
	int				uiSubCapType	=	CONST_subCapType_webcam;


	QY_REG			reg;
	memset(  &reg,  0,  sizeof(  reg  )  );

	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//  _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	getRegRootKey_qmc(  uiCapType,  uiSubCapType,  0,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  _T(  CONST_regKeyName_rtspUrl  )  );

	//
	TCHAR  tBuf[128];
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _ltot(  pRule->usIndex_obj,  tBuf,  10  )  );  
	//
#if  0
	TCHAR	regVal[512]  =  _T(  ""  );
	pUrl->status.bDel  =  TRUE;
	getRegVal_webcam_rtspUrl(  pUrl,  regVal,  mycountof(  regVal  )  );

	TCHAR  tBuf[128];
	qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _ltot(  pUrl->usIndex_obj,  tBuf,  10  ),  regVal  );
#endif

	//
	reloadOnvifList(  );

}

void CDlgShareDynBmps::OnBnClickedButtonselftest()
{
	// TODO: Add your control notification handler code here
	QY_MC			*	pQyMc		=	QY_GET_GBUF();

	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	CWaitCursor	cur;

	//
	ShareDynBmps_onvif_rulesInfo  &  rulesInfo  =  m_var.onvif.rulesInfo;

	//
	int  urlIndex  =  getOnvifRuleIndex(  &rulesInfo,  m_var.onvif.sel.usIndex_obj_sel  );
	if  (  urlIndex  <  0  )  return;


	if  (  !m_var.onvif.selfTest.bSelfTest  )  {
		m_var.onvif.selfTest.bSelfTest  =  TRUE;
		m_var.onvif.selfTest.dwTickCnt_startSelfTest  =  GetTickCount(  );
		m_var.onvif.selfTest.bNeedChkRtsp  =  FALSE;
		m_var.onvif.selfTest.usIndex_obj_selfTest  =  m_var.onvif.sel.usIndex_obj_sel;
		m_var.onvif.selfTest.usHelp_subIndex_selfTest  =  m_var.onvif.sel.usHelp_subIndex;		
		//
		pFuncs->shareDynBmps.pf_dlgShareDynBmps_testRtspUrl(  g_pQyMc,  m_hWnd,  &m_var,  m_var.onvif.sel.usIndex_obj_sel,  m_var.onvif.sel.usHelp_subIndex  );
		
		}
	else  {
		  m_var.onvif.selfTest.bSelfTest  =  FALSE;
		  m_var.onvif.selfTest.bNeedChkRtsp  =  TRUE;
		  m_var.onvif.selfTest.usIndex_obj_selfTest  =  0;
		  m_var.onvif.selfTest.usHelp_subIndex_selfTest  =  0;
		  
		  //
		  pFuncs->shareDynBmps.pf_dlgShareDynBmps_refreshShareStatus(  g_pQyMc,  m_hWnd,  &m_var,  CONST_objType_rtspStream  );
	}

	//
	m_var.onvif.bNeedRefreshed  =  TRUE;
	
	return;
	
}





//
void CDlgShareDynBmps::OnBnClickedButtonptz()
{
	// TODO: Add your control notification handler code here
	//
	int		iErr	=	-1;
	
	int  ii;
	int  i;
	int  uiObjType  =  CONST_objType_rtspStream;
	
	CHelp_shareDynBmp  help_dynBmpMem;
	SHARE_dyn_bmp  *  pMem  =  NULL;

	
	SHARE_dynBmps	*	pShare;																		
	pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  uiObjType  );	
	if  (  !pShare  )  goto  errLabel;							    

	//
	unsigned  short  usIndex_obj  =  m_var.onvif.sel.usIndex_obj_sel;
	unsigned  short  usHelp_subIndex  =  m_var.onvif.sel.usHelp_subIndex;

	//
	for  (  ii  =  0;  ii  <  mycountof(  m_var.onvif.ipDevsInfo.mems  );  ii  ++  )  {	
		if  (  m_var.onvif.ipDevsInfo.mems[ii].rule.usIndex_obj  ==  usIndex_obj
			&&  m_var.onvif.ipDevsInfo.mems[ii].usHelp_subIndex  ==  usHelp_subIndex  ) 			
		{		
			break;				 
		}
	}
	if  (  ii  ==  mycountof(  m_var.onvif.ipDevsInfo.mems  )  )  goto  errLabel;	
	//
	//Onvif_rule  url  =  m_var.onvif.rulesInfo.mems[ii];		
	IP_dev  *  pIpDev  =  &m_var.onvif.ipDevsInfo.mems[ii];
	//
	if  (  pIpDev->iType  !=  CONST_ipDevType_ipCam  )  {
		qyShowHint(  _T(  "Only ipCam can using ptz"  )  );
		goto  errLabel;
	}
	//
	i  =  help_dynBmpMem.getIndexByIndex_obj(  m_hWnd,  &m_var,  uiObjType,  pIpDev->rule.usIndex_obj,  pIpDev->usHelp_subIndex  );
	if  (  i  <  0  )  {
		qyShowHint(  _T(  "ptz can't be used if video of the device is not alive"  )  );
		goto  errLabel;
	}

	pMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );	
	if  (  !pMem  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "getMemByIndex failed"  )  );
		#endif
		goto  errLabel;
	}


	if  (  !pMem->var.ucbLocalVideoOpen  )  {
					 #ifdef  __DEBUG__
							 traceLog(  _T(  "shareDynBmp failed, ucbLocalVideoOpen 0"  )  );
					 #endif
					 goto  errLabel;
	
	}
	
	//
	PARAM_viewLocalPtzControl  param  =  {0};
	//
	param.pf_dlg_YTCmd  =  dlg_YTCmd_shareDynBmps;
	//
	param.p0  =  &this->m_var;
	//
	viewLocalPtzControl(  m_hWnd,  TRUE,  uiObjType,  usIndex_obj,  usHelp_subIndex,  &param,  &pMem->ptzWnd  );
				 
	//		
	iErr  =  0;

errLabel:
		
	return;
 }







//
void CDlgShareDynBmps::OnBnClickedButtonplaylocalaudio()
{
	// TODO: Add your control notification handler code here
	QY_MC			*	pQyMc		=	QY_GET_GBUF();

	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;


	pProcInfo->cfg.ucbPlayLocalAudio_captured  =  !pProcInfo->cfg.ucbPlayLocalAudio_captured;
	
	//	
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_refreshShareStatus(  g_pQyMc,  m_hWnd,  &m_var,  CONST_objType_webcam  );

}


void CDlgShareDynBmps::OnBnClickedButtonremotestoragesettings()
{
	// TODO: Add your control notification handler code here
	showDlgRemoteStorageSettings(  m_hWnd  );
	//
	getRemoteStorageCfg(  &m_var.saveVideo.cfg  );
	//

}



void CDlgShareDynBmps::OnBnClickedCheckautopopupandhideOnStartup()
{
	// TODO: Add your control notification handler code here
	int  idc;

	idc  =  IDC_CHECK_autoPopupAndHideOnStartup;
	BOOL  bVal    =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  ?  1  :  0;

	//
		//
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	TCHAR			*	pRegVal				=	NULL;
	char				buf[256];
	QY_REG				reg;
	unsigned  char		ucCmd;
	unsigned  int		uiCapType;
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );
	TCHAR			*	pT;
	long				lVal;
	TCHAR				rootKeyStr[256]		=  _T(  ""  );

	
	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
	
	ucCmd  =  FALSE;
	pRegVal  =  _T(  CONST_regValName_dlgShareDynBmps_autopopupandhideOnStartup  );
	if  (  bVal  )  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _T(  "1"  )  );
	else  qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	return;
}


void CDlgShareDynBmps::OnBnClickedButtonhide()
{
	// TODO: Add your control notification handler code here
	
	//if  (  myMessageBox(  this->m_hWnd,  _T(  "Are you sure?"  ),  _T(  "qycx.com"  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;

	//
	ShowWindow(  SW_HIDE  );


errLabel:
	return;
}
