




#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

#include	"DXUT.h"
#include	"DXUTgui.h"
#include	"SDKmisc.h"

//  2014/10/23
#include	"D3dx11effect.h"


#include	"CommonStates.h"
#include	"Effects.h"
#include	"GeometricPrimitive.h"
#include	"Model.h"
#include	"PrimitiveBatch.h"
#include	"VertexTypes.h"
#include	"SpriteBatch.h"
#include	"SpriteFont.h"
#include	"DDSTextureLoader.h"



//
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
#if  10
//--------------------------------------------------------------------------------------
void RenderToTexture11_spriteBatch( ID3D11DeviceContext  *  pd3dDeviceContext,  
								   //
								   SpriteBatch  *  pSprites11,
								   //
								   ID3D11RenderTargetView* pRTV, 
								   ID3D11ShaderResourceView* pSRV,
								   bool bClear, 
								   //
								   RECT  *  pSrcRc,  
								   //
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

    // Set the render target and a NULL depth/stencil surface
    if( pRTV )
    {
        ID3D11RenderTargetView* aRTViews[] = { pRTV };
        pd3dDeviceContext->OMSetRenderTargets( 1, aRTViews, NULL );
    }


	// Draw sprite
    pSprites11->Begin( SpriteSortMode_Deferred );


	XMVECTOR color  =  Colors::White;

	//
	pSprites11->Draw(  pSRV,  XMFLOAT2(  0,  0  ),  pSrcRc,  color  );

	//
    pSprites11->End();
		

    // Retore the original viewport
    pd3dDeviceContext->RSSetViewports( 1, &OldVP );
}

#endif


//
extern  "C"  __declspec(  dllexport  )  int  myCopyTex_rtt_spriteBatch(  PARAM_copyTex  *  pParam,  void  *  pSprites11,  int  CropW,  int  CropH,  ID3D11Texture2D  *  pTex_src,  ID3D11ShaderResourceView  *  pSrv_src,  RECT  *  pSrcRc,  ID3D11Texture2D  *   pTex_dst,  ID3D11RenderTargetView  *	g_pRTV_dst,  QIS_trace_common  *  pQtc  )
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
	if  (  !CropW  ||  !CropH  )  return  -1;
	

	//
	HRESULT  hr;
	ID3D11RenderTargetView  *  g_pRTV  =  NULL;
						
	//
	g_pRTV  =  g_pRTV_dst;


	 //	 
	 //  2013/10/31		
	 ClearShaderResources11(  context  );
	 		
	 //	
	 ID3D11RenderTargetView* pPrevRTV = NULL;				
	 ID3D11DepthStencilView* pPrevDS = NULL;
	 context->OMGetRenderTargets( 1, &pPrevRTV, &pPrevDS );
 
	 		 
	 //
#if  10
	 //
	 BOOL  bClear  =  FALSE;
	 //
	 bClear  =  TRUE;
	 //
	 RenderToTexture11_spriteBatch(  context,  
			(  SpriteBatch  *  )pSprites11,
			g_pRTV,  pSrv_src,  bClear,  
			 pSrcRc,
			 CropW,  CropH  );
#endif

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


