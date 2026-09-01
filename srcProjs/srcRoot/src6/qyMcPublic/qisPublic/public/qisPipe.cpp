

#include	"stdafx.h"

#include	<stddef.h>
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>

#include	<WinSock2.h>
#include	<tchar.h>

#include	"qyCommonEx.h"

#include	"qysynccommproc.h"
#include	"genericQueue.h"
#include	"qyq2.h"

#include	"qycommproc.h"


#include	"qmOpenCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmcomm.h"
#include	"qnmCommProc.h"

#include	"qisPipe.h"
#include <qytcharcommproc.h>

//
extern "C" DWORD WINAPI mcThreadProc_qisPipe_starter( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_qisPipe_cli( LPVOID lpParameter );




//
extern  "C"  __declspec(  dllexport  )  QIS_pipe  *  qisPipeNew(  )
{
	int  iErr  =  -1;
	QIS_pipe  *  p  =  NULL;
	int  size  =  sizeof(  QIS_pipe  );
	p  =  (  QIS_pipe  *  )mymalloc(  size  );
	if  (  !p  )  return  NULL;
	memset(  p,  0,  size  );


	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		qisPipeFree(  &p  );
	}

	return  iErr  ?  NULL  :  p;
}

//
extern  "C"  __declspec(  dllexport  )  void  qisPipeFree(  QIS_pipe  **  pp  )
{
	if  (  !pp  ||  !*pp  )  return;

	//
	exitQisPipe(  *pp  );

	//
	myfree(  *pp  );  *pp  =  NULL;
	return;
}


//
extern  "C"  __declspec(dllexport)  int  initQisPipeA(char  *  q_name, char  *  q_mutexName_prefix,  int  q_uiMaxQNodes, char  *  pipeName, BOOL  bStarter, char  *  name, PARAM_initQisPipe* pParam, QIS_pipe* p)
{

	GENERIC_Q_CFG  qCfg = { 0 };
	//
	myUtf82TChar(q_name, qCfg.name, mycountof(qCfg.name));
	myUtf82TChar(q_mutexName_prefix, qCfg.mutexName_prefix,  mycountof(qCfg.mutexName_prefix));
	qCfg.uiMaxQNodes = q_uiMaxQNodes;// 100;	//  CONST_uiMaxQNodes_outputQ_256;




	//
	TCHAR  tmp_pipeName[128] = _T("");
	TCHAR  tmp_name[128] = _T("");

	//
	myUtf82TChar(pipeName, tmp_pipeName, mycountof(tmp_pipeName));
	myUtf82TChar(name, tmp_name, mycountof(tmp_name));

	int  tmpiRet = initQisPipe(&qCfg, tmp_pipeName, bStarter, tmp_name, pParam, p);


	return  tmpiRet;
}


