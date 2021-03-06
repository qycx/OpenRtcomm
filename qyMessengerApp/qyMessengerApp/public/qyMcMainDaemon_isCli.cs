using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

partial class Consts
{
	public const int bufSize_1024 = 1024;
	public const int bufSize_2048 = 2048;
	public const int bufSize_4096 = 4096;
}


namespace qy
{
	public unsafe struct TMP_timeBuf
	{
		public fixed byte timeBuf[Consts.CONST_qyTimeLen + 1];
	};

	partial class qyFuncs
	{
		public unsafe struct RESULT_startChannel
		{
			public fixed char respHint[Consts.cntof_hint];
		}

		public unsafe struct TMP_buf1024
        {
			public fixed byte buf[Consts.bufSize_1024];
        }
		public unsafe struct TMP_buf2048
        {
			public fixed byte buf[Consts.bufSize_2048];

        }
		public unsafe struct TMP_buf4096
		{
			public fixed byte buf[Consts.bufSize_4096];
		}


		/// <summary>
		/// ///////////////////////////
		/// </summary>
		/// <param name="pMisCnt"></param>
		/// <param name="pChannel"></param>
		/// <param name="result"></param>
		/// <returns></returns>
		/// 
		public static unsafe int updateMeDisplayInfo(CCtxQmc pProcInfo, MIS_CNT pMisCnt, QY_MESSENGER_REGINFO* pRegInfo, string talkerDesc, string displayName)
		{
			int iErr = -1;
			
			MIS_MSG_REFRESHMESTATUS_QMC msg;
			int len;
			string str;

			fixed (char* pTalkerDesc = pMisCnt.talkerDesc.talkerDesc)
			{
				fixed (char* pDisplayName = pMisCnt.displayName.displayName)
				{
					fixed (char* pDisplayNameWithIdInfo = pMisCnt.displayName_withIdInfo.displayName) {

						//
						if (null != pRegInfo && pRegInfo->addr.idInfo.ui64Id == pMisCnt.idInfo.ui64Id)
						{
							//
							MY_REG_DESC desc;

							//  2010/04/16
							if (0 != regInfo2Desc(null, pRegInfo, out desc, pTalkerDesc, Consts.cntof_talkerDesc, pDisplayName, Consts.cntof_displayName)) goto errLabel;

							//

							//_sntprintf(pMisCnt->displayName_withIdInfo, mycountof(pMisCnt->displayName_withIdInfo), _T("%s %I64u"), pMisCnt->displayName, pMisCnt->idInfo.ui64Id);

							str = string.Format("{0} {1}", new string(pDisplayName), pMisCnt.idInfo.ui64Id);
								mytcsncpy(pDisplayNameWithIdInfo, str, Consts.cntof_displayName);



							


							//  2016/04/06
						}
						else if (null != talkerDesc && null != displayName)
						{
							mylstrcpyn(pTalkerDesc, talkerDesc, Consts.cntof_talkerDesc);
							mylstrcpyn(pDisplayName, displayName, Consts.cntof_displayName);

							//  2016/04/06
							safeTcsnCpy(pDisplayName, pDisplayNameWithIdInfo, Consts.cntof_displayName);
						}

						//
						mymemset((IntPtr)(byte*)&msg, 0, sizeof(MIS_MSG_REFRESHMESTATUS_QMC));
						msg.uiType = Consts.CONST_misMsgType_refreshMeStatus_qmc;
						//msg.pMisCnt = pMisCnt;
						//			 
						len = sizeof(MIS_MSG_REFRESHMESTATUS_QMC);
						//
						if (0!=qPostMsgAndTrigger((IntPtr)(byte*)&msg, (uint)len, pProcInfo.displayQ))
						{
#if __DEBUG__
				traceLogA("qPostMsgAndTrigger failed");
#endif
							goto errLabel;
						}
					}
				}
			}

			iErr = 0;

		errLabel:

			return iErr;

		}




