using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using AndroidX.RecyclerView.Widget;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using qy.Droid;

//
namespace qyMessengerApp.Droid
{
    class Adapter_dlgTalk_msgList:RecyclerView.Adapter
    {
        public event EventHandler<Adapter_dlgTalk_msgListClickEventArgs> ItemClick;
        public event EventHandler<Adapter_dlgTalk_msgListClickEventArgs> ItemLongClick;
        List<TableItem_dlgTalk_msg> items;
        Activity_dlgTalk mActivity;


        public Adapter_dlgTalk_msgList(Activity activity, List<TableItem_dlgTalk_msg> data)
        {
            mActivity = (Activity_dlgTalk)activity;
            items = data;
        }

        // Create new views (invoked by the layout manager)
        public override RecyclerView.ViewHolder OnCreateViewHolder(ViewGroup parent, int viewType)
        {

            //Setup your layout here
            View itemView = null;
            var id = Resource.Layout.layout_dlgTalk_msgRow;
            itemView = LayoutInflater.From(parent.Context).
                   Inflate(id, parent, false);

            var vh = new Adapter_dlgTalk_msgListViewHolder(itemView, OnClick, OnLongClick);
            return vh;
        }

        // Replace the contents of a view (invoked by the layout manager)
        public override void OnBindViewHolder(RecyclerView.ViewHolder viewHolder, int position)
        {
            var item = items[position];

            // Replace the contents of the view with that element
            var holder = viewHolder as Adapter_dlgTalk_msgListViewHolder;


            //holder.TextView.Text = items[position];
            string str;
            if (mActivity.m_var.addr.uiObjType == Consts.CONST_objType_imGrp)
            {
                str = string.Format("{0} {1} {2}", item.dw, item.bm, item.syr);
                holder.tv_speaker.Text = str;
            }
            else
            {
                str = item.syr;
                holder.tv_speaker.Text = str;
            }
            holder.iv.SetImageResource(item.ImageResourceId);
            holder.tv_msg.Text = item.msg;
        }

        public override int ItemCount => items.Count;

        void OnClick(Adapter_dlgTalk_msgListClickEventArgs args) => ItemClick?.Invoke(this, args);
        void OnLongClick(Adapter_dlgTalk_msgListClickEventArgs args) => ItemLongClick?.Invoke(this, args);

    }

    public class Adapter_dlgTalk_msgListViewHolder : RecyclerView.ViewHolder
    {
        public ImageView iv { get; set; }
        public TextView tv_speaker { get; set; }
        public TextView tv_msg { get; set; }


        public Adapter_dlgTalk_msgListViewHolder(View itemView, Action<Adapter_dlgTalk_msgListClickEventArgs> clickListener,
                            Action<Adapter_dlgTalk_msgListClickEventArgs> longClickListener) : base(itemView)
        {

            //TextView = v;
            iv = (ImageView)itemView.FindViewById(Resource.Id.iv);
            tv_speaker = (TextView)itemView.FindViewById(Resource.Id.tv_speaker);
            tv_msg = (TextView)itemView.FindViewById(Resource.Id.tv_msg);
            //
            itemView.Click += (sender, e) => clickListener(new Adapter_dlgTalk_msgListClickEventArgs { View = itemView, Position = AdapterPosition });
            itemView.LongClick += (sender, e) => longClickListener(new Adapter_dlgTalk_msgListClickEventArgs { View = itemView, Position = AdapterPosition });
        }
    }

    public class Adapter_dlgTalk_msgListClickEventArgs : EventArgs
    {
        public View View { get; set; }
        public int Position { get; set; }
    }


}
