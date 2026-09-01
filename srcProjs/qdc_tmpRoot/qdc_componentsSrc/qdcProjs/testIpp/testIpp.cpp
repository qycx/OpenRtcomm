// testIpp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ipp.h"
#include "testIpp.h"
#include <MMReg.h>
#include <MMSystem.h>
#include "umc_defs.h" 
#include "umc_video_decoder.h" 
#include "umc_video_data.h" 
//  #include "umc_h264_dec.h" 
#include "umc_mp3_encoder.h"
//  #include "umc_mp3_encoder_params.h"
//  #include "umc_mp3dec_fp.h"
//  #include "umc_mp3_decoder_params.h"

#include "umc_structures.h" 

#define MAX_LOADSTRING 100
#define	MAXFRAME	30

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

typedef  struct  __qdcOutput_t										{
				 BYTE									*			pBuf;
				 unsigned  int										len;
				 //
				 __int64											rtStart;		//  REFERENCE_TIME			rtStart;
				 __int64											rtTimeLen;		//  REFERENCE_TIME			rtTimeLen;

}		 QDC_OUTPUT;


typedef  struct  __qdcObj_mp3Common_t			{

				 //  QDC_OUTPUT						outs[1];
				 QDC_OUTPUT						outs[10];	// 2011/09/04

}		 QDC_OBJ_mp3Common;
//
typedef  struct  __qdcObjInfo_t										{
				 void									*			pObj;

				 DWORD												cbInputBuffer;
				 DWORD												cbOutputBuffer;

				 int												iDiffInMs_tStartAudio;						//  2009/05/26
				 void										*		pDebugStep;									//  2010/04/28

}		 QDC_OBJ_INFO;

#define		CONST_bufSize_bExtraData								512
typedef  struct  __qyAudioHeader_t									{						//  2009/05/16
				 WAVEFORMATEX										wfx;
				 char												bExtraData[CONST_bufSize_bExtraData];
}		 QY_AUDIO_HEADER;

typedef  struct  __qdcObj_mp3Enc_t				{
				 QDC_OBJ_mp3Common				common;
				 
				 //
				 struct							{
					 char					*	pBuf;
					 unsigned int				uiBufSize;
					 int						len;
				 }								inputForEnc;

				 int							needSize;

				    
				 //  UMC::Mp3VideoEncoder Mp3Encoder;; 
				 void						*	pEncoder;				 
}		 QDC_OBJ_mp3Enc;

typedef  struct  __qdcObj_mp3Dec_t				{
				 QDC_OBJ_mp3Common				common;

				 struct							{
					 char					*	pBuf;
					 unsigned int				uiBufSize;
					 int						len;
				 }								inputForDec;
				 
				    
				 //  UMC::MP3Decoder MP3Decoder;; 
				 void						*	pDecoder;
				 BOOL							bInited;
				
				 int							needSize;
				 
}		 QDC_OBJ_mp3Dec;

#if  0
extern  "C"  int  __declspec(  dllexport  )qdcInitDecompressAudio(  void  *  pAudioCompressorCfg,  QY_AUDIO_HEADER  *  pAh_compress,  QY_AUDIO_HEADER  *  pAh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_compress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  );

#else
extern  "C"  int  __declspec(  dllexport  )qdcDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_compress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  );
extern  "C"  int  __declspec(  dllexport  )qdcInitDecompressAudio(  void  *  pAudioCompressorCfg,  QY_AUDIO_HEADER  *  pAh_compress,  QY_AUDIO_HEADER  *  pAh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  );
#endif
#if  0
void DecodeStream( Ipp8u *cVideoData,int VideoDataSize, Ipp8u *cYUVData, int& imgWidth, int & imgHeight, int & frameNumber ) 
{
	UMC::Status status; UMC::MediaData DataIn; UMC::VideoData DataOut; UMC::VideoDecoderParams Params; UMC::H264VideoDecoder H264Decoder; 
	int frameSize=0; 
	DataIn.SetBufferPointer(cVideoData,VideoDataSize); 
	DataIn.SetDataSize(VideoDataSize); 
	Params.m_pData = &DataIn; 
	Params.lFlags=0; 
	Params.numThreads=1; 
	if(status = H264Decoder.Init(&Params)!=UMC::UMC_OK) return; 
	H264Decoder.GetInfo(&Params); 
	imgWidth=Params.info.clip_info.width; 
	imgHeight=Params.info.clip_info.height; 
	frameSize = imgWidth*imgHeight*3/2; 
	DataOut.Init(imgWidth,imgHeight,UMC::YV12,8); 
	DataOut.SetBufferPointer(cYUVData,frameSize); 
	int exit_flag=0; frameNumber=0; 
	do{ 
		status = H264Decoder.GetFrame(&DataIn, &DataOut); 
		if (status == UMC::UMC_OK){ cYUVData += (imgWidth*imgHeight*3/2); DataOut.SetBufferPointer(cYUVData,frameSize); frameNumber++; } 
		if((status !=UMC::UMC_OK)||(frameNumber >=MAXFRAME)) exit_flag = 1; 
	}while (exit_flag!=1); 
	do{ 
		status = H264Decoder.GetFrame(NULL, &DataOut); 
		if (status == UMC::UMC_OK) { cYUVData += frameSize; DataOut.SetBufferPointer(cYUVData,frameSize); frameNumber++; } 
	}while(status == UMC::UMC_OK); return; 
}
#endif


 void  qdcAudioFreeOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_mp3Common  *  pObj	=	(  QDC_OBJ_mp3Common  *  )pQdcObjInfo->pObj;
	int			i;

	for  (  i  =  0;  i  <  sizeof(  pObj->outs  )  /  sizeof(  pObj->outs[0]  );  i  ++  )  {
		 if  (  pObj->outs[i].pBuf  )  free(  pObj->outs[i].pBuf  );
	}
	memset(  &pObj->outs,  0,  sizeof(  pObj->outs  )  );
}


