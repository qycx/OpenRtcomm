
#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<mmsystem.h>
#include	<mmreg.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"qmcAcm.h"
#include	"qmcVideoCapture.h"
//#include	"qmcVideoCapture_isCli.h"
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"
#include	"qmcCfg.h"
#include	"dumpAudio.h"

//#include	"qmcCommFunc_isCli.h"







 // int  initCompressVideo(  void  *  pProcInfoParam,  BITMAPINFO  *  pBmpInfo_input,  VIDEO_COMPRESSOR_CFG  *  pCompressor,  BOOL  bCapDev,  unsigned  short  usCapDriverIndex,  unsigned  int  uiBufSize_pData,  COMPRESS_VIDEO  *  pCompressVideo  )
__declspec(dllexport)  int  initCompressAudio(  MC_VAR_common  *  pProcInfo,  WAVEFORMATEX  *  pWf_input,  AUDIO_COMPRESSOR_CFG  *  pCompressor,  COMPRESS_AUDIO  *  p  )
{
	int							iErr				=	-1;
	//
	if  (  !pProcInfo  )  return  -1;
	//QY_MC					*	pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;//
	//if  (  !pQyMc  )  return  -1;
	CUS_MODULES				*	pCusModules			=	(  CUS_MODULES  *  )pProcInfo->getCusModules(  );
	if  (  !pCusModules  )  return  -1;
	//
	WAVEFORMATEX			*	pWfDst				=	NULL;
	WAVEFORMATEX			*	pWfPcm				=	NULL;

	HACMDRIVERID				hadid				=	NULL;

	MMRESULT					mmr					=	0;
	HACMDRIVER					had					=	NULL;
	HACMSTREAM					hstr1				=	NULL;
	HACMSTREAM					hstr2				=	NULL;


	if  (  !pWf_input  )  return  -1;
	if  (  p->bCompressInited  )  return  0;

	traceLogA(  (char*)  "initAudioCompress  enters"  );
	
	//  if  (  syncObj.sync(  pProcInfo->cfg.mutexName_syncAv  )  )  goto  errLabel;

	//
	p->ucTimeoutInS_showFrameInfoResp	=	MAX_ucTimeoutInS_showFrameInfoResp;
	//  p->uiBytesRecorded_perBlockAlign_expected  =  pWf_input->nSamplesPerSec  /  5;
	//  ³õÊ¼»¯¿ØÖÆ²ÎÊý
	p->ucTimeoutInS_showFrameInfoResp	=	MAX_ucTimeoutInS_showFrameInfoResp;

	//
	//  makeWaveFormat_pcm(  DEFAULT_audio_nChannels,  DEFAULT_audio_iHertz,  DEFAULT_audio_wBitsPerSample,  &p->waveFormatEx  );
	memcpy(  &p->ah_decompress.wfx,  pWf_input,  sizeof(  p->ah_decompress.wfx  )  );

	//  ×÷Ò»µãÐ£Ñé
	if  (  MAX_uiBytesRecorded_perBlockAlign  *  p->ah_decompress.wfx.nBlockAlign  >  CONST_bufSize_transferAudioData  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)"",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bufSize_transferAudioData %d too small, should be >= %d"  ),  CONST_bufSize_transferAudioData,  MAX_uiBytesRecorded_perBlockAlign  *  p->ah_decompress.wfx.nBlockAlign  );					
		goto  errLabel;
	}	
	if  (  !p->ah_decompress.wfx.nAvgBytesPerSec  )  goto  errLabel;


	/*
	unsigned  int  uiBytesRecorded_perBlockAlign;	uiBytesRecorded_perBlockAlign  =  pProcInfo->cfg.policy.audio.uiBytesRecorded_perBlockAlign;
	if  (  uiBytesRecorded_perBlockAlign  >=  MIN_uiBytesRecorded_perBlockAlign  &&  uiBytesRecorded_perBlockAlign  <=  MAX_uiBytesRecorded_perBlockAlign  )  {
		p->uiBytesRecorded_perBlockAlign_expected  =  uiBytesRecorded_perBlockAlign;
	}
	*/

	//  
	memcpy(  &p->compressor,  pCompressor,  sizeof(  p->compressor  )  );

	//  2015/02/13
	COMPRESS_AUDIO  *  pCompressAudio  =  p;
		//  2014/04/02		 
	//  2014/03/23	 	
	 GENERIC_Q_cfgEx	qCfgEx;	//  2012/11/10
	 GENERIC_Q_CFG		tmpCfg;

	TCHAR	tBuf[128];
