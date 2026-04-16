// QyRecordSound.cpp : implementation file
//

#include	"stdafx.h"
#include	<mmsystem.h>
#include	<mmreg.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"QyRecordSound_wave.h"
#include	"qmcAcm.h"
#include	"qmcVideoCapture_isCli.h"
#include	"module_qisCamCap.h"

#include	"qmcCommFunc_isCli.h"

//
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif








/////////////////////////////////////////////////////////////////////////////
// CQyRecordSound

CQyRecordSound::CQyRecordSound(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CQyRecordSound::~CQyRecordSound()
{

	OutputDebugString(  _T(  "CQyRecordSound::~CQyRecordSound(  )\n"  )  );

}




void CALLBACK OnCallbackBlock(HWAVEIN hwl,UINT uMsg,
				DWORD dwInstance,
				DWORD dwParam1, DWORD dwParam2)
{
	CQyRecordSound*pCallback = (CQyRecordSound*)dwInstance;
	if  (  pCallback  )  {
		LPWAVEHDR	lpWaveHdr  =  (  LPWAVEHDR  )dwParam1;
		pCallback->OnSoundData(  hwl,  uMsg,  lpWaveHdr  );
	}
}

void CQyRecordSound::displayError(int mmReturn,char errmsg[])
{
	TCHAR errorbuffer[MAX_PATH];
	TCHAR errorbuffer1[MAX_PATH];

	waveInGetErrorText(  mmReturn,  errorbuffer,  mycountof(  errorbuffer  )  );
	_sntprintf(  errorbuffer1,  mycountof(  errorbuffer1  ),  _T(  "RECORD: %s : %x : %s\n"  ), CQyString(  errmsg  ),  mmReturn,  errorbuffer);
	//  myMessageBox(errorbuffer1);  
	OutputDebugString(  errorbuffer1  );
}


  LPWAVEHDR  CQyRecordSound::CreateWaveHeader(  unsigned  int  uiBytesRecorded  )
{
	int				iErr	=	-1;
	LPWAVEHDR		lpHdr	=	NULL;
	BYTE		*	lpByte  =	NULL;
	//  int				len		=	m_var.pProcInfo->av.localAv.recordSoundProcInfo.compressAudio.compressor.uiBytesRecorded_perBlockAlign  *  m_var.pProcInfo->av.localAv.recordSoundProcInfo.compressAudio.ah_decompress.wfx.nBlockAlign;
	int				len		=	uiBytesRecorded;
    
	lpHdr  =  (  LPWAVEHDR  )mymalloc(  sizeof(  WAVEHDR  )  );	
	if  (  !lpHdr  )  goto  errLabel;
	ZeroMemory(  lpHdr, sizeof(  WAVEHDR  )  );

	lpByte  =  (  BYTE  *  )mymalloc(  len  );
	if  (  !lpByte  )  goto  errLabel;
	
	lpHdr->lpData  =  (  char  *  )lpByte;
	lpHdr->dwBufferLength  =  len;

	iErr  =  0;

errLabel:
	
	if  (  iErr  )  {
		if  (  lpByte  )  free(  lpByte  );
		if  (  lpHdr  )  free(  lpHdr  );		
		traceLogA(  (char*)  "CQyRecordSound CreateWaveHeader failed."  );
	}

	return   iErr  ?  NULL  :  lpHdr;

}


 void  CQyRecordSound::AllocateBuffers(  int  nBuffers,  unsigned  int  uiBytesRecorded  )
{
	MMRESULT	mmr;
    int  i;

	for  (  i  =  0;  i  <  nBuffers;  i  ++  )  {
 		 LPWAVEHDR lpWaveHdr = CreateWaveHeader(  uiBytesRecorded  );
		 if  (  !lpWaveHdr  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)"",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "recordSound: Create Wave Header failed"  )  );
			 goto  errLabel;
		 }
		 mmr  =  ::waveInPrepareHeader(  m_var.m_hRecord,  lpWaveHdr,  sizeof(  WAVEHDR  )  );
		 mmr  =  ::waveInAddBuffer(  m_var.m_hRecord,  lpWaveHdr,  sizeof(  WAVEHDR  )  );			
		 m_var.cb.m_iSoundBuffers  ++  ;
	}

