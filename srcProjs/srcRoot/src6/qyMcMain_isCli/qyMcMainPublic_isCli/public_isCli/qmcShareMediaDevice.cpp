

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


#include	"qmcShareMediaDevice.h"
#include	"qmcCommFunc_isCli.h"

 int  myChkFmt_a_mediaDevice(  IAMStreamConfig  *  m_pASC,  WAVEFORMATEX  *  pWf_suggested,  BOOL  &  bMatched,  AM_MEDIA_TYPE  &  mt_matched  );
 int  myChkFmt_v(  IAMStreamConfig  *  m_pVSC,  BITMAPINFOHEADER  *  pBih_suggested,  BOOL  &  bMatched,  AM_MEDIA_TYPE  &  mt_matched  );



 //  int  initShareMediaDevice(  void  **  ppCapStuff,  WAVEFORMATEX  *  pWf_suggested,  BITMAPINFOHEADER  *  pBih_suggested,  HWND  hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppShareMediaDeviceParam  )
 int  initShareMediaDevice(  void  **  ppCapStuff,  AUDIO_COMPRESSOR_CFG  *  pAudioCompressor,  BITMAPINFOHEADER  *  pBih_suggested,  HWND  hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppShareMediaDeviceParam  )
{
	int						iErr		=		-1;

	HRESULT					hr;
	SHARE_MEDIA_DEVICE	*	p			=		NULL;
	
	IMoniker					*	pMoniker_a	=	NULL;
	IMoniker					*	pMoniker_v	=	NULL;

	BOOL							bMatched_a  =  FALSE;
	BOOL							bMatched_v  =  FALSE;
	AM_MEDIA_TYPE					mt_matched_a,  mt_matched_v;
	memset(  &mt_matched_a,  0,  sizeof(  mt_matched_a  )  );
	memset(  &mt_matched_v,  0,  sizeof(  mt_matched_v  )  );


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

	traceLogA(  (char*)  "initShareMediaDevice enters"  );

	p  =  (  SHARE_MEDIA_DEVICE  *  )mymalloc(  sizeof(  SHARE_MEDIA_DEVICE  )  );
	if  (  !p  )  goto  errLabel;
	memset(  p,  0,  sizeof(  SHARE_MEDIA_DEVICE  )  );


	//
	p->p_gcap  =  *ppCapStuff;	*ppCapStuff  =  NULL;		//  这里将对象转移了
	if  (  !p->p_gcap  )  goto  errLabel;

	{

		AV_capStuff& gcap = *(AV_capStuff*)p->p_gcap;


		// get the frame rate from win.ini before making the graph
		gcap.fUseFrameRate = 1;		//  GetProfileInt(TEXT("annie"), TEXT("UseFrameRate"), 1);
		int units_per_frame; units_per_frame = 666667;	//  GetProfileInt(TEXT("annie"), TEXT("FrameRate"), 666667);  // 15fps
		gcap.FrameRate = 10000000. / units_per_frame;
		gcap.FrameRate = (int)(gcap.FrameRate * 100) / 100.;

		// reasonable default
		if (gcap.FrameRate <= 0.)
			gcap.FrameRate = 15.0;

#ifdef  __DEBUG__
		//  gcap.FrameRate  =  8;
#endif

#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )

	//  ChooseDevices(  gcap,  (  TCHAR  *  )displayName_vDev,  (  TCHAR  *  )displayName_aDev  );
	//  enumAvDevices(  NULL,  NULL,  devicePath_selected,  &pMoniker  );	
		pMoniker_a = gcap.pmAudio;
		if (!pMoniker_a) {
#ifdef  __DEBUG__
			traceLog((TCHAR*)_T("initShareMediaDevice: pMoniker_a null"));
#endif
		}
		else {
			pMoniker_a->AddRef();
		}
		pMoniker_v = gcap.pmVideo;
		if (!pMoniker_v) {
#ifdef  __DEBUG__
			traceLogA((char*)"openLocalVideo failed:  pMoniker null");
#endif
			goto  errLabel;
		}
		pMoniker_v->AddRef();

		//  2012/02/24
		MC_VAR_isCli* pProcInfo; pProcInfo = QY_GET_procInfo_isCli();
		if (pMoniker_a) {
			if (bRecorderUsing(pProcInfo, pMoniker_a, NULL, NULL)) {
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("initShareMediaDevice failed, audio device is being used"));
				showNotification(NULL, NULL, NULL, 0, 0, 0, _T("Failed: audio device is used"));
				goto  errLabel;
			}
		}
		if (bWebcamUsing(pProcInfo, 0, pMoniker_v, NULL, NULL, NULL)) {
			//
			TCHAR  friendlyName[256];
			getMonikerFriendlyName(pMoniker_v, friendlyName, mycountof(friendlyName));
			//
			TCHAR  tBuf[128];
			_sntprintf(tBuf, mycountof(tBuf), _T("initShareMD Failed: video device is used，%s"), friendlyName);
			//
			showInfo_open0(0, 0, tBuf);
			showNotification(NULL, NULL, NULL, 0, 0, 0, tBuf);
			goto  errLabel;
		}


		//  if  (  !bBindFilter(  (  IMoniker  *  )pMoniker, &p->m_captureGraphBuilder.m_pMoniker,  &p->m_captureGraphBuilder.m_pBF  )  )  goto  errLabel;

		IMoniker* pmVideo; pmVideo = NULL;
		IMoniker* pmAudio; pmAudio = NULL;
		pmAudio = pMoniker_a;
		pmVideo = pMoniker_v;

		// they chose a new device. rebuild the graphs
		if (gcap.pmVideo != pmVideo || gcap.pmAudio != pmAudio)
		{
			if (pmVideo)
			{
				pmVideo->AddRef();
			}
			if (pmAudio)
			{
				pmAudio->AddRef();
			}

			IMonRelease(gcap.pmVideo);
			IMonRelease(gcap.pmAudio);
			gcap.pmVideo = pmVideo;
			gcap.pmAudio = pmAudio;

			if (gcap.fPreviewing)
				StopPreview(gcap);
			if (gcap.fCaptureGraphBuilt || gcap.fPreviewGraphBuilt)
				TearDownGraph(gcap);

			FreeCapFilters(gcap);
			InitCapFilters(gcap);

		}



#else
		{
			CComPtr<IBaseFilter>			m_pVideoCaptureFilter;
			CComPtr<IPersistPropertyBag>    pPropertyBag;

			CComVariant   varCamName;
			CPropertyBag  PropBag;
			//  OAEVENT       oaEvent;
			WCHAR	      wzDeviceName[MAX_PATH + 1];

			hr = m_pVideoCaptureFilter.CoCreateInstance(CLSID_VideoCapture);
			if (FAILED(hr))  goto  errLabel;
			hr = m_pVideoCaptureFilter.QueryInterface(&pPropertyBag);
			if (FAILED(hr))  goto  errLabel;


			hr = (GetFirstCameraDriver(wzDeviceName));
			if (FAILED(hr))  goto  errLabel;
			varCamName = wzDeviceName;
			if (varCamName.vt != VT_BSTR) {
				hr = E_OUTOFMEMORY;
				goto  errLabel;
			}

			hr = PropBag.Write(L"VCapName", &varCamName);
			if (FAILED(hr))  goto  errLabel;

			hr = pPropertyBag->Load(&PropBag, NULL);
			if (FAILED(hr))  goto  errLabel;

			p->m_pBF = m_pVideoCaptureFilter;
			p->m_pBF->AddRef();

		}
#endif

		//  2012/01/03
		p->bAudio = CAP_STUFF_bAudio(&gcap);
		p->bVideo = CAP_STUFF_bVideo(&gcap);


#if  10  //  ndef  __DEBUG__

		{

			IAMStreamConfig* m_pASC = gcap.pASC;				//  2013/03/20
			IAMStreamConfig* m_pVSC = gcap.pVSC;				//  for video cap
			IGraphBuilder* m_pGB = gcap.pFg;
			IBaseFilter* m_pBF_a = gcap.pACap;				//  2013/03/20
			IBaseFilter* m_pBF_v = gcap.pVCap;
			ICaptureGraphBuilder2* m_pCapture = (ICaptureGraphBuilder2*)get_ICaptureGraphBuilder(gcap.pBuilder);
			IBaseFilter* m_pDecFilter = NULL;		//  for mjpg. 2009/04/10



			BOOL	bConnectDirectly; bConnectDirectly = FALSE;
			//
			BOOL  bForConfig; bForConfig = FALSE;

			if (!bForConfig) {

				//  2013/03/20
				//  2016/03/02
				if (pAudioCompressor->dev.ucbSetOrgAudioFmt) {
					myChkFmt_a_mediaDevice(m_pASC, pWf_suggested, bMatched_a, mt_matched_a);
				}

#if  10	//  2013/03/22. 设置后upmost卡采集的视频异常,所以暂时取消
				//
				if (m_pASC) {
					AM_MEDIA_TYPE* pmt;
					hr = m_pASC->GetFormat(&pmt);
					if (SUCCEEDED(hr)) {

						if (pmt->majortype == MEDIATYPE_Audio
							&& pmt->formattype == FORMAT_WaveFormatEx
							&& pmt->cbFormat >= sizeof(WAVEFORMATEX)
							&& pmt->pbFormat)
						{
							WAVEFORMATEX* pWf = (WAVEFORMATEX*)pmt->pbFormat;

							unsigned  int  uiBytesRecorded_perBlockAlign = MACRO_getuiBytesRecorded_perBlockAlign(*pAudioCompressor, pWf);
							//			
							IAMBufferNegotiation* pNeg = NULL;

							hr = m_pCapture->FindInterface(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Audio, m_pBF_a, IID_IAMBufferNegotiation, (void**)&pNeg);
							if (SUCCEEDED(hr)) {
								ALLOCATOR_PROPERTIES AllocProp = { 0 };

								AllocProp.cbAlign = -1;  // -1 means no preference.
								//  AllocProp.cbBuffer = uiBytesRecorded_perBlockAlign  *  pWf->nBlockAlign;	//  dwBytesPerSec *  dwLatencyInMilliseconds / 1000;
								DWORD  dwBytesPerSec = pWf->nAvgBytesPerSec;
								DWORD  dwLatencyInMilliseconds = 100;
								AllocProp.cbBuffer = dwBytesPerSec * dwLatencyInMilliseconds / 1000;
								AllocProp.cbPrefix = -1;
								AllocProp.cBuffers = -1;
								//
								hr = pNeg->SuggestAllocatorProperties(&AllocProp);

								pNeg->Release();

								//
								TCHAR  tBuf[128];
								_sntprintf(tBuf, mycountof(tBuf), _T("SuggestAllocatorProperties: dwBytesPerSec %d, dwLatencyInMs %d, allocProp.cbBuffer %d, hr %d"), dwBytesPerSec, dwLatencyInMilliseconds, AllocProp.cbBuffer, hr);
								showInfo_open0(0, 0, tBuf);

							}

						}

						//				
						myDeleteMediaType(pmt);
					}
				}
#endif

				//
				myChkFmt_v(m_pVSC, pBih_suggested, bMatched_v, mt_matched_v);

				//  2009/04/10
				if (m_pVSC) {
					AM_MEDIA_TYPE* pmt;
					hr = m_pVSC->GetFormat(&pmt);
					if (SUCCEEDED(hr)) {
						TCHAR		tBuf_type[256] = _T("");
						TCHAR		tBuf_subType[256] = _T("");

						safeTcsnCpy(getMediaSubtypeName(pmt->subtype), tBuf_subType, mycountof(tBuf_subType));
#ifdef  __DEBUG__
						traceLog((TCHAR*)_T("initVideoCapDev_dx: output %s"), getMediaSubtypeName(pmt->subtype));
#endif
						if (!tBuf_subType[0])
						{
							StringFromGUID2(pmt->majortype, tBuf_type, mycountof(tBuf_type));
							StringFromGUID2(pmt->subtype, tBuf_subType, mycountof(tBuf_subType));
						}
						if (tBuf_type[0]) {
							qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("Video capture: output type %s"), tBuf_type);
						}
						qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("Video capture: output %s"), tBuf_subType);

						if (bSubtypeGrabbable(pmt->subtype))  bConnectDirectly = TRUE;

#if  0
						if (pmt->subtype == MEDIASUBTYPE_MJPG) {
							//  CLSID_MjpegDec
							hr = CoCreateInstance(CLSID_MjpegDec, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&p->m_captureGraphBuilder.m_pDecFilter);
							if (FAILED(hr))  goto  errLabel;
							hr = p->m_captureGraphBuilder.m_pGB->AddFilter(p->m_captureGraphBuilder.m_pDecFilter, _T("mjpeg decoder"));
							if (FAILED(hr))  goto  errLabel;
						}
#endif
						myDeleteMediaType(pmt);
					}
				}

				//
#ifndef  __SUPPORT_CUS_sampleGrabber__
				hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&p->video.m_pGrabberFilter);
				if (FAILED(hr))  goto  errLabel;
