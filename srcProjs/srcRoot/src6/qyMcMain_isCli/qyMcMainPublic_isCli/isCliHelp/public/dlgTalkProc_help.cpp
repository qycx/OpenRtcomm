
#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	"qymcMainCommon.h"
#include	"myresource.h"


#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_iscli.h"

#ifdef  __SUPPORT_HTMLEDIT__
	#include	"myHtmlEditCtrl.h"
#endif

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
//#include	"DlgTalk.h"
#include	"dlgtalkproc.h"
#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"

//#include	"DlgInstantAssistant.h"

#include	<assert.h>
#ifndef  __WINCE__
	//#include	"qyPs.h"
#endif
#include	"qmcDxSurfacePublic.h"
#include	"qmcConferenceWall.h"

#include	"isCliHelpPublic.h"
#include	"qmcCmdProc.h"
#include	"isCmdConst.h"

#include	"funcsForIsCliHelp.h"
#include	"isCliD3dPublic.h"
#include	"wallTalkers.h"

//#include	"DlgMsgTool.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliCorePublic.h"

#include	"dyn_isCliD3d_public.h"
#include	"qmcFunc.h"
//
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


 


//  2012/04/30
 //__declspec(  dllexport  )  BOOL  dlgTalk_bQuitDlg(  void  **  ppDlgTalkParam,  BOOL  bCancelTasks  )
__declspec(dllexport)  BOOL  dlgTalk_bQuitDlg(HWND  hDlgTalk,void * pm_var_param, BOOL  bCancelTasks)
{
	//if  (  !ppDlgTalkParam  ||  !*ppDlgTalkParam  )  return  FALSE;
	if (!hDlgTalk || !pm_var_param)  return false;

	//
	BOOL				bRet		=	FALSE;
	//MACRO_CDlgTalk	*	pDlgTalk	=	(  MACRO_CDlgTalk  *  )*ppDlgTalkParam;

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	//DLG_TALK_var	&	m_var		=	pDlgTalk->m_var;
	DLG_TALK_var* pm_var = (DLG_TALK_var*)pm_var_param;//pDlgTalk->get_pm_var();
	if  (  !pm_var  )  return  FALSE;
	DLG_TALK_var  &  m_var  =  *pm_var;

	
	int					i;

#ifdef  __DEBUG__
		traceLogA(  "CDlgTalk(  )::bQuitDlg enters"  );
		//  MC_VAR_isCli  *  pProcInfo	=	QY_GET_procInfo_isCli(  );
#endif

	//  2012/05/25
	if  (  pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_bQuitDlg %I64u, %d enters"  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow  ); 
	}


	//
	BOOL				bShadowMgr	=	isTalkerShadowMgr(  m_var.addr  );
	QY_MESSENGER_ID		tmp_idInfo;	
	tmp_idInfo.ui64Id  =  m_var.addr.idInfo.ui64Id;
	unsigned  int		tmp_uiTranNo_shadow	=	m_var.addr.uiTranNo_shadow;
	int					tmp_iTalkerSubType	=	m_var.iTalkerSubType;
	HWND				tmphDlgTalk = hDlgTalk;//pDlgTalk->m_hWnd;

	//
	M_syncFlg_bQuitDlg_start(  &m_var.syncFlgs.bInSequence,  tmphDlgTalk,  _T(  "CDlgTalk::bQuitDlg failed, bLocked already."  )  );

	//
	{
#if  0
		CQySyncFlg	syncFlg;
		if  (  syncFlg.sync(  &m_var.syncFlgs.bInSequence  )  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::bQuitDlg failed, subWnd exists."  )  );
			goto  errLabel;		//  2011/03/28. 如果子窗口不关闭，这个退出就不能进行。
		}
#endif

		//  2014/04/28
		bool  bFlgSetAlready_saveMsg  =  FALSE;
		bEnable_saveMsgFlg(  pProcInfo,  &bFlgSetAlready_saveMsg  );
		if  (  !bFlgSetAlready_saveMsg  )  {
			BOOL  bEnable  =  FALSE;
			//
			if  (  !pQyMc->appParams.bNoPrompt_mfc  )  {
				//
				if  (  !dyn_bFullScreen_d3dWnd(  pProcInfo,  NULL  )  )  {
					TCHAR  tBuf[128]  =  _T(  ""  );
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_saveMsgAsTextInDir  ),  pProcInfo->cfg.policy.dirToSaveMsg  );
					if  (  qyMessageBox(  tmphDlgTalk,  tBuf,  _T(  "www.qycx.com"  ),  MB_YESNO,  30  *  1000,  NULL  )  ==  IDYES  )  {
						bEnable  =  TRUE;
					}
				}
			}
			//
			setSaveMsgFlg(  bEnable  );
		}

		//  2011/03/07. 要把instantAssistant放在这里，因为如果resourceWnd或者会议窗口先关闭时，instantAssistant作为resourceWnd的子窗口将失效，所以就关不了了，会造成内存泄露。
		if  (  m_var.hWnd_instantAssistant  )  closeInstantAssistant(  hDlgTalk  );
		if  (  IsWindow(  m_var.hWnd_instantAssistant  )  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "dlgTalk_bQuitDlg failed, closeInstantAssistant failed"  )  );
			#endif
			goto  errLabel;
		}
		//
#if  0
		if  (  m_var.confMgr.hWnd_confMgr  )  SendMessageTimeout(  m_var.confMgr.hWnd_confMgr,  WM_CLOSE,  0,  0,  0,  200,  NULL  );
		if  (  IsWindow(  m_var.confMgr.hWnd_confMgr  )  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "dlgTalk_bQuitDlg failed, close confMgr failed"  )  );
			#endif
			goto  errLabel;
		}
#endif
		//  2014/01/26
		if  (  IsWindow(  m_var.msgTool.hWnd_msgTool  )  )  SendMessageTimeout(  m_var.msgTool.hWnd_msgTool,  WM_CLOSE,  0,  0,  0,  200,  NULL  );
		if  (  IsWindow(  m_var.msgTool.hWnd_msgTool  )  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "dlgTalk_bQuitDlg failed, closeMsgTool failed"  )  );
			#endif
			goto  errLabel;
		}

		//  2012/05/16. 先关闭所有输入窗口.
		if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
			TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
			if  (  pShadowMgr  )  {
				for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
					//
					if  (  !isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  continue;
					//
					if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  {
						SendMessage(  pShadowMgr->shadows[i].hShadow,  WM_CLOSE,  0,  0  );
						if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  goto  errLabel;
					}
				}
			}
		}
		//  2012/05/18
		if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
			TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
			if  (  pShadow  )  {
				if  (  IsWindow(  pShadow->hEnlargedWnd  )  )  {
					SendMessage(  pShadow->hEnlargedWnd,  WM_CLOSE,  0,  0   );
					if  (  IsWindow(  pShadow->hEnlargedWnd  )  )  goto  errLabel;
				}
			}
		}


		//  2012/04/30
		if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
			  HWND						hMgr  =  NULL;
			  DLG_TALK_var			*	pMgrVar	=	NULL;
			  CHelp_getDlgTalkVar		help_getDlgTalkVar_mgr;	//  2013/07/15

			  //
			  if (m_var.iTalkerSubType == CONST_talkerSubtype_video) {
				  if (m_var.pShadowInfo) {
					  TALKER_shadow* pTalkerShadow = (TALKER_shadow*)m_var.pShadowInfo;
					  hMgr = pTalkerShadow->hMgr;
					  pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
					  if (pMgrVar) {
						  if (pMgrVar->av.taskInfo.bTaskExists) {
							  //pFuncs->pf_dlgTalk_closeTask(hMgr, pMgrVar->av.taskInfo.iTaskId);
							  pFuncs->pf_dlgTalk_cancelTasks(hMgr, pMgrVar, pMgrVar->av.taskInfo.iTaskId, false);
						  }
					  }

				  }
			  }


			  //
			  if  (  !isTalkerSubtype_canInput(  m_var.iTalkerSubType  )  )  {
					bCancelTasks  =  FALSE;
					}
#if  0
			  else  {
				    if  (  !m_var.pShadowInfo  )  bCancelTasks  =  FALSE;				  
					else  {
					      TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
						  hMgr  =  pTalkerShadow->hMgr;
						  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hMgr  );										  
					}			
			  }
			  if  (  !pMgrVar  ||  !pMgrVar->m_pProcessQ  )  bCancelTasks  =  FALSE;
			  else  if  (  isTalkerShadowMgr(  pMgrVar->addr  )  )  {
						TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
						if  (  pShadowMgr  )  {
							//  2012/05/14
							//  int  n  =  0;
							for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
								 //  2013/08/30
								 if  (  IsWindow(  pShadowMgr->shadows[i].hWall  )  &&  pShadowMgr->shadows[i].iWndContentType_wall  ==  CONST_qyWndContentType_consoleWall  )  {
									 break;
								 }
								 //
								 if  (  pShadowMgr->shadows[i].hShadow  ==  pDlgTalk->m_hWnd  )  continue;
								 if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  &&  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
									 //  n  ++  ;
									 break;
								 }
								 //
								 continue;
							}
							//  如果能找到其他可输入的影子窗口或者是d3d的墙,就不需要取消任务了. 2013/08/30
							//  if  (  n  )  
							if  (  i  <  mycountof(  pShadowMgr->shadows  )  )
							{
								bCancelTasks  =  FALSE;
							}
						}		
			  }
#endif
		}


		//
		if  (  bCancelTasks  )  {

			//  
			if  (  pFuncs->pf_dlgTalk_cancelTasks(  hDlgTalk,  &m_var,  0,  0  )  <  0  )  {
				QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
				if  (  !pQyMc->bQuit  )  {
					//  2017/10/02
					dlgTalk_doLayout(  hDlgTalk  );
					//
					goto  errLabel;
				}
			}
		}


		//
		//if  (  m_var.av.hWnd_remoteAv_taskInfo  )  ::SendMessage(  m_var.av.hWnd_remoteAv_taskInfo,  WM_CLOSE,  0,  0  );
		//if  (  m_var.av.hWnd_remoteAv_resourcesInfo  )  ::SendMessage(  m_var.av.hWnd_remoteAv_resourcesInfo,  WM_CLOSE,  0,  0  );
		//  if  (  m_var.hWnd_vWall  )  SendMessage(  m_var.hWnd_vWall,  WM_CLOSE,  0,  0  );
		//
		if  (  m_var.ptzControl.hWnd_ptzControl  )  ::SendMessage(  m_var.ptzControl.hWnd_ptzControl,  WM_CLOSE,  0,  0  );			//  2013/02/16
		if  (  IsWindow(  m_var.ptzControl.hWnd_ptzControl  )  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::bQuitDlg failed, ptz still exists."  )  );
			goto  errLabel;
		}
		if  (  m_var.subtitles.hWnd_subtitles  )  ::SendMessage(  m_var.subtitles.hWnd_subtitles,  WM_CLOSE,  0,  0  );
		if  (  IsWindow(  m_var.subtitles.hWnd_subtitles  )  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::bQuitDlg failed, subtitles still exists."  )  );
			goto  errLabel;
		}
		//  2015/08/01
		if  (  m_var.offlineRes.hTool_offlineRes  )  ::SendMessageTimeout(  m_var.offlineRes.hTool_offlineRes,  WM_CLOSE,  0,  0,  0,  200,  NULL  );
		if  (  IsWindow(  m_var.offlineRes.hTool_offlineRes  )  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::bQuitDlg failed, offlineRes still exists."  )  );
			goto  errLabel;
		}

		//  2012/04/23
		if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
			TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
			if  (  pShadowMgr  )  {
				//  
				//  2017/10/02
#if  0
				if  (  pShadowMgr->secondView.hWnd_dlgVideos  )  ::SendMessageTimeout(  pShadowMgr->secondView.hWnd_dlgVideos,  WM_CLOSE,  0,  0,  0,  200,  NULL  );
				if  (  IsWindow(  pShadowMgr->secondView.hWnd_dlgVideos  )  )  {
					showInfo_open0(  0,  0,  _T(  "dlgTalk_bQuitDlg failed, hWnd_dlgVideos exists"  )  );
					goto  errLabel;
				}
#endif
				//
				for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
					 //  2013/09/08
					 if  (  pShadowMgr->shadows[i].iWndContentType_wall  ==  CONST_qyWndContentType_consoleWall  )  {
						 GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
						 if  (  pGBuf  )  {
							 #if  0
							 if  (  pShadowMgr->shadows[i].hWall  ==  pGBuf->hWall_d3d  )  {
								 D3DWallDataU  *  pWallMem  =  (  D3DWallDataU  * )getCurD3dWallData(  pGBuf  );
								 if  (  pWallMem  &&  pWallMem->uiType  ==  CONST_wallMemType_talker  )  {
									 if  (  pWallMem->talker.hTalkerMgr  ==  pDlgTalk->m_hWnd  )  {
										 d3dWall_reset(  pGBuf->hWall_d3d  );
									 }
								 }
							 }
							 #endif
							 //  2014/01/14
							 pGBuf->ucbChkD3dWall  =  TRUE;

						 }
					 }
					 //
					 if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  {
						 SendMessage(  pShadowMgr->shadows[i].hShadow,  WM_CLOSE,  0,  0  );
					 }
				}
				//  2012/05/17. 要确保所有的子窗口都被关闭
				for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
					 if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  break;					
				}
				if  (  i  <  mycountof(  pShadowMgr->shadows  )  )  {
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::bQuitDlg failed, shadow still exists."  )  );
					goto  errLabel;
				}
			}
		}
	}

	//  2017/09/23
	m_var.bShouldQuit1  =  TRUE;

	//
#ifdef  __DEBUG__
		//qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::bQuitDlg failed, (%I64u,%d), lCnt_getDlgVar is not 0. %d"  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow,  m_var.syncFlgs.lCnt_getDlgVar  );
		
#endif

	//  2013/07/16
	if  (  m_var.syncFlgs.lCnt_getDlgVar  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "CDlgTalk::bQuitDlg failed, lCnt_getDlgVar is not 0. %d"  ),  m_var.syncFlgs.lCnt_getDlgVar  );
		#endif
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::bQuitDlg failed, (%I64u,%d), lCnt_getDlgVar is not 0. %d"  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow,  m_var.syncFlgs.lCnt_getDlgVar  );
		goto  errLabel;
	}


	//
	//  2016/02/09
	if  (  isTalkerShadowMgr(  m_var.addr  )  )  {		
		if  (  isTalkerInGZone(  tmphDlgTalk,  CONST_qyWndContentType_talker,  NULL  )  )  {
			removeTalkerFromGZone(  pProcInfo,  tmphDlgTalk,  CONST_qyWndContentType_talker  );
		}
	}
	
	//  2009/05/01  
	pProcInfo->myDestroyWindow(tmphDlgTalk);
	
	//  2012/05/15. 检查一下
	if  (  !bShadowMgr  )  {
		if  (  tmp_idInfo.ui64Id  )  {
			HWND	hMgr	=	NULL;
			MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
			if  (  !findTalker(  pQyMc,  &tmp_idInfo,  &hMgr  )  )  {
				#if  0
				if  (  tmp_iTalkerSubType  ==  CONST_talkerSubType_enlarged_mgr  )  {
					//  该窗口代表主窗口,所以把主窗口也关闭
					PostMessage(  hMgr,  WM_CLOSE,  0,  0  );
					}
				else  
				#endif
				{  // 如果没有影子窗口,并且主窗口也不可视,则关闭主窗口 
					CHelp_getDlgTalkVar	help_getDlgTalkVar;
					DLG_TALK_var	*	pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hMgr  );
					  if  (  pMgrVar  )  {
						  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
						  if  (  pShadowMgr  )  {
							  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
								   TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
								   //  2013/08/30
								   if  (  IsWindow(  pMem->hWall  )  
									   &&  pMem->iWndContentType_wall  ==  CONST_qyWndContentType_consoleWall  )
								   {								
									   BOOL  bExists  =  FALSE;
									   if  (  !dyn_getVal_bWmTalkerShadowExists(  &pMem->wdId,  &bExists  )
										   &&  bExists  )
									   {										   
										   break;
									   }
								   }
								   //
								   if  (  IsWindow(  pMem->hShadow  )  )  break;							 
								   if  (  pMem->uiVwRuleType  ==  CONST_vwRuleType_dynBmp  &&  IsWindow(  pMem->hWall  )  )  break;
							  }
							  if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  {	//  说明没有影子了
								  if  (  isInvisibleMgr(  *pMgrVar  )  )  {	
									  #ifdef  __DEBUG__
											  traceLog(  _T(  "dlgTalk_bQuitDlg: %I64u, no shadow left and mgr is invisible, so close the shadow mgr"  ),  tmp_idInfo.ui64Id  );
									  #endif
									  PostMessage(  hMgr,  WM_CLOSE,  0,  0  );
								  }
							  }
						  }
					  }
				}
			}
		}
	}

	//  2014/02/14. d3d全屏时，如果失焦会造成不全屏，所以这里聚焦下
