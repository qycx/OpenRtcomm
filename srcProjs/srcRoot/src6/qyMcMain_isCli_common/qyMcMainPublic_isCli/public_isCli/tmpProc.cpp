
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


    BOOL tmpHandler_bTask(QY_MC  *  pQyMc,  void * p0,void * p1, TASK_common * taskElem)
        {
            bool bRet = false;
            int iTaskId = (int)p0;
            //p1
            TASK_common *taskMem = (TASK_common*)taskElem;

            //CCtxQyMc *pQyMc = g_pQyMc;
            CCtxQmc *pProcInfo = (CCtxQmc * )pQyMc->get_pProcInfo();

            QMC_TASK_INFO *pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, taskMem->m_index_taskInfo);
            if (pTaskInfo == NULL) return false;

            if ( pTaskInfo->var.pTaskData->msgU.uiType==CONST_misMsgType_task
                && pTaskInfo->var.pTaskData->msgU.task.iTaskId==iTaskId)
            {
                bRet = true;
            }

            return bRet;
        }

        int removeTask(int iTaskId)
        {
            CCtxQyMc *pQyMc = g_pQyMc;
            CCtxQmc *pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

            pProcInfo->processQ_media.qRemoveMsg(tmpHandler_bTask, (void *)iTaskId, NULL);


            return 0;

        }

