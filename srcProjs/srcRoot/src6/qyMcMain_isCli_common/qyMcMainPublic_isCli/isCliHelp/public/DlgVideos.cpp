// DlgVideos.cpp: implementation of the CDlgVideos class.
//
//////////////////////////////////////////////////////////////////////

#include	"stdafx.h"
#include	<math.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"

#include	"DlgVideos.h"
#include	"qmcVideoCapture_isCli.h"
//  #include	"DlgCfgVideoConference.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"
#include	"dlgTalkProc.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"qycusResTemp.h"

#include	"ctxQmc.h"
#include	"qmcCommFunc_iscli.h"
#include	"wallTalkers.h"

//
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include	"remoteAssistPublic.h"



/////////////
__declspec(  dllexport  )  int  showDlgVideos(  HWND  hParent,  HWND  hDlg_org,  BOOL  bDlgTalk,  void  *  pPARAM_dlgVideos,  CAP_subWnds  *  pSubWnds,  HWND  *  phWnd  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	PARAM_dlgVideos  *  p  =  (  PARAM_dlgVideos  *  )pPARAM_dlgVideos;

#ifndef  __SUPPORT_dlgDesktopsMon__
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "showEnlargedWnd not supported"  )  );
		 #endif
		 return  -1;
#else
	int						iErr				=		-1;
	QY_MC				*	pQyMc				=		QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo			=		QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp	*	pFuncs				=		QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	//CAP_IMAGE			*	pImg				=		NULL;
	CDlgVideos			*	pDlg				=		NULL;
	TCHAR					tBuf[256]			=		_T(  ""  );
	RECT					rect;


	MIS_CNT				*	pMisCnt				=		getMisCntByName(  pProcInfo,  _T(  ""  )  );			//  2009/
	if  (  !pMisCnt  )  return  -1;

	if  (  !hDlg_org  ||  !p  )  return  -1;

	//
	void  *  pDb  =  NULL;
	#ifndef  __NOTSUPPORT_DB__
			 CQnmDb				db;
			 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
			 pDb  =  db.m_pDbMem->pDb;
	#endif
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	if  (  bDlgTalk  )  {
		//  CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );
		CHelp_getDlgTalkVar		help_getDlgTalkVar_mgr;

		CHelp_getDlgTalkVar		help_getDlgTalkVar;
		DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlg_org  );
		if  (  !pDlgTalkVar  )  goto  errLabel;

		DLG_TALK_var  *  pMgrVar  =  NULL;
		if  (  isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  pMgrVar  =  pDlgTalkVar;
		else  {
			  TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
			  if  (  !pTalkerShadow  )  goto  errLabel;
			  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr  );
			  if  (  !pMgrVar  )  goto  errLabel;
		}


		if  (  !p->bMeImage  
			&&  pMgrVar->av.taskInfo.bTaskExists  )  
		{
		}
		
		if  (  p->bLocalAvWnd  )  {	//  2011/03/13
		}
	}


	
	//
	//  2007/09/08	
	pDlg  =  new  CDlgVideos(  IsWindow(  hParent  )  ?  CWnd::FromHandle(  hParent  )  :  CWnd::GetDesktopWindow(  )  );
	if  (  !pDlg  )  goto  errLabel;
	if  (  p->bVideoConference  )  {
			  if  (  bDlgTalk  )  {
				  //  CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );
				  CHelp_getDlgTalkVar	help_getDlgTalkVar;
				  DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlg_org  );
				  if  (  !pDlgTalkVar  )  goto  errLabel;
				  pFuncs->pf_getTalkerDesc(  pDlgTalkVar->addr.idInfo,  tBuf,  mycountof(  tBuf  ),  0,  0  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_videoConference  )  );
			  }
	}
	//  2014/10/12
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  _T(  "Local video"  )  );

	//
	int				iWndContentType		=	CONST_qyWndContentType_dlgVideos;		//  2011/02/02
	int				iSubtype			=	CONST_dlgVideosSubtype_view;
	int				iResId_menu			=	0;
	unsigned  int	nElapseInMs			=	0;
	nElapseInMs  =  1000;
	//
	if  (  !pDlg->bSetDlgInfo(  iWndContentType,  iSubtype,  tBuf,  iResId_menu,  hDlg_org,  p->iTaskId,  &p->idInfo_sender,  p->uiTranNo_openAvDev,  pMisCnt,  p->usCnt_monPics_row,  p->usCnt_monPics_col,  p->uiInitW,  p->uiInitH,  FALSE,  nElapseInMs  )  )  goto  errLabel;
	
	//
	pDlg->m_var.ucbAutoClip  =  TRUE;

	//  2016/03/12
	if  (  p->bBgWallImage  )  {
		pDlg->m_var.showResolutionInTitle.ucbNeedShow  =  TRUE;
	}
		
	//
	pDlg->bEnableScrollBar(  p->bScrollBarEnabled  );
	pDlg->doLayout(  );
	pDlg->bEnableRemoteAssist(  p->bRemoteAssist  );

	//  2010/08/30
	if  (  p->bVideoConference  )  {
		pDlg->m_var.bVideoConference  =  TRUE;
	}

	//  2010/12/24
	if  (  p->bInstantAssistant  )  {
		pDlg->m_var.bInstantAssistant  =  TRUE;
	}

	//
	if  (  p->bMediaControl  )  {
		pDlg->m_var.bMediaControl  =  TRUE;
		pDlg->m_var.iIndex_capBmp  =  p->iIndex_capBmp;
		CAP_procInfo_bmpU  *  pCapBmp  =  getCapBmpBySth(  pProcInfo,  p->iIndex_capBmp,  0  );
		if  (  pCapBmp  )  {
			QY_SHARED_OBJ	*	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapBmp->common.iIndex_sharedObj  );
			if  (  pSharedObj  )  {
				pDlg->m_var.iIndex_capAudio  =  pSharedObj->iIndex_capAudio;
			}
		}
	}

	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		
	//	
	if  (  p->bVideoConference  ||  p->bRemoteAssist  )  {
		if  (  registerSubWnd(  pDlg->m_hWnd,  0,  0,  p->iTaskId,  NULL,  0,  0,  pSubWnds,  NULL  )  )  {
			traceLogA(  "showEnlargedWnd failed. registerSubWnd failed."  );
			goto  errLabel;
		}
	}
	//
	pDlg->ShowWindow(  SW_SHOW  );
	
	//
	if  (  bDlgTalk  )  {
			  //  CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );		
			  CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;

			  CHelp_getDlgTalkVar	help_getDlgTalkVar;
			  DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlg_org  );
			  if  (  !pDlgTalkVar  )  goto  errLabel;
			  	
			  DLG_TALK_var  *  pMgrVar  =  NULL;
			  if  (  isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  pMgrVar  =  pDlgTalkVar;
			  else  {
				    TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
					if  (  !pTalkerShadow  )  goto  errLabel;
					pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr  );
					if  (  !pMgrVar  )  goto  errLabel;
			  }

			  if  (  p->bLocalAvWnd  )  {	//  2011/03/13
				  //  pDlgTalk->m_var.av.hWnd_localAv  =  pDlg->m_hWnd;
			  }
			  else  if  (  pMgrVar->av.taskInfo.bTaskExists  )  {
						//  if  (  pMgrVar->av.taskInfo.iTaskId  ==  p->m_var.iTaskId  )  pDlgTalkVar->av.hWnd_remoteAv_taskInfo  =  pDlg->m_hWnd;
			  }
	}

	iErr  =  0;

errLabel:
	if  (  iErr  )  {
        if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
		if  (  phWnd  )  {
			if  (  pDlg  )  {
				*phWnd  =  pDlg->m_hWnd;
			}
		} 
	}


	return  iErr;
#endif
}


//
 __declspec(  dllexport  )  int  showEnlargedWnd(  HWND  hParent,  HWND  hDlg_org,  BOOL  bDlgTalk,  void  *  pPARAM_dlgVideos,  CAP_subWnds  *  pSubWnds  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	PARAM_dlgVideos  *  p  =  (  PARAM_dlgVideos  *  )pPARAM_dlgVideos;

#ifndef  __SUPPORT_dlgDesktopsMon__
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "showEnlargedWnd not supported"  )  );
		 #endif
		 return  -1;
