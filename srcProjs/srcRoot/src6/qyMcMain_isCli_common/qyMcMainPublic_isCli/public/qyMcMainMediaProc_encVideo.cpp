

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



 








 //  2011/12/24
 int  doEncVideoPkt(  MC_VAR_common  *  pProcInfo,  QY_SHARED_OBJ  *  pSharedObj,  CAP_procInfo_bmpCommon  *  pCapBmp,  myDRAW_VIDEO_DATA  *  pPkt1  )
{
	int				iErr	=	-1;

	QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();
	//
	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;
	//
	int						tmpiRet						=	0;

	if  (  !pPkt1  )  return  -1;
	//  if  (  !pPkts  ||  !nPkts  )  return  -1;
	myDRAW_VIDEO_DATA  *  pPkts  =  pPkt1;
	unsigned  int  nPkts  =  1;

#if  0
	if  (  nPkts  !=  1  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "toShareVideo_post failed: nPkts must is 1"  )  );
		#endif
		return  -1;
	}
#endif

	COMPRESS_VIDEO  *  pCompressVideo  =  &pCapBmp->compressVideo;

	DWORD					dwCkID						=	0;
	DWORD					dwFlags						=	0;
	DWORD					lIndex						=	0;
	DWORD					dwQuality					=	pCompressVideo->u.vcm.iQuality;
	//  int						i;
	unsigned  int			uiChannelType				=	CONST_channelType_media;

	time_t					tStartTran					=	pPkts[0].input.tStartTran;			//  2011/08/30
	if  (  !tStartTran  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "doEncVideoPkt: tStartTran is 0"  )  );
		#endif
		mytime(  &tStartTran  );  
	}


	SHARED_OBJ_USR* pSharedObjUsr; pSharedObjUsr = NULL;
	if  (  !pSharedObj  )  goto  errLabel;
	pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
	if  (  !pSharedObjUsr  )  goto  errLabel;


	if  (  pCompressVideo->tLastTime_sendVideo  !=  tStartTran  )  {				//  Õâ±íÃ÷ÊÇÒ»ÃëµÄ¿ªÊ¼				

#if  0
		//  pCompressVideo->usFramesPerSecond_input  =  pCompressVideo->usFramesThisSecond_input  -  1;		//  2009/10/21
		pCompressVideo->usFps_input  =  pCompressVideo->usFramesThisSecond_input  -  nPkts;		//  2009/10/21. 
#endif

		//  2011/07/30. 这里计算发送帧速
		pCompressVideo->usFps_toSend  =  pCompressVideo->usFramesThisSecond_toSend;
		//
		DWORD	dwTickCnt;	dwTickCnt  =  GetTickCount(  );
		if  (  dwTickCnt  <  pCompressVideo->dwTickCnt_selectTime  +  500  )  pCompressVideo->fFps_sending  =  pCompressVideo->usFrames_perSecond_expected;
		else  pCompressVideo->fFps_sending  =  (  float  )(  pCompressVideo->uiCnt_pkts_fromSelect  *  1000.  /  (  dwTickCnt  -  pCompressVideo->dwTickCnt_selectTime  )  );

		#if		0
				//  traceLogA(  (char*)  "toShareBmp: usFramesPerSecond %d, expected %d",  pCompressVideo->usFramesThisSecond,  pCompressVideo->usFrames_perSecond_expected  );  
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "toShareBmp: usFramesPerSecond %d, expected %d, input %d"  ),  pCompressVideo->usFramesThisSecond,  pCompressVideo->usFrames_perSecond_expected,  pCompressVideo->usFramesPerSecond_input  );  
		#endif

		//
		pCompressVideo->tLastTime_sendVideo  =  tStartTran;				
		pCompressVideo->usFramesThisSecond_toSend  =  0;

#if  0
		//  ¶¨ÆÚÏò¿Í»§¶ËÏÂ·¢Ö¡ËÙÐÅÏ¢				
		if  (  (  int  )(  tStartTran  -  pCompressVideo->tLastTime_showFrameInfo  )  >  pProcInfo->cfg.usNeedShowFrameInfoIntervalInS  )  {			
			//
			ucbNeedShowFrameInfo  =  TRUE;
		}
