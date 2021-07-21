package crc64e283f0523daf9d73;


public class MyTextureView
	extends android.view.TextureView
	implements
		mono.android.IGCUserPeer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.MyTextureView, qyMessengerApp.Android", MyTextureView.class, __md_methods);
	}


	public MyTextureView (android.content.Context p0, android.util.AttributeSet p1)
	{
		super (p0, p1);
		if (getClass () == MyTextureView.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MyTextureView, qyMessengerApp.Android", "Android.Content.Context, Mono.Android:Android.Util.IAttributeSet, Mono.Android", this, new java.lang.Object[] { p0, p1 });
	}


	public MyTextureView (android.content.Context p0, android.util.AttributeSet p1, int p2)
	{
		super (p0, p1, p2);
		if (getClass () == MyTextureView.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MyTextureView, qyMessengerApp.Android", "Android.Content.Context, Mono.Android:Android.Util.IAttributeSet, Mono.Android:System.Int32, mscorlib", this, new java.lang.Object[] { p0, p1, p2 });
	}

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
