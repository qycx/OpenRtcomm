
#define  __noDbg_new__


#include "CDlgTalk_qt.h"
#include "MessageData.h"
#include "DBManager.h"
#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon_qt.h"
//#include	"qyMcMainCommon.h"
//  #include	"myresource.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
#include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>

//  #include	"qwmDynFunc.h"

#include	"qmcCmdProc.h"

#include	"tmpCeLib.h"
#include	"qySqlFunc.h"
#include	"qyThread.h"
#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
//
#include	"policyAvParams.h"


#include	"myDb.h"

#include	"isCliCorePublic.h"
#include	"isCliHelpPublic.h"
#include	"qyMessengerHelpPublic.h"
#include	"imgProcessPublic.h"
#include	"isCliD3dPublic.h"
#include	"qisWallsProc.h"
#include	"qmcObjVarPublic.h"
#include	"qmcTaskPublic.h"
#include	"qmcSharePublic.h"
#include	"dlgShareDynBmpsProc.h"
#include	"funcsForIsCliHelp.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliExPublic.h"
#include	"ctxMcThread.h"

//
#include	"qmcVideoTool.h"
#include	"ctxQmc_sm.h"
#include	"policyAvParams.h"
#include	"qyAvRecordPublic.h"
//

//
#include	"qmcCmdProc.h"
#include	"qyMcMainWndProc.h"
#include	<shellapi.h>
#include	"resource.h"  
#include <CMainFrame.h>
#include <QualitySelSetDialog.h>
#include <CDlgTalk_invite_hint.h>
#include    "hgCommProc.h"
#include <smCommProc.h>
#include <dbgFunc_open.h>
//
#include    "confCli_func.h"
//
#include    "myTalkExt.h"
#include    "myQmcExt.h"



//
int  tmpHandler_showMsg_task_qmcCli(void* hDlgTalkParam, DLG_TALK_var& m_var, void* p1, void* pMsgParam);



//
extern  "C"  __declspec(dllexport)  int  parseCmdLine_qyMc(LPCTSTR  pCmdLine, QMC_APP_PARAMS * pParams)
{

    parseCmdLine_qmc_func(pCmdLine, pParams);

    //
    pParams->bSmZy = false;
    //
    pParams->bNoPrompt_mfc = true;
    traceLog((TCHAR*)_T("parseCmdLine_qyMc: bNoPrompt set to true"));

    //
#ifdef  __DEBUG__
#endif


    return  0;

}

//
int  doPre_createConsoleWall(void* p0, void* p1, void* p2)
{
    return  0;
}

//
//  2015/01/20
int  newVar_isCli_gui(void* p0, void* p1, void* p2)
{
    QY_MC* pQyMc = (QY_MC*)p0;
    QY_SERVICEGUI_INFO* pSci = (QY_SERVICEGUI_INFO*)p1;

    CCtxQmc* p = NULL;

    p = new  CCtxQmc_sm;

    if (!p)  return  -1;

    pSci->pVar = p;

    return  0;
}

int  freeVar_isCli_gui(void* p0, void* p1, void* p2)
{
    QY_MC* pQyMc = (QY_MC*)p0;
    QY_SERVICEGUI_INFO* pSci = (QY_SERVICEGUI_INFO*)p1;

    if (pSci->pVar) {
        CCtxQmc* p = (CCtxQmc*)pSci->pVar;
        delete  p;
        pSci->pVar = NULL;
    }

    return  0;
}




//
CCtxQmc_sm::CCtxQmc_sm()
{
    //  2014/02/08
    this->m_iCtxType = CONST_ctxType_qmc;
    //
    this->m_iCtxSubtype = CONST_ctxSubtype_qmcSm;

    //
#ifdef  __DEBUG__
    //this->test1 = 567;
    //this->test2 = 901;

    //
    //218.240.128.210
#endif

    //
    int  size = &this->_bEnd - &this->_start;
    memset(&this->_start, 0, size);

    //
    memset(&m_var, 0, sizeof(m_var));

    //
    this->cfg.ucb_talkToMsgr_manually = true;

    //
    this->cfg.maxTimes_noXtResp3 = 3;

    //
    this->cfg.ucb_closeTalkIfNoConf = true;

    //
#ifdef  __DEBUG__
        //
#if  10
        this->m_var.b_app_showNormal = false;// true;in
        //
        this->m_var.b_app_testSize_forDebug = false;// true;//;
        //
        this->m_var.b_app_noChkXtResp_forDebug = true;
#endif
        //
#endif

    //
    QString qstr = getInstallDir_qt();
    safeTcsnCpy((TCHAR*)qstr.utf16(), m_var.installDir_qt, mycountof(m_var.installDir_qt));

    //



    //
    return;

}

CCtxQmc_sm::~CCtxQmc_sm()
{
    int  i = 0;
    if (m_var.pDBManager) {
        DBManager* p = (DBManager*)m_var.pDBManager;
        delete  p;
        m_var.pDBManager = mynull;
    }

}




TalkExtTmpl* CCtxQmc_sm::new_talkExt()
{
    return  new myTalkExt();
}

QmcExtTmpl* CCtxQmc_sm::new_qmcExt()
{
    return  new myQmcExt();
}



//
int  CCtxQmc_sm::getAuthType()
{
    //
    int iAuthType  =  CONST_authType_bjca;

    //
    int tmp_authType = m_var.ctxSm.smTerminalInitCfg.authType;
    if (tmp_authType) {
        iAuthType = tmp_authType;
    }

    //
    return  iAuthType;
}






//
int  CCtxQmc_sm::setQmDbFuncs(int  iDbType, QM_dbFuncs* pDbFuncs)
{
    return  ::setQmDbFuncs_qm(iDbType, pDbFuncs);
}


//



//
int  qyMc_setQmDbFuncs(int  iDbType, QM_dbFuncs* pDbFuncs)
{
    return  ::setQmDbFuncs_qm(iDbType, pDbFuncs);
}



//
int  CCtxQmc_sm::initInfrared()
{
    startInfraredThread();

    return  0;
}


int  CCtxQmc_sm::exitInfrared()
{
    stopInfraredThread();

    return  0;
}

//
int CCtxQmc_sm::channelsInit(Param_channelsInit* pParam, MIS_CNT* pMisCnt)
{
    return  confCli_channelsInit(pParam, pMisCnt);
}


int CCtxQmc_sm::channelsExit(MIS_CNT* pMisCnt)
{
    confCli_channelsExit(pMisCnt);
    return  0;
}


//
int  CCtxQmc_sm::loadCusModules(void* pQyMcParam)
{
    return  ::loadCusModules(pQyMcParam);
}


int  CCtxQmc_sm::unloadCusModules(void* pQyMcParam)
{
    return  ::unloadCusModules(pQyMcParam);
}

//
int  CCtxQmc_sm::initCusModules(void* pQyMcParam)
{
    return  ::initCusModules(pQyMcParam);

}


int  CCtxQmc_sm::startCusModules(void* pQyMcParam)
{
    return  ::startCusModules(pQyMcParam);
}


int  CCtxQmc_sm::stopCusModules(void* pQyMcParam)
{
    return  ::stopCusModules(pQyMcParam);
}



//
int  CCtxQmc_sm::initVar_post(void* p0, void* p1, void* p2)
{
  

    //
    return  0;
}

int  CCtxQmc_sm::exitVar_pre(void* p0, void* p1, void* p2)
{
    return  0;
}


int  CCtxQmc_sm::exitVar_post(void* p0, void* p1, void* p2)
{
    return  0;
}



//
int  CCtxQmc_sm::qyShowMainWndFunc(HWND  hMainWnd, void* pVar, BOOL  bShow)
{
    //return  ::qyShowMainWndFunc_cli(hMainWnd, pVar, bShow);
    return  -1;
}


