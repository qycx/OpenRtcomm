

#ifndef  __QMCDMO_H__
#define  __QMCDMO_H__	//  {


#include	"qmcDmoPublic.h"
#include	"qmcVideoCapture_dx.h"

#ifdef  __SUPPORT_CUS_sampleGrabber__
		#include	"qySampleGrabberPublic.h"
#endif



#define   SAFERELEASE(x)            if((x)){ (x)->Release(); (x) = NULL;}
#define   SAFEDELETE(x)             if((x)){ delete [] (x);  (x) = NULL;}
#define   SAFEDELETES(x)            if((x)){ delete    (x);  (x) = NULL;}
#define   SAFEFREE(x)               if((x)){ free(x);        (x) = NULL;}


//  CMediaBuffer object
class CMediaBuffer : public IMediaBuffer
{
public:
    CMediaBuffer(DWORD cbMaxLength) :
        m_cRef(0),
        m_cbMaxLength(cbMaxLength),
        m_cbLength(0),
        m_pbData(NULL)
    {
		memset(  &m_var,  0,  sizeof(  m_var  )  );		//  2009/05/19
    }

    ~CMediaBuffer()
    {
        if (m_pbData) {
            //  delete [] m_pbData;
			free(  m_pbData  );							//  2009/09/23
        }
    }

    STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        if (ppv == NULL) {
            return E_POINTER;
        }
        if (riid == IID_IMediaBuffer || riid == IID_IUnknown) {
            *ppv = static_cast<IMediaBuffer *>(this);
            AddRef();
            return S_OK;
        }
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    STDMETHODIMP_(ULONG) AddRef()
    {
        return InterlockedIncrement(&m_cRef);
    }

    STDMETHODIMP_(ULONG) Release()
    {
        LONG lRef = InterlockedDecrement(&m_cRef);
        if (lRef == 0) {
            delete this;
        }
        return lRef;
    }

    STDMETHODIMP SetLength(DWORD cbLength)
    {
        if (cbLength > m_cbMaxLength) {
            return E_INVALIDARG;
        } else {
            m_cbLength = cbLength;
            return S_OK;
        }
    }

    STDMETHODIMP GetMaxLength(DWORD *pcbMaxLength)
    {
        if (pcbMaxLength == NULL) {
            return E_POINTER;
        }
        *pcbMaxLength = m_cbMaxLength;
        return S_OK;
    }

    STDMETHODIMP GetBufferAndLength(BYTE **ppbBuffer, DWORD *pcbLength)
    {
        if (ppbBuffer == NULL || pcbLength == NULL) {
            return E_POINTER;
        }
        *ppbBuffer = m_pbData;
        *pcbLength = m_cbLength;
        return S_OK;
    }

    HRESULT Init()
    {
        //  m_pbData = new BYTE[m_cbMaxLength];
		m_pbData  =  (  BYTE  *  )mymalloc(  m_cbMaxLength  );		//  2009/09/23
        if (NULL == m_pbData) {
            return E_OUTOFMEMORY;
        } else {
            return S_OK;
        }
    }

    DWORD						m_cbLength;
    const DWORD					m_cbMaxLength;
    LONG						m_cRef;
    BYTE					*	m_pbData;

	struct						{
#if  0	//  2009/12/12
		REFERENCE_TIME			rtStart;
		REFERENCE_TIME			rtTimeLen;
#endif
	}							m_var;

};


class CMediaBuffer_new : public IMediaBuffer
{
public:
    CMediaBuffer_new() :
        m_cRef(0),
        m_cbMaxLength(0),
        m_cbLength(0),
        m_pbData(NULL)
    {
		memset(  &m_var,  0,  sizeof(  m_var  )  );		//  2009/05/19
    }

    ~CMediaBuffer_new()
    {
    }

    STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        if (ppv == NULL) {
            return E_POINTER;
        }
        if (riid == IID_IMediaBuffer || riid == IID_IUnknown) {
            *ppv = static_cast<IMediaBuffer *>(this);
            AddRef();
            return S_OK;
        }
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    STDMETHODIMP_(ULONG) AddRef()
    {
        return InterlockedIncrement(&m_cRef);
    }

    STDMETHODIMP_(ULONG) Release()
    {
        LONG lRef = InterlockedDecrement(&m_cRef);
        if (lRef == 0) {
            delete this;
        }
        return lRef;
    }

    STDMETHODIMP SetLength(DWORD cbLength)
    {
        if (cbLength > m_cbMaxLength) {
            return E_INVALIDARG;
        } else {
            m_cbLength = cbLength;
            return S_OK;
        }
    }

    STDMETHODIMP GetMaxLength(DWORD *pcbMaxLength)
    {
        if (pcbMaxLength == NULL) {
            return E_POINTER;
        }
        *pcbMaxLength = m_cbMaxLength;
        return S_OK;
    }

    STDMETHODIMP GetBufferAndLength(BYTE **ppbBuffer, DWORD *pcbLength)
    {
        if (ppbBuffer == NULL || pcbLength == NULL) {
            return E_POINTER;
        }
        *ppbBuffer = m_pbData;
        *pcbLength = m_cbLength;
        return S_OK;
    }

#if  0
    HRESULT Init()
    {
        //  m_pbData = new BYTE[m_cbMaxLength];
		m_pbData  =  (  BYTE  *  )mymalloc(  m_cbMaxLength  );		//  2009/09/23
        if (NULL == m_pbData) {
            return E_OUTOFMEMORY;
        } else {
            return S_OK;
        }
    }
#endif

	void set_Buffer(BYTE *pData, DWORD ulSize,  DWORD ulData) 
	{
        m_pbData = pData;
		m_cbMaxLength = ulSize;
        m_cbLength = ulData;
    }



    DWORD						m_cbLength;
    DWORD						m_cbMaxLength;
    LONG						m_cRef;
    BYTE					*	m_pbData;

	struct						{
#if  0	//  2009/12/12
		REFERENCE_TIME			rtStart;
		REFERENCE_TIME			rtTimeLen;
#endif
	}							m_var;

};



typedef  struct  __qmcDmo_t					{
				 IMediaObject			*	m_pObject;

				 CMediaBuffer			*	pInputBuffer;
				 CMediaBuffer			*	pOutputBuffer;

			#if  0
				 struct						{
					 BYTE				*	pBuf;
					 unsigned  int			len;
					 //
					 REFERENCE_TIME			rtStart;
					 REFERENCE_TIME			rtTimeLen;

				 }							outs[15];
			#endif
				 QDC_OUTPUT					outs[15];
				 
}		 QMC_DMO;


//



//
HRESULT CreateBuffer(DWORD cbMaxLength, CMediaBuffer **ppBuffer);
//  int  dmoProcessOutputs(  QMC_DMO  *  pDmo,  BYTE *  pbOutData,  DWORD  &m_uDataSize );
int  dmoProcessOutputs(  MY_DMO_INFO  *  pDmoInfo,  MY_DEBUG_STEP  *  pDebugStep  =  NULL  );


#endif  //  }


