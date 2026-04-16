
#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	<time.h>
#include	<stddef.h>
#include	<ShellAPI.h>
#include	<tchar.h>

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
#include	"dyn_isCliD3d_public.h"
#include	"myTChar.h"

#ifdef  __TEST_ONLY__
		#include	"testOnly.h"
#endif

#ifdef  __DEBUG__
#endif


//
  //  2014/11/30
  ZONE_PARAM  *  dlgTalk_getZoneParam(  HWND  hDlg,  DLG_TALK_var  &  m_var,  MIS_MSG_procVideo_qmc  *  pMsg  )
 {
	 ZONE_PARAM  *  pZoneParam  =  NULL;
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	 if  (  pMsg->localOnPeer.bLocalVideoDisplayedOnPeer  )  {
		 int  index_capImage  =  pMsg->localOnPeer.index_capImage_localVideoInMeImages;
		 if  (  index_capImage  <  0  ||  index_capImage  >=  CONST_maxCapImages  )  goto  errLabel;
		 pZoneParam  =  &m_var.av.zoneParams_localOnPeer[index_capImage];  goto  errLabel;
	 }
	 if  (  pMsg->meOnBgWall.bMeDisplayedOnBgWall  )  {
		 pZoneParam  =  &m_var.av.zoneParam_meOnBgWall;  goto  errLabel;
	 }
	 
	 if  (  pMsg->playerId.index_player  <  0  ||  pMsg->playerId.index_player  >=  m_var.av.usCnt_zoneParams  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_procVideo failed: index_player is < 0 or >= usCnt_zoneParams"  )  );
		goto  errLabel;
	}
	pZoneParam  =  &m_var.av.pZoneParams[pMsg->playerId.index_player];

errLabel:

	return  pZoneParam;
 }






//
 //  2013/07/16
__declspec(dllexport)  int  dlgTalk_procVideo(HWND  hDlg, void* pDLG_TALK_var, MIS_MSG_procVideo_qmc* pMsg, PARAM_dlgTalk_procVideo* pParam)
{
	int							iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);

	//
	if (!pDLG_TALK_var)  return  -1;
	DLG_TALK_var& m_var = *(DLG_TALK_var*)pDLG_TALK_var;

	//
	//int							idc = 0;
	HWND						hCtrl = NULL;
	HWND						hWnd_dst = NULL;
	HDC* phDc_dst = NULL;
	PARAM_dc_draw* pDcDrawParam = NULL;
	PARAM_dc_draw				tmp_dcDrawParam;
	//
	myZONE* pZone = NULL;
	//
	CAP_subWnds* pSubWnds = NULL;
	BOOL						bMeImages = FALSE;
	int							i;
	DLG_TALK_var* pDlgMgrVar = NULL;
	ZONE_PARAM* pZoneParam = NULL;

	TCHAR  tBuf[128];

	//
	if (pMsg->idInfo_peer.ui64Id && pMsg->idInfo_sender.ui64Id) {
		m_var.lastTickCnt_guiMsgArrive = myGetTickCount(mynull);
		m_var.last_lParam_guiMsgArrive = pMsg->playerId.index_player;

		//
#ifdef  __DEBUG__
		if (0) {
			if (m_var.addr.uiTranNo_shadow) {
				_sntprintf(tBuf, mycountof(tBuf), _T("dlgTalk_procVideo: %I64u,tn %d,  index_player %d, idInfo %I64u, pts %d"), m_var.addr.idInfo.ui64Id, m_var.addr.uiTranNo_shadow, pMsg->playerId.index_player, pMsg->idInfo_sender.ui64Id, pMsg->pkt.head.uiPts);
				showInfo_open0(0, 0, tBuf);
			}
		}
#endif
	}

	//
#ifdef  __DEBUG__
	if (!pMsg->iTaskId) {
		int  kk = 0;
	}
	if (pMsg->bih.biWidth > 1000) {
		int kk = 0;
	}
	if (pMsg->idInfo_sender.ui64Id) {
		int  ii = 0;
		if (!isTalkerShadowMgr(m_var.addr)) {
			int  ii = 0;
		}
	}
#endif

	//
	if (pProcInfo->av.hk.portStatus.bDisable_hdmi1Out_hdmi) {
		return  -1;
	}

	//  2013/07/20	
	memset(&tmp_dcDrawParam, 0, sizeof(tmp_dcDrawParam));
	pDcDrawParam = &tmp_dcDrawParam;


	//  2012/04/26
	if (isTalkerShadowMgr(m_var.addr)) {
		pDlgMgrVar = &m_var;


		//  主窗口必须绘制,因为需要用img的刷新参数来确定是否任务需要重新发起
	}
	else {
		pDlgMgrVar = (DLG_TALK_var*)pMsg->paramMsgToShadow.pDlgMgrVar;
		if (!pDlgMgrVar)  goto  errLabel;

	}



	//如果非法用户 就直接不显示视频流   判断会议中 判断p2p 
	
	if (pQyMc->appParams.bSmZy) {
		
		if (pDlgMgrVar->av.taskInfo.bTaskExists && 
			pDlgMgrVar->av.taskInfo.ucbVideoConference && 
			pDlgMgrVar->av.taskInfo.hgInfo.iMeetingType_hg != 2 && 
			pProcInfo->legal_info.isOk && 
			!pProcInfo->legal_info.bLegal)
		{
			return -1;
		}
	}

	




	//
	//
	pZoneParam = dlgTalk_getZoneParam(hDlg, m_var, pMsg);

	//  2012/04/28
	if (!pDlgMgrVar || !pZoneParam) {
#ifdef  __DEBUG__
		traceLog(_T("dlgTalk_procVideo failed: pZoneParam is null"));
#endif
		goto  errLabel;
	}