#else
	int						iErr				=		-1;
	QY_MC				*	pQyMc				=		QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo			=		QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp	*	pFuncs				=		QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	CAP_IMAGE			*	pImg				=		NULL;
	CDlgVideos			*	pDlg				=		NULL;
	TCHAR					tBuf[256]			=		_T(  ""  );
	RECT					rect;


	MIS_CNT				*	pMisCnt				=		getMisCntByName(  pProcInfo,  _T(  ""  )  );			//  2009/
	if  (  !pMisCnt  )  return  -1;

	if  (  !hDlg_org  ||  !p  )  return  -1;
	if  (  !p->pImgs  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "showEnlargedWnd failed, p->m_var.pImgs is null"  )  );
		#endif
		return  -1;
	}


	void  *  pDb  =  NULL;
	#ifndef  __NOTSUPPORT_DB__
			 CQnmDb				db;
			 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
			 pDb  =  db.m_pDbMem->pDb;
	#endif
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	if  (  bDlgTalk  )  {
		//  CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );
		CHelp_getDlgTalkVar		help_getDlgTalkVar_mgr;

		CHelp_getDlgTalkVar		help_getDlgTalkVar;
		DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlg_org  );
		if  (  !pDlgTalkVar  )  goto  errLabel;

		DLG_TALK_var  *  pMgrVar  =  NULL;
		if  (  isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  pMgrVar  =  pDlgTalkVar;
		else  {
			  TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
			  if  (  !pTalkerShadow  )  goto  errLabel;
			  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr  );
			  if  (  !pMgrVar  )  goto  errLabel;
		}


		if  (  !p->bMeImage  
			&&  pMgrVar->av.taskInfo.bTaskExists  )  
		{
		}
		
		if  (  p->bLocalAvWnd  )  {	//  2011/03/13
		}
	}

	if  (  p->iIndex_capImage  >=  0  &&  p->iIndex_capImage  <  mycountof(  p->pImgs->mems  )  )  {
		pImg  =  &p->pImgs->mems[p->iIndex_capImage];

		if  (  IsWindow(  pImg->hWnd_remoteAv  )  )  {
			if  (  ::IsIconic(  pImg->hWnd_remoteAv  )  )  ::SendMessage(  pImg->hWnd_remoteAv,  WM_SYSCOMMAND,  SC_RESTORE,  0  );
			else  ::SetForegroundWindow(  pImg->hWnd_remoteAv  );
			iErr  =  0;  goto  errLabel;
		}		
	}

	
	//
	//  2007/09/08	
	pDlg  =  new  CDlgVideos(  IsWindow(  hParent  )  ?  CWnd::FromHandle(  hParent  )  :  CWnd::GetDesktopWindow(  )  );
	if  (  !pDlg  )  goto  errLabel;
	if  (  pImg  )  {
		pFuncs->pf_getTalkerDesc(  pImg->idInfo_sender,  tBuf,  mycountof(  tBuf  ),  0,  0  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s( %d )"  ),  tBuf,  pImg->uiTranNo_openAvDev  );
		}
	else  if  (  p->bVideoConference  )  {
			  if  (  bDlgTalk  )  {
				  //  CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );
				  CHelp_getDlgTalkVar	help_getDlgTalkVar;
				  DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlg_org  );
				  if  (  !pDlgTalkVar  )  goto  errLabel;
				  pFuncs->pf_getTalkerDesc(  pDlgTalkVar->addr.idInfo,  tBuf,  mycountof(  tBuf  ),  0,  0  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_videoConference  )  );
			  }
	}
	//  2014/10/12
	if  (  pImg  &&  !pImg->idInfo_sender.ui64Id  
		&&  p->bBgWallImage  
		&&  p->idInfo_sel_bgWall.ui64Id  )  
	{
		//////////////
		QY_MESSENGER_REGINFO		regInfo;
		MY_REG_DESC				desc;
		//	 					
		if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  pQyMc->cfg.db.iDbType,  CONST_fieldIdTable_en,  CONST_tabName_qyImObjRegInfoTab,  pMisCnt->cfg.misServName,  &p->idInfo_sel_bgWall,  0,  &regInfo  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );			 
		regInfo2Desc(  0,  &regInfo,  &desc,  0,  0,  tBuf,  mycountof(  tBuf  )  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u"  ),  tBuf,  p->idInfo_sel_bgWall.ui64Id  );
		/////////////////////////////////
	}
	//
	int				iWndContentType		=	CONST_qyWndContentType_dlgVideos;		//  2011/02/02
	int				iSubtype			=	CONST_dlgVideosSubtype_enlargedWnd;
	int				iResId_menu			=	0;
	unsigned  int	nElapseInMs			=	0;
	if  (  p->bRemoteAssist  )  {
		iResId_menu  =  CONST_resId_menu_dlgRemoteAssist;
		nElapseInMs  =  1000;
	}
	if  (  !pDlg->bSetDlgInfo(  iWndContentType,  iSubtype,  tBuf,  iResId_menu,  hDlg_org,  p->iTaskId,  &p->idInfo_sender,  p->uiTranNo_openAvDev,  pMisCnt,  p->usCnt_monPics_row,  p->usCnt_monPics_col,  p->uiInitW,  p->uiInitH,  FALSE,  nElapseInMs  )  )  goto  errLabel;
	
	//  2016/03/12
	if  (  p->bBgWallImage  )  {
		pDlg->m_var.showResolutionInTitle.ucbNeedShow  =  TRUE;
	}
		
	//
	pDlg->bEnableScrollBar(  p->bScrollBarEnabled  );
	pDlg->doLayout(  );
	pDlg->bEnableRemoteAssist(  p->bRemoteAssist  );

	//  2010/08/30
	if  (  p->bVideoConference  )  {
		pDlg->m_var.bVideoConference  =  TRUE;
	}

	//  2010/12/24
	if  (  p->bInstantAssistant  )  {
		pDlg->m_var.bInstantAssistant  =  TRUE;
	}

	//
	if  (  p->bMediaControl  )  {
		pDlg->m_var.bMediaControl  =  TRUE;
		pDlg->m_var.iIndex_capBmp  =  p->iIndex_capBmp;
		CAP_procInfo_bmpU  *  pCapBmp  =  getCapBmpBySth(  pProcInfo,  p->iIndex_capBmp,  0  );
		if  (  pCapBmp  )  {
			QY_SHARED_OBJ	*	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapBmp->common.iIndex_sharedObj  );
			if  (  pSharedObj  )  {
				pDlg->m_var.iIndex_capAudio  =  pSharedObj->iIndex_capAudio;
			}
		}
	}

	//
	if  (  p->bEnlageFromDynBmps  )  {
		pDlg->m_var.bEnlargeFromDynBmps  =  TRUE;
	}

	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		
	//	
	if  (  p->bVideoConference  ||  p->bRemoteAssist  )  {
		if  (  registerSubWnd(  pDlg->m_hWnd,  0,  0,  p->iTaskId,  NULL,  0,  0,  pSubWnds,  NULL  )  )  {
			#ifdef  __DEBUG__
					traceLogA(  "showEnlargedWnd failed. registerSubWnd failed."  );
			#endif
			goto  errLabel;
		}
	}
	//
	pDlg->ShowWindow(  SW_SHOW  );
	//

	if  (  pImg  )  {
        pImg->hWnd_remoteAv  =  pDlg->m_hWnd;
		}
	else  if  (  bDlgTalk  )  {
			  //  CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );		
			  CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;

			  CHelp_getDlgTalkVar	help_getDlgTalkVar;
			  DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlg_org  );
			  if  (  !pDlgTalkVar  )  goto  errLabel;
			  	
			  DLG_TALK_var  *  pMgrVar  =  NULL;
			  if  (  isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  pMgrVar  =  pDlgTalkVar;
			  else  {
				    TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
					if  (  !pTalkerShadow  )  goto  errLabel;
					pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr  );
					if  (  !pMgrVar  )  goto  errLabel;
			  }

			  if  (  p->bLocalAvWnd  )  {	//  2011/03/13
				  //  pDlgTalk->m_var.av.hWnd_localAv  =  pDlg->m_hWnd;
			  }
			  else  if  (  pMgrVar->av.taskInfo.bTaskExists  )  {
						//  if  (  pMgrVar->av.taskInfo.iTaskId  ==  p->m_var.iTaskId  )  pDlgTalkVar->av.hWnd_remoteAv_taskInfo  =  pDlg->m_hWnd;
			  }
	}

	//
	if  (  p->bEnlageFromDynBmps  )  {
		::PostMessage(  pDlg->m_hWnd,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );
	}


	//
	iErr  =  0;

errLabel:
	if  (  iErr  )  {
        if  (  pDlg  )  delete  pDlg;
	}

	return  iErr;
#endif
}


//
 __declspec(  dllexport  )  int  showRemoteAssistWnd(  HWND  hParent,  HWND  hDlg_org,  BOOL  bDlgTalk,  void  *  pPARAM_dlgVideos,  CAP_subWnds  *  pSubWnds  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	PARAM_dlgVideos  *  p  =  (  PARAM_dlgVideos  *  )pPARAM_dlgVideos;

#ifndef  __SUPPORT_dlgDesktopsMon__
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "showEnlargedWnd not supported"  )  );
		 #endif
		 return  -1;
