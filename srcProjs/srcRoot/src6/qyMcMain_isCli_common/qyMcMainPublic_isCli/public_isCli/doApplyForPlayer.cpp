

#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qyCusResTemp.h"

#ifndef  __NOTSUPPORT_MULTIDOC__
	//#include	"mainClient.h"
	//#include	"mainFrm.h"
#endif
#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	"qmcVideoCapture_isCli.h"

#include	"myresource.h"

#ifdef  __WINCE__
		#ifndef  __TEST__
				 #include	"ceMenuBar.h"
		#endif
		#include	"dlgTalk_ce.h"
#else
		#include	"dlgtalkproc.h"
#endif

#include	"QyPlaySound_wave.h"
#include	"qmcDxSurfacePublic.h"
#include	"qyWnd.h"

#include	"dlgMcClientLogon.h"
#ifdef  __WINCE__
		#include	"dlg_qyMc_winCe.h"
		#include	"dlgObjs.h"
#endif
#include	"DlgQnmCfgOptionsIsClient.h"
#include	"module_qisCamCap.h"

#ifndef  __NOTSUPPORT_MULTIDOC__
		 //#include	"dlgNotification.h"
#endif

//  
#include	"mmDeviceProc.h"
#include	"isCliHelpPublic.h"
#include	"wallTalkers.h"
#include	"isCliD3dPublic.h"
#include	"isCliCorePublic.h"
#include	"dyn_isCliD3d_public.h"
#include	"qmcCommFunc_isCli.h"

//
#include	"qisWebRtcPublic.h"
#include	"aecPublic.h"


//  2013/05/24
BOOL  bTaskId_conference(  int  iTaskId  )
{
	BOOL				bRet				=	FALSE;
	MC_VAR_isCli	*	pProcInfo			=	QY_GET_procInfo_isCli(  );
	int					iIndex_sharedObj	=  getSharedObjIndex_localAv(  );
	QY_SHARED_OBJ	*	pSharedObj			=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;

	if  (  !iTaskId  )  goto  errLabel;

	if  (  !bSharedObjActive(  pProcInfo,  iIndex_sharedObj  )  )  goto  errLabel;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pSharedObj->usrs  );  i  ++  )  {
		if  (  pSharedObj->usrs[i].iTaskId  ==  iTaskId  )  break;		 
	}
	if  (  i  ==  mycountof(  pSharedObj->usrs  )  )  goto  errLabel;

	bRet  =  TRUE;

errLabel:
	return  bRet;
}


//


//
int  myWaitForQThread_infinite(  QY_qThreadProcInfo_common  *  pQThread,  LPCTSTR  hint  )
{
	if  (  !hint  )  hint  =  _T(  ""  );

	int  nTries  =  30;	//  这里必须停下来								  				  
	int  i;
		
	for  (  i  =  0;  i  <  nTries;  i  ++  )  {		 
		 if  (  !bQThreadExists(  *pQThread  )  )  break;
										   
		 pQThread->bQuit  =  TRUE;			
		 //
		 if  (  pQThread->q2.hEvents[0]  )  SetEvent(  pQThread->q2.hEvents[0]  );
		 //
		 //						
		 waitForQThread(  (  QY_qThreadProcInfo_common  *  )pQThread,  1000  );					  
		
	}				  

	//
	if  (  i  ==  nTries  )  {	//  2013/08/02							  	
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: waitFor failed. l113"  ),  hint  );
		qyExitProcess(  tBuf  );					  								  
	}

	return  0;
}



