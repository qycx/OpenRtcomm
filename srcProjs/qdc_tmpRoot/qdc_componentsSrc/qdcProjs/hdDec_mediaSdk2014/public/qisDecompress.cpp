

#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
#include	<Dshow.h>

#include	<assert.h>
//#include	"base_allocator.h"
#include	<d3d11.h>


#include	"qisCompressProc.h"
#include	"myFunc_mediaSdk.h"

#include	"pipeline_decode.h"
#include	"myDecPipeline.h"
#include	"dec_d3d11_dev_open.h"

#include	"tmpDecOpenFunc.h"
#include	"version.h"


void  qdcFreeOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  );
int  yv12ToRgb24_ipp(  unsigned char  *  yuv,  unsigned char  *  rgb,  int  width,  int  height  );


/////////////////////////////
//  2017/10/07

void PrintHelp(msdk_char *strAppName, const msdk_char *strErrorMessage)
{
    msdk_printf(MSDK_STRING("Decoding Sample Version %s\n\n"), GetMSDKSampleVersion().c_str());

    if (strErrorMessage)
    {
        msdk_printf(MSDK_STRING("Error: %s\n"), strErrorMessage);
    }

    msdk_printf(MSDK_STRING("Usage: %s <codecid> [<options>] -i InputBitstream\n"), strAppName);
    msdk_printf(MSDK_STRING("   or: %s <codecid> [<options>] -i InputBitstream -r\n"), strAppName);
    msdk_printf(MSDK_STRING("   or: %s <codecid> [<options>] -i InputBitstream -o OutputYUVFile\n"), strAppName);
    msdk_printf(MSDK_STRING("\n"));
    msdk_printf(MSDK_STRING("Supported codecs (<codecid>):\n"));
    msdk_printf(MSDK_STRING("   <codecid>=h264|mpeg2|vc1|mvc|jpeg - built-in Media SDK codecs\n"));
    msdk_printf(MSDK_STRING("   <codecid>=h265|vp9|capture            - in-box Media SDK plugins (may require separate downloading and installation)\n"));
    msdk_printf(MSDK_STRING("\n"));
    msdk_printf(MSDK_STRING("Work models:\n"));
    msdk_printf(MSDK_STRING("  1. Performance model: decoding on MAX speed, no rendering, no YUV dumping (no -r or -o option)\n"));
    msdk_printf(MSDK_STRING("  2. Rendering model: decoding with rendering on the screen (-r option)\n"));
    msdk_printf(MSDK_STRING("  3. Dump model: decoding with YUV dumping (-o option)\n"));
    msdk_printf(MSDK_STRING("\n"));
    msdk_printf(MSDK_STRING("Options:\n"));
    msdk_printf(MSDK_STRING("   [-hw]                     - use platform specific SDK implementation (default)\n"));
    msdk_printf(MSDK_STRING("   [-sw]                     - use software implementation, if not specified platform specific SDK implementation is used\n"));
    msdk_printf(MSDK_STRING("   [-p guid]                 - 32-character hexadecimal guid string\n"));
    msdk_printf(MSDK_STRING("   [-path path]              - path to plugin (valid only in pair with -p option)\n"));
    msdk_printf(MSDK_STRING("                               (optional for Media SDK in-box plugins, required for user-decoder ones)\n"));
    msdk_printf(MSDK_STRING("   [-f]                      - rendering framerate\n"));
    msdk_printf(MSDK_STRING("   [-w]                      - output width\n"));
    msdk_printf(MSDK_STRING("   [-h]                      - output height\n"));
    msdk_printf(MSDK_STRING("   [-di bob/adi]             - enable deinterlacing BOB/ADI\n"));
    msdk_printf(MSDK_STRING("\n"));
    msdk_printf(MSDK_STRING("JPEG Chroma Type:\n"));
    msdk_printf(MSDK_STRING("   [-jpeg_rgb] - RGB Chroma Type\n"));
    msdk_printf(MSDK_STRING("Output format parameters:\n"));
    msdk_printf(MSDK_STRING("   [-i420] - pipeline output format: NV12, output file format: I420\n"));
    msdk_printf(MSDK_STRING("   [-nv12] - pipeline output format: NV12, output file format: NV12\n"));
    msdk_printf(MSDK_STRING("   [-rgb4] - pipeline output format: RGB4, output file format: RGB4\n"));
    msdk_printf(MSDK_STRING("   [-rgb4_fcr] - pipeline output format: RGB4 in full color range, output file format: RGB4 in full color range\n"));
    msdk_printf(MSDK_STRING("   [-p010] - pipeline output format: P010, output file format: P010\n"));
    msdk_printf(MSDK_STRING("   [-a2rgb10] - pipeline output format: A2RGB10, output file format: A2RGB10\n"));
    msdk_printf(MSDK_STRING("\n"));
#if D3D_SURFACES_SUPPORT
    msdk_printf(MSDK_STRING("   [-d3d]                    - work with d3d9 surfaces\n"));
    msdk_printf(MSDK_STRING("   [-d3d11]                  - work with d3d11 surfaces\n"));
    msdk_printf(MSDK_STRING("   [-r]                      - render decoded data in a separate window \n"));
    msdk_printf(MSDK_STRING("   [-wall w h n m t tmo]     - same as -r, and positioned rendering window in a particular cell on specific monitor \n"));
    msdk_printf(MSDK_STRING("       w                     - number of columns of video windows on selected monitor\n"));
    msdk_printf(MSDK_STRING("       h                     - number of rows of video windows on selected monitor\n"));
    msdk_printf(MSDK_STRING("       n(0,.,w*h-1)          - order of video window in table that will be rendered\n"));
    msdk_printf(MSDK_STRING("       m(0,1..)              - monitor id \n"));
    msdk_printf(MSDK_STRING("       t(0/1)                - enable/disable window's title\n"));
    msdk_printf(MSDK_STRING("       tmo                   - timeout for -wall option\n"));
    msdk_printf(MSDK_STRING("Screen capture parameters:\n"));
    msdk_printf(MSDK_STRING("   [-scr:w]                  - screen resolution width\n"));
    msdk_printf(MSDK_STRING("   [-scr:h]                  - screen resolution height\n"));
    msdk_printf(MSDK_STRING("\n"));

#endif
#if defined(LIBVA_SUPPORT)
    msdk_printf(MSDK_STRING("   [-vaapi]                  - work with vaapi surfaces\n"));
#endif
#if defined(LIBVA_X11_SUPPORT)
    msdk_printf(MSDK_STRING("   [-r]                      - render decoded data in a separate X11 window \n"));
#endif
#if defined(LIBVA_WAYLAND_SUPPORT)
    msdk_printf(MSDK_STRING("   [-rwld]                   - render decoded data in a Wayland window \n"));
    msdk_printf(MSDK_STRING("   [-perf]                   - turn on asynchronous flipping for Wayland rendering \n"));
#endif
#if defined(LIBVA_DRM_SUPPORT)
    msdk_printf(MSDK_STRING("   [-rdrm]                   - render decoded data in a thru DRM frame buffer\n"));
    msdk_printf(MSDK_STRING("   [-window x y w h]         - set render window position and size\n"));
#endif
    msdk_printf(MSDK_STRING("   [-low_latency]            - configures decoder for low latency mode (supported only for H.264 and JPEG codec)\n"));
    msdk_printf(MSDK_STRING("   [-calc_latency]           - calculates latency during decoding and prints log (supported only for H.264 and JPEG codec)\n"));
    msdk_printf(MSDK_STRING("   [-async]                  - depth of asynchronous pipeline. default value is 4. must be between 1 and 20\n"));
    msdk_printf(MSDK_STRING("   [-gpucopy::<on,off>] Enable or disable GPU copy mode\n"));
    msdk_printf(MSDK_STRING("   [-timeout]                - timeout in seconds\n"));
#if _MSDK_API >= MSDK_API(1,22)
    msdk_printf(MSDK_STRING("   [-dec_postproc force/auto] - resize after decoder using direct pipe\n"));
    msdk_printf(MSDK_STRING("                  force: instruct to use decoder-based post processing\n"));
    msdk_printf(MSDK_STRING("                         or fail if the decoded stream is unsupported\n"));
    msdk_printf(MSDK_STRING("                  auto: instruct to use decoder-based post processing for supported streams \n"));
    msdk_printf(MSDK_STRING("                        or perform VPP operation through separate pipeline component for unsupported streams\n"));

#endif //_MSDK_API >= MSDK_API(1,22)
#if !defined(_WIN32) && !defined(_WIN64)
    msdk_printf(MSDK_STRING("   [-threads_num]            - number of mediasdk task threads\n"));
    msdk_printf(MSDK_STRING("   [-threads_schedtype]      - scheduling type of mediasdk task threads\n"));
    msdk_printf(MSDK_STRING("   [-threads_priority]       - priority of mediasdk task threads\n"));
    msdk_printf(MSDK_STRING("\n"));
    msdk_thread_printf_scheduling_help();
#endif
#if defined(_WIN32) || defined(_WIN64)
    msdk_printf(MSDK_STRING("   [-jpeg_rotate n]          - rotate jpeg frame n degrees \n"));
    msdk_printf(MSDK_STRING("       n(90,180,270)         - number of degrees \n"));

    msdk_printf(MSDK_STRING("\nFeatures: \n"));
    msdk_printf(MSDK_STRING("   Press 1 to toggle fullscreen rendering on/off\n"));
#endif
    msdk_printf(MSDK_STRING("\n"));
    msdk_printf(MSDK_STRING("Example:\n"));
    msdk_printf(MSDK_STRING("  %s h265 -i in.bit -o out.yuv -p 15dd936825ad475ea34e35f3f54217a6\n"), strAppName);
}