#endif

		if  (  pCompressVideo->ucbFixedRate  )  {  //  ±íÃ÷Òª²ÎÓëÊÓÆµ»áÒé¡£¶ÔÊÓÆµ»áÒé£¬²ÉÓÃ¹Ì¶¨Ö¡ËÙ
				pCompressVideo->ucSeconds_perFrame_expected  =  pCompressVideo->compressor.common.ucSeconds_perFrame;	//  pProcInfo->cfg.policy.video.ucSeconds_perFrame_videoConference;
				pCompressVideo->usFrames_perSecond_expected  =  pCompressVideo->compressor.common.usMaxFps_toShareBmp;	//  pProcInfo->cfg.policy.video.usFrames_perSecond_videoConference;
			}		
		else  {
			  //  ·ÖÎöÏìÓ¦Çé¿ö
			  if  (  pCompressVideo->tFirstTime_showFrameInfo_withoutResp  )  {
					  
				  if  (  pCompressVideo->tRecvTime_resp_fromCli  <  pCompressVideo->tFirstTime_showFrameInfo_withoutResp  )  {	//  Î´ÊÕµ½µÄÇé¿öÏÂ
                        
					  if  (  tStartTran  -  pCompressVideo->tFirstTime_showFrameInfo_withoutResp  >  pCompressVideo->ucTimeoutInS_showFrameInfoResp  )  {    						//  5Ãë¶¼Ã»ÊÕµ½ÏìÓ¦µÄ
		
						  pCompressVideo->usTimes_failure  +=  (  MAX_failures_frames_perSecond  +  1  )  /  2;		//  ¶Ô³¬Ê±£¬Òª¾¡¿ì½µµÍÖ¡ËÙ¡£ÊÇÑÏÖØÎÊÌâ
								  
						  if  (  pCompressVideo->ucTimeoutInS_showFrameInfoResp  <  MAX_ucTimeoutInS_showFrameInfoResp  )  pCompressVideo->ucTimeoutInS_showFrameInfoResp  ++  ;	//  ×î´óÊÇ30,²»ÄÜ³¬ÁË
						  //
						  if  (  pCompressVideo->usFrames_perSecond_expected  ==  1  )  {
							  if  (  pCompressVideo->ucSeconds_perFrame_expected  <  MAX_ucSeconds_perFrame  )  pCompressVideo->ucSeconds_perFrame_expected  ++  ;				//  ÔÚ³¬Ê±Çé¿öÏÂ£¬ÓÃÕâ¸ö¼ä¸ôÀ´¼õÉÙÊä³ö£¬±ÜÃâÍ¨µÀ¶ÂÈû¡£																  
						  }

						  //qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Speed down, fps [%d]/s, spf [%ds]"  ),  pCompressVideo->usFrames_perSecond_expected,  pCompressVideo->ucSeconds_perFrame_expected  );
				
					  }
					  }
				  else  {														//  ÊÕµ½ÏìÓ¦µÄÇé¿ö
					    pCompressVideo->ucSeconds_perFrame_expected  =  0;		//  ÊÕµ½ÁËÁ¢¼´¼ä¸ô²ÎÊý½µÎª0						  
				  }
					  
			  }
				
			  //  µ÷Õû×´Ì¬
			  if  (  pCompressVideo->usTimes_failure  )  {
						
				  if  (  isVideoNormalState(  pCompressVideo  )  )  {
					  if  (  pCompressVideo->usTimes_failure  >  MAX_failures_frames_perSecond  )  {				//  È¡ÏûÎÈ¶¨Ì¬
						  pCompressVideo->usFps_ok  =  0;
						  pCompressVideo->bTopFrames  =  0;								  
						  //
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Try to readjust speed"  )  );
					  }
				  }
					
				  if  (  !isVideoNormalState(  pCompressVideo  )  )  {
					  BOOL	bSelect  =  FALSE;

					  if  (  pCompressVideo->usTimes_failure  >  MAX_failures_frames_perSecond  )  {
						  if  (  pCompressVideo->usFrames_perSecond_expected  >  pCompressVideo->compressor.common.usMinFps_toShareBmp /*1*/  )  {									//  ±ØÐëÒª±£³ÖÖ¡ËÙÔÚ1/SÒÔÉÏ
							  pCompressVideo->usFrames_perSecond_expected  --  ;
						  }
		
						  bSelect  =  TRUE;

						  //qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Speed down. set fps %d/s <-> actual %.2f/s"  ),  pCompressVideo->usFrames_perSecond_expected,  pCompressVideo->fFps_sending  );
					  }
					  if  (  !bSelect  )  {
						  if  (  pCompressVideo->usTimes_ok  >=  5  )  {							  
							  bSelect  =  TRUE;

							  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Try to test speed. %d/s <-> actual %.2f/s )"  ),  pCompressVideo->usFrames_perSecond_expected,  pCompressVideo->fFps_sending  );
						  }
					  }

					  if  (  bSelect  )  {
						  CQySyncObj	syncObj;
						  if  (  !syncObj.sync(  pQmcCfg->mutexName_syncSendAv,  0  )  )  {

							  pCompressVideo->tSelectTime  =  tStartTran;
							  pCompressVideo->dwTickCnt_selectTime  =  GetTickCount(  );
							  pCompressVideo->uiCnt_pkts_fromSelect  =  0;

							  pCompressVideo->usTimes_ok  =  0;
							  pCompressVideo->usTimes_failure  =  0;															//  ÐÂµÄ½µµÍÖ¡ËÙÐèÒª½«´íÎóÇå0
						  }
					  }
				  }
				  //
				  if  (  pCompressVideo->usFps_ok  ==  pCompressVideo->usFrames_perSecond_expected  )  {
					  pCompressVideo->bTopFrames  =  TRUE;															//  ±íÃ÷ÊÇ×î¸ß¿ÉÓÃèåËÙ

					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Speed is top. %d/s <-> actual %.2f/s."  ),  pCompressVideo->usFrames_perSecond_expected,  pCompressVideo->fFps_sending  );
					  }
					  //
				}
			  else  {	  //  Õý³£ÊÕµ½ÁËÏìÓ¦					  	  
				    if  (  !isVideoNormalState(  pCompressVideo  )  )  {                        
						if  (  pCompressVideo->usTimes_ok  >=  10  )  {		//  ÕâÀï£¬Ê¹ÓÃÁË10ÃëÀ´ÅÐ¶ÏÊÇ·ñÆ½ÎÈÆðÀ´¡£
							pCompressVideo->usFps_ok  =  pCompressVideo->usFrames_perSecond_expected;		//  ÕâËµÃ÷ÊÇ¿ÉÒÔÊ¹ÓÃµÄÖ¡ËÙ¡£µ«ÊÇ»¹Ã»È·¶¨ÊÇ·ñÊÇ×î¸ßµÄÆµÂÊ¡£
                           
							qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Speed is ok. input %d/s, expected %d/s, actual %.2f/s. "  ),  pCompressVideo->input_BufferCB.videoInputInfo.usFps,  pCompressVideo->usFrames_perSecond_expected,  pCompressVideo->fFps_sending  );

							if  (  !pCompressVideo->bTopFrames  )  {													//  ÊÔÍ¼ÌáÉýÖ¡ËÙ
								if  (  pCompressVideo->usFrames_perSecond_expected  >=  pCompressVideo->compressor.common.usMaxFps_toShareBmp  )  {	//  ÔÝÊ±ÏÞÖÆÔÚ30Ö¡/S
									pCompressVideo->bTopFrames  =  TRUE;
									//									  	
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Speed reaches top. expected %d/s, actual %.2f/s"  ),  pCompressVideo->usFrames_perSecond_expected,  pCompressVideo->fFps_sending  );
									}
								else  if  (  pCompressVideo->usFrames_perSecond_expected  <=  (  unsigned  short  )(  pCompressVideo->fFps_sending  +  2.5  )  )  {		//  +0.2 ÊÇµ£ÐÄ¸¡µãÊýÓÐÐ¡Êý±»ºöÂÔ¡£					
										  CQySyncObj	syncObj;
										  if  (  !syncObj.sync(  pQmcCfg->mutexName_syncSendAv,  0  )  )  {
											  pCompressVideo->usFrames_perSecond_expected  ++  ;								  							
											  pCompressVideo->tSelectTime  =  tStartTran;
											  pCompressVideo->dwTickCnt_selectTime  =  GetTickCount(  );
											  pCompressVideo->uiCnt_pkts_fromSelect  =  0;
					  
											  pCompressVideo->usTimes_ok  =  0;
											  pCompressVideo->usTimes_failure  =  0;															//  ÐÂµÄ½µµÍÖ¡ËÙÐèÒª½«´íÎóÇå0

											  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Speed up. expected %d/s, actual %.2f/s"  ),  pCompressVideo->usFrames_perSecond_expected,  pCompressVideo->fFps_sending  );
										  }
								}							  
							}						  
						}					  
					}					  				
			  }
				
			  //  if  (  !isVideoNormalState(  pCompressVideo  )  )  ucbNeedShowFrameInfo  =  TRUE;								//  ·ÇÎÈ¶¨Ì¬ÐèÒª²»Í£µÄÈ¥ÎÊ¿Í»§¶Ë¡£Ò»Ö±µ½½¨Á¢ÎÈ¶¨Ì¬ÎªÖ¹
		}																													//  ÎÈ¶¨Ì¬¿¿¶¨Ê±Æ÷¶¨ÆÚÎÊ¿Í»§¶Ë, ·ÀÖ¹ÖÐ¼ä³ö´íÁË¡£
	
		//  2008/12/05, ÔÚµÚÒ»´Î»òÕßuiCnt_pkts_fromSelectÌ«´óÊ±£¬ÒªÖØÐÂÉèÖÃÏÂ
		if  (  !pCompressVideo->tSelectTime  
			||  pCompressVideo->uiCnt_pkts_fromSelect  >  32  *  1024
			//||  pCompressVideo->tmp_bMediaChannelReady  !=  pProcInfo->bVideoChannelReady()  
			//||  pCompressVideo->tmp_ucbNotSendData  !=  pSharedObjUsr->ucbNotSendData  
			)  
		{
			CQySyncObj		syncObj;
			if  (  !syncObj.sync(  pQmcCfg->mutexName_syncSendAv,  0  )  )  {
				pCompressVideo->tSelectTime  =  tStartTran;
				pCompressVideo->dwTickCnt_selectTime  =  GetTickCount(  );
				pCompressVideo->uiCnt_pkts_fromSelect  =  0;
				pCompressVideo->fFps_sending  =  0;

				pCompressVideo->usTimes_ok  =  0;
				pCompressVideo->usTimes_failure  =  0;
		
				//pCompressVideo->tmp_bMediaChannelReady  =  pProcInfo->bVideoChannelReady();
				//pCompressVideo->tmp_ucbNotSendData  =  pSharedObjUsr->ucbNotSendData;

				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "to select %d/s"  ),  pCompressVideo->usFrames_perSecond_expected  );
			}
		}
	}

	//  2015/10/14
	QY_Q2* p_mediaQ2; p_mediaQ2 = pProcInfo->get_mediaQ2();
	if  (  !p_mediaQ2  )  goto  errLabel;
	//
