
//

//
using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//
using qy;
using qy.Droid;
using Android.Support.Design.Widget;
using Android.Opengl;

//
namespace qyMessengerApp.Droid
{
    [Activity(Label = "Activity_dlgTalk_av")]
    public class Activity_dlgTalk_av : BaseActivity
    {
        //
        public Activity_dlgTalk mOwner_hTalk;

        //
        public Fragment_dlgTalk_av m_fg_dlgTalk_av;
        //
#if DEBUG
        public Fragment_test m_fg_test;
        public Fragment_test2 m_fg_test2;
#endif
        //
        public Fragment_dlgTalk_av2 m_fg_dlgTalk_av2;

        //
        BottomSheetDialog m_bsd_askToStopAv;

        //
        public int m_iCmd;
        public int m_index_taskInfo;

        //
        public uint uiLastTickCnt_touch;

        //
        public MyHandler mHandler;

        //
        public bool m_bSurfaceTextureSizeChanged;
        //
        public bool m_bTalkDraw_needRestart;
        public bool m_bDlgTalk_av_readyFor_talkDrawRestart;


        //
        public class MyHandler : Handler
        {
            Activity_dlgTalk_av mOwner;

            //
            public MyHandler(Activity_dlgTalk_av owner)
            {
                mOwner = owner;
            }


