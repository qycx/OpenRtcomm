package crc6437f8a4b20549deeb;


public class decObj_a_mediaCodec_decObj_a_mediaCodec_Wrapper
	extends java.lang.Object
	implements
		mono.android.IGCUserPeer,
		java.lang.Runnable
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_run:()V:GetRunHandler:Java.Lang.IRunnableInvoker, Mono.Android, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null\n" +
			"";
		mono.android.Runtime.register ("qy.Droid.decObj_a_mediaCodec+decObj_a_mediaCodec_Wrapper, qyMessengerApp.Android", decObj_a_mediaCodec_decObj_a_mediaCodec_Wrapper.class, __md_methods);
	}


	public decObj_a_mediaCodec_decObj_a_mediaCodec_Wrapper ()
	{
		super ();
		if (getClass () == decObj_a_mediaCodec_decObj_a_mediaCodec_Wrapper.class)
			mono.android.TypeManager.Activate ("qy.Droid.decObj_a_mediaCodec+decObj_a_mediaCodec_Wrapper, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
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
