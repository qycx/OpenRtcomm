

#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
#include	<Dshow.h>

#include	"qdcOpenCommon.h"
#include	"qySyncObj.h"
#include	"genericqueue.h"


//#include	"





////////////////////
 extern "C" int doThreadProc_playAudio_webRtc( void  *  lpParameter )
{
#if  0
	 MC_VAR_isCli					*	pProcInfo					=	(  MC_VAR_isCli  *  )lpParameter;
	 if (  !pProcInfo  )  return  -1;
	 QY_MC						*	pQyMc						=	pProcInfo->pQyMc;
	 if  (  !pQyMc  )  return  -1;

	 //
	 DYN_LIB_DX					*	pDynLib						=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;

	 QY_PLAYER					*	pPlayer						=	NULL;
	 PLAY_AUDIO_procInfo		*	pPlayAudio					=	NULL;

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

	 memset(  &myPs,  0,  sizeof(  myPs  )  );

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

	 traceLogA(  "playSound %S enters",  pPlayAudio->q2.cfg.name  );

	 //
	 nAvgBytesPerSec  =  pPlayer->audio.ah.wfx.nAvgBytesPerSec;
	 if  (  !nAvgBytesPerSec  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  "mcThreadProc_playAudio failed: nAvgBytesPerSec is 0"  );
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
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u iNotifyInterval too big %d"  ),  pPlayAudio->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id,  iNotifyInterval  );
		 goto  errLabel;
	 }

	 //
	 pPlayAudio->bQuit  =  FALSE;
	 pPlayAudio->dwTickCnt_start  =  M_GetTickCount_audio(  tickObj  );		//  2010/05/04
	 pPlayAudio->bRunning  =  TRUE;
	 pPlayer->uiSampleTimeInMs_start  =  0;
	 memset(  &pPlayAudio->m_var,  0,  sizeof(  pPlayAudio->m_var  )  );

	 //
	 if  (  bLocalAudio  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, Local audio, starts"  ),  pPlayAudio->q2.cfg.name  );
	 else  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u starts"  ),  pPlayAudio->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id  );

	 //  getMsg from q

	 uiBufSize  =  max(  (  CONST_bufSize_transferAudioData  +  256  )  *  2,  pPlayAudio->ah.wfx.nAvgBytesPerSec  *  2  );
	 pBuf  =  (  char  *  )mallocObj_pBuf.mallocf(  uiBufSize  );
	 if  (  !uiBufSize  ||  !pBuf  )  goto  errLabel;

	 //
	 pLeft  =  pBuf;  nLeft  =  0;

	 //  runBuffers_play(  pMgr,  &myPs  );
	 //  bPlayStarted  =  TRUE;

	 for  (  ;  !pPlayAudio->bQuit;  )  {
		  
		  if  (  !dwToInMs  ||  dwToInMs  >  DEFAULT_dwToInMs_playAudio  )  {			  
			  #if  0
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: mcThreadProc_playAudio: dwToInMs %d"  ),  dwToInMs  );
			  #endif
			  dwToInMs  =  DEFAULT_dwToInMs_playAudio;
			  #ifdef  __DEBUG__
					  //  traceLog(  _T(  "Warning: mcThreadProc_playAudio: dwToInMs %d"  ),  dwToInMs  );
			  #endif
		  }

		  DWORD  dwTickCnt0  =  M_GetTickCount_audio(  tickObj  );
		  DWORD  dwTickCnt;
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(
							 pPlayAudio->q2.cfg.usCnt_hEvents,			//  mycountof(  pPlayAudio->hEvents  ),		// Number of events.
							 pPlayAudio->q2.hEvents,					// Location of handles.
                             FALSE,										// Wait for all?
                             dwToInMs,									// How long to wait?
                             0  );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  goto  errLabel;
	      //
		  dwTickCnt =   M_GetTickCount_audio(  tickObj );

		  //  2013/05/26. 本地音频为了aec,需要一直保持. 
		  if  (  !bLocalAudio  )  {
			  if  (  dwTickCnt  -  dwTickCnt_lastAudioData  >  (  DWORD  )pProcInfo->cfg.usTimeoutInMs_player_a  )  {
				  #ifdef  __DEBUG__
						  traceLogA(  "audio data may not arrives, player exits. timeout is %d",  pProcInfo->cfg.usTimeoutInMs_player_a  );
				  #endif
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "audio data may not arrives, player exits. timeout is %d"  ),  pProcInfo->cfg.usTimeoutInMs_player_a  );
				  break;
			  }
		  }

		  //
		  bNeedCheck_oldAudio  =  FALSE;
		  if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
			  dwEvt -= WAIT_OBJECT_0;
			  switch  (  dwEvt  )  {
					  case  0:
							 #ifdef  __DEBUG__
									 traceLogA(  "playAudio: event 0."  );
							 #endif
						     //  dwTickCnt_lastAudioData  =  dwTickCnt;		//  audio data received
							 break;
					  case  1:
							 #ifdef  __DEBUG__
									 #if  0
										  traceLogA(  "playAudio: event 1."  );
									 #endif
							 #endif
						     bNeedCheck_oldAudio  =  TRUE;
							 break;
					  default:
						     traceLogA(  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
		  }

		  //  if  (  dwEvt  ==  0  )  
		  {

			  if  (  !bLocalAudio  )	//  2013/05/25. localAudio不需要等待
			  {

			  if  (  !myPs.bPlayInited  ||  !myPs.bPlayStarted  )  {
				  
				  dwToInMs  =  DEFAULT_dwToInMs_playAudio;
					   
				  len  =  uiBufSize;					   
				  //  if  (  qGetMsg(  &pPlayAudio->q,  pBuf,  (  unsigned  int  *  )&len  )  )  continue;
				  pktLen  =  sizeof(  pPkt[0]  );
				  {
					  CQyQ2Help		q2Help;
					  if  (  qGetMsg(  q2Help.getQ_toGetMsg(  &pPlayAudio->q2  ),  pPkt,  (  unsigned  int  *  )&pktLen  )  )  continue;
				  }
				  if  (  !pPkt->memory.m_pBuf  )  {
					  traceLogA(  "mcThreadProc_playAudio failed: 1. pPkt->pBuf is null"  );
					  continue;
				  }
				  //
				  //  len  =  min(  (  unsigned  int  )len,  pPkt->head.uiLen  );
				  len  =  min(  (  unsigned  int  )len,  pPkt->uiSize_dec  );		//  2016/12/14
				  //
				  if  (  len  )  memcpy(  pBuf,  pPkt->memory.m_pBuf,  len  );
				  clean_myPLAY_AUDIO_DATA(  pPkt,  _T(  "playAudio"  )  );
				
				  #ifdef  __DEBUG__
						  #if  1
							   traceLog(  _T(  "playSound not inited: add audio data len %d, size_dec %d, bufSize %d\n"  ),  len,  pPkt->uiSize_dec,  uiBufSize  );
						  #endif
				  #endif

			      if  (  !len  )  {
					  #ifdef  __DEBUG__
							  traceLogA(  "len can't be 0, error"  );  
					  #endif
					  continue;
				  }

				  //
				  pLeft  =  pBuf;  nLeft  =  len;

			  }
			  }

			  if  (  !myPs.bPlayInited  )  {

				  DWORD		dwOffset_notify_unit	=	pPlayAudio->ah.wfx.nAvgBytesPerSec;

				  memset(  &myPs,  0,  sizeof(  myPs  )  );
				  
				  if  (  initPlay_dx(  pDynLib,  pPlayAudio,  dwOffset_notify_unit  *  4,  &myPs  )  )  goto  errLabel;

				  //
				  myPs.dwOffset_notify_unit  =  dwOffset_notify_unit;
				  myPs.dwNotifyCount  =  2  *  myPs.dsbDesc.dwBufferBytes  /  myPs.dwOffset_notify_unit;
				  myPs.lpdsbpns  =  (  LPDSBPOSITIONNOTIFY  )mymalloc(  myPs.dwNotifyCount  *  sizeof(  DSBPOSITIONNOTIFY  )  );
				  if  (  !myPs.lpdsbpns  )  goto  errLabel;
				  memset(  myPs.lpdsbpns,  0,  myPs.dwNotifyCount  *  sizeof(  DSBPOSITIONNOTIFY  )  );
				  
				  for  (  i  =  0;  i  <  (  int  )myPs.dwNotifyCount;  i  ++  )  {					   
					   myPs.lpdsbpns[i].dwOffset  =  (  i  +  1  )  *  myPs.dwOffset_notify_unit  /  2  -  1;
					   myPs.lpdsbpns[i].hEventNotify  =  pPlayAudio->q2.hEvents[1];

					   //
					   if (pProcInfo->cfg.debugStatusInfo.ucbDbgDetail) {
						   traceLogA("lpdsbpns[%d].dwOffset %d,  dwBufferBytes %d", i, myPs.lpdsbpns[i].dwOffset, myPs.dsbDesc.dwBufferBytes);
					   }
				  }				  

				  //
				  if  (  !pPlayAudio->ah.wfx.nAvgBytesPerSec  )  goto  errLabel;

				  //  
				  myPs.uiMaxMsgWaiting  =  (  bLocalAudio  ?  2  :  10  );
#ifdef  __DEBUG__	//  for test
				  //  traceLogA(  "Warning: myPs.usMaxMsgWaiting is set to 100 for test. 2009/04/27"  );
				  //  myPs.uiMaxMsgWaiting  =  100;
#endif
				  if  (  !myPs.uiMaxMsgWaiting  )  {
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u, uiMaxMsgWaiting error: %d."  ),  pPlayAudio->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id,  myPs.uiMaxMsgWaiting  );
					  goto  errLabel;
				  }

			  }

			  if  (  !myPs.bPlayStarted  )  {

				  traceLogA(  "before play"  );

				#if  0
				  if  (  !bWriteSilenceToOutput(  &myPs,  0,  myPs.dsbDesc.dwBufferBytes  )  )  {
					  traceLogA(  "initPlay_dx: bWriteSilenceToOutput failed."  );
					  goto  errLabel;
				  }
				#endif
			  
				  nWrite  =  MACRO_getnWrite_toFillSilence(  myPs.dwOffset_notify_unit  );
				  if  (  processOutput(  pMgr,  pPlayAudio,  &myPs,  TRUE,  NULL,  nWrite  )  )  {
					  traceLogA(  "playSound: processOutput failed, try to restart"  );
					  goto  errLabel;					  
				  }
				  uiTimeInMs_nWrite  =  (  nWrite  *  1000  /  nAvgBytesPerSec  );
				  pPlayAudio->m_var.uiTimeInMs_audio_remains  +=  uiTimeInMs_nWrite;


				  /*
				  // Start output buffer.
				  if  (  FAILED(  hr = myPs.lpdsb->Play( 0, 0, DSBPLAY_LOOPING )  )  )  goto  errLabel;
				  myPs.bPlayStarted  =  TRUE;

				  if  (  FAILED(  hr  =  myPs.lpdsb->Stop(  )  )  )  goto  errLabel;
				  
				  if  (  FAILED(  hr  =  myPs.lpdsnOutput->SetNotificationPositions(  myPs.dwNotifyCount,  myPs.lpdsbpns  )  )  )  {
					  traceLogA(  "playSound: SetNotificationPositions failed."  );
					  goto  errLabel;
				  }
				  */
				  //  2015/07/30. 没有播放设备时，Play()会死在里面
				  #ifdef  __DEBUG__
						  //showInfo_open0(  0,  0,  _T(  "playAudio: before myPs.lpdsb->Play( 0, 0, DSBPLAY_LOOPING )"  )  );
				  #endif
				  pPlayAudio->m_var.dwTickCnt_beforePlay  =  GetTickCount(  );
				  hr = myPs.lpdsb->Play( 0, 0, DSBPLAY_LOOPING );
				  pPlayAudio->m_var.dwTickCnt_beforePlay  =  0;
				  #ifdef  __DEBUG__
						  //showInfo_open0(  0,  0,  _T(  "playAudio: after myPs.lpdsb->Play( 0, 0, DSBPLAY_LOOPING )"  )  );
				  #endif
				  //
				  if  (  FAILED(  hr  )  )  goto  errLabel;
				  myPs.bPlayStarted  =  TRUE;
				
				  //  continue;
			  }


			  //  continue;
		  }
		  

		  if  (  !myPs.bPlayInited  ||  !myPs.bPlayStarted  )  {
			  
			  dwToInMs  =  DEFAULT_dwToInMs_playAudio;

			  traceLogA(  "event1, play not inited,  not started, or in silence. skipped"  );
			  continue;
		  }

		  //  traceLogA(  "Playing sound event. dwMyWriteCursor %d, dwNotifyCount * dwOffset_notify_unit %d, dwBufferBytes %d",  myPs.dwMyWriteCursor,  myPs.dwNotifyCount  *  myPs.dwOffset_notify_unit,  myPs.dsbDesc.dwBufferBytes  );
		  if  (  myPs.dwMyWriteCursor  >=  myPs.dsbDesc.dwBufferBytes  )  {
			  traceLogA(  "playSound: error: dwMyWriteCursor >= myPs.dsbDesc.dwBufferBytes."  );
			  goto  errLabel;
		  }
			  
		  if  (  FAILED(  hr  =  myPs.lpdsb->GetCurrentPosition(  &dwCurPlayCursor,  NULL  )  )  )  {
			  traceLogA(  "playSound: GetCurrentPosition failed.1"  );
			  goto  errLabel;
		  }
		  DWORD	dwTickCnt_GetCurrentPosition  =  M_GetTickCount_audio(  tickObj  );
		  int	iDiff_dwTickCnt_GetCurrentPosition  =  0;
		  if  (  pPlayAudio->m_var.dwTickCnt_GetCurrentPosition  )  {
			  iDiff_dwTickCnt_GetCurrentPosition  =  dwTickCnt_GetCurrentPosition  -  pPlayAudio->m_var.dwTickCnt_GetCurrentPosition;
			  if  (  iDiff_dwTickCnt_GetCurrentPosition  >  pPlayAudio->m_var.uiTimeInMs_audio_remains  )  {
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playAudio failed: too few audioData remains"  )  );
				  goto  errLabel;
			  }
		  }
		  pPlayAudio->m_var.dwTickCnt_GetCurrentPosition  =  dwTickCnt_GetCurrentPosition;
			  
		  //
		  if  (  myPs.dwMyWriteCursor  >=  dwCurPlayCursor  )  dwBytes_cur2Write  =  myPs.dwMyWriteCursor  -  dwCurPlayCursor;
		  else  dwBytes_cur2Write  =  myPs.dwMyWriteCursor  +  myPs.dsbDesc.dwBufferBytes  -  dwCurPlayCursor;

		  //  2012/02/19
		  unsigned  int  uiTimeInMs_audio_remains  =  dwBytes_cur2Write  *  1000  /  nAvgBytesPerSec;

		  #ifdef  __DEBUG__
				#if  0
					  //  这里的uiTimeInMs_audio_remains其实应该等于pPlayAudio->m_var.uiTimeInMs_audio_remains  -  iDiff_dwTickCnt_GetCurrentPosition;
					  int  iDiff_uiTimeInMs_audio_remains  =  pPlayAudio->m_var.uiTimeInMs_audio_remains  -  iDiff_dwTickCnt_GetCurrentPosition  -  uiTimeInMs_audio_remains;
		  				
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playAudio: %dms remains, iDiff_curPos %dms, still remains %dms, iDiff_remains %dms"  ),  pPlayAudio->m_var.uiTimeInMs_audio_remains,  iDiff_dwTickCnt_GetCurrentPosition,  uiTimeInMs_audio_remains,  iDiff_uiTimeInMs_audio_remains  );
				#endif
		  #endif

		  //
		  if  (  uiTimeInMs_audio_remains  <=  pPlayAudio->m_var.uiTimeInMs_audio_remains  )  pPlayAudio->m_var.uiTimeInMs_audio_remains  =  uiTimeInMs_audio_remains;
		  else  {
			    pPlayAudio->m_var.uiTimeInMs_audio_remains  =  0;

				//
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playAudio err: uiTimeInMs_audio_remains > pPlayAudio.uiTimeInMs_audio_remains"  )  );
		  }


		  #if  0
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playAudio: %dms remains, iDiff_curPos %dms"  ),  pPlayAudio->m_var.uiTimeInMs_audio_remains,  iDiff_dwTickCnt_GetCurrentPosition  );
		  #endif

		  //
		  if  (  pPlayAudio->m_var.uiTimeInMs_audio_remains  >=  pPlayAudio->playCfg.usMinTimeInMsOfAudioDataPlaying  )
		  {

			  #if  0	
			  //  2015/07/05. 不应该在wait后清理，因为这时候可能音频数据已经播放完了，所以remains要是总小于usMinTimeInMsOfAudioDataPlaying,就无法清理队列了，要等填完数据就清理比较好
			  //  2015/07/03
			  if  (  !bNeedCheck_oldAudio  )  {
				  //
				  int  nQ2  =  getQ2Nodes_toGetMsg(  &pPlayAudio->q2  );
				  //
				  if  (  nQ2  >  4  )  {  //  2015/07/03
					  DWORD  tmp_dwTickCnt  =  GetTickCount(  );
					  if  (  tmp_dwTickCnt  -  dwTickCnt_bNeedCheck_oldAudio  >  1000  )  {
						  dwTickCnt_bNeedCheck_oldAudio  =  tmp_dwTickCnt;
						  //
						  bNeedCheck_oldAudio  =  TRUE;
					  }
				  }
			  }
			  //
			  if  (  bNeedCheck_oldAudio  )  {			  
				  if  (  pPlayAudio->m_var.uiSampleTimeInMs  &&  getQ2Nodes_toGetMsg(  &pPlayAudio->q2  )  >  1  )  {				
					  DWORD	tmpTickCnt_now  =  M_GetTickCount_audio(  tickObj  );
					  int  nWaitingInMs_audio  =  MACRO_getnWaitingInMs_audio_internal(  pPlayer->audio,  tmpTickCnt_now  );
					  if  (  pPlayAudio->m_var.uiSampleTimeInMs_newRecvd  <  pPlayAudio->m_var.uiSampleTimeInMs
						  ||  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  >  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  +  1000  
						  ||  (  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  &&  nWaitingInMs_audio  >  (  int  )(  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  +  pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying  )  )  
						  )
					  {
						 #ifdef  __DEBUG__
							     #if  10
									  if  (  pPlayAudio->m_var.uiSampleTimeInMs_newRecvd  <  pPlayAudio->m_var.uiSampleTimeInMs  )  {
										  traceLog(  _T(  "playSound: uiSampleTimeInMs_newRecvd %d, uiSampleTimeInMs %d"  ),  pPlayAudio->m_var.uiSampleTimeInMs_newRecvd,  pPlayAudio->m_var.uiSampleTimeInMs  );
									  }
									  if  (  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  >  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  +  1000  )  {
										  traceLog(  _T(  "playSound: dwTickCnt_newRecvd %d, dwTickCnt %d. SampleTimeInMs %d"  ),  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_newRecvd,  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv,  pPlayAudio->m_var.uiSampleTimeInMs  );
									  }
									  if  (  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  &&  MACRO_getnWaitingInMs_audio_internal(  pPlayer->audio,  tmpTickCnt_now  )  >  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  +  pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying  )  {
										  traceLog(  _T(  "playSound: nWaiting_audio %d > uiMaxTimeInMsToplay %d"  ),  MACRO_getnWaitingInMs_audio_internal(  pPlayer->audio,  tmpTickCnt_now  ),  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  +  pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying  );
									  }								  
								 #endif								
						 #endif
						
						 CQyQ2Help		q2Help;						
						 qRemoveMsg(  q2Help.getQ_toGetMsg(  &pPlayAudio->q2  ),  (  PF_bCommonHandler  )tmpHandler_bOldAudio,  (  void  *  )tmpTickCnt_now,  pPlayer  );								 
					  }							 
				  }
			  }
			  #endif

			  //
			  dwToInMs  =  pPlayAudio->m_var.uiTimeInMs_audio_remains;
			  if  (  dwToInMs  <=  iNotifyInterval  )  {
				  traceLogA(  "mcThreadProc_playAudio: minPlaying < iNotifyInterval"  );
				  goto  errLabel;
			  }
			  dwToInMs  -=  iNotifyInterval;
			  continue;
		  }


		  //
		  //  for  (  ;  nLeft  <  myPs.dwOffset_notify_unit;  )  
		  //  for  (  ;  nLeft  <  myPs.dwOffset_notify_unit  *  2  /  5;  )  
		  for  (  ;  nLeft  <  myPs.dwOffset_notify_unit  *  pPlayAudio->playCfg.usAudioDataAddedToPlayEveryTime  /  1000;  )  
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
				   traceLogA(  "mcThreadproc_playSound failed: len %d < 0",  len  );
				   goto  errLabel;
			   }
			   //  if  (  qGetMsg(  &pPlayAudio->q,  pBuf  +  nLeft,  (  unsigned  int  *  )&len  )  )  break;
			   pktLen  =  sizeof(  pPkt[0]  );
			   {
				   CQyQ2Help	q2Help;
				   if  (  qGetMsg(  q2Help.getQ_toGetMsg(  &pPlayAudio->q2  ),  pPkt,  (  unsigned  int  *  )&pktLen  )  )  break;
			   }
			   if  (  !pPkt->memory.m_pBuf  )  {
				   traceLogA(  "mcThreadProc_playAudio failed: 2. pPkt->pBuf is null"  );
				   break;				   
			   }
			   //
			   //  len  =  min(  (  unsigned  int  )len,  pPkt->head.uiLen  );
			   len  =  min(  (  unsigned  int  )len,  pPkt->uiSize_dec  );			//  2016/12/14
			   //
			   memcpy(  pBuf  +  nLeft,  pPkt->memory.m_pBuf,  len  );
			   clean_myPLAY_AUDIO_DATA(  pPkt,  _T(  "playAudio"  )  );
			   //
			   nLeft  +=  len;
 			  
			   //  2011/11/30
			   dwTickCnt_lastAudioData  =  dwTickCnt;		//  audio data received

			   //  pPlayer->audio.uiSampleTimeInMs  =  pkt.uiSampleTimeInMs;
			   if  (  pPkt->head.uiSampleTimeInMs  )  {
				   uiSampleTimeInMs_pLeft  =  (  (  pPkt->head.uiSampleTimeInMs  >=  iTimeInMs_nLeft  )  ?  (  pPkt->head.uiSampleTimeInMs  -  iTimeInMs_nLeft  )  :  0  );
				   #ifdef  __DEBUG__
				           //  traceLogA(  "playAudio: iSampleTime_pLeft: %u. iTimeInMs_nLeft %d",  uiSampleTimeInMs_pLeft,  iTimeInMs_nLeft  );
				   #endif			
			   }
			   
				#ifdef  __DEBUG__  //  2016/12/15
						#if  0
							 traceLog(  _T(  "playSound: add audio data len %d, size_dec %d, bufSize %d\n"  ),  len,  pPkt->uiSize_dec,  uiBufSize  );
						#endif
				#endif


		  }

		  if  (  !bLocalAudio  )  {	//  2013/05/25. localAudio不需要判断video

		  if  (  !pPlayer->audio.m_var.bVideoReady  )  {
		   	  //  2009/05/03
			  if  (  pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd  
				  &&  pPlayer->video.m_var.uiSampleTimeInMs_newRecvd
				  &&  abs(  (  int  )(  pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd  -  pPlayer->video.m_var.uiSampleTimeInMs_newRecvd  )  )  <  10000  )  
			  {
				  if  (  dwTickCnt  -  pPlayer->video.m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  <  5000  //  means video is active	
					  &&  uiSampleTimeInMs_pLeft  )  
				  {		
					  if  (  pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd  -  uiSampleTimeInMs_pLeft  <  pPlayer->audio.playCfg.usMinTimeInMsToPlay  )  {
						  #ifdef  __DEBUG__
								  traceLogA(  "playAudio: iDiffInMsToPlay %d, delay to wait. fill silence",  pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd  -  uiSampleTimeInMs_pLeft  );
						  #endif
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playAudio: iDiffInMsToPlay %d, delay to wait. fill silence"  ),  pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd  -  uiSampleTimeInMs_pLeft  );

						  //
						  nWrite  =  MACRO_getnWrite_toFillSilence(  myPs.dwOffset_notify_unit  );

						  if  (  processOutput(  pMgr,  pPlayAudio,  &myPs,  TRUE,  NULL,  nWrite  )  )  {
							  traceLogA(  "playSound: processOutput failed, try to restart"  );
							  goto  errLabel;					  
						  }
						  uiTimeInMs_nWrite  =  (  nWrite  *  1000  /  nAvgBytesPerSec  );
						  pPlayAudio->m_var.uiTimeInMs_audio_remains  +=  uiTimeInMs_nWrite;
						  //
						  dwToInMs  =  (  DWORD  )(  nWrite  *  1000.  /  nAvgBytesPerSec  );
						  //  if  (  dwToInMs  >  CONST_notifyInterval  )  dwToInMs  -=  CONST_notifyInterval;
						  if  (  dwToInMs  <=  iNotifyInterval  )  {
							  traceLogA(  "mcThreadProc_playAudio: bVideo not ready, fillSilence, dwToInMs <= iNotifyInterval"  );
							  goto  errLabel;
						  }						  
						  dwToInMs  -=  iNotifyInterval;
						  continue;
					  }
					  //  
					  pPlayer->audio.m_var.bVideoReady  =  TRUE;
				  }
			  }
		  }

		  }

	
		  nWrite  =  0;

		  if  (  nLeft  )  {		  				  
				  
			  nWrite  =  min(  myPs.dwOffset_notify_unit,  nLeft  );
			  //
			  if  (  processOutput(  pMgr,  pPlayAudio,  &myPs,  FALSE,  (  LPBYTE  )pLeft,  nWrite  )  )  {
				  traceLogA(  "playSound: processOutput failed, try to restart"  );
				  goto  errLabel;
			  }
			  uiTimeInMs_nWrite  =  (  nWrite  *  1000  /  nAvgBytesPerSec  );
			  pPlayAudio->m_var.uiTimeInMs_audio_remains  +=  uiTimeInMs_nWrite;

			  pLeft  +=  nWrite;
			  nLeft  -=  nWrite;
		  }
			
		  //  2015/07/05. 不应该在wait后处理，因为这时候可能音频数据已经播放完了，所以remains要是总小于usMinTimeInMsOfAudioDataPlaying,就无法清理队列了，要等填完数据就处理比较好
		  //
		  if  (  pPlayAudio->m_var.uiTimeInMs_audio_remains  >=  pPlayAudio->playCfg.usMinTimeInMsOfAudioDataPlaying  )
		  {
			  //  2015/07/03
			  if  (  !bNeedCheck_oldAudio  )  {
				  //
				  int  nQ2  =  getQ2Nodes_toGetMsg(  &pPlayAudio->q2  );
				  //
				  if  (  nQ2  >  4  )  {  //  2015/07/03
					  DWORD  tmp_dwTickCnt  =  GetTickCount(  );
					  if  (  tmp_dwTickCnt  -  dwTickCnt_bNeedCheck_oldAudio  >  1000  )  {
						  dwTickCnt_bNeedCheck_oldAudio  =  tmp_dwTickCnt;
						  //
						  bNeedCheck_oldAudio  =  TRUE;
					  }
				  }
			  }
			  //
			  if  (  bNeedCheck_oldAudio  )  {			  
				  if  (  pPlayAudio->m_var.uiSampleTimeInMs  &&  getQ2Nodes_toGetMsg(  &pPlayAudio->q2  )  >  1  )  {				
					  DWORD	tmpTickCnt_now  =  M_GetTickCount_audio(  tickObj  );
					  int  nWaitingInMs_audio  =  MACRO_getnWaitingInMs_audio_internal(  pPlayer->audio,  tmpTickCnt_now  );
					  if  (  pPlayAudio->m_var.uiSampleTimeInMs_newRecvd  <  pPlayAudio->m_var.uiSampleTimeInMs
						  ||  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  >  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  +  1000  
						  ||  (  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  &&  nWaitingInMs_audio  >  (  int  )(  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  +  pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying  )  )  
						  )
					  {
						 #ifdef  __DEBUG__
							     #if  10
									  if  (  pPlayAudio->m_var.uiSampleTimeInMs_newRecvd  <  pPlayAudio->m_var.uiSampleTimeInMs  )  {
										  traceLog(  _T(  "playSound: uiSampleTimeInMs_newRecvd %d, uiSampleTimeInMs %d"  ),  pPlayAudio->m_var.uiSampleTimeInMs_newRecvd,  pPlayAudio->m_var.uiSampleTimeInMs  );
									  }
									  if  (  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  >  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  +  1000  )  {
										  traceLog(  _T(  "playSound: dwTickCnt_newRecvd %d, dwTickCnt %d. SampleTimeInMs %d"  ),  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_newRecvd,  pPlayAudio->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv,  pPlayAudio->m_var.uiSampleTimeInMs  );
									  }
									  if  (  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  &&  MACRO_getnWaitingInMs_audio_internal(  pPlayer->audio,  tmpTickCnt_now  )  >  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  +  pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying  )  {
										  traceLog(  _T(  "playSound: nWaiting_audio %d > uiMaxTimeInMsToplay %d"  ),  MACRO_getnWaitingInMs_audio_internal(  pPlayer->audio,  tmpTickCnt_now  ),  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  +  pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying  );
									  }								  
								 #endif								
						 #endif
						
						 CQyQ2Help		q2Help;						
						 qRemoveMsg(  q2Help.getQ_toGetMsg(  &pPlayAudio->q2  ),  (  PF_bCommonHandler  )tmpHandler_bOldAudio,  (  void  *  )tmpTickCnt_now,  pPlayer  );								 
					  }							 
				  }
			  }

#if  0
			  //
			  dwToInMs  =  pPlayAudio->m_var.uiTimeInMs_audio_remains;
			  if  (  dwToInMs  <=  iNotifyInterval  )  {
				  traceLogA(  "mcThreadProc_playAudio: minPlaying < iNotifyInterval"  );
				  goto  errLabel;
			  }
			  dwToInMs  -=  iNotifyInterval;
			  continue;
#endif
		  }




		  //
		  dwToInMs  =  pPlayAudio->m_var.uiTimeInMs_audio_remains;
		  //  if  (  dwToInMs  >  MIN_dwToInMs  )  
		  if  (  dwToInMs  >  iNotifyInterval  )
		  {

			  if  (  nWrite  )  pPlayer->audio.m_var.nTimes_noAudioData  =  0;
				  
			  //  if  (  dwToInMs  >  CONST_notifyInterval  )  dwToInMs  -=  CONST_notifyInterval;
			  dwToInMs  -=  iNotifyInterval;
			  }
		  else  {
			    pPlayer->audio.m_var.nTimes_noAudioData  ++  ;
				
				if  (  pPlayer->audio.m_var.nTimes_noAudioData  >  1  )  {
					pPlayer->audio.m_var.bVideoReady  =  FALSE;					//  this means to check video again
				}

				//  nWrite  =  myPs.dwOffset_notify_unit;
				nWrite  =  MACRO_getnWrite_toFillSilence(  myPs.dwOffset_notify_unit  );
				if  (  processOutput(  pMgr,  pPlayAudio,  &myPs,  TRUE,  NULL,  nWrite  )  )  {
					traceLogA(  "playSound: processOutput failed, try to restart"  );
					goto  errLabel;
				}
				uiTimeInMs_nWrite  =  (  nWrite  *  1000  /  nAvgBytesPerSec  );
				pPlayAudio->m_var.uiTimeInMs_audio_remains  +=  uiTimeInMs_nWrite;

				dwToInMs  +=  uiTimeInMs_nWrite;
				//  if  (  dwToInMs  >  CONST_notifyInterval  )  dwToInMs  -=  CONST_notifyInterval;
				if  (  dwToInMs  <=  iNotifyInterval  )  {
					traceLogA(  "mcThreadProc_playAudio failed: fillSilence, dwToInMs <= iNotifyInterval"  );
					goto  errLabel;
				}
				dwToInMs  -=  iNotifyInterval;

				//
				if  (  !bLocalAudio  )  {
					#ifdef  __DEBUG__
						    traceLogA(  "playAudio: no enough audio data to play. dwToInMs %d. fill silence, tickCnt %d",  dwToInMs,  M_GetTickCount_audio(  tickObj  )  );
					#endif
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u: no enough audio data to play. dwToInMs %d. fill silence, tickCnt %d"  ),  pPlayAudio->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id,  dwToInMs,  M_GetTickCount_audio(  tickObj  )  );
				}

		  }
			
		  //  
		  if  (  nWrite  &&  uiSampleTimeInMs_pLeft  )  {
			  int  iTimeInMs_cur2Write  =  (  int  )(  dwBytes_cur2Write  *  1000.  /  nAvgBytesPerSec  );
			  pPlayer->audio.m_var.uiSampleTimeInMs  =  uiSampleTimeInMs_pLeft;
			  pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_internal  =  dwTickCnt  +  iTimeInMs_cur2Write;
			  pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_syncAv  =  M_GetTickCount_av(  tickObj  )  +  iTimeInMs_cur2Write;		//  2012/02/19
			  pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  =  GetTickCount(  );

			  //
			  uiSampleTimeInMs_pLeft  =  0;
			  //
			  //  
			  #if  0	//  2012/01/27. 让video自己来读取和设置时间戳
					q2TriggerToProcess(  &pPlayer->video.q2  );
			  #endif

			  #ifdef  __DEBUG__
					  //  traceLogA(  "playAudio: iSampleTimeInMs: %d, iTimeInMs_cur2Write %d",  pPlayer->audio.uiSampleTimeInMs,  iTimeInMs_cur2Write  );
					  //  traceLogA(  "playAudio: iSampleTimeInMs_pLeft: %d, dwTickCnt %d",  pPlayer->audio.m_var.uiSampleTimeInMs,  pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs  );
			  #endif
			  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPlayAudioStatus  )  {	//  2015/05/24
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playAudio: %I64u,%d: iSampleTimeInMs: %u, iTimeInMs_cur2Write %d, audio_remains %d"  ),  pPlayer->idInfo_recorder.ui64Id,  pPlayer->audio.uiTranNo,  pPlayer->audio.m_var.uiSampleTimeInMs,  iTimeInMs_cur2Write,  pPlayer->audio.m_var.uiTimeInMs_audio_remains  );
			  }
		  }


		  continue;
	 }

 
	 traceLogA(  "mcThreadProc_playSound will quit"  );

errLabel:

	 if  (  myPs.bPlayInited  )  {
		 exitPlay_dx(  pDynLib,  pPlayAudio,  &myPs  );
	 }

	 //
	 if  (  bLocalAudio  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, Local audio, ends."  ),  pPlayAudio->q2.cfg.name  );
	 else  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u ends."  ),  pPlayAudio->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id  );
	 
	 //  if  (  pBuf  )  free(  pBuf  );

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
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Local audio player: postMsg to notify inputErr"  )  );
		 }
	 }
#endif

	traceLogA(  "playSound %S leaves",  pPlayAudio->q2.cfg.name  );
#endif

	return  0;
}





