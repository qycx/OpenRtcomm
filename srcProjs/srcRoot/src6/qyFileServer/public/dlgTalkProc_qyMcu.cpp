



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
int  tmpHandler_showMsg_task_qyMcu(void* hDlgTalkParam, DLG_TALK_var& m_var, void* p1, void* pMsgParam)
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
#ifdef  __DEBUG__
				traceLogA((char*)"starter recv layout .");
#endif

				//
				if (!isTalkerShadowMgr(m_var.addr)) {
					break;
				}

				//
				{
					unsigned  short  usOp = pContent->confLayout.usOp;
					tBuf[0] = 0;
					_sntprintf(tBuf, mycountof(tBuf), _T("confLayout.l158: %s. op %d"), tBuf, (int)usOp);
					ConfLayoutParam* pParam = &pContent->confLayout.confLayoutParam;
					if (pParam) {
						_sntprintf(tBuf, mycountof(tBuf), _T("%s. x %d, y %d, channel %d"), tBuf, (int)pParam->phoneEnlargeParam.x, (int)pParam->phoneEnlargeParam.y, pParam->ipcParam.iChannel);
					}
					//
					showInfo_open0(0, 0, tBuf);
				}


				//
				if (pContent->confLayout.usOp == CONST_imOp_enlargeImg) {

					//
					QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
					if (pTaskInfo && pTaskInfo->bUsed) {
						QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
						if (pTaskData) {
							if (pTaskData->uiType == CONST_taskDataType_conf) {
								QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskData;
								DLG_TALK_videoConference* pVideoConference = (DLG_TALK_videoConference*)&pTc->videoConference;
								pVideoConference->confLayoutParam1 = pContent->confLayout.confLayoutParam;

								if (pContent->confLayout.confLayoutParam.enlargeParam.ui64Id) {
									//  检查confLayoutParam.ui64Id是否为nvr, 是则发该终端去取nvrInfo
									DLG_TALK_videoConferenceActiveMemFrom* pActiveMem;
									for (i = 0; i < pVideoConference->usCntLimit_activeMems_from; i++) {
										pActiveMem = &pVideoConference->activeMems_from[i];
										if (!pActiveMem->avStream.idInfo.ui64Id) continue;
										if (pActiveMem->avStream.idInfo.ui64Id == pContent->confLayout.confLayoutParam.enlargeParam.ui64Id) {
											break;
										}
									}
									if (i < pVideoConference->usCntLimit_activeMems_from) {
										//if (pActiveMem->ucbNvr) 
										{
											//
											QY_MESSENGER_ID idInfo_to; idInfo_to.ui64Id = pContent->confLayout.confLayoutParam.enlargeParam.ui64Id;
											if (idInfo_to.ui64Id == pMisCnt->idInfo.ui64Id) goto  errLabel;
											QY_MESSENGER_ID idInfo_requester; idInfo_requester.ui64Id = pMsg->task.data.route.idInfo_from.ui64Id;
											//
											sendConfNvrInfo(nullptr, 0, pMgrVar->addr.idInfo, idInfo_requester, idInfo_to, _T(""));
											//
											int  ii = 0;
										}
									}
									//
								}
							}
						}
					}



					//
					break;
				}
				//
				if (pContent->confLayout.usOp == CONST_imOp_phone_enlargeImg) {

					//手机放大指令接收
					int ii = 0;

					int usEnlargeType = pContent->confLayout.confLayoutParam.phoneEnlargeParam.usEnlargeType;
					int x = pContent->confLayout.confLayoutParam.phoneEnlargeParam.x;  //例如    100
					int y = pContent->confLayout.confLayoutParam.phoneEnlargeParam.y;  //例如    120
					// int  x = 100;  y = 200; 
					m_var.m_bEnlarge1 = true;
					m_var.x = x;
					m_var.y = y;
					m_var.idInfo_requester.ui64Id = pMsg->task.data.route.idInfo_from.ui64Id;

					//
					//sendStatusConfLayoutParam(hDlg, m_var.addr.idInfo, _T("send layoutReq"));

					//
					// 								  
					break;
				}




				//
				if (pContent->confLayout.usOp == CONST_imOp_setOneBig) {

				}
				if (pContent->confLayout.usOp == CONST_imOp_videoTop) {
					m_var.m_moveOperation = 0;

					showInfo_open0(0, 0, _T("mcu  gaoguang imOp_videoTop"));
					break;
				}
				if (pContent->confLayout.usOp == CONST_imOp_videoBottom) {
					m_var.m_moveOperation = 1;

					showInfo_open0(0, 0, _T("mcu  gaoguang imOp_videoBottom"));
					break;
				}
				if (pContent->confLayout.usOp == CONST_imOp_videoLeft) {
					m_var.m_moveOperation = 2;

					showInfo_open0(0, 0, _T("mcu  gaoguang imOp_videoLeft"));
					break;
				}
				if (pContent->confLayout.usOp == CONST_imOp_videoRight) {
					m_var.m_moveOperation = 3;

					showInfo_open0(0, 0, _T("mcu  gaoguang imOp_videoRight"));
					break;
				}

				if (pContent->confLayout.usOp == CONST_imOp_cancelSel) {

					//主動取消 高光
					//int ii = 0;
					m_var.m_moveOperation = 4;
					showInfo_open0(0, 0, _T("mcu  gaoguang imOp_cancelSel"));
					break;
				}

				if (pContent->confLayout.usOp == CONST_imOp_phone_cancelEnlargeImg) {

					//手机取消放大指令接收
					int ii = 0;
					m_var.m_bEnlarge1 = false;
					m_var.x = -1;
					m_var.y = -1;

					//
					QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
					if (pTaskInfo && pTaskInfo->bUsed) {
						QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
						if (pTaskData) {
							if (pTaskData->uiType == CONST_taskDataType_conf) {
								QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskData;
								DLG_TALK_videoConference* pVideoConference = (DLG_TALK_videoConference*)&pTc->videoConference;

								//
								{
									OneBigLayoutParam  oblp = pVideoConference->confLayoutParam1.oneBigLayoutParam;
									//pVideoConference->confLayoutParam = pContent->confLayout.confLayoutParam;
									memset(&pVideoConference->confLayoutParam1, 0, sizeof(pVideoConference->confLayoutParam1));

									showInfo_open0(0, 0, _T("mcu  qiuji memset------------------------------"));
									pVideoConference->confLayoutParam1.oneBigLayoutParam = oblp;
								}
							}
						}
					}


					FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
					if (!pFuncs)  return  -1;
					//QY_MESSENGER_ID idInfo_to = m_var.addr.idInfo;
					QY_MESSENGER_ID idInfo_imGrp_related = m_var.addr.idInfo;
					//QY_MESSENGER_ID idInfo_requester;
				   // idInfo_requester.ui64Id = 0;
					ConfLayoutParam  confLayoutParam = { 0 };

					QY_MESSENGER_ID idInfo_to; idInfo_to = m_var.addr.idInfo;
					if (idInfo_to.ui64Id == pMisCnt->idInfo.ui64Id) goto  errLabel;
					QY_MESSENGER_ID idInfo_requester; idInfo_requester.ui64Id = 0;

					//pFuncs->pf_sendVideoConferenceLayout(true, 0, CONST_imOp_phone_respCurr, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, idInfo_to, _T(""));


					//
					sendStatusConfLayoutParam(hDlg, m_var.addr.idInfo, _T("send layoutReq"));
					//
					break;
				}


				if (pContent->confLayout.usOp == CONST_imOp_enlargeChannel
					|| pContent->confLayout.usOp == CONST_imOp_setOneBig)
				{
					//
					QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
					if (pTaskInfo && pTaskInfo->bUsed) {
						QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
						if (pTaskData) {
							if (pTaskData->uiType == CONST_taskDataType_conf) {
								QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskData;
								DLG_TALK_videoConference* pVideoConference = (DLG_TALK_videoConference*)&pTc->videoConference;

								//
								if (pContent->confLayout.usOp == CONST_imOp_enlargeChannel) {
									OneBigLayoutParam  oblp = pVideoConference->confLayoutParam1.oneBigLayoutParam;
									if (pContent->confLayout.confLayoutParam.enlargeParam.ui64Id == 0) {
										showInfo_open0(0, 0, _T("mcu  qiuji enlargeParamUid64------------------------------"));
										int ii = 1;
									}
									pVideoConference->confLayoutParam1 = pContent->confLayout.confLayoutParam;
									pVideoConference->confLayoutParam1.oneBigLayoutParam = oblp;

									//
									if (pContent->confLayout.confLayoutParam.enlargeParam.ui64Id) {
										//  检查confLayoutParam.ui64Id是否为nvr, 是则发该终端去取nvrInfo
										DLG_TALK_videoConferenceActiveMemFrom* pActiveMem;
										for (i = 0; i < pVideoConference->usCntLimit_activeMems_from; i++) {
											pActiveMem = &pVideoConference->activeMems_from[i];
											if (!pActiveMem->avStream.idInfo.ui64Id) continue;
											if (pActiveMem->avStream.idInfo.ui64Id == pContent->confLayout.confLayoutParam.enlargeParam.ui64Id) {
												break;
											}
										}
										if (i < pVideoConference->usCntLimit_activeMems_from) {
											//if (pActiveMem->ucbNvr) 
											{

												//
													//
												//sendStatusConfLayoutParam(hDlg, m_var.addr.idInfo, _T("send layoutReq"));

												//
												QY_MESSENGER_ID idInfo_to; idInfo_to.ui64Id = pContent->confLayout.confLayoutParam.enlargeParam.ui64Id;
												if (idInfo_to.ui64Id == pMisCnt->idInfo.ui64Id) goto  errLabel;
												QY_MESSENGER_ID idInfo_requester; idInfo_requester.ui64Id = pMsg->task.data.route.idInfo_from.ui64Id;
												//
												//sendConfNvrInfo(nullptr, 0, pMgrVar->addr.idInfo, idInfo_requester, idInfo_to, _T(""));
												sendConfLayout(false, 0, CONST_imOp_enlargeChannel, &pContent->confLayout.confLayoutParam, pMgrVar->addr.idInfo, idInfo_requester, idInfo_to, _T(""));
												//
											
												int  ii = 0;
											}
										}
										//
									}
								}
								else  if (pContent->confLayout.usOp == CONST_imOp_setOneBig) {
									//
									pVideoConference->confLayoutParam1.oneBigLayoutParam = pContent->confLayout.confLayoutParam.oneBigLayoutParam;

									m_var.av.taskInfo.tmpLayoutInfo.oneBigLayoutParam = pContent->confLayout.confLayoutParam.oneBigLayoutParam;

									//
									_sntprintf(tBuf, mycountof(tBuf), _T("setOneBig: b %d, id %I64u"),
										(int)pVideoConference->confLayoutParam1.oneBigLayoutParam.ucbOneBigLayout,
										pVideoConference->confLayoutParam1.oneBigLayoutParam.ui64Id);
									//
									showInfo_open0(0, 0, tBuf);

								}

							}
						}
					}



					//
					break;
				}

				if (pContent->confLayout.usOp == CONST_imOp_respChannel) 
				{
					 pContent->confLayout.confLayoutParam.ipcParam;
					 int ii = 0;

					 if (!m_var.av.taskInfo.bTaskExists)  goto  errLabel;
					 if (!m_var.av.taskInfo.ucbStarter)  goto  errLabel;

					 //
					 //if (m_var.av.taskInfo.iTaskId != iTaskId)  return  -1;

					 //
					 QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
					 if (!pTaskInfo)  return  -1;
					 if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  return  -1;
					 QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;

					 //		
					 DLG_TALK_videoConference* pVc = &pTc->videoConference;

					 //
					 if (pVc->confLayoutParam1.ipcParam.iChannel != pContent->confLayout.confLayoutParam.ipcParam.iChannel) {
						 showInfo_open0(0, 0, _T("respChannel failed, iChannel not matched"));
						 goto  errLabel;
					 }

					 pVc->confLayoutParam1.ipcParam = pContent->confLayout.confLayoutParam.ipcParam;

					 //
					 sendStatusConfLayoutParam(hDlg, m_var.addr.idInfo, _T("send layoutReq"));
					 break;

				}

				//
				break;

			}

			//  以下为参会人
			if (pContent->confLayout.usOp == CONST_imOp_enlargeChannel) {
				doSelIpc_local(&pContent->confLayout.confLayoutParam.ipcParam, hMgr);
			}

			//
			m_var.av.taskInfo.usLayoutType_starter = pContent->confLayout.usLayoutType;

			if (!dlgTalk_get_usLayoutType_local(hDlg)) {
				//  2012/05/20
				askToRefreshLayout_mgr(hDlg);
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

				if (pContent->transferAvInfo.uiTaskType == CONST_imTaskType_transferAvInfo) {
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
