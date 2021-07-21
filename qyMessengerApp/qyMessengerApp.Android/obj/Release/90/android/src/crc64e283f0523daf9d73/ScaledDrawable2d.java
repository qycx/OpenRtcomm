package crc64e283f0523daf9d73;


public class ScaledDrawable2d
	extends com.qycx.gleslibrary.Drawable2d
	implements
		mono.android.IGCUserPeer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_getTexCoordArray:()Ljava/nio/FloatBuffer;:GetGetTexCoordArrayHandler\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.ScaledDrawable2d, qyMessengerApp.Android", ScaledDrawable2d.class, __md_methods);
	}


	public ScaledDrawable2d (com.qycx.gleslibrary.Drawable2d.Prefab p0)
	{
		super (p0);
		if (getClass () == ScaledDrawable2d.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.ScaledDrawable2d, qyMessengerApp.Android", "Com.Qycx.Gleslibrary.Drawable2d+Prefab, myBindingClassLibrary_gles", this, new java.lang.Object[] { p0 });
	}


	public java.nio.FloatBuffer getTexCoordArray ()
	{
		return n_getTexCoordArray ();
	}

	private native java.nio.FloatBuffer n_getTexCoordArray ();

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
