

#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h> 

#include	"DXUT/Core/DXUT.h"
#include	"DXUT/Core/myDXUTState1.h"
#include	"DXUT/Optional/DXUTcamera.h"
#include	"DXUT/Optional/DXUTgui.h"
//#include	"../DXUT/Optional/SDKmisc.h"
//#include	"../DXUT/Optional/SDKmesh.h"

#include	"DirectXTK/inc/CommonStates.h"
#include	"DirectXTK/inc/Effects.h"
#include	"DirectXTK/inc/GeometricPrimitive.h"
#include	"DirectXTK/inc/Model.h"
#include	"DirectXTK/inc/PrimitiveBatch.h"
#include	"DirectXTK/inc/VertexTypes.h"
#include	"DirectXTK/inc/SpriteBatch.h"
#include	"DirectXTK/inc/SpriteFont.h"
#include	"DirectXTK/Inc/DDSTextureLoader.h"




//
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qySyncCommProc.h"
#include	"qmcVideoCapture_isCli.h"


#include	"isCliD3dCommon.h"
#include	"dlgD3dWall.h"

//
#include	"isCliHelpPublic.h"

//
#include	"cuboidTool.h"

#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
#include	"imgProcessPublic.h"

#include	"dxutGui2.h"

#include	"dynFuncs_d3dCall.h"
#include	"subtitlesCfg.h"
#include	"subtitles.h"

//  2015/01/01
#include	"extOpenCommon.h"

//  2015/03/25
#include	"meshLoaderPublic.h"

//
#include	"funcsForIsCliHelp.h"

//
#include	"d2dProcPublic.h"
#include	"avConsole_open.h"

#include	"myDxutFunc.h"
#include <tmpGuiOpenFunc.h>


//
_Use_decl_annotations_
HRESULT WINAPI qyMcu_DXUTCreateDeviceFromSettings(DXUTDeviceSettings* pDeviceSettings, bool bClipWindowToSingleAdapter);
_Use_decl_annotations_
HRESULT qyMcu_DXUTChangeDevice(DXUTDeviceSettings* pNewDeviceSettings,
	bool bClipWindowToSingleAdapter);
HRESULT qyMcu_DXUTCreate3DEnvironment11();
void WINAPI qyMcu_DXUTRender3DEnvironment();
HRESULT WINAPI qyMcu_DXUTCreateWindow(_In_z_ const WCHAR* strWindowTitle = L"Direct3D Window",
	_In_opt_ HINSTANCE hInstance = nullptr, _In_opt_ HICON hIcon = nullptr, _In_opt_ HMENU hMenu = nullptr,
	_In_ int x = CW_USEDEFAULT, _In_ int y = CW_USEDEFAULT); _Use_decl_annotations_
	LRESULT CALLBACK qyMcu_DXUTStaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//




//  2013/11/27
extern  "C" __declspec(dllexport)  int  createConsoleWall(void* pGBuf_d3d)
{
    int					iErr = -1;
    GBuf_d3d_isCli* pGBuf = (GBuf_d3d_isCli*)pGBuf_d3d;
    if (!pGBuf)  return  -1;
    CCtxQyMc* pQyMc = QY_GET_GBUF();
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    if (!pProcInfo)  return  -1;


    //
#if 0
    if (!pProcInfo->bUse_dx11()) {
        showInfo_open0(0, 0, _T("bUse_dx11 false"));
    }
    else {
        showInfo_open0(0, 0, _T("bUse_dx11 true"));
    }
#endif


    // 
    if (!pProcInfo->bUse_dx11()) {
        return  createConsoleWall_dx12(pGBuf_d3d);
    }


    //
    showInfo_open0(0, 0, _T("qyMcu, createConsoleWall called"));

    //
    int  tickCnt0 = myGetTickCount(null);

    //
    if (IsWindow(pGBuf->hWall_d3d)) {
        MACRO_SetForegroundWindow(pGBuf->hWall_d3d);
        return  -1;
    }

    //
    if (pGBuf->bStartInitialization_d3d) {
        closeConsoleWall(pGBuf);
    }
    if (pGBuf->bStartInitialization_d3d)  goto  errLabel;

    //
    pGBuf->bStartInitialization_d3d = TRUE;

    //
    //  2013/10/05
    //memset(  &pGBuf->wallInfo,  0,  sizeof(  pGBuf->wallInfo  )  );

    //  2013/10/15
    pGBuf->i3dType = get_DEFAULT_i3dType();

    //   
    D3D_context* pCtx = g_pD3dContext;
    pCtx->pGBuf_d3d_isCli = pGBuf;

    //  2016/05/22   
    if (!pGBuf->pD3dWndMgr) {
        showInfo_open0(0, 0, _T("createWall_d3d failed, pD3dWndMgr is null"));
        goto  errLabel;
    }

    //  2014/12/03
    pCtx->status.dwThreadId_createWall = GetCurrentThreadId();

    //
    if (FAILED(DXUTCreateState()))  goto  errLabel;
    if (FAILED(DXUTCreateD3D11Enumeration()))  goto  errLabel;

    //	
    RECT			rect;

    // Set general DXUT callbacks
    DXUTSetCallbackFrameMove(OnFrameMove);
    LPDXUTCALLBACKKEYBOARD  pOnKeyboard = OnKeyboard;
    DXUTSetCallbackKeyboard(pOnKeyboard);
    LPDXUTCALLBACKMSGPROC  pMsgProc = MsgProc_consoleWall;
    DXUTSetCallbackMsgProc(pMsgProc);
    LPDXUTCALLBACKMODIFYDEVICESETTINGS  pModifyDeviceSettings = ModifyDeviceSettings;
    DXUTSetCallbackDeviceChanging(pModifyDeviceSettings);
    LPDXUTCALLBACKDEVICEREMOVED  pOnDeviceRemoved = OnDeviceRemoved;
    DXUTSetCallbackDeviceRemoved(pOnDeviceRemoved);

    // Set the D3D11 DXUT callbacks. Remove these sets if the app doesn't need to support D3D11
    LPDXUTCALLBACKISD3D11DEVICEACCEPTABLE  pIsD3D11DeviceAcceptable = IsD3D11DeviceAcceptable;
    DXUTSetCallbackD3D11DeviceAcceptable(pIsD3D11DeviceAcceptable);
    DXUTSetCallbackD3D11DeviceCreated(OnD3D11CreateDevice);
    DXUTSetCallbackD3D11SwapChainResized(OnD3D11ResizedSwapChain);
    DXUTSetCallbackD3D11FrameRender(OnD3D11FrameRender);
    DXUTSetCallbackD3D11SwapChainReleasing(OnD3D11ReleasingSwapChain);
    DXUTSetCallbackD3D11DeviceDestroyed(OnD3D11DestroyDevice);

    // Perform any application-level initialization here
    InitApp();

    //  2014/11/24
    TCHAR* cmdLine = _T("-forcevsync:1");
    cmdLine = _T("-forcevsync:0");
    //
    DXUTInit(true, true, cmdLine); // Parse the command line, show msgboxes on error, no extra command line params
    DXUTSetCursorSettings(true, true); // Show the cursor and clip it when in full screen

    //
    qyMcu_DXUTCreateWindow(L"Qycx Video Conference");


    // Only require 10-level hardware or later
    D3D_FEATURE_LEVEL reqFL = D3D_FEATURE_LEVEL_10_0;
    //
    unsigned  char  ucbWin7 = bLeWin7();
    //
    showInfo_open0(0, 0, ucbWin7 ? _T("leWin7 true") : _T("leWin7 false"));
    //  2016/05/04
    if (!ucbWin7) {
        //reqFL = D3D_FEATURE_LEVEL_11_0;
        reqFL = D3D_FEATURE_LEVEL_11_1;
    }
    //
    int  nSuggestedWidth = 640;
    int  nSuggestedHeight = 480;
    BOOL  bWindowed = TRUE;
    bool bClipWindowToSingleAdapter = TRUE;

    //
    //DXUTCreateDevice( reqFL, true, 640, 480 );

    DXUTDeviceSettings deviceSettings;
    DXUTApplyDefaultDeviceSettings(&deviceSettings);
    deviceSettings.MinimumFeatureLevel = reqFL;
    deviceSettings.d3d11.sd.BufferDesc.Width = nSuggestedWidth;
    deviceSettings.d3d11.sd.BufferDesc.Height = nSuggestedHeight;
    deviceSettings.d3d11.sd.Windowed = bWindowed;

    //
    if (pProcInfo->cfg.ucb__USE_d2dToRenderTxt__) {
        //
        deviceSettings.d3d11.CreateFlags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;
    }


    HRESULT  hr;
    hr = qyMcu_DXUTCreateDeviceFromSettings(&deviceSettings, bClipWindowToSingleAdapter);
    if (FAILED(hr)) {
        //
        showInfo_open0(0, 0, L"CreateDevice failed, Direct3D 11 is not supported on this OS.");
        //MessageBox( 0, L"CreateDevice failed, Direct3D 11 is not supported on this OS.", L"Error", MB_ICONEXCLAMATION );
        goto  errLabel;
    }

    //
    pGBuf->bInited_d3d = TRUE;

    //
#ifdef  __DEBUG__
    //  DXUTMainLoop(); // Enter into the DXUT render loop
    //
    D3D_FEATURE_LEVEL  tmp_fl;
    ID3D11Device* pDevice = DXUTGetD3D11Device();
    tmp_fl = pDevice->GetFeatureLevel();

#endif

    //
    pGBuf->hWall_d3d = DXUTGetHWNDFocus();

    //  2017/10/26
    int  iWndContentType = CONST_qyWndContentType_consoleWall;

    //  2016/05/27
    D3D_wnd* pD3dWnd = getD3dWndByIndex(0);
    if (!pD3dWnd)  goto  errLabel;
    pD3dWnd->hWnd = pGBuf->hWall_d3d;
    //  2017/10/26
    pD3dWnd->iWndContentType = iWndContentType;


    //
    int  iZoneObjsType = 0;
    //
    D3D_zoneObjs* pVar = (D3D_zoneObjs*)getZoneObjsInfo_d3dWall(pGBuf->hWall_d3d, iWndContentType, iZoneObjsType);
    if (!pVar)  goto  errLabel;
    memset(pVar, 0, sizeof(pVar[0]));

    //
    pGBuf->lStyle_org = GetWindowLong(pGBuf->hWall_d3d, GWL_STYLE);


    //  吽軞岆敦諳宒
    pD3dWnd->bWindowed = TRUE;

    //  2014/10/30
#define DEFAULT_iW_d3dWnd		848				//  800
#define DEFAULT_iH_d3dWnd		480				//  600

   //
    int  wnd_w = DEFAULT_iW_d3dWnd;
    int  wnd_h = DEFAULT_iH_d3dWnd;
#ifdef  __DEBUG__
    //wnd_w  =  1600;
#endif
    SetClientSize(pGBuf->hWall_d3d, wnd_w, wnd_h);
    centerWnd(pGBuf->hWall_d3d);

    //
    GetClientRect(pGBuf->hWall_d3d, &rect);
    pD3dWnd->wnd_w = rect.right - rect.left;
    pD3dWnd->wnd_h = rect.bottom - rect.top;

    //
    //  if  (  D3D_context_init(  pCtx  )  )  goto  errLabel;


    //
    pCtx->lastTimeInMs_myRender = 0;
    //
    pCtx->ts_gZone_talkers.dwModifiedTickCnt = 0;


    //
    getStr_welcomeToUse(pProcInfo, pGBuf->defaultWelcomeMsg, mycountof(pGBuf->defaultWelcomeMsg));
    //
    pGBuf->tWhere[0] = 0;

    //
    if (setCurQisWallCfg(0, g_pQyMc->pQisWallsCfg)) {
        showInfo_open0(0, 0, _T("createWall_d3d failed, setCurQisWallCfg failed"));
        goto  errLabel;
    }

    //
#ifdef  __DEBUG__
#if  10
    if (!bApp_ts(pQyMc)) {
        TCHAR* wallFile = _T("c:\\tttbbb\\test.qvw");
        //
        wallFile = _T("c:\\tttbbb\\2.qvw");
        //
        //wallFile  =  _T(  "c:\\tttbbb\\mm.qvw"  );
        //
        int  iIndex = 0;
        if (addQisWallCfg(g_pQyMc->pQisWallsCfg, CONST_wallType_confWall, wallFile, &iIndex)) {
            goto  errLabel;
        }
        setCurQisWallCfg(iIndex, g_pQyMc->pQisWallsCfg);
    }
#endif
#endif


    //
    tryToChkD3dWall(pCtx);

    //
    int  iGrpType = CONST_wmGrpType_gZone;
    //
    WALLMem_u* pWallMem = (WALLMem_u*)getCurWmVar(pGBuf, iGrpType);
    if (pWallMem) {
        TCHAR  tNote[256] = _T("");
        _sntprintf(tNote, mycountof(tNote), _T("%s"), getResStr(0, &pQyMc->cusRes, CONST_resId_wizard_welcome));  //  _T(  "斕疑ㄛ辣茩妏蚚\"栨\"弝頗祜﹝www.qycx.comㄛ86-10-6297 8471."  )  );
        safeTcsnCpy(tNote, pWallMem->common.head.dataHead.note.tBuf, mycountof(pWallMem->common.head.dataHead.note.tBuf));
    }




    //
    if (pGBuf->timerId) {
        showInfo_open0(0, 0, _T("createWall_d3d failed, timerId is not 0"));
        goto  errLabel;
    }
    UINT_PTR  timerId = 0;
    timerId = SetTimer(pGBuf->hWall_d3d, 1, 1000, NULL);
    if (!timerId)  goto  errLabel;
    pGBuf->timerId = timerId;

    //
#if  1
    int  tickCnt1 = myGetTickCount(null);
    int  iDiffInMs = tickCnt1 - tickCnt0;
    TCHAR  tBuf[128];
    _sntprintf(tBuf, mycountof(tBuf), _T("createConsoleWall ok, %dms"), iDiffInMs);
    showInfo_open0(0, 0, tBuf);
#endif

    //
    iErr = 0;

errLabel:

    if (iErr) {
#if  0
        if (!bCreated) {
            if (pDlg)  delete  pDlg;
        }
#endif
        //
        closeConsoleWall(pGBuf_d3d);

        //
        showInfo_open0(0, _T("createWall_d3d"), _T("failed"));
}


    return  iErr;

}


