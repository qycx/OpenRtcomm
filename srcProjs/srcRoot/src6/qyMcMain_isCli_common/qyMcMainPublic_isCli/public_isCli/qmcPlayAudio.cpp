



#include	"stdafx.h"
 
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>
#include	<stddef.h>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#include	"qmcSound_dx.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyTick.h"


int  stopOutput( myPLAY_SOUND_dx  *  p );
int  fixPlayCfg(  MC_VAR_isCli  *  pProcInfo,  AUDIO_PLAY_CFG  *  pPlayCfg  );


 int  initPlay_dx2(  void  *  pDynLib_dx,  PLAY_AUDIO_procInfo  *  pPlayAudio,  DWORD  dwBufferBytes,  myPLAY_SOUND_dx  *  p  )
{
	int					iErr	=	-1;
    HRESULT             hr;
	DYN_LIB_DX		*	pDynLib	=	(  DYN_LIB_DX  *  )pDynLib_dx;
	QMC_SOUND_MGR	*	pMgr	=	&gQmcSoundMgr;

	if  (  !pDynLib  ||  !pDynLib->pDirectSoundCreate  ||  !pDynLib->pDirectSoundCreate  )  return  -1;
	if  (  !pMgr->m_var.playSound.lpds  )  return  -1;
	
	if  (  p->bPlayInited  )  {
		traceLogA(  (char*)  "initPlay_dx failed. play is already inited."  );
		return  -1;
	}

	traceLogA(  (char*)  "initPlay_dx called"  );

	//Setting WAVEFORMATEX  structure for the audio input
	//  makeWaveFormat_pcm(  DEFAULT_audio_nChannels,  DEFAULT_audio_iHertz,  DEFAULT_audio_wBitsPerSample,  &pPlayAudio->waveFormatEx  );
	if  (  !pPlayAudio->ah.wfx.nChannels
		||  !pPlayAudio->ah.wfx.nSamplesPerSec
			||  !pPlayAudio->ah.wfx.wBitsPerSample  )
	{
		traceLogA(  (char*)  "initPlay_dx failed:  waveFormatEx error"  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initPlay_dx failed: waveFormatEx error."  )  );					
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

	if  (  iErr  )  exitPlay_dx2(  pDynLib_dx,  pPlayAudio,  p  );	
	
	if  (  !iErr  )  {
		p->bPlayInited  =  TRUE;
	}

    return  iErr;
}


  int  exitPlay_dx2(  void  *  pDynLib_dx,  PLAY_AUDIO_procInfo  *  pPlayAudio,  myPLAY_SOUND_dx  *  p  )
 {
	DYN_LIB_DX		*	pDynLib	=	(  DYN_LIB_DX  *  )pDynLib_dx;
	QMC_SOUND_MGR	*	pMgr	=	&gQmcSoundMgr;

	traceLogA(  (char*)  "exitPlay_dx called."  );

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



 //////////////
 


BOOL  bWriteSilenceToOutput( myPLAY_SOUND_dx  *  p,  DWORD dwStart, DWORD cbLength )
{
    PBYTE   pb1, pb2;
    DWORD   cb1, cb2;

    if ( ( !dwStart && !cbLength ) || ( NULL == p->lpdsb )
            || ( NULL == p->dsbDesc.lpwfxFormat ) )
    return FALSE;

    if ( SUCCEEDED( p->lpdsb->Lock( dwStart, cbLength, ( LPVOID * )&pb1, &cb1, 
                             ( LPVOID * )&pb2, &cb2, 0 ) ) )
    {
        FillMemory( pb1, cb1, ( p->dsbDesc.lpwfxFormat->wBitsPerSample == 8 ) ? 128 : 0 );

        if ( NULL != pb2 && cb2 )
            FillMemory( pb2, cb2, ( p->dsbDesc.lpwfxFormat->wBitsPerSample == 8) ? 128 : 0 );

        p->lpdsb->Unlock( pb1, cb1, pb2, cb2 );
        return TRUE;
    }

    return FALSE;
}

 

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

	traceLogA(  (char*)  "stopOutput called"  );

    if  (  FAILED(  hr  =  p->lpdsb->Stop()  )  )  goto  errLabel;
	p->bPlayStarted  =  FALSE;

	iErr  =  0;
errLabel:

	return  iErr;
}  
 
 int  resetOutput(  myPLAY_SOUND_dx  *  p  )
{
	int		iErr	=	-1;
	HRESULT	hr;

	traceLogA(  (char*)  "resetOutput called"  );

	if  (  FAILED(  hr  =  p->lpdsb->SetCurrentPosition( 0 )  )  )  goto  errLabel;
	
	p->dwMyWriteCursor  =  0;

	iErr  =  0;

errLabel:

	return  iErr;
}


 int startOutputBuf2(QMC_SOUND_MGR* pMgr, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p)
 {
	 int  iErr = -1;
	 myPLAY_SOUND_dx& myPs = *p;
	 HRESULT  hr;


	 /*
		 // Start output buffer.
		 if  (  FAILED(  hr = myPs.lpdsb->Play( 0, 0, DSBPLAY_LOOPING )  )  )  goto  errLabel;
		 myPs.bPlayStarted  =  TRUE;

		 if  (  FAILED(  hr  =  myPs.lpdsb->Stop(  )  )  )  goto  errLabel;
		 */

	 if (FAILED(hr = myPs.lpdsnOutput->SetNotificationPositions(myPs.dwNotifyCount, myPs.lpdsbpns))) {
		 traceLogA((char*)"playSound: SetNotificationPositions failed.");
		 goto  errLabel;
	 }

	 //  2015/07/30. 没有播放设备时，Play()会死在里面
#ifdef  __DEBUG__
		//showInfo_open0(  0,  0,  _T(  "playAudio: before myPs.lpdsb->Play( 0, 0, DSBPLAY_LOOPING )"  )  );
#endif
	 pPlayAudio->m_var.dwTickCnt_beforePlay = GetTickCount();
	 hr = myPs.lpdsb->Play(0, 0, DSBPLAY_LOOPING);
	 pPlayAudio->m_var.dwTickCnt_beforePlay = 0;
#ifdef  __DEBUG__
	 //showInfo_open0(  0,  0,  _T(  "playAudio: after myPs.lpdsb->Play( 0, 0, DSBPLAY_LOOPING )"  )  );
#endif
//
	 if (FAILED(hr))  goto  errLabel;


	 iErr = 0;
 errLabel:
	 return  iErr;

 }


//
 int  processOutput2( QMC_SOUND_MGR  *  pMgr,  PLAY_AUDIO_procInfo  *  pPlayAudio,  myPLAY_SOUND_dx  *  p,  BOOL  bFillWithSilence,  LPBYTE  pbInput1,  DWORD  dwNumBytes  )
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
		traceLogA(  (char*)  "processOutput: bufferLost"  );
        if ( FAILED( hr = p->lpdsb->Restore() ) ) {
            traceLogA(  (char*)  "Couldn't Restore output buffer."  );
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
		 traceLogA(  (char*)  "Output lock failure."  );
		 goto  errLabel;
	}


	iErr  =  0;

errLabel:
	return  iErr;
} // processOutput()







 //  BOOL  tmpHandler_bOldAudio(  void  *  p0,  QY_PLAYER  *  pPlayer,  myPLAY_AUDIO_DATA  *  pPkt  )
 BOOL  tmpHandler_bOldAudio(  DWORD  dwTickCnt_now,  QY_PLAYER  *  pPlayer,  myPLAY_AUDIO_DATA  *  pPkt  )
{
	BOOL					bRet		=	FALSE;
	//  p0
	TCHAR					tWhere[128]	=	_T(  ""  );

	//  2012/05/23
	_sntprintf(  tWhere,  mycountof(  tWhere  ),  _T(  "%I64u"  ),  pPlayer->idInfo_recorder.ui64Id  );

	//
	if  (  !dwTickCnt_now  )  {
		#ifdef  __DEBUG__
				MACRO_qyAssert(  0,  _T(  "tmphandler_bOldAudio err"  )  );
		#endif
		return  FALSE;
	}

	//  2011/11/27, 只有一个包时，不能移除
	//  if  (  getQ2Nodes_toGetMsg(  &pPlayer->audio.q2  )  <=  1  )  
	if  (  getQ2Nodes(  &pPlayer->audio.q2  )  <=  1  )  //  2015/02/20. 判断标准不是getMsgQ,而是2队列总和才行
	{
		return  FALSE;
	}

	//
	if  (  pPlayer->uiSampleTimeInMs_start  )  {
		if  (  pPkt->head.uiSampleTimeInMs  <  pPlayer->uiSampleTimeInMs_start  )  {

			traceLogA(  (char*)  "tmpHandler_bOldAudio: one pkt matched. < start"  );
			qyShowInfo1(  CONST_qyShowType_detail,  0,(char*)  "",  _T(  "IsClient"  ),  0,  tWhere,  _T(  ""  ),  _T(  "tmpHandler_bOldAudio: pkt.iSampleTimeInMs %d < start %d. matched"  ),  pPkt->head.uiSampleTimeInMs,  pPlayer->uiSampleTimeInMs_start  );

			bRet  =  TRUE;
			goto  errLabel;
		}
	}

	if  (  pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd  <  pPkt->head.uiSampleTimeInMs									 
		||  pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd  >  pPkt->head.uiSampleTimeInMs  +  5000  )
	{
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "tmpHandler_bOldAudio: one pkt matched. 0: pkt.st %d, st_newRecvd %d. qNodes %d,%d",  pPkt->head.uiSampleTimeInMs,  pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd,  pPlayer->audio.q2.qs[0].uiQNodes,  pPlayer->audio.q2.qs[1].uiQNodes  );
		#endif
		qyShowInfo1(  CONST_qyShowType_detail,  0,(char*)  "",  _T(  "IsClient"  ),  0,  tWhere,  _T(  ""  ),  _T(  "tmpHandler_bOldAudio: pkt.iSampleTimeInMs %d. newRecvd %d. matched"  ),  pPkt->head.uiSampleTimeInMs,  pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd  );

		bRet  =  TRUE;
		goto  errLabel;
	}

	if  (  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  )  {
		int  nWaitingInMs_audio  =  MACRO_getnWaitingInMs_audio_internal(  pPlayer->audio,  dwTickCnt_now  );
		if  (  nWaitingInMs_audio  >  0  &&  nWaitingInMs_audio  >  (  int  )pPlayer->audio.playCfg.usMaxTimeInMsToPlay  )  {
			int  nWaitingInMs_audioPkt  =  MACRO_getnWaitingInMs_audioPkt_internal(  pPkt->head.uiSampleTimeInMs,  pPlayer->audio,  dwTickCnt_now  );
			#ifdef  __DEBUG__
					#if  0
						 traceLogA(  (char*)  "tmpHandler_bOldAudio: nWaitingInMs_audioPkt %d, nodes %d",  nWaitingInMs_audioPkt,  getQ2Nodes_toGetMsg(  &pPlayer->audio.q2  )  );
					#endif
			#endif
			if  (  nWaitingInMs_audioPkt  >  0  &&  nWaitingInMs_audioPkt  >  (  int  )(  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  )  )  {

				if  (  !pPlayer->video.m_var.uiSampleTimeInMs_newRecvd					
					||  (  pPlayer->video.m_var.uiSampleTimeInMs_newRecvd  &&  pPkt->head.uiSampleTimeInMs  <  pPlayer->video.m_var.uiSampleTimeInMs_newRecvd  )  )
				{
					#ifdef  __DEBUG__
							traceLogA(  (char*)  "tmpHandler_bOldAudio: one pkt matched. 1: pkt.st %d, nWaiting_pkt %d, nWait_audio %d",  pPkt->head.uiSampleTimeInMs,  nWaitingInMs_audioPkt,  nWaitingInMs_audio  );
					#endif
					qyShowInfo1(  CONST_qyShowType_detail,  0,(char*)  "",  _T(  "IsClient"  ),  0,  tWhere,  _T(  ""  ),  _T(  "tmpHandler_bOldAudio: pkt.iSampleTimeInMs %d - audio.%d < toBeRemoved %d. matched"  ),  pPkt->head.uiSampleTimeInMs,  pPlayer->audio.m_var.uiSampleTimeInMs,  pPlayer->audio.playCfg.usMaxTimeInMsToBeRemoved  );
	
					bRet  =  TRUE;
					goto  errLabel;
				}
			}
		}
	}


errLabel:
	return  bRet;
}








