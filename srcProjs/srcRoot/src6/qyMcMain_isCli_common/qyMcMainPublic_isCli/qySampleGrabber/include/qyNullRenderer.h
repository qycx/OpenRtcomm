

#ifndef  __QYNULLRENDER_H__
#define  __QYNULLRENDER_H__  //  {


//  CLSID_NullRenderer
class CNullRenderer : public CBaseRenderer    // Base renderer class
{
public:
	DECLARE_IUNKNOWN;

	CNullRenderer(  IUnknown  *  pOuter,  HRESULT  *  phr  ):CBaseRenderer(  CLSID_NullRenderer_is,  _T(  "Null Renderer"  ),  pOuter,  phr  )  
	{  
	}
	~CNullRenderer(  )
	{
		//  OutputDebugString(  _T(  "CNullRenderer::~CNullRenderer\n"  )  );
	}

	static  CUnknown  *  WINAPI  CreateInstance(  LPUNKNOWN  punk,  HRESULT  *  phr  )  
	{	
		return  new  CNullRenderer(  punk,  phr  );								
	}


#if  0
	void OnRenderEnd(IMediaSample *pMediaSample)
	{		
	}
#endif

	HRESULT DoRenderSample(IMediaSample *pMediaSample) 
	{
		  //  OutputDebugString(  _T(  "CNullRenderer::DoRenderSample\n"  )  );

		return  S_OK;
	}
    HRESULT CheckMediaType(const CMediaType *) 
	{
		return  S_OK;
	}

	

};



#endif  //  }


