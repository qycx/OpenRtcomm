package crc64e283f0523daf9d73;


public class camera_RenderThread
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
		mono.android.Runtime.register ("qyMessengerApp.Droid.camera_RenderThread, qyMessengerApp.Android", camera_RenderThread.class, __md_methods);
	}


	public camera_RenderThread ()
	{
		super ();
		if (getClass () == camera_RenderThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.camera_RenderThread, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public camera_RenderThread (java.lang.Runnable p0)
	{
		super (p0);
		if (getClass () == camera_RenderThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.camera_RenderThread, qyMessengerApp.Android", "Java.Lang.IRunnable, Mono.Android", this, new java.lang.Object[] { p0 });
	}


	public camera_RenderThread (java.lang.Runnable p0, java.lang.String p1)
	{
		super (p0, p1);
		if (getClass () == camera_RenderThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.camera_RenderThread, qyMessengerApp.Android", "Java.Lang.IRunnable, Mono.Android:System.String, mscorlib", this, new java.lang.Object[] { p0, p1 });
	}


	public camera_RenderThread (java.lang.String p0)
	{
		super (p0);
		if (getClass () == camera_RenderThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.camera_RenderThread, qyMessengerApp.Android", "System.String, mscorlib", this, new java.lang.Object[] { p0 });
	}


	public camera_RenderThread (java.lang.ThreadGroup p0, java.lang.Runnable p1)
	{
		super (p0, p1);
		if (getClass () == camera_RenderThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.camera_RenderThread, qyMessengerApp.Android", "Java.Lang.ThreadGroup, Mono.Android:Java.Lang.IRunnable, Mono.Android", this, new java.lang.Object[] { p0, p1 });
	}


	public camera_RenderThread (java.lang.ThreadGroup p0, java.lang.Runnable p1, java.lang.String p2)
	{
		super (p0, p1, p2);
		if (getClass () == camera_RenderThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.camera_RenderThread, qyMessengerApp.Android", "Java.Lang.ThreadGroup, Mono.Android:Java.Lang.IRunnable, Mono.Android:System.String, mscorlib", this, new java.lang.Object[] { p0, p1, p2 });
	}


	public camera_RenderThread (java.lang.ThreadGroup p0, java.lang.Runnable p1, java.lang.String p2, long p3)
	{
		super (p0, p1, p2, p3);
		if (getClass () == camera_RenderThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.camera_RenderThread, qyMessengerApp.Android", "Java.Lang.ThreadGroup, Mono.Android:Java.Lang.IRunnable, Mono.Android:System.String, mscorlib:System.Int64, mscorlib", this, new java.lang.Object[] { p0, p1, p2, p3 });
	}


	public camera_RenderThread (java.lang.ThreadGroup p0, java.lang.String p1)
	{
		super (p0, p1);
		if (getClass () == camera_RenderThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.camera_RenderThread, qyMessengerApp.Android", "Java.Lang.ThreadGroup, Mono.Android:System.String, mscorlib", this, new java.lang.Object[] { p0, p1 });
	}

	public camera_RenderThread (android.os.Handler p0, android.opengl.EGLContext p1, int p2, boolean p3, int p4)
	{
		super ();
		if (getClass () == camera_RenderThread.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.camera_RenderThread, qyMessengerApp.Android", "Android.OS.Handler, Mono.Android:Android.Opengl.EGLContext, Mono.Android:System.Int32, mscorlib:System.Boolean, mscorlib:Android.Views.SurfaceOrientation, Mono.Android", this, new java.lang.Object[] { p0, p1, p2, p3, p4 });
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
