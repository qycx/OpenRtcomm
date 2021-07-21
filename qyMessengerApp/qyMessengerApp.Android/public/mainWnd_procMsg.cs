using System;
using System.Collections.Generic;
using System.Text;

//
using qyMessengerApp.Droid;

//
namespace qy.Droid
{
    partial class qyFuncs_Droid
    {
        public static unsafe int msgInput2Task( MIS_MSG_INPUT * pInput, MIS_MSG_TASK  * pTask)
        {
            if (!qyFuncs.isUcFlgTalkData(pInput->ucFlg) && !qyFuncs.isUcFlgRouteTalkData(pInput->ucFlg)) return -1;

			pTask->uiType=Consts.CONST_misMsgType_task;
		
			//
			pTask->uiCliIndex=pInput->uiCliIndex;                           //  input daemon
														  //  2008/01/05, vDev_coms uiCliIndex
														  pTask->uiSessionId=pInput->uiSessionId;
			pTask->uiStep=pInput->uiStep;                                //  2008/04/28

			pTask->ucbConvrted=pInput->ucbConvrted;                      //  input 2007/7/14

			pTask->ucbConvrted_msgRoute=pInput->ucbConvrted_msgRoute;             //  daemon input 
		pTask->lenInBytes_msgRouteInDataBuf=pInput->lenInBytes_msgRouteInDataBuf;        //  daemon input data.route route data.buf
														   //  lenInBytes_msgRouteInDataBuf data.buf route

		//  mc MisCnt qmd uiCliIndex, 2007/06/10
		//void* pMisCnt;                          //  misCntµÄ, 2007/06/02
		pTask->addr_logicalPeer=pInput->addr_logicalPeer;                 //  messenger. 

		//
		pTask->ucFlg=pInput->ucFlg;
		//
		pTask->usCode=pInput->usCode;
		pTask->usCode_org=pInput->usCode_org;                          //  
		pTask->tStartTime=pInput->tStartTime;
		pTask->uiTranNo=pInput->uiTranNo;
		pTask->usSeqNo=pInput->usSeqNo;

		pTask->tStartTime_processed=pInput->tStartTime_processed;                //  iocp uiTranNo_mgr iocp
		pTask->uiTranNo_processed=pInput->uiTranNo_processed;
		pTask->nTimes_tryToSend=pInput->nTimes_tryToSend;                  //  mgr iocp 
													   //
		pTask->tTime_alive=pInput->tTime_alive;                     //  2014/12/09. 当没有找到新的视频数据时，刷新此变量，也可以表明任务是活跃的
													  //
		pTask->tTime_applyForChkTaskAlive=pInput->tTime_applyForChkTaskAlive;          //  2010/10/30
		pTask->nTimes_applyForChkTaskAlive=pInput->nTimes_applyForChkTaskAlive;      //  2014/12/09

		//
		pTask->uiTaskMode_unused=pInput->uiTaskMode_unused;                 //  2009/08/23

		//
		pTask->iTaskId=pInput->iTaskId;                            //  
		pTask->uiTaskType=pInput->uiTaskType;                            //  
		pTask->idInfo_taskSender=pInput->idInfo_taskSender;                  //  
		pTask->idInfo_taskReceiver=pInput->idInfo_taskReceiver;                //  
		pTask->iStatus=pInput->iStatus;                            //  2007/07/18
		pTask->tLastModifiedTime=pInput->tLastModifiedTime;                   //  2014/05/01

		//  
		pTask->tRecvTime=pInput->tRecvTime;                           //  
		pTask->dwTickCnt_start=pInput->dwTickCnt_start;                  //  ( ms ). 
		pTask->dwTickCnt_toSend=pInput->dwTickCnt_toSend;                 //  2011/01/22. start->toSendQ
													  //  
		pTask->usElapsed_recved=pInput->usElapsed_recved;                    //  
		pTask->usElapsed_serv_startToProcess=pInput->usElapsed_serv_startToProcess;       //  mtMgrThreadProc_is 
		pTask->index_debugInfo=pInput->index_debugInfo;                    //  debugInfo index, debugInfo 2008/11/19

		//
		pTask->uiChannelType=pInput->uiChannelType;                     //  2008/04/17, 
													   //
		pTask->uiChannelType_input=pInput->uiChannelType_input;               //  2017/10/03

		//
		pTask->lenInBytes=pInput->lenInBytes;
			//
			qyFuncs.mymemcpy((IntPtr)(byte*)&pTask->data, (IntPtr)(byte*)&pInput->data, pTask->lenInBytes);
	



            return 0;
        }


