

#ifndef		__QNMCOMMPROCMIS_H__
#define		__QNMCOMMPROCMIS_H__  //  {


///////////
#include	"myTypes.h"
//
#include	"qnmCommProc_is_open.h"
#include	"qmcDebugStatusInfo.h"
#include	"saveAvProc_open.h"
#include	"ipcProc_open.h"
//
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"ancPktProcessPublic.h"



//  #define		CONST_maxMisServNameLen								128
#define		CONST_maxMisServNameLen									32					//  2010/08/05

//  
#define		CONST_qyMessengerIdStrLen								20					//  18					//  
//
#define		DEFAULT_initialMessengerId_ui64Id						99
//
#define		CONST_invalidMessengerId								-1					//  2007/07/28 





//
#define		CONST_maxConnsPerCli_mis								7					//  
																						
//
#define		MAX_grpsAMsgrBelongsTo									50					//  2011/04/18
																						
//
#define		CONST_maxTmpMessengers									200					//  

//
//#define		CONST_maxMsgrs_sendTo								32					//  
#define		CONST_maxMsgrs_sendTo									5000				//  2025/01/20

//
#define		MAX_mems_taskAv											512					//  
//
#define		MAX_speakers_taskAv										25		//  16		//8					//  


//
#define		MAX_bitrateInKbps										10000				//  10兆


//
#define		MAX_real_speakers_taskAv_vp8							16		//  12	//8					//  
#define		MAX_real_speakers_taskAv_h264							25		//  9		//  6		//  12	//8					//  


//
#define		DEFAULT_usMaxSpeakers									9

//
//#define		DEFAULT_maxSpeakers										16	//8					//  2014/12/05

//
//#define		MAX_speakers_3d_win32									4					//  2014/12/05. 3d会议里，因资源短缺，所以限制到4



//
#define		MAX_mosaicMems_taskAv									2	//  1
#define		MAX_resourceMems_taskAv_conf							4
//
#define		MAX_resourceMems_taskAv_p2p								2

//
//
//#define		MAX_videoConferenceMems									MAX_speakers_taskAv  +  MAX_mosaicMems_taskAv  +  MAX_resourceMems_taskAv_conf  
#define		MAX_conf_activeMems										MAX_speakers_taskAv  +  MAX_mosaicMems_taskAv  +  MAX_resourceMems_taskAv_conf  
//
#define		MAX_conf_requestingMems									10					//  




//  
//#define		CONST_maxTransferAvDataMems								32					//  2009/02/16
#define		CONST_maxTransferAvDataMems								160		//  32					//  2009/02/16



//  #define			DEFAULT_mems_taskAv									128
#define		DEFAULT_mems_taskAv										256					//  2012/02/21



//
#define		DEFAULT_bUseAec											TRUE				//  2013/05/25
#define		DEFAULT_bFeatrModeOn									FALSE	//  TRUE				//  2014/08/17
#define		DEFAULT_bNoiseSup										TRUE				//  
#define		DEFAULT_bAGC											TRUE				//  
#define		DEFAULT_bCntrClip										TRUE				//  

//  
#define		CONST_channelType_null									0
#define		CONST_channelType_talking								1					//  
#define		CONST_channelType_robot									2
#define		CONST_channelType_webSending							3					//  2007/12/12, wemQm
#define		CONST_channelType_media									4					//  2008/03/15
#define		CONST_channelType_realTimeMedia							5					//  2008/04/17
#define		CONST_channelType_rtOp									6					//  2016/12/26


//
extern  QY_DMITEM  CONST_channelTypeTable[];
//extern  QY_DMITEM  CONST_qyAppAvLevelTable_en[];
extern  QY_DMITEM  CONST_moduleTypeTable_en[]; 

//
extern  QY_DMITEM  CONST_subSystemIdTable_en[];

//////////////////
//


//  #define		CONST_usMaxContactUpdateInfosPerSnd_isCli				100					//  2007/07/26
//


//
#define		DEFAULT_dFramesPerSec_mediaFile							29.97												// 30 frames per sec
#define		DEFAULT_AvgTimePerFrame_mediaFile						(  10000000 / DEFAULT_dFramesPerSec_mediaFile  )	//  2010/06/18

#define		DEFAULT_AvgTimePerFrame									1000000.
#define		DEFAULT_AvgTimePerFrameInMs								DEFAULT_AvgTimePerFrame  /  10000
//


/////////////



#if  0
//
//  2016/02/18
typedef  struct  __playerId_t										{
				 int												index_player;
				 unsigned  int										uiTranNo_player;
}		 PLAYER_ID;

//
#define		isSame_playerId(p1,p2)		( (p1)->index_player==(p2)->index_player && (p1)->uiTranNo_player  ==  (p2)->uiTranNo_player  )
#endif 


//
//////
//

#if  0
typedef  struct  __msgSimpleRoute_t									{										//  
				 QY_MESSENGER_ID									idInfo_to;
				 QY_MESSENGER_ID									idInfo_from;
}		 TALKDATA_ADDR_unused, MSG_SIMPLE_ROUTE;
#endif 

//
typedef  struct  __msgDebugInfo_t									{
				 __int64											tTime_serv_startToRecv;					//  iocpÆðÊ¼ÊÕ°üÊ±¼ä( s )
				 unsigned  short									usElapsed_serv_recved;					//  ÊÕÍê
				 unsigned  short									usElapsed_serv_startToProcess;			//  ¿ªÊ¼´¦Àí		
				 unsigned  short									usElapsed_serv_toFindDst;				//  ÔÚÑ°ÕÒÄ¿±ê¶ÔÏóÖ®Ç°¡£
				 unsigned  short									usElapsed_serv_toBeSwitched;			//  ·ÖÈë
				 unsigned  short									usElapsed_serv_toSend;					//  ×¼±¸·¢ËÍ
}		 MSG_DEBUG_INFO;


//  2012/11/09
#if  defined(  __DEBUG__  )  &&  0
	#define		M_debugInfo_pktNo								long	lPktNo;
	#define		M_pkt_setNo(  tn,  lLastPktNo,  pkt  )			{	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );  if  (  !tn  )  tn  =  InterlockedIncrement(  &pProcInfo->debugInfo.lLastTn_pktNo  );  (  pkt  ).debugInfo.lPktNo  =  tn  *  10000000  +  InterlockedIncrement(  &lLastPktNo  );  if  (  10  )  {  M_pkt_showNo(  pkt,  _T(  "init"  )  );  }	}
	#define		M_pkt_showNo(  pkt,  hint  )					{  	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsCli"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "pktNo: %d, %s"  ),  (  pkt  ).debugInfo.lPktNo,  hint  ?  hint  :  _T(  ""  )  );  }
	#define		M_msg_setNo(  pkt,  msg  )						{   (  msg  ).lPktNo  =  (  pkt  ).debugInfo.lPktNo;  }
	#define		M_msg_showNo(  msg,  hint  )					{  	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsCli"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "pktNo: %d, %s"  ),  (  msg  ).lPktNo,  hint  ?  hint  :  _T(  ""  )  );  }

	#define		M_pkts_showNo(  pkts,  nPkts,  hint  )			{  int  i;		for  (  i  =  0;  i  <  (  nPkts  );  i  ++  )  {  M_pkt_showNo(  (  pkts  )[i],  hint  );  }  }


	#define		M_pkts_showNo_vpp(  pkts,  nPkts  )				//  M_pkts_showNo(  pkts,  nPkts,  _T(  "vpp"  )  )
	#define		M_pkts_showNo_encVideo(  pkts,  nPkts  )		//  M_pkts_showNo(  pkts,  nPkts,  _T(  "encVideo"  )  )
	#define		M_pkts_showNo_encVideo_post(  pkts,  nPkts  )	//  M_pkts_showNo(  pkts,  nPkts,  _T(  "encVideo_post"  )  )
	#define		M_pkts_showNo_playVideo(  pkts,  nPkts  )		M_pkts_showNo(  pkts,  nPkts,  _T(  "playVideo"  )  )

#else
	#define		M_debugInfo_pktNo								
	#define		M_pkt_setNo(  tn,  lLastPktNo,  pkt  )			
	#define		M_pkt_showNo(  pkt,  hint  )					
	#define		M_msg_setNo(  pkt,  msg  )						
	#define		M_msg_showNo(  msg,  hint  )					

	#define		M_pkts_showNo(  pkts,  nPkts,  hint  )			


	#define		M_pkts_showNo_vpp(  pkts,  nPkts  )				
	#define		M_pkts_showNo_encVideo(  pkts,  nPkts  )		
	#define		M_pkts_showNo_encVideo_post(  pkts,  nPkts  )	
	#define		M_pkts_showNo_playVideo(  pkts,  nPkts  )		
#endif


//  2011/12/08
typedef  struct  __debug_myDRAW_VIDEO_DATA_t						{
				 DWORD												dwTickCnt_start;
				 unsigned  short									usToEncInMs;
				 unsigned  short									usEncedInMs;
				 unsigned  short									usPostInMs;
				 unsigned  short									usToDispatchInMs;
				 unsigned  short									usOutputInMs;
				 unsigned  short									usPreTransInMs;
				 unsigned  short									usTransInMs;
				 
				 //
				 DWORD												dwTickCnt_proc_io_read;						//  2015/09/05
				 DWORD												dwTickCnt_doPretrans;						//  2015/02/24
				 DWORD												dwTickCnt_drawVideoData;					//  2015/09/06
				 DWORD												dwTickCnt_playPkt_start;					//  2015/09/11
				 
				 //  2015/09/05
				 unsigned  int										uiTranNo_msgTask;							//  2015/09/05
				 
				 //
				 M_debugInfo_pktNo																				//  2012/11/09
				 //
}		 DEBUG_myDRAW_VIDEO_DATA;


//
typedef  struct  __routeDebugInfo_t									{										//  ´Ë½á¹¹ÎªÁËÁË½âÊý¾Ý°üµÄ´«Êä¹ý³Ì¶øÉè¼Æ.Í¨³£,dwTickCnt...ÊÇ²»ÓÃ´«ÊäµÄ.
				 
				 // 发起端
				 DWORD												dwTickCnt_me_start;						//  clientÆðÊ¼·¢ËÍÇëÇó
				 //
				 __int64											tTime_start;							//  ¿ªÊ¼·¢ËÍ
				 unsigned  short									usElapsed_toSend;						//  ×¼±¸·¢ËÍ

				 //  2008/11/19
				 int												index;									//  uiDataBlockIndex

				 //
				 DWORD												dwTickCnt_serv_startToRecv;				//  iocp ( ms ). 
				 
				 //  2015/08/15
				 DWORD												dwTickCnt_processQ;						
				 DWORD												dwTickCnt_processQ2Grp;
				 //
				 DWORD												dwTickCnt_postMsg2OutputQ_imGrp;
				 //
				 DWORD												dwTickCnt_doMisMgr_processSelf_imGrp;
				 //
				 DWORD												dwTickCnt_tmpHandler_talkToGrpMem_bt;
				 DWORD												dwTickCnt_postMsg2OutputQ_messenger;

				 //
				 int												nSym;
				 TCHAR												tHint[64];

				 //  server转发请求
				 MSG_DEBUG_INFO										req;


				 //  接受并响应端
				 DWORD												dwTickCnt_peer_recved;
				 __int64											tTime_peer_recved;
				 unsigned  short									usElapsed_peer_resp_toSend;
				 
				 //  server转发响应
				 MSG_DEBUG_INFO										resp;

				 //  响应回到发起端
				 DWORD												dwTickCnt_resp_recved;
				 unsigned  short									usElapsed_resp_end;

				 //  2011/12/08
				 DEBUG_myDRAW_VIDEO_DATA							debug_myDRAW_VIDEO_DATA;				//  2011/12/08

				 //
				 unsigned  int										uiStep_showInfo;						//  ÎªÁË¸øshowInfoÌá¹©Çø·ÖÍ¬Ò»¸öÊ±¿Ì(ms)µÄÔç³ÙµÄ²ÎÊý

}		 ROUTE_DEBUG_INFO;


//  2008/02/07, misServerName,idInfo,subPath
//  subPath com0 dev=com0.
//  uiDevType_to wDevIdStr_from
//
typedef  struct  __msgRoute_t										{								//  
				 QY_MESSENGER_ID									idInfo_to;						//  2007/11/30, TALKDATA_ADDR
				 QY_MESSENGER_ID									idInfo_from;					//	
				 //
				 unsigned  int										uiDevType_to;					//
				 //WCHAR												wDevIdStr_to[128];				//	2008/01/04, 
				 unsigned  int										uiDevType_from;					//
				 //WCHAR												wDevIdStr_from[128];			//  2008/01/04
				 //  
				 //  path mailto:qycx@qycx.com|sm:13001101101|http://www.qycx.com/			
				 //																					
				 //
				 //
				 struct												{
					 QY_MESSENGER_ID								idInfo;
				 }													mems_to[CONST_maxMsgrs_sendTo];	//  2008/03/27, 
				 
				 //
				 unsigned  int										uiMsgRouteId;					//  2008/05/27, msgRoute
				 
				 //																					//  peer.
				 //  unsigned  int									uiWebSessId;					//  webMessenger
				 unsigned  int										uiLogonId;						//  webMessenger
				 //
				 unsigned  long										uiObjType_src;					//  messengerType, 
				 //
				 unsigned  short									usLangId_from;					//  
				 unsigned  long										ulDetectedIp_from;
				 WCHAR												displayName_from[64  +  1];
				 //

				 //  2008/05/15
				 ROUTE_DEBUG_INFO									debugInfo;
				 
				 //  2009/09/12
				 struct												{
					 unsigned  short								usCnt_mems_to;
				 }													tmpInternal;

}		 MSG_ROUTE;		 


//
//  MSGR_ADDR;	//  
//

typedef  struct  __msgrAddr_t										{
				 QY_MESSENGER_ID									idInfo;						
				 //
				 TCHAR												misServName[CONST_maxMisServNameLen  +  1];
				 //
				 unsigned  int										uiDevType;						//
				 WCHAR												wDevIdStr[128];					//   2008/01/04,
				 WCHAR												wPath[510  +  1];				//  
				 //																					//  
				 //  unsigned  int									uiWebSessId;					//  webMessenger
				 unsigned  int										uiLogonId;						//  webMessenger
				 //
				 unsigned  int										uiObjType;
				 //
				 WCHAR												displayName[64  +  1];
				 //
				 //
				 																					//  2008/02/12, MSGR_ADDR messenger
																									//  
				 BOOL												bInNoticeMode;					//  2008/01/22, 
																									//				
																									//				
                 time_t												tStartTime_notice;				//  tStartTime_notice uiTranNo_notice
				 unsigned  int										uiTranNo_notice;				//

				 //  2012/04/20
				 unsigned  int										uiTranNo_shadow;				//  用来标识辅助talker窗口,为0时为主窗口

				 //  2013/07/31
				 //int												iNo_debug;						//  用来标识talker类实例,用来debug用. 2013/07/31

}		 MSGR_ADDR;



//
//
typedef  struct  __btGrpMem_t									{
				 QY_MESSENGER_ID								idInfo;
				 void								*			pQMem;
}		 BT_grp_mem;


//
#define		MAX_btGrpMems										5000


//
typedef  struct  __btGrpMems_t									{
				 //
				 void								*			pQMemGrp;
				 //
				 unsigned  short								usCnt;
				 BT_grp_mem										mems[MAX_btGrpMems];
}		 BT_grp_mems;


//
/////////////
//

typedef  struct  __policyImAuthCond_t								{
				 unsigned  char										ucbUseMac;
				 unsigned  char										ucbUsePcName;
				 unsigned  char										ucbUseDomainName;
				 unsigned  char										ucbUseOsUsrName;
				 //
				 unsigned  char										ucbUseMessengerName;
				 //
				 unsigned  char										ucbAutoVerification;			//  
				 //
				 unsigned  char										ucbNeedValidIpForDevice;		//
				 char												startIp[15  +  1];				//  2011/03/23. 只有在此ip范围内的设备能够被识别为dev messenger。
				 char												endIp[15  +  1];
				 //
}		 POLICY_imAuthCond;


typedef  struct  __qyMessengerPcInfo_t								{
				 int												id;

				 TCHAR												misServName[CONST_maxMisServNameLen  +  1];
				 QY_MESSENGER_ID									idInfo;
				 //
				 //
				 unsigned  int										uiType;
				 //
				 int												iPlatformId;
				 //
				 TCHAR												pcName[255  +  1];
				 TCHAR												domainName[255  +  1];
				 TCHAR												osUsrName[255  +  1];
				 //
				 time_t												tLastModifiedTime;
				 	
}		 QY_MESSENGER_PCINFO;


typedef  struct  __qyMessengerInfo_t								{

				 unsigned  int										uiType;										//  messengerType, me, messenger, group

				 int												iRcdId;										//  qyMessengerTab id
				 
				 TCHAR												misServName[CONST_maxMisServNameLen  +  1];
				 QY_MESSENGER_ID									idInfo;

				 //
				 unsigned  int										uiLogonId;									//  2007/12/22
				 time_t												tTime_logon;								//  2022/02/02
				 WCHAR												wLocation[64  +  1];

				 //
				 char												ip[CONST_qyMaxIpLen  +  1];
				 char												detectedIp[CONST_qyMaxIpLen  +  1];

				 unsigned  short									usLangId;
				 //
				 unsigned  int										uiDevType;
				 //
				 WCHAR												messengerName[64  +  1];

				 //
				 int												iRole;										//  2017/08/14

				 //
				 time_t												startTime;
				 //
				 unsigned  short									usRunningStatus;							//  2007/06/07 

				 time_t												tLastModifiedTime;

				 char												clientVer[CONST_qyMaxVerLen  +  1];
				 //
				 unsigned  short									shClientVer;				// clientVer[0-3];
				 BYTE												blClientVer;				// clientVer[4-5];		//  2005/05/23, lhQwmVer  =  atol(  qwmVer  )  /  100;  llQwmVer  =  atol(  qwmVer  )  %  100;
				 BYTE												b_mantissa_clientVer;		// clientVer[6-7]
				 
				 //
				 int												iStatus;										
				 

}		 QY_MESSENGER_INFO;



//  ´Ë½á¹¹²»ÓÃÀ´´«Êä£¬Òª×ª»»³ÉÁ÷²Å½øÐÐ´«Êä
typedef  struct	 __qyMessengerRegInfo_t								{
				 unsigned  int										uiType;
				 //
				 int												id;

				 int												iCustomId;

				 //  TCHAR												misServName[CONST_maxMisServNameLen  +  1];
				 //  QY_MESSENGER_ID									idInfo;
				 MSGR_ADDR											addr;

				 char												regTime[CONST_qyTimeLen  +  1];
				 char												auditTime[CONST_qyTimeLen  +  1];
				 char												tLastModifiedTime[CONST_qyTimeLen  +  1];
				 char												tCommitTime[CONST_qyTimeLen  +  1];

				 unsigned  int										uiFieldIds[CONST_qnmMaxRegFields];
				 union												{
					 //  WCHAR											cols[CONST_qnmMaxRegFields][256];
					 WCHAR											cols[CONST_qnmMaxRegFields][64  +  1];		//  2007/12/01, ÒòÎªMIS_MSGU¹ý´ó£¬Ôì³Éstack overflow,¹Ê½«×Ö¶Î´óÐ¡ÏÞÖÆÔÚ64¸ö×Ö·û.
				 }													u;

				 void									*			pInternal;							//  ÒÔÏÂÎªÄÚ²¿±äÁ¿£¬²»ÓÃÀ´Í¨ÐÅ
				 //
				 QNM_FIELD											fields[CONST_qnmMaxRegFields];		//  2007/08/03, ´ú±íÁËÊý¾Ý¿âÀïµÄ´æ´¢Êý¾Ý
				 //
				 int												index;

}		 QY_MESSENGER_REGINFO;


/////////
//




typedef  struct  __refreshImObjRuleReqMem_t							{
				 QY_MESSENGER_ID									idInfo_related;
				 unsigned  int										uiRuleType;
				 unsigned  short									usIndex;
				 unsigned  int										uiCmd;
				 //  
				 WCHAR												wDesc[128];			//  2011/11/13
}		 REFRESH_imObjRule_reqMem;


#define		MAX_imObjRule_reqMems									10
//
#define		DEFAULT_maxImObjRule_reqMems							10					//  当req.usMaxMemsPerSnd为0时，取此值. 不能修改. 2011/11/13


//
typedef  struct  __refreshImObjRulesReq_t							{
				 unsigned  int										uiType;

				 unsigned  char										ucbResp;
				 unsigned  char										ucbRetrieveAll;

				 unsigned  short									usMaxMemsPerSnd;			//  2011/11/13

				 union												{
					 struct											{
						 unsigned  char								ucbNext;
						 //
						 QY_MESSENGER_ID							idInfo_related;
						 unsigned  int								uiRuleType;
						 unsigned  short							usIndex;
					 }												req;
					 struct											{
					 }												resp;

				 }													u;
				 unsigned  char										ucbEnd;


				 struct												{
					 unsigned  short								usCnt_mems;
				 }													tmpInternal;

				 unsigned  short									usCnt;
				 REFRESH_imObjRule_reqMem							mems[MAX_imObjRule_reqMems];				 
}		 REFRESH_imObjRules_req;


//  2011/11/13. qm的全局策略，也是存在数据库里
typedef  struct  __qyImRules_t										{
				 //  2011/10/15
				 //  unsigned  char										ucbShareWebcamInConference;						//  是否在会议中共享摄像机. 如果选是，则在会议自动接收时，要弹出共享窗口
				 QY_MESSENGER_ID									conferenceId_shareWebcam;
				 unsigned  char										ucbNoLocalVideoInThisConference;				//  是否在这个会议中启动视频. 2011/10/22
				 //
				 unsigned  char										ucbDistinguishSharedWebcams;					//  是否区分被共享的摄像机，（是否使用序号）
				 //
}		 QY_im_rules;

//  
typedef  struct  __qyImObjRules_t									{
				 unsigned  int										uiCmd_autoAnswer_av;
				 unsigned  int										uiCmd_autoAnswer_screen;	//  2010/12/18
				 unsigned  int										uiCmd_autoAnswer_mediaFile;	//  2010/12/18
}		 QY_imObj_rules;


int  imObjRulesReq2ImRules(  REFRESH_imObjRules_req  *  pReq,  QY_im_rules  *  pRules  );
int  imObjRulesReq2Rules(  REFRESH_imObjRules_req  *  pReq,  QY_MESSENGER_ID  *  pIdInfo_related,  QY_imObj_rules  *  pRules  );


//  2010/08/13
typedef struct  __qyImObjRuleRcd_t									{
				int													id;

				TCHAR												misServName[CONST_maxMisServNameLen  +  1];
				QY_MESSENGER_ID										idInfo;
				//
				unsigned  int										uiRuleType;				
				//
				unsigned  short										usIndex;
				QY_MESSENGER_ID										idInfo_related;
				unsigned  int										uiCmd;				
				//
				time_t												startTime;
				time_t												tLastModifiedTime;				
				//
				int													iStatus;				
				//
				WCHAR												col0[255  +  1];
#if  0
				
										"iCol0				int,"
										"iCol1				int,"
										"iCol2				int,"
										"iCol3				int,"
										"iCol4				int,"
										"iCol5				int,"
										"iCol6				int,"
										"iCol7				int,"
										"iCol8				int,"
										"iCol9				int,"
										"col0				varchar(255),"
										"col1				varchar(255),"
										"col2				varchar(255),"
										"col3				varchar(255),"
										"col4				varchar(255),"
										"col5				varchar(255),"
										"col6				varchar(255),"
										"col7				varchar(255),"
										"col8				varchar(255),"
										"col9				varchar(255),"
#endif
		 

}		 QY_imObjRule_rcd;


//  2012/08/05
typedef  struct  __ptzControlMem_t									{
				 int												nAddr;  
				 int												nPelcoType;
				 //
}		 PTZ_control_mem;

//
typedef  struct  __ptzControlReq_t									{
				 unsigned  int										uiType;

				 unsigned  char										ucbReply;


				 union												{
					 struct											{
					 }												req;
					 struct											{
						 time_t										tStartTime_org;
						 unsigned  int								uiTranNo_org;
						 //
						 TCHAR										tHint[255  +  1];		
					 }												reply;

				 }													u;


				 struct												{
					 unsigned  short								usCnt_mems;
				 }													tmpInternal;

				 unsigned  short									usCnt;
				 PTZ_control_mem									mems[8];				 
}		 PTZ_control_req;


//
typedef  struct  __ptzControlCmd_t									{
				 unsigned  int										uiType;

				 //
				 QY_MESSENGER_ID									idInfo_imGrp_related;

				 //
				 PTZ_cmd_common										cmdInfo;
				 
				 //
				 PTZ_cmdParamU										paramU;

				 //
}		 PTZ_control_cmd;



//
typedef  struct  __nvrControlCmd_t									{
				 unsigned  int										uiType;
				 
				 //
				 NVR_cmd_common										cmdInfo;

}		 NVR_control_cmd;



//  2010/01/06
typedef  struct  __qyMessengerAccount_t								{
				 unsigned  int										uiType;

				 //  int												iPasswdType;
				 char												messengerPasswd[255  +  1];


}		 QY_MESSENGER_ACCOUNT;

///////////
//



//  
//

#define		MACRO_setFieldIdInRegInfo(  regInfo  )			{		\
				int			Mi;										\
				QY_DMITEM	*	MpItem	=	NULL;					\
				for  (  Mi  =  0;  Mi  <  mycountof(  regInfo.uiFieldIds  );  Mi  ++  )  {	\
					 for  (  MpItem  =  CONST_regInfo2DbTable;  MpItem->type  !=  -1;  MpItem  ++  )  {	\
						  if  (  (  int  )MpItem->des  ==  Mi  )  break;										\
					 }																						\
					 if  (  MpItem->type  ==  -1  )  continue;												\
					 regInfo.uiFieldIds[Mi]  =  MpItem->type;												\
				}																							\
				}

#if  0
#define		MACRO_setPtrs(  CONST_fieldIdTable_en,  regInfo,  fields  )				{																								\
				int						Mindex		=	0;																											\
				QY_DMITEM		*		MpItem		=	NULL;																										\
				if  (  mycountof(  fields  )  ==  CONST_qnmMaxRegFields  &&  mycountof(  regInfo.uiFieldIds  )  ==  CONST_qnmMaxRegFields  )  {						\
					memset(  fields,  0,  sizeof(  fields  )  );																									\
					for  (  Mindex  =  0;  Mindex  <  CONST_qnmMaxRegFields;  Mindex  ++  )  {																			\
					     fields[Mindex].ptr  =  _T(  ""  );	 fields[Mindex].pName  =  _T(  ""  );																	\
					}																																				\
					for  (  Mindex  =  0;  Mindex  <  mycountof(  regInfo.uiFieldIds  );  Mindex  ++  )  {																\
						 if  (  !(  MpItem  =  qyGetDmItemByType(  CONST_regInfo2DbTable,  regInfo.uiFieldIds[Mindex],  sizeof(  QY_DMITEM  )  )  )  )  continue;		\
						 unsigned  int			Mi;																													\
						 if  (  (  Mi  =  (  unsigned  int  )MpItem->des  )  >=  CONST_qnmMaxRegFields  )  continue;													\
						 fields[Mi].pName  =  qyGetDesByType1(  CONST_fieldIdTable_en,  regInfo.uiFieldIds[Mindex]  );													\
						 fields[Mi].ptr  =  (  TCHAR  *  )regInfo.u.cols[Mindex];																						\
						 fields[Mi].bufSize  =  sizeof(  regInfo.u.cols[Mindex]  )  /  sizeof(  TCHAR  );																\
						 fields[Mi].iDataType  =  (  int  )MpItem->pData;																								\
					}																																				\
			}  }
#endif
 //  2013/02/10
 int  myMACRO_setPtrs(  QY_DMITEM  *  pCONST_fieldIdTable_en,  QY_DMITEM  *  pCONST_regInfo2DbTable,  QY_MESSENGER_REGINFO  &  regInfo,  QNM_FIELD  *  fields_unused  );
#define		MACRO_setPtrs(  CONST_fieldIdTable_en,  regInfo,  fields  )		myMACRO_setPtrs(  CONST_fieldIdTable_en,  CONST_regInfo2DbTable,  regInfo,  fields  )




////////////////////////////////

//  
typedef  struct  __imGrpInfo_t										{
				 unsigned  int										uiType;								//  2011/01/29
				 //
				 int												id;
				 TCHAR												misServName[CONST_maxMisServNameLen  +  1];
				 QY_MESSENGER_ID									idInfo;								//  
				 //
				 TCHAR												name[255   +  1];					//  
				 unsigned  short									usSubtype;							//  2014/01/31
				 //
				 QY_MESSENGER_ID									idInfo_creator;						// 2017/07/26
				 //
				 time_t												startTime;
				 time_t												tLastModifiedTime;
				 //
				 struct												{									//  2011/01/29
					 HWND											hWnd_status;
					 //
				 }													tmpInternal;

}		 IM_GRP_INFO;


//
#define		MAX_imGrpEx_mems										256				//  2018/11/20	//  64

//
typedef  struct  __imGrpExMem_t										{
				 QY_MESSENGER_ID									grpMmem_idInfo;
}		 ImGrpEx_mem;


//
typedef  struct  __imGrpEx_t										{
				 IM_GRP_INFO										common;
				 
				 //
				 unsigned  short									usOp;

				 //
				 struct												{
					 unsigned  short								usCnt_mems;
				 }													tmpInternal;

				 //
 				 unsigned  short									usCnt;
				 ImGrpEx_mem										mems[MAX_imGrpEx_mems];				 
				 
}		 IM_GRP_EX;


//
typedef  struct  __imGrpMem_t										{
				 unsigned  int										uiType;
				 int												id;
				 TCHAR												misServName[CONST_maxMisServNameLen  +  1];
				 QY_MESSENGER_ID									idInfo_grp;								
				 QY_MESSENGER_ID									idInfo_mem;
				 int												iRole;
				 time_t												startTime;
				 time_t												tLastModifiedTime;
				 int												iStatus;
}		 IM_GRP_MEM;