//
int  CCtxQmc_sm::postMsg2Mgr_mc(void* pMIS_CNT, MSG_ROUTE* pRoute, unsigned  int  uiMisMsgType, unsigned  char  ucFlg, unsigned  short  usCode, time_t  tStartTime, unsigned  int  uiTranNo, unsigned  int  uiSeqNo, char* data, unsigned  int  dataLen, QY_MESSENGER_ID* pIdInfo_logicalPeer, QY_MESSENGER_ID* pIdInfo_dst, unsigned  int  uiChannelType, MIS_MSGU* pMsgBuf, BOOL  bLog)
{
    return  ::postMsg2Mgr_mc(pMIS_CNT, pRoute, uiMisMsgType, ucFlg, usCode, tStartTime, uiTranNo, uiSeqNo, data, dataLen, pIdInfo_logicalPeer, pIdInfo_dst, uiChannelType, pMsgBuf, bLog);
}


//
int  CCtxQmc_sm::postMsgTask2Mgr_mc(void* pMIS_CNT, unsigned  int  uiMisMsgType, unsigned  char  ucFlg, unsigned  short  usCode, time_t  tStartTime, unsigned  int  uiTranNo, unsigned  int  uiSeqNo, int  iTaskId, unsigned  int  uiTaskType, char* data, unsigned  int  dataLen, QY_MESSENGER_ID* pIdInfo_logicalPeer, QY_MESSENGER_ID* pIdInfo_taskSender, QY_MESSENGER_ID* pIdInfo_taskReceiver, QY_MESSENGER_ID* pIdInfo_dst, unsigned  int  uiChannelType, MIS_MSGU* pMsgBuf, BOOL  bLog)
{
    return  ::postMsgTask2Mgr_mc(pMIS_CNT, uiMisMsgType, ucFlg, usCode, tStartTime, uiTranNo, uiSeqNo, iTaskId, uiTaskType, data, dataLen, pIdInfo_logicalPeer, pIdInfo_taskSender, pIdInfo_taskReceiver, pIdInfo_dst, uiChannelType, pMsgBuf, bLog);
}


//
int  CCtxQmc_sm::postImMsg2Log_isClient(MIS_MSGU* pMsg, int  lenInBytes_msg)
{
    return  ::postImMsg2Log_isClient(pMsg, lenInBytes_msg);
}




//
int  CCtxQmc_sm::recoverMessenger(QM_dbFuncs* pDbFuncs, void* pDb, int  iDbType, QY_DMITEM* pFieldIdTable, QY_MESSENGER_INFO* pObj, QY_MESSENGER_REGINFO* pRegInfo, time_t  tLastModifiedTime, BOOL  bLog, GENERIC_Q* pLogQ)
{
    return  ::recoverMessenger(pDbFuncs, pDb, iDbType, pFieldIdTable, pObj, pRegInfo, tLastModifiedTime, bLog, pLogQ);
}


//
int  CCtxQmc_sm::recoverImObjRules(QM_dbFuncs* pDbFuncs, void* pDb, int  iDbType, LPCTSTR  misServName, QY_MESSENGER_ID* pIdInfo, REFRESH_imObjRules_req* pReq, time_t  tLastModifiedTime)
{
    return  ::recoverImObjRules(pDbFuncs, pDb, iDbType, misServName, pIdInfo, pReq, tLastModifiedTime);
}

//
int  CCtxQmc_sm::recoverImGrp(QM_dbFuncs* pDbFuncs, void* pDb, int  iDbType, QY_DMITEM* pFieldIdTable, unsigned  int  uiObjType, IM_GRP_INFO* pGrpInfo, time_t  tLastModifiedTime, BOOL  bNoGrpName)
{
    return  ::recoverImGrp(pDbFuncs, pDb, iDbType, pFieldIdTable, uiObjType, pGrpInfo, tLastModifiedTime, bNoGrpName);
}


//
int  CCtxQmc_sm::recoverImGrpMem(QM_dbFuncs* pDbFuncs, void* pDb, int  iDbType, IM_GRP_MEM* pGrpMem, time_t  tLastModifiedTime)
{
    return  ::recoverImGrpMem(pDbFuncs, pDb, iDbType, pGrpMem, tLastModifiedTime);
}


//
//	
FUNCS_for_isCliHelp* CCtxQmc_sm::FUNCS_for_isCliHelp_new()
{
    safeTcsnCpy(_T("isCliD3d.dll"), this->cfg.isCliD3dFileName, mycountof(this->cfg.isCliD3dFileName));
    //
    return  ::FUNCS_for_isCliHelp_new(this->pQyMc);
}


//
void  CCtxQmc_sm::FUNCS_for_isCliHelp_free(void** ppFuncs)
{
    ::FUNCS_for_isCliHelp_free(ppFuncs);
    return;
}

//
int CCtxQmc_sm::newTaskAvOutput()
{
    return  confCli_newTaskAvOutput(this);

}


//
int CCtxQmc_sm::initTaskAvOutput(int  iTaskId, MuxStreamsCfg* pMuxStreamsCfg, PROC_TASK_AV* pTaskAv)
{
    //
    CCtxQmc* pProcInfo = this;
    int  iErr = -1;

    //
    do {
        //
        if (confCli_initTaskAvOutput(this, iTaskId, pMuxStreamsCfg, pTaskAv)) {
            break;
        }

        iErr = 0;
    } while (false);

    //
    return  iErr;
}


int CCtxQmc_sm::exitTaskAvOutput(int  iTaskId, PROC_TASK_AV* pTaskAv)
{
    //
    confCli_exitTaskAvOutput(this, iTaskId, pTaskAv);

    //
    return  0;
}








//  2016/09/08
int  CCtxQmc_sm::tryToTalkToMessenger_any(HWND hParent, unsigned  __int64  ui64Id, int  iTalkSubtype, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
    return  ::tryToTalkToMessenger_any(hParent, ui64Id, iTalkSubtype, bNeedNotShowWnd, bActivateWnd, phWnd);
}


//
int  CCtxQmc_sm::talkToMessenger(unsigned  __int64  ui64Id, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
    return  ::talkToMessenger(ui64Id, 0, bNeedNotShowWnd, bActivateWnd, phWnd);

}


//  
int  CCtxQmc_sm::doApplyForPlayer(HWND  hMainWnd, MIS_MSGU* pMsg)
{
    return  ::doApplyForPlayer(g_pQyMc,hMainWnd, pMsg);
}

//
int  CCtxQmc_sm::removeMosaicFromD3dWall(int  iIndex_sharedObj)
{
    return  ::dyn_removeMosaicFromD3dWall(this, iIndex_sharedObj);
}

int  CCtxQmc_sm::getVal_bExists_mosaic(int  iIndex_sharedObj, BOOL* pbExists)
{
    return  ::dyn_getVal_bExists_mosaic(this, iIndex_sharedObj, pbExists);
}

//
int  CCtxQmc_sm::stopLocalAudioRecorder(int  index_sharedObj, int  nTries)
{
    return  ::stopLocalAudioRecorder(this, index_sharedObj, nTries);
}

//
int  CCtxQmc_sm::talkToMessenger(void* pQyMcParam, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkUsage, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
    return ::talkToMessenger_qt(pQyMcParam, pAddr, pTmpGrpMemQ, iTalkUsage, bNeedNotShowWnd, bActivateWnd, phWnd);
}

void* CCtxQmc_sm::tmp_getDlgTalkVar(HWND  hDlgTalk)
{
    return  ::tmp_getDlgTalkVar_qt(hDlgTalk);
}

int  CCtxQmc_sm::getTalkerShadow(HWND  hParent, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkerSubType, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
    return  ::getTalkerShadow_qt(hParent, pAddr, pTmpGrpMemQ, iTalkerSubType, bNeedNotShowWnd, bActivateWnd, phWnd);
}

