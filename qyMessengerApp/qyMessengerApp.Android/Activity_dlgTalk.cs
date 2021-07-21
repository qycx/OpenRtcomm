using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Support.V4.View;
using Android.Support.V7.App;
using Android.Views;
using Android.Widget;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using qy;
using qy.Droid;
using Java.Lang;

//
namespace qyMessengerApp.Droid
{
    [Activity(Label = "Activity_dlgTalk")]
    public class Activity_dlgTalk : qmcBaseActivity, View.IOnClickListener, ViewPager.IOnPageChangeListener
    {
        //
        public DLG_TALK_var m_var;

        //
        private TextView txt_msg;
        private TextView txt_detail;

        private ViewPager vPager;

        public FragmentPagerAdapter_dlgTalk mAdapter;

        public const int PAGE_ONE = 0;
        public const int PAGE_TWO = 1;

        public string m_str_title;

        //
        public MyHandler mHandler = null;



        //
        public static DLG_TALK_var tmp_getDlgTalkVar(object hDlgTalk)
        {

            if (!GuiShare.pf_IsWindow(hDlgTalk)) return null;
            Activity_dlgTalk pDlgTalk = (Activity_dlgTalk)(hDlgTalk);
            if (null == pDlgTalk) return null;

            //return  &(  (  CDlgTalk  *  )pDlgTalk  )->m_var;
            return (pDlgTalk).get_pm_var();
        }

        public DLG_TALK_var get_pm_var()
        {
            return m_var;
        }



        public class MyHandler : Handler
        {
            Activity_dlgTalk m_hDlgTalk = null;
            public MyHandler(Activity_dlgTalk hDlgTalk)
            {
                m_hDlgTalk = hDlgTalk;
            }

            public override void HandleMessage(Message msg)
            {
                CCtxQyMc pQyMc = g.g_pQyMc;
                if (pQyMc == null) return;

                string str;

                //
                switch (msg.What)
                {
                    case Consts.CONST_qyWm_postComm:

                        //
                        switch (msg.Arg1)
                        {
                            case Consts.CONST_qyWmParam_doTask:
                                m_hDlgTalk.doTask_av_accept();
                                break;
                            case Consts.CONST_qyWmParam_chkTalkDraw:
                                {
                                    qyFuncs.traceLog("dlgTalk.get a msg chkTalkDraw");
                                    //
                                    m_hDlgTalk.doChkTalkDraw();
                                }
                                break;
                            case Consts.CONST_qyWmParam_closeWnd:
                                {
                                    str = string.Format("dlgTalk.closeWnd starts");
                                    qyFuncs.showInfo_open(0, null, str);
                                    //
                                    m_hDlgTalk.doFinish("closeWnd");
                                    //
                                    str = string.Format("dlgTalk.closeWnd ends");
                                    qyFuncs.showInfo_open(0, null, str);
                                }
                                break;
                            case Consts.CONST_qyWmParam_msgArrive:
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }

            }

        };

        //
        public int gui_PostMessage(int msgId, int wParam, int lParam)
        {
            CCtxQyMc pQyMc = g.g_pQyMc;


            {
                Message msg = this.mHandler.ObtainMessage();
                msg.What = msgId;
                msg.Arg1 = wParam;
                msg.Arg2 = lParam;
                this.mHandler.SendMessage(msg);
                return 0;
            }


            return 0;
        }




        //
        public unsafe int gui_procMsg(IntPtr pMsgParam)
        {
            int iErr = -1;
            MIS_MSGU* pMsg = (MIS_MSGU*)pMsgParam;
            CCtxQyMc pQyMc = g.g_pQyMc;
            MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;

            /*
            switch (pMsg->uiType)
            {
                case Consts.CONST_misMsgType_talk:
                    {
                        IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->talk.data.buf;
                        switch (pContent->uiType)
                        {
                            case Consts.CONST_imCommType_htmlContent:
                                {
                                    
                                }
                                break;
                        }


                    }
                    break;
                default:
                    break;


            }
            */


            //
            if (mAdapter.mFragment_dlgTalk_msgList1 != null)
            {
                mAdapter.mFragment_dlgTalk_msgList1.gui_procMsg(pMsg);
            }




            return iErr;

        }

