

#ifndef  __QNMCOMMPROC_H__
#define	 __QNMCOMMPROC_H__	/*  {  */

//
#include	"ancCommProc_open.h"
#include	"ancCommProc_defs.h"
#include	"commonSock_open.h"
#include <qyAuthCommon_open.h>
#include	"qyCommProc.h"

//
#ifdef  __cplusplus
  extern  "C"  {
#endif

//
#define		CONST_stateType_sys			1
//
#define  	CONST_stateType_tasks		10
#define  	CONST_stateType_players		11
#define  	CONST_stateType_talks		12
#define		CONST_stateType_qs			13
//
#define		CONST_stateType_others		20



//
#define		CONST_qyCfgName_cntIp							"Cnt"
	#define		DEFAULT_qyCfgVal_cntIp							"128.0.0.1"
#define		CONST_qyCfgName_cntAddr1						"cnt1"
#define		CONST_qyCfgName_cntAddr2						"cnt2"
//
#define		CONST_qyCfgName_cntPort							"Port"
	#define		DEFAULT_qyCfgVal_cntPort						6789
//
//  #define		CONST_qyCfgName_systemId						"Sys"
#define		CONST_qyCfgName_systemId						"qySys"		//  2007/01/06
#define		CONST_qyCfgName_qwmSeqNo						"seq"		//  ÐòÁÐºÅ£¬2005/0624
#define		CONST_qyCfgName_bSecChkQuickly					"ChkQuck"
#define		CONST_qyCfgName_bNoGui							"NoGui"			
#define		CONST_qyCfgName_bGetPcAsset						"PcAst"		//  ×Ê²ú¹ÜÀí
#define		CONST_qyCfgName_bNetMc2							"Bha"		//  ·Ç·¨ÍâÁª¹ÜÀí
#define		CONST_qyCfgName_bSecChk							"Chk"		//  ÊÇ·ñ°²¼ì	2005/05/02
#define		CONST_qyCfgName_bDj								"Dj"		//  ÊÇ·ñµ¥»ú°æ	2005/08/17
#define		CONST_qyCfgName_yMD								"YMD"		//  µ¥»ú°æ¿ÉÒÔÔËÐÐµÄÔÂÈÕ£¬2005/08/20

//  2006/12/19
#define		CONST_qyCfgName_dbType							"qyDbType"
#define		CONST_qyCfgName_sysName							"qySysName"


#ifdef  __DEBUG__
		  #define		DEFAULT_qwmServIp							"127.0.0.1"
		  //#define		DEFAULT_qwmServIp							"188.188.188.188"
	      //  #define		DEFAULT_qwmServIp							"188.188.188.29"
		#define		DEFAULT_qwmServAddr1						""				//  "testdns.gnway.net"
		#define		DEFAULT_qyCfgVal_qnmRespPort				8788
		#define		DEFAULT_qyCfgVal_systemId					CONST_qySystemId_netMc4
		#define		DEFAULT_qnmDbServIp							"127.0.0.1"				//  Êý¾Ý¿â·þÎñÆ÷µÄIP
		#define		DEFAULT_qnmDbName							"qnmDb"
		#define		DEFAULT_qnmDbUid							"qnmDbUsr"
		#define		DEFAULT_qnmDbPwd							"admin"
#else
	 //  #define		DEFAULT_qwmServIp							"128.1.1.1"
	 #define		DEFAULT_qwmServIp							"192.168.1.0"
	 #define		DEFAULT_qwmServAddr1						"testdns.gnway.net"
	 //
	 #define		DEFAULT_qyCfgVal_qnmRespPort				DEFAULT_qyCfgVal_qnmProxyPort
	 #define		DEFAULT_qyCfgVal_systemId					CONST_qySystemId_null
	 #define		DEFAULT_qnmDbServIp							"127.0.0.1"					//  Êý¾Ý¿â·þÎñÆ÷µÄIP
	 #define		DEFAULT_qnmDbName							"qnmDb"
	 #define		DEFAULT_qnmDbUid							"qnmDbUsr"
	 #define		DEFAULT_qnmDbPwd							""
#endif

#define		DEFAULT_qisDbName									"qisDb"
#define		DEFAULT_qisClientDbName								"qisClientDb"
//
#ifndef  __WINCE__
			#define		CONST_maxOfVideoConferencingServers					121							//	2022/07/13  为测试500点设计的；//	2010/02/15	
		   //#define		CONST_maxOfVideoConferencingServers				31							//	2011/05/11  为测试200点设计的；//	2010/02/15	
		   //#define		CONST_maxOfVideoConferencingServers					61						//	2012/05/19  为测试200点设计的；//	2010/02/15	
		 //#define		CONST_maxOfVideoConferencingServers					10							//	2014/02/04  为测试即时通信
#else  
  		 #define		CONST_maxOfVideoConferencingServers					4							//	2010/07/08	
#endif

//  2004/10/24
//  #define		DEFAULT_interMonPort								7369
#define		DEFAULT_interMonPort								80			//  2004/11/12
#define		CONST_qyMagic_interMon								"StateOk"

typedef  struct  __qwmWarnToInterMonInfo_t						{
				 char											mac0[CONST_qyMacLen  +  1];
				 char											pcName[16  +  1];
}		 QWM_WARNTOINTERMON_INFO;


//
//
typedef  struct  __qnmModulesLoadesInfo_t						{
				 unsigned  long									ulbNetMc2ModuleLoaded:1;		
				 unsigned  long									ulbNmsModuleLoaded:1;			
				 unsigned  long									ulbNetFlowModuleLoaded:1;
				 unsigned  long									ulbSecChkModuleLoaded:1;		
				 //  unsigned  long									ulbNetMc4ModuleLoaded:1;		
				 unsigned  long									ulbAssetMgrModuleLoaded:1;
				 //
				 unsigned  long									ulbMsgrMgrModuleLoaded:1;	//  2007/03/11
				 //
				 unsigned  long									ulbServiceNetMcLoaded:1;		//  2007/03/11
				 unsigned  long									ulbServiceMisLoaded:1;		//  2007/03/11
}		 QNM_MODULES_LOADEDINFO;


#define		MACRO_qnmModulesLoadedInfo							QNM_MODULES_LOADEDINFO	modulesLoadedInfo;


//  2005/08/27
#define		DEFAULT_qmCfgFileName								"qyMc.jpg"
	//
	#define		CONST_cfgName_qyMcTitle							"qyMcTitle"
	#define		CONST_cfgName_qyClientTitle						"qyClientTitle"
	#define		CONST_cfgName_qyClientTitle_part0				"qyClientTitle_part0"
	#define		CONST_cfgName_qyClientTitle_part1				"qyClientTitle_part1"

	//
	#define		CONST_cfgName_qyRegToolTitle					"qyRegToolTitle"
	//
	#define		CONST_cfgName_bThinkPad							"belongToLegend"					//  Èç¹ûÎªThinkPad£¬Ôò±íÃ÷ÊÇ±Ê¼Ç±¾¹ÜÀí£¬ÕâÑùÔÊÐíÉè¼àÊÓ¶Ë
	#define		CONST_cfgVal_bThinkPad							"ThinkPad"							//  ·ñÔò£¬¾Í²»ÔÊÐíÉèÖÃ£¬²¢ÇÒÐèÒªÇå³ý×¢²á±íÀïµÄ¼àÊÓ¶ËÉèÖÃ£¬²¢Òþ²Ø¸ÃÉèÖÃ
	//
	#define		CONST_cfgName_bBhqj								"bhqj"								//  ÊÇ·ñÊÇ²¦ºÅÈ«½ûµÄ°æ±¾£¬2005/04/20
	#define		CONST_cfgVal_bBhqj								"ysd"								//  Õâ¸öÖµÎª²¦ºÅÈ«½û£¬¡°ÑÏËàµã¡±
	
	#define		CONST_cfgName_bRasControlNotSupported			"bhb"
	#define		CONST_cfgVal_bRasControlNotSupported			"qqq"
	 
	//
	#define		CONST_cfgName_bHaveDj							"Smj"								//  Ê²Ã´»ú
	#define		CONST_cfgVal_bHaveDj							"Kdj"								//  ¿ÏµÃ»ù,°²¼ìµ¥»ú°æ±¾£ºdj.exeºÍdj1.exe
	#define		CONST_cfgName_bAdvancedVer						"Smjiu"								//  Ê²Ã´¾Æ
	#define		CONST_cfgVal_bAdvancedVer						"Mtjiu"								//  Ã©Ì¨¾Æ
	#define		CONST_cfgName_bAdvancedOptionEnabled			"Smk"								//  Ê²Ã´¿â, 2005/11/18			
	#define		CONST_cfgVal_bAdvancedOptionEnabled				"Dsjk"								//  ´óÊý¾Ý¿â


//
#define			CONST_cfgName_bUse_decD3d_nv					"bUse_decD3d_nv"	
//
#define			CONST_cfgName_bDbgDetail						"bDbgDetail"	
#define			CONST_cfgName_bDbgDetail_saveAv					"bDbgDetail_saveAv"
#define			CONST_cfgName_bDbgDetail_switch_a				"bDbgDetail_switch_a"
#define			CONST_cfgName_bDbgDetail_switch_v				"bDbgDetail_switch_v"






//
#define		CONST_finalName_qrtForSecChkDj						"dj.exe"
#define		CONST_finalName_qrtForSecChkDj1						"dj1.exe"
#define		CONST_finalName_qrtForSecChkDj98					"dj98.exe"
#define		CONST_finalName_qrtForSecChkDj981					"dj981.exe"
#define		CONST_finalName_myCapture							"myCapture.exe"
//
#define		CONST_finalName_djTool								"djTool.exe"	//  2007/10/21, ÓÃÀ´´ÓÒ»¸öUÅÌÖÐ×ªÒÆµ½ÁíÒ»¸öUÅÌ
// #define		CONST_finalName_djTool								"qyRegTool98.exe"	//  2007/10/21, ÓÃÀ´´ÓÒ»¸öUÅÌÖÐ×ªÒÆµ½ÁíÒ»¸öUÅÌ


////////////////////

//  ÒÔÏÂÊÇ½öÓ¦ÓÃÔÚqnmÏîÄ¿ÀïµÄ¼üÖµ£¬2004/07/12  {
#define		CONST_qyKey_qnmsMonIfs								(  "Software\\Qycx\\Qwm\\Modules\\qnms\\temp\\monIfs"  )				
																//  Ã¿¸öÃ¶¾Ù¼üÖµ¸ñÊ½£º	ip12  +  iPortIfIndex(12Î», ²»×ã´¦Ç°Ìî0)	ÖµÎª´°¿ÚÃû32¸ö×Ö½Ú



//  }
/////////////////////

#define		CONST_winUsr_allUsers				"All Users"
#define		CONST_winUsr_defaultUser			"Default User"  
#define		CONST_winUsr_localService			"LocalService"  
#define		CONST_winUsr_networkService			"NetworkService" 


#define		CONST_subKey_defaultUsr				".Default"		//  ×¢²á±íÀïµÄÌØÊâ¼üÖµ£¬´ú±íÈ±Ê¡ÓÃ»§£¬2005/06/19


BOOL  bSkippedSubDir(  TCHAR  *  subDirName  );
//  BOOL  bDir(  char  *  dir  );// 
//BOOL  bDir(  LPCTSTR  dir  );
int  qwmEnumUsrRootDir(  QY_ENV  *  pEnv,  LPCTSTR  usrsRootDir,  PF_commonHandler  pF,  void  *  p0,  void  *  p1  );
//  int  qwmEnumUsrDir(  QY_ENV  *  pEnv,  TCHAR  *  usrDir,  PF_commonHandler  pF,  void  *  p0,  void  *  p1  );
int  qwmEnumUsrDir(  QY_ENV  *  pEnv,  LPCTSTR  usrDir,  PF_commonHandler  pF,  void  *  p0,  void  *  p1  );
int  showQwmSvrStatus(  QY_ENV  *  pEnv,  char  *  servIp,  unsigned  short  usPort,  int  iServiceId,  char  *  ver,  void  *  pCommEncCtx,  SOCK_TIMEOUT  *  pTo,  unsigned  int  uiStatus,  void  *  pShowQwmSvrStatus  );
int  enumReg(  QY_ENV  *  pEnv,  int  iRuleId,  HKEY  hRootKey,  LPCWSTR keyName,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  );

//

//  ÒÔÉÏqnmChkCommProc.cppÖÐµÄ¶¨Òå

//  ÏÂÃæ¶¨ÒåÒ»¸öÍ¨ÐÅÐ­Òé¹ý³ÌÖÐµÄ·þÎñÏìÓ¦°ü  {
#define		CONST_serviceRespType_null						0
#define		CONST_serviceRespType_serv						1

typedef  struct  __qyCommServiceResp_t  {
		 unsigned  int					uiType;
		 unsigned  int					uiSize;
		 union							{
			 struct						{
				 char					seqNo[128  +  1];
			 }							serv;				//  ¹ÜÀí¶ËÐÅÏ¢
			 char						data[1024];			//  
		 }								u;
}		 QY_COMM_SERVICERESP;								//  Ö»ÓÃÓÚnetMcÏµÍ³, 2007/12/09

//  }

//  ×¢ÒâpcStopMon²»ÒªÈ¡Öµ'\0', ÒòÎªÒªÈë¿â
#define		CONST_stopMon_default							'9'
#define		CONST_stopMon_true								'1'
#define		CONST_stopMon_false								'0'


#define		CONST_rasCmdStr_permitted						"7jkl"
#define		CONST_rasCmdStr_prohibited						"1000"
#define		CONST_rasCmdStr_offlinePermitted				"2cb4"


//
#define		CONST_devCmd_null								0				//  2010/08/13

//  rasCmd
#define		CONST_rasCmd_default							1
#define		CONST_rasCmd_permitted							2
#define		CONST_rasCmd_prohibited							3
#define		CONST_rasCmd_offlinePermitted					4
#define		CONST_rasCmd_zdhmyx								5
//
//  2005/01/04
#define		CONST_devCmd_permitted							CONST_rasCmd_permitted
#define		CONST_devCmd_prohibited							CONST_rasCmd_prohibited		//  只禁用设备。如果设备被锁住，那么也不重启操作系统
#define		CONST_devCmd_restartToProhibit					10							//  2005/06/22
#define		CONST_devCmd_permittedAndLog					11							//  2005/10/07, USB
#define		CONST_devCmd_prohibitedCanReboot				12							//  2011/08/28. 如果设备被锁住，那么可以重启操作系统
//
#define		CONST_devCmd_none								48							//  2007/02/13,	Î´ÅäÖÃ, ÓÃasciiµÄ'0'µÄÖµ£¬·½±ãÓÃÑÛ¾¦Ö±½Ó¿´²ßÂÔ


//  2005/10/15, ÒÔÏÂÎªÈ±Ê¡²ßÂÔ
#define		DEFAULT_rasCmd									CONST_rasCmd_permitted		//  2005/11/16  
#define		DEFAULT_sndEventLogCmd							CONST_devCmd_prohibited
#define		DEFAULT_watchPrinterCmd							CONST_devCmd_permitted
#define		DEFAULT_sndNetStatCmd							CONST_devCmd_prohibited
#define		DEFAULT_sndModuleInfoCmd						CONST_devCmd_prohibited		//  2006/05/06
#define		DEFAULT_capScreenCmd							CONST_devCmd_prohibited
#define		DEFAULT_sndPcRegistryValCmd						CONST_devCmd_permitted		//  2006/08/15
//
#define		DEFAULT_ucHideQwmCmd							CONST_devCmd_prohibited		//  2010/05/16
//  2006/09/11
#define		DEFAULT_ucWarnedNetworkCardCmd					CONST_devCmd_permitted
#define		DEFAULT_ucDetectTimesBeforeWarn					2
#define		DEFAULT_usStopNetworkCardTimeInSecond			5

#define		MAX_usStopNetworkCardTimeInSecond				20  *  60
#define		MIN_usStopNetworkCardTimeInSecond				1


//  ×¢²áÐÅÏ¢µÄ×Ö¶Î¶¨Òå
#define		CONST_fieldId_null								0
#define		CONST_fieldId_yhlx								100
#define		CONST_fieldId_syr								200
#define		CONST_fieldId_bm								201
#define		CONST_fieldId_dw								202
#define		CONST_fieldId_qtdw								203
#define		CONST_fieldId_bb								204
#define		CONST_fieldId_zb								205
//
#define		CONST_fieldId_zcbh0								220
#define		CONST_fieldId_zcbh1								221
#define		CONST_fieldId_zcbh2								222
//  #define		CONST_fieldId_zcsm0								223
#define		CONST_fieldId_zcsm1								224
#define		CONST_fieldId_zcsm2								225
#define		CONST_fieldId_jqlx								240
#define		CONST_fieldId_lxdh								241
#define		CONST_fieldId_sydd								242
#define		CONST_fieldId_zyyt								243
#define		CONST_fieldId_bz1								244
#define		CONST_fieldId_bz2								245

//
#define		CONST_qyGrpBit_administrators					0
#define		CONST_qyGrpBit_system							1


#define		CONST_qnmnMacsBufSize							4
#define		CONST_qnmMaxEventRegFields						10					//  ÈÕÖ¾ÀïÄÜ°üº¬µÄÃèÊöÊÂ¼þµÄÊ¹ÓÃÕßÐÅÏ¢£¨×¢²áÐÅÏ¢£©µÄ×î´óÏîÊý
#define		CONST_qnmMaxEventDesFields						10					//  ÈÕÖ¾ÀïÄÜ°üº¬µÄÃèÊöÊÂ¼þ±¾ÉíÐÅÏ¢µÄ×î´óÏîÊý
#define		CONST_qnmMaxRegFields							30					//  ÒÔÏÂµÄÉèÖÃÖµ²»ÄÜ³¬¹ý´ËÏî, Ö¸cols, »¹ÓÐ¼¸ÏîÈçmac0µÈ£¬²»°üº¬ÔÚÄÚ
#define		CONST_qnmMaxSearchFields						15
//

////
//
#define		CONST_ucFlg_ok									0
#define		CONST_ucFlg_end									(  unsigned  char  )-1
#define		CONST_ucFlg_err									(  unsigned  char  )-2
//  #define		CONST_ucFlg_waitForReboot						(  unsigned  char  )-3
//
#define		isucFlgOk(  ucFlg  )							(  ucFlg  ==  CONST_ucFlg_ok  )
#define		isucFlgEnd(	ucFlg  )							(  ucFlg  ==  CONST_ucFlg_end  )	// 2005/05/24
#define		isucFlgErr(	ucFlg  )							(  ucFlg  ==  CONST_ucFlg_err  )	// 2005/06/04

//
extern		QY_DMITEM   CONST_qyGrpTable[];
extern		QY_DMITEM	CONST_qnmStopMonTable_en[];
extern		QY_DMITEM	CONST_qnmCfgRasCmdTable_en[];
extern		QY_DMITEM	CONST_qnmRasCmdTable_en[];
extern		QY_DMITEM	CONST_qnmRasCmdTable_cn[];


extern		QY_DMITEM	CONST_qnmDevCmdTable0_en[];			//  ÓÃÀ´»ã×ÜËùÓÐµÄÃüÁî£¬ÔÚÏÔÊ¾ÖÐÒ²·½±ã. 2005/06/22
//
extern		QY_DMITEM	CONST_fieldIdTable_en[];			//  2009/01/01,×¢ÊÍÊ±¼ä£º2008/12/28


#define		ASR_CMD_STR_RAS_PERMITTED						CONST_rasCmdStr_permitted
#define		ASR_CMD_STR_RAS_PROHIBITED						CONST_rasCmdStr_prohibited	// any other value will be equivalent to this
#define		ASR_CMD_STR_RAS_OFFLINE_PERMITTED				CONST_rasCmdStr_offlinePermitted



// ÊÂ¼þID¶¨Òå		¾¯¸æ£ºÑÏ½ûÐÞ¸ÄÏÂÃæµÄ¶¨Òå£¬ÒòÎªÕâÊÇÒÑ´æ´¢ÔÚÊý¾Ý¿âÖÐµÄ¶¨Òå£¬ÐÞ¸Ä½«Ê¹ÏÖÓÐµÄÏµÍ³ÎÞ·¨¼æÈÝ
//
#define		CONST_qyEventType_null								0
//		¼ÆËã»úÊÂ¼þID¶¨Òå
#define		CONST_qyEventType_nm_newPc							100
#define		CONST_qyEventType_nm_macsModified					101
#define		CONST_qyEventType_nm_macsModifiedPc					102
#define		CONST_qyEventType_nm_newReg							200
#define		CONST_qyEventType_nm_reReg							201
#define		CONST_qyEventType_nm_qwmDel							300
#define		CONST_qyEventType_nm_qwmDelRecovery					301
#define		CONST_qyEventType_nm_qwmDelOffline					302
#define		CONST_qyEventType_nm_ipChanged						400
#define		CONST_qyEventType_nm_osChanged						401
#define		CONST_qyEventType_nm_rasStart						500
#define		CONST_qyEventType_nm_rasEnd							501
#define		CONST_qyEventType_nm_rasProhibited					502
#define		CONST_qyEventType_nm_onInternet						503
#define		CONST_qyEventType_nm_offInternet					504
#define		CONST_qyEventType_nm_wLanAdapterStart				505				//  2010/05/20
#define		CONST_qyEventType_nm_wLanAdapterEnd					506				//  2010/05/20
#define		CONST_qyEventType_nm_wLanAdapterProhibited			507				//  2010/05/20


//
#define		CONST_qyEventType_nm_usbStorOnFor9x					510				//	2005/01/08			
#define		CONST_qyEventType_nm_usbStorOffFor9x				511				//  2005/01/08
#define		CONST_qyEventType_nm_usbStorIn						512				//  2005/01/07
#define		CONST_qyEventType_nm_usbStorUnallowedIn				513				//  2005/01/07
#define		CONST_qyEventType_nm_usbStorOut						514				//  2005/01/07
#define		CONST_qyEventType_nm_usbStorProhibited				515				//  2005/01/07
#define		CONST_qyEventType_nm_usbRestartToProhibit			516				//  2005/06/26
//
#define		CONST_qyEventType_nm_floppyOn						520				//  2005/01/08
#define		CONST_qyEventType_nm_floppyOff						521				//  2005/01/08
#define		CONST_qyEventType_nm_cdromOn						522				//  2005/01/08
#define		CONST_qyEventType_nm_cdromOff						523				//  2005/01/08
#define		CONST_qyEventType_nm_safeModeOn						524				//  2005/06/25
#define		CONST_qyEventType_nm_safeModeOff					525				//  2005/06/25
#define		CONST_qyEventType_nm_netShareMgr					526				//  2007/02/17
//
#define		CONST_qyEventType_nm_ucBlueToothProhibited			540				//  2010/08/18
#define		CONST_qyEventType_nm_ucInfraredProhibited			543				//  2010/08/18
#define		CONST_qyEventType_nm_uc1394Prohibited				546				//  2010/08/18
#define		CONST_qyEventType_nm_sdHostAdapterProhibited		547				//  2011/08/28

//
#define		CONST_qwmDevType_null								0				//  2011/09/21
#define		CONST_qwmDevType_wpd								1
#define		CONST_qwmDevType_mobileDevice						2
#define		CONST_qwmDevType_usbNetworkCard						3

//
#define		CONST_qyEventType_nm_devIn							560				//  2011/08/25
#define		CONST_qyEventType_nm_devOut							561				//  2011/08/25
#define		CONST_qyEventType_nm_devProhibited					562				//  2011/08/25
#define		CONST_qyEventType_nm_devEnabled						563				//  2011/08/25

#if  0
#define		CONST_qyEventType_nm_mobileDeviceIn					566				//  2011/08/25
#define		CONST_qyEventType_nm_mobileDeviceOut				567				//  2011/08/25
#define		CONST_qyEventType_nm_mobileDeviceProhibited			568				//  2011/08/25
#define		CONST_qyEventType_nm_mobileDeviceEnabled			569				//  2011/08/25
#endif


//
#define		CONST_qyEventType_nm_strangePc						600
#define		CONST_qyEventType_nm_strangePcUnderCtrl				601
#define		CONST_qyEventType_nm_strangePcOffline				602
#define		CONST_qyEventType_nm_pcUnchked						603
#define		CONST_qyEventType_nm_pcAttacked						604
#define		CONST_qyEventType_nm_strangeIp						605				//  Î´×¢²áIPÊÂ¼þ
#define		CONST_qyEventType_nm_delPc							700
#define		CONST_qyEventType_nm_proxyServerSet					800
#define		CONST_qyEventType_nm_proxyServerClear				801
//
#define		CONST_qyEventType_nm_printerJob						810
//  #define		CONST_qyEventType_nm_fileMon						820
#define		CONST_qyEventType_nm_fileAdded						821				//  2006/03/23, ½«ÉÏÃæµÄÊÂ¼þ·Ö³ÉËÄ¸öÊÂ¼þ
#define		CONST_qyEventType_nm_fileRemoved					822
#define		CONST_qyEventType_nm_fileModified					823
#define		CONST_qyEventType_nm_fileRenamed					824
//
#define		CONST_qyEventType_nm_processMgr						830				//  2005/10/10
//
#define		CONST_qyEventType_nm_registryAdded					835				//  2006/07/31
#define		CONST_qyEventType_nm_registryRemoved				836				//  2006/07/31
#define		CONST_qyEventType_nm_registryModified				837				//  2006/07/31
//
#define		CONST_qyEventType_nm_netFlowWarn					840				//  2006/09/12
//
//		°²¼ìÊÂ¼þID¶¨Òå
#define		CONST_qyEventType_secChk_recent						900				//  ¼ì²é×î½üÊ¹ÓÃµÄÎÄ¼þ
#define		CONST_qyEventType_secChk_cookie						901				//  ¼ì²écookie
#define		CONST_qyEventType_secChk_proxyCfg					902				//  ¼ì²é´úÀíÉèÖÃ
#define		CONST_qyEventType_secChk_ieHistory					903				//  ¼ì²éÉÏÍøÁÙÊ±ÎÄ¼þ	
#define		CONST_qyEventType_secChk_fileHistory				904				//  ¼ì²éÎÄ¼þ¼ÇÂ¼
#define		CONST_qyEventType_secChk_shareDirectory				905				//  ¼ì²é¹²Ïí×ÊÔ´
#define		CONST_qyEventType_secChk_sharePrinter				906				//  ¼ì²é¹²Ïí´òÓ¡»ú
#define		CONST_qyEventType_secChk_rasPhoneBk					907				//  ¼ì²é²¦ºÅºÅÂë
#define		CONST_qyEventType_secChk_diskFile					908				//  ¼ì²é´ÅÅÌÎÄ¼þ
#define		CONST_qyEventType_secChk_diskFileDel				909				//  ¼ì²éÒÑÉ¾³ýµÄ´ÅÅÌÎÄ¼þ

//		ÓÃ»§Ê¹ÓÃµçÄÔµÄÊÂ¼þ
#define		CONST_qyEventType_nm_usrMgr							1200			//  ÓÃ»§¼¶¹ÜÀí£¬2007/02/18

//		ÍøÂçÉè±¸ÊÂ¼þID¶¨Òå
#define		CONST_qyEventType_nms_newDev						2000			//  ÐÂÔöÉè±¸
#define		CONST_qyEventType_nms_delDev						2001			//  É¾³ýÉè±¸
#define		CONST_qyEventType_nms_devOnline						2002			//  Éè±¸ÔÚÏß
#define		CONST_qyEventType_nms_devOffline					2003			//  Éè±¸ÀëÏß
#define		CONST_qyEventType_nms_willAttack					2004			//  Ö¸¶¨Éè±¸µÄÖ¸¶¨¶Ë¿Ú×è¶Ï
#define		CONST_qyEventType_nms_stopWillAttack				2005			//  Ö¸¶¨Éè±¸µÄÖ¸¶¨¶Ë¿ÚÍ£Ö¹×è¶Ï
#define		CONST_qyEventType_nms_newConnection					2006			//  ÐÂÔöÁª½Ó
#define		CONST_qyEventType_nms_connectionModified			2007			//  Áª½Ó±ä¸ü
//  #define		CONST_qyEventType_nms_newConnectionIp				2008			//  ÐÂÔöÁª½ÓIp
//  #define		CONST_qyEventType_nms_connectionIpModified			2009			//  Áª½ÓIP±ä¸ü
#define		CONST_qyEventType_nms_delConnection					2010			//  É¾³ýÒ»¸öÁª½Ó
#define		CONST_qyEventType_nms_warnSpeed						2011			//  Á÷Á¿±¨¾¯£¬2006/05/30
//  Ó¦ÓÃÏµÍ³Ê¹ÓÃÈËÔ±ÊÂ¼þID¶¨Òå
#define		CONST_qyEventType_nm_logon							3000			//  µÇÂ¼
#define		CONST_qyEventType_nm_logoff							3001			//  ÀëÂ¼
#define		CONST_qyEventType_nm_addUsr							3002			//  Ìí¼ÓÓÃ»§
#define		CONST_qyEventType_nm_delUsr							3003			//  É¾³ýÓÃ»§
#define		CONST_qyEventType_nm_modifyUsr						3004			//  ÐÞ¸ÄÓÃ»§
#define		CONST_qyEventType_nm_clearupEvent					3005			//  Çå¿ÕÊÂ¼þ
#define		CONST_qyEventType_nm_pzcz							3006			//  ÅäÖÃ²Ù×÷,  2005/10/01
#define		CONST_qyEventType_nm_sysWarn						3007			//  Ó¦ÓÃÏµÍ³×ÔÐÐ²úÉúµÄ¸æ¾¯£¬2005/10/03
#define		CONST_qyEventType_nm_viewRemoteDesktop				3008			//  Ê¹ÓÃÔ¶³Ì×ÀÃæ£¬2006/02/15
#define		CONST_qyEventType_nm_cancelRemoteDesktop			3009			//  È¡ÏûÔ¶³Ì×ÀÃæ£¬2006/02/15
#define		CONST_qyEventType_nm_denyRd							3010			//  Ô¶³Ì×ÀÃæ±»¾Ü¾ø£¬2006/02/15
#define		CONST_qyEventType_nm_autoAcceptRdAndRdStart			3011			//  ×Ô¶¯Æô¶¯Ô¶³Ì×ÀÃæ
#define		CONST_qyEventType_nm_promptToAcceptRdAndRdStart		3012			//  ÓÃ»§ÔÊÐíÆô¶¯Ô¶³Ì×ÀÃæ
#define		CONST_qyEventType_nm_logonFailed					3013			//  µÇÂ¼Ê§°Ü, 2006/02/25
#define		CONST_qyEventType_nm_export							3014			//  µ¼³ö
#define		CONST_qyEventType_nm_bak							3015			//  ±¸·Ý
#define		CONST_qyEventType_nm_import							3016			//  µ¼Èë
#define		CONST_qyEventType_nm_monDesktop						3017			//  ÊµÊ±¼à¿Ø×ÀÃæ£¬2006/02/15
#define		CONST_qyEventType_nm_cancelMonDesktop				3018			//  È¡ÏûÊµÊ±¼à¿Ø×ÀÃæ£¬2006/02/15
#define		CONST_qyEventType_nm_rdReqTimeout					3019			//  Ô¶³Ì×ÀÃæÎÞÈËÓ¦´ð£¬2006/06/15
#define		CONST_qyEventType_nm_clearupImMsg					3020			//  Çå¿ÕÏûÏ¢
#define		CONST_qyEventType_nm_clearupImHisTask				3021			//  Çå¿ÕÀúÊ·ÈÎÎñ



//  ×Ê²ú¹ÜÀíÊÂ¼þ¶¨Òå
#define		CONST_qyEventType_assetMgr_cpuAdd					3500			//  ÐÂÔöCPU
#define		CONST_qyEventType_assetMgr_cpuDel					3501			//  CPUÒÅÊ§
#define		CONST_qyEventType_assetMgr_memAdd					3502			//  ÐÂÔöÄÚ´æ
#define		CONST_qyEventType_assetMgr_memChanged				3503			//  ÄÚ´æ±ä¸ü
#define		CONST_qyEventType_assetMgr_biosAdd					3504			//  ÐÂÔöBIOS
#define		CONST_qyEventType_assetMgr_biosDel					3505			//  BIOSÒÅÊ§
#define		CONST_qyEventType_assetMgr_monitorAdd				3506			//  ÐÂÔö¼àÊÓÆ÷
#define		CONST_qyEventType_assetMgr_monitorDel				3507			//  ¼àÊÓÆ÷ÒÅÊ§
	//  
#define		CONST_qyEventType_assetMgr_ideDiskAdd				3520			//  ÐÂÔöIDEÓ²ÅÌ
#define		CONST_qyEventType_assetMgr_ideDiskDel				3521			//  IDEÓ²ÅÌÒÅÊ§
#define		CONST_qyEventType_assetMgr_ideCdromAdd				3522			//  ÐÂÔöDVD/CD-ROM
#define		CONST_qyEventType_assetMgr_ideCdromDel				3523			//  DVD/CD-ROMÒÅÊ§
#define		CONST_qyEventType_assetMgr_usbDiskAdd				3524			//  ÐÂÔöUSB´ÅÅÌ
#define		CONST_qyEventType_assetMgr_usbDiskDel				3525			//  USB´ÅÅÌÒÅÊ§
	//
#define		CONST_qyEventType_assetMgr_displayAdd				3550			//  ÐÂÔöÏÔ¿¨
#define		CONST_qyEventType_assetMgr_displayDel				3551			//  ÏÔ¿¨ÒÅÊ§
#define		CONST_qyEventType_assetMgr_networkCardAdd			3552			//  ÐÂÔöÍø¿¨
#define		CONST_qyEventType_assetMgr_networkCardDel			3553			//  Íø¿¨ÒÅÊ§
	//
#define		CONST_qyEventType_assetMgr_softwareAdd				3570			//  ÐÂ×°Èí¼þ
#define		CONST_qyEventType_assetMgr_softwareDel				3571			//  Èí¼þÐ¶ÔØ


////////////////////////////////
//
//

#define		CONST_qyEventType_is_base							20000			//  2007/05/08, mis
//
#define		CONST_qyEventType_im_newMessenger					(  CONST_qyEventType_is_base  +  100  )
//
#define		CONST_qyEventType_im_messengerLogon					(  CONST_qyEventType_is_base  +  110  )
#define		CONST_qyEventType_im_messengerLogoff				(  CONST_qyEventType_is_base  +  111  )
//
#define		CONST_qyEventType_im_connErr						(  CONST_qyEventType_is_base  +  115  )	//  
#define		CONST_qyEventType_im_memoryErr						(  CONST_qyEventType_is_base  +  116  )	//  2011/02/05
//
#define		CONST_qyEventType_im_daemonStart					(  CONST_qyEventType_is_base  +  200  )
#define		CONST_qyEventType_im_daemonStop						(  CONST_qyEventType_is_base  +  201  )






//  CONST_objType_pcEnvµÄÖÖÀà
#define		CONST_pcEnvType_null								0	
#define		CONST_pcEnvType_hardware							1	
#define		CONST_pcEnvType_software							2	
#define		CONST_pcEnvType_registry							3					//  2006/06/12


extern  QY_DMITEM	CONST_pcEnvTypeTable[];


#define		CONST_qnm_maxOfficeNameLen							64
#define		CONST_qnm_maxSubOfficeNameLen						64
#define		CONST_qwm_maxVerLen									8
//
#define		CONST_maxCntAddrLen									67					//  2006/06/29

#if  0  //  2010/04/11
typedef  struct  __qnmCntCfg_t									{
				 unsigned  char									ucbAutoCntIp;		//  2006/06/29
				 char											cntIp[CONST_qyMaxIpLen  +  1];				
				 unsigned  char									ucbSys_cntIp;							//  ÊÇ·ñhkey_local_machineÀïµÄ¡£2009/01/16
				 char											cntAddrs[3][CONST_maxCntAddrLen  +  1];
				 unsigned  char									ucbSys_cntAddrs[3];						//  ÊÇ·ñhkey_local_machineÀïµÄ¡£2009/01/16
				 //
				 unsigned  short								usCntPort;
}		 QNM_CNT_CFG;
#endif

typedef  struct  __qnmCntCfg_t									{
				 unsigned  char									ucbAutoCntIp;		//  2006/06/29
				 char											cntIp[CONST_qyMaxIpLen  +  1];				
				 unsigned  char									ucbSys_cntIp;							//  ÊÇ·ñhkey_local_machineÀïµÄ¡£2009/01/16
				 char											cntAddrs[2][CONST_maxCntAddrLen  +  1];
				 unsigned  char									ucbSys_cntAddrs[2];						//  ÊÇ·ñhkey_local_machineÀïµÄ¡£2009/01/16
				 //
				 unsigned  short								usCntPort;
				 unsigned  char									ucbSys_cntPort;							//  hkey_local_machine;  2010/09/24
				 //
				 TCHAR											usr[256];								//  2019/04/08
				 TCHAR											passwd[256];							//  2019/04/08
				 //
				 unsigned  char									ucbSavePasswd;							//  2019/04/08
				 unsigned  char									ucbAutoLogon;							//  2019/04/08

}		 QNM_CNT_CFG;

typedef  struct  __qwmDynCfg_t									{					//  2006/07/01	
				 QNM_CNT_CFG									cnt;				 
}		 QWM_DYN_CFG;

//
bool  isValid_qwmDynCfg(QWM_DYN_CFG* pDynCfg);


//
#define		CONST_maxPermittedPhoneNums							20
#define		CONST_phoneNumBytes									13
#define		CONST_maxSecChkEventCnt								10000				//  ×î´óµÄÒ»´Î·¢ËÍµÄ¼ì²éÊÂ¼þµÄÌõÄ¿ÊýÏÞÖÆ



typedef  struct  __qyMcRight_t								{
				 BOOL										canLogOn;

			 	 //  char										curUsrName[30  +  1];

				 BOOL										bAdmin;				//  ÏµÍ³¹ÜÀíÔ±×é
				 BOOL										bXtpz;				//  ÏµÍ³ÅäÖÃ×é
				 BOOL										bRzsj;				//  ÈÕÖ¾Éó¼Æ×é  
				 
				 BOOL										bXtpzAdmin;			//  sysGrp×éÄÚ¹ÜÀíÔ±£¬2005/09/30
				 BOOL										bRzsjAdmin;			//  logGrp×éÄÚ¹ÜÀíÔ±£¬2005/09/30

}		 QYMC_RIGHT;


typedef  struct  __qyMcUsr_t								{
				 QY_USR_COMMON								common;
				 char										name[30 + 1];
				 char										tel[16 + 1];
				 QYMC_RIGHT									right;

				 struct										{				 	//  2008/08/04			 
					 TCHAR									zbStr[64  +  1];
					 TCHAR									bbStr[64  +  1];
					 TCHAR									dwStr[64  +  1];
					 TCHAR									bmStr[64  +  1];

					 BOOL									bRestricted;

				 }											scope;

				 struct										{
				 }											status;

}		 QYMC_USR;



//
#define		CONST_objIdStr						"0"			//  Õâ¸öÎª³õÊ¼»¯µÄÖµ,²»ÓÃ¶àÓïÑÔ»¯





 /////////////////////////////////////////
 //
 //  +usageType;+objType;+objId0;+objId1;+objId2;+objIdStr0;+objIdStr1;+objIdStr2
typedef  struct  __qyObjIndexRcd_t				{
				 int							id;							//  ×Ô¶¯Ôö³¤
				 int							usageType;
				 TCHAR							usageName[255  +  1];
				 TCHAR							servName[255  +  1];		//  2007/08/06
				 int							objType;
				 int							objId0;
				 int							objId1;
				 int							objId2;
				 TCHAR							objIdStr0[255  +  1];
				 TCHAR							objIdStr1[255  +  1];
				 TCHAR							objIdStr2[255  +  1];
				 TCHAR							col0[255  +  1];
				 TCHAR							col1[255  +  1];
				 TCHAR							col2[255  +  1];
				 TCHAR							col3[255  +  1];
				 TCHAR							col4[255  +  1];
				 TCHAR							comment[255  +  1];
}		 QY_OBJINDEX_RCD;




//  2005/01/28数据库取参数
#ifdef  DBVT_ASTRING																								
	#define		MACRO_sqlStr(   /*CDBVariant*/varVal,  /*  TCHAR  *  */buf,  size  )  {  CString  str;																									\
																					if  (  varVal.m_dwType  ==  DBVT_STRING  )  str  =  CString(  varVal.m_pstring->GetBuffer(  0  )  );				\
																					else  if  (  varVal.m_dwType  ==  DBVT_ASTRING  )  str  =  CString(  varVal.m_pstringA->GetBuffer(  0  )  );	\
																					else  if  (  varVal.m_dwType  ==  DBVT_WSTRING  )  str  =  CString(  varVal.m_pstringW->GetBuffer(  0  )  );	\
																					else  str  =  CString(  ""  );																						\
																					MACRO_CStringTrim(  str  );  lstrcpyn(  buf,  str.GetBuffer(  0  ),  size  );										\
																					}                                                                                                                                                          													

	#define		MACRO_sqlRawStr(   /*CDBVariant*/varVal,  /*  TCHAR  *  */buf,  size  )  {  CString  str;																									\
																					if  (  varVal.m_dwType  ==  DBVT_STRING  )  str  =  CString(  varVal.m_pstring->GetBuffer(  0  )  );				\
																					else  if  (  varVal.m_dwType  ==  DBVT_ASTRING  )  str  =  CString(  varVal.m_pstringA->GetBuffer(  0  )  );	\
																					else  if  (  varVal.m_dwType  ==  DBVT_WSTRING  )  str  =  CString(  varVal.m_pstringW->GetBuffer(  0  )  );	\
																					else  str  =  CString(  ""  );																						\
																					lstrcpyn(  buf,  str.GetBuffer(  0  ),  size  );										\
																					}                                                                                                                                                          													

