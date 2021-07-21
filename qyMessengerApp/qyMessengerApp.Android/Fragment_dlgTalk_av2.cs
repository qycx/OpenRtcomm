
using Android;
using Android.App;
using Android.Content;
using Android.Content.PM;
using Android.Hardware.Camera2;
using Android.Media;
using Android.OS;
using Android.Runtime;
using Android.Util;
using Android.Views;
using Android.Widget;
using AndroidX.Legacy.App;
using Java.Lang;
using Java.Util;
using Java.Util.Concurrent;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading;
using Android.Hardware.Camera2.Params;
using Android.Graphics;
//using Android.Support.V13.App;

//
using qy;
using qy.Droid;

//
using Com.Qycx.Gleslibrary;
using Android.Opengl;
using Android.Animation;
using Android.Support.Design.Widget;

//
namespace qyMessengerApp.Droid
{
    public class Fragment_dlgTalk_av2 : Fragment
    {
        //private static String TAG = "Camera2VideoFragment";
        public static int REQUEST_VIDEO_PERMISSIONS = 1;
        public static string FRAGMENT_DIALOG = "dialog";

        //
        public static string[] VIDEO_PERMISSIONS = {
            Manifest.Permission.Camera,
            Manifest.Permission.RecordAudio,
        };

        //
        public Activity_dlgTalk_av mOwner_wnd;

        //
        public MainHandler mMainHandler;


        //
        public MyTextureView mTextureView;
        private dlgTalk_av_Renderer mRenderer;


        //
#if DEBUG
#if false
        public MyTextureView mTv_test;
        public TMP_stListener m_stListener_test;
        public SurfaceTexture m_st_test;
#endif
#endif

        //
        FrameLayout m_frameLayout_bottomMenu;
        Button m_btn_request;
        TextView m_tv_ioStatus;
        Button m_btn_more;
        Button m_btn_av;
        //
        //public bool mIsShutter;

        //
        BottomSheetDialog m_bsd_more;


        //
#if DEBUG
        public bool m_bTestDec;

        //
        public MyTextureView mTextureView1;

        //
        public struct TestDec            
        {
            public ExtractMp3FramesTest extractMp3FramesTest;
            //
            public decObj_a_mediaCodec decObj_a_mediaCodec;
        };

        public TestDec m_testDec;


        //
        public struct TestEnc {
            public CameraToMpegTest cameraToMpegTest;
            //
            public EncodeAndMuxTest encodeAndMuxTest;
            //
            public encObj_mediaCodec encObj_mediaCodec;
        };

        //
        public TestEnc m_testEnc;

#endif

        //
        camera_RenderThread mCameraRenderThread;
        //
        public int mSensorOrientation;

        //
        public int m_st_iW;
        public int m_st_iH;

        //
        public int m_o_iW;
        public int m_o_iH;


        // These values are passed to us by the camera/render thread, and displayed in the UI.
        // We could also just peek at the values in the RenderThread object, but we'd need to
        // synchronize access carefully.
#if true
        private int mCameraPreviewWidth_unused, mCameraPreviewHeight_unused;
        private float mCameraPreviewFps_unused;
        //
        private int mRectWidth, mRectHeight;
        private int mZoomWidth, mZoomHeight;
        private int mRotateDeg;
#endif

        //
        //public static int m_test_textureId;



        //
        public static volatile bool sReleaseInCallback = true;

        //
        public int showBottomMenu()
        {
            ViewStates state_bottomMenu;

            state_bottomMenu = ViewStates.Visible;
            if (this.m_frameLayout_bottomMenu.Visibility != state_bottomMenu)
            {
                this.m_frameLayout_bottomMenu.Visibility = state_bottomMenu;
            }

            return 0;
        }
        