#else
				if (myGetNewFilter(g_pEnv, CLSID_SampleGrabber_is, 0, (void**)&p->video.m_pGrabberFilter)) {
#ifdef  __DEBUG__
					traceLog((TCHAR*)_T("initVideoCapDev_dx failed, myGetNewFilter, sampleGrabber_is failed"));
#endif
					goto  errLabel;
				}
#endif

				hr = m_pGB->AddFilter(p->video.m_pGrabberFilter, _T("Video Sample Grabber"));
				if (FAILED(hr))  goto  errLabel;

#ifndef  __SUPPORT_CUS_sampleGrabber__
				hr = p->video.m_pGrabberFilter->QueryInterface(IID_ISampleGrabber, (void**)&p->video.m_pGrabber);
				if (FAILED(hr))  goto  errLabel;
#else
				hr = p->video.m_pGrabberFilter->QueryInterface(IID_ISampleGrabber_is, (void**)&p->video.m_pGrabber);
				if (FAILED(hr))  goto  errLabel;
#endif

				if (bMatched_v) {
					hr = p->video.m_pGrabber->SetMediaType(&mt_matched_v);
				}
				else {
					DMO_MEDIA_TYPE	mt;
					memset(&mt, 0, sizeof(mt));
					mt.majortype = MEDIATYPE_Video;
#ifdef  __DEBUG__
					//  mt.subtype  =  MEDIASUBTYPE_MJPG;
#endif

					hr = p->video.m_pGrabber->SetMediaType(&mt);
				}
				if (FAILED(hr))  goto  errLabel;

