package crc6437f8a4b20549deeb;


public class ExtractMp3FramesTest_CodecOutputSurface
	extends java.lang.Object
	implements
		mono.android.IGCUserPeer,
		android.graphics.SurfaceTexture.OnFrameAvailableListener
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_onFrameAvailable:(Landroid/graphics/SurfaceTexture;)V:GetOnFrameAvailable_Landroid_graphics_SurfaceTexture_Handler:Android.Graphics.SurfaceTexture/IOnFrameAvailableListenerInvoker, Mono.Android, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null\n" +
			"";
		mono.android.Runtime.register ("qy.Droid.ExtractMp3FramesTest+CodecOutputSurface, qyMessengerApp.Android", ExtractMp3FramesTest_CodecOutputSurface.class, __md_methods);
	}


	public ExtractMp3FramesTest_CodecOutputSurface ()
	{
		super ();
		if (getClass () == ExtractMp3FramesTest_CodecOutputSurface.class)
			mono.android.TypeManager.Activate ("qy.Droid.ExtractMp3FramesTest+CodecOutputSurface, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}

	public ExtractMp3FramesTest_CodecOutputSurface (int p0, int p1)
	{
		super ();
		if (getClass () == ExtractMp3FramesTest_CodecOutputSurface.class)
			mono.android.TypeManager.Activate ("qy.Droid.ExtractMp3FramesTest+CodecOutputSurface, qyMessengerApp.Android", "System.Int32, mscorlib:System.Int32, mscorlib", this, new java.lang.Object[] { p0, p1 });
	}


	public void onFrameAvailable (android.graphics.SurfaceTexture p0)
	{
		n_onFrameAvailable (p0);
	}

	private native void n_onFrameAvailable (android.graphics.SurfaceTexture p0);

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
