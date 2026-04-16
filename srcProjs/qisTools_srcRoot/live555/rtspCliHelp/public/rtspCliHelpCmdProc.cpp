


#include	"stdafx.h"
#include	<Windows.h>
#include	<stdlib.h>
#include	<tchar.h>
#include	<stddef.h>
#include	<mmsystem.h>

#include	"rtspCliHelpCommon.h"



extern "C" DWORD WINAPI mcThreadProc_cmdProc( LPVOID lpParameter )
{


	 #define		DEFAULT_dwToInMs		5000
	 DWORD								dwToInMs					=	DEFAULT_dwToInMs;

	 DWORD								dwTickCnt_lastAudioData		=	GetTickCount(  );;						// 

	 GBUF_rtspCliHelp			*		pGBuf						=	&gBuf_rtspCliHelp;
	 CTX_rtspCliHelp_cmdProc			ctx;
	 memset(  &ctx,  0,  sizeof(  ctx  )  );

	 OutputDebugString(  _T(  "thread_cmdProc enters\n"  )  );
	 dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "rtspCli::thread_cmdProc starts"  )  );
	 
	 
	 //
	 gBuf_rtspCliHelp.cmdProc.bRunning  =  TRUE;
	 //  memset(  &pDispatchAudio->m_var,  0,  sizeof(  pDispatchAudio->m_var  )  );



	 //

	int  dwToInMs_rtsp  =  3000;
	DWORD  dwRet;

	 //
	 for  (  ;  !gBuf_rtspCliHelp.bQuit;  )  {
		 
		  dwRet  =  WaitForSingleObject(  gBuf_rtspCliHelp.common.hEvent_syncQuit,  3000  );
		  if  (  dwRet  !=  WAIT_FAILED  &&  dwRet  !=  WAIT_TIMEOUT  )  {
			  dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "rtspCli::cmdProc getCmd Quit"  )  );
			  break;
		  }

		  //
		  DWORD	dwTickCnt  =  GetTickCount(  );
		  int	iDiffInMs  =  dwTickCnt  -  gBuf_rtspCliHelp.common.status.dwLastTickCnt_BufferCB_rtspCli;
		  if  (  abs(  iDiffInMs  )  <  5000  )  {
			  gBuf_rtspCliHelp.cmdProc.status.nCnt_noDataArrive  =  0;
			  }
		  else  {
			    gBuf_rtspCliHelp.cmdProc.status.nCnt_noDataArrive  ++  ;

				TCHAR	tBuf[128];				
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "rtspCli::thread_cmdProc, no data arrives. %dms"  ),  iDiffInMs  );
				dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  tBuf  );

				//
				int  max_noDataArrive = 3;
				//
#ifdef  _DEBUG
				max_noDataArrive = 10000;
#endif 
				//
				if  (  gBuf_rtspCliHelp.cmdProc.status.nCnt_noDataArrive  >=  max_noDataArrive  )  {
					gBuf_rtspCliHelp.cmdProc.bSeriousErr  =  TRUE;

					dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "rtspCli::thread_cmdProc, waiting too long. serious err"  )  );
					goto  errLabel;
				}
		  }

		  continue;
	 }

errLabel:
	 
			

	 //
	 gBuf_rtspCliHelp.cmdProc.bRunning  =  FALSE;

	 
	 //
	 gBuf_rtspCliHelp.cmdProc.bStopped  =  TRUE;

	 dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "rtspCli::thread_cmdProc stops"  )  );
	 OutputDebugString(  _T(  "mcThreadProc_cmdProc quit\n"  )  );

	 if  (  gBuf_rtspCliHelp.cmdProc.bSeriousErr  )  {
		 dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "rtspCli::thread_cmdProc, exit now"  )  );
		 //
		 int  i;
		 for  (  i  =  0;  i  <  3;  i  ++  )  {
			  Sleep(  50  );
		 }
		 exit(  0  );
	 }

	return  0;
}

//
extern  bool  g_bDbg;

//
bool  bRespCliQuit()
{
#if  _DEBUG
	if (g_bDbg) {
		return  false;
	}
#endif 


	//
	if (gBuf_rtspCliHelp.spl.bStopped
		|| gBuf_rtspCliHelp.cmdProc.bStopped)
	{
		return  true;
	}

	return  false;
}



