
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

//
namespace qyMessengerApp.Droid
{
    public class Fragment_dlgTalk_av : Fragment
    {
        //private static String TAG = "Camera2VideoFragment";
        public static int REQUEST_VIDEO_PERMISSIONS = 1;
        public static string FRAGMENT_DIALOG = "dialog";

        public static string[] VIDEO_PERMISSIONS = {
            Manifest.Permission.Camera,
            Manifest.Permission.RecordAudio,
        };

        //
        public Activity_dlgTalk_av mOwner_wnd;

        //
        public MyTextureView mTextureView;
        private dlgTalk_av_Renderer mRenderer;

        //
        Button m_btn_request;
        TextView m_tv_ioStatus;
        Button m_btn_more;
        Button m_btn_av;
        //
        //public bool mIsShutter;

        //
#if DEBUG
        public bool m_bTestDec;

        //
        public MyTextureView mTextureView1;

        //
        //public TestDec m_testDec;


        //
        public struct TestEnc {
            public CameraToMpegTest cameraToMpegTest;
            //
            public EncodeAndMuxTest encodeAndMuxTest;
        };

        //
        public TestEnc m_testEnc;

#endif

        //
        string mCameraId;
        public CameraDevice mCameraDevice;
        public CameraCaptureSession mPreviewSession;
        public bool m_camera_isOpen;

        //
        Size mPreviewSize;
        Size mVideoSize;

        //
        public Semaphore mCameraOpenCloseLock = new Semaphore(1);

        //
        MyCameraStateCallback mStateCallback;

        //
        public int mSensorOrientation;
        CaptureRequest.Builder mPreviewBuilder;


        //
        ImageReader mImageReader;
        ImageAvailableListener mOnImageAvailableListener;

        //
        HandlerThread mBackgroundThread;
        public Handler mBackgroundHandler;

        

        //
        public static volatile bool sReleaseInCallback = true;

        //
        public unsafe int gui_onTimer(object p0, object p1, object p2)
        {
            Activity_dlgTalk_av owner = (Activity_dlgTalk_av)this.Activity;


            //
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();


            //
            string str = string.Format("{0,6:0.0},{1,6:0.0}", pProcInfo.status.netStat.ins.uiInSpeedInKbps / 1000.0f, pProcInfo.status.netStat.ins.uiOutSpeedInKbps / 1000.0f);

            //
            m_tv_ioStatus.Text = str;




            //
            //qyFuncs.traceLog("fg_dlgTalk_av onTimer");

            return 0;
        }