///
typedef  struct  __myRegDesc_t										{
				 TCHAR									*			pZb;
				 TCHAR									*			pBb;
				 TCHAR									*			pDw;
				 TCHAR									*			pBm;
				 TCHAR									*			pSyr;
}		 MY_REG_DESC;
//
int  regInfo2Desc(  void  *  p0,  QY_MESSENGER_REGINFO  *  pRegInfo,  MY_REG_DESC  *  pDesc,  TCHAR  *  talkDesc,  unsigned  int  uiCnt_talkDesc,  TCHAR  *  displayName,  unsigned  int  uiCnt_displayName  );
int  grpInfo2Desc(  void  *  p0,  IM_GRP_INFO  *  pGrpInfo,  TCHAR  *  talkerDesc,  unsigned  int  uiCnt_talkerDesc,  TCHAR  *  displayName,  unsigned  int  uiCnt_displayName  );


/////////////////



//
//
/////////////

typedef  struct  __customerServiceObjRcd_t							{
				 int												id;
				 TCHAR												misServName[CONST_maxMisServNameLen  +  1];
				 QY_MESSENGER_ID									idInfo;
				
				 //
				 unsigned  int										uiLangId;
				 unsigned  int										uiCategoryId;
				 
				 //
				 char												startIp[15  +  1];
				 char												endIp[15  +  1];

				 //
				 time_t												startTime;
				 time_t												tLastModifiedTime;

}		 CUSTOMER_serviceObj_rcd;


typedef  struct  __webContactRcd_t									{
				 int												id;
				 TCHAR												misServName[CONST_maxMisServNameLen  +  1];
				 QY_MESSENGER_ID									idInfo;
				 //
				 unsigned  char										ucbPublic;
				 //
				 TCHAR												grpDisplayName[255  +  1];
				 TCHAR												displayName[255  +  1];
				 //
				 unsigned  char										ucbImSwitchable;
				 //
				 time_t												startTime;
				 time_t												tLastModifiedTime;
				 //
				 int												iStatus;
				 //
}		 WEB_CONTACT_RCD;


///////////////////////////////////////
//


//  ÏÂÃæµÄ½á¹¹ÓÃÔÚÏµÍ³ÄÚ²¿Ê¹ÓÃ,²»ÄÜÓÃÀ´´«Êä,2007/08/12
typedef  struct  __qisEvent_t										{
				 long												id;
				 long												lHelpRand;										//	2003/11/15
				 //
				 TCHAR												misServName[CONST_maxMisServNameLen  +  1];
				 QY_MESSENGER_ID									idInfo;
				 //				 
				 char												detectedIp[15  +  1];							//  Í¨ÐÅ¼ì²âµ½µÄ¿Í»§¶ËIP
				 char												ip[15  +  1];									//  ip must be filled before qnmLogPcEvent
				 long												lEventType;										//  eventType must be filled before qnmLogPcEvent
				 int												iCustomId;										//  iCustomId must be filled before qnmLogPcEvent
				 char												localEventTime[14  +  1];									//  localEventTime must be filled before qnmLogPcEvent
				 char												localCntEventTime[14  +  1];								//  ´«Èë¹ÜÀíÖÐÐÄµÄ±¾µØµÄÊ±¼ä
				 char												cntEventTime[14  +  1];									//  ´«Èë¹ÜÀíÖÐÐÄµÄ¹ÜÀíÖÐÐÄµÄÊ±¼ä
				 TCHAR												comment[255  +  1];
				 TCHAR												cols[CONST_qnmMaxEventRegFields][255  +  1];	//  ÊÂ¼þ´¥·¢ÕßµÄÐÅÏ¢10ÁÐ   
				 TCHAR												usrName[255  +  1];
				 //
				 TCHAR												deses[CONST_qnmMaxEventDesFields][255  +  1];	//  ÊÂ¼þÃèÊö±¾ÉíµÄÐÅÏ¢10ÁÐ				 
				 TCHAR												dsnName[128  +  1];								//  2007/01/02
				 int												iStatus;										//  2006/06/02, Ôö¼Ó¶ÔÊÂ¼þµÄ´¦Àí×´Ì¬µÄÃèÊö
}		 QIS_EVENT;		









///////////




#define		CONST_usRunningStatus_null								0
#define		CONST_usRunningStatus_online							1
#define		CONST_usRunningStatus_offline							2
#define		CONST_usRunningStatus_away								3
#define		CONST_usRunningStatus_hide								4								//  2007/06/07, ÔÚÏß£¬ÀëÏß£¬Àë¿ª£¬ÒþÉíµÈ
#define		CONST_usRunningStatus_neverLogon						5								//  Î´ÉÏÏß¡£Ö¸´Ó·þÎñÆ÷¿ª»úºóÃ»ÓÐÉÏ¹ýÏß

//  extern  QY_DMITEM  CONST_usRunningStatusTable[];
extern  QY_DMITEM  CONST_usRunningStatusTable_en[];


//////////////
//

#define		CONST_displayedElemType_null							0
#define		CONST_displayedElemType_wndInfo							1					//  ´°¿ÚÃèÊö
#define		CONST_displayedElemType_messengerWnd					2					//  messengerºÍwndµÄ¹ØÁªÐÔ
#define		CONST_displayedElemType_messengerTree					3					//  messengerºÍtreeItemµÄ¹ØÁªÐÔ
#define		CONST_displayedElemType_meTree							4					//  meºÍtreeItemµÄ¹ØÁªÐÔ						


typedef  struct  __displayedElem_wndInfo_t							{
				 unsigned  int										uiType;
				 HWND												hWnd;
				 BOOL												bClosed;			//  ÊÇ·ñÎªcloseWindowÊÂºóµÄÏûÏ¢
				 TCHAR												wndName[32];
}		 DISPLAYEDELEM_WNDINFO;


typedef  struct  __displayedElem_messengetWnd_t						{
				 unsigned  int										uiType;
				 void										*		pMisCnt;			//  ÎªÁËÅÅÐò¿ìËÙ£¬²»ÄÜÔÚÕâÀïÊ¹ÓÃmisServName
				 QY_MESSENGER_ID									idInfo;
				 HWND												hWnd;
}		 DISPLAYEDELEM_MESSENGER_WND;


typedef  struct  __displayedElem_messengerTree_t					{
				 unsigned  int										uiType;
				 void										*		pMisCnt;
				 QY_MESSENGER_ID									idInfo;
				 HANDLE												hItem;
}		 DISPLAYEDELEM_MESSENGER_TREE;


typedef  union  __displayedElemU_t									{
				unsigned  int										uiType;
				DISPLAYEDELEM_WNDINFO								wndInfo;
				DISPLAYEDELEM_MESSENGER_WND							messengerWnd;
				DISPLAYEDELEM_MESSENGER_TREE						messengerTree;
				DISPLAYEDELEM_MESSENGER_TREE						meTree;				//  
				//
}		 DISPLAYEDELEM_U;


//////////////////////

//  2017/08/27
#include	"imCommType_defs.h"





//
///////////////////



//  2007/07/12£¬¹ØÓÚIMµÄÊý¾Ý°ü£¨ÄÚÈÝ²¿·Ö£©µÄ¸ñÊ½ËµÃ÷£©
//  1¡£¶ÔËùÓÐµÄimµÄÊý¾ÝÄÚÈÝ£¬¶¼ÒÔuiType¿ªÍ·£¬ËùÒÔuiTypeÊÇ×îÖ÷ÒªµÄ¸ñÊ½Çø·Ö·û
//  2¡£¶ÔÏìÓ¦£¬¿ÉÒÔÌá¹©Ò»¸ö¼òµ¥µÄ¸ñÊ½¡£ÒÔuiTypeºÍusCode_orgÀ´¿ªÍ·¡£uiTypeÎª0Ê±Ê¹ÓÃ¡£usCode_orgµÄÉèÁ¢ÊÇÒòÎªmisÏµÍ³ÖÐµÄÍ¨ÐÅÊý¾ÝÊÇÁ÷£¬ÓÐusCode_org¶Ô°üµÄ·ÖÁ÷µ½²»Í¬µÄ´¦ÀíÏß³ÌÓÐÀû£»uiType·Ç0Ê±£¬Ê¹ÓÃÏà¹Ø½á¹¹


typedef  struct  __imSimpleResp_t									{
				 unsigned  int										uiType;  
				 unsigned  short									usCmd_org;
				 unsigned  int										uiContentType_org;
				 int												iStatus;
				 //
}				 IM_SIMPLE_RESP;

#define		MACRO_makeImSimpleResp(  usCmd_org1,  uiContentType1,  iStatus1,  respSimple  )	{  memset(  &respSimple,  0,  sizeof(  respSimple  )  );  respSimple.uiType  =  CONST_imCommType_simpleResp;  respSimple.usCmd_org  =  usCmd_org1;  respSimple.uiContentType_org  =  uiContentType1;  respSimple.iStatus  =  iStatus1;  }


//  html¸ñÊ½ÎÄ±¾
#if  0
typedef  struct  __imHtmlContent_t									{
				 unsigned  int										uiType;								//  ´ËÀàÐÍ¿ÉÒÔ¶à¸öÖµ£¬Çø·Öhtml,txtµÈ¸ñÊ½
				 time_t												tStartTime_serv;					//  ×é»á»°²ÎÊý
				 unsigned  int										uiSerialNo;							//  ÔÚ×éÌÖÂÛÖÐ£¬ÓÃÀ´±íÊ¾·¢ÑÔË³Ðò¡£·½±ã×é³ÉÔ±¿Í»§¶ËÀ´²éÑ¯±»ÒÅÂ©µÄ·¢ÑÔ¡£
				 WCHAR												wBuf[8192];
}		 IM_HTML_CONTENT;
#endif

#if  0	//  2014/07/11
typedef  struct  __imHtmlContent_t									{									//  2010/12/05
				 unsigned  int										uiType;								//  ´ËÀàÐÍ¿ÉÒÔ¶à¸öÖµ£¬Çø·Öhtml,txtµÈ¸ñÊ½
				 time_t												tStartTime_serv;					//  ×é»á»°²ÎÊý
				 unsigned  int										uiSerialNo;							//  ÔÚ×éÌÖÂÛÖÐ£¬ÓÃÀ´±íÊ¾·¢ÑÔË³Ðò¡£·½±ã×é³ÉÔ±¿Í»§¶ËÀ´²éÑ¯±»ÒÅÂ©µÄ·¢ÑÔ¡£
				 WCHAR												wBuf[16  *  1024];
}		 IM_HTML_CONTENT;
#endif

//  2014/07/11
typedef  struct  __imHtmlContent_t									{									//  
				 unsigned  int										uiType;								//  
				 //
				 unsigned  char										ucbResp;							//  2014/07/11
				 //
				 //  2015/02/16
				 //unsigned  char										ucbNotification;
				 QY_MESSENGER_ID									idInfo_logicalPeer;					//  2015/02/16

				 //  time_t											tStartTime_serv;					//  
				 unsigned  int										uiSerialNo;							//  
				 WCHAR												wBuf[16  *  1024];
}		 IM_HTML_CONTENT;


//  2014/07/11. 查询对方状态。在线后可以响应此请求。如果发送方得到这个请求，就可以在发消息的时候，查看是否得到了html的响应包。如果没有得到，就要重复发送（最多三次)
//  该查询请求也可以（在将来）禁止响应，从而避免被意外查询。
typedef  struct  __queryPeerStatus_t									{
				 unsigned  int										uiType;
				 //
				 unsigned  char										ucbResp;
}		 QUERY_peer_status;


#ifndef  __WINCE__		//  2010/04/18

	#if  0	//  2010/09/10
	#else		//  2012/06/28
		#define		CONST_bufSize_imDataContent							63  *  1024
		#define		CONST_bufSize_imStreamContent						63  *  1024						//  2008/03/22, 
		#define		CONST_bufSize_imLStream								(  900  +  32  )  *  1024		//  2008/03/22, 这个包应该比别的包略大一点，所以+32
		//
		//  #define		CONST_bufSize_transferFileDataResp				32  *  1024
		//  #define		CONST_bufSize_transferFileDataResp				64  *  1024						//  2010/12/05
		//#define		CONST_bufSize_transferFileDataResp				128  *  1024					//  2014/07/13
		#define		CONST_bufSize_transferFileDataResp					900  *  1024					//  
		//
		#define		CONST_bufSize_transferVideoData						900  *  1024					//  2012/06/28. mediaSdk压缩出来的一个包就可能600k.cuda压缩出来的一个包可能700多k
		#define		CONST_bufSize_transferAudioData						512  *  1024					//  2009/05/20

		//  #define		CONST_bufSize_myDrawVideoData					8  *  1024  *  1024				//  2009/05/03
		#define		CONST_bufSize_myDrawVideoData_2k					8  *  1024  *  1024				//  2009/05/03
		#define		CONST_bufSize_myDrawVideoData_4k					36  *  1024  *  1024			//  2014/06/01. 4096X2304, 3840X2160
		#define		CONST_bufSize_myDrawVideoData_5k					M_rgb24SizeImage(5472, 3648)

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



//
typedef  struct  __imLStream_t										{									//  2008/04/01
				 unsigned  int										uiType;
				 unsigned  int										uiContentType;
				 unsigned  long										ulStreamLen;
				 char												buf[CONST_bufSize_imLStream  +  1];
}		 IM_L_STREAM;

//  2010/07/10
typedef  struct  __imLStream_nh_t									{									//  2008/04/01
				 unsigned  int										uiType;
				 unsigned  int										uiContentType;
				 unsigned  long										ulStreamLen;
				 char												buf[1];
				 char										*		p;
}		 IM_L_STREAM_nh;


//  ÕâÊÇÎªÁË±ÜÃâÔÚÇå¿Õ´óÄÚ´æÉÏºÄÊ±¹ý¶à¡£ 2008/03/31
#define		MACRO_memset_imStreamContent(  pStream  )				memset(  (  pStream  ),  0,  offsetof(  IM_STREAM_CONTENT,  buf  )  );
#define		MACRO_memset_imLStream(  pStream  )						memset(  (  pStream  ),  0,  offsetof(  IM_L_STREAM,  buf  )  );



typedef  struct  __imDataContent_t									{									//  2008/01/26
				 unsigned  int										uiType;
				 unsigned  short									usDataType;							//  
				 //  unsigned  short									usLen;
				 unsigned  long										ulLen;
				 char												buf[CONST_bufSize_imDataContent  +  1];
}		 IM_DATA_CONTENT;


//////////////////

#define		CONST_authType_null									0										//  2011/03/22
#define		CONST_authType_logon								1
#define		CONST_authType_dev									2
#define		CONST_authType_qyMcu								3

//
#define		CONST_authType_bjca									101
#define		CONST_authType_jdzy									102



//  2007/03/31, 
typedef  struct  __qyCommAuthInfo_mis_t							{

  				 //unsigned  char								ucCmd;				
				 unsigned  short								usAuthCmd;

				 //
				 int											iAppType;								//  2011/03/27
				 int											iCustemId;
				 unsigned  int									uiChannelType;							//  2007/07/08

				 char											ver[CONST_qyMaxVerLen  +  1];			//  
				 //
				 unsigned  short								usLangId;
				 unsigned  int									uiDevType;
				 //
				 unsigned  short								usAuthType;								//  2011/03/22
				 //
				 QWM_MACS_INFO									macsInfo;
				 char											ip[CONST_qyMaxIpLen  +  1];
				 WCHAR											pcName[128  +  1];
				 WCHAR											domainName[128  +  1];
				 WCHAR											osUsrName[128  +  1];
				 //
#if  0
				 unsigned  short								usAppAvLevel;							//  2011/8/15
#endif

				 //
				 WCHAR											messengerName[255  +  1];				//  messenger
				 char											messengerPasswd[255  +  1];
				 
				 //
				 char											ca_sendData[4096];
				 unsigned  int									ca_sendDataLen;				 
				 
				 //
				 WCHAR											ca_usrName[256];						//  2022/12/05
				 char											ca_tmp_passwd[256];						//  2023/05/16

				 //
				 WCHAR											wRndName_serv[255  +  1];				//  
				 unsigned  int									uiRnd_cli;								//  web 2007/11/22
				 //
				 //  unsigned  int								uiWebSessId;							//  web2007/11/22
				 unsigned  int									uiLogonId;								//  2011/02/02
																										//  

				 
				 // ----------------------------------------
				 unsigned  short								usSessionEncType;

				 //
				 unsigned  int									uiBlobLen_sessionKey;					//  »á»°ÃÜÔ¿
				 char											sessionKeyBlob[CONST_bufSize_sessionKeyBlob];

				 //
				 unsigned  short								usLen_sessionIv;
				 char											sessionIv[CONST_bufSize_sessionIv];

				 //
}		 QY_COMM_AUTHINFO_MIS;


//  ÈÏÖ¤ÏìÓ¦
typedef  struct  __authResp_mis_t								{			
				 QY_MESSENGER_ID								idInfo;
				 //
				 WCHAR											wRndName_serv[255  +  1];				//  webMessenger
				 //  unsigned  int								uiWebSessId;							//  webMessenger
				 //
				 unsigned  int									uiLogonId;								//  
				 //
				 unsigned  int									uiCommEncCtxType;						//  
				 unsigned  int									uiBlobLen_publicKey;
				 char											publicKeyBlob[2048];					//  serverHello

				 //
				 unsigned  char									ucbDaemonDemo;							//  2009/10/11
				 unsigned  short								usMaxVideoConferenceMems;				//  2009/11/05
				 unsigned  char									ucDays_left;							//  2010/03/22
				 //
				 //unsigned  short								usAppAvLevel_daemon;					//  2011/10/22
				 //
				 unsigned  short								usSubSystemId_daemon;					//  2017/06/21

				 //
				 WCHAR											talkerDesc[32];							//  2011/04/07
				 WCHAR											wBuf_hint[255  +  1];

				 //
				 TCHAR											clientWelcomeMsg[128];					//  2016/08/10

				 //
				 WCHAR											ca_usrName[256];						//  2022/12/05
				 char											ca_tmp_passwd[256];						//  2023/05/16
				
				 //
				 char											caGwCfg[64 + 1];						//  ip:port
				 char											caYqServCfg[64 + 1];					//  ip:port

				 //
				 char											caRandom[256];

				 //
}		 AUTH_RESP_MIS;


//
/////////////////////////
//
typedef  struct  __chkLogonIdReq_t								{
			 	 unsigned  int									uiType;

				 //
				 unsigned  char									ucbResp;

				 //
				 unsigned  int									uiLogonId;								//  

				 //
}		 ChkLogonIdReq;



//  ÈÏÖ¤ÐÅÏ¢±í
typedef  struct  __qyMessengerAuthRcd_t							{
				 int											id;
				 //
				 TCHAR											misServName[255  +  1];
				 QY_MESSENGER_ID								idInfo;
				 //
				 unsigned  int									uiType;
				 QWM_MACS_INFO									macsInfo;
				 char											ip[CONST_qyMaxIpLen  +  1];
				 //
				 TCHAR											pcName[255  +  1];
				 TCHAR											domainName[255  +  1];
				 TCHAR											osUsrName[255  +  1];
				 //
				 TCHAR											messengerName[255  +  1];
				 //												messengerPasswd[255  +  1];
				 //
				 int											iRole;	//  2017/08/14
				 //
				 int											iStatus;
				 //																				
				 char											startTime[14  +  1];
				 char											tLastModifiedTime[14  +  1];
}		 QY_MESSENGERAUTH_RCD;


//  ÈÏÖ¤ÁÙÊ±±í
typedef  struct  __qyMessengerAuthTmpRcd_t						{
				 int											id;
				 TCHAR											misServName[255  +  1];
				 char											idStr[20  +  1];
				 unsigned  int									uiType;
				 QWM_MACS_INFO									macsInfo;
				 char											ip[CONST_qyMaxIpLen  +  1];
				 //
				 TCHAR											pcName[255  +  1];
				 TCHAR											domainName[255  +  1];
				 TCHAR											osUsrName[255  +  1];
				 //
				 TCHAR											messengerName[255  +  1];
				 //												messengerPasswd[255  +  1];
				 //
				 char											clientVer[CONST_qyMaxVerLen  +  1];
				 //
				 unsigned  int									uiLangId;
				 int											iPlatformId;
				 //
				 int											iStatus;
				 //																				
				 char											startTime[14  +  1];
				 char											tLastModifiedTime[14  +  1];
}		 QY_MESSENGERAUTHTMP_RCD;


#define		MAX_messengerNameLen								16
#define		MAX_messengerPasswdLen								16
#define		CONTS_passwdSaltLen									4


#define		CONST_passwdType_null								0
#define		CONST_passwdType_md5								1


//  2010/01/05
typedef  struct  __qyImAmRcd_t									{
				 int											id;
				 TCHAR											misServName[255  +  1];
				 QY_MESSENGER_ID								idInfo;
				 //
				 unsigned  short								usAuthType;
				 //
				 TCHAR											messengerName[255  +  1];
				 char											messengerPasswd[255  +  1];
				 int											iPasswdType;
				 char											salt[CONTS_passwdSaltLen  +  1];
				 int											iStatus;
				 char											startTime[14  +  1];
				 char											tLastModifiedTime[14  +  1];
}		 QY_imAm_RCD;
	
////////////////////



#if  0
typedef  struct  __qisDynBmp_t										{
				 QY_MESSENGER_ID									idInfo;							//  2009/09/03
				 unsigned  int										uiObjType;						//  2009/09/03
				 unsigned  short									usIndex_obj;
				 TCHAR												name[32];						//  name used to mean device id or unique name for dynBmp
				 TCHAR												cusName[32];					//  cusName used to mean a friendly comment for dynBmp
}		 QIS_dynBmp_info;
#endif

//  2014/09/04
//
#define	M_resObj_common				unsigned  int					uiObjType;					\
									unsigned  short					usIndex_obj;				\
									unsigned  short					usHelp_subIndex;


//  2016/07/23
typedef  struct  __resObjSimple_t									{
				 M_resObj_common				 
}		 RES_obj_simple;

//
typedef  struct  __qisResObj_t										{
				 //
				 QY_MESSENGER_ID									idInfo;						//  2016/07/24
				 RES_obj_simple											resObj;
				 //
}		 QIS_RES_OBJ, QIS_res_obj;

//
typedef  struct  __qisDynBmpInfo_t									{
				 //
				 QIS_RES_OBJ										qisResObj;						//  2016/07/23
				 //
				 TCHAR												name[32];						//  name used to mean device id or unique name for dynBmp
				 TCHAR												cusName[32];					//  cusName used to mean a friendly comment for dynBmp
				 //
				 unsigned  short									usW,  usH;	
				 //
}		 QIS_dynBmp_info;




//  
//  1 CONST_imCommType_transferFileInfo, 
//  2 CONST_imCommType_transferFileInfoReply¸OK
//  3 CONST_imCommType_transferDateReq¸CONST_imCommType_transferFileDataResp¸
//  4 CONST_imCommType_transferFileDataEndResp¸



//  
typedef  struct  __transferFileReq_t								{												//  2007/06/23
				 unsigned  int										uiType;
				 //
				 DWORD64											ui64FileLen;
				 WCHAR												fileName[256];

				 //
				 unsigned  int										uiSizePerSnd_suggest;							//  2014/07/13

				 //
				 unsigned  int										MAX_FILE_SEND_BLOCK_suggest;					//  发送方限定.

				 //  2015/08/05
				 unsigned  short									usSubtype;
				 QY_MESSENGER_ID									idInfo_logicalPeer;								//  2015/08/05

				 //
				 //  
				 void									*			pInternal;

				 //

				 //
				 WCHAR												fullFilePath[MAX_PATH  +  1];		//  
				 //
				 BOOL												bGrpTask;							//  

				 //
				 //FILE									*			fp;

				 //
				 //DWORD												dwStartTickCnt1;						//  
				 //DWORD												dwLastReportTickCnt;				//  
				 //
				 unsigned  char										ucPercent;							//  

				 //
				 unsigned  short									usErrors;							//  

				 //
				 HWND												hTool_offlineRes;					//  2015/08/06
				 BOOL												bNeedCancel;						//  2015/08/08

}		 TRANSFER_FILE_REQ;


//  »Ø¸´ÎÄ¼þ´«ËÍÐÅÏ¢
typedef  struct  __transferFileReplyReq_t							{									//  2007/07/06
				 unsigned  int										uiType;
				 //
				 __int64											tStartTime_org;						//  
				 unsigned  int										uiTranNo_org;						//
				 unsigned  int										uiSerialNo_org;						//  
				 //  
				 unsigned  short									usOp;
				 //

				 //  ÄÚ²¿´¦Àí
				 void									*			pInternal;

				 //

#if  0
				 //
				 DWORD64											ui64FileLen;
				 //
				 WCHAR												fileName_transferred[256  +  1];	//  
				 WCHAR												fullFilePath_save[MAX_PATH  +  1];	//  
				 unsigned  int										uiSizePerSnd_internal;				//  

				 //
				 //FILE									*			fp;

				 //
				 unsigned  int										uiLastDataBlockIndex;				//  
				 unsigned  short									usErrors;							//  

				 //
				 DWORD												dwStartTickCnt;						//  
				 DWORD												dwLastReportTickCnt;				//  
				 //
				 unsigned  char										ucPercent;							//  
#endif


}			    TRANSFER_FILE_REPLYREQ;	 	



//
#define		CONST_usTaskProcObjType_null							0
#define		CONST_usTaskProcObjType_vStream							1

//
typedef  struct  __taskProcReq_t									{									//  2007/07/06
				 unsigned  int										uiType;
				 //
				 __int64											tStartTime_org;						//  
				 unsigned  int										uiTranNo_org;						//
				 unsigned  int										uiSerialNo_org;						//  
				 //
				 unsigned  int										uiContentType_org;					//  2008/05/29
																										//  
				
				 //
				 QY_MESSENGER_ID									idInfo_imGrp_related;						//  


				 //
				 unsigned  short									usOp;
				 
				 //
				 unsigned  short									usTaskProcObjType;						//  表明下面要操作的对象是什么
				 
				 //  2014/08/26. 也许这里应该引入一个objType，这样，就可以把清晰的指定要对什么做操作了.在要操作的对象多起来的时候，需要objType来区分下
				 struct												{
					 unsigned  int									uiTranNo_openAvDev;

					 #if  0	//  send applyForKeyFrame directly to conf mems, 因此暂时不需要代理查询模式
					 //
					 QY_MESSENGER_ID								idInfo_src;								//  2009/05/31
					 //
					 unsigned  int									uiTranNo_openAvDev_src;					//  2012/01/09
					 #endif
					 
				 }													vStream;
				 
				 //  2009/09/11.  //  2014/08/26. 注意： 下面的几个变量uiTaskType,viewDynBmp，并没有在使用中，
				 unsigned  int									uiTaskType;
				 struct											{
#if  0
						 unsigned  int							uiObjType1;
						 unsigned  short						usIndex_obj;
#endif
						 RES_obj_simple							ros;

				 }												viewDynBmp;							//  2009/09/06
					
				 //  
				 void									*			pInternal;

				 //
				 //  WCHAR											fileName_save[MAX_PATH  +  1];

				 //  2014/10/09
				 HWND												hWnd_task;
				 //
#ifdef  __DEBUG__
				 bool												bTestFlg_a;
				 bool												bTestFlg_v;
#endif

				 //
}			    TRANSFER_FILE_PROCREQ,  TRANSFER_FILE_procReq,  TASK_PROC_REQ;	 	


//
typedef  struct  __taskProcResp_t									{
				 unsigned  int										uiType;
				 //
				 __int64											tStartTime_org;						//  2009/10/19
				 unsigned  int										uiTranNo_org;						//
				 //
				 unsigned  short									usCmd_org;							
				 //  unsigned  int										uiContentType_org;
				 //
				 unsigned  short									usOp_org;
				 //
				 int												iStatus;							//  2009/10/19

				 QY_MESSENGER_ID									idInfo_logicalPeer;					//  2009/10/18

				 //
				 void									*			pInternal;

				 struct												{
					 BOOL											bNeedRemoved_o;
				 }													tmpInternal;

}		 TRANSFER_FILE_PROCRESP,  TRANSFER_FILE_procResp,  TASK_PROC_RESP;




typedef  struct  __transferFileDataReq_t							{									//  2007/07/15
				 unsigned  int										uiType;
				 //
				 __int64											tStartTime_org;						//  ÇëÇó·¢ÆðµÄÊ±¼ä, ÕâÊÇÎªÁËÈ·¶¨ÊÇÄÄ¸öÈÎÎñ±»µÃµ½ÁËÔÊÐí
				 unsigned  int										uiTranNo_org;						//
				 unsigned  int										uiSerialNo_org;						//  Ã»Ê²Ã´ÓÃ
				 //
				 unsigned  short									usOp;
				 //
				 unsigned  int										uiSizePerSnd;						//  Õâ´Î×î¶à·¢ËÍµÄ×Ö½ÚÊý, Ó¦¸ÃºÍReplyReqÖÐµÄÒ»Ñù
				 //
				 unsigned  int										uiDataBlockIndex;					//  µÚ¼¸¿éÊý¾Ý£¬´Ó0¿ªÊ¼

				 //
				 unsigned  short									us_nBlocks;

				 //
				 void									*			pInternal;
				 
				 //
				 struct												{
						__int64										tStartTime_new;
						unsigned  int								uiTranNo_new;

						//
						unsigned  char								ucbFileEnd;
				 
				 }													tmpInternal;
				 
				 //
}				 TRANSFER_FILEDATA_REQ;


typedef  struct  __transferFileDataResp_t							{									//  2007/07/15
				 unsigned  int										uiType;
				 unsigned  int										uiDataBlockIndex;					//  buf pInternal, 
				 unsigned  int										uiLen;
				 char												buf[CONST_bufSize_transferFileDataResp];
				 //
				 
}				 TRANSFER_FILEDATA_RESP;


//
typedef  struct  __transferFileEndReq_t								{									//  2007/07/15
				 unsigned  int										uiType;
				 //
				 __int64											tStartTime_org;						//  
				 unsigned  int										uiTranNo_org;						//
				 unsigned  int										uiSerialNo_org;						//  
				 
				 //  2015/09/07
				 struct												{
					 BOOL											bChkToRemove_i;						//  2015/09/07
					 //
					 BOOL											bNeedRemoved_o;
				 }													tmpInternal;


}				 TRANSFER_FILEEND_REQ;


