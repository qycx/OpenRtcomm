


#ifndef  __QMCCOMMFUNC_MIS_H__
#define  __QMCCOMMFUNC_MIS_H__	//  {

//
#include	"syncMtCnt.h"
//
#include	"qmcDefs.h"
//
#include	"subtitles.h"
#include	"qmcMosaic.h"

//
#include	"qmcStruct_defs.h"
#include	"qyMcMainObj.h"

//
#define		CONST_ruleIfMsgArrive_flash							1												//  ÏûÏ¢µ½À´Ê±£¬ÈÃÍ¼±êÉÁË¸¡£
#define		CONST_ruleIfMsgArrive_popup							2												//  ÏûÏ¢µ½À´Ê±£¬µ¯³ö


#define		DEFAULT_ruleIfMsgArrive								CONST_ruleIfMsgArrive_flash		


#define		CONST_maxMisCnts									1

#define		CONST_maxTriesToStartSession_mis					5



//  2014/09/03
#define		CONST_talkerObjType_null							0
#define		CONST_talkerObjType_dynBmp							1



//  2013/02/12
typedef  struct  __talker_dynBmp_t								{
				 unsigned  int									uiType1;

				 DYN_BMP_RULE									dynBmpRule;

				 //				 
				 struct											{
					 int										iTaskId;
					 //  2013/02/12
					 time_t										tStartTran;  
					 unsigned  int								uiTranNo;
					 
					 //  2013/02/24
					 time_t										tStartTime_processed;

					 //  2013/02/05
					 //time_t										tLastTime_active;

					 //
					 BOOL										bNeedProgress;

					 //  2014/09/04
					 struct										{
						 unsigned  int							uiTranNo;
						 //
						 DWORD									dwLastTickCnt_retrieveOne;
					 }											retrieveOne;

					 //  2015/10/23
					 struct										{
						 int									iW,  iH;
						 unsigned  char							ucbUnresizable;
					 }											srcInfo;

				 }												taskInfo;

}		 TALKER_dynBmp;


//
#include	"comPortCfg.h"



//
int  getUi64IdFromReg(  TCHAR  *  pBuf,  QY_MESSENGER_ID  *  pIdInfos,  int  maxCnt_pIdInfos  );
int  getBufFromUi64Id(  QY_MESSENGER_ID  *  idInfos,  int  maxCnt_idInfos,  TCHAR  *  pBuf,  int  maxCnt_pBuf   );





//
#define		DEFAULT_policyAvLevel_reply_hd						CONST_policyAvLevel_480p
#define		DEFAULT_policyAvLevel_reply_fullHd					CONST_policyAvLevel_480p
//  
#define		DEFAULT_policyAvLevel_mosaic_video					CONST_policyAvLevel_848x480					//  2014/11/15
//
//#define		DEFAULT_policyAvLevel_slave_video					CONST_policyAvLevel_240p					//  2016/04/06
#define		DEFAULT_policyAvLevel_slave_video					CONST_policyAvLevel_480p					//  2016/04/06
//
#define		DEFAULT_policyAvLevel_req_screen					CONST_policyAvLevel_dev_5fps
//
#define		DEFAULT_policyAvLevel_req_mediaFile					CONST_policyAvLevel_480p
#define		DEFAULT_policyAvLevel_req_mediaFile_basic			CONST_policyAvLevel_480p
//
#define		DEFAULT_policyAvLevel_req_mediaDevice				CONST_policyAvLevel_480p
#define		DEFAULT_policyAvLevel_req_mediaDevice_basic			CONST_policyAvLevel_480p
//
#define		DEFAULT_policyAvLevel_req_unresizable				CONST_policyAvLevel_dev_5fps				//  2015/03/11
#define		DEFAULT_policyAvLevel_req_unresizable_basic			CONST_policyAvLevel_dev_2fps				//  2015/03/11

//
#define		DEFAULT_policyAvLevel_req_webcam					CONST_policyAvLevel_480p					//  CONST_policyAvLevel_240p


//  2014/04/30
__declspec(dllexport)int  getRegRootKey_qmc(  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage,  TCHAR  *  rootKeyStr,  unsigned  int  uiCnt  );
//
int  get_idRegRootKey_qmc(  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage,  TCHAR  *  rootKeyStr,  unsigned  int  uiCnt  );

//
int  get_resIdTable(  int  level,  int  iFourcc,  int  *  piResId,  int  *  piDefault_bitrate  );
__declspec(dllexport)  int  getCompressorCfg(  QY_REG  *  pReg,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor  );
int  saveCompressorCfg(  QY_REG  reg,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor  );
__declspec(dllexport)CQyString  getCompressorDesc(  unsigned  int  uiCapType,  AV_COMPRESSOR_CFG  *  pCompressor  );

//  2014/04/27
#define			CONST_subDir_msg								"qmMsg\\"
//  2015/08/05
#define			CONST_subDir_fileServer							"qmFileServer\\"

//
#define			CONST_subDir_conf								"conf\\"