		//
		public static unsafe int tryToStartChannel(MIS_CNT pMisCnt, MIS_CHANNEL pChannel, ref RESULT_startChannel result)
		{
			int iErr = -1;


			if (null == pMisCnt) return -1;
			CCtxQmc pProcInfo = (CCtxQmc)pMisCnt.pProcInfoParam;
			if (null == pProcInfo) return -1;
			CCtxQyMc pQyMc = pProcInfo.pQyMc;

			//
			//QM_dbFuncs* p_g_dbFuncs = pQyMc.p_g_dbFuncs;


			//
			//char buf[4096];
			TMP_buf4096 buf4096;
			uint len;
			using (CQyMalloc mallocObj = new CQyMalloc())
			{
				QY_BUF buf_help;
				byte* pbuf_help = (byte*)&buf_help;
				mymemset((IntPtr)pbuf_help, 0, sizeof(QY_BUF));
				buf_help.len = Consts.bufSize_4096;
				if (null == (buf_help.data = (byte*)mallocObj.mallocf((int)buf_help.len))) return -1;


				byte* ptr;
				AUTH_RESP_MIS authResp;
				QY_MESSENGER_ID idInfo;
				QY_MESSENGER_INFO obj;


				if (pChannel.bSessionOpen) return 0;   //  

				QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;
				if (null == pDbFuncs) goto errLabel;
				QM_dbFuncs g_dbFuncs = pDbFuncs;

				//
				pChannel.status.ulbNeedVerified = false;
				pChannel.status.ulbAuthed = false;

				//  ´ò¿ªÁ¬½Ó						   	 
				len = Consts.bufSize_4096;  // sizeof(buf);
				string str_servIp;
				fixed (byte* p = pMisCnt.server.ip)
				{
					str_servIp = mytoString(p);
				}
				if (0 != qnmOpenSession_mis(str_servIp, pMisCnt.server.port, ref pProcInfo.authInfo, 0, pChannel.uiType, null, pQyMc.iServiceId, qnmVerStr(pQyMc.iServiceId), ref pChannel.commEncCtx, ref pChannel.session, ref pChannel.sock, pQyMc.cfg.to, (byte*)buf4096.buf, &len)) goto errLabel;
				pChannel.bSessionOpen = true;

				if (0 != decryptData(ref pChannel.commEncCtx, ref buf_help, buf4096.buf, &len)) goto errLabel;

				byte* pauthResp = (byte*)&authResp;
				mymemset((IntPtr)pauthResp, 0, sizeof(AUTH_RESP_MIS));
				ptr = buf4096.buf;
				if (0 != stream2Data(&ptr, &len, filterStream_is, tmpHandler_stream2AuthResp_mis, null, &authResp)) goto errLabel;
				if (!isRcOk(pChannel.session.usLastRespCode_i))
				{
					if (pChannel.uiType == Consts.CONST_channelType_talking)
					{
						//  2011/08/15
						fixed (char* respHint = result.respHint)
						{
							safeWcsnCpy(authResp.wBuf_hint, respHint, Consts.cntof_hint);
						}
						//
						if (pChannel.session.usLastRespCode_i == Consts.CONST_qyRc_anotherLogonExists)
						{
							if (pQyMc.bLogon)
							{
								showNotification(pMisCnt, null, null, 0, 0, 0, (getResStr(0, pQyMc.cusRes, (int)enumRes.CONST_resId_anotherLogon)) + new string(authResp.wBuf_hint));
								waitToQuit_isCli(pProcInfo, 5000);
							}
							goto errLabel;
						}
					}
					if (!isRcNeedVerified(pChannel.session.usLastRespCode_i))
					{
						//traceLogA("tryToStartChannel failed: access denied");
						goto errLabel;
					}
					//traceLogA("get hint from server: [%S]", authResp.wBuf_hint);
					pChannel.status.ulbNeedVerified = true;
				}
				if (isRcOk(pChannel.session.usLastRespCode_i)) pChannel.status.ulbAuthed = true;

				if (!pChannel.status.ulbAuthed)
				{
					//traceLogA("ulbAuthed is false"); 
					goto errLabel;
				}
				if (!bMessengerIdValid(&authResp.idInfo)) goto errLabel;

				idInfo.ui64Id = authResp.idInfo.ui64Id;

				string str;
				{
					//_sntprintf(pProcInfo.who_showInfo, mycountof(pProcInfo.who_showInfo), _T("%s%I64u"), pQyMc.who_showInfo, idInfo.ui64Id);
					str = string.Format("{0} {1} ", "phone", idInfo.ui64Id);
					pProcInfo.str_who_showInfo = str;
					set_who_showInfo(pProcInfo.str_who_showInfo);
				}
				str= string.Format("tryTostartChannel, getIdInfo {0} ", idInfo.ui64Id);
#if DEBUG
				traceLog(str);
#endif

				//
				if (pChannel.uiType != Consts.CONST_channelType_talking)
				{   //  2008/03/17, 
					iErr = 0; goto errLabel;
				}

				//  2011/02/02
				if (0 != authResp.uiLogonId)
				{
					if (pProcInfo.authInfo.uiLogonId != authResp.uiLogonId)
					{
						pProcInfo.authInfo.uiLogonId = authResp.uiLogonId;
					}
				}
				//
				if (0 != authResp.usAppAvLevel_daemon)
				{
					if (pQyMc.usAppAvLevel_daemon != authResp.usAppAvLevel_daemon)
					{
						pQyMc.usAppAvLevel_daemon = authResp.usAppAvLevel_daemon;  //  2011/10/22
					}
				}
				//  2009/10/11
				if (pQyMc.ucbDaemonDemo != authResp.ucbDaemonDemo)
				{
					pQyMc.ucbDaemonDemo = authResp.ucbDaemonDemo;
				}
				//		
				//  2017/06/21
				if (pQyMc.usSubSystemId_daemon != authResp.usSubSystemId_daemon)
				{
					pQyMc.usSubSystemId_daemon = authResp.usSubSystemId_daemon;
				}

				//  2016/08/10
				if (pChannel.uiType == Consts.CONST_channelType_talking)
				{
					//safeWcsnCpy(authResp.clientWelcomeMsg, pProcInfo.cfg.clientWelcomeMsg, mycountof(pProcInfo.cfg.clientWelcomeMsg));
				}

				//
				if (!pQyMc.bLogon)
				{       //  2010/03/10
					iErr = 0; goto errLabel;
				}

				using (CQnmDb db = new CQnmDb()) {
					//
					if (!bObjDbAvail(pQyMc.procedObjDb)) goto errLabel;
					if (null == db.getAvailableDb(pQyMc.iDsnIndex_mainSys)) goto errLabel;
					object pDb = db.m_pDbMem.pDb;

					if (!g_dbFuncs.pf_bGetMessengerInfoBySth(pQyMc.p_g_dbFuncs, pDb, pQyMc.cfg.db.iDbType, ref CONST_fieldIdTable_en, "", &idInfo, 0, &obj, null, null, null))
					{
						mymemset((IntPtr)(byte*)&obj, 0, sizeof(QY_MESSENGER_INFO));

						//lstrcpyn(obj.misServName, pMisCnt->cfg.misServName, mycountof(obj.misServName));
						obj.uiType = Consts.CONST_objType_me;
						obj.idInfo.ui64Id = idInfo.ui64Id;

						if (0 != pProcInfo.recoverMessenger(pDbFuncs, pDb, pQyMc.cfg.db.iDbType, ref CONST_fieldIdTable_en, &obj, null, 0, false, pProcInfo.schedulerQ))
						{
							//  2013/01/29
							//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo.who_showInfo, 0, _T(""), _T(""), _T("recoverMessenger failed"));
							goto errLabel;
						}

					}


					if (0 != g_dbFuncs.pf_updateImObj_me(pDb, pQyMc.cfg.db.iDbType, &obj)) goto errLabel;


					if (pQyMc.usMaxVideoConferenceMems != authResp.usMaxVideoConferenceMems) pQyMc.usMaxVideoConferenceMems = authResp.usMaxVideoConferenceMems;
					//
					if (pQyMc.ucDays_left != authResp.ucDays_left) pQyMc.ucDays_left = authResp.ucDays_left;  //  2010/03/22
																											  //
																  //uint uiMaxTimeInS_videoConference = bQmFreeVer(pQyMc) ? pQyMc.uiMaxTimeInS_videoConference_freeVer : pQyMc.uiMaxTimeInS_videoConference_general;
																											  //if (pQyMc.uiMaxTimeInS_videoConference != uiMaxTimeInS_videoConference) pQyMc.uiMaxTimeInS_videoConference = uiMaxTimeInS_videoConference;
																											  //
					//																						  //if (mymemcmp(&pMisCnt->idInfo, &idInfo, sizeof(pMisCnt->idInfo))  )  memcpy(&pMisCnt->idInfo, &idInfo, sizeof(pMisCnt->idInfo)  );
					pMisCnt.idInfo = idInfo;

					/*
				
				QM_OBJQ_MEM mem;

				memset(&obj, 0, sizeof(obj));

				lstrcpyn(obj.misServName, pMisCnt->cfg.misServName, mycountof(obj.misServName));
				obj.uiType = CONST_objType_me;
				obj.idInfo.ui64Id = idInfo.ui64Id;

				//  ÕâÀï·Åµ½¹ÜÀí¶ÓÁÐÖÐÈ¥
				if (procQmObjQ(pSci, (QM_OBJQ*)pMisCnt->pObjQ, pDb, pQyMc.cfg.db.iDbType, obj.uiType, &obj, &mem)) goto errLabel;

				QMEM_MESSENGER_CLI* pQMem;
				pQMem = (QMEM_MESSENGER_CLI*)mem.pQMemObj;

				//  (  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj  )->usRunningStatus  =  CONST_usRunningStatus_online;
				pQMem->usRunningStatus = CONST_usRunningStatus_online;
					*/

					pMisCnt.status.usRunningStatus = Consts.CONST_usRunningStatus_online; //  2007/08/31


					/*
				int i;  //  2009/10/11
				for (i = 0; i < pMisCnt.channels.Length; i++)
				{
						IM_NET_STAT netStat;
						mymemset((IntPtr)(byte*)&netStat, 0, sizeof(IM_NET_STAT));
						//mymemset((IntPtr)(byte*)&pMisCnt.channels[i].status.netStat, 0, sizeof(pMisCnt.channels[i].status.netStat)  );
						pMisCnt.channels[i].status.netStat = netStat;
			}
					*/

					//  ÏÂÃæ£¬ÒªÆô¶¯Ò»Ð©²ßÂÔ£¬´¥·¢ÔÚÁ¬½ÓÉÏ·þÎñÆ÷ºó£¬ÐèÒª×öµÄÒ»Ð©¶¯×÷
					//
					QY_MESSENGER_REGINFO regInfo;
					//	 
					//if (bMeInfoNeedReg(pDb, pQyMc.cfg.db.iDbType, pMisCnt, &regInfo)) pMisCnt.ucTriesToReg += 2;
					//
					//pMisCnt->ucbNeedSndDevInfo = TRUE;      //  2007/08/03
					//
					pMisCnt.bIntervalParamsGot = false;        //  2007/09/20,  ÕâÀï£¬Í¨¹ý½«¿ØÖÆ±äÁ¿Çå0¿ÉÒÔÈÃÍ¨µÀÁ¬Í¨Ö®ºó£¬ÖØÐÂÏÂÔØÒ»ÏÂÉèÖÃ¡£
															   //pMisCnt->bToPathsRetrieved = FALSE;     //  2008/02/09


					/*
# ifndef  __NOTSUPPORT_DB__
			if (!pQMem->talkerDesc[0]) {
				if (!g_dbFuncs.pf_bGetMessengerInfoBySth(pQyMc.p_g_dbFuncs, pDb, pSci->cfg.iDbType, getResTable(0, &pQyMc.cusRes, CONST_resId_fieldIdTable), pMisCnt->cfg.misServName, &pMisCnt->idInfo, 0, NULL, &regInfo, NULL, NULL)) goto errLabel;
				if (!regInfo.addr.idInfo.ui64Id) {
					regInfo.addr.idInfo.ui64Id = idInfo.ui64Id;
				}

				MY_REG_DESC desc;
				if (regInfo2Desc(0, &regInfo, &desc, pQMem->talkerDesc, mycountof(pQMem->talkerDesc), pQMem->displayName, mycountof(pQMem->displayName))) goto errLabel;
			}
#endif
			safeWcsnCpy(authResp.talkerDesc, pQMem->talkerDesc, mycountof(pQMem->talkerDesc));
					*/

					if (0 != updateMeDisplayInfo(pProcInfo, pMisCnt, null, null, null)) goto errLabel;



				}
			}

			iErr = 0;
		errLabel:

			if (iErr != 0)
			{
				if (pChannel.bSessionOpen)
				{
					qnmCloseSession_msg(ref pChannel.session, ref pChannel.sock, pQyMc.cfg.to);
					pChannel.bSessionOpen = false;
				}
			}


			return iErr;
		}