int  CCtxQmc_sm::do_addToRecentMsg(HWND  hDlgTalk, void* pDLG_TALK_var, long  lRowIndex, int  iTaskId, MIS_MSGU* pMsgU, MIS_MSG_taskStatus  *  pMsgTaskStatus,  QY_MESSENGER_ID idInfo_talker, LPCTSTR  talkerDesc, unsigned  short  usOp, int  iStatus, char* timeBuf, LPCTSTR  rowIdStr, LPCTSTR  content, BOOL  bFollowingRows, BOOL  bScrollIntoView, TCHAR* txtBuf, unsigned  int  uiTxtBufCnt)
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
    DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;
    QY_MESSENGER_ID* pIdInfo_talker = &idInfo_talker;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

    //
    MIS_MSG_TASK* pMsgTask = NULL;
    MIS_MSG_TALK* pMsgTalk = NULL;
    if (pMsgU) {
        switch (pMsgU->uiType) {
        case  CONST_misMsgType_task:
            pMsgTask = &pMsgU->task;
            break;
        case  CONST_misMsgType_talk:
            pMsgTalk = &pMsgU->talk;
            break;
        default:
            break;

        }
    }

    //
    CDlgTalk_qt* cdlgTalkqt = mynull;
    cdlgTalkqt = (CDlgTalk_qt*)QWidget::find((WId)hDlgTalk);
    if (!cdlgTalkqt) return  -1;
    qDebug() << QString::fromStdWString(content);
    DLG_TALK_var* pm_var = (DLG_TALK_var*)pDLG_TALK_var;
    unsigned  int puiObjType;
    int chatType = 0;
    //判断消息类型
    getTalkerDesc(pm_var->addr.idInfo, &puiObjType, mynull, 0, mynull, mynull, 0, mynull, 0, mynull, 0);
    if (puiObjType == CONST_objType_imGrp) {
        chatType = 1;
    }
    //这是发文件的时候操作
    if (iTaskId) {
        int index_taskInfo = ::getQmcTaskInfoIndexBySth(pProcInfo, iTaskId);
        QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(index_taskInfo);
        if (pTaskInfo == mynull) {
            if (pMsgTask == mynull) {
                //
#if  1
                if (iStatus == CONST_imTaskStatus_canceledBySender) {

                    QList<MessageData> messFind = pDm->getMessagesFind(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId);
                    //
                    if (messFind.size() > 0)
                    {
                        if (messFind[0].fromUserId  != QString::number(pMisCnt->idInfo.ui64Id)) {


                            if (isTalkerShadowMgr(pm_var->addr)) {

                                bool res = pDm->updateMessage(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId, 1, 0);
                            }

                        }
                    }

                    {
                        //                
                        QList<MessageData> messFind = pDm->getMessagesFind(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId);
                        if (messFind.size() > 0) {
                            cdlgTalkqt->showFileProgress(messFind[0].messageId, u8"发送者取消", iStatus, 0);
                        }
                    }

                }
              
#endif
                //
                goto  errLabel;
            }
            //对方当前窗口发送文件
           /* IM_CONTENTU* pContent = M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
            if (pContent == null)goto  errLabel;
            if (pContent->uiType == CONST_imCommType_transferFileReq) {
                int  ii = 0;
            }*/

            QString msgid = QString::number(pIdInfo_talker->ui64Id) + "-" + QString::number(pMsgTask->tStartTime) + "-" + QString::number(pMsgTask->uiTranNo);
            cdlgTalkqt->addShowMsg(QString::fromStdWString(content), pIdInfo_talker->ui64Id, 0, msgid, 1, iTaskId);

        }
        else {

            QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
            if (pTaskData == mynull)  goto  errLabel;
            MIS_MSG_TASK* pMsgTask = &pTaskData->msgU.task;
            if (pMsgTask->uiType != CONST_misMsgType_task)  goto  errLabel;
            //
                       
            IM_CONTENTU* pContent = M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
            if (pContent == mynull)goto  errLabel;
            if (pContent->uiType == CONST_imCommType_transferAvInfo) {

                if (pIdInfo_talker) {
                    if (pContent->transferAvInfo.confCfg.idInfo_initiator.ui64Id == 0) {
                        QString msgid = QString::number(pIdInfo_talker->ui64Id) + "-" + QString::number(pMsgTask->tStartTime) + "-" + QString::number(pMsgTask->uiTranNo);
                        cdlgTalkqt->addShowMsg(QString::fromStdWString(content), pIdInfo_talker->ui64Id, 0, msgid, 2, iTaskId, 0, chatType, 0);
                    }
                    else {

                        if (iStatus !=  CONST_imTaskStatus_waitToRecv) {
                            QString msgid = QString::number(pContent->transferAvInfo.confCfg.idInfo_initiator.ui64Id) + "-" + QString::number(pMsgTask->tStartTime) + "-" + QString::number(pMsgTask->uiTranNo);
                            cdlgTalkqt->addShowMsg(QString::fromStdWString(content), pContent->transferAvInfo.confCfg.idInfo_initiator.ui64Id, 0, msgid, 2, iTaskId, 0, chatType, 0);
                        }
                    }
                    
                }
                
            }
            else if (pContent->uiType == CONST_imCommType_transferFileReq) {
                
                //
                QString msgid = QString::number(pIdInfo_talker->ui64Id) + "-" + QString::number(pMsgTask->tStartTime) + "-" + QString::number(pMsgTask->uiTranNo);
                
                    if (iStatus == CONST_imTaskStatus_receiving) 
                    {
                        QString msgid = QString::number(pMsgTask->idInfo_taskSender.ui64Id) + "-" + QString::number(pMsgTask->tStartTime) + "-" + QString::number(pMsgTask->uiTranNo);
                        QList<MessageData> is_msg = pDm->getMessagesMidFind(QString::number(pm_var->addr.idInfo.ui64Id) , msgid);
                        if (is_msg.size() == 0) {
                            cdlgTalkqt->addShowMsg(QString::fromStdWString(content), pIdInfo_talker->ui64Id, 0, msgid, 1, iTaskId, 0, chatType, 0);
                        }
                        cdlgTalkqt->showFileProgress(msgid, QString::fromStdWString(std::wstring(content)), iStatus, pMisCnt->idInfo.ui64Id);
                        //cdlgTalkqt->addShowMsg(QString::fromStdWString(content), pIdInfo_talker->ui64Id, 0, msgid, 1, iTaskId, 0, chatType, 0);
                    }
                    else if(iStatus == CONST_imTaskStatus_sending || iStatus == CONST_imTaskStatus_waitToSend)
                    {
                        QString msgid = QString::number(pMsgTask->idInfo_taskSender.ui64Id) + "-" + QString::number(pMsgTask->tStartTime) + "-" + QString::number(pMsgTask->uiTranNo);
                        QList<MessageData> is_msg = pDm->getMessagesMidFind(QString::number(pm_var->addr.idInfo.ui64Id), msgid);
                        if (is_msg.size() == 0) {
                            cdlgTalkqt->addShowMsg(QString::fromStdWString(content), pIdInfo_talker->ui64Id, 0, msgid, 1, iTaskId, 0, chatType, 0);
                        }
                        cdlgTalkqt->showFileProgress(msgid, QString::fromStdWString(std::wstring(content)), iStatus, pIdInfo_talker->ui64Id);
                       // 
                    }
                    else {
                        //判断  传输完成后更新数据库状态
                        if (CONST_imTaskStatus_recvFinished == iStatus)
                        {
                            // if (pm_var->addr.uiObjType != CONST_objType_imGrp) {
                            if (isTalkerShadowMgr(pm_var->addr)) {
                                //发送完成 改状态
                                bool res = pDm->updateMessage(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId, 0, 1);
                            }
                            //发送者
                            QList<MessageData> messFind = pDm->getMessagesFind(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId);
                            //
                            if (messFind.size() > 0)
                            {
                                cdlgTalkqt->showFileProgress(messFind[0].messageId, u8"接收完成", iStatus, pMsgTask->data.route.idInfo_to.ui64Id);
                            }
                        }
                        //
                        if (CONST_imTaskStatus_sendFinished == iStatus )
                        {
                            if (pm_var->addr.uiObjType != CONST_objType_imGrp) {
                                if (isTalkerShadowMgr(pm_var->addr)) {
                                    //发送完成 改状态
                                    bool res = pDm->updateMessage(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId, 0, 1);
                                }
                            }

                            //发送显示状态
                            if (pm_var->addr.uiObjType != CONST_objType_imGrp)
                            {
                                QList<MessageData> messFind = pDm->getMessagesFind(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId);
                                //
                                if (messFind.size() > 0)
                                {
                                    cdlgTalkqt->showFileProgress(messFind[0].messageId, u8"接收完成", iStatus, pMsgTask->data.route.idInfo_to.ui64Id);
                                }
                            }

                            else 
                            {
                                
                                QList<MessageData> messFind = pDm->getMessagesFind(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId);
                                //
                                if (messFind.size() > 0)
                                {
                                    cdlgTalkqt->showFileProgress(messFind[0].messageId, u8"接收完成", iStatus, pMsgTask->data.route.idInfo_to.ui64Id);
                                    
                                    cdlgTalkqt->addShowMsg(QString::fromStdWString(content), pIdInfo_talker->ui64Id, 0, msgid, 0, 0, 0, chatType, 0);
                                }
                            }

                                    
                                
                          
                        }
                        if (iStatus == CONST_imTaskStatus_canceledBySender) {

                            if (isTalkerShadowMgr(pm_var->addr)) {
                                bool res = pDm->updateMessage(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId, 1, 0);
                            }

                            //发送者取消
                            QList<MessageData> messFind = pDm->getMessagesFind(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId);
                            //
                            if  (  messFind.size()>0)
                            {
                                cdlgTalkqt->showFileProgress(messFind[0].messageId, u8"发送者已取消", iStatus, pMsgTask->data.route.idInfo_to.ui64Id);
                            }
                            
                        }
                        if (iStatus == CONST_imTaskStatus_canceledByReceiver)
                        {
                            //接收者取消
                            
                             //
                            if (pm_var->addr.uiObjType != CONST_objType_imGrp)
                            {
                                if (isTalkerShadowMgr(pm_var->addr)) {
                                    bool res = pDm->updateMessage(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId, 1, 0);
                                }
                            }

                            if (pm_var->addr.uiObjType != CONST_objType_imGrp)
                            {
                                QList<MessageData> messFind = pDm->getMessagesFind(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId);
                                //
                                if (messFind.size() > 0)
                                {
                                    cdlgTalkqt->showFileProgress(messFind[0].messageId, u8"接收者已取消", iStatus, pMsgTask->data.route.idInfo_to.ui64Id);
                                }
                            }
                            else {
                                QList<MessageData> messFind = pDm->getMessagesFind(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId);
                                //
                                if (messFind.size() > 0)
                                {
                                    cdlgTalkqt->showFileProgress(messFind[0].messageId, u8"接收者已取消", iStatus, pMsgTask->data.route.idInfo_to.ui64Id);
                                }
                            }

                        }
                        //todo 参数需要改进
                     /*   QList<MessageData> messFind = pDm->getMessagesFind(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId);
                        if (messFind.size() > 0) {

                            cdlgTalkqt->showFileProgress(messFind[0].messageId, QString::fromStdWString(std::wstring(content)), iStatus, pMsgTask->data.route.idInfo_to.ui64Id);
                        }*/
                    }
                
            }
        }
    }
    else {
        if (!pMsgTalk) {
            goto  errLabel;
        }
        QString msgid = QString::number(pIdInfo_talker->ui64Id) + "-" + QString::number(pMsgTalk->tStartTime) + "-" + QString::number(pMsgTalk->uiTranNo);
        //这是普通文字消息
         cdlgTalkqt->addShowMsg(QString::fromStdWString(content), pIdInfo_talker->ui64Id, 0, msgid, 0, 0, 0, chatType, 0);
    }

    //


