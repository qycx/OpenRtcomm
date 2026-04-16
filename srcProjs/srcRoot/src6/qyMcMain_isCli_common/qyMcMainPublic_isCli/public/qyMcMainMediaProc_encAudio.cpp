

#include	"stdafx.h"
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"tmpCeLib.h"

#include	"qmcVideoCapture.h"

//#include	"qmcVideoCapture_isCli.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#ifndef  __WINCE__

//#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"
//  #include	"dlgtest_isCli.h"

#endif
#include	"qmcCmdProc.h"

#include	"qySqlFunc.h"
//#include	"qyAvRecordPublic.h"

//  #include	"DlgProgress.h"

#include	"myDb.h"

//#include	"isCliHelpPublic.h"
//#include	"isCliD3dPublic.h"
//#include	"qmcCommFunc_isCli.h"
#include	"qmcAcm.h"
#include	"qmcCfg.h"
#include	"dumpAudio.h"


//
//
int  toShareAudio(  MC_VAR_common  *  pProcInfo1,  CAP_procInfo_audioU  *  pRecordSoundProcInfo1,  int  iSampleTimeInMs,  BYTE	*	pInput,  unsigned  int  dwBytesRecorded,  COMPRESS_AUDIO  *  pCompressAudio,  QY_SHARED_OBJ  *  pSharedObj,  MIS_MSGU  *  pMsgBuf  =  NULL  );



#if  1

//
int  doEncodeAudio_default(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_audioCommon  *  pCapProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsgBuf  )
{
	int		iErr	=	-1;
	

	//  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	QY_MC  *  pQyMc  =  pProcInfo->pQyMc;  //  2018/10/24

	//
	int  iIndex_sharedObj  =  pCapProcInfo->iIndex_sharedObj;
	QY_sharedObj_sync  *  pSharedObjSync  =  pProcInfo->getSharedObjSyncByIndex(  iIndex_sharedObj  );
	if  (  !pSharedObjSync  )  return  -1;
	QY_SHARED_OBJ				*	pSharedObj					=	&pSharedObjSync->sharedObj;//getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;
	//
	QMC_cfg  *  pCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pCfg  )  return  -1;
	
#if  10
				 
		long  old_pktId  =  0;
		 //
		 for  (  ;  ;  )  {
			  if  (  bCapAudioQuit(  pCapProcInfo,  0,  0  )  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "doEncodeAudio_default failed：quit is true"  )  );
				  #endif
				  goto  errLabel;
			  }
			  //
			  for  (  ;  ;  )  {
				   if  (  bCapAudioQuit(  pCapProcInfo,  0,  0  )  )  goto  errLabel;
				   if  (  !getNextAPkt(  pCapProcInfo->compressAudio.pCurPkt,  pCapProcInfo->compressAudio.pInDataCacheQ,  &pCapProcInfo->thread.q2  )  )  break;
				   Sleep(  40  );
			  }
			  //
#if  10
			  unsigned  char  *  pInput  =  NULL;
			  unsigned  int  uiInputSize  =  0;
			  BOOL  bNeed_forceKeyFrame  =  FALSE;	//  2014/09/25
			  if  (  enc_parseOrgAPkt_i(  CONST_uiTransformType_encAudio,  pCapProcInfo,  pCapProcInfo->compressAudio.pCurPkt,  &old_pktId,  &pInput,  &uiInputSize,  &bNeed_forceKeyFrame  )  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "doEncodeAudio_default failed, parsePkt failed"  )  );
				  #endif
				  goto  errLabel;  
			  }
#endif

			  myPLAY_AUDIO_DATA  * pPkt  =  pCapProcInfo->compressAudio.pCurPkt;
			  int  pktLen  =  sizeof(  myPLAY_AUDIO_DATA  );

			  //
#ifdef  __DEBUG__
			  if(pCfg->debugStatusInfo.ucb__Dump_mic_pcm__){
				  int bufSize=256*1024;
				  static char * pBuf=NULL;
				  static int len=0;
				  if ( !pBuf )pBuf=(char * )malloc(bufSize );
				  //
				  if ( pPkt->uiSize_dec<bufSize-len){
					  memcpy(pBuf+len,pPkt->memory.m_pBuf,pPkt->uiSize_dec);
					  len+=pPkt->uiSize_dec;
				  }
				  //
				  if ( len > 32 * 1024 ) {
					  QMC_cfg  * pQmcCfg=(QMC_cfg * )pProcInfo->get_qmc_cfg();
					  char fileName[MAX_PATH  +  1];
					  _snprintf(  fileName,  sizeof(  fileName  ),  "%s%s",  CONST_dump_dir, CONST_fn_dump_mic_pcm  );
					  //
					  static unsigned int stn_dumpAv = 0;
					  if(  stn_dumpAv != pQmcCfg->debugStatusInfo.tn_dumpAv  ) {
						  stn_dumpAv= pQmcCfg->debugStatusInfo.tn_dumpAv;
						  FILE  *  fp=fopen(fileName, "w"  );
						  if( fp )  {
							  fclose(fp);
						  }
					  }
					  //
					  FILE * fp=fopen(fileName,"ab+");
					  if ( fp ) {
						  fwrite(pBuf,len,1,fp );
						  fclose(fp);
						  len=0;
					  }
				  }
			  }