extern  "C" __declspec(dllexport)  int  closeConsoleWall(void* pGBuf_d3d)
{
    int					iErr = -1;
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);

    GBuf_d3d_isCli* pGBuf = (GBuf_d3d_isCli*)pGBuf_d3d;
    if (!pGBuf)  return  -1;


    //
    if (!pProcInfo->bUse_dx11()) {
        return closeConsoleWall_dx12(pGBuf_d3d);
    }

    //
    pGBuf->bInited_d3d = FALSE;

    //
    if (pGBuf->hWall_d3d) {
        if (IsWindow(pGBuf->hWall_d3d)) {
            //
            SendMessage(pGBuf->hWall_d3d, WM_CLOSE, 0, 0);
            //
            if (IsWindow(pGBuf->hWall_d3d)) {
                traceLog(_T("closeTestWnd_d3d: failed, hWnd_test still exists"));
                goto  errLabel;
            }
        }
        pGBuf->hWall_d3d = NULL;
    }

    D3D_context* pCtx = g_pD3dContext;


    //
    DXUTDestroyState();
    DXUTDestroyD3D11Enumeration();

    //
    pGBuf->bStartInitialization_d3d = FALSE;

    //
    iErr = 0;

errLabel:
    return  iErr;

}


// 
void  myRender11()
 {
 QY_MC* pQyMc = QY_GET_GBUF();
 GBuf_d3d_isCli* pGBuf = (GBuf_d3d_isCli*)pQyMc->pGBuf_d3d;
 if (!pGBuf)  return;

 if (!pGBuf->bInited_d3d)  return;

 if (!DXUTGetHWNDFocus())  return;

 qyMcu_DXUTRender3DEnvironment();

 //  2016/05/23
 renderD3dWnds();
 }



 //


