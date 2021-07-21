using System;
using System.Collections.Generic;
using System.Text;

namespace qy
{
 
    partial class qyFuncs
{

        public static QY_DMITEM[] CONST_imOpTable_en = new QY_DMITEM[19]
{
    new QY_DMITEM  (   Consts.CONST_imOp_says,                                        (  "says"  )                         ),
 
 new QY_DMITEM(Consts.   CONST_imOp_tryToSendFile,                               (  "tryToSendFile"  )                ),
 //
 new QY_DMITEM(Consts.   CONST_imOp_recv_accept,                                 (  "recv_accept"  )                  ),
 new QY_DMITEM(Consts.   CONST_imOp_recv_deny,                                   (  "recv_deny"  )                    ),
 new QY_DMITEM(Consts.   CONST_imOp_recvFile_saveas,                             (  "recvFile_saveas"  )              ),
 //
 new QY_DMITEM(Consts.   CONST_imOp_recv_cancel,                                 (  "recv_cancel"  )                  ),
 new QY_DMITEM(Consts.   CONST_imOp_send_cancel,                                 (  "send_cancel"  )                  ),
 new QY_DMITEM(Consts.   CONST_imOp_send_permit,                                 (  "send_permit"  )                  ),
 //
 new QY_DMITEM(Consts.   CONST_imOp_dual_permit,                                 (  "dual_permit"  )                  ),
 //
 new QY_DMITEM(Consts.   CONST_imOp_recv_applyForOrgReq,                         (  "recv_applyForOrgReq"  )          ),
 new QY_DMITEM(Consts.   CONST_imOp_recv_applyForChkTaskAlive,                   (  "recv_applyForChkTaskAlive"  )    ),		//  2009/10/19
 new QY_DMITEM(Consts.CONST_imOp_recv_applyForKeyFrame,                         ("recv_applyForKeyFrame")               ),
 //
 //  2009/02/21
 new QY_DMITEM(Consts.   CONST_imOp_requestToSpeak,                              (  "request to speak"  )             ),
 new QY_DMITEM(Consts.   CONST_imOp_stopSpeaking,                                (  "stop speaking"  )                ),

 //  2014/10/09
 new QY_DMITEM(Consts.   CONST_imOp_requestToSend,                               (  "request to send"  )              ),		//  2014/10/09
 new QY_DMITEM(Consts.   CONST_imOp_stopSending,                                 (  "stop sending"  )                 ),		//  2014/10/09

 //

 //
 new QY_DMITEM(Consts.   CONST_imOp_openFile,                                    (  "openFile"  )                     ),
 //
 new QY_DMITEM(Consts.   CONST_imOp_myMax,                                       (  "imOp_myMax"  )                   ),
 //
 new QY_DMITEM(-1,                                                                ""                             ),
 
};


        public static unsafe bool tmpHandler_bTask( CTX_caller ctxCaller,object p0,object p1, object p2)
        {
            bool bRet = false;
            int iTaskId = (int)p0;
            //p1
            TASK_common taskMem = (TASK_common)p2;

            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            QMC_TASK_INFO pTaskInfo = getQmcTaskInfoByIndex(ctxCaller,pProcInfo, taskMem.m_index_taskInfo,"tmpHandler_bTask");
            if (pTaskInfo == null) return false;
            QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
            if (pTaskData == null) return false;

            if ( pTaskData.msgU.uiType==Consts.CONST_misMsgType_task
                && pTaskData.msgU.task.iTaskId==iTaskId)
            {
                bRet = true;
            }

            return bRet;
        }

        public static unsafe int removeTask(CTX_caller ctxCaller, int iTaskId)
        {
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            
            //
            pProcInfo.processQ_media.qRemoveMsg(ctxCaller, tmpHandler_bTask, (object)iTaskId, null);


            return 0;

        }

        public static unsafe void clearShiftKeys()
        {
            traceLog(_T("clearShiftKeys,  test_touchscreen"));
            return;
        }

    }
}