#else	//  在VC7里，增加了上述的数据类型，故这样区分，2005/11/08
	#define		MACRO_sqlStr(   /*CDBVariant*/varVal,  /*  TCHAR  *  */buf,  size  )  {  CString  str;																									\
																					if  (  varVal.m_dwType  ==  DBVT_STRING  )  str  =  CString(  varVal.m_pstring->GetBuffer(  0  )  );				\
																					else  str  =  CString(  ""  );																						\
																					MACRO_CStringTrim(  str  );  lstrcpyn(  buf,  str.GetBuffer(  0  ),  size  );										\
																					}                                                                                                                                                          													
	#define		MACRO_sqlRawStr(   /*CDBVariant*/varVal,  /*  TCHAR  *  */buf,  size  )  {  CString  str;																									\
																					if  (  varVal.m_dwType  ==  DBVT_STRING  )  str  =  CString(  varVal.m_pstring->GetBuffer(  0  )  );				\
																					else  str  =  CString(  ""  );																						\
																					lstrcpyn(  buf,  str.GetBuffer(  0  ),  size  );										\
																					}                                                                                                                                                          													

#endif

#define		MACRO_sqlLong(  /*CDBVariant*/varVal,  l  )			if  (  varVal.m_dwType  ==  DBVT_LONG  )  {  l  =  varVal.m_lVal;  }
#define		MACRO_sqlUcb(   /*CDBVarinat*/varVal,  ucb  )		{  TCHAR tBuf[256];  TCHAR  *  pStopString;   ucb  =  FALSE;  MACRO_sqlStr(  varVal,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  if  (  _tcstol(  tBuf,  &pStopString,  10  )  )  ucb  =  TRUE;  }  
#define		MACRO_ucbStr(  ucb  )								(  ucb  ?  _T(  "1"  )  :  _T(  ""  )  )


//

#if  0	//  2010/04/08
	#define		MACRO_htons(s)	s  =  qyhtons(s)
	#define		MACRO_htonl(l)	l  =  qyhtonl(l)
	#define		MACRO_htonl64(  l64  )  l64  =  qyhtonl64(  l64  )

	#define		MACRO_ntohs(s)	s  =  qyntohs(s)
	#define		MACRO_ntohl(l)	l  =  qyntohl(l)
	#define		MACRO_ntohl64(  l64  )  l64  =  qyntohl64(  l64  )		//  2007/05/10
