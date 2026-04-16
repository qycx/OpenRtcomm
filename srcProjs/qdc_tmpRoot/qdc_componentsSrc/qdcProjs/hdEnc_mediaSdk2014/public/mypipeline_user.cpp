//
//              INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license  agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in  accordance  with the terms of that agreement.
//        Copyright (c) 2010 Intel Corporation. All Rights Reserved.
//
//
//*/
//  #include	"stdafx.h"

#include	"myutils.h"
#include "mypipeline_user.h"
#include "sysmem_allocator.h"

#include	"qisCompressProc.h"
#include	"myFunc_mediaSdk.h"
#include	"tmp_decode_render.h"
#include	"MyD3D11_Device.h"
#include	"d3d_device.h"
#include "parameters_dumper.h"
#include <ctxQmThread.h>

//
const mfxU8 HEVC_ENCODER_UID[] = {0x2f,0xca,0x99,0x74,0x9f,0xdb,0x49,0xae,0xb1,0x21,0xa5,0xb6,0x3e,0xf5,0x68,0xf7};


int  qdcFindOutputIndex(  void  *  pQdcObjInfoParam  );
int  qdcOutput(  void  *  pQdcObjInfoParam,  int  outputIndex,  char  *  pOutput,  unsigned  int  uiOutputSize  );
int  tmp_showInfo(  TCHAR  *  hint  );



//
//
BOOL  bShowRenderWnd(  )
{
#ifdef  _DEBUG
		#if  0
			 return  TRUE;
		#endif
#endif

	return  FALSE;
}




//
//
int  enc_CMySmplYUVReader_myLoadNextFrame_msdk(  void  *  pPipelineParam,  unsigned  short  usPktResType,  void  *  p0_pInput,  void  *  p1_uiInputSize,  PARAM_CMySmplYUVReader_myLoadNextFrame_msdk  *  pParam  )
{
	CMyUserPipeline  *  pPipeline  =  (  CMyUserPipeline  *  )pPipelineParam;

	return  pPipeline->CMySmplYUVReader_myLoadNextFrame_msdk(  usPktResType,  p0_pInput,  p1_uiInputSize,  pParam  );
}



//
CMyUserPipeline::CMyUserPipeline() : CEncodingPipeline()
{
#if  0
    m_pRotateSurfaces = NULL; 
    ZERO_MEMORY(m_usrRotateParams);        
    ZERO_MEMORY(m_RotateResponse);
#endif
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	//
	init_ext_buffer(m_extCO);

	//  2015/10/30	
	m_bIsMVC  =  FALSE; // enables MVC mode (need to support several files as an output)

#if D3D_SURFACES_SUPPORT
    m_pS3DControl  =  NULL;
#endif

}

CMyUserPipeline::~CMyUserPipeline()
{
    Close();
}

#if  0
mfxStatus CMyUserPipeline::InitRotateParam(sInputParams *pInParams)
{
    MSDK_CHECK_POINTER(pInParams, MFX_ERR_NULL_PTR);

#if  0
    MSDK_ZERO_MEMORY(m_pluginVideoParams);

    m_pluginVideoParams.AsyncDepth = m_nAsyncDepth; // the maximum number of tasks that can be submitted before any task execution finishes
    m_pluginVideoParams.vpp.In.FourCC = MFX_FOURCC_NV12;
    m_pluginVideoParams.vpp.In.Width = m_pluginVideoParams.vpp.In.CropW = pInParams->nWidth;
    m_pluginVideoParams.vpp.In.Height = m_pluginVideoParams.vpp.In.CropH = pInParams->nHeight;
    m_pluginVideoParams.vpp.Out.FourCC = MFX_FOURCC_NV12;
    m_pluginVideoParams.vpp.Out.Width = m_pluginVideoParams.vpp.Out.CropW = pInParams->nWidth;
    m_pluginVideoParams.vpp.Out.Height = m_pluginVideoParams.vpp.Out.CropH = pInParams->nHeight;

    m_RotateParams.Angle = pInParams->nRotationAngle;
#endif

    return MFX_ERR_NONE;
}
#endif


//
int  CMyUserPipeline::MakeSPSPPS(  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize  )
{
	int		iErr	=	-1;


	std::vector<char>  m_SpsPps;

	//
	std::vector<char>& spspps  =  m_SpsPps;

	//
	std::vector<mfxU8> m_Sps;
    std::vector<mfxU8> m_Pps;
	BOOL  m_bCreateSPS  =  TRUE;

	if  (  !spsBuf  ||  !puiSpsSize  ||  !ppsBuf  ||  !puiPpsSize  )  return  -1;


	// void Transform <MFXVideoENCODE>::MakeSPSPPS( std::vector<char>& spspps) 
	{
    if (!m_bCreateSPS)
        return  0;
    m_Sps.resize(128,0);
    m_Pps.resize(128,0);

    mfxExtCodingOptionSPSPPS extSPSPPS;
    MSDK_ZERO_MEMORY(extSPSPPS);
    extSPSPPS.Header.BufferId = MFX_EXTBUFF_CODING_OPTION_SPSPPS;
    extSPSPPS.Header.BufferSz = sizeof(mfxExtCodingOptionSPSPPS);
#if  0
    extSPSPPS.PPSBufSize = (mfxU16)m_Sps.size();
    extSPSPPS.SPSBufSize = (mfxU16)m_Pps.size();
    extSPSPPS.PPSBuffer = &m_Sps.front();
    extSPSPPS.SPSBuffer = &m_Pps.front();
#endif
    extSPSPPS.PPSBufSize = (mfxU16)m_Pps.size();
    extSPSPPS.SPSBufSize = (mfxU16)m_Sps.size();
    extSPSPPS.PPSBuffer = &m_Pps.front();
    extSPSPPS.SPSBuffer = &m_Sps.front();


	//
    mfxExtBuffer* encExtParams[1];
    mfxVideoParam par={};
    encExtParams[0] = (mfxExtBuffer *)&extSPSPPS;
    par.ExtParam = &encExtParams[0];
    par.NumExtParam = 1;
    for (;;) {
		mfxStatus sts = this->m_pmfxENC->GetVideoParam(&par);
        if (sts == MFX_ERR_NONE)
            break;
        if (sts == MFX_ERR_NOT_ENOUGH_BUFFER) {
            extSPSPPS.PPSBufSize = (mfxU16)m_Pps.size()*2;
            extSPSPPS.SPSBufSize = (mfxU16)m_Sps.size()*2;
            m_Sps.resize(extSPSPPS.SPSBufSize);
            m_Pps.resize(extSPSPPS.PPSBufSize);
            continue;
        } else {
            //MSDK_TRACE_ERROR(MSDK_STRING("MFXVideoENCODE::GetVideoParam with mfxExtCodingOptionSPSPPS, sts=") << sts);
            //  throw EncodeGetVideoParamError();
			goto  errLabel;
        }
    }

    spspps.resize(extSPSPPS.SPSBufSize + extSPSPPS.PPSBufSize, 0);
    MSDK_MEMCPY(&spspps.front(), extSPSPPS.SPSBuffer, extSPSPPS.SPSBufSize);
    MSDK_MEMCPY(&spspps.front() + extSPSPPS.SPSBufSize, extSPSPPS.PPSBuffer, extSPSPPS.PPSBufSize);

	//
	if  (  extSPSPPS.SPSBufSize  >  *puiSpsSize  )  {
		tmp_showInfo(  _T(  "MakeSPSPPS failed, spsBufSize too big"  )  );
		goto  errLabel;
	}
	if  (  extSPSPPS.PPSBufSize  >  *puiPpsSize  )  {
		tmp_showInfo(  _T(  "MakeSPSPPS failed, ppsBufSize too big"  )  );
		goto  errLabel;
	}
	memcpy(  spsBuf,  extSPSPPS.SPSBuffer,  extSPSPPS.SPSBufSize  );
	*puiSpsSize  =  extSPSPPS.SPSBufSize;
	memcpy(  ppsBuf,  extSPSPPS.PPSBuffer,  extSPSPPS.PPSBufSize  );
	*puiPpsSize  =  extSPSPPS.PPSBufSize;

	//
    m_bCreateSPS = false;

	}


	//
	iErr  =  0;

errLabel:
	return  iErr;
}