        //
        public unsafe int gui_onTimer(object p0, object p1, object p2)
        {
            Activity_dlgTalk_av owner = (Activity_dlgTalk_av)this.Activity;
            if (owner == null) return -1;
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            //
#if DEBUG
            //int angle = ((WindowManager)owner.GetSystemService(Context.WindowService)).getDefaultDisplay().getRotation();
            //SurfaceOrientation surfaceOrientation = owner.WindowManager.DefaultDisplay.Rotation;
            //int angle = (int)surfaceOrientation;
            //if (surfaceOrientation==SurfaceOrientation.)

#endif


            //
            string str = string.Format("{0,6:0.0},{1,6:0.0}", pProcInfo.status.netStat.ins.uiInSpeedInKbps / 1000.0f, pProcInfo.status.netStat.ins.uiOutSpeedInKbps / 1000.0f);
            //str = string.Format("{0}", surfaceOrientation);
            //
            m_tv_ioStatus.Text = str;

            //
            uint tickCnt = qyFuncs.myGetTickCount(null);
            ViewStates state_bottomMenu;
            if ( tickCnt-owner.uiLastTickCnt_touch > 5000)
            {
                state_bottomMenu = ViewStates.Invisible;
                //
                if (this.m_frameLayout_bottomMenu.Visibility != state_bottomMenu)
                {
                    this.m_frameLayout_bottomMenu.Visibility = state_bottomMenu;
                }

                //
                mOwner_wnd.hideSystemUI();
            }


            //
            //qyFuncs.traceLog("fg_dlgTalk_av onTimer");

            return 0;
        }

        //
        public int waitTextureViewAvailable(object p0, object p1, object p2)
        {
            int iErr = -1;
            Activity_dlgTalk_av owner = (Activity_dlgTalk_av)this.Activity;
            Activity_dlgTalk hTalk = owner.mOwner_hTalk;

            string str;

            str=string.Format("fg_dlgTalk_av2, waitTextureViewAvailable called");
            qyFuncs.showInfo_open(0, null, str);

            //
            if (!mTextureView.IsAvailable)
            {
                qyFuncs.traceLog("fg_dlgTalk_av,gui_onTimer, textureView.isAvail is false");

                return 0;
            }
            //
            if (hTalk.m_var.m_share_eglContext == null)
            {
                qyFuncs.traceLog("fg_dlgTalk_av,gui_onTimer, talk.m_share_eglContext is null");
                return 0;
            }

            //
            owner.killTimer();
            qyFuncs.traceLog("fg_dlgTalk_av2, waitTextureViewAvailable, after killTimer");

            //
            if (!hasPermissionsGranted(VIDEO_PERMISSIONS))
            {
                requestVideoPermissions();
                goto errLabel;
            }

            //
            if (hTalk.m_var.av.taskInfo.bTaskExists)
            {
                if (!hTalk.m_var.m_bNeedResumeTaskAv)
                {
                    owner.pauseTaskAv("waitTexViewAvail");
                }

                if (hTalk.m_var.m_bNeedResumeTaskAv)
                {
                    //
                    owner.resumeTaskAv("waitTexViewAvail");
                    iErr = 0; goto errLabel;
                }

                //
                iErr = 0; goto errLabel;
            }


            //
            int iTaskId = 0;
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
            QMC_TASK_INFO pTaskInfo = (QMC_TASK_INFO)qyFuncs.getQmcTaskInfoByIndex(null,pProcInfo, mOwner_wnd.m_index_taskInfo,"");
            if (pTaskInfo != null)
            {
                iTaskId = pTaskInfo.var.iTaskId;
            }



            //
            doTask_av(mOwner_wnd.m_iCmd,iTaskId);


            //
            iErr = 0;

        errLabel:

            //
            return iErr;
        }

        //
 