#if  10
	if  (  dyn_bFullScreen_d3dWnd(  pProcInfo,  NULL  )  )  {
		GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )g_pQyMc->pGBuf_d3d;
		if  (  pGBuf  )  {
			if  (  IsWindow(  pGBuf->hWall_d3d  )  )  {
				//  SetFocus(  pGBuf->hWall_d3d  );
				SetActiveWindow(  pGBuf->hWall_d3d  );
			}
		}
	}
#endif


	//
	bRet  =  TRUE;
		
errLabel:

	//
#ifdef  __DEBUG__
		traceLogA(  "CDlgTalk(  )::bQuitDlg leaves"  );
#endif
	//  2012/05/25
	if  (  pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_bQuitDlg %I64u, %d leaves. bRet %d"  ),  tmp_idInfo.ui64Id,  tmp_uiTranNo_shadow,  bRet  ); 
	}
	
	//
	M_syncFlg_bQuitDlg_end
		
	return  bRet;
}


__declspec(dllexport)void  dlgTalk_PostNcDestroy(  void  * pm_var_param  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	if  (  !pm_var_param  )  return;

	//MACRO_CDlgTalk	*	pDlgTalk	=	(  MACRO_CDlgTalk  *  )*ppDlgTalkParam;

	//DLG_TALK_var	&	m_var		=	pDlgTalk->m_var;
	DLG_TALK_var  *  pm_var  =  (DLG_TALK_var*)pm_var_param;
	if  (  !pm_var  )  return;
	DLG_TALK_var  &  m_var  =  *pm_var;



#if  0
	#ifdef  __DEBUG__
			traceLogA(  "PostNcDestroy: exit gpsQ"  );
	#endif
	if  (  m_var.ucbGpsQ2Inited  )  exitQyQ2(  &m_var.m_gpsQ2  );
#endif

	#ifdef  __DEBUG__
			traceLogA(  "PostNcDestroy: exit processQ"  );
	#endif
#if  0
	if  (  m_var.bProcessQInited  )  exitGenericQ(  &m_var.m_processQ  );	//  ÒòÎªprocessQ¹ØÏµµ½ÆäËûµÄ´°¿ÚÒª·¢ÏûÏ¢¹ýÀ´¡£ËùÒÔ£¬Ó¦¸ÃÔÚdestroyÖ®ºó£¬ÔÙÇå³ý¶ÓÁÐ¡£
#endif
	//
	if  (  m_var.m_pProcessQ  )  genericQFree(  m_var.m_pProcessQ  );


	//
#if  0
	if  (  m_var.msgToolCommon.m_pHtmlEdit_input  )  {  delete  m_var.msgToolCommon.m_pHtmlEdit_input;  m_var.msgToolCommon.m_pHtmlEdit_input  =  NULL;	}
	if  (  m_var.msgToolCommon.m_pHtmlEdit_recentMsgList  )  {  delete  m_var.msgToolCommon.m_pHtmlEdit_recentMsgList;  m_var.msgToolCommon.m_pHtmlEdit_recentMsgList  =  NULL;	}
#endif

	//  2012/04/24
	pFuncs->pf_TALKER_shadow_free(  isTalkerShadowMgr(  m_var.addr  ),  m_var.pShadowInfo  );

	//  2012/05/08
	exitCapSubWnds(  &m_var.subWnds  );

	//
#if  0
	if  (  !m_var.guiData.bCreated  )  traceLogA(  "DlgTalk::PostNcDestroy(  ): don't need delete"  );

	if  (  m_var.guiData.bCreated  )  {

		#ifdef  __DEBUG__
				traceLog(  _T(  "DlgTalk::PostNcDestroy(  ): delete this, %I64u"  ),  m_var.addr.idInfo.ui64Id  );
		#endif
		//
		if  (  pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  )  { 
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::PostNcDestroy:to delete this, %I64u,%u"  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow  );	
		}

		//
		try  {
			 delete  pDlgTalk;  *ppDlgTalkParam  =  NULL;		
			}
#ifndef  __WINCE__
		catch  (  CException  *  e  )  {
			   e->Delete(  );
			   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::PostNcDestroy failed."  )  );
		}
#endif
		catch  (  ...  )  {
			   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::PostNcDestroy failed."  )  );
		}
	}
#endif


	#if  1	//  def  __SUPPORT_dlgWalls__	
			if  (  pProcInfo  )  {
				PostMessage(  pProcInfo->g_hVWall,  WM_COMMAND,  MAKEWPARAM(  ID_applyForChkingWalls,  0  ),  0  );
			}		 
	#endif
	qmcApplyForChkingTasks_gui(  pProcInfo->pQyMc  );	//  2009/09/10

	traceLogA(  "DlgTalk::PostNcDestroy(  ) leaves"  );

}

 
 __declspec(dllexport) int  tmpHandler_findTalker(  void  *  p0,  void  *  pCommonParam1Param,  void  *  pQElem  )
{
	 int					iRet				=	-1;
	 //  p0;
	 COMMON_PARAM		*	pCommonParam1		=	(  COMMON_PARAM  *  )pCommonParam1Param;
	 //
	 MSGR_ADDR			*	pAddr				=	(  MSGR_ADDR  *  )pCommonParam1->p0;
	 unsigned  int			unused				=	(  unsigned  int  )pCommonParam1->p1;
	 //  pCommonParam1->p2;
	 //  
	 MIS_MSGU			*	pMsg				=	(  MIS_MSGU  *  )pQElem;
	 //
	 BOOL					bMatched			=	FALSE;

	 if  (  pMsg->uiType  ==  CONST_misMsgType_talkingFriend_qmc  )  {
		 
		 //
		 if  (  !lstrcmpi(  pAddr->misServName,  pMsg->talkingFriend_qmc.addr.misServName  )  )  {

			 //  2012/04/23
			 if  (  pAddr->uiTranNo_shadow  !=  pMsg->talkingFriend_qmc.addr.uiTranNo_shadow  )  {
				 iRet  =  0;  goto  errLabel;
			 }

			 //
			 switch  (  pAddr->uiObjType  )  {
#if  0
					 case  CONST_objType_phoneGuest:
						   if  (  pAddr->uiDevType  ==  pMsg->talkingFriend_qmc.addr.uiDevType  
							   &&  !_wcsicmp(  pAddr->wDevIdStr,  pMsg->talkingFriend_qmc.addr.wDevIdStr  )
								   &&  !_wcsicmp(  pAddr->wPath,  pMsg->talkingFriend_qmc.addr.wPath  )  )  bMatched  =  TRUE;
						   break;
					 case  CONST_objType_tmpGrp:  
						   if  (  pAddr->uiDevType  ==  pMsg->talkingFriend_qmc.addr.uiDevType  
							   &&  !_wcsicmp(  pAddr->wDevIdStr,  pMsg->talkingFriend_qmc.addr.wDevIdStr  )
								   &&  !_wcsicmp(  pAddr->wPath,  pMsg->talkingFriend_qmc.addr.wPath  )  
									   &&  (  void  *  )pAddr->tStartTime_notice  ==  (  void  *  )pMsg->talkingFriend_qmc.addr.tStartTime_notice  
										   &&  pAddr->uiTranNo_notice  ==  pMsg->talkingFriend_qmc.addr.uiTranNo_notice  )  bMatched  =  TRUE;
						   break;
#endif
					 default:
						     if  (  pAddr->idInfo.ui64Id  ==  pMsg->talkingFriend_qmc.addr.idInfo.ui64Id  )  bMatched  =  TRUE;
							 break;
			 }
			 if  (  bMatched  )  {
			 	 pCommonParam1->p2  =  (  void  *  )pMsg->talkingFriend_qmc.hWnd;
			 	 iRet  =  1;	goto  errLabel;
		 	 }
		 }
	 
	 }

	 iRet  =  0;
errLabel:
	 return  iRet;
}


 __declspec(  dllexport  )  int  findTalker(  void  *  pQyMcParam,  MSGR_ADDR  *  pAddr,  unsigned  int  unused,  HWND  *  phWnd  )
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr								=	-1;
	 QY_MC					*	pQyMc								=	(  QY_MC  *  )pQyMcParam;
	 COMMON_PARAM				commonParam1;
	 MIS_CNT				*	pMisCnt								=	NULL;
	 int						iRet;
	 HWND						hWnd								=	NULL;
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	 if  (  !pAddr  )  return  -1;

	 //  2012/04/23
	 assert(  !pAddr->uiTranNo_shadow  );

	 //
	 if  (  !(  pMisCnt  =  getMisCntByName(  pProcInfo,  pAddr->misServName  )  )  )  goto  errLabel;

	 MACRO_makeCommonParam3(  (  void  *  )pAddr,  (  void  *  )unused,  0,  commonParam1  );
	 iRet  =  qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_findTalker,  0,  &commonParam1  );
	 if  (  iRet  <=  0  )  goto  errLabel;
	 hWnd  =  (  HWND  )commonParam1.p2;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 if  (  phWnd  )  *phWnd  =  hWnd;
	 }
	 return  iErr;
 }


  int  tmpHandler_findTalker_simple(  void  *  p0,  void  *  pCommonParam1Param,  void  *  pQElem  )
{
	 int					iRet				=	-1;
	 //  p0;
	 COMMON_PARAM		*	pCommonParam1		=	(  COMMON_PARAM  *  )pCommonParam1Param;
	 //
	 TCHAR				*	misServName			=	(  TCHAR  *  )pCommonParam1->p0;
	 QY_MESSENGER_ID	*	pIdInfo				=	(  QY_MESSENGER_ID  *  )pCommonParam1->p1;
	 //  pCommonParam1->p2;
	 //  
	 MIS_MSGU			*	pMsg				=	(  MIS_MSGU  *  )pQElem;
	 //
	 BOOL					bMatched			=	FALSE;

	 if  (  pMsg->uiType  ==  CONST_misMsgType_talkingFriend_qmc  )  {
		 
		 //
		 if  (  !lstrcmpi(  misServName,  pMsg->talkingFriend_qmc.addr.misServName  )  )  {

			 //  2012/04/23. 这里只需要找主窗口,所以把影子窗口略过
			 if  (  !isTalkerShadowMgr(  pMsg->talkingFriend_qmc.addr  )  )  {
				 iRet  =  0;  goto  errLabel;
			 }

			 //
			 if  (  pIdInfo->ui64Id  ==  pMsg->talkingFriend_qmc.addr.idInfo.ui64Id  )  bMatched  =  TRUE;
		 }

		 if  (  bMatched  )  {
			 pCommonParam1->p2  =  (  void  *  )pMsg->talkingFriend_qmc.hWnd;
			 iRet  =  1;	goto  errLabel;
		 }
	 }

	 iRet  =  0;
errLabel:
	 return  iRet;
}


 __declspec(  dllexport  )  int  findTalker(  void  *  pQyMcParam,  QY_MESSENGER_ID  *  pIdInfo,  HWND  *  phWnd  )
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	int						iErr								=	-1;
	 QY_MC					*	pQyMc								=	(  QY_MC  *  )pQyMcParam;
	 if (!pQyMc)return -1;
	 CCtxQmc* pProcInfo = (CCtxQmc *)pQyMc->get_pProcInfo();

	 MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));// (MIS_CNT*)pMisCntParam;
	 COMMON_PARAM				commonParam1;
	 int						iRet;
	 HWND						hWnd								=	NULL;

	 if  (  !pMisCnt  ||  !pIdInfo  ||  !pIdInfo->ui64Id  )  return  -1;

	 MACRO_makeCommonParam3(  (  void  *  )pMisCnt->cfg.misServName,  (  void  *  )pIdInfo,  0,  commonParam1  );
	 iRet  =  qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_findTalker_simple,  0,  &commonParam1  );
	 if  (  iRet  <=  0  )  goto  errLabel;
	 hWnd  =  (  HWND  )commonParam1.p2;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 if  (  phWnd  )  *phWnd  =  hWnd;
	 }
	 return  iErr;
}


 __declspec(  dllexport  )  int  removeTalker(  void  *  pQyMcParam,  MSGR_ADDR  *  pAddr,  unsigned  int  unused  )
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT	*	pMisCnt	=  getMisCntByName(  pProcInfo,  pAddr->misServName  );
	if  (  !pMisCnt  )  return  -1;
	COMMON_PARAM	commonParam1;
	MACRO_makeCommonParam3(  (  void  *  )pAddr,  (  void  *  )unused,  0,  commonParam1  );

	qRemoveMsg(  &pMisCnt->talkingFriendQ,  tmpHandler_findTalker,  NULL,  &commonParam1  );  

	return  0;
}


 //
 //
 __declspec(dllexport  )  int  findTalker_shadow(void* pQyMcParam, unsigned  __int64 id, int  iTalkSubtype, HWND* phWnd)
 {
	 //AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	 int						iErr = -1;
	 QY_MC* pQyMc = (QY_MC*)pQyMcParam;
	 COMMON_PARAM				commonParam1;
	 MIS_CNT* pMisCnt = NULL;
	 int						iRet;
	 HWND						hWnd = NULL;
	 MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

	 if (!id)  return  -1;


	 //
	 if (!(pMisCnt = pProcInfo->getMisCntByName(_T(""))))  goto  errLabel;


	 QY_MESSENGER_ID idInfo;
	 idInfo.ui64Id = id;
	 if (findTalker(pQyMc, &idInfo, &hWnd))  goto  errLabel;

	 HWND  hShadow = mynull;
	 bool bTalkerOk = false;

	 {
		 CHelp_getDlgTalkVar help_getVar;
		 DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getVar.getVar(hWnd);

		 if (!pDlgTalkVar)goto  errLabel;


		 int i;

		 //
		 if (!isTalkerShadowMgr(pDlgTalkVar->addr))goto  errLabel;
		 TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pDlgTalkVar->pShadowInfo;
		 if (!pShadowMgr)  goto  errLabel;

		 for (i = 0; i < mycountof(pShadowMgr->shadows); i++) {
			 if (!IsWindow(pShadowMgr->shadows[i].hShadow))  continue;
			 //if (iTalkSubtype) 
			 {
				 if (pShadowMgr->shadows[i].iTalkerSubType == iTalkSubtype) {
					 hShadow = pShadowMgr->shadows[i].hShadow;
					 bTalkerOk = TRUE;
					 break;
				 }
			 }
#if false
			 else {
				 if (isTalkerSubtype_canInput(pShadowMgr->shadows[i].iTalkerSubType)) {
					 hShadow = pShadowMgr->shadows[i].hShadow;
					 bTalkerOk = true;
					 break;
				 }
			 }
#endif
		 }

	 }
	 if (!bTalkerOk)goto  errLabel;
	 if (phWnd)  *phWnd = hShadow;

	 //
	 iErr = 0;
 errLabel:

	 if (!iErr) {
	 }
	 return  iErr;
 }




 //  2014/04/29
__declspec(dllexport  )  BOOL  bDone_retrieveAllImObjRules(  MIS_CNT  *  pMisCnt  )
{
	return  pMisCnt->refreshImObjRules.tLastRefreshedTime  ?  TRUE  :  FALSE;
}


//
__declspec(  dllexport  )  int  getTalker_inputShadow(  HWND  hCurTalk,  HWND  *  phTalk  )
{
	int  iErr  =  -1;
	int  i;	 	 
	HWND  hTalk  =  NULL;

	CHelp_getDlgTalkVar  help_getDlgTalkVar;
	DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hCurTalk  );
	if  (  !pCurVar  )  return  -1;
	if  (  !isTalkerShadowMgr(  pCurVar->addr  )  )  {
		hTalk  =  hCurTalk;
		iErr  =  0;  goto  errLabel;
	}

	//
	DLG_TALK_var  *  pMgrVar  =  pCurVar;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;


	//
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {		  
		 if  (  !IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  continue;		  
		 if  (  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {			  
			 hTalk  =  pShadowMgr->shadows[i].hShadow;			 
			 break;		  											 
		 }	 							
	}		

	
	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
		if  (  phTalk  )  *phTalk  =  hTalk;
	}

	return  iErr;

}



   //  


//
//
 __declspec(  dllexport  )  int  talkToMessenger(  unsigned  __int64  ui64Id,  int  iTalkUsage,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  )
{
	 CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	MSGR_ADDR	addr;
	memset(  &addr,  0,  sizeof(  addr  )  );
	addr.idInfo.ui64Id  =  ui64Id;

	return  pProcInfo->talkToMessenger(  g_pQyMc,  &addr,  NULL,  iTalkUsage,  bNeedNotShowWnd,  bActivateWnd,  phWnd  );
}