//
int  MACRO_getnWrite_toFillSilence1(  myPLAY_SOUND_dx * myPs  )  {
//	(  (  !(  nAvgBytesPerSec  %  5  )  )  ?  (  nAvgBytesPerSec  /  5  )  :  nAvgBytesPerSec  )
	return  myPs->dwOffset_notify_unit;
}


 //  2012/01/27
 int  doPlayAudio( QY_PLAYER  * pPlayer, bool * pbQuit1 )
{
	int  iErr =  -1;
	 QY_MC						*	pQyMc						=	g_pQyMc;
	 if  (  !pQyMc  )  return  -1;
	 CCtxQmc  *  pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();

	 //
	 bool  bDbg  =  false;

	 //
	 DYN_LIB_DX					*	pDynLib						=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;

	 //
	 PLAY_AUDIO_procInfo		*	pPlayAudio					=	&pPlayer->audio;

	 //
	 QMC_SOUND_MGR				*	pMgr						=	&gQmcSoundMgr;
	 myPLAY_SOUND_dx				myPs;

	 DWORD							dwThreadId					=	GetCurrentThreadId(  );
	 int							i;
	 HRESULT						hr;
	 int							len;

	 CQyMalloc						mallocObj_pBuf;
	 char						*	pBuf						=	NULL;
	 unsigned  int					uiBufSize;

	 char						*	pLeft						=	NULL;									//  2009/04/27
	 unsigned  int					nLeft						=	0;

	 unsigned  int					uiSampleTimeInMs_pLeft		=	0;										//  2009/05/04
	 unsigned  int					dwBytes_cur2Write			=	0;

	 unsigned  int					nAvgBytesPerSec				=	0;


	 //
	 CQyTick						tickObj;
	 DWORD							dwTickCnt_lastAudioData		=	M_GetTickCount_audio(  tickObj  );;						// 
	 BOOL							bLocalAudio					=	FALSE;

	 //  TRANSFER_AUDIO_dataMem			pkt;
	 //CQyMalloc						mallocObj_pPkt;
	 //unsigned  int					uiBufSize_pPkt				=	offsetof(  myPLAY_AUDIO_DATA,  buf  )  +  pProcInfo->cfg.uiBufSize_myPlayAudioData;	//  sizeof(  myPLAY_AUDIO_DATA  );
	 //int							iAllocType					=	0;	//  CONST_iAllocType_audio
	 myPLAY_AUDIO_DATA				tmp_pkt;
	 myPLAY_AUDIO_DATA			*	pPkt						=	&tmp_pkt;//  (  myPLAY_AUDIO_DATA  *  )mallocObj_pPkt.mallocf(  iAllocType,  uiBufSize_pPkt  );
	 if  (  !pPkt  )  return  -1;
	 int							pktLen;

	 int							nWrite						=	0;  
	 unsigned  int					uiTimeInMs_nWrite;
	 BOOL							bNeedCheck_oldAudio			=	FALSE;
	 DWORD							dwTickCnt_bNeedCheck_oldAudio  =  0;	//  2015/07/03
	
	 //
	 bool  tmp_bQuit = false;

//  2011/11/30
//  #define		DEFAULT_dwToInMs_playAudio		5000
#define		DEFAULT_dwToInMs_playAudio		200


	 DWORD							dwToInMs					=	DEFAULT_dwToInMs_playAudio;
	 DWORD							iNotifyInterval;

	 //
	 int							dwTickCnt_last				=	0;


	 //
	 memset(  &myPs,  0,  sizeof(  myPs  )  );


	 traceLogA(  (char*)  "playSound %S enters",  pPlayAudio->q2.cfg.name  );

	 //
	 //	   
	 if (1) {
			pPlayer->audio.ah.wfx.wFormatTag = WAVE_FORMAT_PCM;
			traceLog((TCHAR*)_T("doPlayAudio: set wFormatTag to pcm"));	   
	 }


	 //
	 nAvgBytesPerSec  =  pPlayer->audio.ah.wfx.nAvgBytesPerSec;
	 if  (  !nAvgBytesPerSec  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "mcThreadProc_playAudio failed: nAvgBytesPerSec is 0"  );
		 #endif
		 showInfo_open0(  0,  0,  _T(  "playAudio failed: nAvgBytesPerSec is 0"  )  );
		 goto  errLabel;
	 }

	 // Create the events. We make an extra one for later use 
	 // by the output buffer.
	 /*
	 for  (  i  =  0;  i  <  mycountof(  pPlayAudio->hEvents  );  i  ++  )  {
		  pPlayAudio->hEvents[i] = CreateEvent( NULL, FALSE, FALSE, NULL );
		  if ( NULL == pPlayAudio->hEvents[i] ) goto  errLabel;
	 }
	 */

	 //  fix playCfg. 2009/06/14
	 fixPlayCfg(  pProcInfo,  &pPlayAudio->playCfg  );
	 iNotifyInterval  =  pPlayAudio->playCfg.usNotifyIntervalInMs_needMoreAudioData;


	 if  (  iNotifyInterval  >=  pPlayAudio->playCfg.usAudioDataAddedToPlayEveryTime  ||  iNotifyInterval  >=  pPlayAudio->playCfg.usMinTimeInMsOfAudioDataPlaying  )  {
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u iNotifyInterval too big %d"  ),  pPlayAudio->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id,  iNotifyInterval  );
		 goto  errLabel;
	 }


	 //
	 if (!pQyMc->appParams.bMcu) {
		 if (bLocalAudio)  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s, Local audio, starts"), pPlayAudio->q2.cfg.name);
		 else  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s, %I64u starts"), pPlayAudio->q2.cfg.name, pPlayer->idInfo_recorder.ui64Id);
	 }

	 //  getMsg from q

	 uiBufSize  =  max(  (  CONST_bufSize_transferAudioData  +  256  )  *  2,  pPlayAudio->ah.wfx.nAvgBytesPerSec  *  2  );
	 pBuf  =  (  char  *  )mallocObj_pBuf.mallocf(  uiBufSize  );
	 if  (  !uiBufSize  ||  !pBuf  )  goto  errLabel;

	 //
	 pLeft  =  pBuf;  nLeft  =  0;


	 //	 			  
	 if  (  !myPs.bPlayInited  )  
	 {


				  DWORD		dwOffset_notify_unit	=	0;  //pPlayAudio->ah.wfx.nAvgBytesPerSec;
				  if  (  pPlayAudio->ah.wfx.nAvgBytesPerSec  %  100  )  {
					  traceLog((TCHAR*)  _T(  "doPlayAudio failed, nAvgBytesPerSec can't devided by 100"  )  );
					  goto  errLabel;
				  }
				  dwOffset_notify_unit  =  pPlayAudio->ah.wfx.nAvgBytesPerSec  /  100;

			  
				  //
				  if  (  pProcInfo->pPlayDev->initPlay_dx(  pDynLib,  pPlayAudio,  dwOffset_notify_unit  *  CONST_playerNotifyCnt,  &myPs  )  )  goto  errLabel;

				  //
				  myPs.dwOffset_notify_unit  =  dwOffset_notify_unit;
				  myPs.dwNotifyCount  =  CONST_playerNotifyCnt;//myPs.dsbDesc.dwBufferBytes  /  myPs.dwOffset_notify_unit;
				  myPs.lpdsbpns  =  (  LPDSBPOSITIONNOTIFY  )mymalloc(  myPs.dwNotifyCount  *  sizeof(  DSBPOSITIONNOTIFY  )  );
				  if  (  !myPs.lpdsbpns  )  goto  errLabel;
				  memset(  myPs.lpdsbpns,  0,  myPs.dwNotifyCount  *  sizeof(  DSBPOSITIONNOTIFY  )  );
				  
				  for  (  i  =  0;  i  <  (  int  )myPs.dwNotifyCount;  i  ++  )  {					   
					  myPs.notifEvents[i]=CreateEvent(NULL, FALSE, FALSE,NULL);
					   //myPs.lpdsbpns[i].dwOffset  =  (  i  +  1  )  *  myPs.dwOffset_notify_unit  /  2  -  1;
					   myPs.lpdsbpns[i].dwOffset  =  (  i  +  0.5  )  *  myPs.dwOffset_notify_unit  -  1;
					   myPs.lpdsbpns[i].hEventNotify  =  myPs.notifEvents[i];

					   //
					   if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
						   traceLogA((char*)"lpdsbpns[%d].dwOffset %d,  dwBufferBytes %d", i, myPs.lpdsbpns[i].dwOffset, myPs.dsbDesc.dwBufferBytes);
					   }
				  }				  

				  //
				  if  (  !pPlayAudio->ah.wfx.nAvgBytesPerSec  )  goto  errLabel;

				  //  
				  myPs.uiMaxMsgWaiting  =  (  bLocalAudio  ?  2  :  10  );
