

#include	"stdafx.h"
 
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

#include	"qmcPlayVideo.h"
#include	"qyTick.h"

#include	"isCliD3dPublic.h"
#include	"imgProcessPublic.h"

#include	"qmcCommFunc_isCli.h"
#include	"imgFunc_open.h"
#include <dynFuncs.h>


 //  2012/02/24
 int  getSampleTimeInMs_needed(  MC_VAR_isCli  *  pProcInfo,  int  uiSampleTimeInMs_audio,  unsigned  int  dwTickCnt_audio_syncAv,  int  uiSampleTimeInMs_lastVideo,  unsigned  int  dwTickCnt_lastVideo_internal,  unsigned  int  dwTickCnt_now_syncAv,  unsigned  int  dwTickCnt_now_internal,  int  uiSampleTimeInMs_toPlay,  DWORD  *  pdwToInMs_toPlay  )
{
	int		iErr							=	-1;
	int		uiSampleTimeInMs_now			=	0;
	int		nWaitInMs						=	0;
	int		nWaitInMs_internal				=	0;
	//  int		dwTickCnt_toPlay_internal		=	0;
	DWORD	dwToInMs_toPlay					=	0;

	if  (  dwTickCnt_now_syncAv  >  dwTickCnt_audio_syncAv  +  10000  )  {		//  2009/05/27
		#ifdef  __DEBUG__
				//  traceLogA(  (char*)  "getSampleTimeInMs_needed: audio is lost.dwTickCnt_now %d  -  dwTickCnt_audio %d is %d",  dwTickCnt_now,  dwTickCnt_audio,  dwTickCnt_now  -  dwTickCnt_audio  );
		#endif
		nWaitInMs  =  -1;
		}					
	else  {
		  uiSampleTimeInMs_now  =  uiSampleTimeInMs_audio  +  dwTickCnt_now_syncAv  -  dwTickCnt_audio_syncAv;
		  if  (  uiSampleTimeInMs_toPlay  <=  uiSampleTimeInMs_now  )  {
			  nWaitInMs  =  0;
			  }
		  else  {
			    nWaitInMs  =  uiSampleTimeInMs_toPlay  -  uiSampleTimeInMs_now;
		  }
	}	

	//
	uiSampleTimeInMs_now  =  uiSampleTimeInMs_lastVideo  +  dwTickCnt_now_internal  -  dwTickCnt_lastVideo_internal;
	nWaitInMs_internal  =  uiSampleTimeInMs_toPlay  -  uiSampleTimeInMs_now;
	if  (  nWaitInMs_internal  <  0  )  nWaitInMs_internal  =  0;

	if  (  nWaitInMs  <  0  )  {
		//  
		dwToInMs_toPlay  =  nWaitInMs_internal;
		}
	else  {
		  //  
		  float  fa  =  0.4;
		  dwToInMs_toPlay  =  nWaitInMs  *  fa  +  nWaitInMs_internal  *  (  1  -  fa  );
	}


	//  2014/06/24	
	if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPreDrawStatus  )  {	
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  "getSTInMs_needed:"  ),  _T(  ""  ),  _T(  "st_a %dms, tc_a %dms, st_v %dms, to_toPlay_i %dms, now_i %dms, nWait_a %dms, nWait_i %dms."  ),  uiSampleTimeInMs_audio,  dwTickCnt_audio_syncAv,  uiSampleTimeInMs_toPlay,  dwToInMs_toPlay,  dwTickCnt_now_internal,  nWaitInMs,  nWaitInMs_internal  );
	}


	//
	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
		
		//  restricted.
		//if  (  dwTickCnt_toPlay_internal  >  dwTickCnt_now_internal  +  10000  )  
		if  (  dwToInMs_toPlay  >  10000  )  {
			#ifdef  __DEBUG__
					traceLogA(  (char*)  "getSampleTimeInMs_needed: dwToInMs %d. too long. uiSampleTimeInMs_toPlay %d, thrown.",  dwToInMs_toPlay,  uiSampleTimeInMs_toPlay  );
			#endif
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "getSTInMs_needed: dwToInMs %d, too long. ST_toPlay %d, ST_audio %d."  ),  dwToInMs_toPlay,  uiSampleTimeInMs_toPlay,  uiSampleTimeInMs_audio  );

			//  dwTickCnt_toPlay_internal  =  dwTickCnt_now_internal;
			dwToInMs_toPlay  =  0;
		}

		//  *pTickCnt_toPlay_internal  =  dwTickCnt_toPlay_internal;
		*pdwToInMs_toPlay  =  dwToInMs_toPlay;
	}
	return  iErr;
 }


#if 0
 BOOL  tmpHandler_bOldVideo(  void  *  p0,  QY_PLAYER  *  pPlayer,  myDRAW_VIDEO_DATA  *  pPkt  )
{
	BOOL					bRet		=	FALSE;
	//  p0

	//
	showInfo_open0(0, 0, _T("tmpHandler_bOldVideo called"));

	//
	if  (  pPlayer->uiSampleTimeInMs_start  )  {
		if  (  pPkt->head.uiSampleTimeInMs  <  pPlayer->uiSampleTimeInMs_start  )  {

			traceLogA(  (char*)  "tmpHandler_bOldVideo: one pkt matched. < start"  );
			qyShowInfo1(  CONST_qyShowType_detail,  0,(char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHandler_bOldVideo: pkt.iSampleTimeInMs %d < start %d. matched"  ),  pPkt->head.uiSampleTimeInMs,  pPlayer->uiSampleTimeInMs_start  );

			bRet  =  TRUE;
		}
	}
	if  (  pPlayer->video.m_var.uiSampleTimeInMs_newRecvd  <  pPkt->head.uiSampleTimeInMs									 
		||  pPlayer->video.m_var.uiSampleTimeInMs_newRecvd  >  pPkt->head.uiSampleTimeInMs  +  10000  )
	{
		traceLogA(  (char*)  "tmpHandler_bOldVideo: one pkt matched."  );
		qyShowInfo1(  CONST_qyShowType_detail,  0,(char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHandler_bOldVideo: pkt.iSampleTimeInMs %d. newRecvd %d. matched"  ),  pPkt->head.uiSampleTimeInMs,  pPlayer->video.m_var.uiSampleTimeInMs_newRecvd  );

		bRet  =  TRUE;
	}

	return  bRet;
}
#endif


//
int  accurateSleep(  DWORD  dwMs,  LPCTSTR  hint  )
{
	if  (  !dwMs  )  return  0;

	if  (  !hint  )  hint  =  _T(  ""  );

	//
	timeBeginPeriod(  1  );
	Sleep(  dwMs  );
	timeEndPeriod(  1  );

	//
#ifdef  __DEBUG__
		#if  0
			 TCHAR  tBuf[128];
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "accurateSleep  %dms %s"  ),  dwMs,  hint  );
			 showInfo_open0(  0,  0,  tBuf  );
		#endif
#endif


	return  0;
}



//  2015/09/05
#define		CONST_nInMs_toGetFps				1000	//  2015/09/05	//  1000

//
#define	MIN_fps_pts								5		//	2015/09/10	//  7		//  2015/06/20	//  10	
#define	MIN_realFps_pts							5		//  2015/09/10	//  7		//  2015/06/20	//  10	

//
int  player_get_fps(  QY_MESSENGER_ID  *  pIdInfo,  unsigned  short  usFps_expected,  unsigned  int  uiSampleTimeInMs,  TMP_fps_info  *  pFpsInfo,  TCHAR  *  pHint  )
{
	if  (  !pIdInfo  )  return  -1;

	if  (  !pHint  )  pHint  =  (TCHAR  * )_T(  ""  );

	pFpsInfo->iCount ++;

	DWORD  curTimeInMs  =  myGetTickCount(  NULL  );  //
	int  iDiffInMs  =  curTimeInMs  -  pFpsInfo->lastTimeInMs;	
	//
	if  (  iDiffInMs  >  CONST_nInMs_toGetFps  )
	{
		int  iDiffInMs_st  =  uiSampleTimeInMs  -  pFpsInfo->uiSampleTimeInMs_startToCnt;
		if  (  iDiffInMs_st  )  {
			pFpsInfo->fps_real  =  (  float  )pFpsInfo->iCount  *  1000  /  (  iDiffInMs_st  );
			}
		else  {
			  pFpsInfo->fps_real  =  (  float  )pFpsInfo->iCount  *  1000  /  (  iDiffInMs  );
		}
			
		//
		if  (  (int)pFpsInfo->fps_real  )  {
			pFpsInfo->avgTimePerFrameInMs_real1  =  (  1000.  )  /  pFpsInfo->fps_real;
		}
		//
		if  (  pFpsInfo->avgTimePerFrameInMs_real1  >  200  )  pFpsInfo->avgTimePerFrameInMs_real1  =  200;
		else  if  (  pFpsInfo->avgTimePerFrameInMs_real1  <  5  )  pFpsInfo->avgTimePerFrameInMs_real1  =  5;
		//
		//
		if  (  usFps_expected  >  MIN_fps_pts  )  {
			pFpsInfo->avgTimePerFrameInMs  =  1000  /  usFps_expected;
		}
		else  pFpsInfo->avgTimePerFrameInMs  =  pFpsInfo->avgTimePerFrameInMs_real1;

		
		//
#ifdef  __DEBUG__
		//traceLog((TCHAR*)  _T(  "player_get_fps: %f. avgTimePerFrameInMs %dms"  ),  pFpsInfo->fps,  pFpsInfo->avgTimePerFrameInMs   );
#endif
		MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
		if  (  pProcInfo->cfg.debugStatusInfo.ucbShowToDrawStatus  )  {	
			TCHAR  tBuf[256];
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "player_get_fps: %I64u, real %f, expected_avg %dms. real_avg %dms. cnt %d, iDiff_calc %dms, iDiff_st %dms, %s"  ),  pIdInfo->ui64Id,  pFpsInfo->fps_real,  pFpsInfo->avgTimePerFrameInMs,  pFpsInfo->avgTimePerFrameInMs_real1,  
				pFpsInfo->iCount,
				iDiffInMs,  iDiffInMs_st,
				pHint  );								   
			showInfo_open0(  0,  0,  tBuf  );
		}							   

		//
		pFpsInfo->lastTimeInMs  =  curTimeInMs;
		pFpsInfo->iCount  =  0;
		pFpsInfo->uiSampleTimeInMs_startToCnt  =  uiSampleTimeInMs;

	}

	return  0;			
}



//
extern "C" DWORD WINAPI mcThreadProc_doPre_toPlayVideo(LPVOID lpParameter);






//
#if  0
 extern "C" DWORD WINAPI iimcThreadProc_playVideo( LPVOID lpParameter )
{
	 MC_VAR_isCli				*	pProcInfo					=	(  MC_VAR_isCli  *  )lpParameter;
	 if (  !pProcInfo  )  return  -1;
	 QY_MC						*	pQyMc						=	pProcInfo->pQyMc;
	 if  (  !pQyMc  )  return  -1;

	 //
	 DYN_LIB_DX					*	pDynLib						=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;

	 QY_PLAYER					*	pPlayer						=	NULL;
	 PLAY_VIDEO_procInfo		*	pPlay						=	NULL;

	 //
	 PLAYER_ID						playerId;
	 memset(  &playerId,  0,  sizeof(  playerId  )  );

	 //
	 DWORD							dwThreadId					=	GetCurrentThreadId(  );

	 //
	 CQyTick						tickObj;
	 //DWORD							dwTgt_lastData				=	M_GetTgt_video(  tickObj  );;						// 

	 //
	 myDRAW_VIDEO_DATA				pkts[CONST_pkts_playVideo];
	 unsigned  int					uiLens[CONST_pkts_playVideo];		//  要增加一个qGetMsgs，将pPkts和pktLens作为参数输入。2011/07/15
	 int							nLens = mycountof(uiLens);		//  一次最多处理的包数。

	 //int							len_pkts;
	 int							nPkts;

	 MIS_CNT					*	pMisCnt						=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;	 	 

	 //  2011/12/05
	 CQyMalloc	mallocObj_tmpRgbBuf;
	 char  *  tmpRgbBuf  =  NULL;

	 //
	 Ctx_fillData_d3d  ctx_fillData_d3d;
	 memset(&ctx_fillData_d3d, 0, sizeof(ctx_fillData_d3d));

	 //
	 //  #define		DEFAULT_dwToInMs_playVideo		200
	 //#define		DEFAULT_dwToInMs_playVideo			210
	 //#define		DEFAULT_dwToInMs_playVideo			100
	 #define		DEFAULT_dwToInMs_playVideo			16
	 //
	 #define		CONST_video_skippedInterval			0	//  
	 #define		CONST_video_ahead					0	//  			//  提前量

	 DWORD							dwToInMs					=	DEFAULT_dwToInMs_playVideo;

	 DWORD							dwTickCnt_internal;
	 DWORD							dwTgt_internal_toPlay;
	 DWORD							dwTickCnt_syncAv_now;

	 BOOL							bPktRedirected				=	FALSE;

	 unsigned  int					uiSampleTimeInMs_audio		=	0;			   
	 DWORD							dwTickCnt_syncAv_audio		=	0;

	 //
	 //  2015/03/12. 本地视频没有做pts,是错的。不过，现在先暂时伪造一个，以便用pts来改善播放效果
	 unsigned  int					tmp_localV_pts_faked  =  0;
	 //
	 TCHAR  tBuf[128];

	 //
	 int							totalPkts = 0;
	 int							totalPkts_lastOk = 0;
	 int							nPkts_left = 0;
	 bool							bExists_skipped = false;

	 //
	 {
		 int  i;
	 for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
		  if  (  dwThreadId  ==  pProcInfo->av.pPlayers[i].video.dwThreadId  )  break;		   
	 }
	 if  (  i  ==  pProcInfo->av.usCnt_players  )  {
		 return  -1;
	 }
	 pPlayer  =  &pProcInfo->av.pPlayers[i];
	 pPlay  =  &pProcInfo->av.pPlayers[i].video;
	 
	 //  2016/02/18
	 playerId.index_player  =  i;
	 playerId.uiTranNo_player  =  pPlayer->playerId.uiTranNo_player;
	 }
	 
	 //
