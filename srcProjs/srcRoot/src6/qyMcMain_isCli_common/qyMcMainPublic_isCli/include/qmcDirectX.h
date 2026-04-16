

#ifndef  __QMCDIRECTX_H__
#define  __QMCDIRECTX_H__	//  {


//#include	""
#include	"qmcDirectX_open.h"
#include	"qmcDirectX.h"
#include <dmo.h>

//
#ifdef  __DDRAW_INCLUDED__
		typedef  HRESULT  (  WINAPI  *  PF_DirectDrawCreate  )( GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter );
#else
		#define	 PF_DirectDrawCreate			void  *
#endif



#ifdef  _D3D9_H_
		typedef  IDirect3D9 * (  WINAPI *  PF_Direct3DCreate9  )(UINT SDKVersion);
#else
		#define  PF_Direct3DCreate9				void  *
#endif

#ifdef  __DSOUND_INCLUDED__
		typedef  HRESULT  (  WINAPI  *  PF_DirectSoundCreate  )(LPCGUID pcGuidDevice, LPDIRECTSOUND *ppDS, LPUNKNOWN pUnkOuter);
		typedef  HRESULT  (  WINAPI  *  PF_DirectSoundCaptureCreate  )(LPCGUID pcGuidDevice, LPDIRECTSOUNDCAPTURE *ppDSC, LPUNKNOWN pUnkOuter);
		typedef  HRESULT  (  WINAPI  *  PF_DirectSoundCaptureEnumerateW  )(LPDSENUMCALLBACKW lpDSEnumCallback, LPVOID lpContext);
#else
		#define  PF_DirectSoundCreate				void  *
		#define	 PF_DirectSoundCaptureCreate		void  *
		#define	 PF_DirectSoundCaptureEnumerateW	void  *
#endif

typedef  HRESULT  (  STDAPICALLTYPE  *  PF_DMOEnum  )(  REFGUID guidCategory, DWORD dwFlags, DWORD cInTypes,  const DMO_PARTIAL_MEDIATYPE *pInTypes, DWORD cOutTypes,  const DMO_PARTIAL_MEDIATYPE *pOutTypes, IEnumDMO **ppEnum  );
typedef  HRESULT  (  STDAPICALLTYPE  *  PF_MoInitMediaType  )(DMO_MEDIA_TYPE *pmt, DWORD cbFormat);
typedef  HRESULT  (  STDAPICALLTYPE  *  PF_MoFreeMediaType  )(DMO_MEDIA_TYPE *pmt);




//
typedef  struct  __dynLib_dx_t						{
	
				 HINSTANCE							hDll_DDraw;
				 PF_DirectDrawCreate				pDirectDrawCreate;

				 HINSTANCE							hDll_D3D9;	
				 PF_Direct3DCreate9					pDirect3DCreate9;

				 HINSTANCE							hDll_Dsound;
				 PF_DirectSoundCreate				pDirectSoundCreate;
				 PF_DirectSoundCaptureCreate		pDirectSoundCaptureCreate;
				 PF_DirectSoundCaptureEnumerateW	pDirectSoundCaptureEnumerateW;		//  2011/10/23

				 HINSTANCE							hDll_MsDmo;
				 PF_DMOEnum							pDMOEnum;
				 PF_MoInitMediaType					pMoInitMediaType;
				 PF_MoFreeMediaType					pMoFreeMediaType;

				 //  2015/10/03
				 HINSTANCE							hDll_dxgi;
				 PF_CreateDXGIFactory1				pf_CreateDXGIFactory1;

				 //  2010/06/02
				 HINSTANCE							hDll_sampleGrabber;
				 void				*				pf_getNewFilter;
#if  0
				 void				*				pf_newCrossBar;
				 void				*				pf_freeCrossBar;
				 void				*				pf_crossBarGetInputCount;
#endif


}		 DYN_LIB_DX;


 

#endif  //  }


