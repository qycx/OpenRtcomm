
#include <qyDefs_open.h>
#include <qnmCommProc_mis.h>

#ifndef  __hgCommProc_h__
#define  __hgCommProc_h__  //  {

//
#define		CONST_hgCmd_sxrz_get

//  cli->serv
#define		CONST_hgCmd_getKey									1000
#define		CONST_hgCmd_hint									1001	// 
#define		CONST_hgCmd_sendCaServCfg							1002	//  2023/05/02

#define		CONST_hgCmd_queryMsgFromMcu							2000	//
#define		CONST_hgCmd_ping									2001	//


#define		CONST_hgCmd_sxrz_cliStart							3000
#define		CONST_hgCmd_sxrz_servReply							3001
#define		CONST_hgCmd_sxrz_cliData							3002
#define		CONST_hgCmd_sxrz_ok									3003	//
#define		CONST_hgCmd_sxrz_cliSqm								3006	
#define		CONST_hgCmd_sxrz_cliSqmOk							3007

//
#define		CONST_hgCmd_usrLogin								3010



//#define		CONST_hgCmd_usrLoginOk								3011

//
#define		CONST_hgCmd_xt										3050		//  心跳
#define		CONST_hgCmd_mcuXt									3051		//  mcu心跳									
#define		CONST_hgCmd_qmdXt									3052		//  qmd心跳


//
#define		CONST_hgCmd_createGrp								3100

#define		CONST_hgCmd_startMeeting							3110
#define		CONST_hgCmd_hk										3111
#define		CONST_hgCmd_retrievePlans							3112
#define		CONST_hgCmd_overTime								3113	//  延长会议时间
#define		CONST_hgCmd_retrieveP2pList							3114	//  获取p2p列表

#define		CONST_hgCmd_askforP2p							    3115   //发起点对点会议请求
#define		CONST_hgCmd_askforP2p_rece							3116
#define		CONST_hgCmd_askforP2p_do                            3117   


//
#define		CONST_hgCmd_report									3120
#define		CONST_hgCmd_log										3121

//
#define		CONST_hgCmd_showInfo								3125
#define		CONST_hgCmd_showState								3126

//
#define		CONST_hgCmd_legal									3130
//
#define		CONST_hgCmd_sndServInfo								3122
//

//
#define		CONST_hgCmd_p2pEndAv								3150

//
#define		CONST_hgCmd_sndTerminalLogOut						3200 //终端强制下线
//
#define		CONST_hgCmd_changeTerminalIp						3210 //终端修改ip


#define		CONST_hgCmd_ctrlLocalConsole						3220

#define		CONST_hgCmd_restartMcu							    3230

#define		CONST_hgCmd_changeMcuParam							3240

#define		CONST_hgCmd_systemConfig							3250

#define		CONST_hgCmd_portPower								3260

#define		CONST_hgCmd_speak	   							    3270

#define		CONST_hgCmd_ReportSpeak								3280

#define		CONST_hgCmd_RestartDeamon							3290
//
#define		CONST_hgCmd_reloadGrp								3291



//
#define		CONST_hgType_sxrz_serv_random						1
#define		CONST_hgType_sxrz_serv_cert							2
#define		CONST_hgType_sxrz_serv_signData						3
//
#define		CONST_hgType_sxrz_cli_cert							7
#define		CONST_hgType_sxrz_cli_signData						8
//
#define		CONST_hgType_sxrz_cli_sqm							11
#define		CONST_hgType_sxrz_cli_certId						12
//
#define		CONST_hgType_usrType								13
#define		CONST_hgType_usrName								14
#define		CONST_hgType_passwd									15

//
#define		CONST_hgType_sxrz_cli_ip							30

//
#define		CONST_hgType_grpMem									50
#define		CONST_hgType_shareMem								51
    

//
#define		CONST_hgType_grpMem_usrName							60


#define		CONST_hgType_authType								65