#include	"unDeclareDebugNew.h"
				p->video.m_pCallBack = new  CMySampleGrabberCB;
#include	"declareDebugNew.h"
				if (!p->video.m_pCallBack)  goto  errLabel;

				//  set modes
				hr = p->video.m_pGrabber->SetBufferSamples(FALSE);
				if (FAILED(hr))  goto  errLabel;
				hr = p->video.m_pGrabber->SetCallback(p->video.m_pCallBack, 1);
				if (FAILED(hr))  goto  errLabel;

#ifndef  __SUPPORT_CUS_nullRenderer__
				hr = CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&p->video.m_pNullRenderer);
				if (FAILED(hr))  goto  errLabel;
#else
				if (myGetNewFilter(g_pEnv, CLSID_NullRenderer_is, 0, (void**)&p->video.m_pNullRenderer))  goto  errLabel;
#endif

				hr = m_pGB->AddFilter(p->video.m_pNullRenderer, L"Video Null  Renderer");
				if (FAILED(hr))  goto  errLabel;

				////////////////////  下面抓音频
				//
				if (p->bAudio) {

#ifndef  __SUPPORT_CUS_sampleGrabber__
					hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&p->audio.m_pGrabberFilter);
					if (FAILED(hr))  goto  errLabel;
#else
					if (myGetNewFilter(g_pEnv, CLSID_SampleGrabber_is, 0, (void**)&p->audio.m_pGrabberFilter)) {
#ifdef  __DEBUG__
						traceLog((TCHAR*)_T("initVideoCapDev_dx failed, myGetNewFilter, sampleGrabber_is failed"));
#endif
						goto  errLabel;
					}