#ifdef  __DEBUG__
	 traceLogA(  (char*)  "playVideo %S enters",  pPlay->q2.cfg.name  );
#endif
	 	 	
	 //  2014/07/03
	 //  TMP_fps_info					fpsInfo  =  {0,};	
	 TMP_fps_info			&		fpsInfo  =  pPlay->m_var.status.fpsInfo;
	 memset(  &fpsInfo,  0,  sizeof(  fpsInfo  )  );
	 //  2015/09/13
	 //BOOL  &  bNeedAdjust  =  pPlay->m_var.lowLatency.bNeedAdjust;

	 //
	 switch  (  pPlayer->video.vh.bih.biCompression  )  {
			 case  BI_RGB:
			 case  CONST_fourcc_YV12:
			 case  CONST_fourcc_I420:	//  2014/07/21
			 case  CONST_fourcc_NV12:
				   break;
			 default:
					#ifdef  __DEBUG__
							char  buf[128];
							traceLogA(  (char*)  "playVideo: %s failed. only support play rgb or yv12. ",  iFourcc2Str(  pPlayer->video.vh.bih.biCompression,  buf,  mycountof(  buf  )  )  );  
				    #endif
					goto  errLabel;
	 }

	 BITMAPINFOHEADER	bih;
	 makeBmpInfoHeader_rgb(  24,  pPlayer->video.vh.bih.biWidth,  pPlayer->video.vh.bih.biHeight,  &bih  );
	 if  (  memcmp(  &bih,  &pPlayer->video.vh.bih,  sizeof(  bih  )  )  )  memcpy(  &pPlayer->video.vh.bih,  &bih,  sizeof(  pPlayer->video.vh.bih  )  );

	 //  2011/12/05
	 tmpRgbBuf  =  mallocObj_tmpRgbBuf.mallocf(  bih.biSizeImage  );
	 if  (  !tmpRgbBuf  )  {
		 TCHAR  tBuf[128];
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "playVideo failed: tmpRgbBuf.malloc returns null, bih.biSizeImage %d"  ),  bih.biSizeImage  );
		 showInfo_open0(  0,  0,  tBuf  );
		 goto  errLabel;
	 }


	 // Create the events. We make an extra one for later use 
	 // by the output buffer.
	 /*
	 for  (  i  =  0;  i  <  mycountof(  pPlay->hEvents  );  i  ++  )  {
		  pPlay->hEvents[i] = CreateEvent( NULL, FALSE, FALSE, NULL );
		  if ( NULL == pPlay->hEvents[i] ) goto  errLabel;
	 }
	 */

	 ///////
	 pPlay->doPre_toPlayVideo.bQuit = false;
	 //
	 DWORD  dwThreadDaemonId;
	 pPlay->doPre_toPlayVideo.hThread = CreateThread(NULL, 0, mcThreadProc_doPre_toPlayVideo, pPlayer, CREATE_SUSPENDED, &dwThreadDaemonId);
	 if (!pPlay->doPre_toPlayVideo.hThread)  goto  errLabel;
	 pPlay->doPre_toPlayVideo.dwThreadId = dwThreadDaemonId;
	 if (ResumeThread(pPlay->doPre_toPlayVideo.hThread) == -1)  goto  errLabel;




	 //pPlay->bQuit  =  FALSE;
	 pPlay->dwTickCnt_start  =  myGetTickCount(nullptr  );	//  M_GetTickCount_video(  tickObj  );		//  2010/05/04
	 pPlay->bRunning  =  TRUE;
	 pPlayer->uiSampleTimeInMs_start  =  0;
	 memset(  &pPlay->m_var,  0,  sizeof(  pPlay->m_var  )  );

	 //
	 pPlay->m_var.dwTickCnt_lastData = myGetTickCount(0);


	 //
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u starts"  ),  pPlay->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id  );

	 //  2013/10/06
#if  0
	 int  sizeImage_rgb32  =  M_sizeImage(  32,  pPlay->vh.bih.biWidth,  pPlay->vh.bih.biHeight  );
	 BITMAPINFOHEADER	bih32;
	 makeBmpInfoHeader_rgb(  32,  pPlay->vh.bih.biWidth,  pPlay->vh.bih.biHeight,  &bih32  );
#endif

	 /////////////////
	 emptyQ2(  &pPlay->q2  );

	 //  2015/09/14
	 //pPlay->m_var.lowLatency.mql.max_ql_ok_avg_100  =  pPlayer->video.usFps  /  2  *  100;

	 //
	 for  (  ;  bPlayerOk(pPlayer,0); ) {
		  
		 //
		 if (pPlayer->bNeedEnd1) {
			 //
			 _sntprintf(tBuf, mycountof(tBuf), _T("player[%d].bNeedEnd true, will quit. l414"), playerId.index_player);
			 showInfo_open0(0, 0, tBuf);
			 //
			 break;
		 }

		 //
#if  0	//  2015/09/12
		  if  (  !dwToInMs  ||  dwToInMs  >  DEFAULT_dwToInMs_playVideo  )  {			  
			  traceLogA(  (char*)  (  "Warning: mcThreadProc_playVideo: dwToInMs %d"  ),  dwToInMs  );
			  #if  0
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: mcThreadProc_playVideo: dwToInMs %d"  ),  dwToInMs  );
			  #endif
			  dwToInMs  =  DEFAULT_dwToInMs_playVideo;
		  }
#endif
		  //  2015/09/12
		  dwToInMs  =  DEFAULT_dwToInMs_playVideo;
		  int  iFps  =  (int)fpsInfo.fps_real;
#if 0
		  if (iFps > 15) 
		  {
			  //dwToInMs = 33;
			  dwToInMs = 16;
		  }
#endif
		  dwToInMs = 16;

		  //
		 
		  //
#ifdef  __DEBUG__
		  if (1) {
			  if (!pQyMc->appParams.bMcu) {
				  if (pPlayer->idInfo_recorder.ui64Id) {
					  _sntprintf(tBuf, mycountof(tBuf), _T("playVideo: %I64u, before waitForObject. "), pPlayer->idInfo_recorder.ui64Id);
					  if (pPlay->m_var.lowLatency.bNeedAdjust3) {
					  }
					  showInfo_open0(0, 0, tBuf);
				  }
			  }
		  }
#endif

		  //
		  pPlay->m_var.lowLatency.stat_noMsgAndWait.nTimes++;

		  
		  //
		  //  2012/03/01, 设置此标志位,使有数据包来时,可以触发
		  pPlay->m_var.status.bNoMsgAndWait  =  TRUE;
		  //
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(
			  				 pPlay->q2.cfg.usCnt_hEvents,	//  mycountof(  pPlay->hEvents  ),				// Number of events.
							 pPlay->q2.hEvents,							// Location of handles.
                             FALSE,										// Wait for all?
                             dwToInMs,									// How long to wait?
                             0  );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  goto  errLabel;
		  //  2012/03/01
		  pPlay->m_var.status.bNoMsgAndWait  =  FALSE;
		  
		  
	      //
		  dwTickCnt_internal = myGetTickCount(0);// M_GetTgt_video(tickObj);
		  
		  //
#if  0
		  if  (  dwTgt_internal  -  dwTgt_lastData  >  (  DWORD  )(  pProcInfo->cfg.usTimeoutInMs_player_v  )  )  {
			  #ifdef  __DEBUG__
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "video data may not arrives, player exits. %I64u %d, timeout is %d"  ),  pPlayer->idInfo_recorder.ui64Id,  pPlayer->video.uiTranNo,  pProcInfo->cfg.usTimeoutInMs_player_v  );
					  traceLog(tBuf);
			  #endif
			  break;
		  }
