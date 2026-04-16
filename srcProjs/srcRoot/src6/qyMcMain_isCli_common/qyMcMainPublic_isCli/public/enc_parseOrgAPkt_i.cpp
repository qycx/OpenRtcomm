

#include	"stdafx.h"
#include	<stddef.h>
#include	<time.h>

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
__declspec(  dllexport  )  int  enc_parseOrgAPkt_i(  unsigned  int  uiTransformType,  void  *  pParent_transform,  void  *  pPkt_myPLAY_AUDIO_DATA,  long  *  p_old_lPktId_getNewPkt,  unsigned  char  **  ppInput,  unsigned  int  *puiSize,  BOOL  *  pbNeed_forceKeyFrame  )
{
	int					iErr	=	-1;
	QY_MC		*		pQyMc	=	QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	MC_VAR_common  *		pProcInfo  =  (MC_VAR_common*)pQyMc->get_pProcInfo(  );//QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	//
	BOOL				bNeed_forceKeyFrame  =  FALSE;


	//  myDRAW_VIDEO_DATA  *  pPkt  =  pTransform->video.pCurPkt;
	myPLAY_AUDIO_DATA  *  pPkt  =  (  myPLAY_AUDIO_DATA  *  )pPkt_myPLAY_AUDIO_DATA;
			
	//  检查一下。每个包都只能处理一次，否则，容易死循环
	if  (  !p_old_lPktId_getNewPkt  )  return  -1;
	if  (  !pPkt->lPktId_getNewPkt  )  {
		showInfo_open0(  0,  0,  _T(  "enc_parseOrgAPkt_i failed: lPktId_alloc 0"  )  );
		return  -1;
	}
	if  (  pPkt->lPktId_getNewPkt  ==  *p_old_lPktId_getNewPkt  )  {
		showInfo_open0(  0,  0,  _T(  "enc_parseOrgAPkt_i failed: lPkdId_alloc==old"  )  );
		return  -1;			  
	}
	*p_old_lPktId_getNewPkt  =  pPkt->lPktId_getNewPkt;
	

#if  1
		//  2014/04/22
		if  (  uiTransformType  ==  CONST_uiTransformType_encAudio  )  {
			CAP_procInfo_audioCommon  *  pCapAudio  =  (  CAP_procInfo_audioCommon  *  )pParent_transform;
			#if 0
			#ifdef  __DEBUG__
					int  iNextIndex_preEnc  =  pCapAudio->compressAudio.encInfo.iNextIndex_preEnc;
					int  iLastIndex_preEnc  =  0;
					if  (  !iNextIndex_preEnc  )  iLastIndex_preEnc  =  mycountof(  pCapBmp->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  )  -  1;
					else  iLastIndex_preEnc  =  iNextIndex_preEnc  -  1;
					//
					//traceLog(  _T(  "enc_parseOrgVPkt_i: pkt.sm %dms. iDiff %dms"  ),  pPkt->head.uiSampleTimeInMs,  pPkt->head.uiSampleTimeInMs  -  pCapBmp->compressVideo.encInfo.iSampleTimeInMs_preEnc_array[iLastIndex_preEnc]  );
			#endif
			if  (  pCapBmp->compressVideo.encInfo.iNextIndex_preEnc  >=  mycountof(  pCapBmp->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  )  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "enc_parseOrgVPkt_i failed, iNextIndex_preEnc too large"  )  );
				goto  errLabel;
			}
			pCapBmp->compressVideo.encInfo.iSampleTimeInMs_preEnc_array[pCapBmp->compressVideo.encInfo.iNextIndex_preEnc]  =  pPkt->head.uiSampleTimeInMs;
			pCapBmp->compressVideo.encInfo.iNextIndex_preEnc  ++  ;
			if  (  pCapBmp->compressVideo.encInfo.iNextIndex_preEnc  >=  mycountof(  pCapBmp->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  )  )  {
				pCapBmp->compressVideo.encInfo.iNextIndex_preEnc  =  pCapBmp->compressVideo.encInfo.iNextIndex_preEnc  %  mycountof(  pCapBmp->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  );
			}
			pCapBmp->compressVideo.encInfo.cnt_preEnc  ++  ;

			#endif
			//
			//
			//  2016/12/15		
			int  nAvgBytesPerSec  =  pCapAudio->compressAudio.ah_decompress.wfx.nAvgBytesPerSec;
			if  (  nAvgBytesPerSec  )  {
#if 0
				pCapAudio->compressAudio.encInfo.st.last_iSampleTimeInMs_preEnc  =  pPkt->head.uiSampleTimeInMs;
				long  long  llValInMs  =  pPkt->uiSize_dec  *  1000;
				pCapAudio->compressAudio.encInfo.st.uiTimeLen_preEnc  =  llValInMs  /  nAvgBytesPerSec;
#endif
			}

		}