//
int  CMyUserPipeline::MakeVPS(  char  *  vpsBuf,  unsigned  int  *  puiVpsSize  )
{
	int		iErr	=	-1;


	//std::vector<char>  m_SpsPps;

	//
	//std::vector<char>& spspps  =  m_SpsPps;

	//
	std::vector<mfxU8> m_Vps;
	BOOL  m_bCreateSPS  =  TRUE;

	if  (  !vpsBuf  ||  !puiVpsSize  )  return  -1;


	// void Transform <MFXVideoENCODE>::MakeSPSPPS( std::vector<char>& spspps) 
	{
    if (!m_bCreateSPS)
        return  0;
    m_Vps.resize(128,0);

    mfxExtCodingOptionVPS extVPS;
    MSDK_ZERO_MEMORY(extVPS);
    extVPS.Header.BufferId = MFX_EXTBUFF_CODING_OPTION_VPS;
    extVPS.Header.BufferSz = sizeof(mfxExtCodingOptionVPS);
#if  0
    extSPSPPS.PPSBufSize = (mfxU16)m_Sps.size();
    extSPSPPS.SPSBufSize = (mfxU16)m_Pps.size();
    extSPSPPS.PPSBuffer = &m_Sps.front();
    extSPSPPS.SPSBuffer = &m_Pps.front();
#endif
	extVPS.VPSBufSize = (mfxU16)m_Vps.size();
    extVPS.VPSBuffer = &m_Vps.front();


	//
    mfxExtBuffer* encExtParams[1];
    mfxVideoParam par={};
    encExtParams[0] = (mfxExtBuffer *)&extVPS;
    par.ExtParam = &encExtParams[0];
    par.NumExtParam = 1;
    for (;;) {
		mfxStatus sts = this->m_pmfxENC->GetVideoParam(&par);
        if (sts == MFX_ERR_NONE)
            break;
        if (sts == MFX_ERR_NOT_ENOUGH_BUFFER) {
            extVPS.VPSBufSize = (mfxU16)m_Vps.size()*2;
            m_Vps.resize(extVPS.VPSBufSize);
            continue;
        } else {
            //MSDK_TRACE_ERROR(MSDK_STRING("MFXVideoENCODE::GetVideoParam with mfxExtCodingOptionSPSPPS, sts=") << sts);
            //  throw EncodeGetVideoParamError();
			goto  errLabel;
        }
    }

#if  0
    spspps.resize(extSPSPPS.SPSBufSize + extSPSPPS.PPSBufSize, 0);
    MSDK_MEMCPY(&spspps.front(), extSPSPPS.SPSBuffer, extSPSPPS.SPSBufSize);
    MSDK_MEMCPY(&spspps.front() + extSPSPPS.SPSBufSize, extSPSPPS.PPSBuffer, extSPSPPS.PPSBufSize);
#endif

	//
	if  (  extVPS.VPSBufSize  >  *puiVpsSize  )  {
		tmp_showInfo(  _T(  "MakeVPS failed, vpsBufSize too big"  )  );
		goto  errLabel;
	}
	memcpy(  vpsBuf,  extVPS.VPSBuffer,  extVPS.VPSBufSize  );
	*puiVpsSize  =  extVPS.VPSBufSize;

	//
    m_bCreateSPS = false;

	}


	//
	iErr  =  0;

errLabel:
	return  iErr;
}







//  2016/04/16
#if  0
mfxStatus iiCMyUserPipeline::InitMfxEncParams(sInputParams *pInParams)
{
    m_mfxEncParams.mfx.CodecId                 = pInParams->CodecId;
    m_mfxEncParams.mfx.TargetUsage             = pInParams->nTargetUsage; // trade-off between quality and speed
    m_mfxEncParams.mfx.TargetKbps              = pInParams->nBitRate; // in Kbps
    m_mfxEncParams.mfx.RateControlMethod       = pInParams->nRateControlMethod;
    m_mfxEncParams.mfx.GopRefDist = pInParams->nGopRefDist;
    m_mfxEncParams.mfx.GopPicSize = pInParams->nGopPicSize;
    m_mfxEncParams.mfx.NumRefFrame = pInParams->nNumRefFrame > 0?pInParams->nNumRefFrame : 1;
    m_mfxEncParams.mfx.IdrInterval = pInParams->nIdrInterval;


	//  2016/04/16
	/*Initializing Extcoding options with msxdecframebuffering = 1 to reduce decode latency*/
	if  (  pInParams->numViews  ==  1  )  {
	    m_extCO.MaxDecFrameBuffering               = 1;

	    m_EncExtParams.push_back(reinterpret_cast<mfxExtBuffer*>(&m_extCO));
	}


	//
    if (m_mfxEncParams.mfx.RateControlMethod == MFX_RATECONTROL_CQP)
    {
        m_mfxEncParams.mfx.QPI = pInParams->nQPI;
        m_mfxEncParams.mfx.QPP = pInParams->nQPP;
        m_mfxEncParams.mfx.QPB = pInParams->nQPB;
    }
    m_mfxEncParams.mfx.NumSlice = pInParams->nNumSlice;
    ConvertFrameRate(pInParams->dFrameRate, &m_mfxEncParams.mfx.FrameInfo.FrameRateExtN, &m_mfxEncParams.mfx.FrameInfo.FrameRateExtD);
    m_mfxEncParams.mfx.EncodedOrder            = 0; // binary flag, 0 signals encoder to take frames in display order


    // specify memory type
    if (D3D9_MEMORY == pInParams->memType || D3D11_MEMORY == pInParams->memType)
    {
        m_mfxEncParams.IOPattern = MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }
    else
    {
        m_mfxEncParams.IOPattern = MFX_IOPATTERN_IN_SYSTEM_MEMORY;
    }

    // frame info parameters
    m_mfxEncParams.mfx.FrameInfo.FourCC       = MFX_FOURCC_NV12;
    m_mfxEncParams.mfx.FrameInfo.ChromaFormat = MFX_CHROMAFORMAT_YUV420;
    m_mfxEncParams.mfx.FrameInfo.PicStruct    = pInParams->nPicStruct;

    // set frame size and crops
    if(pInParams->CodecId==MFX_CODEC_HEVC && !memcmp(pInParams->pluginParams.pluginGuid.Data,MFX_PLUGINID_HEVCE_HW.Data,sizeof(MFX_PLUGINID_HEVCE_HW.Data)))
    {
        // In case of HW HEVC decoder width and height must be aligned to 32 pixels. This limitation is planned to be removed in later versions of plugin
        m_mfxEncParams.mfx.FrameInfo.Width  = MSDK_ALIGN32(pInParams->nDstWidth);
        m_mfxEncParams.mfx.FrameInfo.Height = MSDK_ALIGN32(pInParams->nDstHeight);
    }
    else
    {
        // width must be a multiple of 16
        // height must be a multiple of 16 in case of frame picture and a multiple of 32 in case of field picture
        m_mfxEncParams.mfx.FrameInfo.Width  = MSDK_ALIGN16(pInParams->nDstWidth);
        m_mfxEncParams.mfx.FrameInfo.Height = (MFX_PICSTRUCT_PROGRESSIVE == m_mfxEncParams.mfx.FrameInfo.PicStruct)?
            MSDK_ALIGN16(pInParams->nDstHeight) : MSDK_ALIGN32(pInParams->nDstHeight);
    }

    m_mfxEncParams.mfx.FrameInfo.CropX = 0;
    m_mfxEncParams.mfx.FrameInfo.CropY = 0;
    m_mfxEncParams.mfx.FrameInfo.CropW = pInParams->nDstWidth;
    m_mfxEncParams.mfx.FrameInfo.CropH = pInParams->nDstHeight;

    // we don't specify profile and level and let the encoder choose those basing on parameters
    // we must specify profile only for MVC codec
    if (MVC_ENABLED & m_MVCflags)
    {
        m_mfxEncParams.mfx.CodecProfile = MFX_PROFILE_AVC_STEREO_HIGH;
    }

    // configure and attach external parameters
    if (MVC_ENABLED & pInParams->MVC_flags)
        m_EncExtParams.push_back((mfxExtBuffer *)&m_MVCSeqDesc);

    if (MVC_VIEWOUTPUT & pInParams->MVC_flags)
    {
        // ViewOuput option requested
        m_CodingOption.ViewOutput = MFX_CODINGOPTION_ON;
        m_EncExtParams.push_back((mfxExtBuffer *)&m_CodingOption);
    }

    // configure the depth of the look ahead BRC if specified in command line
    if (pInParams->nLADepth || pInParams->nMaxSliceSize || pInParams->nBRefType)
    {
        m_CodingOption2.LookAheadDepth = pInParams->nLADepth;
        m_CodingOption2.MaxSliceSize   = pInParams->nMaxSliceSize;
        m_CodingOption2.BRefType = pInParams->nBRefType;
        m_EncExtParams.push_back((mfxExtBuffer *)&m_CodingOption2);
    }


    // In case of HEVC when height and/or width divided with 8 but not divided with 16
    // add extended parameter to increase performance
    if ( ( !((m_mfxEncParams.mfx.FrameInfo.CropW & 15 ) ^ 8 ) ||
           !((m_mfxEncParams.mfx.FrameInfo.CropH & 15 ) ^ 8 ) ) &&
             (m_mfxEncParams.mfx.CodecId == MFX_CODEC_HEVC) )
    {
        m_ExtHEVCParam.PicWidthInLumaSamples = m_mfxEncParams.mfx.FrameInfo.CropW;
        m_ExtHEVCParam.PicHeightInLumaSamples = m_mfxEncParams.mfx.FrameInfo.CropH;
        m_EncExtParams.push_back((mfxExtBuffer*)&m_ExtHEVCParam);
    }

    if (!m_EncExtParams.empty())
    {
        m_mfxEncParams.ExtParam = &m_EncExtParams[0]; // vector is stored linearly in memory
        m_mfxEncParams.NumExtParam = (mfxU16)m_EncExtParams.size();
    }

    // JPEG encoder settings overlap with other encoders settings in mfxInfoMFX structure
    if (MFX_CODEC_JPEG == pInParams->CodecId)
    {
        m_mfxEncParams.mfx.Interleaved = 1;
        m_mfxEncParams.mfx.Quality = pInParams->nQuality;
        m_mfxEncParams.mfx.RestartInterval = 0;
        MSDK_ZERO_MEMORY(m_mfxEncParams.mfx.reserved5);
    }

    m_mfxEncParams.AsyncDepth = pInParams->nAsyncDepth;

    return MFX_ERR_NONE;
}
#endif

