

#include	"stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__

	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>

#include	"qmcDmoPublic.h"

#include	"qmcVideoCapture_dx.h"
#include	"myfourcc.h"
#include	"mywmcodecconst.h"

#include	"qyCusResTemp.h"

//  #include	"myresource.h"
#ifdef  __SUPPORT_CUS_sampleGrabber__
		#include	"qySampleGrabberPublic.h"
#endif


#include	"qmcShareIc.h"
#include	"qmcCommFunc_isCli.h"

 int  myChkFmt_a_mediaDevice(  IAMStreamConfig  *  m_pASC,  WAVEFORMATEX  *  pWf_suggested,  BOOL  &  bMatched,  AM_MEDIA_TYPE  &  mt_matched  );
 int  myChkFmt_v(  IAMStreamConfig  *  m_pVSC,  BITMAPINFOHEADER  *  pBih_suggested,  BOOL  &  bMatched,  AM_MEDIA_TYPE  &  mt_matched  );

 int  tmp_iW = 5472;// 1440;
 int  tmp_iH = 3648;// 1080;

 // 定义钩子函数类型
 typedef void (*ImageDataHook)(void*p, unsigned char* pData, size_t size);
 // 定义设置钩子函数的函数类型
 typedef void (*SetImageDataHookFunc)(ImageDataHook hook);
 typedef int (*GetImageSizeFunc)(int& width, int& height);
 // 定义DoMvs函数类型
 typedef int (*DoMvsFunc)(void* p, bool& stop);

#include <iomanip>
#include <chrono>
#include <sstream>
#include <ctime>
#include <fstream>
 // 自定义的钩子函数实现
 void CustomImageDataHook(void* p, unsigned char* pData, size_t size) {
	 CCtxQyMc* pQyMc = g_pQyMc;
	 CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	 SHARE_IC* pIc = (SHARE_IC*)p;

	 if (pIc == nullptr) {
		 traceLogA((char*)"CustomImageDataHook: pIc is null");
		 return;
	 }

	//回调函数触发
	 int i = 1;
	 BufferCB_av(pProcInfo, pIc->index_sharedObj, &pIc->m_var, 0, (BYTE*)pData, size);

	 //
	 /*using namespace std::chrono;
	 auto now = system_clock::now();
	 time_t now_c = system_clock::to_time_t(now);
	 auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
	 std::stringstream ss;
	 FILE* m_fDataContent;
	 m_fDataContent = NULL;
	 ss << std::setw(3) << std::setfill('0') << ms.count();
	 std::stringstream ssFile;
	 ssFile << "C:\\tttbbb\\duli\\ouput_" << "_" << ss.str();

	 std::string ssFileRaw = ssFile.str() + ".raw";
	 int flag_savefile = fopen_s(&m_fDataContent, ssFileRaw.c_str(), "wb");

	 fwrite(pData, size, 1, m_fDataContent);
	 fclose(m_fDataContent);*/

 }



#if  10


 extern "C" DWORD WINAPI threadProc_ic_cap(LPVOID lpParameter)
 {
	 SHARE_IC* p = (SHARE_IC*)lpParameter;
	 int  size = tmp_iW * tmp_iH * 3;
	 //CQyMalloc  mallocObj;
	 //char* buf = (char*)mallocObj.mallocf(size);
	 //if (!buf)  return  -1;

	 CCtxQyMc* pQyMc = g_pQyMc;
	 CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	 //
	 DWORD  dwThreadId = GetCurrentThreadId();

	 //---------yu--start-------------
// 加载 DLL
	 //HINSTANCE hDll = LoadLibrary(L"testOpenCV.dll");
	 HINSTANCE hDll = LoadLibrary(L"hikIC.dll");
	 if (!hDll) return -1;

	 // 获取SetImageDataHook函数指针
	 SetImageDataHookFunc setHookFunc = (SetImageDataHookFunc)GetProcAddress(hDll, "SetImageDataHook");
	 if (setHookFunc == NULL) {
		 FreeLibrary(hDll);
		 return -1;
	 }

	 // 设置钩子函数
	 setHookFunc(CustomImageDataHook);

	 // 获取函数地址
	 DoMvsFunc doMvs = (DoMvsFunc)GetProcAddress(hDll, "DoMvs");
	 if (doMvs == NULL) {
		 FreeLibrary(hDll);
		 return -1;
	 }

	 bool& stop = p->bQuit;
	 int result = doMvs(p, stop);


	FreeLibrary(hDll);
	//
	return  0;
 }


#else


#ifdef  __DEBUG__
 //  Õâ¸öÏß³ÌÓÐÖúÓÚ½«test¶Ô»°¿òºÍÆäËû¶Ô»°²Ù×÷²¢ÐÐ½øÐÐ
 extern "C" DWORD WINAPI threadProc_ic_cap(LPVOID lpParameter)
 {
	 SHARE_IC* p = (SHARE_IC*)lpParameter;
	 int  size = tmp_iW * tmp_iH * 3;
	 CQyMalloc  mallocObj;
	 char* buf = (char*)mallocObj.mallocf(size);
	 if (!buf)  return  -1;

	 CCtxQyMc* pQyMc = g_pQyMc;
	 CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	 //
	 DWORD  dwThreadId = GetCurrentThreadId();

	 for (;;) {
		 if (p->bQuit)  break;
		 //
		 TCHAR* fn = (TCHAR*)_T("C:\\tttbbb\\duli\\969.raw");
		 FILE* fp = _tfopen(fn, _T("rb"));
		 if (fp) {
			 //
			 if (1 == fread(buf, size, 1, fp)) {

				 traceLog((TCHAR*)_T("ic_cap: get a img. threadId: %d"), dwThreadId);

				 //
				 BufferCB_av(pProcInfo, p->index_sharedObj, &p->m_var, 0, (BYTE*)buf, size);

			 }

			 //
			 fclose(fp);
		 }

		 //
		 Sleep(30);

		 //
		 continue;
	 }

	 //
	 return  0;
 }
