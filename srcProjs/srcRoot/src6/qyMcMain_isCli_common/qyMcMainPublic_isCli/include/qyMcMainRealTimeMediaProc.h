


#ifndef  __QYMCMAINREALTIMEMEDIAPROC_H__
#define  __QYMCMAINREALTIMEMEDIAPROC_H__	//  {

#define		MAX_inputBuffers											5


//  采样率。

//  8000,11025,22050,44100

#define			DEFAULT_iHertz_pcm_av_old								11025
#define			DEFAULT_nChannels_pcm_av_old							2
#define			DEFAULT_wBitsPerSample_pcm_av_old						16

//  2009/05/16
#if  0
	#define			DEFAULT_iHertz_pcm_av								44100
	#define			DEFAULT_nChannels_pcm_av							2
	#define			DEFAULT_wBitsPerSample_pcm_av						16
#else
	//  #define		DEFAULT_iHertz_pcm_av								8000
	#define			DEFAULT_iHertz_pcm_av								16000		//  2013/05/25. aec's internal nSamples
	#define			DEFAULT_nChannels_pcm_av							1
	#define			DEFAULT_wBitsPerSample_pcm_av						16
#endif

//  2009/05/05
#define			DEFAULT_iHertz_pcm_mediaFile							44100
#define			DEFAULT_nChannels_pcm_mediaFile							2
#define			DEFAULT_wBitsPerSample_pcm_mediaFile					16

//  2012/01/04
#define			DEFAULT_iHertz_pcm_mediaDevice							44100
#define			DEFAULT_nChannels_pcm_mediaDevice						2
#define			DEFAULT_wBitsPerSample_pcm_mediaDevice					16

//  音量缓存，表明每次读取多少字节发送单元。这个是程序根据采样测试的结果自动调整。
#define		MIN_uiBytesRecorded_perBlockAlign							320						//  2009/05/11
#define		MAX_uiBytesRecorded_perBlockAlign							44100

#define		MIN_audio_uiSample											8000					//  2014/05/24
#define		MAX_audio_uiSample											48000					//  2014/05/24

#define		MIN_uiAudio_avgBitrate										16						//  2014/05/20
#define		MAX_uiAudio_avgBitrate										320						//  2014/05/20


//
#define		MAX_failures_uiBytesRecorded_perBlockAlign					3

#define		DEFAULT_maxusCnt_players									64
#define		DEFAULT_maxusCnt_players_ce									5

//  2012/05/07
#define		DEFAULT_maxusCnt_players_gps								300
#define		DEFAULT_maxusCnt_players_gps_ce								10

//
#define		DEFAULT_usMaxCnt_pSharedObjs								9
#define		DEFAULT_usMaxCnt_pSharedObjs_ce								3

//
#define		DEFAULT_usMaxCnt_qmcObjVarInfos								100						//  2015/11/10

//  2014/09/24
#define		DEFAULT_usMaxCnt_taskInfos									500

//
#define		DEFAULT_usTimeoutInMs_player_a								5000		//  2017/07/03	//  10000					//  2010/06/25
#define		DEFAULT_usTimeoutInMs_player_v								10000

#define		DEFAULT_loopCtrl_timer_dlgTalk_chkRecvdTasks				5			// 7			//  30				//  2010/06/26
#define		DEFAULT_loopCtrl_chkPlayers									5			//10						//  2010/06/26

#define		DEFAULT_loopCtrl_chkTasks									5


/*  error,怀疑是nSamplePerSec的8位造成。
#define		DEFAULT_acm_wFormatTag										WAVE_FORMAT_MULAW
#define		DEFAULT_acm_nChannels										2										
#define		DEFAULT_acm_nSamplesPerSec									22050									
#define		DEFAULT_acm_wBitsPerSample									8										
*/
  
/*
#define		DEFAULT_acm_wFormatTag										WAVE_FORMAT_DSPGROUP_TRUESPEECH
#define		DEFAULT_acm_nChannels										2										
#define		DEFAULT_acm_nSamplesPerSec									16000									
#define		DEFAULT_acm_wBitsPerSample									16								
*/

// 通
/*
#define		DEFAULT_acm_wFormatTag										WAVE_FORMAT_DVI_ADPCM	// Intel Corporation 
#define		DEFAULT_acm_nChannels										1										
#define		DEFAULT_acm_nSamplesPerSec									22050									
#define		DEFAULT_acm_wBitsPerSample									4								
*/

// 通



