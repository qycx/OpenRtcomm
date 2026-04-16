

#include	"stdafx.h"
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#include	"qmcCmdProc.h"

#include	"qySqlFunc.h"
#include	"qmcCfg.h"


//
//  2015/10/20
 int  doPostEnc_audio(  void  *  pQDC_OBJ_INFO,  char  *  pInput,  unsigned  int  inputSize,  int  iSampleTimeInMs,  unsigned  int  uiPts,  void  *  pBuf_pkt  )
 {
	 int	iErr	=	-1;
	 QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();
	 if  (  !pQyMc  )  {
		 return  -1;
	 }
	 MC_VAR_common  *  pProcInfo  =	(MC_VAR_common*)pQyMc->get_pProcInfo(  );  //  QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  {
		 return  -1;
	 }
	 QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	 if  (  !pQmcCfg  )  return  -1;
	 //
	 QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pQDC_OBJ_INFO;
	 if  (  !pQdcObjInfo  )  return  -1;
	 CAP_procInfo_audioCommon  *  pCapProcInfo  =  (  CAP_procInfo_audioCommon  *  )pQdcObjInfo->cfg.a.pParent_transform;

	 myPLAY_AUDIO_DATA	*	pPkt	=	(  myPLAY_AUDIO_DATA  *  )pBuf_pkt;
	 BOOL  bMsgGot  =  FALSE;


	 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapProcInfo->iIndex_sharedObj  );
	 if  (  !pSharedObj  )  goto  errLabel;


#if  0
	 unsigned  int  size  =  sizeof(  pPkt[0]  );
	if  (  qGetMsg(  (  GENERIC_Q  *  )pQdcObjInfo->cfg.a.pTmpDataQ,  pPkt,  &size  )  )  {
		showInfo_open0(  0,  0,  _T(  "doPostEnc_mediaSdk failed, qGetMsg failed"  )  );
		goto  errLabel;
	}
	bMsgGot  =  TRUE;
#endif

	//  注意：这个初始化非常重要，涉及压缩数据有效性					
	TRANSFER_AUDIO_DATA  *  pReq  =  pCapProcInfo->compressAudio.pReqCache;	//  (  TRANSFER_AUDIO_DATA  *  )(  pPkt->memory.m_pBuf  +  pPkt->uiSize_dec  );		
	if  (  !pReq  )  {
		goto  errLabel;
	}
	memset(  pReq,  0,  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  );


	//	
	SHARED_OBJ_USR	*	pSharedObjUsr	=	getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );		
	if  (  !pSharedObjUsr  )  {
		#ifdef  __DEBUG__
							   traceLog((TCHAR*)  _T(  "mcThread_toShareBmp: pSharedObjUsr is null"  )  );
		#endif
		goto  errLabel;				   
	}


	//
	//  2016/12/10	
	 QY_Q2  *  p_realTimeMediaQ2  =  pProcInfo->get_realTimeMediaQ2(  );
	 if  (  !p_realTimeMediaQ2  )  goto  errLabel;