//
typedef  struct  __encCtx_isCnt_t								{
				 QY_ENC_CTX										common;											//  2007/06/20
				 
				 //
				 unsigned  int									uiBlobLen_publicKey;
				 char											publicKeyBlob[CONST_bufSize_publicKeyBlob];

				 unsigned  char									ucbPublicKeyDownloaded;							//  
				 unsigned  char									ucbPublicKeyVerified;							//  
				 
				 //
				 struct {
					 //
					 char										caGwIp[15 + 1];
					 int										caGwPort;

					 char										hgGwIp[15 + 1];
					 int										hgGwPort;

					 char										caYqServIp[15 + 1];
					 //
					 unsigned  char								ucbDownloaded;
					 unsigned  char								ucbOk;
				 }												caServCfg;

				 //
				 char											caRandom[256];
																												//
				 unsigned  char									ucbCaRandomDownloaded;							//  2023/01/15
				 unsigned  char									ucbCaRandomOk;


}		 ENC_CTX_isCnt;




typedef  struct  __imTaskStat_t									{
    			 unsigned  int									uiCnt_unprocedTasks;							//  
				 unsigned  int									uiCnt_processingTasks;							//  
				 unsigned  int									uiCnt_processBreakTasks;
}		 IM_TASK_STAT;


//
typedef  struct  __misChannel_t									{
			
				 //
				 MIS_CNT								*		pMisCnt;										//  2016/09/09

				 //
			     unsigned  int									uiType;
				 //
				 ENC_CTX_session								commEncCtx;										//  2008/06/08
				 unsigned  char									ucbEncInited;
				 
				 //
				 QY_LOGICAL_SERVER								curServer;				 
				 
				 //
				 QY_COMM_SESSION								session;
				 QY_SOCK										sock;
				 BOOL											bSessionOpen;

				 //
				 GENERIC_Q										inCacheQ;										//  recv
				 //QY_Q2											inputQ2;										//  2015/09/09
				 //
				 QY_Q2											toSendQ2;
				 QY_Q2											outputQ2;

				 //
				 HANDLE											hThread_io;										//  
				 DWORD											dwThreadId_io;									//  

				 //
				 struct											{
					HANDLE										hThread_toSend;									//  2008/05/23
					DWORD										dwThreadId_toSend;

					//  socket机制使用
					HANDLE										hThread_snd;
					DWORD										dwThreadId_snd;
				}												ctx;


				 //
				 void									*		p0;												//  可以传给thread_work_iocp参数. 2012/02/24

				 //
				 struct											{
					 //  unsigned  long							ulbServNotConnected:1;
					 unsigned  long								ulbAuthed:1;
					 unsigned  long								ulbNeedVerified:1;
					 
					 //
					 unsigned  long								ulbSessionErr:1;								//  

					 IM_NET_STAT								netStat;
					 IM_NET_STAT								oldNetStat;

					 unsigned  long								ulbIoQuit:1;									//  IO
					 //
					 //unsigned  long								ulbInputQuit1:1;									//  2015/09/09
					 unsigned  long								ulbToSendQuit:1;								//  
					 unsigned  long								ulbSndQuit:1;									//  
					 //unsigned  long								ulbRecvQuit:1;									//  
					 
					 //
					 DWORD										dwTickCnt_startChannel;

					 //
					 DWORD										dwTickCnt_lastStartToRecv;						//  2009/02/25
					 DWORD										dwTickCnt_lastEndSending;						//  2011/01/23

					 //
					 DWORD										dwTickCnt_noSending_start;						//  2012/05/21

					 //
					 DWORD										dwLastTickCnt_applyForChkChannels;
					 
				 }												status;

}		  MIS_CHANNEL;





				 
//
struct  __misCnt_t													{

				 //
				 void  *											pProcInfoParam;									//  2009/09/07
	
				 //
				 struct												{

					TCHAR											misServName[CONST_maxMisServNameLen  +  1];

					//
					QWM_DYN_CFG										dynCfg;

					//
					int												iObjQType;										//  2007/04/05
					WCHAR											mutexName_syncQmObjQ[32  +  1];
					WCHAR											semaphoreName_syncQmObjQ[32  +  1];
					unsigned  int									uiMaxCnt_semaphore_qmObjQ;					

					//
					GENERIC_Q_CFG									inCacheQ;										//  2008/04/02
					//GENERIC_Q_CFG									inputQ;											//  2015/09/09
					//
					GENERIC_Q_CFG									toSendQ;
					GENERIC_Q_CFG									outputQ;
					//
					
					GENERIC_Q_CFG									talkingFriendQ,  recentFriendQ;

					unsigned  int									uiSizePerSnd_media;								//  2011/01/30

					unsigned  short									usIntervalInS_getIntervalParams;				//  
					//
					unsigned  short									usMaxMsgrRecentFriends;
					unsigned  short									usIntervalInS_refreshRecentFriends;				//  
					//
					unsigned  short									usIntervalInS_refreshContactList;				//  

					//  2015/07/28
					//unsigned  char								ucbNotUseP2pCall;								

					//
					unsigned  short									usMaxContactUpdateInfosPerSnd_grp;				//  2014/02/06
					unsigned  short									usMaxContactUpdateInfosPerSnd_grpMem;			//  
					unsigned  short									usMaxContactUpdateInfosPerSnd_contact;			//  

					//
					unsigned  short									usIntervalInS_tryToReg;							//  
					unsigned  short									usIntervalInS_tryToSndDevInfo;					

					WCHAR											mutexNamePrefix_syncTask[32  +  1];				//  

					//

				 }													cfg;