#endif

					hr = m_pGB->AddFilter(p->audio.m_pGrabberFilter, _T("Audio Sample Grabber"));
					if (FAILED(hr))  goto  errLabel;

#ifndef  __SUPPORT_CUS_sampleGrabber__
					hr = p->audio.m_pGrabberFilter->QueryInterface(IID_ISampleGrabber, (void**)&p->audio.m_pGrabber);
					if (FAILED(hr))  goto  errLabel;
#else
					hr = p->audio.m_pGrabberFilter->QueryInterface(IID_ISampleGrabber_is, (void**)&p->audio.m_pGrabber);
					if (FAILED(hr))  goto  errLabel;
#endif

					if (bMatched_a) {
						hr = p->audio.m_pGrabber->SetMediaType(&mt_matched_a);
					}
					else {
						DMO_MEDIA_TYPE	mt;

						ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
						mt.majortype = MEDIATYPE_Audio;
						mt.subtype = MEDIASUBTYPE_PCM;

						hr = p->audio.m_pGrabber->SetMediaType(&mt);
					}
					if (FAILED(hr))  goto  errLabel;

#include	"unDeclareDebugNew.h"
					p->audio.m_pCallBack = new  CMySampleGrabberCB;
#include	"declareDebugNew.h"
					if (!p->audio.m_pCallBack)  goto  errLabel;

					//  set modes
					hr = p->audio.m_pGrabber->SetBufferSamples(FALSE);
					if (FAILED(hr))  goto  errLabel;
					hr = p->audio.m_pGrabber->SetCallback(p->audio.m_pCallBack, 1);
					if (FAILED(hr))  goto  errLabel;

