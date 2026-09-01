


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





__declspec(dllexport) int  dlgTalk_procTask_display_op(HWND  hDlgTalk, int  iTaskId, unsigned  short  usOp, MIS_MSG_TASK* pMsgTask, IM_TASK_RCD& rcd, int  iStatus_old, int  iStatus, LPCTSTR  paramStrBuf)
{
	int										iErr = -1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk);
	if (!pCurVar)  return  -1;
	DLG_TALK_var* pm_var = pCurVar;

	QY_MC* pQyMc = QY_GET_GBUF();
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	//int										nItem;
	TCHAR									tBuf[256];
#if  10
	CQyMalloc						mallocObj_pParam;
	PARAM_PROC_ROW* pParam = (PARAM_PROC_ROW*)mallocObj_pParam.mallocf(sizeof(PARAM_PROC_ROW));
	if (!pParam)  return  -1;
	PARAM_PROC_ROW& param = *pParam;
#endif

	if (!pm_var)  return  -1;
	DLG_TALK_var& m_var = *pm_var;
	MSG_tool_common* pmsgToolCommon = mynull;

	//  2014/01/26
	if (IsWindow(m_var.msgTool.hWnd_msgTool)) {
		DLG_msgTool_var* pDlgMsgToolVar = (DLG_msgTool_var*)getDlgMsgToolVar(m_var.msgTool.hWnd_msgTool);
		if (!pDlgMsgToolVar)  return  -1;
		pmsgToolCommon = &pDlgMsgToolVar->msgToolCommon;
	}
	HWND  hParent_tool = m_var.msgTool.hWnd_msgTool;

	//
#ifndef	 __WINCE__
		 //  CListCtrl					*	pListCtrl							=	(  CListCtrl  *  )CWnd::FromHandle(  GetDlgItem(  hDlgTalk,  m_var.idcList_task  )  );
		 //  if  (  !pListCtrl  )  goto  errLabel;
	HWND  					hListCtrl = mynull;
	if (pmsgToolCommon) {
		hListCtrl = GetDlgItem(hParent_tool, pmsgToolCommon->idcList_task);
		if (!hListCtrl)  goto  errLabel;
	}
#endif

	//  LP_MyHtmlEditCtrl				pEditCtrl							=	(  LP_MyHtmlEditCtrl  )m_var.m_pHtmlEdit_recentMsgList;	//  pHtmlEditCtrl;



	TCHAR							rowIdStrBuf[32] = _T("");


	if  (  !pProcInfo->bAppQt())
	{
		int  nItem;
		//  iTaskId  =  iTaskId_param;
		//  usOp  =  usOp_param;
		//
		//  nItem  =  getTaskItem(  pListCtrl->m_hWnd,  iTaskId  );
		nItem = getTaskItem(hListCtrl, iTaskId);
		if (nItem < 0) {
			traceLogA("dlgTalk_procTask failed: getTaskItem failed");  goto  errLabel;
		}
		//	  pListCtrl->GetItemText(  nItem,  CONST_nSubItem_rowId_cur,  rowIdStrBuf,  mycountof(  rowIdStrBuf  )  );  
		myListCtrl_GetItemText(hListCtrl, nItem, CONST_nSubItem_rowId_cur, rowIdStrBuf, mycountof(rowIdStrBuf));
	}


	memset(&param, 0, sizeof(param));
#ifdef  __SUPPORT_HTMLEDIT__
	lstrcpyn(param.rowIdStr, rowIdStrBuf, mycountof(param.rowIdStr));
	param.pf = (PF_commonHandler)modifyRow;
	param.iCol = m_var.iCol_content;
