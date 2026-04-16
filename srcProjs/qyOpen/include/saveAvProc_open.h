

#ifndef  __saveAvProc_open_h__
#define  __saveAvProc_open_h__	//  {

//
#include	<time.h>
//
#include	"qySyncObj.h"
#include	"genericqueue.h"
#include	"qyq2.h"

//
#include	"saveAvProcDefs_open.h"


//
typedef  int  (*PF_setGuiOpen_saveAv)(QIS_guiOpen_saveAv* pGuiOpen);
typedef  int (*PF_getSize_SAVE_av_procInfo)();

//
#define		CONST_bufSize_saveVideoPkt		1024  *  1024


//
#define		M_saveAvPkt_commonMems										\
				 unsigned  int				uiMediaType;				\
				 int						index_activeMems_from;		\
				 QY_MESSENGER_ID			idInfo;						\
				 unsigned  int				uiTranNo_openAvDev;			\
				 bool						bAudio;


//
typedef  struct  __saveVideoPkt_t {
	M_saveAvPkt_commonMems

	//		
	int							iFourcc;

	//
	bool						bSpsPps;

	//
	unsigned  int				uiSampleTimeInMs;					//  2009/05/02

	//  2015/01/15
	unsigned  int				uiPts;								//  2015/01/15

	//
	unsigned  int				uiLen;
	char						buf[CONST_bufSize_saveVideoPkt];

}		 SAVE_video_pkt;


//  2015/05/19
//
typedef  struct  __saveAudioPkt_t {
	M_saveAvPkt_commonMems

	//		
	unsigned  short				wFormatTag;

	//
	unsigned  int				uiSampleTimeInMs;					//  2009/05/02

	//  2015/01/15
	unsigned  int				uiPts;								//  2015/01/15

	//
	unsigned  int				uiLen;
	char						buf[CONST_bufSize_saveVideoPkt];

}		 SAVE_audio_pkt;


//
typedef  union  __saveAvPktU_t {
	struct {
		M_saveAvPkt_commonMems
	}							common;
	SAVE_audio_pkt				aPkt;
	SAVE_video_pkt				vPkt;
}		 SAVE_av_pktU;




//  2014/08/04
typedef  struct  __saveAvProcInfo_t								{
				 //
				 QY_Q2											q2;
				 //
				 bool											bQInited;
				 HANDLE											hThread;
				 DWORD											dwThreadId;
				 bool											bQuit;
				 bool											bRunning;


				 //
				 bool											bResource;

				 //
				 bool											bRecord_conf;			//  
				 //
				 bool											bRecord_trans;			//  2026/04/13

				 //
				 bool											bLive;
				 TCHAR											liveUrl[256];
				 __int64										meetingId;

				 //
				 unsigned  __int64								peerId;

				 //
				 TCHAR											tDir[256];
				 TCHAR											pureFileName_prefix[256];
				 TCHAR											fullOutputFileName[256];
				 TCHAR											ffmpegPath[256];

				 //
				 struct {

				 }												audio;


				 //
				 struct											{
					 //
					 QY_MESSENGER_ID							idInfo;
					 unsigned  int								uiTranNo_openAvDev;
				 
					 //
					 unsigned  short							usMaxFps_toShareBmp;

					 //
					 DWORD										dwLastTickCnt_notification;

					 //
					 int										frame_cnt;
					 
				 }												video;	 

				 
				 //  2014/09/07
				 struct											{
					 DWORD										dwLastTickCnt_showInfo_notSave;
					 //
					 unsigned  char								ucbSave_lastVal;
				 }												status;

				 //
				 int											iType;
				 int											index;
				 TCHAR											tag[32];

				 //
}		 SAVE_av_procInfo;


//
#define		CONST_saverType_conf								1
#define		CONST_saverType_trans								2


//
typedef  struct  __ctxMc_saveAv_t {
	//CTX_MC_thread							common;

	//  2015/05/09
	unsigned  char* pBuf_forSaving;
	unsigned  int							uiBufSize_pBuf;

	//
	bool									bSaveAvTest;

	//
}		 CTX_mc_saveAv;


//
#define		CONST_cfgName_saveAvTest				_T(  "saveAvTest")


#endif  //  }