            public override void HandleMessage(Message msg)
            {
                //base.HandleMessage(msg);

                switch (msg.What)
                {
                    case Consts.CONST_qyWm_postComm:

                        //
                        switch (msg.Arg1)
                        {
                            case Consts.CONST_qyWmParam_closeWnd:
                                if (mOwner.mOwner_hTalk.m_var.av.taskInfo.bTaskExists)
                                {
                                    //
                                    this.mOwner.pauseTaskAv("dlgTalk_av.handler.HandleMessage, get a msg closeWnd");
                                    //
                                }                                 
                                GuiShare.pf_PostMessage_new(mOwner, Consts.CONST_qyWndContentType_dlgTalk_av, Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_doClean, 0);                                 
                                break;
                            case Consts.CONST_qyWmParam_doClean:
                                {
                                    if (this.mOwner.mOwner_hTalk.m_var.av.taskInfo.bTaskExists)
                                    {
                                        //qyFuncs_Droid.dlgTalk_cancelTasks(mOwner_hTalk, mOwner_hTalk.m_var, mOwner_hTalk.m_var.av.taskInfo.iTaskId, true);
                                        ushort usOp = 0;
                                        if (this.mOwner.mOwner_hTalk.m_var.av.taskInfo.ucbStarter) usOp = Consts.CONST_imOp_send_cancel;
                                        else usOp = Consts.CONST_imOp_recv_cancel;
                                        //
                                        PARAM_dlgTalk_procTask param = new PARAM_dlgTalk_procTask();
                                        //
                                        qyFuncs_Droid.dlgTalk_procTask1(this.mOwner.mOwner_hTalk, this.mOwner.mOwner_hTalk.m_var.av.taskInfo.iTaskId, usOp, "", ref param);
                                    }
            
                                    //            
                                    this.mOwner.doFinish("BtnYes_Click");

                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;

                }

                return;
            }

            //
        }



        //
        public unsafe int gui_onTimer(object p0,object p1,object p2)
        {
            string str;

            //
            if ( m_fg_dlgTalk_av!=null)
            {
                m_fg_dlgTalk_av.gui_onTimer(p0,p1,p2);
            }
            if (m_fg_dlgTalk_av2 != null)
            {
                m_fg_dlgTalk_av2.gui_onTimer(p0, p1, p2);
            }

            //
#if DEBUG
            //
#if false
            int i;
            int cnt = 0;
            for ( i=0;i< mOwner_hTalk.m_var.tmp_hTools_dlgTalk_av.Length; i++)
            {
                if (mOwner_hTalk.m_var.tmp_hTools_dlgTalk_av[i] != null)
                {
                    cnt++;
                }
            }
            mOwner_hTalk.m_var.cnt_tmpTools = cnt;
            str = string.Format("tmpTools {0}", cnt);
            qyFuncs.showInfo_open(0, null, str);
#endif

#endif



            //
            return 0;
        }




        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            int iErr = -1;
            //
            string str;

            //
            mTag = "dlgTalk_av";

            //
            this.mHandler = new MyHandler(this);

            //
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
            MIS_CNT pMisCnt = pProcInfo.pMisCnt;
            //
            Intent intent = this.Intent;
            int iCmd = intent.GetIntExtra("iCmd", 0);
            UInt64 ui64Id = (UInt64)intent.GetLongExtra("ui64Id", 0);
            int index_task = intent.GetIntExtra("index_qmcTaskInfo", 0);
            //
            Console.WriteLine("ui64Id {0}", ui64Id);
            QY_MESSENGER_ID idInfo;idInfo.ui64Id = ui64Id;
            object hTalk=null;
            if (0 != GuiShare.pf_findTalker(pQyMc, pMisCnt, idInfo, ref hTalk))
            {
                goto errLabel;
            }
            mOwner_hTalk = (Activity_dlgTalk)hTalk;
            DLG_TALK_var pMgrVar = mOwner_hTalk.m_var;
            //
            if (0!=addTo_tmpTools(pMgrVar, "dlgTalk_av.OnCreate"))
            {
                goto errLabel;
            }

            //
            RequestedOrientation = Android.Content.PM.ScreenOrientation.FullSensor;


            //
            m_iCmd = iCmd;
            m_index_taskInfo = index_task;


            // Create your application here
            SetContentView(Resource.Layout.layout_activity_dlgTalk_av);


            //
            if (pProcInfo.cfg.ucb_USE_Fragment_dlgTalk_av) {
                m_fg_dlgTalk_av = Fragment_dlgTalk_av.NewInstance();
            }
            else {
                m_fg_dlgTalk_av2 = Fragment_dlgTalk_av2.NewInstance();
            }
            //
#if DEBUG
#if false
            m_fg_test = new Fragment_test();
            m_fg_test2 = new Fragment_test2();
#endif
#endif
            //
            //
            FragmentTransaction ft = FragmentManager.BeginTransaction();
            //
            if (m_fg_dlgTalk_av != null) {
                ft.Replace(Resource.Id.container, m_fg_dlgTalk_av);                    
            }
            //.Add(Resource.Id.container,m_fg_test)
            //.Add(Resource.Id.container, m_fg_test2)
            if (m_fg_dlgTalk_av2 != null) {
                ft.Replace(Resource.Id.container, m_fg_dlgTalk_av2);                    
            }
            //              
            ft.Commit();

            //
            this.Window.AddFlags(WindowManagerFlags.KeepScreenOn);


            //
            iErr = 0;
            errLabel:
            if ( 0!=iErr )
            {
                doFinish("dlgTalk_av.OnCreate failed");
            }

        }

        protected override void OnResume()
        {
            base.OnResume();

            //
            qyFuncs.traceLog("dlgTalk_av: onResume");
        }

        //
        int doClean(string str)
        {
            int ii = 0;
            //
            Window.ClearFlags(WindowManagerFlags.KeepScreenOn);
            //
            if (m_fg_dlgTalk_av != null)
            {
                m_fg_dlgTalk_av.doClean_ifActivityIsFinishing();
            }
            //
#if DEBUG
            if (m_fg_test != null)
            {
                m_fg_test.doClean_ifActivityIsFinishing();
                //
            }
            //
            if (m_fg_test2 != null)
            {
                m_fg_test2.doClean_ifActivityIsFinishing();
            }
#endif
            //
            if (m_fg_dlgTalk_av2 != null)
            {
                m_fg_dlgTalk_av2.doClean_ifActivityIsFinishing();
            }
            //
            //removeFrom_tmpTools(mOwner_hTalk.m_var, "OnPause");
            //
            return 0;

        }

        protected override void OnPause()
        {
            if (IsFinishing)
            {
                //
                doClean("OnPause,isFinishing");                
            }

            //
            base.OnPause();

            //
            string str;
            str=string.Format("dlgTalk_av: onPause, {0}", IsFinishing ? "IsFinishing" : "");
            qyFuncs.showInfo_open(0, null, str);


        }