        public unsafe int doTask_av(int iCmd,int iTaskId)
        {
            int iErr = -1;
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
            MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;

            bool bDbg = false;
            string str;

            //
            bool b3D = false;
            //  2017/07/17
            bool ucbAvConsole = false;
            Activity_dlgTalk_av owner = (Activity_dlgTalk_av)this.Activity;

            //
#if DEBUG
            if (this.m_bTestDec){
                //
                //
                bool bTestDec = false;
                //bTestDec = true;

                if (bTestDec)
                {
                    if (false)
                    {
                        this.m_testDec.extractMp3FramesTest = new ExtractMp3FramesTest();

                        this.m_testDec.extractMp3FramesTest.testExtractMpegFrames(this.mOwner_wnd);
                    }
                    else
                    {
                        this.m_testDec.decObj_a_mediaCodec = new decObj_a_mediaCodec();
                        this.m_testDec.decObj_a_mediaCodec.m_bTest = true;
                        this.m_testDec.decObj_a_mediaCodec.testExtractMpegFrames(this.mOwner_wnd);
                    }

                    return 0;
                }        
            }

            //
            bool bTestEnc = false;
            //bTestEnc=true;
            //
            if (bTestEnc)
            {
                if (false)
                {
                    this.m_testEnc.cameraToMpegTest = new CameraToMpegTest();
                    //
                    this.m_testEnc.cameraToMpegTest.testEncodeCameraToMp4();
                }
                else 
                {
#if false
                    this.m_testEnc.encodeAndMuxTest = new EncodeAndMuxTest();
                    //
                    this.m_testEnc.encodeAndMuxTest.testEncodeVideoToMp4();
#else

                    //
                    this.m_testEnc.encObj_mediaCodec = new encObj_mediaCodec();
                    this.m_testEnc.encObj_mediaCodec.testEncodeVideoToMp4();
#endif

                }

                return 0;
            }

#endif
                    //
                    if (!mTextureView.IsAvailable)
            {
                str=string.Format("fg_dlgTalk_av.doTask_av failed, textureView.isAvail is false");
                qyFuncs.showInfo_open(0, null, str);

                goto errLabel;
            }


            //
            switch (iCmd) {
                case tmpResource.IDC_BUTTON_av:
                    {
                        qyFuncs_Droid.doCmd_startAvCall(null, mOwner_wnd.mOwner_hTalk, 0, false, false, null);
                    }
                    break;
                case tmpResource.IDC_BUTTON_av_accept:
                    {
                        int index_taskInfo = qyFuncs.getQmcTaskInfoIndexBySth(null, pProcInfo, iTaskId);
                        QMC_TASK_INFO pTaskInfo = pProcInfo.getQmcTaskInfoByIndex(mainActivity.var_common.ctxCaller,index_taskInfo,"doTask_av");
                        if (pTaskInfo == null) goto errLabel;
                        
                        PARAM_dlgTalk_procTask param=new PARAM_dlgTalk_procTask();
                        //memset(&param, 0, sizeof(param));
                        param.bManualCmd = true;        //  2017/02/12
                                                        //pFuncs->pf_dlgTalk_procTask1(  hDlgTalk,  pDlgTalkVar->guiData.av.iTaskId,  CONST_imOp_dual_permit,  NULL,  &param  );  
                        qyFuncs_Droid.dlgTalk_procTask1(mOwner_wnd.mOwner_hTalk, pTaskInfo.var.iTaskId, Consts.CONST_imOp_dual_permit, null, ref param);
                        
                        qyFuncs.traceLog("not finished");

                    }
                    break;
                default:
                        
                qyFuncs.traceLog("not finished, unknown iCmd");
                    break;

            }

            
            //
            iErr = 0;
            errLabel:

            return iErr;
        }


        //
        public int updateCtrls()
        {
            Activity_dlgTalk dlgTalk=mOwner_wnd.mOwner_hTalk;

            //this.m_btn_request
            bool bState_canSpeak = qyFuncs_Droid.dlgTalk_canSpeak(dlgTalk);


            m_btn_request.Text = (bState_canSpeak) ? "stop" : "speak";

            return 0;
        }




        //
        public static unsafe int initVideoCapDev( object hTalk, int iWndContentType, string displayName_selected, ref BITMAPINFOHEADER pBih_suggested, CAP_procInfo_bmpCommon pCapBmp )