        int startActivity_dlgTalk_av(int iCmd, int index_taskInfo)
        {
            int iErr = -1;
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
            MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;

            //
            if (this.m_var.m_hTool_dlgTalk_av != null) return -1;

            //
            Context context = this;
            Intent intent = new Intent(context, typeof(Activity_dlgTalk_av));
            //
            intent.PutExtra("iCmd", iCmd);
            intent.PutExtra("ui64Id", (long)m_var.addr.idInfo.ui64Id);
            //
            intent.PutExtra("index_qmcTaskInfo", index_taskInfo);
            //
            StartActivity(intent);

            iErr = 0;
        errLabel:

            return iErr;
        }

        //
        public unsafe int doTask_av_accept()
        {
            int iErr = -1;
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
            MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;


            //
            if (!(mainActivity.var_common.notifyTaskStatus.bExists_task && mainActivity.var_common.notifyTaskStatus.bAvCall))
            {
                qyFuncs.showNotification_open(0, 0, 0, "Can't start a avTask, no task needs be accepted.");
                goto errLabel;
            }


            QMC_TASK_INFO pTaskInfo = pProcInfo.getQmcTaskInfoByIndex(mainActivity.var_common.ctxCaller, mainActivity.var_common.notifyTaskStatus.index_taskInfo, "doTask_av_accept");
            if (pTaskInfo == null) goto errLabel;
            QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
            if (pTaskData == null) goto errLabel;

            //            
            if (pTaskData.msgU.uiType != Consts.CONST_misMsgType_task)
            {
                goto errLabel;
            }
            if (pTaskData.msgU.task.addr_logicalPeer.idInfo.ui64Id != this.m_var.addr.idInfo.ui64Id)
            {
                qyFuncs.showNotification_open(0, 0, 0, "Can't start a avTask, because logicalPeer != talker.");
                goto errLabel;

            }


            //
            if (true)
            {
                /*
                CHelp_getDlgTalkVar help_getDlgTalkVar;
                DLG_TALK_var* pm_var = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hWnd_task);
                if (!pm_var) goto errLabel;
                DLG_TALK_var & m_var = *pm_var;
                */

                //
                object hWnd_task = this;
                fixed (MIS_MSG_TASK* pMsg = &pTaskData.msgU.task)
                {

                    //if (uiTaskType != Consts.CONST_imTaskType_viewDynBmp)
                    {   //  2014/09/26

                        //
                        if (0 != GuiShare.pf_dlgTalk_qPostMsg(hWnd_task, (IntPtr)pMsg, (uint)System.Runtime.InteropServices.Marshal.OffsetOf<MIS_MSG_TASK>("data") + pMsg->lenInBytes)) goto errLabel;

                        /*
                        //  2016/02/27
                        PARAM_PROC_ROW param;
                        memset(&param, 0, sizeof(param));
                        param.bScrollIntoView = true;
                        if (dyn_tmpHandler_showMsg(hWnd_task, &param, pMsg)) goto errLabel;
                        */
                    }
                }
            }


            //
            //mainActivity.var_common.processingAvTask
            startActivity_dlgTalk_av(tmpResource.IDC_BUTTON_av_accept, mainActivity.var_common.notifyTaskStatus.index_taskInfo);



            iErr = 0;
        errLabel:

            return iErr;
        }


