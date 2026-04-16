


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


//
int  tmpHandler_showMsg_task_qmcCli(void* hDlgTalkParam, DLG_TALK_var& m_var, void* p1, void* pMsgParam)
{
	int		iErr = -1;

	HWND				hDlg = (HWND)hDlgTalkParam;

	PARAM_PROC_ROW* pParam = (PARAM_PROC_ROW*)p1;
	MIS_MSGU* pMsg = (MIS_MSGU*)pMsgParam;

	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();	//
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  return  -1;

	int					i;
	TCHAR				tBuf[128] = _T("");

	//
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	HWND  hMgr = hDlg;
	DLG_TALK_var* pMgrVar = &m_var;
	if (!isTalkerShadowMgr(pMgrVar->addr)) {
		TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pMgrVar->pShadowInfo;
		if (!pTalkerShadow)  return  -1;
		hMgr = pTalkerShadow->hMgr;
		pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
		if (!pMgrVar)  return  -1;
	}
	TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
	if (!pShadowMgr)  return  -1;

	//
	switch (pMsg->uiType) {
	case  CONST_misMsgType_task:

	{
		MIS_MSG_routeTalkData* pTalkData = &pMsg->task.data;
		IM_CONTENTU* pContent = (IM_CONTENTU*)pTalkData->buf;
		QY_MESSENGER_ID				idInfo_talker;
		//
		char							timeBuf[CONST_qyTimeLen + 1] = "";
		TASK_DISPLAY					taskDisplay;
		char							buf[255 + 1] = "";
		int							nItem;
		int							iStatus;

		//
#ifdef  __DEBUG__
		if (pContent->uiType == CONST_imCommType_transferAvInfo) {
			int  ii = 0;
		}
#endif


		//
		if (pContent->uiType == CONST_imCommType_taskInteractionReq) {
			tmpHandler_showMsg_task_taskInteractionReq(hDlg, m_var, p1, pMsgParam, pContent);
			break;
		}
		if (pContent->uiType == CONST_imCommType_confKey) {
			tmpHandler_showMsg_task_confKey(hDlg, m_var, p1, pMsgParam, pContent);
			break;
		}
		if (pContent->uiType == CONST_imCommType_statusConfLayoutParam) {
			tmpHandler_showMsg_task_statusConfLayoutParam(hDlg, m_var, p1, pMsgParam, pContent);
			break;
		}
		if (pContent->uiType == CONST_imCommType_confLayout) {				//  2010/12/27

#ifdef  __DEBUG__
			traceLogA((char*)"videoConferenceLayout");
#endif
			//
			if (!m_var.av.taskInfo.bTaskExists)  goto  errLabel;

			if (m_var.av.taskInfo.ucbStarter) {
				break;
			}

			//  以下为参会人
			if (!pContent->confLayout.ucbResp) {
				if (pContent->confLayout.usOp == CONST_imOp_enlargeChannel) {
					doSelIpc_local(&pContent->confLayout.confLayoutParam.ipcParam, hMgr);
					//
					CHelp_getDlgTalkVar help_getDlgTalkVar;
					DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgr);
					if (!pDlgTalkVar)break;
					if (!isTalkerShadowMgr(pDlgTalkVar->addr)) break;

					QY_MESSENGER_ID  idInfo_to = pDlgTalkVar->av.taskInfo.idInfo_starter;

					//
					QY_MESSENGER_ID  idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
					QY_MESSENGER_ID  idInfo_requester = pMisCnt->idInfo;

					ConfLayoutParam  confLayoutParam = { 0 };
					confLayoutParam.ipcParam = pContent->confLayout.confLayoutParam.ipcParam;//通道
					
					NvrInfo* pNvrInfo = &pProcInfo->m_ipcProc.dev.nvrInfo;
					for (i = 0; i < pNvrInfo->usCnt; i++) {
						if (!confLayoutParam.ipcParam.iChannel) continue;
						if (confLayoutParam.ipcParam.iChannel == pNvrInfo->mems[i].iChannel) {
							safeTcsnCpy(pNvrInfo->mems[i].name, confLayoutParam.ipcParam.channelName, mycountof(confLayoutParam.ipcParam.channelName));
							break;
						}
					}

					//
					sendConfLayout(true, 0, CONST_imOp_respChannel, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, idInfo_to, _T(""));


				}

				//
				m_var.av.taskInfo.usLayoutType_starter = pContent->confLayout.usLayoutType;

				if (!dlgTalk_get_usLayoutType_local(hDlg)) {
					//  2012/05/20
					askToRefreshLayout_mgr(hDlg);
				}

			}
			else {  //  2023/12/09
				//
				//
				if (pContent->confLayout.usOp == CONST_imOp_videoTop) {

					QY_MESSENGER_ID idInfo_curr;
					idInfo_curr.ui64Id = pContent->confLayout.confLayoutParam.resp.curr_idinfo;

					pProcInfo->do_videoCurrInfo(hDlg, &m_var, pContent);

					//
					showInfo_open0(0, 0, _T("doSelLayoutType  resc yidong  videoTop "));

				}
				if (pContent->confLayout.usOp == CONST_imOp_videoBottom) {
					QY_MESSENGER_ID idInfo_curr;
					idInfo_curr.ui64Id = pContent->confLayout.confLayoutParam.resp.curr_idinfo;

					pProcInfo->do_videoCurrInfo(hDlg, &m_var, pContent);

					//
					showInfo_open0(0, 0, _T("doSelLayoutType  resc yidong  videoBottom "));

				}
				if (pContent->confLayout.usOp == CONST_imOp_videoLeft) {
					QY_MESSENGER_ID idInfo_curr;
					idInfo_curr.ui64Id = pContent->confLayout.confLayoutParam.resp.curr_idinfo;

					pProcInfo->do_videoCurrInfo(hDlg, &m_var, pContent);
					//
					showInfo_open0(0, 0, _T("doSelLayoutType  resc yidong  videoLeft "));
				}
				if (pContent->confLayout.usOp == CONST_imOp_videoRight) {
					QY_MESSENGER_ID idInfo_curr;
					idInfo_curr.ui64Id = pContent->confLayout.confLayoutParam.resp.curr_idinfo;

					pProcInfo->do_videoCurrInfo(hDlg, &m_var, pContent);

					//
					showInfo_open0(0, 0, _T("doSelLayoutType  resc yidong  videoRight "));
				}
				if (pContent->confLayout.usOp == CONST_imOp_loseSel) {
					int  ii = 0;
					//视频区域失去高光触发
					//
					showInfo_open0(0, 0, _T("doSelLayoutType  resc  loseSel "));

					pContent->confLayout.confLayoutParam.resp.ii;

					pProcInfo->do_videoCurrInfo(hDlg, &m_var, pContent);

				}
				if (pContent->confLayout.usOp == CONST_imOp_phone_respCurr) {
					int  ii = 0;


					pContent->confLayout.confLayoutParam.resp.ii;


				}

			}
			break;

		}
		if (pContent->uiType == CONST_imCommType_confNvrInfo) {

			//
			if (!pMgrVar->av.taskInfo.bTaskExists)  break;
			//
			if (pMgrVar->av.taskInfo.ucbStarter) {
				//
				if (pContent->confNvrInfo.ucbResp) {  //  发给requester

					//
					showInfo_open0(0, 0, _T("recv confNvrInfo resp, rediect to requester"));

					//
					QY_MESSENGER_ID  idInfo_to;  idInfo_to = pContent->confNvrInfo.idInfo_requester;
					QY_MESSENGER_ID  idInfo_requester;  idInfo_requester = pContent->confNvrInfo.idInfo_requester;
					NvrInfo nvrInfo = pContent->confNvrInfo.nvrInfo;
					nvrInfo.ui64Id = pMsg->task.data.route.idInfo_from.ui64Id;
					//
					sendConfNvrInfo(&nvrInfo, true, pMgrVar->addr.idInfo, idInfo_requester, idInfo_to, _T(""));
					break;
				}

				break;
			}

			//
			if (!pContent->confNvrInfo.ucbResp) {
				//
				QY_MESSENGER_ID  idInfo_to; idInfo_to = pMgrVar->av.taskInfo.idInfo_starter;
				QY_MESSENGER_ID  idInfo_requester; idInfo_requester = pContent->confNvrInfo.idInfo_requester;
				//
				//int  sendConfNvrInfo(NvrInfo * pNvrInfo, unsigned  char  ucbResp, QY_MESSENGER_ID idInfo_imGrp_related, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint);
				sendConfNvrInfo(&pProcInfo->m_ipcProc.dev.nvrInfo, true, pMgrVar->addr.idInfo, idInfo_requester, idInfo_to, _T(""));

				//
				showInfo_open0(0, 0, _T("sendConfNvrInfo: dev"));

				//
				break;
			}
			//
			_sntprintf(tBuf, mycountof(tBuf), _T("recv confNvrInfo resp, cnt %d"), (int)pContent->confNvrInfo.nvrInfo.usCnt);
			showInfo_open0(0, 0, tBuf);
			//						  
			pProcInfo->m_ipcProc.op.nvrInfo = pContent->confNvrInfo.nvrInfo;
			//pProcInfo->m_ipcProc.op.idInfo.ui64Id = pMsg->task.data.route.idInfo_from.ui64Id;
			//
			break;
		}
		if (pContent->uiType == CONST_imCommType_confState) {  //  2017/09/17
			//
			dlgTalk_proc_recvd_confState(hDlg, &m_var, &pMsg->task, &pContent->confState);
			//
			break;
		}
		if (pContent->uiType == CONST_imCommType_confCtrlState) {
			//
			dlgTalk_proc_recvd_confCtrlState(hDlg, &m_var, &pMsg->task, &pContent->confCtrlState);
			//
			break;
		}


		//
		activateWnd(hDlg, m_var);	//  ÕâÀïÒªÉÁÁÁ¶Ô»°¿ò¡£ÌáÐÑÓÃ»§µÄ×¢Òâ
		//  m_var.ucbNewMsgArrives  =  TRUE;
		dlgTalk_set_newMsgArrives(hDlg, &m_var, TRUE);

		if (!isTalkerShadowMgr(m_var.addr))  goto  errLabel;

		//
		dlgTalk_displayAvStatus(hDlg, m_var, 0, 0, 0);
		//
		TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)m_var.pShadowInfo;
		if (!pShadowMgr)  goto  errLabel;
		for (i = 0; i < mycountof(pShadowMgr->shadows); i++) {
			if (pShadowMgr->shadows[i].hShadow && isTalkerSubtype_canInput(pShadowMgr->shadows[i].iTalkerSubType)) {
				CHelp_getDlgTalkVar	help_getDlgTalkVar;
				tmpHandler_showMsg_displayTask(pShadowMgr->shadows[i].hShadow, (DLG_TALK_var*)help_getDlgTalkVar.getVar(pShadowMgr->shadows[i].hShadow), pParam, pMsg);
			}
		}
		//
		tmpHandler_showMsg_displayTask(hDlg, &m_var, pParam, pMsg);

		//
		if (pParam->bNewMsg) {
			postImMsg2Log_isClient(pMsg, offsetof(MIS_MSG_TASK, data) + pMsg->task.lenInBytes);
		}

		MIS_CNT* pMisCnt = (MIS_CNT*)pMsg->task.pMisCnt;
		if (!pMisCnt)  goto  errLabel;

		//  2010/09/06
		if (pMsg->task.data.route.idInfo_from.ui64Id != pMisCnt->idInfo.ui64Id) {
			if (pContent->uiType == CONST_imCommType_transferAvInfo) {
				QM_OBJQ_MEM				mem;
				QMEM_MESSENGER_CLI* pQMemObj = NULL;
				unsigned  int				uiRuleCmd = 0;

				if (findQMemByKey(pProcInfo->pSgiParam, (QM_OBJQ*)m_var.pMisCnt->pObjQ, &m_var.addr.idInfo, &mem)) {
#ifdef  __DEBUG__
					traceLog((TCHAR*)_T("dlgTalk_OnInitDialog failed, findQMemByKey failed."));
#endif
					goto  errLabel;
				}
				if (!mem.pQMemObj)  goto  errLabel;

				pQMemObj = (QMEM_MESSENGER_CLI*)mem.pQMemObj;

				if (pContent->transferAvInfo.uiTaskType == CONST_imTaskType_transferAvInfo
					||  pContent->transferAvInfo.uiTaskType  ==  CONST_imTaskType_shareDevice_grp) 
				{
					//
					//  2016/02/12
					set_recentAvRecvd_gZone(pProcInfo, hDlg);
					//
					BOOL  bPermitted = FALSE;

					if (bAutoAccepted_avCall(hDlg, &pQMemObj->rules, pContent->transferAvInfo.uiTaskType)) {
						bPermitted = TRUE;
					}
					//
					if (bPermitted)
					{
#if  0
						if (!m_var.av.taskInfo.bTaskExists) {
							//
							if (m_var.av.autoAnswer_av.task.bTaskNeedAutoAnswered)  goto  errLabel;
							//  
							if (isRuleCmdPermit(pQMemObj->rules.uiCmd_autoAnswer_av))  uiRuleCmd = pQMemObj->rules.uiCmd_autoAnswer_av;
							else  uiRuleCmd = pQMemObj->customerService.rules.uiCmd_autoAnswer_av;
							m_var.av.autoAnswer_av.uiCmd_autoAnswer = uiRuleCmd;
							//
							m_var.av.autoAnswer_av.task.iTaskId = pMsg->task.iTaskId;
							m_var.av.autoAnswer_av.task.iTaskStatus = pMsg->task.iStatus;
							m_var.av.autoAnswer_av.task.bTaskNeedAutoAnswered = TRUE;
						}
#endif
						//  2014/12/09
						m_var.autoAnswer.bTaskExists = TRUE;
					}
					//
					//  2016/05/09
					_sntprintf(tBuf, mycountof(tBuf), _T("tmpHandler_showMsg: task transferAvInfo, from %I64u. bPermitted %d"), pMsg->task.data.route.idInfo_from.ui64Id, bPermitted);
					showInfo_open0(0, 0, tBuf);
					//
				}
				else  if (pContent->transferAvInfo.uiTaskType == CONST_imTaskType_shareScreen) {		//  2010/12/20
					BOOL  bPermitted = FALSE;

					if (bAutoAccepted_avCall(hDlg, &pQMemObj->rules, pContent->transferAvInfo.uiTaskType)) {
						bPermitted = TRUE;
					}
					//
					if (bPermitted)
					{
#if  0
						//
						if (isRuleCmdPermit(pQMemObj->rules.uiCmd_autoAnswer_screen))  uiRuleCmd = pQMemObj->rules.uiCmd_autoAnswer_screen;
						else  uiRuleCmd = pQMemObj->customerService.rules.uiCmd_autoAnswer_screen;
						m_var.av.autoAnswer_screen.uiCmd_autoAnswer = uiRuleCmd;
						//
						m_var.av.autoAnswer_screen.task.iTaskId = pMsg->task.iTaskId;
						m_var.av.autoAnswer_screen.task.iTaskStatus = pMsg->task.iStatus;
						m_var.av.autoAnswer_screen.task.bTaskNeedAutoAnswered = TRUE;
#endif
						//  2014/12/09
						m_var.autoAnswer.bTaskExists = TRUE;
					}
				}
				else  if (pContent->transferAvInfo.uiTaskType == CONST_imTaskType_remoteAssist) {		//  2017/08/23
					BOOL  bPermitted = FALSE;

					if (bAutoAccepted_avCall(hDlg, &pQMemObj->rules, pContent->transferAvInfo.uiTaskType)) {
						bPermitted = TRUE;
					}
					//
					if (bPermitted)
					{
#if  0
						//
						if (isRuleCmdPermit(pQMemObj->rules.uiCmd_autoAnswer_screen))  uiRuleCmd = pQMemObj->rules.uiCmd_autoAnswer_screen;
						else  uiRuleCmd = pQMemObj->customerService.rules.uiCmd_autoAnswer_screen;
						m_var.av.autoAnswer_screen.uiCmd_autoAnswer = uiRuleCmd;
						//
						m_var.av.autoAnswer_screen.task.iTaskId = pMsg->task.iTaskId;
						m_var.av.autoAnswer_screen.task.iTaskStatus = pMsg->task.iStatus;
						m_var.av.autoAnswer_screen.task.bTaskNeedAutoAnswered = TRUE;
#endif
						//  2014/12/09
						m_var.autoAnswer.bTaskExists = TRUE;
					}
				}
				else  if (pContent->transferAvInfo.uiTaskType == CONST_imTaskType_shareMediaFile) {	//  2010/12/20
					BOOL  bPermitted = FALSE;

					if (bAutoAccepted_avCall(hDlg, &pQMemObj->rules, pContent->transferAvInfo.uiTaskType)) {
						bPermitted = TRUE;
					}
					//
					if (bPermitted)
					{
#if  0
						m_var.av.autoAnswer_mediaFile.uiCmd_autoAnswer = pQMemObj->rules.uiCmd_autoAnswer_mediaFile;
						m_var.av.autoAnswer_mediaFile.task.iTaskId = pMsg->task.iTaskId;
						m_var.av.autoAnswer_mediaFile.task.iTaskStatus = pMsg->task.iStatus;
						m_var.av.autoAnswer_mediaFile.task.bTaskNeedAutoAnswered = TRUE;
#endif
						//  2014/12/09
						m_var.autoAnswer.bTaskExists = TRUE;
					}
				}
				//
			}
			else  if (pContent->uiType == CONST_imCommType_queryCustomerServiceOfficerReq) {		//  2011/04/08
#if  0
				if (m_var.addr.uiObjType == CONST_objType_messenger) {						//  暂时只有messenger才可以
					m_var.av.autoAnswer_customerService.uiCmd_autoAnswer = CONST_ruleCmd_permit;	//  这里暂时采用不需要设置就可以自动响应的办法，因为在服务器上实际上设置的客服可以认为是已经授权了。
					m_var.av.autoAnswer_customerService.task.iTaskId = pMsg->task.iTaskId;
					m_var.av.autoAnswer_customerService.task.iTaskStatus = pMsg->task.iStatus;
					m_var.av.autoAnswer_customerService.task.bTaskNeedAutoAnswered = TRUE;
				}
#endif
				//  2014/12/09											
				m_var.autoAnswer.bTaskExists = TRUE;
			}
			else  if (pContent->uiType == CONST_imCommType_transferFileReq) {  //  2015/08/05
				if (bSupported_fileServer(pQyMc)) {
					m_var.autoAnswer.bTaskExists = TRUE;
				}
				else {
					if (pContent->transferFileReq.usSubtype == CONST_procOfflineResSubtype_download) {
						m_var.autoAnswer.bTaskExists = TRUE;
					}
				}
				//
			}
			else {
#ifdef  __DEBUG__
				//  其他的contentType不需要自动处理. 2011/04/08
#endif
			}

		}

	}
	break;

	default:
		break;
	}

	iErr = 0;

errLabel:


	//  2013/09/09	
	dyn_d3dWall_refreshWallMemByTalker(hDlg);

	return  iErr;


}


