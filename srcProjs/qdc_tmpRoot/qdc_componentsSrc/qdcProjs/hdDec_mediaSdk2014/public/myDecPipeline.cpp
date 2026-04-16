

#if defined(_WIN32) || defined(_WIN64)
#include <tchar.h>
#include <windows.h>
#endif
#include <numeric>
#include <ctime>
#include <algorithm>
#include "pipeline_decode.h"
#include "sysmem_allocator.h"
//#include "../../sample_user_modules/plugin_api/plugin_loader.h"

#if defined(_WIN32) || defined(_WIN64)
#include "d3d_allocator.h"
#include "d3d11_allocator.h"
#include "d3d_device.h"
#include "d3d11_device.h"
#endif

#if defined LIBVA_SUPPORT
#include "vaapi_allocator.h"
#include "vaapi_device.h"
#endif



#include	"myutils.h"
#include "pipeline_decode.h"
#include "sysmem_allocator.h"

//#include "../../sample_user_modules/plugin_api/plugin_loader.h"


#include	"qdcOpenCommon.h"
#include	"myDecPipeline.h"

#include	"qisCompressProc.h"
#include	"myFunc_mediaSdk.h"
#include	"tmpGuiOpenFunc.h"

#include	"myD3d11_device.h"

//
const mfxU8 HEVC_DECODER_UID[] = {0x15,0xdd,0x93,0x68,0x25,0xad,0x47,0x5e,0xa3,0x4e,0x35,0xf3,0xf5,0x42,0x17,0xa6};


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




////

