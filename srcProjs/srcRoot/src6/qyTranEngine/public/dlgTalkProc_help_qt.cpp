#include "stdafx.h"
#include "CDlgTalk_qt.h"
#include "ctxQmc.h"
#include <qmcCommFunc_isCli.h>
#include	"isCliHelpPublic.h"
//#include "VideoRenderWidget.h"

//
__declspec(dllexport) void* tmp_getDlgTalkVar_qt(HWND  hDlgTalk)
{
	void* p = NULL;

	QY_WMBUF_COMM  wmBuf;
	memset(&wmBuf, 0, sizeof(wmBuf));
	int  lRet;
	lRet =  ::SendMessage(hDlgTalk, CONST_qyWm_comm, CONST_qyWmParam_getObjAddr, (LPARAM)&wmBuf);
	if (lRet != CONST_qyWmRc_ok)return  NULL;

	CDlgTalk_qt*  pDlgTalk =  (CDlgTalk_qt*  )wmBuf.u.getObjAddr.pObjAddr;
	if (!pDlgTalk)return  NULL;
	p = pDlgTalk->get_pm_var();

	return  p;
}




#if  10
__declspec(dllexport)  int  talkToMessenger_qt(void* pQyMcParam, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkUsage, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr = -1;
	QY_MC* pQyMc = (QY_MC*)pQyMcParam;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;

	RECT						rect;
	COMMON_PARAM				commonParam1;
	MIS_CNT* pMisCnt = NULL;
	HWND						hWnd = NULL;
	int						iRet;
	HWND						hFore = NULL;
	//HWND						hParent = NULL;

	CDlgTalk_qt* pDlgTalk = NULL;

	int						nStep = 0;

	if (!pAddr)  return  -1;

	//
	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("talkToMessenger %I64u, %d: enters"), pAddr->idInfo.ui64Id, pAddr->uiTranNo_shadow);

	//
	if (!(pMisCnt = getMisCntByName(pProcInfo, pAddr->misServName))) {
		nStep = 10;
		goto  errLabel;
	}


	//  2014/04/29
	if (!bDone_retrieveAllImObjRules(pMisCnt)) {
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("talkToMessenger failed: not all imObjRules retrieved"));
		return  -1;
	}

	//  2011/03/01
#ifdef  __SUPPORT_dlgWalls__
		//  viewWalls(  );
#endif


	MACRO_makeCommonParam3((void*)pAddr, (void*)0, (void*)0, commonParam1);
	//
	iRet = qTraverse(&pMisCnt->talkingFriendQ, tmpHandler_findTalker, 0, &commonParam1);
	if (iRet < 0) {
		nStep = 20;
		goto  errLabel;
	}
	else  if (iRet > 0) {
		hWnd = (HWND)commonParam1.p2;
		//
#if 0
		if (isTalkerShadowMgr(*pAddr)) {
			//  2012/04/30. 如果有其他的影子窗口可以接收输入,那么就不把主窗口显示出来
			CHelp_getDlgTalkVar	help_getDlgTalkVar;
			DLG_TALK_var* pVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hWnd);
			if (!pVar) {
				nStep = 30;
				goto  errLabel;
			}
			TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pVar->pShadowInfo;
			if (!pShadowMgr) {
				nStep = 40;
				goto  errLabel;
			}
			int  i;
			for (i = 0; i < mycountof(pShadowMgr->shadows); i++) {
				if (IsWindow(pShadowMgr->shadows[i].hShadow)
					&& isTalkerSubtype_canInput(pShadowMgr->shadows[i].iTalkerSubType))
				{
					break;
				}
			}
			if (i < mycountof(pShadowMgr->shadows)) {
				if (bActivateWnd) {
					PostMessage(pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_setActiveWindow, (LPARAM)pShadowMgr->shadows[i].hShadow);
				}
				iErr = 0;  goto  errLabel;
			}
		}
		//
		if (!bNeedNotShowWnd) {
			CHelp_getDlgTalkVar	help_getDlgTalkVar;
			DLG_TALK_var* pVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hWnd);
			if (!pVar) {
				nStep = 60;
				goto  errLabel;
			}
			if (pVar->guiData.param.bNeedNotShowWnd)  pVar->guiData.param.bNeedNotShowWnd = FALSE;

			//  ShowWindow(  hWnd,  SW_SHOWNOACTIVATE    );
			ShowWindow(hWnd, SW_SHOWNA);
		}
