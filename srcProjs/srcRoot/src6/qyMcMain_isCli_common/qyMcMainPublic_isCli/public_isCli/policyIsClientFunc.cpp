
#include	"stdafx.h"
#include	<tchar.h>
#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<msacm.h>
#endif

#include	<shlobj.h>

#include	"qyMcMainCommon.h"
//#include	"myresource.h"

#include	"myfourcc.h"


#include	"tmpCeLib.h"
#include	"policyAvParams.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qmcDmoPublic.h"

#include	"qyOpenShellCommon.h"
#include	"policyIsClientFunc.h"
#include	"funcsForIsCliHelp.h"


 int  get_pcm_forAcm(  unsigned  int  uiCapType,  WAVEFORMATEX  *  pWfx  )
{
	switch  (  uiCapType  )  {
			case  CONST_capType_av:
				  makeWaveFormat_pcm(  DEFAULT_nChannels_pcm_av,  DEFAULT_iHertz_pcm_av,  DEFAULT_wBitsPerSample_pcm_av,  pWfx  );
				  break;
			case  CONST_capType_mediaFile:
				  makeWaveFormat_pcm(  DEFAULT_nChannels_pcm_mediaFile,  DEFAULT_iHertz_pcm_mediaFile,  DEFAULT_wBitsPerSample_pcm_mediaFile,  pWfx  );
				  break;
			case  CONST_capType_mediaDevice:
				  makeWaveFormat_pcm(  DEFAULT_nChannels_pcm_mediaDevice,  DEFAULT_iHertz_pcm_mediaDevice,  DEFAULT_wBitsPerSample_pcm_mediaDevice,  pWfx  );
				  break;
			default:
					break;
	}

	return  0;				  
}

 //
 //  2016/12/05  
 int  get_pcm_forVorbis(  unsigned  int  uiCapType,  WAVEFORMATEX  *  pWfx  )
 {
	 return  get_pcm_forAcm(  uiCapType,  pWfx  );
 }



 //  2014/08/30  
 int  get_pcm_forIpp(  unsigned  int  uiCapType,  WAVEFORMATEX  *  pWfx  )
 {
	 return  get_pcm_forAcm(  uiCapType,  pWfx  );
 }

 //
 //  2014/08/30  
 int  get_pcm_forDmo(  unsigned  int  uiCapType,  WAVEFORMATEX  *  pWfx  )
 {
	 return  get_pcm_forAcm(  uiCapType,  pWfx  );
 }



 //
 int  getAudioCompressorCfg_default_acm(  unsigned  int  uiCapType,  AUDIO_COMPRESSOR_CFG  *  pCfg  )
{
	memset(  pCfg,  0,  sizeof(  pCfg  )  );

	pCfg->common.ucCompressors  =  CONST_audioCompressors_acm;

	switch  (  uiCapType  )  {
			case  CONST_capType_screen:
				  break;			
			case  CONST_capType_mediaFile:
				  //  2009/05/05
				  pCfg->wf_compress.wFormatTag  =  DEFAULT_wFormatTag_acm_mediaFile;
				  pCfg->wf_compress.nChannels  =  DEFAULT_nChannels_acm_mediaFile;
				  pCfg->wf_compress.nSamplesPerSec  =  DEFAULT_nSamplesPerSec_acm_mediaFile;
				  pCfg->wf_compress.wBitsPerSample  =  DEFAULT_wBitsPerSample_acm_mediaFile;
				  //
				  break;
			case  CONST_capType_mediaDevice:
				  //  2009/05/05
				  pCfg->wf_compress.wFormatTag  =  DEFAULT_wFormatTag_acm_mediaDevice;
				  pCfg->wf_compress.nChannels  =  DEFAULT_nChannels_acm_mediaDevice;
				  pCfg->wf_compress.nSamplesPerSec  =  DEFAULT_nSamplesPerSec_acm_mediaDevice;
				  pCfg->wf_compress.wBitsPerSample  =  DEFAULT_wBitsPerSample_acm_mediaDevice;
				  //
				  break;
			case  CONST_capType_av:
				  pCfg->wf_compress.wFormatTag  =  DEFAULT_wFormatTag_acm_av;
				  pCfg->wf_compress.nChannels  =  DEFAULT_nChannels_acm_av;
				  pCfg->wf_compress.nSamplesPerSec  =  DEFAULT_nSamplesPerSec_acm_av;
				  pCfg->wf_compress.wBitsPerSample  =  DEFAULT_wBitsPerSample_acm_av;
				  //
				  break;
			default:
					break;
	}
	
	get_pcm_forAcm(  uiCapType,  &pCfg->wf_decompress_default  );

	return  0;
}


 int  getAudioCompressorCfg_default_dmo(  unsigned  int  uiCapType,  AUDIO_COMPRESSOR_CFG  *  pCfg  )
{
	memset(  pCfg,  0,  sizeof(  pCfg  )  );

	pCfg->common.ucCompressors  =  CONST_audioCompressors_dmo;

	switch  (  uiCapType  )  {
			case  CONST_capType_screen:
				  break;			
			case  CONST_capType_mediaFile:
				  pCfg->wf_compress.wFormatTag  =  DEFAULT_wFormatTag_dmo_mediaFile;
				  pCfg->wf_compress.nChannels  =  DEFAULT_nChannels_dmo_mediaFile;
				  pCfg->wf_compress.nSamplesPerSec  =  DEFAULT_nSamplesPerSec_dmo_mediaFile;
				  pCfg->wf_compress.wBitsPerSample  =  DEFAULT_wBitsPerSample_dmo_mediaFile;				  
				  break;
			case  CONST_capType_mediaDevice:
				  pCfg->wf_compress.wFormatTag  =  DEFAULT_wFormatTag_dmo_mediaDevice;
				  pCfg->wf_compress.nChannels  =  DEFAULT_nChannels_dmo_mediaDevice;
				  pCfg->wf_compress.nSamplesPerSec  =  DEFAULT_nSamplesPerSec_dmo_mediaDevice;
				  pCfg->wf_compress.wBitsPerSample  =  DEFAULT_wBitsPerSample_dmo_mediaDevice;
				  break;
			case  CONST_capType_av:
				  pCfg->wf_compress.wFormatTag  =  DEFAULT_wFormatTag_dmo_av;
				  pCfg->wf_compress.nChannels  =  DEFAULT_nChannels_dmo_av;
				  pCfg->wf_compress.nSamplesPerSec  =  DEFAULT_nSamplesPerSec_dmo_av;
				  pCfg->wf_compress.wBitsPerSample  =  DEFAULT_wBitsPerSample_dmo_av;
				  //
				  break;
			default:
					break;
	}

	//  2016/12/25
	//  makeWaveFormat_pcm(  pCfg->wf_compress.nChannels,  pCfg->wf_compress.nSamplesPerSec,  pCfg->wf_compress.wBitsPerSample,  &pCfg->wf_decompress_default  );
	get_pcm_forDmo(  uiCapType,  &pCfg->wf_decompress_default  );

	return  0;
}

 //  2016/12/05
 int  getAudioCompressorCfg_default_vorbis(  unsigned  int  uiCapType,  AUDIO_COMPRESSOR_CFG  *  pCfg  )				//  2012/01/20
{
	int		iErr	=	-1;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	memset(  pCfg,  0,  sizeof(  pCfg  )  );

	pCfg->common.ucCompressors  =  CONST_audioCompressors_vorbis;


	CUS_MODULE_U	*  pModule	=	pFuncs->pf_getCusModule(  &pQyMc->cusModules,  CONST_moduleType_qdc_vorbis_enc,  0,  0,  NULL  );
	if  (  !pModule  )  goto  errLabel;
	if  (  !pModule->compress.ucbInited  )  goto  errLabel;

	if  (  !pModule->compress.pf_qdcGetCompressAudioCfg  )  goto  errLabel;
	if  (  pModule->compress.pf_qdcGetCompressAudioCfg(  &pCfg->wf_decompress_default,  &pCfg->wf_compress  )  )  goto  errLabel;
	
	//  2014/08/29
	get_pcm_forVorbis(  uiCapType,  &pCfg->wf_decompress_default  );

	//
	AUDIO_COMPRESSOR_CFG* pAudioCompressor;pAudioCompressor = pCfg;
	//
	pAudioCompressor->uiBytesRecorded_perBlockAlign  =  MACRO_getuiBytesRecorded_perBlockAlign(  *pAudioCompressor,  &pAudioCompressor->wf_decompress_default  );					
	//
	WORD  wFormatTag; wFormatTag = pAudioCompressor->wf_compress.wFormatTag;
	memset(  &pAudioCompressor->wf_compress,  0,  sizeof(  pAudioCompressor->wf_compress  )  );	//  2011/02/02
	pAudioCompressor->wf_compress.wFormatTag  =  wFormatTag;
	pAudioCompressor->wf_compress.nChannels  =  pAudioCompressor->wf_decompress_default.nChannels;			  														  
	pAudioCompressor->wf_compress.nSamplesPerSec  =  pAudioCompressor->wf_decompress_default.nSamplesPerSec;
	pAudioCompressor->wf_compress.wBitsPerSample  =  pAudioCompressor->wf_decompress_default.wBitsPerSample;															

	//
	iErr  =  0;
errLabel:
	return  iErr;
}



 //
 int  getAudioCompressorCfg_default_ipp(  unsigned  int  uiCapType,  AUDIO_COMPRESSOR_CFG  *  pCfg  )				//  2012/01/20
{
	int		iErr	=	-1;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	memset(  pCfg,  0,  sizeof(  pCfg  )  );

	pCfg->common.ucCompressors  =  CONST_audioCompressors_ipp;


	CUS_MODULE_U	*  pModule	=	pFuncs->pf_getCusModule(  &pQyMc->cusModules,  CONST_moduleType_ipp,  0,  0,  NULL  );
	if  (  !pModule  )  goto  errLabel;
	if  (  !pModule->compress.ucbInited  )  goto  errLabel;

	if  (  !pModule->compress.pf_qdcGetCompressAudioCfg  )  goto  errLabel;
	if  (  pModule->compress.pf_qdcGetCompressAudioCfg(  &pCfg->wf_decompress_default,  &pCfg->wf_compress  )  )  goto  errLabel;
	
	//  2014/08/29
	get_pcm_forIpp(  uiCapType,  &pCfg->wf_decompress_default  );

	//
	AUDIO_COMPRESSOR_CFG* pAudioCompressor;pAudioCompressor = pCfg;
	//
	pAudioCompressor->uiBytesRecorded_perBlockAlign  =  MACRO_getuiBytesRecorded_perBlockAlign(  *pAudioCompressor,  &pAudioCompressor->wf_decompress_default  );					
	//
	WORD  wFormatTag;wFormatTag = pAudioCompressor->wf_compress.wFormatTag;
	memset(  &pAudioCompressor->wf_compress,  0,  sizeof(  pAudioCompressor->wf_compress  )  );	//  2011/02/02
	pAudioCompressor->wf_compress.wFormatTag  =  wFormatTag;
	pAudioCompressor->wf_compress.nChannels  =  pAudioCompressor->wf_decompress_default.nChannels;			  														  
	pAudioCompressor->wf_compress.nSamplesPerSec  =  pAudioCompressor->wf_decompress_default.nSamplesPerSec;
	pAudioCompressor->wf_compress.wBitsPerSample  =  pAudioCompressor->wf_decompress_default.wBitsPerSample;															

	//
	iErr  =  0;
errLabel:
	return  iErr;
}


 //
  int  getAudioCompressorCfg_default_ffmpeg(  unsigned  int  uiCapType,  AUDIO_COMPRESSOR_CFG  *  pCfg  )				//  2012/01/20
{
	int		iErr	=	-1;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	memset(  pCfg,  0,  sizeof(  pCfg  )  );

	pCfg->common.ucCompressors  =  CONST_audioCompressors_ffmpeg;


	CUS_MODULE_U	*  pModule	=	pFuncs->pf_getCusModule(  &pQyMc->cusModules,  CONST_moduleType_ffmpeg,  0,  0,  NULL  );
	if  (  !pModule  )  goto  errLabel;
	if (!pModule->compress.ucbInited) {
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("getAudioCompressorCfg_default_ffmpeg failed, pModule->compress.ucbInited is false"));
#endif
		goto  errLabel;
	}

	/*
	if  (  !pModule->compress.pf_qdcGetCompressAudioCfg  )  goto  errLabel;
	if  (  pModule->compress.pf_qdcGetCompressAudioCfg(  &pCfg->wf_decompress_default,  &pCfg->wf_compress  )  )  goto  errLabel;
	*/
	pCfg->wf_compress.wFormatTag=WAVE_FORMAT_MPEGLAYER3;
	
	//  2014/08/29
	get_pcm_forIpp(  uiCapType,  &pCfg->wf_decompress_default  );

	//
	AUDIO_COMPRESSOR_CFG* pAudioCompressor;pAudioCompressor = pCfg;
	//
	pAudioCompressor->uiBytesRecorded_perBlockAlign  =  MACRO_getuiBytesRecorded_perBlockAlign(  *pAudioCompressor,  &pAudioCompressor->wf_decompress_default  );					
	//
	WORD  wFormatTag;wFormatTag = pAudioCompressor->wf_compress.wFormatTag;
	memset(  &pAudioCompressor->wf_compress,  0,  sizeof(  pAudioCompressor->wf_compress  )  );	//  2011/02/02
	pAudioCompressor->wf_compress.wFormatTag  =  wFormatTag;
	pAudioCompressor->wf_compress.nChannels  =  pAudioCompressor->wf_decompress_default.nChannels;			  														  
	pAudioCompressor->wf_compress.nSamplesPerSec  =  pAudioCompressor->wf_decompress_default.nSamplesPerSec;
	pAudioCompressor->wf_compress.wBitsPerSample  =  pAudioCompressor->wf_decompress_default.wBitsPerSample;															

	//
	iErr  =  0;