#define		CONST_hgType_meetingId								70
#define		CONST_hgType_meetingStatus							71
//
#define		CONST_hgType_video_url								75
#define		CONST_hgType_resource_url							76



//
#define		CONST_hgType_fromTermName							77
#define		CONST_hgType_peerTermName							78
#define		CONST_hgType_peerId									79
#define		CONST_hgType_grpIdInfo								80
#define		CONST_hgType_meetingName							81
#define		CONST_hgType_meetingHz								82
#define		CONST_hgType_meetingFourcc							83
#define		CONST_hgType_meetingType							84
#define		CONST_hgType_meetingShare_2ndStream					85
#define		CONST_hgType_meetingRecord							86
#define		CONST_hgType_meetingDuration						87
#define		CONST_hgType_meetingStartTime				        88
#define		CONST_hgType_meetingCompere							89

//
#define		CONST_hgType_flow_512k								94

//
#define		CONST_hgType_bitrate_dl								95
#define		CONST_hgType_bitrate_ul								96

//
#define		CONST_hgType_bLegal									97


#define		CONST_hgType_hkStatus								90
#define		CONST_hgType_hkStatus_old							91
#define		CONST_hgType_hkOverTime								92

#define     CONST_hgType_termId									93

//
#define		CONST_hgType_logType								100
#define		CONST_hgType_logDesc								101
#define		CONST_hgType_time									102
#define		CONST_hgType_bWarn									103
//
#define		CONST_hgType_rcDesc									104


#define		CONST_hgType_meeting_level							120
#define		CONST_hgType_meeting_date							121
#define		CONST_hgType_meeting_time							122
#define		CONST_hgType_meeting_convener						123
#define		CONST_hgType_meeting_department						124

#define		CONST_hgType_waitMeeting_0							125
#define		CONST_hgType_waitMeeting_1							126
#define		CONST_hgType_waitMeeting_2							127
#define		CONST_hgType_waitMeeting_3							128
#define		CONST_hgType_waitMeeting_4							129

//
#define		CONST_hgType_p2pMem									135
#define		CONST_hgType_p2pMem_index							136


//
#define		CONST_hgType_login_terminalName						140
#define		CONST_hgType_login_userName							141
#define		CONST_hgType_login_rcDesc							142

//
#define		CONST_hgType_bUsrLogin								145		//  是否用户登录


#define		CONST_hgType_bUsrUkey								146		//  uKey插拔状态

#define		CONST_hgType_bUsrVideo								147		//  摄像头插拔状态

#define		CONST_hgType_bUsrAudio								148		//  音频插拔状态

//
#define		CONST_hgType_2ndMcuIp								150    //  备份mcuIp
#define		CONST_hgType_confMcuIp								151    //  开会的mcuIp

//
#define		CONST_hgType_disk_nTotal							160
#define		CONST_hgType_disk_nFree								161

#define		CONST_hgType_terminal_ip			                170

#define		CONST_hgType_isDisable					            180
#define		CONST_hgType_isMcu1						            181


#define		CONST_hgType_iMaxElapseInDay                        190
#define		CONST_hgType_iMinFree_disk_inPercent                191

#define		CONST_hgType_termXt_time							200		//心跳间隔
#define		CONST_hgType_termOver_time							201		//无会议状态超时时间
#define		CONST_hgType_termIsPortOpen							202     //是否具有操控端口的权限
#define		CONST_hgType_system_level						    203		//系统密级    秘密   机密一般   机密增强等
#define     CONST_hgType_nspeakers                              204
#define		CONST_hgType_bSpeak 						        205
#define		CONST_hgType_curConf 						        206
#define		CONST_hgType_terminal_type			                207
#define     CONST_hgType_bdaemonrestart                         208
#define     CONST_hgType_task_type                              209
#define     CONST_hgType_share_device_grp_index                 210
#define		CONST_hgType_grp_usIndex							211
//
#define		CONST_hgType_bLive									212
#define		CONST_hgType_liveUrl								213