#endif 

		  //
		  if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
			  dwEvt -= WAIT_OBJECT_0;
			  switch  (  dwEvt  )  {
					  case  0:
						     //  dwTickCnt_lastData  =  dwTickCnt;		//  audio data received
							 break;
					  case  1:
						       //  traceLogA(  (char*)  "playVideo: event 1."  );
							 if  (  0  )	//  2015/09/13
							 {
								   //  traceLogA(  (char*)  "playVideo: event 1... "  );
								   if  (  pPlay->m_var.uiSampleTimeInMs  )  {
									   if  (  pPlay->m_var.uiSampleTimeInMs_newRecvd  <  pPlay->m_var.uiSampleTimeInMs
										   ||  pPlay->m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  >  pPlay->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  +  1000  )
									   {
										   CQyQ2Help		q2Help;
										   //qRemoveMsg(  q2Help.getQ_toGetMsg(  &pPlay->q2,  _T(  "playVideo remove"  )), (PF_bCommonHandler)tmpHandler_bOldVideo, 0, pPlayer);
									   }
								   }

							 }
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
		  }


		  //
		  for (; bPlayerOk(pPlayer, 0); ) {
			  			  
			  //
			  if (pPlayer->bNeedEnd1) {
				  //
				  _sntprintf(tBuf, mycountof(tBuf), _T("player[%d].bNeedEnd true, will quit. l527"), playerId.index_player);
				  showInfo_open0(0, 0, tBuf);
				  //
				  break;
			   }


			   //  traceLogA(  (char*)  "playVideo: msg reaved"  );
#if 0
			   len_pkts  =  sizeof(  pkts  );  
			   {
				   CQyQ2Help	q2Help;
				   if  (  qGetMsg(  q2Help.getQ_toGetMsg(  &pPlay->q2,  _T(  "playVideo 2"  )), pkts, (unsigned  int*)&len_pkts)) {
					   dwToInMs  =  DEFAULT_dwToInMs_playVideo;
					   break;			   
				   }
			   }
#endif
			   //
			   nPkts = 0;
			   int i;
			   //
#ifdef  __DEBUG__
			   DWORD  dwTickCnt_beforeGetMsg = myGetTickCount(nullptr);
#endif

			   // 					  //  pktLen  =  uiBufSize;  
			   nLens = mycountof(uiLens);
			   //  2014/04/10
			   if (q2GetMsgPkg(&pPlay->q2, (void*)pkts, sizeof(pkts), (unsigned  int*)uiLens, (unsigned  int*)&nLens, _T("playVideo"))) {
				   break;
			   }

			   for (i = 0; i < nLens; i++) {
				   nPkts += uiLens[i] / sizeof(pkts[0]);
				   if (uiLens[i] % sizeof(pkts[0])) {
#ifdef  __DEBUG__
					   traceLog((TCHAR*)_T("vpp: uiLen err"));
					   assert(0);
#endif
				   }
			   }

										//  注意：在上面qGetMsg和下面的attach之间，不要添加代码，否则，内存就失去管理了

			   #ifdef  __DEBUG__
			           //  traceLogA(  (char*)  "playVideo: pkt.SampleTime %d, pktLen %d",  pPkt->head.uiSampleTimeInMs,  pktLen  );			
			   #endif

			   {
				   CQyMalloc		mallocObj_tmpPkts[CONST_pkts_playVideo];
				 

				   BOOL  tmpbErr  =  FALSE;	//  注意：这里如果attach出错，要继续attach, 但是最后要continue. 以防止pPkts[i]没有机会释放内存
				   //
				   //nPkts  =  len_pkts  /  sizeof(  pkts[0]  );
				   for  (  int  i  =  0;  i  <  nPkts;  i  ++  )  {
					    myDRAW_VIDEO_DATA	*	pPkt  =  &pkts[i];
					    if  (  pPkt->memory.m_pBuf  )  {
							if  (  mallocObj_tmpPkts[i].attach(  &pPkt->memory  )  )  {
								#ifdef  __DEBUG__
										traceLogA(  (char*)  "mcThreadProc_playVideo: mallocObj.attach failed"  );
								#endif
								clean_myDRAW_VIDEO_DATA(  pPkt,  _T(  "playVideo"  )  );
								tmpbErr  =  TRUE;
								continue;
							}
						}
				   }
				   if  (  tmpbErr  )  continue;

#if 0
				   if  (  len_pkts  %  sizeof(  myDRAW_VIDEO_DATA  )  )  {
					   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playVideo err: len_pkts err"  )  );
					   #ifdef  __DEBUG__
							   assert(  0  );
					   #endif
					   continue;
					   //  应该只发个myDRAW_VIDEO_DATA过来
				   }
#endif

				   #ifdef  __DEBUG__
						   //
						   if  (  0  )  {
							   if (pPlayer->idInfo_recorder.ui64Id) {
								   DWORD  dwTickCnt_afterGetMsg = myGetTickCount(nullptr);
								   int iDiffInMs = dwTickCnt_afterGetMsg - dwTickCnt_beforeGetMsg;
								   _sntprintf(tBuf, mycountof(tBuf), _T("playVideo %I64u: get %d pkts. iDiffInMs %dms"), pPlayer->idInfo_recorder.ui64Id, nPkts, iDiffInMs);
								   showInfo_open0(0, 0, tBuf);
							   }
						   }
						   //
						   if  (  nPkts  !=  1  )  {
							   //traceLog((TCHAR*)  _T(  "playVideo: nPkts %d"  ),  nPkts  );
						   }
						   for  (  int  i  =  0;  i  <  nPkts;  i  ++  )  {
							    myDRAW_VIDEO_DATA  *  pPkt  =  &pkts[i];
								if  (  !pPkt->hWnd_task
									&&  !pPkt->idInfo_peer.ui64Id  )
								{
									traceLog((TCHAR*)  _T(  "playVideo: iIndex_player %d, nPkts %d, [%d].idInfo_peer is 0"  ),  playerId.index_player,  nPkts,  i  );
								}
						   }

						   //
						   M_pkts_showNo_playVideo(  pkts,  nPkts  );
				   #endif


				   //  
				   pPlayer->video.m_var.dwTickCnt_lastData  =  M_GetTgt_video(  tickObj  );		//  video data received

				   //
				   
				   //
				   for (int iIndex = 0; iIndex < nPkts; iIndex++) {
					   myDRAW_VIDEO_DATA* pPkt = &pkts[iIndex];
					   int						pktLen = sizeof(pkts[0]);

					   //  2015/03/12. 对本地视频，伪造一个pts. 等回头在包生成处产生pts才对
					   if (!pPlayer->idInfo_recorder.ui64Id) {
						   if (!pPkt->head.uiPts) {
							   pPkt->head.uiPts = tmp_localV_pts_faked;
							   tmp_localV_pts_faked++;
						   }
					   }

					   //
					   totalPkts++;

					   
						//  2015/10/04
						if (pPkt->usPktResType != CONST_pktResType_sharedTex) {
							//
							if (pPkt->head.uiLen < pPlay->vh.bih.biSizeImage) {
#ifdef  __DEBUG__
								traceLogA((char*)("playVideo err: pkt.head.uiLen %d <  sizeImage %d. skipped"), pPkt->head.uiLen, pPlay->vh.bih.biSizeImage);
#endif
								qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("playVideo err: pkt.head.uiLen %d <  sizeImage %d. skipped"), pPkt->head.uiLen, pPlay->vh.bih.biSizeImage);
								continue;
							}

							//
							Param_bPktSkipped  param = { 0 };
							param.last_mql = pPlay->m_var.lowLatency.mql.mql_3s.last_mql;
							param.mql_ok = pPlay->m_var.lowLatency.mql.mql_ok;
#ifdef  __DEBUG__
							//param.bDbg = true;
#endif
							//
							//
							int nQNodes = getQ2Nodes(&pPlayer->video.q2);
							//
							nPkts_left = nPkts - iIndex;
							//
							bool  b4k = is4k(pPlayer->video.vh.bih.biWidth, pPlayer->video.vh.bih.biHeight);
							unsigned  __int64 nFactor = 0;
							if (bPktSkipped(&param,  CONST_nWhere_playVideo, pPlayer->video.usFps, 0, nQNodes, totalPkts, nPkts_left,  b4k,  &totalPkts_lastOk,  &nFactor)) {
								//_sntprintf(tBuf, mycountof(tBuf), _T("playVideo %I64u: totalPkts %d, factor %I64u, n_left %d, skipped"), pPlayer->idInfo_recorder.ui64Id, totalPkts, nFactor, nPkts_left  +  nQNodes);
								_sntprintf(tBuf, mycountof(tBuf), _T("playVideo %I64u: totalPkts %d, fps %d, mql_last %d,mql_ok %d, n_left %d, skipped. l707"), pPlayer->idInfo_recorder.ui64Id, totalPkts, (int)pPlayer->video.usFps,  param.last_mql,param.mql_ok,nPkts_left + nQNodes);
								//showInfo_open0(0, 0, tBuf);
								if (param.bDbg) {
									showInfo_open(0, 0, 0, param.tBuf);
								}
								//
								doCalcMql(pProcInfo, pPkt->head.uiTranNo_openAvDev, pPkt, &pPlayer->idInfo_recorder, nPkts_left, &pPkt->idInfo_peer, pPkt->iTaskId, &playerId, _T("after bPktSkipped"));

								//
								bExists_skipped = true;

								//
								continue;
							}

							//
#ifdef  __DEBUG__
							if (0) {
								if (!pQyMc->appParams.bMcu) {
									if (pPlayer->idInfo_recorder.ui64Id) {
										//_sntprintf(tBuf, mycountof(tBuf), _T("playVideo %I64u: totalPkts %d, factor %I64u, n_left %d, ok"), pPlayer->idInfo_recorder.ui64Id, totalPkts, nFactor, nPkts_left  +  nQNodes);
										_sntprintf(tBuf, mycountof(tBuf), _T("playVideo %I64u: totalPkts %d, fps %d, mql_last %d,mql_ok %d, n_left %d, ok"), pPlayer->idInfo_recorder.ui64Id, totalPkts, (int)pPlayer->video.usFps, param.last_mql, param.mql_ok, nPkts_left + nQNodes);
										showInfo_open0(0, 0, tBuf);
										if (param.bDbg) {
											showInfo_open0(0, 0, param.tBuf);
										}
									}
								}
							}							
#endif

							//
							if (bExists_skipped) {
								bExists_skipped = false;
								//
								//pPlay->m_var.lowLatency.bNeedAdjust3 = true;
							}

						}

						//  
						if (!pPkt->bResizeToPlay) {
							if (pPkt->bih.biWidth != pPlay->vh.bih.biWidth
								|| pPkt->bih.biHeight != pPlay->vh.bih.biHeight
								|| !pPkt->bih.biSizeImage)
							{
#ifdef  __DEBUG__
								traceLog((TCHAR*)_T("playVideo err: pkt %d,%d !=  player %d,%d. skipped"), (int)pPkt->bih.biWidth, (int)pPkt->bih.biHeight, (int)pPlay->vh.bih.biWidth, (int)pPlay->vh.bih.biHeight);
#endif
								qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("playVideo err: pkt %d,%d !=  player %d,%d. skipped"), (int)pPkt->bih.biWidth, (int)pPkt->bih.biHeight, (int)pPlay->vh.bih.biWidth, (int)pPlay->vh.bih.biHeight);
								continue;
							}
						}


						//
						DWORD	dwTickCnt_beforeYv12 = myGetTickCount(mynull);
					   //
					   if  (  pPkt->usPktResType  !=  CONST_pktResType_sharedTex  )  {
						   if  (  pPkt->bih.biCompression  !=  BI_RGB  )  {
							   #if  0
									if  (  pPkt->bih.biCompression  !=  CONST_fourcc_YV12  )  {
	   								   #ifdef  __DEBUG__
										   traceLog((TCHAR*)  _T(  "playVideo err: pPkt->bih err"  )  );
									   #endif
									   continue;
								    }
							   #endif
							   if  (  pPkt->bih.biSizeImage  >  bih.biSizeImage  )  {
								   #ifdef  __DEBUG__
										   assert(  0  );
								   #endif
								   continue;
							   }
							   memcpy(  tmpRgbBuf,  pPkt->memory.m_pBuf,  pPkt->bih.biSizeImage  );					
							   //
							   switch  (  pPkt->bih.biCompression  )  {
									   case  CONST_fourcc_YV12:
										     pQyMc->yv12ToRgb24(  (  BYTE  *  )tmpRgbBuf,  (  BYTE  *  )pPkt->memory.m_pBuf,  pPkt->bih.biWidth,  pPkt->bih.biHeight,  0  );//pPlayer->video.ucbFlippedImg  );								 
											 break;
									   case  CONST_fourcc_I420:
										     i420ToRgb24(  (  BYTE  *  )tmpRgbBuf,  (  BYTE  *  )pPkt->memory.m_pBuf,  pPkt->bih.biWidth,  pPkt->bih.biHeight,  0  ); //pPlayer->video.ucbFlippedImg  );								 										
										     break;
									   case  CONST_fourcc_NV12:
											{
#if 0
										   static FILE* fp = null;
										   static int cnt = 0;
										   cnt++;
										   if (!fp) {
											   fp = fopen("c:\\codecSdk\\out\\kk.nv12", "wb");
										   }
										   if (fp) {
											   fwrite(tmpRgbBuf, pPkt->bih.biSizeImage, 1, fp);
										   }
										   if (cnt > 300) {
											   if (fp) {
												   fclose(fp);
												   fp = null;
											   }
										   }
#endif


										    
										   //
										   //NV12_TO_RGB24((unsigned  char*)tmpRgbBuf, (unsigned  char*)pPkt->memory.m_pBuf, pPkt->bih.biWidth, pPkt->bih.biHeight);
										   nv12ToRgb24((unsigned  char*)tmpRgbBuf, (unsigned  char*)pPkt->memory.m_pBuf, pPkt->bih.biWidth, pPkt->bih.biHeight,false);

											}
										     break;
									   default:
			   	   							   #ifdef  __DEBUG__
													   traceLog((TCHAR*)  _T(  "playVideo err: pPkt->bih err"  )  );
											   #endif
										       continue;
											   break;
							   }
							   //
							   memcpy(  &pPkt->bih,  &pPlay->vh.bih,  sizeof(  pPkt->bih  )  );
							   pPkt->uiSize_dec  =  pPlay->vh.bih.biSizeImage;

							   }
						   else  {
						   }
					   }

					   //
					   //
					   DWORD  dwTickCnt_afterYv12 = myGetTickCount(mynull);
					   int  iDiffInMs = dwTickCnt_afterYv12 - dwTickCnt_beforeYv12;
					   //_sntprintf(pPlay->m_var.lowLatency.tBuf, mycountof(pPlay->m_var.lowLatency.tBuf), _T("PlayVideo %I64u: It costs %dms to yv12"), pPlayer->idInfo_recorder.ui64Id,  iDiffInMs);
					   _sntprintf(pPlay->m_var.lowLatency.tBuf, mycountof(pPlay->m_var.lowLatency.tBuf), _T("%dms to yv12"), iDiffInMs);
#ifdef  __DEBUG__

					   //
					   if (pPkt->usPktResType == CONST_pktResType_sharedTex) {
						   int  ii = 0;
					   }
#endif
					   
					   //  2015/09/11
					   pPkt->debugInfo.dwTickCnt_playPkt_start  =  myGetTickCount( mynull );

					    //  __declspec(  dllexport  )  int  fillData_d3d(  BITMAPINFOHEADER  *  pBih,  BYTE  *  pData,  int  iIndex_player,  BOOL  *  pbFilled  )
					   memset(  &pPlay->m_var.status.fillD3d,  0,  sizeof(  pPlay->m_var.status.fillD3d  )  );
					   if  (  pPlay->m_var.status.ucSkipped_for_d3dData  )  {
						   pPlay->m_var.status.ucSkipped_for_d3dData  --  ;
						   //
						   pPlay->m_var.status.fillD3d.bNeedFill  =  FALSE;						   //
						   pPlay->m_var.status.fillD3d.bFilled_d3dData  =  FALSE;
						   }
					   else  {
						     pPlay->m_var.status.fillD3d.bNeedFill  =  TRUE;
							 //
							 if  (  dyn_fillData_d3d(  &ctx_fillData_d3d,  pPkt,  playerId.index_player,  &pPlay->m_var.status.fillD3d.param0,  &pPlay->m_var.status.fillD3d.bFilled_d3dData  )  )  {
								 pPlay->m_var.status.fillD3d.bFilled_d3dData  =  FALSE;					   
							 }
					   }

					   //
					   pPlay->m_var.lowLatency.nTimes_sleep  =  0;
					   
					   //
					   if  (  !pPkt->head.uiSampleTimeInMs  )  {
						   //  2012/02/06
						   dwToInMs  =  0;		//  2013/09/09
						   //
						   pPlay->m_var.lowLatency.dwToInMs_toPostDraw  =  dwToInMs;	//  2013/09/09
						   //
						   bPktRedirected  =  FALSE;
						   postToDraw(  pProcInfo,  pPkt->head.uiTranNo_openAvDev,  pPkt,  pktLen,  &bPktRedirected,  pPkt->uiCapType,  pPkt->iIndex_capBmp,  &pPlayer->idInfo_recorder,  nPkts_left,  &pPkt->idInfo_peer,  pPkt->iTaskId,  pPkt->hWnd_task,  &playerId,  _T(  "pkt.st is 0"  )  );
						   if  (  bPktRedirected  )  {
							   mallocObj_tmpPkts[iIndex].detach(    );
						   }
						   //
						   player_get_fps(  &pPlayer->idInfo_recorder,  pPlayer->video.usFps,  pPkt->head.uiSampleTimeInMs,  &fpsInfo,  pPlayer->video.q2.cfg.name  );	//  2014/07/03

						   continue;
					   }

				   	 

					   for  (  ;  !pPlay->bQuit;  )  {

						    //  2012/01/27
						   if  (  uiSampleTimeInMs_audio  !=  pPlayer->audio.m_var.uiSampleTimeInMs  )  {
							   uiSampleTimeInMs_audio  =  pPlayer->audio.m_var.uiSampleTimeInMs;
							   dwTickCnt_syncAv_audio  =  pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_syncAv;
						   }
			   
						   //
						   dwTickCnt_syncAv_now  =  M_GetTickCount_av(  tickObj  );
						   dwTickCnt_internal = myGetTickCount(0);// M_GetTgt_video(tickObj);
						   
						   //
						   BOOL		bNoAudio	=  FALSE;

						   						   
						   //  这里通常是没有audio的情况							
						   if  (  dwTickCnt_syncAv_now  >  dwTickCnt_syncAv_audio  +  10000  )  {
							   bNoAudio  =  TRUE;										 								 
						   }	 
						   //																	 
						   _sntprintf(  pPlay->m_var.tWhere,  mycountof(  pPlay->m_var.tWhere  ),  _T(  "%I64u %s:"  ),  pPlayer->idInfo_recorder.ui64Id,  bNoAudio  ?  _T(  "no audio"  )  :  _T(  "av"  )  );
						   TCHAR  *	tWhere  =  pPlay->m_var.tWhere;

						   //  2016/04/10
						   pPlay->m_var.lowLatency.bNoAudio  =  bNoAudio;
						   //
						   pPlay->m_var.lowLatency.bAccurate  =  FALSE;
						   
						   //  2015/09/14
						   int  nQNodes_left  =  getQ2Nodes(&pPlay->q2)  +  nPkts_left;
						   
						   //  2015/09/12
						   #define	MAX_nTimes_sleep	4	//  3	//  2

						   //
						   if (pPlay->m_var.lowLatency.nTimes_sleep) {
							   int ii = 0;

						   }

						   //
						   if  (  pPlay->m_var.lowLatency.nTimes_sleep  >  MAX_nTimes_sleep  )  {
							   dwToInMs  =  0;
							   //							   	
							   dwTgt_internal_toPlay  =  dwTickCnt_internal  +  dwToInMs;
							   //
							   if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPreDrawStatus  )  {	
								   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  tWhere,  _T(  "big nTimes_sleep:"  ),  _T(  "pkt.sm %dms, play.sm %dms, play.sm_new %dms, dwToInMs %dms"  ),  pPkt->head.uiSampleTimeInMs,  pPlay->m_var.uiSampleTimeInMs,  pPlay->m_var.uiSampleTimeInMs_newRecvd,  dwToInMs  );	
							   }

							   }
						   else  {
							     DWORD  nInterval_pkt  =  pPkt->head.uiSampleTimeInMs  -  pPlayer->video.m_var.uiSampleTimeInMs;
								 //
								 //nInterval_pkt  =  min(  nInterval_pkt,  200  );
								 nInterval_pkt  =  min(  nInterval_pkt,  33  );
								 //
							     int  iMax_toInMs  =  nInterval_pkt;
								 int	iElapseInMs  =  dwTickCnt_internal  -  pPlay->m_var.dwTgt_uiSampleTimeInMs_internal;
								 if  (  iMax_toInMs  >  iElapseInMs  )  iMax_toInMs  -=  iElapseInMs;
								 else  iMax_toInMs  =  0;
								 //							
								 //int	nQNodes_left  =  pPlay->q2.qs[0].uiQNodes  +  pPlay->q2.qs[1].uiQNodes;
								 //
								 //int		nAheadInMs  =  0;
								 //int		nAheadInMs_min_qNodes_left  =  0;	//  2015/03/02

								 								 
						   
								 
								 //
								 int	nReason  =  0;

								 //
								 if (pPlay->usFps > 30) {
									 //MAX_interval_videoOnly_1Node
								 }


								 									
								 //								
								 //  2015/02/20									
								 //if  (  pPkt->head.uiPts  &&  fpsInfo.fps  >  MIN_realFps_pts  &&  pPlayer->video.usFps  >  MIN_fps_pts  )  
								 if  (  pPkt->head.uiPts  &&  pPlayer->video.usFps  >  MIN_fps_pts  )  
								 {
									 //
									 //  2016/04/10
									 BOOL  bAccurate  =  FALSE;
									 if  (  //pPlayer->video.m_var.status.fpsInfo..fps_real  >=  15
										 pPlay->usFps>=15
										 //&&  pPlayer->video.m_var.lowLatency.mql.mql_ok  
										 )
									 {
										 bAccurate  =  TRUE;
									 }
									 if  (  pPlay->m_var.lowLatency.bAccurate  !=  bAccurate  )  {
										 pPlay->m_var.lowLatency.bAccurate  =  bAccurate;
									 }								 										 
								 									
									 //
									 DWORD  needed_toPlay  =  0;										
									 DWORD  elapse_real  =  0;
									{									
										 //
										 if  (  bAccurate  )  {	
											 //
											 #ifdef  __DEBUG__
													 //showInfo_open0(  0,  0,  _T(  "bAccurate"  )  );
											 #endif
											 //
											#if  10
											 needed_toPlay  =  pPkt->head.uiSampleTimeInMs  -  pPlay->m_var.lowLatency.calc.uiSampleTimeInMs_start1;	//(  pPkt->head.uiPts  -  pPlay->m_var.lowLatency.calc.uiPts_start  )  *  fpsInfo.avgTimePerFrameInMs_real;	//  (  pPkt->head.uiPts  -  pPlay->m_var.status.uiPts_last  )  *  fpsInfo.avgTimePerFrameInMs;										
											 elapse_real  =  dwTickCnt_internal  -  pPlay->m_var.lowLatency.calc.dwTickCnt_start2;  //dwTgt_internal  -  pPlay->m_var.status.dwLastTgt_postToDraw;											  
											#endif
											#if  0
											 needed_toPlay  =  (  pPkt->head.uiSampleTimeInMs  -  pPlay->m_var.status.iSampleTimeInMs_last  +  fpsInfo.avgTimePerFrameInMs_real  )  /  2;
											 elapse_real  =  dwTgt_internal  -  pPlay->m_var.status.dwLastTickCnt_postToDraw;
											#endif
											 //
											 }
										 else  {
											   needed_toPlay  =  (  pPkt->head.uiPts  -  pPlay->m_var.status.uiPts_last  )  *  fpsInfo.avgTimePerFrameInMs;																																 												
											   elapse_real  =  dwTickCnt_internal  -  pPlay->m_var.status.dwLastTickCnt_postToDraw;											  
										 }
										 //
										 //if  (  elapse_real  +  pPlay->m_var.lowLatency.ah.totalAh1  >  needed_toPlay  +  pPlay->m_var.lowLatency.ah.totalDelay1  )  
										 if (elapse_real > needed_toPlay)
										 {	
											 //
											 #ifdef  __DEBUG__
													#if  0
													 //if  (  pPlayer->idInfo_recorder.ui64Id  )  
													 {
														 int  ii  =  1;
														 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "playVideo: %I64u, elapse %d  +  totalAh %d > needed_toPlay %d  +  totalDelay %d"  ),  pPlayer->idInfo_recorder.ui64Id,  elapse_real,  pPlay->m_var.lowLatency.ah.totalAh,  needed_toPlay,  pPlay->m_var.lowLatency.ah.nDelay  );
														 showInfo_open0(  0,  0,  tBuf  );
													 }
													#endif
											 #endif
											 //
											 //pPlay->m_var.lowLatency.bNeedAdjust3  =  true;
											 //
										     dwToInMs  =  0;												   
											 nReason  =  1;												   
											 }											
										 else  {
											   //dwToInMs  =  needed_toPlay  -  elapse_real  -  pPlay->m_var.lowLatency.ah.totalAh1  +  pPlay->m_var.lowLatency.ah.totalDelay1;
											   dwToInMs = needed_toPlay - elapse_real;
	
											   //
											   if (dwToInMs > pPlay->m_var.status.fpsInfo.avgTimePerFrameInMs * 5) {
												   pPlay->m_var.lowLatency.bNeedAdjust3 = true;	//
												   //
												   if (pPlayer->idInfo_recorder.ui64Id) {
													   _sntprintf(tBuf, mycountof(tBuf), _T("playVideo %I64u: to %dms, 乱了，重新复位一下 "), pPlayer->idInfo_recorder.ui64Id, dwToInMs);
													   //showInfo_open0(0, 0, tBuf);
												   }
											   }
											   else {
												   if (pProcInfo->cfg.debugStatusInfo.ucbShowToDrawStatus) {
													   if (0) {
														   if (pPlayer->idInfo_recorder.ui64Id) {
															   _sntprintf(tBuf, mycountof(tBuf), _T("playVideo %I64u: to %dms"), pPlayer->idInfo_recorder.ui64Id, dwToInMs);
															   showInfo_open0(0, 0, tBuf);
														   }
													   }
												   }
											   }


											   //
										 }
										 //
										 #ifdef  __DEBUG__
												 //  2016/04/11
												 //pPlay->m_var.lowLatency.dwToInMs_1740  =  dwToInMs;
										 #endif
									 }
									 //
									 //int  max_to  =  fpsInfo.avgTimePerFrameInMs  *  1.1;	//  +  3;									
									 int  max_to = fpsInfo.avgTimePerFrameInMs * 3;//  +1;//  *1.2;	//  +  3;
									if (pPlay->usFps > 30) {
										max_to = fpsInfo.avgTimePerFrameInMs  +  1;
									}
									 if  (  dwToInMs  >  max_to  )  {
										 dwToInMs  =  max_to;
									 }							 

									 //
