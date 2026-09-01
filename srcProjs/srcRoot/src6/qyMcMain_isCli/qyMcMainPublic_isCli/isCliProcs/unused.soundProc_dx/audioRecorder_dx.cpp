
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
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
#include	<dsound.h>

#include	"qmcDmoPublic.h"

#include	"qmcVideoCapture_dx.h"

#include	"myfourcc.h"
#include	"mywmcodecconst.h"

#include	"qmcCmdProc.h"

#include	"cPropertyBag.h"

#include	"qyCusResTemp.h"
#include	"qmcDirectX.h"

//  #include	"myresource.h"
#ifdef  __SUPPORT_CUS_sampleGrabber__
		#include	"qySampleGrabberPublic.h"
#endif

#include	"myresource.h"
#include	"qmcShareMediaDevice.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qmcCommFunc_isCli.h"

//
 int  printDmoMediaType(  int  index,  DMO_MEDIA_TYPE  *  pMt  );


#if  10
 int  myChkFmt_a_mediaDevice(  IAMStreamConfig  *  m_pASC,  WAVEFORMATEX  *  pWf_suggested,  BOOL  &  bMatched,  AM_MEDIA_TYPE  &  mt_matched  )
{
	int					iErr		=	-1;
	BOOL				bNeedSet	=	TRUE;
	HRESULT				hr;

	if  (  m_pASC  )  {
		AM_MEDIA_TYPE	*	pmt;

		hr  =  m_pASC->GetFormat(  &pmt  );
		if  (  SUCCEEDED(  hr  )  )  {

			traceLog((TCHAR*)  _T(  "subtype %s"  ),  getMediaSubtypeName(  pmt->subtype  )  );

			if  (  pmt->majortype  ==  MEDIATYPE_Audio
				&&  pmt->formattype  ==  FORMAT_WaveFormatEx
					&&  pmt->cbFormat  >=  sizeof(  WAVEFORMATEX  )  
						&&  pmt->pbFormat  )
			{
				WAVEFORMATEX  *  pWf  =  (  WAVEFORMATEX  *  )pmt->pbFormat;
				if  (
					#if  0
						pmt->subtype  ==  MEDIASUBTYPE_YUY2  
					||  pmt->subtype  ==  MEDIASUBTYPE_MJPG  
					||  pmt->subtype  ==  MEDIASUBTYPE_YV12
					||  pmt->subtype  ==  WMCMEDIASUBTYPE_I420
					||  pmt->subtype  ==  MEDIASUBTYPE_RGB565
					||  pVih->bmiHeader.biCompression  ==  BI_RGB  
					#endif
					//  bSubtypeGrabbable(  pmt->subtype  )
					pmt->subtype  ==  MEDIASUBTYPE_PCM
					)  
				{
					if  (  pWf_suggested  &&  pWf_suggested->wFormatTag  &&  pWf_suggested->nChannels  )  {
						BOOL  bMatched_biCompression  =  TRUE;

						if  (  bMatched_biCompression  )  {
							if  (  pWf->wFormatTag  ==  pWf_suggested->wFormatTag
								//  &&  pWf->wBitsPerSample  ==  pWf_suggested->wBitsPerSample  
								&&  pWf->nSamplesPerSec  ==  pWf_suggested->nSamplesPerSec
								&&  pWf->nChannels  ==  pWf_suggested->nChannels
								//  &&  pWf->nBlockAlign  ==  pWf_suggested->nBlockAlign
								//  &&  pWf->nAvgBytesPerSec  ==  pWf_suggested->nAvgBytesPerSec  
								) 							
							{
									bNeedSet  =  FALSE;											
							}
							}
						}						
					else  
						bNeedSet  =  FALSE;
				}
			}
			myDeleteMediaType(  pmt  );
		}		
	}

	//
	if  (  m_pASC  )  {
		TCHAR  *  pT  =  (TCHAR*)(bNeedSet  ?  _T(  "myChkFmt_a: org fmt needs to be set"  )  :  _T(  "myChkFmt_a: org fmt don't need to be set"  ));
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  pT  );
	}
	
	//
	if  (  bNeedSet  &&  m_pASC  )  {
		int		iCount  =  0,  iSize  =  0;
		int		i;

		traceLogA(  (char*)  "initAudioCapDev_dx: need to set capture audio"  );

		hr  =  m_pASC->GetNumberOfCapabilities(  &iCount,  &iSize  );
		if  (  SUCCEEDED(  hr  )  )  {
			AUDIO_STREAM_CONFIG_CAPS		scc;
			AM_MEDIA_TYPE				*	pmtConfig;
			for  (  i  =  0;  i  <  iCount  &&  bNeedSet;  i  ++  )  {
				hr  =  m_pASC->GetStreamCaps(  i,  &pmtConfig,  (  BYTE  *  )&scc  );
				if  (  SUCCEEDED(  hr  )  )  {
					//  pmtcon
					printDmoMediaType(  i,  pmtConfig  );

					if  (  pmtConfig->majortype  ==  MEDIATYPE_Audio
						&&  pmtConfig->formattype  ==  FORMAT_WaveFormatEx
							&&	pmtConfig->cbFormat  >=  sizeof(  WAVEFORMATEX  )
								&&  pmtConfig->pbFormat  )				
					{
						WAVEFORMATEX	*	pWf	=	(  WAVEFORMATEX  *  )pmtConfig->pbFormat;
						BOOL				bOk		=	FALSE;

						//  2013/03/21
						MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
						TCHAR	tDesc[256]  =  _T(  ""  );
						if  (  pProcInfo  )  {
							if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_a_mt  )  {
								_sntprintf(  tDesc,  mycountof(  tDesc  ),  _T(  "fmt 0x%x, nChan %d,nSamp %d,nAvg %d,wBits %d,nBlock %d."  ),  pWf->wFormatTag,  pWf->nChannels,  pWf->nSamplesPerSec,  pWf->nAvgBytesPerSec,  pWf->wBitsPerSample,  pWf->nBlockAlign  );

								qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "myChkFmt_a: %s"  ),  tDesc  );
							}
						}

						//
						if  (  
							#if  0
								pmtConfig->subtype  ==  MEDIASUBTYPE_YUY2  
							||  pmtConfig->subtype  ==  MEDIASUBTYPE_MJPG 
							||  pmtConfig->subtype  ==  MEDIASUBTYPE_YV12
							||  pmtConfig->subtype  ==  WMCMEDIASUBTYPE_I420
							||  pmtConfig->subtype  ==  MEDIASUBTYPE_RGB565
							||  pvih->bmiHeader.biCompression  ==  BI_RGB  
							#endif
							//  bSubtypeGrabbable(  pmtConfig->subtype  )
							pmtConfig->subtype  ==  MEDIASUBTYPE_PCM
							)  
						{
							if  (  pWf_suggested  &&  pWf_suggested->wFormatTag  &&  pWf_suggested->nChannels  )  {
								BOOL  bMatched_biCompression  =  TRUE;
								
								if  (  bMatched_biCompression  )  {
									if  (  pWf->wFormatTag  ==  pWf_suggested->wFormatTag
										//  &&  pWf->wBitsPerSample  ==  pWf_suggested->wBitsPerSample  
										&&  pWf->nSamplesPerSec  ==  pWf_suggested->nSamplesPerSec
										&&  pWf->nChannels  ==  pWf_suggested->nChannels
										//  &&  pWf->nBlockAlign  ==  pWf_suggested->nBlockAlign
										//  &&  pWf->nAvgBytesPerSec  ==  pWf_suggested->nAvgBytesPerSec  
										) 														
									{
										bOk  =  TRUE;
									}
								}
								}
							else							
								bOk  =  TRUE;
						}

						if  (  bOk  )  {
							#if  1  //  ndef  __DEBUG__
									 hr  =  m_pASC->SetFormat(  pmtConfig  );	
							#endif

							//  2011/09/02. 将选中的类型从此函数中带出，方便sampleGrabber设置
							bMatched  =  TRUE;								//  
							myCopyMediaType(  &mt_matched,  pmtConfig  );

							//
							#ifdef  __DEBUG__
									char  fourccStr[16]	=	"";
									//  iFourcc2Str(  pvih->bmiHeader.biCompression,  fourccStr,  mycountof(  fourccStr  )  );
									if  (  FAILED(  hr  )  )  {  
										traceLogA(  (char*)  "initAudioCapDev_dx: SetFormat failed, hr %x. ",  hr  );
										}
									else  
										traceLogA(  (char*)  "initAudioCapDev_dx: cap audio is set. "  );
							#endif
							//
							_sntprintf(  tDesc,  mycountof(  tDesc  ),  _T(  "fmt 0x%x, nChan %d,nSamp %d,nAvg %d,wBits %d,nBlock %d."  ),  pWf->wFormatTag,  pWf->nChannels,  pWf->nSamplesPerSec,  pWf->nAvgBytesPerSec,  pWf->wBitsPerSample,  pWf->nBlockAlign  );
							qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "myChkFmt_a: setFmt, hr 0x%x. %s"  ),  hr,  tDesc  );
							//
							bNeedSet  =  FALSE;
						}
					}					
					myDeleteMediaType(  pmtConfig  );
				}
			}
		}
	}

	iErr  =  0;

	return  iErr;
}
#else
 int  myChkFmt_a_mediaDevice(  IAMStreamConfig  *  m_pASC,  WAVEFORMATEX  *  pWf_suggested,  BOOL  &  bMatched,  AM_MEDIA_TYPE  &  mt_matched  )
 {
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "Not supported: myChkFmt_a"  )  );
#endif
		return  -1;
 }