#endif


				  //  toShareAudio(  pProcInfo,  (  CAP_procInfo_audioU  *  )pCapProcInfo,  pPkt->head.uiSampleTimeInMs,  (  BYTE  *  )pPkt->memory.m_pBuf,  pPkt->head.uiLen,  &pCapProcInfo->compressAudio,  getSharedObjByIndex(  pProcInfo,  pCapProcInfo->iIndex_sharedObj  ),  NULL,  pMsgBuf  );
#if  0
				  if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )   toShareAudio_hzj(  pProcInfo,  (  CAP_procInfo_audioU  *  )pCapProcInfo,  pPkt->head.uiSampleTimeInMs,  (  BYTE  *  )pPkt->memory.m_pBuf,  pPkt->uiSize_dec,  &pCapProcInfo->compressAudio,  getSharedObjByIndex(  pProcInfo,  pCapProcInfo->iIndex_sharedObj  ),  pMsgBuf  );
				  else  
#endif		
				  //
				  toShareAudio(  pProcInfo,  (  CAP_procInfo_audioU  *  )pCapProcInfo,  pPkt->head.uiSampleTimeInMs,  (  BYTE  *  )pPkt->memory.m_pBuf,  pPkt->uiSize_dec,  &pCapProcInfo->compressAudio,  getSharedObjByIndex(  pProcInfo,  pCapProcInfo->iIndex_sharedObj  ),  pMsgBuf  );
		
				  //
				  BOOL  bPlayLocal  =  FALSE;
				  switch  (  pSharedObj->uiType1 )  {
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
								#if  0	//  本地测试的音频在processInput_post里直接处理了
								 if  (  pSharedObj->bSoundRecorder  )  {  //  本地播放
									 if  (  pProcInfo->av.localAv.recordSoundProcInfo.bLocalAudioPlaying  )  { 
										 //
										 #ifdef  __DEBUG__
												 traceLog((TCHAR*)  _T(  "%d bytes audio data"  ),  pPkt->head.uiLen  );
										 #endif			

										if  (  pProcInfo->av.localAv.player.audio.bRunning  )  {	//  if thread is active
											bPlayLocal  =  TRUE;							 
										}						 
									 }
								 }
								#endif
								 break;
				  }
				  //
				  BOOL		bPktRedirected  =  FALSE;				   
				  if  (  bPlayLocal  )  {
					  //			  	
					  SHARED_OBJ_USR	*	pSharedObjUsr	=	getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
					  if  (  !pSharedObjUsr  )  {
						  #ifdef  __DEBUG__
							  #if  0
									traceLog((TCHAR*)  _T(  "mcThreadProc_toShareAudio: pSharedObjUsr is null,  index_sharedObj %d"  ),  iIndex_sharedObj  );
							  #endif
						  #endif
						  //goto  errLabel;
						  //continue;
						  }
					  else  {
							//  
							pProcInfo->playLocalAudioData(  pSharedObjUsr->iTaskId,  pSharedObjUsr->uiTranNo_openAvDev_a,  &pCapProcInfo->compressAudio.ah_decompress.wfx,  pPkt,  pktLen,  &bPktRedirected,  pCapProcInfo->uiType,  pSharedObj->iIndex_capAudio  );  
					  }
				  }
				  //
				  if  (  bPktRedirected  )  {
					  //mallocObj_tmpPkt.detach(  );
					  detachAPkt(  pPkt,  0  );
					  }
				  else  {
					    clean_myPLAY_AUDIO_DATA(  pPkt,  _T(  ""  )  );
				  }



			  //
			  continue;
		 }


#endif

	iErr  =  0;
errLabel:

	return  iErr;
}



//
int  doEncodeAudio_vorbis(  CAP_procInfo_audioCommon  *  pCapProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsgBuf  )
{
	int		iErr	=	-1;
	QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();


		 //
	switch  (  pCapProcInfo->compressAudio.compressor.common.ucCompressors  )  {
			case  CONST_audioCompressors_vorbis:
				  break;
			default:
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "doEncodeAudio_vorbis failed, uiModuleType_toEnc is not vorbis"  )  );
				   #endif
				   goto  errLabel;
				   break;		 
	}

		 //
		 if  (  !pQyMc->cusModules.pQdc_vorbis_enc
			 ||  !pQyMc->cusModules.pQdc_vorbis_enc->compress.pf_qdcCompressAudioRun  )
		 {
			 goto  errLabel;
		 }

		 __try  {
				if  (  pQyMc->cusModules.pQdc_vorbis_enc->compress.pf_qdcCompressAudioRun(  &pCapProcInfo->compressAudio.u.qoi.myQoi.common  )  )  {
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "doEncodeAudio_vorbis failed, qdcCompressAudioRun failed"  )  );
							showInfo_open0(  0,  0,  _T(  "doEncodeAudio_vorbis failed, qdcCompressAudioRun failed"  )  );
					#endif
					goto  errLabel;
				}
				 }
		 __except  (  1  )  {
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "qdcCompressAudioRun exception"  )  );
				   #endif
				   goto  errLabel;
		 }

	iErr  =  0;
	
errLabel:
	return  iErr;
}



/////////////////////
int  doEncodeAudio(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_audioCommon  *  pCapProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsgBuf  )
{
	int					iErr			=	-1;
	//  MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	COMPRESS_AUDIO  *  pCompressAudio  =  &pCapProcInfo->compressAudio;
	

	//
	switch  (  pCompressAudio->uiModuleType_toEnc  )  {
			case  CONST_moduleType_qdc_vorbis_enc:	//  2014/07/19
				  return  doEncodeAudio_vorbis(  pCapProcInfo,  pMisCnt,  pMsgBuf  );
				  break;
			default:
					break;
	}


	//	
	doEncodeAudio_default(  pProcInfo,  pCapProcInfo,  pMisCnt,  pMsgBuf  );

	iErr  =  0;
errLabel:
	return  iErr;

}



