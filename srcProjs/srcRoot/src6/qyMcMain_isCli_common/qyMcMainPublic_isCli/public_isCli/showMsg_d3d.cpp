





#include	"stdafx.h"
#include	<stdlib.h>
#include	<math.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"
#include	"qmcVWall.h"
#include	"WallTalkers.h"

#include	"dlgDesktopsMonProc.h"
#include	"DlgDynBmpsProc.h"
#include	"dlgVideosProc.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"

#include	"qyCusResTemp.h"

#include	"qyAvRecordPublic.h"

#include	"sp.h"



#include	"dlgTalkProc.h"

#include	"qmcGpsProc.h"
//
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"dlgSelect_isCli_public.h"

#include	"myDb.h"
#include	"isCliD3dPublic.h"

#include	"qmcCommFunc_isCli.h"













  int  showMsg_d3d(  HWND   hDlg,  QY_MESSENGER_ID  *  pIdInfo_from,  LPCTSTR  senderDesc,  LPCTSTR  str  )
 {
	if  (  !str  ||  !str[0]  )  return  -1;
	 	
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pm_var					=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlg  );
	if  (  !pm_var  )  return  -1;	
	DLG_TALK_var	&	m_var					=	*pm_var;

	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;	
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	SUBTITLE_msgs  *  pSubtitleMsgs  =  &pShadowMgr->msg.msgs;
	
	//  2014/12/23	
	//SUBTITLE_msgs  *  pSubtitleMsgs;  pSubtitleMsgs  =  &pShadowMgr->msg.msgs;
					
	//		
	pSubtitleMsgs->dwModifiedTickCnt_any_start  =  GetTickCount(  );		
	//
	int  i;		
	for  (  i  =  0;  i  <  mycountof(  pSubtitleMsgs->mems  )  -  1;  i  ++  )  {			
		 SUBTITLE_msg  *  pMem_cur  =  &pSubtitleMsgs->mems[i];
		 SUBTITLE_msg  *  pMem_next  =  &pSubtitleMsgs->mems[i  +  1];										 
		 *pMem_cur  =  *pMem_next;									
	}
									
	SUBTITLE_msg  *  pMem_last;  pMem_last  =  &pSubtitleMsgs->mems[i];	
	memset(  pMem_last,  0,  sizeof(  *pMem_last  )  );
	pMem_last->dwTickCnt_recvd  =  GetTickCount(  );
	if  (  pIdInfo_from  )  {
		pMem_last->idInfo_sender.ui64Id  =  pIdInfo_from->ui64Id;
	}
	if  (  senderDesc  )  {
		safeTcsnCpy(  senderDesc,  pMem_last->talkerDesc,  mycountof(  pMem_last->talkerDesc  )  );
	}
	safeTcsnCpy(  str,  pMem_last->tBuf,  mycountof(  pMem_last->tBuf  )  );									
	//									
	pSubtitleMsgs->dwModifiedTickCnt_any_end  =  pSubtitleMsgs->dwModifiedTickCnt_any_start;

	//
	dyn_refreshDlgTalkSubtitleMsgs_d3dWall(  hDlg  );

	return  0;
 }



  //  2015/02/16
 int  showNotification_d3d(  HWND  hDlg,  LPCTSTR  str  )
{	
	if  (  !str  ||  !str[0]  )  return  -1;
	
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pm_var					=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlg  );
	if  (  !pm_var  )  return  -1;	
	DLG_TALK_var	&	m_var					=	*pm_var;

	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;	
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	SUBTITLE_msgs  *  pSubtitleMsgs  =  &pShadowMgr->msg.msgs;

	 //
	 pSubtitleMsgs->dwModifiedTickCnt_any_start  =  GetTickCount(  );		
	
	 //
	 int  i;
		
	 for  (  i  =  0;  i  <  mycountof(  pSubtitleMsgs->notifications  )  -  1;  i  ++  )  {	
		  SUBTITLE_msg  *  pMem_cur  =  &pSubtitleMsgs->notifications[i];										 
		  SUBTITLE_msg  *  pMem_next  =  &pSubtitleMsgs->notifications[i  +  1];										 
		  *pMem_cur  =  *pMem_next;									
	 }									
	 SUBTITLE_msg  *  pMem_last;  pMem_last  =  &pSubtitleMsgs->notifications[i];		
	 memset(  pMem_last,  0,  sizeof(  *pMem_last  )  );									
	 pMem_last->dwTickCnt_recvd  =  GetTickCount(  );									
	 //pMem_last->idInfo_sender.ui64Id  =  pTalkData->route.idInfo_from.ui64Id;									
	 //safeTcsnCpy(  senderDesc,  pMem_last->talkerDesc,  mycountof(  pMem_last->talkerDesc  )  );									
	 safeTcsnCpy(  str,  pMem_last->tBuf,  mycountof(  pMem_last->tBuf  )  );
	 //
	 pSubtitleMsgs->bExists_notifications  =  TRUE;
	 //									
	 pSubtitleMsgs->dwModifiedTickCnt_any_end  =  pSubtitleMsgs->dwModifiedTickCnt_any_start;		
	 //	
	 dyn_refreshDlgTalkSubtitleMsgs_d3dWall(  hDlg  );


	 return  0;
 }




