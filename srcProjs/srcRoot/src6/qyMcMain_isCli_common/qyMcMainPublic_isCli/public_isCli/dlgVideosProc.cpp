

#include	"stdafx.h"
#include	<math.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"

//#include	"DlgVideos.h"
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
#include	"dlgVideosProc.h"


//
int  dlgVideos_procVideo(HWND  m_hWnd,  DLG_videos_var  &m_var,  MIS_MSG_procVideo_qmc* pMsg, int iW_ctrl, int iH_ctrl)
{
	int		iErr = -1;

	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;

	//CDlgDesktopsMon* pBase = this;
	//DLG_desktopsMon_var* pBaseVar = &pBase->m_var;

	//  2017/10/02
	int  iSubtype = 0;// pBaseVar->iSubtype;

	//
	//
	ZONE_PARAM* pZoneParam = NULL;
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
		static  BOOL  b = FALSE;
		if (!b)  traceLogA((char*)"Not finished: dlgVideos, bUseDxSurface shall be processed.");
		b = TRUE;
	}
#endif


	//  if  (  m_var.bVideoConference  )  
	{  //  2010/09/12

		//			
		CAP_IMAGES* pImgs = &m_var.images;
		HWND						hDlg = m_hWnd;

#if  0
		QY_PLAYER* pPlayer;

		if (pMsg->index_player < 0 || pMsg->index_player >= pProcInfo->av.usCnt_players)  goto  errLabel;
		pPlayer = &pProcInfo->av.pPlayers[pMsg->index_player];
#endif

		if (pMsg->playerId.index_player < 0 || pMsg->playerId.index_player >= m_var.usCnt_zoneParams)  goto  errLabel;
		pZoneParam = &m_var.pZoneParams[pMsg->playerId.index_player];

		BOOL			bZoneOk = FALSE;
		if (pZoneParam->index_capImage >= 0 && pZoneParam->index_capImage < mycountof(pImgs->mems)) {
			CAP_IMAGE* pImg = &pImgs->mems[pZoneParam->index_capImage];
			if (pImg->idInfo_sender.ui64Id == pMsg->idInfo_sender.ui64Id
				&& pImg->uiTranNo_openAvDev == pMsg->uiTranNo_openAvDev
				&& pImg->usIndex_activeMems_from == pMsg->usIndex)
			{
				bZoneOk = TRUE;
			}
		}
		//
#ifdef  __DEBUG__
	//  if  (  !bMeImages  ) traceLog(  _T(  "dlgTalk: bZoneOk %d, index_player %d, usIndex %d, index_capImage %d, "  ),  bZoneOk,  pMsg->index_player,  pMsg->usIndex,  pPlayer->video.m_var.zoneParam.index_capImage  );
#endif
//
		if (!bZoneOk) {
			memset(pZoneParam, 0, sizeof(pZoneParam[0]));

			//
#if 0
			if (iSubtype == CONST_dlgVideosSubtype_view) {
				QY_DMITEM* pTable = pBase->m_var.pIdcTable;
				if (!pTable)  goto  errLabel;
				int  idc = (int)pTable->des;
				RECT  rc;
				if (getPicRect(idc, &rc))  goto  errLabel;
				int  iW = rc.right - rc.left;
				int  iH = rc.bottom - rc.top;
				//
				if (pMsg->bih.biWidth != iW || pMsg->bih.biHeight != iH) {
					SetPicRect(pMsg->bih.biWidth, pMsg->bih.biHeight, FALSE);
					showInfo_open0(0, _T(""), _T("dlgVideos::procVideo, pMsg->wXh not matched, call SetPicRect"));
				}
			}
#endif
			//
			if (m_var.bVideoConference) {

				CHelp_getDlgTalkVar	help_getDlgTalkVar;

				DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(m_var.hDlgTalk);
				if (!pDlgTalkVar)  goto  errLabel;


				CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;

				DLG_TALK_var* pMgrVar = NULL;
				if (isTalkerShadowMgr(pDlgTalkVar->addr))  pMgrVar = pDlgTalkVar;
				else {
					TALKER_shadow* pShadow = (TALKER_shadow*)pDlgTalkVar->pShadowInfo;
					if (!pShadow)  goto  errLabel;
					pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(pShadow->hMgr);
					if (!pMgrVar)  goto  errLabel;
				}

				BOOL	bFound = FALSE;
				if (!pMsg->iTaskId) {
					traceLogA((char*)"dlgTalk::OnQyComm failed: iTaskId is 0");
					goto  errLabel;
				}
				MIS_MSG_TASK* pMsgTask;
				if ((pMsgTask = pFuncs->pf_findTaskInProcessQ(pMgrVar, pMsg->iTaskId, FALSE, FALSE))) {
					if (!bTaskAlive(pMsgTask->iStatus))  goto  errLabel;
					bFound = TRUE;
				}
				if (!bFound) {
					//  2012/04/25			
					TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
					for (i = 0; i < mycountof(pShadowMgr->talkerDynBmps); i++) {
						if (pMsg->iTaskId == pShadowMgr->talkerDynBmps[i].taskInfo.iTaskId) {
							bFound = TRUE;
							break;
						}
					}
				}
				if (!bFound) {
#ifdef  __DEBUG__
					traceLog((TCHAR*)_T("dlgTalk_OnQyComm failed: findTaskInProcessQ failed, iTaskId %d"), pMsg->iTaskId);
#endif
					goto  errLabel;
				}

				//  {	//  2010/09/12
				if (pMgrVar->av.taskInfo.bTaskExists
					&& pMgrVar->av.taskInfo.iTaskId == pMsg->iTaskId
					&& pMgrVar->av.taskInfo.ucbVideoConference)
				{
					CAP_IMAGE* pImg = NULL;
					int				i;

					for (i = 0; i < mycountof(pImgs->mems); i++) {
						pImg = &pImgs->mems[i];
						if (pImg->iTaskId == pMsg->iTaskId
							&& pImg->idInfo_sender.ui64Id == pMsg->idInfo_sender.ui64Id)
						{
							//  freeCapImage(  hDlg,  0,  pImg  );
							//int  idc_dst  =  m_var.idc;
							//old_freeCapImage(  hDlg,  m_var.idc,  pImg,  old_M_GetDlgItem(  hDlg,  idc_dst  ),  _T(  "dlgVideos_procVideo.1010"  ));
							freeCapImage(hDlg, m_var.hCtrl, pImg, m_var.hCtrl);
						}
					}

					//
					QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, pMgrVar->av.taskInfo.iIndex_taskInfo);
					if (!pTaskInfo)  goto  errLabel;
					if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  goto  errLabel;
					QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;


					QY_MESSENGER_ID	idInfo_sender;
					idInfo_sender.ui64Id = pMsg->idInfo_sender.ui64Id;
					if (!isMemFromActive(&pTc->videoConference, &idInfo_sender, mynull, NULL)) {
						traceLog((TCHAR*)_T("skipped: %I64u is not an activeMem"), pMsg->idInfo_sender.ui64Id);
						goto  errLabel;
					}

					if (pMsg->usIndex >= mycountof(pImgs->mems))  goto  errLabel;
					pImg = &pImgs->mems[pMsg->usIndex];
					//  freeCapImage(  hDlg,  0,  pImg  );
					//int  idc_dst  =  m_var.idc;
					//old_freeCapImage(  hDlg,  m_var.idc,  pImg,  old_M_GetDlgItem(  hDlg,  idc_dst  ),  _T(  "dlgVideos_procVideo.1032"  ));
					freeCapImage(hDlg, m_var.hCtrl, pImg, m_var.hCtrl);

					pImg->iW_org = pMsg->bih.biWidth;
					pImg->iH_org = pMsg->bih.biHeight;
					pImg->idInfo_sender.ui64Id = pMsg->idInfo_sender.ui64Id;
					pImg->uiTranNo_openAvDev = pMsg->uiTranNo_openAvDev;
					pImg->usIndex_activeMems_from = pMsg->usIndex;

					pImgs->head.bResized = TRUE;
				}
				//  }
			}
		}

				  }

	//  
	//  if  (  drawCapImages(  m_hWnd,  m_var.idc,  &m_var.hDc,  NULL,  m_var.ucbLocalAv,  m_var.ucbAutoClip,  pMsg,  0,  0,  pBaseVar->mems[0].iW,  pBaseVar->mems[0].iH,  NULL,  pZoneParam,  &m_var.images,  bUseDxSurface,  FALSE  )  )  goto  errLabel;
	HWND  hWnd_src = m_var.hCtrl;// old_M_GetDlgItem(m_hWnd, m_var.idc);	//  2014/04/10
	HWND  hWnd_dst = hWnd_src;

	//
	PARAM_dc_draw  dcDrawParam = { 0 };
	//
	if (iSubtype == CONST_dlgVideosSubtype_view) {
		dcDrawParam.param_getCapImages.bNew = TRUE;
	}

	//
	if (drawCapImages(pProcInfo->pQyMc,  hWnd_src, m_var.ucbAutoClip, pMsg, 0, 0, iW_ctrl, iH_ctrl, NULL, pZoneParam, &m_var.images, hWnd_dst, &m_var.hDc, &dcDrawParam))  goto  errLabel;

	//
	iErr = 0;
