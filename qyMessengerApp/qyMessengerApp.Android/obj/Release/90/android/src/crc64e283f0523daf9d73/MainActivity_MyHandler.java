package crc64e283f0523daf9d73;


public class MainActivity_MyHandler
	extends android.os.Handler
	implements
		mono.android.IGCUserPeer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_handleMessage:(Landroid/os/Message;)V:GetHandleMessage_Landroid_os_Message_Handler\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.MainActivity+MyHandler, qyMessengerApp.Android", MainActivity_MyHandler.class, __md_methods);
	}


	public MainActivity_MyHandler ()
	{
		super ();
		if (getClass () == MainActivity_MyHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MainActivity+MyHandler, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public MainActivity_MyHandler (android.os.Looper p0)
	{
		super (p0);
		if (getClass () == MainActivity_MyHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MainActivity+MyHandler, qyMessengerApp.Android", "Android.OS.Looper, Mono.Android", this, new java.lang.Object[] { p0 });
	}

	public MainActivity_MyHandler (crc64e283f0523daf9d73.MainActivity p0)
	{
		super ();
		if (getClass () == MainActivity_MyHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MainActivity+MyHandler, qyMessengerApp.Android", "qyMessengerApp.Droid.MainActivity, qyMessengerApp.Android", this, new java.lang.Object[] { p0 });
	}


	public void handleMessage (android.os.Message p0)
	{
		n_handleMessage (p0);
	}

	private native void n_handleMessage (android.os.Message p0);

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
