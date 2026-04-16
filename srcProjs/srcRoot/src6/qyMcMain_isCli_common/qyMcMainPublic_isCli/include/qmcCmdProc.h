

#ifndef  __QMCCMDPROC_H__
#define  __QMCCMDPROC_H__	//  {

#include	"ctxQmcTmpl.h"

#if  0
typedef  struct  __mcVar_qmCmd_t								{
				 MACRO_mcVar_common

				 struct											{
					 HANDLE										hMap;
					 char	*  									pBuf;
				 }												cmdsShm;
				 struct											{
					 unsigned  int								uiBufSize_qmShm;

					 HANDLE										hMap;
					 char	*									pBuf;
				 }												dataShm;
				 struct											{
					 HANDLE										hEvent_toSendData;
					 TCHAR										mutexName_syncShmData[64];
				 }												a, v;

				 int											iIndex_shmCmd;
				 
				 //  HWND											hWnd_main;

				 //
				 CAP_procInfo_video								vc;
				 void									*		pShareMediaFile;											//  2009/05/07

				 QY_VIDEO_HEADER								vh_org;
				 QY_AUDIO_HEADER								ah_org;

				 //
				 HWND											hWnd_mediaControl;


}		 MC_VAR_qmCmd;
#endif


typedef  struct  __qmShmCmd_t									{
				 DWORD											dwProcessId;
				 int											iIndex_sharedObj;
				 unsigned  int									uiTranNo_sharedObj;
				 BOOL											bQuit;
				 HWND											hWnd_task;
				 TCHAR											path[MAX_PATH  +  1];	
				 HWND											hWnd_progress;				//  2009/12/28
				 unsigned  char									ucbTaskInited;				//  set by main process
				 //
				 unsigned  char									ucbShmCmdInited;			//  set by sub process
				 unsigned  char									ucbProcessEnd;				//  set by sub process
				 //
				 HWND											hWnd_qmShmCmd;
				 //
				 BOOL											bLooping;					//   = FALSE,
				 BOOL											bPlayThrough;				//   = FALSE;
				 //
				 BOOL											bGlobalMute;
				 //
				 int											psCurrent;													//  2009/05/06

}		 QM_SHM_CMD,  QM_SHM_cmd;

#define		CONST_maxCnt_qmCmds									16
struct  __qmShm_cmds_t											{
				 WCHAR											hint[128];
				 HWND											hWnd_main;
				 //
				 unsigned  char									ucbDaemonDemo;				//  2010/09/13
				 //
				 QM_SHM_CMD										mems[CONST_maxCnt_qmCmds];
};

//
#include	"qmcStruct_defs.h"



int  newShmCmdIndex(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj  );
QM_SHM_CMD  *  getShmCmdByIndex(  QM_SHM_CMDS  *  pCmds,  int  iIndex  );


//
int  doCmdBySubProcess(  void  *  p0,  LPCTSTR  cmdStr,  LPCTSTR  cmdParam,  HANDLE  *  phProcess,  DWORD  *  pdwProcessId  );



#endif  //  }