				 ENC_CTX_isCnt										commEncCtx;										//  2007/06/20
				 unsigned  char										ucbEncInited;
				 
				 QY_COMM_AUTHINFO_MIS							*	pAuthInfo;

				 //
				 QY_LOGICAL_SERVER									server;							//  当前正使用的
		 
				 //
				 struct {					 
					 QWM_DYN_CFG									dynCfg;					//  建议配置
					 //
					 struct {
							 bool									bDone;
							 bool									bFail;
					 }												helpInfo;
					 //
					 unsigned  int									tn_changed;
					 //
				 }													dynCfg_suggested;
				 //
				 struct {
					 DWORD											dwServIp;				//  建议使用的
					 //
					 unsigned  int									tn_changed;
				 }													servIp_suggested;



				 //  2ndMcu和confMcu都为0时，不需要双机热备.
				 //  当dwConfMcuIp==dwServIp_suggested  ==  server.ip时，表明是正确的
				 //  当以上模式联不通时，则将dwservIp_suggested设为dw2ndMcuIp
				 struct {
					 //
					 //DWORD											dw2ndMcuIp;
					 DWORD											dwConfMcuIp;

					 //
					 bool											bNeedXt_ifSessionOff;

					 //
					 bool											bStartToFindCorrectMcu;
					 int											nTimes_toWait;
					 struct {
						 struct {							
							 bool									bInited;
						 }											confMcu;
						 struct {
							 bool									bInited;
							 bool									bDone;
						 }											str1stMcu, str2ndMcu;
						 //  
					 }												status;


				 }													dualSystem;// HotBackup;


				 //
				 void											*	pObjQ;											//  2007/06/03
				 unsigned  char										ucbQmObjQInited;								//  2007/06/03

				 unsigned  short									usConnectCntInterval;
				 
				 //
				 MIS_CHANNEL										channels[CONST_maxConnsPerCli_mis];

				 //
				 QY_MESSENGER_ID									idInfo;											//  Me idInfo
				 TCHAR												displayName[64  +  1];							//  Me 
				 TCHAR												talkerDesc[64  +  1];							//  Me 
				 TCHAR												displayName_withIdInfo[64  +  1];				//  2016/04/06

				 //
				 BOOL												bIntervalParamsGot;								//  2007/09/20
				 DWORD												dwLastTickCnt_getIntervalParams;

				 //
				 RETRIEVE_TO_PATHS									toPaths;										//  2008/02/09
				 BOOL												bToPathsRetrieved;
				 DWORD												dwLastTickCnt_retrieveToPaths;

				 //
				 GENERIC_Q											talkingFriendQ;									//  
				 //
				 GENERIC_Q											recentFriendQ;									//  pRecentFriendsºÍrecentFriendQµÄ¹ØÏµ£ºpRecentFriendsºÍ·þÎñÆ÷ÊÇÍ¬ÑùµÄÄÚ´æÇø£¬
																												//		recentFriend
																												//		recentFriend pRecentFriends
																												//		pRecentFriends
				 struct												{
                     time_t											tLastRefreshedTime_misServ;
				 	 DWORD											dwLastTickCnt;									//  
					 //
					 bool											bRefreshAtOnce;
					 //
				 }													refreshRecentFriends;
				 //
				 
				 unsigned  char										ucTriesToReg;									//  2007/08/05
				 DWORD												dwLastTickCnt_tryToReg;							

				 unsigned  char										ucbNeedSndDevInfo;								//  2007/08/03
				 DWORD												dwLastTickCnt_tryToSndDevInfo;					

				 //  DWORD											dwLastTickCnt_chkChannels;					//  channel channel. 2008/06/01

				 //
				 TCHAR												whoBuf_showInfo[32];							//  2007/05/28

				 struct												{												//  2997/08/02
					 DWORD											dwLastTickCnt_startToRetrieve;					//  2007/07/26
					 DWORD											dwLastTickCnt_respRecvd;						//  2014/02/11
				 
					 //
					 time_t											tLastRefreshedTime_misServ;						//  
				 	 time_t											tStartTime;										//  
				 	 unsigned  int									uiTranNo;
					 //
					 QY_MESSENGER_ID								idInfo_lastRefreshed;							//  
					 //
				 }													refreshContactList;
				 
				 struct												{
					 DWORD											dwLastTickCnt;
				 }													retrieveCustomerServiceObjList;					//  2011/04/10

				 struct												{												//  2008/02/01
					 DWORD											dwLastTickCnt;
					 //
					 WCHAR											wDevIdStr_lastRefreshed[32  +  1];
					 //
				 }													retrievePhoneMsgrs;

				 //
#if  10
				 struct {
					 unsigned  long									ulbImGrpExists : 1;											//  是否下载了分组信息。2011/04/10.
					 unsigned  long									ulbContactExists : 1;											//  是否下载了contact信息
					//
					 unsigned  long									ulbAllContactsRetrieved : 1;									//  是否用户信息都下载了. 2013/08/01
					 //
					 unsigned  short								nTimes_refresh;												//  因为access写入较慢,所以,在所有用户信息得到后,需要自动的刷新几次. 比如3次
					 DWORD											dwTickCnt_lastRefreshed;
				 }													retrieveImObjList;
#endif

