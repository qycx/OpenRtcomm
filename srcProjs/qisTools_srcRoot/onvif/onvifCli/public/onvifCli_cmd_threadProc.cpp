
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
int  procOnvifMsg(  	 GBUF_onvifCli  *  pGBuf,  OnvifMsg_common  *  pMsgCommon  );




//
extern "C" DWORD WINAPI onvifCli_cmd_threadProc( LPVOID lpParameter )
{
	 int										iErr						=	-1;

	 //
	 GBUF_onvifCli  *  pGBuf  =  &gBuf_onvifCli;
	 TCHAR				tBuf[128];
	 //
	 OnvifMsg_common  *  tmppMsg  =  (  OnvifMsg_common  *  )malloc(  pGBuf->uiSize_pOnvifMsgBuf  );
	 if  (  !tmppMsg  )  goto  errLabel;

	 QIS_pipe  *  pQisPipe  =  pGBuf->pQisPipe;


	 //
	 for  (  ;  !pGBuf->bQuit  &&  !pGBuf->cmdProc.bQuit;  )  {
		  
		  //
		  DWORD  dwTickCnt  =  GetTickCount(  );
		  int  iDiff  =  dwTickCnt  -  pGBuf->status.dwTickCnt_lastMsg;
		  if  (  iDiff  <  15000  )  {
			  pGBuf->status.nTimes_readMsg_timeout  =  0;
			  }
		  else  {
			  pGBuf->status.nTimes_readMsg_timeout  ++  ;
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nTimes_readMsg_timeout %d"  ),  pGBuf->status.nTimes_readMsg_timeout  );
			  dyn_showInfo_open(  0,  _T(  "cmdProc"  ),  tBuf  );
		  }
		  if  (  pGBuf->status.nTimes_readMsg_timeout  >  30  )  {
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nTimes_readMsg_timeout too big, quit now"  )  );
			  dyn_showInfo_open(  0,  _T(  "cmdProc"  ),  tBuf  );
			  goto  errLabel;
		  }

		  //
		  if  (  pGBuf->bMsgExists  )  {
			  
			  {
				  CQySyncObj  syncObj;
				  if  (  syncObj.sync(  CONST_mtxName_syncOnvifMsgBuf  )  )  goto  errLabel;
				  //
				  memcpy(  tmppMsg,  pGBuf->pOnvifMsgBuf,  pGBuf->uiSize_pOnvifMsgBuf  );
				  //
				  pGBuf->bMsgExists  =  FALSE;
			  }
			  //
			  procOnvifMsg(  pGBuf,  tmppMsg  );

			  //
			  continue;

		  }
		  //  2016/08/03
		  if  (  pGBuf->bQuit  ||  pGBuf->cmdProc.bQuit  )  {
			  dyn_showInfo_open(  0,  0,  _T(  "cmdProc will quit: bQuit is true"  )  );
			  goto  errLabel;
		  }

		  //
		  Sleep(  1000  );
		  continue;
	 }



	 //
	 iErr  =  0;

errLabel:

	 //
	 if  (  tmppMsg  )  {
		 free(  tmppMsg  );
	 }

	 //
	 PostMessage(  pGBuf->hMainWnd,  WM_CLOSE,  0,  0  );

	 return  0;
}