errLabel:

    return  0;
}


//
int  CCtxQmc_sm::do_talk_OnTimer(HWND  hDlgTalk,void *pDLG_TALK_var)
{
    DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)pDLG_TALK_var;
    if (!pDlgTalkVar) return -1;
    CCtxQyMc* pQyMc = g_pQyMc;
    if (!pQyMc)  return  -1;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return  -1;

    //
    CDlgTalk_qt* cdlgTalkqt = mynull;
    cdlgTalkqt = (CDlgTalk_qt*)QWidget::find((WId)hDlgTalk);
    if (!cdlgTalkqt) return  -1;
    //MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    //

    cdlgTalkqt->doTimerProc();

    //
    conf_chkAvDev(hDlgTalk, pDLG_TALK_var);

    //
    if (isTalkerShadowMgr(pDlgTalkVar->addr)) {
        if (pDlgTalkVar->av.taskInfo.bTaskExists) {
            int  iDiffInMs = myGetTickCount(mynull) - pProcInfo->av.localAv.dwLastTickCnt_vCap;
            if (iDiffInMs > 10000) {
                pProcInfo->av.localAv.chkCamera.mTimes_lostVideo++;
            }
            else {
                 pProcInfo->av.localAv.chkCamera.mTimes_lostVideo = 0;
                 //
                 pProcInfo->av.localAv.chkCamera.mTimes_noCamera = 0;
            }
            //
            if (pProcInfo->av.localAv.chkCamera.mTimes_lostVideo > 10) {  //  摄像头没有正常工作
                pProcInfo->av.localAv.chkCamera.mTimes_lostVideo = 0;  //  清0，避免下一次误判
                //
                if (pProcInfo->uiTerminalType == CONST_terminalType_mon) {
                    qmcLogStatus(_T("do_talk_OnTimer"), 0, _T("摄像头没有正常工作,自动关闭会议"));
                    //
                    PostMessage(hDlgTalk, WM_CLOSE, 0, 0);
                    //
                    pProcInfo->av.localAv.chkCamera.mTimes_noCamera++;
                }
            }
        }
    }


    //
    return  0;
}


//
int CCtxQmc_sm::do_talk_shareDevice(HWND  hDlgTalk, void* pDLG_TALK_var, bool  bEnable, bool bSaveSpeakState)
{
    CDlgTalk_qt* cdlgTalkqt = mynull;
    cdlgTalkqt = (CDlgTalk_qt*)QWidget::find((WId)hDlgTalk);
    if (!cdlgTalkqt) return  -1;

    DLG_TALK_var* pCurVar = cdlgTalkqt->get_pm_var();
    if (!pCurVar) return -1;

    if (!isTalkerShadowMgr(pCurVar->addr))  return  -1;

    //
    if (bEnable) {
        cdlgTalkqt->do_shareDevice(bEnable,bSaveSpeakState);
    }

    //
    return  0;
}



//
int  CCtxQmc_sm::do_talk_afterInit(HWND  hDlgTalk)
{
    //
    CDlgTalk_qt* cdlgTalkqt = mynull;
    cdlgTalkqt = (CDlgTalk_qt*)QWidget::find((WId)hDlgTalk);
    if (!cdlgTalkqt) return  -1;

    //
    cdlgTalkqt->do_afterInit();

    //
    return  0;
}


int  CCtxQmc_sm::do_talk_refreshLayout(HWND  hDlgTalk)
{
    CDlgTalk_qt* cdlgTalkqt = mynull;
    cdlgTalkqt = (CDlgTalk_qt*)QWidget::find((WId)hDlgTalk);
    if (!cdlgTalkqt) return  -1;

    cdlgTalkqt->refreshLayout();

    return  0;
}