#ifdef  __DEBUG__
									 if (pPlayer->idInfo_recorder.ui64Id == 0) {
										 _sntprintf(tBuf, mycountof(tBuf), _T("%s: nQNodes %d"), pPlay->q2.cfg.name,  nQNodes_left);
										 showInfo_open(0, 0, 0, tBuf);
									 }
#endif 

									 //  2026/03/02
									 //if (pPkt->usPktResType == CONST_pktResType_sharedTex) 
									 {
										 if (nQNodes_left > 6) {
											 dwToInMs = fpsInfo.avgTimePerFrameInMs;
										 }
									 }

									 //
									 }		//  >10fps
								 else  {	//  low fps video


										 //  2013/04/08
										 int	MAX_interval_videoOnly_1Node = 600;		//  120		//  200	//  1200
										 //
										 int  MAX_interval_videoOnly_manyNodes = 80;		//  160		//  80
										 //
										 int  MAX_dwToInMs_videoOnly = 40;		//  2013/08/02. 最慢按25fps算

										 //
										 if  (  bNoAudio  )  {

									 
										   //	
										   float  f  =  0.3;
										   if  (  nQNodes_left  >  0  )  {
											   if  (  pPlay->m_var.uiSampleTimeInMs_newRecvd  >  pPkt->head.uiSampleTimeInMs  +  MAX_interval_videoOnly_manyNodes  )  {
												   f  =  0.17;
											   }																					 
											   }
										   else  {
												 if  (  pPlay->m_var.uiSampleTimeInMs_newRecvd  >  pPkt->head.uiSampleTimeInMs  +  MAX_interval_videoOnly_1Node  )  {									     
													 f  =  0.05;		//  把过老的数据扔出去									
												 }																													   									 
										   }
										   //									
										   dwToInMs  =  pPkt->head.uiSampleTimeInMs  -  pPlay->m_var.uiSampleTimeInMs;
										   //
										   if  (  dwToInMs  >  iElapseInMs  )  dwToInMs  -=  iElapseInMs;																				
										   else  dwToInMs  =  0;
										   //										
										   int  iMax_dwToInMs_videoOnly  =  min(  MAX_dwToInMs_videoOnly,  fpsInfo.avgTimePerFrameInMs  );
										   
										   //  
										   if  (  dwToInMs  >  iMax_dwToInMs_videoOnly  )  dwToInMs  =  iMax_dwToInMs_videoOnly  +  (  dwToInMs  -  iMax_dwToInMs_videoOnly  )  *  f;
									 
										   //									 
										   //
										   if  (  nInterval_pkt  >  fpsInfo.avgTimePerFrameInMs  +  1  )  {	
											   int  iVal  =  nInterval_pkt  -  (  fpsInfo.avgTimePerFrameInMs  +  1  );
											   for  (  ;  iVal;  iVal  --  )  {
												    if  (  dwToInMs  )  dwToInMs  --  ;	
													if  (  iMax_toInMs  )  iMax_toInMs  --  ;										   
											   }										   
											   }									   
										   else  if  (  nInterval_pkt  <  fpsInfo.avgTimePerFrameInMs  )  {
													 if  (  nQNodes_left  <  pPlayer->video.q2.cfg.uiMaxQNodes  *  2  /  3  )  {																									 
														 dwToInMs  ++  ;													   																											   												 
													 }												 									   
										   }
										   
										   //
										   int  iMin  =  min(  iMax_toInMs,  fpsInfo.avgTimePerFrameInMs  -  3  );									  
										   int  iMax  =  min(  iMax_toInMs,  fpsInfo.avgTimePerFrameInMs  +  2  );
									 		
										   if  (  dwToInMs  <  iMin  )  dwToInMs  =  iMin;									 
										   else  if  (  dwToInMs  >  iMax  )  {
													 dwToInMs  = iMax;											   									 
										   }										   									
										   
										   //  2015/06/20
										   int  tmp_fps_2  =  fpsInfo.fps_real  /  2;	//  以半秒为界来衰减
										   if  (  nQNodes_left  >  tmp_fps_2  )  {
											   //
											   if  (  tmp_fps_2  <=  0  )  tmp_fps_2  =  1;
											   int  n  =  nQNodes_left  /  tmp_fps_2;
											   //
											   if  (  n  <=  0  )  n  =  1;
											   dwToInMs  /=  n;
										   }

										   //											 
										   if  (  dwToInMs  >  1  )  dwToInMs  -=  1;	
										   
										   //
										   if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPreDrawStatus  )  {									
												 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  tWhere,  _T(  ""  ),  _T(  "fps_real %.2f. nNodes_left %d, dwToInMs %d"  ),  
																															fpsInfo.fps_real,  nQNodes_left,  dwToInMs  );					
										   }							   

									 }
									 
								 else  {

										     //							
										     getSampleTimeInMs_needed(  pProcInfo,  uiSampleTimeInMs_audio,  dwTickCnt_syncAv_audio,  pPlay->m_var.uiSampleTimeInMs,  pPlay->m_var.dwTgt_uiSampleTimeInMs_internal,  dwTickCnt_syncAv_now,  dwTickCnt_internal,  pPkt->head.uiSampleTimeInMs,  &dwToInMs  ); 								 						   
											 //
											 if  (  nInterval_pkt  >  fpsInfo.avgTimePerFrameInMs  +  1  )  {	
												 int  iVal  =  nInterval_pkt  -  (  fpsInfo.avgTimePerFrameInMs  +  1  );
												 for  (  ;  iVal;  iVal  --  )  {
													  if  (  dwToInMs  )  dwToInMs  --  ;	
													  if  (  iMax_toInMs  )  iMax_toInMs  --  ;										   
												 }										   
												 }
											 else  if  (  nInterval_pkt  <  fpsInfo.avgTimePerFrameInMs  )  {
													   if  (  nQNodes_left  <  pPlayer->video.q2.cfg.uiMaxQNodes  *  2  /  3  )  {																									 
														   dwToInMs  ++  ;													   																											   												
													   }												 									   
											 }
											 //
											 int  iMin  =  min(  iMax_toInMs,  fpsInfo.avgTimePerFrameInMs  -  3  );
											 int  iMax  =  min(  iMax_toInMs,  fpsInfo.avgTimePerFrameInMs  +  2  );									   									   

											 if  (  dwToInMs  <  iMin  )  {										
												 int  iAhead  =  0;										   									   											

												 if  (  nQNodes_left  )  {
													 if  (  iMin  )  {
														 iAhead  =  1;
													 }										   
												 }										   
												 dwToInMs  =  iMin  -  iAhead;										   
												 }
											 else  if  (  dwToInMs  >  iMax  )  {
												 int  iDelay  =  0;	
												 
												 //
												 if  (  nQNodes_left  <  pPlay->q2.cfg.uiMaxQNodes  *  2  *  2  /  3  )  {
													 												
													 if  (  dwToInMs  >  fpsInfo.avgTimePerFrameInMs  +  3  )  {													
														 iDelay  =  2;													 
														 }
													 else  {
														   iDelay  =  1;												 
													 }
												 }

												 dwToInMs  = iMax  +  iDelay;												 									   
											 }									   
									   }
								 }								 

								 //								
								 dwTgt_internal_toPlay  =  dwTickCnt_internal  +  dwToInMs;

								 //								
								 if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPreDrawStatus  )  {									
									 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  tWhere,  _T(  ""  ),  _T(  "pkt.sm %d, play.sm %d, play.sm_new %d. nQNodes_left %d,  mql %d, dwToInMs %d. bAdjust %d, nReason %d"  ),  
																																			pPkt->head.uiSampleTimeInMs,  pPlay->m_var.uiSampleTimeInMs,  pPlay->m_var.uiSampleTimeInMs_newRecvd,  
																																			nQNodes_left,
																																			pPlay->m_var.lowLatency.mql.mql_1s.mql,
																																			dwToInMs,  
																																			pPlay->m_var.lowLatency.bNeedAdjust3,  nReason  );   
								 }							   
						   }
			   
						   if  (  dwTgt_internal_toPlay  <=  dwTickCnt_internal  +  CONST_video_skippedInterval  )  {
							   //  2012/02/07
							   //  pPkt->debugInfo.dwTickCnt_postToDraw  =  M_GetTickCount_video(  tickObj  );
							   if  (  dwTgt_internal_toPlay  >  dwTickCnt_internal  )  dwToInMs  =  dwTgt_internal_toPlay  -  dwTickCnt_internal;
							   else  dwToInMs  =  0;		//  2013/09/09						   
							   //
							   pPlay->m_var.lowLatency.dwToInMs_toPostDraw  =  dwToInMs;	//  2013/09/09
							   //
							   bPktRedirected  =  FALSE;
							   postToDraw(  pProcInfo,  pPkt->head.uiTranNo_openAvDev,  pPkt,  pktLen,  &bPktRedirected,  pPkt->uiCapType,  pPkt->iIndex_capBmp,  &pPlayer->idInfo_recorder,  nPkts_left,  &pPkt->idInfo_peer,  pPkt->iTaskId,  pPkt->hWnd_task,  &playerId,  _T(  "dwTgt_internal_toPlay  <=  dwTgt_internal  +  CONST_video_skippedInterval"  )  );
							   if  (  bPktRedirected  )  {
								   mallocObj_tmpPkts[iIndex].detach(    );

							   }

							   //  2009/05/26
							   pPlay->m_var.uiSampleTimeInMs  =  pPkt->head.uiSampleTimeInMs;
							   pPlay->m_var.dwTgt_uiSampleTimeInMs_internal  =  dwTickCnt_internal;	//  M_GetTickCount_video(  tickObj  );
							   pPlay->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  =  myGetTickCount( mynull  );
							   //
							   player_get_fps(  &pPlayer->idInfo_recorder,  pPlayer->video.usFps,  pPkt->head.uiSampleTimeInMs,  &fpsInfo,  pPlayer->video.q2.cfg.name  );	//  2014/07/03

							   break;
						   }


						   //
						   dwToInMs  =  dwTgt_internal_toPlay  -  dwTickCnt_internal;

						   int nAHead = CONST_video_ahead;