errLabel:
	return  iErr;

}



#if 10
//
LRESULT  dlgVideos_OnQyComm(HWND  m_hWnd,  DLG_videos_var  *  pm_var,  WPARAM  wParam, LPARAM  lParam)
{
	long				lRet = -1;
	QY_WMBUF_COMM* pComm = (QY_WMBUF_COMM*)lParam;
	//CDlgDesktopsMon* pBase = this;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;
	CTX_qm_thread* pCqt = &pQyMc->gui.ctx_gui_thread;  //  2017/09/28

	//
	int  idc_dst;

	if (!pm_var)return -1;
	DLG_videos_var& m_var = *pm_var;

	if (!pComm)  return  -1;

	if (!m_var.guiData.bInited) {
		//  MACRO_qyAssert(  0,  _T(  "CDlgVideos::OnQyComm, can't be called before inited"  )  );
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("CDlgVideos::OnQyComm, can't be called before inited"));
#endif
		return  -1;
	}

	//
	switch (pComm->uiType) {
	case  CONST_misMsgType_procVideo_qmc: {
		MIS_MSG_procVideo_qmc* pMsg = (MIS_MSG_procVideo_qmc*)pComm;
		//
		int iW_ctrl = 0;
		int iH_ctrl = 0;
		RECT  rcCtrl;
		GetClientRect(m_var.hCtrl, &rcCtrl);
		iW_ctrl = rcCtrl.right - rcCtrl.left;
		iH_ctrl = rcCtrl.bottom - rcCtrl.top;
		//
		if (dlgVideos_procVideo(m_hWnd, m_var,pMsg,iW_ctrl,iH_ctrl))  goto  errLabel;
		//
		if (m_var.showResolutionInTitle.ucbNeedShow) {
			if (!m_var.showResolutionInTitle.ucbDone) {
				TCHAR   tBuf[128] = _T("");
				GetWindowText(m_hWnd,  tBuf, mycountof(tBuf));
				_sntprintf(tBuf, mycountof(tBuf), _T("%s %dX%d"), tBuf, pMsg->bih.biWidth, pMsg->bih.biHeight);
				SetWindowText(m_hWnd,tBuf);
				m_var.showResolutionInTitle.ucbDone = TRUE;
			}
		}
	}
										break;

	case  CONST_qyWmParam_freeCapImage:
		QY_MESSENGER_ID	idInfo;
		idInfo.ui64Id = pComm->u.freeCapImage.idInfo.ui64Id;
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

	lRet = QY_RC_WMOK;

errLabel:

	return  lRet;
}
#endif



