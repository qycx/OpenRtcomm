

#include	"stdafx.h"

#include "windows.h"
#include "htmlhelp.h"
#pragma warning(disable: 4995)
#include	<tchar.h>
#include <strsafe.h>
#include <shlwapi.h>
#include <shlobj.h>

#pragma warning(default: 4995)




#include "d3d9.h"
//#include "d3dx9.h"


#include "DXUT.h"





#include	"meshLoaderCommon.h"
#include	"tmpDefs_meshLoader.h"


//
_declspec(  dllexport  )  void  *  meshLoader_new(  )
{
	return  new  CMeshLoader;
}

//
_declspec(  dllexport  )  void  meshLoader_free(  void  **  pp  )
{
	if  (  !pp  )  return;
	if  (  !*pp  )  return;
	delete  (  CMeshLoader  *  )*pp;
	*pp  =  NULL;
	return;
}


//
_declspec(  dllexport  )  int  meshLoader_init(  void  *  pMeshLoaderParam,  void  *  pID3D11Device  )
{
	if  (  !pMeshLoaderParam  )  return  -1;
	CMeshLoader  *  pMeshLoader  =  (  CMeshLoader  *  )pMeshLoaderParam;
	ID3D11Device  *  pd3dDevice  =  (  ID3D11Device  *  )pID3D11Device;

	return  pMeshLoader->init(  pd3dDevice  );
}


//
_declspec(  dllexport  )  void  meshLoader_Shutdown(  void  *  pMeshLoaderParam  )
{
	if  (  !pMeshLoaderParam  )  return;
	CMeshLoader  *  pMeshLoader  =  (  CMeshLoader  *  )pMeshLoaderParam;

	pMeshLoader->Shutdown();

	return;
}


//  2015/03/28
_declspec(  dllexport  )  int  meshLoader_loadFile(  void  *  pMeshLoaderParam,  LPCTSTR  fn  )
{
	if  (  !pMeshLoaderParam  )  return  -1;
	CMeshLoader  *  pMeshLoader  =  (  CMeshLoader  *  )pMeshLoaderParam;

	pMeshLoader->LoadFile(  fn  );

	return  0;
}

_declspec(  dllexport  )  int  meshLoader_OnFrameMove( void  *  pMeshLoaderParam,  double fTime, float fElapsedTime )	
{
	if  (  !pMeshLoaderParam  )  return  -1;
	CMeshLoader  *  pMeshLoader  =  (  CMeshLoader  *  )pMeshLoaderParam;

	pMeshLoader->OnFrameMove( fTime, fElapsedTime );

	return  0;
}


_declspec(  dllexport  )  int  meshLoader_OnFrameRender( void  *  pMeshLoaderParam,  void  *  pID3D11DeviceContextParam,  double fTime, float fElapsedTime )
{
	if  (  !pMeshLoaderParam  )  return  -1;
	CMeshLoader  *  pMeshLoader  =  (  CMeshLoader  *  )pMeshLoaderParam;
	ID3D11DeviceContext  *  pID3D11DeviceContext  =  (  ID3D11DeviceContext  *  )pID3D11DeviceContextParam;

#ifdef  __DEBUG__
	//
	//  OutputDebugString(  _T(  "Not finished: meshLoader_OnFrameRender\n"  )  );
	//
	pMeshLoader->OnFrameRender(  pID3D11DeviceContext, fTime, fElapsedTime);
#endif

	return  0;
}



//
CMeshLoader::CMeshLoader(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	//
	LastRenderTime = 0;    
	RenderCount = 0;

	//
	g_States  =  NULL;
	g_FXFactory  =  NULL;
	g_Model  =  NULL;

}


CMeshLoader::~CMeshLoader(  )
{
}


//
int  CMeshLoader::init(  ID3D11Device  *  pd3dDevice  )
{
	//
	m_var.pd3dDevice  =  pd3dDevice;

	// Create other render resources here
    g_States.reset( new CommonStates( pd3dDevice ) );
    g_FXFactory.reset( new MyEffectFactory( pd3dDevice ) );
	
	//
	m_var.bInited  =  TRUE;

	return  0;
}




//  2015/03/27
void CMeshLoader::Shutdown()
{
	g_States.reset();
    g_FXFactory.reset();
    g_Model.reset();

}


//
int CMeshLoader::LoadFile( LPCWSTR filepath )
{
	int  iErr  =  -1;

	if  (  !m_var.bInited  )  return  -1;

#if  0
    if( 0 == lstrcmpi( PathFindExtension(filepath), L".x"))
    {
        LoadX( filepath );
    }
    else if( 0 == lstrcmpi( PathFindExtension(filepath), L".fx"))
    {
        LoadFX( filepath );

    } 
    else if( 0 == lstrcmpi( PathFindExtension(filepath), L".dds"))
    {
        LoadDDS( filepath );

    }
#endif
	
	ID3D11Device  *  pd3dDevice  =  m_var.pd3dDevice;

#if  0
	WCHAR str[MAX_PATH];
	if  (  FAILED(  DXUTFindDXSDKMediaFileCch( str, MAX_PATH, L"Tiny\\tiny.sdkmesh" ) )  )  goto  errLabel;

    g_FXFactory->SetPath( L"Tiny\\" );
    g_Model = Model::CreateFromSDKMESH( pd3dDevice, str, *g_FXFactory, true );
#endif

	                WCHAR szFile[MAX_PATH];
					szFile[0]  =  0;

					//
					safeTcsnCpy(  filepath,  szFile,  mycountof(  szFile  )  ); 

					//
	                    // g_FXFactory->SetPath( L"" );
#ifdef  __DEBUG__
					g_FXFactory->SetPath(  L"D:\\qycx4\\testProjs\\myDxViewer\\msDx2010\\Samples\\Media\\Airplane\\"  );
#else	
					OutputDebugString(  _T(  "not finished\n"  )  );
#endif


                    WCHAR ext[_MAX_EXT];
                    _wsplitpath_s( szFile, nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT );

#if 0
                    if ( _wcsicmp( ext, L".sdkmesh" ) == 0 )
                    {
                        g_Model = Model::CreateFromSDKMESH( DXUTGetD3D11Device(), szFile, *g_FXFactory, true );
                    }
                    else if ( _wcsicmp( ext, L".vbo" ) == 0 )
                    {
                        g_Model = Model::CreateFromVBO( DXUTGetD3D11Device(), szFile, nullptr, true );
                    }
                    else
                    {
                        g_Model = Model::CreateFromCMO( DXUTGetD3D11Device(), szFile, *g_FXFactory, false );
                    }
#endif

#ifndef  __DEBUG__
					OutputDebugString(  _T(  "not finished\n"  )  );
						                    //SetViewForModel();

#endif

					iErr  =  0;
errLabel:
	return  iErr;
}

 
void CMeshLoader::LoadDDS( LPCWSTR filepath )
{
}

