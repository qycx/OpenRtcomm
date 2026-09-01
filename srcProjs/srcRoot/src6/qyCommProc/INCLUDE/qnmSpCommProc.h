

#ifndef  __QNMSPCOMMPROC_H__
#define	 __QNMSPCOMMPROC_H__	/*  {  */

#define		CONST_maxPcSps		128


#define		CONST_spType_servicePack	1
#define		CONST_spType_sp				2


typedef  struct  __qyOsSpRcd_t			{
				 int					id;
				 int					iType;
				 int					iPlatformId;
				 TCHAR					prog[255  +  1];
				 TCHAR					servicePack[64  +  1];
				 TCHAR					spName[255  +  1];
				 unsigned  int			uiLangId;
				 TCHAR					cusName[64  +  1];
				 TCHAR					des0[255  +  1];
				 TCHAR					url[255  +  1];
				 //  char				comment0[255  +  1];
}		 QY_OSSP_RCD;




typedef  struct  __myosSpInfo_t			{
				 int					id;
			  	 BOOL					bSupported;
				 TCHAR					servicePack[64  +  1];
				 TCHAR					url[255  +  1];
}		 MY_OSSP_INFO;		


typedef  struct  __qyOsSpInfo_t			{
				 int					iType;
				 TCHAR					prog[255  +  1];
				 TCHAR					spName[255  +  1];
				 unsigned  int			uiLangId;
				 TCHAR					cusName[64  +  1];
				 TCHAR					des0[255  +  1];

				 MY_OSSP_INFO			winNt,  win2000,  winXp,  win2003;
				 
				 int					iPlatformId_servicePack;
				 MY_OSSP_INFO		*	pMyOsSpInfo_servicePack;

}		 QY_OSSP_INFO;


typedef  struct	 __spProcInfo_t			{
				 int					iDlgType;
				 int					idParam;				//  当输入参数
				 int					iPlatformIdParam;	//  当输入参数
				 char					servicePackParam[64  +  1];
				 char					spNameParam[64  +  1];
				 unsigned  int			uiLangIdParam;

				 //
				 QY_DMITEM		*		pLangIdTable;
				 //
				 QY_OSSP_INFO			osSp;
				 unsigned  char			ucbInited;
				 //
				 unsigned  char			ucbChanged;
}		 SP_PROCINFO;


//  {  //  cgi与daemon之间的通讯结构

typedef  struct  __qwmQueryPcSpReq_t	{
				 unsigned  int			uiType;								//  希望得到什么样的响应也可以靠这个变量来区分
				 unsigned  long			ulQwmIp;
				 unsigned  char			ucbCgiSelf;							//  看看是不是cgiProxy自己, 2005/02/02
}		 QWM_QUERYPCSP_REQ;

typedef  struct  __qwmQueryPcSpResp_t	{
				 unsigned  int			uiType;								//  反应类型
				 char					mac0[CONST_qyMacLen  +  1];
				 int					iPlatformId;						
				 unsigned  int			uiLangId;
				 char					winDir[255  +  1];				
				 char					pcName[32  +  1];					//  主机名
				 char					servicePack[64  +  1];				//  
				 char					lastTime[CONST_qyTimeLen  +  1];	//  最后一次检查时间
				 char					hint0[255  +  1];					//  管理人员希望告诉的话
				 char					resultBuf[64  +  1];
				 unsigned	int			uiPcSpCnt,  uiPcSpSize;				//  补丁的个数和大小
}		 QWM_QUERYPCSP_RESP;


#define		CONST_status_notInstalled				0
#define		CONST_status_installed					1

typedef  struct  __qwmPcSpInfo_t		{
				 int					iType;
				 char					name[32  +  1];
				 char					cusName[32  +  1];
				 char					des0[255  +  1];
				 char					url[255  +  1];
				 unsigned  char			ucStatus;
}		 QWM_PC_SPINFO;


#ifdef  __cplusplus
 extern  "C"  {
#endif

int  qyhtonQwmQueryPcSpReq(  QWM_QUERYPCSP_REQ  *  pReq  );
int  qyntohQwmQueryPcSpReq(  QWM_QUERYPCSP_REQ  *  pReq  );
int  qyhtonQwmQueryPcSpResp(  QWM_QUERYPCSP_RESP  *  pResp  );
int  qyntohQwmQueryPcSpResp(  QWM_QUERYPCSP_RESP  *  pResp  );
int  qyhtonQwmPcSpInfo(  QWM_PC_SPINFO  *  pSpInfo  );
int  qyntohQwmPcSpInfo(  QWM_PC_SPINFO  *  pSpInfo  );



#ifdef  __cplusplus
 }
#endif


//  }

#define		CONST_servicePackPrefix		"Service Pack"

extern  QY_DMITEM	CONST_spTypeTable[];


#endif  /*  }  */


