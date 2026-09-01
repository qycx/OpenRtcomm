

#include "stdafx.h"
#include	<stdio.h>

//#include "onvifCli.h"

#include	"onvifCliCommon.h"
#include	"showInfo_open.h"
#include	"qisMsg_open.h"
#include	"qisOnvifCommProc_open.h"
#include	"parseCmdLine_open.h"
//
#include	"dyn_qisPublic.h"

//
GBUF_onvifCli  gBuf_onvifCli  =  {0};


//
//  2016/04/03
#define		CONST_qnmVer_onvifCli							"02630379"				//  2015/08/21	//  "02622960"				//  

//
extern  "C"  char  *  qnmVerStr_onvifCli(  )
{
	char	*	p	=	"";


	p  =  CONST_qnmVer_onvifCli;


	return  p;
}


//
int  onvifCli_qisPipe_onRead(  QIS_pipe  *  pQisPipe,  void  *  pMsg,  unsigned  int  msgLen,  void  *  p0,  void  *  p1  )
{
	int  iErr  =  -1;
	unsigned  int    dwByte  =  msgLen;
	//	
	TCHAR  tBuf[128];
		
	//	
	if  (  dwByte  <  sizeof(  OnvifMsg_common  )  )  {		
		dyn_showInfo_open(  0,  0,  _T(  "pipeThread_cli err: read too small bytes < sizeof(  Onvif_msg_common  )"  )  );
		return  -1;		   
	}			
	if  (  dwByte  >  gBuf_onvifCli.uiSize_pOnvifMsgBuf  )  
	{				
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "onvifMsgBuf too small, dwByte %d > size_msgBuf %d"  ),  dwByte,  gBuf_onvifCli.uiSize_pOnvifMsgBuf  );
		dyn_showInfo_open(  0,  0,  tBuf  );
		return  -1;		
	}

	
	//
	gBuf_onvifCli.status.dwTickCnt_lastMsg  =  GetTickCount(  );

	//
	OnvifMsg_common  *  pMsgCommon  =  (  OnvifMsg_common  *  )pMsg;
	if  (  pMsgCommon->uiType  !=  CONST_qisMsgType_onvif  )  return  -1;

	//
	switch  (  pMsgCommon->iSubtype  )  {
			case  CONST_onvifMsg_subtype_discovery:  
			case  CONST_onvifMsg_subtype_probe:  {

				  //
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "onvifCli_qisPipe_onRead: tn_task %d"  ),  pMsgCommon->uiTranNo  );	
				  dyn_showInfo_open(  0,  0,  tBuf  );					     

				  //
				  if  (  pMsgCommon->ucbResp  )  {
					  dyn_showInfo_open(  0,  0,  _T(  "onvifcli_onread: msg err, ucbResp is true"  )  );
					  goto  errLabel;
				  }
				  //
				  {
					  CQySyncObj  syncObj;

					  if  (  syncObj.sync(  CONST_mtxName_syncOnvifMsgBuf  )  )  goto  errLabel;
					  //
					  memcpy(  gBuf_onvifCli.pOnvifMsgBuf,  pMsgCommon,  dwByte  );
					  //
					  gBuf_onvifCli.bMsgExists  =  TRUE;
					  break;
				  }
				  
				  }
				  //
				  break;
				
			case  CONST_onvifMsg_subtype_ptz:  {
				  OnvifMsg_ptz  *  pMsgPtz  =  (  OnvifMsg_ptz  *  )pMsgCommon;
				  //
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "onvifCli_qisPipe_onRead: ptz. %d, %S"  ),  (  int  )pMsgPtz->ucCmd,  pMsgPtz->deviceServiceAddr  );	
				  dyn_showInfo_open(  0,  0,  tBuf  );					     

				  }
				  break;
			case  CONST_onvifMsg_subtype_quit:  {
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "onvifCli_qisPipe_onRead: quit"  )  );	
				  dyn_showInfo_open(  0,  0,  tBuf  );					     
				  //
				  PostMessage(  gBuf_onvifCli.hMainWnd,  WM_CLOSE,  0,  0  );
				  }
				  break;
			default:
				    dyn_showInfo_open(  0,  0,  _T(  "onvifCli_qisPipe_onRead: unprocessed subtype"  )  );
					break;
	}

	

	iErr  =  0;

errLabel:

	//
	return  iErr;
}





