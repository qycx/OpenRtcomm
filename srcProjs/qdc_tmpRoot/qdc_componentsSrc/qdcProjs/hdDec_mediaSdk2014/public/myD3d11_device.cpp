

#if defined(_WIN32) || defined(_WIN64)
#include <tchar.h>
#include <windows.h>
#endif
#include <numeric>
#include <ctime>
#include <algorithm>
#include "pipeline_decode.h"
#include "sysmem_allocator.h"
//#include "../../sample_user_modules/plugin_api/plugin_loader.h"

#if defined(_WIN32) || defined(_WIN64)
#include "d3d_allocator.h"
#include "d3d11_allocator.h"
#include "d3d_device.h"
#include "d3d11_device.h"
#endif

#if defined LIBVA_SUPPORT
#include "vaapi_allocator.h"
#include "vaapi_device.h"
#endif



#include	"myutils.h"
#include "pipeline_decode.h"
#include "sysmem_allocator.h"

//#include "../../sample_user_modules/plugin_api/plugin_loader.h"


#include	"qdcOpenCommon.h"
#include	"myDecPipeline.h"

#include	"qisCompressProc.h"
#include	"myFunc_mediaSdk.h"
#include	"tmpGuiOpenFunc.h"

#include	"myD3d11_device.h"
//
#include	"qyDefs_open.h"
#include	"qisD3dDefs_open.h"
#include	"qisD3d_open.h"
#include	"qmcDirectX_open.h"
#include	"dec_d3d11_dev_open.h"	//  2016/04/26
#include	"tmpDecOpenFunc.h"


//
extern  BOOL				g_bShowDec_sharedTexStatus;			//  2016/04/09
extern  unsigned  int		g_uiXql_player;		



//
BOOL  bShowRenderWnd(  );


//
CMyD3D11Device::CMyD3D11Device(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	if  (  g_pf_DEC_d3d11_devVar_new  )  {
		m_var.pDEC_d3d11_devVar  =  g_pf_DEC_d3d11_devVar_new(  );
	}
}


CMyD3D11Device::~CMyD3D11Device(  )
{
	//  decDev_free_resource(  &m_var.devVar  );
	if  (  g_pf_DEC_d3d11_devVar_free  )  {
		g_pf_DEC_d3d11_devVar_free(  &m_var.pDEC_d3d11_devVar  );
	}
}


mfxStatus CMyD3D11Device::Init(
    mfxHDL hWindow,
    mfxU16 nViews,
    mfxU32 nAdapterNum)
{
    m_HandleWindow = (HWND)hWindow;
    mfxStatus sts = MFX_ERR_NONE;
    HRESULT hres = S_OK;
    m_nViews = nViews;
    if (2 < nViews)
        return MFX_ERR_UNSUPPORTED;
    m_bDefaultStereoEnabled = FALSE;

    static D3D_FEATURE_LEVEL FeatureLevels[] = {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };
    D3D_FEATURE_LEVEL pFeatureLevelsOut;

	//
	if  (  g_pGuiOpen->pf_CreateDXGIFactory1  )  {
		PF_CreateDXGIFactory1  pf  =  (  PF_CreateDXGIFactory1  )g_pGuiOpen->pf_CreateDXGIFactory1;
		hres = pf(__uuidof(IDXGIFactory2), (void**)(&m_pDXGIFactory) );
		}
	else  {    
		  //hres = CreateDXGIFactory(__uuidof(IDXGIFactory2), (void**)(&m_pDXGIFactory) );
		  tmp_showInfo(  _T(  "d3d11Device.init failed, pf_CreateDXGIFactory1 is null"  )  );
		  return  MFX_ERR_UNKNOWN;
	}
	//  2015/09/29
    if (FAILED(hres))  {
		//
		tmp_showInfo(  _T(  "pf_CreateDXGIFactory1 failed"  )  );
		//
        return MFX_ERR_DEVICE_FAILED;
	}

    if (m_nViews == 2 && hWindow)
    {
        hres = m_pDXGIFactory->QueryInterface(__uuidof(IDXGIDisplayControl), (void **)&m_pDisplayControl);
        if (FAILED(hres))
            return MFX_ERR_DEVICE_FAILED;

        m_bDefaultStereoEnabled = m_pDisplayControl->IsStereoEnabled();
        if (!m_bDefaultStereoEnabled)
            m_pDisplayControl->SetStereoEnabled(TRUE);
    }

    hres = m_pDXGIFactory->EnumAdapters(nAdapterNum,&m_pAdapter);
    if (FAILED(hres))
        return MFX_ERR_DEVICE_FAILED;

    hres =  D3D11CreateDevice(m_pAdapter ,
                            D3D_DRIVER_TYPE_UNKNOWN,
                            NULL,
                            0,
                            FeatureLevels,
                            MSDK_ARRAY_LEN(FeatureLevels),
                            D3D11_SDK_VERSION,
                            &m_pD3D11Device,
                            &pFeatureLevelsOut,
                            &m_pD3D11Ctx);

    if (FAILED(hres))
        return MFX_ERR_DEVICE_FAILED;

    m_pDXGIDev = m_pD3D11Device;
    m_pDX11VideoDevice = m_pD3D11Device;
    m_pVideoContext = m_pD3D11Ctx;

    MSDK_CHECK_POINTER(m_pDXGIDev.p, MFX_ERR_NULL_PTR);
    MSDK_CHECK_POINTER(m_pDX11VideoDevice.p, MFX_ERR_NULL_PTR);
    MSDK_CHECK_POINTER(m_pVideoContext.p, MFX_ERR_NULL_PTR);

    // turn on multithreading for the Context
    CComQIPtr<ID3D10Multithread> p_mt(m_pVideoContext);

    if (p_mt)
        p_mt->SetMultithreadProtected(true);
    else
        return MFX_ERR_DEVICE_FAILED;

    // create swap chain only for rendering use case (hWindow != 0)
    if (hWindow)
    {
        MSDK_CHECK_POINTER(m_pDXGIFactory.p, MFX_ERR_NULL_PTR);
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {0};

        sts = FillSCD1(swapChainDesc);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

        hres = m_pDXGIFactory->CreateSwapChainForHwnd(m_pD3D11Device,
            (HWND)hWindow,
            &swapChainDesc,
            NULL,
            NULL,
            reinterpret_cast<IDXGISwapChain1**>(&m_pSwapChain));
        if (FAILED(hres))
            return MFX_ERR_DEVICE_FAILED;
    }

    return sts;
}


