

#ifndef  __isD3dFunc_public_h__
#define  __isD3dFunc_public_h__	//  {

//
extern  "C"  __declspec(  dllexport  )  int  getOrtho2DMats(  float  w,  float  h,  QIS_mats  *  pMats  );


//
//
extern  "C"  __declspec(  dllexport  )  HRESULT createQuad( ID3D11Device* pd3dDevice,  UINT uiTexX, UINT uiTexY,  QIS_mats  *  pMats,  QIS_quad  *  pQuad );
extern  "C"  __declspec(  dllexport  )  void  freeQuad(  QIS_quad  *  pQuad  );
//
extern  "C"  __declspec(  dllexport  )  HRESULT tmp_createQuad( ID3D11Device* pd3dDevice,  float  fl,  float  ft,  float  fu,  float  fv,  UINT uiTexX, UINT uiTexY,  QIS_mats  *  pMats,  QIS_quad  *  pQuad );


//
extern  "C"  __declspec(  dllexport  )  int  myCopyTex_rtt(  PARAM_copyTex  *  pParam,  int  CropW,  int  CropH,  ID3D11Texture2D  *  pTex_src,  ID3D11ShaderResourceView  *  pSrv_src,  QIS_mats  *  pMats_quad,  QIS_quad  *  pQuad,  ID3D11Texture2D  *   pTex_dst,  ID3D11RenderTargetView  *	g_pRTV_dst,  QIS_trace_common  *  pQtc  );


//
extern  "C"  __declspec(  dllexport  )  int  myCopyTex_rtt_spriteBatch(  PARAM_copyTex  *  pParam,  void  *  pSprites11,  int  CropW,  int  CropH,  ID3D11Texture2D  *  pTex_src,  ID3D11ShaderResourceView  *  pSrv_src,  RECT  *  pSrcRc,  ID3D11Texture2D  *   pTex_dst,  ID3D11RenderTargetView  *	g_pRTV_dst,  QIS_trace_common  *  pQtc  );


#endif  }



