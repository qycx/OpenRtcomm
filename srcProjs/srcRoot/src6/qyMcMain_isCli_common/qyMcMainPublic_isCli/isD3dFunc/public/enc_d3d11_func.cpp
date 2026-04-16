
#include	"stdafx.h"
#if defined(_WIN32) || defined(_WIN64)
#include <tchar.h>
#include <windows.h>
#endif
#include <numeric>
#include <ctime>
#include <algorithm>

#include	"qisD3dDefs_open.h"

//#include	"DXUT.h"
// Standard Windows includes
//#define NOMINMAX
#include <windows.h>
#include <initguid.h>


// Direct3D11 includes
#include <d3dcommon.h>
#include <dxgi.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>

//
#ifdef  __USE_dx11__
#include	<d3d11.h>
#include	"d3dx11effect.h"
#endif

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
#include	"enc_d3d11_func.h"
//
#include	"qisChromaKeyEffect.h"
//
#include	"ctxQmcTmpl.h"
#include	"qisPropIdDefs.h"
#include	"isD3dFunc_public.h"


//
void  encDev_free_resource(  ENC_d3d11_devVar  *  pDevVar  );


//
extern  "C"  __declspec(  dllexport  )  void  *  ENC_d3d11_devVar_new(  )
{
	ENC_d3d11_devVar  *  p  =  NULL;
	int  size  =  sizeof(  ENC_d3d11_devVar  );
	p  =  (  ENC_d3d11_devVar  *  )malloc(  size  );
	if  (  !p  )  return  NULL;
	memset(  p,  0,  size  );
	return  p;
}

//
extern  "C"  __declspec(  dllexport  )  void  ENC_d3d11_devVar_free(  void  **  ppENC_d3d11_devVar  )
{
	if  (  !ppENC_d3d11_devVar  )  return;
	if  (  !*ppENC_d3d11_devVar  )  return;
	ENC_d3d11_devVar  *  p  =  (  ENC_d3d11_devVar  *  )*ppENC_d3d11_devVar;
	encDev_free_resource(  p  );

	//
	if  (  p->pQIS_chromaKey_effect  )  {
		exitQisChromaKeyEffect(  (  QIS_chromaKey_effect  *  )p->pQIS_chromaKey_effect  );  
		MACRO_safeFree(  p->pQIS_chromaKey_effect  );
	}


	//
	free(  p  );
	*ppENC_d3d11_devVar  =  NULL;
	return;	
}




//
void  encDev_free_resource(  ENC_d3d11_devVar  *  pDevVar  )
{
	int  i;

	if  (  !pDevVar  )  return;
	ENC_d3d11_devVar  &devVar  =  *pDevVar;

	//
	for  (  int  i  =  0;  i  <  mycountof(  devVar.mems  );  i  ++  )  {
		CLI_sharedTex  *  pMem  =  &devVar.mems[i];
		 free_CLI_sharedTex(  pMem  );
	}
	//
	MACRO_safeRelease(  devVar.sharedTex_to_srf.pVideoProcessorEnum  );
	MACRO_safeRelease(  devVar.sharedTex_to_srf.m_pVideoProcessor  );
	
	//
	MACRO_safeRelease(  devVar.g_pTexture_nv12  );
	MACRO_safeRelease(  devVar.g_pTexture_rgb  );

	//
	freeQuad(  &devVar.quad  );

	//
	devVar.bInited_resource  =  FALSE;

	//
	return;

}











//
//  2016/05/02	
extern  "C"  __declspec(  dllexport  )  int  encDev_YUVReader_myLoadNextFrame(	QDC_OBJ_INFO							*  pQdcObjInfo,
						     void									*  pENC_d3d11_devVar,  		
							 //
							ID3D11Device							*  m_pD3D11Device,
							ID3D11DeviceContext						*  m_pD3D11Ctx,			
							//
							ID3D11Device1							*  m_pd3d11Device1,
							//
							ID3D11VideoDevice						*  m_pDX11VideoDevice,						   
							ID3D11VideoContext						*  m_pVideoContext,
							
							//
							//PKT_sharedTex_info					*	pPktSharedTexInfo,
							PKT_sharedTex_info1						*	pPktSharedTexInfo,

							//
							ID3D11Texture2D							*  pRTTexture2D,
							ID3D11RenderTargetView					*  pRTV,		
							//
							int										   m_nViews,
							//
							BOOL									   g_bShowEnc_sharedTexStatus,
							//
							QIS_trace_common						*	pQtc
						   )

