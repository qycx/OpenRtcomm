
#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	<time.h>
#include	<stddef.h>
#include	<ShellAPI.h>

#include	"qymcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"


#include	"tmpCeLib.h"
#include	"qyWnd.h"

#include	"qyRtcCommProc.h"
#ifndef  __WINCE__
#include	"dlgVideosProc.h"
#endif
#include	<assert.h>
#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
#include	"qmcConferenceWall.h"
#include	"isCliHelpPublic.h"
#endif
#include	"qmcCmdProc.h"

#include	"policyAvParams.h"

#include	"dlgTalkProc.h"
#include	"qmcSharePublic.h"

#include	"DlgWalls.h"

#include	"gpsCommProc.h"
#include	"qmcGpsProc.h"

#include	"qyCusResTemp.h"

#include	"qmcVWall.h"
#include	"dlgDesktopsMonProc.h"

#include	"sp.h"
#include	"myDb.h"
#include	"isCliHelpPublic.h"

#include	"imgProcessPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"dlgMsgToolProc.h"
#include	"qmcVideoCapture_rtsp.h"
#include	"qmcDynBmp.h"

#include	"qyCusResTemp.h"
#include	"dlgShareDynBmpsProc.h"
#include	"isCliD3dPublic.h"
#include	"policyIsClientFunc.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliExPublic.h"
#include	"isCliCorePublic.h"
#include	"guiShare.h"


//
__declspec(  dllexport  )  int  dlgTalk_freeCapImageBySth(  HWND  hDlgTalk,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo  )
{
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pm_var	=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk,  _T(  "dlgTalk_freeCapImageBySth"  )  );
	if  (  !pm_var  )  return  -1;
	DLG_TALK_var	&	m_var	=	*pm_var;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	CTX_qm_thread  *  pCqt  =  &pQyMc->gui.ctx_gui_thread;
	//
	int					idc		=	0;
	int					idc_dst	=	0;
	CAP_IMAGES	*	pImgs  =  NULL;

	idc  =  m_var.av.idc_peer;
	pImgs  =  &m_var.av.peerZone.images;	//.peerImages;
	idc_dst  =  0;	//  idc;
	old_freeCapImageBySth(  pCqt,  hDlgTalk,  idc,  iTaskId,  pIdInfo,  pImgs,  old_M_GetDlgItem(  hDlgTalk,  idc_dst  )  );
	//  2012/05/04
	idc  =  m_var.av.idc_me;
	pImgs  =  &m_var.av.meZone.images;		//  .meImages;
	idc_dst  =  idc;
	old_freeCapImageBySth(  pCqt,  hDlgTalk,  idc,  iTaskId,  pIdInfo,  pImgs,  old_M_GetDlgItem(  hDlgTalk,  idc_dst  )  );
	//  2013/02/27
	idc  =  m_var.av.idc_other;
	pImgs  =  &m_var.av.otherZone.images;	//  .otherImages;
	idc_dst  =  idc;
	old_freeCapImageBySth(  pCqt,  hDlgTalk,  idc,  iTaskId,  pIdInfo,  pImgs,  old_M_GetDlgItem(  hDlgTalk,  idc_dst  )  );

	//idc = m_var.av.idc_other;
	pImgs = &m_var.av.remoteVideoZone.images;	//  .otherImages;
	//idc_dst = idc;
	freeCapImageBySth(pCqt, hDlgTalk, m_var.av.hCtrl_RemoteVideo, iTaskId, pIdInfo, pImgs, m_var.av.hCtrl_RemoteVideo ? m_var.av.hCtrl_RemoteVideo : hDlgTalk/*old_M_GetDlgItem(hDlgTalk, idc_dst)*/);
	//  2014/11/30
#if  0
	idc  =  m_var.av.idc_bgWall;
	pImgs  =  &m_var.av.bgWallImages;
	idc_dst  =  idc;
	freeCapImageBySth(  hDlgTalk,  idc,  iTaskId,  pIdInfo,  pImgs,  old_M_GetDlgItem(  hDlgTalk,  idc_dst  )  );
#endif
	dlgTalk_freeCapImageBySth_bgWall(  hDlgTalk,  iTaskId,  pIdInfo  );
	
	return  0;
}


 //  2014/12/07
__declspec(  dllexport  )   int  dlgTalk_freeCapImageBySth_bgWall(  HWND  hDlgTalk,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo  )
{
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pm_var	=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk,  _T(  "dlgTalk_freeCapImageBySth"  )  );
	if  (  !pm_var  )  return  -1;
	DLG_TALK_var	&	m_var	=	*pm_var;
	//
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	CTX_qm_thread  *  pCqt  =  &pQyMc->gui.ctx_gui_thread;
	//
	int					idc		=	0;
	int					idc_dst	=	0;
	CAP_IMAGES	*	pImgs  =  NULL;

	//  2014/11/30
	idc  =  m_var.av.idc_bgWall_conf;
	idc_dst  =  idc;

	//
	int  i;
	for  (  i  =  0;  i  <  m_var.av.bgWall.usCnt;  i  ++  )  {
		 pImgs  =  &m_var.av.bgWall.mems[i].images;
	
		 old_freeCapImageBySth(  pCqt,  hDlgTalk,  idc,  iTaskId,  pIdInfo,  pImgs,  old_M_GetDlgItem(  hDlgTalk,  idc_dst  )  );
	}

	return  0;
}


//
  //  2014/12/07
__declspec(  dllexport  )  int  dlgTalk_freeCapImageBySth_bgWall_mgr(  HWND  hDlgTalk,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo  )
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
			 dlgTalk_freeCapImageBySth_bgWall(  pShadowMgr->shadows[i].hShadow,  iTaskId,  pIdInfo  );
		 }
	}
  
	dlgTalk_freeCapImageBySth_bgWall(  hDlgTalk,  iTaskId,  pIdInfo  );

	iErr  =   0;

errLabel:
	return  iErr;
}


//
__declspec(  dllexport  )  int  dlgTalk_freeCapImageBySth_mgr(  HWND  hDlgTalk,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo  )
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
			 dlgTalk_freeCapImageBySth(  pShadowMgr->shadows[i].hShadow,  iTaskId,  pIdInfo  );
		 }
	}
  
	dlgTalk_freeCapImageBySth(  hDlgTalk,  iTaskId,  pIdInfo  );

	iErr  =   0;

errLabel:
	return  iErr;
}