int  procOnvifMsg(  	 GBUF_onvifCli  *  pGBuf,  OnvifMsg_common  *  pMsgCommon  )
{
	int  iErr  =  -1;
	TCHAR  tBuf[128];

	//
	QIS_pipe  *  pQisPipe  =  pGBuf->pQisPipe;
		
	//	
	switch  (  pMsgCommon->iSubtype  )  {
					  case  CONST_onvifMsg_subtype_discovery:  {
				  
						    //				  
						    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "onvifCli_cmdProc: onvifMsg_discovery. tn_task %d"  ),  pMsgCommon->uiTranNo  );					  
							dyn_showInfo_open(  0,  0,  tBuf  );					     

						    //				  
						    if  (  pMsgCommon->ucbResp  )  {
								dyn_showInfo_open(  0,  0,  _T(  "onvifcli_onread: msg discovery err, ucbResp is true"  )  );					  
								goto  errLabel;				  
							}
				  		
							//				 
							OnvifMsg_ipCams  res  =  {0};				  
							//
							res.uiType  =  CONST_qisMsgType_onvif;
							res.iSubtype  =  CONST_onvifMsg_subtype_ipCams;
							//
							res.ucbResp  =  TRUE;
							res.uiTranNo  =  pMsgCommon->uiTranNo;				  
							//
							int  index;				  
							//
							Onvif_ipCam  *  pIpCam  =  &res.mems[res.usCnt];
							index  =  0;
							_snprintf(  pIpCam->urls[index].token,  mycountof(  pIpCam->urls[index].token  ),  "mainToken"  );
							_snprintf(  pIpCam->urls[index].rtspUrl.url,  mycountof(  pIpCam->urls[index].rtspUrl.url  ),  "rtsp://127.0.0.1/video.264"  );
							index  =  1;
							_snprintf(  pIpCam->urls[index].token,  mycountof(  pIpCam->urls[index].token  ),  "submainToken"  );
							_snprintf(  pIpCam->urls[index].rtspUrl.url,  mycountof(  pIpCam->urls[index].rtspUrl.url  ),  "rtsp://127.0.0.1/video.264"  );
							//
							_snprintf(  pIpCam->deviceServiceAddr,  mycountof(  pIpCam->deviceServiceAddr  ),  "%s",  "http://127.0.0.1:8080/onvif/device_service"  );				  
							//
							res.usCnt  ++  ;
							//
							pIpCam  =  &res.mems[res.usCnt];
							index  =  0;
							_snprintf(  pIpCam->urls[index].token,  mycountof(  pIpCam->urls[index].token  ),  "mainToken"  );
							_snprintf(  pIpCam->urls[index].rtspUrl.url,  mycountof(  pIpCam->urls[index].rtspUrl.url  ),  "rtsp://127.0.0.1/720p.ts"  );
							index  =  1;
							_snprintf(  pIpCam->urls[index].token,  mycountof(  pIpCam->urls[index].token  ),  "submainToken"  );
							_snprintf(  pIpCam->urls[index].rtspUrl.url,  mycountof(  pIpCam->urls[index].rtspUrl.url  ),  "rtsp://127.0.0.1/240p.264"  );				  
							//
							_snprintf(  pIpCam->deviceServiceAddr,  mycountof(  pIpCam->deviceServiceAddr  ),  "%s",  "http://127.0.0.1:8080/onvif/device_service"  );				  
							//				  
							res.usCnt  ++  ;
							
							//
							//  qisPipe_writeMsg(  &res,  sizeof(  res  ),  pQisPipe  );
							dyn_qisPipeWriteMsg(  &res,  sizeof(  res  ),  pQisPipe  );
				  
							}				 
							//
							break;
					  case  CONST_onvifMsg_subtype_probe:  {
						    OnvifMsg_probe  *  pMsgProbe  =  (  OnvifMsg_probe  *  )pMsgCommon;
				  
							//				  
						    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "onvifCli_cmdProc: onvifMsg_probe mmmm. tn_task %d"  ),  pMsgCommon->uiTranNo  );					  
							dyn_showInfo_open(  0,  0,  tBuf  );					     

							//				  
							if  (  pMsgCommon->ucbResp  )  {
								dyn_showInfo_open(  0,  0,  _T(  "onvifcli_onread: msg probe err, ucbResp is true"  )  );
								goto  errLabel;				  
							}				  
							//
							OnvifMsg_ipCams  res  =  {0};				  
							//
							res.uiType  =  CONST_qisMsgType_onvif;
							res.iSubtype  =  CONST_onvifMsg_subtype_ipCams;				  
							//
							res.ucbResp  =  TRUE;
							res.uiTranNo  =  pMsgCommon->uiTranNo;
				  
							//
							int  index;				  
							//
							Onvif_ipCam  *  pIpCam  =  &res.mems[res.usCnt];
							index  =  0;
							_snprintf(  pIpCam->urls[index].token,  mycountof(  pIpCam->urls[index].token  ),  "mainToken"  );
							_snprintf(  pIpCam->urls[index].rtspUrl.url,  mycountof(  pIpCam->urls[index].rtspUrl.url  ),  "rtsp://127.0.0.1/video.264"  );
							index  =  1;
							_snprintf(  pIpCam->urls[index].token,  mycountof(  pIpCam->urls[index].token  ),  "submainToken"  );
							_snprintf(  pIpCam->urls[index].rtspUrl.url,  mycountof(  pIpCam->urls[index].rtspUrl.url  ),  "rtsp://127.0.0.1/video.264"  );
							//
							_snprintf(  pIpCam->deviceServiceAddr,  mycountof(  pIpCam->deviceServiceAddr  ),  "%s",  "http://127.0.0.1:8080/onvif/device_service"  );				  
							//
							res.usCnt  ++  ;

							//
							dyn_qisPipeWriteMsg(  &res,  sizeof(  res  ),  pQisPipe  );
				  				 
							}
							//				
							break;
					  default:				    
						      dyn_showInfo_open(  0,  0,  _T(  "onvifCli_cmdProc: unprocessed subtype"  )  );					
							  break;	
			  }


	iErr  =  0;

errLabel:
			  
	return  iErr;
}