		//
		public static CTX_caller mainWnd_getCtxCaller(object hMainWnd)
        {
			MainActivity mainActivity = (MainActivity)hMainWnd;
			return mainActivity.var_common.ctxCaller;
        }


		//
        public static unsafe int mainWnd_procMsgInput_transferAvInfo(object hMainWnd, ref QY_MC_mainWndVar var, MIS_MSG_INPUT* pMsgInput)
        {
            int iErr = -1;

			//
			bool bDbg = false;
			string str;

			//
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
			MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;
            int i;
            int index_taskInfo = -1;

            IM_CONTENTU* pContent = qyFuncs.M_getMsgContent(pMsgInput->ucFlg, &pMsgInput->data);
            if (pContent->uiType != Consts.CONST_imCommType_transferAvInfo) goto errLabel;

            if (pMsgInput->iTaskId == 0)
            {
                qyFuncs.traceLog("mainWnd_procMsgInput failed, iTaskId is 0");
                goto errLabel;
            }

			//
			str = string.Format("mainWnd_procMsgInput_av enters: from {0}", pMsgInput->data.route.idInfo_from.ui64Id);
			qyFuncs.showInfo_open(0, null, str);


			//
			for (i = 0; i < pProcInfo.cfg.usMaxCnt_taskInfos; i++)
            {
                QMC_TASK_INFO e = pProcInfo.getQmcTaskInfoByIndex(mainActivity.var_common.ctxCaller, i,"mainWnd_procMsgInput_transferAvInfo");
                if (!e.bUsed) continue;
                //
                if (e.var.iTaskId == pMsgInput->iTaskId)
                {
                    {
                        break;
                    }
                }
            }
			//
			if (i < pProcInfo.cfg.usMaxCnt_taskInfos)
			{
				// skipped
				iErr = 0; goto errLabel;
			}

                
			index_taskInfo = qyFuncs.newTaskInfoIndex(mainActivity.var_common.ctxCaller,pProcInfo, Consts.CONST_taskDataType_conf, null, pMsgInput->iTaskId, "mainWnd_procMsgInput_transferAvInfo" );            
			if (index_taskInfo < 0)             
			{
                        qyFuncs.traceLog("mainWnd_procMsgInput_transferAvInfo failed: too many tasks");
                        goto errLabel;
                    
			}           
			//            
			QMC_TASK_INFO tts = pProcInfo.getQmcTaskInfoByIndex(mainActivity.var_common.ctxCaller,index_taskInfo,"mainWnd_procMsgInput_transferAvInfo");
			if (tts == null) goto errLabel;
			QMC_taskData_common pTaskData = tts.getTaskData();
			if (pTaskData == null) goto errLabel;
			fixed ( MIS_MSG_TASK * pMsgTask=&pTaskData.msgU.task )
            {
				msgInput2Task(pMsgInput, pMsgTask);
            }

			//
			GuiShare.pf_gui_procMsg((IntPtr)pMsgInput);
			
			

                //
                if (var.notifyTaskStatus.bExists_task && var.notifyTaskStatus.bAvCall)
                {
                    iErr = 0; goto errLabel;
                }
			var.notifyTaskStatus.bExists_task = true;
			var.notifyTaskStatus.bAvCall = true;
			var.notifyTaskStatus.index_taskInfo = index_taskInfo;

			//
			str = string.Format("mainWnd_procMsgInput_transferAvInfo: fill notifyTaskStatus, call gui_notify_chk");
			qyFuncs.showInfo_open(0, null, str);

			//
			GuiShare.pf_gui_notify_chk();
			
			
                iErr = 0;

            errLabel:

			//
			str = string.Format("mainWnd_procMsgInput_av leaves: from {0}", pMsgInput->data.route.idInfo_from.ui64Id);
			qyFuncs.showInfo_open(0, null, str);

			return iErr;

            }