//
BOOL  bPlayerOk(QY_PLAYER* pPlayer, Param_dbg* pParam)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	TCHAR  tBuf[128];
	TCHAR* pHint; pHint = nullptr;

	//
	PLAY_AUDIO_procInfo* pPlayAudio = &pPlayer->audio;
	
	//
	Param_dbg  param;
	if (pParam) {
		param.m_bShowInfo = pParam->m_bShowInfo;
		param.m_pHint = pParam->m_pHint;
	}


	//
	DWORD  dwTickCnt  =  myGetTickCount(  mynull  );

	//
	if (pPlayer->bNeedEnd1) {
		//
		//safeTcsnCpy(_T("bNeedEnd1 true"), tHint, cntof_tHint);
		//
		return  false;
	}



	//
	BOOL  bNeedEnd_a = FALSE;
	BOOL  bNeedEnd_v = FALSE;


	//
	switch  (  pPlayAudio->uiPlayType  )  {
			case  0:
				  break;
			case  CONST_aPlayType_dSound:
			case  CONST_aPlayType_webRtc:  {
				  int  nDiff  =  0;
				  //  2018/06/16
				  if  (  pPlayAudio->bNeedStop_webRtc_my_inStream  )  {
					  bNeedEnd_a  =  TRUE;
					  //
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "bPlayAudio_needEnd: %I64u, bNeedStop is true"  ),  pPlayer->idInfo_recorder.ui64Id  );
					  showInfo_open0(  0,  0,  tBuf  );
				  }
				  //
				  nDiff  =  dwTickCnt  -  pPlayAudio->dwLastTickCnt_startPlayer;
				  nDiff  =  abs(  nDiff  );
#ifdef  __DEBUG__
				  _sntprintf(tBuf, mycountof(tBuf), _T("bPlayerOk: %I64u: a:e_start %dms"), pPlayer->idInfo_recorder.ui64Id,  nDiff);
#endif 
				  //
				  if (nDiff < 1000)  break;
				  //
				  nDiff  =  dwTickCnt  -  pPlayAudio->cache.dwTickCnt_lastAudioData3;
				  nDiff  =  abs(  nDiff  );
#ifdef  __DEBUG__
				  _sntprintf(tBuf, mycountof(tBuf), _T("%s. e_lastData %dms"), tBuf, nDiff);
#endif 
				  if  (  nDiff  >  (  DWORD  )pProcInfo->cfg.usTimeoutInMs_player_a  )  {
					  pPlayAudio->nTimes_noAudioData_webRtc  ++  ;
					  }
				  else  {
					    pPlayAudio->nTimes_noAudioData_webRtc  =  0;					  
				  }
				  //
#ifdef  __DEBUG__
#endif
					
				  //
				  if  (  pPlayAudio->nTimes_noAudioData_webRtc  >  3  )  {
					  bNeedEnd_a  =  TRUE;  break;
				  }
				  }
				  break;
			default:	

				break;

	}

	//
	int  v_e_start = abs((int)(dwTickCnt - pPlayer->video.dwLastTickCnt_startPlayer));
	int  v_e_lastData = abs((int)(dwTickCnt - pPlayer->video.m_var.dwTickCnt_lastData));
#ifdef  __DEBUG__
	_sntprintf(tBuf, mycountof(tBuf), _T("%s. v.e_start %dms, e_lastData %dms"), tBuf, v_e_start, v_e_lastData);
	//
	//  showInfo_open(0, 0, 0, tBuf);
#endif 

	if  (  v_e_start > 1000  //  线程没启动，或已停止					
		&& v_e_lastData  >  3000  )
	{
		bNeedEnd_v = true;
	}

	//
#if  10
	if (bNeedEnd_a && bNeedEnd_v) {
		return false;
	}
#endif 


	//
	if (pQyMc->bQuit || !pQyMc->bLogon || pPlayer->status.ulbPlayerErr) {
		return false;
	}

	//
	return  true;
}