#endif

 //  2014/05/24
  int  myChkFmt_a_dx(  IAMStreamConfig  *  m_pASC,  WAVEFORMATEX  *  pWf_suggested,  BOOL  &  bMatched,  AM_MEDIA_TYPE  &  mt_matched  )
 {
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "Not supported: myChkFmt_a_dx"  )  );
#endif
		return  -1;
 }



 int  initAudioCapDev_dx(  void  *  p_reserved,  LPCTSTR  displayName_selected,  void  **  ppCapStuff,  AUDIO_COMPRESSOR_CFG  *  pCompressor,  BOOL  bForConfig,  HWND hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppAudioCapDevParam  )
{
	int								iErr	=	-1;
	HRESULT							hr;
	AUDIO_capDev_dx				*	p		=	NULL;

	IMoniker					*	pMoniker_a	=	NULL;

	BOOL							bMatched_a  =  FALSE;
	AM_MEDIA_TYPE					mt_matched_a;
	memset(  &mt_matched_a,  0,  sizeof(  mt_matched_a  )  );

	
	if  (  !ppAudioCapDevParam  )  return  -1;
	if  (  *ppAudioCapDevParam  )  return  -1;
	if  (  !pCompressor  )  return  -1;


	WAVEFORMATEX  *  pWf_suggested  =  &pCompressor->wf_decompress_default;

	p  =  (  AUDIO_capDev_dx  *  )mymalloc(  sizeof(  AUDIO_capDev_dx  )  );
	if  (  !p  )  goto  errLabel;
	memset(  p,  0,  sizeof(  AUDIO_capDev_dx  )  );
	

	if  (  getMonikerByDisplayName(  displayName_selected,  (  void  **  )&pMoniker_a  )
			||  !pMoniker_a  )  
		{
			traceLogA(  (char*)  "initAudioCapDev_dx failed:  pMoniker null"  );
			goto  errLabel;		 
		}

	//
	MC_VAR_isCli* pProcInfo; pProcInfo = QY_GET_procInfo_isCli();
	if  (  bRecorderUsing(  pProcInfo,  pMoniker_a,  NULL,  NULL  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initAudioCapDev_dx failed, audio device is being used"  )  );
		showNotification(  NULL,  NULL,  NULL,  0,  0,  0,  _T(  "Failed: audio device is used"  )  );
		goto  errLabel;  
	}

	//
	if  (  initCaptureGraphBuilder(  &p->m_captureGraphBuilder,  NULL  )  )  goto  errLabel;
			
	//	
	hr = pMoniker_a->BindToObject(0, 0, IID_IBaseFilter, (void**)&p->m_captureGraphBuilder.m_pBF);
	if  (  FAILED(  hr  )  )  goto  errLabel;
	
	//
	IGraphBuilder* m_pGB; m_pGB = p->m_captureGraphBuilder.m_pGB;
	IBaseFilter* m_pBF; m_pBF = p->m_captureGraphBuilder.m_pBF;
	ICaptureGraphBuilder2* m_pCapture; m_pCapture = p->m_captureGraphBuilder.m_pCapture;

	//		
	hr  =  m_pGB->AddFilter(  m_pBF,  _T(  "Audio Source"  )  );		
	if  (  FAILED(  hr  )  )  goto  errLabel;


	//  chk format
	hr = m_pCapture->FindInterface(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Audio, m_pBF,
                                      IID_IAMStreamConfig, (void **)&p->m_captureGraphBuilder.m_pASC);

    if  (  hr != NOERROR  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initAudioCapDev_dx failed, Cannot find ACapture:IAMStreamConfig"));
    }
	
	//
	if  (  p->m_captureGraphBuilder.m_pASC  )  {
		//
		myChkFmt_a_dx(  p->m_captureGraphBuilder.m_pASC,  pWf_suggested,  bMatched_a,  mt_matched_a  );
	
		//	
		AM_MEDIA_TYPE	*	pmt;	
		hr  =  p->m_captureGraphBuilder.m_pASC->GetFormat(  &pmt  );
		if  (  SUCCEEDED(  hr  )  )  {
			
			if  (  pmt->majortype  ==  MEDIATYPE_Audio
				&&  pmt->formattype  ==  FORMAT_WaveFormatEx
					&&  pmt->cbFormat  >=  sizeof(  WAVEFORMATEX  )  
						&&  pmt->pbFormat  )
			{
				WAVEFORMATEX  *  pWf  =  (  WAVEFORMATEX  *  )pmt->pbFormat;
						
				unsigned  int  uiBytesRecorded_perBlockAlign  =  MACRO_getuiBytesRecorded_perBlockAlign(  *pCompressor,  pWf  );
				//			
				IAMBufferNegotiation  *  pNeg  =  NULL;

				hr  =  m_pCapture->FindInterface(  &PIN_CATEGORY_CAPTURE, &MEDIATYPE_Audio, m_pBF,  IID_IAMBufferNegotiation,  (  void  **  )&pNeg  );
				if  (  SUCCEEDED(  hr  )  )  {
					ALLOCATOR_PROPERTIES AllocProp  =  {0};
					
					AllocProp.cbAlign = -1;  // -1 means no preference.
					AllocProp.cbBuffer = uiBytesRecorded_perBlockAlign  *  pWf->nBlockAlign;	//  dwBytesPerSec *  dwLatencyInMilliseconds / 1000;
					AllocProp.cbPrefix = -1;
					AllocProp.cBuffers = -1;
					//
					hr  =  pNeg->SuggestAllocatorProperties(&AllocProp);
				
					pNeg->Release(  );				
				}

				//
				myDeleteMediaType(  pmt  );
			}
		}
	}
			
		////////////////////  下面抓音频
		//
#ifndef  __SUPPORT_CUS_sampleGrabber__
		hr  =  CoCreateInstance(  CLSID_SampleGrabber,  NULL,  CLSCTX_INPROC_SERVER,  IID_IBaseFilter,  (  void  **  )&p->audio.m_pGrabberFilter  );
		if  (  FAILED(  hr  )  )  goto  errLabel;
#else
		if  (  myGetNewFilter(  g_pEnv,  CLSID_SampleGrabber_is,  0,  (  void  **  )&p->audio.m_pGrabberFilter  )  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "initVideoCapDev_dx failed, myGetNewFilter, sampleGrabber_is failed"  )  );
			#endif
			goto  errLabel;
		}