#if  0
	 BOOL  bQWarning  =  isQ2Warning(  p_realTimeMediaQ2,  pCfg->envVar.usQNodes_warningInterval_rtMediaQ  );
	 if  (  bQWarning  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo1->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning:  realTimeMediaQ too many nodes. audio data will be lossed"  )  );					
#endif
	 
	//
	 if  (  !pProcInfo->bAudioChannelReady(  )  )  {
		 static  DWORD	sdwTickCnt_applyForChkChannels	=	0;
		 //  QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pRecordSoundProcInfo->iIndex_sharedObj  );
	
		 //
		 if  (  pSharedObj
			 //&&  !pSharedObjUsr->ucbNotSendData
				//&&  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id
				//	  ||  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  
					  )
		 {
			 MIS_CNT							*	pMisCnt		=	NULL;
			 MIS_MSG_applyForChkChannels_qmc		msg_applyForChkChannels;
			 int	dwTickCnt;						dwTickCnt  =  GetTickCount(  );
			 int									i;
			 CQyQ2Help								q2Help;

			 if  (  dwTickCnt  -  sdwTickCnt_applyForChkChannels  >  4000  )  {
				 //for  (  i  =  0;  i  <  mycountof(  pProcInfo1->misCnts  );  i  ++  )  
				 for  (  i  =  0;  i  <  pProcInfo->get_ucCnt_misCnts(  );  i  ++  )  
				 {
					  pMisCnt  =  (  MIS_CNT  *  )pProcInfo->getMisCntByIndex(  i  );//&pProcInfo1->misCnts[i];				
					  if  (  !pMisCnt  )  continue;
					  if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;

					  traceLogA(  (char*)  "toShareAudio: applyForChkChannels"  );
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)"",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "toShareAudio: rtMedia Channel not Ready, applyForChkChannels"  )  );

					  //
					  memset(  &msg_applyForChkChannels,  0,  sizeof(  msg_applyForChkChannels  )  );
					  msg_applyForChkChannels.uiType  =  CONST_misMsgType_applyForChkChannels_qmc;
					  msg_applyForChkChannels.pMisCnt  =  pMisCnt;
					  //
					  //  qPostMsgAndTrigger(  &msg_applyForChkChannels,  sizeof(  msg_applyForChkChannels  ),  &pProcInfo1->realTimeMediaQ  );
					  q2Help.qPostMsgAndTrigger(  &msg_applyForChkChannels,  sizeof(  msg_applyForChkChannels  ),  p_realTimeMediaQ2,  _T(  "doPostEnc_audio"  ));
				 }
				 sdwTickCnt_applyForChkChannels  =  dwTickCnt;
			 }
		 }

		 iErr  =  0;  goto  errLabel;
	 }






	//
	BOOL  bInited_pReq =   FALSE;
	int  myuiSampleTimeInMs  =  0;
	unsigned  int  myuiPts  =  0;	//  2015/01/15
	//int  usIndex_activeMems_from  =  0;


					   if  (  !bInited_pReq  )  {
						   if  (  pReq  )  {
							   //  memset(  pReq,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
							   pReq->uiType  =  CONST_imCommType_transferAudioData;
							   //  pReq->uiTranNo_openAvDev  =  pCompressVideo->uiTranNo_openAvDev;
							   pReq->uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_a;			//  2010/09/04
							   //
						   }
						   //
						   bInited_pReq  =  TRUE;
					   }

					   if  (  sizeof(  pReq->buf  )  <=  pReq->uiLen  )  {
						   traceLogA(  (char*)  "toShareBmp failed: sizeof(  pReq->buf  ) %d  <=  pReq->len %d",  sizeof(  pReq->buf  ),  pReq->uiLen  );
						   goto  errLabel;
					   }

					   //  int  tmpiRet  =  pModule->compress.pf_qdcGetOutputByIndex(  &pCompressVideo->u.custom,  index_output,  (  BYTE  *  )pReq->buf  +  pReq->uiLen,  &pReq->mems[pReq->usCnt].uiLen,  NULL,  NULL  );
					   if  (  sizeof(  pReq->buf  )  -  pReq->uiLen  <  inputSize  )  {
						   showInfo_open0(  0,  0,  _T(  "doPostEnc_mediaSdk failed, buf too small"  )  );
						   goto  errLabel;
					   }
					   memcpy(  pReq->buf  +  pReq->uiLen,  pInput,  inputSize  );
					   pReq->mems[pReq->usCnt].uiLen  =  inputSize;

					   #ifdef  __DEBUG__
							   //
						#endif

						
						//  2014/04/22
						#if  0						
							   int  nIntervalInMs  =  40;
							   #if  0
							   if  (  pCapProcInfo->compressVideo.compressor.common.usMaxFps_toShareBmp  )  {						
								   nIntervalInMs  =  1000  /  pCapProcInfo->compressVideo.compressor.common.usMaxFps_toShareBmp;							   
							   }
							   #endif
							   unsigned  short  usFps  =  min(  pCapProcInfo->compressVideo.input.usFps,  pCapProcInfo->compressVideo.compressor.common.usMaxFps_toShareBmp  );
							   if  (  !usFps  ||  abs(  usFps  -  pCapProcInfo->compressVideo.compressor.common.usMaxFps_toShareBmp  )  <  3  )  {
								   usFps  =  pCapProcInfo->compressVideo.compressor.common.usMaxFps_toShareBmp;
							   }
							   if  (  usFps  )  {
								   nIntervalInMs  =  1000  /  usFps;
							   }
							   //
							   int  iNextIndex_preEnc  =  pCapProcInfo->compressVideo.encInfo.iNextIndex_preEnc;
							   int  iLastIndex_preEnc  =  0;
							   if  (  !iNextIndex_preEnc  )  iLastIndex_preEnc  =  mycountof(  pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  )  -  1;
							   else  iLastIndex_preEnc  =  iNextIndex_preEnc  -  1;
							   //
							   if  (  pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc  >=  mycountof(  pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  )  )  {
								   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doPostEnc failed: iIndex_postEnc too big"  )  );
								   goto  errLabel;
							   }
							   //
							   int  iDiff_index  =  mycountof(  pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  )  +  iNextIndex_preEnc  -  pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc;
							   iDiff_index  =  iDiff_index  %  mycountof(  pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  );
							   int  max_iDiff_index  =  10;
							   if  (  iDiff_index  >  max_iDiff_index  )  {
								   pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc  =  mycountof(  pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  )  +  iNextIndex_preEnc  -  6;
								   pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc  =  pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc  %  mycountof(  pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  );
								   //
								   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doPostEnc: iDiff_index %d, adjusted: ind_preEnc %d, ind_postEnc %d"  ),  iDiff_index,  iNextIndex_preEnc,  pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc  );
							   }
							   //
							   iSampleTimeInMs  =  pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array[pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc];

							   //
							   if  (  !pCapProcInfo->compressVideo.ucbUseEvt  )  {
								   //  2015/01/15
								   BOOL  bNeedPts  =  TRUE;
								   //
								   #if  0  //  2015/09/10. vp8也用pts
										if  (  pCapProcInfo->compressVideo.compressor.common.ucCompressors  ==  CONST_videoCompressors_vp8  )  bNeedPts  =  FALSE;
								   #endif

								   //
								   if  (  bNeedPts  )  {
									   myuiPts  =  pCapProcInfo->compressVideo.encInfo.cnt_postEnc;
								   }
								   }
							   else  {  //  2015/10/20
								     myuiPts  =  uiPts;
							   }

							   //
							   if  (  pQmcCfg->debugStatusInfo.ucbShowEncVStatus  )  {
								   int  uiCapType  =  0;
								   BOOL  bShow  =  TRUE;

								   #ifdef  __DEBUG__	//  2014/12/01
										   //uiCapType  =  CONST_capType_mosaic;
								   #endif

								   if  (  uiCapType  )  {
									   if  (  uiCapType  !=  pCapProcInfo->compressVideo.compressor.common.uiCapType  )  bShow  =  FALSE;
								   }

								   if  (  bShow  )  {
									   int  st_preEnc  =  pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array[iLastIndex_preEnc];
									   TCHAR	tBuf[256]  =  _T(  ""  );
									   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "st_po %dms. d_po %dms. st_new %dms, d_new_po %dms. i_new %d, i_po %d. encSize %d. pts %d"  ),  
										   iSampleTimeInMs,  iSampleTimeInMs -  pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_postEnc,  
										   st_preEnc,  st_preEnc  -  iSampleTimeInMs,  
										   iLastIndex_preEnc,  pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc,  
										   inputSize,  myuiPts  );
									   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  "postEnc:"  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
								   }
							   }
							   pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_postEnc  =  iSampleTimeInMs;
							   pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc  ++  ;
							   if  (  pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc  >=  mycountof(  pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  )  )  {
								   pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc  =  pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc  %  mycountof(  pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  );
							   }
							   pCapProcInfo->compressVideo.encInfo.cnt_postEnc  ++  ;
					   #endif
					   //	
					   //  2016/12/15
					   if  (  !iSampleTimeInMs  )  {
#if 0
						   int  timeLenInMs  =  pCapProcInfo->compressAudio.encInfo.st.uiTimeLen_preEnc;
						   if  (  timeLenInMs  )  {			
							   //			
							   if  (  !pCapProcInfo->compressAudio.encInfo.st.lastEnd_iSampleTimeInMs_postEnc  )  pCapProcInfo->compressAudio.encInfo.st.lastEnd_iSampleTimeInMs_postEnc  =  pCapProcInfo->compressAudio.encInfo.st.last_iSampleTimeInMs_preEnc;
							   
							   //
							   int  iSampleTimeInMs_calc  =  0;			
							   //			
							   int  iDiffInMs  =  pCapProcInfo->compressAudio.encInfo.st.last_iSampleTimeInMs_preEnc  -  pCapProcInfo->compressAudio.encInfo.st.lastEnd_iSampleTimeInMs_postEnc;
							   if  (  abs(  iDiffInMs  )  >  300  )  {				
								   iSampleTimeInMs_calc  =  (  pCapProcInfo->compressAudio.encInfo.st.lastEnd_iSampleTimeInMs_postEnc  +  pCapProcInfo->compressAudio.encInfo.st.last_iSampleTimeInMs_preEnc  )  /  2;			
							   }			
							   else  iSampleTimeInMs_calc  =  pCapProcInfo->compressAudio.encInfo.st.lastEnd_iSampleTimeInMs_postEnc;							
							   //			
							   unsigned int  uiSampleTimeInMs_end_calc  =  iSampleTimeInMs_calc  +  timeLenInMs;			
							   pCapProcInfo->compressAudio.encInfo.st.lastEnd_iSampleTimeInMs_postEnc  =  uiSampleTimeInMs_end_calc;
							   //
							   iSampleTimeInMs  =  iSampleTimeInMs_calc;
							   //
						   }
#endif
					   }
					   #ifdef  __DEBUG__
									   #if  10
											 TCHAR  tBuf[128];
											 static int  last_st  =  0;
											 int  iDiffInMs;
											 iDiffInMs  =  iSampleTimeInMs  -  last_st;  last_st  =  iSampleTimeInMs;
											_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doPostEnc_audio: st %dms, diff %dms"  ),  iSampleTimeInMs,  iDiffInMs  );
											showInfo_open0(  0,  0,  tBuf  );
									   #endif
					   #endif
	

					   //  2008/11/12, 
					   if  (  iSampleTimeInMs  )  {
						   //  pReq->mems[0].uiSampleTimeInMs  =  iSampleTimeInMs;				  
						   pReq->mems[pReq->usCnt].uiSampleTimeInMs  =  myuiSampleTimeInMs  =  iSampleTimeInMs  -  pSharedObj->iDiffInMs_tStartAudio;	//  2009/05/26
						   //pReq->mems[pReq->usCnt].uiSampleTimeInMs_org  =  iSampleTimeInMs;									//  2009/05/27
					   }
					   //  2015/01/15
					   pReq->mems[pReq->usCnt].uiPts  =  myuiPts;
					   //
