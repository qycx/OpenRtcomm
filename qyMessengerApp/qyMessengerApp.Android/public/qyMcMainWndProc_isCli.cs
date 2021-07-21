using qyMessengerApp.Droid;
using System;
using System.Collections.Generic;
using System.Text;

namespace qy.Droid
{
	partial class qyFuncs_Droid
	{
		public static unsafe  int initVar_onCreate_mainFrame(IntPtr p0, object hMainWnd, ref QY_MC_mainWndVar pVar)
		{
			int iErr = -1;

# if  __DEBUG__
			traceLogA("initVar_onCreate_mainFrame enters.");
#endif

			//
			if (null==hMainWnd ) return -1;

			CCtxQyMc pQyMc = g.g_pQyMc;
			if (null==pQyMc) return -1;
			CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
			if (null==pProcInfo) return -1;
			if (pProcInfo.m_iCtxType != Consts.CONST_ctxType_qmc) return -1;

			//
			pProcInfo.dwThreadId_gui = qyFuncs.myGetCurrentProcessId();
			//
			pVar.ctxCaller = new CTX_caller();
			pVar.ctxCaller.type = Consts.CONST_ctxCallerType_thread;
			pVar.ctxCaller.dwThreadId = qyFuncs.myGetCurrentThreadId();


			//
			{

				//
				pVar.pMsgBuf_msgArrive = (MIS_MSGU*)qyFuncs.mymalloc(sizeof(MIS_MSGU));    //  .pVar  =  pSci->pVar;
				if (null==pVar.pMsgBuf_msgArrive) goto errLabel;

				
			}

			
			//pVar->uiTimerId = SetTimer(hMainWnd, 1, 1000, NULL);
			GuiShare.pf_mainWnd_setTimer();

			iErr = 0;
		errLabel:

			if (0!=iErr) exitVar_onDestroy_mainFrame(p0, hMainWnd, ref pVar);

			return iErr;
		}

		public static unsafe  int exitVar_onDestroy_mainFrame(IntPtr p0, object hMainWnd, ref QY_MC_mainWndVar pVar)
		{
			int iErr = -1;

			if (null==hMainWnd )
			{
				qyFuncs.traceLogA("exitVar_onDestroy_mainFrame failed: pMainWnd or pVar is null");
				return -1;
			}

			CCtxQyMc pQyMc = g.g_pQyMc;
			if (null==pQyMc) return -1;


			qyFuncs.traceLogA("exitVar_onDestroy_mainFrame enters.");
			qyFuncs.showInfo_open(0, null, ("exitVar_onDestroy_mainFrame enters."));

			//
			//if (pVar->uiTimerId) KillTimer(hMainWnd, pVar->uiTimerId);
			GuiShare.pf_mainWnd_killTimer();


			//
			

			//
			if ( pVar.pMsgBuf_msgArrive!=null)
            {
				qyFuncs.myfree((IntPtr)pVar.pMsgBuf_msgArrive); pVar.pMsgBuf_msgArrive = null;
            }

			//
			qyFuncs.traceLogA("exitVar_onDestroy_mainFrame leaves.");
			qyFuncs.showInfo_open(0, null, ("exitVar_onDestroy_mainFrame leaves."));


			return 0;
		}



		public static unsafe int tmpHandler_findMissingOrgReq(object p0, object pMsgTaskStatusParam, object pQElem)
		{
			int iRet = -1;
			//  p0;
			MIS_MSG_taskStatus* pMsgTaskStatus = (MIS_MSG_taskStatus*)(IntPtr)pMsgTaskStatusParam;
			//
			//
			// 
			int index_taskInfo = (int)pQElem;
			//
			CCtxQyMc pQyMc = g.g_pQyMc;
			CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
			MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;
			/*
			BOOL bMatched = FALSE;

			if (pMsg->uiType == CONST_misMsgType_talkingFriend_qmc)
			{

				MIS_MSG_TALKINGFRIEND_QMC* pMem = &pMsg->talkingFriend_qmc;

				if (isTalkerShadowMgr(pMem->addr))
				{
					SendMessage(pMem->hWnd, CONST_qyWm_comm, 0, (LPARAM)pMsgTaskStatus);
					if (pMsgTaskStatus->ucbFound)
					{
						iRet = 1; goto errLabel;
					}
				}

			}
			*/
			if (!qyFuncs.qmcTaskInfo_bAlive(mainActivity.var_common.ctxCaller,pProcInfo, index_taskInfo)) goto errLabel;
			QMC_TASK_INFO pTaskInfo = qyFuncs.getQmcTaskInfoByIndex(mainActivity.var_common.ctxCaller,pProcInfo, index_taskInfo,"tmpHandler_findMissingOrgReq");
			QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
			if (pTaskData == null) goto errLabel;

			fixed (MIS_MSGU* tmp_pMsg = &pTaskData.msgU) {
				if (tmp_pMsg->uiType != Consts.CONST_misMsgType_task) goto errLabel;
				IM_CONTENTU *pContent = (IM_CONTENTU*)tmp_pMsg->task.data.buf;
				if (pContent->uiType != Consts.CONST_imCommType_transferAvInfo) goto errLabel;
				AV_TRAN_INFO* pAvTranInfo = &pContent->transferAvInfo.ass.tranInfo;
				//
				if(pMsgTaskStatus->uiContentType==Consts.CONST_imCommType_transferAudioData
					&& pMsgTaskStatus->uiTranNo==pAvTranInfo->audio.uiTranNo_openAvDev)
                {
					iRet = 1; goto errLabel;
                }
				if( pMsgTaskStatus->uiContentType==Consts.CONST_imCommType_transferVideoData
					&&pMsgTaskStatus->uiTranNo==pAvTranInfo->video.uiTranNo_openAvDev)
                {
					iRet = 1; goto errLabel;
                }
			}

			iRet = 0;
		errLabel:
			return iRet;
		}