#ifdef  __DEBUG__
	if (m_var.iTalkerSubType == CONST_talkerSubtype_enlarged) {
		//  traceLog(  _T(  "kk"  )  );
	}
	//
	if (!isTalkerShadowMgr(m_var.addr)) {
		int  ii = 0;
		if (pDlgMgrVar->av.taskInfo.bDbgFlg) {
			if (pDlgMgrVar->av.taskInfo.iTaskId != pMsg->iTaskId) {
				ii = 1;
			}
		}
	}

#endif

	//
	unsigned  short	usLayoutType = m_var.m_layout.usLayoutType_cur;
	if (!usLayoutType)  usLayoutType = DEFAULT_usLayoutType;
	//		
	unsigned  char  ucbAutoClip = m_var.ucbAutoClip;

	//. 
#ifdef  __DEBUG__
#if  0
	usLayoutType = CONST_usLayoutType_dialog;
	traceLog(_T("for test, set usLayoutType"));
#endif
	//
	//traceLog(  _T(  "msg.usIndex %d. tn %d"  ),  pMsg->usIndex,  pMsg->uiTranNo_openAvDev  );
	//
	if (pMsg->usIndex == 2) {
		int  ii = 0;
	}
#endif


	//				  
	if (!pMsg->idInfo_peer.ui64Id && pMsg->uiCapType) {
		//
		if (pMsg->meOnBgWall.bMeDisplayedOnBgWall) {  //  2014/11/29
			//idc = m_var.guiData.iIDC_STATIC_bgWall_conf;	//  2013/02/23
			hCtrl = m_var.av.hCtrl_bgWall_conf;
			//pCapRect  =  &m_var.guiData.bgWallCapRect;
			//
			hWnd_dst = hCtrl;//GetDlgItem(hDlg, idc);
			phDc_dst = &m_var.av.hDc_bgWall_conf;
			//
			//pImgs  =  &m_var.av.bgWallImages;	
			if (pZoneParam->index_zone < 0 || pZoneParam->index_zone >= m_var.av.bgWall.usCnt) {
				showInfo_open0(0, 0, _T("dlgTalk_procVideo failed, index_zone err"));
				goto  errLabel;
			}
			pZone = &m_var.av.bgWall.mems[pZoneParam->index_zone];
			//pImgs  =  &pZone->images;
			//
			pSubWnds = &pDlgMgrVar->subWnds;
			//
			memcpy(&tmp_dcDrawParam.bgWallLayout, &m_var.m_layout.bgWallLayout, sizeof(tmp_dcDrawParam.bgWallLayout));
			tmp_dcDrawParam.bBgWall = TRUE;
		}
		else  if (pMsg->localOnPeer.bLocalVideoDisplayedOnPeer) {			//  2014/11/15
			//idc = m_var.guiData.iIDC_STATIC_peerDesc;	//  2013/02/23
			hCtrl = m_var.av.hCtrl_peer;
			//pCapRect  =  &m_var.guiData.peerCapRect;
			hWnd_dst = m_var.av.hWnd_dst_peer;//hDlg;
			phDc_dst = &m_var.av.hDc_peer;
			//
			pZone = &m_var.av.peerZone;
			//pImgs  =  &m_var.av.peerZone.images;						
			//
			bMeImages = FALSE;

			//
			//  2015/03/12
			switch (usLayoutType) {
			case  CONST_usLayoutType_training:
			case  CONST_usLayoutType_resourceOnly:
				ucbAutoClip = FALSE;
				break;
			default:
				break;
			}

		}
		else {
			//idc = m_var.guiData.iIDC_STATIC_meDesc;	//  2013/02/23
			hCtrl = m_var.av.hCtrl_me;
			//pCapRect  =  &m_var.guiData.meCapRect;
			//
			hWnd_dst = hCtrl;//GetDlgItem(hDlg, idc);
			phDc_dst = &m_var.av.hDc_me;
			//
			//  pImgs  =  &m_var.av.meImages;						
			pZone = &m_var.av.meZone;
			//
			bMeImages = TRUE;

			//  2016/02/16
			ucbAutoClip = m_var.ucbAutoClip_me;
		}

		//
		//
	}
	else {
#ifdef  __DEBUG__
		//  traceLog(  _T(  "for test. usLayoutType is changed."  )  );
		//  usLayoutType =  CONST_usLayoutType_videoOnly;
#endif

//
		TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pDlgMgrVar->pShadowInfo;

		//  2013/11/18
		if (isTalkerShadowMgr(m_var.addr)) {
			if (pMsg->iTaskId == pShadowMgr->remoteAssist.iTaskId
				&& pShadowMgr->remoteAssist.hWnd_remoteAssist)
			{
				if (CONST_qyWmRc_ok != SendMessage(pShadowMgr->remoteAssist.hWnd_remoteAssist, CONST_qyWm_comm, 0, (LPARAM)pMsg)) {
					if (!IsWindow(pShadowMgr->remoteAssist.hWnd_remoteAssist)) {
						pShadowMgr->remoteAssist.hWnd_remoteAssist = 0;
						pShadowMgr->remoteAssist.iTaskId = 0;
					}
				}
			}
		}

		//
		BOOL	bSkipped = FALSE;
		//		
		switch (usLayoutType) {
		case  CONST_usLayoutType_training:
			if (pDlgMgrVar->av.taskInfo.bTaskExists) {
				if (pMsg->iTaskId == pDlgMgrVar->av.taskInfo.iTaskId) {
					int  index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, pMsg->iTaskId);
					QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
					if (!pTaskInfo)  goto  errLabel;
					QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
					int  index_active = 0;
					if (!isVideoActive(pDlgMgrVar->pMisCnt, &pTc->videoConference, &pMsg->idInfo_sender, pMsg->uiTranNo_openAvDev, &index_active))  goto  errLabel;
					if (!pTc->videoConference.activeMems_from[index_active].avStream.obj.resObj.uiObjType) {
						//
						//idc = m_var.guiData.iIDC_STATIC_otherDesc;		//  peerDesc当背景色用,所以直接画在对话框上. 2013/02/23
						hCtrl = m_var.av.hCtrl_other;
						//pCapRect  =  &m_var.guiData.otherCapRect;
						hWnd_dst = hCtrl;//GetDlgItem(hDlg, idc);
						phDc_dst = &m_var.av.hDc_other;
						//
						//pImgs  =  &m_var.av.otherImages;					  
						pZone = &m_var.av.otherZone;
						//
						pSubWnds = &pDlgMgrVar->subWnds;
					}
				}
			}
			break;
		case  CONST_usLayoutType_resourceOnly:
			if (pDlgMgrVar->av.taskInfo.bTaskExists) {
				//
				if (!pDlgMgrVar->av.taskInfo.mosaicTrans.bExists_confMosaic) {   //  2014/11/18
					//
					if (pMsg->iTaskId == pDlgMgrVar->av.taskInfo.iTaskId) {
						bSkipped = TRUE;
						break;
					}
					//
				}
			}
			break;
		case  CONST_usLayoutType_videoOnly:
			if (pDlgMgrVar->av.taskInfo.bTaskExists) {
				if (pMsg->iTaskId != pDlgMgrVar->av.taskInfo.iTaskId) {  //  2010/12/21
					bSkipped = TRUE;
					break;
				}
			}
			break;
		case  CONST_usLayoutType_dialog:
		case  CONST_usLayoutType_conference:
		default:
			break;
		}

		//
		if (bSkipped) {  //  将任务的tStartTime_processed更新一下,表明该任务是活跃的
			BOOL	bFound = FALSE;
			MIS_MSG_TASK* pMsgTask;
			time_t	t;  mytime(&t);

			if ((pMsgTask = findTaskInProcessQ(pDlgMgrVar, pMsg->iTaskId))) {
				if (!bTaskAlive(pMsgTask->iStatus))  goto  errLabel;
				bFound = TRUE;
			}
			if (bFound) {
				//  pMsgTask->tStartTime_processed  =  t;
				pMsgTask->tTime_alive = t;	//  2014/12/09
				iErr = 0;  goto  errLabel;
			}
			for (i = 0; i < mycountof(pShadowMgr->talkerDynBmps); i++) {
				if (pMsg->iTaskId == pShadowMgr->talkerDynBmps[i].taskInfo.iTaskId) {
					bFound = TRUE;
					break;
				}
			}
			if (bFound) {
				pShadowMgr->talkerDynBmps[i].taskInfo.tStartTime_processed = t;
				iErr = 0;  goto  errLabel;
			}

#ifdef  __DEBUG__
			traceLog(_T("dlgTalk_procVideo: msg err, task not found"));
#endif
			goto  errLabel;
		}

		if (!hCtrl) {		//  没有指定时,都放到peer里去
			if (pMsg->pkt.uiTaskType == CONST_imTaskType_viewDynBmp) {

				if (m_var.addr.uiObjType == CONST_objType_imGrp) {
					//idc = m_var.guiData.iIDC_STATIC_bgWall_conf;	//  2013/02/23
					hCtrl = m_var.av.hCtrl_bgWall_conf;
					//pCapRect  =  &m_var.guiData.bgWallCapRect;
					//
					hWnd_dst = hCtrl;//GetDlgItem(hDlg, idc);
					phDc_dst = &m_var.av.hDc_bgWall_conf;
					//
					//pImgs  =  &m_var.av.bgWallImages;	
					if (pZoneParam->index_zone < 0 || pZoneParam->index_zone >= m_var.av.bgWall.usCnt) {
						showInfo_open0(0, 0, _T("dlgTalk_procVideo failed,  index_zone err"));
						goto  errLabel;
					}
					pZone = &m_var.av.bgWall.mems[pZoneParam->index_zone];
					//pImgs  =  &pZone->images;
					//
					pSubWnds = &pDlgMgrVar->subWnds;
					//
					memcpy(&tmp_dcDrawParam.bgWallLayout, &m_var.m_layout.bgWallLayout, sizeof(tmp_dcDrawParam.bgWallLayout));
					tmp_dcDrawParam.bBgWall = TRUE;
					//


				}

			}
		}

		if (!hCtrl) {
			//
			//idc = m_var.guiData.iIDC_STATIC_peerDesc;		//  2013/02/23
			hCtrl = m_var.av.hCtrl_peer;
			//pCapRect  =  &m_var.guiData.peerCapRect;
			hWnd_dst = m_var.av.hWnd_dst_peer;//hDlg;								//  2013/03/04
			phDc_dst = &m_var.av.hDc_peer;
			//pImgs  =  &m_var.av.peerImages;
			pZone = &m_var.av.peerZone;
			//
			pSubWnds = &pDlgMgrVar->subWnds;

			//  2014/04/13
			switch (usLayoutType) {
			case  CONST_usLayoutType_training:
			case  CONST_usLayoutType_resourceOnly:
				ucbAutoClip = FALSE;
				break;
			default:
				break;
			}

			//  2013/02/27
		}
	}

	//
	if (hCtrl == m_var.av.hCtrl_peer) {
		if (!bMeImages
			&& pDlgMgrVar->av.taskInfo.bTaskExists
			&& pDlgMgrVar->av.taskInfo.iTaskId == pMsg->iTaskId
			&& pDlgMgrVar->av.taskInfo.mosaicTrans.bExists_confMosaic)
		{
			//

			//
			if (pDlgMgrVar->av.taskInfo.mosaicTrans.status.ucb2Streams) {
				if (pMsg->uiTranNo_openAvDev == pDlgMgrVar->av.taskInfo.mosaicTrans.status.uiTranNo_openAvDev_confMosaic_resource) {
					if (isTalkerShadowMgr(m_var.addr)) {
						if (CONST_qyWmRc_ok != SendMessage(pProcInfo->dlg2ndScreen.hWnd_2ndScreen, CONST_qyWm_comm, 0, (LPARAM)pMsg)) {
							if (!IsWindow(pProcInfo->dlg2ndScreen.hWnd_2ndScreen)) {
								pProcInfo->dlg2ndScreen.hWnd_2ndScreen = NULL;
							}
						}
					}
					iErr = 0;  goto  errLabel;
				}
			}
			
			//			
			if (pMsg->uiTranNo_openAvDev == pDlgMgrVar->av.taskInfo.mosaicTrans.status.uiTranNo_openAvDev_confMosaic_video) {
				//  2023/01/28. 为了减少一次闪烁，在这里把usIndex设为0，不是个好方法
				pMsg->usIndex = 0;

			}
						
			//
			if (pMsg->bih.biWidth > 1000) {
				int  iii = 0;
			}

			//
			int  ii = 0;
			//
		}
	}



	//  2016/02/16
	BOOL			bRemoteVideo = FALSE;
	BOOL			bAddedManually = FALSE;
	//
	BOOL			bZoneOk = FALSE;
	if (pZone) {
		CAP_IMAGES* pImgs = &pZone->images;
		if (pZoneParam->index_capImage >= 0 && pZoneParam->index_capImage < mycountof(pImgs->mems)) {
			CAP_IMAGE* pImg = &pImgs->mems[pZoneParam->index_capImage];
			if (pImg->idInfo_sender.ui64Id == pMsg->idInfo_sender.ui64Id
				&& pImg->uiTranNo_openAvDev == pMsg->uiTranNo_openAvDev
				&& pImg->usIndex_activeMems_from == pMsg->usIndex)
			{
				bZoneOk = TRUE;
			}
		}
	}

	//
