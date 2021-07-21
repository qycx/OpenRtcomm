package crc64e283f0523daf9d73;


public class MyApplication
	extends android.app.Application
	implements
		mono.android.IGCUserPeer,
		androidx.lifecycle.LifecycleObserver
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_onCreate:()V:GetOnCreateHandler\n" +
			"n_onAppBackgrounded:()V:__export__\n" +
			"n_onAppForegrounded:()V:__export__\n" +
			"";
	}

	public MyApplication ()
	{
		mono.MonoPackageManager.setContext (this);
	}


	public void onCreate ()
	{
		n_onCreate ();
	}

	private native void n_onCreate ();

	@androidx.lifecycle.OnLifecycleEvent(androidx.lifecycle.Lifecycle.Event.ON_STOP)

	public void onAppBackgrounded ()
	{
		n_onAppBackgrounded ();
	}

	private native void n_onAppBackgrounded ();

	@androidx.lifecycle.OnLifecycleEvent(androidx.lifecycle.Lifecycle.Event.ON_START)

	public void onAppForegrounded ()
	{
		n_onAppForegrounded ();
	}

	private native void n_onAppForegrounded ();

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