#else
	int						iErr				=		-1;
	QY_MC				*	pQyMc				=		QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo			=		QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp	*	pFuncs				=		QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	CAP_IMAGE			*	pImg				=		NULL;
	CDlgVideos			*	pDlg				=		NULL;
	TCHAR					tBuf[256]			=		_T(  ""  );
	RECT					rect;
	MIS_CNT				*	pMisCnt				=		getMisCntByName(  pProcInfo,  _T(  ""  )  );			//  2009/
	if  (  !pMisCnt  )  return  -1;

	if  (  !hDlg_org  ||  !p  )  return  -1;
	if  (  !p->pImgs  )  return  -1;

	if  (  bDlgTalk  )  {
		//  CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );
		CHelp_getDlgTalkVar		help_getDlgTalkVar_mgr;

		CHelp_getDlgTalkVar		help_getDlgTalkVar;
		DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlg_org  );
		if  (  !pDlgTalkVar  )  goto  errLabel;

		DLG_TALK_var  *  pMgrVar  =  NULL;
		if  (  isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  pMgrVar  =  pDlgTalkVar;
		else  {
			  TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
			  if  (  !pTalkerShadow  )  goto  errLabel;
			  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr  );
			  if  (  !pMgrVar  )  goto  errLabel;
		}


		if  (  !p->bMeImage  
			&&  pMgrVar->av.taskInfo.bTaskExists  )  
		{
#if  0	//  201409/22
			if  (  pMgrVar->av.taskInfo.iTaskId  ==  p->m_var.iTaskId  
				&&  IsWindow(  pDlgTalkVar->av.hWnd_remoteAv_taskInfo  )  )
			{
				if  (  IsIconic(  pDlgTalkVar->av.hWnd_remoteAv_taskInfo  )  )  ::SendMessage(  pDlgTalkVar->av.hWnd_remoteAv_taskInfo,  WM_SYSCOMMAND,  SC_RESTORE,  0  );

				if  (  p->m_var.bFreeCapImages  )  {
					QY_WMBUF_COMM	wmBuf;
					memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
					wmBuf.uiType  =  CONST_qyWmParam_freeCapImages;
					SendMessage(  pDlgTalkVar->av.hWnd_remoteAv_taskInfo,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
				}

				SetForegroundWindow(  pDlgTalkVar->av.hWnd_remoteAv_taskInfo  );
				iErr  =  0;  goto  errLabel;
			}
#endif
		}
		
		if  (  p->bLocalAvWnd  )  {	//  2011/03/13
			#if  0
			if  (  IsWindow(  pDlgTalk->m_var.av.hWnd_localAv  )  )  {

				if  (  p->m_var.bFreeCapImages  )  {
					QY_WMBUF_COMM	wmBuf;
					memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
					wmBuf.uiType  =  CONST_qyWmParam_freeCapImages;
					SendMessage(  pDlgTalk->m_var.av.hWnd_localAv,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
				}

				iErr  =  0;  goto  errLabel;
			}
			#endif
		}
	}

	if  (  p->iIndex_capImage  >=  0  &&  p->iIndex_capImage  <  mycountof(  p->pImgs->mems  )  )  {
		pImg  =  &p->pImgs->mems[p->iIndex_capImage];

		if  (  IsWindow(  pImg->hWnd_remoteAv  )  )  {
			if  (  ::IsIconic(  pImg->hWnd_remoteAv  )  )  ::SendMessage(  pImg->hWnd_remoteAv,  WM_SYSCOMMAND,  SC_RESTORE,  0  );
			else  ::SetForegroundWindow(  pImg->hWnd_remoteAv  );
			iErr  =  0;  goto  errLabel;
		}		
	}

	
	//
	//  2007/09/08	
	pDlg  =  new  CDlgVideos(  IsWindow(  hParent  )  ?  CWnd::FromHandle(  hParent  )  :  CWnd::GetDesktopWindow(  )  );
	if  (  !pDlg  )  goto  errLabel;
	if  (  pImg  )  {
		pFuncs->pf_getTalkerDesc(  pImg->idInfo_sender,  tBuf,  mycountof(  tBuf  ),  0,  0  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s( %d )"  ),  tBuf,  pImg->uiTranNo_openAvDev  );
		}
	else  if  (  p->bVideoConference  )  {
			  if  (  bDlgTalk  )  {
				  //  CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );
				  CHelp_getDlgTalkVar	help_getDlgTalkVar;
				  DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlg_org  );
				  if  (  !pDlgTalkVar  )  goto  errLabel;
				  pFuncs->pf_getTalkerDesc(  pDlgTalkVar->addr.idInfo,  tBuf,  mycountof(  tBuf  ),  0,  0  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_videoConference  )  );
			  }
	}
	int				iWndContentType		=	CONST_qyWndContentType_dlgVideos;		//  2011/02/02
	int				iSubtype			=	CONST_dlgVideosSubtype_remoteAssist;
	int				iResId_menu			=	0;
	unsigned  int	nElapseInMs			=	0;
	if  (  p->bRemoteAssist  )  {
		iResId_menu  =  CONST_resId_menu_dlgRemoteAssist;
		nElapseInMs  =  1000;
	}
	if  (  !pDlg->bSetDlgInfo(  iWndContentType,  iSubtype,  tBuf,  iResId_menu,  hDlg_org,  p->iTaskId,  &p->idInfo_sender,  p->uiTranNo_openAvDev,  pMisCnt,  p->usCnt_monPics_row,  p->usCnt_monPics_col,  p->uiInitW,  p->uiInitH,  FALSE,  nElapseInMs  )  )  goto  errLabel;
	//  pDlg->m_var.uiTaskType  =  p->m_var.uiTaskType;
	
	//
	pDlg->bEnableScrollBar(  p->bScrollBarEnabled  );
	pDlg->doLayout(  );
	pDlg->bEnableRemoteAssist(  p->bRemoteAssist  );

	//  2010/08/30
	if  (  p->bVideoConference  )  {
		pDlg->m_var.bVideoConference  =  TRUE;
	}

	//  2010/12/24
	if  (  p->bInstantAssistant  )  {
		pDlg->m_var.bInstantAssistant  =  TRUE;
	}

	//
	if  (  p->bMediaControl  )  {
		pDlg->m_var.bMediaControl  =  TRUE;
		pDlg->m_var.iIndex_capBmp  =  p->iIndex_capBmp;
		CAP_procInfo_bmpU  *  pCapBmp  =  getCapBmpBySth(  pProcInfo,  p->iIndex_capBmp,  0  );
		if  (  pCapBmp  )  {
			QY_SHARED_OBJ	*	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapBmp->common.iIndex_sharedObj  );
			if  (  pSharedObj  )  {
				pDlg->m_var.iIndex_capAudio  =  pSharedObj->iIndex_capAudio;
			}
		}
	}

	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		
	//	
	if  (  p->bVideoConference  ||  p->bRemoteAssist  )  {
		if  (  registerSubWnd(  pDlg->m_hWnd,  0,  0,  p->iTaskId,  NULL,  0,  0,  pSubWnds,  NULL  )  )  {
			traceLogA(  "showEnlargedWnd failed. registerSubWnd failed."  );
			goto  errLabel;
		}
	}
	//
	pDlg->ShowWindow(  SW_SHOW  );
	//

	if  (  pImg  )  {
        pImg->hWnd_remoteAv  =  pDlg->m_hWnd;
		}
	else  if  (  bDlgTalk  )  {
			  //  CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );		
			  CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;

			  CHelp_getDlgTalkVar	help_getDlgTalkVar;
			  DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlg_org  );
			  if  (  !pDlgTalkVar  )  goto  errLabel;
			  	
			  DLG_TALK_var  *  pMgrVar  =  NULL;
			  if  (  isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  pMgrVar  =  pDlgTalkVar;
			  else  {
				    TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
					if  (  !pTalkerShadow  )  goto  errLabel;
					pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr  );
					if  (  !pMgrVar  )  goto  errLabel;
			  }
			  //
			  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
			  if  (  !pShadowMgr  )  goto  errLabel;

			  //
			  if  (  IsWindow(  pShadowMgr->remoteAssist.hWnd_remoteAssist  )  )  {
				  SendMessage(  pShadowMgr->remoteAssist.hWnd_remoteAssist,  WM_CLOSE,  0,  0  );
			  }
			  if  (  IsWindow(  pShadowMgr->remoteAssist.hWnd_remoteAssist  )  )  {
				  goto  errLabel;
			  }
			  pShadowMgr->remoteAssist.hWnd_remoteAssist  =  0;

			  //
			  pShadowMgr->remoteAssist.iTaskId  =  p->iTaskId;
			  pShadowMgr->remoteAssist.hWnd_remoteAssist  =  pDlg->m_hWnd;

	}

	iErr  =  0;

errLabel:
	if  (  iErr  )  {
        if  (  pDlg  )  delete  pDlg;
	}

	return  iErr;
#endif
}




//
  __declspec(  dllexport  )  void  *  getDlgVideosVar(  HWND  hDlgVideos  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if  (  !IsWindow(  hDlgVideos  )  )  return  NULL;
	CDlgVideos  *  pDlg  =  (  CDlgVideos  *  )CDlgVideos::FromHandlePermanent(  hDlgVideos  );
	if  (  !pDlg  )  return  NULL;

	return  &pDlg->m_var;
}




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDlgVideos::CDlgVideos(  CWnd* pParent /*= NULL*/) :  CDlgDesktopsMon(  pParent  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	//
	m_var.iMAX_timeoutInS_dlgVideos = MAX_timeoutInS_dlgVideos_mfc;


	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	//m_var.bUseDirectX  =  pQyMc->cfg.bUseDxSurface;	//  2009/08/06
}

