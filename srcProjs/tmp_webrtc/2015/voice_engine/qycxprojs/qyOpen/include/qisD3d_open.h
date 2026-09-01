
#ifndef  __qisD3d_open_h__
#define  __qisD3d_open_h__	//  {


#include	"qisTrace_open.h"
#include	"qisD3dDefs_open.h"

//
#include	"tmp_d3d11_dev_open.h"


//
//  2014/10/26
typedef  struct  __myMATRIX_t										{
		         float m[4][4];				 
}		 MY_MATRIX;



//  2013/10/21
typedef  struct  __qisMats_t										{
				 MY_MATRIX											matWorld,  matView,  matProj;
				 //  
				 D3D11_VIEWPORT										vp;
}		 QIS_mats;



//
//  2016/05/05
typedef  struct  __qisQuad_t										{
				 //
				 #ifdef  __USE_dx10__
						ID3D10Buffer						*		g_pQuadVB10;
						ID3D10Buffer						*		g_pQuadIB10;				// = NULL;
				 #endif
						
				 //  2014/10/23
				 #ifdef  __USE_dx11__
						ID3D11Buffer						*		g_pQuadVB11;
						ID3D11Buffer						*		g_pQuadIB11;				// = NULL;
				 #endif

}		 QIS_quad;



//
 //
 typedef  struct  __param_copyTex_t									{
				  //
				  ID3D11Device								*		g_pd3d11Device;			// = NULL;
				  ID3D11DeviceContext						*		context;

				  //
				  ID3D11VideoDevice							*		m_pDX11VideoDevice;	
				  ID3D11VideoContext						*		m_pVideoContext;

				  //
				  ID3D11VideoProcessorEnumerator			*		pVideoProcessorEnum;
				  ID3D11VideoProcessor						*		m_pVideoProcessor;    
				  
				  //  
				  void										*		pQIS_chromaKey_effect;		//  201605/06

 }		  PARAM_copyTex;

 //
 int  myCreateVideoProcessor(  ID3D11VideoDevice  *  m_pDX11VideoDevice,  int  CropW,  int  CropH,  ID3D11VideoProcessorEnumerator  **  pm_pVideoProcessorEnum,  ID3D11VideoProcessor  **  pm_pVideoProcessor  );
 int  myCopyTex(  PARAM_copyTex  *  pParam,  int  CropW,  int  CropH,  ID3D11Texture2D  *  pTex_src,  ID3D11Texture2D  *  pTex_dst,  QIS_trace_common  *  pQtc  );


 //
 int  myCreateVideoProcessorEx(  ID3D11VideoDevice  *  m_pDX11VideoDevice,  int  CropW_i,  int  CropH_i,  int  CropW_o,  int  CropH_o,  ID3D11VideoProcessorEnumerator  **  pm_pVideoProcessorEnum,  ID3D11VideoProcessor  **  pm_pVideoProcessor  );
 int  myCopyTexEx(  PARAM_copyTex  *  pParam,  int  CropW_i,  int  CropH_i,  int  CropW_o,  int  CropH_o,  RECT  rect_src,  RECT  rect_dst,  ID3D11Texture2D  *  pTex_src,  ID3D11Texture2D  *  pTex_dst  );


 //
 //
typedef  struct  __sharedTex_t										{

				 ID3D11Texture2D							*		m_shared_pTex;
				 //  2016/05/05
				 ID3D11RenderTargetView						*		m_pRTV;

				 //
				 IDXGIKeyedMutex							*		m_pDXGIKeyedMutex;

				 //
				 HANDLE												g_sharedTex_handle;

				 //
				 unsigned  int										uiSeqNo;
				 BOOL												bExists_sn;

}		 SHARED_tex;

//
//  2015/10/03
typedef  struct  __cli_sharedTex_t									{
					 PKT_sharedTex_info								pktSharedTexInfo;
					 //
					 ID3D11Texture2D						*       m_shared_pTex;	
					 //
					 ID3D11ShaderResourceView				*		m_pSRV;
					 //
					 IDXGIKeyedMutex						*		m_pDXGIKeyedMutex;
}		 CLI_sharedTex;



//
void  freeSharedTex(  SHARED_tex  *  pMem  );
void  free_CLI_sharedTex(  CLI_sharedTex  *  pMem  );

//
typedef  int  (  *PF_myCopyTex_rtt  )(  PARAM_copyTex  *  pParam,  int  CropW,  int  CropH,  LP_ID3D11Texture2D  pTex_src,  LP_ID3D11ShaderResourceView  pSrv_src,  QIS_mats  *  pMats_quad,  QIS_quad  *  pQuad,  LP_ID3D11Texture2D   pTex_dst,  LP_ID3D11RenderTargetView  g_pRTV_dst,  QIS_trace_common  *  pQtc  );


#endif


