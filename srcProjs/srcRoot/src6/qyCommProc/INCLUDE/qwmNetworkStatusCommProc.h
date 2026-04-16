
#ifndef  __QWMNETWORKSTATUSCOMMPROC_H__
#define  __QWMNETWORKSTATUSCOMMPROC_H__	 //  {


#define		CONST_regValName_ywPcNetworkPropType		"yw_pcNetworkPropType"
#define		CONST_regValName_ywDevIdStr					"yw_devIdStr"
#define		CONST_regValName_ywDevIndex					"yw_devIndex"
#define		CONST_regValName_ywMac						"yw_mac"
#define		CONST_regValName_ywIp						"yw_ip"
#define		CONST_regValName_ywIpMask					"yw_ipMask"
#define		CONST_regValName_ywGateway					"yw_gateway"
#define		CONST_regValName_ywUcbDhcpEnabled			"yw_ucbDhcpEnabled"
#define		CONST_regValName_ywDns						"yw_dns"		
//
#define		CONST_regValName_ywNeedRecover				"yw_needRecover"		


#define		MACRO_pcNetworkHead			unsigned  int  uiType;  unsigned  int  uiSize;  unsigned  char  ucFlg;  char  reserved[7];	int  iPlatformId;  unsigned  int  uiLangId;		
				 

#define		MACRO_pcAdapterProp														\
				MACRO_pcNetworkHead													\
				char						devIdStr[255  +  1];					\
				 int						devIndex;								\
				 char						devDesc[255  +  1];						\
																					\
				 char						connectionName[32  +  1];				\
				 unsigned  int				uiAdapterType;							\
																					\
				 char						mac[CONST_qyMacLen  +  1];				\
				 char						ipBuf[64  +  1];						\
				 char						ipMaskBuf[64  +  1];					\
				 char						gatewayBuf[64  +  1];					\
				 char						gatewayMetricBuf[32  +  1];				\
																					\
				 unsigned  char				ucbDhcpEnabled;							\
				 char						dhcpServerIp[CONST_qyMaxIpLen  +  1];	\
				 long						lLeaseObtained;							\
																					\
				 unsigned  char				ucbHaveWins;									\
				 char						primaryWinsServerIp[CONST_qyMaxIpLen  +  1];	\
				 char						secondaryWinsServerIp[CONST_qyMaxIpLen  +  1];	\
																							\
				 unsigned  char				ucbAutoDns;										\
				 char						dnsBuf[64  +  1];								\
				 char						curUsrName[64  +  1];							\
				 char						proxyBuf[128  +  1];							\

				 




typedef  struct  __qyPcAdapterProp_t					{
				 MACRO_pcAdapterProp
}		 QY_PCADAPTER_PROP;


typedef  struct  __qyPcAdapterInfo_t					{
				 MACRO_pcAdapterProp
				 char									adapterName[255  +  1];				 
				 //  char								pnpInstanceIDBuf[255  +  1];				 
				 unsigned  int							uiAdapterIndex;					//  2007/02/19
				 DWORD									mediaSubType;					//  2010/08/18
}		 QY_PCADAPTER_INFO;




typedef  struct  __qwmUsrInfo032816_t					{
				 MACRO_pcNetworkHead

				 char									szSubKey[256  +  1];					//  用户子键名
				 char									name[64  +  1];							//  当前登录用户名，2003/09/12添加
				 char									proxyServer[256  +  1];					//  IE的代理设置，2003/09/12添加

				 //  以下为修改配置代理服务器而加, 2005/06/17
				 unsigned  char							ucbEnableAutodial;
				 unsigned  char							ucbNoNetAutodial;
				 unsigned  char							ucbAutoDetectSettings;					//  是否自动检测设置
				 unsigned  char							reserved0[3];							//
				 unsigned  char							ucbProxyEnable;							//		2005/06/16
				 char									proxyOverride[32];						//		设置为<local>，则表明对本地地址不使用代理服务器

}		 QWM_USR_INFO032816;


