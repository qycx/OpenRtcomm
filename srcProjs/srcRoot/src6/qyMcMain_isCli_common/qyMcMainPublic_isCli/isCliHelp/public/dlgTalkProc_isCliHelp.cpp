

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

//#include	"dlgTalk.h"
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
#include	"myTChar.h"
//#include	"dlgTalk.h"



//  2013/03/06
__declspec(  dllexport  )  int  cleanTalkerRuleTask(  HWND  hDlgTalk_mgr,  TALKER_dynBmp  *  pRuleDynBmp,  BOOL  b_askToRefreshLayout_mgr,  LPCTSTR  hint  )
 {
	 int		iErr	=	-1;
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	 CCtxQmc  *  pProcInfo  =  (CCtxQmc  *  )pQyMc->get_pProcInfo(  );
	 
	 //
	 if  (  !hint  )  hint  =  _T(  ""  );

	 //
	 if  (  !pRuleDynBmp->taskInfo.iTaskId  )  return  0;

	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	 //
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "cleanTalkerRuleTask: iTaskId %d. %s"  ),  pRuleDynBmp->taskInfo.iTaskId,  hint  );

	 	
	 //
	 void  *  pDb  =  NULL;
	 #ifndef  __NOTSUPPORT_DB__
				 CQnmDb				db;
				 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
				 pDb  =  db.m_pDbMem->pDb;
	 #endif


	 int  iStatus  =  CONST_imTaskStatus_canceledBySender;						  			
	 g_dbFuncs.pf_updateTaskStatus(  pDb,  iStatus,  pRuleDynBmp->taskInfo.iTaskId  );

	 //
	 int  index_taskInfo  =  getQmcTaskInfoIndexBySth(  pProcInfo,  pRuleDynBmp->taskInfo.iTaskId  );
	 freeTaskInfo(  pProcInfo,  index_taskInfo,  _T(  "cleanTalkerRuleTask"  )  );


	 //
	 memset(  &pRuleDynBmp->taskInfo,  0,  sizeof(  pRuleDynBmp->taskInfo  )  );

	 //  2013/06/25
	 if  (  b_askToRefreshLayout_mgr  )  {
		 askToRefreshLayout_mgr(  hDlgTalk_mgr  );
	 }

	 //
	 iErr  =  0;
errLabel:
	 return  iErr;
 }
 

//
__declspec(  dllexport  )  int  cleanTalkerRuleTasks(  HWND  hDlgTalk_mgr,  BOOL  b_askToRefreshLayout_mgr,  LPCTSTR  hint  )
{
	CHelp_getDlgTalkVar  help_getVar;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )help_getVar.getVar(  hDlgTalk_mgr  );
	if  (  !pMgrVar  )  return  -1;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  -1;
	 
	 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	 if  (  !pShadowMgr  )  return  -1;

	 int  i;
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->talkerDynBmps  );  i  ++  )  {				   
		  TALKER_dynBmp	*	pRuleElem		=	&pShadowMgr->talkerDynBmps[i];
			   if  (  pRuleElem->taskInfo.iTaskId  )  {
				   dlgTalk_freeCapImageBySth_mgr(  hDlgTalk_mgr,  pRuleElem->taskInfo.iTaskId,  NULL  );
				   //  pRuleElem->taskInfo.iTaskId  =  0;
				   cleanTalkerRuleTask(  hDlgTalk_mgr,  pRuleElem,  TRUE,  hint  );
			   }
	 }

	 qmcApplyForChkingTasks_gui(  g_pQyMc  );

	 return  0;
}



 //
