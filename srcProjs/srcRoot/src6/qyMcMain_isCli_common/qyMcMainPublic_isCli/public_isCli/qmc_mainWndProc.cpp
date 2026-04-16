
#include	"stdafx.h"
//
#include <CMainFrame.h>

//
#include	"qyMcMainCommon_qt.h"
#include <string>
//#include <ctxQmc_qt.h>
#include <qyMcMainWndProc.h>
#include <GuiShare.h>
#include    "myDb.h"
#include <help_getDlgTalkVar.h>
//#include "MessageSignalCenter.h"
//#include "DlgAvAccept.h"

void* getObjAddr(HWND  hWnd);


//
     //
int acceptTaskAv(int  iTaskId)
{
    int  iErr = -1;
    CCtxQyMc* pQyMc = QY_GET_GBUF();
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
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
    pTaskInfo->var.bClosed = false;

    //
    QY_MESSENGER_ID  idInfo = pMsgTask->addr_logicalPeer.idInfo;
    int  iTalkSubtype = CONST_talkerSubtype_video;
    HWND  m_hWnd_shadow = null;

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



#if  10
    //
int mainWnd_procMsgTask_transferAvInfo(MIS_MSG_TASK* pMsgTask)
{
    int iErr = -1;

    //
    bool bDbg = false;
    std::string str;

    //
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)return -1;

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
    if (!bDone_retrieveAllImObjRules(pMisCnt))
    {
        showInfo_open0(0, null, _T("mainWnd_procMsgInput_transferAvInfo failed, ulbAllImObjRules is false"));
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
    QMC_TASK_INFO* tts = (QMC_TASK_INFO*)pProcInfo->getQmcTaskInfoByIndex(index_taskInfo);
    if (tts == null) goto errLabel;

    //
    tts->var.dwTickCnt_recv_lastRefreshed = myGetTickCount(null);


    QMC_taskData_common* pTaskData = tts->var.pTaskData;
    if (pTaskData == null) goto errLabel;

    //  这里的pMsgTask指向了taskInfo里的msgTask
    pMsgTask = &pTaskData->msgU.task;
    if (pMsgTask->uiType != CONST_misMsgType_task)  goto  errLabel;


    //        
    QY_MESSENGER_ID  idInfo_peer = pMsgTask->addr_logicalPeer.idInfo;


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
    if (!qmcTaskInfo_bAlive(pProcInfo, index_taskInfo)) {
        //
        HWND  hWnd;
        if (!findTalker_shadow(pQyMc, idInfo_peer.ui64Id, CONST_talkerSubtype_video, &hWnd)) {
            //  视频窗口已打开，可以接收这个任务
            acceptTaskAv(pMsgTask->iTaskId);
            //
            iErr = 0;  goto  errLabel;
        }

        //
        if (pProcInfo->m_iCtxSubtype == CONST_ctxSubtype_qmcSm) {
            if (pProcInfo->uiTerminalType == CONST_terminalType_conf) {
                if (pMsgTask->iStatus == CONST_imTaskStatus_waitToRecv) {
                    //
                    acceptTaskAv(pMsgTask->iTaskId);
                    //
                    iErr = 0;  goto  errLabel;
                }
            }
        }

        //            
        showInfo_open0(0, null, _T("mainWnd_procMsgTask_transferAvInfo failed, qmcTaskInfo_bAlive false"));
        goto  errLabel;

    }


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
                if (pProcInfo->m_iCtxSubtype != CONST_ctxSubtype_qmcSm) {
                    iErr = 0; goto errLabel;
                }
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


//
   //
int mainWnd_procMsgTask_transferFileReq(MIS_MSG_TASK* pMsgTask)
{
    int iErr = -1;

    //
    bool bDbg = false;
    std::string str;

    //
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

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
    if (!bDone_retrieveAllImObjRules(pMisCnt))
    {
        showInfo_open0(0, null, _T("mainWnd_procMsgInput_transferFileReq failed, ulbAllImObjRules is false"));
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



