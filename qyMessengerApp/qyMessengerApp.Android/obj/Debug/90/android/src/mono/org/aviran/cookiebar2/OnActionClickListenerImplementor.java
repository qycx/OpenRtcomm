package mono.org.aviran.cookiebar2;


public class OnActionClickListenerImplementor
	extends java.lang.Object
	implements
		mono.android.IGCUserPeer,
		org.aviran.cookiebar2.OnActionClickListener
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_onClick:()V:GetOnClickHandler:Org.Aviran.Cookiebar2.IOnActionClickListenerInvoker, myBindingClassLibrary\n" +
			"";
		mono.android.Runtime.register ("Org.Aviran.Cookiebar2.IOnActionClickListenerImplementor, myBindingClassLibrary", OnActionClickListenerImplementor.class, __md_methods);
	}


	public OnActionClickListenerImplementor ()
	{
		super ();
		if (getClass () == OnActionClickListenerImplementor.class)
			mono.android.TypeManager.Activate ("Org.Aviran.Cookiebar2.IOnActionClickListenerImplementor, myBindingClassLibrary", "", this, new java.lang.Object[] {  });
	}


	public void onClick ()
	{
		n_onClick ();
	}

	private native void n_onClick ();

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