        {
            int iErr = -1;
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            string str;

            //
#if DEBUG
            if (pProcInfo.cfg.mSpecialDbg.bNo_videoCap)
            {
                qyFuncs.showInfo_open(0, null, "For test: fg_dlgTalk_av2.initVideoCapDev return -1");
                return -1;
            }
#endif

            //
            if (iWndContentType != Consts.CONST_qyWndContentType_talker) return -1;
            Activity_dlgTalk dlgTalk = (Activity_dlgTalk)hTalk;
            DLG_TALK_var m_var = dlgTalk.m_var;
            if (!GuiShare.pf_IsWindow(dlgTalk.m_var.m_hTool_dlgTalk_av)) return -1;
            Activity_dlgTalk_av dlgTalk_av = (Activity_dlgTalk_av)dlgTalk.m_var.m_hTool_dlgTalk_av;
            if ( dlgTalk_av.m_fg_dlgTalk_av2==null ) return -1;
            Fragment_dlgTalk_av2 fg = dlgTalk_av.m_fg_dlgTalk_av2;


            if (!fg.mTextureView.IsAvailable) return -1;

            //
            int w, h;
            //w = fg.mTextureView.Width;
            //h = fg.mTextureView.Height;
            w = pBih_suggested.biWidth;
            h = pBih_suggested.biHeight;

            //
#if false
            fg.startBackgroundThread();       
            fg.openCamera(w, h);
#endif
            
            //
            if (null == dlgTalk.m_var.m_share_eglContext) goto errLabel;

            //
            SurfaceOrientation surfaceOrientation = dlgTalk_av.WindowManager.DefaultDisplay.Rotation;

            //
            bool bFront = true;
            if (m_var.av.taskInfo.bTaskExists) bFront = !m_var.av.taskInfo.bUse_backCamera;
            //
#if DEBUG
//
#if false
            bFront = false;
            qyFuncs.showInfo_open(0,null,"for test: set bFront false");
#endif
//
#endif
            //
            fg.mCameraRenderThread = new camera_RenderThread(fg.mMainHandler,(EGLContext)dlgTalk.m_var.m_share_eglContext,pCapBmp.iIndex_sharedObj, bFront, surfaceOrientation);
            fg.mCameraRenderThread.Start();
            //
            fg.mCameraRenderThread.waitUntilReady();
            //
            fg.mSensorOrientation = fg.mCameraRenderThread.myCamera.mSensorOrientation;
            //
            //pCapBmp.mSensorOrientation = fg.mSensorOrientation;



            //fg.me_tex 
            //
            SurfaceTexture st = null;// fg.m_st_test;
            //st=new SurfaceTexture(CTalkDraw.me_texId);
            st = CTalkDraw.me_st;

            //
            fg.m_st_iW = fg.mCameraRenderThread.mCameraPreviewWidth;
            fg.m_st_iH = fg.mCameraRenderThread.mCameraPreviewHeight;

            //
#if false
            switch (fg.mSensorOrientation)
            {
                case 90:
                case 270:
                    fg.m_o_iW = fg.mCameraRenderThread.mCameraPreviewHeight;
                    fg.m_o_iH = fg.mCameraRenderThread.mCameraPreviewWidth;
                    break;
                default:
                    fg.m_o_iW = fg.mCameraRenderThread.mCameraPreviewWidth;
                    fg.m_o_iH = fg.mCameraRenderThread.mCameraPreviewHeight;
                    break;
            }
#endif
            //
            int angle_z = 0;
            qyFuncs_Droid.get_tex_o_info(fg.mSensorOrientation,  surfaceOrientation, fg.mCameraRenderThread.mCameraPreviewWidth, fg.mCameraRenderThread.mCameraPreviewHeight, ref angle_z, ref fg.m_o_iW, ref fg.m_o_iH);

            //
#if DEBUG

#endif

            //
            st.SetDefaultBufferSize(fg.m_st_iW, fg.m_st_iH);

            //
            fg.mCameraRenderThread.mHandler.sendSurfaceAvailable(st, true);



            iErr = 0;
        
        errLabel:

            return iErr;
        }

        public static unsafe int exitVideoCapDev(object hTalk, int iWndContentType)
        {
            int iErr = -1;

            if (iWndContentType != Consts.CONST_qyWndContentType_talker) return -1;
            Activity_dlgTalk dlgTalk = (Activity_dlgTalk)hTalk;
            if (null==dlgTalk.m_var.m_hTool_dlgTalk_av) return -1;
            Activity_dlgTalk_av dlgTalk_av = (Activity_dlgTalk_av)dlgTalk.m_var.m_hTool_dlgTalk_av;
            if (dlgTalk_av.m_fg_dlgTalk_av2 == null) return -1;
            Fragment_dlgTalk_av2 fg = dlgTalk_av.m_fg_dlgTalk_av2;


#if false
            fg.closeCamera();
            fg.stopBackgroundThread();
#endif
            //
            if (fg.mCameraRenderThread != null)
            {
                camera_RenderThread.camera_RenderHandler rh = fg.mCameraRenderThread.getHandler();
                if (rh != null)
                {
                    rh.sendShutdown();
                }
                try
                {
                    fg.mCameraRenderThread.Join();
                }
                catch (InterruptedException ie)
                {

                }
                fg.mCameraRenderThread = null;
            }




            iErr = 0;
        errLabel:
            return iErr;
        }