{
	int  iErr  =  -1;

	//
	ENC_d3d11_devVar  *  pDevVar  =  (  ENC_d3d11_devVar  *  )pENC_d3d11_devVar;
	if  (  !pDevVar  )  return  -1;
	ENC_d3d11_devVar  &  devVar  =  *  pDevVar;

	//
	CCtxQyTmpl  *  pCtx_vt  =  devVar.head.pCtxQyTmpl_vt;
	if  (  !pCtx_vt  )  {
		M_qtc_tcsCat(  pQtc,  _T(  "pCtx_vt is null"  )  );
		return  -1;
	}

	//			
	int  CropW_i  =  pQdcObjInfo->cfg.v.iWidth_pic;		//  pSrf->Info.CropW;						
	int  CropH_i  =  pQdcObjInfo->cfg.v.iHeight_pic;	//  pSrf->Info.CropH;


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
		int  size  =  sizeof(  QIS_chromaKey_effect  );
		devVar.pQIS_chromaKey_effect  =  malloc(  size  );
		if  (  !devVar.pQIS_chromaKey_effect  )  goto  errLabel;
		memset(  devVar.pQIS_chromaKey_effect,  0,  size  );
	}
	QIS_chromaKeyEffect_head  *  pQceHead  =  (  QIS_chromaKeyEffect_head  *  )devVar.pQIS_chromaKey_effect;
	if  (  !pQceHead->bInited  )  {
		exitQisChromaKeyEffect(  (  QIS_chromaKey_effect  *  )devVar.pQIS_chromaKey_effect  );  
		//
		TCHAR  fn_ck[MAX_PATH]  =  _T(  ""  );
		//
		if  (  !pCtx_vt->bGetStrProperty(  CONST_qdcPropId_fn_ck,  fn_ck,  mycountof(  fn_ck  )  )  )  {
			M_qtc_tcsCat(  pQtc,  _T(  "get fn_ck failed"  )  );
			goto  errLabel;
		}
		//
		if  (  initQisChromaKeyEffect(  g_pd3dDevice,  pd3dImmediateContext,  fn_ck,  (  QIS_chromaKey_effect  *  )devVar.pQIS_chromaKey_effect  )  )  {
			M_qtc_tcsCat(  pQtc,  _T(  "enc_dev_YUVRead failed, initChromaKeyEffect failed"  )  );
			goto  errLabel;
		}
	}




	//
	if  (  !devVar.bInited_resource  )  {
		//
		encDev_free_resource(  &devVar  );

		//
		switch  (  rtt_desc.Format  )  {
				case  DXGI_FORMAT_NV12:  {

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
					  }
					  break;
				default:  {
					      //
					       //
						  getOrtho2DMats(  CropW_i,  CropH_i,  &devVar.mats_quad  );
						  if  (  !devVar.quad.g_pQuadIB11  )  {
							  if  (  createQuad(  g_pd3dDevice,  CropW_i,  CropH_i,  &devVar.mats_quad,  &devVar.quad  )  )  {
								  M_qtc_tcsCat(  pQtc,  _T(  "encV: createQuad failed"  )  );
								  goto  errLabel;
							  }
						  }
					   }
					   break;
		}


		//
		devVar.bInited_resource  =  TRUE;
	}

	//
#ifdef  _DEBUG
#if  0
	test_CMySmplYUVReader_myLoadNextFrame_msdk(  usPktResType,  (  char  *  )p0_pInput,  (  unsigned  int  )p1_uiInputSize,  pParam,  pAlloc  );
	return  0;