typedef  struct  __transferFileEndResp_t							{									//  2007/07/15
				 unsigned  int										uiType;
				 unsigned  int										uiVerifyMethod;						//  
				 char												buf[2048];
				 
				 //  2015/09/07
				 struct												{
					 BOOL											bChkToRemove_i;
					 //
					 BOOL											bNeedRemoved_o;
				 }													tmpInternal;

}				 TRANSFER_FILEEND_RESP;


//  RtcÇëÇó,  2007/10/07
typedef  struct  __rtcCallReq_t										{									//  
				 unsigned  int										uiType;
				 //
				 unsigned  int										uiTaskType;							//  
				 //
				 unsigned  long										ulIp_caller;						//  ·¢Æð·½µÄIP
				 //
				 //  ÏÂÃæÎªÄÚ²¿´¦ÀíÓÃµÄ
				 void									*			pInternal;
				 
}		 RTC_CALL_REQ;






//
//  2011/01/26
typedef  struct  __transferVideoDataStat_t							{
					 __int64										tLastTime_showFrameInfo_020534;		//  

					 //
					 __int64										tSelectTime;						//  2008/12/05
					 unsigned  short								usCnt_pkts;							//  tSelectTime. 020534 tLastTime_showFrameInfo->tStartTime
					 unsigned  short								usFps;								//  

					 //
					 int											iVal_dbg;							//  2017/09/04

}		 TRANSFER_videoData_stat;




//
typedef  struct  __transferVideoDataMemHead_t						{
				 //unsigned  short									usIndex_ii;							//  2013/07/18. 将被逐步弃用

				 QY_MESSENGER_ID									idInfo;								//  2009/05/31
				 //
				 unsigned  int										uiTranNo_openAvDev;					//  2012/01/09

				 //
				 unsigned  int										uiSampleTimeInMs;					//  2009/05/02
				 //
				 unsigned  short									usElapseInMs_fromLastPkt;			//  2025/10/22. 当usElapseInMs为0时，就认为是iSampleInMs_start. 就传完整的iSampleTimeInMs;

				 //  2015/01/15
				 unsigned  int										uiPts;								//  2015/01/15

				 //
				 unsigned  char										ucbKeyFrame;


				 //  2016/12/26
				 //unsigned  int									uiEventId_lastRecvd_unused;				//  2013/11/15, 表示从remoteAssist收到了事件的id
				 
				 //
				 unsigned  int										uiLen;								//  ¶ÔÓ¦µÄÊý¾Ý³¤¶È
				 
				 //
				 TRANSFER_videoData_stat							stat;								//  2017/09/05
				 				 
				 //
}		 TRANSFER_VIDEO_dataMemHead;



//  2008/10/30
typedef  struct  __transferVideoData_t								{
				 unsigned  int										uiType;
				 //
				 unsigned  int										uiTranNo_openAvDev;					//  ÓÃÀ´Ê¶±ð·¢ÆðÇëÇóµÄtranNo.
																										//  ÒòÎªvideoÊÇË«Ïò·¢£¬ËùÒÔÔÚ»Ø¸´·½£¬Õâ¸öuiTranNo_orgÊÇÖ¸»Ø¸´µÄÇëÇó
				 //  2017/09/05
				 //TRANSFER_videoData_stat							stat;
				 
				 //
				 //unsigned  int										uiEventId_lastRecvd_ii;				//  2008/11/22, ×îºóÒ»´ÎÊÕµ½µÄÊÂ¼þid.
																										//  该变量不再使用了.放在mems[i]里去了. 2013/11/15

				 //
				 struct												{
					 unsigned  short								usCnt_mems;

					 struct											{									//  for procTaskVideo. 2009/05/12

						 //
						 int										index_pMems_from;
						 int										index_activeMems_from;
					 }												param;

					 //  ´¦Àí½á¹û					 
					 struct											{
				 		 unsigned  short							usRespCode;
						 float										fFps;
						 time_t										tSelectTime;
						 unsigned  short							usCnt_pkts;  
						 unsigned  short							usDiff_pkts;						//  2009/04/18
					 }												result;
					 

				 }													tmpInternal;

				 //
				 unsigned  short									usCnt;
				 TRANSFER_VIDEO_dataMemHead							mems[CONST_maxTransferAvDataMems];

				 //
				 unsigned  int										uiLen;
				 char												buf[CONST_bufSize_transferVideoData];				 

}		 TRANSFER_VIDEO_DATA, TRANSFER_video_data;





//
typedef  struct  __myDrawVideoData_t								{
				 unsigned  int										uiType_unused;
				 
				 //
				 unsigned  int										uiCapType;
				 int												iIndex_capBmp;

				 struct												{
					 //
					 BOOL											bRtsp;									//  2015/03/14

					 //
					 time_t											tStartTran;								//  2011/08/30
					 	
					 //
					 bool											bMosaicResource;

					 //
				 }													input;

				 //  2015/05/07
				 struct												{
					 unsigned  int									uiCnt_vpp0;
					 //
				 }													vpp;

				 //  2016/12/27
				 unsigned  int										uiEventId_lastRecvd_unused;

				 //
				 HWND												hWnd_task;
				 int												iTaskId;
				 unsigned  int										uiTaskType;								//  2014/10/01

				 //
				 QY_MESSENGER_ID									idInfo_peer;												

				 //  2011/12/09
				 struct												{
					 int											index_pMems_from;
					 //  2016/12/27
					 unsigned  int									uiEventId_lastRecvd_unused;					//  2008/11/22
					 
					 //  2014/09/04
					 QIS_RES_OBJ									dynBmp;									//  2014/10/12

					 //
					 unsigned  char									ucbUnresizable;							//  2015/10/23

				 }													decInfo;								//  

				 //  2011/12/08
				 DEBUG_myDRAW_VIDEO_DATA							debugInfo;
				 
				 //  
				 long												lPktId_alloc;							//  2014/03/26.一个不重的序号. 分配内存的标识

				 //
				 long												mosaic_n_waitToPost;
				 int												mosaic_index_thisSecond;

				 //
				 TRANSFER_VIDEO_dataMemHead							head;									//  head.len表示pBuf中的缓冲长度, head.len和bih.biSizeImage不一定相等
				 unsigned  short									usIndex_activeMems_from;				//  2013/07/18.

				 //  2015/09/30
				 unsigned  short									usPktResType;							//  2015/09/30

				 //  2015/09/30
				 struct												{
					 //PKT_sharedTex_info							pktSharedTexInfo;
					 //
					 PKT_sharedTex_info1							pktSharedTexInfo;
				 }													sharedTex;

				 //  2011/12/06
				 unsigned  int										uiSize_dec;								//  pBuf中分为2个区，一个为未压缩数据区，大小为uiSize_dec. uiSize_dec应<=head.len
				 BITMAPINFOHEADER									bih;									//  2011/12/04. 此bih表明了未压缩区中的图像格式, bih.sizeImage应该<=uiSize_dec
				 //
				 unsigned  int										uiOffset_enc;
				 unsigned  int										uiLen_enc;								//  另一个为压缩数据区，大小为head.len - uiSize_dec，包含一个包头uiOffset_enc，紧跟一个压缩数据. 真实大小为uiLen_enc
																											//
																											//  2014/02/24. 当bRtsp为true, p->uiLen_enc  =  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  +  BufferLen;

				 //
				 bool  bResizeToPlay;

				 //  char											*	pBuf;								//  2009/12/07, len is in head
				 QY_MEMORY											memory;									//  2010/04/23

				 //

}		 myDRAW_VIDEO_DATA;


//  2014/03/26
#define		M_set_pktId_alloc(  pPkt  )								(  pPkt  )->lPktId_alloc  =  getuiNextTranNo(  0,  0,  0  );
#define		dyn_M_set_pktId_alloc(  pPkt  )							(  pPkt  )->lPktId_alloc  =  dyn_getuiNextTranNo(  0,  0,  0  );
//  2015/02/13
#define		M_set_pktId_getNewPkt(  pPkt  )							(  pPkt  )->lPktId_getNewPkt  =  getuiNextTranNo(  0,  0,  0  );


//
#define		CONST_pkts_playVideo									20  										//  处理线程中一次性读取的最大包数，要保证下面的具体线程中的取值小于此数. 2011/12/06
//
#define		CONST_pkts_vpp											20
#define		CONST_pkts_encVideo										20
#define		CONST_pkts_toShareVideo_post							20
//
#define		CONST_pMsgs_dispatchVideo								20
//
#define		CONST_pMsgs_preTransformVideo							10
#define		CONST_pkts_preTransformVideo							(  CONST_maxTransferAvDataMems  +  CONST_pkts_playVideo  )
#define		CONST_pkts_out_preTransformVideo						20

#define		CONST_pkts_decVideo										20
#define		CONST_pkts_out_decVideo									20

//
#define		CONST_pMsgs_transformVideo								1
#define		CONST_pkts_transformVideo								(  CONST_maxTransferAvDataMems  +  CONST_pkts_playVideo  )


//  2015/02/13
#define		CONST_pkts_decAudio										20


//
typedef  struct  __transferVideoDataResp_t							{
				 unsigned  int										uiType;
				 //
				 QY_MESSENGER_ID									idInfo;
				 unsigned  int										uiTranNo_openAvDev;					//  tranNo.
																										//  uiTranNo_org
				 //
				 __int64											tSelectTime;						//  2008/12/05
				 unsigned  short									usFps;								//  
				 unsigned  short									usCnt_pkts;
				 unsigned  short									usDiff_pkts;						//  2009/04/18

				 //
}		 TRANSFER_VIDEO_dataResp;

/*
typedef  struct  __transferAudioDataMem_t							{
				 unsigned  short									usIndex;							//  2009/05/18

				 QY_MESSENGER_ID									idInfo;								//  ·¢ÑÔÈË

				 struct												{
					 unsigned  int									uiTranNo_org;						//  Ô­Ê¼°üµÄ
                     DWORD											dwTickCnt_videoConferenceRecved;	//  ÊÓÆµ»áÒé·þÎñÆ÷ÊÕµ½µÄÊ±¼ä¡£ÓÃÀ´µ÷ÊÔºÍÁË½âÒôÆµ´«ÊäÐÔÄÜ¡£
				 }													tmpInternal;						//  ÁÙÊ±Ê¹ÓÃµÄ±äÁ¿£¬²»ÄÜÓÃÔÚÍ¨ÐÅÖÐ

				 unsigned  int										uiSampleTimeInMs;					//  2009/05/02

				 unsigned  int										uiLen;
				 char												buf[CONST_bufSize_transferAudioData];				 
}		 TRANSFER_AUDIO_dataMem;



//  »ìÒôÊý¾Ý£¬ÓÐÒ»¸öuiTranNo_openAvDev´ú±í¡£uiTranNo_openAvDev´ú±íÁËÊÓÆµ»áÒé·¢ÆðÕßµÄÒôÆµ±êÊ¶
//  ±»mixerºó£¬ËùÓÐµÄ·¢ËÍ¶ËµÄÑ¹Ëõ¶¼Òª·ÅÆú£¬²¢±»×ª³ÉÊÓÆµ·þÎñÆ÷µÄÍ³Ò»Ñ¹Ëõ¡£//  ×¢£ºÔÝÊ±»¹Ã»ÓÐ
typedef  struct  __transferAudioData_t								{
				 unsigned  int										uiType;
				 //
				 unsigned  int										uiTranNo_openAvDev;					//  ÓÃÀ´Ê¶±ð·¢ÆðÇëÇóµÄtranNo.
				 //
				 __int64											tLastTime_showFrameInfo_020534;		//  ÉÏÒ»´ÎµÄ·¢²¼Ö¡ËÙÐÅÏ¢µÄÊ±¼ä
				 unsigned  short									usCnt_pkts;							//  ´ÓtLastTime_showFrameInfo->tStartTimeµÄ°üÊý

				 struct												{
					 unsigned  short								usCnt_mems;

					 struct											{									//  for procTaskAudio. 2009/05/12
						 int										index_pMems_from;
						 int										index_activeMems_from;
					 }												param;

					 //  audio´¦Àí½á¹û£¬2008/04/17
					 struct											{
                         unsigned  short							usRespCode;				 
						 unsigned  short							usCnt_pkts;
					 }												result;								//  ÐèÒª·¢ËÍÖ¡ËÙÏìÓ¦Ê±£¬ÏÈ½«½á¹û±£´æÔÚÕâÀï¡£ÔÚtmpHandler_toMixerÀï×é°ü·¢ËÍ

				 }													tmpInternal;						//  ÁÙÊ±Ê¹ÓÃµÄ±äÁ¿¡£²»ÄÜÓÃÔÚÍ¨ÐÅÖÐ

				 unsigned  short									usCnt;
				 TRANSFER_AUDIO_dataMem								mems[CONST_maxTransferAvDataMems];


}		 TRANSFER_AUDIO_DATA;
*/


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

				 //
				 unsigned  short									usElapseInMs_fromLastPkt;

				 //
				 unsigned  int										ui_rtTimeLen;						//  2009/05/27
				 
				 //  2015/09/10
				 unsigned  int										uiPts;								//  2015/09/10
				 
				 //
				 unsigned  int										uiLen;
}		 TRANSFER_AUDIO_dataMemHead;



//  »ìÒôÊý¾Ý£¬ÓÐÒ»¸öuiTranNo_openAvDev´ú±í¡£uiTranNo_openAvDev´ú±íÁËÊÓÆµ»áÒé·¢ÆðÕßµÄÒôÆµ±êÊ¶
//  ±»mixerºó£¬ËùÓÐµÄ·¢ËÍ¶ËµÄÑ¹Ëõ¶¼Òª·ÅÆú£¬²¢±»×ª³ÉÊÓÆµ·þÎñÆ÷µÄÍ³Ò»Ñ¹Ëõ¡£//  ×¢£ºÔÝÊ±»¹Ã»ÓÐ
typedef  struct  __transferAudioData_t								{
				 unsigned  int										uiType;
				 //
				 unsigned  int										uiTranNo_openAvDev;					//  ÓÃÀ´Ê¶±ð·¢ÆðÇëÇóµÄtranNo.
				 //
				 __int64											tLastTime_showFrameInfo_020534;		//  ÉÏÒ»´ÎµÄ·¢²¼Ö¡ËÙÐÅÏ¢µÄÊ±¼ä
				 unsigned  short									usCnt_pkts;							//  ´ÓtLastTime_showFrameInfo->tStartTimeµÄ°üÊý

				 struct												{
					 unsigned  short								usCnt_mems;

					 struct											{									//  for procTaskAudio. 2009/05/12
						 int										index_pMems_from;
						 int										index_activeMems_from;
					 }												param;

					 //  audio´¦Àí½á¹û£¬2008/04/17
					 struct											{
                         unsigned  short							usRespCode;				 
						 unsigned  short							usCnt_pkts;
					 }												result;								//  ÐèÒª·¢ËÍÖ¡ËÙÏìÓ¦Ê±£¬ÏÈ½«½á¹û±£´æÔÚÕâÀï¡£ÔÚtmpHandler_toMixerÀï×é°ü·¢ËÍ

				 }													tmpInternal;						//  ÁÙÊ±Ê¹ÓÃµÄ±äÁ¿¡£²»ÄÜÓÃÔÚÍ¨ÐÅÖÐ

				 unsigned  short									usCnt;
				 TRANSFER_AUDIO_dataMemHead							mems[CONST_maxTransferAvDataMems];

				 unsigned  int										uiLen;									//  2009/05/20
			 	 char												buf[CONST_bufSize_transferAudioData];	//  2009/05/20			 

}		 TRANSFER_AUDIO_DATA;


//
#include	"myPlayAudioData.h"
#include <qnmCommProc_is_open.h>

//
typedef  struct  __transferAudioDataResp_t							{											
				 unsigned  int										uiType;
				 //
				 unsigned  int										uiTranNo_openAvDev;
				 unsigned  short									usCnt_pkts;
				 //
}		 TRANSFER_AUDIO_dataResp;


///////////////

#define		CONST_usRaType_null										0
#define		CONST_usRaType_keyEvent									1
#define		CONST_usRaType_pointerEvent								2


/* KeyEvent - key press or release  */
typedef  struct  __raKeyEvent_t										{
				 unsigned  short									usRaType;		
				 unsigned  char										ucbDown;							/* true if down (press), false if up */
				 unsigned  int										key;			
}		 RA_KEY_EVENT;

/* PointerEvent - mouse/pen move and/or button press. */
typedef  struct  __raPointerEvent_t									{
				 unsigned  short									usRaType;		
				 unsigned  char										ucButtonMask;						/* bits 0-7 are buttons 1-8, 0=up, 1=down */
				 unsigned  short									x;
				 unsigned  short									y;

				 //
				 unsigned  int										uiEventId_unused;			//  2016/12/27				//  ÓÃÀ´ÔÚÊó±êÒÆ¶¯ÖÐµ±·´À¡Á¿ mousemoveÐèÒªµÈÏìÓ¦»ØÀ´ºó»òÕß³¬Ê±1¡£5ÃëºóÔÙ·¢ËÍ¡£ÏìÓ¦Í¨¹ýÆÁÄ»Í¼ÏñÊý¾Ý·¢»ØÀ´°É¡£»¹Òª×öÒ»¸öÅÐ¶Ï£¬¾ÍÊÇÈÎºÎÍ¼Ïñ¶¼²»»ØÀ´Ê±¡£ÕâÊ±¾Í²»ÄÜ·¢ËÍÁË¡£

}		 RA_POINTER_EVENT;


#define		CONST_button1Mask										1
#define		CONST_button2Mask										2
#define		CONST_button3Mask										4
#define		CONST_button4Mask										8
#define		CONST_button5Mask										16
#define		CONST_wheelUpMask										CONST_button4Mask
#define		CONST_wheelDownMask										CONST_button5Mask


//  . 2008/11/15
typedef  struct  __remoteAssistReq_t								{
				 unsigned  int										uiType;
				 //
				 unsigned  int										uiTranNo_openAvDev;							//  tranNo.
				 
				 //
				 QY_MESSENGER_ID									idInfo_imGrp_related;						//  2017/08/23
				 
				 //
				 union												{
					 unsigned  short								usRaType;
					 RA_KEY_EVENT									keyEvent;
					 RA_POINTER_EVENT								pointerEvent;
				 }													u;
				 //
}		 REMOTE_ASSIST_REQ;


////////////////////////



//////////////////

typedef  struct  __aecCfg_t											{
				 BOOL												bUseAec;									//  2013/05/25
				 
				 //
				 BOOL												bFeatrModeOn;								//  2014/08/17
				 BOOL												bNoiseSup;									//  2014/08/17
				 BOOL												bAGC;										//  2014/08/17
				 BOOL												bCntrClip;									//  2014/08/17

				 //
				 unsigned  int										uiEchoLengthInMs;		
				 
}		 AEC_cfg;

//
typedef  struct  __videoConferenceCfg_t								{
				 int												iRows;										//  ·ÖÊÓÆµ×é³ÉÒ»¸ö¾ØÕó¡£ÐÐÊý
				 int												iCols;										//  ÁÐÊý
				 //
				 unsigned  short									usMaxSpeakers;								//  2009/02/19

				 //
				 AEC_cfg											aecCfg;

}		 VIDEO_CONFERENCE_CFG;

typedef  struct  __videoEncParams_t									{											//  2009/03/31
    
				 int												nBitrate;
				 float												fFrameRate;
				 int												nKeyDistInMs;
				 int												nBufferDelay;
				 int												nQuality;
				 int												nVBRQuality;
				 int												nComplexity;
				 int												nPeakBuffer;
				 int												nPeakBitrate;

				 int												nProfile;

				 BOOL												fIsVBR;
				 DWORD												dwTag;
    
				 //
				 BOOL												bWmv;
}		 VIDEO_ENC_PARAMS;



//  2011/07/23
typedef  struct  __videoCompressorCfg_t								{
				 M_VideoCompressorCfgCommonEx						//  VIDEO_COMPRESSOR_cfgCommon							common;
				 
				 //
				 unsigned  char										ucbNeedKeyFrameFirst;
				 				 
				 //
				 TCHAR												compressorName[64];
 
				 //
				 VIDEO_ENC_PARAMS									params;

				 //  unsigned  int									uiCamCapType;								//  2010/07/26

				 //  2014/04/26
				 struct												{
					 unsigned  char									ucbSetDevResolution;

					 //
					 int											iWidth;										//  ·ÖÊÓÆµµÄ¿í¶È
					 int											iHeight;									//  ¸ß¶È
				 }													dev;

				 //  2014/08/15
				 //unsigned  char										ucbXpCantSpeak;

}		 VIDEO_COMPRESSOR_CFG;



typedef  struct  __audio_enc_params_t								{											//  2009/05/17

				 void										*		pAh;

}		 AUDIO_ENC_PARAMS;



//
#define	MACRO_getDelayInMs(  audioPlayCfg  )		(  (  audioPlayCfg  ).usMinTimeInMsOfAudioDataPlaying  +  (  audioPlayCfg  ).usMaxTimeInMsToPlay  +  (  audioPlayCfg  ).usMaxTimeInMsToBeRemoved  )


#if  0  //  2014/05/20
//
typedef  struct  __audioCompressorCfg_t								{
				 unsigned  char										ucCompressors;								//  acm or dmo
				 TCHAR												compressorName[64];							//  2009/05/16

				 WAVEFORMATEX										wf_compress;
				 WAVEFORMATEX										wf_decompress_default;	

				 //
				 //  GUID												dmoClsid;

				 AUDIO_ENC_PARAMS									params;

				 //
				 unsigned  int										uiBytesRecorded_perBlockAlign;				//  ÒôÆµµÄ¶ÔÆëµ¥ÔªµÄ»º³å´óÐ¡

				 //  2014/05/20
				 int												iAvgBitrate;
				 
				 //
				 AUDIO_PLAY_CFG										playCfg;									//  2010/03/11

				 //
				 //  unsigned  int										uiRecordType;								//  2010/08/02

}		 AUDIO_COMPRESSOR_CFG;
#endif

//
typedef  struct  __audioCompressorCfg_t								{
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

}		 AUDIO_COMPRESSOR_CFG;




//
__declspec(  dllexport  )  int  MACRO_getuiBytesRecorded_perBlockAlign(  AUDIO_COMPRESSOR_CFG  &audioCompressor,  WAVEFORMATEX  *  pWf_org  );		


typedef  struct  __avCompressorCfg_t								{											//  2009/05/21
				 #if  10
					unsigned  char									ucSeconds_perFrame_videoConference;			//  
					unsigned  short									usFrames_perSecond_videoConference;			//  
				 #endif

				 AUDIO_COMPRESSOR_CFG								audio;
				 VIDEO_COMPRESSOR_CFG								video;
}		 AV_COMPRESSOR_CFG;


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


#if  0
//
//  2012/02/06
typedef  struct  __dmoInfoVmr_t										{
				 void										*		pDmo;

				 DWORD												cbInputBuffer;
				 DWORD												cbOutputBuffer;
}		 DMO_info_vmr;
#endif



//
__declspec(  dllexport  )  void  *  getDebugStep_sth(  void  *  p0,  int  iType,  MY_DEBUG_STEP  *  pDebugStepTotal  );

//////////////////
//  2014/11/07
typedef  struct  __avTranInfoHead_t									{

				 //  2014/09/23
				 unsigned  short									shClientVer;										//  2014/09/23. 客户端版本号的高位

}		 AV_tranInfo_head;


//
#define		MAX_hg_zcrs									5
typedef  struct {
	struct {
		QY_MESSENGER_ID									idInfo;
	}													mems[MAX_hg_zcrs];
}														HgZcrs;

//
//
typedef  struct {
	//
	unsigned  __int64									ui64MeetingId_hg;			//  2023/04/04
	int													iMeetingType_hg;

	//
	int													iMeetingLevel_hg;
	int													iMeetingDurationInMin;		//  分钟

	//
	unsigned  __int64									ui64_meetingStartTime;
	TCHAR												meetingCompere[64];

	//
	bool												bRecord_conf;				//  录制会议
	bool												bShare_2ndStream;
	
	//
	bool												bRecord_trans;				//  录制发送上来的单路流，2026/04/13

	//
#define		MAX_hg_shareMems							256
	struct {
		QY_MESSENGER_ID									idInfo;
	}													shareMems[MAX_hg_shareMems];

	struct {
		QY_MESSENGER_ID									idInfo;
	}													compereMems[MAX_hg_zcrs];

	//
#if  0
#define		MAX_hg_zcrs									5
	struct {
		QY_MESSENGER_ID									idInfo;
	}													zcrs[MAX_hg_zcrs];
#endif 
	//
	HgZcrs												zcrs;



	//
	bool												bFlow512k;

	
	//  2024/11/0177
	bool												bLive;
	TCHAR												liveUrl[256];



	//
	struct {
		int												cnt_shareMems;
		//
		int												cnt_zcrs;
	}													tmpInternal;



}	CONF_hg_info;



//
typedef  struct  __tranConfCfg_t									{

				 //  2014/09/23
				 unsigned  short									usMaxSpeakers;
				 
				 //				
				 struct												{				 
					 
					 //
					 atbyte											conf_ucAudioCompressors;

					 //
					 unsigned  short								usMaxFps_toShareBmp_conf;							//  2009/04/19					
					 //  2014/04/20. 				
					 int											iWidth_pic_conf;									//  2014/08/15
					 int											iHeight_pic_conf;									//  2014/08/15
					 
					 //					
					 int											conf_iFourcc;
					 //int											conf_bitrateInKbps_dl;
					 int											conf_bitrateInKbps_ul;								//  对参会方，只需要知道上传码流

					 //
					 unsigned  char									conf_ucb100k;
					 
					 //  2017/07/06
					 struct											{
						 //
						 unsigned  char								ucbConfCtrl_starter;

					 }												confCtrl;

				 }													conf;

				 //  2017/08/02
				 unsigned  char										ucbVideoConference;

				 
				 //  2017/08/25
				 unsigned  short									usConfType;

				 //  
				 QY_MESSENGER_ID									idInfo_initiator;
				 
				 //
#if 0
				 unsigned  __int64									ui64MeetingId_hg;
				 int												iMeetingType_hg;
#endif
				 //
				 CONF_hg_info										hgInfo;

				 //
}		 TRAN_conf_cfg;



//  2014/11/07
typedef  struct  __tranVideo_t										{
				 //
                 unsigned  int										uiTranNo_openAvDev;
				 				
				 //				 				 					
				 VIDEO_COMPRESSOR_CFG								compressor;											//  2009/03/29				
				 //
				 QY_VIDEO_HEADER									vh_compress;					
				 VH_stream											vh_stream;											//  2014/02/25
				 //
				 QY_VIDEO_HEADER									vh_decompress;
				 				 
}		TRAN_video;


//  2014/11/07
typedef  struct  __tranAudio_t										{
				 unsigned  int										uiTranNo_openAvDev;
				
				 //				
				 AUDIO_COMPRESSOR_CFG								compressor;											//  2009/05/16
					
				 //				
				 QY_AUDIO_HEADER									ah_compress;										//  2009/05/16	
				 AH_stream											ah_stream;											//  2016/12/23

				 //
				 QY_AUDIO_HEADER									ah_decompress;										//  2009/05/16
				 				 
}		 TRAN_audio;



//  2015/03/12
#define  CONST_avFlg_null											0x0
#define  CONST_avFlg_unresizable									0x1

//
#define  isAvFlg_unresizable(  ucAvFlg  )							(  (  ucAvFlg  )  &  CONST_avFlg_unresizable  )

//  2015/03/11
typedef  struct  __taskVProps_t										{
				 unsigned  char										ucAvFlg;
}		 TASK_v_props;
//
typedef  struct  __taskAvProps_t									{
				 TASK_v_props										v;
}		 TASK_av_props;



//
typedef  struct  __AvTranInfo_t										{
				
				 //  2014/11/07
				 AV_tranInfo_head									head;
				 
				 //
				 TRAN_audio											audio;
				 TRAN_video											video;

				 //  2015/03/12
				 TASK_av_props										taskAvProps;

}		 AV_TRAN_INFO;


//  2014/11/07
typedef  struct  __mosaicTranInfo_t									{

				 //
#if  0
				 unsigned  int										uiObjType;											//  2014/11/07. 在transferAvInfo.video_conf,resource_conf要用objType和usIndex_obj来和原来的流区分
				 unsigned  short									usIndex_obj;										//  2014/11/07	
#endif
				 //
				 RES_obj_simple											resObj;

				 //
				 TRAN_video											video;

}		 MOSAIC_TRAN_INFO;


//
typedef  struct  __avStreamSimple_t									{
				 //
				 RES_obj_simple											resObj;
				 //
				 AV_TRAN_INFO										tranInfo;

}		 AV_stream_simple;


//
typedef  struct  __avStream_t										{
				 QY_MESSENGER_ID									idInfo;
				 //
				 AV_stream_simple									obj;
}		 AV_stream;





///////////////////////////////////////////


typedef  struct  __taskInteractionReq_t								{									//  2009/02/23
				 unsigned  int										uiType;
				 
				 unsigned  char										ucbResp;

				 //
				 unsigned  char										ucStep;

				 //
				 __int64											tStartTime_org;						//  
				 unsigned  int										uiTranNo_org;						//
				 //
				 unsigned  short									usOp;
				 
				 //
				 AV_stream											avStream;

				 //
				 TCHAR												talkerDesc[128];

				 //
				 QY_MESSENGER_ID									idInfo_compere;						//  设置主持人

				 //  2015/07/30
				 //QY_MESSENGER_ID									idInfo_speaker;						//  2015/07/30. 增加非发起方的会议主持人，所以需要把idInfo_speaker发给starter来做处理
				 
				 //
				 QY_MESSENGER_ID									idInfo_imGrp_related;				//  2009/02/23

				 //
				 int												iHkStatus;							//  2023/05/03, 只用来显示，不用来控制

				 //
				 unsigned  char										ucbNvr;								//  2023/11/04

				 //  
				 void									*			pInternal;

				 //

}		TASK_INTERACTION_REQ;	 	



typedef  struct  __videoConferenceMem_t								{
				 
				 //
				 AV_stream											avStream;

				 
				 //  2013/07/18. 需要将第几个话筒的属性传给其他用户
				 unsigned  short									usIndex_speaker;


				 //
				 void									*			pInternal;

				 TCHAR												desc[32];

}		 VIDEO_CONFERENCE_MEM;