        protected override void OnDestroy()
        {
            //
            qyFuncs.showInfo_open(0, null, "dlgTalk_av.OnDestroy enters");

            //
            doClean("onDestroy");

            //
            if (mOwner_hTalk != null)
            {
                removeFrom_tmpTools(mOwner_hTalk.m_var, "OnDestroy");
            }
            
            //
            base.OnDestroy();
            Dispose();

            //
            //
            qyFuncs.showInfo_open(0, null, "dlgTalk_av.OnDestroy leaves");


        }

        //
        protected override void OnSaveInstanceState(Bundle outState)
        {
            base.OnSaveInstanceState(outState);
            //
            //横竖屏切换前调用，保存用户想要保存的数据，以下是样例
            outState.PutString("name", "yoosir");
            int ii = 0;

            //
            pauseTaskAv("OnSaveInstanceState");

        }


        protected override void OnRestoreInstanceState(Bundle savedInstanceState)
        {
            base.OnRestoreInstanceState(savedInstanceState);
            //
            if (savedInstanceState != null)
            {
                String name = savedInstanceState.GetString("name");
                //
                int ii = 0;
            }
        }


        //
        public override void OnBackPressed()
        {
            //
            DLG_TALK_var m_var=this.mOwner_hTalk.get_pm_var();
            if ( m_var.av.taskInfo.bTaskExists )
            {
                View view = this.LayoutInflater.Inflate(Resource.Layout.layout_yesCancel,null);
                this.m_bsd_askToStopAv = new BottomSheetDialog(this);
                m_bsd_askToStopAv.SetContentView(view);
                //
                BottomSheetBehavior behavior = BottomSheetBehavior.From((View)view.Parent);
                behavior.State = BottomSheetBehavior.StateExpanded;

                //
                TextView tvTitle = (TextView)view.FindViewById(Resource.Id.title);
                tvTitle.Text = "清扬视频";
                TextView tvContent = (TextView)view.FindViewById(Resource.Id.content);
                tvContent.Text = "要停止视频通话吗？";
                //
                Button btnYes = (Button)view.FindViewById(Resource.Id.yes);
                btnYes.Click += BtnYes_Click;
                Button btnCancel = (Button)view.FindViewById(Resource.Id.cancel);
                btnCancel.Click += BtnCancel_Click;
                //
                m_bsd_askToStopAv.Show();

                return;
            }


            //
            base.OnBackPressed();
        }

        //
        public override bool OnTouchEvent(MotionEvent e)
        {
            this.uiLastTickCnt_touch = qyFuncs.myGetTickCount(null);

            //
            Console.WriteLine("dlgTalk_av, OnTouchEvent enters");

            //
#if DEBUG
            if (m_fg_test != null)
            {
                return m_fg_test.OnTouchEvent(e);
            }
#endif
            //
            qyFuncs_Droid.viewInstantAssistant(null, 0, 0, 0, mOwner_hTalk, true);

            //
            Console.WriteLine("dlgTalk_av, OnTouchEvent leaves");

            //
            return base.OnTouchEvent(e);

        }

        //
        public override void OnWindowFocusChanged(bool hasFocus)
        {
            base.OnWindowFocusChanged(hasFocus);
            //
            if (hasFocus)
            {
                hideSystemUI();
            }
            else
            {
                showSystemUI();
            }
        }

        public void hideSystemUI()
        {
            // Enables regular immersive mode.
            // For "lean back" mode, remove SYSTEM_UI_FLAG_IMMERSIVE.
            // Or for "sticky immersive," replace it with SYSTEM_UI_FLAG_IMMERSIVE_STICKY
            View decorView = this.Window.DecorView;
            decorView.SystemUiVisibility=(StatusBarVisibility)(
                    SystemUiFlags.Immersive
                    // Set the content to appear under the system bars so that the
                    // content doesn't resize when the system bars hide and show.
                    | SystemUiFlags.LayoutStable
                    | SystemUiFlags.LayoutHideNavigation
                    | SystemUiFlags.LayoutFullscreen
                    // Hide the nav bar and status bar
                    | SystemUiFlags.HideNavigation
                    | SystemUiFlags.Fullscreen);
        }