#else
	#define		MACRO_htons(s)	{	short  tmp_s  =  0;  memcpy(  &tmp_s,  &s,  sizeof(  short  )  );  tmp_s  =  qyhtons(tmp_s);  memcpy(  &s,  &tmp_s,  sizeof(  short  )  );  }
	#define		MACRO_htonl(l)	{	long  tmp_l  =  0;  memcpy(  &tmp_l,  &l,  sizeof(  long  )  );  tmp_l  =  qyhtonl(tmp_l);  memcpy(  &l,  &tmp_l,  sizeof(  long  )  );  }
	#define		MACRO_htonl64(  l64  )  {  __int64  tmp_l64  =  0;  memcpy(  &tmp_l64,  &l64,  sizeof(  __int64  )  );  tmp_l64  =  qyhtonl64(  tmp_l64  );  memcpy(  &l64,  &tmp_l64,  sizeof(  __int64  )  );  }

	#define		MACRO_ntohs(s)	{	short  tmp_s  =  0;  memcpy(  &tmp_s,  &s,  sizeof(  short  )  );  tmp_s  =  qyntohs(tmp_s);  memcpy(  &s,  &tmp_s,  sizeof(  short  )  );  }
	#define		MACRO_ntohl(l)	{  long  tmp_l  =  0;  memcpy(  &tmp_l,  &l,  sizeof(  long  )  );  tmp_l  =  qyntohl(tmp_l);  memcpy(  &l,  &tmp_l,  sizeof(  long  )  );  }
	#define		MACRO_ntohl64(  l64  )  {  __int64  tmp_l64  =  0;  memcpy(  &tmp_l64,  &l64,  sizeof(  __int64  )  );  tmp_l64  =  qyntohl64(  tmp_l64  );  memcpy(  &l64,  &tmp_l64,  sizeof(  __int64  )  );  }		//  2007/05/10
#endif

//
DWORD64  qyhtonl64(  DWORD64  x  );		//  2007/05/10
DWORD64  qyntohl64(  DWORD64  x  );

//
//  QY_MESSENGER_ID  //  2007/05/05
#define		MACRO_htonMessengerId(  idInfo  )	{  MACRO_htonl64(  idInfo.ui64Id  );    }
#define		MACRO_ntohMessengerId(  idInfo  )	{  MACRO_ntohl64(  idInfo.ui64Id  );    }


//  2009/09/07
#define		MACRO_SetForegroundWindow(  hWnd  )  {																\
				if  (  ::IsWindow(  hWnd  )  )  {																\
					::ShowWindow(  hWnd,  SW_SHOW  );															\
					if  (  ::IsIconic(  hWnd  )  )  ::SendMessage(  hWnd,  WM_SYSCOMMAND,  SC_RESTORE,  0  );	\
					else  ::SetForegroundWindow(  hWnd  );														\
				}  }



//  ÒÔÏÂÍ¨ÐÅµÄÊý¾Ý°ü¸ñÊ½¡£

#define		CONST_qnmAuthCmd_startSession						0					//  ÊÜ¿Ø¶Ë£¨»òÆäËû£©Á¬½Ó·þÎñÆ÷£¬ÒÔÆô¶¯Ò»¸öÕý³£µÄ»á»°  
#define		CONST_qnmAuthCmd_getHint							1					//  ×¢²á½çÃæÁ¬½Ó·þÎñÆ÷£¬ÒÔÈ¡µÃÌáÊ¾ÐÅÏ¢£¬ÏÞÓÃÔÚnetMc2
#define		CONST_qnmAuthCmd_startProxySession					2					//  ·þÎñÆ÷Á¬½Ó´úÀí£¬ÒÔÆô¶¯´úÀí»á»°
#define		CONST_qnmAuthCmd_guiTalk							3					//  ½çÃæÁ¬½ÓDaemon, ÒÔÍê³ÉÄ³Ð©Ö¸Áî
#define		CONST_qnmAuthCmd_cgiTalk							4					//  cgiÁª½ÓDaemon, ÒÔÍê³ÉwebÏà¹ØµÄ¹¤×÷£¬2007/11/21
#define		CONST_qnmAuthCmd_clientHello						5					//  2008/06/09
//
#define		CONST_qnmAuthCmd_getCaRandom						10					//
#define		CONST_qnmAuthCmd_getCaServCfg						11					//  2023/05/01

//
typedef  struct  __qnmCommAuthInfo_t							{

				 char											ver[CONST_qyMaxVerLen];				 
				 char											macs[CONST_qnmMaxMacs][12];
				 char											otherMacs[255];
				 char											ip[CONST_qyMaxIpLen];

				 //  ÒÔÉÏÊÇ¾É°æ±¾µÄÊý¾Ý³ÉÔ±
				 char											cmd;				//  (1.4)°æ±¾Ç°Óëº¬(1.4)°æ±¾ºóÖ®¼äµÄÖ÷ÒªÊý¾Ý½á¹¹ÉÏµÄÇø±ð
				 unsigned  int									uiQwmType;			//  (0208)ºóÖ§³Ö 

}		 QNM_COMM_AUTHINFO;



#define		CONST_qwmType_null									0
#define		CONST_qwmType_nms									1					//  ¶ÔnmsµÄ¿Í»§¶ËÊ¹ÓÃ
//  #define		CONST_qwmType_secChk								2					//  ÔÝÊ±²»ÓÃ


//////////////  cfgId unsigned short, 64k
//					1 32k
//					2 1000 netMc
//					3  


//  qnm cfgId
//
#define		CONST_qnmCfgId_null									CONST_ancCfgId_null	//  0					//  È¡cfgsµÄ½áÊø·û

//
#if  0
#define		CONST_qnmCfgId_glCntIp								1					//  ¹ÜÀíÖÐÐÄIPµÄÅäÖÃIP
#define		CONST_qnmCfgId_connectIntervalLoops					2					//  Óë¹ÜÀíÖÐÐÄÁªÏµµÄÑ­»·¼ä¸ô
//  #define		CONST_qnmCfgId_rasCmd							3					//  ²¦ºÅÈ¨ÏÞ  
#define		CONST_qnmCfgId_rasRule								4					//  ´øµç»°ºÅÂëµÄ²¦ºÅ¹æÔò
#define		CONST_qnmCfgId_stopMon								5					//  Ð¶ÔØµ¥Ì¨ÊÜ¿Ø¶ËÈí¼þ
//  #define		CONST_qnmCfgId_mgrProxy							6					//  Í£Ö¹Ð¶ÔØ¹ÜÀí´úÀíµÄ¹¦ÄÜ
//  #define		CONST_qnmCfgId_startIpScan						7					//  Æô¶¯IPÉ¨Ãè
//  #define		CONST_qnmCfgId_startRegScan						8					//  Æô¶¯×¢²á¼ì²é
//  #define		CONST_qnmCfgId_vlan								9					//	vlanÉèÖÃ
#define		CONST_qnmCfgId_secChk								10
#define		CONST_qnmCfgId_interMon								11					//  ¼àÊÓ¶ËIPºÍport
#define		CONST_qnmCfgId_devRule								12					//  ÍâÉè¹ÜÀí
#define		CONST_qnmCfgId_intervals							13					//  ÏÂÔØÅäÖÃ¡¢ÉÏ´«ÍøÂçÅäÖÃµÈ¸÷ÖÖ¼ä¸ô(ÒÔÃëÎªµ¥Î»), 2005/06/10
#define		CONST_qnmCfgId_osRule								14					//  ¹ÜÀí²Ù×÷ÏµÍ³µÄ¹æÔò£¬2005/06/25
#define		CONST_qnmCfgId_osAuditRule							15					//  ²Ù×÷ÏµÍ³Éó¼Æ¹æÔò
#define		CONST_qnmCfgId_opRule								16					//  ÊµÊ±²Ù×÷¹æÔò£¬2006/02/11
#define		CONST_qnmCfgId_pcMon								17					//  ¼à¿Ø¹æÔò£¬2006/03/05
#define		CONST_qnmCfgId_pcNetFlow							18					//  Á÷Á¿¹ÜÀí¹æÔò£¬2006/09/11
#endif 

// netMc 2007/04/02

//  CONST_qnmCfgId_start=
//					
//					CONST_qnmCfgId_null

// 2007/04/02
//#define		CONST_qnmCfgId_base_common							1000

//
//  CONST_qnmCfgId_base_common  ->  CONST_qnmCfgId_base_common  +  999
#define		CONST_qnmCfgId_start								CONST_ancCfgId_start		//(  CONST_qnmCfgId_base_common  +  100  )
#define		CONST_qnmCfgId_mem									CONST_ancCfgId_mem			//(  CONST_qnmCfgId_base_common  +  101  )				//  2007/08/05, 只用在小而快的数据包。一般的包的成员要使用CONST_imCommType_mem
//
//

//
//
//
//  
#define		CONST_qnmCfgId_clientVer							(  CONST_qnmCfgId_base_common  +  2009  )
#define		CONST_qnmCfgId_authCmd								(  CONST_qnmCfgId_base_common  +  2010  )
//  #define		CONST_qnmCfgId_uiQwmType							(  CONST_qnmCfgId_base_common  +  2011  )
#define		CONST_qnmCfgId_uiObjType							(  CONST_qnmCfgId_base_common  +  2011  )				//  2007/12/07, qwmType¸objType
#define		CONST_qnmCfgId_iCustemId							(  CONST_qnmCfgId_base_common  +  2012  )
#define		CONST_qnmCfgId_uiChannelType						(  CONST_qnmCfgId_base_common  +  2013  )				//  2007/07/08
//
//  #define		CONST_qnmCfgId_uiDevType						(  CONST_qnmCfgId_base_common  +  2014  )				//  2007/08/03, messenger
#define		CONST_qnmCfgId_uiDevType_from						(  CONST_qnmCfgId_base_common  +  2014  )				//  2007/08/03, messenger
#define		CONST_qnmCfgId_uiDevType_to							(  CONST_qnmCfgId_base_common  +  2015  )				//  2008/01/06, messenger
//#define		CONST_qnmCfgId_wDevIdStr_from						(  CONST_qnmCfgId_base_common  +  2016  )				//  2008/01/06, from from uiDevType_from uiDevType
//#define		CONST_qnmCfgId_wDevIdStr_to							(  CONST_qnmCfgId_base_common  +  2017  )				//  2008/01/06
//#define		CONST_qnmCfgId_wReversePath							(  CONST_qnmCfgId_base_common  +  2018  )				//  2008/02/08
//#define		CONST_qnmCfgId_wForwardPath							(  CONST_qnmCfgId_base_common  +  2019  )				//  2008/02/08
//
#define		CONST_qnmCfgId_usAuthType							(  CONST_qnmCfgId_base_common  +  2020  )				//  2011/03/22
#define		CONST_qnmCfgId_iAppType								(  CONST_qnmCfgId_base_common  +  2021	)				//  2011/03/27
//
#define		CONST_qnmCfgId_shVer								(  CONST_qnmCfgId_base_common  +  2023  )				//  2014/09/23
#define		CONST_qnmCfgId_subSystemId							(  CONST_qnmCfgId_base_common  +  2024  )				//  2017/06/21

//
#define		CONST_qnmCfgId_uiFieldId							(  CONST_qnmCfgId_base_common  +  2100  )				//  2007/07/31
//
#define		CONST_qnmCfgId_usCnt								CONST_ancCfgId_usCnt									//  (  CONST_qnmCfgId_base_common  +  2101  )				//  2007/08/01
//
#define		CONST_qnmCfgId_ucbNext								(  CONST_qnmCfgId_base_common  +  2102  )				//  2007/08/03
#define		CONST_qnmCfgId_ucbEnd								(  CONST_qnmCfgId_base_common  +  2103  )				//  2007/08/03
//#define		CONST_qnmCfgId_tStartTime_serv						(  CONST_qnmCfgId_base_common  +  2104  )				//  tStartTime_serv uiSerialNo
#define		CONST_qnmCfgId_uiSerialNo							(  CONST_qnmCfgId_base_common  +  2105  )				//  2007/09/01
#define		CONST_qnmCfgId_ucbResp								(  CONST_qnmCfgId_base_common  +  2106  )				//  2007/12/22, 
#define		CONST_qnmCfgId_ucbNeedDetail						(  CONST_qnmCfgId_base_common  +  2107  )				//  2007/12/22, 
#define		CONST_qnmCfgId_ucbNeedResp							(  CONST_qnmCfgId_base_common  +  2108  )				//  2008/04/21, 
#define		CONST_qnmCfgId_index								(  CONST_qnmCfgId_base_common  +  2109  )				//  2008/10/30. 这里的index应理解为某项数据的唯一的标识，不应理解为数组的索引。在网络协议里，数组的索引没有意义。
//
#define		CONST_qnmCfgId_uiLen								CONST_ancCfgId_uiLen									//  (  CONST_qnmCfgId_base_common  +  2110  )				//  2008/10/30
//
#define		CONST_qnmCfgId_ucbRetrieveAll						(  CONST_qnmCfgId_base_common  +  2111  )				//  2010/08/17
//  
#define		CONST_qnmCfgId_subtype								(  CONST_qnmCfgId_base_common  +  2112  )				//  2011/01/28
#define		CONST_qnmCfgId_ucbReply								(  CONST_qnmCfgId_base_common  +  2113  )				//  2012/08/06
#define		CONST_qnmCfgId_ucbRetrieveOne						(  CONST_qnmCfgId_base_common  +  2114  )				//  2014/09/04. 
#define		CONST_qnmCfgId_help_subIndex						(  CONST_qnmCfgId_base_common  +  2115  )				//  2016/07/23
//
//#define		CONST_qnmCfgId_ucbAvConsole							(  CONST_qnmCfgId_base_common  +  2116  )				//  2017/06/11
//
#define		CONST_qnmCfgId_ucbVideoConference					(  CONST_qnmCfgId_base_common  +  2117  )				//  2017/08/02
#define		CONST_qnmCfgId_usConfType							(  CONST_qnmCfgId_base_common  +  2118  )				//  2017/08/25
#define		CONST_qnmCfgId_usAvLevel							(  CONST_qnmCfgId_base_common  +  2119  )				//  2011/08/15
//
#define		CONST_qnmCfgId_nStep								(  CONST_qnmCfgId_base_common  +  2120  )				//  

//
//
#define		CONST_qnmCfgId_mac									(  CONST_qnmCfgId_base_common  +  2300  )				//  
#define		CONST_qnmCfgId_ulIp									(  CONST_qnmCfgId_base_common  +  2301  )				//  ulIp 
#define		CONST_qnmCfgId_ip6									(  CONST_qnmCfgId_base_common  +  2302  )				//  reserved
#define		CONST_qnmCfgId_pcName								(  CONST_qnmCfgId_base_common  +  2303  )
#define		CONST_qnmCfgId_domainName							(  CONST_qnmCfgId_base_common  +  2304  )
#define		CONST_qnmCfgId_osUsrName							(  CONST_qnmCfgId_base_common  +  2305  )
#define		CONST_qnmCfgId_langId								(  CONST_qnmCfgId_base_common  +  2306  )
#define		CONST_qnmCfgId_iPlatformId							(  CONST_qnmCfgId_base_common  +  2307  )
#define		CONST_qnmCfgId_categoryId							(  CONST_qnmCfgId_base_common  +  2308  )				//  2011/04/05

//
#define		CONST_qnmCfgId_hint									(  CONST_qnmCfgId_base_common  +  2400  )				//  2007/04/22
#define		CONST_qnmCfgId_clientWelcomeMsg						(  CONST_qnmCfgId_base_common  +  2401  )				//  2016/08/10
//
#define		CONST_qnmCfgId_ucbDaemonDemo						(  CONST_qnmCfgId_base_common  +  2410  )				//  2009/10/11
#define		CONST_qnmCfgId_usMaxVideoConferenceMems				(  CONST_qnmCfgId_base_common  +  2411  )				//  2009/11/05
#define		CONST_qnmCfgId_ucDays_left							(  CONST_qnmCfgId_base_common  +  2412  )				//  2010/03/22
//
#define		CONST_qnmCfgId_uiCommEncCtxType						(  CONST_qnmCfgId_base_common  +  2450  )				//  2008/ 06/09
#define		CONST_qnmCfgId_publicKeyBlob						(  CONST_qnmCfgId_base_common  +  2451  )				//  2008/06/09
#define		CONST_qnmCfgId_sessionKeyBlob						(  CONST_qnmCfgId_base_common  +  2452  )				//  2008/06/10
#define		CONST_qnmCfgId_usSessionEncType						(  CONST_qnmCfgId_base_common  +  2453  )
#define		CONST_qnmCfgId_sessionIv							(  CONST_qnmCfgId_base_common  +  2454  )

//
#define		CONST_qnmCfgId_messengerId							CONST_ancCfgId_messengerId								//  (  CONST_qnmCfgId_base_common  +  2500  )

//
#define		CONST_qnmCfgId_idInfo_grp1							(  CONST_qnmCfgId_base_common  +  2501  )				//  2007/08/26
//
#define		CONST_qnmCfgId_idInfo_logicalPeer					(  CONST_qnmCfgId_base_common  +  2502  )				//  file server  需要使用logicalPeer的概念。其他的应该使用grp_related. 
//
#define		CONST_qnmCfgId_idInfo_grp_related					(  CONST_qnmCfgId_base_common  +  2503  )				//  2015/07/30. 
#define		CONST_qnmCfgId_idInfo_resServ						(  CONST_qnmCfgId_base_common  +  2504  )				//  2015/08/01
#define		CONST_qnmCfgId_idInfo_sender						(  CONST_qnmCfgId_base_common  +  2505  )				//  2015/08/07
#define		CONST_qnmCfgId_idInfo_creator						(  CONST_qnmCfgId_base_common  +  2506  )				//  2017/07/27
#define		CONST_qnmCfgId_idInfo_initiator						(  CONST_qnmCfgId_base_common  +  2507  )
#define		CONST_qnmCfgId_idInfo_mcu							(  CONST_qnmCfgId_base_common  +  2508  )
#define		CONST_qnmCfgId_idInfo_conf							(  CONST_qnmCfgId_base_common  +  2509  )
#define		CONST_qnmCfgId_idInfo_compere						(  CONST_qnmCfgId_base_common  +  2510  )
//
#define		CONST_qnmCfgId_idInfo_requester						(  CONST_qnmCfgId_base_common  +  2511  )
//
#define		CONST_qnmCfgId_idInfo_nvr						(  CONST_qnmCfgId_base_common  +  2512  )

//
#define		CONST_qnmCfgId_messengerName						(  CONST_qnmCfgId_base_common  +  2610  )				//  messengerName
#define		CONST_qnmCfgId_messengerPasswd						(  CONST_qnmCfgId_base_common  +  2611  )				//  messengerPassword

//
#define		CONST_qnmCfgId_wRndName_serv						(  CONST_qnmCfgId_base_common  +  2616  )				//  2007/11/22
#define		CONST_qnmCfgId_uiRnd_cli							(  CONST_qnmCfgId_base_common  +  2617  )				//  2007/11/22
//  #define		CONST_qnmCfgId_uiWebSessId						(  CONST_qnmCfgId_base_common  +  2618  )				//  2007/11/22
#define		CONST_qnmCfgId_uiLogonId							(  CONST_qnmCfgId_base_common  +  2618  )				//  2007/11/22
//
#define		CONST_qnmCfgId_grpDisplayName						(  CONST_qnmCfgId_base_common  +  2620  )				//  2007/11/22
#define		CONST_qnmCfgId_displayName							(  CONST_qnmCfgId_base_common  +  2621  )				//  2007/11/22
#define		CONST_qnmCfgId_wAdvertisement						(  CONST_qnmCfgId_base_common  +  2622  )				//  2008/03/02
#define		CONST_qnmCfgId_talkerDesc							(  CONST_qnmCfgId_base_common  +  2623  )				//  2011/04/07
//
//  MSG_ROUTE
#define		CONST_qnmCfgId_messengerId_from						CONST_ancCfgId_messengerId_from		//  (  CONST_qnmCfgId_base_common  +  2640  )				//  2007/11/29
#define		CONST_qnmCfgId_messengerId_to						CONST_ancCfgId_messengerId_to		//  (  CONST_qnmCfgId_base_common  +  2641  )				//  2007/11/29
//
//#define		CONST_qnmCfgId_messengerId_replyTo					(  CONST_qnmCfgId_base_common  +  2642  )				//  2007/11/29
//
#define		CONST_qnmCfgId_uiMsgRouteId							CONST_ancCfgId_uiMsgRouteId			//  (  CONST_qnmCfgId_base_common  +  2650  )				//  2008/05/27

//
//  3000 - 3499
//
#define		CONST_qnmCfgId_tCreationTime						(  CONST_qnmCfgId_base_common  +  3098  )				//  2015/08/12
//
#define		CONST_qnmCfgId_tLastModifiedTime					(  CONST_qnmCfgId_base_common  +  3099  )				//  2009/08/24
#define		CONST_qnmCfgId_tLastRefreshedTime					(  CONST_qnmCfgId_base_common  +  3100  )
#define		CONST_qnmCfgId_idInfo_lastRefreshed					(  CONST_qnmCfgId_base_common  +  3101  )
#define		CONST_qnmCfgId_idInfo_grp_lastRefreshed				(  CONST_qnmCfgId_base_common  +  3102  )				//  2007/08/26, ½ÇÉ«
//
#define		CONST_qnmCfgId_usRunningStatus						(  CONST_qnmCfgId_base_common  +  3110  )
#define		CONST_qnmCfgId_ulDetectedIp							(  CONST_qnmCfgId_base_common  +  3111  )
#define		CONST_qnmCfgId_tLastCommTime						(  CONST_qnmCfgId_base_common  +  3112  )				//  2007/12/23, webMessengerÓÃµÄ£®
#define		CONST_qnmCfgId_wLocation							(  CONST_qnmCfgId_base_common  +  3113  )				//  2007/12/23, webMessengerÓÃµÄ£¬±íIP¶ÔÓ¦µÄµØ·½£®
//
#define		CONST_qnmCfgId_usMaxMemsPerSnd						(  CONST_qnmCfgId_base_common  +  3120  )				//  2007/08/26
#define		CONST_qnmCfgId_iRole								(  CONST_qnmCfgId_base_common  +  3122  )				//  2007/08/26, ½ÇÉ«


