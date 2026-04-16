// QyPlaySound.cpp : implementation file
//

#include	"stdafx.h"
#include	<mmsystem.h>
#include	<mmreg.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"QyPlaySound_wave.h"

#include	"qyAvRecordPublic.h"
//  #include	<dbgapi.h>
#include	"isCliHelpPublic.h"

#include	"ctxQmc.h"
#include	"qmcCommFunc_isCli.h"


//
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int  get_pcm_forAcm(  unsigned  int  uiCapType,  WAVEFORMATEX  *  pWfx  );


#ifdef  __DEBUG__

 int  dumpWaveFormat(  WAVEFORMATEX  *  pWfx  )
{
	traceLog((TCHAR*)  _T(  "dumpWaveFormat enters"  )  );

	traceLog((TCHAR*)  _T(  "wFormatTag %d,  nAvgBytesPerSec %d,  cbSize %d"  ),  pWfx->wFormatTag,  pWfx->nAvgBytesPerSec,  pWfx->cbSize  );
	int		i;
	TCHAR	tBuf[256]  =  _T(  ""  );
	unsigned  char	*	p		=	(  unsigned  char  *  )pWfx;
	p  +=  sizeof(  WAVEFORMATEX  );
	for  (  i  =  0;  i  <  pWfx->cbSize;  i  ++  )  {
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,0x%02x"  ),  tBuf,  p[i]  );		  
	}
	traceLog((TCHAR*)  _T(  "[%s]"  ),  tBuf  );

	traceLog((TCHAR*)  _T(  "dumpWaveFormat leaves"  )  );

	return  0;
}

#endif



/////////////////////////////////////////////////////////////////////////////
// CQyPlaySound