				 //
				 QY_im_rules										imRules;										//  2011/11/13. 将根本messenger相关的存服务器数据库里的全局规则放在这里
				 //
				 struct												{												//  2010/08/17
					 DWORD											dwLastTickCnt;
					 time_t											tLastRefreshedTime;
					 //
					 time_t											tStart_toRetrieveAll;							//  2011/11/12
				 }													refreshImObjRules;
				 //
				 struct												{												//  2014/04/19
					 time_t											tStartTime;
					 unsigned  int									uiTranNo;
				 }													retrieveDynBmps;

				 //  2009/06/01
				 struct												{
					 DWORD											dwLastTickCnt_refreshed;						//  2009/06/01
					 BOOL											bNeedRefreshed;									//  2009/06/01
					 int											iTaskId;
				 }													refreshVideoConferenceActiveMems;

				 //  2015/08/01
				 struct												{
					 QY_MESSENGER_ID								idInfo_resServ;
				 }													procOfflineRes;


				 //			
				 CAP_subWnds										subWnds;										//  2009/09/09

				 //
				 IM_TASK_STAT										taskStat;

				 //
				 struct												{
					 //
					 unsigned  long									ulbSeriousErr:1;								//  
					 //
					 unsigned  short								usRunningStatus;								//  2007/06/07

					 IM_TASK_STAT									netStat;

					 //
					 float											fDiscards;
					 DWORD											dwLastTickCnt_initTaskAvFrom_video;

				 }													status;
};



//  2015/01/22
#include	"qmcSharedObj.h"



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
#include	"qmcCommFunc_is_open.h"




//  2015/09/10
#if  0
typedef  struct  __statPlayVInt_t								{
				 int											iDiff_real_nIntInMs_big;								//  这里指和avgTimeInMs的差距. 
				 int											iDiff_real_nIntInMs_small;
				 //
				 int											nTotal_abs_iDiff_real;
}		 STAT_play_vInt;
#endif









/////
//  2012/05/07
typedef  struct  __qyPlayerGps_t								{
				 QY_MESSENGER_ID								idInfo;
				 //
				 QY_Q2											q2;																			
				 BOOL											bQInited;					

				 //
				 int											iTaskId;

				 //
				 DWORD											dwTickCnt_lastRecvd;

}		 QY_PLAYER_gps;


/////


#include	"taskAv.h"




//////////////////
//
//






//  2015/01/23
#include	"ctxQmcTmpl.h"








//  2008/05/10, ¿´ÊÓÆµÊÇ·ñÔÚÎÈ¶¨ÔËÐÐÌ¬¡£
#define		isVideoNormalState(  pCompressVideo  )	(  pCompressVideo->usFps_ok  &&  pCompressVideo->bTopFrames  &&  pCompressVideo->usFps_ok  ==  pCompressVideo->usFrames_perSecond_expected  )


//
//
typedef  struct											{
			 unsigned  char								ucbPermitToSpeak;
		
			 //
			 QY_MESSENGER_ID							idInfo_starter;
			 time_t										tStartTime;
			 unsigned  int								uiTranNo;
}														ConfMem_confCtrl;



//
typedef  struct  __qMemMessenger_cli_t					{										//  2007/06/03, ´ËÎªÔÚclientµÄ¹ÜÀí¶ÓÁÐµÄ½Úµã±íÊ¾¡£
	
				 QY_MESSENGER_ID						idInfo;

				 unsigned  int							uiType;

				 //
				 unsigned  short						usRunningStatus;
				 unsigned  long							ulIp;
				 unsigned  long							ulDetectedIp;
				 
				 time_t									tLastRefreshedTickCnt_misServ;

				 //
				 bool									bRefreshed_byGui;

				 //
				 TCHAR									talkerDesc[128  +  1];					//  
				 TCHAR									displayName[64  +  1];					//  2007/09/02

				 QY_imObj_rules							rules;									//  2010/08/17
				 struct									{										//  2011/04/09
					 QY_imObj_rules						rules;									//  专门为视频客服临时设置的策略.
				 }										customerService;

				 //  2017/07/20
				 ConfMem_confCtrl						confMem_confCtrl;

}		 QMEM_MESSENGER_CLI;




//  ÔÚdisplayedObjQÀï´æ·ÅÃ¿Ò»¸öÒªÏÔÊ¾µÄ´°¿Ú£¬²¢ÇÒÔÚppDisplayedObjs_sortedByHandleÀïÅÅÐò
//  ÔÚÃ¿Ò»¸ö¶ÔÓ¦´°¿ÚµÄ½ÚµãÀï£¬´æ·Åmc_Ctx_displayedWnd
//  ÔÚÃ¿Ò»¸ödisplayedWndÀï°ÑËùÓÐµÄÒªÏÔÊ¾µÄ¶ÔÏó¶¼´æÔÚ displayedElemQÀï£¬²¢ÓÃppDisplayedElemes_sortedByKeyÀ´ÅÅÐò
//
typedef  struct  __mcCtx_display_t						{

				 GENERIC_Q								displayedObjQ;							//  ´Ë¶ÓÁÐ´æ·ÅÄ³´°¿ÚÄÚÏÔÊ¾µÄ¶ÔÏó£¬Ã¿¸ö´°¿ÚºÍmessengerµÄ×éºÏ¿ÉÒÔ×÷ÎªÒ»¸ö¶ÀÁ¢½Úµã
				 BOOL									bQInited;
	 			 void							**		ppDisplayedObjs_sortedByHandle;			//  ÓÃhWndÀ´ÅÅÐòµÄ			
				 
				 //
				 HWND									hMainWnd;								//  Ö÷½çÃæ´°¿Ú,ÓÃÀ´ºÍÍùÖ÷½çÃæÉÏ·¢ÏûÏ¢£¬Í¨ÖªÆä×öÒ»Ð©¹¤×÷

}		 MC_CTX_DISPLAY;




