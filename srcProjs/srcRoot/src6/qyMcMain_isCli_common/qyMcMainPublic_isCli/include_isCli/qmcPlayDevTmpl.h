
#ifndef  __qmcPlayDevTmpl_h__
#define  __qmcPlayDevTmpl_h__	//  {

//
#include	"myTypes.h"

//
#include	"qmcCommFunc_is_open.h"
#include	"qmcSound_dx.h"

//
class CCtxQmc;

//
class  CQmcPlayDevTmpl {

	//
	struct {

	}		m_var;

public:
	CQmcPlayDevTmpl();
	virtual ~CQmcPlayDevTmpl();

	//
	virtual  int initDSoundToPlay(void* pDynLib_dx, LPCGUID lpcGUID, HWND  hWnd, void* p2) = mynull;
	virtual void  exitDSoundToPlay(void* pDynLib_dx, void* p1, void* p2) = mynull;
	//
	virtual int  initPlay_dx(void* pDynLib_dx, PLAY_AUDIO_procInfo* pPlayAudio, DWORD  dwBufferBytes, myPLAY_SOUND_dx* p) = mynull;
	virtual int  exitPlay_dx(void* pDynLib_dx, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p) = mynull;

	virtual int startOutputBuf(QMC_SOUND_MGR* pMgr, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p) = mynull;

	//
	virtual int  processOutput(QMC_SOUND_MGR* pMgr, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p, BOOL  bFillWithSilence, LPBYTE  pbInput1, DWORD  dwNumBytes) = mynull;




};




#endif  //  }


