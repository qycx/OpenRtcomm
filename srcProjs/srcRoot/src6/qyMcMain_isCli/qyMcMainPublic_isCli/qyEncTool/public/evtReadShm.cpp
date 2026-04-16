



#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//#include	"qmcVideoCapture_isCli.h"
//#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

#include	"qmcVideoCapture_rtsp.h"
#include	"qmcCopyData.h"
#include	"rtspUsrData.h"
#include	"CtxQmcEvt.h"

//
#include	"vtShmFunc.h"

//
int  readShmPkt(  VT_shm_content  *  pShmContent,  BITMAPINFOHEADER  *  pBih,  unsigned  char  ucCnt_shmPktBufs,  int  index_toRead,  QY_Q2  *  pQ2  )
{
	int  iErr  =  -1;
	//
	//
	if  (  ucCnt_shmPktBufs  >  mycountof(  pShmContent->mems  )  )  return  -1;
	if  (  index_toRead  <  0  ||  index_toRead  >=  ucCnt_shmPktBufs  )  return  -1;
	
	TCHAR  tBuf[128]  =  _T(  ""  );
	VT_shm_pktInfo  *  pShmPkt  =  &pShmContent->mems[index_toRead];	
	//	
	if  (  !pShmPkt->bDataReady  )  {		
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "readShm failed: shm.mems[%d].bDataReady is false. uiCnt_read %d, uiCnt_write %d"  ),  index_toRead,  pShmContent->status.readShm.uiCnt_readShm,  pShmContent->status.writeShm.uiCnt_writeShm   );
		showInfo_open0(  0,  0,  tBuf  );					  						  
		return  -1;		
	}
					
	//	
	BYTE  *  pImg  =  NULL;
		
	//	
	CQyMalloc  mallocObj_pkt;		
	myDRAW_VIDEO_DATA  pkt;
	myDRAW_VIDEO_DATA  *  p  =  &pkt;						
	int					  len  =  sizeof(  pkt  );						
	//
	memset(  p,  0,  sizeof(  p[0]  )  );
			
	//	
	p->bih  =  *pBih;
			
	//	
	if  (  pShmPkt->usPktResType  ==  CONST_pktResType_sharedTex  )  {		
		p->usPktResType  =  pShmPkt->usPktResType;
		p->sharedTex.pktSharedTexInfo  =  pShmPkt->pktSharedTexInfo;							
				  
		//					
		unsigned  int  uiSize_dec  =  0;			
		unsigned  int  uiSize_enc  =  sizeof(  TRANSFER_VIDEO_DATA  );
				  
		//					
		p->head.uiLen  =  uiSize_dec  +  uiSize_enc;			
		p->head.uiSampleTimeInMs  =  0;							  		  
		//
		p->uiSize_dec  =  uiSize_dec;
		
		char  *  pData  =  mallocObj_pkt.mallocf(  0,  p->head.uiLen  );
		if  (  !pData  )  {
			showInfo_open0(  0, 0,  _T(  "readRtt: malloc failed"  )  );
			goto  errLabel;				 
		}
		if  (  mallocObj_pkt.get(  &p->memory  )  )  goto  errLabel;
		
		}		
	else  {  		
		  //			
		  pImg  =  (  BYTE  *  )pShmContent->buf  +  index_toRead  *  pBih->biSizeImage;
		  			
		  //			
		  BYTE					*	pBuffer;			
		  int							BufferLen;
		  
		  //			
		  pBuffer  =  pImg;			
		  BufferLen  =  pBih->biSizeImage;							  
		  							
		  //			
		  unsigned  int  uiSize_dec  =  max(  pBih->biSizeImage,  BufferLen  );			
		  unsigned  int  uiSize_enc  =  sizeof(  TRANSFER_VIDEO_DATA  );
		  							  
		  //			
		  p->head.uiLen  =  uiSize_dec  +  uiSize_enc;			
		  p->head.uiSampleTimeInMs  =  0;							  
		  //
		  p->uiSize_dec  =  uiSize_dec;
						
		  //			
		  if  (  !mallocObj_pkt.mallocf(  pkt.head.uiLen  )  )  goto  errLabel;			
		  if  (  mallocObj_pkt.get(  &p->memory  )  )  goto  errLabel;							  
		  //
		  memcpy(  p->memory.m_pBuf,  pImg,  pBih->biSizeImage  );			
	}
	
	//
	M_set_pktId_alloc(  p  );


	//	
	if  (  q2PostMsgAndTrigger(  p,  len,  pQ2  )  )  {		
		goto  errLabel;						
	}
	mallocObj_pkt.detach(  );

											

	//  2014/02/10
	pShmPkt->bDataReady  =  FALSE;
	
	//
	iErr  =  0;

