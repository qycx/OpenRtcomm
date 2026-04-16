
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
#include	"ctxQmc_qt.h"
#include	"policyAvParams.h"
#include	"qyAvRecordPublic.h"
//#include	"qmcVideoCapture_isCli.h"
//#include	"qmcCommFunc_isCli.h"
#include	"qmcCmdProc.h"
#include	"qyMcMainWndProc.h"
#include	<shellapi.h>
#include	"resource.h"  
#include <CMainFrame.h>
#include <QualitySelSetDialog.h>
#include <CDlgTalk_invite_hint.h>

//#include	<ctxQmc_gui.h>

//
int  tmpHandler_showMsg_task_qmcCli(void* hDlgTalkParam, DLG_TALK_var& m_var, void* p1, void* pMsgParam);
int getSmCfgDir_cli(TCHAR* cfgDirName, int cfgDirNameLen)
{
    //CCtxQyMc* pQyMc = g_pQyMc;

    TCHAR  tBuf[256] = _T("");
    unsigned  int  uiType = 0;
    qyGetRegCfgT(HKEY_CURRENT_USER, _T(CONST_qyRootKey_qnmScheduler_misClient), _T("smCfgDir"), (char*)tBuf, sizeof(tBuf), &uiType);
    tBuf[mycountof(tBuf) - 1] = 0;
    tTrim(tBuf);

    if (!tBuf[0]) {
        safeTcsnCpy(DEFAULT_smCfgDir, cfgDirName, cfgDirNameLen);
    }
    else {
        safeTcsnCpy(tBuf, cfgDirName, cfgDirNameLen);
    }

    //
    return  0;
}