#ifdef  __DEBUG__	//  for test
				  //  traceLogA(  (char*)  "Warning: myPs.usMaxMsgWaiting is set to 100 for test. 2009/04/27"  );
				  //  myPs.uiMaxMsgWaiting  =  100;
#endif
				  if  (  !myPs.uiMaxMsgWaiting  )  {
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u, uiMaxMsgWaiting error: %d."  ),  pPlayAudio->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id,  myPs.uiMaxMsgWaiting  );
					  goto  errLabel;
				  }

			  
	 }


	
	 if  (  !myPs.bPlayStarted  )  
	 {

				  traceLogA(  (char*)  "before play"  );

				#if  0
				  if  (  !bWriteSilenceToOutput(  &myPs,  0,  myPs.dsbDesc.dwBufferBytes  )  )  {
					  traceLogA(  (char*)  "initPlay_dx: bWriteSilenceToOutput failed."  );
					  goto  errLabel;
				  }
				#endif
			  
				  nWrite  =  MACRO_getnWrite_toFillSilence1(  &myPs  );
				  if  (  pProcInfo->pPlayDev->processOutput(  pMgr,  pPlayAudio,  &myPs,  TRUE,  NULL,  nWrite  )  )  {
					  traceLogA(  (char*)  "playSound: processOutput failed, try to restart"  );
					  goto  errLabel;					  
				  }
				  uiTimeInMs_nWrite  =  (  nWrite  *  1000  /  nAvgBytesPerSec  );
				  pPlayAudio->m_var.uiTimeInMs_audio_remains  +=  uiTimeInMs_nWrite;


#if  0
				  if (0) {
					  /*
					  // Start output buffer.
					  if  (  FAILED(  hr = myPs.lpdsb->Play( 0, 0, DSBPLAY_LOOPING )  )  )  goto  errLabel;
					  myPs.bPlayStarted  =  TRUE;

					  if  (  FAILED(  hr  =  myPs.lpdsb->Stop(  )  )  )  goto  errLabel;
					  */

					  if (FAILED(hr = myPs.lpdsnOutput->SetNotificationPositions(myPs.dwNotifyCount, myPs.lpdsbpns))) {
						  traceLogA((char*)"playSound: SetNotificationPositions failed.");
						  goto  errLabel;
					  }

					  //  2015/07/30. 没有播放设备时，Play()会死在里面
#ifdef  __DEBUG__
		//showInfo_open0(  0,  0,  _T(  "playAudio: before myPs.lpdsb->Play( 0, 0, DSBPLAY_LOOPING )"  )  );
#endif
					  pPlayAudio->m_var.dwTickCnt_beforePlay = GetTickCount();
					  hr = myPs.lpdsb->Play(0, 0, DSBPLAY_LOOPING);
					  pPlayAudio->m_var.dwTickCnt_beforePlay = 0;
#ifdef  __DEBUG__
					  //showInfo_open0(  0,  0,  _T(  "playAudio: after myPs.lpdsb->Play( 0, 0, DSBPLAY_LOOPING )"  )  );
#endif
//
					  if (FAILED(hr))  goto  errLabel;
				  }
#endif 
				  //
				  if (pProcInfo->pPlayDev->startOutputBuf(pMgr, pPlayAudio, &myPs)) {
					  goto  errLabel;
				  }

				  //
				  myPs.bPlayStarted  =  TRUE;
				
				  //  continue;
			  
	 }



	 //  runBuffers_play(  pMgr,  &myPs  );
	 //  bPlayStarted  =  TRUE;


	 //
	 for (;  bPlayerOk(pPlayer, 0); ) {
		  
		  if  (  !dwToInMs  ||  dwToInMs  >  DEFAULT_dwToInMs_playAudio  )  {			  
			  #if  0
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: mcThreadProc_playAudio: dwToInMs %d"  ),  dwToInMs  );
			  #endif
			  dwToInMs  =  DEFAULT_dwToInMs_playAudio;
			  #ifdef  __DEBUG__
					  //  traceLog((TCHAR*)  _T(  "Warning: mcThreadProc_playAudio: dwToInMs %d"  ),  dwToInMs  );
			  #endif
		  }

		  //
		  if (pQyMc->appParams.bUse_playDev_dummy) {
			  int  nQNodes = getQ2Nodes(&pPlayAudio->q2);			  
			  dwToInMs = 10;
			  //
			  if (nQNodes > 50)  dwToInMs = 7;
			  else  if (nQNodes > 35)  dwToInMs = 8;
			  else  if (nQNodes > 20)  dwToInMs = 9;
		  }

		  //
		  DWORD  dwTickCnt0  =  M_GetTickCount_audio(  tickObj  );
		  DWORD  dwTickCnt;
		  DWORD  dwEvt  =  WaitForMultipleObjects(
							 CONST_playerNotifyCnt,			//  mycountof(  pPlayAudio->hEvents  ),		// Number of events.
							 myPs.notifEvents,					// Location of handles.
                             FALSE,										// Wait for all?
                             dwToInMs								// How long to wait?
                               );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  goto  errLabel;
		  //
#if  0  //  这里似乎超时处理不需要. 2026/02/13
		  if  (  dwEvt  ==  WAIT_TIMEOUT  )  {
			  traceLog((TCHAR*)  _T(  "doPlayAudio failed: waitFor event timeout"  )  );
			  goto  errLabel;
		  }
#endif 

		  //
		  DWORD  dwTickCnt_cur = myGetTickCount(mynull);
		  int iDiffInMs = dwTickCnt_cur - dwTickCnt_last;
		  dwTickCnt_last = dwTickCnt_cur;
		  TCHAR  tBuf[128];


		  //
#ifdef  __DEBUG__
#if  0
		  //
		  int nQNodes_left;
		  nQNodes_left = getQ2Nodes(&pPlayAudio->q2);
		  //
		  _sntprintf(tBuf, mycountof(tBuf), _T("doPlayAudio: %I64u %d, iDiffInMs %dms. ind_player %d, nQNodes_left %d. "), pPlayer->idInfo_recorder.ui64Id,  pPlayer->audio.uiTranNo,  iDiffInMs,  pPlayer->playerId.index_player,  nQNodes_left);
		  showInfo_open0(0, 0, tBuf);
#endif
#endif



		  //		  		  
		  for  (  ;  nLeft  <  myPs.dwOffset_notify_unit;  )  
		  {
			   if  (  pLeft  !=  pBuf  )  {		
				   if  (  nLeft  )  memcpy(  pBuf,  pLeft,  nLeft  );
				   pLeft  =  pBuf; 
			   }

			   //
			   int							iTimeInMs_nLeft				=	0;
			   iTimeInMs_nLeft  =  (  int  )(  nLeft  *  1000.  /  nAvgBytesPerSec  );

			   //
			   len  =  uiBufSize  -  nLeft;		
			   if  (  len  <=  0  )  {
				   traceLogA(  (char*)  "mcThreadproc_playSound failed: len %d < 0",  len  );
				   goto  errLabel;
			   }
			   if(  len < myPs.dwOffset_notify_unit  )  {
				   goto errLabel;
			   }
			   //
			   //
			   len  =  myPs.dwOffset_notify_unit;			//  2016/12/14
			   len = my_inStream(  pPlayer,  pLeft  +  nLeft,  (void  *  )len  );
			   if  ( len ==  0  )  {
				   //
				   traceLog((TCHAR*)  _T(  "doPlayAudio will quit, my_inStream returns 0"  )  );
				   //
				   tmp_bQuit  =  true;
				   iErr  =  0;  goto errLabel;
			   }
			   //
			   nLeft  +=  len;
			   //
			   if (bDbg) {
				   traceLog((TCHAR*)_T("doPlayAudio: my_instream returns %d"), len);
			   }
			   //
			   continue;
		  }

		  if  (  !nLeft  )  {
			  traceLog((TCHAR*)  _T(  "doPlayAudio failed, nLeft is 0"  )  );
			  goto  errLabel;
		  }
		  if  (  nLeft  )  {		  				  
				  
			  nWrite  =  min(  myPs.dwOffset_notify_unit,  nLeft  );
			  //
			  if  (  pProcInfo->pPlayDev->processOutput(  pMgr,  pPlayAudio,  &myPs,  FALSE,  (  LPBYTE  )pLeft,  nWrite  )  )  {
				  traceLogA(  (char*)  "playSound: processOutput failed, try to restart"  );
				  goto  errLabel;
			  }
			  // 
			  if  (  !pQyMc->appParams.bNoAec  )
			  {
				  QY_PLAYER* pPlayer_mix = getPlayerByIndex(pProcInfo, pProcInfo->av.mixProcInfo.iIndex_localPlayer);
				  if (pPlayer_mix == pPlayer)
				  {
					  ORG_audio_pkt	pkt;
					  memset(&pkt, 0, offsetof(ORG_audio_pkt, buf));
					  if (nWrite > sizeof(pkt.buf)) {
						  showInfo_open0(0, 0, _T("doPlayAudio failed, nWrite > org_audio_pkt.buf"));
						  goto  errLabel;
					  }
					  memcpy(pkt.buf, pLeft, nWrite);
					  pkt.len = nWrite;
					  //
					  if (q2PostMsg(&pkt, sizeof(pkt), &pProcInfo->av.aecInfo.aecPlayQ2, _T("doPlayAudio"))) {
						  traceLog((TCHAR*)_T("doPlayAudio: postMsg 2 aecPlayQ2 failed"));
					  }
				  }
			  }
			  //
			  uiTimeInMs_nWrite  =  (  nWrite  *  1000  /  nAvgBytesPerSec  );
			  pPlayAudio->m_var.uiTimeInMs_audio_remains  +=  uiTimeInMs_nWrite;

			  pLeft  +=  nWrite;
			  nLeft  -=  nWrite;

			  //
			  static uint stickCnt=0;
			  uint tickCnt=myGetTickCount(mynull);
			  int iDiffInMs = tickCnt-stickCnt;
			  stickCnt=tickCnt;

			  //
#if  0  //  这段代码没用
			  DWORD							dwCurPlayCursor;

			  //		  
			  if  (  FAILED(  hr  =  myPs.lpdsb->GetCurrentPosition(  &dwCurPlayCursor,  NULL  )  )  )  {
				  traceLogA(  (char*)  "playSound: GetCurrentPosition failed.1"  );
				  goto  errLabel;
			  }

			  //
			  if (  bDbg  )  {
				  traceLog((TCHAR*)  _T(  "doPlayAudio: processOutput nWrite %d. elapse %dms. nLeft %d. playCursor %d, writeCursor %d\n"  ),  nWrite,  iDiffInMs, nLeft, dwCurPlayCursor, myPs.dwMyWriteCursor  );
			  }
#endif 
		  }

		  
		  //
		  continue;
	 }

 
	 traceLogA(  (char*)  "doPlayAudio will quit"  );
	 iErr  =  0;