//
mfxStatus CMyD3D11Device::RenderFrame(mfxFrameSurface1 * pSrf, mfxFrameAllocator * pAlloc)
{
		//
#if  1
		//  2015/09/28
	    if  (  my_RenderFrame(  pSrf,  pAlloc  )  )  return  MFX_ERR_UNKNOWN;
		//
		#ifdef  _DEBUG
				//
				if  (  bShowRenderWnd(  )  )  {
					if  (  test_RenderFrame_1(  pSrf,  pAlloc  )  )  return  MFX_ERR_UNKNOWN;
				}
		#endif
		//
		return  MFX_ERR_NONE;
#endif

	//
    HRESULT hres = S_OK;
    mfxStatus sts;

    sts = CreateVideoProcessor(pSrf);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    hres = m_pSwapChain->GetBuffer(0, __uuidof( ID3D11Texture2D ), (void**)&m_pDXGIBackBuffer.p);
    if (FAILED(hres))
        return MFX_ERR_DEVICE_FAILED;

    D3D11_VIDEO_PROCESSOR_OUTPUT_VIEW_DESC OutputViewDesc;
    if (2 == m_nViews)
    {
        m_pVideoContext->VideoProcessorSetStreamStereoFormat(m_pVideoProcessor, 0, TRUE,D3D11_VIDEO_PROCESSOR_STEREO_FORMAT_SEPARATE,
            TRUE, TRUE, D3D11_VIDEO_PROCESSOR_STEREO_FLIP_NONE, NULL);
        m_pVideoContext->VideoProcessorSetOutputStereoMode(m_pVideoProcessor,TRUE);

        OutputViewDesc.ViewDimension = D3D11_VPOV_DIMENSION_TEXTURE2DARRAY;
        OutputViewDesc.Texture2DArray.ArraySize = 2;
        OutputViewDesc.Texture2DArray.MipSlice = 0;
        OutputViewDesc.Texture2DArray.FirstArraySlice = 0;
    }
    else
    {
        OutputViewDesc.ViewDimension = D3D11_VPOV_DIMENSION_TEXTURE2D;
        OutputViewDesc.Texture2D.MipSlice = 0;
    }

    if (1 == m_nViews || 0 == pSrf->Info.FrameId.ViewId)
    {
        hres = m_pDX11VideoDevice->CreateVideoProcessorOutputView(
            m_pDXGIBackBuffer,
            m_VideoProcessorEnum,
            &OutputViewDesc,
            &m_pOutputView.p );
        if (FAILED(hres))
            return MFX_ERR_DEVICE_FAILED;
    }

    D3D11_VIDEO_PROCESSOR_INPUT_VIEW_DESC InputViewDesc;
    InputViewDesc.FourCC = 0;
    InputViewDesc.ViewDimension = D3D11_VPIV_DIMENSION_TEXTURE2D;
    InputViewDesc.Texture2D.MipSlice = 0;
    InputViewDesc.Texture2D.ArraySlice = 0;

    mfxHDLPair pair = {NULL};
    sts = pAlloc->GetHDL(pAlloc->pthis, pSrf->Data.MemId, (mfxHDL*)&pair);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    ID3D11Texture2D  *pRTTexture2D = reinterpret_cast<ID3D11Texture2D*>(pair.first);
    D3D11_TEXTURE2D_DESC RTTexture2DDesc;

    if(!m_pTempTexture && m_nViews == 2)
    {
        pRTTexture2D->GetDesc(&RTTexture2DDesc);
        hres = m_pD3D11Device->CreateTexture2D(&RTTexture2DDesc,NULL,&m_pTempTexture.p);
        if (FAILED(hres))
            return MFX_ERR_DEVICE_FAILED;
    }

    // Creating input views for left and righ eyes
    if (1 == m_nViews)
    {
        hres = m_pDX11VideoDevice->CreateVideoProcessorInputView(
            pRTTexture2D,
            m_VideoProcessorEnum,
            &InputViewDesc,
            &m_pInputViewLeft.p );

    }
    else if (2 == m_nViews && 0 == pSrf->Info.FrameId.ViewId)
    {
        m_pD3D11Ctx->CopyResource(m_pTempTexture,pRTTexture2D);
        hres = m_pDX11VideoDevice->CreateVideoProcessorInputView(
            m_pTempTexture,
            m_VideoProcessorEnum,
            &InputViewDesc,
            &m_pInputViewLeft.p );
    }
    else
    {
        hres = m_pDX11VideoDevice->CreateVideoProcessorInputView(
            pRTTexture2D,
            m_VideoProcessorEnum,
            &InputViewDesc,
            &m_pInputViewRight.p );
    }
    if (FAILED(hres))
        return MFX_ERR_DEVICE_FAILED;

    //  NV12 surface to RGB backbuffer
    RECT rect = {0};
    rect.right  = pSrf->Info.CropW;
    rect.bottom = pSrf->Info.CropH;

    D3D11_VIDEO_PROCESSOR_STREAM StreamData;

    if (1 == m_nViews || pSrf->Info.FrameId.ViewId == 1)
    {
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
        StreamData.pInputSurfaceRight = m_nViews == 2 ? m_pInputViewRight : NULL;

        m_pVideoContext->VideoProcessorSetStreamSourceRect(m_pVideoProcessor, 0, true, &rect);
        m_pVideoContext->VideoProcessorSetStreamFrameFormat( m_pVideoProcessor, 0, D3D11_VIDEO_FRAME_FORMAT_PROGRESSIVE);
        hres = m_pVideoContext->VideoProcessorBlt( m_pVideoProcessor, m_pOutputView, 0, 1, &StreamData );
        if (FAILED(hres))
            return MFX_ERR_DEVICE_FAILED;
    }

    if (1 == m_nViews || 1 == pSrf->Info.FrameId.ViewId)
    {
        DXGI_PRESENT_PARAMETERS parameters = {0};
        hres = m_pSwapChain->Present1(0, 0, &parameters);
        if (FAILED(hres))
            return MFX_ERR_DEVICE_FAILED;
    }

    return MFX_ERR_NONE;
}



//  2016/04/13
#if  0
void  CMyD3D11Device::free_resource(  DEC_d3d11_devVar  *  pDevVar  )
{
	int  i;
	for  (  i  =  0;  i  <  mycountof(  pDevVar->sharedTexes  );  i  ++  )  {
		 SHARED_tex  *  pMem  =  &pDevVar->sharedTexes[i];
		 freeSharedTex(  pMem  );
	}
	for  (  i  =  0;  i  <  mycountof(  pDevVar->tmpDecTexes.mems  );  i  ++  )  {
		 TMP_dec_tex  *  pMem  =  &pDevVar->tmpDecTexes.mems[i];
		 MACRO_safeRelease(  pMem->m_pTex  );
	}

	//
	pDevVar->bInited_sharedTexes  =  FALSE;

	//
	return;

}
#endif




