

#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qyCusResTemp.h"

#ifndef  __NOTSUPPORT_MULTIDOC__
#ifndef  __useQt__
	#include	"mainClient.h"
	#include	"mainFrm.h"
#endif
#endif
#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	"qmcVideoCapture_isCli.h"

#include	"myresource.h"

#ifdef  __WINCE__
		#ifndef  __TEST__
				 #include	"ceMenuBar.h"
		#endif
		#include	"dlgTalk_ce.h"
#else
		#include	"dlgtalkproc.h"
#endif

#include	"QyPlaySound_wave.h"
#include	"qmcDxSurfacePublic.h"
#include	"qyWnd.h"

#include	"dlgMcClientLogon.h"
#ifdef  __WINCE__
		#include	"dlg_qyMc_winCe.h"
		#include	"dlgObjs.h"
#endif
#include	"DlgQnmCfgOptionsIsClient.h"
#include	"module_qisCamCap.h"

#ifndef  __NOTSUPPORT_MULTIDOC__
#ifndef  __useQt__
		 #include	"dlgNotification.h"
#endif
#endif

//  
#include	"mmDeviceProc.h"
#include	"isCliHelpPublic.h"
#include	"wallTalkers.h"
#include	"isCliD3dPublic.h"
#include	"isCliCorePublic.h"
#include	"dyn_isCliD3d_public.h"
#include	"qmcCommFunc_isCli.h"


//
extern QYMC_HOTKEY	gHotKeys_main[];



//  2015/07/08
#ifdef  __DEBUG__
//


#endif


//
// 2013/01/15
// 以下4个函数都是提供的给其他程序调用的
 __declspec(  dllexport  )  void  *  newQyWnd(  int  iWndContentType  )
{
	CQyWnd	*	pWnd	=	NULL;

	switch  (  iWndContentType  )  {
#if  0
		    case  CONST_qyWndContentType_mcClientLogon:
				  pWnd  =  new  CDlgMcClientLogon;
				  break;
#endif
			case  CONST_qyWndContentType_qyMc_winCe:
				  #ifdef  __WINCE__
						  pWnd  =  new  CDlg_qyMc_winCe;
				  #endif
				  break;
#if  0
			case  CONST_qyWndContentType_qnmCfgOptionsIsClient:
				  pWnd  =  new  CDlgQnmCfgOptionsIsClient;
				  break;
#endif
			case  CONST_qyWndContentType_talker:
				  #ifdef  __WINCE__
						  pWnd  =  new  CDlgTalk_ce(  GetDesktopWindow(  )  );
				  #endif
				  break;
			case  CONST_qyWndContentType_objs:
				  #ifdef  __WINCE__
						  pWnd  =  new  CDlgObjs(  GetDesktopWindow(  )  );
				  #endif
				  break;
#if  0
			case  CONST_qyWndContentType_instantAssistant:
				  #ifndef  __SUPPORT_dlgInstantAssistant_mfc__
						  pWnd  =  new  CDlgInstantAssistant;
				  #endif
				  break;
#endif
#if  0
			case  CONST_qyWndContentType_menu_walls:
				  pWnd  =  new  CDlgMenuIsCli;
				  break;
#endif
			default:
					break;
	}
	
	if  (  pWnd  )  pWnd->m_var.iWndContentType  =  iWndContentType;

	return  pWnd;
}
 

 


 