        // Shows the system bars by removing all the flags
        // except for the ones that make the content appear under the system bars.
        public void showSystemUI()
        {
            View decorView = Window.DecorView;
            decorView.SystemUiVisibility=(StatusBarVisibility)(
                    SystemUiFlags.LayoutStable
                    | SystemUiFlags.LayoutHideNavigation
                    | SystemUiFlags.LayoutFullscreen);
        }


        //
        private void BtnCancel_Click(object sender, EventArgs e)
        {
            m_bsd_askToStopAv.Dismiss();           
        }

        private void BtnYes_Click(object sender, EventArgs e)
        {
            //throw new NotImplementedException();
            //
#if false
            if(this.mOwner_hTalk.m_var.av.taskInfo.bTaskExists)
            {
                //qyFuncs_Droid.dlgTalk_cancelTasks(mOwner_hTalk, mOwner_hTalk.m_var, mOwner_hTalk.m_var.av.taskInfo.iTaskId, true);
                ushort usOp = 0;
                if (mOwner_hTalk.m_var.av.taskInfo.ucbStarter) usOp = Consts.CONST_imOp_send_cancel;
                else usOp = Consts.CONST_imOp_recv_cancel;
                //
                PARAM_dlgTalk_procTask param = new PARAM_dlgTalk_procTask();
                //
                qyFuncs_Droid.dlgTalk_procTask1(mOwner_hTalk, mOwner_hTalk.m_var.av.taskInfo.iTaskId, usOp, "", ref param);
            }
            //
            this.doFinish("BtnYes_Click");
#endif
            //
            m_bsd_askToStopAv.Dismiss();

            //
            GuiShare.pf_PostMessage_new(this, Consts.CONST_qyWndContentType_dlgTalk_av, Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_closeWnd, 0);



        }

        //
        int addTo_tmpTools(DLG_TALK_var pMgrVar,string hint)
        {
            int iErr=-1;
            string str;

            if (hint == null) hint = "";

            int i;
            for (i = 0; i < pMgrVar.tmp_hTools_dlgTalk_av.Length; i++)
            {
                if (pMgrVar.tmp_hTools_dlgTalk_av[i] == null)
                {
                    pMgrVar.tmp_hTools_dlgTalk_av[i] = this;
                    break;
                }
            }
            if (i == pMgrVar.tmp_hTools_dlgTalk_av.Length)
            {
                str = string.Format("dlgTalk_av.OnCreate failed, too many tmp_hTools");
                qyFuncs.showInfo_open(0, null, str);
                //
                goto errLabel;
            }


            iErr = 0;
        errLabel:
            return iErr;
        }

        int removeFrom_tmpTools(DLG_TALK_var pMgrVar,string hint)
        {
            int iErr = -1;

            string str;

            if (hint == null) hint = "";

            int i;
            for (i = 0; i < pMgrVar.tmp_hTools_dlgTalk_av.Length; i++)
            {
                if (pMgrVar.tmp_hTools_dlgTalk_av[i] == this)
                {
                    pMgrVar.tmp_hTools_dlgTalk_av[i] = null;
                    pMgrVar.tmp_share_eglContexts[i] = null;
                    //
                    break;
                }
            }

            //
            mOwner_hTalk.gui_PostMessage(Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_chkTalkDraw, 0);


            //
            iErr = 0;
        errLabel:
            return iErr;
        }