//
bool CCtxQmc_sm::myDestroyWindow(HWND  hWnd)
{
    bool bRet = false;

    //
    QY_WMBUF_COMM  wmBuf;
    memset(&wmBuf, 0, sizeof(wmBuf));
    int  lRet;
    lRet = ::SendMessage(hWnd, CONST_qyWm_comm, CONST_qyWmParam_getObjAddr, (LPARAM)&wmBuf);
    if (lRet != CONST_qyWmRc_ok) goto errLabel;

    QWidget* pWnd; pWnd = (QWidget*)wmBuf.u.getObjAddr.pObjAddr;

    if (pWnd == NULL) goto  errLabel;

    pWnd->close();
    delete pWnd;

    //
    bRet = true;

errLabel:

    //
    return bRet;
}


//
extern  "C"  int  getDirAndFinalName_qt(LPCTSTR  svFileName, TCHAR * dirName, unsigned  int  size, TCHAR * finalName, unsigned  int  finalNameSize)
{
    TCHAR* pFinalModuleName = NULL;

    if (!svFileName || !lstrlen(svFileName))  return  -1;

    pFinalModuleName = (TCHAR*)_tcsrchr(svFileName, _T('/'));
    if (pFinalModuleName) {
        if (finalName && finalNameSize)  lstrcpyn(finalName, pFinalModuleName + 1, finalNameSize);
        if (dirName && size)  lstrcpyn(dirName, svFileName, std::min(size, (unsigned  int)(pFinalModuleName - svFileName + 2)));
        return  0;
    }

    return  -1;
}


//
int  CCtxQmc_sm::getDirAndFinalName(LPCTSTR  svFileName, TCHAR* dirName, unsigned  int  size, TCHAR* finalName, unsigned  int  finalNameSize)
{
    return  ::getDirAndFinalName_qt(svFileName, dirName, size, finalName, finalNameSize);

}



int CCtxQmc_sm::do_test(HWND  hWnd, int  iWndContentType)
{
    CCtxQyMc* pQyMc = QY_GET_GBUF();

#ifdef  __DEBUG__
    //HWND  hMainWnd = pQyMc->gui.hMainWnd;

    CDlgTalk_qt* pWnd = (CDlgTalk_qt*)getObjAddr(hWnd);
    if (pWnd)
        DLG_TALK_var* pm_var = pWnd->get_pm_var();

    //
#if 0
    TCHAR  tBuf[128];
    _sntprintf(tBuf, mycountof(tBuf), _T("timer:talk%I64u, tn %d, subtype %d"), pm_var->addr.idInfo.ui64Id, pm_var->addr.uiTranNo_shadow, pm_var->iTalkerSubType);
    showInfo_open0(0, _T(""), tBuf);
#endif

#endif


    return 0;
}


//
int CCtxQmc_sm::initDBManager(void* pDBManager)
{
    int  iErr = -1;
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

    //
#if 0
    this->m_var.pDBManager = new DBManager();
    if (m_var.pDBManager == null)  goto  errLabel;
#endif
    DBManager* pDm = (DBManager*)pDBManager;
    if (!pDm) return -1;

    //
    qint64 uid = pMisCnt->idInfo.ui64Id;
    //DBManager::Instance().initDB(QString::number(uid));
    pDm->initDB(QString::number(uid));

    //
#ifdef  __DEBUG__
    traceLog((TCHAR*)_T("do_initDb ok"));
#endif


    iErr = 0;

errLabel:
    //
    return  iErr;
}


//
int  CCtxQmc_sm::do_dlgTalk_procTask_transferAvInfo(HWND  hTalk)
{
    //
    CDlgTalk_qt* pDlgTalk = (CDlgTalk_qt*)CDlgTalk_qt::find((WId)hTalk);
    if (!pDlgTalk)return  -1;
    DLG_TALK_var* pm_var = pDlgTalk->get_pm_var();
    if (!pm_var)return  -1;

    int  iTalkSubtype = CONST_talkerSubtype_video;
    HWND  m_hWnd_shadow;

    if (findTalker_shadow(pQyMc, pm_var->addr.idInfo.ui64Id, iTalkSubtype, &m_hWnd_shadow))
    {
        return -1;
    }
    CDlgTalk_qt* video_cdlgTalkqt = (CDlgTalk_qt*)getObjAddr(m_hWnd_shadow);
    if (!video_cdlgTalkqt)
    {
        return -1;
    }



    video_cdlgTalkqt->viewCompereControl();
    //
    return  0;
}



//
#ifdef  __DEBUG__
//
int test_recentFriends(CCtxQmc_sm  *  pProcInfo)
{
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    QY_MESSENGER_ID  idInfo;

    //
    idInfo.ui64Id = 170;
    isCli_addTo_qmObjQ(idInfo);
    //
    idInfo.ui64Id = 171;
    isCli_addTo_qmObjQ(idInfo);
    //
    idInfo.ui64Id = 172;
    isCli_addTo_qmObjQ(idInfo);
    //
    idInfo.ui64Id = 117;
    isCli_addTo_qmObjQ(idInfo);




    //
    printQmObjQ((QM_OBJQ*)pMisCnt->pObjQ);



    //
    idInfo.ui64Id = 117;
    postRecentFriend(pMisCnt, idInfo, 0);
    idInfo.ui64Id = 172;
    postRecentFriend(pMisCnt, idInfo, 0);

   
    //
    pMisCnt->refreshRecentFriends.bRefreshAtOnce = true;


    //
    return  0;
}
//
#endif

// 获取内存占用率
float GetMemoryUsage() {
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(MEMORYSTATUSEX); // 必须初始化结构体大小

    if (GlobalMemoryStatusEx(&memStatus)) {
        // 总物理内存（字节）
        DWORDLONG totalPhys = memStatus.ullTotalPhys;
        // 可用物理内存（字节）
        DWORDLONG freePhys = memStatus.ullAvailPhys;

        //
        if (totalPhys == 0)  return  -1.;

        // 计算占用率（百分比）
        float usage = (1.0f - static_cast<float>(freePhys) / static_cast<float>(totalPhys)) * 100.0f;
        return usage;
    }
    else {
        return -1.0f; // 返回错误码
    }
}