void myAudioEncodeStream(QDC_OBJ_INFO  *  pQdcObjInfo, 
					Ipp8u *cPcmData, int iPcmDataLen,  int  iSampleTimeInMs  ) 
{
	QDC_OBJ_mp3Enc  *  pObj  =  (  QDC_OBJ_mp3Enc  *  )pQdcObjInfo->pObj;
	UMC::MP3Encoder *  pMp3Encoder  =  (  UMC::MP3Encoder  *  )pObj->pEncoder;
	UMC::MP3Encoder &  MP3Encoder  =  *pMp3Encoder; 
	
	TCHAR  tBuf[256]  = _T(  ""  );

   UMC::Status status;
   UMC::MediaData	DataIn;
   UMC::MediaData	DataOut;

   Ipp32s needSize = pObj->needSize;	//  audio_codec_params.m_SuggestedInputSize;

   //
   if  (  !iPcmDataLen
	   ||  iPcmDataLen  +  pObj->inputForEnc.len  >  pObj->inputForEnc.uiBufSize  )  
   {
	   //  tmp_showInfo(  _T(  "myAudioEnc failed, dataLen too big"  )  );
	   MessageBox(  NULL,  _T(  "myAudioEnc failed, dataLen too big"  ),  _T(  "qycx"  ),  MB_OK  );
	   return;
   }

   memcpy(  pObj->inputForEnc.pBuf  +  pObj->inputForEnc.len,  cPcmData,  iPcmDataLen  );
   pObj->inputForEnc.len  +=  iPcmDataLen;

   //
   int FrameSize  =  pObj->inputForEnc.len;
   DataIn.SetBufferPointer((  Ipp8u  *  )pObj->inputForEnc.pBuf,FrameSize);
   DataIn.SetDataSize(FrameSize);


   int  index  =  0;
   if  (  !pObj->common.outs[index].pBuf  )  {
	   pObj->common.outs[index].pBuf  =  (  BYTE  *  )malloc(  pQdcObjInfo->cbOutputBuffer  );
	   if (  !pObj->common.outs[index].pBuf  )  goto  errLabel;
   }

   Ipp8u  *  cAudioData  =  pObj->common.outs[index].pBuf;
   int  iAudioDataSize  =  pQdcObjInfo->cbOutputBuffer;
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

	   status = MP3Encoder.GetFrame(&DataIn, &DataOut);	    
	   
	   kk  =  DataIn.GetDataSize(  );

	   if (status == UMC::UMC_OK) {
		   // write output data
		   //  Write(DataOut.GetDataPointer(), DataOut.GetDataSize());

		   int  iLen  =  DataOut.GetDataSize(  );
		   iAudioDataLen  +=  iLen;
		   if  (  !iLen  ||  iAudioDataLen  >  iAudioDataSize  )  {
			   //  tmp_showInfo(  _T(  "myAudioEnc failed, dataLen err"  )  );
			   MessageBox(  NULL,  _T(  "myAudioEnc failed, dataLen err"  ),  _T(  "qycx"  ),  MB_OK  );
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
		   pObj->common.outs[index].rtStart  =  iSampleTimeInMs  *  1000  *  10;   
   }

   pObj->inputForEnc.len  =  DataIn.GetDataSize(  );
   if  (  pObj->inputForEnc.len  )  {
	   memcpy(  pObj->inputForEnc.pBuf,  DataIn.GetDataPointer(  ),  pObj->inputForEnc.len  );
   }

errLabel:
//  #ifdef  _DEBUG
#if  0
   _sntprintf(  tBuf,  sizeof(  tBuf  )/  sizeof(  tBuf[0]  ),  _T(  "index %d, audioDataSize %d, nLeft %d\n"  ),  index,  iAudioDataLen,  pObj->inputForEnc.len  );
   tmp_showInfo(  tBuf  );
#endif

    return;  
}
extern  "C"  int  __declspec(  dllexport  )qdcExitCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_mp3Enc	*	pObj  =  (  QDC_OBJ_mp3Enc  *  )pQdcObjInfo->pObj;

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
	pQdcObjInfo->pObj  =  NULL;

	return  0;
}