        //
        int waitTextureViewAvailable(object p0, object p1, object p2)
        {
            int iErr = -1;
            Activity_dlgTalk_av owner = (Activity_dlgTalk_av)this.Activity;

            //qyFuncs.traceLog("fg_dlgTalk_av, waitTextureViewAvailable called");

            if (!mTextureView.IsAvailable)
            {
                qyFuncs.traceLog("fg_dlgTalk_av,gui_onTimer, textureView.isAvail is false");

                return 0;
            }
            owner.killTimer();
            qyFuncs.traceLog("fg_dlgTalk_av, waitTextureViewAvailable, after killTimer");

            //
            if (!hasPermissionsGranted(VIDEO_PERMISSIONS))
            {
                requestVideoPermissions();
                goto errLabel;
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

                if (false)
                {
                    uint tid = qyFuncs.myGetCurrentThreadId();

                    //qyFuncs_Droid.testDec_startPlayback(ref this.m_testDec, this.mTextureView1);

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
                    this.m_testEnc.encodeAndMuxTest = new EncodeAndMuxTest();
                    //
                    this.m_testEnc.encodeAndMuxTest.testEncodeVideoToMp4();
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
            
            //
            iErr = 0;
            errLabel:

            return iErr;
        }






        //
        public static unsafe int initVideoCapDev( object hTalk, int iWndContentType, string displayName_selected, ref BITMAPINFOHEADER pBih_suggested, CAP_procInfo_bmpCommon pCapBmp )

        {
            int iErr = -1;

            if (iWndContentType != Consts.CONST_qyWndContentType_talker) return -1;
            Activity_dlgTalk dlgTalk = (Activity_dlgTalk)hTalk;
            if (!GuiShare.pf_IsWindow(dlgTalk.m_var.m_hTool_dlgTalk_av)) return -1;
            Activity_dlgTalk_av dlgTalk_av = (Activity_dlgTalk_av)dlgTalk.m_var.m_hTool_dlgTalk_av;
            Fragment_dlgTalk_av fg = null;
            //
#if __USE_fg1__
            if ( dlgTalk_av.m_fg_dlgTalk_av==null ) return -1;
            fg= dlgTalk_av.m_fg_dlgTalk_av;
#endif
            //
            if (!fg.mTextureView.IsAvailable) return -1;

            //
            int w, h;
            //w = fg.mTextureView.Width;
            //h = fg.mTextureView.Height;
            w = pBih_suggested.biWidth;
            h = pBih_suggested.biHeight;

            //
            fg.startBackgroundThread();       
            fg.openCamera(w, h);
            pCapBmp.mSensorOrientation = fg.mSensorOrientation;
                        

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
            Fragment_dlgTalk_av fg = null;
#if __USE_fg1__
            if (dlgTalk_av.m_fg_dlgTalk_av == null) return -1;
            fg=dlgTalk_av.m_fg_dlgTalk_av;
#endif



            fg.closeCamera();
            fg.stopBackgroundThread();

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
            Fragment_dlgTalk_av fg = null;
#if __USE_fg1__
            if (dlgTalk_av.m_fg_dlgTalk_av == null) return false;
            fg=dlgTalk_av.m_fg_dlgTalk_av;
#endif
            if (fg.mImageReader == null) return false;

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
            bih_org.biWidth = fg.mImageReader.Width;
            bih_org.biHeight = fg.mImageReader.Height;
            if ( fg.mImageReader.ImageFormat==ImageFormatType.Yuv420888)
            {
                bih_org.biCompression = Consts.CONST_fourcc_I420;
            }
            else
            {
                qyFuncs.traceLog("bGetCapturePara failed, not supported imgFormat");
                goto errLabel;
            }
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
        public static Fragment_dlgTalk_av NewInstance()
        {
            return new Fragment_dlgTalk_av();
        }

        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            //
            mOwner_wnd = (Activity_dlgTalk_av)this.Activity;

            // Create your fragment here
            mOnImageAvailableListener = new ImageAvailableListener(this);
            //mSurfaceTextureListener = new dlgTalk_av_SurfaceTextureListener(this);
            mStateCallback = new MyCameraStateCallback(this);

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
            mTextureView = (MyTextureView)view.FindViewById(Resource.Id.texture);
            m_btn_request = (Button)view.FindViewById(Resource.Id.btn_request);
            m_tv_ioStatus = (TextView)view.FindViewById(Resource.Id.tv_ioStatus);
            m_btn_more = (Button)view.FindViewById(Resource.Id.btn_more);
            m_btn_av = (Button)view.FindViewById(Resource.Id.btn_av);


            //  
            mRenderer = new dlgTalk_av_Renderer(this,Consts.CONST_iFgType_dlgTalk_av);
           mRenderer.Start();

           //
           mTextureView.SurfaceTextureListener = mRenderer;

            //
#if DEBUG
            //mTextureView1 = (MyTextureView)view.FindViewById(Resource.Id.texture1);
#endif


            //
            m_btn_request.Click += M_btn_request_Click;
            m_btn_av.Click += M_btn_av_Click;

            //
            m_btn_av.Text = "Cancel";


            //
            Activity_dlgTalk_av owner = (Activity_dlgTalk_av)this.Activity;
            owner.setTimer(100, waitTextureViewAvailable);

            //
            return view;
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

        

        public int doClean_ifActivityIsFinishing()
        {
            //
            qyFuncs.showInfo_open(0,null,"fg_dlgTalk_av.doClean_ifActivityIsFinished enters");

            Activity_dlgTalk_av owner = (Activity_dlgTalk_av)this.Activity;
            if (owner != null)
            {
                //
                owner.killTimer();

                //
                qyFuncs_Droid.dlgTalk_closeTaskAv(owner.mOwner_hTalk, owner.mOwner_hTalk.m_var, "fg_dlgTalk_av.doClean_ifActivityIsFinishing");
            }
            //
            if (mRenderer != null)
            {
                mRenderer.halt();
                Java.Lang.Thread h = mRenderer;
                qyFuncs_Droid.waitForThread1(ref h, 10000);
                mRenderer = (dlgTalk_av_Renderer)h;
            }

            //
            qyFuncs.showInfo_open(0,null,"fg_dlgTalk_av.doClean_ifActivityIsFinished leaves");

            return 0;
        }

        public override void OnDestroy()
        {
            base.OnDestroy();

            //

            
        }


        public void startBackgroundThread()
        {
            mBackgroundThread = new HandlerThread("CameraBackground");
            mBackgroundThread.Start();
            mBackgroundHandler = new Handler(mBackgroundThread.Looper);

            //
            bool bDbg = false;
            string str;

#if DEBUG
            bDbg = true;
#endif
            str = string.Format("startBackgroundThread, threadId {0}", mBackgroundThread.ThreadId);
            qyFuncs.showInfo_open(0, null, str);

            return;
        }

        public void stopBackgroundThread()
        {
            if (mBackgroundThread != null)
            {
                mBackgroundThread.QuitSafely();
            }
            try
            {
                if (mBackgroundThread != null)
                {
                    mBackgroundThread.Join();
                }
                mBackgroundThread = null;
                mBackgroundHandler = null;
            }
            catch(InterruptedException e)
            {
                e.PrintStackTrace();
            }
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

            //
#if DEBUG
            qyFuncs_Droid.printChoices(choices);
#endif

            //
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
        public void openCamera(int width,int height)
        {
            if ( !hasPermissionsGranted(VIDEO_PERMISSIONS))
            {
                //requestVideoPermissions();
                return;

            }
            Activity activity = Activity;
            if(null==activity || activity.IsFinishing)
            {
                return;
            }
            CameraManager manager = (CameraManager)activity.GetSystemService(Context.CameraService);
            try
            {
                if (!mCameraOpenCloseLock.TryAcquire(2500, TimeUnit.Milliseconds))
                {
                    goto errLabel;

                }
                string[] cameraIdList = manager.GetCameraIdList();
                bool bFront = true;
                string cameraId = selectCamera(manager, bFront);// manager.GetCameraIdList()[0];
                //
                mCameraId = cameraId;
                //
                CameraCharacteristics characteristics = manager.GetCameraCharacteristics(cameraId);
                StreamConfigurationMap map = (StreamConfigurationMap)characteristics
                    .Get(CameraCharacteristics.ScalerStreamConfigurationMap);
                mSensorOrientation = (int)characteristics.Get(CameraCharacteristics.SensorOrientation);
                if (map == null) goto errLabel;

                Size[] sizes = map.GetOutputSizes(Class.FromType(typeof(ImageReader)));
                if (sizes.Length == 0) goto errLabel;

                //mVideoSize = new Size(640, 480);
                if (mSensorOrientation == 90 || mSensorOrientation == 270)
                {
                    mVideoSize = new Size(height, width);

                }
                else
                {
                    mVideoSize = new Size(width, height);
                }
                mVideoSize = chooseOptimalSize(map.GetOutputSizes(Class.FromType(typeof(ImageReader))), mVideoSize.Width, mVideoSize.Height, mVideoSize);
                //
                mImageReader = ImageReader.NewInstance(mVideoSize.Width, mVideoSize.Height, Android.Graphics.ImageFormatType.Yuv420888, 3);
                mImageReader.SetOnImageAvailableListener(mOnImageAvailableListener, mBackgroundHandler);
                //
                /*
                mPreviewSize = chooseOptimalSize(map.GetOutputSizes(Class.FromType(typeof(SurfaceTexture))), width, height, mVideoSize);
                //
                int orientation = (int)Resources.Configuration.Orientation;
                if (orientation == (int)Android.Content.Res.Orientation.Landscape)
                {
                    mTextureView.SetAspectRatio(mPreviewSize.Width, mPreviewSize.Height);
                }
                else
                {
                    mTextureView.SetAspectRatio(mPreviewSize.Height, mPreviewSize.Width);
                }
                configureTransform(width, height);
                */
                //
                manager.OpenCamera(cameraId, mStateCallback, null);

                //
                this.m_camera_isOpen = true;

                //
            }
            catch (CameraAccessException e)
            {
                Toast.MakeText(activity, "cannot access camera", ToastLength.Short).Show();
                goto errLabel;
            }
            catch (NullPointerException e)
            {
                Toast.MakeText(activity, "cannot support camera2", ToastLength.Short).Show();
                goto errLabel;

            }
            catch (InterruptedException e)
            {
                Toast.MakeText(activity, "camera2, interrupted", ToastLength.Short).Show();
                goto errLabel;

            }
            catch (Java.Lang.Exception e)
            {
                Toast.MakeText(activity, "camera2, exception", ToastLength.Short).Show();
                goto errLabel;
            }

            errLabel:

            return;
        }

        public void closeCamera()
        {
            try
            {
                mCameraOpenCloseLock.Acquire();
                //
                this.m_camera_isOpen = false;
                //
                closePreviewSession();
                if(null!=mCameraDevice)
                {
                    mCameraDevice.Close();
                    mCameraDevice = null;
                }
                if ( null!=mImageReader)
                {
                    mImageReader.Close();
                    mImageReader = null;
                }
            }
            catch(InterruptedException e)
            {

            }
            catch(Java.Lang.Exception e)
            {
                int ii = 0;
            }
            finally
            {
                mCameraOpenCloseLock.Release();
            }

        }

        //
#if DEBUG
        //CameraOutputSurface m_outputSurface;
#endif


        public void startPreview()
        {
            if ( null==mCameraDevice||!mTextureView.IsAvailable 
                //|| null==mPreviewSize
                )
            {
                return;
            }
            try
            {
                closePreviewSession();
                /*
                SurfaceTexture texture = mTextureView.SurfaceTexture;
                //Assert(texture != null);
                texture.SetDefaultBufferSize(mPreviewSize.Width, mPreviewSize.Height);
                */
                mPreviewBuilder = mCameraDevice.CreateCaptureRequest(CameraTemplate.Preview);

                List<Surface> surfaces = new List<Surface>();

                //
#if false
                Surface previewSurface = new Surface(texture);
                surfaces.Add(previewSurface);
                mPreviewBuilder.AddTarget(previewSurface);
#endif

                //
                Surface readerSurface = mImageReader.Surface;
                surfaces.Add(readerSurface);
                mPreviewBuilder.AddTarget(readerSurface);

                //
#if DEBUG
#if false
                int saveWidth = 640;
                int saveHeight = 360;

                //
                m_outputSurface = new CameraOutputSurface(this, (EGLContext)mOwner_wnd.mOwner_hTalk.m_var.av.m_share_eglContext, 640, 360,null);
                //
                m_outputSurface.mTextureRender.createEnv(saveWidth, saveHeight);

                //
                surfaces.Add(m_outputSurface.getSurface());
                mPreviewBuilder.AddTarget(m_outputSurface.getSurface());
#endif
#endif



                //
                mCameraDevice.CreateCaptureSession(surfaces, new PreviewCaptureStateCallback(this), mBackgroundHandler);



            }
            catch(CameraAccessException e)
            {
                e.PrintStackTrace();
            }

        }

        public void updatePreview()
        {
            if ( null == mCameraDevice)
            {
                return;
            }
            try
            {
                setupCaptureRequestBuilder(mPreviewBuilder);
                //
                //HandlerThread thread = new HandlerThread("cameraPreview");
                //thread.Start();
                //
                mPreviewSession.SetRepeatingRequest(mPreviewBuilder.Build(), null, mBackgroundHandler);
            }
            catch(CameraAccessException e)
            {
                e.PrintStackTrace();
            }

        }

        public Android.Util.Range  getRange()
        {
            CameraManager manager = (CameraManager)Context.GetSystemService(Context.CameraService);
            CameraCharacteristics chars = null;
            try
            {
                chars = manager.GetCameraCharacteristics(mCameraId);
            }
            catch(CameraAccessException e)
            {
                e.PrintStackTrace();
            }
            Android.Util.Range[] ranges = chars.Get(CameraCharacteristics.ControlAeAvailableTargetFpsRanges).ToArray<Android.Util.Range>();
            
            Android.Util.Range result=null;

            foreach(Android.Util.Range range in ranges)
            {
                int min_fps = 7;// 10;
                
                if ((int)range.Lower < min_fps)
                    continue;
                if (result == null) result = range;
                else if ((int)range.Lower <= 15 && (int)range.Upper - (int)range.Lower > (int)result.Upper - (int)result.Lower)
                    result = range;
                
                /*
                int upper = (int)range.Upper;
                if (upper >= 10)
                {
                    if ( result==null || upper < (int)result.Upper)
                    {
                        result = range;
                    }
                }
                */
                continue;
            }

        errLabel:
            return result;
        }

        public void setupCaptureRequestBuilder(CaptureRequest.Builder builder)
        {
            //builder.Set(CaptureRequest.ControlMode, new Java.Lang.Integer((int)ControlMode.Auto));
            //
            builder.Set(CaptureRequest.ControlAfMode, new Java.Lang.Integer((int)ControlAFMode.ContinuousPicture));
            //
            Android.Util.Range range = getRange();
            if (range != null)
            {
                builder.Set(CaptureRequest.ControlAeTargetFpsRange, range);
            }
            //
            builder.Set(CaptureRequest.ControlAfTrigger, new Java.Lang.Integer((int)ControlAFTrigger.Idle));
        }

        public void configureTransform(int viewWidth, int viewHeight)
        {
            return;
            //
            Activity activity = Activity;
            if ( null==mTextureView||null==mPreviewSize|| null==activity)
            {
                return;
            }
            int rotation = (int)activity.WindowManager.DefaultDisplay.Rotation;
            Android.Graphics.Matrix matrix = new Android.Graphics.Matrix();
            RectF viewRect = new RectF(0, 0, viewWidth, viewHeight);
            RectF bufferRect = new RectF(0, 0, mPreviewSize.Height, mPreviewSize.Width);
            float centerX = viewRect.CenterX();
            float centerY = viewRect.CenterY();
            if ((int)SurfaceOrientation.Rotation90 == rotation || (int)SurfaceOrientation.Rotation270 == rotation)
            {
                bufferRect.Offset(centerX - bufferRect.CenterX(), centerY - bufferRect.CenterY());
                matrix.SetRectToRect(viewRect, bufferRect, Android.Graphics.Matrix.ScaleToFit.Fill);
                float scale = System.Math.Max(
                    (float)viewHeight / mPreviewSize.Height,
                    (float)viewWidth / mPreviewSize.Width);
                matrix.PostScale(scale, scale, centerX, centerY);
                matrix.PostRotate(90 * (rotation - 2), centerX, centerY);


            }
            mTextureView.SetTransform(matrix);

            return;
        }


        public void closePreviewSession()
        {
            if (mPreviewSession != null)
            {
                mPreviewSession.Close();
                mPreviewSession = null;
            }
        }


        //
 
    }
}




