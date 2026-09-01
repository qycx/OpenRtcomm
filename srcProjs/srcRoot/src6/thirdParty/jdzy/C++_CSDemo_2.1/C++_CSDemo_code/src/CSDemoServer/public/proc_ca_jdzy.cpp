
#include	"stdafx.h"

#include	<tchar.h>

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string.h>

#include    <tchar.h>
//
#include    "tmpRegFunc_open.h"
#include <showInfo_open.h>

#include	"proc_ca_jdzy.h"

#include "define_head.h"



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
    FILE* pf = fopen("D:/qycx/log_srv.txt", "a+");
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
    FILE* pf = fopen("D:\\qycx\\log_srv.txt", "a+");
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


//
int jdzy_main(  TCHAR  *  cmdLine,  bool *pbProcessed  )
{
    int  iErr = -1;
    TCHAR* pT;
    //TCHAR  cmdLine[256] = _T("");
    int  ii;
    TCHAR  tBuf[128];

#if 0
    for (ii = 0; ii < argc; ii++) {
        _sntprintf(cmdLine, mycountof(cmdLine), _T("%s %s"), cmdLine, argv[ii]);
    }
#endif


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

    //
    gBuf.m_var.hKeyRoot0 = gBuf.m_var.appParams.bSys ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER;

    //
    bool  bGet_sendData = false;
    bool  bGet_loginAuth = false;

    //
    switch (gBuf.m_var.appParams.iCmd) {
#if 0
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
#endif
    case  CONST_caCmd_getRandom:
          break;
    default:
        break;
    }


    //
    CString  strGateWayIP = _T(  "124.207.188.210"  );
    CString  strGateWayPort = _T("6180");
    CString  strAppFlag = _T("testApp");
    bool  bIsPlain = true;

    //
   // TCHAR  tBuf[128];

    //
    strGateWayIP = gBuf.m_var.appParams.caGwIp;
    strGateWayPort = _ltot(gBuf.m_var.appParams.caGwPort,tBuf,10);



    //
    //指定XML报文版本为11，即 随机数由网关生成
    int nXMLVer = 11;

    //创建对象
    gBuf.m_var.m_pServerAuth = new CServerAuth(strGateWayIP, strGateWayPort, strAppFlag, bIsPlain, nXMLVer);
    if (gBuf.m_var.m_pServerAuth == NULL)
    {
        //MessageBox(_T("对象创建失败！"), _T("提示"), MB_OK);
        goto  errLabel;
    }



    if (gBuf.m_var.appParams.iCmd) {
        *pbProcessed = true;
    }
    else {
        *pbProcessed = false;
    }


    //
    if (gBuf.m_var.appParams.iCmd == CONST_caCmd_getRandom) {

        //
        jdzy_ca_getRandom();


        //
        iErr = 0;  goto  errLabel;

    }
    if (gBuf.m_var.appParams.iCmd == CONST_caCmd_login_auth) {

        //
        jdzy_ca_login_auth();


        //
        iErr = 0;  goto  errLabel;

    }





    iErr = 0;


    //
errLabel:
END:

    if (gBuf.m_var.m_pServerAuth) {
        delete  gBuf.m_var.m_pServerAuth;
        gBuf.m_var.m_pServerAuth = NULL;
    }
    


#ifdef  __USE_showInfo__
    showInfo_open0(0, 0, _T("jdzy leaves"));
    //printLog("jdzy leaves");
    //
    exitShowInfo(&gBuf.m_var.pShowInfoStruct);
#endif


    return  0;

}