#endif

		hr  =  m_pGB->AddFilter(  p->audio.m_pGrabberFilter,  _T(  "Audio Sample Grabber"  )  );
		if  (  FAILED(  hr  )  )  goto  errLabel;

#ifndef  __SUPPORT_CUS_sampleGrabber__
		hr  =  p->audio.m_pGrabberFilter->QueryInterface(  IID_ISampleGrabber,  (  void  **  )&p->audio.m_pGrabber  );
		if  (  FAILED(  hr  )  )  goto  errLabel;
#else
		hr  =  p->audio.m_pGrabberFilter->QueryInterface(  IID_ISampleGrabber_is,  (  void  **  )&p->audio.m_pGrabber  );
		if  (  FAILED(  hr  )  )  goto  errLabel;
#endif

		if  (  bMatched_a  )  {
			hr  =  p->audio.m_pGrabber->SetMediaType(  &mt_matched_a  );
			}
		else  {			
			  DMO_MEDIA_TYPE	mt;

			  ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
			  mt.majortype  =  MEDIATYPE_Audio;
			  mt.subtype = MEDIASUBTYPE_PCM; 

			  hr  =  p->audio.m_pGrabber->SetMediaType(  &mt  );
		}
		if  (  FAILED(  hr  )  )  goto  errLabel;