#ifndef  __SUPPORT_CUS_nullRenderer__
					hr = CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&p->audio.m_pNullRenderer);
					if (FAILED(hr))  goto  errLabel;
#else
					if (myGetNewFilter(g_pEnv, CLSID_NullRenderer_is, 0, (void**)&p->audio.m_pNullRenderer))  goto  errLabel;
#endif

					hr = m_pGB->AddFilter(p->audio.m_pNullRenderer, L"Audio Null  Renderer");
					if (FAILED(hr))  goto  errLabel;

				}

				////////////////////
				{

					const GUID* pCategory = &PIN_CATEGORY_CAPTURE;
					hr = m_pCapture->RenderStream(pCategory, &MEDIATYPE_Interleaved, m_pBF_v, m_pDecFilter, p->video.m_pGrabberFilter);
					if (hr != S_OK) {
						hr = m_pCapture->RenderStream(pCategory, &MEDIATYPE_Video, m_pBF_v, m_pDecFilter, p->video.m_pGrabberFilter);
						if (hr != S_OK) {
							traceLogA((char*)"Can¡¯t build the graph");
							goto  errLabel;
						}
					}
					//
					if (p->bAudio) {

						hr = m_pCapture->RenderStream(pCategory, &MEDIATYPE_Audio, gcap.pACap, NULL, p->audio.m_pGrabberFilter);
						if (hr != S_OK) {
							traceLogA((char*)"Can¡¯t build the graph");
							goto  errLabel;
						}

					}

					//
					hr = m_pCapture->RenderStream(NULL, NULL, p->video.m_pGrabberFilter, NULL, p->video.m_pNullRenderer);
					if (FAILED(hr)) {
						traceLogA((char*)"Can¡¯t build the graph");
						goto  errLabel;
					}

					if (p->bAudio) {
						hr = m_pCapture->RenderStream(NULL, NULL, p->audio.m_pGrabberFilter, NULL, p->audio.m_pNullRenderer);
						if (FAILED(hr)) {
							traceLogA((char*)"Can¡¯t build the graph");
							goto  errLabel;
						}
					}

				}


