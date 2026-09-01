




#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

#include	"DXUT.h"
#include	"DXUTgui.h"
#include	"SDKmisc.h"

//  2014/10/23
#include	"D3dx11effect.h"


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

#include	"qisChromaKeyEffect.h"


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
//
extern  "C"  __declspec(  dllexport  )  int  getOrtho2DMats(  float  w,  float  h,  QIS_mats  *  pMats  )
 {
	 memset(  pMats,  0,  sizeof(  pMats  )  );

#ifdef  __USE_dx9__
	 
	 D3DXMATRIX  Identity;	
	 D3DXMatrixIdentity(  &Identity  );

	 pMats->matWorld  =  Identity;
	 pMats->matView  =  Identity;

	 //
	 D3DXMatrixOrthoLH(  &pMats->matProj,  w,  h,  0.0f,  1.0f  );

	 //	
	 D3DVIEWPORT9 PVP;
        
	 PVP.Width = w;
	 PVP.Height = h;
	 PVP.MinZ = 0;
	 PVP.MaxZ = 1;
	 PVP.X = 0;
	 PVP.Y = 0;

	 pMats->vp  =  PVP;
#endif

	 //  2014/10/24
#ifdef  __USE_dx11__
	 
	 XMMATRIX  Identity  =  XMMatrixIdentity(  );

	 storeMY_MATRIX(  &Identity,  &pMats->matWorld  );
	 storeMY_MATRIX(  &Identity,  &pMats->matView   );

	 //
	 //D3DXMATRIX  matProj;
	 //D3DXMatrixOrthoLH(  &matProj,  w,  h,  0.0f,  1.0f  );
	 
	 XMMATRIX  matProj  =  XMMatrixOrthographicLH(  w,  h,  0.0f,  1.0f  );
	 storeMY_MATRIX(  &matProj,  &pMats->matProj  );

	 //	
	 D3D11_VIEWPORT PVP;
        
	 PVP.Width = w;
	 PVP.Height = h;
	 PVP.MinDepth = 0;
	 PVP.MaxDepth = 1;
	 PVP.TopLeftX = 0;
	 PVP.TopLeftY = 0;

	 pMats->vp  =  PVP;
#endif

	 return  0;
 }


//
extern  "C"  __declspec(  dllexport  )  HRESULT createQuad( ID3D11Device* pd3dDevice,  UINT uiTexX, UINT uiTexY,  QIS_mats  *  pMats,  QIS_quad  *  pQuad )
{
    HRESULT hr = E_FAIL;

	//ID3D11Device* pd3dDevice  =  pCtx->g_pd3d11Device; 

    // First create space for the vertices
    UINT uiVertBufSize = 4*sizeof(SimpleVertex);
    SimpleVertex* pVerts = new SimpleVertex[ uiVertBufSize ];
    if( !pVerts )
        return E_OUTOFMEMORY;

	//
	float  ix  =  0;
	float  iy  =  0;
	float  iw  =  uiTexX;
	float  ih  =  uiTexY;
	POINT  point_lt,point_rt,point_lb,point_rb;
	POINT  realPoint_lt,realPoint_rt,realPoint_lb,realPoint_rb;

	point_lt.x  =  ix;
	point_lt.y  =  iy;
	
	point_rt.x  =  ix  + iw;
	point_rt.y  =  iy;

	point_lb.x  =  ix;
	point_lb.y  =  iy  +  ih;

	point_rb.x  =  ix  +  iw;
	point_rb.y  =  iy  +  ih;

	//
	realPoint_lt.x  =  ix;
	realPoint_lt.y  =  iy;
	
	realPoint_rt.x  =  ix  + iw;
	realPoint_rt.y  =  iy;

	realPoint_lb.x  =  ix;
	realPoint_lb.y  =  iy  +  ih;

	realPoint_rb.x  =  ix  +  iw;
	realPoint_rb.y  =  iy  +  ih;


	XMVECTOR  pt_far;
	float  fz  =  1.0;		//  2014/10/23

	//
	get_pt_far_mats( 0,  realPoint_lt.x,  realPoint_lt.y,  pMats,  fz,  &pt_far  );
	
	//
    int index=0;
    XMStoreFloat3(  &pVerts[index].Pos,  pt_far  );	//  D3DXVECTOR3( -1, -1, 0 );
    pVerts[index].Tex.x = 0;
    pVerts[index].Tex.y = 0;

	//		
	get_pt_far_mats(  0,  realPoint_rt.x,  realPoint_rt.y,  pMats,  fz,  &pt_far  );
	
    index++;
    XMStoreFloat3(  &pVerts[index].Pos,  pt_far  );	//  D3DXVECTOR3( -1, 1, 0 );
    pVerts[index].Tex.x = 1.;	//  0;
    pVerts[index].Tex.y = 0.;	//  uiTexY;

	//
	get_pt_far_mats(  0,  realPoint_rb.x,  realPoint_rb.y,  pMats,  fz,  &pt_far  );
	
    index++;
    XMStoreFloat3(  &pVerts[index].Pos,  pt_far  );	//  D3DXVECTOR3( 1, -1, 0 );
    pVerts[index].Tex.x = 1.;	//  uiTexX;
    pVerts[index].Tex.y = 1.;	//  0;

	//
	get_pt_far_mats(  0,  realPoint_lb.x,  realPoint_lb.y,  pMats,  fz,  &pt_far  );
	
    index++;
    XMStoreFloat3(  &pVerts[index].Pos,  pt_far  );	//  D3DXVECTOR3( 1, 1, 0 );
    pVerts[index].Tex.x = 0.;	//  uiTexX;
    pVerts[index].Tex.y = 1.;	//  uiTexY;

	//
    D3D11_BUFFER_DESC vbdesc =
    {
        uiVertBufSize,
        D3D11_USAGE_IMMUTABLE,
        D3D11_BIND_VERTEX_BUFFER,
        0,
        0
    };

    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = pVerts;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;
    hr = pd3dDevice->CreateBuffer( &vbdesc, &InitData, &pQuad->g_pQuadVB11 );
    if(FAILED(hr))  goto  errLabel;

	//
	DWORD indices[] =
    {
		0,1, 2,
        0,2, 3,
    };


	D3D11_BUFFER_DESC bd;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( DWORD ) * 6;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    InitData.pSysMem = indices;
	hr  =  ( pd3dDevice->CreateBuffer( &bd, &InitData, &pQuad->g_pQuadIB11 ) );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	//
	hr  =  S_OK;

errLabel:

	if  (  hr  !=  S_OK  )  {
		freeQuad(  pQuad  );
	}

	SAFE_DELETE_ARRAY( pVerts );
    
    return hr;
}


