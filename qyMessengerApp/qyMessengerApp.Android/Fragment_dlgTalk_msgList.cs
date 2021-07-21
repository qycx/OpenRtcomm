using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Util;
using Android.Views;
using Android.Widget;
using AndroidX.RecyclerView.Widget;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using qy;
using qy.Droid;
using System.Runtime.InteropServices;


//
namespace qyMessengerApp.Droid
{
    public class Fragment_dlgTalk_msgList : Android.Support.V4.App.Fragment
    {
        RecyclerView mRecyclerView;
        RecyclerView.LayoutManager mLayoutManager;
        Adapter_dlgTalk_msgList mAdapter;
        TextView m_txt_title;
        EditText m_editText_input;
        Button m_button_snd;
        Button m_button_avCall;
        Activity_dlgTalk mhTalk;
        //
        RelativeLayout m_relativeLayout_topMenu;

        //
        public static unsafe int talk_addNewMsg(object hTalkParam, QY_MESSENGER_ID  pIdInfo_from, Int64 tSendTime,uint uiTranNo,ushort usCode, uint uiContentType, string msg, int iTaskId,int iStatus  )
        {
            CCtxQyMc pQyMc = g.g_pQyMc;
            QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;

            if (null == hTalkParam) return -1;
            if (null==msg || msg.Length == 0) return -1;

            //
            Activity_dlgTalk hTalk = (Activity_dlgTalk)hTalkParam;


            //
            TableItem_dlgTalk_msg item = null;
            if (item == null)
            {
                int kk = 0;
                item = new TableItem_dlgTalk_msg();
                item.ui64Id_from = pIdInfo_from.ui64Id;
                //
                QY_MESSENGER_INFO messengerInfo;
                QY_MESSENGER_REGINFO regInfo;
                if (!pDbFuncs.pf_bGetMessengerInfoBySth(pDbFuncs, pQyMc.gui.pDb, pQyMc.cfg.db.iDbType, ref qyFuncs.CONST_fieldIdTable_en, "", &pIdInfo_from,
                    0, &messengerInfo, &regInfo, null, null))
                {
                    goto errLabel;
                }
                {
                    item.dw = new string(regInfo.dw);
                    item.bm = new string(regInfo.bm);
                    item.syr = new string(regInfo.syr);
                }
                //
                item.ImageResourceId = Resource.Drawable.Vegetables;
                //
                QY_MESSENGER_ID idInfo;
                idInfo.ui64Id = pIdInfo_from.ui64Id;
                if (!pDbFuncs.pf_bGetMessengerInfoBySth(pDbFuncs, pQyMc.gui.pDb, pQyMc.cfg.db.iDbType, ref qyFuncs.CONST_fieldIdTable_en, "", &idInfo,
                    0, &messengerInfo, &regInfo, null, null))
                {
                    goto errLabel;
                }
                item.tStartTime = tSendTime;
                item.uiTranNo = uiTranNo;
                item.usCode = usCode;
                item.uiContentType = uiContentType;
                item.msg = (msg);
                item.iTaskId = iTaskId;
                item.iStatus = iStatus;
                //
                hTalk.m_var.m_pProcessQ.Add(item);
                //
                //mTableItems.Sort((x, y) => y.tSendTime.CompareTo(x.tSendTime));
                //
                if (hTalk.mAdapter.mFragment_dlgTalk_msgList1 == null) goto errLabel;
                Fragment_dlgTalk_msgList fg = hTalk.mAdapter.mFragment_dlgTalk_msgList1;
                
                Adapter_dlgTalk_msgList adapter = (Adapter_dlgTalk_msgList)fg.mAdapter;
                if (adapter != null)
                {
                    adapter.NotifyDataSetChanged();
                }

                //
                if (fg.mLayoutManager != null)
                {
                    fg.mLayoutManager.ScrollToPosition(hTalk.m_var.m_pProcessQ.Count - 1);
                }
            }
            errLabel:
                return 0;
            
        }

