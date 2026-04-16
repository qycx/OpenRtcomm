// dh.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include    <mmsystem.h>
#include    "qmOpenCommon.h"
#include "hik.h"
#include    "hikProc.h"
#include <ctxQmThread.h>
#include "myTypes.h"
#include    "ipcProc_open.h"

//#include "pipe_client.h"
//#include "pipe_server.h"



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
//Pipe_Client* g_pipeClient = nullptr;
//Pipe_Server* g_pipe_server = nullptr;


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

char* TCHARToChar(TCHAR* pTchar)
{
    char* pChar = nullptr;
    int nLen = wcslen(pTchar) + 1;
    pChar = new char[nLen * 2];
    WideCharToMultiByte(CP_ACP, 0, pTchar, nLen, pChar, 2 * nLen, NULL, NULL);
    return pChar;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   
   //
   int  iErr = -1;

   //
   do {
       //
       init_tickCnt();


       //
       bool  bCli = true;

       //
       bool  bShowInfoInited = false;
       TCHAR* errHintWndCls = (TCHAR*)_T("mmsmsm");//CONST_qnmStatusToolWndClass;
       //if  (  initShowInfo(  0,  _T(  "syncQ_showInfo_qmd"  ),  errHintWndCls,  TRUE,  FALSE,  &mcDaemon.var.pShowInfoStruct  )  )  goto  errLabel;
       if (initShowInfo_func(0, _T("syncQ_showInfo_hik"), errHintWndCls, false, true, (char*)"127.0.0.1", bCli, &gBuf_dh.m_var.pShowInfoStruct)) {
           //goto  errLabel;
           break;
       }
       bShowInfoInited = TRUE;

       //
       set_who_showInfo(_T("hik"));

       //
       TCHAR* cmdLine = GetCommandLine();
       //
       showInfo_open0(0, _T("hik.haha"), cmdLine);
       //
       parseCmdLine_ipcProc(cmdLine, &gBuf_dh.m_var.appParams);


       printLogChar("-----------hik---------------InitInstance-------------");
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
           param.pf_onRead = hik_qisPipe_onRead;
           param.uiMaxToInMs_read = CONST_toInMs_pipe_read;

           //
           if(initQisPipe(&qCfg, pipeName, false, _T("hik.qm"), &param, gBuf_dh.m_var.qm.pQisPipe)) {
               showInfo_open0(0, _T("hik"), _T("initQisPipe  qm failed\n"));
               break;
           }

           //
       }
   ///////////      
   //
       {
           Ipc_tool_info* pIpc = &gBuf_dh.m_var.dhListIp;
           pIpc->pQisPipe = qisPipeNew();
           if (!pIpc->pQisPipe)  break;

           //
           GENERIC_Q_CFG  qCfg = { 0 };
           TCHAR   pipeName[128] = _T("");
           int  tn_rtspCliPipe = 0;// pParams->tn_cliPipe;
           //
           _sntprintf(qCfg.name, mycountof(qCfg.name), _T("qisPipe"));
           _sntprintf(qCfg.mutexName_prefix, mycountof(qCfg.mutexName_prefix), _T("qiqPipe"));
           qCfg.uiMaxQNodes = 100;	//  CONST_uiMaxQNodes_outputQ_256;

           //
           int  tn = CONST_ipcProcPipe_tn_hikListIp;

           //
           pIpc->tool.tn = tn;

           //		  
           //M_get_pipeName(CONST_ipcProcPipePrefix, _T(""), CONST_ipcProcPipe_tn_d4kListIp, pipeName);
           M_get_pipeName(CONST_ipcProcPipePrefix, _T(""), tn, pipeName);


           //
           PARAM_initQisPipe  param = { 0 };
           param.pf_onRead = dh_listIp_qisPipe_onRead;
           param.uiMaxToInMs_read = CONST_toInMs_pipe_read;

           printLogChar("------------------------------");

           printLog(pipeName);
           //
#ifdef  _DEBUG
           //param.bPrint_write = true;
#endif

           //
           int ret = initQisPipe(&qCfg, pipeName, true, _T("hik.listIp"), &param, pIpc->pQisPipe);


           if(ret) {
               showInfo_open0(0, _T("hik"), _T("initQisPipe listIp failed\n"));
               break;
           }
          

       }

       //
       {
           Ipc_tool_info* pIpc = &gBuf_dh.m_var.hk3ddw;
           pIpc->pQisPipe = qisPipeNew();
           if (!pIpc->pQisPipe)  break;

           //
           GENERIC_Q_CFG  qCfg = { 0 };
           TCHAR   pipeName[128] = _T("");
           //int  tn_rtspCliPipe = 0;// pParams->tn_cliPipe;
           //
           _sntprintf(qCfg.name, mycountof(qCfg.name), _T("qisPipe"));
           _sntprintf(qCfg.mutexName_prefix, mycountof(qCfg.mutexName_prefix), _T("qiqPipe"));
           qCfg.uiMaxQNodes = 100;	//  CONST_uiMaxQNodes_outputQ_256;

           //
           int  tn = CONST_ipcProcPipe_tn_hk3ddw;

           //
           pIpc->tool.tn = tn;


           //		  
           //M_get_pipeName(CONST_ipcProcPipePrefix, _T(""), CONST_ipcProcPipe_tn_d4kListIp, pipeName);
           M_get_pipeName(CONST_ipcProcPipePrefix, _T(""), tn, pipeName);


           //
           PARAM_initQisPipe  param = { 0 };
           param.pf_onRead = hk_3ddw_qisPipe_onRead;
           param.uiMaxToInMs_read = CONST_toInMs_pipe_read;

           printLogChar("------------------------------");

           printLog(pipeName);
           //
#ifdef  _DEBUG
           //param.bPrint_write = true;
#endif

           //
           int ret = initQisPipe(&qCfg, pipeName, true, _T("hk3ddw"), &param, pIpc->pQisPipe);

           if (ret) {
               showInfo_open0(0, _T("hik"), _T("initQisPipe hk3ddw failed\n"));
               break;
           }

       }








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
#ifdef  _DEBUG
   if (0) {
       nCmdShow = SW_SHOW;
        }
#endif 


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

   printLogChar("------hik---------exit------------------");


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
    printLogChar("---------------ExitInstance------------------");
    qisPipeFree(&gBuf_dh.m_var.qm.pQisPipe);
    //
    qisPipeFree(&gBuf_dh.m_var.dhListIp.pQisPipe);
    //
    qisPipeFree(&gBuf_dh.m_var.hk3ddw.pQisPipe);
    
    //
    //qisPipeFree(&gBuf_dh.m_var.dhDeviceControl.pQisPipe);
    //
    //qisPipeFree(&gBuf_dh.m_var.dhPtz.pQisPipe);





    //
    closeTool_ipcProc(&gBuf_dh.m_var.dhListIp.tool);

    //
    closeTool_ipcProc(&gBuf_dh.m_var.hk3ddw.tool);


    //
    //closeTool_ipcProc(&gBuf_dh.m_var.dhDeviceControl.tool);
    //
    //closeTool_ipcProc(&gBuf_dh.m_var.dhPtz.tool);

   /* if (g_pipeClient) {

		delete g_pipeClient;
		g_pipeClient = nullptr;
	}*/



    //
    return  0;
}



