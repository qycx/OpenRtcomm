

#ifndef  __QISCOMPRESSPROC_H__
#define  __QISCOMPRESSPROC_H__	//  {

#include	<mmsystem.h>
#include	"qdcOpenCommon.h"
#include	"qySyncObj.h"
#include	"genericQueue.h"


#include	"tmpGuiOpenFunc.h"


#if  0
typedef  struct  __qdcObj_test_t				{
				 
					 QDC_OUTPUT					outs[1];

}		 QDC_OBJ_test;
#endif


#if  0
typedef  struct  __qdcObj_h264_t				{
				 
				 struct							{
					 QY_VIDEO_HEADER			vh_decompress_real;
					 char					*	pBuf;
					 unsigned int				uiBufSize;
				 }								inputForEnc,  outputForDec;

				    
				 //  UMC::H264VideoEncoder H264Encoder;; 
				 void						*	pEncoder;


				
				 QDC_OUTPUT					outs[1];

}		 QDC_OBJ_h264;

typedef  struct  __qdcObj_h264Common_t			{

				 //  QDC_OUTPUT						outs[1];
				 QDC_OUTPUT						outs[10];	// 2011/09/04

}		 QDC_OBJ_h264Common;
#endif


typedef  struct  __qdcObj_h264Enc_t				{
				 QDC_OBJ_h264Common				common;

				 //  2011/12/12
				 unsigned  char					ucbFlippedImg;

				 //
				 struct							{
					 QY_VIDEO_HEADER			vh_decompress_real;
					 char					*	pBuf;
					 unsigned int				uiBufSize;
				 }								inputForEnc;

				    
				 //  UMC::H264VideoEncoder H264Encoder;; 
				 void						*	pEncoder;
				
				 //  2012/09/15
				 void						*	pParams;				//  EncoderParams  params;
				 void						*	pVideoEncoderParams;	//  VideoEncoderParams  *pEncoderParams = NULL;
				 void						*	pVideoProc;				//  VideoProcessing      videoProc;
				 void						*	pDataIn;				//  VideoData            dataIn;
				 void						*	pDataCvt;				//  VideoData            dataCvt;
				 void						*	pDataOut;				//  MediaData            dataOut;

				 //
				 void						*	pVccParams;				//  VideoColorConversionParams vccParams;

				 
}		 QDC_OBJ_h264Enc;


#if  0  //  2017/10/07
#ifndef  CONST_videoCompressors_ipp		//  2014/08/31
		#define		CONST_videoCompressors_ipp								8	//	"h264"					//  2011/07/30
#endif
#endif


//
typedef  struct  __qdcObj_h264Dec_t				{
				 QDC_OBJ_h264Common				common;

				 struct							{
					 QY_VIDEO_HEADER			vh_decompress_real;
					 char					*	pBuf;
					 unsigned int				uiBufSize;
				 }								outputForDec;

				    
				 //  UMC::H264VideoEncoder H264Encoder;; 
				 void						*	pDecoder;
				 //BOOL							bInited;					//  2014/02/26.等ipp解出sps,pps
				 //BOOL							bInited2;					//  2014/02/26.等ipp解除sps后,需要分配一些内存
				
				 //  2012/09/15
				 void						*	pVideoDecoderParams;		//  UMC::VideoDecoderParams Params; 
				 void						*	pVideoProc;					//  UMC::VideoProcessing	videoProc;
				 void						*	pVccParams;					//  UMC::VideoColorConversionParams vccParams;
				 BOOL							bInited_VideoProcessing;	//  =  FALSE;

				 //
				 void						*	pDataIn;					//  MediaData            dataIn;
				 void						*	pDataOut;					//  VideoData            dataOut;



				 //  2011/11/26
				 unsigned  char					ucCompressors;				//  2014/03/02
				 unsigned  char					ucbFlipped;
				 
}		 QDC_OBJ_h264Dec;

//  2012/01/20
typedef  struct  __qdcObj_mp3Common_t			{

				 //  QDC_OUTPUT						outs[1];
				 QDC_OUTPUT						outs[10];	// 2011/09/04

}		 QDC_OBJ_mp3Common;

typedef  struct  __qdcObj_mp3Enc_t				{
				 QDC_OBJ_mp3Common				common;
				 
				 //
				 struct							{
					 QY_AUDIO_HEADER			ah_decompress;	//  2012/01/25
					 //
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
					 QY_AUDIO_HEADER			ah_decompress;	//  2012/01/25
					 //
					 char					*	pBuf;
					 unsigned int				uiBufSize;
					 int						len;
				 }								inputForDec;
				 
				    
				 //  UMC::MP3Decoder MP3Decoder;; 
				 void						*	pDecoder;
				 BOOL							bInited;
				
				 int							needSize;
				 
}		 QDC_OBJ_mp3Dec;

extern  "C"  int  __declspec(  dllexport  )qdcExitCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );



#endif  //  }