		//
		static void mcThreadProc_isCli(object lpParameter)
		{
			int iErr = -1;

			CCtxQyMc pQyMc = (CCtxQyMc)lpParameter;
			int iServiceId = Consts.CONST_qyServiceId_mis;
			//QY_SERVICEGUI_INFO* pSci = getServiceGuiInfo(pQyMc, iServiceId);
			//
			CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
			int i;
			bool bInited = false;
			uint dwThreadDaemonId;
			int loopCtrl = 0;
			//  QY_LOGICAL_SERVER				tmpCnt;
			QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;
			if (null == pDbFuncs) goto errLabel;
			QM_dbFuncs g_dbFuncs = pDbFuncs;

			MIS_CNT pMisCnt = pProcInfo.pMisCnt;
			if (pMisCnt == null) return;

			string str;
			str=("mcThreadProc_isCli enters");
			showInfo_open(0, null, str);

			/*

			for (; ; Sleep(2500))
			{           //  ÕâÀïÏÈµÈ´ýÓÃ»§µÇÂ½ÁË£¬ÔÙ¿ªÊ¼×öÏÂÃæµÄÊÂ
				if (pQyMc->bQuit) goto errLabel;
				if (!pQyMc->bLogon) continue;       //  2007/05/30

#if  0
		  if  (  !myStr2TChar(  pQyMc->curUsrInfo.name,  pProcInfo->authInfo.messengerName,  mycountof(  pProcInfo->authInfo.messengerName  )  )  )  {
			  traceLogA(  "ÓÃ»§ÃûÌ«³¤£¬·Å²»½øauthInfo.messengerNameÀïÈ¥"  );
			  goto  errLabel;
		  }
#endif
				break;
			}

			//
			if (!pQyMc->bChkQyMcEnv_mis())
			{
# ifdef  __DEBUG__
				traceLog(_T("mcThreadProc_isCli failed, bChkQyMcEnv_mis failed"));
#endif
				goto errLabel;
			}
			


			
			//for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
			for (i = 0; i < pProcInfo->ucCnt_misCnts; i++)
			{
				MIS_CNT* pMisCnt = getMisCntByIndex(0, pProcInfo, i);//&pProcInfo->misCnts[i];
				if (!pMisCnt) continue;
				MIS_CHANNEL* pChannel = NULL;

				if (pMisCnt->cfg.dynCfg.cnt.usCntPort)
				{
					//
					if (!(pChannel = getChannelByType(pMisCnt, CONST_channelType_talking))) goto errLabel;
					//
					//  pMisCnt->pAuthInfo  =  &pProcInfo->authInfo;

					clearQySock(&pChannel->sock);

# ifndef  __NOTSUPPORT_DB__
					{     //  »ñÈ¡±¾µØµÄqqºÅ
						CQnmDb db;
						QY_MESSENGER_INFO messengerInfo;

						if (bObjDbAvail(getProcedObjDb(pQyMc, 0, pQyMc->iDsnIndex_mainSys))
							&& db.getAvailableDb(pQyMc->iDsnIndex_mainSys)
							&& db.m_pDbMem->iDbType != CONST_dbType_myDb)
						{
							if (g_dbFuncs.pf_bGetMeInfoBySth(db.m_pDbMem->pDb, pSci->cfg.iDbType, pMisCnt->cfg.misServName, &messengerInfo)) pMisCnt->idInfo.ui64Id = messengerInfo.idInfo.ui64Id;
							//
							g_dbFuncs.pf_bClearupDeletedImObjs_isClient(pMisCnt, db.m_pDbMem->pDb, pSci->cfg.iDbType);
							//
							qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("Start to moveTask2His"));
							//
							g_dbFuncs.pf_bMoveTask2His(pMisCnt, db.m_pDbMem->pDb, pSci->cfg.iDbType);
							//
							qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("MoveTask2His finished"));
							//
							g_dbFuncs.pf_bStatImTasks(pProcInfo, pMisCnt, db.m_pDbMem->pDb, pSci->cfg.iDbType);
						}
					}
#endif
				}
			}
			*/


			pProcInfo.status.ulbThreadProcInited = true;   //  2007/09/02, ¸æÖªgui¿ÉÒÔÆô¶¯´°¿ÚÁË
														   //traceLogA("mcThreadProc_mis inited");

			//
			pProcInfo.bQuit_threadProc_isCli = false;
			pProcInfo.status.threadsStatus = new QMC_threads_status();

			//
			str = string.Format("mcThreadProc_isCli, to starts all threads");
			showInfo_open(0, null, str);

			//
			pProcInfo.hThread_mgr = new Thread(new ParameterizedThreadStart(mcThreadProc_mis_mgr));
			pProcInfo.hThread_mgr.Start();
			//
			/*
			pProcInfo->hThread_robot = CreateThread(NULL, 0, mcThreadProc_mis_robot, pSci, CREATE_SUSPENDED, &dwThreadDaemonId);
			if (!pProcInfo->hThread_robot) goto errLabel;
			pProcInfo->dwThreadId_robot = dwThreadDaemonId;
			if (ResumeThread(pProcInfo->hThread_robot) == -1) goto errLabel;
			//
			pProcInfo->hThread_display = CreateThread(NULL, 0, mcThreadProc_mis_display, pSci, CREATE_SUSPENDED, &dwThreadDaemonId);
			if (!pProcInfo->hThread_display) goto errLabel;
			pProcInfo->dwThreadId_display = dwThreadDaemonId;
			if (ResumeThread(pProcInfo->hThread_display) == -1) goto errLabel;
			//
			*/
			pProcInfo.hThread_work = new Thread(new ParameterizedThreadStart(mcThreadProc_mis_work));
			pProcInfo.hThread_work.Start();

			//
			pProcInfo.hThread_scheduler = new Thread(new ParameterizedThreadStart(mcThreadProc_mis_scheduler));
			pProcInfo.hThread_scheduler.Start();
			 //  
			pProcInfo.hThread_media = new Thread(new ParameterizedThreadStart(mcThreadProc_mis_media));
			pProcInfo.hThread_media.Start();			
			//
			pProcInfo.hThread_realTimeMedia = new Thread(new ParameterizedThreadStart(mcThreadProc_mis_realTimeMedia));
			pProcInfo.hThread_realTimeMedia.Start();

			/*
			//  2016/12/26
			pProcInfo->hThread_rtOp = CreateThread(NULL, 0, mcThreadProc_mis_rtOp, pSci, CREATE_SUSPENDED, &dwThreadDaemonId);
			if (!pProcInfo->hThread_rtOp) goto errLabel;
			pProcInfo->dwThreadId_rtOp = dwThreadDaemonId;
			if (ResumeThread(pProcInfo->hThread_rtOp) == -1) goto errLabel;
			*/

			//

			//
			for (; !pQyMc.bQuit && pQyMc.bLogon; loopCtrl++)
			{
				//, Thread.Sleep(1000)
				myWaitOne(pProcInfo.hEvt_notify_thread_isCli, 1000);
				//traceLog("mcThreadProc_isCli: evt waited");
				if (pQyMc.bQuit) break;

				//
				int loopCtrl_chkChannel = 5;
				loopCtrl_chkChannel = 3;
				if (0 == (loopCtrl % loopCtrl_chkChannel))
				{   //  ÕâÀïÏÈÓÃÕâ¸öÆµÂÊ£¬Ó¦¸Ã¼ÓÉÏºÍserverÁªÏµ¶ÏµÄÊ±ºò£¬Ò²Òª¼´Ê±ÖØÐÂÁ¬½Ó
					//for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  

					MIS_CHANNEL pChannel = getChannelByType(pMisCnt, Consts.CONST_channelType_talking);
					if (null == pChannel) continue;


					//  ÉÏÃæ²âÊÔÍêcorrectCntºó£¬²»ÄÜcontinue. ÒªÁ¢¼´ÅÐ¶ÏÏÂÃæµÄ×´Ì¬Î»¡£
					//
					if (pMisCnt.cfg.dynCfg.cnt.usCntPort != 0)
					{

						if (pProcInfo.status.threadsStatus.ulbMgrQuit
							|| pProcInfo.status.threadsStatus.ulbWorkQuit
								 || pProcInfo.status.threadsStatus.ulbDisplayQuit
									 || pProcInfo.status.threadsStatus.ulbRobotQuit
										 || pProcInfo.status.threadsStatus.ulbSchedulerQuit
											 || pProcInfo.status.threadsStatus.ulbMediaQuit
											 || pProcInfo.status.threadsStatus.ulbRealTimeMediaQuit
											 || pProcInfo.status.threadsStatus.ulbRtOpQuit
												 || pProcInfo.status.threadsStatus.ulbLogQuit
														//|| pMisCnt.status.ulbSeriousErr
														)
						{
							showInfo_open(IntPtr.Zero, "mcThreadProc_isCli", "mcThreadProc_mis will quit, because sub thread has quitted.");
							goto errLabel;
						}


						//
						if (!pChannel.bSessionOpen)
						{
							//  ´ò¿ªÁ¬½Ó
							startChannel(pProcInfo, pMisCnt, getChannelByType(pMisCnt, 0), "");
						}

						if (pChannel.hThread_io != null)
						{   //  ÕâÀïÒª¿´Ò»ÏÂÊÇ·ñÓÐÏß³ÌÍË³öÁË£¬µ±Í¨ÐÅÖÐ¶Ï»òÆäËûÒì³£Ô­ÒòÊ±£¬Ïß³Ì»áÍË³ö
							waitForThread(ref pChannel.hThread_io, 500);
							if (null == pChannel.hThread_io)
							{
								str = string.Format("channal {0} closed", qyGetDesByType1(CONST_channelTypeTable, pChannel.uiType));
								showInfo_open(null, "mcThreadProc_isCli", str);
							}

							/*
								if (null==pChannel.hThread_io)
								{

									//  ÏÂÃæÎªÍ¨ÖªÎÒ½Úµã±ä³ÉÀëÏß×´Ì¬
									//

									QM_OBJQ_MEM mem;

									if (!findQMemByKey(0, (QM_OBJQ*)pMisCnt->pObjQ, &pMisCnt->idInfo, &mem))
									{
										//	 
										((QMEM_MESSENGER_CLI*)mem.pQMemObj)->usRunningStatus = CONST_usRunningStatus_offline;

										pMisCnt->status.usRunningStatus = CONST_usRunningStatus_offline;

										lstrcpyn(pMisCnt->displayName, getResStr(0, &pQyMc->cusRes, CONST_resId_objIdStr_me), mycountof(pMisCnt->displayName));

										//  Ë¢ÐÂÒ»ÏÂÎÒ½Úµã£¬ 2007/06/20
										updateMeDisplayInfo(pProcInfo, pMisCnt, NULL, NULL, NULL);
									}

								}
							*/

						}

					}


				}
			}



			iErr = 0;

		errLabel:

			//
			str = string.Format("mcThreadProc_isCli will quit");
			qyFuncs.showInfo_open(0, null, str);

			//
			pProcInfo.bQuit_threadProc_isCli = true;

			//							
			{
				MIS_CHANNEL pChannel = getChannelByType(pProcInfo.pMisCnt, Consts.CONST_channelType_talking);

				//
				//Console.WriteLine("waitForChannel");
				waitForChannel(pProcInfo, pProcInfo.pMisCnt, 0, true);
				traceLog("channel talking waited");
			}

			//
			myEventSet(pProcInfo.mgrQ.hEvent);
			mySemaRelease(pProcInfo.schedulerQ.hSemaTrigger, 1);


			//
			MACRO_qyNullThread(ref pProcInfo.hThread_rtOp);    //  2016/12/26	 
			showInfo_open(0,null,"rtOp waited");
			//
			MACRO_qyNullThread(ref pProcInfo.hThread_realTimeMedia);   //  2008/04/25
			showInfo_open(0,null,"rt waited");
			//
			MACRO_qyNullThread(ref pProcInfo.hThread_media);           //  2008/03/15
			showInfo_open(0,null,"media waited");
			//
			MACRO_qyNullThread(ref pProcInfo.hThread_scheduler);
			showInfo_open(0,null,"scheduler waited");
			//
			MACRO_qyNullThread(ref pProcInfo.hThread_work);
			showInfo_open(0,null,"work waited");
			//
			MACRO_qyNullThread(ref pProcInfo.hThread_display);
			showInfo_open(0,null,"display waited");
			MACRO_qyNullThread(ref pProcInfo.hThread_robot);           //  2007/07/04
			showInfo_open(0,null,"robot waited");
			MACRO_qyNullThread(ref pProcInfo.hThread_mgr);
			showInfo_open(0,null,"mgr waited");

			//
			GuiShare.pf_PostMessage(pQyMc.gui.hMainWnd, Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_threadProc_isCli_end, 0);

			//
			pProcInfo.bEnd_threadProc_isCli = true;

			//
			str=string.Format("mcThreadProc_isCli leaves");
			qyFuncs.showInfo_open(0, null, str);


			//return iErr;
			return;
		}


