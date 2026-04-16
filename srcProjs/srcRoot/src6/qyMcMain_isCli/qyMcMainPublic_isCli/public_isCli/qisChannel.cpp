

#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qmcAcm.h"
#include	"qyAvRecordPublic.h" 
#include	"qyVk.h"
#include	"qyMcMainInternalBak.h"
#include	<assert.h>
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"

#include	"myDb.h"
 
//  
#include	"isCliHelpPublic.h"
#include	"saveAvProc_open.h"
#include	"qmcCommFunc_isCli.h"
#include	"ctxMcThread.h"


int  startChannel(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  MIS_CHANNEL  *  pChannel,  LPCTSTR  hint  )
{
	int						iErr				=	-1;
	DWORD					dwThreadDaemonId;

	if  (  !pProcInfo  ||  !pChannel  )  {
		assert(  pProcInfo  );
		assert(  pChannel  );

		traceLogA(  (char*)  "startChannel: pProcInfo or pChannel is null"  );
		return  -1;
	}

	if  (  pChannel->hThread_io  )  {
		Param_dbg param;
		param.m_pHint=(TCHAR*)_T("startChannel.43");
		param.m_bShowInfo = false;
		//
		if  (  bChannelOk(  pChannel,&param  )  )  {
			iErr  =  0;  goto  errLabel;
		}

		waitForObject(  &pChannel->hThread_io,  0  );
		if  (  !pChannel->hThread_io  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s is closed"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  )  );
		}
	}
	
	if  (  pMisCnt->commEncCtx.ucbPublicKeyVerified  )  {		//  2008/06/09, 需要确认后，才可以启动收发线程。				 

		if  (  !pChannel->hThread_io  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Try to start channel %s %s"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ), (  hint  ?  hint  :  _T(  ""  )  )  );

			switch  (  pChannel->uiType  )  {					//  2008/05/14. 对实时数据来说，最重要是当前数据。为了避免未发出的数据积累，先在这里清除了。
				    case  CONST_channelType_media:
					case  CONST_channelType_realTimeMedia:
					case  CONST_channelType_rtOp:
						  emptyQ2(  &pChannel->toSendQ2  );
						  emptyQ2(  &pChannel->outputQ2  );
						  break;
					default:
							break;
			}

			LPTHREAD_START_ROUTINE lpStartAddress  =  mcThreadProc_mis_io;
			#if		0
				lpStartAddress  =  mcThreadProc_mis_io_iocp;
				#ifdef  __DEBUG__
						//traceLog(  _T(  "startChannel: use iocp"  )  );
				#endif
			#endif
			//
			#ifdef  __DEBUG__	//  2016/09/09
					#if  0
						lpStartAddress  =  mcThreadProc_mis_io;
						traceLog(  _T(  "TEST: startChannel: us io"  )  );
					#endif
			#endif
			//						
			LPVOID lpParameter  =  pProcInfo->pSgiParam;
			//  2016/09/09
			lpParameter  =  pChannel;
			//
			pChannel->hThread_io  =  CreateThread(  NULL,  0,  lpStartAddress,  lpParameter,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			if  (  !pChannel->hThread_io  )  goto  errLabel;
			pChannel->dwThreadId_io  =  dwThreadDaemonId;
			if  (  ResumeThread(  pChannel->hThread_io  )  ==  -1  )  traceLogA(  (char*)  "ResumeThread recv failed"  );
			//

			//  2008/03/21
			//  bChkMessengerChannelsReady(  (  QY_MC  *  )pProcInfo->pQyMc  );
		}
	}
	
	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "startChannel failed. %s"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  )  );
	}

	return  iErr;
}


//
 int  waitForChannel(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  unsigned  int  uiChannelType,  BOOL  bForceQuit  )
{
	MIS_CHANNEL	*	pChannel	=	NULL;

	if  (  (  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )
		&&  pChannel->hThread_io  )  
	{
		if  (  !bForceQuit  )  waitForObject(  &pChannel->hThread_io,  0  );
		else  {
			  pChannel->status.ulbSessionErr  =  TRUE;
			  waitForObject(  &pChannel->hThread_io,  20000  );
			  if  (  pChannel->hThread_io  )  {
				  traceLogA(  (char*)  "waitForChannel failed."  );
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "waitForChannel failed. %s"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  )  );
			  }
		}

		if  (  !pChannel->hThread_io  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "waitForChannel ok. %s"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  )  );
		}
	}

	return  0;
}