__declspec(  dllexport  )  BOOL  bSame_dynBmpRule(  DYN_BMP_rule  *pRule1,  DYN_BMP_rule  *  pRule2  )
 {
	 if  (  pRule1->dynBmp.resObj.uiObjType  ==  pRule2->dynBmp.resObj.uiObjType
		 &&  pRule1->dynBmp.resObj.usIndex_obj  ==  pRule2->dynBmp.resObj.usIndex_obj  
		 &&  pRule1->dynBmp.resObj.usHelp_subIndex  ==  pRule2->dynBmp.resObj.usHelp_subIndex				//  2016/07/24
		 &&  pRule1->ucbSaveVideo  ==  pRule2->ucbSaveVideo  )		 
	 {
			 return  TRUE;
	 }

	 //
	 return  FALSE;
 }

 //  2014/05/30
 BOOL  tmp_bShadowExists(  TALKER_shadow_mgr  *  pShadowMgr,  DYN_BMP_rule  *  pDynBmpRule  )
{
	 BOOL  bShadowExists  =  FALSE;
	 int  i;
	 int  j;
	
	 DYN_BMP_rule  &  tmpDynBmp  =  *pDynBmpRule;

	 if  (  !pDynBmpRule->dynBmp.resObj.uiObjType  )  return  FALSE;

	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
			   TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
			   if  (  !pMem->hWall  )  continue;
			   //
			   for  (  j  =  0;  j  <  mycountof(  pMem->vwRuleCmd.dynBmpRules  );  j  ++  )  {				    				    
				    //
				   if  (  bSame_dynBmpRule(  &pMem->vwRuleCmd.dynBmpRules[j],  &tmpDynBmp  )  )  {
						break;
					}
			   }
			   if  (  j  ==  mycountof(  pMem->vwRuleCmd.dynBmpRules  )  )  continue;
			   //
			   if  (  pMem->uiVwRuleType  ==  CONST_vwRuleType_dynBmp  )  {
				   bShadowExists  =  TRUE;
				   break;
			   }			   
			   if  (  pMem->hShadow  )  {
				   bShadowExists  =  TRUE;
				   break;
			   }		  
	 }
	 
	 //  2013/02/13, 手工启动也当一个shadow	
	 for  (  j  =  0;  j  <  mycountof(  pShadowMgr->vwRuleCmd_manual.dynBmpRules  );  j  ++  )  {
		 if  (  bSame_dynBmpRule(  &pShadowMgr->vwRuleCmd_manual.dynBmpRules[j],  &tmpDynBmp  )  )  {
			  bShadowExists  =  TRUE;
			  break;
		  }
	 }

	 return  bShadowExists;

 }


 //
 int  tmp_addVwRule(  VW_rule_messengerCmd  *  pVwRuleCmd,  BOOL  bManual,  TALKER_shadow_mgr  *  pShadowMgr  )
 {
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 VW_rule_messengerCmd  &  vwRuleCmd  =  *pVwRuleCmd;
	 int  j;
 
	 //  2016/02/15
	 if  (  bManual  )  {
		 pShadowMgr->vwRuleCmd.helpInfo.tn_addedManuall  ++  ;
	 }

	 //
	 for  (  j  =  0;  j  <  mycountof(  vwRuleCmd.dynBmpRules  );  j  ++  )  {
		 if  (  !vwRuleCmd.dynBmpRules[j].dynBmp.resObj.uiObjType  )  continue;			
		  //
		  int  k;			
		  for  (  k  =  0;  k  <  mycountof(  pShadowMgr->vwRuleCmd.dynBmpRules  );  k  ++  )  {
			  if  (  bSame_dynBmpRule(  &vwRuleCmd.dynBmpRules[j],  &pShadowMgr->vwRuleCmd.dynBmpRules[k]  )  )  {
				  //
				  if  (  bManual  )  {  //  2016/02/15
					  pShadowMgr->vwRuleCmd.dynBmpRules[k].helpInfo.tn_addedManuall  =  pShadowMgr->vwRuleCmd.helpInfo.tn_addedManuall;
					  pShadowMgr->vwRuleCmd.dynBmpRules[k].helpInfo.ucbAddedManually  =  TRUE;
				  }
				  //
				  break;			   
			  }
		  }
		  //
		  if  (  k  ==  mycountof(  pShadowMgr->vwRuleCmd.dynBmpRules  )  )  {			
			  for  (  k  =  0;  k  <  mycountof(  pShadowMgr->vwRuleCmd.dynBmpRules  );  k  ++  )  {
				  if  (  !pShadowMgr->vwRuleCmd.dynBmpRules[k].dynBmp.resObj.uiObjType  )  {							
					  //
					  pShadowMgr->vwRuleCmd.dynBmpRules[k]  =  vwRuleCmd.dynBmpRules[j];
					  //
					  if  (  bManual  )  {  //  2016/02/15
						  pShadowMgr->vwRuleCmd.dynBmpRules[k].helpInfo.tn_addedManuall  =  pShadowMgr->vwRuleCmd.helpInfo.tn_addedManuall;
						  pShadowMgr->vwRuleCmd.dynBmpRules[k].helpInfo.ucbAddedManually  =  TRUE;				  
					  }
					  //
					  break;						
				  }				   
			  }				   
			  if  (  k  ==  mycountof(  pShadowMgr->vwRuleCmd.dynBmpRules  )  )  {				
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "chkTalkRules: too many ruleCmd.dynBmps"  )  );
				  showNotification(  NULL,  0,  0,  0,  0,  0,  _T(  "chkTalkRules: too many ruleCmd.dynBmps"  )  );  
			  }			   
		  }		  
	 }
	 //
	 //  2016/02/15
	 int  k;
	 for  (  k  =  0;  k  <  mycountof(  pShadowMgr->vwRuleCmd.dynBmpRules  );  k  ++  )  {
		  if  (  !pShadowMgr->vwRuleCmd.dynBmpRules[k].dynBmp.resObj.uiObjType  )  continue;
		  if  (  pShadowMgr->vwRuleCmd.dynBmpRules[k].helpInfo.tn_addedManuall  !=  pShadowMgr->vwRuleCmd.helpInfo.tn_addedManuall  )  {
			  pShadowMgr->vwRuleCmd.dynBmpRules[k].helpInfo.ucbAddedManually  =  FALSE;
		  }
	 }

	 //
	 return  0;
 }


 //
 __declspec(  dllexport  )   int  chkTalkerRules(  HWND  hDlgTalk,  void  *  pDLG_TALK_var  )
 {
	 int	iErr  =  -1;
	 
	 DLG_TALK_var  &  m_var  =  *(  DLG_TALK_var  *  )pDLG_TALK_var;
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;

	 int  i;	
	 BOOL  bShadowExists;	
	 
	 if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
	 
	 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	 if  (  !pShadowMgr  )  return  -1;
	 	

	 //  2014/05/30
#if  10
	 int  j;
	 for  (  j  =  0;  j  <  mycountof(  pShadowMgr->vwRuleCmd.dynBmpRules  );  j  ++  )  {
		 if  (  !pShadowMgr->vwRuleCmd.dynBmpRules[j].dynBmp.resObj.uiObjType  )  continue;
		  //
		  DYN_BMP_rule  &  tmpDynBmp  =  pShadowMgr->vwRuleCmd.dynBmpRules[j];
		  //
		  bShadowExists  =  tmp_bShadowExists(  pShadowMgr,  &tmpDynBmp  );
		  //
		  if  (  !bShadowExists  )  {
			  memset(  &pShadowMgr->vwRuleCmd.dynBmpRules[j],  0,  sizeof(  pShadowMgr->vwRuleCmd.dynBmpRules[j]  )  );
			  //
			   TALKER_dynBmp	*	pRuleElem		=	&pShadowMgr->talkerDynBmps[j];
			   if  (  pRuleElem->taskInfo.iTaskId  )  {
				   dlgTalk_freeCapImageBySth_mgr(  hDlgTalk,  pRuleElem->taskInfo.iTaskId,  NULL  );
				   //  pRuleElem->taskInfo.iTaskId  =  0;
				   cleanTalkerRuleTask(  hDlgTalk,  pRuleElem,  TRUE,  _T(  "No shadow to view remote dynBmp"  )  );
				   qmcApplyForChkingTasks_gui(  pProcInfo->pQyMc  );
			   }
		  }
	 }
	 //
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		  TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
		  if  (  !pMem->hWall  )  continue;
		  tmp_addVwRule(  &pMem->vwRuleCmd,  FALSE,  pShadowMgr  );		  
	 }
	 tmp_addVwRule(  &pShadowMgr->vwRuleCmd_manual,  TRUE,  pShadowMgr  );
#endif
			
	 //  gps	
	 bShadowExists  =  FALSE;			
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		  if  (  pShadowMgr->shadows[i].vwRuleCmd.ucbViewGps  &&  pShadowMgr->shadows[i].hShadow  )  {		
			  bShadowExists  =  TRUE;
			  break;					
		  }				
	 }			
	 if  (  bShadowExists  )  pShadowMgr->vwRuleCmd.ucbViewGps  =  TRUE;		
	 else  {
		   if  (  !pShadowMgr->ucbNotAutoStopViewing  )  {			
			   pShadowMgr->vwRuleCmd.ucbViewGps  =  FALSE;
			   if  (  pShadowMgr->viewGps.iTaskId  )  {
				   //  把任务取消
				   pShadowMgr->viewGps.iTaskId  =  0;
				   qmcApplyForChkingTasks_gui(  pProcInfo->pQyMc  );						  
			   }					  
		   }				
	 }
				
	 iErr  =  0;