#endif


	switch (usOp) {
	case  CONST_imOp_send_permit:
#ifdef  __SUPPORT_HTMLEDIT__
		param.pf = (PF_commonHandler)getlRowIndex;
#if  0
		if (m_var.m_pHtmlEdit_recentMsgList) {
			IHTMLDocument2* pDoc = NULL;
			if (!m_var.m_pHtmlEdit_recentMsgList->GetDHtmlDocument(&pDoc))  goto  errLabel;

			doDoc(pDoc, (PF_commonHandler)doTable_byRowId, 0, &param);
		}
#endif
		if (doDoc_doTable_byRowId_param(&m_var, &param))  goto  errLabel;
		//  
		lstrcpyn(param.rowIdStr, getNextRowIdStr(hDlgTalk), mycountof(param.rowIdStr));
#endif
		param.idInfo_talker.ui64Id = rcd.idInfo_send.ui64Id;
		lstrcpyn(param.content, getResStr(0, &pQyMc->cusRes, CONST_resId_sendAgain), mycountof(param.content));
		//
		if (param.lRowIndex_who_gotByRowId == -1)  param.lRowIndex = -1;
		else  param.lRowIndex = param.lRowIndex_who_gotByRowId + 2;	//  ¼Ó£²ÊÇÒòÎªÓÐ·¢ÑÔÈËºÍÁÄÌìÄÚÈÝ£²ÐÐ
		param.bFollowingRows = TRUE;
		//
		addToRecentMsg(hDlgTalk, &m_var, param.lRowIndex, 0, mynull, mynull, param.idInfo_talker, NULL, CONST_imOp_tryToSendFile, 0, NULL, param.rowIdStr, param.content, param.bFollowingRows, param.bScrollIntoView, param.txtContent, mycountof(param.txtContent));
		//
#ifdef  __SUPPORT_HTMLEDIT__
		activateRowByRowId(hDlgTalk, param.rowIdStr);

		if (!pProcInfo->bAppQt()) {
			int  nItem;

			//  nItem  =  getTaskItem(  pListCtrl->m_hWnd,  rcd.id  );
			nItem = getTaskItem(hListCtrl, rcd.id);
			if (nItem < 0)  break;
			//
			//  pListCtrl->SetItemState(  nItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
			myListCtrl_SetItemState(hListCtrl, nItem, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING);
			//  pListCtrl->Update(  nItem  );
			myListCtrl_Update(hListCtrl, nItem);
		}
#endif

		break;

	case  CONST_imOp_recv_accept:
	case  CONST_imOp_recvFile_saveas:
	case  CONST_imOp_dual_permit:


#ifdef  __SUPPORT_HTMLEDIT__
		if (tmpMakeHtmlStr(pQyMc,(MIS_MSGU*)pMsgTask, iStatus_old, FALSE, rowIdStrBuf, paramStrBuf, &param.idInfo_talker, param.content, mycountof(param.content)))  goto  errLabel;
#if  0
		if (m_var.m_pHtmlEdit_recentMsgList) {
			IHTMLDocument2* pDoc = NULL;
			if (!m_var.m_pHtmlEdit_recentMsgList->GetDHtmlDocument(&pDoc))  goto  errLabel;

			doDoc(pDoc, (PF_commonHandler)doTable_byRowId, 0, &param);
		}
#endif
		if (doDoc_doTable_byRowId_param(&m_var, &param))  goto  errLabel;

		//
		lstrcpyn(param.rowIdStr, getNextRowIdStr(hDlgTalk), mycountof(param.rowIdStr));
#endif
		//  
		if (tmpMakeHtmlStr(pQyMc,(MIS_MSGU*)pMsgTask, iStatus, TRUE, param.rowIdStr, paramStrBuf, &param.idInfo_talker, param.content, mycountof(param.content)))  goto  errLabel;
		//
		if (param.lRowIndex_who_gotByRowId == -1)  param.lRowIndex = -1;
		else  param.lRowIndex = param.lRowIndex_who_gotByRowId + 2;	//  ¼Ó£²ÊÇÒòÎªÓÐ·¢ÑÔÈËºÍÁÄÌìÄÚÈÝ£²ÐÐ
		param.bFollowingRows = TRUE;
		//
		addToRecentMsg(hDlgTalk, &m_var, param.lRowIndex, pMsgTask->iTaskId, mynull, mynull, param.idInfo_talker, NULL, CONST_imOp_tryToSendFile, pMsgTask->iStatus, NULL, param.rowIdStr, param.content, param.bFollowingRows, param.bScrollIntoView, param.txtContent, mycountof(param.txtContent));
		//					
#ifdef  __SUPPORT_HTMLEDIT__
		activateRowByRowId(hDlgTalk, param.rowIdStr);

		if (!pProcInfo->bAppQt()) {
			int  nItem;
			//  2007/07/22, °ÑtaskListµÄ¶ÔÓ¦ÐÐµÄrowIdStr_cur¸ÄÎª´ËÏî
			//  nItem  =  getTaskItem(  pListCtrl->m_hWnd,  rcd.id  );
			nItem = getTaskItem(hListCtrl, rcd.id);
			if (nItem < 0)  break;
			//  pListCtrl->SetItemText(  nItem,  CONST_nSubItem_rowId_cur,  param.rowIdStr  );
			myListCtrl_SetItemText(hListCtrl, nItem, CONST_nSubItem_rowId_cur, param.rowIdStr);
			//  pListCtrl->SetItemText(  nItem,  CONST_nSubItem_iStatus_cur,  _ltot(  iStatus,  tBuf,  10  )  );
			myListCtrl_SetItemText(hListCtrl, nItem, CONST_nSubItem_iStatus_cur, _ltot(iStatus, tBuf, 10));
			//
			//  pListCtrl->SetItemState(  nItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
			myListCtrl_SetItemState(hListCtrl, nItem, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING);
			//  pListCtrl->Update(  nItem  );
			myListCtrl_Update(hListCtrl, nItem);
		}
#endif

		break;

	case  CONST_imOp_recv_deny:
	case  CONST_imOp_recv_cancel:

#ifdef  __SUPPORT_HTMLEDIT__
		if (!pProcInfo->bAppQt()) {
			int  nItem;
			//  nItem  =  getTaskItem(  pListCtrl->m_hWnd,  rcd.id  );
			nItem = getTaskItem(hListCtrl, rcd.id);
			if (nItem < 0)  break;
			//  pListCtrl->SetItemText(  nItem,  m_var.nSubItem_status,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskStatusTable  ),  iStatus  )  );
			myListCtrl_SetItemText(hListCtrl, nItem, m_var.nSubItem_status, qyGetDesByType1(getResTable(0, &pQyMc->cusRes, CONST_resId_imTaskStatusTable), iStatus));
			//  pListCtrl->SetItemText(  nItem,  CONST_nSubItem_iStatus_cur,  _ltot(  iStatus,  tBuf,  10  )  );
			myListCtrl_SetItemText(hListCtrl, nItem, CONST_nSubItem_iStatus_cur, _ltot(iStatus, tBuf, 10));
			//
			//  pListCtrl->SetItemState(  nItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
			myListCtrl_SetItemState(hListCtrl, nItem, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING);
			//  pListCtrl->Update(  nItem  );
			myListCtrl_Update(hListCtrl, nItem);
		}

		//  
		if (tmpMakeHtmlStr(pQyMc,(MIS_MSGU*)pMsgTask, iStatus_old, FALSE, rowIdStrBuf, paramStrBuf, &param.idInfo_talker, param.content, mycountof(param.content)))  goto  errLabel;
		getTalkerDesc(param.idInfo_talker, NULL, 0, param.talker, mycountof(param.talker));
#if  0
		if (m_var.m_pHtmlEdit_recentMsgList) {
			IHTMLDocument2* pDoc = NULL;
			if (!m_var.m_pHtmlEdit_recentMsgList->GetDHtmlDocument(&pDoc))  goto  errLabel;

			doDoc(pDoc, (PF_commonHandler)doTable_byRowId, 0, &param);
		}
#endif
		if (doDoc_doTable_byRowId_param(&m_var, &param))  goto  errLabel;

		//  
		lstrcpyn(param.rowIdStr, getNextRowIdStr(hDlgTalk), mycountof(param.rowIdStr));
#endif
		if (tmpMakeHtmlStr(pQyMc,(MIS_MSGU*)pMsgTask, iStatus, TRUE, rowIdStrBuf, paramStrBuf, &param.idInfo_talker, param.content, mycountof(param.content)))  goto  errLabel;
		//  
		if (param.lRowIndex_who_gotByRowId == -1)  param.lRowIndex = -1;
		else  param.lRowIndex = param.lRowIndex_who_gotByRowId + 2;	//  ¼Ó£²ÊÇÒòÎªÓÐ·¢ÑÔÈËºÍÁÄÌìÄÚÈÝ£²ÐÐ
		param.bFollowingRows = TRUE;
		//
		addToRecentMsg(hDlgTalk, &m_var, param.lRowIndex, pMsgTask->iTaskId, mynull, mynull, param.idInfo_talker, NULL, CONST_imOp_tryToSendFile, pMsgTask->iStatus, NULL, param.rowIdStr, param.content, param.bFollowingRows, param.bScrollIntoView, param.txtContent, mycountof(param.txtContent));
		//
#ifdef  __SUPPORT_HTMLEDIT__
		activateRowByRowId(hDlgTalk, param.rowIdStr);
#endif

		break;

	case  CONST_imOp_send_cancel:
#ifdef  __SUPPORT_HTMLEDIT__
		if (!pProcInfo->bAppQt()) {
			int  nItem;
			nItem = getTaskItem(hListCtrl, iTaskId);
			if (nItem < 0)  break;
			myListCtrl_SetItemText(hListCtrl, nItem, m_var.nSubItem_status, qyGetDesByType1(getResTable(0, &pQyMc->cusRes, CONST_resId_imTaskStatusTable), iStatus));
			myListCtrl_SetItemText(hListCtrl, nItem, CONST_nSubItem_iStatus_cur, _ltot(iStatus, tBuf, 10));
			//
			myListCtrl_SetItemState(hListCtrl, nItem, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING);
			myListCtrl_Update(hListCtrl, nItem);
		}
		//  
		if (tmpMakeHtmlStr(pQyMc,(MIS_MSGU*)pMsgTask, iStatus_old, FALSE, rowIdStrBuf, paramStrBuf, &param.idInfo_talker, param.content, mycountof(param.content)))  goto  errLabel;
		getTalkerDesc(param.idInfo_talker, NULL, 0, param.talker, mycountof(param.talker));
#if  0
		if (m_var.m_pHtmlEdit_recentMsgList) {
			IHTMLDocument2* pDoc = NULL;
			if (!m_var.m_pHtmlEdit_recentMsgList->GetDHtmlDocument(&pDoc))  goto  errLabel;

			doDoc(pDoc, (PF_commonHandler)doTable_byRowId, 0, &param);
		}
#endif
		if (doDoc_doTable_byRowId_param(&m_var, &param))  goto  errLabel;

		//  
		lstrcpyn(param.rowIdStr, getNextRowIdStr(hDlgTalk), mycountof(param.rowIdStr));
#endif

		if (tmpMakeHtmlStr(pQyMc,(MIS_MSGU*)pMsgTask, iStatus, TRUE, rowIdStrBuf, paramStrBuf, &param.idInfo_talker, param.content, mycountof(param.content)))  goto  errLabel;
		//  
		if (param.lRowIndex_who_gotByRowId == -1)  param.lRowIndex = -1;
		else  param.lRowIndex = param.lRowIndex_who_gotByRowId + 2;	//  ¼Ó£²ÊÇÒòÎªÓÐ·¢ÑÔÈËºÍÁÄÌìÄÚÈÝ£²ÐÐ
		param.bFollowingRows = TRUE;
		//
		addToRecentMsg(hDlgTalk, &m_var, param.lRowIndex, pMsgTask->iTaskId, mynull, mynull, param.idInfo_talker, NULL, CONST_imOp_tryToSendFile, iStatus, NULL, param.rowIdStr, param.content, param.bFollowingRows, param.bScrollIntoView, param.txtContent, mycountof(param.txtContent));
		//
#ifdef  __SUPPORT_HTMLEDIT__
		activateRowByRowId(hDlgTalk, param.rowIdStr);
#endif
		break;
	default:
		break;
	}

	iErr = 0;
