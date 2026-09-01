
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


int  tmpHandler_canAcceptTalks(void* p0, void* p1, MIS_MSGU* pMsgElem)
{
	COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
	// p1;

    unsigned  __int64& gid = *(unsigned  __int64*)pCommonParam->p0;


	TCHAR		tBuf[512] = _T("");
	int			i = 0;
	char		timeBuf[CONST_qyTimeLen + 1] = "";
	char		displayBuf[255 + 1] = "";
	int			j;
	QY_MC* pQyMc = QY_GET_GBUF();


	if (pMsgElem->uiType == CONST_misMsgType_talkingFriend_qmc) {
        
		HWND			hDlgTalk = pMsgElem->talkingFriend_qmc.hWnd;
		//  CDlgTalk	*	pDlg	=	(  CDlgTalk  *  )CWnd::FromHandle(  pMsg->talkingFriend_qmc.hWnd  );
		CHelp_getDlgTalkVar	help_getDlgTalkVar;
		DLG_talk_var* pDlgTalkVar = (DLG_talk_var*)help_getDlgTalkVar.getVar(hDlgTalk);
		if (!pDlgTalkVar)  goto  errLabel;
		DLG_talk_var& m_var = *pDlgTalkVar;

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("talk %I64u, tn %d"), m_var.addr.idInfo.ui64Id, m_var.addr.uiTranNo_shadow);
		traceLog(tBuf);

        if (m_var.addr.idInfo.ui64Id != gid) {
            return 2;
        }

	}

errLabel:
	return  0;
}
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
    if (pTaskInfo == mynull)  return  -1;
    QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
    MIS_MSG_TASK* pMsgTask = &pTaskData->msgU.task;
    
    //
    //pMsgTask->iStatus = CONST_imTaskStatus_waitToRecv;
    pMsgTask->iStatus = CONST_imTaskStatus_applyToRecv;
    pTaskInfo->var.bClosed = false;

    //
    QY_MESSENGER_ID  idInfo = pMsgTask->addr_logicalPeer.idInfo;
    int  iTalkSubtype = CONST_talkerSubtype_video;
    HWND  m_hWnd_shadow = mynull;	

    if (pProcInfo->m_iCtxSubtype == CONST_ctxSubtype_qmcSm) {
        COMMON_PARAM commonParam;
        unsigned  __int64 gid = idInfo.ui64Id;
        int when = 0;

        MACRO_makeCommonParam3(&gid, &when, 0, commonParam);
        if (qTraverse(&pMisCnt->talkingFriendQ, (PF_commonHandler)tmpHandler_canAcceptTalks, &commonParam, 0) == 2) {
            goto errLabel;
        }
    }


    //
#ifdef  __DEBUG__
    IM_CONTENTU* pContent; pContent = M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
    if (pContent->uiType == CONST_imCommType_transferAvInfo) {
        int  ii = 0;
    }