#define		CONST_mutexNamePrefix_encA	_T(  "mtxEncA"  )
	int		tn  =  GetTickCount(  );
	int size  =  sizeof(  GENERIC_Q  );
	pCompressAudio->pInDataCacheQ  =  (  GENERIC_Q  *  )mymalloc(  size  );
	if  (  !pCompressAudio->pInDataCacheQ  )  goto  errLabel;
	memset(  pCompressAudio->pInDataCacheQ,  0,  size  );
#if  0
	size  =  sizeof(  GENERIC_Q  );
	pCompressAudio->pTmpDataQ  =  (  GENERIC_Q  *  )mymalloc(  size  );
	if  (  !pCompressAudio->pTmpDataQ  )  goto  errLabel;
	memset(  pCompressAudio->pTmpDataQ,  0,  size  );
#endif

	//
	memset(  &tmpCfg,  0,  sizeof(  tmpCfg  )  );
	_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-in-%d"  ),  CONST_mutexNamePrefix_encA,  tn  );
	_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-in-%d"  ),  CONST_mutexNamePrefix_encA,  tn  );
	tmpCfg.uiMaxQNodes  =  100;
	
	memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );		
	memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );	
	qCfgEx.pfQElemNewEx  =  mallocMemory;
	qCfgEx.pfQElemNew  =  mymalloc;
	qCfgEx.pfQElemFreeEx  =  freeMemory;
	qCfgEx.pfQElemFree  =  myfree;
	qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myPLAY_AUDIO_DATA;
	qCfgEx.pfQElemRemove  =  ( PF_qElemRemove  )clean_myPLAY_AUDIO_DATA;

	if  (  initGenericQ(  &qCfgEx,  (  GENERIC_Q  *  )pCompressAudio->pInDataCacheQ  )  )  goto  errLabel;

	
#if  0
	//
	memset(  &tmpCfg,  0,  sizeof(  tmpCfg  )  );
	_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-tmp-%d"  ),  CONST_mutexNamePrefix_encA,  tn  );
	_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-tmp-%d"  ),  CONST_mutexNamePrefix_encA,  tn  );
	tmpCfg.uiMaxQNodes  =  100;
	
	memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );		
	memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );	
	qCfgEx.pfQElemNewEx  =  mallocMemory;
	qCfgEx.pfQElemNew  =  mymalloc;
	qCfgEx.pfQElemFreeEx  =  freeMemory;
	qCfgEx.pfQElemFree  =  myfree;
	qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myPLAY_AUDIO_DATA;
	qCfgEx.pfQElemRemove  =  ( PF_qElemRemove  )clean_myPLAY_AUDIO_DATA;

	if  (  initGenericQ(  &qCfgEx,  pCompressAudio->pTmpDataQ  )  )  goto  errLabel;
#endif

	//
	size  =  sizeof(  myPLAY_AUDIO_DATA  );
	pCompressAudio->pCurPkt  =  (  myPLAY_AUDIO_DATA  *  )mymalloc(  size  );
	if  (  !pCompressAudio->pCurPkt  )  goto  errLabel;
	memset(  pCompressAudio->pCurPkt,  0,  size  );


	//
	memset(&pCompressAudio->encInfo, 0, sizeof(pCompressAudio->encInfo));



	////////////////////////////////////
