
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

#include	"dlgTalk.h"
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


__declspec(dllexport)  int  refreshGrpMemListStatus(HWND  hCurTalk)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int  iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	CHelp_getDlgTalkVar  help_getDlgTalkVar;

	DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hCurTalk);
	if (!pCurVar)  return  -1;

	HWND  hMgr = hCurTalk;
	DLG_TALK_var* pMgrVar = pCurVar;
	if (!isTalkerShadowMgr(pMgrVar->addr)) {
		TALKER_shadow* pShadow = (TALKER_shadow*)pCurVar->pShadowInfo;
		if (!pShadow)  return  -1;
		hMgr = pShadow->hMgr;
		pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
		if (!pMgrVar)  return  -1;
	}
	TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
	if (!pShadowMgr)  return  -1;

	//
#ifdef  __DEBUG__
#if  1
	showInfo_open0(0, 0, _T("refreshGrpMemListStatus called"));
#endif
#endif

	//
	if (!pMgrVar->av.taskInfo.bTaskExists)  return  0;

	//
	CDlgTalk* pCurTalk = (CDlgTalk*)CWnd::FromHandlePermanent(hCurTalk);
	if (!pCurTalk)  return  -1;
	CListCtrl* pListCtrl = (CListCtrl*)pCurTalk->GetDlgItem(pCurVar->guiData.iIDC_LIST_members);
	if (!pListCtrl)  return  -1;

	//
	TCHAR  tBuf[128] = _T("kks");

	//
#if  0
	QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, pMgrVar->av.iIndex_sharedObj_localAv);
	if (!pSharedObj)  return  -1;
	SHARED_OBJ_USR* pSharedObjUsr = getSharedObjUsr(pSharedObj, pMgrVar->av.iIndex_usr_localAv);
	if (!pSharedObjUsr)  return  -1;
#endif
	TASK_respInfo* pRespInfo = get_respInfo(pProcInfo, pMgrVar->av.taskInfo.iIndex_taskInfo);
	if (!pRespInfo)  return  -1;

	//
	DWORD  dwTickCnt = GetTickCount();

	//
	int  i;
	GrpMemList_status* pGrpMemListStatus = &pCurVar->grpMemList.grpMemListStatus;
	//
	for (i = 0; i < pGrpMemListStatus->usCnt; i++) {
		GrpMem_status* pMem = &pGrpMemListStatus->mems[i];
		//
		if (!pMem->idInfo.ui64Id)  continue;

		//
		int  tmp_usCnt = min(pRespInfo->usCnt, MAX_taskRespInfoMems);
		TASK_respInfo_mem* pRespInfoMem = (TASK_respInfo_mem*)bsearch(&pMem->idInfo, pRespInfo->mems, tmp_usCnt, sizeof(pRespInfo->mems[0]), bCmp_respInfoMem);
		if (!pRespInfoMem) {
			continue;
		}

		//
		if (pMem->usState == pRespInfoMem->var.usState_byDlgTalk)  continue;

		//
		int  nImage_need = pQyMc->cfg.image.nImage_messenger;
		switch (pRespInfoMem->var.usState_byDlgTalk) {
			//
		case  CONST_taskRespInfoMemState_join:
			nImage_need = pQyMc->cfg.image.normal.nImage_pcNormal;
			break;
		case  CONST_taskRespInfoMemState_leave:
			nImage_need = pQyMc->cfg.image.offline.nImage_pcNormal;
			break;
		case  CONST_taskRespInfoMemState_ok:
			nImage_need = pQyMc->cfg.image.normal.nImage_pcNormal;
			break;
		case  CONST_taskRespInfoMemState_warning:
			nImage_need = pQyMc->cfg.image.normalWarn.nImage_pcNormal;
			break;
		case  CONST_taskRespInfoMemState_notInConf:
		case  CONST_taskRespInfoMemState_offline:
		default:
			nImage_need = pQyMc->cfg.image.offline.nImage_pcNormal;
			break;
		}
		//
		if (pMem->nImage != nImage_need)
		{
			//
			LVITEM				lvItem;

			memset(&lvItem, 0, sizeof(lvItem));
			lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
			lvItem.iItem = i;//nItems;
			lvItem.pszText = tBuf;
			lvItem.cchTextMax = mycountof(tBuf);
			pListCtrl->GetItem(&lvItem);

			//
			lvItem.iImage = nImage_need;
			pListCtrl->SetItem(&lvItem);

			//
			pMem->nImage = nImage_need;
		}
		//
		pMem->usState = pRespInfoMem->var.usState_byDlgTalk;
		//
		continue;
	}
	//
	pGrpMemListStatus->dwTickCnt_lastRefreshed = dwTickCnt;


	//
	iErr = 0;
errLabel:


	return  iErr;
}

