﻿using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace qyMessengerApp.Droid
{
    class ErrorDialog:DialogFragment
    {
        private static readonly string ARG_MESSAGE = "message";
        
        private class PositiveListener:Java.Lang.Object,IDialogInterfaceOnClickListener
        {
            ErrorDialog er;
            public PositiveListener(ErrorDialog e)
            {
                er = e;
            }
            public void OnClick(IDialogInterface dialog,int which)
            {
                er.Activity.Finish();
            }

        }

        //
        public static ErrorDialog newInstance(string message)
        {
            ErrorDialog dialog = new ErrorDialog();
            Bundle args = new Bundle();
            args.PutString(ARG_MESSAGE, message);
            dialog.Arguments=args;
            return dialog;

        }
        

        public override Dialog OnCreateDialog(Bundle savedInstanceState)
        {
            var alert = new AlertDialog.Builder(Activity);
            alert.SetMessage(Arguments.GetString(ARG_MESSAGE));
            alert.SetPositiveButton(Android.Resource.String.Ok, new PositiveListener(this));
            return alert.Show();
        }
    }
}