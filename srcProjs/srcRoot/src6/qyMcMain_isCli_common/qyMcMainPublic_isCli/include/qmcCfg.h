

#ifndef  __qmcCfg_h__
#define  __qmcCfg_h__	//  {

//
#include	"myTypes.h"
#include	"policyIsClientFunc.h"
#include	"ipcProcCfg.h"


//
typedef  struct  __render_cfg_t  {
				 float			fps_suggested;
}		 RENDER_cfg;


//  2015/01/25
typedef  struct  __qmcCfg_t										{

					 unsigned  int								uiMaxSendMsgs;												//  
					 unsigned  short							usMaxMsgrRecentFriends;										//  2007/06/04
					 
					 //
					 unsigned  int								uiSizePerSnd_file_noAv;										//  2014/07/13
					 unsigned  int								uiSizePerSnd_file_avExists;									//  2014/07/13

					 //
					 unsigned  int								uiSizePerSnd_media;											//  2008/04/01
					 unsigned  short							usNeedShowFrameInfoIntervalInS;								//  
					 
					 unsigned  int								uiBufSize_myDrawVideoData;									//  2010/04/24
					 unsigned  int								uiBufSize_myPlayAudioData;									//  2010/04/24

					 //
					 struct										{															//  2010/06/26
						 unsigned  short						usMaxQNodes_mediaQ;		
						 unsigned  short						usQNodes_warningInterval_mediaQ;
						 unsigned  short						usMaxQNodes_rtMediaQ;
						 unsigned  short						usQNodes_warningInterval_rtMediaQ;						 
						 unsigned  short						usMaxQNodes_rtOpQ;											//  2016/12/26
						 unsigned  short						usQNodes_warningInterval_rtOpQ;						 

						 //
						 unsigned  short						usMaxQNodes_playSoundQ;
						 unsigned  short						usMaxQNodes_playVideoQ;										//  2012/11/09
						 unsigned  short						usMaxQNodes_displayVideoQ;									//  2012/11/09

						 //
						 unsigned  short						usMaxQNodes_dlgTalk_processQ;								//  2010/07/22
						 unsigned  short						usMaxnItems_dlgTalk_list;									//  2010/07/22
						 //
						 unsigned  short						usMaxQNodes_imMsgLogQ;
						 
						 //  2017/08/15
						 unsigned  char							default_ucbLetConfMgrSetMicOn;



					 }											envVar;

					 //
					 GENERIC_Q_cfgEx							mgrQEx;
					 GENERIC_Q_CFG								displayQ,  workQ,  schedulerQ,  robotQ,  mediaQ, realTimeMediaQ,  rtOpQ;		//  svrThreadÍ¨³£ÓÃÀ´ÏòÆäËûµÄcontactÌá¹©ÐÅÏ¢£¬±ÈÈç´«ÎÄ¼þµÈ
					 //  
					 GENERIC_Q_CFG								processQ_robot;
					 //
					 GENERIC_Q_CFG								processQ_media;												//  

					 GENERIC_Q_CFG								outputQ_toMix_audio;										//  ÒôÆµµÄÊä³ö¶ÓÁÐ¡£
					 GENERIC_Q_CFG								outputQ_toMosaic_video;										//  2009/07/26

					 //
					 GENERIC_Q_CFG								playSoundQ;
					 GENERIC_Q_CFG								playVideoQ;													//  2009/05/02
					 GENERIC_Q_CFG								displayVideoQ;												//  2009/07/25

					 //
					 GENERIC_Q_CFG								transformQ;													//  2009/05/12

					 //
					 GENERIC_Q_CFG								mixQ;

					 //
					 GENERIC_Q_CFG								aecQ;
					 GENERIC_Q_CFG								aecPlayQ;

					 //  2017/01/29
					 GENERIC_Q_CFG								appQ;														//  2017/01/29
					 //
					 GENERIC_Q_CFG								vppQ;	
					 //  2011/12/04
					 GENERIC_Q_CFG								toSaveIcQ;
					 //
					 GENERIC_Q_CFG								toShareAudioQ;												//  2011/01/21
					 GENERIC_Q_CFG								toShareVideoQ;												//  2011/01/21

					 //
					 GENERIC_Q_CFG								toShareVideo_postQ;											//  2011/12/06

					 //
					 GENERIC_Q_CFG								dispatchQ;													//  2009/06/17

					 //  2016/03/15
					 GENERIC_Q_CFG								talkerThreadQ;												//  2016/03/15

					 //  2016/06/15
					 GENERIC_Q_CFG								shareDynBmpsQ;												//  2016/06/15

					 //
					 GENERIC_Q_CFG								guestQ;														//  2008/01/18, 
					 //
					 GENERIC_Q_CFG								dynBmpQ;													//  2009/09/05

					 //
					 POLICY_isClient							policy;
					 
					 //
					 IpcProcInitCfg								ipcProcInitCfg;
					 ShareProcInitCfg							shareProcInitCfg;

					 //
					 RENDER_cfg									render;

					 //
					 TCHAR										mutexName_syncSendAv[16  +  1];
					 TCHAR										mutexName_syncActiveMem_prefix1[16  +  1];					//  2009/05/31
					 TCHAR										mutexName_syncStartAv[16  +  1];

					 //  2014/09/22
					 unsigned  char								ucb__SUPPORT_shareDynBmps__;

					 //  2008/05/17
					 //unsigned  char								ucbNeedShowFrameInfo_forVideoConference;
					 //
					 unsigned  char								ucb__SUPPORT_dmoToDec__;									//  2010/08/05
					 
					 //  2014/04/03
					 //unsigned  char							ucb__USE_hdEnc_conf__;										//  unused

					 //
					 unsigned  char								ucb_talkToMsgr_manually;

					 //
					 unsigned  char								ucb_closeTalkIfNoConf;


					 //  2012/05/15
					 unsigned  char								ucbTestGps;
					 


					 //  2015/05/18
					 unsigned  char								ucbPlayLocalAudio_captured;									//  2015/05/18
					 unsigned  char								ucbPlayRemoteAudio_viewDynBmp;								//  2015/05/19		 
					 
					 //
					 unsigned  char								ucb__USE_d2dToRenderTxt__;									//  2016/05/18

					 //
					 int										maxTimes_noXtResp3;

					 //
					 unsigned  short							usMaxCnt_capProcInfoBmps;
					 unsigned  short							usMaxCnt_capProcInfoAudios;

					 unsigned  short							usMaxCnt_pSharedObjs;										//  2008/10/04


					 //  2015/11/10
					 unsigned  short							usMaxCnt_qmcObjVarInfos;										//  2015/11/10
					 //  2014/09/23
					 unsigned  short							usMaxCnt_taskInfos;

					 //
					 unsigned  short							usTimeoutInMs_player_a;										//  2010/06/25
					 unsigned  short							usTimeoutInMs_player_v;
					 
					 unsigned  short							loopCtrl_chkPlayers;										//  default 10. 2010/06/26
					 unsigned  short							loopCtrl_timer_dlgTalk_chkRecvdTasks;						//  default 30. 2010/06/26. 
					 
					 //
					 unsigned  short							loopCtrl_chkTasks;

					 //
					 ushort										usTimeoutInMs_waitIfNoData;

					 //
					 TCHAR										isCliD3dFileName[32];
					 TCHAR										isCliD3dFileName_dx12[32];

					 //
					 bool										b_useAudioQ2_toDecA;
					 bool										b_useQ2_toPlayA;

					 //
					 bool										bSaveAv_conf;												//  存混合流
					 bool										bSaveAv_trans;												//  存单流

					 //
					 QMC_debugStatusInfo						debugStatusInfo;	//  2015/01/23
					 DWORD										dwRefreshedTickCnt_debugStatusInfo;
				
					 //  2016/08/10
					 TCHAR										clientWelcomeMsg[128];
				 
					 //
					 bool										bSkip_sm_usrLogin;

					 //
					 bool										m_bUseWx;		//  用做卫星带宽下  


}		QMC_cfg;


//
bool  bUseD3DFullScreen(  );


//
 int  getTransformQName(  TCHAR  *  tName,  unsigned  int  cnt  );



//
#endif  //  }