#if  0
	if  (  !pProcInfo->bVideoChannelReady()  )  {
		static  DWORD	sdwTickCnt_applyForChkChannels	=	0;
		//
		if  (  !pSharedObjUsr->ucbNotSendData
			//&&  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  
			//||  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  
			)
		{
					   MIS_CNT							*	pMisCnt		=	NULL;
					   MIS_MSG_applyForChkChannels_qmc		msg_applyForChkChannels;
					   int	dwTickCnt;						dwTickCnt  =  GetTickCount(  );
					   int									i;
					   //  CQyQ2Help								q2Help;

					   if  (  dwTickCnt  -  sdwTickCnt_applyForChkChannels  >  4000  )  {
						   //for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
						   for  (  i  =  0;  i  <  pProcInfo->get_ucCnt_misCnts();  i  ++  )  
						   {
							   pMisCnt  =  (  MIS_CNT  *  )pProcInfo->getMisCntByIndex(  i  );//&pProcInfo->misCnts[i];
							   if  (  !pMisCnt  )  continue;
							   if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;

							   //  traceLogA(  (char*)  "toShareBmp: applyForChkChannels"  );
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "toShareBmp: media Channel not Ready, applyForChkChannels"  )  );

							   //
							   memset(  &msg_applyForChkChannels,  0,  sizeof(  msg_applyForChkChannels  )  );
							   msg_applyForChkChannels.uiType  =  CONST_misMsgType_applyForChkChannels_qmc;
							   msg_applyForChkChannels.pMisCnt  =  pMisCnt;
							   //
							   if  (  q2PostMsgAndTrigger(  &msg_applyForChkChannels,  sizeof(  msg_applyForChkChannels  ),  p_mediaQ2  )  )  {
								   showNotification(  0,  0,  0,  0,  0,  0,  _T(  "toShareBmp: applyForChkChannels failed"  )  );
							   }
						   }
						   sdwTickCnt_applyForChkChannels  =  dwTickCnt;
					   }
				   
		}		  
	
		//  
		iErr  =  0;  goto  errLabel;
	}
#endif

#if  0
	if  (  pSharedObjUsr->ucbNotSendData  )  {
		iErr  =  0;  goto  errLabel;
	}
#endif


	//
	unsigned  char			ucFlg; ucFlg = CONST_commFlg_routeTalkData;	//  0;
	//unsigned  short			usIndex_activeMems_from		=	0;				  
	unsigned  int			myuiSampleTimeInMs; myuiSampleTimeInMs = 0;//  2009/05/30
	int						ii;

	//  2011/12/24
	int						index_pReq; index_pReq = 0;
	BOOL					bInited_pReq; bInited_pReq = FALSE;


	//
	unsigned  char  ucSeconds_perFrame;  ucSeconds_perFrame  =  pCompressVideo->ucSeconds_perFrame_expected;	//  
	//  if  (  pProcInfo->cfg.policy.video.ucSeconds_perFrame_videoConference  )  ucSeconds_perFrame  =  pProcInfo->cfg.policy.video.ucSeconds_perFrame_videoConference;	//  2010/06/27
	//

	for  (  ii  =  0;  ii  <  nPkts;  ii  ++  )  {

		 int					iSampleTimeInMs				=	pPkts[ii].head.uiSampleTimeInMs;
		 BYTE				*	pInput						=	(  BYTE  *  )pPkts[ii].memory.m_pBuf;
		 BITMAPINFO			*	pBmpInfo_input				=	(  BITMAPINFO  *  )&pPkts[ii].bih;			//  2011/12/05
		 BOOL					bCompressOk					=	FALSE;

		 //
		 if  (  (  !ucSeconds_perFrame  ||  (  ucSeconds_perFrame  &&  !(  tStartTran  %  ucSeconds_perFrame  )  )  )
			 //&&  !pSharedObjUsr->ucbNotSendData
			 &&  pCompressVideo->usFramesThisSecond_toSend  <  pCompressVideo->usFrames_perSecond_expected
			 //&&  pProcInfo->bVideoChannelReady()	//  2009/02/26
			 &&  !isQ2Warning(  p_mediaQ2,  pQmcCfg->envVar.usQNodes_warningInterval_mediaQ  )		//  
			 )  
		 {
			 //  pCompressVideo->dwTickCnt_lastFrameThisSecond  =  dwTickCnt;
			 pCompressVideo->usFramesThisSecond_toSend  ++  ;
			 }		
		 else  {		//  skipped
			   continue;
		 }


		//  
		pCompressVideo->vh_compress.bih.biSizeImage  =  pCompressVideo->iCompressBufSize;
		if  (  pCompressVideo->compressor.common.ucCompressors  ==  CONST_videoCompressors_vcm  )  {
			//
#ifndef  __WINCE__
			try  {			
				 tmpiRet  =  ICCompressBegin(  pCompressVideo->u.vcm.hicLocal,  pBmpInfo_input,  &pCompressVideo->vh_compress.bih  );				 
				 }
#ifdef  __useMfc__
			catch  (  CException  *  e  )  {
				e->Delete(  );
				tmpiRet  =  -1;
			}
#endif
			catch  (  ...  )  {
				   tmpiRet  =  -1;
			}
			if  (  tmpiRet  !=  ICERR_OK  )  {
				traceLogA(  (char*)  "toShareBmp: ICCompressBegin failed."  );
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Video: ICCompressBegin failed"  )  );
				}
			else  {
				  try  {
					   tmpiRet  =  ICCompress(  pCompressVideo->u.vcm.hicLocal,  0,  &pCompressVideo->vh_compress.bih,  pCompressVideo->pCompressBuf,  &pBmpInfo_input->bmiHeader,  pInput,  &dwCkID,  &dwFlags,  lIndex,  0,  dwQuality,  NULL,  NULL  );					   
					  }
#ifdef  __useMfc__
				  catch  (  CException  *  e  )  {
						 e->Delete(  );
						 tmpiRet  =  -1;
				  }
#endif
				  catch  (  ...  )  {
						 tmpiRet  =  -1;
				  }
				  if  (  tmpiRet  ==  ICERR_OK  )  bCompressOk  =  TRUE;
				  else  {
					    traceLogA(  (char*)  "toShareBmp: ICCompress failed"  );					  
						qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Video: ICCompress failed"  )  );
				  }
				  //
				  if  (  (  tmpiRet  =  ICCompressEnd(  pCompressVideo->u.vcm.hicLocal  )  )  !=  ICERR_OK  )  {
					  traceLogA(  (char*)  "ICCompressEnd failed"  );
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Video: ICCompressEnd failed"  )  );
				  }
			}
#else
			traceLog((TCHAR*)  _T(  "vcm is not supported in winCe"  )  );
#endif
			if  (  !bCompressOk  )  goto  errLabel;

			if  (  (  int  )pCompressVideo->vh_compress.bih.biSizeImage  >  pCompressVideo->iCompressBufSize  )  {	//  ×öÒ»¸öÐ£Ñé£¬ÒªÊÇÑ¹ËõËã·¨Ã»´íµÄ»°£¬Êµ¼Ê²»»á·¢Éú
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoCap: Ñ¹Ëõ°ü´óÐ¡[%d]>Ñ¹Ëõ°ü¿Õ¼ä´óÐ¡[%d],ÑÏÖØ´íÎó"  ),  pCompressVideo->vh_compress.bih.biSizeImage,  pCompressVideo->iCompressBufSize  );
				  goto  errLabel;
			  }
			  //
			  if  (  !pCompressVideo->vh_compress.bih.biSizeImage  )  {		//  2009/04/01. no change in bmp.
				  continue;
			  }

			  #ifdef  __DEBUG__
					  //  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoCap: compress, %d -> %d"  ),  pCompressVideo->vh_decompress.bih.biSizeImage,  pCompressVideo->vh_compress.bih.biSizeImage  );
			  #endif

			  //
			  if  (  index_pReq  >=  nPkts  )  {
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doEncVideo failed: index_pReq >=  nPkts"  )  );
				  goto  errLabel;
			  }
			  TRANSFER_VIDEO_DATA  *  pReq  =  (  TRANSFER_VIDEO_DATA  *  )(  pPkts[index_pReq].memory.m_pBuf  +  pPkts[index_pReq].uiSize_dec  );
			  if  (  !bInited_pReq  )  {
				  if  (  pReq  )  {
					  //  memset(  pReq,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
					  pReq->uiType  =  CONST_imCommType_transferVideoData;
					  //  pReq->uiTranNo_openAvDev  =  pCompressVideo->uiTranNo_openAvDev;
					  pReq->uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;			//  2010/09/04
					  //
				  }
				  //
				  bInited_pReq  =  TRUE;
			  }

			  //
			  if  (  pReq->usCnt  >=  mycountof(  pReq->mems  )  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "doEncVideo failed: pReq->usCnt >=  mems"  )  );
				  #endif
				  goto  errLabel;
			  }
			  if  (  sizeof(  pReq->buf  )  <=  pReq->uiLen  )  {
				  traceLogA(  (char*)  "toShareBmp failed: sizeof(  pReq->buf  ) %d  <=  pReq->len %d",  sizeof(  pReq->buf  ),  pReq->uiLen  );
				  goto  errLabel;
			  }

			  if  (  pCompressVideo->vh_compress.bih.biSizeImage  >  sizeof(  pReq->buf  )  -  pReq->uiLen  )  
			  {
				  traceLogA(  (char*)  "toShareBmp error: compress biSizeImage [%d] > sizeof(  pReq->buf  ) [%d]",  pCompressVideo->vh_compress.bih.biSizeImage,  sizeof(  pReq->buf  )  -  pReq->uiLen  );
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "toShareBmp error: compress biSizeImage [%d] > sizeof(  pReq->buf  ) [%d]"  ),  pCompressVideo->vh_compress.bih.biSizeImage,  sizeof(  pReq->buf  )  -  pReq->uiLen  );
				  goto  errLabel;
			  }
			  //
			  //
			  pReq->mems[pReq->usCnt].uiLen  =  pCompressVideo->vh_compress.bih.biSizeImage;
			  memcpy(  pReq->buf  +  pReq->uiLen,  pCompressVideo->pCompressBuf,  pReq->mems[pReq->usCnt].uiLen  );

			  //  2008/11/12, 
			  if  (  iSampleTimeInMs  )  {
				  //  pReq->mems[0].uiSampleTimeInMs  =  iSampleTimeInMs;				  
				  pReq->mems[pReq->usCnt].uiSampleTimeInMs  =  myuiSampleTimeInMs  =  iSampleTimeInMs  -  pSharedObj->iDiffInMs_tStartAudio;	//  2009/05/26
				  //pReq->mems[pReq->usCnt].uiSampleTimeInMs_org  =  iSampleTimeInMs;									//  2009/05/27
			  }
