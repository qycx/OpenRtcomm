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

#include "actions.h"
#include "action_processor.h"
#include "brc.h"
#include <sample_defs.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <typeinfo>

#include	"myutils.h"

//
#define	CONST_ver_qisCompress		"02630336"		//  2016/04/10,"02630294"	//  2015/11/03,"02630243"		//  2015/11/02,"02630239"		//  2015/10/24,"02630228"	//  2012/08/24		//  2012/06/23


//
//
//  #include	"pipeline_encode.h"
#include	"mypipeline_user.h"

//QIS_guiOpen		*  g_pGuiOpen					=	NULL;
//BOOL				g_bUsePipeline_videoconf	=  FALSE;		//  2012/09/01


#if  0
int  yuy2ToRgb24_ipp(  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );
int  rgb24ToYv12_ipp(  unsigned  char  *  rgb,  unsigned  char  *  yuv,  int  width,  int  height,  BOOL  bFlip  );
#endif






//  2011/09/25
void PrintHelp(TCHAR *strAppName, TCHAR *strErrorMessage)
{
}






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

	//  2012/09/01. 在hd4000的核显,采用pipeline_videoconf. hd p4000上出错,所以,暂时不使用
#if  0
	g_bUsePipeline_videoconf  =  FALSE;	//  IsHw31Supported(  );	//  FALSE;	//  TRUE;
#endif
	
	//  2012/09/10. 没有解决好硬解压的初始化,经常出现无法初始化的错误,所以暂时不能使用
	//  if  (  p->ucbNotSupported  ||  !IsHw31Supported(  )  )  
	{
		p->ucbNotSupported_dec_h264  =  TRUE;
	}
#ifdef  _DEBUG
		//  p->ucbNotSupported_dec_h264  =  TRUE;		
		//  g_bUsePipeline_videoconf  =  FALSE;
#endif

	//  2012/05/26
	//  tmp_showInfo(  _T(  "qdcInit called. v025127"  )  );
	TCHAR	tBuf[128];
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "qdcInit called. hdEnc_conf_mediasdk,%s"  ),  _T(  CONST_ver_qisCompress  )  );
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s. %s"  ),  tBuf,  p->ucbNotSupported_hw  ?  _T(  "hw not supported"  )  :  _T(  "OK"  )  );
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
	QDC_OBJ_h264Common  *  pObj	=	(  QDC_OBJ_h264Common  *  )pQdcObjInfo->var.pObj;
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


///////////////////////////////

template<typename T>
    inline void read_argument(const msdk_string& option, const msdk_string& argument, T& value)
    {
        if (MFX_ERR_NONE != msdk_opt_read(argument.c_str(), value)) {
            throw msdk_string(MSDK_STRING("Failed to read argument for the option ") + option);
        }
    }

mfxI32 get_index(const std::basic_string<msdk_char>& from, int prefix_len )
{
    mfxI32 idx = 0;
    if (from.length() != (size_t)prefix_len)
    {
        if (MFX_ERR_NONE != msdk_opt_read(from.substr(prefix_len), idx))
        {
            idx = -1;
        }
    }
    return idx;
}

#define CHECK_OPTION_ARGS(n)\
if (i + n == nArgNum)\
{\
    throw std::basic_string<msdk_char>(MSDK_STRING("Invalid syntax for option:")) + strInput[i];\
}

