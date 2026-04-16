#include <QtCore/QCoreApplication>

#include <stdio.h>
#include <iostream>
#include "Windows.h"
#include <time.h>
#include "HCNetSDK.h"
#include <qDebug>
#include <QTime>

//
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

#if  0
#include "./json/config.h"
#include "./json/reader.h"
#include "./json/writer.h"

#include "dhnetsdk.h"
#include "dhplay.h"
#include "dhconfigsdk.h"
#include "json/json.h"

#include "CSKF_API.h"
#endif 

#include <qytcharcommproc.h>

//#pragma comment(lib,"dhnetsdk.lib")

#pragma comment(lib,"Wininet")
#define safecountof(_Array) (_countof(_Array) - 1)
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "kernel32.lib")

//
#include    "qmOpenCommon.h"
#include <hk3ddw.h>
#include <ipcProc_open.h>
#include    "showInfo_open.h"
#include <ctxQmThread.h>


using namespace std;


void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID_q, LONG lHandle, void* pUser)
{
    char tempbuf[256] = { 0 };
    switch (dwType)
    {
    case EXCEPTION_RECONNECT:    //预览时重连
        printf("----------reconnect----------%d\n", time(NULL));
        break;
    default:
        break;
    }
}


#if  0
int iimain(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    DWORD dwReturned = 0;
    //---------------------------------------
    // 初始化
    NET_DVR_Init();
    //设置连接时间与重连时间
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);

    //---------------------------------------
    //设置异常消息回调函数
    NET_DVR_SetExceptionCallBack_V30(0, NULL, g_ExceptionCallBack, NULL);

    //---------------------------------------
    // 注册设备
    LONG lUserID_q;

    //登录参数，包括设备地址、登录用户、密码等
    NET_DVR_USER_LOGIN_INFO struLoginInfo = { 0 };
    struLoginInfo.bUseAsynLogin = 0; //同步登录方式
    strcpy_s(struLoginInfo.sDeviceAddress, "192.168.1.101"); //设备IP地址
    struLoginInfo.wPort = 8000; //设备服务端口
    strcpy_s(struLoginInfo.sUserName, "admin"); //设备登录用户名
    strcpy_s(struLoginInfo.sPassword, "test,234"); //设备登录密码

    //设备信息, 输出参数
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = { 0 };

    lUserID_q = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
    if (lUserID_q < 0)
    {
        printf("Login failed, error code: %d\n", NET_DVR_GetLastError());
        qDebug() << NET_DVR_GetLastError();


        NET_DVR_Cleanup();
        return -1;
    }


    //假设1920显示
    int std_cols = 1920; // 图像长宽
    int std_rows = 1080;

    //
    int xTop = 0;
    int  yTop = 50;

    //
    xTop = 200;
    yTop = 50;


    //
    NET_DVR_POINT_FRAME pStruPointFrame = { 0 };
    pStruPointFrame.xTop = (int)(xTop * 255 / std_cols); // 坐标归一化到(255, 255) //方框起始点的x坐标
    pStruPointFrame.yTop = (int)(yTop * 255 / std_rows);//方框起始点的y坐标
    pStruPointFrame.xBottom = pStruPointFrame.xTop;//方框结束点的x坐标
    pStruPointFrame.yBottom = pStruPointFrame.yTop;//方框结束点的y坐标
    DWORD dwReturn = 1;

    //这里用到的第一个通道号是33
    if (!NET_DVR_PTZSelZoomIn_EX(lUserID_q, 33, &pStruPointFrame))
    {
        printf("云台3D定位失败，错误码：%d\n", NET_DVR_GetLastError());
        qDebug() << NET_DVR_GetLastError();
        NET_DVR_Logout(lUserID_q);
        NET_DVR_Cleanup();
        return -1;
    }
    else
    {

        printf("云台3D定位成功！");
    }

    //注销用户
    NET_DVR_Logout(lUserID_q);

    //释放SDK资源
    NET_DVR_Cleanup();



    return a.exec();
}
#endif 


// 注册设备
LONG lUserID_q  =  0;




bool is_ipc = false;