//


 

 //
 __declspec(  dllexport  )  int  addTalkerShadow(  HWND  hWall,  int  iWndContentType_wall,  WM_ID  *  pWdId,  HWND  hShadow,  HWND  hDlgTalk_mgr  )
{
	int					iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;	
	DLG_TALK_var  *  pMgrVar  =  NULL;
	
	//
	if  (  !IsWindow(  hWall  )  )  return  -1;
	if  (  !pWdId  )  return  -1;

	//
	HWND	hMgr  =  hDlgTalk_mgr;
	 pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
	 if  (  !pMgrVar  )  goto  errLabel;

	 if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;

	 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	 if  (  !pShadowMgr  )  goto  errLabel;

	 int  i;
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		 TALKER_shadow_mgrMem  *  pShadow  =  &pShadowMgr->shadows[i];
		 if  (  pShadow->hWall  ==  hWall
			 &&  pShadow->iWndContentType_wall  ==  iWndContentType_wall  )
		 {
			 BOOL  bMatched  =  FALSE;
			 //
			 switch  (  iWndContentType_wall  )  {
					 case  CONST_qyWndContentType_consoleWall:
						   if  (  pShadow->wdId.iGrpType  ==  pWdId->iGrpType
							   &&  pShadow->wdId.index_wm  ==  pWdId->index_wm
							   &&  pShadow->wdId.uiTranNo_wm  ==  pWdId->uiTranNo_wm  )
						   {
							   bMatched  =  TRUE;
						   }
						   break;
					 default:
							break;
			 }
			 //
			 if  (  bMatched  )  {
				 iErr  =  0;  goto  errLabel;
			 }
		 }
	 }

	 // not matched
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		  TALKER_shadow_mgrMem  *  pShadow  =  &pShadowMgr->shadows[i];
		  if  (  !IsWindow(  pShadow->hWall  )  )  {
			  break;			  
		  }
	 }
	 if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  {
		 showInfo_open0(  0,  0,  _T(  "addTalkerShadow failed, too many shadow"  )  );
		 goto  errLabel;
	 }
	 //
	 TALKER_shadow_mgrMem  *  pShadow  =  &pShadowMgr->shadows[i];
	 memset(  pShadow,  0,  sizeof(  pShadow[0]  )  );
	 pShadow->hWall  =  hWall;
	 pShadow->iWndContentType_wall  =  iWndContentType_wall;
	 pShadow->wdId  =  *pWdId;

	 //
	 iErr  =  0;
errLabel:

	 return  iErr;
}



 //
 __declspec(  dllexport  )  int  removeTalkerShadow(  HWND  hWall,  int  iWndContentType_wall,  HWND  hShadow,  HWND  hDlgTalk_mgr  )
{
	int					iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;	
	DLG_TALK_var  *  pMgrVar  =  NULL;
	
	HWND	hMgr  =  hDlgTalk_mgr;
	 pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
	 if  (  !pMgrVar  )  goto  errLabel;

	 if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;

	 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	 if  (  !pShadowMgr  )  goto  errLabel;

	 int  i;
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		 TALKER_shadow_mgrMem  *  pShadow  =  &pShadowMgr->shadows[i];
		 if  (  pShadow->hWall  ==  hWall
			 &&  pShadow->iWndContentType_wall  ==  iWndContentType_wall  )
		 {
			 switch  (  iWndContentType_wall  )  {
					 case  CONST_qyWndContentType_consoleWall:
						   memset(  pShadow,  0,  sizeof(  pShadow[0]  )  );
						   break;
					 default:
							break;
			 }
		 }
		 //
		 if  (  iWndContentType_wall  ==  CONST_qyWndContentType_consoleWall  )  {
			 if  (  isTalkerSubtype_canInput(  pShadow->iTalkerSubType  )  )  {
				 //PostMessage(  pShadow->hShadow,  
			 }
		 }
	 }

	 //
	 if  (  pMgrVar->guiData.param.bNeedNotShowWnd  )  {
		 BOOL  bCanClose  =  FALSE;
		 if  (  !bTalkerShadowExists(  hMgr,  &bCanClose  )
			 ||  bCanClose  )  
		 {
			 qyShowInfo1(  CONST_qyShowType_warning,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "removeTalkerShadow(%I64u), no shadow exists, close window now"  ),  pMgrVar->addr.idInfo.ui64Id  );
			 PostMessage(  hDlgTalk_mgr,  WM_CLOSE,  0,  0  );
		 }
	 }


	 iErr  =  0;
errLabel:

	 return  iErr;
}


 //
 __declspec(  dllexport  )  BOOL  bTalkerShadowExists(  HWND  hDlgTalk_mgr,  BOOL  *  pbCanClose  )
 {
	 BOOL  bRet  =  FALSE;
	 //BOOL  bOnlyD3dShadow  =  FALSE;		//  2014/02/04
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  FALSE;

	 CHelp_getDlgTalkVar  help_getDlgTalkVar;
	 DLG_TALK_var  *  pDLG_TALK_var  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlgTalk_mgr,  _T(  "bTalkerShadowExists"  )  );
	 if  (  !pDLG_TALK_var  )  return  FALSE;

	 DLG_TALK_var  &m_var  =  *(  DLG_TALK_var  *  )pDLG_TALK_var;

	 if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  FALSE;

	 //
	 BOOL  bCanClose  =  FALSE;
	 BOOL  bInGZone  =  FALSE;
	 BOOL  bShadowExists =  FALSE;

	 //
	 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	 int  i;
	 
	 //  2016/02/09
	 if  (  isTalkerInGZone(  hDlgTalk_mgr,  CONST_qyWndContentType_talker,  &i  )  )  {
		 //
		 bInGZone  =  TRUE;
		 //
		 ZONE_objs  *  pGZone  =  pProcInfo->pGZone_activeTalkers;
		 if  (  !pGZone  )  goto  errLabel;
		 ZONE_obj  *  pMem  =  NULL;
		 for  (  i  =  0;  i  <  mycountof(  pGZone->mems  );  i  ++  )  {
			  pMem  =  &pGZone->mems[i];
			  if  (  pMem->hWndWallMem  ==  hDlgTalk_mgr  )  {
				  break;
			  }
		 }
		 if  (  i  <  mycountof(  pGZone->mems  )  )  {
			 if  (  pMem->waitForPreRender.bWait  )  {
				 DWORD  dwTickCnt  =  GetTickCount(  );
				 int  iDiffInMs  =  dwTickCnt  -  pMem->waitForPreRender.dwTickCnt_startToWait;
				 //
				 if  (  iDiffInMs  <  5000  )  {
					 //
					 TCHAR  tBuf[128]  =  _T(  ""  );
					 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u, bTalkerShadowExists returns true. waitForPreRender.bWait true"  ),  m_var.addr.idInfo.ui64Id  );
					 showInfo_open0(  0,  0,  tBuf  );
					 //
					 bRet  =  TRUE;  goto  errLabel;
				 }
			 }
		 }
	 }


	 //  2015/12/16
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {	
		  TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
		  //
		  if  (  !IsWindow(  pMem->hWall  )  )  continue;
		  
		  //
		  bShadowExists  =  TRUE;

		  //			
		  if  (  pMem->iWndContentType_wall  ==  CONST_qyWndContentType_consoleWall  )  {
			
			  //  有工作窗口相当于影子窗口
			  BOOL  bExists  =  FALSE;
			  if  (  !dyn_getVal_bWmTalkerShadowExists(  &pMem->wdId,  &bExists  )  
				  &&  bExists  )		  
			  {
				  break;		  
			  }

			  continue;
		  }

		  //  对不在GZONE里，有SHADOW就可以不要关闭
		  if  (  !bInGZone  )  break;

		  // 如果在GZONE里，之有非vwall的shadow才能算有效
		  if  (  pMem->iWndContentType_wall  !=  CONST_qyWndContentType_vWall  )  {
			  break;
		  }

		  //
		  continue;
	 }		

	 //
	 if (!bShadowExists) {
		 goto  errLabel;
	 }

	 //
	 if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  {
		 bCanClose  =  TRUE;
	 }
	 
	 //
	 bRet  =  TRUE;

errLabel:

	 if  (  bRet  )  {

		 if  (  pbCanClose  )  {
			 *pbCanClose  =  bCanClose;
		 }

	 }

	 return  bRet;
 }


 //  2015/08/02
 __declspec(  dllexport  )  BOOL  bProcOfflineResToolExists_mgr(  void  *  pDLG_TALK_var  )
 {
	 BOOL  bRet  =  FALSE;
	 //BOOL  bOnlyD3dShadow  =  FALSE;		//  2014/02/04

	 if  (  !pDLG_TALK_var  )  return  FALSE;

	 DLG_TALK_var  &m_var  =  *(  DLG_TALK_var  *  )pDLG_TALK_var;

	 if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  FALSE;

	 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	 int  i;
	 
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->procOfflineRes_mgr.mems  );  i  ++  )  {	
		 if  (  IsWindow(  pShadowMgr->procOfflineRes_mgr.mems[i].hTool_offlineRes  )  )  break;				
	 }
	 if  (  i  <  mycountof(  pShadowMgr->procOfflineRes_mgr.mems  )  )  {
		 bRet  =  TRUE;  goto  errLabel;
	 }

	 //
	 if  (  IsWindow(  pShadowMgr->offlineRes.hTool_offlineRes  )  )  {
		 //
		 bRet  =  TRUE;  goto  errLabel;
	 }

	  

errLabel:

	 if  (  bRet  )  {
	 }

	 return  bRet;
 }


 //
 		








//#include	"dlgMsgTool.h"
 
 //  int  dlgTalk_procTask_htmlEdit(  HWND  hDlgTalk,  void  *  pHtmlEditCtrl,  LPCTSTR  url  )



 __declspec(dllexport)  void  dlgTalk_taskInfo_memset0(HWND  hDlgTalk_mgr)
 {
	 CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	 CHelp_getDlgTalkVar help_getDlgTalkVar;
	 DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var *)help_getDlgTalkVar.getVar(hDlgTalk_mgr);
	 if (!pDlgTalkVar)  return;
	 if (!isTalkerShadowMgr(pDlgTalkVar->addr)) return;
	 DLG_TALK_var* pMgrVar = pDlgTalkVar;

	 memset(&pMgrVar->av.taskInfo, 0, sizeof(pMgrVar->av.taskInfo));

	 //
	 int iHkStatus_local = pProcInfo->av.confLayout.taskInfo.iHkStatus_local;
	 memset(&pProcInfo->av.confLayout.taskInfo, 0, sizeof(pProcInfo->av.confLayout.taskInfo));
	 pProcInfo->av.confLayout.taskInfo.iHkStatus_local = iHkStatus_local;


	 return;	 
 }




 





 

  //
  __declspec(  dllexport  )  BOOL  dlgTalk_canSpeak(  HWND  hDlgTalk_mgr  )
{
	BOOL							bRet				=	FALSE;
	CHelp_getDlgTalkVar				help_getDlgTalkVar;
	DLG_TALK_var				*	pm_var				=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk_mgr,  _T(  "dlgTalk_canSpeak"  )  );
	if  (  !pm_var  )  return  FALSE;
	DLG_TALK_var				&	m_var				=	*pm_var;
	//
	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  FALSE;
	//
	MC_VAR_isCli					*	pProcInfo			=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	QY_SHARED_OBJ				*	pSharedObj			=	NULL;
	SHARED_OBJ_USR				*	pSharedObjUsr		=	NULL;

	if  (  !m_var.av.taskInfo.bTaskExists  )  return  FALSE;
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
	if  (  !pTaskInfo  )  goto  errLabel;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
	DLG_TALK_videoConference  *  pVc  =  &pTc->videoConference;

	//
	if  (  !(  pSharedObj  =	getSharedObjByIndex(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  )  )  )  goto  errLabel;
	if  (  pSharedObj->iIndex_curUsr  !=  m_var.av.iIndex_usr_localAv  )  goto  errLabel;		//  2010/09/07
	if  (  !(  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  m_var.av.iIndex_usr_localAv  )  )  )  goto  errLabel;

	//  if  (  m_var.av.taskInfo.ucbVideoConference  )  
	{	//  2010/09/04
		if  (  !isMemFromActive(  pVc,  &m_var.pMisCnt->idInfo,  mynull,  NULL  )  
			//||  pVc->bNeedRefresh_activeMems_from  
			)  goto  errLabel;
	}

	//
	if  (  pTc->ucbNotSendData  )  goto  errLabel;
	
	//if  (  !pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  &&  !pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  goto  errLabel;
	if  (  !pTaskInfo->var.curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  &&  !pTaskInfo->var.curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  goto  errLabel;
		
#if  0  //  2014/11/27
	//  2013/03/19
	if  (  pSharedObj->uiType  !=  CONST_sharedObjType_av  )  {
		if  (  pProcInfo->av.localAv.recordSoundProcInfo.uiRecordType  ==  CONST_recordType_directX  )  {
			if  (  !pProcInfo->av.localAv.recordSoundProcInfo.bCapDevConnected  )  goto  errLabel;
		    }
		else  {
			  if  (  !pProcInfo->av.localAv.recordSoundProcInfo.recThread.bRunning  )  goto  errLabel;

			  //  2013/05/26
			  if  (  pProcInfo->av.localAv.recordSoundProcInfo.uiRecordType  ==  CONST_recordType_msAec  )  {
				  if  (  pProcInfo->av.localAv.recordSoundProcInfo.bInputErr_aec  )  goto  errLabel;
			  }
		}
	}
#endif

	//
	bRet  =  TRUE;
errLabel:
	return  bRet;

}


 




  //
  BOOL  dlgTalk_bRecorderOk(  HWND  hDlgTalk  )
 {
	 BOOL  bRet  =  FALSE;

	CHelp_getDlgTalkVar				help_getDlgTalkVar;
	DLG_TALK_var				*	pm_var				=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk,  _T(  "dlgTalk_canSpeak"  )  );
	if  (  !pm_var  )  return  FALSE;
	DLG_TALK_var				&	m_var				=	*pm_var;
	MC_VAR_isCli					*	pProcInfo			=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	QY_SHARED_OBJ				*	pSharedObj			=	NULL;
	SHARED_OBJ_USR				*	pSharedObjUsr		=	NULL;

	if  (  !m_var.av.taskInfo.bTaskExists  )  return  FALSE;

	if  (  !(  pSharedObj  =	getSharedObjByIndex(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  )  )  )  goto  errLabel;
	if  (  pSharedObj->iIndex_curUsr  !=  m_var.av.iIndex_usr_localAv  )  goto  errLabel;		//  2010/09/07
	if  (  !(  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  m_var.av.iIndex_usr_localAv  )  )  )  goto  errLabel;


#if  10  //  2014/11/27
	//  2013/03/19
	if  (  pSharedObj->uiType1  !=  CONST_sharedObjType_av  )  {
		if  (  pProcInfo->av.localAv.recordSoundProcInfo.uiRecordType  ==  CONST_recordType_directX  )  {
			if  (  !pProcInfo->av.localAv.recordSoundProcInfo.bCapDevConnected  )  goto  errLabel;
		    }
		else  {
			  //if  (  !pProcInfo->av.localAv.recordSoundProcInfo.recThread.bRunning  )  goto  errLabel;
			  //  2017/06/19
			  if  (  !bRecordRunning(  &pProcInfo->av.localAv.recordSoundProcInfo  )  )  {
				  goto  errLabel;
			  }

			  //  2013/05/26
			  if  (  pProcInfo->av.localAv.recordSoundProcInfo.uiRecordType  ==  CONST_recordType_msAec  )  {
				  if  (  pProcInfo->av.localAv.recordSoundProcInfo.bInputErr_aec  )  goto  errLabel;
			  }
		}
	}
#endif

	bRet  =  TRUE;
errLabel:
	return  bRet;

  }


 //  2012/05/05

 __declspec(  dllexport  )  BOOL  dlgTalk_bShowMsgBox1(  HWND  hCurTalker  )
{
	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurTalker,  _T(  "dlgTalk_bShowMsgBox"  )  );
	if  (  !pCurTalkerVar  )  return  FALSE;

	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	DLG_TALK_var  *  pMgrVar  =  NULL;
	if  (  !isTalkerShadowMgr(  pCurTalkerVar->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pCurTalkerVar->pShadowInfo;
		if  (  !pTalkerShadow  )  return  FALSE;
		pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr,  _T(  "dlgTalk_bShowMsgBox,  hMgr"  )  );
		if  (  !pMgrVar  )  return  FALSE;
		}
	else  {
		  pMgrVar  =  pCurTalkerVar;
	}
	//  2017/08/24
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  return  FALSE;
		

	//  1. 本地设置优先
	if  (  pCurTalkerVar->guiData.snmpbShowMsgBox  )  {	 
		if  (  pCurTalkerVar->guiData.snmpbShowMsgBox  ==  CONST_snmpTrue  )  return  TRUE;
		return  FALSE;
	}


	//  消息组有消息框. 2014/02/01
	if  (  pCurTalkerVar->guiData.usGrpSubtype  ==  CONST_imGrpSubtype_msg  )  {
		return  TRUE;
	}


	//  一般墙也不显示. 2012/04/23
	if  (  pCurTalkerVar->iTalkerSubType  ==  CONST_talkerSubtype_onVWall  )  return  FALSE;


	//
	//  DLG_TALK_var  &  m_var  =  *pMgrVar;

	//  2013/02/28
	unsigned  short  usLayoutType_local  =  dlgTalk_get_usLayoutType_local(  hCurTalker  );

	//  2. 模式为对话框时显示
 	if  (  pMgrVar->av.taskInfo.bTaskExists
		||  pShadowMgr->resourcesInfo.bTaskExists_recvd_screenAndMediaFile  )  
	{
		if  (  usLayoutType_local  )  {
			if  (  usLayoutType_local  ==  CONST_usLayoutType_dialog  )  return  TRUE;
			return  FALSE;
		}
		if  (  pMgrVar->av.taskInfo.usLayoutType_starter  )  {
			if  (  pMgrVar->av.taskInfo.usLayoutType_starter  ==  CONST_usLayoutType_dialog  )  return  TRUE;
			return  FALSE;
		}
		//  2011/10/11
#if  0
		if  (  pCurTalkerVar->m_layout.usLayoutType_cur  ==  CONST_usLayoutType_conference  
			||  pCurTalkerVar->m_layout.usLayoutType_cur  ==  CONST_usLayoutType_resourceOnly  )  
		{
			return  FALSE;
		}
#endif
	}

	//  3. 全局会议墙不显示. 2012/04/10
	if  (  pCurTalkerVar->ucbOnGlobalVWall  )  return  FALSE;
	 

	//  4. 缺省策略设置
 	MC_VAR_isCli		*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  pProcInfo->cfg.policy.dlgTalk.snmpbShowMsgBox  ==  CONST_snmpTrue  )  return  TRUE;
	return  FALSE;
}


 //
 //  2012/09/05
  BOOL  dlgTalk_bMsgBoxShown(  HWND  hCurTalker  )
{
#ifdef  __DEBUG__
		#if  0
			traceLog(  _T(  "Test: dlgTalk_bShowPtz returns true"  )  );
			return  TRUE;
		#endif
#endif

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hCurTalker,  _T(  "dlgTalk_bShowPtz"  )  );
	if  (  !pCurTalkerVar  )  return  FALSE;


	return  IsWindow(  pCurTalkerVar->msgTool.hWnd_msgTool  );
  }