#endif

		if (bActivateWnd) {
			PostMessage(pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_setActiveWindow, (LPARAM)hWnd);
		}

		iErr = 0;  goto  errLabel;

		//
	}
	else {
		if (pAddr->uiTranNo_shadow) {	//  对辅助窗口,不可以在这里建立. 2012/04/22
#ifdef  __DEBUG__
			traceLog((TCHAR*)_T("talkToMessenger failed, primary talker doesn't exists"));
#endif
			nStep = 70;
			goto  errLabel;
		}
	}


	memset(&rect, 0, sizeof(rect));

	if (!bActivateWnd) {		//
		hFore = GetForegroundWindow();
	}




	pDlgTalk = new  CDlgTalk_qt(NULL);
	if (!pDlgTalk) {
		nStep = 80;
		goto  errLabel;
	}
	//pDlgTalk->hide();

	//
	DLG_TALK_var* pm_var = pDlgTalk->get_pm_var();
	if (!pm_var)  goto  errLabel;
	DLG_TALK_var& m_var = *pm_var;

	//
	HWND  m_hWnd = (HWND)pDlgTalk->winId();

	//  if  (  !pDlgTalk->bSetDlgInfo(  0,  pAddr,  pTmpGrpMemQ,  bNeedNotShowWnd,  hFore  )  )  goto  errLabel;
	if (!dlgTalk_bSetDlgInfo(m_hWnd, m_var, pAddr, pTmpGrpMemQ, iTalkUsage, 0, bNeedNotShowWnd, hFore)) {
		nStep = 90;
		goto  errLabel;
	}

	//
	if (dlgTalk_OnInitDialog(m_hWnd, &m_var)) {
		goto  errLabel;
	}


#if  0

	if (!pDlgTalk->Create(rect)) {
		nStep = 100;
		goto  errLabel;
	}
#endif

	if (!bNeedNotShowWnd) {
		pDlgTalk->show();
	}
	 

	//  
	hWnd = (HWND)pDlgTalk->winId();

	if (!bNeedNotShowWnd) {
#ifndef  __WINCE__
		if (hFore)  ::SetWindowPos(hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
		else  ShowWindow(hWnd, SW_SHOW);
#else
		if (hFore) {
			//  ShowWindow(  pDlgTalk->m_hWnd,  SW_SHOWNOACTIVATE    );				
			ShowWindow(pDlgTalk->m_hWnd, SW_SHOWNA);
		}
		else
			ShowWindow(pDlgTalk->m_hWnd, SW_SHOW);
#endif
	}

	if (bActivateWnd) {
		PostMessage(g_pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_setActiveWindow, (LPARAM)hWnd);
	}

	iErr = 0;

errLabel:

	if (iErr) {
		if (pDlgTalk) {
			HWND  m_hWnd = (HWND)pDlgTalk->winId();
			if (IsWindow(m_hWnd)) {
				PostMessage(m_hWnd, WM_CLOSE, 0, 0);
			}
			else {
#ifndef  __WINCE__
				if (pDlgTalk)  delete  pDlgTalk;
#else				  
				if (pDlgTalk)  freeQyWnd(pDlgTalk);
#endif
			}
		}
	}
	if (!iErr) {
		if (bActivateWnd) {
#ifndef  __WINCE__
			if (IsIconic(hWnd))  SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
#endif
		}
		if (phWnd)  *phWnd = hWnd;
	}

	//
	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("talkToMessenger %I64u, %d: leaves %s, nStep %d"), pAddr->idInfo.ui64Id, pAddr->uiTranNo_shadow,
		iErr ? _T("failed") : _T("OK"), nStep);


	return  0;

}
#endif


