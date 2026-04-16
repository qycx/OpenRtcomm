

#ifndef  __qisChromaKeyEffect_h__	
#define  __qisChromaKeyEffect_h__	//  {

//
#include	"qisChromakeyEffect_open.h"

//
typedef  struct  __chromaKeyInputParams_t  {
				 //  MY_uniform	int									g_cfg_usCnt;


#ifdef  __USE_dx11__
				 ID3DX11EffectScalarVariable		*		p_g_cfg_usCnt;
				 //
				 ID3DX11EffectVectorVariable		*		p_g_cfg_keys_rgb_key;
				 
				 //
				 ID3DX11EffectVectorVariable		*		p_g_cfg_keys_hsl_key;
				 //
				 ID3DX11EffectScalarVariable		*		p_g_cfg_keys_alphaArray;

				 //
				 ID3DX11EffectScalarVariable		*		p_g_iImgW;
				 ID3DX11EffectScalarVariable		*		p_g_iImgH;

				 //
				 ID3DX11EffectScalarVariable		*		p_g_lBlurSize;

				 //
				 ID3DX11EffectScalarVariable		*		p_g_ws_preBlur;
				 ID3DX11EffectScalarVariable		*		p_g_ws_postBlur;
				 
				 //
				 ID3DX11EffectScalarVariable		*		p_g_tn_modified;
#endif



}		ChromaKey_inputParams;


//  2013/10/18
typedef  struct  __qisChromaKeyEffect_t								{
				 //
				 QIS_chromaKeyEffect_head							head;
					 
				 //
#ifdef  __USE_dx11__
					 					 

					 ID3DX11Effect							*       g_pEffect;					// = NULL;

					 ID3DX11EffectTechnique					*		g_pTechnique;				// = NULL;
					 ID3D11InputLayout						*		g_pVertexLayout;			// = NULL;

					 //
					 ID3DX11EffectTechnique					*		g_pTechnique_preBlur_x;		// = NULL;
					 ID3D11InputLayout						*		g_pVertexLayout_preBlur_x;	// = NULL;
					 //
					 ID3DX11EffectTechnique					*		g_pTechnique_preBlur_y;		// = NULL;
					 ID3D11InputLayout						*		g_pVertexLayout_preBlur_y;	// = NULL;
					 					 
					 //
					 ID3DX11EffectTechnique					*		g_pTechnique_chromaKey;		// = NULL;
					 ID3D11InputLayout						*		g_pVertexLayout_chromaKey;	// = NULL;
					 
					 //
					 ID3DX11EffectTechnique					*		g_pTechnique_postBlur_x;	// = NULL;
					 ID3D11InputLayout						*		g_pVertexLayout_postBlur_x;	// = NULL;
					 
					 //
					 ID3DX11EffectTechnique					*		g_pTechnique_postBlur_y;	// = NULL;
					 ID3D11InputLayout						*		g_pVertexLayout_postBlur_y;	// = NULL;

					 //
					 ID3DX11EffectTechnique					*		g_pTechnique_blend;			// = NULL;
					 ID3D11InputLayout						*		g_pVertexLayout_blend;		// = NULL;
					 
					 //
					 ID3DX11EffectTechnique					*		g_pTechnique_mask;		// = NULL;
					 ID3D11InputLayout						*		g_pVertexLayout_mask;	// = NULL;
					 
					 //
					 ID3DX11EffectMatrixVariable			*       g_pWorldVariable;			// = NULL;
					 ID3DX11EffectMatrixVariable			*       g_pViewVariable;			// = NULL;
					 ID3DX11EffectMatrixVariable			*       g_pProjectionVariable;		// = NULL;
					 ID3DX11EffectVectorVariable			*       g_pMeshColorVariable;		// = NULL;
					 ID3DX11EffectShaderResourceVariable	*		g_pDiffuseVariable;			// = NULL;
					 ID3DX11EffectShaderResourceVariable	*		g_pMaskVariable;			// = NULL;

#endif


					 //
					 ChromaKey_inputParams							inputParams;

					 //
#ifdef  __USE_dx11__
					 //
					 ID3D11Buffer							*		g_pVertexBuffer;			// = NULL;
					 ID3D11Buffer							*		g_pIndexBuffer;				// = NULL;
					 ID3D11ShaderResourceView				*       g_pTextureRV;				// = NULL;
					 //
					 ID3D11Buffer							*		g_pVertexBuffer2;			// = NULL;
					 ID3D11Buffer							*		g_pIndexBuffer2;			// = NULL;
					 ID3D11Texture2D						*		g_pTexture2;
					 ID3D11ShaderResourceView				*       g_pTextureRV2;				// = NULL;
					 
#endif
		
				 
}				 QIS_chromaKey_effect;

//
int  ChromaKey_inputParams_init(  QIS_chromaKey_effect  *  pQce,  ChromaKey_inputParams  *  pParams  );
void  ChromaKey_inputParams_exit(  QIS_chromaKey_effect  *  pQce,  ChromaKey_inputParams  *  pParams  );
//int  ChromaKey_inputParams_update(  void  *  pD3D_context,  void  *  pIMG_process_cfg,  ChromaKey_inputParams  *  pParams  );

//
extern  "C"  __declspec(  dllexport  )  int  getSize_QIS_chromaKey_effect(  );
extern  "C"  __declspec(  dllexport  )  int  initQisChromaKeyEffect(  ID3D11Device  *  g_pd3dDevice,  ID3D11DeviceContext  *  pd3dImmediateContext,  LPCTSTR  fn_ck,  QIS_chromaKey_effect  *  pQce  );
extern  "C"  __declspec(  dllexport  )  void  exitQisChromaKeyEffect(  QIS_chromaKey_effect  *  pQce  );





#endif  //  }