        //
        public unsafe int doChkTalkDraw()
        {
            int iErr = -1;
            bool bDbg = false;
            string str;

            //
#if DEBUG
            bDbg = true;
#endif

            //
            if (bDbg)
            {
                str = string.Format("dlgTalk.doChkTalkDraw enters");
                qyFuncs.showInfo_open(0, null, str);
            }

            //
            int i;
            int cnt = 0;
            for (i = 0; i < m_var.tmp_hTools_dlgTalk_av.Length; i++)
            {
                if (m_var.tmp_hTools_dlgTalk_av[i] != null)
                {
                    cnt++;
                }
            }
            if (cnt == 0)
            {
                m_var.m_hTool_dlgTalk_av = null;
                m_var.m_share_eglContext = null;
                iErr = 0; goto errLabel;
            }
            //
            if (cnt == 1)
            {
                for (i = 0; i < m_var.tmp_hTools_dlgTalk_av.Length; i++)
                {
                    if (m_var.tmp_hTools_dlgTalk_av[i] != null
                        && m_var.tmp_share_eglContexts[i] != null)
                    {
                        m_var.m_hTool_dlgTalk_av = m_var.tmp_hTools_dlgTalk_av[i];
                        m_var.m_share_eglContext = m_var.tmp_share_eglContexts[i];
                        //
                        Activity_dlgTalk_av hTalk_av = (Activity_dlgTalk_av)m_var.m_hTool_dlgTalk_av;
                        if (hTalk_av.m_fg_dlgTalk_av2 != null)
                        {
                            hTalk_av.m_fg_dlgTalk_av2.waitTextureViewAvailable(null, null, null);
                        }
                        //
                        break;
                    }
                }
                iErr = 0; goto errLabel;
            }


            //
            iErr = 0;
        errLabel:

            //
            if (bDbg)
            {
                str = string.Format("dlgTalk.doChkTalkDraw leaves");
                qyFuncs.showInfo_open(0, null, str);
            }


            return iErr;

        }


        //
        public int doTask_startAvCall()
        {
            int iErr = -1;
            //
            startActivity_dlgTalk_av(tmpResource.IDC_BUTTON_av, -1);

            iErr = 0;

        errLabel:

            return iErr;

        }



        //
        public unsafe int gui_onTimer(object p0, object p1, object p2)
        {
            m_var.loopCtrl_timer++;


            if (m_var.m_hTool_dlgTalk_av != null)
            {
                Activity_dlgTalk_av dlgTalk_av = (Activity_dlgTalk_av)m_var.m_hTool_dlgTalk_av;
                dlgTalk_av.gui_onTimer(p0, p1, p2);
            }

            //
            qyFuncs_Droid.dlgTalk_myTimerProc(this, 0, 0, 0);


            //
            return 0;
        }