errLabel:
	return;
}

#if  0
 // 0 is mute, 1 is unmute
 int  set_mute(  HMIXEROBJ  hMixer,  MIXERLINE  *  pMixerLine,  DWORD  val,  BOOL  errMsg  )
{
	int								iErr				=	-1;
	MIXERCONTROL					mixerControlArray;
	MIXERLINECONTROLS				mixerLineControls;
	MIXERCONTROLDETAILS_UNSIGNED	values[2];
	MIXERCONTROLDETAILS				mixerControlDetails;
	DWORD							mmr;

	memset(  &mixerLineControls,  0,  sizeof(  mixerLineControls  )  );
	mixerLineControls.cbStruct  =  sizeof(  mixerLineControls  );
	mixerLineControls.dwLineID  =  pMixerLine->dwLineID;
	mixerLineControls.cControls  =  1;
	mixerLineControls.dwControlType  =  MIXERCONTROL_CONTROLTYPE_MUTE;
	mixerLineControls.pamxctrl  =  &mixerControlArray;
	mixerLineControls.cbmxctrl  =  sizeof(  mixerControlArray  );
	mmr  =  mixerGetLineControls(  hMixer,  &mixerLineControls,  MIXER_GETLINECONTROLSF_ONEBYTYPE  );
	if  (  mmr  )  {
		traceLog((TCHAR*)  _T(  "No mute control"  )  );
		}
	else  {
		  memset(  &mixerControlDetails,  0,  sizeof(  mixerControlDetails  )  );
		  mixerControlDetails.cbStruct  =  sizeof(  mixerControlDetails  );
		  mixerControlDetails.dwControlID  =  mixerControlArray.dwControlID;
		  mixerControlDetails.cChannels  =  pMixerLine->cChannels;
		  if  (  mixerControlDetails.cChannels  >  2  )  mixerControlDetails.cChannels  =  2;
		  if  (  mixerControlArray.fdwControl  &  MIXERCONTROL_CONTROLF_UNIFORM  ) {
			  mixerControlDetails.cChannels  =  1;
		  }
		  mixerControlDetails.cMultipleItems  =  0;
		  mixerControlDetails.paDetails  =  &values[0];
		  mixerControlDetails.cbDetails  =  sizeof(  values[0]  );

		  values[0].dwValue  =  values[1].dwValue  =  val;

		  mmr  =  mixerSetControlDetails(  hMixer,  &mixerControlDetails,  MIXER_SETCONTROLDETAILSF_VALUE  );
		  if  (  mmr  )  {
			  traceLog((TCHAR*)  _T(  "mixerSetControlDetails failed"  )  );
			  goto  errLabel;
		  }
		  showNotification(  0,  0,  0,  0,  0,  _T(  "Unmute ok"  )  );
	}

	iErr  =  0;
errLabel:
	return  iErr;

 }


 int  chkWaveInDev(  HWAVEIN	m_hRecord  )
 {
	int				iErr		=	-1;
	HMIXER			hMixer		=	NULL;
	MIXERLINE		mixerLine;
	unsigned  int	n,  numSrc;
	DWORD			mmReturn;

	mmReturn  =  mixerOpen(  &hMixer,  (  DWORD  )m_hRecord,  0,  0,  MIXER_OBJECTF_HWAVEIN  );
	if  (  mmReturn  )  {
		traceLog((TCHAR*)  _T(  "device doesn't have mixer support"  )  );
		goto  errLabel;
		}
	else  {
		  memset(  &mixerLine,  0,  sizeof(  mixerLine  )  );
		  mixerLine.cbStruct  =  sizeof(  mixerLine  );
		  mixerLine.dwComponentType  =  MIXERLINE_COMPONENTTYPE_DST_WAVEIN;
		  mmReturn  =  mixerGetLineInfo(  (  HMIXEROBJ  )hMixer,  &mixerLine,  MIXER_GETLINEINFOF_COMPONENTTYPE  );
		  if  (  mmReturn  )  {
			  traceLog((TCHAR*)  _T(  "device does not have a wave recording control"  )  );
			  goto  errLabel;
		  }
		  numSrc  =  mixerLine.cConnections;
		  mixerLine.dwSource  =  mixerLine.dwDestination;
		  set_mute(  (  HMIXEROBJ  )hMixer,  &mixerLine,  1,  0  );
		  
		  if  (  !numSrc  )  goto  errLabel;		  
		  //
	}

	iErr  =  0;

errLabel:

	if  (  hMixer  )  mixerClose(  hMixer  );

	return  iErr;
 }
