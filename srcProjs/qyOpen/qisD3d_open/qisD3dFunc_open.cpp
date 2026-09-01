

#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

#include <d3d9.h>

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include	<d3d12.h>

//
#include	<tchar.h>


//
#include	"qyDefs_open.h"
#include	"qisD3dDefs_open.h"
#include	"qisD3d_open.h"




#include	"atlcomcli.h"


 //
 //  2015/11/02
 int  myCreateVideoProcessor(  ID3D11VideoDevice  *  m_pDX11VideoDevice,  int  CropW,  int  CropH,  ID3D11VideoProcessorEnumerator  **  pm_pVideoProcessorEnum,  ID3D11VideoProcessor  **  pm_pVideoProcessor  )
{
    HRESULT hres = S_OK;

	if  (  !m_pDX11VideoDevice  )  return  -1;
	if  (  !pm_pVideoProcessorEnum  ||  !pm_pVideoProcessor  )  return  -1;
	if (  *pm_pVideoProcessorEnum &&  *pm_pVideoProcessor)
        return 0;

    //create video processor
    D3D11_VIDEO_PROCESSOR_CONTENT_DESC ContentDesc;
	memset(  &ContentDesc,  0,  sizeof(  ContentDesc  )  );

    ContentDesc.InputFrameFormat = D3D11_VIDEO_FRAME_FORMAT_PROGRESSIVE;
    ContentDesc.InputFrameRate.Numerator = 30000;
    ContentDesc.InputFrameRate.Denominator = 1000;
    ContentDesc.InputWidth  = CropW;
    ContentDesc.InputHeight = CropH;
    ContentDesc.OutputWidth = CropW;
    ContentDesc.OutputHeight = CropH;
    ContentDesc.OutputFrameRate.Numerator = 30000;
    ContentDesc.OutputFrameRate.Denominator = 1000;

    ContentDesc.Usage = D3D11_VIDEO_USAGE_PLAYBACK_NORMAL;

	if  (  !*pm_pVideoProcessorEnum  )  {
	    hres = m_pDX11VideoDevice->CreateVideoProcessorEnumerator( &ContentDesc, pm_pVideoProcessorEnum );
	    if (FAILED(hres))
		    return -1;
	}

	if  (  !*pm_pVideoProcessor  )  {
	    hres = m_pDX11VideoDevice->CreateVideoProcessor( *pm_pVideoProcessorEnum, 0, pm_pVideoProcessor );
	    if (FAILED(hres))
		    return -1;
	}

    return 0;
}

 //
 int  myCreateVideoProcessorEx(  ID3D11VideoDevice  *  m_pDX11VideoDevice,  int  CropW_i,  int  CropH_i,  int  CropW_o,  int  CropH_o,  ID3D11VideoProcessorEnumerator  **  pm_pVideoProcessorEnum,  ID3D11VideoProcessor  **  pm_pVideoProcessor  )
{
    HRESULT hres = S_OK;

	if  (  !m_pDX11VideoDevice  )  return  -1;
	if  (  !pm_pVideoProcessorEnum  ||  !pm_pVideoProcessor  )  return  -1;
	if (  *pm_pVideoProcessorEnum &&  *pm_pVideoProcessor)
        return 0;

    //create video processor
    D3D11_VIDEO_PROCESSOR_CONTENT_DESC ContentDesc;
	memset(  &ContentDesc,  0,  sizeof(  ContentDesc  )  );

    ContentDesc.InputFrameFormat = D3D11_VIDEO_FRAME_FORMAT_PROGRESSIVE;
    ContentDesc.InputFrameRate.Numerator = 30000;
    ContentDesc.InputFrameRate.Denominator = 1000;
    ContentDesc.InputWidth  = CropW_i;
    ContentDesc.InputHeight = CropH_i;
    ContentDesc.OutputWidth = CropW_o;
    ContentDesc.OutputHeight = CropH_o;
    ContentDesc.OutputFrameRate.Numerator = 30000;
    ContentDesc.OutputFrameRate.Denominator = 1000;

    ContentDesc.Usage = D3D11_VIDEO_USAGE_PLAYBACK_NORMAL;

	if  (  !*pm_pVideoProcessorEnum  )  {
	    hres = m_pDX11VideoDevice->CreateVideoProcessorEnumerator( &ContentDesc, pm_pVideoProcessorEnum );
	    if (FAILED(hres))
		    return -1;
	}

	if  (  !*pm_pVideoProcessor  )  {
	    hres = m_pDX11VideoDevice->CreateVideoProcessor( *pm_pVideoProcessorEnum, 0, pm_pVideoProcessor );
	    if (FAILED(hres))
		    return -1;
	}

    return 0;
}




 //  2015/10/02
 int  myCopyTex(  PARAM_copyTex  *  pParam,  int  CropW,  int  CropH,  ID3D11Texture2D  *  pTex_src,  ID3D11Texture2D  *  pTex_dst,  QIS_trace_common  *  pQtc  )
 {
	 int  iErr  =  -1;
	 
	 //  2016/05/04
	 if  (  !pParam  ||  !pTex_src  ||  !pTex_dst  )  {
		 return  -1;
	 }

	 //
	ID3D11Device *  g_pd3d11Device  =  pParam->g_pd3d11Device;
	ID3D11DeviceContext  *  context  =  pParam->context;

	if (!g_pd3d11Device) {
#ifdef  _DEBUG
		OutputDebugString(_T("myCopyTex failed, g_p3d11Device is null\n"));
#endif
		return  -1;
	}
	if (!pParam->m_pVideoContext) {
		if (!context) {
#ifdef  _DEBUG
			OutputDebugString(_T("myCopyTex failed, context is null\n"));
#endif
			return  -1;
		}
	}

	//
	TCHAR  tBuf[128]  =  _T(  ""  );
	HRESULT  hr;
	
	CComPtr<ID3D11VideoProcessorInputView>  m_pInputViewLeft;
    CComPtr<ID3D11VideoProcessorOutputView> m_pOutputView;

	//
	BOOL  bGot_m_pDX11VideoDevice  =  FALSE;
	BOOL  bGot_m_pVideoContext  =  FALSE;
	BOOL  bGot_pVideoProcessorEnum  =  FALSE;
	BOOL  bGot_m_pVideoProcessor  =  FALSE;

	//
	if  (  !pParam->m_pDX11VideoDevice  )  {
		hr  =  g_pd3d11Device->QueryInterface(  IID_ID3D11VideoDevice,  (  void  **  )&pParam->m_pDX11VideoDevice  );
		if  (  FAILED(  hr  )  )  {
			if  (  pQtc  )  {
				M_qtc_tcsCat(  pQtc,  _T(  "queryInt IID_ID3D11VideoDevice failed"  )  );
			}
			goto  errLabel;
		}
		bGot_m_pDX11VideoDevice  =  TRUE;
	}
	if  (  !pParam->m_pVideoContext  )  {
		hr  =  context->QueryInterface(  IID_ID3D11VideoContext,  (  void  **  )&pParam->m_pVideoContext  );
		if  (  FAILED(  hr  )  )  {
			if  (  pQtc  )  {
				M_qtc_tcsCat(  pQtc,  _T(  "queryInt IID_ID3D11VideoContext failed"  )  );
			}
			goto  errLabel;
		}
		bGot_m_pVideoContext  =  TRUE;
	}
	
	//create video processor
    D3D11_VIDEO_PROCESSOR_CONTENT_DESC ContentDesc;
    memset(  &ContentDesc,  0,  sizeof(  ContentDesc  )  );

    ContentDesc.InputFrameFormat = D3D11_VIDEO_FRAME_FORMAT_PROGRESSIVE;
    ContentDesc.InputFrameRate.Numerator = 30000;
    ContentDesc.InputFrameRate.Denominator = 1000;
    ContentDesc.InputWidth  = CropW;
    ContentDesc.InputHeight = CropH;
    ContentDesc.OutputWidth = CropW;
    ContentDesc.OutputHeight = CropH;
    ContentDesc.OutputFrameRate.Numerator = 30000;
    ContentDesc.OutputFrameRate.Denominator = 1000;

    ContentDesc.Usage = D3D11_VIDEO_USAGE_PLAYBACK_NORMAL;

	//
	if  (  !pParam->pVideoProcessorEnum  )  {		
		hr = pParam->m_pDX11VideoDevice->CreateVideoProcessorEnumerator( &ContentDesc, &pParam->pVideoProcessorEnum );
		if (FAILED(hr))  {
			if  (  pQtc  )  {			
				M_qtc_tcsCat(  pQtc,  _T(  "CreateVideoProcessorEnumerator failed"  )  );
			}
			goto  errLabel;
		}
		bGot_pVideoProcessorEnum  =  TRUE;
	}

	if  (  !pParam->m_pVideoProcessor  )  {
		hr = pParam->m_pDX11VideoDevice->CreateVideoProcessor( pParam->pVideoProcessorEnum, 0, &pParam->m_pVideoProcessor );
		if (FAILED(hr))  {
			if  (  pQtc  )  {			
				M_qtc_tcsCat(  pQtc,  _T(  "CreateVideoProcessor failed"  )  );
			}
			goto  errLabel;
		}
		bGot_m_pVideoProcessor  =  TRUE;
	}

    //
    D3D11_VIDEO_PROCESSOR_OUTPUT_VIEW_DESC OutputViewDesc;
    
    {
        OutputViewDesc.ViewDimension = D3D11_VPOV_DIMENSION_TEXTURE2D;
        OutputViewDesc.Texture2D.MipSlice = 0;
    }


	hr = pParam->m_pDX11VideoDevice->CreateVideoProcessorOutputView(
            pTex_dst,
            pParam->pVideoProcessorEnum,
            &OutputViewDesc,
            &m_pOutputView.p );
	if  (  FAILED(hr)  )  {
		#ifdef  _DEBUG
				OutputDebugString(  _T(  "myCopyTex failed: videoDevice.CreateVideoProcessorOutputView failed\n"  )  );
		#endif
		//
		if  (  pQtc  )  {					
			M_qtc_tcsCat(  pQtc,  _T(  "CreateVideoProcessorOutputView failed"  )  );		
		}
		goto  errLabel;
	}

    D3D11_VIDEO_PROCESSOR_INPUT_VIEW_DESC InputViewDesc;
    InputViewDesc.FourCC = 0;
    InputViewDesc.ViewDimension = D3D11_VPIV_DIMENSION_TEXTURE2D;
    InputViewDesc.Texture2D.MipSlice = 0;
    InputViewDesc.Texture2D.ArraySlice = 0;


	ID3D11Texture2D* pRTTexture2D; pRTTexture2D = NULL;	//  reinterpret_cast<ID3D11Texture2D*>(pair.first);
    D3D11_TEXTURE2D_DESC RTTexture2DDesc;

	//  2015/09/28
	pRTTexture2D  =  pTex_src;	//  m_pTexture_shared;

	//

    // Creating input views for left and righ eyes
	hr = pParam->m_pDX11VideoDevice->CreateVideoProcessorInputView(
            pRTTexture2D,
            pParam->pVideoProcessorEnum,
            &InputViewDesc,
            &m_pInputViewLeft.p );
	if  (  FAILED(  hr  )  )  {
		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "CreateVideoProcessorInputView failed. hr 0x%x"  ),  hr  );		
		//
		pRTTexture2D->GetDesc(  &RTTexture2DDesc  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. src: %dX%d. CropWH: %dX%d."  ),  tBuf,  RTTexture2DDesc.Width,  RTTexture2DDesc.Height,  CropW,  CropH  );
		//
		M_qtc_tcsCat(  pQtc,  tBuf  );
		//
		goto  errLabel;
	}
    
	//
	RECT rect;  
	memset(  &rect,  0,  sizeof(  rect  )  );
    rect.right  = CropW;
    rect.bottom = CropH;
	
	//
	D3D11_VIDEO_PROCESSOR_STREAM StreamData;

    {
		
		//
        StreamData.Enable = TRUE;
        StreamData.OutputIndex = 0;
        StreamData.InputFrameOrField = 0;
        StreamData.PastFrames = 0;
        StreamData.FutureFrames = 0;
        StreamData.ppPastSurfaces = NULL;
        StreamData.ppFutureSurfaces = NULL;
        StreamData.pInputSurface = m_pInputViewLeft;
        StreamData.ppPastSurfacesRight = NULL;
        StreamData.ppFutureSurfacesRight = NULL;
        StreamData.pInputSurfaceRight = NULL;

		//
		if (pParam->pVideoLock) {
			EnterCriticalSection(pParam->pVideoLock);
		}

		//
        pParam->m_pVideoContext->VideoProcessorSetStreamSourceRect(pParam->m_pVideoProcessor, 0, true, &rect);
        pParam->m_pVideoContext->VideoProcessorSetStreamFrameFormat( pParam->m_pVideoProcessor, 0, D3D11_VIDEO_FRAME_FORMAT_PROGRESSIVE);
        hr = pParam->m_pVideoContext->VideoProcessorBlt( pParam->m_pVideoProcessor, m_pOutputView, 0, 1, &StreamData );
		
		//
		if (pParam->pVideoLock) {
			LeaveCriticalSection(pParam->pVideoLock);
		}

		//
        if  (  FAILED(hr)  )  {
			//
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "videoProcessorBlt failed. hr 0x%x\n"  ),  hr  );
			//
			#ifdef  _DEBUG
					OutputDebugString(  tBuf  );
					int  ii  =  E_INVALIDARG;
			#endif
			//
			if  (  pQtc  )  {			
				M_qtc_tcsCat(  pQtc,  tBuf  );
			}
			goto  errLabel;
		}
    }




	 iErr  =  0;
