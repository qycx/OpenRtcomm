
#ifndef  __dec_d3d11_dev_open_h__
#define  __dec_d3d11_dev_open_h__	//  {

//
#include	"qisTrace_open.h"

#include	"tmp_d3d11_dev_open.h"




//
 typedef  void  *  (  *PF_DEC_d3d11_devVar_new  )(  );
 typedef  void  (  *PF_DEC_d3d11_devVar_free  )(  void  **  ppDEC_d3d11_devVar  );
 typedef  int  (  *PF_decDev_my_RenderFrame  )(	void  *  pQDC_OBJ_INFO,
						     void									*  pDEC_d3d11_devVar,  				
							LP_ID3D11Device								m_pD3D11Device,
							LP_ID3D11DeviceContext						m_pD3D11Ctx,						   
							LP_ID3D11VideoDevice					   m_pDX11VideoDevice,						   
							LP_ID3D11VideoContext					   m_pVideoContext,
							LP_ID3D11VideoProcessorEnumerator		   m_VideoProcessorEnum,
							LP_ID3D11VideoProcessor					   m_pVideoProcessor,
							//							
							LP_ID3D11Texture2D							pRTTexture2D,
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
						   );

 //



#endif  //  }



