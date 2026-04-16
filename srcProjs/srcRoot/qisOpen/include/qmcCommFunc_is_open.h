
#ifndef  __qmcCommFunc_is_open_h__
#define  __qmcCommFunc_is_open_h__	//  {

#include	"qnmCommProc_is_open.h"
#include	"qy_qBuf2.h"
#include	"ancPktProcessPublic.h"




//
//  2012/02/24
typedef  struct  __playAudioProcInfo_t							{
				 MACRO_qyQThreadProcInfo_common

				 //
				 QY_qBuf2 *qBuf2;

				 //
				 unsigned  int									uiTranNo;										//  2009/04/27
				 
				 //
				 QY_AUDIO_HEADER								ah;												//  2010/06/17

				 AUDIO_PLAY_CFG									playCfg;										//  2009/06/03

				 //  2013/05/24
				 TCHAR											playbackDevDesc[48];							//  ??????????

				 //  2017/06/15
				 unsigned  int									uiPlayType;
				 DWORD											dwLastTickCnt_startPlayer;

				 //
				 struct											{
					 void  *									pVoePlay;
				 }												webRtc;

				 //
#if  0
				 QY_Q2											aecPlayQ2;						 
				 struct											{
					 //
					 DWORD										dwTgt_start1;
					 //
					 int										mql;
					 //
				 }												aec_var;
#endif
				 
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

					 //  
					 int										nTimes_noAudioData;

					 BOOL										bVideoReady;

					 //  2012/02/19
					 unsigned  int								uiTimeInMs_audio_remains;						//  ???????????
					 DWORD										dwTickCnt_GetCurrentPosition;					//  ??GetCurrentPosition???

					 //  2015/07/29
					 DWORD										dwTickCnt_beforePlay;
					 
					 //
					 int										nTimes_my_inStream;                             //  调用了几次. 2026/04/04

				 }												m_var;
				 
				 //				
				 BOOL											bNeedStop_webRtc_my_inStream;					//  2018/06/16
				 
				 //
				 int											nTimes_noAudioData_webRtc;
				 
				 //
				 struct											{
					 //
					 unsigned  int								uiBufSize;  
					 char								*		pBuf;
					 //
					 char								*		pLeft;											//  =	NULL;									//  2009/04/27
					 unsigned  int								nLeft;											//	=	0;

					 //
					 DWORD										dwTickCnt_lastAudioData3;

				 }												cache;

				 //  2017/06/22				 
				 struct											{
					 int										mql;
					 int										xql;
					 //
					 int										last_mql;
					 int										last_xql;
					 //
					 int										last_dangerousMql;
					 DWORD										dwTickCnt_last_dangerousMql;

					 //
					 DWORD										dwTgt_start1;

					 //
					 BOOL										bNeedAdjust;
					 DWORD										dwTickCnt_last_adjust;

					 //  2017/10/13
					 struct										{
						 unsigned  int							uiPts_lastRecvd;
						 unsigned  int							nErr_ptsMissed;
					 }											ptsInfo;
					 //
					 struct										{
						 int									nBytes_ptks;
						 int									n_pkts;
						 //
						 int									nAvg_pkt_inMs;
					 }											avg_pkt;
					 //
					 int										xql_ok;
					 int										min_mql_ok;
					 int										max_mql_ok;

				 }												lowLatency;


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
typedef  struct  __playV_mql_t									{
							 //
							 DWORD								dwTgt_start;

							 //
							 int								mql;
							 int								xql;
							 
							 //
							 int								last_mql;										//  last_min_qNodes_left;
							 int								last_xql;
							 							 
							 //
							 BOOL								bNeedReset;
					
}  PLAY_v_mql;


