
#ifndef  __avCapDevTmpl_h__
#define  __avCapDevTmpl_h__		//  {

//
#include	"qmOpenCommon.h"

//
class CCtxQmc;

//
class  AvCapDevTmpl {

	struct			{
		//

	}  m_var;

public:
	//
	AvCapDevTmpl(); 
	virtual ~AvCapDevTmpl();

	//
	virtual  int  initDev(void** ppCapStuff, AUDIO_COMPRESSOR_cfgCommon* pAudioCompressor, BITMAPINFOHEADER* pBih_suggested, HWND  hWnd_notify, LONG_PTR lInstanceData, void** ppShareMediaDeviceParam)  =  mynull;
	virtual  int  exitDev(void** ppShareMediaDeviceParam)  =  mynull;

	virtual  BOOL  bGetCapturePara(CCtxQmc* pProcInfo, int  iIndex_capAudio, int  iIndex_capBmp, void* pShareMediaDevice, WAVEFORMATEX* pWf_org, QY_VIDEO_HEADER* pVh_org, SAMPLE_grabberCb_cache* pCache)  =  mynull;

	virtual  int  runDev(void* pShareMediaDeviceParam)  =  mynull;;
	virtual  int  stopDev(void* pShareMediaDeviceParam)  =  mynull;



};


#endif  //  }

