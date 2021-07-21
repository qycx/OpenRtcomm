package crc64e283f0523daf9d73;


public class MainActivity_Tmp_progressThread
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
		mono.android.Runtime.register ("qyMessengerApp.Droid.MainActivity+Tmp_progressThread, qyMessengerApp.Android", MainActivity_Tmp_progressThread.class, __md_methods);
	}


	public MainActivity_Tmp_progressThread ()
	{
		super ();
		if (getClass () == MainActivity_Tmp_progressThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MainActivity+Tmp_progressThread, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public MainActivity_Tmp_progressThread (java.lang.Runnable p0, java.lang.String p1)
	{
		super (p0, p1);
		if (getClass () == MainActivity_Tmp_progressThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MainActivity+Tmp_progressThread, qyMessengerApp.Android", "Java.Lang.IRunnable, Mono.Android:System.String, mscorlib", this, new java.lang.Object[] { p0, p1 });
	}


	public MainActivity_Tmp_progressThread (java.lang.String p0)
	{
		super (p0);
		if (getClass () == MainActivity_Tmp_progressThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MainActivity+Tmp_progressThread, qyMessengerApp.Android", "System.String, mscorlib", this, new java.lang.Object[] { p0 });
	}

	public MainActivity_Tmp_progressThread (crc64e283f0523daf9d73.MainActivity_Tmp_progressHandler p0)
	{
		super ();
		if (getClass () == MainActivity_Tmp_progressThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MainActivity+Tmp_progressThread, qyMessengerApp.Android", "qyMessengerApp.Droid.MainActivity+Tmp_progressHandler, qyMessengerApp.Android", this, new java.lang.Object[] { p0 });
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