//  errLabel:
	
	 return  iErr;
 }



 //
 __declspec(  dllexport  ) int  chkIfDynBmpRuleUnmatched(  HWND  hDlgTalk,  void  *  pDLG_TALK_var, DYN_BMP_rule  *  pRuleDynBmp,  TALKER_dynBmp  *	pObjElem  )
 {
	 int  iErr  =  -1;
	 DLG_TALK_var	&	m_var		=	*(  DLG_TALK_var  *  )pDLG_TALK_var;

	 //  2014/09/27
	 if  (  !pRuleDynBmp->dynBmp.idInfo.ui64Id  )  {
#ifdef  __DEBUG__
		 traceLog(  _T(  "chkIfDynBmpRuleUnmatched failed, ruleDynBmp.idInfo is 0"  )  );
#endif
		 return  -1;
	 }

	 
#if  10  //  2014/09/26
	//
	BOOL  bRuleUnmatched  =  FALSE;

	//  2014/09/27
	if  (  pObjElem->dynBmpRule.dynBmp.idInfo.ui64Id  !=  pRuleDynBmp->dynBmp.idInfo.ui64Id  )  {
		bRuleUnmatched  =  TRUE;
	}
	//
	if  (  pObjElem->uiType1  !=  CONST_talkerObjType_dynBmp	//  CONST_vwRuleType_dynBmp
		||  pObjElem->dynBmpRule.dynBmp.resObj.uiObjType  !=  pRuleDynBmp->dynBmp.resObj.uiObjType  )  
	{
		bRuleUnmatched  =  TRUE;
		}
	else  {
		  if  (  pRuleDynBmp->dynBmp.resObj.usIndex_obj  )  {
			  if  (  pObjElem->dynBmpRule.dynBmp.resObj.usIndex_obj  !=  pRuleDynBmp->dynBmp.resObj.usIndex_obj  
				  ||  pObjElem->dynBmpRule.dynBmp.resObj.usHelp_subIndex  !=  pRuleDynBmp->dynBmp.resObj.usHelp_subIndex	//  2016/07/24
				  )  
			  {
				  bRuleUnmatched  =  TRUE;
			  }
		  }
		  if  (  pObjElem->dynBmpRule.ucbSaveVideo  !=  pRuleDynBmp->ucbSaveVideo  )  {
			  bRuleUnmatched  =  TRUE;
		  }
	}

	//
	if  (  bRuleUnmatched  ) 
	{
		//
		if  (  pObjElem->uiType1  ==  CONST_talkerObjType_dynBmp  )  {
			if  (  pObjElem->taskInfo.iTaskId  )  {
				cleanTalkerRuleTask(  hDlgTalk,  pObjElem,  true,  _T(  "chkToViewDynBmp. call cleanTalkerRuleTask before init"  )  );
			}
			//  2014/09/04
			memset(  &pObjElem->taskInfo,  0,  sizeof(  pObjElem->taskInfo  )  );
		}
		//  2014/09/04
		if  (  pObjElem->uiType1  &&  pObjElem->uiType1  !=  CONST_talkerObjType_dynBmp  )  {
			MACRO_qyAssert(  FALSE,  _T(  "ObjElem->uiType err"  )  );
		}
		//
		pObjElem->uiType1  =  CONST_talkerObjType_dynBmp;
#if  0
		pObjElem->dynBmpRule.dynBmp.idInfo.ui64Id  =  pRuleDynBmp->dynBmp.idInfo.ui64Id;	//  m_var.addr.idInfo.ui64Id;
		pObjElem->dynBmpRule.dynBmp.uiObjType  =  pRuleDynBmp->dynBmp.uiObjType;
		pObjElem->dynBmpRule.dynBmp.usIndex_obj  =  pRuleDynBmp->dynBmp.usIndex_obj;
		pObjElem->dynBmpRule.ucbSaveVideo  =  pRuleDynBmp->ucbSaveVideo;	//  2014/08/04
#endif
		//  2016/07/19
		pObjElem->dynBmpRule  =  *pRuleDynBmp;
	}
	if  (  pObjElem->uiType1  !=  CONST_talkerObjType_dynBmp  )  goto  errLabel;
#endif

	iErr  =  0;
errLabel:
	return  iErr;
 }
 




 //
 __declspec(  dllexport  )  BOOL  bTaskImgActive(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var,  MIS_MSG_TASK  *  pMsgTask  )
 {
	 int  iErr  =  -1;	
	 int					nElapseInS		=	MAX_nElapseInS;	//5;
	 int  nTimeoutInS  =  MAX_nTimeoutInS;//65;

	 
	 BOOL			bTaskImgAlive	=	FALSE;
	
	 time_t			t;  
	 int			minElapseInMs	=	nTimeoutInS  *  1000  +  1;					  
	 DWORD			dwTickCnt		=	GetTickCount(  );					   
	 mytime(  &t  );

	 TCHAR			tBuf[128];
	

	 //
	 CAP_IMAGES* pImgs = nullptr;// &pm_var->av.peerZone.images;
	 int  i;

	 //
	 pImgs = getLayoutPeerImages_forD3d(pm_var);
	 if (pImgs) {
		 //
		 if (pm_var->av.taskInfo.bTaskExists) {
			 if (pMsgTask->iTaskId == pm_var->av.taskInfo.iTaskId) {
				 int  iDiffInMs = myGetTickCount(NULL) - pm_var->av.taskInfo.dwTickCnt_start;
				 if (iDiffInMs < nElapseInS * 1000) {
					 bTaskImgAlive = TRUE;
					 iErr = 0;  goto  errLabel;
				 }
			 }
		 }


		 //
		 for (i = 0; i < mycountof(pImgs->mems); i++) {
			 if (pImgs->mems[i].iTaskId == pMsgTask->iTaskId) {
				 //minElapseInMs  =  min(  minElapseInMs,  dwTickCnt  -  pImgs->mems[i].dwTickCnt_lastDrawing  );							   
				 minElapseInMs = dwTickCnt - pImgs->mems[i].dwTickCnt_lastDrawing;
				 //
				 //
				 if (minElapseInMs < nElapseInS * 1000) {
					 break;
				 }
				 //
				 _sntprintf(tBuf, mycountof(tBuf), _T("talker%I64u.bTaskImgActive: task %d, elapse %dms. inactive"), pm_var->addr.idInfo.ui64Id, pMsgTask->iTaskId, minElapseInMs);
				 showInfo_open0(0, 0, tBuf);
				 //
				 continue;
			 }
		 }

		 if (i < mycountof(pImgs->mems)) {
			 bTaskImgAlive = TRUE;
			 iErr = 0;  goto  errLabel;
		 }
	 }

	 //
	 //pImgs  =  &pm_var->av.otherZone.images;	//.otherImages;
	 pImgs = getLayoutOtherImages_forD3d(pm_var);
	 if (pImgs) {

		 for (i = 0; i < mycountof(pImgs->mems); i++) {
			 if (pImgs->mems[i].iTaskId == pMsgTask->iTaskId) {
				 minElapseInMs = dwTickCnt - pImgs->mems[i].dwTickCnt_lastDrawing;
				 if (minElapseInMs < nElapseInS * 1000) {
					 break;
				 }
			 }
		 }

		 if (i < mycountof(pImgs->mems)) {
			 bTaskImgAlive = TRUE;
			 iErr = 0;  goto  errLabel;
		 }
	 }

	 //
	 iErr  =  0;
errLabel:
	 return  iErr  ?  FALSE  :  bTaskImgAlive;
 }


 //
  //  2014/09/05
 __declspec(  dllexport  ) BOOL  bActive_talkerDynBmp(  time_t  tNow,  CAP_IMAGES  *  pImgs,  TALKER_dynBmp  *  pTalkerDynBmp  )
 {
	 BOOL  bActive  =  FALSE;

	 if  (  !pTalkerDynBmp  )  return  FALSE;
	 if  (  !pImgs  )  return  FALSE;

	 TALKER_dynBmp  *  pObjElem  =  pTalkerDynBmp;
	 CAP_IMAGES  &  images  =  *pImgs;


	 if  (  pObjElem->taskInfo.iTaskId  )  {
		//  2013/02/25. 当切换到非dialog模式时,查看视频不能在可视区显示, 靠刷新tStartTime_processed来证明该任务是活跃的
		time_t	t;  t  =  tNow;  //  mytime(  &t  );

		if  (  t  -  pObjElem->taskInfo.tStartTime_processed  <  15  )  {
			#ifdef  __DEBUG__
					//traceLog(  _T(  "chkToViewDynBmp: rules_viewDynBmp[%d] active"  ),  talkerRuleIndex  );
			#endif
			bActive  =  TRUE;
		}

		if  (  !bActive  )  {

			//
			int  k;
			
			for  (  k  =  0;  k  <  mycountof(  images.mems  );  k  ++  )  {			
				 CAP_IMAGE	*	pImg	=  &images.mems[k];					  		
				 if  (  !pImg->idInfo_sender.ui64Id  )  continue;
				 
				 if  (  pImg->iTaskId  ==  pObjElem->taskInfo.iTaskId  )  {
					 bActive  =  TRUE;  break;				  			 
				 }			 						
			}
		}
	 }

	 return  bActive;

 }

 