        public static unsafe bool bGetCapturePara(object hTalk, int iWndContentType, ref QY_VIDEO_HEADER pVh_org)
        {
            bool bRet = false;

            if (iWndContentType != Consts.CONST_qyWndContentType_talker) return false;
            Activity_dlgTalk dlgTalk = (Activity_dlgTalk)hTalk;
            if (!GuiShare.pf_IsWindow(dlgTalk.m_var.m_hTool_dlgTalk_av)) return false;
            Activity_dlgTalk_av dlgTalk_av = (Activity_dlgTalk_av)dlgTalk.m_var.m_hTool_dlgTalk_av;
            if (dlgTalk_av.m_fg_dlgTalk_av2 == null) return false;
            Fragment_dlgTalk_av2 fg = dlgTalk_av.m_fg_dlgTalk_av2;
#if false
            if (fg.mImageReader == null) return false;
#endif

            //
            BITMAPINFOHEADER bih_org;
            qyFuncs.mymemset((IntPtr)(byte*)&bih_org, 0, sizeof(BITMAPINFOHEADER));
            /*
            switch (fg.mSensorOrientation)
            {
                case 90:
                case 270:
                    bih_org.biWidth = fg.mImageReader.Height;
                    bih_org.biHeight = fg.mImageReader.Width;
                    break;
                default:
                    bih_org.biWidth = fg.mImageReader.Width;
                    bih_org.biHeight = fg.mImageReader.Height;
                    break;
            }
            */
#if true
            if (fg.mCameraRenderThread == null) goto errLabel;

            bih_org.biWidth = fg.m_o_iW;
            bih_org.biHeight = fg.m_o_iH;
            //           
            bih_org.biCompression = Consts.CONST_fourcc_I420;
#endif
            pVh_org.bih = bih_org;


            //
            bRet = true;
            errLabel:

            return bRet;
        }

        public static unsafe int startCapture(object hTalk,int iWndContentType)
        {
            return 0;
        }
             
        public static unsafe int stopCapture(object hTalk,int iWndContentType)
        {
            return 0;
        }



        //
        public static Fragment_dlgTalk_av2 NewInstance()
        {
            return new Fragment_dlgTalk_av2();
        }

        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            //
            mOwner_wnd = (Activity_dlgTalk_av)this.Activity;

            // Create your fragment here
#if false
            mOnImageAvailableListener = new ImageAvailableListener(this);
            //mSurfaceTextureListener = new dlgTalk_av_SurfaceTextureListener(this);
            mStateCallback = new MyCameraStateCallback(this);
#endif

            //
#if DEBUG
            this.m_bTestDec = true;
            qyFuncs.showInfo_open(0, null, "For test: m_bTestDesc set to true");

            //
            if  (m_bTestDec)
            {
#if false
                m_testDec.mTimeAnimator = new TimeAnimator();



                //m_testDec.mCodecWrapper = new MediaCodecWrapper();
                m_testDec.mExtractor = new MediaExtractor();
#endif
    
            }
#endif

            }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            // Use this to return your custom view for this Fragment
            // return inflater.Inflate(Resource.Layout.YourFragment, container, false);

            //return base.OnCreateView(inflater, container, savedInstanceState);
            View view = null;

            view = inflater.Inflate(Resource.Layout.layout_fg_dlgTalk_av, container, false);

            //
            this.mMainHandler = new MainHandler(this);

            
            //
            mTextureView = (MyTextureView)view.FindViewById(Resource.Id.texture);
            //
            m_frameLayout_bottomMenu = (FrameLayout)view.FindViewById(Resource.Id.bottomMenu);
            //
            m_btn_request = (Button)view.FindViewById(Resource.Id.btn_request);
            m_tv_ioStatus = (TextView)view.FindViewById(Resource.Id.tv_ioStatus);
            m_btn_more = (Button)view.FindViewById(Resource.Id.btn_more);
            m_btn_av = (Button)view.FindViewById(Resource.Id.btn_av);

            //  
           mRenderer = new dlgTalk_av_Renderer(this,Consts.CONST_iFgType_dlgTalk_av2);
           mRenderer.init();
           mRenderer.Start();

           //
           mTextureView.SurfaceTextureListener = mRenderer;

            //
#if DEBUG
#if false
            mTv_test = (MyTextureView)view.FindViewById(Resource.Id.texture_test);
            //
            m_stListener_test = new TMP_stListener(this);
            mTv_test.SurfaceTextureListener = m_stListener_test;
#endif
            //
#endif


            //
            m_btn_request.Click += M_btn_request_Click;
            m_btn_av.Click += M_btn_av_Click;
            m_btn_more.Click += M_btn_more_Click;

            //
            m_btn_av.Text = "Cancel";


            //
            