#if  0
						   //  2023/04/28
						   int tmp_nQNodes = getQ2Nodes(&pPlayer->video.q2)  +  nPkts_left  ;
						   int n1 = tmp_nQNodes / 5;
						   int mm = n1 * n1;
						   //												
						   //
						   if (fpsInfo.fps_real > 40) {
							   mm = mm * n1;
						   }
						   //
						   nAHead += mm;
#endif
						   
							//  2012/01/28, 有一个很小的提前量,因为从恢复休眠到显示,也需要时间
							if  (  dwToInMs  >  nAHead  )  {
								//
								accurateSleep(  dwToInMs  -  nAHead,  _T(  ""  )  );
								
							}						


							//  if  (  bPktLeft  )  
							{
								//
								//  pPkt->debugInfo.dwTickCnt_postToDraw  =  M_GetTickCount_video(  tickObj  );
								pPlay->m_var.lowLatency.dwToInMs_toPostDraw  =  dwToInMs;
								//
								bPktRedirected  =  FALSE;
								postToDraw(  pProcInfo,  pPkt->head.uiTranNo_openAvDev,  pPkt,  pktLen,  &bPktRedirected,  pPkt->uiCapType,  pPkt->iIndex_capBmp,  &pPlayer->idInfo_recorder,  nPkts_left,  &pPkt->idInfo_peer,  pPkt->iTaskId,  pPkt->hWnd_task,  &playerId,  _T(  "after accurateSleep"  )  );
								if  (  bPktRedirected  )  {
									mallocObj_tmpPkts[iIndex].detach(    );
								}
								//  bPktLeft  =  FALSE;

								//  2009/05/26
								pPlay->m_var.uiSampleTimeInMs  =  pPkt->head.uiSampleTimeInMs;
								pPlay->m_var.dwTgt_uiSampleTimeInMs_internal  =  M_GetTgt_video(  tickObj  );	//  dwTickCnt_toPlay;
								pPlay->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  =  myGetTickCount( nullptr );
								//
								player_get_fps(  &pPlayer->idInfo_recorder,  pPlayer->video.usFps,  pPkt->head.uiSampleTimeInMs,  &fpsInfo,  pPlayer->video.q2.cfg.name  );	//  2014/07/03

							}
							break;				   //  一个pkt被播放完了					   
					   }					   
					}

					//
					#ifdef  __DEBUG__
					        for  (  int  i  =  0;  i  <  nPkts;  i  ++  )  {
								 QY_MEMORY	memory;
								 if  (  mallocObj_tmpPkts[i].get(  &memory  )  )  continue;
								 if  (  memory.m_pBuf  &&  memory.uiBufSize  )  {
									 M_pkt_showNo(  pkts[i],  _T(  "playVideo . free"  )  );							
								 }
							}
				    #endif

			   }
		  }

		  //
		  continue;
	 }

	 traceLogA(  (char*)  "mcThreadProc_playVideo will quit"  );

errLabel:

	 pPlay->bRunning  =  FALSE;

	 //
	 pPlay->doPre_toPlayVideo.bQuit = true;
	 waitForObject(&pPlay->doPre_toPlayVideo.hThread, 20000);
	 if (pPlay->doPre_toPlayVideo.hThread) {
		 showInfo_open0(0, 0, _T("playVideo: waitForObject failed"));
	 }




	 //
	 if (ctx_fillData_d3d.pImgDataBuf) {
		 MACRO_safeFree(ctx_fillData_d3d.pImgDataBuf);
	 }

	 //
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u ends."  ),  pPlayer->video.q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id  );
	 
	 traceLogA(  (char*)  "playVideo %S leaves",  pPlay->q2.cfg.name  );
	
	 return  0;

}
#endif 


//
extern "C" DWORD WINAPI mcThreadProc_playVideo(LPVOID lpParameter)
{
	MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)lpParameter;
	if (!pProcInfo)  return  -1;
	QY_MC* pQyMc = pProcInfo->pQyMc;
	if (!pQyMc)  return  -1;

	//
	DYN_LIB_DX* pDynLib = (DYN_LIB_DX*)((QY_DYN_LIBS*)pQyMc->env.pDynLibs)->pLib_dx;

	QY_PLAYER* pPlayer = NULL;
	PLAY_VIDEO_procInfo* pPlay = NULL;

	//
	PLAYER_ID						playerId;
	memset(&playerId, 0, sizeof(playerId));

	//
	DWORD							dwThreadId = GetCurrentThreadId();

	//
	CQyTick						tickObj;
	//DWORD							dwTgt_lastData				=	M_GetTgt_video(  tickObj  );;						// 

	//
	myDRAW_VIDEO_DATA				pkts[CONST_pkts_playVideo];
	unsigned  int					uiLens[CONST_pkts_playVideo];		//  要增加一个qGetMsgs，将pPkts和pktLens作为参数输入。2011/07/15
	int							nLens = mycountof(uiLens);		//  一次最多处理的包数。

	//int							len_pkts;
	int							nPkts;

	MIS_CNT* pMisCnt = getMisCntByName(pProcInfo, _T(""));
	if (!pMisCnt)  return  -1;

	//  2011/12/05
	CQyMalloc	mallocObj_tmpRgbBuf;
	char* tmpRgbBuf = NULL;

	//
	Ctx_fillData_d3d  ctx_fillData_d3d;
	memset(&ctx_fillData_d3d, 0, sizeof(ctx_fillData_d3d));

	//
	//  #define		DEFAULT_dwToInMs_playVideo		200
	//#define		DEFAULT_dwToInMs_playVideo			210
	//#define		DEFAULT_dwToInMs_playVideo			100
#define		DEFAULT_dwToInMs_playVideo			16
//
#define		CONST_video_skippedInterval			0	//  
#define		CONST_video_ahead					0	//  			//  提前量

	DWORD							dwToInMs = DEFAULT_dwToInMs_playVideo;

	DWORD							dwTickCnt_internal;
	DWORD							dwTgt_internal_toPlay;
	DWORD							dwTickCnt_syncAv_now;

	BOOL							bPktRedirected = FALSE;

	unsigned  int					uiSampleTimeInMs_audio = 0;
	DWORD							dwTickCnt_syncAv_audio = 0;

	//
	//  2015/03/12. 本地视频没有做pts,是错的。不过，现在先暂时伪造一个，以便用pts来改善播放效果
	unsigned  int					tmp_localV_pts_faked = 0;
	//
	TCHAR  tBuf[128];

	//
	int							totalPkts = 0;
	int							totalPkts_lastOk = 0;
	int							nPkts_left = 0;
	bool							bExists_skipped = false;

	//
	{
		int  i;
		for (i = 0; i < pProcInfo->av.usCnt_players; i++) {
			if (dwThreadId == pProcInfo->av.pPlayers[i].video.dwThreadId)  break;
		}
		if (i == pProcInfo->av.usCnt_players) {
			return  -1;
		}
		pPlayer = &pProcInfo->av.pPlayers[i];
		pPlay = &pProcInfo->av.pPlayers[i].video;

		//  2016/02/18
		playerId.index_player = i;
		playerId.uiTranNo_player = pPlayer->playerId.uiTranNo_player;
	}

	//
#ifdef  __DEBUG__
	traceLogA((char*)"playVideo %S enters", pPlay->q2.cfg.name);
#endif

	//  2014/07/03
	//  TMP_fps_info					fpsInfo  =  {0,};	
	TMP_fps_info& fpsInfo = pPlay->m_var.status.fpsInfo;
	memset(&fpsInfo, 0, sizeof(fpsInfo));
	//  2015/09/13
	//BOOL  &  bNeedAdjust  =  pPlay->m_var.lowLatency.bNeedAdjust;

	//
	switch (pPlayer->video.vh.bih.biCompression) {
	case  BI_RGB:
	case  CONST_fourcc_YV12:
	case  CONST_fourcc_I420:	//  2014/07/21
	case  CONST_fourcc_NV12:
		break;
	default:
#ifdef  __DEBUG__
		char  buf[128];
		traceLogA((char*)"playVideo: %s failed. only support play rgb or yv12. ", iFourcc2Str(pPlayer->video.vh.bih.biCompression, buf, mycountof(buf)));
#endif
		goto  errLabel;
	}

	BITMAPINFOHEADER	bih;
	makeBmpInfoHeader_rgb(24, pPlayer->video.vh.bih.biWidth, pPlayer->video.vh.bih.biHeight, &bih);
	if (memcmp(&bih, &pPlayer->video.vh.bih, sizeof(bih)))  memcpy(&pPlayer->video.vh.bih, &bih, sizeof(pPlayer->video.vh.bih));

	//  2011/12/05
	tmpRgbBuf = mallocObj_tmpRgbBuf.mallocf(bih.biSizeImage);
	if (!tmpRgbBuf) {
		TCHAR  tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("playVideo failed: tmpRgbBuf.malloc returns null, bih.biSizeImage %d"), bih.biSizeImage);
		showInfo_open0(0, 0, tBuf);
		goto  errLabel;
	}


	// Create the events. We make an extra one for later use 
	// by the output buffer.
	/*
	for  (  i  =  0;  i  <  mycountof(  pPlay->hEvents  );  i  ++  )  {
		 pPlay->hEvents[i] = CreateEvent( NULL, FALSE, FALSE, NULL );
		 if ( NULL == pPlay->hEvents[i] ) goto  errLabel;
	}
	*/

	///////
	pPlay->doPre_toPlayVideo.bQuit = false;
	//
	DWORD  dwThreadDaemonId;
	pPlay->doPre_toPlayVideo.hThread = CreateThread(NULL, 0, mcThreadProc_doPre_toPlayVideo, pPlayer, CREATE_SUSPENDED, &dwThreadDaemonId);
	if (!pPlay->doPre_toPlayVideo.hThread)  goto  errLabel;
	pPlay->doPre_toPlayVideo.dwThreadId = dwThreadDaemonId;
	if (ResumeThread(pPlay->doPre_toPlayVideo.hThread) == -1)  goto  errLabel;




	//pPlay->bQuit  =  FALSE;
	pPlay->dwTickCnt_start = myGetTickCount(nullptr);	//  M_GetTickCount_video(  tickObj  );		//  2010/05/04
	pPlay->bRunning = TRUE;
	pPlayer->uiSampleTimeInMs_start = 0;
	memset(&pPlay->m_var, 0, sizeof(pPlay->m_var));

	//
	pPlay->m_var.dwTickCnt_lastData = myGetTickCount(0);


	//
	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s, %I64u starts"), pPlay->q2.cfg.name, pPlayer->idInfo_recorder.ui64Id);

	//  2013/10/06