mfxStatus ParseInputString(msdk_char* strInput[], mfxU8 nArgNum, sInputParams* pParams)
{
    if (1 == nArgNum)
    {
        PrintHelp(strInput[0], NULL);
        return MFX_ERR_UNSUPPORTED;
    }

    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);

    // set default implementation
    pParams->bUseHWLib = true;
    pParams->bUseFullColorRange = false;
#if defined(LIBVA_SUPPORT)
    pParams->libvaBackend = MFX_LIBVA_DRM;
#endif

    for (mfxU8 i = 1; i < nArgNum; i++)
    {
        if (MSDK_CHAR('-') != strInput[i][0])
        {
            mfxStatus sts = StrFormatToCodecFormatFourCC(strInput[i], pParams->videoType);
            if (sts != MFX_ERR_NONE)
            {
                PrintHelp(strInput[0], MSDK_STRING("Unknown codec"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (!IsDecodeCodecSupported(pParams->videoType))
            {
                PrintHelp(strInput[0], MSDK_STRING("Unsupported codec"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (pParams->videoType == CODEC_MVC)
            {
                pParams->videoType = MFX_CODEC_AVC;
                pParams->bIsMVC = true;
            }
            continue;
        }

        if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-sw")))
        {
            pParams->bUseHWLib = false;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-hw")))
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
            pParams->mode = MODE_RENDERING;
            // use d3d9 rendering by default
            if (SYSTEM_MEMORY == pParams->memType)
                pParams->memType = D3D9_MEMORY;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-wall")))
        {
            if(i + 6 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -wall key"));
                return MFX_ERR_UNSUPPORTED;
            }
            // use d3d9 rendering by default
            if (SYSTEM_MEMORY == pParams->memType)
                pParams->memType = D3D9_MEMORY;

            pParams->mode = MODE_RENDERING;

            msdk_opt_read(strInput[++i], pParams->nWallW);
            msdk_opt_read(strInput[++i], pParams->nWallH);
            msdk_opt_read(strInput[++i], pParams->nWallCell);
            msdk_opt_read(strInput[++i], pParams->nWallMonitor);

            mfxU32 nTitle;
            msdk_opt_read(strInput[++i], nTitle);

            pParams->bWallNoTitle = 0 == nTitle;

            msdk_opt_read(strInput[++i], pParams->nTimeout);
        }
#endif
#if defined(LIBVA_SUPPORT)
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-vaapi")))
        {
            pParams->memType = D3D9_MEMORY;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-r")))
        {
            pParams->memType = D3D9_MEMORY;
            pParams->mode = MODE_RENDERING;
            pParams->libvaBackend = MFX_LIBVA_X11;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-rwld")))
        {
            pParams->memType = D3D9_MEMORY;
            pParams->mode = MODE_RENDERING;
            pParams->libvaBackend = MFX_LIBVA_WAYLAND;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-perf")))
        {
            pParams->bPerfMode = true;
        }
        else if (0 == msdk_strncmp(strInput[i], MSDK_STRING("-rdrm"), 5))
        {
            pParams->memType = D3D9_MEMORY;
            pParams->mode = MODE_RENDERING;
            pParams->libvaBackend = MFX_LIBVA_DRM_MODESET;
            if (strInput[i][5]) {
                if (strInput[i][5] != '-') {
                    PrintHelp(strInput[0], MSDK_STRING("unsupported monitor type"));
                    return MFX_ERR_UNSUPPORTED;
                }
                pParams->monitorType = getMonitorType(&strInput[i][6]);
                if (pParams->monitorType >= MFX_MONITOR_MAXNUMBER) {
                    PrintHelp(strInput[0], MSDK_STRING("unsupported monitor type"));
                    return MFX_ERR_UNSUPPORTED;
                }
            } else {
                pParams->monitorType = MFX_MONITOR_AUTO; // that's case of "-rdrm" pure option
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-window")))
        {
            if(i +4 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -window key"));
                return MFX_ERR_UNSUPPORTED;
            }
            msdk_opt_read(strInput[++i], pParams->nRenderWinX);
            msdk_opt_read(strInput[++i], pParams->nRenderWinY);
            msdk_opt_read(strInput[++i], pParams->Width);
            msdk_opt_read(strInput[++i], pParams->Height);

            if (0 == pParams->Width)
                pParams->Width = 320;
            if (0 == pParams->Height)
                pParams->Height = 240;

            pParams->bRenderWin = true;
        }
#endif
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-low_latency")))
        {
            switch (pParams->videoType)
            {
                case MFX_CODEC_HEVC:
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
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-jpeg_rotate")))
        {
            if(MFX_CODEC_JPEG != pParams->videoType)
                return MFX_ERR_UNSUPPORTED;

            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -jpeg_rotate key"));
                return MFX_ERR_UNSUPPORTED;
            }

            msdk_opt_read(strInput[++i], pParams->nRotation);
            if((pParams->nRotation != 90)&&(pParams->nRotation != 180)&&(pParams->nRotation != 270))
            {
                PrintHelp(strInput[0], MSDK_STRING("-jpeg_rotate is supported only for 90, 180 and 270 angles"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-calc_latency")))
        {
            switch (pParams->videoType)
            {
                case MFX_CODEC_HEVC:
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
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-async")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -async key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nAsyncDepth))
            {
                PrintHelp(strInput[0], MSDK_STRING("async is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-timeout")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -timeout key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nTimeout))
            {
                PrintHelp(strInput[0], MSDK_STRING("timeout is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }

        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-di")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -di key"));
                return MFX_ERR_UNSUPPORTED;
            }
            msdk_char diMode[32] = {};
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], diMode))
            {
                PrintHelp(strInput[0], MSDK_STRING("deinterlace value is not set"));
                return MFX_ERR_UNSUPPORTED;
            }

            if (0 == msdk_strcmp(diMode, MSDK_CHAR("bob")))
            {
                pParams->eDeinterlace = MFX_DEINTERLACING_BOB;
            }
            else if (0 == msdk_strcmp(diMode, MSDK_CHAR("adi")))
            {
                pParams->eDeinterlace = MFX_DEINTERLACING_ADVANCED;
            }
            else
            {
                PrintHelp(strInput[0], MSDK_STRING("deinterlace value is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-gpucopy::on")))
        {
            pParams->gpuCopy = MFX_GPUCOPY_ON;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-gpucopy::off")))
        {
            pParams->gpuCopy = MFX_GPUCOPY_OFF;
        }
#if !defined(_WIN32) && !defined(_WIN64)
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-threads_num")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -threads_num key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nThreadsNum))
            {
                PrintHelp(strInput[0], MSDK_STRING("threads_num is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-threads_schedtype")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -threads_schedtype key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_thread_get_schedtype(strInput[++i], pParams->SchedulingType))
            {
                PrintHelp(strInput[0], MSDK_STRING("threads_schedtype is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-threads_priority")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -threads_priority key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->Priority))
            {
                PrintHelp(strInput[0], MSDK_STRING("threads_priority is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
#endif // #if !defined(_WIN32) && !defined(_WIN64)
#if _MSDK_API >= MSDK_API(1,22)
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-dec_postproc")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for \"-dec_postproc\", right is  \"--dec_postproc force//auto\""));
                return MFX_ERR_UNSUPPORTED;
            }
            msdk_char postProcMode[32] = {};
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], postProcMode))
            {
                PrintHelp(strInput[0], MSDK_STRING("dec_postproc value is not set"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (0 == msdk_strcmp(postProcMode, MSDK_STRING("auto")))
            {
                pParams->nDecoderPostProcessing = MODE_DECODER_POSTPROC_AUTO;
            }
            else if (0 == msdk_strcmp(postProcMode, MSDK_STRING("force")))
            {
                pParams->nDecoderPostProcessing = MODE_DECODER_POSTPROC_FORCE;
            }
            else
            {
                PrintHelp(strInput[0], MSDK_STRING("dec_postproc is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
#endif //_MSDK_API >= MSDK_API(1,22)
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-f")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -f key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nMaxFPS))
            {
                PrintHelp(strInput[0], MSDK_STRING("rendering frame rate is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-scr:w")))
        {
            if (i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -scr:w key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->scrWidth))
            {
                PrintHelp(strInput[0], MSDK_STRING("screen width rate is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-scr:h")))
        {
            if (i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -scr:h key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->scrHeight))
            {
                PrintHelp(strInput[0], MSDK_STRING("screen height is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-w")))
        {
            if (i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -w key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->Width))
            {
                PrintHelp(strInput[0], MSDK_STRING("width is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-h")))
        {
            if (i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -h key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->Height))
            {
                PrintHelp(strInput[0], MSDK_STRING("height is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-n")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -n key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nFrames))
            {
                PrintHelp(strInput[0], MSDK_STRING("rendering frame rate is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-jpeg_rgb")))
        {
            if(MFX_CODEC_JPEG == pParams->videoType)
            {
               pParams->chromaType = MFX_JPEG_COLORFORMAT_RGB;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-i420")))
        {
            pParams->fourcc = MFX_FOURCC_NV12;
            pParams->outI420 = true;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-nv12")))
        {
            pParams->fourcc = MFX_FOURCC_NV12;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-rgb4")))
        {
            pParams->fourcc = MFX_FOURCC_RGB4;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-rgb4_fcr")))
        {
            pParams->fourcc = MFX_FOURCC_RGB4;
            pParams->bUseFullColorRange = true;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-p010")))
        {
            pParams->fourcc = MFX_FOURCC_P010;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-a2rgb10")))
        {
            pParams->fourcc = MFX_FOURCC_A2RGB10;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-path")))
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
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-i:null")))
        {
            ;
        }
        else // 1-character options
        {
            switch (strInput[i][1])
            {
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
            case MSDK_CHAR('i'):
                if (++i < nArgNum) {
                    msdk_opt_read(strInput[i], pParams->strSrcFile);
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-i' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('o'):
                if (++i < nArgNum) {
                    pParams->mode = MODE_FILE_DUMP;
                    msdk_opt_read(strInput[i], pParams->strDstFile);
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-o' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('?'):
                PrintHelp(strInput[0], NULL);
                return MFX_ERR_UNSUPPORTED;
            default:
                {
                    std::basic_stringstream<msdk_char> stream;
                    stream << MSDK_STRING("Unknown option: ") << strInput[i];
                    PrintHelp(strInput[0], stream.str().c_str());
                    return MFX_ERR_UNSUPPORTED;
                }
            }
        }
    }

    if (0 == msdk_strlen(pParams->strSrcFile) && MFX_CODEC_CAPTURE != pParams->videoType)
    {
        msdk_printf(MSDK_STRING("error: source file name not found"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (MFX_CODEC_CAPTURE == pParams->videoType)
    {
        if (!pParams->scrWidth || !pParams->scrHeight)
        {
            msdk_printf(MSDK_STRING("error: for screen capture, width and height must be specified manually (-scr:w and -scr:h)"));
            return MFX_ERR_UNSUPPORTED;
        }
    }
    else if (pParams->scrWidth || pParams->scrHeight)
    {
        msdk_printf(MSDK_STRING("error: width and height parameters are supported only by screen capture decoder"));
        return MFX_ERR_UNSUPPORTED;
    }

    if ((pParams->mode == MODE_FILE_DUMP) && (0 == msdk_strlen(pParams->strDstFile)))
    {
        msdk_printf(MSDK_STRING("error: destination file name not found"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (MFX_CODEC_MPEG2   != pParams->videoType &&
        MFX_CODEC_AVC     != pParams->videoType &&
        MFX_CODEC_HEVC    != pParams->videoType &&
        MFX_CODEC_VC1     != pParams->videoType &&
        MFX_CODEC_JPEG    != pParams->videoType &&
        MFX_CODEC_CAPTURE != pParams->videoType &&
        MFX_CODEC_VP8     != pParams->videoType &&
        MFX_CODEC_VP9     != pParams->videoType)
    {
        PrintHelp(strInput[0], MSDK_STRING("Unknown codec"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (pParams->nAsyncDepth == 0)
    {
        pParams->nAsyncDepth = 4; //set by default;
    }

    return MFX_ERR_NONE;
}



//////////////////////////////////////////////


//
 int makeBmpInfoHeader_yv12(  unsigned int bits,  int iWidth,  int iHeight,  BITMAPINFOHEADER  *  p  );

 




 //
extern  "C"  int  __declspec(  dllexport  )qdcInitDecompressVideo(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_compress,  QY_VIDEO_HEADER  *  pVh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{	
	int						iErr	=	-1;
	//QDC_OBJ_INFO			qdcObjInfo;
	QDC_OBJ_trans		*	pObj	=	NULL;	
	TCHAR					tBuf[128];


	//
	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;

	//  2016/04/26
	if  (  tmpDec_setFuncs(  pQdcObjInfo  )  )  {
		return  -1;
	}  


	//
	VIDEO_COMPRESSOR_cfgCommon  *  pVideoCfgCommon  =  (  VIDEO_COMPRESSOR_cfgCommon  *  )pVideoCompressorCfg_reserved;

	//
	memcpy(  &pQdcObjInfo->cfg.v,  pVideoCfgCommon,  sizeof(  pQdcObjInfo->cfg.v  )  );

	//  memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_trans  *  )malloc(  sizeof(  QDC_OBJ_trans  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	pQdcObjInfo->var.pObj  =  pObj;
	
	//
	pQdcObjInfo->var.ucbTransformFuncsOk  =  TRUE;	//  bTransformFuncsOk(  pQdcObjInfo  );
	if  (  !pQdcObjInfo->var.ucbTransformFuncsOk  )  {
		#ifdef  _DEBUG
				OutputDebugString(  _T(  "initDecV failed, bTransformFuncs false\n"  )  );
		#endif
		goto  errLabel;
	}

	//
	sInputParams        Params;   // input parameters from command line
		
    
    mfxStatus sts = MFX_ERR_NONE; // return value check

	//
	//memset(  &Params,  0,  sizeof(  Params  )  );

	//
	//  Params.nAsyncDepth  =  1;

	//
	TCHAR  *  argv[30];
	int		cnt  =  0;
	argv[cnt]  =  _T(  "appName"  );						cnt  ++  ;
	//
	TCHAR  argv_fourcc[32]  =  _T(  ""  );
	BOOL  bUse_lowLat  =  FALSE;
	//
	int  iFourcc_enc  =  fourccStr2i(  pVideoCfgCommon->fourccStr  );
	switch  (  iFourcc_enc  )  {
			case  CONST_fourcc_h264:
				  _tcsncpy(  argv_fourcc,  _T(  "h264"  ),  mycountof(  argv_fourcc  )  );
				  //
				  bUse_lowLat  =  TRUE;
				  //
				  break;
			case  CONST_fourcc_HEVC:
				  _tcsncpy(  argv_fourcc,  _T(  "h265"  ),  mycountof(  argv_fourcc  )  );
				  //				  
				  break;
			default:
				    char  buf[128];
					iFourcc2Str(  iFourcc_enc,  buf,  mycountof(  buf  )  );
				    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qdcInitDecV failed, unsupported fourcc_enc [%S]"  ),  buf  );
					tmp_showInfo(  tBuf  );
					goto  errLabel;
	}
	argv[cnt]  =  argv_fourcc;								cnt  ++  ;
	//
	argv[cnt]  =  _T(  "-i"  );								cnt  ++  ;
	argv[cnt]  =  _T(  "input.264"  );						cnt  ++  ;
	argv[cnt]  =  _T(  "-o"  );								cnt  ++  ;
	argv[cnt]  =  _T(  "c:\\tttbbb\\testoutput.yuv"  );		cnt  ++  ;
#if  0
	argv[cnt]  =  _T(  "-hw"  );							cnt  ++  ;
#else
	OutputDebugString(  _T(  "Note: hw is off\n"  )  );
#endif
	//
	if  (  bUse_lowLat  )  {
		argv[cnt]  =  _T(  "-low_latency"  );					cnt  ++  ;
	}
	argv[cnt]  =  _T(  "-async"  );							cnt  ++  ;
	argv[cnt]  =  _T(  "1"  );								cnt  ++  ;
	//

	//  2016/04/19	
	unsigned  short  usPktResType  =  0;

	//  2015/09/28
	mfxVersion  ver;
	if  (  IsSupported_hwAcclD11(  &ver  )  )  {

		//  2015/09/27
		#define		MIN_hdDec_majorVer_sharedTex	1
		#define		MIN_hdDec_minorVer_sharedTex	8	//  2015/10/18.1.8是hd4400	//  11
		
		//
		unsigned  char  ucbUsing_sharedTex  =  FALSE;

		//
		if  (  ver.Major  >=  MIN_hdDec_majorVer_sharedTex
			&&  ver.Minor  >=  MIN_hdDec_minorVer_sharedTex  )
		{
			ucbUsing_sharedTex  =  TRUE;
		}

		// 2015/10/03. 非3D程序需要有dlgTalk窗口，不能用纹理来显示。
		//  createDXGIFactory1也很重要
		if  (  pQdcObjInfo->cfg.v.usPktResType_suggested  !=  CONST_pktResType_sharedTex
			||  !g_pGuiOpen->pf_CreateDXGIFactory1  )  
		{
			ucbUsing_sharedTex  =  FALSE;
		}
		//
		#ifdef  _DEBUG
				#if  0
					 ucbUsing_sharedTex  =  FALSE;		
					 OutputDebugString(  _T(  "TEST: set ucbUsing_sharedTex to false\n"  )  );
				#endif
		#endif
		//
		if  (  ucbUsing_sharedTex  )  usPktResType  =  CONST_pktResType_sharedTex;
		//

	}
	//  201604/19
	pQdcObjInfo->var.usPktResType_dec  =  usPktResType;
		
	//	
	if  (  pQdcObjInfo->var.usPktResType_dec  ==  CONST_pktResType_sharedTex  )  {		
		argv[cnt]  =  _T(  "-d3d11"  );		cnt  ++  ;		
		argv[cnt]  =  _T(  "-r"  );			cnt  ++  ;
		}
	else  {
		  #define		MIN_hdDec_majorVer_d3d		1
		  #define		MIN_hdDec_minorVer_d3d		16	//  2016/04/19.	1.16是hd573		//  
		
		  //
		  unsigned  char  ucbUsing_d3d  =  FALSE;

		  //
		  if  (  ver.Major  >=  MIN_hdDec_majorVer_d3d
			  &&  ver.Minor  >=  MIN_hdDec_minorVer_d3d  )
		  {
			  ucbUsing_d3d  =  TRUE;
		  }

		  //
		  if  (  ucbUsing_d3d  )  {
			  //argv[cnt]  =  _T(  "-d3d"  );		cnt  ++  ;		//  2014/07/04. 
			  argv[cnt]  =  _T(  "-d3d11"  );		cnt  ++  ;		//  2014/07/04. 
		  }
	}

	//
	int  argc  =  min(  cnt,  sizeof(  argv  )  /  sizeof(  argv[1]  )  );

	try  {

		//
        //  ParseInputString_dec((  msdk_char  **  )&argv[1], --argc, &Params);


	sts = ParseInputString(argv, (mfxU8)argc, &Params);
    MSDK_CHECK_PARSE_RESULT(sts, MFX_ERR_NONE, 1);
	
	{	
		TCHAR	tBuf[128]  =  _T(  ""  );
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "hdDecV init: %s memType %d,  bLowLat %d. bAppX64 %d. pktResType %d"  ),  argv_fourcc,  (  int  )Params.memType,  Params.bLowLat,  (  int  )g_pGuiOpen->ucbAppX64,  (  int  )pQdcObjInfo->var.usPktResType_dec    );
		tmp_showInfo(  tBuf  );		
	}

	//
	CMyDecPipeline  *   pPipeline  =  NULL; // pipeline for decoding, includes input file reader, decoder and output file writer
	pPipeline  =  new  CMyDecPipeline;
	if  (  !pPipeline  )  goto  errLabel;
	pObj->pVar  =  pPipeline;

	//  2014/03/29
	pPipeline->m_var.pQdcObjInfo  =  pQdcObjInfo;
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

	}
	catch (std::exception &ex)
    {
#ifdef UNICODE
        wprintf(L"\nstd::exception caught: %S\n", ex.what());    
#else
        printf("\nstd::exception caught: %s\n", ex.what());    
#endif
		tmp_showInfo(  _T(  "qdcInitDecV: exception caught"  )  );
		goto  errLabel;
		}
    catch (...)
    {
        msdk_printf(MSDK_STRING("\nUnknown exception caught\n"));
		tmp_showInfo(  _T(  "qdcInitDecV: Unknown exception caught"  )  );
		goto  errLabel;
    }



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
	QDC_OBJ_trans	*	pObj	=	(  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;

	if  (  pObj  )  {
		//
		if  (  pObj->pVar  )  {
			CDecodingPipeline  *  pPipeline  =  (  CDecodingPipeline  *  )pObj->pVar;
			//
			// 秪峈婓decodingPipeline腔close祥夔覃蚚2棒ㄛ垀眕祥婬涴爵覃蚚坳ㄛ秪婓價濬腔昴凳滲杅爵眒冪覃蚚賸
			// pPipeline->Close(  );
			//
			delete  pPipeline;
			pObj->pVar  =  NULL;
		}

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
	QDC_OBJ_trans	*	pObj	=	(  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;
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
		tmp_showInfo(  _T(  "qdcDecVideoㄩ qPostMsg failed"  )  );
	}
#endif
	//  2014/03/25. not supported
	return  -1;


#if  0
	if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pQdcObjInfo->cbInputBuffer  )  return  -1;
#endif

	CMyDecPipeline  *  pPipeline  =  (  CMyDecPipeline  *  )pObj->pVar;


	int  frameNumber  =  1;
#if  0
	int  imgWidth,  imgHeight;
	imgWidth  =  pBmpInfo_input->bmiHeader.biWidth;
	imgHeight  =  pBmpInfo_input->bmiHeader.biHeight;
#endif

#if  0

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

	return  frameNumber;
}



extern  "C"  int  __declspec(  dllexport  )  qdcDecompressVideoRun(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int					iErr	=	-1;
	QDC_OBJ_trans	*	pObj	=	(  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;
	CMyDecPipeline  *  pPipeline  =  (  CMyDecPipeline  *  )pObj->pVar;
	TCHAR				tBuf[256]	=	_T(  ""  );
	//  2014/07/17
	DEBUG_step_dec	*	pDebugStepDec  =  (  DEBUG_step_dec  *  )tmp_getDebugStep_sth(  0,  CONST_debugStepType_dec,  pQdcObjInfo->var.pDebugStep  );
	if  (  !pDebugStepDec  )  return  -1;
	
	//
	mfxStatus sts = MFX_ERR_NONE; // return value check

	try  {
	
		sts  =  pPipeline->myRun(  pQdcObjInfo  );
	
		//  2014/07/17
		pDebugStepDec->sts_run  =  sts;

		//  2014/05/28
		TCHAR	tBuf[128]  =  _T(  ""  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "decVPipeline->Run returns sts %d"  ),  sts  );
		tmp_showInfo(  tBuf  );


		}		
	catch (std::exception &ex)  {

		//  2014/07/17
		pDebugStepDec->bException  =  TRUE;

		//
#ifdef UNICODE
        wprintf(L"\nstd::exception caught: %S\n", ex.what());    
#else
        printf("\nstd::exception caught: %s\n", ex.what());    
#endif
		tmp_showInfo(  _T(  "qdcDecVRun: exception caught"  )  );
		goto  errLabel;
		}
    catch (...)  {

		//  2014/07/17
		pDebugStepDec->bException  =  TRUE;

		//
        msdk_printf(MSDK_STRING("\nUnknown exception caught\n"));
		tmp_showInfo(  _T(  "qdcDecVRun: Unknown exception caught"  )  );
		goto  errLabel;
    }


	iErr  =  0;
errLabel:
	return  iErr;
}