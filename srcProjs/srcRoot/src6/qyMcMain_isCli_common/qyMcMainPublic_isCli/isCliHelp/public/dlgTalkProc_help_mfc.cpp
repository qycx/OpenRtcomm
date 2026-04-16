
#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>

#define  __noDbg_new__

#include	"qymcMainCommon.h"
#include	"myresource.h"


#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_iscli.h"

#ifdef  __SUPPORT_HTMLEDIT__
#include	"myHtmlEditCtrl.h"
#endif

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
#include	"DlgTalk.h"
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

#include	"DlgMsgTool.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliCorePublic.h"

#include	"dyn_isCliD3d_public.h"
#include	"qmcFunc.h"



__declspec(dllexport)  int  talkToMessenger_mfc(void* pQyMcParam, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkUsage, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

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
	HWND						hParent = NULL;

	MACRO_CDlgTalk* pDlgTalk = NULL;

	int						nStep = 0;

	if (!pAddr)  return  -1;

	//
	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("talkToMessenger %I64u, %d: enters"), pAddr->idInfo.ui64Id, pAddr->uiTranNo_shadow);

	//
	if (!(pMisCnt = getMisCntByName(pProcInfo, pAddr->misServName))) {
		nStep = 10;
		goto  errLabel;
	}


	//  2014/04/29
	if (!bDone_retrieveAllImObjRules(pMisCnt)) {
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("talkToMessenger failed: not all imObjRules retrieved"));
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

		if (bActivateWnd) {
			PostMessage(pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_setActiveWindow, (LPARAM)hWnd);
		}

		iErr = 0;  goto  errLabel;

		//
	}
	else {
		if (pAddr->uiTranNo_shadow) {	//  对辅助窗口,不可以在这里建立. 2012/04/22
#ifdef  __DEBUG__
			traceLog(_T("talkToMessenger failed, primary talker doesn't exists"));
#endif
			nStep = 70;
			goto  errLabel;
		}
	}


	memset(&rect, 0, sizeof(rect));

	if (!bActivateWnd) {		//
		hFore = GetForegroundWindow();
	}



#ifndef  __WINCE__
	//
	if (bApp_ts(pQyMc)) {  //  #ifdef  __APP_qyMc_touchscreen__  		//  2012/05/12
		if (IsWindow(pProcInfo->g_hVWall)) {
			hParent = pProcInfo->g_hVWall;
		}
		else {
			hParent = ::GetDesktopWindow();
		}
	}	//  #endif
	else {  //  2013/08/01
		hParent = ::GetDesktopWindow();
	}

	pDlgTalk = new  MACRO_CDlgTalk(pQyMc,  hParent);
	if (!pDlgTalk) {
		nStep = 80;
		goto  errLabel;
	}

	//
	DLG_TALK_var* pm_var = pDlgTalk->get_pm_var();
	if (!pm_var)  goto  errLabel;
	DLG_TALK_var& m_var = *pm_var;

	//

	//  if  (  !pDlgTalk->bSetDlgInfo(  0,  pAddr,  pTmpGrpMemQ,  bNeedNotShowWnd,  hFore  )  )  goto  errLabel;
	if (!dlgTalk_bSetDlgInfo(pDlgTalk->m_hWnd, m_var, pAddr, pTmpGrpMemQ, iTalkUsage, 0, bNeedNotShowWnd, hFore)) {
		nStep = 90;
		goto  errLabel;
	}

	if (!pDlgTalk->Create(rect)) {
		nStep = 100;
		goto  errLabel;
	}

#else

	G_guiData_qyMc* pGuiData = (G_guiData_qyMc*)get_g_guiData();
	PF_commonHandler			pf_newDlgTalk_ce = (PF_commonHandler)pGuiData->pf_newDlgTalk_ce;
	if (!pf_newDlgTalk_ce)  goto  errLabel;

	DLG_guiDataParam_talk			guiDataParam;
	memset(&guiDataParam, 0, sizeof(guiDataParam));
	guiDataParam.iDlgType = 0;
	guiDataParam.pAddr = pAddr;
	guiDataParam.pTmpGrpMemQ = pTmpGrpMemQ;
	guiDataParam.bNeedNotShowWnd = bNeedNotShowWnd;
	guiDataParam.hFore = hFore;

	hParent = pQyMc->gui.hMainWnd;	//  GetDesktopWindow(  );

	pDlgTalk = (CDlgTalk_ce*)pf_newDlgTalk_ce(pQyMc->g_hInst, hParent, &guiDataParam);
	if (!pDlgTalk)  goto  errLabel;

