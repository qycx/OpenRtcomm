#pragma once

#include  <dshow.h>
//  #include  "streams.h"
#include  <initguid.h>

//  #include	"qySampleGrabberPublic.h"




#define  CONST_FILTERNAME	L"SampleGrabberFilter"

class CSampleGrabber : public CTransInPlaceFilter,  public ISampleGrabber_is
{
private:
	struct	{
		//  MANAGEDCALLBACKPROC  callback;
		ISampleGrabberCB_is	*	pCB;

#if  0
		long  m_Width;
		long  m_Height;
		long  m_SampleSize;
		long  m_Stride;
#endif
	}			m_var;

	CMediaType	mt;

#if  0
	unsigned  format_BitsPerSample;
	unsigned  format_SamplesPerSecond;
	unsigned  format_BytesPerSecond;

#endif

public:
	CSampleGrabber(  IUnknown  *  pOuter,  HRESULT  *  phr  );
	~CSampleGrabber(  );
	static  CUnknown  *  WINAPI  CreateInstance(  LPUNKNOWN  punk,  HRESULT  *  phr  );

	DECLARE_IUNKNOWN;
	STDMETHODIMP  NonDelegatingQueryInterface(  REFIID  riid,  void   **  ppv  );

    //  CTransInPlaceFilter
	HRESULT  CheckInputType(  const  CMediaType  *  pmt  );
	HRESULT  SetMediaType(  PIN_DIRECTION  direction,  const  CMediaType  *  pmt  );
	HRESULT  Transform(  IMediaSample  *  pMediaSample  );
	HRESULT  DecideBufferSize(  IMemAllocator  *  pAlloc,  ALLOCATOR_PROPERTIES  *  pProperties  );
	HRESULT  GetMediaType(  int  iPosition,  CMediaType  *  pMediaType  );
	HRESULT  CheckTransform(  const  CMediaType  *  mtIn,  const  CMediaType  *  mtOut  ){  return  NOERROR;  }

	STDMETHODIMP_(  ULONG  )  NonDelegatingAddRef(  )
	{
		return  InterlockedIncrement(  (  LPLONG  )&m_cRef  );
	}
	 
	//  STDMETHODIMP  RegisterCallback( MANAGEDCALLBACKPROC  mdelegate  );
		
	HRESULT STDMETHODCALLTYPE SetMediaType(  const AM_MEDIA_TYPE *pType  );
	HRESULT STDMETHODCALLTYPE GetConnectedMediaType(  AM_MEDIA_TYPE *pType  );
	HRESULT STDMETHODCALLTYPE SetBufferSamples(  BOOL BufferThem  );
	HRESULT STDMETHODCALLTYPE SetCallback(  ISampleGrabberCB_is *pCallback,  long WhichMethodToCallback  );

	STDMETHODIMP_(  ULONG  )  NonDelegatingRelease(  );
};