//
//
 int  chkPlayers(  MC_VAR_isCli  *  pProcInfo  )
{
	int						iErr		=		-1;
	if  (  !pProcInfo  )  return  -1;
	QY_MC				*	pQyMc		=		pProcInfo->pQyMc;
	int						i;
	//
	TCHAR					tBuf[128];



	//
	//traceLogA(  (char*)  (  "chkPlayers called."  )  );

	if  (  !pProcInfo->av.pPlayers  )  {
		return  0;
	}

	 //
	 QY_PLAYER				*	pPlayer;
	 PLAY_AUDIO_procInfo	*	pPlayAudio;
	 PLAY_VIDEO_procInfo	*	pPlayVideo;

	 //  comment: player是一个数组,在pProcInfo->av.pPlayers[]. pProcInfo是一个全局的结构
	 //
	 for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
		 pPlayer  =  &pProcInfo->av.pPlayers[i];
		 pPlayAudio  =  &pProcInfo->av.pPlayers[i].audio;
		 pPlayVideo  =  &pProcInfo->av.pPlayers[i].video;
		 //
		 //  comment: 这段是判断哪个player是退出了。如果退出就回收player		 
#if  0
		 waitForQThread(  (  QY_qThreadProcInfo_common  *  )pPlayAudio,  0  );
		 waitForQThread(  (  QY_qThreadProcInfo_common  *  )pPlayVideo,  0  );
		 if  (  !bQThreadExists(  *pPlayAudio  )  &&  !bQThreadExists(  *pPlayVideo  )  )  {
			 if  (  pPlayer->idInfo_recorder.ui64Id  ||  pPlayAudio->uiTranNo  ||  pPlayVideo->uiTranNo  )  											  
			 {
				 pPlayer->idInfo_recorder.ui64Id  =  0;										//  reset
				 pPlayAudio->uiTranNo  =  0;
				 pPlayVideo->uiTranNo  =  0;
				 pPlayer->iTaskId  =  0;														//  2009/09/17
			 }
		 }
#endif
		//
		DWORD  dwTickCnt  =  myGetTickCount(  mynull  );

		//
#ifdef  __DEBUG__
		if  (  pPlayer->idInfo_recorder.ui64Id  == 110  )  {
			int  ii  =  1;
			//
		}
#endif

		//  2017/06/13
		//if  (  pPlayer->idInfo_recorder.ui64Id  )  
		{
			if  (  pPlayAudio->uiPlayType  )  {
				//
				TCHAR  tHint[128]  =  _T("");
				
				if  (  !bPlayerOk(  pPlayer, mynull  )  )  {
					//
					_sntprintf(tBuf, mycountof(tBuf), _T("chkPlayers: clean playAudio index_player %d, %I64u, %d,%d."), i,  pPlayer->idInfo_recorder.ui64Id, pPlayAudio->uiTranNo, pPlayer->video.uiTranNo);
					_sntprintf(tBuf, mycountof(tBuf), _T("%s. %s"), tBuf, tHint);
										
					//			
					//qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
					showInfo_open(0, 0, 0, tBuf);
							
					//  回收
					pPlayAudio->bQuit  =  TRUE;		//  注意：bQuit不能在mcThread_playX里赋值，只能在主线程里赋值
					switch  (  pPlayAudio->uiPlayType  )  {
							case  CONST_aPlayType_webRtc:
								  stopPlayAudio_webRtc(  pPlayer  );							
								  break;						
							case  CONST_aPlayType_dSound:							 
								  //
								  //myWaitForQThread_infinite(  (  QY_qThreadProcInfo_common  *  )pPlayAudio,  _T(  "doApplyForPlayer"  )  );								  
								  stopPlayAudio_dSound( pPlayer  );
								  break;						
							default:
								   MACRO_qyAssert(  0,  _T(  "ERROR: unprocessed aplayType"  )  );							
								   break;					
					}
					//
					pPlayAudio->uiPlayType  =  0;  

					//
					PLAYER_ID  playerId;
					playerId.index_player  =  i;
					playerId.uiTranNo_player  =  pPlayer->playerId.uiTranNo_player;
					if  (  removeFromAecLayout(  pProcInfo,  playerId,  &pProcInfo->av.aecInfo.aecLayout  )  )  {
						showInfo_open0(  0,  0,  _T(  "chkPlayers error: removeFromAecLayout failed"  )  );
					}
				}
				
			}
			if  (  pPlayVideo->uiPlayType  )  {
				//
#if  0
				if  (  !pPlayVideo->bRunning  
					&&  dwTickCnt  -  pPlayVideo->dwLastTickCnt_startPlayer  >  500  //  线程没启动，或已停止					
						)
#endif 
				//	
				if  (  !bPlayerOk(pPlayer,mynull))
				{
					//			
					_sntprintf(tBuf,mycountof(tBuf),_T(  "chkPlayers: clean playVideo %I64u, %d, %d"  ),  pPlayer->idInfo_recorder.ui64Id,  pPlayer->audio.uiTranNo,  pPlayVideo->uiTranNo  );
					showInfo_open(0, 0, 0, tBuf);

					//  回收
					pPlayVideo->bQuit  =  TRUE;		//  注意：bQuit不能在mcThread_playX里赋值，只能在主线程里赋值
					switch  (  pPlayVideo->uiPlayType  )  {
							case  CONST_vPlayType_v:
								  myWaitForQThread_infinite(  (  QY_qThreadProcInfo_common  *  )pPlayVideo,  _T(  "chkPlayers"  )  );								  
								  break;
							default:
								   MACRO_qyAssert(  0,  _T(  "ERROR: unprocessed vplayType"  )  );							
								   break;					
					}
					//
					pPlayVideo->uiPlayType  =  0;
				}
				
			}
			//
			if  (  !pPlayAudio->uiPlayType  &&  !pPlayVideo->uiPlayType  )  {
				 pPlayer->idInfo_recorder.ui64Id  =  0;										//  reset
				 pPlayAudio->uiTranNo  =  0;
				 pPlayVideo->uiTranNo  =  0;
				 pPlayer->iTaskId  =  0;														//  2009/09/17

				 //
				 pPlayer->bNeedEnd1 = false;

				 //
				 memset(&pPlayer->status, 0, sizeof(pPlayer->status));

			}
		}										  

		//
		continue;

	}

	return  0;
}


