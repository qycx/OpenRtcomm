
#ifndef  __qmcCommFunc_is_open_h__
#define  __qmcCommFunc_is_open_h__	//  {

//
#include	"qmcStruct_defs.h"


//
#if  0	//  2012/02/19
	#define		MACRO_getnWaitingInMs_audioPkt(  pkt_uiSampleTimeInMs,  player_audio  )		(  pkt_uiSampleTimeInMs  -  player_audio.m_var.uiSampleTimeInMs  +  player_audio.m_var.dwTickCnt_uiSampleTimeInMs  -  GetTickCount(  )  )
	#define		MACRO_getnWaitingInMs_audio(  player_audio  )								(  (  player_audio  ).m_var.uiSampleTimeInMs_newRecvd  -  (  player_audio  ).m_var.uiSampleTimeInMs  +  (  player_audio  ).m_var.dwTickCnt_uiSampleTimeInMs  -  GetTickCount(  )  )
#endif

#define		MACRO_getnWaitingInMs_audioPkt_internal(  pkt_uiSampleTimeInMs,  player_audio,  dwTickCnt_now  )		(  pkt_uiSampleTimeInMs  -  player_audio.m_var.uiSampleTimeInMs  +  player_audio.m_var.dwTickCnt_uiSampleTimeInMs_internal  -  dwTickCnt_now  )
#define		MACRO_getnWaitingInMs_audio_internal(  player_audio,  dwTickCnt_now  )								(  (  player_audio  ).m_var.uiSampleTimeInMs_newRecvd  -  (  player_audio  ).m_var.uiSampleTimeInMs  +  (  player_audio  ).m_var.dwTickCnt_uiSampleTimeInMs_internal  -  dwTickCnt_now  )
//
#define		MACRO_getnWaitingInMs_audioPkt_syncRecv(  pkt_uiSampleTimeInMs,  player_audio,  dwTickCnt_now  )		(  pkt_uiSampleTimeInMs  -  player_audio.m_var.uiSampleTimeInMs  +  player_audio.m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  -  dwTickCnt_now  )
#define		MACRO_getnWaitingInMs_audio_syncRecv(  player_audio,  dwTickCnt_now  )								(  (  player_audio  ).m_var.uiSampleTimeInMs_newRecvd  -  (  player_audio  ).m_var.uiSampleTimeInMs  +  (  player_audio  ).m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  -  dwTickCnt_now  )


//
//  2012/02/24
typedef  struct  __playAudioProcInfo_t							{
				 MACRO_qyQThreadProcInfo_common

				 unsigned  int									uiTranNo;										//  2009/04/27
				 //  unsigned  short							usIndex;										//  2009/04/27
				 //

				 QY_AUDIO_HEADER								ah;												//  2010/06/17

				 AUDIO_PLAY_CFG									playCfg;										//  2009/06/03

				 //  2013/05/24
				 TCHAR											playbackDevDesc[48];							//  ??????????

				 //  2017/02/28
				 unsigned  int									uiPlayType;
				 struct											{
					 BOOL										bStarted;										//  如果初始化执行完毕，则设置bStarted=1.否则直接清理，bStarted因此保留为0
					 BOOL										bWaitForStop;									//  运行时，如果出错或需要退出，设置此值
				 }												play_webRtc;									//  2017/02/28
				 //
				 struct											{
					 unsigned  int								uiSampleTimeInMs;								//  2009/05/03
					 unsigned  int								dwTickCnt_uiSampleTimeInMs_internal;			//  2012/02/24. audioPlayer????
					 unsigned  int								dwTickCnt_uiSampleTimeInMs_syncAv;				//  2012/02/18. ?video???
					 
					 //
					 unsigned  int								dwTickCnt_uiSampleTimeInMs_syncRecv;			//  2012/02/24. ?newRecv????, ????????
					 
					 //
					 unsigned  int								uiSampleTimeInMs_newRecvd;						//  2009/05/03
					 unsigned  int								dwTickCnt_uiSampleTimeInMs_newRecvd;  

					 //  int									nTimes_toFillSilence;
					 int										nTimes_noAudioData;

					 BOOL										bVideoReady;

					 //  2012/02/19
					 unsigned  int								uiTimeInMs_audio_remains;						//  ???????????
					 DWORD										dwTickCnt_GetCurrentPosition;					//  ??GetCurrentPosition???

					 //  2015/07/29
					 DWORD										dwTickCnt_beforePlay;

				 }												m_var;

}		 PLAY_AUDIO_procInfo;



//
//
typedef  struct  __param_fillD3d_t								{
					 DWORD										nIntervalInMs_fillData;							
					 BOOL										bFailed_getTextureInfo_toFill;					//  2014/11/25
					 //BOOL										bFailed_devCtx_stillUsed;						//  2014/11/25
					 //BOOL										bFailed_FinishCommandList;

}		 PARAM_fillD3d;


