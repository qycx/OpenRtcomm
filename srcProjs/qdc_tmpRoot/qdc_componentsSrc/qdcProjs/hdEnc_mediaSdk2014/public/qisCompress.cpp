// qisCompress.cpp : Defines the exported functions for the DLL application.
//

#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
#include	<Dshow.h>

#include	<assert.h>
#include	"base_allocator.h"

#include	"qisCompressProc.h"
#include	"myFunc_mediaSdk.h"
#include	"tmpGuiOpenFunc.h"

#include	"myutils.h"
#include	"tmpEncOpenFunc.h"

#include "version.h"


//
#define	CONST_ver_qisCompress		"02660254"	// "02660251"	//  2017/10/07	//  "02650115"		//  2016/12/14，"02630336"		//  2016/04/10,"02630294"		//  2015/11/03,"02630243"		//  2015/11/02,"02630239"		//  2015/10/24,"02630228"	//  2012/08/24		//  2012/06/23


//
//
//  #include	"pipeline_encode.h"
#include	"mypipeline_user.h"

//QIS_guiOpen		*  g_pGuiOpen					=	NULL;
//BOOL				g_bUsePipeline_videoconf	=  FALSE;		//  2012/09/01

//
 BOOL				g_bUsing_sharedTex_enc  =	FALSE;
 BOOL				g_bWin7					=	FALSE;


 //
#if  0
int  yuy2ToRgb24_ipp(  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );
int  rgb24ToYv12_ipp(  unsigned  char  *  rgb,  unsigned  char  *  yuv,  int  width,  int  height,  BOOL  bFlip  );
#endif












 extern  "C"  __declspec(  dllexport  )  int  qdcInit(  QDC_MGR  *  p  )
{


#ifdef  _DEBUG
		#if  0   // _DEBUG
			GetMSDKVersion(  );
			BOOL	bSupported  =  IsHwAcclSupported(  );
			#if 0
				if  (  bSupported  )	MessageBox(  NULL,  _T(  "Hardware supported"  ),  _T(  ""  ),  MB_OK  );
				else  	MessageBox(  NULL,  _T(  "Hardware not be supported"  ),  _T(  ""  ),  MB_OK  );
			#endif

			int  i  =  0;

		#endif
#endif


	OutputDebugString(  _T(  "qdcInit\n"  )  );
	//
	g_pGuiOpen  =  p->pGuiOpen;
	//
	p->iCompressorId  =  1;
	_tcsncpy(  p->name,  _T(  "test"  ),  sizeof(  p->name  )  /  sizeof(  p->name[0]  )  );
	//  2014/12/02
	strncpy(  p->ver,  CONST_ver_qisCompress,  mycountof(  p->ver  )  );  

	//
#if  0
	p->pf_yuy2ToRgb24  =  yuy2ToRgb24_ipp;
#endif

	//
	p->ucbNotSupported_hw  =  !IsHwAcclSupported(  NULL  ); 

	//  2012/09/01. ÔÚhd4000µÄºËÏÔ,²ÉÓÃpipeline_videoconf. hd p4000ÉÏ³ö´í,ËùÒÔ,ÔÝÊ±²»Ê¹ÓÃ
#if  0
	g_bUsePipeline_videoconf  =  FALSE;	//  IsHw31Supported(  );	//  FALSE;	//  TRUE;
#endif
	
	//  2012/09/10. Ã»ÓÐ½â¾öºÃÓ²½âÑ¹µÄ³õÊ¼»¯,¾­³£³öÏÖÎÞ·¨³õÊ¼»¯µÄ´íÎó,ËùÒÔÔÝÊ±²»ÄÜÊ¹ÓÃ
	//  if  (  p->ucbNotSupported  ||  !IsHw31Supported(  )  )  
	{
		p->ucbNotSupported_dec_h264  =  TRUE;
	}
#ifdef  _DEBUG
		//  p->ucbNotSupported_dec_h264  =  TRUE;		
		//  g_bUsePipeline_videoconf  =  FALSE;
#endif

	//
	{	
		//	
		unsigned  char  ucbUsing_sharedTex  =  FALSE;
					
		//  2015/09/28		
		mfxVersion  ver;
		if  (  IsSupported_hwAcclD11(  &ver  )					   
			&&  IsSupported_sharedTex_msdk(  &ver  )  )  				   
		{		
			ucbUsing_sharedTex  =  TRUE;						   
		}	
		//
		g_bUsing_sharedTex_enc  =  ucbUsing_sharedTex;

	}

	//  2012/05/26
	//  tmp_showInfo(  _T(  "qdcInit called. v025127"  )  );
	TCHAR	tBuf[128];
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "qdcInit called. hdEnc_mediasdk,%s"  ),  _T(  CONST_ver_qisCompress  )  );
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s. %s"  ),  tBuf,  p->ucbNotSupported_hw  ?  _T(  "hw not supported"  )  :  _T(  "OK"  )  );
	//  _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s. bUsePipeline %d, ucbNotSupported_dec_h264 %d"  ),  tBuf,  g_bUsePipeline_videoconf,  p->ucbNotSupported_dec_h264  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. bUse_sharedTex_enc %d"  ),  tBuf,  g_bUsing_sharedTex_enc  );
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s. ucbNotSupported_dec_h264 %d"  ),  tBuf,  p->ucbNotSupported_dec_h264  );
	tmp_showInfo(  tBuf  );

	
#ifdef  _DEBUG
		
