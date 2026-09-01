

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
//#include	"d3dx11effect.h"
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
#include	"dec_d3d11_func.h"


//
#if  1  //  def  _DEBUG
		#define  mfxStatus	int
		#define	 MFX_ERR_UNKNOWN -1
		#define  MFX_ERR_DEVICE_FAILED	-1
		#define  MFX_ERR_NONE			0


#endif


//
//extern  BOOL				g_bShowDec_sharedTexStatus;			//  2016/04/09
//extern  unsigned  int		g_uiXql_player;		

//
void  decDev_free_resource(  DEC_d3d11_devVar  *  pDevVar  );


//
extern  "C"  __declspec(  dllexport  )  void  *  DEC_d3d11_devVar_new(  )
{
	DEC_d3d11_devVar  *  p  =  NULL;
	int  size  =  sizeof(  DEC_d3d11_devVar  );
	p  =  (  DEC_d3d11_devVar  *  )malloc(  size  );
	if  (  !p  )  return  NULL;
	memset(  p,  0,  size  );
	return  p;
}

//
extern  "C"  __declspec(  dllexport  )  void  DEC_d3d11_devVar_free(  void  **  ppDEC_d3d11_devVar  )
{
	if  (  !ppDEC_d3d11_devVar  )  return;
	if  (  !*ppDEC_d3d11_devVar  )  return;
	DEC_d3d11_devVar  *  p  =  (  DEC_d3d11_devVar  *  )*ppDEC_d3d11_devVar;
	decDev_free_resource(  p  );
	free(  p  );
	*ppDEC_d3d11_devVar  =  NULL;
	return;	
}




//
void  decDev_free_resource(  DEC_d3d11_devVar  *  pDevVar  )
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