//
 __declspec(  dllexport  ) int  sndViewDynBmpReq(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  BOOL  bNeedProgress,  BOOL  *  pbImgRestarted,  TALKER_dynBmp		*	pObjElem,  QY_MESSENGER_ID  *  p_content_idInfo_logicalPeer  )
{
	int  iErr  =  -1;
	DLG_TALK_var	&	m_var		=	*(  DLG_TALK_var  *  )pDLG_TALK_var;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	int					tmpiRet		=	-1;
	
	QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

	
	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;


#if  10  //  2014/09/05
		//
		char	timeBuf[CONST_qyTimeLen  +  1];
		getCurTime(  timeBuf  );
		char	buf[256];
		qyDisplayTime(  timeBuf,  buf,  mycountof(  buf  )  );

		//
		_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "%s: %I64u, %s, %d."  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_statusVWallRestart  ),  pObjElem->dynBmpRule.dynBmp.idInfo.ui64Id,  qyGetDesByType1(  pTable,  pObjElem->dynBmpRule.dynBmp.resObj.uiObjType  ),  pObjElem->dynBmpRule.dynBmp.resObj.usIndex_obj  );
		if  (  pObjElem->dynBmpRule.ucbSaveVideo  )  _sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "%s save"  ),  m_var.tHint  );
		//  2014/09/27
		if  (  p_content_idInfo_logicalPeer  )  {
			_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "%s (in grp %I64u )"  ),  m_var.tHint,  p_content_idInfo_logicalPeer->ui64Id  );
		}
		//
		_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "%s %s."  ),  m_var.tHint,  CQyString(  buf  )  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "talker: %s"  ),  m_var.tHint  );

		MSGR_ADDR		addr;

		memset(  &addr,  0,  sizeof(  addr  )  );
		lstrcpyn(  addr.misServName,  m_var.pMisCnt->cfg.misServName,  mycountof(  addr.misServName  )  );
		addr.idInfo.ui64Id  =  pObjElem->dynBmpRule.dynBmp.idInfo.ui64Id;

		//
		if  (  !pObjElem->taskInfo.iTaskId  )  {
		
		//  
		pObjElem->taskInfo.bNeedProgress  =  bNeedProgress;
		BOOL  bDlgTalk  =  TRUE;	//  FALSE
		int  tmp_iTaskId  =  0;
		//
		{
		void	*	pDb	=	NULL;
		#ifndef  __NOTSUPPORT_DB__
				 CQnmDb		db;
				 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
				 pDb  =  db.m_pDbMem->pDb;
		#endif

		tmp_iTaskId  =  newTaskId(  pDb,  pQyMc->cfg.db.iDbType  );
		}
		//
		PARAM_startAvCall param = { 0 };
		tmpiRet  =  procSendAvInfo(  m_var.pMisCnt,  hDlgTalk,  bDlgTalk,  CONST_imTaskType_viewDynBmp,  &param, NULL,  NULL,  -1,  -1,  pObjElem,  p_content_idInfo_logicalPeer,  &tmp_iTaskId,  &addr,  NULL  );
		pObjElem->taskInfo.iTaskId  =  tmp_iTaskId;
		pObjElem->taskInfo.bNeedProgress  =  FALSE;
		if  (  tmpiRet  )  
		{
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "talker: procSendAvInfo failed"  )  );
			goto  errLabel;
		}

		}
		else  {
			int  index_taskInfo  =  getQmcTaskInfoIndexBySth(  pProcInfo,  pObjElem->taskInfo.iTaskId  );
			QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  index_taskInfo  );
			if  (  !pTaskInfo  )  {
				showInfo_open0(  0,  0,  _T(  "sndViewDynBmpReq failed, getTaskInfo from taskId failed"  )  );
				goto  errLabel;
			}
			MIS_MSG_TASK  *  pMsgTask_o  =  &pTaskInfo->var.pTaskData->msgU.task;
			if  (  pMsgTask_o->uiType  !=  CONST_misMsgType_task  )  goto  errLabel;
			//
												IM_CONTENTU		*	pContentTask_o	=	(  IM_CONTENTU  *  )pMsgTask_o->data.buf;
									if  (  pContentTask_o->uiType  !=  CONST_imCommType_transferAvInfo  )  goto  errLabel;

									#ifdef  __DEBUG__
											traceLogA(  "sndViewDynBmpReq: send transferAvInfo again."  );				  
									#endif
									//
									int  lenInBytes  =  pMsgTask_o->lenInBytes  -  offsetof(  MIS_MSG_routeTalkData,  buf  );
									if  (  lenInBytes  <  0  )  goto  errLabel;

			//
			QY_MESSENGER_ID  idInfo_dst  =  addr.idInfo;
			//
			postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_outputTask,  0,  pMsgTask_o->usCode,  pMsgTask_o->tStartTime,  pMsgTask_o->uiTranNo,  0,  pMsgTask_o->iTaskId,  pMsgTask_o->uiTaskType,  (  char  *  )pMsgTask_o->data.buf,  lenInBytes,  &m_var.addr.idInfo,  &pMsgTask_o->idInfo_taskSender,  &pMsgTask_o->idInfo_taskReceiver,  &idInfo_dst,  0,  NULL,  FALSE  );	
									
			//
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sndViewDynBmpReq: send transferAvInfo again to %I64u. tn %d"  ),  idInfo_dst.ui64Id,  pMsgTask_o->uiTranNo  );
									
			//
		}

		//  2013/06/25
		askToRefreshLayout_mgr(  hDlgTalk  );

		//
		if  (  pbImgRestarted  )  *pbImgRestarted  =  TRUE;
