

#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
//  #include	<Dshow.h>
#include	<mmreg.h>

#include	"qySyncObj.h"
#include	"qisCompressProc.h"

int		tmp_showInfo(  TCHAR  *  hint  );


/*/////////////////////////////////////////////////////////////////////////////////////////// 
// This is a simple code to get started to use H.264 decoder. For more of the code sample, check 
// simpleplaeyr application in the UMC sample code */ 
//#include 
//#include 
#include "ipp.h" 
#include "umc_defs.h" 
//	#include "umc_video_decoder.h" 
//	#include "umc_video_data.h" 
#include "umc_mp3_encoder.h"
#include "umc_mp3_decoder.h"
#include "umc_audio_data.h"
//	#include "umc_mp3_encoder_params.h"
//	#include "umc_mp3dec_fp.h"
//	#include "umc_mp3_decoder_params.h"
//	#include "umc_structures.h" 

void  qdcFreeOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  );

 extern  "C"  int  __declspec(  dllexport  )qdcGetCompressAudioCfg(  WAVEFORMATEX  *  pWf_decompress,  WAVEFORMATEX  *  pWf_compress  )
{
	memset(  pWf_decompress,  0,  sizeof(  pWf_decompress[0]  )  );			//  2012/01/21
	memset(  pWf_compress,  0,  sizeof(  pWf_compress[0]  )  );

#if 0
	pWf_compress->wFormatTag			=	WAVE_FORMAT_PCM;
	pWf_compress->nChannels				=	1;
	pWf_compress->wBitsPerSample		=	16;
	pWf_compress->cbSize				=	0;
	pWf_compress->nSamplesPerSec		=	8000;

	pWf_compress->nBlockAlign		=	(  pWf_compress->wBitsPerSample  /  8  )  *  pWf_compress->nChannels;
	pWf_compress->nAvgBytesPerSec	=	pWf_compress->nSamplesPerSec  *  pWf_compress->nBlockAlign;

	memcpy(  pWf_decompress,  pWf_compress,  sizeof(  pWf_decompress[0]  )  );
#endif
	pWf_compress->wFormatTag			=	WAVE_FORMAT_MPEGLAYER3;
	pWf_compress->nChannels				=	2;
	pWf_compress->wBitsPerSample		=	16;
	pWf_compress->cbSize				=	0;
	pWf_compress->nSamplesPerSec		=	44100;


	pWf_decompress->wFormatTag			=	WAVE_FORMAT_PCM;
	pWf_decompress->nChannels			=	2;
	pWf_decompress->wBitsPerSample		=	16;
	pWf_decompress->cbSize				=	0;
	pWf_decompress->nSamplesPerSec		=	44100;

	pWf_decompress->nBlockAlign		=	(  pWf_decompress->wBitsPerSample  /  8  )  *  pWf_decompress->nChannels;
	pWf_decompress->nAvgBytesPerSec	=	pWf_decompress->nSamplesPerSec  *  pWf_decompress->nBlockAlign;

	return  0;
}



 void  qdcAudioFreeOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_mp3Common  *  pObj	=	(  QDC_OBJ_mp3Common  *  )pQdcObjInfo->var.pObj;
	int			i;

	for  (  i  =  0;  i  <  sizeof(  pObj->outs  )  /  sizeof(  pObj->outs[0]  );  i  ++  )  {
		 if  (  pObj->outs[i].pBuf  )  free(  pObj->outs[i].pBuf  );
	}
	memset(  &pObj->outs,  0,  sizeof(  pObj->outs  )  );
}


