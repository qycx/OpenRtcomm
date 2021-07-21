package crc6437f8a4b20549deeb;


public class MyThread
	extends java.lang.Thread
	implements
		mono.android.IGCUserPeer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_run:()V:GetRunHandler\n" +
			"";
		mono.android.Runtime.register ("qy.Droid.MyThread, qyMessengerApp.Android", MyThread.class, __md_methods);
	}


	public MyThread ()
	{
		super ();
		if (getClass () == MyThread.class)
			mono.android.TypeManager.Activate ("qy.Droid.MyThread, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public MyThread (java.lang.Runnable p0, java.lang.String p1)
	{
		super (p0, p1);
		if (getClass () == MyThread.class)
			mono.android.TypeManager.Activate ("qy.Droid.MyThread, qyMessengerApp.Android", "Java.Lang.IRunnable, Mono.Android:System.String, mscorlib", this, new java.lang.Object[] { p0, p1 });
	}


	public MyThread (java.lang.String p0)
	{
		super (p0);
		if (getClass () == MyThread.class)
			mono.android.TypeManager.Activate ("qy.Droid.MyThread, qyMessengerApp.Android", "System.String, mscorlib", this, new java.lang.Object[] { p0 });
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