//
#define		M_getTexName_dec(  dwProcessId,  tn_sharedTex,  real_index,  tName,  cnt  )		_sntprintf(  tName,  cnt,  _T(  "qmstd%d-%d-%d"  ),  dwProcessId,  tn_sharedTex,  real_index  );


//  2015/10/21  //  from src to dst //  2016/04/09

#if  10
mfxStatus CMyD3D11Device::my_RenderFrame(mfxFrameSurface1 * pSrf, mfxFrameAllocator * pAlloc)
{
    HRESULT hres = S_OK;
    mfxStatus sts;
	HRESULT  hr;

    sts = CreateVideoProcessor(pSrf);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

#if  0
	hres = m_pSwapChain->GetBuffer(0, __uuidof( ID3D11Texture2D ), (void**)&m_pDXGIBackBuffer.p);
    if (FAILED(hres))
        return MFX_ERR_DEVICE_FAILED;
	D3D11_TEXTURE2D_DESC  kkDesc;
	m_pDXGIBackBuffer->GetDesc(  &kkDesc  );
#endif

	//
    D3D11_VIDEO_PROCESSOR_INPUT_VIEW_DESC InputViewDesc;
    InputViewDesc.FourCC = 0;
    InputViewDesc.ViewDimension = D3D11_VPIV_DIMENSION_TEXTURE2D;
    InputViewDesc.Texture2D.MipSlice = 0;
    InputViewDesc.Texture2D.ArraySlice = 0;

    mfxHDLPair pair = {NULL};
    sts = pAlloc->GetHDL(pAlloc->pthis, pSrf->Data.MemId, (mfxHDL*)&pair);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    ID3D11Texture2D  *pRTTexture2D = reinterpret_cast<ID3D11Texture2D*>(pair.first);

	//
	CMyDecPipeline  *  pDecPipeline  =  (  CMyDecPipeline  *  )m_var.pMyPipeline;		
	if  (  !pDecPipeline  )  {
		return  MFX_ERR_UNKNOWN;		
	}
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pDecPipeline->m_var.pQdcObjInfo;	
	if  (  !pQdcObjInfo  )  {
		return  MFX_ERR_UNKNOWN;		
	}
	//
	//  DEC_d3d11_devVar  *  pDevVar  =  (  DEC_d3d11_devVar  *  )m_var.pDEC_d3d11_devVar;
	QIS_trace_common  qtc  =  {0};

	//
	if  (  g_pf_decDev_my_RenderFrame  )  {
		PF_decDev_my_RenderFrame  pf  =  (  PF_decDev_my_RenderFrame  )g_pf_decDev_my_RenderFrame;
		pf(  pQdcObjInfo,  m_var.pDEC_d3d11_devVar,  m_pD3D11Device,  m_pD3D11Ctx,  m_pDX11VideoDevice,  m_pVideoContext,  m_VideoProcessorEnum,  m_pVideoProcessor,  pRTTexture2D,  pSrf->Info.CropW,  pSrf->Info.CropH,  m_nViews,  &pDecPipeline->m_var.pkts_sharedTexInfo,  	
			g_bShowDec_sharedTexStatus,  
			g_uiXql_player,
			&qtc  );
	}


	//
#if  0  //  2016/04/24
	//
	TCHAR  tBuf[128];

	//
	unsigned  short  usMaxFps_toShareBmp1  =  25;

	//	
	unsigned  int  uiFrameTimeInMs  =  1000  /  usMaxFps_toShareBmp1;
	if  (  !uiFrameTimeInMs  )  {
		tmp_showInfo(  _T(  "renderFrame failed, uiFrameTimeInMs is 0"  )  );
		return  MFX_ERR_UNKNOWN;
	}

	
	//
#define		MIN_ucMaxCnt_sharedTexes_dec		12						//  2016/04/08	//  18	//  2015/10/18	//  10	//  5
#define		MAX_ucMaxCnt_sharedTexes_dec		36						//  2016/04/08	//  18	//  2015/10/18	//  10	//  5


#define		DEFAULT_ucMaxCnt_sharedTexes_dec	12
	//
	unsigned  char  ucMaxCnt_expected  =  DEFAULT_ucMaxCnt_sharedTexes_dec;
	if  (  pDevVar->uiMax_intervalInMs_renderFrame  )  {
		unsigned  char  tmp_ucMaxCnt  =  M_get_ucMaxCnt(  pDevVar->uiMax_intervalInMs_renderFrame,  uiFrameTimeInMs  );
		if  (  tmp_ucMaxCnt  <  MIN_ucMaxCnt_sharedTexes_dec  )  tmp_ucMaxCnt  =  MIN_ucMaxCnt_sharedTexes_dec;
		if  (  tmp_ucMaxCnt  >  MAX_ucMaxCnt_sharedTexes_dec  )  tmp_ucMaxCnt  =  MAX_ucMaxCnt_sharedTexes_dec;
		if  (  tmp_ucMaxCnt  >  MAX_sharedTexes_dec  )  tmp_ucMaxCnt  =  MAX_sharedTexes_dec;
		//
		ucMaxCnt_expected  =  tmp_ucMaxCnt;
	}
	if  (  ucMaxCnt_expected  !=  pDevVar->ucMaxCnt_shared_pTexes  )  {
		decDev_free_resource(  pDevVar  );
	}

	//
	if(!pDevVar->bInited_sharedTexes  )
    {
		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "renderFrame: start to init sharedTexes, ucMaxCnt %d->%d"  ),  (  int  )pDevVar->ucMaxCnt_shared_pTexes,  (  int  )ucMaxCnt_expected  );
		tmp_showInfo(  tBuf  );
		//
#if  0
		unsigned  char  ucMaxCnt  =  ucMaxCnt_epQdcObjInfo->cfg.usMaxFps_toShareBmp  /  4;
		if  (  ucMaxCnt  <=  MIN_ucMaxCnt_sharedTexes_dec  )  ucMaxCnt  =  MIN_ucMaxCnt_sharedTexes_dec;
		if  (  ucMaxCnt  >  MAX_sharedTexes_dec  )  ucMaxCnt  =  MAX_sharedTexes_dec;