#endif

		iErr  =  0;
errLabel:

	return  iErr;
}



 //
 //
 __declspec(  dllexport  )  int  tryToFindSameRule_sndViewDynBmpReq(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  BOOL  bNeedProgress,  BOOL  *  pbImgRestarted,  int  talkerRuleIndex  )
 {
	 
	 int					iErr		=	-1;
	DLG_TALK_var	&	m_var		=	*(  DLG_TALK_var  *  )pDLG_TALK_var;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	int					tmpiRet		=	-1;

	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
			
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;

	//
	CAP_IMAGES		&	images  =  m_var.av.peerZone.images;
	
	//
	if  (  talkerRuleIndex  <  0  ||  talkerRuleIndex  >=  mycountof(  pShadowMgr->talkerDynBmps  )  )  goto  errLabel;
	TALKER_dynBmp		*	pObjElem  =  &pShadowMgr->talkerDynBmps[talkerRuleIndex];
		
	QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
	
	time_t	t;  mytime(  &t  );

	//
	if  (  !pObjElem->dynBmpRule.dynBmp.resObj.usIndex_obj  )  {
		showInfo_open0(  0,  0,  _T(  "sndViewDynBmpReq failed, usIndex_obj is 0"  )  );
		goto  errLabel;
	}
		
	//  2014/09/05. 如果有规则符合的视频对象，就把该对象的属性赋给该对象。
	int  i;
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->vwRuleCmd.dynBmpRules  );  i  ++  )  {
			DYN_BMP_rule  *  pMemRule  =  &pShadowMgr->vwRuleCmd.dynBmpRules[i];
			TALKER_dynBmp  *  pMemTalkerDynBmp  =  &pShadowMgr->talkerDynBmps[i];

			if  (  talkerRuleIndex  ==  i  )  {
				//  是规则自己，所以不需要判断
				continue;
			}

			//
			if  (  bSame_dynBmpRule(  &pObjElem->dynBmpRule,  &pMemTalkerDynBmp->dynBmpRule  )  )  {
					if  (  bActive_talkerDynBmp(  t,  &images,  pMemTalkerDynBmp  )  )  {  
						//
						if  (  pObjElem->taskInfo.iTaskId  )  {
							cleanTalkerRuleTask(  hDlgTalk,  pObjElem,  true,  _T(  ""  )  );
						}
						//
						pObjElem->taskInfo.iTaskId  =  pMemTalkerDynBmp->taskInfo.iTaskId;
						//
						iErr  =  0;  goto  errLabel;
						//
						break;
					}
			}

			//
			if  (  pObjElem->dynBmpRule.dynBmp.resObj.uiObjType  ==  pMemTalkerDynBmp->dynBmpRule.dynBmp.resObj.uiObjType
				&&  pObjElem->dynBmpRule.dynBmp.resObj.usIndex_obj  ==  pMemTalkerDynBmp->dynBmpRule.dynBmp.resObj.usIndex_obj  
				&&  pObjElem->dynBmpRule.ucbSaveVideo  !=  pMemTalkerDynBmp->dynBmpRule.ucbSaveVideo  )
			{
				TCHAR  tBuf[128];
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Rules conflict. %I64u, %s, %d. save flg different."  ),  pObjElem->dynBmpRule.dynBmp.idInfo.ui64Id,  qyGetDesByType1(  pTable,  pObjElem->dynBmpRule.dynBmp.resObj.uiObjType  ),  pObjElem->dynBmpRule.dynBmp.resObj.usIndex_obj  );
				showNotification(  0,  0,  0,  0,  0,  0,  tBuf  );
			}
	}


	//		
	if  (  sndViewDynBmpReq(  hDlgTalk,  &m_var,  bNeedProgress,  pbImgRestarted,  pObjElem,  NULL  )  )  goto  errLabel;
			
	iErr  =  0;
errLabel:
		return  iErr;

 }



