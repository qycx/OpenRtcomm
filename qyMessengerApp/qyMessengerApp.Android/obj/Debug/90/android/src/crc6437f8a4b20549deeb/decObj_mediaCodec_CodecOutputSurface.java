package crc6437f8a4b20549deeb;


public class decObj_mediaCodec_CodecOutputSurface
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
		mono.android.Runtime.register ("qy.Droid.decObj_mediaCodec+CodecOutputSurface, qyMessengerApp.Android", decObj_mediaCodec_CodecOutputSurface.class, __md_methods);
	}


	public decObj_mediaCodec_CodecOutputSurface ()
	{
		super ();
		if (getClass () == decObj_mediaCodec_CodecOutputSurface.class)
			mono.android.TypeManager.Activate ("qy.Droid.decObj_mediaCodec+CodecOutputSurface, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
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
