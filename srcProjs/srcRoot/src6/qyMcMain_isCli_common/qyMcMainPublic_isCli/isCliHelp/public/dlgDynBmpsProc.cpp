

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



//
 int  tmpHandler_findZoneParam(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 int						iErr			=	-1;
	 MIS_MSG_procVideo_qmc	*	pMsg			=	(  MIS_MSG_procVideo_qmc  *  )p0;
	 COMMON_PARAM			*	pCommonParam	=	(  COMMON_PARAM  *  )p1;
	 VW_ruleU				*	pRuleElem		=	(  VW_ruleU  *  )p2;
	 //
	 //  pCommonParam->p0;
	 int						iTaskId_videoConference	=	(  int  )pCommonParam->p1;
	 ZONE_PARAM				*	pZoneParam		=	(  ZONE_PARAM  *  )pCommonParam->p2;

	 //
	 MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMsg->pMisCnt;
	 if  (  !pMisCnt  )  {
		 return  -1;
	 }

	 //
	 BOOL						bMatched		=	FALSE;
	 int						nRulePriority	=	0;

	 switch  (  pRuleElem->common.uiType  )  {
			 case  CONST_vwRuleType_dynBmp:  
				   //  if  (  pMsg->iTaskId  ==  pRuleElem->dynBmp.iTaskId  )  
				   if  (  pMsg->paramMsgToShadow.uiTranNo_zone  ==  pRuleElem->dynBmp.uiTranNo_spObj
					   &&  pMsg->idInfo_peer.ui64Id  ==  pRuleElem->dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id
					   &&  pMsg->paramMsgToShadow.tmp_dynBmp.uiObjType  ==  pRuleElem->dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType  )
				   {
					   if  (  !pRuleElem->dynBmp.ruleDynBmp.dynBmp.resObj.usIndex_obj  )  {	//  2014/06/03
						   bMatched  =  TRUE;
						   break;
					   }
					   if  (  pRuleElem->dynBmp.ruleDynBmp.dynBmp.resObj.usIndex_obj  
						   &&  pMsg->paramMsgToShadow.tmp_dynBmp.usIndex_obj  ==  pRuleElem->dynBmp.ruleDynBmp.dynBmp.resObj.usIndex_obj  )				   
					   {		
						   bMatched  =  TRUE;  
						   break;
					   }
				   }				   
				   break;
			 case  CONST_vwRuleType_conference_imGrp:  {
				   bMatched  =  TRUE;
				   }
				   break;
			 case  CONST_vwRuleType_conference_imGrpMem:
				   if  (  iTaskId_videoConference  )  {		//  2010/09/12
					   if  (  pMsg->iTaskId  !=  iTaskId_videoConference  )  break;
				   }
				   if  (  pMsg->idInfo_sender.ui64Id  ==  pRuleElem->conference_imGrpMem.idInfo.ui64Id  )  {
					   bMatched  =  TRUE;
					   break;
				   }
				   break;
			 case  CONST_vwRuleType_bgMemVideo:  {  //  2017/09/25
				   int  ii  =  0;
				   //
				   if  (  !pMsg->idInfo_sender.ui64Id  )  {
					   if  (  pRuleElem->bgMemVideo.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
						   bMatched  =  TRUE;
						   break;
					   }
					   }
				   else  {
					     if  (  pRuleElem->bgMemVideo.idInfo.ui64Id  ==  pMsg->idInfo_sender.ui64Id  )  {
							 bMatched  =  TRUE;
							 break;
						 }
				   }
				   }
				   break;
			 default:
					 #ifdef  __DEBUG__
							 traceLogA(  "tmpHandler_getZoneParam: unknown ruleType %d",  pRuleElem->common.uiType  );
					 #endif
					 break;
	 }

	 if  (  bMatched  )  {
		 nRulePriority  =  (  int  )qyGetDesByType(  CONST_rulePriorityTable,  pRuleElem->common.uiType  );
		 if  (  nRulePriority  <  0  )  {
			 #ifdef  __DEBUG__
					 traceLogA(  "tmphandle_getZoneparam: rulePriorityTable error"  );
			 #endif
			 goto  errLabel;
		 }
		 if  (  nRulePriority  >  pZoneParam->nRulePriority  )  {
			 memset(  pZoneParam,  0,  sizeof(  ZONE_PARAM  )  );
			 //  pZoneParam->uiTranNo_zone  =  pRuleElem->dynBmp.uiTranNo_spObj;
			 pZoneParam->uiTranNo_zone  =  pRuleElem->common.uiTranNo_spObj;		//  2012/04/03
			 pZoneParam->nRulePriority  =  nRulePriority;
		 }
	 }
	 iErr  =  0;
errLabel:

	 return  iErr;
 }


