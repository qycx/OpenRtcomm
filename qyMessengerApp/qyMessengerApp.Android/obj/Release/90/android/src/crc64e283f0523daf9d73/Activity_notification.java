package crc64e283f0523daf9d73;


public class Activity_notification
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
		mono.android.Runtime.register ("qyMessengerApp.Droid.Activity_notification, qyMessengerApp.Android", Activity_notification.class, __md_methods);
	}


	public Activity_notification ()
	{
		super ();
		if (getClass () == Activity_notification.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Activity_notification, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public Activity_notification (int p0)
	{
		super (p0);
		if (getClass () == Activity_notification.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Activity_notification, qyMessengerApp.Android", "System.Int32, mscorlib", this, new java.lang.Object[] { p0 });
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
