

#ifndef  __qisChromaKeyEffect_open_h__
#define  __qisChromaKeyEffect_open_h__	//  {

//
//
#include	"tmp_d3d11_dev_open.h"


//
typedef  struct  __qisChromaKeyEffect_head_t	{
				 BOOL							bInited;
}		 QIS_chromaKeyEffect_head;



//
typedef  int  (  *PF_getSize_QIS_chromaKey_effect  )(  );
//
typedef  int  (  *PF_initQisChromaKeyEffect  )(  LP_ID3D11Device  g_pd3dDevice,  LP_ID3D11DeviceContext  pd3dImmediateContext,  LPCTSTR  fn_ck,  void  *  pQIS_chromaKey_effect  );
typedef  void  (  *PF_exitQisChromaKeyEffect  )(  void  *  pQIS_chromaKey_effect  );


//
typedef  HRESULT (  *PF_createQuad  )( LP_ID3D11Device pd3dDevice,  UINT uiTexX, UINT uiTexY,  void  *  pQIS_mats,  void  *  pQIS_quad );
typedef  void  (  *PF_freeQuad  )(  void  *  pQIS_quad  );

//
typedef  int  (  *PF_getOrtho2DMats  )(  float  w,  float  h,  void  *  pQIS_mats  );


//


#endif  //  }