//
//
extern  "C"  __declspec(  dllexport  )  int  initQisPipe(  GENERIC_Q_CFG  *  pqCfg,  LPCTSTR  pipeName,  BOOL  bStarter,  LPCTSTR  name,  PARAM_initQisPipe  *  pParam,  QIS_pipe  *  p  )
{
	int  iErr  =  -1;
	
	//
	if  (  !pipeName  ||  !pipeName[0]  )  return  -1;
	if  (  !pParam  )  {
		showInfo_open0(  0,  0,  _T(  "initQisPipe failed, pParam is null"  )  );
		return  -1;
	}
	if  (  p->bInited  )  {
		showInfo_open0(  0,  0,  _T(  "initQisPipe failed, bInited already true"  )  );
		return  -1;
	}

	//
	safeTcsnCpy(  pipeName,  p->cfg.pipeName,  mycountof(  p->cfg.pipeName  )  );
	
	//
	p->cfg.bStarter  =  bStarter;

	//
	safeTcsnCpy(  name,  p->name,  mycountof(  p->name  )  );
	
	//
	memcpy(  &p->param,  pParam,  sizeof(  p->param  )  );

	//
#if  0
				  //
			  _sntprintf(  pMisCnt->cfg.outputQ.name,  mycountof(  pMisCnt->cfg.outputQ.name  ),  _T(  "outputQ%u"  ),  i  );
			  _sntprintf(  pMisCnt->cfg.outputQ.mutexName_prefix,  mycountof(  pMisCnt->cfg.outputQ.mutexName_prefix  ),  _T(  "qmcOutputQ%u"  ),  i  );			  				  
			  pMisCnt->cfg.outputQ.uiMaxQNodes  =  CONST_uiMaxQNodes_outputQ_256;

			  //
			  //M_get_pipeName(  CONST_rtspCliPipePrefix,  pProcInfo->get_appObjPrefix(  ),  pRtsp->tn_rtspCliPipe,  pipeName  );

#endif

	//
	RW_lock_param  rwLockParam  =  {0};
		
	//	
	rwLockParam.uiMaxCnt_sema			=	CONST_uiInitCnt_sema_q2SyncFlg;	
	rwLockParam.uiInitCnt_sema			=	rwLockParam.uiMaxCnt_sema  -  1;
	rwLockParam.uiMilliSeconds_mutex_r	=	10000;
	rwLockParam.uiMilliSeconds_sema_r	=	10000;
	rwLockParam.uiMilliSeconds_mutex_w	=	10000;	 
	rwLockParam.uiMilliSeconds_sema_w	=	10000;


	//							  
	if  (  initQyQ2(  pqCfg,  &rwLockParam,  1,  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &p->outputQ2  )  )  goto  errLabel;


	//  2015/06/23
	p->hEvent_syncThreadQuit_recvRtsp  =  CreateEvent(  NULL,  FALSE,  FALSE,  NULL  );
	if  (  !p->hEvent_syncThreadQuit_recvRtsp  )  goto  errLabel;

	//
	DWORD  dwThreadDaemonId;

	//
	LPTHREAD_START_ROUTINE  lpStartAddress  =  NULL;
	//
	if  (  bStarter  )  lpStartAddress  =  mcThreadProc_qisPipe_starter;
	else  lpStartAddress  =  mcThreadProc_qisPipe_cli;

	//
	p->bQuit  =  FALSE;
	p->hThread_recvRtsp  =  CreateThread(  NULL,  0,  lpStartAddress,  p,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
	if  (  !p->hThread_recvRtsp  )  goto  errLabel;					
	p->dwThreadId  =  dwThreadDaemonId;					
	if  (  ResumeThread(  p->hThread_recvRtsp  )  ==  -1  )  goto  errLabel;									 


	//
	p->bInited  =  TRUE;

	//
	iErr  =  0;

errLabel:
	
	if  (  iErr  )  {
		exitQisPipe(  p  );
	}

	//
	TCHAR  tBuf[128];
	_sntprintf(tBuf, mycountof(tBuf), _T("%s %s"), p->name, iErr ? _T("Failed") : _T("OK"));
	showInfo_open0(  0,  _T("initQisPipe"), tBuf );

	//
	return  iErr;
}


//
extern  "C"  __declspec(  dllexport  )  int  exitQisPipe(  QIS_pipe  *  p  )
{
	if  (  !p  )  return  -1;

	//
	QIS_pipe *  pPipe  =  p;

	//
	pPipe->bQuit  =  TRUE;

	//
	//这里应该停止线程。
	if  (  pPipe->hThread_recvRtsp  )  {
		
		//  2015/06/22
		SetEvent(  p->hEvent_syncThreadQuit_recvRtsp  );

		//	 
		waitForObject(  &pPipe->hThread_recvRtsp,  20000  );		
		if  (  pPipe->hThread_recvRtsp  )  {
				  traceLogA(  "waitForChannel failed."  );
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "waitForChannel failed. "  )  );
			  }

		if  (  !pPipe->hThread_recvRtsp  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "waitForChannel ok. "  )  );
		}
	}

	//
	//  2015/06/23
	if  (  p->hEvent_syncThreadQuit_recvRtsp  )  {
		CloseHandle(  p->hEvent_syncThreadQuit_recvRtsp  );  p->hEvent_syncThreadQuit_recvRtsp  =  NULL;
	}


	//
	exitQyQ2(  &p->outputQ2  );

	//
	p->bInited  =  FALSE;

	//
	showInfo_open0(  0,  _T(  "exitQisPipe"  ),  _T(  "OK"  )  );


	return  0;
}



//
extern  "C"  __declspec(  dllexport  )  int  qisPipe_writeMsg(  void  *  pMsg,  unsigned  int  msgLen,  QIS_pipe  *  pQisPipe  )
{
	if  (  !pQisPipe  )  return  -1;
	if  (  !pQisPipe->bInited  )  return  -1;

	if  (  !pMsg  )  {
		return  -1;
	}
	//
	if  (  msgLen  <  sizeof(  int  )  )  {
		showInfo_open0(  0,  0,  _T(  "qisPipe_writeMsg failed, msgLen too small"  )  );
		return  -1;
	}

	//
#if  0
	int  msgLen  =  offsetof(  RTSP_msg,  buf  )  +  pMsg->uiLen;
	if  (  msgLen  >  sizeof(  RTSP_msg  )  )  {
		showInfo_open0(  0,  0,  _T(  "qisPipe_writeMsg failed, msgLen too big"  )  );
		return  -1;
	}
#endif

	return  q2PostMsgAndTrigger(  pMsg,  msgLen,  &pQisPipe->outputQ2,  _T(  "qisPipe_writeMsg"  )  );
}