//
 
 //  2012/05/13
 int  tryToTalkToMessenger(HWND  hParent,  void  *  pMSGR_ADDR,  int  iTalkUsage, int iTalkSubtype,  BOOL  bActivateWnd,  HWND  hVWall,  int  iWndContentType_hVWall,  HWND	*	phWnd  )
 {
	 int					iErr				=	-1;
	 MSGR_ADDR			*	pAddr				=  (  MSGR_ADDR  *  )pMSGR_ADDR;
	 QY_MC				*	pQyMc				=	QY_GET_GBUF(  );
	 MC_VAR_isCli		*	pProcInfo			=	QY_GET_procInfo_isCli(  );
	 //
	 CTX_qm_thread		*	pCqt				=	&pQyMc->gui.ctx_gui_thread;
	 //
	 HWND					hWnd				=	NULL;
	 BOOL					bExists_already		=	FALSE;
	 HWND					hShadow				=  NULL;


	 CHelp_getDlgTalkVar	help_getDlgTalkVar;


	 if  (  !pAddr  )  return  -1;

	 MSGR_ADDR  &  addr_logicalPeer  =  *pAddr;
	 								
	 BOOL	bTalkerOk  =  FALSE;
	 int	i;
	 if  (  !findTalker(  pQyMc,  &addr_logicalPeer,  0,  &hWnd  )  )  bExists_already  =  TRUE;
	 
	 if  (  !bExists_already  )  {
		 if (pProcInfo->talkToMessenger(pQyMc, &addr_logicalPeer, NULL, iTalkUsage, TRUE, FALSE, &hWnd)) {
			 goto  errLabel;
		 }
	 }

	 //
	 DLG_TALK_var* pDlgTalkVar; pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hWnd);
	 if  (  !pDlgTalkVar  )  goto  errLabel;
	 if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  goto  errLabel;

	 //  2012/05/23
	 if  (  !pProcInfo->bSupported_shadow_for_tmpMsgr(  )  )  {
		 if  (  pDlgTalkVar->ucbTmpMsgr  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tryToTalkToMessenger failed: no shadow allowed,  %I64u is tmpMsgr"  ),  addr_logicalPeer.idInfo.ui64Id  );
			 goto  errLabel;
		 }
	 }

	 //  2015/12/04
	 if  (  addTalkerToGZone(  pCqt,  hWnd,  CONST_qyWndContentType_talker,  &addr_logicalPeer.idInfo,  0,  NULL  )  )  {
		 showInfo_open0(  0,  0,  _T(  "tryToTalkertoMessenger failed, addTalkerToGZone failed"  )  );
		 goto  errLabel;
	 }  

	 //  2018/11/11
	 if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )  {
		 iErr  =  0;  goto  errLabel;
	 }


	 //
	 TALKER_shadow_mgr* pShadowMgr; pShadowMgr = (TALKER_shadow_mgr*)pDlgTalkVar->pShadowInfo;
	 if  (  !pShadowMgr  )  goto  errLabel;
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		  if  (  !IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  continue;
		  //if  (  iTalkSubtype  ) 
		  {
			  if  (  pShadowMgr->shadows[i].iTalkerSubType == iTalkSubtype  ) {
				  bTalkerOk = TRUE;
				  break;
			  }
				}
#if 0
		  else {
			  if (isTalkerSubtype_canInput(pShadowMgr->shadows[i].iTalkerSubType))
			  {
				  bTalkerOk = TRUE;
				  break;
			  }
		  }
#endif
	 }
	 if  (  !bTalkerOk  )  {
		 if  (  !pDlgTalkVar->guiData.param.bNeedNotShowWnd  )  {
			 bTalkerOk  =  TRUE;
		 }
	 }
	 if  (  !bTalkerOk  )  {
#if  10   //  2016/02/01. windows系统以3d为主，全局会议墙已经没有价值。但是在android系统里可能还有用
		 //
		 if  (  IsWindow(  hVWall  )  )  {
			 //			
			 //  先在shadows里找个空位			
			 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {									
				  if  (  !IsWindow(  pShadowMgr->shadows[i].hWall  )  )  break;				
			 }
			 if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  {
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "Gui"  ),  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tryToTalkToMessenger failed: no new shadow allowed,  %I64u"  ),  addr_logicalPeer.idInfo.ui64Id  );
				 goto  errLabel;
			 }

			 //
			 int	iTalkerSubType  =  CONST_talkerSubtype_onVWall_global;
			 MSGR_ADDR	addr;
			 memcpy(  &addr,  &pDlgTalkVar->addr,  sizeof(  addr  )  );
			 addr.uiTranNo_shadow  =  getuiNextTranNo(  0,  0,  0  );
			 //
			 pProcInfo->getTalkerShadow(  hVWall,  &addr,  NULL,  iTalkerSubType,  FALSE,  0,  &hShadow  );				  
			 if  (  !IsWindow(  hShadow  )  )  goto  errLabel;
			 
			 //  2014/01/02				
			 int  iIndex_wall;
			 if  (  addToWalls(  hShadow,  hVWall,  iWndContentType_hVWall,  &iIndex_wall  )  )  goto  errLabel;
			 
			 //
			 memset(  &pShadowMgr->shadows[i],  0,  sizeof(  pShadowMgr->shadows[i]  )  );
			 pShadowMgr->shadows[i].hWall  =  hVWall;
			 pShadowMgr->shadows[i].iWndContentType_wall  =  iWndContentType_hVWall;
			 pShadowMgr->shadows[i].iTalkerSubType  =  iTalkerSubType;
			 pShadowMgr->shadows[i].hShadow  =  hShadow;
			 //
			 bTalkerOk  =  TRUE;
		 }
