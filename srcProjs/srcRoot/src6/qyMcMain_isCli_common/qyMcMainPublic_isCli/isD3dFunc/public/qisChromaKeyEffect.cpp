


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


//
extern  "C"  __declspec(  dllexport  )  int  getSize_QIS_chromaKey_effect(  )
{
	return  sizeof(  QIS_chromaKey_effect  );
}



//
extern  "C"  __declspec(  dllexport  )  int  initQisChromaKeyEffect(  ID3D11Device  *  g_pd3dDevice,  ID3D11DeviceContext  *  pd3dImmediateContext,  LPCTSTR  fn_ck,  QIS_chromaKey_effect  *  pQce  )
{
	int  iErr  =  -1;

	//  2016/05/05
	if  (  !pQce  )  return  -1;
	if  (  pQce->head.bInited  )  {
		showInfo_open0(  0,  0,  _T(  "initChromaKeyEffect failed, bInited is true"  )  );
		return  -1;
	}
	//
	showInfo_open0(  0,  0,  _T(  "initChromakeyEffect called"  )  );

    // Create the effect
    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
	
	//
#if  0
	cfgStr  =  CQyString(  pQyMc->cfg.installDir  )  +   _T(  CONST_qyCfgSubDir  );
	fn_ck  =  cfgStr  +  CONST_fileName_fx_ck;
#endif

#if  1	//  def  __DEBUG__
	LPCTSTR  fileName  =  _T(  "c:\\tttbbb\\Tutorial08.fx"  );
		
#if  0
	//  fileName  =  _T(  "c:\\tttbbb\\Tutorial04.fx"  );
	fileName  =  _T(  "c:\\tttbbb\\qisChromaKey.fx"  );
#ifdef  __DEBUG__
		fileName  =  _T(  "D:\\qycx4\\develop6\\srcProjs\\srcRoot\\src6\\qyMcMain_isCli\\qyMcMainPublic_isCli\\shader\\qisChromaKey.fx"  );
#endif
#endif
		fileName  =  fn_ck;

#endif
		//
		HRESULT  hr  =  E_FAIL;
		
	//
	ID3DBlob* pFXBlob = nullptr;
	hr  =  DXUTCompileFromFile(  fileName, nullptr, "none", "fx_5_0", D3DCOMPILE_ENABLE_STRICTNESS, D3DCOMPILE_EFFECT_ALLOW_SLOW_OPS, &pFXBlob );
	if  (  FAILED(  hr  )  )  goto  errLabel;
		
	//
	hr = D3DX11CreateEffectFromMemory(   pFXBlob->GetBufferPointer(  ), pFXBlob->GetBufferSize(  ), 0, g_pd3dDevice, &pQce->g_pEffect );
	SAFE_RELEASE( pFXBlob );
    if( FAILED( hr ) )
    {
        //  MessageBox( NULL, L"The FX file cannot be located.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
		#ifdef  __DEBUG__
				traceLog(  _T(  "The FX file cannot be located.  Please run this executable from the directory that contains the FX file.")  );
		#endif
		goto  errLabel;
    }

    // Obtain the technique
	ID3DX11Effect  *  g_pEffect  =  pQce->g_pEffect;
	pQce->g_pTechnique = g_pEffect->GetTechniqueByName( "Render" );
	pQce->g_pTechnique_preBlur_x  =  g_pEffect->GetTechniqueByName(  "Render_preBlur_x"  );
	pQce->g_pTechnique_preBlur_y  =  g_pEffect->GetTechniqueByName(  "Render_preBlur_y"  );
	pQce->g_pTechnique_chromaKey = g_pEffect->GetTechniqueByName( "Render_chromaKey" );
	pQce->g_pTechnique_postBlur_x = g_pEffect->GetTechniqueByName( "Render_postBlur_x" );
	pQce->g_pTechnique_postBlur_y = g_pEffect->GetTechniqueByName( "Render_postBlur_y" );
	pQce->g_pTechnique_blend = g_pEffect->GetTechniqueByName( "Render_blend" );
	pQce->g_pTechnique_mask = g_pEffect->GetTechniqueByName( "Render_mask" );



	pQce->g_pWorldVariable = g_pEffect->GetVariableByName( "World" )->AsMatrix();
    pQce->g_pViewVariable = g_pEffect->GetVariableByName( "View" )->AsMatrix();
    pQce->g_pProjectionVariable = g_pEffect->GetVariableByName( "Projection" )->AsMatrix();
    pQce->g_pMeshColorVariable = g_pEffect->GetVariableByName( "vMeshColor" )->AsVector();
    pQce->g_pDiffuseVariable = g_pEffect->GetVariableByName( "txDiffuse" )->AsShaderResource();
	//
	pQce->g_pMaskVariable  =  g_pEffect->GetVariableByName(  "txMask"  )->AsShaderResource(  );	//  2013/10/23


	//  2013/10/31
	if  (  ChromaKey_inputParams_init(  pQce,  &pQce->inputParams  )  )  goto  errLabel;

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },  
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
    };
    UINT numElements = sizeof(layout)/sizeof(layout[0]);

    // Create the input layout
    D3DX11_PASS_DESC PassDesc;
    pQce->g_pTechnique->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    hr = g_pd3dDevice->CreateInputLayout( layout, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &pQce->g_pVertexLayout );
    if( FAILED( hr ) )  {
		goto  errLabel;
	}

	//
    pQce->g_pTechnique_preBlur_x->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    hr = g_pd3dDevice->CreateInputLayout( layout, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &pQce->g_pVertexLayout_preBlur_x );
    if( FAILED( hr ) )  {
		goto  errLabel;
	}
	//
    pQce->g_pTechnique_preBlur_y->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    hr = g_pd3dDevice->CreateInputLayout( layout, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &pQce->g_pVertexLayout_preBlur_y );
    if( FAILED( hr ) )  {
		goto  errLabel;
	}

	//
    pQce->g_pTechnique_chromaKey->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    hr = g_pd3dDevice->CreateInputLayout( layout, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &pQce->g_pVertexLayout_chromaKey );
    if( FAILED( hr ) )  {
		goto  errLabel;
	}
	
	//
    pQce->g_pTechnique_postBlur_x->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    hr = g_pd3dDevice->CreateInputLayout( layout, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &pQce->g_pVertexLayout_postBlur_x );
    if( FAILED( hr ) )  {
		goto  errLabel;
	}
	//
    pQce->g_pTechnique_postBlur_y->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    hr = g_pd3dDevice->CreateInputLayout( layout, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &pQce->g_pVertexLayout_postBlur_y );
    if( FAILED( hr ) )  {
		goto  errLabel;
	}

	//
    pQce->g_pTechnique_blend->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    hr = g_pd3dDevice->CreateInputLayout( layout, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &pQce->g_pVertexLayout_blend );
    if( FAILED( hr ) )  {
		goto  errLabel;
	}


	//
    pQce->g_pTechnique_mask->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    hr = g_pd3dDevice->CreateInputLayout( layout, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &pQce->g_pVertexLayout_mask );
    if( FAILED( hr ) )  {
		goto  errLabel;
	}


    // Set the input layout
    //  g_pd3dDevice->IASetInputLayout( pQce->g_pVertexLayout );

    // Create vertex buffer
	    SimpleVertex vertices[] =
    {
        XMFLOAT3( -1.0f, 1.0f,	 -1.0f),  XMFLOAT2(0.0f, 0.0f ),	
        XMFLOAT3(  1.0f, 1.0f,   -1.0f ),  XMFLOAT2(1.0f, 0.0f ),
        XMFLOAT3(  1.0f, -1.0f, -1.0f ),  XMFLOAT2(1.0f, 1.0f ),
        XMFLOAT3( -1.0f, -1.0f, -1.0f ),  XMFLOAT2(0.0f, 1.0f ),

        XMFLOAT3( 1.0f, 1.0f,  1.0f ),  XMFLOAT2(0.0f, 0.0f ),
        XMFLOAT3( -1.0f,1.0f,  1.0f ),  XMFLOAT2(1.0f, 0.0f ),
        XMFLOAT3( -1.0f,-1.0f, 1.0f ),  XMFLOAT2(1.0f, 1.0f ),
        XMFLOAT3( 1.0f, -1.0f, 1.0f ),  XMFLOAT2(0.0f, 1.0f ),
		
		XMFLOAT3( -1.0f,  1.0f,  1.0f ),  XMFLOAT2(0.0f, 0.0f ),
        XMFLOAT3(  1.0f,  1.0f,  1.0f ),  XMFLOAT2(1.0f, 0.0f ),
        XMFLOAT3(  1.0f,  1.0f, -1.0f ),  XMFLOAT2(1.0f, 1.0f ),
        XMFLOAT3( -1.0f,  1.0f, -1.0f ),  XMFLOAT2(0.0f, 1.0f ),

        XMFLOAT3( -1.0f, -1.0f, -1.0f ),  XMFLOAT2(0.0f, 0.0f ),
        XMFLOAT3(  1.0f, -1.0f, -1.0f ),  XMFLOAT2(1.0f, 0.0f ),
        XMFLOAT3(  1.0f, -1.0f,  1.0f ),  XMFLOAT2(1.0f, 1.0f ),
        XMFLOAT3( -1.0f, -1.0f,  1.0f ),  XMFLOAT2(0.0f, 1.0f ),

        XMFLOAT3( -1.0f, 1.0f,  1.0f ),  XMFLOAT2(0.0f, 0.0f ),
        XMFLOAT3( -1.0f, 1.0f, -1.0f ),  XMFLOAT2(1.0f, 0.0f ),
        XMFLOAT3( -1.0f, -1.0f, -1.0f ),  XMFLOAT2(1.0f, 1.0f ),
        XMFLOAT3( -1.0f, -1.0f,  1.0f ),  XMFLOAT2(0.0f, 1.0f ),

        XMFLOAT3( 1.0f, 1.0f, -1.0f ),  XMFLOAT2(0.0f, 0.0f ),
        XMFLOAT3( 1.0f, 1.0f, 1.0f ),  XMFLOAT2(1.0f, 0.0f ),
        XMFLOAT3( 1.0f, -1.0f, 1.0f ),  XMFLOAT2(1.0f, 1.0f ),
        XMFLOAT3( 1.0f, -1.0f, -1.0f ),  XMFLOAT2(0.0f, 1.0f ),
    };



    D3D11_BUFFER_DESC bd;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( SimpleVertex ) * 24;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = vertices;
    hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &pQce->g_pVertexBuffer );
    if( FAILED( hr ) )
        return hr;


	// Set vertex buffer
    UINT stride = sizeof( SimpleVertex );
    UINT offset = 0;
    //  g_pd3dDevice->IASetVertexBuffers( 0, 1, &pQce->g_pVertexBuffer, &stride, &offset );
	pd3dImmediateContext->IASetVertexBuffers(  0, 1, &pQce->g_pVertexBuffer, &stride, &offset );


		    
	// Create index buffer
    // Create vertex buffer
    DWORD indices[] =
    {
#if 0
        3,1,0,
        2,1,3,

        6,4,5,
        7,4,6,

        11,9,8,
        10,9,11,

        14,12,13,
        15,12,14,

        19,17,16,
        18,17,19,

        22,20,21,
        23,20,22
#else
		0,1,2,
		0,2,3,

		4,5,6,
		4,6,7,

		8,9,10,
		8,9,11,

		12,13,14,
		12,14,15,

		16,17,18,
		16,18,19,

		20,21,22,
		20,22,23,
#endif
    };



    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( DWORD ) * 36;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    InitData.pSysMem = indices;
    hr  =  ( g_pd3dDevice->CreateBuffer( &bd, &InitData, &pQce->g_pIndexBuffer ) );
	if  (  FAILED(  hr  )  )  goto  errLabel;

    // Set index buffer
    //  g_pd3dDevice->IASetIndexBuffer( pQce->g_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	pd3dImmediateContext->IASetIndexBuffer(  pQce->g_pIndexBuffer,  DXGI_FORMAT_R32_UINT,  0  );

	
    // Set primitive topology
    //  g_pd3dDevice->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	pd3dImmediateContext->IASetPrimitiveTopology(  D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST  );



	if  (  10  )  {
		    // Create vertex buffer
	    SimpleVertex vertices[] =
    {
#if 0
        XMFLOAT3( -1.0f, -1.0f, 1.0f , 0.0f, 0.0f ),
        XMFLOAT3(  1.0f, -1.0f, 1.0f , 1.0f, 0.0f ),
        XMFLOAT3(  1.0f,  1.0f, 1.0f , 1.0f, 1.0f ),
        XMFLOAT3( -1.0f,  1.0f, 1.0f , 0.0f, 1.0f ),
#else
		XMFLOAT3(  -1.0f, 1.0f, 1.0f  ),  XMFLOAT2(  0.0f, 0.0f ),
		XMFLOAT3(  1.0f, 1.0f, 1.0f  ),  XMFLOAT2(  1.0f, 0.0f ),
		XMFLOAT3(  1.0f, -1.0f, 1.0f  ),  XMFLOAT2(  1.0f, 1.0f ),
		XMFLOAT3(  -1.0f, -1.0f, 1.0f  ), XMFLOAT2(  0.0f, 1.0f ),
#endif
    };



    D3D11_BUFFER_DESC bd;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( SimpleVertex ) * 4;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = vertices;
    hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &pQce->g_pVertexBuffer2 );
    if( FAILED( hr ) )
        return hr;

    // Set vertex buffer
    UINT stride = sizeof( SimpleVertex );
    UINT offset = 0;
    //  g_pd3dDevice->IASetVertexBuffers( 0, 1, &pQce->g_pVertexBuffer2, &stride, &offset );
	pd3dImmediateContext->IASetVertexBuffers(  0, 1, &pQce->g_pVertexBuffer2, &stride, &offset );
		    
	// Create index buffer
    // Create vertex buffer
    DWORD indices[] =
    {
#if 0
		2,1, 0,
        3,2, 0,
#else
		0,1, 2,
        0,2, 3,
#endif
    };

    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( DWORD ) * 6;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    InitData.pSysMem = indices;
    hr  =  ( g_pd3dDevice->CreateBuffer( &bd, &InitData, &pQce->g_pIndexBuffer2 ) );
	if  (  FAILED(  hr  )  )  goto  errLabel;

    // Set index buffer
    //  g_pd3dDevice->IASetIndexBuffer( pQce->g_pIndexBuffer2, DXGI_FORMAT_R32_UINT, 0 );
	pd3dImmediateContext->IASetIndexBuffer(  pQce->g_pIndexBuffer2,  DXGI_FORMAT_R32_UINT,  0  );
	
    // Set primitive topology
    //  g_pd3dDevice->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	pd3dImmediateContext->IASetPrimitiveTopology(  D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST  );

	}

	//
	pQce->head.bInited  =  TRUE;

	iErr  =  0;