// 3500 - 3999
#define		CONST_qnmCfgId_ui64FileLen							(  CONST_qnmCfgId_base_common  +  3500  )				//  2007/09/03
#define		CONST_qnmCfgId_fileName								(  CONST_qnmCfgId_base_common  +  3501  )				//  2007/09/03
#define		CONST_qnmCfgId_usOp									(  CONST_qnmCfgId_base_common  +  3502  )				//  2007/09/03
#define		CONST_qnmCfgId_tStartTime_org						(  CONST_qnmCfgId_base_common  +  3503  )				//  2007/09/03
#define		CONST_qnmCfgId_uiTranNo_org							(  CONST_qnmCfgId_base_common  +  3504  )				//  2007/09/03
#define		CONST_qnmCfgId_uiSerialNo_org						(  CONST_qnmCfgId_base_common  +  3505  )				//  2007/09/03
#define		CONST_qnmCfgId_uiSizePerSnd							(  CONST_qnmCfgId_base_common  +  3506  )				//  2007/09/03
#define		CONST_qnmCfgId_uiDataBlockIndex						(  CONST_qnmCfgId_base_common  +  3507  )				//  2007/09/04
//  #define		CONST_qnmCfgId_fileData								(  CONST_qnmCfgId_base_common  +  3508  )				//  2007/09/04
//
#define		CONST_qnmCfgId_rawData								CONST_ancCfgId_rawData									//  (  CONST_qnmCfgId_base_common  +  3508  )				//  2008/03/23
//
#define		CONST_qnmCfgId_uiVerifyMethod						(  CONST_qnmCfgId_base_common  +  3509  )				//  2007/09/04
#define		CONST_qnmCfgId_uiContentType_org					(  CONST_qnmCfgId_base_common  +  3510  )				//  2008/05/31
#define		CONST_qnmCfgId_usCmd_org							(  CONST_qnmCfgId_base_common  +  3511  )				//  2009/10/19
#define		CONST_qnmCfgId_usOp_org								(  CONST_qnmCfgId_base_common  +  3512  )				//  2009/10/19
//
#define		CONST_qnmCfgId_ucbSaveVideo							(  CONST_qnmCfgId_base_common  +  3513  )				//  2014/08/04. 这个值其实不应该放在这里.
#define		CONST_qnmCfgId_us_nBlocks							(  CONST_qnmCfgId_base_common  +  3514  )
//
#define		CONST_qnmCfgId_MAX_FILE_SEND_BLOCK					(  CONST_qnmCfgId_base_common  +  3515  )

//
#define		CONST_qnmCfgId_usIntervalInS_refreshRecentFriends	(  CONST_qnmCfgId_base_common  +  3530  )				//  2007/09/20
#define		CONST_qnmCfgId_usIntervalInS_refreshContactList		(  CONST_qnmCfgId_base_common  +  3531  )				//  2007/09/20


// 4000 - 4999
#define		CONST_qnmCfgId_usMaxFps_toShareBmp					(  CONST_qnmCfgId_base_common  +  4035  )				//  2014/08/07
//
//#define		CONST_qnmCfgId_usCntLimit_mems_from					(  CONST_qnmCfgId_base_common  +  4036  )				//  2009/05/30
#define		CONST_qnmCfgId_uiBytesRecorded_perBlockAlign		(  CONST_qnmCfgId_base_common  +  4037  )				//  2009/05/24
//
#define		CONST_qnmCfgId_usMaxFps_toShareBmp_conf				(  CONST_qnmCfgId_base_common  +  4038  )				//  2009/04/19
#define		CONST_qnmCfgId_conf_usFps							CONST_qnmCfgId_usMaxFps_toShareBmp_conf

//
#define		CONST_qnmCfgId_ucVideoCompressors					(  CONST_qnmCfgId_base_common  +  4039  )				//  2009/03/30
#define		CONST_qnmCfgId_uiTaskType							(  CONST_qnmCfgId_base_common  +  4040  )				//  2007/10/07							//  
#define		CONST_qnmCfgId_ulIp_caller							(  CONST_qnmCfgId_base_common  +  4041  )				//  IP
#define		CONST_qnmCfgId_usCapDriverIndex						(  CONST_qnmCfgId_base_common  +  4042  )				//  2008/03/23
//
//#define	CONST_qnmCfgId_fourccStr							(  CONST_qnmCfgId_base_common  +  4043  )				//  
#define		CONST_qnmCfgId_iFourcc								(  CONST_qnmCfgId_base_common  +  4043  )				//  
//
#define		CONST_qnmCfgId_bih_compress							(  CONST_qnmCfgId_base_common  +  4044  )				//  bitmapInfoHeader
#define		CONST_qnmCfgId_bih_decompress						(  CONST_qnmCfgId_base_common  +  4045  )				//  bitmapInfoHeader
#define		CONST_qnmCfgId_usFps								(  CONST_qnmCfgId_base_common  +  4046  )				//  
#define		CONST_qnmCfgId_wf_compress							(  CONST_qnmCfgId_base_common  +  4047  )				//  2008/06/15
#define		CONST_qnmCfgId_wf_decompress						(  CONST_qnmCfgId_base_common  +  4048  )				//  2009/04/27
#define		CONST_qnmCfgId_ucAudioCompressors					(  CONST_qnmCfgId_base_common  +  4049  )				//  2009/05/17

//
#define		CONST_qnmCfgId_uiTranNo_openVideoDev				CONST_ancCfgId_uiTranNo_openVideoDev					//  (  CONST_qnmCfgId_base_common  +  4050  )				//  

//
#define		CONST_qnmCfgId_uiTranNo_openAudioDev				CONST_ancCfgId_uiTranNo_openAudioDev					//  (  CONST_qnmCfgId_base_common  +  4051  )				//  

//#define		CONST_qnmCfgId_ucbFlippedImg						(  CONST_qnmCfgId_base_common  +  4052  )				//  2011/12/11
#define		CONST_qnmCfgId_spsPps								(  CONST_qnmCfgId_base_common  +  4053  )				//  2014/03/30
//
#define		CONST_qnmCfgId_uiSampleTimeInMs						CONST_ancCfgId_uiSampleTimeInMs							//  (  CONST_qnmCfgId_base_common  +  4054  )				//  2009/05/04
//
#define		CONST_qnmCfgId_ui_rtTimeLen							(  CONST_qnmCfgId_base_common  +  4055  )				//  2009/05/27
//#define	CONST_qnmCfgId_uiSampleTimeInMs_org					(  CONST_qnmCfgId_base_common  +  4056  )				//  2009/05/04
//
#define		CONST_qnmCfgId_uiPts								CONST_ancCfgId_uiPts									//  (  CONST_qnmCfgId_base_common  +  4057  )				//  2015/01/15
//
#define		CONST_qnmCfgId_ucbKeyFrame							CONST_ancCfgId_ucbKeyFrame								//  (CONST_qnmCfgId_base_common + 4058)

//
#define		CONST_qnmCfgId_tLastTime_showFrameInfo_020534		(  CONST_qnmCfgId_base_common  +  4060  )				//  
#define		CONST_qnmCfgId_usCnt_pkts							(  CONST_qnmCfgId_base_common  +  4061  )				//  
#define		CONST_qnmCfgId_tSelectTime							(  CONST_qnmCfgId_base_common  +  4062  )				//  2008/12/05
#define		CONST_qnmCfgId_usDiff_pkts							(  CONST_qnmCfgId_base_common  +  4063  )				//  2009/04/18

//
#define		CONST_qnmCfgId_ucbNeedKeyFrameFirst						(CONST_qnmCfgId_base_common + 4070)

//
#define		CONST_qnmCfgId_usMaxSpeakers							(  CONST_qnmCfgId_base_common  +  4201  )				//  2009/05/31
#define		CONST_qnmCfgId_usIndex_speaker							(  CONST_qnmCfgId_base_common  +  4202  )				//  2013/07/18
#define		CONST_qnmCfgId_conf_iFourcc								(  CONST_qnmCfgId_base_common  +  4203  )				//  
//
#define		CONST_qnmCfgId_ucHardwareAccl							(  CONST_qnmCfgId_base_common  +  4204  )
//
#define		CONST_qnmCfgId_usLayoutType								(  CONST_qnmCfgId_base_common  +  4205  )				//  2010/12/27	
//
//#define		CONST_qnmCfgId_ucb2Streams								(  CONST_qnmCfgId_base_common  +  4206  )
//
#define		CONST_qnmCfgId_meetingId_hg								(  CONST_qnmCfgId_base_common  +  4207  )			//		
#define		CONST_qnmCfgId_meetingType_hg							(  CONST_qnmCfgId_base_common  +  4208  )			//		
#define		CONST_qnmCfgId_meetingRecord_hg							(  CONST_qnmCfgId_base_common  +  4209  )
#define		CONST_qnmCfgId_meetingShare_2ndStream_hg				(  CONST_qnmCfgId_base_common  +  4210  )
#define		CONST_qnmCfgId_shareMem_hg								(  CONST_qnmCfgId_base_common  +  4211  )
#define		CONST_qnmCfgId_meetingLevel_hg							(  CONST_qnmCfgId_base_common  +  4212  )
#define		CONST_qnmCfgId_meetingDuration_hg						(  CONST_qnmCfgId_base_common  +  4213  )
#define		CONST_qnmCfgId_iHkStatus								(  CONST_qnmCfgId_base_common  +  4214  )			//  2023/05/03
#define		CONST_qnmCfgId_meetingStartTime_hg						(  CONST_qnmCfgId_base_common  +  4215  )
#define		CONST_qnmCfgId_meetingCompere_hg						(  CONST_qnmCfgId_base_common  +  4216  )
#define		CONST_qnmCfgId_ucbNvr									(  CONST_qnmCfgId_base_common  +  4217  )
#define		CONST_qnmCfgId_bFlow512k_hg								(  CONST_qnmCfgId_base_common  +  4218  )
#define		CONST_qnmCfgId_conf_bitrateInKbps_dl					(  CONST_qnmCfgId_base_common  +  4219  )			//  2024/02/05
#define		CONST_qnmCfgId_conf_bitrateInKbps_ul					(  CONST_qnmCfgId_base_common  +  4220  )			//  2024/02/05
#define		CONST_qnmCfgId_shareDevice_grp_index					(  CONST_qnmCfgId_base_common  +  4221  )
#define		CONST_qnmCfgId_gpu_usIndex								(  CONST_qnmCfgId_base_common  +  4222  )			//  2024/10/20
//
#define		CONST_qnmCfgId_bLive									(  CONST_qnmCfgId_base_common  +  4223  )
#define		CONST_qnmCfgId_liveUrl									(  CONST_qnmCfgId_base_common  +  4224  )
//
#define		CONST_qnmCfgId_zcr_hg									(  CONST_qnmCfgId_base_common  +  4225  )
//
#define		CONST_qnmCfgId_conf_ucb100k								(  CONST_qnmCfgId_base_common  +  4226  )			//  
//
#define		CONST_qnmCfgId_conf_ucAudioCompressors					(  CONST_qnmCfgId_base_common  +  4227  )			//  



//  2014/08/15
#define		CONST_qnmCfgId_iWidth_pic_conf							(  CONST_qnmCfgId_base_common  +  4230  )			//  2014/08/15
#define		CONST_qnmCfgId_iHeight_pic_conf							(  CONST_qnmCfgId_base_common  +  4231  )			//  2014/08/15
//
//#define		CONST_qnmCfgId_ucbShowBgWall_starter					(  CONST_qnmCfgId_base_common  +  4232  )			//  2016/03/26
//
#define		CONST_qnmCfgId_width									(  CONST_qnmCfgId_base_common  +  4233  )			//  2017/06/12
#define		CONST_qnmCfgId_height									(  CONST_qnmCfgId_base_common  +  4234  )			//  2017/06/12
#define		CONST_qnmCfgId_ucbConfCtrl_starter						(  CONST_qnmCfgId_base_common  +  4235  )			//  2017/07/06


//
#define		CONST_qnmCfgId_uiTranNo_avTask_starter					(  CONST_qnmCfgId_base_common  +  4250  )			//  2014/11/22
#define		CONST_qnmCfgId_ucAvFlg									(  CONST_qnmCfgId_base_common  +  4251  )			//  2015/03/12


//
#define		CONST_qnmCfgId_startTime_task							(  CONST_qnmCfgId_base_common  +  4300  )
#define		CONST_qnmCfgId_usMcuType								(  CONST_qnmCfgId_base_common  +  4301  )

//
//
#define		CONST_qnmCfgId_ca_sendData								(  CONST_qnmCfgId_base_common  +  4492  )
#define		CONST_qnmCfgId_ca_usrName								(  CONST_qnmCfgId_base_common  +  4493  )
#define		CONST_qnmCfgId_ca_tmp_passwd							(  CONST_qnmCfgId_base_common  +  4494  )				//  2023/05/16
//
#define		CONST_qnmCfgId_sxrz_servReply							(  CONST_qnmCfgId_base_common  +  4500  )
#define		CONST_qnmCfgId_sxrz_cliData								(  CONST_qnmCfgId_base_common  +  4501  )
#define		CONST_qnmCfgId_sHgCmd									(  CONST_qnmCfgId_base_common  +  4502  )
#define		CONST_qnmCfgId_ca_random								(  CONST_qnmCfgId_base_common  +  4503  )
#define		CONST_qnmCfgId_caGwCfg									(  CONST_qnmCfgId_base_common  +  4504  )


//
#define		CONST_qnmCfgId_usEnlargeType							(  CONST_qnmCfgId_base_common  +  4600  )				//  
#define		CONST_qnmCfgId_iChannel									(  CONST_qnmCfgId_base_common  +  4601  )
#define		CONST_qnmCfgId_ip										(  CONST_qnmCfgId_base_common  +  4602  )
#define		CONST_qnmCfgId_mouseStatus								(  CONST_qnmCfgId_base_common  +  4603  )
#define		CONST_qnmCfgId_ucbOneBigLayout							(  CONST_qnmCfgId_base_common  +  4604  )
#define		CONST_qnmCfgId_messengerId_oneBig						(  CONST_qnmCfgId_base_common  +  4605  )
#define		CONST_qnmCfgId_ii										(  CONST_qnmCfgId_base_common  +  4606  )
#define		CONST_qnmCfgId_curr_idinfo								(  CONST_qnmCfgId_base_common  +  4607  )
#define		CONST_qnmCfgId_enlarge_x								(  CONST_qnmCfgId_base_common  +  4608  )
#define		CONST_qnmCfgId_enlarge_y								(  CONST_qnmCfgId_base_common  +  4609  )
#define		CONST_qnmCfgId_phone_usEnlargeType						(  CONST_qnmCfgId_base_common  +  4610  )	
#define		CONST_qnmCfgId_amplificationType						(  CONST_qnmCfgId_base_common  +  4611  )	
#define		CONST_qnmCfgId_channelName								(  CONST_qnmCfgId_base_common  +  4612  )	


// 5000 - 5999
#define		CONST_qnmCfgId_uiVDevId									(  CONST_qnmCfgId_base_common  +  5000  )				//  2008/01/25
#define		CONST_qnmCfgId_name										(  CONST_qnmCfgId_base_common  +  5001  )				//  2009/08/25
#define		CONST_qnmCfgId_model									(  CONST_qnmCfgId_base_common  +  5002  )				//  2008/01/25
#define		CONST_qnmCfgId_smsc										(  CONST_qnmCfgId_base_common  +  5003  )				//  2008/01/25
#define		CONST_qnmCfgId_status									(  CONST_qnmCfgId_base_common  +  5004  )				//  2008/01/25
#define		CONST_qnmCfgId_cusName									(  CONST_qnmCfgId_base_common  +  5005  )				//  2008/01/25
#define		CONST_qnmCfgId_ucbDefaultSmServer						(  CONST_qnmCfgId_base_common  +  5006  )				//  2008/01/25

//
#define		CONST_qnmCfgId_wDevIdStr_lastRefreshed					(  CONST_qnmCfgId_base_common  +  5020  )				//  2008/02/01

//
#define		CONST_qnmCfgId_usRaType									(  CONST_qnmCfgId_base_common  +  5050  )				//  2008/11/15
#define		CONST_qnmCfgId_ucButtonMask								(  CONST_qnmCfgId_base_common  +  5051  )				
#define		CONST_qnmCfgId_x										(  CONST_qnmCfgId_base_common  +  5052  )				//  2008/11/12. x×ø±ê
#define		CONST_qnmCfgId_y										(  CONST_qnmCfgId_base_common  +  5053  )				//  2008/11/12  y×ø±ê
//  2016/12/26
//#define		CONST_qnmCfgId_uiEventId_unused							(  CONST_qnmCfgId_base_common  +  2854  )				//  ÊÂ¼þµÄ±êÊ¶¡£
//
#define		CONST_qnmCfgId_key										(  CONST_qnmCfgId_base_common  +  5056  )				//  ¼üÖµ
#define		CONST_qnmCfgId_ucbDown									(  CONST_qnmCfgId_base_common  +  5057  )				//  ÊÇ·ñ°´ÏÂ


//
#define		CONST_qnmCfgId_uiTranNo_retrieveAll						(  CONST_qnmCfgId_base_common  +  5170  )			//  2017/09/17
#define		CONST_qnmCfgId_usSeqNo_retrievePart						(  CONST_qnmCfgId_base_common  +  5171  )			//  2017/09/17
#define		CONST_qnmCfgId_usSeqNo									(  CONST_qnmCfgId_base_common  +  5172  )			//  2017/09/17


// 6000 - 
//  #define		CONST_qnmCfgId_										(  (  CONST_qnmCfgId_base_common  +  6000  )		//  
#define		CONST_qnmCfgId_uiRuleType								(  CONST_qnmCfgId_base_common  +  6001  )
#define		CONST_qnmCfgId_nCmd										(  CONST_qnmCfgId_base_common  +  6002  )

//  gps
#define		CONST_qnmCfgId_iLaInM10000f								(  CONST_qnmCfgId_base_common  +  6200  )			//  4200. 2012/04/20
#define		CONST_qnmCfgId_iLoInM10000f								(  CONST_qnmCfgId_base_common  +  6201  )			//  

//  ptz
#define		CONST_qnmCfgId_nAddr									(  CONST_qnmCfgId_base_common  +  6300  )			//  4300, 2012/08/07
#define		CONST_qnmCfgId_nPelcoType								(  CONST_qnmCfgId_base_common  +  6301  )			//  
//
#define		CONST_qnmCfgId_xTop										(  CONST_qnmCfgId_base_common  +  6310  )
#define		CONST_qnmCfgId_yTop										(  CONST_qnmCfgId_base_common  +  6311  )
#define		CONST_qnmCfgId_xBottom									(  CONST_qnmCfgId_base_common  +  6312  )
#define		CONST_qnmCfgId_yBottom									(  CONST_qnmCfgId_base_common  +  6313  )





//  2014/08/28
#define		CONST_qnmCfgId_usTaskProcObjType						(  CONST_qnmCfgId_base_common  +  6400  )			//  4400. 2014/08/28


//  2015/08/13
#define		CONST_qnmCfgId_ucbP2p									(  CONST_qnmCfgId_base_common  +  6504  )				//  4504.  //  2015/08/05
#define		CONST_qnmCfgId_index_page								(  CONST_qnmCfgId_base_common  +  6505  )
#define		CONST_qnmCfgId_max_usCnt								(  CONST_qnmCfgId_base_common  +  6506  )				//  max of usCnt
#define		CONST_qnmCfgId_keyword									(  CONST_qnmCfgId_base_common  +  6507  )				//  


//
#define		CONST_qnmCfgId_testSpeed_data							(  CONST_qnmCfgId_base_common  +  6620  )	//  2016/12/01

//
#define		CONST_qnmCfgId_mcuUsrName								(  CONST_qnmCfgId_base_common  +  6700  )
#define		CONST_qnmCfgId_mcuPasswd								(  CONST_qnmCfgId_base_common  +  6701  )
#define		CONST_qnmCfgId_mcuDomainName							(  CONST_qnmCfgId_base_common  +  6702  )



//  2008/05/15
// 30000 - 31999
#define		CONST_qnmCfgId_debug_base								30000													//  2015/09/01. 把dbg的定义放高点。以后就固定下来。

//
#define		CONST_qnmCfgId_tTime_start								(  CONST_qnmCfgId_debug_base  +  1  )
#define		CONST_qnmCfgId_usElapsed_toSend							(  CONST_qnmCfgId_debug_base  +  2  )
//  #define		CONST_qnmCfgId_sElapsed_videoConferenceRecved		(  CONST_qnmCfgId_debug_base  +  3  )

#define		CONST_qnmCfgId_tTime_serv_startToRecv					(  CONST_qnmCfgId_debug_base  +  20  )
#define		CONST_qnmCfgId_usElapsed_serv_recved					(  CONST_qnmCfgId_debug_base  +  21  )
#define		CONST_qnmCfgId_usElapsed_serv_startToProcess			(  CONST_qnmCfgId_debug_base  +  22  )
#define		CONST_qnmCfgId_usElapsed_serv_toFindDst					(  CONST_qnmCfgId_debug_base  +  23  )
#define		CONST_qnmCfgId_usElapsed_serv_toBeSwitched				(  CONST_qnmCfgId_debug_base  +  24  )
#define		CONST_qnmCfgId_usElapsed_serv_toSend					(  CONST_qnmCfgId_debug_base  +  25  )

#define		CONST_qnmCfgId_dwTickCnt_peer_recved					(  CONST_qnmCfgId_debug_base  +  40  )
#define		CONST_qnmCfgId_usElapsed_peer_resp_toSend				(  CONST_qnmCfgId_debug_base  +  41  )
#define		CONST_qnmCfgId_tTime_peer_recved						(  CONST_qnmCfgId_debug_base  +  42  )

