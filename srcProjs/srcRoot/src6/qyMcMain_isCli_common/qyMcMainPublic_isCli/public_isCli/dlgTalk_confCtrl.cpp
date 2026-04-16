

#include	"stdafx.h"
#include	<time.h>
#include	<windowsx.h>
#include	<math.h>
#include	"qymcMainCommon.h"


#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"

#include	"qyOpenShellCommon.h"


#include	"tmpCeLib.h"

#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"

#include	"myresource.h"

#include	<assert.h>
#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
#include	"qmcConferenceWall.h"
#endif
#include	"qmcCmdProc.h"
#include	"dlgTalkProc.h"
#include	"isCliHelpPublic.h"
#include	"isCliD3dPublic.h"

#include	"qmcCommFunc_isCli.h"
//
#include	"funcsForIsCliHelp.h"

//
bool  dlgTalk_bConfInitiator(HWND  hDlgTalk,  QY_MESSENGER_ID  idInfo)
{
    bool  bRet = false;

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    TCHAR  tBuf[128];

    //
    //showInfo_open0(0, 0, _T("dlgTalk_bConfInitiator enters"));

    //
#ifdef  __DEBUG__
#if 0
    traceLog((TCHAR*)_T("for test: bConfInitiator set to true"));
    return  true;
#endif
#endif


    //
    HWND  hCur = (HWND)hDlgTalk;
    CHelp_getDlgTalkVar  getDlgTalkVar_cur;
    CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;

    DLG_TALK_var* pCurVar = (DLG_TALK_var*)getDlgTalkVar_cur.getVar(hCur);
    if (!pCurVar)  goto  errLabel;
    HWND  hMgr;  hMgr = hCur;
    DLG_TALK_var* pMgrVar;pMgrVar = pCurVar;
    if (!isTalkerShadowMgr(pCurVar->addr)) {
        TALKER_shadow* pShadowInfo = (TALKER_shadow*)pCurVar->pShadowInfo;
        if (!pShadowInfo)goto  errLabel;
        hMgr = pShadowInfo->hMgr;
        pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
        if (!pMgrVar)goto  errLabel;
    }
    if (!pMgrVar->av.taskInfo.bTaskExists)goto  errLabel;

    //
    if (pQyMc->appParams.bConfServer) {
        if (idInfo.ui64Id == pProcInfo->av.doConf.confReq.idInfo_initiator.ui64Id) {
            bRet = true;
        }
    }
    else {
        if (idInfo.ui64Id == pMgrVar->av.taskInfo.idInfo_initiator.ui64Id) {
            bRet = true;
        }
    }

    //
#if 0
    _sntprintf(tBuf, mycountof(tBuf), _T("idInfo %I64u, mgr.initiator %I64u, procInfo.initiator %I64u, bRet %d"), 
        idInfo.ui64Id, pMgrVar->av.taskInfo.idInfo_initiator.ui64Id, pProcInfo->av.doConf.confReq.idInfo_initiator.ui64Id,  bRet);
    showInfo_open0(0, 0, tBuf);
#endif


    //
errLabel:

    //


    //
    return  bRet;
}



bool  dlgTalk_bIAmConfInitiator(  HWND  hDlgTalk)
{
    bool  bRet = false;

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();


    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

    if  (  dlgTalk_bConfInitiator(hDlgTalk,pMisCnt->idInfo)  ) {
        bRet = true;
    }

errLabel:

    return  bRet;
}