typedef  struct  __isGuestElem_t						{
				 unsigned  int							uiDevType;
				 WCHAR									wDevIdStr[128];
}		 IS_GUEST_ELEM;




//
extern  QY_DMITEM  CONST_capTypeTable[];
extern  QY_DMITEM  CONST_subCapTypeTable[];
extern  QY_DMITEM  CONST_capUsageTable[];		//  2014/11/19
extern  QY_DMITEM  CONST_sharedObjTypeTable[];	//  2014/05/28
extern  QY_DMITEM  CONST_qyWndContentTypeTable[];	//  2016/01/30




int  getCountryCode(  char  *  countryCode,  unsigned  int  size  );
//
int  getDefaultRecordType(  );
int  getDefaultAPlayType(  QY_MC  *  pQyMc,  int  *  piAPlayType_16kMono16  );

//
BOOL  bFourccWmv(  DWORD  dwTag  );
void  setEncodingDefaults_video(  unsigned  int  uiCapType,  float  fFps,  DWORD  fourcc,  VIDEO_ENC_PARAMS  *  pParams  );



int  getTalkerDesc(  QY_MESSENGER_ID  idInfo,  TCHAR  *  talkerDesc,  unsigned  int  talkerDescCnt,  TCHAR  *  shortName,  unsigned  int  shortNameCnt  );
int  getTalkerDesc(QY_MESSENGER_ID idInfo, unsigned  int* puiObjType, TCHAR* grpName, int  cntof_grpName, QY_MESSENGER_ID* pidInfo_creator,
	TCHAR* dw, int  cntof_dw, TCHAR* bm, int  cntof_bm, TCHAR* syr, int  cntof_syr);
int  getTalkerDesc(QY_MESSENGER_ID idInfo, unsigned  int* puiObjType, TCHAR* grpName, int  cntof_grpName, QY_MESSENGER_ID* pidInfo_creator, unsigned  short  *  p_grp_usSubtype,
	TCHAR* dw, int  cntof_dw, TCHAR* bm, int  cntof_bm, TCHAR* syr, int  cntof_syr);

//  2012/04/03
//#define		M_getActiveMemDesc(  pMisCnt,  pIdInfo,  desc,  descCnt  )	getTalkerDesc(  pMisCnt,  pIdInfo,  0,  0,  desc,  descCnt  );  _sntprintf(  desc,  descCnt,  _T(  "%s(%I64u)"  ),  desc,  (  pIdInfo  )->ui64Id  );
#define		M_getActiveMemDesc(  pMisCnt,  pIdInfo,  desc,  descCnt  )	getTalkerDesc(  *pIdInfo,  desc,  descCnt,  0,  0  );  





typedef  struct  __ceTaskMem_t		{
				  QY_MESSENGER_ID	idInfo_send;
				  time_t			tStartTime;
				  unsigned  int		uiTranNo;
				  //
				  int				iTaskId;
				  int				iStatus;

				  QY_MESSENGER_ID	idInfo_recv;			//  ½ÓÊÕ·½  

 }		  CE_TASK_MEM;

//
__declspec(  dllexport  )  int  storeTaskInDb(  void  *  pDb,  int  iDbType,  MIS_CNT  *  pMisCnt,  int  iTaskId_suggested,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  );
//
int  getCeTaskMem(  void  *  pDb,  int  iDbType,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_send,  time_t  tSendTime,  unsigned  int  uiTranNo,  int  iTaskId,  CE_TASK_MEM  *  pTaskMem  );







int  initMisMsg(  void  *  pMsgParam  );
void  exitMisMsg(  void  *  pMsgParam  );



