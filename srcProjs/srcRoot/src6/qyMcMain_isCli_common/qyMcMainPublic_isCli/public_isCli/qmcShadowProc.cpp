


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

void  TALKER_shadow_free(  BOOL  bMgr,  void  *  pShadowInfo  )
{
	if  (  !pShadowInfo  )  return;

	if  (  bMgr  )  {
		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pShadowInfo;
		int  i;
		for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
			 TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
			 //  MACRO_safeFree(  pMem->pZoneParams  );
		}		
	}

	myfree(  pShadowInfo  );
}

void  *  TALKER_shadow_new(  BOOL  bMgr  )
{
	int					iErr			=	-1;
	void			*	pShadowInfo		=	NULL;
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	int					iSize;

	if  (  bMgr  )  {
		iSize  =  sizeof(  TALKER_shadow_mgr  );
		pShadowInfo  =  mymalloc(  iSize  );
		if  (  !pShadowInfo  )  goto  errLabel;
		memset(  pShadowInfo,  0,  iSize);
		//
		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pShadowInfo;
		int  i;
		for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
			 TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
#if  0
			 pMem->usCnt_zoneParams  =  pProcInfo->av.usCnt_players;
			 if  (  !pMem->usCnt_zoneParams  )  goto  errLabel;
			 iSize  =  pMem->usCnt_zoneParams  *  sizeof(  ZONE_PARAM  );
			 pMem->pZoneParams  =  (  ZONE_PARAM  *  )mymalloc(  iSize  );
			 if  (  !pMem->pZoneParams  )  goto  errLabel;
			 memset(  pMem->pZoneParams,  0,  iSize  );
#endif
		}
	    }
	else  {
		iSize  =  sizeof(  TALKER_shadow  );
		pShadowInfo  =  mymalloc(  iSize  );
		if  (  !pShadowInfo  )  goto  errLabel;
		memset(  pShadowInfo,  0,  iSize);
		  
	}

	iErr	=	0;

errLabel:
	if  (  iErr  )  {
		if  (  pShadowInfo  )  TALKER_shadow_free(  bMgr,  pShadowInfo  );
	}
	return  iErr  ?  NULL  :  pShadowInfo;

}




	//  2013/03/02
  int  dlgTalk_freeCapImageByTaskId_me_mgr(  HWND    hDlgTalk,  int  idc,  int  iTaskId  )
{
	int					iErr		=	-1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	DLG_TALK_var	*	pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  hDlgTalk,  _T(  "freeCapImageByTaskId_mgr"  )  );
	if  (  !pMgrVar  )  goto  errLabel;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;

	if  (  idc  !=  pMgrVar->guiData.iIDC_STATIC_meDesc  )  goto  errLabel;
	int  idc_dst  =  idc;


	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		 TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
		 if  (  pShadowMgr->shadows[i].hShadow  )  {			 
			 CHelp_getDlgTalkVar	help_getDlgTalkVar;	
			 DLG_TALK_var	*	pVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  pMem->hShadow,  _T(  "freeCapImageByTaskId_me_mgr"  )  );
			 if  (  !pVar  )  continue;	
			 CAP_IMAGES  *  tmp_pImgs  =  &pVar->av.meZone.images;
			 old_freeCapImageByTaskId(  pShadowMgr->shadows[i].hShadow,  idc,  iTaskId,  tmp_pImgs,  old_M_GetDlgItem(  pShadowMgr->shadows[i].hShadow,  idc_dst  )  );
		 }
	}
 
	CAP_IMAGES  *  pImgs  =  &pMgrVar->av.meZone.images;
	old_freeCapImageByTaskId(  hDlgTalk,  idc,  iTaskId,  pImgs,  old_M_GetDlgItem(  hDlgTalk,  idc  )  );

	iErr  =   0;

