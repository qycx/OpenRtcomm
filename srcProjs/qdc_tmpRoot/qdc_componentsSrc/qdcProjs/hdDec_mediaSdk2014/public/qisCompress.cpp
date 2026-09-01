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
#include	"myutils.h"
#include	"tmpDecOpenFunc.h"

//
#define	CONST_ver_qisCompress		"02660251"	//  2017/10/07	//  "02650115"		//  2016/12/14，"02630336"		//  2016/04/19. "02630318"	//  2016/04/10,"02630294"		//  2015/11/03,"02630243"		//  2015/11/02,"02630239"			//  2015/10/24,"02630234"	//  2015/10/18	//  "02622836"	//  2015/01/11,  2012/08/24		//  2012/06/23


//
//
BOOL				g_bUsing_sharedTex_dec  =  FALSE;
//
BOOL				g_bShowDec_sharedTexStatus	=	FALSE;			//  2016/04/09
//
unsigned  int		g_uiXql_player				=	0;				//  2016/04/14




#if  0
int  yuy2ToRgb24_ipp(  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );
int  rgb24ToYv12_ipp(  unsigned  char  *  rgb,  unsigned  char  *  yuv,  int  width,  int  height,  BOOL  bFlip  );
#endif



//  



//  2011/09/25
void PrintHelp(TCHAR *strAppName, TCHAR *strErrorMessage)
{
}