CQyPlaySound::CQyPlaySound(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CQyPlaySound::~CQyPlaySound()
{
	//  traceLog((TCHAR*)  _T(  "~playSound 0"  )  );
	//  if  (  m_var.m_pSemaphore  )  delete  m_var.m_pSemaphore;
	//  traceLog((TCHAR*)  _T(  "~playSound 1"  )  );

	if  (  m_var.pBuf  )  free(  m_var.pBuf  );
}




BOOL CQyPlaySound::bStartPlaying(WPARAM wParam, LPARAM lParam)
{	
	MMRESULT		mmReturn = 0;
	//  CQySyncObj		syncObj;

	if  (  !m_var.pPlayer  )  return  FALSE;

	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  m_var.pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playSound %I64u: will start"  ),  m_var.pPlayer->idInfo_recorder.ui64Id  );

	//  if  (  syncObj.sync(  m_var.mutexName_syncStartStop  )  )  return  FALSE;

	if  (  m_var.pPlayer->audio.bRunning  )  return FALSE;

	//  log.WriteString("\n Starting playing");

#ifdef  __DEBUG__
		//  dumpWaveFormat(  &m_var.pPlayer->audio.ah.wfx  );
#endif
	
	// open wavein device
	mmReturn = ::waveOutOpen( &m_var.m_hPlay, WAVE_MAPPER,
		&m_var.pPlayer->audio.ah.wfx, ::GetCurrentThreadId(), 0, CALLBACK_THREAD);
		
	if  (  mmReturn  )  {
		displayError(mmReturn,(char*)"PlayStart");	
		return  FALSE;
	}

	m_var.pPlayer->audio.bQuit  =  FALSE;
	m_var.pPlayer->audio.dwTickCnt_start  =  GetTickCount(  );
	m_var.pPlayer->audio.bRunning = TRUE;
	m_var.pPlayer->uiSampleTimeInMs_start  =  0;
	memset(  &m_var.pPlayer->audio.m_var,  0,  sizeof(  m_var.pPlayer->audio.m_var  )  );
	
	return  TRUE;
}








BOOL CQyPlaySound::bStopPlaying(WPARAM wParam, LPARAM lParam)
{
	MMRESULT		mmReturn	=	0;
	CQySyncObj		syncObj;

	if  (  !m_var.pPlayer  )  return  FALSE;

	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  m_var.pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playSound %I64u: will stop"  ),  m_var.pPlayer->idInfo_recorder.ui64Id  );
	
	m_var.pPlayer->audio.bRunning  =  FALSE;

	//  log.WriteString("\n Stopped  playing");
	MSG msg;
	mmReturn = ::waveOutReset(m_var.m_hPlay);
	Sleep(20);
	while  (  ::PeekMessage(&msg,NULL,MM_WOM_OPEN,MM_WOM_DONE,  PM_REMOVE))  {
		   if  (  msg.message  ==  MM_WOM_OPEN  ||  msg.message  ==  MM_WOM_CLOSE  )  continue;			
		   OnEndPlaySoundData(msg.wParam,msg.lParam);
		   Sleep(5);
	}
		
	Sleep(500);

	if(!mmReturn)  {
		mmReturn = ::waveOutClose(  m_var.m_hPlay  );
		if  (  !mmReturn  )  m_var.m_hPlay  =  NULL;
	}

	return  TRUE;

}


void  CQyPlaySound::OnMmWomOpen(WPARAM wParam, LPARAM lParam)
{
	//  m_var.dwTickCnt_devOpen  =  GetTickCount(  );
	m_var.bDevOk  =  TRUE;
	return;
}


void CQyPlaySound::OnEndPlaySoundData(WPARAM wParam, LPARAM lParam)
{
	LPWAVEHDR lpHdr = (LPWAVEHDR) lParam;
	
	//  OutputDebugString(  _T(  "CQyPlaySound::OnEndPlaySoundData\n"  )  );
	if  (  lpHdr  )  {

		#ifdef  __DEBUG__
				#if  10
					if  (  !m_var.pPlayer->audio.bRunning  )  {
						traceLog((TCHAR*)  _T(  "OnEndPlaySoundData: bRunning is false, m_iSoundBuffers %d"  ),  m_var.m_nOutputBuffers  );			
					}
				#endif
		#endif

		::waveOutUnprepareHeader(  m_var.m_hPlay, lpHdr, sizeof(WAVEHDR));
	
		m_var.m_nOutputBuffers  --  ;
		
		//  2010/06/21
		DWORD	dwTickCnt	=	GetTickCount(  );
		int  iIndex  =  lpHdr->dwUser;
		if  (  iIndex  <  0  &&  iIndex  >=  mycountof(  m_var.helpStruct.mems  )  )  traceLog((TCHAR*)  _T(  "PlaySound err: EndPlaySoundData, iIndex error"  )  );
		else  {
				  if  (  m_var.helpStruct.mems[iIndex].lpHdr  !=  lpHdr  )  traceLog((TCHAR*)  _T(  "PlaySound err: EndPlaySoundData, lpHdr is not matched"  )  );
				  else  {
					    //
					    m_var.helpStruct.rtPlaying  -=  m_var.helpStruct.mems[iIndex].ui_rtTimeLen;

						#if  1
						    #ifdef  __DEBUG__
									#if  0
										int iDiff_uiSampleTimeInMs  =  m_var.helpStruct.mems[iIndex].iSampleTimeInMs  -  m_var.pPlayer->audio.m_var.uiSampleTimeInMs;
										int dwTickCnt_uiSampleTimeInMs  =  dwTickCnt  -  (  int  )(  m_var.helpStruct.mems[iIndex].ui_rtTimeLen  /  10000  );
										int	iDiff_dwTickCnt  =  dwTickCnt_uiSampleTimeInMs  -  m_var.pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs;
										traceLog((TCHAR*)  _T(  "playSound: EndData, iIndex %d, st %d, tickCnt %d, diff_st %d, diff_tickCnt %d, nO %d, rtPlaying %d"  ),  iIndex,  m_var.helpStruct.mems[iIndex].iSampleTimeInMs,  dwTickCnt_uiSampleTimeInMs,  iDiff_uiSampleTimeInMs,  iDiff_dwTickCnt,  m_var.m_nOutputBuffers,  m_var.helpStruct.rtPlaying  );
									#endif
							#endif

							m_var.pPlayer->audio.m_var.uiSampleTimeInMs  =  m_var.helpStruct.mems[iIndex].iSampleTimeInMs;	//  +  m_var.helpStruct.mems[iIndex].ui_rtTimeLen  /  10000;
							m_var.pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  =  dwTickCnt  -  (  int  )(  m_var.helpStruct.mems[iIndex].ui_rtTimeLen  /  10000  );	//  5000;
							m_var.pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_internal  =  m_var.pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_syncRecv;
							//
							m_var.helpStruct.bModified_uiSampleTimeInMs_audio  =  TRUE;

						#endif

						//
						m_var.helpStruct.mems[iIndex].lpHdr  =  NULL;
				  }
	
		}	

		if  (  !m_var.m_nOutputBuffers  )  {
			if  (  m_var.helpStruct.rtPlaying  )  {
				traceLog((TCHAR*)  _T(  "playSound: EndPlaySoundData, rtPlaying is error"  )  );
				MACRO_qyAssert(  0,  _T(  "playSound: EndPlaySoundData, rtPlaying is error"  )  );
			}
		}

		
		if  (  !m_var.pPlayer->audio.bRunning  )  {
			if  (  !m_var.m_nOutputBuffers  )  {
				#ifdef  __DEBUG__
						traceLog((TCHAR*)  _T(  "OnEndPlaySoundData: bRunning is false, m_iSoundBuffers is 0, postThreadMessage to endThread"  )  );
				#endif
				PostThreadMessage(  CONST_qyWm_postComm,  CONST_qyWmParam_endThread,  0  );
			}
			goto  errLabel;
		}

		if  (  m_var.m_nOutputBuffers  <=  2  )  {	//  apply for more data.
			PostThreadMessage(  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
		}

	}

errLabel:

	if  (  lpHdr  )  {
		if(lpHdr->lpData)  free ((BYTE*) lpHdr->lpData);
		free( lpHdr  );
	}

	return;
}


 LPWAVEHDR  CQyPlaySound::CreateWaveHeader(  unsigned  int  uiBytesRecorded  )
{
	int				iErr	=	-1;
	LPWAVEHDR		lpHdr	=	NULL;
	BYTE		*	lpByte	=	NULL;

	lpHdr  =  (  WAVEHDR  *  )mymalloc(  sizeof(  WAVEHDR  )  );
	if  (  !lpHdr  )  goto  errLabel;
	ZeroMemory(lpHdr, sizeof(WAVEHDR));

	lpByte  =  (  BYTE  *  )mymalloc(  uiBytesRecorded  );
	if  (  !lpByte  )  goto  errLabel;

	lpHdr->lpData = (char *) lpByte;
	lpHdr->dwBufferLength = (  uiBytesRecorded  );
	
	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		if  (  lpByte  )  free(  lpByte  );
		if  (  lpHdr  )  free(  lpHdr  );
	}
	return  iErr  ?  NULL  :  lpHdr;

}


	

 void CQyPlaySound::displayError(int code,char mesg[])
{
	TCHAR errorbuffer[MAX_PATH];
	TCHAR errorbuffer1[MAX_PATH];

	waveOutGetErrorText( code,errorbuffer,MAX_PATH);
	_sntprintf(  errorbuffer1,  mycountof(  errorbuffer1  ),  _T(  "PLAY : %s :%x:%s\n"  ),  CQyString(  mesg  ),code,errorbuffer);
	OutputDebugString(  errorbuffer1  );  
	traceLogA(  (char*)  "CQyPlaySound::displayError: %S",  errorbuffer1  );

}



void CQyPlaySound::ProcessSoundData(BYTE *sound, DWORD dwSamples)
{
}


LRESULT CQyPlaySound::OnWriteSoundData(WPARAM wParam, LPARAM lParam)
{
	LPWAVEHDR lpHdr = (LPWAVEHDR) lParam;
	MMRESULT mmResult = 0;

	if  (  !m_var.pPlayer  )  return  FALSE;

	if  (  lpHdr  )  {
		//  char debugbuffer[256];
		//  sprintf(  debugbuffer, "SOUND BUFFER written: %d, %d\n",lpHdr->dwBufferLength,  m_var.m_nOutputBuffers  );
		//  TRACE(debugbuffer);

		if  (  m_var.pPlayer->audio.bRunning  )  {
			BYTE* lpInt = (BYTE*) lpHdr->lpData;
			DWORD dwSamples = lpHdr->dwBufferLength/sizeof(BYTE);

			ProcessSoundData(lpInt, dwSamples);

			//  if  (  m_var.m_pSemaphore  )  m_var.m_pSemaphore->Lock(  1000  );

			mmResult = ::waveOutPrepareHeader(  m_var.m_hPlay, lpHdr, sizeof(WAVEHDR));
			if  (  mmResult  )  {
				traceLogA(  (char*)  "CQyPlaySound::OnWriteSoundData: waveoutprepareheader failed. mmResult %d",  mmResult  );
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  m_var.pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playSound %I64u: OnWriteSoundData: waveOutPrepareHeader failed. mmResult %d"  ),  m_var.pPlayer->idInfo_recorder.ui64Id,  mmResult  );
				}
			else  {
				  try  {
					   mmResult = ::waveOutWrite(  m_var.m_hPlay, lpHdr, sizeof(WAVEHDR));
					   if  (  mmResult  )  {
						   traceLogA(  (char*)  "CQyPlaySound::OnWriteSoundData: waveOutWrite failed. mmResult %d",  mmResult  );
						   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  m_var.pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playSound %I64u: OnWriteSoundData: waveOutWrite failed. mmResult %d"  ),  m_var.pPlayer->idInfo_recorder.ui64Id,  mmResult  );
					   }
					   }					   
			#ifdef  __useMfc__
				  catch  (  CException  *  e  )  {
						 e->Delete(  );
						 traceLogA(  (char*)  "CQyPlaySound::OnWriteSoundData: waveOutWrite exception."  );
						 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  m_var.pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playSound %I64u: OnWriteSoundData: waveOutWrite failed. exception"  ),  m_var.pPlayer->idInfo_recorder.ui64Id  );
				  }
			#endif
				  catch  (  ...  )  {
					     traceLogA(  (char*)  "CQyPlaySound::OnWriteSoundData: waveOutWrite exception."  );
						 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  m_var.pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playSound %I64u: OnWriteSoundData: waveOutWrite failed. exception"  ),  m_var.pPlayer->idInfo_recorder.ui64Id  );
				  }
			}

			m_var.m_nOutputBuffers++;
		}
	}

	return  TRUE;
}





/**
*	End this thread...
*
*/
BOOL CQyPlaySound::bEndThread(WPARAM wParam, LPARAM lParam)
{
	if  (  m_var.pPlayer  )  {

		traceLogA(  (char*)  (  "CQyPlaySound::OnEndThread enters. %I64u"  ),  m_var.pPlayer->idInfo_recorder.ui64Id  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  m_var.pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playSound %I64u: will end"  ),  m_var.pPlayer->idInfo_recorder.ui64Id  );

		m_var.pPlayer->audio.bRunning  =  FALSE;
		if  (  !m_var.dwTickCnt_startToEndThread  )  m_var.dwTickCnt_startToEndThread   =  GetTickCount(  );

		if  (  GetTickCount(  )  -  m_var.dwTickCnt_startToEndThread  <  5000  )  {
			if  (  m_var.m_nOutputBuffers  )  {			
				return  FALSE;
			}
		}
				
		bStopPlaying(0,0);
	
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  m_var.pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playSound %I64u: end"  ),  m_var.pPlayer->idInfo_recorder.ui64Id  );

	}

	// Quit this thread...
	::PostThreadMessage(  this->m_nThreadID,  WM_QUIT,  0,  0  );

	traceLogA(  (char*)  (  "CQyPlaySound::OnEndThread leaves"  )  );
	
	return TRUE;
}


BOOL CQyPlaySound::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	BOOL					bRet		=		FALSE;

	MC_VAR_isCli	*	pProcInfo  =  NULL;	//  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	QY_PLAYER	*	pPlayer		=	NULL;
	
	DWORD					dwThreadId	=		GetCurrentThreadId(  );
	int						i;
	
	if  (  dwThreadId  ==  pProcInfo->av.localAv.player.audio.dwThreadId  )  {
		 pPlayer  =  &pProcInfo->av.localAv.player;
		 }
	 else  {
		   for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
			    if  (  dwThreadId  ==  pProcInfo->av.pPlayers[i].audio.dwThreadId  )  break;
		   }
		   if  (  i  ==  pProcInfo->av.usCnt_players  )  goto  errLabel;
		   pPlayer  =  &pProcInfo->av.pPlayers[i];
	 }

	 //
	 if  (  !pPlayer->audio.ah.wfx.nAvgBytesPerSec  )  goto  errLabel;

	 //
	 fixPlayCfg(  pProcInfo,  &pPlayer->audio.playCfg  );

	 //
	 m_var.pProcInfo  =  pProcInfo;
	 m_var.pPlayer  =  pPlayer;

	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  m_var.pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playSound: %I64u started"  ),  m_var.pPlayer->idInfo_recorder.ui64Id  );

	if  (  !bStartPlaying(  0,  0  )  )  {
		goto  errLabel;
	}

	//  m_var.bStarted  =  TRUE;

	traceLog((TCHAR*)  _T(  "playSound: %I64u started"  ),  m_var.pPlayer->idInfo_recorder.ui64Id  );

	bRet  =  TRUE;

errLabel:

	//  traceLog((TCHAR*)  _T(  "CQyPlaySound::InitInstance called"  )  );

	return  bRet;
}