#if  10	//  2013/06/12
int  dlgDynBmps_findZoneParam(  HWND  hDlgDynBmps,  MIS_MSG_procVideo_qmc  *  pMsg,  ZONE_PARAM  *  pParam  )
{
	int			iErr	=	-1;

	DLG_desktopsMon_var  *  pDlgDesktopsMonVar  =  (  DLG_desktopsMon_var  *  )getDlgDesktopsMonVar(  hDlgDynBmps  );
	if  (  !pDlgDesktopsMonVar  )  return  -1;
	DLG_dynBmps_var  *  pDlgDynBmpsVar  =  (  DLG_dynBmps_var  *  )getDlgDynBmpsVar(  hDlgDynBmps  );
	if  (  !pDlgDynBmpsVar  )  return  -1;
	DLG_dynBmps_var	&  m_var  =  *pDlgDynBmpsVar;

	int			i;
	int			tmpiRet;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	//
	ZONE_PARAM	zoneParam  =  {0};
	
	//
	if  (  !IsWindow(  pMsg->hWnd_task  )  )  return  -1;

	//
	int  iSubtype  =  pDlgDesktopsMonVar->iSubtype;
	//
	if  (  iSubtype  ==  CONST_vwSubtype_bgWall  )  {

	}
	//if  (  pDlgDynBmpsVar->


	//  2010/09/12
	int				iTaskId_videoConference	=	0;
	if  (  pDlgDesktopsMonVar->iWndContentType  ==  CONST_qyWndContentType_vWall  )  {
		if  (  m_var.vWall.ucbVideoConference  )  {
			if  (  pMsg->hWnd_task  ==  m_var.vWall.hDlgTalk_mgr  )  {

				CHelp_getDlgTalkVar	help_getDlgTalkVar;

				DLG_TALK_var  *  pDlgTalkVar	=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  m_var.vWall.hDlgTalk_mgr  );
				if  (  !pDlgTalkVar  )  goto  errLabel;

				if  (  pDlgTalkVar->av.taskInfo.bTaskExists  )  {
					iTaskId_videoConference  =  pDlgTalkVar->av.taskInfo.iTaskId;				
					//
					if  (  pMsg->iTaskId  ==  pDlgTalkVar->av.taskInfo.iTaskId  )  {
						QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pDlgTalkVar->av.taskInfo.iIndex_taskInfo  );
						if  (  !pTaskInfo  )  goto  errLabel;
						if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
						QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
						DLG_TALK_videoConference  *  pVc  =  &pTc->videoConference;

						QY_MESSENGER_ID	idInfo_sender;
						idInfo_sender.ui64Id  =  pMsg->idInfo_sender.ui64Id;
						if  (  !isMemFromActive(  pVc,  &idInfo_sender,  mynull,  NULL  )  )  {
							#ifdef  __DEBUG__
									traceLog(  _T(  "skipped: %I64u is not an activeMem"  ),  pMsg->idInfo_sender.ui64Id  );
							#endif
							goto  errLabel;
						}
					}
				}
			}
		}
	}
	
	//
	COMMON_PARAM	commonParam;
	memset(  &zoneParam,  0,  sizeof(  zoneParam  )  );
	MACRO_makeCommonParam3(  0,  (  void  *  )iTaskId_videoConference,  &zoneParam,  commonParam  );
	for  (  i  =  0;  i  <  m_var.pWall->m_var.usCnt;  i  ++  )  {
		 tmpiRet  =  qTraverse(  m_var.pWall->getSubWall(  i  )->pRuleQ,  tmpHandler_findZoneParam,  pMsg,  &commonParam  );
		 if  (  tmpiRet  )  goto  errLabel;
		 if  (  zoneParam.uiTranNo_zone  )  {
			 zoneParam.index_subWall  =  i;
			 break;
		 }
	}
	if  (  i  ==  m_var.pWall->m_var.usCnt  )  goto  errLabel;

	//
	SUB_V_WALL	*	pSubWall	=	m_var.pWall->getSubWall(  zoneParam.index_subWall  );
	if  (  !pSubWall  )  goto  errLabel;
	for  (  i  =  0;  i  <  pSubWall->usCnt;  i  ++  )  {
		 if  (  pSubWall->mems[i].uiTranNo_spObj  ==  zoneParam.uiTranNo_zone  )  break;
	}
	if  (  i  ==  pSubWall->usCnt  )  goto  errLabel;
	zoneParam.index_zone  =  i;
	
	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
		memcpy(  pParam,  &zoneParam,  sizeof(  ZONE_PARAM  )  );

	    #ifdef  __DEBUG__
		        traceLogA(  "getZoneParams: ( %I64u, %d, %d ) -> index_subWall %d, uiTranNo_spObj %d",  pMsg->idInfo_sender.ui64Id,  pMsg->uiTranNo_openAvDev,  pMsg->usIndex,  zoneParam.index_subWall,  zoneParam.uiTranNo_zone  );
		#endif
	}
	if  (  iErr  )  {
		#ifdef  __DEBUG__
			   traceLogA(  "getZoneParams failed: ( %I64u, %d, %d )",  pMsg->idInfo_sender.ui64Id,  pMsg->uiTranNo_openAvDev,  pMsg->usIndex  );
		#endif
	}

	return  iErr;
}
#endif


 //  2012/05/05
 int  tmpHandler_chkVWallRule_dlgDynBmps(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int					iErr			=	-1;
	//  p0
	COMMON_PARAM	*	pCommonParam	=	(  COMMON_PARAM  *  )p1;
	VW_ruleU		*	pRuleElem		=	(  VW_ruleU  *  )p2;
	//
	//  CDlgDynBmps		*	pDlg			=	(  CDlgDynBmps  *  )pCommonParam->p0;
	HWND				hDlgDynBmps		=	(  HWND  )pCommonParam->p0;
	int					subWallIndex	=	(  int  )pCommonParam->p1;
	BOOL			*	pbImgRestarted	=	(  BOOL  *  )pCommonParam->p2;
	//
	DLG_desktopsMon_var  *  pDlgDesktopsMonVar  =  (  DLG_desktopsMon_var  *  )getDlgDesktopsMonVar(  hDlgDynBmps  );
	if  (  !pDlgDesktopsMonVar  )  return  -1;
	DLG_dynBmps_var  *  pDlgDynBmpsVar  =  (  DLG_dynBmps_var  *  )getDlgDynBmpsVar(  hDlgDynBmps  );
	if  (  !pDlgDynBmpsVar  )  return  -1;
	DLG_dynBmps_var  &  m_var  =  *pDlgDynBmpsVar;
	//
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	QY_MC			*	pQyMc			=	(  QY_MC  *  )pProcInfo->pQyMc;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	//
	SUB_V_WALL		*	pSubWall		=	m_var.pWall->getSubWall(  subWallIndex  );
	if  (  !pSubWall  )  return  -1;
	int					j,  k;
	BOOL				bImgRestarted	=	FALSE;
	BOOL				bFound			=	FALSE;


	//  如果客户端没联上服务器,那么就不需要viewDynBmp
	if  (  !bMeOnline(  pQyMc  )  )  {
		char	timeBuf[CONST_qyTimeLen  +  1];
		getCurTime(  timeBuf  );
		char	buf[256];
		qyDisplayTime(  timeBuf,  buf,  mycountof(  buf  )  );

		_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "Can't connect to server, don't need to check vWall rule."  )  );
		_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "%s %s."  ),  m_var.tHint,  CQyString(  buf  )  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "vWall: %s"  ),  m_var.tHint  );

		goto  errLabel;
	}
	m_var.tHint[0]  =  0;


	if  (  pRuleElem->common.uiType  ==  CONST_vwRuleType_dynBmp  )  {
		

		//
#if  0
		if  (  pRuleElem->dynBmp.iTaskId  )  {
			for  (  j  =  0;  !bFound  &&  j  <  pSubWall->usCnt;  j  ++  )  {
				 for  (  k  =  0;  !bFound  &&  k  <  mycountof(  pSubWall->mems[j].images.mems  );  k  ++  )  {
					  CAP_IMAGE	*	pImg	=  &pSubWall->mems[j].images.mems[k];	
					  if  (  !pImg->idInfo_sender.ui64Id  )  continue;

					  if  (  pImg->iTaskId  ==  pRuleElem->dynBmp.iTaskId  )  {
						  bFound  =  TRUE;  break;
					  }
				 }
			}
		}
#endif

		//
		for  (  j  =  0;  j  <  pSubWall->usCnt;  j  ++  )  {
			 if  (  pSubWall->mems[j].uiTranNo_spObj  ==  pRuleElem->dynBmp.uiTranNo_spObj  )  break;
		}
		if  (  j  <  pSubWall->usCnt  )  {
			for  (  k  =  0;  k  <  mycountof(  pSubWall->mems[j].images.mems  );  k  ++  )  {
				  CAP_IMAGE	*	pImg	=  &pSubWall->mems[j].images.mems[k];	
				  if  (  !pImg->idInfo_sender.ui64Id  )  continue;
				  if  (  pImg->idInfo_sender.ui64Id  ==  pRuleElem->dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id  
					  &&  GetTickCount(  )  -  pImg->dwTickCnt_lastDrawing  <  15  *  1000  )
				  {
					  bFound  =  TRUE;
					  break;
				  }				 
			}
		}


		if  (  !bFound  )  {				 
			//
			//  pRuleElem->dynBmp.iTaskId  =  0;

			//
			QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
			char	timeBuf[CONST_qyTimeLen  +  1];
			getCurTime(  timeBuf  );
			char	buf[256];
			qyDisplayTime(  timeBuf,  buf,  mycountof(  buf  )  );

			_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "%s: %I64u, %s, %d."  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_statusVWallRestart  ),  pRuleElem->dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id,  qyGetDesByType1(  pTable,  pRuleElem->dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType  ),  pRuleElem->dynBmp.ruleDynBmp.dynBmp.resObj.usIndex_obj  );
			if  (  pRuleElem->dynBmp.ruleDynBmp.ucbSaveVideo  )  _sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "%s save"  ),  m_var.tHint  );
			_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "%s %s."  ),  m_var.tHint,  CQyString(  buf  )  );
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Wall: %s"  ),  m_var.tHint  );
			
			//
			if  (  pRuleElem->dynBmp.hTalkerShadowMgr  )  {
				if  (  !IsWindow(  pRuleElem->dynBmp.hTalkerShadowMgr  )  )  pRuleElem->dynBmp.hTalkerShadowMgr  =  NULL;
			}
			if  (  !pRuleElem->dynBmp.hTalkerShadowMgr  )  {
				// 首先找到主窗口
				HWND	hDlgTalk  =  NULL;

				BOOL  bNeedNotShowWnd  =  TRUE;
				#ifdef  __DEBUG__	
					    #ifdef  __TEST_showTalkerShadowMgrFirst__
								bNeedNotShowWnd  =  FALSE;	
								traceLog(  _T(  "for test, bNeedNotShowWnd is false"  )  );
						#endif
				#endif				
				pFuncs->pf_talkToMessenger(  pRuleElem->dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id,  0,  bNeedNotShowWnd,  FALSE,  &hDlgTalk  );				
				if  (  IsWindow(  hDlgTalk  )  )  {
					pRuleElem->dynBmp.hTalkerShadowMgr  =  hDlgTalk;					  
				}				
			}
			if  (  pRuleElem->dynBmp.hTalkerShadowMgr  )  {

				VW_rule_messengerCmd	vwRuleCmd;
				memset(  &vwRuleCmd,  0,  sizeof(  vwRuleCmd  )  );

#if  0
				if  (  pRuleElem->dynBmp.dynBmp.uiObjType  ==  CONST_objType_screen  )  {
					//  vwRuleCmd.ucbViewScreen  =  TRUE;
					tmpF_setViewRemoteVideo(  CONST_objType_screen,  CONST_usIndex_screen0,  TRUE,  &vwRuleCmd  );
					}
				else  if  (  pRuleElem->dynBmp.dynBmp.uiObjType  ==  CONST_objType_webcam  )  {
						  //
						  tmpF_setViewRemoteVideo(  CONST_objType_webcam,  pRuleElem->dynBmp.dynBmp.usIndex_obj,  TRUE,  &vwRuleCmd  );

						  }
				else  {
					  #ifdef  __DEBUG__
							  traceLog(  _T(  "tmpHandler_chkVWallRule: unprocessed objType %d"  ),  pRuleElem->dynBmp.dynBmp.uiObjType  );
					  #endif
				}
#endif
				switch  (  pRuleElem->dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType  )  {
						case  CONST_objType_screen:
						case  CONST_objType_webcam:
						case  CONST_objType_rtspStream:
						case  CONST_objType_smallStream:
							  //
							  tmpF_setViewRemoteVideo(  pRuleElem->dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType,  pRuleElem->dynBmp.ruleDynBmp.dynBmp.resObj.usIndex_obj,  pRuleElem->dynBmp.ruleDynBmp.ucbSaveVideo,  TRUE,  &vwRuleCmd  );
							  break;
						default:
							  #ifdef  __DEBUG__
							traceLog(  _T(  "tmpHandler_chkVWallRule: unprocessed objType %d"  ),  pRuleElem->dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType  );
							  #endif
							  break;
				}
				

				//		
				_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "start dynBmp: %I64u."  ),  pRuleElem->dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id  );				
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Wall: %s"  ),  m_var.tHint  );

				MIS_MSG_applyForTalkerShadow_qmc	msg;
				memset(  &msg,  0,  sizeof(  msg  )  );
				msg.uiType  =  CONST_misMsgType_applyForTalkerShadow_qmc;
				msg.hWall  =  hDlgDynBmps;	//  pDlg->m_hWnd;
				msg.iWndContentType_wall  =  pDlgDesktopsMonVar->iWndContentType;	//  pDlg->getWndContentType(  );
				msg.uiVwRuleType  =  pRuleElem->common.uiType;
				msg.uiTranNo_zone  =  pRuleElem->common.uiTranNo_spObj;
				memcpy(  &msg.vwRuleCmd,  &vwRuleCmd,  sizeof(  msg.vwRuleCmd  )  );
				msg.idInfo.ui64Id  =  pRuleElem->dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id;
				//
				pFuncs->pf_dlgTalk_qPostMsg(  pRuleElem->dynBmp.hTalkerShadowMgr,  &msg,  sizeof(  msg  )  );
				PostMessage(  pRuleElem->dynBmp.hTalkerShadowMgr,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
				
			}

		}

		}
	else  if  (  pRuleElem->common.uiType  ==  CONST_vwRuleType_messenger  )  {		//  2012/04/22

			  //
			  if  (  !bSupported_vwRuleType_messenger(  pQyMc  )  )  {
				  _sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "chkVWallRule failed, vwRuleType_messenger not supported"  )  );				
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dynBmp: %s"  ),  m_var.tHint  );
				  goto  errLabel;
			  }
			  //  2012/05/27
			  int  iSubType  =  pDlgDesktopsMonVar->iSubtype;	//  pDlg->getWndContentSubtype(  );
			  switch  (  iSubType  )  {
					  case  CONST_vwSubtype_confWall:
					  case  CONST_vwSubtype_globalGps:
					  case  CONST_vwSubtype_gps:
						    break;
					  default:
							_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "chkVWallRule failed, vwRuleType_messenger not supported in this wall"  )  );				
							qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dynBmp: %s"  ),  m_var.tHint  );
							goto  errLabel;
			  }

			  //
			  for  (  j  =  0;  !bFound  &&  j  <  pSubWall->usCnt;  j  ++  )  {
				   if  (  pSubWall->mems[j].uiTranNo_spObj  ==  pRuleElem->messenger.uiTranNo_spObj  )  {
					   bFound  =  TRUE;
					   break;	
				   }		
			  }
			  if  (  bFound  )  {
				  if  (  pRuleElem->messenger.hTalkerShadowMgr  )  {
					  if  (  !IsWindow(  pRuleElem->messenger.hTalkerShadowMgr  )  )  pRuleElem->messenger.hTalkerShadowMgr  =  NULL;
				  }
				  if  (  !pRuleElem->messenger.hTalkerShadowMgr  )  {
					  // 首先找到主窗口
					  HWND	hDlgTalk  =  NULL;

					  BOOL  bNeedNotShowWnd  =  TRUE;
					  #ifdef  __DEBUG__	
							  #ifdef  __TEST_showTalkerShadowMgrFirst__
									bNeedNotShowWnd  =  FALSE;	
									traceLog(  _T(  "for test, bNeedNotShowWnd is false"  )  );
							  #endif
					  #endif
					  pFuncs->pf_talkToMessenger(  pRuleElem->messenger.idInfo.ui64Id,  0,  bNeedNotShowWnd,  FALSE,  &hDlgTalk  );
					  if  (  IsWindow(  hDlgTalk  )  )  {
						  pRuleElem->messenger.hTalkerShadowMgr  =  hDlgTalk;
					  }
				  }
				  if  (  pRuleElem->messenger.hTalkerShadowMgr  )  {

					  //  再找影子窗口
					  if  (  pRuleElem->messenger.hTalkerShadow  )  {					  
						  if  (  !IsWindow(  pRuleElem->messenger.hTalkerShadow  )  )  pRuleElem->messenger.hTalkerShadow  =  NULL;				  
					  }

					  VW_rule_messengerCmd	vwRuleCmd;
					  memcpy(  &vwRuleCmd,  &pRuleElem->messenger.cmd,  sizeof(  vwRuleCmd  )  );
					  vwRuleCmd.ucbViewGps  =  isVwSubtype_gps(  pDlgDesktopsMonVar->iSubtype  );	//  pDlg->getWndContentSubtype(  )  );

					  if  (  !pRuleElem->messenger.hTalkerShadow  )  {

						  _sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "start shadow: %I64u."  ),  pRuleElem->messenger.idInfo.ui64Id  );
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Messenger: %s"  ),  m_var.tHint  );

						  MIS_MSG_applyForTalkerShadow_qmc	msg;
						  memset(  &msg,  0,  sizeof(  msg  )  );
						  msg.uiType  =  CONST_misMsgType_applyForTalkerShadow_qmc;
						  msg.hWall  =  hDlgDynBmps;	//  pDlg->m_hWnd;
						  msg.iWndContentType_wall  =  pDlgDesktopsMonVar->iWndContentType;	//  pDlg->getWndContentType(  );
						  msg.uiVwRuleType  =  pRuleElem->common.uiType;
						  msg.uiTranNo_zone  =  pRuleElem->messenger.uiTranNo_spObj;
						  memcpy(  &msg.vwRuleCmd,  &vwRuleCmd,  sizeof(  msg.vwRuleCmd  )  );
						  msg.idInfo.ui64Id  =  pRuleElem->messenger.idInfo.ui64Id;
						  //
						  pFuncs->pf_dlgTalk_qPostMsg(  pRuleElem->messenger.hTalkerShadowMgr,  &msg,  sizeof(  msg  )  );
						  PostMessage(  pRuleElem->messenger.hTalkerShadowMgr,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
					  }

					  //
					  if  (  pRuleElem->messenger.hTalkerShadow  )  {
						  CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
						  DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pRuleElem->messenger.hTalkerShadowMgr  );
						  if  (  !pMgrVar  )  goto  errLabel;
						  if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
						  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
						  if  (  !pShadowMgr  )  goto  errLabel;
						  for  (  k  =  0;  k  <  mycountof(  pShadowMgr->shadows  );  k  ++  )  {
							   if  (  pShadowMgr->shadows[k].hShadow  ==  pRuleElem->messenger.hTalkerShadow  )  break;
						  }
						  if  (  k  <  mycountof(  pShadowMgr->shadows  )  )  {
					
							  if  (  memcmp(  &pShadowMgr->shadows[k].vwRuleCmd,  &vwRuleCmd,  sizeof(  pShadowMgr->shadows[k].vwRuleCmd  )  )  )  {						  
								  //
								  _sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "cmd need refreshed: %I64u."  ),  pRuleElem->messenger.idInfo.ui64Id  );
								  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Messenger: %s"  ),  m_var.tHint  );

								  MIS_MSG_applyForTalkerShadow_qmc	msg;
								  memset(  &msg,  0,  sizeof(  msg  )  );
								  msg.uiType  =  CONST_misMsgType_applyForTalkerShadow_qmc;
								  msg.hWall  =  hDlgDynBmps;	//  pDlg->m_hWnd;
								  msg.iWndContentType_wall  =  pDlgDesktopsMonVar->iWndContentType;	//  pDlg->getWndContentType(  );
								  msg.uiVwRuleType  =  pRuleElem->common.uiType;
								  msg.uiTranNo_zone  =  pRuleElem->messenger.uiTranNo_spObj;
								  memcpy(  &msg.vwRuleCmd,  &vwRuleCmd,  sizeof(  msg.vwRuleCmd  )  );
								  msg.idInfo.ui64Id  =  pRuleElem->messenger.idInfo.ui64Id;
								  msg.ucbRefreshCmd  =  TRUE;
								  //
								  pFuncs->pf_dlgTalk_qPostMsg(  pRuleElem->messenger.hTalkerShadowMgr,  &msg,  sizeof(  msg  )  );
								  PostMessage(  pRuleElem->messenger.hTalkerShadowMgr,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
							  }
						  }
					  }
				  }
			  }

	}


	if  (  bImgRestarted  )  {
		if  (  pbImgRestarted  )  *pbImgRestarted  =  TRUE;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}


