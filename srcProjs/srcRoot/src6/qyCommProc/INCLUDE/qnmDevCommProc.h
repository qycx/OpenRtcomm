
#ifndef  __QNMDEVCOMMPROC_H__
#define  __QNMDEVCOMMPROC_H__	/*  {  */

#define		CONST_MAX_DEVICE_ID_LEN			200

typedef  struct  __qnmDevInfo_t				{
				 HANDLE						hDevs;
				 void				*		pDevInfo;
				 unsigned  int				index;
				 char						devIdStr[CONST_MAX_DEVICE_ID_LEN];
				 char						devDesc[512];
				 char						devicePath[1024];
				 unsigned  char				ucbUsb;
				 
				 unsigned  long				ulStatus;	//  2010/08/18
				 unsigned  long				ulProblemNumber;

				 char						buf[128];	//  2005/10/09, 将buf大小从32改为128

}		 QNM_DEV_INFO;


typedef  struct  __qwmDevInfo_t				{
				 char						devIdStr[CONST_MAX_DEVICE_ID_LEN];
				 char						devDesc[64];
				 unsigned  char				ucbUsb;						//  USB
				 //  unsigned  char				ucbLogged;				//  
				 DWORD						dwProcedLoopCtrl;			//  2005/01/06
				 unsigned  char				ucbDisabled;				//  2011/08/26
				 GUID						guid_class;					//  2011/08/28
				 unsigned  short			usQwmDevType;				//  2011/09/21
}		 QWM_DEV_INFO;

typedef  struct  __controlDevParam_t		{							//  2007/02/19
				 DWORD						count;
				 DWORD						dwControl;					//  2005/05/26
				 BOOL						bRebootForDev;				//  该参数为设备API的响应参数，是微软API的重起建议
}		CONTROL_DEV_PARAM;						
				 
typedef  struct  __procDevStruct_t			{

				 DWORD						dwProcedLoopCtrl;			//  2005/01/06加,处理过的序号

				 QWM_DEV_INFO				disks[5];
				 unsigned  char				ucMaxDisks;					//  最大磁盘数
				 unsigned  char				ucbRemoved;					//  是否删除过USB


				 unsigned  char				ucbNeedReboot;				//  该参数为修改网络配置的控制参数，看是否需要重起，我们以此参数为准，不要和下面的参数混淆
				 unsigned  char				ucbNeedRecover;				//  当网卡配置有误，与管理端无法连通时，需要恢复原来的设置

				 CONTROL_DEV_PARAM			controlParam;

				 //  2011/08/25
				 struct						{
					 QWM_DEV_INFO			devs[20];
					 unsigned  char			ucMaxDevs;
				 }							wpd;

}		 PROC_DEV_STRUCT;



//  int  tmpHandler_sndQwmAdapterProp(  void  *  pCommonParam1,  void  *  p1,  void  *  pAdapterInfoParam  );
int  tmpHandler_sndPcNetworkProp(  void  *  pCommonParam1,  void  *  p1,  void  *  pPcNetworkInfoU  );




#endif  /*  }  */