		//
		public static unsafe int mainWnd_procMsgInput_transferAvReplyInfo(object hMainWnd, ref QY_MC_mainWndVar var, MIS_MSG_INPUT* pMsgInput)
		{
			int iErr = -1;

			//
			bool bDbg = false;
			string str;

			//
			CCtxQyMc pQyMc = g.g_pQyMc;
			CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
			MIS_CNT pMisCnt = pProcInfo.pMisCnt;
			//
			QM_dbFuncs g_dbFuncs = pQyMc.p_g_dbFuncs;
			//
			MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;
			int i;
			int index_taskInfo = -1;

			IM_CONTENTU* pContent = qyFuncs.M_getMsgContent(pMsgInput->ucFlg, &pMsgInput->data);
			if (pContent->uiType != Consts.CONST_imCommType_transferAvReplyInfo) goto errLabel;


			//
			str = string.Format("mainWnd_procMsgInput_avReply enters: from {0}", pMsgInput->data.route.idInfo_from.ui64Id);
			qyFuncs.showInfo_open(0, null, str);

			//
			object pDb = null;
			using (CQnmDb db = new CQnmDb())
			{

				ushort usRespCode = Consts.CONST_qyRc_unknown;

				//if (null == pCtx.pProcessQ) goto errLabel;

				if (null == db.getAvailableDb(pQyMc.iDsnIndex_mainSys)) goto errLabel;
				pDb = db.m_pDbMem.pDb;

				QY_MESSENGER_ID idInfo = pMisCnt.idInfo;
				if (!g_dbFuncs.pf_bGetImTaskRcdBySth(pDb, pQyMc.cfg.db.iDbType, false, "", &idInfo, (Int64)pContent->transferAvReplyInfo.tStartTime_org, pContent->transferAvReplyInfo.uiTranNo_org, 0, null))
				{
#if __DEBUG__
										traceLogA("procMsgTask_mc_media failed: bGetImTaskRcdBySth returns false");
#endif
					goto errLabel;
				}

				//
				//  printQ_mis(  &pCtx.pProcessQ.m_q,  0  );
				//
				qyFuncs.printMisMsg(null, null, (MIS_MSGU*)pMsgInput);

				//  
				if (pProcInfo.processQ_media.qTraverse_mono(null, qyFuncs.tmpHandler_findOrgMsgAndProc_is, (IntPtr)pMsgInput, (IntPtr)0) <= 0)
				{
					qyFuncs.traceLogA("procMsgTask_mc_media failed: ");
					//qyShowInfo1(Consts.CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, NULL, (""), (""), ("%s err: "), qyGetDesByType1(getResTable(0, &pQyMc->cusRes, Consts.CONST_resId_qyCommTypeTable), pContent->uiType));
					//
					//  postMsg2Mgr...
					goto errLabel;
				}

				//
				qyFuncs.chkTransformThreads(pProcInfo, pMsgInput->iTaskId);

			}



			//
			iErr = 0;
		errLabel:
			return iErr;

		}