//
 _Use_decl_annotations_
     HRESULT WINAPI qyMcu_DXUTCreateDeviceFromSettings(DXUTDeviceSettings* pDeviceSettings, bool bClipWindowToSingleAdapter)
 {
     if (!pDeviceSettings)
         return E_INVALIDARG;

     HRESULT hr;

     GetDXUTState_SetDeviceCreateCalled(true);

     // If DXUTCreateWindow() or DXUTSetWindow() has not already been called, 
     // then call DXUTCreateWindow() with the default parameters.         
     if (!GetDXUTState_GetWindowCreated())
     {
         // If DXUTCreateWindow() or DXUTSetWindow() was already called and failed, then fail.
         // DXUTCreateWindow() or DXUTSetWindow() must first succeed for this function to succeed
         if (GetDXUTState_GetWindowCreateCalled())
             return E_FAIL;

         // If DXUTCreateWindow() or DXUTSetWindow() hasn't been called, then 
         // automatically call DXUTCreateWindow() with default params
         hr = DXUTCreateWindow();
         if (FAILED(hr))
             return hr;
     }

     DXUTUpdateDeviceSettingsWithOverrides(pDeviceSettings);

     GetDXUTState_SetWindowBackBufferWidthAtModeChange(pDeviceSettings->d3d11.sd.BufferDesc.Width);
     GetDXUTState_SetWindowBackBufferHeightAtModeChange(pDeviceSettings->d3d11.sd.BufferDesc.Height);
     GetDXUTState_SetFullScreenBackBufferWidthAtModeChange(pDeviceSettings->d3d11.sd.BufferDesc.Width);
     GetDXUTState_SetFullScreenBackBufferHeightAtModeChange(pDeviceSettings->d3d11.sd.BufferDesc.Height);

     // Change to a Direct3D device created from the new device settings.  
     // If there is an existing device, then either reset or recreate the scene
     hr = qyMcu_DXUTChangeDevice(pDeviceSettings, bClipWindowToSingleAdapter);
     if (FAILED(hr))
         return hr;

     return S_OK;
 }



 //
 _Use_decl_annotations_
     HRESULT qyMcu_DXUTChangeDevice(DXUTDeviceSettings* pNewDeviceSettings,
         bool bClipWindowToSingleAdapter)
 {
     if (GetDXUTState_GetReleasingSwapChain())
         return S_FALSE;

     HRESULT hr = S_OK;
     DXUTDeviceSettings* pOldDeviceSettings = GetDXUTState_GetCurrentDeviceSettings();

     if (!pNewDeviceSettings)
         return S_FALSE;

     hr = DXUTDelayLoadDXGI();

     if (FAILED(hr))
         return hr;

     // Make a copy of the pNewDeviceSettings on the heap
     DXUTDeviceSettings* pNewDeviceSettingsOnHeap = new (std::nothrow) DXUTDeviceSettings;
     if (!pNewDeviceSettingsOnHeap)
         return E_OUTOFMEMORY;
     memcpy(pNewDeviceSettingsOnHeap, pNewDeviceSettings, sizeof(DXUTDeviceSettings));
     pNewDeviceSettings = pNewDeviceSettingsOnHeap;

     GetDXUTState_SetCurrentDeviceSettings(pNewDeviceSettingsOnHeap);
     hr = DXUTSnapDeviceSettingsToEnumDevice(pNewDeviceSettingsOnHeap, false);

     if (FAILED(hr)) // the call will fail if no valid devices were found
     {
         DXUTDisplayErrorMessage(hr);
         return DXUT_ERR(L"DXUTFindValidDeviceSettings", hr);
     }

     // If the ModifyDeviceSettings callback is non-NULL, then call it to let the app 
     // change the settings or reject the device change by returning false.
     LPDXUTCALLBACKMODIFYDEVICESETTINGS pCallbackModifyDeviceSettings = GetDXUTState_GetModifyDeviceSettingsFunc();
     if (pCallbackModifyDeviceSettings)
     {
         bool bContinue = pCallbackModifyDeviceSettings(pNewDeviceSettings,
             GetDXUTState_GetModifyDeviceSettingsFuncUserContext());
         if (!bContinue)
         {
             // The app rejected the device change by returning false, so just use the current device if there is one.
             if (!pOldDeviceSettings)
                 DXUTDisplayErrorMessage(DXUTERR_NOCOMPATIBLEDEVICES);
             SAFE_DELETE(pNewDeviceSettings);
             return E_ABORT;
         }
         if (!GetDXUTState_GetDXGIFactory()) // if DXUTShutdown() was called in the modify callback, just return
         {
             SAFE_DELETE(pNewDeviceSettings);
             return S_FALSE;
         }
         DXUTSnapDeviceSettingsToEnumDevice(pNewDeviceSettingsOnHeap, false); // modify the app specified settings to the closed enumerated settigns

         if (FAILED(hr)) // the call will fail if no valid devices were found
         {
             DXUTDisplayErrorMessage(hr);
             return DXUT_ERR(L"DXUTFindValidDeviceSettings", hr);
         }

     }

     //  2013/12/15. 如果不用这个格式，屏幕共享的图像会变淡失真
     pNewDeviceSettingsOnHeap->d3d11.sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
     //
     GetDXUTState_SetCurrentDeviceSettings(pNewDeviceSettingsOnHeap);

     DXUTPause(true, true);

     // Take note if the backbuffer width & height are 0 now as they will change after pd3dDevice->Reset()
     bool bKeepCurrentWindowSize = false;
     if (DXUTGetBackBufferWidthFromDS(pNewDeviceSettings) == 0 &&
         DXUTGetBackBufferHeightFromDS(pNewDeviceSettings) == 0)
         bKeepCurrentWindowSize = true;

     //////////////////////////
     // Before reset
     /////////////////////////

     if (DXUTGetIsWindowedFromDS(pNewDeviceSettings))
     {
         // Going to windowed mode
         if (pOldDeviceSettings && !DXUTGetIsWindowedFromDS(pOldDeviceSettings))
         {
             // Going from fullscreen -> windowed
             GetDXUTState_SetFullScreenBackBufferWidthAtModeChange(DXUTGetBackBufferWidthFromDS(
                 pOldDeviceSettings));
             GetDXUTState_SetFullScreenBackBufferHeightAtModeChange(DXUTGetBackBufferHeightFromDS(
                 pOldDeviceSettings));
         }
     }
     else
     {
         // Going to fullscreen mode
         if (!pOldDeviceSettings || (pOldDeviceSettings && DXUTGetIsWindowedFromDS(pOldDeviceSettings)))
         {
             // Transistioning to full screen mode from a standard window so 
             if (pOldDeviceSettings)
             {
                 GetDXUTState_SetWindowBackBufferWidthAtModeChange(DXUTGetBackBufferWidthFromDS(
                     pOldDeviceSettings));
                 GetDXUTState_SetWindowBackBufferHeightAtModeChange(DXUTGetBackBufferHeightFromDS(
                     pOldDeviceSettings));
             }
         }
     }

     if (pOldDeviceSettings)
         DXUTCleanup3DEnvironment(false);

     // Create the D3D device and call the app's device callbacks
     hr = qyMcu_DXUTCreate3DEnvironment11();
     if (FAILED(hr))
     {
         SAFE_DELETE(pOldDeviceSettings);
         DXUTCleanup3DEnvironment(true);
         DXUTDisplayErrorMessage(hr);
         DXUTPause(false, false);
         GetDXUTState_SetIgnoreSizeChange(false);
         return hr;
     }

     // Enable/disable StickKeys shortcut, ToggleKeys shortcut, FilterKeys shortcut, and Windows key 
     // to prevent accidental task switching
     DXUTAllowShortcutKeys((DXUTGetIsWindowedFromDS(pNewDeviceSettings)) ?
         GetDXUTState_GetAllowShortcutKeysWhenWindowed() :
         GetDXUTState_GetAllowShortcutKeysWhenFullscreen());

     HMONITOR hAdapterMonitor = DXUTGetMonitorFromAdapter(pNewDeviceSettings);
     GetDXUTState_SetAdapterMonitor(hAdapterMonitor);

     // Update the device stats text
     DXUTUpdateStaticFrameStats();

     if (pOldDeviceSettings && !DXUTGetIsWindowedFromDS(pOldDeviceSettings) &&
         DXUTGetIsWindowedFromDS(pNewDeviceSettings))
     {
         // Going from fullscreen -> windowed

         // Restore the show state, and positions/size of the window to what it was
         // It is important to adjust the window size 
         // after resetting the device rather than beforehand to ensure 
         // that the monitor resolution is correct and does not limit the size of the new window.
         auto pwp = GetDXUTState_GetWindowedPlacement();
         SetWindowPlacement(DXUTGetHWNDDeviceWindowed(), pwp);

         // Also restore the z-order of window to previous state
         HWND hWndInsertAfter = GetDXUTState_GetTopmostWhileWindowed() ? HWND_TOPMOST : HWND_NOTOPMOST;
         SetWindowPos(DXUTGetHWNDDeviceWindowed(), hWndInsertAfter, 0, 0, 0, 0,
             SWP_NOMOVE | SWP_NOREDRAW | SWP_NOSIZE);
     }

     // Check to see if the window needs to be resized.  
     // Handle cases where the window is minimized and maxmimized as well.

     bool bNeedToResize = false;
     if (DXUTGetIsWindowedFromDS(pNewDeviceSettings) && // only resize if in windowed mode
         !bKeepCurrentWindowSize)                      // only resize if pp.BackbufferWidth/Height were not 0
     {
         UINT nClientWidth;
         UINT nClientHeight;
         if (IsIconic(DXUTGetHWNDDeviceWindowed()))
         {
             // Window is currently minimized. To tell if it needs to resize, 
             // get the client rect of window when its restored the 
             // hard way using GetWindowPlacement()
             WINDOWPLACEMENT wp;
             ZeroMemory(&wp, sizeof(WINDOWPLACEMENT));
             wp.length = sizeof(WINDOWPLACEMENT);
             GetWindowPlacement(DXUTGetHWNDDeviceWindowed(), &wp);

             if ((wp.flags & WPF_RESTORETOMAXIMIZED) != 0 && wp.showCmd == SW_SHOWMINIMIZED)
             {
                 // WPF_RESTORETOMAXIMIZED means that when the window is restored it will
                 // be maximized.  So maximize the window temporarily to get the client rect 
                 // when the window is maximized.  GetSystemMetrics( SM_CXMAXIMIZED ) will give this 
                 // information if the window is on the primary but this will work on multimon.
                 ShowWindow(DXUTGetHWNDDeviceWindowed(), SW_RESTORE);
                 RECT rcClient;
                 GetClientRect(DXUTGetHWNDDeviceWindowed(), &rcClient);
                 nClientWidth = (UINT)(rcClient.right - rcClient.left);
                 nClientHeight = (UINT)(rcClient.bottom - rcClient.top);
                 ShowWindow(DXUTGetHWNDDeviceWindowed(), SW_MINIMIZE);
             }
             else
             {
                 // Use wp.rcNormalPosition to get the client rect, but wp.rcNormalPosition 
                 // includes the window frame so subtract it
                 RECT rcFrame = { 0 };
                 AdjustWindowRect(&rcFrame, GetDXUTState_GetWindowedStyleAtModeChange(), GetDXUTState_GetMenu() != 0);
                 LONG nFrameWidth = rcFrame.right - rcFrame.left;
                 LONG nFrameHeight = rcFrame.bottom - rcFrame.top;
                 nClientWidth = (UINT)(wp.rcNormalPosition.right - wp.rcNormalPosition.left - nFrameWidth);
                 nClientHeight = (UINT)(wp.rcNormalPosition.bottom - wp.rcNormalPosition.top - nFrameHeight);
             }
         }
         else
         {
             // Window is restored or maximized so just get its client rect
             RECT rcClient;
             GetClientRect(DXUTGetHWNDDeviceWindowed(), &rcClient);
             nClientWidth = (UINT)(rcClient.right - rcClient.left);
             nClientHeight = (UINT)(rcClient.bottom - rcClient.top);
         }

         // Now that we know the client rect, compare it against the back buffer size
         // to see if the client rect is already the right size
         if (nClientWidth != DXUTGetBackBufferWidthFromDS(pNewDeviceSettings) ||
             nClientHeight != DXUTGetBackBufferHeightFromDS(pNewDeviceSettings))
         {
             bNeedToResize = true;
         }

         if (bClipWindowToSingleAdapter && !IsIconic(DXUTGetHWNDDeviceWindowed()))
         {
             // Get the rect of the monitor attached to the adapter
             MONITORINFO miAdapter;
             miAdapter.cbSize = sizeof(MONITORINFO);
             hAdapterMonitor = DXUTGetMonitorFromAdapter(pNewDeviceSettings);
             DXUTGetMonitorInfo(hAdapterMonitor, &miAdapter);
             HMONITOR hWindowMonitor = DXUTMonitorFromWindow(DXUTGetHWND(), MONITOR_DEFAULTTOPRIMARY);

             // Get the rect of the window
             RECT rcWindow;
             GetWindowRect(DXUTGetHWNDDeviceWindowed(), &rcWindow);

             // Check if the window rect is fully inside the adapter's vitural screen rect
             if ((rcWindow.left < miAdapter.rcWork.left ||
                 rcWindow.right > miAdapter.rcWork.right ||
                 rcWindow.top < miAdapter.rcWork.top ||
                 rcWindow.bottom > miAdapter.rcWork.bottom))
             {
                 if (hWindowMonitor == hAdapterMonitor && IsZoomed(DXUTGetHWNDDeviceWindowed()))
                 {
                     // If the window is maximized and on the same monitor as the adapter, then 
                     // no need to clip to single adapter as the window is already clipped 
                     // even though the rcWindow rect is outside of the miAdapter.rcWork
                 }
                 else
                 {
                     bNeedToResize = true;
                 }
             }
         }
     }

     // Only resize window if needed 

     if (bNeedToResize)
     {
         // Need to resize, so if window is maximized or minimized then restore the window
         if (IsIconic(DXUTGetHWNDDeviceWindowed()))
             ShowWindow(DXUTGetHWNDDeviceWindowed(), SW_RESTORE);
         if (IsZoomed(DXUTGetHWNDDeviceWindowed())) // doing the IsIconic() check first also handles the WPF_RESTORETOMAXIMIZED case
             ShowWindow(DXUTGetHWNDDeviceWindowed(), SW_RESTORE);

         if (bClipWindowToSingleAdapter)
         {
             // Get the rect of the monitor attached to the adapter
             MONITORINFO miAdapter;
             miAdapter.cbSize = sizeof(MONITORINFO);
             hAdapterMonitor = DXUTGetMonitorFromAdapter(pNewDeviceSettings);
             DXUTGetMonitorInfo(hAdapterMonitor, &miAdapter);

             // Get the rect of the monitor attached to the window
             MONITORINFO miWindow;
             miWindow.cbSize = sizeof(MONITORINFO);
             DXUTGetMonitorInfo(DXUTMonitorFromWindow(DXUTGetHWND(), MONITOR_DEFAULTTOPRIMARY), &miWindow);

             // Do something reasonable if the BackBuffer size is greater than the monitor size
             int nAdapterMonitorWidth = miAdapter.rcWork.right - miAdapter.rcWork.left;
             int nAdapterMonitorHeight = miAdapter.rcWork.bottom - miAdapter.rcWork.top;

             int nClientWidth = DXUTGetBackBufferWidthFromDS(pNewDeviceSettings);
             int nClientHeight = DXUTGetBackBufferHeightFromDS(pNewDeviceSettings);

             // Get the rect of the window
             RECT rcWindow;
             GetWindowRect(DXUTGetHWNDDeviceWindowed(), &rcWindow);

             // Make a window rect with a client rect that is the same size as the backbuffer
             RECT rcResizedWindow;
             rcResizedWindow.left = 0;
             rcResizedWindow.right = nClientWidth;
             rcResizedWindow.top = 0;
             rcResizedWindow.bottom = nClientHeight;
             AdjustWindowRect(&rcResizedWindow, GetWindowLong(DXUTGetHWNDDeviceWindowed(), GWL_STYLE),
                 GetDXUTState_GetMenu() != 0);

             int nWindowWidth = rcResizedWindow.right - rcResizedWindow.left;
             int nWindowHeight = rcResizedWindow.bottom - rcResizedWindow.top;

             if (nWindowWidth > nAdapterMonitorWidth)
                 nWindowWidth = nAdapterMonitorWidth;
             if (nWindowHeight > nAdapterMonitorHeight)
                 nWindowHeight = nAdapterMonitorHeight;

             if (rcResizedWindow.left < miAdapter.rcWork.left ||
                 rcResizedWindow.top < miAdapter.rcWork.top ||
                 rcResizedWindow.right > miAdapter.rcWork.right ||
                 rcResizedWindow.bottom > miAdapter.rcWork.bottom)
             {
                 int nWindowOffsetX = (nAdapterMonitorWidth - nWindowWidth) / 2;
                 int nWindowOffsetY = (nAdapterMonitorHeight - nWindowHeight) / 2;

                 rcResizedWindow.left = miAdapter.rcWork.left + nWindowOffsetX;
                 rcResizedWindow.top = miAdapter.rcWork.top + nWindowOffsetY;
                 rcResizedWindow.right = miAdapter.rcWork.left + nWindowOffsetX + nWindowWidth;
                 rcResizedWindow.bottom = miAdapter.rcWork.top + nWindowOffsetY + nWindowHeight;
             }

             // Resize the window.  It is important to adjust the window size 
             // after resetting the device rather than beforehand to ensure 
             // that the monitor resolution is correct and does not limit the size of the new window.
             SetWindowPos(DXUTGetHWNDDeviceWindowed(), 0, rcResizedWindow.left, rcResizedWindow.top, nWindowWidth,
                 nWindowHeight, SWP_NOZORDER);
         }
         else
         {
             // Make a window rect with a client rect that is the same size as the backbuffer
             RECT rcWindow = { 0 };
             rcWindow.right = (long)(DXUTGetBackBufferWidthFromDS(pNewDeviceSettings));
             rcWindow.bottom = (long)(DXUTGetBackBufferHeightFromDS(pNewDeviceSettings));
             AdjustWindowRect(&rcWindow, GetWindowLong(DXUTGetHWNDDeviceWindowed(), GWL_STYLE), GetDXUTState_GetMenu() != 0);

             // Resize the window.  It is important to adjust the window size 
             // after resetting the device rather than beforehand to ensure 
             // that the monitor resolution is correct and does not limit the size of the new window.
             int cx = (int)(rcWindow.right - rcWindow.left);
             int cy = (int)(rcWindow.bottom - rcWindow.top);
             SetWindowPos(DXUTGetHWNDDeviceWindowed(), 0, 0, 0, cx, cy, SWP_NOZORDER | SWP_NOMOVE);
         }

         // Its possible that the new window size is not what we asked for.  
         // No window can be sized larger than the desktop, so see if the Windows OS resized the 
         // window to something smaller to fit on the desktop.  Also if WM_GETMINMAXINFO
         // will put a limit on the smallest/largest window size.
         RECT rcClient;
         GetClientRect(DXUTGetHWNDDeviceWindowed(), &rcClient);
         UINT nClientWidth = (UINT)(rcClient.right - rcClient.left);
         UINT nClientHeight = (UINT)(rcClient.bottom - rcClient.top);
         if (nClientWidth != DXUTGetBackBufferWidthFromDS(pNewDeviceSettings) ||
             nClientHeight != DXUTGetBackBufferHeightFromDS(pNewDeviceSettings))
         {
             // If its different, then resize the backbuffer again.  This time create a backbuffer that matches the 
             // client rect of the current window w/o resizing the window.
             auto deviceSettings = DXUTGetDeviceSettings();
             deviceSettings.d3d11.sd.BufferDesc.Width = 0;
             deviceSettings.d3d11.sd.BufferDesc.Height = 0;

             hr = qyMcu_DXUTChangeDevice(&deviceSettings, bClipWindowToSingleAdapter);
             if (FAILED(hr))
             {
                 SAFE_DELETE(pOldDeviceSettings);
                 DXUTCleanup3DEnvironment(true);
                 DXUTPause(false, false);
                 GetDXUTState_SetIgnoreSizeChange(false);
                 return hr;
             }
         }
     }

     //if (DXUTGetIsWindowedFromDS( pNewDeviceSettings )) {
     //    RECT rcFrame = {0};
     //    AdjustWindowRect( &rcFrame, GetDXUTState().GetWindowedStyleAtModeChange(), GetDXUTState().GetMenu() );
    // }

     // Make the window visible
     if (!IsWindowVisible(DXUTGetHWND()))
         ShowWindow(DXUTGetHWND(), SW_SHOW);

     // Ensure that the display doesn't power down when fullscreen but does when windowed
     if (!DXUTIsWindowed())
         SetThreadExecutionState(ES_DISPLAY_REQUIRED | ES_CONTINUOUS);
     else
         SetThreadExecutionState(ES_CONTINUOUS);

     SAFE_DELETE(pOldDeviceSettings);
     GetDXUTState_SetIgnoreSizeChange(false);
     DXUTPause(false, false);
     GetDXUTState_SetDeviceCreated(true);

     return S_OK;
 }

