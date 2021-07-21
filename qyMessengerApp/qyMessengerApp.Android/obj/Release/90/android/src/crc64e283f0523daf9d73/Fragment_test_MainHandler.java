package crc64e283f0523daf9d73;


public class Fragment_test_MainHandler
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
		mono.android.Runtime.register ("qyMessengerApp.Droid.Fragment_test+MainHandler, qyMessengerApp.Android", Fragment_test_MainHandler.class, __md_methods);
	}


	public Fragment_test_MainHandler ()
	{
		super ();
		if (getClass () == Fragment_test_MainHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Fragment_test+MainHandler, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public Fragment_test_MainHandler (android.os.Looper p0)
	{
		super (p0);
		if (getClass () == Fragment_test_MainHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Fragment_test+MainHandler, qyMessengerApp.Android", "Android.OS.Looper, Mono.Android", this, new java.lang.Object[] { p0 });
	}

	public Fragment_test_MainHandler (crc64e283f0523daf9d73.Fragment_test p0)
	{
		super ();
		if (getClass () == Fragment_test_MainHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Fragment_test+MainHandler, qyMessengerApp.Android", "qyMessengerApp.Droid.Fragment_test, qyMessengerApp.Android", this, new java.lang.Object[] { p0 });
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
