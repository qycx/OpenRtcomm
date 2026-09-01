
#ifndef  __BHBSRC1COMMPROC_H__
#define  __BHBSRC1COMMPROC_H__	/*  {  */

//  以下摘自bhbSrc1的qwmCfg.h"
//#define		CONST_qwmFlg_intraRestricted						//  当此项被定义时，探测端被限制输入  

#define		CONST_qwmVerStr							"3.0.2"
#define		CONST_maxQwmScannedSegs					64			//  定义被限制的最大的扫描网段数


BOOL  bQwmScannedPcsRestricted(  );
int  restrictScannedPcs(  unsigned  int  *  puiPcsCnt,  BOOL  *  pbDel );


//  #define		DEFAULT_AWM_EXT_DSN_NAME				"awmExtDsn"
#define		CONST_qyDsn_netMc						"qyNetMcDsn"		//  2003/11/25加
#define		DEFAULT_AWM_EXT_DSN_NAME				CONST_qyDsn_netMc	//  2003/11/25为实现安检系统的融合，作此修改


//  以下信息摘自diadetect的stdafx.h

#define  ROOT_AWM_KEY										"Software\\Asr\\Awm"
	#define  AWM_START_STOP_KEY									"stopMon"

#define  ROOT_AWM_INTRAMON_KEY								"Software\\asr\\awm\\intramon"
#define  ROOT_AWM_INTRA_MON_KEY								ROOT_AWM_INTRAMON_KEY
  #define  CONST_regValName_newInterMonIp0						"newInterMonIp0"			//  added by ywm on 2002/10/09
  #define  CONST_regValName_newInterMonIp1						"newInterMonIp1"			//  added by ywm on 2002/10/09
  #define  CONST_regValName_newInterMonIp2						"newInterMonIp2"			//  added by ywm on 2002/10/09
  #define  CONST_regValName_newInterMonIp3						"newInterMonIp3"			//  added by ywm on 2002/10/09
  #define  AWM_CHK_DOMAIN_CTRL_SERVER_IP_KEY					"intramonip"
  #define  CONST_regValName_scanIntervalInSecond				"scanIntervalInSecond"  
  #define  CONST_regValName_scanIntervalPerCNetSegInSecond		"scanIntervalPerCNetSegInSecond"
  #define  CONST_regValName_scanIntervalPerPcInMilliSecond		"scanIntervalPerPcInMilliSecond"


#define  ROOT_AWM_INTERMON_KEY								"Software\\asr\\awm\\intermon"
  #define  CONST_regValName_newInterMonIp0						"newInterMonIp0"			//  added by ywm on 2002/10/09
  #define  CONST_regValName_newInterMonIp1						"newInterMonIp1"			//  added by ywm on 2002/10/09
  //  #define  CONST_regValName_warnOn								"warnOn"
  //  #define  CONST_regValName_warnUntilUsrStopIt					"warnUntilUsrStopIt"
  #define  CONST_regValName_maxWarnElapse						"maxWarnElapse"
  //  #define  CONST_regValName_emergencyTime						"emergencyTime"
  //  #define  CONST_regValName_newEmergency						"newEmergency"
  #define  CONST_regValName_stopPermitNat						"stopPermitNat"

#define		ROOT_AWM_INTER_MON_TOOL_KEY						"Software\\Asr\\Awm\\interMonTool"

#define  CONST_max_nScanIntervalInSecond						86400
#define  CONST_min_nScanIntervalInSecond						5
#define  CONST_max_nScanIntervalPerCNetSegInSecond				3600
#define  CONST_min_nScanIntervalPerCNetSegInSecond				5
#define  DEFAULT_nScanIntervalPerCNetSegInSecond				10
#define  CONST_max_nScanIntervalPerPcInMilliSecond				1000


#define COMPUTER_IP_INFO struct computer_ip_info
COMPUTER_IP_INFO
{
	char  interMonIp[16];
	char  cUnitInfo[8+1];
	char  cSubOffice[8+1];
	char  cStartIp[15 + 1];
	char  cEndIp[15 + 1];
};


typedef  struct  __onlineComputerTabRcd_t				{

				 char									officeName[8 + 1];
				 char									subOfficeName[8 + 1];
				 char									ip[15 + 1];
				 char									mac[CONST_qyMacLen  +  1];	//  2004/05/22
				 char									compName[16  +  1];			//  2004/05/23
				 char									usrName[16  +  1];			//  2004/05/23
				 unsigned  char							is_server;					//  2004/05/23

				 char									firstRecvdTime[14 + 1];
				 char									lastRecvdTime[14 + 1];

				 unsigned  char							ucbIpOnly;			//  指示量，非库成员，用于在TCPSCAN中
				 unsigned  char							ucbOnlyIpFound;		//  指示量，非库成员，指前面的记录仅找到了IP(指TCPScan记录)

}														ONLINE_COMPUTER_TAB_RCD;

typedef  struct  __offlineComputerLogTabRcd_t			{
	
				 int									index;
				 char									officeName[8 + 1];
				 char									subOfficeName[8 + 1];
				 char									ip[15 + 1];
				 char									mac[CONST_qyMacLen  +  1];	//  2004/05/22
				 char									compName[16  +  1];			//  2004/05/23
				 char									usrName[16  +  1];			//  2004/05/23
				 unsigned  char							is_server;					//  2004/05/23

				 char									firstRecvdTime[14 + 1];
				 char									lastRecvdTime[14 + 1];

}														OFFLINE_COMPUTER_LOG_TAB_RCD;


#endif  /*  }  */

