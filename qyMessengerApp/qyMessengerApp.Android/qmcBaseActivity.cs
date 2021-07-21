using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Support.V7.App;
using Android.Views;
using Android.Widget;
using Java.Lang;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using qy;


namespace qyMessengerApp.Droid
{
    [Activity(Label = "BaseActivity")]
    public class BaseActivity : AppCompatActivity
    {
        Handler m_timerHandler;
        myTimerRunnable m_timerRunnable;
        int                 m_delayInMs;
        PF_commonHandler    m_pf;

        //
        public string mTag;

        //       
        class myTimerRunnable : Java.Lang.Object, IRunnable
        {
            BaseActivity mOwner;
            public myTimerRunnable(BaseActivity owner)
            {
                mOwner = owner;
            }

            public void Run()
            {
                //throw new NotImplementedException();

                //
#if DEBUG
                qyFuncs.chkAllTc("timer starts");
#endif

                //
                mOwner.m_pf(null, null, null);

                //
#if DEBUG
                qyFuncs.chkAllTc("timer ends");
#endif

                //
                if (mOwner.m_timerHandler != null)
                {
                    mOwner.m_timerHandler.PostDelayed(mOwner.m_timerRunnable, mOwner.m_delayInMs);
                }
            }
        }



        public int setTimer(int delayInMs, PF_commonHandler pf)
        {
            if (delayInMs == 0) return -1;
            if (pf == null) return -1;

            if (m_timerHandler != null || m_timerRunnable != null) return -1;

            //
            this.m_timerHandler = new Handler();
            this.m_timerRunnable = new myTimerRunnable(this);
            this.m_delayInMs = delayInMs;
            m_pf = pf;

            //
            this.m_timerHandler.PostDelayed(this.m_timerRunnable, delayInMs);

            return 0;
        }

        public void killTimer()
        {
            if (this.m_timerHandler == null && this.m_timerRunnable == null) return;
            //
            this.m_timerHandler.RemoveCallbacks(this.m_timerRunnable);
            this.m_timerRunnable = null;
            this.m_timerHandler = null;

            return;
        }

  


        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Create your application here
            
        }


        //
        public int doFinish(string hint)
        {
            string str;

            //
            if (hint == null) hint = "";

            str = string.Format("{0}.doFinish, {1}", mTag, hint);
            qyFuncs.showInfo_open(0, null, str);

            //
            Finish();
            return 0;
        }


    }

    //
    public class qmcBaseActivity : BaseActivity
    {

        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            //
            RequestedOrientation = Android.Content.PM.ScreenOrientation.Portrait;
        }

    }

}