//
typedef  struct  __conf_requestingMem_t								{
				 //
				 QY_MESSENGER_ID									idInfo;

				 //
				 TCHAR												desc[32];

				 //
				 void									*			pInternal;

}		 CONF_requesting_mem;


//
typedef  struct  __conf_requestingMems_t							{

				 unsigned  short									usCnt;
				 CONF_requesting_mem								mems[MAX_conf_requestingMems];

				 struct {
					 unsigned  short								usCnt_mems;
				 }													tmpInternal;

}		 CONF_requesting_mems;


//
//
typedef  struct  __ipcParam_t										{
				 //
				 int												iChannel;
				 //
				 TCHAR												channelName[128];

}		 IpcParam;


//
typedef  struct  __enlargeParam_t {
				 unsigned  short								usEnlargeType;					//  放大类型
				 unsigned  __int64								ui64Id;
				 unsigned  int									tn_v;

}		 EnlargeParam;


//
typedef  struct  __oneBigLayoutParam_t {
				 unsigned  char										ucbOneBigLayout;				//  一大7小的布局
				 unsigned  __int64									ui64Id;
}		 OneBigLayoutParam;


//
//
typedef  struct  __confLayoutParam_t								{
				 //
				 OneBigLayoutParam									oneBigLayoutParam;
				 
				 //
				 EnlargeParam										enlargeParam;
				 
				 //
				 IpcParam											ipcParam;

				 //
				 struct 
				 {
					 int ii;
					 unsigned  __int64 							curr_idinfo;

				 }													resp;

				 //
				 struct
				 {
					 int										bAmplification;
				 }												respVideoStatus;

				 //
				 struct
				 {
					 unsigned  short												x;
					 unsigned  short												y;
					 unsigned  short									usEnlargeType;					//  放大类型
				 }													phoneEnlargeParam;

}		 ConfLayoutParam;


//
#define		CONST_enlargeType_null									0
#define		CONST_enlargeType_img									1


//
typedef  struct  __confKey_t										{
				 unsigned  int										uiType;

				 QY_MESSENGER_ID									idInfo_imGrp_related;				//  2009/02/23

				 //
				 struct												{
					 unsigned  short								usCnt_mems;
				 }													tmpInternal;

				 //
				 QY_MESSENGER_ID									idInfo_compere;						//  暂时不用，用HgZcrs

				 //
				 unsigned  short									usLayoutType_starter;				//  2010/12/29

				 //
				 unsigned  short									usCnt;
				 VIDEO_CONFERENCE_MEM								mems[MAX_conf_activeMems];

				 //
				 CONF_requesting_mems								requestingMems;

				 //
				 ConfLayoutParam									confLayoutParam;


				 //
}		 CONF_KEY;		


//
typedef  struct  __status_confLayoutParam_t {
				 unsigned  int										uiType;
				 QY_MESSENGER_ID									idInfo_imGrp_related;

				 //
				 ConfLayoutParam			confLayoutParam;
}		 StatusConfLayoutParam;




//  2010/12/27
typedef  struct  __confLayout_t										{
				 unsigned  int										uiType;

				 unsigned  char										ucbResp;

				 QY_MESSENGER_ID									idInfo_imGrp_related;				//  2009/02/23

				 unsigned  short									usLayoutType;

				 //
				 unsigned  short									usOp;

				 //
				 ConfLayoutParam									confLayoutParam;

				 //
}		 CONF_LAYOUT;


//
typedef  struct  __confNvrInfo_t									{
				 unsigned  int										uiType;

				 //
				 unsigned  char										ucbResp;

				 //
				 QY_MESSENGER_ID									idInfo_imGrp_related;

				 //
				 NvrInfo											nvrInfo;

				 //
				 QY_MESSENGER_ID									idInfo_requester;

				 //
				 struct {
					 //
					 int											usCnt_mems;
					 //
				 }													tmpInternal;

}		 ConfNvrInfo;



//
typedef  struct  __talkerPolicy_t {


				 //  2017/06/25
				 //
				 unsigned  char										ucbConfCtrl_starter;

				 //
				 atbyte												conf_ucAudioCompressors;				//  

				 //
				 unsigned  short									conf_usFps;											//  指定会议帧速. 发给mcu.
				 //
				 unsigned  char										conf_ucb100k;										//  是否使用100k模式。不是只有100k.是指必须严格限制流量，支持最小的带宽模式。要发给所有的客户端

				 //
				 int												conf_iFourcc;



				 //
				 int												conf_bitrateInKbps_dl;
				 int												conf_bitrateInKbps_ul;



				 //
				 //unsigned  char									ucb2Streams;

				 //
				 unsigned  int										uiTaskType;
				 int												shareDevice_grp_index;		//  取1,2,3,4. 不能用0
				 //
				 unsigned  short									gpu_usIndex;				//  是gpu的index. 

				 //
				 unsigned  short									usConfType;					//  会议类型

				 //
}		 TALKER_policy;


//
//
typedef  struct  __param_startAvCall_t {
	unsigned  char			ucbNoLocalAv;
	//
	QY_MESSENGER_ID		idInfo_initiator;
	//
	unsigned  short		conf_usMaxSpeakers;

	//int					conf_iFourcc;
	TALKER_policy			talkerPolicy;

	//
	unsigned  char			ucb2Streams;

	//
	bool					bNoPrompt;


	//
}		 PARAM_startAvCall;





//
typedef  struct  __confReq_policy_t									{

				 //
				 unsigned  short									usAvLevel;

				 //
				 unsigned  short									usMaxSpeakers;

				 //
				 //int												conf_iFourcc;

				 //
				 TALKER_policy										talkerPolicy;

				 //
}		 CONF_req_policy;




//
typedef  struct  __confReq_t										{
				 unsigned  int										uiType;
				 
				 //
				 unsigned  char										ucbResp;		//  2025/01/22
				 
				 //
				 QY_MESSENGER_ID									idInfo_imGrp_related;

				 //
				 unsigned  short									usOp;

				 //
				 CONF_req_policy									policy;

				 //
				 QY_MESSENGER_ID									idInfo_initiator;

				 //
				 unsigned  char										ucHardwareAccl;			//  2021/

				 //
				 CONF_hg_info										hgInfo;

				 //
				 QY_MESSENGER_ID									idInfo_requester;				//  if qmd will redirect application from cli to mcu, idInfo_requester must be set. 

				 //
				 //bool												bLive;					//  2024/11/01
				 //TCHAR												liveUrl[256];


				 //
}		 CONF_req;



//
typedef  struct  __mcuCmd_t											{
				 unsigned  int										uiType;

				 //
				 QY_MESSENGER_ID									idInfo_mcu;

				 //
				 QMC_debugStatusInfo								debugStatusInfo;

				 //
				 struct												{
					 bool											bSend_debugStatusInfo;
					 //
				 }													tmpInternal;

}		 MCU_cmd;



/////////////////////////////////


//
typedef  struct  __taskAvFrom_t										{

				 //
				 QY_MESSENGER_ID									idInfo;										//  
				 time_t												tStartTime_task;							//  
				 //
				 unsigned  char										ucbVideoConferenceStarter;					//  2009/04/02
				 
				 //  2014/09/23
				 short												shClientVer;
				 
				 //
				 struct												{

					 //
					 TRAN_video										tv_recvd;									//  2014/11/10
					 
					 //  2014/11/10
					 BOOL											bGot_vh_stream;
					 
					 //
					 unsigned  short								usFrames_perSecond_expected;				//  TRANSFER_VIDEO_DATA
					 //
					 time_t											tLastTime_showFrameInfo_020534;
					 unsigned  short								usCnt_pkts;
					 time_t											tSelectTime;
					 DWORD											dwTickCnt_selectTime;

				 }													video;

				 struct												{

					 //  2014/11/10
					 TRAN_audio										ta_recvd;									//  2014/11/10

					 //
					 time_t											tLastTime_showFrameInfo_020534;
					 unsigned  short								usCnt_pkts;

				 }													audio;

				 //
				 //  2015/05/19. 2014/09/04
				 struct												{
						 unsigned  char								ucbSaveVideo_reply;
				 }													viewDynBmp_reply;

				 //  2015/10/23
				 TASK_av_props										taskAvProps;

				 //
				 int												iDiffInMs_tStartAudios[MAX_speakers_taskAv];						//  2009/05/27
				 int												iSampleTimeInMs_audios[MAX_speakers_taskAv];						//  2010/06/19

}		 TASK_AV_FROM;


#if  0
typedef  struct  __activeTaskAvFrom_t								{											//  2009/02/19

				 QY_MESSENGER_ID									idInfo;										//  ·¢ËÍÕß£¨ÔÚ×é²¥Àï£¬Õâ¸öºÜÖØÒª£©

				 unsigned  short									usIndex_pMems_from;

}		 ACTIVE_taskAvFrom;
#endif








#define		CONST_threadStep_null		  		0
#define		CONST_threadStep_start		  		1
#define		CONST_threadStep_toWait		  		3
#define		CONST_threadStep_toGetMsg			5
#define		CONST_threadStep_msgGot				9
//
#define		CONST_nStep_enter					30				//
#define		CONST_nStep_leave					39
//
//  user defined step 100->1000
//
#define		CONST_threadStep_msgProced			1001
#define		CONST_threadStep_toExit				1011
#define		CONST_threadStep_end				1019

#if  1
	#define		M_setStep(  pDebugStep,  nStep  )				{  if  (  pDebugStep  )  {  (  pDebugStep  )->nStep_debug  =  (  nStep  );  (  pDebugStep  )->dwTickCnt_step_debug  =  GetTickCount(  );  }  }
	#define		M_setStep_fg(  pDebugStep,  nStep  )			{  if  (  pDebugStep  )  {  (  pDebugStep  )->fg.FillBuffer.nStep_debug  =  (  nStep  );  (  pDebugStep  )->fg.FillBuffer.dwTickCnt_step_debug  =  GetTickCount(  );  }  }

#else
	#define		M_setStep(  pDebugStep,  nStep  )		
	#define		M_setStep_fg(  pDebugStep,  nStep  )
#endif

#define		M_setMyStep(  pDebugStep,  nMyStep  )				{	MACRO_qyAssert(  nMyStep  <  800,  _T(  "nMyStep err. must < 800"  )  );  M_setStep(  pDebugStep,  100  +  nMyStep  );  }


//  以下要被废弃.2012/03/21
#define		MACRO_setStep(  debugStep,  nStep  )				M_setStep(  &debugStep,  nStep  )
#define		MACRO_setMyStep(  debugStep,  nMyStep  )			M_setMyStep(  &debugStep,  nMyStep  )


//
typedef  struct  __qyQThreadProcInfo_common_t					{
				 MACRO_qyQThreadProcInfo_common
}		 QY_qThreadProcInfo_common;


//  2010/04/28
#define  CONST_bufSize_tmpPktEncA		16000

	//
typedef  struct 
{
	TRANSFER_AUDIO_dataMemHead memHead_a;
	int bufSize;
	char buf[CONST_bufSize_tmpPktEncA];	//  128000/8
	int len;
}Tmp_pkt_encA;


//
typedef  struct  __pktInfo_toDec_t								{
				 void								*			pMIS_MSGU;

				 //
				 Tmp_pkt_encA									pkt_encA;

				 //
				 void								*			pPkt_dec_myPLAY_AUDIO_DATA;						//  用来做解码缓存
				 //
				 BOOL											bGot_msg;										//  2015/02/14. 表明pMIS_MSGU是否有效数据
				 //
				 long											lPktId_getNewPkt;
				 //
				 struct											{
					 BOOL										bGot_pkt;
					 //
					 int										index_mems;
					 int										iPos;	
				 }												info;
}		 PKT_info_toDec;



//
#define		CONST_toolCliPipePrefix		_T(  "\\\\.\\pipe\\toolCliPipe"  )


//
typedef  struct  __qyShm_t											{
				 TCHAR												shmName[128];
				 //					
				 unsigned  int										uiBufSize_pBuf;						 
				 //
				 HANDLE												hMap;					
				 char	*  											pBuf;									 
}		 QY_shm;

//
typedef  struct  __vtShmPktInfo_t									{
				 //  2015/10/04
				 unsigned  short									usPktResType;
				 //
				 //PKT_sharedTex_info									pktSharedTexInfo;
				 //
				 PKT_sharedTex_info1									pktSharedTexInfo;
				 //
				 BOOL												bDataReady;
}		 VT_shm_pktInfo;


//  2015/10/15
#define		CONST_shmType_null										0
#define		CONST_shmType_dvt										1
#define		CONST_shmType_evt										2


//
typedef  struct  {
				struct													{
					 unsigned  char										ucbShowDec_pipeStatus;
					 //
					 unsigned  char										ucbShowPreDecVStatus;										//  2014/06/23
					 unsigned  char										ucbShowPostDecVStatus;										//  2014/06/23
					 //
					 unsigned  char										ucbShowDec_sharedTexStatus;									//  2016/04/08
					 //
				}														i;
				struct													{
				}														o;
}		 VT_shm_dvtInfo;

//
typedef  struct  {
				struct													{
					VIDEO_COMPRESSOR_cfgCommon							compressorCfgCommon;
					//
					BOOL												bNeed_forceKeyFrame;
					//
					unsigned  char										ucbShowEncVStatus;		//  2015/10/20
				}														i;
				struct													{
					VH_stream											vh_stream;
					BOOL												bDone_vh_stream;
				}														o;
}		 VT_shm_evtInfo;


//
#define			MAX_shmPktBufs											60	//  30	//  15	//  2016/04/08	//  10	
//
#define			MAX_shmPktBufs_dvt										3	//  2
#define			MAX_shmPktBufs_evt										5	//  2

//  2015/01/30
typedef  struct  __vtShmContent_t										{
				 unsigned  int											uiType;
				 unsigned  int											uiBufSize_content;				 
				 //
				 struct													{
					 //
					 TCHAR												name[32];						//  2016/04/12

				 }														cfg;
				 //
				 union													{
					 VT_shm_dvtInfo										dvt;
					 VT_shm_evtInfo										evt;
				 }														u;
				 //
				 BITMAPINFOHEADER										bih_dec;
				 //
				 unsigned  char											ucCnt_shmPktBufs;
				 //
				 VT_shm_pktInfo											mems[MAX_shmPktBufs];
				 
				 //
				 //
				 struct													{
					 struct												{
						 //
						 DWORD											lastRead_sampleTimeInMs;		//  2014/11/26

						 //
						 unsigned  int									uiCnt_readShm;
					 
					 }													readShm;
				 
					 //
					 struct												{
						 unsigned  int									uiCnt_writeShm;
					 }													writeShm;
					 
					 //					
					 unsigned  int										uiSeqNo_lastRender;				//  2015/10/06
					 unsigned  int										uiXql_player;					//  2016/04/14

				 }														status;

				 //
				 char													buf[1];				 
}		 VT_shm_content;


//  2015/10/16
#define		CONST_vtType_null										0
#define		CONST_vtType_decV										1
#define		CONST_vtType_encV										2


//  2015/10/16
typedef  struct  __vt_process_t										{
				 //  2015/02/01
				 HANDLE												hProcess_vt;

}		 VT_process;

//
int  createVt(  void  *  pMC_VAR_common,  int  iVtType,  unsigned  int  tn_cliPipe,  unsigned  short  usPktResType1,  VT_process  *  pVtProcess,  LPCTSTR  hint  );
int  closeVt(  void  *  pMC_VAR_common,  unsigned  int  tn_cliPipe,  VT_process  *  pVtProcess  );
int  askVtToQuit(  void  *  pMC_VAR_common,  unsigned  int  tn_cliPipe,  VT_process  *  pVtProcess  );
int  restartVt(  void  *  pMC_VAR_common,  int  vtType,  int  tn_cliPipe,  unsigned  short  usPktResType,  VT_process  *  pVtProcess  );


//  2015/01/30
typedef  struct  __dvtCli_t										{
					 
				 unsigned  int									tn_cliPipe;		

				 //				
				 void									*		pRtspCli;
				 
				 //  2015/02/01
				 VT_process										vtProcess;
				 
				 //  2015/01/30				
				 QY_shm											dataShm;
				 					 
				 //				
				 struct											{
						 HANDLE									hThread;
						 DWORD									dwThreadId;
					

						 //				
						 TCHAR									evtName_syncR[32];				
						 HANDLE									hEvent_syncR;

						 //  2015/02/19
						 TCHAR									evtName_syncW[32];				
						 HANDLE									hEvent_syncW;
						 

				 }												readShm;
				
				 struct											{
					 BOOL										bShmOpen_dvt;

					 //  2016/03/29
					 DWORD										dwLastTickCnt_decDataGot;
					 //
					 struct										{
						 int									nTimes_noDecData;
						 DWORD									dwStartTickCnt_noDecData;		//  2016/04/18
					 }											noDecData;


				 }												status;

				 //

				 //
				 BOOL											bQuit;

}		 DVT_cli;



//  2015/02/25
//
typedef  struct  __pretransProcInfo_t							{
				 MACRO_qyQThreadProcInfo_common

				 //
				 struct											{
					 struct										{

						 DWORD									dwTickCnt_start;			//  2015/01/15
						 unsigned  int							uiPts_first;
						 //
						 //
						 unsigned  int							uiPts_lastRecvd;			//  2015/01/15

					 }											pts;

				 }												helpInfo;

}		 PRETRANS_procInfo;






//
//
//  2015/06/18
typedef  struct  __trans_ptsInfo_t									{
				 //
				 struct												{
					 
					 //
					 DWORD											dwTickCnt_calc_start;						//  每隔几秒计算一次。每次都重新清零。

					 //
					 unsigned  int									uiCnt_ptsErr;								//  pts不匹配的次数
					 unsigned  int									uiCnt_notRecvd_pts;							//  多少pts丢了

				 }													v;
}		 TRANS_pts_info;




#if  10
	#define		MACRO_getTransform(  task,  index_activeMems_from  )	(  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  (  task  ).usCntLimit_transforms  )  ?  NULL  :  &(  task  ).pTransforms[index_activeMems_from]  )
#else	//  for test
	#define		MACRO_getTransform(  task,  index_activeMems_from  )	(  (  task.usCntLimit_transforms  ==  0  )  ?  NULL  :  &task.pTransforms[0]  )
#endif

//  2011/12/08
#define		MACRO_getDispatch(  task,  index_activeMems_from  )	(  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  (  task  ).usCntLimit_dispatchs  )  ?  NULL  :  &(  task  ).pDispatchs[index_activeMems_from]  )


//  2009/06/17
typedef  struct  __qisDispatchProcInfo_t							{
				 MACRO_qyQThreadProcInfo_common
}		 QIS_DISPATCH_procInfo;

typedef  struct  __qisDispatch_t									{
				 void									*			pProcInfo;				 
				 MSGR_ADDR								*			pAddr_logicalPeer;
				 int												iTaskId;
				 void									*			pTranInfo;										//  AV_TRAN_INFO  *
				 void									*			pTask;											//  PROC_TASK_AV  *
				 
				 //  2011/12/08
				 int												index_activeMems_from;

				 //
				 QIS_DISPATCH_procInfo								audio;
				 QIS_DISPATCH_procInfo								video;

				 //
				 SAVE_av_pktU										tmpBuf_saveAPkt;

				 //
}		 QIS_DISPATCH;




//  2016/04/18


//  2014/11/20. //  2014/11/20. 在某些情况下，比如mosaic. 客户端需要将请求发往会议发起方。发起方再代理发往所有客户端
typedef  struct  __proxiedTranInfo_t								{
				 QY_MESSENGER_ID									idInfo;
				 unsigned  int										uiObjType;
				 AV_TRAN_INFO										ti;
}		 PROXIED_TRAN_INFO;


//
//  2016/04/18
#define		CONST_transferAvInfo_subtype_null						0
#define		CONST_transferAvInfo_subtype_task						2
//
#define		CONST_transferAvReplyInfo_subtype_task					3




//  2008/03/15.
typedef  struct  __transferAvInfo_t									{
				 unsigned  int										uiType;
				 //
				 unsigned  char										ucbResp;
				 
				 //
				 unsigned  int										uiTaskType;							//  

				 //
				 int												shareDevice_grp_index;				//  查看设备分组
				 
				 //
				 TRAN_conf_cfg										confCfg;

				 //
				 //AV_TRAN_INFO										tranInfo;
				 AV_stream_simple									ass;
				 
				 //  2014/11/07
				 MOSAIC_TRAN_INFO									confMosaicTranInfo_video,  confMosaicTranInfo_resource;

				 //
				 struct												{
					 //  2016/07/24
					 //RES_obj_simple									resObj;
					 //
					 unsigned  char									ucbSaveVideo;						//  2014/08/04
				 }													viewDynBmp;							//  2009/09/06

				 //
				 QY_MESSENGER_ID									idInfo_logicalPeer;					//  2009/10/18

				 //
				 unsigned  int										uiTranNo_avTask_starter;			//  2014/11/22. 这个tranNo用来在会议和共享资料等任务里建立关联。
				 				 
				 //  2014/11/20
				 PROXIED_TRAN_INFO									proxiedTranInfo;


				 //
				 void									*			pInternal;

				 //
				 BOOL												bGrpTask;							
				 
				 //  2016/04/18
				 unsigned  short									tmp_usSubtype;

				 //  2014/11/09
				 struct												{

					 struct											{
						QY_MESSENGER_ID								idInfo;
						unsigned  int								uiObjType;
						unsigned  int								usIndex_obj;
					 }												streamInfo;
					 //
					 unsigned  short								usCnt_consult_mems;  
					 //
					 AV_stream										tmpAs;

				 }													tmp_internal;
				 //

}		 TRANSFER_AV_INFO;


//  
typedef  struct  __transferAvReplyInfo_t							{									//  2007/07/06
				 unsigned  int										uiType;
				 //
				 __int64											tStartTime_org;						//  
																										//  tStartTime_org tranNo
				 unsigned  int										uiTranNo_org;						//
				 //  
				 unsigned  short									usOp;
				 //
				 AV_TRAN_INFO										tranInfo;
				 
				 //  2014/09/04
				 struct												{
					 unsigned  char									ucbSaveVideo;
				 }													viewDynBmpReply;

				 //  
				 void									*			pInternal;

				 //
				 //  2016/04/18
				 unsigned  short									tmp_usSubtype;

				 struct												{
					 AV_stream										tmpAs;
				 }													tmp_internal;

				 //
				 //  PROC_TASK_AV										myTask;
				 
}			    TRANSFER_AV_replyInfo;	 	



///////////////////////////




///////////////////////////
//  2017/09/16
//  2017/09/16
typedef  struct  __confMemState_t									{
				 QY_MESSENGER_ID									idInfo;
				 unsigned  short									usState;
}		 CONF_mem_state;

//
//  当把全部的confMemState发送给confMgr时，用uiTranNo_retrieveAll来表示当前的状态
//  每次有部分变化，就发送部分给confMgr, 用usSeqNo_retrievePart来表示每次的变化。usSeqNo_retrievePart每次增一. 从0开始，在发送全部时，此值为0。
//  发送的个数可能大于50，所以用usSeqNo来表示部分。最后一个包要设置ucbEnd.
//  
#define		MAX_confMemStates										50
//
typedef  struct  __confState_t										{
				 unsigned  int										uiType;
				 //
				 QY_MESSENGER_ID									idInfo_imGrp_related;			//  2014/09/25	
				 //
				 unsigned  int										uiTranNo_retrieveAll;			//  发送所有成员状态的标识
				 unsigned  short									usSeqNo_retrievePart;			//  发送部分包的序号， 从0开始，逐步增1. 为0时，表示发送所有

				 //
				 struct												{
					 unsigned  char									ucbRetrieveAll;					//  如果接收端没有接收到正确的发送序号，就要发送请求到发送方，要求发送发送全部。发送方会用新的uiTranNo_retrieveAll
				 }													sendByReceiver;
				 
				 //
				 unsigned  short									usSeqNo;						//  2017/09/17. 发送大包会分包发送，用usSeqNo来表示包的顺序。ucbEnd表示发送完毕 
				 unsigned  char										ucbEnd;
				 //
				 unsigned  short									usCnt;
				 CONF_mem_state										mems[MAX_confMemStates];

				 //
				 struct												{
					 unsigned  short								usCnt_mems;
				 }													tmpInternal;
				 
				 
}		 CONF_state;



//
typedef  struct {
				unsigned  int										uiType;
				//
				QY_MESSENGER_ID										idInfo_imGrp_related;			//  2014/09/25	
				//
				QY_MESSENGER_ID										idInfo_compere;


				//
}		 CONF_ctrl_state;




////////////////////////////////////////////////
//  2012/04/19  {

typedef  struct  __procTaskGps_t									{
				 HWND												hWnd_task;

				 //
				 int												iIndex_sharedObj;

				 //
				 int												iIndex_player_gps;								//  2012/05/07

				 DWORD												dwTickCnt_lastApplyForPlayer;

				 //
				 BOOL												bTaskInvalid;

}		 PROC_TASK_GPS;


typedef  struct  __transferGpsInfo_t								{
				 unsigned  int										uiType;
				 //
				 unsigned  char										ucbResp;
				 //
				 unsigned  int										uiTaskType;							//  
				 //

				 //  QY_MESSENGER_ID									idInfo_logicalPeer;					//  2009/10/18

				 //
				 void									*			pInternal;

				 PROC_TASK_GPS										myTask;


}		 TRANSFER_GPS_INFO;


//  
typedef  struct  __transferGpsReplyInfo_t							{									//  2007/07/06
				 unsigned  int										uiType;
				 //
				 __int64											tStartTime_org;						//  
																										//  tStartTime_org tranNo
				 unsigned  int										uiTranNo_org;						//
				 //  
				 unsigned  short									usOp;
				 //

				 //  ÄÚ²¿´¦Àí
				 void									*			pInternal;

				 PROC_TASK_GPS										myTask;

				 
}			    TRANSFER_GPS_replyInfo;	 	


//
typedef  struct  __transferGpsDataMem_t								{
				 int												iLaInM10000f;
				 int												iLoInM10000f;
				 //  int												iAt
				 
}		 TRANSFER_GPS_dataMem;

#define	MAX_transferGpsDataMems										8
typedef  struct  __transferGpsData_t								{
				 unsigned  int										uiType;

				 //
				 __int64											tLastTime_showFrameInfo_020534;		//  2012/04/26

				 //
				 struct												{
					 unsigned  short								usCnt_mems;
				 }													tmpInternal;						//  

				 //
				 unsigned  short									usCnt;
				 TRANSFER_GPS_dataMem								mems[MAX_transferGpsDataMems];


}		 TRANSFER_GPS_DATA;


typedef  struct  __transferGpsDataResp_t							{
				 unsigned  int										uiType;
				 //
			#if  0
				 unsigned  int										uiTranNo_openAvDev;					//  tranNo.
																										//  uiTranNo_org
				 //
				 unsigned  short									usFrames_perSecond;					//  
				 __int64											tSelectTime;						//  2008/12/05
				 unsigned  short									usCnt_pkts;
				 unsigned  short									usDiff_pkts;						//  2009/04/18
			#endif
				 //
}		 TRANSFER_GPS_dataResp;


////////////////////////  }




/////////////////////////////////////////////////


//  ¸
//  
//  1 ucbRetrieveImGrpList 
//  2 RETRIEVE_IMGRPLIST_RESP
//  3.ucbRetrieveImGrpList FALSE
//  4 RETRIEVE_CONTACTLIST_RESP
//	5 ucbRetrieveImGrpList FALSE
//  6 RETRIEVE_CONTACTLIST_RESP
//
typedef  struct  __retrieveImObjListReq_t							{
				 unsigned  int										uiType;
				 unsigned  short									usMaxContactUpdateInfosPerSnd;				//  Ò»´Î¿ÉÒÔÏÂÔØ×î¶à¶àÉÙ¸öÁªÏµÈË¸üÐÂÐÅÏ¢
				 __int64											tLastRefreshedTime_contactList_misServ;		//  ÉÏ´ÎµÄË¢ÐÂÊ±¼ä£¬Îª0Ê±£¬±íÃ÷È«ÃæË¢ÐÂ
				 //
				 unsigned  char										ucbNext;									//  ÊÇ·ñ¼ÌÐøÇëÇó
				 QY_MESSENGER_ID									idInfo_grp_lastRefreshed;					//  ÉÏ´ÎË¢ÐÂµÄ×éID£¬½öÓÃÔÚË¢ÐÂ³ÉÔ±¹ØÏµ¡£
				 QY_MESSENGER_ID									idInfo_lastRefreshed;						//  ÉÏ´ÎµÄË¢ÐÂ½Úµã
}		 RETRIEVE_IMOBJLIST_REQ;	



//  
//
#define		CONST_maxContactUpdateInfos_025909						10											// 
//
#define		CONST_maxContactUpdateInfos_grp							128											//  2014/02/06
#define		CONST_maxContactUpdateInfos_grpMem						2048										//  2014/02/06
#define		CONST_maxContactUpdateInfos_contact						128  *  3									//  2014/02/09

//

typedef  struct  __retrieveImGrpListResp_t							{
				 unsigned  int										uiType;
				 //
				 QY_MESSENGER_ID									idInfo_lastRefreshed;						//  ¶¼ÓÐ
				 //
				 unsigned  char										ucbEnd;										//  ÊÇ·ñÏìÓ¦Êý¾ÝÒÑ¾­½áÊø¡£

				 unsigned  short									usCnt;										//  ·Ç½áÊø°ü
				 IM_GRP_INFO										mems[CONST_maxContactUpdateInfos_grp];			//  ·Ç½áÊø°ü	

				 void									*			pInternal;									//  ÒÔÏÂÎªÄÚ²¿±äÁ¿£¬·ÇÕýÊ½Ê¹ÓÃ
				 int												index;

}		 RETRIEVE_IMGRPLIST_RESP;


