// dh.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include    <mmsystem.h>
#include    "qmOpenCommon.h"
#include "d4k.h"
#include    "d4kProc.h"
#include <ctxQmThread.h>
#include "myTypes.h"
#include    "ipcProc_open.h"



#include <showInfo_open.h>


//
#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
int ExitInstance();

//
DhProc  gBuf_dh;



//
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DH));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    //
    ExitInstance();

    //
    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DH);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   
   //
   int  iErr = -1;

   //
   do {
       //
       init_tickCnt();


       printLogChar("InitInstance");

       //
       bool  bCli = true;

       //
       bool  bShowInfoInited = false;
       TCHAR* errHintWndCls = (TCHAR*)_T("mmsmsm");//CONST_qnmStatusToolWndClass;
       //if  (  initShowInfo(  0,  _T(  "syncQ_showInfo_qmd"  ),  errHintWndCls,  TRUE,  FALSE,  &mcDaemon.var.pShowInfoStruct  )  )  goto  errLabel;
       if (initShowInfo_func(0, _T("syncQ_showInfo_d4k"), errHintWndCls, false, true, (char*)"127.0.0.1", bCli, &gBuf_dh.m_var.pShowInfoStruct)) {
           //goto  errLabel;
           break;
       }
       bShowInfoInited = TRUE;

       //
       set_who_showInfo(_T("d4k"));

       //
       TCHAR* cmdLine = GetCommandLine();
       //
       showInfo_open0(0, _T("d4k.haha"), cmdLine);
       //
       parseCmdLine_ipcProc(cmdLine, &gBuf_dh.m_var.appParams);



       //
       DhProcCfg* pCfg = &gBuf_dh.m_var.cfg;
       //
       GetModuleFileName(NULL, pCfg->installDir, mycountof(pCfg->installDir));
       showInfo_open0(0, _T("moduleFileName"), pCfg->installDir);
       TCHAR* pT = _tcsrchr(pCfg->installDir, _T('\\'));
       if (pT == NULL) break;// goto errLabel;
       *pT = 0;
       pT = _tcsrchr(pCfg->installDir, _T('\\'));
       if (pT == NULL) break;// goto errLabel;
       pT++; *pT = 0;
       showInfo_open0(0, _T("installDir"), pCfg->installDir);


       //      
       if  ( 10  )
       {
           //
           gBuf_dh.m_var.qm.pQisPipe = qisPipeNew();
           if (!gBuf_dh.m_var.qm.pQisPipe)  break;

           //
           GENERIC_Q_CFG  qCfg = { 0 };
           TCHAR   pipeName[128] = _T("");
           int  tn_rtspCliPipe = 0;// pParams->tn_cliPipe;
           //
           _sntprintf(qCfg.name, mycountof(qCfg.name), _T("qisPipe"));
           _sntprintf(qCfg.mutexName_prefix, mycountof(qCfg.mutexName_prefix), _T("qiqPipe"));
           qCfg.uiMaxQNodes = 100;	//  CONST_uiMaxQNodes_outputQ_256;

           //		  
           M_get_pipeName(CONST_ipcProcPipePrefix, _T(""), CONST_ipcProcPipe_tn, pipeName);


           //
           PARAM_initQisPipe  param = { 0 };
           param.pf_onRead = dh_qisPipe_onRead;
           param.uiMaxToInMs_read = CONST_toInMs_pipe_read;

           //
           initQisPipe(&qCfg, pipeName, false, _T("dh.qm"), &param, gBuf_dh.m_var.qm.pQisPipe);

           //
       }
   ///////////      
   //
       {
           gBuf_dh.m_var.dhListIp.pQisPipe = qisPipeNew();
           if (!gBuf_dh.m_var.dhListIp.pQisPipe)  break;

           //
           GENERIC_Q_CFG  qCfg = { 0 };
           TCHAR   pipeName[128] = _T("");
           int  tn_rtspCliPipe = 0;// pParams->tn_cliPipe;
           //
           _sntprintf(qCfg.name, mycountof(qCfg.name), _T("qisPipe"));
           _sntprintf(qCfg.mutexName_prefix, mycountof(qCfg.mutexName_prefix), _T("qiqPipe"));
           qCfg.uiMaxQNodes = 100;	//  CONST_uiMaxQNodes_outputQ_256;

           //		  
           M_get_pipeName(CONST_ipcProcPipePrefix, _T(""), CONST_ipcProcPipe_tn_d4kListIp, pipeName);

           

           //
           PARAM_initQisPipe  param = { 0 };
           param.pf_onRead = dh_listIp_qisPipe_onRead;
           param.uiMaxToInMs_read = CONST_toInMs_pipe_read;

           //
#ifdef  _DEBUG
           //param.bPrint_write = true;
#endif

           //
           initQisPipe(&qCfg, pipeName, true, _T("d4k.listIp"), &param, gBuf_dh.m_var.dhListIp.pQisPipe);

           //

       }


       //
       {
           gBuf_dh.m_var.dhDeviceControl.pQisPipe = qisPipeNew();
           if (!gBuf_dh.m_var.dhDeviceControl.pQisPipe)  break;

           //
           GENERIC_Q_CFG  qCfg = { 0 };
           TCHAR   pipeName[128] = _T("");
           int  tn_rtspCliPipe = 0;// pParams->tn_cliPipe;
           //
           _sntprintf(qCfg.name, mycountof(qCfg.name), _T("qisPipe"));
           _sntprintf(qCfg.mutexName_prefix, mycountof(qCfg.mutexName_prefix), _T("qiqPipe"));
           qCfg.uiMaxQNodes = 100;	//  CONST_uiMaxQNodes_outputQ_256;

           //		  
           M_get_pipeName(CONST_ipcProcPipePrefix, _T(""), CONST_ipcProcPipe_tn_d4kDeviceControl, pipeName);


           //
           PARAM_initQisPipe  param = { 0 };
           param.pf_onRead = dh_deviceControl_qisPipe_onRead;
           param.uiMaxToInMs_read = CONST_toInMs_pipe_read;

           //
#ifdef  _DEBUG
           //param.bPrint_write = true;
#endif

           //
           initQisPipe(&qCfg, pipeName, true, _T("d4k.deviceControl"), &param, gBuf_dh.m_var.dhDeviceControl.pQisPipe);

           //

       }


       /*
       {
           gBuf_dh.m_var.dhPtz.pQisPipe = qisPipeNew();
           if (!gBuf_dh.m_var.dhPtz.pQisPipe)  break;

           //
           GENERIC_Q_CFG  qCfg = { 0 };
           TCHAR   pipeName[128] = _T("");
           int  tn_rtspCliPipe = 0;// pParams->tn_cliPipe;
           //
           _sntprintf(qCfg.name, mycountof(qCfg.name), _T("qisPipe"));
           _sntprintf(qCfg.mutexName_prefix, mycountof(qCfg.mutexName_prefix), _T("qiqPipe"));
           qCfg.uiMaxQNodes = 100;	//  CONST_uiMaxQNodes_outputQ_256;

           //		  
           M_get_pipeName(CONST_ipcProcPipePrefix, _T(""), CONST_ipcProcPipe_tn_dhPtz, pipeName);


           //
           PARAM_initQisPipe  param = { 0 };
           param.pf_onRead = dh_ptz_qisPipe_onRead;
           param.uiMaxToInMs_read = CONST_toInMs_pipe_read;

           //
#ifdef  _DEBUG
           //param.bPrint_write = true;
#endif

           //
           initQisPipe(&qCfg, pipeName, true, _T("dh.ptz"), &param, gBuf_dh.m_var.dhPtz.pQisPipe);

           //

       }
       */



   //
   gBuf_dh.m_var.m_bAutoClose_ifToolLongNoRecvd_qm = true;

   //
#ifdef  _DEBUG
        //
        #if  0
             //
             gBuf_dh.m_var.m_bAutoClose_ifToolLongNoRecvd_qm = false;
        #endif  
#endif
  



   //
   HWND hWnd;
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   //
   nCmdShow = SW_HIDE;

   //
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   //
   gBuf_dh.m_var.hMainWnd = hWnd;
   //
   gBuf_dh.m_var.qm.dwLastTickCnt_recvd = myGetTickCount(mynull);

   //
   iErr = 0;

   //
   } while (false);


   if (iErr) {
       //
       return false;
   }
   //
   return TRUE;
}


