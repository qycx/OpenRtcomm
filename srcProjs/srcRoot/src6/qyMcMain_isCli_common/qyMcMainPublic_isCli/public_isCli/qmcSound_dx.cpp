

#include	"stdafx.h"
#include	<stddef.h>
 
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#include	"qmcSound_dx.h"

#include	"qmcVideoCapture_isCli.h"
#include	"GuiShare.h"

//
QMC_SOUND_MGR	gQmcSoundMgr;	

int  exitRecord_dx(  void  *  pDynLib_dx,  CAP_procInfo_recordSound  *  pRecordSoundProcInfo  );



//////////////

 BOOL  bDSoundToPlayInited(  )
{
	QMC_SOUND_MGR	*	pMgr					=	&gQmcSoundMgr;

	return  pMgr->m_var.bPlaySoundInited;
}

 //  int initDSoundToPlay( void  *  pDynLib_dx,  HWND  hWnd,  void  *  p2  )
 int initDSoundToPlay2( void  *  pDynLib_dx,  LPCGUID lpcGUID,  HWND  hWnd,  void  *  p2  ) 	
{
	int					iErr					=	-1;
    HRESULT             hr;
	DYN_LIB_DX		*	pDynLib					=	(  DYN_LIB_DX  *  )pDynLib_dx;
	QMC_SOUND_MGR	*	pMgr					=	&gQmcSoundMgr;
	BOOL				bDirectSoundCreated		=	FALSE;

	if  (  !pDynLib  ||  !pDynLib->pDirectSoundCreate  ||  !pDynLib->pDirectSoundCreate  )  return  -1;
	if  (  pMgr->m_var.bPlaySoundInited  )  return  0;

    // Create DirectSound.
	if  (  FAILED(  hr  =  pDynLib->pDirectSoundCreate(  lpcGUID,  &pMgr->m_var.playSound.lpds,  NULL  )  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initDSoundToPlay: DirectSoundCreate failed, hr 0x%x"  ),  hr  );
		return  -1;
	}
	bDirectSoundCreated  =  TRUE;

    // Set cooperative level.
	if  (  FAILED(  hr  =  pMgr->m_var.playSound.lpds->SetCooperativeLevel(  hWnd,  DSSCL_NORMAL  )  )  )  goto  errLabel;

	pMgr->m_var.bPlaySoundInited  =  TRUE;

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		if (  bDirectSoundCreated  )  {
			pMgr->m_var.playSound.lpds->Release(  );  pMgr->m_var.playSound.lpds  =  NULL;
		}
	}
	if  (  !iErr  )  {
		traceLogA(  (char*)  "init playSound successfully."  );	 
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  _T(  "Init playSound successfully."  )  );
		}
	else  {
		  traceLogA(  (char*)  "Failed to init playSound."  );	 
		  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  _T(  "Failed to tnit playSound."  )  );
	}

	return  iErr;
 }

  void  exitDSoundToPlay2(  void  *  pDynLib_dx,  void  *  p1,  void  *  p2  )
{
	QMC_SOUND_MGR	*	pMgr	=	&gQmcSoundMgr;

	if  (  !pMgr->m_var.bPlaySoundInited  )  return;

	//  2015/07/30
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  _T(  "exit playSound enters."  )  );

	//
	if ( pMgr->m_var.playSound.lpds ) {
		pMgr->m_var.playSound.lpds->Release();  pMgr->m_var.playSound.lpds  =  NULL;
	}

	#ifdef  __DEBUG__
			traceLogA(  (char*)  "exit playSound"  );
	#endif
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  _T(  "exit playSound leaves."  )  );

	pMgr->m_var.bPlaySoundInited  =  FALSE;

	return;
}

 int  initRecord_dx(  void  *  pDynLib_dx,  CAP_procInfo_recordSound  *  pRecordSoundProcInfo  )
{
	int					iErr	=	-1;
    int                 i;
    HRESULT             hr;
	DYN_LIB_DX		*	pDynLib	=	(  DYN_LIB_DX  *  )pDynLib_dx;
	QMC_SOUND_MGR	*	pMgr	=	&gQmcSoundMgr;

	WAVEFORMATEX		wfx;

	if  (  !pDynLib  ||  !pDynLib->pDirectSoundCreate  ||  !pDynLib->pDirectSoundCreate  )  return  -1;
	//  if  (  !pMgr->m_var.myPs.lpds  )  return  -1;

	LPCGUID lpcGUID	=	NULL;		//  2011/10/24
#ifdef  __SUPPORT_chooseADevice__		
	    if  (  pRecordSoundProcInfo->guid_aDevice  !=  GUID_NULL  )  {
			lpcGUID  =  &pRecordSoundProcInfo->guid_aDevice;
		}
#endif

    // Create DirectSoundCapture.
	if  (  FAILED(  hr  =  pDynLib->pDirectSoundCaptureCreate(  lpcGUID,  &pMgr->m_var.myRs.lpdsc,  NULL  )  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initRecord_dx: DirectSoundCaptureCreate failed, hr 0x%x"  ),  hr  );
		return -1;
	}
	
	//Setting WAVEFORMATEX  structure for the audio input
	/*
	memset(  &wfx,  0x00,  sizeof(  wfx  )  );	
	wfx.wFormatTag			=	WAVE_FORMAT_PCM;
	wfx.nChannels			=	DEFAULT_nChannels_pcm_audio;		//  2;
	wfx.wBitsPerSample		=	DEFAULT_wBitsPerSample_pcm_audio;	//  16;
	wfx.cbSize				=	0;
	wfx.nSamplesPerSec		=	DEFAULT_iHertz_pcm_audio;			//  22.05 KHz

	wfx.nBlockAlign			=	(  wfx.wBitsPerSample  /  8  )  *  wfx.nChannels;
	//  wfx.nAvgBytesPerSec	=	wfx.nSamplesPerSec  *  (  wfx.wBitsPerSample  /  8  );
	wfx.nAvgBytesPerSec		=	wfx.nSamplesPerSec  *  wfx.nBlockAlign;
	*/
	//	memcpy(  &wfx,  &pRecordSoundProcInfo->compressAudio.waveFormatEx,  sizeof(  wfx  )  );
	if  (  !pRecordSoundProcInfo->compressAudio.bCompressInited  )  {
		traceLogA(  (char*)  "initRecord_dx failed: compressAudio not inited."  );
		goto  errLabel;
	}
	memcpy(  &wfx,  &pRecordSoundProcInfo->compressAudio.ah_decompress.wfx,  sizeof(  wfx  )  );

	//
	DWORD		dwOffset_notify_unit; dwOffset_notify_unit = 0;  //pPlayAudio->ah.wfx.nAvgBytesPerSec;
				  if  (  wfx.nAvgBytesPerSec  %  100  )  {
					  traceLog((TCHAR*)  _T(  "initRecord_dx failed, nAvgBytesPerSec can't devided by 100"  )  );
					  goto  errLabel;
				  }
				  dwOffset_notify_unit  =  wfx.nAvgBytesPerSec  /  100  *  2;

				  myRECORD_SOUND_dx* pMyRs; pMyRs = &pMgr->m_var.myRs;


					pMyRs->dwOffset_notify_unit  =  dwOffset_notify_unit;
					pMyRs->dwNotifyCount  =  CONST_numCaptureEvents;//myPs.dsbDesc.dwBufferBytes  /  myPs.dwOffset_notify_unit;


	// Create capture buffer. 
	memset(  &pMgr->m_var.myRs.dscbDesc,  0,  sizeof(  pMgr->m_var.myRs.dscbDesc  )  );
	pMgr->m_var.myRs.dscbDesc.dwSize = sizeof( DSCBUFFERDESC );
	pMgr->m_var.myRs.dscbDesc.dwFlags = 0;
    
	// We’re going to capture one second's worth of audio.
	//  pMgr->m_var.myRs.dscbDesc.dwBufferBytes = wfx.nAvgBytesPerSec;	//  2009/02/13
	pMgr->m_var.myRs.dscbDesc.dwBufferBytes  =  pMyRs->dwOffset_notify_unit * pMyRs->dwNotifyCount;//  pRecordSoundProcInfo->compressAudio.compressor.uiBytesRecorded_perBlockAlign  *  pRecordSoundProcInfo->compressAudio.ah_decompress.wfx.nBlockAlign  *  2;	// 

	pMgr->m_var.myRs.dscbDesc.dwReserved = 0;
	pMgr->m_var.myRs.dscbDesc.lpwfxFormat = &wfx;

	if ( !SUCCEEDED( hr = pMgr->m_var.myRs.lpdsc->CreateCaptureBuffer( &pMgr->m_var.myRs.dscbDesc, &pMgr->m_var.myRs.lpdscb, NULL ) ) )  {
		traceLogA(  (char*)  "startRecord_dx: CreateCaptureBuffer failed. hr %d",  hr  );
		goto  errLabel;  
	}


	/*
    // Create output buffer in same format as input buffer.
    ZeroMemory( &dsbDesc, sizeof( dsbDesc ) );
    dsbDesc.dwSize = sizeof( dsbDesc );

    // Set flags for whatever properties of the buffer you want to 
    // be able to change. We also set DSBCAPS_GLOBALFOCUS to keep
    // the buffer running when the app is in the background.
    dsbDesc.dwFlags = DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GLOBALFOCUS
                      | DSBCAPS_GETCURRENTPOSITION2; 

    // The output buffer should be bigger than the capture buffer to
    // avoid any overlap problems.
    dsbDesc.dwBufferBytes = pMgr->m_var.dscbDesc.dwBufferBytes * 4;
    dsbDesc.lpwfxFormat = &wfx;

    if ( FAILED( hr = pMgr->m_var.lpds->CreateSoundBuffer( &dsbDesc, &lpdsb, NULL ) ) )  goto  errLabel;
	*/

    /* Notifications */
 
    // Create the events. We make an extra one for later use 
    // by the output buffer.
    for ( i = 0; i < CONST_numCaptureEvents; i++ )  {
		pMyRs->hEvents[i] = CreateEvent( NULL, FALSE, FALSE, NULL );
		if ( NULL == pMyRs->hEvents[i] ) goto  errLabel;
    }

    // Set up notification positions in capture buffer. These occur halfway 
    // through the buffer, at the end of the buffer, and when capture stops.
	/*
	pMgr->m_var.myRs.rgdscbpn[0].dwOffset = ( pMgr->m_var.myRs.dscbDesc.dwBufferBytes / 2 ) - 1;
	pMgr->m_var.myRs.rgdscbpn[0].hEventNotify = pMyRs->hEvents[0  +  1];
	pMgr->m_var.myRs.rgdscbpn[1].dwOffset = pMgr->m_var.myRs.dscbDesc.dwBufferBytes - 1;
	pMgr->m_var.myRs.rgdscbpn[1].hEventNotify = pMyRs->hEvents[1  +  1];
	pMgr->m_var.myRs.rgdscbpn[2].dwOffset = DSBPN_OFFSETSTOP;
	pMgr->m_var.myRs.rgdscbpn[2].hEventNotify = pMyRs->hEvents[2  +  1];
	*/
	for  (  i  =  0;  i  <  pMyRs->dwNotifyCount;  i  ++  )  {
		//
		pMyRs->rgdscbpn[i].dwOffset  =  (  i  +  1  )  *  pMyRs->dwOffset_notify_unit  -  1;
		pMyRs->rgdscbpn[i].hEventNotify  =  pMyRs->hEvents[i];
	}


    // Get interface for capture buffer notification.
	if ( FAILED( hr = pMgr->m_var.myRs.lpdscb->QueryInterface( IID_IDirectSoundNotify, ( VOID ** )&pMgr->m_var.myRs.lpdsnInput ) ) )  goto  errLabel;

    // Set capture buffer notifications.
	if ( FAILED( hr = pMgr->m_var.myRs.lpdsnInput->SetNotificationPositions(  CONST_numCaptureEvents, pMgr->m_var.myRs.rgdscbpn ) ) ) {
		pMgr->m_var.myRs.lpdsnInput->Release();  pMgr->m_var.myRs.lpdsnInput  =  NULL;
		goto  errLabel;
    }

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		exitRecord_dx(  pDynLib_dx,  pRecordSoundProcInfo  );
	}
	
    return  iErr;
}


 int  exitRecord_dx(  void  *  pDynLib_dx,  CAP_procInfo_recordSound  *  pRecordSoundProcInfo  )
 {
	DYN_LIB_DX		*	pDynLib	=	(  DYN_LIB_DX  *  )pDynLib_dx;
	QMC_SOUND_MGR	*	pMgr	=	&gQmcSoundMgr;
	int					i;

	if  (  !pDynLib  ||  !pDynLib->pDirectSoundCreate  ||  !pDynLib->pDirectSoundCreate  )  return  -1;

	myRECORD_SOUND_dx * pMyRs=&pMgr->m_var.myRs;

	if ( pMgr->m_var.myRs.lpdsnInput ) {
		pMgr->m_var.myRs.lpdsnInput->Release();  pMgr->m_var.myRs.lpdsnInput  =  NULL;
	}

	for  (  i  =  0;  i  <  mycountof(  pMyRs->hEvents  );  i  ++  )  {
		 if  (  pMyRs->hEvents[i]  )  {
			 CloseHandle(  pMyRs->hEvents[i]  );  pMyRs->hEvents[i]  =  NULL;
		 }
	}

	if  (  pMgr->m_var.myRs.lpdscb  )  {
		pMgr->m_var.myRs.lpdscb->Release(  );  pMgr->m_var.myRs.lpdscb  =  NULL;
	}
	if ( pMgr->m_var.myRs.lpdsc ) {
		pMgr->m_var.myRs.lpdsc->Release();  pMgr->m_var.myRs.lpdsc  =  NULL;
	}

	return  0;
}


 /////////////////


 //  2011/12/25
 int  processInput(  MC_VAR_isCli  *  pProcInfo,  QMC_SOUND_MGR  *  pMgr,  DWORD index_dscbpn,  char  *  pAudioDataBuf,  unsigned  int  *  puiSize  )
{
	int					iErr			=	-1;
    HRESULT             hr;
    DWORD               dwCBReadPos;
    DWORD               dwNumBytes;
    LPBYTE              pbInput1;
    DWORD               cbInput1;
    LPBYTE              pbInput2;
    DWORD               cbInput2;
	BOOL				bLocked			=	FALSE;


    // Get the position of the read cursor when the event was set. 
    // Remember, the index of the event is the index into the array
    // of notifications.
	dwCBReadPos = pMgr->m_var.myRs.rgdscbpn[index_dscbpn].dwOffset;

    if  (  dwCBReadPos == DSBPN_OFFSETSTOP ) {
		traceLogA(  (char*)  "processInput failed: get event stop. "  );
		return  -1;

		/*
		pMgr->m_var.myRs.lpdscb->GetCurrentPosition( NULL, &dwCBReadPos );
        // The current position is one ahead of the last byte of data
        // available. It's important to sync up for 16-bit data.
        dwCBReadPos--;
        if ( dwCBReadPos < 0 )
			dwCBReadPos += pMgr->m_var.myRs.dscbDesc.dwBufferBytes;
		*/
    }

	//
#ifdef  __DEBUG__
	traceLog((TCHAR*)  _T(  "processInput: index %d, dwOffset %d, readCursor %d"  ),  index_dscbpn, dwCBReadPos,  pMgr->m_var.myRs.dwMyReadCursor  );
#endif

    // Calculate the number of bytes to read.
    // We don't have to worry about wraparound, since we know we did
    // a read when the cursor last hit the end of the buffer.
    dwNumBytes = ( dwCBReadPos - pMgr->m_var.myRs.dwMyReadCursor ) + 1;

    // Lock the part of the capture buffer that has the data we want.
    // Note that cbInput2 will always be zero, since our reads never
    // wrap around.
	if ( FAILED( hr = pMgr->m_var.myRs.lpdscb->Lock( pMgr->m_var.myRs.dwMyReadCursor, dwNumBytes,
                  ( LPVOID * )&pbInput1, &cbInput1, 
				  ( LPVOID * )&pbInput2, &cbInput2, 0 ) ) )  
	{
		traceLogA(  (char*)  "processInput:  Capture lock failure"  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "processInput: lock failed."  )  );					
		goto  errLabel;		
	}
	bLocked  =  TRUE;
				  
	
	/*
    // Make sure we haven't lost the output buffer.
    DWORD dwStatus;
    hr = lpdsb->GetStatus( &dwStatus );
    if ( dwStatus & DSBSTATUS_BUFFERLOST )
    {
        if ( FAILED( hr = lpdsb->Restore() ) )
        {
            OutputDebugString( _T(  "Couldn't Restore output buffer.\n" )  );
            return;
        }
    }

    // If just starting, find the point at which it is safe to write 
    // to the output buffer and initialize our internal cursor. 
    if ( dwMyWriteCursor == 0xFFFFFFFF )
    {
        hr = lpdsb->GetCurrentPosition( NULL, &dwMyWriteCursor );

        // We should get some distance between us and the write position
        // to make sure it never overtakes us; it is not necessarily going
        // to stay a constant distance in front of the play position.
        dwMyWriteCursor += ( dsbDesc.dwBufferBytes / 8 );

        if ( dwMyWriteCursor >= dsbDesc.dwBufferBytes )
            dwMyWriteCursor -= dsbDesc.dwBufferBytes;
    }
	

    if ( SUCCEEDED( hr = lpdsb->Lock( dwMyWriteCursor,
                             dwNumBytes,
                             ( LPVOID * )&pbOutput1, &cbOutput1, 
                             ( LPVOID * )&pbOutput2, &cbOutput2, 0 ) ) )
    {
	*/

		/*
		Need to send msg ....
        // Do the copy.
        CopyMemory( pbOutput1, pbInput1, cbOutput1 ); 

        if ( cbOutput2 )  
            CopyMemory( pbOutput2, pbInput1 + cbOutput1, cbOutput2 );
			*/


	if  (  pbInput1  !=  NULL  &&  dwNumBytes  )  {

		if  (  dwNumBytes  >  *puiSize  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "processInput failed: dwNumBytes too big."  )  );					
			goto  errLabel;		
		}
		
		memcpy(  pAudioDataBuf,  pbInput1,  dwNumBytes  );
		*puiSize  =  dwNumBytes;
		

	}

		/*
        lpdsb->Unlock( pbOutput1, cbOutput1, pbOutput2, cbOutput2 );

        // Advance our internal write cursor, compensating for wraparound.
        dwMyWriteCursor += dwNumBytes; 
        if ( dwMyWriteCursor >= dsbDesc.dwBufferBytes )
            dwMyWriteCursor -= dsbDesc.dwBufferBytes;

    }
    else OutputDebugString( _T(  "Output lock failure." )  );
	*/

    // Finished with capture buffer.
	pMgr->m_var.myRs.lpdscb->Unlock( pbInput1, cbInput1, pbInput2, cbInput2 );
	bLocked  =  FALSE;
	

    // Advance our internal read cursor by the number of bytes in
    // the capture lock, compensating for wraparound.
    pMgr->m_var.myRs.dwMyReadCursor += dwNumBytes;
	if ( pMgr->m_var.myRs.dwMyReadCursor >= pMgr->m_var.myRs.dscbDesc.dwBufferBytes )
		pMgr->m_var.myRs.dwMyReadCursor -= pMgr->m_var.myRs.dscbDesc.dwBufferBytes;

	
    // If this was a "capture buffer stopped" event, we want the output buffer
    // to stop after it has played the data, so we make an event notification.
	if ( pMgr->m_var.myRs.rgdscbpn[index_dscbpn].dwOffset == DSBPN_OFFSETSTOP )
    {
		/*
        lpdsb->Stop();
        dsbpn.dwOffset = dwMyWriteCursor;
        dsbpn.hEventNotify = pMgr->m_var.rghEvent[iEvent + 1];

        if ( lpdsnOutput == NULL )
        {
            hr = lpdsb->QueryInterface( IID_IDirectSoundNotify, 
				                        ( VOID ** )&lpdsnOutput );
        }

        if ( lpdsnOutput != NULL )
        { 
            lpdsnOutput->SetNotificationPositions( 1, &dsbpn );
        }

        lpdsb->Play( 0, 0, DSBPLAY_LOOPING );

        dwMyWriteCursor = 0xFFFFFFFF;
		*/
		traceLogA(  (char*)  "This is the end."  );

    }

	iErr  =  0;