            //
            public unsafe int gui_procMsg(MIS_MSGU* pMsgU)
        {
            int iErr = -1;
            CCtxQyMc pQyMc = g.g_pQyMc;
            MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;
            QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
            MIS_CNT pMisCnt = pProcInfo.pMisCnt;

            //
            bool bDbg = false;
            string str;

            //
            Activity_dlgTalk hTalk = this.mhTalk;
            DLG_TALK_var m_var = hTalk.get_pm_var();

            //
            switch (pMsgU->uiType)
            {
                /*
                case Consts.CONST_misMsgType_talk:
                    {
                        MIS_MSG_TALK* pMsg = &pMsgU->talk;
                        IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->data.buf;
                        switch (pContent->uiType)
                        {
                            case Consts.CONST_imCommType_htmlContent:
                                {
                                    //mainActivity.mAdapter.myFragment_msg
                                    UInt64 id = pMsg->addr_logicalPeer.idInfo.ui64Id;
                                        //
                                        talk_addNewMsg(this.mhTalk, pMsg->data.route.idInfo_from, pMsg->tStartTime,pMsg->uiTranNo,pMsg->usCode, pContent->uiType, new string(pContent->html.wBuf),pMsg->iTaskId,pMsg->iStatus);
                                    
                                }
                                break;
                        }


                    }
                    break;
                */
                case Consts.CONST_misMsgType_input:
                    {
                        MIS_MSG_INPUT* pMsg = &pMsgU->input;
                        IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->data.buf;
                        switch (pContent->uiType)
                        {
                            /*
                            case Consts.CONST_imCommType_transferAvInfo:
                                {
                                    talk_addNewMsg(this.mhTalk, pMsg->data.route.idInfo_from, pMsg->tStartTime,pMsg->uiTranNo,pMsg->usCode, pContent->uiType, new string("视频呼叫"),pMsg->iTaskId,pMsg->iStatus);

                                }
                                break;
                            case Consts.CONST_imCommType_taskInteractionReq:
                                break;
                            */
                            case Consts.CONST_imCommType_taskProcReq:
                                if (pContent->taskProcReq.usOp == Consts.CONST_imOp_recv_applyForOrgReq)
                                {
                                    using (CQyMalloc malloc_pMsgTask_o = new CQyMalloc()) {;
                                        int size = sizeof(MIS_MSG_TASK);
                                        MIS_MSG_TASK* pMsgTask_o = (MIS_MSG_TASK*)malloc_pMsgTask_o.mallocf(size);
                                        if (null==pMsgTask_o) goto errLabel;
                                        qyFuncs.MACRO_memset_misMsgTask(pMsgTask_o);

                                        if (pMsg->iTaskId == 0) goto errLabel;
                                        int index_taskInfo = qyFuncs.getQmcTaskInfoIndexBySth(mainActivity.var_common.ctxCaller,pProcInfo, pMsg->iTaskId);
                                        if (index_taskInfo < 0) goto errLabel;
                                        QMC_TASK_INFO pTaskInfo = qyFuncs.getQmcTaskInfoByIndex(mainActivity.var_common.ctxCaller,pProcInfo,index_taskInfo,"fg_dlgTalk_msgList.gui_procMsg");
                                        if (pTaskInfo == null) goto errLabel;
                                        QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
                                        if (pTaskData == null) goto errLabel;

                                        //MIS_MSG_TASK* pMsgTask_i = findTaskInProcessQ(&m_var, pMsg->iTaskId);
                                        fixed (MIS_MSG_TASK* pMsgTask_i = &pTaskData.msgU.task) {
                                            if (null==pMsgTask_i) goto errLabel;
                                            if (pMsgTask_i->uiType != Consts.CONST_misMsgType_task) goto errLabel;
                                            //
                                            IM_CONTENTU* pContentTask_i = (IM_CONTENTU*)pMsgTask_i->data.buf;
#if DEBUG
                                            ref IM_CONTENTU tmp_pContentTask_i = ref *pContentTask_i;
#endif
                                            if (pContentTask_i->uiType != Consts.CONST_imCommType_transferAvInfo) goto errLabel;
                                            //
                                            if (true)
                                            {   //  2012/05/25
                                                bool bPermitted = false;
# if  DEBUG
                                                str=string.Format("recvd applyForOrgReq. to check whether the from is a valid user. {0}", pMsg->data.route.idInfo_from.ui64Id);
                                                qyFuncs.traceLog(str);
#endif
                                                /*
                                                if (m_var.addr.uiObjType == Consts.CONST_objType_imGrp)
                                                {
                                                    //  要检查是否是组成员
                                                    bool bVal = false;
                                                    if (!getVal_bImGrpMem(&m_var.addr.idInfo, &pMsg->data.route.idInfo_from, &bVal)
                                                        && bVal)
                                                    {
                                                        bPermitted = true;
                                                    }
                                                }
                                                else
                                                {
                                                    if (pMsg->data.route.idInfo_from.ui64Id == m_var.addr.idInfo.ui64Id)
                                                    {
                                                        bPermitted = true;
                                                    }
                                                }
                                                */
                                                bPermitted = true;
                                                //
                                                if (!bPermitted)
                                                {
# if  DEBUG
                                                    qyFuncs.traceLog(("applyForOrgReq denied. Not a valid user."));
#endif
                                                    goto errLabel;
                                                }
                                            }
                                            //
                                            PARAM_findOrgMsg param;
                                            qyFuncs.mymemset((IntPtr)(byte*)&param, 0, sizeof(PARAM_findOrgMsg));
                                            param.pMsgTask_o = pMsgTask_o;
                                            if (pProcInfo.processQ_media.qTraverse(mainActivity.var_common.ctxCaller,qyFuncs.tmpHandler_findOrgMsgAndProc_is, (IntPtr)pMsgTask_i, (IntPtr)(byte*)&param) <= 0)
                                            {
# if  DEBUG
                                                qyFuncs.traceLogA("dlgTalk_OnQyComm: taskProcReq: applyForOrgReq failed.");
#endif
                                                goto errLabel;
                                            }

                                            if (pMsgTask_o->uiType != Consts.CONST_misMsgType_task)
                                            {
# if  DEBUG
                                                str=string.Format("dlgTalk_OnQyComm: taskProcReq: applyForOrgReq failed. msg.type {0} err", pMsgTask_o->uiType);
                                                qyFuncs.traceLog(str);
#endif
                                                goto errLabel;
                                            }
                                            IM_CONTENTU* pContentTask_o = (IM_CONTENTU*)pMsgTask_o->data.buf;
                                            if (pContentTask_o->uiType != Consts.CONST_imCommType_transferAvInfo) goto errLabel;

# if DEBUG
                                            qyFuncs.traceLogA("dlgTalk_OnQyComm: send transferAvInfo again.");
#endif
                                            //
                                            int lenInBytes = (int)(pMsgTask_o->lenInBytes - (uint)Marshal.OffsetOf<MIS_MSG_routeTalkData>("buf"));
                                            if (lenInBytes < 0) goto errLabel;
                                            //
                                            QY_MESSENGER_ID idInfo_dst;
                                            idInfo_dst.ui64Id = pMsg->data.route.idInfo_from.ui64Id;
                                            //  set idInfo_logicalPeer temporiary.
                                            if (m_var.addr.idInfo.ui64Id != idInfo_dst.ui64Id)
                                            {
                                                pContentTask_o->transferAvInfo.idInfo_logicalPeer.ui64Id = m_var.addr.idInfo.ui64Id;
                                            }
                                            QY_MESSENGER_ID idInfo_logicalPeer=m_var.addr.idInfo;
                                            qyFuncs.postMsgTask2Mgr_mc(mainActivity.var_common.ctxCaller,pMisCnt, Consts.CONST_misMsgType_outputTask, 0, pMsgTask_o->usCode, pMsgTask_o->tStartTime, pMsgTask_o->uiTranNo, 0, pMsgTask_o->iTaskId, pMsgTask_o->uiTaskType, (byte*)pMsgTask_o->data.buf, (uint)lenInBytes, &idInfo_logicalPeer, &pMsgTask_o->idInfo_taskSender, &pMsgTask_o->idInfo_taskReceiver, &idInfo_dst, 0, null, false);
                                            //pContentTask_o->transferAvInfo.idInfo_logicalPeer.ui64Id  =  0;
                                            //
                                            str=string.Format("dlgTalk: send transferAvInfo again to {0}. tn {1}", idInfo_dst.ui64Id, pMsgTask_o->uiTranNo);
                                            qyFuncs.qyShowInfo1(Consts.CONST_qyShowType_qwmComm, null, (""), pProcInfo.str_who_showInfo, null, (""), (""), str);
                                                
                                            //
                                            break;
                                        }
                                    }
                                }
                                //  2014/10/09
                                /*
                                if (pContent->taskProcReq.usOp == CONST_imOp_stopSending
                                    || pContent->taskProcReq.usOp == CONST_imOp_requestToSend)
                                {
                                    if (!m_var.av.taskInfo.bTaskExists) goto errLabel;
                                    if (!m_var.av.ucbGot_iIndex_sharedObj_localAv) goto errLabel;
                                    QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, m_var.av.iIndex_sharedObj_localAv);
                                    if (!pSharedObj) goto errLabel;
                                    if (pSharedObj->bSlave) goto errLabel;
                                    SHARE_dyn_bmp* pDynBmpMem = (SHARE_dyn_bmp*)pSharedObj->master.pShareDynBmp_slave;
                                    if (!pDynBmpMem) goto errLabel;

                                    if (pDynBmpMem->resObj.uiObjType != pContent->taskProcReq.viewDynBmp.uiObjType
                                        || pDynBmpMem->resObj.usIndex_obj != pContent->taskProcReq.viewDynBmp.usIndex_obj)
                                    {
                                        goto errLabel;
                                    }

                                    QY_SHARED_OBJ* pSharedObj_slave = getSharedObjByIndex(pProcInfo, pSharedObj->master.slaveKey.iIndex_sharedObj);
                                    if (!pSharedObj_slave) goto errLabel;
                                    if (!pSharedObj_slave->bUsed) goto errLabel;
                                    if (!pSharedObj_slave->bSlave) goto errLabel;
                                    if (pSharedObj_slave->uiTranNo != pSharedObj->master.slaveKey.uiTranNo) goto errLabel;

                                    if (pContent->taskProcReq.usOp == CONST_imOp_stopSending)
                                    {
                                        removeFromMsgrs_sendLocalAv(pProcInfo, m_var.pMisCnt, &pMsg->data.route.idInfo_from, &pSharedObj_slave->curRoute_sendLocalAv);
                                        qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("dlgTalk_OnQyComm: slave: removeFromMsgrs_sendLocalAv, %I64u"), pMsg->data.route.idInfo_from);
                                    }

                                    break;
                                }
                                */
                                break;
                            case Consts.CONST_imCommType_taskProcResp:
                                if (pContent->taskProcResp.usOp_org == Consts.CONST_imOp_recv_applyForChkTaskAlive)
                                {
                                    /*
                                    Q_NODE* pQNode;
                                    MIS_MSGU* pMsg;

                                    if (!m_var.m_pProcessQ) goto errLabel;

                                    for (pQNode = m_var.m_pProcessQ->front.pNext; pQNode; pQNode = pQNode->pNext)
                                    {
                                        pMsg = (MIS_MSGU*)pQNode->qElemMemory.m_pBuf;
                                        if (pMsg->uiType != CONST_misMsgType_task) continue;
                                        if (pMsg->task.tStartTime == pContent->taskProcResp.tStartTime_org
                                            && pMsg->task.uiTranNo == pContent->taskProcResp.uiTranNo_org)
                                        {
                                            if (bTaskAlive(pContent->taskProcResp.iStatus))
                                            {
                                                //
                                                _sntprintf(tBuf, mycountof(tBuf), _T("resp recvd, task %d is alive"), pMsg->task.iTaskId);
                                                showInfo_open(0, 0, tBuf);
# if DEBUG
                                                traceLog(tBuf);
#endif
                                                //
                                                //  mytime(  &pMsg->task.tStartTime_processed  );
                                                mytime(&pMsg->task.tTime_alive);    //  2014/12/09
                                            }
                                            break;
                                        }
                                    }
                                    */
                                }
                                break;

                                break;
                            default:
                                break;
                        }


                    }
                        break;
                default:
                    break;


            }
            
            PARAM_PROC_ROW ppr=new PARAM_PROC_ROW();

            qyFuncs_Droid.tmpHandler_showMsg(mhTalk, ppr, (IntPtr)pMsgU);


            iErr = 0;

        errLabel:


            return iErr;

        }

        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Create your fragment here
            mhTalk=(Activity_dlgTalk)this.Activity;