#endif

#if  10

BOOL CQyRecordSound::bStartRecording(WPARAM wp,LPARAM lp)
{
	BOOL							bRet		=	FALSE;
	DWORD							mmReturn	=	0;
	MC_VAR_isCli					*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	CAP_procInfo_recordSound	*	pRecord		=	&pProcInfo->av.localAv.recordSoundProcInfo;
	WAVEFORMATEX				*	pWfx		=	NULL;
	
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)"",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "recordSound: will start"  )  );

	if  (  pRecord->thread.bRunning  )  return  FALSE;

#ifndef  __WINCE__
	m_var.cb.pWfx  =  &pRecord->compressAudio.ah_decompress.wfx;
	pWfx  =  (  WAVEFORMATEX  *  )m_var.cb.pWfx;
	m_var.cb.uiBytesRecorded  =  pRecord->compressAudio.compressor.uiBytesRecorded_perBlockAlign  *  pWfx->nBlockAlign;
#else
	m_var.cb.pWfx  =  &pRecord->compressAudio.ah_compress.wfx;
	pWfx  =  (  WAVEFORMATEX  *  )m_var.cb.pWfx;
	m_var.cb.uiBytesRecorded  =  pRecord->compressAudio.compressor.uiBytesRecorded_perBlockAlign  *  pRecord->compressAudio.ah_decompress.wfx.nBlockAlign;
	m_var.cb.uiBytesRecorded  =  (  int  )(  1.0  *  m_var.cb.uiBytesRecorded  *  pWfx->nAvgBytesPerSec  /  pRecord->compressAudio.ah_decompress.wfx.nAvgBytesPerSec  );
	if  (  (  m_var.cb.uiBytesRecorded  %  pWfx->nBlockAlign  )  )  {
		m_var.cb.uiBytesRecorded  =  (  m_var.cb.uiBytesRecorded  /  pWfx->nBlockAlign  +  1  )  *  pWfx->nBlockAlign;
		if  (  m_var.cb.uiBytesRecorded  >  pWfx->nAvgBytesPerSec  )  m_var.cb.uiBytesRecorded  -=  pWfx->nBlockAlign;
	}
#endif
	
	m_var.cb.uiBufSize_pPkt  =  sizeof(  myPLAY_AUDIO_DATA  )  +  pProcInfo->cfg.uiBufSize_myPlayAudioData;  
	m_var.cb.uiBufSize_pMsgBuf  =  sizeof(  MIS_MSGU  );

	if  (  pRecord->uiRecordType  !=  CONST_recordType_waveform  )  {
		traceLog((TCHAR*)  _T(  "recordSound::bStartRecording failed, uiRecordType error"  )  );
		goto  errLabel;
	}

	if  (  !(  m_var.cb.pPkt  =  (  BYTE  *  )mymalloc(  m_var.cb.uiBufSize_pPkt  )  )  )  goto  errLabel;
	if  (  !(  m_var.cb.pMsgBuf  =  mymalloc(  m_var.cb.uiBufSize_pMsgBuf  )  )  )  goto  errLabel;

	//  
	mmReturn = ::waveInOpen( &m_var.m_hRecord, WAVE_MAPPER,  pWfx, (DWORD) &OnCallbackBlock, (DWORD)this, CALLBACK_FUNCTION);
	if  (  mmReturn  !=  MMSYSERR_NOERROR  )  {
		displayError(  mmReturn, (char*)"Open"  );  
		showNotification(  0,  0,  0,  0,  0,  0,  _T(  "Can't open audio device"  )  );
		goto  errLabel;
	}		
	
	//
	//  chkWaveInDev(  m_var.m_hRecord  );

	//  
	AllocateBuffers(  MAX_inputBuffers,  m_var.cb.uiBytesRecorded  );
	
	mmReturn = ::waveInStart(m_var.m_hRecord);			
	if  (  mmReturn  !=  MMSYSERR_NOERROR  )  {
		displayError(mmReturn,(char*)"Start");
		goto  errLabel;
	}

	//pRecord->thread.bQuit  =  FALSE;
	pRecord->thread.bRunning  =  TRUE;	 
	pRecord->usErrors_processInput  =  0;

	bRet  =  TRUE;