errLabel:

	if  (  bLocked  )  {
		pMgr->m_var.myRs.lpdscb->Unlock( pbInput1, cbInput1, pbInput2, cbInput2 );
	}

	return  iErr;

} 


 int  processInput_post(  void  *  pProcInfoParam,  int  nAvgBytesPerSec,  BYTE  *  pbInput1,  unsigned  int  dwNumBytes,  MIS_MSGU  *  pMsgBuf  )
{
	int								iErr						=	-1;
	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pProcInfoParam;

		BOOL			bHaveMsgrs_sendLocalAv	=	TRUE;
		unsigned  int	uiSampleTimeInMs = myGetTickCount(mynull);// mytimeGetTime();
		if  (  !nAvgBytesPerSec  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "Attention: processInput_post: nAvgBytesPerSec not given here"  )  );
			#endif
			}
		else  {
			  int  nDataInMs  =  (  dwNumBytes  *  1000  )  /  nAvgBytesPerSec;
			  uiSampleTimeInMs  -=  nDataInMs;			
			  #ifdef  __DEBUG__
					  #if  0
  						  traceLog((TCHAR*)  _T(  "processInput_post: dataLen %d, nDataInMs %dms"  ),  dwNumBytes,  nDataInMs  );
					  #endif
			  #endif
		}


		//
		if (bNeedMute()) {
			goto  errLabel;
		}


		//