#include	"undeclareDebugNew.h"
		p->audio.m_pCallBack  =  new  CMySampleGrabberCB;
#include	"declareDebugNew.h"
		if  (  !p->audio.m_pCallBack  )  goto  errLabel;
	
		//  set modes
		hr  =  p->audio.m_pGrabber->SetBufferSamples(  FALSE  );
		if  (  FAILED(  hr  )  )  goto  errLabel;
		hr  =  p->audio.m_pGrabber->SetCallback(  p->audio.m_pCallBack,  1  );
		if  (  FAILED(  hr  )  )  goto  errLabel;

#ifndef  __SUPPORT_CUS_nullRenderer__
		hr  =  CoCreateInstance(  CLSID_NullRenderer,  NULL,  CLSCTX_INPROC_SERVER,  IID_IBaseFilter,  (  void  **  )&p->audio.m_pNullRenderer  );
		if  (  FAILED(  hr  )  )  goto  errLabel;
#else
		if  (  myGetNewFilter(  g_pEnv,  CLSID_NullRenderer_is,  0,  (  void  **  )&p->audio.m_pNullRenderer  )  )  goto  errLabel;
#endif

		hr  =  m_pGB->AddFilter(  p->audio.m_pNullRenderer,  L"Audio Null  Renderer"  );
		if  (  FAILED(  hr  )  )  goto  errLabel;

		////////////////////
		{

			  const GUID *pCategory  =  &PIN_CATEGORY_CAPTURE;
			  //
			  hr  =  m_pCapture->RenderStream( pCategory, &MEDIATYPE_Audio, p->m_captureGraphBuilder.m_pBF, NULL, p->audio.m_pGrabberFilter );
			  if  (  hr != S_OK  )  {
				  traceLogA(  (char*)  "Can¡¯t build the graph"  );  
				  goto  errLabel;				  
			  }

			  hr  =  m_pCapture->RenderStream( NULL, NULL, p->audio.m_pGrabberFilter, NULL, p->audio.m_pNullRenderer  );
			  if( FAILED( hr ) )  {
				  traceLogA(  (char*)  "Can¡¯t build the graph"  );  
				  goto  errLabel;
			  }

		}

		//
		#ifdef  __DEBUG__
		//  myDumpGraph(  p->m_pGB,  6  );
		#endif

	//	
	//  M_setMyStep(  pDebugStep,  40  );


	//
	p->audio.m_pCallBack->m_var.pProcInfo  =  (  MC_VAR_common  *  )pProcInfo;
	//  p->audio.m_pCallBack->m_var.pDmoInfo  =  pDmoInfo;


	//	
	if  (  IsWindow(  hWnd_notify  )  )  {
		if  (  !p->m_captureGraphBuilder.m_pME  )  {
			hr = p->m_captureGraphBuilder.m_pGB->QueryInterface(IID_IMediaEventEx, (void **)&p->m_captureGraphBuilder.m_pME);
				if(hr != NOERROR)  goto  errLabel;
			}

			// Have the graph signal event via window callbacks		
			hr = p->m_captureGraphBuilder.m_pME->SetNotifyWindow(  (OAHWND)hWnd_notify, CONST_qyWm_graphNotify_mediaDevice, lInstanceData  );	
	}


	//	
	p->bInited  =  TRUE;
	
	iErr  =  0;