//
int  hk_init(const std::string& devAddress, const std::string& username, const std::string& passwd)
{
    DWORD dwReturned = 0;
    //---------------------------------------
    // 初始化
    NET_DVR_Init();
    //设置连接时间与重连时间
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);

    //---------------------------------------
    //设置异常消息回调函数
    NET_DVR_SetExceptionCallBack_V30(0, NULL, g_ExceptionCallBack, NULL);

    //---------------------------------------

    //登录参数，包括设备地址、登录用户、密码等
    NET_DVR_USER_LOGIN_INFO struLoginInfo = { 0 };
    struLoginInfo.bUseAsynLogin = 0; //同步登录方式
    strcpy_s(struLoginInfo.sDeviceAddress, devAddress.c_str()/*"192.168.1.101"*/); //设备IP地址
    struLoginInfo.wPort = 8000; //设备服务端口
    strcpy_s(struLoginInfo.sUserName, username.c_str()/*"admin"*/); //设备登录用户名
    strcpy_s(struLoginInfo.sPassword, passwd.c_str()/*"test,234"*/); //设备登录密码

    //设备信息, 输出参数
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = { 0 };

    lUserID_q = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
    if (lUserID_q < 0)
    {
        printf("Login failed, error code: %d\n", NET_DVR_GetLastError());
        qDebug() << NET_DVR_GetLastError();

        showInfo_open0(0, _T("hk3ddw"), _T("Login failed, error code: %d\n"));

        NET_DVR_Cleanup();
        return -1;
    }

    if (struDeviceInfoV40.struDeviceV30.byChanNum > 0 && struDeviceInfoV40.struDeviceV30.byIPChanNum == 0) {
        is_ipc = true;
    }
    printLogChar("byIPChanNum", struDeviceInfoV40.struDeviceV30.byIPChanNum);
    printLogChar("byChanNum", struDeviceInfoV40.struDeviceV30.byChanNum);
    //printLogChar("byStartChan", struDeviceInfoV40.struDeviceV30.byStartChan);
    //printLogChar("byStartDChan", struDeviceInfoV40.struDeviceV30.byStartDChan);

    return  0;
}

//
int  hk_exit()
{
    //注销用户
    if (lUserID_q > 0) {
        NET_DVR_Logout(lUserID_q);
    }

    //释放SDK资源
    NET_DVR_Cleanup();


    return  0;
}


// 根据官方公式计算SDK坐标
void CalculateSDKCoordinates(int mouseX, int mouseY, int selectWidth, int selectHeight,
    int previewWidth, int previewHeight,
    int& xTop, int& yTop, int& xBottom, int& yBottom) {
    // 计算选择区域的起始点和结束点
    int startX = mouseX;
    int startY = mouseY;
    int endX = mouseX + selectWidth;
    int endY = mouseY + selectHeight;

    // 应用官方提供的计算公式
    xTop = startX * 255 / previewWidth;
    xBottom = endX * 255 / previewWidth;
    yTop = startY * 255 / previewHeight;
    yBottom = endY * 255 / previewHeight;

    xTop = (xTop < 0) ? 0 : ((xTop > 255) ? 255 : xTop);
    xBottom = (xBottom < 0) ? 0 : ((xBottom > 255) ? 255 : xBottom);
    yTop = (yTop < 0) ? 0 : ((yTop > 255) ? 255 : yTop);
    yBottom = (yBottom < 0) ? 0 : ((yBottom > 255) ? 255 : yBottom);
}

#define ZOOM_IN        11  // 变倍+
#define ZOOM_OUT       12  // 变倍-
#define ZOOM_STOP      13  // 变倍停止