//  2015/02/13
 //
 DWORD WINAPI mcThreadProc_toShareAudio( LPVOID lpParameter )
{
	 int							iIndex_sharedObj			=	(  int  )lpParameter;

	 QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();
	 QY_SERVICEGUI_INFO	*	pSci		=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSci  )  return  -1;
	 MC_VAR_common					*	pProcInfo					=	(  MC_VAR_common  *  )pSci->pVar;
	 if (  !pProcInfo  )  return  -1;

	 QY_SHARED_OBJ				*	pSharedObj					=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	 if  (  !pSharedObj  )  return  -1;

	 CAP_procInfo_audioCommon  *  pCapProcInfo  =  (  CAP_procInfo_audioCommon  *  )getCapAudioBySth(  pProcInfo,  pSharedObj->iIndex_capAudio,  0  );
	 if  (  !pCapProcInfo  )  return  -1;

	 //  2009/12/24
#if  0
	 QM_SHM_CMD					*	pShmCmd						=	NULL;
	 QM_SHM_DATA				*	pShmData					=	NULL;
	 TCHAR							mutexName_syncShmData[64]	=	_T(  ""  );
	 pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pSharedObj->iIndex_shmCmd  );
	 pShmData  =  (  QM_SHM_DATA  *  )pSharedObj->dataShm.pBuf;
	 _sntprintf(  mutexName_syncShmData,  mycountof(  mutexName_syncShmData  ),  _T(  "%s%u"  ),  CONST_mutexName_qm_syncData_a,  pSharedObj->uiTranNo  );
#endif

	 //
	 DWORD							dwThreadId					=	GetCurrentThreadId(  );

#if  0
	 CQyMalloc						mallocObj_pPkt;
	 unsigned  int					uiBufSize					=	sizeof(  myPLAY_AUDIO_DATA  )  +  pProcInfo->cfg.uiBufSize_myPlayAudioData;  //  sizeof(  myPLAY_AUDIO_DATA  );
	 myPLAY_AUDIO_DATA			*	pPkt						=	(  myPLAY_AUDIO_DATA  *  )mallocObj_pPkt.mallocf(  CONST_iAllocType_longTimeMsg,  uiBufSize  );
	 if  (  !pPkt  )  return  -1;
	 int							pktLen;
#endif
	 MIS_CNT					*	pMisCnt						=	(  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;	 	 

	 CQyMalloc						mallocObj_pMsgBuf;
	 MIS_MSGU					*	pMsgBuf						=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;

	 DWORD							dwTickCnt;

	 //  2010/09/18
	 //  TMP_MEMORY_GRP					tmpMemoryGrp;
	 //  BOOL							bInited_tmpMemoryGrp		=	FALSE;
	 int							tmpiRet;

	 //	 
	 traceLogA(  (char*)  "mcThreadProc_toShareAudio %S enters",  pCapProcInfo->thread.q2.cfg.name  );

	 pCapProcInfo->thread.bQuit  =  FALSE;
	 pCapProcInfo->thread.bRunning  =  TRUE;

	 //  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u starts"  ),  pPlay->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id  );

	 /////////////////

	 for  (  ;  !pCapProcInfo->thread.bQuit;  )  {
		  
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
						     //  traceLogA(  (char*)  "mcThreadProcInfo_toShareAudio: event 0."  );
							 break;
					  case  1:
						     traceLogA(  (char*)  "mcThreadProcInfo_toShareAudio: event 1."  );
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
		  }

		  //  2015/10/11
		  if  (  !pCapProcInfo->compressAudio.bCompressInited  )  {
			  #ifdef  __DEBUG__
					  //traceLog((TCHAR*)  _T(  "thread_toShareAudio: bCompressInited false, continued"  )  );
			  #endif
			  continue;
		  }
	
		  //
		  for  (  ;  !pCapProcInfo->thread.bQuit;  )  {

			  
			   //
			  if  (  getNextAPkt(  pCapProcInfo->compressAudio.pCurPkt,  pCapProcInfo->compressAudio.pInDataCacheQ,  &pCapProcInfo->thread.q2  )  )  break;
			   
			   //
			   if  (  !pCapProcInfo->compressAudio.pCurPkt->lPktId_getNewPkt  )  {
				   MACRO_qyAssert(  0,  _T(  "mcThreadProc_toShareAudio: id_pkt is 0"  )  );
			   }
			   //
			   long		old_pktId  =  pCapProcInfo->compressAudio.pCurPkt->lPktId_getNewPkt;
			   doEncodeAudio(  pProcInfo,  pCapProcInfo,  pMisCnt,  pMsgBuf  );
			   if  (  pCapProcInfo->compressAudio.pCurPkt->lPktId_getNewPkt  ==  old_pktId  )  {	//  如果没有处理掉就需要释放
				   clean_myPLAY_AUDIO_DATA(  pCapProcInfo->compressAudio.pCurPkt,  _T(  ""  )  );						  
			   }

			  continue;
		  }

		  continue;
	 }

	 traceLogA(  (char*)  "mcThreadProc_toShareAudio will quit"  );

errLabel:

	 pCapProcInfo->thread.bRunning  =  FALSE;

