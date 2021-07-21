package crc64e283f0523daf9d73;


public class MainActivity_TmpCustomViewInitializer
	extends java.lang.Object
	implements
		mono.android.IGCUserPeer,
		org.aviran.cookiebar2.CookieBar.CustomViewInitializer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_initView:(Landroid/view/View;)V:GetInitView_Landroid_view_View_Handler:Org.Aviran.Cookiebar2.CookieBar/ICustomViewInitializerInvoker, myBindingClassLibrary\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.MainActivity+TmpCustomViewInitializer, qyMessengerApp.Android", MainActivity_TmpCustomViewInitializer.class, __md_methods);
	}


	public MainActivity_TmpCustomViewInitializer ()
	{
		super ();
		if (getClass () == MainActivity_TmpCustomViewInitializer.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MainActivity+TmpCustomViewInitializer, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public void initView (android.view.View p0)
	{
		n_initView (p0);
	}

	private native void n_initView (android.view.View p0);

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