//
__declspec(dllexport)  int  getTalkerShadow_qt(HWND  hParent, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkerSubType, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{

	int						iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;

	RECT						rect;
	COMMON_PARAM				commonParam1;
	MIS_CNT* pMisCnt = NULL;
	HWND						hWnd = NULL;
	int						iRet;
	HWND						hFore = NULL;

	CDlgTalk_qt* pDlgTalk = NULL;
	std::wstring  dispName;

	int						nStep = 0;

	if (!pAddr)  return  -1;

	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("getTalkerShadow enters, %I64u, %d"), pAddr->idInfo.ui64Id, pAddr->uiTranNo_shadow);


	if (!(pMisCnt = getMisCntByName(pProcInfo, pAddr->misServName))) {
		nStep = 10;
		goto  errLabel;
	}


	if (!pAddr->uiTranNo_shadow) {	//  此函数不能用于建主窗口. 2012/04/22
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("getTalkerShadow failed, iParam is 0"));
#endif
		nStep = 15;
		goto  errLabel;
	}

	//
	QWidget* pParent = NULL;
	QY_WMBUF_COMM  wmBuf;
	memset(&wmBuf, 0, sizeof(wmBuf));
	if (IsWindow(hParent)) {
		long lRet = SendMessage(hParent, CONST_qyWm_comm, CONST_qyWmParam_getObjAddr, (LPARAM)&wmBuf);
		if (lRet == CONST_qyWmRc_ok) {
			pParent = (QWidget*)wmBuf.u.getObjAddr.pObjAddr;
		}
	}



	//  BOOL	bNeedNotShowWnd		=	TRUE;

	memset(&rect, 0, sizeof(rect));
	pDlgTalk = new  CDlgTalk_qt(pParent);

	if (!pDlgTalk) {
		nStep = 80;
		goto  errLabel;
	}

	//
	DLG_TALK_var* pm_var = pDlgTalk->get_pm_var();
	if (!pm_var)  goto  errLabel;
	DLG_TALK_var& m_var = *pm_var;

	//
	int  iTalkUsage = 0;

	HWND  m_hWnd = (HWND)pDlgTalk->winId();

	//  if  (  !pDlgTalk->bSetDlgInfo(  0,  pAddr,  pTmpGrpMemQ,  bNeedNotShowWnd,  hFore  )  )  goto  errLabel;
	if (!dlgTalk_bSetDlgInfo(m_hWnd, m_var, pAddr, pTmpGrpMemQ, iTalkUsage, iTalkerSubType, bNeedNotShowWnd, hFore)) {
		nStep = 90;
		goto  errLabel;
	}
	unsigned  int uiTranNo_shadow = m_var.addr.uiTranNo_shadow;
	//
	if (dlgTalk_OnInitDialog(m_hWnd, &m_var)) {
		goto  errLabel;
	}

	
	dispName = m_var.displayName;

	static bool click = false;
	
	if (!click && dispName == _T("test")) {
		click = true;
		pDlgTalk->autoSet(uiTranNo_shadow);
	}

#if  0
	if (!pDlgTalk->Create(rect)) {
		nStep = 100;
		goto  errLabel;
	}
#endif
	//
	pDlgTalk->show();
	//  
	hWnd = m_hWnd;

	if (!bNeedNotShowWnd) {
#ifndef  __WINCE__
	//	if (hFore) ::SetWindowPos(m_hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
	//	else  ShowWindow(m_hWnd, SW_SHOW);
#else
		if (hFore) {
			//  ShowWindow(  pDlgTalk->m_hWnd,  SW_SHOWNOACTIVATE    );				
			ShowWindow(pDlgTalk->m_hWnd, SW_SHOWNA);
		}
		else
			ShowWindow(pDlgTalk->m_hWnd, SW_SHOW);
#endif
	}

	if (bActivateWnd) {
		PostMessage(g_pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_setActiveWindow, (LPARAM)hWnd);
	}

	iErr = 0;

errLabel:

	if (iErr) {
#ifndef  __WINCE__
		if (pDlgTalk)  delete  pDlgTalk;
#else
		if (pDlgTalk)  freeQyWnd(pDlgTalk);
#endif
	}
	if (!iErr) {
		if (bActivateWnd) {
#ifndef  __WINCE__
			//if (IsIconic(hWnd))  SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
#endif
		}
		if (phWnd)  *phWnd = hWnd;
	}

	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("getTalkerShadow called %s, nStep %d"), iErr ? _T("failed") : _T("OK"), nStep);

	return  0;

}



//
void* getObjAddr(HWND  hWnd)
{
	QWidget* qwidget = null;

	QY_WMBUF_COMM  wmBuf;
	memset(&wmBuf, 0, sizeof(wmBuf));
	int  lRet;
	lRet = ::SendMessage(hWnd, CONST_qyWm_comm, CONST_qyWmParam_getObjAddr, (LPARAM)&wmBuf);
	if (lRet != CONST_qyWmRc_ok) goto errLabel;

	qwidget = (QWidget*)wmBuf.u.getObjAddr.pObjAddr;
errLabel:
	return  qwidget;
}