#endif 


#endif 


 int  initShareIc(  void  **  ppCapStuff,  AUDIO_COMPRESSOR_CFG  *  pAudioCompressor,  BITMAPINFOHEADER  *  pBih_suggested,  HWND  hWnd_notify,  int  index_sharedObj,  void  **  ppShareMediaDeviceParam  )
{
	int						iErr		=		-1;

	HRESULT					hr;
	SHARE_IC	*	p			=		NULL;
	
	

	if  (  !ppShareMediaDeviceParam  )  return  -1;
	if  (  *ppShareMediaDeviceParam  )  return  -1;
	if  (  !pAudioCompressor  )  return  -1;
	
	WAVEFORMATEX	wf_suggested;
	if  (  pAudioCompressor->dev.ucbSetOrgAudioFmt  )  {
		wf_suggested  =  pAudioCompressor->dev.wf_org_suggested;
		wf_suggested.wFormatTag  =  WAVE_FORMAT_PCM;
		}
	else  {
		  wf_suggested  =  pAudioCompressor->wf_decompress_default;
	}
	WAVEFORMATEX  *  pWf_suggested  =  &wf_suggested;	//  &pAudioCompressor->wf_decompress_default;

	traceLogA(  (char*)  "initShareIc enters"  );

	p  =  (  SHARE_IC  *  )mymalloc(  sizeof(  SHARE_IC  )  );
	if  (  !p  )  goto  errLabel;
	memset(  p,  0,  sizeof(  SHARE_IC  )  );

	//
	p->index_sharedObj = index_sharedObj;

	HINSTANCE hDll = LoadLibrary(L"hikIC.dll");
	if (!hDll) return -1;	

	GetImageSizeFunc getSizeFunc = (GetImageSizeFunc)GetProcAddress(hDll, "GetImageSize");
	if (getSizeFunc != NULL) {
		
		getSizeFunc(tmp_iW, tmp_iH);
		
	}

	//
//#ifdef  __DEBUG__
	DWORD	dwThreadDaemonId;
	p->hThread_cap = CreateThread(NULL, 0, threadProc_ic_cap, p, CREATE_SUSPENDED, &dwThreadDaemonId);
	if (!isHandleValid(p->hThread_cap))  goto  errLabel;
	//				   
	//pVDev->m_var.dwThreadId_dlg = dwThreadDaemonId;
	if (ResumeThread(p->hThread_cap) == -1)  goto  errLabel;


//#endif 



	//
	p->bInited  =  TRUE;

	iErr  =  0;

errLabel:

	
	//
	if  (  iErr  )  {
		exitShareIc(  (  void  **  )&p  );
	}
	if  (  !iErr  )  {
		*ppShareMediaDeviceParam  =  p;
	}

	 return  iErr;
 }

 int  exitShareIc(  void  **  ppShareMediaDeviceParam  )
 {
	HRESULT					hr;
	SHARE_IC	*	p		=	(  SHARE_IC  *  )*ppShareMediaDeviceParam;
	if  (  !p  )  return  -1;

	traceLogA(  (char*)  "exitShareMediaDevice enters"  );

	stopShareIc(  p  );

	//

#ifdef  __DEBUG__
	p->bQuit = true;
	waitForObject(&p->hThread_cap, INFINITE);

#endif 
	




	free(  p  );

	*ppShareMediaDeviceParam  =  NULL;

	traceLogA(  (char*)  "exitShareMediaDevice leaves"  );


	return  0;
 }

 BOOL  bGetCapturePara_shareIc(  MC_VAR_common  *  pProcInfo,  int  iIndex_capAudio,  int  iIndex_capBmp,  void  *  pShareMediaDevice,  WAVEFORMATEX  *  pWf_org,  QY_VIDEO_HEADER  *  pVh_org  )
{
	SHARE_IC	*	p				=	(  SHARE_IC  *  )pShareMediaDevice;

	//
	makeBmpInfoHeader_rgb(24, tmp_iW, tmp_iH, &pVh_org->bih);

	//
	return true;
}


 int  runShareIc(  void  *  pShareMediaDeviceParam  )
{
	int						iErr	=	-1;
	SHARE_IC	*	p		=	(  SHARE_IC  *  )pShareMediaDeviceParam;
	
	if  (  !p  )  return  -1;
	if  (  !p->bInited  )  return  -1;

	//
	p->bRunning = true;

	//
	iErr  =  0;
errLabel:
	return  iErr;
}


 int  stopShareIc(  void  *  pShareMediaDeviceParam  )
 {
	 	int						iErr	=	-1;
	SHARE_IC	*	p		=	(  SHARE_IC  *  )pShareMediaDeviceParam;
	
	if  (  !p  )  return  -1;
	if  (  !p->bInited  )  return  -1;

	//
	p->bRunning = false;

	//
	iErr  =  0;
errLabel:
	 return  iErr;
 }