			//
			public static unsafe int mainWnd_chk_tasks(object hMainWnd, ref QY_MC_mainWndVar var)
        {
            int iErr = -1;
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
			MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;
			//
            uint uiTickCnt_now = qyFuncs.myGetTickCount(null);
            QMC_TASK_INFO pTaskInfo = null;
            int i;
			int iElapseInMs = 0;

			bool bDbg = false;
#if DEBUG
			//bDbg = true;
#endif
			//bDbg = true;


			//
			if (bDbg)
			{
				qyFuncs.showInfo_open(0, null, "mainWnd_chk_tasks enters");
				qyFuncs.showAllTc(mainActivity.var_common.ctxCaller, "mainWnd_chk_tasks enters");
			}

            //
            if (0==(var.loopCtrl % 10))
            {
                for ( i = 0;i < pProcInfo.cfg.usMaxCnt_taskInfos;i ++)
                {
                    pTaskInfo = pProcInfo.getQmcTaskInfoByIndex(mainActivity.var_common.ctxCaller,i,"mainWnd_chk_tasks");
                    if (!pTaskInfo.bUsed) continue;
					QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
					if (pTaskData == null) continue;
					//
                    fixed( MIS_MSG_TASK * pMsgTask=&pTaskData.msgU.task )
                    {
						if (pMsgTask->uiType != Consts.CONST_misMsgType_task)
						{
							continue;
						}

						//if (qyFuncs.bTaskAlive(pMsgTask->iStatus)) continue;
						if (qyFuncs.qmcTaskInfo_bAlive(mainActivity.var_common.ctxCaller,pProcInfo, i)) continue;
                        
						//						
						iElapseInMs = Math.Abs((int)(uiTickCnt_now-pTaskInfo.var.dwTickCnt_lastRefreshed));
						if ( iElapseInMs>pProcInfo.cfg.usTimeoutInMs_waitIfNoData)
                        {
							qyFuncs.freeTaskInfo(ref mainActivity.var_common.ctxCaller,pProcInfo, i, "mainWnd_chk_tasks");
                        }
                    }

                }
            }
                
            //
            if (var.notifyTaskStatus.bExists_task && var.notifyTaskStatus.bAvCall)
                {


                    pTaskInfo = pProcInfo.getQmcTaskInfoByIndex(var.ctxCaller,var.notifyTaskStatus.index_taskInfo,"mainWnd_chk_tasks");
				if (pTaskInfo == null
				|| !qyFuncs.qmcTaskInfo_bAlive(var.ctxCaller, pProcInfo,var.notifyTaskStatus.index_taskInfo))
				{
					var.notifyTaskStatus.bExists_task = false;
					GuiShare.pf_gui_notify_cancel();
				}
				else
				{
					if (var.processingAvTask.bTaskExists
					&& var.processingAvTask.index_taskInfo == var.notifyTaskStatus.index_taskInfo
					)
					{
						iErr = 0; goto errLabel;
					}

					//
					iElapseInMs = Math.Abs((int)(uiTickCnt_now - pTaskInfo.var.dwTickCnt_start));
					if (iElapseInMs < pProcInfo.cfg.usTimeoutInMs_waitForProcessingOf_avTask)
					{
						iErr = 0; goto errLabel;
					}

					qyFuncs.traceLog("mainWnd_chk_tasks: timeout, to cancel task");

					// to cancel task
					do_cancelTask1(pTaskInfo.var.iTaskId, true, "timeout");

					//
					var.notifyTaskStatus.bExists_task = false;
					GuiShare.pf_gui_notify_cancel();
				}
            }

                //
                for ( i=0; i < pProcInfo.cfg.usMaxCnt_taskInfos;i++)
            {
                pTaskInfo = pProcInfo.getQmcTaskInfoByIndex(mainActivity.var_common.ctxCaller,i,"mainWnd_chk_tasks");
                if (!pTaskInfo.bUsed) continue;
				QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
				if (pTaskData == null) continue;

				//
				if (!qyFuncs.qmcTaskInfo_bAlive(mainActivity.var_common.ctxCaller,pProcInfo, i)) continue;

				//
				fixed (MIS_MSG_TASK* pMsgTask = &pTaskData.msgU.task) {
					if(pMsgTask->uiType!=Consts.CONST_misMsgType_task)
                    {
						continue;
                    }
					//
                        //
                        IM_CONTENTU* pContent = qyFuncs.M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
                        if (null == pContent) goto errLabel;
						//
                        if ( pContent->uiType == Consts.CONST_imCommType_transferAvInfo )
                        {
                            //
                            var.notifyTaskStatus.index_taskInfo = i;
                            var.notifyTaskStatus.bExists_task = true;
                            var.notifyTaskStatus.bAvCall = true;

							//
							GuiShare.pf_gui_notify_chk();

                            iErr = 0; goto errLabel;                                
                            break;
                        }
					// 对其他任务，等待60秒后暂时都作废
					iElapseInMs = Math.Abs((int)(uiTickCnt_now - pTaskInfo.var.dwTickCnt_lastRefreshed));
					if ( iElapseInMs>pProcInfo.cfg.usTimeoutInMs_waitForProcessingOf_otherTask)
                    {
						do_cancelTask1(pTaskInfo.var.iTaskId, true, "timeout for nonAvTask");
						continue;
                    }

                
				}
				continue;
            }

                //
                if ( var.notifyTaskStatus.bExists_task)
            {
                GuiShare.pf_gui_notify_cancel();
                var.notifyTaskStatus.bExists_task = false;

            }
            

                iErr = 0;
		errLabel:

			//
			if (bDbg)
			{
				qyFuncs.showAllTc(mainActivity.var_common.ctxCaller,"mainWnd_chk_tasks leaves");
				qyFuncs.showInfo_open(0, null, "mainWnd_chk_tasks leaves");
			}

			//              
			return iErr;

            
            }