//  2012/09/05
  BOOL  dlgTalk_bPtzShown(  HWND  hCurTalker  )
{
#ifdef  __DEBUG__
		#if  0
			traceLog(  _T(  "Test: dlgTalk_bShowPtz returns true"  )  );
			return  TRUE;
		#endif
#endif

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hCurTalker,  _T(  "dlgTalk_bShowPtz"  )  );
	if  (  !pCurTalkerVar  )  return  FALSE;


	return  IsWindow(  pCurTalkerVar->ptzControl.hWnd_ptzControl  );
  }

//  2013/04/05
 BOOL  dlgTalk_bSubtitlesShown(  HWND  hCurTalker  )
{
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hCurTalker,  _T(  "dlgTalk_bShowSubtitles"  )  );
	if  (  !pCurTalkerVar  )  return  FALSE;

	return  IsWindow(  pCurTalkerVar->subtitles.hWnd_subtitles  );
}



 //  2014/10/03
 BOOL  dlgTalk_bShowBgWall(  HWND  hCurTalker  )
 {
	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurTalker,  _T(  "dlgTalk_bShowMsgBox"  )  );
	if  (  !pCurTalkerVar  )  return  FALSE;

	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	DLG_TALK_var  *  pMgrVar  =  NULL;
	if  (  !isTalkerShadowMgr(  pCurTalkerVar->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pCurTalkerVar->pShadowInfo;
		if  (  !pTalkerShadow  )  return  FALSE;
		pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr,  _T(  "dlgTalk_bShowMsgBox,  hMgr"  )  );
		if  (  !pMgrVar  )  return  FALSE;
		}
	else  {
		  pMgrVar  =  pCurTalkerVar;
	}
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;

	//
	if  (  !pMgrVar->av.taskInfo.bTaskExists  
		||  !pMgrVar->av.taskInfo.ucbVideoConference  
		||  !pMgrVar->av.taskInfo.ucbStarter  )  return  FALSE;

	//
	unsigned char  ucbShowBgWall  =  0;
	if  (  pMgrVar->av.taskInfo.ucbStarter  )  {
		//ucbShowBgWall  =  pMgrVar->m_layout.ucbShowBgWall_starter;
		ucbShowBgWall  =  pShadowMgr->bgWall.bgWallCfg.useBgWall  ||  pShadowMgr->bgWall.bgWallCfg.ucbAddBgWallToConf;
	}
	
	return  ucbShowBgWall;
 }


 //
//  2015/08/01
  BOOL  dlgTalk_bOfflineResShown(  HWND  hCurTalker  )
{
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hCurTalker,  _T(  "dlgTalk_bShowSubtitles"  )  );
	if  (  !pCurTalkerVar  )  return  FALSE;

	return  IsWindow(  pCurTalkerVar->offlineRes.hTool_offlineRes  );
}


 //  2014/10/03
 BOOL  dlgTalk_bShowPeerTool(  HWND  hCurTalker  )
 {
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	//
	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurTalker,  _T(  "dlgTalk_bShowMsgBox"  )  );
	if  (  !pCurTalkerVar  )  return  FALSE;

	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	DLG_TALK_var  *  pMgrVar  =  NULL;
	if  (  !isTalkerShadowMgr(  pCurTalkerVar->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pCurTalkerVar->pShadowInfo;
		if  (  !pTalkerShadow  )  return  FALSE;
		pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr,  _T(  "dlgTalk_bShowMsgBox,  hMgr"  )  );
		if  (  !pMgrVar  )  return  FALSE;
		}
	else  {
		  pMgrVar  =  pCurTalkerVar;
	}

	//
	if  (  pQyMc->iCustomId  !=   CONST_qyCustomId_bjyz   )  return  FALSE;

	//
	if  (  !pMgrVar->av.taskInfo.bTaskExists  
		||  !pMgrVar->av.taskInfo.ucbVideoConference  )  return  FALSE;
	//
	if  (  pMgrVar->av.taskInfo.ucbStarter  )  return  FALSE;

	//
	if  (  pMgrVar->av.taskInfo.usConfType  !=  CONST_usConfType_consult  )  return  FALSE;

	//
	BOOL  bShow  =  TRUE;
	
	return  bShow;
 }




  //  2014/07/14
__declspec(  dllexport  )  int  dlgTalk_set_newMsgArrives(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var,  BOOL  bOn  )
{
	int  iErr  =  -1;
	HWND  hMgr  =  NULL;
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	DLG_TALK_var  *  pMgrVar  =  NULL;

	if  (  !pm_var  ) return  -1;

	//
	if  (  isTalkerShadowMgr(  pm_var->addr  )  )  {
		pMgrVar  =  pm_var;
		}
	else  {
	      TALKER_shadow  *  pShadow;
		  pShadow  =  (  TALKER_shadow  *  )pm_var->pShadowInfo;									
		  if  (  !pShadow  )  goto  errLabel;
		  hMgr  =  pShadow->hMgr;
		  
		  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		  if  (  !pMgrVar  )  goto  errLabel;
	}

	
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;	
	if  (  !pShadowMgr  )  goto  errLabel;
		
	pShadowMgr->ucbNewMsgArrives  =  bOn;
	
	iErr  =  0;
errLabel:
	return  iErr;
}

__declspec(  dllexport  )   BOOL  dlgTalk_bNewMsgArrives(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var  )
{
	int  iErr  =  -1;
	HWND  hMgr  =  NULL;
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	DLG_TALK_var  *  pMgrVar  =  NULL;

	if  (  !pm_var  )  return  FALSE;

	if  (  isTalkerShadowMgr(  pm_var->addr  )  )  {
		pMgrVar  =  pm_var;
		}
	else  {
	      TALKER_shadow  *  pShadow;
		  pShadow  =  (  TALKER_shadow  *  )pm_var->pShadowInfo;									
		  if  (  !pShadow  )  goto  errLabel;
		  hMgr  =  pShadow->hMgr;
		  
		  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		  if  (  !pMgrVar  )  goto  errLabel;
	}

	
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;	
	if  (  !pShadowMgr  )  goto  errLabel;
		
	return  pShadowMgr->ucbNewMsgArrives;

errLabel:
	return  FALSE;
}




//
__declspec(  dllexport  )  BOOL  bTaskExists_sendingResource(  void  *  pMgrVar,  int  *  pnScreens,  int  *  pnMediaFiles,  int  *  pnMediaFiles_unresizable,  int  *  piW_unresizable,  int  *  piH_unresizable,  int  *  piTaskId_sendingResource  )
{
	BOOL  bRet  =  FALSE;

	INFO_sendResource  info  =  {0};
	bRet  =  bTaskExists_sendingResource1(  pMgrVar,  &info  );

	//
	if  (  pnScreens  )  *pnScreens  =  info.nScreens;
	if  (  pnMediaFiles  )  *pnMediaFiles  =  info.nMediaFiles;
	if  (  pnMediaFiles_unresizable  )  *pnMediaFiles_unresizable  =  info.nMediaFiles_unresizable;
	if  (  piW_unresizable  )  *piW_unresizable  =  info.iW_unresizable;
	if  (  piH_unresizable  )  *piH_unresizable  =  info.iH_unresizable;
	if  (  piTaskId_sendingResource  )  *piTaskId_sendingResource  =  info.iTaskId_sendingResource;

	return  bRet;
}


//
//  2010/12/23

__declspec(  dllexport  )  BOOL  bTaskExists_sendingResource1(  void  *  pMgrVarParam,  INFO_sendResource  *  pInfo  )
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL				bRet			=	FALSE;
	CCtxQyMc  *  pQyMc  =  g_pQyMc;
	CCtxQmc  *  pProcInfo  =  (  CCtxQmc  *  )pQyMc->get_pProcInfo();
	//
	if  (  !pMgrVarParam  )  return  FALSE;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )pMgrVarParam;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  FALSE;
	//
	MIS_CNT  *  pMisCnt  =  pMgrVar->pMisCnt;
	//
	//MIS_MSGU		*	pMsg			=	NULL;
	//Q_NODE			*	pQNode			=	NULL;
	int					nScreens		=	0;
	int					nMediaFiles		=	0;
	//  2015/03/12
	int					nMediaFiles_unresizable		=	0;
	//
	int					iW_unresizable		=	0;
	int					iH_unresizable		=	0;
	int					iTaskId_sendingResource  =  0;
	//
	BOOL				bExists_remoteAssist  =  FALSE;
	//
	//IM_CONTENTU		*	pContent		=	NULL;

	DLG_TALK_var  &  m_var  =  *pMgrVar;

	if  (  !m_var.m_pProcessQ  )  return  FALSE;
	GENERIC_Q		&	m_processQ		=	*m_var.m_pProcessQ;

#ifdef  __DEBUG__
		printQ_mis(  &m_processQ,  FALSE  );
#endif'

		if  (  !m_var.av.taskInfo.bTaskExists  )  return  false;
		QMC_TASK_INFO  *  pTaskInfo  =  ( QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
		if  (  !pTaskInfo  )  goto  errLabel;
		if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
		QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
		int  i;

		//
		if  (  pTc->shareScreen.bTaskExists  )  {
			nScreens  ++  ;
			if  (  nScreens  ==  1  )  {
				QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pTc->shareScreen.index_sharedObj  );
				if  (  pSharedObj  )  {
					int  index_capV  =  pSharedObj->iIndex_capBmp;
					CAP_procInfo_bmpU  *  pCapV  =  getCapBmpBySth(  pProcInfo,  index_capV,  0  );
					if  (  pCapV  )  {
						iW_unresizable  =  pCapV->common.compressVideo.vh_decompress.bih.biWidth;
						iH_unresizable  =  pCapV->common.compressVideo.vh_decompress.bih.biHeight;
					}
				}
			}
		}

		//
		if (pTc->shareMediaDevice.bTaskExists) {
			QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, pTc->shareMediaDevice.index_sharedObj);
			if (pSharedObj) {
				nMediaFiles++;
				if (isAvFlg_unresizable(pSharedObj->taskAvProps.v.ucAvFlg)) {
					nMediaFiles_unresizable++;
					if (nMediaFiles_unresizable == 1) {
						if (pSharedObj) {
							int  index_capV = pSharedObj->iIndex_capBmp;
							CAP_procInfo_bmpU* pCapV = getCapBmpBySth(pProcInfo, index_capV, 0);
							if (pCapV) {
								iW_unresizable = pCapV->common.compressVideo.vh_decompress.bih.biWidth;
								iH_unresizable = pCapV->common.compressVideo.vh_decompress.bih.biHeight;
							}
						}
					}
				}
			}
		}


	//
	if  (  pInfo  )  {
		pInfo->nScreens  =  nScreens;
		pInfo->nMediaFiles  =  nMediaFiles;
		//  2015/03/12
		pInfo->nMediaFiles_unresizable  =  nMediaFiles_unresizable;
		//
		if  (  (  nScreens  ==  1  &&  !nMediaFiles  )  
			||  (  !nScreens  &&  nMediaFiles  ==  1  &&  nMediaFiles_unresizable  ==  1  )
			)
		{
			pInfo->iW_unresizable  =  iW_unresizable;
			pInfo->iH_unresizable  =  iH_unresizable;
		}
		//
		//  2014/12/09
		pInfo->iTaskId_sendingResource  =  iTaskId_sendingResource;
		//
		pInfo->bExists_remoteAssist  =  bExists_remoteAssist;
	}
	//
	if  (  nScreens  ||  nMediaFiles  )  bRet  =  TRUE;
	
errLabel:

	return  bRet;
}




 

//
#if  0  
__declspec(  dllexport  )  BOOL  iibTaskExists_recvdResource(  void  *  pDLG_TALK_var,  int  *  pnScreens,  int  *  pnMediaFiles,  int  *  pnMediaFiles_unresizable,  int  *  piW_unresizable,  int  *  piH_unresizable,  int  *  piTaskId_recvdResource  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL				bRet			=	FALSE;
	DLG_TALK_var	&	m_var			=	*(  DLG_TALK_var  *  )pDLG_TALK_var;
	MIS_MSGU		*	pMsg			=	NULL;
	Q_NODE			*	pQNode			=	NULL;
	int					nScreens		=	0;
	int					nMediaFiles		=	0;
	int					nMediaFiles_unresizable  =  0;	//  2015/03/12
	//
	int					iW_unresizable		=	0;
	int					iH_unresizable		=	0;
	int					iTaskId_recvdResource		=  0;
	//
	IM_CONTENTU		*	pContent					=	NULL;

	if  (  !m_var.m_pProcessQ  )  return  FALSE;
	GENERIC_Q		&	m_processQ		=	*m_var.m_pProcessQ;

#ifdef  __DEBUG__
		printQ_mis(  &m_processQ,  FALSE  );
#endif

	for  (  pQNode  =  m_processQ.front.pNext;  pQNode;  pQNode  =  pQNode->pNext  )  {
		pMsg  =  (  MIS_MSGU  *  )pQNode->qElemMemory.m_pBuf;
		if  (  pMsg->uiType  !=  CONST_misMsgType_task  )  continue;
		if  (  !bTaskAlive(  pMsg->task.iStatus  )  )  continue;
		//
		if  (  pMsg->task.data.route.idInfo_from.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  )  continue;
		//
		pContent  =  (  IM_CONTENTU  *  )pMsg->task.data.buf;
		if  (  pContent->uiType  !=  CONST_imCommType_transferAvInfo  )  continue;
		//
		switch  (  pContent->transferAvInfo.uiTaskType  )  {
				case  CONST_imTaskType_shareScreen:
				case  CONST_imTaskType_remoteAssist:	//  2017/08/23
					  iTaskId_recvdResource  =  pMsg->task.iTaskId;
					  nScreens  ++  ;
					  if  (  nScreens  ==  1  )  {
						  iW_unresizable  =  pContent->transferAvInfo.tranInfo.video.vh_decompress.bih.biWidth;
						  iH_unresizable  =  pContent->transferAvInfo.tranInfo.video.vh_decompress.bih.biHeight;
					  }
					  break;
				case  CONST_imTaskType_shareMediaFile:
					  iTaskId_recvdResource  =  pMsg->task.iTaskId;
					  nMediaFiles  ++  ;
					  //
					  if  (  isAvFlg_unresizable(  pContent->transferAvInfo.tranInfo.taskAvProps.v.ucAvFlg  )  )  {
						  nMediaFiles_unresizable  ++  ;
						  //
						  if  (  nMediaFiles_unresizable  ==  1  )  {
							  iW_unresizable  =  pContent->transferAvInfo.tranInfo.video.vh_decompress.bih.biWidth;						
							  iH_unresizable  =  pContent->transferAvInfo.tranInfo.video.vh_decompress.bih.biHeight;
						  }
					  }
					  break;
				default:
						break;
		}		
	}

	if  (  pnScreens  )  *pnScreens  =  nScreens;
	if  (  pnMediaFiles  )  *pnMediaFiles  =  nMediaFiles;
	//  2015/03/12
	if  (  pnMediaFiles_unresizable  )  *pnMediaFiles_unresizable  =  nMediaFiles_unresizable;
	//
	if  (  (  nScreens  ==  1  &&  !nMediaFiles  )  
		||  (  !nScreens  &&  nMediaFiles  ==  1  &&  nMediaFiles_unresizable  ==  1  )
		)
	{
		if  (  piW_unresizable  )  *piW_unresizable  =  iW_unresizable;
		if  (  piH_unresizable  )  *piH_unresizable  =  iH_unresizable;
	}
	//  2014/12/09
	if  (  piTaskId_recvdResource  )  *piTaskId_recvdResource  =  iTaskId_recvdResource;
	//
	if  (  nScreens  ||  nMediaFiles  )  bRet  =  TRUE;
	
	return  bRet;
 }