            //
            if (mhTalk.m_var != null)
            {
                mhTalk.m_var.m_pProcessQ.Add(new TableItem_dlgTalk_msg() { ui64Id_from = 106, dw = "清扬创新", bm = "技术部", syr = "王五", ImageResourceId = Resource.Drawable.Vegetables, msg = "今天快递了吗" });
                mhTalk.m_var.m_pProcessQ.Add(new TableItem_dlgTalk_msg() { ui64Id_from = 105, dw = "微软", bm = "销售部门", syr = "张三", ImageResourceId = Resource.Drawable.Vegetables, msg = "任务完成了吗？我说，今天任务没完成，我的时间都花在看抖音了。这是不对的。要说了很多话怎么办？你吃饭了吗？吃了是什么呢，吃的是鱼还是肉？" });
            }

        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            // Use this to return your custom view for this Fragment
            // return inflater.Inflate(Resource.Layout.YourFragment, container, false);

            //return base.OnCreateView(inflater, container, savedInstanceState);


            View view = inflater.Inflate(Resource.Layout.layout_dlgTalk_msgList,container,false);

            //

            //
            m_txt_title = view.FindViewById<TextView>(Resource.Id.txt_title);


            //
            mRecyclerView = view.FindViewById<RecyclerView>(Resource.Id.recyclerView);