errLabel:
	return  iErr;
}




 int  getAudioCompressorCfg_default_custom(  unsigned  int  uiCapType,  AUDIO_COMPRESSOR_CFG  *  pCfg  )
{
	int		iErr	=	-1;
	QY_MC			*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	memset(  pCfg,  0,  sizeof(  pCfg  )  );

	pCfg->common.ucCompressors  =  CONST_audioCompressors_custom;


	CUS_MODULE_U	*  pModule	=	pFuncs->pf_getCusModule(  &pQyMc->cusModules,  CONST_moduleType_compress,  0,  0,  NULL  );
	if  (  !pModule  )  goto  errLabel;
	if  (  !pModule->compress.ucbInited  )  goto  errLabel;

	if  (  !pModule->compress.pf_qdcGetCompressAudioCfg  )  goto  errLabel;
	if  (  pModule->compress.pf_qdcGetCompressAudioCfg(  &pCfg->wf_decompress_default,  &pCfg->wf_compress  )  )  goto  errLabel;
	
	//  get_pcm_forAcm(  uiCapType,  &pCfg->wf_decompress_default  );

	iErr  =  0;
errLabel:
	return  iErr;
}

 int  getAudioCompressorCfg_default(  unsigned  int  uiCapType,  int  level,  AUDIO_COMPRESSOR_CFG  *  pCfg  )
{
	unsigned  char			ucCompressors	=	0;								//  acm or dmo
	
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	//
	switch  (  uiCapType  )  {
			case  CONST_capType_av:
				  ucCompressors  =  CONST_audioCompressors_mp3;
				  break;

			case  CONST_capType_screen:
			case  CONST_capType_mediaDevice:  
			case  CONST_capType_mediaFile:
			default:
#if  0
					if  (  qyGetAppAvLevel_qyMc(  pQyMc  )  <=  CONST_qyAppAvLevel_sd  )  ucCompressors  =  CONST_audioCompressors_dmo;					
					else  ucCompressors  =  CONST_audioCompressors_mp3;
#endif
					//
					ucCompressors  =  CONST_audioCompressors_mp3;
					//
				    break;
	}

	switch  (  ucCompressors  )  {
			case  CONST_audioCompressors_acm:
				  return  getAudioCompressorCfg_default_acm(  uiCapType,  pCfg  );
				  break;
			case  CONST_audioCompressors_dmo:
				  return  getAudioCompressorCfg_default_dmo(  uiCapType,  pCfg  );
				  break;
			case  CONST_audioCompressors_ipp:
				  return  getAudioCompressorCfg_default_ipp(  uiCapType,  pCfg  );
				  break;
			case CONST_audioCompressors_ffmpeg:
				  return  getAudioCompressorCfg_default_ffmpeg(  uiCapType,  pCfg  );
				  break;
			case  CONST_audioCompressors_custom:
				  return  getAudioCompressorCfg_default_custom(  uiCapType,  pCfg  );
				  break;
			default:
					break;
	}
	return  -1;
}


 //  2011/08/08
 int  getAudioPlayCfg(  QY_REG  reg,  unsigned int  uiCapType,  unsigned int  uiSubCapType,  int  level,  AUDIO_PLAY_CFG  *  pPlayCfg  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	PolicyAvParams		&	gAvParams	=	*pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );
	 //
	 TCHAR		*	pRegVal;
	 TCHAR			tBuf[256];
	 //  char			buf[128];
	 //  TCHAR		*	name;
	 TCHAR		*	pT;
	 long			lVal;

		//  2009/06/14
	pRegVal  =  (TCHAR*)CONST_regValName_uiMinTimeInMsOfAudioDataPlaying;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  _tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  <  MIN_uiMinTimeInMsOfAudioDataPlaying  ||  lVal  >  MAX_uiMinTimeInMsOfAudioDataPlaying  )  {  //  		lVal  =  DEFAULT_uiMinTimeInMsOfAudioDataPlaying;
		switch  (  uiCapType  )  {
			case  CONST_capType_av:  {
				if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
					lVal  =  gAvParams.DEFAULT_audioPlayCfg_webcam.usMinTimeInMsOfAudioDataPlaying;
				}
				else  {
					switch  (  level  )  {
#if  0
							case  CONST_policyAvLevel_ld1:
								lVal  =  gAvParams.audioPlayCfg_ld1.usMinTimeInMsOfAudioDataPlaying;
								break;
#endif
#if  0
							case  CONST_policyAvLevel_sd:
								lVal  =  gAvParams.audioPlayCfg_sd.usMinTimeInMsOfAudioDataPlaying;
								break;
#endif
							case  CONST_policyAvLevel_480p:
								lVal  =  gAvParams.audioPlayCfg_480p.usMinTimeInMsOfAudioDataPlaying;
								break;
#if  0
							case  CONST_policyAvLevel_sd2:
								lVal  =  gAvParams.audioPlayCfg_sd2.usMinTimeInMsOfAudioDataPlaying;
								break;
#endif
							case  CONST_policyAvLevel_576p:
								lVal  =  gAvParams.audioPlayCfg_576p.usMinTimeInMsOfAudioDataPlaying;
								break;
#if  0
							case  CONST_policyAvLevel_hd:
								lVal  =  gAvParams.audioPlayCfg_hd.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_hd1:
								lVal  =  gAvParams.audioPlayCfg_hd1.usMinTimeInMsOfAudioDataPlaying;
								break;
#endif
							case  CONST_policyAvLevel_720p:
								lVal  =  gAvParams.audioPlayCfg_720p.usMinTimeInMsOfAudioDataPlaying;
								break;
#if  0
							case  CONST_policyAvLevel_hd3:
								lVal  =  gAvParams.audioPlayCfg_hd3.usMinTimeInMsOfAudioDataPlaying;
								break;
#endif
#if  0
							case  CONST_policyAvLevel_fullHd:
								lVal  =  gAvParams.audioPlayCfg_fullHd.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_fullHd1:
								lVal  =  gAvParams.audioPlayCfg_fullHd1.usMinTimeInMsOfAudioDataPlaying;
								break;
#endif
							case  CONST_policyAvLevel_1080p:
								lVal  =  gAvParams.audioPlayCfg_1080p.usMinTimeInMsOfAudioDataPlaying;
								break;
#if  0
							case  CONST_policyAvLevel_fullHd3:
								lVal  =  gAvParams.audioPlayCfg_1080p.usMinTimeInMsOfAudioDataPlaying;
								break;
#endif
							case  CONST_policyAvLevel_240p:
							default:
								lVal  =  gAvParams.audioPlayCfg_240p.usMinTimeInMsOfAudioDataPlaying;
								break;
					}
				}
				}
				break;
			case  CONST_capType_screen:
			case  CONST_capType_mediaDevice:
			case  CONST_capType_mediaFile:
				lVal  =  CONST_uiMinTimeInMsOfAudioDataPlaying_1s;
				break;
			default:
				break;
		}
	}
	if  (  pPlayCfg->usMinTimeInMsOfAudioDataPlaying  !=  lVal  )  pPlayCfg->usMinTimeInMsOfAudioDataPlaying  =  (  unsigned  short  )lVal;

	pRegVal  =  (TCHAR*)CONST_regValName_uiAudioDataAddedToPlayEveryTime;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  _tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  <  MIN_uiAudioDataAddedToPlayEveryTime  ||  lVal  >  MAX_uiAudioDataAddedToPlayEveryTime  )  {  //  lVal  =  DEFAULT_uiAudioDataAddedToPlayEveryTime;
		switch  (  uiCapType  )  {
			case  CONST_capType_av:{
				if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
					lVal  =  gAvParams.DEFAULT_audioPlayCfg_webcam.usAudioDataAddedToPlayEveryTime;
				}
				else  {
					switch  (  level  )  {
#if  0
						case  CONST_policyAvLevel_ld1:
							lVal  =  gAvParams.audioPlayCfg_ld1.usAudioDataAddedToPlayEveryTime;
							break;
#endif
#if  0
						case  CONST_policyAvLevel_sd:
							lVal  =  gAvParams.audioPlayCfg_sd.usAudioDataAddedToPlayEveryTime;
							break;
#endif
						case  CONST_policyAvLevel_480p:
							lVal  =  gAvParams.audioPlayCfg_480p.usAudioDataAddedToPlayEveryTime;
							break;
#if  0
						case  CONST_policyAvLevel_sd2:
							lVal  =  gAvParams.audioPlayCfg_sd2.usAudioDataAddedToPlayEveryTime;
							break;
#endif
						case  CONST_policyAvLevel_576p:
							lVal  =  gAvParams.audioPlayCfg_576p.usAudioDataAddedToPlayEveryTime;
							break;
#if  0
						case  CONST_policyAvLevel_hd:
							lVal  =  gAvParams.audioPlayCfg_hd.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_hd1:
							lVal  =  gAvParams.audioPlayCfg_hd1.usAudioDataAddedToPlayEveryTime;
							break;
#endif
						case  CONST_policyAvLevel_720p:
							lVal  =  gAvParams.audioPlayCfg_720p.usAudioDataAddedToPlayEveryTime;
							break;
#if  0
						case  CONST_policyAvLevel_hd3:
							lVal  =  gAvParams.audioPlayCfg_hd3.usAudioDataAddedToPlayEveryTime;
							break;
#endif
#if  0
						case  CONST_policyAvLevel_fullHd:
							lVal  =  gAvParams.audioPlayCfg_fullHd.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_fullHd1:
							lVal  =  gAvParams.audioPlayCfg_fullHd1.usAudioDataAddedToPlayEveryTime;
							break;
#endif
						case  CONST_policyAvLevel_1080p:
							lVal  =  gAvParams.audioPlayCfg_1080p.usAudioDataAddedToPlayEveryTime;
							break;
#if  0
						case  CONST_policyAvLevel_fullHd3:
							lVal  =  gAvParams.audioPlayCfg_1080p.usAudioDataAddedToPlayEveryTime;
							break;
#endif
						case  CONST_policyAvLevel_240p:
						default:
							lVal  =  gAvParams.audioPlayCfg_240p.usAudioDataAddedToPlayEveryTime;
							break;
						}
					}
				}
				break;
			case  CONST_capType_screen:
			case  CONST_capType_mediaDevice:
			case  CONST_capType_mediaFile:
				lVal  =  CONST_uiAudioDataAddedToPlayEveryTime_1s;
				break;
			default:
				break;
		}
	}
	if  (  pPlayCfg->usAudioDataAddedToPlayEveryTime  !=  lVal  )  pPlayCfg->usAudioDataAddedToPlayEveryTime  =  (  unsigned  short  )lVal;

	pRegVal  =  (TCHAR*)CONST_regValName_uiNotifyIntervalInMs_needMoreAudioData;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  _tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  <  MIN_uiNotifyIntervalInMs_needMoreAudioData  ||  lVal  >  MAX_uiNotifyIntervalInMs_needMoreAudioData  )  {  //  lVal  =  DEFAULT_uiNotifyIntervalInMs_needMoreAudioData;
		switch  (  uiCapType  )  {
			case  CONST_capType_av:{
				if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
					lVal  =  gAvParams.DEFAULT_audioPlayCfg_webcam.usNotifyIntervalInMs_needMoreAudioData;
				}
				else  {
					switch  (  level  )  {
#if  0
						case  CONST_policyAvLevel_ld1:
							lVal  =  gAvParams.audioPlayCfg_ld1.usNotifyIntervalInMs_needMoreAudioData;
							break;
#endif
#if  0
						case  CONST_policyAvLevel_sd:
							lVal  =  gAvParams.audioPlayCfg_sd.usNotifyIntervalInMs_needMoreAudioData;
							break;
#endif
						case  CONST_policyAvLevel_480p:
							lVal  =  gAvParams.audioPlayCfg_480p.usNotifyIntervalInMs_needMoreAudioData;
							break;
#if  0
						case  CONST_policyAvLevel_sd2:
							lVal  =  gAvParams.audioPlayCfg_sd2.usNotifyIntervalInMs_needMoreAudioData;
							break;
#endif
						case  CONST_policyAvLevel_576p:
							lVal  =  gAvParams.audioPlayCfg_576p.usNotifyIntervalInMs_needMoreAudioData;
							break;
#if  0
						case  CONST_policyAvLevel_hd:
							lVal  =  gAvParams.audioPlayCfg_hd.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_hd1:
							lVal  =  gAvParams.audioPlayCfg_hd1.usNotifyIntervalInMs_needMoreAudioData;
							break;
#endif
						case  CONST_policyAvLevel_720p:
							lVal  =  gAvParams.audioPlayCfg_720p.usNotifyIntervalInMs_needMoreAudioData;
							break;
#if  0
						case  CONST_policyAvLevel_hd3:
							lVal  =  gAvParams.audioPlayCfg_hd3.usNotifyIntervalInMs_needMoreAudioData;
							break;
#endif
#if  0
						case  CONST_policyAvLevel_fullHd:
							lVal  =  gAvParams.audioPlayCfg_fullHd.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_fullHd1:
							lVal  =  gAvParams.audioPlayCfg_fullHd1.usNotifyIntervalInMs_needMoreAudioData;
							break;
#endif
						case  CONST_policyAvLevel_1080p:
							lVal  =  gAvParams.audioPlayCfg_1080p.usNotifyIntervalInMs_needMoreAudioData;
							break;
#if  0
						case  CONST_policyAvLevel_fullHd3:
							lVal  =  gAvParams.audioPlayCfg_1080p.usNotifyIntervalInMs_needMoreAudioData;
							break;
#endif
						case  CONST_policyAvLevel_240p:
						default:
							lVal  =  gAvParams.audioPlayCfg_240p.usNotifyIntervalInMs_needMoreAudioData;
							break;
						}
					}
				}
				break;
			case  CONST_capType_screen:
			case  CONST_capType_mediaDevice:
			case  CONST_capType_mediaFile:
				lVal  =  CONST_uiNotifyIntervalInMs_needMoreAudioData_1s;
				break;
			default:
				break;
		}
	}
	if  (  pPlayCfg->usNotifyIntervalInMs_needMoreAudioData  !=  lVal  )  pPlayCfg->usNotifyIntervalInMs_needMoreAudioData  =  (  unsigned  short  )lVal;

	//  2012/01/27
	pRegVal  =  (TCHAR*)CONST_regValName_uiMinTimeInMsToPlay;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  _tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  <=  0  ||  lVal  >  MAX_uiMinTimeInMsToPlay  )  {	//  lVal  =  DEFAULT_uiMinTimeInMsToPlay;
		switch  (  uiCapType  )  {
			case  CONST_capType_av:{
				if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
					lVal  =  gAvParams.DEFAULT_audioPlayCfg_webcam.usMinTimeInMsToPlay;
				}
				else  {
					switch  (  level  )  {
#if  0
						case  CONST_policyAvLevel_ld1:
							  lVal  =  gAvParams.audioPlayCfg_ld1.usMinTimeInMsToPlay;
							  break;
#endif
#if  0
						case  CONST_policyAvLevel_sd:
							  lVal  =  gAvParams.audioPlayCfg_sd.usMinTimeInMsToPlay;
							  break;
#endif
						case  CONST_policyAvLevel_480p:
							  lVal  =  gAvParams.audioPlayCfg_480p.usMinTimeInMsToPlay;
							  break;
#if  0
						case  CONST_policyAvLevel_sd2:
							  lVal  =  gAvParams.audioPlayCfg_sd2.usMinTimeInMsToPlay;
							  break;
#endif
						case  CONST_policyAvLevel_576p:
							  lVal  =  gAvParams.audioPlayCfg_576p.usMinTimeInMsToPlay;
							  break;
#if  0
						case  CONST_policyAvLevel_hd:
							  lVal  =  gAvParams.audioPlayCfg_hd.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_hd1:
							  lVal  =  gAvParams.audioPlayCfg_hd1.usMinTimeInMsToPlay;
							  break;
#endif
						case  CONST_policyAvLevel_720p:
							  lVal  =  gAvParams.audioPlayCfg_720p.usMinTimeInMsToPlay;
							  break;
#if  0
						case  CONST_policyAvLevel_hd3:
							  lVal  =  gAvParams.audioPlayCfg_hd3.usMinTimeInMsToPlay;
							  break;
#endif
#if  0
						case  CONST_policyAvLevel_fullHd:
							  lVal  =  gAvParams.audioPlayCfg_fullHd.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_fullHd1:
							  lVal  =  gAvParams.audioPlayCfg_fullHd1.usMinTimeInMsToPlay;
							  break;
#endif
						case  CONST_policyAvLevel_1080p:
							  lVal  =  gAvParams.audioPlayCfg_1080p.usMinTimeInMsToPlay;
							  break;
#if  0
						case  CONST_policyAvLevel_fullHd3:
							  lVal  =  gAvParams.audioPlayCfg_1080p.usMinTimeInMsToPlay;
							  break;
#endif
						case  CONST_policyAvLevel_240p:
						default:
							  lVal  =  gAvParams.audioPlayCfg_240p.usMinTimeInMsToPlay;
							  break;
						}
					}
			    }
				break;
			case  CONST_capType_screen:
			case  CONST_capType_mediaDevice:
			case  CONST_capType_mediaFile:
				lVal  =  CONST_uiMinTimeInMsToPlay_1s;
				break;
			default:
				break;
		}
	}
	if  (  pPlayCfg->usMinTimeInMsToPlay  !=  lVal  )  pPlayCfg->usMinTimeInMsToPlay  =  (  unsigned  short  )lVal;


	//  2009/06/03
	pRegVal  =  (TCHAR*)CONST_regValName_uiMaxTimeInMsToPlay;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  _tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  <=  0  ||  lVal  >  MAX_uiMaxTimeInMsToPlay  )  {	//  lVal  =  DEFAULT_uiMaxTimeInMsToPlay;
		switch  (  uiCapType  )  {
			case  CONST_capType_av:{
				if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
					lVal  =  gAvParams.DEFAULT_audioPlayCfg_webcam.usMaxTimeInMsToPlay;
				}
				else  {
					switch  (  level  )  {
#if  0
						case  CONST_policyAvLevel_ld1:
							  lVal  =  gAvParams.audioPlayCfg_ld1.usMaxTimeInMsToPlay;
							  break;
#endif
#if  0
						case  CONST_policyAvLevel_sd:
							  lVal  =  gAvParams.audioPlayCfg_sd.usMaxTimeInMsToPlay;
							  break;
#endif
						case  CONST_policyAvLevel_480p:
							  lVal  =  gAvParams.audioPlayCfg_480p.usMaxTimeInMsToPlay;
							  break;
#if  0
						case  CONST_policyAvLevel_sd2:
							  lVal  =  gAvParams.audioPlayCfg_sd2.usMaxTimeInMsToPlay;
							  break;
#endif
						case  CONST_policyAvLevel_576p:
							  lVal  =  gAvParams.audioPlayCfg_576p.usMaxTimeInMsToPlay;
							  break;
#if  0
						case  CONST_policyAvLevel_hd:
							  lVal  =  gAvParams.audioPlayCfg_hd.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_hd1:
							  lVal  =  gAvParams.audioPlayCfg_hd1.usMaxTimeInMsToPlay;
							  break;
#endif
						case  CONST_policyAvLevel_720p:
							  lVal  =  gAvParams.audioPlayCfg_720p.usMaxTimeInMsToPlay;
							  break;
#if  0
						case  CONST_policyAvLevel_hd3:
							  lVal  =  gAvParams.audioPlayCfg_hd3.usMaxTimeInMsToPlay;
							  break;
#endif
#if  0
						case  CONST_policyAvLevel_fullHd:
							  lVal  =  gAvParams.audioPlayCfg_fullHd.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_fullHd1:
							  lVal  =  gAvParams.audioPlayCfg_fullHd1.usMaxTimeInMsToPlay;
							  break;
#endif
						case  CONST_policyAvLevel_1080p:
							  lVal  =  gAvParams.audioPlayCfg_1080p.usMaxTimeInMsToPlay;
							  break;
#if  0
						case  CONST_policyAvLevel_fullHd3:
							  lVal  =  gAvParams.audioPlayCfg_1080p.usMaxTimeInMsToPlay;
							  break;
#endif
						case  CONST_policyAvLevel_240p:
						default:
							  lVal  =  gAvParams.audioPlayCfg_240p.usMaxTimeInMsToPlay;
							  break;
						}
					}
				}
				break;
			case  CONST_capType_screen:
			case  CONST_capType_mediaDevice:
			case  CONST_capType_mediaFile:
				lVal  =  CONST_uiMaxTimeInMsToPlay_1s;
				break;
			default:
				break;
			}	
	}
	if  (  pPlayCfg->usMaxTimeInMsToPlay  !=  lVal  )  pPlayCfg->usMaxTimeInMsToPlay  =  (  unsigned  short  )lVal;
	
	//  
	pRegVal  =  (TCHAR*)CONST_regValName_uiMaxTimeInMsToBeRemoved;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  _tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  <=  0  ||  lVal  >  MAX_uiMaxTimeInMsToBeRemoved  )  {	//  lVal  =  DEFAULT_uiMaxTimeInMsToBeRemoved;
		switch  (  uiCapType  )  {
			case  CONST_capType_av:{
				if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
					lVal  =  gAvParams.DEFAULT_audioPlayCfg_webcam.usMaxTimeInMsToBeRemoved;
				}
				else  {
					switch  (  level  )  {
#if  0
						case  CONST_policyAvLevel_ld1:
							  lVal  =  gAvParams.audioPlayCfg_ld1.usMaxTimeInMsToBeRemoved;
							  break;
#endif
#if  0
						case  CONST_policyAvLevel_sd:
							  lVal  =  gAvParams.audioPlayCfg_sd.usMaxTimeInMsToBeRemoved;
							  break;
#endif
						case  CONST_policyAvLevel_480p:
							  lVal  =  gAvParams.audioPlayCfg_480p.usMaxTimeInMsToBeRemoved;
							  break;
#if  0
						case  CONST_policyAvLevel_sd2:
							  lVal  =  gAvParams.audioPlayCfg_sd2.usMaxTimeInMsToBeRemoved;
							  break;
#endif
						case  CONST_policyAvLevel_576p:
							  lVal  =  gAvParams.audioPlayCfg_576p.usMaxTimeInMsToBeRemoved;
							  break;
#if  0
						case  CONST_policyAvLevel_hd:
							  lVal  =  gAvParams.audioPlayCfg_hd.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_hd1:
							  lVal  =  gAvParams.audioPlayCfg_hd1.usMaxTimeInMsToBeRemoved;
							  break;
#endif
						case  CONST_policyAvLevel_720p:
							  lVal  =  gAvParams.audioPlayCfg_720p.usMaxTimeInMsToBeRemoved;
							  break;
#if  0
						case  CONST_policyAvLevel_hd3:
							  lVal  =  gAvParams.audioPlayCfg_hd3.usMaxTimeInMsToBeRemoved;
							  break;
#endif
#if  0
						case  CONST_policyAvLevel_fullHd:
							  lVal  =  gAvParams.audioPlayCfg_fullHd.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_fullHd1:
							  lVal  =  gAvParams.audioPlayCfg_fullHd1.usMaxTimeInMsToBeRemoved;
							  break;
#endif
						case  CONST_policyAvLevel_1080p:
							  lVal  =  gAvParams.audioPlayCfg_1080p.usMaxTimeInMsToBeRemoved;
							  break;
#if  0
						case  CONST_policyAvLevel_fullHd3:
							  lVal  =  gAvParams.audioPlayCfg_1080p.usMaxTimeInMsToBeRemoved;
							  break;
#endif
						case  CONST_policyAvLevel_240p:
						default:
							  lVal  =  gAvParams.audioPlayCfg_240p.usMaxTimeInMsToBeRemoved;
							  break;
						}
					}
				}
				break;
			case  CONST_capType_screen:
			case  CONST_capType_mediaDevice:
			case  CONST_capType_mediaFile:
				lVal  =  CONST_uiMaxTimeInMsToBeRemoved_1s;
				break;
			default:
				break;
		}						  
	}
	if  (  pPlayCfg->usMaxTimeInMsToBeRemoved  !=  lVal  )  pPlayCfg->usMaxTimeInMsToBeRemoved  =  (  unsigned  short  )lVal;

	return  0;
}