#endif

	return  0;
}


 extern  "C"  int  __declspec(  dllexport  )qdcExit(  QDC_MGR  *  p  )
{

	OutputDebugString(  _T(  "qdcExit\n"  )  );

	return  0;
}



 

 //  2015/10/20 
  extern  "C"  int  __declspec(  dllexport  )qdcGetProp(  int  iPropId,  void  *  pParam_input,  void  *  pParam_output  )
 {
	 int  iErr  =  -1;

	 //
	 if  (  !pParam_output  )  return  -1;

	 //
#if  0
	 switch  (  iPropId  )  {
			 case  CONST_qdcPropId_bSupport_sharedTex_enc:  {
				   BOOL  *  pbVal  =  (  BOOL  *  )pParam_output;
				   
				   //
				   unsigned  char  ucbUsing_sharedTex  =  FALSE;

				   //  2015/09/28
				   mfxVersion  ver;
				   if  (  IsSupported_hwAcclD11(  &ver  )
					   &&  IsSupported_sharedTex_msdk(  &ver  )  )  
				   {
					   ucbUsing_sharedTex  =  TRUE;		
				   }	
				   //
				   *pbVal  =  (  BOOL  )ucbUsing_sharedTex;
				   //
				   }
				   //
				   break;
			 default:
				    tmp_showInfo(  _T(  "qdcGetProp failed, unprocessed propId"  )  );
					goto  errLabel;
	 }
#endif
	 //
	 switch  (  iPropId  )  {
			 case  CONST_qdcPropId_bSupport_sharedTex_enc:  
			 default:
				    if  (  tmpEnc_qdcGetProp(  iPropId,  pParam_input,  pParam_output  )  )  {
						goto  errLabel;
					}
					break;
	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
 }


  //
   extern  "C"  int  __declspec(  dllexport  )qdcSetProp(  int  iPropId,  void  *  pParam_input,  void  *  pParam_output  )
 {
	 int  iErr  =  -1;

	 //
	 if  (  !pParam_input  )  return  -1;

	 //
	 switch  (  iPropId  )  {
			 case  CONST_qdcPropId_bWin7:  {
				   bool  *  pbWin7  =  (  bool  *  )pParam_input;
				   g_bWin7  =  *pbWin7;
				   }
				   break;
			 default:
				    tmp_showInfo(  _T(  "qdcSetProp failed, unknown propId"  )  );
					goto  errLabel;
					break;
	 }

	 //
	 iErr  =  0;
errLabel:
	 return  iErr;

   }



 //
 extern  "C"  int  __declspec(  dllexport  )qdcGetCompressAudioCfg(  WAVEFORMATEX  *  pWf_decompress,  WAVEFORMATEX  *  pWf_compress  )
{
	memset(  pWf_compress,  0,  sizeof(  pWf_compress[0]  )  );

	pWf_compress->wFormatTag			=	WAVE_FORMAT_PCM;
	pWf_compress->nChannels				=	1;
	pWf_compress->wBitsPerSample		=	16;
	pWf_compress->cbSize				=	0;
	pWf_compress->nSamplesPerSec		=	8000;

	pWf_compress->nBlockAlign		=	(  pWf_compress->wBitsPerSample  /  8  )  *  pWf_compress->nChannels;
	pWf_compress->nAvgBytesPerSec	=	pWf_compress->nSamplesPerSec  *  pWf_compress->nBlockAlign;

	memcpy(  pWf_decompress,  pWf_compress,  sizeof(  pWf_decompress[0]  )  );

	return  0;
}

 extern  "C"  int  __declspec(  dllexport  )qdcGetCompressVideoCfg(  char  *  fourccStr,  unsigned  int  size  )
{
	strncpy(  fourccStr,  "h264",  size  );
	return  0;
}


 void  qdcFreeOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_transCommon  *  pObj	=	(  QDC_OBJ_transCommon  *  )pQdcObjInfo->var.pObj;
	int			i;

	for  (  i  =  0;  i  <  sizeof(  pObj->outs  )  /  sizeof(  pObj->outs[0]  );  i  ++  )  {
		 if  (  pObj->outs[i].pBuf  )  free(  pObj->outs[i].pBuf  );
	}
	memset(  &pObj->outs,  0,  sizeof(  pObj->outs  )  );
}

 
extern  "C"  int  __declspec(  dllexport  )qdcInitCompressAudio(  void  *  pAudioCompressorCfg_reserved,  QY_AUDIO_HEADER  *  pAh_decompress,  QY_AUDIO_HEADER  *  pAh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int						iErr	=	-1;
	QDC_OBJ_INFO			qdcObjInfo;
	QDC_OBJ_trans		*	pObj	=	NULL;	

	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;

	memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_trans  *  )malloc(  sizeof(  QDC_OBJ_trans  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	qdcObjInfo.var.pObj  =  pObj;

	//  qdcObjInfo.
	qdcObjInfo.var.cbInputBuffer  =  pAh_decompress->wfx.nAvgBytesPerSec  *  2;
	qdcObjInfo.var.cbOutputBuffer  =  qdcObjInfo.var.cbInputBuffer;

	//
	memcpy(  pAh_compress,  pAh_decompress,  sizeof(  pAh_compress[0]  )  );

	//	
	if  (  !pObj->common.outs[0].pBuf  )  {
		pObj->common.outs[0].pBuf  =  (  BYTE  *  )malloc(  qdcObjInfo.var.cbOutputBuffer  );
		if  (  !pObj->common.outs[0].pBuf  )  goto  errLabel;
	}


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
	QDC_OBJ_trans	*	pObj  =  (  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;

	if  (  pObj  )  {
		//
		qdcFreeOutputs(  pQdcObjInfo  );
		//
		free(  pObj  );	
	}
	pQdcObjInfo->var.pObj  =  NULL;

	return  0;
}

extern  "C"  int  __declspec(  dllexport  )qdcCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_decompress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs  )
{
	QDC_OBJ_trans	*	pObj	=	(  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;

	if  (  uiInputSize  >  pQdcObjInfo->var.cbInputBuffer  )  return  -1;

	int  index  =  0;
	memcpy(  pObj->common.outs[index].pBuf,  pInput,  uiInputSize  );
	pObj->common.outs[index].len  =  uiInputSize;
	pObj->common.outs[index].rtStart  =  iSampleTimeInMs  *  1000  *  10;

	return  0;
}

extern  "C"  int  __declspec(  dllexport  )qdcInitDecompressAudio(  void  *  pAudioCompressorCfg,  QY_AUDIO_HEADER  *  pAh_compress,  QY_AUDIO_HEADER  *  pAh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{	
	int						iErr	=	-1;
	QDC_OBJ_INFO			qdcObjInfo;
	QDC_OBJ_trans		*	pObj	=	NULL;	

	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;

	memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_trans  *  )malloc(  sizeof(  QDC_OBJ_trans  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	qdcObjInfo.var.pObj  =  pObj;

	//  qdcObjInfo.
	qdcObjInfo.var.cbOutputBuffer  =  pAh_decompress->wfx.nAvgBytesPerSec  *  2;
	qdcObjInfo.var.cbInputBuffer  =  qdcObjInfo.var.cbOutputBuffer;

	//
	memcpy(  pAh_compress,  pAh_decompress,  sizeof(  pAh_compress[0]  )  );

	//	
	if  (  !pObj->common.outs[0].pBuf  )  {
		pObj->common.outs[0].pBuf  =  (  BYTE  *  )malloc(  qdcObjInfo.var.cbOutputBuffer  );
		if  (  !pObj->common.outs[0].pBuf  )  goto  errLabel;
	}

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
	QDC_OBJ_trans	*	pObj  =  (  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;

	if  (  pObj  )  {
		//
		qdcFreeOutputs(  pQdcObjInfo  );
		//
		free(  pObj  );	
	}
	pQdcObjInfo->var.pObj  =  NULL;

	return  0;
}

extern  "C"  int  __declspec(  dllexport  )qdcDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_compress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  )
{	
	QDC_OBJ_trans	*	pObj	=	(  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;

	if  (  uiInputSize  >  pQdcObjInfo->var.cbInputBuffer  )  return  -1;

	int  index  =  0;
	memcpy(  pObj->common.outs[index].pBuf,  pInput,  uiInputSize  );
	pObj->common.outs[index].len  =  uiInputSize;
	pObj->common.outs[index].rtStart  =  iSampleTimeInMs  *  1000  *  10;

	return  0;
}

//
#define VAL_CHECK(val, argIdx, argName) \
{ \
    if (val) \
    { \
        PrintHelp(NULL, MSDK_STRING("Input argument number %d \"%s\" require more parameters"), argIdx, argName); \
        return MFX_ERR_UNSUPPORTED;\
    } \
}

// Extensions for internal use, normally these macros are blank
#ifdef MOD_ENC
    #include "extension_macros.h"
#else
    #define MOD_ENC_CREATE_PIPELINE
    #define MOD_ENC_PRINT_HELP
    #define MOD_ENC_PARSE_INPUT
#endif


void PrintHelp(msdk_char *strAppName, const msdk_char *strErrorMessage, ...)
{
    msdk_printf(MSDK_STRING("Encoding Sample Version %s\n\n"), GetMSDKSampleVersion().c_str());

    if (strErrorMessage)
    {
        va_list args;
        msdk_printf(MSDK_STRING("ERROR: "));
        va_start(args, strErrorMessage);
        msdk_vprintf(strErrorMessage, args);
        va_end(args);
        msdk_printf(MSDK_STRING("\n\n"));
    }

    msdk_printf(MSDK_STRING("Usage: %s <msdk-codecid> [<options>] -i InputYUVFile -o OutputEncodedFile -w width -h height\n"), strAppName);
    msdk_printf(MSDK_STRING("\n"));
    msdk_printf(MSDK_STRING("Supported codecs, <msdk-codecid>:\n"));
    msdk_printf(MSDK_STRING("   <codecid>=h264|mpeg2|vc1|mvc|jpeg - built-in Media SDK codecs\n"));
    msdk_printf(MSDK_STRING("   <codecid>=h265                - in-box Media SDK plugins (may require separate downloading and installation)\n"));
    msdk_printf(MSDK_STRING("   If codecid is jpeg, -q option is mandatory.)\n"));
    msdk_printf(MSDK_STRING("Options: \n"));
#ifdef MOD_ENC
    MOD_ENC_PRINT_HELP;
#endif
    msdk_printf(MSDK_STRING("   [-nv12|yuy2|p010|rgb4] - input color format (by default YUV420 is expected). YUY2 is for JPEG encode only.\n"));
    msdk_printf(MSDK_STRING("   [-ec::p010] - force usage of P010 surfaces for encoder (conversion will be made if necessary). Use for 10 bit HEVC encoding\n"));
    msdk_printf(MSDK_STRING("   [-tff|bff] - input stream is interlaced, top|bottom fielf first, if not specified progressive is expected\n"));
    msdk_printf(MSDK_STRING("   [-bref] - arrange B frames in B pyramid reference structure\n"));
    msdk_printf(MSDK_STRING("   [-nobref] -  do not use B-pyramid (by default the decision is made by library)\n"));
    msdk_printf(MSDK_STRING("   [-idr_interval size] - idr interval, default 0 means every I is an IDR, 1 means every other I frame is an IDR etc\n"));
    msdk_printf(MSDK_STRING("   [-f frameRate] - video frame rate (frames per second)\n"));
    msdk_printf(MSDK_STRING("   [-n number] - number of frames to process\n"));
    msdk_printf(MSDK_STRING("   [-b bitRate] - encoded bit rate (Kbits per second), valid for H.264, H.265, MPEG2 and MVC encoders \n"));
    msdk_printf(MSDK_STRING("   [-u speed|quality|balanced] - target usage, valid for H.264, H.265, MPEG2 and MVC encoders\n"));
    msdk_printf(MSDK_STRING("   [-q quality] - mandatory quality parameter for JPEG encoder. In range [1,100]. 100 is the best quality. \n"));
    msdk_printf(MSDK_STRING("   [-r distance] - Distance between I- or P- key frames (1 means no B-frames) \n"));
    msdk_printf(MSDK_STRING("   [-g size] - GOP size (default 256)\n"));
    msdk_printf(MSDK_STRING("   [-x numRefs]   - number of reference frames\n"));
    msdk_printf(MSDK_STRING("   [-la] - use the look ahead bitrate control algorithm (LA BRC) (by default constant bitrate control method is used)\n"));
    msdk_printf(MSDK_STRING("           for H.264, H.265 encoder. Supported only with -hw option on 4th Generation Intel Core processors. \n"));
    msdk_printf(MSDK_STRING("   [-lad depth] - depth parameter for the LA BRC, the number of frames to be analyzed before encoding. In range [10,100].\n"));
    msdk_printf(MSDK_STRING("            may be 1 in the case when -mss option is specified \n"));
    msdk_printf(MSDK_STRING("   [-dstw width] - destination picture width, invokes VPP resizing\n"));
    msdk_printf(MSDK_STRING("   [-dsth height] - destination picture height, invokes VPP resizing\n"));
    msdk_printf(MSDK_STRING("   [-hw] - use platform specific SDK implementation (default)\n"));
    msdk_printf(MSDK_STRING("   [-sw] - use software implementation, if not specified platform specific SDK implementation is used\n"));
    msdk_printf(MSDK_STRING("   [-p guid] - 32-character hexadecimal guid string\n"));
    msdk_printf(MSDK_STRING("                              (optional for Media SDK in-box plugins, required for user-encoder ones)\n"));
    msdk_printf(MSDK_STRING("   [-path path] - path to plugin (valid only in pair with -p option)\n"));
    msdk_printf(MSDK_STRING("   [-async]                 - depth of asynchronous pipeline. default value is 4. must be between 1 and 20.\n"));
    msdk_printf(MSDK_STRING("   [-gpucopy::<on,off>] Enable or disable GPU copy mode\n"));
    msdk_printf(MSDK_STRING("   [-vbr]                   - variable bitrate control\n"));
    msdk_printf(MSDK_STRING("   [-cqp]                   - constant quantization parameter (CQP BRC) bitrate control method\n"));
    msdk_printf(MSDK_STRING("                              (by default constant bitrate control method is used), should be used along with -qpi, -qpp, -qpb.\n"));
    msdk_printf(MSDK_STRING("   [-qpi]                   - constant quantizer for I frames (if bitrace control method is CQP). In range [1,51]. 0 by default, i.e.no limitations on QP.\n"));
    msdk_printf(MSDK_STRING("   [-qpp]                   - constant quantizer for P frames (if bitrace control method is CQP). In range [1,51]. 0 by default, i.e.no limitations on QP.\n"));
    msdk_printf(MSDK_STRING("   [-qpb]                   - constant quantizer for B frames (if bitrace control method is CQP). In range [1,51]. 0 by default, i.e.no limitations on QP.\n"));
    msdk_printf(MSDK_STRING("   [-qsv-ff]       Enable QSV-FF mode\n"));
    msdk_printf(MSDK_STRING("   [-gpb:<on,off>]          - Turn this option OFF to make HEVC encoder use regular P-frames instead of GPB\n"));
    msdk_printf(MSDK_STRING("   [-num_slice]             - number of slices in each video frame. 0 by default.\n"));
    msdk_printf(MSDK_STRING("                              If num_slice equals zero, the encoder may choose any slice partitioning allowed by the codec standard.\n"));
    msdk_printf(MSDK_STRING("   [-mss]                   - maximum slice size in bytes. Supported only with -hw and h264 codec. This option is not compatible with -num_slice option.\n"));
    msdk_printf(MSDK_STRING("   [-mfs]                   - maximum frame size in bytes. Supported only with h264 and hevc codec for VBR mode.\n"));
    msdk_printf(MSDK_STRING("   [-re]                    - enable region encode mode. Works only with h265 encoder\n"));
    msdk_printf(MSDK_STRING("   [-CodecProfile]          - specifies codec profile\n"));
    msdk_printf(MSDK_STRING("   [-CodecLevel]            - specifies codec level\n"));
    msdk_printf(MSDK_STRING("   [-GopOptFlag:closed]     - closed gop\n"));
    msdk_printf(MSDK_STRING("   [-GopOptFlag:strict]     - strict gop\n"));
    msdk_printf(MSDK_STRING("   [-InitialDelayInKB]      - the decoder starts decoding after the buffer reaches the initial size InitialDelayInKB, \
                            which is equivalent to reaching an initial delay of InitialDelayInKB*8000/TargetKbps ms\n"));
    msdk_printf(MSDK_STRING("   [-BufferSizeInKB ]       - represents the maximum possible size of any compressed frames\n"));
    msdk_printf(MSDK_STRING("   [-MaxKbps ]              - for variable bitrate control, specifies the maximum bitrate at which \
                            the encoded data enters the Video Buffering Verifier buffer\n"));
    msdk_printf(MSDK_STRING("   [-signal:tm ]            - represents transfer matrix coefficients for mfxExtVideoSignalInfo. 0 - unknown, 1 - BT709, 2 - BT601\n"));

    msdk_printf(MSDK_STRING("   [-timeout]               - encoding in cycle not less than specific time in seconds\n"));
    msdk_printf(MSDK_STRING("   [-membuf]                - size of memory buffer in frames\n"));
    msdk_printf(MSDK_STRING("   [-uncut]                 - do not cut output file in looped mode (in case of -timeout option)\n"));
    msdk_printf(MSDK_STRING("   [-dump fileName]         - dump MSDK components configuration to the file in text form\n"));

    msdk_printf(MSDK_STRING("Example: %s h265 -i InputYUVFile -o OutputEncodedFile -w width -h height -hw -p 2fca99749fdb49aeb121a5b63ef568f7\n"), strAppName);
#if D3D_SURFACES_SUPPORT
    msdk_printf(MSDK_STRING("   [-d3d] - work with d3d surfaces\n"));
    msdk_printf(MSDK_STRING("   [-d3d11] - work with d3d11 surfaces\n"));
    msdk_printf(MSDK_STRING("Example: %s h264|h265|mpeg2|jpeg -i InputYUVFile -o OutputEncodedFile -w width -h height -d3d -hw \n"), strAppName);
    msdk_printf(MSDK_STRING("Example for MVC: %s mvc -i InputYUVFile_1 -i InputYUVFile_2 -o OutputEncodedFile -w width -h height \n"), strAppName);
#endif
#ifdef LIBVA_SUPPORT
    msdk_printf(MSDK_STRING("   [-vaapi] - work with vaapi surfaces\n"));
    msdk_printf(MSDK_STRING("Example: %s h264|mpeg2|mvc -i InputYUVFile -o OutputEncodedFile -w width -h height -angle 180 -g 300 -r 1 \n"), strAppName);
#endif
#if defined (ENABLE_V4L2_SUPPORT)
    msdk_printf(MSDK_STRING("   [-d]                            - Device video node (eg: /dev/video0)\n"));
    msdk_printf(MSDK_STRING("   [-p]                            - Mipi Port number (eg: Port 0)\n"));
    msdk_printf(MSDK_STRING("   [-m]                            - Mipi Mode Configuration [PREVIEW/CONTINUOUS/STILL/VIDEO]\n"));
    msdk_printf(MSDK_STRING("   [-uyvy]                        - Input Raw format types V4L2 Encode\n"));
    msdk_printf(MSDK_STRING("   [-YUY2]                        - Input Raw format types V4L2 Encode\n"));
    msdk_printf(MSDK_STRING("   [-i::v4l2]                        - To enable v4l2 option\n"));
    msdk_printf(MSDK_STRING("Example: %s h264|mpeg2|mvc -i::v4l2 -o OutputEncodedFile -w width -h height -d /dev/video0 -uyvy -m preview -p 0\n"), strAppName);
#endif
    msdk_printf(MSDK_STRING("   [-viewoutput] - instruct the MVC encoder to output each view in separate bitstream buffer. Depending on the number of -o options behaves as follows:\n"));
    msdk_printf(MSDK_STRING("                   1: two views are encoded in single file\n"));
    msdk_printf(MSDK_STRING("                   2: two views are encoded in separate files\n"));
    msdk_printf(MSDK_STRING("                   3: behaves like 2 -o opitons was used and then one -o\n\n"));
    msdk_printf(MSDK_STRING("Example: %s mvc -i InputYUVFile_1 -i InputYUVFile_2 -o OutputEncodedFile_1 -o OutputEncodedFile_2 -viewoutput -w width -h height \n"), strAppName);
    // user module options
    msdk_printf(MSDK_STRING("User module options: \n"));
    msdk_printf(MSDK_STRING("   [-angle 180] - enables 180 degrees picture rotation before encoding, CPU implementation by default. Rotation requires NV12 input. Options -tff|bff, -dstw, -dsth, -d3d are not effective together with this one, -nv12 is required.\n"));
    msdk_printf(MSDK_STRING("   [-opencl] - rotation implementation through OPENCL\n"));
    msdk_printf(MSDK_STRING("Example: %s h264|h265|mpeg2|mvc|jpeg -i InputYUVFile -o OutputEncodedFile -w width -h height -angle 180 -opencl \n"), strAppName);

    msdk_printf(MSDK_STRING("\n"));
}

mfxStatus ParseInputString(msdk_char* strInput[], mfxU8 nArgNum, sInputParams* pParams)
{

    if (1 == nArgNum)
    {
        PrintHelp(strInput[0], NULL);
        return MFX_ERR_UNSUPPORTED;
    }

    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);
    msdk_opt_read(MSDK_CPU_ROTATE_PLUGIN, pParams->strPluginDLLPath);

    // default implementation
    pParams->bUseHWLib = true;
    pParams->isV4L2InputEnabled = false;
    pParams->nNumFrames = 0;
    pParams->FileInputFourCC = MFX_FOURCC_I420;
    pParams->EncodeFourCC = MFX_FOURCC_NV12;
#if defined (ENABLE_V4L2_SUPPORT)
    pParams->MipiPort = -1;
    pParams->MipiMode = NONE;
    pParams->v4l2Format = NO_FORMAT;
#endif

    // parse command line parameters
    for (mfxU8 i = 1; i < nArgNum; i++)
    {
        MSDK_CHECK_POINTER(strInput[i], MFX_ERR_NULL_PTR);

        if (MSDK_CHAR('-') != strInput[i][0])
        {
            mfxStatus sts = StrFormatToCodecFormatFourCC(strInput[i], pParams->CodecId);
            if (sts != MFX_ERR_NONE)
            {
                PrintHelp(strInput[0], MSDK_STRING("Unknown codec"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (!IsEncodeCodecSupported(pParams->CodecId))
            {
                PrintHelp(strInput[0], MSDK_STRING("Unsupported codec"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (pParams->CodecId == CODEC_MVC)
            {
                pParams->CodecId = MFX_CODEC_AVC;
                pParams->MVC_flags |= MVC_ENABLED;
            }
            continue;
        }

        // process multi-character options
        if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-dstw")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nDstWidth))
            {
                PrintHelp(strInput[0], MSDK_STRING("Destination picture Width is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-dsth")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nDstHeight))
            {
                PrintHelp(strInput[0], MSDK_STRING("Destination picture Height is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-sw")))
        {
            pParams->bUseHWLib = false;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-hw")))
        {
            pParams->bUseHWLib = true;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-yuy2")))
        {
#if defined (ENABLE_V4L2_SUPPORT)
            pParams->v4l2Format = YUY2;
#endif
            pParams->FileInputFourCC = MFX_FOURCC_YUY2;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-nv12")))
        {
            pParams->FileInputFourCC = MFX_FOURCC_NV12;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-rgb4")))
        {
            pParams->FileInputFourCC = MFX_FOURCC_RGB4;
            pParams->EncodeFourCC = MFX_FOURCC_RGB4;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-p010")))
        {
            pParams->FileInputFourCC = MFX_FOURCC_P010;
            pParams->EncodeFourCC = MFX_FOURCC_P010;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-ec::p010")))
        {
            pParams->EncodeFourCC = MFX_FOURCC_P010;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-tff")))
        {
            pParams->nPicStruct = MFX_PICSTRUCT_FIELD_TFF;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-bff")))
        {
            pParams->nPicStruct = MFX_PICSTRUCT_FIELD_BFF;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-bref")))
        {
            pParams->nBRefType = MFX_B_REF_PYRAMID;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-nobref")))
        {
            pParams->nBRefType = MFX_B_REF_OFF;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-idr_interval")))
        {
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nIdrInterval))
            {
                PrintHelp(strInput[0], MSDK_STRING("IdrInterval is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-angle")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nRotationAngle))
            {
                PrintHelp(strInput[0], MSDK_STRING("Rotation Angle is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-opencl")))
        {
            msdk_opt_read(MSDK_OCL_ROTATE_PLUGIN, pParams->strPluginDLLPath);
            pParams->nRotationAngle = 180;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-viewoutput")))
        {
            if (!(MVC_ENABLED & pParams->MVC_flags))
            {
                PrintHelp(strInput[0], MSDK_STRING("-viewoutput option is supported only when mvc codec specified"));
                return MFX_ERR_UNSUPPORTED;
            }
            pParams->MVC_flags |= MVC_VIEWOUTPUT;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-la")))
        {
            pParams->nRateControlMethod = MFX_RATECONTROL_LA;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-lad")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            pParams->nRateControlMethod = MFX_RATECONTROL_LA;
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nLADepth))
            {
                PrintHelp(strInput[0], MSDK_STRING("Look Ahead Depth is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-vbr")))
        {
            pParams->nRateControlMethod = MFX_RATECONTROL_VBR;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-mss")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nMaxSliceSize))
            {
                PrintHelp(strInput[0], MSDK_STRING("MaxSliceSize is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-mfs")))
       {
            VAL_CHECK(i + 1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nMaxFrameSize))
            {
                PrintHelp(strInput[0], MSDK_STRING("MaxFrameSize is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
       }
#if D3D_SURFACES_SUPPORT
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-d3d")))
        {
            pParams->memType = D3D9_MEMORY;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-d3d11")))
        {
            pParams->memType = D3D11_MEMORY;
        }
#endif
#ifdef LIBVA_SUPPORT
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-vaapi")))
        {
            pParams->memType = D3D9_MEMORY;
        }
#endif
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-async")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);

            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nAsyncDepth))
            {
                PrintHelp(strInput[0], MSDK_STRING("Async Depth is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-CodecLevel")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->CodecLevel))
            {
                PrintHelp(strInput[0], MSDK_STRING("CodecLevel is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-CodecProfile")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->CodecProfile))
            {
                PrintHelp(strInput[0], MSDK_STRING("CodecProfile is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-GopOptFlag:closed")))
        {
            pParams->GopOptFlag = MFX_GOP_CLOSED;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-GopOptFlag:strict")))
        {
            pParams->GopOptFlag = MFX_GOP_STRICT;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-InitialDelayInKB")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->InitialDelayInKB))
            {
                PrintHelp(strInput[0], MSDK_STRING("InitialDelayInKB is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-MaxKbps")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->MaxKbps))
            {
                PrintHelp(strInput[0], MSDK_STRING("MaxKbps is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-BufferSizeInKB")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->BufferSizeInKB))
            {
                PrintHelp(strInput[0], MSDK_STRING("BufferSizeInKB is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-timeout")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);

            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nTimeout))
            {
                PrintHelp(strInput[0], MSDK_STRING("Timeout is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-signal:tm")))
        {
            VAL_CHECK(i + 1 >= nArgNum, i, strInput[i]);

            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->TransferMatrix))
            {
                PrintHelp(strInput[0], MSDK_STRING("Transfer matrix param is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-membuf")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);

            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nMemBuf))
            {
                PrintHelp(strInput[0], MSDK_STRING("membuf is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-uncut")))
        {
            pParams->bUncut = true;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-gpucopy::on")))
        {
            pParams->gpuCopy = MFX_GPUCOPY_ON;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-gpucopy::off")))
        {
            pParams->gpuCopy = MFX_GPUCOPY_OFF;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-dump")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->DumpFileName))
            {
                PrintHelp(strInput[0], MSDK_STRING("File Name for dumping MSDK library configuration should be provided"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-cqp")))
        {
            pParams->nRateControlMethod = MFX_RATECONTROL_CQP;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-qpi")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nQPI))
            {
                PrintHelp(strInput[0], MSDK_STRING("Quantizer for I frames is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-qpp")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nQPP))
            {
                PrintHelp(strInput[0], MSDK_STRING("Quantizer for P frames is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-qpb")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nQPB))
            {
                PrintHelp(strInput[0], MSDK_STRING("Quantizer for B frames is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-gpb:on")))
        {
            pParams->nGPB = MFX_CODINGOPTION_ON;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-gpb:off")))
        {
            pParams->nGPB = MFX_CODINGOPTION_OFF;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-qsv-ff")))
        {
            pParams->enableQSVFF=true;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-num_slice")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nNumSlice))
            {
                PrintHelp(strInput[0], MSDK_STRING("Number of slices is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        } else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-path")))
        {
            i++;
#if defined(_WIN32) || defined(_WIN64)
            msdk_char wchar[MSDK_MAX_FILENAME_LEN];
            msdk_opt_read(strInput[i], wchar);
            std::wstring wstr(wchar);
            std::string str(wstr.begin(), wstr.end());

            strcpy_s(pParams->pluginParams.strPluginPath, str.c_str());
#else
            msdk_opt_read(strInput[i], pParams->pluginParams.strPluginPath);
#endif
            pParams->pluginParams.type = MFX_PLUGINLOAD_TYPE_FILE;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-re")))
        {
            pParams->UseRegionEncode = true;
        }
#ifdef MOD_ENC
        MOD_ENC_PARSE_INPUT
#endif
#if defined (ENABLE_V4L2_SUPPORT)
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-d")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->DeviceName))
            {
                PrintHelp(strInput[0], MSDK_STRING("Device name is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-uyvy")))
        {
            pParams->v4l2Format = UYVY;

        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-p")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->MipiPort))
            {
                PrintHelp(strInput[0], MSDK_STRING("Mipi-port is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-m")))
        {
            VAL_CHECK(i+1 >= nArgNum, i, strInput[i]);
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->MipiModeName))
            {
                PrintHelp(strInput[0], MSDK_STRING("Device name is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }

            if(strcasecmp(pParams->MipiModeName,"STILL") == 0)
                pParams->MipiMode = STILL;
            else if(strcasecmp(pParams->MipiModeName,"VIDEO") == 0)
                pParams->MipiMode = VIDEO;
            else if(strcasecmp(pParams->MipiModeName,"PREVIEW") == 0)
                pParams->MipiMode = PREVIEW;
            else if(strcasecmp(pParams->MipiModeName,"CONTINUOUS") == 0)
                pParams->MipiMode = CONTINUOUS;
            else
                pParams->MipiMode = NONE;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-i::v4l2")))
        {
            pParams->isV4L2InputEnabled = true;
        }
#endif
        else // 1-character options
        {
            switch (strInput[i][1])
            {
            case MSDK_CHAR('u'):
                if (++i < nArgNum) {
                    pParams->nTargetUsage = StrToTargetUsage(strInput[i]);
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-u' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('w'):
                if (++i < nArgNum) {
                    if (MFX_ERR_NONE != msdk_opt_read(strInput[i], pParams->nWidth))
                    {
                        PrintHelp(strInput[0], MSDK_STRING("Width is invalid"));
                        return MFX_ERR_UNSUPPORTED;
                    }
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-w' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('h'):
                if (++i < nArgNum) {
                    if (MFX_ERR_NONE != msdk_opt_read(strInput[i], pParams->nHeight))
                    {
                        PrintHelp(strInput[0], MSDK_STRING("Height is invalid"));
                        return MFX_ERR_UNSUPPORTED;
                    }
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-h' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('f'):
                if (++i < nArgNum) {
                    if (MFX_ERR_NONE != msdk_opt_read(strInput[i], pParams->dFrameRate))
                    {
                        PrintHelp(strInput[0], MSDK_STRING("Frame Rate is invalid"));
                        return MFX_ERR_UNSUPPORTED;
                    }
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-f' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('n'):
                if (++i < nArgNum) {
                    if (MFX_ERR_NONE != msdk_opt_read(strInput[i], pParams->nNumFrames))
                    {
                        PrintHelp(strInput[0], MSDK_STRING("Number of frames to process is invalid"));
                        return MFX_ERR_UNSUPPORTED;
                    }
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-n' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('b'):
                if (++i < nArgNum) {
                    if (MFX_ERR_NONE != msdk_opt_read(strInput[i], pParams->nBitRate))
                    {
                        PrintHelp(strInput[0], MSDK_STRING("Bit Rate is invalid"));
                        return MFX_ERR_UNSUPPORTED;
                    }
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-b' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('x'):
                if (++i < nArgNum) {
                    if (MFX_ERR_NONE != msdk_opt_read(strInput[i], pParams->nNumRefFrame))
                    {
                        PrintHelp(strInput[0], MSDK_STRING("Ref Num is invalid"));
                        return MFX_ERR_UNSUPPORTED;
                    }
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-x' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('g'):
                if (++i < nArgNum) {
                    if (MFX_ERR_NONE != msdk_opt_read(strInput[i], pParams->nGopPicSize))
                    {
                        PrintHelp(strInput[0], MSDK_STRING("Gop Size is invalid"));
                        return MFX_ERR_UNSUPPORTED;
                    }
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-g' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('r'):
                if (++i < nArgNum) {
                    if (MFX_ERR_NONE != msdk_opt_read(strInput[i], pParams->nGopRefDist))
                    {
                        PrintHelp(strInput[0], MSDK_STRING("Ref Dist is invalid"));
                        return MFX_ERR_UNSUPPORTED;
                    }
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-r' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('i'):
                if (++i < nArgNum) {
                    pParams->InputFiles.push_back(msdk_string(strInput[i]));
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-i' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('o'):
                if (++i < nArgNum) {
                    pParams->dstFileBuff.push_back(strInput[i]);
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-o' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('q'):
                if (++i < nArgNum) {
                    if (MFX_ERR_NONE != msdk_opt_read(strInput[i], pParams->nQuality))
                    {
                        PrintHelp(strInput[0], MSDK_STRING("Quality is invalid"));
                        return MFX_ERR_UNSUPPORTED;
                    }
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-q' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('p'):
                if (++i < nArgNum) {
                    if (MFX_ERR_NONE == ConvertStringToGuid(strInput[i], pParams->pluginParams.pluginGuid))
                    {
                        if(pParams->pluginParams.type != MFX_PLUGINLOAD_TYPE_FILE)
                        {
                            pParams->pluginParams.type = MFX_PLUGINLOAD_TYPE_GUID;
                        }
                    }
                    else
                    {
                        PrintHelp(strInput[0], MSDK_STRING("Unknown options"));
                    }
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-p' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('?'):
                PrintHelp(strInput[0], NULL);
                return MFX_ERR_UNSUPPORTED;
            default:
                PrintHelp(strInput[0], MSDK_STRING("Unknown options"));
            }
        }
    }

#if defined (ENABLE_V4L2_SUPPORT)
    if (pParams->isV4L2InputEnabled)
    {
        if (0 == msdk_strlen(pParams->DeviceName))
        {
            PrintHelp(strInput[0], MSDK_STRING("Device Name not found"));
            return MFX_ERR_UNSUPPORTED;
        }

        if ((pParams->MipiPort > -1 && pParams->MipiMode == NONE) ||
            (pParams->MipiPort < 0 && pParams->MipiMode != NONE))
        {
            PrintHelp(strInput[0], MSDK_STRING("Invalid Mipi Configuration\n"));
            return MFX_ERR_UNSUPPORTED;
        }

        if (pParams->v4l2Format == NO_FORMAT)
        {
            PrintHelp(strInput[0], MSDK_STRING("NO input v4l2 format\n"));
            return MFX_ERR_UNSUPPORTED;
        }
    }
#endif

    // check if all mandatory parameters were set
    if (!pParams->InputFiles.size() && !pParams->isV4L2InputEnabled)
    {
        PrintHelp(strInput[0], MSDK_STRING("Source file name not found"));
        return MFX_ERR_UNSUPPORTED;
    };


    if (0 == pParams->nWidth || 0 == pParams->nHeight)
    {
        PrintHelp(strInput[0], MSDK_STRING("-w, -h must be specified"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (MFX_CODEC_MPEG2 != pParams->CodecId &&
        MFX_CODEC_AVC != pParams->CodecId &&
        MFX_CODEC_JPEG != pParams->CodecId &&
        MFX_CODEC_HEVC != pParams->CodecId)
    {
        PrintHelp(strInput[0], MSDK_STRING("Unknown codec"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (MFX_CODEC_JPEG != pParams->CodecId &&
        pParams->FileInputFourCC == MFX_FOURCC_YUY2 &&
        !pParams->isV4L2InputEnabled)
    {
        PrintHelp(strInput[0], MSDK_STRING("-yuy2 option is supported only for JPEG encoder"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (MFX_CODEC_HEVC != pParams->CodecId && (pParams->EncodeFourCC == MFX_FOURCC_P010) )
    {
        PrintHelp(strInput[0], MSDK_STRING("P010 surfaces are supported only for HEVC encoder"));
        return MFX_ERR_UNSUPPORTED;
    }

    // check parameters validity
    if (pParams->nRotationAngle != 0 && pParams->nRotationAngle != 180)
    {
        PrintHelp(strInput[0], MSDK_STRING("Angles other than 180 degrees are not supported."));
        return MFX_ERR_UNSUPPORTED; // other than 180 are not supported
    }

    if (pParams->nQuality && (MFX_CODEC_JPEG != pParams->CodecId))
    {
        PrintHelp(strInput[0], MSDK_STRING("-q option is supported only for JPEG encoder"));
        return MFX_ERR_UNSUPPORTED;
    }

    if ((pParams->nTargetUsage || pParams->nBitRate) && (MFX_CODEC_JPEG == pParams->CodecId))
    {
        PrintHelp(strInput[0], MSDK_STRING("-u and -b options are supported only for H.264, MPEG2 and MVC encoders. For JPEG encoder use -q"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (!pParams->nQuality && (MFX_CODEC_JPEG == pParams->CodecId))
    {
        PrintHelp(strInput[0], MSDK_STRING("-q must be specified for JPEG encoder"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (MFX_TRANSFERMATRIX_UNKNOWN != pParams->TransferMatrix &&
        MFX_TRANSFERMATRIX_BT601 != pParams->TransferMatrix &&
        MFX_TRANSFERMATRIX_BT709 != pParams->TransferMatrix)
    {
        PrintHelp(strInput[0], MSDK_STRING("Invalid transfer matrix type"));
        return MFX_ERR_UNSUPPORTED;
    }

    // set default values for optional parameters that were not set or were set incorrectly
    mfxU32 nviews = (mfxU32)pParams->InputFiles.size();
    if ((nviews <= 1) || (nviews > 2))
    {
        if (!(MVC_ENABLED & pParams->MVC_flags))
        {
            pParams->numViews = 1;
        }
        else
        {
            PrintHelp(strInput[0], MSDK_STRING("Only 2 views are supported right now in this sample."));
            return MFX_ERR_UNSUPPORTED;
        }
    }
    else
    {
        pParams->numViews = nviews;
    }

    if (MFX_TARGETUSAGE_BEST_QUALITY != pParams->nTargetUsage && MFX_TARGETUSAGE_BEST_SPEED != pParams->nTargetUsage)
    {
        pParams->nTargetUsage = MFX_TARGETUSAGE_BALANCED;
    }

    if (pParams->dFrameRate <= 0)
    {
        pParams->dFrameRate = 30;
    }

    // if no destination picture width or height wasn't specified set it to the source picture size
    if (pParams->nDstWidth == 0)
    {
        pParams->nDstWidth = pParams->nWidth;
    }

    if (pParams->nDstHeight == 0)
    {
        pParams->nDstHeight = pParams->nHeight;
    }

    // calculate default bitrate based on the resolution (a parameter for encoder, so Dst resolution is used)
    if (pParams->nBitRate == 0)
    {
        pParams->nBitRate = CalculateDefaultBitrate(pParams->CodecId, pParams->nTargetUsage, pParams->nDstWidth,
            pParams->nDstHeight, pParams->dFrameRate);
    }

    if (!pParams->nPicStruct)
    {
        pParams->nPicStruct = MFX_PICSTRUCT_PROGRESSIVE;
    }

    if ((pParams->nRateControlMethod == MFX_RATECONTROL_LA) && (!pParams->bUseHWLib))
    {
        PrintHelp(strInput[0], MSDK_STRING("Look ahead BRC is supported only with -hw option!"));
        return MFX_ERR_UNSUPPORTED;
    }

    if ((pParams->nMaxSliceSize) && (!pParams->bUseHWLib))
    {
        PrintHelp(strInput[0], MSDK_STRING("MaxSliceSize option is supported only with -hw option!"));
        return MFX_ERR_UNSUPPORTED;
    }

    if ((pParams->nMaxSliceSize) && (pParams->nNumSlice))
    {
        PrintHelp(strInput[0], MSDK_STRING("-mss and -num_slice options are not compatible!"));
        return MFX_ERR_UNSUPPORTED;
    }

    //if ((pParams->nRateControlMethod == MFX_RATECONTROL_LA) && (pParams->CodecId != MFX_CODEC_AVC))
    //{
    //    PrintHelp(strInput[0], MSDK_STRING("Look ahead BRC is supported only with H.264 encoder!"));
    //    return MFX_ERR_UNSUPPORTED;
    //}

    if ((pParams->nMaxSliceSize) && (pParams->CodecId != MFX_CODEC_AVC))
    {
        PrintHelp(strInput[0], MSDK_STRING("MaxSliceSize option is supported only with H.264 encoder!"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (pParams->nLADepth && (pParams->nLADepth < 10 || pParams->nLADepth > 100))
    {
        if ((pParams->nLADepth != 1) || (!pParams->nMaxSliceSize))
        {
            PrintHelp(strInput[0], MSDK_STRING("Unsupported value of -lad parameter, must be in range [10, 100] or 1 in case of -mss option!"));
            return MFX_ERR_UNSUPPORTED;
        }
    }

    // not all options are supported if rotate plugin is enabled
    if (pParams->nRotationAngle == 180 && (
        MFX_PICSTRUCT_PROGRESSIVE != pParams->nPicStruct ||
        pParams->nDstWidth != pParams->nWidth ||
        pParams->nDstHeight != pParams->nHeight ||
        MVC_ENABLED & pParams->MVC_flags ||
        pParams->nRateControlMethod == MFX_RATECONTROL_LA))
    {
        PrintHelp(strInput[0], MSDK_STRING("Some of the command line options are not supported with rotation plugin!"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (pParams->nAsyncDepth == 0)
    {
        pParams->nAsyncDepth = 4; //set by default;
    }

    // Ignoring user-defined Async Depth for LA
    if (pParams->nMaxSliceSize)
    {
        pParams->nAsyncDepth = 1;
    }

    if (pParams->nRateControlMethod == 0)
    {
        pParams->nRateControlMethod = MFX_RATECONTROL_CBR;
    }

    if(pParams->UseRegionEncode)
    {
        if(pParams->CodecId != MFX_CODEC_HEVC)
        {
            msdk_printf(MSDK_STRING("Region encode option is compatible with h265(HEVC) encoder only.\nRegion encoding is disabled\n"));
            pParams->UseRegionEncode=false;
        }
        if (pParams->nWidth  != pParams->nDstWidth ||
            pParams->nHeight != pParams->nDstHeight ||
            pParams->nRotationAngle!=0)
        {
            msdk_printf(MSDK_STRING("Region encode option is not compatible with VPP processing and rotation plugin.\nRegion encoding is disabled\n"));
            pParams->UseRegionEncode=false;
        }
    }

    if (pParams->dstFileBuff.size() == 0)
    {
        msdk_printf(MSDK_STRING("File output is disabled as -o option isn't specified\n"));
    }

    return MFX_ERR_NONE;
}







//
extern  "C"  int  __declspec(  dllexport  )qdcInitCompressVideo(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{	
	int						iErr	=	-1;
	//QDC_OBJ_INFO		&	qdcObjInfo  =  *(  QDC_OBJ_INFO  *  )pQdcObjInfo;
	QDC_OBJ_trans		*	pObj	=	NULL;	

	//  2012/09/01
	//
	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;

	//
	if  (  tmpEnc_setFuncs(  pQdcObjInfo  )  )  {
		tmp_showInfo(  _T(  "qdcInitEncV: tmpEnc_setFuncs failed"  )  );
		return  -1;
	}

	//
	VIDEO_COMPRESSOR_cfgCommon	*	pCompressor	=	(  VIDEO_COMPRESSOR_cfgCommon  *  )pVideoCompressorCfg_reserved;

	//
	memcpy(  &pQdcObjInfo->cfg.v,  pCompressor,  sizeof(  pQdcObjInfo->cfg.v  )  );

	//
	//  sInputParams        Params  =  {};   // input parameters from command line


	//  memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_trans  *  )malloc(  sizeof(  QDC_OBJ_trans  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	pQdcObjInfo->var.pObj  =  pObj;
	
	//
	pQdcObjInfo->var.ucbTransformFuncsOk  =  bTransformFuncsOk(  pQdcObjInfo  );
	if  (  !pQdcObjInfo->var.ucbTransformFuncsOk  )  {
		#ifdef  _DEBUG
				OutputDebugString(  _T(  "initCompressV failed, bTransformFuncs false\n"  )  );
		#endif
		goto  errLabel;
	}

	//  2015/10/11
	pObj->p_init_params  =  new  sInputParams();
	if  (  !pObj->p_init_params  )  goto  errLabel;

	//  2015/10/11
	sInputParams  &Params  =  *(  sInputParams  *  )pObj->p_init_params;
	{
		sInputParams  tmp_inputParams  =  {};
		Params  =  tmp_inputParams;
	}

	//  
#ifdef  _DEBUG
	    //Params.InputFiles.push_back(msdk_string(_T(  "kk"  )));        
#endif

	//
	int  iTargetUsage  =  DEFAULT_iTargetUsage;
	switch  (  pCompressor->iTargetUsage  )  {  
		case  CONST_iTargetUsage_bestQuality:
		case	CONST_iTargetUsage_balanced:
		case	CONST_iTargetUsage_bestSpeed:
			iTargetUsage  =  pCompressor->iTargetUsage;
			break;
		default:
			break;
	}

	mfxU16  nTargetUsage  =  0;
	switch  (  iTargetUsage  )  {
		case  CONST_iTargetUsage_bestQuality:
			  nTargetUsage  =  MFX_TARGETUSAGE_BEST_QUALITY;
			  break;
		case  CONST_iTargetUsage_balanced:
			  nTargetUsage  =  MFX_TARGETUSAGE_BALANCED; 
			  break;
		case  CONST_iTargetUsage_bestSpeed:
			  nTargetUsage  =  MFX_TARGETUSAGE_BEST_SPEED;
			  break;
		default:
			goto  errLabel;
			break;

	}

	//
	//  Îª0Ê±,ÓÉParseInputStringÀï×Ô¶¯ÉèÖÃ
	int  nBitRate  =  myGetBitrate(  pCompressor,  pVh_decompress->bih.biWidth,  pVh_decompress->bih.biHeight  )  /  1024;
	int  policy_bitrate  =  pCompressor->iAvgBitrate  /  1024;
	if  (  policy_bitrate  )  {
		if  (  pCompressor->iWidth_pic  <=  pVh_decompress->bih.biWidth  
			&&  pCompressor->iHeight_pic  <=  pVh_decompress->bih.biHeight  
			&&  pCompressor->usMaxFps_toShareBmp  >=  15  )
		{
			nBitRate  =  policy_bitrate;
		}
	}


	//
	mfxStatus sts = MFX_ERR_NONE; // return value check



	//
	TCHAR	argv0[32]  =  _T(  "encode"  );
	TCHAR	argv_fourccStr[32]  =  _T(  "h264"  );
	TCHAR	argv2[32]  =  _T(  "-i"  );
	TCHAR	argv3[32]  =  _T(  "tmp.yuv"  );
	TCHAR	argv4[32]  =  _T(  "-o"  );
	TCHAR	argv5[32]  =  _T(  "o.264"  );
	TCHAR	argv6[32]  =  _T(  "-w"  );
	TCHAR	argv_w[32]  =  _T(  "320"  );
	TCHAR	argv8[32]  =  _T(  "-h"  );
	TCHAR	argv_h[32]  =  _T(  "240"  );
	TCHAR	argv10[32]	=	_T(  "-f"  );
	TCHAR	argv_f[32]	=	_T(  "30"  );
	TCHAR	argv12[32]	=	_T(  "-b"  );
	TCHAR	argv_kbps[32]	=	_T(  "0"  );
	TCHAR	argv14[32]	=	_T(  "-dstw"  );
	TCHAR	argv_dstw[32]  =  _T(  "320"  );
	TCHAR	argv16[32]	=	_T(  "-dsth"  );
	TCHAR	argv_dsth[32]  =  _T(  "240"  );
	TCHAR	argv17[32]  =  _T(  "-async"  );	//  2015/10/04
	TCHAR	argv18[32]  =  _T(  "1"  );	//  2015/10/04

	//  2017/10/08
	int  iFourcc_enc  =  fourccStr2i(  pCompressor->fourccStr  );
	switch  (  iFourcc_enc  )  {
			case  CONST_fourcc_h264:
				  break;
			case  CONST_fourcc_HEVC:
				  _tcsncpy(  argv_fourccStr,  _T(  "h265"  ),  mycountof(  argv_fourccStr  )  );
				  break;
			default:
					tmp_showInfo(  _T(  "qdcInitCompressVideo: unsupported fourcc"  )  );
					goto  errLabel;
	}

	//
	//  2015/10/30
	unsigned  char  ucbUsing_sharedTex  =  FALSE;
			
	//  2015/09/28
	if  (  pCompressor->usPktResType_suggested  ==  CONST_pktResType_sharedTex  )  {
		mfxVersion  ver;				  
		if  (  IsSupported_hwAcclD11(  &ver  )					
			&&  IsSupported_sharedTex_msdk(  &ver  )  )  				   
		{
			ucbUsing_sharedTex  =  TRUE;			
		}
	}
#ifdef  _DEBUG
		#if  0
			 ucbUsing_sharedTex  =  FALSE;
			 tmp_showInfo(  _T(  "TEST: encV: ucbUsing_sharedTex is set to false"  )  );
		#endif
#endif
	
	//
	TCHAR	argv_d3d[32]	=	_T(  "-d3d11"  );	//  2014/07/04
	if  (  g_bWin7  )  {
		//TCHAR	argv_d3d[32]	=	_T(  "-d3d"  );	//  2014/07/04
		lstrcpyn(  argv_d3d,  _T(  "-d3d"  ),  mycountof(  argv_d3d  )  );
		tmp_showInfo(  _T(  "g_bWin7 is true: use -d3d"  )  );
	}
	if  (  ucbUsing_sharedTex  )  {
		lstrcpyn(  argv_d3d,  _T(  "-d3d11"  ),  mycountof(  argv_d3d  )  );	//  2014/07/04
	}
	
	//
	_sntprintf(  argv_f,  mycountof(  argv_f  ),	_T(  "%d"  ),  pCompressor->usMaxFps_toShareBmp  );
	_sntprintf(  argv_kbps,  mycountof(  argv_kbps  ),  _T(  "%d"  ),  nBitRate  );
	if  (  !pCompressor->enc.ucbResizable  )  {
		_sntprintf(  argv_w,  mycountof(  argv_w  ),  _T(  "%d"  ),  pVh_decompress->bih.biWidth  );	
		_sntprintf(  argv_h,  mycountof(  argv_h  ),  _T(  "%d"  ),  pVh_decompress->bih.biHeight  );
		}
	else  {
		  _sntprintf(  argv_w,  mycountof(  argv_w  ),  _T(  "%d"  ),  pCompressor->enc.iW_org  );	
		  _sntprintf(  argv_h,  mycountof(  argv_h  ),  _T(  "%d"  ),  pCompressor->enc.iH_org  );
		  _sntprintf(  argv_dstw,  mycountof(  argv_dstw  ),  _T(  "%d"  ),  pVh_decompress->bih.biWidth  );
		  _sntprintf(  argv_dsth,  mycountof(  argv_dsth  ),  _T(  "%d"  ),  pVh_decompress->bih.biHeight  );
	}


	//
#if  0
	Params.dFrameRate  =  pCompressor->usMaxFps_toShareBmp;
	Params.bUseHWLib  =  FALSE;	//  TRUE;		//  FALSE;			//  	
	Params.nBitRate  =  nBitRate;
#endif
	Params.nTargetUsage  =  nTargetUsage;   //  MFX_TARGETUSAGE_BALANCED;	//  MFX_TARGETUSAGE_UNKNOWN;    	//  MFX_TARGETUSAGE_BEST_QUALITY;				//  MFX_TARGETUSAGE_BEST_SPEED;		//  2011/12/18
	
	//
	TCHAR  *  pArgv[30];
	int		tmp_argc  =  0;
	//
	pArgv[tmp_argc]  =  argv0;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv_fourccStr;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv2;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv3;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv4;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv5;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv6;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv_w;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv8;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv_h;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv10;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv_f;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv12;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv_kbps;  tmp_argc  ++  ;
	if  (  pCompressor->enc.ucbResizable  )  {
		pArgv[tmp_argc]  =  argv14;  tmp_argc  ++  ;
		pArgv[tmp_argc]  =  argv_dstw;  tmp_argc  ++  ;
		pArgv[tmp_argc]  =  argv16;  tmp_argc  ++  ;
		pArgv[tmp_argc]  =  argv_dsth;  tmp_argc  ++  ;
	}
	//
	pArgv[tmp_argc]  =  argv17;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv18;  tmp_argc  ++  ;
	//
	pArgv[tmp_argc]  =  argv_d3d;  tmp_argc  ++  ;
	if  (  tmp_argc  >  mycountof(  pArgv  )  )  goto  errLabel;



	try  {
		
	//
	sts = ParseInputString(  pArgv,  tmp_argc,  &Params  );
	if  (  sts  <  0  )  goto  errLabel;
	//  2016/04/16
	Params.nGopRefDist  =  1;
	Params.nNumRefFrame  =  1;

	//  2017/10/07
	if  (  pVh_decompress->bih.biCompression  ==  CONST_fourcc_I420  )  {
		Params.FileInputFourCC  =  MFX_FOURCC_I420;
		}
	else  {
		  Params.FileInputFourCC  =  MFX_FOURCC_YV12;
	}

	//
	{
	
		TCHAR	tBuf[128]  =  _T(  ""  );
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "hdEncV init: %s. bitrate [%dk]. w %d, h %d, fps %d"  ),  argv_fourccStr,  (  int  )Params.nBitRate,  (  int  )Params.nWidth,  (  int  )Params.nHeight,  (  int  )Params.dFrameRate    );
		if  (  pCompressor->enc.ucbResizable  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. dstw %d, dsth %d"  ),  tBuf,  (  int  )Params.nDstWidth,  (  int  )Params.nDstHeight  );
		}
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, targetUsage %d, memType %d"  ),  tBuf,  Params.nTargetUsage,  Params.memType  );
		tmp_showInfo(  tBuf  );		
	}
	//
	CMyUserPipeline  *  pPipeline  =  NULL;
	pPipeline  =  new  CMyUserPipeline;
	if  (  !pPipeline  )  goto  errLabel;
	pObj->pVar  =  pPipeline;

	//
	//  memcpy(  &pPipeline->m_params,  &Params,  sizeof(  pPipeline->m_params  )  );
	//pPipeline->m_params  =  Params;
	pPipeline->m_var.pQdcObjInfo  =  pQdcObjInfo;
	//  2015/10/30
	pPipeline->m_var.ucbUsing_sharedTex  =  ucbUsing_sharedTex;
	if  (  ucbUsing_sharedTex  )  {
		pPipeline->m_var.ucbUsingRender  =  TRUE;
	}

	//
	sts = pPipeline->Init(  &Params);
	if  (  sts  <  0  )  {
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encV: initCompressVideo failed, pipe.init failed, %d"  ),  sts  );
		tmp_showInfo(  tBuf  );
		goto  errLabel;
	}

	//  Ó¦¸Ã°ÑCEncodingPipeline´ÓÀý×ÓÄÇÀï¿½³öÀ´£¬·ñÔòÓÐÐ©²Ù×÷²»ÄÜ°´Ô¤¼ÆÀ´ÐÞ¸Ä¡£ÏóÎÄ¼þ²Ù×÷Ö®Àà£¬Ó¦¸Ã´Ó´úÂëÖÐÈ¥³ý ¡£


	//  qdcObjInfo.
	pQdcObjInfo->var.cbOutputBuffer  =  pVh_decompress->bih.biSizeImage;
	pQdcObjInfo->var.cbInputBuffer  =  pQdcObjInfo->var.cbOutputBuffer;

	//  2012/06/27
	//pObj->ucbFlippedImg  =  pCompressor->ucbOutputFlippedImg;

	//
	memcpy(  pVh_compress,  pVh_decompress,  sizeof(  pVh_compress[0]  )  );
	pVh_compress->bih.biCompression  =  iFourcc_enc;	//  2017/10/08	//  CONST_fourcc_h264;

	//
#if  0
	makeBmpInfoHeader_yv12(  12,  pVh_compress->bih.biWidth,  pVh_compress->bih.biHeight,  &pObj->inputForEnc.vh_decompress_real.bih  );
	pObj->inputForEnc.uiBufSize  =  pObj->inputForEnc.vh_decompress_real.bih.biSizeImage;
	pObj->inputForEnc.pBuf  =  (  char  *  )malloc(  pObj->inputForEnc.uiBufSize  );
	if  (  !pObj->inputForEnc.pBuf  )  goto  errLabel;
#endif

	//	
	if  (  !pObj->common.outs[0].pBuf  )  {
		pObj->common.outs[0].pBuf  =  (  BYTE  *  )malloc(  pQdcObjInfo->var.cbOutputBuffer  );
		if  (  !pObj->common.outs[0].pBuf  )  goto  errLabel;
	}

	}
		catch (std::exception &ex)
    {
#ifdef UNICODE
        wprintf(L"\nstd::exception caught: %S\n", ex.what());    
#else
        printf("\nstd::exception caught: %s\n", ex.what());    
#endif
		tmp_showInfo(  _T(  "qdcInitCompressV: exception caught"  )  );
		goto  errLabel;
		}
    catch (...)
    {
        msdk_printf(MSDK_STRING("\nUnknown exception caught\n"));
		tmp_showInfo(  _T(  "qdcInitComressV:Unknown exception caught"  )  );
		goto  errLabel;
    }


	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		qdcExitCompressVideo(  pQdcObjInfo  );
	}
	if  (  !iErr  )  {
	}
	return  iErr;
}

extern  "C"  int  __declspec(  dllexport  )qdcExitCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	//  2012/09/01
	//
	if  (  !pQdcObjInfo  )  return  -1;

	QDC_OBJ_trans	*	pObj	=	(  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;

	//
	tmp_showInfo(  _T(  "hdEnc::qdcExitCompressVideo enters"  )  );

	//
	if  (  pObj  )  {
		//
		if  (  pObj->pVar  )  {
			CEncodingPipeline  *  pPipeline  =  (  CEncodingPipeline  *  )pObj->pVar;
			//
			tmp_showInfo(  _T(  "hdEnc: to close pipeline"  )  );
			//
			pPipeline->Close(  );
			//
			tmp_showInfo(  _T(  "hdEnc: pipeline closed"  )  );
			//
			delete  pPipeline;
			pObj->pVar  =  NULL;
		}
		//  2015/10/11
		if  (  pObj->p_init_params  )  {
			sInputParams  *  pParams  =  (  sInputParams  *  )pObj->p_init_params;
			delete  pParams;
			pObj->p_init_params  =  NULL;
		}
		//
		qdcFreeOutputs(  pQdcObjInfo  );
		//
#if  0
		if  (  pObj->inputForEnc.pBuf  )  {
			free(  pObj->inputForEnc.pBuf  );  pObj->inputForEnc.pBuf  =  NULL;
		}
#endif
		//
		free(  pObj  );	
	}
	pQdcObjInfo->var.pObj  =  NULL;
	
	//
	tmp_showInfo(  _T(  "hdEnc::qdcExitCompressVideo leaves"  )  );

	return  0;
}

//  2014/03/30
//extern  "C"  __declspec(  dllexport  )  int  qdcGetSpsPps(  QDC_OBJ_INFO  *  pQdcObjInfo,  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize,  char  *  kk,  unsigned  int  *  puiKkSize  )
extern  "C"  __declspec(  dllexport  )  int  qdcGetSpsPps(  QDC_OBJ_INFO  *  pQdcObjInfo,  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize,  char  *  vpsBuf,  unsigned  int  *  puiVpsSize  )
{
	if  (  !pQdcObjInfo->var.pObj  )  return  -1;
	QDC_OBJ_trans	*	pObj	=	(  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;
	if  (  !pObj  )  return  -1;
	CMyUserPipeline  *  pPipeline  =  (  CMyUserPipeline  *  )pObj->pVar;

	//
	int  iFourcc  =  fourccStr2i(  pQdcObjInfo->cfg.v.fourccStr  );
	//
	switch  (  iFourcc  )  {
			case  CONST_fourcc_h264:
				  if  (  pPipeline->MakeSPSPPS(  spsBuf,  puiSpsSize,  ppsBuf,  puiPpsSize  )  )  return  -1;
				  break;
			case  CONST_fourcc_HEVC:
				  //
				  if  (  pPipeline->MakeVPS(  vpsBuf,  puiVpsSize  )  )  return  -1;
				  //
				  if  (  pPipeline->MakeSPSPPS(  spsBuf,  puiSpsSize,  ppsBuf,  puiPpsSize  )  )  return  -1;				  
				  break;
			default:
					tmp_showInfo(  _T(  "qdcGetSpsPps failed,  unprocessed fourcc"  )  );
				    return  -1;
					break;
	}



	return  0;
}


int  qdcFindOutputIndex(  void  *  pQdcObjInfoParam  )
{
	if  (  !pQdcObjInfoParam  )  return  -1;

	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pQdcObjInfoParam;
	QDC_OBJ_transCommon	*	pObj	=	(  QDC_OBJ_transCommon  *  )pQdcObjInfo->var.pObj;
	
#if  0
	if  (  uiOutputSize  >  pQdcObjInfo->cbOutputBuffer  )  {
		OutputDebugString(  _T(  "qdcSetOutput failed: uiOutputSize too big\n"  )  );
		return  -1;
	}
#endif

	int  index  =  0;
	for  (  index  =  0;  index  <  sizeof(  pObj->outs  )  /  sizeof(  pObj->outs[0]  );  index  ++  )  {
		 if  (  !pObj->outs[index].pBuf  )  continue;
		 if  (  !pObj->outs[index].len  )  break;
	}
	if  (  index  ==  sizeof(  pObj->outs  )  /  sizeof(  pObj->outs[0]  )  )  {
		tmp_showInfo(  _T(  "qdcSetOutput failed: no outs[index]"  )  );
		return  -1;
	}
	
#if  0
	memcpy(  pObj->outs[index].pBuf,  pOutput,  uiOutputSize  );
	pObj->outs[index].len  =  uiOutputSize;
#endif
	
	return  index;

}

int  qdcOutput(  void  *  pQdcObjInfoParam,  int  outputIndex,  char  *  pOutput,  unsigned  int  uiOutputSize  )
{
	if  (  !pQdcObjInfoParam  )  return  -1;

	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pQdcObjInfoParam;
	QDC_OBJ_transCommon	*	pObj	=	(  QDC_OBJ_transCommon  *  )pQdcObjInfo->var.pObj;

	if  (  outputIndex  <  0  ||  outputIndex  >=  sizeof(  pObj->outs  )  /  sizeof(  pObj->outs[0]  )  )  return  -1;
	if  (  !pObj->outs[outputIndex].pBuf  )  {
		TCHAR	tBuf[128]  =  _T(  ""  );
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "qdcOutput failed, [%d].pBuf is null"  ),  outputIndex  );
		tmp_showInfo(  tBuf  );		
		return  -1;
	}

	if  (  uiOutputSize  >  pQdcObjInfo->var.cbOutputBuffer  -  pObj->outs[outputIndex].len  )  {
		OutputDebugString(  _T(  "qdcSetOutput failed: uiOutputSize too big\n"  )  );
		return  -1;
	}

	memcpy(  pObj->outs[outputIndex].pBuf  +  pObj->outs[outputIndex].len,  pOutput,  uiOutputSize  );
	pObj->outs[outputIndex].len  +=  uiOutputSize;

	return  0;

}



extern  "C"  int  __declspec(  dllexport  )qdcCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput  )
{
	//  2012/09/01
#if  0
	if  (  g_bUsePipeline_videoconf  )  return  qdcCompressVideo_videoconf(  pQdcObjInfo,  pBmpInfo_input,  pInput  );
#endif

	//
	if  (  !pQdcObjInfo  )  return  -1;

	QDC_OBJ_trans	*	pObj	=	(  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;

	//
	if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pQdcObjInfo->var.cbInputBuffer  )  return  -1;

	//

#if  0

#if  0
	rgb24ToYv12(  pInput,  (  unsigned  char  *  )pObj->inputForEnc.pBuf,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight,  TRUE  );
#else
	rgb24ToYv12_ipp(  pInput,  (  unsigned  char  *  )pObj->inputForEnc.pBuf,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight,  TRUE  );
#endif


	CMyUserPipeline  *  pPipeline  =  (  CMyUserPipeline  *  )pObj->pPipeline;

	//  pPipeline->compressVideo(  pQdcObjInfo,  pBmpInfo_input,  pInput  );
	pPipeline->compressVideo(  pQdcObjInfo,  (  BITMAPINFO  *  )&pObj->inputForEnc.vh_decompress_real,  (  BYTE  *  )pObj->inputForEnc.pBuf  );
#else

	CMyUserPipeline  *  pPipeline  =  (  CMyUserPipeline  *  )pObj->pVar;

#if  0
	if  (  pBmpInfo_input->bmiHeader.biCompression  ==  CONST_fourcc_YV12  )  {

		//  pPipeline->compressVideo(  pQdcObjInfo,  pBmpInfo_input,  pInput  );
		pPipeline->compressVideo(  pQdcObjInfo,  pBmpInfo_input,  (  BYTE  *  )pInput  );
		}
	else  if  (  pBmpInfo_input->bmiHeader.biCompression  ==  BI_RGB
		&&  pBmpInfo_input->bmiHeader.biBitCount  ==  24  )
	{
		//  tmp_showInfo(  _T(  "mediaSdk: biCompression is RGB ,biBitCount is 24"  )  );
		if  (  pObj->ucbFlippedImg  )  {
			//  rgb24ToYv12_ipp(  pInput,  (  unsigned  char  *  )pObj->inputForEnc.pBuf,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight,  TRUE  );
			rgb24ToYv12(  pInput,  (  unsigned  char  *  )pObj->inputForEnc.pBuf,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight,  TRUE  );
		    }
		else  {
			  rgb24ToYv12(  pInput,  (  unsigned  char  *  )pObj->inputForEnc.pBuf,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight,  FALSE  );
		}

		//
		pPipeline->compressVideo(  pQdcObjInfo,  (  BITMAPINFO  *  )&pObj->inputForEnc.vh_decompress_real.bih,  (  BYTE  *  )pObj->inputForEnc.pBuf  );
		}
	else  {
		  OutputDebugString(  _T(  "compressVideo: input fmt err\n"  )  );
		  tmp_showInfo(  _T(  "compressVideo: input fmt err\n"  )  );
		  return  -1;
	}
#endif

#endif

#if  0
	int  index  =  0;
	memcpy(  pObj->outs[index].pBuf,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );
	pObj->outs[index].len  =  pBmpInfo_input->bmiHeader.biSizeImage;
#endif

	return  0;
}


extern  "C"  int  __declspec(  dllexport  )  qdcCompressVideoRun(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int					iErr	=	-1;
	QDC_OBJ_trans	*	pObj	=	(  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;
	TCHAR				tBuf[256]	=	_T(  ""  );
	mfxStatus sts = MFX_ERR_NONE; // return value check

	CMyUserPipeline  *  pPipeline  =  (  CMyUserPipeline  *  )pObj->pVar;
	
	if  (  !pPipeline  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qdcCompressVideoRun failed, encVPipeline is null"  )  );
		tmp_showInfo(  tBuf  );
		return  -1;
	}
	
	//  2014/07/01	
	if  (  pPipeline->m_var.bFailed  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encVPipeline->bFailed ture, sts %d"  ),  pPipeline->m_var.sts_failed  );
		tmp_showInfo(  tBuf  );
		return  -1;		
	}


	//  2015/10/11
	//for  (  ;  ;  )  
	{

		 if  (  pQdcObjInfo->cfg.v.pf_bTransformVideoQuit(  pQdcObjInfo->cfg.v.pParent_transform,  0,  0  )  )  {
			 tmp_showInfo(  _T(  "qdcCompressVideoRun failed, bQuit true"  )  );
			 goto  errLabel;
		 }

		//
		sts  =  pPipeline->Run(  );

		//  2014/05/28
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encVPipeline->Run returns sts %d"  ),  sts  );
		tmp_showInfo(  tBuf  );
		//  2016/03/31
		goto  errLabel;
		
		
#if  0
		//
		if  (  pQdcObjInfo->cfg.pf_bTransformVideoQuit(  pQdcObjInfo->cfg.pParent_transform,  0,  0  )  )  {
			 tmp_showInfo(  _T(  "qdcCompressVideoRun failed, bQuit true"  )  );
			 goto  errLabel;		 
		}

		//
		if  (  pObj->pPipeline  )  {
			CEncodingPipeline  *  pPipeline  =  (  CEncodingPipeline  *  )pObj->pPipeline;
			//
			tmp_showInfo(  _T(  "hdEnc_run: to close pipeline"  )  );
			//
			pPipeline->Close(  );
			//
			tmp_showInfo(  _T(  "hdEnc_run: pipeline closed"  )  );
			//
			delete  pPipeline;
			pObj->pPipeline  =  NULL;
		}
		//
		{
			CMyUserPipeline  *  pPipeline  =  NULL;
			pPipeline  =  new  CMyUserPipeline;
			if  (  !pPipeline  )  goto  errLabel;
			pObj->pPipeline  =  pPipeline;
			
			//
			//  memcpy(  &pPipeline->m_params,  &Params,  sizeof(  pPipeline->m_params  )  );
			//pPipeline->m_params  =  Params;
			pPipeline->m_var.pQdcObjInfo  =  pQdcObjInfo;
			
			//
			sInputParams  &Params  =  *(  sInputParams  *  )pObj->p_init_params;
			
			//
			sts = pPipeline->Init(  &Params);
			if  (  sts  <  0  )  goto  errLabel;
		}

		//
		continue;
#endif

	}

	iErr  =  0;

errLabel:
	
	//  2014/07/01	
	pPipeline->m_var.bFailed  =  TRUE;
	pPipeline->m_var.sts_failed  =  sts;


	return  iErr;
}


extern  "C"  int  __declspec(  dllexport  )qdcGetOutputByIndex(  QDC_OBJ_INFO  *  pQdcObjInfo,  int  index,  BYTE *  pbOutData,  unsigned  int  *  puiDataSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  pui_rtTimeLen  )
{
	TCHAR					tBuf[128]	=	_T(  ""  );
	QDC_OBJ_transCommon	*	pObj	=	(  QDC_OBJ_transCommon  *  )pQdcObjInfo->var.pObj;

	if  (  index  <  0  ||  index  >=  sizeof(  pObj->outs  )  /  sizeof(  pObj->outs[0]  )  )  return  -1;
	//

	if  (  *puiDataSize  <  pObj->outs[index].len  )  {
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "m.qdcGetOutputByIndex failed: buf too small:puiDataSize:%d, outs[%d].len:%d"  ),  *puiDataSize,  index,  pObj->outs[index].len  );
		tmp_showInfo(  tBuf  );
		return  CONST_qdcRet_bufTooSmall;
	}

	if  (  !pObj->outs[index].len  )  return  -1;	

	*puiDataSize  =  pObj->outs[index].len;

	memcpy(  pbOutData,  pObj->outs[index].pBuf,  pObj->outs[index].len  );

	if  (  puiSampleTimeInMs  )  {
		*puiSampleTimeInMs  =  (  unsigned  int  )(  pObj->outs[index].rtStart  /  (  10  *  1000  )  );
		if  (  (  (  int  )*puiSampleTimeInMs  )  <  0  )  {
			*puiSampleTimeInMs  =  0;
		}
	}
	if  (  pui_rtTimeLen  )  {
		*pui_rtTimeLen  =  (  unsigned  int  )pObj->outs[index].rtTimeLen;
	}

	pObj->outs[index].len  =  0;

	return  0;
}


extern  "C"  int  __declspec(  dllexport  )qdcClearOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int		i;
	QDC_OBJ_transCommon	*	pObj	=	(  QDC_OBJ_transCommon  *  )pQdcObjInfo->var.pObj;

	tmp_showInfo(  _T(  "qdcClearOutputs"  )  );
	
	for  (  i  =  0;  i  <  sizeof(  pObj->outs  )  /  sizeof(  pObj->outs[0]  );  i  ++  )  {
		 pObj->outs[i].len  =  0;
	}

	return  0;
}
