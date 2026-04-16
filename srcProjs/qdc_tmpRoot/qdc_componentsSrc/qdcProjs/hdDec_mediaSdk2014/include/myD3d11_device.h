

#ifndef  __myD3d11_device_h__
#define  __myD3d11_device_h__	//  {

#include	"d3d11_device.h"



//
#if MFX_D3D11_SUPPORT

//
#include	"qisD3d_open.h"




//
//#include	"dec_d3d11_func.h"


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
	virtual mfxStatus RenderFrame(mfxFrameSurface1 * pSurface, mfxFrameAllocator * pmfxAlloc);

	//
	//void  free_resource(  DEC_d3d11_devVar  *  pDevVar  );

	//
	mfxStatus  my_RenderFrame(mfxFrameSurface1 * pSurface, mfxFrameAllocator * pmfxAlloc);
	//
#ifdef  _DEBUG
	mfxStatus  test_RenderFrame_1(mfxFrameSurface1 * pSurface, mfxFrameAllocator * pmfxAlloc);

#endif

	//
#ifdef  _DEBUG
	CComPtr<ID3D11Texture2D>                m_pTexture_intermediate;
#endif
	//
	//CComPtr<ID3D11Texture2D>                m_shared_pTexes[MAX_sharedTexes_dec];
	//CComPtr<IDXGIKeyedMutex>				m_pDXGIKeyedMutexes[MAX_sharedTexes_dec];


	//
#if 0
	CComPtr<ID3D11VideoProcessorInputView>  m_pInputViewLeft_my;
    CComPtr<ID3D11VideoProcessorOutputView> m_pOutputView_my;
#endif

	//
	struct									{
		//
		void						*		pMyPipeline;

#if  0  //  2016/04/24
		//
		BOOL								bInited_sharedTexes;
		//
		SHARED_tex							sharedTexes[MAX_sharedTexes_dec];
		//
		unsigned  char						ucMaxCnt_shared_pTexes;

		//
#define		MAX_tmpDecTexes					4	//  8	//  10
		//
		struct								{
			TMP_dec_tex						mems[MAX_tmpDecTexes];
			unsigned  char					ucMaxCnt_tmpDecTexes;
			//
			unsigned  int					uiCnt_filled;
		}									tmpDecTexes;
		
		//
		unsigned  int						tn_sharedTex;
		DWORD								dwProcessId;
		//
		unsigned  int						uiSeqNo_newSharedTex1;
	
		//
		unsigned  int						uiSeqNo_lastCopied;

		//			
		unsigned  int						uiLoopCtrls;;
		//
		DWORD								dwLastTickCnt_renderFrame;	
		//
		unsigned  int						uiNewMax_intervalInMs_renderFrame;
		DWORD								dwStartTickCnt_toGetNew;
		//
		unsigned  int						uiMax_intervalInMs_renderFrame;
#endif
		//  2016/04/24
		//DEC_d3d11_devVar					devVar;
		void							*	pDEC_d3d11_devVar;

	}										m_var;

};


#endif

#endif  //  }