            //


            //
            mLayoutManager = new LinearLayoutManager(inflater.Context);
            mRecyclerView.SetLayoutManager(mLayoutManager);




            mAdapter = new Adapter_dlgTalk_msgList(this.Activity, mhTalk.m_var.m_pProcessQ);

            //
            //mAdapter.ItemClick += OnItemClick;

            //
            mRecyclerView.SetAdapter(mAdapter);


            //
            m_editText_input = view.FindViewById<EditText>(Resource.Id.editText_input);
            m_button_snd = view.FindViewById<Button>(Resource.Id.button_snd);
            m_button_avCall = view.FindViewById<Button>(Resource.Id.btn_av);

            //
            m_button_snd.Click += M_button_snd_Click;
            m_button_avCall.Click += M_button_avCall_Click;
            

            //
            Activity_dlgTalk hTalk = (Activity_dlgTalk)this.Activity;
            m_txt_title.Text = hTalk.m_str_title;

            //
            m_relativeLayout_topMenu = (RelativeLayout)view.FindViewById(Resource.Id.topMenu);


            //
        errLabel:

            return view;
        }

        //
        public override void OnDestroyView()
        {
            base.OnDestroyView();
        }

        public override void OnDestroy()
        {
            if (this.m_txt_title != null)
            {
                m_txt_title.Dispose();
            }
            if (this.m_editText_input != null)
            {
                this.m_editText_input.Dispose();
            }
            if (this.m_button_snd != null)
            {
                m_button_snd.Dispose();
            }
            if (this.m_button_avCall != null)
            {
                m_button_avCall.Dispose();
            }
            if (mRecyclerView != null)
            {
                mRecyclerView.Dispose();
            }
            if (mLayoutManager != null)
            {
                mLayoutManager.Dispose();
            }
            if (mAdapter != null)
            {
                mAdapter.Dispose();
            }
            if (m_relativeLayout_topMenu != null)
            {
                m_relativeLayout_topMenu.Dispose();
            }

            //
            base.OnDestroy();
            //
            Dispose();
        }