//
__declspec(dllexport)int  getRegRootKey_qmc(  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage,  TCHAR  *  rootKeyStr,  unsigned  int  uiCnt  )
{
	TCHAR  *  pT;
	TCHAR  name[128]	=	_T(  ""  );
	TCHAR	tBuf[256]	=	_T(  ""  );

	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	
	if  (  !uiCapType  )  {
		safeTcsnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  rootKeyStr,  uiCnt  );
		return  -1;
	}

	if  (  !(  pT  =  qyGetDesByType(  CONST_capTypeTable,  uiCapType  )  )  )  return  -1;		 
	 if  (  !pT[0]  )  return  -1;
	 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s"  ),  pT  );
	 //
	 if  (  !(  pT  =  qyGetDesByType(  CONST_subCapTypeTable,  uiSubCapType  )  )  )  return  -1;
	 if  (  !pT[0]  )  return  -1;
	 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s.%s"  ),  name,  pT  );
	 //  2014/11/19
	 if  (  !(  pT  =  qyGetDesByType(  CONST_capUsageTable,  iCapUsage  )  )  )  return  -1;
	 if  (  !pT[0]  )  return  -1;	
	 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s.%s"  ),  name,  pT  );
	 
	 //  2014/04/26
	 lstrcpyn(  tBuf,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  mycountof(  tBuf  )  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s"  ),  tBuf,  name  );
	 
	 safeTcsnCpy(  tBuf,  rootKeyStr,  uiCnt  );

	 return  0;
}

