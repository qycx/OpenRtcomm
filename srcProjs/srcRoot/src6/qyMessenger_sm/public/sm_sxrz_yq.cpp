



#include	"stdafx.h"

//#include    <qdir.h>

#include	"myCmdParams_open.h"
#include	"tmpRegFunc_open.h"
#include	"imCommType_defs.h"
#include	"qyMcMainCommon.h"
#include	"qnmCommProc.h"
#include <DlgMcClientLogon.h>
#include	"smLoginProc.h"
#include	"ctxQmc.h"
//#include <smProc.h>
//#include	"ctxQmc_sm.h"
#include	"qyCusResTemp.h"
#include <qmcCommFunc_isCli.h>
#include <dlgtalkproc.h>
#include <qmcStruct_defs.h>
#include <funcsForIsCliHelp.h>


extern  "C"  __declspec(dllexport)  void resetShowInfoServIp(const char* servIp, int port);
//
int sm_sxrz_yq(QIS_ca_req* p)
{
    int  iErr = -1;
    CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
    Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
    
    if (!pCtxSm)  return  -1;
    Ctx_sm& ctxSm = *pCtxSm;

    //
    if (p->sHgCmd == CONST_hgCmd_hk) {
        int  ii = 0;
    }
    if (p->sHgCmd == CONST_hgCmd_sxrz_cliSqmOk) {
        int  ii = 0;
    }

    if (p->sHgCmd == CONST_hgCmd_overTime) {
        int  ii = 0;
    }
    if (p->sHgCmd == CONST_hgCmd_askforP2p_rece) {
        int  ii = 0;
    }
    if (p->sHgCmd == CONST_hgCmd_systemConfig) {
        int  ii = 0;
    }
    if (p->sHgCmd == CONST_hgCmd_portPower) {
        int  ii = 0;
    }




    //
    {
        Var_ca_dev_qmc* pVc = &ctxSm.ca_dev;


        //
        Param_sxrz_servReply param;
        memset(&param, 0, sizeof(param));
        //
        if (parseHgCmd_sxrz_servReply(p->ca_servData, p->ca_servDataLen, 0, &param)) {
            showInfo_open0(0, 0, _T("sxrz_yq.parseHgCmd_sxrz_servReply failed"));
            goto  errLabel;
        }
        

        //
        if (p->sHgCmd == CONST_hgCmd_sxrz_cliSqmOk) {

            if (param.iRc == CONST_hgRc_sxrz_cliSqm_failed) {
                //
                showInfo_open0(0, 0, _T(" recv cliSqmFailed"));
                //safeTcsnCpy(_T("注册码校验失败，请检查"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
                safeTcsnCpy(_T("recv cliSqmFailed"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

                goto  errLabel;
            }
            //
            pVc->flgs.sxrz.bDone_sqm = true;

            //todo  这里已经接收到   系统密级  心跳间隔   超时时间  打开端口权限   终端名称         已存在param中
            //

            ctxSm.hg.systemConfig.intervalInS_xt = param.termXt_time;
            ctxSm.hg.systemConfig.intervalInS_over = param.termOver_time;
           
          //  pProcInfo->av.confLayout.login_termialName = param.login_terminalName;

            safeTcsnCpy(param.login_terminalName, pProcInfo->av.confLayout.login_termialName, mycountof(pProcInfo->av.confLayout.login_termialName));
           
            ctxSm.hg.menuPower.bPortEnd = param.termIsPort_open;


            ctxSm.hg.systemConfig.system_level = param.systemLevel;


            //
            showInfo_open0(0, 0, _T(" recv cliSqmOk"));
            //safeTcsnCpy(_T("注册码确认成功"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
            safeTcsnCpy(_T("recv cliSmOk"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

            iErr = 0;  goto  errLabel;
        }


        //会管主动下发端口权限开关
        if (p->sHgCmd == CONST_hgCmd_portPower) {

            ctxSm.hg.menuPower.bPortEnd = param.termIsPort_open;

            int  ii = 0;
        }



        //
        if (p->sHgCmd == CONST_hgCmd_sxrz_ok) {
            //
            pVc->flgs.sxrz.bDone_sxrz = true;

            //
            showInfo_open0(0, 0, _T(" recv sxrz ok"));
            safeTcsnCpy(_T("双向认证成功"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

            iErr = 0;  goto  errLabel;

        }

        if (p->sHgCmd == CONST_hgCmd_askforP2p_rece) {
            
      

            safeTcsnCpy(param.fromTermName, ctxSm.hg.p2pMsg.formTermName, mycountof(ctxSm.hg.p2pMsg.formTermName));
            ctxSm.hg.p2pMsg.idInfo_grp  =  param.idInfo_grp;
            ctxSm.hg.p2pMsg.p2pLevel = param.p2pLevel;

          
            ctxSm.hg.p2pMsg.bMsg = true;

        }

        if (p->sHgCmd == CONST_hgCmd_systemConfig) {

            //接收心跳参数变动     终端心跳： param.termXt_time   超时心跳  param.termOver_time   系统密级  param.systemLevel
            int i = 12;
            ctxSm.hg.systemConfig.intervalInS_xt = param.termXt_time;
            ctxSm.hg.systemConfig.intervalInS_over = param.termOver_time;
            //判断系统密级变化
            if (param.systemLevel != ctxSm.hg.systemConfig.system_level) {

                pProcInfo->xt.bNeedRestart_mjChanged = true;

            }

            ctxSm.hg.systemConfig.system_level = param.systemLevel;


        }


        //
        if (param.cmd_org == CONST_hgCmd_retrievePlans) {

            //
            int  i;
            for (i = 0; i < mycountof(ctxSm.hg.meetingInfos); i++) {
                ctxSm.hg.meetingInfos[i] = param.meetingInfos[i];
            }
            //
            //  通知界面显示

            //
            iErr = 0;  goto  errLabel;
        }

        //
        if (param.cmd_org == CONST_hgCmd_retrieveP2pList) {
            //
            int  i;
            memset(&ctxSm.hg.p2pInfos, 0, sizeof(ctxSm.hg.p2pInfos));
            int nMax = min(mycountof(ctxSm.hg.p2pInfos.mems), mycountof(param.p2pInfos));
            for (i = 0; i < nMax; i++) {
                ctxSm.hg.p2pInfos.mems[i] = param.p2pInfos[i];
            }
            //
            for (i = 0; i < nMax; i++) {
                if (!ctxSm.hg.p2pInfos.mems[i].idfo)  break;
                ctxSm.hg.p2pInfos.cnt++;
            }
            //
            ctxSm.hg.bDone_p2p = true;


            //  通知界面显示


            //
            iErr = 0;  goto  errLabel;
        }

        //
        if (param.cmd_org == CONST_hgCmd_legal) {
            //
            memset(&pProcInfo->legal_info, 0, sizeof(pProcInfo->legal_info));

            if (param.iLegal) {
                pProcInfo->legal_info.bLegal = true;
            }
            else {
                pProcInfo->legal_info.bLegal = false;
            }
            pProcInfo->legal_info.isOk = true;
            pProcInfo->legal_info.nTimes_last = myGetTickCount(mynull);


            
        }

        if (param.cmd_org == CONST_hgCmd_askforP2p) {
            
        

            if (param.iRc == CONST_hgRc_p2p_busy) {

                
                //
                _sntprintf(  ctxSm.hg.p2pWarn.p2pContent,  mycountof(ctxSm.hg.p2pWarn.p2pContent), _T("对方%s正在占线中，请稍后再尝试发起点对点！"), param.peerTermName);

                //
                ctxSm.hg.p2pWarn.bWarn = true;


              
             }

            //
            iErr = 0;  goto  errLabel;
        }


        if (param.cmd_org == CONST_hgCmd_sxrz_cliStart) {
            int i = 121;

            if(param.iRc == CONST_hgRc_cliStart_failed){
                showInfo_open0(0, 0, _T(" recv cliStart failed"));
                safeTcsnCpy(_T("双向认证失败，联系管理员"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
                    

            }
            //
            iErr = 0;  goto  errLabel;
        }


        //
        if (p->sHgCmd == CONST_hgCmd_hk) {

            //
            Param_hg_cliReply  cliReply = { 0 };
            cliReply.iHkStatus_old = param.iHkStatus;// this->av.hk.iHkStatus;

            //
            int  ii = 0;
            if (pProcInfo->av.hk.iHkStatus != param.iHkStatus) {
                pProcInfo->av.hk.iHkStatus = param.iHkStatus;

                bool flag = false;
                if (isFyOff(pProcInfo->av.hk.iHkStatus)) { 
                    flag = true;
                    pProcInfo->xt.bSpeak = true;
                }
                else {
                    flag = false;
                    pProcInfo->xt.bSpeak = false;
                }

                HWND  hTalk;
                QY_MC* pQyMc = QY_GET_GBUF();
                //QY_MESSENGER_ID id;
                //id.ui64Id = 108;
                //if (!findTalker(pQyMc, &pProcInfo->hzj.idInfo_tmpGrp, &hTalk)) {
                if (findTalker(pQyMc, &param.idInfo_grp, &hTalk) != 0) {
                    iErr = 0;  goto  errLabel;
                }
                    

                MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
                if (pProcInfo == NULL) {
                    iErr = 0;  goto  errLabel;
                }
                FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
                if (pFuncs == NULL) {
                    iErr = 0;  goto  errLabel;
                }

                CHelp_getDlgTalkVar	help_getDlgTalkVar;
                HWND				hMgrTalk = hTalk;

                //DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hCurTalk, _T("viewIa"));
                //if (!pCurVar)
                //    iErr = 0;  goto  errLabel;;



                DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgrTalk, _T("dlgIa::OnBnClickedrequest"));
                if (pDlgTalkVar == nullptr) {
                    iErr = 0;  goto  errLabel;
                }

                //if (!pDlgTalkVar->av.taskInfo.bTaskExists)  
                //    iErr = 0;  goto  errLabel;;

                //  2014/07/26
                //CWaitCursor	cur;

                //  2010/09/02
                pFuncs->pf_setCurSharedObjUsr_localAv(pProcInfo, pDlgTalkVar->av.iIndex_sharedObj_localAv, pDlgTalkVar->av.iIndex_usr_localAv);

                //
                //  requestToSpeak(  !m_var.canSpeak  );
                pFuncs->pf_dlgTalk_requestToSpeak(hMgrTalk, flag, false);


                


                //
                confOthers_sendStreamInfo();

            }

            int respCode = 0;
            //
            sendRespToHg(respCode, p->sHgCmd, param.ui64MeetingId, &cliReply);

            //
            iErr = 0;  goto  errLabel;
        }

        //
        if (param.cmd_org == CONST_hgCmd_xt) {


            //
            qmcProc_xt_resp(&param);

            if (pCtxSm->debugPort != param.debugPort || strcmp(param.debugIp, pCtxSm->debugIp) != 0) {

                safeStrnCpy(param.debugIp, pCtxSm->debugIp, sizeof(pCtxSm->debugIp));
                pCtxSm->debugPort = param.debugPort;

                if (strlen(pCtxSm->debugIp) <= 0 || pCtxSm->debugPort <= 0) {
                    //DEFAULT_qyPort_showInfo_cli;
                    resetShowInfoServIp("127.0.0.1", DEFAULT_qyPort_showInfo_cli);
                }
                else {
                    resetShowInfoServIp(param.debugIp, param.debugPort);
                }
            }

            //
            iErr = 0;  goto  errLabel;
        }


        //
        if (param.cmd_org == CONST_hgCmd_usrLogin) {

            //if  (  param.iRc  ==  0  )
            {
                Var_ca_usr_qmc* pVc = &ctxSm.ca_usr;


                if (param.iRc == CONST_hgRc_login_firstOk
                    || param.iRc == CONST_hgRc_login_ok)

                {
                    //
                    pVc->usrLogin.bDone = true;

                    //
                    safeTcsnCpy(param.login_terminalName, pProcInfo->av.confLayout.login_termialName, mycountof(pProcInfo->av.confLayout.login_termialName));
                    safeTcsnCpy(param.login_userName, pProcInfo->av.confLayout.login_userName, mycountof(pProcInfo->av.confLayout.login_userName));

                    //
                    showInfo_open0(0, 0, _T(" recv usrLoginOk"));
                    //safeTcsnCpy(_T("收到用户登录成功的信息"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
                    safeTcsnCpy(_T("recv usrLoginOk"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
#ifdef  __DEBUG__
                    traceLog(pVc->tStatusBuf);
#endif

                    //
                    iErr = 0;  goto  errLabel;

                }

                //
                pVc->usrLogin.iRc       = param.iRc;
                
                safeTcsnCpy(param.rcDesc, pVc->usrLogin.tRcDesc, mycountof(pVc->usrLogin.tRcDesc));
                 

                //
                TCHAR  tBuf[128];
                _sntprintf(tBuf, mycountof(tBuf), _T("登录失败: %d"), param.iRc);
                safeTcsnCpy(tBuf, pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
                iErr = 0;  goto  errLabel;
            }

        }

        //
        if (p->sHgCmd == CONST_hgCmd_sndTerminalLogOut) {

            pCtxSm->bNeedRestart = true;
        }

        //
        if (p->sHgCmd == CONST_hgCmd_changeTerminalIp) {
            Sm_terminal_initCfg  initCfg;

            CCtxQyMc* pQyMc = g_pQyMc;
            memset(&initCfg, 0, sizeof(initCfg));

            //
            if (!bIpValid(param.terminalIp))  goto  errLabel;

            //
            bGetSmTerminalInitCfg(pQyMc->cfg.tmInitFile, &initCfg);

            //
            safeStrnCpy(param.terminalIp, initCfg.terminal_ip, mycountof(initCfg.terminal_ip));

            if (!pProcInfo->m_bUseKeyToLogin_forQmcGui) {
                //
                if (saveSmTerminalInitCfg(&initCfg, pQyMc->cfg.tmInitFile)) {
                }
            }

            //
            return 0;
        }

        //
        if (p->sHgCmd == CONST_hgCmd_overTime) {
            param.iOverTime;
            int i = 1;
        }
        /*
        if (p->ca_sendDataLen > sizeof(pVc->serv.ca_sendData))  goto  errLabel;
        memcpy(pVc->serv.ca_sendData, p->ca_sendData, p->ca_sendDataLen);
        pVc->serv.ca_sendDataLen = p->ca_sendDataLen;
        */
        pVc->sxrz.serv.param_sxrz_servReply = param;

        //
        pVc->flgs.sxrz.bGot_servReply = true;

        //
        showInfo_open0(0, 0, _T("recv servReply"));
        //safeTcsnCpy(_T("收到服务器信息"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
        safeTcsnCpy(_T("recv servReply"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

    }

    //
    iErr = 0;
errLabel:
    //
    return  iErr;
}