typedef  struct  __retrieveImGrpMemListResp_t						{
				 unsigned  int										uiType;
				 //
				 QY_MESSENGER_ID									idInfo_grp_lastRefreshed;					//  ÒªË¢ÐÂµÄ×éID, Îª0Ê±±íË¢ÐÂËùÊô×éÐÅÏ¢¡£»òÕß£¬ÔÚ¹ÜÀí¶ËÃ»Æô¶¯×éÄ£Ê½Ê±£¬ÔòÏÂÔØËùÓÐ³ÉÔ±
				 QY_MESSENGER_ID									idInfo_lastRefreshed;						//  ¶¼ÓÐ
				 //
				 unsigned  char										ucbEnd;										//  ÊÇ·ñÏìÓ¦Êý¾ÝÒÑ¾­½áÊø¡£

				 unsigned  short									usCnt;										//  ·Ç½áÊø°ü
				 IM_GRP_MEM											mems[CONST_maxContactUpdateInfos_grpMem];			//  ·Ç½áÊø°ü	

				 void									*			pInternal;									//  ÒÔÏÂÎªÄÚ²¿±äÁ¿£¬·ÇÕýÊ½Ê¹ÓÃ
				 int												index;

}		 RETRIEVE_IMGRPMEMLIST_RESP;


//  2017/08/14
typedef  struct  __retrieveContactMem_t								{
				 QY_MESSENGER_REGINFO								regInfo;
				 int												iRole;
}		 RETRIEVE_contact_mem;


//
typedef  struct  __retrieveContactListResp_t						{
				 unsigned  int										uiType;
				 //
				 QY_MESSENGER_ID									idInfo_lastRefreshed;						//  ¶¼ÓÐ
				 //
				 unsigned  char										ucbEnd;										//  ÊÇ·ñÏìÓ¦Êý¾ÝÒÑ¾­½áÊø¡£

				 unsigned  short									usCnt;										//  ·Ç½áÊø°ü
				 RETRIEVE_contact_mem								mems[CONST_maxContactUpdateInfos_contact];			//  ·Ç½áÊø°ü	

				 //
				 void									*			pInternal;			//  ÒÔÏÂÎªÄÚ²¿±äÁ¿£¬·ÇÕýÊ½Ê¹ÓÃ
				 int												index;
				 int												iFiledIndex;

}		 RETRIEVE_CONTACTLIST_RESP;


typedef  struct  __retrieveImObjListEndResp_t						{											//  ½áÊø°ü
				 unsigned  int										uiType;
				 //
				 __int64											tLastRefreshedTime_contactList_misServ;		//  ·¢ËÍ¸ø¿Í»§¶ËÈÃÖªµÀÊÇ´ÓÊ²Ã´Ê±¼ä¿ªÊ¼Ë¢ÐÂµÄ
				 //
}		 RETRIEVE_IMOBJLISTEND_RESP;


//  2007/11/27
typedef  struct  __webContactInfo_t									{
				 WCHAR												misServName[CONST_maxMisServNameLen  +  1];
				 QY_MESSENGER_ID									idInfo;
				 //
				 WCHAR												grpDisplayName[255  +  1];
				 WCHAR												displayName[255  +  1];
				 //
}		 WEB_CONTACT_INFO;

typedef  struct  __retrieveWebContactListResp_t						{
				 unsigned  int										uiType;
				 //
				 WCHAR												wAdvertisement[510  +  1];	//  2008/03/02
				 //
				 unsigned  short									usCnt;
				 WEB_CONTACT_INFO									mems[32];

				 void									*			pInternal;					//  ÒÔÏÂÎªÄÚ²¿±äÁ¿£¬·ÇÕýÊ½Ê¹ÓÃ
				 int												index;
}		 RETRIEVE_WEBCONTACTLIST_RESP;


//  2007/12/22, ÓÃÀ´Ïò·þÎñÆ÷²éÑ¯webContactµÄ×´Ì¬¡£
typedef  struct  __webContactStatus_t								{
				 WCHAR												misServName[CONST_maxMisServNameLen  +  1];
				 //  unsigned  int										uiWebSessId;
				 unsigned  int										uiLogonId;
				 QY_MESSENGER_ID									idInfo;
				 //
				 unsigned  short									usRunningStatus;
				 __int64 											tLastCommTime;
				 WCHAR												wLocation[64  +  1];				//  Î»ÖÃ  
				 //
}		 WEB_CONTACT_STATUS;

typedef  struct  __refreshWebContactsInfo_t							{
				 unsigned  int										uiType;
				 unsigned  char										ucbResp;							//  ÊÇ·ñÏìÓ¦°ü
				 unsigned  char										ucbNeedDetail;						//  ÊÇ·ñÐèÒªÏ¸½ÚÐÅÏ¢ÇëÇó£®´Ë±êÖ¾Î»µÄÒâÒåÔÚÓÚ¶ÔÊ×°ü·µ»ØËùÓÐÐÅÏ¢£¬¶ÔºóÐø°ü·µ»Ø²¿·ÖÐÅÏ¢
				 unsigned  short									usCnt;
				 WEB_CONTACT_STATUS									mems[CONST_maxTmpMessengers];
				 //
				 void									*			pInternal;							//  ÒÔÏÂÎªÄÚ²¿±äÁ¿£¬·ÇÕýÊ½Ê¹ÓÃ
				 unsigned  short									usCnt_mems;							//  Óöµ½CONST_qnmCfgId_memµÄ´ÎÊý
				 //
}		 REFRESH_WEBCONTACTS_INFO;


/////////

typedef  struct  __customerServiceObj_t								{
				 QY_MESSENGER_ID									idInfo;

				 //
				 unsigned  int										uiLangId;
				 unsigned  int										uiCategoryId;
				 TCHAR												displayName[64];

}		 CUSTOMER_service_obj;

//
typedef  struct  __retrieveCustomerServiceObjListReq_t				{
				 unsigned  int										uiType;
				 unsigned  char										ucbResp;

				 //
				 unsigned  int										uiLangId;					//  在请求里作为限定条件
				 unsigned  int										uiCategoryId;				//

				 //
				 unsigned  short									usCnt;
				 CUSTOMER_service_obj								mems[8];

				 //
				 void									*			pInternal;					//  ÒÔÏÂÎªÄÚ²¿±äÁ¿£¬·ÇÕýÊ½Ê¹ÓÃ
				 int												index;

}		 RETRIEVE_customerServiceObjList_req;


//  2011/04.06
typedef  struct  __queryCustomerServiceOfficerReq_t					{
				 unsigned  int										uiType;
				 unsigned  char										ucbResp;
				 //
				 TCHAR												talkerDesc[64];
}		 QUERY_customerServiceOfficer_req;


typedef  struct  __queryCustomerServiceOfficerReplyReq_t			{
				 unsigned  int										uiType;
				 //
				 __int64											tStartTime_org;						//  ÇëÇó·¢ÆðµÄÊ±¼ä, ÕâÊÇÎªÁËÈ·¶¨ÊÇÄÄ¸öÈÎÎñ±»µÃµ½ÁËÔÊÐí
				 unsigned  int										uiTranNo_org;						//
				 //
				 TCHAR												talkerDesc[64];
}		 QUERY_customerServiceOfficer_replyReq;


/////////////

//
#define		CONST_maxCnt_recentFriends								300

//  
typedef  struct  __refreshRecentFriendReq_h_t							{									//  µ¥¸öÁªÏµÈËµÄË¢ÐÂÇëÇó
				 QY_MESSENGER_ID									idInfo;
				 __int64											tLastRefreshedTime_misServ;			//  ±íÃ÷¸ÃÁªÏµÈËÊÇÊ²Ã´Ê±¼ä£¨·þÎñÆ÷Ê±¼ä£©µÄ×´Ì¬
}				 REFRESH_RECENTFRIEND_REQ_h;

//
typedef  struct  __refreshRecentFriendsReq_h_t						{									//  ×ÜµÄÁªÏµÈËµÄË¢ÐÂÇëÇó
				 unsigned  int										uiType;
				 __int64											tLastRefreshedTime_misServ;			//  ÉÏ´ÎµÄË¢ÐÂ¹¤×÷µÄ·þÎñÆ÷Ê±¼ä¡£
				 unsigned  short									usCnt;
				 REFRESH_RECENTFRIEND_REQ_h							mems[CONST_maxCnt_recentFriends];
}		 REFRESH_RECENTFRIENDS_REQ_h;


//
typedef  struct  __at_refreshRecentFriendReq_n_t {
				 //
				 unsigned  char		idInfo_buf[8];
				 unsigned  char		tLastRefreshedTime_misServ_buf[8];
				 //
}		 AT_REFRESH_RECENTFRIEND_REQ_n;


//
typedef  struct  __at_refreshRecentFriendsReq_n_t {
				 unsigned  char		uiType_buf[4];
				 unsigned  char		ucReqType_buf[1];					//  用来表示refreshRecentFriendsReq的类型
				 unsigned  char		tLastRefreshedTime_misServ_buf[8];
				 //
				 unsigned  char		usCnt_buf[2];
				 //
				 unsigned  char		mems_buf[sizeof(AT_REFRESH_RECENTFRIEND_REQ_n) * CONST_maxCnt_recentFriends];
}		 AT_REFRESH_RECENTFRIENDS_REQ_n;




//  ×î½üÁªÏµÈËË¢ÐÂÏìÓ¦
typedef  struct  __refreshRecentFriendResp_h_t						{									//  µ¥¸öÁªÏµÈËµÄ×´Ì¬, ´Ë½á¹¹²»ÓÃÀ´Í¨ÐÅ£¬½«×ª³ÉÁ÷À´´«Êä
				 QY_MESSENGER_ID									idInfo;
				 
				 unsigned  long										ulIp;
				 unsigned  long										ulDetectedIp;
				 unsigned  short									usRunningStatus;
				 
				 //
				 __int64											conf_ui64Id;

				 //
}		 REFRESH_RECENTFRIEND_RESP_h;

//
typedef  struct  __refreshRecentFriendsResp_h_t						{									//  ×ÜµÄÁªÏµÈËµÄË¢ÐÂÏìÓ¦¡£Òª×ª³ÉÁ÷²ÅÄÜÓÃÓÚ´«Êä
				 unsigned  int										uiType;
				 __int64											tLastRefreshedTime_misServ;			//  ÕâÒ»´ÎµÄÏìÓ¦·þÎñÆ÷Ê±¼äÊÇÊ²Ã´
				 unsigned  short									usCnt;
				 REFRESH_RECENTFRIEND_RESP_h						mems[CONST_maxCnt_recentFriends];

				 void									*			pInternal;							//  ÒÔÏÂÎªÄÚ²¿±äÁ¿£¬·ÇÕýÊ½Ê¹ÓÃ
				 unsigned  short									usCnt_mems;							//  Óöµ½CONST_qnmCfgId_memµÄ´ÎÊý

}		 REFRESH_RECENTFRIENDS_RESP_h;

 //
typedef  struct  __at_refreshRecentFriendResp_n_t {									//  µ¥¸öÁªÏµÈËµÄ×´Ì¬, ´Ë½á¹¹²»ÓÃÀ´Í¨ÐÅ£¬½«×ª³ÉÁ÷À´´«Êä
				 //
				 unsigned  char									idInfo_buf[8];

				 unsigned  char									ulIp_buf[4];
				 unsigned  char									ulDetectedIp_buf[4];
				 unsigned  char									usRunningStatus_buf[2];

}		 AT_REFRESH_RECENTFRIEND_RESP_n;

//
typedef  struct  __at_refreshRecentFriendsResp_n_t {									//  ×ÜµÄÁªÏµÈËµÄË¢ÐÂÏìÓ¦¡£Òª×ª³ÉÁ÷²ÅÄÜÓÃÓÚ´«Êä
				 unsigned  char 								uiType_buf[4];
				 unsigned  char								ucReqType_buf[1];
				 unsigned  char								tLastRefreshedTime_misServ_buf[8];			//  ÕâÒ»´ÎµÄÏìÓ¦·þÎñÆ÷Ê±¼äÊÇÊ²Ã´
				 //
				 unsigned  char								usCnt_buf[2];
				 //
				 unsigned  char								mems_buf[sizeof(AT_REFRESH_RECENTFRIEND_RESP_n) * CONST_maxCnt_recentFriends];
				 	

}		 AT_REFRESH_RECENTFRIENDS_RESP_n;




//
typedef  struct  __qisIntervalParams_t								{										//  2005/06/10
				 //  unsigned  int										uiType;

				 //  unsigned  short								usGetCfgInterval;

				 unsigned  short									usIntervalInS_refreshRecentFriends;
				 unsigned  short									usIntervalInS_refreshContactList;
				 //				
}		 QIS_INTERVAL_PARAMS;


//  2011/01/30
typedef  struct  __qisGetCfgsReq_t									{
				 unsigned  int										uiType;

				 unsigned  char										ucbResp;

				 unsigned  int										uiSizePerSnd_media;

				 QIS_INTERVAL_PARAMS								intervalParams;

				 //  2015/07/28
				 //unsigned  char										ucbNotUseP2pCall;

}		 QIS_getCfgs_req;




//
typedef  struct  __qisCaReq_t										{
				 unsigned  int										uiType;
				 //
				 unsigned  char										ucbResp;
				 //
				 char												ca_sendData[2048];
				 unsigned  int										ca_sendDataLen;

				 //
				 short												sHgCmd;

				 //
				 char												ca_servData[4096];
				 unsigned  int										ca_servDataLen;

				 //
				 char												ca_cliData[4096];
				 unsigned  int										ca_cliDataLen;


}		 QIS_ca_req;


///////////////////
//
typedef  struct  __refreshImObjMemInfo_t							{
	unsigned  int													uiType;								//  2011/01/29

	//
	unsigned  short													usOp;

	//
}		 RefreshImObjMemInfo;



///////////////



//  GSM Modem
typedef  struct  __qyVDevCom_t										{
				 QY_MESSENGER_ID									idInfo;
				 TCHAR												wDevIdStr[128  +  1];
				 TCHAR												name[64  +  1];
				 TCHAR												model[64  +  1];
				 char												smsc[64  +  1];
				 int												iStatus;				 
}		 QY_VDEV_COM;

#define		CONST_maxComs											64

typedef  struct  __qyVDevComs_t										{					//  QY_VDEV_INFO
				 MACRO_qyVDev_common
				 //
				 unsigned  short									usCnt;
				 QY_VDEV_COM										mems[CONST_maxComs];
				 //
				 void									*			pInternal;
				 unsigned  short									usCnt_mems;

}		 QY_VDEV_COMS;


typedef  struct  __qyVDevComRcd_t									{
				 int												id;
				 TCHAR												misServName[128  +  1];
				 QY_MESSENGER_ID									idInfo;
				 TCHAR												wDevIdStr[128  +  1];
				 //
				 TCHAR												name[255  +  1];
				 TCHAR												model[255  +  1];
				 char												smsc[255  +  1];
				 int												iStatus;				 
				 //
				 char												startTime[14  +  1];
				 char												endTime[14  +  1];
}		 QY_VDEVCOM_RCD;


typedef  struct  __qySmContact_t									{
				 TCHAR												wDevIdStr[128  +  1];
				 TCHAR												cusName[255  +  1];
				 QY_MESSENGER_ID									idInfo_contact;
}		 QY_SM_CONTACT;

//  2008/01/28
typedef  struct  __retrieveSmPolicy									{	
				 MACRO_qyVDev_common
				 //  
				 unsigned  char										ucbDefaultSmServer;
				 //
				 unsigned  short									usCnt;
				 QY_SM_CONTACT										mems[CONST_maxComs  +  1];
				 //
				 void									*			pInternal;
				 unsigned  short									usCnt_mems;

}		 RETRIEVE_SM_POLICY;




typedef  struct  __qySmContactRcd_t									{
				 int												id;
				 TCHAR												misServName[CONST_maxMisServNameLen  +  1];
				 QY_MESSENGER_ID									idInfo;
				 TCHAR												wDevIdStr[128  +  1];
				 //
				 unsigned  char										ucbDefaultSmServer;

				 TCHAR												cusName[255  +  1];
				 //
				 unsigned  char										ucbPublic;
				 //
				 unsigned  char										ucbDefault;				 
				 //
				 QY_MESSENGER_ID									idInfo_contact;
				 TCHAR												displayName[255  +  1];
				 //
				 unsigned  char										ucbImSwitchable;
				 //
				 char												startTime[CONST_qyTimeLen  +  1];
				 char												endTime[CONST_qyTimeLen  +  1];
				 //
				 int												iStatus;
		
}		 QY_SMCONTACT_RCD;


#define		CONST_maxCnt_retrievePhoneMsgrs							300
//
typedef  struct  __retrievePhoneMsgr_t								{
				 WCHAR												wDevIdStr[32  +  1];						//  ÊÖ»úºÅ¡£
				 QY_MESSENGER_ID									idInfo;										//  2008/02/14
				 TCHAR												displayName[64  +  1];						//  ÏÔÊ¾ÓÃ£¬±ãÓÚÊ¶±ð¡£
}		 RETRIEVE_PHONE_MSGR;

typedef  struct  __retrievePhoneMsgrs_t								{
				 unsigned  int										uiType;
				 //
				 unsigned  short									usMaxPhoneMsgrsPerSnd;						//  Ò»´Î¿ÉÒÔÏÂÔØ×î¶à¶àÉÙ¸öÊÖ»úÁªÏµÈËÐÅÏ¢
				 //
				 WCHAR												wDevIdStr_lastRefreshed[32  +  1];			//  ÉÏ´ÎµÄË¢ÐÂ½Úµã

				 //
				 unsigned  char										ucbResp;									//  ÊÇ·ñÏìÓ¦
				 unsigned  char										ucbEnd;										//  ÊÇ·ñÏìÓ¦Êý¾ÝÒÑ¾­½áÊø¡£

				 unsigned  short									usCnt;
				 RETRIEVE_PHONE_MSGR								mems[CONST_maxCnt_retrievePhoneMsgrs];
				 //
				 void									*			pInternal;
				 unsigned  short									usCnt_mems;

}		 RETRIEVE_PHONE_MSGRS;



typedef  struct  __retrieveToPath_t									{											//  2008/02/09
				 unsigned  char										ucbDefaultSmServer;
				 QY_MESSENGER_ID									idInfo_vDev;
				 TCHAR												wDevIdStr[128  +  1];
				 TCHAR												cusName[64  +  1];
}		 RETRIEVE_TO_PATH;

#define		CONST_maxToPaths										24											//  ×î¶à¿ÉÒÔµÄ·¢ËÍÍ¨µÀÊý
//
typedef  struct  __retrieveToPaths_t								{
				 unsigned  int										uiType;
				 //
				 unsigned  char										ucbResp;
				 //
				 unsigned  short									usMaxMemsPerSnd;
				 //
				 unsigned  short									usCnt;
				 RETRIEVE_TO_PATH									mems[CONST_maxToPaths];
				 //
				 void									*			pInternal;
				 unsigned  short									usCnt_mems;

}		 RETRIEVE_TO_PATHS;


//////////////



//
typedef  struct  __refreshDynBmps_t									{
				 unsigned  int										uiType;
				 //
				 unsigned  char										ucbResp;
				 //
				 //  unsigned  int										uiObjType;
				 __int64											tLastModifiedTime;

				 //
				 unsigned  short									usCnt;
				 QIS_dynBmp_info										mems[8];

				 void									*			pInternal;
				 unsigned  short									usCnt_mems;

}		 REFRESH_DYN_BMPS;

//  2011/10/31
typedef  struct  __verifyViewDynBmp_t								{
				 unsigned  int										uiType;
				 //
				 unsigned  char										ucbResp;
				 //
				 QY_MESSENGER_ID									idInfo_viewer;
				 //
				 unsigned  int										uiCmd;
				 //
}		 VERIFY_viewDynBmp;

//
typedef  struct  __retrieveDynBmps_t								{
				 unsigned  int										uiType;
				 //
				 unsigned  char										ucbResp;
				 //
				 __int64											tLastRefreshedTime_misServ;		//  2009/09/03
				 union												{
					 struct											{
						 //
						 unsigned  char								ucbRetrieveOne;					//  2014/09/04
						 //
						 unsigned  char								ucbNext;
						 QY_MESSENGER_ID							idInfo;
						 unsigned  int								uiObjType;
						 unsigned  short							usIndex_obj;

					 }												req;
					 struct											{
						 unsigned  char								ucbEnd;
					 }												resp;
				 }													u;
				 				 
				 //  2014/09/25
				 struct												{						
					 QY_MESSENGER_ID								idInfo_imGrp_related;			//  2014/09/25					
				 }													conf;
				 
				 //  2017/06/11
				 unsigned  char										ucbAvConsole;					//  2017/06/11

				 //
				 unsigned  short									usCnt;
				 QIS_dynBmp_info									mems[8];

				 void									*			pInternal;
				 unsigned  short									usCnt_mems;

}		 RETRIEVE_DYN_BMPS;


//
typedef  struct  __qyDynBmpRcd_t									{
				 int												id;
				 TCHAR												misServName[255  +  1];
				 QY_MESSENGER_ID									idInfo;
				 unsigned  int										uiObjType;
				 unsigned  short									usIndex;
				 TCHAR												name[255  +  1];
				 TCHAR												cusName[255  +  1];
				 int												iStatus;
				 //
				 char												startTime[14  +  1];
				 char												endTime[14  +  1];
				 //
				 struct												{
					 unsigned  char									ucbFound;
				 }													tmpInternal;

}		 QY_dynBmp_RCD;


//
typedef  struct  __qyDynBmpRuleRcd_t								{
				 int												id;
				 
				 TCHAR												misServName[255  +  1];
				 QY_MESSENGER_ID									idInfo;				 
				 //
				 QY_MESSENGER_ID									idInfo_visitor;			 
				 //										
				 unsigned  int										uiRuleCmd;
				 //
				 int												iStatus;				 
				 //
				 char												startTime[14  +  1];
				 char												endTime[14  +  1];			 
				 //																				//
}		 QY_dynBmpRule_RCD;



//  2015/08/02
#define		CONST_procOfflineResSubtype_null						0
#define		CONST_procOfflineResSubtype_getCfgs						1
#define		CONST_procOfflineResSubtype_retrieve					2
#define		CONST_procOfflineResSubtype_upload						3
#define		CONST_procOfflineResSubtype_download					4
#define		CONST_procOfflineResSubtype_del							5



//
typedef  struct  __qisOfflineRes_t									{
				 QIS_res_obj										res;
				 //
				 unsigned  __int64									ui64FileLen;
				 TCHAR												name[128];
				 __int64											tCreationTime;		//  2015/08/12
				 
}		 QIS_offline_res;

//
#define		M_procOfflineRes_common									unsigned  int					uiType;			\
																	unsigned  char					ucbResp;		\
																	unsigned  short					usSubtype;		\
																	HWND							hTool_offlineRes;



//
typedef  struct  __procOfflineResCommon_t							{
				 M_procOfflineRes_common
}		 PROC_offlineRes_common;

//
typedef  struct  __procOfflineRes_getCfgs_t							{
				 M_procOfflineRes_common
				 //					
				 struct												{
						 QY_MESSENGER_ID							idInfo_resServ;					
				 }													resp;

}		 PROC_offlineRes_getCfgs;


//
#define		MAX_offlineRes_mems										16

//
typedef  struct  __procOfflineRes_retrieve_t						{
				 M_procOfflineRes_common
				 //
				 struct												{
						 QY_MESSENGER_ID							idInfo_logicalPeer;
						 //
						 unsigned  char								ucbP2p;						//  2015/08/05
						 //
						 unsigned  short							usIndex_page;				//  0 based index. 2015/08/13
						 unsigned  short							max_usCnt;					//  max of usCnt
						 TCHAR										keyword[128];				//  

				 }													req;
				 //
				 struct												{
						 unsigned  short							usCnt;
						 QIS_offline_res							mems[MAX_offlineRes_mems];
				 }													resp;
				 
				 //
				 void									*			pInternal;
				 unsigned  short									usCnt_mems;
				 	
}		 PROC_offlineRes_retrieve;

//
typedef  struct  __procOfflineRes_upload_t							{
				 M_procOfflineRes_common
				 //
				 TCHAR												fileName[128];
				 //				
				 QY_MESSENGER_ID									idInfo_logicalPeer;
				
				 //
				 void									*			pInternal;
				 TCHAR												fullFileName[MAX_PATH  +  1];
				 
				 //
}		 PROC_offlineRes_upload;

//
typedef  struct  __procOfflineRes_download_t						{
				 M_procOfflineRes_common
				 //
				 TCHAR												fileName[128];
				 QY_MESSENGER_ID									idInfo_sender;
				 __int64											tCreationTime;		//  2015/08/12
				 //				
				 QY_MESSENGER_ID									idInfo_logicalPeer;
				
				 //
				 void									*			pInternal;
				 
				 //
}		 PROC_offlineRes_download;

//
//
typedef  struct  __procOfflineRes_del_t								{
				 M_procOfflineRes_common
				 //
				 TCHAR												fileName[128];
				 QY_MESSENGER_ID									idInfo_sender;
				 __int64											tCreationTime;		//  2015/08/12
				 //				
				 QY_MESSENGER_ID									idInfo_logicalPeer;
				
				 //
				 void									*			pInternal;
				 
				 //
}		 PROC_offlineRes_del;





//  2015/08/02
typedef  union  __procOfflineResU_t									{
				 PROC_offlineRes_common								common;
				 //
				 PROC_offlineRes_getCfgs							getCfgs;
				 //
				 PROC_offlineRes_retrieve							retrieve;
				 //
				 PROC_offlineRes_upload								upload;
				 //
				 PROC_offlineRes_download							download;
				 //
				 PROC_offlineRes_del								del;

}		 PROC_offlineRes_u;





////////////////
//  2011/01/18

//
#define		CONST_printShowFlg_pktIn								0x1
#define		CONST_printShowFlg_pktOut								0x1  <<  1
#define		CONST_printShowFlg_procBt								0x1  <<  2		//	CONST_printShowFlg_procBtOff
#define		CONST_printShowFlg_pSelf								0x1  <<  3
#define		CONST_printShowFlg_noCorresponding						0x1  <<  4
#define		CONST_printShowFlg_postMsg2OutputQ_msgr					0x1  <<  5
#define		CONST_printShowFlg_bigElapse							0x1  <<  6
#define		CONST_printShowFlg_sendFinished							0x1  <<  7
#define		CONST_printShowFlg_switchRouteQ							0x1  <<  8



//  2015/09/01
typedef  struct  __printDaemonShowInfo_t							{
				 unsigned  long										ulFlgs;				
}		 PRINT_daemon_showInfo;

//  2015/09/01
#define		DEFAULT_printDaemonShowInfo_ulFlgs						0

//
#define		isPrint_pktIn(  ulFlgs  )								(  ulFlgs  &  CONST_printShowFlg_pktIn  )
#define		isPrint_pktOut(  ulFlgs  )								(  ulFlgs  &  CONST_printShowFlg_pktOut  )
#define		isPrint_procBt(  ulFlgs  )								(  ulFlgs  &  CONST_printShowFlg_procBt  )
#define		isPrint_pSelf(  ulFlgs  )								(  ulFlgs  &  CONST_printShowFlg_pSelf  )
#define		isPrint_noCorresponding(  ulFlgs  )						(  ulFlgs  &  CONST_printShowFlg_noCorresponding  )
#define		isPrint_postMsg2OutputQ_msgr(  ulFlgs  )				(  ulFlgs  &  CONST_printShowFlg_postMsg2OutputQ_msgr  )
#define		isPrint_bigElapse(  ulFlgs  )							(  ulFlgs  &  CONST_printShowFlg_bigElapse  )
#define		isPrint_sendFinished(  ulFlgs  )						(  ulFlgs  &  CONST_printShowFlg_sendFinished  )
#define		isPrint_switchRouteQ(  ulFlgs  )						(  ulFlgs  &  CONST_printShowFlg_switchRouteQ  )

//
typedef  struct  __netStats_total_t									{
				 IM_NET_STAT										netStat_f, netStat_a, netStat_v, netStat_others;
				 IM_NET_STAT										netStat_op;			//  2016/12/26
				 IM_NET_STAT										netStat_admin;
				 //
				 int												n_talkingChannels;	//  2017/10/28
}		 NET_STATS_total;




typedef  struct  __qmdChannelStatus_t								{
				 IM_NET_STAT										stat;
				 CHANNEL_status_io									io;				 
}		 QMD_channel_status;


//
typedef  struct  __qmdStatus_msgrMem_t								{
				 QY_MESSENGER_ID									idInfo;																//  如果idInfo为0，则表明是总流量
				 QMD_channel_status									t,  f,  a,  v;
				 QMD_channel_status									op;	//    2016/12/26
}		 QMD_status_msgrMem;


//
typedef  struct  __qmdStatus_channelMem_t							{
				 unsigned  int										uiCliIndex;
				 QMD_channel_status									status;
				 QY_MESSENGER_ID									idInfo;
				 unsigned  int										uiChannelType;
				 //
				 unsigned  long										ulIp;								//  2015/09/11
				 unsigned  int										uiSessionId;
				 //
}		 QMD_status_channelMem;


//
#define		CONST_iDaemonStatusType_null							0
#define		CONST_iDaemonStatusType_msgr							1
#define		CONST_iDaemonStatusType_channel							2

//
typedef  struct  __qmdStatus_t										{
				 unsigned  int										uiType;

				 unsigned  char										ucbResp;

				 int												iSubType;

				 unsigned  char										ucbGetTotal;						//  req
				 QY_MESSENGER_ID									idInfo;								//  req, to get status from

				 //  2015/09/01
				 PRINT_daemon_showInfo								printDaemonShowInfo;				//  req, to control flgs
				  
				 //
				 struct												{
					 HWND											hWnd_status;
					 //
					 unsigned  short								usCnt_mems;
				 }													tmpInternal;

				 NET_STATS_total									total;

				 unsigned  short									usCnt;
				 union												{
					 struct											{
						 QMD_status_msgrMem							mems[256];
					 }												msgr;
					 struct											{
						 QMD_status_channelMem						mems[256];
					 }												channel;
				 }													u;

}		 QMD_status;


//
#define		CONST_mcuType_null										0
#define		CONST_mcuType_confServ									1
#define		CONST_mcuType_fileServ									2


//
typedef  struct  __qmdMcuStatusMem_t								{
				 QY_MESSENGER_ID									idInfo_mcu;
				 //
				 unsigned  short									usMcuType;

				 //
				 QY_MESSENGER_ID									idInfo_conf;
				 QY_MESSENGER_ID									idInfo_initiator;
				 //
				 __int64											tStartTime_task;
				 //
				 QMD_status_msgrMem									mcuStatus;

				 //
}		 QMD_mcuStatus_mem;