#if  0
			  if  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {
				  //pReq->mems[pReq->usCnt].usIndex_ii  =  
					  usIndex_activeMems_from  =  pSharedObjUsr->iIndex_activeMems_from_videoConferenceStarter; 
			  }
#endif

			  //
			  pReq->uiLen  +=  pReq->mems[pReq->usCnt].uiLen;
			  pReq->usCnt  ++  ;

		    }
		else  if  (  pCompressVideo->compressor.common.ucCompressors  ==  CONST_videoCompressors_dmo  )  {
			      //  if  (  dmoCompressVideo(  &pCompressVideo->u.dmo,  pBmpInfo_input,  pInput,  &pCompressVideo->vh_compress,  (  BYTE  *  )pCompressVideo->pCompressBuf  )  )  
			      if  (  compressVideo_dmo(  &pCompressVideo->u.dmo,  pBmpInfo_input,  pInput  )  )  
				  {
					  traceLogA(  (char*)  "dmoCompressVideo failed"  );
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Video: dmoCompressVideo failed"  )  );
					  goto  errLabel;
				  }
				  int  index_output;
				  for  (  index_output  =  0;  ;  )  {

					   if  (  index_pReq  >=  nPkts  
						   ||  index_output  >  200  )  
					   {
						   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doEncVideo failed: index_pReq >=  nPkts or i too big"  )  );
						   goto  errLabel;
					   }
					   TRANSFER_VIDEO_DATA  *  pReq  =  (  TRANSFER_VIDEO_DATA  *  )(  pPkts[index_pReq].memory.m_pBuf  +  pPkts[index_pReq].uiSize_dec  );
					   if  (  !bInited_pReq  )  {
						   if  (  pReq  )  {
							   //  memset(  pReq,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
							   pReq->uiType  =  CONST_imCommType_transferVideoData;
							   //  pReq->uiTranNo_openAvDev  =  pCompressVideo->uiTranNo_openAvDev;
							   pReq->uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;			//  2010/09/04
							   //
						   }
						   //
						   bInited_pReq  =  TRUE;
					   }

					   if  (  pReq->usCnt  >=  mycountof(  pReq->mems  )  )  {
						   //  装不下了
						   index_pReq  ++  ;  bInited_pReq  =  FALSE;
						   continue;
					   }
					   if  (  sizeof(  pReq->buf  )  <=  pReq->uiLen  )  {
						   traceLogA(  (char*)  "toShareBmp failed: sizeof(  pReq->buf  ) %d  <=  pReq->len %d",  sizeof(  pReq->buf  ),  pReq->uiLen  );
						   goto  errLabel;
					   }
					   pReq->mems[pReq->usCnt].uiLen  =  sizeof(  pReq->buf  )  -  pReq->uiLen;						
					   //  if  (  getDmoOutputByIndex(  &pCompressVideo->u.dmo,  i,  (  BYTE  *  )pCompressVideo->pCompressBuf,  (  unsigned  int  *  )&pCompressVideo->vh_compress.bih.biSizeImage,  NULL,  NULL  )  )  break;
					   tmpiRet  =  getDmoOutputByIndex(  &pCompressVideo->u.dmo,  index_output,  (  BYTE  *  )pReq->buf  +  pReq->uiLen,  &pReq->mems[pReq->usCnt].uiLen,  NULL,  NULL  );
					   if  (  tmpiRet  )  {
						   if  (  tmpiRet  ==  CONST_qdcRet_bufTooSmall  )  {
							   if  (  pReq->uiLen  )  {
								   //  装不下了
								   index_pReq  ++  ;  bInited_pReq  =  FALSE;
								   continue;
							   }
							   //  如果整个pReq->buf都装不下，那肯定是这个包实在太大了，必须清除
							   dmoClearOutputs(  &pCompressVideo->u.dmo  );
						   }
						   break;
					   }

					   //  2008/11/12, 
					   if  (  iSampleTimeInMs  )  {
						   //  pReq->mems[0].uiSampleTimeInMs  =  iSampleTimeInMs;				  
						   pReq->mems[pReq->usCnt].uiSampleTimeInMs  =  myuiSampleTimeInMs  =  iSampleTimeInMs  -  pSharedObj->iDiffInMs_tStartAudio;	//  2009/05/26
						   //pReq->mems[pReq->usCnt].uiSampleTimeInMs_org  =  iSampleTimeInMs;									//  2009/05/27
					   }
#if  0
					   if  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {
						   //pReq->mems[pReq->usCnt].usIndex_ii  =  
							   usIndex_activeMems_from  =  pSharedObjUsr->iIndex_activeMems_from_videoConferenceStarter; 
					   }
#endif

					   //
					   pReq->uiLen  +=  pReq->mems[pReq->usCnt].uiLen;
					   pReq->usCnt  ++  ;

					   //  注意，i只能这里增加，因为如果bufTooSmall,往往会重新读取一次
					   index_output  ++  ;
				  }					   
				  
				  bCompressOk  =  TRUE;
			      }
		else    {
				  CUS_MODULE_U	*	pModule  =  NULL;
				  //
				  M_getCompressModule(  &pQyMc->cusModules,  pCompressVideo->uiModuleType_toEnc,  pModule  );	//  2012/09/09

				  if  (  !pModule  
					  ||  !pModule->compress.pf_qdcCompressVideo 
						||  !pModule->compress.pf_qdcGetOutputByIndex  )  goto  errLabel;

				  if  (  pModule->compress.pf_qdcCompressVideo(  &pCompressVideo->u.qoi.myQoi.common,  pBmpInfo_input,  pInput,  iSampleTimeInMs  )  <  0  )  
				  {
					  traceLogA(  (char*)  "qdcCompressVideo failed"  );
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Video: qdcCompressVideo failed"  )  );
					  goto  errLabel;
				  }


				  //
				  int  index_output;
				  for  (  index_output  =  0;  ;  )  {

					   if  (  index_pReq  >=  nPkts  
						   ||  index_output  >  200  )  
					   {
						   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doEncVideo failed: index_pReq >=  nPkts or i too big"  )  );
						   goto  errLabel;
					   }

					   //
					   TRANSFER_VIDEO_DATA  *  pReq  =  (  TRANSFER_VIDEO_DATA  *  )(  pPkts[index_pReq].memory.m_pBuf  +  pPkts[index_pReq].uiSize_dec  );
					   if  (  !bInited_pReq  )  {
						   if  (  pReq  )  {
							   //  memset(  pReq,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
							   pReq->uiType  =  CONST_imCommType_transferVideoData;
							   //  pReq->uiTranNo_openAvDev  =  pCompressVideo->uiTranNo_openAvDev;
							   pReq->uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;			//  2010/09/04
							   //
						   }
						   //
						   bInited_pReq  =  TRUE;
					   }

					   if  (  pReq->usCnt  >=  mycountof(  pReq->mems  )  )  {
						   //  装不下了
						   index_pReq  ++  ;  bInited_pReq  =  FALSE;
						   continue;
					   }
					   if  (  sizeof(  pReq->buf  )  <=  pReq->uiLen  )  {
						   traceLogA(  (char*)  "toShareBmp failed: sizeof(  pReq->buf  ) %d  <=  pReq->len %d",  sizeof(  pReq->buf  ),  pReq->uiLen  );
						   goto  errLabel;
					   }
					   pReq->mems[pReq->usCnt].uiLen  =  sizeof(  pReq->buf  )  -  pReq->uiLen;						
					   //  if  (  getDmoOutputByIndex(  &pCompressVideo->u.dmo,  i,  (  BYTE  *  )pCompressVideo->pCompressBuf,  (  unsigned  int  *  )&pCompressVideo->vh_compress.bih.biSizeImage,  NULL,  NULL  )  )  break;					
					   tmpiRet  =  pModule->compress.pf_qdcGetOutputByIndex(  &pCompressVideo->u.qoi.myQoi.common,  index_output,  (  BYTE  *  )pReq->buf  +  pReq->uiLen,  &pReq->mems[pReq->usCnt].uiLen,  NULL,  NULL  );
					   if  (  tmpiRet  )  {
						   if  (  tmpiRet  ==  CONST_qdcRet_bufTooSmall  )  {
							   if  (  pReq->uiLen  )  {
								   //  装不下了
								   index_pReq  ++  ;  bInited_pReq  =  FALSE;
								   continue;
							   }

							   //  如果整个pReq->buf都装不下，那肯定是这个包实在太大了，必须清除
							   if  (  pModule->compress.pf_qdcClearOutputs  )  {
								   pModule->compress.pf_qdcClearOutputs(  &pCompressVideo->u.qoi.myQoi.common  );
							   }
						   }
						   break;
					   }
					   #ifdef  __DEBUG__
							   if  (  pQmcCfg->debugStatusInfo.ucb__Dump_h265_enc__  )  {
								   FILE  *  fp  =  NULL;
								   char  *  fn  =  (char*)CONST_fn_dump_h265_enc;
								   fp  =  fopen(  fn,  "ab+"  );
								   if  (  fp  )  {
									   char  *  pBuffer  =  pReq->buf  +  pReq->uiLen;
									   int  BufferLen  =  pReq->mems[pReq->usCnt].uiLen;
									   //
									   fwrite(  pBuffer,  BufferLen,  1,  fp  );							
									   fclose(  fp  );					
								   }
								   static  int  uiCnt_fn  =  0;
								   uiCnt_fn  ++  ;
								   if  (  uiCnt_fn  ==  2000  )  {
									   int  i;
									   i  =  1;		
								   }
							   }
					   #endif

					   //  2008/11/12, 
					   if  (  iSampleTimeInMs  )  {
						   //  pReq->mems[0].uiSampleTimeInMs  =  iSampleTimeInMs;				  
						   pReq->mems[pReq->usCnt].uiSampleTimeInMs  =  myuiSampleTimeInMs  =  iSampleTimeInMs  -  pSharedObj->iDiffInMs_tStartAudio;	//  2009/05/26
						   //pReq->mems[pReq->usCnt].uiSampleTimeInMs_org  =  iSampleTimeInMs;									//  2009/05/27
					   }
#if  0
					   if  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {
						   //pReq->mems[pReq->usCnt].usIndex_ii  =  
							   usIndex_activeMems_from  =  pSharedObjUsr->iIndex_activeMems_from_videoConferenceStarter; 
					   }
#endif

					   pReq->uiLen  +=  pReq->mems[pReq->usCnt].uiLen;
					   pReq->usCnt  ++  ;

					   //  注意，i只能这里增加，因为如果bufTooSmall,往往会重新读取一次
					   index_output  ++  ;
				  }					   
				  
				  bCompressOk  =  TRUE;
			      
		}

		if  (  !bCompressOk  )  {
			traceLog((TCHAR*)  _T(  "toShareBmp failed: compress failed"  )  );
			goto  errLabel;
		}

		#ifdef  __DEBUG__
				#if  0
					 traceLog((TCHAR*)  _T(  "doEncVideo: pReq->usCnt %d, pReq->uiLen %d, nPkts %d"  ),  (  int  )pReq->usCnt,  pReq->uiLen,  nPkts  );
				#endif
		#endif


		continue;
	}

