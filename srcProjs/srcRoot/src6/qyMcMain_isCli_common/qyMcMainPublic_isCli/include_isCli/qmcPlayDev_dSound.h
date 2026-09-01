
#ifndef  __qmcPlayDev_dSound_h__
#define  __qmcPlayDev_dSound_h__	//  {

//
#include	"qmcPlayDevTmpl.h"

//
class CQmcPlayDev_dSound :public CQmcPlayDevTmpl {

public:
	CQmcPlayDev_dSound();
	virtual ~CQmcPlayDev_dSound();
	
	//
	virtual  int initDSoundToPlay(void* pDynLib_dx, LPCGUID lpcGUID, HWND  hWnd, void* p2);
	virtual void exitDSoundToPlay(void* pDynLib_dx, void* p1, void* p2);


	virtual int  initPlay_dx(void* pDynLib_dx, PLAY_AUDIO_procInfo* pPlayAudio, DWORD  dwBufferBytes, myPLAY_SOUND_dx* p);
	virtual int  exitPlay_dx(void* pDynLib_dx, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p);

	//
	virtual int startOutputBuf(QMC_SOUND_MGR* pMgr, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p);

	//
	virtual int  processOutput(QMC_SOUND_MGR* pMgr, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p, BOOL  bFillWithSilence, LPBYTE  pbInput1, DWORD  dwNumBytes);


};




#endif  //  }