#endif 

	//  
	hWnd = pDlgTalk->m_hWnd;

	if (!bNeedNotShowWnd) {
#ifndef  __WINCE__
		if (hFore)  ::SetWindowPos(pDlgTalk->m_hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
		else  ShowWindow(pDlgTalk->m_hWnd, SW_SHOW);
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
			if (IsWindow(pDlgTalk->m_hWnd)) {
				PostMessage(pDlgTalk->m_hWnd, WM_CLOSE, 0, 0);
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
	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("talkToMessenger %I64u, %d: leaves %s, nStep %d"), pAddr->idInfo.ui64Id, pAddr->uiTranNo_shadow,
		iErr ? _T("failed") : _T("OK"), nStep);


	return  0;

}


//
__declspec(dllexport)  int  getTalkerShadow_mfc(HWND  hParent, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkerSubType, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

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

	MACRO_CDlgTalk* pDlgTalk = NULL;

	int						nStep = 0;

	if (!pAddr)  return  -1;

	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("getTalkerShadow enters, %I64u, %d"), pAddr->idInfo.ui64Id, pAddr->uiTranNo_shadow);


	if (!(pMisCnt = getMisCntByName(pProcInfo, pAddr->misServName))) {
		nStep = 10;
		goto  errLabel;
	}


	if (!pAddr->uiTranNo_shadow) {	//  此函数不能用于建主窗口. 2012/04/22
#ifdef  __DEBUG__
		traceLog(_T("getTalkerShadow failed, iParam is 0"));
#endif
		nStep = 15;
		goto  errLabel;
	}


	//  BOOL	bNeedNotShowWnd		=	TRUE;

	memset(&rect, 0, sizeof(rect));

	pDlgTalk = new  MACRO_CDlgTalk(pQyMc,  hParent);
	if (!pDlgTalk) {
		nStep = 80;
		goto  errLabel;
	}

	//
	DLG_TALK_var* pm_var = pDlgTalk->get_pm_var();
	if (!pm_var)  goto  errLabel;
	DLG_TALK_var& m_var = *pm_var;

	//

	//
	int  iTalkUsage = 0;

	//  if  (  !pDlgTalk->bSetDlgInfo(  0,  pAddr,  pTmpGrpMemQ,  bNeedNotShowWnd,  hFore  )  )  goto  errLabel;
	if (!dlgTalk_bSetDlgInfo(pDlgTalk->m_hWnd, m_var, pAddr, pTmpGrpMemQ, iTalkUsage, iTalkerSubType, bNeedNotShowWnd, hFore)) {
		nStep = 90;
		goto  errLabel;
	}

	if (!pDlgTalk->Create(rect)) {
		nStep = 100;
		goto  errLabel;
	}


	//  
	hWnd = pDlgTalk->m_hWnd;

	if (!bNeedNotShowWnd) {
#ifndef  __WINCE__
		if (hFore)  ::SetWindowPos(pDlgTalk->m_hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
		else  ShowWindow(pDlgTalk->m_hWnd, SW_SHOW);
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
			if (IsIconic(hWnd))  SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
#endif
		}
		if (phWnd)  *phWnd = hWnd;
	}

	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("getTalkerShadow called %s, nStep %d"), iErr ? _T("failed") : _T("OK"), nStep);

	return  0;

}