void CMeshLoader::LoadFX( LPCWSTR filepath )
{

}

void CMeshLoader::LoadX( LPCWSTR filepath )
{
}

void CMeshLoader::Reload()
{
}


void CMeshLoader::OutputA(const CHAR* message, ... )
{
}


void CMeshLoader::OutputW(const WCHAR* message, ... )
{
}

    
void CMeshLoader::OutputClear()
{
}

	
//
void  CMeshLoader::OnFrameMove( double fTime, float fElapsedTime )	
{
    bool bReloadNeeded = false;


#if  0
    if( timeGetTime() - DXVGetFileWatcher().GetTimeLastCheck() > 500 )
    {
        if( DXVGetFileWatcher().CheckForChanges() )
        {
            bReloadNeeded = true;
        }
    }
#endif

}


#include	"DXUTcamera.h"
extern  CModelViewerCamera          g_Camera;               // A model viewing camera

 
void  CMeshLoader::OnFrameRender( ID3D11DeviceContext* pd3dImmediateContext,  double fTime, float fElapsedTime)
{ 
	    // Get the projection & view matrix from the camera class
    XMMATRIX mWorld = g_Camera.GetWorldMatrix();
    XMMATRIX mView = g_Camera.GetViewMatrix();
    XMMATRIX mProj = g_Camera.GetProjMatrix();

    // Draw 3D object
    XMVECTOR qid = XMQuaternionIdentity();
    const XMVECTORF32 scale = { 1.f, 1.f, 1.f};
    const XMVECTORF32 translate = { 0.f, 0.f, 0.f };
    const XMVECTORF32 rotate = { 0.f, 0.f, 0.f, 1.f };
    XMMATRIX local = XMMatrixMultiply( mWorld, XMMatrixTransformation( g_XMZero, qid, scale, g_XMZero, rotate, translate ) );



	//  2015/04/24
	//    Update the model's effect. The lambda we pass covers each model part. Because we use the default DirectXTK EffectFactory, when
	//  loading the model, the effect that was set for each part is a BasicEffect. Using dynamic_cast to cast to a pointer will give us a
	//  nullptr in case the effect was changed and this code wasn't update
	g_Model->UpdateEffects([](DirectX::IEffect*effect)
	{
		auto  basicEffect  =  dynamic_cast<DirectX::BasicEffect*>(effect);
		if  (  basicEffect  !=  nullptr  )  {
			
			//
#ifdef  __DEBUG__	//  Not fished: 以下用来根据名称来设置视频纹理。
			WCHAR  *  pW  =  _T(  "kk"  );
#if  0
			if  (  !_tcsicmp(  basicEffect->tmpName,  pW  )  )  
			{
				basicEffect->SetTexture(  nullptr  );
			}
#endif

#endif
		}
	});

	//
#ifdef  __DEBUG__
#if  0
		size_t  count  =  0;
		for  (  auto  mit  =  g_Model->meshes.cbegin(  );  mit  !=  g_Model->meshes.cend(  );  ++  mit  )  {
			 auto  mesh  =  mit->get(  );
			 assert(  mesh  !=  0  );
			 //
			 for  (  auto  it  =  mesh->meshParts.cbegin(  );  it  !=  mesh->meshParts.cend(  );  ++  it  )  {
				  auto  part  =  it->get(  );
				  assert(  part  !=  0  );
				  //
				  //part->
				  //  part->effect.
			 }
		}
#endif
#endif



	//
    //auto pComboBox = g_SampleUI.GetComboBox( IDC_MESH_LIST );
    int meshDraw = -1;
#if  0
    if ( pComboBox )
    {
        meshDraw = PtrToInt( pComboBox->GetSelectedData() );
    }
#endif

    //auto pCheckBox = g_SampleUI.GetCheckBox( IDC_WIREFRAME );
    bool wireframe = false;//(pCheckBox) ? pCheckBox->GetChecked() : false;

    if ( g_Model )
    {
        if ( meshDraw == -1 )
        {
            g_Model->Draw( pd3dImmediateContext, *g_States, local, mView, mProj, wireframe );
        }
        else

        {
            int index = 0;
            for( auto it = g_Model->meshes.cbegin(); it != g_Model->meshes.cend(); ++it, ++index )
            {
                if ( index != meshDraw )
                    continue;

                auto mesh = it->get();
                assert( mesh != 0 );

                mesh->PrepareForRendering( pd3dImmediateContext, *g_States, false, wireframe );

                mesh->Draw( pd3dImmediateContext, local, mView, mProj );
            }
        }
    }

}













