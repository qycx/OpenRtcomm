
#ifndef  __ipcProc_open_h__
#define  __ipcProc_open_h__		//  {

//
#include	"qisOnvifCommProc_open.h"


//
#define		CONST_iNvrType_null						0
//
#define		CONST_iNvrType_dh						1	
#define		CONST_iNvrType_dhListIp					2
#define		CONST_iNvrType_dhDeviceControl			3
#define		CONST_iNvrType_dhPtz					4

#define		CONST_iNvrType_d4k						11	
#define		CONST_iNvrType_d4kListIp			    12
#define		CONST_iNvrType_d4kDeviceControl			13
#define		CONST_iNvrType_d4kPtz					14

#define		CONST_iNvrType_hik						21	
#define		CONST_iNvrType_hikListIp			    22
#define		CONST_iNvrType_hikDeviceControl			33
#define		CONST_iNvrType_hikPtz					24
//
#define		CONST_iNvrType_hk3ddw					25




//
typedef  struct  __ipcProcTool_t					{

				 //	
				 HANDLE								hProcess_ipcProc;
				 DWORD								dwProcessId_ipcProc;

				 //
				 int								tn;

}		 IpcProcTool;


//
#define		CONST_intervalInMs_nvrInfo			60000

//
#define		CONST_intervalInMs_ping				10000		//  定期发送包以表明通道是活跃的
#define		CONST_toInMs_pipe_read				15000		//  每次读的超时

//
#define		CONST_toInMs_ipcProc				35000		//  超过这个时间就认为通道已经彻底放弃


//
typedef  struct  __onvifMsg_ping_t {
				 M_onvifMsgCommon_mems

				 int	tn;
}		 OnvifMsg_ping;


//
typedef  struct  __ipcInfo_t {
				 int	iChannel;		//  通道
				 WCHAR	name[128];
				 char  ip[15 + 1];
}		 IpcInfo;


enum DeviceType {
	DeviceType_UNKNOWN = 0,
	DeviceType_IPC = 1,
	DeviceType_NVR = 2,
	DeviceType_DVR = 3,
	DeviceType_IPZM = 4,
};


typedef  struct  __nvrInfo_t		{
				 //
				 unsigned  __int64	ui64Id;
				 //
				 unsigned  short	usCnt;
				 IpcInfo			mems[128];		//  最多一个nvr管128个
				 int                deviceType;

}		 NvrInfo;



//
//
typedef  struct  __onvifMsg_nvrInfo_t {
				 M_onvifMsgCommon_mems

				 //
				 NvrInfo	nvrInfo;
	


}		 OnvifMsg_nvrInfo;








//
int  createTool_ipcProc(LPCTSTR  installDir, int iNvrType, char* ip, TCHAR* tUsr, char* passwd, int tn,  LPCTSTR  who_showInfo, LPCTSTR  logFile, IpcProcTool* pToolCa, int log = 0, int ipcType = 0);
int  closeTool_ipcProc(IpcProcTool* pToolCa);



//
#endif  //  }