#ifdef  __DEBUG__
		//  if  (  !bMeImages  ) traceLog(  _T(  "dlgTalk: bZoneOk %d, index_player %d, usIndex %d, index_capImage %d, "  ),  bZoneOk,  pMsg->index_player,  pMsg->usIndex,  pPlayer->video.m_var.zoneParam.index_capImage  );
		//if  (  !bZoneOk  )  
	if (!bMeImages)
	{
		//traceLog(  _T(  "dlgTalk: bZoneOk %d, %I64u, index_player %d, usIndex %d, index_capImage %d, iTaskId %d"  ),  bZoneOk,  pMsg->idInfo_peer.ui64Id,  pMsg->index_player,  pMsg->usIndex,  pZoneParam->index_capImage,  pMsg->iTaskId  );
		//traceLog(  _T(  "dlgTalk_procVideo: msg.tn %d, iTaskId %d"  ),  pMsg->uiTranNo_openAvDev,  pMsg->iTaskId  );
	}
#endif

	//
	if (!bZoneOk) {
		memset(pZoneParam, 0, sizeof(pZoneParam[0]));
		//					  
		if (hDlg == pProcInfo->hWnd_testWebcam) {
#ifndef  __WINCE__
			traceLog(_T("In pc, dlgTalk can't be hWnd_testWebcam"));
			goto  errLabel;
#endif			
		}
		else {
			BOOL				bFound = FALSE;
			if (!pMsg->iTaskId) {
#ifdef  __DEBUG__
				traceLogA("dlgTalk::OnQyComm failed: iTaskId is 0");
#endif
				goto  errLabel;
			}
			if (!pMsg->meOnBgWall.bMeDisplayedOnBgWall) {
				/*
				MIS_MSG_TASK	*	pMsgTask;
				if  (  (  pMsgTask  =  findTaskInProcessQ(  pDlgMgrVar,  pMsg->iTaskId  )  )  )  {
					if  (  !bTaskAlive(  pMsgTask->iStatus  )  )  goto  errLabel;
					bFound  =  TRUE;
				}
				*/
				int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, pMsg->iTaskId);
				QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
				if (pTaskInfo) {
					if (!qmcTaskInfo_bAlive(pProcInfo, index_taskInfo))  goto  errLabel;
					bFound = TRUE;
				}

			}
			if (!bFound) {
				//  2012/04/25
				TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pDlgMgrVar->pShadowInfo;
				for (i = 0; i < mycountof(pShadowMgr->talkerDynBmps); i++) {
					TALKER_dynBmp* pTalkerDynBmp = &pShadowMgr->talkerDynBmps[i];
					if (pMsg->iTaskId == pTalkerDynBmp->taskInfo.iTaskId) {
						bFound = TRUE;

						//  2016/02/18
						bRemoteVideo = TRUE;

						//  2016/02/16
						if (!pShadowMgr->vwRuleCmd.dynBmpRules[i].helpInfo.ucbAddedManually) {
							//
							time_t	t;  mytime(&t);  // 注意这里要刷新一下时间，表明任务是活跃的。
							pTalkerDynBmp->taskInfo.tStartTime_processed = t;
						}
						else {
							bAddedManually = TRUE;
						}
						//
						if (!pTalkerDynBmp->taskInfo.srcInfo.iW || !pTalkerDynBmp->taskInfo.srcInfo.iH) {
							pTalkerDynBmp->taskInfo.srcInfo.iW = pMsg->pkt.bih.biWidth;
							pTalkerDynBmp->taskInfo.srcInfo.iH = pMsg->pkt.bih.biHeight;
							pTalkerDynBmp->taskInfo.srcInfo.ucbUnresizable = pMsg->pkt.decInfo.ucbUnresizable;
							//  2015/10/23
							showInfo_open0(0, 0, _T("dlgTalk_procVideo: talkerDynBmp w,h got"));
							//
							askToRefreshLayout_mgr(hDlg);
						}
						//
						//  break;
					}
					continue;
				}
			}
			//  2014/09/29
			if (!bFound) {
				if (pDlgMgrVar->av.taskInfo.bTaskExists
					&& pDlgMgrVar->av.taskInfo.ucbStarter)
				{
					HWND	hMgr = hDlg;
					if (!isTalkerShadowMgr(m_var.addr)) {
						TALKER_shadow* pShadow = (TALKER_shadow*)m_var.pShadowInfo;
						if (!pShadow)  goto  errLabel;
						hMgr = pShadow->hMgr;
					}
					//
					QIS_res_obj		tmp_dynBmp;
					unsigned  short	usIndex_active = FALSE;
					//
					if (pMsg->meOnBgWall.bMeDisplayedOnBgWall) {  //  2014/11/29
						if (confStarter_bMeOnBgWall(hMgr, pDlgMgrVar, NULL, &usIndex_active)) {
							tmp_dcDrawParam.usIndex_active = usIndex_active;
							bFound = TRUE;
						}
					}
					else {
						//
						if (confStarter_bTaskInBgWall(hMgr, pDlgMgrVar, pMsg->iTaskId, &tmp_dynBmp, &usIndex_active)) {
							tmp_dcDrawParam.usIndex_active = usIndex_active;
							bFound = TRUE;
						}
					}
				}
			}
			//
			if (!bFound) {
				//
				if (pMsg->pkt.uiTaskType == CONST_imTaskType_viewDynBmp) {
					if (pMsg->pkt.decInfo.dynBmp.resObj.uiObjType == CONST_objType_smallStream) {
						DWORD  dwTickCnt = GetTickCount();
						if (dwTickCnt - pDlgMgrVar->av.taskInfo.dwLastTickCnt_confStarter_sendReq_toStopSending > 200) {
							pDlgMgrVar->av.taskInfo.dwLastTickCnt_confStarter_sendReq_toStopSending = dwTickCnt;	//  不要发的太快了
							//
							MSGR_ADDR  addr;
							memset(&addr, 0, sizeof(addr));
							addr.idInfo.ui64Id = pMsg->pkt.decInfo.dynBmp.idInfo.ui64Id;
							if (!addr.idInfo.ui64Id || addr.idInfo.ui64Id == m_var.pMisCnt->idInfo.ui64Id) {
								goto  errLabel;
							}
							//
							QY_MESSENGER_ID  idInfo_imGrp_related;
							idInfo_imGrp_related.ui64Id = m_var.addr.idInfo.ui64Id;
							//
							BOOL  bOutputDirectly = TRUE;
							LPCTSTR  tmppHint = _T("talk_procV: ");
							procSendTaskProcReq(m_var.pMisCnt, CONST_qyCmd_sendMedia, CONST_imOp_stopSending, 0, 0, 0, idInfo_imGrp_related, pMsg->iTaskId, 0, &pMsg->pkt.decInfo.dynBmp, CONST_channelType_media, bOutputDirectly, tmppHint, &addr);
						}


					}
				}
				//
#ifdef  __DEBUG__
				traceLog(_T("dlgTalk_OnQyComm failed: findTaskInProcessQ failed, iTaskId %d"), pMsg->iTaskId);
#endif
				goto  errLabel;
			}

			//  {	//  2010/09/12
			if (!bMeImages
				&& !tmp_dcDrawParam.bBgWall
				&& pDlgMgrVar->av.taskInfo.bTaskExists
				&& pDlgMgrVar->av.taskInfo.iTaskId == pMsg->iTaskId
				//  &&  m_var.av.taskInfo.ucbVideoConference  
				)
			{
				QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, pDlgMgrVar->av.taskInfo.iIndex_taskInfo);
				if (!pTaskInfo)  goto  errLabel;
				if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  goto  errLabel;
				QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;

				//
				if (pZone) {
					CAP_IMAGES* pImgs = &pZone->images;
					CAP_IMAGE* pImg = NULL;
					int				i;

					for (i = 0; i < mycountof(pImgs->mems); i++) {
						pImg = &pImgs->mems[i];
						if (pImg->iTaskId == pMsg->iTaskId
							//&&  pImg->idInfo_sender.ui64Id  ==  pMsg->idInfo_sender.ui64Id  
							&& !isVideoActive(pDlgMgrVar->pMisCnt, &pTc->videoConference, &pMsg->idInfo_sender, pMsg->uiTranNo_openAvDev, mynull)
							)
						{
							//  freeCapImage(  hDlg,  0,  pImg  );
							freeCapImage(hDlg, hCtrl, pImg, M_GetDlgItem(hDlg, hCtrl));
						}
					}


					//  2014/11/12
					if (pDlgMgrVar->av.taskInfo.mosaicTrans.bExists_confMosaic) {
						BOOL							bPermitted = FALSE;

						//DLG_talk_mosaicTransStatus	status;
						//memset(&status, 0, sizeof(status));
						//
						if (pMsg->idInfo_sender.ui64Id == pDlgMgrVar->av.taskInfo.idInfo_starter.ui64Id) {
							//
#if  0
							QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, pDlgMgrVar->av.taskInfo.iIndex_taskInfo);
							if (!pTaskInfo)  goto  errLabel;
							QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
							if (pTc->common.uiType != CONST_taskDataType_conf)  goto  errLabel;
							//
							unsigned  int  uiTranNo_openAvDev_confMosaic_video = 0;
							unsigned  int  uiTranNo_openAvDev_confMosaic_resource = 0;
							//
							bool  bFound_mosaic = false;
							for (i = 0; i < pTc->videoConference.usCntLimit_activeMems_from; i++) {
								DLG_TALK_videoConferenceActiveMemFrom* pActiveMem_from = &pTc->videoConference.activeMems_from[i];
								if (pActiveMem_from->avStream.idInfo.ui64Id == pDlgMgrVar->av.taskInfo.idInfo_starter.ui64Id) {
									switch (pActiveMem_from->avStream.obj.resObj.uiObjType) {
									case  CONST_objType_mosaicStream_video:
										uiTranNo_openAvDev_confMosaic_video = pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev;
										bFound_mosaic = true;
										break;
									case  CONST_objType_mosaicStream_resource:
										uiTranNo_openAvDev_confMosaic_resource = pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev;
										bFound_mosaic = true;
										break;
									default:
										break;
									}
								}
								//
								//if (bFound_mosaic)  break;
								//
								continue;
							}
#endif

							//
							if (pMsg->uiTranNo_openAvDev == pDlgMgrVar->av.taskInfo.mosaicTrans.status.uiTranNo_openAvDev_confMosaic_video) {
								bPermitted = TRUE;
								//
							}
							else  if (pMsg->uiTranNo_openAvDev == pDlgMgrVar->av.taskInfo.mosaicTrans.status.uiTranNo_openAvDev_confMosaic_resource) {
								bPermitted = TRUE;
								//
#if 0
								status.bDisplayResource = TRUE;
								status.iW_resource = pMsg->bih.biWidth;
								status.iH_resource = pMsg->bih.biHeight;
#endif
							}
							//  2014/11/29. 对发起方传来的视频，不clip比较好
							ucbAutoClip = FALSE;
						}
						if (!bPermitted) {
#ifdef  __DEBUG__
							traceLog(_T("dlgTalk_procVideo faied: %I64u is not an valid mosaic video"), pMsg->idInfo_sender.ui64Id);
#endif
							goto  errLabel;
						}
#if 0
						if (memcmp(&status, &pDlgMgrVar->av.taskInfo.mosaicTrans.status, sizeof(status))) {  //  2014/11/16
							pDlgMgrVar->av.taskInfo.mosaicTrans.status = status;
							askToRefreshLayout_mgr(hDlg);
							//
#ifdef  __DEBUG__
							traceLog((TCHAR*)_T("dlgTalk_procVideo: mosaic.status changed, after askToRefreshLayout_mgr "));
#endif
						}
#endif
					}
					else {
						QY_MESSENGER_ID	idInfo_sender;
						idInfo_sender.ui64Id = pMsg->idInfo_sender.ui64Id;
						//if  (  !isMemFromActive(  &pTc->videoConference,  &idInfo_sender,  null,  NULL  )  )  
						if (!isVideoActive(m_var.pMisCnt, &pTc->videoConference, &idInfo_sender, pMsg->uiTranNo_openAvDev, NULL))
						{
#ifdef  __DEBUG__
							traceLog(_T("dlgTalk_procVideo faied: %I64u is not an activeMem"), pMsg->idInfo_sender.ui64Id);
#endif
							goto  errLabel;
						}
					}

					//
					if (pMsg->usIndex >= mycountof(pImgs->mems))  goto  errLabel;

					//  2023/01/28
#if 0
					for (int n = 0; n < mycountof(pImgs->mems); n++) {
						//
						if (n == pMsg->usIndex) continue;
						pImg = &pImgs->mems[n];
						//
						if (pImg->idInfo_sender.ui64Id == pMsg->idInfo_sender.ui64Id
							&& pImg->uiTranNo_openAvDev == pMsg->uiTranNo_openAvDev)
						{
							freeCapImage(hDlg, hCtrl, pImg, M_GetDlgItem(hDlg, hCtrl));
						}
					}
#endif
					//
					pImg = &pImgs->mems[pMsg->usIndex];
					//  freeCapImage(  hDlg,  0,  pImg  );
					freeCapImage(hDlg, hCtrl, pImg, M_GetDlgItem(hDlg, hCtrl));

					pImg->iW_org = pMsg->bih.biWidth;
					pImg->iH_org = pMsg->bih.biHeight;
					pImg->idInfo_sender.ui64Id = pMsg->idInfo_sender.ui64Id;
					pImg->uiTranNo_openAvDev = pMsg->uiTranNo_openAvDev;
					pImg->usIndex_activeMems_from = pMsg->usIndex;
					pImg->iTaskId = pMsg->iTaskId;	//  2017/08/28   

					pImgs->head.bResized = TRUE;

					//
					if (pImgs->mems[0].iW_org > 1000) {
						int  ii = 0;
					}
				}
			}
			//  2014/10/02
			if (!bMeImages
				&& pDlgMgrVar->av.taskInfo.bTaskExists
				&& tmp_dcDrawParam.bBgWall)
			{
				//
				//
#if  0
				CAP_IMAGE* pImg = NULL;

				if (tmp_dcDrawParam.usIndex_active >= mycountof(pImgs->mems))  goto  errLabel;
				pImg = &pImgs->mems[tmp_dcDrawParam.usIndex_active];
				//  freeCapImage(  hDlg,  0,  pImg  );
				freeCapImage(hDlg, idc, pImg, old_M_GetDlgItem(hDlg, idc));
#endif
				//
				if (tmp_dcDrawParam.usIndex_active >= mycountof(m_var.av.bgWall.mems)) {
					goto  errLabel;
				}
				pZoneParam->index_zone = tmp_dcDrawParam.usIndex_active;
				pZone = &m_var.av.bgWall.mems[tmp_dcDrawParam.usIndex_active];
				CAP_IMAGES* pImgs = &pZone->images;
				//  2017/09/26
				freeCapImages(hDlg, hCtrl, pImgs, NULL, NULL);
				//
				pImgs->head.bResized = TRUE;

				//
			}
			//  2012/05/22
			if (bMeImages
				&& pDlgMgrVar->av.taskInfo.bTaskExists
				&& pDlgMgrVar->av.taskInfo.iTaskId == pMsg->iTaskId
				)
			{

#if  0

				BOOL					bCurUsr = FALSE;
				QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, pDlgMgrVar->av.iIndex_sharedObj_localAv);
				if (pSharedObj && pSharedObj->iIndex_curUsr == pDlgMgrVar->av.iIndex_usr_localAv)  bCurUsr = TRUE;

				if (!bCurUsr) {
#ifdef  __DEBUG__
					traceLog(_T("dlgTalk_procVideo failed: meImages, not curUsr"));
#endif
					goto  errLabel;
				}