#define		CONST_qnmCfgId_tTime_serv_resp_startToRecv				(  CONST_qnmCfgId_debug_base  +  60  )
#define		CONST_qnmCfgId_usElapsed_serv_resp_recved				(  CONST_qnmCfgId_debug_base  +  61  )
#define		CONST_qnmCfgId_usElapsed_serv_resp_startToProcess		(  CONST_qnmCfgId_debug_base  +  62  )
#define		CONST_qnmCfgId_usElapsed_serv_resp_toFindDst			(  CONST_qnmCfgId_debug_base  +  63  )
#define		CONST_qnmCfgId_usElapsed_serv_resp_toBeSwitched			(  CONST_qnmCfgId_debug_base  +  64  )
#define		CONST_qnmCfgId_usElapsed_serv_resp_toSend				(  CONST_qnmCfgId_debug_base  +  65  )


//  
//  #define		CONST_qnmCfgId_dwTickCnt_resp_recved				(  CONST_qnmCfgId_debug_base  +  80  )
//  #define		CONST_qnmCfgId_usElapsed_resp_end					(  CONST_qnmCfgId_debug_base  +  81  )

#define		CONST_qnmCfgId_ucbGetTotal								(  CONST_qnmCfgId_debug_base  +  200  )
#define		CONST_qnmCfgId_netStats_total							(  CONST_qnmCfgId_debug_base  +  201  )
#define		CONST_qnmCfgId_qmdStatus_msgrMem						(  CONST_qnmCfgId_debug_base  +  202  )
#define		CONST_qnmCfgId_qmdStatus_channelMem						(  CONST_qnmCfgId_debug_base  +  203  )
//
#define		CONST_qnmCfgId_showInfoFlgs								(  CONST_qnmCfgId_debug_base  +  210  )		//  2015/09/01
#define		CONST_qnmCfgId_debugStatusInfo							(  CONST_qnmCfgId_debug_base  +  211  )

// 32000 - 
#define		CONST_qnmCfgId_user										32000



//
//
//  32k( 32768 ), 2007/08/05
//
//


//  CONST_qnmMaxPcLastCommIntervalÓ¦´ó¹ýCONST_qnmMaxWaitPcCommTimeÖÁÉÙÁ½±¶

#define		CONST_demoDefined_qwmConnectIntervalLoops			3
#define		CONST_qnmMaxLastCommTime							(  15  *  60  )  		//  2007/02/20, ÓÃÀ´ÅÐ¶ÏPCÊÇ·ñÀëÏßµÄÊ±¼ä¼ä¸ô
//
#ifdef  __DEBUG__
	#define		CONST_qnmMaxWaitPcCommTime							8000				//  µÈ´ý8ÃëpcÆô¶¯Ê±¼ä
#else
	#define		CONST_qnmMaxWaitPcCommTime							120000				//  µÈ´ý120ÃëpcÆô¶¯Ê±¼ä
#endif
#define		CONST_qnmMaxPcLastCommInterval						(  20  *  60  *  1000  )		//  20·ÖÖÓ


#ifdef  __DEBUG__
	#define		CONST_qwmFindCntIntervalLoops					10					//  2006/07/01
	#define		CONST_qwmConnectIntervalLoops					4
	#define		CONST_qwmQueryGlCntIpIntervalLoops				4
	#define		CONST_qwmQueryCfgsIntervalLoops					4					//  2006/08/15
	#define		CONST_qwmShowPcNetworkPropIntervalLoops			4					//  	
	#define		CONST_qwmShowPcWindowsUpdatePolicyIntervalLoops	4					//  2006/05/21
	#define		CONST_qwmShowPcNetFlowIntervalLoops				4					//  2006/09/10
	#define		CONST_qwmShowProcessIntervalLoops				4					//  2005/07/03
	#define		CONST_qwmSndEventLogIntervalLoops				4444
	#define		CONST_qwmSndLogIntervalLoops					4
	#define		CONST_qwmSndUsrInfoIntervalLoops				4
	#define		CONST_qwmSndNetStatIntervalLoops				4
	#define		CONST_qwmSndPrintersIntervalLoops				4
	#define		CONST_servDefined_qwmConnectIntervalLoops		3
	#define		CONST_qwmGetRandIntervalLoops					500
	#define		CONST_qwmCommWithGlCntIntervalLoops				40
	#define		CONST_qnmMaxCommWithGlCntTime					25000				//  proxy·¢ËÍÈÕÖ¾µÄÊ±¼ä¼ä¸ô
	//  #define		CONST_qnmMinInvalidChkedIpTime					(  24  *  3600  *  1000	 )
	#define		CONST_queryAutoLogonIntervalLoops				4					//  ²éÑ¯×Ô¶¯µÇÂ¼¼ä¸ô£¬2006/01/08
#else
	#define		CONST_qwmFindCntIntervalLoops					160					//  2006/07/01
	#define		CONST_qwmConnectIntervalLoops					150
	#define		CONST_qwmQueryGlCntIpIntervalLoops				300
	#define		CONST_qwmQueryCfgsIntervalLoops					300					//  2006/08/15
	#define		CONST_qwmShowPcNetworkPropIntervalLoops			170					//  	
	#define		CONST_qwmShowPcWindowsUpdatePolicyIntervalLoops	300					//  2006/05/21
	#define		CONST_qwmShowPcNetFlowIntervalLoops				300					//  2006/09/10
	#define		CONST_qwmShowProcessIntervalLoops				170					//  2005/07/03
	#define		CONST_qwmSndEventLogIntervalLoops				150
	#define		CONST_qwmSndLogIntervalLoops					20
	#define		CONST_qwmSndUsrInfoIntervalLoops				150
	#define		CONST_qwmSndNetStatIntervalLoops				150
	#define		CONST_qwmSndPrintersIntervalLoops				150
	#define		CONST_servDefined_qwmConnectIntervalLoops		150
	#define		CONST_qwmGetRandIntervalLoops					1500
	#define		CONST_qwmCommWithGlCntIntervalLoops				200
	#define		CONST_qnmMaxCommWithGlCntTime					120000				//  proxy·¢ËÍÈÕÖ¾µÄÊ±¼ä¼ä¸ô
	//  #define		CONST_qnmMinInvalidChkedIpTime					(  24  *  3600  *  1000	 )
	#define		CONST_queryAutoLogonIntervalLoops				100					//  ²éÑ¯×Ô¶¯µÇÂ¼¼ä¸ô£¬2006/01/08
#endif

#define		DEFAULT_getCfgInterval								90
#define		DEFAULT_queryCfgsInterval							(  10  *  60  )
#define		DEFAULT_getOpCmdInterval							20
#define		DEFAULT_getOpCmdInterval_realTime					8					//  2006/03/23
#define		DEFAULT_capScreenInterval							10					//  2006/03/05
#ifdef  __DEBUG__	//  2005/09/19
		#define		DEFAULT_showPcNetworkInterval				7
		#define		DEFAULT_sndUsrInfoInterval					15
		#define		DEFAULT_showProcessInterval					30
		#define		DEFAULT_showModulesInterval					90
		#define		DEFAULT_showNetFlowInterval					40
		#define		DEFAULT_showPcWindowsUpdatePolicyIntervalLoops		90
		#define		DEFAULT_sndEventLogInterval					120
		#define		DEFAULT_sndNetStatInterval					60
		#define		DEFAULT_showNetShareInterval				10
		#define		DEFAULT_showArpInterval						60
#else
		#define		DEFAULT_showPcNetworkInterval				300  //  150
		#define		DEFAULT_sndUsrInfoInterval					600
		#define		DEFAULT_showProcessInterval					280
		#define		DEFAULT_showModulesInterval					3600
		#define		DEFAULT_showNetFlowInterval					330
		#define		DEFAULT_showPcWindowsUpdatePolicyIntervalLoops	3600
		#define		DEFAULT_sndEventLogInterval					320
		#define		DEFAULT_sndNetStatInterval					360
		#define		DEFAULT_showNetShareInterval				1800
		#define		DEFAULT_showArpInterval						1800
#endif
//
#define		DEFAULT_demoDefined_getCfgInterval					6
#define		DEFAULT_demoDefined_queryCfgsInterval				60
#define		DEFAULT_demoDefined_showPcNetworkInterval			7
#define		DEFAULT_demoDefined_sndUsrInfoInterval				15
#define		DEFAULT_demoDefined_showProcessInterval				30
#define		DEFAULT_demoDefined_showModulesInterval				90
#define		DEFAULT_demoDefined_showNetFlowInterval				40
#define		DEFAULT_demoDefined_showPcWindowsUpdatePolicyIntervalLoops		90
#define		DEFAULT_demoDefined_sndEventLogInterval				120
#define		DEFAULT_demoDefined_sndNetStatInterval				60

//
#define		DEFAULT_autoLogonInterval							(  5  *  60  )
#define		CONST_minAutoLogonInterval							(  1  *  60  )
//
#define		DEFAULT_maxLogs										0						//  2005/10/01
//
#ifdef  __DEBUG__
		#define		DEFAULT_maxConns_netMc						50						//  2006/08/18
		//  #define		DEFAULT_maxConns_is							25						//  2006/08/18
#else
		#define		DEFAULT_maxConns_netMc						50						//  2006/08/18
		//  #define		DEFAULT_maxConns_is							800					//  2006/08/18
#endif

//  2014/02/05
#define		MAX_conns_is										5000  *  4				//  单服务器上的最大连接数

//
#define		CONST_minInterval									6
#define		CONST_maxInterval									(  12  *  3600  )		//  ×¢Òâ£ºÕâÀï×î´óµÄ²»ÄÜ³¬¹ý65535

//
#define		CONST_min_nMgrThreads_cs								1	//10
#define		CONST_max_nMgrThreads_cs								90						
//
#define		CONST_min_nMgrThreads_route								1	//10
#define		CONST_max_nMgrThreads_route								300						
//
#define		CONST_min_nMgrThreads_switch_route						1	//10
#define		CONST_max_nMgrThreads_switch_route						300						
//
#define		CONST_min_nCliThreads									6
#define		CONST_max_nCliThreads									100						



//  {  Ò»¸ö¿ÉÒÔÉè¶¨×î´óÖµÓë×îÐ¡ÖµµÄÈ¡ÅäÖÃºê,  2006/03/05
#define		MACRO_getInterval(  defInterval,  rootKey_qnmScheduler,  regValName,  intervalVar  )  {									\
				unsigned  short		usInterval  =  defInterval;													\
				TCHAR				buf[64]		=	_T(  ""  );															\
				if  (  !qyGetRegCfg(  rootKey_qnmScheduler,  regValName,  (  char  *  )buf,  sizeof(  buf  )  )		\
					&&  _ttol(  buf  )  >=  CONST_minInterval													\
						&&  _ttol(  buf  )  <=  CONST_maxInterval  )												\
		 		{																								\
					usInterval  =  (  unsigned  short  )_ttol(  buf  );											\
				}																								\
				if  (  intervalVar  !=  usInterval  )  intervalVar  =  usInterval;								\
		 }

//  }


//  #define		CONST_qnmMinChkedPcs								64				//  ÔÚ´óÍø¶ÎÇé¿öÏÂ£¬ÊÕ¼¯ÐÅÏ¢Âú64Ì¨¾ÍÉÏ±¨·þÎñÆ÷
#define		CONST_maxTmpUnchkedDays								2					//  ÁÙÊ±ºìÃûµ¥³ÖÐøÊ±¼ä



#ifdef  __USE_atCommVer_1__

//  ÒÔÏÂÊÇÊý¾ÝÀàÐÍ, ÓÃÔÚÍ¨ÐÅÀï£¬ÑÏ½ûÐÞ¸Ä
#define		CONST_qyDataType_l32								1				//  netMcÀïÒÑÊ¹ÓÃ
#define		CONST_qyDataType_long								CONST_qyDataType_l32
#define		CONST_qyDataType_str								2				//  netMcÀïÒÑÊ¹ÓÃ, ´ËÀàÐÍÊµ¼Ê·ÇÒÔ0½ØÎ²µÄ×Ö·û´®¡£Êµ¼ÊÊÇÒ»¸ö¶þ½øÖÆÁ÷¡£ÒòÎªÄÚÍø¹ÜÀíÒÑ¾­Ê¹ÓÃ£¬¹ÊÔÝÊ±²»¸Ä¶¯ 
//
#define		CONST_qyDataType_wStr								3				//  2007/03/31
#define		CONST_qyDataType_utf8Str							4				//  2007/03/31
#define		CONST_qyDataType_data								5				//  2007/03/31, Êý¾Ý³¤¶ÈÓÃshortÀ´±íÊ¾.
#define		CONST_qyDataType_l64								6				//  2007/08/01
#define		CONST_qyDataType_byte								7				//  2007/08/05
#define		CONST_qyDataType_char								CONST_qyDataType_byte
#define		CONST_qyDataType_short								8				//  2007/08/05
#define		CONST_qyDataType_lData								9				//  2008/04/01, Õâ¸öÀàÐÍ¿ÉÌá¹©¸ü³¤µÄÊý¾ÝÃèÊö¡£Êý¾Ý³¤¶ÈÓÃlongÀ´±íÊ¾

#else

#define		CONST_qyDataType_l32								CONST_atDataType_l32				//  netMcÀïÒÑÊ¹ÓÃ
#define		CONST_qyDataType_long								CONST_qyDataType_l32
#define		CONST_qyDataType_str								CONST_atDataType_str				//  netMcÀïÒÑÊ¹ÓÃ, ´ËÀàÐÍÊµ¼Ê·ÇÒÔ0½ØÎ²µÄ×Ö·û´®¡£Êµ¼ÊÊÇÒ»¸ö¶þ½øÖÆÁ÷¡£ÒòÎªÄÚÍø¹ÜÀíÒÑ¾­Ê¹ÓÃ£¬¹ÊÔÝÊ±²»¸Ä¶¯ 
//
#define		CONST_qyDataType_wStr								CONST_atDataType_wStr				//  2007/03/31
#define		CONST_qyDataType_utf8Str							CONST_atDataType_utf8Str				//  2007/03/31
#define		CONST_qyDataType_data								CONST_atDataType_data				//  2007/03/31, Êý¾Ý³¤¶ÈÓÃshortÀ´±íÊ¾.
#define		CONST_qyDataType_l64								CONST_atDataType_l64				//  2007/08/01
#define		CONST_qyDataType_byte								CONST_atDataType_byte				//  2007/08/05
#define		CONST_qyDataType_char								CONST_qyDataType_byte
#define		CONST_qyDataType_short								CONST_atDataType_short				//  2007/08/05
#define		CONST_qyDataType_lData								CONST_atDataType_lData				//  2008/04/01, Õâ¸öÀàÐÍ¿ÉÌá¹©¸ü³¤µÄÊý¾ÝÃèÊö¡£Êý¾Ý³¤¶ÈÓÃlongÀ´±íÊ¾


#endif 


typedef  struct  __qyCfgItem_t									{
				 unsigned  short								cfgId;
				 unsigned  short								dataType;
}		 QY_CFGITEM;

typedef  struct  __qyCfgItemLong_t								{
				 unsigned  short								cfgId;
				 unsigned  short								dataType;
				 unsigned  long									ulVal;
}		 QY_CFGITEM_LONG;


typedef  struct  __qyCfgItemL64_t								{			//  ÒòÎª´Ó×Ö½ÚË³ÐòÉÏ£¬¿ÉÄÜ__int64ºÍunsigned  short²»ÄÜË³×Ö½Ú´æ·Å£¬¹ÊÖ»ÄÜÓÃÒ»¸öchar»º´æÀ´Ìæ»»
				 unsigned  short								cfgId;
				 unsigned  short								dataType;
				 char											buf_l64Val[sizeof(  __int64  )];	//  unsigned  __int64								ui64Val;
}		 QY_CFGITEM_L64;

typedef  struct  __qyCfgItemChar_t								{			//  2007/08/05
				 unsigned  short								cfgId;
				 unsigned  short								dataType;
				 unsigned  char									ucVal;
}		 QY_CFGITEM_CHAR;

typedef  struct  __qyCfgItemShort_t								{			//  2007/08/05
				 unsigned  short								cfgId;
				 unsigned  short								dataType;
				 unsigned  short								usVal;
}		 QY_CFGITEM_SHORT;


/*
typedef  struct  __qyCfgItemStr_t								{				//  netMcÀïÊ¹ÓÃµÄ£¬ÒòÎªstrµÄ³¤¶È¶ÔisÀ´Ëµ²»¹»ÓÃ£¬¹ÊÀ©µ½ÏÂÃæµÄ³¤¶È¡£µ«ÊÇÒª×¢Òâ£ºÔ­À´µÄ³¤¶ÈÊÇ¡¶1024µÄ
				 unsigned  short								cfgId;
				 unsigned  short								dataType;
				 unsigned  short								len;
				 char											str[1024];
}		 QY_CFGITEM_STR;
*/

typedef  struct  __qyCfgItemStr_t								{
				 unsigned  short								cfgId;
				 unsigned  short								dataType;
				 unsigned  short								len;
				 char											str[4096];		//  2007/03/31, ½«»º³åµÄ³¤¶È±ä³¤ÁË
}		 QY_CFGITEM_STR;

typedef  struct  __qyCfgItemWStr_t								{				//  2007/03/31
				 unsigned  short								cfgId;
				 unsigned  short								dataType;
				 unsigned  short								len;
				 WCHAR											wStr[4096];
}		 QY_CFGITEM_WSTR;


#define		CONST_bufSize_cfgItemData							32  *  1024		//  2007/03/31, ½«»º³åµÄ³¤¶È±ä³¤ÁË
#define		CONST_bufSize_cfgItemLData							1024  *  1024	//  2008/03/22

typedef  struct  __qyCfgItemData_t								{
				 unsigned  short								cfgId;
				 unsigned  short								dataType;
				 unsigned  short								len;
				 char											buf[CONST_bufSize_cfgItemData  +  1];		
}		 QY_CFGITEM_DATA;

typedef  struct  __qyCfgItemLData_t								{
				 unsigned  short								cfgId;
				 unsigned  short								dataType;
				 unsigned  long									ulLen;
				 char											buf[CONST_bufSize_cfgItemLData  +  1];		
}		 QY_CFGITEM_LDATA;


//  2010/07/09
typedef  union  __qyCfgItem_ntoh_u								{
				QY_CFGITEM										head;
				QY_CFGITEM_LONG									l;
				QY_CFGITEM_L64									l64;
				QY_CFGITEM_CHAR									c;
				QY_CFGITEM_SHORT								s;
				struct											{
					 unsigned  short							cfgId;
					 unsigned  short							dataType;
					 unsigned  short							len;
					 char										buf[1];		
					 char									*	p;					 
				}												data;
				struct											{
					 unsigned  short							cfgId;
					 unsigned  short							dataType;
					 unsigned  long								ulLen;
					 char										buf[1];		
					 char									*	p;
				}												lData;
				//				
				struct											{				//  2007/03/31
					 unsigned  short							cfgId;
					 unsigned  short							dataType;
					 unsigned  short							len;
					 WCHAR										wBuf[1];
					 WCHAR									*	pWStr;
				}												wStr;

}		 QY_CFGITEM_ntoh_U;


//
typedef  struct  __qnmStopMonRule_t								{
				 unsigned  char									ucbStopped;
}		 QNM_STOPMON_RULE;


typedef  struct  __qnmRasRule_t									{
				 unsigned  char									ucRasCmd;
				 unsigned  char									ucCnt;					//  ÌØÐíµç»°ºÅÂëµÄ×ÜÊý
				 char											permittedPhoneNums[CONST_maxPermittedPhoneNums][CONST_phoneNumBytes  +  1];
				 unsigned  char									ucbNotChkOnInternet;	//  ²»¼ì²â·Ç·¨ÍâÁ·, 2005/01/05
				 unsigned  char									ucWarnToInternetCmd;	//  Ô¶³ÌÉÏÍø±¨¾¯£¬2005/06/26
}		 QNM_RAS_RULE;

#if  0
typedef  struct  __qnmDevRult_t									{						//  2005/01/04
				 unsigned  char									ucFloppyCmd;
				 unsigned  char									ucCdromCmd;
				 unsigned  char									ucUsbStorCmd;
				 unsigned  char									ucWLanAdapterCmd;		//  2010/05/20
}		 QNM_DEV_RULE;
#endif
#if  0		//  2011/08/26
typedef  struct  __qnmDevRult_t									{						//  2005/01/04
				 unsigned  char									ucFloppyCmd;
				 unsigned  char									ucCdromCmd;
				 unsigned  char									ucUsbStorCmd;
				 unsigned  char									ucWLanAdapterCmd;		//  2010/05/20

				 unsigned  char									ucBlueToothCmd;			//  2010/08/18
				 unsigned  char									ucInfraredCmd;			//  2010/08/18
				 unsigned  char									uc1394Cmd;				//  2010/08/18
}		 QNM_DEV_RULE;
#endif
typedef  struct  __qnmDevRult_t									{						//  2005/01/04
				 unsigned  char									ucFloppyCmd;
				 unsigned  char									ucCdromCmd;
				 unsigned  char									ucUsbStorCmd;
				 unsigned  char									ucWLanAdapterCmd;		//  2010/05/20

				 unsigned  char									ucBlueToothCmd;			//  2010/08/18
				 unsigned  char									ucInfraredCmd;			//  2010/08/18
				 unsigned  char									uc1394Cmd;				//  2010/08/18
				 unsigned  char									ucWpdCmd;				//  2011/08/26
				 unsigned  char									ucSdHostAdapterCmd;		//  2011/08/28
				 unsigned  char									ucMobileDeviceCmd;		//  2011/08/28
				 unsigned  char									ucUsbNetworkCardCmd;	//  2011/09/18
}		 QNM_DEV_RULE;



typedef  struct  __qnmMgrProxyRule_t							{
				 unsigned  char									ucbDel;					//  Í£Ö¹´úÀí²¢ÍË³ö
				 unsigned  char									ucbStart;				//  ÆôÓÃ´úÀí¹¦ÄÜ£¬¿ÉÒÔ»Ö¸´ 
				 unsigned  char									reserved[2];
				 unsigned  long									ulRandOfStartup;		//  ±êÊ¶Æô¶¯µÄËæ»úÊý
}		 QNM_MGRPROXY_RULE;


typedef  struct  __qnmUnchkRule_t								{
				 unsigned  char									ucbUnchked;
}		 QNM_UNCHK_RULE;