//
//
int  get_idRegRootKey_qmc(  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage,  TCHAR  *  rootKeyStr,  unsigned  int  uiCnt  )
{
	int  iErr  =  -1;
	TCHAR  *  pT;
	TCHAR  name[128]	=	_T(  ""  );
	TCHAR	tBuf[256]	=	_T(  ""  );

	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	
	//
	if  (  !pIdInfo  )  return  -1;
	if  (  !pIdInfo->ui64Id  )  return  -1;

	//
	if  (  !uiCapType  )  {
		safeTcsnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  tBuf,  mycountof(  tBuf  )  );
		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\id%I64u"  ),  tBuf,  pIdInfo->ui64Id  );
		//
		iErr  =  0;  goto  errLabel;
	}

	 //
	 if  (  !(  pT  =  qyGetDesByType(  CONST_capTypeTable,  uiCapType  )  )  )  return  -1;		 
	 if  (  !pT[0]  )  return  -1;
	 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s"  ),  pT  );
	 //
	 if  (  !(  pT  =  qyGetDesByType(  CONST_subCapTypeTable,  uiSubCapType  )  )  )  return  -1;
	 if  (  !pT[0]  )  return  -1;
	 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s.%s"  ),  name,  pT  );
	 //  2014/11/19
	 if  (  !(  pT  =  qyGetDesByType(  CONST_capUsageTable,  iCapUsage  )  )  )  return  -1;
	 if  (  !pT[0]  )  return  -1;	
	 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s.%s"  ),  name,  pT  );
	 
	 //  2014/04/26
	 lstrcpyn(  tBuf,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  mycountof(  tBuf  )  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\id%I64u\\%s"  ),  tBuf,  pIdInfo->ui64Id,  name  );
	 
	 iErr  =  0;

errLabel:
	 
	 if  (  !iErr  )  {
		 safeTcsnCpy(  tBuf,  rootKeyStr,  uiCnt  );
	 }

	 return  iErr;
}


//
//  2016/04/16
  int  get_resIdTable(  int  level,  int  iFourcc,  int  *  piResId,  int  *  piDefault_bitrate  )
 {
	 int  iErr  =  -1;
	 int  iResId  =  0;
	 int  iDefault_bitrate  =  0;

	 //
	 switch  (  iFourcc  )  {
			 case  CONST_fourcc_h264:
				   //	 
				   switch  (  level  )  {			 
						   case  CONST_policyAvLevel_720p:				   
							     iResId  =  CONST_resId_iAvgBitrateTable_h264_720p;				   
								 iDefault_bitrate  =  DEFAULT_iAvgBitrate_h264_720p;				   
								 break;			 
						   case  CONST_policyAvLevel_1080p:				   
							     iResId  =  CONST_resId_iAvgBitrateTable_h264_1080p;				   
								 iDefault_bitrate  =  DEFAULT_iAvgBitrate_h264_1080p;				   
								 break;			 
						   default:					
								   break;
				   }
				   break;
			 case  CONST_fourcc_HEVC:
				   //	 
				   switch  (  level  )  {			 
						   case  CONST_policyAvLevel_720p:				   
							     iResId  =  CONST_resId_iAvgBitrateTable_h265_720p;				   
								 iDefault_bitrate  =  DEFAULT_iAvgBitrate_h265_720p;				   
								 break;			 
						   case  CONST_policyAvLevel_1080p:				   
							     iResId  =  CONST_resId_iAvgBitrateTable_h265_1080p;				   
								 iDefault_bitrate  =  DEFAULT_iAvgBitrate_h265_1080p;				   
								 break;			 
						   default:					
								   break;
				   }
				   break;
			 default:
					 break;
	 }

	 //
	 if  (  piResId  )  *piResId  =  iResId;
	 if  (  piDefault_bitrate  )  *piDefault_bitrate  =  iDefault_bitrate;
	 

	 iErr  =  0;
	 
	 return  iErr;				   
 }


//
  __declspec(dllexport)  int  getCompressorCfg(  QY_REG  *  pReg,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor  )
{
	 QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 PolicyAvParams		&	gAvParams	=	*pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );

	 CQyString		rootKeyStr;
	 TCHAR		*	pRegVal;
	 TCHAR			tBuf[256]	=  _T(  ""  );
	 char			buf[128];
	 TCHAR			name[128]	=	_T(  ""  );
	 TCHAR		*	pT;
	 long			lVal;
	 QY_REG			reg;

	 //
	 memset(  pCompressor,  0,  sizeof(  pCompressor[0]  )  );

	 //
	 if  (  pReg  )  memcpy(  &reg,  pReg,  sizeof(  reg  )  );
	 else  {
		   memset(  &reg,  0,  sizeof(  reg  )  );
		   reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	 }
#if 0
	 if  (  !(  pT  =  qyGetDesByType(  CONST_capTypeTable,  uiCapType  )  )  )  return  -1;		 
	 if  (  !pT[0]  )  return  -1;
	 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s"  ),  pT  );
	 if  (  uiSubCapType  )  {
		 if  (  !(  pT  =  qyGetDesByType(  CONST_subCapTypeTable,  uiSubCapType  )  )  )  return  -1;
		 if  (  !pT[0]  )  return  -1;
		 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s.%s"  ),  name,  pT  );
	 }
	 
	 //  2014/04/26
	 lstrcpyn(  tBuf,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  tBuf  )  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s"  ),  tBuf,  name  );
	 rootKeyStr  =  CQyString(  tBuf  );