//
int  procTalkTo(HWND  hParent, int  iWndContentType_hParent, LPCTSTR  inputStr)
{
	int						iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;

	CQyString				str;
	TCHAR					txtContent[1024];
	BOOL					bNothing = FALSE;
	MIS_CNT* pMisCnt = NULL;
	TCHAR* pT = NULL;
	TCHAR					tBuf[255 + 1] = _T("");
	char					buf[255 + 1] = "";

	//
	CHelp_getDlgTalkVar		help_getDlgTalkVar;
	DLG_TALK_var* pCurVar = NULL;

	CQyMalloc				mallocObj_pMsgBuf;
	MIS_MSGU* pMsgBuf = NULL;

	//  
	HWND  hCurTalk = NULL;
	MSG_tool_common* pMsgToolCommon = NULL;

	//
	CHelp_getDlgTalkVar   help_getDlgTalkVar_mgr;
	QY_MESSENGER_ID		idInfo_dst;



#ifdef  __DEBUG__
	//  traceLog(  _T(  "Not finished"  )  );
#endif

	switch (iWndContentType_hParent) {
	case  CONST_qyWndContentType_talker:
		hCurTalk = hParent;
		break;
	case  CONST_qyWndContentType_dlgMsgTool: {
		CDlgMsgTool* pDlgMsgTool = (CDlgMsgTool*)CWnd::FromHandlePermanent(hParent);
		if (!pDlgMsgTool)  goto  errLabel;
		//
		if (!pDlgMsgTool->m_var.guiData.bFinished_createCtrls)  goto  errLabel;
		//
		hCurTalk = pDlgMsgTool->m_var.hDlgTalk;
		//
		pMsgToolCommon = &pDlgMsgTool->m_var.msgToolCommon;
	}
										   break;
	default:
		goto  errLabel;
	}


	if (!hCurTalk)  return  -1;
	//
	pCurVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hCurTalk);
	if (!pCurVar)  return  -1;
	//  DLG_TALK_var		&	m_var				=	*pm_var;

	pMsgBuf = (MIS_MSGU*)mallocObj_pMsgBuf.mallocf(sizeof(MIS_MSGU));
	if (!pMsgBuf)  return  -1;

	//
	HWND					hMgr = hCurTalk;
	DLG_TALK_var* pMgrVar = pCurVar;
	if (!isTalkerShadowMgr(pCurVar->addr)) {
		TALKER_shadow* pShadow = (TALKER_shadow*)pCurVar->pShadowInfo;
		if (!pShadow)  goto  errLabel;
		hMgr = pShadow->hMgr;
		pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
		if (!pMgrVar)  goto  errLabel;
	}
	TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
	if (!pShadowMgr)  goto  errLabel;


	//
	if (!(pMisCnt = pCurVar->pMisCnt))  goto  errLabel;
	//
#ifdef  __SUPPORT_HTMLEDIT__

	//
	if (pMsgToolCommon) {
		MSG_tool_common& msgToolCommon = *pMsgToolCommon;

		//
		IHTMLDocument2* pDoc = NULL;
		IHTMLElement* pBody = NULL;
		if (!msgToolCommon.m_pHtmlEdit_input->GetDHtmlDocument(&pDoc))  goto  errLabel;

		if (SUCCEEDED(pDoc->get_body(&pBody))) {
			BSTR  bstr = NULL;
			if (SUCCEEDED(pBody->get_innerText(&bstr))) {
				str = bstr;
				SysFreeString(bstr);
			}
			//  MACRO_CStringTrim(  str  );
			str.Trim();
			if (!str.GetLength())  bNothing = TRUE;

			if (!pCurVar->addr.bInNoticeMode) {	//  
				if (SUCCEEDED(pBody->get_innerHTML(&bstr))) {
					str = bstr;
					SysFreeString(bstr);
				}
			}

			pBody->Release();
		}

		//
#ifdef  __DEBUG__
		printHtmlEdit(msgToolCommon.m_pHtmlEdit_input);
#endif
	}
	else {
		if (!inputStr)  goto  errLabel;
		str = inputStr;
		str.Trim();
		if (!str[0])  bNothing = TRUE;
	}

#else
	if (!inputStr)  goto  errLabel;
	str = inputStr;
	str.Trim();
	if (!str[0])  bNothing = TRUE;