#endif

			}
			//  }
		}
	}

	//
	//  2013/07/17
	if (isTalkerShadowMgr(m_var.addr)) {

		pDlgMgrVar = &m_var;
		//
		TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)m_var.pShadowInfo;
		if (!pShadowMgr)  goto  errLabel;

		//  2014/09/04
#ifdef  __DEBUG__	//  2014/09/04
		//traceLog(  _T(  "msg.usIndex_obj %d"  ),  (  int  )pMsg->dynBmp.usIndex_obj  );
#endif


		//  
		PARAM_msgToShadow	paramMsgToShadow;
		memcpy(&paramMsgToShadow, &pMsg->paramMsgToShadow, sizeof(paramMsgToShadow));
		memset(&pMsg->paramMsgToShadow, 0, sizeof(pMsg->paramMsgToShadow));
		for (i = 0; i < mycountof(pShadowMgr->shadows); i++) {
			TALKER_shadow_mgrMem* pMem = &pShadowMgr->shadows[i];

			if (pMem->hShadow) {

				//  2016/02/16
				if (bRemoteVideo && !bAddedManually) {
#ifdef  __DEBUG__
					//traceLog(  _T(  "dlgTalk_procVideo： bSkipped_remoteVideo_notAddedManually, for a shadow"  )  );
#endif
					continue;
				}

				//
				pMsg->paramMsgToShadow.pDlgMgrVar = &m_var;

#ifdef  __DEBUG__
				//  DLG_TALK_var  *  pTmpTalkVar  =  getDlgTalkVar(  pShadowMgr->shadows[i].hShadow  );
#endif
				if (CONST_qyWmRc_ok != SendMessage(pMem->hShadow, CONST_qyWm_comm, 0, (LPARAM)pMsg)) {
					if (!IsWindow(pMem->hShadow)) {
						pMem->hShadow = NULL;
					}
				}
			}
			else  if (pMem->uiVwRuleType == CONST_vwRuleType_dynBmp) {
				//  2014/09/04
				//
				if (pMem->hWall) {
					BOOL		bMatched = FALSE;
					//

					int		j;
					for (j = 0; j < mycountof(pShadowMgr->talkerDynBmps); j++) {

						if (pMsg->iTaskId != pShadowMgr->talkerDynBmps[j].taskInfo.iTaskId)  continue;

						TALKER_dynBmp& tmp_talkerDynBmp = pShadowMgr->talkerDynBmps[j];
						DYN_BMP_rule& tmp_dynBmpRule = pShadowMgr->vwRuleCmd.dynBmpRules[j];

						//  
						int  k;
						for (k = 0; k < mycountof(pMem->vwRuleCmd.dynBmpRules); k++) {
							//
							if (bSame_dynBmpRule(&pMem->vwRuleCmd.dynBmpRules[k], &tmp_dynBmpRule))  break;
						}
						if (k < mycountof(pMem->vwRuleCmd.dynBmpRules)) {
							pMsg->paramMsgToShadow.tmp_dynBmp.uiObjType = tmp_talkerDynBmp.dynBmpRule.dynBmp.resObj.uiObjType;		//  tmp_dynBmpRule.dynBmp.uiObjType;							
							pMsg->paramMsgToShadow.tmp_dynBmp.usIndex_obj = tmp_talkerDynBmp.dynBmpRule.dynBmp.resObj.usIndex_obj;	//  tmp_dynBmpRule.dynBmp.usIndex_obj;
							bMatched = TRUE;
						}

						//
						if (bMatched) {
							//  2017/09/22
							//pMsg->paramMsgToShadow.pZoneParam  =  &pMem->zoneParam_viewDynBmp;	//  2012/05/06
							//
							pMsg->paramMsgToShadow.uiTranNo_zone = pMem->uiTranNo_spObj;
							//  pMsg->paramMsgToShadow.tmp_dynBmp.idInfo.ui64Id  =  m_var.addr.idInfo.ui64Id;
							if (CONST_qyWmRc_ok != myGuiSendMessage(pMem->hWall, pMem->iWndContentType_wall, CONST_qyWm_comm, 0, (LPARAM)pMsg)) {
#ifdef  __DEBUG__
								traceLog(_T("dlgTalk_procVideo: send dynBmp failed"));
#endif
							}
							else {
								pMem->dwTickCnt_lastRefreshed = GetTickCount();
							}
						}

					}
				}
			}
			//  2014/09/04
			continue;
		}
		memcpy(&pMsg->paramMsgToShadow, &paramMsgToShadow, sizeof(pMsg->paramMsgToShadow));

		//  主窗口必须绘制,因为需要用img的刷新参数来确定是否任务需要重新发起

		//  2016/02/16. 非手工加入的远程视频不能在talker上显示
		if (bRemoteVideo && !bAddedManually) {
#ifdef  __DEBUG__
			//traceLog(  _T(  "dlgTalk_procVideo： bSkipped_remoteVideo_notAddedManually, for talkerShadowMgr"  )  );
#endif
			goto  errLabel;
		}


		//
		QY_PLAYER* pPlayer;

		if (pMsg->playerId.index_player < 0 || pMsg->playerId.index_player >= pProcInfo->av.usCnt_players)  goto  errLabel;
		pPlayer = &pProcInfo->av.pPlayers[pMsg->playerId.index_player];
		//  pZoneParam  =  &pPlayer->video.m_var.zoneParam;

	}



	if (!pMsg->idInfo_peer.ui64Id && pMsg->uiCapType) {

	}

	//
	if (!pZone) {
		showInfo_open0(0, 0, _T("dlgTalk_procVideo failed, pZone is null"));
		goto  errLabel;
	}
	CAP_IMAGES* pImgs = &pZone->images;
	//
	pImgs->head.hWnd_notifyToDraw = hDlg;	//  2014/04/12
	pImgs->head.lUserData = 0;

	//