typedef  struct  __qwmUsrInfo_t							{
				 MACRO_pcNetworkHead

				 char									szSubKey[256  +  1];					//  用户子键名
				 char									name[64  +  1];							//  当前登录用户名，2003/09/12添加
				 char									proxyServer[256  +  1];					//  IE的代理设置，2003/09/12添加

				 //  以下为修改配置代理服务器而加, 2005/06/17
				 unsigned  char							ucbEnableAutodial;
				 unsigned  char							ucbNoNetAutodial;
				 unsigned  char							ucbAutoDetectSettings;					//  是否自动检测设置
				 unsigned  char							reserved0[3];							//
				 unsigned  char							ucbProxyEnable;							//		2005/06/16
				 char									proxyOverride[32];						//		设置为<local>，则表明对本地地址不使用代理服务器
				 char									autoConfigUrl[96];						//  2006/11/15, 自动配置脚本

}		 QWM_USR_INFO;

#if  0	//  2010/03/26
typedef  struct  __qwmComputerProp_t					{	//  2005/06/21
				 MACRO_pcNetworkHead
				 char									winDir[255  +  1];				//  系统目录
				 char									activeComputerName[MAX_COMPUTERNAME_LENGTH  +  1];
				 char									computerName[MAX_COMPUTERNAME_LENGTH  +  1];
				 char									hostname[128  +  1];
				 unsigned  char							ucbAutoRestartIfChanged;		//  修改计算机名后是否自动重起
}		 QWM_COMPUTER_PROP;
#endif
typedef  struct  __qwmComputerProp_t					{	//  2005/06/21
				 MACRO_pcNetworkHead
				 char									winDir[255  +  1];				//  系统目录
				 char									activeComputerName[15  +  1];
				 char									computerName[15  +  1];
				 char									hostname[128  +  1];
				 unsigned  char							ucbAutoRestartIfChanged;		//  修改计算机名后是否自动重起
}		 QWM_COMPUTER_PROP;

#define		CONST_dwRegVal_invalid								3887654321

typedef  struct  __qwmWindowsUpdatePolicyProp_t				{	//  2006/05/21
				 MACRO_pcNetworkHead

				 int										RescheduleWaitTime;
				 int										RescheduleWaitTimeEnabled;
				 int										NoAutoRebootWithLoggedOnUsers;
				 int										NoAutoUpdate;
				 int										AUOptions;
				 int										ScheduledInstallDay;
				 int										ScheduledInstallTime;
				 int										DetectionFrequency;						//  2006/05/25
				 int										DetectionFrequencyEnabled;				//  2006/05/25
				 int										UseWUServer;
				 //
				 char										WUServer[255  +  1];
				 char										WUStatusServer[255  +  1];
				 int										ElevateNonAdmins;
				 int										TargetGroupEnabled;
				 char										TargetGroup[255  +  1];
				 //
				 int										AutoUpdate_AUOptions;
				 int										AutoUpdate_ScheduledInstallDay;
				 int										AutoUpdate_ScheduledInstallTime;
				 //
				 //  unsigned  char								ucbWSusPolicyExists;				//  是否起用WSus

}		 QWM_WINDOWSUPDATEPOLICY_PROP;




#define		CONST_pcNetworkPropType_null				CONST_pcCommType_null
#define		CONST_pcNetworkPropType_adapter				CONST_pcCommType_adapter	//  1
#define		CONST_pcNetworkPropType_proxy				CONST_pcCommType_proxy		//  2
#define		CONST_pcNetworkPropType_computer			CONST_pcCommType_computer	//  3
//  网络属性不再增加pcNetworkPropType类型的，增加都放到commType那里去, 2006/05/07

//
#define		CONST_pcAdapterStatus_null					0	//
#define		CONST_pcAdapterStatus_willBeLocked			1	//  待锁定
#define		CONST_pcAdapterStatus_locked				2	//  已锁定
#define		CONST_pcAdapterStatus_cantBeLocked			3	//  无法锁定



typedef  union  __qyPcNetworkPropU						{
				unsigned  int							uiType;
				struct									{
					MACRO_pcNetworkHead
				}										head;
				QY_PCADAPTER_PROP						adapter;
				QWM_USR_INFO							usrInfo;
				QWM_COMPUTER_PROP						computer;					//  2005/06/21
				QWM_WINDOWSUPDATEPOLICY_PROP			windowsUpdatePolicy;		//  2006/05/21  
}				QY_PCNETWORK_PROPU;