//
extern  "C"  __declspec(dllexport)  int  parseCmdLine_qyMc(LPCTSTR  pCmdLine, QMC_APP_PARAMS * pParams)
{

    parseCmdLine_qmc_func(pCmdLine, pParams);

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

    p = new  CCtxQmc_qt;

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
CCtxQmc_qt::CCtxQmc_qt()
{
    //  2014/02/08
    this->m_iCtxType = CONST_ctxType_qmc;
    this->m_iCtxSubtype = CONST_ctxSubtype_qmcQt;


    //
#ifdef  __DEBUG__
    this->test1 = 567;
    this->test2 = 901;
#endif

    //
    int  size = &this->_bEnd - &this->_start;
    memset(&this->_start, 0, size);

    //
    memset(&m_var, 0, sizeof(m_var));

    //
    this->cfg.ucb_talkToMsgr_manually = true;

    //
    QString qstr = getInstallDir_qt();
    safeTcsnCpy((TCHAR*)qstr.utf16(), m_var.installDir_qt, mycountof(m_var.installDir_qt));

}

CCtxQmc_qt::~CCtxQmc_qt()
{
    int  i = 0;
    if (m_var.pDBManager) {
        DBManager* p = (DBManager*)m_var.pDBManager;
        delete  p;
        m_var.pDBManager = mynull;
    }

}


//
int  CCtxQmc_qt::setQmDbFuncs(int  iDbType, QM_dbFuncs* pDbFuncs)
{
    return  ::setQmDbFuncs_qm(iDbType, pDbFuncs);
}

//
int  qyMc_setQmDbFuncs(int  iDbType, QM_dbFuncs* pDbFuncs)
{
    return  ::setQmDbFuncs_qm(iDbType, pDbFuncs);
}



//
int  CCtxQmc_qt::loadCusModules(void* pQyMcParam)
{
    return  ::loadCusModules(pQyMcParam);
}


int  CCtxQmc_qt::unloadCusModules(void* pQyMcParam)
{
    return  ::unloadCusModules(pQyMcParam);
}

//
int  CCtxQmc_qt::initCusModules(void* pQyMcParam)
{
    return  ::initCusModules(pQyMcParam);

}


int  CCtxQmc_qt::startCusModules(void* pQyMcParam)
{
    return  ::startCusModules(pQyMcParam);
}


int  CCtxQmc_qt::stopCusModules(void* pQyMcParam)
{
    return  ::stopCusModules(pQyMcParam);
}


//
int  CCtxQmc_qt::initVar_post(void* p0, void* p1, void* p2)
{
    return  0;
}

int  CCtxQmc_qt::exitVar_pre(void* p0, void* p1, void* p2)
{
    return  0;
}


int  CCtxQmc_qt::exitVar_post(void* p0, void* p1, void* p2)
{
    return  0;
}

//
int  CCtxQmc_qt::qyShowMainWndFunc(HWND  hMainWnd, void* pVar, BOOL  bShow)
{
    //return  ::qyShowMainWndFunc_cli(hMainWnd, pVar, bShow);
    return  -1;
}


//
int  CCtxQmc_qt::postMsg2Mgr_mc(void* pMIS_CNT, MSG_ROUTE* pRoute, unsigned  int  uiMisMsgType, unsigned  char  ucFlg, unsigned  short  usCode, time_t  tStartTime, unsigned  int  uiTranNo, unsigned  int  uiSeqNo, char* data, unsigned  int  dataLen, QY_MESSENGER_ID* pIdInfo_logicalPeer, QY_MESSENGER_ID* pIdInfo_dst, unsigned  int  uiChannelType, MIS_MSGU* pMsgBuf, BOOL  bLog)
{
    return  ::postMsg2Mgr_mc(pMIS_CNT, pRoute, uiMisMsgType, ucFlg, usCode, tStartTime, uiTranNo, uiSeqNo, data, dataLen, pIdInfo_logicalPeer, pIdInfo_dst, uiChannelType, pMsgBuf, bLog);
}


//
int  CCtxQmc_qt::postMsgTask2Mgr_mc(void* pMIS_CNT, unsigned  int  uiMisMsgType, unsigned  char  ucFlg, unsigned  short  usCode, time_t  tStartTime, unsigned  int  uiTranNo, unsigned  int  uiSeqNo, int  iTaskId, unsigned  int  uiTaskType, char* data, unsigned  int  dataLen, QY_MESSENGER_ID* pIdInfo_logicalPeer, QY_MESSENGER_ID* pIdInfo_taskSender, QY_MESSENGER_ID* pIdInfo_taskReceiver, QY_MESSENGER_ID* pIdInfo_dst, unsigned  int  uiChannelType, MIS_MSGU* pMsgBuf, BOOL  bLog)
{
    return  ::postMsgTask2Mgr_mc(pMIS_CNT, uiMisMsgType, ucFlg, usCode, tStartTime, uiTranNo, uiSeqNo, iTaskId, uiTaskType, data, dataLen, pIdInfo_logicalPeer, pIdInfo_taskSender, pIdInfo_taskReceiver, pIdInfo_dst, uiChannelType, pMsgBuf, bLog);
}


//
int  CCtxQmc_qt::postImMsg2Log_isClient(MIS_MSGU* pMsg, int  lenInBytes_msg)
{
    return  ::postImMsg2Log_isClient(pMsg, lenInBytes_msg);
}




//
int  CCtxQmc_qt::recoverMessenger(QM_dbFuncs* pDbFuncs, void* pDb, int  iDbType, QY_DMITEM* pFieldIdTable, QY_MESSENGER_INFO* pObj, QY_MESSENGER_REGINFO* pRegInfo, time_t  tLastModifiedTime, BOOL  bLog, GENERIC_Q* pLogQ)
{
    return  ::recoverMessenger(pDbFuncs, pDb, iDbType, pFieldIdTable, pObj, pRegInfo, tLastModifiedTime, bLog, pLogQ);
}


//
int  CCtxQmc_qt::recoverImObjRules(QM_dbFuncs* pDbFuncs, void* pDb, int  iDbType, LPCTSTR  misServName, QY_MESSENGER_ID* pIdInfo, REFRESH_imObjRules_req* pReq, time_t  tLastModifiedTime)
{
    return  ::recoverImObjRules(pDbFuncs, pDb, iDbType, misServName, pIdInfo, pReq, tLastModifiedTime);
}

//
int  CCtxQmc_qt::recoverImGrp(QM_dbFuncs* pDbFuncs, void* pDb, int  iDbType, QY_DMITEM* pFieldIdTable, unsigned  int  uiObjType, IM_GRP_INFO* pGrpInfo, time_t  tLastModifiedTime, BOOL  bNoGrpName)
{
    return  ::recoverImGrp(pDbFuncs, pDb, iDbType, pFieldIdTable, uiObjType, pGrpInfo, tLastModifiedTime, bNoGrpName);
}


//
int  CCtxQmc_qt::recoverImGrpMem(QM_dbFuncs* pDbFuncs, void* pDb, int  iDbType, IM_GRP_MEM* pGrpMem, time_t  tLastModifiedTime)
{
    return  ::recoverImGrpMem(pDbFuncs, pDb, iDbType, pGrpMem, tLastModifiedTime);
}


//
//	
FUNCS_for_isCliHelp* CCtxQmc_qt::FUNCS_for_isCliHelp_new()
{
    safeTcsnCpy(_T("isCliD3d.dll"), this->cfg.isCliD3dFileName, mycountof(this->cfg.isCliD3dFileName));
    //
    return  ::FUNCS_for_isCliHelp_new(this->pQyMc);
}


//
void  CCtxQmc_qt::FUNCS_for_isCliHelp_free(void** ppFuncs)
{
    ::FUNCS_for_isCliHelp_free(ppFuncs);
    return;
}



//  2016/09/08
int  CCtxQmc_qt::tryToTalkToMessenger_any(HWND hParent, unsigned  __int64  ui64Id, int  iTalkSubtype, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
    return  ::tryToTalkToMessenger_any(hParent, ui64Id, iTalkSubtype, bNeedNotShowWnd, bActivateWnd, phWnd);
}


//
int  CCtxQmc_qt::talkToMessenger(unsigned  __int64  ui64Id, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
    return  ::talkToMessenger(ui64Id, 0, bNeedNotShowWnd, bActivateWnd, phWnd);

}


//  
int  CCtxQmc_qt::doApplyForPlayer(HWND  hMainWnd, MIS_MSGU* pMsg)
{
    return  ::doApplyForPlayer(g_pQyMc,  hMainWnd, pMsg);
}

int CCtxQmc_qt::do_videoCurrInfo(HWND  hDlgTalk, void* pDlgTalkVar, void* pContent)
{
    CDlgTalk_qt* pDlg = (CDlgTalk_qt*)CDlgTalk_qt::find((WId)hDlgTalk);
    if (!pDlg)return   -1;

    pDlg->video_curr_info(pContent);
    //
    return -1;
}

//
int  CCtxQmc_qt::removeMosaicFromD3dWall(int  iIndex_sharedObj)
{
    return  ::dyn_removeMosaicFromD3dWall(this, iIndex_sharedObj);
}

int  CCtxQmc_qt::getVal_bExists_mosaic(int  iIndex_sharedObj, BOOL* pbExists)
{
    return  ::dyn_getVal_bExists_mosaic(this, iIndex_sharedObj, pbExists);
}

//
int  CCtxQmc_qt::stopLocalAudioRecorder(int  index_sharedObj, int  nTries)
{
    return  ::stopLocalAudioRecorder(this, index_sharedObj, nTries);
}

//
int  CCtxQmc_qt::talkToMessenger(void* pQyMcParam, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkUsage, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
    return ::talkToMessenger_qt(pQyMcParam, pAddr, pTmpGrpMemQ, iTalkUsage, bNeedNotShowWnd, bActivateWnd, phWnd);
}

void* CCtxQmc_qt::tmp_getDlgTalkVar(HWND  hDlgTalk)
{
    return  ::tmp_getDlgTalkVar_qt(hDlgTalk);
}

int  CCtxQmc_qt::getTalkerShadow(HWND  hParent, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkerSubType, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
    return  ::getTalkerShadow_qt(hParent, pAddr, pTmpGrpMemQ, iTalkerSubType, bNeedNotShowWnd, bActivateWnd, phWnd);
}

int  CCtxQmc_qt::do_addToRecentMsg(HWND  hDlgTalk, void* pDLG_TALK_var, long  lRowIndex, int  iTaskId, MIS_MSGU* pMsgU, MIS_MSG_taskStatus  *  pMsgTaskStatus,  QY_MESSENGER_ID idInfo_talker, LPCTSTR  talkerDesc, unsigned  short  usOp, int  iStatus, char* timeBuf, LPCTSTR  rowIdStr, LPCTSTR  content, BOOL  bFollowingRows, BOOL  bScrollIntoView, TCHAR* txtBuf, unsigned  int  uiTxtBufCnt)
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
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
int  CCtxQmc_qt::do_talk_OnTimer(HWND  hDlgTalk, void *pDLG_TALK_var)
{

    CDlgTalk_qt* cdlgTalkqt = mynull;
    cdlgTalkqt = (CDlgTalk_qt*)QWidget::find((WId)hDlgTalk);
    if (!cdlgTalkqt) return  -1;
    //MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    //

    cdlgTalkqt->doTimerProc();


    return  0;
}



//
int  CCtxQmc_qt::do_talk_afterInit(HWND  hDlgTalk)
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


int  CCtxQmc_qt::do_talk_refreshLayout(HWND  hDlgTalk)
{
    CDlgTalk_qt* cdlgTalkqt = mynull;
    cdlgTalkqt = (CDlgTalk_qt*)QWidget::find((WId)hDlgTalk);
    if (!cdlgTalkqt) return  -1;

    cdlgTalkqt->refreshLayout();

    return  0;
}



//
bool CCtxQmc_qt::myDestroyWindow(HWND  hWnd)
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
int  CCtxQmc_qt::getDirAndFinalName(LPCTSTR  svFileName, TCHAR* dirName, unsigned  int  size, TCHAR* finalName, unsigned  int  finalNameSize)
{
    return  ::getDirAndFinalName_qt(svFileName, dirName, size, finalName, finalNameSize);

}



int CCtxQmc_qt::do_test(HWND  hWnd, int  iWndContentType)
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
int CCtxQmc_qt::initDBManager(void* pDBManager)
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
int  CCtxQmc_qt::do_dlgTalk_procTask_transferAvInfo(HWND  hTalk)
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
int test_recentFriends(CCtxQmc_qt  *  pProcInfo)
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


//
int  CCtxQmc_qt::do_mainWnd_OnTimer(HWND  hMainWnd, void* pVar, UINT  nIDEvent)
{
#ifdef  __DEBUG__
    //test_recentFriends(this);
#endif

    if (!pVar)  return  -1;
    QY_MC_mainWndVar& var = *(QY_MC_mainWndVar*)pVar;
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_qt* pProcInfo = this;

   

    


    //
    //qmcChkSmTmpLogFile();



    //
    if (!(var.loopCtrl % CONST_intervalInS_xt)) {
        //if (pProcInfo->m_var.ctxSm.ca_dev.flgs.sxrz.bDone_sqm) 
        {
            send_xt(var.loopCtrl);
        }

    }


    //
    //if (!(var.loopCtrl % 30)) {
    //    //		  
    //    startToRetrievePlans();
    //}

    mainWnd_chkIpcProc(var.loopCtrl);

    //
    return  0;
}


//
int  CCtxQmc_qt::displayRecentFriends(MIS_MSG_displayRecentFriends_qmc* pMsg)
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
int  CCtxQmc_qt::confKeyChanged(HWND  hDlgTalk)
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
int CCtxQmc_qt::do_permitToSpeak(HWND  hDlgTalk, QY_MESSENGER_ID idInfo_from)
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



int CCtxQmc_qt::do_pleaseSpeak(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from)
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
    //
    showNotification(0, &idInfo_from, 0, 0, 0, 0, _T("主持人请你发言"));

    iErr = 0;

errLabel:

    //
    return  iErr;
}

