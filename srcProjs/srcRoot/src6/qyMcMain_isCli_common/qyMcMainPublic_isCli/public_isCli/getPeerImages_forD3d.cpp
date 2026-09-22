

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
#include	"qyCusResTemp.h"

#include	"dlgTalkProc.h"




//
CAP_images* getLayoutPeerImages_forD3d(DLG_TALK_var* pMgrVar)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (!isTalkerShadowMgr(pMgrVar->addr))  return  nullptr;

	CAP_images* pImgs = nullptr;

	//
	if  ( !pQyMc->appParams.bConfServer ) {
		pImgs = &pMgrVar->av.peerZone.images;
		return  pImgs;
	}


	//
	pImgs = &pProcInfo->av.confLayout.peerZone.images;

	//
#ifdef  __DEBUG__
	if (0) {
		pImgs = &pMgrVar->av.peerZone.images;
	}
#endif

	//
	return  pImgs;
}

//
CAP_images* getLayoutOtherImages_forD3d(DLG_TALK_var* pMgrVar)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (!isTalkerShadowMgr(pMgrVar->addr))  return  nullptr;


	CAP_images* pImgs = nullptr;

	//
	if (!pQyMc->appParams.bConfServer) {
		pImgs = &pMgrVar->av.otherZone.images;
		return  pImgs;
	}


	//
	pImgs = &pProcInfo->av.confLayout.otherZone.images;

	//
#ifdef  __DEBUG__
	if (0) {
		pImgs = &pMgrVar->av.otherZone.images;
	}
#endif

	//
	return  pImgs;
}


//
__declspec(dllexport)  BOOL  bTaskImgActive(HWND  hDlgTalk, DLG_TALK_var* pm_var, MIS_MSG_TASK* pMsgTask, int nElapseInS)
{
	int  iErr = -1;
	//int					nElapseInS = MAX_nElapseInS;	//5;
	int  nTimeoutInS = MAX_nTimeoutInS;//65;


	BOOL			bTaskImgAlive = FALSE;

	time_t			t;
	int			minElapseInMs = nTimeoutInS * 1000 + 1;
	DWORD			dwTickCnt = GetTickCount();
	mytime(&t);

	TCHAR			tBuf[128];


	//
	CAP_IMAGES* pImgs = nullptr;// &pm_var->av.peerZone.images;
	int  i;

	//
	if (!nElapseInS)  nElapseInS = MAX_nElapseInS;


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
	iErr = 0;
errLabel:
	return  iErr ? FALSE : bTaskImgAlive;
}