//
bool  dlgTalk_bConfCompere(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo)
{
    bool  bRet = false;

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

    CHelp_getDlgTalkVar  help_getDlgTalkVar_cur;
    CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;

    if (!idInfo.ui64Id) return false;

    //
#ifdef  __DEBUG__
    traceLog((TCHAR*)_T("for test: bConfCompere set to true"));
    return  true;
#endif



    //
    HWND  hCur = (HWND)hDlgTalk;
    DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar_cur.getVar(hCur);
    if (!pCurVar)goto  errLabel;
    HWND  hMgr; hMgr = hCur;
    DLG_TALK_var* pMgrVar; pMgrVar = pCurVar;
    if (!isTalkerShadowMgr(pCurVar->addr)) {
        TALKER_shadow* pShadowInfo = (TALKER_shadow*)pCurVar->pShadowInfo;
        if (!pShadowInfo)goto  errLabel;
        hMgr = pShadowInfo->hMgr;
        pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
        if (!pMgrVar)goto  errLabel;
    }
    if (!pMgrVar->av.taskInfo.bTaskExists)goto  errLabel;

#if  0
    QY_MESSENGER_ID  idInfo_compere = pMgrVar->av.taskInfo.idInfo_compere;
    if (!idInfo_compere.ui64Id) idInfo_compere.ui64Id = pMgrVar->av.taskInfo.idInfo_initiator.ui64Id;

    //
    if (idInfo.ui64Id == idInfo_compere.ui64Id) {
        bRet = true;
    }
#endif
    int  i;
    HgZcrs* pZcrs = &pMgrVar->av.taskInfo.hgInfo.zcrs;
    for (i = 0; i < mycountof(pZcrs->mems); i++) {
        if (pZcrs->mems[i].idInfo.ui64Id == idInfo.ui64Id) {
            bRet = true;
            break;
        }
    }


    //
errLabel:
    return  bRet;
}


bool  dlgTalk_bIAmConfCompere(HWND  hDlgTalk)
{
    bool  bRet = false;
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

    if (dlgTalk_bConfCompere(hDlgTalk, pMisCnt->idInfo)) {
        bRet = true;
    }

    return  bRet;
}

//
QY_MESSENGER_ID  dlgTalk_get_idInfo_starter(HWND  hDlgTalk)
{
    QY_MESSENGER_ID     idInfo_starter = { 0 };

    CHelp_getDlgTalkVar help_getDlgTalkVar_cur;
    CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;

    //
    HWND  hCur = (HWND)hDlgTalk;
    DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar_cur.getVar(hCur);
    if (!pCurVar) goto  errLabel;

    HWND  hMgr;hMgr = hCur;
    DLG_TALK_var* pMgrVar;pMgrVar = pCurVar;
    if (!isTalkerShadowMgr(pCurVar->addr)) {
        TALKER_shadow* pShadowInfo = (TALKER_shadow*)pCurVar->pShadowInfo;
        if (!pShadowInfo)goto  errLabel;
        hMgr = pShadowInfo->hMgr;
        pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
        if (!pMgrVar)goto  errLabel;
    }
    if (!pMgrVar->av.taskInfo.bTaskExists)goto  errLabel;

    idInfo_starter.ui64Id = pMgrVar->av.taskInfo.idInfo_starter.ui64Id;

    //
errLabel:
    return  idInfo_starter;

}



//
QY_MESSENGER_ID  unused_dlgTalk_get_idInfo_compere(HWND  hDlgTalk)
{
    QY_MESSENGER_ID     idInfo_compere = { 0 };

#if  0
    //
    CHelp_getDlgTalkVar help_getDlgTalkVar_cur;
    CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;

    //
    HWND  hCur = (HWND)hDlgTalk;
    DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar_cur.getVar(hDlgTalk);
    if (!pCurVar) goto  errLabel;
    HWND  hMgr;hMgr = hCur;
    DLG_TALK_var* pMgrVar;pMgrVar = pCurVar;
    if (!isTalkerShadowMgr(pCurVar->addr)) {
        TALKER_shadow* pShadowInfo = (TALKER_shadow*)pCurVar->pShadowInfo;
        if (!pShadowInfo)goto  errLabel;
        hMgr = pShadowInfo->hMgr;
        pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
        if (!pMgrVar)goto  errLabel;
    }
    if (!pMgrVar->av.taskInfo.bTaskExists)goto  errLabel;

    if (pMgrVar->av.taskInfo.idInfo_compere.ui64Id)  idInfo_compere.ui64Id = pMgrVar->av.taskInfo.idInfo_compere.ui64Id;
    else  idInfo_compere.ui64Id = pMgrVar->av.taskInfo.idInfo_initiator.ui64Id;
#endif 

    //
errLabel:
    return  idInfo_compere;

}