//
int  CCtxQmc_sm::do_mainWnd_OnTimer(HWND  hMainWnd, void* pVar, UINT  nIDEvent)
{
    if (!pVar)  return  -1;
    QY_MC_mainWndVar& var = *(QY_MC_mainWndVar*)pVar;
#ifdef  __DEBUG__
    //test_recentFriends(this);
#endif

    if (!(var.loopCtrl % 5)) {
        //
        qmcChkSmTmpLogFile();
    }

    //
    if (!(var.loopCtrl % 30)
        ||  this->m_var.bNeedRetrievePlans  ) 
    {
        //
        m_var.bNeedRetrievePlans = false;

        //
        startToRetrievePlans();
    }

    //
    MIS_CNT* pMisCnt = this->getMisCntByName(_T(""));
    if (pMisCnt) {
        if (!isQEmpty(&pMisCnt->talkingFriendQ)) 
        {
            mainWnd_chkIpcProc(var.loopCtrl);
        }
    }

    //
    chkInfraredThread();

    //
    if (!(var.loopCtrl % 5)) 
    {
        QY_REG  reg;
        TCHAR  tBuf[128];

        memset(&reg, 0, sizeof(reg));
        reg.hKeyRoot0 = HKEY_CURRENT_USER;
        lstrcpyn(reg.rootKey, CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), mycountof(reg.rootKey));

        //
        int  nQNodes = pQyMc->gui.processQ.uiQNodes;
        bool  bWarn_processQ = isQFull(&pQyMc->gui.processQ);
        bWarn_processQ  =  isQWarning(&pQyMc->gui.processQ, 20);
        
        //
        float fMemUsage;
        fMemUsage  =  GetMemoryUsage();
        bool  bWarn_mem = false;
        if (fMemUsage > 90) {
            bWarn_mem = true;
            //
            showInfo_open0(0, 0, _T("do_mainWnd_OnTimer: bWarn_mem true"));
        }

        
        //
#ifdef  __DEBUG__        

        //
        if (0) {
            traceLog((TCHAR*)_T("do_mainWnd_OnTimer: for test, bWarn_processQ set true"));
            bWarn_processQ = true;
        }
        //
        if (0) {
            traceLog((TCHAR*)_T("do_mainWnd_OnTimer: for test, bWarn_mem set true"));
            bWarn_mem = true;
        }

#endif
        //
        int  sm_loopCtrl = var.loopCtrl;
        //
        if (bWarn_processQ  ||  bWarn_mem) {
            sm_loopCtrl = 999;
            //
            if (bWarn_processQ) {
                _sntprintf(tBuf, mycountof(tBuf), _T("err: bWarn_processQ is true. qNodes_processQ %d"), nQNodes);
                logStatus(pQyMc->cfg.qmcLogFile, _T("sm"), _T("do_mainWnd_OnTimer"), 0, tBuf);
            }
            if (bWarn_mem) {
                _sntprintf(tBuf, mycountof(tBuf), _T("do_mainWnd_OnTimer: bWarn_mem true: fMemUsage %f"), fMemUsage);
                logStatus(pQyMc->cfg.qmcLogFile, _T("sm"), _T("do_mainWnd_OnTimer"), 0, tBuf);
            }
        }
        //
        TCHAR  *  pRegVal = (  TCHAR  *  )_T(CONST_regValName_sm_loopCtrl);
        qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  _ltot(  sm_loopCtrl,  tBuf,  10  )  );

        //
#ifdef  __DEBUG__
        //
        _sntprintf(tBuf, mycountof(tBuf), _T("do_mainWnd_OnTimer: save sm_loopCtrl %d. nQNodes_processQ %d"), sm_loopCtrl,  nQNodes);
        traceLog(tBuf);
#endif
    }


    //
    return  0;
}


//
int  CCtxQmc_sm::displayRecentFriends(MIS_MSG_displayRecentFriends_qmc* pMsg)
{
    //
    int  iErr = -1;

    //
    printRefreshRecentFriendsResp(&pMsg->resp,_T("ctxQmc.displayRecentFriends"));
    //
    CCtxQyMc* pQyMc = g_pQyMc;
    CMainFrame* pMainWnd = (CMainFrame*)QWidget::find((WId)pQyMc->gui.hMainWnd);
    if (!pMainWnd)  goto  errLabel;

    pMainWnd->displayRecentFriends(pMsg);

    HWND hTalk_vide; hTalk_vide = m_var.hTalk_video;

    CDlgTalk_qt* pTalk; pTalk = (CDlgTalk_qt*)QWidget::find((WId)hTalk_vide);
    if (!pTalk) goto errLabel;

    for (int j = 0; j < pMsg->resp.usCnt; j++)
    {
        
            pTalk->updateMemStatus(pMsg->resp.mems[j].idInfo.ui64Id, pMsg->resp.mems[j].usRunningStatus);
       
    }


    iErr = 0;


    errLabel:


    //
    return  0;
}


//
int  CCtxQmc_sm::confKeyChanged(HWND  hDlgTalk)
{
    int  iErr = -1;

    //
    HWND  hDlgTalk_mgr = hDlgTalk;

    //
    CHelp_getDlgTalkVar	help_getDlgTalkVar;
    DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk_mgr);
    if (!pMgrVar)  goto  errLabel;

    if (!isTalkerShadowMgr(pMgrVar->addr))  goto  errLabel;
    TALKER_shadow_mgr* pShadowMgr; pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
    if (!pShadowMgr)  goto  errLabel;

    int  i;


    //
    for (i = 0; i < mycountof(pShadowMgr->shadows); i++) {
        TALKER_shadow_mgrMem* pMem = &pShadowMgr->shadows[i];
        if (pMem->hShadow) {
            CDlgTalk_qt* pTalk = (CDlgTalk_qt*)CDlgTalk_qt::find((WId)pMem->hShadow);
            if (pTalk) {
                //refreshTalkToInfo(pMem->hShadow);
                pTalk->do_confKeyChanged();
            }
        }
    }

    //
    CDlgTalk_qt* pTalk; pTalk = (CDlgTalk_qt*)CDlgTalk_qt::find((WId)hDlgTalk_mgr);
    if (pTalk) {
        //refreshTalkToInfo(hDlgTalk_mgr);
        pTalk->do_confKeyChanged();
    }

   
    if (pTalk) {



      
        pTalk->do_confMemKeyChanged(hDlgTalk);
    }








    iErr = 0;
    errLabel:
    //
    return  iErr;
}


//
int CCtxQmc_sm::do_permitToSpeak(HWND  hDlgTalk,QY_MESSENGER_ID  idInfo_from)
{

#if  0
    if (pProcInfo->cfg.policy.avRules.ucbLetConfMgrSetMicOn) {

        //  2017/07/13
        setCurSharedObjUsr_localAv(pProcInfo, pMgrVar->av.iIndex_sharedObj_localAv, hMgr);

        dlgTalk_requestToSpeak(hMgr, TRUE);
    }
#endif
  
    viewInviteHint(hDlgTalk);
    
    //
    showNotification_open(0, 0, 0, _T("主持人请你发言"));

    return  0;
}


//
int CCtxQmc_sm::do_pleaseSpeak(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from)
{
    //
    int  iErr = -1;
    //
    CCtxQmc* pProcInfo = this;
    //
    CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
    HWND  hMgr = hDlgTalk;
    DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);// &m_var;
    if (!pMgrVar)return  -1;
    if (!isTalkerShadowMgr(pMgrVar->addr)) {
        TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pMgrVar->pShadowInfo;
        if (!pTalkerShadow)  return  -1;
        hMgr = pTalkerShadow->hMgr;
        pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
        if (!pMgrVar)  return  -1;
    }
    TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
    if (!pShadowMgr)  return  -1;

    //
    if (!dlgTalk_bConfCompere(hMgr, idInfo_from)) {
        showNotification(0, &idInfo_from, 0, 0, 0, 0, _T("错误：收到一个非主持人的请求"));
        goto  errLabel;

    }

    if (pMgrVar->av.taskInfo.usConfType != CONST_usConfType_emergencyCommand) {
        showNotification(0, &idInfo_from, 0, 0, 0, 0, _T("错误：非应急指挥，不能调取视频"));
        goto  errLabel;
    }

    //
    //if (pProcInfo->cfg.policy.avRules.ucbLetConfMgrSetMicOn) 
    {

        //  2017/07/13
        setCurSharedObjUsr_localAv(pProcInfo, pMgrVar->av.iIndex_sharedObj_localAv, pMgrVar->av.iIndex_usr_localAv);

        dlgTalk_requestToSpeak(hMgr, TRUE);
    }
    //
    refreshTalkerList(hMgr);

    pProcInfo->xt.bSpeak = true;
    pProcInfo->av.hk.iHkStatus = setFyOff(pProcInfo->av.hk.iHkStatus);
    reportToHg_speakOn(0, pMgrVar->addr.idInfo.ui64Id, true);

    //
    showNotification(0, &idInfo_from, 0, 0, 0, 0, _T("主持人请你发言"));

    iErr = 0;

errLabel:

    //
    return  iErr;
}