void myAudioEncodeStream(QDC_OBJ_INFO  *  pQdcObjInfo, 
					Ipp8u *cPcmData, int iPcmDataLen,  int  iSampleTimeInMs  ) 
{
	QDC_OBJ_mp3Enc  *  pObj  =  (  QDC_OBJ_mp3Enc  *  )pQdcObjInfo->var.pObj;
	UMC::MP3Encoder *  pMp3Encoder  =  (  UMC::MP3Encoder  *  )pObj->pEncoder;
	UMC::MP3Encoder &  MP3Encoder  =  *pMp3Encoder; 
	
	TCHAR  tBuf[256]  = _T(  ""  );

   UMC::Status status;
   UMC::MediaData	DataIn;
   UMC::MediaData	DataOut;

   Ipp32s needSize = pObj->needSize;	//  audio_codec_params.m_SuggestedInputSize;


   //
   if  (  !iPcmDataLen  )  {
	   tmp_showInfo(  _T(  "myAudioEnc failed, iPcmDataLen is 0"  )  );
	   return;
   }

   //  2012/01/25, 
   int  nLeft_last  =  pObj->inputForEnc.len;

   //
   if  (  iPcmDataLen  +  pObj->inputForEnc.len  >  pObj->inputForEnc.uiBufSize  )  
   {
	   //
       //  2017/08/20
	   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "myAudioEnc failed, dataLen too big: iPcmDataLen %d, inpurtForEnc.len %d, uiBufSize %d"  ),
		   iPcmDataLen,  pObj->inputForEnc.len,  pObj->inputForEnc.uiBufSize  );
	   tmp_showInfo(  tBuf  );
	   //
	   //  return;
	   }
   else  {
	     //
		 memcpy(  pObj->inputForEnc.pBuf  +  pObj->inputForEnc.len,  cPcmData,  iPcmDataLen  );
		 pObj->inputForEnc.len  +=  iPcmDataLen;
   }

   //
   int FrameSize  =  pObj->inputForEnc.len;
   DataIn.SetBufferPointer((  Ipp8u  *  )pObj->inputForEnc.pBuf,FrameSize);
   DataIn.SetDataSize(FrameSize);


   int  index  =  0;
   if  (  !pObj->common.outs[index].pBuf  )  {
	   pObj->common.outs[index].pBuf  =  (  BYTE  *  )malloc(  pQdcObjInfo->var.cbOutputBuffer  );
	   if (  !pObj->common.outs[index].pBuf  )  {
		   tmp_showInfo(  _T(  "myAudioEnc failed, pObj->common.outs[].pBuf malloc failed"  )  );
		   goto  errLabel;
	   }
   }

   Ipp8u  *  cAudioData  =  pObj->common.outs[index].pBuf;
   int  iAudioDataSize  =  pQdcObjInfo->var.cbOutputBuffer;
   int  iAudioDataLen  =  0;

   //  DataOut.SetBufferPointer(cVideoData,MAXVIDEOSIZE);
   DataOut.SetBufferPointer(  cAudioData,  iAudioDataSize  );


   //  DataIn.
   /*
	do {
		// append data to inMediaBuffer up to needSize bytes
		AudioDataSize = Append(DataIn, needSize);
		do {
			status = MP3Encoder.GetFrame(&DataIn, &DataOut);	    
			if (status == UMC::UMC_OK) {
				// write output data
				Write(DataOut.GetDataPointer(), DataOut.GetDataSize());
			}
		} while (status == UMC::UMC_OK);
	} while ((AudioDataSize) && (status != UMC::UMC_ERR_INVALID_STREAM));
*/


   do {
	   int  kk  =  DataIn.GetDataSize(  );

	   try  {
			status = MP3Encoder.GetFrame(&DataIn, &DataOut);	    
			}
	   catch  (  ...  )  {
			   status  =  -1;
	  		   _sntprintf(  tBuf,  sizeof(  tBuf  ) /  sizeof(  tBuf[0]  ),  _T(  "myAudioEncoder.GetFrame failed, __except"  )  );
			   tmp_showInfo(  tBuf  );
			   goto  errLabel;
	   }
	   
	   kk  =  DataIn.GetDataSize(  );

	   if (status == UMC::UMC_OK) {
		   // write output data
		   //  Write(DataOut.GetDataPointer(), DataOut.GetDataSize());

		   int  iLen  =  DataOut.GetDataSize(  );
		   iAudioDataLen  +=  iLen;
		   if  (  !iLen  ||  iAudioDataLen  >  iAudioDataSize  )  {
			   tmp_showInfo(  _T(  "myAudioEnc failed, dataLen err"  )  );
			   goto  errLabel;
		   }
		   if  (  !DataIn.GetDataSize(  )  )  {
			   break;
		   }

		   DataOut.SetBufferPointer(  cAudioData  +  iAudioDataLen,  iAudioDataSize  -  iAudioDataLen  );
	   }
   } while (status == UMC::UMC_OK);

   if  (  iAudioDataLen  )  {
		   pObj->common.outs[index].len  =  iAudioDataLen;
		   int  timeInMs_left  =  0;
		   if  (  pObj->inputForEnc.ah_decompress.wfx.nAvgBytesPerSec  )  timeInMs_left  =  nLeft_last  *  1000  /  pObj->inputForEnc.ah_decompress.wfx.nAvgBytesPerSec;	//  2012/01/25
		   //  pObj->common.outs[index].rtStart  =  (  iSampleTimeInMs  -  timeInMs_left  )  *  1000  *  10;   
		   pObj->common.outs[index].rtStart  =  (  iSampleTimeInMs  -  timeInMs_left  );
		   pObj->common.outs[index].rtStart  *=  1000  *  10;   
   }

   pObj->inputForEnc.len  =  DataIn.GetDataSize(  );
   if  (  pObj->inputForEnc.len  )  {
	   memcpy(  pObj->inputForEnc.pBuf,  DataIn.GetDataPointer(  ),  pObj->inputForEnc.len  );
   }