        //
        public static unsafe int talk_updatePlayerInfo(object hTalk, IntPtr pMIS_MSG_applyForPlayer_qmc, PLAYER_ID playerId)
        {
            int iErr = -1;
            Activity_dlgTalk dlgTalk = (Activity_dlgTalk)hTalk;
            MIS_MSG_applyForPlayer_qmc* pMsg = (MIS_MSG_applyForPlayer_qmc*)pMIS_MSG_applyForPlayer_qmc;

            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
            MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;


            DLG_TALK_var m_var = dlgTalk.m_var;
            bool bChanged = false;

            if (!m_var.av.taskInfo.bTaskExists) goto errLabel;
            if (pMsg->iTaskId != m_var.av.taskInfo.iTaskId) goto errLabel;

            //
            int index_taskInfo = m_var.av.taskInfo.iIndex_taskInfo;
            QMC_TASK_INFO pTaskInfo = qyFuncs.getQmcTaskInfoByIndex(mainActivity.var_common.ctxCaller, pProcInfo, index_taskInfo, "do_closeTask");
            if (pTaskInfo == null) goto errLabel;
            QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
            if (pTaskData == null) goto errLabel;
            QMC_taskData_conf pTc = (QMC_taskData_conf)pTaskData;
            DLG_TALK_videoConference videoConference = pTc.getVideoConference();

            //
            DLG_TALK_videoConferenceActiveMemFrom pActiveMem = null;
            int i;

            //
#if DEBUG
            ref MIS_MSG_applyForPlayer_qmc tmp_pMsg = ref *pMsg;
#endif


            //
            if (pMsg->idInfo_recorder.ui64Id != 0)
            {
                for (i = 0; i < videoConference.usCntLimit_activeMems_from; i++)
                {
                    pActiveMem = videoConference.activeMems_from[i];
                    if (pActiveMem.avStream.idInfo.ui64Id == pMsg->idInfo_recorder.ui64Id
                        && pActiveMem.avStream.obj.tranInfo.video.uiTranNo_openAvDev == pMsg->video.uiTranNo)
                    {
                        break;
                    }
                }
                if (i == videoConference.usCntLimit_activeMems_from) goto errLabel;
                //
                if (m_var.av.taskInfo.ucbVideoConference)
                {
                    if (0 == pActiveMem.avStream.obj.resObj.uiObjType) goto errLabel;
                }
            }

            //
            if (pMsg->idInfo_recorder.ui64Id == 0)
            {
                if (m_var.m_drawLayout.param.me.param.playerId.index_player != playerId.index_player
                    || m_var.m_drawLayout.param.me.param.playerId.uiTranNo_player != playerId.uiTranNo_player)
                {
                    m_var.m_drawLayout.param.me.param.playerId = playerId;
                    m_var.m_drawLayout.param.me.tn_modified = qyFuncs.getuiNextTranNo(null, 0, null);
                    bChanged = true;
                }
            }
            else
            {
                if (m_var.m_drawLayout.param.peer.param.playerId.index_player != playerId.index_player
                    || m_var.m_drawLayout.param.peer.param.playerId.uiTranNo_player != playerId.uiTranNo_player)
                {
                    QY_PLAYER pPlayer = qyFuncs.getPlayerByIndex(pProcInfo, playerId.index_player);
                    //
                    m_var.m_drawLayout.param.peer.param.playerId = playerId;
                    m_var.m_drawLayout.param.peer.tn_modified = qyFuncs.getuiNextTranNo(null, 0, null);
                    bChanged = true;
                }
            }


            iErr = 0;
        errLabel:

            if (iErr == 0)
            {
                if (bChanged)
                {
                    m_var.m_drawLayout.tn_modified = qyFuncs.getuiNextTranNo(null, 0, null);
                }
            }

            return iErr;
        }

        //
        public unsafe int do_closeTask(int index_taskInfo)
        {
            int iErr = -1;
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            //
            MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;

            //
            string str;

            //
            str = string.Format("dlgTalk.do_closeTask enters");
            qyFuncs.showInfo_open(0, null, str);

            //
            QMC_TASK_INFO pTaskInfo = qyFuncs.getQmcTaskInfoByIndex(mainActivity.var_common.ctxCaller, pProcInfo, index_taskInfo, "do_closeTask");
            if (pTaskInfo == null) return -1;

            if (m_var.av.taskInfo.bTaskExists
                && m_var.av.taskInfo.iIndex_taskInfo == index_taskInfo)
            {
                //
#if false
                qyFuncs_Droid.dlgTalk_closeTaskAv(this, m_var,"dlgTalk.do_closeTask");
                //
                if (m_var.m_hTool_dlgTalk_av != null)
                {
                    Activity_dlgTalk_av dlgTalk_av = (Activity_dlgTalk_av)m_var.m_hTool_dlgTalk_av;
                    dlgTalk_av.doFinish("dlgTalk.do_closeTask");
                }
#endif
                //
                if (m_var.m_hTool_dlgTalk_av != null)
                {
                    //
                    str = string.Format("trigger to close taskAv");
                    qyFuncs.showInfo_open(0, null, str);

                    //
                    GuiShare.pf_PostMessage_new(m_var.m_hTool_dlgTalk_av, Consts.CONST_qyWndContentType_dlgTalk_av, Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_closeWnd, 0);
                }

                //
                iErr = 0; goto errLabel;
            }

            //            
            qyFuncs_Droid.mainWnd_do_closeTask(index_taskInfo);


            //
            iErr = 0;
        errLabel:

            //
            str = string.Format("dlgTalk.do_closeTask leaves");
            qyFuncs.showInfo_open(0, null, str);

            return iErr;
        }


        //
        protected override unsafe void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Create your application here
            int iErr = -1;
            string str;

            //
            this.mTag = "dlgTalk";