		public static unsafe int mainWnd_OnQyPostComm(object hMainWnd, ref QY_MC_mainWndVar var, int wParam, int lParam)
		{
			int lRet = -1;
			CCtxQyMc pQyMc = g.g_pQyMc;
			if (null == pQyMc) return -1;
			CCtxQmc pProcInfo = (CCtxQmc)pQyMc.get_pProcInfo();
			if (null == pProcInfo) return -1;
			if (pProcInfo.m_iCtxType != Consts.CONST_ctxType_qmc) return -1;
			MIS_CNT pMisCnt = pProcInfo.pMisCnt;
			MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;

			bool bDbg = false;
			string str;

#if DEBUG
			bDbg = true;
#endif

			//  char				buf[1024]		=	"";
			uint len;
			int i;

			//
			if (pQyMc.bGuiQuit)
			{
				qyFuncs.showInfo_open(0, null, ("mainWnd_OnQyPostComm failed, bGuiQuit is true"));
				return -1;
			}
			if (pQyMc.bPrepareToGuiQuit)
			{
				qyFuncs.showInfo_open(0, null, ("mainWnd_OnQyPostComm failed, bPrepareToGuiQuit is true"));
				return -1;
			}

            //
            if (bDbg)
            {
				qyFuncs.showInfo_open(0, null, "mainWnd_OnQyPostComm enters");
				qyFuncs.showAllTc(mainActivity.var_common.ctxCaller,"mainWnd_OnQyPostComm enters");
            }

			//
			switch (wParam)
			{
				/*
				case CONST_qyWmParam_setActiveWindow:
					if (lParam)  ::PostMessage((HWND)lParam, CONST_qyWm_postComm, wParam, 0);
					break;
				*/
				case Consts.CONST_qyWmParam_msgArrive:
					{
						//  CQyMalloc			mallocObj;
						MIS_MSGU* pMsg = var.pMsgBuf_msgArrive; //  (  MIS_MSGU  *  )mallocObj.malloc(  sizeof(  MIS_MSGU  )  );
						if (null == pMsg) goto errLabel;

						for (; !pQyMc.bQuit;)
						{
							//MACRO_memset_misMsg(pMsg);
							len = (uint)sizeof(MIS_MSGU);
							if (0 != qyFuncs.qGetMsg(pQyMc.gui.processQ, (IntPtr)pMsg, &len)) break;
							switch (pMsg->uiType)
							{
								case Consts.CONST_misMsgType_talk:
								case Consts.CONST_misMsgType_task:
									{
										object hWnd = null;
										MSGR_ADDR addr_logicalPeer;
										bool bNeedNotShowWnd = false;

										qyFuncs.mymemset((IntPtr)(byte*)&addr_logicalPeer, 0, sizeof(MSGR_ADDR));
										if (pMsg->uiType == Consts.CONST_misMsgType_talk)
										{
											//
											if (null == (pMisCnt = (MIS_CNT)pProcInfo.pMisCnt)) goto errLabel;
											//
											if (0 != qyFuncs.myGetPeer("", &pMsg->talk.data.route, &pMsg->talk.addr_logicalPeer, &addr_logicalPeer)) goto errLabel;

											//										
											IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->talk.data.buf;

											//  2017/07/17
											if (pContent->uiType == Consts.CONST_imCommType_htmlContent)
											{
												/*
												if (pProcInfo->avConsole.bGotMsg_avConsole)
												{
													//
													__declspec(dllexport)  int doAvConsole_cmd_recvMsg(__int64 ui64Id_from, __int64 ui64Id_to, TCHAR* tTxt);

													doAvConsole_cmd_recvMsg(pMsg->talk.data.route.idInfo_from.ui64Id, pMsg->talk.data.route.idInfo_to.ui64Id, pContent->html.wBuf);
													//
													showInfo_open(0, 0, _T("avConsole: bGotMsg_avConsole is true, doAvConsole_cmd_recvMsg called"));
													//
													break;
												}
												*/
												GuiShare.pf_gui_procMsg((IntPtr)pMsg);
											}


										}
										else if (pMsg->uiType == Consts.CONST_misMsgType_task)
										{
											//
											if (null == (pMisCnt = (MIS_CNT)pProcInfo.pMisCnt)) goto errLabel;
											//
											if (0 != qyFuncs.myGetPeer("", &pMsg->task.data.route, &pMsg->task.addr_logicalPeer, &addr_logicalPeer)) goto errLabel;

											//
											IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->task.data.buf;

											//
#if __DEBUG__
											if (pContent->uiType == CONST_imCommType_imGrp)
											{
												int ii = 0;
											}
#endif

											//  2009/09/07
											/*
											if (pMsg->task.uiTaskType == CONST_imTaskType_viewDynBmp
												|| pMsg->task.uiTaskType == CONST_imTaskType_viewGps)
											{
												//  2014/09/28			
												if (pContent->uiType == CONST_imCommType_transferAvInfo)
												{
													if (pContent->transferAvInfo.idInfo_logicalPeer.ui64Id)
													{
														if (findTalker(pQyMc, pMisCnt, &pContent->transferAvInfo.idInfo_logicalPeer, &hWnd))
														{
# if  __DEBUG__
															traceLog(_T("mainWnd_OnPostComm: retrieveDynBmps conf findTalker failed"));
#endif
															goto errLabel;
														}
														   ::SendMessage(hWnd, CONST_qyWm_comm, 0, (LPARAM)pMsg);
														break;
													}
												}

												//
												if (!IsWindow(pProcInfo->hWnd_shareDynBmps))
												{
													traceLogA("Not finished. hWnd_sharedWebcams is not valid");
													break;
												}
												   ::SendMessage(pProcInfo->hWnd_shareDynBmps, CONST_qyWm_comm, 0, (LPARAM)pMsg);

												break;
											}
											*/

											//  2015/06/06
											/*
											if (pContent->uiType == CONST_imCommType_ptzControlReq
												&& pContent->ptzControlReq.ucbReply)
											{
												if (findTalker(pQyMc, pMisCnt, &addr_logicalPeer.idInfo, &hWnd))
												{
# ifdef  __DEBUG__
													traceLog(_T("mainWnd_OnPostComm: reply for ptzControlReq, findTalker failed"));
#endif
													goto errLabel;
												}
												   ::SendMessage(hWnd, CONST_qyWm_comm, 0, (LPARAM)pMsg);
												break;
											}

											//  2012/08/08
											if (pContent->uiType == CONST_imCommType_ptzControlCmd)
											{
# ifdef  __DEBUG__
												traceLog(_T("mainWnd_OnPostComm: ptzControlCmd"));
#endif
												//  2016/07/20
												if (pContent->ptzControlCmd.cmdInfo.obj.uiObjType == CONST_objType_rtspStream)
												{
													SendMessage(pProcInfo->hWnd_shareDynBmps, CONST_qyWm_comm, 0, (LPARAM)pMsg);
													break;
												}

												//
												PARAM_viewLocalPtzControl param = { 0 };
												//
												doRemotePtzCmd(NULL, &pContent->ptzControlCmd, &param, &pProcInfo->ptzWnd);

												break;
											}
											*/
											//  2015/08/05
											if (pContent->uiType == Consts.CONST_imCommType_transferFileReq
												&& pContent->transferFileReq.usSubtype == Consts.CONST_procOfflineResSubtype_download)
											{
												if (0 != GuiShare.pf_findTalker(pQyMc, pMisCnt, addr_logicalPeer.idInfo, ref hWnd))
												{
#if __DEBUG__
													traceLog(_T("mainWnd_OnPostComm: transferFileReq download, findTalker failed"));
#endif
													goto errLabel;
												}

												//									 
												if (0 != GuiShare.pf_dlgTalk_qPostMsg(hWnd, (IntPtr)pMsg, len)) goto errLabel;


												GuiShare.pf_PostMessage(hWnd, Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_msgArrive, 0);
												//
												break;
											}
											//
											if (0 == pMsg->task.iTaskId)
											{

#if __DEBUG__
												traceLog(_T("mainWnd_OnQyPostComm: task.iTaskId is 0"));
#endif

												//
												bNeedNotShowWnd = true;
											}

										}
										else
											goto errLabel;

										//
									#if false
										//
										hWnd = null;

										//
										if (null == hWnd)
										{

											if (0 != pProcInfo.tryToTalkToMessenger_any(addr_logicalPeer.idInfo.ui64Id, bNeedNotShowWnd, false, ref hWnd)) goto errLabel;

										}

										//									 
										/*
										if (0 != dlgTalk_qPostMsg(hWnd, (IntPtr)pMsg, len)) goto errLabel;
										GuiShare.pf_PostMessage(hWnd, Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_msgArrive, 0);
										*/
										GuiShare.pf_gui_dlgTalk_procMsg(hWnd, (IntPtr)pMsg);
									#endif

									}
									break;

								case Consts.CONST_misMsgType_input:    //  2014/09/05
									{
										object hWnd = null;
										MSGR_ADDR addr_logicalPeer;

										IM_CONTENTU* pContent = qyFuncs.M_getMsgContent(pMsg->input.ucFlg, &pMsg->input.data);

										//
#if DEBUG
										if  (  pContent->uiType  ==  Consts.CONST_imCommType_confKey)
                                        {
											int ii = 0;
                                        }
#endif

										//  2014/05/05
										bool bMsgProcessed = false;
										switch (pContent->uiType)
										{
											case Consts.CONST_imCommType_transferAvInfo:
												 bMsgProcessed = true;
												//
												mainWnd_procMsgInput_transferAvInfo(hMainWnd, ref var, &pMsg->input);

												 break;
											case Consts.CONST_imCommType_transferAvReplyInfo:
												bMsgProcessed = true;
												//
												mainWnd_procMsgInput_transferAvReplyInfo(hMainWnd, ref var, &pMsg->input);
												//
												break;

											/*
										case Consts.CONST_imCommType_htmlContent:  //  2014/07/12
											bMsgProcessed = true;

											if (!(isUcFlgTalkData(pMsg->input.ucFlg) || isUcFlgRouteTalkData(pMsg->input.ucFlg)))
											{
#if __DEBUG__
												traceLog(_T("mainWnd_OnPostComm: error: resp html not from others"));
#endif
												goto errLabel;
											}
											if (isUcFlgResp(pMsg->input.ucFlg))
											{
												if (findTalker(pQyMc, pMisCnt, &pMsg->input.data.route.idInfo_from, &hWnd)) goto errLabel;
												   ::SendMessage(hWnd, CONST_qyWm_comm, 0, (LPARAM)pMsg);
												break;
											}
#if __DEBUG__
											traceLog(_T("Err: request html is not processed here"));
#endif
											break;
											*/
										case  Consts.CONST_imCommType_taskProcReq:  //  2014/10/09
												
												object hTalk=null;
												if(0==findTalker(pQyMc,pMisCnt,pMsg->input.addr_logicalPeer.idInfo, ref hTalk) ) {
											
												bMsgProcessed = true;
													//
													//::SendMessage(pContent->taskProcReq.hWnd_task, CONST_qyWm_comm, 0, (LPARAM)pMsg);
													dlgTalk_OnQyComm(hTalk, 0, pMsg);

											}
											break;
											/*
										case Consts.CONST_imCommType_procOfflineRes:  //  2015/08/03
											bMsgProcessed = TRUE;

											//  2015/06/05
#if __DEBUG__
											traceLog(_T("mainWnd_OnPostComm: get procOfflineRes from %I64u, bResp %d"), pMsg->input.data.route.idInfo_from.ui64Id, pContent->procOfflineResU.common.ucbResp);
#endif

											//
											if (!(isUcFlgTalkData(pMsg->input.ucFlg) || isUcFlgRouteTalkData(pMsg->input.ucFlg)))
											{
#if __DEBUG__
												traceLog(_T("mainWnd_OnPostComm: error: req retrieveDynBmps not from others"));
#endif
												goto errLabel;
											}
											//
											if (pContent->procOfflineResU.common.usSubtype == CONST_procOfflineResSubtype_download)
											{
												if (pProcInfo->talkToMessenger(pMsg->input.data.route.idInfo_from.ui64Id, FALSE, FALSE, &hWnd))
												{
#if __DEBUG__
													traceLog(_T("mainWnd_OnPostComm: procOfflineRes req talkToMessenger failed"));
#endif
													goto errLabel;
												}
											}
											else
											{
												if (findTalker(pQyMc, pMisCnt, &pMsg->input.data.route.idInfo_from, &hWnd))
												{
# ifdef  __DEBUG__
													traceLog(_T("mainWnd_OnPostComm: procOfflineRes req findTalker failed"));
#endif
										goto errLabel;
												}
											}
											   //
											   ::SendMessage(hWnd, CONST_qyWm_comm, 0, (LPARAM)pMsg);

											//												   
											break;
										case CONST_imCommType_imGrp:  //  2017/07/26
											bMsgProcessed = TRUE;
											//
											if ((isUcFlgTalkData(pMsg->input.ucFlg) || isUcFlgRouteTalkData(pMsg->input.ucFlg)))
											{
												//  说明时从其他的客户端发过来，通知临时组变化的。直接发到 dlgAvRes_mem_hzj上去显示分组成员。
												//traceLog(  _T(  "not finished. need to send to dlgAvRes_mem_hzj"  )  );
												//
												if (!IsWindow(pProcInfo->hWall_hzj))
												{
													traceLog(_T("hWall_hzj is invalid. imGrp can't be processed"));
													break;
												}
												   //
												   ::SendMessage(pProcInfo->hWall_hzj, CONST_qyWm_comm, 0, (LPARAM)pMsg);
												//
												break;
											}

											//
											hWnd = pProcInfo->cfgGrp.hWnd_cfgGrp;
											//
											if (IsWindow(hWnd))
											{
												   ::SendMessage(hWnd, CONST_qyWm_comm, 0, (LPARAM)pMsg);
												break;
											}
											//
											notifyProgressEnd(pMsg->input.uiTranNo, 0);

											//
											break;
											*/

											default:
												break;
										}
										if (bMsgProcessed) break;

										//
										if (0 == pMsg->input.addr_logicalPeer.idInfo.ui64Id)
										{
											/*
											switch (pContent->uiType)
											{
												case Consts.CONST_imCommType_refreshDynBmps:
												case Consts.CONST_imCommType_verifyViewDynBmp:
													   ::SendMessage(pProcInfo->hWnd_shareDynBmps, CONST_qyWm_comm, 0, (LPARAM)pMsg);
													break;
												case Consts.CONST_imCommType_retrieveCustomerServiceObjListReq:
													//
# if  __DEBUG__
													traceLog(_T("Not finished, CONST_imCommType_retrieveCustomerServiceObjListReq"));
													for (i = 0; i < pContent->retrieveCustomerServiceObjListReq.usCnt; i++)
													{
														traceLog(_T("mems[%d]: %I64u, %s"), i, pContent->retrieveCustomerServiceObjListReq.mems[i].idInfo.ui64Id, pContent->retrieveCustomerServiceObjListReq.mems[i].displayName);
													}
#endif
													//
													for (i = 0; i < mycountof(pProcInfo->customerService.objs); i++)
													{
														if (i < pContent->retrieveCustomerServiceObjListReq.usCnt)
														{
															memcpy(&pProcInfo->customerService.objs[i], &pContent->retrieveCustomerServiceObjListReq.mems[i], sizeof(pProcInfo->customerService.objs[i])  );
	
														}
															else
														{
																	memset(&pProcInfo->customerService.objs[i], 0, sizeof(pProcInfo->customerService.objs[i])  );
														}
													}
													PostMessage(pQyMc->gui.hMainWnd, WM_COMMAND, MAKEWPARAM(ID_refreshLayout, 0), 0);
													break;
											default:
													     TCHAR tBuf[128];
														_sntprintf(tBuf, mycountof(tBuf), _T("mainWnd_OnPostComm: msgInput, unprocessed content.type %d"), pContent->uiType);
														showInfo_open(0, 0, tBuf);
														break;
											}
											*/
											break;
										}

										//
										qyFuncs.mymemset((IntPtr)(byte*)&addr_logicalPeer, 0, sizeof(MSGR_ADDR));
										qyFuncs.mylstrcpyn(addr_logicalPeer.misServName, "", Consts.CONST_maxMisServNameLen + 1);
										addr_logicalPeer.idInfo.ui64Id = pMsg->input.addr_logicalPeer.idInfo.ui64Id;        //  ÔÚÈ¡webMessengerµÄ×´Ì¬Ê±£¬»áÓÃµ½Õâ¸öÀàÐÍ¡£
																															//  Ã»ÓÐ¶ÀÁ¢Æô¶¯´°¿ÚµÄÄÜÁ¦£¬µ«ÊÇ¿ÉÒÔ·¢ÏÖ´°¿Ú£¬È»ºó½«ÏûÏ¢ËÍµ½´°¿ÚÄÇÀï¡£


										hWnd = null;

										//  2013/09/09

										//
										if (null == hWnd)
										{
											//  2014/01/14
											bool bNeedNotShowWnd = false;
											if (0 != pProcInfo.tryToTalkToMessenger_any(addr_logicalPeer.idInfo.ui64Id, bNeedNotShowWnd, false, ref hWnd))
											{
												str = string.Format("mainWnd_onQyPostComm. trytoTalkToMessenger_any {0} failed", addr_logicalPeer.idInfo.ui64Id);
												qyFuncs.traceLog(str);
												//
												goto errLabel;
											}
										}

										//::SendMessage(hWnd, CONST_qyWm_comm, 0, (LPARAM)pMsg);
										GuiShare.pf_gui_dlgTalk_procMsg(hWnd, (IntPtr)pMsg);

									}

									break;
								

										
								case  Consts.CONST_misMsgType_taskStatus:
								{
									object hWnd = null;
									MSGR_ADDR addr_logicalPeer;
									//  QY_MESSENGER_ID			idInfo_peer;


									if (pMsg->taskStatus.ucbNotification)
									{
										displayNotification(pProcInfo, &pMsg->taskStatus);
										break;
									}

										int ii = 0;

										//
										if(pMsg->taskStatus.iStatus==Consts.CONST_imTaskStatus_canceledBySender)
                                        {
											int jj = 0;
											int index_taskInfo = qyFuncs.getQmcTaskInfoIndexBySth(mainActivity.var_common.ctxCaller,pProcInfo, pMsg->taskStatus.iTaskId);
											if(index_taskInfo<0)
                                            {
												goto errLabel;
                                            }
											QMC_TASK_INFO pTaskInfo = qyFuncs.getQmcTaskInfoByIndex(mainActivity.var_common.ctxCaller,pProcInfo, index_taskInfo,"mainWnd_onqyPostComm");
											if (pTaskInfo == null) goto errLabel;
											QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
											if (pTaskData == null) goto errLabel;
											//
											if (pTaskData.msgU.uiType != Consts.CONST_misMsgType_task) goto errLabel;
											if(pTaskData.msgU.task.data.route.idInfo_from.ui64Id==pMisCnt.idInfo.ui64Id)
                                            {
												goto errLabel;
                                            }
											//
											do_closeTask1(pTaskInfo.var.iTaskId, true, "");
											//
											break;
                                        }
									

									qyFuncs.mymemset((IntPtr)(byte*)&addr_logicalPeer, 0, sizeof(MSGR_ADDR));
									//lstrcpyn(addr_logicalPeer.misServName, pMisCnt->cfg.misServName, mycountof(addr_logicalPeer.misServName));
									addr_logicalPeer.idInfo.ui64Id = pMsg->taskStatus.idInfo_logicalPeer.ui64Id;


										//
										bool bNeeded_applyForOrgReq = false;

										if (pMsg->taskStatus.iStatus == Consts.CONST_imTaskStatus_err_cantGet_index_activeMems_from)
										{
											bNeeded_applyForOrgReq = true;
										}
										else
										{

											if (pMsg->taskStatus.iStatus == Consts.CONST_imTaskStatus_err_missingOrgReq
												//|| 0==addr_logicalPeer.idInfo.ui64Id
												)
											{       //  
												/*
											qTraverse(&pMisCnt->talkingFriendQ, tmpHandler_findMissingOrgReq, 0, pMsg);

											//
											if (pMsg->taskStatus.ucbFound)
											{
												addr_logicalPeer.idInfo.ui64Id = pMsg->taskStatus.idInfo_logicalPeer.ui64Id;
											}
												*/
												for (i = 0; i < pProcInfo.cfg.usMaxCnt_taskInfos; i++)
												{
													if (tmpHandler_findMissingOrgReq(null, (IntPtr)pMsg, i) > 0)
													{
														//
														str = string.Format("err_missingOrgReq: taskInfo {0} found", i);
														qyFuncs.showInfo_open(0,null,str);
														//
														break;
													}
												}
												if (i == pProcInfo.cfg.usMaxCnt_taskInfos)
												{
													bNeeded_applyForOrgReq = true;

												}
											}
										}


									if ( bNeeded_applyForOrgReq  )
									{
										
										//
										//TCHAR tBuf[128];
										//
										TASK_PROC_REQ taskProcReq;
										int lenInBytes;
										qyFuncs.mymemset((IntPtr)(byte*)&taskProcReq, 0, sizeof(TASK_PROC_REQ));
										taskProcReq.uiType = Consts.CONST_imCommType_taskProcReq;
										taskProcReq.usOp = Consts.CONST_imOp_recv_applyForOrgReq;
										//  taskProcReq.tStartTime_org  =  0;
										taskProcReq.uiTranNo_org = pMsg->taskStatus.uiTranNo;
										//  taskProcReq.uiSerialNo_org  =  0;
										taskProcReq.uiContentType_org = pMsg->taskStatus.uiContentType;
										//	
										lenInBytes = sizeof(TASK_PROC_REQ);
											//				
											//				
											//				
											Int64 tStartTran;uint uiTranNo;	
										qyFuncs.MACRO_prepareForTran(out tStartTran,out uiTranNo);

											//  2017/10/11
											if (pMsg->taskStatus.iStatus == Consts.CONST_imTaskStatus_err_cantGet_index_activeMems_from)
											{
												str  =  _T("cantGet_index_activeMems_from. ");
											}
											else
											{
												str  =  _T("taskAvOrgReq not found. ");
											}
											//
											str += string.Format("send taskProcReq to {0}. tn {1}. kkkk", pMsg->taskStatus.idInfo_taskSender.ui64Id, uiTranNo);
								# if  DEBUG
										qyFuncs.traceLog(str);
								#endif
										qyFuncs.showInfo_open(0, null, str);

										//
										if (0!=qyFuncs.postMsgTask2Mgr_mc(mainActivity.var_common.ctxCaller, pMisCnt, Consts.CONST_misMsgType_task, 0, pMsg->taskStatus.cmdCode, tStartTran, uiTranNo, 0, 0, 0, (byte*)&taskProcReq, (uint)lenInBytes, &addr_logicalPeer.idInfo, null, null, &pMsg->taskStatus.idInfo_taskSender, 0, null, false)) goto errLabel;

										//  2017/10/03
										pProcInfo.status.dwTickCnt_sendTo_applyForOrgReq = qyFuncs.myGetTickCount(null);

									}
										
									


								}
								break;
									/*
															   case  CONST_misMsgType_refreshContactsStatus_qmc:
															   case  CONST_misMsgType_refreshMeStatus_qmc:
								{
																	 //  QY_WMBUF
																	 ::SendMessage(pMsg->refreshContactsStatus_qmc.hWnd, CONST_qyWm_comm, 0, (LPARAM)pMsg);
								}
								break;
															   case  CONST_misMsgType_getDaemonStatus:

																	 ::SendMessage(pMsg->getDaemonStatus.hWnd, CONST_qyWm_comm, 0, (LPARAM)pMsg);
								break;
									*/
										
								case  Consts.CONST_misMsgType_applyForPlayer_qmc:								
									  pProcInfo.doApplyForPlayer(hMainWnd, pMsg);										
									  break;
									/*

																	 //  2011/12/10
															   case  CONST_misMsgType_notifyTaskEnd_qmc:

																	 ::SendMessage(pMsg->notifyTaskEnd.hWnd, CONST_qyWm_comm, 0, (LPARAM)pMsg);
																	break;
																*/

								default:
									//traceLogA("CMainFrame::OnQyPostComm: msgArrive:  unprocessed: msgType: %d", pMsg->uiType);
									break;
							}
						}
					}
					break;

				case Consts.CONST_qyWmParam_task_end:
#if __DEBUG__
traceLog(_T("CMainFrame: task end, to tryToFreeSharedObjs"));
#endif
					qyFuncs.tryToFreeSharedObjs(pProcInfo);
					break;

				case Consts.CONST_qyWmParam_chkTask:
#if __DEBUG__
traceLog(_T("CMainFrame: to chk task"));
#endif
					qyFuncs.qmcChkTasks_gui(pProcInfo);
					break;

				case Consts.CONST_qyWmParam_toStartLocalAudioPlayer:      //  2013/05/26
#if __DEBUG__
traceLog(_T("MainFrm: get Msg toStartLocalAudioPlayer"));
#endif
					//startLocalAudioPlayer(pProcInfo);
					break;

				default:
#if __DEBUG__
							traceLog(_T("mainWnd_OnQyPostComm: unknown wParam"));
#endif
					break;
			}


			lRet = Consts.QY_RC_WMOK;
		errLabel:

			//
			if (bDbg)
			{
				qyFuncs.showInfo_open(0, null, "mainWnd_OnQyPostComm leaves");
				qyFuncs.showAllTc(mainActivity.var_common.ctxCaller,"mainWnd_OnQyPostComm leaves");
			}

			return lRet;
		}