#if  0	//  2013/08/02
		toShareAudio(  pProcInfo,  (  CAP_procInfo_audioU  *  )&pProcInfo->av.localAv.recordSoundProcInfo,  uiSampleTimeInMs,  pbInput1,  dwNumBytes,  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio,  getSharedObjByIndex(  pProcInfo,  pProcInfo->av.localAv.recordSoundProcInfo.iIndex_sharedObj  ),  &bHaveMsgrs_sendLocalAv,  pMsgBuf  );
#else
		{
			CQyMalloc				mallocObj;
			
			CAP_procInfo_audioCommon  *  pCapAudio  =  (  CAP_procInfo_audioCommon  *  )&pProcInfo->av.localAv.recordSoundProcInfo;

			myPLAY_AUDIO_DATA		*	p;			
			int							len;

			len  =  sizeof(  myPLAY_AUDIO_DATA  );


			myPLAY_AUDIO_DATA	tmp_myPLAY_AUDIO_DATA;			
			p  =  &tmp_myPLAY_AUDIO_DATA;	//  (  myPLAY_AUDIO_DATA  *  )m_var.pBuf;
			if  (  !p  )  goto  errLabel;
			memset(  p,  0,  len  );

			//  2016/12/10
			unsigned  int  uiSize_dec  =  dwNumBytes;
					
			//  2011/12/06		
			unsigned  int  uiSize_enc  =  0;	//  sizeof(  TRANSFER_AUDIO_DATA  );
			
			//
			//  p->head.uiLen  =  dwNumBytes;
			p->head.uiLen  =  uiSize_dec  +  uiSize_enc;	//  2016/12/10
			p->uiSize_dec  =  uiSize_dec;					//  2016/12/10
			//
			p->head.uiSampleTimeInMs  =  uiSampleTimeInMs;							
			//  
			if  (  !mallocObj.mallocf(  p->head.uiLen  )  )  goto  errLabel;				
			if  (  mallocObj.get(  &p->memory  )  )  goto  errLabel;
			//memcpy(  p->memory.m_pBuf,  pbInput1,  p->head.uiLen  );
			memcpy(  p->memory.m_pBuf,  pbInput1,  p->uiSize_dec  );	//  2016/12/14
			
			//
			if  (  q2PostMsgAndTrigger(  p,  len,  &pCapAudio->thread.q2,  _T(  "processInput_post"  )))  goto  errLabel;
			mallocObj.detach(    );

		}

