#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <comutil.h>
#include <strsafe.h>
#include <strsafe.h>
#include <WinInet.h>
#include <regex>
#include <string>

#include "./json/config.h"
#include "./json/reader.h"
#include "./json/writer.h"

#include "dhnetsdk.h"
#include "dhplay.h"
#include "dhconfigsdk.h"
#include "json/json.h"

#include "CSKF_API.h"
#include <qytcharcommproc.h>

#pragma comment(lib,"dhnetsdk.lib")

#pragma comment(lib,"Wininet")
#define safecountof(_Array) (_countof(_Array) - 1)
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "kernel32.lib")

//
#include    "qmOpenCommon.h"
#include <hikListIpProc.h>
#include <ipcProc_open.h>
#include    "showInfo_open.h"
#include <ctxQmThread.h>



using namespace std;
void __stdcall DisConnectFunc(LLONG lLoginID, char* pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    printf("Device disconnect, IP=%s, Port=%d\n", pchDVRIP, nDVRPort);
}

void __stdcall SubDisConnectFunc(EM_INTERFACE_TYPE emInterfaceType, BOOL bOnline, LLONG lOperateHandle, LLONG lLoginID, LDWORD dwUser)
{
    switch (emInterfaceType)
    {
    case DH_INTERFACE_REALPLAY:
        printf("实时监视接口: Short connect is %d\n", bOnline);
        break;
    case DH_INTERFACE_PREVIEW:
        printf("多画面预览接口: Short connect is %d\n", bOnline);
        break;
    case DH_INTERFACE_PLAYBACK:
        printf("回放接口: Short connect is %d\n", bOnline);
        break;
    case DH_INTERFACE_DOWNLOAD:
        printf("下载接口: Short connect is %d\n", bOnline);
        break;
    default:
        break;
    }
}