errLabel:
//  #ifdef  _DEBUG
#if  0
   _sntprintf(  tBuf,  sizeof(  tBuf  )/  sizeof(  tBuf[0]  ),  _T(  "index %d, audioDataLen %d, nLeft %d, pcmLen %d\n"  ),  index,  iAudioDataLen,  pObj->inputForEnc.len,  iPcmDataLen  );
   tmp_showInfo(  tBuf  );
#endif

    return;  
}



//  2012/01/20
extern  "C"  int  __declspec(  dllexport  )qdcInitCompressAudio(  void  *  pAudioCompressorCfg_reserved,  QY_AUDIO_HEADER  *  pAh_decompress,  QY_AUDIO_HEADER  *  pAh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int						iErr	=	-1;
	QDC_OBJ_INFO			qdcObjInfo;
	QDC_OBJ_mp3Enc		*	pObj	=	NULL;	
	UMC::MP3EncoderParams MP3EncoderParams;
	UMC::Status status;

	//  UMC::AudioCodecParams audio_codec_params;   
	UMC::AudioEncoderParams	audio_codec_params;


	if  (  !pAudioCompressorCfg_reserved  )  return  -1;
	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;

	//
	AUDIO_COMPRESSOR_cfgCommon  *  pAudioCompressorCfg  =  (  AUDIO_COMPRESSOR_cfgCommon  *  )pAudioCompressorCfg_reserved;

	//  2014/05/20
	int  iBitrate  =  0;
	int  k1  =  1000;	//  1024
	iBitrate  =  pAudioCompressorCfg->iAvgBitrateInKbps  *  k1;
	if  (  iBitrate  <  16  *  k1  ||  iBitrate  >  320  *  k1  )  {
		iBitrate  =  128  *  k1;
	}
	if  (  pAh_decompress->wfx.nSamplesPerSec  !=  16000  )  {
		iBitrate  =  128  *  k1;
		tmp_showInfo(  _T(  "Note: force bitrate to 128000 if nSamplesPerSec != 16000"  )  );
	}
	TCHAR  tBuf[256];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qdcInitCompressAudio: cfg.bitreate %d, real. %d"  ),  pAudioCompressorCfg->iAvgBitrateInKbps  *  k1,  iBitrate  );
	tmp_showInfo(  tBuf  );

	//
	memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_mp3Enc  *  )malloc(  sizeof(  QDC_OBJ_mp3Enc  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	qdcObjInfo.var.pObj  =  pObj;

	// initialize input and output buffer
	qdcObjInfo.var.cbInputBuffer  =  pAh_decompress->wfx.nAvgBytesPerSec  *  2;
	qdcObjInfo.var.cbOutputBuffer  =  qdcObjInfo.var.cbInputBuffer;

	// set encoder params (See Initialization examples section)
#if  0
	MP3EncoderParams.m_info_in.sample_frequency = 44100;
	MP3EncoderParams.m_info_in.channels = 2;
#endif
	MP3EncoderParams.m_info.audioInfo.m_iSampleFrequency = pAh_decompress->wfx.nSamplesPerSec;		//.sample_frequency = pAh_decompress->wfx.nSamplesPerSec;
	MP3EncoderParams.m_info.audioInfo.m_iChannels  = pAh_decompress->wfx.nChannels;					//_in.channels = pAh_decompress->wfx.nChannels;
	MP3EncoderParams.m_info.audioInfo.m_iBitPerSample =  pAh_decompress->wfx.wBitsPerSample;		//_in.bitPerSample  =  pAh_decompress->wfx.wBitsPerSample;
	//
	MP3EncoderParams.m_info.audioInfo.m_iChannelMask  =  0;											//_in.channel_mask = 0;
	MP3EncoderParams.m_info.iBitrate = iBitrate;	//  128000;			 							//_out.bitrate = 128000;
	MP3EncoderParams.layer = 3;
	MP3EncoderParams.force_mpeg1 = 0;
	MP3EncoderParams.stereo_mode = UMC_MPA_LR_STEREO;
	MP3EncoderParams.mode = 0;
	MP3EncoderParams.mc_matrix_procedure = 0;
	MP3EncoderParams.mc_lfe_filter_off = 0;

	//
	try  {		//  2014/10/16
		 //
		UMC::MP3Encoder  *  pMP3Encoder  =  new  UMC::MP3Encoder;
		if  (  !pMP3Encoder  )  goto  errLabel;

		pObj->pEncoder  =  pMP3Encoder;


		//Initialization of MPEG Audio encoder
		if  (  (  status  =  pMP3Encoder->Init(&MP3EncoderParams)  )  !=  UMC::UMC_OK  )  goto  errLabel;	//  qdcObjInfo.
		//
		pMP3Encoder->GetInfo(&audio_codec_params);
   
		pObj->needSize  =  audio_codec_params.m_iSuggestedInputSize;
		}
	catch  (  ...  )  {
			tmp_showInfo(  _T(  "qdcInitCompressAudio: new failed"  )  );
			goto  errLabel;

	}

	//
	memcpy(  pAh_compress,  pAh_decompress,  sizeof(  pAh_compress[0]  )  );
	pAh_compress->wfx.wFormatTag  =  WAVE_FORMAT_MPEGLAYER3;

	//
	if  (  pAh_decompress->wfx.nSamplesPerSec  !=  audio_codec_params.m_info.audioInfo.m_iSampleFrequency	//  .m_info_in.sample_frequency  
		||  pAh_decompress->wfx.nChannels  !=  audio_codec_params.m_info.audioInfo.m_iChannels				//  .m_info_in.channels  
		||  pAh_decompress->wfx.wBitsPerSample  !=  audio_codec_params.m_info.audioInfo.m_iBitPerSample		//  .m_info_in.bitPerSample  
		)
	{
		tmp_showInfo(  _T(  "qdcInitCompressAudio: input format not matched"  )  );
		goto  errLabel;
	}


	//	
	if  (  !pObj->common.outs[0].pBuf  )  {
		pObj->common.outs[0].pBuf  =  (  BYTE  *  )malloc(  qdcObjInfo.var.cbOutputBuffer  );
		if  (  !pObj->common.outs[0].pBuf  )  goto  errLabel;
	}

	//
	memcpy(  &pObj->inputForEnc.ah_decompress,  pAh_decompress,  sizeof(  pObj->inputForEnc.ah_decompress  )  );  
	pObj->inputForEnc.uiBufSize  =  qdcObjInfo.var.cbInputBuffer;
	pObj->inputForEnc.pBuf  =  (  char  *  )malloc(  pObj->inputForEnc.uiBufSize  );
	if  (  !pObj->inputForEnc.pBuf  )  goto  errLabel;

	//
	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		qdcExitCompressAudio(  pQdcObjInfo  );
	}
	if  (  !iErr  )  {
		memcpy(  pQdcObjInfo,  &qdcObjInfo,  sizeof(  pQdcObjInfo[0]  )  );
	}
	return  iErr;
}

