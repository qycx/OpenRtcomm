
#ifndef  __qnmCommProc_is_public_h__
#define  __qnmCommProc_is_public_h__	//  {

//
#include	"qmcStruct_defs.h"

//
#ifndef  __WINCE__		//  2010/04/18

	#if  0	//  2010/09/10
	#else		//  2012/06/28
		#define		CONST_bufSize_imDataContent							63  *  1024
		#define		CONST_bufSize_imStreamContent						63  *  1024						//  2008/03/22, 
		#define		CONST_bufSize_imLStream								(  900  +  32  )  *  1024		//  2008/03/22, 这个包应该比别的包略大一点，所以+32
		//
		//  #define		CONST_bufSize_transferFileDataResp				32  *  1024
		//  #define		CONST_bufSize_transferFileDataResp				64  *  1024						//  2010/12/05
		#define		CONST_bufSize_transferFileDataResp					128  *  1024					//  2014/07/13
		//
		#define		CONST_bufSize_transferVideoData						900  *  1024					//  2012/06/28. mediaSdk压缩出来的一个包就可能600k.cuda压缩出来的一个包可能700多k
		#define		CONST_bufSize_transferAudioData						512  *  1024					//  2009/05/20

		//  #define		CONST_bufSize_myDrawVideoData					8  *  1024  *  1024				//  2009/05/03
		#define		CONST_bufSize_myDrawVideoData_2k					8  *  1024  *  1024				//  2009/05/03
		#define		CONST_bufSize_myDrawVideoData_4k					36  *  1024  *  1024			//  2014/06/01. 4096X2304, 3840X2160

		#define		CONST_bufSize_myPlayAudioData						1  *  1024  *  1024
	#endif

#else

	#define		CONST_bufSize_imDataContent								63  *  1024
	#define		CONST_bufSize_imStreamContent							63  *  1024						//  2008/03/22, ÎªÁËÄÜ´«ÊäÊÓÆµÊý¾Ý£¬ÐèÒª´óÒ»µãµÄ»º´æ¡£
	#define		CONST_bufSize_imLStream									512  *  1024					//  2008/03/22, ÎªÁËÄÜ´«ÊäÊÓÆµÊý¾Ý£¬ÐèÒª´óÒ»µãµÄ»º´æ¡£
	//
	//  #define		CONST_bufSize_transferFileDataResp					32  *  1024						//  2010/12/05
	#define		CONST_bufSize_transferFileDataResp						64  *  1024
	//
	#define		CONST_bufSize_transferVideoData							512  *  1024
	#define		CONST_bufSize_transferAudioData							512  *  1024					//  2009/05/20

	#define		CONST_bufSize_myDrawVideoData							(  640  *  480  *  3  +  1024  )//  2009/05/03
	#define		CONST_bufSize_myPlayAudioData							512  *  1024

#endif


#include	"qyMessengerId.h"

//
//
typedef  struct  __transferAudioDataMemHead_t						{
				 //unsigned  short									usIndex_ii;							//  2013/07/18. 将被逐渐弃用

				 QY_MESSENGER_ID									idInfo;								//  会议时,发言人的id

				 //
				 unsigned  int										uiTranNo_openAvDev;					//  2013/08/04. 当会议参会人,断开会议,修改策略,重新参会时,需要有tn来标识不同的视频流,所以要加这个成员


				 struct												{
					 unsigned  int									uiTranNo_org;						//  Ô­Ê¼°üµÄ
                     DWORD											dwTickCnt_videoConferenceRecved;	//  ÊÓÆµ»áÒé·þÎñÆ÷ÊÕµ½µÄÊ±¼ä¡£ÓÃÀ´µ÷ÊÔºÍÁË½âÒôÆµ´«ÊäÐÔÄÜ¡£
				 }													tmpInternal;						//  ÁÙÊ±Ê¹ÓÃµÄ±äÁ¿£¬²»ÄÜÓÃÔÚÍ¨ÐÅÖÐ

				 unsigned  int										uiSampleTimeInMs;					//  2009/05/02
				 unsigned  int										ui_rtTimeLen;						//  2009/05/27
				 
				 //  2015/09/10
				 unsigned  int										uiPts;								//  2015/09/10
				 
				 //
				 unsigned  int										uiLen;
}		 TRANSFER_AUDIO_dataMemHead;