#if  0
	int  sizeImage_rgb32 = M_sizeImage(32, pPlay->vh.bih.biWidth, pPlay->vh.bih.biHeight);
	BITMAPINFOHEADER	bih32;
	makeBmpInfoHeader_rgb(32, pPlay->vh.bih.biWidth, pPlay->vh.bih.biHeight, &bih32);
#endif

	/////////////////
	emptyQ2(&pPlay->q2);

	//  2015/09/14
	//pPlay->m_var.lowLatency.mql.max_ql_ok_avg_100  =  pPlayer->video.usFps  /  2  *  100;

	//
	for (; bPlayerOk(pPlayer, 0); ) {

		//
		if (pPlayer->bNeedEnd1) {
			//
			_sntprintf(tBuf, mycountof(tBuf), _T("player[%d].bNeedEnd true, will quit. l414"), playerId.index_player);
			showInfo_open0(0, 0, tBuf);
			//
			break;
		}

		//
#if  0	//  2015/09/12
		if (!dwToInMs || dwToInMs > DEFAULT_dwToInMs_playVideo) {
			traceLogA((char*)("Warning: mcThreadProc_playVideo: dwToInMs %d"), dwToInMs);
#if  0
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Warning: mcThreadProc_playVideo: dwToInMs %d"), dwToInMs);
#endif
			dwToInMs = DEFAULT_dwToInMs_playVideo;
		}
#endif
		//  2015/09/12
		dwToInMs = DEFAULT_dwToInMs_playVideo;
		int  iFps = (int)fpsInfo.fps_real;
#if 0
		if (iFps > 15)
		{
			//dwToInMs = 33;
			dwToInMs = 16;
		}
#endif
		dwToInMs = 16;

		//

		//
#ifdef  __DEBUG__
		if (pProcInfo->cfg.debugStatusInfo.bDbgDetail_playV) {
			if (!pQyMc->appParams.bMcu) {
				if (pPlayer->idInfo_recorder.ui64Id) {
					_sntprintf(tBuf, mycountof(tBuf), _T("playVideo: %I64u, before waitForObject. "), pPlayer->idInfo_recorder.ui64Id);
					if (pPlay->m_var.lowLatency.bNeedAdjust3) {
					}
					showInfo_open0(0, 0, tBuf);
				}
			}
		}
#endif

		//
		pPlay->m_var.lowLatency.stat_noMsgAndWait.nTimes++;


		//
		//  2012/03/01, 设置此标志位,使有数据包来时,可以触发
		pPlay->m_var.status.bNoMsgAndWait = TRUE;
		//
		DWORD  dwEvt = MsgWaitForMultipleObjects(
			pPlay->q2.cfg.usCnt_hEvents,	//  mycountof(  pPlay->hEvents  ),				// Number of events.
			pPlay->q2.hEvents,							// Location of handles.
			FALSE,										// Wait for all?
			dwToInMs,									// How long to wait?
			0);										// Any message is an 
		// event.
		if (dwEvt == WAIT_FAILED)  goto  errLabel;
		//  2012/03/01
		pPlay->m_var.status.bNoMsgAndWait = FALSE;


		//
		dwTickCnt_internal = myGetTickCount(0);// M_GetTgt_video(tickObj);

		//
#if  0
		if (dwTgt_internal - dwTgt_lastData > (DWORD)(pProcInfo->cfg.usTimeoutInMs_player_v)) {
#ifdef  __DEBUG__
			_sntprintf(tBuf, mycountof(tBuf), _T("video data may not arrives, player exits. %I64u %d, timeout is %d"), pPlayer->idInfo_recorder.ui64Id, pPlayer->video.uiTranNo, pProcInfo->cfg.usTimeoutInMs_player_v);
			traceLog(tBuf);
#endif
			break;
		}
#endif 

		//
		if (dwEvt != WAIT_TIMEOUT) {
			dwEvt -= WAIT_OBJECT_0;
			switch (dwEvt) {
			case  0:
				//  dwTickCnt_lastData  =  dwTickCnt;		//  audio data received
				break;
			case  1:
				//  traceLogA(  (char*)  "playVideo: event 1."  );
				if (0)	//  2015/09/13
				{
					//  traceLogA(  (char*)  "playVideo: event 1... "  );
					if (pPlay->m_var.uiSampleTimeInMs) {
						if (pPlay->m_var.uiSampleTimeInMs_newRecvd  <  pPlay->m_var.uiSampleTimeInMs
							|| pPlay->m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  >  pPlay->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv + 1000)
						{
							CQyQ2Help		q2Help;
							//qRemoveMsg(  q2Help.getQ_toGetMsg(  &pPlay->q2,  _T(  "playVideo remove"  )), (PF_bCommonHandler)tmpHandler_bOldVideo, 0, pPlayer);
						}
					}

				}
				break;
			default:
				traceLogA((char*)"unknown event");
				goto  errLabel;
				break;
			}
		}


		//
		for (; bPlayerOk(pPlayer, 0); ) {

			//
			if (pPlayer->bNeedEnd1) {
				//
				_sntprintf(tBuf, mycountof(tBuf), _T("player[%d].bNeedEnd true, will quit. l527"), playerId.index_player);
				showInfo_open0(0, 0, tBuf);
				//
				break;
			}


			//  traceLogA(  (char*)  "playVideo: msg reaved"  );
#if 0
			len_pkts = sizeof(pkts);
			{
				CQyQ2Help	q2Help;
				if (qGetMsg(q2Help.getQ_toGetMsg(&pPlay->q2, _T("playVideo 2")), pkts, (unsigned  int*)&len_pkts)) {
					dwToInMs = DEFAULT_dwToInMs_playVideo;
					break;
				}
			}
#endif
			//
			nPkts = 0;
			int i;
			//
#ifdef  __DEBUG__
			DWORD  dwTickCnt_beforeGetMsg = myGetTickCount(nullptr);
#endif

			// 					  //  pktLen  =  uiBufSize;  
			nLens = mycountof(uiLens);
			//  2014/04/10
			if (q2GetMsgPkg(&pPlay->q2, (void*)pkts, sizeof(pkts), (unsigned  int*)uiLens, (unsigned  int*)&nLens, _T("playVideo"))) {
				break;
			}

			for (i = 0; i < nLens; i++) {
				nPkts += uiLens[i] / sizeof(pkts[0]);
				if (uiLens[i] % sizeof(pkts[0])) {
#ifdef  __DEBUG__
					traceLog((TCHAR*)_T("vpp: uiLen err"));
					assert(0);
#endif
				}
			}

			//  注意：在上面qGetMsg和下面的attach之间，不要添加代码，否则，内存就失去管理了

#ifdef  __DEBUG__
		//  traceLogA(  (char*)  "playVideo: pkt.SampleTime %d, pktLen %d",  pPkt->head.uiSampleTimeInMs,  pktLen  );			
#endif

			{
				CQyMalloc		mallocObj_tmpPkts[CONST_pkts_playVideo];


				BOOL  tmpbErr = FALSE;	//  注意：这里如果attach出错，要继续attach, 但是最后要continue. 以防止pPkts[i]没有机会释放内存
				//
				//nPkts  =  len_pkts  /  sizeof(  pkts[0]  );
				for (int i = 0; i < nPkts; i++) {
					myDRAW_VIDEO_DATA* pPkt = &pkts[i];
					if (pPkt->memory.m_pBuf) {
						if (mallocObj_tmpPkts[i].attach(&pPkt->memory)) {
#ifdef  __DEBUG__
							traceLogA((char*)"mcThreadProc_playVideo: mallocObj.attach failed");
#endif
							clean_myDRAW_VIDEO_DATA(pPkt, _T("playVideo"));
							tmpbErr = TRUE;
							continue;
						}
					}
				}
				if (tmpbErr)  continue;

#if 0
				if (len_pkts % sizeof(myDRAW_VIDEO_DATA)) {
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("playVideo err: len_pkts err"));
#ifdef  __DEBUG__
					assert(0);
#endif
					continue;
					//  应该只发个myDRAW_VIDEO_DATA过来
				}
#endif

#ifdef  __DEBUG__
				//
				if (nPkts != 1) {
					//traceLog((TCHAR*)  _T(  "playVideo: nPkts %d"  ),  nPkts  );
				}
				for (int i = 0; i < nPkts; i++) {
					myDRAW_VIDEO_DATA* pPkt = &pkts[i];
					if (!pPkt->hWnd_task
						&& !pPkt->idInfo_peer.ui64Id)
					{
						traceLog((TCHAR*)_T("playVideo: iIndex_player %d, nPkts %d, [%d].idInfo_peer is 0"), playerId.index_player, nPkts, i);
					}
				}

				//
				M_pkts_showNo_playVideo(pkts, nPkts);
#endif


				//  
				pPlayer->video.m_var.dwTickCnt_lastData = M_GetTgt_video(tickObj);		//  video data received

				//

				//
				for (int iIndex = 0; iIndex < nPkts; iIndex++) {
					myDRAW_VIDEO_DATA* pPkt = &pkts[iIndex];
					int						pktLen = sizeof(pkts[0]);

					//  2015/03/12. 对本地视频，伪造一个pts. 等回头在包生成处产生pts才对
					if (!pPlayer->idInfo_recorder.ui64Id) {
						if (!pPkt->head.uiPts) {
							pPkt->head.uiPts = tmp_localV_pts_faked;
							tmp_localV_pts_faked++;
						}
					}

					//
					totalPkts++;


					//  2015/10/04
					if (pPkt->usPktResType != CONST_pktResType_sharedTex) {
						//
						if (pPkt->head.uiLen < pPlay->vh.bih.biSizeImage) {
#ifdef  __DEBUG__
							traceLogA((char*)("playVideo err: pkt.head.uiLen %d <  sizeImage %d. skipped"), pPkt->head.uiLen, pPlay->vh.bih.biSizeImage);
#endif
							qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("playVideo err: pkt.head.uiLen %d <  sizeImage %d. skipped"), pPkt->head.uiLen, pPlay->vh.bih.biSizeImage);
							continue;
						}

						//
						Param_bPktSkipped  param = { 0 };
						param.last_mql = pPlay->m_var.lowLatency.mql.mql_3s.last_mql;
						param.mql_ok = pPlay->m_var.lowLatency.mql.mql_ok;
#ifdef  __DEBUG__
						//param.bDbg = true;
#endif
							//
							//
						int nQNodes = getQ2Nodes(&pPlayer->video.q2);
						//
						nPkts_left = nPkts - iIndex;
						//
						bool  b4k = is4k(pPlayer->video.vh.bih.biWidth, pPlayer->video.vh.bih.biHeight);
						unsigned  __int64 nFactor = 0;
						if (bPktSkipped(&param, CONST_nWhere_playVideo, pPlayer->video.usFps, 0, nQNodes, totalPkts, nPkts_left, b4k, &totalPkts_lastOk, &nFactor)) {
							//_sntprintf(tBuf, mycountof(tBuf), _T("playVideo %I64u: totalPkts %d, factor %I64u, n_left %d, skipped"), pPlayer->idInfo_recorder.ui64Id, totalPkts, nFactor, nPkts_left  +  nQNodes);
							_sntprintf(tBuf, mycountof(tBuf), _T("playVideo %I64u: totalPkts %d, fps %d, mql_last %d,mql_ok %d, n_left %d, skipped"), pPlayer->idInfo_recorder.ui64Id, totalPkts, (int)pPlayer->video.usFps, param.last_mql, param.mql_ok, nPkts_left + nQNodes);
							//showInfo_open0(0, 0, tBuf);
							if (param.bDbg) {
								showInfo_open0(0, 0, param.tBuf);
							}
							//
							doCalcMql(pProcInfo, pPkt->head.uiTranNo_openAvDev, pPkt, &pPlayer->idInfo_recorder, nPkts_left, &pPkt->idInfo_peer, pPkt->iTaskId, &playerId, _T("after bPktSkipped"));

							//
							bExists_skipped = true;

							//
							continue;
						}

						//
#ifdef  __DEBUG__
#endif

						//
						if (bExists_skipped) {
							bExists_skipped = false;
							//
							//pPlay->m_var.lowLatency.bNeedAdjust3 = true;
						}

					}

					//  
					if (!pPkt->bResizeToPlay) {
						if (pPkt->bih.biWidth != pPlay->vh.bih.biWidth
							|| pPkt->bih.biHeight != pPlay->vh.bih.biHeight
							|| !pPkt->bih.biSizeImage)
						{
#ifdef  __DEBUG__
							traceLog((TCHAR*)_T("playVideo err: pkt %d,%d !=  player %d,%d. skipped"), (int)pPkt->bih.biWidth, (int)pPkt->bih.biHeight, (int)pPlay->vh.bih.biWidth, (int)pPlay->vh.bih.biHeight);
#endif
							qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("playVideo err: pkt %d,%d !=  player %d,%d. skipped"), (int)pPkt->bih.biWidth, (int)pPkt->bih.biHeight, (int)pPlay->vh.bih.biWidth, (int)pPlay->vh.bih.biHeight);
							continue;
						}
					}


					//
#ifdef  __DEBUG__
					DWORD	dwTickCnt_beforeYv12;  dwTickCnt_beforeYv12 = 0;
					//dwTickCnt_beforeYv12  = myGetTickCount(mynull);
#endif 
					//
					if (pPkt->usPktResType != CONST_pktResType_sharedTex) {
						if (pPkt->bih.biCompression != BI_RGB) {
							//
#if  0
							if (pPkt->bih.biCompression != CONST_fourcc_YV12) {
#ifdef  __DEBUG__
								traceLog((TCHAR*)_T("playVideo err: pPkt->bih err"));
#endif
								continue;
							}
#endif
							//
							if (pPkt->bih.biSizeImage > bih.biSizeImage) {
#ifdef  __DEBUG__
								assert(0);
#endif
								continue;
							}
							memcpy(tmpRgbBuf, pPkt->memory.m_pBuf, pPkt->bih.biSizeImage);
							//
							switch (pPkt->bih.biCompression) {
							case  CONST_fourcc_YV12:
								pQyMc->yv12ToRgb24((BYTE*)tmpRgbBuf, (BYTE*)pPkt->memory.m_pBuf, pPkt->bih.biWidth, pPkt->bih.biHeight, 0);//pPlayer->video.ucbFlippedImg  );								 
								break;
							case  CONST_fourcc_I420:
								i420ToRgb24((BYTE*)tmpRgbBuf, (BYTE*)pPkt->memory.m_pBuf, pPkt->bih.biWidth, pPkt->bih.biHeight, 0); //pPlayer->video.ucbFlippedImg  );								 										
								break;
							case  CONST_fourcc_NV12:
							{
#if 0
								static FILE* fp = null;
								static int cnt = 0;
								cnt++;
								if (!fp) {
									fp = fopen("c:\\codecSdk\\out\\kk.nv12", "wb");
								}
								if (fp) {
									fwrite(tmpRgbBuf, pPkt->bih.biSizeImage, 1, fp);
								}
								if (cnt > 300) {
									if (fp) {
										fclose(fp);
										fp = null;
									}
								}
#endif

								//
								//NV12_TO_RGB24((unsigned  char*)tmpRgbBuf, (unsigned  char*)pPkt->memory.m_pBuf, pPkt->bih.biWidth, pPkt->bih.biHeight);
								nv12ToRgb24((unsigned  char*)tmpRgbBuf, (unsigned  char*)pPkt->memory.m_pBuf, pPkt->bih.biWidth, pPkt->bih.biHeight, false);

							}
							break;
							default:
#ifdef  __DEBUG__
								traceLog((TCHAR*)_T("playVideo err: pPkt->bih err"));
#endif
								continue;
								break;
							}
							//
							memcpy(&pPkt->bih, &pPlay->vh.bih, sizeof(pPkt->bih));
							pPkt->uiSize_dec = pPlay->vh.bih.biSizeImage;

						}
						else {
						}
					}

					//
					//
					if (0) {
						DWORD  dwTickCnt_afterYv12 = myGetTickCount(mynull);
						int  iDiffInMs  =  0;
						//iDiffInMs  = dwTickCnt_afterYv12 - dwTickCnt_beforeYv12;
						//_sntprintf(pPlay->m_var.lowLatency.tBuf, mycountof(pPlay->m_var.lowLatency.tBuf), _T("PlayVideo %I64u: It costs %dms to yv12"), pPlayer->idInfo_recorder.ui64Id,  iDiffInMs);
						_sntprintf(pPlay->m_var.lowLatency.tBuf, mycountof(pPlay->m_var.lowLatency.tBuf), _T("%dms to yv12"), iDiffInMs);
					}
					//
#ifdef  __DEBUG__

					//
					if (pPkt->usPktResType == CONST_pktResType_sharedTex) {
						int  ii = 0;
					}
#endif

					//  2015/09/11
					pPkt->debugInfo.dwTickCnt_playPkt_start = myGetTickCount(mynull);

					//  __declspec(  dllexport  )  int  fillData_d3d(  BITMAPINFOHEADER  *  pBih,  BYTE  *  pData,  int  iIndex_player,  BOOL  *  pbFilled  )
					memset(&pPlay->m_var.status.fillD3d, 0, sizeof(pPlay->m_var.status.fillD3d));
					if (pPlay->m_var.status.ucSkipped_for_d3dData) {
						pPlay->m_var.status.ucSkipped_for_d3dData--;
						//
						pPlay->m_var.status.fillD3d.bNeedFill = FALSE;						   //
						pPlay->m_var.status.fillD3d.bFilled_d3dData = FALSE;
					}
					else {
						pPlay->m_var.status.fillD3d.bNeedFill = TRUE;
						//
						if (dyn_fillData_d3d(&ctx_fillData_d3d, pPkt, playerId.index_player, &pPlay->m_var.status.fillD3d.param0, &pPlay->m_var.status.fillD3d.bFilled_d3dData)) {
							pPlay->m_var.status.fillD3d.bFilled_d3dData = FALSE;
						}
					}

					//
					pPlay->m_var.lowLatency.nTimes_sleep = 0;

					//
					if (!pPkt->head.uiSampleTimeInMs) {
						//  2012/02/06
						dwToInMs = 0;		//  2013/09/09
						//
						pPlay->m_var.lowLatency.dwToInMs_toPostDraw = dwToInMs;	//  2013/09/09
						//
						bPktRedirected = FALSE;
						postToDraw(pProcInfo, pPkt->head.uiTranNo_openAvDev, pPkt, pktLen, &bPktRedirected, pPkt->uiCapType, pPkt->iIndex_capBmp, &pPlayer->idInfo_recorder, nPkts_left, &pPkt->idInfo_peer, pPkt->iTaskId, pPkt->hWnd_task, &playerId, _T("pkt.st is 0"));
						if (bPktRedirected) {
							mallocObj_tmpPkts[iIndex].detach();
						}
						//
						player_get_fps(&pPlayer->idInfo_recorder, pPlayer->video.usFps, pPkt->head.uiSampleTimeInMs, &fpsInfo, pPlayer->video.q2.cfg.name);	//  2014/07/03

						continue;
					}



					for (; !pPlay->bQuit; ) {

						//  2012/01/27
						if (uiSampleTimeInMs_audio != pPlayer->audio.m_var.uiSampleTimeInMs) {
							uiSampleTimeInMs_audio = pPlayer->audio.m_var.uiSampleTimeInMs;
							dwTickCnt_syncAv_audio = pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_syncAv;
						}

						//
						DWORD  dwTickCnt_cur = myGetTickCount(0);
						dwTickCnt_syncAv_now = dwTickCnt_cur;// M_GetTickCount_av(tickObj);
						dwTickCnt_internal = dwTickCnt_cur;// M_GetTgt_video(tickObj);

						//
						BOOL		bNoAudio = FALSE;


						//  这里通常是没有audio的情况							
						if (dwTickCnt_syncAv_now > dwTickCnt_syncAv_audio + 10000) {
							bNoAudio = TRUE;
						}
						//																	 
						_sntprintf(pPlay->m_var.tWhere, mycountof(pPlay->m_var.tWhere), _T("%I64u %s:"), pPlayer->idInfo_recorder.ui64Id, bNoAudio ? _T("no audio") : _T("av"));
						TCHAR* tWhere = pPlay->m_var.tWhere;

						//  2016/04/10
						pPlay->m_var.lowLatency.bNoAudio = bNoAudio;
						//
						pPlay->m_var.lowLatency.bAccurate = FALSE;

						//  2015/09/14
						int  nQNodes_left = getQ2Nodes(&pPlay->q2) + nPkts_left;

						//  2015/09/12
#define	MAX_nTimes_sleep	4	//  3	//  2

//
						if (pPlay->m_var.lowLatency.nTimes_sleep) {
							int ii = 0;

						}

						//
						if (pPlay->m_var.lowLatency.nTimes_sleep > MAX_nTimes_sleep) {
							dwToInMs = 0;
							//							   	
							dwTgt_internal_toPlay = dwTickCnt_internal + dwToInMs;
							//
							if (pProcInfo->cfg.debugStatusInfo.ucbShowPreDrawStatus) {
								qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, tWhere, _T("big nTimes_sleep:"), _T("pkt.sm %dms, play.sm %dms, play.sm_new %dms, dwToInMs %dms"), pPkt->head.uiSampleTimeInMs, pPlay->m_var.uiSampleTimeInMs, pPlay->m_var.uiSampleTimeInMs_newRecvd, dwToInMs);
							}

						}
						else {
							DWORD  nInterval_pkt = pPkt->head.uiSampleTimeInMs - pPlayer->video.m_var.uiSampleTimeInMs;
							//
							//nInterval_pkt  =  min(  nInterval_pkt,  200  );
							nInterval_pkt = min(nInterval_pkt, 33);
							//
							int  iMax_toInMs = nInterval_pkt;
							int	iElapseInMs = dwTickCnt_internal - pPlay->m_var.dwTgt_uiSampleTimeInMs_internal;
							if (iMax_toInMs > iElapseInMs)  iMax_toInMs -= iElapseInMs;
							else  iMax_toInMs = 0;
							//							
							//int	nQNodes_left  =  pPlay->q2.qs[0].uiQNodes  +  pPlay->q2.qs[1].uiQNodes;
							//
							//int		nAheadInMs  =  0;
							//int		nAheadInMs_min_qNodes_left  =  0;	//  2015/03/02




							//
							int	nReason = 0;

							//
							if (pPlay->usFps > 30) {
								//MAX_interval_videoOnly_1Node
							}



							//								
							//  2015/02/20									
							//if  (  pPkt->head.uiPts  &&  fpsInfo.fps  >  MIN_realFps_pts  &&  pPlayer->video.usFps  >  MIN_fps_pts  )  
							if (pPkt->head.uiPts && pPlayer->video.usFps > MIN_fps_pts)
							{
								//
								//  2016/04/10
								BOOL  bAccurate = FALSE;
								if (  //pPlayer->video.m_var.status.fpsInfo..fps_real  >=  15
									pPlay->usFps >= 15
									//&&  pPlayer->video.m_var.lowLatency.mql.mql_ok  
									)
								{
									bAccurate = TRUE;
								}
								if (pPlay->m_var.lowLatency.bAccurate != bAccurate) {
									pPlay->m_var.lowLatency.bAccurate = bAccurate;
								}

								//
								DWORD  needed_toPlay = 0;
								DWORD  elapse_real = 0;
								{
									//
									if (bAccurate) {
										//
#ifdef  __DEBUG__
		//showInfo_open0(  0,  0,  _T(  "bAccurate"  )  );
#endif
//
#if  10
										needed_toPlay = pPkt->head.uiSampleTimeInMs - pPlay->m_var.lowLatency.calc.uiSampleTimeInMs_start1;	//(  pPkt->head.uiPts  -  pPlay->m_var.lowLatency.calc.uiPts_start  )  *  fpsInfo.avgTimePerFrameInMs_real;	//  (  pPkt->head.uiPts  -  pPlay->m_var.status.uiPts_last  )  *  fpsInfo.avgTimePerFrameInMs;										
										elapse_real = dwTickCnt_internal - pPlay->m_var.lowLatency.calc.dwTickCnt_start2;  //dwTgt_internal  -  pPlay->m_var.status.dwLastTgt_postToDraw;											  
#endif
#if  0
										needed_toPlay = (pPkt->head.uiSampleTimeInMs - pPlay->m_var.status.iSampleTimeInMs_last + fpsInfo.avgTimePerFrameInMs_real) / 2;
										elapse_real = dwTgt_internal - pPlay->m_var.status.dwLastTickCnt_postToDraw;
#endif
										//
									}
									else {
										needed_toPlay = (pPkt->head.uiPts - pPlay->m_var.status.uiPts_last) * fpsInfo.avgTimePerFrameInMs;
										elapse_real = dwTickCnt_internal - pPlay->m_var.status.dwLastTickCnt_postToDraw;
									}
									//
									//if  (  elapse_real  +  pPlay->m_var.lowLatency.ah.totalAh1  >  needed_toPlay  +  pPlay->m_var.lowLatency.ah.totalDelay1  )  
									if (elapse_real > needed_toPlay)
									{
										//
#ifdef  __DEBUG__
#if  0
 //if  (  pPlayer->idInfo_recorder.ui64Id  )  
										{
											int  ii = 1;
											_sntprintf(tBuf, mycountof(tBuf), _T("playVideo: %I64u, elapse %d  +  totalAh %d > needed_toPlay %d  +  totalDelay %d"), pPlayer->idInfo_recorder.ui64Id, elapse_real, pPlay->m_var.lowLatency.ah.totalAh, needed_toPlay, pPlay->m_var.lowLatency.ah.nDelay);
											showInfo_open0(0, 0, tBuf);
										}
#endif
#endif
										//
										//pPlay->m_var.lowLatency.bNeedAdjust3  =  true;
										//
										dwToInMs = 0;
										nReason = 1;
									}
									else {
										//dwToInMs  =  needed_toPlay  -  elapse_real  -  pPlay->m_var.lowLatency.ah.totalAh1  +  pPlay->m_var.lowLatency.ah.totalDelay1;
										dwToInMs = needed_toPlay - elapse_real;

										//
										if (dwToInMs > pPlay->m_var.status.fpsInfo.avgTimePerFrameInMs * 5) {
											pPlay->m_var.lowLatency.bNeedAdjust3 = true;	//
											//
											if (pPlayer->idInfo_recorder.ui64Id) {
												_sntprintf(tBuf, mycountof(tBuf), _T("playVideo %I64u: to %dms, 乱了，重新复位一下 "), pPlayer->idInfo_recorder.ui64Id, dwToInMs);
												//showInfo_open0(0, 0, tBuf);
											}
										}
										else {
											if (pProcInfo->cfg.debugStatusInfo.ucbShowToDrawStatus) {
												if (0) {
													if (pPlayer->idInfo_recorder.ui64Id) {
														_sntprintf(tBuf, mycountof(tBuf), _T("playVideo %I64u: to %dms"), pPlayer->idInfo_recorder.ui64Id, dwToInMs);
														showInfo_open0(0, 0, tBuf);
													}
												}
											}
										}


										//
									}
									//
#ifdef  __DEBUG__
		//  2016/04/11
		//pPlay->m_var.lowLatency.dwToInMs_1740  =  dwToInMs;
#endif
								}
								//
								//int  max_to  =  fpsInfo.avgTimePerFrameInMs  *  1.1;	//  +  3;									
								int  max_to = fpsInfo.avgTimePerFrameInMs * 3;//  +1;//  *1.2;	//  +  3;
								if (pPlay->usFps > 30) {
									max_to = fpsInfo.avgTimePerFrameInMs + 1;
								}
								if (dwToInMs > max_to) {
									dwToInMs = max_to;
								}



								//
#ifdef  __DEBUG__
								if (pProcInfo->cfg.debugStatusInfo.ucbPrint_lPktId_alloc) {
									if (pPlayer->idInfo_recorder.ui64Id == 0) {
										_sntprintf(tBuf, mycountof(tBuf), _T("%s: %I64u: nQNodes %d. fps_avg %.3f, lAlloc %d, pts %d, dwTo %d, l2207"), pPlay->q2.cfg.name, pPlayer->idInfo_recorder.ui64Id, nQNodes_left, fpsInfo.fps_real, pPkt->lPktId_alloc, pPkt->head.uiPts, dwToInMs);
										showInfo_open(0, 0, 0, tBuf);
									}
								}
#endif 


								//
							}		//  >10fps
							else {	//  low fps video


								//  2013/04/08
								int	MAX_interval_videoOnly_1Node = 600;		//  120		//  200	//  1200
								//
								int  MAX_interval_videoOnly_manyNodes = 80;		//  160		//  80
								//
								int  MAX_dwToInMs_videoOnly = 40;		//  2013/08/02. 最慢按25fps算

								//
								if (bNoAudio) {


									//	
									float  f = 0.3;
									if (nQNodes_left > 0) {
										if (pPlay->m_var.uiSampleTimeInMs_newRecvd > pPkt->head.uiSampleTimeInMs + MAX_interval_videoOnly_manyNodes) {
											f = 0.17;
										}
									}
									else {
										if (pPlay->m_var.uiSampleTimeInMs_newRecvd > pPkt->head.uiSampleTimeInMs + MAX_interval_videoOnly_1Node) {
											f = 0.05;		//  把过老的数据扔出去									
										}
									}
									//									
									dwToInMs = pPkt->head.uiSampleTimeInMs - pPlay->m_var.uiSampleTimeInMs;
									//
									if (dwToInMs > iElapseInMs)  dwToInMs -= iElapseInMs;
									else  dwToInMs = 0;
									//										
									int  iMax_dwToInMs_videoOnly = min(MAX_dwToInMs_videoOnly, fpsInfo.avgTimePerFrameInMs);

									//  
									if (dwToInMs > iMax_dwToInMs_videoOnly)  dwToInMs = iMax_dwToInMs_videoOnly + (dwToInMs - iMax_dwToInMs_videoOnly) * f;

									//									 
									//
									if (nInterval_pkt > fpsInfo.avgTimePerFrameInMs + 1) {
										int  iVal = nInterval_pkt - (fpsInfo.avgTimePerFrameInMs + 1);
										for (; iVal; iVal--) {
											if (dwToInMs)  dwToInMs--;
											if (iMax_toInMs)  iMax_toInMs--;
										}
									}
									else  if (nInterval_pkt < fpsInfo.avgTimePerFrameInMs) {
										if (nQNodes_left < pPlayer->video.q2.cfg.uiMaxQNodes * 2 / 3) {
											dwToInMs++;
										}
									}

									//
									int  iMin = min(iMax_toInMs, fpsInfo.avgTimePerFrameInMs - 3);
									int  iMax = min(iMax_toInMs, fpsInfo.avgTimePerFrameInMs + 2);

									if (dwToInMs < iMin)  dwToInMs = iMin;
									else  if (dwToInMs > iMax) {
										dwToInMs = iMax;
									}

									//  2015/06/20
									int  tmp_fps_2 = fpsInfo.fps_real / 2;	//  以半秒为界来衰减
									if (nQNodes_left > tmp_fps_2) {
										//
										if (tmp_fps_2 <= 0)  tmp_fps_2 = 1;
										int  n = nQNodes_left / tmp_fps_2;
										//
										if (n <= 0)  n = 1;
										dwToInMs /= n;
									}

									//											 
									if (dwToInMs > 1)  dwToInMs -= 1;

									//
									if (pProcInfo->cfg.debugStatusInfo.ucbShowPreDrawStatus) {
										qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, tWhere, _T(""), _T("fps_real %.2f. nNodes_left %d, dwToInMs %d"),
											fpsInfo.fps_real, nQNodes_left, dwToInMs);
									}

								}

								else {

									//							
									getSampleTimeInMs_needed(pProcInfo, uiSampleTimeInMs_audio, dwTickCnt_syncAv_audio, pPlay->m_var.uiSampleTimeInMs, pPlay->m_var.dwTgt_uiSampleTimeInMs_internal, dwTickCnt_syncAv_now, dwTickCnt_internal, pPkt->head.uiSampleTimeInMs, &dwToInMs);
									//
									if (nInterval_pkt > fpsInfo.avgTimePerFrameInMs + 1) {
										int  iVal = nInterval_pkt - (fpsInfo.avgTimePerFrameInMs + 1);
										for (; iVal; iVal--) {
											if (dwToInMs)  dwToInMs--;
											if (iMax_toInMs)  iMax_toInMs--;
										}
									}
									else  if (nInterval_pkt < fpsInfo.avgTimePerFrameInMs) {
										if (nQNodes_left < pPlayer->video.q2.cfg.uiMaxQNodes * 2 / 3) {
											dwToInMs++;
										}
									}
									//
									int  iMin = min(iMax_toInMs, fpsInfo.avgTimePerFrameInMs - 3);
									int  iMax = min(iMax_toInMs, fpsInfo.avgTimePerFrameInMs + 2);

									if (dwToInMs < iMin) {
										int  iAhead = 0;

										if (nQNodes_left) {
											if (iMin) {
												iAhead = 1;
											}
										}
										dwToInMs = iMin - iAhead;
									}
									else  if (dwToInMs > iMax) {
										int  iDelay = 0;

										//
										if (nQNodes_left < pPlay->q2.cfg.uiMaxQNodes * 2 * 2 / 3) {

											if (dwToInMs > fpsInfo.avgTimePerFrameInMs + 3) {
												iDelay = 2;
											}
											else {
												iDelay = 1;
											}
										}

										dwToInMs = iMax + iDelay;
									}
								}
							}

							//								
							dwTgt_internal_toPlay = dwTickCnt_internal + dwToInMs;

							//
#ifdef  __DEBUG__
							if (0) {
								_sntprintf(tBuf, mycountof(tBuf), _T("l2357: internal_toPlay %d,internal %d,to %d"), dwTgt_internal_toPlay, dwTickCnt_internal, dwToInMs);
								showInfo_open(0, 0, 0, tBuf);
							}
#endif 

							//								
							if (pProcInfo->cfg.debugStatusInfo.ucbShowPreDrawStatus) {
								qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, tWhere, _T(""), _T("pkt.sm %d, play.sm %d, play.sm_new %d. nQNodes_left %d,  mql %d, dwToInMs %d. bAdjust %d, nReason %d"),
									pPkt->head.uiSampleTimeInMs, pPlay->m_var.uiSampleTimeInMs, pPlay->m_var.uiSampleTimeInMs_newRecvd,
									nQNodes_left,
									pPlay->m_var.lowLatency.mql.mql_1s.mql,
									dwToInMs,
									pPlay->m_var.lowLatency.bNeedAdjust3, nReason);
							}
						}

						//
						

						//
						if (dwTgt_internal_toPlay <= dwTickCnt_internal + CONST_video_skippedInterval) {
							//  2012/02/07
							//  pPkt->debugInfo.dwTickCnt_postToDraw  =  M_GetTickCount_video(  tickObj  );
							if (dwTgt_internal_toPlay > dwTickCnt_internal)  dwToInMs = dwTgt_internal_toPlay - dwTickCnt_internal;
							else  dwToInMs = 0;		//  2013/09/09						   
							//
							pPlay->m_var.lowLatency.dwToInMs_toPostDraw = dwToInMs;	//  2013/09/09
							//
							bPktRedirected = FALSE;
							postToDraw(pProcInfo, pPkt->head.uiTranNo_openAvDev, pPkt, pktLen, &bPktRedirected, pPkt->uiCapType, pPkt->iIndex_capBmp, &pPlayer->idInfo_recorder, nPkts_left, &pPkt->idInfo_peer, pPkt->iTaskId, pPkt->hWnd_task, &playerId, _T("dwTgt_internal_toPlay  <=  dwTgt_internal  +  CONST_video_skippedInterval"));
							if (bPktRedirected) {
								mallocObj_tmpPkts[iIndex].detach();

							}

							//  2009/05/26
							pPlay->m_var.uiSampleTimeInMs = pPkt->head.uiSampleTimeInMs;
							pPlay->m_var.dwTgt_uiSampleTimeInMs_internal = dwTickCnt_internal;	//  M_GetTickCount_video(  tickObj  );
							pPlay->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv = myGetTickCount(mynull);
							//
							player_get_fps(&pPlayer->idInfo_recorder, pPlayer->video.usFps, pPkt->head.uiSampleTimeInMs, &fpsInfo, pPlayer->video.q2.cfg.name);	//  2014/07/03

							break;
						}

						//
						if (0) {
							showInfo_open(0, 0, 0, _T("l2410"));
						}

						//
						dwToInMs = dwTgt_internal_toPlay - dwTickCnt_internal;

						int nAHead = CONST_video_ahead;
