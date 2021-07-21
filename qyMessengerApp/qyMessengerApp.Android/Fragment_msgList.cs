using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Util;
using Android.Views;
using Android.Widget;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using qy;
using qy.Droid;

//
namespace qyMessengerApp.Droid
{
    public class Fragment_msgList : Android.Support.V4.App.Fragment
    {
        List<TableItem_msg> mTableItems = new List<TableItem_msg>();
        ListView listView;

        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Create your fragment here

            /*
     tableItems.Add(new TableItem() { Heading = "Vegetables", SubHeading = "65 items", ImageResourceId = Resource.Drawable.Vegetables });
     tableItems.Add(new TableItem() { Heading = "Fruits", SubHeading = "17 items", ImageResourceId = Resource.Drawable.Vegetables });
     tableItems.Add(new TableItem() { Heading = "Flower Buds", SubHeading = "5 items", ImageResourceId = Resource.Drawable.Vegetables });
     tableItems.Add(new TableItem() { Heading = "Legumes", SubHeading = "33 items", ImageResourceId = Resource.Drawable.Vegetables });
     tableItems.Add(new TableItem() { Heading = "Bulbs", SubHeading = "18 items", ImageResourceId = Resource.Drawable.Vegetables });
     tableItems.Add(new TableItem() { Heading = "Tubers", SubHeading = "43 items", ImageResourceId = Resource.Drawable.Vegetables });
     */
            mTableItems.Add(new TableItem_msg() { ui64Id=108,dw = "清扬创新", syr = "user9", ImageResourceId = Resource.Drawable.Vegetables, speaker = "张三", msg = "今天快递了吗" });
            mTableItems.Add(new TableItem_msg() { ui64Id = 107, dw = "清扬创新", syr = "user8", ImageResourceId = Resource.Drawable.Vegetables, speaker = "王五", msg = "今天跑步了吗" });
            mTableItems.Add(new TableItem_msg() { ui64Id=111,uiObjType = Consts.CONST_objType_imGrp, grpName = "userGrp", ImageResourceId = Resource.Drawable.Vegetables, speaker = "李四", msg = "任务完成了吗" });



        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            // Use this to return your custom view for this Fragment
            // return inflater.Inflate(Resource.Layout.YourFragment, container, false);

            //return base.OnCreateView(inflater, container, savedInstanceState);

            //
            View view = inflater.Inflate(Resource.Layout.layout_msgList, container, false);

            //
            listView = (ListView)view.FindViewById(Resource.Id.list);

            //
            listView.Adapter = new Adapter_msgList(inflater, mTableItems);

            //
            listView.ItemClick += ListView_ItemClick; ;

            return view;

        }


        //
        public static unsafe int TableItem_msg_new_fillInfo( QY_MESSENGER_ID addr_logicalPeer_idInfo, QY_MESSENGER_ID idInfo_from, ref TableItem_msg item )
        {
            int iErr = -1;
            CCtxQyMc pQyMc = g.g_pQyMc;
            QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;

            //
            item.ui64Id = addr_logicalPeer_idInfo.ui64Id;
            //
            QY_MESSENGER_INFO messengerInfo;
            QY_MESSENGER_REGINFO regInfo;
            if (!pDbFuncs.pf_bGetMessengerInfoBySth(pDbFuncs, pQyMc.gui.pDb, pQyMc.cfg.db.iDbType, ref qyFuncs.CONST_fieldIdTable_en, "", &addr_logicalPeer_idInfo,
                0, &messengerInfo, &regInfo, null, null))
            {
                goto errLabel;
            }
            item.uiObjType = messengerInfo.uiType;
            if (messengerInfo.uiType == Consts.CONST_objType_imGrp)
            {
                IM_GRP_INFO grpInfo;
                if (!pDbFuncs.pf_bGetImGrpInfoBySth(pQyMc.gui.pDb, pQyMc.cfg.db.iDbType, "", &addr_logicalPeer_idInfo, &grpInfo))
                {
                    qyFuncs.mymemset((IntPtr)(byte*)&grpInfo, 0, sizeof(IM_GRP_INFO));
                }
                item.grpName = new string(grpInfo.name);
            }
            else
            {
                item.dw = new string(regInfo.dw);
                item.bm = new string(regInfo.bm);
                item.syr = new string(regInfo.syr);
            }
            //
            item.ImageResourceId = Resource.Drawable.Vegetables;
            //
            QY_MESSENGER_ID idInfo;
            idInfo.ui64Id = idInfo_from.ui64Id;
            if (!pDbFuncs.pf_bGetMessengerInfoBySth(pDbFuncs, pQyMc.gui.pDb, pQyMc.cfg.db.iDbType, ref qyFuncs.CONST_fieldIdTable_en, "", &idInfo,
                0, &messengerInfo, &regInfo, null, null))
            {
                goto errLabel;
            }
            item.speaker = new string(regInfo.syr);




            iErr = 0;
            
        errLabel:

            return iErr;
        }

