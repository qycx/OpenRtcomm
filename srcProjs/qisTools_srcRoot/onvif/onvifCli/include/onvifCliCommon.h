
#ifndef  __onvifCliCommon_h__
#define  __onvifCliCommon_h__	//  {


#include	<stdlib.h>
#include	<tchar.h>
#include	<stddef.h>
#include	<mmsystem.h>

//
#include	"qdcOpenCommon.h"

#include	"qySyncObj.h"
#include	"genericQueue.h"
#include	"qisPipe_open.h"
#include	"parseCmdLine_open.h"
#include	"qisOnvifCommProc_open.h"

//
typedef  struct								{
			
			//
			HWND							hMainWnd;
	
			//
			QIS_pipe				*		pQisPipe;
		

			//
			BOOL							bQuit;
		
			//
			OnvifMsg_common			*		pOnvifMsgBuf;
			int								uiSize_pOnvifMsgBuf;
			//
			BOOL							bMsgExists;

			//

			
			//  2014/06/06
			struct							{
				HANDLE						hThread;
				DWORD						dwThreadId;
				//
				BOOL						bQuit;

			}								cmdProc;

			//
			struct							{
				DWORD						dwTickCnt_lastMsg;
				int							nTimes_readMsg_timeout;
			}								status;

			//
}		GBUF_onvifCli;

//
extern  GBUF_onvifCli  gBuf_onvifCli;


int  onvifCli_init(  QmcAppParams_common  *  pParams,  HWND  hMainWnd  );
int  onvifCli_exit(  );

//
extern "C" DWORD WINAPI onvifCli_cmd_threadProc( LPVOID lpParameter );


#endif  //  }



