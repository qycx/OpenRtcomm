

#include	"stdafx.h"
//
#include <CMainFrame.h>

//
#include	"qyMcMainCommon_qt.h"
#include <string>
#include <qyMcMainWndProc.h>
#include <GuiShare.h>
#include    "myDb.h"
#include "MessageSignalCenter.h"
#include "DlgAvAccept.h"
#include    "oldConfs.h"



     //
     int findOldRecvdConfActive(HWND  hTalk,  int * piTaskId)
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
             if (pTaskInfo == mynull) goto errLabel;
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
                     uint uiTickCnt = myGetTickCount(mynull);
                     int iDissInMs = (int)(uiTickCnt - pTaskInfo->var.dwTickCnt_recv_lastRefreshed);
                     if (abs(iDissInMs) < 20000)
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




    //
int findOldRecvdConfsActive(OldConfs* pOldConfs)
{
    int iErr = -1;
    //
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    int i;
    //std::wstring str;
    TCHAR  tBuf[128];


    //
    if (!pOldConfs) return  -1;
    memset(pOldConfs, 0, sizeof(OldConfs));


    //
    for (i = 0; i < pProcInfo->cfg.usMaxCnt_taskInfos; i++)
    {
        QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, i);
        if (pTaskInfo == mynull) goto errLabel;
        if (!pTaskInfo->bUsed) continue;
        QMC_taskData_common* taskData = pTaskInfo->var.pTaskData;
        if (taskData->uiType != CONST_taskDataType_conf) continue;
        QMC_taskData_conf* pTc = (QMC_taskData_conf*)taskData;
        MIS_MSG_TASK* pMsgTask = &pTc->common.msgU.task;

        if (pMsgTask->uiType != CONST_misMsgType_task) continue;
        //
        if (pMsgTask->data.route.idInfo_from.ui64Id != pMisCnt->idInfo.ui64Id)
        {
            IM_CONTENTU* pContent = (IM_CONTENTU*)pMsgTask->data.buf;
            if (pContent->uiType != CONST_imCommType_transferAvInfo) continue;

#if DEBUG
            ref IM_CONTENTU tmp_pContent = ref * pContent;
#endif
            uint uiTickCnt = myGetTickCount(mynull);
            int iDiffInMs = (int)(uiTickCnt - pTaskInfo->var.dwTickCnt_recv_lastRefreshed);
            if (abs(iDiffInMs) < 25000)
            {

                //_sntprintf(tBuf, mycountof(tBuf), _T("任务 %d 仍在活跃中"), (pTaskInfo->var.iTaskId));
                //showNotification_open(0, 0, 0, tBuf);

                //
                //*piTaskId = pTaskInfo->var.iTaskId;
                if (pOldConfs->usCnt < mycountof(pOldConfs->mems))
                {
                    OldConfMem* pMem = &pOldConfs->mems[pOldConfs->usCnt];
                    pMem->iTaskId = pTaskInfo->var.iTaskId;
                    pMem->uiElapseInms_lastRefreshed = iDiffInMs;
                    pMem->idInfo_peer.ui64Id = pMsgTask->addr_logicalPeer.idInfo.ui64Id;

                    //
                    pOldConfs->usCnt++;
                }

                //
            }
        }
        continue;
    }

    iErr = 0;
errLabel:
    return iErr;
}