//  2016/05/17
extern  "C"  __declspec(  dllexport  )  HRESULT tmp_createQuad( ID3D11Device* pd3dDevice,  float  fl,  float  ft,  float  fu,  float  fv,  UINT uiTexX, UINT uiTexY,  QIS_mats  *  pMats,  QIS_quad  *  pQuad )
{
    HRESULT hr = E_FAIL;

	//ID3D11Device* pd3dDevice  =  pCtx->g_pd3d11Device; 

    // First create space for the vertices
    UINT uiVertBufSize = 4*sizeof(SimpleVertex);
    SimpleVertex* pVerts = new SimpleVertex[ uiVertBufSize ];
    if( !pVerts )
        return E_OUTOFMEMORY;

	//
	float  ix  =  0;
	float  iy  =  0;
	float  iw  =  uiTexX;
	float  ih  =  uiTexY;
	POINT  point_lt,point_rt,point_lb,point_rb;
	POINT  realPoint_lt,realPoint_rt,realPoint_lb,realPoint_rb;

	point_lt.x  =  ix;
	point_lt.y  =  iy;
	
	point_rt.x  =  ix  + iw;
	point_rt.y  =  iy;

	point_lb.x  =  ix;
	point_lb.y  =  iy  +  ih;

	point_rb.x  =  ix  +  iw;
	point_rb.y  =  iy  +  ih;

	//
	realPoint_lt.x  =  ix;
	realPoint_lt.y  =  iy;
	
	realPoint_rt.x  =  ix  + iw;
	realPoint_rt.y  =  iy;

	realPoint_lb.x  =  ix;
	realPoint_lb.y  =  iy  +  ih;

	realPoint_rb.x  =  ix  +  iw;
	realPoint_rb.y  =  iy  +  ih;


	XMVECTOR  pt_far;
	float  fz  =  1.0;		//  2014/10/23

	//
	get_pt_far_mats( 0,  realPoint_lt.x,  realPoint_lt.y,  pMats,  fz,  &pt_far  );
	
	//
    int index=0;
    XMStoreFloat3(  &pVerts[index].Pos,  pt_far  );	//  D3DXVECTOR3( -1, -1, 0 );
    pVerts[index].Tex.x = fl;	//  0;
    pVerts[index].Tex.y = ft;	//  0;

	//		
	get_pt_far_mats(  0,  realPoint_rt.x,  realPoint_rt.y,  pMats,  fz,  &pt_far  );
	
    index++;
    XMStoreFloat3(  &pVerts[index].Pos,  pt_far  );	//  D3DXVECTOR3( -1, 1, 0 );
    pVerts[index].Tex.x = fl  +  fu;	//  1.;	//  0;
    pVerts[index].Tex.y = ft;			//0.;	//  uiTexY;

	//
	get_pt_far_mats(  0,  realPoint_rb.x,  realPoint_rb.y,  pMats,  fz,  &pt_far  );
	
    index++;
    XMStoreFloat3(  &pVerts[index].Pos,  pt_far  );	//  D3DXVECTOR3( 1, -1, 0 );
    pVerts[index].Tex.x = fl  +  fu;	//  1.;	//  uiTexX;
    pVerts[index].Tex.y = ft  +  fv;	//  1.;	//  0;

	//
	get_pt_far_mats(  0,  realPoint_lb.x,  realPoint_lb.y,  pMats,  fz,  &pt_far  );
	
    index++;
    XMStoreFloat3(  &pVerts[index].Pos,  pt_far  );	//  D3DXVECTOR3( 1, 1, 0 );
    pVerts[index].Tex.x = fl;			//  0.;	//  uiTexX;
    pVerts[index].Tex.y = ft  +  fv;	//  1.;	//  uiTexY;

	//
    D3D11_BUFFER_DESC vbdesc =
    {
        uiVertBufSize,
        D3D11_USAGE_IMMUTABLE,
        D3D11_BIND_VERTEX_BUFFER,
        0,
        0
    };

    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = pVerts;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;
    hr = pd3dDevice->CreateBuffer( &vbdesc, &InitData, &pQuad->g_pQuadVB11 );
    if(FAILED(hr))  goto  errLabel;

	//
	DWORD indices[] =
    {
		0,1, 2,
        0,2, 3,
    };


	D3D11_BUFFER_DESC bd;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( DWORD ) * 6;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    InitData.pSysMem = indices;
	hr  =  ( pd3dDevice->CreateBuffer( &bd, &InitData, &pQuad->g_pQuadIB11 ) );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	//
	hr  =  S_OK;

errLabel:

	if  (  hr  !=  S_OK  )  {
		freeQuad(  pQuad  );
	}

	SAFE_DELETE_ARRAY( pVerts );
    
    return hr;
}