//
//  2012/03/30
/*
comment:
player是用来管理播放音频和视频数据的对象，含音频部分audio和视频部分video 
这段函数用来在有了音视频数据然后准备启动一个player
1.先会收到一个applyForPlayer_qmc的消息，里面包含了播放的参数
*/
 int  doApplyForPlayer(  QY_MC  *  pQyMc,  HWND  hMainWnd,  MIS_MSGU  *  pMsg  )
 {
	 int						iErr	=	-1;
	 //QY_MC					*	pQyMc	=	QY_GET_GBUF(  );
	 int						i;

	 QY_SERVICEGUI_INFO		*	pSgi;		pSgi		=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if (!pSgi)  return  -1;// goto  errLabel;
	 MC_VAR_isCli				*	pProcInfo;	pProcInfo	=  (  MC_VAR_isCli  *  )pSgi->pVar;
	 if (!pProcInfo)  return  -1;// goto  errLabel;
	 DWORD						dwThreadDaemonId;

	 TCHAR						tHintBuf[256]; tHintBuf[0] = 0;// = _T("");

	 //
	 TCHAR  tBuf[128];
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doApplyForPlayer: get applyForPlayer_qmc msg: %I64u, %d %d"  ),  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id, pMsg->applyForPlayer_qmc.audio.uiTranNo,  pMsg->applyForPlayer_qmc.video.uiTranNo  );
	 showInfo_open0(  0,  0,  tBuf  );
	 
		//
#ifdef  __DEBUG__
	 //
	 if  (  !pMsg->applyForPlayer_qmc.video.vh.bih.biWidth  )  {
		 int  ii;
		 ii  =  0;
	 }
#endif

	 // comment: 消息applyForPlayer_qmc里包含idInfo_recorder. audio.uiTranNo,video.uiTranNo来唯一代表一个player.
	 if  (  !pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id  &&  !pMsg->applyForPlayer_qmc.audio.uiTranNo  &&  !pMsg->applyForPlayer_qmc.video.uiTranNo  )  {
		 safeTcsnCpy(  _T(  "idInfo and uiTranNo are 0"  ),  tHintBuf,  mycountof(  tHintBuf  )  );
		 goto  errLabel;
	 }

	 //  2012/05/07
 	 // comment: 这段gps处理暂时没用
//////////////////
	 if  (  pMsg->applyForPlayer_qmc.bGps  )  {
		 //
		 QY_PLAYER_gps		*	pPlayer_gps=nullptr;
		 for  (  i  =  0;  i  <  pProcInfo->gps.usCnt_players;  i  ++  )  {
			  pPlayer_gps  =  &pProcInfo->gps.pPlayers[i];
			  if  (  pPlayer_gps->idInfo.ui64Id  )  {
				  if  (  GetTickCount(  )  -  pPlayer_gps->dwTickCnt_lastRecvd  >  30  *  1000  )  {
					  pPlayer_gps->idInfo.ui64Id  =  0;
					  pPlayer_gps->iTaskId  =  0;
				  }
			  }
			  if  (  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id  ==  pPlayer_gps->idInfo.ui64Id
				  &&  pMsg->applyForPlayer_qmc.iTaskId  ==  pPlayer_gps->iTaskId  )
			  {
				  break;
			  }
		 }
		 if  (  i  ==  pProcInfo->gps.usCnt_players  )  {
			 //  try to find an unused player
			 for  (  i  =  0;  i  <  pProcInfo->gps.usCnt_players;  i  ++  )  {
				  pPlayer_gps  =  &pProcInfo->gps.pPlayers[i];
				  if  (  !pPlayer_gps->idInfo.ui64Id
					  &&  !pPlayer_gps->iTaskId  )
				  {
					  break;
				  }
			 }
			 if  (  i  ==  pProcInfo->gps.usCnt_players  )  {
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "too many gps players"  )  );
				 goto  errLabel;
			 }
			 pPlayer_gps->idInfo.ui64Id  =  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id;
			 pPlayer_gps->iTaskId  =  pMsg->applyForPlayer_qmc.iTaskId;
			 pPlayer_gps->dwTickCnt_lastRecvd  =  GetTickCount(  );
		 }

		 //
		 iErr  =  0;  goto  errLabel;
	 }
	 ////////////////////

	 //
	 QY_PLAYER* pPlayer;pPlayer = nullptr;
	 PLAY_AUDIO_procInfo* pPlayAudio; pPlayAudio = nullptr;
	 PLAY_VIDEO_procInfo* pPlayVideo; pPlayVideo = nullptr;

	 //
	 //  comment: 这段是判断哪个player是退出了。如果退出就回收player		 
	 chkPlayers(  pProcInfo  );

	 //  comment: player是一个数组,在pProcInfo->av.pPlayers[]. pProcInfo是一个全局的结构
	 //
	 for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
		 pPlayer  =  &pProcInfo->av.pPlayers[i];
		 pPlayAudio  =  &pProcInfo->av.pPlayers[i].audio;
		 pPlayVideo  =  &pProcInfo->av.pPlayers[i].video;
		 //
		//
		//DWORD  dwTickCnt  =  GetTickCount(  );

		//
		if (pPlayer->bNeedEnd1)  continue;

		 //
		 if  (  pMsg->applyForPlayer_qmc.iTaskId  ==  pPlayer->iTaskId
			 &&  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id  ==  pPlayer->idInfo_recorder.ui64Id  
			 &&  pMsg->applyForPlayer_qmc.audio.uiTranNo  ==  pPlayAudio->uiTranNo
			 &&  pMsg->applyForPlayer_qmc.video.uiTranNo  ==  pPlayVideo->uiTranNo  )  												
		 {									
			 break;
		 }
	 }
	 if  (  i  ==  pProcInfo->av.usCnt_players  )  {

		 //
		 int iStart = 1;// 0;	// 忽略0,方便清空时该值为无效

		 //  try to find an unused player
		 for  (  i  =  iStart;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
			 pPlayer  =  &pProcInfo->av.pPlayers[i];
			 pPlayAudio  =  &pProcInfo->av.pPlayers[i].audio;
			 pPlayVideo  =  &pProcInfo->av.pPlayers[i].video;
			 if  (  !pPlayer->idInfo_recorder.ui64Id
				 &&  !pPlayAudio->uiTranNo
				 &&  !pPlayVideo->uiTranNo
				 &&  !pPlayer->bNeedEnd1
				 )  
			 {
				 break;
			 }
		 }
		 if  (  i  ==  pProcInfo->av.usCnt_players  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "too many players"  )  );
			 goto  errLabel;
		 }

		 pPlayer->idInfo_recorder.ui64Id  =  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id;
		 //
		 pPlayAudio->uiTranNo  =  pMsg->applyForPlayer_qmc.audio.uiTranNo;
		 memcpy(  &pPlayAudio->ah,  &pMsg->applyForPlayer_qmc.audio.ah,  sizeof(  pPlayAudio->ah  )  );
		 //  2009/06/14
		 memcpy(  &pPlayAudio->playCfg,  &pMsg->applyForPlayer_qmc.audio.playCfg,  sizeof(  pPlayAudio->playCfg  )  );
		 //
		 pPlayVideo->uiTranNo  =  pMsg->applyForPlayer_qmc.video.uiTranNo;
		 memcpy(  &pPlayVideo->vh,  &pMsg->applyForPlayer_qmc.video.vh,  sizeof(  pPlayVideo->vh  )  );
		 //
		 pPlayVideo->usFps  =  pMsg->applyForPlayer_qmc.video.usFps;	//  2015/0220
		 //
		 pPlayer->iTaskId  =  pMsg->applyForPlayer_qmc.iTaskId;			//  2009/09/17

		 //  2016/02/18
		 pPlayer->playerId.uiTranNo_player  =  getuiNextTranNo(  0,  0,  &pQyMc->globals.lTranNo_player  );

		 //
		 memset(&pPlayer->status, 0, sizeof(pPlayer->status));
	 }
	 //  2009/02/09

	 //  2014/1210
	 DWORD  dwTickCnt;dwTickCnt = myGetTickCount(mynull);
	 int min_intervalInMs_toApply; min_intervalInMs_toApply = 200;
	 //
	 if (pQyMc->appParams.bConfServer) {
		 min_intervalInMs_toApply = 2000;
	 }
	 //
	 if  (  dwTickCnt  -  pPlayer->dwLastTickCnt_doApplyForPlayer  <  min_intervalInMs_toApply  )  {

		 //
		 safeTcsnCpy(  _T(  " too quickly, skipped"  ),  tHintBuf,  mycountof(  tHintBuf  )  );

		 //
		 #ifdef  __DEBUG__
		 if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
			 traceLog((TCHAR*)_T("doApplyForPlay failed, too quickly"));
		 }
		 #endif
		 goto  errLabel;
	 }
	 pPlayer->dwLastTickCnt_doApplyForPlayer  =  dwTickCnt;

	 //
	 
	 if  (  pPlayAudio->uiTranNo  
		 &&  !pPlayAudio->uiPlayType  )  
	 {

		 //  2013/05/24
		 pPlayAudio->playbackDevDesc[0]  =  0;

		 //  2017/02/16
		 unsigned  int  uiPlayType  =  pQyMc->uiAPlayType;
		 
		 //
		 if  (  pPlayAudio->ah.wfx.nSamplesPerSec  ==  16000
			 &&  pPlayAudio->ah.wfx.nChannels  ==  1
			 &&  pPlayAudio->ah.wfx.wBitsPerSample  ==  16  )
		 {
			 uiPlayType  =  pQyMc->uiAPlayType_16kMono16;//CONST_aPlayType_webRtc;
		 }

		 //  2017/09/24
		 if (pMsg->applyForPlayer_qmc.bMix) {
			 uiPlayType = CONST_aPlayType_dSound;
		 }

		 //
#ifdef  __DEBUG__

#if  10
		 if  (  0  )  {
			 uiPlayType  =  CONST_aPlayType_dSound;
			 //
			 showInfo_open0(  0,  _T(  "doApplyForPlayer"  ),  _T(  "use dSound to playAudio"  )  );
		 }
#endif

#endif

		 //
		 pPlayAudio->uiPlayType  =  uiPlayType;
		 pPlayAudio->dwLastTickCnt_startPlayer  =  dwTickCnt;
		 pPlayAudio->bQuit  =  FALSE;
		 pPlayAudio->bRunning  =  FALSE;

		 //
		 if  (  uiPlayType  ==  CONST_aPlayType_webRtc  )  {
			 //
			 showInfo_open0(  0,  _T(  "doApplyForPlayer"  ),  _T(  "before startPlayAudio_webRtc"  )  );
			 //
			 startPlayAudio_webRtc(  pPlayer  );
			 //
			 showInfo_open0(  0,  _T(  "doApplyForPlayer"  ),  _T(  "after startPlayAudio_webRtc"  )  );
			 //
			 }
		 else  if  (  uiPlayType  ==  CONST_aPlayType_dSound  )  //  2017/02/16
		 {
			 //
			 exitDSoundToPlayIfNoPlayer(  pProcInfo  );

			 //
			 LPGUID  lpGuid  =  NULL;
			 
			 //  还要检查是否是会议里的player. 对于不是会议的播放,采用系统缺省设备.
			 OLD_audioDevice	audioDev;
			 if  (  bTaskId_conference(  pPlayer->iTaskId  )  )  {
				 if  (  !getDefaultPlaybackDevice(  &audioDev  )  )  {				 
					 lpGuid  =  &audioDev.guid_audio;
					 safeTcsnCpy(  audioDev.names_audio,  pPlayAudio->playbackDevDesc,  mycountof(  pPlayAudio->playbackDevDesc  )  );
				 }
			 }

			 //
			 if  (  pProcInfo->pPlayDev->initDSoundToPlay(  (  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx,  lpGuid,  hMainWnd,  0  )  )  {
				 //
				 showInfo_open(0, 0, 0, _T("doApplyForPlayer: initDSoundToPlay failed."));

				 //
				 //  goto  errLabel;
			 }
			 else  {

				 //
				 #ifdef  __DEBUG__
						 traceLogA(  (char*)  "CMainFrame: start audio player: %I64u,%d",  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id,  pMsg->applyForPlayer_qmc.audio.uiTranNo  );
				 #endif
				 //if  (  startQThread(  mcThreadProc_playAudio,  pProcInfo,  NULL,  (  QY_qThreadProcInfo_common  *  )pPlayAudio  )  )  goto  errLabel;
						 if( startPlayAudio_dSound(  pPlayer  )  )  goto  errLabel;
			 }
		 }
		 else  {	//  use wave api. 2010/05/03


#if  0

					#include	"unDeclareDebugNew.h"
					void  *  pThreadClass  =  new  CQyPlaySound();
					#include	"declareDebugNew.h"
					if  (  startQThread(  NULL,  0,  pThreadClass,  (  QY_qThreadProcInfo_common  * )pPlayAudio  )  )  goto  errLabel;
#endif 
					//
					showInfo_open(0, 0, 0, _T("doApplyForPlayer: a.uiPlayType err"));
					goto  errLabel;
		 }

		 //
		 if (!pMsg->applyForPlayer_qmc.bMix) {
			 //
			 PLAYER_ID  playerId;
			 playerId.index_player = i;
			 playerId.uiTranNo_player = pPlayer->playerId.uiTranNo_player;
			 if (addToAecLayout(pProcInfo, playerId, &pProcInfo->av.aecInfo.aecLayout)) {
				 showInfo_open0(0, 0, _T("doApplyForPlayer faile,d addToAecLayout failed"));
				 goto  errLabel;
			 }
		 }

	 }

	 //
#if 1
	 showInfo_open0(0, 0, _T("l703.doApplyForPlayer"));
#endif

	 //
	 if  (  pPlayVideo->uiTranNo
		 &&  !pPlayVideo->uiPlayType  )  
	 {
		 unsigned  int  uiPlayType  =  CONST_vPlayType_v;

		 //
		 pPlayVideo->uiPlayType  =  uiPlayType;
		 pPlayVideo->dwLastTickCnt_startPlayer  =  dwTickCnt;
		 pPlayVideo->bQuit  =  FALSE;
		 pPlayVideo->bRunning  =  FALSE;

		 //
		 TCHAR  tBuf[128];
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "CMainFrame: start video player: %I64u,%d"  ),  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id,  pMsg->applyForPlayer_qmc.video.uiTranNo  );
		 showInfo_open0(  0,  0,  tBuf  );

		 //
		 pPlayVideo->hThread  =  CreateThread(  NULL,  0,  mcThreadProc_playVideo,  pProcInfo,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
		 if  (  !pPlayVideo->hThread  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "applyForPlayer failed. CreateThread video failed"  )  );
			 goto  errLabel;
		 }
		 pPlayVideo->dwThreadId  =  dwThreadDaemonId;
		 if  (  ResumeThread(  pPlayVideo->hThread  )  ==  -1  )  goto  errLabel;
	 }


	 iErr  =  0;

errLabel:

	 //  if  (  iErr  )  
	 {
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "applyForPlayer %I64u,%d,%d leave, %s. %s"  ),  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id,  pMsg->applyForPlayer_qmc.audio.uiTranNo,  pMsg->applyForPlayer_qmc.video.uiTranNo,  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  ),  tHintBuf  );
	 }

	 //
	 int  nThreads_player   =  0;
	 for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
		  pPlayer  =  &pProcInfo->av.pPlayers[i];
		  if  (  pPlayer->audio.uiPlayType  )  nThreads_player  ++  ;
		  if  (  pPlayer->video.uiPlayType  )  nThreads_player  ++  ;	  
	 }
	 if  (  bQThreadExists(  pProcInfo->av.localAv.player.audio  )  )  nThreads_player  ++  ;
	 if  (  bQThreadExists(  pProcInfo->av.localAv.player.video  )  )  nThreads_player  ++  ;
	 if  (  pProcInfo->status.nThreads_player  !=  nThreads_player  )  pProcInfo->status.nThreads_player  =  nThreads_player; 
	

	return  iErr;
									 
}