errLabel:

	if  (  !bRet  )  {
	}

	return  bRet;
}

#else

BOOL CQyRecordSound::bStartRecording(WPARAM wp,LPARAM lp)
{
	BOOL							bRet		=	FALSE;
	QY_MC						*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli					*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	CAP_procInfo_recordSound	*	pRecord		=	&pProcInfo->av.localAv.recordSoundProcInfo;

	DWORD		mmReturn = 0;
	
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "recordSound: will start"  )  );

	if  (  pRecord->thread.bRunning  )  return  FALSE;

#ifndef  __WINCE__
		 m_var.cb.pWfx  =  &pRecord->compressAudio.ah_decompress.wfx;
		 m_var.cb.uiBytesRecorded  =  pRecord->compressAudio.compressor.uiBytesRecorded_perBlockAlign  *  m_var.cb.pWfx->nBlockAlign;
#else
	m_var.pWfx  =  &m_var.pRecord->compressAudio.ah_compress.wfx;
	m_var.uiBytesRecorded  =  m_var.pRecord->compressAudio.compressor.uiBytesRecorded_perBlockAlign  *  m_var.pRecord->compressAudio.ah_decompress.wfx.nBlockAlign;
	m_var.uiBytesRecorded  =  (  int  )(  1.0  *  m_var.uiBytesRecorded  *  m_var.pWfx->nAvgBytesPerSec  /  m_var.pRecord->compressAudio.ah_decompress.wfx.nAvgBytesPerSec  );
	if  (  (  m_var.uiBytesRecorded  %  m_var.pWfx->nBlockAlign  )  )  {
		m_var.uiBytesRecorded  =  (  m_var.uiBytesRecorded  /  m_var.pWfx->nBlockAlign  +  1  )  *  m_var.pWfx->nBlockAlign;
		if  (  m_var.uiBytesRecorded  >  m_var.pWfx->nAvgBytesPerSec  )  m_var.uiBytesRecorded  -=  m_var.pWfx->nBlockAlign;
	}