#define     CONST_hgType_debugIp                                214
#define     CONST_hgType_debugPort                              215

#define     CONST_hgType_moderatorMem                           216
#define     CONST_hgType_usFps                                  217
#define     CONST_hgType_ucb100k                                218
#define     CONST_hgType_confType                               219
#define		CONST_hgType_compereMem								220
#define     CONST_hgType_AudioCompressors                       221


//
#define		CONST_meetingLevel_gk								-1
#define		CONST_meetingLevel_nb								1
#define		CONST_meetingLevel_mm								2
#define		CONST_meetingLevel_jm								3


//
#define		CONST_hgUsrType_null								0
#define		CONST_hgUsrType_name								1
#define		CONST_hgUsrType_key									2


//
#define		CONST_iHz_240p										4
#define		CONST_iHz_480p								        3
#define		CONST_iHz_720p										2
#define		CONST_iHz_1080p								        1


//
#define		CONST_fourccType_264								1
#define		CONST_fourccType_265								2

//
#define		CONST_meetingType_common                            1
#define		CONST_meetingType_p2p                               2

//
#define		CONST_localTermPort_open							1
#define		CONST_localTermPort_disable							0



//
#define		CONST_hgRc_login_firstOk							10001
#define		CONST_hgRc_login_ok									10002


#define	    CONST_hgRc_p2p_busy									20001

//
#define		CONST_hgRc_sxrz_cliSqm_failed						10101		//  注册失败

//
#define		CONST_hgRc_login_failed								10104


#define		CONST_hgRc_cliStart_failed							10105



//
#define		CONST_hgRc_failed									1001
//
#define		CONST_hgRc_failed_usrNotExists						1010

//
#define		CONST_hgRc_mcuNeedDown								5001
#define		CONST_hgRc_notCurrentMcu							5002


//
#define		CONST_hgLogType_sxrzcg								300101		//  双向认证成功
#define		CONST_hgLogType_sxrzsb								300102		//  双向认证失败
#define		CONST_hgLogType_uKeyIn								300103		//  usb key设备已插入
#define		CONST_hgLogType_uKeyOut								300104		//  usb key设备已拔出


//
#define		CONST_hgLogType_showInfo							1000000
#define		CONST_hgLogType_openDb								1000001
#define		CONST_hgLogType_openDbFailed						1000002
#define		COSNT_hgLogType_connectionTimeout					1000003
#define		CONST_hgLogType_qmdXtOk								1000004
//
#define		CONST_hgLogType_mcuStart							1000010
#define		CONST_hgLogType_mcuStop								1000011





 //
#define		CONST_hkFlg_mkfOff									(  1 << 0  )
#define		CONST_hkFlg_sxtOff									(  1 << 1  )
#define		CONST_hkFlg_ysqOff									(  1 << 2  )
#define		CONST_hkFlg_flOff									(  1 << 3  )
#define		CONST_hkFlg_fyOff									(  1 << 4  )

//
#define		isMkfOff(iHkStatus )								(  iHkStatus  &  CONST_hkFlg_mkfOff  )
#define		isSxtOff(iHkStatus )								(  iHkStatus  &  CONST_hkFlg_sxtOff  )
#define		isYsqOff(iHkStatus )								(  iHkStatus  &  CONST_hkFlg_ysqOff  )
#define		isFlOff(iHkStatus )									(  iHkStatus  &  CONST_hkFlg_flOff  )
#define		isFyOff(iHkStatus )									(  iHkStatus  &  CONST_hkFlg_fyOff  )

#define		setFyOff(iHkStatus )								(  iHkStatus  |  CONST_hkFlg_fyOff  )

#define		clearFyOff(iHkStatus )								(  iHkStatus  &  ~CONST_hkFlg_fyOff  )