#if  0
						//  2023/04/28
						int tmp_nQNodes = getQ2Nodes(&pPlayer->video.q2) + nPkts_left;
						int n1 = tmp_nQNodes / 5;
						int mm = n1 * n1;
						//												
						//
						if (fpsInfo.fps_real > 40) {
							mm = mm * n1;
						}
						//
						nAHead += mm;
#endif

						//  2012/01/28, 有一个很小的提前量,因为从恢复休眠到显示,也需要时间
						if (dwToInMs > nAHead) {
							//
							accurateSleep(dwToInMs - nAHead, _T(""));

						}


						//  if  (  bPktLeft  )  
						{
							//
							//  pPkt->debugInfo.dwTickCnt_postToDraw  =  M_GetTickCount_video(  tickObj  );
							pPlay->m_var.lowLatency.dwToInMs_toPostDraw = dwToInMs;
							//
							bPktRedirected = FALSE;
							postToDraw(pProcInfo, pPkt->head.uiTranNo_openAvDev, pPkt, pktLen, &bPktRedirected, pPkt->uiCapType, pPkt->iIndex_capBmp, &pPlayer->idInfo_recorder, nPkts_left, &pPkt->idInfo_peer, pPkt->iTaskId, pPkt->hWnd_task, &playerId, _T("after accurateSleep"));
							if (bPktRedirected) {
								mallocObj_tmpPkts[iIndex].detach();
							}
							//  bPktLeft  =  FALSE;

							//  2009/05/26
							pPlay->m_var.uiSampleTimeInMs = pPkt->head.uiSampleTimeInMs;
							pPlay->m_var.dwTgt_uiSampleTimeInMs_internal = M_GetTgt_video(tickObj);	//  dwTickCnt_toPlay;
							pPlay->m_var.dwTickCnt_uiSampleTimeInMs_syncRecv = myGetTickCount(nullptr);
							//
							player_get_fps(&pPlayer->idInfo_recorder, pPlayer->video.usFps, pPkt->head.uiSampleTimeInMs, &fpsInfo, pPlayer->video.q2.cfg.name);	//  2014/07/03

						}
						break;				   //  一个pkt被播放完了					   
					}
				}

				//
#ifdef  __DEBUG__
				for (int i = 0; i < nPkts; i++) {
					QY_MEMORY	memory;
					if (mallocObj_tmpPkts[i].get(&memory))  continue;
					if (memory.m_pBuf && memory.uiBufSize) {
						M_pkt_showNo(pkts[i], _T("playVideo . free"));
					}
				}
#endif

			}
		}

		//
		continue;
	}

	traceLogA((char*)"mcThreadProc_playVideo will quit");

errLabel:

	pPlay->bRunning = FALSE;

	//
	pPlay->doPre_toPlayVideo.bQuit = true;
	waitForObject(&pPlay->doPre_toPlayVideo.hThread, 20000);
	if (pPlay->doPre_toPlayVideo.hThread) {
		showInfo_open0(0, 0, _T("playVideo: waitForObject failed"));
	}




	//
	if (ctx_fillData_d3d.pImgDataBuf) {
		MACRO_safeFree(ctx_fillData_d3d.pImgDataBuf);
	}

	//
	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s, %I64u ends."), pPlayer->video.q2.cfg.name, pPlayer->idInfo_recorder.ui64Id);

	traceLogA((char*)"playVideo %S leaves", pPlay->q2.cfg.name);

	return  0;

}







