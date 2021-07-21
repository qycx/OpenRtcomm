package crc64e283f0523daf9d73;


public class BaseActivity_myTimerRunnable
	extends java.lang.Object
	implements
		mono.android.IGCUserPeer,
		java.lang.Runnable
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_run:()V:GetRunHandler:Java.Lang.IRunnableInvoker, Mono.Android, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.BaseActivity+myTimerRunnable, qyMessengerApp.Android", BaseActivity_myTimerRunnable.class, __md_methods);
	}


	public BaseActivity_myTimerRunnable ()
	{
		super ();
		if (getClass () == BaseActivity_myTimerRunnable.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.BaseActivity+myTimerRunnable, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}

	public BaseActivity_myTimerRunnable (crc64e283f0523daf9d73.BaseActivity p0)
	{
		super ();
		if (getClass () == BaseActivity_myTimerRunnable.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.BaseActivity+myTimerRunnable, qyMessengerApp.Android", "qyMessengerApp.Droid.BaseActivity, qyMessengerApp.Android", this, new java.lang.Object[] { p0 });
	}


	public void run ()
	{
		n_run ();
	}

	private native void n_run ();

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