errLabel:
	
	myFreeMediaType(  mt_matched_a  );

	MACRO_safeRelease(  pMoniker_a  );
	

	if  (  iErr  )  {
		exitAudioCapDev_dx(  (  void  **  )&p  );
	}
	if  (  !iErr  )  {
		*ppAudioCapDevParam  =  p;
	}


	 return  iErr;
}


#if  10	//  2011/09/01
 int  exitAudioCapDev_dx(  void  **  ppAudioCapDevParam  )
{
	AUDIO_capDev_dx  *  p;

	if  (  !ppAudioCapDevParam  )  return  0;
	if  (  !*ppAudioCapDevParam  )  return  0;

	p  =  (  AUDIO_capDev_dx  *  )*ppAudioCapDevParam;
	
	//
	stopAudioCapDev_dx(  p  );

#if  0
	p->bQuit  =  TRUE;
	if  (  p->pQ2  &&  p->bQInited  )  {
		q2PostMsgAndTrigger(  NULL,  0,  p->pQ2  );
	}
#endif

	//
	exitCaptureGraphBuilder(  &p->m_captureGraphBuilder,  NULL  );

	MACRO_safeRelease(  p->audio.m_pGrabber  );
	MACRO_safeRelease(  p->audio.m_pGrabberFilter  );
	if  (  p->audio.m_pCallBack  )  {
		MACRO_safeFree(  p->audio.m_pCallBack->m_var.pMsgBuf  );
		delete  p->audio.m_pCallBack;
	}

	MACRO_safeRelease(  p->audio.m_pNullRenderer  );


	free(  p  );
	*ppAudioCapDevParam  =  NULL;

	return  0;
}
#endif


  BOOL  bGetCapturePara_audioCapdev(  MC_VAR_common  *  pProcInfo,  int  iIndex_capAudio,  unsigned  int  uiBufSize_pMsgBuf,  void  *  pAudioCapDevParam,  WAVEFORMATEX  *  pWf_org,  SAMPLE_grabberCb_cache  *  pCache  )
{
	AUDIO_capDev_dx				*	p				=	(  AUDIO_capDev_dx  *  )pAudioCapDevParam;
	SAMPLE_grabber_info  *  pA  =  NULL;
	SAMPLE_grabber_info  *  pV  =  NULL;
	int						iIndex_capBmp  =  -1;


	//  if  (  !p->g_bNoAudio  )  pA  =  &p->audio;
	//  if  (  !p->g_bAudioOnly  )  pV  =  &p->video;
	pA  =  &p->audio;
	
	return  bGetCapturePara_shareMediaObj(  pProcInfo,  CONST_capType_av,  iIndex_capAudio,  sizeof(  MIS_MSGU  ),  pA,  pWf_org,  iIndex_capBmp,  0,  pV,  NULL,  pCache  );  
}

   int  startAudioCapDev_dx(  void  *  pAudioCapDevParam  )
{
	int						iErr	=	-1;
	HRESULT					hr;
	AUDIO_capDev_dx		*	p		=	(  AUDIO_capDev_dx  *  )pAudioCapDevParam;
	if  (  !p  )  return  -1;
	if  (  !p->bInited  )  return  -1;


	// run the graph
    IMediaControl *pMC = NULL;
	hr = p->m_captureGraphBuilder.m_pGB->QueryInterface(IID_IMediaControl, (void **)&pMC);
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
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Cap, run failed, 0x%x"  ),  hr  );
			showNotification(  NULL,  NULL,  NULL,  0,  0,  0,  tBuf  );

            // stop parts that ran
            pMC->Stop();
        }
        pMC->Release();
    }
    if(FAILED(hr))
    {
		goto  errLabel;
    }

	iErr  =  0;