//
extern QY_DMITEM  CONST_mcuTypeTable[];


//
typedef  struct  __qmdMcuStatusList_t								{
				 unsigned  int										uiType;

				 //
				 struct												{
					 unsigned  short								usCnt_mems;
					 //
					 int											index_mcu;
					 //
				 }													tmpInternal;


				 //
				 unsigned  short									usCnt;
				 QMD_mcuStatus_mem									mems[256];

}		 QMD_mcuStatus_list;



//
typedef  struct  __qmdPolicy_t										{
				 unsigned  int										uiType;
				 //
				 TCHAR												mcuUsrName[128];
				 char												mcuPasswd[128];
				 TCHAR												mcuDomainName[128];

}		 QMD_policy;


//
//  2016/12/28
typedef  struct  __testSpeedReq_t									{
				 //
				 BOOL												bResp;
				 //
				 unsigned  int										tn_perSend;
				 //
				 unsigned  short									usLen;
				 char												buf[1250  *  1000];
}		 TEST_speed_req;



////////////


typedef  union	 __imContentU_t										{									//  ÄÚ²¿´¦ÀíÊ±£¬¶¼²ÉÓÃwcharÀàÐÍ£¬·¢ËÍÒÔutf8·¢ËÍ
				 unsigned  int										uiType;								//  ´ËÀàÐÍ¿ÉÒÔ¶à¸öÖµ£¬Çø·Öhtml,txtµÈ¸ñÊ½
				 IM_SIMPLE_RESP										simpleResp;
				 //  IM_STREAM_CONTENT									stream;							//  2011/01/29
				 IM_DATA_CONTENT									data;
				 IM_L_STREAM										lStream;
				 //
				 //  QIS_INTERVAL_PARAMS							intervalParams;						//  2007/12/01
				 QIS_getCfgs_req									getCfgsReq;							//  2011/01/30
				 //
				 RETRIEVE_IMOBJLIST_REQ								retrieveImObjListReq;
				 RETRIEVE_IMGRPLIST_RESP							retrieveImGrpListResp;
				 RETRIEVE_IMGRPMEMLIST_RESP							retrieveImGrpMemListResp;
				 RETRIEVE_CONTACTLIST_RESP							retrieveContactListResp;
				 RETRIEVE_IMOBJLISTEND_RESP							retrieveImObjListEndResp;
				 
				 //
				 REFRESH_RECENTFRIENDS_REQ_h						refreshRecentFriendsReq;			//  2007/07/12
				 REFRESH_RECENTFRIENDS_RESP_h						refreshRecentFriendsResp;


				 //
				 CONF_req											confReq;
				 MCU_cmd											mcuCmd;

				 //
				 IM_GRP_EX											imGrpEx;
				 //
				 QIS_ca_req											qisCaReq;

				 //
				 RefreshImObjMemInfo								refreshImObjMemInfo;

				 //
				 ChkLogonIdReq										chkLogonIdReq;

				 //
				 RETRIEVE_customerServiceObjList_req				retrieveCustomerServiceObjListReq;	//  2011/04/04
				 QUERY_customerServiceOfficer_req					queryCustomerServiceOfficerReq;		//  2011/04/06
				 QUERY_customerServiceOfficer_replyReq				queryCustomerServiceOfficerReplyReq;//  2011/04/06
				 //
				 RETRIEVE_WEBCONTACTLIST_RESP						retrieveWebContactListResp;
				 REFRESH_WEBCONTACTS_INFO							refreshWebContactsInfo;				//  2007/12/22

				 // 
				 TRANSFER_FILE_REQ									transferFileReq;
				 TRANSFER_FILE_REPLYREQ								transferFileReplyReq;				//  2007/07/06
				 TRANSFER_FILEDATA_REQ								transferFileDataReq;
				 TRANSFER_FILEDATA_RESP								transferFileDataResp;
				 TRANSFER_FILEEND_REQ								transferFileEndReq;
				 TRANSFER_FILEEND_RESP								transferFileEndResp;
				 //
				 TASK_PROC_REQ										taskProcReq;
				 TASK_PROC_RESP										taskProcResp;
				 //
				 //
				 RTC_CALL_REQ										rtcCallReq;							//  2007/10/07
				 //
				 TRANSFER_AV_INFO									transferAvInfo;						//  2008/03/15
				 TRANSFER_AV_replyInfo								transferAvReplyInfo;
				 TRANSFER_VIDEO_DATA								transferVideoData;	
				 TRANSFER_VIDEO_dataResp							transferVideoDataResp;
				 TRANSFER_AUDIO_DATA								transferAudioData;					//  2008/04/16
				 TRANSFER_AUDIO_dataResp							transferAudioDataResp;				//  2008/04/16
				 //
				 REMOTE_ASSIST_REQ									remoteAssistReq;					//  2008/11/15
				 //
				 TASK_INTERACTION_REQ								taskInteractionReq;					//  2009/02/23
				 CONF_KEY											confKey;
				 CONF_LAYOUT										confLayout;							//  2010/12/27
				 ConfNvrInfo										confNvrInfo;
				 CONF_state											confState;							//  2017/09/17
				 CONF_ctrl_state									confCtrlState;
				 StatusConfLayoutParam								statusConfLayoutParam;

				 //
				 TRANSFER_GPS_INFO									transferGpsInfo;					//  2012/04/19
				 TRANSFER_GPS_replyInfo								transferGpsReplyInfo;				//  2012/04/19
				 TRANSFER_GPS_DATA									transferGpsData;					//  2012/04/20
				 TRANSFER_GPS_dataResp								transferGpsDataResp;				//  2012/04/20
				 //
				 //  stream
				 //
				 IM_HTML_CONTENT									html;		
				 //
				 //
				 QY_VDEV_COMS										vDevComs;
				 RETRIEVE_SM_POLICY									retrieveSmPolicy;
				 RETRIEVE_PHONE_MSGRS								retrievePhoneMsgrs;					//  2008/01/02
				 RETRIEVE_TO_PATHS									retrieveToPaths;					//  2008/02/09
				 //
				 REFRESH_DYN_BMPS									refreshDynBmps;						//  2009/08/24
				 VERIFY_viewDynBmp									verifyViewDynBmp;					//  2011/10/31
				 RETRIEVE_DYN_BMPS									retrieveDynBmps;					//  2009/09/04
				 REFRESH_imObjRules_req								refreshImObjRulesReq;				//  2010/08/15
				 //
				 PROC_offlineRes_u									procOfflineResU;					//  2015/08/01
				 
				 
				 //
				 PTZ_control_req									ptzControlReq;						//  2012/08/05
				 PTZ_control_cmd									ptzControlCmd;
				 
				 //
				 QUERY_peer_status									queryPeerStatus;					//  2014/07/11
				 
				 //
				 QY_VDEV_DATA										vDevData;


				 //
				 QMD_status											qmdStatus;							//  2011/01/08
				 QMD_mcuStatus_list									qmdMcuStatusList;
				 QMD_policy											qmdPolicy;


				 				 
}		 IM_CONTENTU;


typedef  union	 __imContentU_nh_t									{									//  2010/07/29
				 unsigned  int										uiType;								//  
				 IM_SIMPLE_RESP										simpleResp;
				 //  IM_STREAM_CONTENT_nh								stream;
				 IM_L_STREAM_nh										lStream;
}		 IM_CONTENTU_nh;




//////////////
//

#define		CONST_misMsgType_null								0
#define		CONST_misMsgType_base								CONST_qyWmParam_misMsg_base
#define		CONST_misMsgType_resp_onlySock						(  CONST_misMsgType_base  +  1  )	//  
#define		CONST_misMsgType_quit								(  CONST_misMsgType_base  +  2	)
#define		CONST_misMsgType_closeSession						(  CONST_misMsgType_base  +  3	)
#define		CONST_misMsgType_input								(  CONST_misMsgType_base  +  4	)
#define		CONST_misMsgType_send								(  CONST_misMsgType_base  +  5	)	//  
#define		CONST_misMsgType_processSelf						(  CONST_misMsgType_base  +  6	)	//  
#define		CONST_misMsgType_processBt							(  CONST_misMsgType_base  +  7  )	//  2011/04/18
//#define		CONST_misMsgType_processSelf_sendFinished			(  CONST_misMsgType_base  +  8	)	//  2015/08/18
#define		CONST_misMsgType_processSelf_new					(  CONST_misMsgType_base  +  9	)	//  2015/08/21
#define		CONST_misMsgType_inputArrive						(  CONST_misMsgType_base  +  10  )	//  2015/08/24
//#define		CONST_misMsgType_resp1								(  CONST_misMsgType_base  +  11	 )	//  2015/08/25. 暂时用来替换resp,以帮助发现未加密的resp
#define		CONST_misMsgType_resp2								(  CONST_misMsgType_base  +  12	 )	//  2015/08/25. resp的处理标识已经是网络字节流顺序，resp2表明不是网络顺序


																									//  
//  #define		CONST_misMsgType_resumeToSend					(  CONST_misMsgType_base  +  16  )	//	
//  
#define		CONST_misMsgType_req								(  CONST_misMsgType_base  +  130	 )	//  messenger·
#define		CONST_misMsgType_resp								(  CONST_misMsgType_base  +  131	 )	//  iocp·
#define		CONST_misMsgType_talk								(  CONST_misMsgType_base  +  132	 )	//  
#define		CONST_misMsgType_task								(  CONST_misMsgType_base  +  133	 )	//  
//
//
#define		CONST_misMsgType_isSendOk							(  CONST_misMsgType_base  +  250	 )	//  iocp iocp tranNo. messenger outputQ iocp,tranNo starttime
#define		CONST_misMsgType_sendOk								(  CONST_misMsgType_base  +  251	 )	//  MGR tranNo. messenger iocp, tranNoºÍstarttime
																									//  mgr·
//
#define		CONST_misMsgType_sendFinished						(  CONST_misMsgType_base  +  252	 )	//  mgr
//
//  #define		CONST_misMsgType_closeChannel					(  CONST_misMsgType_base  +  53  )	//  2007/12/20, QMemMessenge
#define		CONST_misMsgType_closeChannelByCliIndex				(  CONST_misMsgType_base  +  253  )	//  2007/12/20, 
#define		CONST_misMsgType_chkChannelByType_mgr				(  CONST_misMsgType_base  +  254  )	//  2015/08/26, 
//
#define		CONST_misMsgType_applyForWork						(  CONST_misMsgType_base  +  255  )	//  

//
//#define		CONST_misMsgType_confMgr							(  CONST_misMsgType_base  +  260  )


//////
#define		CONST_misMsgType_taskStatus							(  CONST_misMsgType_base  +  360  )	//  
#define		CONST_misMsgType_imMsgRcd							(  CONST_misMsgType_base  +  361  )	//  
#define		CONST_misMsgType_event								(  CONST_misMsgType_base  +  362  )	//  

//  2008/05/26
#define		CONST_misMsgType_grp								(  CONST_misMsgType_base  +  400  )	//  ×éºÏ°ü¡£×éºÏ°üÓÐÊ±ºÜ´ó.²»Òª½«MIS_MSGUºÍ×éºÏ°ü»ìÆðÀ´¡£·ñÔò£¬Ó°ÏìÍ¨³£µÄMIS_MSGUµÄÄÚ´æ·ÖÅä¡£

//
#define		CONST_misMsgType_serv_base							(  CONST_misMsgType_base  +  500  )
//
//#define		CONST_misMsgType_getDaemonStatus					(  CONST_misMsgType_base  +  585  )	//  2011/01/12



//  ÒÔÉÏÊÇ°üÀàÐÍ
#define		CONST_misMsgType_talkingFriend_qmc					(  CONST_misMsgType_base  +  670	 )	//	talkingFriendQ
#define		CONST_misMsgType_recentFriend_qmc					(  CONST_misMsgType_base  +  671	 )	//	recentFriendQ
#define		CONST_misMsgType_displayedElem_qmc					(  CONST_misMsgType_base  +  672	 )	//  
#define		CONST_misMsgType_refreshContactsStatus_qmc			(  CONST_misMsgType_base  +  673  )	//  messenger display
#define		CONST_misMsgType_refreshMeStatus_qmc				(  CONST_misMsgType_base  +  674  )	//  diplay
#define		CONST_misMsgType_applyForPlayer_qmc					(  CONST_misMsgType_base  +  675  )	//  
#define		CONST_misMsgType_applyForChkChannels_qmc			(  CONST_misMsgType_base  +  676  )	//  
//
//#define		CONST_misMsgType_applyForRemovingInvalidTasks_qmc				(  CONST_misMsgType_base  +  77  )	//  2009/09/10
//
#define		CONST_misMsgType_applyForTalkerShadow_qmc			(  CONST_misMsgType_base  +  678  )	//  2012/04/23. 由墙发起,请求dlgTalk生成一个影子窗口
//
#define		CONST_misMsgType_displayRecentFriends_qmc			(  CONST_misMsgType_base  +  679  )


//
#define		CONST_misMsgType_procVideo_qmc						(  CONST_misMsgType_base  +  680  )	//  2009/03/24
#define		CONST_misMsgType_notifyTaskEnd_qmc					(  CONST_misMsgType_base  +  681  )	//  2009/04/28
#define		CONST_misMsgType_procGps_qmc						(  CONST_misMsgType_base  +  682  )	//  2012/04/20
//
#define		CONST_misMsgType_outputTask							(  CONST_misMsgType_base  +  690  )	//  robot
//#define		CONST_misMsgType_outputTask_toMix					(  CONST_misMsgType_base  +  91  )	//  2011/01/23




//
extern  QY_DMITEM  CONST_misMsgTypeTable[];




#define		MACRO_misMsg_common									unsigned  int		uiType;


//  ×î³£ÓÃµÄÊý¾Ý°üÄÚÈÝ
//



/*  //  2007/11/30, 1.4.3°æ±¾Ç°Ê¹ÓÃµÄtalkData
typedef  struct  __misMsgTalkData_t								{
				 QY_MESSENGER_ID								idInfo_dst;
				 QY_MESSENGER_ID								idInfo_src;
				 //
				 char											buf[sizeof(  IM_CONTENTU  )  +  1024];	//  ×¢Òâ£¬ÔÚ·ÅÈë¶ÓÁÐÀï£¬²»ÒªÓÃsizeof(  data  ),  Ó¦¸ÃÊ¹ÓÃoffsetof(  ,  data  )  +  dataLen, ÒÔ½ÚÔ¼ÄÚ´æ
}		 MIS_MSG_TALKDATA;
*/

#if  0
typedef  struct  __misMsgTalkData_t								{
				 MSG_SIMPLE_ROUTE								route;	//  TALKDATA_ADDR									addr;
				 //
				 char											buf[sizeof(  IM_CONTENTU  )  +  1024];	//  ×¢Òâ£¬ÔÚ·ÅÈë¶ÓÁÐÀï£¬²»ÒªÓÃsizeof(  data  ),  Ó¦¸ÃÊ¹ÓÃoffsetof(  ,  data  )  +  dataLen, ÒÔ½ÚÔ¼ÄÚ´æ
}		 MIS_MSG_TALKDATA;
#endif 


//  ½«Ñ°Ö·ºÍÄÚÈÝ·Ö¿ªµÄÊý¾Ý°ü½á¹¹£¬2007/11/29. ÊÇ¶ÔMIS_MSG_TALKDATAµÄÑ°Ö·ÇøµÄÀ©Õ¹¡£
//  MSG_ROUTEÊÇÒ»¸öÍêÕûµÄÁ÷¡£ºóÃæIM_CONTENTUµÄ¶¨ÒåºÍÆäËûÊÇÒ»ÑùµÄ
//



//  ¿ÉÑ°Ö·µÄÊý¾Ý°ü½á¹¹. 
typedef  struct  __misMsgRouteTalkData_t						{
				 MSG_ROUTE										route;
				 //
				 char											buf[sizeof(  IM_CONTENTU  )  +  1024];
}		 MIS_MSG_routeTalkData;


//  
//#define		MACRO_msgRouteTalkData(  ucFlg,  pMsgBuf  )			(  (  isUcFlgRouteTalkData(  ucFlg  )  ||  isUcFlgTalkData(  ucFlg  )  )  ?  pMsgBuf  :  NULL  )
#define		MACRO_msgRouteTalkData(  ucFlg,  pMsgBuf  )			(  (  isUcFlgRouteTalkData(  ucFlg  )  )  ?  pMsgBuf  :  NULL  )
//  2014/09/28
//  #define		M_getMsgContent(  ucFlg,  pMsgBuf  )				(  (  isUcFlgRouteTalkData(  ucFlg  )  ||  isUcFlgTalkData(  ucFlg  )  )  ?  (  (  IM_CONTENTU  *  )(  (  MIS_MSG_routeTalkData  *  )pMsgBuf  )->buf  )  :  (  IM_CONTENTU  *  )pMsgBuf  )
//#define		M_getMsgContent(  ucFlg,  pMsgData  )				(  (  isUcFlgRouteTalkData(  ucFlg  )  ||  isUcFlgTalkData(  ucFlg  )  )  ?  (  (  IM_CONTENTU  *  )(  (  MIS_MSG_routeTalkData  *  )pMsgData  )->buf  )  :  (  IM_CONTENTU  *  )pMsgData  )
#define		M_getMsgContent(  ucFlg,  pMsgData  )				(  (  isUcFlgRouteTalkData(  ucFlg  )  )  ?  (  (  IM_CONTENTU  *  )(  (  MIS_MSG_routeTalkData  *  )pMsgData  )->buf  )  :  (  IM_CONTENTU  *  )pMsgData  )



typedef  struct  __misMsg_result_t								{						//  ÓÃÀ´ÔÚclientÎ´ÈÏÖ¤Ç°µÄmgrºÍclientµÄ´¦ÀíÄ£¿éÖ®¼äµÄÊý¾Ý´«Êä
				 MACRO_misMsg_common
				 unsigned  int									uiCliIndex;
				 //
				 unsigned  int									uiSessionId;			//  ±»´¦ÀíµÄsessionId, ÓÃÀ´ºÍcliInfos[index]µÄsessionIdÀ´±È½Ï£¬ÒÔ·ÀÖ¹·¢µÄÏìÓ¦°üÔÚ´¥·¢Ê±£¬Êµ¼ÊµÄsocketÒÑ¾­¹Ø±ÕÁË£¬»òÕßÊÇÐÂµÄSESSION¡£
				 //
				 unsigned  char									ucFlg;
				 //
				 unsigned  short								usCode;
				 unsigned  short								usCode_org;				//  ÏìÓ¦µÄÊ±ºò£¬±íÃ÷ÊÇÔ­À´µÄcmdCode
				 time_t											tStartTime;
				 unsigned  int									uiTranNo;
				 unsigned  short								usSeqNo;				//  2007/05/02
				 //
				 void									*		pQMemObj;	
				 //
				 unsigned  __int64								ui64Id_cli;				//  2015/08/24
				 unsigned  int									uiChannelType;			//  2007/07/08
				 //
				 BOOL											bAdmin;					//  2015/08/28
				 //
				 unsigned  int									lenInBytes;
				 char											buf[sizeof(  AUTH_RESP_MIS  )  +  256];
				 //
}		 MIS_MSG_RESULT;



#if  0		//  2012/02/19
#define		CONST_bufSize_misMsgRespBuf							16000  +  256

//  #define		CONST_bufSize_misMsgRespBuf							64  *  1024

#endif
//
#define		CONST_bufSize_misMsgRespBuf							128  *  1024			//  2014/02/09


typedef  struct  __misMsg_resp_t								{						//  ÓÃÀ´ÔÚclientÎ´ÈÏÖ¤Ç°µÄmgrºÍclientµÄ´¦ÀíÄ£¿éÖ®¼äµÄÊý¾Ý´«Êä
				 MACRO_misMsg_common
				 unsigned  int									uiCliIndex;
				 //
				 unsigned  int									uiSessionId;			//  ±»´¦ÀíµÄsessionId, ÓÃÀ´ºÍcliInfos[index]µÄsessionIdÀ´±È½Ï£¬ÒÔ·ÀÖ¹·¢µÄÏìÓ¦°üÔÚ´¥·¢Ê±£¬Êµ¼ÊµÄsocketÒÑ¾­¹Ø±ÕÁË£¬»òÕßÊÇÐÂµÄSESSION¡£
				 //
				 unsigned  char									ucFlg;
				 //
				 unsigned  short								usCode;
				 unsigned  short								usCode_org;				//  ÏìÓ¦µÄÊ±ºò£¬±íÃ÷ÊÇÔ­À´µÄcmdCode
				 time_t											tStartTime;
				 unsigned  int									uiTranNo;
				 unsigned  short								usSeqNo;				//  2007/05/02

				 //  2015/09/05
				 time_t											tStartTime_processed;
				 unsigned  int									uiTranNo_processed;
				 unsigned  int									nTimes_tryToSend;					//  mgr iocp 
				 
				 //  
				 unsigned  int									lenInBytes;
				 char											buf[CONST_bufSize_misMsgRespBuf];		//  2007/10/19
				 //				 
}		 MIS_MSG_RESP;



//  2007/11/30
//  
//		MIS_MSG_TALK
//  ucFlg CONST_commFlg_talkData MIS_MSG_TALKDATA
//  ucFlg CONST_commFlg_addrTalkData MIS_MSG_addrTalkData
//



//  2007/12/02, MIS_MSG_INPUT, MIS_MSG_TALK, MIS_MSG_TASK

typedef  struct  __misMsg_talk_t								{									//  2007/11/29, addressable talk
				 MACRO_misMsg_common
				 //
				 unsigned  int									uiCliIndex;							//  input daemon
				 QY_MESSENGER_ID								idInfo_cli;
																			
				 //
				 unsigned  int									uiSessionId;
				 unsigned  int									uiStep;								//  2008/04/28

				 unsigned  char									ucbConvrted;						//  input 2007/7/14

				 unsigned  char									ucbConvrted_msgRoute;				//  daemon input 
				 unsigned  short								lenInBytes_msgRouteInDataBuf;		//  daemon input data.route route data.buf
																									//  lenInBytes_msgRouteInDataBuf data.buf route

																									//  mc MisCnt qmd uiCliIndex, 2007/06/10
				 void								*			pMisCnt;							//  misCntµÄ, 2007/06/02
				 MSGR_ADDR										addr_logicalPeer;					//  messenger. 
				 
				 //
				 unsigned  char									ucFlg;		
				 //
				 unsigned  short								usCode;
				 unsigned  short								usCode_org;							//  
				 time_t											tStartTime;
				 unsigned  int									uiTranNo;
				 unsigned  short								usSeqNo;

				 time_t											tStartTime_processed;				//  iocp uiTranNo_mgr iocp
				 unsigned  int									uiTranNo_processed;
				 unsigned  int									nTimes_tryToSend;					//  mgr iocp 
				 //
				 time_t											tTime_alive;						//  2014/12/09. 当没有找到新的视频数据时，刷新此变量，也可以表明任务是活跃的
				 //
				 time_t											tTime_applyForChkTaskAlive;			//  2010/10/30
				 unsigned  char									nTimes_applyForChkTaskAlive;		//  2014/12/09

				 //
				 unsigned  int									uiTaskMode_unused;					//  2009/08/23

				 //
				 int											iTaskId;							//  
				 unsigned  int									uiTaskType;							//  
				 QY_MESSENGER_ID								idInfo_taskSender;					//  
				 QY_MESSENGER_ID								idInfo_taskReceiver;				//  
				 int											iStatus;							//  2007/07/18
				 time_t											tLastModifiedTime;					//  2014/05/01
				 
				 //
				 bool											bFrom_sharedObj;
				 int											index_sharedObj;

				 //  
				 time_t											tRecvTime;							//  
				 DWORD											dwTickCnt_start;					//  ( ms ). 
				 DWORD											dwTickCnt_toSend;					//  2011/01/22. start->toSendQ
																									//  
				 unsigned  short								usElapsed_recved;					//  
				 unsigned  short								usElapsed_serv_startToProcess;		//  mtMgrThreadProc_is 
				 int											index_debugInfo;					//  debugInfo index, debugInfo 2008/11/19

				 //
				 unsigned  int									uiChannelType;						//  2008/04/17, 
				 //
				 unsigned  int									uiChannelType_input;				//  2017/10/03

				 //
				 struct											{
					 BT_grp_mems								grpMems;
				 }												bt;

				 //
				 struct											{
					 unsigned  int								sn_output_talk;
					 //
					 bool										bRecvCancel;
					 //
				 }												dbg;

				 //
				 unsigned  int									lenInBytes;
				 //
				 MIS_MSG_routeTalkData							data;								//  sizeof(  data  ),  offsetof(  ,  data  )  +  offsetof(  MIS_MSG_TALKDATA,  buf  )  +  bufLen
}		 MIS_MSG_TALK, MIS_MSG_INPUT, MIS_MSG_TASK, MIS_MSG_REQ;	

//  msgTalk. 2008/03/31
//
#define		MACRO_memset_misMsgTalk(  pMsgTalk  )	memset(  (  pMsgTalk  ),  0,  offsetof(  MIS_MSG_TALK,  data  )  +  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  sizeof(  unsigned  int  )  );
#define		MACRO_memset_misMsgInput(  pMsgInput  )	memset(  (  pMsgInput  ),  0,  offsetof(  MIS_MSG_INPUT,  data  )  +  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  sizeof(  unsigned  int  )  );
#define		MACRO_memset_misMsgTask(  pMsgTask  )	memset(  (  pMsgTask  ),  0,  offsetof(  MIS_MSG_TASK,  data  )  +  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  sizeof(  unsigned  int  )  );
#define		MACRO_memset_misMsgReq(  pMsgReq  )	memset(  (  pMsgReq  ),  0,  offsetof(  MIS_MSG_REQ,  data  )  +  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  sizeof(  unsigned  int  )  );
//
//  MIS_MSGU
#define		MACRO_memset_misMsg(  pMsg  )	memset(  (  pMsg  ),  0,  offsetof(  MIS_MSG_TALK,  data  )  +  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  sizeof(  unsigned  int  )  );




//
typedef  struct  __misMsgGrpMemHead_t							{
				 unsigned  int									uiPos;					//  buf buf  +  uiPos
}		 MIS_MSG_grpMemHead;


typedef  struct  __misMsgGrpMemData_t							{

				 unsigned  int									uiMsgType;				//  

				 unsigned  char									ucFlg;		
				 unsigned  short								usCode;
				 time_t											tStartTime;
				 unsigned  int									uiTranNo;

				 QY_MESSENGER_ID								idInfo_from;			//	2009/09/11

				 ROUTE_DEBUG_INFO								debugInfo;

				 unsigned  int									lenInBytes;

				 char											buf[1];
}		 MIS_MSG_grpMemData;

//
#define		CONST_misMsg_grpMems								128	* 5					//  Ó¦¸Ã  <  CONST_uiMaxQNodes_perSocketContextOutputQ

//
//  MIS_MSG_TALK, nPos
//  misMsgGrp offsetof(  MIS_MSG_GRP,  buf  )  +  uiBufSize
//  Ãoffsetof(  MIS_MSG_GRP,  buf  )  +  lenInBytes
//  uiBufSize, var.cfg.uiBufSize_msgGrpData
//
typedef  struct  __misMsgGrp_t									{						//  2008/05/27
				 MACRO_misMsg_common
				 
				 //  2015/08/19
				 BOOL											bNeedActiveSession;
				 struct											{
					 unsigned  int								uiCliIndex;				//  input daemon  //  2008/01/05, vDev_coms uiCliIndex com																				
					 unsigned  int								uiSessionId;
				 }												activeSession;

				 //
				 unsigned  int									uiStep;					//  2008/04/28
				 TCHAR											tmpHint[48];			//  2015/08/18. 在集包时提供一点提示
				 unsigned  char									ucbShowHint;			//  2015/09/01
				 //
				 struct											{
					 //
					 QY_MESSENGER_ID							idInfo_grp;
					 QY_MESSENGER_ID							idInfo_upper;		//  2021/05/16
					 //					
					 BT_grp_mems								grpMems;
				 }												bt;

				 //
				 unsigned  char									ucFlg;					//  ucFlg route
				 unsigned  short								usCode;					//  
				 time_t											tStartTime;
				 unsigned  int									uiTranNo;

				 //
				 time_t											tStartTime_processed;	//  mgr iocp uiTranNo_mgr iocp
				 unsigned  int									uiTranNo_processed;
				 unsigned  int									nTimes_tryToSend;		//  mgr iocp 

				 unsigned  int									uiChannelType;			//  2008/04/17, media

				 MSG_ROUTE										route;
				 //
				 unsigned  short								usCnt;
				 MIS_MSG_grpMemHead								memDataHeads[CONST_misMsg_grpMems];

				 unsigned  int									lenInBytes;

				 //
				 char											buf[1];

				 //
}		 MIS_MSG_GRP;

#define		MACRO_memset_misMsgGrp(  pMsg  )	memset(  (  pMsg  ),  0,  offsetof(  MIS_MSG_GRP,  buf  )  );




///////////////////////////////////////////
//

//  ´«ËÍÎÄ¼þµÄ×´Ì¬, 2007/07/17
typedef  struct  __myTransferFileStatus_t						{									//  robotÓÃÀ´¸ø½çÃæ·¢ÏûÏ¢£¬ÈÃ½ØÃæÏÔÊ¾ÎÄ¼þ·¢ËÍµÈ¹ý³Ì, 2007/07/17
				 unsigned  char									ucPercent;
				 unsigned  __int64								ui64Len_recvd;						//  ÊÕµ½µÄ×Ö½ÚÊý¡£ 2008/10/25
				 WCHAR											fileName[256  +  1];
				 WCHAR											fullFilePath[MAX_PATH  +  1];
}		 myTRANSFER_FILE_STATUS;

typedef  struct  __myNotification_t								{									//  2010/07/21
				 QY_MESSENGER_ID								idInfo_from;
				 WCHAR											tBuf[128];
}		 myNOTIFICATION;