extern  "C"  int  __declspec(  dllexport  )qdcExitCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_mp3Enc	*	pObj  =  (  QDC_OBJ_mp3Enc  *  )pQdcObjInfo->var.pObj;

	if  (  pObj  )  {
		//
		if  (  pObj->pEncoder  )  {
			UMC::MP3Encoder  *  pEncoder  =  (  UMC::MP3Encoder  *  )pObj->pEncoder;
			delete  pEncoder;
			pObj->pEncoder  =  NULL;
		}
		//
		if  (  pObj->inputForEnc.pBuf  )  {
			free(  pObj->inputForEnc.pBuf  );
		}
		//
		qdcAudioFreeOutputs(  pQdcObjInfo  );
		//
		free(  pObj  );	
	}
	pQdcObjInfo->var.pObj  =  NULL;

	return  0;
}

extern  "C"  int  __declspec(  dllexport  )qdcCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_decompress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs  )
{
	QDC_OBJ_mp3Enc	*	pObj	=	(  QDC_OBJ_mp3Enc  *  )pQdcObjInfo->var.pObj;

	if  (  uiInputSize  >  pQdcObjInfo->var.cbInputBuffer  )  return  -1;

#if  0
	int  index  =  0;
	memcpy(  pObj->common.outs[index].pBuf,  pInput,  uiInputSize  );
	pObj->common.outs[index].len  =  uiInputSize;
	pObj->common.outs[index].rtStart  =  iSampleTimeInMs  *  1000  *  10;
#endif

	myAudioEncodeStream(  pQdcObjInfo,  pInput,  uiInputSize,  iSampleTimeInMs  );

	
	return  0;
}


