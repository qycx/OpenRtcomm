
//
#include	<WinSock2.h>
#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>

#include <winrt/base.h>

#include "D3DHelpers.h"
#include "Capture.h"
#include    "Readback.h"
#include    "Bitmap.h"

#include	"qmOpenCommon.h"

#include	"wgcCapturePublic.h"
#include <showInfo_open.h>
//
#include    "ctxQmcTmpl.h"
#include    "ctxQyMc.h"



//
#ifdef  _DEBUG
//
__declspec(dllexport) int test_wgc()
{
    WgcCapture wgc;

    //
    if (!wgc_initDev(&wgc)) {

        //
        int  i;
        for (i = 0; i < 1000; i++) {
            Sleep(1000);
        }

        //
        wgc_exitDev(&wgc);
    }

    //
    return  0;
}
#endif 






//
//extern "C" DWORD WINAPI wgc_threadProc_cap(LPVOID lpParameter)
unsigned __stdcall wgc_threadProc_cap(void* arg)
{
    //
    winrt::init_apartment(winrt::apartment_type::multi_threaded);

    WgcCapture* pWgc = static_cast<WgcCapture*>(arg);
    if (!pWgc->m_var.pProcInfoTmpl) {
        return  -1;
    }
    CCtxQyMc* pQyMc = pWgc->m_var.pProcInfoTmpl->pQyMc;
    if (!pQyMc) {
        return  -1;
    }
    
    //
    if (pWgc->m_var.bDbg_traceRt_wgc) {
        showInfo_open(0, 0, 0,  _T("wgc_th_cap: enters"));
    }

    //
    Readback readback;

    std::vector<unsigned char> pixels;

    int w, h;

    std::cout << "Windows Graphics Capture Demo\n";

    //
    auto last =
        std::chrono::steady_clock::now();

    int frames = 0;

    //
    if (pWgc->m_var.bDbg_traceRt_wgc) {
        showInfo_open(0, 0, 0, _T("wgc_th_cap: before d3d.init"));
    }

    //
    // 创建 D3D11
    //
    D3DHelpers d3d;

    if (!d3d.Initialize())
    {
        std::cout
            << "D3D initialize failed\n";

        return -1;
    }


    std::cout
        << "D3D OK\n";


    //
    // 创建 Capture
    //
    WGCCapture capture;


    if (!capture.Initialize(d3d))
    {
        std::cout
            << "Capture initialize failed\n";

        return -1;
    }


    capture.Start();


    std::cout
        << "Capture started\n";

    //
    if (pWgc->m_var.bDbg_traceRt_wgc) {
        showInfo_open(0, 0, 0, _T("Capture started"));
    }


    //
    bool  bNeedQuit_initForWriteFrame = false;

    //
    // 主循环
    //
    while (!pWgc->m_var.bQuit  &&  !bNeedQuit_initForWriteFrame  )
    {
        //
        showInfo_open(0, 0, 0, _T("wgc_cap: l146"));

        //
        winrt::com_ptr<ID3D11Texture2D> texture;

        //
        if (capture.GetFrame(texture))
        {
            //
            showInfo_open(0, 0, 0, _T("capture.GetFrame ok"));

            //
            if (readback.Copy(
                d3d.Device(),
                d3d.Context(),
                texture.get(),
                pixels,
                w,
                h))
            {
                //
                if (!w || !h) {
                    showInfo_open(0, 0, 0, _T("wgc_thread_cap err: w or h is 0"));
                    continue;
                }

                //
                int  iFmt;
                iFmt = 0;

                //
                if (!pWgc->m_var.bGot_wh) {
                    pWgc->m_var.w = w;
                    pWgc->m_var.h = h;
                    //
                    pWgc->m_var.bGot_wh = true;
                    //
                }
                if  (  !pWgc->m_var.pProcInfoTmpl->wgsWriteFrame_m_bInited)  {
                    //
                    Param_initForWriteFrame  param = { 0 };
                    //
                    if (!pWgc->m_var.pProcInfoTmpl->initForWriteFrame( iFmt, w, h, &param)) {
                        pWgc->m_var.pProcInfoTmpl->wgsWriteFrame_m_bInited = true;
                    }
                    else  {
                          //
                          if (param.bNeedQuit) {
                              //
                              bNeedQuit_initForWriteFrame = true;
                              //
                              showInfo_open(0, 0, 0, _T("bNeedQuit_initForWriteFrame set to true"));
                          }
                    }
                       
                }

                //
                if (pWgc->m_var.bDbg) {
                    std::cout
                        << "CPU Frame "
                        << w
                        << "x"
                        << h
                        << "\n";
                    TCHAR  tBuf[128];
                    _sntprintf(tBuf, mycountof(tBuf), _T("wgc: %dx%d, frames %d"), w, h, frames);
                    showInfo_open(0, 0, 0, tBuf);
                }
                 
                //
                pWgc->m_var.pProcInfoTmpl->procWgsCaptureFrame(iFmt, pixels.data(), w, h);
                

                //
                static bool saved = false;

                if (!saved)
                {
                    SaveBMP(
                        L"d:\\tttbbb\\screen.bmp",
                        pixels.data(),
                        w,
                        h);

                    saved = true;

                    std::cout
                        << "BMP saved\n";
                }

                //
            }
        }
        else {
             //
            if (pWgc->m_var.bDbg) {
                showInfo_open(0, 0, 0, _T(" capture.GetFrame(texture)) failed"));
            }
        }

        //
        frames++;

        auto now =
            std::chrono::steady_clock::now();


        auto ms =
            std::chrono::duration_cast<
            std::chrono::milliseconds>
            (now - last).count();


        if (ms >= 1000)
        {
            std::cout
                << "FPS="
                << frames
                << "\n";


            //frames = 0;

            //
            last = now;
        }


        //
        // 控制一下 CPU
        //
        std::this_thread::sleep_for(
            std::chrono::milliseconds(5));
    }

    //
    showInfo_open(0, 0, 0,  _T("wgc_th_cap: will quit"));

    //
    capture.Stop();

    //    
    pWgc->m_var.pProcInfoTmpl->exitForWriteFrame();    
    //
    pWgc->m_var.pProcInfoTmpl->wgsWriteFrame_m_bInited = false;
       


    //
    return 0;
}