typedef  struct  __misMsgTaskStatus_t							{									//  2007/07/17
				 MACRO_misMsg_common
				 //
				 void								*			pMisCnt;
				 QY_MESSENGER_ID								idInfo_logicalPeer;
				 //
				 QY_MESSENGER_ID								idInfo_taskSender;		
				 //QY_MESSENGER_ID								idInfo_taskReceiver;	
				 //
				 QY_MESSENGER_ID								idInfo_mem;
				 //
				 BOOL											bImGrpMem;				

				 unsigned  short								cmdCode;
				 time_t											tStartTime;							//  2009/10/18
				 unsigned  int									uiTranNo;							//  2009/10/18
				 unsigned  int									uiContentType;
				 int											iTaskId;
				 unsigned  int									uiTaskType;							//  2007/07/22
				 int											iStatus;

				 //
				 time_t											tStartTime_processed;				//  2011/03/10

				 //
				 unsigned  char									ucbNeeded_applyForOrgReq;			//  2010/07/21
				 //
				 unsigned  char									ucbFound;							//  2014/11/21
				 //
				 unsigned  char									ucbNotification;					//  2010/07/21

				 //
				 union											{
                     myTRANSFER_FILE_STATUS						transferFileStatus;
					 myNOTIFICATION								notification;						//  2010/07/21
				 }												u;

}		 MIS_MSG_TASKSTATUS,  MIS_MSG_taskStatus;	

#ifndef  __WINCE__

//
#define		CONST_cntof_logMsgContent							512

//
typedef  struct  __imMsgRcd_t									{
		
				 int											id;

				 TCHAR											misServName[CONST_maxMisServNameLen  +  1];
				 QY_MESSENGER_ID								idInfo_send;
				 TCHAR											senderDesc[255  +  1];
				 //
				 time_t											tSendTime;
				 unsigned  int									uiTranNo;
				 unsigned  short								usSeqNo;
				 //
				 QY_MESSENGER_ID								idInfo_logicalPeer;
				 //
				 int											iTaskId;
				 //	
				 time_t											tStartTime_serv;
				 unsigned  int									uiSerialNo;
				 //
				 QY_MESSENGER_ID								idInfo_recv;
				 TCHAR											receiverDesc[255  +  1];
				 int											iRole;
				 //										
				 __int64										tRecvTime;
				 unsigned  short								usRespCode;
				 //
				 unsigned  int									uiType;
				 //
				 QY_MESSENGER_ID								idInfo_initiator;
				 //
				 unsigned  __int64								ui64FileLen;
				 unsigned  int									uiSizePerSnd_suggest;
				 //
				 TCHAR											logMsgContent[CONST_cntof_logMsgContent];
				 //
				 TCHAR											content[256];		// [2048] ;
				 TCHAR											txtContent[256];	// [2048] ;
				 //
				 time_t											firstTime;
				 time_t											lastTime;
				 int											iStatus;
				 time_t											tLastModifiedTime;

}		 IM_MSG_RCD; 

#else

typedef  struct  __imMsgRcd_t									{
		
				 int											id;

				 TCHAR											misServName[1];
				 QY_MESSENGER_ID								idInfo_send;
				 TCHAR											senderDesc[32  +  1];
				 //
				 time_t											tSendTime;
				 unsigned  int									uiTranNo;
				 unsigned  short								usSeqNo;
				 //	
				 time_t											tStartTime_serv;
				 unsigned  int									uiSerialNo;
				 //
				 QY_MESSENGER_ID								idInfo_recv;
				 TCHAR											receiverDesc[32  +  1];
				 int											iRole;
				 //										
				 __int64										tRecvTime;
				 unsigned  short								usRespCode;
				 //
				 unsigned  int									uiType;
				 //										
				 TCHAR											content[512];
				 TCHAR											txtContent[1];
				 //
				 time_t											firstTime;
				 time_t											lastTime;
				 int											iStatus;
				 time_t											tLastModifiedTime;

}		 IM_MSG_RCD; 

#endif


typedef  struct  __misMsgImMsgRcd_t								{						//  2007/08/12
				 MACRO_misMsg_common
				 //
                 IM_MSG_RCD										rcd;
}		 MIS_MSG_imMsgRcd;

typedef  struct  __misMsgImEvent_t								{						//  2007/09/13
				 MACRO_misMsg_common
				 //
				 QIS_EVENT										event;
}		 MIS_MSG_EVENT;



typedef  struct  __misMsgTalkingFriend_qmc_t					{
				 MACRO_misMsg_common
				 //
				 HWND											hWnd;
				 //  
				 MSGR_ADDR										addr;
				 //
}		 MIS_MSG_TALKINGFRIEND_QMC;	


//////////////////

typedef  struct  __param_send_t									{
				 int											iUnused;
}		 PARAM_send;


typedef  struct  __misMsgSend_t									{
				 MACRO_misMsg_common

				 //
				 unsigned  int									uiCliIndex;

				 //
				 PARAM_send										param;
}		 MIS_MSG_send;


//  2015/08/21
typedef  struct  __param_sendFinished_t							{
				 QY_MESSENGER_ID								idInfo;					//  mgr

				 //
				 bool											bSubQ;					//  是否放入subQ
				 QY_MESSENGER_ID								idInfo_from;			//  subQ的idInfo
				 int											index_subQ;				//  是哪个subQ

				 //
				 DWORD											dbg_dwTickCnt;			//  2015/08/21

				 //
				 bool											bTrace;
				 int											dbg_sn;

}		 PARAM_sendFinished;



typedef  struct  __misMsgSendFinished_t							{
				 MACRO_misMsg_common
				 unsigned  int									uiCliIndex;
				 unsigned  int									uiSessionId;
				 //
				 unsigned  int									uiChannelType;
				 //
				 PARAM_sendFinished								param;
				 //
}		 MIS_MSG_sendFinished;



typedef  struct  __misMsgIsSendOk_t								{						//  ÓÉMgrÀ´·¢¸øiocp, ÎÊiocpµÄ´Ë°üÊÇ·ñ´¦Àíµ½ÁË¡£iocp°Ñ°üµÄuiTranNo_mgr·¢»Ø¡£MGRÊÕµ½ºó£¬ÔÚoutputQÀï£¬½«È¥³ýuiTranNo_mgr¶ÔÓ¦µÄÊý¾Ý°ü
				 MACRO_misMsg_common
				 unsigned  int									uiTranNo_mgr;
}		 MIS_MSG_isSendOk;


//  2015/08/24
typedef  struct  __param_sendOk_t								{
				 QY_MESSENGER_ID								idInfo;
				 //
				 DWORD											dbg_dwTickCnt;			//  2015/08/21

}		 PARAM_sendOk;

//
typedef  struct  __misMsgSendOk_t								{							//  iocp Mgr,
				 MACRO_misMsg_common
				 unsigned  int									uiChannelType;				//  2007/07/08
				 //  unsigned  int								uiCliIndex;
				 //  unsigned  int								uiSessionId;				//  
																							//  
				 unsigned  int									uiTranNo_mgr;
				 //
				 PARAM_sendOk									param;
				 //
				 void									*		pQMem1;
}		 MIS_MSG_sendOk;


//  2015/08/26
typedef  struct  __param_chkChannel_t							{
	
				 QY_MESSENGER_ID								idInfo;

}		 PARAM_chkChannel;



//  2007/12/20
typedef  struct  __misMsgChkChannel_t							{
				 MACRO_misMsg_common
				 //
				 unsigned  int									uiChannelType;				//  
				 //
				 PARAM_chkChannel								param;
}		 MIS_MSG_chkChannel;







//  2015/08/24
typedef  struct  __param_inputArrive_t							{
				 QY_MESSENGER_ID								idInfo;

				 //
				 BOOL											bCsData;

				 //
				 DWORD											dbg_dwTickCnt;
}		 PARAM_inputArrive;

typedef  struct  __misMsgInputArrive_t							{
				 MACRO_misMsg_common					 
				 //				 				 
				 unsigned  int									uiCliIndex;
				 unsigned  int									uiSessionId;				//  

				 //
				 unsigned  int									uiChannelType;				//  uiChannelType
				 //
				 PARAM_inputArrive								param;

}		 MIS_MSG_inputArrive;



//  2015/08/21
typedef  struct  __param_processSelf_t							{
				 void								*			pQMem;						//  mgr

				 //
				 BOOL											bCsData;					//  2015/09/01

				 //
				 DWORD											dbg_dwTickCnt;				//  2015/08/21

}		 PARAM_processSelf;
//
typedef  struct  __misMsgProcessSelf_t							{		
				 MACRO_misMsg_common
				 //
				 unsigned  int									uiChannelType;				//  uiChannelType
				 //
				 //  void							*			pQMem;						//  mgr
				 PARAM_processSelf								param;
}		 MIS_MSG_processSelf;



//  2011/04/19
typedef  struct  __param_processBt_t							{
				 //void								*			pQMemGrp;					//  mgr
				 void								*			pQMem;						//  mgr
				 
				 //  2021/05/16
				 //QY_MESSENGER_ID								idInfo_bt_upper1;

				 //
				 bool											bForce_postMsg;

				 //
}		 PARAM_processBt;

//
typedef  struct  __misMsgProcessBt_t							{
				 MACRO_misMsg_common
				 //
				 unsigned  int									uiChannelType;				//  uiChannelType
				 PARAM_processBt								param;
}		 MIS_MSG_processBt;


//
typedef  struct  __misMsgApplyForWork_t							{
				 MACRO_misMsg_common
				 //
				 unsigned  int									uiContentType;
				 //
				 unsigned  int									uiToBeDelMsgIndex;			//  2008/01/08, vDevComs

				 //
				 time_t											tStartTime_processed;		//  2011/03/10

}		 MIS_MSG_applyForWork;


//
//

//
//  2011/01/12
#if  0
typedef  struct  __misMsg_getDaemonStatus_t						{
				 MACRO_misMsg_common
				 //
				 HWND											hWnd;
				 QMD_status							data;

}		 MIS_MSG_getDaemonStatus;
#endif

//////////////////
//

typedef  struct  __misMsgNeedRegQmc_t							{
				 MACRO_misMsg_common
				 void								*			pMisCnt;					//  mc pMisCnt, qmd uiCliIndex, 2007/06/10
}		 MIS_MSG_NEEDREG_QMC;




/////////////////////


//
typedef  struct  __misMsgRecentFriendQmc_t						{							//  2007/06/05
				 MACRO_misMsg_common
				 //
				 QY_MESSENGER_ID								idInfo;
				 int											iOp;						//  
				 unsigned  int									dwTickCnt_op;				//  
}		 MIS_MSG_RECENTFRIEND_QMC;



//
typedef  struct  __misMsgDisplayRecentFriendsQmc_t				{
				 MACRO_misMsg_common
				 //
				 REFRESH_RECENTFRIENDS_RESP_h						resp;

}		 MIS_MSG_displayRecentFriends_qmc;



//
typedef  struct  __misMsgDisplayedElemQmc_t						{
				 MACRO_misMsg_common
				 //
				 DISPLAYEDELEM_U								elemU;
}		 MIS_MSG_DISPLAYEDELEM_QMC;


/////////////




typedef  struct  __misMsgRefreshContactsStatusQmc_t				{
				 MACRO_misMsg_common
				 //
				 HWND											hWnd;
				 void										*	pMisCnt;
				 REFRESH_RECENTFRIENDS_RESP_h					status;
}		 MIS_MSG_REFRESHCONTACTSSTATUS_QMC;


typedef  struct  __misMsgRefreshMeStatusQmc_t					{								//  
				 MACRO_misMsg_common
				 //
				 HWND											hWnd;
				 void										*	pMisCnt;
				 //  
}		 MIS_MSG_REFRESHMESTATUS_QMC;


typedef  struct  __misMsgApplyForPlayer_qmc_t					{
				 MACRO_misMsg_common
				 //
				 QY_MESSENGER_ID								idInfo_recorder;
				 int											iTaskId;						//  2009/09/17

				 //
				 BOOL											bGps;							//  2012/05/07

				 //
				 bool											bMix;							//  是否混音播放器

				 //
				 struct											{
					 unsigned  int								uiTranNo;						//  2009/04/27
					 //
					 QY_AUDIO_HEADER							ah;								//  2010/06/17

					 AUDIO_PLAY_CFG								playCfg;						//  2009/06/14

				 }												audio;
				 struct											{
					 unsigned  int								uiTranNo;
					 //  
					 QY_VIDEO_HEADER							vh;		
					 //
					 unsigned  short							usFps;							//  2015/02/20

				 }												video;


}		 MIS_MSG_applyForPlayer_qmc;


typedef  struct  __misMsgApplyForChkChannels_qmc_t				{								//  2008/06/01
				 MACRO_misMsg_common
				 //
				 void										*	pMisCnt;
				 
				 //
				 BOOL											bTaskExists;
				 //  BOOL											bTaskNeedRestart;
				 BOOL											bTask_sendLocalAv;				//  2008/10/17, ´æÔÚÐèÒª·¢ËÍ±¾µØavµÄÈÎÎñ

}		 MIS_MSG_applyForChkChannels_qmc;


/*
typedef  struct  __misMsgApplyForRemovingInvalidTasks_qmc_t		{									//  2009/09/10
				 MACRO_misMsg_common
				 //
}		 MIS_MSG_applyForRemovingInvalidTasks_qmc;
*/


//
//  #define		CONST_vwRuleMessengerCmd_dynBmps				3
#define		CONST_vwRuleMessengerCmd_dynBmps					7									//  4  +  3. 2014/05/31

//  2014/05/31
#define		CONST_usIndex_screen0								1
#define		CONST_usIndex_webcam0								1
#define		CONST_usIndex_webcam1								2
#define		CONST_usIndex_webcam2								3
//
#define		CONST_usIndex_avStream_slave						2									//  2014/09/28
//
#define		CONST_usIndex_photomosaic_video						3									//  2014/11/91
#define		CONST_usIndex_photomosaic_resource					4									//  2014/11/01


//  2014/08/04
typedef  struct  __dynBmpRule_t									{
				 //
				 QIS_res_obj									dynBmp;
				 //
				 TCHAR											name[32];							//  name used to mean device id or unique name for dynBmp
				 TCHAR											cusName[32];						//  cusName used to mean a friendly comment for dynBmp


				 //
				 unsigned  char									ucbSaveVideo;

				 //
				 struct											{
					 unsigned  char								ucbAddedManually;
					 unsigned  int								tn_addedManuall;
				 }												helpInfo;


}		 DYN_BMP_rule,  DYN_BMP_RULE;


//
typedef  struct  __vwRule_messenger_cmd_t						{

				 //
				 unsigned  char									ucbViewGps;							//  2012/04/19

				 //  2014/05/23
				 DYN_BMP_rule									dynBmpRules[CONST_vwRuleMessengerCmd_dynBmps];

				 //
				 struct											{
					 unsigned  int								tn_addedManuall;
				 }												helpInfo;

}		 VW_rule_messengerCmd;

//  2014/05/31
BOOL  tmpF_bViewRemoteVideo(  VW_rule_messengerCmd  *  pCmd,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj,  unsigned  short  usHelp_subIndex  );
int  tmpF_setViewRemoteVideo(  DYN_BMP_RULE  *  pDynBmp,  BOOL  bView,  VW_rule_messengerCmd  *  pCmd  );
int  tmpF_setViewRemoteVideo(  unsigned  int  uiObjType,  unsigned  short  usIndex_obj,  unsigned  char  ucbSaveVideo,  BOOL  bView,  VW_rule_messengerCmd  *  pCmd  );


//  2012/04/23
typedef  struct  __misMsgApplyForTalkerShadow_qmc_t				{
				 MACRO_misMsg_common
				 //
				 HWND											hWall;
				 int											iWndContentType_wall;				//  2012/04/29    
				 unsigned  int									uiVwRuleType;
				 unsigned  int									uiTranNo_zone;
				 VW_rule_messengerCmd							vwRuleCmd;
				 //
				 unsigned  char									ucbRefreshCmd;
				 
				 //
				 QY_MESSENGER_ID								idInfo;
				 HWND											hShadow;

				 //
				 time_t											tStartTime_processed;				//  2011/03/10

}		 MIS_MSG_applyForTalkerShadow_qmc;

///////////////////////////////////

//  2012/04/28
typedef  struct  __paramMsgToShadow_t							{

				 void										*	pDlgMgrVar;

				 //  2017/09/22
				 //void										*	pZoneParam;							//

				 //  
				 unsigned  int									uiTranNo_zone;

				 struct											{
					 //  QY_MESSENGER_ID							idInfo;							//  2009/09/03
					 unsigned  int								uiObjType;							//  2009/09/03
					 unsigned  short							usIndex_obj;
				 }												tmp_dynBmp;

}		 PARAM_msgToShadow;



//  2014/09/23
//  procVide.data will allocate bih.biSizeImage bytes, and biSizeImage may be a larger value. the data must be freed.
typedef  struct  __misMsg_procVideo_qmc_t						{									//  2008/03/18
				 MACRO_misMsg_common	
				 //
				 void										*	pMisCnt;
				 QY_MESSENGER_ID								idInfo_peer;
				 //
#if  0
				 struct											{
						unsigned  __int64						ui64Id;
				 }												idInfo_sender;	
#endif
				 QY_MESSENGER_ID								idInfo_sender;
				 //
				 //
				 unsigned  int									uiTranNo_openAvDev;
				 unsigned  short								usIndex;
				 //
				 int											iTaskId;
				 HWND											hWnd_task;							//  2009/09/14
				 //
				 unsigned  int									uiEventId_lastRecvd_unused;			//  2016/12/26	//  2008/11/22

				 //
				 unsigned  int									uiCapType;
				 int											iIndex_capProcInfo;
				 BITMAPINFOHEADER								bih;

				 //
				 //QY_MEMORY									memory;

				 //  2014/09/23
				 myDRAW_VIDEO_DATA								pkt;

				 //
				 //  int										index_player;						//  2009/10/03
				 PLAYER_ID										playerId;							//  2016/02/18

				 //
				 PARAM_msgToShadow								paramMsgToShadow;					//  2012/04/28

				 //
				 unsigned  char									ucbDisplayAllFrames;				//  2009/07/25

				 //
				 struct											{
					 BOOL										bLocalVideoDisplayedOnPeer;			//  2014/11/15					
					 int										index_capImage_localVideoInMeImages;
				 }												localOnPeer;
				 //
				 struct											{
					 BOOL										bMeDisplayedOnBgWall;				//  2014/11/29
				 }												meOnBgWall;

				 //  
				 M_debugInfo_pktNo																	//  2012/11/09

}		MIS_MSG_procVideo_qmc;



//  2012/04/20
typedef  struct  __misMsg_procGps_qmc_t							{
				 MACRO_misMsg_common

				 //
				 QY_MESSENGER_ID								idInfo_peer;

				 TRANSFER_GPS_DATA								transferGpsData;

}		 MIS_MSG_procGps_qmc;


//
typedef  struct  __misMsg_notifyTaskEnd_qmc_t					{
				 MACRO_misMsg_common
				 //
				 HWND											hWnd;
				 int											iTaskId;
				 BOOL											bToCancel;

				 //
				 time_t											tStartTime_processed;				//  2011/03/10

}		 MIS_MSG_notifyTaskEnd_qmc;





//////////////


typedef  union  __misMsgU_t										{
				unsigned  int									uiType;
				MIS_MSG_RESULT									result;
				MIS_MSG_RESP									resp;
				MIS_MSG_INPUT									input;
				MIS_MSG_REQ										req;
				MIS_MSG_TALK									talk;
				MIS_MSG_TASK									task;						//  2007/07/08
				//
				MIS_MSG_GRP										grp;						//  2008/05/27
				//
				MIS_MSG_inputArrive								inputArrive;				//  2015/08/24
				MIS_MSG_send									send;						//  2015/09/02
				MIS_MSG_sendFinished							sendFinished;				//  2007/05/30
				MIS_MSG_processSelf								processSelf;				//  2007/05/30
				MIS_MSG_processBt								processBt;					//  2011/04/18
				MIS_MSG_isSendOk								isSendOk;
				MIS_MSG_sendOk									sendOk;
				MIS_MSG_chkChannel								chkChannel;					//  2007/12/20
				MIS_MSG_applyForWork							applyForWork;				//  2007/09/03

				//
				//MIS_MSG_confMgr									confMgr;


				//
				//MIS_MSG_getDaemonStatus							getDaemonStatus;			//  2011/01/12


				//
				MIS_MSG_TASKSTATUS								taskStatus;					//  2007/07/17
				MIS_MSG_imMsgRcd								imMsgRcd;					//  2007/08/12
				MIS_MSG_EVENT									event;
				
				//
				MIS_MSG_NEEDREG_QMC								needReg_qmc;
				
				//
				MIS_MSG_TALKINGFRIEND_QMC						talkingFriend_qmc;
				MIS_MSG_RECENTFRIEND_QMC						recentFriend_qmc;
				MIS_MSG_DISPLAYEDELEM_QMC						displayedElem_qmc;			//  2007/06/10
				MIS_MSG_REFRESHCONTACTSSTATUS_QMC				refreshContactsStatus_qmc;
				MIS_MSG_REFRESHMESTATUS_QMC						refreshMeStatus_qmc;		//  2007/06/20
				MIS_MSG_applyForPlayer_qmc						applyForPlayer_qmc;			//  2008/05/09
				MIS_MSG_applyForChkChannels_qmc					applyForChkChannels_qmc;	//  2008/06/01
				//MIS_MSG_applyForRemovingInvalidTasks_qmc		applyForRemovingInvalidTasks_qmc;		//  2009/09/10
				MIS_MSG_applyForTalkerShadow_qmc				applyForTalkerShadow_qmc;	//  2012/04/23
				//
				MIS_MSG_displayRecentFriends_qmc				displayRecentFriends_qmc;

				//
				MIS_MSG_procVideo_qmc							procVideo;					//  2009/03/24
				MIS_MSG_procGps_qmc								procGps;					//  2012/04/20
				//
				MIS_MSG_notifyTaskEnd_qmc						notifyTaskEnd;				//  2009/04/28
				


				//
}		 MIS_MSGU;



#define		CONST_maxTimeoutInS_sendMsg_is						20							//  2007/12/09, 
//#define		CONST_maxSendMsgs_is								20  *  10					//  2015/09/04  //20							//  2007/12/09, iocp
#define		CONST_maxSendMsgs_isClient							40							//  2007/12/09, iocp


//
#define		MAX_outputQ2Nodes_toPostQ							40							//  must < CONST_uiMaxQNodes_outputQ



  


/////////////////////////////////


#ifdef  __DEBUG__
	    #define		CONST_usMaxIntervalIsSBetweenWebSessions		300
#else
	    #define		CONST_usMaxIntervalIsSBetweenWebSessions		40
#endif

#define		CONST_usIntervalInSBetweenWebSessions					15

//
#define		DEFAULT_usTimeoutInMsToSwitch_isMgr						1500	//3000	//  1000								//  2008/10/28

//
#define		DEFAULT_usTimeoutInMsToSwitch_isClient					3000	//  2000								//  2008/10/28
#define		DEFAULT_usTimeoutInMsToSwitch_rt_isClient				3000	//  2000								//	2009/06/07从100调整为200，//  2008/10/28
#define		DEFAULT_usTimeoutInMsToSwitch_file_isClient				10000	//  3000

//
#define		DEFAULT_usMaxMsgs_allowedToSwitchToTalkChannel_robot	8									//  2009/04/02
#define		DEFAULT_usMaxMsgs_allowedToSwitchToTalkChannel_media	1									//  2009/04/02

#define		MAX_usMaxMsgs_allowedToSwitchToTalkChannel				10									//  2009/04/02
#define		MIN_usMaxMsgs_allowedToSwitchToTalkChannel				1



//



//
//
typedef  struct  __mcuPolicy_t {
				 unsigned  char  ucHardwareAccl;
}  MCU_policy;

//
extern  QY_DMITEM  CONST_hdAccl_table[];

//
int getMcuPolicy( TCHAR * rootKey_qnmScheduler, LPCTSTR  smCfgFile,  MCU_policy * p );


//

//
typedef  struct  __policyIsMgr_t								{
				unsigned  char									ucbLogImMsg;							//  £2007/09/12
				//
				QY_MESSENGER_ID									startMcuIdInfo;
				unsigned  short									usMaxCnt_mcus;
				//
				TCHAR											mcuUsrName[128];
				char											mcuPasswd[128];
				TCHAR											mcuDomainName[128];

				//			
				MCU_policy	mcuPolicy;

				//
				bool											bUseManuallySetResServId;
				QY_MESSENGER_ID									idInfo_manuallySetResServ;

				//
				QY_MESSENGER_ID									startTmpMessengerId;							//  2007/11/23
				unsigned  int									uiMaxCnt_tmpMessengers;
				//
				unsigned  short									usMaxIntervalIsSBetweenWebSessions;				//  2007/12/11, 
				unsigned  short									usIntervalInSBetweenWebSessions;				//  
				//
				unsigned  short									usTimeoutInMsToSwitch;							//  2008/10/28, media realTimeMedia daemon 
				//
				unsigned  short									usMaxMsgs_allowedToSwitchToTalkChannel_robot;	//  2009/04/02
				unsigned  short									usMaxMsgs_allowedToSwitchToTalkChannel_media;	//  2009/04/02
				//
				unsigned  int									uiCommEncCtxType;								//  2008/06/09
				//

				unsigned  char									ucbUseDynBmpRule;								//  2009/09/17

				//  2015/07/28
				//unsigned  char									ucbNotUseP2pCall;							//  不允许单对单的呼叫。当需要对视频进行统一管理时，此标志位可以禁止单对单的呼叫（分组靠设置分组管理员来实现)

				//  2015/08/01
				//QY_MESSENGER_ID									idInfo_resServ;								//  用来存放通知和离线文件的msgrId
				TCHAR											resServDir[MAX_PATH  +  1];

				//
				unsigned  int									uiSizePerSnd_media;								//  2011/01/30

				//
				bool											bChannelRedirect;								//  在对应通道不通时，是否把包重定向到talk通道

}		 POLICY_isMgr;


//  2015/08/21
typedef  struct  __sys_param_isMgr_t								{
				 unsigned  short									usCliThreads;					//  2015/08/23
				 unsigned  short									usMgrThreads_cs;				 
				 unsigned  short									usMgrThreads_route;		
				 unsigned  short									usMgrThreads_switch_route;		//  2015/09/03
}		 SYS_param_isMgr;


//////////////////////////////////////////////

//  
#define		CONST_imTaskType_null								0
//
#define		CONST_imTaskType_sendFile							11
#define		CONST_imTaskType_recvFile							12
//
//#define		CONST_imTaskType_avSetup							15
//  #define		CONST_imTaskType_listening							16
//#define		CONST_imTaskType_avCall								17			//  ºóÃæÓ¦¸Ã¸úÒ»¸öÄ¿µÄIP
//#define		CONST_imTaskType_whiteboard							18			//  
//#define		CONST_imTaskType_appCall							19			//  
//
#define		CONST_imTaskType_transferAvInfo						25			//  
#define		CONST_imTaskType_shareScreen						26			//  2008/10/06
#define		CONST_imTaskType_remoteAssist						27			//  2008/11/10
#define		CONST_imTaskType_shareMediaFile						28			//  2009/04/23
#define		CONST_imTaskType_shareDynBmp						29			//  2009/08/21
#define		CONST_imTaskType_viewDynBmp							30			//  2009/09/07
#define		CONST_imTaskType_queryCustomerServiceOfficer		31			//  2011/04/06




//	extern  QY_DMITEM  CONST_imTaskTypeTable[];			




//
//