		public static bool bChkMessengerChannelsReady(CCtxQyMc pQyMc)
		{
			bool bRet = false;
			//QY_SERVICEGUI_INFO* pSci = (QY_SERVICEGUI_INFO*)getServiceGuiInfo(pQyMc, pQyMc->iServiceId);
			//if (!pSci) goto errLabel;
			CCtxQmc pVar = (CCtxQmc)pQyMc.get_pProcInfo();
			if (null == pVar) return false;
			int i;
			MIS_CHANNEL pChannel = null;



					
			bool bTalkReady = false;
			bool bMediaReady = false;
			bool bRtMediaReady = false;
			bool bRobotReady = false;
			bool bRtOpReady = false;

			MIS_CNT pMisCnt = pVar.pMisCnt;
			if (null == pMisCnt) goto errLabel;
			//
			if (pMisCnt.cfg.dynCfg.cnt.usCntPort != 0)
			{
				if (bChannelOk(getChannelByType(pMisCnt, Consts.CONST_channelType_talking))) bTalkReady = true;
				if (bChannelOk(getChannelByType(pMisCnt, Consts.CONST_channelType_media))) bMediaReady = true;
				if (bChannelOk(getChannelByType(pMisCnt, Consts.CONST_channelType_realTimeMedia))) bRtMediaReady = true;
				if (bChannelOk(getChannelByType(pMisCnt, Consts.CONST_channelType_robot))) bRobotReady = true;
				if (bChannelOk(getChannelByType(pMisCnt, Consts.CONST_channelType_rtOp))) bRtOpReady = true;
			}


			bRet = true;

		errLabel:

			if (bRet)
			{
				if (pVar != null)
				{
					uint dwTickCnt = myGetTickCount(null);
					//
					if (pVar.av.talk.bChannelReady != bTalkReady)
					{
						pVar.av.talk.bChannelReady = bTalkReady;
						pVar.av.talk.dwLastModifiedTickCnt = dwTickCnt;

					}
					if (pVar.av.video.bChannelReady != bMediaReady)
					{
						pVar.av.video.bChannelReady = bMediaReady;
						pVar.av.video.dwLastModifiedTickCnt = dwTickCnt;
					}
					if (pVar.av.audio.bChannelReady != bRtMediaReady)
					{
						pVar.av.audio.bChannelReady = bRtMediaReady;
						pVar.av.audio.dwLastModifiedTickCnt = dwTickCnt;
					}
                    if (pVar.av.robot.bChannelReady != bRobotReady)
                    {
						pVar.av.robot.bChannelReady = bRobotReady;
						pVar.av.robot.dwLastModifiedTickCnt = dwTickCnt;
                    }
					if (pVar.av.rtOp.bChannelReady != bRtOpReady)
					{
						pVar.av.rtOp.bChannelReady = bRtOpReady;
						pVar.av.rtOp.dwLastModifiedTickCnt = dwTickCnt;
					}
				}
			}

			return bRet;

		}


