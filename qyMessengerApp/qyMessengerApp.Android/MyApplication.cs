using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using AndroidX.Lifecycle;
using Java.Interop;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//
using qy;
using Square.LeakCanary;


//
namespace qyMessengerApp.Droid
{
    [Application]
    public class MyApplication:Application,ILifecycleObserver
    {
        private RefWatcher _refWatcher;

        public MyApplication(IntPtr javaReference, Android.Runtime.JniHandleOwnership transfer) : base(javaReference, transfer)
        {
        }

        public override void OnCreate()
        {
            base.OnCreate();

            //
            bool bNoLeakCannary = false;
            bNoLeakCannary = true;
            if (!bNoLeakCannary)
            {
                SetupLeakCanary();
            }

            //
            var lifecycleOwner = ProcessLifecycleOwner.Get();
            var lifecycle = lifecycleOwner.Lifecycle;
            lifecycle.AddObserver(this);

        }

        protected void SetupLeakCanary()
        {
            if (LeakCanaryXamarin.IsInAnalyzerProcess(this))
            {
                return;
            }
            _refWatcher = LeakCanaryXamarin.Install(this);
        }



        [Lifecycle.Event.OnStop]
        [Export]
        public void onAppBackgrounded()
        {
            Console.WriteLine("background");
            //
            CCtxQyMc pQyMc = g.g_pQyMc;
            if (pQyMc != null)
            {
                pQyMc.gui.bForeground = false;
            }
        }

        [Lifecycle.Event.OnStart]
        [Export]
        public void onAppForegrounded()
        {
            Console.WriteLine("foreground");
            //
            CCtxQyMc pQyMc = g.g_pQyMc;
            if (pQyMc != null)
            {
                pQyMc.gui.bForeground = true;
            }
        }


    }
}