#if  0
	p->uiTranNo_openAvDev  =  getuiNextTranNo(  0,  0,  0  );
#endif
	p->uiTranNo_openAvDev_org  =  getuiNextTranNo(  0,  MAX_sharedObjUsrs,  0  );	//  2010/09/04

	//
	if  (  p->compressor.common.ucCompressors  ==  CONST_audioCompressors_acm  )  {

#ifndef  __WINCE__

		//
		hadid  =  find_driver(  p->compressor.wf_compress.wFormatTag,  p->compressor.wf_compress.nChannels,  p->compressor.wf_compress.nSamplesPerSec,  p->compressor.wf_compress.wBitsPerSample  );
		if  (  hadid  ==  NULL  )  {
			traceLogA(  (char*)  "initAudioCompress failed. No driver found."  );
			goto  errLabel;
		}
		traceLogA(  (char*)  "Driver found ( hadid: %4.4lxh)\n",  hadid  );

		//  ÕÒµ½¸ø¶¨±êÇ©µÄ¶ÔÓ¦µÄ¸ñÊ½	
		pWfDst	=	get_driver_format(  hadid,  p->compressor.wf_compress.wFormatTag,  p->compressor.wf_compress.nChannels,  p->compressor.wf_compress.nSamplesPerSec,  p->compressor.wf_compress.wBitsPerSample  );
		if  (  !pWfDst  )  goto  errLabel;
		traceLogA(  (char*)  "Driver format:%u bits,  %lu samples ps, %d channels\n ",  pWfDst->wBitsPerSample,  pWfDst->nSamplesPerSec,  pWfDst->nChannels  );

		if  (  pWfDst->cbSize  >  sizeof(  p->ah_compress.bExtraData  )  )  {
			traceLogA(  (char*)  "initCompressAudio failed: pWfDst->cbSize %d > sizeof(  bExtraData  ) %d",  pWfDst->cbSize,  sizeof(  p->ah_compress.bExtraData  )  );
			goto  errLabel;
		}
		memcpy(  &p->ah_compress.wfx,  pWfDst,  sizeof(  p->ah_compress.wfx  )  +  pWfDst->cbSize  );

		//  ÕÒµ½¸ø¶¨±êÇ©¶ÔÓ¦µÄÇý¶¯
		pWfPcm	=	get_driver_suggestedFormat(  hadid,	pWfDst,  WAVE_FORMAT_PCM,  p->compressor.wf_compress.nChannels,  p->compressor.wf_compress.nSamplesPerSec,  p->compressor.wf_compress.wBitsPerSample  );
		if  (  !pWfPcm	)  goto  errLabel;
		traceLogA(  (char*)  "PCM  format: %u bits,  %lu samples ps, %d channels\n",  pWfPcm->wBitsPerSample,  pWfPcm->nSamplesPerSec,  pWfPcm->nChannels  );
		
		if  (  pWfPcm->cbSize  >  sizeof(  p->ah_pcm.bExtraData  )  )  {
			traceLogA(  (char*)  "initCompressAudio failed: pWfPcm->cbSize %d >  sizeof(  bExtraData  ) %d",  pWfPcm->cbSize,  sizeof(  p->ah_pcm.bExtraData  )  );
			goto  errLabel;
		}
		memcpy(  &p->ah_pcm.wfx,  pWfPcm,  sizeof(  p->ah_pcm.wfx  )  +  pWfPcm->cbSize  );

		//  2009/07/14
		try  {
			 mmr	=  acmStreamOpen(  &hstr1,  had,  &p->ah_decompress.wfx,  &p->ah_pcm.wfx,  NULL,  NULL,  0,  ACM_STREAMOPENF_NONREALTIME  );
			}
#ifdef  __useMfc__
		catch  (  CException  *  e  )  {
			   e->Delete(  );
			   mmr  =  -1;
		}
#endif
		catch  (  ...  )  {
			   mmr  =  -1;
		}
		if  (  mmr  )  {
			hstr1  =  NULL;  goto  errLabel;
		}			
		try  {
			 mmr	=  acmStreamOpen(  &hstr2,  had,  &p->ah_pcm.wfx,  &p->ah_compress.wfx,  NULL,  NULL,  0,  ACM_STREAMOPENF_NONREALTIME  );
			}
#ifdef  __useMfc__
		catch  (  CException  *  e  )  {
			   e->Delete(  );
			   mmr  =  -1;
		}
#endif
		catch  (  ...  )  {
			   mmr  =  -1;
		}
		if  (  mmr  )  {
			hstr2  =  NULL;  goto  errLabel;
		}

		p->u.acm.hadid  =  hadid;
		p->u.acm.hstr1  =  hstr1;	hstr1  =  NULL;
		p->u.acm.hstr2  =  hstr2;	hstr2  =  NULL;

#else

		switch  (  p->compressor.wf_compress.wFormatTag  )  {
				case  WAVE_FORMAT_GSM610:  {
					  GSM610WAVEFORMAT	wfDst;
					  memset(  &wfDst,  0,  sizeof(  wfDst  )  );
					  wfDst.wfx.wFormatTag  =  WAVE_FORMAT_GSM610;
					  wfDst.wfx.nChannels  =  1;
					  wfDst.wfx.nSamplesPerSec  =  8000;
					  wfDst.wfx.nAvgBytesPerSec  =  1625;
					  wfDst.wfx.nBlockAlign  =  65;
					  wfDst.wfx.wBitsPerSample  =  0;
					  wfDst.wfx.cbSize  =  2;
					  wfDst.wSamplesPerBlock  =  320;

					  memcpy(  &p->ah_compress.wfx,  &wfDst,  sizeof(  p->ah_compress.wfx  )  +  wfDst.wfx.cbSize  );			
					  }
					  break;
					#if  0
						case  WAVE_FORMAT_MPEGLAYER3:  {
							  MPEGLAYER3WAVEFORMAT	wfDst;
							  memset(  &wfDst,  0,  sizeof(  wfDst  )  );
							  wfDst.wfx.wFormatTag  =  WAVE_FORMAT_MPEGLAYER3;
							  wfDst.wfx.nChannels  =  1;
							  wfDst.wfx.nSamplesPerSec  =  8000;
							  //  wfDst.wfx.nAvgBytesPerSec  =  ;
							  wfDst.wfx.nBlockAlign  =  1;
							  wfDst.wfx.wBitsPerSample  =  0;
							  //  wfDst.wfx.cbSize  =  ;

							  fillIn_wfx_mp3(  sizeof(  wfDst  ),  192000,  (  WAVEFORMATEX  *  )&wfDst  );  

							  memcpy(  &p->ah_compress.wfx,  &wfDst,  sizeof(  p->ah_compress.wfx  )  +  wfDst.wfx.cbSize  );			

							  }
							  break;				
					#endif
				default:
					   traceLog(  _T(  "initCompressAudio failed: wFormatTag not supported"  )  );
					   goto  errLabel;
		}
		if  (  !p->ah_compress.wfx.wFormatTag  )  {
			traceLog(  _T(  "initCompressAudio failed, ah_compress not filled"  )  );
			goto  errLabel;
		}
			
#endif

		}
	else  if  (  p->compressor.common.ucCompressors  ==  CONST_audioCompressors_dmo  )  {

			  if  (  initCompressAudio_dmo(  pProcInfo->pQyMc,  &p->compressor,  &p->ah_decompress,  &p->ah_compress,  &p->u.dmo  )  )  goto  errLabel;

			  }
	else  {
		   CUS_MODULE_U	*	pModule	=	NULL;
		   unsigned  int		uiModuleType	=	0;				//  2012/09/09


		   switch  (  p->compressor.common.ucCompressors  )  {
#if  0
				   case  CONST_audioCompressors_ipp:
					     //
					     uiModuleType  =  CONST_moduleType_ipp;
						 //
					     pModule	=	pCusModules->pIpp;			
						 break;
#endif 
						 //
				   case CONST_audioCompressors_ffmpeg:
					     //
					     uiModuleType=CONST_moduleType_ffmpeg;
					     pModule=pCusModules->pFfmpeg;
						 break;
				   case  CONST_audioCompressors_lyra:
					   uiModuleType = CONST_moduleType_lyra;
					   pModule = pCusModules->pLyra;
					   break;
				   case  CONST_audioCompressors_aac:
					   uiModuleType = CONST_moduleType_aac;
					   pModule = pCusModules->pAAC;;
					   break;

						 //  2016/12/05
				   case  CONST_audioCompressors_vorbis:
					     //
					     uiModuleType  =  CONST_moduleType_qdc_vorbis_enc;
						 //
						 pModule  =  pCusModules->pQdc_vorbis_enc;
					     break;
				   case  CONST_audioCompressors_custom:
					     //
					     uiModuleType  =  CONST_moduleType_compress;
					     //
					     pModule	=	getCusModule(  pCusModules,  CONST_moduleType_compress  );
						 break;
				   default:
						#ifdef  __DEBUG__
					   traceLogA(  (char*)  "initCompressAudio: ucCompressors err: %d",  p->compressor.common.ucCompressors  );
						#endif
					   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCompressAudio: ucCompressors err: %d"  ),  p->compressor.common.ucCompressors  );
						goto  errLabel;
						break;
		   }

		   //
		   M_getCompressModule(  pCusModules,  uiModuleType,  pModule  );	//  2012/09/09
		   if  (  !pModule  ||  !pModule->compress.pf_qdcInitCompressAudio  )  goto  errLabel;
		   p->uiModuleType_toEnc  =  uiModuleType;


		   ///////////////////////////////
		   //  2016/12/09
		   COMPRESS_AUDIO  *  pCompressAudio  =  p;
		   		  
		  //  2014/04/02
		  AUDIO_COMPRESSOR_CFG  compressor;			 
		  memcpy(  &compressor,  &pCompressAudio->compressor,  sizeof(  compressor  )  );		  		  
		  compressor.common.pCurPkt  =  pCompressAudio->pCurPkt;
		  compressor.common.size_pCurPkt  =  sizeof(  pCompressAudio->pCurPkt[0]  );
		  //
		  compressor.common.pInDataCacheQ  =  pCompressAudio->pInDataCacheQ;
		  //
		  compressor.common.pAudioQ2  =  pCompressAudio->compressor.common.pAudioQ2;	//  2014/04/03. pVideoQ2这时尚未初始化。等数据流运行时，pVideoQ2已经ready
		  if  (  !compressor.common.pAudioQ2  )  {
			  showInfo_open0(  0,  0,  _T(  "initCompressVideo failed, pVideoQ2 is null"  )  );
			  goto  errLabel;
		  }
		  //compressor.common.pTmpDataQ  =  pCompressAudio->pTmpDataQ;
		  //
		  compressor.common.pParent_transform  =  pCompressAudio->compressor.common.pParent_transform;
		  if  (  !compressor.common.pParent_transform  )  {
			  goto  errLabel;
		  }
		  compressor.common.uiTransformType_pParent  =  CONST_uiTransformType_encAudio;
		  //
		  compressor.common.pf_bTransformAudioQuit  =  bCapAudioQuit;


		  //
		  //  compressor.common.pf_transformGetSpsPps  =  capBmpGetSpsPps;
		  compressor.common.pf_transformGetWfx  =  (  PF_commonHandler  )capAudioGetWfx;

		  
		  //
		  compressor.common.pf_getNextAPkt  =  (  PF_commonHandler  )getNextAPkt;

		  //compressor.common.pf_parseVPkt_i  =  enc_parseOrgVPkt_i;
		  compressor.common.pf_parseDecAPkt_o  =  parseDecAPkt_o;


		  compressor.common.pf_detachPkt  =  detachAPkt;
		  compressor.common.pf_clean_myPLAY_AUDIO_DATA  =  (  PF_clean_myPLAY_AUDIO_DATA  )clean_myPLAY_AUDIO_DATA;


		  //
		  compressor.common.enc.pf_smplPCMReader_LoadNextFrame  =  smplPCMReader_LoadNextFrame;
		  compressor.common.enc.pf_doPostEnc  =  doPostEnc_audio;

		  //  2014/03/29
		  //  compressor.common.ucHardwareAccl  =  pQmcCfg->policy.ucHardwareAccl;

		  //
		  QMC_cfg * pQmcCfg=(QMC_cfg*)pProcInfo->get_qmc_cfg();
		  if(pQmcCfg ) {
			  if(pQmcCfg->debugStatusInfo.ucb__Dump_mp3_enc__){
				  dumpAudio_init();
			  }
		  }


		  ////////////////////////
		  
		  //
		  p->u.qoi.myQoi.common.uiType  =  CONST_qoiType_encA;
		  //			
		  //  2016/04/26							
		  pProcInfo->set_qoi_funcs(  &pCompressAudio->u.qoi.myQoi  );
		  
		  //
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "initCompressA: fmt 0x%x, compressor.bitrateInKbps %d"  ),  (  int  )pCompressor->wf_compress.wFormatTag,  compressor.common.iAvgBitrateInKbps  );
		  showInfo_open0(  0,  0,  tBuf  );

		  //
		  if  (  pModule->compress.pf_qdcInitCompressAudio(  &compressor,  &p->ah_decompress,  &p->ah_compress,  &p->u.qoi.myQoi.common  )  )  goto  errLabel;

		  //  
		  if  (  p->compressor.common.ucCompressors  ==  CONST_audioCompressors_vorbis  )  {
			  if  (  !p->u.qoi.pf_qdcGetVorbisHeaders  )  {
				  goto  errLabel;
			  }
			  //
			  memset(  &p->ah_stream,  0,  sizeof(  p->ah_stream  )  );		
			  AH_stream  *  pAh_stream  =  &p->ah_stream;
			  char  buf0[256]  =  "";
			  char  buf1[256]  =  "";
			  char  buf2[5  *  1024]  =  "";
			  //
			  unsigned  int  header0Len  =  sizeof(  buf0  );
			  unsigned  int  header1Len  =  sizeof(  buf1  );
			  unsigned  int  header2Len  =  sizeof(  buf2  );
			  if  (  p->u.qoi.pf_qdcGetVorbisHeaders(  &p->u.qoi.myQoi.common,  buf0,  &header0Len,  buf1,  &header1Len,  buf2,  &header2Len  )  )  {
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCompressAudio failed, qdcGetVorbisHeaders failed."  )  );
					  goto  errLabel;  				
			  }
			  //
			  if  (  header0Len  +  header1Len  +  header2Len  >  sizeof(  p->ah_stream.buf  )  )  goto  errLabel;
			  //				
			  int  iPos  =  0;
			  pAh_stream->mems[0].usLen  =  header0Len;  memcpy(  pAh_stream->buf,  buf0,  header0Len  );
			  iPos  +=  header0Len;
			  pAh_stream->mems[1].usLen  =  header1Len;  memcpy(  pAh_stream->buf  +  iPos,  buf1,  header1Len  );
			  iPos  +=  header1Len;
			  pAh_stream->mems[2].usLen  =  header2Len;  memcpy(  pAh_stream->buf  +  iPos,  buf2,  header2Len  );
			  //
			  //pVh_stream->dwFourcc  =  pCompressVideo->vh_compress.bih.biCompression;				
			  //  2014/05/02				  
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qdcGetSpsPps: header0Len %d, header1Len %d, header2Len %d"  ),  header0Len,  header1Len,  header2Len  );

			  //
#ifdef  __DEBUG__
		#if  10
			  int  iii;
			  for  (  iii  =  0;  iii  <  58;  iii  ++  )  {
				   TCHAR  tt[128];
				   _sntprintf(  tt,  mycountof(  tt  ),  _T(  "header[%d] %02x\n"  ),  iii,  (  unsigned  char  )pAh_stream->buf[iii]  );
				   OutputDebugString(  tt  );
			  }
			  iii  =  iii;
		#endif
#endif

		  }

	}