#if  0
					   if  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {
						   //pReq->mems[pReq->usCnt].usIndex_ii  =  
							   usIndex_activeMems_from  =  pSharedObjUsr->iIndex_activeMems_from_videoConferenceStarter; 
					   }
#endif
					   //
					   pReq->uiLen  +=  pReq->mems[pReq->usCnt].uiLen;
					   pReq->usCnt  ++  ;


					   //
					   DWORD  dwTickCnt;
					   int  i;
					   COMPRESS_AUDIO  *  pCompressAudio  =  &pCapProcInfo->compressAudio;
					   unsigned  char  ucbNeedShowFrameInfo  =  FALSE;


					   //////////////////////////////////		 
					   //  2010/09/12				  
		 if  (  !pReq->usCnt  )  {	
			 //  traceLog((TCHAR*)  _T(  "toShareAudio failed: req.usCnt is 0"  )  );
			 goto  errLabel;
		 }
		 //  2015/09/10
		 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {										
			  unsigned  int  myuiPts  =  0;	//  2015/01/15
			  //								
			  BOOL  bNeedPts  =  TRUE;				
			  if  (  bNeedPts  )  {								   
				  myuiPts  =  pCompressAudio->encInfo.cnt_postEnc;							   								
			  }							
			  //				
			  pCompressAudio->encInfo.cnt_postEnc  ++  ;				
			  //								
			  pReq->mems[i].uiPts  =  myuiPts;							
		 }

		 //
		 MACRO_prepareForTran(  );
		 unsigned  char				ucFlg						=	CONST_commFlg_routeTalkData;	//  0;
	 	 int						lenInBytes					=	0;
		 //
		 unsigned  int				uiChannelType				=	CONST_channelType_realTimeMedia;	
		 //