int CCtxQmc_qt::do_pleaseStopSpeaking(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from)
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
    //
    showNotification(0, &idInfo_from, 0, 0, 0, 0, _T("主持人请你停止发言"));

    iErr = 0;

errLabel:

    //
    return  iErr;
}



//
int CCtxQmc_qt::do_dlgTalk_proc_recvd_confCtrlState(HWND  hDlgTalk)
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
int  CCtxQmc_qt::do_logImMsg_isCli(void* pDb, int  iDbType, void* pDBManager, IM_MSG_RCD* pRcd)
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
int  CCtxQmc_qt::viewDlgSelectAvCompressor(HWND  hParent, QY_MESSENGER_ID idInfo, unsigned  int  uiCapType, unsigned  int  uiSubCapType, int  iCapUsage, BOOL  b3D, unsigned  short  usConfType)
{
    QWidget* pParent = QWidget::find((WId)hParent);
    //
    QualitySelSetDialog dlg;
    int tmpiRet = dlg.exec();
    if (tmpiRet != QDialog::Accepted) return  -1;

    return  IDOK;
}

//
void CCtxQmc_qt::gui_notify_clearTask(int  iTaskId)
{
    ::gui_notify_clearTask(iTaskId);
    return;
}

void CCtxQmc_qt::gui_notify_clear()
{
    ::gui_notify_clear();
    return;
}

