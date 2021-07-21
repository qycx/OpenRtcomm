package crc64e283f0523daf9d73;


public class Activity_dlgTalk_av_MyHandler
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
		mono.android.Runtime.register ("qyMessengerApp.Droid.Activity_dlgTalk_av+MyHandler, qyMessengerApp.Android", Activity_dlgTalk_av_MyHandler.class, __md_methods);
	}


	public Activity_dlgTalk_av_MyHandler ()
	{
		super ();
		if (getClass () == Activity_dlgTalk_av_MyHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Activity_dlgTalk_av+MyHandler, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public Activity_dlgTalk_av_MyHandler (android.os.Handler.Callback p0)
	{
		super (p0);
		if (getClass () == Activity_dlgTalk_av_MyHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Activity_dlgTalk_av+MyHandler, qyMessengerApp.Android", "Android.OS.Handler+ICallback, Mono.Android", this, new java.lang.Object[] { p0 });
	}


	public Activity_dlgTalk_av_MyHandler (android.os.Looper p0)
	{
		super (p0);
		if (getClass () == Activity_dlgTalk_av_MyHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Activity_dlgTalk_av+MyHandler, qyMessengerApp.Android", "Android.OS.Looper, Mono.Android", this, new java.lang.Object[] { p0 });
	}


	public Activity_dlgTalk_av_MyHandler (android.os.Looper p0, android.os.Handler.Callback p1)
	{
		super (p0, p1);
		if (getClass () == Activity_dlgTalk_av_MyHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Activity_dlgTalk_av+MyHandler, qyMessengerApp.Android", "Android.OS.Looper, Mono.Android:Android.OS.Handler+ICallback, Mono.Android", this, new java.lang.Object[] { p0, p1 });
	}

	public Activity_dlgTalk_av_MyHandler (crc64e283f0523daf9d73.Activity_dlgTalk_av p0)
	{
		super ();
		if (getClass () == Activity_dlgTalk_av_MyHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Activity_dlgTalk_av+MyHandler, qyMessengerApp.Android", "qyMessengerApp.Droid.Activity_dlgTalk_av, qyMessengerApp.Android", this, new java.lang.Object[] { p0 });
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
