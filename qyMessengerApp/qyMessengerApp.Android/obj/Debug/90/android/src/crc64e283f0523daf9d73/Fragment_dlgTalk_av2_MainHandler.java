package crc64e283f0523daf9d73;


public class Fragment_dlgTalk_av2_MainHandler
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
		mono.android.Runtime.register ("qyMessengerApp.Droid.Fragment_dlgTalk_av2+MainHandler, qyMessengerApp.Android", Fragment_dlgTalk_av2_MainHandler.class, __md_methods);
	}


	public Fragment_dlgTalk_av2_MainHandler ()
	{
		super ();
		if (getClass () == Fragment_dlgTalk_av2_MainHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Fragment_dlgTalk_av2+MainHandler, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public Fragment_dlgTalk_av2_MainHandler (android.os.Handler.Callback p0)
	{
		super (p0);
		if (getClass () == Fragment_dlgTalk_av2_MainHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Fragment_dlgTalk_av2+MainHandler, qyMessengerApp.Android", "Android.OS.Handler+ICallback, Mono.Android", this, new java.lang.Object[] { p0 });
	}


	public Fragment_dlgTalk_av2_MainHandler (android.os.Looper p0)
	{
		super (p0);
		if (getClass () == Fragment_dlgTalk_av2_MainHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Fragment_dlgTalk_av2+MainHandler, qyMessengerApp.Android", "Android.OS.Looper, Mono.Android", this, new java.lang.Object[] { p0 });
	}


	public Fragment_dlgTalk_av2_MainHandler (android.os.Looper p0, android.os.Handler.Callback p1)
	{
		super (p0, p1);
		if (getClass () == Fragment_dlgTalk_av2_MainHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Fragment_dlgTalk_av2+MainHandler, qyMessengerApp.Android", "Android.OS.Looper, Mono.Android:Android.OS.Handler+ICallback, Mono.Android", this, new java.lang.Object[] { p0, p1 });
	}

	public Fragment_dlgTalk_av2_MainHandler (crc64e283f0523daf9d73.Fragment_dlgTalk_av2 p0)
	{
		super ();
		if (getClass () == Fragment_dlgTalk_av2_MainHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Fragment_dlgTalk_av2+MainHandler, qyMessengerApp.Android", "qyMessengerApp.Droid.Fragment_dlgTalk_av2, qyMessengerApp.Android", this, new java.lang.Object[] { p0 });
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
