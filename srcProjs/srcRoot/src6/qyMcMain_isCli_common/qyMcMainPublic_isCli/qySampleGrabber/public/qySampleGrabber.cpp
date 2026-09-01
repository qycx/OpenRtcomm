
#include	"stdafx.h"
#include	<tchar.h>
#include	<streams.h>
#include	<initguid.h>

#include	<dvdmedia.h>

#include	"qyCommon.h"
#include	"qysyncCommProc.h"
#include	"qySampleGrabberPublic.h"
#include	"qySampleGrabber.h"
#include	"qyNullRenderer.h"
#include	"qyVCam.h"
#ifndef  __WINCE__
	//  #include	"qyFilterNetSender.h"
#endif
#include	"mywmcodecconst.h"

//  #include	"Crossbar.h"		//  2011/09/02


#if  0
const AMOVIESETUP_MEDIATYPE sudPinTypes =
{
    &MEDIATYPE_NULL,            // Major type
    &MEDIASUBTYPE_NULL          // Minor type
};
#endif

const AMOVIESETUP_PIN sudPins[] =
{
	{
		L"Input",                   // Pin string name
		FALSE,                      // Is it rendered
		FALSE,                      // Is it an output
		FALSE,                      // Allowed none
		FALSE,                      // Likewise many
		&CLSID_NULL,                // Connects to filter
		L"",		                // Connects to pin
		0,                          // Number of types
		NULL		                // Pin information
	},
	{
		L"Output",                  // Pin string name
		FALSE,                      // Is it rendered
		TRUE,                       // Is it an output
		FALSE,                      // Allowed none
		FALSE,                      // Likewise many
		&CLSID_NULL,                // Connects to filter
		L"",		                // Connects to pin
		0,                          // Number of types
		NULL		                // Pin information
	},
};

const AMOVIESETUP_FILTER sudSampleGrabber =
{
    &CLSID_SampleGrabber_is,    // Filter CLSID
    CONST_FILTERNAME,           // String name
    MERIT_DO_NOT_USE,           // Filter merit
    2,                          // Number pins
    sudPins                    // Pin details
};


//
//  Object creation stuff
//
CFactoryTemplate g_Templates[]= {
    CONST_FILTERNAME, &CLSID_SampleGrabber_is, CSampleGrabber::CreateInstance, NULL, &sudSampleGrabber
};
int g_cTemplates = 1;