#endif


#if  10		
		 
		 //		
		 if  (  pPkt->head.uiLen  >  pPkt->memory.uiBufSize  
			 //||  pPkt->uiSize_dec  +  pPkt->uiOffset_enc  +  pPkt->uiLen_enc  >  pPkt->head.uiLen  
			 )  			 
		 {
				#ifdef  __DEBUG__
						 traceLog(  _T(  "doDecVideo: uiSize_dec or uiLen error"  )  );
				#endif
				showInfo_open0(  0,  0,  _T(  "doDecVideo: uiSize_dec or uiLen error"  )  );
				return  -1;		 			 
		 }		 
		 char	*	decData	=  pPkt->memory.m_pBuf;	//    +  pPkt->uiSize_dec  +  pPkt->uiOffset_enc;
		 myPLAY_AUDIO_DATA	*	pPkt_dec  =  pPkt;

		 //
		 //int  index_pMems_from  =  pPkt->decInfo.index_pMems_from;	


#endif

		 //
		 *ppInput  =  (  unsigned  char  *  )decData;
		 *puiSize  =  pPkt->uiSize_dec;	//  head.uiLen;


		 iErr  =  0;
errLabel:

		 //  2014/08/25
		 if  (  pbNeed_forceKeyFrame  )  {
			 *pbNeed_forceKeyFrame  =  bNeed_forceKeyFrame;
		 }

	return  iErr;
}



// int  enc_parseOrgVPkt_i(  unsigned  int  uiTransformType,  void  *  pParent_transform,  void  *  pPkt_myDRAW_VIDEO_DATA,  long  *  p_old_lPktId_alloc,  unsigned  char  **  ppInput,  unsigned  int  *puiSize  )
__declspec(  dllexport  )   int  enc_parseOrgVPkt_i(  unsigned  int  uiTransformType,  void  *  pParent_transform,  void  *  pPkt_myDRAW_VIDEO_DATA,  long  *  p_old_lPktId_alloc,  unsigned  char  **  ppInput,  unsigned  int  *puiSize,  BOOL  *  pbNeed_forceKeyFrame  )
{
	int					iErr	=	-1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	MC_VAR_common  *		pProcInfo  =  (MC_VAR_common*)pQyMc->get_pProcInfo(  );  //  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	//
	BOOL				bNeed_forceKeyFrame  =  FALSE;
	//
	TCHAR  tBuf[128]  =  _T(  ""  );
	
	//  
	myDRAW_VIDEO_DATA  *  pPkt  =  (  myDRAW_VIDEO_DATA  *  )pPkt_myDRAW_VIDEO_DATA;
	
	//
#ifdef  __DEBUG__
		#if  0
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "enc_parseOrgVPkt_i failed: lPkdId_alloc==old %d"  ),  pPkt->lPktId_alloc  );
			 traceLog(  _T(  "%s"  ),  tBuf  );
		#endif
#endif

	//  检查一下。每个包都只能处理一次，否则，容易死循环
	if  (  !p_old_lPktId_alloc  )  return  -1;
	if  (  !pPkt->lPktId_alloc  )  {
		showInfo_open0(  0,  0,  _T(  "enc_parseOrgVPkt_i failed: lPktId_alloc 0"  )  );
		return  -1;
	}
	if  (  pPkt->lPktId_alloc  ==  *p_old_lPktId_alloc  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "enc_parseOrgVPkt_i failed: lPkdId_alloc==old %d"  ),  pPkt->lPktId_alloc  );
		showInfo_open0(  0,  0,  tBuf  );
		return  -1;			  
	}
	*p_old_lPktId_alloc  =  pPkt->lPktId_alloc;
	