#endif

	if (bNothing) {
#ifdef  __DEBUG__
		traceLogA("procTalkTo failed: nothing input");
#endif
		goto  errLabel;
	}

	if (pCurVar->addr.bInNoticeMode) {
#ifndef  __WINCE__
		if (myMessageBox(hCurTalk, CQyString("Whether to send \"") + str + _T("\""), _T(""), MB_YESNO | MB_DEFBUTTON2) != IDYES)  goto  errLabel;
#else
		traceLog(_T("Not supported in ce"));
		goto  errLabel;
#endif
	}




	//  Æä´ÎÔÙ·¢ÍùmgrÊ¹·¢ËÍ
	unsigned  char		ucFlg;
	IM_HTML_CONTENT		content;
	int					lenInBytes;
	//
	ucFlg = 0;
	//
	memset(&content, 0, sizeof(content));
	content.uiType = CONST_imCommType_htmlContent;
	lstrcpyn(content.wBuf, str, mycountof(content.wBuf));
	lenInBytes = offsetof(IM_HTML_CONTENT, wBuf) + (lstrlen(content.wBuf) + 1) * sizeof(content.wBuf[0]);
	//
	MSG_ROUTE	route;
	memset(&route, 0, sizeof(route));
	//
	route.idInfo_from.ui64Id = pMisCnt->idInfo.ui64Id;
	//
	route.idInfo_to.ui64Id = pCurVar->addr.idInfo.ui64Id;
	route.uiDevType_to = pCurVar->addr.uiDevType;
	//
	if (pMgrVar->addr.uiObjType != CONST_objType_imGrp
		|| !pMgrVar->av.taskInfo.bTaskExists
		|| !pMgrVar->av.taskInfo.ucbConfCtrl)
	{
		MACRO_prepareForTran();

		if (postMsg2Mgr_mc(pMisCnt, &route, CONST_misMsgType_talk, ucFlg, CONST_qyCmd_talkTo, tStartTran, uiTranNo, 0, (char*)&content, lenInBytes, &pMgrVar->addr.idInfo, &pMgrVar->addr.idInfo, 0, pMsgBuf, TRUE))  goto  errLabel;
	}
	else  if (pMgrVar->av.taskInfo.ucbStarter
		|| pShadowMgr->av.ucbMeConfMgr)
	{
		idInfo_dst.ui64Id = pCurVar->confMgr_grpMemListInfo.idInfo_talkTo.ui64Id;
		if (idInfo_dst.ui64Id == pMisCnt->idInfo.ui64Id) {
			showNotification(0, 0, 0, 0, 0, 0, _T("Can't talk to me"));
			goto  errLabel;
		}
		if (!idInfo_dst.ui64Id)  idInfo_dst.ui64Id = pCurVar->addr.idInfo.ui64Id;
		//
		if (idInfo_dst.ui64Id != pCurVar->addr.idInfo.ui64Id)  content.idInfo_logicalPeer.ui64Id = pCurVar->addr.idInfo.ui64Id;
		//
		MACRO_prepareForTran();

		if (postMsg2Mgr_mc(pMisCnt, &route, CONST_misMsgType_talk, ucFlg, CONST_qyCmd_talkTo, tStartTran, uiTranNo, 0, (char*)&content, lenInBytes, &pCurVar->addr.idInfo, &idInfo_dst, 0, pMsgBuf, TRUE))  goto  errLabel;

	}
	else {
		int  i;

		//
		content.idInfo_logicalPeer.ui64Id = pMgrVar->addr.idInfo.ui64Id;

		//
		idInfo_dst.ui64Id = pMgrVar->av.taskInfo.idInfo_starter.ui64Id;
		//
		MACRO_prepareForTran();

		if (postMsg2Mgr_mc(pMisCnt, &route, CONST_misMsgType_talk, ucFlg, CONST_qyCmd_talkTo, tStartTran, uiTranNo, 0, (char*)&content, lenInBytes, &pMgrVar->addr.idInfo, &idInfo_dst, 0, pMsgBuf, TRUE))  goto  errLabel;

		//
		for (i = 0; i < pShadowMgr->av.confMgrInfo.usCnt; i++) {
			idInfo_dst.ui64Id = pShadowMgr->av.confMgrInfo.mems[i].idInfo.ui64Id;
			if (idInfo_dst.ui64Id == pMgrVar->av.taskInfo.idInfo_starter.ui64Id)  continue;
			//
			MACRO_prepareForTran();

			if (postMsg2Mgr_mc(pMisCnt, &route, CONST_misMsgType_talk, ucFlg, CONST_qyCmd_talkTo, tStartTran, uiTranNo, 0, (char*)&content, lenInBytes, &pMgrVar->addr.idInfo, &idInfo_dst, 0, pMsgBuf, TRUE))  goto  errLabel;

		}
	}

	// 
	//  postImMsg2Log(  pMisCnt->cfg.misServName,  &pMisCnt->idInfo,  pMisCnt->talkerDesc,  tStartTran,  uiTranNo,  &m_var.addr.idInfo,  m_var.talkerDesc,  content.uiType,  str,  txtContent,  0,  &pProcInfo->schedulerQ  );    





	pFuncs->pf_dlgTalk_qPostMsg(hMgr, pMsgBuf, sizeof(MIS_MSGU));
	PostMessage(hMgr, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);


	//  ½«ÏÂÃæµÄinputÊäÈëÇå¿Õ
#ifdef  __SUPPORT_HTMLEDIT__
	if (pMsgToolCommon) {
		MSG_tool_common& msgToolCommon = *pMsgToolCommon;
		//
		IHTMLDocument2* pDoc = NULL;
		IHTMLElement* pBody = NULL;
		//
		if (msgToolCommon.m_pHtmlEdit_input->GetDHtmlDocument(&pDoc)) {
			if (SUCCEEDED(pDoc->get_body(&pBody))) {
				BSTR  bstr = NULL;
				//  str  =  CString(  ""  );
				//  bstr  =  str.AllocSysString(  );
				bstr = SysAllocString(_T(""));
				if (bstr) {
					pBody->put_innerHTML(bstr);
					SysFreeString(bstr);
				}
				pBody->Release();
			}
		}
	}
