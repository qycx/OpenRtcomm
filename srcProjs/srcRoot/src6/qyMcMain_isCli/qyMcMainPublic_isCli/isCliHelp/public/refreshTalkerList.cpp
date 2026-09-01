
#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	<time.h>
#include	<stddef.h>

#include	"qymcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"

#ifdef  __SUPPORT_HTMLEDIT__
	//  #include	"myHtmlEditCtrl.h"
#endif

#include	"tmpCeLib.h"
#include	"qyWnd.h"

#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"
#ifndef  __WINCE__
//		 #include	"DlgVideos.h"
		 //  #include	"DlgCfgVideoConference.h"
		 //  #include	"DlgPolicyIsClient.h"
		 //  #include	"DlgInstantAssistant.h"
#endif
#include	<assert.h>
#ifndef  __WINCE__
	//  #include	"qyPs.h"
#endif
#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
#include	"qmcConferenceWall.h"
//  #include	"dlgProgress.h"
#endif
#include	"qmcCmdProc.h"

#include	"policyAvParams.h"

#ifndef  __WINCE__
		 //  #include	"qyStatic.h"
#endif
#include	"dlgTalkProc.h"
#include	"qmcSharePublic.h"

#if  1  //  def  __APP_qyMc_touchscreen__
		#include	"DlgWalls.h"
#endif

#include	"gpsCommProc.h"
#include	"qmcGpsProc.h"


#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"

#include	"sp.h"
#include	"isCliHelpPublic.h"




//
__declspec(  dllexport  )  int  resetTalkerList_mgr(  HWND  hDlgTalk_mgr  )
{
	int  iErr   =  -1;
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	HWND  hMgr  =  hDlgTalk_mgr;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hDlgTalk_mgr  );
	if  (  !pMgrVar  )  return  -1;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  -1;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;

		//
	int  i;
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
		if  (  !IsWindow(  pMem->hShadow  )  )  continue;
		//
		{
			CHelp_getDlgTalkVar  help;
			DLG_TALK_var  *  pVar  =  (  DLG_TALK_var  *  )help.getVar(  pMem->hShadow  );
			if  (  !pVar  )  continue;
			//
			myListCtrl_DeleteAllItems(  GetDlgItem(  pMem->hShadow,  pVar->guiData.iIDC_talkerList  )  );
			//
			memset(  &pVar->av.videoConferenceStatus,  0,  sizeof(  pVar->av.videoConferenceStatus  )  );

			//
			if  (  pVar->guiData.ucbShowImGrpMems  )  {
				SetDlgItemText(  pMem->hShadow,  pVar->guiData.iIDC_EDIT_filter,  _T(  ""  )  );
				dlgTalk_loadGrpMems(  pMem->hShadow,  pVar,  _T(  ""  )  );
			}
		}
	}
	myListCtrl_DeleteAllItems(  GetDlgItem(  hMgr,  pMgrVar->guiData.iIDC_talkerList  )  );
	memset(  &pMgrVar->av.videoConferenceStatus,  0,  sizeof(  pMgrVar->av.videoConferenceStatus  )  );

	//
	if  (  pMgrVar->guiData.ucbShowImGrpMems  )  {
		SetDlgItemText(  hMgr,  pMgrVar->guiData.iIDC_EDIT_filter,  _T(  ""  )  );
		dlgTalk_loadGrpMems(  hMgr,  pMgrVar,  _T(  ""  )  );
	}


	iErr  =  0;
errLabel:
	return  iErr;
}

 //
 int  fillTalkerList_func_mgr(  HWND  hDlgTalk_mgr,  HWND  hTool,  void  *  pVIDEO_CONFERENCE_STATUS,  int  idcList  )
 {
 
	BOOL	bRet	=	FALSE;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk_mgr  );
	if  (  !pMgrVar  )  goto  errLabel;

	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;
	int  i;
	HWND  hWnd_dst  =  NULL;

	//
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		 TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
		 if  (  pMem->hShadow  )  {			 
			 CHelp_getDlgTalkVar	help_getDlgTalkVar;	
			 DLG_TALK_var	*	pVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  pMem->hShadow,  _T(  "freeCapImages"  )  );
			 if  (  !pVar  )  continue;	
			 //
			 fillTalkerList_func(  pMem->hShadow,  pMem->hShadow,  &pVar->av.videoConferenceStatus,  pVar->guiData.iIDC_talkerList  );  
		 }
	}

	//
	fillTalkerList_func(  hDlgTalk_mgr,  hDlgTalk_mgr,  &pMgrVar->av.videoConferenceStatus,  pMgrVar->guiData.iIDC_talkerList  );  


	bRet  =  TRUE;

errLabel:
	return  bRet;
	 
}
 
 
 //
 __declspec(  dllexport  )  int  refreshTalkerList(  HWND  hDlgTalk  )
 {

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pVar  )  return  -1;

	 DLG_TALK_var  &m_var  =  *(  DLG_TALK_var  *  )pVar;
 
	 //  trigger the instantAssistant to refresh
								
	 if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
		 SendMessage(  m_var.hWnd_instantAssistant,  CONST_qyWm_comm,  0,  0  );	
		 }
	 else  {
		   DLG_TALK_var  *  pMgrVar  = &m_var;

		   TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
		   if  (  !pShadowMgr  )  goto  errLabel;
		    
		    int  i;
		   	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
				TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
				if  (  pMem->hShadow  )  {			 
					CHelp_getDlgTalkVar	help_getDlgTalkVar;	
					DLG_TALK_var	*	pVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  pMem->hShadow,  _T(  "freeCapImages"  )  );
					if  (  !pVar  )  continue;	
					//

					SendMessage(  pVar->hWnd_instantAssistant,  CONST_qyWm_comm,  0,  0  );	
				}
			}
	 }

	 //  2017/06/25												
	 //SendMessage(  m_var.confMgr.hWnd_confMgr,  CONST_qyWm_comm,  0,  0  );													
	 //fillTalkerList_func_mgr(  hDlgTalk,  hDlgTalk,  &m_var.av.videoConferenceStatus,  m_var.guiData.iIDC_talkerList  );

errLabel:

	 return  0;
 }

