


#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

#include	"qmcVideoCapture_rtsp.h"

#include	"isCliHelpPublic.h"
//#include	"rtspCliHelpPublic.h"
#include	"qmcTaskInfo.h"
#include	"funcsForIsCliHelp.h"
#include    "ctxQmc.h"



     //  检测活跃的视频会议是否已存在，以talkerSubtype_video是否存在为标准
bool  bExists_activeTaskAv(QY_MC  *  pQyMc,  int* piTaskId_activeTaskAv, QY_MESSENGER_ID* pIdInfo_peer)
{
    bool  bRet = false;
    //CCtxQyMc* pQyMc = QY_GET_GBUF();
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    int  index_taskInfo;
    QMC_TASK_INFO* pTaskInfo;

    //
    for (index_taskInfo = 0; index_taskInfo < pProcInfo->cfg.usMaxCnt_taskInfos; index_taskInfo++) {
        pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
        if (!pTaskInfo->bUsed)  continue;
        QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
        MIS_MSG_TASK* pMsgTask = &pTaskData->msgU.task;
        if (pMsgTask->uiType != CONST_misMsgType_task)  continue;
        IM_CONTENTU* pContent = M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
        if (pContent->uiType != CONST_imCommType_transferAvInfo)  continue;
        //
        if (!qmcTaskInfo_bAlive(pProcInfo, index_taskInfo))  continue;
        //
        QY_MESSENGER_ID  idInfo_peer = pMsgTask->addr_logicalPeer.idInfo;
        //
        HWND  hWnd;
        if (findTalker_shadow(pQyMc, idInfo_peer.ui64Id, CONST_talkerSubtype_video, &hWnd))  continue;
        //
        if (piTaskId_activeTaskAv)  *piTaskId_activeTaskAv = pTaskInfo->var.iTaskId;
        if (pIdInfo_peer)*pIdInfo_peer = idInfo_peer;
        //
        bRet = true;  goto  errLabel;

    }

errLabel:
    return  bRet;
}


//
int chkAvStatus()
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

    bool  bExists = bExists_activeTaskAv(pQyMc,  mynull, mynull);
    if (pProcInfo->status.avStatus.bExists_meeting != bExists) {
        pProcInfo->status.avStatus.bExists_meeting = bExists;
    }

    return  0;
}