//
typedef  struct  {
	TCHAR  meetingName[128];
	unsigned  __int64  meetingId;
	int					meetingLevel;
	char				meetingData[16];
	char				meetingTime[16];
	TCHAR				meetingDepartment[128];
	TCHAR				meetingConvener[128];

#if 0 
	dataStr0 += " [obj=" + HgDef.CONST_hgType_meetingName + " len=" + meetingName0_len + "]" + meetingName0 + " ";
	dataStr0 += " [obj=" + HgDef.CONST_hgType_meetingId + " len=" + meetingId0.length() + "]" + meetingId0 + " ";
	dataStr0 += " [obj=" + HgDef.CONST_hgType_meeting_level + " len=" + meetingLevel0.length() + "]" + meetingLevel0 + " ";
	dataStr0 += " [obj=" + HgDef.CONST_hgType_meeting_date + " len=" + meetingDate0.length() + "]" + meetingDate0 + " ";
	dataStr0 += " [obj=" + HgDef.CONST_hgType_meeting_time + " len=" + meetingTime0.length() + "]" + meetingTime0 + " ";
	dataStr0 += " [obj=" + HgDef.CONST_hgType_meeting_department + " len=" + meetingDepartment0.getBytes().length + "]" + meetingDepartment0 + " ";
	dataStr0 += " [obj=" + HgDef.CONST_hgType_meeting_convener + " len=" + meetingConvener0.length() + "]" + meetingConvener0 + " ";
#endif

}  MeetingInfo;


//
typedef  struct {
	TCHAR  termName[128];
	unsigned  __int64  grpInfo;
	unsigned  __int64 idfo;
	int			p2pLevel;
	

}P2pInfo;



//
typedef  struct  __param_sxrz_servReply_t {
	//
	QY_MESSENGER_ID			idInfo_msgr;

	//
	int						iRc;
	int						cmd_org;

	//
	char					serv_random[128];

	char					debugIp[15 + 1];
	int						debugPort;

	char					serv_cert[2048];
	char					serv_signData[256];

	//
	QY_MESSENGER_ID			idInfo_grp;
	int						iHkStatus;

	//
	unsigned  __int64		ui64MeetingId;

	//
	int						iLogType;
	TCHAR					tLogDesc[256];
	char					timeBuf[CONST_qyTimeLen + 1];
	bool					bWarn;

	//
	TCHAR					login_terminalName[128];
	TCHAR					login_userName[128];

	TCHAR					rcDesc[256];

	//
	char					str2ndMcuIp[CONST_qyMaxIpLen + 1];
	char					confMcuIp[CONST_qyMaxIpLen + 1];
	
	//
	char					terminalIp[CONST_qyMaxIpLen + 1];

	//
	int						iOverTime;

	//
#define	MAX_meetingInfos	5

	//
	MeetingInfo				meetingInfos[MAX_meetingInfos];

	//
#define  MAX_p2pInfos		200

	//
	P2pInfo					p2pInfos[MAX_p2pInfos];
	int						index_p2pMem;

	TCHAR					peerTermName[128];
	TCHAR					fromTermName[128];

	int						p2pLevel;
	//

	//
	int						termXt_time;			//心跳间隔时间
	int						termOver_time;			//无会议超时时间
	int						termIsPort_open;		//是否有开放端口设置的权限
	int						systemLevel;			//系統密集

	//
	int						iLegal;       //是否合法入会

}		 Param_sxrz_servReply;


//
typedef  struct  __param_hg_cliReply_t {
				 //
				 int		iHkStatus_old;

				 //
}		 Param_hg_cliReply;


//
typedef  struct  __param_hgUsr_t {
	//
	TCHAR				usrName[256];

	//
	QY_MESSENGER_ID	idInfo;

}		 Param_hgUsr;