errLabel:

	 if  (  iErr  )  {
		 int  ii;
		 ii  =  0;
	 }

	 //
	 if  (  bGot_m_pVideoProcessor  )  {
		 MACRO_safeRelease(  pParam->m_pVideoProcessor  );
	 }
	 if  (  bGot_pVideoProcessorEnum  )  {
		 MACRO_safeRelease(  pParam->pVideoProcessorEnum  );
	 }
	 if  (  bGot_m_pVideoContext  )  {
		 MACRO_safeRelease(  pParam->m_pVideoContext  );
	 }
	 if  (  bGot_m_pDX11VideoDevice  )  {
		 MACRO_safeRelease(  pParam->m_pDX11VideoDevice  );
	 }

	 return  iErr;
 }



//
  int  myCopyTexEx(  PARAM_copyTex  *  pParam,  int  CropW_i,  int  CropH_i,  int  CropW_o,  int  CropH_o,  RECT  rect_src,  RECT  rect_dst,  ID3D11Texture2D  *  pTex_src,  ID3D11Texture2D  *  pTex_dst  )
 {
	 int  iErr  =  -1;
	 
	ID3D11Device *  g_pd3d11Device  =  pParam->g_pd3d11Device;
	ID3D11DeviceContext  *  context  =  pParam->context;

	if  (  !g_pd3d11Device  )  return  -1;
	if  (  !context  )  return  -1;

	TCHAR  tBuf[128]  =  _T(  ""  );
	HRESULT  hr;
	
	CComPtr<ID3D11VideoProcessorInputView>  m_pInputViewLeft;
    CComPtr<ID3D11VideoProcessorOutputView> m_pOutputView;

	//
	BOOL  bGot_m_pDX11VideoDevice  =  FALSE;
	BOOL  bGot_m_pVideoContext  =  FALSE;
	BOOL  bGot_pVideoProcessorEnum  =  FALSE;
	BOOL  bGot_m_pVideoProcessor  =  FALSE;

	//
	if  (  !pParam->m_pDX11VideoDevice  )  {
		hr  =  g_pd3d11Device->QueryInterface(  IID_ID3D11VideoDevice,  (  void  **  )&pParam->m_pDX11VideoDevice  );
		if  (  FAILED(  hr  )  )  {
			goto  errLabel;
		}
		bGot_m_pDX11VideoDevice  =  TRUE;
	}
	if  (  !pParam->m_pVideoContext  )  {
		hr  =  context->QueryInterface(  IID_ID3D11VideoContext,  (  void  **  )&pParam->m_pVideoContext  );
		if  (  FAILED(  hr  )  )  {
			goto  errLabel;
		}
		bGot_m_pVideoContext  =  TRUE;
	}
	
	//create video processor
    D3D11_VIDEO_PROCESSOR_CONTENT_DESC ContentDesc;
    memset(  &ContentDesc,  0,  sizeof(  ContentDesc  )  );

    ContentDesc.InputFrameFormat = D3D11_VIDEO_FRAME_FORMAT_PROGRESSIVE;
    ContentDesc.InputFrameRate.Numerator = 30000;
    ContentDesc.InputFrameRate.Denominator = 1000;
    ContentDesc.InputWidth  = CropW_i;
    ContentDesc.InputHeight = CropH_i;
    ContentDesc.OutputWidth = CropW_o;
    ContentDesc.OutputHeight = CropH_o;
    ContentDesc.OutputFrameRate.Numerator = 30000;
    ContentDesc.OutputFrameRate.Denominator = 1000;

    ContentDesc.Usage = D3D11_VIDEO_USAGE_PLAYBACK_NORMAL;

	//
	if  (  !pParam->pVideoProcessorEnum  )  {		
		hr = pParam->m_pDX11VideoDevice->CreateVideoProcessorEnumerator( &ContentDesc, &pParam->pVideoProcessorEnum );
		if (FAILED(hr))  {
			goto  errLabel;
		}
		bGot_pVideoProcessorEnum  =  TRUE;
	}

	if  (  !pParam->m_pVideoProcessor  )  {
		hr = pParam->m_pDX11VideoDevice->CreateVideoProcessor( pParam->pVideoProcessorEnum, 0, &pParam->m_pVideoProcessor );
		if (FAILED(hr))  {
			goto  errLabel;
		}
		bGot_m_pVideoProcessor  =  TRUE;
	}

    //
    D3D11_VIDEO_PROCESSOR_OUTPUT_VIEW_DESC OutputViewDesc;
    
    {
        OutputViewDesc.ViewDimension = D3D11_VPOV_DIMENSION_TEXTURE2D;
        OutputViewDesc.Texture2D.MipSlice = 0;
    }


	hr = pParam->m_pDX11VideoDevice->CreateVideoProcessorOutputView(
            pTex_dst,
            pParam->pVideoProcessorEnum,
            &OutputViewDesc,
            &m_pOutputView.p );
	if (FAILED(hr))  {
		#ifdef  _DEBUG
				OutputDebugString(  _T(  "myCopyTex failed: videoDevice.CreateVideoProcessorOutputView failed\n"  )  );
		#endif
		goto  errLabel;
	}

    D3D11_VIDEO_PROCESSOR_INPUT_VIEW_DESC InputViewDesc;
    InputViewDesc.FourCC = 0;
    InputViewDesc.ViewDimension = D3D11_VPIV_DIMENSION_TEXTURE2D;
    InputViewDesc.Texture2D.MipSlice = 0;
    InputViewDesc.Texture2D.ArraySlice = 0;


	ID3D11Texture2D* pRTTexture2D; pRTTexture2D = NULL;	//  reinterpret_cast<ID3D11Texture2D*>(pair.first);
    //D3D11_TEXTURE2D_DESC RTTexture2DDesc;

	//  2015/09/28
	pRTTexture2D  =  pTex_src;	//  m_pTexture_shared;

	//

    // Creating input views for left and righ eyes
	hr = pParam->m_pDX11VideoDevice->CreateVideoProcessorInputView(
            pRTTexture2D,
            pParam->pVideoProcessorEnum,
            &InputViewDesc,
            &m_pInputViewLeft.p );
	if  (  FAILED(  hr  )  )  {
		goto  errLabel;
	}
    
	//
	//RECT rect = {0};
    //rect.right  = CropW;
    //rect.bottom = CropH;
	
	//
	D3D11_VIDEO_PROCESSOR_STREAM StreamData;

    {
		
		//
        StreamData.Enable = TRUE;
        StreamData.OutputIndex = 0;
        StreamData.InputFrameOrField = 0;
        StreamData.PastFrames = 0;
        StreamData.FutureFrames = 0;
        StreamData.ppPastSurfaces = NULL;
        StreamData.ppFutureSurfaces = NULL;
        StreamData.pInputSurface = m_pInputViewLeft;
        StreamData.ppPastSurfacesRight = NULL;
        StreamData.ppFutureSurfacesRight = NULL;
        StreamData.pInputSurfaceRight = NULL;

		//
        pParam->m_pVideoContext->VideoProcessorSetStreamSourceRect(pParam->m_pVideoProcessor, 0, true, &rect_src);
		//
		pParam->m_pVideoContext->VideoProcessorSetStreamDestRect(pParam->m_pVideoProcessor, 0, true, &rect_dst);
		//
        pParam->m_pVideoContext->VideoProcessorSetStreamFrameFormat( pParam->m_pVideoProcessor, 0, D3D11_VIDEO_FRAME_FORMAT_PROGRESSIVE);
        hr = pParam->m_pVideoContext->VideoProcessorBlt( pParam->m_pVideoProcessor, m_pOutputView, 0, 1, &StreamData );
		
		//
        if (FAILED(hr))  {
			#ifdef  _DEBUG
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "myCopyTex failed, videoContext.videoProcessorBlt failed. hr 0x%x\n"  ),  hr  );
					OutputDebugString(  tBuf  );
					int  ii  =  E_INVALIDARG;
			#endif
			goto  errLabel;
		}
    }




	 iErr  =  0;