        public static unsafe string get_syr_by_idInfo(QY_MESSENGER_ID idInfo)
        {
            string str = "";
            CCtxQyMc pQyMc = g.g_pQyMc;
            QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;

            QY_MESSENGER_INFO messengerInfo;
            QY_MESSENGER_REGINFO regInfo;
            //QY_MESSENGER_ID idInfo;
            //idInfo.ui64Id = pMsg->data.route.idInfo_from.ui64Id;
            if (!pDbFuncs.pf_bGetMessengerInfoBySth(pDbFuncs, pQyMc.gui.pDb, pQyMc.cfg.db.iDbType, ref qyFuncs.CONST_fieldIdTable_en, "", &idInfo,
                0, &messengerInfo, &regInfo, null, null))
            {
                goto errLabel;
            }

            str = new string(regInfo.syr);

        errLabel:
            return str;
        }

        //
        public unsafe int gui_procMsg(MIS_MSGU* pMsgU)
        {
            int iErr = -1;
            CCtxQyMc pQyMc = g.g_pQyMc;
            MainActivity mainActivity = (MainActivity)pQyMc.gui.hMainWnd;
            QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;

            //
            QY_MESSENGER_ID addr_logicalPeer_idInfo;    addr_logicalPeer_idInfo.ui64Id=0;
            QY_MESSENGER_ID idInfo_from;                idInfo_from.ui64Id=  0 ;
            string msg = "";
            Int64 tRecvTime=0;
            string str;


            //
            str = string.Format("fg_msglist.gui_procMsg enters");
            qyFuncs.showInfo_open(0, null, str);

            //
            switch (pMsgU->uiType)
            {
                case Consts.CONST_misMsgType_talk:
                    {
                        MIS_MSG_TALK* pMsg = &pMsgU->talk;
                        IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->data.buf;
                        //
                        addr_logicalPeer_idInfo = pMsg->addr_logicalPeer.idInfo;
                        idInfo_from = pMsg->data.route.idInfo_from;
                        tRecvTime = pMsg->tRecvTime;
                        //
                        switch (pContent->uiType)
                        {
                            case Consts.CONST_imCommType_htmlContent:
                                {
                                    msg = new string(pContent->html.wBuf);
                                }
                                break;
                        }


                    }
                    break;
                case Consts.CONST_misMsgType_input:
                    {
                        MIS_MSG_INPUT* pMsg = &pMsgU->input;
                        IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->data.buf;
                        //
                        addr_logicalPeer_idInfo = pMsg->addr_logicalPeer.idInfo;
                        idInfo_from = pMsg->data.route.idInfo_from;
                        tRecvTime = pMsg->tRecvTime;
                        //
                        switch (pContent->uiType)
                        {
                            case Consts.CONST_imCommType_transferAvInfo:
                                {
                                    msg = new string("视频呼叫");
                                }
                                break;
                        }

                    }
                    break;
                default:
                    goto errLabel;
                    break;


            }

            //
            str = string.Format("fg_msgList.gui_procMsg, recvd {0}", msg);
            qyFuncs.showInfo_open(0,null,str);
            //
            TableItem_msg item = this.mTableItems.Find(x => x.ui64Id == addr_logicalPeer_idInfo.ui64Id);
            if (item == null)
            {
                int kk = 0;
                item = new TableItem_msg();
                //
                TableItem_msg_new_fillInfo(addr_logicalPeer_idInfo, idInfo_from, ref item);
                //
                item.msg = msg;// new string(pContent->html.wBuf);
                item.tRecvTime = tRecvTime;
                //
                mTableItems.Add(item);
                //
                mTableItems.Sort((x, y) => y.tRecvTime.CompareTo(x.tRecvTime));
                //
                Adapter_msgList adapter = (Adapter_msgList)listView.Adapter;
                adapter.NotifyDataSetChanged();


            }
            else
            {
                item.speaker = get_syr_by_idInfo(idInfo_from);
                item.msg = msg;// new string(pContent->html.wBuf);
                item.tRecvTime = tRecvTime;
                //
                //
                mTableItems.Sort((x, y) => y.tRecvTime.CompareTo(x.tRecvTime));
                //
                Adapter_msgList adapter = (Adapter_msgList)listView.Adapter;
                adapter.NotifyDataSetChanged();
                //
                int kk = 0;
            }



            iErr = 0;
            
        errLabel:


            //
            str = string.Format("fg_msglist.gui_procMsg leaves, iErr {0}",iErr);
            qyFuncs.showInfo_open(0, null, str);

            //
            return iErr;

        }


        //
        private unsafe void ListView_ItemClick(object sender, AdapterView.ItemClickEventArgs e)
        {
            //throw new NotImplementedException();
            Console.WriteLine("{0} clicked", mTableItems[e.Position].ui64Id);
            //
            TableItem_msg item_sel = mTableItems[e.Position];

            //
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
            MIS_CNT pMisCnt = pProcInfo.pMisCnt;

            //
            qyFuncs.traceLog("这里应该提示一下，如果有视频任务在进行，就不能激活新窗口");

            //
            QY_MESSENGER_ID idInfo;idInfo.ui64Id = item_sel.ui64Id;

            //
            MSGR_ADDR addr;
            addr.idInfo.ui64Id = item_sel.ui64Id;
            PARAM_talkToMessenger param = new PARAM_talkToMessenger();

            qyFuncs_Droid.talkToMessenger(pQyMc, &addr, false, true, ref param);

        }

    }
}


