
#ifndef  __QNMPCCOMM_H__
#define	 __QNMPCCOMM_H__  //  {

#ifdef  __cplusplus
  extern  "C"  {
#endif


//  #define		MACRO_qyPcCommHead			unsigned  int  uiType;  unsigned  int  uiSize;  unsigned  char  ucFlg;  char  reserved[7];	int  iPlatformId;  unsigned  int  uiLangId;  char  winDir[255  +  1];		
#define		MACRO_qyPcCommHead			unsigned  int  uiType;  unsigned  int  uiSize;  unsigned  char  ucFlg;  char  reserved[7];	int  iPlatformId;  unsigned  int  uiLangId;  char  winDir[255  +  1];  unsigned  int  cnt;		//  2005/08/31

//  2017/08/27
#include	"imCommType_defs.h"



//  为进程管理设置的规则



typedef  struct  __qyProcessProp0326_t					{
				 DWORD									dwPid;
				 char									appPath[256];
				 DWORD									dwPpid;				//  父进程
				 DWORD									dwCpuPercent;		//  CPU占有率
				 DWORD									dwCpuTime;			//  CPU时间
				 DWORD									dwMemInK;			//  内存大小
				 DWORD									dwVmemInK;			//  虚存大小
				 DWORD									dwHandles;			//  句柄数
				 DWORD									dwThreads;			//  线程数				 		
}		 QY_PROCESS_PROP0326;


//
#define		CONST_maxProcesses							256
typedef  struct  __qyPcProcesses0326_t						{
				 MACRO_qyPcCommHead
				 //  unsigned  int						cnt;
				 QY_PROCESS_PROP0326						mems[CONST_maxProcesses];
}		 QY_PC_PROCESSES0326;

///////////////

typedef  struct  __qyProcessProp_t						{
				 DWORD									dwPid;
				 char									appPath[256];
				 DWORD									dwPpid;				//  父进程
				 DWORD									dwCpuPercent;		//  CPU占有率
				 DWORD									dwCpuTime;			//  CPU时间
				 DWORD									dwMemInK;			//  内存大小
				 DWORD									dwVmemInK;			//  虚存大小
				 DWORD									dwHandles;			//  句柄数
				 DWORD									dwThreads;			//  线程数				 		
				 char									cmdLine[128];		//  2006/09/06, 增加此命令行参数，以更了解进程的行为
}		 QY_PROCESS_PROP;


typedef  struct  __qyPcProcesses_t						{
				 MACRO_qyPcCommHead
				 //  unsigned  int						cnt;
				 QY_PROCESS_PROP						mems[CONST_maxProcesses];
}		 QY_PC_PROCESSES;


////////////////


typedef  struct  __qyPcProcessModuleProp_t				{					//  2006/04/14
				 DWORD									dwPid;
				 char									modulePath[256];
				 DWORD									dwParam0;			//  
				 DWORD									dwParam1;			//  
				 DWORD									dwParam2;			//  
				 DWORD									dwParam3;			//  
				 DWORD									dwParam4;			//  
}		 QY_PCPROCESSMODULE_PROP;


typedef  struct  __qyPcProcessModules_t					{					//  2006/04/14
				 MACRO_qyPcCommHead
				 //  unsigned  int						cnt;
				 QY_PCPROCESSMODULE_PROP				mems[CONST_maxProcesses];
}		 QY_PC_PROCESSMODULES;


////////////////

#define		CONST_iDataType_moduleName					SQL_WVARCHAR
#define		CONST_iDataType_modulePath					SQL_WVARCHAR
#define		CONST_iDataType_cmdLine						SQL_WVARCHAR						//  2006/09/06
#define		CONST_iDataType_cusName						SQL_WVARCHAR						//  2006/05/03后的別名都將為這??型


typedef  struct  __qyPcProcessRcd_t						{									//  2006/04/16
				 int									id;
				 unsigned  int							uiType;
				 char									mac0[12  +  1];
				 unsigned  int							uiLangId;
				 int									iPlatformId;
				 char									winDir[255  +  1];
				 unsigned  int							dwPid;
				 TCHAR									moduleName[255  +  1];
				 TCHAR									modulePath[255  +  1];
				 TCHAR									myModulePath[255  +  1];
				 TCHAR									cmdLine[255  +  1];					//  2006/09/06
				 unsigned  int							dwPpid;
				 unsigned  int							dwCpuPercent;								//  CPU占有率
				 unsigned  int							dwCpuTime;									//  CPU时间
				 unsigned  int							dwMemInK;									//  内存大小
				 unsigned  int							dwVmemInK;									//  虚存大小
				 unsigned  int							dwHandles;									//  句柄数
				 unsigned  int							dwThreads;									//  线程数
				 //
				 //						"iProp0						int,"
				 //						"iProp1						int,"
				 //						"iProp2						int,"
				 //						"iProp3						int,"
				 //						"iProp4						int,"
				 //						"iProp5						int,"
				 //						"iProp6						int,"
				 //						"iProp7						int,"
				 //						"iProp8						int,"
				 //						"iProp9						int,"
				 //						"propStr0					varchar(255),"
				 //						"propStr1					varchar(255),"
				 //						"propStr2					varchar(255),"
				 //						"propStr3					varchar(255),"
				 //						"propStr4					varchar(255),"
				 //						"propStr5					varchar(255),"
				 //						"propStr6					varchar(255),"
				 //						"propStr7					varchar(255),"
				 //						"propStr8					varchar(255),"
				 //						"propStr9					varchar(255),"
				 //
				 char										firstTime[14  +  1];
				 char										lastTime[14  +  1];
				 int										iStatus;
				 //						"comment0					varchar(255)"

				 void						*			pInternal;					//  以下为内部处理变量
				 BOOL									bExists;

}		  QY_PCPROCESS_RCD;



typedef  struct  __qyPcModuleKnowledgeRcd_t					{
				 int										id;
				 unsigned  int								uiType;
				 TCHAR										fileName[255  +  1];					//  文件名
				 TCHAR										cmdLine[255  +  1];
				 TCHAR										name[255  +  1];						//  名称
				 TCHAR										des0[255  +  1];						//  描述
				 TCHAR										company[255  +  1];						//  公司
				 TCHAR										product[255  +  1];						//  产品
				 unsigned  char								ucbSys;									//  是否系统文件
				 unsigned  char								ucbDaemon;								//  是否后台程序
				 unsigned  char								ucbUseNet;								//  是否使用网络
				 unsigned  char								ucbHardware;							//  是否硬件相关
				 TCHAR										commonErr[255  +  1];					//  常见错误
				 TCHAR										memInfo[255  +  1];						//  内存使用
				 unsigned  int								securityLevel;							//  安全等级
				 unsigned  char								ucbSpy;									//  是否间谍软件
				 unsigned  char								ucbAdvertisement;						//  是否广告软件
				 unsigned  char								ucbVirus;								//  是否病毒
				 unsigned  char								ucbBackDoor;							//  是否后门
				 //
				 //						"iProp0						int,"
				 //						"iProp1						int,"
				 //						"iProp2						int,"
				 //						"iProp3						int,"
				 //						"iProp4						int,"
				 //						"iProp5						int,"
				 //						"iProp6						int,"
				 //						"iProp7						int,"
				 //						"iProp8						int,"
				 //						"iProp9						int,"
				 //						"propStr0					varchar(255),"
				 //						"propStr1					varchar(255),"
				 //						"propStr2					varchar(255),"
				 //						"propStr3					varchar(255),"
				 //						"propStr4					varchar(255),"
				 //						"propStr5					varchar(255),"
				 //						"propStr6					varchar(255),"
				 //						"propStr7					varchar(255),"
				 //						"propStr8					varchar(255),"
				 //						"propStr9					varchar(255),"
				 //						//
				 TCHAR										provider[255  +  1];				//  提交者
				 TCHAR										providerAddr[255  +  1];			//  提交者联系方式
				 TCHAR										providerTime[255  +  1];			//  提交时间
				 //
				 char										auditTime[14  +  1];				//  审核时间
				 char										firstTime[14  +  1];				//
				 char										lastTime[14  +  1];					
				 int										iStatus;
}		 QY_PCMODULEKNOWLEDGE_RCD;


/////////////////////

typedef  struct  __qyPcRegistryKnowledgeRcd_t				{
				 int										id;
				 unsigned  int								uiType;
				 int										iRootKey;
				 TCHAR										subKey[255  +  1];
				 TCHAR										cfgName[255  +  1];
				 TCHAR										suggestedVal[255  +  1];
				 TCHAR										name[255  +  1];						//  名称
				 TCHAR										des0[255  +  1];						//  描述
				 TCHAR										company[255  +  1];						//  公司
				 TCHAR										product[255  +  1];						//  产品
				 unsigned  char								ucbSys;									//  是否系统文件
				 unsigned  char								ucbDaemon;								//  是否后台程序
				 unsigned  char								ucbUseNet;								//  是否使用网络
				 unsigned  char								ucbHardware;							//  是否硬件相关
				 TCHAR										commonErr[255  +  1];					//  常见错误
				 unsigned  int								securityLevel;							//  安全等级
				 unsigned  char								ucbSpy;									//  是否间谍软件
				 unsigned  char								ucbAdvertisement;						//  是否广告软件
				 unsigned  char								ucbVirus;								//  是否病毒
				 unsigned  char								ucbBackDoor;							//  是否后门
				 //
				 //						"iProp0						int,"
				 //						"iProp1						int,"
				 //						"iProp2						int,"
				 //						"iProp3						int,"
				 //						"iProp4						int,"
				 //						"iProp5						int,"
				 //						"iProp6						int,"
				 //						"iProp7						int,"
				 //						"iProp8						int,"
				 //						"iProp9						int,"
				 //						"propStr0					varchar(255),"
				 //						"propStr1					varchar(255),"
				 //						"propStr2					varchar(255),"
				 //						"propStr3					varchar(255),"
				 //						"propStr4					varchar(255),"
				 //						"propStr5					varchar(255),"
				 //						"propStr6					varchar(255),"
				 //						"propStr7					varchar(255),"
				 //						"propStr8					varchar(255),"
				 //						"propStr9					varchar(255),"
				 //						//
				 TCHAR										provider[255  +  1];				//  提交者
				 TCHAR										providerAddr[255  +  1];			//  提交者联系方式
				 TCHAR										providerTime[255  +  1];			//  提交时间
				 //
				 char										auditTime[14  +  1];				//  审核时间
				 char										firstTime[14  +  1];				//
				 char										lastTime[14  +  1];					
				 int										iStatus;
}		 QY_PCREGISTRYKNOWLEDGE_RCD;


typedef  struct  __ipKnowledgeRcd_t							{
				 int										id;
				 unsigned  int								uiType;
				 char										startIp[15  +  1];
				 char										endIp[15  +  1];
				 TCHAR										wLocation[255  +  1];
				 int										iWeight;			 
				 //
				 char										startTime[14  +  1];
				 char										endTime[14  +  1];
				 char										tLastModifiedTime[14  +  1];
				 //
				 int										iStatus;
				 
}		 IP_KNOWLEDGE_RCD;

/////////////




typedef  struct  __qyPcProcessRule_t					{					//  2005/10/10
				 DWORD									dwPid;
}		 QY_PC_PROCESSRULE;

#define		CONST_maxPcProcessRules						5
typedef  struct  __qyPcProcessRules_t					{
				 unsigned  int							cnt;
				 QY_PC_PROCESSRULE						mems[CONST_maxPcProcessRules];
}		 QY_PC_PROCESSRULES;



//////  2006/09/10
#define		CONST_myMAXLEN_PHYSADDR							8				//  引自iprtrmib.h
	
typedef  struct  __qyPcNetFlowProp_t							{	//  2006/09/10
				 DWORD										dwIndex;		//  很多成员摘自MIB_IFROW
				 DWORD										dwType;			
				 DWORD										dwSpeed;		
				 DWORD										dwInSpeed;		//  入流量, 自定义
				 DWORD										dwOutSpeed;		//  出流量, 自定义
    			 DWORD										dwPhysAddrLen;
    			 BYTE										bPhysAddr[CONST_myMAXLEN_PHYSADDR];
				 //									
    			 DWORD										dwMtu;
    			 DWORD										dwAdminStatus;
    			 DWORD										dwOperStatus;
    			 DWORD										dwLastChange;
    			 DWORD										dwInOctets;
    			 DWORD										dwInUcastPkts;
    			 DWORD										dwInNUcastPkts;
    			 DWORD										dwInDiscards;
    			 DWORD										dwInErrors;
    			 DWORD										dwInUnknownProtos;
    			 DWORD										dwOutOctets;
    			 DWORD										dwOutUcastPkts;
    			 DWORD										dwOutNUcastPkts;
    			 DWORD										dwOutDiscards;
    			 DWORD										dwOutErrors;
    			 DWORD										dwOutQLen;
				 //
				 unsigned  char								ucWarnCnt;
				 unsigned  char								iireserved[3];
				 				 
}		 QY_PCNETFLOW_PROP;

//  #define		CONST_maxDetectNetFlows							8		//  2006/09/10
#define		CONST_maxDetectNetFlows							28		//  2007/02/19
typedef  struct  __qyPcNetFlows_t							{
				 MACRO_qyPcCommHead
				 QY_PCNETFLOW_PROP							mems[CONST_maxDetectNetFlows];
}		 QY_PC_NETFLOWS;


/////////  2007/02/14
typedef  struct  __qyPcNetShareProp_t						{
				 WCHAR										shi502_netname[64];
				 DWORD										shi502_type;
				 WCHAR										shi502_path[128];
}		 QY_PCNETSHARE_PROP;

#define		CONST_maxSntNetShares							16
typedef  struct  __qyPcNetShares_t							{
				 MACRO_qyPcCommHead
				 QY_PCNETSHARE_PROP							mems[CONST_maxSntNetShares];
}		 QY_PC_NETSHARES;

/////////  2006/07/11

/*
typedef  struct  __qyPcRegistry_t						{
				 int									iRootKey;				//  HKEY_CLASSES_ROOT等预定值，或者对应的自定义的值
				 char									subkey[512  +  1];
				 char									cfgName[255  +  1];
				 int									iValType;
				 unsigned  int							uiValSize;				//  值的长度
				 char									cfgVal[255  +  1];
}		 QY_PC_REGISTRY;

#define		CONST_maxPcRegistrys						20
typedef  struct  __qyPcRegistrys_t						{
				 unsigned  int							cnt;
				 QY_PC_REGISTRY							mems[CONST_maxPcRegistrys];
}		 QY_PC_REGISTRYS;
*/



typedef  struct  __qyPcRegistryVal_t					{
				 int									iRuleId;						//  用来标识配置项的数据库记录
				 unsigned  char							ucFlg;							//  用来标识其状态
				 unsigned  char							ucbKey;							//  是否是key, 不是的话就是value
				 unsigned  char							ucbERROR_MORE_DATA;				//  是否键名或键值太长
				 unsigned  int							uiCfgNameLen;					//  配置名长度
				 WCHAR									wCfgName[128  +  1];
				 int									iValType;
				 unsigned  int							uiValLenInBytes;				//  值的长度
				 union									{
					 int								iCfgVal;
				 	 WCHAR								wCfgVal[128  +  1];
				 }										u;
}		 QY_PC_REGISTRYVAL;


#define		CONST_maxPcRegistryVals						24
typedef  struct  __qyPcRegistryVals_t					{
				 MACRO_qyPcCommHead
				 char									szSidKey[256  +  1];				//  用户子键名,2006/09/29
				 WCHAR									wUsrName[128  +  1];				//  登陆名，对HKEY_USERS下的键值是需要
				 QY_PC_REGISTRYVAL						mems[CONST_maxPcRegistryVals];
}		 QY_PC_REGISTRYVALS;

typedef  struct  __qnmCmdParam_queryCfg_t				{								//  
				 unsigned  int							uiChangesId_fileMon;
				 unsigned  int							uiQueryTimes;					//  2006/07/15, 查询次数
}		 QNM_CMDPARAM_queryCfg;

typedef  struct  __qyPcQueryCfgs_t						{								//  2006/08/06
				 MACRO_qyPcCommHead
				 QNM_CMDPARAM_queryCfg					mems[1];
}		 QY_PC_QUERYCFGS;


typedef  struct  __qyPcRegistryRuleRcd_t				{
				 int									id;
				 unsigned  int							uiType;
				 char									mac0[CONST_qyMacLen  +  1];
				 unsigned  int							uiLangId;
				 int									iPlatformId;					//  操作系统类型
				 char									winDir[255  +  1];				//  Windows目录
				 //
				 int									iRootKey;						//  HKEY_CLASSES_ROOT等预定值，或者对应的自定义的值
				 TCHAR									usrName[255  +  1];
				 TCHAR									subKey[255  +  1];
				 unsigned  char							ucbKey;
				 unsigned  int							uiCfgNameLen;
				 TCHAR									cfgName[255  +  1];
				 int									iValType;
				 unsigned  int							uiValLenInBytes;				//  值的长度
				 int									iCfgVal;				
				 TCHAR									cfgVal[255  +  1];
				 //				
				 unsigned  int							nIntervals;						//  每N个周期发一次
				 //
				 unsigned  char							ucbUnsupport98;
				 unsigned  char							ucbUnsupportMe;
				 unsigned  char							ucbUnsupportNt;
				 unsigned  char							ucbUnsupport2k;
				 unsigned  char							ucbUnsupportXp;
				 unsigned  char							ucbUnsupport2003;
				 unsigned  char							ucbUnsupportVista;
				 //
				 unsigned  char							ucbNotLogAdd;
				 unsigned  char							ucbNotLogDel;
				 unsigned  char							ucbNotLogModify;
				 //
				 char									firstTime[CONST_qyTimeLen  +  1];
				 char									lastTime[CONST_qyTimeLen  +  1];
				 int									iStatus;
}		QY_PCREGISTRYRULE_RCD;


typedef  struct  __qyPcRegistryValRcd_t					{
				 int									id;
				 unsigned  int							uiType;							//  区分代理服务器和网卡配置等类型
																						//
				 char									mac0[CONST_qyMacLen  +  1];		//
				 unsigned  int							uiLangId;						//  2005/01/24, 语种
				 int									iPlatformId;					//  操作系统类型
				 char									winDir[255  +  1];				//  Windows目录
																						//
																						//
				 int									iRuleId;
				 char									szSidKey[255  +  1];			//  2006/09/29
				 TCHAR									tUsrName[255  +  1];			//  varchar(255),"
 				 unsigned  char							ucbKey;
				 unsigned  char							ucbERROR_MORE_DATA;
				 unsigned  int							uiCfgNameLen;
				 TCHAR									tCfgName[255  +  1];			//  varchar(255),"
				 int									iValType;
				 unsigned  int							uiValLenInBytes;				//  值的长度
				 int									iCfgVal;						
				 TCHAR									tCfgVal[255  +  1];				//  varchar(255),"
																						//
				 char									firstTime[14  +  1];
				 char									lastTime[14  +  1];
				 int									iSessionId;
				 int									iStatus;
																						//
																						//
}		 QY_PCREGISTRYVAL_RCD;
										


//  2005/08/31
typedef  struct  __qyEventLogProp_t						{
			     DWORD									dwRecordNumber;  // Absolute record number
				 char									timeGeneratedBuf[14  +  1]; // Seconds since 1-1-1970
				 WORD									wEventType;
				 char									sourceName[32  +  1];
				 WORD									wEventCategory;
				 DWORD									dwEventID;
				 char									accountName[32  +  1];
	 			 char									computerName[32  +  1];
	 			 char									eventLogDesc[255  +  1];
}		 QY_EVENTLOG_PROP;

#define		CONST_maxEventLogs							32
typedef	 struct  __qyPcEventLogs_t						{
				 MACRO_qyPcCommHead
				 //  unsigned  int						cnt;
				 QY_EVENTLOG_PROP						mems[CONST_maxEventLogs];
}		 QY_PC_EVENTLOGS;


//  2005/09/04
typedef  struct  __qyPcUsrProp_t							{
				 char									usrName[128  +  1];
				 unsigned  char							ucbDisabled;
}		 QY_PCUSR_PROP;

#define		CONST_maxUsrInfos							32
typedef  struct  __qyPcUsrInfos_t						{
				 MACRO_qyPcCommHead
				 //
				 QY_PCUSR_PROP							mems[CONST_maxUsrInfos];
}		 QY_PC_USRINFOS;


//  摘自iphlpapi.h,  2005/09/17
//
typedef  struct  __myMIB_TCPROW
{
	DWORD       dwState;
	DWORD       dwLocalAddr;
	DWORD       dwLocalPort;
	DWORD       dwRemoteAddr;
	DWORD       dwRemotePort;
} myMIB_TCPROW;

typedef  struct __myMIB_UDPROW
{
	DWORD       dwLocalAddr;
	DWORD       dwLocalPort;
} myMIB_UDPROW;


#define		CONST_maxTcpRows							100
//  #define		CONST_maxTcpRows							3
typedef  struct  __qyPcTcpTable_t						{
				 MACRO_qyPcCommHead
				 //
				 myMIB_TCPROW							mems[CONST_maxTcpRows];
}		 QY_PC_TCPTABLE;

typedef  struct  __qyPcUdpTable_t						{
				 MACRO_qyPcCommHead
				 //
				 myMIB_UDPROW							mems[CONST_maxTcpRows];
}		 QY_PC_UDPTABLE;


typedef  struct  __qyPcPrinterProp						{
				 char									name[255  +  1];
}		 QY_PC_PRINTERPROP;

#define		CONST_maxPrinters							96	//  8	//  2005/11/01, 因为金杜的打印机非常多，故将这个打印机的数字调大
typedef  struct	 __qyPcPrinters_t						{
				 MACRO_qyPcCommHead
				 //
				 QY_PC_PRINTERPROP						mems[CONST_maxPrinters];	//  32, 将这个数字和客户端统一起来，2005/11/01
}		 QY_PC_PRINTERS;

#define		MACRO_makePcCommHead(  uiTypeParam,  pQwm,  pcCommU  )	pcCommU.head.uiType  =  uiTypeParam;  pcCommU.head.iPlatformId  =  pQwm->env.iPlatformId;  pcCommU.head.uiLangId	=  pQwm->env.usLangId;  {  TCHAR	winDir[MAX_PATH];  GetWindowsDirectory(  winDir,  mycountof(  winDir  )  );  myTChar2Utf8(  winDir,  pcCommU.head.winDir,  mycountof(  pcCommU.head.winDir  )  );  }
//
typedef  union  __qyPcCommU_t							{
				unsigned  int							uiType;
				struct									{
					MACRO_qyPcCommHead
				}										head;
				char									buf[4096];
				QY_PC_PROCESSES0326						processesInfo0326;
				QY_PC_PROCESSES							processesInfo;			//  2006/09/06, 增加新的进程信息				
				QY_PC_EVENTLOGS							eventLogsInfo;
				QY_PC_USRINFOS							usrInfos;
				QY_PC_TCPTABLE							tcpTable;
				QY_PC_UDPTABLE							udpTable;
				QY_PC_PRINTERS							printers;
				QY_PC_PROCESSMODULES					processModulesInfo;
				QY_PC_REGISTRYVALS						registryVals;			//  2006/07/16
				QY_PC_QUERYCFGS							queryCfgs;				//  2006/08/06
				QY_PC_NETFLOWS							netFlows;
				QY_PC_NETSHARES							netShares;				//  2007/02/14


}		 QY_PC_COMMU;															//  注意：这里已经严重超标，qy_pc_commu的结构大小不应超过能加密的长度，共CONST_maxReqDataLen（16384）个字节	//  2006/08/14




										
int  qyhtonQyProcessProp0326(  QY_PROCESS_PROP0326  *  p  );
int  qyntohQyProcessProp0326(  QY_PROCESS_PROP0326  *  p  );
int  qyhtonQyProcessProp(  QY_PROCESS_PROP  *  p  );
int  qyntohQyProcessProp(  QY_PROCESS_PROP  *  p  );


//  int  qyhtonQyPcCommU(  QY_PC_COMMU  *  pPcCommU  );
//  int  qyntohQyPcCommU(  QY_PC_COMMU  *  pPcCommU  );	//  2006/09/06改成下面的转换函数
int  qyhtonQyPcCommU(  long  lhQwmVer,  QY_PC_COMMU  *  pPcCommU  );
int  qyntohQyPcCommU(  long  lhQwmVer,  QY_PC_COMMU  *  pPcCommU  );



//


extern  QY_DMITEM	CONST_iRootKeyTable[];
extern  QY_DMITEM	CONST_iRootKeyTable_abbr[];
extern  QY_DMITEM	CONST_regTypeTable[];
extern  QY_DMITEM	CONST_pcEventLogTypeTable[];
extern  QY_DMITEM	CONST_tcpStateTable[];
//	extern  QY_DMITEM	CONST_pcProcessRuleTypeTable[];
extern  QY_DMITEM	CONST_netShareTypeTable[];

int  printEventLogProp(  QY_EVENTLOG_PROP  *  pEventLog  );

#ifdef  __cplusplus
  }
#endif



#endif  //  }