#if  0
	 if  (  bInited_tmpMemoryGrp  )  {
		 tmpiRet  =  freeTmpMemoryGrp(  &tmpMemoryGrp  );
		 MACRO_qyAssert(  !tmpiRet,  _T(  "mcThread_toShareBmp: freeTmpMemoryGrp failed"  )  );
	 }
#endif

	 traceLogA(  (char*)  "mcThreadProc_toShareAudio %S leaves",  pCapProcInfo->thread.q2.cfg.name  );
	
	 return  0;

}

#endif




///////////////
#if  10  //  2018/10/24
 int  toShareAudio(  MC_VAR_common  *  pProcInfo1,  CAP_procInfo_audioU  *  pRecordSoundProcInfo1,  int  iSampleTimeInMs,  BYTE	*	pInput,  unsigned  int  dwBytesRecorded,  COMPRESS_AUDIO  *  pCompressAudio,  QY_SHARED_OBJ  *  pSharedObj,  MIS_MSGU  *  pMsgBuf  )
{
	 int						iErr						=	-1;
	 QY_MC				*		pQyMc						=	(  QY_MC  *  )pProcInfo1->pQyMc;//QY_GET_GBUF(  );
	 CCtxQmc			*		pProcInfo					=	(  CCtxQmc  *  )pProcInfo1;
	 CUS_MODULES		*		pCusModules					=	(CUS_MODULES * )pProcInfo1->getCusModules();
	 if(!pCusModules) return -1;
	 //
	 DWORD						dwBytes_input				=	dwBytesRecorded;
	 MACRO_prepareForTran(  );
	 unsigned  char				ucFlg						=	CONST_commFlg_routeTalkData;	//  0;
	 int						lenInBytes					=	0;
	 //
	 unsigned  int				uiChannelType				=	CONST_channelType_realTimeMedia;
	 unsigned  char				ucbNeedShowFrameInfo		=	FALSE;
	 int						i;
	 //  2010/09/04
	 SHARED_OBJ_USR			*	pSharedObjUsr				=	NULL;

	 //
	 if  (  !pProcInfo1  )  return  -1;
	 QMC_cfg  *  pCfg  =  (  QMC_cfg  *  )pProcInfo1->get_qmc_cfg(  );
	 if  (  !pCfg  )  return  -1;
	 if  (  !pSharedObj  )  goto  errLabel;
	 pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
	 if  (  !pSharedObjUsr  )  goto  errLabel;

	 
	 if  (  pCompressAudio->tLastTime_sendAudio  !=  tStartTran  )  {		//  表明是一秒的开始
		 pCompressAudio->tLastTime_sendAudio  =  tStartTran;

		 //  定期向客户端下发帧速信息		
		 if  (  (  int  )(  tStartTran  -  pCompressAudio->tLastTime_showFrameInfo  )  >  pCfg->usNeedShowFrameInfoIntervalInS  )  {
			 //
			 ucbNeedShowFrameInfo  =  TRUE;
		 }
		 #ifdef  __DEBUG__	//  for test
				 //  ucbNeedShowFrameInfo  =  TRUE;						
		 #endif
		
		 //  2008/05/13, 不用调整了，用固定设置值
		 /*
		 unsigned  int  uiBytesRecorded_perBlockAlign;	uiBytesRecorded_perBlockAlign  =  pProcInfo1->cfg.policy.audio.uiBytesRecorded_perBlockAlign;
		 if  (  uiBytesRecorded_perBlockAlign  >=  MIN_uiBytesRecorded_perBlockAlign  &&  uiBytesRecorded_perBlockAlign  <=  MAX_uiBytesRecorded_perBlockAlign  )  {
			 pCompressAudio->uiBytesRecorded_perBlockAlign_expected  =  uiBytesRecorded_perBlockAlign;
		 }
		 */
	 }
	
	 //
	 QY_Q2* p_realTimeMediaQ2; p_realTimeMediaQ2 = pProcInfo1->get_realTimeMediaQ2();
	 if  (  !p_realTimeMediaQ2  )  goto  errLabel;
	 BOOL  bQWarning; bQWarning = isQ2Warning(p_realTimeMediaQ2, pCfg->envVar.usQNodes_warningInterval_rtMediaQ);
	 if  (  bQWarning  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo1->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning:  realTimeMediaQ too many nodes. audio data will be lossed"  )  );					

	 //
#if  0
	 if  (  !pProcInfo1->bAudioChannelReady(  )  )  {
		 static  DWORD	sdwTickCnt_applyForChkChannels	=	0;
		 //  QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pRecordSoundProcInfo->iIndex_sharedObj  );
	
		 //
		 if  (  pSharedObj
			 &&  !pSharedObjUsr->ucbNotSendData
				//&&  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id
					//  ||  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  
					  )
		 {
			 MIS_CNT							*	pMisCnt		=	NULL;
			 MIS_MSG_applyForChkChannels_qmc		msg_applyForChkChannels;
			 int	dwTickCnt;						dwTickCnt  =  GetTickCount(  );
			 int									i;
			 CQyQ2Help								q2Help;

			 if  (  dwTickCnt  -  sdwTickCnt_applyForChkChannels  >  4000  )  {
				 //for  (  i  =  0;  i  <  mycountof(  pProcInfo1->misCnts  );  i  ++  )  
				 for  (  i  =  0;  i  <  pProcInfo1->get_ucCnt_misCnts(  );  i  ++  )  
				 {
					  pMisCnt  =  (  MIS_CNT  *  )pProcInfo1->getMisCntByIndex(  i  );//&pProcInfo1->misCnts[i];				
					  if  (  !pMisCnt  )  continue;
					  if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;

					  traceLogA(  (char*)  "toShareAudio: applyForChkChannels"  );
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo1->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "toShareAudio: rtMedia Channel not Ready, applyForChkChannels"  )  );

					  //
					  memset(  &msg_applyForChkChannels,  0,  sizeof(  msg_applyForChkChannels  )  );
					  msg_applyForChkChannels.uiType  =  CONST_misMsgType_applyForChkChannels_qmc;
					  msg_applyForChkChannels.pMisCnt  =  pMisCnt;
					  //
					  //  qPostMsgAndTrigger(  &msg_applyForChkChannels,  sizeof(  msg_applyForChkChannels  ),  &pProcInfo1->realTimeMediaQ  );
					  q2Help.qPostMsgAndTrigger(  &msg_applyForChkChannels,  sizeof(  msg_applyForChkChannels  ),  p_realTimeMediaQ2  );
				 }
				 sdwTickCnt_applyForChkChannels  =  dwTickCnt;
			 }
		 }

		 iErr  =  0;  goto  errLabel;
	 }
