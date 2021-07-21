package crc6437f8a4b20549deeb;


public class ExtractMp3FramesTest_ExtractMpegFramesWrapper
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
		mono.android.Runtime.register ("qy.Droid.ExtractMp3FramesTest+ExtractMpegFramesWrapper, qyMessengerApp.Android", ExtractMp3FramesTest_ExtractMpegFramesWrapper.class, __md_methods);
	}


	public ExtractMp3FramesTest_ExtractMpegFramesWrapper ()
	{
		super ();
		if (getClass () == ExtractMp3FramesTest_ExtractMpegFramesWrapper.class)
			mono.android.TypeManager.Activate ("qy.Droid.ExtractMp3FramesTest+ExtractMpegFramesWrapper, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
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