#endif
	 getRegRootKey_qmc(  uiCapType,  uiSubCapType,  iCapUsage,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	 rootKeyStr  =  CQyString(  reg.rootKey  );

	 //  2014/04/26. 这几个设备策略是总体策略，不分级别.
	 pRegVal  =  (TCHAR*)_T(  CONST_regValName_ucbSetDevResolution  );
	 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  _tcstol(  tBuf,  &pT,  10  );
	 pCompressor->video.dev.ucbSetDevResolution  =  lVal  ?  TRUE  :  FALSE;

	 pRegVal  = (TCHAR*)_T(  CONST_regValName_iDevWidth  );
	 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  _tcstol(  tBuf,  &pT,  10  );
	 pCompressor->video.dev.iWidth  =  lVal;

	 pRegVal  = (TCHAR*)_T(  CONST_regValName_iDevHeight  );
	 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  _tcstol(  tBuf,  &pT,  10  );
	 pCompressor->video.dev.iHeight  =  lVal;


	 //
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\level%d"  ),  reg.rootKey,  level  );
	 rootKeyStr  =  CQyString(  tBuf  );

	 tBuf[0]  =  0;

	 pRegVal  = (TCHAR*)_T(  CONST_regValName_audioCompressors  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 pCompressor->audio.common.ucCompressors  =  (  unsigned  char  )_ttol(  tBuf  );
	 }
	 if  (  pQyMc->cfg.bGetPolicyFromIni  )  {	 
		 if  (  !getCfgValByName(  pQyMc->cfg.iniFullFileName,  (char*)CONST_regValName_audioCompressors,  buf,  sizeof(  buf  )  )  )  {
			 trim(  buf  );
			 lVal  =  qyGetTypeByDes(  gAvParams.pAudioCompressorsTable,  CQyString(  buf  )  );
			 if  (  lVal  !=  -1  )  pCompressor->audio.common.ucCompressors  =  lVal;
		}
	 }

	 pRegVal  = (TCHAR*)_T(  CONST_regValName_audioCompressorName  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 lstrcpyn(  pCompressor->audio.compressorName,  tBuf,  mycountof(  pCompressor->audio.compressorName  )  );
	 }
	 pRegVal  = (TCHAR*)_T(  CONST_regValName_wfx_enc_wFormatTag  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 pCompressor->audio.wf_compress.wFormatTag  =  (  WORD  )_ttol(  tBuf  );
	 }
	 pRegVal  = (TCHAR*)_T(  CONST_regValName_wfx_enc_nChannels  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 pCompressor->audio.wf_compress.nChannels  =  (  WORD  )_ttol(  tBuf  );
	 }	 
	 pRegVal  = (TCHAR*)_T(  CONST_regValName_wfx_enc_nSamplesPerSec  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 pCompressor->audio.wf_compress.nSamplesPerSec  =  (  DWORD  )_ttol(  tBuf  );
	 }	
	 pRegVal  = (TCHAR*)_T(  CONST_regValName_wfx_enc_wBitsPerSample  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 pCompressor->audio.wf_compress.wBitsPerSample  =  (  WORD  )_ttol(  tBuf  );
	 }
	 pRegVal  = (TCHAR*)_T(  CONST_regValName_wfx_enc_nAvgBytesPerSec  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 pCompressor->audio.wf_compress.nAvgBytesPerSec  =  (  DWORD  )_ttol(  tBuf  );
	 }

	 //  2013/08/23
	 if  (  pCompressor->audio.common.ucCompressors  &&		
		 !qyGetDesByType(  gAvParams.pAudioCompressorsTable,  pCompressor->audio.common.ucCompressors  )  )  
	 {
		 //showNotification(  NULL,  NULL,  NULL,  0,  0,  0,  _T(  "Audio compressor adjusted."  )  );
		 qyShowInfo1(  CONST_qyShowType_warning,  0,  (char*)"",  _T(  "IsCli"  ),  NULL,  NULL,  _T(  ""  ),  _T(  "Audio compressor adjusted."  )  );
		 //
		 getAudioCompressorCfg_default(  uiCapType,  level,  &pCompressor->audio  );
		 }
	 else  {	 //
		 if  (  pCompressor->audio.common.ucCompressors  ==  CONST_audioCompressors_custom  )  getAudioCompressorCfg_default_custom(  uiCapType,  &pCompressor->audio  );
		 else  if  (  pCompressor->audio.common.ucCompressors  ==  CONST_audioCompressors_ipp  )  getAudioCompressorCfg_default_ipp(  uiCapType,  &pCompressor->audio  );
		 else  if  (  pCompressor->audio.common.ucCompressors  
			 &&  pCompressor->audio.wf_compress.wFormatTag
				&&  pCompressor->audio.wf_compress.nChannels  
					&&  pCompressor->audio.wf_compress.nSamplesPerSec
						&&  pCompressor->audio.wf_compress.wBitsPerSample  
						)
		 {
			 if  (  pCompressor->audio.common.ucCompressors  ==  CONST_audioCompressors_acm  )  get_pcm_forAcm(  uiCapType,  &pCompressor->audio.wf_decompress_default  );
			 else  makeWaveFormat_pcm(  pCompressor->audio.wf_compress.nChannels,  pCompressor->audio.wf_compress.nSamplesPerSec,  pCompressor->audio.wf_compress.wBitsPerSample,  &pCompressor->audio.wf_decompress_default  );
			 }
		 else  if  (  pCompressor->audio.common.ucCompressors  ==  CONST_audioCompressors_acm  )  {	//  2014/08/16
				   getAudioCompressorCfg_default_acm(  uiCapType,  &pCompressor->audio  );
				   }
		 else    	
			 getAudioCompressorCfg_default(  uiCapType,  level,  &pCompressor->audio  );
	 }
 	 
	 //  2010/03/11
	 QY_REG	tmpReg;
	 tmpReg  =  reg;
	 //  myTChar2Str(  rootKeyStr,  tmpReg.rootKey,  mycountof(  tmpReg.rootKey  )  );
	 lstrcpyn(  tmpReg.rootKey,  rootKeyStr,  mycountof(  tmpReg.rootKey  )  );
	 getAudioPlayCfg(  tmpReg,  uiCapType,  uiSubCapType,  level,  &pCompressor->audio.playCfg  );

	 //
	 pRegVal  = (TCHAR*)CONST_regValName_uiBytesRecorded_perBlockAlign;
	 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  _tcstol(  tBuf,  &pT,  10  );
	 if  (  lVal  <  MIN_uiBytesRecorded_perBlockAlign  ||  lVal  >  MAX_uiBytesRecorded_perBlockAlign  )  {
		 lVal  =  MACRO_getuiBytesRecorded_perBlockAlign(  pCompressor->audio,  &pCompressor->audio.wf_decompress_default  );
	 }
	 if  (  pCompressor->audio.uiBytesRecorded_perBlockAlign  !=  lVal  )  pCompressor->audio.uiBytesRecorded_perBlockAlign  =  lVal;
	 
	 //  2014/05/24
	 pRegVal  = (TCHAR*)CONST_regValName_ucbOrgAudioFmt;
	 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  _tcstol(  tBuf,  &pT,  10  );
	 if  (  pCompressor->audio.dev.ucbSetOrgAudioFmt  !=  lVal  )   pCompressor->audio.dev.ucbSetOrgAudioFmt  =  lVal  ?  TRUE  :  FALSE;

	 if  (  pCompressor->audio.dev.ucbSetOrgAudioFmt  )  {
		 pRegVal  = (TCHAR*)CONST_regValName_uiChannel;
		 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
		 lVal  =  _tcstol(  tBuf,  &pT,  10  );
		 if  (  lVal  !=  1  &&  lVal  !=  2  )  {
			 lVal  =  pCompressor->audio.wf_compress.nChannels;
		 }
		 if  (  pCompressor->audio.dev.wf_org_suggested.nChannels  !=  lVal  )  pCompressor->audio.dev.wf_org_suggested.nChannels  =  lVal;

		 pRegVal  = (TCHAR*)CONST_regValName_uiSample;
		 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
		 lVal  =  _tcstol(  tBuf,  &pT,  10  );
		 if  (  lVal  <  MIN_audio_uiSample  ||  lVal  >  MAX_audio_uiSample  )  {
			 lVal  =  pCompressor->audio.wf_compress.nSamplesPerSec;
		 }
		 if  (  pCompressor->audio.dev.wf_org_suggested.nSamplesPerSec  !=  lVal  )  pCompressor->audio.dev.wf_org_suggested.nSamplesPerSec  =  lVal;

		 pRegVal  = (TCHAR*)CONST_regValName_uiBit;
		 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
		 lVal  =  _tcstol(  tBuf,  &pT,  10  );
		 if  (  lVal  !=  8  &&  lVal  !=  16  )  {
			 lVal  =  pCompressor->audio.wf_compress.wBitsPerSample;
		 }
		 if  (  pCompressor->audio.dev.wf_org_suggested.wBitsPerSample  !=  lVal  )  pCompressor->audio.dev.wf_org_suggested.wBitsPerSample  =  lVal;
	 }

	 //  2014/05/20
	 pRegVal  = (TCHAR*)CONST_regValName_audio_avgBitrate;
	 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  _tcstol(  tBuf,  &pT,  10  );
	 if  (  lVal <  MIN_uiAudio_avgBitrate  ||  lVal  >  MAX_uiAudio_avgBitrate  )  {
		 switch (  uiCapType  )  {
			case  CONST_capType_av:
				  if  (  pCompressor->audio.wf_compress.nSamplesPerSec  ==  16000  )  {
					  lVal  =  32;
					  }
				  else  {
					    lVal  =  128;
				  }
				break;
			default:
				  lVal  =  128;
				break;
		 }
	 }
	 if  (  pCompressor->audio.common.iAvgBitrateInKbps  !=  lVal  )  pCompressor->audio.common.iAvgBitrateInKbps  =  lVal;

	 //
	 pRegVal  = (TCHAR*)_T(  CONST_regValName_videoCompressors  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 pCompressor->video.common.ucCompressors  =  (  unsigned  char  )_ttol(  tBuf  );
	 }
	 if  (  pQyMc->cfg.bGetPolicyFromIni  )  {
		 if  (  !getCfgValByName(  pQyMc->cfg.iniFullFileName,  (char*)CONST_regValName_videoCompressors,  buf,  sizeof(  buf  )  )  )  {
			 trim(  buf  );
			 lVal  =  qyGetTypeByDes(  gAvParams.pVideoCompressorsTable,  CQyString(  buf  )  );
			 if  (  lVal  !=  -1  )  pCompressor->video.common.ucCompressors  =  lVal;
		}
	 }

	 //
	 pRegVal  = (TCHAR*)_T(  CONST_regValName_videoCompressorName  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 lstrcpyn(  pCompressor->video.compressorName,  tBuf,  mycountof(  pCompressor->video.compressorName  )  );
	 }
	 //  2008/03/15
	 pRegVal  = (TCHAR*)_T(  CONST_regValName_v_fourccStr  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
		 safeStrnCpy(  buf,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
	 }

	 if  (  !qyGetDesByType(  gAvParams.pVideoCompressorsTable,  pCompressor->video.common.ucCompressors  )  
			||  !pCompressor->video.common.fourccStr[0]  )  
	 {
		 if  (  pCompressor->video.common.ucCompressors  !=  CONST_videoCompressors_custom  )  {
		 switch  (  uiCapType  )  {
				 case  CONST_capType_mosaic:
					   switch(  level  )  { 
							 case  CONST_policyAvLevel_848x480:  //  2014/11/15
								   pCompressor->video.common.ucCompressors  =  gAvParams.SD_mosaic_video.videoCompressors_av;
								   safeStrnCpy(  gAvParams.SD_mosaic_video.videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
								   break;
							 case  CONST_policyAvLevel_dev_5fps1:
							 default:
								       pCompressor->video.common.ucCompressors  =  gAvParams.DEV5FPS_videoCompressors_mosaic_resource;
									   safeStrnCpy(  gAvParams.DEV5FPS_videoFourccStr_mosaic_resource,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									   break;
					   }
					   break;
				 case  CONST_capType_slave:  //  2016/04/06
					   switch  (  level  )  {
							   case  CONST_policyAvLevel_240p:
							   default:
								       pCompressor->video.common.ucCompressors  =  gAvParams.LD_slave_video.videoCompressors_av;
									   safeStrnCpy(  gAvParams.LD_slave_video.videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									   break;
					   }
					   break;
				 case  CONST_capType_screen:		//  2012/02/16
				 case  CONST_capType_mediaDevice:
				 case  CONST_capType_mediaFile:
				 case  CONST_capType_av:
				 default:
					 {
						 //  2015/03/11
						 if  (  uiCapType  ==  CONST_capType_screen
							 //||  (  uiCapType  ==  CONST_capType_mediaDevice  &&  uiSubCapType  ==  CONST_subCapType_unresizable  )  
							 )
						 {
						   switch  (  level  )  {
							   case  CONST_policyAvLevel_dev_2fps:
								     pCompressor->video.common.ucCompressors  =  gAvParams.DEV2FPS_videoCompressors_screen;
									 safeStrnCpy(  gAvParams.DEV2FPS_videoFourccStr_screen,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
								     break;
							   case  CONST_policyAvLevel_dev_5fps:
							   case  CONST_policyAvLevel_dev_5fps1:
							   default:
								       pCompressor->video.common.ucCompressors  =  gAvParams.DEV5FPS_videoCompressors_screen;
									   safeStrnCpy(  gAvParams.DEV5FPS_videoFourccStr_screen,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									   break;	
						   }
						   break;
						 }
						 //
					     switch  (  level  )  {
								 case  CONST_policyAvLevel_480p:
									   pCompressor->video.common.ucCompressors  =  gAvParams.SD1.videoCompressors_av;
									   safeStrnCpy(  gAvParams.SD1.videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									   break;
							     case  CONST_policyAvLevel_576p:
									   pCompressor->video.common.ucCompressors  =  gAvParams.SD3.videoCompressors_av;
									   safeStrnCpy(  gAvParams.SD3.videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									   break;
							     case  CONST_policyAvLevel_720p:
									   pCompressor->video.common.ucCompressors  =  gAvParams.HD.videoCompressors_av;
									   safeStrnCpy(  gAvParams.HD.videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									   break;
							     case  CONST_policyAvLevel_1080p:
									   pCompressor->video.common.ucCompressors  =  gAvParams.fullHD.videoCompressors_av;
									   safeStrnCpy(  gAvParams.fullHD.videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									   break;
									   //
								 case  CONST_policyAvLevel_1080p60:
									   pCompressor->video.common.ucCompressors = gAvParams.fullHD60.videoCompressors_av;
									   safeStrnCpy(gAvParams.fullHD60.videoFourccStr_av, pCompressor->video.common.fourccStr, mycountof(pCompressor->video.common.fourccStr));
									   break;
									   //
								 case  CONST_policyAvLevel_2160p:
									 pCompressor->video.common.ucCompressors = gAvParams.video4k.videoCompressors_av;
									 safeStrnCpy(gAvParams.video4k.videoFourccStr_av, pCompressor->video.common.fourccStr, mycountof(pCompressor->video.common.fourccStr));
									 break;

									   //
								 case  CONST_policyAvLevel_2160p60:
									 pCompressor->video.common.ucCompressors = gAvParams.video4k60.videoCompressors_av;
									 safeStrnCpy(gAvParams.video4k60.videoFourccStr_av, pCompressor->video.common.fourccStr, mycountof(pCompressor->video.common.fourccStr));
									 break;


							     case  CONST_policyAvLevel_240p:
									   pCompressor->video.common.ucCompressors  =  gAvParams.LD.videoCompressors_av;
									   safeStrnCpy(  gAvParams.LD.videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );									   
									   break;
								 case  CONST_policyAvLevel_256x144:
								 default:
									 pCompressor->video.common.ucCompressors = gAvParams.QCIF.videoCompressors_av;
									 safeStrnCpy(gAvParams.QCIF.videoFourccStr_av, pCompressor->video.common.fourccStr, mycountof(pCompressor->video.common.fourccStr));
									 break;

						 }
					 }
						 break;
			 }
		}
		
	 }

	 //
	 //
	 if  (  bLikeXp(  )  )  {  //  2014/04/10
		 if  (  pCompressor->video.common.ucCompressors  ==  CONST_videoCompressors_hwAccl  )  {
			 pCompressor->video.common.ucCompressors  =  CONST_videoCompressors_ipp;
			 qyShowInfo1(  CONST_qyShowType_warning,  0,  (char*)"",  _T(  "IsCli"  ),  NULL,  NULL,  _T(  ""  ),  _T(  "Adjusted: for Xp, use ipp to make h264"  )  );
		 }
	 }


	 //  2011/07/31
	 if  (  pCompressor->video.common.ucCompressors  ==  CONST_videoCompressors_ipp  )  {
		 pCompressor->video.common.profile_idc  =  H264_PROFILE_BASELINE;
		 //  pCompressor->video.common.profile_idc  =  H264_PROFILE_MAIN;			//  2014/06/25
	 }

	 //
	 switch  (  uiCapType  )  {
			 case  CONST_capType_mosaic:
				   switch  (  level  )  {
							case  CONST_policyAvLevel_848x480:  {  //  2014/11/15
								  myVIDEO_init_cfg  *  pInitCfg  =  &gAvParams.SD_mosaic_video;
								  //
								  pCompressor->video.common.usMaxFps_toShareBmp  =  pInitCfg->usMaxFps_toShareBmp;
								  pCompressor->usFrames_perSecond_videoConference  =  pInitCfg->usFps_toShareBmp_videoConference;
								  										
								  //									
								  pCompressor->video.common.iWidth_pic  =  pInitCfg->iW_av;																		
								  pCompressor->video.common.iHeight_pic  =  pInitCfg->iH_av;
								  
								  }
								  break;
							case  CONST_policyAvLevel_dev_5fps1:
							default:
									 pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV5FPS_usMaxFps_mosaic_resource;						//  2012/02/16;.LD_usMaxFps_screen;											//  2008/12/6,
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS_700kb;//gAvParams.DEV5FPS_500kb;
								     break;
				   }
				   break;

			 case  CONST_capType_slave:  //  2016/04/06
				   switch  (  level  )  {
						   case  CONST_policyAvLevel_240p:
						   default:  {
							       myVIDEO_init_cfg  *  pInitCfg  =  &gAvParams.LD_slave_video;
								   pInitCfg  =  &gAvParams.SD_slave_video;  //  2018/12/19
								   pCompressor->video.common.usMaxFps_toShareBmp  =  pInitCfg->usMaxFps_toShareBmp;
								   pCompressor->ucSeconds_perFrame_videoConference  =  pInitCfg->usFps_toShareBmp_videoConference;
								   //
								   pCompressor->video.common.iWidth_pic  =  pInitCfg->iW_av;
								   pCompressor->video.common.iHeight_pic  =  pInitCfg->iH_av;
								   }
								   break;
				   }
				   break;

			 case  CONST_capType_screen:				   
			 case  CONST_capType_mediaDevice:
			 case  CONST_capType_mediaFile:
			 case  CONST_capType_av:
			 default:
				 
				    if  (  uiCapType  ==  CONST_capType_screen
						//||  (  uiCapType  ==  CONST_capType_mediaDevice  &&  uiSubCapType  ==  CONST_subCapType_unresizable  )
						)
					{
						switch  (  level  )  {
						   case  CONST_policyAvLevel_dev_2fps:
							     pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV2FPS_usMaxFps;										//  2012/02/16..FULLHD2_usMaxFps_screen;											//  2008/12/6,
								 break;
						   case  CONST_policyAvLevel_dev_5fps:
						   default:
							     pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV5FPS_usMaxFps;											//  2012/02/16;.LD_usMaxFps_screen;											//  2008/12/6,
								 break;				   
						}
						//  2012/10/29
						//if  (  pCompressor->video.common.ucCompressors  ==  CONST_videoCompressors_ipp  )  
						{
							switch  (  level  )  {
							   case  CONST_policyAvLevel_dev_5fps2:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS_700kb;
								     break;
							   case  CONST_policyAvLevel_dev_5fps1:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS_500kb;
								     break;
							   case  CONST_policyAvLevel_dev_5fps:
							   default:
									  pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS_500kb;
									  break;					   
							}				   
						}
						break;

					}
				    //
				    switch  (  level  )  {
							case  CONST_policyAvLevel_480p:  
							case  CONST_policyAvLevel_848x480:
								{
								  myVIDEO_init_cfg  *  pInitCfg  =  &gAvParams.SD1;  
								  if  (  uiCapType  ==  CONST_capType_av  )  {
									  pInitCfg  =  &gAvParams.SD1_av;									  
								  }								  
									
								  //
								  pCompressor->video.common.usMaxFps_toShareBmp  =  pInitCfg->usMaxFps_toShareBmp;										//  2008/12/6,									
								  pCompressor->usFrames_perSecond_videoConference  =  pInitCfg->usFps_toShareBmp_videoConference;						//  2012/02/16
								  										
								  //									
								  pCompressor->video.common.iWidth_pic  =  pInitCfg->iW_av;																		
								  pCompressor->video.common.iHeight_pic  =  pInitCfg->iH_av;
								  
								  }
								  break;
							case  CONST_policyAvLevel_576p:  {
								  myVIDEO_init_cfg  *  pInitCfg  =  &gAvParams.SD3;  
								  if  (  uiCapType  ==  CONST_capType_av  )  {
									  pInitCfg  =  &gAvParams.SD3_av;									  
								  }								  

								  //
								  pCompressor->video.common.usMaxFps_toShareBmp  =  pInitCfg->usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  pInitCfg->usFps_toShareBmp_videoConference;						//  2012/02/16
								  //
								  pCompressor->video.common.iWidth_pic  =  pInitCfg->iW_av;									
								  pCompressor->video.common.iHeight_pic  =  pInitCfg->iH_av;

								  }
								  break;
							case  CONST_policyAvLevel_720p:  {
								  myVIDEO_init_cfg  *  pInitCfg  =  &gAvParams.HD;  
								  if  (  uiCapType  ==  CONST_capType_av  )  {
									  if  (  iCapUsage  ==  CONST_capUsage_3dConf  )  {
										  ;
										  }
									  else  {
										    if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  pInitCfg  =  &gAvParams.HD_webcam;									  
											else  pInitCfg  =  &gAvParams.HD_av;									  
									  }
								  }								  

								  pCompressor->video.common.usMaxFps_toShareBmp  =  pInitCfg->usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  pInitCfg->usFps_toShareBmp_videoConference;						//  2012/02/16
								  //
								  pCompressor->video.common.iWidth_pic  =  pInitCfg->iW_av;									
								  pCompressor->video.common.iHeight_pic  =  pInitCfg->iH_av;
								  }
								  break;
							case  CONST_policyAvLevel_1080p:  {
								  myVIDEO_init_cfg  *  pInitCfg  =  &gAvParams.fullHD;  
								  if  (  uiCapType  ==  CONST_capType_av  )  {
									  if  (  iCapUsage  ==  CONST_capUsage_3dConf  )  {
										  ;
										  }
									  else  {
										    if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  pInitCfg  =  &gAvParams.fullHD_webcam;									  
											else  pInitCfg  =  &gAvParams.fullHD_av;									  
									  }
								  }								  

								  pCompressor->video.common.usMaxFps_toShareBmp  =  pInitCfg->usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  pInitCfg->usFps_toShareBmp_videoConference;						//  2012/02/16
								  //
								  pCompressor->video.common.iWidth_pic  =  pInitCfg->iW_av;									
								  pCompressor->video.common.iHeight_pic  =  pInitCfg->iH_av;
								  }
								  break;
								  //
																  //
							case  CONST_policyAvLevel_1080p60: {
								myVIDEO_init_cfg* pInitCfg = &gAvParams.fullHD60;

								pCompressor->video.common.usMaxFps_toShareBmp = pInitCfg->usMaxFps_toShareBmp;										//  2008/12/6,
								pCompressor->usFrames_perSecond_videoConference = pInitCfg->usFps_toShareBmp_videoConference;						//  2012/02/16
								//
								pCompressor->video.common.iWidth_pic = pInitCfg->iW_av;
								pCompressor->video.common.iHeight_pic = pInitCfg->iH_av;
							}
														  
															 break;
														   //
							case  CONST_policyAvLevel_2160p: {
								myVIDEO_init_cfg* pInitCfg = &gAvParams.video4k;

								pCompressor->video.common.usMaxFps_toShareBmp = pInitCfg->usMaxFps_toShareBmp;										//  2008/12/6,
								pCompressor->usFrames_perSecond_videoConference = pInitCfg->usFps_toShareBmp_videoConference;						//  2012/02/16
								//
								pCompressor->video.common.iWidth_pic = pInitCfg->iW_av;
								pCompressor->video.common.iHeight_pic = pInitCfg->iH_av;
							}
															 break;



							case  CONST_policyAvLevel_2160p60: {
								myVIDEO_init_cfg* pInitCfg = &gAvParams.video4k60;

								pCompressor->video.common.usMaxFps_toShareBmp = pInitCfg->usMaxFps_toShareBmp;										//  2008/12/6,
								pCompressor->usFrames_perSecond_videoConference = pInitCfg->usFps_toShareBmp_videoConference;						//  2012/02/16
								//
								pCompressor->video.common.iWidth_pic = pInitCfg->iW_av;
								pCompressor->video.common.iHeight_pic = pInitCfg->iH_av;
							}
														   break;


								  //
							case  CONST_policyAvLevel_240p:
								{
								  myVIDEO_init_cfg  *  pInitCfg  =  &gAvParams.LD;
								  if  (  uiCapType  ==  CONST_capType_av  )  {
									  pInitCfg  =  &gAvParams.LD_av;
								  }

								  //
								  pCompressor->video.common.usMaxFps_toShareBmp  =  pInitCfg->usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  pInitCfg->usFps_toShareBmp_videoConference;						//  2012/02/16
								  //
								  pCompressor->video.common.iWidth_pic  =  pInitCfg->iW_av;									
								  pCompressor->video.common.iHeight_pic  =  pInitCfg->iH_av;
								  }
								  break;
							case  CONST_policyAvLevel_256x144:
							default:
							{
								myVIDEO_init_cfg* pInitCfg = &gAvParams.QCIF;

								//
								pCompressor->video.common.usMaxFps_toShareBmp = pInitCfg->usMaxFps_toShareBmp;										//  2008/12/6,
								pCompressor->usFrames_perSecond_videoConference = pInitCfg->usFps_toShareBmp_videoConference;						//  2012/02/16
								//
								pCompressor->video.common.iWidth_pic = pInitCfg->iW_av;
								pCompressor->video.common.iHeight_pic = pInitCfg->iH_av;
							}



								break;


					}
				break;
	 }

	 pRegVal  = (TCHAR*)_T(  CONST_regValName_usMaxFps_toShareBmp  );
	 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  (  short  )_tcstol(  tBuf,  &pT,  10  );
	 if  (  lVal  >  0  &&  lVal  <=  MAX_usFps_toShareBmp  )  pCompressor->video.common.usMaxFps_toShareBmp  =  (  unsigned  short  )lVal;
	 //
	 if  (  pQyMc->cfg.bGetPolicyFromIni  )  {
		if  (  !getCfgValByName(  pQyMc->cfg.iniFullFileName,  (char*)CONST_regValName_usMaxFps_toShareBmp,  buf,  sizeof(  buf  )  )  )  {
			trim(  buf  );
			lVal  =  (  unsigned  short  )atol(  buf  );
			if  (  lVal  &&  lVal  <=  MAX_usFps_toShareBmp  )  {
				pCompressor->video.common.usMaxFps_toShareBmp  =  lVal;
			}
		}
	 }

	 pRegVal  = (TCHAR*)_T(  CONST_regValName_usMinFps_toShareBmp  );
	 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  (  short  )_tcstol(  tBuf,  &pT,  10  );
	 if  (  lVal  >  0  &&  lVal  <=  pCompressor->video.common.usMaxFps_toShareBmp  )  pCompressor->video.common.usMinFps_toShareBmp  =  (  unsigned  short  )lVal;

	 //  2012/07/01
	 pRegVal  = (TCHAR*)_T(  CONST_regValName_ucSeconds_perFrame  );
	 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  (  short  )_tcstol(  tBuf,  &pT,  10  );
	 if  (  lVal  >  0  &&  lVal  <=  MAX_ucSeconds_perFrame  )  pCompressor->video.common.ucSeconds_perFrame  =  (  unsigned  short  )lVal;


	 //
	 switch  (  uiCapType  )  {
			 case  CONST_capType_mosaic:
				   switch  (  level  )  {
						   case  CONST_policyAvLevel_848x480:  {  //  2014/11/15
								pRegVal  = (TCHAR*)_T(  CONST_regValName_iWidth_pic  );
								if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  )  tBuf[0]  =  0;
								lVal  =  _ttol(  tBuf  );
								if  (  lVal  >  0  )  {
									pCompressor->video.common.iWidth_pic  =  lVal;
								}	 			 
								pRegVal  = (TCHAR*)_T(  CONST_regValName_iHeight_pic  );
								if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  )  tBuf[0]  =  0;
								lVal  =  _ttol(  tBuf  );					
								if  (  lVal  >  0  )  {					
									pCompressor->video.common.iHeight_pic  =  lVal;
								}
						        }
								 break;
						   case  CONST_policyAvLevel_dev_5fps1: 
								 break;
  				   }
				   break;
			 case  CONST_capType_screen:
			 case  CONST_capType_av: 
			 default:
				    if  (  uiCapType  ==  CONST_capType_screen  
						//||  (  uiCapType  ==  CONST_capType_mediaDevice  &&  uiSubCapType  ==  CONST_subCapType_unresizable  )  
						)
					{
						break;
					}
				    //
#if 0
					pRegVal  = (TCHAR*)_T(  CONST_regValName_iWidth_pic  );
					if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  )  tBuf[0]  =  0;
					lVal  =  _ttol(  tBuf  );
					if  (  lVal  >  0  )  {
						pCompressor->video.common.iWidth_pic  =  lVal;
					}	 			 
					pRegVal  = (TCHAR*)_T(  CONST_regValName_iHeight_pic  );
					if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  )  tBuf[0]  =  0;
					lVal  =  _ttol(  tBuf  );					
					if  (  lVal  >  0  )  {					
						pCompressor->video.common.iHeight_pic  =  lVal;
					}
#endif
	 }

	 //  2011/12/10
	 switch  (  pCompressor->video.common.ucCompressors  )  {
			 case  CONST_videoCompressors_hwAccl:		//  2011/12/10, 调用ipp的rgb2Yv12的转换函数，送出的是翻转的图像
				   #if  0	//  201405/24. 中间过程存储时，也变成倒立了，很不方便。另外也容易出错，所以不用这种方式了
						pCompressor->video.common.ucbOutputFlippedImg  =  TRUE;
				   #endif
				   //  2012/02/08
				   pRegVal  = (TCHAR*)_T(  CONST_regValName_videoEffect  );
				   if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
					   pCompressor->video.common.iTargetUsage  =  _ttol(  tBuf  );
				   }
				   if  (  !pCompressor->video.common.iTargetUsage  )  pCompressor->video.common.iTargetUsage  =  DEFAULT_iTargetUsage;
				   //  2016/04/17
				   pRegVal  = (TCHAR*)_T(  CONST_regValName_avgBitrate  );
				   if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
					   pCompressor->video.common.iAvgBitrate  =  _ttol(  tBuf  );
				   }
				   //
#if  0
				   int  iResId;  iResId  =  0;
				   int  iDefault_bitrate;  iDefault_bitrate  =  0;				   
				   get_resIdTable(  level,  fourccStr2i(  pCompressor->video.common.fourccStr  ),  &iResId,  &iDefault_bitrate  );  
				   if  (  !pCompressor->video.common.iAvgBitrate  
					   ||  !qyGetDesByType(  getResTable(  0,  &pQyMc->cusRes,  iResId  ),  pCompressor->video.common.iAvgBitrate  )  )
				   {
					   pCompressor->video.common.iAvgBitrate  =  iDefault_bitrate;
				   }
#endif

				   //
				   if  (  pCompressor->video.common.iAvgBitrate <=  0  )  {
					   int  nBitRate  =  myGetBitrate(  &pCompressor->video.common,  pCompressor->video.common.iWidth_pic,  pCompressor->video.common.iHeight_pic  );
					   pCompressor->video.common.iAvgBitrate=nBitRate;
				   }


				   break;
			 default:
					 break;
	 }

	 return  0;
}


 int  saveCompressorCfg(  QY_REG  reg,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor  )
{
	QY_MC			*	pQyMc		=  QY_GET_GBUF(  );
	CQyString			rootKeyStr;
	//  TCHAR		*	pRegVal;
	TCHAR				tBuf[256]	=  _T(  ""  );
	//  char			buf[128];
	TCHAR			name[128]		=	_T(  ""  );
	TCHAR		*	pT;
	//  long			lVal;

#if  0
	 if  (  !(  pT  =  qyGetDesByType(  CONST_capTypeTable,  uiCapType  )  )  )  return  -1;		 
	 if  (  !pT[0]  )  return  -1;
	 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s"  ),  pT  );
	 if  (  uiSubCapType  )  {
		 if  (  !(  pT  =  qyGetDesByType(  CONST_subCapTypeTable,  uiSubCapType  )  )  )  return  -1;
		 if  (  !pT[0]  )  return  -1;
		 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s.%s"  ),  name,  pT  );
	 }

	 //
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  name  );
	 rootKeyStr  =  CQyString(  tBuf  );
#endif
	 getRegRootKey_qmc(  uiCapType,  uiSubCapType,  iCapUsage,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	 rootKeyStr  =  CQyString(  reg.rootKey  );

	 //  2014/04/26                                                            
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_ucbSetDevResolution  ),  CQyString(  _ltot(  pCompressor->video.dev.ucbSetDevResolution,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_iDevWidth  ),  CQyString(  _ltot(  pCompressor->video.dev.iWidth,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_iDevHeight  ),  CQyString(  _ltot(  pCompressor->video.dev.iHeight,  tBuf,  10  )  )  );
			
	//	
	//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  name  );	
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\level%d"  ),  reg.rootKey,  level  );
	rootKeyStr  =  CQyString(  tBuf  );

	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_audioCompressors  ),  CQyString(  _ltot(  pCompressor->audio.common.ucCompressors,  tBuf,  10  )  )  );	
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_audioCompressorName  ),  CQyString(  pCompressor->audio.compressorName  )  );

	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_wfx_enc_wFormatTag  ),  CQyString(  _ltot(  pCompressor->audio.wf_compress.wFormatTag,  tBuf,  10  )  )  );	
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_wfx_enc_nChannels  ),  CQyString(  _ltot(  pCompressor->audio.wf_compress.nChannels,  tBuf,  10  )  )  );	
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_wfx_enc_nSamplesPerSec  ),  CQyString(  _ltot(  pCompressor->audio.wf_compress.nSamplesPerSec,  tBuf,  10  )  )  );	
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_wfx_enc_nAvgBytesPerSec  ),  CQyString(  _ltot(  pCompressor->audio.wf_compress.nAvgBytesPerSec,  tBuf,  10  )  )  );	
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_wfx_enc_wBitsPerSample  ),  CQyString(  _ltot(  pCompressor->audio.wf_compress.wBitsPerSample,  tBuf,  10  )  )  );	

	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiBytesRecorded_perBlockAlign,  CQyString(  _ltot(  pCompressor->audio.uiBytesRecorded_perBlockAlign,  tBuf,  10  )  )  );	
	//
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_ucbOrgAudioFmt,  CQyString(  _ltot(  pCompressor->audio.dev.ucbSetOrgAudioFmt,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiChannel,  CQyString(  _ltot(  pCompressor->audio.dev.wf_org_suggested.nChannels,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiSample,  CQyString(  _ltot(  pCompressor->audio.dev.wf_org_suggested.nSamplesPerSec,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiBit,  CQyString(  _ltot(  pCompressor->audio.dev.wf_org_suggested.wBitsPerSample,  tBuf,  10  )  )  );

	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_audio_avgBitrate,  CQyString(  _ltot(  pCompressor->audio.common.iAvgBitrateInKbps,  tBuf,  10  )  )  );	
	//  2010/03/11
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiMinTimeInMsOfAudioDataPlaying,  CQyString(  _ltot(  pCompressor->audio.playCfg.usMinTimeInMsOfAudioDataPlaying,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiAudioDataAddedToPlayEveryTime,  CQyString(  _ltot(  pCompressor->audio.playCfg.usAudioDataAddedToPlayEveryTime,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiNotifyIntervalInMs_needMoreAudioData,  CQyString(  _ltot(  pCompressor->audio.playCfg.usNotifyIntervalInMs_needMoreAudioData,  tBuf,  10  )  )  );
	//  2012/01/27
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiMinTimeInMsToPlay,  CQyString(  _ltot(  pCompressor->audio.playCfg.usMinTimeInMsToPlay,  tBuf,  10  )  )  );
	//
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiMaxTimeInMsToPlay,  CQyString(  _ltot(  pCompressor->audio.playCfg.usMaxTimeInMsToPlay,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiMaxTimeInMsToBeRemoved,  CQyString(  _ltot(  pCompressor->audio.playCfg.usMaxTimeInMsToBeRemoved,  tBuf,  10  )  )  );

	//
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_iWidth_pic  ),  CQyString(  _ltot(  pCompressor->video.common.iWidth_pic,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_iHeight_pic  ),  CQyString(  _ltot(  pCompressor->video.common.iHeight_pic,  tBuf,  10  )  )  );
	//
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_videoCompressors  ),  CQyString(  _ltot(  pCompressor->video.common.ucCompressors,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_videoCompressorName  ),  CQyString(  pCompressor->video.compressorName  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_v_fourccStr  ),  CQyString(  pCompressor->video.common.fourccStr  )  );
	//  2012/02/08
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_videoEffect  ),  _ltot(  pCompressor->video.common.iTargetUsage,  tBuf,  10  )  );
	//  2012/06/27
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_avgBitrate  ),  _ltot(  pCompressor->video.common.iAvgBitrate,  tBuf,  10  )  );
	//
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_usMaxFps_toShareBmp  ), _ltot(  pCompressor->video.common.usMaxFps_toShareBmp,  tBuf,  10  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_usMinFps_toShareBmp  ), _ltot(  pCompressor->video.common.usMinFps_toShareBmp,  tBuf,  10  )  );
	//  2012/07/01
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_ucSeconds_perFrame  ),  _ltot(  pCompressor->video.common.ucSeconds_perFrame,   tBuf,  10  )  );

	return  0;
}


 //