#ifdef  __DEBUG__
	BOOL  bPeer = hCtrl == m_var.av.hCtrl_peer;
	if (bPeer) {
		pImgs->head.lUserData = TRUE;
		//
		//traceLog(  _T(  "dlgTalk_procVideo: pMsg. idInfo %I64u, usIndex %d"  ),  pMsg->idInfo_sender.ui64Id,  pMsg->usIndex  );
	}
	else {
		pImgs->head.lUserData = FALSE;
	}
	//
	if (hCtrl == m_var.av.hCtrl_bgWall_conf) {
		//traceLog(  _T(  "dlgTalk_procVideo: pMsg. idInfo %I64u, usIndex %d, index_player %d. tn_shadow %d,  index_capBmp %d"  ),  pMsg->idInfo_sender.ui64Id,  pMsg->usIndex,  pMsg->playerId.index_player,  m_var.addr.uiTranNo_shadow,  pZoneParam->index_capImage  );
	}
	//
	if (bMeImages) {
		int  iii;
		iii = 0;
		//
		if (pDcDrawParam) {
			if (!isTalkerShadowMgr(m_var.addr)) {
				pDcDrawParam->dbgInfo.ucbDbgImgs = TRUE;
			}
		}
	}
	//
#endif

	
	//
	if (pMsg->bih.biWidth > 1000) {
		int  iii = 0;
	}


	//
	if (isTalkerShadowMgr(m_var.addr)) {
		TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)m_var.pShadowInfo;
		if (!pShadowMgr)  goto  errLabel;
		//