#if  0
	else  if  (  p->compressor.ucCompressors  ==  CONST_audioCompressors_custom  )  {
			  CUS_MODULE_U	*	pModule	=	getCusModule(  pProcInfo->pQyMc,  CONST_moduleType_compress  );
			  if  (  !pModule  ||  !pModule->compress.pf_qdcInitCompressAudio  )  goto  errLabel;
			  if  (  pModule->compress.pf_qdcInitCompressAudio(  &p->compressor,  &p->ah_decompress,  &p->ah_compress,  &p->u.custom  )  )  goto  errLabel;
			  }
	else  {
		  traceLogA(  (char*)  "initCompressAudio failed: unprocessed ucCompressors %d",  p->compressor.ucCompressors  );
		  goto  errLabel;
	}
#endif

	//
	size  =  sizeof(  TRANSFER_AUDIO_DATA  );
	p->pReqCache  =  (  TRANSFER_AUDIO_DATA  *  )mymalloc(  size  );
	if  (  !p->pReqCache  )  goto  errLabel;
	memset(  p->pReqCache,  0,  size  );


	p->bCompressInited  =  TRUE;

	iErr  =  0;

errLabel:

	if  (  hstr1  )  {
		acmStreamClose(  hstr1,  0  );	hstr1	=	NULL;
	}
	if  (  hstr2  )  {
		acmStreamClose(  hstr2,  0  );	hstr2	=	NULL;
	}	

	if  (  pWfDst  )  free(  pWfDst  );
	if  (  pWfPcm  )  free(  pWfPcm  );

	if  (  iErr  )  {
		exitCompressAudio(  pProcInfo,  p  );
	}

	traceLogA(  (char*)  "initAudioCompress  leaves %s",  iErr  ?  "failed."  :  "ok"  );

	return  iErr;
}