//
int  onvifCli_init(  QmcAppParams_common  *  pParams,  HWND  hMainWnd  )
{
	int  iErr  =  -1;

	//
	GBUF_onvifCli  *  pGBuf  =  &gBuf_onvifCli;
	
	//
	if  (  load_dynLib_qisPublic(  )  )  {
		return  -1;
	}
	
	//
	dyn_set_who_showInfo(  _T(  "onvifCli"  )  );

	
	//
	TCHAR  tBuf[128]  =  _T(  ""  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "onvifCli starts. %S"  ),  qnmVerStr_onvifCli(  )  );
	dyn_showInfo_open(  0,  0,  tBuf  );



	//
	gBuf_onvifCli.pQisPipe  =  dyn_qisPipeNew(  );
	if  (  !gBuf_onvifCli.pQisPipe  )  goto  errLabel;

	//
			  //
		  GENERIC_Q_CFG  qCfg  =  {0};
		  TCHAR   pipeName[128]  =  _T(  ""  );
		  int  tn_rtspCliPipe  =  pParams->tn_cliPipe;
		  //
		  _sntprintf(  qCfg.name,  mycountof(  qCfg.name  ),  _T(  "qisPipe"  )  );
		  _sntprintf(  qCfg.mutexName_prefix,  mycountof(  qCfg.mutexName_prefix  ),  _T(  "qiqPipe"  )  );
		  qCfg.uiMaxQNodes  =  100;	//  CONST_uiMaxQNodes_outputQ_256;
		  
		  //		  
		  M_get_pipeName(  CONST_rtspCliPipePrefix,  pParams->appObjPrefix,  tn_rtspCliPipe,  pipeName  );

		  //
		  PARAM_initQisPipe  param  =  {0};
		  param.pf_onRead  =  onvifCli_qisPipe_onRead;
		  
		  //
		  dyn_initQisPipe(  &qCfg,  pipeName,  0,  _T(  "onvifCli"  ),  &param,  gBuf_onvifCli.pQisPipe  );

		  //
		  gBuf_onvifCli.uiSize_pOnvifMsgBuf  =  4  *  1024;
		  gBuf_onvifCli.pOnvifMsgBuf  =  (  OnvifMsg_common  *  )malloc(  gBuf_onvifCli.uiSize_pOnvifMsgBuf  );
		  if  (  !gBuf_onvifCli.pOnvifMsgBuf  )  goto  errLabel;

		  //
		  {
			 DWORD  dwThreadDaemonId;
			 //
			 if  (  !pGBuf->cmdProc.hThread  )  {
				 //
				 pGBuf->cmdProc.bQuit  =  FALSE;
				 pGBuf->cmdProc.hThread  =  CreateThread(  NULL,  0,  onvifCli_cmd_threadProc,  pGBuf,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
				 if  (  !pGBuf->cmdProc.hThread  )  goto  errLabel;					
				 pGBuf->cmdProc.dwThreadId  =  dwThreadDaemonId;			
				 if  (  ResumeThread(  pGBuf->cmdProc.hThread  )  ==  -1  )  goto  errLabel;	


			 }
		 }


	iErr  =  0;	
errLabel:
	return  iErr;
}


//
//
int  onvifCli_exit(  )
{
	int  iErr  =  -1;

	//
	dyn_showInfo_open(  0,  _T(  "onvifCli_exit"  ),  _T(  "called"  )  );

	
	//
	GBUF_onvifCli  *  pGBuf  =  &gBuf_onvifCli;
	pGBuf->cmdProc.bQuit  =  TRUE;
	//
	DWORD  dwRet;
	DWORD  dwMilliseconds  =  2000;

	//
	if  (  pGBuf->cmdProc.hThread  )  {
		
		dwRet  =  WaitForSingleObject(  pGBuf->cmdProc.hThread,  dwMilliseconds   );				
		if  (  dwRet  !=  WAIT_TIMEOUT  &&  dwRet  !=  WAIT_FAILED  )  {	

			CloseHandle(  pGBuf->cmdProc.hThread  );  pGBuf->cmdProc.hThread  =  NULL;								

		}
	}
	if  (  pGBuf->cmdProc.hThread  )  {
		dyn_showInfo_open(  0,  _T(  "onvifCli_exit"  ),  _T(  "cmdThread has not exited"  )  );
	}

	//
	if  (  !pGBuf->cmdProc.hThread  )  {
		if  (  pGBuf->pOnvifMsgBuf  )  {
			free(  pGBuf->pOnvifMsgBuf  );  pGBuf->pOnvifMsgBuf  =  NULL;
		}
	}
	
	//
	dyn_qisPipeFree(  &gBuf_onvifCli.pQisPipe  );

	//
	unload_dynLib_qisPublic(  );

	//
	iErr  =  0;
	
errLabel:
	return  iErr;
}