errLabel:
	if  (  iErr  )  {
		exitQisChromaKeyEffect(  pQce  );
	}
	return  iErr;

}


//
extern  "C"  __declspec(  dllexport  )  void  exitQisChromaKeyEffect(  QIS_chromaKey_effect  *  pQce  )
{
	if  (  !pQce  )  return;

	//
	showInfo_open0(  0,  0,  _T(  "exitChromakeyEffect called"  )  );
	
	//
	MACRO_safeRelease(  pQce->g_pVertexBuffer  );
	MACRO_safeRelease(  pQce->g_pIndexBuffer  );
	MACRO_safeRelease(  pQce->g_pTextureRV  );
	//
	MACRO_safeRelease(  pQce->g_pVertexBuffer2  );						// = NULL;
	MACRO_safeRelease(  pQce->g_pIndexBuffer2  );						// = NULL;
	MACRO_safeRelease(  pQce->g_pTexture2  );
	MACRO_safeRelease(  pQce->g_pTextureRV2  );						// = NULL;


	//
	MACRO_safeRelease(  pQce->g_pVertexLayout_mask  );
	MACRO_safeRelease(  pQce->g_pVertexLayout_blend  );
	MACRO_safeRelease(  pQce->g_pVertexLayout_postBlur_x  );
	MACRO_safeRelease(  pQce->g_pVertexLayout_postBlur_y  );
	MACRO_safeRelease(  pQce->g_pVertexLayout_chromaKey  );			// = NULL;
	MACRO_safeRelease(  pQce->g_pVertexLayout_preBlur_x  );
	MACRO_safeRelease(  pQce->g_pVertexLayout_preBlur_y  );
	MACRO_safeRelease(  pQce->g_pVertexLayout  );						// = NULL;

	//  2013/10/31
	ChromaKey_inputParams_exit(  pQce,  &pQce->inputParams  );

	//
	MACRO_safeRelease(  pQce->g_pEffect  );
	
	//
	pQce->head.bInited  =  FALSE;

	return;
}



