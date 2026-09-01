

#ifndef  __enc_d3d11_func_h__
#define  __enc_d3d11_func_h__	//  {


//
#include	"enc_d3d11_dev_open.h"


//	
typedef  struct												{

			//
			//  CCtxQyTmpl							*		pCtxQyTmpl_vt;
			ENC_d3d11_devVar_head							head;						//  2016/05/10

			//
			void									*		pQIS_chromaKey_effect;

			//
			BOOL											bInited_resource;
						
			//  这个在createTex时就要建立.
			struct  {
					ID3D11VideoProcessorEnumerator	*		pVideoProcessorEnum;			
					ID3D11VideoProcessor			*		m_pVideoProcessor;    
			}												sharedTex_to_srf;	//sharedTex_to_rgb,  rgb_to_nv12;

			//
			CLI_sharedTex									mems[MAX_sharedTexes_enc];

			//				
			ID3D11Texture2D							*		g_pTexture_rgb;
			ID3D11Texture2D							*		g_pTexture_nv12;

			//  2016/05/08
			QIS_mats										mats_quad;
			QIS_quad										quad;
	
}															ENC_d3d11_devVar;


//
extern  "C"  __declspec(  dllexport  )  void  *  ENC_d3d11_devVar_new(  );
extern  "C"  __declspec(  dllexport  )  void  ENC_d3d11_devVar_free(  void  **  ppENC_d3d11_devVar  );


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
						   );



#endif  //  }