#endif

	 //
#if 0
	 int nAvgBytesPerSec = pCompressAudio->ah_decompress.wfx.nAvgBytesPerSec;
	 if (nAvgBytesPerSec) {
		 pCompressAudio->encInfo.st.uiTimeLen_enc = dwBytesRecorded  *  1000 / nAvgBytesPerSec;
		 //
		 int iDiffInMs = iSampleTimeInMs - pCompressAudio->encInfo.st.last_iSampleTimeInMs_enc;
		 if (abs(iDiffInMs) > 1000) {
			 if (iSampleTimeInMs > pCompressAudio->encInfo.st.uiTimeLen_enc) {
				 pCompressAudio->encInfo.st.last_iSampleTimeInMs_enc = iSampleTimeInMs - pCompressAudio->encInfo.st.uiTimeLen_enc;
				 //
				 showInfo_open0(0, null, _T("toShareAudio: last_iSampleTimeInMs_enc is set"));
			 }
		 }
	 }
#endif

	 
	 //
	 TRANSFER_AUDIO_DATA* pReq; pReq = (TRANSFER_AUDIO_DATA*)pCompressAudio->pReqCache;
	 if  (  pReq  &&  !bQWarning  )  {
		 memset(  pReq,  0,  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  );
		 pReq->uiType  =  CONST_imCommType_transferAudioData;
		 pReq->uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_a;	//  pCompressAudio->uiTranNo_openAvDev  +  iIndex_sharedObjUsr;					

#if  0	//  2010/09/12
		 pCompressAudio->usCnt_pkts  ++  ;
		 if  (  ucbNeedShowFrameInfo  )  {
			 ucFlg  |=  CONST_commFlg_routeTalkData;
			 if  (  pCompressAudio->tRecvTime_resp_fromCli  >=  pCompressAudio->tFirstTime_showFrameInfo_withoutResp  )  {	//  这是为了超时
				 pCompressAudio->tFirstTime_showFrameInfo_withoutResp  =  tStartTran;							  
			 }
			 pReq->tLastTime_showFrameInfo_020534  =  pCompressAudio->tLastTime_showFrameInfo;								//  设置标记						
			 pReq->usCnt_pkts  =  pCompressAudio->usCnt_pkts;
			 //
			 pCompressAudio->tLastTime_showFrameInfo  =  tStartTran;												
			 pCompressAudio->usCnt_pkts  =  0;
			 //
			 //  qyShowInfo1(  CONST_qyShowType_debug,  0,  "",  pProcInfo1->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tn %d, %d bytes audio data. %s"  ),  uiTranNo,  dwBytesRecorded,  ucbNeedShowFrameInfo  ?  _T(  "含音频取样信息"  )  :  _T(  ""  )  );					
		 }
#endif

		 #ifdef  __DEBUG__
				 if  (  dwBytes_input  >  sizeof(  pReq->buf  )  )  {
					 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo1->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sizeof(  audioBuf  ) %d too small, should be >= %d"  ),  sizeof(  pReq->buf  ),  dwBytesRecorded  );					
				 }
		 #endif


		 if  (  pCompressAudio->bCompressInited  )  {
			 if  (  pCompressAudio->compressor.common.ucCompressors  ==  CONST_audioCompressors_acm  )  {

				 #ifndef  __WINCE__

						 if  (  !pCompressAudio->ah_decompress.wfx.nAvgBytesPerSec  ||  !pCompressAudio->ah_pcm.wfx.nAvgBytesPerSec  ||  !pCompressAudio->ah_compress.wfx.nAvgBytesPerSec  )  goto  errLabel;
						 DWORD	dwPcmBytes		=	(  DWORD  )(  dwBytes_input  *  pCompressAudio->ah_pcm.wfx.nAvgBytesPerSec  *  1.  /  (  pCompressAudio->ah_decompress.wfx.nAvgBytesPerSec  )  );
						 if  (  !pCompressAudio->pPcmBuf  ||  dwPcmBytes  >=  pCompressAudio->dwPcmBufSize  )  {
							 if  (  pCompressAudio->pPcmBuf  )  {
								 free(  pCompressAudio->pPcmBuf  );  pCompressAudio->pPcmBuf  =  NULL;
							 }
							 pCompressAudio->dwPcmBufSize  =  dwPcmBytes  *  3  /  2  +  256;
							 pCompressAudio->pPcmBuf  =  (  char  *  )mymalloc(  pCompressAudio->dwPcmBufSize  );
							 if  (  !pCompressAudio->pPcmBuf  )  goto  errLabel;
						 }
						 DWORD	dwDstBytes		=	pCompressAudio->ah_compress.wfx.nAvgBytesPerSec  *  dwPcmBytes  /  (  pCompressAudio->ah_pcm.wfx.nAvgBytesPerSec  );
						 if  (  !pCompressAudio->pDstBuf  ||  dwDstBytes  >=  pCompressAudio->dwDstBufSize  )  {
							 if  (  pCompressAudio->pDstBuf  )  {
								 free(  pCompressAudio->pDstBuf  );  pCompressAudio->pDstBuf  =  NULL;
							 }
							 pCompressAudio->dwDstBufSize  =  dwDstBytes  *  3  /  2  +  256;
							 pCompressAudio->pDstBuf  =  (  char  *  )mymalloc(  pCompressAudio->dwDstBufSize  );
							 if  (  !pCompressAudio->pDstBuf  )  goto  errLabel;
						 }
						 //

						 dwDstBytes  =  pCompressAudio->dwDstBufSize;
						 if  (  convertAudio(  pCompressAudio->u.acm.hstr1,  pCompressAudio->u.acm.hstr2,  &pCompressAudio->ah_decompress.wfx,  (  BYTE  *  )pInput,  dwBytes_input,  &pCompressAudio->ah_pcm.wfx,  (  BYTE  *  )pCompressAudio->pPcmBuf,  pCompressAudio->dwPcmBufSize,  &pCompressAudio->ah_compress.wfx,  (  BYTE  *  )pCompressAudio->pDstBuf,  &dwDstBytes  )  )  {
							 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo1->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "convertAudio failed"  )  );					
							 goto  errLabel;
						 }

						 pInput  =  (  BYTE  *  )pCompressAudio->pDstBuf;
						 dwBytes_input  =  dwDstBytes;

				 #endif

				 //
				 pReq->uiLen  =  min(  sizeof(  pReq->buf  ),  dwBytes_input  );
				 memcpy(  pReq->buf,  pInput,  pReq->uiLen  );		 				 
				
				 pReq->mems[0].uiSampleTimeInMs  =  iSampleTimeInMs;
				 pReq->mems[0].uiLen  =  pReq->uiLen;
				 pReq->usCnt  =  1;			  

				}
			 else  if  (  pCompressAudio->compressor.common.ucCompressors  ==  CONST_audioCompressors_dmo  )  {

					   DWORD	dwDstBytes  =  pCompressAudio->u.dmo.cbOutputBuffer;
					   if  (  !pCompressAudio->pDstBuf  ||  dwDstBytes  >=  pCompressAudio->dwDstBufSize  )  {
						   if  (  pCompressAudio->pDstBuf  )  {
							   free(  pCompressAudio->pDstBuf  );  pCompressAudio->pDstBuf  =  NULL;
						   }
						   pCompressAudio->dwDstBufSize  =  dwDstBytes  *  3  /  2  +  256;
						   pCompressAudio->pDstBuf  =  (  char  *  )mymalloc(  pCompressAudio->dwDstBufSize  );
						   if  (  !pCompressAudio->pDstBuf  )  goto  errLabel;
					   }

					   dwDstBytes  =  pCompressAudio->dwDstBufSize;
					   if  (  compressAudio_dmo(  &pCompressAudio->u.dmo,  &pCompressAudio->ah_decompress,  pInput,  dwBytes_input,  iSampleTimeInMs  )  )  goto  errLabel;

					   if  (  pSharedObj  &&  pSharedObj->iDiffInMs_tStartAudio  !=  pCompressAudio->u.dmo.iDiffInMs_tStartStream  )  pSharedObj->iDiffInMs_tStartAudio  =  pCompressAudio->u.dmo.iDiffInMs_tStartStream;

					   /*
					   for  (  i  =  0;  i  <  mycountof(  pReq->mems  );  i  ++  )  {
						    memset(  &pReq->mems[i],  0,  offsetof(  TRANSFER_AUDIO_dataMem,  buf  )  );
							pReq->mems[i].uiLen  =  sizeof(  pReq->mems[i].buf  );
							if  (  getDmoOutputByIndex(  &pCompressAudio->u.dmo,  i,  (  BYTE  *  )pReq->mems[i].buf,  &pReq->mems[i].uiLen,  &pReq->mems[i].uiSampleTimeInMs  )  )  break;
							pReq->usCnt  ++  ;
					   }
					   */
					   for  (  i  =  0;  i  <  mycountof(  pReq->mems  );  i  ++  )  {		//  2009/05/20
						    if  (  sizeof(  pReq->buf  )  <=  pReq->uiLen  )  {
								traceLogA(  (char*)  "toShareAudio: sizeof(  pReq->buf  ) %d  <=  pReq->len %d",  sizeof(  pReq->buf  ),  pReq->uiLen  );
								goto  errLabel;
							}
						    pReq->mems[i].uiLen  =  sizeof(  pReq->buf  )  -  pReq->uiLen;
							if  (  getDmoOutputByIndex(  &pCompressAudio->u.dmo,  i,  (  BYTE  *  )pReq->buf  +  pReq->uiLen,  &pReq->mems[i].uiLen,  &pReq->mems[i].uiSampleTimeInMs,  &pReq->mems[i].ui_rtTimeLen  )  )  break;
							pReq->uiLen  +=  pReq->mems[i].uiLen;
							pReq->usCnt  ++  ;
					   }

					   }
			 else  {
				   CUS_MODULE_U		*	pModule  =  NULL;

				   /*
				   switch  (  pCompressAudio->compressor.common.ucCompressors  )  {
						   case  CONST_audioCompressors_ipp:
							     pModule  =  pQyMc->cusModules.pIpp;
							     break;
					       case  CONST_audioCompressors_custom:
							     pModule	=	getCusModule(  &pQyMc->cusModules,  CONST_moduleType_compress  );
								 break;
						   default:

							   traceLogA(  (char*)  "toShareAudio failed: unprocessed ucCompressors %d",  pCompressAudio->compressor.common.ucCompressors  );			   
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "toShareAudio failed: unprocessed ucCompressors %d"  ),  pCompressAudio->compressor.common.ucCompressors  );
								  goto  errLabel;				   
								  break;
				   }
				   */
				   M_getCompressModule(pCusModules,pCompressAudio->uiModuleType_toEnc,pModule );

				   //
					   if  (  !pModule
						   ||  !pModule->compress.pf_qdcCompressAudio
							||  !pModule->compress.pf_qdcGetOutputByIndex  )  goto  errLabel;

					   DWORD	dwDstBytes  =  pCompressAudio->u.qoi.myQoi.common.var.cbOutputBuffer;
					   if  (  !pCompressAudio->pDstBuf  ||  dwDstBytes  >=  pCompressAudio->dwDstBufSize  )  {
						   if  (  pCompressAudio->pDstBuf  )  {
							   free(  pCompressAudio->pDstBuf  );  pCompressAudio->pDstBuf  =  NULL;
						   }
						   pCompressAudio->dwDstBufSize  =  dwDstBytes  *  3  /  2  +  256;
						   pCompressAudio->pDstBuf  =  (  char  *  )mymalloc(  pCompressAudio->dwDstBufSize  );
						   if  (  !pCompressAudio->pDstBuf  )  goto  errLabel;
					   }

					   dwDstBytes  =  pCompressAudio->dwDstBufSize;
					   if  (  pModule->compress.pf_qdcCompressAudio(  &pCompressAudio->u.qoi.myQoi.common,  &pCompressAudio->ah_decompress,  pInput,  dwBytes_input,  iSampleTimeInMs  )  <  0  )  goto  errLabel;

					   if  (  pSharedObj  &&  pSharedObj->iDiffInMs_tStartAudio  !=  pCompressAudio->u.qoi.myQoi.common.var.iDiffInMs_tStartAudio  )  pSharedObj->iDiffInMs_tStartAudio  =  pCompressAudio->u.qoi.myQoi.common.var.iDiffInMs_tStartAudio;

					   /*
					   for  (  i  =  0;  i  <  mycountof(  pReq->mems  );  i  ++  )  {
						    memset(  &pReq->mems[i],  0,  offsetof(  TRANSFER_AUDIO_dataMem,  buf  )  );
							pReq->mems[i].uiLen  =  sizeof(  pReq->mems[i].buf  );
							if  (  getDmoOutputByIndex(  &pCompressAudio->u.dmo,  i,  (  BYTE  *  )pReq->mems[i].buf,  &pReq->mems[i].uiLen,  &pReq->mems[i].uiSampleTimeInMs  )  )  break;
							pReq->usCnt  ++  ;
					   }
					   */
					   for  (  i  =  0;  i  <  mycountof(  pReq->mems  );  i  ++  )  {		//  2009/05/20
						    if  (  sizeof(  pReq->buf  )  <=  pReq->uiLen  )  {
								traceLogA(  (char*)  "toShareAudio: sizeof(  pReq->buf  ) %d  <=  pReq->len %d",  sizeof(  pReq->buf  ),  pReq->uiLen  );
								goto  errLabel;
							}
						    pReq->mems[i].uiLen  =  sizeof(  pReq->buf  )  -  pReq->uiLen;
							if  (  pModule->compress.pf_qdcGetOutputByIndex(  &pCompressAudio->u.qoi.myQoi.common,  i,  (  BYTE  *  )pReq->buf  +  pReq->uiLen,  &pReq->mems[i].uiLen,  &pReq->mems[i].uiSampleTimeInMs,  &pReq->mems[i].ui_rtTimeLen  )  )  break;
							//
							if(pCfg->debugStatusInfo.ucb__Dump_mp3_enc__ ) {
								dumpAudio(pReq->buf+pReq->uiLen,pReq->mems[i].uiLen);
							}
							//
							if (0 == pReq->mems[i].uiSampleTimeInMs) {
								//
								//pReq->mems[i].uiSampleTimeInMs = pCompressAudio->encInfo.st.last_iSampleTimeInMs_enc + pCompressAudio->encInfo.st.uiTimeLen_enc;
								//pCompressAudio->encInfo.st.last_iSampleTimeInMs_enc = pReq->mems[i].uiSampleTimeInMs;
								//
								pReq->mems[i].uiSampleTimeInMs = iSampleTimeInMs;
							}
							//
							pReq->uiLen  +=  pReq->mems[i].uiLen;
							pReq->usCnt  ++  ;
					   }

					   
			 }