errLabel:

	return  iErr;

}



__declspec(dllexport) int  dlgTalk_procTask_display_op_mgr(HWND  hDlgTalk_mgr, int  iTaskId, unsigned  short  usOp, MIS_MSG_TASK* pMsgTask, IM_TASK_RCD& rcd, int  iStatus_old, int  iStatus, LPCTSTR  paramStrBuf)
{
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk_mgr);
	if (!pMgrVar)  goto  errLabel;

	DLG_TALK_var* pm_var = pMgrVar;

	if (!isTalkerShadowMgr(pMgrVar->addr))  goto  errLabel;
	TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
	if (!pShadowMgr)  goto  errLabel;

	int  i;


	//
	for (i = 0; i < mycountof(pShadowMgr->shadows); i++) {
		TALKER_shadow_mgrMem* pMem = &pShadowMgr->shadows[i];
		if (pMem->hShadow) {
			dlgTalk_procTask_display_op(pMem->hShadow, iTaskId, usOp, pMsgTask, rcd, iStatus_old, iStatus, paramStrBuf);

		}
	}

	//
	dlgTalk_procTask_display_op(hDlgTalk_mgr, iTaskId, usOp, pMsgTask, rcd, iStatus_old, iStatus, paramStrBuf);


errLabel:

	return  0;
}


