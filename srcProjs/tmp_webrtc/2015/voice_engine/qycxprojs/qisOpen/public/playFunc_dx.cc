
//#include	"stdafx.h"


//#include	<mmsystem.h>
//#include	<dmo.h>
#include    "webrtc\voice_engine\qycxprojs\qisOpen\include\tmpTypes.h"

//#include	<dsound.h>
#include	<stddef.h>
#include	<tchar.h>

#include	<tchar.h>
#include	<stdlib.h>
#include	<Dshow.h>
#include	<dsound.h>
#include	<dmoreg.h>


#include	"webrtc\voice_engine\qycxprojs\qyOpen\include\qdcOpenCommon.h"
#include	"webrtc\voice_engine\qycxprojs\qyOpen\include\qySyncObj.h"
#include	"webrtc\voice_engine\qycxprojs\qyOpen\include\genericqueue.h"

#include	"webrtc\voice_engine\qycxprojs\qisOpen\include\qySyncCommProc.h"
#include	"webrtc\voice_engine\qycxprojs\qisOpen\include\qyq2.h"
#include	"webrtc\voice_engine\qycxprojs\qisOpen\include\qnmCommProc_is_public.h"

#include	"webrtc\voice_engine\qycxprojs\qisOpen\include\qmcCommFunc_is_public.h"



#include	"webrtc\voice_engine\qycxprojs\qisOpen\include\qyTick.h"

#include	"webrtc\voice_engine\qycxprojs\qisOpen\include\qmcSound_dx.h"
#include	"webrtc\voice_engine\qycxprojs\qisOpen\include\qmcDirectX.h"
#include	"webrtc\voice_engine\qycxprojs\qyOpen\include\showInfo_open.h"

#include	"webrtc\voice_engine\qycxprojs\qisOpen\include\traceLog.h"
#include	"webrtc\voice_engine\qycxprojs\qisOpen\include\myPlayAudioData.h"

#include	"webrtc\voice_engine\qycxprojs\qisOpen\include\qyCommProc_public.h"