#endif


//
//  2010/12/23
__declspec(  dllexport  )  BOOL  bTaskExists_recvResource(  void  *  pMgrVar,  int  *  pnScreens,  int  *  pnMediaFiles,  int  *  pnMediaFiles_unresizable,  int  *  piW_unresizable,  int  *  piH_unresizable,  int  *  piTaskId_recvdResource  )
{
	INFO_recvResource  param  =  {0};
	
	//
	BOOL  bRet  =  bTaskExists_recvResource1(  pMgrVar,  &param  );

	//
	if  (  pnScreens  )  *pnScreens  =  param.nScreens;
	if  (  pnMediaFiles  )  *pnMediaFiles  =  param.nMediaFiles;
	if  (  pnMediaFiles_unresizable  )  *pnMediaFiles_unresizable  =  param.nMediaFiles_unresizable;
	if  (  piW_unresizable  )  *piW_unresizable  =  param.iW_unresizable;
	if  (  piH_unresizable  )  *piH_unresizable  =  param.iH_unresizable;
	if  (  piTaskId_recvdResource  )  *piTaskId_recvdResource  =  param.iTaskId_recvdResource;

	//
	return  bRet;
}

//
#if  0
__declspec(  dllexport  )  BOOL  old_bTaskExists_recvResource1(  void  *  pMgrVarParam,  INFO_recvResource  *  pParam  )  //  int  *  pnScreens,  int  *  pnMediaFiles,  int  *  pnMediaFiles_unresizable,  int  *  piW_unresizable,  int  *  piH_unresizable,  int  *  piTaskId_recvdResource  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL				bRet						=	FALSE;
	if  (  !pMgrVarParam  )  return  FALSE;
	//
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )pMgrVarParam;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  FALSE;
	//
	DLG_TALK_var	&	m_var						=	*(  DLG_TALK_var  *  )pMgrVar;
	MIS_MSGU		*	pMsg						=	NULL;
	Q_NODE			*	pQNode						=	NULL;
	//
	INFO_recvResource	info_recv  = {0};
	//
	//
	IM_CONTENTU		*	pContent					=	NULL;

	//
	if  (  !m_var.m_pProcessQ  )  return  FALSE;
	GENERIC_Q		&	m_processQ		=	*m_var.m_pProcessQ;


	//
	for  (  pQNode  =  m_processQ.front.pNext;  pQNode;  pQNode  =  pQNode->pNext  )  {
		pMsg  =  (  MIS_MSGU  *  )pQNode->qElemMemory.m_pBuf;
		if  (  pMsg->uiType  !=  CONST_misMsgType_task  )  continue;
		if  (  !bTaskAlive(  pMsg->task.iStatus  )  )  continue;
		//
		if  (  pMsg->task.data.route.idInfo_from.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  )  continue;
		//
		pContent  =  (  IM_CONTENTU  *  )pMsg->task.data.buf;
		if  (  pContent->uiType  !=  CONST_imCommType_transferAvInfo  )  continue;
		//
		switch  (  pContent->transferAvInfo.uiTaskType  )  {
				case  CONST_imTaskType_shareScreen:
				case  CONST_imTaskType_remoteAssist:	//  2017/08/23
					  info_recv.iTaskId_recvdResource  =  pMsg->task.iTaskId;
					  info_recv.nScreens  ++  ;
					  if  (  info_recv.nScreens  ==  1  )  {
						  info_recv.iW_unresizable  =  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biWidth;
						  info_recv.iH_unresizable  =  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biHeight;
					  }
					  //  2017/08/23
					  if  (  pContent->transferAvInfo.uiTaskType  ==  CONST_imTaskType_remoteAssist  )  {
						  info_recv.bExists_remoteAssist  =  TRUE;
					  }
					  //
					  int  i;
					  for  (  i  =  0;  i  <  mycountof(  info_recv.screenTasks  );  i  ++  )  {
						   if  (  pMsg->task.data.route.idInfo_from.ui64Id  ==  info_recv.screenTasks[i].idInfo_sender.ui64Id  )  break;
					  }
					  if  (  i  ==  mycountof(  info_recv.screenTasks  )  )  {
						  for  (  i  =  0;  i  <  mycountof(  info_recv.screenTasks  );  i  ++  )  {
							   if  (  !info_recv.screenTasks[i].idInfo_sender.ui64Id  )  break;
						  }
						  if  (  i  <  mycountof(  info_recv.screenTasks  )  )  {
							  INFO_recv_screenTask  *  pMem  =  &info_recv.screenTasks[i];
							  pMem->idInfo_sender.ui64Id  =  pMsg->task.data.route.idInfo_from.ui64Id;
						  }
					  }
					  break;
				case  CONST_imTaskType_shareMediaFile:
					  info_recv.iTaskId_recvdResource  =  pMsg->task.iTaskId;
					  info_recv.nMediaFiles  ++  ;
					  //
					  if  (  isAvFlg_unresizable(  pContent->transferAvInfo.ass.tranInfo.taskAvProps.v.ucAvFlg  )  )  {
						  info_recv.nMediaFiles_unresizable  ++  ;
						  //
						  if  (  info_recv.nMediaFiles_unresizable  ==  1  )  {
							  info_recv.iW_unresizable  =  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biWidth;						
							  info_recv.iH_unresizable  =  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biHeight;
						  }
					  }
					  break;
				default:
						break;
		}		
	}

	//
#if  0
	pParam->nScreens  =  nScreens;
	pParam->nMediaFiles  =  nMediaFiles;
	//  2015/03/12
	pParam->nMediaFiles_unresizable  =  nMediaFiles_unresizable;
	//
	if  (  (  nScreens  ==  1  &&  !nMediaFiles  )  
		||  (  !nScreens  &&  nMediaFiles  ==  1  &&  nMediaFiles_unresizable  ==  1  )
		)
	{
		pParam->iW_unresizable  =  iW_unresizable;
		pParam->iH_unresizable  =  iH_unresizable;
	}
	//  2014/12/09
	pParam->iTaskId_recvdResource  =  iTaskId_recvdResource;
	//  2017/08/23
	pParam->bExists_remoteAssist  =  bExists_remoteAssist;
#endif
	if  (  pParam  )  {
		*pParam  =  info_recv;
	}
	//
	if  (  info_recv.nScreens  ||  info_recv.nMediaFiles  )  bRet  =  TRUE;
	
	return  bRet;
 }
#endif


#if 0
__declspec(  dllexport  )  BOOL  iibTaskExists_recvResource1(  void  *  pMgrVarParam,  INFO_recvResource  *  pParam  )  //  int  *  pnScreens,  int  *  pnMediaFiles,  int  *  pnMediaFiles_unresizable,  int  *  piW_unresizable,  int  *  piH_unresizable,  int  *  piTaskId_recvdResource  )
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL				bRet						=	FALSE;
	if  (  !pMgrVarParam  )  return  FALSE;
	//
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )pMgrVarParam;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  FALSE;
	//
	DLG_TALK_var	&	m_var						=	*(  DLG_TALK_var  *  )pMgrVar;
	//MIS_MSGU		*	pMsg						=	NULL;
	Q_NODE			*	pQNode						=	NULL;
	//
	INFO_recvResource	info_recv  = {0};
	//
	//
	//IM_CONTENTU		*	pContent					=	NULL;

	//
	CCtxQmc  *  pProcInfo  =  QY_GET_procInfo_isCli();
	MIS_CNT  *  pMisCnt  =  m_var.pMisCnt;


	//
	if  (  !m_var.m_pProcessQ  )  return  FALSE;
	GENERIC_Q		&	m_processQ		=	*m_var.m_pProcessQ;

	if  (  !m_var.av.taskInfo.bTaskExists  )  return  false;
		QMC_TASK_INFO  *  pTaskInfo  =  ( QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
		if  (  !pTaskInfo  )  goto  errLabel;
		if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
		QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
		int  i;

			for  (  i  =  0;  i  <  pTc->videoConference.usCntLimit_activeMems_from;  i  ++  )  {
			DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[i];
			//
			if  (  pActiveMem_from->avStream.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  continue;
	
		//
			switch  (  pActiveMem_from->avStream.obj.resObj.uiObjType  )  {
				case  CONST_objType_screen:
				//case  CONST_imTaskType_remoteAssist:	//  2017/08/23
					  info_recv.iTaskId_recvdResource  =  0;//pMsg->task.iTaskId;
					  info_recv.nScreens  ++  ;
					  if  (  info_recv.nScreens  ==  1  )  {
						  info_recv.iW_unresizable  =  pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress.bih.biWidth;
						  info_recv.iH_unresizable  =  pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress.bih.biHeight;
					  }
					  //  2017/08/23
#if  0
					  if  (  pContent->transferAvInfo.uiTaskType  ==  CONST_imTaskType_remoteAssist  )  
					  {
						  info_recv.bExists_remoteAssist  =  TRUE;
					  }
#endif
					  //
					  int  i;
					  for  (  i  =  0;  i  <  mycountof(  info_recv.screenTasks  );  i  ++  )  {
						  if  (  pActiveMem_from->avStream.idInfo.ui64Id  ==  info_recv.screenTasks[i].idInfo_sender.ui64Id  )  break;
					  }
					  if  (  i  ==  mycountof(  info_recv.screenTasks  )  )  {
						  for  (  i  =  0;  i  <  mycountof(  info_recv.screenTasks  );  i  ++  )  {
							   if  (  !info_recv.screenTasks[i].idInfo_sender.ui64Id  )  break;
						  }
						  if  (  i  <  mycountof(  info_recv.screenTasks  )  )  {
							  INFO_recv_screenTask  *  pMem  =  &info_recv.screenTasks[i];
							  pMem->idInfo_sender.ui64Id  =  pActiveMem_from->avStream.idInfo.ui64Id;
						  }
					  }
					  break;
				case  CONST_imTaskType_shareMediaFile:
					  info_recv.iTaskId_recvdResource  =  0;//pMsg->task.iTaskId;
					  info_recv.nMediaFiles  ++  ;
					  //
					  if  (  isAvFlg_unresizable(  pActiveMem_from->avStream.obj.tranInfo.taskAvProps.v.ucAvFlg  )  )  {
						  info_recv.nMediaFiles_unresizable  ++  ;
						  //
						  if  (  info_recv.nMediaFiles_unresizable  ==  1  )  {
							  info_recv.iW_unresizable  =  pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress.bih.biWidth;						
							  info_recv.iH_unresizable  =  pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress.bih.biHeight;
						  }
					  }
					  break;
				default:
						break;
		}		
	}

	//
	if  (  pParam  )  {
		*pParam  =  info_recv;
	}
	//
	if  (  info_recv.nScreens  ||  info_recv.nMediaFiles  )  bRet  =  TRUE;

errLabel:

	return  bRet;
 }
#endif



 //
__declspec(dllexport)  BOOL  bTaskExists_recvResource1(void* pMgrVarParam, INFO_recvResource* pParam)  //  int  *  pnScreens,  int  *  pnMediaFiles,  int  *  pnMediaFiles_unresizable,  int  *  piW_unresizable,  int  *  piH_unresizable,  int  *  piTaskId_recvdResource  )
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL				bRet = FALSE;
	if (!pMgrVarParam)  return  FALSE;
	//
	DLG_TALK_var* pMgrVar = (DLG_TALK_var*)pMgrVarParam;
	if (!isTalkerShadowMgr(pMgrVar->addr))  return  FALSE;
	//
	DLG_TALK_var& m_var = *(DLG_TALK_var*)pMgrVar;
	//MIS_MSGU		*	pMsg						=	NULL;
	Q_NODE* pQNode = NULL;
	//
	INFO_recvResource	info_recv = { 0 };
	//
	//
	//IM_CONTENTU		*	pContent					=	NULL;

	//
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = m_var.pMisCnt;


	//
	if (!m_var.m_pProcessQ)  return  FALSE;
	GENERIC_Q& m_processQ = *m_var.m_pProcessQ;

	if (!m_var.av.taskInfo.bTaskExists)  return  false;

	return  bTaskExists_recvResource1(m_var.av.taskInfo.iIndex_taskInfo, pParam);

}



 //
 __declspec(dllexport)  BOOL  bTaskExists_recvResource1(int iIndex_taskInfo, INFO_recvResource* pParam)  //  int  *  pnScreens,  int  *  pnMediaFiles,  int  *  pnMediaFiles_unresizable,  int  *  piW_unresizable,  int  *  piH_unresizable,  int  *  piTaskId_recvdResource  )
 {
	 //AFX_MANAGE_STATE(AfxGetStaticModuleState());

	 BOOL				bRet = FALSE;
	 //if (!pMgrVarParam)  return  FALSE;
	 //
	 //DLG_TALK_var* pMgrVar = (DLG_TALK_var*)pMgrVarParam;
	 //if (!isTalkerShadowMgr(pMgrVar->addr))  return  FALSE;
	 //
	 //DLG_TALK_var& m_var = *(DLG_TALK_var*)pMgrVar;
	 //MIS_MSGU		*	pMsg						=	NULL;
	 //Q_NODE* pQNode = NULL;
	 //
	 INFO_recvResource	info_recv = { 0 };
	 //
	 //
	 //IM_CONTENTU		*	pContent					=	NULL;

	 //
	 CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	 MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));// m_var.pMisCnt;


	 //
	 //if (!m_var.m_pProcessQ)  return  FALSE;
	 //GENERIC_Q& m_processQ = *m_var.m_pProcessQ;

	 //if (!m_var.av.taskInfo.bTaskExists)  return  false;
	 QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, iIndex_taskInfo);
	 if (!pTaskInfo)  goto  errLabel;
	 if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  goto  errLabel;
	 QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
	 int  i;

	 for (i = 0; i < pTc->videoConference.usCntLimit_activeMems_from; i++) {
		 DLG_TALK_videoConferenceActiveMemFrom* pActiveMem_from = &pTc->videoConference.activeMems_from[i];
		 //
		 if (pActiveMem_from->avStream.idInfo.ui64Id == pMisCnt->idInfo.ui64Id)  continue;

		 //
		 switch (pActiveMem_from->avStream.obj.resObj.uiObjType) {
		 case  CONST_objType_screen:
			 //case  CONST_imTaskType_remoteAssist:	//  2017/08/23
			 info_recv.iTaskId_recvdResource = 0;//pMsg->task.iTaskId;
			 info_recv.nScreens++;
			 if (info_recv.nScreens == 1) {
				 info_recv.iW_unresizable = pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress.bih.biWidth;
				 info_recv.iH_unresizable = pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress.bih.biHeight;
			 }
			 //  2017/08/23
#if  0
			 if (pContent->transferAvInfo.uiTaskType == CONST_imTaskType_remoteAssist)
			 {
				 info_recv.bExists_remoteAssist = TRUE;
			 }
#endif
			 //
			 int  i;
			 for (i = 0; i < mycountof(info_recv.screenTasks); i++) {
				 if (pActiveMem_from->avStream.idInfo.ui64Id == info_recv.screenTasks[i].idInfo_sender.ui64Id)  break;
			 }
			 if (i == mycountof(info_recv.screenTasks)) {
				 for (i = 0; i < mycountof(info_recv.screenTasks); i++) {
					 if (!info_recv.screenTasks[i].idInfo_sender.ui64Id)  break;
				 }
				 if (i < mycountof(info_recv.screenTasks)) {
					 INFO_recv_screenTask* pMem = &info_recv.screenTasks[i];
					 pMem->idInfo_sender.ui64Id = pActiveMem_from->avStream.idInfo.ui64Id;
				 }
			 }
			 break;
		 case  CONST_imTaskType_shareMediaFile:
			 info_recv.iTaskId_recvdResource = 0;//pMsg->task.iTaskId;
			 info_recv.nMediaFiles++;
			 //
			 if (isAvFlg_unresizable(pActiveMem_from->avStream.obj.tranInfo.taskAvProps.v.ucAvFlg)) {
				 info_recv.nMediaFiles_unresizable++;
				 //
				 if (info_recv.nMediaFiles_unresizable == 1) {
					 info_recv.iW_unresizable = pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress.bih.biWidth;
					 info_recv.iH_unresizable = pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress.bih.biHeight;
				 }
			 }
			 break;
		 default:
			 break;
		 }
	 }

	 //
	 if (pParam) {
		 *pParam = info_recv;
	 }
	 //
	 if (info_recv.nScreens || info_recv.nMediaFiles)  bRet = TRUE;

 errLabel:

	 return  bRet;
 }



   //  2014/12/16
  __declspec(  dllexport  )  int  dlgTalk_getCurSubtitlesCfg(  HWND  hDlgTalk,  SUBTITLES_cfg  *  pCfg  )	
  {
	 int						iErr		=	-1;
	 DLG_TALK_var			*	pDlgTalkVar  =  NULL;
	 CHelp_getDlgTalkVar		help_getDlgTalkVar;
	 CHelp_getDlgTalkVar		help_getDlgTalkVar_mgr;
	 
	 DLG_TALK_var  *  pMgrVar  =  NULL;
	
	 if  (  !pCfg  )  return  -1;

	 pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlgTalk  );
	 if  (  !pDlgTalkVar  )  return  -1;

	 pMgrVar  =  pDlgTalkVar;
	 if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  {
		 TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
		 if  (  !pShadow  )  goto  errLabel;
		 HWND  hMgr  =  pShadow->hMgr;
		 pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		 if  (  !pMgrVar  )  goto  errLabel;
	 }

	 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	 if  (  !pShadowMgr  )  goto  errLabel;

	 memcpy(  pCfg,  &pShadowMgr->subtitles.d3dConf,  sizeof(  pCfg[0]  )  );

	 iErr  =  0;
