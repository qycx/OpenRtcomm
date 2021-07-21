using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Util;
using Android.Views;
using Android.Widget;
using qy;
using qy.Droid;

namespace qyMessengerApp.Droid
{
    public class Fragment_me : Android.Support.V4.App.Fragment
    {
        bool m_bInited;
        //
        TextView tv_staticUsrName;
        TextView tv_dwmc;
        TextView tv_usrName;
        TextView tv_idInfo;
        TextView tv_staticIo;
        TextView tv_io;
        TextView tv_staticServer;
        TextView tv_server;
        //
        TextView tv_staticStatusServer;
        EditText edt_statusServer;
        Button btn_apply;
        TextView tv_statusQInfo;
        TextView tv_ver;
        TextView tv_staticSupport;
        TextView tv_support;

        //
        bool m_bUpdated_afterLogon;

        //
        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Create your fragment here
        }

        public override unsafe View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            // Use this to return your custom view for this Fragment
            // return inflater.Inflate(Resource.Layout.YourFragment, container, false);

            //return base.OnCreateView(inflater, container, savedInstanceState);

            //
            View view = inflater.Inflate(Resource.Layout.layout_fg_me, container, false);

            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
            QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;

            string str;

            //
            tv_staticUsrName = (TextView)view.FindViewById(Resource.Id.staticUsrName);
            tv_dwmc=(TextView)view.FindViewById(Resource.Id.dwmc);
            tv_usrName=(TextView)view.FindViewById(Resource.Id.usrName);
            tv_idInfo = (TextView)view.FindViewById(Resource.Id.idInfo);
            tv_staticIo = (TextView)view.FindViewById(Resource.Id.staticIo);
            tv_io = (TextView)view.FindViewById(Resource.Id.io);
            tv_staticServer = (TextView)view.FindViewById(Resource.Id.staticServer);
            tv_server = (TextView)view.FindViewById(Resource.Id.server);
            //
            tv_staticStatusServer = (TextView)view.FindViewById(Resource.Id.staticStatusServer);
            edt_statusServer = (EditText)view.FindViewById(Resource.Id.edt_statusServer);
            btn_apply = (Button)view.FindViewById(Resource.Id.btn_apply);
            tv_statusQInfo = (TextView)view.FindViewById(Resource.Id.statusQInfo);

            //
            btn_apply.Click += Btn_apply_Click;

            //
            string statusServer = "";
            qyFuncs.showInfo_get_cfgServer(ref statusServer);
            edt_statusServer.Text = statusServer;

            tv_statusQInfo.Text = "";

            //
            string verBuf=qyFuncs.qnmVerStr(pQyMc.iServiceId);
            bool bDebug = false;
#if DEBUG
           bDebug = true;
#endif
            int iVer = int.Parse(verBuf);
            str=string.Format("V{0}.{1}.{2}.{3} {4}", iVer / 1000000, (iVer / 10000) % 100, (iVer / 100) % 100, iVer % 100, bDebug ? ("Debug") : (""));

            tv_ver = (TextView)view.FindViewById(Resource.Id.ver);
            tv_ver.Text = str;

            tv_staticSupport = (TextView)view.FindViewById(Resource.Id.staticSupport);
            //
            tv_staticSupport.Text = "支持网站:";
            //
            tv_support = (TextView)view.FindViewById(Resource.Id.support);
            tv_support.Text = "www.qycx.com";

            //
            updateCtrls();


            //
            m_bInited = true;


            errLabel:

            //
            return view;

        }

        //
        unsafe int updateCtrls()
        {
            int iErr = -1;
            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
            QM_dbFuncs pDbFuncs = pQyMc.p_g_dbFuncs;
            MIS_CNT pMisCnt = pProcInfo.pMisCnt;

            string str;

            if (pMisCnt == null) return -1;

            //
            QY_MESSENGER_INFO msgrInfo;
            QY_MESSENGER_REGINFO regInfo;

            QY_MESSENGER_ID idInfo = pMisCnt.idInfo;
            if (!pDbFuncs.pf_bGetMessengerInfoBySth(pDbFuncs, pQyMc.gui.pDb, pQyMc.cfg.db.iDbType, ref qyFuncs.CONST_fieldIdTable_en, "", &idInfo, 0, &msgrInfo, &regInfo, null, null))
            {
                goto errLabel;
            }

            str = string.Format("{0} {1}", new string(regInfo.dw), new string(regInfo.bm));
            tv_dwmc.Text = str;

            tv_usrName.Text = new string(regInfo.syr);

            str = string.Format("{0}", idInfo.ui64Id);
            tv_idInfo.Text = str;

            fixed (byte* pIp = pMisCnt.server.ip)
            {
                str = string.Format("{0}:{1}",qyFuncs.mytoString(pIp),pMisCnt.server.port);
            }
            tv_server.Text = str;

            //
            if (!this.m_bUpdated_afterLogon)
            {
                if (pQyMc.bLogon)
                {
                    this.m_bUpdated_afterLogon = true;
                }
            }


            iErr = 0;
            errLabel:

            return iErr;
        }


        private void Btn_apply_Click(object sender, EventArgs e)
        {
            //throw new NotImplementedException();
            string statusServer = edt_statusServer.Text;
            //
            qyFuncs_Droid.saveDbgCfg(statusServer);
            //
            qyFuncs.showInfo_cfgServer(statusServer);

            return;
        }

        //
        public unsafe int gui_onTimer(object p0, object p1, object p2)
        {
            if (!m_bInited) return -1;

            CCtxQyMc pQyMc = g.g_pQyMc;
            CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

            //
            string status="";

            //
            if (!this.m_bUpdated_afterLogon)
            {
                updateCtrls();
            }

            //
            status = string.Format("{0,6:0.0},{1,6:0.0}", pProcInfo.status.netStat.ins.uiInSpeedInKbps / 1000.0f, pProcInfo.status.netStat.ins.uiOutSpeedInKbps / 1000.0f);
            tv_io.Text = status;

            //
            qyFuncs.showInfo_getStatus(ref status);

            tv_statusQInfo.Text = status;

            return 0;
        }

        //
        public override void OnResume()
        {
            base.OnResume();
            //
            updateCtrls();

            return;
        }

        //
        public override void OnDestroyView()
        {
            base.OnDestroyView();
        }

        //
        public override void OnDestroy()
        {
            if (this.edt_statusServer != null)
            {
                edt_statusServer.Dispose();
            }
            if (this.btn_apply != null)
            {
                this.btn_apply.Dispose();
            }
            if (this.tv_statusQInfo != null)
            {
                this.tv_statusQInfo.Dispose();
            }

            //
            base.OnDestroy();
            //
            Dispose();

        }

    }
}