#endif
		//
		pDevVar->ucMaxCnt_shared_pTexes  =  ucMaxCnt_expected;
		//  这个 tn_sharedTex仅是一个随机数，暂时用GetTickCount(  )
		pDevVar->tn_sharedTex  =  GetTickCount(  );
		//
		pDevVar->dwProcessId  =  GetCurrentProcessId(  );

		//
		D3D11_TEXTURE2D_DESC dstTex2DDesc;
        pRTTexture2D->GetDesc(&dstTex2DDesc);
		//
#ifdef  _DEBUG
		if  (  !m_pTexture_intermediate  )  {
			dstTex2DDesc.Format  =  DXGI_FORMAT_B8G8R8A8_UNORM;
			dstTex2DDesc.Usage  =  D3D11_USAGE_DEFAULT;
			dstTex2DDesc.BindFlags  =  D3D11_BIND_RENDER_TARGET  |  D3D11_BIND_SHADER_RESOURCE;
			dstTex2DDesc.CPUAccessFlags  =  0;
			dstTex2DDesc.MiscFlags  =  0;
			//
			hres = m_pD3D11Device->CreateTexture2D(&dstTex2DDesc,NULL,&m_pTexture_intermediate.p);
			if (FAILED(hres))            
				return MFX_ERR_DEVICE_FAILED;

		}
#endif

		//
		int  i;

		//
		pDevVar->tmpDecTexes.ucMaxCnt_tmpDecTexes  =  mycountof(  pDevVar->tmpDecTexes.mems  );
		for  (  i  =  0;  i  <  pDevVar->tmpDecTexes.ucMaxCnt_tmpDecTexes;  i  ++  )  {
			dstTex2DDesc.Format  =  DXGI_FORMAT_B8G8R8A8_UNORM;
			dstTex2DDesc.Usage  =  D3D11_USAGE_DEFAULT;
			dstTex2DDesc.BindFlags  =  D3D11_BIND_RENDER_TARGET  |  D3D11_BIND_SHADER_RESOURCE;
			dstTex2DDesc.CPUAccessFlags  =  0;
			dstTex2DDesc.MiscFlags  =  0;
			//
			hres = m_pD3D11Device->CreateTexture2D(&dstTex2DDesc,NULL,&pDevVar->tmpDecTexes.mems[i].m_pTex);
			if (FAILED(hres))  {            
				tmp_showInfo(  _T(  "myRenderFrame failed, Create tmpTex failed"  )  );
				return MFX_ERR_DEVICE_FAILED;
			}
		}		


		//
		for  (  i  =  0;  i  <  pDevVar->ucMaxCnt_shared_pTexes;  i  ++  )  {
			//
			dstTex2DDesc.Format  =  DXGI_FORMAT_B8G8R8A8_UNORM;
			dstTex2DDesc.Usage  =  D3D11_USAGE_DEFAULT;
			dstTex2DDesc.BindFlags  =  D3D11_BIND_RENDER_TARGET  |  D3D11_BIND_SHADER_RESOURCE;
			dstTex2DDesc.CPUAccessFlags  =  0;
			dstTex2DDesc.MiscFlags  =  D3D11_RESOURCE_MISC_SHARED_NTHANDLE  |  D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;
			//
	        hres = m_pD3D11Device->CreateTexture2D(&dstTex2DDesc,NULL,&pDevVar->sharedTexes[i].m_shared_pTex);
	        if (FAILED(hres))  {
	            return MFX_ERR_DEVICE_FAILED;
			}

			//	
			//  2015/08/14
			IDXGIResource1  *  dxgiResource  =  0;
			hr  =  pDevVar->sharedTexes[i].m_shared_pTex->QueryInterface(  __uuidof(  IDXGIResource1  ),  reinterpret_cast< void ** >(&dxgiResource  )  );
			if  (  SUCCEEDED(  hr  )  )  {
				//
				TCHAR  tName[128];	//  _T(  "testTex"  )
				M_getTexName_dec(  pDevVar->dwProcessId,  pDevVar->tn_sharedTex,  i,  tName,  mycountof(  tName  )  );
				//
				hr  =  dxgiResource->CreateSharedHandle(  NULL,  DXGI_SHARED_RESOURCE_READ  |  DXGI_SHARED_RESOURCE_WRITE, tName,  &pDevVar->sharedTexes[i].g_sharedTex_handle  );
				dxgiResource->Release(  );
			}
			if  (  FAILED(  hr  )  )  {
				return  MFX_ERR_UNKNOWN;
			}
			//
			hr  =  pDevVar->sharedTexes[i].m_shared_pTex->QueryInterface(_uuidof(IDXGIKeyedMutex), (  void  **  )&pDevVar->sharedTexes[i].m_pDXGIKeyedMutex);
			if  (  FAILED(  hr  )  )  {
				return  MFX_ERR_UNKNOWN;
			}

		}

		//
		pDevVar->bInited_sharedTexes  =  TRUE;
    }

	//  2015/10/02
	if  (  1  !=  m_nViews  )  {
		return  MFX_ERR_UNKNOWN;
	}


	//
	if  (  pDevVar->tmpDecTexes.ucMaxCnt_tmpDecTexes  <=  0  ||  pDevVar->tmpDecTexes.ucMaxCnt_tmpDecTexes  >  mycountof(  pDevVar->tmpDecTexes.mems  )  )  {
		return  MFX_ERR_UNKNOWN;
	}
	int  real_index;
	real_index  =  pDevVar->tmpDecTexes.uiCnt_filled  %  pDevVar->tmpDecTexes.ucMaxCnt_tmpDecTexes;		
	//
	TMP_dec_tex  *  pTdt  =  &pDevVar->tmpDecTexes.mems[real_index];
	if  (  pTdt->bExists_sn  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Warning: tmptex[%d].tex already filled"  ),  real_index  );
		tmp_showInfo(  tBuf  );
	}
	
	{
			 PARAM_copyTex  param;
			 memset(  &param,  0,  sizeof(  param  )  );
			 param.g_pd3d11Device  =  this->m_pD3D11Device;
			 param.context  =  this->m_pD3D11Ctx;
			 //
			 param.m_pDX11VideoDevice  =  this->m_pDX11VideoDevice;			
			 param.m_pVideoContext  =  this->m_pVideoContext;
			 //
			 param.pVideoProcessorEnum  =  this->m_VideoProcessorEnum;			
			 param.m_pVideoProcessor  =  this->m_pVideoProcessor;
			 //
			 if  (  myCopyTex(  &param,  pSrf->Info.CropW,  pSrf->Info.CropH,  pRTTexture2D,  pTdt->m_pTex  )  )  {
				 tmp_showInfo(  _T(  "myRenderFrame err, myCopytex failed"  )  );
			 }
			 else  {
				   pTdt->bExists_sn  =  TRUE;
				   //
				   pTdt->tmp_sn  =  pDevVar->tmpDecTexes.uiCnt_filled;
				   //
				   pDevVar->tmpDecTexes.uiCnt_filled  ++  ;
			 }
	}
	
	//
	pDevVar->uiLoopCtrls  ++  ;
	//
	DWORD  dwTickCnt  =  GetTickCount(  );
	unsigned  int						uiIntervalInMs_renderFrame  =  0;
	if  (  pDevVar->dwLastTickCnt_renderFrame  )  {
		uiIntervalInMs_renderFrame  =  dwTickCnt  -  pDevVar->dwLastTickCnt_renderFrame;
		//
		pDevVar->uiNewMax_intervalInMs_renderFrame  =  max(  pDevVar->uiNewMax_intervalInMs_renderFrame,  uiIntervalInMs_renderFrame  );

		//
		if  (  pDevVar->uiNewMax_intervalInMs_renderFrame  >  pDevVar->uiMax_intervalInMs_renderFrame  
			||  dwTickCnt  -  pDevVar->dwStartTickCnt_toGetNew  >  5  *  60  *  1000  )  
		{
			//
			#ifdef  _DEBUG
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "max_intervalInMs_renderFrame changed, %dms -> %dms"  ),  pDevVar->uiMax_intervalInMs_renderFrame,  pDevVar->uiNewMax_intervalInMs_renderFrame  );
					tmp_showInfo(  tBuf  );
			#endif
			//
			pDevVar->uiMax_intervalInMs_renderFrame  =  pDevVar->uiNewMax_intervalInMs_renderFrame;
			pDevVar->dwStartTickCnt_toGetNew  =  dwTickCnt;
			pDevVar->uiNewMax_intervalInMs_renderFrame  =  0;
			//
		}
	}
	pDevVar->dwLastTickCnt_renderFrame  =  dwTickCnt;

	//
	//  2016/04/08		
	unsigned  int  uiSeqNo_lastRender  =  pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender;
	int  iDiff_sn  =  pDevVar->uiSeqNo_lastCopied  -  uiSeqNo_lastRender;

	//
	int  max_copied  =  0;
	//
	int			i_qNodes_left_ok_sharedTex  =  pDevVar->ucMaxCnt_shared_pTexes  -  2;  //12;	//  3		
	if  (  i_qNodes_left_ok_sharedTex  <  1  )  {
		tmp_showInfo(  _T(  "renderFrame failed, iQNodes_left_ok_sharedTex err"  )  );
		return  MFX_ERR_UNKNOWN;
	}
	//
	if  (  pDevVar->ucMaxCnt_shared_pTexes  >  MAX_ucMaxCnt_sharedTexes_dec  -  5  )  {
		if  (  iDiff_sn  >  g_uiXql_player  -  4  )  {
			int  iSleepInMs  =  15;	//  10;
			//
			if  (  g_bShowDec_sharedTexStatus  )  {
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "renderFrame: too big iDiff_sn %d, xql_ok %d, sleep %dms"  ),  iDiff_sn,  g_uiXql_player,  iSleepInMs  );
				tmp_showInfo(  tBuf  );
			}
			//
			Sleep(  iSleepInMs  );		
		}
	}
	//
	if  (  iDiff_sn  <  i_qNodes_left_ok_sharedTex  )  {
		max_copied  =  i_qNodes_left_ok_sharedTex  -  iDiff_sn;
		}
	else  {
		  unsigned  short  nDistance  =  pQdcObjInfo->cfg.usMaxFps_toShareBmp;
		  //if  (  !nDistance  ||  nDistance  >  5  )  nDistance  =  5;
		  nDistance  =  2;
		  
		  if  (  !(  pDevVar->uiLoopCtrls  %  nDistance  ) )  {
			  max_copied  =  1;	
		  }
	}
	if  (  !max_copied  )  {
#if  10
		real_index  =  pDevVar->tmpDecTexes.uiCnt_filled  %  pDevVar->tmpDecTexes.ucMaxCnt_tmpDecTexes;			
		//
		TMP_dec_tex  *  pTdt  =  &pDevVar->tmpDecTexes.mems[real_index];
		if  (  pTdt->bExists_sn  )  {
			max_copied  =  1;  // this means tmpDecTexes full.
		}
#endif
	}

	//