//
//
typedef  struct  __myDebugStep_t									{										
				 M_debugStep_common

				 //
				 unsigned  int										uiCnt_DMO_E_NOTACCEPTING;
				 unsigned  int										nErrs_ProcessInput;
				 unsigned  int										nErrs_ProcessOutput;
				 unsigned  int										nErrs_pOutputBuffers_index;
				 //
				 struct												{
					 BOOL											bInited;
					 BOOL											bStarted;
					 //
					 HRESULT										hr_GetState_beforeStart;
					 int											fs_beforeStart;
					 //
					 BOOL											bBeforeRun;
					 HRESULT										hr_run;
					 //
					 DWORD											dwTickCnt_startToQuit;
					 //
					 HRESULT										hr_GetState_beforeStop;
					 int											fs_beforeStop;
					 //
					 struct											{
						M_debugStep_common
						//
						HRESULT										hr;
						BOOL										bPktGot;
						BOOL										bParentQuit;						
						//
						BOOL										bFailed;
						//
					 }												FillBuffer;


					 //
				 }													fg;
				 //  2014/07/17
				 DEBUG_step_dec										dec;
				 //
				 int												iErr_thread;								//  2012/09/08
				 //
				 struct												{											//  2014/05/08
					TCHAR											tWhere[16];
					unsigned  int									uiStep;
				 }													showInfo;
				 //
}		 MY_DEBUG_STEP;


//
#define		MACRO_qyQThreadProcInfo_common		QY_Q2			q2;							\
												BOOL			bQInited;					\
												DWORD			dwThreadId;					\
												HANDLE			hThread;					\
												BOOL			bQuit;						\
												DWORD			dwTickCnt_start;			\
												BOOL			bRunning;					\
												MY_DEBUG_STEP	debugStep;


//
//
typedef  struct  __qyQThreadProcInfo_common_t					{
				 MACRO_qyQThreadProcInfo_common
}		 QY_qThreadProcInfo_common;

//
struct  __audioPlayCfg_t									{
				 unsigned  short									usMinTimeInMsOfAudioDataPlaying;					//  2009/06/14
				 //  
				 unsigned  short									usAudioDataAddedToPlayEveryTime;					//  2009/06/16
				 //
				 unsigned  short									usNotifyIntervalInMs_needMoreAudioData;				//  2009/06/14. = CONST_notifyInterval
				 //
				 unsigned  short									usMinTimeInMsToPlay;								//  2012/01/27
				 //
				 unsigned  short									usMaxTimeInMsToPlay;								//  2009/06/03
				 unsigned  short									usMaxTimeInMsToBeRemoved;							//  2009/06/03
};


//
typedef  struct  __audio_enc_params_t								{											//  2009/05/17

				 void										*		pAh;

}		 AUDIO_ENC_PARAMS;


//
//
struct  __audioCompressorCfg_t								{
				 //  unsigned  char										ucCompressors;								//  acm or dmo
				 AUDIO_COMPRESSOR_cfgCommon							common;
				 TCHAR												compressorName[64];							//  2009/05/16
				 
				 //
				 WAVEFORMATEX										wf_compress;
				 WAVEFORMATEX										wf_decompress_default;	

				 //
				 //  GUID												dmoClsid;

				 AUDIO_ENC_PARAMS									params;

				 //
				 unsigned  int										uiBytesRecorded_perBlockAlign;				//  ÒôÆµµÄ¶ÔÆëµ¥ÔªµÄ»º³å´óÐ¡

				 //  2014/05/20
				 struct												{
						//
						unsigned char								ucbSetOrgAudioFmt;

						//
						WAVEFORMATEX								wf_org_suggested;

				 }													dev;
				 
				 //
				 AUDIO_PLAY_CFG										playCfg;									//  2010/03/11

				 //
				 //  unsigned  int										uiRecordType;								//  2010/08/02

};




//
//  2009/05/17
typedef  struct  __myDmoInfo_t										{
				 void										*		pDmo;

				 DWORD												cbInputBuffer;
				 DWORD												cbOutputBuffer;

				 #ifdef  __DEBUG__
						 BOOL										bAudio;
				 #endif
				 BOOL												bFilterGraph;								//  2010/06/14
				 //
				 int												unused_iIndex_player;						//  2015/10/01
				 
				 //
				 struct												{
					 QY_VIDEO_HEADER								vh_decompress_real;
					 char									*		pBuf;
					 unsigned  int									uiBufSize;
				 }													inputForEnc;

				 //  
				 unsigned  __int64									ui64_total_inputBytes;						//  for audio compress

				 //
				 LONGLONG											rt_total_rtTimeLen;							//  for decompress

				 //
				 int												iSampleTimeInMs_new;						//  for video decompress.  2010/06/19
				 int												iSampleTimeInMs_audio;						//  for video decompress
				 //  int												iSampleTimeInMs_stream;						//  for video decompress

				 //
				 int												iDiffInMs_tStartStream;						//  2009/05/26

				 //
				 void										*		pDebugStep;									//  2010/04/28

}		 MY_DMO_INFO;



#endif  }