//
extern  "C"  __declspec(  dllexport  )  void  freeQuad(  QIS_quad  *  pQuad  )
{
	if  (  !pQuad  )  return;
	MACRO_safeRelease(  pQuad->g_pQuadIB11  );
	MACRO_safeRelease(  pQuad->g_pQuadVB11  );

	return;
}


//
#if  10
//--------------------------------------------------------------------------------------
void RenderToTexture11( ID3D11DeviceContext  *  pd3dDeviceContext,  
					  ID3D11RenderTargetView* pRTV, 
					  ID3D11ShaderResourceView* pSRV,
                      bool bClear, 
					  ID3DX11EffectTechnique* pTechnique,
					  ID3DX11EffectShaderResourceVariable* ptxSource,
					  ID3D11InputLayout* pInputLayout,
					  ID3D11Buffer* pVB,
					  ID3D11Buffer  *  pIB,
					  UINT iStride,
					  UINT iRTX,
					  UINT iRTY )
{
    // Clear if we need to
    if(bClear)
    {
        float ClearColor[4] = { 0.0, 0.0, 0.0, 0.0 };
        pd3dDeviceContext->ClearRenderTargetView( pRTV, ClearColor);
    }

    // Store the old viewport
    D3D11_VIEWPORT OldVP;
    UINT cRT = 1;
    pd3dDeviceContext->RSGetViewports( &cRT, &OldVP );

    if( pRTV )
    {
        // Set a new viewport that exactly matches the size of our 2d textures
        D3D11_VIEWPORT PVP;
        PVP.Width = iRTX;
		PVP.Height = iRTY;
        PVP.MinDepth = 0;
        PVP.MaxDepth = 1;
        PVP.TopLeftX = 0;
        PVP.TopLeftY = 0;
        pd3dDeviceContext->RSSetViewports( 1, &PVP );
    }

    // Set input params
    pd3dDeviceContext->IASetInputLayout( pInputLayout );
    UINT offsets = 0;
    UINT uStrides = iStride;
    pd3dDeviceContext->IASetVertexBuffers( 0, 1, &pVB, &uStrides, &offsets );
	//
	pd3dDeviceContext->IASetIndexBuffer( pIB, DXGI_FORMAT_R32_UINT, 0 );
	//
	pd3dDeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST  );  //D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

    // Set the render target and a NULL depth/stencil surface
    if( pRTV )
    {
        ID3D11RenderTargetView* aRTViews[] = { pRTV };
        pd3dDeviceContext->OMSetRenderTargets( 1, aRTViews, NULL );
    }

    D3DX11_TECHNIQUE_DESC techDesc;
    pTechnique->GetDesc( &techDesc );
    for( UINT p = 0; p < techDesc.Passes; ++p )
    {
        ptxSource->SetResource( pSRV );
        pTechnique->GetPassByIndex( p )->Apply(0,pd3dDeviceContext);
        //  pd3dDevice->Draw( 4, 0 );
		pd3dDeviceContext->DrawIndexed(  6,  0,  0  );
    }

	

    // Retore the original viewport
    pd3dDeviceContext->RSSetViewports( 1, &OldVP );
}