		//
		public static unsafe int mainWnd_showStatus()
		{
			//static int stickCnt_last = 0;
			//DWORD dwTickCnt = myGetTickCount(null);
			//if  (  dwTickCnt  -  stickCnt_last  >  1000  )  
			{

				CCtxQyMc pQyMc = g.g_pQyMc;
				CCtxQmc pProcInfo = (CCtxQmc)pQyMc.get_pProcInfo();
				MIS_CNT pMisCnt = pProcInfo.pMisCnt;
				if (null==pMisCnt) return -1;

				//
				string str;

				//
				string tServ;
				fixed (byte* pIp = pMisCnt.server.ip) {
					tServ = qyFuncs.mytoString(pIp);
				}

				//
#if DEBUG

#endif

				//
				str = string.Format("FPS:{0:000.0} IO:{1,6:0.0},{2,6:0.0} t({3},{4,3}) a({5,5:0.0},{6,5:0.0} {7},{8}) v({9},{10} {11},{12}) f({13},{14} {15},{16}) CPU {17}% {18}. s({19})",
					pProcInfo.status.render.fps,
					pProcInfo.status.netStat.ins.uiInSpeedInKbps / 1000.0f, pProcInfo.status.netStat.ins.uiOutSpeedInKbps / 1000.0f,
					pProcInfo.av.talk.bChannelReady ? _T("  ") : _T("no"),
					pProcInfo.av.talk.iThreadsStatus,
					pProcInfo.status.netStat.uiInSpeedInKbps_a / 1000.0f, pProcInfo.status.netStat.uiOutSpeedInKbps_a / 1000.0f,
					pProcInfo.av.audio.bChannelReady ? _T("  ") : _T("no"),
					pProcInfo.av.audio.iThreadsStatus,
					pProcInfo.status.netStat.uiInSpeedInKbps_v / 1000.0f, pProcInfo.status.netStat.uiOutSpeedInKbps_v / 1000.0f,
					pProcInfo.av.video.bChannelReady ? _T("  ") : _T("no"),
					pProcInfo.av.video.iThreadsStatus,
					pProcInfo.status.netStat.uiInSpeedInKbps_f / 1000.0f, pProcInfo.status.netStat.uiOutSpeedInKbps_f / 1000.0f,
					pProcInfo.av.robot.bChannelReady ? _T("  ") : _T("no"),
					pProcInfo.av.robot.iThreadsStatus,
					pProcInfo.status.cpu.iCpuUsage,
					tServ,
					qyFuncs.showInfo_getQ2Nodes()
					) ;


				//
				qyFuncs.showStatus_open(0, null, str, 0);

				//		
				//stickCnt_last = dwTickCnt;
			}

			//
			return 0;
		}