int CQyPlaySound::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	if  (  m_var.pPlayer  )  {
		traceLogA(  (char*)  (  "CQyPlaySound::ExitInstance enters. %I64u"  ),  m_var.pPlayer->idInfo_recorder.ui64Id  );

		this->bStopPlaying(  0,  0  );

		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  m_var.pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playSound: %I64u exited"  ),  m_var.pPlayer->idInfo_recorder.ui64Id  );

	}

	//  m_var.bStarted  =  FALSE;
	
	traceLogA(  (char*)  (  "CQyPlaySound::ExitInstance leaves."  )  );

	//  2010/05/05
	//  if  (  m_var.pPlayer  )  SetEvent(  m_var.pPlayer->audio.hEvent_winThreadEnd  );


	return CQyThread::ExitInstance();
}

#if  0
BEGIN_MESSAGE_MAP(CQyPlaySound, CWinThread)
	//{{AFX_MSG_MAP(CQyPlaySound)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_THREAD_MESSAGE( MM_WOM_OPEN, OnMmWomOpen  )
	ON_THREAD_MESSAGE( MM_WOM_DONE, OnEndPlaySoundData)
	ON_THREAD_MESSAGE( CONST_qyWm_postComm, OnQyPostComm )

END_MESSAGE_MAP()
#endif