typedef  union  __qyPcNetworkInfoU_t					{							//  用在客户端的内部结构
				 unsigned  int							uiType;
				 struct									{
					 MACRO_pcNetworkHead
				 }										head;
				 QY_PCADAPTER_INFO						adapter;
				 QWM_USR_INFO							usrInfo;
				 QWM_COMPUTER_PROP						computer;
				 QWM_WINDOWSUPDATEPOLICY_PROP			windowsUpdatePolicy;		//  2006/05/23
}		 QY_PCNETWORK_INFOU;


typedef  struct  __qyPcAdapterRcd_t						{

				 int									id;
				 unsigned  char							ucbRule;			//  是否规则
				 unsigned  int							uiType;
				 //
				 char									mac0[CONST_qyMacLen  +  1];
				 //
				 //
				 char									deses[3][255  +  1];

				 char									devIdStr[255  +  1];
				 int									devIndex;
				 char									devDesc[255  +  1];

				 unsigned  int							uiAdapterType;
				 char									mac[CONST_qyMacLen  +  1];
				 char									ipBuf[64  +  1];
				 char									ipMaskBuf[64  +  1];
				 char									gatewayBuf[64  +  1];
				 char									gatewayMetricBuf[32  +  1];
				 //
				 unsigned  char							ucbDhcpEnabled;
				 char									dhcpServerIp[CONST_qyMaxIpLen  +  1];
				 long									lLeaseObtained;
				 //
				 unsigned  char							ucbHaveWins;
				 char									primaryWinsServerIp[CONST_qyMaxIpLen  +  1];
				 char									secondaryWinsServerIp[CONST_qyMaxIpLen  +  1];
				 //
				 unsigned  char							ucbAutoDns;
				 char									dnsBuf[64  +  1];
				 //
				 char									curUsrName[64  +  1];	
				 char									proxyBuf[128  +  1];
				 //  
				 int									iParams[20];						//  标志性整数参数,  2005/06/18
				 char									paramStrs[10][255  +  1];			//  标志性字符串参数,  2005/06/18
				 //  int									iProps[10];							//  性能参数,  2005/06/18
				 int									iProps[20];							//  性能参数,  2006/05/21
				 //  char									propStrs[10][255  +  1];			//  性能参数,  2005/06/18
				 char									propStrs[20][255  +  1];			//  性能参数,  2006/05/21
				 //
				 char									firstTime[14  +  1];
				 char									lastTime[14  +  1];
				 int									iStatus;
				 //
				 //  char								comment0[255];

}		 QY_PCADAPTER_RCD;


typedef  QY_PCADAPTER_PROP		QY_PCADAPTER_RULE;





extern  QY_DMITEM  CONST_adapterTypeTable[];
//
extern	QY_DMITEM  CONST_qyCommTypeTable_en[];
#define		CONST_pcCommTypeTable_en		CONST_qyCommTypeTable_en
//
extern  QY_DMITEM  CONST_qyStatusTable_en[];

//  extern  QY_DMITEM  CONST_pcAdapterStatusTable[];




#ifdef  __cplusplus
  extern  "C"  {
#endif



//  int  qyhtonQyPcAdapterProp(  QY_PCADAPTER_PROP  *  p  );
//  int  qyntohQyPcAdapterProp(  QY_PCADAPTER_PROP  *  p  );

int  qyhtonQyPcNetworkPropU(  QY_PCNETWORK_PROPU  *  p  );
int  qyntohQyPcNetworkPropU(  QY_PCNETWORK_PROPU  *  p  );

int  enumPcAdaptersByIpHlp(  void  *  pReserved,  QY_ENV  *  pEnv,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  );

//  #ifdef  __DEBUG__
	
		int  printPcAdapterProp(  QY_PCADAPTER_PROP  *  p  );
		int  printQwmUsrInfo(  QWM_USR_INFO  *  pUsrInfo  );
		int  printPcNetworkProp(  QY_PCNETWORK_PROPU  *  p  );

//  #endif

int  printPcCommU(  QY_PC_COMMU  *  pPcCommU  );



int  getQwmMacsByIpHlp(  QY_ENV  *  pEnv,  QWM_MACS_INFO  *  pMacsInfo  );



#ifdef  __cplusplus
  }
#endif




#endif  //  }