bool Perform3DLocate(LONG userID, int channel, int mouseX, int mouseY,
    int selectWidth, int selectHeight,
    int previewWidth = 1920, int previewHeight = 1080) {
    // 计算SDK需要的坐标
    int xTop, yTop, xBottom, yBottom;
    CalculateSDKCoordinates(mouseX, mouseY, selectWidth, selectHeight,
        previewWidth, previewHeight,
        xTop, yTop, xBottom, yBottom);

    NET_DVR_POINT_FRAME pointFrame = { 0 };
    pointFrame.xTop = xTop;
    pointFrame.yTop = yTop;
    pointFrame.xBottom = xBottom;
    pointFrame.yBottom = yBottom;

    // 输出计算结果供调试
    /*std::cout << "计算的SDK坐标: "
        << "xTop=" << xTop << ", "
        << "yTop=" << yTop << ", "
        << "xBottom=" << xBottom << ", "
        << "yBottom=" << yBottom << std::endl;*/

    printLogChar("Perform3DLocate:begin");

    if (!NET_DVR_PTZControlWithSpeed_Other(userID, channel, ZOOM_STOP, 0, 0))
    {
        DWORD dwError = NET_DVR_GetLastError();
        //printf("停止变焦失败，错误码: %d\n", dwError);
        showInfo_open0(0, _T("hk3ddw"), _T("hk3ddw: NET_DVR_PTZControlWithSpeed_Other stop failed"));
        printLogChar("Perform3DLocate:NET_DVR_PTZControlWithSpeed_Other failed");
        printLogChar(dwError);
        LONG errNo = dwError;
        char* errMsg = NET_DVR_GetErrorMsg(&errNo);
        if(errMsg)
            printLogChar(errMsg);
    }
    else
    {
        //printf("变焦已停止\n");
        showInfo_open0(0, _T("hk3ddw"), _T("Perform3DLocate: NET_DVR_PTZControlWithSpeed_Other stop success"));
        printLogChar("Perform3DLocate: NET_DVR_PTZControlWithSpeed_Other stop success");
    }

    // 调用3D定位接口
    BOOL result = NET_DVR_PTZSelZoomIn_EX(userID, channel, &pointFrame);
    if (!result) {
        //std::cerr << "3D定位失败，错误码: " << NET_DVR_GetLastError() << std::endl;
        showInfo_open0(0, _T("hk3ddw"), _T("error: NET_DVR_PTZSelZoomIn_EX  "));
        DWORD dwError = NET_DVR_GetLastError();
        printLogChar("Perform3DLocate: NET_DVR_PTZSelZoomIn_EX failed");
        printLogChar(dwError);
        LONG errNo = dwError;
        char* errMsg = NET_DVR_GetErrorMsg(&errNo);
        if (errMsg)
            printLogChar(errMsg);
        return false;
    }
    else {
        printLogChar("Perform3DLocate:  NET_DVR_PTZSelZoomIn_EX success");
    }

    printLogChar("Perform3DLocate:end ");

    //Sleep(3000);

    // 停止变焦
   /* result = NET_DVR_PTZSelZoomIn_EX(userID, channel, 0);
    if (result) {
        cout << "变焦操作已停止" << endl;
        showInfo_open0(0, 0, _T("hk3ddw: NET_DVR_PTZSelZoomIn_EX stop success"));
    }
    else {
        cout << "停止变焦失败，错误码: " << NET_DVR_GetLastError() << endl;
        showInfo_open0(0, 0, _T("hk3ddw: NET_DVR_PTZSelZoomIn_EX stop failed"));
    }*/

    


    //std::cout << "3D定位命令已发送，鼠标坐标: (" << mouseX << ", " << mouseY << ")" << std::endl;
    return true;
}


//
int  hk_do3ddw(int channel, int std_cols, int std_rows, int xTop, int  yTop, int xBottom, int yBottom)
{
    //
    OutputDebugString(_T("hk_do3ddw: called\n"));

    if (std_cols <= 0 || std_rows <= 0) {
        showInfo_open0(0, _T("hk3ddw"), _T("error: std_cols || std_rows <= 0 "));
        return -1;
    }

    // 示例：在1920 1080的预览窗口中，鼠标点击(176, 144)位置，选择区域大小为10x10
 //窗口大小
    int previewWidth = std_cols;//1920;
    int previewHeight = std_rows;//1080;

    int mouseX = xTop;//200;  // 鼠标点击位置X
    int mouseY = yTop;//50;  // 鼠标点击位置Y
    int selectWidth = 50;  // 选择区域宽度
    int selectHeight = 50; // 选择区域高度


    showInfo_open0(0, 0, _T("hk3ddw"));
    printLogChar("hk3ddw");

    TCHAR tBuf[256];

    _sntprintf(tBuf, mycountof(tBuf), _T("hk3ddw11:  wh %dX%d, top %d,%d, select %d,%d"),
        (int)previewWidth, (int)previewHeight,
        (int)mouseX, (int)mouseY, (int)selectWidth, (int)selectHeight);

    //
    showInfo_open0(0, 0, tBuf);
    printLogChar("hk_do3ddw:Perform3DLocate begin");

    int newChannel = channel;
    if (!is_ipc) {
        newChannel += 32;
    }

    // 执行3D定位  //这里用到的第一个通道号是33
    if (Perform3DLocate(lUserID_q, newChannel /*channel + 32 * / /*33*/, mouseX, mouseY, selectWidth, selectHeight, previewWidth, previewHeight)) {
        //std::cout << "3D定位请求成功发送!" << std::endl;
        showInfo_open0(0, _T("hk3ddw"), _T("hk3ddw: Perform3DLocate success"));
        printLogChar("hk_do3ddw:Perform3DLocate success");
    }
    else {
        printLogChar("hk_do3ddw:Perform3DLocate failed");
    }

    return  0;
}