//
extern "C" DWORD WINAPI mcThreadProc_mis_io( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_mis_io_iocp( LPVOID lpParameter );
//
//extern "C" DWORD WINAPI mcThreadProc_mis_input( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_mis_toSend( LPVOID lpParameter );


//  int  makeWaveFormat_pcm(  int  iHertz,  WAVEFORMATEX  *  p  );
int  makeWaveFormat_pcm(  WORD  nChannels,  int  iHertz,  WORD  wBitsPerSample,  WAVEFORMATEX  *  p  );


//  CString  getWaveFormatExStr(  unsigned  char  ucCompressors,  WAVEFORMATEX  *  pWfx  );
TCHAR  *  getWaveFormatExStr(  unsigned  char  ucCompressors,  WAVEFORMATEX  *  pWfx,  TCHAR  *  tBuf,  unsigned  int  cnt  );
int  getWaveFormatExByStr(  LPCTSTR  str,  WAVEFORMATEX  *  pWfx  );

int  initCompressAudio_dmo(  QY_MC  *  pQyMc,  AUDIO_COMPRESSOR_CFG  *  pCompressor,  QY_AUDIO_HEADER  *  pVh_decompress,  QY_AUDIO_HEADER  *  pVh_compress,  MY_DMO_INFO  *  pDmoInfo  );
int  exitCompressAudio_dmo(  MY_DMO_INFO  *  pDmoInfo  );
int  compressAudio_dmo(  MY_DMO_INFO  *  pDmoInfo,  QY_AUDIO_HEADER  *  pAh_decompress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs  );

int  initDecompressAudio_dmo(  QY_MC  *  pQyMc,  const  AUDIO_COMPRESSOR_CFG  *  pCompressor,  QY_AUDIO_HEADER  *  pAh_compress,  QY_AUDIO_HEADER  *  pAh_decompress,  MY_DMO_INFO  *  pDmoInfo  );
int  exitDecompressAudio_dmo(  MY_DMO_INFO  *  pDmoInfo  );
int  decompressAudio_dmo(  MY_DMO_INFO  *  pDmoInfo,  QY_AUDIO_HEADER  *  pAh_compress,  BYTE  *  pInput,  unsigned  int  uiInputLen,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  );

#if  0
int  initDecompressAudio_filterGraph(  const  AUDIO_COMPRESSOR_CFG  *  pCompressor,  QY_AUDIO_HEADER  *  pAh_compress,  QY_AUDIO_HEADER  *  pAh_decompress,  MY_DMO_INFO  *  pDmoInfo  );
int  decompressAudio_filterGraph(  MY_DMO_INFO  *  pDmoInfo,  QY_AUDIO_HEADER  *  pAh_compress,  BYTE  *  pInput,  unsigned  int  uiInputLen,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  );
#endif

//////////////  2015/03/11


//
//  2016/03/13
typedef  struct  __p_sendAvInfo_taskInfo_t  {

				 //  i
				 struct							{
					 unsigned  char				ucbVideoConference;		//  2017/08/02
					 //
					 unsigned  char				ucbAvConsole;			//   2017/07/17
					 //
					 unsigned  short			usConfType;				//  2017/08/25
					 
					 //
					 QY_MESSENGER_ID			idInfo_initiator;

					 //
#if 0
					 unsigned  __int64			ui64MeetingId_hg;
					 int						iMeetingType_hg;
#endif
					 //
					 CONF_hg_info				hgInfo;

					 //
				 }								i;

				 //  o
				 struct							{

					 //
					 int						iTaskId;
					 //  
					 QY_MESSENGER_ID			idInfo_starter;			//.ui64Id  =  rcd.idInfo_send.ui64Id;
		
					 //
					 time_t						tStartTime_org;			//  =  rcd.tSendTime;
					 unsigned  int				uiTranNo_org;			//  =  rcd.uiTranNo;
					 unsigned  int				uiContentType_org;		//  =  rcd.uiContentType;

					 //
					 unsigned  char				ucbStarter;				//  =  pContent->myTask.ucbStarter;									//  2010/08/31
					 unsigned  char				ucbVideoConference;		//  =  pContent->myTask.ucbVideoConference;					//  2010/08/31
				 
					 //
					 unsigned  int				uiInitW;				//  =  pContent->tranInfo.video.vh_decompress.bih.biWidth;
					 unsigned  int				uiInitH;				//  =  pContent->tranInfo.video.vh_decompress.bih.biHeight;
				 
					 //  2014/09/25
					 int						iIndex_taskInfo;		//  =  pContent->myTask.iIndex_taskInfo;

					 //
					 AV_stream_simple			local_avStream;

				 }								o;

}		 P_sendAvInfo_taskInfo;


//
__declspec(  dllexport  )  int  getMosaicTranInfo(  SHARE_dyn_bmp  *  pShareDynBmp,  MOSAIC_TRAN_INFO  *  p  );


//  
__declspec(  dllexport  )  int  procSendAvInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType, PARAM_startAvCall* pParam, COMPRESS_VIDEO  *  pCompressVideo,  COMPRESS_AUDIO  *  pCompressAudio,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  TALKER_dynBmp  *  pTalkerDynBmp,  QY_MESSENGER_ID  *  p_content_idInfo_logicalPeer,  int  *  piTaskId,  MSGR_ADDR  *  pAddr,  P_sendAvInfo_taskInfo  *  pPst  );
//  2015/03/11
__declspec(  dllexport  )  int  procSendAvInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType,  COMPRESS_VIDEO  *  pCompressVideo,  COMPRESS_AUDIO  *  pCompressAudio,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  TALKER_dynBmp  *  pTalkerDynBmp,  QY_MESSENGER_ID  *  p_content_idInfo_logicalPeer,  TASK_av_props  *  pTaskAvProps,  int  *  piTaskId,  MSGR_ADDR  *  pAddr  );
//  2014/11/22
__declspec(  dllexport  )  int  procSendAvInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType,  COMPRESS_VIDEO  *  pCompressVideo,  COMPRESS_AUDIO  *  pCompressAudio,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  TALKER_dynBmp  *  pTalkerDynBmp,  QY_MESSENGER_ID  *  p_content_idInfo_logicalPeer,  unsigned  int  uiTranNo_avTask_starter,  int  *  piTaskId,  MSGR_ADDR  *  pAddr  );
//
__declspec(  dllexport  )  int  procSendAvInfo_conf(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType,  VIDEO_CONFERENCE_CFG  *  pVideoConferenceCfg,  TALKER_policy  *  pTalkerPolicy, PARAM_startAvCall  *  pParam,  AV_COMPRESSOR_CFG  *  pAvCompressor_conf,  QMC_mosaic_maker  *  pMosaic,  COMPRESS_VIDEO  *  pCompressVideo,  COMPRESS_AUDIO  *  pCompressAudio,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  TALKER_dynBmp  *  pTalkerDynBmp,  QY_MESSENGER_ID  *  p_content_idInfo_logicalPeer,  int  *  piTaskId,  MSGR_ADDR  *  pAddr,  P_sendAvInfo_taskInfo  *  pPst  );