#endif

	m_var.cb.uiBufSize_pPkt  =  offsetof(  myPLAY_AUDIO_DATA,  buf  )  +  pProcInfo->cfg.uiBufSize_myPlayAudioData;  
	m_var.cb.uiBufSize_pMsgBuf  =  sizeof(  MIS_MSGU  );

	switch  (  pRecord->uiRecordType  )  {
			case  CONST_recordType_waveform:  {
				  if  (  !(  m_var.cb.pPkt  =  (  BYTE  *  )mymalloc(  m_var.cb.uiBufSize_pPkt  )  )  )  goto  errLabel;

				  m_var.cb.pMsgBuf  =  (  MIS_MSGU  *  )mymalloc(  m_var.cb.uiBufSize_pMsgBuf  );
				  if  (  !m_var.cb.pMsgBuf  )  goto  errLabel;

				  //  
				  mmReturn = ::waveInOpen( &m_var.m_hRecord, WAVE_MAPPER,  m_var.cb.pWfx, (DWORD)m_var.cb.hWnd_record, (DWORD)this, CALLBACK_WINDOW);
				  if  (  mmReturn  !=  MMSYSERR_NOERROR  )  {
					  displayError(  mmReturn, "Open"  );  
					  showNotification(  0,  0,  0,  0,  0,  _T(  "Can't open audio device"  )  );
					  goto  errLabel;
				  }		

				  //  
				  AllocateBuffers(  MAX_inputBuffers,  m_var.cb.uiBytesRecorded  );
	
				  mmReturn = ::waveInStart(m_var.m_hRecord);			
				  if  (  mmReturn  !=  MMSYSERR_NOERROR  )  {
					  displayError(mmReturn,"Start");
					  goto  errLabel;
				  }
				  }
				  break;
			case  CONST_recordType_custom:  {
				  MODULE_camCap	*	pModule	=	(  MODULE_camCap  *  )getCusModule(  pQyMc,  CONST_moduleType_camCap  );
				  if  (  !pModule  )  goto  errLabel;
				  if  (  !pModule->pf_initRecordSound
					  ||  !pModule->pf_exitRecordSound
					  ||  !pModule->pf_startRecord
					  ||  !pModule->pf_stopRecord  
					  ||  !pModule->pf_OnMM_WIM_OPEN
					  ||  !pModule->pf_OnMM_WIM_DATA
					  ||  !pModule->pf_OnMM_WIM_CLOSE  )
				  {
					  goto  errLabel;
				  }
				  this->m_var.pModule  =  pModule;

				  //  pModule->pf_initRecordSound(  &m_var,  
				  //  startRecording
				  }
				  break;
			default:
					traceLog((TCHAR*)  _T(  "startRecording failed: unknown uiRecordType"  )  );
					goto  errLabel;
	}

	pRecord->thread.bQuit  =  FALSE;
	pRecord->thread.bRunning  =  TRUE;	 
	pRecord->usErrors_processInput  =  0;

	bRet  =  TRUE;

errLabel:

	if  (  !bRet  )  {
	}

	return  bRet;
}

#endif	




BOOL CQyRecordSound::bStopRecording(WPARAM wp,LPARAM lp)
{
	MMRESULT						mmReturn	=	0;
	MC_VAR_isCli					*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	CAP_procInfo_recordSound	*	pRecord		=  &pProcInfo->av.localAv.recordSoundProcInfo;

	qyShowInfo1(  CONST_qyShowType_qwmComm,  0, (char*) "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "recordSound: will stop"  )  );

	pRecord->thread.bRunning = FALSE;

	switch  (  pRecord->uiRecordType  )  {
			case  CONST_recordType_waveform:

				  if  (  !m_var.m_hRecord  )  break;

				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "recorder: bStopRecording, before waveInStop"  )  );
				  #endif
				  mmReturn = ::waveInStop(m_var.m_hRecord);
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "recorder: bStopRecording, waveInStop returns %d"  ),  mmReturn  );
				  #endif
				  if  (  !mmReturn  )  {
					  mmReturn = ::waveInReset(m_var.m_hRecord);  
					  #ifdef  __DEBUG__
							  traceLog((TCHAR*)  _T(  "recorder: bStopRecording, waveInStop returns %d"  ),  mmReturn  );
					  #endif	
				  }		
	
				  Sleep(  500  ); 
	
				  if  (  !mmReturn  )  {
					  #ifdef  __DEBUG__
							  //  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  m_var.pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "recordSound: will close"  )  );
					  #endif	
		
					  mmReturn = ::waveInClose(m_var.m_hRecord);
					  if  (  !mmReturn  )  m_var.m_hRecord  =  NULL;

					  #ifdef  __DEBUG__
							  traceLog((TCHAR*)  _T(  "recorder: bStopRecording, waveInClose returns %d"  ),  mmReturn  );
					  #endif	


				  }
				  break;
			default:
				break;

	}


	MACRO_safeFree(  m_var.cb.pPkt  );
	MACRO_safeFree(  m_var.cb.pMsgBuf  );

	return  mmReturn;
}