errLabel:
				
	return  iErr;

}


extern  "C"  DWORD WINAPI mcThreadProc_readShm_evt( LPVOID lpParameter )
{
	int										iErr						=	-1;
	QY_SHARED_OBJ						*	pSharedObj					=	(  QY_SHARED_OBJ  *  )lpParameter;
	if  (  !pSharedObj  )  return  -1;
	 CCtxQmcEvt						*	pProcInfo					=	(  CCtxQmcEvt  *  )pSharedObj->pProcInfo;//QY_GET_procInfo_isCli(  );
	 if (  !pProcInfo  )  return  -1;
	 QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	 if  (  !pQmcCfg  )  return  -1;

	 //  
	 CAP_procInfo_bmpCommon  *  pCapBmp  =  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
	 if  (  !pCapBmp  )  return  -1;

	 QY_MC							*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;

	 //
	 DWORD								dwThreadId					=	GetCurrentThreadId(  );

	 int								i;
	 
	 //
	 EVT_encV						*	pEvt						=	(  EVT_encV  *  )pSharedObj->pEvt;
	 if  (  !pEvt  )  return  -1;
	 //
	 //RTSP_cli_common				*	pRtspCli					=	(  RTSP_cli_common  *  )pDvtCli->pRtspCli;	
	 
	 QY_shm  *  pShm  =  &pEvt->dataShm;
	 VT_shm_content  *  pShmContent  =  (  VT_shm_content  *  )pShm->pBuf;
	 BITMAPINFOHEADER	bih_shm  =  pShmContent->bih_dec;

	 //
	 QDC_OBJ_INFO					*	pQdcObjInfo					=	&pCapBmp->compressVideo.u.qoi.myQoi.common;	//  .qdcObjInfo;

	 //
	 myDRAW_VIDEO_DATA					pkt;

	 //  2015/02/19
	 int  total_nPkts  =  0;
	 TCHAR  tBuf[128]  =  _T(  ""  );

	 //
	 DWORD  dwLastTickCnt_setFlg_forceKeyFrame  =  0;

	 //  2015/02/19
	 //if  (  !pTransformVideo->pTmpDataQ  )  goto  errLabel;

	 //
	 for  (  ;  !pEvt->bQuit;  )  {
	  
		  HANDLE  hs[5];
		  unsigned  short  usCnt  =  0;
		  hs[usCnt]  =  pEvt->readShm.hEvent_syncR;  usCnt  ++  ;

		  //
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(							
							 usCnt,	//  mycountof(  pPlay->hEvents  ),				// Number of events.
							 hs,							// Location of handles.
                             FALSE,										// Wait for all?
                             5000,									// How long to wait?
                             0  );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  goto  errLabel;
	      //
		  //dwTickCnt  =  GetTickCount(  );

		  if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
			  dwEvt -= WAIT_OBJECT_0;
			  switch  (  dwEvt  )  {
					  case  0:
						     //  dwTickCnt_lastData  =  dwTickCnt;		//  audio data received
							 #ifdef  __DEBUG__
									traceLogA(  "mcThreadProcInfo_readShm: event 0."  );
									//showInfo_open0(  0,  0,  _T(  "readShm: event0"  )  );
							 #endif
							 break;
					  case  1:
						     traceLogA(  "mcThreadProcInfo_readShm: event 1."  );
							 break;
					  default:
						     traceLogA(  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
			  //
			  #ifdef  __DEBUG__
					  if  (  pShmContent->u.evt.i.ucbShowEncVStatus  )  
					  {
						  //showInfo_open0(  0,  0,  _T(  "readShm here"  )  );
					  }
			  #endif
		  }


		  //
		  for  (  ;  !pEvt->bQuit;  )  {

			   //  2015/10/17
			   if  (  pShmContent->u.evt.i.bNeed_forceKeyFrame  )  {
				   DWORD  dwTickCnt  =  GetTickCount(  );
				   if  (  abs(  (  long  )(  dwTickCnt  -  dwLastTickCnt_setFlg_forceKeyFrame  )  )  >  1000  )  {
					   setFlg_forceKeyFrame(  pProcInfo,  pProcInfo->m_var.iIndex_sharedObj  );
					   dwLastTickCnt_setFlg_forceKeyFrame  =  dwTickCnt;
				   }
			   }
			   //  2015/10/20
			   if  (  pShmContent->u.evt.i.ucbShowEncVStatus  !=  pQmcCfg->debugStatusInfo.ucbShowEncVStatus  )  {
				   pQmcCfg->debugStatusInfo.ucbShowEncVStatus  =  pShmContent->u.evt.i.ucbShowEncVStatus;
			   }

			      //
				  int  ucCnt_shmPktBufs  =  pShmContent->ucCnt_shmPktBufs;
				  if  (  !ucCnt_shmPktBufs  ||  ucCnt_shmPktBufs  >  mycountof(  pShmContent->mems  )  )  goto  errLabel;
				  //
				  if  (  pShmContent->status.readShm.uiCnt_readShm  >=  pShmContent->status.writeShm.uiCnt_writeShm  )  {
					  //
					  if  (  pShmContent->u.evt.i.ucbShowEncVStatus  )  {
						  for  (  i  =  0;  i  <  ucCnt_shmPktBufs;  i  ++  )  {
							   if  (  pShmContent->mems[i].bDataReady  )  {
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Err: uiCnt_read %d >= uiCnt_write %d. and mems[%d].bDataReady is ture"  ),  pShmContent->status.readShm.uiCnt_readShm,  pShmContent->status.writeShm.uiCnt_writeShm,  i  );
								   showInfo_open0(  0,  0,  tBuf  );
								   break;
							   }
						  }
					  }
					  //
					  break;
				  }
				  //
				  int  index_toRead  =  pShmContent->status.readShm.uiCnt_readShm  %  ucCnt_shmPktBufs;
				  VT_shm_pktInfo  *  pShmPkt  =  &pShmContent->mems[index_toRead];
				  		
				  //  2015/10/04					
				  if  (  pQdcObjInfo->var.usPktResType_dec  !=  pShmPkt->usPktResType  )  {							
					  if  (  !pQdcObjInfo->var.usPktResType_dec  )  {
						  pQdcObjInfo->var.usPktResType_dec  =  pShmPkt->usPktResType;								
						  //
						  showInfo_open0(  0,  0,  _T(  "readShm: qdcObjInfo.usPktResType_dec set to shmMem."  )  );							
						  }							
					  else  {							
						    showInfo_open0(  0,  0,  _T(  "readShm: failed, qdcObjInfo.usPktResType_dec != shmMem."  )  );							
					  }						
				  }
				  if  (  readShmPkt(  pShmContent,  &bih_shm,  ucCnt_shmPktBufs,  index_toRead,  &pCapBmp->thread.q2  )  )  {
					  break;
				  }

				  //  2015/10/06
				  //
				  pShmContent->status.readShm.uiCnt_readShm  ++  ;
				  SetEvent(  pEvt->readShm.hEvent_syncW  );	//  2015/02/19
	
				  //  2015/11/02
				  if  (  pShmContent->status.uiSeqNo_lastRender  !=  pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender  )  {
					  pShmContent->status.uiSeqNo_lastRender  =  pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender;
				  }

				  //
				  pProcInfo->m_var.evtStatus.dwLastTickCnt_readShm  =  GetTickCount(  );


				  //
				  continue;
		  }


		  continue;
	 }
	 
	 iErr =  0;
errLabel:

	 //
	 pEvt->status.bStopped_threadReadShm  =  TRUE;

	 return  iErr;

 }