int ExitInstance()
{
    //
    qisPipeFree(&gBuf_dh.m_var.qm.pQisPipe);
    //
    qisPipeFree(&gBuf_dh.m_var.dhListIp.pQisPipe);
    //
    qisPipeFree(&gBuf_dh.m_var.dhDeviceControl.pQisPipe);
    //
    //qisPipeFree(&gBuf_dh.m_var.dhPtz.pQisPipe);



    //
    closeTool_ipcProc(&gBuf_dh.m_var.dhListIp.tool);
    //
    closeTool_ipcProc(&gBuf_dh.m_var.dhDeviceControl.tool);
    //
    //closeTool_ipcProc(&gBuf_dh.m_var.dhPtz.tool);


    //
    return  0;
}



//
VOID (__stdcall myTimerProc)(HWND  hWnd, UINT, UINT_PTR, DWORD)
{

    //
    if (gBuf_dh.m_var.m_bAutoClose_ifToolLongNoRecvd_qm) {
        //
        DWORD  dwTickCnt = myGetTickCount(nullptr);
        int iDiffInMs = dwTickCnt - gBuf_dh.m_var.qm.dwLastTickCnt_recvd;
        if (abs(iDiffInMs) > CONST_toInMs_ipcProc) {
            //
            showInfo_open0(0,0,_T("d4k too long to recv, quit now\n"));
            //
            PostMessage(hWnd, WM_CLOSE, 0, 0);
        }
    }


    //
    waitForObject(&gBuf_dh.m_var.dhListIp.tool.hProcess_ipcProc, 0);
    waitForObject(&gBuf_dh.m_var.dhDeviceControl.tool.hProcess_ipcProc, 0);
    //waitForObject(&gBuf_dh.m_var.dhPtz.tool.hProcess_ipcProc, 0);


    //
    if (!gBuf_dh.m_var.dhListIp.tool.hProcess_ipcProc) {

        printLog(gBuf_dh.m_var.cfg.installDir);
        //
        if (0) {
            TCHAR  tBuf[128];
            _sntprintf(tBuf, mycountof(tBuf), _T("appParams: %S,%s,%S"), gBuf_dh.m_var.appParams.nvrIp, gBuf_dh.m_var.appParams.nvrUsr, gBuf_dh.m_var.appParams.nvrPwd);
            showInfo_open0(0, 0, tBuf);
        }

        //
        gBuf_dh.m_var.g_tn++;
        gBuf_dh.m_var.dhListIp.tool.tn = gBuf_dh.m_var.g_tn;

        //
#if 10
        createTool_ipcProc(gBuf_dh.m_var.cfg.installDir, CONST_iNvrType_d4kListIp, gBuf_dh.m_var.appParams.nvrIp, gBuf_dh.m_var.appParams.nvrUsr,gBuf_dh.m_var.appParams.nvrPwd,  gBuf_dh.m_var.dhListIp.tool.tn,  _T(""), _T(""), &gBuf_dh.m_var.dhListIp.tool, gBuf_dh.m_var.appParams.log);
#endif
    }
    if (!gBuf_dh.m_var.dhDeviceControl.tool.hProcess_ipcProc) {
        //
        gBuf_dh.m_var.g_tn++;
        gBuf_dh.m_var.dhDeviceControl.tool.tn = gBuf_dh.m_var.g_tn;

        //

#if 10
        createTool_ipcProc(gBuf_dh.m_var.cfg.installDir, CONST_iNvrType_d4kDeviceControl, gBuf_dh.m_var.appParams.nvrIp, gBuf_dh.m_var.appParams.nvrUsr, gBuf_dh.m_var.appParams.nvrPwd, gBuf_dh.m_var.dhDeviceControl.tool.tn,_T(""), _T(""), &gBuf_dh.m_var.dhDeviceControl.tool, gBuf_dh.m_var.appParams.log);
#endif
    }

/*
    if (!gBuf_dh.m_var.dhPtz.tool.hProcess_ipcProc) {

        //
        gBuf_dh.m_var.g_tn++;
        gBuf_dh.m_var.dhPtz.tool.tn = gBuf_dh.m_var.g_tn;

#if 10
        createTool_ipcProc(gBuf_dh.m_var.cfg.installDir, CONST_iNvrType_dhPtz, gBuf_dh.m_var.appParams.nvrIp, gBuf_dh.m_var.appParams.nvrUsr, gBuf_dh.m_var.appParams.nvrPwd, gBuf_dh.m_var.dhPtz.tool.tn,_T(""), _T(""), &gBuf_dh.m_var.dhPtz.tool);
#endif


    }
    */



    //
#if 0
    showInfo_open0(0, 0, _T("dh.myTimerProc: before qisPipe_writeMsg"));
    //
    OnvifMsg_dbg m = { 0 };
    m.uiType = CONST_qisMsgType_onvif;
    m.iSubtype = CONST_onvifMsg_subtype_dbg;
    static int ii = 0;  ii++;
    m.uiTranNo = ii;
    qisPipe_writeMsg(&m, sizeof(m), gBuf_dh.m_var.tool.pQisPipe);
#endif

    //
    return;
 }




//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case  WM_CREATE:
        SetTimer(hWnd, 1, 1000, myTimerProc);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                //
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