//
 __declspec(  dllexport  )  int  chkToViewDynBmp(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  int  talkerRuleIndex,  BOOL  bNeedProgress,  BOOL  *  pbImgRestarted  ) 
{
	int					iErr		=	-1;
	DLG_TALK_var	&	m_var		=	*(  DLG_TALK_var  *  )pDLG_TALK_var;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	int					tmpiRet		=	-1;

	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
			
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;

	
	//
	if  (  talkerRuleIndex  <  0  ||  talkerRuleIndex  >=  mycountof(  pShadowMgr->talkerDynBmps  )  )  goto  errLabel;

	DYN_BMP_rule  *  pRuleDynBmp  =  &pShadowMgr->vwRuleCmd.dynBmpRules[talkerRuleIndex];
	if  (  !pRuleDynBmp->dynBmp.resObj.uiObjType  )  return  -1;

	CAP_IMAGES		&	images  =  m_var.av.peerZone.images;
	TALKER_dynBmp		*	pObjElem		=	&pShadowMgr->talkerDynBmps[talkerRuleIndex];
	
	//
	pRuleDynBmp->dynBmp.idInfo.ui64Id  =  m_var.addr.idInfo.ui64Id;	//  2014/09/27
	if  (  chkIfDynBmpRuleUnmatched(  hDlgTalk,  &m_var,  pRuleDynBmp,  pObjElem  )  )  goto  errLabel;

	BOOL			bActive  =  FALSE;
	time_t	t;  mytime(  &t  );

	if  (  pObjElem->taskInfo.iTaskId  )  {

		//  2014/09/06
		bActive  =  bActive_talkerDynBmp(  t,  &images,  pObjElem  );

		//
		if  (  bActive  )  {
			//pObjElem->taskInfo.tLastTime_active  =  t;
			iErr  =  0;  goto  errLabel;
		}


		//2014/10/23
		memset(  &pObjElem->taskInfo.srcInfo,  0,  sizeof(  pObjElem->taskInfo.srcInfo  )  );
		showInfo_open0(  0,  0,  _T(  "dlgTalk_procVideo: talkerDynBmp.w,h reset"  )  );


	}

	//
	if  (  !bActive  )  {				 
		QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

		

		//  2014/09/04. 如果usIndex_obj未指定，那么需要发起一个retrieveOne的请求来，随机获取一个
		if  (  !pRuleDynBmp->dynBmp.resObj.usIndex_obj  )  {
			//
			DWORD  dwTickCnt  =  GetTickCount(  );
			if  (  dwTickCnt  -  pObjElem->taskInfo.retrieveOne.dwLastTickCnt_retrieveOne  <  5000  )  goto  errLabel;
			pObjElem->taskInfo.retrieveOne.dwLastTickCnt_retrieveOne  =  dwTickCnt;
			// 
			_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "Retrieve one: %I64u, %s, %d."  ),  pObjElem->dynBmpRule.dynBmp.idInfo.ui64Id,  qyGetDesByType1(  pTable,  pObjElem->dynBmpRule.dynBmp.resObj.uiObjType  ),  pObjElem->dynBmpRule.dynBmp.resObj.usIndex_obj  );
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Talker: %s"  ),  m_var.tHint  );
			//
			unsigned  int  uiTranNo  =  0;
			if  (  sndRetrieveDynBmpsReqToMsgr_qmc(  m_var.pMisCnt,  FALSE,  pObjElem->dynBmpRule.dynBmp.resObj.uiObjType,  TRUE,  NULL,  FALSE,  &m_var.addr.idInfo,  &uiTranNo  )  )  goto  errLabel;	
			pObjElem->taskInfo.retrieveOne.uiTranNo  = uiTranNo;

			iErr  =  0;  goto  errLabel;
		}

		//
		tryToFindSameRule_sndViewDynBmpReq(  hDlgTalk,  pDLG_TALK_var,  bNeedProgress,  pbImgRestarted,  talkerRuleIndex  );

	}

	iErr  =  0;
errLabel:

	return  iErr;
	
}

///////////////////
 //

//
 int  tmpHandler_showTmpGrpMems(  void  *  p0,  void  *  p1,  void  *  p2  )
{
#ifdef  __WINCE__
	return  -1;
#else
	int							iErr						=	-1;
	//  CWnd					*	pDlgTalk					=	(  CWnd  *  )p0;
	HWND						hDlgTalk					=	(  HWND  )p0;
	if  (  !hDlgTalk  )  return  -1;
	PARAM_PROC_ROW			*	pParam						=	(  PARAM_PROC_ROW  *  )p1;
	MSGR_ADDR				*	pAddr						=	(  MSGR_ADDR  *  )p2;
	//
	CHelp_getDlgTalkVar			help_getDlgTalkVar;
	DLG_TALK_var			*	pm_var						=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pm_var  )  return  -1;
	DLG_TALK_var			&	m_var						=	*pm_var;
	QY_MC					*	pQyMc						=	QY_GET_GBUF(  );
	//  CListCtrl				*	pListCtrl				=	(  CListCtrl  *  )pDlgTalk->GetDlgItem(  m_var.idcList_members  );
	HWND						hListCtrl					=	GetDlgItem(  hDlgTalk,  m_var.idcList_members  );
	int							i;

	TCHAR						talkerDesc[128  +  1]		=	_T(  ""  );
	TCHAR						displayName[64  +  1]		=	_T(  ""  );
	int							nImage,  nSelectedImage;

	getMessengerImages(  pQyMc,  CONST_usRunningStatus_offline,  &nImage,  &nSelectedImage  );

	if  (  pAddr->displayName[0]  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  pAddr->displayName  );
	else  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "(%s)"  ),  pAddr->wDevIdStr  );
	//
	//  i  =  0;  pListCtrl->InsertItem(  pParam->nItem,  displayName,  nImage  );
	i  =  0;  myListCtrl_InsertItem(  hListCtrl,  pParam->nItem,  displayName,  nImage  );
	//  i  ++  ;  pListCtrl->SetItemText(  pParam->nItem,  i,  pAddr->wDevIdStr  );	//  ID
	i  ++  ;  myListCtrl_SetItemText(  hListCtrl,  pParam->nItem,  i,  pAddr->wDevIdStr  );	//  ID
	i  ++  ;	//  ×´Ì¬Ïî


	pParam->nItem  ++  ;


	iErr  =  0;

	return  iErr;
