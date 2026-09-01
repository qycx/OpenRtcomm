
#ifndef  __qmcPlayDev_dummy_h__
#define  __qmcPlayDev_dummy_h__		//  {

//
#include	"qmcPlayDevTmpl.h"

//
class  CQmcPlayDev_dummy:public CQmcPlayDevTmpl {

public:
	CQmcPlayDev_dummy();
	~CQmcPlayDev_dummy();

	//
	virtual  int initDSoundToPlay(void* pDynLib_dx, LPCGUID lpcGUID, HWND  hWnd, void* p2)
	{
		return  0;
	}

	virtual void  exitDSoundToPlay(void* pDynLib_dx, void* p1, void* p2)
	{
		return;
	}


	virtual int  initPlay_dx(void* pDynLib_dx, PLAY_AUDIO_procInfo* pPlayAudio, DWORD  dwBufferBytes, myPLAY_SOUND_dx* p)
	{
		return  0;
	}

	virtual int  exitPlay_dx(void* pDynLib_dx, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p)
	{
		return  0;
	}

	virtual int startOutputBuf(QMC_SOUND_MGR* pMgr, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p)
	{
		return  0;
	}

	//
	virtual int  processOutput(QMC_SOUND_MGR* pMgr, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p, BOOL  bFillWithSilence, LPBYTE  pbInput1, DWORD  dwNumBytes)
	{
		return  0;
	}






};



#endif  //  }