errLabel:
	return  iErr;

}



    //  2014/10/09
 int  dlgTalk_freeCapImages_bgWall_mgr(  HWND    hDlgTalk,  int  idc  )
 {	 
	int					iErr		=	-1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	DLG_TALK_var	*	pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  hDlgTalk,  _T(  "freeCapImages_bg_mgr"  )  );
	if  (  !pMgrVar  )  goto  errLabel;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;

	if  (  idc  !=  pMgrVar->guiData.iIDC_STATIC_bgWall_conf  )  goto  errLabel;

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
			 int  j;
			 for  (  j  =  0;  j  <  mycountof(  pVar->av.bgWall.mems  );  j  ++  )  {
				 CAP_IMAGES  *  tmp_pImgs  =  &pVar->av.bgWall.mems[j].images;
				 old_freeCapImages(  pMem->hShadow,  idc,  tmp_pImgs,  old_M_GetDlgItem(  pShadowMgr->shadows[i].hShadow,  idc  ),  &pVar->av.hDc_bgWall_conf,  _T(  "dlgTalk_freeCapImages_bgWall_mgr.198"  ));
			 }
		 }
	}
 
	int  j;
	for  (  j  =  0;  j  <  mycountof(  pMgrVar->av.bgWall.mems  );  j  ++  )  {
		 CAP_IMAGES  *  pImgs  =  &pMgrVar->av.bgWall.mems[j].images;
		 old_freeCapImages(  hDlgTalk,  idc,  pImgs,  old_M_GetDlgItem(  hDlgTalk,  idc  ),  &pMgrVar->av.hDc_bgWall_conf,  _T(  "dlgTalk_freeCapImages_bgWall_mgr.206"  ));
	}

	iErr  =   0;

errLabel:
	return  iErr;

}
 



  //
  void  chooseAvDevice_mgr(  void  *  pCapParam,  HWND  hDlgTalk,  HWND  hWndStatus,  int  iMenuId  )
{
	int					iErr		=	-1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pMgrVar  )  goto  errLabel;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;


	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		 if  (  pShadowMgr->shadows[i].hShadow  )  {  
			 chooseAvDevice_shadow(  pMgrVar->pCapStuff,  pMgrVar->bIncludeACap,  pShadowMgr->shadows[i].hShadow,  NULL,  iMenuId  );
		 }
	}
    
	chooseAvDevice(  pMgrVar->pCapStuff,  pMgrVar->bIncludeACap,  hDlgTalk,  NULL,  iMenuId  );

	iErr  =   0;

errLabel:
	return;
}


 BOOL  InvalidateRect_mgr(  HWND hDlgTalk, int  idc,  CONST RECT *lpRect, BOOL bErase  )
{
	BOOL	bRet	=	FALSE;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pMgrVar  )  goto  errLabel;

	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;
	int  i;
	HWND  hWnd_dst  =  NULL;

	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		if  (  !pShadowMgr->shadows[i].hShadow  )  continue;
		hWnd_dst  =  old_M_GetDlgItem(  pShadowMgr->shadows[i].hShadow,  idc  );
		if  (  hWnd_dst  )  {
			InvalidateRect(  hWnd_dst,  lpRect,  bErase  );
		}
	}
	hWnd_dst  =  old_M_GetDlgItem(  hDlgTalk,  idc  );
	if  (  hWnd_dst  )  {
		InvalidateRect(  hWnd_dst,  lpRect,  bErase  );
	}

	bRet  =  TRUE;

errLabel:
	return  bRet;
	 
}


 //
__declspec(  dllexport  )  int  closeInstantAssistant_mgr(  HWND  hDlgTalk  )
{
	int					iErr		=	-1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk,  _T(  "dlgTalk_freeCapImgBySth_mgr"  )  );
	if  (  !pMgrVar  )  goto  errLabel;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;


	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		 if  (  pShadowMgr->shadows[i].hShadow  )  {
			 closeInstantAssistant(  pShadowMgr->shadows[i].hShadow  );
		 }
	}
  
	closeInstantAssistant(  hDlgTalk  );

	iErr  =   0;

errLabel:
	return  iErr;
}


					



