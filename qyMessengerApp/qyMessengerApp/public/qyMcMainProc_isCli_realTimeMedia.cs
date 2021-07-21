using System;
using System.Collections.Generic;
using System.Text;

namespace qy
{
    partial class qyFuncs
{


		//
		public static unsafe void mcThreadProc_mis_realTimeMedia(object lpParameter)
		{
			CCtxQyMc pQyMc = g.g_pQyMc;
			CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

			QY_Q2 pTriggerQ = pProcInfo.realTimeMediaQ2;
			uint uiChannelType = Consts.CONST_channelType_realTimeMedia;

			bool bDbg = false;
			string str;
			string where_showInfo = "audioMgr";

			//
			int loopCtrl = 0;
			int i;

			//uint dwThreadId = myGetCurrentThreadId();
			pProcInfo.dwThreadId_realTimeMedia = myGetCurrentThreadId();
			
			
			//
			using (CQyMalloc mallocObj = new CQyMalloc())
			{
				;
				MIS_MSGU* pMsg = null;
				uint len;
				uint dwRet;
				//  long								lPrev;
				//
				CTX_MC_thread ctx;
				using (CQyMalloc mallocObj_pMsgInputBuf = new CQyMalloc())
				{
					;
					using (CQyMalloc mallocObj_pMsgBuf = new CQyMalloc())
					{
						;
						//
						//  CWnd						*		pMainWnd						=	AfxGetApp(  )->m_pMainWnd;
						//
						//
						str=string.Format("mcThreadProc_mis_realTimeMedia:  enters");
						showInfo_open(0, where_showInfo, str);

						//memset(&ctx, 0, sizeof(ctx));
						ctx = new CTX_MC_thread();
						ctx.pProcessQ = pProcInfo.processQ_media;
						ctx.pMsgBuf_forInput = (MIS_MSGU*)mallocObj_pMsgInputBuf.mallocf(Consts.CONST_iAllocType_longTimeMsg, sizeof(MIS_MSGU));
						if (null == ctx.pMsgBuf_forInput) goto errLabel;
						ctx.pMsgBuf = (MIS_MSGU*)mallocObj_pMsgBuf.mallocf(Consts.CONST_iAllocType_longTimeMsg, sizeof(MIS_MSGU));
						if (null == ctx.pMsgBuf) goto errLabel;

						if (null == (pMsg = (MIS_MSGU*)mallocObj.mallocf(Consts.CONST_iAllocType_longTimeMsg, sizeof(MIS_MSGU)))) goto errLabel;

						for (; !pQyMc.bQuit; loopCtrl++)
						{

							//  if  (  !pMainWnd  )  pMainWnd					=	AfxGetApp(  )->m_pMainWnd;
							/*
							if (!pQyMc.gui.hMainWnd)
							{
								Sleep(1000); continue;
							}
							*/

							/*
							 * dwRet = WaitForSingleObject(pTriggerQ->hEvents[0], 5000);
							if (dwRet == WAIT_FAILED) goto errLabel;
							*/
							myWaitOne(pTriggerQ.hEvent0,5000);

							//
							for (; !pQyMc.bQuit;)
							{
								len = (uint)sizeof(MIS_MSGU);

								if (0!=q2GetMsg(pTriggerQ, (IntPtr)pMsg, &len)) break;

								mymemset((IntPtr)(((byte*)pMsg) + len), 0, (int)Math.Min(256, sizeof(MIS_MSGU) - len));

								switch (pMsg->uiType)
								{
									case Consts.CONST_misMsgType_input:
										{
											MIS_CNT pMisCnt = pProcInfo.pMisCnt;// (MIS_CNT*)pMsg->input.pMisCnt;
											MIS_CHANNEL pChannel = null;

											if (null==pMisCnt) break;
											//  if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  pMsg->input.uiChannelType  )  )  )  break;
											if (null==(pChannel = getChannelByType(pMisCnt, uiChannelType))) break;

											if (isUcFlgResp(pMsg->input.ucFlg))
											{
												if (0!=procMsgInput_other_resp(pQyMc, pProcInfo, &pMsg->input, len, ctx, pChannel))
												{
													//  traceLogA(  "mcThreadProc_mis_realTimeMedia: procMsgInput_other_resp failed."  );
												}
											}
											else
											{
												if (0!=procMsgInput_other_req(pQyMc, pProcInfo, &pMsg->input, len, ctx, pChannel))
												{
													//  traceLogA(  "mcThreadProc_mis_realTimeMedia: procMsgInput_other_req failed."  );
												}
											}

											//
										}
										break;
									case Consts.CONST_misMsgType_talk:
										traceLogA("mcThreadProc_mis_realTimeMedia: msg_talk ÔÝÊ±²»´¦Àí");
										break;
									case Consts.CONST_misMsgType_task:
										{
											MIS_CNT pMisCnt = pProcInfo.pMisCnt;// (MIS_CNT*)pMsg->task.pMisCnt;
											MIS_CHANNEL pChannel = null;

											if (null==pMisCnt) break;
											if (null==(pChannel = getChannelByType(pMisCnt, uiChannelType))) break;

											if (0!=procMsgTask_mc_media(pQyMc, pProcInfo, &pMsg->task, len, false, ref ctx, pChannel)) break;

											//  printMisMsg(  0,  0,  pMsg  );

										}
										break;
									case Consts.CONST_misMsgType_applyForChkChannels_qmc:
										{
											MIS_CNT pMisCnt = pProcInfo.pMisCnt;// (MIS_CNT*)pMsg->applyForChkChannels_qmc.pMisCnt;
											if (null==pMisCnt) break;

											traceLog(_T("rtMedia: applyForChkChannels"));
											startChannel(pProcInfo, pMisCnt, getChannelByType(pMisCnt, uiChannelType), _T("rtMedia: applyForChannels"));

										}
										break;

									case Consts.CONST_misMsgType_outputTask:
									/*
									{
									MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMsg->task.pMisCnt;
									MIS_CHANNEL				*		pChannel						=	null;

									if  (  !pMisCnt  )  break;
									if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  pMsg->task.uiChannelType  )  )  )  break;

									if  (  procMsgTask2Output_mc(  pQyMc,  pSci,  pProcInfo,  pMisCnt,  &pMsg->task,  len,  pChannel  )  )  break;
									}
									break;
									*/
									default:
										str=string.Format("mcThreadProc_mis_realTimeMedia failed, msgType {0}", pMsg->uiType);
										traceLog(str);
										break;
								}

								//  dwRet  =  WaitForSingleObject(  pTriggerQ->hSemaTrigger,  50  );
								//  if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;			   
							}


							if (0==(loopCtrl % 5))
							{

								//  for  (  i  =  0;  i  <  mycountof(  pProcInfo.misCnts  );  i  ++  )  
								//for (i = 0; i < pProcInfo.ucCnt_misCnts; i++)
								{
									MIS_CNT pMisCnt = pProcInfo.pMisCnt;// getMisCntByIndex(0, pProcInfo, i);  //&pProcInfo.misCnts[i]; 
									//if (!pMisCnt) continue;
									//
									//if (!pMisCnt->cfg.dynCfg.cnt.usCntPort) continue;

									waitForChannel(pProcInfo, pMisCnt, uiChannelType, false);
								}
							}
						}

					}
				}
			}

		errLabel:

			//for  (  i  =  0;  i  <  mycountof(  pProcInfo.misCnts  );  i  ++  )  
			//for (i = 0; i < pProcInfo.ucCnt_misCnts; i++)
			{
				MIS_CNT pMisCnt = pProcInfo.pMisCnt; // getMisCntByIndex(0, pProcInfo, i);  //&pProcInfo.misCnts[i]; 
				//if (!pMisCnt) continue;
				//
				//if (!pMisCnt->cfg.dynCfg.cnt.usCntPort) continue;

				waitForChannel(pProcInfo, pMisCnt, uiChannelType, true);
			}


			// 
			//  pProcInfo.processQ_media.emptyQ(  );

			pProcInfo.status.threadsStatus.ulbRealTimeMediaQuit = true;

			traceLogA("mcThreadProc_mis_realTimeMedia:  leaves");

			return ;
		}



	}
}