#if  1
		//  2014/04/22
		if  (  uiTransformType  ==  CONST_uiTransformType_encVideo  )  {
			CAP_procInfo_bmpCommon  *  pCapBmp  =  (  CAP_procInfo_bmpCommon  *  )pParent_transform;
			//
			#ifdef  __DEBUG__
			#endif
			//
#if  0
			if  (  pCapBmp->compressVideo.encInfo.iNextIndex_preEnc  >=  mycountof(  pCapBmp->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  )  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "enc_parseOrgVPkt_i failed, iNextIndex_preEnc too large"  )  );
				goto  errLabel;
			}
			pCapBmp->compressVideo.encInfo.iSampleTimeInMs_preEnc_array[pCapBmp->compressVideo.encInfo.iNextIndex_preEnc]  =  pPkt->head.uiSampleTimeInMs;
			pCapBmp->compressVideo.encInfo.iNextIndex_preEnc  ++  ;
			if  (  pCapBmp->compressVideo.encInfo.iNextIndex_preEnc  >=  mycountof(  pCapBmp->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  )  )  {
				pCapBmp->compressVideo.encInfo.iNextIndex_preEnc  =  pCapBmp->compressVideo.encInfo.iNextIndex_preEnc  %  mycountof(  pCapBmp->compressVideo.encInfo.iSampleTimeInMs_preEnc_array  );
			}
#endif
			int  arraySize = mycountof(pCapBmp->compressVideo.encInfo.iSampleTimeInMs_preEnc_array);
			int  iNextIndex_preEnc = pCapBmp->compressVideo.encInfo.cnt_preEnc % arraySize;
			pCapBmp->compressVideo.encInfo.iSampleTimeInMs_preEnc_array[iNextIndex_preEnc] = pPkt->head.uiSampleTimeInMs;
			pCapBmp->compressVideo.encInfo.cnt_preEnc  ++  ;

			//
#define		CONST_timeInMs_forceKeyFrame	1800	//  2015/10/04	//  4000  
			if  (  pCapBmp->compressVideo.encInfo.dwTickCnt_startToForceKeyFrame  )  {
				DWORD  dwTickCnt  =  GetTickCount(  );
				if  (  dwTickCnt  -  pCapBmp->compressVideo.encInfo.dwTickCnt_startToForceKeyFrame  <  CONST_timeInMs_forceKeyFrame  )  {
					bNeed_forceKeyFrame  =  TRUE;
					//
					#ifdef  __DEBUG__
							//showInfo_open0(  0,  0,  _T(  "enc_parseOrgVPkt_i: bNeed_forceKeyFrame true"  )  );
					#endif
				}
			}
		}
#endif

#if  10		
		 
		 //		
		 if  (  pPkt->head.uiLen  >  pPkt->memory.uiBufSize  
			 ||  pPkt->uiSize_dec  +  pPkt->uiOffset_enc  +  pPkt->uiLen_enc  >  pPkt->head.uiLen  )  			 
		 {
				#ifdef  __DEBUG__
						 traceLog(  _T(  "enc_parseOrgVPkt_i failed: uiSize_dec or uiLen error"  )  );
				#endif
				showInfo_open0(  0,  0,  _T(  "enc_parseOrgVPkt_i failed: uiSize_dec or uiLen error"  )  );
				return  -1;		 			 
		 }
		 //  2015/10/29
		 if  (  pPkt->usPktResType  !=  CONST_pktResType_sharedTex  )  {
			 //
			 #ifdef  __DEBUG__
					 char  buf[128];
					 iFourcc2Str(  pPkt->bih.biCompression,  buf,  mycountof(  buf  )  );
			 #endif
			 //
			 switch  (  pPkt->bih.biCompression  )  {
					 case  BI_RGB:
					 case  CONST_fourcc_I420:
					 case  CONST_fourcc_YV12:
						   break;
					 default:  {
							 
							char  buf[128];					 							
							iFourcc2Str(  pPkt->bih.biCompression,  buf,  mycountof(  buf  )  );							   
							_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "enc_parseOrgVPkt_i failed, unsupported bih.biCompression %S"  ),  buf  );							  
							showInfo_open0(  0,  0,  tBuf  );
							}
						    return  -1;
							break;
			 }

			 //
			 if  (  pPkt->bih.biSizeImage  >  pPkt->uiSize_dec  )  {
				 showInfo_open0(  0,  0,  _T(  "enc_parseOrgVPkt_i failed, bih.sizeImg > size_dec"  )  );
				 return  -1;
			 }
		 }
		 //
		 char	*	decData	=  pPkt->memory.m_pBuf;	//    +  pPkt->uiSize_dec  +  pPkt->uiOffset_enc;
		 myDRAW_VIDEO_DATA	*	pPkt_dec  =  pPkt;

		 //
		 int  index_pMems_from  =  pPkt->decInfo.index_pMems_from;	