errLabel:

	 if  (  iErr  )  {
		 int  ii;
		 ii  =  0;
	 }

	 //
	 if  (  bGot_m_pVideoProcessor  )  {
		 MACRO_safeRelease(  pParam->m_pVideoProcessor  );
	 }
	 if  (  bGot_pVideoProcessorEnum  )  {
		 MACRO_safeRelease(  pParam->pVideoProcessorEnum  );
	 }
	 if  (  bGot_m_pVideoContext  )  {
		 MACRO_safeRelease(  pParam->m_pVideoContext  );
	 }
	 if  (  bGot_m_pDX11VideoDevice  )  {
		 MACRO_safeRelease(  pParam->m_pDX11VideoDevice  );
	 }

	 return  iErr;
 }


 //  2015/10/21
 void  freeSharedTex(  SHARED_tex  *  pMem  )
 {
	 if  (  !pMem  )  return;

	 if  (  pMem->g_sharedTex_handle  )  {
		 if  (  isHandleValid_open(  pMem->g_sharedTex_handle  )  )  {
			 CloseHandle(  pMem->g_sharedTex_handle  );  
		 }
		 pMem->g_sharedTex_handle  =  NULL;
	 }
	 //		
	 MACRO_safeRelease(  pMem->m_pDXGIKeyedMutex  );
	 //
	 MACRO_safeRelease(  pMem->m_pRTV  );  //  2016/05/05
	 MACRO_safeRelease(  pMem->m_shared_pTex11  );

	 //
	 MACRO_safeRelease(pMem->m_shared_pTex12);

 }


 //
 void  free_CLI_sharedTex(  CLI_sharedTex  *  pMem  )
 {
	 if  (  !pMem  )  return;
	 
	 MACRO_safeRelease(  pMem->m_shared_pTex  );	
	 //  2016/05/07
	 MACRO_safeRelease(  pMem->m_pSRV  );
	 //
	 MACRO_safeRelease(  pMem->m_pDXGIKeyedMutex  );

	 return;
 }