LRESULT CQyPlaySound::procMsg(  UINT  msg,  WPARAM wParam, LPARAM lParam)
{
	LRESULT	lRet	=	-1;
	switch  (  msg  )  {
			case  MM_WOM_OPEN:
				  OnMmWomOpen(  wParam,  lParam  );
				  return  0;
			case  MM_WOM_DONE:
				  OnEndPlaySoundData(  wParam,  lParam  );
				  return  0;
			case  CONST_qyWm_postComm:
				  OnQyPostComm(  wParam,  lParam  );
				  return  0;
			default:
					break;
	}
	return  lRet;
}

/////////////////////////////////////////////////////////////////////////////
// CQyPlaySound message handlers



 void  CQyPlaySound::OnQyPostComm( UINT wParam, LONG lParam )
{
#if  0
	long				lRet				=					-1;
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	LPWAVEHDR			lpHdr				=					NULL;
	QY_PLAYER		*	pPlayer				=					m_var.pPlayer;

	if  (  !m_var.pPlayer  )  {
		traceLogA(  (char*)  "CQyPlaySound::OnQyPostComm failed: m_var.pPlaySoundProcInfo is null."  );
		return;
	}
	//  traceLog((TCHAR*)  _T(  "CQyPlaySound::OnQyPostComm enters."  )  );

	switch  (  wParam  )  {
			case  CONST_qyWmParam_endThread:
				  this->bEndThread(  0,  0  );
				  break;
			case  CONST_qyWmParam_msgArrive:
				  int						len;
				  DWORD						dwTickCnt;

				  if  (  !m_var.pPlayer->audio.bRunning  ||  !m_var.bDevOk  )  {
					  goto  errLabel;
				  }

				  if  (  !m_var.uiBufSize  ||  !m_var.pBuf  )  {
                      //  m_var.uiBufSize  =  CONST_bufSize_transferAudioData  +  512;
					  m_var.uiBufSize  =  offsetof(  myPLAY_AUDIO_DATA,  buf  )  +  m_var.pProcInfo->cfg.uiBufSize_myPlayAudioData;	//  sizeof(  myPLAY_AUDIO_DATA  );
					  m_var.pBuf  =  (  char  *  )mymalloc(  m_var.uiBufSize  );
					  if  (  !m_var.uiBufSize  ||  !m_var.pBuf  )  goto  errLabel;
					  //
				  }

				  dwTickCnt  =  GetTickCount(  );
#if  10		
				  if  (  m_var.helpStruct.bModified_uiSampleTimeInMs_audio  )  {
					  q2TriggerToProcess(  &m_var.pPlayer->video.q2  );					
					  m_var.helpStruct.bModified_uiSampleTimeInMs_audio  =  FALSE;
				  }

				  //  2010/06/22
				  {
					  PLAY_AUDIO_procInfo	*	pPlayAudio  =  &m_var.pPlayer->audio;
					  if  (  pPlayAudio->m_var.uiSampleTimeInMs  &&  getQ2Nodes_toGetMsg(  &pPlayAudio->q2  )  >  1  )  {
						  int  nWaitingInMs_audio  =  MACRO_getnWaitingInMs_audio_internal(  pPlayer->audio,  dwTickCnt  );
						  if  (  pPlayAudio->m_var.uiSampleTimeInMs_newRecvd  <  pPlayAudio->m_var.uiSampleTimeInMs
							  ||  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  >  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  +  1000  
							  ||  (  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  &&  nWaitingInMs_audio  >  (  int  )(  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  +  pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying  )  )  
							  )
						  {
								#ifdef  __DEBUG__
									    #if  10
										  if  (  pPlayAudio->m_var.uiSampleTimeInMs_newRecvd  <  pPlayAudio->m_var.uiSampleTimeInMs  )  {
											  traceLog((TCHAR*)  _T(  "playSound: uiSampleTimeInMs_newRecvd %d, uiSampleTimeInMs %d"  ),  pPlayAudio->m_var.uiSampleTimeInMs_newRecvd,  pPlayAudio->m_var.uiSampleTimeInMs  );
										  }
										  if  (  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  >  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  +  1000  )  {
											  traceLog((TCHAR*)  _T(  "playSound: dwTickCnt_newRecvd %d, dwTickCnt %d. SampleTimeInMs %d, qNodes %d,%d"  ),  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_newRecvd,  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv,  pPlayAudio->m_var.uiSampleTimeInMs,  pPlayer->audio.q2.qs[0].uiQNodes,  pPlayer->audio.q2.qs[1].uiQNodes  );
										  }
										  if  (  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  &&  nWaitingInMs_audio  >  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  +  pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying  )  {
											  traceLog((TCHAR*)  _T(  "playSound: nWaiting_audio %d > Toplay %d. qNodes %d,%d"  ),  nWaitingInMs_audio,  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  +  pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying,  pPlayer->audio.q2.qs[0].uiQNodes,  pPlayer->audio.q2.qs[1].uiQNodes  );
										  }								  
									    #endif								
								#endif
						
								CQyQ2Help		q2Help;
								qRemoveMsg(  q2Help.getQ_toGetMsg(  &pPlayAudio->q2  ),  (  PF_bCommonHandler  )tmpHandler_bOldAudio,  (  void  *  )dwTickCnt,  pPlayer  );
						  }
					  }
				  }
#endif

				  //
#if  10
				  if  (  !pPlayer->audio.m_var.bVideoReady  
					  &&  pPlayer->audio.m_var.uiSampleTimeInMs  <=  pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd  )  
				  {
					  //  2009/05/03
					  if  (  pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_syncRecv
						  &&  pPlayer->video.m_var.dwTickCnt_uiSampleTimeInMs_syncRecv
						  &&  abs(  (  int  )(  pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd  -  pPlayer->video.m_var.uiSampleTimeInMs_newRecvd  )  )  <  10000  						  
						  )  
					  {
						  if  (  dwTickCnt  -  pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  <  10000
							  &&  dwTickCnt  -  pPlayer->video.m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  <  10000  )  //  means video is active								 
						  {					
							  int  iSampleTimeInMs_expected_video  =  GetTickCount(  )  -  pPlayer->video.m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  +  pPlayer->video.m_var.uiSampleTimeInMs_newRecvd;
							  if  (  pPlayer->audio.m_var.uiSampleTimeInMs  >  iSampleTimeInMs_expected_video  )  {
								  #ifdef  __DEBUG__								  
										  traceLogA(  (char*)  "playSound: iDiffInMs %d, delay to wait for video. ",  pPlayer->audio.m_var.uiSampleTimeInMs  -  iSampleTimeInMs_expected_video  );
								  #endif
								  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playAudio: iDiffInMs %d, delay to wait for video."  ),  pPlayer->audio.m_var.uiSampleTimeInMs  -  iSampleTimeInMs_expected_video  );
								  //
								  goto  errLabel;
							  }					  				
							  pPlayer->audio.m_var.bVideoReady  =  TRUE;							  
						  }					  
					  }					  
				  }
#endif
		  
				  //
				  for  (  ;  m_var.pPlayer->audio.bRunning;  )  {

					   if  (  m_var.m_nOutputBuffers  >  1  )  {
						   if  (  m_var.helpStruct.rtPlaying  /  10000  >=  m_var.pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying  +  m_var.pPlayer->audio.playCfg.usAudioDataAddedToPlayEveryTime  )  {
							   //  traceLog((TCHAR*)  _T(  "rtPlaying / 10000 is %d,  maxPlaying %d. can't add more data"  ),  (  int  )(  m_var.helpStruct.rtPlaying  /  10000  ),  m_var.pPlayer->audio.playCfg.uiMinTimeInMsOfAudioDataPlaying  +  m_var.pPlayer->audio.playCfg.uiAudioDataAddedToPlayEveryTime  );
							   break;
						   }
					   }
					   
					   if  (  m_var.helpStruct.mems[m_var.helpStruct.iIndex_toFill].lpHdr  )  {
						   traceLog((TCHAR*)  _T(  "PlaySound err: toFill mems[%d].lpHdr is not null, total %d"  ),  m_var.helpStruct.iIndex_toFill,  m_var.m_nOutputBuffers  );
						   PostThreadMessage(  CONST_qyWm_postComm,  CONST_qyWmParam_endThread,  0  );
						   goto  errLabel;
					   }

					   len  =  m_var.uiBufSize;
					   if  (  q2GetMsg(  &m_var.pPlayer->audio.q2,  m_var.pBuf,  (  unsigned  int  *  )&len  )  )  break;

					   myPLAY_AUDIO_DATA	*	pPkt	=	(  myPLAY_AUDIO_DATA  *  )m_var.pBuf;

					   #ifdef  __DEBUG__
							   //  traceLog((TCHAR*)  _T(  "CQyPlaySound: len%d, dataLen %d"  ),  len,  pPkt->head.uiLen  );
					   #endif

					   if  (  !pPkt->memory.m_pBuf  )  {
						   goto  errLabel;
					   }

					   lpHdr  =  this->CreateWaveHeader(  pPkt->head.uiLen  );
					   if  (  lpHdr  )  {
						   DWORD	dwTickCnt	=	GetTickCount(  );

						   //
						   memcpy(  lpHdr->lpData,  pPkt->memory.m_pBuf,  pPkt->head.uiLen  );
						   lpHdr->dwBufferLength  =  pPkt->head.uiLen;
						   //
						   m_var.helpStruct.mems[m_var.helpStruct.iIndex_toFill].lpHdr  =  lpHdr;
						   m_var.helpStruct.mems[m_var.helpStruct.iIndex_toFill].iSampleTimeInMs  =  pPkt->head.uiSampleTimeInMs;
						   m_var.helpStruct.mems[m_var.helpStruct.iIndex_toFill].ui_rtTimeLen  =  pPkt->head.ui_rtTimeLen  ?  pPkt->head.ui_rtTimeLen  :  (  unsigned  int  )(  pPkt->head.uiLen  *  10000000.  /  m_var.pPlayer->audio.ah.wfx.nAvgBytesPerSec  );
						   m_var.helpStruct.mems[m_var.helpStruct.iIndex_toFill].dwTickCnt  =  dwTickCnt;
						   //
						   m_var.helpStruct.rtPlaying  +=  m_var.helpStruct.mems[m_var.helpStruct.iIndex_toFill].ui_rtTimeLen;
						   //
						   lpHdr->dwUser  =  m_var.helpStruct.iIndex_toFill;
						   //
						   //
						   m_var.helpStruct.iIndex_toFill  ++  ;
						   m_var.helpStruct.iIndex_toFill  =  m_var.helpStruct.iIndex_toFill  %  (  mycountof(  m_var.helpStruct.mems  )  );
					   }
					   clean_myPLAY_AUDIO_DATA(  pPkt,  _T(  "playSound"  )  );

					   if  (  !lpHdr  )  {
						   traceLogA(  (char*)  "CQyPlaySound: CreateWaveHeader failed."  );
						   goto  errLabel;
					   }

					   this->OnWriteSoundData(  0,  (  LPARAM  )lpHdr  );					   
					   //
					   lpHdr  =  NULL;

				  }
				  
#if  10
				  if  (  m_var.helpStruct.rtPlaying  )  pPlayer->audio.m_var.nTimes_noAudioData  =  0;
				  else  pPlayer->audio.m_var.nTimes_noAudioData  ++  ;
				  //
				  if  (  pPlayer->audio.m_var.nTimes_noAudioData  >  2  )  {
					  pPlayer->audio.m_var.bVideoReady  =  FALSE;
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playAudio: no audio data, bVideoReady is false"  )  );
				  }
#endif

				  break;
			default:
					goto  errLabel;
	}
	

	lRet	=	CONST_qyWmRc_ok;

errLabel:

	if  (  lpHdr  )  {
		free(  lpHdr->lpData  );
		free(  lpHdr  );
	}

	return;	//  lRet;
#endif

}