//
#include <sstream>
VOID (__stdcall myTimerProc)(HWND  hWnd, UINT, UINT_PTR, DWORD)
{
    //
    int  tmpiRet = -1;

    //
#ifdef  _DEBUG

    //
        //


    //
    if (0) {

#if 10
        showInfo_open0(0, 0, _T("hik.myTimerProc: for test: to listIp, qisPipe_writeMsg"));
        //
        OnvifMsg_dbg m = { 0 };
        m.uiType = CONST_qisMsgType_onvif;
        m.iSubtype = CONST_onvifMsg_subtype_dbg;
        static int ii = 0;  ii++;
        m.uiTranNo = ii;
        qisPipe_writeMsg(&m, sizeof(m), gBuf_dh.m_var.dhListIp.pQisPipe);
#endif



        OutputDebugString(_T("myTimerProc: for test, returns here\n"));
        return;
    }
#endif 

    //
    if (gBuf_dh.m_var.m_bAutoClose_ifToolLongNoRecvd_qm) {
        //
        DWORD  dwTickCnt = myGetTickCount(nullptr);
        int iDiffInMs = dwTickCnt - gBuf_dh.m_var.qm.dwLastTickCnt_recvd;

        //
#ifdef  _DEBUG
        TCHAR  tBuf[128];
        if (0) {
            _sntprintf(tBuf, mycountof(tBuf), _T("myTimerProc: %dms"), iDiffInMs);
            showInfo_open0(0, 0, tBuf);
        }
#endif 


        //
        if (abs(iDiffInMs) > CONST_toInMs_ipcProc) {
            //
            showInfo_open0(0,0,_T("too long to recv, quit now\n"));
            printLogChar("too long to recv, quit now");
            //
            PostMessage(hWnd, WM_CLOSE, 0, 0);
        }
    }

    //printLogChar("-----------myTimerProc---------------in-------------");
    //std::stringstream ss;
    //ss << gBuf_dh.m_var.dhListIp.tool.hProcess_ipcProc;    
    //printLogChar(ss.str().c_str());
    //printLogChar("-----------myTimerProc---------------in----end---------");

    //printLogChar("-----------myTimerProc---------------in-------------");
    waitForObject(&gBuf_dh.m_var.dhListIp.tool.hProcess_ipcProc, 0);
    waitForObject(&gBuf_dh.m_var.hk3ddw.tool.hProcess_ipcProc, 0);

    //
    if (!gBuf_dh.m_var.dhListIp.tool.hProcess_ipcProc) {
        //
        if (0) {
            TCHAR  tBuf[128];
            _sntprintf(tBuf, mycountof(tBuf), _T("appParams: %S,%s,%S"), gBuf_dh.m_var.appParams.nvrIp, gBuf_dh.m_var.appParams.nvrUsr, gBuf_dh.m_var.appParams.nvrPwd);
            showInfo_open0(0, 0, tBuf);
        }

        //
        gBuf_dh.m_var.g_tn++;
        gBuf_dh.m_var.dhListIp.tool.tn = gBuf_dh.m_var.g_tn;

        //printLogChar("-----------CONST_iNvrType_hikListIp---------------create-------------");

        //
#if 10
        tmpiRet  =  createTool_ipcProc(gBuf_dh.m_var.cfg.installDir, CONST_iNvrType_hikListIp, gBuf_dh.m_var.appParams.nvrIp, gBuf_dh.m_var.appParams.nvrUsr,gBuf_dh.m_var.appParams.nvrPwd,  gBuf_dh.m_var.dhListIp.tool.tn,  _T(""), _T(""), &gBuf_dh.m_var.dhListIp.tool, gBuf_dh.m_var.appParams.log, gBuf_dh.m_var.appParams.devType);
        if (!tmpiRet) {
            showInfo_open0(0, 0, _T("hikListIp created"));
        }
#endif

        //

        /*
        if (g_pipe_server != nullptr) {
            delete g_pipe_server;
            g_pipe_server = nullptr;
        }

        DWORD processId = GetCurrentProcessId();
        std::stringstream ss;
        ss << "pipe_hik_" << processId;
        printLogChar(ss.str().c_str());
        g_pipe_server = new Pipe_Server(ss.str().c_str(), std::bind(msgProcess, std::placeholders::_1));
        g_pipe_server->Start();


        if (g_pipeClient != nullptr) {
            delete g_pipeClient;
            g_pipeClient = nullptr;
        }


        std::stringstream ssClient;
        ssClient << "pipe_list_" << gBuf_dh.m_var.dhListIp.tool.dwProcessId_ipcProc;
        printLogChar(ssClient.str().c_str());
        g_pipeClient = new Pipe_Client(ssClient.str());
        g_pipeClient->Start();

        */
    }

    
    //
    Ipc_tool_info* pIpc = &gBuf_dh.m_var.hk3ddw;
    if (!pIpc->tool.hProcess_ipcProc) {
        //
        if (0) {
            TCHAR  tBuf[128];
            _sntprintf(tBuf, mycountof(tBuf), _T("appParams: %S,%s,%S"), gBuf_dh.m_var.appParams.nvrIp, gBuf_dh.m_var.appParams.nvrUsr, gBuf_dh.m_var.appParams.nvrPwd);
            showInfo_open0(0, 0, tBuf);
        }

        //
        gBuf_dh.m_var.g_tn++;
        pIpc->tool.tn = gBuf_dh.m_var.g_tn;

        //printLogChar("-----------CONST_iNvrType_hk3ddw---------------create-------------");
        
        //
#if 10
        int  tmpiRet;
        tmpiRet  =  createTool_ipcProc(gBuf_dh.m_var.cfg.installDir, CONST_iNvrType_hk3ddw, gBuf_dh.m_var.appParams.nvrIp, gBuf_dh.m_var.appParams.nvrUsr, gBuf_dh.m_var.appParams.nvrPwd, pIpc->tool.tn, _T(""), _T(""), &pIpc->tool, gBuf_dh.m_var.appParams.log);
        if (!tmpiRet) {
            showInfo_open0(0, 0, _T("hk3ddw created"));

        }

#endif

    }




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