#else
	//  SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_EDIT_input,  _T(  ""  )  );
#endif

	iErr = 0;

errLabel:
	return  iErr;
}


//
int  msgTool_proc_mouseMove(HWND  hWnd, int  iWndContentType_hWnd)
{
	int  iErr = -1;

	if (iWndContentType_hWnd != CONST_qyWndContentType_dlgMsgTool)  return  -1;
	CDlgMsgTool* pDlgMsgTool = (CDlgMsgTool*)CWnd::FromHandlePermanent(hWnd);
	if (!pDlgMsgTool)  goto  errLabel;
	//				
	if (!pDlgMsgTool->m_var.guiData.bFinished_createCtrls)  goto  errLabel;

	//
	HWND  hCurTalk;
	hCurTalk = pDlgMsgTool->m_var.hDlgTalk;

	//
	DWORD dwPos = GetMessagePos();

	long  lParam = dwPos;
	POINT	point;
	point.x = GET_X_LPARAM(lParam);
	point.y = GET_Y_LPARAM(lParam);

	//
#if 0
	viewInstantAssistant(hCurTalk, CONST_qyWndContentType_talker, point.x, point.y, hCurTalk, FALSE);
	{
		CHelp_getDlgTalkVar  help;
		DLG_TALK_var* pCurVar = (DLG_TALK_var*)help.getVar(hCurTalk);
		if (!pCurVar)  goto  errLabel;
		if (IsWindow(pCurVar->hWnd_instantAssistant)) {
			SetForegroundWindow(pCurVar->hWnd_instantAssistant);
		}

	}
#endif

	iErr = 0;
errLabel:
	return  iErr;

}


int  dlgTalk_procTask_htmlEdit(HWND  hParent, int  iWndContentType_hParent, LPCTSTR  url)
{
	int							iErr = -1;

	CHelp_getDlgTalkVar			help_getDlgTalkVar;
	DLG_TALK_var* pm_var = NULL;


	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;


	HWND  hDlgTalk = NULL;

	switch (iWndContentType_hParent) {
	case  CONST_qyWndContentType_talker:
		hDlgTalk = hParent;
		break;
	case  CONST_qyWndContentType_dlgMsgTool:
		CDlgMsgTool* pDlgMsgTool;
		pDlgMsgTool = (CDlgMsgTool*)CWnd::FromHandle(hParent);
		if (!pDlgMsgTool->m_var.guiData.bFinished_createCtrls)  goto  errLabel;
		//
		hDlgTalk = pDlgMsgTool->m_var.hDlgTalk;
		break;
	default:
		goto  errLabel;
	}

	pm_var = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk);
	if (!pm_var)  goto  errLabel;
	DLG_TALK_var& m_var = *pm_var;

#if  0
	if (!isTalkerShadowMgr(m_var.addr)) {
		TALKER_shadow* pTalkerShadow = (TALKER_shadow*)m_var.pShadowInfo;
		if (!pTalkerShadow)  goto  errLabel;

		DLG_TALK_var* pMgrVar = getDlgTalkVar(pTalkerShadow->hMgr);
		if (!pMgrVar)  goto  errLabel;

		//
		hDlgTalk = pTalkerShadow->hMgr;
		//  pHtmlEditCtrl  =  pMgrVar->m_pHtmlEdit_recentMsgList;
	}
#endif


	int  iTaskId;
	TCHAR							rowIdStrBuf[32] = _T("");
	unsigned  short					usOp = 0;
	TCHAR							paramStrBuf[128] = _T("");


	if (parseQmInternalUrl(url, &iTaskId, rowIdStrBuf, mycountof(rowIdStrBuf), &usOp, paramStrBuf, mycountof(paramStrBuf)))  goto  errLabel;

	PARAM_dlgTalk_procTask  param;
	memset(&param, 0, sizeof(param));
	if (pFuncs->pf_dlgTalk_procTask1(hDlgTalk, iTaskId, usOp, paramStrBuf, &param))  goto  errLabel;

	iErr = 0;

errLabel:

	return  iErr;
}