#ifdef  __DEBUG__
#endif


	iErr  =  0;

errLabel:

	return  iErr;
}













int  doEncodeVideo_default(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_bmpCommon  *  pCapProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsgBuf,  BOOL  bPassThrough  )
{
	int		iErr	=	-1;
	

	//MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	int  iIndex_sharedObj  =  pCapProcInfo->iIndex_sharedObj;
	QY_SHARED_OBJ				*	pSharedObj					=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;

	
				 
		long  old_pktId  =  0;
		 //
		 for  (  ;  ;  )  {
			  if  (  bCapBmpQuit(  pCapProcInfo,  0,  0  )  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "doEncodeVideo_default failed：quit is true"  )  );
				  #endif
				  goto  errLabel;
			  }
			  //
			  for  (  ;  ;  )  {
				   if  (  bCapBmpQuit(  pCapProcInfo,  0,  0  )  )  goto  errLabel;
				   if  (  !getNextVPkt(  pCapProcInfo->compressVideo.pCurPkt,  pCapProcInfo->compressVideo.pInDataCacheQ,  &pCapProcInfo->thread.q2  )  )  break;
				   Sleep(  40  );
			  }
			  //
#if  10
			  unsigned  char  *  pInput  =  NULL;
			  unsigned  int  uiInputSize  =  0;
			  BOOL  bNeed_forceKeyFrame  =  FALSE;	//  2014/09/25
			  if  (  enc_parseOrgVPkt_i(  CONST_uiTransformType_encVideo,  pCapProcInfo,  pCapProcInfo->compressVideo.pCurPkt,  &old_pktId,  &pInput,  &uiInputSize,  &bNeed_forceKeyFrame  )  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "doTrans_default failed, parsePkt failed"  )  );
				  #endif
				  goto  errLabel;  
			  }
			  //
			  pCapProcInfo->compressVideo.u.qoi.myQoi.common.var.encInfo.bNeed_forceKeyFrame=bNeed_forceKeyFrame;
#endif

			//
			  myDRAW_VIDEO_DATA  * pPkt  =  pCapProcInfo->compressVideo.pCurPkt;

			  //
			  unsigned  int	uiSize_enc;				
			  if  (  pPkt->memory.uiBufSize  <  pPkt->uiSize_dec  )  {
							#ifdef  __DEBUG__
									traceLog((TCHAR*)  _T(  "Err: uiLen < uiSize_dec"  )  );
							#endif
							break;		 					   
			  }
			  uiSize_enc  =  pPkt->memory.uiBufSize  -  pPkt->uiSize_dec;
			  //  if  (  uiSize_enc  !=  sizeof(  TRANSFER_VIDEO_DATA  )  )  
			  if  (  uiSize_enc  <  sizeof(  TRANSFER_VIDEO_DATA  )  )  //  2014/10/01
			  {
						   #ifdef  __DEBUG__
								   				  traceLog((TCHAR*)  _T(  "Err: uiSize_enc %d <sizeof( TRANSFER_VIDEO_DATA ) %d. uiBufSize %d, uiSize_dec %d, iIndex_sharedObj %d"  ),  uiSize_enc,  sizeof(  TRANSFER_VIDEO_DATA  ),  
													  pPkt->memory.uiBufSize,  pPkt->uiSize_dec,					  
													  pCapProcInfo->iIndex_sharedObj  );
						   #endif
						   break;		 					  
			  }
			  //  注意：这个初始化非常重要，涉及压缩数据有效性				
			  TRANSFER_VIDEO_DATA  *  pReq  =  (  TRANSFER_VIDEO_DATA  *  )(  pPkt->memory.m_pBuf  +  pPkt->uiSize_dec  );					 
			  memset(  pReq,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );

			  //