		//
		public static unsafe int postMsg2OutputQ_mc(MIS_CNT pMisCnt, MIS_MSGU* pMsg, uint msgLen, MIS_CHANNEL pChannel)
		{
			int iErr = -1;

			if (null == pMisCnt)
			{
				traceLogA("postMsg2OutputQ_mc failed: pMisCnt is null");
				return -1;
			}

			CCtxQmc pProcInfo = (CCtxQmc)pMisCnt.pProcInfoParam;
			if (null == pProcInfo) return -1;
			CCtxQyMc pQyMc = (CCtxQyMc)pProcInfo.pQyMc;
			//QY_SERVICEGUI_INFO* pSci = (QY_SERVICEGUI_INFO*)pProcInfo->pSgiParam;
			//TCHAR tHintBuf[255 + 1] = _T("");
			TMP_tHintBuf tHintBuf;
			int tmpiRet = -1;
			//  CQyQ2Help					q2Help;


			if (0 != (tmpiRet = q2PostMsgAndTrigger((IntPtr)pMsg, msgLen, pChannel.outputQ2)))
			{

				if (tmpiRet != Consts.CONST_qyRet_qFull)
				{
					//_sntprintf(tHintBuf, mycountof(tHintBuf), _T("qPostMsgAndTrigger failed."));
					goto errLabel;
				}
				else
				{
					//_sntprintf(tHintBuf, mycountof(tHintBuf), _T("outputQ of %s is full. "), qyGetDesByType1(CONST_channelTypeTable, pChannel->uiType));
					switch (pChannel.uiType)
					{       //  2008/05/18, ÎªÁË±ÜÃâÊä³ö¶ÂÈû²»ÄÜÆð×÷ÓÃÁË£¬ÕâÀïÏÈ²ÉÈ¡Çå¿Õ²Ù×÷¡£×¢Òâ£ºÖ»ÄÜ¶ÔÊÓÆµµÈÊý¾Ý²»ÖØÒª£¬µ«ÊÇ×¢ÖØÊµÊ±ÐÔµÄ¶ÓÁÐ¡£
						case Consts.CONST_channelType_media:
						case Consts.CONST_channelType_realTimeMedia:
							//_sntprintf(tHintBuf, mycountof(tHintBuf), _T("%semptyQ now."), tHintBuf);
							emptyQ2(pChannel.outputQ2);
							break;
						default:
							break;
					}
					//  2015/08/22. 队列满时，不能退出，应接着触发发送. 在q2PostMsgAndTrigger已经触发
				}
			}
			if (pChannel.outputQ2.ucbTriggerErr) q2AvoidTriggerTooHigh(null, pChannel.outputQ2);

			iErr = 0;

		errLabel:

			if (iErr != 0 || tHintBuf.tHintBuf[0] != 0)
			{
				string str = string.Format(("postMsg2OutputQ_mc: {0}"), tHintBuf);
				qyShowInfo1(Consts.CONST_qyShowType_debugWarning, null, (""), pProcInfo.str_who_showInfo, null, (""), "", str);

			}

			return iErr;
		}

