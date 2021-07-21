using Android.App;
using Android.Content;
using Android.Hardware.Camera2;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using qy;


//
namespace qyMessengerApp.Droid
{
    class PreviewCaptureStateCallback:CameraCaptureSession.StateCallback
    {
        Fragment_dlgTalk_av fragment;

        public PreviewCaptureStateCallback(Fragment_dlgTalk_av frag)
        {
            fragment = frag;
        }

        public override void OnConfigured(CameraCaptureSession session)
        {
            bool bDbg = false;
            string str;
#if DEBUG
            bDbg = true;
#endif
            //
            if (bDbg)
            {
                str = string.Format("PreviewCaptrueStateCallback.OnConfigured");
                qyFuncs.showInfo_open(0, null, str);
            }

            //
            fragment.mPreviewSession = session;
            fragment.updatePreview();
        }

        public override void OnConfigureFailed(CameraCaptureSession session)
        {
            Activity activity = fragment.Activity;
            if ( null!=activity)
            {
                Toast.MakeText(fragment.Activity, "Failed", ToastLength.Short).Show();
            }

        }

    }
}