//  void myAudioDecodeStream( UMC::MP3Decoder  *  pMP3Decoder,  BOOL  *  pbInited,  Ipp8u *cVideoData,int VideoDataSize, Ipp8u *cYUVData, int imgWidth, int  imgHeight, int & frameNumber ) 
void myAudioDecodeStream( QDC_OBJ_INFO  *  pQdcObjInfo,  UMC::MP3Decoder  *  pMP3Decoder,  BOOL  *  pbInited,  Ipp8u  *  cAudioData,  int  iAudioDataSize,  int iSampleTimeInMs )
{ 
	int			iErr  =  -1;
	UMC::Status status; 
	UMC::MediaData DataIn; UMC::MediaData DataOut;
	QDC_OBJ_mp3Dec  *  pObj  =  (  QDC_OBJ_mp3Dec  *  )pQdcObjInfo->var.pObj;
	UMC::MP3Decoder *  pMp3Decoder  =  (  UMC::MP3Decoder  *  )pObj->pDecoder;
	UMC::MP3Decoder &  MP3Decoder  =  *pMp3Decoder; 

	TCHAR	tBuf[128]   =  _T(  ""  );

	Ipp32s needSize = pObj->needSize;	//  audio_codec_params.m_SuggestedInputSize;


	if  (  !iAudioDataSize
		||  iAudioDataSize  +  pObj->inputForDec.len  >  pObj->inputForDec.uiBufSize  )
	{
		tmp_showInfo(  _T(  "myAudioDec failed, dataLen too big"  ) );
		return;
	}

	//  2012/01/25
	int  nLeft_last  =  pObj->inputForDec.len;

	//
	memcpy(  pObj->inputForDec.pBuf  +  pObj->inputForDec.len,  cAudioData,  iAudioDataSize  );
	pObj->inputForDec.len  +=  iAudioDataSize;


   int FrameSize  =  pObj->inputForDec.len;
   DataIn.SetBufferPointer((  Ipp8u  *  )pObj->inputForDec.pBuf,FrameSize);
   DataIn.SetDataSize(FrameSize);

	
#if  0
	if  (  !*pbInited  )  {
		UMC::MP3DecoderParams Params; 

		Params.m_pData = &DataIn; 
		Params.numThreads=1; 
		if  (  (  status = MP3Decoder.Init(&Params)  )  !=  UMC::UMC_OK  ) return; 

		MP3Decoder.GetInfo(&Params); 
	}
#endif

	Ipp8u *cPcmData  =  NULL;
	int iPcmDataSize  =  0;
	int iPcmDataLen  =  0;
	//  
	int  index  =  0;
	cPcmData  =  pObj->common.outs[index].pBuf;
	iPcmDataSize  =  pQdcObjInfo->var.cbOutputBuffer;
	
	DataOut.SetBufferPointer(cPcmData,iPcmDataSize);

	//  int  maxFrame  =  frameNumber;
	int  size;

	//  do  {
		//  size  =  Append(  inMediaBuf,  needSize  );
		do{ 
			//
			try  {
				status = MP3Decoder.GetFrame(&DataIn, &DataOut); 
				}
			catch  (  ...  )  {
					status  =  -1;
					_sntprintf(  tBuf,  sizeof(  tBuf  ) /  sizeof(  tBuf[0]  ),  _T(  "AudioDecoder.GetFrame failed, __except"  )  );
				    tmp_showInfo(  tBuf  );
					goto  errLabel;
			}
			//
			if (status == UMC::UMC_OK){ 
				//  cYUVData += (imgWidth*imgHeight*3/2);
				//  注意：这里因为输入只给了一个frame的buf，所以不能移动指针.
			
				//   DataOut.GetDataPointer(  );
				int  iLen  =  DataOut.GetDataSize(  );
				iPcmDataLen  +=  iLen;
				if  (  !iLen  ||  iPcmDataLen  >  iPcmDataSize  )  {
					tmp_showInfo(  _T(  "myAudioDecodeStream failed, pcmDataLen err"  )  );
					goto  errLabel;
				}
				if  (  !DataIn.GetDataSize(  )  )  {
					//tmp_showInfo(  _T(  "myAudioDecode ok, break"  )  );
					break;
				}
				
				DataOut.SetBufferPointer(cPcmData  +  iPcmDataLen,iPcmDataSize  -  iPcmDataLen); 

				//  frameNumber++; 
			} 

		}while (status  ==  UMC::UMC_OK); 
	//  }  while  (  (  size  )  &&  (  status  !=  UMC::UMC_ERR_INVALID_STREAM  )  );


		if  (  status  ==  UMC::UMC_ERR_NOT_ENOUGH_DATA  )  pObj->inputForDec.len  =  DataIn.GetDataSize(  );
		else  pObj->inputForDec.len  =  0;
		if  (  pObj->inputForDec.len  )  {
			memcpy(  pObj->inputForDec.pBuf,  DataIn.GetDataPointer(  ),  pObj->inputForDec.len  );
		}

		//
		if  (  iPcmDataLen  )  {
			pObj->common.outs[index].len  =  iPcmDataLen;
			//			
			int  timeInMs_left  =  0;		   
			int  nReal  =  nLeft_last  +  iAudioDataSize  -  pObj->inputForDec.len;
			if  (  nReal  >  0
				&&  pObj->inputForDec.ah_decompress.wfx.nAvgBytesPerSec  )  
			{		
				int  nPcmLeft_last  =  nLeft_last  *  iPcmDataLen  /  nReal;
				timeInMs_left  =  nPcmLeft_last  *  1000  /  pObj->inputForDec.ah_decompress.wfx.nAvgBytesPerSec;	//  2012/01/25
				
			    #if  0
					_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "myAudioDecode nLeft %d, audioDataLen %d, time_left %d"  ),  nLeft_last,  iAudioDataSize,  timeInMs_left  );
					tmp_showInfo(  tBuf  );
				#endif
			}
			//
			//  pObj->common.outs[index].rtStart  =  (  iSampleTimeInMs  -  timeInMs_left  )  *  1000  *  10;
			pObj->common.outs[index].rtStart  =  (  iSampleTimeInMs  -  timeInMs_left  );
			pObj->common.outs[index].rtStart  *=  1000  *  10;
		}

	
		iErr  =  0;