		//
		public static unsafe int mainWnd_OnTimer(object hMainWnd, ref QY_MC_mainWndVar var, uint nIDEvent)
		{
			int iErr = -1;


			CCtxQyMc pQyMc = g.g_pQyMc;
			if (null==pQyMc) return -1;

			CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
			if (null==pProcInfo) return -1;
			if (pProcInfo.m_iCtxType != Consts.CONST_ctxType_qmc)
			{
				return -1;
			}
			//
			bool bDbg = false;
			string str;

			//
#if DEBUG
			//bDbg = true;
#endif
			//bDbg = true;

			//			
			var.loopCtrl ++;

			//
			if (bDbg)
			{
				qyFuncs.showInfo_open(0, null, "mainWnd_OnTimer enters");
				qyFuncs.showAllTc(var.ctxCaller, "mainWnd_OnTimer enters");
			}



			//
			/*
			if (pQyMc->bQuit)
			{       //  Èç¹û£¬ÒªÍË³öÁË£¬¾Í·¢¸ö¹Ø±ÕÏûÏ¢°É£®
				SendMessage(hMainWnd, WM_CLOSE, 0, 0);
				iErr = CONST_qyRet_quit; goto errLabel;
			}
			if (pQyMc->bGuiQuit)
			{   //  ÕâÀïÊÇ£¬Òª¿´ÓÐÃ»ÓÐ½çÃæÔªËØÐèÒªÇå³ý¡£ÒªÊÇÃ»ÓÐ£¬¾Í½«bQuitÉèÎªtrue

				pQyMc->usTimes_tryToQuit++;

				if (isIsCli(pQyMc))
				{

					//  
					stopAll_avRecord();
					stopAll_sharedObjs(pProcInfo);

					closeOtherPlayers(pProcInfo);

					if (pQyMc->usTimes_tryToQuit < 7)
					{

						//  avRecord
						if (!bNoSharedObjExists(pProcInfo))
						{
							OutputDebugString(_T("Shared Objects still exist.\n"));
							qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("Gui"), NULL, _T(""), _T(""), _T("SharedObjects still exits. %d times"), pQyMc->usTimes_tryToQuit);

							//  ÊÔÍ¼»ØÊÕ×ÊÔ´
							tryToFreeSharedObjs(pProcInfo);

							iErr = CONST_qyRet_quit; goto errLabel;
						}

					}

				}

				pQyMc->bQuit = TRUE;
				SendMessage(hMainWnd, WM_CLOSE, 0, 0);
				iErr = CONST_qyRet_quit; goto errLabel;
			}
			*/



			{
				//
				if (0==(var.loopCtrl % 5)) qyFuncs.bChkMessengerChannelsReady(pQyMc);


				if (null!=pProcInfo)
				{

					/*
					if (!(siCnt % pProcInfo->cfg.loopCtrl_chkPlayers)
						|| pProcInfo->av.bNeedChkPlayers)
					{
						pProcInfo->av.bNeedChkPlayers = FALSE;  //  2018/06/16
																//
						chkPlayers(pProcInfo);
					}
					//
					if (GetTickCount() - pProcInfo->status.notification.dwTickCnt_lastDisplayed > 900) displayNotification(NULL, NULL);
					*/
					//

					//
					if (0!=pProcInfo.waitToQuit.dwTickCnt_start)
					{
						if (qyFuncs.myGetTickCount(null) - pProcInfo.waitToQuit.dwTickCnt_start > pProcInfo.waitToQuit.dwTimeInMs)
						{
							qyFuncs.traceLog(_T("It's time to quit"));
							qyFuncs.notifyPanicToApp(pQyMc, -1, _T(""));
						}
					}



					//  2011/03/30
					mainWnd_chk_tasks(hMainWnd, ref var);

#if __isCli__
					//  2012/08/01

					//  2013/03/07
					if (!(siCnt % 5))
					{
						qisChkDb_gui_myDb();
						//  2014/12/22
						if (pProcInfo->status.sysErr.bFailed_newSharedObj)
						{
							pProcInfo->status.sysErr.bFailed_newSharedObj = FALSE;
							//
							showInfo_open(0, 0, _T("mainWnd_timer: bFailed_newSharedObj true. to chk sharedObj"));
							//  2009/12/28
							PostMessage(pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_task_end, 0);
						}
					}

					//  2013/08/07

					//  2013/08/01
					//   2017/09/13
					if (!(siCnt % 10))
					{
						chkSharedObjs(pProcInfo);
					}

#endif
					//
					MIS_CNT pMisCnt = pProcInfo.pMisCnt;
					str = null;
					MIS_CHANNEL channel = qyFuncs.getChannelByType(pMisCnt, Consts.CONST_channelType_talking);
					if ( !qyFuncs.bChannelOk(channel))
                    {
						str+=("t not ok");
                    }
					
					channel = qyFuncs.getChannelByType(pMisCnt, Consts.CONST_channelType_media);
                    if (!qyFuncs.bChannelOk(channel)){
						str+=(" v not ok");
                    }
					channel = qyFuncs.getChannelByType(pMisCnt, Consts.CONST_channelType_realTimeMedia);
					if (!qyFuncs.bChannelOk(channel))
					{
						str += (" a not ok");
					}
					if  (str != null)
                    {
						str = "channel " + str + " ";
                    }
					//
					str += var.memoryStatusStr;
					//
					if (str != null)
                    {
						//qyFuncs.showStatus_open(0, null, str, 1);
                    }

					//
#if false
					mySYSTEMTIME st;
					qyFuncs.myGetLocalTime(out st);
					str = string.Format("{0}-{1}-{2}-{3}-{4}-{5}-{6}", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
					qyFuncs.traceLog(str);
#endif

//
#if false
					str = string.Format("test: {0} times ", var.loopCtrl);
					qyFuncs.showInfo_open(0, _T(  "ontimer"  ), str);
#endif


				}

				//
				mainWnd_showStatus();

				//
#if DEBUG
				if ( pProcInfo.cfg.mSpecialDbg.bDoGC_mainWnd_OnTimer)
                {
					qyFuncs.showInfo_open(0, null, "for test, doGC");
					qyFuncs_Droid.doGC("mainWnd_OnTimer");
                }
#endif

			}

			iErr = 0;

		errLabel:

			//
			if (bDbg)
			{
				qyFuncs.showAllTc(var.ctxCaller,"mainWnd_OnTimer leaves");
				qyFuncs.showInfo_open(0, null, "mainWnd_OnTimer leaves");
			}

			//
			return iErr;
		}

		public static unsafe int displayNotification(CCtxQmc pProcInfo, MIS_MSG_taskStatus* pStatus)
		{
			int iErr = -1;
			//
			if (null==pProcInfo) return -1;

			//
			//pProcInfo->status.notification.dwTickCnt_lastDisplayed = GetTickCount();
			GuiShare.pf_gui_displayNotification(pProcInfo, (IntPtr)pStatus);


			iErr = 0;

		errLabel:

			return 0;   //  iErr;

		}

		//
		public static unsafe int qmcApplyForChkingTasks_gui(CCtxQyMc pQyMc)   //  2009/09/10
		{
#if DEBUG
			qyFuncs.traceLog(_T("qisApplyForChkingTasks_gui called"));
#endif

			if (null!=pQyMc)
			{
				GuiShare.pf_PostMessage(pQyMc.gui.hMainWnd, Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_chkTask, 0);
			}

			return 0;
		}


	}
}



