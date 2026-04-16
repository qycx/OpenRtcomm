
#ifndef  __ipcProc_h__
#define  __ipcProc_h__	//  {


#include	"ipcProcCfg.h"
#include	"ipcProc_open.h"



//
typedef  struct  __ipcProc_t					{

				 //
				 QIS_pipe			*			pQisPipe;

				 //
				 IpcProcTool					tool;				 		 

				 //
				 DWORD							dwLastTickCnt_ping;

				 //
				 struct {
					 NvrInfo					nvrInfo;
					 DWORD						dwLastTickCnt_nvrInfoGot;
					 int						cnt_wait;  //等待nvr信息拿到
					 int                        deviceType;
				 }								dev;		//  终端上关联的解码器


				 //
				 struct {
					 QY_MESSENGER_ID			idInfo;		//  关联解码器的终端idInfo
					 NvrInfo					nvrInfo;	//  从mcu上获取的该终端的nvrInfo
					 //
					 int						iChannel;	//  独占的通道号

					 int						nID;		// nResourceID

					 unsigned  char				ucMouseStatus; //ucMouseStatus

				 }								op;			//  要操作的解码器


		 //
}		 IpcProc;



//
bool bGetIpcProcInitCfg(TCHAR* cfgFileName, IpcProcInitCfg* pCfg);
bool bGetShareProcInitCfg(TCHAR* cfgFileName, ShareProcInitCfg* pCfg);




int ipcProc_exit();

//
int mainWnd_chkIpcProc(int loopCtrl);

//
int saveSmIpicInitCfg(IpcProcInitCfg* pCfg, TCHAR* cfgFileName);
int saveSmShareInitCfg(ShareProcInitCfg* pCfg, TCHAR* cfgFileName);

//
#endif  //  }