void CQyRecordSound::ProcessSoundData(BYTE* sound, DWORD dwSamples)
{
}


 int  BufferCB_recordSound(  RECORD_soundCb_var  *  pCbVar,  char  *  pbInput1,  DWORD  dwNumBytes  )
{
	int								iErr				=	-1;
	if  (  !pCbVar  )  return  -1;
	RECORD_soundCb_var			&	m_var				=	*pCbVar;
	MC_VAR_isCli					*	pProcInfo			=	(  MC_VAR_isCli  *  )m_var.pProcInfo;
	if  (  !pProcInfo  )  return  -1;
	myPLAY_AUDIO_DATA			*	pPkt				=	(  myPLAY_AUDIO_DATA  *  )m_var.pPkt;
	if  (  !pPkt  )  return  -1;
	CAP_procInfo_recordSound	*	pRecord				=	&pProcInfo->av.localAv.recordSoundProcInfo;

#if  0
	
	if  (  pbInput1  !=  NULL  &&  dwNumBytes  &&  pRecord->thread.bRunning  )  {
			
			BOOL			bHaveMsgrs_sendLocalAv	=	TRUE;
			unsigned  int	uiSampleTimeInMs		=	mytimeGetTime(  );

			toShareAudio(  pProcInfo,  (  CAP_procInfo_audioU  *  )&pProcInfo->av.localAv.recordSoundProcInfo,  uiSampleTimeInMs,  (  BYTE  *  )pbInput1,  dwNumBytes,  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio,  getSharedObjByIndex(  pProcInfo,  pProcInfo->av.localAv.recordSoundProcInfo.iIndex_sharedObj  ),  &bHaveMsgrs_sendLocalAv,  (  MIS_MSGU  *  )m_var.pMsgBuf  );

			if  (  pProcInfo->av.localAv.recordSoundProcInfo.bLocalAudioPlaying  )  { 
				//
				#ifdef  __DEBUG__
						#if  1
							TCHAR	tBuf[128];
							_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d bytes audio data\n"  ),  dwNumBytes  ); 
							OutputDebugString(  tBuf  );
						#endif
			    #endif
			
				if  (  pProcInfo->av.localAv.player.audio.bRunning  )  {	//  if thread is active
					CQyMalloc	mallocObj;

					memset(  pPkt,  0,  sizeof(  myPLAY_AUDIO_DATA  )  );
					//  pkt.idInfo.ui64Id  =  0;
					pPkt->head.uiSampleTimeInMs  =  uiSampleTimeInMs;
					if  (  dwNumBytes  >  pProcInfo->cfg.uiBufSize_myPlayAudioData  )  goto  errLabel;
					pPkt->head.uiLen  =  dwNumBytes;
					//
					if  (  !mallocObj.mallocf(  pPkt->head.uiLen  )  )  goto  errLabel;
					if  (  mallocObj.get(  &pPkt->memory  )  )  goto  errLabel;
					memcpy(  pPkt->memory.m_pBuf,  pbInput1,  pPkt->head.uiLen  );

					//  2010/06/21
					pProcInfo->av.localAv.player.audio.m_var.uiSampleTimeInMs_newRecvd  =  pPkt->head.uiSampleTimeInMs;
					pProcInfo->av.localAv.player.audio.m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  =  GetTickCount(  );

					//
					if  (  q2PostMsgAndTrigger(  pPkt,  offsetof(  myPLAY_AUDIO_DATA,  buf  ),  &pProcInfo->av.localAv.player.audio.q2  )  )  {
						goto  errLabel;
					}
					mallocObj.detach(    );

					QY_MC	*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;
					if  (  !pQyMc->bUseDirectSound_toPlay  )  {
						::PostThreadMessage(  pProcInfo->av.localAv.player.audio.dwThreadId,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
					}

					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%d bytes audio data."  ),  dwNumBytes  );					
					#ifdef  __DEBUG__
							//  traceLog((TCHAR*)  _T(  "%d bytes sent"  ),  dwNumBytes  );
					#endif

				}
			}

			if  (  bHaveMsgrs_sendLocalAv  ||  pProcInfo->av.localAv.recordSoundProcInfo.bLocalAudioPlaying  )  pRecord->dwTickCnt_sendLocalAv  =  GetTickCount(  );
			else  {

				  if  (  GetTickCount(  )  -  pRecord->dwTickCnt_sendLocalAv  <  4000  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: no messenger need to be sent."  )  );
				  else  {
					    qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: no messenger need to be sent, audio shall be stopped."  )  );
						goto  errLabel;					
				  }
			 }
			
		
	}
#endif


	iErr  =  0;

errLabel:
	return  iErr;
}


void CQyRecordSound::OnSoundData(  HWAVEIN  hwl,  UINT  uMsg,  LPWAVEHDR  lpWaveHdr  )
{

	int						iRet						=	-1;
	int						i							=	0;
	BYTE				*	lpInt						=	NULL;
			
	//  OutputDebugString(  _T(  "CQyRecordSound::onSoundData enters.\n"  )  );
			
	if  (  lpWaveHdr  &&  uMsg  ==  WIM_DATA  )  {
		
		//
		lpInt														=	(  BYTE  *  )lpWaveHdr->lpData;
		DWORD							iRecorded					=	lpWaveHdr->dwBytesRecorded;
		
		char						*	pInput						=	lpWaveHdr->lpData;
		DWORD							dwBytes_input				=	lpWaveHdr->dwBytesRecorded;		

		char						*	pbInput1					=	pInput;
		DWORD							dwNumBytes					=	dwBytes_input;
		MC_VAR_isCli					*	pProcInfo					=	(  MC_VAR_isCli  *  )m_var.cb.pProcInfo;
		myPLAY_AUDIO_DATA			*	pPkt						=	(  myPLAY_AUDIO_DATA  *  )m_var.cb.pPkt;
		CAP_procInfo_recordSound	*	pRecord						=	&pProcInfo->av.localAv.recordSoundProcInfo;


#ifdef  __DEBUG__
		#if  0
			if  (  !m_var.pRecord->bRecording  )  {
				traceLog((TCHAR*)  _T(  "OnSoundData: bRecording is false, m_iSoundBuffers %d"  ),  m_var.m_iSoundBuffers  );
			}
		#endif
#endif

		//  if  (  m_var.pRecord->bRecording  )  
		{
			::waveInUnprepareHeader(  m_var.m_hRecord,  lpWaveHdr,  sizeof(WAVEHDR)  );
		}
	
		m_var.cb.m_iSoundBuffers  --  ;
		if  (  !pRecord->thread.bRunning  )  {
			if  (  !m_var.cb.m_iSoundBuffers  )  {
				#ifdef  __DEBUG__
						traceLog((TCHAR*)  _T(  "OnSoundData: bRecording is false, m_iSoundBuffers is 0, postThreadMessage to endThread"  )  );
				#endif
				PostThreadMessage(  CONST_qyWm_postComm,  CONST_qyWmParam_endThread,  0  );
			}
			goto  errLabel;
		}

		ProcessSoundData(lpInt, iRecorded/sizeof(BYTE));

		if  (  pRecord->thread.bRunning  )  {
			AllocateBuffers(  1,  m_var.cb.uiBytesRecorded  );
		}

		BufferCB_recordSound(  &m_var.cb,  pbInput1,  dwNumBytes  );


	}

	iRet  =  0;

errLabel:			//  上面有内存需要释放，所以，不能有goto  errLabel, 以防止不释放了

	if  (  lpInt  )  free(  lpInt  );
	if  (  lpWaveHdr  )  free(  lpWaveHdr  );
	
	return;

}



 BOOL CQyRecordSound::bEndThread(WPARAM wp,LPARAM lp)
{
	MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )m_var.cb.pProcInfo;
	if  (  !pProcInfo  )  return  FALSE;
	CAP_procInfo_recordSound	*	pRecord	=	(  CAP_procInfo_recordSound  *  )&pProcInfo->av.localAv.recordSoundProcInfo;

	traceLogA(  (char*)  (  "CQyRecordSound::OnEndThread enters"  )  );
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0, (char*) "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "recordSound: will end"  )  );
	
	pRecord->thread.bRunning  =  FALSE;
	if  (  !m_var.cb.dwTickCnt_startToEndThread  )  m_var.cb.dwTickCnt_startToEndThread  =  GetTickCount(  );

	if  (  GetTickCount(  )  -  m_var.cb.dwTickCnt_startToEndThread  <  5000  )  {
		if  (  m_var.cb.m_iSoundBuffers  )  {		
			return  FALSE;	
		}
	}

	bStopRecording(0,0);

	#ifdef  __DEBUG__
			traceLog((TCHAR*)  _T(  "recorder: bEndThread: postThreadMessage WM_QUIT"  )  );
	#endif
	//  
	::PostThreadMessage(  this->m_nThreadID,  WM_QUIT,  0,  0  );
	
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)"",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "recordSound: end"  )  );
	traceLogA(  (char*)  (  "CQyRecordSound::OnEndThread leaves"  )  );

	return  TRUE;
}