int CCtxQmc_sm::do_pleaseStopSpeaking(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from)
{
    //
    int  iErr = -1;
    //
    CCtxQmc* pProcInfo = this;
    //
    CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
    HWND  hMgr = hDlgTalk;
    DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);// &m_var;
    if (!pMgrVar)return  -1;
    if (!isTalkerShadowMgr(pMgrVar->addr)) {
        TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pMgrVar->pShadowInfo;
        if (!pTalkerShadow)  return  -1;
        hMgr = pTalkerShadow->hMgr;
        pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
        if (!pMgrVar)  return  -1;
    }
    TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
    if (!pShadowMgr)  return  -1;

    //
    if (!dlgTalk_bConfCompere(hMgr, idInfo_from)) {
        showNotification(0, &idInfo_from, 0, 0, 0, 0, _T("错误：收到一个非主持人的请求"));
        goto  errLabel;

    }

    if (pMgrVar->av.taskInfo.usConfType != CONST_usConfType_emergencyCommand) {
        showNotification(0, &idInfo_from, 0, 0, 0, 0, _T("错误：非应急指挥，不能调取视频"));
        goto  errLabel;
    }

    //
    //if (pProcInfo->cfg.policy.avRules.ucbLetConfMgrSetMicOn) 
    {

        //  2017/07/13
        setCurSharedObjUsr_localAv(pProcInfo, pMgrVar->av.iIndex_sharedObj_localAv, pMgrVar->av.iIndex_usr_localAv);

        dlgTalk_requestToSpeak(hMgr, false);
    }
    //
    refreshTalkerList(hMgr);

    pProcInfo->xt.bSpeak = false;
    pProcInfo->av.hk.iHkStatus = clearFyOff(pProcInfo->av.hk.iHkStatus);
    reportToHg_speakOn(0, pMgrVar->addr.idInfo.ui64Id, false);
    //
    showNotification(0, &idInfo_from, 0, 0, 0, 0, _T("主持人请你停止发言"));

    

    iErr = 0;

errLabel:

    //
    return  iErr;
}

//
int CCtxQmc_sm::do_dlgTalk_proc_recvd_confCtrlState(HWND  hDlgTalk)
{
    CDlgTalk_qt* pDlgTalk = (CDlgTalk_qt*)CDlgTalk_qt::find((WId)hDlgTalk);
     if (!pDlgTalk)return  -1;
     DLG_TALK_var* pm_var = pDlgTalk->get_pm_var();
     if (!pm_var)return  -1;

    int  iTalkSubtype = CONST_talkerSubtype_video;
    HWND  m_hWnd_shadow;

    if (findTalker_shadow(pQyMc, pm_var->addr.idInfo.ui64Id, iTalkSubtype, &m_hWnd_shadow))
    {
        return -1;
    }
    CDlgTalk_qt* video_cdlgTalkqt = (CDlgTalk_qt*)getObjAddr(m_hWnd_shadow);
    if (!video_cdlgTalkqt)
    {
        return -1 ;
    }


    
   
    video_cdlgTalkqt->updateMenuComper();
    
    return  0;
}

//
#if 0
int CCtxQmc_sm::update_serv_ca_sendData(QIS_ca_req* p)
{
    int  iErr = -1;
    Var_ca_dev_qmc* pVc = &m_var.ca_dev;
    if (p->ca_sendDataLen > sizeof(pVc->serv.ca_sendData))  goto  errLabel;
    memcpy(pVc->serv.ca_sendData, p->ca_sendData, p->ca_sendDataLen);
    pVc->serv.ca_sendDataLen = p->ca_sendDataLen;

    //
    pVc->flgs.bGot_serv_ca_sendData = true;

    //
    showInfo_open0(0, 0, _T("recv serv_ca_sendData"));

    //
    iErr = 0;
    errLabel:
    return  iErr;
}
#endif

//
int CCtxQmc_sm::sxrz_yq(QIS_ca_req* p)
{
    //
    sm_sxrz_yq(p);

    //
    return  0;

}





//
int  CCtxQmc_sm::do_logImMsg_isCli(void* pDb, int  iDbType, void* pDBManager, IM_MSG_RCD* pRcd)
{
    //
    DBManager* pDm = (DBManager*)pDBManager;
    if (!pDm)  return  -1;

    //
    unsigned  int puiObjType;
    unsigned  int  uiObjType_peer = 0;
    unsigned  int  uiObjType_from = 0;
    TCHAR grpName_peer[128] = _T("");
    TCHAR srcName_peer[128] = _T("");

    TCHAR grpName_from[128] = _T("");
    TCHAR srcName_from[128] = _T("");
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return -1;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    struct MessageData md;
    md.fileSize = 0;
    md.sizePerSnd_suggest = 0;
    md.messageId = QString::number(pRcd->idInfo_send.ui64Id) + "-" + QString::number(pRcd->tSendTime) + "-" + QString::number(pRcd->uiTranNo);
    
    md.fromUserId = QString::number(pRcd->idInfo_send.ui64Id);
    if (pRcd->uiType == CONST_imCommType_htmlContent) {
        md.type = MessageTypes::TextMessage;
        getTalkerDesc(pRcd->idInfo_send, &uiObjType_from, grpName_from, mycountof(grpName_from), mynull, mynull, 0, mynull, 0, srcName_from, mycountof(srcName_from));
    }
    else if (pRcd->uiType == CONST_imCommType_transferFileReq) {
        md.type = MessageTypes::FileMessage;
        md.fileName = QString::fromStdWString(std::wstring(pRcd->content));
        md.iTaskId = QString::number(pRcd->iTaskId);
        md.is_activeProcess = 1;
        md.fileSize = pRcd->ui64FileLen;
        md.sizePerSnd_suggest = pRcd->uiSizePerSnd_suggest;
        getTalkerDesc(pRcd->idInfo_send, &uiObjType_from, grpName_from, mycountof(grpName_from), mynull, mynull, 0, mynull, 0, srcName_from, mycountof(srcName_from));
    }
    else {
        md.type = MessageTypes::MeetingMessage;
        md.iTaskId = QString::number(pRcd->iTaskId);
        if (pRcd->idInfo_initiator.ui64Id == 0) {
            getTalkerDesc(pRcd->idInfo_send, &uiObjType_from, grpName_from, mycountof(grpName_from), mynull, mynull, 0, mynull, 0, srcName_from, mycountof(srcName_from));
        }
        else {
            md.fromUserId = QString::number(pRcd->idInfo_initiator.ui64Id);
            getTalkerDesc(pRcd->idInfo_initiator, &uiObjType_from, grpName_from, mycountof(grpName_from), mynull, mynull, 0, mynull, 0, srcName_from, mycountof(srcName_from));
        }
        
    }

    //getTalkerDesc(pRcd->idInfo_send, &uiObjType_from, grpName_from, mycountof(grpName_from), null, null, 0, null, 0, srcName_from, mycountof(srcName_from));
    getTalkerDesc(pRcd->idInfo_recv, &uiObjType_peer, grpName_peer, mycountof(grpName_peer), mynull, mynull, 0, mynull, 0, srcName_peer, mycountof(srcName_peer));

    md.is_rece = 0;
    md.cancel = 0;
    md.fromUserName = QString::fromStdWString(srcName_from);
    md.headerUrl = ":/Resources/Images/WinMain/person.png";
    if (uiObjType_peer == CONST_objType_imGrp
        || uiObjType_peer  ==  CONST_objType_tmpGrp ) 
    {
        //if (srcName_peer[0] == _T('\0')) {

        md.toUserName = QString::fromStdWString(grpName_peer);

        md.userId = QString::number(pRcd->idInfo_recv.ui64Id);

    }
    else {
        md.toUserName = QString::fromStdWString(srcName_peer);

        if (pMisCnt->idInfo.ui64Id == pRcd->idInfo_send.ui64Id) {

            md.userId = QString::number(pRcd->idInfo_recv.ui64Id);
        }
        else {
            md.userId = QString::number(pRcd->idInfo_send.ui64Id);
        }
    }

    md.messageTime = pRcd->tSendTime;
   
    md.toUserId = QString::number(pRcd->idInfo_recv.ui64Id);
    getTalkerDesc(pRcd->idInfo_logicalPeer, &puiObjType, mynull, 0, mynull, mynull, 0, mynull, 0, mynull, 0);
    if (puiObjType == CONST_objType_imGrp) {
        md.chatType = ChatType::GroupChat;
        md.userId = QString::number(pRcd->idInfo_logicalPeer.ui64Id);
    }
    else {
        md.chatType = ChatType::OneChat;
    }
    md.isRead = 0;
    md.isSend = 0;
    md.content = QString::fromStdWString(std::wstring(pRcd->content));
    md.isRealDel = 0;
    md.deleteTime = 0;
    md.other = "";
    md.isDownload = 0;
    md.isRealDel = 0;
  
    md.isUpload = 0;
    md.seqNo = 0;
    md.is_rece = 0;
    md.cancel = 0;
   




    if (pRcd->uiType == CONST_imCommType_transferAvInfo) {
        md.is_activeProcess = 1;
        md.content = u8"发起了语音视频";
        QList<MessageData> m_find = pDm->getMessagesMidFind(md.userId, md.messageId);
        if (m_find.size() != 0) {
            return 0;
        }
    }



    bool res = pDm->insertMessage(md);

    if (res) {
        return 0;
    }

    return -1;
}