errLabel:

	 if  (  myPs.bPlayInited  )  {
		 pProcInfo->pPlayDev->exitPlay_dx(  pDynLib,  pPlayAudio,  &myPs  );
	 }
	 for (size_t i = 0; i < mycountof(myPs.notifEvents); i++){
		if (myPs.notifEvents[i]){
			CloseHandle(myPs.notifEvents[i]);
			myPs.notifEvents[i] = NULL;
		}
	}


	 //
	 if (!pQyMc->appParams.bMcu) {
		 if (bLocalAudio)  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s, Local audio, ends."), pPlayAudio->q2.cfg.name);
		 else  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s, %I64u ends."), pPlayAudio->q2.cfg.name, pPlayer->idInfo_recorder.ui64Id);
	 }


	 if (pbQuit1) {
		 *pbQuit1 = tmp_bQuit;
	 }

	 //
	traceLogA(  (char*)  "doPlayAudio %S leaves",  pPlayAudio->q2.cfg.name  );

	return  0;
}


//
 extern "C" DWORD WINAPI mcThreadProc_playAudio( LPVOID lpParameter )
{
	 MC_VAR_isCli					*	pProcInfo					=	(  MC_VAR_isCli  *  )lpParameter;
	 if (  !pProcInfo  )  return  -1;
	 QY_MC						*	pQyMc						=	pProcInfo->pQyMc;
	 if  (  !pQyMc  )  return  -1;

	 //
	 DYN_LIB_DX					*	pDynLib						=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;

	 QY_PLAYER					*	pPlayer						=	NULL;
	 PLAY_AUDIO_procInfo		*	pPlayAudio					=	NULL;

	 QMC_SOUND_MGR				*	pMgr						=	&gQmcSoundMgr;
	 //myPLAY_SOUND_dx				myPs;

	 DWORD							dwThreadId					=	GetCurrentThreadId(  );
	 int							i;
	 HRESULT						hr;
	 int							len;

	 CQyMalloc						mallocObj_pBuf;
	 char						*	pBuf						=	NULL;
	 unsigned  int					uiBufSize;

	 char						*	pLeft						=	NULL;									//  2009/04/27
	 unsigned  int					nLeft						=	0;

	 unsigned  int					uiSampleTimeInMs_pLeft		=	0;										//  2009/05/04
	 unsigned  int					dwBytes_cur2Write			=	0;

	 unsigned  int					nAvgBytesPerSec				=	0;

	 DWORD							dwCurPlayCursor;

	 //
	 CQyTick						tickObj;
	 DWORD							dwTickCnt_lastAudioData		=	M_GetTickCount_audio(  tickObj  );;						// 
	 BOOL							bLocalAudio					=	FALSE;

	 //  TRANSFER_AUDIO_dataMem			pkt;
	 //CQyMalloc						mallocObj_pPkt;
	 //unsigned  int					uiBufSize_pPkt				=	offsetof(  myPLAY_AUDIO_DATA,  buf  )  +  pProcInfo->cfg.uiBufSize_myPlayAudioData;	//  sizeof(  myPLAY_AUDIO_DATA  );
	 //int							iAllocType					=	0;	//  CONST_iAllocType_audio
	 myPLAY_AUDIO_DATA				tmp_pkt;
	 myPLAY_AUDIO_DATA			*	pPkt						=	&tmp_pkt;//  (  myPLAY_AUDIO_DATA  *  )mallocObj_pPkt.mallocf(  iAllocType,  uiBufSize_pPkt  );
	 if  (  !pPkt  )  return  -1;
	 int							pktLen;

	 int							nWrite						=	0;  
	 unsigned  int					uiTimeInMs_nWrite;
	 BOOL							bNeedCheck_oldAudio			=	FALSE;
	 DWORD							dwTickCnt_bNeedCheck_oldAudio  =  0;	//  2015/07/03
		  
//  2011/11/30
//  #define		DEFAULT_dwToInMs_playAudio		5000
#define		DEFAULT_dwToInMs_playAudio		200

//
#define		MACRO_getnWrite_toFillSilence(  nAvgBytesPerSec  )	(  (  !(  nAvgBytesPerSec  %  5  )  )  ?  (  nAvgBytesPerSec  /  5  )  :  nAvgBytesPerSec  )

	 DWORD							dwToInMs					=	DEFAULT_dwToInMs_playAudio;
	 DWORD							iNotifyInterval;

	 //memset(  &myPs,  0,  sizeof(  myPs  )  );

	 if  (  dwThreadId  ==  pProcInfo->av.localAv.player.audio.dwThreadId  )  {
		 pPlayer  =  &pProcInfo->av.localAv.player;
		 pPlayAudio  =  &pProcInfo->av.localAv.player.audio;
		 bLocalAudio  =  TRUE;
		 }
	 else  {
		   for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
			    if  (  dwThreadId  ==  pProcInfo->av.pPlayers[i].audio.dwThreadId  )  break;
		   }
		   if  (  i  ==  pProcInfo->av.usCnt_players  )  {
			   return  -1;
		   }
		   pPlayer  =  &pProcInfo->av.pPlayers[i];
		   pPlayAudio  =  &pProcInfo->av.pPlayers[i].audio;
	 }

	 traceLogA(  (char*)  "playSound %S enters",  pPlayAudio->q2.cfg.name  );

	 //
	 nAvgBytesPerSec  =  pPlayer->audio.ah.wfx.nAvgBytesPerSec;
	 if  (  !nAvgBytesPerSec  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "mcThreadProc_playAudio failed: nAvgBytesPerSec is 0"  );
		 #endif
		 showInfo_open0(  0,  0,  _T(  "playAudio failed: nAvgBytesPerSec is 0"  )  );
		 goto  errLabel;
	 }

	 int maxDataBufLen; maxDataBufLen = 48000 * 2 * 3 / 2;
	 if (pPlayer->audio.qBuf2->alloc(maxDataBufLen) != 0) goto errLabel;


	 // Create the events. We make an extra one for later use 
	 // by the output buffer.
	 /*
	 for  (  i  =  0;  i  <  mycountof(  pPlayAudio->hEvents  );  i  ++  )  {
		  pPlayAudio->hEvents[i] = CreateEvent( NULL, FALSE, FALSE, NULL );
		  if ( NULL == pPlayAudio->hEvents[i] ) goto  errLabel;
	 }
	 */

	 //  fix playCfg. 2009/06/14
	 fixPlayCfg(  pProcInfo,  &pPlayAudio->playCfg  );
	 iNotifyInterval  =  pPlayAudio->playCfg.usNotifyIntervalInMs_needMoreAudioData;


	 if  (  iNotifyInterval  >=  pPlayAudio->playCfg.usAudioDataAddedToPlayEveryTime  ||  iNotifyInterval  >=  pPlayAudio->playCfg.usMinTimeInMsOfAudioDataPlaying  )  {
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u iNotifyInterval too big %d"  ),  pPlayAudio->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id,  iNotifyInterval  );
		 goto  errLabel;
	 }

	 //
	 //pPlayAudio->bQuit  =  FALSE;
	 pPlayAudio->dwTickCnt_start  =  M_GetTickCount_audio(  tickObj  );		//  2010/05/04
	 pPlayAudio->bRunning  =  TRUE;
	 pPlayer->uiSampleTimeInMs_start  =  0;
	 memset(  &pPlayAudio->m_var,  0,  sizeof(  pPlayAudio->m_var  )  );

	 //
	 if (!pQyMc->appParams.bMcu) {
		 if (bLocalAudio)  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s, Local audio, starts"), pPlayAudio->q2.cfg.name);
		 else  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s, %I64u starts"), pPlayAudio->q2.cfg.name, pPlayer->idInfo_recorder.ui64Id);
	 }

	 //  getMsg from q

	 uiBufSize  =  max(  (  CONST_bufSize_transferAudioData  +  256  )  *  2,  pPlayAudio->ah.wfx.nAvgBytesPerSec  *  2  );
	 pBuf  =  (  char  *  )mallocObj_pBuf.mallocf(  uiBufSize  );
	 if  (  !uiBufSize  ||  !pBuf  )  goto  errLabel;

	 //
	 pLeft  =  pBuf;  nLeft  =  0;

	 //  runBuffers_play(  pMgr,  &myPs  );
	 //  bPlayStarted  =  TRUE;

	 for  (  ;  bPlayerOk(pPlayer,0);  )  {
		 		 
		 bool  bQuit  =  false;
		 doPlayAudio(  pPlayer,  &bQuit  );
		 if(  bQuit  )  break;

		 //		 
		 continue;
	 }

 
	 traceLogA(  (char*)  "mcThreadProc_playSound will quit"  );

