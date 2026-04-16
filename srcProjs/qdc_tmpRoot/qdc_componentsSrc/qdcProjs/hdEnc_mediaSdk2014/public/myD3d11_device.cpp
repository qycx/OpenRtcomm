

#if defined(_WIN32) || defined(_WIN64)
#include <tchar.h>
#include <windows.h>
#endif
#include <numeric>
#include <ctime>
#include <algorithm>
//#include "pipeline_decode.h"
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
//#include "pipeline_decode.h"
#include "sysmem_allocator.h"

//#include "../../sample_user_modules/plugin_api/plugin_loader.h"


#include	"qdcOpenCommon.h"
//#include	"myDecPipeline.h"

#include	"qisCompressProc.h"
#include	"myFunc_mediaSdk.h"
#include	"tmpGuiOpenFunc.h"

#include	"myD3d11_device.h"
//
#include	"qyDefs_open.h"
#include	"qisD3dDefs_open.h"
#include	"qisD3d_open.h"
#include	"qmcDirectX_open.h"

//
#include	"mypipeline_user.h"
#include	"myEncode_render.h"
#include	"tmpEncOpenFunc.h"


//
CMyD3D11Device::CMyD3D11Device(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	//		
	if  (  g_pf_ENC_d3d11_devVar_new  )  		
	{
		PF_ENC_d3d11_devVar_new  pf  =  (  PF_ENC_d3d11_devVar_new  )g_pf_ENC_d3d11_devVar_new;
		m_var.pENC_d3d11_devVar  =  pf(  );
	}

}