//
__declspec(  dllexport  )  int  procSendAvReplyInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  MIS_MSG_TASK  *  pMsgTask,  unsigned  char  ucbSendLocalAv,  int  iIndex_sharedObj,  int  iTaskId,  DYN_BMP_rule  *  pDynBmp,  TASK_av_props  *  pTaskAvProps,  MSGR_ADDR  *  pAddr  );

//  2014/10/09
//__declspec(  dllexport  )  int  procSendTaskProcReq(  MIS_CNT  *  pMisCnt,  unsigned  short  usCode,  unsigned  short  usOp,  time_t  tStartTime_org,  unsigned  int  uiTranNo_org,  unsigned  int  uiContentType_org,  int  iTaskId,  unsigned  int  uiTaskType,  QIS_res_obj  *  pDynBmp,  unsigned  int  uiChannelType,  BOOL  bOutputDirectly,  LPCTSTR  pHint,  MSGR_ADDR  *  pAddr  );
__declspec(dllexport)  int  procSendTaskProcReq(MIS_CNT* pMisCnt, unsigned  short  usCode, unsigned  short  usOp, time_t  tStartTime_org, unsigned  int  uiTranNo_org, unsigned  int  uiContentType_org, QY_MESSENGER_ID idInfo_imGrp_related, int  iTaskId, unsigned  int  uiTaskType, QIS_res_obj* pDynBmp, unsigned  int  uiChannelType, BOOL  bOutputDirectly, LPCTSTR  pHint, MSGR_ADDR* pAddr);

//
__declspec(  dllexport  )  int  procSendGpsInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  void  *  pReserved,  int  *  piTaskId,  MSGR_ADDR  *  pAddr  );
__declspec(  dllexport  )  int  procSendGpsReplyInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  MIS_MSG_TASK  *  pMsgTask,  unsigned  char  ucbSendLocalAv,  int  iIndex_sharedObj,  MSGR_ADDR  *  pAddr  );



//
int  startToRefreshRecentFriends(  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsgBuf  );
__declspec(  dllexport  )  int  setPasswd_isClient(  HWND  hParent  );


 //

 //
//
BOOL  isSlaveOfMaster(  int  iIndex_sharedObj_slave,  QY_SHARED_OBJ  *  pSharedObj_slave,  int  iIndex_sharedObj_master,  QY_SHARED_OBJ  *  pSharedObj_master  );
//
BOOL  bExists_slave(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj_master  );
BOOL  bExists_master(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj_slave  );


//
int  addSlaveToMaster(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj_slave,  int  iIndex_sharedObj_master  );
int  removeSlaveFromMaster(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj_slave,  int  iIndex_sharedObj_master  );



MIS_CHANNEL  *  getChannelByType(  MIS_CNT  *  pMisCnt,  unsigned  int  uiChannelType  );
BOOL  bChannelOk(  MIS_CHANNEL  *  pChannel,  Param_dbg  *  pParam  );
//
BOOL  bMisCntOnline(  QY_MC  *  pQyMc,  MIS_CNT  *  pMisCnt  );
//
BOOL  bMeOnline(  QY_MC  *  pQyMc  );
//BOOL  bMessengerTalking(  QY_MC  *  pQyMc  );
BOOL  bChkMessengerChannelsReady(  QY_MC  *  pQyMc  );

typedef  struct  __qmObjQParamMisClient_t		{
				 unsigned  int					uiType;
				 QY_SERVICEGUI_INFO			*	pSci;
				 MIS_CNT					*	pMisCnt;
				 void						*	pDb;
				 int							iDbType;
				 int							iObjType;
				 QY_MESSENGER_INFO			*	pClient;
}		 QMOBJQ_PARAM_MISCLIENT;


int  addToDisplayedObjQ(  MC_CTX_DISPLAYEDWND  *  pCtx,  QMOBJQ_PARAM_MISCLIENT  *  pParam,  HWND  hWnd,  HTREEITEM  hItem  );
int  addToDisplayedObjQ(  MC_CTX_DISPLAYEDWND  *  pCtx,  QMOBJQ_PARAM_MISCLIENT  *  pParam,  HWND  hWnd,  int  iObjId  );

__declspec(  dllexport  )  int  postMsg2MgrFunc_mc(  void  *  pMIS_CNT,  MSG_ROUTE  *  pRoute,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  short  usSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  
						QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  
						QY_MESSENGER_ID	 *  pIdInfo_taskSender,					
						QY_MESSENGER_ID	 *  pIdInfo_taskReceiver,				
						QY_MESSENGER_ID  *  pIdInfo_dst,  
						unsigned  int  uiChannelType,
						MIS_MSGU  *  pMsgBuf  =  NULL,  BOOL  bLog  =  FALSE  );