//
//  Note: enc的纹理方案都出错了，解码后颜色变了。
//  Note: h265如果用上面那个2016/04/16的方案可以不变色。
//  比较后，发现如果mfxEncParams.mfx.FrameInfo.Width = MASK_ALIGN32()就可以保持颜色。
//  如果用MSDK_ALIGN16()就会出错。
//  可能是myCopyTex( )等函数没做好。
//  暂时先把压缩的纹理方案放弃，回头在说。
//  2017/10/13
 mfxStatus CMyUserPipeline::InitMfxEncParams(sInputParams *pParams)
 {
	 return  CEncodingPipeline::InitMfxEncParams(  pParams  );
 }




//
mfxStatus CMyUserPipeline::InitFileWriter(CSmplBitstreamWriter **ppWriter, const msdk_char *filename)
{
    MSDK_CHECK_ERROR(ppWriter, NULL, MFX_ERR_NULL_PTR);

    MSDK_SAFE_DELETE(*ppWriter);
    *ppWriter = new CMySmplBitstreamWriter;
    MSDK_CHECK_POINTER(*ppWriter, MFX_ERR_MEMORY_ALLOC);

	//
	CMySmplBitstreamWriter  *  pWriter  =  (  CMySmplBitstreamWriter  *  )*ppWriter;
	pWriter->m_var.m_pQdcObjInfoParam  =  m_var.pQdcObjInfo;


	//
    mfxStatus sts = (*ppWriter)->Init(filename);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    return sts;
}





