using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Support.V4.App;
using Android.Views;
using Android.Widget;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace qyMessengerApp.Droid
{
    public class FragmentPagerAdapter_dlgTalk : FragmentPagerAdapter
    {
        private int PAGER_COUNT = 2;
        public Fragment_dlgTalk_msgList mFragment_dlgTalk_msgList1 = null;
        public Fragment_dlgTalk_detail  mFragment_dlgTalk_detail1 = null;
#if DEBUG
        Fragment_null mFg_test0;
        Fragment_null mFg_test1;

#endif

        public FragmentPagerAdapter_dlgTalk(Android.Support.V4.App.FragmentManager fm):base(fm)
        {
            mFragment_dlgTalk_msgList1 = new Fragment_dlgTalk_msgList();
            mFragment_dlgTalk_detail1 = new Fragment_dlgTalk_detail();
            //
#if DEBUG
            mFg_test0 = new Fragment_null();
            mFg_test1 = new Fragment_null();

#endif
        }

        public override int Count
        {
            get
            {
                return PAGER_COUNT;
            }

        }

        public override Android.Support.V4.App.Fragment GetItem(int position)
        {
            Android.Support.V4.App.Fragment fragment = null;

#if DEBUG
            switch (position)
            {
                case 0:
                    //return this.mFg_test0;//
                    return this.mFragment_dlgTalk_msgList1;
                    break;
                case 1:
                    return this.mFragment_dlgTalk_detail1;
                    break;
                default:
                    return null;
                    break;

            }
#endif


            //
            switch (position)
            {
                case Activity_dlgTalk.PAGE_ONE:
                    fragment = mFragment_dlgTalk_msgList1;
                    break;
                case Activity_dlgTalk.PAGE_TWO:
                    fragment = mFragment_dlgTalk_detail1;
                    break;
                default:
                    break;
            }
            return fragment;
        }

        public override long GetItemId(int position)
        {
            return position;
        }

      
    }

}