#endif

		//
		if  (  pProcInfo->av.localAv.recordSoundProcInfo.bLocalAudioPlaying  )  { 
			//
			#ifdef  __DEBUG__
					//  traceLog((TCHAR*)  _T(  "%d bytes audio data"  ),  dwNumBytes  );
		    #endif
			
			if  (  pProcInfo->av.localAv.player.audio.bRunning  )  {	//  if thread is active
				CQyMalloc	mallocObj;

				//  qPostMsgAndTrigger_playSound(  pbInput1,  dwNumBytes,  &pProcInfo->av.localAv.playSoundProcInfo  );					
				//  TRANSFER_AUDIO_dataMem	pkt;
				myPLAY_AUDIO_DATA	pkt;
				myPLAY_AUDIO_DATA	*	pPkt  =  &pkt;
				memset(  pPkt,  0,  sizeof(  myPLAY_AUDIO_DATA  )  );
				//  pkt.idInfo.ui64Id  =  0;
				//  pkt.uiSampleTimeInMs  =  (  unsigned  int  )(  SampleTime  *  1000  );
				pPkt->head.uiSampleTimeInMs  =  uiSampleTimeInMs;
				//
				//  pPkt->head.uiLen  =  min(  pProcInfo->cfg.uiBufSize_myPlayAudioData,  dwNumBytes  );

				//  2016/12/10			
				unsigned  int  uiSize_dec  =  dwNumBytes;				
			
				//  2011/12/06					
				unsigned  int  uiSize_enc  =  0;
						
				//			
				//  p->head.uiLen  =  dwNumBytes;
				pPkt->head.uiLen  =  uiSize_dec  +  uiSize_enc;	//  2016/12/10			
				pPkt->uiSize_dec  =  uiSize_dec;					//  2016/12/10

				//
			#if  0
				pPkt->pBuf  =  mallocObj.malloc(  pPkt->head.uiLen  );
				if  (  !pPkt->pBuf  )  goto  errLabel;
			#else
				if  (  !mallocObj.mallocf(  pPkt->head.uiLen  )  )  goto  errLabel;
				if  (  mallocObj.get(  &pPkt->memory  )  )  goto  errLabel;
			#endif
				memcpy(  pPkt->memory.m_pBuf,  pbInput1,  pPkt->uiSize_dec  );

				//  2010/06/21
				pProcInfo->av.localAv.player.audio.m_var.uiSampleTimeInMs_newRecvd  =  pPkt->head.uiSampleTimeInMs;
				pProcInfo->av.localAv.player.audio.m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  =  GetTickCount(  );

				//  
#if  0			//  2011/11/30, 不想采用触发机制了
				if  (  q2PostMsgAndTrigger(  pPkt,  offsetof(  myPLAY_AUDIO_DATA,  buf  ),  &pProcInfo->av.localAv.player.audio.q2  )  )  goto  errLabel;
#else
				if  (  q2PostMsg(  pPkt,  sizeof(  myPLAY_AUDIO_DATA  ),  &pProcInfo->av.localAv.player.audio.q2,  _T(  "processInput_post 1"  )))  goto  errLabel;
#endif
				mallocObj.detach(    );

				QY_MC	*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;
				//  if  (  !pQyMc->bUseDirectSound_toPlay  )  
				if  (  pQyMc->uiAPlayType  ==  CONST_aPlayType_wave  )  
				{
					PostThreadMessage(  pProcInfo->av.localAv.player.audio.dwThreadId,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
				}

				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%d bytes audio data."  ),  dwNumBytes  );					
			}
		}

		if  (  bHaveMsgrs_sendLocalAv  ||  pProcInfo->av.localAv.recordSoundProcInfo.bLocalAudioPlaying  )  pProcInfo->av.localAv.recordSoundProcInfo.dwTickCnt_sendLocalAv  =  GetTickCount(  );
		else  {

			  if  (  GetTickCount(  )  -  pProcInfo->av.localAv.recordSoundProcInfo.dwTickCnt_sendLocalAv  <  4000  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (char*)"",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: no messenger need to be sent."  )  );
			  else  {
				    qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (char*)"",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: no messenger need to be sent, audio shall be stopped."  )  );
					goto  errLabel;					
			  }
		 }


	iErr  =  0;

errLabel:

	return  iErr;
}


 extern "C" DWORD WINAPI mcThreadProc_recordSound( LPVOID lpParameter )
{
	 QY_MC						*	pQyMc						=	QY_GET_GBUF(  );
	 DYN_LIB_DX					*	pDynLib						=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	 MC_VAR_isCli					*	pProcInfo					=	QY_GET_procInfo_isCli(  );
	 if (  !pProcInfo  )  return  -1;
	 CAP_procInfo_recordSound	*	pRecordSoundProcInfo		=	&pProcInfo->av.localAv.recordSoundProcInfo;
	 QMC_SOUND_MGR				*	pMgr						=	&gQmcSoundMgr;
	 

	 //  2013/08/02
	 QY_qThreadProcInfo_common  *  pRecThread  =  &pRecordSoundProcInfo->recThread;

	 //
	 BOOL							bRecordInited				=	FALSE;
	 BOOL							bRecordStarted				=	FALSE;

	 HRESULT						hr;

	 CQyMalloc						mallocObj_pAudioDataBuf;
	 char						*	pAudioDataBuf				=	NULL;

	 CQyMalloc						mallocObj_pMsgBuf;
	 MIS_MSGU					*	pMsgBuf						=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;

	 traceLogA(  (char*)  "recordSound enters"  );

	 memset(  &pMgr->m_var.myRs,  0,  sizeof(  pMgr->m_var.myRs  )  );

	 //  
	 int	bufSize_pAudioDataBuf  =  pProcInfo->cfg.uiBufSize_myPlayAudioData;
	 if  (  !(  pAudioDataBuf  =  (  char  *  )mallocObj_pAudioDataBuf.mallocf(  bufSize_pAudioDataBuf  )  )  )  goto  errLabel;
	 unsigned  int  len;

	 //
	 int  nAvgBytesPerSec; nAvgBytesPerSec = pRecordSoundProcInfo->compressAudio.ah_decompress.wfx.nAvgBytesPerSec;
	 if  (  !nAvgBytesPerSec  )  goto  errLabel;

	 //
	 if  (  initRecord_dx(  pDynLib,  pRecordSoundProcInfo  )  )  goto  errLabel;
	 bRecordInited  =  TRUE;


	 //
	 //pRecThread->bQuit  =  FALSE;
	 pRecThread->bRunning  =  TRUE;
	 pRecordSoundProcInfo->usErrors_processInput  =  0;

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Record sound starts"  )  );

	 if  (  FAILED(  hr = pMgr->m_var.myRs.lpdscb->Start( DSCBSTART_LOOPING )  )  )  goto  errLabel;
	 bRecordStarted  =  TRUE;

	 broadcastRecorderStatus(  pQyMc  );

	 traceLogA(  (char*)  "record sound starts..."  );

	 //
	 myRECORD_SOUND_dx* pMyRs; pMyRs = &pMgr->m_var.myRs;

	 //
	 SetThreadPriority(GetCurrentThread(), THREAD_BASE_PRIORITY_LOWRT);

	 // 
	 for  (  ;  !pRecThread->bQuit;  )  {
		  
		  DWORD  dwEvt  =  WaitForMultipleObjects(
                             CONST_numCaptureEvents,		// Number of events.
                             pMyRs->hEvents,		// Location of handles.
                             FALSE,								// Wait for all?
                             5000								// How long to wait?
                               );								// Any message is an 
																// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  goto  errLabel;
		  if  (  dwEvt  ==  WAIT_TIMEOUT  )  goto  errLabel;

		  // WAIT_OBJECT_0 == zero but is properly treated as an arbitrary
		  // index value assigned to the first event, therefore we subtract
		  // it from dwEvt to get the zero-based index of the event.

		  DWORD  dwIndex  =  dwEvt - WAIT_OBJECT_0;


		  // If the event was set by the capture buffer, you have input
		  // to process.
		  if ( dwIndex < CONST_numCaptureEvents ) {

			  //
#ifdef  __DEBUG__
			  uint tickCnt0=myGetTickCount(mynull);
#endif


			  // Copy data to output buffer.
			  len  =  bufSize_pAudioDataBuf;
			  if  (  processInput(  pProcInfo,  pMgr, dwIndex,  pAudioDataBuf,  &len  )  )  { 
				  traceLogA(  (char*)  "mcThreadProc_recordSound: processInput failed"  );  
				  pRecordSoundProcInfo->usErrors_processInput  ++  ;
				  }
			  else  {
				    //
#ifdef  __DEBUG__
				    static  uint  stickCnt=0;
					uint  tickCnt1=myGetTickCount(mynull);
					int  iDiffInMs = tickCnt1  -  stickCnt;
					stickCnt  =  tickCnt1;
#endif
				    //
				    //processInput_post(  pProcInfo,  0,  (  BYTE  *  )pAudioDataBuf,  len,  pMsgBuf  );				    
					processInput_post(  pProcInfo,  nAvgBytesPerSec,  (  BYTE  *  )pAudioDataBuf,  len,  pMsgBuf  );				    

					//
#ifdef  __DEBUG__
					uint  tickCnt2=myGetTickCount(mynull);
					int  iDiffInMs2=tickCnt2  -  tickCnt1;
					traceLog((TCHAR*)  _T(  "record: elapse %dms. len %d. e_processInput %dms, e_processInput_post %dms"  ),  iDiffInMs,  len,
						tickCnt1  -  tickCnt0,  tickCnt2-tickCnt1);

#endif
			  }
			  if  (  pRecordSoundProcInfo->usErrors_processInput  >  25  )  {				  
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "record sound failed. totoal erros are %d"  ),  pRecordSoundProcInfo->usErrors_processInput  );					
				  goto  errLabel;
			  }

			  continue;
		  }

		  traceLogA(  (char*)  "unknown event"  );	
		  goto  errLabel;
	 }
	 