extern  "C"  int  __declspec(  dllexport  )qdcCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_decompress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs  )
{
	QDC_OBJ_mp3Enc	*	pObj	=	(  QDC_OBJ_mp3Enc  *  )pQdcObjInfo->pObj;

	if  (  uiInputSize  >  pQdcObjInfo->cbInputBuffer  )  return  -1;

#if  0
	int  index  =  0;
	memcpy(  pObj->common.outs[index].pBuf,  pInput,  uiInputSize  );
	pObj->common.outs[index].len  =  uiInputSize;
	pObj->common.outs[index].rtStart  =  iSampleTimeInMs  *  1000  *  10;
#endif

	myAudioEncodeStream(  pQdcObjInfo,  pInput,  uiInputSize,  iSampleTimeInMs  );

	
	return  0;
}
extern  "C"  int  __declspec(  dllexport  )qdcInitCompressAudio(  void  *  pAudioCompressorCfg_reserved,  QY_AUDIO_HEADER  *  pAh_decompress,  QY_AUDIO_HEADER  *  pAh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int						iErr	=	-1;
	QDC_OBJ_INFO			qdcObjInfo;
	QDC_OBJ_mp3Enc		*	pObj	=	NULL;	
	UMC::MP3EncoderParams MP3EncoderParams;
	UMC::Status status;

	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->pObj  )  return  -1;

	memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_mp3Enc  *  )malloc(  sizeof(  QDC_OBJ_mp3Enc  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	qdcObjInfo.pObj  =  pObj;

	// initialize input and output buffer
	qdcObjInfo.cbInputBuffer  =  pAh_decompress->wfx.nAvgBytesPerSec  *  2;
	qdcObjInfo.cbOutputBuffer  =  qdcObjInfo.cbInputBuffer;

	// set encoder params (See Initialization examples section)
	MP3EncoderParams.m_info_in.sample_frequency = 44100;
	MP3EncoderParams.m_info_in.channels = 2;
	MP3EncoderParams.m_info_in.channel_mask = 0;
	MP3EncoderParams.m_info_out.bitrate = 128000;
	MP3EncoderParams.layer = 3;
	MP3EncoderParams.force_mpeg1 = 0;
	MP3EncoderParams.stereo_mode = UMC_MPA_LR_STEREO;
	MP3EncoderParams.mode = 0;
	MP3EncoderParams.mc_matrix_procedure = 0;
	MP3EncoderParams.mc_lfe_filter_off = 0;

	//
	UMC::MP3Encoder  *  pMP3Encoder  =  new  UMC::MP3Encoder;
	if  (  !pMP3Encoder  )  goto  errLabel;

	pObj->pEncoder  =  pMP3Encoder;


	//Initialization of MPEG Audio encoder
	if  (  (  status  =  pMP3Encoder->Init(&MP3EncoderParams)  )  !=  UMC::UMC_OK  )  goto  errLabel;	//  qdcObjInfo.
	//
	UMC::AudioCodecParams audio_codec_params;   
	pMP3Encoder->GetInfo(&audio_codec_params);
   
	pObj->needSize  =  audio_codec_params.m_SuggestedInputSize;

	//
	memcpy(  pAh_compress,  pAh_decompress,  sizeof(  pAh_compress[0]  )  );
	pAh_compress->wfx.wFormatTag  =  WAVE_FORMAT_MPEGLAYER3;

	//
	if  (  pAh_decompress->wfx.nSamplesPerSec  !=  audio_codec_params.m_info_in.sample_frequency  
		||  pAh_decompress->wfx.nChannels  !=  audio_codec_params.m_info_in.channels  
		||  pAh_decompress->wfx.wBitsPerSample  !=  audio_codec_params.m_info_in.bitPerSample  )
	{
		//  tmp_showInfo(  _T(  "qdcInitCompressAudio: input format not matched"  )  );
		MessageBox(  NULL,  _T(  "qdcInitCompressAudio: input format not matched"  ),  _T(  "qycx"  ),  MB_OK  );
		goto  errLabel;
	}


	//	
	if  (  !pObj->common.outs[0].pBuf  )  {
		pObj->common.outs[0].pBuf  =  (  BYTE  *  )malloc(  qdcObjInfo.cbOutputBuffer  );
		if  (  !pObj->common.outs[0].pBuf  )  goto  errLabel;
	}

	//
	pObj->inputForEnc.uiBufSize  =  qdcObjInfo.cbInputBuffer;
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


void myAudioDecodeStream( QDC_OBJ_INFO  *  pQdcObjInfo,  UMC::MP3Decoder  *  pMP3Decoder,  BOOL  *  pbInited,  Ipp8u  *  cAudioData,  int  iAudioDataSize,  int iSampleTimeInMs )
{ 
	int			iErr  =  -1;
	UMC::Status status; 
	UMC::MediaData DataIn; UMC::MediaData DataOut;
	QDC_OBJ_mp3Dec  *  pObj  =  (  QDC_OBJ_mp3Dec  *  )pQdcObjInfo->pObj;
	UMC::MP3Decoder *  pMp3Decoder  =  (  UMC::MP3Decoder  *  )pObj->pDecoder;
	UMC::MP3Decoder &  MP3Decoder  =  *pMp3Decoder; 

	Ipp32s needSize = pObj->needSize;	//  audio_codec_params.m_SuggestedInputSize;

	if  (  !iAudioDataSize
		||  iAudioDataSize  +  pObj->inputForDec.len  >  pObj->inputForDec.uiBufSize  )
	{
		//  tmp_showInfo(  _T(  "myAudioDec failed, dataLen too big"  ) );
		MessageBox(  NULL,  _T(  "myAudioDec failed, dataLen too big"  ),  _T(  "qycx"  ),  MB_OK );
		return;
	}
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
	iPcmDataSize  =  pQdcObjInfo->cbOutputBuffer;
	
	DataOut.SetBufferPointer(cPcmData,iPcmDataSize);

	//  int  maxFrame  =  frameNumber;
	int  size;

	//  do  {
		//  size  =  Append(  inMediaBuf,  needSize  );
		do{ 
			status = MP3Decoder.GetFrame(&DataIn, &DataOut); 
			if (status == UMC::UMC_OK){ 
				//  cYUVData += (imgWidth*imgHeight*3/2);
				//  注意：这里因为输入只给了一个frame的buf，所以不能移动指针.
			
				//   DataOut.GetDataPointer(  );
				int  iLen  =  DataOut.GetDataSize(  );
				iPcmDataLen  +=  iLen;
				if  (  !iLen  ||  iPcmDataLen  >  iPcmDataSize  )  {
					//  tmp_showInfo(  _T(  "myAudioDecodeStream failed, pcmDataLen err"  )  );
					MessageBox(  NULL,  _T(  "myAudioDecodeStream failed, pcmDataLen err"  ),  _T(  "qycx"  ),  MB_OK  );
					goto  errLabel;
				}
				if  (  !DataIn.GetDataSize(  )  )  {
					//  tmp_showInfo(  _T(  "myAudioDecode ok, break"  )  );

					MessageBox(  NULL,  _T(  "myAudioDecode ok, break"  ),  _T(  "qycx"  ),  MB_OK  );

					break;
				}
				
				DataOut.SetBufferPointer(cPcmData  +  iPcmDataLen,iPcmDataSize  -  iPcmDataLen); 

				//  frameNumber++; 
			} 

		}while (status  ==  UMC::UMC_OK); 
	//  }  while  (  (  size  )  &&  (  status  !=  UMC::UMC_ERR_INVALID_STREAM  )  );

		if  (  iPcmDataLen  )  {
			pObj->common.outs[index].len  =  iPcmDataLen;
			pObj->common.outs[index].rtStart  =  iSampleTimeInMs  *  1000  *  10;
		}

		if  (  status  ==  UMC::UMC_ERR_NOT_ENOUGH_DATA  )  pObj->inputForDec.len  =  DataIn.GetDataSize(  );
		else  pObj->inputForDec.len  =  0;
		if  (  pObj->inputForDec.len  )  {
			memcpy(  pObj->inputForDec.pBuf,  DataIn.GetDataPointer(  ),  pObj->inputForDec.len  );
		}

		iErr  =  0;

errLabel:

			TCHAR	tBuf[128]   =  _T(  ""  );
		if  (  !iPcmDataLen  )  {
			_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "myAudioDecode failed, status %d, dataSize %d"  ),  status,  iAudioDataSize  );
			MessageBox(  NULL,  tBuf,  _T(  "qycx"  ),  MB_OK  );
			//  tmp_showInfo(  tBuf  );
		}
#if  0
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "myAudioDec, pcmLen %d, nLeft %d"  ),  iPcmDataLen,  pObj->inputForDec.len  );
		tmp_showInfo(  tBuf  );