CDlgVideos::~CDlgVideos()
{

}





 //	 
 BOOL	CDlgVideos::bSetDlgInfo(  int  iWndContentType,  int  iSubtype,  LPCTSTR  title,  int  iResId_menu,  HWND  hDlgTalk,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo_sender,  unsigned  int  uiTranNo_openAvDev,  MIS_CNT  *  pMisCnt,  unsigned  short  usCnt_row,  unsigned  short  usCnt_col,  unsigned  int  uiInitW_pc,  unsigned  int  uiInitH_pic,  unsigned  char  ucbLocalAv,  unsigned  int  nElapseInMs  )
{
	BOOL							bRet		=	FALSE;
	QY_MC						*	pQyMc		=	QY_GET_GBUF(  );

	if  (  !pMisCnt  )  {
		#ifdef  __DEBUG__
				traceLogA(  "dlgVideos::bSegDlgInfo failed, pMisCnt is null"  );
		#endif
		return  FALSE;
	}

	if  (  !iResId_menu  )  iResId_menu  =  CONST_resId_menu_dlgVideos;

	if  (  !::CDlgDesktopsMon::bSetDlgInfo(  iWndContentType,  iSubtype,  iResId_menu,  usCnt_row,  usCnt_col,  uiInitW_pc,  uiInitH_pic  )  )  goto  errLabel;

	if  (  title  )  lstrcpyn(  m_var.title,  title,  mycountof(  m_var.title  )  );
	//  m_var.iResId_menu  =  iResId_menu  ?  iResId_menu  :  CONST_resId_menu_dlgVideos;		//  2009/09/20
	m_var.hDlgTalk  =  hDlgTalk;
	m_var.iTaskId  =  iTaskId;
	if  (  pIdInfo_sender  )  m_var.idInfo_sender.ui64Id  =  pIdInfo_sender->ui64Id;
	m_var.uiTranNo_openAvDev  =  uiTranNo_openAvDev;
	//  m_var.iIndex_capImage  =  iIndex_capImage;
	m_var.pMisCnt  =  pMisCnt;
	//
	m_var.ucbLocalAv  =  ucbLocalAv;
	//
	m_var.nElapseInMs  =  nElapseInMs;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  CDlgVideos::bEnableRemoteAssist(  BOOL  bRemoteAssist  )
 {
	 if  (  m_var.bRemoteAssist  ==  bRemoteAssist  )  return  TRUE;
	 m_var.bRemoteAssist  =  bRemoteAssist;
	 return  TRUE;
 }


BOOL CDlgVideos::OnInitDialog()
{
	int								iErr	=	-1;
	QY_MC						*	pQyMc	=	QY_GET_GBUF(  );
	if  (  !m_var.pMisCnt  )  return  FALSE;
	MC_VAR_isCli  *  pProcInfo				=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	CDlgDesktopsMon				*	pBase	=	this;
	QY_DMITEM					*	pItem	=	pBase->m_var.pIdcTable;

	//m_var.idc  =  (  int  )pItem[0].des;
	m_var.hCtrl = ::GetDlgItem(m_hWnd, (int)pItem[0].des);

	CDlgDesktopsMon::OnInitDialog(  );
	
	//  cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//  m_var.bUseDirectX  =  pQyMc->cfg.bUseDxSurface;	//  2009/08/06

	SetWindowText(  m_var.title  );


	//
	m_var.pMsgBuf_doWnd_guiMsgArrive  =  (  MIS_MSGU  *  )mymalloc(  sizeof(  MIS_MSGU  )  );
	if  (  !m_var.pMsgBuf_doWnd_guiMsgArrive  )  goto  errLabel;


	//  2012/05/05
	int  iSize;	
	m_var.usCnt_zoneParams  =  pProcInfo->av.usCnt_players;
	iSize  =  m_var.usCnt_zoneParams  *  sizeof(  ZONE_PARAM  );
	m_var.pZoneParams  =  (  ZONE_PARAM  *  )mymalloc(  iSize  );
	if  (  !m_var.pZoneParams  )  goto  errLabel;
	memset(  m_var.pZoneParams,  0,  iSize  );


	//  if  (  m_var.iIndex_capImage  <  0  &&  m_var.iTaskId  )  SetTimer(  1,  1000,  NULL  );
	if  (  m_var.nElapseInMs  )  SetTimer(  1,  m_var.nElapseInMs,  NULL  );

	//  2011/03/25
	m_var.guiData.bInited  =  TRUE;

	iErr  =  0;

errLabel:
	
	if  (  iErr  )  {
		traceLogA(  "CDlgVideo::OnInitDialog error exists."  );
		PostMessage(  WM_CLOSE,  0,  0  );
	}

	return  TRUE;
}


BEGIN_MESSAGE_MAP(CDlgVideos, CDlgDesktopsMon)
	ON_WM_DESTROY()
	ON_WM_ACTIVATE()
//	ON_WM_SIZE()
//	ON_COMMAND(ID_stopScrollBar, Onstopscrollbar)
//	ON_UPDATE_COMMAND_UI(ID_stopScrollBar, OnUpdatestopscrollbar)
//	ON_COMMAND(ID_startScrollBar, Onstartscrollbar)
//	ON_UPDATE_COMMAND_UI(ID_startScrollBar, OnUpdatestartscrollbar)
	ON_WM_TIMER()
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
	ON_WM_MOUSEWHEEL()
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void CDlgVideos::OnDestroy()
{
#if 0
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	MACRO_safeFree(  m_var.pZoneParams  );							//  2012/05/05

	MACRO_safeFree(  m_var.pMsgBuf_doWnd_guiMsgArrive  );			//  2009/12/08

	//int  idc_dst  =  m_var.idc;
	//old_freeCapImages(  this->m_hWnd,  m_var.idc,  &m_var.images,  old_M_GetDlgItem(  m_hWnd,  idc_dst  ),  &m_var.hDc,  _T(  "dlgVideos.OnDestroy.846"  ));
	freeCapImages(this->m_hWnd, m_var.hCtrl, &m_var.images, m_var.hCtrl, &m_var.hDc);
#endif

	//
	dlgVideos_OnDestroy(m_hWnd, m_var);

	//
	CDlgDesktopsMon::OnDestroy();

	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë
}



//
//
#if 0
int  CDlgVideos::dlgVideos_procVideo(  MIS_MSG_procVideo_qmc  *	pMsg    )
 {
	 int		iErr	=	-1;

	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;

	 CDlgDesktopsMon  *  pBase  =  this;
	 DLG_desktopsMon_var  *  pBaseVar  =  &pBase->m_var;

	 //  2017/10/02
	 int  iSubtype  =  pBaseVar->iSubtype;

	 //
	 //
	 ZONE_PARAM				*	pZoneParam		=	NULL;
	 int							i;

				  /*
				  switch  (  m_var.uiTaskType  )  {
						  case  CONST_imTaskType_shareScreen:
						  case  CONST_imTaskType_remoteAssist:
						  case  0:									//  2009/10/12. for vWall
							    bUseDxSurface  =  FALSE;
								break;
						  default:
								  break;
				  }
				  */
				  //bUseDxSurface  =  FALSE;
				  #ifdef  __DEBUG__
						  {
							  static  BOOL  b  =  FALSE;
							  if  (  !b  )  traceLogA(  "Not finished: dlgVideos, bUseDxSurface shall be processed."  );
							  b  =  TRUE;
						  }
				  #endif

				
				  //  if  (  m_var.bVideoConference  )  
				  {  //  2010/09/12

					  //			
					  CAP_IMAGES			*	pImgs		=	&m_var.images;
					  HWND						hDlg		=	m_hWnd;

					#if  0
					  QY_PLAYER				*	pPlayer;
					  
					  if  (  pMsg->index_player  <  0  ||  pMsg->index_player  >=  pProcInfo->av.usCnt_players  )  goto  errLabel;
					  pPlayer  =  &pProcInfo->av.pPlayers[pMsg->index_player];
					#endif

					  if  (  pMsg->playerId.index_player  <  0  ||  pMsg->playerId.index_player  >=  m_var.usCnt_zoneParams  )  goto  errLabel;
					  pZoneParam  =  &m_var.pZoneParams[pMsg->playerId.index_player];
				  						
					  BOOL			bZoneOk		=	FALSE;				  
					  if  (  pZoneParam->index_capImage  >=  0  &&  pZoneParam->index_capImage  <  mycountof(  pImgs->mems  )  )  {
						  CAP_IMAGE	*	pImg	=	&pImgs->mems[pZoneParam->index_capImage];
						  if  (  pImg->idInfo_sender.ui64Id  ==  pMsg->idInfo_sender.ui64Id  
							  &&  pImg->uiTranNo_openAvDev  ==  pMsg->uiTranNo_openAvDev
							  &&  pImg->usIndex_activeMems_from  ==  pMsg->usIndex  )  
						  {
							  bZoneOk  =  TRUE;
						  }
					  }											   
					  //
					  #ifdef  __DEBUG__
						  //  if  (  !bMeImages  ) traceLog(  _T(  "dlgTalk: bZoneOk %d, index_player %d, usIndex %d, index_capImage %d, "  ),  bZoneOk,  pMsg->index_player,  pMsg->usIndex,  pPlayer->video.m_var.zoneParam.index_capImage  );
					  #endif
					  //
					  if  (  !bZoneOk  )  {							
						  memset(  pZoneParam,  0,  sizeof(  pZoneParam[0]  )  );
				  
						  //
						  if  (  iSubtype  ==  CONST_dlgVideosSubtype_view  )  {
							  QY_DMITEM  *  pTable  =  pBase->m_var.pIdcTable;
							  if  (  !pTable  )  goto  errLabel;
							  int  idc  =  (  int  )pTable->des;
							  RECT  rc;
							  if  (  getPicRect(  idc,  &rc  )  )  goto  errLabel;
							  int  iW  =  rc.right  -  rc.left;
							  int  iH  =  rc.bottom  -  rc.top;
							  //
							  if  (  pMsg->bih.biWidth  !=  iW  ||  pMsg->bih.biHeight  !=  iH  )  {
								  SetPicRect(  pMsg->bih.biWidth,  pMsg->bih.biHeight,  FALSE  );
								  showInfo_open0(  0,  _T(  ""  ),  _T(  "dlgVideos::procVideo, pMsg->wXh not matched, call SetPicRect"  )  );
							  }
						  }
						  //
						  if  (  m_var.bVideoConference  )  {

							  CHelp_getDlgTalkVar	help_getDlgTalkVar;

							  DLG_TALK_var	*	pDlgTalkVar	=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  m_var.hDlgTalk  );
							  if  (  !pDlgTalkVar  )  goto  errLabel;


							  CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;

							  DLG_TALK_var	*	pMgrVar		=	NULL;
							  if  (  isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  pMgrVar  =  pDlgTalkVar;
							  else  {
								    TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
									if  (  !pShadow  )  goto  errLabel;
									pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pShadow->hMgr  );
									if  (  !pMgrVar  )  goto  errLabel;
							  }

							  BOOL	bFound  =  FALSE;
							  if  (  !pMsg->iTaskId  )  {
								  traceLogA(  "dlgTalk::OnQyComm failed: iTaskId is 0"  );
								  goto  errLabel;					  
							  }
							  MIS_MSG_TASK	*	pMsgTask;
							  if  (  (  pMsgTask  =  pFuncs->pf_findTaskInProcessQ(  pMgrVar,  pMsg->iTaskId,  FALSE,  FALSE  )  )  )  {
								  if  (  !bTaskAlive(  pMsgTask->iStatus  )  )  goto  errLabel;			  
								  bFound  =  TRUE;
							  }
							  if  (  !bFound  )  {
								  //  2012/04/25			
								  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
								  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->talkerDynBmps  );  i  ++  )  {
									  if  (  pMsg->iTaskId  ==  pShadowMgr->talkerDynBmps[i].taskInfo.iTaskId  )  {
										  bFound  =  TRUE;
										  break;
									  }
								  }	
							  }							  		
							  if  (  !bFound  )  {
								  #ifdef  __DEBUG__
								          traceLog(  _T(  "dlgTalk_OnQyComm failed: findTaskInProcessQ failed, iTaskId %d"  ),  pMsg->iTaskId  );
								  #endif
								  goto  errLabel;
							  }

							  //  {	//  2010/09/12
							  if  (  pMgrVar->av.taskInfo.bTaskExists
								  &&  pMgrVar->av.taskInfo.iTaskId  ==  pMsg->iTaskId  
								  &&  pMgrVar->av.taskInfo.ucbVideoConference  )
							  {
								  CAP_IMAGE	*	pImg	=	NULL;
								  int				i;
								
								  for  (  i  =  0;  i  <  mycountof(  pImgs->mems  );  i  ++  )  {
									   pImg  =  &pImgs->mems[i];
									   if  (  pImg->iTaskId  ==  pMsg->iTaskId
										   &&  pImg->idInfo_sender.ui64Id  ==  pMsg->idInfo_sender.ui64Id  )  
									   {
										   //  freeCapImage(  hDlg,  0,  pImg  );
										   //int  idc_dst  =  m_var.idc;
										   //old_freeCapImage(  hDlg,  m_var.idc,  pImg,  old_M_GetDlgItem(  hDlg,  idc_dst  ),  _T(  "dlgVideos_procVideo.1010"  ));
										   freeCapImage(hDlg, m_var.hCtrl, pImg, m_var.hCtrl);
									   }
								  }

								  //
								  QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pMgrVar->av.taskInfo.iIndex_taskInfo  );
								  if  (  !pTaskInfo  )  goto  errLabel;
								  if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
								  QMC_taskData_conf  *  pTc = (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;


								  QY_MESSENGER_ID	idInfo_sender;
								  idInfo_sender.ui64Id  =  pMsg->idInfo_sender.ui64Id;
								  if  (  !isMemFromActive(  &pTc->videoConference,  &idInfo_sender,  null,  NULL  )  )  {
									  traceLog(  _T(  "skipped: %I64u is not an activeMem"  ),  pMsg->idInfo_sender.ui64Id  );
									  goto  errLabel;
								  }

								  if  (  pMsg->usIndex  >=  mycountof(  pImgs->mems  )  )  goto  errLabel;
								  pImg  =  &pImgs->mems[pMsg->usIndex];
								  //  freeCapImage(  hDlg,  0,  pImg  );
								  //int  idc_dst  =  m_var.idc;
								  //old_freeCapImage(  hDlg,  m_var.idc,  pImg,  old_M_GetDlgItem(  hDlg,  idc_dst  ),  _T(  "dlgVideos_procVideo.1032"  ));
								  freeCapImage(hDlg, m_var.hCtrl, pImg, m_var.hCtrl);

								  pImg->iW_org  =  pMsg->bih.biWidth;
								  pImg->iH_org  =  pMsg->bih.biHeight;
								  pImg->idInfo_sender.ui64Id  =  pMsg->idInfo_sender.ui64Id;
								  pImg->uiTranNo_openAvDev  =  pMsg->uiTranNo_openAvDev;
								  pImg->usIndex_activeMems_from  =  pMsg->usIndex;

								  pImgs->head.bResized  =  TRUE;
							  }
							  //  }
						  }
					  }

				  }
				
				  //  
				  //  if  (  drawCapImages(  m_hWnd,  m_var.idc,  &m_var.hDc,  NULL,  m_var.ucbLocalAv,  m_var.ucbAutoClip,  pMsg,  0,  0,  pBaseVar->mems[0].iW,  pBaseVar->mems[0].iH,  NULL,  pZoneParam,  &m_var.images,  bUseDxSurface,  FALSE  )  )  goto  errLabel;
				  HWND  hWnd_src = m_var.hCtrl;// old_M_GetDlgItem(m_hWnd, m_var.idc);	//  2014/04/10
				  HWND  hWnd_dst  =  hWnd_src;
				  
				  //
				  PARAM_dc_draw  dcDrawParam  =  {0};
				  //
				  if  (   iSubtype  ==  CONST_dlgVideosSubtype_view  )  {
					  dcDrawParam.param_getCapImages.bNew  =  TRUE;
				  }
				  
				  //
				  if  (  drawCapImages(  hWnd_src,  m_var.ucbAutoClip,  pMsg,  0,  0,  pBaseVar->mems[0].iW,  pBaseVar->mems[0].iH,  NULL,  pZoneParam,  &m_var.images,  hWnd_dst,  &m_var.hDc,  &dcDrawParam  )  )  goto  errLabel;

				  //
				  iErr  =  0;