typedef  struct  __qnmSecChkRule_t								{
				 unsigned  char									ucbDoSecChk;
}		 QNM_SECCHK_RULE;

typedef  struct  __qnmOsRule_t									{
				 unsigned  char									ucSafeModeCmd;		//  ÊÇ·ñÔÊÐíÊ¹ÓÃ°²È«Ä£Ê½£¬	2005/06/25
				 unsigned  char									ucHideQwmCmd;		//  ÊÇ·ñÔÊÐíqwmµÄ½ø³ÌÒþ²Ø£¬	2007/01/14¡£ÓÉÓÚºÜ¶àÓÎÏ·Èí¼þºÍqwmµÄ³åÍ»£¬µ¼ÖÂ½ø³Ì¹ÜÀíÆ÷²»ÄÜÕý³£Ê¹ÓÃ¡£¹ÊÔö¼Ó´Ë¹¦ÄÜ£¬¿É½ûÖ¹½ø³ÌÒþ²Ø
				 unsigned  char									ucAutorunCmd;		//  Çý¶¯Æ÷×Ô¶¯²¥·Å£¬		2007/02/12
				 unsigned  char									ucNetShareCmd;		//  ÍøÂç¹²Ïí£¬				2007/02/12
				 unsigned  char									ucAdminCmd;			//  ¹ÜÀíÔ±µÇÂ½£¬			2007/02/12

}		 QNM_OS_RULE;

/*
typedef  struct  __qnmOsAuditRule_t								{					//  2005/08/30
				 unsigned  char									ucSndEventLogCmd;
				 unsigned  char									ucSndUsrInfoCmd;	//  ÊÇ·ñ·¢ÓÃ»§ÐÅÏ¢£¬2005/09/04
				 unsigned  char									ucSndNetStatCmd;	//  ÊÇ·ñÉÏ´«Á¬½ÓÐÅÏ¢£¬2005/09/17
				 unsigned  char									ucWatchPrinterCmd;	//  ÊÇ·ñÉÏ´«´òÓ¡Éó¼ÆÐÅÏ¢£¬2005/09/18
				 unsigned  char									ucbReserveds[4];	//  ÕâÀï»¹±£Áô5¸ö×Ö½Ú½«À´ÓÃ
				 char											dirName[32  +  1];	//  ÎÄ¼þ²Ù×÷Éó¼ÆÄ¿Â¼, 2005/09/14
				 //
}		 QNM_OSAUDIT_RULE;
*/

/*
typedef  struct  __qnmOsAuditRule_t								{					//  2005/08/30
				 unsigned  char									ucSndEventLogCmd;
				 unsigned  char									ucSndUsrInfoCmd;	//  ÊÇ·ñ·¢ÓÃ»§ÐÅÏ¢£¬2005/09/04
				 unsigned  char									ucSndNetStatCmd;	//  ÊÇ·ñÉÏ´«Á¬½ÓÐÅÏ¢£¬2005/09/17
				 unsigned  char									ucWatchPrinterCmd;	//  ÊÇ·ñÉÏ´«´òÓ¡Éó¼ÆÐÅÏ¢£¬2005/09/18
				 unsigned  char									ucSndModuleInfoCmd;	//  ÊÇ·ñÉÏ´«Ä£¿éÐÅÏ¢£¬2006/04/17
				 unsigned  char									ucbReserveds[3];	//  ÕâÀï»¹±£Áô3¸ö×Ö½Ú½«À´ÓÃ
				 char											dirName[32  +  1];	//  ÎÄ¼þ²Ù×÷Éó¼ÆÄ¿Â¼, 2005/09/14
				 //
}		 QNM_OSAUDIT_RULE;															//  ×¢£ºÎªÁË¼ÓÈë½ø³ÌÄ£¿éÐÅÏ¢µÄÆôÍ£¹¦ÄÜ£¬ÌØÒâÕ÷ÓÃÁËÉÏÊöµÄ±£ÁôµÄÒ»¸ö×Ö½Ú£¬2006/04/17ÐÞ¸Ä
*/

typedef  struct  __qnmOsAuditRule_t								{						//  2005/08/30
				 unsigned  char									ucSndEventLogCmd;
				 unsigned  char									ucSndUsrInfoCmd;		//  ÊÇ·ñ·¢ÓÃ»§ÐÅÏ¢£¬2005/09/04
				 unsigned  char									ucSndNetStatCmd;		//  ÊÇ·ñÉÏ´«Á¬½ÓÐÅÏ¢£¬2005/09/17
				 unsigned  char									ucWatchPrinterCmd;		//  ÊÇ·ñÉÏ´«´òÓ¡Éó¼ÆÐÅÏ¢£¬2005/09/18
				 unsigned  char									ucSndModuleInfoCmd;		//  ÊÇ·ñÉÏ´«Ä£¿éÐÅÏ¢£¬2006/04/17
				 unsigned  char									ucSndPcRegistryValCmd;	//  ÊÇ·ñÉÏ´«×¢²á±íÐÅÏ¢£¬2006/08/15
				 unsigned  char									ucbReserveds[2];		//  ÕâÀï»¹±£Áô2¸ö×Ö½Ú½«À´ÓÃ
				 char											dirName[32  +  1];		//  ÎÄ¼þ²Ù×÷Éó¼ÆÄ¿Â¼, 2005/09/14
				 //
}		 QNM_OSAUDIT_RULE;																//  ×¢£ºÎªÁË¼ÓÈë½ø³ÌÄ£¿éÐÅÏ¢µÄÆôÍ£¹¦ÄÜ£¬ÌØÒâÕ÷ÓÃÁËÉÏÊöµÄ±£ÁôµÄÒ»¸ö×Ö½Ú£¬2006/04/17ÐÞ¸Ä
																						//  ×¢£ºÎªÁË¼ÓÈë×¢²á±í¼à¿ØµÄÆôÍ£¹¦ÄÜ£¬Õ÷ÓÃÁËÉÏÊöµÄÒ»¸ö±£Áô×Ö½Ú£¬2006/08/15



typedef  struct  __qnmPcMonRule_t								{						//  2006/03/04, ´Ë½á¹¹Ó¦ÓÃÓÚÐÐÎª¼à¿Ø
				 unsigned  char									ucCapScreenCmd;			//  ×¥ÆÁ
				 unsigned  char									ucImMonCmd;				//  ¼´Ê±Í¨Ñ¶
				 unsigned  char									ucIeMonCmd;				//  ¼à¿ØIE
				 unsigned  char									reserved;
				 unsigned  short								usCapScreenInterval;	//  ÆÁÄ»¿½±´¼ä¸ô
}		 QNM_PCMON_RULE;


typedef  struct  __qnmPcNetFlowRule_t							{								//  2006/09/10
				 unsigned  int									uiWarnPercentOfBandWithFactor;	//  ÒÔ´ø¿íµÄÊ®Íò·ÖÖ®Ò»Îªµ¥Î»
				 unsigned  char									ucWarnedNetworkCardCmd;			//  ÊÇ·ñ½ûÓÃ±»±¨¾¯µÄÍø¿¨
				 unsigned  char									ucDetectTimesBeforeWarn;		//  ´ïµ½±¨¾¯Ìõ¼þºóÁ¬Ðø¼ì²â´ÎÊý£¬ÒÔ±ÜÃâÎó±¨	
				 unsigned  char									ucbPopupToWarn;					//  ÊÇ·ñµ¯³ö´°¿Ú±¨¾¯
				 unsigned  short								usStopNetworkCardTimeInSecond;	//  ½ûÓÃ³ÖÐøÊ±¼ä									
}		 QNM_PCNETFLOW_RULE;


//  {  //  2006/03/21

#define		CONST_maxFileMonRules								100
#define		CONST_maxFileMonRuleBufSize							32						
//
#define		CONST_fileMonFlg_suffix								1
#define		CONST_fileMonFlg_str								(  1  <<  1  )
//
//  Êý¾Ý¿âÀï´æ´¢µÄÀàÐÍ
#define		CONST_fileMonRuleType_null							0
#define		CONST_fileMonRuleType_changesId						1
#define		CONST_fileMonRuleType_filterSysDir					2
#define		CONST_fileMonRuleType_filterWinDir					3
#define		CONST_fileMonRuleType_filterWinTmpDir				4
#define		CONST_fileMonRuleType_filterUsrTmpDir				5
#define		CONST_fileMonRuleType_filterRename					100
#define		CONST_fileMonRuleType_filterModify					101
#define		CONST_fileMonRuleType_bMonAll						200
#define		CONST_fileMonRuleType_suffix						201
#define		CONST_fileMonRuleType_str							202
//
#define		DEFAULT_fileMonFilter_changesId						18


//  2006/03/22
//  #define		CONST_ruleType_pcFileMon						2
//
//  ×¢£º2006/07/16, ½«ÉÏÊöµÄ¶¨ÒåÖØÐÂÕûÀí£¬Í³Ò»µ½CONST_pcCommType_*µÄ¶¨ÒåÖÐÈ¥
//
#define		CONST_ruleType_pcFileMon							CONST_pcCommType_pcFileMonRules

#define		MACRO_ruleCommonHead								unsigned  int  uiType;	unsigned  int  uiChangesId;
																//  uiType, ÓÃÀ´±ê¼ÇÀàÐÍ£¬ÕùÈ¡°Ñ¸÷ÖÖ²ßÂÔ¶¼ÄÉÈëÍ³Ò»µÄ¹ÜÀíÖÐ£¬¼õÉÙÍøÂçÍ¨ÐÅÄÚÈÝ
				 												//  uiChangesId, ÓÃÀ´±ê¼Ç±ä¸ü£¬Ã¿´Î²ßÂÔ±ä»¯£¬¶¼Òª¸Ä±äÒ»ÏÂ
																//  2006/07/16, ×¢ÒâÕâÀï£¬²»ÄÜ¼ÓÈë³ÉÔ±ÁË£¬ÒòÎªÕâÀï¼ÓÈëµÄ»°Òª¸Ä±äfileMonRulesµÄ½á¹¹ÁË£¬ËùÒÔÒ»¶¨²»ÒªÔÙ¼ÓÈëÁË
																//				Òª¼ÓÈëµÄ»°ÒªÖØÐÂÉè¼Æ

typedef  struct  __ruleCommonHead_t								{
				 MACRO_ruleCommonHead
}		 RULE_COMMON_HEAD;
			 								


typedef  struct  __pcFileMonRules_t								{
				 MACRO_ruleCommonHead
				 unsigned  char									ucbFilterSysDir;
				 unsigned  char									ucbFilterWinDir;
				 unsigned  char									ucbFilterWinTmpDir;	
				 unsigned  char									ucbFilterUsrTmpDir;
				 unsigned  char									ucbFilterRename;
				 unsigned  char									ucbFilterModify;
				 unsigned  char									ucbMonAll;
				 unsigned  char									reserved[25];		
				 unsigned  char									ucCnt;
				 unsigned  char									ucFlgs[CONST_maxFileMonRules];		//  CONST_fileMonFlg_subFix,	1  
				 char											bufs[CONST_maxFileMonRules][CONST_maxFileMonRuleBufSize];
}		 PC_FILEMON_RULES;


typedef  struct  __qyPcRegistryRule_t							{
				 unsigned  int									id;						//  ÓÃÀ´±êÊ¶ÅäÖÃÏîµÄÊý¾Ý¿â¼ÇÂ¼
				 int											iRootKey;				//  HKEY_CLASSES_ROOTµÈÔ¤¶¨Öµ£¬»òÕß¶ÔÓ¦µÄ×Ô¶¨ÒåµÄÖµ
				 WCHAR											wSubKey[255  +  1];		//  ÔÚÄÚ²¿Ê¹ÓÃÊ±Ç¿ÖÆ×ª»»ÎªUNICODEÀ´´¦Àí£¬´«ÊäÊ±ÓÃUTF8
				 WCHAR											wCfgName[255  +  1];	//  ÖµÃû³Æ
}		 QY_PC_REGISTRYRULE;

#define		CONST_maxPcRegistryRules							20
typedef  struct  __qyPcRegistryRules_t							{
				 MACRO_ruleCommonHead
				 unsigned  int									cnt;
				 QY_PC_REGISTRYRULE								mems[CONST_maxPcRegistryRules];
}		 QY_PC_REGISTRYRULES;


typedef  union  __qyPcRulesU_t									{
				unsigned  int									uiType;
				struct											{
					MACRO_ruleCommonHead
				}												head;
				char											buf[4096];
				PC_FILEMON_RULES								fileMonRules;
				QY_PC_REGISTRYRULES								registryRules;				
}		 QY_PC_RULESU;

int  qyhtonQyPcRulesU(  QY_PC_RULESU  *  pU  );
int  qyntohQyPcRulesU(  QY_PC_RULESU  *  pU  );


//  }


#define		CONST_qnmPcRuleFlg_stopMon											(  1  )
#define		CONST_qnmPcRuleFlg_ras												(  1  <<  1  )
#define		CONST_qnmPcRuleFlg_startProxy										(  1  <<  2  )
#define		CONST_qnmPcRuleFlg_delProxy											(  1  <<  3  )
#define		CONST_qnmPcRuleFlg_unchk											(  1  <<  4  )
#define		CONST_qnmPcRuleFlg_secChk											(  1  <<  5  )
#define		CONST_qnmPcRuleFlg_floppyCmd										(  1  <<  6  )		//  2005/01/05
#define		CONST_qnmPcRuleFlg_cdromCmd											(  1  <<  7  )		//  2005/01/05
#define		CONST_qnmPcRuleFlg_usbStorCmd										(  1  <<  8  )		//  2005/01/05
#define		CONST_qnmPcRuleFlg_os_ucSafeModeCmd									(  1  <<  9  )		//  2005/06/25
#define		CONST_qnmPcRuleFlg_warnToInternet									(  1  <<  10  )		//  2005/06/25	//  not used
#define		CONST_qnmPcRuleFlg_sndEventLogCmd									(  1  <<  11  )		//  2005/09/18
#define		CONST_qnmPcRuleFlg_sndUsrInfoCmd									(  1  <<  12  )		//  2005/09/18
#define		CONST_qnmPcRuleFlg_watchPrinterCmd									(  1  <<  13  )		//  2005/09/18
#define		CONST_qnmPcRuleFlg_sndNetStatCmd									(  1  <<  14  )		//  2005/09/18
#define		CONST_qnmPcRuleFlg_fileMonDir										(  1  <<  15  )		//  2005/09/18
#define		CONST_qnmPcRuleFlg_pcMon											(  1  <<  16  )		//  2006/03/05
#define		CONST_qnmPcRuleFlg_sndModuleInfoCmd									(  1  <<  17  )		//  2006/05/06
#define		CONST_qnmPcRuleFlg_sndPcRegistryValCmd								(  1  <<  18  )		//  2006/08/15
#define		CONST_qnmPcRuleFlg_pcNetFlow_uiWarnPercentOfBandWithFactor			(  1  <<  19  )		//  2006/09/11
#define		CONST_qnmPcRuleFlg_pcNetFlow_ucWarnedNetworkCardCmd					(  1  <<  20  )		//  2006/09/11
#define		CONST_qnmPcRuleFlg_os_ucHideQwmCmd									(  1  <<  21  )		//  2007/02/17
#define		CONST_qnmPcRuleFlg_os_ucAutorunCmd									(  1  <<  22  )		//  2007/02/17
#define		CONST_qnmPcRuleFlg_os_ucNetShareCmd									(  1  <<  23  )		//  2007/02/17
#define		CONST_qnmPcRuleFlg_os_ucAdminCmd									(  1  <<  24  )		//  2007/02/17
#define		CONST_qnmPcRuleFlg_wLanAdapterCmd									(  1  <<  25  )		//  2010/05/20
#define		CONST_qnmPcRuleFlg_ucBlueToothCmd									(  1  <<  26  )		//  2010/08/18
#define		CONST_qnmPcRuleFlg_ucInfraredCmd									(  1  <<  27  )		//  2010/08/18
#define		CONST_qnmPcRuleFlg_uc1394Cmd										(  1  <<  28  )		//  2010/08/18
#define		CONST_qnmPcRuleFlg_ucWpdCmd											(  1  <<  29  )		//  2011/08/26
#define		CONST_qnmPcRuleFlg_ucSdHostAdapterCmd								(  1  <<  30  )		//  2011/08/28
#define		CONST_qnmPcRuleFlg_ucMobileDeviceCmd								(  (  __int64  )1  <<  31  )		//  2011/08/28
#define		CONST_qnmPcRuleFlg_ucUsbNetworkCardCmd								(  (  __int64  )1  <<  32  )		//  2011/09/18
//

				 


//  pcµÄ¹æÔò½á¹¹
typedef  struct  __qnmPcRules_t									{
				 //  int										flg;
				 unsigned  __int64								flg;				//  2011/08/28
				 QNM_STOPMON_RULE								stopMon;
				 QNM_RAS_RULE									ras;
				 QNM_MGRPROXY_RULE								mgrProxy;
				 QNM_UNCHK_RULE									unchk;
				 QNM_SECCHK_RULE								secChk;
				 QNM_DEV_RULE									dev;				//  2005/01/05
				 QNM_OS_RULE									os;					//  2005/06/25
				 QNM_OSAUDIT_RULE								osAudit;			//  2005/09/14
				 QNM_PCMON_RULE									pcMon;				//  2006/03/04
				 QNM_PCNETFLOW_RULE								pcNetFlow;			//  2006/09/11
}		 QNM_PC_RULES;


//  2007/01/26
typedef  struct  __qwmGBufDetail_t								{
	             //  BOOL											bServerOnline;
				 //  DWORD											dwTickCnt_policyRefreshed;
				 //  QNM_PC_RULES									pcRules;				 
				 char											unused;
}		 QWM_GBUF_DETAIL;	

//  


//  È¡ÅäÖÃµÄ¸½¼Ó²ÎÊý
typedef  struct  __qnmCmdParam_getCfgs_t						{
				 unsigned  char									ucbStartProxy;
}		 QNM_CMDPARAM_getCfgs;


//  2006/03/22
typedef  struct  __qnmCmdParam_queryCfgs0325_t					{							//  °æ±¾Ð¡ÓÚµÈÓÚ0325µÄ¿Í»§¶ËÊÇÕâ¸ö½á¹¹
				 unsigned  int									uiChangesId_fileMon;
				 char											reserved[128];				//  ÕâÀï ¹ÊÒâÔö¼Ó¼¸¸ö¿ÕµÄ×Ö½Ú£¬ÒÔ·ÀÖ¹Òç³ö£¬2006/08/06
}		 QNM_CMDPARAM_queryCfgs0325;




//  È¡Ò»ÌØ¶¨IPµÄMACÐÅÏ¢
typedef  struct  __qnmCmdParam_getMacByIp_t						{
				 unsigned  long									ulIp;
}		 QNM_CMDPARAM_getMacByIp;


typedef  struct  __qnmCmdParam_refreshProxyPolicy_t				{
				 unsigned  char									ucbRefreshProxyPolicy;
}		 QNM_CMDPARAM_refreshProxyPolicy;


//  2005/05/02
#define		CONST_qwmSvrStatus_null								0
#define		CONST_qwmSvrStatus_doSecChk							1
#define		CONST_qwmSvrStatus_secChkFinished					2
#define		CONST_qwmSvrStatus_sndSecChkLogDetail				3		
#define		CONST_qwmSvrStatus_chdShallQuit						4						
#define		CONST_qwmSvrStatus_terminateChd						5
#define		CONST_qwmSvrStatus_pcNetworkPropWillChange			6		//  2005/06/04
#define		CONST_qwmSvrStatus_needReboot						7		//  2005/06/04
#define		CONST_qwmSvrStatus_recoverPcNetworkPropForErr		8		//  2005/06/04
#define		CONST_qwmSvrStatus_pcNetworkPropChangeFinished		9		//  2005/06/04
#define		CONST_qwmSvrStatus_fileMon							10		//  2005/09/19
#define		CONST_qwmSvrStatus_watchPrinters					11		//  2005/09/19
#define		CONST_qwmSvrStatus_denyRd							12		//  2006/02/15
#define		CONST_qwmSvrStatus_autoAcceptRdAndRdStart			13
#define		CONST_qwmSvrStatus_promptToAcceptRd					14
#define		CONST_qwmSvrStatus_rdStart							15
#define		CONST_qwmSvrStatus_rdEnd							16
#define		CONST_qwmSvrStatus_capScreenNotSupported			17		//  2006/03/06
#define		CONST_qwmSvrStatus_mdStart							18		//  2006/03/06
#define		CONST_qwmSvrStatus_mdEnd							19		//  2006/03/06
#define		CONST_qwmSvrStatus_rdReqTimeout						20		//  2006/06/15



//  2005/05/02
typedef  struct  __qnmCmdParam_showQwmSvrStatus_t				{				 
				 unsigned  int									uiQwmSvrStatus;
				 unsigned  int									uiSecChkEventCnt;				//  Ðè·¢ËÍ¼ÇÂ¼×ÜÊý
				 unsigned  int									uiSecChkEventSentCnt;			//  ÒÑ·¢ËÍ¼ÇÂ¼×ÜÊý
				 char											progressTxt[128];
}		 QNM_CMDPARAM_showQwmSvrStatus;								


//  2006/06/02
typedef  struct  __qnmCmdParam_retrieveWarningMsg_t				{
				 unsigned  int									reserved;
				 unsigned  char									ucbProced;						//  ÊÇ·ñÒªÇó´¦Àí
				 unsigned  int									uiLastEventId;
}		 QNM_CMDPARAM_retrieveWarningMsg;


//  2006/01/07
typedef  struct  __qnmCmdParam_queryAutoLogon_t					{
				 char											domainName[256];
				 char											logonName[256];
				 char											logonPasswd[256];
				 unsigned  short								usAutoLogonInterval;
}		 QNM_CMDPARAM_queryAutoLogon;