//  2025/11/30
typedef  struct  __doPre_toPlayVideo_t {
							QY_Q2								q2;
							bool								bQInited;
							//
							bool								bQuit;

							//
							HANDLE								hThread;
							DWORD								dwThreadId;

							//
}				 DoPre_toPlayVideo;


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
				 unsigned  int									uiPlayType;
				 DWORD											dwLastTickCnt_startPlayer;
				 
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

						 //
						 struct									{

							 //
							 int								mql_ok;
							 int								mql_big_ok;
							 						
							 //
							 PLAY_v_mql							mql_1s;
							 //mql_2s
							 PLAY_v_mql							mql_3s;
							 //, mql_5s;
							 PLAY_v_mql							mql_8s;
							 //mql_10s;
						 }										mql;
						 
						 //
						 BOOL									bNoAudio;										//  2016/04/10
						 //
						 BOOL									bAccurate;										//  2016/04/11

						 //
						 BOOL									bNeedAdjust3;									//  2015/09/13			
						 struct									{
							 //
							 int								nAh;
							 //
							 int								nDelay;
							 //
						 }										ah;
						 
						 //
						 int									nTimes_sleep;
						 DWORD									dwToInMs_toPostDraw;							//  2012/02/07

						 //
						 struct									{
							 unsigned  int						uiPts_start;

							 //
							 DWORD								dwTickCnt_start2;
							 unsigned  int						uiSampleTimeInMs_start1;
							 //
							 int								last_mql;
							 //
						 }										calc;

						 //
						 struct									{
							 //
							 time_t								tStart_toChk_st_start1;
							 //
							 unsigned  int						nNeedAhead;										//  根据mql-mql_ok得出的需要将st_start提前nNeedAhead次
							 unsigned  int						nTimes_ahead;

							 //
							 unsigned  int						nNeedDelay;
							 unsigned  int						nTimes_delay;

						 }										chk_st_start1;

						 //
						 struct {
							 //
							 unsigned  int						nTimes;
						 }										stat_noMsgAndWait;

						 //
						 TCHAR									tBuf[128];

					 }											lowLatency;


					 //
					 struct										{
						 DWORD									dwLastTickCnt_postToDraw;						//  2012/01/26
						 int									nInterval_real_postToDraw;
						 //
						 int									iSampleTimeInMs_last;
						 unsigned  int							uiPts_last;										//  2015/02/19
						 
						 //
						 BOOL									bNoMsgAndWait;									//  2012/03/01
						 //
						 struct									{
							 BOOL								bNeedFill;										//  2014/11/25
							 //
							 PARAM_fillD3d						param0,  param1;
							 //
							 BOOL								bFilled_d3dData;								//  2013/08/08

							 //
							 uint								uiSeqNo_lastRender;

						 }										fillD3d;						
						 //							
						 unsigned  char							ucSkipped_for_d3dData;							//  2013/09/09
						 
						 //  2015/02/25
						 TMP_fps_info							fpsInfo;										//  2015/09/10

						 //
					 }											status;

					 //  2024/01/01
					 int										totalPkts_postToDraw;
					 int										totalPkts_lastOk_postToDraw;

					 //
					 DWORD										dwTickCnt_lastData;								// 

					 //
					 int										nErr_pktIsSharedTex_tex2not;


					 //
				 }												m_var;

				 QY_Q2											displayQ2;										//  2009/07/25
				 unsigned  char									ucbDisplayQInited;					

				 //
				 DoPre_toPlayVideo								doPre_toPlayVideo;

				 //
}		 PLAY_VIDEO_procInfo;



//


typedef  struct  __qyPlayer_t									{												//  2009/05/02
				 QY_MESSENGER_ID								idInfo_recorder;								//  

				 unsigned  int									uiSampleTimeInMs_start;							//  2009/05/27

				 PLAY_AUDIO_procInfo							audio;
				 PLAY_VIDEO_procInfo							video;

				 int											iTaskId;										//  2009/09/17

				 //
				 PLAYER_ID										playerId;

				 //  2014/12/10
				 DWORD											dwLastTickCnt_doApplyForPlayer;					//  2014/12/10

				 //
				 bool											bNeedEnd1;										//  2025/05/29

				 //
				 struct {
					 unsigned  long								ulbPlayerErr : 1;								//  
					 //
					 unsigned  long								ulbAQuit : 1;									//  
					 unsigned  long								ulbVQuit : 1;									//  

				 }												status;

				 //
}		 QY_PLAYER;


//
int fillSilence(int wBits, char* buf, int bufLen);

//
int  my_inStream(void* p0, void* p1, void* p2);
//  pPlayer, char * buf, int bufLen

int my_inStream4_toMix(void* p0, void* p1, void* p2, void* p3);
//pProcInfo,index_source,char* buf,int size
// 	return  nRead;





//
BOOL  bPlayerOk(QY_PLAYER* pPlayer,  Param_dbg  *  pParam);


//


//
#endif  //  }



