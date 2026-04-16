

#ifndef  __QNMASSETSCOMMPROC_H__
#define  __QNMASSETSCOMMPROC_H__		//  {


#ifdef  __cplusplus
 extern  "C"  {
#endif

	 //  以下定义在出厂后不能再修改
#define		CONST_assetType_null								0
#define		CONST_assetType_cpu									1		//  芯片
#define		CONST_assetType_mem									2		//  内存
#define		CONST_assetType_bios								3		//  主板
#define		CONST_assetType_floppy								4		//  软驱
#define		CONST_assetType_monitor								5		//  监视器
#define		CONST_assetType_cpu1								6		//  用注册表的数据读的cpu格式, 2005/08/07

//
#define		CONST_assetType_ideHardDisk							10		//  IDE硬盘
#define		CONST_assetType_scsiHardDisk						11		//  SCSI硬盘
#define		CONST_assetType_ideCdrom							12		//  CD-ROM
#define		CONST_assetType_usbDisk								13		//  USB的移动硬盘
//
#define		CONST_assetType_display								20		//  显卡
#define		CONST_assetType_networkCard							21		//  网卡
#define		CONST_assetType_soundCard							22		//  声卡

//  
#define		CONST_assetType_modem								30		//	Modem
//
#define		CONST_assetType_software							60		//  软件


extern  QY_DMITEM	CONST_assetTypeTable[];
extern  QY_DMITEM	CONST_classGUIDTable[];

#define		CONST_assetLocLen									48


//  资产管理的组件信息, 2004/07/26
typedef  struct  __qwmComponentInfo_t							{
				 unsigned  int									uiPktSize;						//  本数据包的长度
				 unsigned  int									uiType;							//  组件类型
				 char											makeTime[14  +  1];				//  出厂时间
				 char											installTime[14  +  1];			//  安装时间
				 union											{
					 struct  __cpu_t							{
							 int								iManufacturer;					//  iParam0
							 int								iType;							//  iParam1
							 int								iFamily;						//  iParam2
							 int								iModel;							//  iParam3
							 int								iRevision;						//  iParam4
							 int								iCache;							//  iParam5
							 int								iExtendedFamily;				//  iParam6
							 int								iExtendedModel;					//  iParam7
							 unsigned  char						ucbHasMMX;						//  iParam8
							 unsigned  char						ucbSupportsMP;					//  iParam9
							 int								iFrequency;						//  iProp0
							 //  char								serialNumber[29  +  1];			//  idStr
							 unsigned  int						uiBrandId;						//  2005/01/16加入
					 }											cpu;
					 struct  __cpu1_t							{
							 char								processorName[64  +  1];
							 unsigned  int						uimHz;
							 char								vendor[32  +  1];
							 unsigned  char						ucSeqNo;
					 }											cpu1;
					 struct  __mem_t							{
							 unsigned  int						uiTotalPhys;
					 }											mem;
					 struct  __bios_t							{
						     char								identifier[32  +  1];
							 char								systemBiosDate[14  +  1];
							 char								systemBiosVer[64  +  1];
					 }											bios;
					 struct  __disk_t							{
						     //  unsigned  int						uiBusType;				//  ATA
							 //  unsigned  int						uiMediaType;			//  Fixed
							 //  char								vendor[32];
							 char								modelNo[48  +  1];			//  QUANTUM FIREBALLlct20 20
							 char								firmwareRevision[16  +  1];	//  APL.0900
							 char								serialNo[16  +  1];			//  552111334574
							 //  unsigned  int						uiCylinders;			//  2482
							 //  unsigned  int						uiTracksPerCylinder;		//  255
							 //  unsigned  int						uiSectorsPerTrack;			//  63
							 //  unsigned  int						uiBytesPerSector;			//  512
							 //  unsigned  int						uiDiskSizeInUnit;			//  20415144960 Bytes (19469 MB)
							 //  unsigned  int						uiDiskSizeUnit;				//  uiDiskSizeInUint的单位
							 char								locationInformation[CONST_assetLocLen  +  1];
 							 char								vendor[20];
							 char								driverDesc[64];
							 char								driverDate[14];
							 char								driverVersion[16];
					 }											disk;
					 struct  __display_t						{
							 char								vendor[20];
							 char								driverDesc[64];
							 char								driverDate[14];
							 char								driverVersion[16];
							 char								locationInformation[CONST_assetLocLen  +  1];
					 }											display;
					 struct  __networkCard_t					{
						     char								name[16];
							 char								networkaddress[12 + 1];
							 char								vendor[20];
							 char								driverDesc[64];
							 char								driverDate[14];
							 char								driverVersion[16];
 							 char								locationInformation[CONST_assetLocLen  +  1];
					 }											net;
					 struct  __monitor_t						{
							 char								driverDesc[64];
							 char								driverDate[14];
							 char								driverVersion[16];
 							 char								vendor[20];		//  "ProviderName"="Microsoft"
							 char								locationInformation[CONST_assetLocLen  +  1];
					 }											monitor;
					 struct  __floppy_t							{			      
							 char								driverDesc[64];
							 char								driverDate[14];
							 char								driverVersion[16];
 							 char								vendor[20];		//  "ProviderName"="Microsoft"
					 }											floppy;

							
					 struct   __volume_t						{
							  char								reserved[1];
					 }											volume;
					 

					 /////////
					 struct  __software_t						{
							 char								displayName[255  +  1];			
					 }											software;
				 }												u;
}		 QWM_COMPONENT_INFO;


//  资产信息, 2004/07/26
typedef  struct  __qwmAssetsInfo0303_t								{
				 int											iPlatformId;
				 char											winDir[255  +  1];				//  系统目录
				 char											usrName[64  +  1];				//  最近检查的登录用户名
				 unsigned  int									cnt;
				 QWM_COMPONENT_INFO								components[128];

				 //  以下成员不会被发送，仅用于处理													
				 unsigned  int									uiCodePage;						//  2005/01/14
				 unsigned  char									ucbHeadProced;					//  2005/01/15
				 unsigned  char									ucbNotConvrtPlatformId;			//  2005/01/15, 由于山西晋中烟草的版本中忘了转换，故设此标志，以实现兼容

}		 QWM_ASSETS_INFO0303;

#define		CONST_maxAssetComponents							256								//  128, 2006/05/05增大了此值

typedef  struct  __qwmAssetsInfo_t								{
				 unsigned  int									uiLangId;								//  2005/01/24
				 int											iPlatformId;
				 char											winDir[255  +  1];						//  系统目录
				 char											usrName[64  +  1];						//  最近检查的登录用户名
				 unsigned  int									cnt;
				 QWM_COMPONENT_INFO								components[CONST_maxAssetComponents];

				 //  以下成员不会被发送，仅用于处理													
				 unsigned  int									uiCodePages[CONST_maxAssetComponents];	//  2006/05/05, 用来指明对应的component的内容是不是utf8的
				 unsigned  int									uiCodePage;								//  2005/01/14
				 unsigned  char									ucbHeadProced;							//  2005/01/15
				 unsigned  char									ucbNotConvrtPlatformId;					//  2005/01/15, 由于山西晋中烟草的版本中忘了转换，故设此标志，以实现兼容

}		 QWM_ASSETS_INFO;


typedef  struct  __qyPcAssetRcd_t								{
				 int											id;
				 char											mac0[CONST_qyMacLen  +  1];
				 unsigned  int									uiLangId;							//  2005/01/24
				 int											iPlatformId;
				 char											winDir[255  +  1];					//  系统目录
				 char											startTime[CONST_qyTimeLen  +  1];
				 char											endTime[CONST_qyTimeLen  +  1];
				 char											lastUsrName[64  +  1];				//  最近检查的登录用户名

				 unsigned  int									uiType;								//  组件类型
				 TCHAR											name[64  +  1];						//  名称
				 TCHAR											maker[48  +  1];					//  制造商
				 char											makeTime[14  +  1];					//  出厂时间
				 TCHAR											idStr[64  +  1];					//  序号
				 char											installTime[14  +  1];				//  安装时间
				 int											iParams[20];						//  标志性整数参数
				 TCHAR											paramStrs[10][128  +  1];			//  标志性字符串参数
				 TCHAR											locationInfo[255  +  1];
				 int											iProps[10];							//  性能参数
				 TCHAR											propStrs[10][128  +  1];
				 TCHAR											deses[5][64  +  1];					
				 TCHAR											comment0[255  +  1];				//  备注
}		 QY_PCASSET_RCD;



#define		CONST_qyRootKey_softwareInstalled					"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"  
#define		CONST_qyRootKey_softwareInstalled_wow64				"SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall"  
#define		CONST_regValName_displayName						"DisplayName"  
#define		CONST_regValName_systemComponent					"SystemComponent"  
#define		CONST_regValName_uninstallString					"UninstallString"  


QWM_COMPONENT_INFO  *  nextComponent(  QWM_ASSETS_INFO  *  pAssetsInfo  );
int  submitComponent(  QWM_ASSETS_INFO  *  pAssetsInfo,  unsigned  int  uiCodePage  );





#define		CONST_UnknownManufacturer		0
#define		CONST_AMD						1
#define		CONST_Intel						2
#define		CONST_NSC						3
#define		CONST_UMC						4
#define		CONST_Cyrix						5
#define		CONST_NexGen					6
#define		CONST_IDT						7
#define		CONST_Rise						8
#define		CONST_Transmeta					9

extern  QY_DMITEM  CONST_cpuManufacturerTable[];


BOOL  bGetCpuName(  int  ChipManufacturer,  int  Type,  int  Family,  int  Model,  int  iRevision,  int  iCache,  int  ExtendedFamily,  BOOL  HasMMX,  BOOL  SupportsMP,  unsigned  int  uiBrandId,  char  *  processorName,  unsigned  int  size  );
int  qyntohQwmAssetsInfo(  QWM_ASSETS_INFO  *  pQwmAssetInfo  );
int  qyhtonQwmAssetsInfo(  QWM_ASSETS_INFO  *  pQwmAssetInfo  );

#ifdef  __DEBUG__
  int  printQwmAssetsInfo(  QWM_ASSETS_INFO  *  pAssetInfo  );
  int  printComponentInfo(  int  i,  QWM_COMPONENT_INFO  *  pComponent  );
#endif


#ifdef  __cplusplus
 }
#endif


#endif	//  }