#ifdef  _DEBUG
		#if  0
			 max_copied  =  1;
			 tmp_showInfo(  _T( "max_copied set to 1"  )  );
		#endif
#endif
	//
	if  (  max_copied  )
	{
		//
		if  (  pDevVar->ucMaxCnt_shared_pTexes  <=  0  ||  pDevVar->ucMaxCnt_shared_pTexes  >  MAX_sharedTexes_dec  )  {
			return  MFX_ERR_UNKNOWN;	
		}
		
		int  i;
		//int  cnt_copied  =  0;
		//
		int  first_tmp  =  pDevVar->tmpDecTexes.uiCnt_filled  -  pDevVar->tmpDecTexes.ucMaxCnt_tmpDecTexes;
		if  (  first_tmp  <  0  )  first_tmp  =  0;
		//
		for  (  i  =  first_tmp;  i  <  pDevVar->tmpDecTexes.uiCnt_filled;  i  ++  )  {		
			 int  tmp_real_index  =  i  %  pDevVar->tmpDecTexes.ucMaxCnt_tmpDecTexes;
			 TMP_dec_tex  *  pTdt  =  &pDevVar->tmpDecTexes.mems[tmp_real_index];
			 if  (  !pTdt->bExists_sn  )  continue;
			
			 //
			 if  (  pDecPipeline->m_var.pkts_sharedTexInfo.ucCnt  >=  max_copied  )  {
				 break;
			 }
			 //			
			 if  (  pDecPipeline->m_var.pkts_sharedTexInfo.ucCnt  >=  mycountof(  pDecPipeline->m_var.pkts_sharedTexInfo.mems  )  )  {
				tmp_showInfo(  _T(  "renderFrame: cnt_pktsharedTexInfo is max"  )  );
				break;			
			 }
			 PKT_sharedTex_info  *  pPktSharedTexInfo  =  &pDecPipeline->m_var.pkts_sharedTexInfo.mems[pDecPipeline->m_var.pkts_sharedTexInfo.ucCnt];			
			 //
			 memset(  pPktSharedTexInfo,  0,  sizeof(  pPktSharedTexInfo[0]  )  );			

			 // to copyTex
			 //			
			 real_index  =  pDevVar->uiSeqNo_newSharedTex1  %  pDevVar->ucMaxCnt_shared_pTexes;
			 SHARED_tex  *  pSharedTex  =  &pDevVar->sharedTexes[real_index];
			 			
			 //			
			 UINT64  reqKey  =  CONST_send_reqKey;
			 UINT64  relKey  =  CONST_send_relKey;			
			 //
			 DWORD  dwWaitToInMs  =  0;	//  1000;
			 BOOL  bCopied  =  FALSE;
			 		
			 //
			 hr  =  pDevVar->sharedTexes[real_index].m_pDXGIKeyedMutex->AcquireSync(  reqKey,  dwWaitToInMs  );
			 if  (  SUCCEEDED(  hr  )  )  {
				 if  (  hr == static_cast<HRESULT>(WAIT_TIMEOUT)  )  {				

					 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "renderFrame: acquireSync timeout. warning. ucMaxCnt %d. real_index %d"  ),  (  int  )pDevVar->ucMaxCnt_shared_pTexes,  real_index  );
					tmp_showInfo(  tBuf  );

					}
				 else  {


					//
					//this->m_pD3D11Ctx->CopyResource(  this->m_pTexture_shared,  m_pTexture_intermediate  );
					PARAM_copyTex  param;
					memset(  &param,  0,  sizeof(  param  )  );
					param.g_pd3d11Device  =  this->m_pD3D11Device;
					param.context  =  this->m_pD3D11Ctx;
					//
					param.m_pDX11VideoDevice  =  this->m_pDX11VideoDevice;
					param.m_pVideoContext  =  this->m_pVideoContext;
					//
					param.pVideoProcessorEnum  =  this->m_VideoProcessorEnum;
					param.m_pVideoProcessor  =  this->m_pVideoProcessor;
					//
					ID3D11Texture2D  *  pTex_src  =  pTdt->m_pTex;	//  pRTTexture2D;
					//
					if  (  myCopyTex(  &param,  pSrf->Info.CropW,  pSrf->Info.CropH,  pTex_src,  pDevVar->sharedTexes[real_index].m_shared_pTex  )  )  {
						tmp_showInfo(  _T(  "mycopyTex failed"  )  );					
						}
					else  {
						  pTdt->bExists_sn  =  FALSE;
					}

					//
					bCopied  =  TRUE;
				
					//
					//			
					hr  =  pDevVar->sharedTexes[real_index].m_pDXGIKeyedMutex->ReleaseSync(  relKey  );
					if  (  FAILED(  hr  )  )  {
						tmp_showInfo(  _T(  "renderFrame: releaseSync failed, skipped"  )  );
					}				
				 }						
			 }
			 
			 //
			 pPktSharedTexInfo->ucMaxCnt_sharedTexes  =  pDevVar->ucMaxCnt_shared_pTexes;
			 pPktSharedTexInfo->dwProcessId  =  pDevVar->dwProcessId;
			 pPktSharedTexInfo->tn  =  pDevVar->tn_sharedTex;
			 if  (  bCopied  )  {  //2015/09/30
				 pPktSharedTexInfo->uiSeqNo  =  pDevVar->uiSeqNo_newSharedTex1;
				 pPktSharedTexInfo->bTexShared  =  TRUE;				
				 //  2016/04/13
				 //pPktSharedTexInfo->usIntervalInMs_renderFrame  =  uiIntervalInMs_renderFrame;
				 pPktSharedTexInfo->usMax_intervalInMs_renderFrame  =  pDevVar->uiMax_intervalInMs_renderFrame;
				 //
				 pSharedTex->uiSeqNo  =  pDevVar->uiSeqNo_newSharedTex1;
				 pSharedTex->bExists_sn  =  TRUE;				
				 //
				 pDevVar->uiSeqNo_lastCopied  =  pDevVar->uiSeqNo_newSharedTex1;				
				 //				
				 pDevVar->uiSeqNo_newSharedTex1  ++  ;

				//
				//  2016/04/09
				pDecPipeline->m_var.pkts_sharedTexInfo.ucCnt  ++  ;


				//
#if  0
				if  (  g_bShowDec_sharedTexStatus  )  {
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "renderFrame: sn %d ok. iDiff_sn from lastRender %d"  ),  pPktSharedTexInfo->uiSeqNo,  iDiff_sn  );
					tmp_showInfo(  tBuf  );
				}