//
//
typedef  struct  __tmp_fps_info_t								{		 	
				 int											iCount;											//  帧数.2014/07/02.用d3d的get_fps( )来得到player的fps.然后计算帧间隔，限制各时间在realInterval - 3, realInterval + 3间。fps放在player里，在playList里显示出来	
				 DWORD											curTimeInMs;
				 DWORD											lastTimeInMs;
				 float											fps_real;
				 //
				 DWORD											avgTimePerFrameInMs;
				 //
				 DWORD											avgTimePerFrameInMs_real;						//  2015/09/10
				 
}		 TMP_fps_info;


//
//
typedef  struct  __playVideoProcInfo_t							{												//  2009/05/02
				 MACRO_qyQThreadProcInfo_common

				 //
				 unsigned  int									uiTranNo;										//  2009/04/27
				 
				 //
				 QY_VIDEO_HEADER								vh;
				 unsigned  short								usFps;											//  2015/02/20. 这个来自于传输过来的策略。


				 //
				 struct											{
					 unsigned  int								uiSampleTimeInMs;								//  2009/05/03
					 unsigned  int								dwTgt_uiSampleTimeInMs_internal;
					 //
					 unsigned  int								dwTickCnt_uiSampleTimeInMs_syncRecv;

					 unsigned  int								uiSampleTimeInMs_newRecvd;						//  2009/05/03
					 unsigned  int								dwTickCnt_uiSampleTimeInMs_newRecvd;  
					 
					 //  2015/09/30
					 unsigned  short							usPktResType;									//  2015/09/30. 
					 
					 //
					 //  2015/02/20
					 //
					 HWND										hWnd_display;									//  2009/07/25
					 unsigned  char								ucbDisplayAllFrames;							//  2009/07/25

					 //
					 TCHAR										tWhere[64];										//  2015/09/13

					 //
					 struct										{
						 struct									{
							 DWORD								dwTgt_start1;
							 int								mql;
							 int								xql;
							 
							 //
							 int								last_mql;										//  last_min_qNodes_left;
							 int								last_xql;

							 //
							 int								mql_ok;
							 int								mql_big_ok;
							 int								xql_ok;
							 							 
							 //
							 BOOL								bNeedReset;
						 }										mql;
						 
						 //
						 BOOL									bNoAudio;										//  2016/04/10
						 //
						 BOOL									bAccurate;										//  2016/04/11

						 //
						 BOOL									bNeedAdjust;									//  2015/09/13			
						 //
						 int									nAheadInMs;
						 int									nAheadInMs_gt_mql;								//  2015/03/02. greater than
						 int									nDelayInMs_lt_mql;								//  less than

						 //
						 int									nTimes_sleep;
						 DWORD									dwToInMs_toPostDraw;							//  2012/02/07
						 //
						 DWORD									dwToInMs_1740;

						 //
						 struct									{
							 unsigned  int						uiPts_start;
							 DWORD								dwTgt_start;
						 }										calc;


					 }											lowLatency;


					 //
					 struct										{
						 DWORD									dwLastTgt_postToDraw;							//  2012/01/26
						 int									nInterval_real_postToDraw;
						 //
						 int									iSampleTimeInMs_last;
						 unsigned  int							uiPts_last;										//  2015/02/19
						 
						 //
						 //int									last_nQNodes_postToDraw;						//  2015/09/16
						 
						 //
						 BOOL									bNoMsgAndWait;									//  2012/03/01
						 int									nTimes_wait;									//  2015/09/11
						 //
						 struct									{
							 BOOL								bNeedFill;										//  2014/11/25
							 //
							 PARAM_fillD3d						param0,  param1;
							 //
							 BOOL								bFilled_d3dData;								//  2013/08/08
						 }										fillD3d;						
						 //							
						 unsigned  char							ucSkipped_for_d3dData;							//  2013/09/09
						 
						 //  2015/02/25
						 TMP_fps_info							fpsInfo;										//  2015/09/10

						 //
					 }											status;

				 }												m_var;

				 QY_Q2											displayQ2;										//  2009/07/25
				 unsigned  char									ucbDisplayQInited;					

}		 PLAY_VIDEO_procInfo;



//


struct  __qyPlayer_t									{												//  2009/05/02
				 QY_MESSENGER_ID								idInfo_recorder;								//  

				 unsigned  int									uiSampleTimeInMs_start;							//  2009/05/27

				 PLAY_AUDIO_procInfo							audio;
				 PLAY_VIDEO_procInfo							video;

				 int											iTaskId;										//  2009/09/17

				 //
				 unsigned  int									uiTranNo_player;								//  2016/02/18


				 //  2014/12/10
				 DWORD											dwLastTickCnt_startPlayer;						//  2014/12/10

				 //  2017/02/21
				 BOOL											bLocalAv;

				 //
				 void									*		pProcInfo;

};


//
#include	"qmcStruct_defs.h"




//
#endif  //  }