//
int  CCtxQmc_sm::viewDlgSelectAvCompressor(HWND  hParent, QY_MESSENGER_ID idInfo, unsigned  int  uiCapType, unsigned  int  uiSubCapType, int  iCapUsage, BOOL  b3D, unsigned  short  usConfType)
{
    QWidget* pParent = QWidget::find((WId)hParent);
    //
    QualitySelSetDialog dlg;
    int tmpiRet = dlg.exec();
    if (tmpiRet != QDialog::Accepted) return  -1;

    return  IDOK;
}

//
void CCtxQmc_sm::gui_notify_clearTask(int  iTaskId)
{
    ::gui_notify_clearTask(iTaskId);
    return;
}

void CCtxQmc_sm::gui_notify_clear()
{
    ::gui_notify_clear();
    return;
}

void* CCtxQmc_sm::DBManager_new()
{
    DBManager* p = new DBManager();
    return  p;
}

void CCtxQmc_sm::DBManager_free(void** ppDBManager)
{
    if (!ppDBManager || !*ppDBManager)return;
    DBManager* p = (DBManager*)*ppDBManager;
    delete p;
    *ppDBManager = mynull;
    return;
}


//
int  CCtxQmc_sm::infrared_recvChar(unsigned  char nChar, int portNo)
{
    //
    TCHAR  tBuf[128];
    char instruct;
    _sntprintf(tBuf, mycountof(tBuf), _T("%x\n"), (int)nChar);
    OutputDebugString(tBuf);



   
    
    //做一个发送
    
    CCtxQyMc* pQyMc = g_pQyMc;
    CMainFrame* pMainWnd = (CMainFrame*)QWidget::find((WId)pQyMc->gui.hMainWnd);
    

    //pMainWnd->recvInfraredInstruct(tBuf,portNo);
    mainWnd_recvInfraredInstruct(pMainWnd,  tBuf, portNo);


    //
    return  0;
}


//
//
int  CCtxQmc_sm::getChosenCamera(TCHAR* webcam_selected, unsigned  int  uiCnt_webcam_selected)
{
    CCtxQmc* pProcInfo = this;


    //
    if (sm_getChosenCamera(webcam_selected, uiCnt_webcam_selected))  return  -1;


    //
    return  0;
}


//
 int CCtxQmc_sm::reportToHg_meetingOn(unsigned  __int64  ui64MeetingId_hg, int  iMeetingType, unsigned  __int64  ui64Id_grp, bool  bOn) {
    //
    CCtxQmc_sm* pProcInfo = this;
    
    if (!bOn) {
        if (pProcInfo->m_var.ctxSm.usrLogin_sm.bUsrLogined
            && pProcInfo->m_var.ctxSm.usrLogin_sm.loginState.bExists_usrKey 
            && !pProcInfo->xt.bUsrUkeyed)
       
        {
            
            //
            // log
            QString tmp_keyStatus = u8"";

            QString log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + tmp_keyStatus;

            TCHAR  tBuf[128];
            _sntprintf(tBuf, mycountof(tBuf), _T("%sUKEY拔出退出会议，会议号：%d"), pProcInfo->av.confLayout.login_termialName, ui64Id_grp);

            qmcLogForHg(0, tBuf, true);
             
            //
            pProcInfo->xt.bErr_leaveConf = false;
        }
    }
    //
    return  ::reportToHg_meetingOn(ui64MeetingId_hg, iMeetingType, ui64Id_grp, bOn);
}

 //
 int  CCtxQmc_sm::tmpHandler_showMsg_task(void* hDlgTalkParam, void* pDLG_TALK_var, void* p1, void* pMsgParam)
 {
     if (!pDLG_TALK_var) return  -1;
     DLG_TALK_var& m_var = *(DLG_TALK_var*)pDLG_TALK_var;

     return   ::tmpHandler_showMsg_task_qmcCli(hDlgTalkParam, m_var, p1, pMsgParam);

 }


 //
 int CCtxQmc_sm::do_videoCurrInfo(HWND  hDlgTalk, void* pDlgTalkVar, void* pContent)
 {
     CDlgTalk_qt* pDlg = (CDlgTalk_qt*)CDlgTalk_qt::find((WId)hDlgTalk);
     if (!pDlg)return   -1;

     pDlg->video_curr_info(pContent);
     //
     return -1;
 }


 int  CCtxQmc_sm::doCmd_startAvCall(HWND  hParent, HWND  hCurTalk, int  level, BOOL  b3D, unsigned  char  ucbAvConsole, PARAM_startAvCall* pParam)
 {
     return  confCli_doCmd_startAvCall(hParent, hCurTalk, level, b3D, ucbAvConsole, pParam);

}

 //
 int sm_dlgTalk_closeTaskAv_afterTaskClosed(HWND  hDlgTalk, DLG_TALK_var* pm_var)
 {
     CDlgTalk_qt* pDlgTalk = (CDlgTalk_qt*)CDlgTalk_qt::find((WId)hDlgTalk);
     if (!pDlgTalk)return  -1;

     pDlgTalk->do_closeTaskAv_afterTaskClosed();

     return  0;
 }

 int  CCtxQmc_sm::dlgTalk_closeTaskAv_afterTaskClosed(HWND  hDlgTalk, void* pm_var)
 {
     sm_dlgTalk_closeTaskAv_afterTaskClosed(hDlgTalk, (DLG_TALK_var*)pm_var);

     return confCli_dlgTalk_closeTaskAv_afterTaskClosed(hDlgTalk,pm_var);
 }


//
int mainWnd_procMsgInput_confReq(HWND  hMainWnd, void* pVar, MIS_MSG_INPUT* pMsgInput)
{

    return  -1;
}




//
QString  getInstallDir_qt()
{
    QString tmpDir=qApp->applicationDirPath();
    TCHAR tDir[256];

    int i=tmpDir.lastIndexOf("bin");
    QString kk = tmpDir.mid(0, i);
    return  kk;


}


//
int chkXtResp()
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm  *  )QY_GET_procInfo_isCli();
    
    //
#ifdef  __DEBUG__
    //
    if (pProcInfo->m_var.b_app_noChkXtResp_forDebug) {
        //
        traceLog((TCHAR*)_T("chkXtResp: b_app_noChkXpResp_forDebug is true"));
        //
        return  0;        
    }
#endif 


    //
    if (pProcInfo->xt.nTimes_waitForXtResp > pProcInfo->cfg.maxTimes_noXtResp3) {
        showInfo_open0(0, 0, _T("chkXtResp: too long no xtResp, bNeedRestart_noXtResp set to true"));
        //
        pProcInfo->xt.bNeedRestart_noXtResp = true;
    }

    
    return  0;
}