/*
#define		DEFAULT_acm_wFormatTag											WAVE_FORMAT_PCM
#define		DEFAULT_acm_nChannels											2										
#define		DEFAULT_acm_nSamplesPerSec										11025									
#define		DEFAULT_acm_wBitsPerSample										16								
*/



		//
		#define		DEFAULT_wFormatTag_acm_av								WAVE_FORMAT_ADPCM;  //  2016/12/26, WAVE_FORMAT_GSM610
		#define		DEFAULT_wFormatTag_dmo_av								WAVE_FORMAT_WMAUDIO2
		
		//
		#define		DEFAULT_audioCompressors_mediaFile						CONST_audioCompressors_dmo
		#define		DEFAULT_audioCompressors_mediaDevice					CONST_audioCompressors_ipp
		//
		#define		CONST_audioCompressors_mp3								CONST_audioCompressors_ffmpeg	//CONST_audioCompressors_ipp




#if  DEFAULT_wFormatTag_acm_av  ==  WAVE_FORMAT_ADPCM
	//  #define		DEFAULT_wFormatTag_acm_av								WAVE_FORMAT_ADPCM					//  Microsoft Corporation
	#define		DEFAULT_nChannels_acm_av									1										
	#define		DEFAULT_nSamplesPerSec_acm_av								8000									
	#define		DEFAULT_wBitsPerSample_acm_av								4								
#elif  DEFAULT_wFormatTag_acm_av  ==  WAVE_FORMAT_GSM610
	//  #define		DEFAULT_wFormatTag_acm_av								WAVE_FORMAT_GSM610
	#define		DEFAULT_nChannels_acm_av									1										
	#define		DEFAULT_nSamplesPerSec_acm_av								8000									
	#define		DEFAULT_wBitsPerSample_acm_av								0										
#elif  DEFAULT_wFormatTag_acm_av  ==  WAVE_FORMAT_MPEGLAYER3
	//  #define		DEFAULT_wFormatTag_acm_av								WAVE_FORMAT_MPEGLAYER3
	#define		DEFAULT_nChannels_acm_av									1										
	#define		DEFAULT_nSamplesPerSec_acm_av								8000									
	#define		DEFAULT_wBitsPerSample_acm_av								0								
#endif


//
#if  DEFAULT_wFormatTag_dmo_av  ==  WAVE_FORMAT_MPEGLAYER3
	//  #define		DEFAULT_wFormatTag_dmo_av								WAVE_FORMAT_MPEGLAYER3
	#define		DEFAULT_nChannels_dmo_av									1										
	#define		DEFAULT_nSamplesPerSec_dmo_av								8000									
	#define		DEFAULT_wBitsPerSample_dmo_av								0								
#elif  DEFAULT_wFormatTag_dmo_av  ==  WAVE_FORMAT_WMAUDIO2
	//  #define		DEFAULT_wFormatTag_dmo_av								WAVE_FORMAT_WMAUDIO2			//  Microsoft Corporation
	//  #define		DEFAULT_nChannels_dmo_av									2										
	#define		DEFAULT_nChannels_dmo_av									1										
	//  #define		DEFAULT_nSamplesPerSec_dmo_av								44100
	#define		DEFAULT_nSamplesPerSec_dmo_av								16000
	//  #define		DEFAULT_wBitsPerSample_dmo_av								16
	#define		DEFAULT_wBitsPerSample_dmo_av								16
#endif


//  2009/05/05
#define		DEFAULT_wFormatTag_acm_mediaFile								WAVE_FORMAT_ADPCM		//Microsoft Corporation
#define		DEFAULT_nChannels_acm_mediaFile									2										
#define		DEFAULT_nSamplesPerSec_acm_mediaFile							44100
#define		DEFAULT_wBitsPerSample_acm_mediaFile							4								

//  2009/05/05
#define		DEFAULT_wFormatTag_dmo_mediaFile								WAVE_FORMAT_WMAUDIO2			//Microsoft Corporation
#define		DEFAULT_nChannels_dmo_mediaFile									2										
#define		DEFAULT_nSamplesPerSec_dmo_mediaFile							44100
#define		DEFAULT_wBitsPerSample_dmo_mediaFile							16								



//  2012/01/03
#define		DEFAULT_wFormatTag_acm_mediaDevice								WAVE_FORMAT_ADPCM		//Microsoft Corporation
#define		DEFAULT_nChannels_acm_mediaDevice								2										
#define		DEFAULT_nSamplesPerSec_acm_mediaDevice							44100
#define		DEFAULT_wBitsPerSample_acm_mediaDevice							4
//
#define		DEFAULT_wFormatTag_dmo_mediaDevice								WAVE_FORMAT_WMAUDIO2			//Microsoft Corporation
#define		DEFAULT_nChannels_dmo_mediaDevice								2										
#define		DEFAULT_nSamplesPerSec_dmo_mediaDevice							44100
#define		DEFAULT_wBitsPerSample_dmo_mediaDevice							16								


#endif  //  }



