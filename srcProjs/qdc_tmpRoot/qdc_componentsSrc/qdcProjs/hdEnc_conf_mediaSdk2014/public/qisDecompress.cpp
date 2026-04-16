

#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
#include	<Dshow.h>

#include	<assert.h>
//#include	"base_allocator.h"

#include	"myutils.h"
#include	"qisCompressProc.h"

//#include	"pipeline_decode.h"
//#include	"myDecPipeline.h"


void  qdcFreeOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  );
int  yv12ToRgb24_ipp(  unsigned char  *  yuv,  unsigned char  *  rgb,  int  width,  int  height  );

#if  0
void PrintHelp(msdk_char *strAppName, const msdk_char *strErrorMessage)
{}
#endif

#define GET_OPTION_POINTER(PTR)        \
{                                      \
    if (2 == msdk_strlen(strInput[i]))     \
    {                                  \
        i++;                           \
        if (strInput[i][0] == MSDK_CHAR('-')) \
        {                              \
            i = i - 1;                 \
        }                              \
        else                           \
        {                              \
            PTR = strInput[i];         \
        }                              \
    }                                  \
    else                               \
    {                                  \
        PTR = strInput[i] + 2;         \
    }                                  \
}

#if  0
mfxStatus ParseInputString_dec(msdk_char* strInput[], mfxU8 nArgNum, sInputParams* pParams)
{   
    msdk_char* strArgument = MSDK_STRING("");

    if (1 == nArgNum)
    {
        PrintHelp(strInput[0], NULL);
        return MFX_ERR_UNSUPPORTED;
    }

    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);
    

    for (mfxU8 i = 1; i < nArgNum; i++)
    {
        if (MSDK_CHAR('-') != strInput[i][0])
        {
            if (0 == msdk_strcmp(strInput[i], MSDK_STRING("mpeg2")))
            {
                pParams->videoType = MFX_CODEC_MPEG2;
            }
            else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("h264")))
            {
                pParams->videoType = MFX_CODEC_AVC;
            }
            else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("vc1")))
            {
                pParams->videoType = MFX_CODEC_VC1;
            }
            else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("mvc")))
            {
                pParams->videoType = MFX_CODEC_AVC;
                pParams->bIsMVC = true;
            }
            else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("jpeg")))
            {
                pParams->videoType = MFX_CODEC_JPEG;
            }
            else
            {
                PrintHelp(strInput[0], MSDK_STRING("Unknown codec"));
                return MFX_ERR_UNSUPPORTED;
            }
            continue;
        }

        // multi-character options
        if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-hw")))
        {
            pParams->bUseHWLib = true;
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
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-r")))
        {
            if (SYSTEM_MEMORY == pParams->memType)
                pParams->memType = D3D9_MEMORY;
            pParams->bRendering = true;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-wall")))
        {
            if(i + 6 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -wall key"));
                return MFX_ERR_UNSUPPORTED;
            }
            pParams->memType = D3D9_MEMORY;
            pParams->bRendering = true;

            msdk_sscanf(strInput[++i], MSDK_STRING("%d"), &pParams->nWallW);
            msdk_sscanf(strInput[++i], MSDK_STRING("%d"), &pParams->nWallH);
            msdk_sscanf(strInput[++i], MSDK_STRING("%d"), &pParams->nWallCell);
            msdk_sscanf(strInput[++i], MSDK_STRING("%d"), &pParams->nWallMonitor);
            msdk_sscanf(strInput[++i], MSDK_STRING("%d"), &pParams->nWallFPS);
            int nTitle;
            msdk_sscanf(strInput[++i], MSDK_STRING("%d"), &nTitle);

            //pParams->bNoTitle = 0 == nTitle;
        }
#endif
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-low_latency")))
        {            
            switch (pParams->videoType)
            {
                case MFX_CODEC_AVC:
                case MFX_CODEC_JPEG:
                {
                    pParams->bLowLat = true;
                    if (!pParams->bIsMVC)
                        break;
                }
                default:
                {
                     PrintHelp(strInput[0], MSDK_STRING("-low_latency mode is suppoted only for H.264 and JPEG codecs"));
                     return MFX_ERR_UNSUPPORTED;
                }
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-calc_latency")))
        {            
            switch (pParams->videoType)
            {
                case MFX_CODEC_AVC:
                case MFX_CODEC_JPEG:
                {
                    pParams->bCalLat = true;
                    if (!pParams->bIsMVC)               
                        break;
                }
                default:
                {
                     PrintHelp(strInput[0], MSDK_STRING("-calc_latency mode is suppoted only for H.264 and JPEG codecs"));
                     return MFX_ERR_UNSUPPORTED;
                }
            }
        }
        else // 1-character options
        {
            switch (strInput[i][1])
            {
            case MSDK_CHAR('i'):
                GET_OPTION_POINTER(strArgument);
                msdk_strcopy(pParams->strSrcFile, strArgument);
                break;
            case MSDK_CHAR('o'):
                GET_OPTION_POINTER(strArgument);
                pParams->bOutput = true;
                msdk_strcopy(pParams->strDstFile, strArgument);
                break;
            case MSDK_CHAR('?'):
                PrintHelp(strInput[0], NULL);
                return MFX_ERR_UNSUPPORTED;
            default:
                {
#if  0
                    std::basic_stringstream<msdk_char> stream;
                    stream << MSDK_STRING("Unknown option: ") << strInput[i];
                    PrintHelp(strInput[0], stream.str().c_str());
#endif
                    return MFX_ERR_UNSUPPORTED;
                }
            }
        }
    }

    if (0 == msdk_strlen(pParams->strSrcFile))
    {
        PrintHelp(strInput[0], MSDK_STRING("Source file name not found"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (0 == msdk_strlen(pParams->strDstFile))
    {
        if (!pParams->bRendering)
        {
            PrintHelp(strInput[0], MSDK_STRING("Destination file name not found"));
            return MFX_ERR_UNSUPPORTED;
        }

        pParams->bOutput = false;
    }

    if (MFX_CODEC_MPEG2 != pParams->videoType && 
        MFX_CODEC_AVC   != pParams->videoType && 
        MFX_CODEC_VC1   != pParams->videoType &&
        MFX_CODEC_JPEG  != pParams->videoType)
    {
        PrintHelp(strInput[0], MSDK_STRING("Unknown codec"));
        return MFX_ERR_UNSUPPORTED;
    }

    return MFX_ERR_NONE;
}
#endif

//#define  CONST_fourcc_YV12		MAKEFOURCC('Y','V','1','2')

 //int makeBmpInfoHeader_yv12(  unsigned int bits,  int iWidth,  int iHeight,  BITMAPINFOHEADER  *  p  );



extern  "C"  int  __declspec(  dllexport  )qdcInitDecompressVideo(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_compress,  QY_VIDEO_HEADER  *  pVh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{	
	int						iErr	=	-1;
	//QDC_OBJ_INFO			qdcObjInfo;
	QDC_OBJ_hdDec		*	pObj	=	NULL;	

	//
	VIDEO_COMPRESSOR_cfgCommon  *  pVideoCfgCommon  =  (  VIDEO_COMPRESSOR_cfgCommon  *  )pVideoCompressorCfg_reserved;

	//
	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;

	//
	memcpy(  &pQdcObjInfo->cfg,  pVideoCfgCommon,  sizeof(  pQdcObjInfo->cfg  )  );

	//  memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_hdDec  *  )malloc(  sizeof(  QDC_OBJ_hdDec  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	pQdcObjInfo->var.pObj  =  pObj;
	
	//
	pQdcObjInfo->var.ucbTransformFuncsOk  =  bTransformFuncsOk(  pQdcObjInfo  );
	if  (  !pQdcObjInfo->var.ucbTransformFuncsOk  )  {
		#ifdef  _DEBUG
				OutputDebugString(  _T(  "initDecV failed, bTransformFuncs false\n"  )  );
		#endif
		goto  errLabel;
	}

#if  0
	//
	sInputParams        Params;   // input parameters from command line
		
    
    mfxStatus sts = MFX_ERR_NONE; // return value check

	//
	tmp_showInfo(  _T(  "qdcInitDecompressVideo: DecPipeline called"  )  );

	//
	memset(  &Params,  0,  sizeof(  Params  )  );
	//Params.bUseHWLib  =  TRUE;
#ifdef  _DEBUG
		//  Params.bUseHWLib  =  FALSE;
#endif

	//
	TCHAR  *  argv[30];
	int		cnt  =  0;
	argv[cnt]  =  _T(  "appName"  );						cnt  ++  ;
	argv[cnt]  =  _T(  "h264"  );							cnt  ++  ;
	argv[cnt]  =  _T(  "-i"  );								cnt  ++  ;
	argv[cnt]  =  _T(  "input.264"  );						cnt  ++  ;
	argv[cnt]  =  _T(  "-o"  );								cnt  ++  ;
	argv[cnt]  =  _T(  "c:\\tttbbb\\testoutput.yuv"  );		cnt  ++  ;
#if  0
	argv[cnt]  =  _T(  "-hw"  );							cnt  ++  ;
#else
	OutputDebugString(  _T(  "Note: hw is off\n"  )  );
#endif
	argv[cnt]  =  _T(  "-low_latency"  );					cnt  ++  ;

	int  argc  =  min(  cnt,  sizeof(  argv  )  /  sizeof(  argv[1]  )  );

		//
        //  ParseInputString_dec((  msdk_char  **  )&argv[1], --argc, &Params);


	sts = ParseInputString_dec(argv, (mfxU8)argc, &Params);
    MSDK_CHECK_PARSE_RESULT(sts, MFX_ERR_NONE, 1);
	

	//
	CMyDecPipeline  *   pPipeline  =  NULL; // pipeline for decoding, includes input file reader, decoder and output file writer
	pPipeline  =  new  CMyDecPipeline;
	if  (  !pPipeline  )  goto  errLabel;
	pObj->pPipeline  =  pPipeline;

	//
	//  memcpy(  &pPipeline->m_params,  &Params,  sizeof(  pPipeline->m_params  )  );
	pPipeline->m_params  =  Params;


#if  0
	//  qdcObjInfo.
	qdcObjInfo.cbOutputBuffer  =  pVh_decompress->bih.biSizeImage;
	qdcObjInfo.cbInputBuffer  =  qdcObjInfo.cbOutputBuffer;

	//

	//
	makeBmpInfoHeader_yv12(  12,  pVh_compress->bih.biWidth,  pVh_compress->bih.biHeight,  &pObj->outputForDec.vh_decompress_real.bih  );
	pObj->outputForDec.uiBufSize  =  pObj->outputForDec.vh_decompress_real.bih.biSizeImage;
	pObj->outputForDec.pBuf  =  (  char  *  )malloc(  pObj->outputForDec.uiBufSize  );
	if  (  !pObj->outputForDec.pBuf  )  goto  errLabel;


	//	
	if  (  !pObj->common.outs[0].pBuf  )  {
		pObj->common.outs[0].pBuf  =  (  BYTE  *  )malloc(  qdcObjInfo.cbOutputBuffer  );
		if  (  !pObj->common.outs[0].pBuf  )  goto  errLabel;
	}
#endif

	//  2014/03/23
	//
#if  0
	pObj->pMediaData  =  (  QDC_media_data  *  )malloc(  sizeof(  QDC_media_data  )  );
	if  (  !pObj->pMediaData  )  goto  errLabel;
	memset(  pObj->pMediaData,  0,  offsetof(  QDC_media_data,  buf  )  );
#endif

#endif


	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		qdcExitDecompressVideo(  pQdcObjInfo  );
	}
	if  (  !iErr  )  {
		//  memcpy(  pQdcObjInfo,  &qdcObjInfo,  sizeof(  pQdcObjInfo[0]  )  );
	}
	return  iErr;
}

extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_hdDec	*	pObj	=	(  QDC_OBJ_hdDec  *  )pQdcObjInfo->var.pObj;

	if  (  pObj  )  {
		//
#if  0
		if  (  pObj->pPipeline  )  {
			CDecodingPipeline  *  pPipeline  =  (  CDecodingPipeline  *  )pObj->pPipeline;
			pPipeline->Close(  );
			delete  pPipeline;
			pObj->pPipeline  =  NULL;
		}
#endif

		//  2014/03/24
#if  0
		if  (  pObj->pMediaData  )  {
			free(  pObj->pMediaData  );  pObj->pMediaData  =  NULL;
		}
#endif

		//  2014/03/23
		//
		qdcFreeOutputs(  pQdcObjInfo  );
		//
#if  0
		if  (  pObj->outputForDec.pBuf  )  {
			free(  pObj->outputForDec.pBuf  );  pObj->outputForDec.pBuf  =  NULL;
		}
#endif
		//
		free(  pObj  );	
	}
	pQdcObjInfo->var.pObj  =  NULL;

	return  0;
}

extern  "C"  int  __declspec(  dllexport  )qdcDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput  )
{
	QDC_OBJ_hdDec	*	pObj	=	(  QDC_OBJ_hdDec  *  )pQdcObjInfo->var.pObj;
	TCHAR				tBuf[256]	=	_T(  ""  );

	if  (  !pBmpInfo_input->bmiHeader.biSizeImage  )  {
		tmp_showInfo(  _T(  "qdcDecVideo, sizeImg 0"  )  );
		return  0;
	}

#if  0
	//  2014/03/24
	QDC_media_data  *  pMediaData  =  pObj->pMediaData;
	memset(  &pMediaData->head,  0,  sizeof(  pMediaData->head  )  );
	if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  sizeof(  pMediaData->buf  )  )  {
		tmp_showInfo(  _T(  "qdcDecVideo failed, sizeImg too big"  )  );
		return  -1;
	}
	pMediaData->head.uiLen  =  pBmpInfo_input->bmiHeader.biSizeImage;
	memcpy(  pMediaData->buf,  pInput,  pMediaData->head.uiLen  );
	if  (  qPostMsg(  pMediaData,  offsetof(  QDC_media_data,  buf  )  +  pMediaData->head.uiLen,  (  GENERIC_Q  *  )pObj->pEncDataQ  )  )  {
		tmp_showInfo(  _T(  "qdcDecVideo£º qPostMsg failed"  )  );
	}
#endif
	//  2014/03/25. not supported
	return  -1;


#if  0
	if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pQdcObjInfo->cbInputBuffer  )  return  -1;
#endif

#if  0
	CMyDecPipeline  *  pPipeline  =  (  CMyDecPipeline  *  )pObj->pPipeline;


	int  frameNumber  =  1;
#if  0
	int  imgWidth,  imgHeight;
	imgWidth  =  pBmpInfo_input->bmiHeader.biWidth;
	imgHeight  =  pBmpInfo_input->bmiHeader.biHeight;
#endif



	int  index  =  0;
	mfxStatus  sts;
	sts  =  pPipeline->decompressVideo(  pQdcObjInfo,  &pObj->bInited,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage,  (  BYTE  *  )pObj->common.outs[index].pBuf,  &pBmpInfo_input->bmiHeader.biWidth,  &pBmpInfo_input->bmiHeader.biHeight,  frameNumber  );
	if  (  sts  ==  MFX_ERR_MORE_DATA  )  {
		return  0;
	}
	if  (  sts  <  0  )  {
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "qdcDecompressVideo: pPipeline->decompressVideo failed, sts %d\n"  ),  sts  );
		//  frameNumber  =  0;
		tmp_showInfo(  tBuf  );
		return  -1;
	}

	if  (  frameNumber  !=  1  )  {
		if  (  frameNumber  )  {
			assert(  0  );
		}
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "qdcDecompressVideo err: frameNumber %d\n"  ),  frameNumber  );
		OutputDebugString(  tBuf  );
		//  return  -1;

	}
	else  {
		  //#ifdef  _DEBUG
		  #if		1
				  OutputDebugString(  _T(  "qdcDecompressVideo ok\n"  )  );
		  #endif
	}

	if  (  frameNumber  )  {
		int  biBitCount  =  12;
		pObj->common.outs[index].len  =  (  pBmpInfo_input->bmiHeader.biWidth  *  biBitCount  +  31  )  /  32  *  4  *  pBmpInfo_input->bmiHeader.biHeight;
	}


#endif


#if  0
	int  index  =  0;
	memcpy(  pObj->outs[index].pBuf,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );
	pObj->outs[index].len  =  pBmpInfo_input->bmiHeader.biSizeImage;
#endif

//	return  frameNumber;
}



extern  "C"  int  __declspec(  dllexport  )  qdcDecompressVideoRun(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int					iErr	=	-1;
	QDC_OBJ_hdDec	*	pObj	=	(  QDC_OBJ_hdDec  *  )pQdcObjInfo->var.pObj;
	TCHAR				tBuf[256]	=	_T(  ""  );
	
#if  0
	CMyDecPipeline  *  pPipeline  =  (  CMyDecPipeline  *  )pObj->pPipeline;
	
	mfxStatus sts = MFX_ERR_NONE; // return value check
	
	sts  =  pPipeline->myRun(  pQdcObjInfo  );
#endif

	iErr  =  0;
errLabel:
	return  iErr;
}