//

 int  getNewFilter(  REFCLSID  rclsid,  void  *  pParam,  void  **  ppIBaseFilter  )
{
	int					iErr			=	-1;
	CSampleGrabber	*	pGrabberF		=	NULL;
	CNullRenderer	*	pNullRenderer	=	NULL;
	QVCam			*	pVCam			=	NULL;
#ifndef  __WINCE__
	//  CFilterNetSender	*	pNetSender	=	NULL;
#endif
	HRESULT				hr;
	IBaseFilter		*	pFilter			=	NULL;
	
	if  (  rclsid  ==  CLSID_SampleGrabber_is  )  {
		pGrabberF  =  new  CSampleGrabber(  NULL,  &hr  );
		if  (  !pGrabberF  )  goto  errLabel;
		pGrabberF->AddRef(  );
	
		pFilter  =  pGrabberF;
		}
	else  if  (  rclsid  ==  CLSID_NullRenderer_is  )  {
			  pNullRenderer  =  new  CNullRenderer(  NULL,  &hr  );
			  if  (  !pNullRenderer  )  goto  errLabel;
			  pNullRenderer->AddRef(  );

			  pFilter  =  pNullRenderer;
			  }
	else  if  (  rclsid  ==  CLSID_VCam_is  )  {
			  pVCam  =  new  QVCam(  NULL,  &hr  );
			  if  (  !pVCam  )  goto  errLabel;

			  if  (  !pParam  )  goto  errLabel;
			  memcpy(  &pVCam->m_var.param,  pParam,  sizeof(  pVCam->m_var.param  )  );
			  if  (  !pVCam->m_var.param.pAmMediaType
				  ||  !pVCam->m_var.param.pbQuit
				  ||  !pVCam->m_var.param.pQ2
				  ||  !pVCam->m_var.param.pf_q2GetMsg
				  ||  !pVCam->m_var.param.uiBufSize_pPkt  )
			  {
				  goto  errLabel;
			  }

			  CMediaType		m_preferredMt;
			  QVCamStream	*	pPin  =  (  QVCamStream  *  )pVCam->GetPin(  0  );
			  	
#if  0
			  {			 
				  m_preferredMt.SetType(  &MEDIATYPE_Video  );
				  m_preferredMt.SetFormatType(  &FORMAT_VideoInfo  );
				  //
				  VIDEOINFOHEADER  *  pvi  =  (  VIDEOINFOHEADER  *  )pVCam->m_var.param.pbFormat;
				  const  GUID  subtype  =  GetBitmapSubtype(  &pvi->bmiHeader  );
				  m_preferredMt.SetSubtype(  &subtype  );

				  pvi->bmiHeader.biSizeImage  =  GetBitmapSize(  &pvi->bmiHeader  );
				  m_preferredMt.SetFormat(  (  BYTE  *  )pVCam->m_var.param.pbFormat,  pVCam->m_var.param.cbFormat  );
				  m_preferredMt.SetSampleSize(  pvi->bmiHeader.biSizeImage  );
			  }
			  m_preferredMt.SetTemporalCompression(  FALSE  );
#endif
			  m_preferredMt  =  *(  const  AM_MEDIA_TYPE  *  )pVCam->m_var.param.pAmMediaType;

			  hr  =  pPin->SetMediaType(  &m_preferredMt  );
			  if  (  FAILED(  hr  )  )  goto  errLabel;

			  pVCam->m_var.pPkt  =  (  char  *  )mymalloc(  pVCam->m_var.param.uiBufSize_pPkt  );
			  if  (  !pVCam->m_var.pPkt  )  goto  errLabel;


			  pVCam->AddRef(  );

			  pFilter  =  pVCam;
			  }
#if  0
	else  if  (  rclsid  ==  CLSID_NetSender_is  )  {
			  pNetSender  =  new  CFilterNetSender(  NULL,  &hr  );
			  if  (  !pNetSender  )  goto  errLabel;
			  pNetSender->AddRef(  );

			  pFilter  =  pNetSender;
			}
#endif
	else  {
		  OutputDebugString(  _T(  "getNewFilter failed: unknown clsid\n"  )  );
		  goto  errLabel;
	}

	
	*ppIBaseFilter  =  pFilter;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pGrabberF  )  delete  pGrabberF;
		if  (  pNullRenderer  )  delete  pNullRenderer;
		if  (  pVCam  )  delete  pVCam;
#ifndef  __WINCE__
		//  if  (  pNetSender  )  delete  pNetSender;
#endif
	}
	return  iErr;
}


//  2011/09/02
#if  0
void  *  newCrossBar(  void  *  pStartInputPinParam,  HRESULT  *  phr  )
{
	IPin  *  pStartingInputPin  =  (  IPin  *  )pStartInputPinParam;

	return  new  CCrossbar(  pStartingInputPin,  phr  );
}

void  freeCrossBar(  void  *  pCrossBarParam  )
{
	CCrossbar	*	pCrossBar  =  (  CCrossbar  *  )pCrossBarParam;

	if  (  pCrossBar  )  delete  pCrossBar;
}


 int  crossBarGetInputCount(  void  *  pCrossBarParam,  long  *  pCount  )
{
	CCrossbar  *  pCrossBar  =  (  CCrossbar  *  )pCrossBarParam;
	return  pCrossBar->GetInputCount(  pCount  );
}
#endif




////

CUnknown  *  WINAPI  CSampleGrabber::CreateInstance(  LPUNKNOWN  punk,  HRESULT  *  phr  )
{
	HRESULT  hr;
	if  (  !phr  )  phr  =  &hr;

	CSampleGrabber  *  pNewObject  =  new  CSampleGrabber(  punk,  phr  );
	if  (  pNewObject  ==  NULL  )*phr  =  E_OUTOFMEMORY;

	return  pNewObject;
}