//
__declspec(dllexport) int viewQnmStatus()
{
	int						iRet = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	TCHAR						tmpExeName[MAX_PATH + 1];
	STARTUPINFO				si;
	PROCESS_INFORMATION		pi;
	BOOL						bProcessCreated = FALSE;
	DWORD						dwRet;

	traceLogA("installDir is [%s]", pQyMc->cfg.installDir);

	HWND hWnd;
	if (hWnd = FindWindow(NULL, (pQyMc->iAppType != CONST_qyAppType_client) ? CONST_qnmStatusWndTitle : CONST_qnmStatusWndTitle_client)) {
		MACRO_SetForegroundWindow(hWnd);
		goto  errLabel;
	}

	if (pQyMc->gui.hProcessStatusTool) {
		dwRet = ::WaitForSingleObject(pQyMc->gui.hProcessStatusTool, 200);
		if (dwRet != WAIT_TIMEOUT && dwRet != WAIT_FAILED) {
			CloseHandle(pQyMc->gui.hProcessStatusTool);  pQyMc->gui.hProcessStatusTool = NULL;
		}
	}

	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));

	traceLogA("Now start qwm ");
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_FORCEOFFFEEDBACK;

	_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%sbin\\%s"), pQyMc->cfg.installDir, (pQyMc->iAppType == CONST_qyAppType_client) ? _T("qyStatusTool_client.exe") : _T("qyStatusTool_main.exe"));
	if (tQyQuoteFileName(tmpExeName, mycountof(tmpExeName)))  goto  errLabel;

	if (!CreateProcess(NULL, (tmpExeName), NULL, NULL, 0, 0, NULL, NULL, &si, &pi))  goto  errLabel;
	bProcessCreated = TRUE;
	traceLogA("CreateProcess %s succeeded,  new processId is %d,  new threadId is %d.", tmpExeName, pi.dwProcessId, pi.dwThreadId);

	iRet = 0;

errLabel:

	if (bProcessCreated) {
		if (pi.hThread) { CloseHandle(pi.hThread);  pi.hThread = NULL; }
		if (pi.hProcess)  pQyMc->gui.hProcessStatusTool = pi.hProcess;
	}

	return  iRet;
}