errLabel:
	 return  iErr;

  }


    
   //  2014/12/16
  __declspec(  dllexport  )  int  dlgTalk_getSubtitleMsgs(  HWND  hDlgTalk,  SUBTITLE_msgs  *  pMsgs  )	
  {
	 int						iErr		=	-1;
	 DLG_TALK_var			*	pDlgTalkVar  =  NULL;
	 CHelp_getDlgTalkVar		help_getDlgTalkVar;
	 CHelp_getDlgTalkVar		help_getDlgTalkVar_mgr;
	 
	 DLG_TALK_var  *  pMgrVar  =  NULL;
	
	 if  (  !pMsgs  )  return  -1;

	 pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlgTalk  );
	 if  (  !pDlgTalkVar  )  return  -1;

	 pMgrVar  =  pDlgTalkVar;
	 if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  {
		 TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
		 if  (  !pShadow  )  goto  errLabel;
		 HWND  hMgr  =  pShadow->hMgr;
		 pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		 if  (  !pMgrVar  )  goto  errLabel;
	 }

	 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	 if  (  !pShadowMgr  )  goto  errLabel;

	 memcpy(  pMsgs,  &pShadowMgr->msg.msgs,  sizeof(  pMsgs[0]  )  );

	 iErr  =  0;
errLabel:
	 return  iErr;

  }







   int  tmpHandler_fillTmpGrpMemQ(  void  *  p0,  void  *  p1,  void  *  pQElem  )
{
	int				iErr		=	-1;
	//  p0
	GENERIC_Q	*	pTmpGrpMemQ	=	(  GENERIC_Q  *  )p1;
	//
	if  (  qPostMsg(  pQElem,  sizeof(  MSGR_ADDR  ),  pTmpGrpMemQ,  _T(  "tmp_fillTmpGrpMemQ"  )))  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;
}


   __declspec(dllexport) BOOL  dlgTalk_bSetDlgInfo(  HWND  hDlgTalk,  DLG_TALK_var  &  m_var,  MSGR_ADDR  *  pAddr,  GENERIC_Q  *  pTmpGrpMemQ,  int  iTalkUsage,  int  iTalkerSubType,  BOOL  bNeedNotShowWnd,  HWND  hFore  )
{
	 BOOL						bRet		=	FALSE;
	 QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	 MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 

	 if  (  !pAddr  )  return  FALSE;
	 if  (  !bMessengerIdValid(  &pAddr->idInfo  )  )  return  FALSE;
	 if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	 
	 
	 //
	 m_var.usMaxDisplayedTasks  =  pQyMc->cfg.usMaxDisplayedTasksInDlgTalk;
	 //
	 memcpy(  &m_var.addr,  pAddr,  sizeof(  m_var.addr  )  );

	 //
	 m_var.ucbGuest  =  bMessengerGuest(  m_var.addr.uiObjType  );
	 if  (  m_var.ucbGuest  )  {
         m_var.addr.uiLogonId  =  pAddr->uiLogonId;
	 }
	 //
	 if  (  pTmpGrpMemQ  )  {
		 if  (  m_var.bTmpGrpMemQInited  )  {
			 exitGenericQ(  &m_var.tmpGrpMemQ  );  m_var.bTmpGrpMemQInited  =  FALSE;
		 }
		 if  (  initGenericQ(  _T(  "tmpGrpMemQ"  ),  NULL,  0,  CONST_uiMaxQNodes_tmpGrpMemQ,  mymalloc,  myfree,  &m_var.tmpGrpMemQ  )  )  goto  errLabel;
		 m_var.bTmpGrpMemQInited  =  TRUE;
		 //
		 if  (  qTraverse(  pTmpGrpMemQ,  tmpHandler_fillTmpGrpMemQ,  0,  &m_var.tmpGrpMemQ  )  )  goto  errLabel;
	 }

	 //
	 m_var.iTalkUsage  =  iTalkUsage;
	 //  2012/04/30
	 m_var.iTalkerSubType  =  iTalkerSubType;

	 //
	 m_var.guiData.param.bNeedNotShowWnd  =  bNeedNotShowWnd;		//  2010/04/22
	 m_var.hFore  =  hFore;	//  2007/09/09


	 //  ¼ÆËãÒ»ÏÂºÍmisServNameÏà¹ØµÄpMisCnt
	 if  (  !(  m_var.pMisCnt  =  getMisCntByName(  pProcInfo,  m_var.addr.misServName  )  )  )  goto  errLabel;
	 //


	 switch  (  m_var.addr.uiObjType  )  {
			 case  CONST_objType_phoneGuest:
			 case  CONST_objType_tmpGrp:
				   break;
			 default:
					 //  Í¨³£µÄidInfo²»ÄÜÎª0
					 if  (  !m_var.addr.idInfo.ui64Id  )  {
						 traceLogA(  "CDlgTalk::bSetDlgInfo(  ) failed, idInfo is 0"  );
						 goto  errLabel;
					 }
				     //  ¼ì²éÒ»ÏÂ£¬²»ÄÜ¶Ô±¾ÈËÁÄÌì
				     if  (  m_var.addr.idInfo.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  &&  !m_var.addr.uiDevType  )  {
						 traceLogA(  "CDlgTalk::bSetDlgInfo(  ) failed: idInfo is me, can't be talked to"  );  goto  errLabel;
					 }
					 break;
	 }

	 //  2013/07/31. 用来标识talker类实例, 仅用来debug
	 //m_var.addr.iNo_debug  =  getuiNextTranNo(  0,  0,  0  );

	 //
	 bRet  =  TRUE;

errLabel:

	 if  (  bRet  )  {
		 m_var.guiData.bInfoSet  =  TRUE;
	 }

	 return  bRet;
}

 //  2013/02/28
  __declspec(  dllexport  )  unsigned  short  dlgTalk_get_usLayoutType_local(  HWND  hDlgTalk  )
 {
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	unsigned  short  usLayoutType_local		=	0;


	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	
	CHelp_getDlgTalkVar				help_getDlgTalkVar;
	DLG_TALK_var				*	pm_var		=		(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk,  _T(  "dlgTalk_get_usLayoutType_local"  )  );
	 if  (  !pm_var  )  goto  errLabel;
	 	 
	 
	 //  2013/02/28
	DLG_TALK_var  *  pMgrVar  =  pm_var;
	if  (  !isTalkerShadowMgr(  pm_var->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pm_var->pShadowInfo;
		if  (  !pTalkerShadow  )  goto  errLabel;
		if  (  !IsWindow(  pTalkerShadow->hMgr  )  )  goto  errLabel;
		//  hMgr  =  pTalkerShadow->hMgr;		//  2013/02/15
		pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr,  _T(  "dlgTalk_get_usLayoutType_local, hMgr"  )  );
		if  (  !pMgrVar  )  goto  errLabel;
	}
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;	
	if  (  !pShadowMgr  )  goto  errLabel;

	usLayoutType_local  =  pShadowMgr->av.usLayoutType_local;

errLabel:
	return  usLayoutType_local;
 }

  //
  __declspec(  dllexport  ) MIS_MSG_TASK  *  findTaskInProcessQ(  void  *  pDLG_TALK_var,  int  iTaskId,  BOOL  bNextAv,  BOOL  bToShareScreen  )
{
	MIS_MSGU		*	pMsg	=	NULL;
	Q_NODE			*	pQNode	=	NULL;
	
	DLG_TALK_var  &	m_var  =  *(  DLG_TALK_var  *  )pDLG_TALK_var;
	if  (  !m_var.m_pProcessQ  )  return  NULL;
	GENERIC_Q		&	m_processQ	=	*m_var.m_pProcessQ;

	for  (  pQNode  =  m_processQ.front.pNext;  pQNode;  pQNode  =  pQNode->pNext  )  {
		 pMsg	=	(  MIS_MSGU  *  )pQNode->qElemMemory.m_pBuf;
		 if  (  pMsg->uiType  ==  CONST_misMsgType_task  )  {
			 if  (  iTaskId  )  {
				 if  (  iTaskId  ==  pMsg->task.iTaskId  )  break;				 
				}
			 else  if  (  bNextAv  )  {
					   if  (  pMsg->task.uiTaskType  ==  CONST_imTaskType_transferAvInfo  
						   &&  bTaskAlive(  pMsg->task.iStatus  )  )  
					   {
						   break;
					   }
					   }
			 else  if  (  bToShareScreen  )  {		//  2011/03/12
				       if  (  (  pMsg->task.uiTaskType  ==  CONST_imTaskType_shareScreen  
						   ||  pMsg->task.uiTaskType  ==  CONST_imTaskType_remoteAssist		//  2015/11/05
						   )
						   &&  bTaskAlive(  pMsg->task.iStatus  )
						   &&  pMsg->task.data.route.idInfo_from.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  )
					   {
						   break;
					   }
			 }
		 }
	}
	if  (  !pQNode  )  return  NULL;

	return  &pMsg->task;
}




 //
__declspec(  dllexport  )  int  tmpHandler_bRemoveMsgInProcessQ(  void  *  p0,  void  *  p1, void  *  pMsgParam  )
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr					=	-1;
	HWND				hDlgTalk				=	(  HWND  )p0;
	PARAM_PROC_ROW	*	pParam					=	(  PARAM_PROC_ROW  *  )p1;
	MIS_MSGU		*	pMsg					=	(  MIS_MSGU  *  )pMsgParam;
	QY_MC			*	pQyMc					=	QY_GET_GBUF(  );

	if  (  !pParam  ||  !pMsg  )  return  -1;
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pDlgTalkVar				=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk,  _T(  "tmpHandler_bRemoveMsgInProcessQ"  )  );
	if  (  !pDlgTalkVar  )  {
		#ifdef  __DEBUG__
				MACRO_qyAssert(  0,  _T(  "tmpHandler_bRemoveMsgInProcessQ failed, hDlgTalk err"  )  );
		#endif
		return  -1;
	}

	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_talk:  
				  if  (  !pMsg->talk.tStartTime_processed  )  break;
			
				  if  (  pDlgTalkVar->nMsgTalks_processed_inProcessQ  <  50  )  {		//  保留到50个消息
					  pParam->nMsgTalks_processed_inProcessQ  ++  ;
					  break;
				  }
				  pDlgTalkVar->nMsgTalks_processed_inProcessQ  --  ;

				  iErr  =  1;  goto  errLabel;
				  break;
			case  CONST_misMsgType_task:
				  if  (  pParam->iTaskId  )  {
					  if  (  pMsg->task.iTaskId  ==  pParam->iTaskId  )  {
						  iErr  =  1;  goto  errLabel;
					  }
					  break;
				  }

				  if  (  !pMsg->task.tStartTime_processed  )  break;

				  if  (  !pMsg->task.iTaskId  )  {
					  iErr  =  1;  goto  errLabel;
				  }
				  break;
			case  CONST_misMsgType_input:	//  2014/09/05
				  if  (  !pMsg->input.tStartTime_processed  )  break;
				  iErr  =  1;  goto  errLabel;
				  break;

			case  CONST_misMsgType_taskStatus:
				  if  (  !pMsg->taskStatus.tStartTime_processed  )  break;
				  iErr  =  1;  goto  errLabel;
				  break;
			case  CONST_misMsgType_notifyTaskEnd_qmc:
				  if  (  !pMsg->notifyTaskEnd.tStartTime_processed  )  break;
				  iErr  =  1;  goto  errLabel;
				  break;
			case  CONST_misMsgType_applyForWork:		//  2011/04/08
				  if  (  !pMsg->applyForWork.tStartTime_processed  )  break;
				  iErr  =  1;  goto  errLabel;
				  break;
			case  CONST_misMsgType_applyForTalkerShadow_qmc:	//  2012/04/23
				  if  (  !pMsg->applyForTalkerShadow_qmc.tStartTime_processed  )  break;
				  iErr  =  1;  goto  errLabel;
				  break;

			default:
					#ifdef  __DEBUG__
						    traceLogA(  "tmp_bRemoveMsgInProcessQ: unprocessed msg, %d",  pMsg->uiType  );
							assert(  0  );
					#endif
					break;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}


//
__declspec(  dllexport  )  int  dlgTalk_re_acceptTask(  HWND  hDlgTalk_mgr,  int  iTaskId  )
{
	int  iErr  =  -1;
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk_mgr  );

	if  (  !pVar  )  return  -1;
	if  (  !isTalkerShadowMgr(  pVar->addr  )  )  return  -1;
	if  (  !iTaskId  )  return  -1;

	//
	DLG_TALK_var  *  pMgrVar  = pVar;
						  
	//	
	{				
		//		
		PARAM_PROC_ROW	param;									
		memset(  &param,  0,  sizeof(  param  )  );
		param.iTaskId  =  iTaskId;
		qRemoveMsg(  pMgrVar->m_pProcessQ,  tmpHandler_bRemoveMsgInProcessQ,  hDlgTalk_mgr,  &param  );						  
	}

	iErr  =  0;
	return  iErr;

}


//
__declspec(  dllexport  )  BOOL  canJoinInBgWall(  HWND  hTalkerMgr,  void  *  pDLG_TALK_var  )
{
	BOOL  bRet  =  FALSE;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )pDLG_TALK_var;
	if  (  !pMgrVar  )  goto  errLabel;

	//
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;
	//
	if  (  pShadowMgr->av.joinInBgWall.idcRet_joinInBgWall  !=  ID_qyOk  )  {
		goto  errLabel;
	}

	//
	bRet  =  TRUE;

errLabel:
	return  bRet;
}



//
__declspec(  dllexport  )  int  dlgTalk_doCmd_joinInBgWall(  HWND  hTalkerMgr  )
{	
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;	  
	TCHAR  tBuf[128]  =  _T(  ""  );	
	//
	DLG_TALK_var	*	pMgrVar  =  NULL;	

	pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  hTalkerMgr,  _T(  "dlgTalk_calculateLayout"  )  );
	if  (  !pMgrVar  )  goto  errLabel;		
				  
				  
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	//		
	if  (  pMgrVar->av.taskInfo.bTaskExists  &&  pMgrVar->av.taskInfo.ucbStarter  )  {
				
		//pMgrVar->m_layout.ucbShowBgWall_starter  =  !pMgrVar->m_layout.ucbShowBgWall_starter;
		
		
		}		
	else  {

		  //
		  //if  (  pShadowMgr->av.joinInBgWall.idcRet_joinInBgWall  !=  ID_qyOk  )  
		  if  (  !canJoinInBgWall(  hTalkerMgr,  pMgrVar  )  )
		  {
		
			  //
			  pShadowMgr->av.joinInBgWall.idcRet_joinInBgWall  =  ID_qyOk;
					   //					   	
					   //if  (  idcRet  ==  ID_qyOk  )  
					   {	//  
							#ifdef  __DEBUG__
									//traceLog(  _T(  "调用声音独占的功能"  )  );																
							#endif
							//
							pFuncs->pf_setCurSharedObjUsr_localAv(  pProcInfo,  pMgrVar->av.iIndex_sharedObj_localAv,  pMgrVar->av.iIndex_usr_localAv  );  							   
							safeTcsnCpy(  getResStr(  0,  &pQyMc->cusRes,  	CONST_resId_notJoinInBgWall  ),  tBuf,  mycountof(  tBuf  )  ); 
					   }
					   //  2016/03/27
					   setSlaveStreamOn(  hTalkerMgr,  TRUE  );
					   }			
	
		  else  {
					     pShadowMgr->av.joinInBgWall.idcRet_joinInBgWall  =  ID_qyCancel;					     
					     safeTcsnCpy(  getResStr(  0,  &pQyMc->cusRes,  	CONST_resId_joinInBgWall  ),  tBuf,  mycountof(  tBuf  )  ); 
						 //
						 //  2016/03/27
						 setSlaveStreamOn(  hTalkerMgr,  FALSE  );			
	
		  }
	}
	//
	PostMessage(  hTalkerMgr,  CONST_qyWm_postComm,  CONST_qyWmParam_curSharedObjUsrChanged_mgr,  0  );

	//
	dyn_d3dWall_refreshImgs(  hTalkerMgr,  _T(  "dlgTalk_doCmd_joinInBgWall"  ));
	
	//
	iErr  =  0;