#endif
#endif


	//
	PKT_sharedTex_info1  cur_pktSharedTexInfo;
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
			M_getTexName_enc(  cur_pktSharedTexInfo.dwProcessId,  cur_pktSharedTexInfo.index_mosaic,  cur_pktSharedTexInfo.tn,  real_index,  tName,  mycountof(  tName  )  );				
			//M_getTexName_enc( cur_pktSharedTexInfo.dwProcessId, cur_pktSharedTexInfo.tn, real_index, tName, mycountof(tName));
			//		
			hr  =  m_pd3d11Device1->OpenSharedResourceByName(  tName,  DXGI_SHARED_RESOURCE_READ,  __uuidof(  ID3D11Texture2D),  (LPVOID  *)&pMem->m_shared_pTex  );
			if  (  FAILED(  hr  )  )  {
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "OpenSharedResourceByName failed, hr 0x%x"  ),  hr  );
				//
				M_qtc_tcsCat(  pQtc,  tBuf  );
				//
				goto  errLabel;
			}
			//  2016/05/08
			{
						D3D11_SHADER_RESOURCE_VIEW_DESC  srvDesc;
						D3D11_RESOURCE_DIMENSION type;

						memset(  &srvDesc,  0,  sizeof(  srvDesc  )  );
						pMem->m_shared_pTex->GetType( &type );

						switch  (  type  )  {
								case D3D11_RESOURCE_DIMENSION_BUFFER:
									 break;
								case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
									 break;
								case D3D11_RESOURCE_DIMENSION_TEXTURE2D:			
									{
									D3D11_TEXTURE2D_DESC  desc;
									ID3D11Texture2D * pTexture2D = ( ID3D11Texture2D *)pMem->m_shared_pTex;
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
						hr  =  g_pd3dDevice->CreateShaderResourceView( pMem->m_shared_pTex,  &srvDesc, &pSRView );
						//	
						if  (  FAILED(  hr  )  )  goto  errLabel;
						pMem->m_pSRV  =  pSRView;
					}
	}
		
	//
	//ID3D11Texture2D  *  g_pTex  =  pMem->m_shared_pTex;			
	//
	if  (  !pMem->m_pDXGIKeyedMutex  )  {		
		hr  =  pMem->m_shared_pTex->QueryInterface(_uuidof(IDXGIKeyedMutex), (  void  **  )&pMem->m_pDXGIKeyedMutex);
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
					int  iW  =  pQdcObjInfo->cfg.v.iWidth_pic;
					int  iH  =  pQdcObjInfo->cfg.v.iHeight_pic;
					

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
					
					//  2016/05/08
					param.pQIS_chromaKey_effect  =  devVar.pQIS_chromaKey_effect;  //

					//
					switch  (  rtt_desc.Format  )  {
							case  DXGI_FORMAT_NV12:  {											
								  //
								  //  2015/11/02
								  #ifdef  _DEBUG
								          bool  usedds  =  false;
										  usedds  =  true;
										  //tmp_DXUTSaveTextureToFile(  pd3dImmediateContext,  pMem->m_shared_pTex,  usedds,  _T(  "c:\\tttbbb\\encV.g_pTex.dds"  )  );
								  #endif

								  //						
								  myCopyTex(  &param,  iW,  iH,  pMem->m_shared_pTex,  devVar.g_pTexture_rgb,  pQtc  );
						
								  #ifdef  _DEBUG
										  //tmp_DXUTSaveTextureToFile(  pd3dImmediateContext,  devVar.g_pTexture_rgb,  usedds,  _T(  "c:\\tttbbb\\encV.g_pTex_rgb.dds"  )  );
								  #endif
								  //
								  }
								  //
								  break;
							case  DXGI_FORMAT_B8G8R8A8_UNORM:  {
								  myCopyTex_rtt(  &param,  iW,  iH,  pMem->m_shared_pTex,  pMem->m_pSRV,  &devVar.mats_quad,  &devVar.quad,  pRTTexture2D,  pRTV,  pQtc  );
								  }
								  break;

							default:
								    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encV.YUVReader: unprocessed rtt.format %d"  ),  rtt_desc.Format  );
									M_qtc_tcsCat(  pQtc,  tBuf  );
									break;
					}

					//
					// Release the lock and specify a key.									
					hr  =  pDXGIKeyedMutex->ReleaseSync(relKey);					
					if  (  FAILED(  hr  )  )  {
						M_qtc_tcsCat(  pQtc,  _T(  "encV.YUVReader: releaseSync failed, skipped"  )  );
					}
					

					//
					switch  (  rtt_desc.Format  )  {
							case  DXGI_FORMAT_NV12:  {
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
						
								  //
								  //						
								  pd3dImmediateContext->CopyResource(  pRTTexture2D,  devVar.g_pTexture_nv12  );

								  }
								  //
								  break;
							default:
									break;									
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
						
						//
						//tmp_DXUTSaveTextureToFile(  pd3dImmediateContext,  devVar.g_pTexture_rgb,  true,  _T(  "c:\\tttbbb\\encV.pRtt2D.dds"  )  );



				#endif
				//
				if  (  ucbShowRenderStatus  )  {
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encV.YUVReader: uiSeqNo_lastRender %d"  ),  cur_pktSharedTexInfo.uiSeqNo  );
					//
					M_qtc_tcsCat(  pQtc,  tBuf  );					
				}

			}					
		
	}
		


	iErr  =  0;
errLabel:
	return  iErr;
}



