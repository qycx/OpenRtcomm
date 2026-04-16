
#include	"stdafx.h"

#include	<ShellAPI.h>
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qyCusResTemp.h"

#ifndef  __NOTSUPPORT_MULTIDOC__

#ifndef  __useQt__
	#include	"mainClient.h"
	#include	"mainFrm.h"
#endif

#endif
#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	"qmcVideoCapture_isCli.h"

#include	"myresource.h"

#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
#ifdef  __WINCE__
		#ifndef  __TEST__
				 #include	"ceMenuBar.h"
		#endif
		#include	"dlgTalk_ce.h"
#else
//		#include	"myHtmlEditCtrl.h"		 
//		#include	"DlgTalk.h"
		#include	"DlgTalkproc.h"
#endif
#endif
#include	"QyPlaySound_wave.h"
#include	"qmcDxSurfacePublic.h"
#include	"qyWnd.h"

#include	"dlgMcClientLogon.h"
#ifdef  __WINCE__
		#include	"dlg_qyMc_winCe.h"
		#include	"dlgObjs.h"
#endif
#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
#include	"DlgQnmCfgOptionsIsClient.h"
//  #include	"DlgInstantAssistant.h"
#endif
#include	"module_qisCamCap.h"

#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
#ifndef  __NOTSUPPORT_MULTIDOC__
#ifndef  __useQt__
		 #include	"dlgNotification.h"
#endif

#endif
#endif

//  
#include	"myDb.h"
#include	"isCliHelpPublic.h"
#include	"isCliD3dPublic.h"
#include	"qyMessengerHelpPublic.h"
#include	"qmcCommFunc_isCli.h"
#include	"dyn_isCliD3d_public.h"

#include	"avConsole_open.h"
#include	"myTypes.h"
#include	"qmcTaskInfo.h"


//
int chkTasksStatus(AtTasksStatus* pTasksStatus, LPCTSTR  hint)
{
    boolean bTaskExists_av = false;
    boolean bTaskExists_file = false;

    CCtxQyMc  *  pQyMc = g_pQyMc;
    CCtxQmc  *  pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();
    if (pProcInfo == mynull)return  -1;

    //
    //Log.d("anc","chkTasksStatus called "  +  hint);

    //
    int  i;
    QMC_TASK_INFO  * pTaskInfo  =  mynull;
    //
    for (i = 0; i < pProcInfo->cfg.usMaxCnt_taskInfos; i++) {
        pTaskInfo = (QMC_TASK_INFO*)pProcInfo->getQmcTaskInfoByIndex( i);
        if (!pTaskInfo->bUsed) continue;
        QMC_taskData_common  * pTaskData = pTaskInfo->var.pTaskData;
        if (pTaskData == mynull) continue;

        //
        if (!qmcTaskInfo_bAlive(pProcInfo, i))
            continue;

        //
        MIS_MSG_TASK  * pMsgTask = (MIS_MSG_TASK*) &pTaskData->msgU;
        {
            if (pMsgTask->uiType != CONST_misMsgType_task) {
                continue;
            }

            //
            IM_CONTENTU  * pContent = M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
            if (mynull == pContent) continue;
            //
            if (pContent->uiType == CONST_imCommType_transferAvInfo) {
                bTaskExists_av = true;
            }

            //
            continue;
        }

        //
    }


    //
    if (pTasksStatus->bTaskExists_av != bTaskExists_av) {
        pTasksStatus->bTaskExists_av = bTaskExists_av;
        //
        //Log.d("anc", "chkTasksStatus: changed: exists_av is " + tasksStatus.bTaskExists_av);
    }
    if (pTasksStatus->bTaskExists_file != bTaskExists_file) {    //  bTaskExists_file 还没完成
        pTasksStatus->bTaskExists_file = bTaskExists_file;
        //
        //Log.d("anc", "chkTasksStatus: changed: exists_file is " + tasksStatus.bTaskExists_file);
    }

    //
    return  0;
}