__declspec(  dllexport  )  int  makeMsg2MgrFunc_mc(  MIS_CNT  *  pMisCnt,  MSG_ROUTE  *  pRoute,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  short  usSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  
							QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  
	 						QY_MESSENGER_ID	 *  pIdInfo_taskSender,					
							QY_MESSENGER_ID	 *  pIdInfo_taskReceiver,				
							QY_MESSENGER_ID  *  pIdInfo_dst,  
							unsigned  int  uiChannelType,  MIS_MSGU  *  pMsg,  int  *  pMsgLen  );



#if  0	//  ndef  __DEBUG__

#define  postMsg2Mgr_mc(  pMisCnt,  pRoute,  uiMisMsgType,  ucFlg,  usCode,  tStartTime,  uiTranNo,  uiSeqNo,  data,  dataLen,  pIdInfo_logicalPeer,  pIdInfo_dst,  uiChannelType,  pMsgBuf,  bLog  )  \
			postMsg2MgrFunc_mc(  pMisCnt,  pRoute,  uiMisMsgType,  ucFlg,  usCode,  tStartTime,  uiTranNo,  uiSeqNo,  0,  0,  data,  dataLen,  pIdInfo_logicalPeer,  NULL,  NULL,  pIdInfo_dst,  uiChannelType,  pMsgBuf,  bLog  )

#define  postMsgTask2Mgr_mc(  pMisCnt,  uiMisMsgType,  ucFlg,  usCode,  tStartTime,  uiTranNo,  uiSeqNo,  iTaskId,  uiTaskType,  data,  dataLen,  pIdInfo_logicalPeer,  pIdInfo_taskSender,  pIdInfo_taskReceiver,  pIdInfo_dst,  uiChannelType,  pMsgBuf,  bLog  )	\
			postMsg2MgrFunc_mc(  pMisCnt,  NULL,  uiMisMsgType,  ucFlg,  usCode,  tStartTime,  uiTranNo,  uiSeqNo,  iTaskId,  uiTaskType,  data,  dataLen,  pIdInfo_logicalPeer,  pIdInfo_taskSender,  pIdInfo_taskReceiver,  pIdInfo_dst,  uiChannelType,  pMsgBuf,  bLog  )

#else
  __declspec(  dllexport  )  int  postMsg2Mgr_mc(  void  *  pMIS_CNT,  MSG_ROUTE  *  pRoute,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf  =  NULL,  BOOL  bLog  =  FALSE  );
  __declspec(  dllexport  )  int  postMsgTask2Mgr_mc(  void  *  pMIS_CNT,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_taskReceiver,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf  =  NULL,  BOOL  bLog  =  FALSE  );
#endif


//
int  postMsg2OutputQ_mc(  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsg,  unsigned  int  msgLen,  MIS_CHANNEL  *  pChannel  );


//  2014/11/21
typedef  struct  __param_findOrgMsg_t		{
				 BOOL						bNeedUpdate;
				 //
				 void					*	pMsgTask_o;
}		 PARAM_findOrgMsg;



//  
int  tmpHandler_findOrgMsgAndProc_is(  QY_MC  *  pQyMc,  void  *  pMsg_toBeSearchedParam,  void  *  p1,  TASK_common  *  taskElem  );

//
//  2015/01/22
int  myShowInfo(  MC_VAR_common  *  pProcInfo,  void  *  p1,  LPCTSTR  hint  );

//
int  getStr_welcomeToUse(  CCtxQmc  *  pProcInfo,  TCHAR  *  hint0,  int  cnt  );

//
BOOL  bRefreshMeStatus_wnd(  MIS_MSG_REFRESHMESTATUS_QMC  *  pMsg,  MC_CTX_DISPLAYEDWND  *  pCtx,  PF_commonHandler  pf,  void  *  pWndParam  );
BOOL  bRefreshContactsStatus_wnd(  MIS_MSG_REFRESHCONTACTSSTATUS_QMC  *  pMsg,  MC_CTX_DISPLAYEDWND  *  pCtx,  PF_commonHandler  pf,  void  *  pWndParam  );

//  int  getIdInfo_logicalPeer(  QY_SERVICEGUI_INFO  *  pSci,  MIS_CNT  *  pMisCnt,  MSG_SIMPLE_ROUTE  *  pAddr,  QY_MESSENGER_ID  *  pIdInfo_virtualPeer  );
int  getIdInfo_logicalPeer(  QY_SERVICEGUI_INFO  *  pSci,  MIS_CNT  *  pMisCnt,  MSG_ROUTE  *  pAddr,  MSGR_ADDR  *  pAddr_virtualPeer  );
int  myGetPeer(  LPCTSTR  misServName,  MSG_ROUTE  *  pRoute,  MSGR_ADDR  *  pAddr_logicalPeer,  MSGR_ADDR  *  pPeer  );

int  testLocalAv_openLocalVideo(  HWND  hWnd_testWebcam,  void  *  pADeviceGuid,  LPCTSTR  capDevDesc,  void  *  pMoniker,  BOOL  *  pbGot_sharedObjIndex_localAv,  int  *  piIndex_sharedObj  );


#endif  //  }