#define		CONST_minMonDesktopIntervalIsS						5
//
//  2006/02/11. ×¢Òâ£ºÔÚ¿Í»§¶ËµÄ½ÓÊÕÊµÊ±²Ù×÷Ö¸Áî£¬ÊÇÓÃsizeof(  QNM_CMDPARAM_getOpCmd  )×÷Îª½ÓÊÕ»º³å´óÐ¡¡£ËùÒÔ£¬¾Í²»ÄÜ½«½á¹¹ËæÒâÀ©´ó¡£
//  ÒÔºóÈôÐèÒªÀ©Õ¹³ÉÔ±£¬ÔòÐèÒªÅÐ¶Ï¿Í»§¶ËµÄ°æ±¾ºÅ¡£À´Çø·Ö²»Í¬µÄÏÂ·¢²ßÂÔ¡£¶ÔÓÚÆÁÄ»¼à¿Ø¡£2008/02/17ºó£¬03¡£33¡£03ºóÊ¹ÓÃÊµÊ±ÆÁÄ»¿½±´À´Ìá¹©¡£ÊµÊ±ÆÁÄ»¿½±´µÄ¼ä¸ô£¬¿ÉÒÔ´æÔÚucbMonDesktopÀï¡££¨1-255Ãë£©
//
typedef  struct  __qnmCmdParam_getOpCmd_t						{
				 unsigned  char									ucbOped;						//  2006/03/23
				 unsigned  char									ucbViewRemoteDesktop;
				 unsigned  char									ucbMonDesktop;					//  2006/03/06, //  2008/02/17, ÓÃÀ´ÉèÖÃÐÂÊ½ÆÁÄ»¼à¿ØÊ±µÄÈ¡ÆÁÄ»¼ä¸ô¡£
}		 QNM_CMDPARAM_getOpCmd;


//  2006/03/06
typedef  struct  __qnmCmdParam_sndCapScreen_t					{
				 unsigned  int									uiFileSize;
				 unsigned  int									uiSizePerSnd;
				 unsigned  int									uiCurSessionId;
				 unsigned  int									uiActiveSessionId;
				 WCHAR											wUsrDomainInfo[96];				//  2007/02/03
}		 QNM_CMDPARAM_sndCapScreen;			


//  ÒÔºóÔÚqwmInfoÀïÓÃucbSthFollows±íÊ¾ÊÇ·ñÔÚQWM_INFOÊý¾Ý°üºóÃæ»¹¼ÌÐø·¢ËÍÐÅÏ¢£¬ÈçQWM_SP_INFO

#define		MACRO_qwmInfo					 int				iPlatformId;														\
											 char				pcName[64  +  1];													\
											 char				systemBuf[64  +  1];			/*  °æ±¾>=0200,  2003/09/12Ìí¼Ó  */ \
											 char				servicePackBuf[64  +  1];		/*  °æ±¾>=0200,  2003/09/12Ìí¼Ó  */	\
											 char				curUsrName[32  +  1];			/*  °æ±¾>=0208,  2004/05/14Ìí¼Ó  */	\
											 char				ieBuf[16  +  1];				/*  °æ±¾>=0208,  2004/05/14Ìí¼Ó  */	\
											 char				ieSpBuf[16  +  1];				/*  °æ±¾>=0208,  2004/05/14Ìí¼Ó	 */ 
  			 
								
//  pcµÄÏêÏ¸ÐÅÏ¢
typedef  struct  __qwmInfo0303_t								{
				 int											iPlatformId;
				 char											pcName[64  +  1];
				 char											systemBuf[64  +  1];			//  °æ±¾>=0200,  2003/09/12Ìí¼Ó,  
				 char											servicePackBuf[64  +  1];		//  °æ±¾>=0200,  2003/09/12Ìí¼Ó
				 char											curUsrName[32  +  1];			//  °æ±¾>=0208,  2004/05/14Ìí¼Ó
				 char											ieBuf[16  +  1];				//  °æ±¾>=0208,  2004/05/14Ìí¼Ó
				 char											ieSpBuf[16  +  1];				//  °æ±¾>=0208,  2004/05/14Ìí¼Ó				 
}		 QWM_INFO0303;


typedef  struct  __qwmInfo_t									{
				 int											iPlatformId;
				 char											pcName[64  +  1];
				 char											systemBuf[64  +  1];			//  °æ±¾>=0200,  2003/09/12Ìí¼Ó,  
				 char											servicePackBuf[64  +  1];		//  °æ±¾>=0200,  2003/09/12Ìí¼Ó
				 char											curUsrName[32  +  1];			//  °æ±¾>=0208,  2004/05/14Ìí¼Ó
				 char											ieBuf[16  +  1];				//  °æ±¾>=0208,  2004/05/14Ìí¼Ó
				 char											ieSpBuf[16  +  1];				//  °æ±¾>=0208,  2004/05/14Ìí¼Ó				 
				 unsigned  int									uiLangId;						//  °æ±¾>=0304,	 2005/01/22Ìí¼Ó
				 char											winDir[255  +  1];				//  °æ±¾>=0304,	 2005/01/22Ìí¼Ó
}		 QWM_INFO;


#define		CONST_qwmInfoType_null								0
#define		CONST_qwmInfoType_sp								1
#define		CONST_qwmInfoType_qwmSvr							2

typedef  struct  __qwmInfoEx_t									{
				 int											type;
				 union											{
					 struct										{
						 QWM_INFO0303							qwm0303;
					     char									spNames[100][16];
					 }											sp0303;
					 struct										{
						 QWM_INFO								qwm;
					     char									spNames[100][16];
					 }											sp;
					 struct										{
						 QWM_INFO								qwm;
						 char									seqNo[128  +  1];
					 }											qwmSvr;
				 }												u;
}		 QWM_INFO_EX;



//  2007/08/03, ÓÃÓÚÔÚregInfoµÄÖÚ¶à×Ö¶ÎÀïºÍÊý¾Ý¿âµÄ´æ´¢Ë³Ðò¼ä×ö×ª»»
//
typedef  struct  __qnmField_t									{
				 TCHAR							*				ptr;
				 TCHAR							*				pName;
				 unsigned  int									bufSize;		//  ×¼±¸´æ·ÅÊý¾ÝµÄbuf´óÐ¡(°üº¬'\0')
				 int											iDataType;		//  Êý¾Ý¿â×Ö¶ÎÀàÐÍ£¬2006/05/03
}		 QNM_FIELD;



////////////////////
//


#define		DEFAULT_nDwLevels									3
#define		CONST_maxnDwLevels									5
#define		CONST_minnDwLevels									3
#define		DEFAULT_nZcbhs										0	//1
#define		CONST_maxnZcbhs										3
#define		CONST_minnZcbhs										0
//
#define		CONST_maxQrtTitleLen								48		//  2005/11/16
#define		CONST_maxQrtHintLen									156		//  2005/07/27


typedef  struct  __qnmCustomComm_t								{
				 unsigned  char									nDwLevels;										//  µ¥Î»µÄ¼¶±ð×ÜÊý
				 unsigned  char									nZcbhs;											//  ×Ê²ú±àºÅµÄ×ÜÊý
}		 QNM_CUSTOM_COMM;


//  ×¢²áÌáÊ¾µÄÐÅÏ¢½á¹¹
typedef  struct  __qwmRegHint_t									{
				 //  char											hintBuf[64  +  1];	//  0308Ç°£¬2005/07/27
				 char											hintBuf[CONST_maxQrtHintLen  +  1];	//  
				 unsigned  char									ucbReged;
				 char											qyRegToolTitle[48  +  1];		//  2003/09/19Ìí¼Ó
				 QNM_CUSTOM_COMM								custom;							//  2005/02/10
}		 QWM_REG_HINT;




#define		CONST_qnmCmd_ok										0								//  ²»²Ù×÷, Î´ÉóºËµ«²»²ÉÓÃ×è¶ÏµÄ·½Ê½Ê±¿É²ÉÓÃ´ËÖÖÖ¸Áî
#define		CONST_qnmCmd_attack									1								//	×è¶Ï
#define		CONST_qnmCmd_audited								2								//  ÒÑÉóºË
#define		CONST_qnmCmd_unChked								3								//  Ãâ¼ì


#define		CONST_qnmStatus_online								0								//  ÔÚÏß
#define		CONST_qnmStatus_offline								1								//  ÀëÏß
#define		CONST_qnmStatus_attacked							2								//  ±»×è¶Ï
#define		CONST_qnmStatus_bProxy								3								//  ÊÇ´úÀí
#define		CONST_qnmStatus_bServer								CONST_qnmStatus_bProxy			//  ÊÇ·þÎñÆ÷


//  pcµÄ²É¼¯ÐÅÏ¢
typedef  struct  __qnmScannedPcInfo_t							{
				 unsigned  long									ulIp;							//  ulIp
				 char											mac[CONST_qyMacLen];			//  mac
				 unsigned  char									ucCmd;							//  Ö¸Áî
				 unsigned  char									ucStatus;						//  ×´Ì¬
				 char											reserved[14];					//  ±£Áô
}		 QNM_SCANNED_PCINFO;




typedef  struct  __qnmChkedIpStruct_t							{

				 //  ÒÔÏÂÊÇ¼ÇÂ¼Êý¾Ý³ÉÔ±
				 char											mac[CONST_qyMacLen  +  1];
				 char											ip[CONST_qyMaxIpLen  +  1];
				 char											lastCommTime[CONST_qyTimeLen  +  1];
				 char											startTime[CONST_qyTimeLen  +  1];
				 char											endTime[CONST_qyTimeLen  +  1];
				 unsigned  char									ucbBwd;

				 //  ÒÔÏÂÊÇ¼ÇÂ¼×´Ì¬Î»
				 unsigned  long									ulbProxy:1;						//  ÊÇ·ñ´úÀí
				 unsigned  long									ulbOffline:1;					//  ÊÇ·ñÀëÏß
				 unsigned  long									ulbAttacked:1;					//  ÊÇ·ñÒÑ×è¶Ï
				 unsigned  long									ulbKnownPc:1;					//  ÊÇ·ñÒÑÈë¿â
				 unsigned  long									ulbAudited:1;					//  ÊÇ·ñÒÑÉóºË
				 unsigned  long									ulbInTmpTab:1;					//  ÊÇ·ñÔÚ¹æÔò¿âÖÐ
				 unsigned  long									ulbLogAttacked:1;				//  ÊÇ·ñ¿âÖÐ¼ÇÂ¼ÒÑ×è¶Ï
				 unsigned  long									ulbUnchked:1;					//  ÊÇ·ñÃâ¼ì
				 unsigned  long									ulbWillAttack:1;				//  ÊÇ·ñÓ¦×è¶Ï
				 
				 char											mac0[CONST_qyMacLen  +  1];		//  Èç¹ûÒÑ±»ÆäËûÊÖ¶Î·¢ÏÖ£¬ÆäÖÐÖ÷ÒªÊÇÖ¸±»Ô­ÓÐµÄ
																								//  ÄÚÍø¹ÜÀíÏµÍ³»ò´úÀí¶Ë·¢ÏÖ£¬Ôò½«ulbKnownPcÖÃÎªTRUE
																								//  ÇÒ¶Á³ömac0·ÅÔÚÕâÀï¡£²¢×÷ÎªºóÃæµÄËùÓÐ¹¤×÷µÄÅÐ¶ÏÒÀ¾Ý¡£

}		 QNM_CHKEDIP_STRUCT;


typedef  struct  __qnmChkedPcCmdInfo_t								{
				 unsigned  char									ucCmd;
				 unsigned  char									reserved[3];
}		 QNM_CHKEDPC_CMDINFO;


typedef  struct  __qwmRasEventInfo_t							{
				 unsigned  char									ucRasCmd;
				 unsigned  char									fullPhoneNum[20 + 1];
}		 QWM_RAS_EVENTINFO;


#if  0  //  2011/09/21
typedef  struct  __qwmEvent_t									{
			 	 long											eventType;										//
				 int											iCustomId;										//
				 char											localEventTime[14  +  1];						//  filled before qnmLogPcEvent
				 union  {
						QWM_RAS_EVENTINFO						ras;
						char									comment[255  +  1];
						char									comments[2][255  +  1];		//  2005/09/11
				 }												u;				 
				 char											usrName[128  +  1];			//  2007/02/18

				 //  ÏÂÃæÎª³ÌÐò¿ØÖÆÐÅÏ¢£¬²»×÷ÎªÍ¨ÐÅÐÅÏ¢£¬2006/03/25
				 unsigned  char									ucbUtf8;					
}		 QWM_EVENT;
#endif

typedef  struct  __qwmEvent_t									{
			 	 long											eventType;										//
				 int											iCustomId;										//
				 char											localEventTime[14  +  1];						//  filled before qnmLogPcEvent
				 union  {
						QWM_RAS_EVENTINFO						ras;
						char									comment[255  +  1];
						char									comments[2][255  +  1];		//  2005/09/11
				 }												u;				 
				 char											usrName[128  +  1];			//  2007/02/18

				 //  2006/03/25
				 unsigned  char									ucbUtf8;					
				 unsigned  short								usQwmDevType;					//  2011/09/21
}		 QWM_EVENT;


//
typedef  struct  __qnmWmBufShowStruct_t							{
				 MACRO_qyWmBuf_commHead

				 QY_SHOW_STRUCT									showStruct;
}		 QNM_WMBUF_SHOWSTRUCT;


//
typedef  struct  __qnmPcInfo_t									{

				 int											iType;												//  2007/04/01

				 unsigned  int									nMacs;
				 char											macs[CONST_qnmMaxMacs][CONST_qyMacLen  +  1];
				 char											ip[CONST_qyMaxIpLen  +  1];
				 char											ips[CONST_qnmMaxMacs][CONST_qyMaxIpLen  +  1];
				 char											startTime[CONST_qyTimeLen  +  1];
				 char											lastCommTime[CONST_qyTimeLen  +  1];

				 char											qwmVer[CONST_qyMaxVerLen  +  1];
				 //  long											lQwmVer;										//  2003/09/13Ìí¼Ó£¬=atol(  qwmVer  )
				 long											lhQwmVer,  llQwmVer;								//  2005/05/23, lhQwmVer  =  atol(  qwmVer  )  /  100;  llQwmVer  =  atol(  qwmVer  )  %  100;
				 //
				 int											iPlatformId;										//  2006/02/15
				 char											osName[CONST_qyMaxOsNameLen  +  1];
				 char											servicePack[CONST_qyMaxServicePackLen  +  1];		//  2003/09/12Ìí¼Ó
				 char											pcName[CONST_qyMaxNameLen  +  1];
				 char											curUsrName[256  +  1];								//  2003/09/12
				 char											proxyServer[255  +  1];								//  2003/09/12
				 unsigned  char									ucbAddedManually;									//  2004/04/11¼Ó

				 BOOL											bReged;
				 char											ownerName[CONST_qyMaxUsrNameLen  +  1];
				 char											officeName[CONST_qnm_maxOfficeNameLen  +  1];
				 char											subOfficeName[CONST_qnm_maxSubOfficeNameLen  +  1];

				 char											glCntIp[CONST_qyMaxIpLen  +  1];

				 void								*			pPcProcessQ;										//  2008/02/29, ½ø³Ì¶ÓÁÐ

}		 QNM_PC_INFO;



typedef  struct	 __qnmRegInfo0104_t								{
				 int											iCustomId;

				 char											mac0[CONST_qyMacLen  +  1];
				 char											regTime[CONST_qyTimeLen  +  1];

				 union											{
					 //  GENERAL_REG_INFO						general;			//  ¶Ô1.01°æ
					 //  SHHG_REG_INFO							shhg;				//  ¶Ô1.01°æ
					 char										cols[CONST_qnmMaxRegFields][256];
				 }												u;
}		 QNM_REG_INFO_0104;


typedef  struct	 __qnmRegInfo0303_t								{
				 int											iCustomId;

				 char											mac0[CONST_qyMacLen  +  1];
				 char											regTime[CONST_qyTimeLen  +  1];
				 char											auditTime[CONST_qyTimeLen  +  1];

				 union											{
					 //  GENERAL_REG_INFO						general;			//  ¶Ô1.01°æ
					 //  SHHG_REG_INFO							shhg;				//  ¶Ô1.01°æ
					 char										cols[CONST_qnmMaxRegFields][256];
				 }												u;
}		 QNM_REG_INFO0303;

//  2005/11/06, Õâ¸ö½á¹¹Ó¦¸ÃÌØ±ð×¢Òâ£¬Ó¦°Ñcols[i][256]µÄ256Àí½â³ÉBUFµÄ³¤¶È
//  ÔÚÍ¨ÐÅÊ±ÓÃUTF8
//  ÔÚ¹ÜÀí¶Ë£¬ÓÃTCHAR£¬ÇÐ¼ÇÇÐ¼Ç
//
typedef  struct	 __qnmRegInfo0333_t								{						//  2007/08/06
				 int											iCustomId;

				 char											mac0[CONST_qyMacLen  +  1];
				 char											regTime[CONST_qyTimeLen  +  1];
				 char											auditTime[CONST_qyTimeLen  +  1];

				 unsigned  int									uiFieldIds[CONST_qnmMaxRegFields];
				 union											{
					 //  GENERAL_REG_INFO						general;			//  ¶Ô1.01°æ
					 //  SHHG_REG_INFO							shhg;				//  ¶Ô1.01°æ
					 char										cols[CONST_qnmMaxRegFields][256];
				 }												u;
}		 QNM_REG_INFO0333;

typedef  struct	 __qnmRegInfo_t									{						//  2007/08/06, ÌØ±ð×¢Òâ1£ºÒòÎªÔÚgetObjId( )ÖÐ£¬Òª´«ÈëregInfoÐÅÏ¢¡£Ô­½á¹¹0333ºÍmessengerRegInfoÎÞ·¨Çø·Ö¡£¹Ê¸ÄÎª´Ë½á¹¹£¬Ìí¼ÓÁË¸öuiType³ÉÔ±
				 unsigned  int									uiType;					//  2007/08/06ÐÂÔö¡£×¢2¡£ÒòÎª´Ë½á¹¹ÊÇÓÃÓÚ×¢²á£¬·Ç³£×¤Í¨ÐÅ¹¦ÄÜ£¬ËùÒÔ¼ÓÒ»³ÉÔ±²¢²»Ó°ÏìºóÐøµÄ°æ±¾¡£
				 //
				 int											iCustomId;

				 char											mac0[CONST_qyMacLen  +  1];
				 char											regTime[CONST_qyTimeLen  +  1];
				 char											auditTime[CONST_qyTimeLen  +  1];

				 unsigned  int									uiFieldIds[CONST_qnmMaxRegFields];
				 union											{
					 //  GENERAL_REG_INFO						general;			//  ¶Ô1.01°æ
					 //  SHHG_REG_INFO							shhg;				//  ¶Ô1.01°æ
					 char										cols[CONST_qnmMaxRegFields][256];
				 }												u;
}		 QNM_REG_INFO;


//  2004/04/21ÐÞ¸Ä
typedef  struct  __qnmPcGrpRcd_t								{
				 char											startIp[15  +  1];
				 char											endIp[15  +  1];
				 char											officeName[64  +  1];
				 char											subOfficeName[64  +  1];
				 char											lanName[16  +  1];
				 unsigned  char									ucbStopSnmpScan;
				 unsigned  char									ucbStopMacScan;
				 char											glCntIp[15  +  1];
				 //  char											mac[12  +  1];
				 //  BOOL											fBwd;					//  ·Ç±¾Íø¶Î
				 //  char											flg[2  +  1];			
}		 QNM_PCGRP_RCD;

//  ÏÂÃæµÄ½á¹¹ÓÃÔÚÏµÍ³ÄÚ²¿Ê¹ÓÃ,²»ÄÜÓÃÀ´´«Êä,2005/11/14
typedef  struct  __qnmEvent_t									{
				 long											id;
				 long											lHelpRand;										//	2003/11/15
				 char											macs[CONST_qnmMaxMacs][CONST_qyMacLen  +  1];	//  macs[0] filled before qnmLogPcEvent
				 char											ip[15  +  1];									//  ip must be filled before qnmLogPcEvent
				 TCHAR											productName[128  +  1];							//	Éè±¸ÐÍºÅ£¬2004/03/01
				 long											lEventType;										//  eventType must be filled before qnmLogPcEvent
				 int											iCustomId;										//  iCustomId must be filled before qnmLogPcEvent
				 char											localEventTime[14  +  1];						//  localEventTime must be filled before qnmLogPcEvent
				 char											localCntEventTime[14  +  1];					//  ´«Èë¹ÜÀíÖÐÐÄµÄ±¾µØµÄÊ±¼ä
				 char											cntEventTime[14  +  1];							//  ´«Èë¹ÜÀíÖÐÐÄµÄ¹ÜÀíÖÐÐÄµÄÊ±¼ä
				 TCHAR											comment[255  +  1];
				 TCHAR											cols[CONST_qnmMaxEventRegFields][255  +  1];	//  ÊÂ¼þ´¥·¢ÕßµÄÐÅÏ¢10ÁÐ   
				 TCHAR											usrName[255  +  1];
				 char											connectedMac[CONST_qyMacLen  +  1];
				 int											iPortIfIndex;
				 TCHAR											deses[CONST_qnmMaxEventDesFields][255  +  1];	//  ÊÂ¼þÃèÊö±¾ÉíµÄÐÅÏ¢10ÁÐ				 
				 TCHAR											dsnName[128  +  1];								//  2007/01/02
				 int											iStatus;										//  2006/06/02, Ôö¼Ó¶ÔÊÂ¼þµÄ´¦Àí×´Ì¬µÄÃèÊö
}		 QNM_EVENT;		
#define		QNM_PC_EVENT		QNM_EVENT	//  2004/04/14½«QNM_PC_EVENTÐÞ¸ÄÎª¸üÍ¨ÓÃµÄÃû³Æ

//  2004/05/15¼Ó
#define		CONST_cusNameType_null								0
#define		CONST_cusNameType_pcSp								1
#define		CONST_cusNameType_pcRegInfo							2					//  ÓÃ»§¹æ·¶ÐÅÏ¢£¬2006/09/02

//
#define		CONST_maxCusNameCols								8					//  Ñ¡Ôñ8ÊÇÒòÎªaccessÖ»ÔÊÐí×î¶à10¸ö×Ö¶ÎµÄ¼üÖµ
typedef  struct  __qyCusNameRcd_t								{
				 int											id;
				 int											iType;
				 unsigned  int									uiLangId;
				 TCHAR											objNames[CONST_maxCusNameCols][255  +  1];
				 TCHAR											cusNames[CONST_maxCusNameCols][255  +  1];
				 //  char										comment0[255  +  1];
}		 QY_CUSNAME_RCD;


