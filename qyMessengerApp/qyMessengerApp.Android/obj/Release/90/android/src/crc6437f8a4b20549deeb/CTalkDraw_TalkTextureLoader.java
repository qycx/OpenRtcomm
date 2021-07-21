package crc6437f8a4b20549deeb;


public class CTalkDraw_TalkTextureLoader
	extends crc6437f8a4b20549deeb.CQmcDrawTmpl_TextureLoader
	implements
		mono.android.IGCUserPeer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"";
		mono.android.Runtime.register ("qy.Droid.CTalkDraw+TalkTextureLoader, qyMessengerApp.Android", CTalkDraw_TalkTextureLoader.class, __md_methods);
	}


	public CTalkDraw_TalkTextureLoader ()
	{
		super ();
		if (getClass () == CTalkDraw_TalkTextureLoader.class)
			mono.android.TypeManager.Activate ("qy.Droid.CTalkDraw+TalkTextureLoader, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public CTalkDraw_TalkTextureLoader (java.lang.Runnable p0, java.lang.String p1)
	{
		super (p0, p1);
		if (getClass () == CTalkDraw_TalkTextureLoader.class)
			mono.android.TypeManager.Activate ("qy.Droid.CTalkDraw+TalkTextureLoader, qyMessengerApp.Android", "Java.Lang.IRunnable, Mono.Android:System.String, mscorlib", this, new java.lang.Object[] { p0, p1 });
	}


	public CTalkDraw_TalkTextureLoader (java.lang.String p0)
	{
		super (p0);
		if (getClass () == CTalkDraw_TalkTextureLoader.class)
			mono.android.TypeManager.Activate ("qy.Droid.CTalkDraw+TalkTextureLoader, qyMessengerApp.Android", "System.String, mscorlib", this, new java.lang.Object[] { p0 });
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