//
/* --------------------------------------------------------

    StopOutput()
    This is called when a notification has been received 
    from the output buffer that all available data has been 
    played. The function stops the output buffer and clears 
    the notification position.

   -------------------------------------------------------- */


 int  stopOutput(  myPLAY_SOUND_dx  *  p )
{
	int		iErr	=	-1;
	HRESULT	hr;

	//traceLogA(  "stopOutput called"  );

    if  (  FAILED(  hr  =  p->lpdsb->Stop()  )  )  goto  errLabel;
	p->bPlayStarted  =  FALSE;

	iErr  =  0;
errLabel:

	return  iErr;
}  
 

 //
  int  initPlay_dx(  void  *  pDynLib_dx,  QMC_SOUND_MGR	*	pMgr,  PLAY_AUDIO_procInfo  *  pPlayAudio,  DWORD  dwBufferBytes,  myPLAY_SOUND_dx  *  p  )
{
	int					iErr	=	-1;
    HRESULT             hr;
	DYN_LIB_DX		*	pDynLib	=	(  DYN_LIB_DX  *  )pDynLib_dx;
	//QMC_SOUND_MGR	*	pMgr	=	&gQmcSoundMgr;

	if  (  !pDynLib  ||  !pDynLib->pDirectSoundCreate  ||  !pDynLib->pDirectSoundCreate  )  return  -1;
	if  (  !pMgr->m_var.playSound.lpds  )  return  -1;
	
	if  (  p->bPlayInited  )  {
		//traceLogA(  "initPlay_dx failed. play is already inited."  );
		return  -1;
	}

	//traceLogA(  "initPlay_dx called"  );

	//Setting WAVEFORMATEX  structure for the audio input
	//  makeWaveFormat_pcm(  DEFAULT_audio_nChannels,  DEFAULT_audio_iHertz,  DEFAULT_audio_wBitsPerSample,  &pPlayAudio->waveFormatEx  );
	if  (  !pPlayAudio->ah.wfx.nChannels
		||  !pPlayAudio->ah.wfx.nSamplesPerSec
			||  !pPlayAudio->ah.wfx.wBitsPerSample  )
	{
		//traceLogA(  "initPlay_dx failed:  waveFormatEx error"  );
		//qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initPlay_dx failed: waveFormatEx error."  )  );					
		showInfo_open0(  0,  _T(  ""  ),  _T(  "initPlay_dx failed: waveFormatEx error."  )  );					
		return  -1;
	}


    // Create output buffer in same format as input buffer.
    ZeroMemory( &p->dsbDesc, sizeof( p->dsbDesc ) );
    p->dsbDesc.dwSize = sizeof( p->dsbDesc );

    // Set flags for whatever properties of the buffer you want to 
    // be able to change. We also set DSBCAPS_GLOBALFOCUS to keep
    // the buffer running when the app is in the background.
    p->dsbDesc.dwFlags = DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GLOBALFOCUS
                      | DSBCAPS_GETCURRENTPOSITION2; 

    // The output buffer should be bigger than the capture buffer to
    // avoid any overlap problems.
    //  p->dsbDesc.dwBufferBytes = pPlayAudio->waveFormatEx.nAvgBytesPerSec  *  4;
	p->dsbDesc.dwBufferBytes  =  dwBufferBytes;

	p->dsbDesc.lpwfxFormat = &pPlayAudio->ah.wfx;

	if ( FAILED( hr = pMgr->m_var.playSound.lpds->CreateSoundBuffer( &p->dsbDesc, &p->lpdsb, NULL ) ) )  {
		p->lpdsb  =  NULL;  goto  errLabel;
	}

	//
	if  (  FAILED(  hr = p->lpdsb->QueryInterface( IID_IDirectSoundNotify, ( VOID ** )&p->lpdsnOutput )  )  )  {
		p->lpdsnOutput  =  NULL;  goto  errLabel;
	}

	iErr  =  0;
errLabel:

	if  (  iErr  )  exitPlay_dx(  pDynLib_dx,  pMgr,  pPlayAudio,  p  );	
	
	if  (  !iErr  )  {
		p->bPlayInited  =  TRUE;
	}

    return  iErr;
}




 //int  exitPlay_dx(  void  *  pDynLib_dx,  PLAY_AUDIO_procInfo  *  pPlayAudio,  myPLAY_SOUND_dx  *  p  )
 int  exitPlay_dx(  void  *  pDynLib_dx,  QMC_SOUND_MGR	*	pMgr,  PLAY_AUDIO_procInfo  *  pPlayAudio,  myPLAY_SOUND_dx  *  p  )
 {
	DYN_LIB_DX		*	pDynLib	=	(  DYN_LIB_DX  *  )pDynLib_dx;
	//QMC_SOUND_MGR	*	pMgr	=	&gQmcSoundMgr;

	//traceLogA(  "exitPlay_dx called."  );

	if  (  !pDynLib  ||  !pDynLib->pDirectSoundCreate  ||  !pDynLib->pDirectSoundCreate  )  return  -1;

	if  (  p->bPlayStarted  )  stopOutput(  p  );    

	if ( p->lpdsnOutput ) {
		p->lpdsnOutput->Release();  p->lpdsnOutput  =  NULL;
	}

	if  (  p->lpdsb  )  {
		p->lpdsb->Release(  );  p->lpdsb  =  NULL;
	}

	if  (  p->lpdsbpns  )  {
		free(  p->lpdsbpns  );  p->lpdsbpns  =  NULL;				  
	}

	p->bPlayInited  =  FALSE;

	return  0;
}



 //
  int  processOutput( QMC_SOUND_MGR  *  pMgr,  PLAY_AUDIO_procInfo  *  pPlayAudio,  myPLAY_SOUND_dx  *  p,  BOOL  bFillWithSilence,  LPBYTE  pbInput1,  DWORD  dwNumBytes  )
{
	int					iErr			=		-1;
    HRESULT             hr;
    LPBYTE              pbOutput1;
    DWORD               cbOutput1;
    LPBYTE              pbOutput2;
    DWORD               cbOutput2;

    // Make sure we haven't lost the output buffer.
    DWORD dwStatus;
    hr = p->lpdsb->GetStatus( &dwStatus );
    if ( dwStatus & DSBSTATUS_BUFFERLOST ) {
		//traceLogA(  "processOutput: bufferLost"  );
		//
        if ( FAILED( hr = p->lpdsb->Restore() ) ) {
            //traceLogA(  "Couldn't Restore output buffer."  );
			goto  errLabel;
        }
    }

    // If just starting, find the point at which it is safe to write 
    // to the output buffer and initialize our internal cursor. 
	/*
    if ( p->dwMyWriteCursor == 0xFFFFFFFF )
    {
        hr = p->lpdsb->GetCurrentPosition( NULL, &p->dwMyWriteCursor );

        // We should get some distance between us and the write position
        // to make sure it never overtakes us; it is not necessarily going
        // to stay a constant distance in front of the play position.
		p->dwMyWriteCursor  =  (  p->dwMyWriteCursor  /  p->dwOffset_notify_unit  +  1  )  *  p->dwOffset_notify_unit;

        if ( p->dwMyWriteCursor >= p->dsbDesc.dwBufferBytes )
            p->dwMyWriteCursor -= p->dsbDesc.dwBufferBytes;
    }
	*/
	

    if ( SUCCEEDED( hr = p->lpdsb->Lock( p->dwMyWriteCursor,
                             dwNumBytes,
                             ( LPVOID * )&pbOutput1, &cbOutput1, 
                             ( LPVOID * )&pbOutput2, &cbOutput2, 0 ) ) )
    {
		if  (  !bFillWithSilence  )  {

			// Do the copy.
			CopyMemory( pbOutput1, pbInput1, cbOutput1 ); 

			if  (  cbOutput2  )  
				CopyMemory( pbOutput2, pbInput1 + cbOutput1, cbOutput2 );
			}
		else  {
			  FillMemory(  pbOutput1,  cbOutput1,  ( p->dsbDesc.lpwfxFormat->wBitsPerSample == 8 ) ? 128 : 0 );
			  if  (  cbOutput2  )
				  FillMemory(  pbOutput2,  cbOutput2,  (  p->dsbDesc.lpwfxFormat->wBitsPerSample  ==  8  )  ?  128  :  0  );
		}

        p->lpdsb->Unlock( pbOutput1, cbOutput1, pbOutput2, cbOutput2 );

        // Advance our internal write cursor, compensating for wraparound.
        p->dwMyWriteCursor += dwNumBytes; 
        if ( p->dwMyWriteCursor >= p->dsbDesc.dwBufferBytes )
            p->dwMyWriteCursor -= p->dsbDesc.dwBufferBytes;

		 }
	else {
		 //traceLogA(  "Output lock failure."  );
		 goto  errLabel;
	}


	iErr  =  0;

errLabel:
	return  iErr;
} // processOutput()


