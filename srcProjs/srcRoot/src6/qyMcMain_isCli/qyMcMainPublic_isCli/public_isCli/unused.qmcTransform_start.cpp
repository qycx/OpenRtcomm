

#include	"stdafx.h"

#include	<time.h>
#include	<stddef.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qmcAcm.h"
//#include	"qyAvRecordPublic.h" 
#include	"qyVk.h"
#include	"qyMcMainInternalBak.h"
#include	<assert.h>
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"

#include	"myDb.h"
 
//  
//#include	"isCliHelpPublic.h"
#include	"saveAvProc_open.h"
#include	"qmcCfg.h"
#include	"ctxQmc.h"

//
//
BOOL  isTooManyThreads(  );



// 
int  startTransformThread(  MC_VAR_common  *  pProcInfo,  unsigned  int  uiTaskType,  PROC_TASK_AV  *  pTask,  QY_TRANSFORM  *  p  )
{	
	int  iErr  =  -1;
	DWORD				dwThreadDaemonId;
	//MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );

	QMC_status  *  pStatus  =  pProcInfo->get_qmc_status(  );
	if  (  !pStatus  )  return  -1;

	TCHAR				tHintBuf[128]	=	_T(  ""  );

		 //  QY_TRANSFORM	*	p	=	&pTask->pTransforms[i];

		 //  2014/08/04

		 //
		 //if  (  !bVideoOnly  )  
		 {
			 if  (  !p->audio.hThread  )  {
				 //
				 p->audio.bQuit  =  FALSE;
				 p->audio.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_decAudio,  p,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
				 if  (  !p->audio.hThread  )  goto  errLabel;					
				 p->audio.dwThreadId  =  dwThreadDaemonId;			
				 if  (  ResumeThread(  p->audio.hThread  )  ==  -1  )  goto  errLabel;									 

				 //  2012/03/25
				 InterlockedIncrement(  &pStatus->nThreads_dec  );

			 }				
			 if  (  !p->video.hThread  )  {
				 //
				 p->video.bQuit  =  FALSE;
				 p->video.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_decVideo,  p,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
				 if  (  !p->video.hThread  )  goto  errLabel;					
				 p->video.dwThreadId  =  dwThreadDaemonId;			
				 if  (  ResumeThread(  p->video.hThread  )  ==  -1  )  goto  errLabel;	

				 //  2012/03/25
				 InterlockedIncrement(  &pStatus->nThreads_dec  );

			 }
			 //  2011/12/09
			 if  (  !p->v_preTransThread.hThread  )  {
				 //
				 p->v_preTransThread.bQuit  =  FALSE;
				 p->v_preTransThread.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_preTransformVideo,  p,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
				 if  (  !p->v_preTransThread.hThread  )  goto  errLabel;					
				 p->v_preTransThread.dwThreadId  =  dwThreadDaemonId;			
				 if  (  ResumeThread(  p->v_preTransThread.hThread  )  ==  -1  )  goto  errLabel;	

				 //  2012/03/25
				 InterlockedIncrement(  &pStatus->nThreads_dec  );
	
			 }
			 //
			}


		 iErr  =  0;

errLabel:
		 return  iErr;
	
}

 int  startTransformThreads(  MC_VAR_common  *  pProcInfo,  unsigned  int  uiTaskType,  PROC_TASK_AV  *  pTask  )
{
	int					iErr	=	-1;
	int					i;
	DWORD				dwThreadDaemonId;
	//MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	TCHAR				tHintBuf[128]	=	_T(  ""  );

	QMC_status* pStatus = pProcInfo->get_qmc_status();
	if (!pStatus)  return  -1;

	//BOOL				bVideoOnly		=	FALSE;

#if  0	//  2014/04/19
	switch  (  uiTaskType  )  {
			case  CONST_imTaskType_viewDynBmp:
			case  CONST_imTaskType_shareScreen:
				  bVideoOnly  =  TRUE;
				  break;
			default:
					break;
	}
#endif

	//
	if  (  isTooManyThreads(  )  )  {
		_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "too many dec threads"  )  );
		goto  errLabel;
	}

	//
	for  (  i  =  0;  i  <  pTask->usCntLimit_transforms;  i  ++  )  {
		 QY_TRANSFORM	*	p	=	&pTask->pTransforms[i];

		 //
		 if  (  startTransformThread(  pProcInfo,  uiTaskType,  pTask,  p  )  )  goto  errLabel;

	}

	//  2014/11/11
#if  0
	if  (  pTask->confMosaicTrans.bExists_confMosaic  )  {
		if  (  startTransformThread(  pProcInfo,  uiTaskType,  pTask,  &pTask->confMosaicTrans.confMosaic_video.transform  )  )  goto  errLabel;
		if  (  startTransformThread(  pProcInfo,  uiTaskType,  pTask,  &pTask->confMosaicTrans.confMosaic_resource.transform  )  )  goto  errLabel;

	}
#endif




	//
	iErr  =  0;
errLabel:

	OutputDebugString(  _T(  "startTransformTrheads leaves with "  )  );
	OutputDebugString(  iErr  ?  _T(  "failed"  )  :  _T(  "Ok"  )  );
	OutputDebugString(  _T(  "\n"  )  );

	if  (  iErr  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "startTransformThreads failed, %s"   ),  tHintBuf  );
	}

	return  iErr;
}


