
#ifndef  __enc_d3d11_dev_open_h__
#define  __enc_d3d11_dev_open_h__	//  {

//
#include	"qisTrace_open.h"

//
#include	"tmp_d3d11_dev_open.h"

//
//
class  CCtxQyTmpl;


//
typedef  struct												{

			//
			CCtxQyTmpl								*		pCtxQyTmpl_vt;

}		 ENC_d3d11_devVar_head;


//
typedef  void  *  (  *PF_ENC_d3d11_devVar_new  )(  );
typedef  void  (  *PF_ENC_d3d11_devVar_free  )(  void  **  ppENC_d3d11_devVar  );


//
//  2016/05/02	
typedef  int  (  *PF_encDev_YUVReader_myLoadNextFrame  )(	void  *  pQDC_OBJ_INFO,
						     	void									*	pENC_d3d11_devVar,  				
								//
								LP_ID3D11Device								m_pD3D11Device,							
								LP_ID3D11DeviceContext						m_pD3D11Ctx,			
							
								//							
								LP_ID3D11Device1							m_pd3d11Device1,
							
								//
								LP_ID3D11VideoDevice						m_pDX11VideoDevice,						   							
								LP_ID3D11VideoContext						m_pVideoContext,							
							
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



//  2016/05/07
typedef  int  (  *PF_preForTest_encDev_YUVReader_myLoadNextFrame  )(	void  *  pQDC_OBJ_INFO,  void  *  pENC_d3d11_devVar  );  				







#endif  //  }