//
LRESULT  dlgVideos_OnQyPostComm(HWND  m_hWnd,  DLG_videos_var  * pm_var,  WPARAM  wParam, LPARAM  lParam)
{
	long				lRet = -1;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	DLG_videos_var& m_var = *pm_var;

	switch (wParam) {
	case  CONST_qyWmParam_guiMsgArrive:
		doWnd_guiMsgArrive(pProcInfo, lParam, m_hWnd, TRUE, m_var.pMsgBuf_doWnd_guiMsgArrive);
		break;
	default:
		break;
	}

	//  errLabel:

	return  lRet;
}


//
int dlgVideos_OnTimer(HWND  m_hWnd, DLG_videos_var &m_var)
{
	//
	//CDlgDesktopsMon* pBase = this;
	//int  idc  =  (  int  )m_var.idc;
	HWND  hCtrl = m_var.hCtrl;

	//
#ifdef  __DEBUG__
	MACRO_qyAssert(m_var.iMAX_timeoutInS_dlgVideos, _T("err: iMAX_timeoutInS_dlgVideos is 0"));
#endif


	int  k;
	DWORD  dwTickCnt = GetTickCount();
	for (k = 0; k < mycountof(m_var.images.mems); k++) {
		CAP_IMAGE* pImg = &m_var.images.mems[k];
		if (!pImg->iW_org || !pImg->iH_org)  continue;


		//  is active
		if (dwTickCnt - pImg->dwTickCnt_lastDrawing < m_var.iMAX_timeoutInS_dlgVideos * 1000)  continue;

		//
		//HWND  hCtrl  =  ::GetDlgItem(  m_hWnd,  idc  );
		//	
		//old_freeCapImageByTaskId(  this->m_hWnd,  (  int  )idc,  pImg->iTaskId,  &m_var.images,  hCtrl  );
		freeCapImageByTaskId(m_hWnd, m_var.hCtrl, pImg->iTaskId, &m_var.images, hCtrl);
	}




	return  0;

}


void dlgVideos_OnDestroy(HWND  m_hWnd, DLG_videos_var&m_var)
{
	if (!m_hWnd) {
		return;
	}
	QY_MC* pQyMc = QY_GET_GBUF();

	MACRO_safeFree(m_var.pZoneParams);							//  2012/05/05

	MACRO_safeFree(m_var.pMsgBuf_doWnd_guiMsgArrive);			//  2009/12/08

	//int  idc_dst  =  m_var.idc;
	//old_freeCapImages(  this->m_hWnd,  m_var.idc,  &m_var.images,  old_M_GetDlgItem(  m_hWnd,  idc_dst  ),  &m_var.hDc,  _T(  "dlgVideos.OnDestroy.846"  ));
	freeCapImages(m_hWnd, m_var.hCtrl, &m_var.images, m_var.hCtrl, &m_var.hDc);


	//CDlgDesktopsMon::OnDestroy();

	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë
	return;
}


