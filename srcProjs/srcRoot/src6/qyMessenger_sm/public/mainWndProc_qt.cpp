

#include	"stdafx.h"
//
#include <CMainFrame.h>

//
#include	"qyMcMainCommon_qt.h"
#include <string>
#include <ctxQmc_sm.h>
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


#if  0
    //
int iimainWnd_procMsgTask_transferAvInfo(MIS_MSG_TASK* pMsgTask)
{
    int iErr = -1;

    //
    bool bDbg = false;
    std::string str;

    //
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    int i;
    int index_taskInfo = -1;

    IM_CONTENTU* pContent = M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
    if (pContent->uiType != CONST_imCommType_transferAvInfo) goto errLabel;

    //
    HWND  hMainWnd = pQyMc->gui.hMainWnd;
    CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
    if (pMainWnd == NULL)  goto  errLabel;
    QY_MC_mainWndVar& var = pMainWnd->var.common;



    //
    if (!pProcInfo->status.retrieveImObjList.ulbAllContactsRetrieved)
    {
        showInfo_open0(0, null, _T("mainWnd_procMsgInput_transferAvInfo failed, ulbAllContactsRetrieved is false"));
        goto errLabel;
    }


    //
    if (pMsgTask->iTaskId == 0)
    {
        traceLog((TCHAR*)_T("mainWnd_procMsgInput failed, iTaskId is 0"));
        goto errLabel;
    }

    //
    //str = string.Format("mainWnd_procMsgInput_av enters: from {0}", pMsgInput->data.route.idInfo_from.ui64Id);
    //qyFuncs.showInfo_open0(0, null, str);


    //
    for (i = 0; i < pProcInfo->cfg.usMaxCnt_taskInfos; i++)
    {
        QMC_TASK_INFO* e = (QMC_TASK_INFO*)pProcInfo->getQmcTaskInfoByIndex(i);
        if (!e->bUsed) continue;
        //
        if (e->var.iTaskId == pMsgTask->iTaskId)
        {
            {
                break;
            }
        }
    }
    //
    if (i < pProcInfo->cfg.usMaxCnt_taskInfos) {
        index_taskInfo = i;
    }
    else {


        index_taskInfo = newTaskInfoIndex(pProcInfo, CONST_taskDataType_conf, null, pMsgTask->iTaskId, _T("mainWnd_procMsgInput_transferAvInfo"));
        if (index_taskInfo < 0)
        {
            traceLog((TCHAR*)_T("mainWnd_procMsgInput_transferAvInfo failed: too many tasks"));
            goto errLabel;

        }
        //
             //            
        QMC_TASK_INFO* tts1 = (QMC_TASK_INFO*)pProcInfo->getQmcTaskInfoByIndex(index_taskInfo);
        if (tts1 == null) goto errLabel;

        //
        QMC_taskData_common* pTaskData1 = tts1->var.pTaskData;
        if (pTaskData1 == null) goto errLabel;
        //(MIS_MSG_TASK * pMsgTask = &pTaskData.msgU.task)
        {
            //msgInput2Task(pMsgInput, pMsgTask);
            pTaskData1->msgU.task = *pMsgTask;


        }
    }


        //            
        QMC_TASK_INFO *tts = (QMC_TASK_INFO*)pProcInfo->getQmcTaskInfoByIndex( index_taskInfo);
        if (tts == null) goto errLabel;

        //
        tts->var.dwTickCnt_recv_lastRefreshed = myGetTickCount(null);

        //
        if (!qmcTaskInfo_bAlive(pProcInfo, index_taskInfo)) {
            showInfo_open0(0, null, _T("mainWnd_procMsgTask_transferAvInfo failed, qmcTaskInfo_bAlive false"));
            goto  errLabel;
        }

        QMC_taskData_common* pTaskData = tts->var.pTaskData;
        if (pTaskData == null) goto errLabel;

        //  这里的pMsgTask指向了taskInfo里的msgTask
        pMsgTask = &pTaskData->msgU.task;
        if (pMsgTask->uiType != CONST_misMsgType_task)  goto  errLabel;



            //
            QY_MESSENGER_ID  idInfo_peer = pMsgTask->addr_logicalPeer.idInfo;

            //
            //GuiShare.pf_gui_procMsg((IntPtr)pMsgInput);

            //
#ifdef  __DEBUG__
            if (idInfo_peer.ui64Id == 114) {
                int  ii = 0;
            }
            if (idInfo_peer.ui64Id == 177) {
                int  ii = 0;
            }
#endif
            
            //
            if (!bTaskNeedAcception(pMsgTask->iStatus)) {
                showInfo_open0(0, null, _T("mainWnd_procMsgTask_transferAvInfo failed, bTaskNeedAcception false"));
                goto  errLabel;
            }

            //
            {
                //
                HWND  hWnd;
                if (findTalker_shadow(pQyMc, idInfo_peer.ui64Id, CONST_talkerSubtype_video, &hWnd)) {

                    //
                    if (var.notifyTaskStatus.bExists_task && IsWindow(var.notifyTaskStatus.hTool_dlgAvAccept))
                    {
                        iErr = 0; goto errLabel;
                    }
                    var.notifyTaskStatus.bExists_task = true;
                    var.notifyTaskStatus.bAvCall = true;
                    //var.notifyTaskStatus.index_taskInfo = index_taskInfo;
                    var.notifyTaskStatus.iTaskId = pMsgTask->iTaskId;

                    //
                    //str = string.Format("mainWnd_procMsgInput_transferAvInfo: fill notifyTaskStatus, call gui_notify_chk");
                    //qyFuncs.showInfo_open0(0, null, str);

                    //
                    GuiShare.pf_gui_notify_chk();

                    //

                }
            }
        

        //
        iErr = 0;

    errLabel:

        //
        //str = string.Format("mainWnd_procMsgInput_av leaves: from {0}", pMsgInput->data.route.idInfo_from.ui64Id);
        //qyFuncs.showInfo_open0(0, null, str);

        return iErr;

    }