CMyD3D11Device::~CMyD3D11Device(  )
{
#if  0
	for  (  int  i  =  0;  i  <  mycountof(  m_var.devVar.mems  );  i  ++  )  {
		CLI_sharedTex  *  pMem  =  &m_var.devVar.mems[i];
		 free_CLI_sharedTex(  pMem  );
	}
	//
	MACRO_safeRelease(  m_var.devVar.sharedTex_to_srf.pVideoProcessorEnum  );
	MACRO_safeRelease(  m_var.devVar.sharedTex_to_srf.m_pVideoProcessor  );
	
	//
	MACRO_safeRelease(  m_var.devVar.g_pTexture_nv12  );
	MACRO_safeRelease(  m_var.devVar.g_pTexture_rgb  );
#endif
	//
	if  (  g_pf_ENC_d3d11_devVar_free  )  {
		PF_ENC_d3d11_devVar_free  pf  =  (  PF_ENC_d3d11_devVar_free  )g_pf_ENC_d3d11_devVar_free;
		pf(  &m_var.pENC_d3d11_devVar  );  
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

	//  2015/10/31
	// Direct3D 11.1
    {
		this->m_pd3d11Device1  =  this->m_pD3D11Device;
		if  (  this->m_pd3d11Device1  )  {
			this->m_pd3dImmediateContext1  =  this->m_pD3D11Ctx;
		}
    }



	//
    return sts;
}


//
//
//  2016/05/02	
#ifdef  _DEBUG
 int  test_encDev_YUVReader_myLoadNextFrame(	void  *  pQDC_OBJ_INFO,
						     void									*  pENC_d3d11_devVar,  				
							LP_ID3D11Device							   m_pD3D11Device,
							LP_ID3D11DeviceContext					   m_pD3D11Ctx,			
							//
							LP_ID3D11Device1						   m_pd3d11Device1,
							//
							LP_ID3D11VideoDevice					   m_pDX11VideoDevice,						   
							LP_ID3D11VideoContext					   m_pVideoContext,
							
							//
							PKT_sharedTex_info						*	pPktSharedTexInfo,

							//
							LP_ID3D11Texture2D							pRTTexture2D,
							LP_ID3D11RenderTargetView					pRTV,
							//
							int											m_nViews,
							//
							BOOL										g_bShowEnc_sharedTexStatus,
							//
							QIS_trace_common						*	pQtc
						   );
#endif




//  2015/10/30
int  CMyD3D11Device::CMySmplYUVReader_myLoadNextFrame_msdk(  unsigned  short  usPktResType,  void  *  p0_pInput,  void  *  p1_uiInputSize,  PARAM_CMySmplYUVReader_myLoadNextFrame_msdk  *  pParam,  mfxFrameAllocator * pAlloc)
{
	int  iErr  =  -1;
	mfxStatus  sts;
	
	PKT_sharedTex_info  *  pPktSharedTexInfo  =  (  PKT_sharedTex_info  *  )p0_pInput;
	if  (  !pPktSharedTexInfo  )  return  -1;

	if  (  !pParam  )  return  -1;
	mfxFrameSurface1  *  pSrf  =  pParam->pSurface;
	if  (  !pSrf  )  return  -1;

	//
	CMyUserPipeline  *  pPipeline  =  (  CMyUserPipeline  *  )m_var.pMyPipeline;
	if  (  !pPipeline  )  return  -1;
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pPipeline->m_var.pQdcObjInfo;
	if  (  !pQdcObjInfo  )  return  -1;

	//
	if  (  !this->m_pd3d11Device1  ||  !this->m_pd3dImmediateContext1  )  {
		tmp_showInfo(  _T(  "encV: device, yuvReader failed, m_pd3d11Device1 or m_pd3dImmediateContext1 is null"  )  );
		return  -1;
	}

	//
	if  (  pQdcObjInfo->cfg.v.iWidth_pic  !=  pSrf->Info.CropW
		||  pQdcObjInfo->cfg.v.iHeight_pic  !=  pSrf->Info.CropH  )
	{
		tmp_showInfo(  _T(  "encV: device, yuvReader failed, iW_pic,iH_pic != pSrf.cropW,cropH"  )  );
		return  -1;
	}


	
	

	//
	mfxHDLPair pair = {NULL};
    sts = pAlloc->GetHDL(pAlloc->pthis, pSrf->Data.MemId, (mfxHDL*)&pair);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    ID3D11Texture2D  *pRTTexture2D = reinterpret_cast<ID3D11Texture2D*>(pair.first);
	//
	LP_ID3D11RenderTargetView					pRTV  =  NULL;

	//
	QIS_trace_common							qtc  =  {0};

	//								
	int											m_nViews  =  1;	
	//		
	BOOL										g_bShowEnc_sharedTexStatus  =  FALSE;		

	//
	if  (  !g_pf_encDev_YUVReader_myLoadNextFrame  )  return  -1;	
	PF_encDev_YUVReader_myLoadNextFrame  pf  =  (  PF_encDev_YUVReader_myLoadNextFrame  )g_pf_encDev_YUVReader_myLoadNextFrame;
	
	//
#ifdef  _DEBUG
#if  0
	if  (  !g_pf_preForTest_encDev_YUVReader_myLoadNextFrame  )  return  -1;
	PF_preForTest_encDev_YUVReader_myLoadNextFrame  pf_preForTest  =  (  PF_preForTest_encDev_YUVReader_myLoadNextFrame  )g_pf_preForTest_encDev_YUVReader_myLoadNextFrame;
	if  (  pf_preForTest(  pQdcObjInfo,  m_var.pENC_d3d11_devVar  )  )  {
		return  -1;
	}
	pf  =  test_encDev_YUVReader_myLoadNextFrame;
#endif
#endif

	//
	PKT_sharedTex_info1  psi1;
	memset(&psi1, 0, sizeof(psi1));
	memcpy(&psi1, pPktSharedTexInfo, sizeof(PKT_sharedTex_info));
	//
	if  (  pf(  pQdcObjInfo,  m_var.pENC_d3d11_devVar,  m_pD3D11Device,  m_pD3D11Ctx,  m_pd3d11Device1,  m_pDX11VideoDevice,  m_pVideoContext,  &psi1,  		
		pRTTexture2D,  pRTV,  m_nViews,  g_bShowEnc_sharedTexStatus,  &qtc  )  )  								
	{
		tmp_showInfo(  qtc.errBuf  );
	}
	


#if  0  //  2016/05/02

	TCHAR  tBuf[128];


	//	
	D3D11_TEXTURE2D_DESC	rtt_desc;		
	pRTTexture2D->GetDesc(  &rtt_desc  );

	//
	if  (  rtt_desc.Width  <  pSrf->Info.Width  ||  rtt_desc.Height  <  pSrf->Info.Height  )  {
		tmp_showInfo(  _T(  "encV: device, yuvReader failed, rtt.w,h<pSrf.cropW,cropH"  )  );
		return  -1;
	}


	//
	//
	HRESULT  hr;
	ID3D11Device  *  g_pd3dDevice  =  this->m_pD3D11Device;
	ID3D11DeviceContext  *  pd3dImmediateContext  =  this->m_pD3D11Ctx;


	if  (  !m_var.devVar.bInited  )  {

		//  2015/11/02
		if  (  !m_var.devVar.sharedTex_to_srf.pVideoProcessorEnum  ||  !m_var.devVar.sharedTex_to_srf.m_pVideoProcessor  )  {
				
			//		
			int  CropW_i  =  pQdcObjInfo->cfg.v.iWidth_pic;		//  pSrf->Info.CropW;			
			int  CropH_i  =  pQdcObjInfo->cfg.v.iHeight_pic;	//  pSrf->Info.CropH;
				  
			//
			if  (  myCreateVideoProcessor(  this->m_pDX11VideoDevice,  CropW_i,  CropH_i,  &m_var.devVar.sharedTex_to_srf.pVideoProcessorEnum,  &m_var.devVar.sharedTex_to_srf.m_pVideoProcessor  )  )  {			
				goto  errLabel;				  
			}
		}

		//
		if  (  !m_var.devVar.g_pTexture_rgb  )  {		

			//
			D3D11_TEXTURE2D_DESC	desc;			
			memset(  &desc,  0,  sizeof(  desc  )  );									
			desc.Width  =  pSrf->Info.CropW;  //256;
			desc.Height  =  pSrf->Info.CropH;	//  256;
			desc.MipLevels  =  1;
			desc.ArraySize  =  1;															
			desc.Format  =  DXGI_FORMAT_R8G8B8A8_UNORM;	//  DXGI_FORMAT_NV12;
			//desc.Format  =  DXGI_FORMAT_NV12;
			desc.SampleDesc.Count  =  1;										 
			desc.Usage  =  D3D11_USAGE_DEFAULT;									
			desc.BindFlags  =  D3D11_BIND_RENDER_TARGET  |  D3D11_BIND_SHADER_RESOURCE;										 
			desc.CPUAccessFlags  =  0;	//  D3D11_CPU_ACCESS_WRITE;
			hr  =  g_pd3dDevice->CreateTexture2D(  &desc,  NULL,  &m_var.devVar.g_pTexture_rgb  );
			if  (  FAILED(  hr  )  )  goto  errLabel;
		}
		
		//
		if  (  !m_var.devVar.g_pTexture_nv12  )  {		
			D3D11_TEXTURE2D_DESC	desc;
			memset(  &desc,  0,  sizeof(  desc  )  );
			desc.Width  =  rtt_desc.Width;		//  pSrf->Info.CropW;  //256;
			desc.Height  =  rtt_desc.Height;	//  pSrf->Info.CropH;	//  256;
			desc.MipLevels  =  1;
			desc.ArraySize  =  1;
			desc.Format  =  DXGI_FORMAT_R8G8B8A8_UNORM;	//  DXGI_FORMAT_NV12;
			desc.Format  =  DXGI_FORMAT_NV12;
			desc.SampleDesc.Count  =  1;
			desc.Usage  =  D3D11_USAGE_DEFAULT;
			desc.BindFlags  =  D3D11_BIND_RENDER_TARGET  |  D3D11_BIND_SHADER_RESOURCE;
			desc.CPUAccessFlags  =  0;	//  D3D11_CPU_ACCESS_WRITE;
			hr  =  g_pd3dDevice->CreateTexture2D(  &desc,  NULL,  &m_var.devVar.g_pTexture_nv12  );
			if  (  FAILED(  hr  )  )  goto  errLabel;
		}


		//
		m_var.devVar.bInited  =  TRUE;
	}

	//
#ifdef  _DEBUG
#if  0
	test_CMySmplYUVReader_myLoadNextFrame_msdk(  usPktResType,  (  char  *  )p0_pInput,  (  unsigned  int  )p1_uiInputSize,  pParam,  pAlloc  );
	return  0;
#endif
#endif


	//
	PKT_sharedTex_info  cur_pktSharedTexInfo  =  *pPktSharedTexInfo;

	//
	//				
	if  (  cur_pktSharedTexInfo.ucMaxCnt_sharedTexes  <=  0  ||  cur_pktSharedTexInfo.ucMaxCnt_sharedTexes  >  mycountof(  m_var.devVar.mems  )  )  {			
		//
		tmp_showInfo(  _T(  "encDevice: loadNextFrame failed, cur_pktTex.ucMaxCnt is 0, or too big"  )  );				 
		//
		return  -1;					
	}

	//	
	//	
	
						
	//	
	int  real_index  =  cur_pktSharedTexInfo.uiSeqNo  %  cur_pktSharedTexInfo.ucMaxCnt_sharedTexes;		
	CLI_sharedTex  *  pMem  =  &m_var.devVar.mems[real_index];
	//
	if  (  pMem->pktSharedTexInfo.dwProcessId  !=  cur_pktSharedTexInfo.dwProcessId
		||  pMem->pktSharedTexInfo.tn  !=  cur_pktSharedTexInfo.tn  
		)
	{
			free_CLI_sharedTex(  pMem  );
			//
			pMem->pktSharedTexInfo  =  cur_pktSharedTexInfo;
			//
			pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender  =  0;
			//    2015/10/10
			tmp_showInfo(  _T(  "encV: processId or tn changed, pSharedTex released, sn_lastRender is set to 0"  )  );
	}
	//	
	if  (  !pMem->m_shared_pTex  )  {		
			TCHAR  tName[128];	//  _T(  "testTex"  )			
			M_getTexName_enc(  cur_pktSharedTexInfo.dwProcessId,  cur_pktSharedTexInfo.tn,  real_index,  tName,  mycountof(  tName  )  );				
			//		
			hr  =  this->m_pd3d11Device1->OpenSharedResourceByName(  tName,  DXGI_SHARED_RESOURCE_READ,  __uuidof(  ID3D11Texture2D),  (LPVOID  *)&pMem->m_shared_pTex  );
			if  (  FAILED(  hr  )  )  {
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "OpenSharedResourceByName failed, hr 0x%x"  ),  hr  );
				tmp_showInfo(  tBuf  );
				goto  errLabel;
			}			
	}
		
	//
	ID3D11Texture2D  *  g_pTex  =  pMem->m_shared_pTex;			
	//
	if  (  !pMem->m_pDXGIKeyedMutex  )  {		
			hr  =  g_pTex->QueryInterface(_uuidof(IDXGIKeyedMutex), (  void  **  )&pMem->m_pDXGIKeyedMutex);
			if  (  FAILED(  hr  )  )  {					
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "queryInterface keyedMutex failed, hr 0x%x"  ),  hr  );
				tmp_showInfo(  tBuf  );
				goto  errLabel;				
			}					
	}
			
	//	
	IDXGIKeyedMutex  *  pDXGIKeyedMutex  =  pMem->m_pDXGIKeyedMutex;
			

	//
	if  (  cur_pktSharedTexInfo.uiSeqNo  <=  pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender  )  {				
			//			
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encV.YUV.loadNextFrame failed: err, pkt.sn %d <= last.%d. "  ),  cur_pktSharedTexInfo.uiSeqNo,  pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender  );			
			tmp_showInfo(  tBuf  );		
			}
	else  {
			//		
			UINT64  reqKey  =  CONST_recv_reqKey;	//  1;				
			UINT64  relKey  =  CONST_recv_relKey;	//  0;							
			//
			DWORD  dwWaitToInMs  =  0;	//  1000;
							
			// Acquire a lock to the resource.						
			hr  =  pDXGIKeyedMutex->AcquireSync(reqKey, dwWaitToInMs);
			if  (  SUCCEEDED(  hr  )  )  {
				if  (  hr == static_cast<HRESULT>(WAIT_TIMEOUT)  )  {				

					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encV.YUVReader: acquireSync timeout. warning. ucMaxCnt %d. sn %d, real_ind %d"  ),  (  int  )cur_pktSharedTexInfo.ucMaxCnt_sharedTexes,  cur_pktSharedTexInfo.uiSeqNo,  real_index  );
					tmp_showInfo(  tBuf  );
					}
				else  {
					
					//
					int  iW  =  pQdcObjInfo->cfg.v.iWidth_pic;
					int  iH  =  pQdcObjInfo->cfg.v.iHeight_pic;
					

					PARAM_copyTex  param;												
					memset(  &param,  0,  sizeof(  param  )  );
					//
					param.g_pd3d11Device  =  this->m_pD3D11Device;							
					param.context  =  this->m_pD3D11Ctx;
					//
					param.m_pDX11VideoDevice  =  this->m_pDX11VideoDevice;
					param.m_pVideoContext  =  this->m_pVideoContext;
					//
					param.pVideoProcessorEnum  =  m_var.devVar.sharedTex_to_srf.pVideoProcessorEnum;
					param.m_pVideoProcessor  =  m_var.devVar.sharedTex_to_srf.m_pVideoProcessor;

					//
					{					
						//
											//  2015/11/02
					#ifdef  _DEBUG
							//tmp_DXUTSaveTextureToFile(  pd3dImmediateContext,  g_pTex,  FALSE,  _T(  "c:\\tttbbb\\encV.g_pTex.bmp"  )  );
					#endif

						myCopyTex(  &param,  iW,  iH,  g_pTex,  m_var.devVar.g_pTexture_rgb,  &qtc  );
						
					#ifdef  _DEBUG
							//tmp_DXUTSaveTextureToFile(  pd3dImmediateContext,  m_var.sharedTex.g_pTexture_rgb,  FALSE,  _T(  "c:\\tttbbb\\encV.g_pTex_rgb.bmp"  )  );
					#endif

					}

					//
					// Release the lock and specify a key.									
					hr  =  pDXGIKeyedMutex->ReleaseSync(relKey);					
					if  (  FAILED(  hr  )  )  {
						tmp_showInfo(  _T(  "encV.YUVReader: releaseSync failed, skipped"  )  );
					}
					

					//				
					//
					int  CropW_i  =  iW;
					int  CropH_i  =  iH;
					int  CropW_o  =  rtt_desc.Width;
					int  CropH_o  =  rtt_desc.Height;
									
					//
					RECT  rc_src  =  {0};
					rc_src.right  =  iW;
					rc_src.bottom  =  iH;
					RECT  rc_dst  =  {0};
					rc_dst  =  rc_src;

					//					
					if  (  myCopyTexEx(  &param,  CropW_i,  CropH_i,  CropW_o,  CropH_o,  rc_src,  rc_dst,  m_var.devVar.g_pTexture_rgb,  m_var.devVar.g_pTexture_nv12  )  )  {						
						OutputDebugString(  _T(  "myCopyTex failed\n"  )  );						
					}
						

				}					

				//
				//  2015/10/06
				pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender  =  cur_pktSharedTexInfo.uiSeqNo;

				//
				unsigned  char  ucbShowRenderStatus  =  FALSE;

				#if  0
					 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );				
					 if  (  pProcInfo  )  {
						 if  (  pProcInfo->cfg.v.debugStatusInfo.ucbShowRenderStatus  )  					
						 {					
						 }				
					 }
				#endif
				//
				#ifdef  _DEBUG
						ucbShowRenderStatus  =  TRUE;
				#endif
				//
				if  (  ucbShowRenderStatus  )  {
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encV.YUVReader: uiSeqNo_lastRender %d"  ),  cur_pktSharedTexInfo.uiSeqNo  );
					tmp_showInfo(  tBuf  );					
				}

			}					
		
	}
		

	//						
	pd3dImmediateContext->CopyResource(  pRTTexture2D,  m_var.devVar.g_pTexture_nv12  );

