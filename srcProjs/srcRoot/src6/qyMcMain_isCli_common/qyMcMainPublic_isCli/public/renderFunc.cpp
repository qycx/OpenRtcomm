
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

//#include	"isCliHelpPublic.h"
#include	"testOnly.h"
#include	"qmcCfg.h"
//#include	"qmcVideoTool.h"


//
void  postAPktToRender(  void  *  pQY_TRANSFORM,  void  *  pmyPLAY_AUDIO_DATA,  BOOL  *  unused_pbPktRedirected  )
{
	int				iErr		=	-1;
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pQY_TRANSFORM;
	myPLAY_AUDIO_DATA  *  pPkt  =  (  myPLAY_AUDIO_DATA  *  )pmyPLAY_AUDIO_DATA;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
		
	
	//
	if  (  pTransform->pCapDev_rtsp  )  {
#if  0
				  //VIDEO_capDev_rtsp				*	pRtsp							=	(  VIDEO_capDev_rtsp  *  )pTransform->pCapDev_rtsp;
				  CAP_dev_rtspCommon				*	pRtsp							=	(  CAP_dev_rtspCommon  *  )pTransform->pCapDev_rtsp;
			 
				  QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pRtsp->iIndex_sharedObj  );			 
				  if  (  !pSharedObj  )  goto  errLabel;
				  CAP_procInfo_video  *  pVc  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
				  if  (  !pVc  )  goto  errLabel;
				  TRANSINFO_stream				*	pTransInfo					=	(  TRANSINFO_stream  *  )pSharedObj->pTransInfo_stream;
				  if  (  !pTransInfo  )  goto  errLabel;
				  if  (  !pTransInfo->myTask.pTransforms  )  goto  errLabel;
			 

				  //  dec可能是异步的，所以可能没输出数据。这时候，pkt.bih没赋值，所以需要判断下. 2014/03/16					 
				  if  (  pPkt->bih.biWidth  &&  pPkt->bih.biHeight  )  {
					  //
					  if  (  pPkt->bih.biWidth  !=  pVc->vh_org.bih.biWidth  ||  pPkt->bih.biHeight  !=  pVc->vh_org.bih.biHeight  )  {
						  #ifdef  __DEBUG__
								  traceLog(  _T(  "postVPktToRender failed, pkt %dx%d != pVc.vh_org %dx%d"  ),  pPkt->bih.biWidth,  pPkt->bih.biHeight,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight  );
						  #endif
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "postVPktToRender failed, pkt %dx%d != pVc.vh_org %dx%d"  ),  pPkt->bih.biWidth,  pPkt->bih.biHeight,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight  );
						  goto  errLabel;
					  }
					  
					  //
					  if  (  pRtsp->uiType  ==  CONST_rtspType_decV  )  {
						  VIDEO_capDev_rtsp  *  pRtsp1  =  (  VIDEO_capDev_rtsp  *  )pRtsp;
						  //  2015/02/01
						  if  (  !pRtsp1->bQInited_dvt_decV  )  {
							  showInfo_open0(  0,  0,  _T(  "postVPktTotender failed: cacheQ not inited"  )  );						  
							  goto  errLabel;
						  }
						  //
						  //  2015/10/06
						  QMC_cfg  *  pCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
						  if  (  pCfg  &&  pCfg->debugStatusInfo.ucbShowRenderStatus  )  {
								  if  (  pPkt->usPktResType  ==  CONST_pktResType_sharedTex  )  {
									  TCHAR  tBuf[128];
									  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "postVPktToRender: sn %d ok"  ),  pPkt->sharedTex.pktSharedTexInfo.uiSeqNo  );
									  showInfo_open0(  0,  0,  tBuf  );
								  }
						  }
						  //
						  #ifdef  __DEBUG__  //  2015/10/06
								  //showInfo_open0(  0,  0,  _T(  "postVPktTotender: haha"  )  );			
						  #endif
						  //
						  if  (  !q2PostMsgAndTrigger(  pPkt,  1  *  sizeof(  pPkt[0]  ),  &pRtsp1->cacheQ2_dvt_decV  )  )  {												
							  bPktsRedirected  =  TRUE;																					 						  
						  }											 					  

						  }
#if  0
					  else  if  (  pRtsp->uiType  ==  CONST_rtspType_qvcf  )  {
						        //  2015/05/12
								int  i;
								i  =  99;
								drawLocalVideoData(
								}
#endif
					  else  {

						    //  2014/09/08
						    if  (  !pVc->vppThread.bQInited  )  {						  
								showInfo_open0(  0,  0,  _T(  "postVPktToRender failed: vpp.q not inited"  )  );
								goto  errLabel;				  					  
							}
							
							//
							BOOL  bNoSkip  =  FALSE;
							//
							if  (  pSharedObj->uiType  ==  CONST_sharedObjType_qvcf  )  {	//  2015/05/25. 本地播放，不需要帧速控制
								bNoSkip  =  TRUE;
							}
							//				 
							if  (  !setPktInputInfo(  pProcInfo,  &pVc->compressVideo.input,  pVc->compressVideo.usFrames_perSecond_expected,  bNoSkip,  pPkt  )  )  {														  
								//
								if  (  !q2PostMsgAndTrigger(  pPkt,  1  *  sizeof(  pPkt[0]  ),  &pVc->vppThread.q2  )  )  {					
									bPktsRedirected  =  TRUE;																					 						  
								}											 					  
							}		

					  }
				  }			 
#endif
		}		
	else  {		
		  //  
		  //  pProcInfo->drawVideoData(  pPkt,  1  *  sizeof(  pPkt[0]  ),  &bPktsRedirected,  pTransform  );		 				
		  pProcInfo->playAudioData(  pPkt->head.uiSampleTimeInMs,  pPkt->head.uiPts,  (  BYTE  *  )pPkt->memory.m_pBuf,  pPkt->uiSize_dec,  pTransform->iIndex_player  );

	}

	//
	iErr  =  0;

errLabel:
			  


			  return;

}