__declspec(dllexport)  int  exitCompressAudio(  MC_VAR_common  *  pProcInfo,  COMPRESS_AUDIO  *  pCompressAudio  )
{
	int		iErr	=	-1;
	//QY_MC	*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;//
	//  CQySyncObj			syncObj;
	if  (  !pProcInfo  )  return  -1;
	CUS_MODULES  *  pCusModules  =  (  CUS_MODULES  *  )pProcInfo->getCusModules(  );
	if  (  !pCusModules  )  return  -1;


	traceLogA(  (char*)  "exitAudioCompress  enters"  );

	//  if  (  syncObj.sync(  pProcInfo->cfg.mutexName_syncAv  )  )  goto  errLabel;

	if  (  !pCompressAudio->compressor.common.ucCompressors  )  ;
	else  if  (  pCompressAudio->compressor.common.ucCompressors  ==  CONST_audioCompressors_acm  )  {

			  #ifndef  __WINCE__
					   if  (  pCompressAudio->u.acm.hstr1  )  {
						   acmStreamClose(  pCompressAudio->u.acm.hstr1,  0  );	pCompressAudio->u.acm.hstr1	=	NULL;
					   }
					   if  (  pCompressAudio->u.acm.hstr2  )  {
						   acmStreamClose(  pCompressAudio->u.acm.hstr2,  0  );	pCompressAudio->u.acm.hstr2	=	NULL;	
					   }
			  #endif

			  }
	else  if  (  pCompressAudio->compressor.common.ucCompressors  ==  CONST_audioCompressors_dmo  )  {
			  exitCompressAudio_dmo(  &pCompressAudio->u.dmo  );
			  }
	else  {
		   CUS_MODULE_U	*	pModule  =  NULL;
		   /*
		   switch  (  pCompressAudio->compressor.common.ucCompressors  )  {
				   case  CONST_audioCompressors_ipp:
					     pModule  =  pCusModules->pIpp;
						 break;
				   case  CONST_audioCompressors_vorbis:	//  2016/12/05
					     pModule  =  pCusModules->pQdc_vorbis_enc;
					     break;
				   case  CONST_audioCompressors_custom:
					     pModule  =  getCusModule(  pCusModules,  CONST_moduleType_compress  );
					     break;
				   default:
					   traceLogA(  (char*)  "exitCompressAudio: ucCompressors err: %d",  pCompressAudio->compressor.common.ucCompressors  );
					   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "exitCompressAudio: ucCompressors err: %d"  ),  pCompressAudio->compressor.common.ucCompressors  );
						  break;
		   }
		   */
		   M_getCompressModule(pCusModules,pCompressAudio->uiModuleType_toEnc,pModule);

		   if  (  pModule  &&  pModule->compress.pf_qdcExitCompressAudio  )  {
			   pModule->compress.pf_qdcExitCompressAudio(  &pCompressAudio->u.qoi.myQoi.common  );
		   }

		   //
		   QMC_cfg * pCfg=(QMC_cfg*)pProcInfo->get_qmc_cfg();
		   if ( pCfg){
			   if(pCfg->debugStatusInfo.ucb__Dump_mp3_enc__){
				   dumpAudio_exit();
			   }
		   }
		  
	}


	//  2015/02/13
	//  2014/03/25
	 clean_myPLAY_AUDIO_DATA(  pCompressAudio->pCurPkt,  _T(  "exitCompressAudio"  )  );
	 MACRO_safeFree(  pCompressAudio->pCurPkt  );

	//	 
	 //  2014/03/24
	 if  (  pCompressAudio->pInDataCacheQ  )  {
		 genericQFree(  pCompressAudio->pInDataCacheQ  );  pCompressAudio->pInDataCacheQ  =  NULL;
	 }
#if  0
	 if  (  pCompressAudio->pTmpDataQ  )  {
		 genericQFree(  pCompressAudio->pTmpDataQ  );  pCompressAudio->pTmpDataQ  =  NULL;
	 }
#endif

	//
	if  (  pCompressAudio->pReqCache  )  {	//  2009/02/11
		free(  pCompressAudio->pReqCache  );  pCompressAudio->pReqCache  =  NULL;
	}

	if  (  pCompressAudio->pDstBuf  )  {
		free(  pCompressAudio->pDstBuf  );  pCompressAudio->pDstBuf  =  NULL;
	}
	if  (  pCompressAudio->pPcmBuf  )  {
		free(  pCompressAudio->pPcmBuf  );  pCompressAudio->pPcmBuf  =  NULL;
	}

	//  if  (  p->pWfDst  )  {
	//  	free(  p->pWfDst  );  p->pWfDst  =  NULL;
	//  }
	//  if  (  p->pWfPcm  )  {
	//  	free(  p->pWfPcm  );  p->pWfPcm  =  NULL;
	//  }

	pCompressAudio->bCompressInited  =  FALSE;
	memset(  pCompressAudio,  0,  sizeof(  pCompressAudio[0]  )  );

	iErr  =  0;

//  errLabel:

	traceLogA(  (char*)  "exitAudioCompress  leaves %s",  iErr  ?  "failed."  :  "ok"  );

	return  iErr;
}