#endif
}


 int  qCmp_GrpMem_status_indexes(  const  void  *  p1,  const  void  *  p2  )
 {
	 GrpMem_status_index  *  pGsi1  =  (  GrpMem_status_index  *  )p1;
	 GrpMem_status_index  *  pGsi2  =  (  GrpMem_status_index  *  )p2;

	 __int64  iDiff  =  pGsi1->idInfo.ui64Id  -  pGsi2->idInfo.ui64Id;

	 if  (  iDiff  <  0  )  return  -1;
	 if  (  !iDiff  )  return  0;
	 return  1;
 }

 //
 __declspec(  dllexport  )  int  dlgTalk_loadGrpMems(  HWND  hCurTalk,  DLG_TALK_var  *  pCurTalkVar,  LPCTSTR  tFilter  )	//  2014/02/10
  {
	  //AFX_MANAGE_STATE(AfxGetStaticModuleState());

	 int  iErr  =  -1;
	 QY_MC  *  pQyMc  =  QY_GET_GBUF(  );		
	 MC_VAR_isCli			*	pProcInfo			=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	 MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;
		
	 //
	 if  (  !pCurTalkVar  )  return  -1;
	 HWND  hDlgTalk  =  hCurTalk;
	 DLG_TALK_var  &  m_var  =  *(  DLG_TALK_var  *  )pCurTalkVar;	


	 //
	 CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	 DLG_TALK_var  *  pMgrVar  =  &m_var;
	 if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		 TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
		 if  (  !pTalkerShadow  )  return  -1;
		 HWND  hMgr  =  pTalkerShadow->hMgr;
		 pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		 if  (  !pMgrVar  )  return  -1;
	 }
	 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;

	 //
	 QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	 if  (  !pDbFuncs  )  goto  errLabel;
	 QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	 
	 //
	 //
	 QY_MESSENGER_REGINFO		regInfo;
	 QY_MESSENGER_REGINFO	*	pRegInfo			=	&regInfo;


	 //	
	 if  (  !tFilter  )  tFilter  =  _T(  ""  );
		
	 //  2017/09/07
	 GrpMem_status  *  pGrpMemStatus  =  NULL;
	 GrpMemList_status  *  pGrpMemListStatus  =  &m_var.grpMemList.grpMemListStatus;
	 memset(  pGrpMemListStatus,  0,  sizeof(  pGrpMemListStatus[0]  )  );

	 //  2014/02/10. 不再一开始就装载，等手工显示分组成员时，再装载									
	 if  (  m_var.guiData.ucbShowImGrpMems  )  {
		 PARAM_PROC_ROW		param;
		
		 memset(  &param,  0,  sizeof(  param  )  );
		 //
		 param.hListCtrl  =  ::GetDlgItem(  hDlgTalk,  m_var.idcList_members  );


		 //
		 myListCtrl_DeleteAllItems(  param.hListCtrl   );

		 //
		 if  (  m_var.addr.uiObjType  ==  CONST_objType_tmpGrp  )  {
			 qTraverse(  &m_var.tmpGrpMemQ,  tmpHandler_showTmpGrpMems,  hDlgTalk,  &param  );											
			 }				
		 else  {				
			   CQnmDb				db;
								
			   if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
								
			   //  g_dbFuncs.pf_bSelectImGrpMem_dlgTalk_OnInitDialog(  hDlgTalk,  db.m_pDbMem->pDb,  &param  );						



			   //
			   CMyDb			*	pDb											=	(  CMyDb  *  )db.m_pDbMem->pDb;
			   //
			   PARAM_PROC_ROW  *  pParam  =  &param;
			   
			   //
			   HWND						hListCtrl			=	pParam->hListCtrl;	//  2017/06/25	//GetDlgItem(  hDlgTalk,  m_var.idcList_members  );
			   if  (  !hListCtrl  )  goto  errLabel;
			   int  i;
			   
			   //				
			   MY_REG_DESC					desc;
			   TCHAR						talkerDesc[128  +  1];			 
			   TCHAR						displayName[64  +  1];
						 
			   int							nImage,  nSelectedImage;			
			   TCHAR						tBuf[128];
			   
			   //
			   BOOL  bHaveAll  =  TRUE;

			   //
			   if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_bjyz  )  {
				   bHaveAll  =  FALSE;
			   }
			   			 
			   //
			   if  (  bHaveAll  )  {
				   //
				   if  (  pMgrVar->av.taskInfo.bTaskExists
					   &&  (  pMgrVar->av.taskInfo.ucbStarter
					   ||  pShadowMgr->av.ucbMeConfMgr  )
					   )			
				   {					 
					   //			  
					   nImage  =  pQyMc->cfg.image.normal.nImage_pcNormal;
					   //
					   i  =  0;  myListCtrl_InsertItem(  hListCtrl,  pParam->nItem,  _T(  "All"  ),  nImage  );
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  (  __int64  )0  );
					   i  ++  ;  myListCtrl_SetItemText(  hListCtrl,  pParam->nItem,  i,  tBuf  );
					   //
					   pParam->nItem  ++  ;			

					   //
					   if  (  pGrpMemListStatus->usCnt  <  mycountof(  pGrpMemListStatus->mems  )  )  {
						   pGrpMemStatus  =  &pGrpMemListStatus->mems[pGrpMemListStatus->usCnt];
						   pGrpMemStatus->idInfo.ui64Id  =  0;
						   //
						   pGrpMemStatus->nImage  =  nImage;
						   //
						   pGrpMemListStatus->usCnt  ++  ;
					   }
				   }
			   }


			   //
			   for  (  i  =  0;  i  <  pShadowMgr->confCtrl.grpConfCtrl.usCnt;  i  ++  )  {
				    GrpMem_confCtrl  *  pMem  =  &pShadowMgr->confCtrl.grpConfCtrl.pMems[i];

					//
					int  id_imGrpMem  =  pMem->id_imGrpMem;
				    
					//
					//
					int  iDbType  =  CONST_dbType_myDb;
					if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  _T(  ""  ),  &pMem->idInfo,  0,  &regInfo  )  )  {
						memset(  &regInfo,  0,  sizeof(  regInfo  )  );
					}

				    
					//						
					//
					if  (  regInfo2Desc(  0,  pRegInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  displayName,  mycountof(  displayName  )  )  )  goto  errLabel;
			 	
					//
					if  (  tFilter[0]  )  {
						TCHAR  *  pT;
						if  (  !my_tcsistr(  talkerDesc,  tFilter  )
							&&  !my_tcsistr(  displayName,  tFilter  )  )  					 
						{
							continue;
						}
					}

					//
					nImage  =  pQyMc->cfg.image.nImage_messenger;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedMessenger;

					{	 
						//  
						QM_OBJQ_MEM					mem;
						QMEM_MESSENGER_CLI		*	pQMem	=	NULL;
						QY_MESSENGER_INFO			messengerInfo;
						void					*	pDb		=	NULL;
						int							i;

						CQnmDb						tmpObjDb;						
						pDb				=		tmpObjDb.getAvailableDb(  pQyMc->iDsnIndex_mainSys  );

						//  regInfo messengerInfo, pClient messengerInfo
						memset(  &messengerInfo,  0,  sizeof(  messengerInfo  )  );
						//
						//lstrcpyn(  messengerInfo.misServName,  regInfo.addr.misServName,  mycountof(  messengerInfo.misServName  )  );
						messengerInfo.idInfo.ui64Id  =  pMem->idInfo.ui64Id;//  regInfo.addr.idInfo.ui64Id;

						//               
						if  (  procQmObjQ(  pProcInfo->pSgiParam,  (  QM_OBJQ  *  )m_var.pMisCnt->pObjQ,  pDb,  pQyMc->cfg.db.iDbType,  CONST_objType_messenger,  &messengerInfo,  &mem  )  )  goto  errLabel;
						if  (  !mem.pQMemObj  )  goto  errLabel;

						pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;

						//  
						lstrcpyn(  pQMem->talkerDesc,  talkerDesc,  mycountof(  pQMem->talkerDesc  )  );
						lstrcpyn(  pQMem->displayName,  displayName,  mycountof(  pQMem->displayName  )  );		//  2007/09/02

						//
						safeTcsnCpy(  talkerDesc,  pMem->talkerDesc,  mycountof(  pMem->talkerDesc  )  );
						safeTcsnCpy(  displayName,  pMem->displayName,  mycountof(  pMem->displayName  )  );

						//
						TCHAR  tDisplayBuf[128]  =  _T(  ""  );
						_sntprintf(  tDisplayBuf,  mycountof(  tDisplayBuf  ),  _T(  "%s %s %s"  ),  pMem->displayName,  pMem->ksName,  pMem->ysName  );
						//_sntprintf(  tDisplayBuf,  mycountof(  tDisplayBuf  ),  _T(  "%s %I64u"  ),  tDisplayBuf,  pMem->idInfo.ui64Id  );

						//
						getMessengerImages(  pQyMc,  pQMem->usRunningStatus,  &nImage,  &nSelectedImage  );
						//
						i  =  0;  myListCtrl_InsertItem(  hListCtrl,  pParam->nItem,  tDisplayBuf,  nImage  );
						_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMem->idInfo.ui64Id  );
						i  ++  ;  myListCtrl_SetItemText(  hListCtrl,  pParam->nItem,  i,  tBuf  );
						i  ++  ;  myListCtrl_SetItemText(  hListCtrl,  pParam->nItem,  i,  _ltot(  pMem->id_imGrpMem,  tBuf,  10  )  );
						//
						tBuf[0]  =  0;
						if  (  pMem->idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. "  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_me  )  );		//_T(  "Me"  )  );
						if  (  pMgrVar->av.taskInfo.bTaskExists
							&&  pMgrVar->addr.uiObjType  ==  CONST_objType_imGrp  )
						{
							if  (  pMem->idInfo.ui64Id  ==  pMgrVar->av.taskInfo.idInfo_starter.ui64Id  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_confStarter  )  );  //  _T(  "Starter"  )  );
							else  {
								int  k;
								for  (  k  =  0;  k  <  pShadowMgr->av.confMgrInfo.usCnt;  k  ++  )  {
									if  (  pMem->idInfo.ui64Id  ==  pShadowMgr->av.confMgrInfo.mems[k].idInfo.ui64Id  )  {
										_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_confManager  )  );  
									}
								}
							}
						}
						//
						i  ++  ;  myListCtrl_SetItemText(  hListCtrl,  pParam->nItem,  i,  tBuf  );  //  ²»ÐèÒª×´Ì¬Ïî
						i  ++  ;
						//
						myListCtrl_SetItemData(  hListCtrl,  pParam->nItem,  id_imGrpMem  );
						//
						pParam->nItem  ++  ;

						//
						//					   
						if  (  pGrpMemListStatus->usCnt  <  mycountof(  pGrpMemListStatus->mems  )  )  {
						   pGrpMemStatus  =  &pGrpMemListStatus->mems[pGrpMemListStatus->usCnt];
						   pGrpMemStatus->idInfo.ui64Id  =  pMem->idInfo.ui64Id;
						   //
						   pGrpMemStatus->nImage  =  nImage;
						   //
						   pGrpMemListStatus->usCnt  ++  ;
					   
						}


						//  2007/06/03 
						QMOBJQ_PARAM_MISCLIENT		qmObjQParam;
						//
						memset(  &qmObjQParam,  0,  sizeof(  qmObjQParam  )  );
						//  uiType
						qmObjQParam.pSci  =  (  QY_SERVICEGUI_INFO  *  )pProcInfo->pSgiParam;
						qmObjQParam.pMisCnt  =  m_var.pMisCnt;
						qmObjQParam.pDb  =  pDb;
						qmObjQParam.iDbType  =  pQyMc->cfg.db.iDbType;
						qmObjQParam.iObjType  =  CONST_objType_messenger;
						qmObjQParam.pClient  =  &messengerInfo;

						addToDisplayedObjQ(  &m_var.displayCtx,  &qmObjQParam,  hDlgTalk,  id_imGrpMem  );  

						if  (  postRecentFriend(  qmObjQParam.pMisCnt,  qmObjQParam.pClient->idInfo,  0  )  )  traceLogA(  "postRecentFriend failed"  );  

					}
				}									
	 
		}

	 }

	 //
	 GrpMem_status_indexes  *  pIndexes  =  &pCurTalkVar->grpMemList.indexes;
	 pIndexes->usCnt  =  0;
	 int  i;
	 for  (  i  =  0;  i  <  pGrpMemListStatus->usCnt;  i  ++  )  {
		  if  (  pIndexes->usCnt  >=  mycountof(  pIndexes->mems  )   )  break;
		  pIndexes->mems[pIndexes->usCnt].idInfo.ui64Id  =  pGrpMemListStatus->mems[i].idInfo.ui64Id;
		  pIndexes->mems[pIndexes->usCnt].index  =  i;
		  pIndexes->usCnt  ++  ;
	 }
	 qsort(  pIndexes->mems,  pIndexes->usCnt,  sizeof(  pIndexes->mems[0]  ),  qCmp_GrpMem_status_indexes  );

	 //  2017/09/07
	 refreshGrpMemListStatus(  hCurTalk  );

	 
	 //
	 iErr  =  0;
errLabel:
	 return  iErr;

}


//