#endif


    //         
    if (!findTalker_shadow(pQyMc, idInfo.ui64Id, iTalkSubtype, &m_hWnd_shadow)) {
        //SetForegroundWindow(m_hWnd_shadow);
    }
    else {
        //
        pProcInfo->tryToTalkToMessenger_any(mynull, idInfo.ui64Id, iTalkSubtype, FALSE, FALSE, &m_hWnd_shadow);

        if (findTalker_shadow(pQyMc, idInfo.ui64Id, iTalkSubtype, &m_hWnd_shadow)) {
            goto errLabel;
        }

    }
    //
    HWND  hMgr; hMgr = mynull;
    if (findTalker(pQyMc, &idInfo, &hMgr))  goto  errLabel;
    dlgTalk_qPostMsg(hMgr, pMsgTask, sizeof(MIS_MSG_TASK));
    //
    ::PostMessage(hMgr, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);

    //
    {
        CHelp_getDlgTalkVar getDlgTalkVar;
        DLG_TALK_var* pMgrVar = (DLG_TALK_var*)getDlgTalkVar.getVar(hMgr);
        if (pMgrVar == mynull)goto  errLabel;
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
    if (pContent->uiType != CONST_imCommType_transferAvInfo) return  -1;// goto errLabel;

    //
    HWND  hMainWnd = pQyMc->gui.hMainWnd;
    CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
    if (pMainWnd == NULL)  return  -1;// goto  errLabel;
    QY_MC_mainWndVar& var = pMainWnd->var.common;



    //
    if (!bDone_retrieveAllImObjRules(pMisCnt))
    {
        showInfo_open0(0, mynull, _T("mainWnd_procMsgInput_transferAvInfo failed, ulbAllImObjRules is false"));
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


        index_taskInfo = newTaskInfoIndex(pProcInfo, CONST_taskDataType_conf, mynull, pMsgTask->iTaskId, _T("mainWnd_procMsgInput_transferAvInfo"));
        if (index_taskInfo < 0)
        {
            traceLog((TCHAR*)_T("mainWnd_procMsgInput_transferAvInfo failed: too many tasks"));
            goto errLabel;

        }
        //
             //            
        QMC_TASK_INFO* tts1 = (QMC_TASK_INFO*)pProcInfo->getQmcTaskInfoByIndex(index_taskInfo);
        if (tts1 == mynull) goto errLabel;

        //
        QMC_taskData_common* pTaskData1 = tts1->var.pTaskData;
        if (pTaskData1 == mynull) goto errLabel;
        //(MIS_MSG_TASK * pMsgTask = &pTaskData.msgU.task)
        {
            //msgInput2Task(pMsgInput, pMsgTask);
            pTaskData1->msgU.task = *pMsgTask;


        }
    }


    //            
    QMC_TASK_INFO* tts; tts = (QMC_TASK_INFO*)pProcInfo->getQmcTaskInfoByIndex(index_taskInfo);
    if (tts == mynull) goto errLabel;

    //
    tts->var.dwTickCnt_recv_lastRefreshed = myGetTickCount(mynull);


    QMC_taskData_common* pTaskData; pTaskData = tts->var.pTaskData;
    if (pTaskData == mynull) goto errLabel;

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
        showInfo_open0(0, mynull, _T("mainWnd_procMsgTask_transferAvInfo failed, qmcTaskInfo_bAlive false"));
        goto  errLabel;

    }


    //        
    if (!bTaskNeedAcception(pMsgTask->iStatus)) {
        showInfo_open0(0, mynull, _T("mainWnd_procMsgTask_transferAvInfo failed, bTaskNeedAcception false"));
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
    if (pContent->uiType != CONST_imCommType_transferFileReq) return  -1;// goto errLabel;

    //
    HWND  hMainWnd = pQyMc->gui.hMainWnd;
    CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
    if (pMainWnd == NULL)  return  -1;// goto  errLabel;
    QY_MC_mainWndVar& var = pMainWnd->var.common;



    //
    if (!bDone_retrieveAllImObjRules(pMisCnt))
    {
        showInfo_open0(0, mynull, _T("mainWnd_procMsgInput_transferFileReq failed, ulbAllImObjRules is false"));
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
            getTalkerDesc(pMsgTask->addr_logicalPeer.idInfo, &uiObjType, mynull, 0, mynull, mynull, 0, mynull, 0, mynull, 0);
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
    int lenInBytes_msg; lenInBytes_msg = offsetof(MIS_MSG_TASK, data) + pMsgTask->lenInBytes;
    pProcInfo->postImMsg2Log_isClient((MIS_MSGU*)pMsgTask, lenInBytes_msg);


    //
    iErr = 0;

errLabel:

    //
    //str = string.Format("mainWnd_procMsgInput_av leaves: from {0}", pMsgInput->data.route.idInfo_from.ui64Id);
    //qyFuncs.showInfo_open0(0, null, str);

    return iErr;

}