//
__declspec(dllexport)  int  wgc_initDev(WgcCapture* pWgc)
{
	int  iErr = -1;

	do {
		WgcCapture* p = pWgc;

		//
		//LPTHREAD_START_ROUTINE lpStartAddress;
		//lpStartAddress = wgc_threadProc_cap;


		//
		DWORD	dwThreadDaemonId;
        //
        p->hThread_cap = (HANDLE)_beginthreadex(
                nullptr,
                0,
                wgc_threadProc_cap,
                pWgc,
                0,
                nullptr
            );

		if (!isHandleValid_open(p->hThread_cap))  {
			break;
		}
		//				   
		//pVDev->m_var.dwThreadId_dlg = dwThreadDaemonId;


		//
		iErr = 0;
	} while (false);

	//
	if (iErr) {
		wgc_exitDev(pWgc);
	}

	//
	return  iErr;
}

//

__declspec(dllexport)  int  wgc_exitDev(WgcCapture* pWgc)
{
	int  iErr = -1;

	do {
        //
        showInfo_open(0, 0, 0, _T("wgc_exitDev: start to waitFor thread_cap"));

        //
        pWgc->m_var.bQuit = true;
        waitForObject(&pWgc->hThread_cap, INFINITE);

        //
        showInfo_open(0, 0, 0, _T("wgc_exitDev: thread_cap waited"));

        //
		iErr = 0;
	} while (false);

	return  iErr;
}



//
__declspec(dllexport)  BOOL  wgc_bGetCapturePara(WgcCapture* pWgc, WAVEFORMATEX* pWf_org, QY_VIDEO_HEADER* pVh_org)
{
	bool  bRet = false;
    int  loopCtrl = 0;

	do {
        loopCtrl++;
        if (loopCtrl > 100) {   //  等10秒
            showInfo_open(0, 0, 0, _T("wgc_bGetCapturePara failed, waitFor wh too long"));
            break;
        }
        //
        if (!pWgc->m_var.bGot_wh) {
            //
            Sleep(100);
            continue;
        }
        //
        makeBmpInfoHeader_rgb(24, pWgc->m_var.w, pWgc->m_var.h, &pVh_org->bih);

		//
		bRet = true;

        //
        break;
	} while (true );

	return  bRet;
	
}

//

__declspec(dllexport)  int  wgc_runDev(WgcCapture* pWgc)
{
    int						iErr = -1;
    WgcCapture* p = (WgcCapture*)pWgc;

    if (!p)  return  -1;
    if (!p->m_var.bInited)  return  -1;

    //
    p->m_var.bRunning = true;

    //
    iErr = 0;
errLabel:
    return  iErr;
}


__declspec(dllexport)  int  wgc_stopDev(WgcCapture* pWgc)
{
    int						iErr = -1;
    WgcCapture* p = (WgcCapture*)pWgc;

    if (!p)  return  -1;
    if (!p->m_var.bInited)  return  -1;

    //
    p->m_var.bRunning = false;

    //
    iErr = 0;
errLabel:
    return  iErr;
}