#endif


	//
	iErr  =  0;
errLabel:

	//


	return  iErr;
}


//
#ifdef  _DEBUG
int  CMyD3D11Device::test_CMySmplYUVReader_myLoadNextFrame_msdk(  unsigned  short  usPktResType,  char  *  pInput,  unsigned  int  uiInputSize,  PARAM_CMySmplYUVReader_myLoadNextFrame_msdk  *  pParam,  mfxFrameAllocator * pAlloc)
{
	int  iErr  =  -1;
	mfxStatus  sts;
	mfxFrameSurface1  *  pSrf  =  pParam->pSurface;


	mfxHDLPair pair = {NULL};
    sts = pAlloc->GetHDL(pAlloc->pthis, pSrf->Data.MemId, (mfxHDL*)&pair);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    ID3D11Texture2D  *pRTTexture2D = reinterpret_cast<ID3D11Texture2D*>(pair.first);

	//
	
			D3D11_TEXTURE2D_DESC	rtt_desc;
			pRTTexture2D->GetDesc(  &rtt_desc  );
			int  ii  =  0;

	


	//
	HRESULT  hr;
	ID3D11Device  *  g_pd3dDevice  =  this->m_pD3D11Device;
	ID3D11DeviceContext  *  pd3dImmediateContext  =  this->m_pD3D11Ctx;


	//
	ID3D11Texture2D  *  g_pTexture2  =  NULL;
	//ID3D11ShaderResourceView  *  g_pTextureRV2  =  NULL;

	{
			//
	D3D11_TEXTURE2D_DESC	desc;
	memset(  &desc,  0,  sizeof(  desc  )  );
	desc.Width  =  pSrf->Info.CropW;  //256;
	desc.Height  =  pSrf->Info.CropH;	//  256;
	desc.MipLevels  =  1;
	desc.ArraySize  =  1;
	desc.Format  =  DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count  =  1;
	desc.Usage  =  D3D11_USAGE_DYNAMIC;
	desc.BindFlags  =  D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags  =  D3D11_CPU_ACCESS_WRITE;
	hr  =  g_pd3dDevice->CreateTexture2D(  &desc,  NULL,  &g_pTexture2  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

#if  0
	D3D11_SHADER_RESOURCE_VIEW_DESC  srvDesc;
	D3D11_RESOURCE_DIMENSION type;
	g_pTexture2->GetType( &type );
	switch( type )
	{
		case D3D11_RESOURCE_DIMENSION_BUFFER:
			break;
		case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
			break;
		case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
			{
				D3D11_TEXTURE2D_DESC  desc;
				ID3D11Texture2D * pTexture2D = ( ID3D11Texture2D *)g_pTexture2;
				pTexture2D->GetDesc( &desc );

				srvDesc.Format = desc.Format;
				srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				srvDesc.Texture2D.MipLevels = desc.MipLevels;
				srvDesc.Texture2D.MostDetailedMip = desc.MipLevels - 1;

			}
			break;
		case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
			break;
		default:
			break;
	}
		ID3D11ShaderResourceView * pSRView = NULL;
	hr  =  g_pd3dDevice->CreateShaderResourceView( g_pTexture2,  &srvDesc, &pSRView );
	//	hr  =  g_pd3dDevice->CreateShaderResourceView( pCtx->test.g_pTexture2,  NULL, &pSRView );
	if  (  FAILED(  hr  )  )  goto  errLabel;
	g_pTextureRV2  =  pSRView;
#endif

	D3D11_MAPPED_SUBRESOURCE	mappedTex;
	pd3dImmediateContext->Map(  g_pTexture2,  D3D11CalcSubresource(  0,  0,  1  ),  D3D11_MAP_WRITE_DISCARD,  0,  &mappedTex  );
	UCHAR  *  pTexels  =  (  UCHAR  *  )mappedTex.pData;
	for  (  int  row  =  0;  row  <  desc.Height;  row  ++  )  {
		 int  rowStart  =  row  *  mappedTex.RowPitch;
		 for  (  int  col  =  0;  col  <  desc.Width;  col  ++  )  {
			  UINT  colStart  =  col  *  4;
			  pTexels[rowStart  +  colStart  +  0]  =  0;	//  255;
			  pTexels[rowStart  +  colStart  +  1]  =  0;	//128;
			  pTexels[rowStart  +  colStart  +  2]  =  255;	//  0;	//64;
			  pTexels[rowStart  +  colStart  +  3]  =  255;	//  32;
		 }
	}

	pd3dImmediateContext->Unmap(  g_pTexture2,  D3D11CalcSubresource(  0,  0,  1  )  );

	//



	}

	//
	//pd3dImmediateContext->CopyResource( pRTTexture2D,  g_pTexture2  );

#ifdef  _DEBUG

	hr  =  tmp_DXUTSaveTextureToFile(  pd3dImmediateContext,  g_pTexture2,  FALSE,  _T(  "c:\\tttbbb\\imagemmm2.bmp"  )  );

	
#endif


	//
	ID3D11Texture2D  *  g_pTexture3  =  NULL;
	ID3D11Texture2D  *  g_pTexture4  =  NULL;

	//ID3D11ShaderResourceView  *  g_pTextureRV2  =  NULL;

	{
			//
	D3D11_TEXTURE2D_DESC	desc;
	memset(  &desc,  0,  sizeof(  desc  )  );
	desc.Width  =  pSrf->Info.CropW;  //256;
	desc.Height  =  pSrf->Info.CropH;	//  256;
	desc.MipLevels  =  1;
	desc.ArraySize  =  1;
	desc.Format  =  DXGI_FORMAT_R8G8B8A8_UNORM;	//  DXGI_FORMAT_NV12;
	//desc.Format  =  DXGI_FORMAT_NV12;
	desc.SampleDesc.Count  =  1;
	desc.Usage  =  D3D11_USAGE_DEFAULT;
	desc.BindFlags  =  D3D11_BIND_RENDER_TARGET  |  D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags  =  0;	//  D3D11_CPU_ACCESS_WRITE;
	hr  =  g_pd3dDevice->CreateTexture2D(  &desc,  NULL,  &g_pTexture3  );
	if  (  FAILED(  hr  )  )  goto  errLabel;


	//
		hr  =  tmp_DXUTSaveTextureToFile(  pd3dImmediateContext,  g_pTexture3,  FALSE,  _T(  "c:\\tttbbb\\imagemmm3.0.bmp"  )  );


	//
	pd3dImmediateContext->CopyResource(  g_pTexture3,  g_pTexture2  );
	//pd3dImmediateContext->Flush(  );
	//
	#if  0
    if (1 == m_nViews || 1 == pSrf->Info.FrameId.ViewId)
    {
        DXGI_PRESENT_PARAMETERS parameters = {0};
        hr = m_pSwapChain->Present1(0, 0, &parameters);
        if (FAILED(hr))
            return MFX_ERR_DEVICE_FAILED;
    }
#endif

	//
	hr  =  tmp_DXUTSaveTextureToFile(  pd3dImmediateContext,  g_pTexture3,  FALSE,  _T(  "c:\\tttbbb\\imagemmm3.1.bmp"  )  );

	//
//		D3D11_TEXTURE2D_DESC	desc;
	memset(  &desc,  0,  sizeof(  desc  )  );
	desc.Width  =  rtt_desc.Width;//  pSrf->Info.CropW;  //256;
	desc.Height  =  rtt_desc.Height;	//pSrf->Info.CropH;	//  256;
	desc.MipLevels  =  1;
	desc.ArraySize  =  1;
	desc.Format  =  DXGI_FORMAT_R8G8B8A8_UNORM;	//  DXGI_FORMAT_NV12;
	desc.Format  =  DXGI_FORMAT_NV12;
	desc.SampleDesc.Count  =  1;
	desc.Usage  =  D3D11_USAGE_DEFAULT;
	desc.BindFlags  =  D3D11_BIND_RENDER_TARGET  |  D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags  =  0;	//  D3D11_CPU_ACCESS_WRITE;
	hr  =  g_pd3dDevice->CreateTexture2D(  &desc,  NULL,  &g_pTexture4  );
	if  (  FAILED(  hr  )  )  goto  errLabel;



	}

	//

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
				//myCopyTex(  &param,  pSrf->Info.CropW,  pSrf->Info.CropH,  g_pTexture3,  g_pTexture4  );
				  //myCopyTex(  &param,  pSrf->Info.CropW,  pSrf->Info.CropH,  g_pTexture3,  pRTTexture2D  );

				//
				

				
				RECT  rc_src  =  {0};
				rc_src.right  =  pSrf->Info.CropW;
				rc_src.bottom  =  pSrf->Info.CropH;
				RECT  rc_dst  =  {0};
				rc_dst  =  rc_src;
				myCopyTexEx(  &param,  pSrf->Info.CropW,  pSrf->Info.CropH,  rtt_desc.Width,  rtt_desc.Height,  rc_src,  rc_dst,  g_pTexture3,  g_pTexture4  );

				//
				pd3dImmediateContext->CopyResource(  pRTTexture2D,  g_pTexture4  );


	//
	iErr  =  0;
errLabel:

	//
	MACRO_safeRelease(  g_pTexture2  );
	MACRO_safeRelease(  g_pTexture3  );
	MACRO_safeRelease(  g_pTexture4  );





	return  iErr;
}
#endif