            //
            return view;
        }

        private void M_btn_more_Click(object sender, EventArgs e)
        {
            //throw new NotImplementedException();

            View view = this.LayoutInflater.Inflate(Resource.Layout.layout_fg_dlgTalk_av_tool_more, null);
#if true
            this.m_bsd_more = new BottomSheetDialog(this.Activity);
            m_bsd_more.SetContentView(view);
            //
            //
            Button btnChangeCamera = (Button)view.FindViewById(Resource.Id.changeCamera);
            btnChangeCamera.Click += BtnChangeCamera_Click;
            Button btnLocalVideo = (Button)view.FindViewById(Resource.Id.localVideo);
            btnLocalVideo.Click += BtnLocalVideo_Click; ;
            //
            m_bsd_more.Show();
#endif
            return;


        }

        private void BtnLocalVideo_Click(object sender, EventArgs e)
        {
            //throw new NotImplementedException();
            qyFuncs.traceLog("changeCamera clicked");

            m_bsd_more.Dismiss();
            m_bsd_more = null;

            //
            mOwner_wnd.changeLocalVideo();

            return;
        }

        private void BtnChangeCamera_Click(object sender, EventArgs e)
        {
            //throw new NotImplementedException();
            qyFuncs.traceLog("changeCamera clicked");

            m_bsd_more.Dismiss();
            m_bsd_more = null;
            //
            //
            mOwner_wnd.changeCamera();

            return;
        }

        private void M_btn_request_Click(object sender, EventArgs e)
        {
            //throw new NotImplementedException();
            //mIsShutter = true;

            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            //
            Activity_dlgTalk_av owner = mOwner_wnd;
            Activity_dlgTalk dlgTalk = owner.mOwner_hTalk;
            DLG_TALK_var m_var = dlgTalk.m_var;

            //
            if (!m_var.av.taskInfo.bTaskExists) goto errLabel;

            //
            qyFuncs.setCurSharedObjUsr_localAv(pProcInfo, m_var.av.iIndex_sharedObj_localAv, dlgTalk);


            //
            bool canSpeak = qyFuncs_Droid.dlgTalk_canSpeak(dlgTalk);

            //
            qyFuncs_Droid.dlgTalk_requestToSpeak(dlgTalk, !canSpeak);

            bool bState_canSpeak = !canSpeak;

            //
            m_btn_request.Text = (bState_canSpeak) ? "stop": "speak";



        errLabel:
            return;
        }

        private void M_btn_av_Click(object sender, EventArgs e)
        {
            //throw new NotImplementedException();
            //mIsShutter = true;
            //
            Activity_dlgTalk_av owner = this.mOwner_wnd;
            owner.OnBackPressed();
        }




        public override void OnResume()
        {
            base.OnResume();

            if ( mTextureView.IsAvailable)
            {
                int ii = 0;
            }
            else
            {
                int jj = 0;
            }

            /*
            startBackgroundThread();
            if (mTextureView.IsAvailable)
            {
                openCamera(mTextureView.Width, mTextureView.Height);
            }
            else
            {
                mTextureView.SurfaceTextureListener = mSurfaceTextureListener;

            }
            */
        }

        public override void OnPause()
        {
            /*
            closeCamera();
            stopBackgroundThread();
            */

            
            
            //
            base.OnPause();           

        }

        public override void OnDestroyView()
        {
            //
            doClean("fg.OnDestroyView");
            
            //
            base.OnDestroyView();
        }


        public int doClean(string hint )
        {
            string str;

            if (hint == null) hint = "";

            //
            str=string.Format("fg_dlgTalk_av2.doClean enters {0}",hint);
            qyFuncs.showInfo_open(0, null, str);

            //
            Activity_dlgTalk_av owner = (Activity_dlgTalk_av)this.Activity;
            if (owner != null)
            {
                //
                owner.killTimer();

                //
                if (!owner.mOwner_hTalk.m_var.m_bNeedResumeTaskAv)
                {
                    qyFuncs_Droid.dlgTalk_closeTaskAv(owner.mOwner_hTalk, owner.mOwner_hTalk.m_var, "fg_dlgTalk_av.doClean_ifActivityIsFinishing");
                }
            }
            //
            if (mRenderer != null)
            {
                mRenderer.halt();
                //Java.Lang.Thread h = mRenderer;
                //qyFuncs_Droid.waitForThread1(ref h, 10000);
                mRenderer.Join();
                mRenderer.exit();
                mRenderer = null;// (dlgTalk_av_Renderer)h;
            }

            //
#if DEBUG
            if (owner == null)
            {
                int ii = 0;
            }
#endif

            //
            str=string.Format("fg_dlgTalk_av2.doClean leaves {0}",hint);
            qyFuncs.showInfo_open(0, null, str);

            return 0;
        }


        public int doClean_ifActivityIsFinishing()
        {
            return doClean("doClean_ifActivityIfFinishing");
        }


        public override void OnDestroy()
        {
            base.OnDestroy();

            //

            
        }




        public bool shouldShowRequestPermissionRationale(string[] permissions )
        {
            foreach (string permission in permissions) {
                if (FragmentCompat.ShouldShowRequestPermissionRationale(this,permission) )
                {
                    return true;
                }                    
            }

            return false;

        }

        public void requestVideoPermissions()
        {
            if (shouldShowRequestPermissionRationale(VIDEO_PERMISSIONS))
            {
                new ConfirmationDialog().Show(ChildFragmentManager, FRAGMENT_DIALOG);
            }
            else
            {
                FragmentCompat.RequestPermissions(this, new string[] { Manifest.Permission.Camera,Manifest.Permission.RecordAudio,},
                    REQUEST_VIDEO_PERMISSIONS);
            }
        }

        public override void OnRequestPermissionsResult(int requestCode, string[] permissions, [GeneratedEnum] Permission[] grantResults)
        {
            if (requestCode == REQUEST_VIDEO_PERMISSIONS)
            {
                if ( grantResults.Length==VIDEO_PERMISSIONS.Length)
                {
                    bool bOk = true;
                    foreach ( int result in grantResults )
                    {
                        if(result!=(int)Permission.Granted)
                        {
                            ErrorDialog.newInstance("This app needs permission form camera and audio record")
                               .Show(ChildFragmentManager, FRAGMENT_DIALOG);
                            //
                            bOk = false;
                        }

                    }
                    //
                    if ( bOk )
                    {
                        int iTaskId = 0;
                        CCtxQyMc pQyMc = g.g_pQyMc;
                        CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
                        QMC_TASK_INFO pTaskInfo = (QMC_TASK_INFO)qyFuncs.getQmcTaskInfoByIndex(null,pProcInfo,mOwner_wnd.m_index_taskInfo,"");
                        if (pTaskInfo != null)
                        {
                            iTaskId = pTaskInfo.var.iTaskId;
                        }

                        doTask_av(mOwner_wnd.m_iCmd,iTaskId);
                        //
                        return;
                    }

                }
                else
                {
                    ErrorDialog.newInstance("This app needs permission for camera and audio record")
                        .Show(ChildFragmentManager, FRAGMENT_DIALOG);
                }

            }
            else
            {
                base.OnRequestPermissionsResult(requestCode, permissions, grantResults);
            }
        }

        public bool hasPermissionsGranted(string[] permissions)
        {
            foreach (string permission in permissions){
                if (ActivityCompat.CheckSelfPermission(Activity, permission)
                    != Permission.Granted)
                {
                    return false;
                }
            }
            return true;
        }

        static Size chooseVideoSize(Size[] choices)
        {
            if (choices.Length == 0)
            {
                return new Size(0, 0);
            }
            foreach (Size size in choices)
            {
                if ( size.Width==size.Height * 4/ 3 && size.Width <=1080)
                {
                    return size;
                }
            }

            return choices[choices.Length - 1];

        }

        static Size chooseOptimalSize(Size[] choices,int width,int height,Size aspectRatio)
        {
            List<Size> bigEnough = new List<Size>();
            List<Size> notBigEnough = new List<Size>();
            int w = aspectRatio.Width;
            int h = aspectRatio.Height;

            for ( int i = 0; i < choices.Length; i++)
            {
                Size option = choices[i];
                if(option.Height==option.Width * h/w 
                    && option.Width>=width && option.Height>=height) {
                    bigEnough.Add(option);
                }
            }

            if ( bigEnough.Count>0)
            {
                return (Size)Collections.Min(bigEnough, new CompareSizesByArea());
            }
            else
            {
                return choices[0];
            }


        }

        //
        public string selectCamera(CameraManager manager,bool bFront)
        {
            string sel_id=null;

            string[] cameraIdList = manager.GetCameraIdList();
            if (cameraIdList == null) return null;

            foreach(string cameraId in cameraIdList)
            {
                CameraCharacteristics characteristics = manager.GetCameraCharacteristics(cameraId);
                if (bFront)
                {
                    if (((Integer)(characteristics.Get(CameraCharacteristics.LensFacing))).IntValue() == (int)LensFacing.Front)
                    {
                        sel_id = cameraId;
                        break;
                    }
                }
                else
                {
                    if (((Integer)(characteristics.Get(CameraCharacteristics.LensFacing))).IntValue() == (int)LensFacing.Back)
                    {
                        sel_id = cameraId;
                        break;
                    }
                }
            }
            if (sel_id == null)
            {
                if (cameraIdList.Length > 0)
                {
                    sel_id = cameraIdList[0];
                }
            }

            return sel_id;
       }


        //
        private void updateControls()
        {

        }

        //
        public class MainHandler : Handler
        {
            private const int MSG_SEND_CAMERA_PARAMS0 = 0;
            private const int MSG_SEND_CAMERA_PARAMS1 = 1;
            private const int MSG_SEND_RECT_SIZE = 2;
            private const int MSG_SEND_ZOOM_AREA = 3;
            private const int MSG_SEND_ROTATE_DEG = 4;
            //
            private const int MSG_talkDraw_needRestart = 10;

            //private WeakReference<TextureFromCameraActivity> mWeakActivity;
            Fragment_dlgTalk_av2 m_fg;

            public MainHandler(Fragment_dlgTalk_av2 fg)
            {
                //mWeakActivity = new WeakReference<TextureFromCameraActivity>(activity);
                m_fg = fg;
            }

            /**
             * Sends the updated camera parameters to the main thread.
             * <p>
             * Call from render thread.
             */
            public void sendCameraParams(int width, int height, float fps)
            {
                // The right way to do this is to bundle them up into an object.  The lazy
                // way is to send two messages.
                SendMessage(ObtainMessage(MSG_SEND_CAMERA_PARAMS0, width, height));
                SendMessage(ObtainMessage(MSG_SEND_CAMERA_PARAMS1, (int)(fps * 1000), 0));
            }

            /**
             * Sends the updated rect size to the main thread.
             * <p>
             * Call from render thread.
             */
            public void sendRectSize(int width, int height)
            {
                SendMessage(ObtainMessage(MSG_SEND_RECT_SIZE, width, height));
            }

            /**
             * Sends the updated zoom area to the main thread.
             * <p>
             * Call from render thread.
             */
            public void sendZoomArea(int width, int height)
            {
                SendMessage(ObtainMessage(MSG_SEND_ZOOM_AREA, width, height));
            }

            /**
             * Sends the updated zoom area to the main thread.
             * <p>
             * Call from render thread.
             */
            public void sendRotateDeg(int rot)
            {
                SendMessage(ObtainMessage(MSG_SEND_ROTATE_DEG, rot, 0));
            }

            //
            public void send_MSG_talkDraw_needRestart()
            {
                SendMessage(ObtainMessage(MSG_talkDraw_needRestart, 0, 0));
            }



            public override void HandleMessage(Message msg)
            {
                Fragment_dlgTalk_av2 activity = m_fg;
                if (activity == null)
                {
                    //Log.d(TAG, "Got message for dead activity");
                    return;
                }

#if true
                switch (msg.What)
                {
                    case MSG_SEND_CAMERA_PARAMS0:
                        {
                            activity.mCameraPreviewWidth_unused = msg.Arg1;
                            activity.mCameraPreviewHeight_unused = msg.Arg2;
                            break;
                        }
                    case MSG_SEND_CAMERA_PARAMS1:
                        {
                            activity.mCameraPreviewFps_unused = msg.Arg1 / 1000.0f;
                            activity.updateControls();
                            break;
                        }
                    case MSG_SEND_RECT_SIZE:
                        {
                            activity.mRectWidth = msg.Arg1;
                            activity.mRectHeight = msg.Arg2;
                            activity.updateControls();
                            break;
                        }
                    case MSG_SEND_ZOOM_AREA:
                        {
                            activity.mZoomWidth = msg.Arg1;
                            activity.mZoomHeight = msg.Arg2;
                            activity.updateControls();
                            break;
                        }
                    case MSG_SEND_ROTATE_DEG:
                        {
                            activity.mRotateDeg = msg.Arg1;
                            activity.updateControls();
                            break;
                        }
                    case MSG_talkDraw_needRestart:
                        {
                            Activity_dlgTalk_av dlgTalk_av = (Activity_dlgTalk_av)activity.Activity;
                            if (dlgTalk_av.m_bTalkDraw_needRestart)
                            {
                                dlgTalk_av.pauseTaskAv("fg_dlgTalk_av2.Handler, MSG_talkDraw_needRestart");
                                //
                                dlgTalk_av.m_bDlgTalk_av_readyFor_talkDrawRestart = true;
                            }
                        }
                        break;
                    default:
                        throw new RuntimeException("Unknown message " + msg.What);
                }
#endif
            }
        }

        //
 
        //
  
        }
}




