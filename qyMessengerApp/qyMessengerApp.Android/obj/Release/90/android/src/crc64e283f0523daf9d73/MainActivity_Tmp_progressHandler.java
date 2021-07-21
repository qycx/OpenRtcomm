package crc64e283f0523daf9d73;


public class MainActivity_Tmp_progressHandler
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
		mono.android.Runtime.register ("qyMessengerApp.Droid.MainActivity+Tmp_progressHandler, qyMessengerApp.Android", MainActivity_Tmp_progressHandler.class, __md_methods);
	}


	public MainActivity_Tmp_progressHandler ()
	{
		super ();
		if (getClass () == MainActivity_Tmp_progressHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MainActivity+Tmp_progressHandler, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public MainActivity_Tmp_progressHandler (android.os.Looper p0)
	{
		super (p0);
		if (getClass () == MainActivity_Tmp_progressHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MainActivity+Tmp_progressHandler, qyMessengerApp.Android", "Android.OS.Looper, Mono.Android", this, new java.lang.Object[] { p0 });
	}

	public MainActivity_Tmp_progressHandler (android.app.ProgressDialog p0)
	{
		super ();
		if (getClass () == MainActivity_Tmp_progressHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MainActivity+Tmp_progressHandler, qyMessengerApp.Android", "Android.App.ProgressDialog, Mono.Android", this, new java.lang.Object[] { p0 });
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