#if  0
				AM_MEDIA_TYPE* pmt = 0;

				if (!gcap.fMPEG2)
				{
					hr = gcap.fUseFrameRate ? E_FAIL : NOERROR;
					if (gcap.pVSC && gcap.fUseFrameRate)
					{
						hr = gcap.pVSC->GetFormat(&pmt);

						// DV capture does not use a VIDEOINFOHEADER
						if (hr == NOERROR)
						{
							if (pmt->formattype == FORMAT_VideoInfo)
							{
								VIDEOINFOHEADER* pvi = (VIDEOINFOHEADER*)pmt->pbFormat;
								pvi->AvgTimePerFrame = (LONGLONG)(10000000 / gcap.FrameRate);
								hr = gcap.pVSC->SetFormat(pmt);
							}
							myDeleteMediaType(pmt);
						}
					}
					if (hr != NOERROR)
						ErrMsg_amCap(TEXT("Cannot set frame rate for capture"));
				}
#endif


				//
				if (IsWindow(hWnd_notify)) {
					if (!gcap.pME) {
						hr = gcap.pFg->QueryInterface(IID_IMediaEventEx, (void**)&gcap.pME);
						if (hr != NOERROR)  goto  errLabel;
					}

					// Have the graph signal event via window callbacks		
					hr = gcap.pME->SetNotifyWindow((OAHWND)hWnd_notify, CONST_qyWm_graphNotify_mediaDevice, lInstanceData);
				}


				// All done.
				gcap.fCaptureGraphBuilt = TRUE;


#ifdef  __DEBUG__
				myDumpGraph(gcap.pFg, 6);
#endif
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("Video capture: graph is ok"));

			}

		}
#endif

	}

	//
	p->bInited  =  TRUE;

	iErr  =  0;

errLabel:

	myFreeMediaType(  mt_matched_a  );
	myFreeMediaType(  mt_matched_v  );

	MACRO_safeRelease(  pMoniker_a  );
	MACRO_safeRelease(  pMoniker_v  );


	if  (  iErr  )  {
		exitShareMediaDevice(  (  void  **  )&p  );
	}
	if  (  !iErr  )  {
		*ppShareMediaDeviceParam  =  p;
	}

	 return  iErr;
 }

 int  exitShareMediaDevice(  void  **  ppShareMediaDeviceParam  )
 {
	HRESULT					hr;
	SHARE_MEDIA_DEVICE	*	p		=	(  SHARE_MEDIA_DEVICE  *  )*ppShareMediaDeviceParam;
	if  (  !p  )  return  -1;

	traceLogA(  (char*)  "exitShareMediaDevice enters"  );

	stopShareMediaDevice(  p  );

	//
	CAP_STUFF_free(  p->p_gcap  );  p->p_gcap  =  NULL;

	//
	MACRO_safeRelease(  p->video.m_pGrabber  );
	MACRO_safeRelease(  p->video.m_pGrabberFilter  );
	if  (  p->video.m_pCallBack  )  {
		MACRO_safeFree(  p->video.m_pCallBack->m_var.pMsgBuf  );
		delete  p->video.m_pCallBack;
	}
	MACRO_safeRelease(  p->video.m_pNullRenderer  );

	MACRO_safeRelease(  p->audio.m_pGrabber  );
	MACRO_safeRelease(  p->audio.m_pGrabberFilter  );
	if  (  p->audio.m_pCallBack  )  {
		MACRO_safeFree(  p->audio.m_pCallBack->m_var.pMsgBuf  );
		delete  p->audio.m_pCallBack;
	}
	MACRO_safeRelease(  p->audio.m_pNullRenderer  );





	free(  p  );

	*ppShareMediaDeviceParam  =  NULL;

	traceLogA(  (char*)  "exitShareMediaDevice leaves"  );


	return  0;
 }

 BOOL  bGetCapturePara_shareMediaDevice(  MC_VAR_common  *  pProcInfo,  int  iIndex_capAudio,  int  iIndex_capBmp,  void  *  pShareMediaDevice,  WAVEFORMATEX  *  pWf_org,  QY_VIDEO_HEADER  *  pVh_org,  SAMPLE_grabberCb_cache  *  pCache  )
{
	SHARE_MEDIA_DEVICE	*	p				=	(  SHARE_MEDIA_DEVICE  *  )pShareMediaDevice;
	SAMPLE_grabber_info  *  pA  =  NULL;
	SAMPLE_grabber_info  *  pV  =  NULL;

	if  (  p->bAudio  )  pA  =  &p->audio;
	if  (  p->bVideo  )  pV  =  &p->video;
	
	//  return  bGetCapturePara_shareMediaObj(  pProcInfo,  CONST_capType_mediaDevice,  iIndex_capAudio,  iIndex_capBmp,  pA,  pV,  pWf_org,  pVh_org,  pCache  );  
	return  bGetCapturePara_shareMediaObj(  pProcInfo,  CONST_capType_mediaDevice,  iIndex_capAudio,  0,  pA,  pWf_org,  iIndex_capBmp,  0,  pV,  pVh_org,  pCache  );
}


 int  runShareMediaDevice(  void  *  pShareMediaDeviceParam  )
{
	int						iErr	=	-1;
	SHARE_MEDIA_DEVICE	*	p		=	(  SHARE_MEDIA_DEVICE  *  )pShareMediaDeviceParam;
	
	if  (  !p  )  return  -1;
	if  (  !p->bInited  )  return  -1;

	AV_capStuff  &  gcap  =  *(  AV_capStuff  *  )p->p_gcap;

	// run the graph
    IMediaControl *pMC = NULL;
    HRESULT hr = gcap.pFg->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if(SUCCEEDED(hr))
    {
        hr = pMC->Run();
        if(FAILED(hr))
        {
			TCHAR	tBuf[128]	=	_T(  ""  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "startCapture_dx,IMediaControl.run failed,hr 0x%x"  ),  hr  );
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "%s"  ),  tBuf  );
			#endif
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Cap, run failed, 0x%x"  ),  hr  );
			showNotification(  NULL,  NULL,  NULL,  0,  0,  0,  tBuf  );

            // stop parts that ran
            pMC->Stop();
        }
        pMC->Release();
    }
    if(FAILED(hr))
    {
        //  ErrMsg(TEXT("Error %x: Cannot run preview graph"), hr);
		goto  errLabel;
    }


	iErr  =  0;
