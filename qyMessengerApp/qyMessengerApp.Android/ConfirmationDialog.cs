using Android;
using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using AndroidX.Legacy.App;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace qyMessengerApp.Droid
{
    class ConfirmationDialog:DialogFragment
    {
        private static Fragment mParent;

        class PositiveListener:Java.Lang.Object,IDialogInterfaceOnClickListener
        {
            public void OnClick(IDialogInterface dialog,int which)
            {
                FragmentCompat.RequestPermissions(mParent,
                    new string[] { Manifest.Permission.Camera, Manifest.Permission.RecordAudio,}, Fragment_dlgTalk_av.REQUEST_VIDEO_PERMISSIONS);
            }
        }

        class NegativeListener:Java.Lang.Object,IDialogInterfaceOnClickListener
        {
            public void OnClick(IDialogInterface dialog,int which)
            {
                Activity activity = mParent.Activity;
                if (activity != null)
                {
                    activity.Finish();
                }

            }
        }

        public override Dialog OnCreateDialog(Bundle savedInstanceState)
        {
            mParent = ParentFragment;
            return new AlertDialog.Builder(Activity)
                .SetMessage(Resource.String.request_permission)
                .SetPositiveButton(Android.Resource.String.Ok, new PositiveListener())
                .SetNegativeButton(Android.Resource.String.Cancel, new NegativeListener())
                .Create();
        }
    }
}