            //
            Intent intent = this.Intent;
            UInt64 ui64Id = (UInt64)intent.GetLongExtra("ui64Id", 0);
            int wParam = (int)intent.GetIntExtra("wParam", 0);
            int lParam = (int)intent.GetIntExtra("lParam", 0);
            //
            Console.WriteLine("ui64Id {0}", ui64Id);

            //
            mHandler = new MyHandler(this);

            //


            //
            if (m_var != null)
            {
                int ii = 0;
            }
            m_var = new DLG_TALK_var();

            //
            m_var.m_pProcessQ = new List<TableItem_dlgTalk_msg>();



            //        
            m_var.addr.idInfo.ui64Id = ui64Id;

            //
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
            MIS_CNT pMisCnt = pProcInfo.pMisCnt;
            //
            MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;


            //
            if (m_var.addr.idInfo.ui64Id == pMisCnt.idInfo.ui64Id)
            {
                str = string.Format("talker{0} can't talk to myself", m_var.addr.idInfo.ui64Id);
                qyFuncs.showInfo_open(0, null, str);
                qyFuncs.showNotification_open(0, 0, 0, str);
                goto errLabel;
            }


            //
            switch (wParam)
            {
                case Consts.CONST_qyWmParam_doTask:
                    m_var.bActivityStarted_toDoTask = true;
                    m_var.toDoTask_usOp = (ushort)lParam;
                    break;
                default:
                    break;
            }

            //
            //

            //
            SetContentView(Resource.Layout.layout_dlgTalk);


            //

            //
            mAdapter = new FragmentPagerAdapter_dlgTalk(SupportFragmentManager);



            bindViews();


            //
            QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;
            QY_MESSENGER_ID idInfo = m_var.addr.idInfo;



            QY_MESSENGER_INFO msgrInfo;
            QY_MESSENGER_REGINFO regInfo;
            if (!pDbFuncs.pf_bGetMessengerInfoBySth(pDbFuncs, pQyMc.gui.pDb, pQyMc.cfg.db.iDbType, ref qyFuncs.CONST_fieldIdTable_en,
                "", &idInfo, 0, &msgrInfo, &regInfo, null, null))
            {
                str = string.Format("dlgTalk.OnCreate failed, bGetMessengerInfoBySth failed, {0}", idInfo.ui64Id);
                qyFuncs.traceLog(str);
                qyFuncs.showInfo_open(0, null, str);
                //
                goto errLabel;
            }

            //
            m_var.addr.uiObjType = msgrInfo.uiType;

            //
            if (m_var.addr.uiObjType == Consts.CONST_objType_imGrp)
            {
                IM_GRP_INFO grpInfo;
                if (!pDbFuncs.pf_bGetImGrpInfoBySth(pQyMc.gui.pDb, pQyMc.cfg.db.iDbType, "", &idInfo, &grpInfo))
                {
                    qyFuncs.mymemset((IntPtr)(byte*)&grpInfo, 0, sizeof(IM_GRP_INFO));
                }
                m_str_title = new string(grpInfo.name);
            }
            else
            {
                str = string.Format("{0}", new string(regInfo.syr));
                m_str_title = str;
            }

            //
            qyFuncs_Droid.dlgTalk_OnInitDialog(this, ref m_var);
            //
            setTimer(1000, gui_onTimer);

            //
            if (m_var.bActivityStarted_toDoTask)
            {
                doTask_av_accept();
            }


            //
            iErr = 0;
        errLabel:
            if (iErr != 0)
            {
                doFinish("dlgTalk.OnCreate failed");
            }
            return;
        }

        protected override void OnResume()
        {
            base.OnResume();
            //
            qyFuncs.traceLog("dlgTalk: onResume");

            //
            CCtxQyMc pQyMc = g.g_pQyMc;

            //
            pQyMc.gui.hLastActiveTalk = this;

            //
            pQyMc.gui.hActiveWnd = this;

            //
            GuiShare.pf_gui_notify_chk();
        }