errLabel:
	return  iErr;
}


 int  stopShareMediaDevice(  void  *  pShareMediaDeviceParam  )
 {
	 	int						iErr	=	-1;
	SHARE_MEDIA_DEVICE	*	p		=	(  SHARE_MEDIA_DEVICE  *  )pShareMediaDeviceParam;
	
	if  (  !p  )  return  -1;
	if  (  !p->bInited  )  return  -1;

	AV_capStuff  &  gcap  =  *(  AV_capStuff  *  )p->p_gcap;


	 // stop the graph
    IMediaControl *pMC = NULL;
    HRESULT hr = gcap.pFg->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if(SUCCEEDED(hr))
    {
        hr = pMC->Stop();
        pMC->Release();
    }
    if(FAILED(hr))
    {
        //  ErrMsg(TEXT("Error %x: Cannot stop preview graph"), hr);
		goto  errLabel;
    }

	iErr  =  0;
errLabel:
	 return  iErr;
 }


  int  handleGraphEvent_mediaDevice(  void  *  pShareMediaDeviceParam  )
{
	SHARE_MEDIA_DEVICE	*	p		=	(  SHARE_MEDIA_DEVICE  *  )pShareMediaDeviceParam;
	
	if  (  !p  )  return  -1;
	if  (  !p->bInited  )  return  -1;

	AV_capStuff  &  gcap  =  *(  AV_capStuff  *  )p->p_gcap;

	if  (  gcap.pME  )  
	{
                LONG event;
				LONG_PTR l1, l2;
                HRESULT hrAbort = S_OK;
                BOOL bAbort = FALSE;
                while(gcap.pME->GetEvent(&event, &l1, &l2, 0) == S_OK)
                {
                    gcap.pME->FreeEventParams(event, l1, l2);
					
					//  2014/08/01
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  "graphEvent_mDevice"  ),  _T(  ""  ),  _T(  "event %d"  ),  event  );
					
					//
                    if(event == EC_ERRORABORT)
                    {
                        StopCapture(  gcap  );
                        bAbort = TRUE;
                        hrAbort = static_cast<HRESULT>(l1);
                        continue;
                    }
                    else if(event == EC_DEVICE_LOST)
                    {
                            // Check if we have lost a capture filter being used.
                            // lParam2 of EC_DEVICE_LOST event == 1 indicates device added
                            //                                 == 0 indicates device removed
                            if(l2 == 0)
                            {
                                IBaseFilter *pf;
                                IUnknown *punk = (IUnknown *) l1;
                                if(S_OK == punk->QueryInterface(IID_IBaseFilter, (void **) &pf))
                                {
#if  0
                                    if(AreComObjectsEqual(gcap.pVCap, pf))
                                    {
                                        pf->Release();
                                        bAbort = FALSE;
                                        StopCapture();
                                        TCHAR szError[100];
                                        HRESULT hr = StringCchCopy(szError, 100,
                                            TEXT("Stopping Capture (Device Lost). Select New Capture Device\0"));
                                        ErrMsg(szError);
                                        break;
                                    }
#endif
                                    pf->Release();
									StopCapture(  gcap  );	//  2014/08/01
                                }
                            }
                    }



                } // end while
                if(bAbort)
                {
					#if  0
                        if(gcap.fWantPreview)
                        {
                            BuildPreviewGraph();
                            StartPreview();
                        }
                        TCHAR szError[100];
                        HRESULT hr = StringCchPrintf(szError, 100, TEXT("ERROR during capture, error code=%08x\0"), hrAbort);
                        ErrMsg(szError);
					#endif
                }
            }

	return  0;
}


  #ifdef  __isCli__
  LRESULT mainWnd_OnQyGraphNotify_mediaDevice(  QY_MC  *  pQyMc,  HWND  hMainWnd,  void  *  pVar,  WPARAM  wParam,  LPARAM  lParam  )
{
	int						iErr			=	-1;
	if  (  !pVar  )  return  -1;
	QY_MC_mainWndVar  &  var			=	*(  QY_MC_mainWndVar  *  )pVar;


	//QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	if (!pQyMc) return  -1;
	MC_VAR_isCli			*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	int						iIndex_sharedObj	=	(  int  )lParam;
	int						iIndex_capBmp		=	0;
	int						iIndex_capAudio		=	0;		//  2013/03/19

	QY_SHARED_OBJ		*	pSharedObj	=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;

	switch  (  pSharedObj->uiType1  )  {
			case  CONST_sharedObjType_av:
			case  CONST_sharedObjType_mediaDevice:
				  handleGraphEvent_mediaDevice(  pSharedObj->pShareMediaObj  );
				  break;
			default:  {
				      iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
					  CAP_procInfo_bmpCommon  *  pCapBmp  =  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
					  if  (  pCapBmp->uiType  ==  CONST_capType_av  )  {
						  CAP_procInfo_video  *  pVc  =  (  CAP_procInfo_video  *  )pCapBmp;
						  if  (  pVc->uiCamCapType  ==  CONST_camCapType_directX  )  {

							  handleGraphEvent_videoCapDev_dx(  pVc->capDev.pVideoCapDev  );
						  
						  }					  
					  }
					  //
					  iIndex_capAudio  =  pSharedObj->iIndex_capAudio;
					  CAP_procInfo_audioCommon  *  pCapAudio  =  (  CAP_procInfo_audioCommon  *  )getCapAudioBySth(  pProcInfo,  iIndex_capAudio,  0  );
					  if  (  pCapAudio  )  {
						  if  (  pCapAudio->uiType  ==  CONST_capType_av  )  {
							  CAP_procInfo_recordSound  *  pRecordSound  =  (  CAP_procInfo_recordSound  *  )pCapAudio;
							  if  (  pRecordSound->uiRecordType  ==  CONST_recordType_directX  )  {
								  handleGraphEvent_audioCapDev_dx(  pRecordSound->u.dx.pAudioCapDev  );
							  }
						  }
					  }
					  }
					  break;
	}


	iErr  =  0;
errLabel:

	return  0;
}
#endif