__declspec(dllexport) CQyString  getCompressorDesc(  unsigned  int  uiCapType,  AV_COMPRESSOR_CFG  *  pCompressor  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  _T(  ""  );
	PolicyAvParams		&	gAvParams	=	*pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );
	TCHAR	tBuf[256]	=	_T(  ""  );
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );

	switch  (  uiCapType  )  {
			case  CONST_capType_av:
			case  CONST_capType_mediaFile:
			case  CONST_capType_mediaDevice:
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "(%d,%d,%d)%d"  ),  pCompressor->audio.wf_decompress_default.nChannels,  pCompressor->audio.wf_decompress_default.nSamplesPerSec,  pCompressor->audio.wf_decompress_default.wBitsPerSample,  pCompressor->audio.uiBytesRecorded_perBlockAlign  );
				  GUID guid_wFormatTag; guid_wFormatTag = FOURCCMap(pCompressor->audio.wf_compress.wFormatTag);
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s:%s(%d,%d,%d,%d)"  ),  tBuf,  qyGetDesByType1(  gAvParams.pAudioCompressorsTable,  pCompressor->audio.common.ucCompressors  ),  getMediaSubtypeName(guid_wFormatTag  ),  pCompressor->audio.wf_compress.nChannels,  pCompressor->audio.wf_compress.nSamplesPerSec,  pCompressor->audio.wf_compress.wBitsPerSample,  pCompressor->audio.wf_compress.nAvgBytesPerSec  );
				  if  (  pCompressor->audio.common.ucCompressors  ==  CONST_audioCompressors_ipp  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,%dkbps"  ),  tBuf,  pCompressor->audio.common.iAvgBitrateInKbps  );
				  }

				  int  iDelayInMs;
				  iDelayInMs  =  MACRO_getDelayInMs(  pCompressor->audio.playCfg  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %.1fs"  ),  tBuf,  iDelayInMs  /  1000.  );

				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, "  ),  tBuf  );
				  if  (  pCompressor->video.dev.ucbSetDevResolution  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%dX%d->"  ),  tBuf,  pCompressor->video.dev.iWidth,  pCompressor->video.dev.iHeight  );
				  }
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%dX%d %dfps"  ),  tBuf,  pCompressor->video.common.iWidth_pic,  pCompressor->video.common.iHeight_pic,  (  int  )pCompressor->video.common.usMaxFps_toShareBmp  );

				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s:%s"  ),  tBuf,  qyGetDesByType1(  gAvParams.pVideoCompressorsTable,  pCompressor->video.common.ucCompressors  ),  CQyString(  pCompressor->video.common.fourccStr  )  );
				  if  (  pCompressor->video.common.iTargetUsage  )_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iTargetUsageTable  ),  pCompressor->video.common.iTargetUsage  )  );
				  if  (  pCompressor->video.common.iAvgBitrate  ) {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %dk"  ),  tBuf,  pCompressor->video.common.iAvgBitrate  /  1000  );
				  }
				  break;

			case  CONST_capType_screen:
			case  CONST_capType_mosaic:
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ",,,%dfps, %s:%s"  ),  (  int  )pCompressor->video.common.usMaxFps_toShareBmp,  qyGetDesByType1(  gAvParams.pVideoCompressorsTable,  pCompressor->video.common.ucCompressors  ),  CQyString(  pCompressor->video.common.fourccStr  )  );
				  if  (  pCompressor->video.common.ucCompressors  ==  CONST_videoCompressors_ipp  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dkbps"  ),  tBuf,  pCompressor->video.common.iAvgBitrate  /  1000  );
				  }
				  break;
			default:
				    break;
	}

	return  CQyString(  tBuf  );
 }


