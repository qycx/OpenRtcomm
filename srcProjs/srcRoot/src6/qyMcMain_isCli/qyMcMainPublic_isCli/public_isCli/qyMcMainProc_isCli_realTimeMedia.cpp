
#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qyPlaySound_wave.h"
//  #include	"QyRecordSound_wave.h"
#include	"module_qisCamCap.h"

#include	"mmDeviceProc.h"
#include	"qmcCommFunc_isCli.h"
#include	"ctxMcThread.h"
#include	"qisWebRtcPublic.h"

//
 int  getuiTranNo_openAvDev_audio(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	static  unsigned  int	suiTranNo_openAvDev_audio	=	0;

	if  (  !suiTranNo_openAvDev_audio  )  suiTranNo_openAvDev_audio  =  getuiNextTranNo(  0,  0,  0  );

	return  suiTranNo_openAvDev_audio;
}








 int  startLocalAudioPlayer(  MC_VAR_isCli  *  pProcInfo  )
{
	int						iErr		=		-1;

	if  (  !pProcInfo  )  return  -1;
	QY_MC				*	pQyMc		=		pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;

	//
	DWORD					dwThreadDaemonId;

#if  0
	if  (  bLocalAudioPlaying  )  {
		pProcInfo->av.localAv.recordSoundProcInfo.bLocalAudioPlaying  =  TRUE;
	}
#endif

	//
	waitForQThread(  (  QY_qThreadProcInfo_common  *  )&pProcInfo->av.localAv.player.audio, 0  );
	if  (  !bQThreadExists(  pProcInfo->av.localAv.player.audio  )  )  {

		//  2011/08/08
#if  0
		AV_COMPRESSOR_CFG	avCompressor;
		if  (  myGetAvCompressorCfg(  CONST_capType_av,  0,  0,  0,  &avCompressor  )  )  goto  errLabel;

		//  2009/04/27
		memcpy(  &pProcInfo->av.localAv.player.audio.ah.wfx,  &avCompressor.audio.wf_decompress_default,  sizeof(  pProcInfo->av.localAv.player.audio.ah.wfx  )  );
#endif
		memcpy(  &pProcInfo->av.localAv.player.audio.ah.wfx,  &pProcInfo->av.localAv.recordSoundProcInfo.wf_org,  sizeof(  pProcInfo->av.localAv.player.audio.ah.wfx  )  );

		//
		PLAY_AUDIO_procInfo  *  pPlayAudio  =  &pProcInfo->av.localAv.player.audio;


		//
		unsigned  int  uiPlayType  =  pQyMc->uiAPlayType;

		//
		pPlayAudio->bQuit  =  FALSE;
		pPlayAudio->bRunning  =  FALSE;


		//  if  (  pQyMc->bUseDirectSound_toPlay  )  
		if  (  uiPlayType  ==  CONST_aPlayType_dSound  )   //  2017/02/16
		{
			
			exitDSoundToPlayIfNoPlayer(  pProcInfo  );
			
			//  2013/05/24
			LPGUID  lpGuid  =  NULL;
			
			OLD_audioDevice	audioDev;
			if  (  !getDefaultPlaybackDevice(  &audioDev  )  )  {			
				lpGuid  =  &audioDev.guid_audio;	
				safeTcsnCpy(  audioDev.names_audio,  pProcInfo->av.localAv.player.audio.playbackDevDesc,  mycountof(  pProcInfo->av.localAv.player.audio.playbackDevDesc  )  );
			}

			//
			if  (  pProcInfo->pPlayDev->initDSoundToPlay(  (  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx,  lpGuid,  pQyMc->gui.hMainWnd,  0  )  )  goto  errLabel;

			//
			pProcInfo->av.localAv.player.audio.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_playAudio,  pProcInfo,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			if  (  !pProcInfo->av.localAv.player.audio.hThread  )  goto  errLabel;
			pProcInfo->av.localAv.player.audio.dwThreadId  =  dwThreadDaemonId;
			if  (  ResumeThread(  pProcInfo->av.localAv.player.audio.hThread  )  ==  -1  )  goto  errLabel;
			}
		else  {		//  use wave api, 2010/05/03
#ifndef  __qmdConn__
			  #include	"unDeclareDebugNew.h"
			  if  (  startQThread(  NULL,  0,  new  CQyPlaySound,  (  QY_qThreadProcInfo_common  *  )&pProcInfo->av.localAv.player.audio  )  )  goto  errLabel;
			  #include	"declareDebugNew.h"
#endif
			  
		}
	}


	iErr  =  0;

errLabel:

	//  2013/05/28
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "startLocalAudioPlayer called, iErr %d"  ),  iErr  );				

	return  iErr;
}



 int  stopLocalAudioPlayer(  MC_VAR_isCli  *  pProcInfo,  int  nTries  )
{
	int						iErr		=		-1;
	if  (  !pProcInfo  )  return  -1;
	QY_MC				*	pQyMc		=		pProcInfo->pQyMc;	

	//
	if  (  !nTries  )  nTries  =  10;

	//
	pProcInfo->av.localAv.recordSoundProcInfo.bLocalAudioPlaying  =  FALSE;

	//
	int  i;
	for  (  i  =  0;  i  <  nTries;  i  ++  )  {
		 if  (  !bQThreadExists(  pProcInfo->av.localAv.player.audio  )  )  break;

		 pProcInfo->av.localAv.player.audio.bQuit  =  TRUE;
		 if  (  pProcInfo->av.localAv.player.audio.q2.hEvents[0]  )  SetEvent(  pProcInfo->av.localAv.player.audio.q2.hEvents[0]  );
		 //  if  (  !pQyMc->bUseDirectSound_toPlay  )  
		 if  (  pQyMc->uiAPlayType  ==  CONST_aPlayType_wave  )  		//  2017/02/16	
		 {
				 PostThreadMessage(  pProcInfo->av.localAv.player.audio.dwThreadId,  CONST_qyWm_postComm,  CONST_qyWmParam_endThread,  0  );
		 }
		 //
		 waitForQThread(  (  QY_qThreadProcInfo_common  *  )&pProcInfo->av.localAv.player.audio,  1000  );
	}
	
	//  2013/05/28
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "stopLocalAudioPlayer called"  )  );				

	return  0;
}


   //  2013/05/23
 int  startLocalAudioPlaying(  MC_VAR_common  *  pProcInfoCommon  )
{
	MC_VAR_isCli			*	pProcInfo	=		(  MC_VAR_isCli  *  )pProcInfoCommon;
	if  (  !pProcInfo  )  return  -1;
	if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  return  -1;

	pProcInfo->av.localAv.recordSoundProcInfo.bLocalAudioPlaying  =  TRUE;

	return  0;
}

 //  2013/05/23
 int  stopLocalAudioPlaying(  MC_VAR_common  *  pProcInfoCommon  )
{
	MC_VAR_isCli			*	pProcInfo	=		(  MC_VAR_isCli  *  )pProcInfoCommon;
	if  (  !pProcInfo  )  return  -1;
	if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  return  -1;

	pProcInfo->av.localAv.recordSoundProcInfo.bLocalAudioPlaying  =  FALSE;

	return  0;
}


 //
 //  2017/06/15
 int  closeOtherPlayers(  MC_VAR_isCli  *  pProcInfo  )
{
	int						iErr		=		-1;

	if  (  !pProcInfo  )  return  -1;
	QY_MC				*	pQyMc		=		pProcInfo->pQyMc;
	int						i;

	//
	traceLogA(  (char*)  (  "closeOtherPlayers enters."  )  );
	showInfo_open0(0, 0, _T("closeOtherPlayers enters"));

	//
	if  (  pProcInfo->av.pPlayers  )  {

		for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
			 QY_PLAYER  *  pPlayer  =  &pProcInfo->av.pPlayers[i];
			  PLAY_AUDIO_procInfo  *  pPlayAudio	=	&pProcInfo->av.pPlayers[i].audio;
			  PLAY_VIDEO_procInfo  *  pPlayVideo	=	&pProcInfo->av.pPlayers[i].video;
			  if  (  pPlayAudio->uiPlayType  )  {
				  pPlayAudio->bQuit  =  TRUE;
				  if  (  pPlayAudio->q2.hEvents[0]  )  SetEvent(  pPlayAudio->q2.hEvents[0]  );
				  //				
				  if  (  pQyMc->uiAPlayType  ==  CONST_aPlayType_wave  )  					
				  {
						  PostThreadMessage(  pPlayAudio->dwThreadId,  CONST_qyWm_postComm,  CONST_qyWmParam_endThread,  0  );
				  }
			  }
			  if  (  pPlayVideo->uiPlayType  )  {
				  pPlayVideo->bQuit  =  TRUE;
				  if  (  pPlayVideo->q2.hEvents[0]  )  SetEvent(  pPlayVideo->q2.hEvents[0]  );
			  }
		 }
		 for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
			 QY_PLAYER  *  pPlayer  =  &pProcInfo->av.pPlayers[i];
			  PLAY_AUDIO_procInfo  *  pPlayAudio	=	&pProcInfo->av.pPlayers[i].audio;
			  PLAY_VIDEO_procInfo  *  pPlayVideo	=	&pProcInfo->av.pPlayers[i].video;

			  //
#if 0
			  TCHAR  tBuf[128];
			  _sntprintf(tBuf, mycountof(tBuf), _T("closeOtherPlayes: audio.playType %d, video.playType %d"), pPlayAudio->uiPlayType, pPlayVideo->uiPlayType);
			  showInfo_open0(0, 0, tBuf);
			  if (pPlayAudio->uiPlayType  ) {
				  //MessageBox(null, _T("hh"), _T("mm"), MB_OK);
			  }/
#endif

			  //
			  if  (  pPlayAudio->uiPlayType  )  {
				  switch  (  pPlayAudio->uiPlayType  )  {
						  case  CONST_aPlayType_dSound:
							    //myWaitForQThread_infinite(  (  QY_qThreadProcInfo_common  *  )pPlayAudio,  _T(  "closeOtherPlayers"  )  );
							    stopPlayAudio_dSound(pPlayer  );
								break;
						  case  CONST_aPlayType_webRtc:
							    //
							    showInfo_open0(0, 0, _T("closeOtherPlayers: before stopPlayAudio_webRtc"));

							    //
							    stopPlayAudio_webRtc(  pPlayer  );
							    break;
						  default:
								 break;
				  }
				  pPlayAudio->uiPlayType  =  0;
			  }
			  
			  //
			  if  (  pPlayVideo->uiPlayType  )  {
				  switch  (  pPlayVideo->uiPlayType  )  {
						  case  CONST_vPlayType_v:
							    //
							    #ifdef  __DEBUG__
										//traceLog((TCHAR*)  _T(  "before waitForVideoThread, %d"  ),  j  );
								#endif
				  
								//
								myWaitForQThread_infinite(  (  QY_qThreadProcInfo_common  *  )pPlayVideo,  _T(  "closeOtherPlayers"  )  );
								//
							    #ifdef  __DEBUG__						  
										traceLog((TCHAR*)  _T(  "after waitForVideoThread"  )  );
								#endif
								//
								break;
						  default:
								  break;
				  }
				  //
				  pPlayVideo->uiPlayType  =  0;
			  }
			  //
		 }

	}

	traceLogA(  (char*)  (  "closeOtherPlayers leaves."  )  );
	showInfo_open0(0, 0, _T("closeOtherPlayers leaves"));


	return  0;
}



 

 //
 int  exitDSoundToPlayIfNoPlayer(  MC_VAR_isCli  *  pProcInfo  )
{
	int						iErr		=		-1;
	if  (  !pProcInfo  )  return  -1;
	QY_MC				*	pQyMc		=		pProcInfo->pQyMc;
	QY_SERVICEGUI_INFO	*	pSci		=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;
	
	int						i;
	PLAY_AUDIO_procInfo	*	pPlayAudio;

	if  (  bDSoundToPlayInited(  )  )  {
		//  try to check if any player exists
		for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
			 pPlayAudio  =  &pProcInfo->av.pPlayers[i].audio;
			 if  (  !bQThreadExists(  *pPlayAudio  )  )  continue;
			 if  (  !pPlayAudio->bRunning  )  waitForQThread(  (  QY_qThreadProcInfo_common  *  )pPlayAudio,  0  );
			 if  (  bQThreadExists(  *pPlayAudio  )  )  break;			 
		}
		if  (  i  ==  pProcInfo->av.usCnt_players  )  {
			if  (  !pProcInfo->av.localAv.player.audio.bRunning  )  {
				waitForQThread(  (  QY_qThreadProcInfo_common  *  )&pProcInfo->av.localAv.player.audio,  0  );
			}
			if  (  !bQThreadExists(  pProcInfo->av.localAv.player.audio  )  )  {
				pProcInfo->pPlayDev->exitDSoundToPlay(  (  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx,  0,  0  );
			}
		}
	}

	return  0;
}



 extern "C" DWORD WINAPI mcThreadProc_mis_realTimeMedia( LPVOID lpParameter )
{
	 QY_SERVICEGUI_INFO			*		pSci							=	(  QY_SERVICEGUI_INFO  *  )lpParameter;
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli				*		pProcInfo						=	(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 QY_MC						*		pQyMc							=	pProcInfo->pQyMc;
	 
	 int								loopCtrl						=	0;
	 int								i;
	 DWORD								dwThreadId						=	GetCurrentThreadId(  );
	 CQyMalloc							mallocObj;
	 MIS_MSGU					*		pMsg							=	NULL;
	 unsigned  int						len;
	 DWORD								dwRet;
	 //  long								lPrev;
	 //
	 CTX_MC_THREAD						ctx;
	 CQyMalloc							mallocObj_pMsgInputBuf;
	 CQyMalloc							mallocObj_pMsgBuf;
	 //
	 //  CWnd						*		pMainWnd						=	AfxGetApp(  )->m_pMainWnd;
	 //
	 QY_Q2						*		pTriggerQ						=	&pProcInfo->realTimeMediaQ2;
	 unsigned  int						uiChannelType					=	CONST_channelType_realTimeMedia;
	 
	 //
	 int lastTickCnt_chkTasksStatus = 0;

	 //
#ifdef  __DEBUG__	 
	 traceLogA(  (char*)  "mcThreadProc_mis_realTimeMedia:  enters"  );
#endif 

	 //
	 memset(  &ctx,  0,  sizeof(  ctx  )  );
	 ctx.pProcessQ  =  &pProcInfo->processQ_media;
	 ctx.pMsgBuf_forInput  =  (  MIS_MSGU  *  )mallocObj_pMsgInputBuf.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 if  (  !ctx.pMsgBuf_forInput  )  goto  errLabel;
	 ctx.pMsgBuf  =  (  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 if  (  !ctx.pMsgBuf  )  goto  errLabel;
	 	 
	 //
	 if  (  !(  pMsg  =  (  MIS_MSGU  *  )mallocObj.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  )  )  )  goto  errLabel;


	 //
	 for  (  ;  !pQyMc->bQuit;  loopCtrl  ++  )  {
		 if (!pQyMc->bLogon) {
			 break;
		 }

		  //  if  (  !pMainWnd  )  pMainWnd					=	AfxGetApp(  )->m_pMainWnd;
		  if  (  !pQyMc->gui.hMainWnd  )  {
			  Sleep(  1000  );  continue;
		  }

		  //
		  int  iWaitTimeInMs = 5000;
		  iWaitTimeInMs = CONST_iWaitTimeInMs_rtMedia;
		  dwRet  =  WaitForSingleObject(  pTriggerQ->hEvents[0],  iWaitTimeInMs  );
		  if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
		  
		  for  (  ;  !pQyMc->bQuit;  )  {
			   len  =  sizeof(  pMsg[0]  );
#if  0
			   {
				   CQyQ2Help	q2Help;
				   if  (  qGetMsg(  q2Help.getQ_toGetMsg(  pTriggerQ  ),  pMsg,  &len  )  )  break;
			   }
#endif			//  2014/04/10
			   if  (  q2GetMsg(  pTriggerQ,  pMsg,  &len,  _T(  "thread_rtMedia"  )))  break;

			   memset(  (  (  char  *  )pMsg  )  +  len,  0,  min(  256,  sizeof(  pMsg[0]  )  -  len  )  );			   

			   switch  (  pMsg->uiType  )  {
					   case  CONST_misMsgType_input:  {
						     MIS_CNT					*		pMisCnt							=  (  MIS_CNT  *  )pMsg->input.pMisCnt;
							 MIS_CHANNEL				*		pChannel						=	NULL;

							 if  (  !pMisCnt  )  break;
							 //  if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  pMsg->input.uiChannelType  )  )  )  break;
							 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  break;

							 if  (  isUcFlgResp(  pMsg->input.ucFlg  )  )  {
								 if  (  procMsgInput_other_resp(  pQyMc,  pSci,  pProcInfo,  &pMsg->input,  len,  &ctx,  pChannel  )  )  {
									 //  traceLogA(  (char*)  "mcThreadProc_mis_realTimeMedia: procMsgInput_other_resp failed."  );
								 }
								}
							 else  {
								 if  (  procMsgInput_other_req(  pQyMc,  pSci,  pProcInfo,  &pMsg->input,  len,  &ctx,  pChannel  )  )  {
									 //  traceLogA(  (char*)  "mcThreadProc_mis_realTimeMedia: procMsgInput_other_req failed."  );
								 }
							 }							 

							 //
							 }							 
						     break;
					   case  CONST_misMsgType_talk:  
						     traceLogA(  (char*)  "mcThreadProc_mis_realTimeMedia: msg_talk ÔÝÊ±²»´¦Àí"  );
						     break;
					   case  CONST_misMsgType_task:  {
						     MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMsg->task.pMisCnt;
							 MIS_CHANNEL				*		pChannel						=	NULL;

							 if  (  !pMisCnt  )  break;
							 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  break;

							 if  (  procMsgTask_mc_media(  pQyMc,  pSci,  pProcInfo,  &pMsg->task,  len,  FALSE,  &ctx,  pChannel  )  )  break;

							 //  printMisMsg(  0,  0,  pMsg  );

							 }
						     break;
					   case  CONST_misMsgType_applyForChkChannels_qmc:  {
						     MIS_CNT	*	pMisCnt		=	(  MIS_CNT  *  )pMsg->applyForChkChannels_qmc.pMisCnt;
							 if  (  !pMisCnt  )  break;
							 
							 traceLog((TCHAR*)  _T(  "rtMedia: applyForChkChannels"  )  );
							 startChannel(  pProcInfo,  pMisCnt,  getChannelByType(  pMisCnt,  uiChannelType  ),  _T(  "rtMedia: applyForChannels"  )  );  		

							 }						     
						     break;

					   case  CONST_misMsgType_outputTask:  
						     /*
							 {
						     MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMsg->task.pMisCnt;
							 MIS_CHANNEL				*		pChannel						=	NULL;

						     if  (  !pMisCnt  )  break;
							 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  pMsg->task.uiChannelType  )  )  )  break;

							 if  (  procMsgTask2Output_mc(  pQyMc,  pSci,  pProcInfo,  pMisCnt,  &pMsg->task,  len,  pChannel  )  )  break;
							 }
						     break;
							 */
					   default:
								traceLogA(  (char*)  "mcThreadProc_mis_realTimeMedia failed, Î´´¦ÀíµÄÏûÏ¢ÀàÐÍ%d",  pMsg->uiType  );
								break;
			   }
		
			   //  dwRet  =  WaitForSingleObject(  pTriggerQ->hSemaTrigger,  50  );
			   //  if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;			   
		  }

		  //
		  bool  bNeedStartChannel;  bNeedStartChannel = false;
		  //
		  if (!(loopCtrl % 2))
		  {
			  int  tickCnt0 = myGetTickCount(mynull);
			  int  lDiffInMs = tickCnt0 - lastTickCnt_chkTasksStatus;
			  if (abs(lDiffInMs) > 1000) {
				  bNeedStartChannel = true;
				  //
				  lastTickCnt_chkTasksStatus = tickCnt0;
			  }
		  }
		  if (pProcInfo->av.bNeedStartChannel_a) {
			  bNeedStartChannel = true;
			  //  这里要将标志位清除
			  pProcInfo->av.bNeedStartChannel_a = false;
			  //
			  showInfo_open0(0, 0, _T("rtMedia: bNeedStartChannel_a is true"));
		  }
		  //
		  if (bNeedStartChannel) {
			  //
			  if (pProcInfo->status.tasksStatus.bTaskExists_av) {
				  MIS_CNT* pMisCnt = (MIS_CNT*)pProcInfo->getMisCntByName(_T(""));
				  if (!pMisCnt)  break;

				  //
				  //traceLog((TCHAR*)_T("rtMedia: taskExists_av true, try to startChannel "));
				  startChannel(pProcInfo, pMisCnt, getChannelByType(pMisCnt, uiChannelType), _T("rtMedia: taskExists_av true, try to startChannels"));
			  }
		  }		  

		  //
		  if  (  !(  loopCtrl  %  5  )  )  {

			  //  for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
			  for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
			  {
				   MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  i  );  //&pProcInfo->misCnts[i]; 
				   if  (  !pMisCnt  )  continue;
				   //
				   if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;

				   waitForChannel(  pProcInfo,  pMisCnt,  uiChannelType,  FALSE  );
			  }
		  }
	 }


errLabel:

	 //for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
	 for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
	 {
		  MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  i  );  //&pProcInfo->misCnts[i]; 
		  if  (  !pMisCnt  )  continue;
		  //
		  if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;

		  waitForChannel(  pProcInfo,  pMisCnt,  uiChannelType,  TRUE  );
	 }


	 // 
	 //  pProcInfo->processQ_media.emptyQ(  );
	 
	 pProcInfo->status.threadsStatus.ulbRealTimeMediaQuit  =  TRUE;

	 traceLogA(  (char*)  "mcThreadProc_mis_realTimeMedia:  leaves"  );

	 return  0;
}