//
#if  0  //  2016/04/16
mfxStatus CMyUserPipeline::iiInit(sInputParams *pParams)
{
    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);

	//  2015/10/04
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
	if  (  !pQdcObjInfo  )  {
		return  MFX_ERR_UNKNOWN;
	}
	this->m_FileReader.m_var.m_pQdcObjInfoParam  =  m_var.pQdcObjInfo;
	//  2015/10/29
	this->m_FileReader.m_var.pPipeline  =  this;
	this->m_FileReader.m_var.pf_CMySmplYUVReader_myLoadNextFrame_msdk  =  enc_CMySmplYUVReader_myLoadNextFrame_msdk;
	//
	//this->m_FileWriter.m_var.m_pQdcObjInfoParam  =  m_var.pQdcObjInfo;
	
	//
    mfxStatus sts = MFX_ERR_NONE;

    // prepare input file reader
    sts = m_FileReader.Init(pParams->strSrcFile,
                            pParams->ColorFormat,
                            pParams->numViews,
                            pParams->srcFileBuff);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    m_MVCflags = pParams->MVC_flags;

    sts = InitFileWriters(pParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    mfxVersion min_version;
    mfxVersion version;     // real API version with which library is initialized

    // we set version to 1.0 and later we will query actual version of the library which will got leaded
    min_version.Major = 1;
    min_version.Minor = 0;

	//
	//  2014/04/21
	switch  (  pQdcObjInfo->cfg.v.ucHardwareAccl  )  {
			case  CONST_hdAccl_auto:
				  pParams->bUseHWLib  =  IsHwAcclSupported(  &min_version  );
				  break;
			case  CONST_hdAccl_msdk_hardware:
				  pParams->bUseHWLib  =  TRUE;
				  break;
			case  CONST_hdAccl_msdk_software:
			default:
				  pParams->bUseHWLib  =  FALSE;
				  break;

	}

    // Init session
    if (pParams->bUseHWLib)
    {
        // try searching on all display adapters
        mfxIMPL impl = MFX_IMPL_HARDWARE_ANY;

        // if d3d11 surfaces are used ask the library to run acceleration through D3D11
        // feature may be unsupported due to OS or MSDK API version
        if (D3D11_MEMORY == pParams->memType)
            impl |= MFX_IMPL_VIA_D3D11;

        sts = m_mfxSession.Init(impl, &min_version);

        // MSDK API version may not support multiple adapters - then try initialize on the default
        if (MFX_ERR_NONE != sts)
           sts = m_mfxSession.Init((impl & (!MFX_IMPL_HARDWARE_ANY)) | MFX_IMPL_HARDWARE, &min_version);
    }
    else
        sts = m_mfxSession.Init(MFX_IMPL_SOFTWARE, &min_version);

    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    sts = MFXQueryVersion(m_mfxSession , &version); // get real API version of the loaded library
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

	//  2015/10/04
	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encV：bUseHWLib %d, ucHwAccl %d, ver %d.%d"  ),  pParams->bUseHWLib,  (  int  )pQdcObjInfo->cfg.v.ucHardwareAccl,  version.Major,  version.Minor  );
	tmp_showInfo(  tBuf  );
	
	//
    if ((pParams->MVC_flags & MVC_ENABLED) != 0 && !CheckVersion(&version, MSDK_FEATURE_MVC)) {
        msdk_printf(MSDK_STRING("error: MVC is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;

    }
    if ((pParams->MVC_flags & MVC_VIEWOUTPUT) != 0 && !CheckVersion(&version, MSDK_FEATURE_MVC_VIEWOUTPUT)) {
        msdk_printf(MSDK_STRING("error: MVC Viewoutput is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }
    if ((pParams->CodecId == MFX_CODEC_JPEG) && !CheckVersion(&version, MSDK_FEATURE_JPEG_ENCODE)) {
        msdk_printf(MSDK_STRING("error: Jpeg is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }

    if ((pParams->nRateControlMethod == MFX_RATECONTROL_LA) && !CheckVersion(&version, MSDK_FEATURE_LOOK_AHEAD)) {
        msdk_printf(MSDK_STRING("error: Look ahead is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }

    if (CheckVersion(&version, MSDK_FEATURE_PLUGIN_API)) {
        /* Here we actually define the following codec initialization scheme:
        *  1. If plugin path or guid is specified: we load user-defined plugin (example: HEVC encoder plugin)
        *  2. If plugin path not specified:
        *    2.a) we check if codec is distributed as a mediasdk plugin and load it if yes
        *    2.b) if codec is not in the list of mediasdk plugins, we assume, that it is supported inside mediasdk library
        */
        if (pParams->pluginParams.type == MFX_PLUGINLOAD_TYPE_FILE && strlen(pParams->pluginParams.strPluginPath))
        {
            m_pUserModule.reset(new MFXVideoUSER(m_mfxSession));
            m_pPlugin.reset(LoadPlugin(MFX_PLUGINTYPE_VIDEO_ENCODE, m_mfxSession, pParams->pluginParams.pluginGuid, 1, pParams->pluginParams.strPluginPath, (mfxU32)strlen(pParams->pluginParams.strPluginPath)));
            if (m_pPlugin.get() == NULL) sts = MFX_ERR_UNSUPPORTED;
        }
        else
        {
            if (AreGuidsEqual(pParams->pluginParams.pluginGuid, MSDK_PLUGINGUID_NULL))
            {
                mfxIMPL impl = pParams->bUseHWLib ? MFX_IMPL_HARDWARE : MFX_IMPL_SOFTWARE;
                pParams->pluginParams.pluginGuid = msdkGetPluginUID(impl, MSDK_VENCODE, pParams->CodecId);
            }
            if (!AreGuidsEqual(pParams->pluginParams.pluginGuid, MSDK_PLUGINGUID_NULL))
            {
                m_pPlugin.reset(LoadPlugin(MFX_PLUGINTYPE_VIDEO_ENCODE, m_mfxSession, pParams->pluginParams.pluginGuid, 1));
                if (m_pPlugin.get() == NULL) sts = MFX_ERR_UNSUPPORTED;
            }
        }
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    // set memory type
    m_memType = pParams->memType;

    // create and init frame allocator
    sts = CreateAllocator();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    sts = InitMfxEncParams(pParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    sts = InitMfxVppParams(pParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // MVC specific options
    if (MVC_ENABLED & m_MVCflags)
    {
        sts = AllocAndInitMVCSeqDesc();
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    // create encoder
    m_pmfxENC = new MFXVideoENCODE(m_mfxSession);
    MSDK_CHECK_POINTER(m_pmfxENC, MFX_ERR_MEMORY_ALLOC);

    // create preprocessor if resizing was requested from command line
    // or if different FourCC is set in InitMfxVppParams
    if (pParams->nWidth  != pParams->nDstWidth ||
        pParams->nHeight != pParams->nDstHeight ||
        m_mfxVppParams.vpp.In.FourCC != m_mfxVppParams.vpp.Out.FourCC)
    {
        m_pmfxVPP = new MFXVideoVPP(m_mfxSession);
        MSDK_CHECK_POINTER(m_pmfxVPP, MFX_ERR_MEMORY_ALLOC);
    }

    sts = ResetMFXComponents(pParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

	//  2015/10/30
	if (m_var.ucbUsingRender)
    {
		bool try_s3d  =  FALSE;	//  m_bIsMVC && (m_memType == D3D9_MEMORY);
        sts = CreateRenderingWindow(pParams, try_s3d);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }


    return MFX_ERR_NONE;
}
#endif




//  2016/04/16
#if  0
mfxStatus iiCMyUserPipeline::old_Init(sInputParams *pParams)
{
    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);

		//  2015/10/04
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
	if  (  !pQdcObjInfo  )  {
		return  MFX_ERR_UNKNOWN;
	}
	this->m_FileReader.m_var.m_pQdcObjInfoParam  =  m_var.pQdcObjInfo;
	//  2015/10/29
	this->m_FileReader.m_var.pPipeline  =  this;
	this->m_FileReader.m_var.pf_CMySmplYUVReader_myLoadNextFrame_msdk  =  enc_CMySmplYUVReader_myLoadNextFrame_msdk;




	//
    mfxStatus sts = MFX_ERR_NONE;

    // prepare input file reader
    sts = m_FileReader.Init(pParams->strSrcFile,
                            pParams->ColorFormat,
                            pParams->numViews,
                            pParams->srcFileBuff);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    m_MVCflags = pParams->MVC_flags;

    sts = InitFileWriters(pParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    mfxInitParam initPar;
    mfxVersion version;     // real API version with which library is initialized

    MSDK_ZERO_MEMORY(initPar);

    // we set version to 1.0 and later we will query actual version of the library which will got leaded
    initPar.Version.Major = 1;
    initPar.Version.Minor = 0;

    initPar.GPUCopy = pParams->gpuCopy;


		//
	//  2014/04/21
	switch  (  pQdcObjInfo->cfg.v.ucHardwareAccl  )  {
			case  CONST_hdAccl_auto:
				  pParams->bUseHWLib  =  IsHwAcclSupported(  &initPar.Version  );
				  break;
			case  CONST_hdAccl_msdk_hardware:
				  pParams->bUseHWLib  =  TRUE;
				  break;
			case  CONST_hdAccl_msdk_software:
			default:
				  pParams->bUseHWLib  =  FALSE;
				  break;

	}



    // Init session
    if (pParams->bUseHWLib) {
        // try searching on all display adapters
        initPar.Implementation = MFX_IMPL_HARDWARE_ANY;

        // if d3d11 surfaces are used ask the library to run acceleration through D3D11
        // feature may be unsupported due to OS or MSDK API version
        if (D3D11_MEMORY == pParams->memType)
            initPar.Implementation |= MFX_IMPL_VIA_D3D11;

        sts = m_mfxSession.InitEx(initPar);

        // MSDK API version may not support multiple adapters - then try initialize on the default
        if (MFX_ERR_NONE != sts) {
            initPar.Implementation = (initPar.Implementation & !MFX_IMPL_HARDWARE_ANY) | MFX_IMPL_HARDWARE;
            sts = m_mfxSession.InitEx(initPar);
        }
    } else {
        initPar.Implementation = MFX_IMPL_SOFTWARE;
        sts = m_mfxSession.InitEx(initPar);
    }

    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    sts = MFXQueryVersion(m_mfxSession , &version); // get real API version of the loaded library
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

		//  2015/10/04
	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encV: bUseHWLib %d, ucHwAccl %d, ver %d.%d"  ),  pParams->bUseHWLib,  (  int  )pQdcObjInfo->cfg.v.ucHardwareAccl,  version.Major,  version.Minor  );
	tmp_showInfo(  tBuf  );


	//
    if ((pParams->MVC_flags & MVC_ENABLED) != 0 && !CheckVersion(&version, MSDK_FEATURE_MVC)) {
        msdk_printf(MSDK_STRING("error: MVC is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;

    }
    if ((pParams->MVC_flags & MVC_VIEWOUTPUT) != 0 && !CheckVersion(&version, MSDK_FEATURE_MVC_VIEWOUTPUT)) {
        msdk_printf(MSDK_STRING("error: MVC Viewoutput is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }
    if ((pParams->CodecId == MFX_CODEC_JPEG) && !CheckVersion(&version, MSDK_FEATURE_JPEG_ENCODE)) {
        msdk_printf(MSDK_STRING("error: Jpeg is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }

    if ((pParams->nRateControlMethod == MFX_RATECONTROL_LA) && !CheckVersion(&version, MSDK_FEATURE_LOOK_AHEAD)) {
        msdk_printf(MSDK_STRING("error: Look ahead is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }

    if (CheckVersion(&version, MSDK_FEATURE_PLUGIN_API)) {
        /* Here we actually define the following codec initialization scheme:
        *  1. If plugin path or guid is specified: we load user-defined plugin (example: HEVC encoder plugin)
        *  2. If plugin path not specified:
        *    2.a) we check if codec is distributed as a mediasdk plugin and load it if yes
        *    2.b) if codec is not in the list of mediasdk plugins, we assume, that it is supported inside mediasdk library
        */
        if (pParams->pluginParams.type == MFX_PLUGINLOAD_TYPE_FILE && strlen(pParams->pluginParams.strPluginPath))
        {
            m_pUserModule.reset(new MFXVideoUSER(m_mfxSession));
            m_pPlugin.reset(LoadPlugin(MFX_PLUGINTYPE_VIDEO_ENCODE, m_mfxSession, pParams->pluginParams.pluginGuid, 1, pParams->pluginParams.strPluginPath, (mfxU32)strlen(pParams->pluginParams.strPluginPath)));
            if (m_pPlugin.get() == NULL) sts = MFX_ERR_UNSUPPORTED;
        }
        else
        {
            if (AreGuidsEqual(pParams->pluginParams.pluginGuid, MSDK_PLUGINGUID_NULL))
            {
                mfxIMPL impl = pParams->bUseHWLib ? MFX_IMPL_HARDWARE : MFX_IMPL_SOFTWARE;
                pParams->pluginParams.pluginGuid = msdkGetPluginUID(impl, MSDK_VENCODE, pParams->CodecId);
            }
            if (!AreGuidsEqual(pParams->pluginParams.pluginGuid, MSDK_PLUGINGUID_NULL))
            {
                m_pPlugin.reset(LoadPlugin(MFX_PLUGINTYPE_VIDEO_ENCODE, m_mfxSession, pParams->pluginParams.pluginGuid, 1));
                if (m_pPlugin.get() == NULL) sts = MFX_ERR_UNSUPPORTED;
            }
            if(sts==MFX_ERR_UNSUPPORTED)
            {
                msdk_printf(MSDK_STRING("Default plugin cannot be loaded (possibly you have to define plugin explicitly)\n"));
            }
        }
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    // set memory type
    m_memType = pParams->memType;

    // create and init frame allocator
    sts = CreateAllocator();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    sts = InitMfxEncParams(pParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    sts = InitMfxVppParams(pParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // MVC specific options
    if (MVC_ENABLED & m_MVCflags)
    {
        sts = AllocAndInitMVCSeqDesc();
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    // create encoder
    m_pmfxENC = new MFXVideoENCODE(m_mfxSession);
    MSDK_CHECK_POINTER(m_pmfxENC, MFX_ERR_MEMORY_ALLOC);

    // create preprocessor if resizing was requested from command line
    // or if different FourCC is set in InitMfxVppParams
    if (pParams->nWidth  != pParams->nDstWidth ||
        pParams->nHeight != pParams->nDstHeight ||
        m_mfxVppParams.vpp.In.FourCC != m_mfxVppParams.vpp.Out.FourCC)
    {
        m_pmfxVPP = new MFXVideoVPP(m_mfxSession);
        MSDK_CHECK_POINTER(m_pmfxVPP, MFX_ERR_MEMORY_ALLOC);
    }

    sts = ResetMFXComponents(pParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);


	//  2015/10/30
	if (m_var.ucbUsingRender)
    {
		bool try_s3d  =  FALSE;	//  m_bIsMVC && (m_memType == D3D9_MEMORY);
        sts = CreateRenderingWindow(pParams, try_s3d);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }



	//
    return MFX_ERR_NONE;
}
#endif


//
mfxStatus CMyUserPipeline::Init(sInputParams *pParams)
{
    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);
	
	//  2015/10/04
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
	if  (  !pQdcObjInfo  )  {
		return  MFX_ERR_UNKNOWN;
	}
	this->m_FileReader.m_var.m_pQdcObjInfoParam  =  m_var.pQdcObjInfo;
	//  2015/10/29
	this->m_FileReader.m_var.pPipeline  =  this;
	this->m_FileReader.m_var.pf_CMySmplYUVReader_myLoadNextFrame_msdk  =  enc_CMySmplYUVReader_myLoadNextFrame_msdk;





	//
    mfxStatus sts = MFX_ERR_NONE;

#if defined ENABLE_V4L2_SUPPORT
    isV4L2InputEnabled = pParams->isV4L2InputEnabled;
#endif

    m_MVCflags = pParams->MVC_flags;

    // FileReader can convert yv12->nv12 without vpp
    m_InputFourCC = (pParams->FileInputFourCC == MFX_FOURCC_I420) ? MFX_FOURCC_NV12 : pParams->FileInputFourCC;

    m_nTimeout = pParams->nTimeout;

    mfxInitParam initPar;
    mfxVersion version;     // real API version with which library is initialized

    MSDK_ZERO_MEMORY(initPar);

    // we set version to 1.0 and later we will query actual version of the library which will got leaded
    initPar.Version.Major = 1;
    initPar.Version.Minor = 0;

    initPar.GPUCopy = pParams->gpuCopy;

	//
			//
	//  2014/04/21
	switch  (  pQdcObjInfo->cfg.v.ucHardwareAccl  )  {
			case  CONST_hdAccl_auto:
				  pParams->bUseHWLib  =  IsHwAcclSupported(  &initPar.Version  );
				  break;
			case  CONST_hdAccl_msdk_hardware:
				  pParams->bUseHWLib  =  TRUE;
				  break;
			case  CONST_hdAccl_msdk_software:
			default:
				  pParams->bUseHWLib  =  FALSE;
				  break;

	}





    // Init session
    if (pParams->bUseHWLib) {
        // try searching on all display adapters
        initPar.Implementation = MFX_IMPL_HARDWARE_ANY;

        // if d3d11 surfaces are used ask the library to run acceleration through D3D11
        // feature may be unsupported due to OS or MSDK API version
        if (D3D11_MEMORY == pParams->memType)
            initPar.Implementation |= MFX_IMPL_VIA_D3D11;

        // Library should pick first available compatible adapter during InitEx call with MFX_IMPL_HARDWARE_ANY
        sts = m_mfxSession.InitEx(initPar);
    }
    else
    {
        initPar.Implementation = MFX_IMPL_SOFTWARE;
        sts = m_mfxSession.InitEx(initPar);
    }

    MSDK_CHECK_STATUS(sts, "m_mfxSession.InitEx failed");

    sts = MFXQueryVersion(m_mfxSession , &version); // get real API version of the loaded library
    MSDK_CHECK_STATUS(sts, "MFXQueryVersion failed");

			//  2015/10/04
	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encV: bUseHWLib %d, ucHwAccl %d, ver %d.%d"  ),  pParams->bUseHWLib,  (  int  )pQdcObjInfo->cfg.v.ucHardwareAccl,  version.Major,  version.Minor  );
	tmp_showInfo(  tBuf  );


	//
    if ((pParams->MVC_flags & MVC_ENABLED) != 0 && !CheckVersion(&version, MSDK_FEATURE_MVC)) {
        msdk_printf(MSDK_STRING("error: MVC is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;

    }
    if ((pParams->MVC_flags & MVC_VIEWOUTPUT) != 0 && !CheckVersion(&version, MSDK_FEATURE_MVC_VIEWOUTPUT)) {
        msdk_printf(MSDK_STRING("error: MVC Viewoutput is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }
    if ((pParams->CodecId == MFX_CODEC_JPEG) && !CheckVersion(&version, MSDK_FEATURE_JPEG_ENCODE)) {
        msdk_printf(MSDK_STRING("error: Jpeg is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }

    if ((pParams->nRateControlMethod == MFX_RATECONTROL_LA) && !CheckVersion(&version, MSDK_FEATURE_LOOK_AHEAD)) {
        msdk_printf(MSDK_STRING("error: Look ahead is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }

    if (CheckVersion(&version, MSDK_FEATURE_PLUGIN_API)) {
        /* Here we actually define the following codec initialization scheme:
        *  1. If plugin path or guid is specified: we load user-defined plugin (example: HEVC encoder plugin)
        *  2. If plugin path not specified:
        *    2.a) we check if codec is distributed as a mediasdk plugin and load it if yes
        *    2.b) if codec is not in the list of mediasdk plugins, we assume, that it is supported inside mediasdk library
        */
        if (pParams->pluginParams.type == MFX_PLUGINLOAD_TYPE_FILE && msdk_strnlen(pParams->pluginParams.strPluginPath,sizeof(pParams->pluginParams.strPluginPath)))
        {
            m_pUserModule.reset(new MFXVideoUSER(m_mfxSession));
            m_pPlugin.reset(LoadPlugin(MFX_PLUGINTYPE_VIDEO_ENCODE, m_mfxSession, pParams->pluginParams.pluginGuid, 1, pParams->pluginParams.strPluginPath, (mfxU32)msdk_strnlen(pParams->pluginParams.strPluginPath,sizeof(pParams->pluginParams.strPluginPath))));
            if (m_pPlugin.get() == NULL) sts = MFX_ERR_UNSUPPORTED;
        }
        else
        {
            bool isDefaultPlugin = false;
            if (AreGuidsEqual(pParams->pluginParams.pluginGuid, MSDK_PLUGINGUID_NULL))
            {
                mfxIMPL impl = pParams->bUseHWLib ? MFX_IMPL_HARDWARE : MFX_IMPL_SOFTWARE;
                pParams->pluginParams.pluginGuid = msdkGetPluginUID(impl, MSDK_VENCODE, pParams->CodecId);
                isDefaultPlugin = true;
            }
            if (!AreGuidsEqual(pParams->pluginParams.pluginGuid, MSDK_PLUGINGUID_NULL))
            {
                m_pPlugin.reset(LoadPlugin(MFX_PLUGINTYPE_VIDEO_ENCODE, m_mfxSession, pParams->pluginParams.pluginGuid, 1));
                if (m_pPlugin.get() == NULL) sts = MFX_ERR_UNSUPPORTED;
            }
            if(sts==MFX_ERR_UNSUPPORTED)
            {
                msdk_printf(isDefaultPlugin ?
                    MSDK_STRING("Default plugin cannot be loaded (possibly you have to define plugin explicitly)\n")
                    : MSDK_STRING("Explicitly specified plugin cannot be loaded.\n"));
            }
        }
        MSDK_CHECK_STATUS(sts, "LoadPlugin failed");
    }

    // create encoder
    m_pmfxENC = new MFXVideoENCODE(m_mfxSession);
    MSDK_CHECK_POINTER(m_pmfxENC, MFX_ERR_MEMORY_ALLOC);

    // create preprocessor if resizing was requested from command line
    // or if different FourCC is set
    if (pParams->nWidth  != pParams->nDstWidth ||
        pParams->nHeight != pParams->nDstHeight ||
        FileFourCC2EncFourCC(pParams->FileInputFourCC) != pParams->EncodeFourCC)
    {
        m_pmfxVPP = new MFXVideoVPP(m_mfxSession);
        MSDK_CHECK_POINTER(m_pmfxVPP, MFX_ERR_MEMORY_ALLOC);
    }

    // Determine if we should shift P010 surfaces
    pParams->shouldUseShiftedP010VPP = m_pmfxVPP && pParams->memType != SYSTEM_MEMORY &&
        pParams->FileInputFourCC == MFX_FOURCC_P010;

    pParams->shouldUseShiftedP010Enc = pParams->memType != SYSTEM_MEMORY &&
        pParams->FileInputFourCC == MFX_FOURCC_P010 &&
        AreGuidsEqual(pParams->pluginParams.pluginGuid, MFX_PLUGINID_HEVCE_HW);
    bool readerShift = m_pmfxVPP ? pParams->shouldUseShiftedP010VPP  : pParams->shouldUseShiftedP010Enc;

    if(readerShift)
    {
        msdk_printf(MSDK_STRING("P010 frames data will be shifted to MSB area to be compatible with HEVC HW input format\n"));
    }

    if(m_pmfxVPP && pParams->shouldUseShiftedP010Enc && !pParams->shouldUseShiftedP010Enc && pParams->bUseHWLib)
    {
        msdk_printf(MSDK_STRING("ERROR: Encoder requires P010 LSB format. VPP currently supports only MSB encoding for P010 format. Sample cannot combine both of them in one pipeline.\n"));
        return MFX_ERR_UNSUPPORTED;
    }

    // Preparing readers and writers
    if (!isV4L2InputEnabled)
    {
        // prepare input file reader
        sts = m_FileReader.Init(pParams->InputFiles,
            pParams->FileInputFourCC,readerShift);
        MSDK_CHECK_STATUS(sts, "m_FileReader.Init failed");
    }

    sts = InitFileWriters(pParams);
    MSDK_CHECK_STATUS(sts, "InitFileWriters failed");


    // set memory type
    m_memType = pParams->memType;
    m_nMemBuffer = pParams->nMemBuf;

    // create and init frame allocator
    sts = CreateAllocator();
    MSDK_CHECK_STATUS(sts, "CreateAllocator failed");

    sts = InitMfxEncParams(pParams);
    MSDK_CHECK_STATUS(sts, "InitMfxEncParams failed");

    sts = InitMfxVppParams(pParams);
    MSDK_CHECK_STATUS(sts, "InitMfxVppParams failed");

    // MVC specific options
    if (MVC_ENABLED & m_MVCflags)
    {
        sts = AllocAndInitMVCSeqDesc();
        MSDK_CHECK_STATUS(sts, "AllocAndInitMVCSeqDesc failed");
    }

    sts = ResetMFXComponents(pParams);
    MSDK_CHECK_STATUS(sts, "ResetMFXComponents failed");

    InitV4L2Pipeline(pParams);

    m_nFramesToProcess = pParams->nNumFrames;

    // If output isn't specified work in performance mode and do not insert idr
    m_bCutOutput = pParams->dstFileBuff.size() ? !pParams->bUncut : false;

    // Dumping components configuration if required
    if(*pParams->DumpFileName)
    {
        CParametersDumper::DumpLibraryConfiguration(pParams->DumpFileName, NULL, m_pmfxVPP, m_pmfxENC, NULL, &m_mfxVppParams,&m_mfxEncParams);
    }

	//  2015/10/30
	if (m_var.ucbUsingRender)
    {
		bool try_s3d  =  FALSE;	//  m_bIsMVC && (m_memType == D3D9_MEMORY);
        sts = CreateRenderingWindow(pParams, try_s3d);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }


	//
    return MFX_ERR_NONE;
}



//////////////////////////////
//
#if  0  //  2017/10/07
mfxStatus iiCMyUserPipeline::Run()
{
    MSDK_CHECK_POINTER(m_pmfxENC, MFX_ERR_NOT_INITIALIZED);

    mfxStatus sts = MFX_ERR_NONE;

    mfxFrameSurface1* pSurf = NULL; // dispatching pointer

    sTask *pCurrentTask = NULL; // a pointer to the current task
    mfxU16 nEncSurfIdx = 0;     // index of free surface for encoder input (vpp output)
    mfxU16 nVppSurfIdx = 0;     // index of free surface for vpp input

    mfxSyncPoint VppSyncPoint = NULL; // a sync point associated with an asynchronous vpp call
    bool bVppMultipleOutput = false;  // this flag is true if VPP produces more frames at output
                                      // than consumes at input. E.g. framerate conversion 30 fps -> 60 fps


    // Since in sample we support just 2 views
    // we will change this value between 0 and 1 in case of MVC
    mfxU16 currViewNum = 0;

    sts = MFX_ERR_NONE;

    // main loop, preprocessing and encoding
    while (MFX_ERR_NONE <= sts || MFX_ERR_MORE_DATA == sts)
    {
        // get a pointer to a free task (bit stream and sync point for encoder)
        sts = GetFreeTask(&pCurrentTask);
        MSDK_BREAK_ON_ERROR(sts);

        // find free surface for encoder input
        nEncSurfIdx = GetFreeSurface(m_pEncSurfaces, m_EncResponse.NumFrameActual);
        MSDK_CHECK_ERROR(nEncSurfIdx, MSDK_INVALID_SURF_IDX, MFX_ERR_MEMORY_ALLOC);

        // point pSurf to encoder surface
        pSurf = &m_pEncSurfaces[nEncSurfIdx];
        if (!bVppMultipleOutput)
        {
            // if vpp is enabled find free surface for vpp input and point pSurf to vpp surface
            if (m_pmfxVPP)
            {
                nVppSurfIdx = GetFreeSurface(m_pVppSurfaces, m_VppResponse.NumFrameActual);
                MSDK_CHECK_ERROR(nVppSurfIdx, MSDK_INVALID_SURF_IDX, MFX_ERR_MEMORY_ALLOC);

                pSurf = &m_pVppSurfaces[nVppSurfIdx];
            }

            // load frame from file to surface data
			//
			if  (  m_var.ucbUsing_sharedTex  )  {  //  2015/10/30
				if  (  !m_bExternalAlloc  )  {
					tmp_showInfo(  _T(  "encV: pipeline::run failed, m_bExternalAlloc is false"  )  );
					return  MFX_ERR_UNKNOWN;
				}
				
				//
				pSurf->Info.FrameId.ViewId = currViewNum;
		        sts = m_FileReader.LoadNextFrame(pSurf);
		        MSDK_BREAK_ON_ERROR(sts);
		        if (MVC_ENABLED & m_MVCflags) currViewNum ^= 1; // Flip between 0 and 1 for ViewId

				//
				}
			else  {
				//
	            // if we share allocator with Media SDK we need to call Lock to access surface data and...
		        if (m_bExternalAlloc)
		        {
			        // get YUV pointers
				    sts = m_pMFXAllocator->Lock(m_pMFXAllocator->pthis, pSurf->Data.MemId, &(pSurf->Data));
			        MSDK_BREAK_ON_ERROR(sts);
		        }

		        pSurf->Info.FrameId.ViewId = currViewNum;
		        sts = m_FileReader.LoadNextFrame(pSurf);
		        MSDK_BREAK_ON_ERROR(sts);
		        if (MVC_ENABLED & m_MVCflags) currViewNum ^= 1; // Flip between 0 and 1 for ViewId
						
				// ... after we're done call Unlock
			    if (m_bExternalAlloc)
	            {
		            sts = m_pMFXAllocator->Unlock(m_pMFXAllocator->pthis, pSurf->Data.MemId, &(pSurf->Data));
			        MSDK_BREAK_ON_ERROR(sts);
			    }
				//
			}
        }

        // perform preprocessing if required
        if (m_pmfxVPP)
        {
            bVppMultipleOutput = false; // reset the flag before a call to VPP
            for (;;)
            {
                sts = m_pmfxVPP->RunFrameVPPAsync(&m_pVppSurfaces[nVppSurfIdx], &m_pEncSurfaces[nEncSurfIdx],
                    NULL, &VppSyncPoint);

                if (MFX_ERR_NONE < sts && !VppSyncPoint) // repeat the call if warning and no output
                {
                    if (MFX_WRN_DEVICE_BUSY == sts)
                        MSDK_SLEEP(1); // wait if device is busy
                }
                else if (MFX_ERR_NONE < sts && VppSyncPoint)
                {
                    sts = MFX_ERR_NONE; // ignore warnings if output is available
                    break;
                }
                else
                    break; // not a warning
            }

            // process errors
            if (MFX_ERR_MORE_DATA == sts)
            {
                continue;
            }
            else if (MFX_ERR_MORE_SURFACE == sts)
            {
                bVppMultipleOutput = true;
            }
            else
            {
                MSDK_BREAK_ON_ERROR(sts);
            }
        }

        // save the id of preceding vpp task which will produce input data for the encode task
        if (VppSyncPoint)
        {
            pCurrentTask->DependentVppTasks.push_back(VppSyncPoint);
            VppSyncPoint = NULL;
        }

        for (;;)
        {
			//  2015/10/04
			mfxEncodeCtrl  *  pEncCtrl  =  NULL;
			mfxEncodeCtrl  tmpEncCtrl;
			if  (  m_var.pQdcObjInfo  )  {
				QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
				if  (  pQdcObjInfo->var.encInfo.bNeed_forceKeyFrame  )  {		
					DWORD  dwTickCnt  =  GetTickCount(  );
					if  (  dwTickCnt  -   pQdcObjInfo->var.encInfo.dwLastTickCnt_insertKeyFrame  >  1000  )  {
						pQdcObjInfo->var.encInfo.dwLastTickCnt_insertKeyFrame  =  dwTickCnt;
						//
						tmp_showInfo(  _T(  "hdEnc: insertKeyFrame"  )  );			
						//
						memset(  &tmpEncCtrl,  0,  sizeof(  tmpEncCtrl  )  );
						tmpEncCtrl.FrameType = MFX_FRAMETYPE_I | MFX_FRAMETYPE_IDR | MFX_FRAMETYPE_REF;
						pEncCtrl  =  &tmpEncCtrl;
					}		
				}
			}

            // at this point surface for encoder contains either a frame from file or a frame processed by vpp
            sts = m_pmfxENC->EncodeFrameAsync(pEncCtrl, &m_pEncSurfaces[nEncSurfIdx], &pCurrentTask->mfxBS, &pCurrentTask->EncSyncP);

            if (MFX_ERR_NONE < sts && !pCurrentTask->EncSyncP) // repeat the call if warning and no output
            {
                if (MFX_WRN_DEVICE_BUSY == sts)
                    MSDK_SLEEP(1); // wait if device is busy
            }
            else if (MFX_ERR_NONE < sts && pCurrentTask->EncSyncP)
            {
                sts = MFX_ERR_NONE; // ignore warnings if output is available
                break;
            }
            else if (MFX_ERR_NOT_ENOUGH_BUFFER == sts)
            {
                sts = AllocateSufficientBuffer(&pCurrentTask->mfxBS);
                MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
            }
            else
            {
                // get next surface and new task for 2nd bitstream in ViewOutput mode
                MSDK_IGNORE_MFX_STS(sts, MFX_ERR_MORE_BITSTREAM);
                break;
            }
        }
    }

    // means that the input file has ended, need to go to buffering loops
    MSDK_IGNORE_MFX_STS(sts, MFX_ERR_MORE_DATA);
    // exit in case of other errors
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    if (m_pmfxVPP)
    {
        // loop to get buffered frames from vpp
        while (MFX_ERR_NONE <= sts || MFX_ERR_MORE_DATA == sts || MFX_ERR_MORE_SURFACE == sts)
            // MFX_ERR_MORE_SURFACE can be returned only by RunFrameVPPAsync
            // MFX_ERR_MORE_DATA is accepted only from EncodeFrameAsync
        {
            // find free surface for encoder input (vpp output)
            nEncSurfIdx = GetFreeSurface(m_pEncSurfaces, m_EncResponse.NumFrameActual);
            MSDK_CHECK_ERROR(nEncSurfIdx, MSDK_INVALID_SURF_IDX, MFX_ERR_MEMORY_ALLOC);

            for (;;)
            {
                sts = m_pmfxVPP->RunFrameVPPAsync(NULL, &m_pEncSurfaces[nEncSurfIdx], NULL, &VppSyncPoint);

                if (MFX_ERR_NONE < sts && !VppSyncPoint) // repeat the call if warning and no output
                {
                    if (MFX_WRN_DEVICE_BUSY == sts)
                        MSDK_SLEEP(1); // wait if device is busy
                }
                else if (MFX_ERR_NONE < sts && VppSyncPoint)
                {
                    sts = MFX_ERR_NONE; // ignore warnings if output is available
                    break;
                }
                else
                    break; // not a warning
            }

            if (MFX_ERR_MORE_SURFACE == sts)
            {
                continue;
            }
            else
            {
                MSDK_BREAK_ON_ERROR(sts);
            }

            // get a free task (bit stream and sync point for encoder)
            sts = GetFreeTask(&pCurrentTask);
            MSDK_BREAK_ON_ERROR(sts);

            // save the id of preceding vpp task which will produce input data for the encode task
            if (VppSyncPoint)
            {
                pCurrentTask->DependentVppTasks.push_back(VppSyncPoint);
                VppSyncPoint = NULL;
            }

            for (;;)
            {
                sts = m_pmfxENC->EncodeFrameAsync(NULL, &m_pEncSurfaces[nEncSurfIdx], &pCurrentTask->mfxBS, &pCurrentTask->EncSyncP);

                if (MFX_ERR_NONE < sts && !pCurrentTask->EncSyncP) // repeat the call if warning and no output
                {
                    if (MFX_WRN_DEVICE_BUSY == sts)
                        MSDK_SLEEP(1); // wait if device is busy
                }
                else if (MFX_ERR_NONE < sts && pCurrentTask->EncSyncP)
                {
                    sts = MFX_ERR_NONE; // ignore warnings if output is available
                    break;
                }
                else if (MFX_ERR_NOT_ENOUGH_BUFFER == sts)
                {
                    sts = AllocateSufficientBuffer(&pCurrentTask->mfxBS);
                    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
                }
                else
                {
                    // get next surface and new task for 2nd bitstream in ViewOutput mode
                    MSDK_IGNORE_MFX_STS(sts, MFX_ERR_MORE_BITSTREAM);
                    break;
                }
            }
        }

        // MFX_ERR_MORE_DATA is the correct status to exit buffering loop with
        // indicates that there are no more buffered frames
        MSDK_IGNORE_MFX_STS(sts, MFX_ERR_MORE_DATA);
        // exit in case of other errors
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    // loop to get buffered frames from encoder
    while (MFX_ERR_NONE <= sts)
    {
        // get a free task (bit stream and sync point for encoder)
        sts = GetFreeTask(&pCurrentTask);
        MSDK_BREAK_ON_ERROR(sts);

        for (;;)
        {
            sts = m_pmfxENC->EncodeFrameAsync(NULL, NULL, &pCurrentTask->mfxBS, &pCurrentTask->EncSyncP);

            if (MFX_ERR_NONE < sts && !pCurrentTask->EncSyncP) // repeat the call if warning and no output
            {
                if (MFX_WRN_DEVICE_BUSY == sts)
                    MSDK_SLEEP(1); // wait if device is busy
            }
            else if (MFX_ERR_NONE < sts && pCurrentTask->EncSyncP)
            {
                sts = MFX_ERR_NONE; // ignore warnings if output is available
                break;
            }
            else if (MFX_ERR_NOT_ENOUGH_BUFFER == sts)
            {
                sts = AllocateSufficientBuffer(&pCurrentTask->mfxBS);
                MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
            }
            else
            {
                // get new task for 2nd bitstream in ViewOutput mode
                MSDK_IGNORE_MFX_STS(sts, MFX_ERR_MORE_BITSTREAM);
                break;
            }
        }
        MSDK_BREAK_ON_ERROR(sts);
    }

    // MFX_ERR_MORE_DATA is the correct status to exit buffering loop with
    // indicates that there are no more buffered frames
    MSDK_IGNORE_MFX_STS(sts, MFX_ERR_MORE_DATA);
    // exit in case of other errors
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // synchronize all tasks that are left in task pool
    while (MFX_ERR_NONE == sts)
    {
        sts = m_TaskPool.SynchronizeFirstTask();
    }

    // MFX_ERR_NOT_FOUND is the correct status to exit the loop with
    // EncodeFrameAsync and SyncOperation don't return this status
    MSDK_IGNORE_MFX_STS(sts, MFX_ERR_NOT_FOUND);
    // report any errors that occurred in asynchronous part
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    return sts;
}
#endif


//
mfxStatus CMyUserPipeline::LoadNextFrame(mfxFrameSurface1* pSurf)
{


    mfxStatus sts = MFX_ERR_NONE;

    if (isV4L2InputEnabled)
        return MFX_ERR_NONE;

    m_bTimeOutExceed = (m_nTimeout < m_statOverall.GetDeltaTime()) ? true : false;

    if (m_nMemBuffer)
    {
        // memoty buffer mode. No file reading required
        bool bMemBufExceed = !(m_nFramesRead % m_nMemBuffer) && m_nFramesRead;
        if (m_bTimeOutExceed && bMemBufExceed )
        {
            sts = MFX_ERR_MORE_DATA;
        }
        else if (bMemBufExceed)
        {
            // Rewrite outupt file and insert idr frame
            m_bFileWriterReset = m_bCutOutput;
            m_bInsertIDR = m_bCutOutput;
        }
    }
    else
    {
        // read frame from file
        if (m_bExternalAlloc)
        {
			//
			if  (  m_var.ucbUsing_sharedTex  )  {  //  2017/10/09
				
				//
				sts = m_FileReader.LoadNextFrame(pSurf);
		        

				}
			else  {

				//
	            mfxStatus sts1 = m_pMFXAllocator->Lock(m_pMFXAllocator->pthis, pSurf->Data.MemId, &(pSurf->Data));
	            MSDK_CHECK_STATUS(sts1, "m_pMFXAllocator->Lock failed");

	            sts = m_FileReader.LoadNextFrame(pSurf);

	            sts1 = m_pMFXAllocator->Unlock(m_pMFXAllocator->pthis, pSurf->Data.MemId, &(pSurf->Data));
	            MSDK_CHECK_STATUS(sts1, "m_pMFXAllocator->Unlock failed");
			
			//
			}
        }
        else
        {
            sts = m_FileReader.LoadNextFrame(pSurf);
        }

        if ( (MFX_ERR_MORE_DATA == sts) && !m_bTimeOutExceed )
        {
            m_FileReader.Reset();
            m_bFileWriterReset = m_bCutOutput;
            // forcedly insert idr frame to make output file readable
            m_bInsertIDR = m_bCutOutput;
            return sts;
        }
    }

    m_nFramesRead++;




	//
		if  (  m_var.pQdcObjInfo  )  {
				QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
				if  (  pQdcObjInfo->var.encInfo.bNeed_forceKeyFrame  )  {		
					DWORD  dwTickCnt  =  myGetTickCount(  0  );
					if  (  dwTickCnt  -   pQdcObjInfo->var.encInfo.dwLastTickCnt_insertKeyFrame1  >  1000  )  {
						pQdcObjInfo->var.encInfo.dwLastTickCnt_insertKeyFrame1  =  dwTickCnt;
						//
						tmp_showInfo(  _T(  "hdEnc: insertKeyFrame"  )  );			
						//
						m_bInsertIDR  =  TRUE;
					}		
				}
			}


	//
	return  sts;

}





/////////
int  CMyUserPipeline::CMySmplYUVReader_myLoadNextFrame_msdk(  unsigned  short  usPktResType,  void  *  p0_pInput,  void  *  p1_uiInputSize,  PARAM_CMySmplYUVReader_myLoadNextFrame_msdk  *  pParam  )
{
	//

#if MFX_D3D11_SUPPORT

	CMyD3D11Device  *  pDevice  =  (  CMyD3D11Device  *  )this->m_hwdev;

	mfxFrameAllocator * pAlloc  =  m_pMFXAllocator;
	if  (  pDevice->CMySmplYUVReader_myLoadNextFrame_msdk(  usPktResType,  p0_pInput,  p1_uiInputSize,  pParam,  pAlloc  )  )  {
		return  -1;
	}

	return  0;
#else
	return  -1;
#endif
}


//  2015/10/30
mfxStatus CMyUserPipeline::CreateHWDevice()
{
#if D3D_SURFACES_SUPPORT
    mfxStatus sts = MFX_ERR_NONE;

    HWND window = NULL;
    bool render = m_var.ucbUsingRender;	//  (m_eWorkMode == MODE_RENDERING);

    if (render) {
        window = (D3D11_MEMORY == m_memType) ? NULL : m_d3dRender.GetWindowHandle();
    }

#if MFX_D3D11_SUPPORT
    if (D3D11_MEMORY == m_memType)  {
        m_hwdev = new CMyD3D11Device();
		//  2015/09/30
		(  (  CMyD3D11Device  *  )m_hwdev  )->m_var.pMyPipeline  =  this;
		}
    else
#endif // #if MFX_D3D11_SUPPORT
        m_hwdev = new CD3D9Device();

    if (NULL == m_hwdev)
        return MFX_ERR_MEMORY_ALLOC;

    if (render && m_bIsMVC && m_memType == D3D9_MEMORY) {
        sts = m_hwdev->SetHandle((mfxHandleType)MFX_HANDLE_GFXS3DCONTROL, m_pS3DControl);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }
    sts = m_hwdev->Init(
        window,
        render ? (m_bIsMVC ? 2 : 1) : 0,
        MSDKAdapter::GetNumber(m_mfxSession));
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    if (render)
        m_d3dRender.SetHWDevice(m_hwdev);
#elif LIBVA_SUPPORT
    mfxStatus sts = MFX_ERR_NONE;
    m_hwdev = CreateVAAPIDevice();

    if (NULL == m_hwdev) {
        return MFX_ERR_MEMORY_ALLOC;
    }

    sts = m_hwdev->Init(NULL, (m_eWorkMode == MODE_RENDERING) ? 1 : 0, MSDKAdapter::GetNumber(m_mfxSession));
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
#endif
    return MFX_ERR_NONE;
}




//  2015/10/30
mfxStatus CMyUserPipeline::CreateRenderingWindow(sInputParams *pParams, bool try_s3d)
{
    mfxStatus sts = MFX_ERR_NONE;

#if D3D_SURFACES_SUPPORT
#if  0
    if (try_s3d) {

        m_pS3DControl = CreateIGFXS3DControl();
        MSDK_CHECK_POINTER(m_pS3DControl, MFX_ERR_DEVICE_FAILED);

        // check if s3d supported and get a list of supported display modes
        IGFX_S3DCAPS caps;
        MSDK_ZERO_MEMORY(caps);
        HRESULT hr = m_pS3DControl->GetS3DCaps(&caps);
        if (FAILED(hr) || 0 >= caps.ulNumEntries) {
            MSDK_SAFE_DELETE(m_pS3DControl);
            return MFX_ERR_DEVICE_FAILED;
        }

        // switch to 3D mode
        ULONG max = 0;
        MSDK_CHECK_POINTER(caps.S3DSupportedModes, MFX_ERR_NOT_INITIALIZED);
        for (ULONG i = 0; i < caps.ulNumEntries; i++) {
            if (caps.S3DSupportedModes[max] < caps.S3DSupportedModes[i])
                max = i;
        }

        if (0 == pParams->nWallCell) {
            hr = m_pS3DControl->SwitchTo3D(&caps.S3DSupportedModes[max]);
            if (FAILED(hr)) {
                MSDK_SAFE_DELETE(m_pS3DControl);
                return MFX_ERR_DEVICE_FAILED;
            }
        }
    }
#endif
    sWindowParams windowParams;

    windowParams.lpWindowName = MSDK_STRING(  "encV"  );	//  pParams->bWallNoTitle ? NULL : MSDK_STRING("sample_decode");
    windowParams.nx           = 0;	//  pParams->nWallW;
    windowParams.ny           = 0;	//  pParams->nWallH;
	windowParams.nWidth       = pParams->nWidth;	//  m_mfxVideoParams.mfx.FrameInfo.Width;
	windowParams.nHeight      = pParams->nHeight;	//  m_mfxVideoParams.mfx.FrameInfo.Height;
    windowParams.ncell        = 0;	//pParams->nWallCell;
    windowParams.nAdapter     = 0;	//pParams->nWallMonitor;

    windowParams.lpClassName  = MSDK_STRING("Render Window Class");
    windowParams.dwStyle      = WS_OVERLAPPEDWINDOW;
    windowParams.hWndParent   = NULL;
    windowParams.hMenu        = NULL;
    windowParams.hInstance    = GetModuleHandle(NULL);
    windowParams.lpParam      = NULL;
    windowParams.bFullScreen  = FALSE;

    sts = m_d3dRender.Init(windowParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    //setting videowall flag
#if  0
    m_bIsVideoWall = 0 != windowParams.nx;
    //setting timeout value
    if (m_bIsVideoWall && (pParams->nWallTimeout>0)) m_nTimeout = pParams->nWallTimeout;
#endif

#endif
    return sts;
}