CSampleGrabber::CSampleGrabber(  IUnknown  *  pOuter,  HRESULT  *  phr   )
	: CTransInPlaceFilter(  CONST_FILTERNAME,  (  IUnknown  *  )pOuter,  CLSID_SampleGrabber_is,  phr  )
{
	//  callback  =  NULL;
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CSampleGrabber::~CSampleGrabber(   )  
{
	m_var.pCB  =  NULL;	//  callback  =  NULL;
	OutputDebugString(  _T(  "~CSampleGrabber(  )  \n"  )  );
}

HRESULT  CSampleGrabber::NonDelegatingQueryInterface(const IID &riid, void **ppv)
{
	if  (  riid  ==  IID_ISampleGrabber_is  )
		return  GetInterface(  static_cast<ISampleGrabber_is *>(  this  ),  ppv  );
	else  
		return  CTransInPlaceFilter::NonDelegatingQueryInterface(  riid,  ppv  );
}

#if  10
HRESULT  CSampleGrabber::CheckInputType(  const  CMediaType  *  pmt  )
{
	HRESULT		hr	=	E_FAIL;

	if  (  mt.majortype  ==  MEDIATYPE_Video  )  {
		if  (  pmt->majortype   ==  MEDIATYPE_Video  )  {
			if  (  mt.subtype  ==  GUID_NULL  )  {
				if  (  bSubtypeGrabbable(  pmt->subtype  )  )  {
					#ifdef  __DEBUG__
							OutputDebugString(  _T(  "CheckInputType video ok\n"  )  );
							//  myDisplayType(  _T(  ""  ),  pmt  );
					#endif
					hr  =  S_OK;  goto  errLabel;					
				}
				goto  errLabel;
			}
#if  0
			//  2011/09/02, 这里给出了严格一致的匹配要求
			if  (  mt.formattype  ==  FORMAT_VideoInfo
				&&  mt.cbFormat  >=  sizeof(  VIDEOINFOHEADER  )
				&&  mt.pbFormat  )
			{
				VIDEOINFOHEADER  *  pVih  =  (  VIDEOINFOHEADER  *  )mt.pbFormat;
				if  (  bSubtypeGrabbable(  mt.subtype  )  
					&&  pVih->bmiHeader.biWidth
					&&  pVih->bmiHeader.biHeight  )
				{
					if  (  mt  ==  *pmt  )  {
						#ifdef  __DEBUG__
								OutputDebugString(  _T(  "CheckInputType video ok\n"  )  );
								//  myDisplayType(  _T(  ""  ),  pmt  );
						#endif
						hr  =  S_OK;  goto  errLabel;					
					}
					goto  errLabel;
				}
			}
#endif
			//
			if  (  pmt->subtype  ==  mt.subtype  )  {
				#ifdef  __DEBUG__
						OutputDebugString(  _T(  "CheckInputType video subtype ok\n"  )  );
				#endif
				hr  =  S_OK;  goto  errLabel;
			}

			goto  errLabel;			
		}
	
		goto  errLabel;
	}
	
	if  (  mt.majortype  ==  MEDIATYPE_Audio  )  {
		if  (  pmt->majortype  ==  MEDIATYPE_Audio  )  {
			if  (  mt.subtype  ==  GUID_NULL  )  {
				if  (  pmt->subtype  ==  MEDIASUBTYPE_PCM  )  {
					#ifdef  __DEBUG__
							OutputDebugString(  _T(  "ChecInputType audio ok\n"  )  );
					#endif
					hr  =  S_OK;  goto  errLabel;				
				}			
				goto  errLabel;
			}
			//
			if  (  pmt->subtype  ==  mt.subtype  )  {
				#ifdef  __DEBUG__
						OutputDebugString(  _T(  "CheckInputType audio subtype ok\n"  )  );
				#endif
				hr  =  S_OK;  goto  errLabel;
			}
			goto  errLabel;
		}
		goto  errLabel;
	}

	OutputDebugString(  _T(  "CSampleGrabber::CheckInputType failed: mt is not set\n"  )  );
	goto  errLabel;

	hr  =  S_OK;

errLabel:

#ifdef  __DEBUG__
	#if  0
		if  (  FAILED(  hr  )  )  {
			OutputDebugString(  _T(  "SampleGrabber::CheckInputType failed\n"  )  );
		}
	#endif
#endif

	return  hr;
}

#else
HRESULT  CSampleGrabber::CheckInputType(  const  CMediaType  *  pmt  )
{
	if  (  pmt->majortype   ==  MEDIATYPE_Video  &&
		(  pmt->subtype  ==  MEDIASUBTYPE_RGB24  )  &&
		pmt->formattype  ==  FORMAT_VideoInfo  )
		return  S_OK;
	else
		return  E_FAIL;
}

#endif


#if  10
HRESULT  CSampleGrabber::SetMediaType(  PIN_DIRECTION  direction,  const  CMediaType  *  pmt  )
{
	HRESULT				hr  =  E_FAIL;

	if  (  mt.majortype  ==  MEDIATYPE_Video  )  {
		if  (  pmt->majortype  ==  MEDIATYPE_Video  &&
			bSubtypeGrabbable(  pmt->subtype  )  )  			
		{
			if  (  pmt->formattype  ==  FORMAT_VideoInfo  &&
				pmt->cbFormat  >=  sizeof(  VIDEOINFOHEADER  )  &&
				pmt->pbFormat  !=  NULL  )
			{
				VIDEOINFOHEADER  *  vih  =  (  VIDEOINFOHEADER  *  )pmt->pbFormat;
				#if  0
					DWORD  dwStride  =  (  vih->bmiHeader.biWidth  *  (  vih->bmiHeader.biBitCount  /  8  )  +  3  )  &  ~3;
					//
					m_var.m_Width  =  vih->bmiHeader.biWidth;
					m_var.m_Height  =  vih->bmiHeader.biHeight;
					m_var.m_SampleSize  =  pmt->lSampleSize;
					m_var.m_Stride  =  ( long  )dwStride;
				#endif
				}
			else  if  (  pmt->formattype  ==  FORMAT_VideoInfo2  &&
						pmt->cbFormat  >=  sizeof(  VIDEOINFOHEADER2  )  &&
						pmt->pbFormat  )
			{
				VIDEOINFOHEADER2  *  vih	=  (  VIDEOINFOHEADER2  *  )pmt->pbFormat;

				}
			else  {
				  goto  errLabel;
			}

			}
		else  {
			  goto  errLabel;
		}
		}
	else  if  (  mt.majortype  ==  MEDIATYPE_Audio  )  {
			  if  (  pmt->subtype  ==  MEDIASUBTYPE_PCM  )  {
				  //  traceLog(  _T(  "SetMediaType: pcm"  )  );

				  }
			  else  {
				    goto  errLabel;					
			  }
			  }
	else
		goto  errLabel;

	hr  =  S_OK;

errLabel:
	return  hr;
}

#else

HRESULT  CSampleGrabber::SetMediaType(  PIN_DIRECTION  direction,  const  CMediaType  *  pmt  )
{
	HRESULT  hr  =  S_OK;
	VIDEOINFOHEADER  *  vih  =  (  VIDEOINFOHEADER  *  )pmt->pbFormat;

	if  (  pmt->majortype  ==  MEDIATYPE_Video  &&
		pmt->subtype   ==  MEDIASUBTYPE_RGB24  &&
		pmt->formattype  ==  FORMAT_VideoInfo  &&
		pmt->cbFormat  >=  sizeof(  VIDEOINFOHEADER  )  &&
		pmt->pbFormat  !=  NULL  )
	{
		DWORD  dwStride  =  (  vih->bmiHeader.biWidth  *  (  vih->bmiHeader.biBitCount  /  8  )  +  3  )  &  ~3;

#if  0
		//
		m_Width  =  vih->bmiHeader.biWidth;
		m_Height  =  vih->bmiHeader.biHeight;
		m_SampleSize  =  pmt->lSampleSize;
		m_Stride  =  ( long  )dwStride;
#endif
	}
	else  hr  =  E_FAIL;

	return  hr;
}

#endif


HRESULT  CSampleGrabber::Transform(  IMediaSample  *  pMediaSample  )
{
	if  (  !pMediaSample  )  return  E_FAIL;

	HRESULT		hr;
	double		dSampleTimeInS	=	0;
	BYTE	*	pData			=	NULL;

	REFERENCE_TIME	timeStart,  timeEnd;
	hr  =  pMediaSample->GetTime(  &timeStart,  &timeEnd  );
	if  (  FAILED(  hr  )  )  {
		#ifdef  __DEBUG__
				OutputDebugString(  _T(  "Transform: GetTime failed, skipped\n"  )  );
		#endif
		//  return  E_FAIL;
		//  注意，在使用preview采集时，没有时间戳的, 所以不能当失败处理。 2011/09/02
		timeStart  =  0;
		timeEnd  =  0;
	}
	dSampleTimeInS  =  timeStart  /  10000000.;

	if  (  FAILED(  pMediaSample->GetPointer(  &pData )  )  )  return  E_FAIL;

	long  size  =  pMediaSample->GetActualDataLength(  );

#ifdef  __DEBUG__
	#if  0
		TCHAR	tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Transform: %f, Bytes: %u\n"  ),  (  float  )dSampleTimeInS,  size  );
		OutputDebugString(  tBuf  );
	#endif
#endif

	//  if  (  callback  )  callback(  pData,  size  );
	if  (  m_var.pCB  )  m_var.pCB->BufferCB(  dSampleTimeInS,  pData,  size  );

	 return  S_OK;
}

#if  10
HRESULT  CSampleGrabber::DecideBufferSize(  IMemAllocator  *  pAlloc,  ALLOCATOR_PROPERTIES  *  pProperties  )
{
	if  (  m_pInput->IsConnected(  )  ==  FALSE  )  return  E_UNEXPECTED;

	ASSERT(  pAlloc  );
	ASSERT(  pProperties  );
	HRESULT  hr  =  NOERROR;

	if  (  mt.majortype  ==  MEDIATYPE_Video  )  {
		pProperties->cBuffers  =  1;
		pProperties->cbBuffer  =  m_pInput->CurrentMediaType(  ).GetSampleSize(  );
		//  ASSERT(  pProperties->cbBuffer  );
		if  (  !pProperties->cbBuffer  )  {
			#ifdef  __DEBUG__
					OutputDebugString(  _T(  "Attention: SampleGrabber::DecideBufferSize, cbBuffer is 0\n"  )  );
			#endif
		}
		}
	else  if  (  mt.majortype  ==  MEDIATYPE_Audio  )  {
			  CMediaType	mtIn  =  m_pInput->CurrentMediaType(  );
			  WAVEFORMATEX	*	pWave  =  (  WAVEFORMATEX  *  )mtIn.Format(  );
			  if  (  !pWave  )  return  E_FAIL;
			  pProperties->cBuffers  =  1;
			  pProperties->cbBuffer  =  pWave->nSamplesPerSec  *  pWave->nBlockAlign;
			  ASSERT(  pProperties->cbBuffer  );
			  }
	else  
		return  E_FAIL;

	ALLOCATOR_PROPERTIES  Actual;
	hr  =  pAlloc->SetProperties(  pProperties,  &Actual  );
	if  (  FAILED(  hr  )  )  return  hr;

	ASSERT(  Actual.cBuffers  >=  1  );

	if  ( pProperties->cBuffers > Actual.cBuffers  ||
		pProperties->cbBuffer  >  Actual.cbBuffer  )
	{
		return  E_FAIL;
	}
	return  NOERROR;
}
#else

HRESULT  CSampleGrabber::DecideBufferSize(  IMemAllocator  *  pAlloc,  ALLOCATOR_PROPERTIES  *  pProperties  )
{
	if  (  m_pInput->IsConnected(  )  ==  FALSE  )  return  E_UNEXPECTED;

	ASSERT(  pAlloc  );
	ASSERT(  pProperties  );
	HRESULT  hr  =  NOERROR;

	pProperties->cBuffers  =  1;
	pProperties->cbBuffer  =  m_pInput->CurrentMediaType(  ).GetSampleSize(  );
	ASSERT(  pProperties->cbBuffer  );

	ALLOCATOR_PROPERTIES  Actual;
	hr  =  pAlloc->SetProperties(  pProperties,  &Actual  );
	if  (  FAILED(  hr  )  )  return  hr;

	ASSERT(  Actual.cBuffers  >=  1  );

	if  ( pProperties->cBuffers > Actual.cBuffers  ||
		pProperties->cbBuffer  >  Actual.cbBuffer  )
	{
		return  E_FAIL;
	}
	return  NOERROR;
}
#endif



HRESULT  CSampleGrabber::GetMediaType(  int  iPosition,  CMediaType  *  pMediaType  )
{
	if  (  m_pInput->IsConnected(  )  ==  FALSE  )  return  E_UNEXPECTED;

	if  (  iPosition  <  0  )  return  E_INVALIDARG;

	if  (  iPosition  >  0  )  return  VFW_S_NO_MORE_ITEMS;

	*pMediaType  =  m_pInput->CurrentMediaType(  );
	return  NOERROR;
}

#if  0
STDMETHODIMP  CSampleGrabber::RegisterCallback(  MANAGEDCALLBACKPROC  mdelegate  )
{
	callback  =  mdelegate;

	return S_OK;
}
#endif

HRESULT STDMETHODCALLTYPE CSampleGrabber::SetMediaType(  const AM_MEDIA_TYPE *pType  )
{
	mt  =  *pType;

	return  S_OK;
}

#if  0
HRESULT STDMETHODCALLTYPE CSampleGrabber::GetConnectedMediaType(  AM_MEDIA_TYPE *pType  )
{
	HRESULT		hr;

	if  (  !this->m_pInput  )  return  -1;
	if  (  !m_pInput->IsConnected(  )  )  return  -1;

	hr  =  this->m_pInput->ConnectionMediaType(  pType  );

	return  hr;
}
#endif

HRESULT STDMETHODCALLTYPE CSampleGrabber::GetConnectedMediaType(  AM_MEDIA_TYPE *pType  )
{
	HRESULT		hr;

	if  (  !this->m_pInput  )  return  -1;
	if  (  m_pInput->IsConnected(  )  )  {
		hr  =  this->m_pInput->ConnectionMediaType(  pType  );
		return  hr;
	}
	if  (  !this->m_pOutput  )  return  -1;
	if  (  m_pOutput->IsConnected(  )  )  {
		hr  =  m_pOutput->ConnectionMediaType(  pType  );
		return  hr;
	}
	return  -1;
}

	
HRESULT STDMETHODCALLTYPE CSampleGrabber::SetBufferSamples(  BOOL BufferThem  )
{
	return  S_OK;
}

HRESULT STDMETHODCALLTYPE CSampleGrabber::SetCallback(  ISampleGrabberCB_is *pCallback,  long WhichMethodToCallback  )
{
	m_var.pCB  =  pCallback;
	return  S_OK;
}


#if  10
STDMETHODIMP_(ULONG)  CSampleGrabber::NonDelegatingRelease(  )
{
	if  (  InterlockedDecrement(  (  LPLONG  )&m_cRef  )  !=  0  )  return  m_cRef;

	delete  this;

	return 0;
}
#endif

#ifdef  __DEBUG__
int  i  =  0;
void  CALLBACK  myProc(  BYTE  *  pdata,  long  len  )
{
	int  cbBuffer  =  len;

	if  (  i  <  10  )  {
		i  ++;

		HANDLE  fh;
		BITMAPFILEHEADER  bmphdr;
		DWORD  nWritten;

		memset(  &bmphdr,  0,  sizeof(  bmphdr  )  );

		bmphdr.bfType  =  (  'M'  <<  8  )  |  'B';
		bmphdr.bfSize  =  sizeof(  bmphdr  )  +  sizeof(  BITMAPINFOHEADER  )  +  cbBuffer;
		bmphdr.bfOffBits  =  sizeof(  bmphdr  )  +  sizeof(  BITMAPINFOHEADER  );

		TCHAR  m_strSaveTo[128];
		_sntprintf(  m_strSaveTo,  128,  _T(  "c:\\tttbbb\\%d.bmp"  ),  i  );

		BITMAPINFOHEADER  bi;
		memset(  &bi,  0,  sizeof(  bi  )  );
		bi.biSize  =  sizeof(  bi  );
		bi.biWidth  =  720;
		bi.biHeight  =  480;
		bi.biPlanes  =  1;
		bi.biBitCount  =  24;
		bi.biCompression  =  BI_RGB;
		bi.biSizeImage  =  (  (  (  (  bi.biWidth  *  bi.biBitCount   )  +  31  )  &  ~  31  )  /  8  )  *  bi.biHeight;

		fh  =  CreateFile(  m_strSaveTo,  
							GENERIC_WRITE,  0,  NULL,
							CREATE_ALWAYS,  FILE_ATTRIBUTE_NORMAL,  NULL  );
		WriteFile(  fh,  &bmphdr,  sizeof(  bmphdr  ),  &nWritten,  NULL  );
		WriteFile(  fh,  &bi,  sizeof(  BITMAPINFOHEADER  ),  &nWritten,  NULL  );
		WriteFile(  fh,  pdata,  cbBuffer,  &nWritten,  NULL  );

		CloseHandle(  fh  );
	}
	return;
}





 #endif

	

#ifdef  __DEBUG__

EXTERN_C  const  CLSID  CLSID_NullRenderer;

#if  1
ISampleGrabber_is		*	m_pGrabber	=	0;
#endif

void WINAPI myDumpGraph(IFilterGraph *pGraph, DWORD dwLevel);
#if  0
BOOL  testSampleGrabber(  )
{


	AM_MEDIA_TYPE	mt;
	memset(  &mt,  0,  sizeof(  mt  )  );
	GUID	k	=	GUID_NULL;


	try  
	{
		IGraphBuilder  *  pGraph  =  NULL;

		IMediaControl  *  pControl  =  NULL;

		IMediaEvent  *  pEvent  =  NULL;

		IBaseFilter  *  pWMASFReader  =  NULL;

		IPin  *  pStreamOut  =  NULL,  *  pStreamRender  =  NULL;

		IFileSourceFilter  *  pIFileSourceFilter  =  NULL;

		// initialize  COM,  create  the filter graph manager,  and  query  for the event and control interfaces

		HRESULT  hr  =  CoInitialize(  NULL  );
		if  (  FAILED(  hr  ) )  return  FALSE;

		hr  =  CoCreateInstance(  CLSID_FilterGraph,  NULL,  CLSCTX_INPROC_SERVER,  IID_IGraphBuilder,  (  void  **  )&pGraph  );
		if  (  FAILED(  hr  )  )  return  FALSE;

		hr  =  CoCreateInstance(  CLSID_WMAsfReader,  NULL,  CLSCTX_INPROC_SERVER,  IID_IBaseFilter,  (  void  **  )&pWMASFReader  );
		if  (  SUCCEEDED(  hr  )  )
		{
			hr  =  pGraph->AddFilter(  pWMASFReader,  L"WM ASF Reader"  );

			if  (  SUCCEEDED(  hr  )  )
			{
				hr  =  pWMASFReader->QueryInterface(  IID_IFileSourceFilter,  (  void  **  )&pIFileSourceFilter  );

				if  (  SUCCEEDED(  hr  )  )
				{
					TCHAR  *  url  =  _T(  "c:\\tttbbb\\123.wmv"  );
					hr  =  pIFileSourceFilter->Load(  url,  NULL  );
				}
			}
		}
		if  (  FAILED(  hr  )  )  return  FALSE;

#if  0
		IBaseFilter  *  pGrabberF  =  NULL;

		hr  =  CoCreateInstance(  CLSID_SampleGrabber,  NULL,  CLSCTX_INPROC_SERVER,  IID_IBaseFilter,  (  void  **  )&pGrabberF  );
		if  (  FAILED(  hr  )  )  return  FALSE;
#endif 
		CSampleGrabber  *  pGrabberF  =  new  CSampleGrabber(  NULL,  &hr  );
		pGrabberF->AddRef(  );

		hr  =  pGraph->AddFilter(  pGrabberF,  L"Sample  Grabber"  );
		if  (  FAILED(  hr  )  )  return  FALSE;

		pGrabberF->QueryInterface(  IID_ISampleGrabber_is,  (  void  **  )&m_pGrabber  );

		AM_MEDIA_TYPE  mt;
		ZeroMemory(  &mt,  sizeof(  AM_MEDIA_TYPE  )  );
		mt.majortype  =  MEDIATYPE_Video;
		mt.subtype  =  MEDIASUBTYPE_RGB24;
		mt.formattype  =  FORMAT_VideoInfo;

		VIDEOINFOHEADER  vih;
		memset(  &vih,  0,  sizeof(  vih  )  );
		mt.cbFormat  =  sizeof(  vih  );
		mt.pbFormat  =  (  BYTE  *  )&vih;

		hr  =  pGrabberF->SetMediaType(  &CMediaType(  mt  )  );
		hr  =  pGrabberF->SetMediaType(  PINDIR_INPUT,  &CMediaType(  mt  )  );

		IBaseFilter  *  pNullRenderer;
		hr  =  CoCreateInstance(  CLSID_NullRenderer,  NULL,  CLSCTX_INPROC_SERVER,  IID_IBaseFilter,  (  void  **  )&pNullRenderer  );

		hr  =  pGraph->AddFilter(  pNullRenderer,  L"Null  Renderer"  );

		hr  =  ConnectFilters(  pGraph,  pWMASFReader,  pGrabberF  );

		IPin  *   pGrabInPin  =  NULL;
		hr  =  myGetPin(  pGrabberF,  PINDIR_INPUT,  &pGrabInPin  );
		AM_MEDIA_TYPE  mt1;
		hr  =  pGrabInPin->ConnectionMediaType(  &mt1  );
		myDisplayType(  _T(  "connectedMediaType"  ),  &mt1  );
		pGrabInPin->Release(  );

		IPin   *  pGrabOutPin  =  NULL;
		hr  =  myGetPin(  pGrabberF,  PINDIR_OUTPUT,  &pGrabOutPin  );
		hr  =  pGraph->Render(  pGrabOutPin  );
		if  (  FAILED(  hr  )  )  
		{
			MessageBox(  NULL,  _T(  ""  ),  _T(  "Could  not  render  grabber output pin\r\n"  ),  MB_OK  );
			return  FALSE;
		}
		pGrabOutPin->Release(  );

		myDumpGraph(  pGraph,  0  );  

		hr  =  pGraph->QueryInterface(  IID_IMediaEvent,  (  void  **  )&pEvent  );
		if  (  FAILED(  hr  )  )  return  FALSE;

		hr  =  pGraph->QueryInterface(  IID_IMediaControl,  (  void  **  )&pControl  );
		if  (  FAILED(  hr  )  )  return  FALSE;

		//  pGrabberF->RegisterCallback(  myProc  );

		long  evCode  =  0;
		hr  =  pControl->Run(  );
		hr  =  pEvent->WaitForCompletion(  INFINITE,  &evCode  );
		Sleep(  1000  );

		//  pGrabberF->RegisterCallback(  NULL  );

		pControl->Stop(  );
		pControl->Release(  );
		m_pGrabber->Release(  );
		pEvent->Release(  );
		pGraph->Release(  );

		pNullRenderer->Release(  );

		//  pGrabOutPin->Release(  );

		//  pGrabberF->Release(  );

		return  TRUE;
	}

	catch(  ...  )
	{
		return  FALSE;
	}

}
#endif

#endif