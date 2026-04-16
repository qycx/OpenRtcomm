

#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>



#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qySyncCommProc.h"
#include	"qmcVideoCapture_isCli.h"



//
#include	"isCliHelpPublic.h"

//

#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
#include	"imgProcessPublic.h"
#include	"dlgTalkProc.h"
#include	"funcsForisCliHelp.h"
#include	"subtitlesCfg.h"

#include	"qmcDirectXPublic.h"



#include	"imgProcessPublic.h"
#include	"qyCusResTemp.h"
#include	"dlgTalkPublic.h"
#include	"isCliHelpPublic.h"
#include	"funcsforisCliHelp.h"

#include	"qmcCmdProc.h"

#include	"meshLoaderpublic.h"

#include	"qisD3d_open.h"
#include	"qisTexture.h"

//
#include	"isD3dFunc_public.h"



//
XMMATRIX  loadMY_MATRIX(  MY_MATRIX  *  p  )
{
	XMMATRIX  m;
	XMFLOAT4X4  mf4x4(  (  float  *  )p->m  );
	return  XMLoadFloat4x4(  &mf4x4  );
}

void  storeMY_MATRIX(  XMMATRIX  *  pM,  MY_MATRIX  *  pDst  )
{
	XMFLOAT4X4  mf4x4;
	XMStoreFloat4x4(  &mf4x4,  *pM  );
	memcpy(  pDst->m,  mf4x4.m,  sizeof(  pDst->m  )  );

	return;
}


//
//
#if  1
//
void ClearShaderResources11( ID3D11DeviceContext* pd3dDevice )
{
	// unload
	ID3D11ShaderResourceView* pNULLS[4] = {0,0,0,0};
	pd3dDevice->PSSetShaderResources( 0, 4, pNULLS );
	pd3dDevice->GSSetShaderResources( 0, 4, pNULLS );
	pd3dDevice->VSSetShaderResources( 0, 4, pNULLS );
}
#endif


//
int  get_pt_far_mats(  void  *  p0_reserved,  float x_screen,  float y_screen,  QIS_mats  *  pMats,  float  z_1,  XMVECTOR  *  pPt_far  )
{
	int				iErr  =  -1;
	

#ifdef  __USE_dx11__
	//
	XMVECTOR  pt_in;

	//
#if  0
	pt_in.x  =  x_screen;
	pt_in.y  =  y_screen;
	pt_in.z  =  1.0f;					//  Ô¶²ÃÃæ
#endif
	pt_in  =  XMVectorSet(  x_screen,  y_screen,  z_1,  0  );

	TCHAR  tBuf[1000];
	
	//
#if  0
	GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pCtx->pGBuf_d3d_isCli;
	if  (  pGBuf  )  {
		if  (  pGBuf->i3dType  ==  CONST_i3dType_d3d9  )  {
			pt_in.x  -=  0.5;
			pt_in.y  -=  0.5;
		}
	}
#endif

	//
	//D3DXVec3Unproject(  pPt_far, &pt_in,  &pMats->vp,  &pMats->matProj,  &pMats->matView,  &pMats->matWorld  );		
	XMVECTOR  pt_far  =  XMVector3Unproject(  pt_in,  pMats->vp.TopLeftX,  pMats->vp.TopLeftY,  pMats->vp.Width,  pMats->vp.Height,  pMats->vp.MinDepth,  pMats->vp.MaxDepth,  loadMY_MATRIX(  &pMats->matProj  ),  loadMY_MATRIX(  &pMats->matView  ),  loadMY_MATRIX(  &pMats->matWorld  )  );


	//  pPt_far->y  =  -pPt_far->y;
	// pPt_far->z  =  floor(  pPt_far->z  );
	
	float  x  =  XMVectorGetX(  pt_far  );
	float  y  =  XMVectorGetY(  pt_far  );
	float  z  =  XMVectorGetZ(  pt_far  );
	//z  =  floor(  z  );
	float  w  =  XMVectorGetW(  pt_far  );

	*pPt_far  =  XMVectorSet(  x,  y,  z,  w  );



	iErr  =  0;

#endif

	#ifdef  __USE_dx9__
	//
	D3DXVECTOR3  pt_in;

	//
	pt_in.x  =  x_screen;
	pt_in.y  =  y_screen;
	pt_in.z  =  1.0f;					//  Ô¶²ÃÃæ
	TCHAR  tBuf[1000];
	
	//
	GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pCtx->pGBuf_d3d_isCli;
	if  (  pGBuf  )  {
		if  (  pGBuf->i3dType  ==  CONST_i3dType_d3d9  )  {
			pt_in.x  -=  0.5;
			pt_in.y  -=  0.5;
		}
	}

	//
	D3DXVec3Unproject(  pPt_far, &pt_in,  &pMats->vp,  &pMats->matProj,  &pMats->matView,  &pMats->matWorld  );


	//  pPt_far->y  =  -pPt_far->y;
	pPt_far->z  =  floor(  pPt_far->z  );


	iErr  =  0;

#endif


	return  iErr;

}