errLabel:

		if  (  !iPcmDataLen
			&&  status  !=  UMC::UMC_ERR_NOT_ENOUGH_DATA  )  
		{
			_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "myAudioDecode failed, status %d, dataSize %d"  ),  status,  iAudioDataSize  );
			tmp_showInfo(  tBuf  );
		}
#if  0
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "myAudioDec, pcmLen %d, nLeft %d"  ),  iPcmDataLen,  pObj->inputForDec.len  );
		tmp_showInfo(  tBuf  );
#endif

	return; 
} 


extern  "C"  int  __declspec(  dllexport  )qdcInitDecompressAudio(  void  *  pAudioCompressorCfg,  QY_AUDIO_HEADER  *  pAh_compress,  QY_AUDIO_HEADER  *  pAh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{	
	int						iErr	=	-1;
	QDC_OBJ_INFO			qdcObjInfo;
	QDC_OBJ_mp3Dec		*	pObj	=	NULL;
	UMC::Status				status;

	//  UMC::AudioCodecParams audio_codec_params;  
	UMC::AudioDecoderParams	audio_codec_params;
	UMC::BaseCodecParams	params;


	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;

	memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_mp3Dec  *  )malloc(  sizeof(  QDC_OBJ_mp3Dec  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	qdcObjInfo.var.pObj  =  pObj;

	//  qdcObjInfo.
	qdcObjInfo.var.cbOutputBuffer  =  pAh_decompress->wfx.nAvgBytesPerSec  *  2;
	qdcObjInfo.var.cbInputBuffer  =  qdcObjInfo.var.cbOutputBuffer;

	try  {
		// MP3Decoder Initialization,  2012/01/21
		UMC::MP3Decoder  *  pMP3Decoder  =  new  UMC::MP3Decoder;
		if  (  !pMP3Decoder  )  goto  errLabel;

		pObj->pDecoder  =  pMP3Decoder;



		//Initialization of MPEG Audio decoder,  2012/01/21
		if  (  (  status  =  pMP3Decoder->Init(  &params  )  )  !=  UMC::UMC_OK   )  {
			tmp_showInfo(  _T(  "qdcInitDecompressAudio failed, decoder init failed"  )  );
			goto  errLabel;
		}
		//
		pMP3Decoder->GetInfo(&audio_codec_params);
   
		pObj->needSize  =  audio_codec_params.m_iSuggestedInputSize;
	
		}
	catch  (  ...  )  {
			tmp_showInfo(  _T(  "qdcInitDecA: new failed"  )  );
			goto  errLabel;
	}
	
	
	//
	//  memcpy(  pAh_compress,  pAh_decompress,  sizeof(  pAh_compress[0]  )  );

	//
#if  0
	if  (  pAh_compress->wfx.nSamplesPerSec  !=  audio_codec_params.m_info_in.sample_frequency  
		||  pAh_compress->wfx.nChannels  !=  audio_codec_params.m_info_in.channels  
		||  pAh_compress->wfx.wBitsPerSample  !=  audio_codec_params.m_info_in.bitPerSample  )
	{
		tmp_showInfo(  _T(  "qdcInitDecompressAudio: input format not matched"  )  );
		goto  errLabel;
	}
#endif

	//	
	if  (  !pObj->common.outs[0].pBuf  )  {
		pObj->common.outs[0].pBuf  =  (  BYTE  *  )malloc(  qdcObjInfo.var.cbOutputBuffer  );
		if  (  !pObj->common.outs[0].pBuf  )  goto  errLabel;
	}

	//
	memcpy(  &pObj->inputForDec.ah_decompress,  pAh_decompress,  sizeof(  pObj->inputForDec.ah_decompress  )  );
	pObj->inputForDec.uiBufSize  =  qdcObjInfo.var.cbInputBuffer;
	pObj->inputForDec.pBuf  =  (  char  *  )malloc(  pObj->inputForDec.uiBufSize  );
	if  (  !pObj->inputForDec.pBuf  )  goto  errLabel;

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		qdcExitDecompressAudio(  pQdcObjInfo  );
	}
	if  (  !iErr  )  {
		memcpy(  pQdcObjInfo,  &qdcObjInfo,  sizeof(  pQdcObjInfo[0]  )  );
	}
	return  iErr;
}

extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_mp3Dec	*	pObj  =  (  QDC_OBJ_mp3Dec  *  )pQdcObjInfo->var.pObj;

	if  (  pObj  )  {
		//
		if  (  pObj->pDecoder  )  {
			UMC::MP3Decoder  *  pDecoder  =  (  UMC::MP3Decoder  *  )pObj->pDecoder;
			delete  pDecoder;
			pObj->pDecoder  =  NULL;
		}
		//
		if  (  pObj->inputForDec.pBuf  )  {
			free(  pObj->inputForDec.pBuf  );
		}
		//
		qdcAudioFreeOutputs(  pQdcObjInfo  );
		//
		free(  pObj  );	
	}
	pQdcObjInfo->var.pObj  =  NULL;

	return  0;
}

extern  "C"  int  __declspec(  dllexport  )qdcDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_compress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  )
{	
	QDC_OBJ_mp3Dec	*	pObj	=	(  QDC_OBJ_mp3Dec  *  )pQdcObjInfo->var.pObj;

	if  (  uiInputSize  >  pQdcObjInfo->var.cbInputBuffer  )  return  -1;

#if  0
	int  index  =  0;
	memcpy(  pObj->common.outs[index].pBuf,  pInput,  uiInputSize  );
	pObj->common.outs[index].len  =  uiInputSize;
	pObj->common.outs[index].rtStart  =  iSampleTimeInMs  *  1000  *  10;
#endif

	
	myAudioDecodeStream(  pQdcObjInfo,  (  UMC::MP3Decoder  *  )pObj->pDecoder,  NULL,  pInput,  uiInputSize,  iSampleTimeInMs  );

	return  0;
}