#endif

	return; 
}

extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_mp3Dec	*	pObj  =  (  QDC_OBJ_mp3Dec  *  )pQdcObjInfo->pObj;

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
	pQdcObjInfo->pObj  =  NULL;

	return  0;
}


extern  "C"  int  __declspec(  dllexport  )qdcInitDecompressAudio(  void  *  pAudioCompressorCfg,  QY_AUDIO_HEADER  *  pAh_compress,  QY_AUDIO_HEADER  *  pAh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{	
	int						iErr	=	-1;
	QDC_OBJ_INFO			qdcObjInfo;
	QDC_OBJ_mp3Dec		*	pObj	=	NULL;
	UMC::Status				status;

	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->pObj  )  return  -1;

	memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_mp3Dec  *  )malloc(  sizeof(  QDC_OBJ_mp3Dec  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	qdcObjInfo.pObj  =  pObj;

	//  qdcObjInfo.
	qdcObjInfo.cbOutputBuffer  =  pAh_decompress->wfx.nAvgBytesPerSec  *  2;
	qdcObjInfo.cbInputBuffer  =  qdcObjInfo.cbOutputBuffer;

	// MP3Decoder Initialization,  2012/01/21
	UMC::MP3Decoder  *  pMP3Decoder  =  new  UMC::MP3Decoder;
	if  (  !pMP3Decoder  )  goto  errLabel;

	pObj->pDecoder  =  pMP3Decoder;

	UMC::BaseCodecParams	params;


	//Initialization of MPEG Audio decoder,  2012/01/21
	if  (  (  status  =  pMP3Decoder->Init(  &params  )  )  !=  UMC::UMC_OK   )  {
		//  tmp_showInfo(  _T(  "qdcInitDecompressAudio failed, decoder init failed"  )  );
		MessageBox(  NULL,  _T(  "qdcInitDecompressAudio failed, decoder init failed"  ),  _T(  "qycx"  ),  MB_OK  );
		goto  errLabel;
	}
	//
	UMC::AudioCodecParams audio_codec_params;   
	pMP3Decoder->GetInfo(&audio_codec_params);
   
	pObj->needSize  =  audio_codec_params.m_SuggestedInputSize;
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
		pObj->common.outs[0].pBuf  =  (  BYTE  *  )malloc(  qdcObjInfo.cbOutputBuffer  );
		if  (  !pObj->common.outs[0].pBuf  )  goto  errLabel;
	}

	//
	pObj->inputForDec.uiBufSize  =  qdcObjInfo.cbInputBuffer;
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

extern  "C"  int  __declspec(  dllexport  )qdcDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_compress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  )
{	
	QDC_OBJ_mp3Dec	*	pObj	=	(  QDC_OBJ_mp3Dec  *  )pQdcObjInfo->pObj;

	if  (  uiInputSize  >  pQdcObjInfo->cbInputBuffer  )  return  -1;

#if  0
	int  index  =  0;
	memcpy(  pObj->common.outs[index].pBuf,  pInput,  uiInputSize  );
	pObj->common.outs[index].len  =  uiInputSize;
	pObj->common.outs[index].rtStart  =  iSampleTimeInMs  *  1000  *  10;
#endif

	
	myAudioDecodeStream(  pQdcObjInfo,  (  UMC::MP3Decoder  *  )pObj->pDecoder,  NULL,  pInput,  uiInputSize,  iSampleTimeInMs  );

	return  0;
}
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TESTIPP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTIPP));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTIPP));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TESTIPP);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ippStaticInit();
   for  (  ;0;  )  {
	   int  w,  h,  f;
	   //  DecodeStream(  0, 0,  0, w,  h,  f  );
	   //  myAudioDecodeStream( NULL,  NULL,  NULL,  NULL,  0,  0 );
 qdcDecompressAudio(  NULL,  NULL,  NULL,  0,  0,  0  ); 
  // qdcInitDecompressAudio(  NULL,  NULL,  NULL,  NULL  );
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