CMyDecPipeline::CMyDecPipeline():CDecodingPipeline(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CMyDecPipeline::~CMyDecPipeline()
{
	//  DecodingPipeline的close()不能调用2次，所以，要在decodingPipeline::~decodingPipe()里去掉Close
	Close();
}



#if  0
//  2015/09/27
mfxStatus CMyDecPipeline::iiInit(sInputParams *pParams)
{
	//
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
	if  (  !pQdcObjInfo  )  {
		return  MFX_ERR_UNKNOWN;
	}
	DEBUG_step_dec	*	pDebugStepDec  =  (  DEBUG_step_dec  *  )tmp_getDebugStep_sth(  0,  CONST_debugStepType_dec,  pQdcObjInfo->var.pDebugStep  );
	if  (  !pDebugStepDec  )  return  (mfxStatus  )-1;

	//
	pDebugStepDec->bCalled_pipeline_Init  =  TRUE;
	

	//
    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);

    mfxStatus sts = MFX_ERR_NONE;

    // prepare input stream file reader
    // for VP8 complete and single frame reader is a requirement
    // create reader that supports completeframe mode for latency oriented scenarios
    if (pParams->bLowLat || pParams->bCalLat)
    {
        switch (pParams->videoType)
        {
        case MFX_CODEC_HEVC:
        case MFX_CODEC_AVC:
            //m_FileReader.reset(new CH264FrameReader());
			m_FileReader.reset(new  CMySmplBitstreamReader());
			//
            //m_bIsCompleteFrame = true;
			//
            m_bPrintLatency = pParams->bCalLat;
			//
			{
				if  (  !m_FileReader.get(  )  )  return  MFX_ERR_UNKNOWN;
				CMySmplBitstreamReader	&m_FileReader1  =  *(CMySmplBitstreamReader*)m_FileReader.get();
				memset(  &m_FileReader1.m_var.inputInfo,  0,  sizeof(  m_FileReader1.m_var.inputInfo  )  );
				m_FileReader1.m_var.m_pQdcObjInfoParam  =  m_var.pQdcObjInfo;
			}
			//
            break;
        case MFX_CODEC_JPEG:
            m_FileReader.reset(new CJPEGFrameReader());
            m_bIsCompleteFrame = true;
            m_bPrintLatency = pParams->bCalLat;
            break;
        case CODEC_VP8:
            m_FileReader.reset(new CIVFFrameReader());
            m_bIsCompleteFrame = true;
            m_bPrintLatency = pParams->bCalLat;
            break;
        default:
            return MFX_ERR_UNSUPPORTED; // latency mode is supported only for H.264 and JPEG codecs
        }
    }
    else
    {
        switch (pParams->videoType)
        {
        case CODEC_VP8:
            m_FileReader.reset(new CIVFFrameReader());
            break;
        default:
            m_FileReader.reset(new CSmplBitstreamReader());
            break;
        }
    }

    m_memType = pParams->memType;
    m_nMaxFps = pParams->nMaxFPS;
    m_nFrames = pParams->nFrames ? pParams->nFrames : MFX_INFINITE;

    if (MFX_CODEC_CAPTURE != pParams->videoType)
    {
        sts = m_FileReader->Init(pParams->strSrcFile);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    mfxInitParam initPar;
    mfxExtThreadsParam threadsPar;
    mfxExtBuffer* extBufs[1];
    mfxVersion version;     // real API version with which library is initialized

    MSDK_ZERO_MEMORY(initPar);
    MSDK_ZERO_MEMORY(threadsPar);

    // we set version to 1.0 and later we will query actual version of the library which will got leaded
    initPar.Version.Major = 1;
    initPar.Version.Minor = 0;

    init_ext_buffer(threadsPar);

    bool needInitExtPar = false;

    if (pParams->nThreadsNum) {
        threadsPar.NumThread = pParams->nThreadsNum;
        needInitExtPar = true;
    }
    if (pParams->SchedulingType) {
        threadsPar.SchedulingType = pParams->SchedulingType;
        needInitExtPar = true;
    }
    if (pParams->Priority) {
        threadsPar.Priority = pParams->Priority;
        needInitExtPar = true;
    }
    if (needInitExtPar) {
        extBufs[0] = (mfxExtBuffer*)&threadsPar;
        initPar.ExtParam = extBufs;
        initPar.NumExtParam = 1;
    }


	//  2015/09/27
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


	//  2015/09/27		
	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "decV: bUseHWLib %d, ucHwAccl %d, ver %d.%d, pktResType %d"  ),  pParams->bUseHWLib,  (  int  )pQdcObjInfo->cfg.v.ucHardwareAccl,  version.Major,  version.Minor,  (  int  )pQdcObjInfo->var.usPktResType_dec  );
	tmp_showInfo(  tBuf  );
	
	//
    if (pParams->bIsMVC && !CheckVersion(&version, MSDK_FEATURE_MVC)) {
        msdk_printf(MSDK_STRING("error: MVC is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;

    }
    if ((pParams->videoType == MFX_CODEC_JPEG) && !CheckVersion(&version, MSDK_FEATURE_JPEG_DECODE)) {
        msdk_printf(MSDK_STRING("error: Jpeg is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }
    if (pParams->bLowLat && !CheckVersion(&version, MSDK_FEATURE_LOW_LATENCY)) {
        msdk_printf(MSDK_STRING("error: Low Latency mode is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }

    // create decoder
    m_pmfxDEC = new MFXVideoDECODE(m_mfxSession);
    MSDK_CHECK_POINTER(m_pmfxDEC, MFX_ERR_MEMORY_ALLOC);

    // set video type in parameters
    m_mfxVideoParams.mfx.CodecId = pParams->videoType;

    // prepare bit stream
    if (MFX_CODEC_CAPTURE != pParams->videoType)
    {
        sts = InitMfxBitstream(&m_mfxBS, 1024 * 1024);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    if (CheckVersion(&version, MSDK_FEATURE_PLUGIN_API)) {
        /* Here we actually define the following codec initialization scheme:
        *  1. If plugin path or guid is specified: we load user-defined plugin (example: VP8 sample decoder plugin)
        *  2. If plugin path not specified:
        *    2.a) we check if codec is distributed as a mediasdk plugin and load it if yes
        *    2.b) if codec is not in the list of mediasdk plugins, we assume, that it is supported inside mediasdk library
        */
        // Load user plug-in, should go after CreateAllocator function (when all callbacks were initialized)
        if (pParams->pluginParams.type == MFX_PLUGINLOAD_TYPE_FILE && strlen(pParams->pluginParams.strPluginPath))
        {
            m_pUserModule.reset(new MFXVideoUSER(m_mfxSession));
            if (pParams->videoType == CODEC_VP8 || pParams->videoType == MFX_CODEC_HEVC)
            {
                m_pPlugin.reset(LoadPlugin(MFX_PLUGINTYPE_VIDEO_DECODE, m_mfxSession, pParams->pluginParams.pluginGuid, 1, pParams->pluginParams.strPluginPath, (mfxU32)strlen(pParams->pluginParams.strPluginPath)));
            }
            if (m_pPlugin.get() == NULL) sts = MFX_ERR_UNSUPPORTED;
        }
        else
        {
            if (AreGuidsEqual(pParams->pluginParams.pluginGuid, MSDK_PLUGINGUID_NULL))
            {
                mfxIMPL impl = pParams->bUseHWLib ? MFX_IMPL_HARDWARE : MFX_IMPL_SOFTWARE;
                pParams->pluginParams.pluginGuid = msdkGetPluginUID(impl, MSDK_VDECODE, pParams->videoType);
            }
            if (!AreGuidsEqual(pParams->pluginParams.pluginGuid, MSDK_PLUGINGUID_NULL))
            {
                m_pPlugin.reset(LoadPlugin(MFX_PLUGINTYPE_VIDEO_DECODE, m_mfxSession, pParams->pluginParams.pluginGuid, 1));
                if (m_pPlugin.get() == NULL) sts = MFX_ERR_UNSUPPORTED;
            }
        }
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    // Populate parameters. Involves DecodeHeader call
    sts = InitMfxParams(pParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    m_eWorkMode = pParams->mode;
    if (m_eWorkMode == MODE_FILE_DUMP) {
        // prepare YUV file writer
        sts = m_FileWriter.Init(pParams->strDstFile, pParams->numViews);
    } else if ((m_eWorkMode != MODE_PERFORMANCE) && (m_eWorkMode != MODE_RENDERING)) {
        msdk_printf(MSDK_STRING("error: unsupported work mode\n"));
        sts = MFX_ERR_UNSUPPORTED;
    }
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // create device and allocator
    sts = CreateAllocator();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // in case of HW accelerated decode frames must be allocated prior to decoder initialization
    sts = AllocFrames();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    sts = m_pmfxDEC->Init(&m_mfxVideoParams);
    if (MFX_WRN_PARTIAL_ACCELERATION == sts)
    {
        msdk_printf(MSDK_STRING("WARNING: partial acceleration\n"));
        MSDK_IGNORE_MFX_STS(sts, MFX_WRN_PARTIAL_ACCELERATION);
    }
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    if (m_eWorkMode == MODE_RENDERING)
    {
        sts = CreateRenderingWindow(pParams, m_bIsMVC && (m_memType == D3D9_MEMORY));
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

		//  2015/09/30
		sts = m_FileWriter.Init(pParams->strDstFile, pParams->numViews);
		if  (  sts  )  {
			return  MFX_ERR_UNKNOWN;
		}

    }

    return sts;
}
#endif



//  2016/04/16
#if  0
mfxStatus iiCMyDecPipeline::Init(sInputParams *pParams)
{
		//  2016/04/16
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
	if  (  !pQdcObjInfo  )  {
		return  MFX_ERR_UNKNOWN;
	}
	DEBUG_step_dec	*	pDebugStepDec  =  (  DEBUG_step_dec  *  )tmp_getDebugStep_sth(  0,  CONST_debugStepType_dec,  pQdcObjInfo->var.pDebugStep  );
	if  (  !pDebugStepDec  )  return  (mfxStatus  )-1;

	//
	pDebugStepDec->bCalled_pipeline_Init  =  TRUE;
	


	//
    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);

    mfxStatus sts = MFX_ERR_NONE;

    // prepare input stream file reader
    // for VP8 complete and single frame reader is a requirement
    // create reader that supports completeframe mode for latency oriented scenarios
    if (pParams->bLowLat || pParams->bCalLat)
    {
        switch (pParams->videoType)
        {
        case MFX_CODEC_HEVC:
        case MFX_CODEC_AVC:
            //m_FileReader.reset(new CH264FrameReader());
            //m_bIsCompleteFrame = true;
			//
			m_FileReader.reset(new  CMySmplBitstreamReader());
			//
            m_bPrintLatency = pParams->bCalLat;

			//
			{
				if  (  !m_FileReader.get(  )  )  return  MFX_ERR_UNKNOWN;
				CMySmplBitstreamReader	&m_FileReader1  =  *(CMySmplBitstreamReader*)m_FileReader.get();
				memset(  &m_FileReader1.m_var.inputInfo,  0,  sizeof(  m_FileReader1.m_var.inputInfo  )  );
				m_FileReader1.m_var.m_pQdcObjInfoParam  =  m_var.pQdcObjInfo;
			}

            break;
        case MFX_CODEC_JPEG:
            m_FileReader.reset(new CJPEGFrameReader());
            m_bIsCompleteFrame = true;
            m_bPrintLatency = pParams->bCalLat;
            break;
        case CODEC_VP8:
            m_FileReader.reset(new CIVFFrameReader());
            m_bIsCompleteFrame = true;
            m_bPrintLatency = pParams->bCalLat;
            break;
        default:
            return MFX_ERR_UNSUPPORTED; // latency mode is supported only for H.264 and JPEG codecs
        }
    }
    else
    {
        switch (pParams->videoType)
        {
        case CODEC_VP8:
            m_FileReader.reset(new CIVFFrameReader());
            break;
        default:
            m_FileReader.reset(new CSmplBitstreamReader());
            break;
        }
    }

    if (pParams->fourcc)
        m_fourcc = pParams->fourcc;

#ifdef LIBVA_SUPPORT
    if(pParams->bPerfMode)
        m_bPerfMode = true;
#endif

    if (pParams->Width)
        m_vppOutWidth = pParams->Width;
    if (pParams->Height)
        m_vppOutHeight = pParams->Height;


    m_memType = pParams->memType;

    m_nMaxFps = pParams->nMaxFPS;
    m_nFrames = pParams->nFrames ? pParams->nFrames : MFX_INFINITE;

    if (MFX_CODEC_CAPTURE != pParams->videoType)
    {
        sts = m_FileReader->Init(pParams->strSrcFile);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    mfxInitParam initPar;
    mfxExtThreadsParam threadsPar;
    mfxExtBuffer* extBufs[1];
    mfxVersion version;     // real API version with which library is initialized

    MSDK_ZERO_MEMORY(initPar);
    MSDK_ZERO_MEMORY(threadsPar);

    // we set version to 1.0 and later we will query actual version of the library which will got leaded
    initPar.Version.Major = 1;
    initPar.Version.Minor = 0;

    initPar.GPUCopy = pParams->gpuCopy;

    init_ext_buffer(threadsPar);

    bool needInitExtPar = false;

    if (pParams->eDeinterlace)
    {
        m_diMode = pParams->eDeinterlace;
    }

    if (pParams->nThreadsNum) {
        threadsPar.NumThread = pParams->nThreadsNum;
        needInitExtPar = true;
    }
    if (pParams->SchedulingType) {
        threadsPar.SchedulingType = pParams->SchedulingType;
        needInitExtPar = true;
    }
    if (pParams->Priority) {
        threadsPar.Priority = pParams->Priority;
        needInitExtPar = true;
    }
    if (needInitExtPar) {
        extBufs[0] = (mfxExtBuffer*)&threadsPar;
        initPar.ExtParam = extBufs;
        initPar.NumExtParam = 1;
    }


	//  2015/09/27
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

    sts = m_mfxSession.QueryVersion(&version); // get real API version of the loaded library
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    sts = m_mfxSession.QueryIMPL(&m_impl); // get actual library implementation
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

	//
	//  2015/09/27		
	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "decV: bUseHWLib %d, ucHwAccl %d, ver %d.%d, pktResType %d"  ),  pParams->bUseHWLib,  (  int  )pQdcObjInfo->cfg.v.ucHardwareAccl,  version.Major,  version.Minor,  (  int  )pQdcObjInfo->var.usPktResType_dec  );
	tmp_showInfo(  tBuf  );


	//
    if (pParams->bIsMVC && !CheckVersion(&version, MSDK_FEATURE_MVC)) {
        msdk_printf(MSDK_STRING("error: MVC is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;

    }
    if ((pParams->videoType == MFX_CODEC_JPEG) && !CheckVersion(&version, MSDK_FEATURE_JPEG_DECODE)) {
        msdk_printf(MSDK_STRING("error: Jpeg is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }
    if (pParams->bLowLat && !CheckVersion(&version, MSDK_FEATURE_LOW_LATENCY)) {
        msdk_printf(MSDK_STRING("error: Low Latency mode is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }

    if (pParams->eDeinterlace &&
        (pParams->eDeinterlace != MFX_DEINTERLACING_ADVANCED) &&
        (pParams->eDeinterlace != MFX_DEINTERLACING_BOB) )
    {
        msdk_printf(MSDK_STRING("error: Unsupported deinterlace value: %d\n"), pParams->eDeinterlace);
        return MFX_ERR_UNSUPPORTED;
    }

    if (pParams->bRenderWin) {
        m_bRenderWin = pParams->bRenderWin;
        // note: currently position is unsupported for Wayland
#if !defined(LIBVA_WAYLAND_SUPPORT)
        m_nRenderWinX = pParams->nRenderWinX;
        m_nRenderWinY = pParams->nRenderWinY;
#endif
    }

    // create decoder
    m_pmfxDEC = new MFXVideoDECODE(m_mfxSession);
    MSDK_CHECK_POINTER(m_pmfxDEC, MFX_ERR_MEMORY_ALLOC);

    // set video type in parameters
    m_mfxVideoParams.mfx.CodecId = pParams->videoType;

    // prepare bit stream
    if (MFX_CODEC_CAPTURE != pParams->videoType)
    {
        sts = InitMfxBitstream(&m_mfxBS, 1024 * 1024);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    if (CheckVersion(&version, MSDK_FEATURE_PLUGIN_API)) {
        /* Here we actually define the following codec initialization scheme:
        *  1. If plugin path or guid is specified: we load user-defined plugin (example: VP8 sample decoder plugin)
        *  2. If plugin path not specified:
        *    2.a) we check if codec is distributed as a mediasdk plugin and load it if yes
        *    2.b) if codec is not in the list of mediasdk plugins, we assume, that it is supported inside mediasdk library
        */
        // Load user plug-in, should go after CreateAllocator function (when all callbacks were initialized)
        if (pParams->pluginParams.type == MFX_PLUGINLOAD_TYPE_FILE && strlen(pParams->pluginParams.strPluginPath))
        {
            m_pUserModule.reset(new MFXVideoUSER(m_mfxSession));
            if (pParams->videoType == CODEC_VP8 || pParams->videoType == MFX_CODEC_HEVC)
            {
                m_pPlugin.reset(LoadPlugin(MFX_PLUGINTYPE_VIDEO_DECODE, m_mfxSession, pParams->pluginParams.pluginGuid, 1, pParams->pluginParams.strPluginPath, (mfxU32)strlen(pParams->pluginParams.strPluginPath)));
            }
            if (m_pPlugin.get() == NULL) sts = MFX_ERR_UNSUPPORTED;
        }
        else
        {
            if (AreGuidsEqual(pParams->pluginParams.pluginGuid, MSDK_PLUGINGUID_NULL))
            {
                mfxIMPL impl = pParams->bUseHWLib ? MFX_IMPL_HARDWARE : MFX_IMPL_SOFTWARE;
                pParams->pluginParams.pluginGuid = msdkGetPluginUID(impl, MSDK_VDECODE, pParams->videoType);
            }
            if (!AreGuidsEqual(pParams->pluginParams.pluginGuid, MSDK_PLUGINGUID_NULL))
            {
                m_pPlugin.reset(LoadPlugin(MFX_PLUGINTYPE_VIDEO_DECODE, m_mfxSession, pParams->pluginParams.pluginGuid, 1));
                if (m_pPlugin.get() == NULL) sts = MFX_ERR_UNSUPPORTED;
            }
            if(sts==MFX_ERR_UNSUPPORTED)
            {
                msdk_printf(MSDK_STRING("Default plugin cannot be loaded (possibly you have to define plugin explicitly)\n"));
            }
        }
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    // Populate parameters. Involves DecodeHeader call
    sts = InitMfxParams(pParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    if (m_bVppIsUsed)
        m_bDecOutSysmem = pParams->bUseHWLib ? false : true;
    else
        m_bDecOutSysmem = pParams->memType == SYSTEM_MEMORY;

    if (m_bVppIsUsed)
    {
        m_pmfxVPP = new MFXVideoVPP(m_mfxSession);
        if (!m_pmfxVPP) return MFX_ERR_MEMORY_ALLOC;
    }

    m_eWorkMode = pParams->mode;
    if (m_eWorkMode == MODE_FILE_DUMP) {
        // prepare YUV file writer
        sts = m_FileWriter.Init(pParams->strDstFile, pParams->numViews);
    } else if ((m_eWorkMode != MODE_PERFORMANCE) && (m_eWorkMode != MODE_RENDERING)) {
        msdk_printf(MSDK_STRING("error: unsupported work mode\n"));
        sts = MFX_ERR_UNSUPPORTED;
    }
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    m_monitorType = pParams->monitorType;
    // create device and allocator
#if defined(LIBVA_SUPPORT)
    m_libvaBackend = pParams->libvaBackend;
#endif // defined(MFX_LIBVA_SUPPORT)

    sts = CreateAllocator();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // in case of HW accelerated decode frames must be allocated prior to decoder initialization
    sts = AllocFrames();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    sts = m_pmfxDEC->Init(&m_mfxVideoParams);
    if (MFX_WRN_PARTIAL_ACCELERATION == sts)
    {
        msdk_printf(MSDK_STRING("WARNING: partial acceleration\n"));
        MSDK_IGNORE_MFX_STS(sts, MFX_WRN_PARTIAL_ACCELERATION);
    }
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    if (m_bVppIsUsed)
    {
        if (m_diMode)
            m_mfxVppVideoParams.vpp.Out.PicStruct = MFX_PICSTRUCT_PROGRESSIVE;

        sts = m_pmfxVPP->Init(&m_mfxVppVideoParams);
        if (MFX_WRN_PARTIAL_ACCELERATION == sts)
        {
            msdk_printf(MSDK_STRING("WARNING: partial acceleration\n"));
            MSDK_IGNORE_MFX_STS(sts, MFX_WRN_PARTIAL_ACCELERATION);
        }
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    sts = m_pmfxDEC->GetVideoParam(&m_mfxVideoParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    if (m_eWorkMode == MODE_RENDERING)
    {
        sts = CreateRenderingWindow(pParams, m_bIsMVC && (m_memType == D3D9_MEMORY));
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);


		//  2015/09/30
		sts = m_FileWriter.Init(pParams->strDstFile, pParams->numViews);
		if  (  sts  )  {
			return  MFX_ERR_UNKNOWN;
		}


    }

    return sts;
}
#endif

//  2017/10/08
//
mfxStatus CMyDecPipeline::Init(sInputParams *pParams)
{
	//  2016/04/16
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
	if  (  !pQdcObjInfo  )  {
		return  MFX_ERR_UNKNOWN;
	}
	DEBUG_step_dec	*	pDebugStepDec  =  (  DEBUG_step_dec  *  )tmp_getDebugStep_sth(  0,  CONST_debugStepType_dec,  pQdcObjInfo->var.pDebugStep  );
	if  (  !pDebugStepDec  )  return  (mfxStatus  )-1;

	//
	pDebugStepDec->bCalled_pipeline_Init  =  TRUE;
	


	//
    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);

    mfxStatus sts = MFX_ERR_NONE;

    // prepare input stream file reader
    // for VP8 complete and single frame reader is a requirement
    // create reader that supports completeframe mode for latency oriented scenarios
    if (pParams->bLowLat || pParams->bCalLat)
    {
        switch (pParams->videoType)
        {
        case MFX_CODEC_AVC:
            //m_FileReader.reset(new CH264FrameReader());
            //m_bIsCompleteFrame = true;

			//
			m_FileReader.reset(new  CMySmplBitstreamReader());
			
			//
            m_bPrintLatency = pParams->bCalLat;

			//
			{
				if  (  !m_FileReader.get(  )  )  return  MFX_ERR_UNKNOWN;
				CMySmplBitstreamReader	&m_FileReader1  =  *(CMySmplBitstreamReader*)m_FileReader.get();
				memset(  &m_FileReader1.m_var.inputInfo,  0,  sizeof(  m_FileReader1.m_var.inputInfo  )  );
				m_FileReader1.m_var.m_pQdcObjInfoParam  =  m_var.pQdcObjInfo;
			}

            break;
        case MFX_CODEC_JPEG:
            m_FileReader.reset(new CJPEGFrameReader());
            m_bIsCompleteFrame = true;
            m_bPrintLatency = pParams->bCalLat;
            break;
        case MFX_CODEC_VP8:
        case MFX_CODEC_VP9:
            m_FileReader.reset(new CIVFFrameReader());
            m_bIsCompleteFrame = true;
            m_bPrintLatency = pParams->bCalLat;
            break;
        default:
            return MFX_ERR_UNSUPPORTED; // latency mode is supported only for H.264 and JPEG codecs
        }
    }
    else
    {
        switch (pParams->videoType)
        {
        case MFX_CODEC_VP8:
        case MFX_CODEC_VP9:
            m_FileReader.reset(new CIVFFrameReader());
            break;
        default:
            //m_FileReader.reset(new CSmplBitstreamReader());
			//
			//  2017/10/08
			m_FileReader.reset(new  CMySmplBitstreamReader());
			//
			{
				if  (  !m_FileReader.get(  )  )  return  MFX_ERR_UNKNOWN;
				CMySmplBitstreamReader	&m_FileReader1  =  *(CMySmplBitstreamReader*)m_FileReader.get();
				memset(  &m_FileReader1.m_var.inputInfo,  0,  sizeof(  m_FileReader1.m_var.inputInfo  )  );
				m_FileReader1.m_var.m_pQdcObjInfoParam  =  m_var.pQdcObjInfo;
			}
			//
            break;
        }
    }

    if (pParams->fourcc)
        m_fourcc = pParams->fourcc;

#ifdef LIBVA_SUPPORT
    if(pParams->bPerfMode)
        m_bPerfMode = true;
#endif

    if (pParams->Width)
        m_vppOutWidth = pParams->Width;
    if (pParams->Height)
        m_vppOutHeight = pParams->Height;


    m_memType = pParams->memType;

    m_nMaxFps = pParams->nMaxFPS;
    m_nFrames = pParams->nFrames ? pParams->nFrames : MFX_INFINITE;

    m_bOutI420 = pParams->outI420;

    m_nTimeout = pParams->nTimeout;

    if (MFX_CODEC_CAPTURE != pParams->videoType)
    {
        sts = m_FileReader->Init(pParams->strSrcFile);
        MSDK_CHECK_STATUS(sts, "m_FileReader->Init failed");
    }

    mfxInitParam initPar;
    mfxExtThreadsParam threadsPar;
    mfxExtBuffer* extBufs[1];
    mfxVersion version;     // real API version with which library is initialized

    MSDK_ZERO_MEMORY(initPar);
    MSDK_ZERO_MEMORY(threadsPar);

    // we set version to 1.0 and later we will query actual version of the library which will got leaded
    initPar.Version.Major = 1;
    initPar.Version.Minor = 0;

    initPar.GPUCopy = pParams->gpuCopy;

    init_ext_buffer(threadsPar);

    bool needInitExtPar = false;

    if (pParams->eDeinterlace)
    {
        m_diMode = pParams->eDeinterlace;
    }

    if (pParams->bUseFullColorRange)
    {
        m_bVppFullColorRange = pParams->bUseFullColorRange;
    }

    if (pParams->nThreadsNum) {
        threadsPar.NumThread = pParams->nThreadsNum;
        needInitExtPar = true;
    }
    if (pParams->SchedulingType) {
        threadsPar.SchedulingType = pParams->SchedulingType;
        needInitExtPar = true;
    }
    if (pParams->Priority) {
        threadsPar.Priority = pParams->Priority;
        needInitExtPar = true;
    }
    if (needInitExtPar) {
        extBufs[0] = (mfxExtBuffer*)&threadsPar;
        initPar.ExtParam = extBufs;
        initPar.NumExtParam = 1;
    }

	//  2015/09/27
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
    if (pParams->bUseHWLib)
    {
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

    MSDK_CHECK_STATUS(sts, "m_mfxSession.Init failed");

    sts = m_mfxSession.QueryVersion(&version); // get real API version of the loaded library
    MSDK_CHECK_STATUS(sts, "m_mfxSession.QueryVersion failed");

    sts = m_mfxSession.QueryIMPL(&m_impl); // get actual library implementation
    MSDK_CHECK_STATUS(sts, "m_mfxSession.QueryIMPL failed");


	//
	//  2015/09/27		
	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "decV: bUseHWLib %d, ucHwAccl %d, ver %d.%d, pktResType %d"  ),  pParams->bUseHWLib,  (  int  )pQdcObjInfo->cfg.v.ucHardwareAccl,  version.Major,  version.Minor,  (  int  )pQdcObjInfo->var.usPktResType_dec  );
	tmp_showInfo(  tBuf  );



	//
    if (pParams->bIsMVC && !CheckVersion(&version, MSDK_FEATURE_MVC)) {
        msdk_printf(MSDK_STRING("error: MVC is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;

    }
    if ((pParams->videoType == MFX_CODEC_JPEG) && !CheckVersion(&version, MSDK_FEATURE_JPEG_DECODE)) {
        msdk_printf(MSDK_STRING("error: Jpeg is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }
    if (pParams->bLowLat && !CheckVersion(&version, MSDK_FEATURE_LOW_LATENCY)) {
        msdk_printf(MSDK_STRING("error: Low Latency mode is not supported in the %d.%d API version\n"),
            version.Major, version.Minor);
        return MFX_ERR_UNSUPPORTED;
    }

    if (pParams->eDeinterlace &&
        (pParams->eDeinterlace != MFX_DEINTERLACING_ADVANCED) &&
        (pParams->eDeinterlace != MFX_DEINTERLACING_BOB) )
    {
        msdk_printf(MSDK_STRING("error: Unsupported deinterlace value: %d\n"), pParams->eDeinterlace);
        return MFX_ERR_UNSUPPORTED;
    }

    if (pParams->bRenderWin) {
        m_bRenderWin = pParams->bRenderWin;
        // note: currently position is unsupported for Wayland
#if !defined(LIBVA_WAYLAND_SUPPORT)
        m_nRenderWinX = pParams->nRenderWinX;
        m_nRenderWinY = pParams->nRenderWinY;
#endif
    }

    m_delayTicks = pParams->nMaxFPS ? msdk_time_get_frequency() / pParams->nMaxFPS : 0;

    // create decoder
    m_pmfxDEC = new MFXVideoDECODE(m_mfxSession);
    MSDK_CHECK_POINTER(m_pmfxDEC, MFX_ERR_MEMORY_ALLOC);

    // set video type in parameters
    m_mfxVideoParams.mfx.CodecId = pParams->videoType;

    // prepare bit stream
    if (MFX_CODEC_CAPTURE != pParams->videoType)
    {
        sts = InitMfxBitstream(&m_mfxBS, 8 * 1024 * 1024);
        MSDK_CHECK_STATUS(sts, "InitMfxBitstream failed");
    }

    if (CheckVersion(&version, MSDK_FEATURE_PLUGIN_API)) {
        /* Here we actually define the following codec initialization scheme:
        *  1. If plugin path or guid is specified: we load user-defined plugin (example: VP8 sample decoder plugin)
        *  2. If plugin path not specified:
        *    2.a) we check if codec is distributed as a mediasdk plugin and load it if yes
        *    2.b) if codec is not in the list of mediasdk plugins, we assume, that it is supported inside mediasdk library
        */
        // Load user plug-in, should go after CreateAllocator function (when all callbacks were initialized)
        if (pParams->pluginParams.type == MFX_PLUGINLOAD_TYPE_FILE && msdk_strnlen(pParams->pluginParams.strPluginPath,sizeof(pParams->pluginParams.strPluginPath)))
        {
            m_pUserModule.reset(new MFXVideoUSER(m_mfxSession));
            if (pParams->videoType == MFX_CODEC_HEVC || pParams->videoType == MFX_CODEC_VP8 ||
                pParams->videoType == MFX_CODEC_VP9 || pParams->videoType == MFX_CODEC_CAPTURE)
            {
                m_pPlugin.reset(LoadPlugin(MFX_PLUGINTYPE_VIDEO_DECODE, m_mfxSession, pParams->pluginParams.pluginGuid, 1, pParams->pluginParams.strPluginPath, (mfxU32)msdk_strnlen(pParams->pluginParams.strPluginPath,sizeof(pParams->pluginParams.strPluginPath))));
            }
            if (m_pPlugin.get() == NULL) sts = MFX_ERR_UNSUPPORTED;
        }
        else
        {
            bool isDefaultPlugin = false;
            if (AreGuidsEqual(pParams->pluginParams.pluginGuid, MSDK_PLUGINGUID_NULL))
            {
                mfxIMPL impl = pParams->bUseHWLib ? MFX_IMPL_HARDWARE : MFX_IMPL_SOFTWARE;
                pParams->pluginParams.pluginGuid = msdkGetPluginUID(impl, MSDK_VDECODE, pParams->videoType);
                isDefaultPlugin = true;
            }
            if (!AreGuidsEqual(pParams->pluginParams.pluginGuid, MSDK_PLUGINGUID_NULL))
            {
                m_pPlugin.reset(LoadPlugin(MFX_PLUGINTYPE_VIDEO_DECODE, m_mfxSession, pParams->pluginParams.pluginGuid, 1));
                if (m_pPlugin.get() == NULL) sts = MFX_ERR_UNSUPPORTED;
            }
            if(sts==MFX_ERR_UNSUPPORTED)
            {
                msdk_printf(isDefaultPlugin ?
                    MSDK_STRING("Default plugin cannot be loaded (possibly you have to define plugin explicitly)\n")
                    : MSDK_STRING("Explicitly specified plugin cannot be loaded.\n"));
            }
        }
        MSDK_CHECK_STATUS(sts, "Plugin load failed");
    }

    // Populate parameters. Involves DecodeHeader call
    sts = InitMfxParams(pParams);
    MSDK_CHECK_STATUS(sts, "InitMfxParams failed");

    if (m_bVppIsUsed)
        m_bDecOutSysmem = pParams->bUseHWLib ? false : true;
    else
        m_bDecOutSysmem = pParams->memType == SYSTEM_MEMORY;

    if (m_bVppIsUsed)
    {
        m_pmfxVPP = new MFXVideoVPP(m_mfxSession);
        if (!m_pmfxVPP) return MFX_ERR_MEMORY_ALLOC;
    }

    m_eWorkMode = pParams->mode;
    if (m_eWorkMode == MODE_FILE_DUMP) {
        // prepare YUV file writer
        sts = m_FileWriter.Init(pParams->strDstFile, pParams->numViews);
        MSDK_CHECK_STATUS(sts, "m_FileWriter.Init failed");
    } else if ((m_eWorkMode != MODE_PERFORMANCE) && (m_eWorkMode != MODE_RENDERING)) {
        msdk_printf(MSDK_STRING("error: unsupported work mode\n"));
        return MFX_ERR_UNSUPPORTED;
    }

    m_monitorType = pParams->monitorType;
    // create device and allocator
#if defined(LIBVA_SUPPORT)
    m_libvaBackend = pParams->libvaBackend;
#endif // defined(MFX_LIBVA_SUPPORT)

    sts = CreateAllocator();
    MSDK_CHECK_STATUS(sts, "CreateAllocator failed");

    // in case of HW accelerated decode frames must be allocated prior to decoder initialization
    sts = AllocFrames();
    MSDK_CHECK_STATUS(sts, "AllocFrames failed");

    sts = m_pmfxDEC->Init(&m_mfxVideoParams);
    if (MFX_WRN_PARTIAL_ACCELERATION == sts)
    {
        msdk_printf(MSDK_STRING("WARNING: partial acceleration\n"));
        MSDK_IGNORE_MFX_STS(sts, MFX_WRN_PARTIAL_ACCELERATION);
    }
    MSDK_CHECK_STATUS(sts, "m_pmfxDEC->Init failed");

    if (m_bVppIsUsed)
    {
        if (m_diMode)
            m_mfxVppVideoParams.vpp.Out.PicStruct = MFX_PICSTRUCT_PROGRESSIVE;

        sts = m_pmfxVPP->Init(&m_mfxVppVideoParams);
        if (MFX_WRN_PARTIAL_ACCELERATION == sts)
        {
            msdk_printf(MSDK_STRING("WARNING: partial acceleration\n"));
            MSDK_IGNORE_MFX_STS(sts, MFX_WRN_PARTIAL_ACCELERATION);
        }
        MSDK_CHECK_STATUS(sts, "m_pmfxVPP->Init failed");
    }

    sts = m_pmfxDEC->GetVideoParam(&m_mfxVideoParams);
    MSDK_CHECK_STATUS(sts, "m_pmfxDEC->GetVideoParam failed");

    if (m_eWorkMode == MODE_RENDERING)
    {
        sts = CreateRenderingWindow(pParams, m_bIsMVC && (m_memType == D3D9_MEMORY));
        MSDK_CHECK_STATUS(sts, "CreateRenderingWindow failed");
		
		//  2015/09/30
		sts = m_FileWriter.Init(pParams->strDstFile, pParams->numViews);
		if  (  sts  )  {
			return  MFX_ERR_UNKNOWN;
		}

    }

    return sts;
}






//  2015/01/17
#if  0
mfxStatus CMyDecPipeline::iiDeliverOutput(mfxFrameSurface1* frame)
{
    CAutoTimer timer_fwrite(m_tick_fwrite);

    mfxStatus res = MFX_ERR_NONE, sts = MFX_ERR_NONE;

    if (!frame) {
        return MFX_ERR_NULL_PTR;
    }

    if (m_bExternalAlloc) {
        if (m_eWorkMode == MODE_FILE_DUMP) {

			//
			res  =  m_FileWriter.WriteNextFrame_pre(  );
			if  (  res  !=  MFX_ERR_NONE  )  {
				//  to skip. 2015/01/17
				res  =  MFX_ERR_NONE;
				}
			else  {	

            res = m_pMFXAllocator->Lock(m_pMFXAllocator->pthis, frame->Data.MemId, &(frame->Data));
            if (MFX_ERR_NONE == res) {
                //res = m_FileWriter.WriteNextFrame(frame);
				res = m_FileWriter.WriteNextFrame0(frame);
				//
                sts = m_pMFXAllocator->Unlock(m_pMFXAllocator->pthis, frame->Data.MemId, &(frame->Data));
				//
				//  2015/01/17		
				if  (  res  ==  MFX_ERR_NONE  )  {
					m_FileWriter.WriteNextFrame1(  );									  
				}
				//  这里表明忽略write的错误				
				res  =  MFX_ERR_NONE;            
            }
            if ((MFX_ERR_NONE == res) && (MFX_ERR_NONE != sts)) {
                res = sts;
            }
			}
        } else if (m_eWorkMode == MODE_RENDERING) {
				  //
				  //  2015/09/30
				  //memset(  &m_var.pktSharedTexInfo,  0,  sizeof(  m_var.pktSharedTexInfo  )  );

				  //
#if D3D_SURFACES_SUPPORT
            res = m_d3dRender.RenderFrame(frame, m_pMFXAllocator);
#elif LIBVA_SUPPORT
            res = m_hwdev->RenderFrame(frame, m_pMFXAllocator);
#endif
			
			//  2015/09/30
			if  (  res  ==  MFX_ERR_NONE  )  {
				QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
				if  (  pQdcObjInfo  )  {
					m_FileWriter.m_var.outputInfo.usPktResType  =  pQdcObjInfo->var.usPktResType_dec;
				}
				if  (  m_var.pkts_sharedTexInfo.ucCnt  )  {					
					int  i;
					for  (  i  =  0;  i  <  m_var.pkts_sharedTexInfo.ucCnt;  i  ++  )  {
						 //m_FileWriter.m_var.outputInfo.pktSharedTexInfo  =  m_var.pktSharedTexInfos[i];				
						 m_FileWriter.m_var.outputInfo.pkts_sharedTexInfo.mems[i]  =  m_var.pkts_sharedTexInfo.mems[i];								
					}
					m_FileWriter.m_var.outputInfo.pkts_sharedTexInfo.ucCnt  =  m_var.pkts_sharedTexInfo.ucCnt;
					//				
					m_FileWriter.WriteNextFrame(  frame  );				
					//
					m_var.pkts_sharedTexInfo.ucCnt  =  0;
				}
			}
        }
    }
    else {
        res = m_FileWriter.WriteNextFrame(frame);
    }

    return res;
}
#endif


//
mfxStatus CMyDecPipeline::DeliverOutput(mfxFrameSurface1* frame)
{
    CAutoTimer timer_fwrite(m_tick_fwrite);

    mfxStatus res = MFX_ERR_NONE, sts = MFX_ERR_NONE;

    if (!frame) {
        return MFX_ERR_NULL_PTR;
    }

    if (m_bExternalAlloc) {
        if (m_eWorkMode == MODE_FILE_DUMP) {
            res = m_pGeneralAllocator->Lock(m_pGeneralAllocator->pthis, frame->Data.MemId, &(frame->Data));
            if (MFX_ERR_NONE == res) {
                res = m_FileWriter.WriteNextFrame(frame);
                sts = m_pGeneralAllocator->Unlock(m_pGeneralAllocator->pthis, frame->Data.MemId, &(frame->Data));
            }
            if ((MFX_ERR_NONE == res) && (MFX_ERR_NONE != sts)) {
                res = sts;
            }
        } else if (m_eWorkMode == MODE_RENDERING) {
#if D3D_SURFACES_SUPPORT
            res = m_d3dRender.RenderFrame(frame, m_pGeneralAllocator);
#elif LIBVA_SUPPORT
            res = m_hwdev->RenderFrame(frame, m_pGeneralAllocator);
#endif
			//
			//  2015/09/30
			if  (  res  ==  MFX_ERR_NONE  )  {
				QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
				if  (  pQdcObjInfo  )  {
					m_FileWriter.m_var.outputInfo.usPktResType  =  pQdcObjInfo->var.usPktResType_dec;
				}
				if  (  m_var.pkts_sharedTexInfo.ucCnt  )  {					
					int  i;
					for  (  i  =  0;  i  <  m_var.pkts_sharedTexInfo.ucCnt;  i  ++  )  {
						 //m_FileWriter.m_var.outputInfo.pktSharedTexInfo  =  m_var.pktSharedTexInfos[i];				
						 m_FileWriter.m_var.outputInfo.pkts_sharedTexInfo.mems[i]  =  m_var.pkts_sharedTexInfo.mems[i];								
					}
					m_FileWriter.m_var.outputInfo.pkts_sharedTexInfo.ucCnt  =  m_var.pkts_sharedTexInfo.ucCnt;
					//				
					m_FileWriter.WriteNextFrame(  frame  );				
					//
					m_var.pkts_sharedTexInfo.ucCnt  =  0;
				}
			}

			//

        }
    }
    else {
        res = m_FileWriter.WriteNextFrame(frame);
    }

    return res;
}















//
#if  0
mfxStatus CMyDecPipeline::iiInitMfxParams(sInputParams *pParams)
{
    MSDK_CHECK_POINTER(m_pmfxDEC, MFX_ERR_NULL_PTR);
    mfxStatus sts = MFX_ERR_NONE;
    mfxU32 &numViews = pParams->numViews;


	//  2014/04/01
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
	if  (  !pQdcObjInfo  )  {
		tmp_showInfo(  _T(  "CMyDecPipeline::InitMfxParams failed, pQdcObjInfo is null"  )  );
		return    MFX_ERR_UNKNOWN;
	}
	if  (  !pQdcObjInfo->var.ucbTransformFuncsOk  )  return  MFX_ERR_UNKNOWN;


    // try to find a sequence header in the stream
    // if header is not found this function exits with error (e.g. if device was lost and there's no header in the remaining stream)
    if (MFX_CODEC_CAPTURE == pParams->videoType)
    {
        m_mfxVideoParams.mfx.CodecId = MFX_CODEC_CAPTURE;
        m_mfxVideoParams.mfx.FrameInfo.PicStruct = MFX_PICSTRUCT_PROGRESSIVE;
        m_mfxVideoParams.mfx.FrameInfo.Width = MSDK_ALIGN32(pParams->width);
        m_mfxVideoParams.mfx.FrameInfo.Height = MSDK_ALIGN32(pParams->height);
        m_mfxVideoParams.mfx.FrameInfo.CropW = pParams->width;
        m_mfxVideoParams.mfx.FrameInfo.CropH = pParams->height;
        m_mfxVideoParams.mfx.FrameInfo.FourCC = pParams->fourcc;
        if (!m_mfxVideoParams.mfx.FrameInfo.FourCC)
            m_mfxVideoParams.mfx.FrameInfo.FourCC = MFX_FOURCC_NV12;
        if (!m_mfxVideoParams.mfx.FrameInfo.ChromaFormat)
        {
            if (MFX_FOURCC_NV12 == m_mfxVideoParams.mfx.FrameInfo.FourCC)
                m_mfxVideoParams.mfx.FrameInfo.ChromaFormat = MFX_CHROMAFORMAT_YUV420;
            else if (MFX_FOURCC_RGB4 == m_mfxVideoParams.mfx.FrameInfo.FourCC)
                m_mfxVideoParams.mfx.FrameInfo.ChromaFormat = MFX_CHROMAFORMAT_YUV444;
        }
    }

    for (; MFX_CODEC_CAPTURE != pParams->videoType;)
    {

		//  2014/04/01
		if  (  pQdcObjInfo->cfg.v.pf_bTransformVideoQuit(  pQdcObjInfo->cfg.v.pParent_transform,  0,  0  )  )  {
			tmp_showInfo(  _T(  "CMyDecPipeline::InitMfxParams failed, quit now"  )  );
			return  MFX_ERR_UNKNOWN;
		}

        // trying to find PicStruct information in AVI headers
        if ( m_mfxVideoParams.mfx.CodecId == MFX_CODEC_JPEG )
            MJPEG_AVI_ParsePicStruct(&m_mfxBS);

        // parse bit stream and fill mfx params
        sts = m_pmfxDEC->DecodeHeader(&m_mfxBS, &m_mfxVideoParams);
        if (m_pPlugin.get() && pParams->videoType == CODEC_VP8 && !sts) {
            // force set format to nv12 as the vp8 plugin uses yv12
            m_mfxVideoParams.mfx.FrameInfo.FourCC = MFX_FOURCC_NV12;
        }
        if (MFX_ERR_MORE_DATA == sts)
        {
            if (m_mfxBS.MaxLength == m_mfxBS.DataLength)
            {
                sts = ExtendMfxBitstream(&m_mfxBS, m_mfxBS.MaxLength * 2);
                MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
            }
            // read a portion of data
            sts = m_FileReader->ReadNextFrame(&m_mfxBS);
            if (MFX_ERR_MORE_DATA == sts &&
                !(m_mfxBS.DataFlag & MFX_BITSTREAM_EOS))
            {
                m_mfxBS.DataFlag |= MFX_BITSTREAM_EOS;
                sts = MFX_ERR_NONE;
            }
            MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

            continue;
        }
        else
        {
            // Enter MVC mode
            if (m_bIsMVC)
            {
                // Check for attached external parameters - if we have them already,
                // we don't need to attach them again
                if (NULL != m_mfxVideoParams.ExtParam)
                    break;

                // allocate and attach external parameters for MVC decoder
                sts = AllocateExtBuffer<mfxExtMVCSeqDesc>();
                MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

                AttachExtParam();
                sts = m_pmfxDEC->DecodeHeader(&m_mfxBS, &m_mfxVideoParams);

                if (MFX_ERR_NOT_ENOUGH_BUFFER == sts)
                {
                    sts = AllocateExtMVCBuffers();
                    SetExtBuffersFlag();

                    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
                    MSDK_CHECK_POINTER(m_mfxVideoParams.ExtParam, MFX_ERR_MEMORY_ALLOC);
                    continue;
                }
            }

            // if input is interlaced JPEG stream
            if ( m_mfxBS.PicStruct == MFX_PICSTRUCT_FIELD_TFF || m_mfxBS.PicStruct == MFX_PICSTRUCT_FIELD_BFF)
            {
                m_mfxVideoParams.mfx.FrameInfo.CropH *= 2;
                m_mfxVideoParams.mfx.FrameInfo.Height = MSDK_ALIGN16(m_mfxVideoParams.mfx.FrameInfo.CropH);
                m_mfxVideoParams.mfx.FrameInfo.PicStruct = m_mfxBS.PicStruct;
            }

            switch(pParams->nRotation)
            {
            case 0:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_0;
                break;
            case 90:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_90;
                break;
            case 180:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_180;
                break;
            case 270:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_270;
                break;
            default:
                return MFX_ERR_UNSUPPORTED;
            }

            break;
        }
    }

    // check DecodeHeader status
    if (MFX_WRN_PARTIAL_ACCELERATION == sts)
    {
        msdk_printf(MSDK_STRING("WARNING: partial acceleration\n"));
        MSDK_IGNORE_MFX_STS(sts, MFX_WRN_PARTIAL_ACCELERATION);
    }
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // If MVC mode we need to detect number of views in stream
    if (m_bIsMVC)
    {
        mfxExtMVCSeqDesc* pSequenceBuffer;
        pSequenceBuffer = (mfxExtMVCSeqDesc*) GetExtBuffer(m_mfxVideoParams.ExtParam, m_mfxVideoParams.NumExtParam, MFX_EXTBUFF_MVC_SEQ_DESC);
        MSDK_CHECK_POINTER(pSequenceBuffer, MFX_ERR_INVALID_VIDEO_PARAM);

        mfxU32 i = 0;
        numViews = 0;
        for (i = 0; i < pSequenceBuffer->NumView; ++i)
        {
            /* Some MVC streams can contain different information about
               number of views and view IDs, e.x. numVews = 2
               and ViewId[0, 1] = 0, 2 instead of ViewId[0, 1] = 0, 1.
               numViews should be equal (max(ViewId[i]) + 1)
               to prevent crashes during output files writing */
            if (pSequenceBuffer->View[i].ViewId >= numViews)
                numViews = pSequenceBuffer->View[i].ViewId + 1;
        }
    }
    else
    {
        numViews = 1;
    }

    // specify memory type
    m_mfxVideoParams.IOPattern = (mfxU16)(m_memType != SYSTEM_MEMORY ? MFX_IOPATTERN_OUT_VIDEO_MEMORY : MFX_IOPATTERN_OUT_SYSTEM_MEMORY);

    m_mfxVideoParams.AsyncDepth = pParams->nAsyncDepth;

    return MFX_ERR_NONE;
}
#endif


//
#if  0
//  2016/04/16
mfxStatus iiCMyDecPipeline::InitMfxParams(sInputParams *pParams)
{
    MSDK_CHECK_POINTER(m_pmfxDEC, MFX_ERR_NULL_PTR);
    mfxStatus sts = MFX_ERR_NONE;
    mfxU32 &numViews = pParams->numViews;

		//  2014/04/01
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
	if  (  !pQdcObjInfo  )  {
		tmp_showInfo(  _T(  "CMyDecPipeline::InitMfxParams failed, pQdcObjInfo is null"  )  );
		return    MFX_ERR_UNKNOWN;
	}
	if  (  !pQdcObjInfo->var.ucbTransformFuncsOk  )  return  MFX_ERR_UNKNOWN;



    // try to find a sequence header in the stream
    // if header is not found this function exits with error (e.g. if device was lost and there's no header in the remaining stream)
    if (MFX_CODEC_CAPTURE == pParams->videoType)
    {
        m_mfxVideoParams.mfx.CodecId = MFX_CODEC_CAPTURE;
        m_mfxVideoParams.mfx.FrameInfo.PicStruct = MFX_PICSTRUCT_PROGRESSIVE;
        m_mfxVideoParams.mfx.FrameInfo.Width = MSDK_ALIGN32(pParams->scrWidth);
        m_mfxVideoParams.mfx.FrameInfo.Height = MSDK_ALIGN32(pParams->scrHeight);
        m_mfxVideoParams.mfx.FrameInfo.CropW = pParams->scrWidth;
        m_mfxVideoParams.mfx.FrameInfo.CropH = pParams->scrHeight;
        m_mfxVideoParams.mfx.FrameInfo.FourCC = (m_fourcc == MFX_FOURCC_RGB4) ? MFX_FOURCC_RGB4 : MFX_FOURCC_NV12;

        if (!m_mfxVideoParams.mfx.FrameInfo.ChromaFormat)
        {
            if (MFX_FOURCC_NV12 == m_mfxVideoParams.mfx.FrameInfo.FourCC)
                m_mfxVideoParams.mfx.FrameInfo.ChromaFormat = MFX_CHROMAFORMAT_YUV420;
            else if (MFX_FOURCC_RGB4 == m_mfxVideoParams.mfx.FrameInfo.FourCC)
                m_mfxVideoParams.mfx.FrameInfo.ChromaFormat = MFX_CHROMAFORMAT_YUV444;
        }
        m_bVppIsUsed = IsVppRequired(pParams);
    }

    for (; MFX_CODEC_CAPTURE != pParams->videoType;)
    {

		//  2014/04/01
		if  (  pQdcObjInfo->cfg.v.pf_bTransformVideoQuit(  pQdcObjInfo->cfg.v.pParent_transform,  0,  0  )  )  {
			tmp_showInfo(  _T(  "CMyDecPipeline::InitMfxParams failed, quit now"  )  );
			return  MFX_ERR_UNKNOWN;
		}



        // trying to find PicStruct information in AVI headers
        if ( m_mfxVideoParams.mfx.CodecId == MFX_CODEC_JPEG )
            MJPEG_AVI_ParsePicStruct(&m_mfxBS);

        // parse bit stream and fill mfx params
        sts = m_pmfxDEC->DecodeHeader(&m_mfxBS, &m_mfxVideoParams);
        if (!sts)
        {
            m_bVppIsUsed = IsVppRequired(pParams);
        }

        if (!sts &&
            !(m_impl & MFX_IMPL_SOFTWARE) &&                        // hw lib
            (m_mfxVideoParams.mfx.FrameInfo.BitDepthLuma == 10) &&  // hevc 10 bit
            (m_mfxVideoParams.mfx.CodecId == MFX_CODEC_HEVC) &&
            AreGuidsEqual(pParams->pluginParams.pluginGuid, MFX_PLUGINID_HEVCD_SW) && // sw hevc decoder
            m_bVppIsUsed )
        {
            sts = MFX_ERR_UNSUPPORTED;
            msdk_printf(MSDK_STRING("Error: Combination of (SW HEVC plugin in 10bit mode + HW lib VPP) isn't supported. Use -sw option.\n"));
        }
        if (m_pPlugin.get() && pParams->videoType == CODEC_VP8 && !sts) {
            // force set format to nv12 as the vp8 plugin uses yv12
            m_mfxVideoParams.mfx.FrameInfo.FourCC = MFX_FOURCC_NV12;
        }
        if (MFX_ERR_MORE_DATA == sts)
        {
            if (m_mfxBS.MaxLength == m_mfxBS.DataLength)
            {
                sts = ExtendMfxBitstream(&m_mfxBS, m_mfxBS.MaxLength * 2);
                MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
            }
            // read a portion of data
            sts = m_FileReader->ReadNextFrame(&m_mfxBS);
            if (MFX_ERR_MORE_DATA == sts &&
                !(m_mfxBS.DataFlag & MFX_BITSTREAM_EOS))
            {
                m_mfxBS.DataFlag |= MFX_BITSTREAM_EOS;
                sts = MFX_ERR_NONE;
            }
            MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

            continue;
        }
        else
        {
            // Enter MVC mode
            if (m_bIsMVC)
            {
                // Check for attached external parameters - if we have them already,
                // we don't need to attach them again
                if (NULL != m_mfxVideoParams.ExtParam)
                    break;

                // allocate and attach external parameters for MVC decoder
                sts = AllocateExtBuffer<mfxExtMVCSeqDesc>();
                MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

                AttachExtParam();
                sts = m_pmfxDEC->DecodeHeader(&m_mfxBS, &m_mfxVideoParams);

                if (MFX_ERR_NOT_ENOUGH_BUFFER == sts)
                {
                    sts = AllocateExtMVCBuffers();
                    SetExtBuffersFlag();

                    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
                    MSDK_CHECK_POINTER(m_mfxVideoParams.ExtParam, MFX_ERR_MEMORY_ALLOC);
                    continue;
                }
            }

            // if input is interlaced JPEG stream
            if ( m_mfxBS.PicStruct == MFX_PICSTRUCT_FIELD_TFF || m_mfxBS.PicStruct == MFX_PICSTRUCT_FIELD_BFF)
            {
                m_mfxVideoParams.mfx.FrameInfo.CropH *= 2;
                m_mfxVideoParams.mfx.FrameInfo.Height = MSDK_ALIGN16(m_mfxVideoParams.mfx.FrameInfo.CropH);
                m_mfxVideoParams.mfx.FrameInfo.PicStruct = m_mfxBS.PicStruct;
            }

            switch(pParams->nRotation)
            {
            case 0:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_0;
                break;
            case 90:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_90;
                break;
            case 180:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_180;
                break;
            case 270:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_270;
                break;
            default:
                return MFX_ERR_UNSUPPORTED;
            }

            break;
        }
    }

    // check DecodeHeader status
    if (MFX_WRN_PARTIAL_ACCELERATION == sts)
    {
        msdk_printf(MSDK_STRING("WARNING: partial acceleration\n"));
        MSDK_IGNORE_MFX_STS(sts, MFX_WRN_PARTIAL_ACCELERATION);
    }
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    if (!m_mfxVideoParams.mfx.FrameInfo.FrameRateExtN || !m_mfxVideoParams.mfx.FrameInfo.FrameRateExtD) {
        msdk_printf(MSDK_STRING("pretending that stream is 30fps one\n"));
        m_mfxVideoParams.mfx.FrameInfo.FrameRateExtN = 30;
        m_mfxVideoParams.mfx.FrameInfo.FrameRateExtD = 1;
    }
    if (!m_mfxVideoParams.mfx.FrameInfo.AspectRatioW || !m_mfxVideoParams.mfx.FrameInfo.AspectRatioH) {
        msdk_printf(MSDK_STRING("pretending that aspect ratio is 1:1\n"));
        m_mfxVideoParams.mfx.FrameInfo.AspectRatioW = 1;
        m_mfxVideoParams.mfx.FrameInfo.AspectRatioH = 1;
    }

    // Videoparams for RGB4 JPEG decoder output
    if ((pParams->fourcc == MFX_FOURCC_RGB4) && (pParams->videoType == MFX_CODEC_JPEG))
    {
        m_mfxVideoParams.mfx.FrameInfo.FourCC = MFX_FOURCC_RGB4;
        m_mfxVideoParams.mfx.FrameInfo.ChromaFormat = MFX_CHROMAFORMAT_YUV444;
    }

    // If MVC mode we need to detect number of views in stream
    if (m_bIsMVC)
    {
        mfxExtMVCSeqDesc* pSequenceBuffer;
        pSequenceBuffer = (mfxExtMVCSeqDesc*) GetExtBuffer(m_mfxVideoParams.ExtParam, m_mfxVideoParams.NumExtParam, MFX_EXTBUFF_MVC_SEQ_DESC);
        MSDK_CHECK_POINTER(pSequenceBuffer, MFX_ERR_INVALID_VIDEO_PARAM);

        mfxU32 i = 0;
        numViews = 0;
        for (i = 0; i < pSequenceBuffer->NumView; ++i)
        {
            /* Some MVC streams can contain different information about
               number of views and view IDs, e.x. numVews = 2
               and ViewId[0, 1] = 0, 2 instead of ViewId[0, 1] = 0, 1.
               numViews should be equal (max(ViewId[i]) + 1)
               to prevent crashes during output files writing */
            if (pSequenceBuffer->View[i].ViewId >= numViews)
                numViews = pSequenceBuffer->View[i].ViewId + 1;
        }
    }
    else
    {
        numViews = 1;
    }

    // specify memory type
    if (!m_bVppIsUsed)
        m_mfxVideoParams.IOPattern = (mfxU16)(m_memType != SYSTEM_MEMORY ? MFX_IOPATTERN_OUT_VIDEO_MEMORY : MFX_IOPATTERN_OUT_SYSTEM_MEMORY);
    else
        m_mfxVideoParams.IOPattern = (mfxU16)(pParams->bUseHWLib ? MFX_IOPATTERN_OUT_VIDEO_MEMORY : MFX_IOPATTERN_OUT_SYSTEM_MEMORY);

    m_mfxVideoParams.AsyncDepth = pParams->nAsyncDepth;

    return MFX_ERR_NONE;
}
#endif


mfxStatus CMyDecPipeline::InitMfxParams(sInputParams *pParams)
{
    MSDK_CHECK_POINTER(m_pmfxDEC, MFX_ERR_NULL_PTR);
    mfxStatus sts = MFX_ERR_NONE;
    mfxU32 &numViews = pParams->numViews;

	//
			//  2014/04/01
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfo;
	if  (  !pQdcObjInfo  )  {
		tmp_showInfo(  _T(  "CMyDecPipeline::InitMfxParams failed, pQdcObjInfo is null"  )  );
		return    MFX_ERR_UNKNOWN;
	}
	if  (  !pQdcObjInfo->var.ucbTransformFuncsOk  )  return  MFX_ERR_UNKNOWN;



    // try to find a sequence header in the stream
    // if header is not found this function exits with error (e.g. if device was lost and there's no header in the remaining stream)
    if (MFX_CODEC_CAPTURE == pParams->videoType)
    {
        m_mfxVideoParams.mfx.CodecId = MFX_CODEC_CAPTURE;
        m_mfxVideoParams.mfx.FrameInfo.PicStruct = MFX_PICSTRUCT_PROGRESSIVE;
        m_mfxVideoParams.mfx.FrameInfo.Width = MSDK_ALIGN32(pParams->scrWidth);
        m_mfxVideoParams.mfx.FrameInfo.Height = MSDK_ALIGN32(pParams->scrHeight);
        m_mfxVideoParams.mfx.FrameInfo.CropW = pParams->scrWidth;
        m_mfxVideoParams.mfx.FrameInfo.CropH = pParams->scrHeight;
        m_mfxVideoParams.mfx.FrameInfo.FourCC = (m_fourcc == MFX_FOURCC_RGB4) ? MFX_FOURCC_RGB4 : MFX_FOURCC_NV12;

        if (!m_mfxVideoParams.mfx.FrameInfo.ChromaFormat)
        {
            if (MFX_FOURCC_NV12 == m_mfxVideoParams.mfx.FrameInfo.FourCC)
                m_mfxVideoParams.mfx.FrameInfo.ChromaFormat = MFX_CHROMAFORMAT_YUV420;
            else if (MFX_FOURCC_RGB4 == m_mfxVideoParams.mfx.FrameInfo.FourCC)
                m_mfxVideoParams.mfx.FrameInfo.ChromaFormat = MFX_CHROMAFORMAT_YUV444;
        }
        m_bVppIsUsed = IsVppRequired(pParams);
    }

    for (; MFX_CODEC_CAPTURE != pParams->videoType;)
    {
		//  2014/04/01
		if  (  pQdcObjInfo->cfg.v.pf_bTransformVideoQuit(  pQdcObjInfo->cfg.v.pParent_transform,  0,  0  )  )  {
			tmp_showInfo(  _T(  "CMyDecPipeline::InitMfxParams failed, quit now"  )  );
			return  MFX_ERR_UNKNOWN;
		}



        // trying to find PicStruct information in AVI headers
        if ( m_mfxVideoParams.mfx.CodecId == MFX_CODEC_JPEG )
            MJPEG_AVI_ParsePicStruct(&m_mfxBS);

        // parse bit stream and fill mfx params
        sts = m_pmfxDEC->DecodeHeader(&m_mfxBS, &m_mfxVideoParams);
        if (!sts)
        {
            m_bVppIsUsed = IsVppRequired(pParams);
        }

        if (!sts &&
            !(m_impl & MFX_IMPL_SOFTWARE) &&                        // hw lib
            (m_mfxVideoParams.mfx.FrameInfo.BitDepthLuma == 10) &&  // hevc 10 bit
            (m_mfxVideoParams.mfx.CodecId == MFX_CODEC_HEVC) &&
            AreGuidsEqual(pParams->pluginParams.pluginGuid, MFX_PLUGINID_HEVCD_SW) && // sw hevc decoder
            m_bVppIsUsed )
        {
            sts = MFX_ERR_UNSUPPORTED;
            msdk_printf(MSDK_STRING("Error: Combination of (SW HEVC plugin in 10bit mode + HW lib VPP) isn't supported. Use -sw option.\n"));
        }
        if (m_pPlugin.get() && pParams->videoType == CODEC_VP8 && !sts) {
            // force set format to nv12 as the vp8 plugin uses yv12
            m_mfxVideoParams.mfx.FrameInfo.FourCC = MFX_FOURCC_NV12;
        }
        if (MFX_ERR_MORE_DATA == sts)
        {
            if (m_mfxBS.MaxLength == m_mfxBS.DataLength)
            {
                sts = ExtendMfxBitstream(&m_mfxBS, m_mfxBS.MaxLength * 2);
                MSDK_CHECK_STATUS(sts, "ExtendMfxBitstream failed");
            }
            // read a portion of data
            sts = m_FileReader->ReadNextFrame(&m_mfxBS);
            if (MFX_ERR_MORE_DATA == sts &&
                !(m_mfxBS.DataFlag & MFX_BITSTREAM_EOS))
            {
                m_mfxBS.DataFlag |= MFX_BITSTREAM_EOS;
                sts = MFX_ERR_NONE;
            }
            MSDK_CHECK_STATUS(sts, "m_FileReader->ReadNextFrame failed");

            continue;
        }
        else
        {
            // Enter MVC mode
            if (m_bIsMVC)
            {
                // Check for attached external parameters - if we have them already,
                // we don't need to attach them again
                if (NULL != m_mfxVideoParams.ExtParam)
                    break;

                // allocate and attach external parameters for MVC decoder
                sts = AllocateExtBuffer<mfxExtMVCSeqDesc>();
                MSDK_CHECK_STATUS(sts, "AllocateExtBuffer<mfxExtMVCSeqDesc> failed");

                AttachExtParam();
                sts = m_pmfxDEC->DecodeHeader(&m_mfxBS, &m_mfxVideoParams);

                if (MFX_ERR_NOT_ENOUGH_BUFFER == sts)
                {
                    sts = AllocateExtMVCBuffers();
                    SetExtBuffersFlag();

                    MSDK_CHECK_STATUS(sts, "AllocateExtMVCBuffers failed");
                    MSDK_CHECK_POINTER(m_mfxVideoParams.ExtParam, MFX_ERR_MEMORY_ALLOC);
                    continue;
                }
            }

            // if input is interlaced JPEG stream
            if ( m_mfxBS.PicStruct == MFX_PICSTRUCT_FIELD_TFF || m_mfxBS.PicStruct == MFX_PICSTRUCT_FIELD_BFF)
            {
                m_mfxVideoParams.mfx.FrameInfo.CropH *= 2;
                m_mfxVideoParams.mfx.FrameInfo.Height = MSDK_ALIGN16(m_mfxVideoParams.mfx.FrameInfo.CropH);
                m_mfxVideoParams.mfx.FrameInfo.PicStruct = m_mfxBS.PicStruct;
            }

            switch(pParams->nRotation)
            {
            case 0:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_0;
                break;
            case 90:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_90;
                break;
            case 180:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_180;
                break;
            case 270:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_270;
                break;
            default:
                return MFX_ERR_UNSUPPORTED;
            }

            break;
        }
    }

    // check DecodeHeader status
    if (MFX_WRN_PARTIAL_ACCELERATION == sts)
    {
        msdk_printf(MSDK_STRING("WARNING: partial acceleration\n"));
        MSDK_IGNORE_MFX_STS(sts, MFX_WRN_PARTIAL_ACCELERATION);
    }
    MSDK_CHECK_STATUS(sts, "m_pmfxDEC->DecodeHeader failed");

    if (!m_mfxVideoParams.mfx.FrameInfo.FrameRateExtN || !m_mfxVideoParams.mfx.FrameInfo.FrameRateExtD) {
        msdk_printf(MSDK_STRING("pretending that stream is 30fps one\n"));
        m_mfxVideoParams.mfx.FrameInfo.FrameRateExtN = 30;
        m_mfxVideoParams.mfx.FrameInfo.FrameRateExtD = 1;
    }
    if (!m_mfxVideoParams.mfx.FrameInfo.AspectRatioW || !m_mfxVideoParams.mfx.FrameInfo.AspectRatioH) {
        msdk_printf(MSDK_STRING("pretending that aspect ratio is 1:1\n"));
        m_mfxVideoParams.mfx.FrameInfo.AspectRatioW = 1;
        m_mfxVideoParams.mfx.FrameInfo.AspectRatioH = 1;
    }

    // Videoparams for RGB4 JPEG decoder output
    if ((pParams->fourcc == MFX_FOURCC_RGB4) && (pParams->videoType == MFX_CODEC_JPEG))
    {
        m_mfxVideoParams.mfx.FrameInfo.FourCC = MFX_FOURCC_RGB4;
        m_mfxVideoParams.mfx.FrameInfo.ChromaFormat = MFX_CHROMAFORMAT_YUV444;
        if (pParams->chromaType == MFX_JPEG_COLORFORMAT_RGB)
        {
            m_mfxVideoParams.mfx.JPEGColorFormat = pParams->chromaType;
        }
    }

#if _MSDK_API >= MSDK_API(1,22)
    /* Lets make final decision how to use VPP...*/
    if (!m_bVppIsUsed)
    {

        if ( (m_mfxVideoParams.mfx.FrameInfo.CropW != pParams->Width && pParams->Width) ||
            (m_mfxVideoParams.mfx.FrameInfo.CropH != pParams->Height && pParams->Height) )
        {
            /* By default VPP used for resize */
            m_bVppIsUsed = true;
            /* But... lets try to use decoder's post processing */
            if ( ((MODE_DECODER_POSTPROC_AUTO == pParams->nDecoderPostProcessing) ||
                  (MODE_DECODER_POSTPROC_FORCE == pParams->nDecoderPostProcessing)) &&
                 (MFX_CODEC_AVC == m_mfxVideoParams.mfx.CodecId) && /* Only for AVC */
                 (MFX_PICSTRUCT_PROGRESSIVE == m_mfxVideoParams.mfx.FrameInfo.PicStruct)) /* ...And only for progressive!*/
            {   /* it is possible to use decoder's post-processing */
                m_bVppIsUsed = false;
                m_DecoderPostProcessing.In.CropX = 0;
                m_DecoderPostProcessing.In.CropY = 0;
                m_DecoderPostProcessing.In.CropW = m_mfxVideoParams.mfx.FrameInfo.CropW;
                m_DecoderPostProcessing.In.CropH = m_mfxVideoParams.mfx.FrameInfo.CropH;

                m_DecoderPostProcessing.Out.FourCC = m_mfxVideoParams.mfx.FrameInfo.FourCC;
                m_DecoderPostProcessing.Out.ChromaFormat = m_mfxVideoParams.mfx.FrameInfo.ChromaFormat;
                m_DecoderPostProcessing.Out.Width = MSDK_ALIGN16(pParams->Width);
                m_DecoderPostProcessing.Out.Height = MSDK_ALIGN16(pParams->Height);
                m_DecoderPostProcessing.Out.CropX = 0;
                m_DecoderPostProcessing.Out.CropY = 0;
                m_DecoderPostProcessing.Out.CropW = pParams->Width;
                m_DecoderPostProcessing.Out.CropH = pParams->Height;

                m_ExtBuffers.push_back((mfxExtBuffer *)&m_DecoderPostProcessing);
                AttachExtParam();
                msdk_printf(MSDK_STRING("Decoder's post-processing is used for resizing\n") );
            }
            /* POSTPROC_FORCE */
            if (MODE_DECODER_POSTPROC_FORCE == pParams->nDecoderPostProcessing)
            {
               if ((MFX_CODEC_AVC != m_mfxVideoParams.mfx.CodecId) ||
                   (MFX_PICSTRUCT_PROGRESSIVE != m_mfxVideoParams.mfx.FrameInfo.PicStruct))
               {
                   /* it is impossible to use decoder's post-processing */
                   msdk_printf(MSDK_STRING("ERROR: decoder postprocessing (-dec_postproc forced) cannot resize this stream!\n") );
                   return MFX_ERR_UNSUPPORTED;
               }
            }
            if ((m_bVppIsUsed) && (MODE_DECODER_POSTPROC_AUTO == pParams->nDecoderPostProcessing))
                msdk_printf(MSDK_STRING("Decoder post-processing is unsupported for this stream, VPP is used for resizing\n") );
        }
    }
#endif //_MSDK_API >= MSDK_API(1,22)

    // If MVC mode we need to detect number of views in stream
    if (m_bIsMVC)
    {
        mfxExtMVCSeqDesc* pSequenceBuffer;
        pSequenceBuffer = (mfxExtMVCSeqDesc*) GetExtBuffer(m_mfxVideoParams.ExtParam, m_mfxVideoParams.NumExtParam, MFX_EXTBUFF_MVC_SEQ_DESC);
        MSDK_CHECK_POINTER(pSequenceBuffer, MFX_ERR_INVALID_VIDEO_PARAM);

        mfxU32 i = 0;
        numViews = 0;
        for (i = 0; i < pSequenceBuffer->NumView; ++i)
        {
            /* Some MVC streams can contain different information about
               number of views and view IDs, e.x. numVews = 2
               and ViewId[0, 1] = 0, 2 instead of ViewId[0, 1] = 0, 1.
               numViews should be equal (max(ViewId[i]) + 1)
               to prevent crashes during output files writing */
            if (pSequenceBuffer->View[i].ViewId >= numViews)
                numViews = pSequenceBuffer->View[i].ViewId + 1;
        }
    }
    else
    {
        numViews = 1;
    }

    // specify memory type
    if (!m_bVppIsUsed)
        m_mfxVideoParams.IOPattern = (mfxU16)(m_memType != SYSTEM_MEMORY ? MFX_IOPATTERN_OUT_VIDEO_MEMORY : MFX_IOPATTERN_OUT_SYSTEM_MEMORY);
    else
        m_mfxVideoParams.IOPattern = (mfxU16)(pParams->bUseHWLib ? MFX_IOPATTERN_OUT_VIDEO_MEMORY : MFX_IOPATTERN_OUT_SYSTEM_MEMORY);

    m_mfxVideoParams.AsyncDepth = pParams->nAsyncDepth;

    return MFX_ERR_NONE;
}




//
mfxStatus CMyDecPipeline::CreateHWDevice()
{
#if D3D_SURFACES_SUPPORT
    mfxStatus sts = MFX_ERR_NONE;

    HWND window = NULL;
    bool render = (m_eWorkMode == MODE_RENDERING);

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







mfxStatus  CMyDecPipeline::myRun(  void  * pQdcObjInfoParam  )
{
	mfxStatus sts = MFX_ERR_NONE; // return value check

	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pQdcObjInfoParam;
	QDC_OBJ_trans  *  pObj  =  (  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;
	TCHAR	tBuf[128];
	
	//  2014/07/17
	DEBUG_step_dec	*	pDebugStepDec  =  (  DEBUG_step_dec  *  )tmp_getDebugStep_sth(  0,  CONST_debugStepType_dec,  pQdcObjInfo->var.pDebugStep  );
	if  (  !pDebugStepDec  )  return  (mfxStatus  )-1;


	//
#if  0
	int  imgWidth  =  0;
	int  imgHeight  =  0;
#endif
		
	//if  (  !*pbInited  )  
	{

	    sts = this->Init(&m_params);
		if  (  sts  <  0  )  {		//  2012/09/10
			//
			pDebugStepDec->sts_pipeline_Init  =  sts;
			//
			_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "MyDecPipeline::myRun init failed, sts %d"  ),  sts  );
			tmp_showInfo(  tBuf  );
		}
		CHECK_RESULT(sts, MFX_ERR_NONE, MFX_ERR_UNKNOWN);   

		//  *pbInited  =  TRUE;

		//
#if  0
		if  (  pimgWidth  )  {
			if  (  !*pimgWidth  )  *pimgWidth  =  this->m_mfxVideoParams.mfx.FrameInfo.Width;
			if  (  !*pimgHeight  )  *pimgHeight  =  this->m_mfxVideoParams.mfx.FrameInfo.Height;
		}
#endif
#if  0
		//
		imgWidth  =  this->m_mfxVideoParams.mfx.FrameInfo.Width;
		imgHeight  =  this->m_mfxVideoParams.mfx.FrameInfo.Height;
#endif

		//
		_tprintf(_T("Decoding started\n"));
	}
	

	//  
	if  (  !m_mfxVideoParams.mfx.FrameInfo.Width  ||  !m_mfxVideoParams.mfx.FrameInfo.Height  )  {			
		tmp_showInfo(  _T(  "decPipeline::decode failed, imgW or imgH is 0"  )  );
		goto  errLabel;
	}

#if  0
	if  (  !pObj->bInited2  )  {

		//
		BITMAPINFOHEADER  bih;
		makeBmpInfoHeader_yv12(  12,  imgWidth,  imgHeight,  &bih  );
		if  (  pQdcObjInfo->cfg.dec.pf_updateDecVideoParam(  &bih,  pQdcObjInfo->cfg.pParent_transform,  pQdcObjInfo->cfg.uiTransformType_pParent  )  )  {
			tmp_showInfo(  _T(  "decPipeline: updateDecVideoParam  failed"  )  );
			goto  errLabel;
		}

		//  qdcObjInfo.
		pQdcObjInfo->cbOutputBuffer  =  M_sizeImage_open(  24,  imgWidth,  imgHeight  );
		pQdcObjInfo->cbInputBuffer  =  pQdcObjInfo->cbOutputBuffer;

	
		//
		makeBmpInfoHeader_yv12(  12,  imgWidth,  imgHeight,  &pObj->outputForDec.vh_decompress_real.bih  );
		pObj->outputForDec.uiBufSize  =  pObj->outputForDec.vh_decompress_real.bih.biSizeImage;
		if  (  !pObj->outputForDec.pBuf  )  {
			pObj->outputForDec.pBuf  =  (  char  *  )malloc(  pObj->outputForDec.uiBufSize  );
			if  (  !pObj->outputForDec.pBuf  )  goto  errLabel;
		}

		//	
		if  (  !pObj->common.outs[0].pBuf  )  {
			pObj->common.outs[0].pBuf  =  (  BYTE  *  )malloc(  pQdcObjInfo->cbOutputBuffer  );
			if  (  !pObj->common.outs[0].pBuf  )  goto  errLabel;
		}

		//
		memset(  &this->m_FileWriter.m_var.outputInfo,  0,  sizeof(  this->m_FileWriter.m_var.outputInfo  )  );
		this->m_FileWriter.m_var.outputInfo.pBuf  =  (  BYTE  *  )pObj->outputForDec.pBuf;
		this->m_FileWriter.m_var.outputInfo.uiOutputSize  =  pObj->outputForDec.uiBufSize;

		//
		pObj->bInited2  =  TRUE;
	}
#endif


#if  10

	this->m_FileWriter.m_var.pQdcObjInfoParam  =  pQdcObjInfo;
	//
	this->m_FileWriter.m_var.size_pPkt  =  pQdcObjInfo->cfg.v.size_pCurPkt;
	if  (  this->m_FileWriter.m_var.pPkt  )  {
		tmp_showInfo(  _T(  "decPipeline::myRun failed, fileWriter.pPkt is not null"  )  );
		goto  errLabel;
	}
	this->m_FileWriter.m_var.pPkt  =  malloc(  this->m_FileWriter.m_var.size_pPkt  );
	if  (  !this->m_FileWriter.m_var.pPkt  )  {
		tmp_showInfo(  _T(  "decPipeline::myRun failed, fileWriter.pPkt malloc failed"  )  );
		goto  errLabel;
	}
	//  2015/01/17
	memset(  this->m_FileWriter.m_var.pPkt,  0,  this->m_FileWriter.m_var.size_pPkt  );
#endif


	//
	sts = RunDecoding();

	mfxStatus  tmp_sts  =  sts;

        if (MFX_ERR_INCOMPATIBLE_VIDEO_PARAM == sts || MFX_ERR_DEVICE_LOST == sts || MFX_ERR_DEVICE_FAILED == sts)
        {
            if (MFX_ERR_INCOMPATIBLE_VIDEO_PARAM == sts)
            {
                msdk_printf(MSDK_STRING("\nERROR: Incompatible video parameters detected. Recovering...\n"));
            }
            else
            {
                msdk_printf(MSDK_STRING("\nERROR: Hardware device was lost or returned unexpected error. Recovering...\n"));
				if  (  m_hwdev  )  {
	                sts = ResetDevice();
		            //MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, 1);
				}
            }           

			//
#if  0
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "decVPipeline: runs returns %d"  ),  tmp_sts  );
			MessageBox(  NULL,  tBuf,  _T(  "Qycx"  ),  MB_OK  );
#endif

			//
            sts = ResetDecoder(&m_params);
            //MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, 1);            
            //continue;
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dec.ResetDecoder returns %d"  ),  sts  );
			tmp_showInfo(  tBuf  );
        }        

		//
		sts  =  tmp_sts;

errLabel:
	return  sts;
}