#endif

		 //
		 *ppInput  =  (  unsigned  char  *  )decData;
		 *puiSize  =  pPkt->bih.biSizeImage;


		 iErr  =  0;
errLabel:

		 //  2014/08/25
		 if  (  pbNeed_forceKeyFrame  )  {
			 *pbNeed_forceKeyFrame  =  bNeed_forceKeyFrame;
		 }

	return  iErr;
}



//

//  2016/12/16
__declspec(  dllexport  )  int  tmp_playLocalAudioData(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int  iErr  =  -1;

		if  (  pQdcObjInfo->cfg.a.uiTransformType_pParent  ==  CONST_uiTransformType_encAudio  )  {
			CAP_procInfo_audioCommon  *  pCapAudio  =  (  CAP_procInfo_audioCommon  *  )pQdcObjInfo->cfg.a.pParent_transform;
				QY_MC		*		pQyMc	=	QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	MC_VAR_common  *		pProcInfo  =  (MC_VAR_common*)pQyMc->get_pProcInfo(  );//QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	//
	QMC_cfg  *  pCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );

	//
	QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapAudio->iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	SHARED_OBJ_USR				*	pSharedObjUsr		=	NULL;
	pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
	if  (  !pSharedObjUsr  )  goto  errLabel;


					  BOOL  bPlayLocal  =  FALSE;
				  switch  (  pSharedObj->uiType1  )  {
						  case  CONST_sharedObjType_mediaFile:  
						  case  CONST_sharedObjType_mediaDevice:
							    bPlayLocal  =  TRUE;
								break;
						  case  CONST_sharedObjType_webcam_av:	//  2015/05/18.
							    if  (  pCfg->ucbPlayLocalAudio_captured  )  {								
									bPlayLocal  =  TRUE;
								}
								break;
						  default:
								#if  0	//  ±¾µØ²âÊÔµÄÒôÆµÔÚprocessInput_postÀïÖ±½Ó´¦ÀíÁË
								 if  (  pSharedObj->bSoundRecorder  )  {  //  ±¾µØ²¥·Å
									 if  (  pProcInfo->av.localAv.recordSoundProcInfo.bLocalAudioPlaying  )  { 
										 //
										 #ifdef  __DEBUG__
												 traceLog(  _T(  "%d bytes audio data"  ),  pPkt->head.uiLen  );
										 #endif			

										if  (  pProcInfo->av.localAv.player.audio.bRunning  )  {	//  if thread is active
											bPlayLocal  =  TRUE;							 
										}						 
									 }
								 }
								#endif
								 break;
				  }
				  if  (  bPlayLocal  )  {
					  //  
					  pProcInfo->playLocalAudioData(  pSharedObjUsr->iTaskId,  pSharedObjUsr->uiTranNo_openAvDev_a,  &pCapAudio->compressAudio.ah_decompress.wfx,  (  myPLAY_AUDIO_DATA  *  )pQdcObjInfo->cfg.a.pCurPkt,  pQdcObjInfo->cfg.a.size_pCurPkt,  NULL,  pCapAudio->uiType,  pSharedObj->iIndex_capAudio  );  
				  }
				  //

	}

		iErr  =  0;

errLabel:
		return  iErr;

}