//  ¼ì²é¹¤¾ßµÄ´«Êä½á¹¹	2003/11/15 
//  {

//  ¼ì²éÊÂ¼þ´«ÊäÇ°µÄÐ­µ÷
typedef  struct  __qnmSecChkCommHead_t							{
				 long											lEventCnt;			//  ÊÂ¼þÌõÊý
				 unsigned  int									uiEventSndSize;		//  ÊÂ¼þ·¢ËÍ´óÐ¡
				 union											{
					 char										reserved[256];
				 }												u;
}		 QNM_SECCHK_COMMHEAD;


//  ¼ì²é¹¤¾ßµÄÊÂ¼þÃèÊöµÄ½á¹¹
typedef  struct  __qnmSecChkEvent_t								{
				 long											lEventType;
				 char											localCntEventTime[14  +  1];	//  ´«Èë¹ÜÀíÖÐÐÄµÄ±¾µØÊ±¼ä
				 char											localEventTime[14  +  1];		//  ÊÂ¼þµÄ±¾µØÊ±¼ä
				 char											usrName[32  +  1];
				 char											des0[255  +  1];				//  ÊÂ¼þÃèÊö
				 char											des1[32  +  1];					//  ÊÂ¼þÃèÊö1, 2004/03/14												
				 char											des2[32  +  1];					//  ÊÂ¼þÃèÊö2
}		 QNM_SECCHK_EVENT;



typedef  struct  __qnmWmBufShowSecChkEvent_t					{
				 MACRO_qyWmBuf_commHead

				 QNM_SECCHK_EVENT								event;

}		 QNM_WMBUF_SHOWSECCHKEVENT;


//  }


//  {

#define		CONST_opCmd_null									0
#define		CONST_opCmd_viewRemoteDesktop						1		//  ÒªÇóÏÔÊ¾Ô¶³Ì×ÀÃæ
#define		CONST_opCmd_monDesktop								2		//  ÒªÇóÊµÊ±¼à¿Ø×ÀÃæ



#define		CONST_cmdStatus_null								0	//  ×´Ì¬Î»²»¸³»òÎª0±í´ýÖ´ÐÐ
#define		CONST_cmdStatus_start								1
#define		CONST_cmdStatus_end									2	//  ½áÊø
#define		CONST_cmdStatus_err									3	//  ³ö´íÖÕÖ¹
#define		CONST_cmdStatus_restart								4


typedef  struct  __pcStatusInfo_t								{
				 //  int											iObjType;					//  CONST_objType_syr
				 char											mac0[CONST_qyMacLen  +  1];
				 unsigned  char									ucbOped;
				 unsigned  char									ucbViewRemoteDesktop;
				 unsigned  char									ucbMonDesktop;				//  ÊµÊ±ÆÁÄ»¼à¿Ø
				 QNM_PC_INFO									pcInfo;
				 QNM_REG_INFO									regInfo;					//  2006/09/03
}		 PC_STATUS_INFO;





//  È¡ÅäÖÃÊ±´«µÝ¸ø¿Í»§¶ËµÄ²Ù×÷Ö¸Áî
typedef  struct  __qnmPcOpRule_t								{
				 unsigned  char									ucbOped;
				 unsigned  char									reserved[15];
}		 QNM_PCOP_RULE;




//  }


typedef  struct  __nmsScanStruct_t		{
				
				 int					iNmsOp;
				 int					iNmsOpCmd;					//  
				 void				*	pfThreadProc;
				 void				*	pf;
				 void				*	pParentParam;				//  2004/08/16

				 WCHAR					showWho[64];
				 WCHAR				*	pRegValName;
				 char					whereClause[256];
				 
				 unsigned  char			ucbStopScan;
				 
}		 NMS_SCAN_STRUCT;


#define		CONST_qyAppName_qySnmpHelp			"qySnmpHelp.exe"


#define		CONST_nmsOp_snmpScan				0		//  È±Ê¡
#define		CONST_nmsOp_nbtScan					1

extern  QY_DMITEM  CONST_nmsOpTable[];

extern  QY_DMITEM	CONST_qyPlatformTable[];
TCHAR	*			qyPlatformStr(  int  iPlatform  );

#if  0
#define		CONST_qyPlatformStr_unknown		CONST_qyPlatformTable[0].des
#define		CONST_qyPlatformStr_win32		CONST_qyPlatformTable[1].des
#define		CONST_qyPlatformStr_win95		CONST_qyPlatformTable[2].des
#define		CONST_qyPlatformStr_win98		CONST_qyPlatformTable[3].des
#define		CONST_qyPlatformStr_winme		CONST_qyPlatformTable[4].des
#define		CONST_qyPlatformStr_winnt		CONST_qyPlatformTable[5].des
#define		CONST_qyPlatformStr_win2k		CONST_qyPlatformTable[6].des
#define		CONST_qyPlatformStr_winxp		CONST_qyPlatformTable[7].des
#endif


/*
#define		CONST_nmsOpStr_snmpScan				"snmpScan"
#define		CONST_nmsOpStr_nbtScan				"nbtScan"
#define		CONST_nmsOpStr_snmpScanNetFlow		"snmpNetFlow"
*/


//

//  #define		CONST_grpName_admin					"¹ÜÀíÔ±×é"
//  #define		CONST_grpName_xtpz					"ÏµÍ³ÅäÖÃ×é"
//  #define		CONST_grpName_rzsj					"ÈÕÖ¾Éó¼Æ×é"
#define		CONST_grpName_admin					"adminGrp"  		//  °Ñ×éÃûºÍÏÔÊ¾·Ö¿ª£¬2005/09/30
#define		CONST_grpName_xtpz					"sysGrp"  
#define		CONST_grpName_rzsj					"logGrp"  
//
#define		CONST_usrName_admin					"admin"
#define		CONST_adminInitialPasswd			"admin"
#define		CONST_adminInitialEncXPasswd		"923b56hnw"
//
#define		CONST_usrName_sysAdmin				"sysadmin"
#define		CONST_sysAdminInitialPasswd			"sysadmin123"
#define		CONST_sysAdminInitialEncXPasswd		"f3f9f3e1e4ede9eeb1b2b3"
//
#define		CONST_usrName_logAdmin				"logadmin"
#define		CONST_logAdminInitialPasswd			"logadmin123"
#define		CONST_logAdminInitialEncXPasswd		"ecefe7e1e4ede9eeb1b2b3"


//////////////////////////////////////////
//

#define		CONST_fakedFactor_percentOfBand						1000							//  ·Å´óÒò×Ó£¬Ê¹warnPercentOfBandÒÔ·Å´óÒ»Ç§±¶´æ´¢



#define		CONST_qnmFakedMac									"001122334455"  
#define		CONST_NPFServiceName								TEXT(  "NPF"  )
#define		CONST_NPFRegistryLocation							TEXT("SYSTEM\\CurrentControlSet\\Services\\NPF")
#define		CONST_qnmNullPcSp									"00000000"

#define		CONST_ip_localhost									"127.0.0.1"			//  2007/03/28


typedef  int  (  *	PF_qyDelService  )(  char  *  serviceName  );




//  int  qyntohCfgItem(  QY_CFGITEM  *  pItem  );
int  qyntohCfgItem(  char  *  p,  QY_CFGITEM_ntoh_U  *  pItem  );
int  qyhtonCfgItem(  QY_CFGITEM  *  pItem  );
int  qyntohCommServiceResp(  QY_COMM_SERVICERESP  *  p  );
int  qyhtonCommServiceResp(  QY_COMM_SERVICERESP  *  p  );
int  qyntohQwmEvent(  QWM_EVENT  *  pEvent  );
int  qyhtonQwmEvent(  QWM_EVENT  *  pEvent  );
int  qyntohQnmSecChkCommHead(  QNM_SECCHK_COMMHEAD  *  pSecChkCommHead  );
int  qyhtonQnmSecChkCommHead(  QNM_SECCHK_COMMHEAD  *  pSecChkCommHead  );
int  qyntohQnmSecChkEvent(  QNM_SECCHK_EVENT  *  pEvent  );
int  qyhtonQnmSecChkEvent(  QNM_SECCHK_EVENT  *  pEvent  );
int  qyntohQwmInfo(  QWM_INFO  *  pQwmInfo  );
int  qyhtonQwmInfo(  QWM_INFO  *  pQwmInfo  );
int  qyntohQwmInfoEx(  QWM_INFO_EX  *  pQwmInfoEx  );
int  qyhtonQwmInfoEx(  QWM_INFO_EX  *  pQwmInfoEx  );
int  qyhtonShowQwmSvrStatus(  QNM_CMDPARAM_showQwmSvrStatus  *  pStatus  );
int  qyntohShowQwmSvrStatus(  QNM_CMDPARAM_showQwmSvrStatus  *  pStatus  );


//  2007/05/08
time_t  gettTimeBylStr(  char  *  timeBuf  );
int  getTimeStr(  time_t  t,  char  *  timeBuf,  unsigned  int  size  );

BOOL  b2TimeNear(  char  *  time1,  char  *  time2,  int  interval  );
int  getTimeByInterval(  char  *  oldTime,  int  interval,  char  *  newTime,  unsigned  int  newTimeSize  );

//int  waitForObject(  HANDLE  *  ph, DWORD  dwMilliseconds   );  


//
BOOL  bObjTypeGrp(unsigned int  uiObjType);

//
BOOL  bTaskAlive(  int  iStatus  );
bool bTaskNeedAcception(int iStatus);



//
char  *  qyStdToIp12(  char  *  ip,  char  *  ip12  );
char  *  qyIp12ToStd(  char  *  ip12,  char  *  ip  );
//
char  *  ulIp2Str(  unsigned  long  lVal,  char  *  ip,  unsigned  int  size  );


int  qyGetRegCfgT(  HKEY  hKeyRoot0,  LPCTSTR  rootKey,  LPCTSTR  cfgName,  char  *  cfgVal,  int  size,  unsigned  int  *  puiType  );
int  qySetRegCfgT(  HKEY  hRoot,  LPCTSTR  rootKey,  LPCTSTR  cfgName,  LPCTSTR  cfgVal  );
int  qyDelRegCfgT(  HKEY  hKeyRoot0,  LPCTSTR  rootKey,  LPCTSTR  cfgName  );

int		qyGetRegCfgEx(  QY_REG  *  pReg,  LPCTSTR  cfgName,  char  *  cfgVal,  int  size  );
int		qySetRegCfgEx(  QY_REG  *  pReg,  LPCTSTR  cfgName,  LPCTSTR  cfgVal  );
int		qyGetRegDataEx(  QY_REG  *  pReg,  LPCTSTR  cfgName,  char  *  cfgVal,  unsigned  long  *  pDataLen  );
int		qySetRegDataEx(  QY_REG  *  pReg,  LPCTSTR  cfgName,  char  *  data,  unsigned  long  dataLen  );

//  int  myStr2Utf8(  char  *  buf,  unsigned  int  size  );
//  int  myUtf82Str(  char  *  buf,  unsigned  int  size  );
char  *  myStr2Utf8(  char  *  buf,  unsigned  int  size  );
char  *  myUtf82Str(  char  *  buf,  unsigned  int  size  );
WCHAR  *    myStr2WChar(  const  char  *  str,  WCHAR  *  wBuf,  unsigned  int  wBufSize  );
char  *  myWChar2Str(  LPCWSTR,  char  *  buf,  unsigned  int  bufSize  );
char  *  myWChar2Utf8(  LPCWSTR  wStr,  char  *  buf,  unsigned  int  bufSize  );
WCHAR  *    myUtf82WChar(  char  *  str,  WCHAR  *  wBuf,  unsigned  int  wBufSize  );

//  2007/03/31

//
int  getFieldData_long(  QY_CFGITEM_ntoh_U  *  pItem,  long  *  plVal  );
int  getFieldData_char(  QY_CFGITEM_ntoh_U  *  pItem,  char  *  pcVal  );
int  getFieldData_short(  QY_CFGITEM_ntoh_U  *  pItem,  short  *  psVal  );
int  getFieldData_l64(  QY_CFGITEM_ntoh_U  *  pItem,  __int64  *  pl64Val  );
int  getFieldData_data(  QY_CFGITEM_ntoh_U  *  pItem,  char  *  val,  unsigned  int  *  pSize  );
int  getFieldData_lData(  QY_CFGITEM_ntoh_U  *  pItem,  char  *  val,  unsigned  int  *  pSize  );
int  getFieldData_str(  QY_CFGITEM_ntoh_U  *  pItem,  char  *  val,  unsigned  int  size  );
int  getFieldData_wStr(  QY_CFGITEM_ntoh_U  *  pItem,  WCHAR  *  val,  unsigned  int  size  );

//
int  safeWcsCpy(  LPCWSTR  strIn,  WCHAR  *  strOut,  unsigned  int  size  );
void  safeWcsnCpy(  LPCWSTR  strIn,  WCHAR  *  strOut,  unsigned  int  size  );


char  *  qnmVerStr(  int  iServiceId  );
char  *  qnmDbVerStr(  int  iServiceId  );

//  2014/09/23
int  parse_qnmVerStr(  char  *  ver,  unsigned  short  *  pshVer,  BYTE  *  pblVer,  BYTE  *  pb_mantissa_ver  );



extern  BOOL		g_bIsWinNT;
//
//void  GetOSVersion( );
//
int initDynLib(  void  **  pp  );
int exitDynLib(  void  **  pp  );
//
int  qnmCompareMacs(  const  void  *  arg1,  const  void  *  arg2  );
int  sortQwmMacs(  QWM_MACS_INFO  *  pMacsInfo  );
void  getQwmMacs(  QY_ENV  *  pEnv,  QWM_MACS_INFO  *  pMacsInfo  );
void  getQwmSortedMacs(  QY_ENV  *  pEnv,  QWM_MACS_INFO  *  pMacsInfo  );
int  qyGetRemoteMacByIp(  QY_ENV  *  pEnv,  char  *  fakedIp,  char  *  mac,  unsigned  int  macSize  );

int mystricmp(  const char *string1,  const TCHAR *t_string2  );

int  attackHost(  char  *  fakedIp,  void  *  l  );


//  2007/03/11
typedef  struct  __qnmSysCfgInfo_t						{
				 int									iSystemId;
				 int									iAppType;
				 unsigned  char							ucbDnsless;				
				 TCHAR								*	defaultDbName;				//  ÔÚÎÞDSNµÄÇé¿öÏÂ£¬ÊÇÈ±Ê¡µÄdbFileµÄÃû×ÖÇ°×ºÁË¡£ÓÐDSNÊ±£¬ÎªÊý¾ÝÔ´Ãû 
				 TCHAR								*	rootKey_mcGui;				//  2007/06/16
				 TCHAR								*	rootKey_qnmScheduler;
}		 QNM_SYSCFG_INFO;


//  ¹ÜÀí¶ËµÄÄ³Ð©ÅäÖÃÐÅÏ¢
typedef  struct  __qnmGuiCfgInfo_t						{
				 int									iSystemId;
				 int									iAppType;
				 char								*	qmCfgPureFile;				//  一般为软件自己所用
				 char								*	qmCfgIniFile;				//  2009/07/29，可以被用户编辑
				 char								*	splashBmpPureFile;
				 char								*	helpPureFile;

				 unsigned  char							ucbCfgNotAllAllowed;		//  netMc2
				 unsigned  char							ucbSupportNbtScan;
				 unsigned  char							ucbSupportSnmpScan;

				 int									iResId_popupMenu_procedObj;
				 //

				 unsigned  short						nSubMenuPos_pcList;
				 unsigned  short						nSubMenuPos_eventList;				 
				 unsigned  short						nSubMenuPos_netDevEventList;
				 unsigned  short						nSubMenuPos_searchList;
				 //
				 
				 int									iResId_sys;
				 
}		 QNM_GUICFG_INFO;

__declspec(  dllexport  )  QNM_SYSCFG_INFO	*	getQnmSysCfgInfo(  int  iSystemId,  int  iAppType  );
QNM_GUICFG_INFO	*	getQnmGuiCfgInfo(  int  iSystemId,  int  iAppType  );

//  2007/04/07, qmCommonProc.cppÀïµÄº¯Êý
__declspec(  dllexport  )  int  getCfgValByName(  LPCTSTR  cfgFile,  char  *  cfgName,  char  *  cfgVal,  int  size  );
__declspec(  dllexport  )  int  getCfgValByNameT(  LPCTSTR  cfgFile,  TCHAR  *  cfgName,  TCHAR  *  cfgVal,  int  size  );
__declspec(  dllexport  )  BOOL  bQmAdvancedVer(  void  *  p0,  LPCTSTR  cfgFullFileName,  void  *  p2  );

//  2015/07/18
LPCTSTR  get_who_showInfo(  void  *  pCtx,  int  iCtxType  );

//
char  *  qnmBatIp(  char  *  ip,  unsigned  int  size  );
char  *  qnmCntIp(  char  *  ip,  unsigned  int  size  );
int  qnmCntPort(  int  iServiceId  );
int  getQnmCntCfg(  void  *  p0,  BOOL  bServer,  int  iServiceId,  HKEY  hKeyRoot0,  LPCTSTR  rootKey_qnmScheduler,  QNM_CNT_CFG  *  pCfg  );

int  qnmInstallDriver(  unsigned  short  idrData,  char  *  drvName  );
int  qnmRemoveDriver(  char  *  drvName,  PF_qyDelService  pf  );

int  makeQwmAuthInfo(  char  *  ver,  QWM_MACS_INFO  *  pMacsInfo,  QNM_COMM_AUTHINFO  *  pNai  );
int  qwmGetPcName(  char  *  pcName,  unsigned  int  len  );
int  qnmOpenSession(  char  *  servIp,  unsigned  short  usPort,  QWM_MACS_INFO  *  pMacsInfo,  unsigned  char  ucCmd,  int  iServiceId,  char  *  ver,  void  *  pEncCtx,  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  char  *  data,  unsigned  int  *  piDataSize  );
void  qnmCloseSession(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo  );
BOOL  bServConnected(  QY_ENV  *  pEnv,  char  *  serverIp,  unsigned  short  serverPort,  void  *  pMacsInfo_notused,  int  serviceId,  char  *  ver,  QY_ENC_CTX  *  pCommEncCtx,  SOCK_TIMEOUT  *  pTo  );

//
//  int  getQyEnv(  QY_ENV  *  pEnv  );
int  getQyEnv(  void  *  pDynLibs,  QY_ENV  *  pEnv  );

//
int  parseQwmDynCfg(  char  *  pQyCfgs,  unsigned  int  uiCfgSize,  QWM_DYN_CFG  *  pDynCfg  );

int  getIpFromName(  char  *  name,  char  *  ip,  unsigned  int  size  );

typedef  BOOL  (  *  PF_bServConnected  )(  QY_ENV  *  pEnv,  char  *  serverIp,  unsigned  short  serverPort,  void  *  pParam,  int  serviceId,  char  *  ver,  QY_ENC_CTX  *  pCommEncCtx,  __int64  i64StartTime_base,  SOCK_TIMEOUT  *  pTo  );
//
int  getCorrectCnt(  QY_ENV  *  pEnv,  QWM_DYN_CFG  *  pDynCfg,  PF_bServConnected  pf_bServConnected,  void  *  pParam,  int  serviceId,  char  *  ver,  QY_ENC_CTX  *  pCommEncCtx,  __int64  iStartTime_base,  SOCK_TIMEOUT  *  pTo,  QY_LOGICAL_SERVER  *  pCnt  );


BOOL  bQnmModuleInstalled(  char  *  rootKey_mc,  char  *  moduleName  );
int  getQnmModulesLoadedInfo(  QNM_MODULES_LOADEDINFO  *  p  );
//
int  getDirAndFinalName_win(  LPCTSTR  svFileName,  TCHAR  *  dirName,  unsigned  int  size,  TCHAR  *  finalName,  unsigned  int  finalNameSize    );






DWORD  WINAPI  qnmSnmpNetFlowThreadProc(  LPVOID  lp  );
DWORD  WINAPI  qnmCommonScanThreadProc(  LPVOID  lp  );
int  qnmScanFunc(  void  *  pDaemonParam,  void  *  pScanStructParam,  void  *  pPcGrpInfoParam  );



//
int  errLog(  char  *  fmt,  ...  );


//  2006/08/13
#define myMAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define myMAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define myLOWORD(l)           ((WORD)(l))
#define myHIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define myLOBYTE(w)           ((BYTE)(w))
#define myHIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))
//
#define myMAKEWPARAM(l, h)      (WPARAM)myMAKELONG(l, h)
#define myMAKELPARAM(l, h)      (LPARAM)myMAKELONG(l, h)
#define myMAKELRESULT(l, h)     (LRESULT)myMAKELONG(l, h)




#ifdef  __DEBUG__
  int  printSystemId(  );
  int  printDefaultQyCustomId(  );
  int  printQwmMacsInfo(  char  *  hint,  QWM_MACS_INFO  *  pMacsInfo  );
  int  printQnmRegInfo(  QNM_REG_INFO  *  pRegInfo  );  
#endif

#ifdef  __cplusplus
  }
#endif


//
typedef  struct  __ctx_stream2Data_t  {
				 //
				 unsigned  int			uiStreamIds[5];
				 //
				 int  index_streamId;
}			CTX_stream2Data;



int  data2Stream(  int  iDataType,  unsigned  short  usCfgId,  void  *  orgData,  unsigned  int  orgDataSize,  char  **  pptr_usable,  unsigned  int  *  pSize_usable  );
//  typedef  int  (  *  PF_handler_stream2Data  )(  LPVOID  p0,  LPVOID  p1,  unsigned  int  uiStreamId,  LPVOID  p3  );				//  
typedef  int  (  *  PF_handler_stream2Data  )(  CTX_stream2Data  *  pCtx,  LPVOID  p0,  LPVOID  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  );	//  
int  stream2Data(  char  **  pCfgsBuf_usable,  unsigned  int  *  pSize_usable,  PF_handler_stream2Data  pf_filter,  PF_handler_stream2Data  pf,  void  *  p0,  void  *  p1  );
//


#endif  /*  }  */