BOOL CQyRecordSound::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	OutputDebugString(  _T(  "CQyRecordSound::InitInstancs.\n"  )  );

	BOOL					bRet		=		FALSE;
	QY_MC* pQyMc = nullptr;// QY_GET_GBUF();
	if (!pQyMc) return  false;// goto  errLabel;
	MC_VAR_isCli			*	pProcInfo	=		QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;

	m_var.cb.pProcInfo  =  pProcInfo;
	//  m_var.pRecord  =  &pProcInfo->av.localAv.recordSoundProcInfo;
	m_var.cb.iIndex_capProcInfo  =  0;


	//
	if  (  !this->bStartRecording(  0,  0  )  )  goto  errLabel;
	m_var.cb.bStarted  =  TRUE; 

	qyShowInfo1(  CONST_qyShowType_qwmComm,  0, (char*) "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "recordSound: started"  )  );

	bRet  =  TRUE;

errLabel:
	return  bRet;
}

int CQyRecordSound::ExitInstance()
{
	QY_MC* pQyMc = nullptr;// QY_GET_GBUF();
	if (!pQyMc) return  -1;
	MC_VAR_isCli					*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	CAP_procInfo_recordSound	*	pRecord		=	&pProcInfo->av.localAv.recordSoundProcInfo;

	// TODO:  perform any per-thread cleanup here
	traceLogA(  (char*)  (  "CQyRecordSound::ExitInstancs enters"  )  );

	this->bStopRecording(  0,  0  );
	m_var.cb.bStarted  =  FALSE;


	//
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0, (char*) "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "recordSound: exited"  )  );
	traceLogA(  (char*)  (  "CQyRecordSound::ExitInstancs leaves."  )  );

	//  2010/05/05
	//  SetEvent(  pRecord->thread.hEvent_winThreadEnd  );

	return CQyThread::ExitInstance();
}


LRESULT CQyRecordSound::procMsg(  UINT  msg,  WPARAM wParam, LPARAM lParam)
{
	LRESULT	lRet	=	-1;
	switch  (  msg  )  {
			case  CONST_qyWm_postComm:
				  this->OnQyPostComm(  wParam,  lParam  );
				  return  0;
			default:
					break;
	}

	return  lRet;
}


/////////////////////////////////////////////////////////////////////////////
// CQyRecordSound message handlers


 void  CQyRecordSound::OnQyPostComm( UINT wParam, LONG lParam )
{
	long				lRet				=					-1;
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;

	
	switch  (  wParam  )  {
			case  CONST_qyWmParam_endThread:
				  this->bEndThread(  0,  0  );
				  break;
			default:
					goto  errLabel;
	}
	

	lRet	=	CONST_qyWmRc_ok;

errLabel:

	return;	//  lRet;

}

