





#include	"stdafx.h"
#include	<Windows.h>
#include	"qyMcMainCommon.h"
//#include <ctxQmc_sm.h>
#include	"myCmdParams_open.h"
#include	"myTChar.h"
#include	"hgCommProc.h"
#include	"ctxQmc.h"
#include	<time.h>
#include	"qyMsgFunc.h"
#include	"isCliHelpPublic.h"
#include <isCliD3dPublic.h>
#include	"dlgtalkproc.h"


//
int addToImgs(unsigned  __int64 ui64Id, unsigned  int  tn_a,  unsigned  int  tn_v, int iW_org, int iH_org, int  iTaskId,  CAP_IMAGES* pImgs)
{
	int  iErr = -1;
	int  i;

	//
	if (!ui64Id )  return  -1;
	//
	if (!tn_a && !tn_v) {
		return  -1;
	}
	if (tn_v) {
		if (!iW_org || !iH_org) {
			return  -1;
		}
	}
	if (!iTaskId)  return  -1;

	//
	do {
		for (i = 0; i < mycountof(pImgs->mems); i++) {
			CAP_image* pImg = &pImgs->mems[i];
			if (ui64Id  ==  pImg->idInfo_sender.ui64Id
				&&  tn_a  ==  pImg->tn_a				//  增加对tn_a的判断
				&& tn_v == pImg->uiTranNo_openAvDev
				&&  iTaskId  ==  pImg->iTaskId  )
			{
				break;
			}
		}
		if (i < mycountof(pImgs->mems)) {
			iErr = 0;  break;
		}
		for (i = 0; i < mycountof(pImgs->mems); i++) {
			CAP_image* pImg = &pImgs->mems[i];
			if (!pImg->idInfo_sender.ui64Id
				&& !pImg->uiTranNo_openAvDev
				&&  !pImg->iTaskId  )
			{
				break;
			}
		}
		if (i == mycountof(pImgs->mems)) {
			showInfo_open0(0, 0, _T("addToImgs failed, too many imgs"));
			break;
		}
		CAP_image* pImg = &pImgs->mems[i];

		pImg->idInfo_sender.ui64Id = ui64Id;
		//
		pImg->tn_a = tn_a;
		//
		pImg->uiTranNo_openAvDev = tn_v;
		pImg->iW_org = iW_org;
		pImg->iH_org = iH_org;
		pImg->iTaskId = iTaskId;
		
		//
		iErr = 0;
	} while (false);

	//
	return  iErr;
}


//
#ifdef  __DEBUG__
int printLayoutCapImages(CAP_images* pImgs, LPCTSTR  hint)
{
	TCHAR  tBuf[256]  =  _T(  ""  );
	if (!hint)  hint = _T("");

	int  i;
	for (i = 0; i < mycountof(pImgs->mems); i++) {
		CAP_image* pImg = &pImgs->mems[i];
		if (pImg->idInfo_sender.ui64Id) {
			_sntprintf(tBuf, mycountof(tBuf), _T("%s: [%d]: %I64u,%d, %dx%d, pktType %d\n"), hint, i, pImg->idInfo_sender.ui64Id, pImg->uiTranNo_openAvDev, pImg->iW_org, pImg->iH_org,  (int)pImg->usPktResType);
			traceLog(tBuf);
		}
	}


	//
	return  0;
}
#endif


//
HWND  getConfTalker(int index_taskInfo)
{
	HWND  hRet = nullptr;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	//
	do {
		QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
		if (!pTaskInfo)  break;
		if (!pTaskInfo->bUsed)break;
		//
		QMC_taskData_common* pTaskData = (QMC_taskData_common*)pTaskInfo->var.pTaskData;
		if (pTaskData->uiType != CONST_taskDataType_conf)  break;
		if (pTaskData->msgU.uiType != CONST_misMsgType_task)  break;
		QY_MESSENGER_ID  idInfo_peer = pTaskData->msgU.task.addr_logicalPeer.idInfo;
		HWND  hTalk = nullptr;
		if (findTalker(pQyMc, &idInfo_peer, &hTalk))break;
		hRet = hTalk;
		//
	} while (false);

	//	
	return  hRet;
}