__declspec(dllexport)  int  dlgMsgTool_OnQyPostComm_idcInited(QY_MC  *pQyMc, HWND  hDlgMsgTool, DLG_msgTool_var* pDlgMsgToolVar, UINT  wParam, LONG  lParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int	iErr = -1;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;


	//  if  (  !pDLG_TALK_var  )  return  -1;
	//  DLG_TALK_var  &  m_var  =  *(  DLG_TALK_var  *  )pDLG_TALK_var;
	DLG_msgTool_var& m_var = *pDlgMsgToolVar;
	HWND				hDlg = hDlgMsgTool;


#ifdef  __SUPPORT_HTMLEDIT__
	CString				strInfo;
	IHTMLDocument2* pDoc = NULL; // Declared earlier in the code
	CMyHtmlEditCtrl* pEditCtrl = NULL;

	//  2012/05/17
	if (!m_var.msgToolCommon.m_pHtmlEdit_input || !m_var.msgToolCommon.m_pHtmlEdit_recentMsgList) {
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("CDlgTalk::postComm: idcInited, failed, htmlEdit_input or recentMsgList is null."));
		goto  errLabel;
	}

	//
	if (m_var.msgToolCommon.m_pHtmlEdit_input->m_hWnd == (HWND)lParam) {
		pEditCtrl = m_var.msgToolCommon.m_pHtmlEdit_input;

		strInfo = CString(CONST_html_input);
	}
	else  if (m_var.msgToolCommon.m_pHtmlEdit_recentMsgList->m_hWnd == (HWND)lParam) {
		pEditCtrl = m_var.msgToolCommon.m_pHtmlEdit_recentMsgList;

		strInfo = CString(CONST_html_recentMsgList);
	}
	else {
		traceLogA("CDlgTalk::OnQyPostComm(  ): µÃµ½²»Æ¥ÅäµÄ¿Ø¼þ¾ä±ú");
		goto  errLabel;
	}

	if (!pEditCtrl->GetDHtmlDocument(&pDoc) || !pDoc)  goto  errLabel;

	if (initHtmlDisplay(pDoc, strInfo))  goto  errLabel;

	pEditCtrl->m_bDisplayInited = TRUE;

	if (m_var.msgToolCommon.m_pHtmlEdit_recentMsgList->m_bDisplayInited && m_var.msgToolCommon.m_pHtmlEdit_input->m_bDisplayInited) {

		//  Èç¹û³õÊ¼»¯³ö´í£¬ÕâÀïÓ¦¸ÃÖ÷¶¯ÍË³ö
		if (m_var.bInitFailed) {
			//
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("CDlgTalk::postComm: bInitFailed, to close Window."));
#ifdef  __DEBUG__
			traceLog(_T("CDlgTalk::postComm: bInitFailed, to close Window."));
#endif

			//  2012/05/17
			PostMessage(hDlg, WM_CLOSE, 0, 0);
			goto  errLabel;
		}

		//  2008/11/14
		m_var.guiData.bFinished_createCtrls = TRUE;

#ifndef  __WINCE__
		m_var.msgToolCommon.m_pHtmlEdit_input->SetFocus();
#else
		SetForegroundWindow(hDlg);
#endif

		//
#if  0
		if (m_var.hFore) {		//  2007/09/09
			::SetForegroundWindow(m_var.hFore);  m_var.hFore = NULL;
#if !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )			//  2010/09/08
			::SetWindowPos(hDlg, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
#endif
		}
#endif
	}

	//  if  (  m_var.m_pHtmlEdit_recentMsgList->m_hWnd  ==  (  HWND  )lParam  )  
	if (m_var.guiData.bFinished_createCtrls)
	{
		//  2012/05/17
		int  iWndContentType = CONST_qyWndContentType_dlgMsgTool;
		pFuncs->pf_doSth_afterInitDlgMsgTool(pQyMc,  hDlg, iWndContentType);
	}
#endif

	iErr = 0;

errLabel:

	return  iErr;

}