#include    "qmcDirectX_open.h"
#include    "cguid.h"
#include    "atlcomcli.h"

 CComPtr<IDXGIFactory2>                  m_pDXGIFactory;

 //--------------------------------------------------------------------------------------
 // Creates the 3D environment
 //--------------------------------------------------------------------------------------
 HRESULT qyMcu_DXUTCreate3DEnvironment11()
 {
     HRESULT hr = S_OK;
     //
     CCtxQyMc* pQyMc = g_pQyMc;

     //
     ID3D11Device* pd3d11Device = nullptr;
     ID3D11DeviceContext* pd3dImmediateContext = nullptr;
     D3D_FEATURE_LEVEL FeatureLevel = D3D_FEATURE_LEVEL_11_1;

     IDXGISwapChain* pSwapChain = nullptr;
     auto pNewDeviceSettings = GetDXUTState_GetCurrentDeviceSettings();
     assert(pNewDeviceSettings);
     _Analysis_assume_(pNewDeviceSettings);

     auto pDXGIFactory = DXUTGetDXGIFactory();
     assert(pDXGIFactory);
     _Analysis_assume_(pDXGIFactory);
     hr = pDXGIFactory->MakeWindowAssociation(DXUTGetHWND(), 0);


     //////////////////////////////
     HRESULT hres;
     QIS_guiOpen* g_pGuiOpen = &pQyMc->guiOpen;
     if (m_pDXGIFactory == null) {
         if (g_pGuiOpen->pf_CreateDXGIFactory1) {
             PF_CreateDXGIFactory1  pf = (PF_CreateDXGIFactory1)g_pGuiOpen->pf_CreateDXGIFactory1;
             hres = pf(__uuidof(IDXGIFactory2), (void**)(&m_pDXGIFactory));
         }
         else {
             //hres = CreateDXGIFactory(__uuidof(IDXGIFactory2), (void**)(&m_pDXGIFactory) );
             showInfo_open0(0, null, _T("d3d11Device.init failed, pf_CreateDXGIFactory1 is null"));
             return  E_FAIL;
         }
     }




     // Try to create the device with the chosen settings
     IDXGIAdapter1* pAdapter = nullptr;

     hr = S_OK;
     D3D_DRIVER_TYPE ddt = pNewDeviceSettings->d3d11.DriverType;
     //
#if 10  //  2022/06/18. 因为server2016不支持新的创建方式，故暂时回复原来的做法。
        //  回头需要在这里判断一下是否是server2016
     //
     if (pNewDeviceSettings->d3d11.DriverType == D3D_DRIVER_TYPE_HARDWARE)
     {
         hr = pDXGIFactory->EnumAdapters1(pNewDeviceSettings->d3d11.AdapterOrdinal, &pAdapter);
         if (FAILED(hr))
         {
             return E_FAIL;
         }
         ddt = D3D_DRIVER_TYPE_UNKNOWN;
     }
     else if (pNewDeviceSettings->d3d11.DriverType == D3D_DRIVER_TYPE_WARP)
     {
         ddt = D3D_DRIVER_TYPE_WARP;
         pAdapter = nullptr;
     }
     else if (pNewDeviceSettings->d3d11.DriverType == D3D_DRIVER_TYPE_REFERENCE)
     {
         ddt = D3D_DRIVER_TYPE_REFERENCE;
         pAdapter = nullptr;
     }
#else
     UINT nAdapterNum = pNewDeviceSettings->d3d11.AdapterOrdinal;
     hres = m_pDXGIFactory->EnumAdapters1(nAdapterNum, &pAdapter);
     if (FAILED(hres))
         return E_FAIL;
     ddt = D3D_DRIVER_TYPE_UNKNOWN;
#endif


     //
     if (SUCCEEDED(hr))
     {
         hr = DXUT_Dynamic_D3D11CreateDevice(pAdapter,
             ddt,
             (HMODULE)0,
             pNewDeviceSettings->d3d11.CreateFlags,
             &pNewDeviceSettings->d3d11.DeviceFeatureLevel,
             1,
             D3D11_SDK_VERSION,
             &pd3d11Device,
             &FeatureLevel,
             &pd3dImmediateContext
         );

         if (FAILED(hr))
         {
             pAdapter = nullptr;
             // Remote desktop does not allow you to enumerate the adapter.  In this case, we let D3D11 do the enumeration.
             if (ddt == D3D_DRIVER_TYPE_UNKNOWN)
             {
                 hr = DXUT_Dynamic_D3D11CreateDevice(pAdapter,
                     D3D_DRIVER_TYPE_HARDWARE,
                     (HMODULE)0,
                     pNewDeviceSettings->d3d11.CreateFlags,
                     &pNewDeviceSettings->d3d11.DeviceFeatureLevel,
                     1,
                     D3D11_SDK_VERSION,
                     &pd3d11Device,
                     &FeatureLevel,
                     &pd3dImmediateContext
                 );
             }
             if (FAILED(hr))
             {
                 DXUT_ERR(L"D3D11CreateDevice", hr);
                 return DXUTERR_CREATINGDEVICE;
             }
         }
     }

#ifndef NDEBUG
     if (SUCCEEDED(hr))
     {
         ID3D11Debug* d3dDebug = nullptr;
         if (SUCCEEDED(pd3d11Device->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&d3dDebug))))
         {
             ID3D11InfoQueue* infoQueue = nullptr;
             if (SUCCEEDED(d3dDebug->QueryInterface(__uuidof(ID3D11InfoQueue), reinterpret_cast<void**>(&infoQueue))))
             {
                 // ignore some "expected" errors
                 D3D11_MESSAGE_ID denied[] =
                 {
                     D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                 };

                 D3D11_INFO_QUEUE_FILTER filter;
                 memset(&filter, 0, sizeof(filter));
                 filter.DenyList.NumIDs = _countof(denied);
                 filter.DenyList.pIDList = denied;
                 infoQueue->AddStorageFilterEntries(&filter);
                 infoQueue->Release();
             }
             d3dDebug->Release();
         }
     }
