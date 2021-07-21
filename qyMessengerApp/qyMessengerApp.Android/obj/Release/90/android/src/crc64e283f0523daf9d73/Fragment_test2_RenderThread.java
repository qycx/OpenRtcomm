package crc64e283f0523daf9d73;


public class Fragment_test2_RenderThread
	extends java.lang.Thread
	implements
		mono.android.IGCUserPeer,
		android.graphics.SurfaceTexture.OnFrameAvailableListener
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_run:()V:GetRunHandler\n" +
			"n_onFrameAvailable:(Landroid/graphics/SurfaceTexture;)V:GetOnFrameAvailable_Landroid_graphics_SurfaceTexture_Handler:Android.Graphics.SurfaceTexture/IOnFrameAvailableListenerInvoker, Mono.Android, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.Fragment_test2+RenderThread, qyMessengerApp.Android", Fragment_test2_RenderThread.class, __md_methods);
	}


	public Fragment_test2_RenderThread ()
	{
		super ();
		if (getClass () == Fragment_test2_RenderThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Fragment_test2+RenderThread, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public Fragment_test2_RenderThread (java.lang.Runnable p0, java.lang.String p1)
	{
		super (p0, p1);
		if (getClass () == Fragment_test2_RenderThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Fragment_test2+RenderThread, qyMessengerApp.Android", "Java.Lang.IRunnable, Mono.Android:System.String, mscorlib", this, new java.lang.Object[] { p0, p1 });
	}


	public Fragment_test2_RenderThread (java.lang.String p0)
	{
		super (p0);
		if (getClass () == Fragment_test2_RenderThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Fragment_test2+RenderThread, qyMessengerApp.Android", "System.String, mscorlib", this, new java.lang.Object[] { p0 });
	}

	public Fragment_test2_RenderThread (crc64e283f0523daf9d73.Fragment_test2_MainHandler p0)
	{
		super ();
		if (getClass () == Fragment_test2_RenderThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Fragment_test2+RenderThread, qyMessengerApp.Android", "qyMessengerApp.Droid.Fragment_test2+MainHandler, qyMessengerApp.Android", this, new java.lang.Object[] { p0 });
	}


	public void run ()
	{
		n_run ();
	}

	private native void n_run ();


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