        //
        public static unsafe int tmpHandler_pauseTaskAv(CTX_caller ctxCaller, object p0, object p1, object p2)
        {
            int iErr = -1;
            int iTaskId = (int)p0;
            //p1
            TASK_common taskMem = (TASK_common)p2;

            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            QMC_TASK_INFO pTaskInfo = (QMC_TASK_INFO)qyFuncs.getQmcTaskInfoByIndex(ctxCaller, pProcInfo, taskMem.m_index_taskInfo, "tmpHandler_pauseTaskAv");
            if (pTaskInfo == null) goto errLabel;
            QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
            if (pTaskData == null) goto errLabel;

            if (pTaskData.msgU.uiType == Consts.CONST_misMsgType_task
                && pTaskData.msgU.task.iTaskId == iTaskId)
            {
                TASK_transferAv task = (TASK_transferAv)taskMem;
                //
                qyFuncs.stopTransformThreads(pProcInfo, ref task.myTask,"tmpHandler_pauseTaskAv");
                

                //
                iErr = 1; goto errLabel;

            }

            iErr = 0;
            errLabel:

            return iErr;
        }


        //
        public int pauseTaskAv(string hint)
        {
            int iErr = -1;
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            //
            string str;

            //
            if (hint == null) hint = "";

            //
            DLG_TALK_var m_var = mOwner_hTalk.m_var;
            object hTalk = mOwner_hTalk;
            int iWndContentType = Consts.CONST_qyWndContentType_talker;

            //
            str=string.Format("pauseTaskAv enters, {0}",hint);
            qyFuncs.showInfo_open(0, null, str);

            //
            if (!m_var.av.taskInfo.bTaskExists) return -1;

            //
            if ( m_var.av.ucbGot_iIndex_sharedObj_localAv )
            {
                QY_SHARED_OBJ pSharedObj = qyFuncs.getSharedObjByIndex(pProcInfo,m_var.av.iIndex_sharedObj_localAv);
                if (pSharedObj == null) goto errLabel;

                if (pSharedObj.var.bCapDev)
                {
                    CAP_procInfo_bmpCommon pCapBmp = qyFuncs.getCapBmpBySth(pProcInfo, pSharedObj.var.iIndex_capBmp, 0);
                    if (pCapBmp == null) goto errLabel;
                    qyFuncs.stopCapture(hTalk, iWndContentType, (CAP_procInfo_video)pCapBmp);
                    //
                    qyFuncs.closeLocalVideo(hTalk, iWndContentType, m_var.av.iIndex_sharedObj_localAv);
                }

                // audio

            }

            //
            pProcInfo.processQ_media.qTraverse_mono(null, tmpHandler_pauseTaskAv, m_var.av.taskInfo.iTaskId, null);


            //
            m_var.m_bNeedResumeTaskAv = true;


            //
            iErr = 0;
            errLabel:

            //
            qyFuncs.showInfo_open(0, null, "pauseTaskAv leaves");

            return iErr;
        }


        //
        public static unsafe int tmpHandler_resumeTaskAv(CTX_caller ctxCaller, object p0, object p1, object p2)
        {
            int iErr = -1;
            int iTaskId = (int)p0;
            //p1
            TASK_common taskMem = (TASK_common)p2;

            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            QMC_TASK_INFO pTaskInfo = (QMC_TASK_INFO)qyFuncs.getQmcTaskInfoByIndex(ctxCaller, pProcInfo, taskMem.m_index_taskInfo, "tmpHandler_resumeTaskAv");
            if (pTaskInfo == null) goto errLabel;
            QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
            if (pTaskData == null) goto errLabel;

            if (pTaskData.msgU.uiType == Consts.CONST_misMsgType_task
                && pTaskData.msgU.task.iTaskId == iTaskId)
            {
                TASK_transferAv task = (TASK_transferAv)taskMem;
                //
                qyFuncs.startTransformThreads(pProcInfo, task.myTask.uiTaskType,ref task.myTask,"tmpHandler_resumeTaskAv");


                //
                iErr = 1; goto errLabel;

            }

            iErr = 0;
        errLabel:

            return iErr;
        }


