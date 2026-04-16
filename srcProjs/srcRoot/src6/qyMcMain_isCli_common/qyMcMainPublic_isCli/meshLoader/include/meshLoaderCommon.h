


#ifndef  __meshLoaderCommon_h__
#define  __meshLoaderCommon_h__		//  {

//
#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "Effects.h"
#include "Model.h"


//
#include	"sdkmisc.h"

//
#include	<tchar.h>
#include	<strsafe.h>
#include	"qyMcMainCommon.h"


//
using namespace DirectX;


//--------------------------------------------------------------------------------------
class MyEffectFactory : public EffectFactory
{
public:
    MyEffectFactory( _In_ ID3D11Device* device ) : EffectFactory( device ) { *searchPath = 0; }

    virtual void __cdecl CreateTexture( _In_z_ const WCHAR* name, _In_opt_ ID3D11DeviceContext* deviceContext, _Outptr_ ID3D11ShaderResourceView** textureView ) override
    {
        WCHAR fname[MAX_PATH] = {0};
        if ( *searchPath )
            wcscpy_s( fname, searchPath );
        wcscat_s( fname, name );

        WCHAR path[MAX_PATH] = {0};
        if ( FAILED( DXUTFindDXSDKMediaFileCch( path, MAX_PATH, fname ) ) )
        {
            throw std::exception("Media not found");
        }

        EffectFactory::CreateTexture( path, deviceContext, textureView );
    }

    void SetPath( const WCHAR* path ) { if ( path ) { wcscpy_s( searchPath, path ); } else { *searchPath = 0; } }

private:
    WCHAR searchPath[ MAX_PATH ];
};


//
class  CMeshLoader  {

public:
	CMeshLoader(  );
	~CMeshLoader(  );

	//
	struct					{
		ID3D11Device  *		pd3dDevice;
		BOOL				bInited;

	}						m_var;
		

	std::unique_ptr<CommonStates>       g_States;
	std::unique_ptr<MyEffectFactory>    g_FXFactory;
	std::unique_ptr<Model>              g_Model;
	


	//
	int  init(  ID3D11Device  *  pd3dDevice  );
	void Shutdown();
	
	//	  
	int LoadFile( LPCWSTR filepath );
    void LoadX( LPCWSTR filepath );
    void LoadFX( LPCWSTR filepath );
    void LoadDDS( LPCWSTR filepath );
    void Reload();
	
	//
	void OutputA(const CHAR* message, ... );
    void OutputW(const WCHAR* message, ... );
    void OutputClear();



	//
	void    OnFrameMove( double fTime, float fElapsedTime );
    void    OnFrameRender( ID3D11DeviceContext* pd3dImmediateContext,  double fTime, float fElapsedTime);

	//
	float LastRenderTime;
    int RenderCount;


};








#endif  //  }