#endif
				//
			    #ifdef  _DEBUG
						#if  0
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "renderFrame: sn %d ok. iDiff_sn from lastRender %d"  ),  pDecPipeline->m_var.pktSharedTexInfo.uiSeqNo,  iDiff_sn  );
							  tmp_showInfo(  tBuf  );
						#endif
				#endif



				}			
			 else  {

				  //
				  if  (  pSharedTex->bExists_sn  )  {

					  //
					  unsigned  int  uiSeqNo_lastRender  =  pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender;

					  //
					  if  (  pSharedTex->uiSeqNo  <=  uiSeqNo_lastRender  )  {  //  2015/10/06. 这里是表明已经被render弃用，所以自己清理掉。
						  //
						  hr  =  pDevVar->sharedTexes[real_index].m_pDXGIKeyedMutex->AcquireSync(  CONST_recv_reqKey,  dwWaitToInMs  );
						  if  (  SUCCEEDED(  hr  )  )  {
							  if  (  hr == static_cast<HRESULT>(WAIT_TIMEOUT)  )  {				
								  tmp_showInfo(  _T(  "renderFrame: acquireSync timeout, recv_reqKey."  )  );
								  }
							  else  {
								  //
								  hr  =  pDevVar->sharedTexes[real_index].m_pDXGIKeyedMutex->ReleaseSync(  CONST_recv_relKey  );
								if  (  FAILED(  hr  )  )  {
									  tmp_showInfo(  _T(  "renderFrame: releaseSync failed, recv_relkey, skipped"  )  );				
								  }
								  //
								  pSharedTex->bExists_sn  =  FALSE;
							  }
						  }
					  }
				  }

				  break;			
			 }			
		}

		
		//		
		if  (  !pDecPipeline->m_var.pkts_sharedTexInfo.ucCnt  )  {
					
			PKT_sharedTex_info  *  pPktSharedTexInfo  =  &pDecPipeline->m_var.pkts_sharedTexInfo.mems[pDecPipeline->m_var.pkts_sharedTexInfo.ucCnt];			
			//
			memset(  pPktSharedTexInfo,  0,  sizeof(  pPktSharedTexInfo[0]  )  );				
			//
			pPktSharedTexInfo->ucMaxCnt_sharedTexes  =  pDevVar->ucMaxCnt_shared_pTexes;				
			pPktSharedTexInfo->dwProcessId  =  pDevVar->dwProcessId;
			pPktSharedTexInfo->tn  =  pDevVar->tn_sharedTex;
			
			pPktSharedTexInfo->uiSeqNo  =  pDevVar->uiSeqNo_lastCopied;
			
			//  2016/04/13
			//pPktSharedTexInfo->usIntervalInMs_renderFrame  =  uiIntervalInMs_renderFrame;
			pPktSharedTexInfo->usMax_intervalInMs_renderFrame  =  pDevVar->uiMax_intervalInMs_renderFrame;

			
			//  2016/04/09
			pDecPipeline->m_var.pkts_sharedTexInfo.ucCnt  ++  ;

		}
		
	}

	//
	if  (  g_bShowDec_sharedTexStatus  )  {
		//_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "renderFrame: uiSeqNo_lastRender:  %d. ucMaxCnt %d. fps %d"  ),  pQdcObjInfo->var.decInfo.uiSeqNo_lastRender,  (  int  )m_var.ucMaxCnt_shared_pTexes,  (  int  )pQdcObjInfo->cfg.usMaxFps_toShareBmp  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "renderFrame: cnt_pkt_sharedTex %d. iDiff_sn %d. loopCtrl %d, tmpTex.cnt_filled %d, sn_lastCopied %d, sn_lastRender %d"  ),  (  int  )pDecPipeline->m_var.pkts_sharedTexInfo.ucCnt,  iDiff_sn,  pDevVar->uiLoopCtrls,  pDevVar->tmpDecTexes.uiCnt_filled,  pDevVar->uiSeqNo_lastCopied,  uiSeqNo_lastRender  );
		tmp_showInfo(  tBuf  );
	}