#ifdef  __DEBUG__
			  if  (  pSharedObj->bSlave  )  {
				  int  i;
				  i  =  0;
			  }			  
			  //
			  if  (  0  )
			  {					
				  traceLog((TCHAR*)  _T(  "uiSize_enc %d,sizeof( TRANSFER_VIDEO_DATA ) %d. uiBufSize %d, uiSize_dec %d, iIndex_sharedObj %d"  ),  uiSize_enc,  sizeof(  TRANSFER_VIDEO_DATA  ),  
					  pPkt->memory.uiBufSize,  pPkt->uiSize_dec,
					  pCapProcInfo->iIndex_sharedObj  );
					

			  }
#endif

			  //
			  SHARED_OBJ_USR	*	pSharedObjUsr	=	getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );				  
			  if  (  !pSharedObjUsr  )  {
					   #ifdef  __DEBUG__
							   traceLog((TCHAR*)  _T(  "mcThread_toShareBmp: pSharedObjUsr is null"  )  );
					   #endif
					   continue;				   
			  }
			  				 
			  //
			  #if  1
						DWORD	dwTickCnt  =  GetTickCount(  );
						pPkt->debugInfo.usToEncInMs  =  dwTickCnt  -  pPkt->debugInfo.dwTickCnt_start;
			  #endif

			  //  2016/02/12
			  if  (  bPassThrough  )  {
				  //  2016/02/29
				  if  (  pSharedObj->uiType1  !=  CONST_sharedObjType_qvcf  )  {
					  if  (  !pSharedObjUsr->bIn3DConf  )  {
						  showInfo_open0(  0,  0,  _T(  "doEncode_default failed, sharedObjUsr->bIn3DConf changed to false. not matched with bPassThrough"  )  );
						  goto  errLabel;
					  }
				  }
			  }

			  //
			  #ifdef  __DEBUG__
					  if  (  pSharedObj->bSlave  )  {
						  int  ii;
						  ii  =  0;
					  }
			  #endif

			  //
			  //  2015/05/23. 对3d会议的本地流来说，不需要压缩，只用其无压缩视频，所以不需要执行压缩
			  //
			  if  (  !bPassThrough  )  {
				  doEncVideoPkt(  pProcInfo,  pSharedObj,  pCapProcInfo,  pPkt  );//  
			  }
		

				#if  1
						dwTickCnt  =  GetTickCount(  );
							pPkt->debugInfo.usEncedInMs  =  dwTickCnt  -  pPkt->debugInfo.dwTickCnt_start;
						//  2012/01/06
						unsigned  char  ucbFpsUnmatched  =  FALSE;
						if  (  pCapProcInfo->compressVideo.usFrames_perSecond_expected  >=  pCapProcInfo->compressVideo.input_BufferCB.videoInputInfo.usFps  +  5  )  {		//  如果设置29.但是输入是24,那么也需要警告提示,所以是 >=
							ucbFpsUnmatched  =  TRUE;							
						}
						if  (  pSharedObj->status.ucbFpsUnmatched  !=  ucbFpsUnmatched  )  pSharedObj->status.ucbFpsUnmatched  =  ucbFpsUnmatched;
				   #endif

				   //
				   BOOL		bPktRedirected  =  FALSE;
				   if  (  !q2PostMsgAndTrigger(  pPkt,  1  *  sizeof(  pPkt[0]  ),  &pCapProcInfo->postThread.q2,  _T(  "doEncodeVideo_default"  ))) {
					   bPktRedirected  =  TRUE;
				   }
				   if  (  bPktRedirected  )  {						
					   detachVPkt(  pPkt,  0  );
					   }
				   else  {
						 clean_myDRAW_VIDEO_DATA(  pCapProcInfo->compressVideo.pCurPkt,  _T(  ""  )  );			  
				   }

				   
				   //
   				   #ifdef  __DEBUG__
							if  (  !bPktRedirected  )  {
								M_pkts_showNo(  pkts,  nPkts,  _T(  "encVideo free"  )  );
							}
				   #endif


			  //
			  continue;
		 }



	iErr  =  0;
errLabel:

	return  iErr;
}


//  2015/10/20



 //
int  doEncodeVideo_mediaSdk(  CAP_procInfo_bmpCommon  *  pCapProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsgBuf  )
{
	int		iErr	=	-1;
	QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();


		 //
	switch  (  pCapProcInfo->compressVideo.compressor.common.ucCompressors  )  {
			case  CONST_videoCompressors_ipp:
			case  CONST_videoCompressors_hwAccl:
			//case  CONST_videoCompressors_cuda:
				  break;
			default:
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "doEncodeVideo_mediaSdk failed, uiModuleType_toDec is not mediaSdk_dec"  )  );
				   #endif
				   goto  errLabel;
				   break;		 
	}

		 //
		 if  (  !pQyMc->cusModules.pMediaSdk_enc
			 ||  !pQyMc->cusModules.pMediaSdk_enc->compress.pf_qdcCompressVideoRun  )
		 {
			 goto  errLabel;
		 }

		 __try  {
				if  (  pQyMc->cusModules.pMediaSdk_enc->compress.pf_qdcCompressVideoRun(  &pCapProcInfo->compressVideo.u.qoi.myQoi.common  )  )  goto  errLabel;
				 }
		 __except  (  1  )  {
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "doEncodeVideo_mediaSdk exception"  )  );
				   #endif
				   goto  errLabel;
		 }

	iErr  =  0;
	
errLabel:
	return  iErr;
}


#if  0
int  doEncodeVideo_mediaSdk_conf(  CAP_procInfo_bmpCommon  *  pCapProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsgBuf  )
{
	int		iErr	=	-1;
	QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();


		 //
	switch  (  pCapProcInfo->compressVideo.compressor.common.ucCompressors  )  {
			case  CONST_videoCompressors_ipp:
			case  CONST_videoCompressors_hwAccl:
			//case  CONST_videoCompressors_cuda:
				  break;
			default:
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "doEncodeVideo_mediaSdk_conf failed, uiModuleType_toDec is not mediaSdk_dec"  )  );
				   #endif
				   goto  errLabel;
				   break;		 
	}

		 //
		 if  (  !pQyMc->cusModules.pMediaSdk_enc_conf
			 ||  !pQyMc->cusModules.pMediaSdk_enc_conf->compress.pf_qdcCompressVideoRun  )
		 {
			 goto  errLabel;
		 }

		 __try  {
				if  (  pQyMc->cusModules.pMediaSdk_enc_conf->compress.pf_qdcCompressVideoRun(  &pCapProcInfo->compressVideo.u.qoi.myQoi.common  )  )  goto  errLabel;
				 }
		 __except  (  1  )  {
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "qdcDecompressVideoRun exception"  )  );
				   #endif
				   goto  errLabel;
		 }

	iErr  =  0;
	
errLabel:
	return  iErr;
}
#endif 


int  doEncodeVideo_vpl(CAP_procInfo_bmpCommon* pCapProcInfo, MIS_CNT* pMisCnt, MIS_MSGU* pMsgBuf)
{
	int		iErr = -1;
	QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();


	//
	switch (pCapProcInfo->compressVideo.compressor.common.ucCompressors) {
	case  CONST_videoCompressors_ipp:
	case  CONST_videoCompressors_hwAccl:
		//case  CONST_videoCompressors_cuda:
		break;
	default:
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("doEncodeVideo_mediaSdk_conf failed, uiModuleType_toDec is not mediaSdk_dec"));
#endif
		goto  errLabel;
		break;
	}

	CUS_MODULE_U* pModule; pModule = pQyMc->cusModules.pEnc_vpl;

	//
	if (!pModule
		|| !pModule->compress.pf_qdcCompressVideoRun)
	{
		goto  errLabel;
	}

	__try {
		if (pModule->compress.pf_qdcCompressVideoRun(&pCapProcInfo->compressVideo.u.qoi.myQoi.common))  goto  errLabel;
	}
	__except (1) {
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("qdcDecompressVideoRun exception"));
#endif
		goto  errLabel;
	}

	iErr = 0;