//  #define		MACRO_getuiBytesRecorded_perBlockAlign(  audioCompressor  )		(  (  (  audioCompressor.ucCompressors  ==  CONST_audioCompressors_acm  )  ?  1  :  1  )  *  audioCompressor.wf_decompress_default.nSamplesPerSec  /  5  )
__declspec(  dllexport  )   int  MACRO_getuiBytesRecorded_perBlockAlign(  AUDIO_COMPRESSOR_CFG  &audioCompressor,  WAVEFORMATEX  *  pWf_org  )		
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	PolicyAvParams		&	gAvParams	=	*pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );

	//
	int  uiBytesRecorded_perBlockAlign	=	-1;
	
	//  2013/03/09
	//if  (  !memcmp(  &audioCompressor.playCfg,  &gAvParams.CONST_audioPlayCfg_07s,  sizeof(  audioCompressor.playCfg  )  )  )  
	{
		//
		if  (  !(  pWf_org->nSamplesPerSec  %  100  )  )  {
			uiBytesRecorded_perBlockAlign  =  pWf_org->nSamplesPerSec  /  100  *  1;
			return  uiBytesRecorded_perBlockAlign;
		}		

		//  2017/10/13
#if  10
		if  (  !(  pWf_org->nSamplesPerSec  %  25  )  )  {
			uiBytesRecorded_perBlockAlign  =  pWf_org->nSamplesPerSec  /  25;
			return  uiBytesRecorded_perBlockAlign;
		}
#endif
			
	}

	//
	uiBytesRecorded_perBlockAlign  =  pWf_org->nSamplesPerSec  /  5;

	return  uiBytesRecorded_perBlockAlign;
}


//  2011/08/07
#ifndef  __DEBUG__
		 #define		DEFAULT_policyAvLevel_req							CONST_policyAvLevel_480p					//  sd
		 //#define		DEFAULT_policyAvLevel_req							CONST_policyAvLevel_1080p					//  sd
#else
		//#define		DEFAULT_policyAvLevel_req								CONST_policyAvLevel_480p					//  sd
		//#define		DEFAULT_policyAvLevel_req								CONST_policyAvLevel_720p					//  sd
		#define		DEFAULT_policyAvLevel_req								CONST_policyAvLevel_1080p					//  sd