#endif

		//
#ifdef  _DEBUG
		//
		//
		if  (  bShowRenderWnd(  )  )  {
			 PARAM_copyTex  param;
			 memset(  &param,  0,  sizeof(  param  )  );
			 param.g_pd3d11Device  =  this->m_pD3D11Device;
			 param.context  =  this->m_pD3D11Ctx;
			 //
			 param.m_pDX11VideoDevice  =  this->m_pDX11VideoDevice;			
			 param.m_pVideoContext  =  this->m_pVideoContext;
			 //
			 param.pVideoProcessorEnum  =  this->m_VideoProcessorEnum;			
			 param.m_pVideoProcessor  =  this->m_pVideoProcessor;
			 //
			 if  (  myCopyTex(  &param,  pSrf->Info.CropW,  pSrf->Info.CropH,  pRTTexture2D,  this->m_pTexture_intermediate,  NULL  )  )  {
				 tmp_showInfo(  _T(  "myCopytex failed"  )  );
			 }
		}
#endif

#if  0
    // Creating input views for left and righ eyes
    if (1 == m_nViews)
    {
        hres = m_pDX11VideoDevice->CreateVideoProcessorInputView(
            pRTTexture2D,
            m_VideoProcessorEnum,
            &InputViewDesc,
            &m_pInputViewLeft_my.p );

    }
    if (FAILED(hres))
        return MFX_ERR_DEVICE_FAILED;


	D3D11_VIDEO_PROCESSOR_OUTPUT_VIEW_DESC OutputViewDesc;
	if (1 != m_nViews)  return  MFX_ERR_UNKNOWN;

    {
        OutputViewDesc.ViewDimension = D3D11_VPOV_DIMENSION_TEXTURE2D;
        OutputViewDesc.Texture2D.MipSlice = 0;
    }

	//	  
	if (1 == m_nViews || 0 == pSrf->Info.FrameId.ViewId)
    {
        hres = m_pDX11VideoDevice->CreateVideoProcessorOutputView(
            m_pTexture_intermediate,
            m_VideoProcessorEnum,
            &OutputViewDesc,
            &m_pOutputView_my.p );
        if (FAILED(hres))
            return MFX_ERR_DEVICE_FAILED;
    }



    //  NV12 surface to RGB backbuffer
    RECT rect = {0};
    rect.right  = pSrf->Info.CropW;
    rect.bottom = pSrf->Info.CropH;

    D3D11_VIDEO_PROCESSOR_STREAM StreamData;

    if (1 == m_nViews || pSrf->Info.FrameId.ViewId == 1)
    {

		//
        StreamData.Enable = TRUE;
        StreamData.OutputIndex = 0;
        StreamData.InputFrameOrField = 0;
        StreamData.PastFrames = 0;
        StreamData.FutureFrames = 0;
        StreamData.ppPastSurfaces = NULL;
        StreamData.ppFutureSurfaces = NULL;
        StreamData.pInputSurface = m_pInputViewLeft_my;
        StreamData.ppPastSurfacesRight = NULL;
        StreamData.ppFutureSurfacesRight = NULL;
        StreamData.pInputSurfaceRight = m_nViews == 2 ? m_pInputViewRight : NULL;

        m_pVideoContext->VideoProcessorSetStreamSourceRect(m_pVideoProcessor, 0, true, &rect);
        m_pVideoContext->VideoProcessorSetStreamFrameFormat( m_pVideoProcessor, 0, D3D11_VIDEO_FRAME_FORMAT_PROGRESSIVE);
        hres = m_pVideoContext->VideoProcessorBlt( m_pVideoProcessor, m_pOutputView_my, 0, 1, &StreamData );
		//
        if (FAILED(hres))
            return MFX_ERR_DEVICE_FAILED;

		//
		UINT64  reqKey  =  0;
		UINT64  relKey  =  1;
		//
		DWORD  dwWaitToInMs  =  0;	//  1000;
		BOOL  bCopied  =  FALSE;
		//
		hr  =  this->m_pDXGIKeyedMutex->AcquireSync(  reqKey,  dwWaitToInMs  );
		if  (  SUCCEEDED(  hr  )  )  {
			if  (  hr != static_cast<HRESULT>(WAIT_TIMEOUT)  )  {				
				//
				this->m_pD3D11Ctx->CopyResource(  this->m_pTexture_shared,  m_pTexture_intermediate  );
				bCopied  =  TRUE;
			}			
			//			
			hr  =  this->m_pDXGIKeyedMutex->ReleaseSync(  relKey  );
		}
		//
		if  (  bCopied  )  {  //2015/09/30
			CMyDecPipeline  *  pDecPipeline  =  (  CMyDecPipeline  *  )m_var.pMyDecPipeline;
			if  (  pDecPipeline  )  {
				pDecPipeline->m_var.bTexShared  =  TRUE;
			}
		}

    }