		//
		public static unsafe int do_cancelTask1(int iTaskId, bool bAutoCancel, string hint)
		{

			int iErr = -1;
			bool bDbg = false;
			string str;

#if DEBUG
			bDbg = true;
#endif
			//
			if (bDbg)
            {
				qyFuncs.showInfo_open(0, null, "do_canncelTask1 enters");
            }

			//
			//
			CCtxQyMc pQyMc = g.g_pQyMc;
			CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
			MIS_CNT pMisCnt = pProcInfo.pMisCnt;
			MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;
			//TCHAR tBuf[256] = _T("");
			//char buf[256] = "";
			CQyMalloc mallocObj;

			//if (!hDlg || !pParam || !pMsgElem) return -1;
			QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;
			if (null==pDbFuncs) goto errLabel;
			QM_dbFuncs  g_dbFuncs = pDbFuncs;

            Int64 tStartTran; uint uiTranNo;

			int index_taskInfo = qyFuncs.getQmcTaskInfoIndexBySth(mainActivity.var_common.ctxCaller,pProcInfo, iTaskId);
			if (index_taskInfo < 0) return -1;

			//
			QMC_TASK_INFO pTaskInfo = pProcInfo.getQmcTaskInfoByIndex(mainActivity.var_common.ctxCaller,index_taskInfo,"do_cancelTask");
			if (pTaskInfo == null) return -1;

			//
			if (!pTaskInfo.bUsed) return 0;

            //
            if (bDbg)
            {
				str = string.Format("do_cancelTask, index_taskInfo {0}. {1}", index_taskInfo,hint );
				qyFuncs.traceLog(str);
            }

			//
			QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
			if (pTaskData == null) goto errLabel;

			//
			fixed (MIS_MSG_TASK* pMsg = &pTaskData.msgU.task) {
				if (pMsg->uiType != Consts.CONST_misMsgType_task)
				{
					goto errLabel;
				}

					IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->data.buf;
					int iStatus;
					int lenInBytes;


					object pDb = null;
					using (CQnmDb db = new CQnmDb()) {
						if (null==db.getAvailableDb(pQyMc.iDsnIndex_mainSys)) goto errLabel;
						pDb = db.m_pDbMem.pDb;

						switch (pContent->uiType)
						{
							case Consts.CONST_imCommType_transferAvInfo:
							case Consts.CONST_imCommType_transferFileReq:
								switch (pMsg->iStatus)
								{
									case Consts.CONST_imTaskStatus_req:
									case Consts.CONST_imTaskStatus_applyToSend:
									case Consts.CONST_imTaskStatus_waitToSend:
									case Consts.CONST_imTaskStatus_acceptedByReceiver:
									case Consts.CONST_imTaskStatus_dualByReceiver:
										{


											iStatus = Consts.CONST_imTaskStatus_canceledBySender;
											g_dbFuncs.pf_updateTaskStatus(pDb, iStatus, pMsg->iTaskId);
											pMsg->iStatus = iStatus;        //  2012/05/15

											//  °ÑÏÔÊ¾×´Ì¬ÐÞ¸ÄÏÂ.2008/11/14
											//showTaskStatus(pMisCnt, &pMgrVar->addr.idInfo, &pMsg->idInfo_taskSender, &pMsg->idInfo_taskReceiver, FALSE, pContent->uiType, pMsg->iTaskId, iStatus, 0, 0, _T(""), _T(""));

											//  Í¨Öª¶Ô·½
											TASK_PROC_REQ taskProcReq;
											qyFuncs.mymemset((IntPtr)(byte*)&taskProcReq, 0, sizeof(TASK_PROC_REQ));
											taskProcReq.uiType = Consts.CONST_imCommType_taskProcReq;
											taskProcReq.usOp = Consts.CONST_imOp_send_cancel;
											taskProcReq.tStartTime_org = pMsg->tStartTime;
											taskProcReq.uiTranNo_org = pMsg->uiTranNo;
											taskProcReq.uiContentType_org = pContent->uiType;
											//
											lenInBytes = sizeof(TASK_PROC_REQ);
											//					  
											qyFuncs.MACRO_prepareForTran( out tStartTran,out uiTranNo);
											//  2015/09/08
											uint uiChannelType = pMsg->uiChannelType;
											//
											uiChannelType = 0;
											//
											if (0!=qyFuncs.postMsgTask2Mgr_mc(mainActivity.var_common.ctxCaller,pMisCnt, Consts.CONST_misMsgType_task, 0, pMsg->usCode, tStartTran, uiTranNo, 0, pMsg->iTaskId, pMsg->uiTaskType, (byte*)&taskProcReq, (uint)lenInBytes, &pMsg->addr_logicalPeer.idInfo, &pMsg->idInfo_taskSender, &pMsg->idInfo_taskReceiver, &pMsg->idInfo_taskReceiver, uiChannelType, null, false)) goto errLabel;
										}
										break;
									case Consts.CONST_imTaskStatus_resp:
									case Consts.CONST_imTaskStatus_applyToRecv:
									case Consts.CONST_imTaskStatus_waitToRecv:
										{


											iStatus = bAutoCancel ? Consts.CONST_imTaskStatus_autoCanceledByReceiver : Consts.CONST_imTaskStatus_canceledByReceiver;
											g_dbFuncs.pf_updateTaskStatus(pDb, iStatus, pMsg->iTaskId);
											pMsg->iStatus = iStatus;        //  2012/05/15

											//  °ÑÏÔÊ¾×´Ì¬ÐÞ¸ÄÏÂ.2008/11/14
											//showTaskStatus(pMisCnt, &pMgrVar->addr.idInfo, &pMsg->idInfo_taskSender, &pMsg->idInfo_taskReceiver, FALSE, pContent->uiType, pMsg->iTaskId, iStatus, 0, 0, _T(""), _T(""));

											//  Í¨Öª¶Ô·½
											TASK_PROC_REQ taskProcReq;
											qyFuncs.mymemset((IntPtr)(byte*)&taskProcReq, 0, sizeof(TASK_PROC_REQ));
											taskProcReq.uiType = Consts.CONST_imCommType_taskProcReq;
											taskProcReq.usOp = Consts.CONST_imOp_recv_cancel;
											taskProcReq.tStartTime_org = pMsg->tStartTime;
											taskProcReq.uiTranNo_org = pMsg->uiTranNo;
											taskProcReq.uiContentType_org = pContent->uiType;
											//
											lenInBytes = sizeof(TASK_PROC_REQ);
											//					  
											qyFuncs.MACRO_prepareForTran(out tStartTran,out uiTranNo);
											//  2015/09/08
											uint uiChannelType = pMsg->uiChannelType;
											//
											uiChannelType = 0;
											//	
											if (0!=qyFuncs.postMsgTask2Mgr_mc(mainActivity.var_common.ctxCaller,pMisCnt, Consts.CONST_misMsgType_task, 0, pMsg->usCode, tStartTran, uiTranNo, 0, pMsg->iTaskId, 0, (byte*)&taskProcReq, (uint)lenInBytes, &pMsg->addr_logicalPeer.idInfo, &pMsg->idInfo_taskSender, &pMsg->idInfo_taskReceiver, &pMsg->idInfo_taskSender, uiChannelType, null, false)) goto errLabel;
										}
										break;
									default:
										break;
								}
								break;
							default:
								break;
						}
					}


			}
			//
			pTaskInfo.var.dwTickCnt_lastRefreshed = qyFuncs.myGetTickCount(null);

			iErr = 0;

		errLabel:

			if (bDbg)
			{
				qyFuncs.showInfo_open(0, null, "do_canncelTask1 leaves");
			}

			//
			return iErr;
		}