        protected override void OnPause()
        {
            base.OnPause();
            //
            string str;

            //
            qyFuncs.traceLog("dlgTalk: onPause");

            //
            CCtxQyMc pQyMc = g.g_pQyMc;
            if (pQyMc.gui.hActiveWnd == this)
            {
                pQyMc.gui.hActiveWnd = null;
            }

            if (IsFinishing)
            {
                //
                str = string.Format("dlgTalk.OnPause,IsFinishing");
                if (m_var != null) str = string.Format("dlgTalk{0}.OnPause,IsFinishing", m_var.addr.idInfo.ui64Id);
                str += " enters";
                qyFuncs.showInfo_open(0, null, str);

                //
                killTimer();

                //
                qyFuncs_Droid.dlgTalk_OnDestroy(this, ref m_var);

                //
                qyFuncs.showInfo_open(0, null, "dlgTalk.OnPause leaves,IsFinishing");
            }

        }

        public override void OnBackPressed()
        {
            Console.WriteLine("dlgTalk.OnBackPressed enters");

            //base.OnBackPressed();
            GuiShare.pf_PostMessage_new(this, Consts.CONST_qyWndContentType_talker, Consts.CONST_qyWm_postComm, Consts.CONST_qyWmParam_closeWnd, 0);

            Console.WriteLine("dlgTalk.OnBackPressed leave");
        }

        //



        private void bindViews()
        {
            txt_msg = (TextView)FindViewById(Resource.Id.txt_msg);
            txt_detail = (TextView)FindViewById(Resource.Id.txt_detail);

            txt_msg.SetOnClickListener(this);
            txt_detail.SetOnClickListener(this);

            vPager = (ViewPager)FindViewById(Resource.Id.vpager);

            //
            vPager.Adapter = mAdapter;

            //vPager.SetCurrentItem(0,true);
            vPager.AddOnPageChangeListener(this);
            //
            txt_msg.PerformClick();
        }

        private void clearSelected()
        {
            txt_msg.Selected = false;
            txt_detail.Selected = false;

        }

        public void OnClick(View v)
        {
            switch (v.Id)
            {
                case Resource.Id.txt_msg:
                    clearSelected();
                    txt_msg.Selected = true;
                    vPager.SetCurrentItem(PAGE_ONE, false);
                    break;
                case Resource.Id.txt_detail:
                    clearSelected();
                    txt_detail.Selected = true;
                    vPager.SetCurrentItem(PAGE_TWO, false);
                    break;
                default:
                    break;
            }
        }

        protected override void OnDestroy()
        {
            int i = 1;

            string str = "dlgTalk.OnDestroy";
            if (m_var != null)
            {
                str = string.Format("dlgTalk.OnDestroy {0}", m_var.addr.idInfo.ui64Id);
            }
            qyFuncs.showInfo_open(0, null, str + "enters");


            if (this.txt_msg != null)
            {
                this.txt_msg.Dispose();
            }
            if (this.txt_detail != null) {
                txt_detail.Dispose();
            }

            if (this.vPager != null)
            {
                vPager.Adapter = null;
                vPager.Dispose();
            }
            if (this.mAdapter != null)
            {
                this.mAdapter.Dispose();
            }


            //
            base.OnDestroy();
            Dispose();

            //
            qyFuncs_Droid.doGC("dlgTalk.OnDestroy");

            //
            qyFuncs.showInfo_open(0, null, str + "leaves");

        }


        void ViewPager.IOnPageChangeListener.OnPageScrollStateChanged(int state)
        {
            //throw new NotImplementedException();
            if (state == 2)
            {
                switch (vPager.CurrentItem)
                {
                    case PAGE_ONE:
                        clearSelected();
                        txt_msg.Selected = true;
                        break;
                    case PAGE_TWO:
                        clearSelected();
                        txt_detail.Selected = true;
                        break;
                }


            }

        }

        void ViewPager.IOnPageChangeListener.OnPageScrolled(int position, float positionOffset, int positionOffsetPixels)
        {
            //throw new NotImplementedException();
        }

        void ViewPager.IOnPageChangeListener.OnPageSelected(int position)
        {
            //throw new NotImplementedException();
        }
    }
}