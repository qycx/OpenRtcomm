

#include	"stdafx.h"
//
#include <CMainFrame.h>

//
#include	"qyMcMainCommon_qt.h"
#include <string>
#include <ctxQmc_qt.h>
#include <qyMcMainWndProc.h>
#include <GuiShare.h>
#include    "myDb.h"
#include "MessageSignalCenter.h"
#include "DlgAvAccept.h"


//
int mainWnd_procMsgTask_transferAvInfo(MIS_MSG_TASK* pMsgTask);
int mainWnd_procMsgTask_transferFileReq(MIS_MSG_TASK* pMsgTask);


//
int mainWnd_gui_procMsg(void* pMsgParam)
{
	MIS_MSGU* pMsgU = (MIS_MSGU*)pMsgParam;

//    
        int iErr = -1;
        CCtxQyMc* pQyMc = QY_GET_GBUF();
        //QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;

        //
        QY_MESSENGER_ID addr_logicalPeer_idInfo;    addr_logicalPeer_idInfo.ui64Id = 0;
        QY_MESSENGER_ID idInfo_from;                idInfo_from.ui64Id = 0;
        std::wstring msg = _T("");
        __int64 tRecvTime = 0;
        __int64 tStartTime = 0;
        std::wstring str;
        SendData sd;
        memset(&sd, 0, sizeof(sd));
        bool bneedsend = false;
    
        bool  bDbg = false;


        //
        if (bDbg) {
            str = _T("fg_msglist.gui_procMsg enters");
            showInfo_open0(0, _T(""), str.c_str());
        }

        //
        switch (pMsgU->uiType)
        {
        case CONST_misMsgType_talk:
        {
            //
            

            //
            MIS_MSG_TALK* pMsg = &pMsgU->talk;
            IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->data.buf;
            //
            addr_logicalPeer_idInfo = pMsg->addr_logicalPeer.idInfo;
            idInfo_from = pMsg->data.route.idInfo_from;
            tRecvTime = pMsg->tRecvTime;
            tStartTime = pMsg->tStartTime;
            //
            switch (pContent->uiType)
            {
            case CONST_imCommType_htmlContent:
            {
                msg = std::wstring(pContent->html.wBuf);
                sd.from_id = idInfo_from;
                bneedsend = true;
            }
            break;
            }


        }
        break;
        case  CONST_misMsgType_task: {
            MIS_MSG_TASK* pMsg = &pMsgU->task;
            IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->data.buf;
            //
            addr_logicalPeer_idInfo = pMsg->addr_logicalPeer.idInfo;
            idInfo_from = pMsg->data.route.idInfo_from;
            tRecvTime = pMsg->tRecvTime;
            tStartTime = pMsg->tStartTime;
            //
            switch (pContent->uiType) {
            case  CONST_imCommType_transferAvInfo:
                msg = std::wstring(_T("视频呼叫"));
                
                //
                QY_MESSENGER_ID idInfo_initiator;
                if (pContent->transferAvInfo.confCfg.idInfo_initiator.ui64Id)
                {
                    idInfo_initiator.ui64Id = pContent->transferAvInfo.confCfg.idInfo_initiator.ui64Id;
                }
                else {

                    idInfo_initiator.ui64Id = idInfo_from.ui64Id;
                }


                sd.uiTranNo = pMsg->uiTranNo;
                sd.iTaskId = pMsg->iTaskId;
                sd.from_id = idInfo_initiator;
                mainWnd_procMsgTask_transferAvInfo(pMsg);
                bneedsend = true;
                //
                //
                break;
            case  CONST_imCommType_transferFileReq:
                msg = std::wstring(_T("文件发送"));
                mainWnd_procMsgTask_transferFileReq(pMsg);
                sd.from_id = idInfo_from;
                bneedsend = true;
                break;

            }

        }
            break;
        case CONST_misMsgType_input:
        {
            MIS_MSG_INPUT* pMsg = &pMsgU->input;
            IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->data.buf;
            //
            addr_logicalPeer_idInfo = pMsg->addr_logicalPeer.idInfo;
            idInfo_from = pMsg->data.route.idInfo_from;
            tRecvTime = pMsg->tRecvTime;
            tStartTime = pMsg->tStartTime;
            //
            switch (pContent->uiType)
            {
            case CONST_imCommType_transferAvInfo:
            {
                msg = std::wstring(_T("视频呼叫"));
            }
            break;
            }

        }
        break;
        default:
            goto errLabel;
            break;


        }

       
        
        sd.peer_id = addr_logicalPeer_idInfo;
        //TCHAR赋值 
        safeTcsnCpy(msg.c_str(), sd.msg, mycountof(sd.msg));
        sd.send_time = tStartTime;
        
        //
        if (bneedsend) {
            emit MessageSignalCenter::Instance().signal_recv_new_message(sd);
        }
       

        //
        if (bDbg) {
            str = _T("fg_msgList.gui_procMsg, recvd ") + msg;
            showInfo_open0(0, NULL, str.c_str());
        }
        //



        iErr = 0;

    errLabel:


        //
        if (bDbg) {
            str = _T("fg_msglist.gui_procMsg leaves, iErr ") + iErr;
            showInfo_open0(0, NULL, str.c_str());
        }

        //
        return iErr;

    }
	

    //



 



    //
     int gui_notify_chk()
     {
         int iErr = -1;
         CCtxQyMc *pQyMc = g_pQyMc;
         if (pQyMc == null) return -1;
         CCtxQmc *pProcInfo = (CCtxQmc *)pQyMc->get_pProcInfo();

         HWND  hMainWnd = pQyMc->gui.hMainWnd;
         CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
         if (pMainWnd == NULL)goto  errLabel;
         QY_MC_mainWndVar &var_common = pMainWnd->var.common;

         //
         bool bNeedShow = false;
         //
         if (var_common.notifyTaskStatus.bExists_task
             && var_common.notifyTaskStatus.bAvCall)
         {
             int  index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, var_common.notifyTaskStatus.iTaskId);
             if  (  qmcTaskInfo_bAlive(pProcInfo, index_taskInfo) )         
             {         
                 bNeedShow = true;         
             }
         }

         //
         if (bNeedShow) {

             viewDlgAvAccept();

         }
         else {
             closeDlgAvAccept();   
             //
             gui_notify_clear();
         }

         //
         iErr = 0;
     errLabel:

             return  iErr;

     }

     //
     void gui_notify_clear()
     {
         CCtxQyMc* pQyMc = g_pQyMc;
         if (pQyMc == null) return;
         CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

         HWND  hMainWnd = pQyMc->gui.hMainWnd;
         CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
         if (pMainWnd == NULL)goto  errLabel;
         QY_MC_mainWndVar& var_common = pMainWnd->var.common;

         //
         closeDlgAvAccept();
         //
         memset(&var_common.notifyTaskStatus, 0, sizeof(var_common.notifyTaskStatus));


         //
     errLabel:
         return;

     }

     void gui_notify_clearTask(int  iTaskId)
     {
         CCtxQyMc* pQyMc = g_pQyMc;
         if (pQyMc == null) return;
         CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

         HWND  hMainWnd = pQyMc->gui.hMainWnd;
         CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
         if (pMainWnd == NULL)goto  errLabel;
         QY_MC_mainWndVar& var_common = pMainWnd->var.common;

         if (iTaskId == 0)return;

         //
         if (var_common.notifyTaskStatus.bExists_task && var_common.notifyTaskStatus.bAvCall) {
             if (var_common.notifyTaskStatus.iTaskId == iTaskId) {
                 closeDlgAvAccept();
                 memset(&var_common.notifyTaskStatus, 0, sizeof(var_common.notifyTaskStatus));
             }
         }


     errLabel:
         return;
     }





     //
     int  getAvCallerInfo(QY_MESSENGER_ID  *  pidInfo_logicalPeer, QY_MESSENGER_ID  *    pidInfo_from)
     {
         int  iErr = -1;
         CCtxQyMc* pQyMc = g_pQyMc;
         CCtxQmc* pProcInfo = (CCtxQmc *)pQyMc->get_pProcInfo();

         if (pidInfo_logicalPeer == null || pidInfo_from == null)  return  -1;
  
         HWND  hMainWnd = pQyMc->gui.hMainWnd;
         CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
         if (pMainWnd == null)  goto  errLabel;
         QY_MC_mainWndVar& var = pMainWnd->var.common;

         //
         if (!var.notifyTaskStatus.bExists_task ||  !var.notifyTaskStatus.bAvCall)  goto  errLabel;

         int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo,var.notifyTaskStatus.iTaskId);
         QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(pProcInfo,index_taskInfo);
         if (pTaskInfo == null)  goto  errLabel;

         QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
         MIS_MSG_TASK* pMsgTask = &pTaskData->msgU.task;
         if (pMsgTask->uiType != CONST_misMsgType_task)  goto  errLabel;
         
         IM_CONTENTU* pContent = M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
         if (pContent->uiType != CONST_imCommType_transferAvInfo)  goto  errLabel;


         pidInfo_logicalPeer->ui64Id = pMsgTask->addr_logicalPeer.idInfo.ui64Id;
         pidInfo_from->ui64Id = pMsgTask->data.route.idInfo_from.ui64Id;
         if (pContent->transferAvInfo.confCfg.idInfo_initiator.ui64Id) {
             pidInfo_from->ui64Id = pContent->transferAvInfo.confCfg.idInfo_initiator.ui64Id;
         }


         //
         iErr = 0;

     errLabel:

         return  iErr;
     }














     //
     int doAvRecover(int iTaskId)
     {
         int iErr = -1;
         CCtxQyMc  * pQyMc = g_pQyMc;
         CCtxQmc  * pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();

         int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, iTaskId);
         QMC_TASK_INFO *pTaskInfo = (QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
         if (pTaskInfo == null) goto errLabel;

         //
         pTaskInfo->var.bClosed = false;
         
         
         //
         QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
         MIS_MSG_TASK* pMsgTask = &pTaskData->msgU.task;
         if (pMsgTask->uiType != CONST_misMsgType_task)  goto  errLabel;
         pMsgTask->nTimes_applyForChkTaskAlive = 0;


         //
#if  0
         //
         DLG_TALK_var m_var = this.mhTalk.m_var;


         //
         m_var.av.bNeedDoTaskAv = true;

         //
         //mainActivity.var_common.processingAvTask
         this.mhTalk.startActivity_dlgTalk_av(tmpResource.IDC_BUTTON_av_accept, index_taskInfo);
#endif



         iErr = 0;
     errLabel:

         return iErr;
     }


     //
     int do_cancelTask1(int iTaskId, bool bAutoCancel, LPCTSTR hint)
     {

         int iErr = -1;
         bool bDbg = false;
         std::wstring str;

#if DEBUG
         bDbg = true;
#endif
         //
         if (bDbg)
         {
             showInfo_open0(0, null, _T("do_canncelTask1 enters"));
         }

         //
         //
         CCtxQyMc  * pQyMc = g_pQyMc;
         CCtxQmc *pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
         MIS_CNT *pMisCnt = pProcInfo->getMisCntByName(_T(""));
         //MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;
         //TCHAR tBuf[256] = _T("");
         //char buf[256] = "";
         CQyMalloc mallocObj;

         //if (!hDlg || !pParam || !pMsgElem) return -1;
         QM_dbFuncs * pDbFuncs = pQyMc->p_g_dbFuncs;
         if (null == pDbFuncs) goto errLabel;
         QM_dbFuncs * g_dbFuncs = pDbFuncs;

         time_t tStartTran; uint uiTranNo;

         int index_taskInfo = getQmcTaskInfoIndexBySth( pProcInfo, iTaskId);
         if (index_taskInfo < 0) return -1;

         //
         QMC_TASK_INFO *pTaskInfo = (QMC_TASK_INFO*)pProcInfo->getQmcTaskInfoByIndex( index_taskInfo);
         if (pTaskInfo == null) return -1;

         //
         if (!pTaskInfo->bUsed) return 0;

         //
         if (bDbg)
         {
             //str = string.Format("do_cancelTask, index_taskInfo {0}. {1}", index_taskInfo, hint);
             showInfo_open0(0, null, str.c_str());
         }

         //
         QMC_taskData_common *pTaskData = pTaskInfo->var.pTaskData;
         if (pTaskData == null) goto errLabel;

         //
         MIS_MSG_TASK* pMsg = &pTaskData->msgU.task; {
             if (pMsg->uiType != CONST_misMsgType_task)
             {
                 goto errLabel;
             }

             IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->data.buf;
             int iStatus;
             int lenInBytes;


             void * pDb = null;
             {
                 CQnmDb db;
                 if (null == db.getAvailableDb(pQyMc->iDsnIndex_mainSys)) goto errLabel;
                 pDb = db.m_pDbMem->pDb;

                 switch (pContent->uiType)
                 {
                 case CONST_imCommType_transferAvInfo:
                 case CONST_imCommType_transferFileReq:
                     switch (pMsg->iStatus)
                     {
                     case CONST_imTaskStatus_req:
                     case CONST_imTaskStatus_applyToSend:
                     case CONST_imTaskStatus_waitToSend:
                     case CONST_imTaskStatus_acceptedByReceiver:
                     case CONST_imTaskStatus_dualByReceiver:
                     {


                         iStatus = CONST_imTaskStatus_canceledBySender;
                         g_dbFuncs->pf_updateTaskStatus(pDb, iStatus, pMsg->iTaskId);
                         pMsg->iStatus = iStatus;        //  2012/05/15

                         //  °ÑÏÔÊ¾×´Ì¬ÐÞ¸ÄÏÂ.2008/11/14
                         //showTaskStatus(pMisCnt, &pMgrVar->addr.idInfo, &pMsg->idInfo_taskSender, &pMsg->idInfo_taskReceiver, FALSE, pContent->uiType, pMsg->iTaskId, iStatus, 0, 0, _T(""), _T(""));

                         //  Í¨Öª¶Ô·½
                         TASK_PROC_REQ taskProcReq;
                         memset((byte*)&taskProcReq, 0, sizeof(TASK_PROC_REQ));
                         taskProcReq.uiType = CONST_imCommType_taskProcReq;
                         taskProcReq.usOp = CONST_imOp_send_cancel;
                         taskProcReq.tStartTime_org = pMsg->tStartTime;
                         taskProcReq.uiTranNo_org = pMsg->uiTranNo;
                         taskProcReq.uiContentType_org = pContent->uiType;
                         //
                         lenInBytes = sizeof(TASK_PROC_REQ);
                         //					  
                         MACRO_prepareForTran();
                         //  2015/09/08
                         uint uiChannelType = pMsg->uiChannelType;
                         //
                         uiChannelType = 0;
                         //
                         if (0 != postMsgTask2Mgr_mc( pMisCnt, CONST_misMsgType_task, 0, pMsg->usCode, tStartTran, uiTranNo, 0, pMsg->iTaskId, pMsg->uiTaskType, (char*)&taskProcReq, (uint)lenInBytes, &pMsg->addr_logicalPeer.idInfo, &pMsg->idInfo_taskSender, &pMsg->idInfo_taskReceiver, &pMsg->idInfo_taskReceiver, uiChannelType, null, false)) goto errLabel;
                     }
                     break;
                     case CONST_imTaskStatus_resp:
                     case CONST_imTaskStatus_applyToRecv:
                     case CONST_imTaskStatus_waitToRecv:
                     {


                         iStatus = bAutoCancel ? CONST_imTaskStatus_autoCanceledByReceiver : CONST_imTaskStatus_canceledByReceiver;
                         g_dbFuncs->pf_updateTaskStatus(pDb, iStatus, pMsg->iTaskId);
                         pMsg->iStatus = iStatus;        //  2012/05/15

                         //  °ÑÏÔÊ¾×´Ì¬ÐÞ¸ÄÏÂ.2008/11/14
                         //showTaskStatus(pMisCnt, &pMgrVar->addr.idInfo, &pMsg->idInfo_taskSender, &pMsg->idInfo_taskReceiver, FALSE, pContent->uiType, pMsg->iTaskId, iStatus, 0, 0, _T(""), _T(""));

                         //  Í¨Öª¶Ô·½
                         TASK_PROC_REQ taskProcReq;
                         memset((byte*)&taskProcReq, 0, sizeof(TASK_PROC_REQ));
                         taskProcReq.uiType = CONST_imCommType_taskProcReq;
                         taskProcReq.usOp = CONST_imOp_recv_cancel;
                         taskProcReq.tStartTime_org = pMsg->tStartTime;
                         taskProcReq.uiTranNo_org = pMsg->uiTranNo;
                         taskProcReq.uiContentType_org = pContent->uiType;
                         //
                         lenInBytes = sizeof(TASK_PROC_REQ);
                         //					  
                         MACRO_prepareForTran( );
                         //  2015/09/08
                         uint uiChannelType = pMsg->uiChannelType;
                         //
                         uiChannelType = 0;
                         //	
                         if (0 != postMsgTask2Mgr_mc(pMisCnt, CONST_misMsgType_task, 0, pMsg->usCode, tStartTran, uiTranNo, 0, pMsg->iTaskId, 0, (char*)&taskProcReq, (uint)lenInBytes, &pMsg->addr_logicalPeer.idInfo, &pMsg->idInfo_taskSender, &pMsg->idInfo_taskReceiver, &pMsg->idInfo_taskSender, uiChannelType, null, false)) goto errLabel;
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
         pTaskInfo->var.dwTickCnt_recv_lastRefreshed = myGetTickCount(null);

         iErr = 0;

     errLabel:

         if (bDbg)
         {
             showInfo_open0(0, null, _T("do_canncelTask1 leaves"));
         }

         //
         return iErr;
     }