		///////////////////////////////////////
		///

		public static unsafe int procMsgInput_work_resp(CCtxQyMc pQyMc, CCtxQmc pProcInfo, MIS_MSG_INPUT* pMsgInput, uint lenInBytes_msg,  CTX_MC_thread pCtx, MIS_CHANNEL pChannel)
		{
			int iErr = -1;

			//  IM_CONTENTU		*	pContent	=	(  IM_CONTENTU  *  )&pMsgInput->data;
			IM_CONTENTU* pContent = M_getMsgContent(pMsgInput->ucFlg, &pMsgInput->data);

			int i;

			if (!isUcFlgResp(pMsgInput->ucFlg)) return -1;
			if (lenInBytes_msg < (uint)Marshal.OffsetOf<MIS_MSG_INPUT>("data")) return -1;

			switch (pContent->uiType)
			{
				/*
				case CONST_imCommType_refreshWebContactsInfo:

					for (i = 0; i < pContent->refreshWebContactsInfo.usCnt; i++)
					{
						//  ÐèÒªÈ·¶¨logicalPeer
						pMsgInput->addr_logicalPeer.idInfo.ui64Id = pContent->refreshWebContactsInfo.mems[i].idInfo.ui64Id;

						if (qPostMsg(pMsgInput, lenInBytes_msg, &pQyMc->gui.processQ))
						{
							traceLogA("mcThreadProc_mis_work(  ): qPostMsg(  ) failed");
							break;
						}
						PostMessage(pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);
					}

					break;
				case CONST_imCommType_vDevComs:
					if (!pContent->vDevComs.ucbResp) goto errLabel;

					myVDev_postData2Dev(pQyMc, pContent->vDevComs.uiVDevId, NULL, 0, 0, 0, pContent, lenInBytes_msg - offsetof(MIS_MSG_INPUT, data), 0, NULL, 0);

					break;
				case CONST_imCommType_retrieveSmPolicy:
					if (!pContent->retrieveSmPolicy.ucbResp) goto errLabel;

					myVDev_postData2Dev(pQyMc, pContent->retrieveSmPolicy.uiVDevId, NULL, 0, 0, 0, pContent, lenInBytes_msg - offsetof(MIS_MSG_INPUT, data), 0, NULL, 0);

					break;
				*/
				case Consts.CONST_imCommType_htmlContent:  //  2014/07/12

					if (0 != qPostMsg((IntPtr)pMsgInput, lenInBytes_msg, pQyMc.gui.processQ))
					{
						traceLogA("mcThreadProc_mis_work: qPostMsg failed.");
						break;
					}
					//PostMessage(pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);
					GuiShare.pf_PostMessage(pQyMc.gui.hMainWnd, Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_msgArrive, 0);

					break;
				default:
#if __DEBUG__
					traceLog(_T("Unprocessed contentType %d, procMsgInput_work_resp"), pContent->uiType);
#endif
					break;
			}

			iErr = 0;
		errLabel:
			return iErr;
		}



