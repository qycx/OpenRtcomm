

#ifndef  __policyIsClientFunc_h__
#define  __policyIsClientFunc_h__	//  {


//  2011/11/27
#if  0
	#define		CONST_uiMinTimeInMsOfAudioDataPlaying_1s			500
	#define		CONST_uiAudioDataAddedToPlayEveryTime_1s			200
	#define		CONST_uiNotifyIntervalInMs_needMoreAudioData_1s		70
	#define		CONST_uiMaxTimeInMsToPlay_1s						500
	#define		CONST_uiMaxTimeInMsToBeRemoved_1s					200

	//
	#define		CONST_uiMinTimeInMsOfAudioDataPlaying_05s			300
	#define		CONST_uiAudioDataAddedToPlayEveryTime_05s			120
	#define		CONST_uiNotifyIntervalInMs_needMoreAudioData_05s	70
	#define		CONST_uiMaxTimeInMsToPlay_05s						300
	#define		CONST_uiMaxTimeInMsToBeRemoved_05s					60

#else

	// 1.5s,  2012/01/28
	#define		CONST_usMinTimeInMsOfAudioDataPlaying_15s			500
	#define		CONST_usAudioDataAddedToPlayEveryTime_15s			200
	#define		CONST_usNotifyIntervalInMs_needMoreAudioData_15s	70
	#define		CONST_usMinTimeInMsToPlay_15s						650
	#define		CONST_usMaxTimeInMsToPlay_15s						900
	#define		CONST_usMaxTimeInMsToBeRemoved_15s					200
	// 1s
	#define		CONST_uiMinTimeInMsOfAudioDataPlaying_1s			500
	#define		CONST_uiAudioDataAddedToPlayEveryTime_1s			200
	#define		CONST_uiNotifyIntervalInMs_needMoreAudioData_1s		70
	#define		CONST_uiMinTimeInMsToPlay_1s						250
	#define		CONST_uiMaxTimeInMsToPlay_1s						500
	#define		CONST_uiMaxTimeInMsToBeRemoved_1s					200

	//
	#define		CONST_uiMinTimeInMsOfAudioDataPlaying_07s			150
	#define		CONST_uiAudioDataAddedToPlayEveryTime_07s			200
	#define		CONST_uiNotifyIntervalInMs_needMoreAudioData_07s	70
	#define		CONST_uiMinTimeInMsToPlay_07s						100
	#define		CONST_uiMaxTimeInMsToPlay_07s						220
	#define		CONST_uiMaxTimeInMsToBeRemoved_07s					200

	//
	#define		CONST_uiMinTimeInMsOfAudioDataPlaying_05s			150
	#define		CONST_uiAudioDataAddedToPlayEveryTime_05s			120
	#define		CONST_uiNotifyIntervalInMs_needMoreAudioData_05s	70
	#define		CONST_uiMinTimeInMsToPlay_05s						100
	#define		CONST_uiMaxTimeInMsToPlay_05s						150
	#define		CONST_uiMaxTimeInMsToBeRemoved_05s					120

#endif

//  2014/12/24
#define		CONST_w_240p		424		//  320
#define		CONST_h_240p		240		//  320
#define		CONST_w_480p		848		//  640
#define		CONST_h_480p		480		//  320


//
#define		CONST_w_256x144		256
#define		CONST_h_256x144		144



//  2014/12/24
#if  0
	#define		MAX_w_slave		CONST_w_240p
	#define		MAX_h_slave		CONST_h_240p
#else
	#define		MAX_w_slave		CONST_w_480p		//  2018/12/19
	#define		MAX_h_slave		CONST_h_480p
#endif