#if  1  //def  __DEBUG__
		 MIS_MSGU  *  pMsgBuf  =  NULL;		//  2016/12/10. 要在压缩初始化时分配，在停止时释放。否则速度有影响。
#endif

		 //  2010/09/12
		 pCompressAudio->usCnt_pkts  ++  ;
		 if  (  ucbNeedShowFrameInfo  )  {
			 ucFlg  |=  CONST_commFlg_routeTalkData;
			 if  (  pCompressAudio->tRecvTime_resp_fromCli  >=  pCompressAudio->tFirstTime_showFrameInfo_withoutResp  )  {	//  ÕâÊÇÎªÁË³¬Ê±
				 pCompressAudio->tFirstTime_showFrameInfo_withoutResp  =  tStartTran;							  
			 }
			 pReq->tLastTime_showFrameInfo_020534  =  pCompressAudio->tLastTime_showFrameInfo;								//  ÉèÖÃ±ê¼Ç						
			 pReq->usCnt_pkts  =  pCompressAudio->usCnt_pkts;
			 //
			 pCompressAudio->tLastTime_showFrameInfo  =  tStartTran;												
			 pCompressAudio->usCnt_pkts  =  0;
			 //
			 //  qyShowInfo1(  CONST_qyShowType_debug,  0,  "",  pProcInfo1->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tn %d, %d bytes audio data. %s"  ),  uiTranNo,  dwBytesRecorded,  ucbNeedShowFrameInfo  ?  _T(  "º¬ÒôÆµÈ¡ÑùÐÅÏ¢"  )  :  _T(  ""  )  );					
		 }


		 #ifdef  __DEBUG__
				 if  (  pQmcCfg->debugStatusInfo.ucbPrint_a_out  )  {				
					 traceLogA(  (char*)  "toShareAudio: tn %d, req.usCnt %d, len %d, mems[0].uiSampleTimeInMs %d, iSampleTimeInMs %d",  uiTranNo,  pReq->usCnt,  pReq->uiLen,  pReq->mems[0].uiSampleTimeInMs,  iSampleTimeInMs  );
					 //  qyShowInfo1(  CONST_qyShowType_debug,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "will send tn [%d]"  ),  uiTranNo  );
				 }
		 #endif

		 //  
		 lenInBytes  =  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  +  pReq->uiLen;
		 //			
		 //BOOL					bHaveMsgrs_sendLocalAv		=	FALSE;
		 //  QY_SHARED_OBJ		*	pSharedObj					=	NULL;	
		 MIS_CNT			*	pMisCnt						=	NULL;		

		 //  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pRecordSoundProcInfo->iIndex_sharedObj  );
		 if  (  pSharedObj  )  {

			 int  iIndex_misCnt  =  0;  //  pSharedObj->curRoute_sendLocalAv.iIndex_misCnt
			 pMisCnt  =  (  MIS_CNT  *  )pProcInfo->getMisCntByIndex(  iIndex_misCnt    );
			 if  (  pMisCnt  &&  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {
											   
				
				 //							   
				 #ifdef  __DEBUG__
						 //  testÎªÁË²âÊÔ
						 //  if  (  (  uiTranNo  %  30  )  )  break;
				 #endif
				
				 //if  (  !pSharedObjUsr->ucbNotSendData  )  
				 {

#if 1
					 showInfo_open0(  0,  0,  _T(  "doPostEnc_audio failed, not finished"  )  );
					 goto  errLabel;
#else
					 pSharedObj->curRoute_sendLocalAv.route.debugInfo.dwTickCnt_me_start  =  GetTickCount(  );
					 if  (  ucbNeedShowFrameInfo  )  {	//  2008/05/16									 
						 time_t		tNow;	mytime(  &tNow  );	pSharedObj->curRoute_sendLocalAv.route.debugInfo.tTime_start  =  tNow;
					 }

					 if  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {	//  
						 #if  0
							 if  (  postMsg2Mgr_mc(  pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route,  CONST_misMsgType_task,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  (  char  *  )pReq,  lenInBytes,  &pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to,  0,  uiChannelType,  pMsgBuf,  FALSE  )  )  {
								 traceLogA(  (char*)  "CQyRecordSound::OnSoundData: postMsg2Mgr_mc to videoConference failed"  );		//  
							 }
						 #else		//  2011/01/30
							 if  (  postMsg2MgrFunc_mc(  pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route,  CONST_misMsgType_outputTask_toMix,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  pSharedObjUsr->iTaskId,  0,  (  char  *  )pReq,  lenInBytes,  &pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to,  NULL,  NULL,  0,  uiChannelType,  pMsgBuf,  FALSE  )  )  {
								 traceLogA(  (char*)  "CQyRecordSound::OnSoundData: postMsg2MgrFunc_mc to videoConference failed"  );		//  
							 }
						 #endif
						 }
					 else  {
						   if  (  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  {
							   #if  0
									if  (  postMsg2Mgr_mc(  pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route,  CONST_misMsgType_outputTask,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  (  char  *  )pReq,  lenInBytes,  0,  0,  uiChannelType,  pMsgBuf,  FALSE  )  )  {
										traceLogA(  (char*)  "CQyRecordSound::OnSoundData: postMsg2Mgr_mc failed"  );		//  
									}
							   #else	//  2011/01/27
									if  (  postMsg2MgrFunc_mc(  pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route,  CONST_misMsgType_outputTask_toMix,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  pSharedObjUsr->iTaskId,  0,  (  char  *  )pReq,  lenInBytes,  0,  NULL,  NULL,  0,  uiChannelType,  pMsgBuf,  FALSE  )  )  {
										traceLogA(  (char*)  "CQyRecordSound::OnSoundData: postMsg2MgrFunc_mc failed"  );		//  
									}
							   #endif
						   }
					 }
#endif
				 }
				 #ifdef  __DEBUG__
						 //if  (  pSharedObjUsr->ucbNotSendData  )  
						 {					
							 //  traceLogA(  (char*)  "toShareAudio: not send data"  );
						 }
				 #endif

				 //
				 //if  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  ||  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  bHaveMsgrs_sendLocalAv  =  TRUE;

			 }
		 }





	iErr  =  0;
errLabel:

	if  (  bMsgGot  )  {
		pQdcObjInfo->cfg.a.pf_clean_myPLAY_AUDIO_DATA(  pPkt,  _T(  ""  )  );
	}

 return  iErr;
 }



