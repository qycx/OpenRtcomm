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

namespace qyMessengerApp.Droid
{
    public class Fragment_dlgTalk_detail : Android.Support.V4.App.Fragment
    {
        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Create your fragment here
        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            // Use this to return your custom view for this Fragment
            // return inflater.Inflate(Resource.Layout.YourFragment, container, false);

            //return base.OnCreateView(inflater, container, savedInstanceState);

            //
            View view = inflater.Inflate(Resource.Layout.layout_fg, container, false);

            //
            TextView txt_content = (TextView)view.FindViewById(Resource.Id.txt_content);
            txt_content.Text = "这是一个dlgTalk_detail fragment";


            //
            return view;


        }
    }
}