std::string Utf8ToGbk(const char* src_str) {
    int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
    wchar_t* wszGBK = new wchar_t[len + 1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
    char* szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
    std::string strTemp(szGBK);
    if (wszGBK) delete[] wszGBK;
    if (szGBK) delete[] szGBK;
    return strTemp;
}

//
#if 0
extern  "C"  WCHAR * myUtf82WChar(char* str, WCHAR * wBuf, unsigned  int  wBufSize)
{
    int		iErr = -1;
    int		wBufSizeNeeded = 0;
    UINT	uiCodePage = CP_UTF8;

    wBufSizeNeeded = MultiByteToWideChar(uiCodePage, 0, str, -1, wBuf, 0);
    if (wBufSizeNeeded > (int)wBufSize)  goto  errLabel;
    if (wBufSizeNeeded != MultiByteToWideChar(uiCodePage, 0, str, -1, wBuf, wBufSize))  goto  errLabel;
    iErr = 0;
errLabel:
    return  iErr ? NULL : wBuf;
}
#endif



//
//int main(int argc,char **argv)
int _tmain(int argc, TCHAR* argv[])
{
    //
    int  iErr = -1;
    TCHAR* pT;
    TCHAR  cmdLine[1024] = _T("");
    int  ii;
    TCHAR  tBuf[256];

    for (ii = 0; ii < argc; ii++) {
        _sntprintf(cmdLine, mycountof(cmdLine), _T("%s %s"), cmdLine, argv[ii]);
    }

    printLogChar("hik-----_tmain");

    //
    parseCmdLine_ipcProc(cmdLine, &gBuf_dhListIp.m_var.appParams);

    try {

        do {

            //
            init_tickCnt();

            //
            bool  bCli = true;

            //
            bool  bShowInfoInited = false;
            TCHAR* errHintWndCls = (TCHAR*)_T("mmsmsm");//CONST_qnmStatusToolWndClass;
            //if  (  initShowInfo(  0,  _T(  "syncQ_showInfo_qmd"  ),  errHintWndCls,  TRUE,  FALSE,  &mcDaemon.var.pShowInfoStruct  )  )  goto  errLabel;
            if (initShowInfo_func(0, _T("syncQ_showInfo_dh"), errHintWndCls, false, true, (char*)"127.0.0.1", bCli, &gBuf_dhListIp.m_var.pShowInfoStruct)) {
                //goto  errLabel;
                break;
            }
            bShowInfoInited = TRUE;

            //
            set_who_showInfo(_T("dhListIp"));

            //
            if (gBuf_dhListIp.m_var.appParams.nvrIp[0] == 0) {
                showInfo_open0(0, 0, _T("dhListIp: nvrIp is null, failed"));
                break;
            }

            //
            gBuf_dhListIp.m_var.m_bAutoClose_ifToolLongNoRecvd_dh = true;

#ifdef  _DEBUG
            //gBuf_dhListIp.m_var.m_bAutoClose_ifToolLongNoRecvd_dh = false;
#endif

        //
            gBuf_dhListIp.m_var.dwLastTickCnt_recvd = myGetTickCount(nullptr);

            //
            gBuf_dhListIp.m_var.pQisPipe = qisPipeNew();
            if (!gBuf_dhListIp.m_var.pQisPipe)  break;

            //
                      //
            GENERIC_Q_CFG  qCfg = { 0 };
            TCHAR   pipeName[128] = _T("");
            int  tn_rtspCliPipe = 0;// pParams->tn_cliPipe;
            //
            _sntprintf(qCfg.name, mycountof(qCfg.name), _T("qisPipe"));
            _sntprintf(qCfg.mutexName_prefix, mycountof(qCfg.mutexName_prefix), _T("qiqPipe"));
            qCfg.uiMaxQNodes = 100;	//  CONST_uiMaxQNodes_outputQ_256;

            //		  
            M_get_pipeName(CONST_ipcProcPipePrefix, _T(""), CONST_ipcProcPipe_tn_hikListIp, pipeName);


            //
            PARAM_initQisPipe  param = { 0 };
            param.pf_onRead = dhListIp_qisPipe_onRead;
            //
            param.uiMaxToInMs_read = CONST_toInMs_pipe_read;

            //
            initQisPipe(&qCfg, pipeName, false, _T("hikListIp"), &param, gBuf_dhListIp.m_var.pQisPipe);






            //初始化
            CLIENT_Init(DisConnectFunc, 0);
            CLIENT_SetSubconnCallBack(SubDisConnectFunc, 0);


            NET_IN_LOGIN_WITH_HIGHLEVEL_SECURITY stInparam;
            memset(&stInparam, 0, sizeof(stInparam));
            stInparam.dwSize = sizeof(stInparam);
            //strncpy(stInparam.szIP, "10.0.1.169", sizeof(stInparam.szIP) - 1);
            strncpy(stInparam.szIP, gBuf_dhListIp.m_var.appParams.nvrIp, sizeof(stInparam.szIP) - 1);
            //strncpy(stInparam.szUserName, "admin", sizeof(stInparam.szUserName) - 1);
            myTChar2Utf8(gBuf_dhListIp.m_var.appParams.nvrUsr, stInparam.szUserName, mycountof(stInparam.szUserName));
            //strncpy(stInparam.szPassword, "test,234", sizeof(stInparam.szPassword) - 1);
            strncpy(stInparam.szPassword, gBuf_dhListIp.m_var.appParams.nvrPwd, sizeof(stInparam.szPassword) - 1);
            //
            stInparam.nPort = 37777;
            stInparam.emSpecCap = EM_LOGIN_SPEC_CAP_TCP;
            NET_OUT_LOGIN_WITH_HIGHLEVEL_SECURITY stOutparam;
            memset(&stOutparam, 0, sizeof(stOutparam));
            stOutparam.dwSize = sizeof(stOutparam);

            LLONG lLoginHandle = NULL;
            LLONG lRealHandle = NULL;
            LLONG lSearch = NULL;
            //注册用户到设备
            lLoginHandle = CLIENT_LoginWithHighLevelSecurity(&stInparam, &stOutparam);
            DWORD dwError = CLIENT_GetLastError() & (0x7fffffff);

            Json::Value return_root;
            Json::Reader reader;
            Json::Value value;
            Json::FastWriter return_writer;

            int nerror = 0;
            char* szOutBuffer = new char[32 * 1024];
            memset(szOutBuffer, 0, 32 * 1024);

            //
            NvrInfo nvrInfo = { 0 };

            //获取网络信息
            BOOL r1 = CLIENT_GetNewDevConfig(lLoginHandle, (char*)CFG_CMD_REMOTEDEVICE, 2, szOutBuffer, 32 * 1024, &nerror);
            int b = CLIENT_GetLastError() & (0x7fffffff);

            reader.parse(szOutBuffer, value);
            Json::Value devs = value["params"]["table"];
            Json::Value::Members member = devs.getMemberNames();
            int i = 0;
            for (Json::Value::Members::iterator iter = member.begin(); iter != member.end(); ++iter)
            {
                if (devs[*iter]["Enable"].asBool())
                {
                    Json::Value item;
                    item["Channel"] = ++i;
                    item["Ip"] = devs[*iter]["Address"];
                    //
                    //
                    return_root.append(item);
                }
            }

            //获取通道名称
            memset(szOutBuffer, 0, 32 * 1024);
            BOOL r2 = CLIENT_GetNewDevConfig(lLoginHandle, (char*)CFG_CMD_CHANNELTITLE, -1, szOutBuffer, 32 * 1024, &nerror);
            reader.parse(szOutBuffer, value);




            //
            Json::Value channels = value["params"]["table"];
            for (unsigned int i = 0; i < return_root.size(); ++i)
            {
                std::string name = channels[i]["Name"].asString();

                //
                std::string ip = return_root[i]["Ip"].asString();
                //
                TCHAR  tName[256];
                myUtf82TChar((char*)name.c_str(), tName, sizeof(tName) / sizeof(tName[0]));
                //
                NvrInfo* pNvrInfo = &gBuf_dhListIp.m_var.nvrInfo;
                if (pNvrInfo->usCnt < mycountof(pNvrInfo->mems)) {
                    IpcInfo* pMem = &pNvrInfo->mems[pNvrInfo->usCnt];
                    //
                    pMem->iChannel = return_root[i]["Channel"].asInt();
                    strncpy(pMem->ip, ip.c_str(), mycountof(pMem->ip));
                    lstrcpyn(pMem->name, tName, mycountof(tName));

                    //
                    pNvrInfo->usCnt++;
                }


                //
                return_root[i]["Name"] = Utf8ToGbk(name.c_str());
            }
            //
            gBuf_dhListIp.m_var.m_bGot_nvrInfo = true;

            //
            std::string result = return_writer.write(return_root);
            std::cout << result << std::endl;

            delete szOutBuffer;

            //
            for (; ; ) {

                //
                if (gBuf_dhListIp.m_var.m_bDone_nvrInfo
                    )
                {
                    //
                    //Sleep(1000);
                    //
                    break;
                }

                //
                if (gBuf_dhListIp.m_var.m_bAutoClose_ifToolLongNoRecvd_dh) {
                    //
                    DWORD  dwTickCnt = myGetTickCount(nullptr);
                    int iDiffInMs = dwTickCnt - gBuf_dhListIp.m_var.dwLastTickCnt_recvd;
                    if (abs(iDiffInMs) > CONST_toInMs_ipcProc) {
                        //
                        showInfo_open0(0, _T("dhListIp"), _T("too long to recv, quit now\n"));
                        //
                        break;
                    }
                }


                //
                Sleep(1000);

                //
                continue;
            }

            //
            iErr = 0;

        } while (false);


        //
        exitQisPipe(gBuf_dhListIp.m_var.pQisPipe);

        //
        exitShowInfo(&gBuf_dhListIp.m_var.pShowInfoStruct);

    }
    catch (...)
    {
        printf("exception\n");

        exit(0);
    }

    //
    printf("dhListIp finished\n");

    //
    return  iErr;
}