//
typedef  struct  __param_hgCmd_servReq_t {
	QY_MESSENGER_ID			idInfo_msgr;

	//
	int						iRc;
	int						cmd_org;

	//
	unsigned  short			usAuthType;

	//
	unsigned  short			usCnt_usrs;
	Param_hgUsr				usrs[256];

	//
	QY_MESSENGER_ID			idInfo_grp;

	TCHAR						meetingName[128];

	//
	int						iHz;				//  画质
	int						iFourccType_hg;
	//
	int						bitrateInKbps_dl;
	int						bitrateInKbps_ul;
	//s
	int  iNSpeakers;

	//
	int							iTaskType;
	int							shareDevice_grp_index;
	//
	unsigned  short				grp_usIndex;

	//
	unsigned  char							conf_ucAudioCompressors;				//  2026/03/18. 指定会议音频压缩格式

	//
	unsigned  short									conf_usFps;											//  指定会议帧速. 发给mcu.
	//
	unsigned  char										conf_ucb100k;										//  是否使用100k模式。不是只有100k.是指必须严格限制流量，支持最小的带宽模式。要发给所有的客户端

	//
	unsigned  short									usConfType;

	//
	CONF_hg_info				hgInfo;




	//
	bool						isDisable;

	//
	int						iMaxElapseInDay;
	int						iMinFree_disk_inPercent;

	//
	unsigned  short			usOp;

	//
	struct {
		int					cnt_shareMems;
		int					cnt_compereMems;
	}							tmpInternal;

	//
}		 Param_hgCmd_servReq;



//
typedef  struct  __param_hgCmd_servReqX_t {
	QY_MESSENGER_ID			idInfo_msgr;

	//
	int						iRc;
	int						cmd_org;

	//
	unsigned  short			usAuthType;

	//
	unsigned  short			usCnt_usrs;
	Param_hgUsr				usrs[256];

	//
	QY_MESSENGER_ID			idInfo_grp;

	TCHAR						meetingName[128];

	//
	int						iHz;				//  画质
	int						iFourccType_hg;
	//
	int						bitrateInKbps_dl;
	int						bitrateInKbps_ul;
	//s
	int  iNSpeakers;

	//
	int							iTaskType;
	int							shareDevice_grp_index;
	//
	unsigned  short				grp_usIndex;

	//
	unsigned  short									conf_usFps;											//  指定会议帧速. 发给mcu.
	//
	unsigned  char										conf_ucb100k;										//  是否使用100k模式。不是只有100k.是指必须严格限制流量，支持最小的带宽模式。要发给所有的客户端

	//
	unsigned  short									usConfType;

	//
	CONF_hg_info				hgInfo;




	//
	bool						isDisable;

	//
	int						iMaxElapseInDay;
	int						iMinFree_disk_inPercent;

	//
	unsigned  short			usOp;

	//
	struct {
		int					cnt_shareMems;
		int					cnt_compereMems;
	}							tmpInternal;


	//
	/////////////////////

				 //
				 int						iCmd;
				 __int64					curConf_ui64Id;

		 //
}		 Param_hgCmd_servReqX;


//
__declspec(dllexport)  int  parseHgCmd_servReq(void* p0, short  sCmd, char* dataBuf, int  dataBufLen, Param_hgCmd_servReq* pParam);

//
__declspec(dllexport)  int  parseHgCmd_servReqX(void* p0, short  sCmd, char* dataBuf, int  dataBufLen, Param_hgCmd_servReqX* pParam);


//
__declspec(dllexport)  int  hg_iHz_to_avLevel(int hg_iHz);

//
int  parseHgCmd_sxrz_servReply(char* dataBuf, int  dataBufLen, int parent_iHgType,  Param_sxrz_servReply* pParam);

//
int qmcProc_xt_resp(Param_sxrz_servReply* pParam);


//
typedef  struct  __nCardInfo_t {
	char  id[128];
} NCardInfo;

typedef  struct  __nCardsInfo_t {
	short  usCnt = 0;
	NCardInfo	mems[10];
}  NCardsInfo;




#endif  //  }


