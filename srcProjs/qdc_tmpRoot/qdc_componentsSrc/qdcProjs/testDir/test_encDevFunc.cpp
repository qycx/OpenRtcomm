




#include	"stdafx.h"
#if defined(_WIN32) || defined(_WIN64)
#include <tchar.h>
#include <windows.h>
#endif
#include <numeric>
#include <ctime>
#include <algorithm>

#include	"qisD3dDefs_open.h"

//
#include <windows.h>
#include <initguid.h>


// Direct3D11 includes
#include <d3dcommon.h>
#include <dxgi.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>

//
#include	<d3d11.h>


//
#include	<DirectXMath.h>

//
#include	<WinSock2.h>



#include	<mmeapi.h>




#include	"qdcOpenCommon.h"

#include	"tmpGuiOpenFunc.h"

//
#include	"qyDefs_open.h"
#include	"qisD3dDefs_open.h"
#include	"qisD3d_open.h"
#include	"qmcDirectX_open.h"

//
//#include	"F:\qycx4\develop6\srcProjs\srcRoot\src6\qyMcMain_isCli\qyMcMainPublic_isCli\include\enc_d3d11_func.h"
//
#include	"tmpEncOpenFunc.h"
#include	"ctxQyTmpl.h"



//

//



//
//
//  2016/05/02	

#ifdef  _DEBUG
#if  0
//
//  2016/05/02	
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
						   )