//  2012/09/04
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
	g_iDebugStepType  =  CONST_debugStepType_dec;
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

	//  2016/04/27
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
		g_bUsing_sharedTex_dec  =  ucbUsing_sharedTex;
	}


	//  2012/05/26
	//  tmp_showInfo(  _T(  "qdcInit called. v025127"  )  );
	TCHAR	tBuf[128];
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "qdcInit called. hdDec_mediasdk,%s"  ),  _T(  CONST_ver_qisCompress  )  );
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s. %s"  ),  tBuf,  p->ucbNotSupported_hw  ?  _T(  "hwAccl not supported"  )  :  _T(  "OK"  )  );
	//  _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s. bUsePipeline %d, ucbNotSupported_dec_h264 %d"  ),  tBuf,  g_bUsePipeline_videoconf,  p->ucbNotSupported_dec_h264  );
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
  //  2015/10/20
 extern  "C"  int  __declspec(  dllexport  )qdcGetProp(  int  iPropId,  void  *  pParam_input,  void  *  pParam_output  )
 {
	 int  iErr  =  -1;
	 TCHAR  tBuf[128]  =  _T(  ""  );

	 //
	 if  (  !pParam_output  )  return  -1;

	 //
#if  0
	 switch  (  iPropId  )  {
			 case  CONST_qdcPropId_bSupport_sharedTex_dec:  
				 {
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
			 case  CONST_qdcPropId_bShowDec_sharedTexStatus:  {
				   BOOL  *  pbVal  =  (  BOOL  *  )pParam_output;
				   
				   //
				   *pbVal  =  g_bShowDec_sharedTexStatus;
				   }
				   break;
			 case  CONST_qdcPropId_uiXql_player:  {  //  2016/04/14
				   unsigned  int  *  puiXql_player  =  (  unsigned  int  *  )pParam_output;
				   //
				   *puiXql_player  =  g_uiXql_player;
				   }
				   break;

			 default:
				    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qdcGetProp failed, unprocessed propId %d"  ),  iPropId  );
					tmp_showInfo(  tBuf  );
					goto  errLabel;
	 }
#endif
	 //
	 switch  (  iPropId  )  {
			 case  CONST_qdcPropId_bSupport_sharedTex_dec:  
			 default:
				    if  (  tmpDec_qdcGetProp(  iPropId,  pParam_input,  pParam_output  )  )  {
						goto  errLabel;
					}
					break;

	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
 }


 //  2016/04/09
 extern  "C"  int  __declspec(  dllexport  )qdcSetProp(  int  iPropId,  void  *  pParam_input,  void  *  pParam_output  )
 {
	 int  iErr  =  -1;

	 //
	 if  (  !pParam_input  )  return  -1;

	 //
#if  0
	 switch  (  iPropId  )  {
			 case  CONST_qdcPropId_bShowDec_sharedTexStatus:  {
				   BOOL  *  pbVal  =  (  BOOL  *  )pParam_input;
				   
				   //
				   g_bShowDec_sharedTexStatus  =  *pbVal;

				   //
				   }
				   //
				   break;
			 case  CONST_qdcPropId_uiXql_player:  {
				   unsigned  int  *puiXql_player  =  (  unsigned  int  *  )pParam_input;
				   //
				   g_uiXql_player  =  *puiXql_player;
				   //
				   }
				   break;
			 default:
				    tmp_showInfo(  _T(  "qdcSetProp failed, unprocessed propId"  )  );
					goto  errLabel;
	 }
#endif
	 //
	 switch  (  iPropId  )  {
			 case  CONST_qdcPropId_bShowDec_sharedTexStatus:
			 default:
				     if  (  tmpDec_qdcSetProp(  iPropId,  pParam_input,  pParam_output  )  )  {
						 goto  errLabel;
					 }
				     break;
	 }


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


#if  0
mfxStatus ParseInputString(  sInputParams* pParams)
{
    TCHAR* strArgument = _T("");    


    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);
    //  ZERO_MEMORY(*pParams);


#if  0

    // parse command line parameters
    for (mfxU8 i = 1; i < nArgNum; i++)
    {
        CHECK_POINTER(strInput[i], MFX_ERR_NULL_PTR);

        if (_T('-') != strInput[i][0])
        {
            if (0 == _tcscmp(strInput[i], _T("h264")))
            {
                pParams->CodecId = MFX_CODEC_AVC;
            }
            else if (0 == _tcscmp(strInput[i], _T("mpeg2")))
            {
                pParams->CodecId = MFX_CODEC_MPEG2;
            }
            else
            {
                PrintHelp(strInput[0], _T("Unknown codec"));
                return MFX_ERR_UNSUPPORTED;
            }
            continue;
        }

        // process multi-character options
        if (0 == _tcscmp(strInput[i], _T("-dstw")))
        {
            i++;
            _stscanf_s(strInput[i], _T("%hd"), &pParams->nDstWidth);            
        }
        else if (0 == _tcscmp(strInput[i], _T("-dsth")))
        {
            i++;
            _stscanf_s(strInput[i], _T("%hd"), &pParams->nDstHeight);
        }
        else if (0 == _tcscmp(strInput[i], _T("-hw")))
        {
            pParams->bUseHWLib = true;
        }
        else if (0 == _tcscmp(strInput[i], _T("-nv12")))
        {
            pParams->ColorFormat = MFX_FOURCC_NV12;
        }
        else if (0 == _tcscmp(strInput[i], _T("-tff")))
        {
            pParams->nPicStruct = MFX_PICSTRUCT_FIELD_TFF;
        }
        else if (0 == _tcscmp(strInput[i], _T("-bff")))
        {
            pParams->nPicStruct = MFX_PICSTRUCT_FIELD_BFF;
        }
        else if (0 == _tcscmp(strInput[i], _T("-angle")))
        {
            i++;
            _stscanf_s(strInput[i], _T("%hd"), &pParams->nRotationAngle);            
        }
#ifdef D3D_SURFACES_SUPPORT
        else if (0 == _tcscmp(strInput[i], _T("-d3d")))
        {
            pParams->bd3dAlloc = true;
        }
#endif
        else // 1-character options
        {
            switch (strInput[i][1])
            {
            case _T('u'):
                GET_OPTION_POINTER(strArgument);
                pParams->nTargetUsage = StrToTargetUsage(strArgument);
                break;
            case _T('w'):
                GET_OPTION_POINTER(strArgument);
                _stscanf_s(strArgument, _T("%hd"), &pParams->nWidth);
                break;
            case _T('h'):
                GET_OPTION_POINTER(strArgument);
                _stscanf_s(strArgument, _T("%hd"), &pParams->nHeight);
                break;
            case _T('f'):
                GET_OPTION_POINTER(strArgument);
                _stscanf_s(strArgument, _T("%lf"), &pParams->dFrameRate);
                break;
            case _T('b'):
                GET_OPTION_POINTER(strArgument);
                _stscanf_s(strArgument, _T("%hd"), &pParams->nBitRate);
                break;
            case _T('t'):
                GET_OPTION_POINTER(strArgument);
                _stscanf_s(strArgument, _T("%hd"), &pParams->nThreads);
                break;
            case _T('i'):
                GET_OPTION_POINTER(strArgument);
                _tcscpy_s(pParams->strSrcFile, strArgument);
                break;
            case _T('o'):
                GET_OPTION_POINTER(strArgument);
                _tcscpy_s(pParams->strDstFile, strArgument);
                break;
            case _T('?'):
                PrintHelp(strInput[0], NULL);
                return MFX_ERR_UNSUPPORTED;
            default:
                PrintHelp(strInput[0], _T("Unknown options"));
            }
        }
    }

#endif
	
	pParams->CodecId = MFX_CODEC_AVC;
#if  0	//  ÔÚinitFileWriteÀï,ÐèÒªÊ¹ÓÃdstFileBuff[0].ËùÒÔÕâÀïËæ±ãÌî¸ö¼ÙÊý
	_sntprintf(  pParams->strSrcFile,  sizeof(  pParams->strSrcFile  )  /  sizeof(  pParams->strSrcFile[0]  ),  _T(  "c:\\temp\\my.yuv"  )  );
	_sntprintf(  pParams->dstFileBuffstrDstFile,  sizeof(  pParams->strDstFile  )  /  sizeof(  pParams->strDstFile[0]  ),  _T(  "c:\\temp\\test.264"  )  );
#endif

	//
	//  pParams->dstFileBuff.push_back(  _T(  "c:\\temp\\test.264"  )  );

#if  0
	pParams->nWidth  =  1360;
	pParams->nHeight  =  768;
#endif
 

#if  0
    // check if all mandatory parameters were set
    if (0 == _tcslen(pParams->strSrcFile))
    {
        //  PrintHelp(strInput[0], _T("Source file name not found"));
        return MFX_ERR_UNSUPPORTED;
    };

    if (0 == _tcslen(pParams->strDstFile))
    {
        //  PrintHelp(strInput[0], _T("Destination file name not found"));
        return MFX_ERR_UNSUPPORTED;
    };
#endif

    if (0 == pParams->nWidth || 0 == pParams->nHeight)
    {
        //  PrintHelp(strInput[0], _T("-w, -h must be specified"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (MFX_CODEC_MPEG2 != pParams->CodecId && MFX_CODEC_AVC != pParams->CodecId)
    {
        //  PrintHelp(strInput[0], _T("Unknown codec"));
        return MFX_ERR_UNSUPPORTED;
    }

	//  2012/08/24
	// set default values for optional parameters that were not set or were set incorrectly
    mfxU32 nviews = 0;	//  (mfxU32)pParams->srcFileBuff.size();
    if ((nviews <= 1) || (nviews > 2))
    {
        if (!(MVC_ENABLED & pParams->MVC_flags))
        {
            pParams->numViews = 1;
        }
        else
        {
            //  PrintHelp(strInput[0], MSDK_STRING("Only 2 views are supported right now in this sample."));
            return MFX_ERR_UNSUPPORTED;
        }
    }
    else
    {
        pParams->numViews = nviews;
    }

    // set default values for optional parameters that were not set or were set incorrectly
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

		//  2012/09/02, ¶Ô·ÇÖ¸¶¨ÂëÁ÷µÄÇé¿ö, Èç¹û²»ÊÇÆ·ÖÊÓÅÏÈµÄ»°,¾ÍÓÃ80%µÄÂëÁ÷.
		if  (  pParams->nTargetUsage  !=  MFX_TARGETUSAGE_BEST_QUALITY  )  {
			pParams->nBitRate  *=  0.8;
		}	
	}

    // if nv12 option wasn't specified we expect input YUV file in YUV420 color format
    if (!pParams->ColorFormat)
    {
        pParams->ColorFormat = MFX_FOURCC_YV12;
    }

    if (!pParams->nPicStruct)
    {
        pParams->nPicStruct = MFX_PICSTRUCT_PROGRESSIVE;
    }

    if (pParams->nRotationAngle != 0 && pParams->nRotationAngle != 180)
    {
        //  PrintHelp(strInput[0], _T("Angles other than 180 degrees are not supported."));
        return MFX_ERR_UNSUPPORTED; // other than 180 are not supported 
    }  

    // not all options are supported if rotate plugin is enabled
#if  0  //  2012/08/24
    if (pParams->nRotationAngle == 180) 
    {
        if (MFX_FOURCC_NV12 != pParams->ColorFormat)
        {
            //  PrintHelp(strInput[0], _T("Rotation plugin requires NV12 input. Please specify -nv12 option."));
            return MFX_ERR_UNSUPPORTED;
        }
        pParams->nPicStruct = MFX_PICSTRUCT_PROGRESSIVE;        
        pParams->nDstWidth = pParams->nWidth;
        pParams->nDstHeight = pParams->nHeight;       
        pParams->bd3dAlloc = false;        
    }
#endif

	//  2012/08/24
	if (pParams->nRotationAngle == 180 && (
        MFX_PICSTRUCT_PROGRESSIVE != pParams->nPicStruct ||
        pParams->nDstWidth != pParams->nWidth ||
        pParams->nDstHeight != pParams->nHeight ||
        (MVC_ENABLED & pParams->MVC_flags ||
        pParams->memType & D3D11_MEMORY))) 
    {        
       // PrintHelp(strInput[0], MSDK_STRING("Some of the command line options are not supported with rotation plugin."));
        return MFX_ERR_UNSUPPORTED;
    }




    return MFX_ERR_NONE;
}
#endif


extern  "C"  int  __declspec(  dllexport  )qdcInitCompressVideo(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{	
	int						iErr	=	-1;

	//  2012/09/01
	//
	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;

	VIDEO_COMPRESSOR_cfgCommon	*	pCompressor	=	(  VIDEO_COMPRESSOR_cfgCommon  *  )pVideoCompressorCfg_reserved;
	//QDC_OBJ_INFO		&	qdcObjInfo  =  *(  QDC_OBJ_INFO  *  )pQdcObjInfo;
	QDC_OBJ_trans		*	pObj	=	NULL;	

#if  0

	//
	sInputParams        Params;   // input parameters from command line


	//  memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_trans  *  )malloc(  sizeof(  QDC_OBJ_trans  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	pQdcObjInfo->pObj  =  pObj;

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

	mfxU16  nTargetUsage;
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
	mfxStatus sts = MFX_ERR_NONE; // return value check

	memset(  &Params,  0,  sizeof(  Params  )  );
	Params.nWidth  =  (  mfxU16  )pVh_decompress->bih.biWidth;
	Params.nHeight  =  (  mfxU16  )pVh_decompress->bih.biHeight;
	Params.dFrameRate  =  pCompressor->usMaxFps_toShareBmp;
	Params.nTargetUsage  =  nTargetUsage;   //  MFX_TARGETUSAGE_BALANCED;	//  MFX_TARGETUSAGE_UNKNOWN;    	//  MFX_TARGETUSAGE_BEST_QUALITY;				//  MFX_TARGETUSAGE_BEST_SPEED;		//  2011/12/18
	Params.bUseHWLib  =  TRUE;		//  FALSE;			//  


#ifdef  _DEBUG
		#if  0
			Params.bUseHWLib  =  FALSE;
			OutputDebugString(  _T(  "qdcInitCompressVideo: bUseHWlib is set to false for debug\n"  )  );
		#endif
#endif



#if  0

	Params.

	   Params.key_frame_controls.method=1;
   Params.info.clip_info.height=imgHeight;
   Params.info.clip_info.width=imgWidth;
   Params.info.bitrate = 0;
   Params.numThreads = 0;				//  2011/09/04 
   
   // tmp   
   Params.key_frame_controls.interval  =  pVideoCfgCommon->usMaxFps_toShareBmp  *  3;		// 4frame/s;10s¸ú×ÙÊ±¼ä,¾ÍÊÇ40interval;
   Params.key_frame_controls.idr_interval  =  1;
   Params.profile_idc  =  (  UMC::H264_PROFILE_IDC  )pVideoCfgCommon->profile_idc;								//  100 0             // profile_idc (77-main, 100-high); level_idc (set 0 for automatic selection) (check that num_ref_frames and frame size are in accordance with the level)  
   Params.info.framerate  =  pVideoCfgCommon->usMaxFps_toShareBmp;					//  5                 // frame_rate_code [0,8] (0-30 fps,1-15 fps,2-24 fps,3-25 fps,4-30 fps,5-30 fps,6-50 fps,7-60 fps,8-60 fps)
   Params.level_idc  =  13;

   if  (  pVideoCfgCommon->ucbScreenSharing  )  Params.info.bitrate  =  300000;
   else  
   {
	   Params.info.bitrate  =  (((  imgWidth  *  imgHeight  )  *  Params.info.framerate  /  CONST_bp_compression  )  / 10  )  *  10000;
   }

#endif


    //  Îª0Ê±,ÓÉParseInputStringÀï×Ô¶¯ÉèÖÃ
	Params.nBitRate  =  myGetBitrate(  pCompressor,  pVh_decompress->bih.biWidth,  pVh_decompress->bih.biHeight  )  /  1024;

	//
	sts = ParseInputString( &Params);
	if  (  sts  <  0  )  goto  errLabel;

	{
	
		TCHAR	tBuf[128]  =  _T(  ""  );
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "initCompressVideo: bitrate [%dk]. w %d, h %d, fps %d"  ),  (  int  )Params.nBitRate,  (  int  )Params.nWidth,  (  int  )Params.nHeight,  (  int  )Params.dFrameRate    );
		tmp_showInfo(  tBuf  );		
	}
	//
	CMyUserPipeline  *  pPipeline  =  NULL;
	pPipeline  =  new  CMyUserPipeline;
	if  (  !pPipeline  )  goto  errLabel;
	pObj->pPipeline  =  pPipeline;

	//
	//  memcpy(  &pPipeline->m_params,  &Params,  sizeof(  pPipeline->m_params  )  );
	pPipeline->m_params  =  Params;
	pPipeline->m_var.pQdcObjInfo  =  pQdcObjInfo;

	//
	sts = pPipeline->Init(pQdcObjInfo,  &Params);
	if  (  sts  <  0  )  goto  errLabel;

	//  Ó¦¸Ã°ÑCEncodingPipeline´ÓÀý×ÓÄÇÀï¿½³öÀ´£¬·ñÔòÓÐÐ©²Ù×÷²»ÄÜ°´Ô¤¼ÆÀ´ÐÞ¸Ä¡£ÏóÎÄ¼þ²Ù×÷Ö®Àà£¬Ó¦¸Ã´Ó´úÂëÖÐÈ¥³ý ¡£


	//  qdcObjInfo.
	pQdcObjInfo->cbOutputBuffer  =  pVh_decompress->bih.biSizeImage;
	pQdcObjInfo->cbInputBuffer  =  pQdcObjInfo->cbOutputBuffer;

	//  2012/06/27
	pObj->ucbFlippedImg  =  pCompressor->ucbOutputFlippedImg;

	//
	memcpy(  pVh_compress,  pVh_decompress,  sizeof(  pVh_compress[0]  )  );
	pVh_compress->bih.biCompression  =  CONST_fourcc_h264;

	//
	makeBmpInfoHeader_yv12(  12,  pVh_compress->bih.biWidth,  pVh_compress->bih.biHeight,  &pObj->inputForEnc.vh_decompress_real.bih  );
	pObj->inputForEnc.uiBufSize  =  pObj->inputForEnc.vh_decompress_real.bih.biSizeImage;
	pObj->inputForEnc.pBuf  =  (  char  *  )malloc(  pObj->inputForEnc.uiBufSize  );
	if  (  !pObj->inputForEnc.pBuf  )  goto  errLabel;

	//	
	if  (  !pObj->common.outs[0].pBuf  )  {
		pObj->common.outs[0].pBuf  =  (  BYTE  *  )malloc(  pQdcObjInfo->cbOutputBuffer  );
		if  (  !pObj->common.outs[0].pBuf  )  goto  errLabel;
	}
#endif

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

	if  (  pObj  )  {
		//
#if  0
		if  (  pObj->pPipeline  )  {
			CEncodingPipeline  *  pPipeline  =  (  CEncodingPipeline  *  )pObj->pPipeline;
			pPipeline->Close(  );
			delete  pPipeline;
			pObj->pPipeline  =  NULL;
		}
#endif
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
#if  0

	CMyUserPipeline  *  pPipeline  =  (  CMyUserPipeline  *  )pObj->pPipeline;

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