errLabel:
				  return  iErr;
				  
}
#endif


//
 LRESULT  CDlgVideos::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
#if 0
	long				lRet				=					-1;
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	CDlgDesktopsMon	*	pBase				=					this;
	QY_MC			*	pQyMc				=					QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo			=					QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	CTX_qm_thread  *  pCqt  =  &pQyMc->gui.ctx_gui_thread;  //  2017/09/28
	
	//
	int  idc_dst;  
	
	if  (  !pComm  )  return  -1;

	if  (  !m_var.guiData.bInited  )  {
		//  MACRO_qyAssert(  0,  _T(  "CDlgVideos::OnQyComm, can't be called before inited"  )  );
		#ifdef  __DEBUG__
				traceLog(  _T(  "CDlgVideos::OnQyComm, can't be called before inited"  )  );
		#endif
		return  -1;
	}

	//
	switch  (  pComm->uiType  )  {
			case  CONST_misMsgType_procVideo_qmc:  {  		
				  MIS_MSG_procVideo_qmc		*	pMsg			=	(  MIS_MSG_procVideo_qmc  *  )pComm;
				  //
				  if  (  dlgVideos_procVideo(  m_hWnd,  m_var, pMsg,  pBase->m_var.mems[0].iW,  pBase->m_var.mems[0].iH  )  )  goto  errLabel;
				  //
				  if  (  m_var.showResolutionInTitle.ucbNeedShow  )  {
					  if  (  !m_var.showResolutionInTitle.ucbDone  )  {
						  TCHAR   tBuf[128]  =  _T(  ""  );
						  GetWindowText(  tBuf,  mycountof(  tBuf  )  );
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %dX%d"  ),  tBuf,  pMsg->bih.biWidth,  pMsg->bih.biHeight  );
						  SetWindowText(  tBuf  );
						  m_var.showResolutionInTitle.ucbDone  =  TRUE;
					  }
				  }
				  }
				  break;

			case  CONST_qyWmParam_freeCapImage:
				  QY_MESSENGER_ID	idInfo;
				  idInfo.ui64Id  =  pComm->u.freeCapImage.idInfo.ui64Id;
				  //int  idc_dst;  idc_dst  =  m_var.idc;
				  //old_freeCapImageBySth(  pCqt,  m_hWnd,  m_var.idc,  pComm->u.freeCapImage.iTaskId,  &idInfo,  &m_var.images,  old_M_GetDlgItem(  m_hWnd,  idc_dst  )  );				  
				  freeCapImageBySth(pCqt, m_hWnd, m_var.hCtrl, pComm->u.freeCapImage.iTaskId, &idInfo, &m_var.images, m_var.hCtrl);
				  break;

			case  CONST_qyWmParam_freeCapImages:	//  2010/12/27
				  //idc_dst  =  m_var.idc;
				  //old_freeCapImages(  m_hWnd,  m_var.idc,  &m_var.images,  old_M_GetDlgItem(  m_hWnd,  idc_dst  ),  &m_var.hDc,  _T(  "dlgVideos.OnQyComm.1125"  ));
				  freeCapImages(m_hWnd, m_var.hCtrl, &m_var.images, m_var.hCtrl, &m_var.hDc);
				  break;

			default:
					break;
	}

	lRet  =  QY_RC_WMOK;

errLabel:

	return  lRet;