//
extern  "C"  __declspec(  dllexport  )  int  decDev_my_RenderFrame(	QDC_OBJ_INFO							*  pQdcObjInfo,
						     void									*  pDEC_d3d11_devVar,  				
							ID3D11Device							*  m_pD3D11Device,
							ID3D11DeviceContext						*  m_pD3D11Ctx,						   
							ID3D11VideoDevice						*  m_pDX11VideoDevice,						   
							ID3D11VideoContext						*  m_pVideoContext,
							ID3D11VideoProcessorEnumerator			*  m_VideoProcessorEnum,
							ID3D11VideoProcessor					*  m_pVideoProcessor,
							
							ID3D11Texture2D							*  pRTTexture2D,
							unsigned  short							   CropW,
							unsigned  short							   CropH,
							int										   m_nViews,
							//
							PKTS_sharedTexInfo_forYuvWriter			*  pPkts_sharedTexInfo,
							//
							BOOL										g_bShowDec_sharedTexStatus,
							unsigned  int								g_uiXql_player,
							//
							QIS_trace_common						*	pQtc
						   )
{
    HRESULT hres = S_OK;
    mfxStatus sts;
	HRESULT  hr;
	//
	DEC_d3d11_devVar						*  pDevVar  =  (  DEC_d3d11_devVar  *  )pDEC_d3d11_devVar;						   
	if  (  !pDevVar  )  return  -1;

	//
#if  0
    sts = CreateVideoProcessor(pSrf);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

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
	DEC_d3d11_devVar  *  pDevVar  =  &m_var.devVar;
#endif

	//
	TCHAR  tBuf[128];

	//
	unsigned  short  usMaxFps_toShareBmp1  =  25;

	//	
	unsigned  int  uiFrameTimeInMs  =  1000  /  usMaxFps_toShareBmp1;
	if  (  !uiFrameTimeInMs  )  {
		//
		if  (  pQtc  )  {
			M_qtc_tcsCat(  pQtc,  _T(  "renderFrame failed, uiFrameTimeInMs is 0"  )  );
		}
		//
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
		if  (  pQtc  )  {
			M_qtc_tcsCat(  pQtc,  tBuf  );
		}
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
#if  0  //  def  _DEBUG
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
				if  (  pQtc  )  {
					M_qtc_tcsCat(  pQtc,  _T(  "myRenderFrame failed, Create tmpTex failed"  )  );
				}
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
	        hres = m_pD3D11Device->CreateTexture2D(&dstTex2DDesc,NULL,&pDevVar->sharedTexes[i].m_shared_pTex11);
	        if (FAILED(hres))  {
	            return MFX_ERR_DEVICE_FAILED;
			}

			//	
			//  2015/08/14
			IDXGIResource1  *  dxgiResource  =  0;
			hr  =  pDevVar->sharedTexes[i].m_shared_pTex11->QueryInterface(  __uuidof(  IDXGIResource1  ),  reinterpret_cast< void ** >(&dxgiResource  )  );
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
			hr  =  pDevVar->sharedTexes[i].m_shared_pTex11->QueryInterface(_uuidof(IDXGIKeyedMutex), (  void  **  )&pDevVar->sharedTexes[i].m_pDXGIKeyedMutex);
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
		if  (  pQtc  )  {
			M_qtc_tcsCat(  pQtc,  tBuf  );
		}
	}
	
	{
			 PARAM_copyTex  param;
			 memset(  &param,  0,  sizeof(  param  )  );
			 param.g_pd3d11Device  =  m_pD3D11Device;
			 param.context  =  m_pD3D11Ctx;
			 //
			 param.m_pDX11VideoDevice  =  m_pDX11VideoDevice;			
			 param.m_pVideoContext  =  m_pVideoContext;
			 //
			 param.pVideoProcessorEnum  =  m_VideoProcessorEnum;			
			 param.m_pVideoProcessor  =  m_pVideoProcessor;
			 //
			 if  (  myCopyTex(  &param,  CropW,  CropH,  pRTTexture2D,  pTdt->m_pTex,  pQtc  )  )  {
				 if  (  pQtc  )  {
					 M_qtc_tcsCat(  pQtc,  _T(  "myRenderFrame err, myCopytex failed"  )  );
				 }
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
					if  (  pQtc  )  {
						M_qtc_tcsCat(  pQtc,  tBuf  );
					}
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
		if  (  pQtc  )  {
			M_qtc_tcsCat(  pQtc,  _T(  "renderFrame failed, iQNodes_left_ok_sharedTex err"  )  );
		}
		return  MFX_ERR_UNKNOWN;
	}
	//
	if  (  pDevVar->ucMaxCnt_shared_pTexes  >  MAX_ucMaxCnt_sharedTexes_dec  -  5  )  {
		if  (  iDiff_sn  >  g_uiXql_player  -  4  )  {
			int  iSleepInMs  =  15;	//  10;
			//
			if  (  g_bShowDec_sharedTexStatus  )  {
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "renderFrame: too big iDiff_sn %d, xql_ok %d, sleep %dms"  ),  iDiff_sn,  g_uiXql_player,  iSleepInMs  );
				if  (  pQtc  )  {
					M_qtc_tcsCat(  pQtc,  tBuf  );
				}
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
		  unsigned  short  nDistance  =  pQdcObjInfo->cfg.v.usMaxFps_toShareBmp;
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
			 if  (  pPkts_sharedTexInfo->ucCnt  >=  max_copied  )  {
				 break;
			 }
			 //			
			 if  (  pPkts_sharedTexInfo->ucCnt  >=  mycountof(  pPkts_sharedTexInfo->mems  )  )  {
				 if  (  pQtc  )  {
					 M_qtc_tcsCat(  pQtc,  _T(  "renderFrame: cnt_pktsharedTexInfo is max"  )  );
				 }
				break;			
			 }
			 PKT_sharedTex_info  *  pPktSharedTexInfo  =  &pPkts_sharedTexInfo->mems[pPkts_sharedTexInfo->ucCnt];			
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
					 if  (  pQtc  )  {
						 M_qtc_tcsCat(  pQtc,  tBuf  );
					 }

					}
				 else  {


					//
					//this->m_pD3D11Ctx->CopyResource(  this->m_pTexture_shared,  m_pTexture_intermediate  );
					PARAM_copyTex  param;
					memset(  &param,  0,  sizeof(  param  )  );
					param.g_pd3d11Device  =  m_pD3D11Device;
					param.context  =  m_pD3D11Ctx;
					//
					param.m_pDX11VideoDevice  =  m_pDX11VideoDevice;
					param.m_pVideoContext  =  m_pVideoContext;
					//
					param.pVideoProcessorEnum  =  m_VideoProcessorEnum;
					param.m_pVideoProcessor  =  m_pVideoProcessor;
					//
					ID3D11Texture2D  *  pTex_src  =  pTdt->m_pTex;	//  pRTTexture2D;
					//
					if  (  myCopyTex(  &param,  CropW,  CropH,  pTex_src,  pDevVar->sharedTexes[real_index].m_shared_pTex11,  pQtc  )  )  {
						if  (  pQtc  )  {
							M_qtc_tcsCat(  pQtc,  _T(  "mycopyTex failed"  )  );					
						}
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
						if  (  pQtc  )  {
							M_qtc_tcsCat(  pQtc,  _T(  "renderFrame: releaseSync failed, skipped"  )  );
						}
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
				pPkts_sharedTexInfo->ucCnt  ++  ;


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
								  if  (  pQtc  )  {
									  M_qtc_tcsCat(  pQtc,  _T(  "renderFrame: acquireSync timeout, recv_reqKey."  )  );
								  }
								  }
							  else  {
								  //
								  hr  =  pDevVar->sharedTexes[real_index].m_pDXGIKeyedMutex->ReleaseSync(  CONST_recv_relKey  );								
								  if  (  FAILED(  hr  )  )  {
									  if  (  pQtc  )  {
										  M_qtc_tcsCat(  pQtc,  _T(  "renderFrame: releaseSync failed, recv_relkey, skipped"  )  );				
									  }
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
		if  (  !pPkts_sharedTexInfo->ucCnt  )  {
					
			PKT_sharedTex_info  *  pPktSharedTexInfo  =  &pPkts_sharedTexInfo->mems[pPkts_sharedTexInfo->ucCnt];			
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
			pPkts_sharedTexInfo->ucCnt  ++  ;

		}
		
	}

	//
	if  (  g_bShowDec_sharedTexStatus  )  {
		//_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "renderFrame: uiSeqNo_lastRender:  %d. ucMaxCnt %d. fps %d"  ),  pQdcObjInfo->var.decInfo.uiSeqNo_lastRender,  (  int  )m_var.ucMaxCnt_shared_pTexes,  (  int  )pQdcObjInfo->cfg.usMaxFps_toShareBmp  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "renderFrame: cnt_pkt_sharedTex %d. iDiff_sn %d. loopCtrl %d, tmpTex.cnt_filled %d, sn_lastCopied %d, sn_lastRender %d"  ),  (  int  )pPkts_sharedTexInfo->ucCnt,  iDiff_sn,  pDevVar->uiLoopCtrls,  pDevVar->tmpDecTexes.uiCnt_filled,  pDevVar->uiSeqNo_lastCopied,  uiSeqNo_lastRender  );
		if  (  pQtc  )  {
			M_qtc_tcsCat(  pQtc,  tBuf  );
		}
	}


		//
#if  0  //  def  _DEBUG
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
			 if  (  myCopyTex(  &param,  pSrf->Info.CropW,  pSrf->Info.CropH,  pRTTexture2D,  this->m_pTexture_intermediate  )  )  {
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