void* CCtxQmc_qt::DBManager_new()
{
    DBManager* p = new DBManager();
    return  p;
}

void CCtxQmc_qt::DBManager_free(void** ppDBManager)
{
    if (!ppDBManager || !*ppDBManager)return;
    DBManager* p = (DBManager*)*ppDBManager;
    delete p;
    *ppDBManager = mynull;
    return;
}

//
int  CCtxQmc_qt::tmpHandler_showMsg_task(void* hDlgTalkParam, void* pDLG_TALK_var, void* p1, void* pMsgParam)
{
    if (!pDLG_TALK_var) return  -1;
    DLG_TALK_var& m_var = *(DLG_TALK_var*)pDLG_TALK_var;

    return   ::tmpHandler_showMsg_task_qmcCli(hDlgTalkParam, m_var, p1, pMsgParam);

}



//
int mainWnd_procMsgInput_confReq(HWND  hMainWnd, void* pVar, MIS_MSG_INPUT* pMsgInput)
{
    return  -1;
}


//
int dlgTalk_closeTaskAv_afterTaskClosed(HWND  hDlgTalk, DLG_TALK_var* pm_var)
{
    CDlgTalk_qt* pDlgTalk = (CDlgTalk_qt*)CDlgTalk_qt::find((WId)hDlgTalk);
    if (!pDlgTalk)return  -1;

    pDlgTalk->do_closeTaskAv_afterTaskClosed();

    return  0;
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
int  CCtxQmc_qt::doCmd_startAvCall(HWND  hParent, HWND  hCurTalk, int  level, BOOL  b3D, unsigned  char  ucbAvConsole, PARAM_startAvCall* pParam)
{
    return  	confCli_doCmd_startAvCall(hParent, hCurTalk, level, b3D, ucbAvConsole, pParam);

}