/////////////////
//
typedef  struct  __policyIsClient_t								{
				 unsigned  char									ucbRunAsAdvertisingPlayer;							//  2013/11/14. 是否做为广告机运行

				 //  
				 unsigned  char									ucbDlgShareDynBmps_autopopupandhideOnStartup;

				 //
				 //
				 unsigned  char									ucbUseGlobalVWall;									//  2012/04/02. 是否使用GlobalVWall
				 //
				 unsigned  char									ucRuleIfMsgArrive;
				 TCHAR											dirToSaveFile[MAX_PATH  +  1];
				 TCHAR											dirToSaveICFile[MAX_PATH + 1];
				 bool                                           isSaveICFile;

				 //
				 unsigned  char									ucbSaveMsg;
				 TCHAR											dirToSaveMsg[MAX_PATH  +  1];						//  2014/04/26

				 //
				 unsigned  int									uiTimeOfVideoFileInS;
				 TCHAR											dirToSaveVideo[MAX_PATH  +  1];						//  2014/08/03				

				 //  2014/03/29
				 unsigned  char									ucHardwareAccl;			
				 //

				 //  2011/03/28
				 //  unsigned  char									snmpbShowMsgBox;
				 unsigned  char									ucbShowNotification;
				 unsigned  char									ucbScrollForEnlagedImg;								//  2012/04/07. 对双击放大图像是否不滚动

				 //
				 struct											{
					 unsigned  int								uiCamCapType;										//  2010/07/26
					 //
				 	 //  unsigned  char								ucSeconds_perFrame_videoConference;				//  ºÜÂýÊ±£¬ÓÃ¼¸ÃëÒ»Ö¡. Õâ¸ö²ÎÊýÖ»ÓÃÔÚ·¢ËÍ¶Ë£¬½ÓÊÕ¶Ë²»ÐèÒªÓÃµÄ¡£
				 	 //  unsigned  short							usFrames_perSecond_videoConference;				//  Ò»Ãë¼¸èå


				 }												video;
				 struct											{
					 unsigned  int								uiRecordType;										//  2010/08/02
					 //

					 //  2014/07/31
					 unsigned  char								ucbNot_selectDefaultRecorder;		

				 }												audio;

				 //
				 unsigned  short								usTimeoutInMsToSwitch;							//  2008/10/28, media realTimeMedia daemon 
				 unsigned  short								usTimeoutInMsToSwitch_rt;						//  rt
				 unsigned  short								usTimeoutInMsToSwitch_file;

				 //  2012/03/31
				 unsigned  short								usMax_nPlayers;									//  2012/03/30
				 unsigned  short								usMax_nPlayers_gps;								//  2012/05/07
				 unsigned  short								usMax_nThreads_dec;
				 unsigned  int									uiMaxQNodes_vwRuleQ;

				 //  2009/02/25
				 unsigned  char									ucbManullyPermitToSpeakOnVideoConference;		//  2009/02//24

				 //  2016/02/15
				 struct											{							
					 unsigned  int								uiCmd_autoAnswer_av;
					 //  2017/07/07
					 unsigned  char								ucbLetConfMgrSetMicOn;
					 //
				 }												avRules;
				 
				 //  2010/08/24
				 struct											{
					 unsigned  char								ucbPermitEveryOneNotify;						//  允许任何人呼叫
					 unsigned  char								ucbNotNotifyDuringConference;					//  禁止会议中有通知消息
					 unsigned  char								ucbNotNotify;									//  禁止任何通知消息
					 //
					 unsigned  char								ucbBeep;
					 //
					 unsigned  short							usTimeInMsToPop;								//  pop窗口弹出要花多少时间
					 int										iW_pic;
					 int										iH_pic;
					 int										iH_static;
				 }												notification;

				 //  2010/09/03
				 struct											{
					 unsigned  char								ucbShowImGrpMems;
					 //  
					 unsigned  char								snmpbShowMsgBox;
				 }												dlgTalk;

				 //  2012/08/01
				 //  COM_PORT_cfg									comPort_ptz;

				 //  2012/06/25
				 unsigned  char									ucbPreferCuda;								//  进行视频压缩硬加速时优先采用cuda
				 //  2012/11/06
				 unsigned  char									ucbLooping_mediaFile;						//  循环播放媒体文件

}		 POLICY_isClient;


//

//
 //
#define		CONST_cfgName_saveAvUrl_prefix			"saveAvUrl_prefix"
#define		CONST_cfgName_ffmpegPath				"ffmpegPath"
 //
#define		CONST_cfgName_bDraw3dFps				"bDraw3dFps"
//
//#define		CONST_cfgName_bNoSaveAv_conf			"bNoSaveAv_conf"
//#define		CONST_cfgName_bNoSaveAv_trans			"bNoSaveAv_trans"
#define		CONST_cfgName_bSaveAv_conf				"bSaveAv_conf"						// 设置了才存。不设置不存
#define		CONST_cfgName_bSaveAv_trans				"bSaveAv_trans"


//
typedef  struct {

	//
	char	saveAvUrl_prefix[255 + 1];
	TCHAR	tFfmpegPath[255 + 1];
	
	//
	bool	bDraw3dFps;

	//
	bool	bSaveAv_conf;
	bool	bSaveAv_trans;

	//
}  Mcu_initCfg;

//
bool bGetMcuInitCfg(TCHAR* cfgFileName, Mcu_initCfg* pCfg);




//
 __declspec(  dllexport  )  int  getDefaultPolicyAvLevel(  QY_MC  *  pQyMc,  unsigned  int  uiCapType,  unsigned int uiSubCapType,  int iCapUsage  );
 __declspec(  dllexport  )  int  getPolicyAvLevel(  QY_MC  *  pQyMc,  unsigned  int  uiCapType,  unsigned int uiSubCapType,  int iCapUsage  );

 //
 QY_DMITEM  CONST_conf_fourccTable[];


 //
 __declspec(dllexport)  int  get_conf_fps();
 __declspec(dllexport)  BOOL  get_conf_b100k();
 __declspec(dllexport)  BOOL  get_conf_bLyra();



 //
 __declspec(  dllexport  )  int  get_conf_iFourcc(  );
 __declspec(  dllexport  )  int  set_conf_iFourcc(  int  conf_iFourcc, int conf_bitrateInKbps, AV_COMPRESSOR_CFG  *  pCompressor  );
 //
 __declspec(  dllexport  )  int  get_conf_usMaxSpeakers(  );
 //
 __declspec(dllexport)  int  get_conf_bitrateInKbps(int* pbitrateInKbps_dl, int* pbitrateInKbps_ul);



 //
#if 0
 __declspec(dllexport)  int  get_2ndMcu(char* ipBuf, int  ipBufSize);
 __declspec(dllexport)  int  set_2ndMcu(char* ip);
#endif


  

//
__declspec(  dllexport  ) int  getPolicyIsClient(  MC_VAR_common  *  pProcInfo,  POLICY_isClient  * p   );
 __declspec(  dllexport  ) int  getVideoConferenceCfg(  HKEY  hKeyRoot0,  LPCTSTR  pRootKey_qnmScheduler,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  VIDEO_CONFERENCE_CFG  *  pCfg  );
 __declspec(  dllexport  ) int  getAecCfg(  HKEY  hKeyRoot0,  LPCTSTR  pRootKey_qnmScheduler,  AEC_cfg  *  pCfg  );
  BOOL  bEnable_saveMsgFlg(  MC_VAR_common  *  pProcInfo,  bool  *  pbFlgSetAlready  );
 
 

#endif  //  }