#endif
	 }

	 //  2012/05/18
	 if  (  !bTalkerOk  )  {
			 //			
			 //  先在shadows里找个空位			
			 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {									
				  if  (  !IsWindow(  pShadowMgr->shadows[i].hWall  )  )  break;				
			 }
			 if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  {
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "Gui"  ),  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tryToTalkToMessenger failed: no new shadow allowed,  %I64u"  ),  addr_logicalPeer.idInfo.ui64Id  );
				 goto  errLabel;
			 }

			 //
			 if (!hParent) {
				 hParent = GetDesktopWindow();
			 }

			 //
			 //int	iTalkerSubType  =  CONST_talkerSubtype_enlarged_mgr;
			 MSGR_ADDR	addr;
			 memcpy(  &addr,  &pDlgTalkVar->addr,  sizeof(  addr  )  );
			 addr.uiTranNo_shadow  =  getuiNextTranNo(  0,  0,  0  );
			 //
			 pProcInfo->getTalkerShadow(  hParent,  &addr,  NULL,  iTalkSubtype,  FALSE,  0,  &hShadow  );				  
			 if  (  !IsWindow(  hShadow  )  )  goto  errLabel;
			 //
			 memset(  &pShadowMgr->shadows[i],  0,  sizeof(  pShadowMgr->shadows[i]  )  );
			 pShadowMgr->shadows[i].hWall  =  hWnd;
			 pShadowMgr->shadows[i].iWndContentType_wall  =  0;
			 pShadowMgr->shadows[i].iTalkerSubType  =  iTalkSubtype;
			 pShadowMgr->shadows[i].hShadow  =  hShadow;
			 //
			 bTalkerOk  =  TRUE;
	 }


	 //
	 if  (  !bTalkerOk  )  {
		 if  (  pProcInfo->talkToMessenger(  pQyMc,  &addr_logicalPeer,  NULL,  iTalkUsage,  FALSE,  bActivateWnd,  &hWnd  )  )  goto  errLabel;
		 }
	 else  if  (  bActivateWnd  )  {
			   if  (  pProcInfo->talkToMessenger(  pQyMc,  &addr_logicalPeer,  NULL,  iTalkUsage,  TRUE,  bActivateWnd,  &hWnd  )  )  goto  errLabel;
	 }

	 //  2017/07/07
	 refreshTalkToInfo_mgr(  hWnd  );

	 //
	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 if  (  IsWindow(  hShadow  )  )  PostMessage(  hShadow,  WM_CLOSE,  0,  0  );
		 if  (  !bExists_already  )  {
			 if  (  IsWindow(  hWnd  )  )  PostMessage(  hWnd,  WM_CLOSE,  0,  0  );
		 }
	 }
	 if  (  !iErr  )  {
		 if  (  phWnd  )  *phWnd  =  hWnd;
	 }

	 return  iErr;
}


//
int  tryToTalkToMessenger_id(HWND  hParent, unsigned  __int64  ui64Id,  int  iTalkSubtype,  BOOL  bActivateWnd,  HWND  hVWall,  int  iWndContentType_hVWall,  HWND	*	phWnd  )
{
 
 	MSGR_ADDR	addr;
	memset(  &addr,  0,  sizeof(  addr  )  );
	addr.idInfo.ui64Id  =  ui64Id;

	return  tryToTalkToMessenger(hParent, &addr,  0,  iTalkSubtype,  bActivateWnd,  hVWall,  iWndContentType_hVWall,  phWnd  );
}


//
 int  tryToTalkToMessenger_any(HWND hParent,  unsigned  __int64  ui64Id,  int  iTalkSubtype,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  )
{
	int			iErr  =  -1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	//
	MSGR_ADDR	addr;
	memset(  &addr,  0,  sizeof(  addr  )  );
	addr.idInfo.ui64Id  =  ui64Id;

	if  (  dyn_bD3dUsing(  pProcInfo,  NULL  )  )  {	
		if  (  dyn_tryToTalkToMessenger_d3dWall(  pProcInfo,  &addr.idInfo,  0,  FALSE,  phWnd  )  )  goto  errLabel;	
		}
	else  {
		  //
		  #if  0  //  2017/02/12def  __APP_qyMc_touchscreen__	//  2012/05/12
			      if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  bNeedNotShowWnd,  FALSE,  phWnd  )  )  goto  errLabel;
		  #else
				if  (  tryToTalkToMessenger(hParent, &addr,  0,  iTalkSubtype,  FALSE,  mynull,  0,  phWnd  )  )  goto  errLabel;
	      #endif			
	}

	iErr  =  0;

errLabel:

	return  iErr;
}


 

