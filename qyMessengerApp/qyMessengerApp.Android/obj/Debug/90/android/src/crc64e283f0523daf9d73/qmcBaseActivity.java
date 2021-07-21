package crc64e283f0523daf9d73;


public class qmcBaseActivity
	extends crc64e283f0523daf9d73.BaseActivity
	implements
		mono.android.IGCUserPeer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_onCreate:(Landroid/os/Bundle;)V:GetOnCreate_Landroid_os_Bundle_Handler\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.qmcBaseActivity, qyMessengerApp.Android", qmcBaseActivity.class, __md_methods);
	}


	public qmcBaseActivity ()
	{
		super ();
		if (getClass () == qmcBaseActivity.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.qmcBaseActivity, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public qmcBaseActivity (int p0)
	{
		super (p0);
		if (getClass () == qmcBaseActivity.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.qmcBaseActivity, qyMessengerApp.Android", "System.Int32, mscorlib", this, new java.lang.Object[] { p0 });
	}


	public void onCreate (android.os.Bundle p0)
	{
		n_onCreate (p0);
	}

	private native void n_onCreate (android.os.Bundle p0);

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