errLabel:
	return  iErr;
}

  int  stopAudioCapDev_dx(  void  *  pAudioCapDevParam  )
 {
	 	int						iErr	=	-1;
	AUDIO_capDev_dx	*	p		=	(  AUDIO_capDev_dx  *  )pAudioCapDevParam;
	
	if  (  !p  )  return  -1;
	if  (  !p->bInited  )  return  -1;

	//  AV_capStuff  &  gcap  =  *(  AV_capStuff  *  )p->p_gcap;


	 // stop the graph
    IMediaControl *pMC = NULL;
	HRESULT hr = p->m_captureGraphBuilder.m_pGB->QueryInterface(IID_IMediaControl, (void **)&pMC);
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

 int  handleGraphEvent_audioCapDev_dx(  void  *  pAudioDevCapParam  )
{
	AUDIO_capDev_dx	*	p		=	(  AUDIO_capDev_dx  *  )pAudioDevCapParam;
	
	if  (  !p  )  return  -1;
	//  if  (  !p->bInited  )  return  -1;

	//  AV_capStuff  &  gcap  =  *(  AV_capStuff  *  )p->p_gcap;

	if  (  p->m_captureGraphBuilder.m_pME  )  
	{
                LONG event;
				LONG_PTR l1, l2;
                HRESULT hrAbort = S_OK;
                BOOL bAbort = FALSE;
                while(p->m_captureGraphBuilder.m_pME->GetEvent(&event, &l1, &l2, 0) == S_OK)
                {
                    p->m_captureGraphBuilder.m_pME->FreeEventParams(event, l1, l2);
					
					//  2014/08/01
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  "graphEvent_aCap"  ),  _T(  ""  ),  _T(  "event %d"  ),  event  );
					
					//
                    if(event == EC_ERRORABORT)
                    {
                        //  StopCapture(  gcap  );
						stopAudioCapDev_dx(  p  );
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
									stopAudioCapDev_dx(  p  );	//  2014/08/01

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
