package crc64e283f0523daf9d73;


public class Adapter_dlgTalk_msgListViewHolder
	extends androidx.recyclerview.widget.RecyclerView.ViewHolder
	implements
		mono.android.IGCUserPeer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.Adapter_dlgTalk_msgListViewHolder, qyMessengerApp.Android", Adapter_dlgTalk_msgListViewHolder.class, __md_methods);
	}


	public Adapter_dlgTalk_msgListViewHolder (android.view.View p0)
	{
		super (p0);
		if (getClass () == Adapter_dlgTalk_msgListViewHolder.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Adapter_dlgTalk_msgListViewHolder, qyMessengerApp.Android", "Android.Views.View, Mono.Android", this, new java.lang.Object[] { p0 });
	}

	private java.util.ArrayList refList;
	public void monodroidAddReference (java.lang.Object obj)
	{
		if (refList == null)
			refList = new java.util.ArrayList ();
		refList.add (obj);
	}

	public void monodroidClearReferences ()
	{
		if (refList != null)
			refList.clear ();
	}
}