		public static unsafe int do_closeTask1(int iTaskId, bool bAutoCancel, string hint)
		{

			int iErr = -1;
			bool bDbg = false;
			string str;

#if DEBUG
			bDbg = true;
#endif

			//
			//
			CCtxQyMc pQyMc = g.g_pQyMc;
			CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
			MIS_CNT pMisCnt = pProcInfo.pMisCnt;
			MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;
			//TCHAR tBuf[256] = _T("");
			//char buf[256] = "";
			CQyMalloc mallocObj;

			//if (!hDlg || !pParam || !pMsgElem) return -1;
			QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;
			if (null == pDbFuncs) goto errLabel;
			QM_dbFuncs g_dbFuncs = pDbFuncs;

			Int64 tStartTran; uint uiTranNo;

			int index_taskInfo = qyFuncs.getQmcTaskInfoIndexBySth(mainActivity.var_common.ctxCaller, pProcInfo, iTaskId);
			if (index_taskInfo < 0) return -1;

			QMC_TASK_INFO pTaskInfo = pProcInfo.getQmcTaskInfoByIndex(mainActivity.var_common.ctxCaller,index_taskInfo,"do_closeTask");
			if (pTaskInfo == null) return -1;

			//
			if (!pTaskInfo.bUsed) return 0;

			//
			str = string.Format("qyFuncs_Droid.do_closeTask enters, index_taskInfo {0}. {1}", index_taskInfo, hint);
			qyFuncs.showInfo_open(0,null,str);

			//
			QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
			if (pTaskData == null) goto errLabel;

			//
			fixed (MIS_MSG_TASK* pMsg = &pTaskData.msgU.task)
			{
				if (pMsg->uiType != Consts.CONST_misMsgType_task)
				{
					goto errLabel;
				}

				IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->data.buf;
				int iStatus;
				int lenInBytes;


				object pDb = null;
				using (CQnmDb db = new CQnmDb())
				{
					if (null == db.getAvailableDb(pQyMc.iDsnIndex_mainSys)) goto errLabel;
					pDb = db.m_pDbMem.pDb;

					switch (pContent->uiType)
					{
						case Consts.CONST_imCommType_transferAvInfo:
						case Consts.CONST_imCommType_transferFileReq:
							switch (pMsg->iStatus)
							{
								case Consts.CONST_imTaskStatus_req:
								case Consts.CONST_imTaskStatus_applyToSend:
								case Consts.CONST_imTaskStatus_waitToSend:
								case Consts.CONST_imTaskStatus_acceptedByReceiver:
								case Consts.CONST_imTaskStatus_dualByReceiver:
									{


										iStatus = Consts.CONST_imTaskStatus_canceledBySender;
										g_dbFuncs.pf_updateTaskStatus(pDb, iStatus, pMsg->iTaskId);
										pMsg->iStatus = iStatus;        //  2012/05/15

										//  °ÑÏÔÊ¾×´Ì¬ÐÞ¸ÄÏÂ.2008/11/14
										//showTaskStatus(pMisCnt, &pMgrVar->addr.idInfo, &pMsg->idInfo_taskSender, &pMsg->idInfo_taskReceiver, FALSE, pContent->uiType, pMsg->iTaskId, iStatus, 0, 0, _T(""), _T(""));

									}
									break;
								case Consts.CONST_imTaskStatus_resp:
								case Consts.CONST_imTaskStatus_applyToRecv:
								case Consts.CONST_imTaskStatus_waitToRecv:
									{


										iStatus = bAutoCancel ? Consts.CONST_imTaskStatus_autoCanceledByReceiver : Consts.CONST_imTaskStatus_canceledByReceiver;
										g_dbFuncs.pf_updateTaskStatus(pDb, iStatus, pMsg->iTaskId);
										pMsg->iStatus = iStatus;        //  2012/05/15

										//  °ÑÏÔÊ¾×´Ì¬ÐÞ¸ÄÏÂ.2008/11/14
										//showTaskStatus(pMisCnt, &pMgrVar->addr.idInfo, &pMsg->idInfo_taskSender, &pMsg->idInfo_taskReceiver, FALSE, pContent->uiType, pMsg->iTaskId, iStatus, 0, 0, _T(""), _T(""));

									}
									break;
								default:
									break;
							}
							break;
						default:
							break;
					}
				}

				//
				object hTalk=null;
				if (0 == findTalker(pQyMc, pMisCnt, pMsg->addr_logicalPeer.idInfo, ref hTalk)) {
					Activity_dlgTalk dlgTalk = (Activity_dlgTalk)hTalk;
					dlgTalk.do_closeTask(index_taskInfo);
				}
				else
                {
					//
					mainWnd_do_closeTask(index_taskInfo);
                }
			}
			//
			pTaskInfo.var.dwTickCnt_lastRefreshed = qyFuncs.myGetTickCount(null);

			iErr = 0;

		errLabel:

			//
			str = string.Format("qyFuncs_Droid.do_closeTask leaves");
			qyFuncs.showInfo_open(0,null,str);

			//
			return iErr;
		}



		//
		public static unsafe int mainWnd_do_closeTask(int index_taskInfo)
        {
			int iErr = -1;
			CCtxQyMc pQyMc = g.g_pQyMc;
			CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
			MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;

			QMC_TASK_INFO pTaskInfo = qyFuncs.getQmcTaskInfoByIndex(mainActivity.var_common.ctxCaller,pProcInfo, index_taskInfo,"mainWnd_do_closeTask");
			if (pTaskInfo == null) return -1;

			qyFuncs.removeTask(mainActivity.var_common.ctxCaller,pTaskInfo.var.iTaskId);
			qyFuncs.qmcTaskInfo_setClosed(mainActivity.var_common.ctxCaller,pProcInfo, index_taskInfo,"mainWnd_do_closeTask");

			iErr = 0;
		errLabel:
			return iErr;

        }




		//
		public static unsafe int mainWnd_procTask(int index_taskInfo, ushort usOp)
        {
			int iErr = -1;


			iErr = 0;
		errLabel:
			return iErr;

        }



	}
}