errLabel:
	
	return  iErr;
}


  //  2012/05/02. 在这个函数中,不应该采用qRemoveMsg,因为可能其他地方正在使用被删除的消息.应该做一个需要删除的标志位,并且其他的地方不能再采用这个消息就可以了
  //  int  dlgTalk_qPostMsg(  DLG_TALK_var  *  pVar,  Q_ELEM_T  *  pQElem,  unsigned  int  size  )
  __declspec(  dllexport  )  int  dlgTalk_qPostMsg(  HWND  hDlgTalk,  Q_ELEM_T  *  pQElem,  unsigned  int  size  )
{
	int  iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pVar  )  {
		//  2014/01/24	 
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "Gui"  ),  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_qPostMsg failed,  getDlgTalkVar is null"  )  );
		return  -1;
	}
	if  (  !pVar->m_pProcessQ  )  {
		//  2014/01/24	 
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_qPostMsg failed,  pVar->m_ProcessQ is null"  )  );
		return  -1;
	}
	if  (  !pQElem  ||  !size  )  return  -1;

#ifdef  __DEBUG__
		//traceLog(  _T(  "dlgTalk_qPostMsg not finished"  )  );
#endif

	MIS_MSGU	*	pMsg	=	(  MIS_MSGU  *  )pQElem;
	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_task:
				  if  (  pMsg->task.iTaskId  )  {
					  switch  (  pMsg->task.uiTaskType  )  {
							  case  CONST_imTaskType_sendFile:
							  case  CONST_imTaskType_recvFile:  {
								    PARAM_PROC_ROW	param;
									memset(  &param,  0,  sizeof(  param  )  );
									param.iTaskId  =  pMsg->task.iTaskId;
									qRemoveMsg(  pVar->m_pProcessQ,  tmpHandler_bRemoveMsgInProcessQ,  hDlgTalk,  &param  );
									}
									break;
							  default:  {
									    //  2016/02/17					  
									    MIS_MSG_TASK  *  tmppMsg  =  findTaskInProcessQ(  pVar,  pMsg->task.iTaskId  );					  
										//					  
										if  (  tmppMsg  )  {
											if  (  tmppMsg->iStatus  ==  pMsg->task.iStatus  )  return  -1;						  
											//
											if  (  bTaskAlive(  tmppMsg->iStatus  )  )  return  -1;						  
											//
											if (!pProcInfo->bAppQt()) {
												//
												if (tmppMsg->iStatus == CONST_imTaskStatus_autoCanceledByReceiver) {
													PARAM_PROC_ROW	param;
													memset(&param, 0, sizeof(param));
													param.iTaskId = pMsg->task.iTaskId;
													qRemoveMsg(pVar->m_pProcessQ, tmpHandler_bRemoveMsgInProcessQ, hDlgTalk, &param);
													break;
												}
												//
											}
											//
											return  -1;					  
										}
										break;
						
							  }					
					  }
				  }
				  //
				  IM_CONTENTU  *  pContent;
				  pContent  =  M_getMsgContent(  pMsg->task.ucFlg,  &pMsg->talk.data  );
				  switch  (  pContent->uiType  )  {
						  case  CONST_imCommType_transferAvInfo:  {
							    CQyMalloc  mallocObj_pMsgTask;
								MIS_MSG_TASK  *  pMsgTask  =  (  MIS_MSG_TASK  *  )mallocObj_pMsgTask.mallocf(  sizeof(  MIS_MSG_TASK  )  );
								//
								if  (  sizeof(  TRANSFER_AV_INFO  )  >  sizeof(  IM_CONTENTU  )  )  {
									showInfo_open0(  0,  0,  _T(  "dlgTalk_qPostMsg failed: sizeof(  TRANSFER_AV_task  ) too big"  )  );
									return  -1;
								}
								int  maxLen  =  offsetof(  MIS_MSG_TASK,  data  )  +  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  sizeof(  TRANSFER_AV_INFO  );
								memset(  pMsgTask,  0,  maxLen  );
								//
								int  msgLen  =  offsetof(  MIS_MSG_TASK,  data  )  +  pMsg->task.lenInBytes;
								memcpy(  pMsgTask,  &pMsg->task,  msgLen  );
								//
								IM_CONTENTU  *  pContent_new  =  M_getMsgContent(  pMsgTask->ucFlg,  &pMsgTask->data  );								
								//
								pContent_new->transferAvInfo.tmp_usSubtype  =  CONST_transferAvInfo_subtype_task;
								//
								pMsgTask->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  sizeof(  TRANSFER_AV_INFO  );
								//
								msgLen  =  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes;;
								return  ::qPostMsg(  pMsgTask,  msgLen,  pVar->m_pProcessQ,  _T(  "dlgTalk_qPostMsg"  ));

								}
							    break;
						  default:
								  break;
				  }
				  //
				  break;
			case  CONST_misMsgType_talk:
				  break;
			case  CONST_misMsgType_taskStatus:
				  #ifdef  __DEBUG__
				if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
					traceLog(_T("dlgTalk_qPostMsg: msgTaskStatus"));
				}
				  #endif
				  break;
			case  CONST_misMsgType_applyForTalkerShadow_qmc:
				  break;
			default:
					#ifdef  __DEBUG__
							traceLog(  _T(  "dlgTalk_qPostMsg: unexpected msgType, %d"  ),  pMsg->uiType  );
					#endif
					break;
	}

	return  ::qPostMsg(  pQElem,  size,  pVar->m_pProcessQ,  _T(  "dlgTalk_qPostMsg 2"  ));

errLabel:
	return  iErr;
}


  __declspec(  dllexport  )  int  dlgTalk_findWndForPrompt(  HWND  hDlgTalk_mgr,  void  *  pDLG_TALK_var,  HWND  *  phWnd_forPrompt,  int  *  piWndContentType_forPrompt  )
{
	int		iErr	=	-1;	
	HWND	tmp_hWnd  =  hDlgTalk_mgr;
	int		iWndContentType  =  0;
	int		i;

	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )pDLG_TALK_var;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;

	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;

	
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {	
		 if  (  pShadowMgr->shadows[i].iWndContentType_wall  ==  CONST_qyWndContentType_consoleWall
			 &&  IsWindow(  pShadowMgr->shadows[i].hWall  )  )						  					  
		 {
			 tmp_hWnd  =  pShadowMgr->shadows[i].hWall;			
			 iWndContentType  =  CONST_qyWndContentType_consoleWall;
			 break;					  
		 }										
		 //					  
		 if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  {			
			 tmp_hWnd  =  pShadowMgr->shadows[i].hShadow;				
			 iWndContentType  =  CONST_qyWndContentType_talker;		//  注意:这里是强行赋值. 以后会有非dlgTalk类型的shadow. 所以这里有一些可能出错的地方. 2013/11/14
			 break;					  
		 }				  
	}

	iErr  =  0;
errLabel:
	if  (  !iErr  )  {
		if  (  phWnd_forPrompt  )  *phWnd_forPrompt  =  tmp_hWnd;
		if  (  piWndContentType_forPrompt  )  *piWndContentType_forPrompt  =  iWndContentType;
	}
	return  iErr;
}


  //
__declspec(  dllexport  )  int  dlgTalk_chkShadows(  HWND  hDlgTalk,  DLG_TALK_var  *  pDlgTalkVar_mgr  )
{
	if  (  !pDlgTalkVar_mgr  )  return  -1;
	if  (  !isTalkerShadowMgr(  pDlgTalkVar_mgr->addr  )  )  return  -1;



	#if  10
	
			TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pDlgTalkVar_mgr->pShadowInfo;
			if  (  !pShadowMgr  )  return  -1;

			DWORD  dwTickCnt  =  GetTickCount(  );

			int  i;
			for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
				 TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
				 if  (  !pMem->hWall  )  continue;
				 //
				 if  (  !IsWindow(  pMem->hWall  )  )  {
 					 #ifdef  __DEBUG__
							 traceLog(  _T(  "dlgTalk_myTimeProc: wall is invalied, pMem will be cleared"  )  );
					 #endif
					 memset(  pMem,  0,  sizeof(  pMem[0]  )  );
					 continue;
				 }
				 //
				 //  2013/07/16
				 if  (  pMem->iWndContentType_wall  ==  CONST_qyWndContentType_consoleWall  )  {
					 //
#ifndef  __DEBUG__
					 //traceLog(  _T(  "Not finished: 要检查是否wallD3d里有这个messenger. 如果没有的话,也是无效的"  )  );
#endif
					 //
					 continue;
				 }
				 //
				 if  (  pMem->uiVwRuleType  ==  CONST_vwRuleType_dynBmp  )  {
					 if  (  dwTickCnt  -  pMem->dwTickCnt_lastRefreshed  <  60  *  1000  )  continue;
					 #ifdef  __DEBUG__
							 traceLog(  _T(  "dlgTalk_myTimeProc: dwTickCnt - pMem > 60s, pMem dynBmp will be cleared"  )  );
					 #endif
					 memset(  pMem,  0,  sizeof(  pMem[0]  )  );
					 continue;
				 }
				 if  (  pMem->uiVwRuleType  ==  CONST_vwRuleType_messenger
					 ||  !pMem->uiVwRuleType  )
				 {
					 if  (  IsWindow(  pMem->hShadow  )  ) continue;
					#ifdef  __DEBUG__
							 traceLog(  _T(  "dlgTalk_myTimeProc: hShadow is invalid, pMem msgr will be cleared"  )  );
					 #endif
					 memset(  pMem,  0,  sizeof(  pMem[0]  )  );
					 continue;
				 }
				 //
				 if (isTalkerSubtype_canInput(pMem->iTalkerSubType)) {
					 if (!IsWindow(pMem->hShadow)) {
#ifdef  __DEBUG__
						 traceLog(_T("dlgTalk_myTimeProc: shadow_input is invalied, pMem will be cleared"));
#endif
						 memset(pMem, 0, sizeof(pMem[0]));
						 continue;
					 }
				 }
				 //
				 MACRO_qyAssert(  0,  _T(  "unkonw ruleType"  )  );
				 continue;
			}
#endif

			return  0;
}



  __declspec(  dllexport  ) int  dlgTalk_doApplyForTalkerShadow_qmc(  HWND  hDlgTalk,  MIS_MSG_applyForTalkerShadow_qmc  *  pMsg_applyForTalkerShadow_qmc  )
 {
	int  iErr  =  -1;

	//
	HWND  hDlg  =  hDlgTalk;

	//
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pm_var					=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlg  );
	if  (  !pm_var  )  return  -1;	
	DLG_TALK_var	&	m_var					=	*pm_var;

	//PARAM_PROC_ROW	*	pParam					=	(  PARAM_PROC_ROW  *  )p1;
	
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_MSGU		*	pMsg					=	(  MIS_MSGU  *  )pMsg_applyForTalkerShadow_qmc;

	if  (  pMsg->uiType  !=  CONST_misMsgType_applyForTalkerShadow_qmc  )  goto  errLabel;
 
	   //  2012/04/23
#if  0
				  if  (  pMsg->applyForTalkerShadow_qmc.tStartTime_processed  )  break;
				  mytime(  &pMsg->applyForTalkerShadow_qmc.tStartTime_processed  );	//  2007/10/13, 

				  pParam->bMsgNeedRemoved  =  TRUE;		//  2009/10/18
#endif

				  //
				  if  (  !IsWindow(  pMsg->applyForTalkerShadow_qmc.hWall  )  )  goto  errLabel;

				  if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;
				  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
				  if  (  !pShadowMgr  )  goto  errLabel;

				  int  i;

				  //  2014/02/04
				  dlgTalk_chkShadows(  hDlg,  &m_var  );

				  //
				  if  (  pMsg->applyForTalkerShadow_qmc.uiVwRuleType  ==  CONST_vwRuleType_dynBmp  )  {

					  //  2017/01/10						
					  pShadowMgr->quickToRetrieveImg.ucbOn  =  TRUE;

					  //
					  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
						   if  (  pShadowMgr->shadows[i].hWall  ==  pMsg->applyForTalkerShadow_qmc.hWall
							   &&  pShadowMgr->shadows[i].uiVwRuleType  ==  pMsg->applyForTalkerShadow_qmc.uiVwRuleType
							   &&  pShadowMgr->shadows[i].uiTranNo_spObj  ==  pMsg->applyForTalkerShadow_qmc.uiTranNo_zone  )
						   {
							   break;
						   }
					  }
					  //
					  if  (  i  <  mycountof(  pShadowMgr->shadows  )  )  {
						  //  已经存在了
						  if  (  memcmp(  &pShadowMgr->shadows[i].vwRuleCmd,  &pMsg->applyForTalkerShadow_qmc.vwRuleCmd,  sizeof(  VW_rule_messengerCmd  )  )  )  {
							  memcpy(  &pShadowMgr->shadows[i].vwRuleCmd,  &pMsg->applyForTalkerShadow_qmc.vwRuleCmd,  sizeof(  VW_rule_messengerCmd  )  );
						  }
						  pShadowMgr->shadows[i].dwTickCnt_lastRefreshed  =  GetTickCount(  );
						  //
						  iErr  =  0;  goto  errLabel;
						  //  break;
					  }
					  //  如果没找到,那么需要找一个空位置
					  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
						   if  (  !pShadowMgr->shadows[i].hWall  )  break;
					  }
					  if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  {
						  #ifdef  __DEBUG__
								  traceLog(  _T(  "no new shadow is allowed"  )  );
						  #endif
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "No new shadow of %I64u is allowed"  ),  m_var.addr.idInfo.ui64Id  );
						  //
						  goto  errLabel;
						  //  break;
					  }
					  //  填充shadow信息
					  memset(  &pShadowMgr->shadows[i],  0,  sizeof(  pShadowMgr->shadows[i]  )  );
					  pShadowMgr->shadows[i].hWall  =  pMsg->applyForTalkerShadow_qmc.hWall;
					  pShadowMgr->shadows[i].iWndContentType_wall  =  pMsg->applyForTalkerShadow_qmc.iWndContentType_wall;
					  pShadowMgr->shadows[i].uiVwRuleType  =  pMsg->applyForTalkerShadow_qmc.uiVwRuleType;
					  pShadowMgr->shadows[i].uiTranNo_spObj  =  pMsg->applyForTalkerShadow_qmc.uiTranNo_zone;
					  memcpy(  &pShadowMgr->shadows[i].vwRuleCmd,  &pMsg->applyForTalkerShadow_qmc.vwRuleCmd,  sizeof(  pShadowMgr->shadows[i].vwRuleCmd  )  );
					  pShadowMgr->shadows[i].dwTickCnt_lastRefreshed  =  GetTickCount(  );
					  //
					  iErr  =  0;  goto  errLabel;
					  //  break;
				  }

				  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
					   if  (  pShadowMgr->shadows[i].hWall  ==  pMsg->applyForTalkerShadow_qmc.hWall
						   &&  pShadowMgr->shadows[i].uiVwRuleType  ==  pMsg->applyForTalkerShadow_qmc.uiVwRuleType
						   &&  IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  
					   {
						   break;
					   }
				  }
				  if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  {  
					  //
					  int  iTalkerSubType	=	0;
					  switch  (  pMsg->applyForTalkerShadow_qmc.iWndContentType_wall  )  {
							  case  CONST_qyWndContentType_vWall:  
								    iTalkerSubType  =  CONST_talkerSubtype_onVWall;						  
									break;					  
							  case  CONST_qyWndContentType_consoleWall:
								    iTalkerSubType  =  CONST_talkerSubtype_3dTool;
									break;
							  default:
									 iTalkerSubType  =  CONST_talkerSubtype_enlarged;
									 break;
					  }
					  //
					  if  (  iTalkerSubType  ==  CONST_talkerSubtype_enlarged  )  {

						  #ifndef  __SUPPORT_multiTalkersToInput__
								   //  同一时刻,只能有一个接收输入的talker
								   if  (  IsWindowVisible(  hDlg  )  )  {						  
									   MACRO_SetForegroundWindow(  hDlg  );
									   iErr  =  0;  goto  errLabel;
								   }
						  #endif
						  //
						  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
							   if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  
								   &&  pShadowMgr->shadows[i].iTalkerSubType  ==  CONST_talkerSubtype_enlarged  )
							   {
								   MACRO_SetForegroundWindow(  pShadowMgr->shadows[i].hShadow  );
								   iErr  =  0;  goto  errLabel;
							   }
						  }
					  }

					  //  对临时msgr,不能建立影子
					  if  (  m_var.ucbTmpMsgr  )  {
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "No new shadow of tmpMsgr %I64u is allowed"  ),  m_var.addr.idInfo.ui64Id  );
						  goto  errLabel;
					  }

					  //  下面需要建一个新的shadow
					  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
						   if  (  !IsWindow(  pShadowMgr->shadows[i].hWall  )  )  break;
					  }
					  if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  {
						  #ifdef  __DEBUG__
								  traceLog(  _T(  "no new shadow allowed"  )  );
						  #endif
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "No new shadow of %I64u is allowed"  ),  m_var.addr.idInfo.ui64Id  );
						  goto  errLabel;
					  }
					  //
					  HWND	hShadow  =  NULL;
					  MSGR_ADDR	addr;
					  memcpy(  &addr,  &m_var.addr,  sizeof(  addr  )  );
					  addr.uiTranNo_shadow  =  getuiNextTranNo(  0,  0,  0  );
					  //
					  pProcInfo->getTalkerShadow(  pMsg->applyForTalkerShadow_qmc.hWall,  &addr,  NULL,  iTalkerSubType,  0,  0,  &hShadow  );				  
					  if  (  !IsWindow(  hShadow  )  )  goto  errLabel;
					  memset(  &pShadowMgr->shadows[i],  0,  sizeof(  pShadowMgr->shadows[i]  )  );
					  pShadowMgr->shadows[i].hWall  =  pMsg->applyForTalkerShadow_qmc.hWall;
					  pShadowMgr->shadows[i].iWndContentType_wall  =  pMsg->applyForTalkerShadow_qmc.iWndContentType_wall;
					  pShadowMgr->shadows[i].uiVwRuleType  =  pMsg->applyForTalkerShadow_qmc.uiVwRuleType;
					  pShadowMgr->shadows[i].uiTranNo_spObj  =  pMsg->applyForTalkerShadow_qmc.uiTranNo_zone;
					  pShadowMgr->shadows[i].iTalkerSubType  =  iTalkerSubType;
					  memcpy(  &pShadowMgr->shadows[i].vwRuleCmd,  &pMsg->applyForTalkerShadow_qmc.vwRuleCmd,  sizeof(  pShadowMgr->shadows[i].vwRuleCmd  )  );
					  pShadowMgr->shadows[i].hShadow  =  hShadow;
				  }
				  if  (  pMsg->applyForTalkerShadow_qmc.ucbRefreshCmd  )  {
					  memcpy(  &pShadowMgr->shadows[i].vwRuleCmd,  &pMsg->applyForTalkerShadow_qmc.vwRuleCmd,  sizeof(  pShadowMgr->shadows[i].vwRuleCmd  )  );
					  //
					  iErr  =  0;  goto  errLabel;
					  //  break;
				  }
				  //
				  pMsg->applyForTalkerShadow_qmc.hShadow  =  pShadowMgr->shadows[i].hShadow;
				  SendMessage(  pMsg->applyForTalkerShadow_qmc.hWall,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );
				  
				  iErr  =  0;