        public int resumeTaskAv(string hint)
        {
            int iErr = -1;
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            DLG_TALK_var m_var = mOwner_hTalk.m_var;
            object hTalk = mOwner_hTalk;
            int iWndContentType = Consts.CONST_qyWndContentType_talker;

            string str;

            if (hint == null) hint = "";

            //
            str=string.Format("resumeTaskAv enters, {0}",hint);
            qyFuncs.showInfo_open(0, null, str);

            //
            m_var.m_bNeedResumeTaskAv = false;

            //
            if (!m_var.av.taskInfo.bTaskExists) return -1;

            //
            QMC_TASK_INFO pTaskInfo = qyFuncs.getQmcTaskInfoByIndex(null,pProcInfo,m_var.av.taskInfo.iIndex_taskInfo,"");
            if (pTaskInfo == null) goto errLabel;
            QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
            if (pTaskData == null) goto errLabel;
            QMC_taskData_conf pTc = (QMC_taskData_conf)pTaskData;

            //
            pTc.shared_eglContext = m_var.m_share_eglContext;

            //
            //
            if (m_var.av.ucbGot_iIndex_sharedObj_localAv)
            {
                QY_SHARED_OBJ pSharedObj = qyFuncs.getSharedObjByIndex(pProcInfo, m_var.av.iIndex_sharedObj_localAv);
                if (pSharedObj == null) goto errLabel;

                if (pSharedObj.var.bCapDev)
                {
                    CAP_procInfo_bmpCommon pCapBmp = qyFuncs.getCapBmpBySth(pProcInfo, pSharedObj.var.iIndex_capBmp, 0);
                    if (pCapBmp == null) goto errLabel;
                    //
                    uint uiCamCapType = Consts.CONST_camCapType_android;
                    VIDEO_COMPRESSOR_CFG compressor = pCapBmp.compressVideo.compressor;
                    compressor.shared_eglContext = pTc.shared_eglContext;
                    //
                    qyFuncs.openLocalVideo(pProcInfo, uiCamCapType,"",hTalk, iWndContentType, ref compressor, m_var.av.iIndex_sharedObj_localAv);
                    //
                    qyFuncs.startCapture(hTalk, iWndContentType, (CAP_procInfo_video)pCapBmp);

                    //
                    int iIndex_sharedObjUsr = 0;
                    SHARED_OBJ_USR pSharedObjUsr = qyFuncs.getSharedObjUsr(pSharedObj, iIndex_sharedObjUsr);
                    if (null == pSharedObjUsr) goto errLabel;
                    ref COMPRESS_VIDEO pCompressVideo = ref pCapBmp.compressVideo;

                    if (0 != pCompressVideo.uiTranNo_openAvDev_org)
                    {   //  
                        pSharedObjUsr.uiTranNo_openAvDev_v = (uint)(pCompressVideo.uiTranNo_openAvDev_org + iIndex_sharedObjUsr); //  pSharedObj->iIndex_curUsr;
                    }

                    //
                    m_var.av.taskInfo.local_avStream.tranInfo.video.uiTranNo_openAvDev = pSharedObjUsr.uiTranNo_openAvDev_v;
                    m_var.av.taskInfo.local_avStream.tranInfo.video.compressor = pCompressVideo.compressor.common.head;
                    m_var.av.taskInfo.local_avStream.tranInfo.video.vh_decompress = pCompressVideo.vh_decompress;
                    m_var.av.taskInfo.local_avStream.tranInfo.video.vh_compress = pCompressVideo.vh_compress;
                    m_var.av.taskInfo.local_avStream.tranInfo.video.vh_stream = pCompressVideo.vh_stream;

                    //
                }

                // audio

            }


            //
            pProcInfo.processQ_media.qTraverse_mono(null, tmpHandler_resumeTaskAv, m_var.av.taskInfo.iTaskId, null);


            //
            Activity_dlgTalk dlgTalk = mOwner_hTalk;
            bool canSpeak = qyFuncs_Droid.dlgTalk_canSpeak(dlgTalk);

            if (canSpeak)
            {
                //
                qyFuncs_Droid.dlgTalk_requestToSpeak(dlgTalk, canSpeak);

                bool bState_canSpeak = canSpeak;

                //
                this.m_fg_dlgTalk_av2.updateCtrls();

            }


            //
            iErr = 0;
        errLabel:

            qyFuncs.showInfo_open(0, null, "resumeTaskAv leaves");

            return iErr;
        }