//__declspec(  dllexport  )  int  dlgTalk_OnInitDialog_createHtmlEdits(  HWND  hDlgTalk,  void  *  pDLG_TALK_var  ) 
__declspec(dllexport)  int  dlgMsgTool_OnInitDialog_createHtmlEdits(HWND  hDlgMsgTool, DLG_msgTool_var* pDlgMsgToolVar)
{
	int	iErr = -1;

	if (!pDlgMsgToolVar)  return  -1;


	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

	//
	DLG_msgTool_var& m_var = *pDlgMsgToolVar;
	HWND				hDlg = hDlgMsgTool;

	int							idc;
	BOOL						tmpbRet;
	RECT						rect;

	//
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var* pDlgTalkVar = NULL;


	pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(m_var.hDlgTalk);
	if (!pDlgTalkVar)  goto  errLabel;



	m_var.msgToolCommon.m_pHtmlEdit_input = new  CMyHtmlEditCtrl();
	if (!m_var.msgToolCommon.m_pHtmlEdit_input)  goto  errLabel;
	m_var.msgToolCommon.m_pHtmlEdit_recentMsgList = new  CMyHtmlEditCtrl();
	if (!m_var.msgToolCommon.m_pHtmlEdit_recentMsgList)  goto  errLabel;


	//
	safeTcsnCpy(_T("dlgMsgTool_msgToolCommon"), m_var.msgToolCommon.tmp_desc, mycountof(m_var.msgToolCommon.tmp_desc));

	//

	//
	idc = m_var.guiData.iIDC_STATIC_input;		//  
	//
	GetWindowRect(GetDlgItem(hDlg, idc), &rect);
	ScreenToClient(hDlg, (LPPOINT)&rect);
	HWND  hctrl = GetDlgItem(hDlg, idc);
	//
	idc = IDC_htmlEdit_input;		//  
	m_var.msgToolCommon.m_pHtmlEdit_input->m_bDesignMode = TRUE;
	m_var.msgToolCommon.m_pHtmlEdit_input->m_iWndContentType_hParent = CONST_qyWndContentType_dlgMsgTool;	//  2014/01/25
	tmpbRet = m_var.msgToolCommon.m_pHtmlEdit_input->Create(NULL, WS_CHILD | WS_VISIBLE, rect, CWnd::FromHandle(hDlg), idc, NULL);
	if (!tmpbRet) {
		traceLogA("m_htmlEdit_input create(  ) failed");
		goto  errLabel;
	}
	m_var.msgToolCommon.m_pHtmlEdit_input->m_uiType = CONST_htmlEditType_input;
	CWnd* pWnd = m_var.msgToolCommon.m_pHtmlEdit_input;
	pWnd = CWnd::FromHandle(hctrl);
	if (!pWnd)  goto  errLabel;
	if (!m_var.msgToolCommon.m_pHtmlEdit_input->m_dropTarget.Register(pWnd)) {
#ifdef  __DEBUG__
		qyDisplayLastError("");
		traceLog(_T("dlgMsgTool_OnInitDialog_createHtmlEdits: htmlEdit_input Register failed"));
#endif
	}

	idc = IDC_STATIC_recentMsgList;
	//
	GetWindowRect(GetDlgItem(hDlg, idc), &rect);
	ScreenToClient(hDlg, (LPPOINT)&rect);
	hctrl = GetDlgItem(hDlg, idc);
	//  
	idc = IDC_htmlEdit_recentMsgList;
	m_var.msgToolCommon.m_pHtmlEdit_recentMsgList->m_bDesignMode = FALSE;
	m_var.msgToolCommon.m_pHtmlEdit_recentMsgList->m_iWndContentType_hParent = CONST_qyWndContentType_dlgMsgTool;	//  2014/01/25
	tmpbRet = m_var.msgToolCommon.m_pHtmlEdit_recentMsgList->Create(NULL, WS_CHILD | WS_VISIBLE, rect, CWnd::FromHandle(hDlg), idc, NULL);
	if (!tmpbRet) {
		traceLogA("m_htmlEdit_recentMsgList create(  ) failed");
		goto  errLabel;
	}
	m_var.msgToolCommon.m_pHtmlEdit_recentMsgList->m_uiType = CONST_htmlEditType_recentMsgList;
	//pWnd  =  m_var.msgToolCommon.m_pHtmlEdit_recentMsgList;
	pWnd = CWnd::FromHandle(hctrl);
	if (!pWnd)  goto  errLabel;
	if (!m_var.msgToolCommon.m_pHtmlEdit_recentMsgList->m_dropTarget.Register(pWnd)) {
#ifdef  __DEBUG__
		traceLog(_T("dlgMsgTool_OnInitDialog_createHtmlEdits: htmlEdit_recentMsgList Register failed"));
#endif
	}


	//		
#if  10
	if (1)
	{
		HWND  hListCtrl = NULL;

		//  
		m_var.msgToolCommon.idcList_task = m_var.guiData.iIDC_LIST_task;
		//  m_var.pColumns_task  =  m_var.ucbShowImGrpMems  ?  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_taskListColumns_showMembers  )  :  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_taskListColumns  );
		m_var.msgToolCommon.pColumns_task = (QY_COLUMNINFO*)getResColumnInfo(0, &pQyMc->cusRes, CONST_resId_taskListColumns);
		if (!m_var.msgToolCommon.pColumns_task) {
			qyShowInfo1(CONST_qyShowType_warning, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("pColumns_task is null, qyCusRes.dll is wrong."));
			goto  errLabel;
		}
		//
		//  pListCtrl  =  (  CListCtrl  *  )CWnd::FromHandle(  GetDlgItem(  hDlgTalk,  m_var.idcList_task  )  );
		hListCtrl = GetDlgItem(hDlg, m_var.msgToolCommon.idcList_task);
		//
		//  pListCtrl->ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
		myListCtrl_ModifyStyle(hListCtrl, LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL, 0);
		//  pListCtrl->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );
		myListCtrl_SetExtendedStyle(hListCtrl, LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE);
		//
		myListCtrl_SetImageList(hListCtrl, m_var.pm_LargeImageList, LVSIL_NORMAL);
		myListCtrl_SetImageList(hListCtrl, m_var.pm_SmallImageList, LVSIL_SMALL);

		//  
		int					i;
		QY_COLUMNINFO* pColumns;

		LV_COLUMN lvc;
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

		pColumns = m_var.msgToolCommon.pColumns_task;
		for (i = 0; pColumns[i].type != -1; i++) {
			lvc.iSubItem = i;
			lvc.pszText = pColumns[i].label;
			lvc.cx = pColumns[i].width;
			lvc.fmt = pColumns[i].fmt;
			//  pListCtrl->InsertColumn(  i,  &lvc  );
			myListCtrl_InsertColumn(hListCtrl, i, &lvc);
		}
	}
#endif


	iErr = 0;

errLabel:
	return  iErr;
}