#endif

	//
	return dlgVideos_OnQyComm(m_hWnd, &m_var, wParam, lParam);
}






 LRESULT  CDlgVideos::OnQyPostComm(  WPARAM  wParam,  LPARAM  lParam  )
{
#if 0
	long				lRet			=		-1;
	MC_VAR_isCli		*	pProcInfo		=		QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	switch  (  wParam  )  {
			case  CONST_qyWmParam_guiMsgArrive:  
				  doWnd_guiMsgArrive(  pProcInfo,  lParam,  this->m_hWnd,  TRUE,  m_var.pMsgBuf_doWnd_guiMsgArrive  );
				  break;
			default:
					break;
	}
	
//  errLabel:

	return  lRet;
#endif
	return dlgVideos_OnQyPostComm(m_hWnd, &m_var, wParam, lParam);
}

void CDlgVideos::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDlgDesktopsMon::OnActivate(nState, pWndOther, bMinimized);

	traceLogA(  "DlgVideos: OnActivate: nState %d",  nState  );
	
	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë
	if  (  m_var.ucbLocalAv  )  {
		if  (  nState  !=  WA_INACTIVE  )  {
			traceLogA(  "DlgVideos::OnActivate  ... "  );			
			//  
		}
	}
}

int  CDlgVideos::sizeAllControls(  RECT  rcParam  )
{
	int					iErr	=	-1;
	int					i;
	int					idc;
	QY_DMITEM		*	pItem;
	CWnd			*	pCtrl;
	CDlgDesktopsMon	*	pBase	=	this;
	int  iSubtype  =  this->getWndContentSubtype(  );

	//
	CDlgDesktopsMon::sizeAllControls(  rcParam  );

	//
	for  (  i  =  0;  i  <  pBase->m_var.usCnt_row  *  pBase->m_var.usCnt_col;  i  ++  )  {
		 pItem  =  &pBase->m_var.pIdcTable[i];
		 idc  =  (  int  )pItem->des;		
		 pCtrl  =  GetDlgItem(  idc  );
		 if  (  !pCtrl  )  goto  errLabel;
		 pCtrl->Invalidate(  TRUE  );
		 //  pCtrl->UpdateWindow(  );

		 if  (  m_var.ucbLocalAv  )  myGetImageInfo_2d(  TRUE,  m_var.ucbAutoClip,  m_var.images.mems[i].iW_org,  m_var.images.mems[i].iH_org,  0,  0,  pBase->m_var.mems_org[i].iW,  pBase->m_var.mems_org[i].iH,  (  unsigned  int  *  )&m_var.images.mems[i].iW_i,  (  unsigned  int  *  )&m_var.images.mems[i].iH_i,  &m_var.images.mems[i].iX_src_i,  &m_var.images.mems[i].iY_src_i,  &m_var.images.mems[i].iX_dst,  &m_var.images.mems[i].iY_dst,  &m_var.images.mems[i].iW_dst,  &m_var.images.mems[i].iH_dst  );
		 else  {
			   //  
			   RECT	rc;
			   ::GetClientRect(  pCtrl->m_hWnd,  &rc  );
			   int	iX,  iY,  iW,  iH;
			   iX  =  rc.left;
			   iY  =  rc.top;
			   iW  =  rc.right  -  rc.left;
			   iH  =  rc.bottom  -  rc.top;
			   //
			   PARAM_getCapImages  param_getCapImages  =  {0};
			   //			   				 
			   if  (   iSubtype  ==  CONST_dlgVideosSubtype_view  )  {				
				   param_getCapImages.bNew  =  TRUE;				 
			   }
			   param_getCapImages.bNew  =  TRUE;

			   //
			   getCapImages(  m_var.ucbAutoClip,  iX,  iY,  iW,  iH,  &param_getCapImages,  &m_var.images  );
			   //
			   static  int  n_0cnt  =  0;
			   //
			   if  (  !m_var.images.head.usCnt  )  {
				   n_0cnt  ++  ;
				   if  (  n_0cnt  <  1000  )  
				   {
					   PostMessage(  WM_SIZE  );
				   }
						   
			   }
			   else  n_0cnt  =  0;
			   //
			  
		 }


	}

	iErr  =  0;
errLabel:
	return  iErr;
}

//void CDlgVideos::OnSize(UINT nType, int cx, int cy)
//{
//	CDlgDesktopsMon::OnSize(nType, cx, cy);
//
//	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë
//	sizeAllControls_videos(  );
//
//  errLabel:
//	return;
//}



//void CDlgVideos::Onstopscrollbar()
//{
//	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
//	CDlgDesktopsMon::bEnableScrollBar(  FALSE  );
//
//	sizeAllControls(  );
//
//}

//void CDlgVideos::OnUpdatestopscrollbar(CCmdUI *pCmdUI)
//{
//	// TODO: ÔÚ´ËÌí¼ÓÃüÁî¸üÐÂÓÃ»§½çÃæ´¦Àí³ÌÐò´úÂë
//	CDlgDesktopsMon  *  pBase  =  this;
//	if  (  !pBase->m_var.bScrollBarEnabled  )  pCmdUI->Enable(  FALSE  );
//}


//void CDlgVideos::Onstartscrollbar()
//{
//	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
//	CDlgDesktopsMon::bEnableScrollBar(  TRUE  );
//	
//	sizeAllControls(  );
//
//}




//void CDlgVideos::OnUpdatestartscrollbar(CCmdUI *pCmdUI)
//{
//	// TODO: ÔÚ´ËÌí¼ÓÃüÁî¸üÐÂÓÃ»§½çÃæ´¦Àí³ÌÐò´úÂë
//	CDlgDesktopsMon  *  pBase  =  this;
//	if  (  pBase->m_var.bScrollBarEnabled  )  pCmdUI->Enable(  FALSE  );
//}

//


void CDlgVideos::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 
	//  traceLogA(  "OnTimer(  ) called"  );

#if 0
	//
	CDlgDesktopsMon  *  pBase  =  this;
	//int  idc  =  (  int  )m_var.idc;
	HWND  hCtrl = m_var.hCtrl;

	int  k;
	DWORD  dwTickCnt  =  GetTickCount(  );
	for  (  k  =  0;  k  <  mycountof(  m_var.images.mems  );  k  ++  )  {
		 CAP_IMAGE	*	pImg	=  &m_var.images.mems[k];
		 if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;
  						   

		 //  is active
		 if  (  dwTickCnt  -  pImg->dwTickCnt_lastDrawing  <  MAX_timeoutInS_dlgVideos  *  1000  )  continue;
		
		 //
		 //HWND  hCtrl  =  ::GetDlgItem(  m_hWnd,  idc  );
		 //	
		 //old_freeCapImageByTaskId(  this->m_hWnd,  (  int  )idc,  pImg->iTaskId,  &m_var.images,  hCtrl  );
		 freeCapImageByTaskId(this->m_hWnd, m_var.hCtrl, pImg->iTaskId, &m_var.images, hCtrl);
	}


#ifdef  __DEBUG__
		#if  1
			 OutputDebugString(  _T(  "TEST: no processPointEvent in timer"  )  );
			 return;
		#endif
#endif