//
//  话筒列表决定了有哪些player,所以，在停止发言后，需要检查不在话筒列表里的player,使其尽快退出。
//  以免干扰后面的申请发言
//
int  chkPeerZonePlayers(LPCTSTR  hint)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	//
	int  i;
	QY_PLAYER* pPlayer;

	//
	CAP_IMAGES* pImgs = &pProcInfo->av.confLayout.peerZone.images;

	//
	for (i = 0; i < pProcInfo->av.usCnt_players; i++) {
		pPlayer = &pProcInfo->av.pPlayers[i];
		//pPlayAudio = &pProcInfo->av.pPlayers[i].audio;
		//pPlayVideo = &pProcInfo->av.pPlayers[i].video;

		//
		if (!pPlayer->idInfo_recorder.ui64Id)continue;
		//  没视频的别检查了
		if (!pPlayer->video.uiTranNo)  continue;
		
		//
		bool  bFound = false;
		//
		int  j;
		for (j = 0; j < mycountof(pImgs->mems); j++) {
			CAP_IMAGE* pImg = &pImgs->mems[j];
			//
			if (pImg->idInfo_sender.ui64Id == pPlayer->idInfo_recorder.ui64Id
				&& pImg->uiTranNo_openAvDev == pPlayer->video.uiTranNo
				&& pImg->iTaskId == pPlayer->iTaskId
				)
			{
				bFound = true;
				break;
			}
			continue;
		}

		//
		if (bFound) {
			continue;
		}

		//
		TCHAR  tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("chkPeerZonePlayers: index_player %d need be freed"), i);
		showInfo_open0(0, 0, tBuf);

		//
		pPlayer->bNeedEnd1 = true;

		//
		continue;
	}



	//
	return  0;
}




//
int refreshConfLayout(int index_taskInfo)
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	QMC_TASK_INFO* pTaskInfo = (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
	if (!pTaskInfo)  return  -1;

	if (!pTaskInfo->bUsed)  return  -1;

	int  i;

	//
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("refreshConfLayout called"));
#endif


	//
	INFO_recvResource ir = { 0 };
	bTaskExists_recvResource1(index_taskInfo, &ir);

	//
	int  layout = CONST_usLayoutType_dialog;
	if (ir.nScreens || ir.nMediaFiles) {
		layout = CONST_usLayoutType_training;
	}

	//
	do {
		QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
		if (pTaskData->uiType != CONST_taskDataType_conf)  break;

		QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskData;
		DLG_TALK_videoConference* pVideoConference = &pTc->videoConference;

		//
		myZONE peerZone = { 0 };
		myZONE otherZone = { 0 };

		//
		CAP_images* pImgs = nullptr;

		//
		if (layout == CONST_usLayoutType_dialog) {
			for (i = 0; i < pVideoConference->usCntLimit_activeMems_from; i++) {
				DLG_TALK_videoConferenceActiveMemFrom* pActiveMem = &pVideoConference->activeMems_from[i];
				if (!pActiveMem->avStream.idInfo.ui64Id)  continue;
				
				//
				int  tn_a = pActiveMem->avStream.obj.tranInfo.audio.uiTranNo_openAvDev;

				//
				int  iW_org = pActiveMem->avStream.obj.tranInfo.video.vh_decompress.bih.biWidth;
				int  iH_org = pActiveMem->avStream.obj.tranInfo.video.vh_decompress.bih.biHeight;

				//
				pImgs = &peerZone.images;
				addToImgs(pActiveMem->avStream.idInfo.ui64Id, tn_a,  pActiveMem->avStream.obj.tranInfo.video.uiTranNo_openAvDev,
					iW_org, iH_org, pTaskInfo->var.iTaskId,  pImgs);
			}

		}
		else if  (  layout==CONST_usLayoutType_training  ) {
			for (i = 0; i < pVideoConference->usCntLimit_activeMems_from; i++) {
				DLG_TALK_videoConferenceActiveMemFrom* pActiveMem = &pVideoConference->activeMems_from[i];
				if (!pActiveMem->avStream.idInfo.ui64Id)  continue;

				//
				int  tn_a = pActiveMem->avStream.obj.tranInfo.audio.uiTranNo_openAvDev;

				//
				int  iW_org = pActiveMem->avStream.obj.tranInfo.video.vh_decompress.bih.biWidth;
				int  iH_org = pActiveMem->avStream.obj.tranInfo.video.vh_decompress.bih.biHeight;

				//
				switch (pActiveMem->avStream.obj.resObj.uiObjType) {
				case  CONST_objType_screen:
					pImgs = &peerZone.images;
					break;
				default:
					pImgs = &otherZone.images;
					break;
				}

				//
				addToImgs(pActiveMem->avStream.idInfo.ui64Id, tn_a,  pActiveMem->avStream.obj.tranInfo.video.uiTranNo_openAvDev,
					iW_org, iH_org, pTaskInfo->var.iTaskId, pImgs);
			}


		}
		else {
			 showInfo_open0(  0,  0,  _T(  "getTaskAvLayout failed, unprocessed layout"));
			 break;
		}

		//
		bool  bChanged = false;
		tmp_CAP_IMAGES  imgs_int;

		//
		pImgs = &peerZone.images;
		//
		if (!isSame_layoutCapImages_forD3d(pImgs, &imgs_int, &pProcInfo->av.confLayout.peerZone.images, false,_T("refreshConfLayout.l246"))) {
			//
			for (i = 0; i < mycountof(pImgs->mems); i++) {
				CAP_image  *  pImg = &pImgs->mems[i];
				CAP_image* pImg_old = &pProcInfo->av.confLayout.peerZone.images.mems[i];
				if  (  pImg->idInfo_sender.ui64Id  
					&&  pImg->uiTranNo_openAvDev  
					&& pImg->idInfo_sender.ui64Id == pImg_old->idInfo_sender.ui64Id
					&& pImg->uiTranNo_openAvDev == pImg_old->uiTranNo_openAvDev
					)
				{
					*pImg = *pImg_old;
				}
			}

			//
			pProcInfo->av.confLayout.peerZone.images = *pImgs;

			//
			chkPeerZonePlayers(_T("refreshConfLayout.l285"));

			//
#ifdef  __DEBUG__
			printLayoutCapImages(&pProcInfo->av.confLayout.peerZone.images, _T("refrehConfLayout"));
#endif
			//
			bChanged = true;
		}

		//
		pImgs = &otherZone.images;
		//
		if (!isSame_layoutCapImages_forD3d(pImgs, &imgs_int, &pProcInfo->av.confLayout.otherZone.images, false,_T("refreshConfLayout.l274"))) {
			//
			for (i = 0; i < mycountof(pImgs->mems); i++) {
				CAP_image* pImg = &pImgs->mems[i];
				CAP_image* pImg_old = &pProcInfo->av.confLayout.otherZone.images.mems[i];
				if (pImg->idInfo_sender.ui64Id
					&& pImg->uiTranNo_openAvDev
					&& pImg->idInfo_sender.ui64Id == pImg_old->idInfo_sender.ui64Id
					&& pImg->uiTranNo_openAvDev == pImg_old->uiTranNo_openAvDev
					)
				{
					*pImg = *pImg_old;
				}
			}

			//
			pProcInfo->av.confLayout.otherZone.images = *pImgs;
			//
#ifdef  __DEBUG__
			printLayoutCapImages(&pProcInfo->av.confLayout.otherZone.images, _T("refrehConfLayout"));
#endif
			//
			bChanged = true;
		}


		//
		if (bChanged) {
			HWND  hTalk = nullptr;
			hTalk = getConfTalker(index_taskInfo);
			if (hTalk) {
				dyn_d3dWall_refreshImgs(hTalk,  (TCHAR*)_T(  "refreshConfLayout.214"  ));
			}
		}

		//
		refreshConfStreamInfos(pTaskInfo->var.iTaskId);

		//
#ifdef  __DEBUG__

#endif

		
		//		
		iErr = 0;

	} while (false);

	