#endif

     if (SUCCEEDED(hr))
     {
         IDXGIDevice1* pDXGIDev = nullptr;
         hr = pd3d11Device->QueryInterface(__uuidof(IDXGIDevice1), (LPVOID*)&pDXGIDev);
         if (SUCCEEDED(hr) && pDXGIDev)
         {
             if (!pAdapter)
             {
                 IDXGIAdapter* pTempAdapter = nullptr;
                 V_RETURN(pDXGIDev->GetAdapter(&pTempAdapter));
                 V_RETURN(pTempAdapter->QueryInterface(__uuidof(IDXGIAdapter1), (LPVOID*)&pAdapter));
                 V_RETURN(pAdapter->GetParent(__uuidof(IDXGIFactory1), (LPVOID*)&pDXGIFactory));
                 SAFE_RELEASE(pTempAdapter);
                 if (GetDXUTState_GetDXGIFactory() != pDXGIFactory)
                     GetDXUTState_GetDXGIFactory()->Release();
                 GetDXUTState_SetDXGIFactory(pDXGIFactory);
             }
         }
         SAFE_RELEASE(pDXGIDev);
         GetDXUTState_SetDXGIAdapter(pAdapter);
     }

     if (FAILED(hr))
     {
         DXUT_ERR(L"D3D11CreateDevice", hr);
         return DXUTERR_CREATINGDEVICE;
     }

     // set default render state to msaa enabled
     D3D11_RASTERIZER_DESC drd = {
         D3D11_FILL_SOLID, //D3D11_FILL_MODE FillMode;
         D3D11_CULL_BACK,//D3D11_CULL_MODE CullMode;
         FALSE, //BOOL FrontCounterClockwise;
         0, //INT DepthBias;
         0.0f,//FLOAT DepthBiasClamp;
         0.0f,//FLOAT SlopeScaledDepthBias;
         TRUE,//BOOL DepthClipEnable;
         FALSE,//BOOL ScissorEnable;
         TRUE,//BOOL MultisampleEnable;
         FALSE//BOOL AntialiasedLineEnable;        
     };
     ID3D11RasterizerState* pRS = nullptr;
     hr = pd3d11Device->CreateRasterizerState(&drd, &pRS);
     if (FAILED(hr))
     {
         DXUT_ERR(L"CreateRasterizerState", hr);
         return DXUTERR_CREATINGDEVICE;
     }
     DXUT_SetDebugName(pRS, "DXUT Default");
     GetDXUTState_SetD3D11RasterizerState(pRS);
     pd3dImmediateContext->RSSetState(pRS);

     // Enumerate its outputs.
     UINT OutputCount, iOutput;
     for (OutputCount = 0; ; ++OutputCount)
     {
         IDXGIOutput* pOutput;
         if (FAILED(pAdapter->EnumOutputs(OutputCount, &pOutput)))
             break;
         SAFE_RELEASE(pOutput);
     }
     auto ppOutputArray = new (std::nothrow) IDXGIOutput * [OutputCount];
     if (!ppOutputArray)
         return E_OUTOFMEMORY;
     for (iOutput = 0; iOutput < OutputCount; ++iOutput)
         pAdapter->EnumOutputs(iOutput, ppOutputArray + iOutput);
     GetDXUTState_SetDXGIOutputArray(ppOutputArray);
     GetDXUTState_SetDXGIOutputArraySize(OutputCount);

     // Create the swapchain
     if (!pQyMc->appParams.bService) {
         //
         hr = pDXGIFactory->CreateSwapChain(pd3d11Device, &pNewDeviceSettings->d3d11.sd, &pSwapChain);
         if (FAILED(hr))
         {
             //
             showInfo_open0(0, 0, _T("qmdCliHelp_DXUTCreate3DEnv: CreateSwapChain failed"));
             //
             DXUT_ERR(L"CreateSwapChain", hr);
             return DXUTERR_CREATINGDEVICE;
         }
     }

     GetDXUTState_SetD3D11Device(pd3d11Device);
     GetDXUTState_SetD3D11DeviceContext(pd3dImmediateContext);
     GetDXUTState_SetD3D11FeatureLevel(FeatureLevel);
     GetDXUTState_SetDXGISwapChain(pSwapChain);

     assert(pd3d11Device);
     _Analysis_assume_(pd3d11Device);

     assert(pd3dImmediateContext);
     _Analysis_assume_(pd3dImmediateContext);

     // Direct3D 11.1
     {
         ID3D11Device1* pd3d11Device1 = nullptr;
         hr = pd3d11Device->QueryInterface(__uuidof(ID3D11Device1), (LPVOID*)&pd3d11Device1);
         if (SUCCEEDED(hr) && pd3d11Device1)
         {
             GetDXUTState_SetD3D11Device1(pd3d11Device1);

             ID3D11DeviceContext1* pd3dImmediateContext1 = nullptr;
             hr = pd3dImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), (LPVOID*)&pd3dImmediateContext1);
             if (SUCCEEDED(hr) && pd3dImmediateContext1)
             {
                 GetDXUTState_SetD3D11DeviceContext1(pd3dImmediateContext1);
             }
         }
     }

#ifdef USE_DIRECT3D11_2
     // Direct3D 11.2
     {
         ID3D11Device2* pd3d11Device2 = nullptr;
         hr = pd3d11Device->QueryInterface(__uuidof(ID3D11Device2), (LPVOID*)&pd3d11Device2);
         if (SUCCEEDED(hr) && pd3d11Device2)
         {
             GetDXUTState().SetD3D11Device2(pd3d11Device2);

             ID3D11DeviceContext2* pd3dImmediateContext2 = nullptr;
             hr = pd3dImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext2), (LPVOID*)&pd3dImmediateContext2);
             if (SUCCEEDED(hr) && pd3dImmediateContext2)
             {
                 GetDXUTState().SetD3D11DeviceContext2(pd3dImmediateContext2);
             }
         }
     }