//
       int mainWnd_chk_tasks(HWND hMainWnd, void  *  pVar )
        {
            int iErr = -1;
            CCtxQyMc *pQyMc = g_pQyMc;
            CCtxQmc *pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();
            uint uiTickCnt_now = myGetTickCount(NULL);
            QMC_TASK_INFO *pTaskInfo = mynull;
            int i;
			int iElapseInMs = 0;

			if(  !pVar  )  return  -1;
			QY_MC_mainWndVar &var=*(QY_MC_mainWndVar  * )pVar;
            
            //
            QMC_status* pStatus = &pProcInfo->status;

            //
            chkTasksStatus(&pStatus->tasksStatus, _T("mainWnd_chk_tasks.l168"));

            //
            if (0==(var.loopCtrl % 10))
            {
                for ( i = 0;i < pProcInfo->cfg.usMaxCnt_taskInfos;i ++)
                {
                    pTaskInfo = (QMC_TASK_INFO *)pProcInfo->getQmcTaskInfoByIndex(i);
                    if (!pTaskInfo->bUsed) continue;
					//
                    MIS_MSG_TASK * pMsgTask=&pTaskInfo->var.pTaskData->msgU.task;
                    {
						if (pMsgTask->uiType != CONST_misMsgType_task)
						{
							continue;
						}

						//
						if  (  pTaskInfo->var.bNeedRemoved
							||  pTaskInfo->var.bTaskInvalid  )
						{
							freeTaskInfo(  pProcInfo,  i,  _T(  "mainWnd_chkTasks: task need removed"  )  );
							continue;
						}

						//if (qyFuncs.bTaskAlive(pMsgTask->iStatus)) continue;
						if (qmcTaskInfo_bAlive(pProcInfo, i)) continue;
                        
						//						
						iElapseInMs = abs((int)(uiTickCnt_now-pTaskInfo->var.dwTickCnt_recv_lastRefreshed));
						if ( iElapseInMs>pProcInfo->cfg.usTimeoutInMs_waitIfNoData)
                        {
							freeTaskInfo(pProcInfo, i, _T(  "mainWnd_chk_tasks")  );
							continue;
                        }
                    }

					//
					continue;
                }
            }
                
            //
			/*
            if (var.notifyTaskStatus.bExists_task && var.notifyTaskStatus.bAvCall)
                {
                    pTaskInfo = pProcInfo.getQmcTaskInfoByIndex(var.notifyTaskStatus.index_taskInfo);
				if (pTaskInfo == null
				|| !qyFuncs.qmcTaskInfo_bAlive(pProcInfo,var.notifyTaskStatus.index_taskInfo))
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
                pTaskInfo = pProcInfo.getQmcTaskInfoByIndex(i);
                if (!pTaskInfo.bUsed) continue;

				//
				if (!qyFuncs.qmcTaskInfo_bAlive(pProcInfo, i)) continue;

				//
				fixed (MIS_MSG_TASK* pMsgTask = &pTaskInfo.var.pTaskData.msgU.task) {
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
			*/

                //
            

                iErr = 0;
            errLabel:
                return iErr;

            
            }





			//				
			//
		int mainWnd_do_closeTask(int iTaskId)
        {
			int iErr = -1;
			CCtxQyMc * pQyMc = g_pQyMc;
			CCtxQmc *pProcInfo = (CCtxQmc *)pQyMc->get_pProcInfo();

			int index_taskInfo = getQmcTaskInfoIndexBySth(  pProcInfo,  iTaskId  );
			QMC_TASK_INFO *pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
			if (pTaskInfo == mynull) return -1;

			removeTask(pTaskInfo->var.iTaskId);
			qmcTaskInfo_setClosed(pProcInfo, index_taskInfo,_T(  "mainWnd_do_closeTask")  );

			iErr = 0;
		errLabel:
			return iErr;

        }