{
	int  iErr  =  -1;

	//
	QDC_OBJ_INFO							*  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pQDC_OBJ_INFO;

	//
	ENC_d3d11_devVar  *  pDevVar  =  (  ENC_d3d11_devVar  *  )pENC_d3d11_devVar;
	if  (  !pDevVar  )  return  -1;
	ENC_d3d11_devVar  &  devVar  =  *  pDevVar;

	//
	CCtxQyTmpl  *  pCtx_vt  =  devVar.pCtxQyTmpl_vt;
	if  (  !pCtx_vt  )  {
		M_qtc_tcsCat(  pQtc,  _T(  "pCtx_vt is null"  )  );
		return  -1;
	}

	//			
	int  CropW_i  =  pQdcObjInfo->cfg.iWidth_pic;		//  pSrf->Info.CropW;						
	int  CropH_i  =  pQdcObjInfo->cfg.iHeight_pic;	//  pSrf->Info.CropH;


	//	
	D3D11_TEXTURE2D_DESC	rtt_desc;		
	pRTTexture2D->GetDesc(  &rtt_desc  );

	//
	//if  (  rtt_desc.Width  <  pSrf->Info.Width  ||  rtt_desc.Height  <  pSrf->Info.Height  )  
	if  (  rtt_desc.Width  <  CropW_i  ||  rtt_desc.Height  <  CropH_i  )  
	{
		M_qtc_tcsCat(  pQtc,  _T(  "encV: device, yuvReader failed, rtt.w,h<pSrf.cropW,cropH"  )  );
		return  -1;
	}


	//
	HRESULT  hr;
	ID3D11Device  *  g_pd3dDevice  =  m_pD3D11Device;
	ID3D11DeviceContext  *  pd3dImmediateContext  =  m_pD3D11Ctx;

	//
	TCHAR  tBuf[128]  =  _T(  ""  );

	//
	if  (  !devVar.pQIS_chromaKey_effect  )  {
		if  (  !g_pf_getSize_QIS_chromaKey_effect  )  goto  errLabel;
		int  size  =  g_pf_getSize_QIS_chromaKey_effect(  );
		devVar.pQIS_chromaKey_effect  =  malloc(  size  );
		if  (  !devVar.pQIS_chromaKey_effect  )  goto  errLabel;
		memset(  devVar.pQIS_chromaKey_effect,  0,  size  );
	}
	QIS_chromaKeyEffect_head  *  pQceHead  =  (  QIS_chromaKeyEffect_head  *  )devVar.pQIS_chromaKey_effect;
	if  (  !pQceHead->bInited  )  {
		if  (  !g_pf_exitQisChromaKeyEffect  )  goto  errLabel;

		g_pf_exitQisChromaKeyEffect(  pQceHead  );  

		//
		TCHAR  fn_ck[MAX_PATH]  =  _T(  ""  );
		//
		if  (  !pCtx_vt->bGetStrProperty(  CONST_qdcPropId_fn_ck,  fn_ck,  mycountof(  fn_ck  )  )  )  {
			M_qtc_tcsCat(  pQtc,  _T(  "get fn_ck failed"  )  );
			goto  errLabel;
		}
		//
		if  (  !g_pf_initQisChromaKeyEffect  )  goto  errLabel;
		PF_initQisChromaKeyEffect  pf  =  (  PF_initQisChromaKeyEffect  )g_pf_initQisChromaKeyEffect;
		if  (  pf(  g_pd3dDevice,  pd3dImmediateContext,  fn_ck,  pQceHead  )  )  {
			M_qtc_tcsCat(  pQtc,  _T(  "enc_dev_YUVRead failed, initChromaKeyEffect failed"  )  );
			goto  errLabel;
		}
	}




	//
	if  (  !devVar.bInited_sharedTexes  )  {

		//  2015/11/02
		if  (  !devVar.sharedTex_to_srf.pVideoProcessorEnum  ||  !devVar.sharedTex_to_srf.m_pVideoProcessor  )  {
				
				  
			//
			if  (  myCreateVideoProcessor(  m_pDX11VideoDevice,  CropW_i,  CropH_i,  &devVar.sharedTex_to_srf.pVideoProcessorEnum,  &devVar.sharedTex_to_srf.m_pVideoProcessor  )  )  {			
				//
				M_qtc_tcsCat(  pQtc,  _T(  "encV: myCreateVideoProcessor failed"  )  );
				//
				goto  errLabel;				  
			}
		}

		//
		if  (  !devVar.g_pTexture_rgb  )  {		

			//
			D3D11_TEXTURE2D_DESC	desc;			
			memset(  &desc,  0,  sizeof(  desc  )  );									
			desc.Width  =  CropW_i;		//  pSrf->Info.CropW;  //256;
			desc.Height  =  CropH_i;	//  pSrf->Info.CropH;	//  256;
			desc.MipLevels  =  1;
			desc.ArraySize  =  1;															
			desc.Format  =  DXGI_FORMAT_R8G8B8A8_UNORM;	//  DXGI_FORMAT_NV12;
			//desc.Format  =  DXGI_FORMAT_NV12;
			desc.SampleDesc.Count  =  1;										 
			desc.Usage  =  D3D11_USAGE_DEFAULT;									
			desc.BindFlags  =  D3D11_BIND_RENDER_TARGET  |  D3D11_BIND_SHADER_RESOURCE;										 
			desc.CPUAccessFlags  =  0;	//  D3D11_CPU_ACCESS_WRITE;
			hr  =  g_pd3dDevice->CreateTexture2D(  &desc,  NULL,  &devVar.g_pTexture_rgb  );
			if  (  FAILED(  hr  )  )  {
				//
				M_qtc_tcsCat(  pQtc,  _T(  "encV: CreateTexture2D rgb failed"  )  );
				//
				goto  errLabel;
			}
		}
		
		//
		if  (  !devVar.g_pTexture_nv12  )  {		
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
			hr  =  g_pd3dDevice->CreateTexture2D(  &desc,  NULL,  &devVar.g_pTexture_nv12  );
			if  (  FAILED(  hr  )  )  {
				//
				M_qtc_tcsCat(  pQtc,  _T(  "encV: CreateTexture2D nv12 failed"  )  );
				//
				goto  errLabel;
			}
		}


		//
		devVar.bInited_sharedTexes  =  TRUE;
	}

	//
#ifdef  _DEBUG
#if  0
	test_CMySmplYUVReader_myLoadNextFrame_msdk(  usPktResType,  (  char  *  )p0_pInput,  (  unsigned  int  )p1_uiInputSize,  pParam,  pAlloc  );
	return  0;
#endif
#endif


	//
	PKT_sharedTex_info  cur_pktSharedTexInfo;
	cur_pktSharedTexInfo  =  *pPktSharedTexInfo;

	//
	//				
	if  (  cur_pktSharedTexInfo.ucMaxCnt_sharedTexes  <=  0  ||  cur_pktSharedTexInfo.ucMaxCnt_sharedTexes  >  mycountof(  devVar.mems  )  )  {			
		//
		M_qtc_tcsCat(  pQtc,  _T(  "encDevice: loadNextFrame failed, cur_pktTex.ucMaxCnt is 0, or too big"  )  );				 
		//
		return  -1;					
	}

	//	
	//	
	
						
	//	
	int  real_index  =  cur_pktSharedTexInfo.uiSeqNo  %  cur_pktSharedTexInfo.ucMaxCnt_sharedTexes;		
	CLI_sharedTex  *  pMem  =  &devVar.mems[real_index];
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
			M_qtc_tcsCat(  pQtc,  _T(  "encV: processId or tn changed, pSharedTex released, sn_lastRender is set to 0"  )  );
	}
	//	
	if  (  !pMem->m_shared_pTex  )  {		
			TCHAR  tName[128];	//  _T(  "testTex"  )			
			M_getTexName_enc(  cur_pktSharedTexInfo.dwProcessId,  cur_pktSharedTexInfo.tn,  real_index,  tName,  mycountof(  tName  )  );				
			//		
			hr  =  m_pd3d11Device1->OpenSharedResourceByName(  tName,  DXGI_SHARED_RESOURCE_READ,  __uuidof(  ID3D11Texture2D),  (LPVOID  *)&pMem->m_shared_pTex  );
			if  (  FAILED(  hr  )  )  {
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "OpenSharedResourceByName failed, hr 0x%x"  ),  hr  );
				//
				M_qtc_tcsCat(  pQtc,  tBuf  );
				//
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
				M_qtc_tcsCat(  pQtc,  tBuf  );
				//
				goto  errLabel;				
			}					
	}
			
	//	
	IDXGIKeyedMutex  *  pDXGIKeyedMutex  =  pMem->m_pDXGIKeyedMutex;
			

	//
	if  (  cur_pktSharedTexInfo.uiSeqNo  <=  pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender  )  {				
			//			
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encV.YUV.loadNextFrame failed: err, pkt.sn %d <= last.%d. "  ),  cur_pktSharedTexInfo.uiSeqNo,  pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender  );		
			//
			M_qtc_tcsCat(  pQtc,  tBuf  );		
			//
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
					M_qtc_tcsCat(  pQtc,  tBuf  );
					}
				else  {
					
					//
					int  iW  =  pQdcObjInfo->cfg.iWidth_pic;
					int  iH  =  pQdcObjInfo->cfg.iHeight_pic;
					

					PARAM_copyTex  param;												
					memset(  &param,  0,  sizeof(  param  )  );
					//
					param.g_pd3d11Device  =  m_pD3D11Device;							
					param.context  =  m_pD3D11Ctx;
					//
					param.m_pDX11VideoDevice  =  m_pDX11VideoDevice;
					param.m_pVideoContext  =  m_pVideoContext;
					//
					param.pVideoProcessorEnum  =  devVar.sharedTex_to_srf.pVideoProcessorEnum;
					param.m_pVideoProcessor  =  devVar.sharedTex_to_srf.m_pVideoProcessor;

					//
					{					
						//
											//  2015/11/02
					#ifdef  _DEBUG
							//tmp_DXUTSaveTextureToFile(  pd3dImmediateContext,  g_pTex,  FALSE,  _T(  "c:\\tttbbb\\encV.g_pTex.bmp"  )  );
					#endif

						myCopyTex(  &param,  iW,  iH,  g_pTex,  devVar.g_pTexture_rgb,  pQtc  );
						
					#ifdef  _DEBUG
							//tmp_DXUTSaveTextureToFile(  pd3dImmediateContext,  m_var.sharedTex.g_pTexture_rgb,  FALSE,  _T(  "c:\\tttbbb\\encV.g_pTex_rgb.bmp"  )  );
					#endif

					}

					//
					// Release the lock and specify a key.									
					hr  =  pDXGIKeyedMutex->ReleaseSync(relKey);					
					if  (  FAILED(  hr  )  )  {
						M_qtc_tcsCat(  pQtc,  _T(  "encV.YUVReader: releaseSync failed, skipped"  )  );
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
					if  (  myCopyTexEx(  &param,  CropW_i,  CropH_i,  CropW_o,  CropH_o,  rc_src,  rc_dst,  devVar.g_pTexture_rgb,  devVar.g_pTexture_nv12  )  )  {						
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
						 if  (  pProcInfo->cfg.debugStatusInfo.ucbShowRenderStatus  )  					
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
					//
					M_qtc_tcsCat(  pQtc,  tBuf  );					
				}

			}					
		
	}
		

	//						
	pd3dImmediateContext->CopyResource(  pRTTexture2D,  devVar.g_pTexture_nv12  );

	iErr  =  0;
errLabel:
	return  iErr;
}
#endif
#endif