#if 0
		if (hCtrl == m_var.av.hCtrl_me) {  //  2017/10/02
			if (bMeImages
				&& pDlgMgrVar->av.taskInfo.bTaskExists
				&& pDlgMgrVar->av.taskInfo.iTaskId == pMsg->iTaskId)
			{
				if (CONST_qyWmRc_ok != SendMessage(pProcInfo->dlg2ndScreen.hWnd_2ndScreen, CONST_qyWm_comm, 0, (LPARAM)pMsg)) {
					if (!IsWindow(pProcInfo->dlg2ndScreen.hWnd_2ndScreen)) {
						pProcInfo->dlg2ndScreen.hWnd_2ndScreen = NULL;
					}
				}
			}
		}
#endif
		//
		if (hCtrl == m_var.av.hCtrl_bgWall_conf) {  //  2017/09/22
			//
			if (pShadowMgr->bgWall.hBgWall) {
				if (CONST_qyWmRc_ok != SendMessage(pShadowMgr->bgWall.hBgWall, CONST_qyWm_comm, 0, (LPARAM)pMsg)) {
					if (!IsWindow(pShadowMgr->bgWall.hBgWall)) {
						pShadowMgr->bgWall.hBgWall = NULL;
					}
				}
			}
			//	
		}
	}
	//
	if (pDcDrawParam) {  //  2017/10/02
		if (hCtrl == m_var.av.hCtrl_peer) {
			if (ucbAutoClip) {
				pDcDrawParam->param_getCapImages.bNew = TRUE;
			}
		}
	}
	//
	//if  (  drawCapImages(  old_M_GetDlgItem(  hDlg,  idc  ),  ucbAutoClip,  pMsg,  pCapRect->iX,  pCapRect->iY,  pCapRect->iW,  pCapRect->iH,  pSubWnds,  pZoneParam,  pImgs,  hWnd_dst,  phDc_dst,  pDcDrawParam  )  )  
	if (drawCapImages(pQyMc,  M_GetDlgItem(hDlg, hCtrl), ucbAutoClip, pMsg, pZone->iX, pZone->iY, pZone->iW, pZone->iH, pSubWnds, pZoneParam, pImgs, hWnd_dst, phDc_dst, pDcDrawParam))
	{
#ifdef  __DEBUG__
		traceLog(_T("dlgTalk_procVideo: drawCapImages failed"));
#endif
		goto  errLabel;
	}
	//  2014/11/30
	if (pParam && pParam->bNeed_index_capImage) {
		pParam->index_capBmp = pZoneParam->index_capImage;
	}
	//
	if (isTalkerShadowMgr(m_var.addr)) {
		QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
		if (pTaskInfo) {
			CAP_IMAGES* tmppImgs = nullptr;
			if (pZone == &m_var.av.peerZone) {
				tmppImgs = &pProcInfo->av.confLayout.peerZone.images;
			}
			else  if (pZone = &m_var.av.otherZone) {
				tmppImgs = &pProcInfo->av.confLayout.otherZone.images;
			}
			if (tmppImgs) {
				refreshLayoutCapImages_forD3d(pMsg, tmppImgs,nullptr );
			}
		}
	}
	//
	if (pDcDrawParam) {	//  2013/07/20
		if (pDcDrawParam->bModified_capImg) {
			if (isTalkerShadowMgr(m_var.addr)) {
				//
#ifdef  __DEBUG__
				if (pZone == &m_var.av.peerZone) {
					CAP_images* pImgs = &pZone->images;
						if (m_var.av.peerZone.images.mems[0].idInfo_sender.ui64Id) {
							
								int  ii = 0;
						}
				}
				//
				if (pProcInfo->cfg.debugStatusInfo.ucbPrint_triggerD3d) {
					showInfo_open0(0,0,_T("dlgTalk_procVideo: bModified_capImg true"));
				}
#endif
				//
				dyn_d3dWall_refreshImgs(hDlg, _T("dlgTalk_procVideo"));
			}
		}
	}

	if (isTalkerShadowMgr(m_var.addr)) {
		if (pFuncs->isCliD3d.pf_test_d3dWall_chkImgs) {
			//
			bool  bBreakIfNotSame = false;
			//
#ifdef  __DEBUG__
			bBreakIfNotSame = true;
#endif

			//
			pFuncs->isCliD3d.pf_test_d3dWall_chkImgs(hDlg,bBreakIfNotSame);
		}
	}


	//
	iErr = 0;
errLabel:
	return  iErr;
}






