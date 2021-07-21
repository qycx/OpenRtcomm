using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Java.Lang;
using Java.Nio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace qy.Droid
{
    //
    class CQdcObj_mediaCodec
    {
        //public int m_index_qdcUnit;
        //
        public bool bDec;

        //
        public object obj_qdcUnit;


        /*
        struct {
        char* pBuf;
        int iBufSize;
        int len;
    }
    output;
        */
        //
        public CQdcObj_mediaCodec()
        {
            //m_index_qdcUnit = -1;
            //
            bDec = false;
            //
            //memset(&output, 0, sizeof(output));
        }



    };

    partial class qyFuncs_Droid
{

        public static int qdcInit_mediaCodec(ref QDC_MGR p)
        {
            int iRet = -1;

            iRet = 0;
            return iRet;

        }

        public static int qdcExit_mediaCodec(ref QDC_MGR p)
        {
            int iRet = -1;

            iRet = 0;
            return iRet;

        }

        public static unsafe int qdcInitDecompressVideo_mediaCodec(ref VIDEO_COMPRESSOR_CFG pVideoCompressorCfg, ref QY_VIDEO_HEADER pVh_compress, ref QY_VIDEO_HEADER pVh_decompress, ref QOI_common pQdcObjInfo)
        {
            int iErr = -1;
            bool bDbg = true;



            int iFourcc;

            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            //
            if (pQdcObjInfo.var.pObj != null) return -1;

            //
            pQdcObjInfo.cfg.v = pVideoCompressorCfg.common;


            //
            pQdcObjInfo.var.pObj = new CQdcObj_mediaCodec();
            if (pQdcObjInfo.var.pObj == null) goto errLabel;
            CQdcObj_mediaCodec pObj = (CQdcObj_mediaCodec)pQdcObjInfo.var.pObj;

            //
            pQdcObjInfo.var.ucbTransformFuncsOk = true;

            //
            pObj.bDec = true;


            //fixed (byte* fourccStr = pVideoCompressorCfg.common.fourccStr) 
            {
                iFourcc = pVideoCompressorCfg.common.head.iFourcc;
            }

            //if (0 != TmpFfmpeg.DecV_init(pObj.m_index_qdcUnit, iFourcc, bDbg)) goto errLabel;

            //
            pQdcObjInfo.bHeadLen = 1 + 7 * sizeof(int);
            pQdcObjInfo.nPktsDeced = 0;

            //
#if false
            int index_taskInfo = qyFuncs.getQmcTaskInfoIndexBySth(null, pProcInfo, pVideoCompressorCfg.iTaskId);
            QMC_TASK_INFO pTaskInfo = qyFuncs.getQmcTaskInfoByIndex(null, pProcInfo, index_taskInfo, "");
            if (null==pTaskInfo) goto errLabel;
            QMC_taskData_conf pTc = (QMC_taskData_conf)pTaskInfo.pTaskData;
            if (pTc.uiType != Consts.CONST_taskDataType_conf) goto errLabel;
            if (null == pTc.share_eglContext)
            {
                qyFuncs.showInfo_open(0, null, "qdcInitDecV_mediaCodec failed, share_eglContext is null");
                goto errLabel;
            }
#endif

            //
            string pName = string.Format("qdcDecEvt{0}", qyFuncs.getuiNextTranNo(null, 0, null));
            pQdcObjInfo.hEvent_notifyToQuit = new System.Threading.EventWaitHandle(false, System.Threading.EventResetMode.AutoReset, new string(pName));

            //
            if (pQdcObjInfo.cfg.v.usPktResType_suggested!=Consts.CONST_pktResType_sharedTex)
            {
                qyFuncs.showInfo_open(0, null, "qdcInitDecompressVideo_mediaCodec failed, cfg.usPktResType err");
                goto errLabel;
            }
            pQdcObjInfo.var.usPktResType_dec = Consts.CONST_pktResType_sharedTex;

            //
            pObj.obj_qdcUnit = new decObj_mediaCodec();
            decObj_mediaCodec obj = (decObj_mediaCodec)pObj.obj_qdcUnit;

            //
            //obj.m_sharedEglContext = (Android.Opengl.EGLContext)pTc.share_eglContext;
            obj.m_sharedEglContext = (Android.Opengl.EGLContext)pVideoCompressorCfg.shared_eglContext;
            //
            obj.m_qoi = pQdcObjInfo;

            //
            obj.m_iW = pVh_decompress.bih.biWidth;
            obj.m_iH = pVh_decompress.bih.biHeight;

            //
            QY_TRANSFORM pTransform = (QY_TRANSFORM)pQdcObjInfo.cfg.v.pParent_transform;
            fixed(char * pName1 = pTransform.video.q2.cfg.name)
            {
                obj.mTag = "" + new string(pName1);
            }
            int ii = 0;
#if DEBUG
            //obj.m_bTest = true;


#endif

            //
            obj.m_wrapper = new decObj_mediaCodec.decObj_mediaCodec_Wrapper(obj);
            obj.m_th = new Thread(obj.m_wrapper, "codec test");
            obj.m_th.Start();


            //
            iErr = 0;
        errLabel:
            if (0 != iErr)
            {
                qdcExitDecompressVideo_mediaCodec(ref pQdcObjInfo);
            }

            return iErr;
        }
        public static unsafe int qdcExitDecompressVideo_mediaCodec(ref QOI_common pQdcObjInfo)
        {
            int iErr = -1;
            bool bDbg = true;

            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();


            if (null == pQdcObjInfo.var.pObj) return 0;
            CQdcObj_mediaCodec pObj = (CQdcObj_mediaCodec)pQdcObjInfo.var.pObj;

            //TmpFfmpeg.DecV_exit(pObj.m_index_qdcUnit, bDbg);
            decObj_mediaCodec obj = (decObj_mediaCodec)pObj.obj_qdcUnit;
            if (null != obj)
            {
                if ( null!=obj.m_th )
                {
                    obj.m_th.Join();
                    obj.m_th = null;
                }
                if (null != obj.m_wrapper)
                {
                    obj.m_wrapper = null;

                }
                //
            }

            //
            pObj.obj_qdcUnit = null;

            //
            if (pQdcObjInfo.hEvent_notifyToQuit != null)
            {
                System.Threading.EventWaitHandle hEvt = (System.Threading.EventWaitHandle)pQdcObjInfo.hEvent_notifyToQuit;
                hEvt.Close();
                pQdcObjInfo.hEvent_notifyToQuit = null;
            }

            //
            pQdcObjInfo.bb_input = null;
            pQdcObjInfo.bb_output = null;

            //
            pQdcObjInfo.var.pObj = null;


            //
            iErr = 0;
            return iErr; ;
        }

        public static unsafe int qdcDecompressVideo_mediaCodec(ref QOI_common pQdcObjInfo, ref BITMAPINFOHEADER pBmpInfo_input, IntPtr pInput, int iSampleTimeInMs)    //  2012/06/17
        {
            int iErr = -1;
            int iPaddingSize = 128;

            bool bDbg = false;
            string str;
#if DEBUG
            //
            //bDbg = true;
#endif
            //
            CQdcObj_mediaCodec pObj = (CQdcObj_mediaCodec)pQdcObjInfo.var.pObj;

            //
            if (pQdcObjInfo.bb_input == null)
            {
                pQdcObjInfo.bb_input = ByteBuffer.AllocateDirect(Consts.bufSize_transferVideoData);
                if (pQdcObjInfo.bb_input == null) goto errLabel;
                //
                qyFuncs.traceLog("qdcDecVideo_android: bb_input alloc");
            }
            if (pQdcObjInfo.bb_output == null)
            {
                pQdcObjInfo.bb_output = ByteBuffer.AllocateDirect(128);
                if (pQdcObjInfo.bb_output == null) goto errLabel;
                //
                qyFuncs.traceLog("qdcDecVideo_android: bb_outpt alloc");
            }
            ByteBuffer bb_input = (ByteBuffer)pQdcObjInfo.bb_input;
            ByteBuffer bb_output = (ByteBuffer)pQdcObjInfo.bb_output;
            byte* pBbInput = (byte*)bb_input.GetDirectBufferAddress();
            if (null == pBbInput) goto errLabel;
            byte* pBbOutput = (byte*)bb_output.GetDirectBufferAddress();
            if (null == pBbOutput) goto errLabel;

            //
            if (pBmpInfo_input.biSizeImage + iPaddingSize > bb_input.Capacity())
            {
                qyFuncs.traceLog("qdcDecVideo failed: bb_input is too small");
                goto errLabel;
            }
            qyFuncs.mymemcpy((IntPtr)pBbInput, pInput, (uint)pBmpInfo_input.biSizeImage);

            //
            int total_nums = 7;
            byte len = (byte)(1 + total_nums * 4);
            //int head_array[7];
            if (pQdcObjInfo.bHeadLen < len)
            {
                qyFuncs.traceLog("qdcDecVideo failed, bHeadLen error");
                goto errLabel;
            }

            //
            *pBbOutput = pQdcObjInfo.bHeadLen;

            //
            //if (0 != TmpFfmpeg.DecV_data(pObj.m_index_qdcUnit, bb_input, pBmpInfo_input.biSizeImage, iPaddingSize, bb_output, bb_output.Capacity(), bDbg)) goto errLabel;

            //
            byte* p = pBbOutput;
            p++;
            //
            int k;
            k = 0;
            int tmpiPaddingSize = *(int*)(p + k * sizeof(int));
            k++;
            int nPktsDeced = *(int*)(p + k * sizeof(int));
            k++;
            int iFourcc_dec = *(int*)(p + k * sizeof(int)); ;
            k++;
            int iW = *(int*)(p + k * sizeof(int));
            k++;
            int iH = *(int*)(p + k * sizeof(int)); ;
            k++;
            int iDecBufSize = *(int*)(p + k * sizeof(int)); ;
            k++;
            int bBufTooSmall = *(int*)(p + k * sizeof(int)); ;
            k++;

            //
            if (bDbg)
            {
                str = string.Format("qdcDecV: bBufTooSmall {0}, nPktDeced {1}", bBufTooSmall, nPktsDeced);
                qyFuncs.traceLog(str);
            }

            //
            if (0 != bBufTooSmall)
            {
                switch (iFourcc_dec)
                {
                    case Consts.CONST_fourcc_I420:
                        BITMAPINFOHEADER bih;
                        qyFuncs.makeBmpInfoHeader_i420(12, iW, iH, &bih);
                        int bufSize_output = bih.biSizeImage + pQdcObjInfo.bHeadLen;
                        if (bufSize_output > bb_output.Capacity())
                        {
                            pQdcObjInfo.bb_output = null;
                            //
                            pQdcObjInfo.bb_output = ByteBuffer.AllocateDirect(bufSize_output);
                            if (pQdcObjInfo.bb_output == null) goto errLabel;
                            qyFuncs.traceLog("qdcDecVideo_android: bb realloc");
                        }
                        break;
                    case Consts.CONST_fourcc_YV12:
                    default:
                        qyFuncs.traceLog("qdcDecVideo_android failed, iFourcc_dec unsupported");
                        goto errLabel;
                }

            }

            //
            pQdcObjInfo.nPktsDeced = nPktsDeced;
            pQdcObjInfo.iDecBufSize = iDecBufSize;



        errLabel:

            return 0;
        }


        //
        public static unsafe int qdcDecompressVideoRun_mediaCodec(ref QOI_common pQdcObjInfo)
        {
            int iErr = -1;
            int i;

            bool bDbg = false;
            string str;

            //
#if DEBUG
            //bDbg = true;
#endif


            //
            CQdcObj_mediaCodec pObj = (CQdcObj_mediaCodec)pQdcObjInfo.var.pObj;
            decObj_mediaCodec obj = (decObj_mediaCodec)pObj.obj_qdcUnit;

            str = string.Format("qdcDecVRun_mediaCodec enters");
            qyFuncs.showInfo_open(0, null, str);


            for (i=0; ; i++)
            {
                if (obj.m_bEnd)
                {
                    break;
                }
                //
                qyFuncs.myWaitOne((System.Threading.EventWaitHandle)pQdcObjInfo.hEvent_notifyToQuit, 1000);
                //qyFuncs.mySleep(1000);

                //
                if (bDbg)
                {
                    str = string.Format("qdcDecompressVideoRun_mediaCodec: {0}", i);
                    qyFuncs.showInfo_open(0,null,str);
                }

                //
                continue;
            }


            iErr = 0;

        errLabel:


            str = string.Format("qdcDecVRun_mediaCodec leaves");
            uint nStep = 1;
            qyFuncs.showInfo_open(0, &nStep,null, str);
                       

            return iErr;
        }


        ////////////
        ///
        public static unsafe int qdcInitCompressVideo_mediaCodec(ref VIDEO_COMPRESSOR_CFG pVideoCompressorCfg, ref QY_VIDEO_HEADER pVh_decompress, ref QY_VIDEO_HEADER pVh_compress, ref QOI_common pQdcObjInfo)
        {
            int iErr = -1;
            int iFourcc;
            bool bDbg = false;

            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();


            //
            if (pQdcObjInfo.var.pObj != null) return -1;

            //
            pQdcObjInfo.cfg.v = pVideoCompressorCfg.common;

            //
            pQdcObjInfo.var.pObj = new CQdcObj_mediaCodec();
            if (pQdcObjInfo.var.pObj == null) goto errLabel;
            CQdcObj_mediaCodec pObj = (CQdcObj_mediaCodec)pQdcObjInfo.var.pObj;


            //
#if false
            int index_taskInfo = qyFuncs.getQmcTaskInfoIndexBySth(null, pProcInfo, pVideoCompressorCfg.iTaskId);
            QMC_TASK_INFO pTaskInfo = qyFuncs.getQmcTaskInfoByIndex(null, pProcInfo, index_taskInfo, "");
            if (null == pTaskInfo) goto errLabel;
            QMC_taskData_conf pTc = (QMC_taskData_conf)pTaskInfo.pTaskData;
            if (pTc.uiType != Consts.CONST_taskDataType_conf) goto errLabel;
            if (null == pTc.share_eglContext)
            {
                qyFuncs.showInfo_open(0, null, "qdcInitDecV_mediaCodec failed, share_eglContext is null");
                goto errLabel;
            }
#endif
            
            //
            if (pProcInfo.cfg.mSpecialDbg.bNo_encV)
            {
                iErr = 0;  goto errLabel;
            }


            //
            //
            string pName = string.Format("qdcEnccEvt{0}", qyFuncs.getuiNextTranNo(null, 0, null));
            pQdcObjInfo.hEvent_notifyToQuit = new System.Threading.EventWaitHandle(false, System.Threading.EventResetMode.AutoReset, new string(pName));


            //
            pObj.obj_qdcUnit = new encObj_mediaCodec();
            encObj_mediaCodec obj = (encObj_mediaCodec)pObj.obj_qdcUnit;

            //
            obj.m_sharedEglContext = (Android.Opengl.EGLContext)pVideoCompressorCfg.shared_eglContext;
            //
            obj.m_qoi = pQdcObjInfo;

            //
            obj.m_index_sharedObj = pVideoCompressorCfg.index_sharedObj;

            //
            //obj.testEncodeVideoToMp4();

            //
            obj.mWidth = pVh_decompress.bih.biWidth;
            obj.mHeight = pVh_decompress.bih.biHeight;
            obj.mBitRate = 1000000;


                        //
            obj.m_wrapper = new encObj_mediaCodec.encObj_mediaCodec_Wrapper(obj);
            obj.m_th = new Thread(obj.m_wrapper, "codec test");
            obj.m_th.Start();



            iErr = 0;
        errLabel:

            if (iErr != 0)
            {
                qdcExitCompressVideo_mediaCodec(ref pQdcObjInfo);
            }

            return iErr;
        }
        public static int qdcExitCompressVideo_mediaCodec(ref QOI_common pQdcObjInfo)
        {
            bool bDbg = true;

#if DEBUG
            if (bDbg)
            {
                qyFuncs.traceLog("qdcExitCompressVideo_android enters");
            }
#endif
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();


            if (null == pQdcObjInfo.var.pObj) return 0;
            CQdcObj_mediaCodec pObj = (CQdcObj_mediaCodec)pQdcObjInfo.var.pObj;

            encObj_mediaCodec obj = (encObj_mediaCodec)pObj.obj_qdcUnit;

            if (obj != null)
            {
                //
                obj.m_bQuit = true;
                //
                if (null != obj.m_th)
                {
                    obj.m_th.Join();

                }



                //
                obj = null;
            }

            //
            if (pQdcObjInfo.hEvent_notifyToQuit != null)
            {
                System.Threading.EventWaitHandle hEvt = (System.Threading.EventWaitHandle)pQdcObjInfo.hEvent_notifyToQuit;
                hEvt.Close();
                pQdcObjInfo.hEvent_notifyToQuit = null;
            }


            //
            pQdcObjInfo.bb_output = null;
            pQdcObjInfo.bb_input = null;


            //
            pQdcObjInfo.var.pObj = null;


#if DEBUG
            if (bDbg)
            {
                qyFuncs.traceLog("qdcExitCompressVideo_android leaves");
            }
#endif

            return 0;

        }

        public static unsafe int qdcGetSpsPps_mediaCodec(ref QOI_common pQdcObjInfo, IntPtr spsBuf, ref uint puiSpsSize, IntPtr ppsBuf, ref uint puiPpsSize, IntPtr vps, ref uint puiVpsSize)
        {
            int iErr = -1;
            int k;
            bool bDbg = false;

            //
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            //
            if (pProcInfo.cfg.mSpecialDbg.bNo_encV)
            {
                return 0;
            }


            //
            CQdcObj_mediaCodec pObj = (CQdcObj_mediaCodec)pQdcObjInfo.var.pObj;
            encObj_mediaCodec obj = (encObj_mediaCodec)pObj.obj_qdcUnit;




            //
#if true
            //
            int i;
            for  (i=0;i<10 ;i++ )
            {
                qyFuncs.myWaitOne((System.Threading.EventWaitHandle)pQdcObjInfo.hEvent_notifyToQuit, 1000);
                if (obj.m_bGot_spspps) break;
                continue;
            }
            if (!obj.m_bGot_spspps) goto errLabel;

            //
            uint uiSpsSize = puiSpsSize;
            uint uiPpsSize = puiPpsSize;
            uint uiVpsSize = puiVpsSize;

            fixed (byte* spspps = obj.m_tmpBuf_spspps.buf) {
                if (0 != qyFuncs.parseSpsPps(pQdcObjInfo.cfg.v.head.iFourcc, spspps, obj.m_len_spspps, (byte*)spsBuf, &uiSpsSize, (byte*)ppsBuf, &uiPpsSize, (byte*)vps, &uiVpsSize))
                {
                    goto errLabel;
                }
            }
            puiSpsSize = uiSpsSize;
            puiPpsSize = uiPpsSize;
            puiVpsSize = uiVpsSize;
#endif

            //
            iErr = 0;
        errLabel:

            return iErr;

        }



        public static unsafe int qdcCompressVideoRun_mediaCodec(ref QOI_common pQdcObjInfo)
        {
            int iErr = -1;

            bool bDbg = false;
            string str;
            

            //int[] lens = new int[3];
            byte* p;
            int k;

            //
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            if (pProcInfo.cfg.mSpecialDbg.bNo_encV)
            {
                return 0;
            }

            //
            CQdcObj_mediaCodec pObj = (CQdcObj_mediaCodec)pQdcObjInfo.var.pObj;
            int i;

            encObj_mediaCodec obj = (encObj_mediaCodec)pObj.obj_qdcUnit;


            str = string.Format("qdcEncVRun_mediaCodec enters");
            qyFuncs.showInfo_open(0, null, str);


            for (i = 0; ; i++)
            {
                if (obj.m_bEnd)
                {
                    str = string.Format("qdcEncVRun_mediaCodec: obj.m_bEnd is true, quit now");
                    qyFuncs.showInfo_open(0, null, str);
                    //
                    break;
                }
                //
                qyFuncs.myWaitOne((System.Threading.EventWaitHandle)pQdcObjInfo.hEvent_notifyToQuit, 1000);
                //qyFuncs.mySleep(1000);

                //
                if (bDbg)
                {
                    str = string.Format("qdcCompressVideoRun_mediaCodec: {0}", i);
                    qyFuncs.showInfo_open(0, null, str);
                }

                //
                continue;
            }


            iErr = 0;

        errLabel:


            str = string.Format("qdcEncVRun_mediaCodec leaves");
            uint nStep = 1;
            qyFuncs.showInfo_open(0, &nStep, null, str);


            return iErr;
        }


        ///////////////////////
        ///
        public static unsafe int qdcInitDecompressAudio_mediaCodec(ref AUDIO_COMPRESSOR_CFG pAudioCompressorCfg, ref QY_AUDIO_HEADER pAh_compress, ref QY_AUDIO_HEADER pAh_decompress, ref QOI_common pQdcObjInfo)
        {
            int iErr = -1;
            bool bDbg = true;

            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            //
            if (pQdcObjInfo.var.pObj != null) return -1;

            //
            //
            pQdcObjInfo.cfg.a = pAudioCompressorCfg.common;


            //
            pQdcObjInfo.var.pObj = new CQdcObj_mediaCodec();
            if (pQdcObjInfo.var.pObj == null) goto errLabel;
            CQdcObj_mediaCodec pObj = (CQdcObj_mediaCodec)pQdcObjInfo.var.pObj;

            //
            //
            pQdcObjInfo.var.ucbTransformFuncsOk = true;


            //
            pObj.bDec = true;

            //
            //iFourcc = pAudioCompressorCfg.common.head.iFourcc;

//

#if true
            //
            string pName = string.Format("qdcDecAEvt{0}", qyFuncs.getuiNextTranNo(null, 0, null));
            pQdcObjInfo.hEvent_notifyToQuit = new System.Threading.EventWaitHandle(false, System.Threading.EventResetMode.AutoReset, new string(pName));

            //
#if false
            if (pQdcObjInfo.cfg.v.usPktResType_suggested != Consts.CONST_pktResType_sharedTex)
            {
                qyFuncs.showInfo_open(0, null, "qdcInitDecompressVideo_mediaCodec failed, cfg.usPktResType err");
                goto errLabel;
            }
            pQdcObjInfo.var.usPktResType_dec = Consts.CONST_pktResType_sharedTex;
#endif
            //
            pObj.obj_qdcUnit = new decObj_a_mediaCodec();
            decObj_a_mediaCodec obj = (decObj_a_mediaCodec)pObj.obj_qdcUnit;

            //
            //
            obj.m_qoi = pQdcObjInfo;

            //

            //
#if DEBUG
            //obj.m_bTest = true;


            //
            //obj.dec_init();
#endif

            //
            obj.m_wrapper = new decObj_a_mediaCodec.decObj_a_mediaCodec_Wrapper(obj);
            obj.m_th = new Thread(obj.m_wrapper, "codec test");
            obj.m_th.Start();

#endif

            iErr = 0;
        errLabel:

            if (iErr != 0)
            {
                qdcExitDecompressAudio_mediaCodec(ref pQdcObjInfo);
            }

            return iErr;

        }

        public static int qdcExitDecompressAudio_mediaCodec(ref QOI_common pQdcObjInfo)
        {
            bool bDbg = true;

            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();


            if (null == pQdcObjInfo.var.pObj) return 0;
            CQdcObj_mediaCodec pObj = (CQdcObj_mediaCodec)pQdcObjInfo.var.pObj;

#if true
            //TmpFfmpeg.DecV_exit(pObj.m_index_qdcUnit, bDbg);
            decObj_a_mediaCodec obj = (decObj_a_mediaCodec)pObj.obj_qdcUnit;
            if (null != obj)
            {
                if (null != obj.m_th)
                {
                    obj.m_th.Join();

                }

                //
                //obj.dec_exit();
            }

            //
            pObj.obj_qdcUnit = null;

            //
            if (pQdcObjInfo.hEvent_notifyToQuit != null)
            {
                System.Threading.EventWaitHandle hEvt = (System.Threading.EventWaitHandle)pQdcObjInfo.hEvent_notifyToQuit;
                hEvt.Close();
                pQdcObjInfo.hEvent_notifyToQuit = null;
            }
#endif


            //
            pQdcObjInfo.bb_input = null;
            pQdcObjInfo.bb_output = null;


            //
            pQdcObjInfo.var.pObj = null;


            return 0;

        }

        public static unsafe int qdcDecompressAudio_mediaCodec(ref QOI_common pQdcObjInfo, ref QY_AUDIO_HEADER pAh_compress, IntPtr pInput, uint uiInputLen, int iSampleTimeInMs, uint ui_rtTimeLen)
        {
            int iErr = -1;
            int iPaddingSize = 128;

            bool bDbg = false;
#if DEBUG
            string str;
#endif
            qyFuncs.traceLog("not supported");
  
            //iErr = 0;

        errLabel:

            return iErr;
        }


        //
        //  2016/12/05
        public static unsafe int qdcDecompressAudioRun_mediaCodec(ref QOI_common pQdcObjInfo)
        {
            int iErr = -1;
            int i;

            bool bDbg = false;
            string str;

            //
#if DEBUG
            //bDbg = true;
#endif


            //
            CQdcObj_mediaCodec pObj = (CQdcObj_mediaCodec)pQdcObjInfo.var.pObj;
#if true
            decObj_a_mediaCodec obj = (decObj_a_mediaCodec)pObj.obj_qdcUnit;

            str = string.Format("qdcDecARun_mediaCodec enters");
            qyFuncs.showInfo_open(0, null, str);


            for (i = 0; ; i++)
            {
                if (obj.m_bEnd)
                {
                    break;
                }
                //
                qyFuncs.myWaitOne((System.Threading.EventWaitHandle)pQdcObjInfo.hEvent_notifyToQuit, 1000);
                //qyFuncs.mySleep(1000);

                //
                if (bDbg)
                {
                    str = string.Format("qdcDecompressAudioRun_mediaCodec: {0}", i);
                    qyFuncs.showInfo_open(0, null, str);
                }

                //
                continue;
            }
#endif

            iErr = 0;

        errLabel:


            str = string.Format("qdcDecARun_mediaCodec leaves");
            uint nStep = 1;
            qyFuncs.showInfo_open(0, &nStep, null, str);


            return iErr;


        }



    }



}