typedef  struct  __imTaskRcd_t									{

				 int											id;

				 TCHAR											misServName[CONST_maxMisServNameLen  +  1];
				 QY_MESSENGER_ID								idInfo_send;			//  ·¢ËÍÈË
				 TCHAR											senderDesc[64  +  1];
				 //
				 time_t											tSendTime;				//  ·¢ËÍÊ±¼ä
				 unsigned  int									uiTranNo;				//  ·¢ËÍµÄ½»Ò×ºÅ 
				 unsigned  short								usSeqNo;
				 //

				 unsigned  int									uiContentType;			//  ·¢Æð·½µÄÇëÇóµÄÄÚÈÝÀàÐÍ
				 //

				 time_t											tStartTime_serv;		//  È±Ê¡¿ÉÌî"", ÔÚÌÖÂÛ×éÊ±ÓÐÓÃ
				 unsigned  int									uiSerialNo;				//  È±Ê¡Îª0£¬ÔÚÌÖÂÛ×éÀ´·¢ËÍÊ±£¬Ó¦Ê¹ÓÃtServTimeºÍuiSerialNoÀ´±£Ö¤Ë³ÐòºÍÒ»Ð©ÈÎÎñµÄ²»¿É·Ö¸îÐÔ¡£
				 //
				 QY_MESSENGER_ID								idInfo_recv;			//  ½ÓÊÕ·½  
				 TCHAR											receiverDesc[64  +  1];
				 int											iRole;
				 //
				 time_t											tRecvTime;				//  ½ÓÊÕÊ±¼ä
				 unsigned  short								usRespCode;				//  Í¨ÐÅµÄÏìÓ¦Âë
				 //
				 //
				 int											ibReply;				//  ÊÇ·ñ»Ø¸´
				 //
				 unsigned  int									uiType;					//  ÈÎÎñÀàÐÍ£¬±ÈÈç£ºÎÄ¼þ´«ËÍ, ÓÃqyCmd_sendTaskÖÐµÄimCommTypeÀ´±£´æ¾Í¿ÉÒÔÁË
																						//  2008/05/29, Õâ¸öuiTypeÓÃ´¦²»ÊÇºÜ´ó¡£ÒòÎªÒ»¸öÈÎÎñÒÑ¾­ÓÃidStr_send, tSendTime, uiTranNo À´¾ö¶¨ÁË¡£
																						//  ¹¤×÷ÄÚÈÝÓÃuiContentType¾ö¶¨ÁË¡£messengerµÄ½ÇÉ«ÓÃÊÇ²»ÊÇidStr_sendÒÑ¾­¾ö¶¨ÁË¡£
																						//  Õâ¸ö±äÁ¿£¬¸üÏóÒ»¸ö±ãÓÚ´¦ÀíµÄËµÃ÷ÐÔ±äÁ¿¡£
																						
				 //
				 unsigned  int									uiMode;					//  Ð­Í¬Ä£Ê½,//  Ð­Í¬Ä£Ê½£¬±È·½£ºÁôÑÔ£¬Í¨Öª£¬Òª»Ø¸´µÄÍ¨Öª£¬¿ÉÈ¡ÏûºÍÐÞ¸ÄµÄÍ¨Öª£¨Ö»ÄÜÔÚÏßÌá½»×´Ì¬£©
				 //				 
				 TCHAR											subTypeStr[64];			//  ×Ô¶¨ÒåÈÎÎñÀàÐÍ. Ò»°ãÍ¨Öª, ½ô¼±Í¨Öª, ·Å¼ÙÍ¨Öª. »Ø¸´ÀàÐÍÖ¸ ÖªµÀ¡£¾Ü¾ø¡£µÈ´ý¡£¡£¡£
				 //
				 TCHAR											subject[128];			//  Ö÷Ìâ
				 TCHAR											content[256];			//  ÏêÏ¸ÄÚÈÝ£¬ÒÔºó½«Öð½¥¿¼ÂÇÈçºÎ½«Êý¾ÝÓÐÐ§µÄ·ÖÉ¢µ½Èô¸É¸ö±íÖÐ×Ö¶ÎµÄÎÄ¼þ¡£ÒòÎª²»Í¬µÄÊý¾Ý¿âµÄ×Ö¶Î³¤¶È²»Í¬¡£²»¹ý£¬·Ö¶Î´æ´¢Ò²»áÔì³É²éÑ¯²»·½±ã¡£
				 TCHAR											txtContent[1];		//  Ô­Êý¾Ý°üÄÚÈÝ
				 //
				 int											ibNeedReply;			//  ÊÇ·ñÐèÒª»Ø¸´
				 time_t											tEndTime;				//  ½ØÖ¹Ê±¼ä
				 //
                 TCHAR											issuer[32];				//  ·¢²¼ÈË
				 time_t											tIssueTime;				//  ·¢²¼Ê±¼ä

				 //
				 time_t											tStartTime_req;			//  ¶ÔÏìÓ¦Ê±µÄÇëÇó°üµÄ¶ÔÓ¦Öµ
				 unsigned  int									uiTranNo_req;
				 //
				 time_t											firstTime;
				 time_t											lastTime;
				 int											iStatus;				//  Ö´ÐÐµÄ×´Ì¬£¬±ÈÈç£ºÎ´ÔÄ£¬ÒÑÔÄ£¬ÒÑ»Ø¸´
				 time_t											tLastModifiedTime;		//  ×îºóÖ´ÐÐ¶¯×÷µÄ·¢ÉúÊ±¼ä
				 //
				 QY_MESSENGER_ID								idInfo_auditor;			//  ÉóºËÈË
				 QY_MESSENGER_ID								idInfo_replyTo;			//  Çë»Ø¸´ÖÁ
				 //
				 int											iProps[10];
				 TCHAR											propStrs[10][32];			
				 //

}		 IM_TASK_RCD;




typedef  struct  __phoneGuestRcd_t								{

				 int											id;
				 TCHAR											misServName[CONST_maxMisServNameLen  +  1];
				 unsigned  int									uiDevType;
				 TCHAR											wDevIdStr[128  +  1];
				 //
				 TCHAR											messengerPasswd[255  +  1];
				 //
				 QY_MESSENGER_ID								idInfo_owner;
				 //
				 int											iStatus;
				 //																				
				 time_t											startTime;
				 time_t											tLastModifiedTime;
				 
}		 PHONE_GUEST_RCD;
				 

typedef  struct  __qyMessengerPhoneInfo_t							{

				 int											id;
				 TCHAR											misServName[CONST_maxMisServNameLen  +  1];
				 unsigned  int									uiDevType;
				 TCHAR											wDevIdStr[128  +  1];
				 //
				 TCHAR											messengerPasswd[255  +  1];
				 //
				 QY_MESSENGER_ID								idInfo;
				 //
				 int											iStatus;
				 //																				
				 time_t											startTime;
				 time_t											tLastModifiedTime;
				 
}		 QY_MESSENGER_phoneInfo;





//  2007/07/09
//
#define		CONST_imOp_null										0
#define		CONST_imOp_says										1		//  
#define		CONST_imOp_tryToSendFile							2		//  
//
#define		CONST_imOp_recv_accept								101		//  
#define		CONST_imOp_recv_deny								102		//  

#define		CONST_imOp_recvFile_saveas							103
//
#define		CONST_imOp_recv_cancel								104		//  
#define		CONST_imOp_send_cancel								106		//  
#define		CONST_imOp_send_permit								107		//  
//
#define		CONST_imOp_dual_permit								120		//  2008/05/29
//
#define		CONST_imOp_recv_applyForOrgReq						123		//  2009/10/18
#define		CONST_imOp_recv_applyForChkTaskAlive				124		//  2009/10/19
#define		CONST_imOp_recv_applyForKeyFrame					125		//  2014/08/26
//
#define		CONST_imOp_ping										126
#define		CONST_imOp_applyForConf								127
// 
//
#define		CONST_imOp_requestToSpeak							130		//  2009/02/21. 自己申请发言
#define		CONST_imOp_stopSpeaking								131		//  2009/02/21. 自己停止发言
//
#define		CONST_imOp_permitToSpeak							132		//  2017/07/07.
#define		CONST_imOp_prohibitSpeaking							133		//  2017/07/07. 
//
#define		CONST_imOp_requestToControlDesktop_yz				134		//  2017/08/26
#define		CONST_imOp_stopControlDesktop_yz					135
//
#define		CONST_imOp_pleaseSpeak								136		//  主持人邀请发言
#define		CONST_imOp_pleaseStopSpeaking						137		//  主持人请停止发言

//
#define		CONST_imOp_setCompere								140
//
#define		CONST_imOp_sendStreamInfo							141		//  2023/05/04


//
#define		CONST_imOp_requestToSend							180		//  2014/10/09
#define		CONST_imOp_stopSending								181		//  2014/10/09

//
#define		CONST_imOp_new										190		//  2017/07/29
#define		CONST_imOp_refresh									191
#define		CONST_imOp_del										192
#define		CONST_imOp_modify									193		//  2018/11/20


//
#define		CONST_imOp_enlargeImg								200
#define		CONST_imOp_enlargeChannel							201
#define		CONST_imOp_setOneBig								202

#define		CONST_imOp_videoTop									210
#define		CONST_imOp_videoBottom									211
#define		CONST_imOp_videoLeft									212
#define		CONST_imOp_videoRight									213

#define		CONST_imOp_loseSel										214

#define		CONST_imOp_cancelSel								215

#define		CONST_imOp_phone_enlargeImg								220
#define		CONST_imOp_phone_cancelEnlargeImg							221

#define		CONST_imOp_phone_respCurr							225

#define		CONST_imOp_respChannel								230


//
#define		CONST_imOp_openFile									301		//  
//
#define		CONST_imOp_myMax									10000	//  
//

extern  QY_DMITEM  CONST_imOpTable_en[];



//
#define		CONST_iAllocType_msg								(  CONST_iAllocType_user  +  1  )
#define		CONST_iAllocType_audio								(  CONST_iAllocType_user  +  2  )
#define		CONST_iAllocType_video								(  CONST_iAllocType_user  +  3  )
#define		CONST_iAllocType_longTimeMsg						(  CONST_iAllocType_user  +  4  )



//
extern QY_DMITEM  CONST_procOfflineResSubtypeTable[];





//
int  getCurMaxMessengerId(  void  *  pDb,  QY_MESSENGER_ID  *  pIdInfo  );	
int  getNextMessengerId(  void  *  p0,  void  *  pDb,  QY_MESSENGER_ID  *  pLastIdInfo,  char  *  idStrBuf,  unsigned  int  size  );



QY_MESSENGER_ID  *  idStr2Info(  char  *  idStr,  QY_MESSENGER_ID  *  pIdInfo  );
char  *  idInfo2Str(  QY_MESSENGER_ID  *  pIdInfo,  char  *  idStr,  unsigned  int  size  );

//
int getSeg(char* pData, char* seg, int segSize);
__int64 geti64Val(char* str, char* tag);


//
BOOL  bMessengerIdValid(  QY_MESSENGER_ID  *  pIdInfo  );
BOOL  bMessengerIdStrValid(  char  *  idStr  );

//
BOOL  bMessengerGuest(  unsigned  int  uiObjType  );

//
//  int  filterStream_is(  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  void  *  p2  );
int  filterStream_is(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

//
int  commAuthInfo2Stream_mis(  QY_COMM_AUTHINFO_MIS  *  pAuthInfo,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2CommAuthInfo_mis(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );
//
int  authResp2Stream_mis(  unsigned  int  uiStreamId,  AUTH_RESP_MIS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
//  int  tmpHandler_stream2AuthResp_mis(  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  void  *  p2  );
int  tmpHandler_stream2AuthResp_mis(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );

//
int  chkLogonIdReq2Stream(unsigned  int  uiStreamId, ChkLogonIdReq* pReq, char* buf, unsigned  int* uiBufSize);
int  tmpHandler_stream2ChkLogonIdReq(CTX_stream2Data* pCtx, void* p0, void* p1, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem);


//
int  msgRoute2Stream(  unsigned  int  uiStreamId,  MSG_ROUTE  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2MsgRoute(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );
//
int  imHtmlContent2Stream(  unsigned  int  uiStreamId,  IM_HTML_CONTENT  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2ImHtmlContent(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );
//
int  rtcCallReq2Stream(  unsigned  int  uiStreamId,  RTC_CALL_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RtcCallReq(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );
//
int  qyhtonVideoHeader(  QY_VIDEO_HEADER  *  pVh  );
int  qyntohVideoHeader(  QY_VIDEO_HEADER  *  pVh  );
int  qyhtonAudioHeader(  QY_AUDIO_HEADER  *  pAh  );
int  qyntohAudioHeader(  QY_AUDIO_HEADER  *  pAh  );

//
int  tmp_htonTranAudio(  TRAN_audio  *  pTranAudio,  char  **  ppBuf,  unsigned  int  *  puiBufSize  );
int  tmp_htonTranVideo(  TRAN_video  *  pTranVideo,  char  **  ppBuf,  unsigned  int  *  puiBufSize  );


//
int  tmp_htonAvTranInfo(  AV_TRAN_INFO  *  pTranInfo,  char  **  ppBuf,  unsigned  int  *  puiBufSize  );
int  tmp_ntohAvTranInfo(  QY_CFGITEM_ntoh_U  *  pItem,  AV_TRAN_INFO  *  pTranInfo,  BOOL  *  pbProcessed  );

//
int  tmp_htonAvStream(  AV_stream  *  pObj,  char  **  ppBuf,  unsigned  int  *  puiBufSize  );
int  tmp_ntohAvStream(  QY_CFGITEM_ntoh_U  *  pItem,  AV_stream  *  pObj,  BOOL  *  pbProcessed  );

//
int  tmp_htonConfHgInfo(CONF_hg_info* pReq_hgInfo, char** ppBuf, unsigned  int* uiBufSize);
int  tmp_ntohConfHgInfo(QY_CFGITEM_ntoh_U* pItem, CONF_hg_info* pContent, BOOL* pbProcessed);




//
int  transferAvInfo2Stream(  unsigned  int  uiStreamId,  TRANSFER_AV_INFO  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferAvInfo(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );
//
int  transferAvReplyInfo2Stream(  unsigned  int  uiStreamId,  TRANSFER_AV_replyInfo  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferAvReplyInfo(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );
//
int  transferVideoData2Stream(  unsigned  int  uiStreamId,  TRANSFER_VIDEO_DATA  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferVideoData(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );
//
int  transferVideoDataResp2Stream(  unsigned  int  uiStreamId,  TRANSFER_VIDEO_dataResp  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferVideoDataResp(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );
//


int  transferAudioData2Stream(  unsigned  int  uiStreamId,  TRANSFER_AUDIO_DATA  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferAudioData(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  transferAudioDataResp2Stream(  unsigned  int  uiStreamId,  TRANSFER_AUDIO_dataResp  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferAudioDataResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

//
int  remoteAssistReq2Stream(  unsigned  int  uiStreamId,  REMOTE_ASSIST_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RemoteAssistReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  taskInteractionReq2Stream(  unsigned  int  uiStreamId,  TASK_INTERACTION_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TaskInteractionReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  confKey2Stream(  unsigned  int  uiStreamId,  CONF_KEY  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2confKey(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  statusConfLayoutParam2Stream(unsigned  int  uiStreamId, StatusConfLayoutParam* pReq, char* buf, unsigned  int* uiBufSize);

int  tmpHandler_stream2statusConfLayoutParam(CTX_stream2Data* pCtx, void* p0, void* p1, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem);



int  confLayout2Stream(  unsigned  int  uiStreamId,  CONF_LAYOUT  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2confLayout(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

//
int  confNvrInfo2Stream(unsigned  int  uiStreamId, ConfNvrInfo* pReq, char* buf, unsigned  int* uiBufSize);
int  tmpHandler_stream2confNvrInfo(CTX_stream2Data* pCtx, void* p0, void* p1, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem);

//
int  confState2Stream(  unsigned  int  uiStreamId,  CONF_state  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2ConfState(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );

//
int  confReq2Stream(  unsigned  int  uiStreamId,  CONF_req  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2ConfReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );

//
int  confCtrlState2Stream(unsigned  int  uiStreamId, CONF_ctrl_state* pReq, char* buf, unsigned  int* uiBufSize);
int  tmpHandler_stream2confCtrlState(CTX_stream2Data* pCtx, void* p0, void* p1, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem);




//
int  refreshWebContactsInfo2Stream(  unsigned  int  uiStreamId,  REFRESH_WEBCONTACTS_INFO  *  pInfo,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RefreshWebContactsInfo(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

//
int  qyVDevComs2Stream(  unsigned  int  uiStreamId,  QY_VDEV_COMS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2QyVDevComs(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  retrieveSmPolicy2Stream(  unsigned  int  uiStreamId,  RETRIEVE_SM_POLICY  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RetrieveSmPolicy(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

//
#if  0
	int  qisIntervalParams2Stream(  unsigned  int  uiStreamId,  QIS_INTERVAL_PARAMS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
	int  tmpHandler_stream2QisIntervalParams(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );
#endif
int  qisGetCfgsReq2Stream(  unsigned  int  uiStreamId,  QIS_getCfgs_req  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2QisGetCfgsReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );


//  
int  transferFileReq2Stream(  unsigned  int  uiStreamId,  TRANSFER_FILE_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferFileReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  transferFileReplyReq2Stream(  unsigned  int  uiStreamId,  TRANSFER_FILE_REPLYREQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferFileReplyReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  taskProcReq2Stream(  unsigned  int  uiStreamId,  TASK_PROC_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TaskProcReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  taskProcResp2Stream(  unsigned  int  uiStreamId,  TASK_PROC_RESP  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TaskProcResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  transferFileDataReq2Stream(  unsigned  int  uiStreamId,  TRANSFER_FILEDATA_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferFileDataReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  transferFileDataResp2Stream(  unsigned  int  uiStreamId,  TRANSFER_FILEDATA_RESP  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferFileDataResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  transferFileEndReq2Stream(  unsigned  int  uiStreamId,  TRANSFER_FILEEND_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferFileEndReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  transferFileEndResp2Stream(  unsigned  int  uiStreamId,  TRANSFER_FILEEND_RESP  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferFileEndResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

//
//

int  messengerRegInfo2Stream(  unsigned  int  uiStreamId,  QY_MESSENGER_REGINFO  *  pRegInfo,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2MessengerRegInfo(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );
//
int  messengerPcInfo2Stream(  unsigned  int  uiStreamId,  QY_MESSENGER_PCINFO  *  pPcInfo,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2MessengerPcInfo(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

// 
int  refreshImObjRulesReq2Stream_0247(  unsigned  int  uiStreamId,  REFRESH_imObjRules_req  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RefreshImObjRulesReq_0247(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );

//  2011/11/12
int  refreshImObjRulesReq2Stream(  unsigned  int  uiStreamId,  REFRESH_imObjRules_req  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RefreshImObjRulesReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );

//  2012/08/05
int  ptzControlReq2Stream(  unsigned  int  uiStreamId,  PTZ_control_req  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2PtzControlReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );
int  ptzControlCmd2Stream(  unsigned  int  uiStreamId,  PTZ_control_cmd  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2PtzControlCmd(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );


//
int  messengerAccount2Stream(  unsigned  int  uiStreamId,  QY_MESSENGER_ACCOUNT  *  pPcInfo,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2MessengerAccount(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );


//
int  qisCaReq2Stream(unsigned  int  uiStreamId, QIS_ca_req* pReq, char* buf, unsigned  int* uiBufSize);
int  tmpHandler_stream2QisCaReq(CTX_stream2Data* pCtx, void* p0, void* p1, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem);

//
int  refreshImObjMemInfo2Stream(unsigned  int  uiStreamId, RefreshImObjMemInfo* pReq, char* buf, unsigned  int* uiBufSize);
int  tmpHandler_stream2RefreshImObjMemInfo(CTX_stream2Data* pCtx, void* p0, void* p1, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem);


//
int  imGrpEx2Stream(  unsigned  int  uiStreamId,  IM_GRP_EX  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2ImGrpEx(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );


int  retrieveImObjListReq2Stream(  unsigned  int  uiStreamId,  RETRIEVE_IMOBJLIST_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RetrieveImObjListReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  retrieveImGrpListResp2Stream(  unsigned  int  uiStreamId,  RETRIEVE_IMGRPLIST_RESP  *  pUpdateInfos,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RetrieveImGrpListResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  retrieveImGrpMemListResp2Stream(  unsigned  int  uiStreamId,  RETRIEVE_IMGRPMEMLIST_RESP  *  pUpdateInfos,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RetrieveImGrpMemListResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

//  2014/02/06
int  printRetrieveImGrpListResp(  RETRIEVE_IMGRPLIST_RESP  *  pResp  );
int  printRetrieveImGrpMemListResp(  RETRIEVE_IMGRPMEMLIST_RESP  *  pResp  );
int  printRetrieveContactListResp(  RETRIEVE_CONTACTLIST_RESP  *  p  );


//
int  retrieveContactListResp2Stream(  unsigned  int  uiStreamId,  RETRIEVE_CONTACTLIST_RESP  *  pUpdateInfos,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RetrieveContactListResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  retrieveImObjListEndResp2Stream(  unsigned  int  uiStreamId,  RETRIEVE_IMOBJLISTEND_RESP  *  pResp,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RetrieveImObjListEndResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  retrieveCustomerServiceObjListReq2Stream(  unsigned  int  uiStreamId,  RETRIEVE_customerServiceObjList_req  *  pUpdateInfos,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RetrieveCustomerServiceObjListReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  queryCustomerServiceOfficerReq2Stream(  unsigned  int  uiStreamId,  QUERY_customerServiceOfficer_req  *  pUpdateInfos,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2QueryCustomerServiceOfficerReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );

int  queryCustomerServiceOfficerReplyReq2Stream(  unsigned  int  uiStreamId,  QUERY_customerServiceOfficer_replyReq  *  pUpdateInfos,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2QueryCustomerServiceOfficerReplyReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );

int  transferGpsInfo2Stream(  unsigned  int  uiStreamId,  TRANSFER_GPS_INFO  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferGpsInfo(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );

int  transferGpsReplyInfo2Stream(  unsigned  int  uiStreamId,  TRANSFER_GPS_replyInfo  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferGpsReplyInfo(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );

int  transferGpsData2Stream(  unsigned  int  uiStreamId,  TRANSFER_GPS_DATA  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferGpsData(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );

int  transferGpsDataResp2Stream(  unsigned  int  uiStreamId,  TRANSFER_GPS_dataResp  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2TransferGpsDataResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );

int  retrieveWebContactListResp2Stream(  unsigned  int  uiStreamId,  RETRIEVE_WEBCONTACTLIST_RESP  *  pUpdateInfos,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RetrieveWebContactListResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

//
int  refreshRecentFriendsResp2Stream(  unsigned  int  uiStreamId,  REFRESH_RECENTFRIENDS_RESP_h  *  pResp,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RefreshRecentFriendsResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

//
int  qmdStatus2Stream(  unsigned  int  uiStreamId,  QMD_status  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2qmdStatus(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );

//
int  qmdMcuStatusList2Stream(  unsigned  int  uiStreamId,  QMD_mcuStatus_list  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2qmdMcuStatusList(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );

//
int  mcuCmd2Stream(  unsigned  int  uiStreamId,  MCU_cmd  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2mcuCmd(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );




//
int  qmdPolicy2Stream(  unsigned  int  uiStreamId,  QMD_policy  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2qmdPolicy(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );



//
 int  testSpeedReq2Stream(  unsigned  int  uiStreamId,  TEST_speed_req  *  pPcInfo,  char  *  buf,  unsigned  int  *  uiBufSize  );
 int  tmpHandler_stream2TestSpeedReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );

//
int  retrievePhoneMsgrs2Stream(  unsigned  int  uiStreamId,  RETRIEVE_PHONE_MSGRS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RetrievePhoneMsgrs(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

//
int  retrieveToPaths2Stream(  unsigned  int  uiStreamId,  RETRIEVE_TO_PATHS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RetrieveToPaths(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

int  refreshDynBmps2Stream(  unsigned  int  uiStreamId,  REFRESH_DYN_BMPS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RefreshDynBmps(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

//  2011/10/31
int  verifyViewDynBmp2Stream(  unsigned  int  uiStreamId,  VERIFY_viewDynBmp  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2VerifyViewDynBmp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

//
int  retrieveDynBmps2Stream(  unsigned  int  uiStreamId,  RETRIEVE_DYN_BMPS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
int  tmpHandler_stream2RetrieveDynBmps(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  p2  );

//
 int  procOfflineResU2Stream(  unsigned  int  uiStreamId,  PROC_offlineRes_u  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  );
 int  tmpHandler_stream2ProcOfflineResU(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );


 
 

//
extern  "C"  int  qnmOpenSession_mis(  char  *  servIp,  unsigned  short  usPort,  QY_COMM_AUTHINFO_MIS  *  pAuthInfo,  unsigned  short  usAuthCmd,  unsigned  int  uiChannelType,  char  *  clientIp,  int  iServiceId,  char  *  serviceVer,  void  *  pCommEncCtx,  __int64  i64StartTime_base,  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  char  *  data,  unsigned  int  *piDataSize,  Param_dbg  *  pParam  );




//
//int  qyhtonRefreshRecentFriendsReq(  long  lhClientVer,  REFRESH_RECENTFRIENDS_REQ_h  *  p  );
//int  qyntohRefreshRecentFriendsReq(  long  lhClientVer,  REFRESH_RECENTFRIENDS_REQ_h  *  p  );
//
int  qyhtonRefreshRecentFriendsReq(long  lhClientVer, REFRESH_RECENTFRIENDS_REQ_h* pH, AT_REFRESH_RECENTFRIENDS_REQ_n* pN);
int  qyntohRefreshRecentFriendsReq(long  lhClientVer, AT_REFRESH_RECENTFRIENDS_REQ_n* pN, REFRESH_RECENTFRIENDS_REQ_h* pH);


//
int  qyhtonImSimpleResp(  long  lhClientVer,  IM_SIMPLE_RESP  *  p  );
int  qyntohImSimpleResp(  long  lhClientVer,  IM_SIMPLE_RESP  *  p  );
//
//  int  qyhtonImStreamContent(  long  lhClientVer,  IM_STREAM_CONTENT  *  p  );
//  int  qyntohImStreamContent(  long  lhClientVer,  char  *  p,  IM_STREAM_CONTENT_nh  *  pStream  );
//
int  qyhtonImLStream(  long  lhClientVer,  IM_L_STREAM  *  p  );
int  qyntohImLStream(  long  lhClientVer,  char  *  p,  IM_L_STREAM_nh  *  pStream  );

//
int  qyhtonImContentU(  long  lhClientVer,  IM_CONTENTU  *  p  );
int  qyntohImContentU(  long  lhClientVer,  char  *  src,  IM_CONTENTU_nh  *  p  );

//  
//  ¸úÉÏÃæµÄqyhton²»Í¬µÄÊÇ£¬ÉÏÃæµÄqyhtonÒ»°ã¶¼ÊÇÒ»¸ö½á¹¹µÄ×ª»»¡£ËùÒÔÍùÍù·µ»Ø×ª»»ºóµÄ×Ö½ÚÊý
//  µ«ÊÇÏÂÃæµÄº¯ÊýÒª×ª»»µ½¶à¸ö½á¹¹£¬ËùÒÔ²»ÄÜ·µ»Ø×Ö½ÚÊý
int  qyhtonRouteTalkData(  MSG_ROUTE  *  pAddr,  char  *  pContentParam,  unsigned  int  lenInBytes_content,  BOOL  bNeedContentConvrted,  unsigned  char  ucFlg,  char  *  buf,  unsigned  int  *puiBufSize,  TCHAR  *  tHintBuf_showInfo,  unsigned  int  uiCnt_tHintBuf_showInfo  );
int  qyntohRouteTalkData(  unsigned  char  ucFlg,  char  *  data,  unsigned  int  dataLen,  MSG_ROUTE  *  pAddr,  IM_CONTENTU  *  pContent,  TCHAR  *  tHintBuf_showInfo,  unsigned  int  uiCnt_tHintBuf_showInfo  );

//
void  clean_myPLAY_AUDIO_DATA(  myPLAY_AUDIO_DATA  *  p,  LPCTSTR  hint  );
void  cleanEx_myPLAY_AUDIO_DATA(  myPLAY_AUDIO_DATA  *  p,  size_t	size,  LPCTSTR  hint  );
//
void  clean_myDRAW_VIDEO_DATA(  myDRAW_VIDEO_DATA  *  p,  LPCTSTR  hint  );
void  clean_MIS_MSG_procVideo_qmc(  MIS_MSG_procVideo_qmc  *  p,  LPCTSTR  hint  );

//  2012/11/10
void  cleanEx_myDRAW_VIDEO_DATA(  myDRAW_VIDEO_DATA  *  p,  size_t	size,  LPCTSTR  hint  );
void  cleanEx_MIS_MSG_procVideo_qmc(  MIS_MSG_procVideo_qmc  *  p,  size_t  size,  LPCTSTR  hint );
 

//
IM_TASK_RCD  *  msg2TaskRcd(  void  *  pMisCntParam,  MIS_MSG_TASK  *  pMsg,  unsigned  short  usRespCode,  IM_TASK_RCD  *  pRcd  );
__declspec(  dllexport  )  MIS_MSG_TASK  *  taskRcd2Msg(  void  *  pMisCnt,  IM_TASK_RCD  *  pRcd,  MIS_MSG_TASK  *  pMsg  );

//
int calc_conf_param(bool bConference, unsigned  int  uiTaskType, unsigned  short* pusMaxSpeakers, unsigned  short* pusCntLimit_activeMems_from);

//
bool  is4k(int iW, int iH);








#if  0
#define  bQThreadExists(  /* QY_qThreadProcInfo_common  & */  qThread  )		(  (  qThread  ).hThread  ||  (  qThread  ).hEvent_winThreadEnd  )  
#define  waitForQThread(  /* QY_qThreadProcInfo_common  & */  qThread,  dwMilliSeconds  )						\
							{	waitForObject(  &(  (  qThread  ).hEvent_winThreadEnd  ),  dwMilliSeconds  );	\
								waitForObject(  &(  (  qThread  ).hThread  ),  dwMilliSeconds  );		}
#endif

#define  bQThreadExists(  /* QY_qThreadProcInfo_common  & */  qThread  )		(  (  qThread  ).hThread  )  
#ifndef  __DEBUG__
		 #define  waitForQThread(  pQThread,  dwMilliSeconds  )	waitForObject(  &(  pQThread  )->hThread,  dwMilliSeconds  )
#else
		 void  waitForQThread(  QY_qThreadProcInfo_common  * pQThread,  DWORD  dwMilliSeconds  );
#endif

int  startQThread(  LPTHREAD_START_ROUTINE lpStartAddress,  LPVOID lpParameter,  void  *  pThreadClass,  QY_qThreadProcInfo_common  *  pQThread  );
int  stopQThread(  QY_qThreadProcInfo_common  *  pThread,  LPCTSTR  hint  );


BOOL  bGetPolicyImAuthCond(  HKEY  hKey,  LPCTSTR  schedulerKey,  POLICY_imAuthCond  *  p  );
BOOL  bGetPolicyIsMgr(  HKEY  hKeyRoot,  LPCTSTR  smCfgFile,  LPCTSTR  rootKey_qnmScheduler,  POLICY_isMgr  *  p  );
BOOL  bGetQisIntervalParams(  HKEY  hKeyRoot,  LPCTSTR  rootKey_qnmScheduler,  QIS_INTERVAL_PARAMS  *  pIntervalParams  );
BOOL  bGetSysParamIsMgr(  HKEY  hKeyRoot,  LPCTSTR  rootKey_qnmScheduler,  SYS_param_isMgr  *  p  );



// 
 int  printQ_mis(  void  *  pQ,  BOOL  bNetworkData  );		//  ÊÇ·ñÍøÂçÊý¾Ý
 int  printRetrieveContactListResp(  RETRIEVE_CONTACTLIST_RESP  *  p  );
 //
 int  printRefreshRecentFriendsReq(  REFRESH_RECENTFRIENDS_REQ_h  *  p  );
 int  printRefreshRecentFriendsResp(  REFRESH_RECENTFRIENDS_RESP_h  *  p,  LPCTSTR  hint  );
 //
 int  printQmObjQ_isClient(  void  *  p0,  void  *  p1,  void  *  pQmObjQ  );

 int  printMisMsg(  void  *  bNewworkDataParam,  void  *  p1,  MIS_MSGU  *  pMsg  );
 int  printImMsgContent_n(  void  *  pSessionParam,  MSG_ROUTE  *  pRoute,  IM_CONTENTU  *  pContent_n,  int  iContentLen,  TCHAR  *  tBuf,  unsigned  int  maxuiBufCnt  );



 #ifdef  __DEBUG__

int  printMsgRoute(  unsigned  char  ucFlg,  MSG_ROUTE  *  p  );

#endif

#endif  //  }