		public static unsafe int procMsgTalk_work(CCtxQyMc pQyMc, CCtxQmc pProcInfo, MIS_MSG_TALK* pMsg, uint lenInBytes_msg, ref CTX_MC_work pCtx, MIS_CHANNEL pChannel)
		{
			int iErr = -1;
			MIS_CNT pMisCnt = (MIS_CNT)pProcInfo.pMisCnt;
			int iDbType = pQyMc.cfg.db.iDbType;
			//char timeBuf[CONST_qyTimeLen + 1] = "";
			TMP_timeBuf timeBuf;
			char* pT;

			if (isUcFlgResp(pMsg->ucFlg)) return 0;
			QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;
			if (null==pDbFuncs) goto errLabel;
			QM_dbFuncs  g_dbFuncs = pDbFuncs;


			//
			MIS_MSG_routeTalkData* pTalkData = &pMsg->data;
			IM_CONTENTU* pContent = (IM_CONTENTU*)pTalkData->buf;
			//TCHAR senderDesc[1] = _T("");
			//TCHAR receiverDesc[1] = _T("");

			switch (pContent->uiType)
			{
				case Consts.CONST_imCommType_htmlContent:
					{
						//  2015/02/16
						IM_HTML_CONTENT* pReq = &pContent->html;

						if (0!=pReq->idInfo_logicalPeer.ui64Id)
						{
							if (null==pMisCnt) goto errLabel;
							if (pReq->idInfo_logicalPeer.ui64Id == pMisCnt.idInfo.ui64Id)
							{
								showInfo_open(0, null, ("procMsgTalk_work failed, req.idInfo_logicalPeer is me"));
								goto errLabel;
							}
							pMsg->addr_logicalPeer.idInfo.ui64Id = pReq->idInfo_logicalPeer.ui64Id;
						}
						//
						//  getTalkerDesc(  pMisCnt,  &pTalkData->route.idInfo_to,  receiverDesc,  mycountof(  receiverDesc  ),  NULL,  0  );
						//  postImMsg2Log(  pMisCnt->cfg.misServName,  &pTalkData->route.idInfo_from,  senderDesc,  pMsg->tStartTime,  pMsg->uiTranNo,  &pTalkData->route.idInfo_to,  receiverDesc,  pContent->uiType,  pContent->html.wBuf,  NULL,  pMsg->tRecvTime,  &pProcInfo->schedulerQ  );
						pProcInfo.postImMsg2Log_isClient((MIS_MSGU*)pMsg, (int)lenInBytes_msg);
					}
					break;
				default:
					break;
			}

			//
			if (0!=qPostMsg((IntPtr)pMsg, lenInBytes_msg, pQyMc.gui.processQ))
			{
				traceLogA("mcThreadProc_mis_work(  ): qPostMsg(  ) failed");
				goto errLabel;
			}
			GuiShare.pf_PostMessage(pQyMc.gui.hMainWnd, Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_msgArrive, 0);


			iErr = 0;

		errLabel:

			return iErr;
		}



		static unsafe void mcThreadProc_mis_work(object lpParameter)
		{
			//QY_SERVICEGUI_INFO* pSci = (QY_SERVICEGUI_INFO*)lpParameter;
			//if (!pSci) return -1;

			CCtxQyMc pQyMc = g.g_pQyMc;
			if (null==pQyMc) return;
			CCtxQmc pProcInfo = (CCtxQmc)pQyMc.get_pProcInfo();
			if (null==pProcInfo) return;

			int loopCtrl = 0;
			uint dwThreadId = myGetCurrentThreadId();
			MIS_MSGU* pMsg = null;
			uint len;
			uint dwRet;
			//
			CTX_MC_work ctx;
			//
			//  CWnd						*		pMainWnd						=	AfxGetApp(  )->m_pMainWnd;
			//
			uint uiChannelType = Consts.CONST_channelType_talking;

			traceLogA("mcThreadProc_mis_work:  enters");

			//
			pProcInfo.dwThreadId_work = myGetCurrentThreadId();

			//
			//memset(&ctx, 0, sizeof(ctx));
			ctx = new CTX_MC_work();

			using (CQyMalloc mallocObj = new CQyMalloc()) {
				if (null == (pMsg = (MIS_MSGU*)mallocObj.mallocf(Consts.CONST_iAllocType_longTimeMsg, sizeof(MIS_MSGU)))) goto errLabel;

				/*
				if (initGenericQ(&pProcInfo->cfg.guestQ, mymalloc, 0, 0, myfree, NULL, &ctx.guestQ)) goto errLabel;
				ctx.bGuestQInited = TRUE;
				//
				if (pProcInfo->cfg.guestQ.uiMaxQNodes)
				{
					len = sizeof(void*) * pProcInfo->cfg.guestQ.uiMaxQNodes;
					ctx.ppGuests_sortedByDevIdStr = (void**)mymalloc(len);
					if (!ctx.ppGuests_sortedByDevIdStr) goto errLabel;
					memset(ctx.ppGuests_sortedByDevIdStr, 0, len);
				}
				*/

				//  2007/06/20
				if (!bObjDbAvail(pQyMc.procedObjDb))
				{
					goto errLabel;
				}

				for (; !pProcInfo.bQuit_threadProc_isCli;)
				{

					//  if  (  !pMainWnd  )  pMainWnd					=	AfxGetApp(  )->m_pMainWnd;
					if (null==pQyMc.gui.hMainWnd)
					{
						Thread.Sleep(1000); continue;
					}

					//dwRet = WaitForSingleObject(pProcInfo->workQ.hSemaTrigger, 5000);
					//if (dwRet == WAIT_FAILED) goto errLabel;
					myWaitOne(pProcInfo.workQ.hSemaTrigger, 3500);
					
					//
					for (; !pProcInfo.bQuit_threadProc_isCli;)
					{
						
						len = (uint)sizeof(MIS_MSGU);
						if (0!=qGetMsg(pProcInfo.workQ, (IntPtr)pMsg, &len)) break;
						mymemset((IntPtr)(((byte*)pMsg) + len), 0, (int)Math.Min(256, sizeof(MIS_MSGU) - len));
						
						switch (pMsg->uiType)
						{
							
							case Consts.CONST_misMsgType_input:
								{
									MIS_CNT pMisCnt = (MIS_CNT)pProcInfo.pMisCnt;
									MIS_CHANNEL pChannel = null;

									if (null==pMisCnt)
									{
										traceLogA("mcThreadProc_mis_work failed: pMisCnt is null");
										break;
									}
									if (null==(pChannel = getChannelByType(pMisCnt, uiChannelType))) break;

									if (!isUcFlgResp(pMsg->input.ucFlg))
									{
										if (0!=procMsgInput_other_req(pQyMc, pProcInfo, &pMsg->input, len, ctx, pChannel)) break;
										break;
									}

									if (0!=procMsgInput_work_resp(pQyMc, pProcInfo, &pMsg->input, len, ctx, pChannel)) break;
									//
								}
								break;
								
							case Consts.CONST_misMsgType_talk:
								{
									MIS_CNT pMisCnt = (MIS_CNT)pProcInfo.pMisCnt;
									IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->talk.data.buf;
									MIS_CHANNEL pChannel = null;

									if (null==pMisCnt)
									{
										traceLogA("mcThreadProc_mis_work: pMisCnt is null");
										break;
									}
									if (null==(pChannel = getChannelByType(pMisCnt, uiChannelType))) break;

									//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%I64u [%s]"), pMsg->talk.data.route.idInfo_from.ui64Id, qyGetDesByType1(getResTable(0, &pQyMc->cusRes, CONST_resId_pcCommTypeTable), pContent->uiType));

									if (0!=getIdInfo_logicalPeer( pMisCnt, &pMsg->talk.data.route, &pMsg->talk.addr_logicalPeer)) break;

									traceLogA("mcThreadProc_mis_work(  ): talk");

									//  
									if (0!=procMsgTalk_work(pQyMc, pProcInfo, &pMsg->talk, len, ref ctx, pChannel)) break;

								}
								break;
								
							
							case Consts.CONST_misMsgType_task:
								{
									MIS_CNT pMisCnt = (MIS_CNT)pProcInfo.pMisCnt;
									IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->task.data.buf;

									if (null==pMisCnt)
									{
										traceLogA("mcThreadProc_mis_work: pMisCnt is null");
										break;
									}

									//qyShowInfo1(Consts.CONST_qyShowType_qwmComm, 0, (""), pProcInfo.str_who_showInfo, 0, (""), (""), _T("%I64u [%s]"), pMsg->task.data.route.idInfo_from.ui64Id, qyGetDesByType1(getResTable(0, &pQyMc->cusRes, CONST_resId_pcCommTypeTable), pContent->uiType));

									traceLogA("mcThreadProc_mis_work: task");

								}
								break;
							
							default:
								//traceLog("mcThreadProc_mis_work failed, unknown  msgType %d", pMsg->uiType);
								break;
						}

						//dwRet = WaitForSingleObject(pProcInfo->workQ.hSemaTrigger, 50);
						//if (dwRet == WAIT_FAILED) goto errLabel;
						
					}
					
				}
			}


		errLabel:


			//if (ctx.ppGuests_sortedByDevIdStr) free(ctx.ppGuests_sortedByDevIdStr);
			//if (ctx.bGuestQInited) exitGenericQ(&ctx.guestQ);

			traceLogA("mcThreadProc_mis_work:  leaves");

			pProcInfo.status.threadsStatus.ulbWorkQuit = true;

			return;
		}