errLabel:
	return  iErr;
}






//
int  doEncodeVideo_nv(  CAP_procInfo_bmpCommon  *  pCapProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsgBuf  )
{
	int		iErr	=	-1;
	QY_MC* pQyMc = g_pQyMc;;// QY_GET_GBUF();


		 //
	switch  (  pCapProcInfo->compressVideo.compressor.common.ucCompressors  )  {
			case  CONST_videoCompressors_ipp:
			case  CONST_videoCompressors_hwAccl:
			//case  CONST_videoCompressors_cuda:
				  break;
			default:
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "doEncodeVideo_mediaSdk_conf failed, uiModuleType_toDec is not mediaSdk_dec"  )  );
				   #endif
				   goto  errLabel;
				   break;		 
	}

		 //
		 if  (  !pQyMc->cusModules.pEnc_nv
			 ||  !pQyMc->cusModules.pEnc_nv->compress.pf_qdcCompressVideoRun  )
		 {
			 goto  errLabel;
		 }

		 __try  {
				if  (  pQyMc->cusModules.pEnc_nv->compress.pf_qdcCompressVideoRun(  &pCapProcInfo->compressVideo.u.qoi.myQoi.common  )  )  {
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "doEncodeVideo_nv failed, qdcCompressVideoRun failed"  )  );
					#endif
					goto  errLabel;
				}
				 }
		 __except  (  1  )  {
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "qdcDecompressVideoRun exception"  )  );
				   #endif
				   goto  errLabel;
		 }

	iErr  =  0;
	
errLabel:
	return  iErr;
}


int  doEncodeVideo_d3d_nv(CAP_procInfo_bmpCommon* pCapProcInfo, MIS_CNT* pMisCnt, MIS_MSGU* pMsgBuf)
{
	int		iErr = -1;
	QY_MC* pQyMc = g_pQyMc;;// QY_GET_GBUF();

	//
	showInfo_open(0, 0, 0, _T("doEncodeVideo_d3d_nv. l1077 enters"));

	//
	switch (pCapProcInfo->compressVideo.compressor.common.ucCompressors) {
	case  CONST_videoCompressors_ipp:
	case  CONST_videoCompressors_hwAccl:
		//case  CONST_videoCompressors_cuda:
		break;
	default:
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("doEncodeVideo_mediaSdk_conf failed, uiModuleType_toDec is not mediaSdk_dec"));
#endif
		goto  errLabel;
		break;
	}

	//
	if (!pQyMc->cusModules.pEncD3d_nv
		|| !pQyMc->cusModules.pEncD3d_nv->compress.pf_qdcCompressVideoRun)
	{
		goto  errLabel;
	}

	__try {
		if (pQyMc->cusModules.pEncD3d_nv->compress.pf_qdcCompressVideoRun(&pCapProcInfo->compressVideo.u.qoi.myQoi.common)) {
#ifdef  __DEBUG__
			traceLog((TCHAR*)_T("doEncodeVideo_nv failed, qdcCompressVideoRun failed"));
#endif
			goto  errLabel;
		}
	}
	__except (1) {
		//
		showInfo_open0(0, 0, _T("doEncodeVideo_d3d_nv: qdcCompressVideoRun exception"));
		//
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("qdcCompressVideoRun exception"));
#endif
		goto  errLabel;
	}

	iErr = 0;

errLabel:

	//
	showInfo_open(0, 0, 0, _T("doEncodeVideo_d3d_nv. l1123 leaves"));

	//
	return  iErr;
}


//  2015/04/30
int  doEncodeVideo_amf(  CAP_procInfo_bmpCommon  *  pCapProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsgBuf  )
{
	int		iErr	=	-1;
	QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();


		 //
	switch  (  pCapProcInfo->compressVideo.compressor.common.ucCompressors  )  {
			case  CONST_videoCompressors_ipp:
			case  CONST_videoCompressors_hwAccl:
			//case  CONST_videoCompressors_cuda:
				  break;
			default:
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "doEncodeVideo_mediaSdk_conf failed, uiModuleType_toDec is not mediaSdk_dec"  )  );
				   #endif
				   goto  errLabel;
				   break;		 
	}

		 //
		 if  (  !pQyMc->cusModules.pEnc_amf
			 ||  !pQyMc->cusModules.pEnc_amf->compress.pf_qdcCompressVideoRun  )
		 {
			 goto  errLabel;
		 }

		 __try  {
				if  (  pQyMc->cusModules.pEnc_amf->compress.pf_qdcCompressVideoRun(  &pCapProcInfo->compressVideo.u.qoi.myQoi.common  )  )  {
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "doEncodeVideo_amf failed, qdcCompressVideoRun failed"  )  );
					#endif
					goto  errLabel;
				}
				 }
		 __except  (  1  )  {
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "qdcDecompressVideoRun exception"  )  );
				   #endif
				   goto  errLabel;
		 }

	iErr  =  0;
	
errLabel:
	return  iErr;
}


//
int  doEncodeVideo_vp8(  CAP_procInfo_bmpCommon  *  pCapProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsgBuf  )
{
	int		iErr	=	-1;
	QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();


		 //
	switch  (  pCapProcInfo->compressVideo.compressor.common.ucCompressors  )  {
			case  CONST_videoCompressors_vp8:
				  break;
			default:
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "doEncodeVideo_vp8 failed, uiModuleType_toEnc is not vp8"  )  );
				   #endif
				   goto  errLabel;
				   break;		 
	}

		 //
		 if  (  !pQyMc->cusModules.pEnc_vp8
			 ||  !pQyMc->cusModules.pEnc_vp8->compress.pf_qdcCompressVideoRun  )
		 {
			 goto  errLabel;
		 }

		 __try  {
				if  (  pQyMc->cusModules.pEnc_vp8->compress.pf_qdcCompressVideoRun(  &pCapProcInfo->compressVideo.u.qoi.myQoi.common  )  )  {
					#ifdef  __DEBUG__
							//traceLog((TCHAR*)  _T(  "doEncodeVideo_vp8 failed, qdcCompressVideoRun failed"  )  );
					#endif
					goto  errLabel;
				}
				 }
		 __except  (  1  )  {
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "qdcDecompressVideoRun exception"  )  );
				   #endif
				   goto  errLabel;
		 }

	iErr  =  0;
	
errLabel:
	return  iErr;
}


//
int  doEncodeVideo(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_bmpCommon  *  pCapProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsgBuf  )
{
	int					iErr			=	-1;
	//MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	COMPRESS_VIDEO  *  pCompressVideo  =  &pCapProcInfo->compressVideo;


	//
	showInfo_open(0, 0, 0, _T("doEncodeVideo enters"));


	//  2015/05/23
	int  iIndex_sharedObj  =  pCapProcInfo->iIndex_sharedObj;
	QY_SHARED_OBJ				*	pSharedObj					=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;
	
	SHARED_OBJ_USR	*	pSharedObjUsr	=	getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );	
	if  (  !pSharedObjUsr  )  {
	    #ifdef  __DEBUG__
			    traceLog((TCHAR*)  _T(  "doEncodeVideo: pSharedObjUsr is null"  )  );
		#endif
		return  -1;		
	}
	BOOL  bPathThrough  =  FALSE;
	if  (  pSharedObjUsr->bIn3DConf  )  {  //  2015/05/23. 调用此函数只是为了绕过压缩. 在doEncodeVideo_default里也有判断
		bPathThrough  =  TRUE;
	}
	if  (  pSharedObj->uiType1  ==  CONST_sharedObjType_qvcf  )  {	//  2015/05/23. 本地播放，不需要压缩
		bPathThrough  =  TRUE;
	}
	if  (  bPathThrough  )  {
		doEncodeVideo_default(  pProcInfo,  pCapProcInfo,  pMisCnt,  pMsgBuf,  TRUE  );
		return  0;
	}


	//  2015/10/11
	if  (  pCompressVideo->ucbUseEvt  )  {
#if  0
		if  (  !pProcInfo->m_pf_doEncodeVideo_evtCli_run  )  {
			showInfo_open0(  0,  0,  _T(  "doEncodeVideo failed, m_pf_doEncodeVideo_evtCli_run is null"  )  );
			goto  errLabel;
		}
		return  pProcInfo->m_pf_doEncodeVideo_evtCli_run(  pProcInfo,  pCapProcInfo,  pMisCnt,  pMsgBuf  );
#endif 
		showInfo_open(0, 0, 0, (TCHAR*)_T("doEncodeVideo: bUseEvt true. not supported"));
		goto  errLabel;
	}


	//
	switch  (  pCompressVideo->uiModuleType_toEnc  )  {
			case  CONST_moduleType_mediaSdk_enc:				  
				  doEncodeVideo_mediaSdk(  pCapProcInfo,  pMisCnt,  pMsgBuf  );				  
				  break;
				  //
			case  CONST_moduleType_enc_vpl:
				  doEncodeVideo_vpl(pCapProcInfo, pMisCnt, pMsgBuf);
				  break;

				  //
			case  CONST_moduleType_enc_nv:  //  2014/07/05
				  doEncodeVideo_nv(  pCapProcInfo,  pMisCnt,  pMsgBuf  );
				  break;
			case  CONST_moduleType_encD3d_nv:
				  doEncodeVideo_d3d_nv(pCapProcInfo, pMisCnt, pMsgBuf);
				  break;
			case  CONST_moduleType_enc_amf:	//  2015/04/30
				  doEncodeVideo_amf(  pCapProcInfo,  pMisCnt,  pMsgBuf  );
				  break;

			case  CONST_moduleType_enc_vp8:	//  2014/07/19
				  doEncodeVideo_vp8(  pCapProcInfo,  pMisCnt,  pMsgBuf  );
				  break;
			default:
				//	
				doEncodeVideo_default(pProcInfo, pCapProcInfo, pMisCnt, pMsgBuf, FALSE);
				break;
	}


	iErr  =  0;
