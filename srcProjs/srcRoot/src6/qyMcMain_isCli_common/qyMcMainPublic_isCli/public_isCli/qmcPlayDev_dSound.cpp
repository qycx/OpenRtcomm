
#include	"stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qmcCommFunc_isCli.h"
#include	"qmcPlayDev_dSound.h"
#include	"qyAvRecordPublic.h"



CQmcPlayDev_dSound::CQmcPlayDev_dSound()
{

}



CQmcPlayDev_dSound::~CQmcPlayDev_dSound()
{
	return;
}





int CQmcPlayDev_dSound::initDSoundToPlay(void* pDynLib_dx, LPCGUID lpcGUID, HWND  hWnd, void* p2)
{
	return  ::initDSoundToPlay2(pDynLib_dx, lpcGUID, hWnd, p2);
}

 void  CQmcPlayDev_dSound::exitDSoundToPlay(void* pDynLib_dx, void* p1, void* p2)
 {
	 ::exitDSoundToPlay2(pDynLib_dx, p1, p2);

 }


int  CQmcPlayDev_dSound::initPlay_dx(void* pDynLib_dx, PLAY_AUDIO_procInfo* pPlayAudio, DWORD  dwBufferBytes, myPLAY_SOUND_dx* p)
{
	return  ::initPlay_dx2( pDynLib_dx, pPlayAudio, dwBufferBytes, p);
 }


int  CQmcPlayDev_dSound::exitPlay_dx(void* pDynLib_dx, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p)
{
	return  ::exitPlay_dx2(pDynLib_dx, pPlayAudio, p);
 }


int CQmcPlayDev_dSound::startOutputBuf(QMC_SOUND_MGR* pMgr, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p)
{
	return  ::startOutputBuf2(pMgr, pPlayAudio, p);
}



int  CQmcPlayDev_dSound::processOutput(QMC_SOUND_MGR* pMgr, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p, BOOL  bFillWithSilence, LPBYTE  pbInput1, DWORD  dwNumBytes)
{
	return  ::processOutput2( pMgr, pPlayAudio, p, bFillWithSilence, pbInput1, dwNumBytes);

 }