__declspec(dllexport) int  dlgMsgTool_OnQyComm_getDropTarget(HWND  hDlg, void* pVar, WPARAM  wParam, LPARAM  lParam)
{
	int	iErr = -1;

	if (!pVar)  return  -1;
	//  DLG_TALK_var  &  m_var  =  *(  DLG_TALK_var  *  )pDLG_TALK_var;
	DLG_msgTool_var& m_var = *(DLG_msgTool_var*)pVar;

	QY_WMBUF_COMM* pComm = (QY_WMBUF_COMM*)lParam;

	//  ÕâÀïÊôÓÚ³õÊ¼»¯µÄ¹¤×÷£¬²»ÄÜµÈ¶Ô»°´°¿Ú¶¼³õÊ¼»¯ÍêÁË¡£
	LPDROPTARGET  pMyDropTarget = NULL;

	if (pComm->u.getIDropTarget.hWnd == m_var.msgToolCommon.m_pHtmlEdit_input->m_hWnd) {
		pMyDropTarget = (LPDROPTARGET)m_var.msgToolCommon.m_pHtmlEdit_input->m_dropTarget.GetInterface(&IID_IDropTarget);
	}
	else  if (pComm->u.getIDropTarget.hWnd == m_var.msgToolCommon.m_pHtmlEdit_recentMsgList->m_hWnd) {
		pMyDropTarget = (LPDROPTARGET)m_var.msgToolCommon.m_pHtmlEdit_recentMsgList->m_dropTarget.GetInterface(&IID_IDropTarget);
	}
	else
		goto  errLabel;

	if (pMyDropTarget) {
		pComm->u.getIDropTarget.pIDropTarget = pMyDropTarget;
		pMyDropTarget->AddRef();
	}


	iErr = 0;
errLabel:
	return  iErr;
}


//  2014/01/25
__declspec(dllexport)  int  doDoc_doTable_byRowId_param(void* pDLG_TALK_var, void* pPARAM_PROC_ROW)
{
	int		iErr = -1;
	if (!pDLG_TALK_var)  return  -1;
	DLG_TALK_var& m_var = *(DLG_TALK_var*)pDLG_TALK_var;
	if (!pPARAM_PROC_ROW)  return  -1;
	PARAM_PROC_ROW& param = *(PARAM_PROC_ROW*)pPARAM_PROC_ROW;

	//
	if (!IsWindow(m_var.msgTool.hWnd_msgTool))  return  -1;
	DLG_msgTool_var* pDlgMsgToolVar = (DLG_msgTool_var*)getDlgMsgToolVar(m_var.msgTool.hWnd_msgTool);
	if (!pDlgMsgToolVar)  goto  errLabel;
	if (!pDlgMsgToolVar->guiData.bFinished_createCtrls)  goto  errLabel;

	MSG_tool_common& msgToolCommon = pDlgMsgToolVar->msgToolCommon;


	//
	if (msgToolCommon.m_pHtmlEdit_recentMsgList) {
		IHTMLDocument2* pDoc = NULL;
		if (!msgToolCommon.m_pHtmlEdit_recentMsgList->GetDHtmlDocument(&pDoc))  goto  errLabel;

		doDoc(pDoc, (PF_commonHandler)doTable_byRowId, 0, &param);
	}

	iErr = 0;
errLabel:

	return  iErr;
}