#endif


#if 0
    //
    int iimainWnd_procMsgTask_transferFileReq(MIS_MSG_TASK* pMsgTask)
    {
        int iErr = -1;

        //
        bool bDbg = false;
        std::string str;

        //
        CCtxQyMc* pQyMc = g_pQyMc;
        CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
        QM_dbFuncs& g_dbFuncs = *(QM_dbFuncs*)pQyMc->p_g_dbFuncs;
        //
        int i;
        int index_taskInfo = -1;

        IM_CONTENTU* pContent = M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
        if (pContent->uiType != CONST_imCommType_transferFileReq) goto errLabel;

        //
        HWND  hMainWnd = pQyMc->gui.hMainWnd;
        CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
        if (pMainWnd == NULL)  goto  errLabel;
        QY_MC_mainWndVar& var = pMainWnd->var.common;



        //
        if (!pProcInfo->status.retrieveImObjList.ulbAllContactsRetrieved)
        {
            showInfo_open0(0, null, _T("mainWnd_procMsgInput_transferAvInfo failed, ulbAllContactsRetrieved is false"));
            goto errLabel;
        }


        //
        if (pMsgTask->iTaskId == 0)
        {
            traceLog((TCHAR*)_T("mainWnd_procMsgInput failed, iTaskId is 0"));
            goto errLabel;
        }

        //
        //str = string.Format("mainWnd_procMsgInput_av enters: from {0}", pMsgInput->data.route.idInfo_from.ui64Id);
        //qyFuncs.showInfo_open0(0, null, str);

        //
        if (pMsgTask->addr_logicalPeer.idInfo.ui64Id) {
            if (pMsgTask->addr_logicalPeer.idInfo.ui64Id != pMsgTask->data.route.idInfo_from.ui64Id) {
                bool  bGrp = true;
                //
                unsigned  int  uiObjType = 0;
                getTalkerDesc(pMsgTask->addr_logicalPeer.idInfo, &uiObjType, null, 0, null, null, 0, null, 0, null, 0);
                if (!uiObjType) {
                    CQnmDb db;
                    if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
                    void* pDb = db.m_pDbMem->pDb;
                    uiObjType = CONST_objType_tmpGrp;
                    IM_GRP_INFO  grpInfo;
                    memset(&grpInfo, 0, sizeof(grpInfo));
                    grpInfo.idInfo.ui64Id = pMsgTask->addr_logicalPeer.idInfo.ui64Id;
                    recoverImGrp(&g_dbFuncs, pDb, pQyMc->cfg.db.iDbType, CONST_fieldIdTable_en, uiObjType, &grpInfo, 0, true);
                }
            }
        }




        //
        int lenInBytes_msg = offsetof(MIS_MSG_TASK, data) + pMsgTask->lenInBytes;
        pProcInfo->postImMsg2Log_isClient((MIS_MSGU*)pMsgTask, lenInBytes_msg);
     

        //
        iErr = 0;

    errLabel:

        //
        //str = string.Format("mainWnd_procMsgInput_av leaves: from {0}", pMsgInput->data.route.idInfo_from.ui64Id);
        //qyFuncs.showInfo_open0(0, null, str);

        return iErr;

    }