#endif

     // If switching to REF, set the exit code to 11.  If switching to HAL and exit code was 11, then set it back to 0.
     if (pNewDeviceSettings->d3d11.DriverType == D3D_DRIVER_TYPE_REFERENCE && GetDXUTState_GetExitCode() == 0)
         GetDXUTState_SetExitCode(10);
     else if (pNewDeviceSettings->d3d11.DriverType == D3D_DRIVER_TYPE_HARDWARE && GetDXUTState_GetExitCode() == 10)
         GetDXUTState_SetExitCode(0);

     // Update back buffer desc before calling app's device callbacks
     if (!pQyMc->appParams.bService) {
         //
         DXUTUpdateBackBufferDesc();
     }

     // Setup cursor based on current settings (window/fullscreen mode, show cursor state, clip cursor state)
     DXUTSetupCursor();

     // Update the device stats text
     auto pd3dEnum = DXUTGetD3D11Enumeration();
     assert(pd3dEnum);
     _Analysis_assume_(pd3dEnum);
     auto pAdapterInfo = pd3dEnum->GetAdapterInfo(pNewDeviceSettings->d3d11.AdapterOrdinal);
     DXUTUpdateD3D11DeviceStats(pNewDeviceSettings->d3d11.DriverType, pNewDeviceSettings->d3d11.DeviceFeatureLevel, &pAdapterInfo->AdapterDesc);

     // Call the app's device created callback if non-NULL
     auto pBackBufferSurfaceDesc = DXUTGetDXGIBackBufferSurfaceDesc();
     GetDXUTState_SetInsideDeviceCallback(true);
     auto pCallbackDeviceCreated = GetDXUTState_GetD3D11DeviceCreatedFunc();
     hr = S_OK;
     if (pCallbackDeviceCreated)
         hr = pCallbackDeviceCreated(DXUTGetD3D11Device(), pBackBufferSurfaceDesc,
             GetDXUTState_GetD3D11DeviceCreatedFuncUserContext());
     GetDXUTState_SetInsideDeviceCallback(false);
     if (!DXUTGetD3D11Device()) // Handle DXUTShutdown from inside callback
         return E_FAIL;
     if (FAILED(hr))
     {
         DXUT_ERR(L"DeviceCreated callback", hr);
         return (hr == DXUTERR_MEDIANOTFOUND) ? DXUTERR_MEDIANOTFOUND : DXUTERR_CREATINGDEVICEOBJECTS;
     }
     GetDXUTState_SetDeviceObjectsCreated(true);

     // Setup the render target view and viewport
     if (!pQyMc->appParams.bService) {
         //
         hr = DXUTCreateD3D11Views(pd3d11Device, pd3dImmediateContext, pNewDeviceSettings);
         if (FAILED(hr))
         {
             DXUT_ERR(L"DXUTCreateD3D11Views", hr);
             return DXUTERR_CREATINGDEVICEOBJECTS;
         }
     }

     // Call the app's swap chain reset callback if non-NULL
     GetDXUTState_SetInsideDeviceCallback(true);
     LPDXUTCALLBACKD3D11SWAPCHAINRESIZED pCallbackSwapChainResized = GetDXUTState_GetD3D11SwapChainResizedFunc();
     hr = S_OK;
     if (pCallbackSwapChainResized)
         hr = pCallbackSwapChainResized(DXUTGetD3D11Device(), pSwapChain, pBackBufferSurfaceDesc,
             GetDXUTState_GetD3D11SwapChainResizedFuncUserContext());
     GetDXUTState_SetInsideDeviceCallback(false);
     if (!DXUTGetD3D11Device()) // Handle DXUTShutdown from inside callback
         return E_FAIL;
     if (FAILED(hr))
     {
         DXUT_ERR(L"DeviceReset callback", hr);
         return (hr == DXUTERR_MEDIANOTFOUND) ? DXUTERR_MEDIANOTFOUND : DXUTERR_RESETTINGDEVICEOBJECTS;
     }
     GetDXUTState_SetDeviceObjectsReset(true);

     return S_OK;
 }


 void WINAPI qyMcu_DXUTRender3DEnvironment()
 {
     HRESULT hr;
     //
     CCtxQyMc* pQyMc = QY_GET_GBUF();

     //
     auto pd3dDevice = DXUTGetD3D11Device();
     if (!pd3dDevice)
         return;

     auto pd3dImmediateContext = DXUTGetD3D11DeviceContext();
     if (!pd3dImmediateContext)
         return;

     auto pSwapChain = DXUTGetDXGISwapChain();
#if  0
     if (!pSwapChain)
         return;
#endif

     //
     if (DXUTIsRenderingPaused() || !DXUTIsActive() || GetDXUTState_GetRenderingOccluded())
     {
         // Window is minimized/paused/occluded/or not exclusive so yield CPU time to other processes
         //Sleep( 50 );
         Sleep(25);
         //
#ifdef  __DEBUG__
        //showInfo_open0(  0,  0,  _T(  "qyMcu_DXUTRender3DEnvironment: Sleep( 25  )"  )  );
#endif
     }

     // Get the app's time, in seconds. Skip rendering if no time elapsed
     double fTime, fAbsTime; float fElapsedTime;
     DXUTGetGlobalTimer()->GetTimeValues(&fTime, &fAbsTime, &fElapsedTime);

     // Store the time for the app
     if (GetDXUTState_GetConstantFrameTime())
     {
         fElapsedTime = GetDXUTState_GetTimePerFrame();
         fTime = DXUTGetTime() + fElapsedTime;
     }

     GetDXUTState_SetTime(fTime);
     GetDXUTState_SetAbsoluteTime(fAbsTime);
     GetDXUTState_SetElapsedTime(fElapsedTime);

     // Update the FPS stats
     DXUTUpdateFrameStats();

     DXUTHandleTimers();

     // Animate the scene by calling the app's frame move callback
     LPDXUTCALLBACKFRAMEMOVE pCallbackFrameMove = GetDXUTState_GetFrameMoveFunc();
     if (pCallbackFrameMove)
     {
         pCallbackFrameMove(fTime, fElapsedTime, GetDXUTState_GetFrameMoveFuncUserContext());
         pd3dDevice = DXUTGetD3D11Device();
         if (!pd3dDevice) // Handle DXUTShutdown from inside callback
             return;
     }

     if (!GetDXUTState_GetRenderingPaused())
     {
         // Render the scene by calling the app's render callback
         LPDXUTCALLBACKD3D11FRAMERENDER pCallbackFrameRender = GetDXUTState_GetD3D11FrameRenderFunc();
         if (pCallbackFrameRender && !GetDXUTState_GetRenderingOccluded())
         {
             pCallbackFrameRender(pd3dDevice, pd3dImmediateContext, fTime, fElapsedTime,
                 GetDXUTState_GetD3D11FrameRenderFuncUserContext());

             pd3dDevice = DXUTGetD3D11Device();
             if (!pd3dDevice) // Handle DXUTShutdown from inside callback
                 return;
         }

#if defined(DEBUG) || defined(_DEBUG)
         // The back buffer should always match the client rect 
         // if the Direct3D backbuffer covers the entire window
         RECT rcClient;
         GetClientRect(DXUTGetHWND(), &rcClient);
         if (!IsIconic(DXUTGetHWND()))
         {
             GetClientRect(DXUTGetHWND(), &rcClient);

             if (!pQyMc->appParams.bService) {
                 //
                 assert(DXUTGetDXGIBackBufferSurfaceDesc()->Width == (UINT)rcClient.right);
                 assert(DXUTGetDXGIBackBufferSurfaceDesc()->Height == (UINT)rcClient.bottom);
             }
         }
#endif
     }

     if (GetDXUTState_GetSaveScreenShot())
     {
         DXUTSnapD3D11Screenshot(GetDXUTState_GetScreenShotName(), false);
     }
     if (GetDXUTState_GetExitAfterScreenShot())
     {
         DXUTShutdown();
         return;
     }

     DWORD dwFlags = 0;
     if (GetDXUTState_GetRenderingOccluded())
         dwFlags = DXGI_PRESENT_TEST;
     else
         dwFlags = GetDXUTState_GetCurrentDeviceSettings()->d3d11.PresentFlags;
     UINT SyncInterval = GetDXUTState_GetCurrentDeviceSettings()->d3d11.SyncInterval;

     if (pSwapChain) {
         //
     // Show the frame on the primary surface.
         hr = pSwapChain->Present(SyncInterval, dwFlags);
         if (DXGI_STATUS_OCCLUDED == hr)
         {
             // There is a window covering our entire rendering area.
             // Don't render until we're visible again.
             GetDXUTState_SetRenderingOccluded(true);
         }
         else if (DXGI_ERROR_DEVICE_RESET == hr)
         {
             // If a mode change happened, we must reset the device
             if (FAILED(hr = DXUTReset3DEnvironment11()))
             {
                 if (DXUTERR_RESETTINGDEVICEOBJECTS == hr ||
                     DXUTERR_MEDIANOTFOUND == hr)
                 {
                     DXUTDisplayErrorMessage(hr);
                     DXUTShutdown();
                     return;
                 }
                 else
                 {
                     // Reset failed, but the device wasn't lost so something bad happened, 
                     // so recreate the device to try to recover
                     auto pDeviceSettings = GetDXUTState_GetCurrentDeviceSettings();
                     //
                     //showInfo_open0(  0,  0,  _T(  "before DXUTChangeDevice"  )  );
                     //
                     if (FAILED(qyMcu_DXUTChangeDevice(pDeviceSettings, false)))
                     {
                         DXUTShutdown();
                         return;
                     }

                     // How to handle display orientation changes in full-screen mode?
                 }
             }
         }
         else if (DXGI_ERROR_DEVICE_REMOVED == hr)
         {
             // Use a callback to ask the app if it would like to find a new device.  
             // If no device removed callback is set, then look for a new device
             if (FAILED(DXUTHandleDeviceRemoved()))
             {
                 // Perhaps get more information from pD3DDevice->GetDeviceRemovedReason()?
                 DXUTDisplayErrorMessage(DXUTERR_DEVICEREMOVED);
                 DXUTShutdown();
                 return;
             }
         }
         else if (SUCCEEDED(hr))
         {
             if (GetDXUTState_GetRenderingOccluded())
             {
                 // Now that we're no longer occluded
                 // allow us to render again
                 GetDXUTState_SetRenderingOccluded(false);
             }
         }
     }

     // Update current frame #
     int nFrame = GetDXUTState_GetCurrentFrameNumber();
     nFrame++;
     GetDXUTState_SetCurrentFrameNumber(nFrame);

     // Check to see if the app should shutdown due to cmdline
     if (GetDXUTState_GetOverrideQuitAfterFrame() != 0)
     {
         if (nFrame > GetDXUTState_GetOverrideQuitAfterFrame())
             DXUTShutdown();
     }

     return;
 }


 //
 _Use_decl_annotations_
     HRESULT WINAPI qyMcu_DXUTCreateWindow(const WCHAR* strWindowTitle, HINSTANCE hInstance,
         HICON hIcon, HMENU hMenu, int x, int y)
 {
     HRESULT hr;

     // Not allowed to call this from inside the device callbacks
     if (GetDXUTState_GetInsideDeviceCallback())
         return DXUT_ERR_MSGBOX(L"DXUTCreateWindow", E_FAIL);

     GetDXUTState_SetWindowCreateCalled(true);

     if (!GetDXUTState_GetDXUTInited())
     {
         // If DXUTInit() was already called and failed, then fail.
         // DXUTInit() must first succeed for this function to succeed
         if (GetDXUTState_GetDXUTInitCalled())
             return E_FAIL;

         // If DXUTInit() hasn't been called, then automatically call it
         // with default params
         hr = DXUTInit();
         if (FAILED(hr))
             return hr;
     }

     if (!DXUTGetHWNDFocus())
     {
         if (!hInstance)
             hInstance = (HINSTANCE)GetModuleHandle(nullptr);
         GetDXUTState_SetHInstance(hInstance);

         WCHAR szExePath[MAX_PATH];
         GetModuleFileName(nullptr, szExePath, MAX_PATH);
         if (!hIcon) // If the icon is NULL, then use the first one found in the exe
             hIcon = ExtractIcon(hInstance, szExePath, 0);

         // Register the windows class
         WNDCLASS wndClass;
         wndClass.style = CS_DBLCLKS;
         wndClass.lpfnWndProc = qyMcu_DXUTStaticWndProc;
         wndClass.cbClsExtra = 0;
         wndClass.cbWndExtra = 0;
         wndClass.hInstance = hInstance;
         wndClass.hIcon = hIcon;
         wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
         wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
         wndClass.lpszMenuName = nullptr;
         wndClass.lpszClassName = L"Direct3DWindowClass";

         if (!RegisterClass(&wndClass))
         {
             DWORD dwError = GetLastError();
             if (dwError != ERROR_CLASS_ALREADY_EXISTS)
                 return DXUT_ERR_MSGBOX(L"RegisterClass", HRESULT_FROM_WIN32(dwError));
         }

         // Override the window's initial & size position if there were cmd line args
         if (GetDXUTState_GetOverrideStartX() != -1)
             x = GetDXUTState_GetOverrideStartX();
         if (GetDXUTState_GetOverrideStartY() != -1)
             y = GetDXUTState_GetOverrideStartY();

         GetDXUTState_SetWindowCreatedWithDefaultPositions(false);
         if (x == CW_USEDEFAULT && y == CW_USEDEFAULT)
             GetDXUTState_SetWindowCreatedWithDefaultPositions(true);

         // Find the window's initial size, but it might be changed later
         int nDefaultWidth = 800;
         int nDefaultHeight = 600;
         if (GetDXUTState_GetOverrideWidth() != 0)
             nDefaultWidth = GetDXUTState_GetOverrideWidth();
         if (GetDXUTState_GetOverrideHeight() != 0)
             nDefaultHeight = GetDXUTState_GetOverrideHeight();

         RECT rc;
         SetRect(&rc, 0, 0, nDefaultWidth, nDefaultHeight);
         AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, (hMenu) ? true : false);

         WCHAR* strCachedWindowTitle = GetDXUTState_GetWindowTitle();
         wcscpy_s(strCachedWindowTitle, 256, strWindowTitle);

         // Create the render window
         HWND hWnd = CreateWindow(L"Direct3DWindowClass", strWindowTitle, WS_OVERLAPPEDWINDOW,
             x, y, (rc.right - rc.left), (rc.bottom - rc.top), 0,
             hMenu, hInstance, 0);
         if (!hWnd)
         {
             DWORD dwError = GetLastError();
             return DXUT_ERR_MSGBOX(L"CreateWindow", HRESULT_FROM_WIN32(dwError));
         }

         GetDXUTState_SetWindowCreated(true);
         GetDXUTState_SetHWNDFocus(hWnd);
         GetDXUTState_SetHWNDDeviceFullScreen(hWnd);
         GetDXUTState_SetHWNDDeviceWindowed(hWnd);
     }

     return S_OK;
 }



 //
 _Use_decl_annotations_
     LRESULT CALLBACK qyMcu_DXUTStaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
 {

     // Consolidate the keyboard messages and pass them to the app's keyboard callback
     if (uMsg == WM_KEYDOWN ||
         uMsg == WM_SYSKEYDOWN ||
         uMsg == WM_KEYUP ||
         uMsg == WM_SYSKEYUP)
     {
         bool bKeyDown = (uMsg == WM_KEYDOWN || uMsg == WM_SYSKEYDOWN);
         DWORD dwMask = (1 << 29);
         bool bAltDown = ((lParam & dwMask) != 0);

         bool* bKeys = GetDXUTState_GetKeys();
         bKeys[(BYTE)(wParam & 0xFF)] = bKeyDown;

         LPDXUTCALLBACKKEYBOARD pCallbackKeyboard = GetDXUTState_GetKeyboardFunc();
         if (pCallbackKeyboard)
             pCallbackKeyboard((UINT)wParam, bKeyDown, bAltDown, GetDXUTState_GetKeyboardFuncUserContext());
     }

     // Consolidate the mouse button messages and pass them to the app's mouse callback
     if (uMsg == WM_LBUTTONDOWN ||
         uMsg == WM_LBUTTONUP ||
         uMsg == WM_LBUTTONDBLCLK ||
         uMsg == WM_MBUTTONDOWN ||
         uMsg == WM_MBUTTONUP ||
         uMsg == WM_MBUTTONDBLCLK ||
         uMsg == WM_RBUTTONDOWN ||
         uMsg == WM_RBUTTONUP ||
         uMsg == WM_RBUTTONDBLCLK ||
         uMsg == WM_XBUTTONDOWN ||
         uMsg == WM_XBUTTONUP ||
         uMsg == WM_XBUTTONDBLCLK ||
         uMsg == WM_MOUSEWHEEL ||
         (GetDXUTState_GetNotifyOnMouseMove() && uMsg == WM_MOUSEMOVE))
     {
         int xPos = (short)LOWORD(lParam);
         int yPos = (short)HIWORD(lParam);

         if (uMsg == WM_MOUSEWHEEL)
         {
             // WM_MOUSEWHEEL passes screen mouse coords
             // so convert them to client coords
             POINT pt;
             pt.x = xPos; pt.y = yPos;
             ScreenToClient(hWnd, &pt);
             xPos = pt.x; yPos = pt.y;
         }

         int nMouseWheelDelta = 0;
         if (uMsg == WM_MOUSEWHEEL)
             nMouseWheelDelta = (short)HIWORD(wParam);

         int nMouseButtonState = LOWORD(wParam);
         bool bLeftButton = ((nMouseButtonState & MK_LBUTTON) != 0);
         bool bRightButton = ((nMouseButtonState & MK_RBUTTON) != 0);
         bool bMiddleButton = ((nMouseButtonState & MK_MBUTTON) != 0);
         bool bSideButton1 = ((nMouseButtonState & MK_XBUTTON1) != 0);
         bool bSideButton2 = ((nMouseButtonState & MK_XBUTTON2) != 0);

         bool* bMouseButtons = GetDXUTState_GetMouseButtons();
         bMouseButtons[0] = bLeftButton;
         bMouseButtons[1] = bMiddleButton;
         bMouseButtons[2] = bRightButton;
         bMouseButtons[3] = bSideButton1;
         bMouseButtons[4] = bSideButton2;

         LPDXUTCALLBACKMOUSE pCallbackMouse = GetDXUTState_GetMouseFunc();
         if (pCallbackMouse)
             pCallbackMouse(bLeftButton, bRightButton, bMiddleButton, bSideButton1, bSideButton2, nMouseWheelDelta,
                 xPos, yPos, GetDXUTState_GetMouseFuncUserContext());
     }

     // TODO - WM_POINTER for touch when on Windows 8.0

     // Pass all messages to the app's MsgProc callback, and don't 
     // process further messages if the apps says not to.
     LPDXUTCALLBACKMSGPROC pCallbackMsgProc = GetDXUTState_GetWindowMsgFunc();
     if (pCallbackMsgProc)
     {
         bool bNoFurtherProcessing = false;
         LRESULT nResult = pCallbackMsgProc(hWnd, uMsg, wParam, lParam, &bNoFurtherProcessing,
             GetDXUTState_GetWindowMsgFuncUserContext());
         if (bNoFurtherProcessing)
             return nResult;
     }

     switch (uMsg)
     {
     case WM_PAINT:
     {
         // Handle paint messages when the app is paused
         if (DXUTIsRenderingPaused() &&
             GetDXUTState_GetDeviceObjectsCreated() && GetDXUTState_GetDeviceObjectsReset())
         {
             HRESULT hr;
             double fTime = DXUTGetTime();
             float fElapsedTime = DXUTGetElapsedTime();

             {
                 auto pd3dDevice = DXUTGetD3D11Device();
                 auto pDeferred = DXUTGetD3D11DeviceContext();
                 if (pd3dDevice)
                 {
                     LPDXUTCALLBACKD3D11FRAMERENDER pCallbackFrameRender = GetDXUTState_GetD3D11FrameRenderFunc();
                     if (pCallbackFrameRender &&
                         !GetDXUTState_GetRenderingOccluded())
                     {
                         pCallbackFrameRender(pd3dDevice, pDeferred, fTime, fElapsedTime,
                             GetDXUTState_GetD3D11FrameRenderFuncUserContext());
                     }

                     DWORD dwFlags = 0;
                     if (GetDXUTState_GetRenderingOccluded())
                         dwFlags = DXGI_PRESENT_TEST;
                     else
                         dwFlags = GetDXUTState_GetCurrentDeviceSettings()->d3d11.PresentFlags;

                     auto pSwapChain = DXUTGetDXGISwapChain();
                     if (pSwapChain) {
                         //
                         hr = pSwapChain->Present(0, GetDXUTState_GetCurrentDeviceSettings()->d3d11.PresentFlags);
                         if (DXGI_STATUS_OCCLUDED == hr)
                         {
                             // There is a window covering our entire rendering area.
                             // Don't render until we're visible again.
                             GetDXUTState_SetRenderingOccluded(true);
                         }
                         else if (SUCCEEDED(hr))
                         {
                             if (GetDXUTState_GetRenderingOccluded())
                             {
                                 // Now that we're no longer occluded
                                 // allow us to render again
                                 GetDXUTState_SetRenderingOccluded(false);
                             }
                         }
                     }
                 }
             }
         }
         break;
     }

     case WM_SIZE:

         if (SIZE_MINIMIZED == wParam)
         {
             DXUTPause(true, true); // Pause while we're minimized

             GetDXUTState_SetMinimized(true);
             GetDXUTState_SetMaximized(false);
         }
         else
         {
             RECT rcCurrentClient;
             GetClientRect(DXUTGetHWND(), &rcCurrentClient);
             if (rcCurrentClient.top == 0 && rcCurrentClient.bottom == 0)
             {
                 // Rapidly clicking the task bar to minimize and restore a window
                 // can cause a WM_SIZE message with SIZE_RESTORED when 
                 // the window has actually become minimized due to rapid change
                 // so just ignore this message
             }
             else if (SIZE_MAXIMIZED == wParam)
             {
                 if (GetDXUTState_GetMinimized())
                     DXUTPause(false, false); // Unpause since we're no longer minimized
                 GetDXUTState_SetMinimized(false);
                 GetDXUTState_SetMaximized(true);
                 DXUTCheckForWindowSizeChange();
                 DXUTCheckForWindowChangingMonitors();
             }
             else if (SIZE_RESTORED == wParam)
             {
                 //DXUTCheckForDXGIFullScreenSwitch();
                 if (GetDXUTState_GetMaximized())
                 {
                     GetDXUTState_SetMaximized(false);
                     DXUTCheckForWindowSizeChange();
                     DXUTCheckForWindowChangingMonitors();
                 }
                 else if (GetDXUTState_GetMinimized())
                 {
                     DXUTPause(false, false); // Unpause since we're no longer minimized
                     GetDXUTState_SetMinimized(false);
                     DXUTCheckForWindowSizeChange();
                     DXUTCheckForWindowChangingMonitors();
                 }
                 else if (GetDXUTState_GetInSizeMove())
                 {
                     // If we're neither maximized nor minimized, the window size 
                     // is changing by the user dragging the window edges.  In this 
                     // case, we don't reset the device yet -- we wait until the 
                     // user stops dragging, and a WM_EXITSIZEMOVE message comes.
                 }
                 else
                 {
                     // This WM_SIZE come from resizing the window via an API like SetWindowPos() so 
                     // resize and reset the device now.
                     DXUTCheckForWindowSizeChange();
                     DXUTCheckForWindowChangingMonitors();
                 }
             }
         }
         break;

     case WM_GETMINMAXINFO:
         ((MINMAXINFO*)lParam)->ptMinTrackSize.x = DXUT_MIN_WINDOW_SIZE_X;
         ((MINMAXINFO*)lParam)->ptMinTrackSize.y = DXUT_MIN_WINDOW_SIZE_Y;
         break;

     case WM_ENTERSIZEMOVE:
         // Halt frame movement while the app is sizing or moving
         DXUTPause(true, true);
         GetDXUTState_SetInSizeMove(true);
         break;

     case WM_EXITSIZEMOVE:
         DXUTPause(false, false);
         DXUTCheckForWindowSizeChange();
         DXUTCheckForWindowChangingMonitors();
         GetDXUTState_SetInSizeMove(false);
         break;

     case WM_SETCURSOR:
         if (DXUTIsActive() && !DXUTIsWindowed())
         {
             if (!GetDXUTState_GetShowCursorWhenFullScreen())
                 SetCursor(nullptr);

             return true; // prevent Windows from setting cursor to window class cursor
         }
         break;

     case WM_ACTIVATEAPP:
         if (wParam == TRUE && !DXUTIsActive()) // Handle only if previously not active 
         {
             GetDXUTState_SetActive(true);

             // Enable controller rumble & input when activating app
             DXUTEnableXInput(true);

             // The GetMinimizedWhileFullscreen() varible is used instead of !DXUTIsWindowed()
             // to handle the rare case toggling to windowed mode while the fullscreen application 
             // is minimized and thus making the pause count wrong
             if (GetDXUTState_GetMinimizedWhileFullscreen())
             {
                 GetDXUTState_SetMinimizedWhileFullscreen(false);

                 DXUTToggleFullScreen();
             }

             // Upon returning to this app, potentially disable shortcut keys 
             // (Windows key, accessibility shortcuts) 
             DXUTAllowShortcutKeys((DXUTIsWindowed()) ? GetDXUTState_GetAllowShortcutKeysWhenWindowed() :
                 GetDXUTState_GetAllowShortcutKeysWhenFullscreen());

         }
         else if (wParam == FALSE && DXUTIsActive()) // Handle only if previously active 
         {
             GetDXUTState_SetActive(false);

             // Disable any controller rumble & input when de-activating app
             DXUTEnableXInput(false);

             if (!DXUTIsWindowed())
             {
                 // Going from full screen to a minimized state 
                 ClipCursor(nullptr);      // don't limit the cursor anymore
                 GetDXUTState_SetMinimizedWhileFullscreen(true);
             }

             // Restore shortcut keys (Windows key, accessibility shortcuts) to original state
             //
             // This is important to call here if the shortcuts are disabled, 
             // because if this is not done then the Windows key will continue to 
             // be disabled while this app is running which is very bad.
             // If the app crashes, the Windows key will return to normal.
             DXUTAllowShortcutKeys(true);
         }
         break;

     case WM_ENTERMENULOOP:
         // Pause the app when menus are displayed
         DXUTPause(true, true);
         break;

     case WM_EXITMENULOOP:
         DXUTPause(false, false);
         break;

     case WM_MENUCHAR:
         // A menu is active and the user presses a key that does not correspond to any mnemonic or accelerator key
         // So just ignore and don't beep
         return MAKELRESULT(0, MNC_CLOSE);
         break;

     case WM_NCHITTEST:
         // Prevent the user from selecting the menu in full screen mode
         if (!DXUTIsWindowed())
             return HTCLIENT;
         break;

     case WM_POWERBROADCAST:
         switch (wParam)
         {
         case PBT_APMQUERYSUSPEND:
             // At this point, the app should save any data for open
             // network connections, files, etc., and prepare to go into
             // a suspended mode.  The app can use the MsgProc callback
             // to handle this if desired.
             return true;

         case PBT_APMRESUMESUSPEND:
             // At this point, the app should recover any data, network
             // connections, files, etc., and resume running from when
             // the app was suspended. The app can use the MsgProc callback
             // to handle this if desired.

             // QPC may lose consistency when suspending, so reset the timer
             // upon resume.
             DXUTGetGlobalTimer()->Reset();
             GetDXUTState_SetLastStatsUpdateTime(0);
             return true;
         }
         break;

     case WM_SYSCOMMAND:
         // Prevent moving/sizing in full screen mode
         switch ((wParam & 0xFFF0))
         {
         case SC_MOVE:
         case SC_SIZE:
         case SC_MAXIMIZE:
         case SC_KEYMENU:
             if (!DXUTIsWindowed())
                 return 0;
             break;
         }
         break;

     case WM_KEYDOWN:
     {
         switch (wParam)
         {
         case VK_ESCAPE:
         {
             if (GetDXUTState_GetHandleEscape())
                 SendMessage(hWnd, WM_CLOSE, 0, 0);
             break;
         }

         case VK_PAUSE:
         {
             if (GetDXUTState_GetHandlePause())
             {
                 bool bTimePaused = DXUTIsTimePaused();
                 bTimePaused = !bTimePaused;
                 if (bTimePaused)
                     DXUTPause(true, false);
                 else
                     DXUTPause(false, false);
             }
             break;
         }
         }
         break;
     }

     case WM_CLOSE:
     {
         HMENU hMenu;
         hMenu = GetMenu(hWnd);
         if (hMenu)
             DestroyMenu(hMenu);
         DestroyWindow(hWnd);
         UnregisterClass(L"Direct3DWindowClass", nullptr);
         GetDXUTState_SetHWNDFocus(nullptr);
         GetDXUTState_SetHWNDDeviceFullScreen(nullptr);
         GetDXUTState_SetHWNDDeviceWindowed(nullptr);
         return 0;
     }

     case WM_DESTROY:
#if  0  //  2014/12/27
         PostQuitMessage(0);
#endif
         break;
     }

     // Don't allow the F10 key to act as a shortcut to the menu bar
     // by not passing these messages to the DefWindowProc only when
     // there's no menu present
     if (!GetDXUTState_GetCallDefWindowProc() || !GetDXUTState_GetMenu() &&
         (uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP) && wParam == VK_F10)
         return 0;
     else
         return DefWindowProc(hWnd, uMsg, wParam, lParam);
 }
