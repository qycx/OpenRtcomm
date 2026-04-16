


#ifndef  __QMCDIRECTXPUBLIC_H__
#define  __QMCDIRECTXPUBLIC_H__		//  {


//
//#include	<d3dx9.h>
#ifdef  __USE_dx10__
#include	<d3dx10.h>
#endif
#ifdef  __USE_dx11__
#include	<d3d11.h>
//#include	"d3dx11effect.h"
#endif

#include	<DirectXMath.h>
#include    "qisD3d_open.h"

//
using namespace DirectX;


//

//
struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
};

//
struct Vertex12
{
    XMFLOAT4 position;
    XMFLOAT2 texcoord;
};


#if 0
struct SceneConstantBuffer
{
    XMFLOAT4 offset;
    float padding[60]; // Padding so the constant buffer is 256-byte aligned.
};
#else
struct SceneConstantBuffer
{
    DirectX::XMFLOAT4X4 WorldViewProj;
    float padding[12*4];
};

#endif
static_assert((sizeof(SceneConstantBuffer) % 256) == 0, "Constant Buffer size must be 256-byte aligned");



#endif	//  }