#endif




    //
     int gui_notify_chk()
     {
         int iErr = -1;
         CCtxQyMc *pQyMc = g_pQyMc;
         if (pQyMc == mynull) return -1;
         CCtxQmc *pProcInfo = (CCtxQmc *)pQyMc->get_pProcInfo();

         HWND  hMainWnd = pQyMc->gui.hMainWnd;
         CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
         if (pMainWnd == NULL)return  -1;// goto  errLabel;
         QY_MC_mainWndVar &var_common = pMainWnd->var.common;

         //
         bool bNeedShow; bNeedShow = false;
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
         if (pQyMc == mynull) return;
         CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

         HWND  hMainWnd = pQyMc->gui.hMainWnd;
         CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
         if (pMainWnd == NULL)goto  errLabel;
         {
             QY_MC_mainWndVar& var_common = pMainWnd->var.common;

             //
             closeDlgAvAccept();
             //
             memset(&var_common.notifyTaskStatus, 0, sizeof(var_common.notifyTaskStatus));
         }

         //
     errLabel:
         return;

     }

     void gui_notify_clearTask(int  iTaskId)
     {
         CCtxQyMc* pQyMc = g_pQyMc;
         if (pQyMc == mynull) return;
         CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

         HWND  hMainWnd = pQyMc->gui.hMainWnd;
         CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
         if (pMainWnd == NULL)goto  errLabel;
         //
         {
             QY_MC_mainWndVar& var_common = pMainWnd->var.common;

             if (iTaskId == 0)return;

             //
             if (var_common.notifyTaskStatus.bExists_task && var_common.notifyTaskStatus.bAvCall) {
                 if (var_common.notifyTaskStatus.iTaskId == iTaskId) {
                     closeDlgAvAccept();
                     memset(&var_common.notifyTaskStatus, 0, sizeof(var_common.notifyTaskStatus));
                 }
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

         if (pidInfo_logicalPeer == mynull || pidInfo_from == mynull)  return  -1;
  
         HWND  hMainWnd = pQyMc->gui.hMainWnd;
         CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
         if (pMainWnd == mynull)  return  -1;// goto  errLabel;
         QY_MC_mainWndVar& var = pMainWnd->var.common;

         //
         if (!var.notifyTaskStatus.bExists_task ||  !var.notifyTaskStatus.bAvCall)  goto  errLabel;

         int index_taskInfo; index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, var.notifyTaskStatus.iTaskId);
         QMC_TASK_INFO* pTaskInfo; pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
         if (pTaskInfo == mynull)  goto  errLabel;

         QMC_taskData_common* pTaskData; pTaskData = pTaskInfo->var.pTaskData;
         MIS_MSG_TASK* pMsgTask; pMsgTask = &pTaskData->msgU.task;
         if (pMsgTask->uiType != CONST_misMsgType_task)  goto  errLabel;
         
         IM_CONTENTU* pContent; pContent = M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
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




#if 0
     //
     int iiacceptTaskAv(int  iTaskId)
     {
         int  iErr = -1;
         CCtxQyMc* pQyMc = QY_GET_GBUF();
         CCtxQmc* pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();
         MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
         
         //
         int  index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, iTaskId);
         if (index_taskInfo < 0)return  -1;

         //
         QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
         if (pTaskInfo == null)  return  -1;
         QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
         MIS_MSG_TASK* pMsgTask = &pTaskData->msgU.task;

         //
         //pMsgTask->iStatus = CONST_imTaskStatus_waitToRecv;
         pMsgTask->iStatus = CONST_imTaskStatus_applyToRecv;

         //
         QY_MESSENGER_ID  idInfo = pMsgTask->addr_logicalPeer.idInfo;
         int  iTalkSubtype = CONST_talkerSubtype_video;
         HWND  m_hWnd_shadow  =  null;
         
         //
#ifdef  __DEBUG__
         IM_CONTENTU* pContent = M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
         if (pContent->uiType == CONST_imCommType_transferAvInfo) {
             int  ii = 0;
         }
#endif


         //         
         if (!findTalker_shadow(pQyMc, idInfo.ui64Id, iTalkSubtype, &m_hWnd_shadow)) {
                 SetForegroundWindow(m_hWnd_shadow);
             }
         else {
             //
             pProcInfo->tryToTalkToMessenger_any(null, idInfo.ui64Id, iTalkSubtype, FALSE, FALSE, &m_hWnd_shadow);

             if (findTalker_shadow(pQyMc, idInfo.ui64Id, iTalkSubtype, &m_hWnd_shadow)) {
                 goto errLabel;
             }

         }        
         //
         HWND  hMgr = null;
         if (findTalker(pQyMc, &idInfo, &hMgr))  goto  errLabel;
         dlgTalk_qPostMsg(hMgr, pMsgTask, sizeof(MIS_MSG_TASK));
         //
         ::PostMessage(hMgr, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);

         //
         {
             CHelp_getDlgTalkVar getDlgTalkVar;
             DLG_TALK_var* pMgrVar = (DLG_TALK_var*)getDlgTalkVar.getVar(hMgr);
             if (pMgrVar == null)goto  errLabel;
             pMgrVar->autoAnswer.bTaskExists = true;
         }         
         //
         iErr = 0;
        
     errLabel:
         return  iErr;
     }
#endif


     //
#if 0
     int iifindOldRecvdTaskAvActive(HWND  hTalk,  int * piTaskId)
     {
         int iErr = -1;
         //
         CCtxQyMc  * pQyMc = g_pQyMc;
         CCtxQmc *pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();
         MIS_CNT * pMisCnt = pProcInfo->getMisCntByName(_T(""));
         int i;
         //std::wstring str;
         TCHAR  tBuf[128];


         CHelp_getDlgTalkVar getDlgTalkVar_cur;
         DLG_TALK_var* pCurVar = (DLG_TALK_var*)getDlgTalkVar_cur.getVar(hTalk);
         if (!pCurVar)  return  -1;
#if 0
         if (!isTalkerShadowMgr(pCurVar->addr)) {
             CHelp_getDlgTalkVar  getDlgTalkVar_mgr;
             DLG_TALK_var 

         }
#endif
         QY_MESSENGER_ID talk_idInfo;
         talk_idInfo.ui64Id = pCurVar->addr.idInfo.ui64Id;



         //
         for (i = 0; i < pProcInfo->cfg.usMaxCnt_taskInfos; i++)
         {
             QMC_TASK_INFO *pTaskInfo = (QMC_TASK_INFO  *  )getQmcTaskInfoByIndex( pProcInfo, i);
             if (pTaskInfo == null) goto errLabel;
             if (!pTaskInfo->bUsed) continue;
             QMC_taskData_common *taskData = pTaskInfo->var.pTaskData;
             if (taskData->uiType != CONST_taskDataType_conf) continue;
             QMC_taskData_conf *pTc = (QMC_taskData_conf*)taskData;
             MIS_MSG_TASK* pMsgTask = &pTc->common.msgU.task;
             {
                 if (pMsgTask->uiType != CONST_misMsgType_task) continue;
                 //
                 if (pMsgTask->addr_logicalPeer.idInfo.ui64Id == talk_idInfo.ui64Id
                     && pMsgTask->data.route.idInfo_from.ui64Id != pMisCnt->idInfo.ui64Id)
                 {
                     IM_CONTENTU* pContent = (IM_CONTENTU*)pMsgTask->data.buf;
                     if (pContent->uiType != CONST_imCommType_transferAvInfo) continue;

#if DEBUG
                     ref IM_CONTENTU tmp_pContent = ref * pContent;
#endif
                     uint uiTickCnt = myGetTickCount(null);
                     int iDissInMs = (int)(uiTickCnt - pTaskInfo->var.dwTickCnt_recv_lastRefreshed);
                     if (abs(iDissInMs) < 2000)
                     {

                         _sntprintf(  tBuf,mycountof(  tBuf  ),  _T(  "任务 %d 仍在活跃中"), (pTaskInfo->var.iTaskId));
                         showNotification_open(0, 0, 0, tBuf);

                         //
                         *piTaskId = pTaskInfo->var.iTaskId;

                         //
                         break;
                     }



                 }
             }
         }
         if (i == pProcInfo->cfg.usMaxCnt_taskInfos) goto errLabel;

         iErr = 0;
     errLabel:
         return iErr;
     }
#endif



     //
     int doAvRecover(int iTaskId)
     {
         int iErr = -1;
         CCtxQyMc  * pQyMc = g_pQyMc;
         CCtxQmc  * pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();

         int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, iTaskId);
         QMC_TASK_INFO *pTaskInfo = (QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
         if (pTaskInfo == mynull) goto errLabel;

         //
         pTaskInfo->var.bClosed = false;
         
         
         //
         QMC_taskData_common* pTaskData; pTaskData = pTaskInfo->var.pTaskData;
         MIS_MSG_TASK* pMsgTask; pMsgTask = &pTaskData->msgU.task;
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
             showInfo_open0(0, mynull, _T("do_canncelTask1 enters"));
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
         if (mynull == pDbFuncs) return  -1;// goto errLabel;
         QM_dbFuncs * g_dbFuncs = pDbFuncs;

         time_t tStartTran; uint uiTranNo;

         int index_taskInfo; index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, iTaskId);
         if (index_taskInfo < 0) return -1;

         //
         QMC_TASK_INFO* pTaskInfo; pTaskInfo = (QMC_TASK_INFO*)pProcInfo->getQmcTaskInfoByIndex(index_taskInfo);
         if (pTaskInfo == mynull) return -1;

         //
         if (!pTaskInfo->bUsed) return 0;

         //
         if (bDbg)
         {
             //str = string.Format("do_cancelTask, index_taskInfo {0}. {1}", index_taskInfo, hint);
             showInfo_open0(0, mynull, str.c_str());
         }

         //
         QMC_taskData_common* pTaskData; pTaskData = pTaskInfo->var.pTaskData;
         if (pTaskData == mynull) goto errLabel;

         //
         MIS_MSG_TASK* pMsg; pMsg = &pTaskData->msgU.task; {
             if (pMsg->uiType != CONST_misMsgType_task)
             {
                 goto errLabel;
             }

             IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->data.buf;
             int iStatus;
             int lenInBytes;


             void * pDb = mynull;
             {
                 CQnmDb db;
                 if (mynull == db.getAvailableDb(pQyMc->iDsnIndex_mainSys)) goto errLabel;
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
                         if (0 != postMsgTask2Mgr_mc( pMisCnt, CONST_misMsgType_task, 0, pMsg->usCode, tStartTran, uiTranNo, 0, pMsg->iTaskId, pMsg->uiTaskType, (char*)&taskProcReq, (uint)lenInBytes, &pMsg->addr_logicalPeer.idInfo, &pMsg->idInfo_taskSender, &pMsg->idInfo_taskReceiver, &pMsg->idInfo_taskReceiver, uiChannelType, mynull, false)) goto errLabel;
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
                         if (0 != postMsgTask2Mgr_mc(pMisCnt, CONST_misMsgType_task, 0, pMsg->usCode, tStartTran, uiTranNo, 0, pMsg->iTaskId, 0, (char*)&taskProcReq, (uint)lenInBytes, &pMsg->addr_logicalPeer.idInfo, &pMsg->idInfo_taskSender, &pMsg->idInfo_taskReceiver, &pMsg->idInfo_taskSender, uiChannelType, mynull, false)) goto errLabel;
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
         pTaskInfo->var.dwTickCnt_recv_lastRefreshed = myGetTickCount(mynull);

         iErr = 0;

     errLabel:

         if (bDbg)
         {
             showInfo_open0(0, mynull, _T("do_canncelTask1 leaves"));
         }

         //
         return iErr;
     }