errLabel:
				  return  iErr;
 }



 //
 __declspec(  dllexport  )  int  askToRefreshLayout_mgr(  HWND  hDlgTalk  )
{
	int		iErr	=	-1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;

	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk,  _T(  "askToRefreshLayout_mgr"  )  );
	if  (  !pMgrVar  )  goto  errLabel;

	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	
	//
	 int  i;	 
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		  if  (  !pShadowMgr->shadows[i].hShadow  )  continue;
		  if  (  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
			  ::PostMessage(   pShadowMgr->shadows[i].hShadow,  CONST_qyWm_postComm,  CONST_qyWmParam_refreshLayout,  0  );
		  }
	 }
	 ::PostMessage(   hDlgTalk,  CONST_qyWm_postComm,  CONST_qyWmParam_refreshLayout,  0  );

	 iErr  =  0;
errLabel:
	 return  iErr;
}


 



 //  2014/12/20
  __declspec(  dllexport  )  int  askToRefreshSize_mgr(  HWND  hDlgTalk  )
{
	int		iErr	=	-1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;

	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk,  _T(  "askToRefreshSize_mgr"  )  );
	if  (  !pMgrVar  )  goto  errLabel;

	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	
	//
	 int  i;	 
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		  if  (  !pShadowMgr->shadows[i].hShadow  )  continue;
		  if  (  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
			  //::PostMessage(   pShadowMgr->shadows[i].hShadow,  CONST_qyWm_postComm,  CONST_qyWmParam_refreshLayout,  0  );
			  ::PostMessage(  pShadowMgr->shadows[i].hShadow,  WM_SIZE,  0,  0  );

		  }
	 }
	 ::PostMessage(   hDlgTalk,  WM_SIZE,  0,  0  );

	 iErr  =  0;
errLabel:
	 return  iErr;
}


  __declspec(dllexport)  int  talk_refreshLayout_mgr(HWND  hDlgTalk_mgr)
  {
	  int		iErr = -1;
	  CCtxQyMc* pQyMc = g_pQyMc;
	  CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	  CHelp_getDlgTalkVar	help_getDlgTalkVar;

	  DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk_mgr, _T("talk_refreshLayout_mgr"));
	  if (!pMgrVar)  goto  errLabel;

	  if (!isTalkerShadowMgr(pMgrVar->addr))  goto  errLabel;
	  TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
	  if (!pShadowMgr)  goto  errLabel;


	  //
	  int  i;
	  for (i = 0; i < mycountof(pShadowMgr->shadows); i++) {
		  if (!pShadowMgr->shadows[i].hShadow)  continue;
		  if (isTalkerSubtype_canInput(pShadowMgr->shadows[i].iTalkerSubType)) {
			  //::PostMessage(pShadowMgr->shadows[i].hShadow, CONST_qyWm_postComm, CONST_qyWmParam_refreshLayout, 0);
			  pProcInfo->do_talk_refreshLayout(pShadowMgr->shadows[i].hShadow);
		  }
	  }
	  //::PostMessage(hDlgTalk, CONST_qyWm_postComm, CONST_qyWmParam_refreshLayout, 0);
	  pProcInfo->do_talk_refreshLayout(hDlgTalk_mgr);

	  //
	  iErr = 0;
  errLabel:
	  return  iErr;
  }



  __declspec(dllexport)  BOOL  bDlgTalkWaitToAccept(HWND  hDlgTalk)
  {
	  BOOL					bRet = FALSE;
	  CHelp_getDlgTalkVar		help_getDlgTalkVar;
	  DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk, _T("bDlgTalkWaitToAccept"));
	  if (!pDlgTalkVar)  return  FALSE;

	  CHelp_getDlgTalkVar		help_getDlgTalkVar_mgr;
	  DLG_TALK_var* pMgrVar = pDlgTalkVar;
	  if (!isTalkerShadowMgr(pDlgTalkVar->addr)) {
		  TALKER_shadow* pShadow = (TALKER_shadow*)pDlgTalkVar->pShadowInfo;
		  if (!pShadow)  return  FALSE;
		  pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(pShadow->hMgr, _T("bDlgTalkWaitToAccept,hMgr"));
		  if (!pMgrVar)  return  FALSE;
	  }


	  DLG_guiData_talk* pGuiData = &pMgrVar->guiData;

	  switch (pGuiData->av.iStatus) {
	  case  CONST_imTaskStatus_resp:
	  case  CONST_imTaskStatus_applyToRecv:
		  bRet = TRUE;
		  break;
	  default:
		  break;
	  }

  errLabel:
	  return  bRet;
  }

  //  2013/03/04. 根据可见区域cliRc,来计算pLayout中的iW_...  注意这些iW要有上限
  __declspec(dllexport)  int  dlgTalk_calculateLayout(HWND  hCurTalk, DLG_TALK_var* pCurVar, RECT* pCliRc, DLG_talk_layout* pLayout)
  {
	  int					iErr = -1;
	  RECT				cliRc = { 0 };

	  int					iW = 0, iW_tool = 0;

	  //
	  int			iEdge_l = CONST_edge_l_dlgTalk_wall;
	  int			iEdge_t = CONST_edge_l_dlgTalk_wall;
	  int			iEdge_r = CONST_edge_l_dlgTalk_wall;
	  int			iEdge_b = CONST_edge_l_dlgTalk_wall;
	  //
	  int			iX_spacing = CONST_iX_spacing_dlgTalk_wall;			//  
	  int			iY_spacing = CONST_iY_spacing_dlgTalk_wall;			//  

	 //
	  unsigned short		usGrpSubtype = 0;

	  //
#ifdef  __APP_qyMc__
	  if (!pCurVar->ucbOnGlobalVWall) {
		  iEdge_l = CONST_edge_l_dlgTalk_desktop;
		  iEdge_r = CONST_edge_l_dlgTalk_desktop;
	  }
#endif

	  if (!pLayout)  return  -1;
	  if (!pCurVar)return  -1;

	  memset(pLayout, 0, sizeof(pLayout[0]));

	  if (!pCliRc) {
		  GetClientRect(hCurTalk, &cliRc);
		  pCliRc = &cliRc;
	  }

	  //
	   //
	  MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

	  //
	  HWND				hCtrl;
	  CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	  DLG_TALK_var* pMgrVar = pCurVar;
	  if (!isTalkerShadowMgr(pMgrVar->addr)) {
		  TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pMgrVar->pShadowInfo;
		  if (!pTalkerShadow)  goto  errLabel;
		  if (!IsWindow(pTalkerShadow->hMgr))  goto  errLabel;
		  pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(pTalkerShadow->hMgr, _T("dlgTalk_calculateLayout"));
		  if (!pMgrVar)  goto  errLabel;
	  }
	  usGrpSubtype = pMgrVar->guiData.usGrpSubtype;
	  /*
	  unsigned  char	ucbShowPeerDesc					=	TRUE;
	  unsigned  char	ucbShowMeDesc					=	FALSE;
	  unsigned  char	ucbShowOtherDesc				=   FALSE;
	  */
	  pLayout->ucbShowPeerDesc = FALSE;	//  TRUE;
	  pLayout->ucbShowMeDesc = FALSE;
	  pLayout->ucbShowOtherDesc = FALSE;
	  //
	  unsigned  short	usLayoutType = pCurVar->m_layout.usLayoutType_cur;
	  if (!usLayoutType)  usLayoutType = DEFAULT_usLayoutType;

	  //
	  //  2025/09/18
	  pLayout->usLayoutType_cur = usLayoutType;

	  //  2014/11/17
	  TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
	  if (pShadowMgr) {
		  if (pShadowMgr->shareScreen.ucbExists_localScreenSharing) {
			  //  2015/11/14
			  pLayout->ucbExists_localScreenSharing = TRUE;
			  //
			  pLayout->ucbShowPeerDesc = TRUE;
		  }
	  }
	  //
#ifdef  __DEBUG__
#if  0
	  traceLog(_T("TEST: showPeerDesc set to true"));
	  pLayout->ucbShowPeerDesc = TRUE;
#endif
#endif

	  //
	  if (usLayoutType == CONST_usLayoutType_dialog) {

		  if (pMgrVar->av.taskInfo.bTaskExists) {
			  QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, pMgrVar->av.iIndex_sharedObj_localAv);
			  if (pSharedObj && isSharedObjUsrIndexValid(pSharedObj->iIndex_curUsr) && pSharedObj->iIndex_curUsr == pMgrVar->av.iIndex_usr_localAv) {
				  pLayout->ucbShowMeDesc = TRUE;
			  }
		  }
		  if (!pLayout->ucbShowMeDesc) {  //  2013/03/01
			  int  nScreens = 0, nMediaFiles = 0;
			  if (bTaskExists_sendingResource(pMgrVar, &nScreens, &nMediaFiles, NULL, NULL, NULL, NULL)
				  && (nScreens || nMediaFiles)
				  )
			  {
				  pLayout->ucbShowMeDesc = TRUE;
			  }
		  }
		  //
	  }
	  else {
		  //  2014/11/15
		  if (bTaskExists_sendingResource(pMgrVar, NULL, NULL, NULL, NULL, NULL, NULL)) {
			  pLayout->ucbShowMeDesc = TRUE;
		  }
		  //  2015/10/25
		  if (pMgrVar->addr.uiObjType == CONST_objType_messenger) {
			  if (pMgrVar->av.taskInfo.bTaskExists) {
				  QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, pMgrVar->av.iIndex_sharedObj_localAv);
				  if (pSharedObj && isSharedObjUsrIndexValid(pSharedObj->iIndex_curUsr) && pSharedObj->iIndex_curUsr == pMgrVar->av.iIndex_usr_localAv) {
					  pLayout->ucbShowMeDesc = TRUE;
				  }
			  }
		  }

	  }
	  //
	  if (pMgrVar->addr.uiObjType == CONST_objType_imGrp) {
		  if (pMgrVar->av.taskInfo.bTaskExists) {
			  pLayout->ucbShowMeDesc = pMgrVar->av.taskInfo.bNeedShowMeDesc;
		  }
	  }


	  //
	  if (usLayoutType == CONST_usLayoutType_training)  pLayout->ucbShowOtherDesc = TRUE;

	  pLayout->ucbShowDlgDesc = pCurVar->guiData.ucbShowDlgDesc;
	  if (pLayout->ucbShowDlgDesc) {
		  pLayout->iH_dlgDesc = CONST_iH_dlgDesc;
	  }
	  //
	  BOOL  bShowMemList = pCurVar->guiData.ucbShowImGrpMems;
	  BOOL  bShowTaskList = dlgTalk_bMsgBoxShown(hCurTalk);
	  BOOL  bShowPtz = dlgTalk_bPtzShown(hCurTalk);
	  BOOL  bShowSubtitles = dlgTalk_bSubtitlesShown(hCurTalk);			//  2013/04/05,//  TRUE;				//  
	  BOOL  bShowOfflineRes = dlgTalk_bOfflineResShown(hCurTalk);			//  2015/08/01
	  //
	  BOOL  bShow_peer_tool = dlgTalk_bShowPeerTool(hCurTalk);											//  2017/08/21

	  //  2017/08/21
	  pLayout->ucbShow_peer_tool = bShow_peer_tool;


	  //
	  iW = pCliRc->right - pCliRc->left - iEdge_l - iEdge_r;

	  if (usGrpSubtype == CONST_imGrpSubtype_msg) {
		  iW_tool = iW;
	  }
	  else {
		  iW_tool = iW * 0.6;
	  }

	  if (bShowMemList) {
		  //pLayout->iW_memberList  =  bShowSubtitles  ?  min(  iW_tool  /  3,  300  )  :  min(  iW_tool  /  2,  300  );	//  min(  iW_tool  /  4,  150  );
		  pLayout->iW_memberList = bShowSubtitles ? min(iW_tool / 3, 300) : min(iW_tool * 0.6, 300);	//  min(  iW_tool  /  4,  150  );
	  }
	  else {
		  pLayout->iW_memberList = 0;
	  }

	  //
	  if (bShowTaskList)  pLayout->iW_taskList = bShowSubtitles ? min(iW_tool / 3, 300) : min(iW_tool / 2, 300);
	  else  pLayout->iW_taskList = 0;

	  if (bShowPtz)  pLayout->iW_ptz = bShowSubtitles ? min(iW_tool / 3, 300) : min(iW_tool / 2, 300);
	  else  pLayout->iW_ptz = 0;

	  if (bShowSubtitles)  pLayout->iW_subtitles = iW_tool - pLayout->iW_memberList - pLayout->iW_taskList - pLayout->iW_ptz;
	  else  pLayout->iW_subtitles = 0;

	  if (bShowOfflineRes) {
		  float  factor_iW_tool = 1;
		  if (usGrpSubtype != CONST_imGrpSubtype_msg)  factor_iW_tool = 3. / 2;	//  iW_tool  =  iW_tool  +  iW_tool  /  2;
		  pLayout->iW_offlineRes = iW_tool * factor_iW_tool - pLayout->iW_memberList - pLayout->iW_taskList - pLayout->iW_ptz - pLayout->iW_subtitles;
	  }

	  //  2017/08/21
	  if (bShow_peer_tool) {
		  pLayout->iW_peerInfo = min(iW_tool / 3, 200);
		  //
		  pLayout->iH_staticPeerInfo = CONST_iH_static_peerInfo;

		  //
		  RECT  rc = *pCliRc;
		  int  iH = 0;
		  iH = rc.bottom - rc.top - iEdge_t - iEdge_b - pLayout->iH_dlgDesc - pLayout->iH_staticPeerInfo;
		  iH *= 0.7;
		  pLayout->iH_peerInfo = iH;

		  //
		  pLayout->iH_shareScreen = 20;

	  }
	  else {
		  pLayout->iW_peerInfo = 0;
		  pLayout->iH_peerInfo = 0;
		  //
		  pLayout->iH_shareScreen = 0;
	  }

	  //  2014/10/03
	  pLayout->ucbShowBgWall = dlgTalk_bShowBgWall(hCurTalk);
	  if (pShadowMgr) {
		  pLayout->bgWallLayoutCfg = pShadowMgr->bgWall.bgWallCfg.bgWallLayoutCfg;
	  }
	  //pLayout->usPollingIntervalInS1  =  pMgrVar->m_layout.usPollingIntervalInS1;

	  //	
	  //pLayout->bgWallLayout.usRows_bg  =  pMgrVar->m_layout.bgWallLayout.usRows_bg;		
	  //pLayout->bgWallLayout.usCols_bg  =  pMgrVar->m_layout.bgWallLayout.usCols_bg;


	 //
	  iErr = 0;
  errLabel:

#ifdef  __DEBUG__
#if  0
	  pLayout->iW_memberList = 0;
	  pLayout->iW_taskList = 0;
	  pLayout->iW_ptz = 0;
	  traceLog(_T("Test: dlgTalk_calculateLayout, iW_memberList, iW_taskList, iW_ptz are set to 0"));
#endif
#endif

	  return  iErr;
  }