errLabel:

	//
	showInfo_open(0, 0, 0, _T("doEncodeVideo leaves"));

	//
	return  iErr;

}




 //  2014/04/03
 //  2011/07/15, 每次读取若干包然后一次性压缩
 DWORD WINAPI mcThreadProc_encVideo( LPVOID lpParameter )
{
	 int							iIndex_sharedObj			=	(  int  )lpParameter;

	 QY_MC* pQyMc = g_pQyMc;;// QY_GET_GBUF();
	 if  (  !pQyMc  )  {
		 return  -1;
	 }
	 MC_VAR_common					*	pProcInfo					=	(MC_VAR_common*)pQyMc->get_pProcInfo(  );  //  (  MC_VAR_isCli  *  )pSci->pVar;
	 if (  !pProcInfo  )  return  -1;

	 QY_SHARED_OBJ				*	pSharedObj					=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	 if  (  !pSharedObj  )  return  -1;

	 CAP_procInfo_bmpCommon		*	pCapProcInfo				=  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
	 if  (  !pCapProcInfo  )  return  -1;

	 //  2010/12/28
	 pCapProcInfo->compressVideo.debugInfo.nStep  =  101;

	 //
	 DWORD							dwThreadId					=	GetCurrentThreadId(  );

	 myDRAW_VIDEO_DATA				pkts[CONST_pkts_encVideo];
	 unsigned  int					uiLens[CONST_pkts_encVideo];		//  
	 int							nLens						=	mycountof(  uiLens  );		//  一次最多处理的包数。

	 int							i;
	 int							nPkts;						//								pPkts[]中有几个包是有效的。 2011/07/15

	 MIS_CNT					*	pMisCnt						=	(  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;	 	 

	 CQyMalloc						mallocObj_pMsgBuf;
	 MIS_MSGU					*	pMsgBuf						=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;


	 DWORD							dwTickCnt;

	 //  2010/09/18
	 //  int							tmpiRet;
	 BOOL							tmpbErr;


	 //
#ifdef  __DEBUG__
	 traceLogA(  (char*)  "mcThreadProc_encVideo %S enters",  pCapProcInfo->thread.q2.cfg.name  );
#endif

	 //
	 pCapProcInfo->thread.bQuit  =  FALSE;
	 pCapProcInfo->thread.bRunning  =  TRUE;


	 //  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u starts"  ),  pPlay->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id  );
	 

	 /////////////////

	 for  (  ;  !pCapProcInfo->thread.bQuit;  )  {
		  
		  //  2010/12/28
		  pCapProcInfo->compressVideo.debugInfo.nStep  =  105;

		  //
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(
							pCapProcInfo->thread.q2.cfg.usCnt_hEvents,	//  mycountof(  pPlay->hEvents  ),				// Number of events.
							 pCapProcInfo->thread.q2.hEvents,							// Location of handles.
                             FALSE,										// Wait for all?
                             5000,									// How long to wait?
                             0  );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  goto  errLabel;
	      //
		  dwTickCnt  =  GetTickCount(  );

		  if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
			  dwEvt -= WAIT_OBJECT_0;
			  switch  (  dwEvt  )  {
					  case  0:
						     //  dwTickCnt_lastData  =  dwTickCnt;		//  audio data received
						       //  traceLogA(  (char*)  "mcThreadProcInfo_toShareBmp: event 0."  );
							 break;
					  case  1:
						     traceLogA(  (char*)  "mcThreadProcInfo_toShareBmp: event 1."  );
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
		  }

		  //  2015/10/11
		  if  (  !pCapProcInfo->compressVideo.bVideoCompressInited1  )  {
			  #ifdef  __DEBUG__
					  showInfo_open(0,0,0,_T(  "thread_encV: bCompressInited is false, continue"  )  );						   
			  #endif
			  continue;
		  }
		  	
		  //
		  for  (  ;  !pCapProcInfo->thread.bQuit;  )  {
			  
					   //  2015/10/29
			   #ifdef  __DEBUG__
					   if  (  iIndex_sharedObj  ==  1  )  {
						   if  (  !isQ2Empty(  &pCapProcInfo->thread.q2  )  )  {
							   int  ii  =  0;			  
						   }
					   }
			   #endif

			   //
			  if  (  getNextVPkt(  pCapProcInfo->compressVideo.pCurPkt,  pCapProcInfo->compressVideo.pInDataCacheQ,  &pCapProcInfo->thread.q2  )  ) {
				  //
				  if (0) {
					  showInfo_open(0, 0, 0, _T("th_encVideo l1436: getNextVPkt failed"));
				  }
				  //
				  break;				  
			  }
			   
			   //
			   if  (  !pCapProcInfo->compressVideo.pCurPkt->lPktId_alloc  )  {
				   MACRO_qyAssert(  0,  _T(  "id_pkt is 0"  )  );
			   }
			   //
			   long		old_pktId  =  pCapProcInfo->compressVideo.pCurPkt->lPktId_alloc;
			   doEncodeVideo(  pProcInfo,  pCapProcInfo,  pMisCnt,  pMsgBuf  );
			   if  (  pCapProcInfo->compressVideo.pCurPkt->lPktId_alloc  ==  old_pktId  )  {	//  如果没有处理掉就需要释放
				   clean_myDRAW_VIDEO_DATA(  pCapProcInfo->compressVideo.pCurPkt,  _T(  ""  )  );						  
			   }

			   //
			   continue;
		  }

		  continue;
	 }

	 traceLogA(  (char*)  "mcThreadProc_toShareBmp will quit"  );

errLabel:

	 //  2010/12/28
	 pCapProcInfo->compressVideo.debugInfo.nStep  =  199;

	 //
	 pCapProcInfo->thread.bRunning  =  FALSE;

#if  0
	 if  (  bInited_tmpMemoryGrp  )  {
		 tmpiRet  =  freeTmpMemoryGrp(  &tmpMemoryGrp  );
		 MACRO_qyAssert(  !tmpiRet,  _T(  "mcThread_toShareBmp: freeTmpMemoryGrp failed"  )  );
	 }
#endif

#ifdef  __DEBUG__
	 TCHAR  tBuf[128];
	    _sntprintf(tBuf,mycountof(tBuf), (TCHAR*) _T( "mcThreadProc_encVideo %S leave"),  pCapProcInfo->thread.q2.cfg.name  );
		showInfo_open(0, 0, 0, tBuf);
#endif
	
	 //
	 return  0;

}