        //
        public int save_dlgTalk_share_eglContext(EGLContext share_eglContent,string hint)
        {
            int iErr = -1;
            string str;

            if (hint == null) hint = "";

            //
            Activity_dlgTalk dlgTalk = null;
            Activity_dlgTalk_av act = (Activity_dlgTalk_av)this;// mOwner.Activity;
            if (act != null)
            {
                dlgTalk = act.mOwner_hTalk;
                DLG_TALK_var m_var = dlgTalk.m_var;
                CCtxQyMc pQyMc = g.g_pQyMc;
                CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
                MIS_CNT pMisCnt = pProcInfo.pMisCnt;

                //
                using (CQySyncObj syncObj = new CQySyncObj())
                {
                    if (0 != syncObj.sync("", pMisCnt.hMutex_syncShareEglContext)) goto errLabel;

                    int i;
                    for (i = 0; i < dlgTalk.m_var.tmp_hTools_dlgTalk_av.Length; i++)
                    {
                        if (dlgTalk.m_var.tmp_hTools_dlgTalk_av[i] == this)
                        {
                            dlgTalk.m_var.tmp_share_eglContexts[i] = share_eglContent;
                            break;
                        }

                    }

                }
            }
            
            //
            iErr = 0;
        errLabel:

            str = string.Format("save_dlgTalk_share_eglContext called, {0} {1} {2}", (share_eglContent != null) ? "egl" : "null", (iErr == 0) ? "ok" : "failed", hint);
            qyFuncs.showInfo_open(0, null, str);

            return iErr;
        }



        //
        public void changeCamera()
        {
            Activity_dlgTalk dlgTalk = this.mOwner_hTalk;
            DLG_TALK_var m_var = dlgTalk.m_var;

            //如果是竖屏切换到全屏
            if (m_var.av.taskInfo.bTaskExists)
            {
                //
                pauseTaskAv("changeCamera");
                //
                m_var.av.taskInfo.bUse_backCamera = !m_var.av.taskInfo.bUse_backCamera;
                //
                resumeTaskAv("changeCamera");
            }

            return;
        }


        //
        public void changeLocalVideo()
        {
            Activity_dlgTalk dlgTalk = this.mOwner_hTalk;
            DLG_TALK_var m_var = dlgTalk.m_var;

            //如果是竖屏切换到全屏
            if (m_var.av.taskInfo.bTaskExists)
            {
                m_var.av.taskInfo.bShow_localVideo = !m_var.av.taskInfo.bShow_localVideo;
            }

            //               
            return;
        }

            //
            public static unsafe int initVideoCapDev(object hTalk, int iWndContentType, string displayName_selected, ref BITMAPINFOHEADER pBih_suggested, CAP_procInfo_bmpCommon pCapBmp)
        {
            if (iWndContentType != Consts.CONST_qyWndContentType_talker) return -1;
            Activity_dlgTalk dlgTalk = (Activity_dlgTalk)hTalk;
            if (!GuiShare.pf_IsWindow(dlgTalk.m_var.m_hTool_dlgTalk_av)) return -1;
            Activity_dlgTalk_av dlgTalk_av = (Activity_dlgTalk_av)dlgTalk.m_var.m_hTool_dlgTalk_av;

            //
            if (dlgTalk_av.m_fg_dlgTalk_av != null)
            {
                return Fragment_dlgTalk_av.initVideoCapDev(hTalk, iWndContentType, displayName_selected, ref pBih_suggested, pCapBmp); 
            }
            if (dlgTalk_av.m_fg_dlgTalk_av2 != null)
            {
                return Fragment_dlgTalk_av2.initVideoCapDev(hTalk, iWndContentType, displayName_selected, ref pBih_suggested, pCapBmp);
            }

            return -1;
        }