        private void M_button_avCall_Click(object sender, EventArgs e)
        {
            //throw new NotImplementedException();
            Activity_dlgTalk dlgTalk = (Activity_dlgTalk)this.Activity;

            dlgTalk.doTask_startAvCall();

        }

        private unsafe void M_button_snd_Click(object sender, EventArgs e)
        {
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
            MIS_CNT pMisCnt = pProcInfo.pMisCnt;
            MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;

            //
#if DEBUG
            //TopSnackBar snack = TopSnackBar.Make(m_relativeLayout_topMenu, "测试top snackbar", Com.Qycx.Top_snackbar_library.Top_snackbar.BaseTransientBottomBar.LengthLong);
            //snack.Show();
#endif 

            //
            String str = m_editText_input.Text;
            str.Trim();
            if (str.Length == 0) return;
            //
            QY_MESSENGER_ID idInfo_from;
            idInfo_from.ui64Id = pMisCnt.idInfo.ui64Id;
            //
            Int64 tStartTran; uint uiTranNo;
            qyFuncs.MACRO_prepareForTran(out tStartTran, out uiTranNo);

            //
            m_editText_input.Text = "";
            m_editText_input.RequestFocus();

            //
            //  Æä´ÎÔÙ·¢ÍùmgrÊ¹·¢ËÍ
            byte ucFlg;
            IM_HTML_CONTENT content;
            int lenInBytes;
            MIS_MSGU* pMsgBuf = null;
            //
            ucFlg = 0;
            //
            qyFuncs.mymemset((IntPtr)(byte*)&content, 0, sizeof(IM_HTML_CONTENT));
            content.uiType = Consts.CONST_imCommType_htmlContent;
            qyFuncs.mylstrcpyn(content.wBuf, str, Consts.cntof_imHtmlContent_wBuf);
            lenInBytes = (int)Marshal.OffsetOf<IM_HTML_CONTENT>("wBuf") + (qyFuncs.mylstrlen(content.wBuf) + 1) * sizeof(char);
            //
            MSG_ROUTE route;
            qyFuncs.mymemset((IntPtr)(byte*)&route, 0, sizeof(MSG_ROUTE));
            //
            route.idInfo_from.ui64Id = pMisCnt.idInfo.ui64Id;
            //
            route.idInfo_to.ui64Id = mhTalk.m_var.addr.idInfo.ui64Id;
            //route.uiDevType_to = pCurVar->addr.uiDevType;

            //
            QY_MESSENGER_ID talk_idInfo;
            talk_idInfo.ui64Id = mhTalk.m_var.addr.idInfo.ui64Id;


            //
            if (mhTalk.m_var.addr.uiObjType != Consts.CONST_objType_imGrp)
            {

                if (0!=qyFuncs.postMsg2Mgr_mc(mainActivity.var_common.ctxCaller,pMisCnt, &route, Consts.CONST_misMsgType_talk, ucFlg, Consts.CONST_qyCmd_talkTo, tStartTran, uiTranNo, 0, (byte*)&content, (uint)lenInBytes, &talk_idInfo, &talk_idInfo, 0, pMsgBuf, true)) goto errLabel;
            }
            else 
            {
                QY_MESSENGER_ID idInfo_dst;
                //
                idInfo_dst.ui64Id = mhTalk.m_var.addr.idInfo.ui64Id;
                //
                if (idInfo_dst.ui64Id != mhTalk.m_var.addr.idInfo.ui64Id) content.idInfo_logicalPeer.ui64Id = mhTalk.m_var.addr.idInfo.ui64Id;
                //

                if (0!=qyFuncs.postMsg2Mgr_mc(mainActivity.var_common.ctxCaller,pMisCnt, &route, Consts.CONST_misMsgType_talk, ucFlg, Consts.CONST_qyCmd_talkTo, tStartTran, uiTranNo, 0, (byte*)&content, (uint)lenInBytes, &talk_idInfo, &idInfo_dst, 0, pMsgBuf, true)) goto errLabel;

                
            }
            //
            talk_addNewMsg(this.mhTalk, idInfo_from, tStartTran, uiTranNo, Consts.CONST_qyCmd_talkTo, content.uiType, str,0,0);


        errLabel:
            return;



        }
    }
}