void ParseParFile(const msdk_char* file_path, VideoConfParams& pParams);
void CheckInitParams(VideoConfParams& pParams);
void ParseInputString(msdk_char** strInput, int nArgNum, VideoConfParams& params)
{
    if (0 == nArgNum)
    {
        throw std::basic_string<msdk_char>(MSDK_STRING(""));
    }

    // default implementation
    params.bUseHWLib = true;

    // parse command line parameters
    for (mfxU8 i = 0; i < nArgNum; i++)
    {
        msdk_char* arg = strInput[i];
        mfxI32 idx = get_index(strInput[i], 2);
        if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-sw")))
        {
            params.bUseHWLib = false;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-hw")))
        {
            params.bUseHWLib = true;
        }
#if D3D_SURFACES_SUPPORT
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-d3d")))
        {
            params.memType = D3D9_MEMORY;
        }
#endif
        else if (0 == msdk_strncmp(strInput[i], MSDK_STRING("-w"), 2) && -1 != idx)
        {
            CHECK_OPTION_ARGS(1);
            read_argument(arg, strInput[++i], params.sources[idx].nWidth);
        }
        else if (0 == msdk_strncmp(strInput[i], MSDK_STRING("-h"), 2) && -1 != idx)
        {
            CHECK_OPTION_ARGS(1);
            read_argument(arg, strInput[++i], params.sources[idx].nHeight);
        }
        else if (0 == msdk_strncmp(strInput[i], MSDK_STRING("-f"), 2) && -1 != idx)
        {
            CHECK_OPTION_ARGS(1);
            read_argument(arg, strInput[++i], params.sources[idx].dFrameRate);
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-b")))
        {
            CHECK_OPTION_ARGS(1);
            read_argument(arg, strInput[++i], params.nTargetKbps);
        }
        else if (0 == msdk_strncmp(strInput[i], MSDK_STRING("-i"), 2) && -1 != idx)
        {
            CHECK_OPTION_ARGS(1);
            //we expect frame number attached with -i1, -i2
            if (idx != 0)
            {
                CHECK_OPTION_ARGS(2);
                mfxU32 nFrame = 0;
                read_argument(arg, strInput[++i], nFrame);
                params.pActionProc->RegisterAction(nFrame, new SetSourceAction(idx));
            }
            params.sources[idx].srcFile = strInput[++i];
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-o")))
        {
            CHECK_OPTION_ARGS(1);
            params.dstFile = strInput[++i];
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-par")))
        {
            CHECK_OPTION_ARGS(1);
            ParseParFile(strInput[++i], params);
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-bs" )))
        {
            CHECK_OPTION_ARGS(2);

            double dBitrateScale = 0;
            mfxU32 nFrameOrder = 0;
            read_argument(arg, strInput[++i], nFrameOrder);
            read_argument(arg, strInput[++i], dBitrateScale);

            params.pActionProc->RegisterAction(nFrameOrder, new ChangeBitrateAction(dBitrateScale));
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-l0")))
        {
            CHECK_OPTION_ARGS(2);

            mfxU16 nLen = 0;
            mfxU32 nFrameOrder = 0;
            read_argument(arg, strInput[++i], nFrameOrder);
            read_argument(arg, strInput[++i], nLen);

            params.pActionProc->RegisterAction(nFrameOrder, new SetL0SizeAction(nLen));
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-brc")))
        {
            params.pBrc.reset(new SampleBRC());
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-rpmrs")))
        {
            params.bRPMRS = true;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-bf")))
        {
            CHECK_OPTION_ARGS(2);

            mfxU32 nFrameOrder = 0;
            mfxU32 nFrameBroken = 0;
            read_argument(arg, strInput[++i], nFrameOrder);
            read_argument(arg, strInput[++i], nFrameBroken);
            if (nFrameBroken >= nFrameOrder)
            {
                std::basic_stringstream<msdk_char> stream;
                stream<<MSDK_STRING("in parsing -bf option. Broken frameorder(current=")<<nFrameBroken<<MSDK_STRING(") ");
                stream<<MSDK_STRING("should be less than reported frameorder(current=")<<nFrameOrder<<MSDK_STRING(")");

                throw stream.str();
            }

            //to instruct encoder to DONOT predict from specific frame it is necessary to add this frame to rejected ref list
            //putting frame into rejected list does make this frame permanently rejected

            //if feedback is delayed frames predicted from broken can be already encoded, need to also remove all of them from references
            for (mfxU32 j = nFrameBroken; j < nFrameOrder; j++)
            {
                params.pActionProc->RegisterAction(nFrameOrder, new PutFrameIntoRefListAction(REFLIST_REJECTED, j, false));
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-gkf")))
        {
            CHECK_OPTION_ARGS(1);

            mfxU32 nFrameOrder = 0;
            read_argument(arg, strInput[++i], nFrameOrder);

            params.pActionProc->RegisterAction(nFrameOrder, new KeyFrameInsertAction());
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-ltr")))
        {
            CHECK_OPTION_ARGS(1);

            mfxU32 nLTFrameOrder = 0;
            read_argument(arg, strInput[++i], nLTFrameOrder);

            //firstly frame should be added to long term list once
            //NOTE: to remove this longterm, you need to put it once into rejected reflist
            params.pActionProc->RegisterAction(nLTFrameOrder, new PutFrameIntoRefListAction(REFLIST_LONGTERM, nLTFrameOrder, false));

            //secondary to say MediaSDK that prediction from this longterm is necessary you need to put frameorder into preferred reflist
            //preferred list is stateless and should be created for every frame, that is why we creating permanent action untill next IDR
            params.pActionProc->RegisterAction(nLTFrameOrder, new PutFrameIntoRefListAction(REFLIST_PREFERRED, nLTFrameOrder, true));
        } else if ( 0== msdk_strcmp(strInput[i], MSDK_STRING("-ts")))
        {
            CHECK_OPTION_ARGS(1);
            params.nTemporalScalabilityBase = 2;
            read_argument(arg, strInput[++i], params.nTemporalScalabilityLayers);
            if (params.nTemporalScalabilityLayers > 4)
            {
                throw std::basic_string<msdk_char>(MSDK_STRING("in -ts option maximum layers value is 4"));
            }
        } else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-latency")))
        {
            params.bCalcLAtency = true;
        } else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-ir")))
        {
            CHECK_OPTION_ARGS(2);
            params.nRefrType = 1;
            read_argument(arg, strInput[++i], params.nCycleSize);
            if (params.nCycleSize < 2 || params.nCycleSize >= VideoConfPipeline::gopLength)
            {
                std::basic_stringstream<msdk_char> stream;
                stream<<MSDK_STRING("in -ir option cycle_size should be more than 2 and less than ")<<VideoConfPipeline::gopLength;
                throw stream.str();
            }
            read_argument(arg, strInput[++i], params.nQPDelta);
            if (params.nQPDelta < -51 || params.nQPDelta > 51)
            {
                throw std::basic_string<msdk_char>(MSDK_STRING("in -ir option QP difference is signed value in [-51, 51] range"));
            }
        }

        else
        {
            throw std::basic_string<msdk_char>(MSDK_STRING("Unknown option : ")) + strInput[i];
        }
    }
}

void CheckInitParams(VideoConfParams& params)
{
    std::map<mfxU32, VideoConfParams::SourceInfo> :: iterator i;
    std::basic_stringstream<msdk_char> error;
    if (params.sources.empty())
    {
        throw std::basic_string<msdk_char>(MSDK_STRING("Source file name not set"));
    }

    for (i = params.sources.begin(); i != params.sources.end(); i++)
    {
        VideoConfParams::SourceInfo &info = i->second;
        // check if all mandatory parameters were set
        if (info.srcFile.empty())
        {
            if (i->first != 0)
            {
                error<< i->first << MSDK_STRING(" ");
            }
            error<< MSDK_STRING("source file name not set");

            throw error.str();
        }

        if (params.dstFile.empty())
        {
            throw std::basic_string<msdk_char>(MSDK_STRING("Destination file name not set"));
        }

        if (0 == info.nWidth)
        {
            if (i->first != 0)
            {
                error<< i->first << MSDK_STRING(" ");
            }
            error<< MSDK_STRING("width must be specidied");

            if (i->first != 0)
            {
                error<< MSDK_STRING("(-w") << i->first << MSDK_STRING(")");
            }
            else
            {
                error<< MSDK_STRING("(-w)");
            }

            throw error.str();
        }

        if (0 == info.nHeight)
        {
            if (i->first!= 0)
            {
                error<< i->first << MSDK_STRING(" ");
            }
            error<< MSDK_STRING("height must be specified");

            if (i->first != 0)
            {
                error<< MSDK_STRING("(-h") << i->first << MSDK_STRING(")");
            }
            else
            {
                error<< MSDK_STRING("(-h)");
            }

            throw error.str();
        }

        if (info.dFrameRate <= 0)
        {
            info.dFrameRate = 30;
        }
    }
    // calculate default bitrate based on the resolution (a parameter for encoder, so Dst resolution is used)
    if (params.nTargetKbps == 0)
    {
        params.nTargetKbps = CalculateDefaultBitrate(MFX_CODEC_AVC, 0, params.sources[0].nWidth, params.sources[0].nHeight, params.sources[0].dFrameRate);
    }
}

void ParseParFile(const msdk_char* file_path, VideoConfParams& pParams)
{
    //reading whole file into string stream
    std::basic_fstream<msdk_char> file_stream(file_path, std::ios_base::in );
    if (file_stream.fail())
        throw std::basic_string<msdk_char>(MSDK_STRING("Failed to open par file : ")) + file_path;

    std::basic_stringstream<msdk_char> str_stream;
    file_stream >> str_stream.rdbuf();

    std::basic_string<msdk_char> str = str_stream.str();

    //removing comments
    for (size_t offset = 0; offset != std::basic_string<msdk_char>::npos;)
    {
        offset = str.find(MSDK_STRING("#"), offset);
        if (offset != std::basic_string<msdk_char>::npos)
        {
            //removing whole line
            size_t offset2 = str.find(MSDK_STRING("\n"), offset);
            size_t count = offset2 == std::basic_string<msdk_char>::npos ? offset2 : offset2 - offset;
            str.erase(offset, count);
            offset++;
        }
    }
    //removing line endings
    std::replace(str.begin(), str.end(), MSDK_CHAR('\n'), MSDK_CHAR(' '));

    //put this 1 line file into stream;
    str_stream.str(str);

    //split it into words by spaces, and forming msdk_char** array
    std::list<std::basic_string<msdk_char> > command_line_strings;
    std::vector<msdk_char*> command_line_args;

    for (;!str_stream.eof();)
    {
        std::basic_string<msdk_char> current_arg;
        if ((str_stream >> current_arg).fail())
            break;
        command_line_strings.push_back(current_arg);
        command_line_args.push_back(&command_line_strings.back().at(0));
    }

    if (!command_line_args.empty())
    {
        ParseInputString((msdk_char**)&command_line_args.front(), (int)command_line_args.size(), pParams);
    }
}


//////////////////////////////////////////



extern  "C"  int  __declspec(  dllexport  )qdcInitCompressVideo(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{	
	int						iErr	=	-1;
	//QDC_OBJ_INFO		&	qdcObjInfo  =  *(  QDC_OBJ_INFO  *  )pQdcObjInfo;
	QDC_OBJ_trans		*	pObj	=	NULL;	

	//  2012/09/01
	//
	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;

	VIDEO_COMPRESSOR_cfgCommon	*	pCompressor	=	(  VIDEO_COMPRESSOR_cfgCommon  *  )pVideoCompressorCfg_reserved;

	//
	memcpy(  &pQdcObjInfo->cfg,  pCompressor,  sizeof(  pQdcObjInfo->cfg  )  );

	//
	VideoConfParams init_params;   // input parameters from command line



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
	//  为0时,由ParseInputString里自动设置
	int  nBitRate  =  myGetBitrate(  pCompressor,  pVh_decompress->bih.biWidth,  pVh_decompress->bih.biHeight  )  /  1024;


	//
	mfxStatus sts = MFX_ERR_NONE; // return value check
		

	//
	TCHAR	argv0[32]  =  _T(  "encode"  );
	//  TCHAR	argv1[32]  =  _T(  "h264"  );
	TCHAR	argv2[32]  =  _T(  "-i"  );
	TCHAR	argv3[32]  =  _T(  "tmpYuv"  );
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
	//
	#if  10
	TCHAR	argv_d3d[32]	=	_T(  "-d3d"  );	//  2014/07/04
#else
	TCHAR	argv_d3d[32]	=	_T(  "-d3d11"  );	//  2014/07/04
#endif

	
	//
	_sntprintf(  argv_w,  mycountof(  argv_w  ),  _T(  "%d"  ),  pVh_decompress->bih.biWidth  );
	_sntprintf(  argv_h,  mycountof(  argv_h  ),  _T(  "%d"  ),  pVh_decompress->bih.biHeight  );
	_sntprintf(  argv_f,  mycountof(  argv_f  ),	_T(  "%d"  ),  pCompressor->usMaxFps_toShareBmp  );
	_sntprintf(  argv_kbps,  mycountof(  argv_kbps  ),  _T(  "%d"  ),  nBitRate  );

#if  0
	//
	Params.dFrameRate  =  pCompressor->usMaxFps_toShareBmp;
	Params.nTargetUsage  =  nTargetUsage;   //  MFX_TARGETUSAGE_BALANCED;	//  MFX_TARGETUSAGE_UNKNOWN;    	//  MFX_TARGETUSAGE_BEST_QUALITY;				//  MFX_TARGETUSAGE_BEST_SPEED;		//  2011/12/18
	Params.bUseHWLib  =  FALSE;	//  TRUE;		//  FALSE;			//  	
	Params.nBitRate  =  nBitRate;
#endif
	
	//
	TCHAR  *  pArgv[20];
	int		tmp_argc  =  0;
	//
	pArgv[tmp_argc]  =  argv0;  tmp_argc  ++  ;
	//pArgv[tmp_argc]  =  argv1;  tmp_argc  ++  ;
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
	//
	pArgv[tmp_argc]  =  argv_d3d;  tmp_argc  ++  ;
	if  (  tmp_argc  >  mycountof(  pArgv  )  )  goto  errLabel;

		

	try
	{

		//
		init_params.pActionProc.reset(new ActionProcessor);
		
		//
		ParseInputString(  pArgv  +  1,  tmp_argc  -  1,  init_params  );
		CheckInitParams(init_params);
			

		#if  10	
		{
	
		TCHAR	tBuf[128]  =  _T(  ""  );
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "hdEncV_conf init: bitrate [%dk]. w %d, h %d, fps %d"  ),  (  int  )init_params.nTargetKbps,  (  int  )init_params.sources[0].nWidth,  (  int  )init_params.sources[0].nHeight,  (  int  )init_params.sources[0].dFrameRate    );
		//			
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, memType %d"  ),  tBuf,  init_params.memType  );
		//
		tmp_showInfo(  tBuf  );			
		}
		#endif
	
		//
		CMyUserPipeline  *  pPipeline  =  NULL;
		pPipeline  =  new  CMyUserPipeline;
		if  (  !pPipeline  )  goto  errLabel;
		pObj->pPipeline  =  pPipeline;

		//	
		// 
		//  pPipeline->m_params  =  Params;	
		pPipeline->m_var.pQdcObjInfo  =  pQdcObjInfo;
		
		//
		sts = pPipeline->Init(  &init_params);
		if  (  sts  <  0  )  goto  errLabel;


		//  应该把CEncodingPipeline从例子那里拷出来，否则有些操作不能按预计来修改。象文件操作之类，应该从代码中去除 。
		

		//  qdcObjInfo.
		pQdcObjInfo->var.cbOutputBuffer  =  pVh_decompress->bih.biSizeImage;
		pQdcObjInfo->var.cbInputBuffer  =  pQdcObjInfo->var.cbOutputBuffer;

		//  2012/06/27
		//pObj->ucbFlippedImg  =  pCompressor->ucbOutputFlippedImg;

		//
		memcpy(  pVh_compress,  pVh_decompress,  sizeof(  pVh_compress[0]  )  );
		pVh_compress->bih.biCompression  =  CONST_fourcc_h264;

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
		tmp_showInfo(  _T(  "qdcInitCompressV: exception caught"  )  );
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

	if  (  pObj  )  {
		//
		if  (  pObj->pPipeline  )  {
			CMyUserPipeline  *  pPipeline  =  (  CMyUserPipeline  *  )pObj->pPipeline;
			//
			pPipeline->Close(  );
			//
			delete  pPipeline;
			pObj->pPipeline  =  NULL;
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

	return  0;
}

//  2014/03/30
extern  "C"  __declspec(  dllexport  )  int  qdcGetSpsPps(  QDC_OBJ_INFO  *  pQdcObjInfo,  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize,  char  *  kk,  unsigned  int  *  puiKkSize  )
{
	if  (  !pQdcObjInfo->var.pObj  )  return  -1;
	QDC_OBJ_trans	*	pObj	=	(  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;
	if  (  !pObj  )  return  -1;
	CMyUserPipeline  *  pPipeline  =  (  CMyUserPipeline  *  )pObj->pPipeline;



	if  (  pPipeline->MakeSPSPPS(  spsBuf,  puiSpsSize,  ppsBuf,  puiPpsSize  )  )  return  -1;



	return  0;
}


int  qdcFindOutputIndex(  void  *  pQdcObjInfoParam  )
{
	if  (  !pQdcObjInfoParam  )  return  -1;

	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pQdcObjInfoParam;
	QDC_OBJ_h264Common	*	pObj	=	(  QDC_OBJ_h264Common  *  )pQdcObjInfo->var.pObj;
	
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
	QDC_OBJ_h264Common	*	pObj	=	(  QDC_OBJ_h264Common  *  )pQdcObjInfo->var.pObj;

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

	CMyUserPipeline  *  pPipeline  =  (  CMyUserPipeline  *  )pObj->pPipeline;

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
	
	CMyUserPipeline  *  pPipeline  =  (  CMyUserPipeline  *  )pObj->pPipeline;
	

	//  2015/01/04	
	if  (  !pPipeline  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qdcCompressVideoRun failed, encV_conf. Pipeline is null"  )  );
		tmp_showInfo(  tBuf  );
		return  -1;
	}
	
	//  2014/07/01	
	if  (  pPipeline->m_var.bFailed  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encV_conf. Pipeline->bFailed ture, sts %d"  ),  pPipeline->m_var.sts_failed  );
		tmp_showInfo(  tBuf  );
		return  -1;		
	}


#if  10

		try  {
			

	sts  =  pPipeline->Run(  );


	//  2014/05/28
		TCHAR	tBuf[128]  =  _T(  ""  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encVConfPipeline->Run returns sts %d"  ),  sts  );
		tmp_showInfo(  tBuf  );

		}
			catch (std::exception &ex)
    {
#ifdef UNICODE
        wprintf(L"\nstd::exception caught: %S\n", ex.what());    
#else
        printf("\nstd::exception caught: %s\n", ex.what());    
#endif
		tmp_showInfo(  _T(  "qdcCompressVRun: exception caught"  )  );
		goto  errLabel;
		}
    catch (...)
    {
        msdk_printf(MSDK_STRING("\nUnknown exception caught\n"));
		tmp_showInfo(  _T(  "qdcCompressVRun: unknown exception caught"  )  );
		goto  errLabel;
    }



#endif

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
	QDC_OBJ_h264Common	*	pObj	=	(  QDC_OBJ_h264Common  *  )pQdcObjInfo->var.pObj;

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
	QDC_OBJ_h264Common	*	pObj	=	(  QDC_OBJ_h264Common  *  )pQdcObjInfo->var.pObj;

	tmp_showInfo(  _T(  "qdcClearOutputs"  )  );
	
	for  (  i  =  0;  i  <  sizeof(  pObj->outs  )  /  sizeof(  pObj->outs[0]  );  i  ++  )  {
		 pObj->outs[i].len  =  0;
	}

	return  0;
}