errLabel:
	return  iErr;


}


//
int getStreamInfo(int  iTaskId, unsigned  __int64  ui64Id, int  tn, myStreamInfo  *  pStreamInfo)
{
	int  iErr = -1;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	int  index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, iTaskId);
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
	if (!pTaskInfo)  return  -1;

	//
	if (!ui64Id || !tn)  return -1;

	//
	do {
		if (!pTaskInfo->var.pTaskData)  break;
		if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf) break;
		QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
					
		int  i;

		//
		for (i = 0; i < pTc->videoConference.usCntLimit_activeMems_from; i++) {
			DLG_TALK_videoConferenceActiveMemFrom* pActive = &pTc->videoConference.activeMems_from[i];
			if (pActive->avStream.idInfo.ui64Id==ui64Id
				&&  pActive->avStream.obj.tranInfo.video.uiTranNo_openAvDev  ==  tn)
			{
				pStreamInfo->iHkStatus = pActive->iHkStatus;
				break;
			}
			
			//
			continue;
		}



		//
		iErr = 0;
	} while (false);

	return  iErr;
}



int refreshConfStreamInfos(int  iTaskId)
{
	int  iErr = -1;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	int  index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, iTaskId);
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
	if (!pTaskInfo)  return  -1;

	//
	myZONE* pZone;
	int  i;

	pZone = &pProcInfo->av.confLayout.peerZone;
	for (i = 0; i < mycountof(pZone->images.mems); i++) {
		CAP_image* pImg = &pZone->images.mems[i];
		if (!pImg->idInfo_sender.ui64Id || !pImg->uiTranNo_openAvDev) {
			continue;
		}
		//
		if (getStreamInfo(iTaskId, pImg->idInfo_sender.ui64Id, pImg->uiTranNo_openAvDev, &pZone->streamInfos[i])) {
			memset(&pZone->streamInfos[i], 0, sizeof(pZone->streamInfos[i]));
		}

		//
		continue;
	}

	pZone = &pProcInfo->av.confLayout.otherZone;
	for (i = 0; i < mycountof(pZone->images.mems); i++) {
		CAP_image* pImg = &pZone->images.mems[i];
		if (!pImg->idInfo_sender.ui64Id || !pImg->uiTranNo_openAvDev) {
			continue;
		}
		//
		if (getStreamInfo(iTaskId, pImg->idInfo_sender.ui64Id, pImg->uiTranNo_openAvDev, &pZone->streamInfos[i])) {
			memset(&pZone->streamInfos[i], 0, sizeof(pZone->streamInfos[i]));
		}

		//
		continue;
	}


	//
	iErr = 0;

errLabel:
	return  iErr;
}