		public static unsafe int getIdInfo_logicalPeer( MIS_CNT pMisCnt, MSG_ROUTE* pRoute, MSGR_ADDR* pAddr_logicalPeer)
		{
			int iErr = -1;
			CCtxQyMc pQyMc = g.g_pQyMc;
			if (null==pQyMc) return -1;

			if (null==pMisCnt) return -1;        //  2007/12/23
			QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;
			if (null==pDbFuncs) goto errLabel;
			QM_dbFuncs  g_dbFuncs = pDbFuncs;

			/*
			if (pRoute->uiDevType_from == CONST_objType_dev)
			{
				if (isImGrp_isClient(pSci, pMisCnt, &pRoute->idInfo_to))
				{
					pAddr_logicalPeer->idInfo.ui64Id = pRoute->idInfo_to.ui64Id;
					iErr = 0; goto errLabel;
				}
				//
				pAddr_logicalPeer->idInfo.ui64Id = pRoute->idInfo_from.ui64Id;
				pAddr_logicalPeer->uiDevType = pRoute->uiDevType_from;
				safeWcsnCpy(pRoute->wDevIdStr_from, pAddr_logicalPeer->wDevIdStr, mycountof(pAddr_logicalPeer->wDevIdStr));
			}
			else if (pRoute->uiDevType_to == CONST_objType_dev)
			{
				pAddr_logicalPeer->idInfo.ui64Id = pRoute->idInfo_to.ui64Id;
				pAddr_logicalPeer->uiDevType = pRoute->uiDevType_to;
				safeWcsnCpy(pRoute->wDevIdStr_to, pAddr_logicalPeer->wDevIdStr, mycountof(pAddr_logicalPeer->wDevIdStr));
			}
			else
			*/
			{

				if (pRoute->idInfo_to.ui64Id == pMisCnt.idInfo.ui64Id)
				{
					pAddr_logicalPeer->idInfo.ui64Id = pRoute->idInfo_from.ui64Id;
					iErr = 0; goto errLabel;
				}
				else
				{
				//
				pAddr_logicalPeer->idInfo.ui64Id = pRoute->idInfo_to.ui64Id;
			}
		}

		iErr  =  0;
errLabel:
	return  iErr;
}


		public static unsafe int myGetPeer(string misServName, MSG_ROUTE* pRoute, MSGR_ADDR* pAddr_logicalPeer, MSGR_ADDR* pPeer)
		{
			int iErr = -1;

			//
			if (null==misServName || null==pRoute || null==pAddr_logicalPeer || null==pPeer) return -1;

			mylstrcpyn(pPeer->misServName, misServName, Consts.CONST_maxMisServNameLen + 1);
			pPeer->uiObjType = pRoute->uiObjType_src;
			//
			pPeer->idInfo.ui64Id = pAddr_logicalPeer->idInfo.ui64Id;
			pPeer->uiDevType = pAddr_logicalPeer->uiDevType;
			//safeWcsnCpy(pAddr_logicalPeer->wDevIdStr, pPeer->wDevIdStr, mycountof(pPeer->wDevIdStr));
			//
			pPeer->uiLogonId = pRoute->uiLogonId;



			iErr = 0;
		errLabel:
			return iErr;
		}


		public static unsafe int waitToQuit_isCli(CCtxQmc pProcInfo, int dwTimeInMs)
		{
			if (null==pProcInfo) return -1;

			
			if (0!=pProcInfo.waitToQuit.dwTickCnt_start) return 0;
			pProcInfo.waitToQuit.dwTickCnt_start = myGetTickCount(null);
			pProcInfo.waitToQuit.dwTimeInMs = (uint)dwTimeInMs;
			

			return 0;
		}

		//
		public static int notifyPanicToApp(CCtxQyMc pQyMc, int iErr, string hint)
		{
			traceLogA("notifyPanicToApp: not supported");
			if (null!=pQyMc)
			{
				traceLogA("notifyPanicToApp: WM_CLOSE");
				//  pMainWnd->PostMessage(  WM_CLOSE,  0,  0  );
				//GuiShare.pf_PostMessage(pQyMc.gui.hMainWnd, Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_qyQuitMainWnd, 0);
			}

			return 0;
		}



	}
}