#include <locale>
#include <codecvt>
#include <string>




std::string UnicodeToANSI(const std::wstring& wstr)
{
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4996)
#endif

    // Note: This is deprecated in C++17 but still works in many implementations
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);

#ifdef _MSC_VER
#pragma warning(pop)
#endif
}



//
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

    //
    Hk3ddwProc* pGBuf = &gBuf_hk3ddw;

    //
    parseCmdLine_ipcProc(cmdLine, &pGBuf->m_var.appParams);

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
            if (initShowInfo_func(0, _T("syncQ_showInfo_dh"), errHintWndCls, false, true, (char*)"127.0.0.1", bCli, &pGBuf->m_var.pShowInfoStruct)) {
                //goto  errLabel;
                break;
            }
            bShowInfoInited = TRUE;

            //
            set_who_showInfo(_T("hk3ddw"));

            //
            if (pGBuf->m_var.appParams.nvrIp[0] == 0) {
                showInfo_open0(0, _T("hk3ddw"), _T("nvrIp is null, failed"));
                break;
            }

            //
            pGBuf->m_var.m_bAutoClose_ifToolLongNoRecvd_dh = true;

#ifdef  _DEBUG
            //gBuf_dhListIp.m_var.m_bAutoClose_ifToolLongNoRecvd_dh = false;
#endif

        //
            pGBuf->m_var.dwLastTickCnt_recvd = myGetTickCount(nullptr);

            //
            pGBuf->m_var.pQisPipe = qisPipeNew();
            if (!pGBuf->m_var.pQisPipe)  break;

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
            int  tn = CONST_ipcProcPipe_tn_hk3ddw;

            //		  
            M_get_pipeName(CONST_ipcProcPipePrefix, _T(""), tn, pipeName);


            //
            PARAM_initQisPipe  param = { 0 };
            param.pf_onRead = hk3ddw_qisPipe_onRead;
            //
            param.uiMaxToInMs_read = CONST_toInMs_pipe_read;

            //
            if (initQisPipe(&qCfg, pipeName, false, _T("hk3ddw"), &param, pGBuf->m_var.pQisPipe)) {
                showInfo_open0(0, _T("hk3ddw"), _T("initQisPipe failed\n"));
                break;
            }

       
            //
            if (hk_init(pGBuf->m_var.appParams.nvrIp, UnicodeToANSI(pGBuf->m_var.appParams.nvrUsr),
                pGBuf->m_var.appParams.nvrPwd)) {
                //
                OutputDebugString(_T("hk_init failed\n"));
                showInfo_open0(0, _T("hk3ddw"), _T("hk_init failed\n"));
                break;
            }

            //
            //hk_do3ddw(0,0,0,0,0,0);

            //
            for (; ; ) {


                //
                if (pGBuf->m_var.m_bAutoClose_ifToolLongNoRecvd_dh) {
                    //
                    DWORD  dwTickCnt = myGetTickCount(nullptr);
                    int iDiffInMs = dwTickCnt - pGBuf->m_var.dwLastTickCnt_recvd;
                    if (abs(iDiffInMs) > CONST_toInMs_ipcProc) {
                        //
                        showInfo_open0(0, _T("hk3ddw"), _T("too long to recv, quit now\n"));
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
        hk_exit();



        //
        exitQisPipe(pGBuf->m_var.pQisPipe);

        //
        exitShowInfo(&pGBuf->m_var.pShowInfoStruct);

    }
    catch (...)
    {
        printf("exception\n");

        exit(0);
    }

    //
    printf("hk3ddw finished\n");

    //
    return  iErr;
}