        public static unsafe int exitVideoCapDev(object hTalk, int iWndContentType)
        {
            int iErr = -1;

            if (iWndContentType != Consts.CONST_qyWndContentType_talker) return -1;
            Activity_dlgTalk dlgTalk = (Activity_dlgTalk)hTalk;
            if (null == dlgTalk.m_var.m_hTool_dlgTalk_av) return -1;
            Activity_dlgTalk_av dlgTalk_av = (Activity_dlgTalk_av)dlgTalk.m_var.m_hTool_dlgTalk_av;

            //
            if (dlgTalk_av.m_fg_dlgTalk_av != null)
            {
                return Fragment_dlgTalk_av.exitVideoCapDev(hTalk, iWndContentType);
            }
            if (dlgTalk_av.m_fg_dlgTalk_av2 != null)
            {
                return Fragment_dlgTalk_av2.exitVideoCapDev(hTalk, iWndContentType);
            }

            return -1;

        }

        public static unsafe bool bGetCapturePara(object hTalk, int iWndContentType, ref QY_VIDEO_HEADER pVh_org)
        {
            bool bRet = false;

            if (iWndContentType != Consts.CONST_qyWndContentType_talker) return false;
            Activity_dlgTalk dlgTalk = (Activity_dlgTalk)hTalk;
            if (!GuiShare.pf_IsWindow(dlgTalk.m_var.m_hTool_dlgTalk_av)) return false;
            Activity_dlgTalk_av dlgTalk_av = (Activity_dlgTalk_av)dlgTalk.m_var.m_hTool_dlgTalk_av;

            //
            if (dlgTalk_av.m_fg_dlgTalk_av != null)
            {
                return Fragment_dlgTalk_av.bGetCapturePara(hTalk, iWndContentType,ref pVh_org);
            }
            if (dlgTalk_av.m_fg_dlgTalk_av2 != null)
            {
                return Fragment_dlgTalk_av2.bGetCapturePara(hTalk, iWndContentType,ref pVh_org);
            }

            return false;

        }

        public static unsafe int startCapture(object hTalk, int iWndContentType)
        {
            if (iWndContentType != Consts.CONST_qyWndContentType_talker) return -1;
            Activity_dlgTalk dlgTalk = (Activity_dlgTalk)hTalk;
            if (!GuiShare.pf_IsWindow(dlgTalk.m_var.m_hTool_dlgTalk_av)) return -1;
            Activity_dlgTalk_av dlgTalk_av = (Activity_dlgTalk_av)dlgTalk.m_var.m_hTool_dlgTalk_av;

            //
            if (dlgTalk_av.m_fg_dlgTalk_av != null)
            {
                return Fragment_dlgTalk_av.startCapture(hTalk, iWndContentType);
            }
            if (dlgTalk_av.m_fg_dlgTalk_av2 != null)
            {
                return Fragment_dlgTalk_av2.startCapture(hTalk, iWndContentType);
            }

            return 0;
        }

        public static unsafe int stopCapture(object hTalk, int iWndContentType)
        {
            if (iWndContentType != Consts.CONST_qyWndContentType_talker) return -1;
            Activity_dlgTalk dlgTalk = (Activity_dlgTalk)hTalk;
            if (!GuiShare.pf_IsWindow(dlgTalk.m_var.m_hTool_dlgTalk_av)) return -1;
            Activity_dlgTalk_av dlgTalk_av = (Activity_dlgTalk_av)dlgTalk.m_var.m_hTool_dlgTalk_av;

            //
            if (dlgTalk_av.m_fg_dlgTalk_av != null)
            {
                return Fragment_dlgTalk_av.stopCapture(hTalk, iWndContentType);
            }
            if (dlgTalk_av.m_fg_dlgTalk_av2 != null)
            {
                return Fragment_dlgTalk_av2.stopCapture(hTalk, iWndContentType);
            }

            return 0;
        }

        //
        public unsafe int doTask_av(int iCmd, int iTaskId)
        {
            Activity_dlgTalk_av dlgTalk_av = this;
            //
            if (dlgTalk_av.m_fg_dlgTalk_av != null)
            {
                return dlgTalk_av.m_fg_dlgTalk_av.doTask_av(iCmd, iTaskId);
            }
            if (dlgTalk_av.m_fg_dlgTalk_av2 != null)
            {
                return dlgTalk_av.m_fg_dlgTalk_av2.doTask_av(iCmd,iTaskId);
            }

            return -1;
        }

    }
}