#endif


//
extern  "C"  __declspec(  dllexport  )  int  myCopyTex_rtt(  PARAM_copyTex  *  pParam,  int  CropW,  int  CropH,  ID3D11Texture2D  *  pTex_src,  ID3D11ShaderResourceView  *  pSrv_src,  QIS_mats  *  pMats_quad,  QIS_quad  *  pQuad,  ID3D11Texture2D  *   pTex_dst,  ID3D11RenderTargetView  *	g_pRTV_dst,  QIS_trace_common  *  pQtc  )
{
	//
	int  iErr  =  -1;

	D3D11_TEXTURE2D_DESC  src_desc,  dst_desc;

	//
	if  (  !pParam  )  {
		return  -1;
	}
	if  (  !g_pRTV_dst  )  {
		M_qtc_tcsCat(  pQtc,  _T(  "myCopyTex_rtt failed, pRTV_dst null"  )  );
		return  -1;
	}

	//
	pTex_dst->GetDesc(  &dst_desc  );
	pTex_src->GetDesc(  &src_desc  );

	//return  myCopyTex(  pParam,  CropW,  CropH,  pTex_src,  pTex_dst,  pQtc  );

	//
	ID3D11Device  *  pd3dDevice  =  pParam->g_pd3d11Device;
	ID3D11DeviceContext  *  context  =    pParam->context;

	//
	QIS_chromaKey_effect  *  pQce  =  (  QIS_chromaKey_effect  *  )pParam->pQIS_chromaKey_effect;
	if  (  !pQce  )  {
		M_qtc_tcsCat(  pQtc,  _T(  "pQIS_chromaKey_effect is null"  )  );
		return  -1;
	}


	//
	if  (  !CropW  ||  !CropH  )  return  -1;
	
	//	
	XMMATRIX                  g_World;		
	XMMATRIX                  g_View;
	XMMATRIX                  g_Projection;

	//
	HRESULT  hr;
	ID3D11RenderTargetView  *  g_pRTV  =  NULL;
						
	//
	g_pRTV  =  g_pRTV_dst;


	//		
	QIS_mats  mats_mask;		
	mats_mask  =  *pMats_quad;

	//			 		 
	//		
	g_World  =  loadMY_MATRIX(  &mats_mask.matWorld  );		
	g_View  =  loadMY_MATRIX(  &mats_mask.matView  );
	g_Projection  =  loadMY_MATRIX(  &mats_mask.matProj  );	 			 
	//	
	pQce->g_pWorldVariable->SetMatrix( (float*)&g_World );				
	pQce->g_pViewVariable->SetMatrix( (float*)&g_View );
	pQce->g_pProjectionVariable->SetMatrix( (float*)&g_Projection );
		
	//		
	UINT stride = sizeof( SimpleVertex );	
#if  0

	 UINT offset = 0;
	 context->IASetVertexBuffers(  0,  1,  &pFrm->g_pVertexBuffer11,  &stride,  &offset  );			
	 context->IASetIndexBuffer( pFrm->g_pIndexBuffer11, DXGI_FORMAT_R32_UINT, 0 );
	
	 context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
#endif
		
	 //	
	 pQce->g_pDiffuseVariable->SetResource(  pSrv_src  );

	 //
	 ID3DX11EffectTechnique  *  pTech  =  NULL;
	 ID3D11InputLayout		*	pInputLayout  =  NULL;

	 //	 
	 //  2013/10/31		
	 ClearShaderResources11(  context  );
	 		
	 //	
	 ID3D11RenderTargetView* pPrevRTV = NULL;				
	 ID3D11DepthStencilView* pPrevDS = NULL;
	 context->OMGetRenderTargets( 1, &pPrevRTV, &pPrevDS );
	
	 //  狟醱蔚diffuse葩秶善mask,甜preBlur	
	 pTech  =  pQce->g_pTechnique;
	 pInputLayout  =  pQce->g_pVertexLayout;
		 
	 		 
	 //
	 RenderToTexture11(  context,  g_pRTV,  pSrv_src,  FALSE,  
			 pTech,  pQce->g_pDiffuseVariable,  
			 pInputLayout, pQuad->g_pQuadVB11,  pQuad->g_pQuadIB11,  stride,  CropW,  CropH  );
	 		
	 //	
	 // Restore the original RT and DS				
	 context->OMSetRenderTargets( 1, &pPrevRTV, pPrevDS );
	 SAFE_RELEASE( pPrevRTV );
	 SAFE_RELEASE( pPrevDS );
	 
	 iErr  =  0;

	//
errLabel:


	//
	return  iErr;
}