errLabel:

	 //
	 pPlayAudio->qBuf2->dofree();


	 //
	 if (!pQyMc->appParams.bMcu) {
		 if (bLocalAudio)  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s, Local audio, ends."), pPlayAudio->q2.cfg.name);
		 else  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s.1733, %I64u ends."), pPlayAudio->q2.cfg.name, pPlayer->idInfo_recorder.ui64Id);
	 }
	 
	 //  if  (  pBuf  )  free(  pBuf  );
	 
	 //
	 pPlayAudio->bRunning  =  FALSE;

	 /*
	 for  (  i  =  0;  i  <  mycountof(  pPlayAudio->hEvents  );  i  ++  )  {
		  if  (  pPlayAudio->hEvents[i]  )  {
			  CloseHandle(  pPlayAudio->hEvents[i]  );  pPlayAudio->hEvents[i]  =  NULL;
		  }
	 }
	 */

#if  0
	 //  2013/05/27. 对本地音频,如果没有设置bQuit,那么就是出错退出的. 因为aec的需要,所以需要重新激发起来
	 if  (  bLocalAudio  )  {
		 if  (  !pPlayAudio->bQuit  )  {
			 PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_inputErr_aec,  0  );
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Local audio player: postMsg to notify inputErr"  )  );
		 }
	 }
#endif

	traceLogA(  (char*)  "playSound %S leaves",  pPlayAudio->q2.cfg.name  );

	return  0;
}








