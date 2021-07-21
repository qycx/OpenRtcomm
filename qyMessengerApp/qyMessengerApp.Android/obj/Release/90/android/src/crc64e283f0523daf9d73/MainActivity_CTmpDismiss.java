package crc64e283f0523daf9d73;


public class MainActivity_CTmpDismiss
	extends java.lang.Object
	implements
		mono.android.IGCUserPeer,
		org.aviran.cookiebar2.CookieBarDismissListener
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_onDismiss:(I)V:GetOnDismiss_IHandler:Org.Aviran.Cookiebar2.ICookieBarDismissListenerInvoker, myBindingClassLibrary\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.MainActivity+CTmpDismiss, qyMessengerApp.Android", MainActivity_CTmpDismiss.class, __md_methods);
	}


	public MainActivity_CTmpDismiss ()
	{
		super ();
		if (getClass () == MainActivity_CTmpDismiss.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MainActivity+CTmpDismiss, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public void onDismiss (int p0)
	{
		n_onDismiss (p0);
	}

	private native void n_onDismiss (int p0);

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