#endif

	//
	dlgVideos_OnTimer(m_hWnd,m_var);

	//  Èç¹û×îºóµÄÊó±êÊÂ¼þÓÐÎ´·¢ËÍµÄ£¬ÔÚÕâÀï·¢ËÍ³öÈ¥
	if  (  m_var.bRemoteAssist  )  {
		if  (  m_var.bNeedSend_lastMouseEvent  )  {
			processPointerEvent(  m_var.lastMouseEvent.x,  m_var.lastMouseEvent.y,  m_var.lastMouseEvent.nFlags,  m_var.lastMouseEvent.bMouseMove,  TRUE  );
		}
	}



	CDlgDesktopsMon::OnTimer(nIDEvent);
}


 //  Òª×¼±¸°ÑÕâ¸öÊó±êÒÆ¶¯µÄÏûÏ¢·¢ËÍµ½¶Ô·½È¥¡£
 int  CDlgVideos::processPointerEvent(  int  x,  int  y,  UINT nFlags,  BOOL  bMouseMove,  BOOL  bSendForce  )
{
		int						iErr			=	-1;
		if  (  !m_var.pMisCnt  )  return  -1;
		MC_VAR_isCli		*		pProcInfo		=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
		if  (  !pProcInfo  )  return  -1;
		FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
		if  (  !pFuncs  )  return  -1;
		CDlgDesktopsMon	*		pBase			=	this;

		if  (  !m_var.bRemoteAssist  ||  m_var.images.head.usCnt  !=  1  )  return  -1;

		//  if (  ::GetFocus() != m_hWnd) return 0;

		MACRO_prepareForTran(  )
		unsigned  int			uiChannelType	=	CONST_channelType_rtOp;	//  2016/12/26	//  CONST_channelType_media;
		MIS_CHANNEL			*	pChannel		=	NULL;
		if  (  !(  pChannel  =  getChannelByType(  m_var.pMisCnt,  uiChannelType  )  )  )  goto  errLabel;

		REMOTE_ASSIST_REQ		req;
		int						mask;
 		CAP_IMAGE			*	pImg			=	&m_var.images.mems[0];
		if  (  !pImg->iW_org  ||  !pImg->iH_org  )  goto  errLabel;

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
		req.uiTranNo_openAvDev  =  m_var.uiTranNo_openAvDev;
		req.u.usRaType  =  CONST_usRaType_pointerEvent;
		req.u.pointerEvent.ucButtonMask  =  mask;
		req.u.pointerEvent.x  =  (  unsigned  short  )(  x  +  pBase->m_var.m_nScrollPos_h  );  
		req.u.pointerEvent.y  =  (  unsigned  short  )(  y  +  pBase->m_var.m_nScrollPos_v  );  
		//  È·±£ÔÚ²¶»ñ·¶Î§ÄÚ
		if  (  req.u.pointerEvent.x  <  pBase->m_var.layoutParam.iEdge_l  ||  req.u.pointerEvent.y  <  pBase->m_var.layoutParam.iEdge_t  )  goto  errLabel;
		//  È¥µô±ß½ç²¿·Ö     
		req.u.pointerEvent.x  -=  pBase->m_var.layoutParam.iEdge_l;
		req.u.pointerEvent.y  -=  pBase->m_var.layoutParam.iEdge_t;


		//  1¡£Î´Íê³É¡£Êó±ê¹ý¿ì£¬Òª´ÓÍ¼Ïñ´ø»Ø¸ö±êÊ¶µ±ÏìÓ¦¡£
		//  2¡£ÓÐºÃ¼¸¸öµØ·½ÊÇÍ¨¹ý¶ÔmediaQµÄwarningInterval½øÐÐÏÞËÙ£¬ÕâÊµ¼ÊºÜ¶àÊÇ´íµÄ¡£Ó¦¸Ã¶ÔtoSendQ ½øÐÐÅÐ¶Ï¡£×¢Òâ¡£¡£¡£¡£


		//  ½«ÊÂ¼þ¼ÇÂ¼ÏÂÀ´¡£Èç¹ûÃ»·¢ËÍ³öÈ¥£¬¿ÉÒÔÔÚOnTimerÀï·¢ËÍ
		m_var.lastMouseEvent.x  =  x;
		m_var.lastMouseEvent.y  =  y;
		m_var.lastMouseEvent.nFlags  =  nFlags;
		m_var.lastMouseEvent.bMouseMove  =  bMouseMove;
		//
		m_var.bNeedSend_lastMouseEvent  =  TRUE;

		//  ÕâÀïÒª¸ÄÎª´ÓmousemoveÀï°ÑdwTickCnt´øÉÏ£¬ÓÐ±»Ð­Öú¶Ë°Ñ´ËÖµ´ÓÍ¼ÏñÀú´ø»Ø¡£È»ºó£¬¼ÌÐø·¢ËÍmousemove¡£ÆäËû°ü²»ÏÞ
		if  (  !bSendForce  &&  bMouseMove  )  {
#if  0  //  2016/12/26. 引入rtOp后，不再使用忽略某些包的方法以降低复杂。
			if  (  m_var.uiEventId_lastRecvd  !=  m_var.dwTickCnt_sendLastMouseMove  )  {		//  ±íÃ÷ÏìÓ¦Î´ÊÕµ½
				traceLogA(  "mouseMove is skipped."  );
				goto  errLabel;
			}		
			#ifdef  __DEBUG__
					traceLog(  _T(  "mouseMove: uiEventId_lastRecvd matched"  )  );
			#endif
#endif
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
							   pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  i  );  //  &pProcInfo->misCnts[i];
							   if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;

							   //  traceLogA(  "toShareBmp: applyForChkChannels"  );
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgVideo.processPointerEvent: rtOp Channel not Ready, applyForChkChannels"  )  );

							   //
							   memset(  &msg_applyForChkChannels,  0,  sizeof(  msg_applyForChkChannels  )  );
							   msg_applyForChkChannels.uiType  =  CONST_misMsgType_applyForChkChannels_qmc;
							   msg_applyForChkChannels.pMisCnt  =  pMisCnt;
							   //
							   if  (  q2PostMsgAndTrigger(  &msg_applyForChkChannels,  sizeof(  msg_applyForChkChannels  ),  &pProcInfo->rtOpQ2,  _T(  "dlgVideos.processPointerEvent"  ))) {
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
				m_var.dwTickCnt_sendLastMouseMove  =  GetTickCount(  );
				//  2016/12/26
				//req.u.pointerEvent.uiEventId  =  m_var.dwTickCnt_sendLastMouseMove;
				//
				traceLogA(  "mouseMove sending."  );
			}

			//
			m_var.bNeedSend_lastMouseEvent  =  FALSE;

			if  (  postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_outputTask,  0,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  (  char  *  )&req,  sizeof(  req  ),  0,  &m_var.idInfo_sender,  uiChannelType,  NULL,  FALSE  )  )  traceLogA(  "postMsg2Mgr_mc failed"  );
		}

		iErr  =  0;

errLabel:
		return  iErr;
}


//
void CDlgVideos::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//  traceLogA(  "LButtonDblClk, nFlags %d",  nFlags  );

	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	processPointerEvent(  point.x,  point.y,  nFlags  );
	
	//
	if  (  m_var.bRemoteAssist  )  return;


	//  2018/07/07
	if  (  m_var.bEnlargeFromDynBmps  )  {
		::PostMessage(  m_hWnd,  WM_CLOSE,  0,  0  );
		return;
	}

	//
	::PostMessage(  m_hWnd,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );


	CDlgDesktopsMon::OnLButtonDblClk(nFlags, point);
}


//
void CDlgVideos::OnLButtonDown(UINT nFlags, CPoint point)
{
	//  traceLogA(  "LButtonDown, nFlags %d",  nFlags  );

	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnLButtonDown(nFlags, point);
}


//
void CDlgVideos::OnLButtonUp(UINT nFlags, CPoint point)
{
	//  traceLogA(  "LButtonUp,  nFlags %d",  nFlags  );

	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnLButtonUp(nFlags, point);
}


void CDlgVideos::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnMButtonDblClk(nFlags, point);
}


void CDlgVideos::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnMButtonDown(nFlags, point);
}

void CDlgVideos::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnMButtonUp(nFlags, point);
}

void CDlgVideos::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnRButtonDblClk(nFlags, point);
}


void CDlgVideos::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnRButtonDown(nFlags, point);
}

void CDlgVideos::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnRButtonUp(nFlags, point);
}


 void  CDlgVideos::OnMouseMove(UINT nFlags, CPoint point)
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	//  2010/08/30
	if  (  m_var.bInstantAssistant  )  {
		POINT	tmpPoint;
		tmpPoint.x  =  point.x;
		tmpPoint.y  =  point.y;
		::MapWindowPoints(  this->m_hWnd,  NULL,  &tmpPoint,  1  );
		viewInstantAssistant(  this->m_hWnd,  0,  tmpPoint.x,  tmpPoint.y,  m_var.hDlgTalk,  FALSE  );
	}

	//
	if  (  m_var.bMediaControl  )  {
		viewMediaControl(  this->m_hWnd,  m_var.iIndex_capAudio,  m_var.iIndex_capBmp,  &m_var.hWnd_mediaControl  );		
	}

	// TODO: 
	processPointerEvent(  point.x,  point.y,  nFlags,  TRUE  );

//  errLabel:
	
	CDlgDesktopsMon::OnMouseMove(nFlags, point);
}


BOOL CDlgVideos::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ

	return CDlgDesktopsMon::OnMouseWheel(nFlags, zDelta, pt);
}



