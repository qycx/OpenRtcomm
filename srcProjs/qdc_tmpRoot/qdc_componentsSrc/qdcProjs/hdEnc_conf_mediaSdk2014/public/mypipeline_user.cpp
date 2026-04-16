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



 

CMyUserPipeline::CMyUserPipeline() : VideoConfPipeline()
{
#if  0
    m_pRotateSurfaces = NULL; 
    ZERO_MEMORY(m_usrRotateParams);        
    ZERO_MEMORY(m_RotateResponse);
#endif
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CMyUserPipeline::~CMyUserPipeline()
{
    Close();
}


mfxStatus  CMyUserPipeline::Init(IInitParams *  pParams)
{
	//  mfxStatus		sts			=	MFX_ERR_UNKNOWN;
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
	if  (  !pQdcObjInfo  )  {
		return  MFX_ERR_UNKNOWN;
	}
	this->m_FileReader.m_var.m_pQdcObjInfoParam  =  m_var.pQdcObjInfo;
	this->m_FileWriter.m_var.m_pQdcObjInfoParam  =  m_var.pQdcObjInfo;


	//
    mfxStatus sts = MFX_ERR_NONE;
    VideoConfParams * pVConfParams = dynamic_cast<VideoConfParams *>(pParams);
    MSDK_CHECK_POINTER(pVConfParams, MFX_ERR_NULL_PTR);

    m_initParams = *pVConfParams;

    // prepare input file reader
#if  0
    sts = m_FileReader.Init(pVConfParams->sources[0].srcFile.c_str(),
                            MFX_FOURCC_YV12,
                            0,
                            std::vector<msdk_char*>());

    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
#endif
	//  2017/10/07
	return  MFX_ERR_UNKNOWN;

    // prepare output file writer
    sts = m_FileWriter.Init(pVConfParams->dstFile.c_str());
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
	


    APIChangeFeatures features = {};
    features.IntraRefresh = (pVConfParams->nRefrType == 1);
    mfxVersion version = getMinimalRequiredVersion(features);

	//
	//
	switch  (  pQdcObjInfo->cfg.v.ucHardwareAccl  )  {
			case  CONST_hdAccl_auto:
				  pVConfParams->bUseHWLib  =  IsHwAcclSupported(  &version  );
				  break;
			case  CONST_hdAccl_msdk_hardware:
				  pVConfParams->bUseHWLib  =  TRUE;
				  break;
			case  CONST_hdAccl_msdk_software:
			default:
				  pVConfParams->bUseHWLib  =  FALSE;
				  break;

	}

	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encV£ºbUseHWLib %d, ucHwAccl %d, ver %d.%d"  ),  pVConfParams->bUseHWLib,  (  int  )pQdcObjInfo->cfg.v.ucHardwareAccl,  version.Major,  version.Minor  );
	tmp_showInfo(  tBuf  );

	    // init session
	mfxIMPL impl = pVConfParams->bUseHWLib ? MFX_IMPL_HARDWARE : MFX_IMPL_SOFTWARE;

	
	//
    if (MFX_IMPL_HARDWARE == impl)
    {
        // try searching on all display adapters
        sts = m_mfxSession.Init(MFX_IMPL_HARDWARE_ANY, &version);
    }
    else
        sts = m_mfxSession.Init(MFX_IMPL_SOFTWARE, &version);

    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
	
	// set memory type
    m_memType = pVConfParams->memType;

    sts = InitMfxEncParamsLowLatency();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    InitFrameInfo(m_initParams.sources[0].nWidth, m_initParams.sources[0].nHeight);

    sts = InitTemporalScalability();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    //initialize own or mediasdk's
    InitBrc();

    //init intra refresh
    InitIntraRefresh();

    // create and init frame allocator , and alloc frames
    sts = CreateAllocator();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // create encoder
    m_encoder.reset(new MFXVideoENCODE(m_mfxSession));

    sts = InitMFXComponents();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    m_nFramesProcessed = 0;
    m_pCtrl = 0;
    m_extBuffers.clear();

    return MFX_ERR_NONE;
}


//
int  CMyUserPipeline::MakeSPSPPS(  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize  )
{
	int		iErr	=	-1;

#if  10

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
		//  mfxStatus sts = this->m_pmfxENC->GetVideoParam(&par);
		mfxStatus sts = this->m_encoder->GetVideoParam(&par);
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

#endif

	//
	iErr  =  0;

errLabel:
	return  iErr;
}







 mfxStatus CMyUserPipeline::Run()
{
		QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;


    mfxStatus sts = MFX_ERR_NONE;
    bool bPulRemaining = false;

    // main loop, preprocessing and encoding
    while (MFX_ERR_NONE <= sts || (MFX_ERR_MORE_DATA == sts && !bPulRemaining))
    {
        //applying all scenario actions for current frame
        std::vector<IAction*> actions;
        m_initParams.pActionProc->GetActionsForFrame(m_nFramesProcessed, actions);
        for (size_t j = 0; j < actions.size(); j++)
        {
            sts = actions[j]->ApplyFeedBack(this);
            MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
        }

        mfxFrameSurface1* pSurf = NULL;

        //reading to new surface until file end
        if (!bPulRemaining)
        {
            // find free surface for encoder input
            sts = GetFreeSurface(pSurf);
            MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

            // load frame from file to surface data
            // if we share allocator with Media SDK we need to call Lock to access surface data and after we're done call Unlock
            // get YUV pointers
            sts = m_pMFXAllocator->Lock(m_pMFXAllocator->pthis, pSurf->Data.MemId, &(pSurf->Data));
            MSDK_BREAK_ON_ERROR(sts);

            mfxStatus sts2 = m_FileReader.LoadNextFrame(pSurf);

            sts = m_pMFXAllocator->Unlock(m_pMFXAllocator->pthis, pSurf->Data.MemId, &(pSurf->Data));

            MSDK_BREAK_ON_ERROR(sts);

			//  2014/07/05. added by wxr
			if  (  sts2  )  {
				sts  =  sts2;
				tmp_showInfo(  _T(  "hdEnc_conf: fileReader returns err"  )  );
				MSDK_BREAK_ON_ERROR(sts);
			}

            //file end error
            if (MFX_ERR_MORE_DATA == sts2)
            {
                bPulRemaining = true;
                pSurf = NULL;
            }
            else
            {
                MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

                //surface data ready, for reference list selection it is required that frameorder for every frame specified
                pSurf->Data.FrameOrder = m_nFramesProcessed;
            }
        }

		//  2014/08/25
		if  (  pQdcObjInfo->var.encInfo.bNeed_forceKeyFrame  )  {
			DWORD  dwTickCnt  =  GetTickCount(  );
			if  (  dwTickCnt  -   pQdcObjInfo->var.encInfo.dwLastTickCnt_insertKeyFrame  >  1000  )  {
				pQdcObjInfo->var.encInfo.dwLastTickCnt_insertKeyFrame  =  dwTickCnt;
				//
				tmp_showInfo(  _T(  "hdEnc_conf: insertKeyFrame"  )  );			
				//
				this->InsertKeyFrame(  );
			}
		}


		//
        sts = EncodeFrame(pSurf);
    }

    // MFX_ERR_MORE_DATA is the correct status to exit the loop with
    MSDK_IGNORE_MFX_STS(sts, MFX_ERR_MORE_DATA);
    // report any errors that occurred in asynchronous part
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    return sts;
}


 //  2014/08/25
 mfxStatus CMyUserPipeline::InitMfxEncParamsLowLatency()
{
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
	if  (  !pQdcObjInfo  )  {
		return  MFX_ERR_UNKNOWN;
	}

	mfxU16  tmp_gopPicSize  =  gopLength;
	tmp_gopPicSize  =  DEFAULT_keyDistanceInS  *  pQdcObjInfo->cfg.v.usMaxFps_toShareBmp;
#ifdef  _DEBUG
		//  tmp_gopPicSize  =  30  *  pQdcObjInfo->cfg.usMaxFps_toShareBmp;
#endif
	tmp_gopPicSize  =  max(  tmp_gopPicSize,  gopLength  );
	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "encV: InitMfxencParams... gopPicSize %d"  ),  tmp_gopPicSize  );
	tmp_showInfo(  tBuf  );

	//
    MSDK_ZERO_MEMORY(m_mfxEncParams);

    m_mfxEncParams.mfx.CodecId                 = MFX_CODEC_AVC;//video conferencing features available only for AVC
    m_mfxEncParams.mfx.GopPicSize              = tmp_gopPicSize;	//  gopLength;//gop length should be enough to consume bitrate
    m_mfxEncParams.mfx.GopRefDist              = 1;//Distance between I- or P- key frames (1 means no B-frames)
    m_mfxEncParams.AsyncDepth                  = 1;//internal buffering should be disabled in encode

    /*Initializing Extcoding options with msxdecframebuffering = 1 to reduce decode latency*/
    m_extCO.MaxDecFrameBuffering               = 1;
    //turn on reference picture marking repetition SEI
    m_extCO.RefPicMarkRep = (mfxU16)(m_initParams.bRPMRS ? MFX_CODINGOPTION_ON : MFX_CODINGOPTION_OFF);

    m_extBuffers.push_back(reinterpret_cast<mfxExtBuffer*>(&m_extCO));

    //num ref frames doesn't affect latency
    //while ref lists management feature (for recovery from broken frames) needs at least several frames to be in the ref list, 5 is good enough
    m_mfxEncParams.mfx.NumRefFrame             = 5;

    ConvertFrameRate(m_initParams.sources[0].dFrameRate, &m_mfxEncParams.mfx.FrameInfo.FrameRateExtN, &m_mfxEncParams.mfx.FrameInfo.FrameRateExtD);

    // specify memory type
    if (D3D9_MEMORY == m_memType)    
    {
        m_mfxEncParams.IOPattern = MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }
    else
    {
        m_mfxEncParams.IOPattern = MFX_IOPATTERN_IN_SYSTEM_MEMORY;
    }

    return MFX_ERR_NONE;
}
