#endif


#if  0
    if (1 == m_nViews || 1 == pSrf->Info.FrameId.ViewId)
    {
        DXGI_PRESENT_PARAMETERS parameters = {0};
        hres = m_pSwapChain->Present1(0, 0, &parameters);
        if (FAILED(hres))
            return MFX_ERR_DEVICE_FAILED;
    }
#endif

    return MFX_ERR_NONE;
}
#endif

//
//  2015/10/21  //  from src to dst //  2016/04/09





//
#ifdef  _DEBUG

// from dst to wnd
mfxStatus CMyD3D11Device::test_RenderFrame_1(mfxFrameSurface1 * pSrf, mfxFrameAllocator * pAlloc)
{
	//

	//
    HRESULT hres = S_OK;
    mfxStatus sts;
	HRESULT  hr;

    sts = CreateVideoProcessor(pSrf);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    hres = m_pSwapChain->GetBuffer(0, __uuidof( ID3D11Texture2D ), (void**)&m_pDXGIBackBuffer.p);
    if (FAILED(hres))
        return MFX_ERR_DEVICE_FAILED;

    D3D11_VIDEO_PROCESSOR_OUTPUT_VIEW_DESC OutputViewDesc;
	if (1 != m_nViews) return  MFX_ERR_UNKNOWN;
    
    {
        OutputViewDesc.ViewDimension = D3D11_VPOV_DIMENSION_TEXTURE2D;
        OutputViewDesc.Texture2D.MipSlice = 0;
    }

    if (1 == m_nViews || 0 == pSrf->Info.FrameId.ViewId)
    {
        hres = m_pDX11VideoDevice->CreateVideoProcessorOutputView(
            m_pDXGIBackBuffer,
            m_VideoProcessorEnum,
            &OutputViewDesc,
            &m_pOutputView.p );
        if (FAILED(hres))
            return MFX_ERR_DEVICE_FAILED;
    }

    D3D11_VIDEO_PROCESSOR_INPUT_VIEW_DESC InputViewDesc;
    InputViewDesc.FourCC = 0;
    InputViewDesc.ViewDimension = D3D11_VPIV_DIMENSION_TEXTURE2D;
    InputViewDesc.Texture2D.MipSlice = 0;
    InputViewDesc.Texture2D.ArraySlice = 0;

#if  0
    mfxHDLPair pair = {NULL};
    sts = pAlloc->GetHDL(pAlloc->pthis, pSrf->Data.MemId, (mfxHDL*)&pair);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
#endif

    ID3D11Texture2D  *pRTTexture2D = NULL;	//  reinterpret_cast<ID3D11Texture2D*>(pair.first);
    D3D11_TEXTURE2D_DESC RTTexture2DDesc;

	//  2015/09/28
	pRTTexture2D  =  m_pTexture_intermediate;	//  m_pTexture_shared;

	//
    if(!m_pTempTexture && m_nViews == 2)
    {
        pRTTexture2D->GetDesc(&RTTexture2DDesc);
        hres = m_pD3D11Device->CreateTexture2D(&RTTexture2DDesc,NULL,&m_pTempTexture.p);
        if (FAILED(hres))
            return MFX_ERR_DEVICE_FAILED;
    }

    // Creating input views for left and righ eyes
    if (1 == m_nViews)
    {
        hres = m_pDX11VideoDevice->CreateVideoProcessorInputView(
            pRTTexture2D,
            m_VideoProcessorEnum,
            &InputViewDesc,
            &m_pInputViewLeft.p );

    }
    else if (2 == m_nViews && 0 == pSrf->Info.FrameId.ViewId)
    {
        m_pD3D11Ctx->CopyResource(m_pTempTexture,pRTTexture2D);
        hres = m_pDX11VideoDevice->CreateVideoProcessorInputView(
            m_pTempTexture,
            m_VideoProcessorEnum,
            &InputViewDesc,
            &m_pInputViewLeft.p );
    }
    else
    {
        hres = m_pDX11VideoDevice->CreateVideoProcessorInputView(
            pRTTexture2D,
            m_VideoProcessorEnum,
            &InputViewDesc,
            &m_pInputViewRight.p );
    }
    if (FAILED(hres))
        return MFX_ERR_DEVICE_FAILED;

    //  dst surface to RGB backbuffer
    RECT rect = {0};
    rect.right  = pSrf->Info.CropW;
    rect.bottom = pSrf->Info.CropH;

    D3D11_VIDEO_PROCESSOR_STREAM StreamData;

    if (1 == m_nViews || pSrf->Info.FrameId.ViewId == 1)
    {
		//
#if  0
		UINT64  reqKey  =  1;//0;
		UINT64  relKey  =  0;	//1;

		//
		hr  =  this->m_pDXGIKeyedMutex->AcquireSync(  reqKey,  1000  );
		if  (  FAILED(  hr  )  )  {
			return  MFX_ERR_UNKNOWN;
		}
#endif
		
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
        StreamData.pInputSurfaceRight = m_nViews == 2 ? m_pInputViewRight : NULL;

        m_pVideoContext->VideoProcessorSetStreamSourceRect(m_pVideoProcessor, 0, true, &rect);
        m_pVideoContext->VideoProcessorSetStreamFrameFormat( m_pVideoProcessor, 0, D3D11_VIDEO_FRAME_FORMAT_PROGRESSIVE);
        hres = m_pVideoContext->VideoProcessorBlt( m_pVideoProcessor, m_pOutputView, 0, 1, &StreamData );

		//
		//  hr  =  this->m_pDXGIKeyedMutex->ReleaseSync(  relKey  );

		//
        if (FAILED(hres))
            return MFX_ERR_DEVICE_FAILED;
    }

    if (1 == m_nViews || 1 == pSrf->Info.FrameId.ViewId)
    {
        DXGI_PRESENT_PARAMETERS parameters = {0};
        hres = m_pSwapChain->Present1(0, 0, &parameters);
        if (FAILED(hres))
            return MFX_ERR_DEVICE_FAILED;
    }

    return MFX_ERR_NONE;
}



#endif