errLabel:

	 traceLogA(  (char*)  "mcThreadProc_recordSound will quit"  );

	 if  (  bRecordStarted  )  pMgr->m_var.myRs.lpdscb->Stop(  );
	 
	 pRecThread->bRunning  =  FALSE;

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Record sound ends"  )  );

	 if  (  bRecordInited  )  {
		 exitRecord_dx(  pDynLib,  pRecordSoundProcInfo  );
	 }

	 broadcastRecorderStatus(  pQyMc  );

	 traceLogA(  (char*)  "recordSound leaves"  );

	return  0;
}



#ifdef  __DEBUG__

 BOOL CALLBACK testDSEnumCallback(
  LPGUID lpGuid,
  LPCTSTR lpcstrDescription,
  LPCTSTR lpcstrModule,
  LPVOID lpContext
)
 {
	 traceLog((TCHAR*)  _T(  "%s, %s"  ),  lpcstrDescription,  lpcstrModule  );
	 return  TRUE;
 }


 int  testDx(  )
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	traceLog((TCHAR*)  _T(  "testDx enters"  )  );

	DYN_LIB_DX					*	pDynLib						=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	
	pDynLib->pDirectSoundCaptureEnumerateW(  testDSEnumCallback,  0  );



	traceLog((TCHAR*)  _T(  "testDx leaves"  )  );

	return  0;
}
#endif