#endif


 //  2011/12/13
 __declspec(  dllexport  )  int  getDefaultPolicyAvLevel(  QY_MC  *  pQyMc,  unsigned  int  uiCapType,  unsigned int uiSubCapType,  int iCapUsage  )
{
	int	ucCmd = 0;

	//
	switch  (  uiCapType  )  {
			case  CONST_capType_av:
				  if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
					  ucCmd  =  DEFAULT_policyAvLevel_req_webcam;
					  }
				  else  {
					    if  (  iCapUsage  ==  CONST_capUsage_conf  )  {
							ucCmd  =  DEFAULT_policyAvLevel_reply_hd;
							//if  (  qyGetAppAvLevel_qyMc(  pQyMc  )  ==  CONST_qyAppAvLevel_fullHd  )  ucCmd  =  DEFAULT_policyAvLevel_reply_fullHd;			
							//  2017/08/27
							if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_bjyz  )  ucCmd  =  CONST_policyAvLevel_480p;
							}
						else  {  //  2014/05/19
							  ucCmd  =  DEFAULT_policyAvLevel_req;
							  if  (  !b2Core(  )  )  ucCmd  =  CONST_policyAvLevel_240p;		

							  //
							  if  (  pQyMc->appParams.bUse_forTest_defaultAvLevel_240p  )  {
								  ucCmd=CONST_policyAvLevel_240p;
								  showInfo_open0(  0,  0,  _T(  "for test: getDefaultPolicyAvLevel returns 240p"  )  );
							  }
							  //
						}			
				  }			
				  break;
			case  CONST_capType_screen:			
				  ucCmd  =  DEFAULT_policyAvLevel_req_screen;
				  //  if  (  qyGetAppAvLevel_qyMc(  )  <=  CONST_qyAppAvLevel_sd  )  ucCmd  =  DEFAULT_policyAvLevel_req_screen_basic;
				  //if  (  qyGetAppAvLevel_qyMc(  pQyMc  )  <=  CONST_qyAppAvLevel_sd  )  ucCmd  =  DEFAULT_policyAvLevel_req_screen;
				  break;
			case  CONST_capType_mediaFile:			
				  ucCmd  =  DEFAULT_policyAvLevel_req_mediaFile;
				  //if  (  qyGetAppAvLevel_qyMc(  pQyMc  )  <=  CONST_qyAppAvLevel_sd  )  ucCmd  =  DEFAULT_policyAvLevel_req_mediaFile_basic;
				  break;
			case  CONST_capType_mediaDevice:
				  if  (  uiSubCapType  ==  CONST_subCapType_unresizable  )  {  //  2015/03/11
					  ucCmd  =  DEFAULT_policyAvLevel_req_unresizable;
					  //if  (  qyGetAppAvLevel_qyMc(  pQyMc  )  <=  CONST_qyAppAvLevel_sd  )  ucCmd  =  DEFAULT_policyAvLevel_req_unresizable_basic;				
					  }
				  else  {				  
					    ucCmd  =  DEFAULT_policyAvLevel_req_mediaDevice;		
						//if  (  qyGetAppAvLevel_qyMc(  pQyMc  )  <=  CONST_qyAppAvLevel_sd  )  ucCmd  =  DEFAULT_policyAvLevel_req_mediaDevice_basic;			
				  }
				  break;
			case  CONST_capType_mosaic:	
				  if  (  uiSubCapType ==  CONST_subCapType_mosaic_video  )  {				
					  ucCmd  =  DEFAULT_policyAvLevel_mosaic_video;
				  }
				  else if  (  uiSubCapType ==  CONST_subCapType_mosaic_resource  )  {				
						   ucCmd  =  DEFAULT_policyAvLevel_req_screen;			
				  }			
				  break;		
			case  CONST_capType_slave:  //  2016/04/06
				  ucCmd  =  DEFAULT_policyAvLevel_slave_video;
				  break;

			default:
				    break;
	}
	return  ucCmd;
}


 //  2014/04/10
 __declspec(  dllexport  )  int  getPolicyAvLevel(  QY_MC  *  pQyMc,  unsigned  int  uiCapType,  unsigned int uiSubCapType,  int iCapUsage  )
 {
	 int					iLevel			=	0;

	 if  (  !pQyMc  )  return  0;
	 
	 //
	 QY_REG					reg;
	 TCHAR				*	pRegVal;
	 TCHAR					tBuf[128]		=	_T( "" );

	 QY_DMITEM			*	pTable			=	NULL;

	 memset(  &reg,  0,  sizeof(  reg  )  );

	 reg.hKeyRoot0  =  HKEY_CURRENT_USER;
#if  0
	 _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );

	 if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  
	 {
		 _sntprintf(  tRootKey,  mycountof(  tRootKey  ),  _T(  "%s\\%s.%s"  ),  reg.rootKey,  qyGetDesByType(  CONST_capTypeTable,  uiCapType  ),  qyGetDesByType(  CONST_subCapTypeTable,  uiSubCapType  )  );
	 }
	 else
	 {
		  _sntprintf(  tRootKey,  mycountof(  tRootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  qyGetDesByType(  CONST_capTypeTable,  uiCapType  )  );
	 }
#endif
	 getRegRootKey_qmc(  uiCapType,  uiSubCapType,  iCapUsage,  reg.rootKey,  mycountof(  reg.rootKey  )  );
		 
	//if  (  bReply  )  pRegVal  =  CONST_regValName_policyAvLevel_conf;
	//else  
		pRegVal  = (TCHAR*)CONST_regValName_policyAvLevel_req;
	
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )    
		 &&  _ttol(  tBuf  )  )  
	 {
		 iLevel  =  (  unsigned char  )_ttol(  tBuf  );
	 }

	//  2014/05/05
	 if (!iLevel) {
		 iLevel = getDefaultPolicyAvLevel(pQyMc, uiCapType, uiSubCapType, iCapUsage);
	 }

	 //
	 return  iLevel;

 }



 //
 //
#define		DEFAULT_conf_fourcc_confServ		CONST_fourcc_h264	//h264
#define		DEFAULT_conf_fourcc_others			CONST_fourcc_vp80	//h264


//
QY_DMITEM  CONST_conf_fourccTable[]  =
{
	{	CONST_fourcc_h264,	},
	{	CONST_fourcc_vp80,	},
	{	CONST_fourcc_HEVC,	},
	{	CONST_fourcc_AV01,	},
	{	-1,					},

};


//
 //
__declspec(dllexport)  int  get_conf_fps()
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	TCHAR  tBuf[128];
	char  buf[128];


	if (qyGetRegCfgT(HKEY_CURRENT_USER, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, _T(CONST_regValName_conf_usMaxFps_toShareBmp), (char*)tBuf, sizeof(tBuf), NULL)) {
		tBuf[0] = 0;
	}
	myTChar2Utf8(tBuf, buf, sizeof(buf));
	int  fps = atol(buf);
	if (fps <= 0 || fps > 120) {
		fps = 30;
	}

	//
	return  fps;
}


//
__declspec(dllexport)  BOOL  get_conf_b100k()
{
	BOOL				b100k = FALSE;

	QY_MC* pQyMc = QY_GET_GBUF();


	TCHAR				tBuf[256] = _T("");
	QY_REG				reg;


	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	lstrcpyn(reg.rootKey, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, sizeof(reg.rootKey));

	//  2014/04/08
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_ucb100k, (char*)tBuf, sizeof(tBuf), 0) && _ttol(tBuf)) {
		b100k = TRUE;
	}

	return  b100k;
}


//
__declspec(dllexport)  BOOL  get_conf_bLyra()
{
	BOOL				b100k = FALSE;

	QY_MC* pQyMc = QY_GET_GBUF();


	TCHAR				tBuf[256] = _T("");
	QY_REG				reg;


	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	lstrcpyn(reg.rootKey, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, sizeof(reg.rootKey));

	//  2014/04/08
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_bLyra, (char*)tBuf, sizeof(tBuf), 0) && _ttol(tBuf)) {
		b100k = TRUE;
	}

	return  b100k;
}




 //
 __declspec(  dllexport  )  int  get_conf_iFourcc(  )
{
	CCtxQyMc  *  pQyMc  =  QY_GET_GBUF(  );
	TCHAR  tBuf[128];
	char  buf[128];

	
	if  (  qyGetRegCfgT(  HKEY_CURRENT_USER,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  _T(  CONST_regValName_conf_fourcc  ),  (char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  )  {
		tBuf[0]  =  0;
	}
	myTChar2Utf8(  tBuf,  buf,  sizeof(  buf  )  );
	int  iFourcc  =  fourccStr2i(  buf  );
	if  (  !qyGetDmItemByType(  CONST_conf_fourccTable,  iFourcc,  sizeof(  QY_DMITEM  )  )  )  {
		//
		if  (  pQyMc->appParams.bConfServer  )  iFourcc  =   DEFAULT_conf_fourcc_confServ;
		else  iFourcc  =  DEFAULT_conf_fourcc_others;
	}

	return  iFourcc;
}


 //
 __declspec(  dllexport  )  int  set_conf_iFourcc(  int  conf_iFourcc,  int conf_bitrateInKbps, AV_COMPRESSOR_CFG  *  pCompressor  )
 {
	 QY_DMITEM  *  pItem;
	 for  (  pItem  =  CONST_conf_fourccTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 if  (  pItem->type  ==  conf_iFourcc  )  break;
	 }
	 if  (  pItem->type  ==  -1  )  return  -1;

	 //
	 iFourcc2Str(  conf_iFourcc,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
	 switch  (  conf_iFourcc  )  {
			 case  CONST_fourcc_vp80:
				   pCompressor->video.common.ucCompressors  =  CONST_videoCompressors_vp8;
				   break;
			 default:
				    pCompressor->video.common.ucCompressors  =  CONST_videoCompressors_hwAccl;
					break;
	 }

	 //
	 if (conf_iFourcc == CONST_fourcc_HEVC
		 ||  conf_iFourcc  ==  CONST_fourcc_h264) 
	 {
		 if (conf_bitrateInKbps) {
			 pCompressor->video.common.iAvgBitrate = conf_bitrateInKbps * 1000;
			 }
		 else {
			 pCompressor->video.common.iAvgBitrate = 0;
			 pCompressor->video.common.iAvgBitrate = myGetBitrate(&pCompressor->video.common, pCompressor->video.common.iWidth_pic, pCompressor->video.common.iHeight_pic);
		 }
		 //
		 int  ii = 0;
	 }


	 //
	 return  0;
 }



 //
  __declspec(  dllexport  )  int  get_conf_usMaxSpeakers(  )
{
	CCtxQyMc  *  pQyMc  =  QY_GET_GBUF(  );
	TCHAR  tBuf[128];
	char  buf[128];

	
	if  (  qyGetRegCfgT(  HKEY_CURRENT_USER,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  _T(  CONST_regValName_conf_usMaxSpeakers  ),  (char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  )  {
		tBuf[0]  =  0;
	}
	myTChar2Utf8(  tBuf,  buf,  sizeof(  buf  )  );
	ushort  usMaxSpeakers  =  atol(  buf  );
	if  ( usMaxSpeakers  <=0  ||  usMaxSpeakers  >  MAX_speakers_taskAv  ) {
		usMaxSpeakers  =  DEFAULT_usMaxSpeakers;
	}

	return  usMaxSpeakers;
}


  //
  __declspec(dllexport)  int  get_conf_bitrateInKbps(int *pbitrateInKbps_dl,int *pbitrateInKbps_ul)
  {
	  CCtxQyMc* pQyMc = QY_GET_GBUF();
	  TCHAR  tBuf[128];
	  char  buf[128];


	  if (qyGetRegCfgT(HKEY_CURRENT_USER, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, _T(CONST_regValName_conf_bitrateInKbps_dl), (char*)tBuf, sizeof(tBuf), NULL)) {
		  tBuf[0] = 0;
	  }
	  myTChar2Utf8(tBuf, buf, sizeof(buf));
	  int bitrateInKbps = atol(buf);
	  if (bitrateInKbps <= 0 || bitrateInKbps > MAX_bitrateInKbps) {
		  bitrateInKbps = 0;
	  }

	  if (pbitrateInKbps_dl)  *pbitrateInKbps_dl = bitrateInKbps;

	  //
	  if (qyGetRegCfgT(HKEY_CURRENT_USER, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, _T(CONST_regValName_conf_bitrateInKbps_ul), (char*)tBuf, sizeof(tBuf), NULL)) {
		  tBuf[0] = 0;
	  }
	  myTChar2Utf8(tBuf, buf, sizeof(buf));
	  bitrateInKbps = atol(buf);
	  if (bitrateInKbps <= 0 || bitrateInKbps > MAX_bitrateInKbps) {
		  bitrateInKbps = 0;
	  }

	  if (pbitrateInKbps_ul)  *pbitrateInKbps_ul = bitrateInKbps;

	  //
	  return  0;
  }




////////////////////////////


 //
#if 0
  __declspec(dllexport)  int  get_2ndMcu(char  *  ipBuf,  int  ipBufSize)
  {
	  int  iErr = -1;
	  CCtxQyMc* pQyMc = QY_GET_GBUF();
	  TCHAR  tBuf[128];
	  char  buf[128];

	  do {

		  if (qyGetRegCfgT(HKEY_CURRENT_USER, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, _T(CONST_regValName_2ndMcu), (char*)tBuf, sizeof(tBuf), NULL)) {
			  tBuf[0] = 0;
		  }
		  myTChar2Utf8(tBuf, buf, sizeof(buf));
		  if (!bIpValid(buf)) break;
		  		
		  safeStrnCpy(buf, ipBuf, ipBufSize);
		  
		  iErr = 0;

	  } while (false);


	  return  iErr;
  }


  //
  __declspec(dllexport)  int  set_2ndMcu(char  *  ip)
  {
	  CCtxQyMc* pQyMc = g_pQyMc;

	  TCHAR  tBuf[128];
	  myUtf82TChar(ip, tBuf, mycountof(tBuf));

	  //
	  qySetRegCfgT(HKEY_CURRENT_USER, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, _T(CONST_regValName_2ndMcu ), tBuf);


	  //
	  return  0;
  }
#endif



