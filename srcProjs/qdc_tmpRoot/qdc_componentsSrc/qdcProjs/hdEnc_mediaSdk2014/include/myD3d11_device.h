

#ifndef  __myD3d11_device_h__
#define  __myD3d11_device_h__	//  {

#include	"d3d11_device.h"



//
#if MFX_D3D11_SUPPORT

//
#include	"d3d11_1.h"

//
#include	"qisD3d_open.h"


//
//#include	"enc_d3d11_func.h"


//
class  CMyD3D11Device:public CD3D11Device
{
public:
	CMyD3D11Device(  );
	~CMyD3D11Device(  );

	//
	virtual mfxStatus Init(
        mfxHDL hWindow,
        mfxU16 nViews,
        mfxU32 nAdapterNum);

	//
	CComPtr<ID3D11Device1>									m_pd3d11Device1;
	CComPtr<ID3D11DeviceContext1>							m_pd3dImmediateContext1;
	
	//
#ifdef  _DEBUG
	CComPtr<ID3D11Texture2D>								m_pTexture_intermediate;
#endif

	//
	struct													{
		//
		void										*		pMyPipeline;

		//
		//ENC_d3d11_devVar									devVar;
		void  *												pENC_d3d11_devVar;


	}														m_var;


	//
	int  CMySmplYUVReader_myLoadNextFrame_msdk(  unsigned  short  usPktResType,  void  *  p0_pInput,  void  *  p1_uiInputSize,  PARAM_CMySmplYUVReader_myLoadNextFrame_msdk  *  pParam,  mfxFrameAllocator * pAlloc);
	
	//
#ifdef  _DEBUG
	int  test_CMySmplYUVReader_myLoadNextFrame_msdk(  unsigned  short  usPktResType,  char  *  pInput,  unsigned  int  uiInputSize,  PARAM_CMySmplYUVReader_myLoadNextFrame_msdk  *  pParam,  mfxFrameAllocator * pAlloc);
#endif



};


#endif

#endif  //  }