#if  0

			 else  {
				   traceLogA(  (char*)  "toShareAudio failed: unprocessed ucCompressors %d",  pCompressAudio->compressor.ucCompressors  );			   
				   qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "toShareAudio failed: unprocessed ucCompressors %d"  ),  pCompressAudio->compressor.ucCompressors  );
				   goto  errLabel;				   
			 }		
#endif
	 
		 }

		 //  2010/09/12				  
		 if  (  !pReq->usCnt  )  {	
			 //  traceLog((TCHAR*)  _T(  "toShareAudio failed: req.usCnt is 0"  )  );
			 goto  errLabel;
		 }
		 if (pReq->usCnt != 1) {
			 int ii = 0;
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

		 //  2010/09/12
		 pCompressAudio->usCnt_pkts  ++  ;
		 if  (  ucbNeedShowFrameInfo  )  {
			 ucFlg  |=  CONST_commFlg_routeTalkData;
			 if  (  pCompressAudio->tRecvTime_resp_fromCli  >=  pCompressAudio->tFirstTime_showFrameInfo_withoutResp  )  {	//  这是为了超时
				 pCompressAudio->tFirstTime_showFrameInfo_withoutResp  =  tStartTran;							  
			 }
			 pReq->tLastTime_showFrameInfo_020534  =  pCompressAudio->tLastTime_showFrameInfo;								//  设置标记						
			 pReq->usCnt_pkts  =  pCompressAudio->usCnt_pkts;
			 //
			 pCompressAudio->tLastTime_showFrameInfo  =  tStartTran;												
			 pCompressAudio->usCnt_pkts  =  0;
			 //
			 //  qyShowInfo1(  CONST_qyShowType_debug,  0,  "",  pProcInfo1->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tn %d, %d bytes audio data. %s"  ),  uiTranNo,  dwBytesRecorded,  ucbNeedShowFrameInfo  ?  _T(  "含音频取样信息"  )  :  _T(  ""  )  );					
		 }


		 #ifdef  __DEBUG__
				 if  (  pCfg->debugStatusInfo.ucbPrint_a_out  )  {				
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

			 int  iIndex_misCnt =  0;  //pSharedObj->curRoute_sendLocalAv.iIndex_misCnt
			 pMisCnt  =  (  MIS_CNT  *  )pProcInfo1->getMisCntByIndex(  iIndex_misCnt  );
			 if  (  pMisCnt  &&  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {
											   
				 //  这里的将配置换成当前的方式不好，应该将curRoute_sendLocalAv放在m_var里。这样，就用同步可以确保数据一致性了.暂时不改
#if  0  //  2014/10/28
				 if  (  pSharedObj->curRoute_sendLocalAv.route.uiMsgRouteId  !=  pSharedObj->route_sendLocalAv.route.uiMsgRouteId  )  {			
					 CQySyncObj	syncObj;
					 if  (  !syncObj.sync(  pProcInfo1->cfg.mutexName_syncSendAv,  0  )  )  {
						 memcpy(  &pSharedObj->curRoute_sendLocalAv,  &pSharedObj->route_sendLocalAv,  sizeof(  pSharedObj->curRoute_sendLocalAv  )  );									   
						 #ifdef  __DEBUG__
								 traceLog((TCHAR*)  _T(  "toShareAudio: curRoute_sendLocalAv refreshed"  )  );
						 #endif
					 }
				 }
#endif
				
				 //							   
				 #ifdef  __DEBUG__
						 //  test为了测试
						 //  if  (  (  uiTranNo  %  30  )  )  break;
				 #endif
				
				 //if  (  !pSharedObjUsr->ucbNotSendData  )  
				 {
#if  0
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
					 //
				#if  0
					 if  (  postMsg2MgrFunc_mc(  pMisCnt,  NULL,  CONST_misMsgType_outputTask_toMix,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  pSharedObjUsr->iTaskId,  0,  (  char  *  )pReq,  lenInBytes,  0,  NULL,  NULL,  0,  uiChannelType,  pMsgBuf,  FALSE  )  )  {
					
						 traceLogA(  (char*)  "toShareAudio: postMsg2MgrFunc_mc failed"  );		//  
						
					 }
				#endif
					 int  tmpiRet;
					 //
					 int  msgLen  =  0;
	  		
					 //
					 if  (  makeMsg2MgrFunc_mc(  pMisCnt,  NULL,  CONST_misMsgType_task,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  pSharedObjUsr->iTaskId,  0,  (  char  *  )pReq,  lenInBytes,  0,  NULL,  NULL,  0,  uiChannelType,  pMsgBuf, &msgLen )  )  {
						 traceLog((TCHAR*)  _T(  "makeMsg2MgrFunc_mc failed"  )  );
					 }
					 			
					 if  (  msgLen  >  0  )  {
						 
						 //
						 pMsgBuf->task.bFrom_sharedObj  =  true;
						 pMsgBuf->task.index_sharedObj  =  pSharedObj->index_sharedObj;
						 //
						 if  (  (  tmpiRet  =  pProcInfo->processQ_media.qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsgBuf,  0  )  )  <=  0  )  {
							 #ifdef  __DEBUG__
									 //traceLog((TCHAR*)  _T(  "toShareAudio: postMsg2MgrFunc_mc: msg_task_toMix %s"  ),  tmpiRet  ?  _T(  "failed"  )  :  _T(  "not found"  )  );
							 #endif				
						 }
								
					 }


					 ////////////////////////////

					


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

		 //
		 //
		 //

		 //if  (  pbHaveMsgrs_sendLocalAv  )  *pbHaveMsgrs_sendLocalAv  =  bHaveMsgrs_sendLocalAv;

	}

	iErr  =  0;
errLabel:
	return  iErr;
}
#endif



//