/*
#define		CONST_VK_dead_grave       0xFE50
#define		CONST_VK_dead_acute       0xFE51
#define		CONST_VK_dead_circumflex  0xFE52
#define		CONST_VK_dead_tilde       0xFE53
*/


 KEY_2_SEND  vk2Send(  UINT  virtkey,  DWORD  keyData  ) 
{ 
	UINT numkeys = 0;
    
	BYTE keystate[256];
	unsigned char buf[4]; // lots of space for now

    KEY_2_SEND		kas;
    kas.releaseModifiers  =  0;

    bool extended = ((keyData & 0x1000000) != 0);
    
    if  (  extended  )  { 
        switch  (  virtkey  )  {
		        case  VK_MENU :
					  virtkey  =  VK_RMENU;  
					  break;
				case  VK_CONTROL:
					  virtkey  =  VK_RCONTROL; 
					  break;  
				case  VK_RETURN:
            		  //  virtkey = VK_KEYPAD_ENTER; 
					  break;
				default:
						break;
        }
    }
    
    // We try looking it up in our table
	QY_DMITEM	*	pItem;
        
    // Look up the desired code in the table
    for  (  pItem  =  CONST_qyKeyTable; pItem->type  !=  -1; pItem  ++  )  {
		 if  (  pItem->type  ==  virtkey  ) {
            kas.keycodes[numkeys  ++  ]  =  (  unsigned  int  )pItem->des;
            break;
        }
    }
    

    if  (  numkeys  !=  0  ) {
        UINT key = kas.keycodes[numkeys-1];
		traceLogA(  "keymap gives %u (%x) ", key, key);
	    } 
	else {
         // not found in table
		
         // we try a simple conversion to Ascii, using the current keyboard mapping
		 ::myGetKeyboardState(keystate);
   	
		 int ret = ::myToAscii(virtkey, 0, keystate, (WORD *) buf, 0);

		 // If Left Ctrl & Alt both pressed and ToAscii gives a valid keysym
		 // This is for AltGr on international keyboards  (= LCtrl-Alt).
		 // e.g. Ctrl-Alt-Q gives @ on German keyboards
		 if  (  ((keystate[VK_MENU] & 0x80) != 0) &&
            ((keystate[VK_CONTROL] & 0x80) != 0) ) 
		 {

           // If the key means anything in this keyboard layout
           if  ( (ret >= 1) && 
                 ( ( (*buf >= 32) && (*buf <= 126) ) ||
                   ( (*buf >= 160) && (*buf <= 255) ) ) 
                ) 
		   {
               // Send the modifiers up, then the keystroke, then mods down
               // We don't release the right control; this allows German users
               // to use it for doing Ctl-@ etc. (though not under Win95 --
               // see below)

               if (GetKeyState(VK_LCONTROL) & 0x8000) kas.releaseModifiers |= CONST_KEYMAP_LCONTROL;
               if (GetKeyState(VK_LMENU)    & 0x8000) kas.releaseModifiers |= CONST_KEYMAP_LALT;
               if (GetKeyState(VK_RMENU)    & 0x8000) kas.releaseModifiers |= CONST_KEYMAP_RALT;

               // This is for windows 95, and possibly other systems.  
               // The above GetKeyState calls don't work in 95 - they always return 0.
               // But if we're here at all we know that control and alt are pressed, so let's
               // raise all Control and Alt keys if we haven't registered any yet.
               if  (  kas.releaseModifiers  ==  0  )
                   kas.releaseModifiers  =  CONST_KEYMAP_LCONTROL | CONST_KEYMAP_LALT | CONST_KEYMAP_RALT;

			   for  (  int  i  =  0;  i  <  ret;  i  ++  ) {
                    kas.keycodes[numkeys++]  =  *(buf+i);
                    //  log.Print(8, _T("%02x (%c) "), *(buf+i) , *(buf+i));
                }                
           } 
        } 
        
        // If not a ctrl-alt key
        if  (  numkeys  ==  0  ) {

            // There are no keysyms corresponding to control characters 
            // Eg Ctrl F.  The server already knows whether the control 
            // key is pressed. So we are interested in the key that would be 
            // there if the Ctrl were not pressed.
            keystate[VK_CONTROL] = keystate[VK_LCONTROL] = keystate[VK_RCONTROL] = 0;

		    int ret = ::myToAscii(virtkey, 0, keystate, (WORD *) buf, 0);
            if (ret < 0) {
				/*
                switch (*buf) {
				case '`' :
					kas.keycodes[numkeys++] = XK_dead_grave; break;
				case '\'' :
					kas.keycodes[numkeys++] = XK_dead_acute; break;
				case '~' :
					kas.keycodes[numkeys++] = XK_dead_tilde; break;
				case '^':
					kas.keycodes[numkeys++] = XK_dead_circumflex; break;
				}
				*/
				traceLogA(  "vk2Send: ÕâÀïÓöµ½ÁËToAscii·µ»Ø %d, Îªdead key, ¿´ÓÐÃ»ÓÐÓ°Ïì",  ret  );
            }
            // if this works, and it's a regular printable character, we just send that
            if (ret >= 1) {
                //  log.Print(8,_T("ToAscii (without ctrl) returns %d byte(s): "), ret);
                for (int i = 0; i < ret; i++) {
                   kas.keycodes[numkeys++] = *(buf+i);
                   //  log.Print(8, _T("%02x (%c) "), *(buf+i) , *(buf+i));
                }
            }
        }

    }

    kas.keycodes[numkeys] = CONST_voidKeyCode;
	return  kas;
};


//
 int  CDlgVideos::sendKeyEvent(  unsigned  int  nChar, unsigned  char  ucbDown  ) 
{
	int						iErr			=	-1;
	MC_VAR_isCli			*	pProcInfo		=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	MACRO_prepareForTran(  )
	unsigned  int			uiChannelType	=	CONST_channelType_media;
	REMOTE_ASSIST_REQ		req;

	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_remoteAssistReq;
	req.uiTranNo_openAvDev  =  m_var.uiTranNo_openAvDev;
	req.u.usRaType  =  CONST_usRaType_keyEvent;
	req.u.keyEvent.ucbDown  =  ucbDown;
	req.u.keyEvent.key  =  nChar;

	if  (  postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_outputTask,  0,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  (  char  *  )&req,  sizeof(  req  ),  0,  &m_var.idInfo_sender,  uiChannelType,  NULL,  0  )  )  traceLogA(  "postMsg2Mgr_mc failed"  );

	iErr  =  0;
//  errLabel:
	return  iErr;

}


 int  CDlgVideos::processKeyEvent(  UINT  nChar, DWORD  keyData  )
{
	int					iErr		=	-1;
	MC_VAR_isCli		*	pProcInfo	=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	unsigned  char		ucbDown		=  (  (  keyData  &  0x80000000l  )  ==  0  );


	if  (  !m_var.bRemoteAssist  ||  m_var.images.head.usCnt  !=  1  )  return  -1;

	CAP_IMAGE			*	pImg			=	&m_var.images.mems[0];
	if  (  !pImg->iW_org  ||  !pImg->iH_org  )  goto  errLabel;

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




 int  CDlgVideos::resetKeyEvent(  )
{
	if  (  !m_var.bRemoteAssist  ||  m_var.images.head.usCnt  !=  1  )  return  -1;


	traceLogA(  "Losing focus - cancelling modifiers"  );
	
	sendKeyEvent(  CONST_qK_MENU,		false  );
	sendKeyEvent(  CONST_qK_CONTROL,	false  );
	sendKeyEvent(  CONST_qK_SHIFT,		false  );

	sendKeyEvent(  CONST_qK_LMENU,		false);
	sendKeyEvent(  CONST_qK_LCONTROL,	false);
	sendKeyEvent(  CONST_qK_LSHIFT,		false);
	sendKeyEvent(  CONST_qK_RMENU,		false);
	sendKeyEvent(  CONST_qK_RCONTROL,	false);
	sendKeyEvent(  CONST_qK_RSHIFT,		false);
	

	return  0;
}


 /*
 int  CDlgVideos::getCapImageInfo(  QY_WMBUF_COMM  *  pComm  )
{
	return  0;
}
*/


 /*
 int  CDlgVideos::chkTask(  QY_WMBUF_COMM  *  pComm  )
{
	return  0;
}
*/



BOOL CDlgVideos::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

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
			default:
					break;
	}


	return CDlgDesktopsMon::PreTranslateMessage(pMsg);
}


void CDlgVideos::OnCancel()
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	if  (  m_var.bClosed  )  {				//  200/11/17. Ê¹ÓÃÕâ¸ö±êÖ¾Î»ÊÇÎªÁË·ÀÖ¹ÓÃescapeÍË³ö¡£ÒòÎªÔÚÔ¶³ÌÐ­ÖúµÄÇé¿öÏÂ£¬escapeÐèÒªËÍµ½¶Ô·½µÄ´°¿ÚÈ¥
        CDlgDesktopsMon::OnCancel();
		}
	else  if  (  !m_var.bRemoteAssist  &&  !m_var.bInstantAssistant  )  {	//  2012/07/06. ÔÚÃ»ÓÐ¸¡¶¯²Ëµ¥ºÍ²»ÊÇÔ¶³ÌÐ­ÖúÊ±,¶¼ÐèÒªÁ¢¼´¹Ø±Õ´°¿Ú.
			   CDlgDesktopsMon::OnCancel();
	}
}

void CDlgVideos::OnClose()
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	m_var.bClosed  =  TRUE;

	//  Í¨Öª½áÊø´ËÈÎÎñ
	if  (  m_var.bRemoteAssist  &&  m_var.hDlgTalk  &&  m_var.iTaskId  )  {
		/*QY_WMBUF_COMM		wmBuf;

		traceLogA(  "CDlgVideos::OnDestroy. ÓÃÀ´ÏòdlgTalk·¢ÆðSendMessage Ñ¯ÎÊ£¬ÀûÓÃiTaskIdÀ´¹Ø±Õ´ËÈÎÎñ¡£"  );

		memset(  &wmBuf.u.getCapImageInfo,  0,  sizeof(  wmBuf.u.getCapImageInfo  )  );
		wmBuf.uiType  =  CONST_qyWmParam_getCapImageInfo;
		wmBuf.u.getCapImageInfo.iTaskId  =  m_var.iTaskId;
		wmBuf.u.getCapImageInfo.bStopRemoteAssist  =  TRUE;
		if  (  ::SendMessage(  m_var.hDlgTalk,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  )  !=  CONST_qyWmRc_ok  )  {
			traceLogA(  "CDlgVideos::OnDestroy(  ): SendMessage failed."  );
		}
		*/
		MIS_MSG_notifyTaskEnd_qmc	msg;
		memset(  &msg,  0,  sizeof(  msg  )  );
		msg.uiType  =  CONST_misMsgType_notifyTaskEnd_qmc;
		msg.iTaskId  =  m_var.iTaskId;
		msg.bToCancel  =  TRUE;
		if  (  ::SendMessage(  m_var.hDlgTalk,  CONST_qyWm_comm,  0,  (  LPARAM  )&msg  )  !=  CONST_qyWmRc_ok  )  {
			traceLogA(  "CDlgVideos::OnDestroy(  ): SendMessage failed."  );
		}		
	}

	CDlgDesktopsMon::OnClose();
}

HBRUSH CDlgVideos::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDlgDesktopsMon::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	CDlgDesktopsMon  *  pBase  =  this;
	if  (  pBase->m_var.m_bFullScreen
		||  pBase->m_var.ucbBkBlack  )  
	{
		switch  (  nCtlColor  )  {
			case  CTLCOLOR_DLG:
			case  CTLCOLOR_STATIC:
				  return  (  HBRUSH  )GetStockObject(  BLACK_BRUSH  );
				  break;
			default:
					break;
		}		
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
