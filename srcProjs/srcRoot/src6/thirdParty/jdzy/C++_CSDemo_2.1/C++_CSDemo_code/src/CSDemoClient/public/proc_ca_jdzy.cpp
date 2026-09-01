

#include	"stdafx.h"

#include	<tchar.h>
#include	<MMSystem.h>

#include    "tmpRegFunc_open.h"
#include    "showInfo_open.h"

#include    "myCmdParams_open.h"

#include	"proc_ca_jdzy.h"

#include "ClientAuth.h"



GBuf_jdzy	gBuf;


//
GBuf_jdzy::GBuf_jdzy()
{
	//
	memset(&m_var, 0, sizeof(m_var));

	//
	return;
}


//
GBuf_jdzy::~GBuf_jdzy()
{
	return;
}

void TcharToChar(const TCHAR* ptchar, char* pchar)
{
    int iLength;
    //获取字节长度   
    iLength = WideCharToMultiByte(CP_ACP, 0, ptchar, -1, NULL, 0, NULL, NULL);
    //将ptchar值赋给pchar    
    WideCharToMultiByte(CP_ACP, 0, ptchar, -1, pchar, iLength, NULL, NULL);
}

void CharToTchar(const char* _char, TCHAR* tchar)
{
    int iLength;

    iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
    MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

#include <stdio.h>                                                                 
#include <tchar.h>                                                                 

char* UnicodeToAnsi(const wchar_t* szStr, int& nLen)
{
    nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
    if (nLen == 0)
    {
        return NULL;
    }
    char* pResult = new char[nLen];
    WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
    return pResult;
}

/*
void  main() {

    TCHAR msg[100];
    swprintf_s(msg, L"sjlkjdkld");
    char* str = UnicodeToAnsi(msg);

}*/



int printLogChar(const char* log) {
    return 0;
    FILE* pf = fopen("D:/qycx/log.txt", "a+");
    if (pf == NULL)
    {
        perror("fopen failed");
        //
        return 1;
    }

    //TCHAR* pp;  
 

    fprintf(pf, "%s:%s  - %s \n", __DATE__, __TIME__, log);

    fclose(pf);

    return 0;

}


int printLog(TCHAR* log) {
    return 0;
    FILE* pf = fopen("D:\\qycx\\log.txt", "a+");
    if (pf == NULL)
    {
        perror("fopen failed");
        //
        return 1;
    }

    //TCHAR* pp;

    char* pBuf = NULL;
    int nLen = 0;

    pBuf = UnicodeToAnsi(log, nLen);

    if (pBuf) {
        fprintf(pf, "%s:%s  - %s \n", __DATE__, __TIME__, pBuf);
        delete[] pBuf;
    }

    fclose(pf);

}
#define BUFFER_MED_SIZE 1024

inline void LogToFile(const _TCHAR* szFmt, ...)
{
    va_list args;
    TCHAR szBuf[BUFFER_MED_SIZE] = { 0 };

    va_start(args, szFmt);
    _vstprintf_s(szBuf, BUFFER_MED_SIZE, szFmt, args);
    va_end(args);
}


//
int jdzy_main(TCHAR* cmdLine)
{
   
    //
    int  iErr = -1;
    TCHAR* pT;
    int  ii;
    TCHAR  tBuf[128];


    //
    parseCmdLine_ca(cmdLine, &gBuf.m_var.appParams);

    //
#ifdef  __USE_showInfo__
    initShowInfo_cli(0, _T("syncQ_showInfo_qmc"), (char*)"127.0.0.1", &gBuf.m_var.pShowInfoStruct);
    //
#if 0
    if (gBuf.m_var.appParams.bSys) set_who_showInfo(_T("bjca.serv"));
    else  set_who_showInfo(_T("bjca.cli"));
#endif
    set_who_showInfo(gBuf.m_var.appParams.who_showInfo);
#endif

    //
#ifdef  __USE_showInfo__
    _sntprintf(tBuf, mycountof(tBuf), _T("jdzy cmd %d, tn %d, sys %d, devPre %s, dev %d"), gBuf.m_var.appParams.iCmd, gBuf.m_var.appParams.tn, gBuf.m_var.appParams.bSys,
        gBuf.m_var.appParams.devPrefix, gBuf.m_var.appParams.bDev);
    showInfo_open0(0, 0, tBuf);

    
#endif

    //printLogChar("cmd info--------begin-------------");
    //printLog(tBuf);
    //printLogChar("cmd info--------end-------------");

    //
    gBuf.m_var.hKeyRoot0 = gBuf.m_var.appParams.bSys ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER;

    //
    bool  bGet_sendData = false;
    bool  bGet_loginAuth = false;

    if (CONST_caCmd_usrData) {

    }

    if (gBuf.m_var.appParams.iCmd == CONST_caCmd_chkUsrKey) {
        InitGm(false);

        std::string strCertSN = g_pGmTest->GM_GetSignCertSN();

        if (strCertSN.length() <= 0) {
#ifdef  __USE_showInfo__
            showInfo_open0(0, 0, _T("check usb key failed"));
#endif
        }
        else {
            char resp[1024];
            _snprintf(resp, mycountof(resp), "%s%d", CONST_sym_bExists_usrKey, 1);

            //
            {
                TCHAR  cfgName[128];
                _sntprintf(cfgName, mycountof(cfgName), _T("%s%d"), _T(CONST_regValName_ca_chkUsrKeyResp_prefix), gBuf.m_var.appParams.tn);
                unsigned int  uiType;
                uiType = REG_BINARY;
                tmpSetRegCfg_open(gBuf.m_var.hKeyRoot0, _T(CONST_rootKey_ca), cfgName, uiType, resp, strlen(resp));
            }

#ifdef  __USE_showInfo__
            showInfo_open0(0, 0, _T("check usb key success"));
#endif
        }

        iErr = 0;  
        goto  errLabel;
    }
    else {
        InitGm(true);
    }   

    //
    switch (gBuf.m_var.appParams.iCmd) {
    case  CONST_caCmd_login_sendData:
        bGet_sendData = true;
        break;
    case  CONST_caCmd_login_auth:
        bGet_loginAuth = true;
        break;
    case  CONST_caCmd_usrData:
        bGet_sendData = true;
        bGet_loginAuth = true;
        break;
    default:
        break;
    }

    //
    gBuf.m_var.m_pClientAuth = new CClientAuth();

    //
    if (gBuf.m_var.appParams.iCmd == CONST_caCmd_login_sendData) {
        jdzy_ca_sendData();
        iErr = 0;  goto  errLabel;
    }
    else if (gBuf.m_var.appParams.iCmd == CONST_caCmd_login_auth) {

        TCHAR  cfgName_resp_cli_cert[128];
        TCHAR  cfgName_resp_cli_signData[128];

        const char* tmp = "xxxx";

        _sntprintf(cfgName_resp_cli_cert, mycountof(cfgName_resp_cli_cert), _T("%s%d"), _T(CONST_regValName_cli_cert_prefix), gBuf.m_var.appParams.tn);
        _sntprintf(cfgName_resp_cli_signData, mycountof(cfgName_resp_cli_signData), _T("%s%d"), _T(CONST_regValName_cli_signData_prefix), gBuf.m_var.appParams.tn);


        unsigned int  uiType = 0;
        uiType = REG_BINARY;
        tmpSetRegCfg_open(gBuf.m_var.hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_cli_cert, uiType, (char*)tmp, strlen(tmp));
        tmpSetRegCfg_open(gBuf.m_var.hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_cli_signData, uiType, (char*)tmp, strlen(tmp));
    }

    //
errLabel:
END:

    if (gBuf.m_var.m_pClientAuth) {
        delete  gBuf.m_var.m_pClientAuth;
        gBuf.m_var.m_pClientAuth = NULL;
    }

    //
#ifdef  __USE_showInfo__
    showInfo_open0(0, 0, _T("jdzy leaves"));
    //
    exitShowInfo(&gBuf.m_var.pShowInfoStruct);
#endif

    //
    return 0;
}


