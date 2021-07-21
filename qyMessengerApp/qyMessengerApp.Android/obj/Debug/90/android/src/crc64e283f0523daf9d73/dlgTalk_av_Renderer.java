package crc64e283f0523daf9d73;


public class dlgTalk_av_Renderer
	extends java.lang.Thread
	implements
		mono.android.IGCUserPeer,
		android.view.TextureView.SurfaceTextureListener
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_run:()V:GetRunHandler\n" +
			"n_onSurfaceTextureAvailable:(Landroid/graphics/SurfaceTexture;II)V:GetOnSurfaceTextureAvailable_Landroid_graphics_SurfaceTexture_IIHandler:Android.Views.TextureView/ISurfaceTextureListenerInvoker, Mono.Android, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null\n" +
			"n_onSurfaceTextureDestroyed:(Landroid/graphics/SurfaceTexture;)Z:GetOnSurfaceTextureDestroyed_Landroid_graphics_SurfaceTexture_Handler:Android.Views.TextureView/ISurfaceTextureListenerInvoker, Mono.Android, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null\n" +
			"n_onSurfaceTextureSizeChanged:(Landroid/graphics/SurfaceTexture;II)V:GetOnSurfaceTextureSizeChanged_Landroid_graphics_SurfaceTexture_IIHandler:Android.Views.TextureView/ISurfaceTextureListenerInvoker, Mono.Android, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null\n" +
			"n_onSurfaceTextureUpdated:(Landroid/graphics/SurfaceTexture;)V:GetOnSurfaceTextureUpdated_Landroid_graphics_SurfaceTexture_Handler:Android.Views.TextureView/ISurfaceTextureListenerInvoker, Mono.Android, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.dlgTalk_av_Renderer, qyMessengerApp.Android", dlgTalk_av_Renderer.class, __md_methods);
	}


	public dlgTalk_av_Renderer ()
	{
		super ();
		if (getClass () == dlgTalk_av_Renderer.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.dlgTalk_av_Renderer, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public dlgTalk_av_Renderer (java.lang.Runnable p0)
	{
		super (p0);
		if (getClass () == dlgTalk_av_Renderer.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.dlgTalk_av_Renderer, qyMessengerApp.Android", "Java.Lang.IRunnable, Mono.Android", this, new java.lang.Object[] { p0 });
	}


	public dlgTalk_av_Renderer (java.lang.Runnable p0, java.lang.String p1)
	{
		super (p0, p1);
		if (getClass () == dlgTalk_av_Renderer.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.dlgTalk_av_Renderer, qyMessengerApp.Android", "Java.Lang.IRunnable, Mono.Android:System.String, mscorlib", this, new java.lang.Object[] { p0, p1 });
	}


	public dlgTalk_av_Renderer (java.lang.String p0)
	{
		super (p0);
		if (getClass () == dlgTalk_av_Renderer.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.dlgTalk_av_Renderer, qyMessengerApp.Android", "System.String, mscorlib", this, new java.lang.Object[] { p0 });
	}


	public dlgTalk_av_Renderer (java.lang.ThreadGroup p0, java.lang.Runnable p1)
	{
		super (p0, p1);
		if (getClass () == dlgTalk_av_Renderer.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.dlgTalk_av_Renderer, qyMessengerApp.Android", "Java.Lang.ThreadGroup, Mono.Android:Java.Lang.IRunnable, Mono.Android", this, new java.lang.Object[] { p0, p1 });
	}


	public dlgTalk_av_Renderer (java.lang.ThreadGroup p0, java.lang.Runnable p1, java.lang.String p2)
	{
		super (p0, p1, p2);
		if (getClass () == dlgTalk_av_Renderer.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.dlgTalk_av_Renderer, qyMessengerApp.Android", "Java.Lang.ThreadGroup, Mono.Android:Java.Lang.IRunnable, Mono.Android:System.String, mscorlib", this, new java.lang.Object[] { p0, p1, p2 });
	}


	public dlgTalk_av_Renderer (java.lang.ThreadGroup p0, java.lang.Runnable p1, java.lang.String p2, long p3)
	{
		super (p0, p1, p2, p3);
		if (getClass () == dlgTalk_av_Renderer.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.dlgTalk_av_Renderer, qyMessengerApp.Android", "Java.Lang.ThreadGroup, Mono.Android:Java.Lang.IRunnable, Mono.Android:System.String, mscorlib:System.Int64, mscorlib", this, new java.lang.Object[] { p0, p1, p2, p3 });
	}


	public dlgTalk_av_Renderer (java.lang.ThreadGroup p0, java.lang.String p1)
	{
		super (p0, p1);
		if (getClass () == dlgTalk_av_Renderer.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.dlgTalk_av_Renderer, qyMessengerApp.Android", "Java.Lang.ThreadGroup, Mono.Android:System.String, mscorlib", this, new java.lang.Object[] { p0, p1 });
	}

	public dlgTalk_av_Renderer (android.app.Fragment p0, int p1)
	{
		super ();
		if (getClass () == dlgTalk_av_Renderer.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.dlgTalk_av_Renderer, qyMessengerApp.Android", "Android.App.Fragment, Mono.Android:System.Int32, mscorlib", this, new java.lang.Object[] { p0, p1 });
	}


	public void run ()
	{
		n_run ();
	}

	private native void n_run ();


	public void onSurfaceTextureAvailable (android.graphics.SurfaceTexture p0, int p1, int p2)
	{
		n_onSurfaceTextureAvailable (p0, p1, p2);
	}

	private native void n_onSurfaceTextureAvailable (android.graphics.SurfaceTexture p0, int p1, int p2);


	public boolean onSurfaceTextureDestroyed (android.graphics.SurfaceTexture p0)
	{
		return n_onSurfaceTextureDestroyed (p0);
	}

	private native boolean n_onSurfaceTextureDestroyed (android.graphics.SurfaceTexture p0);


	public void onSurfaceTextureSizeChanged (android.graphics.SurfaceTexture p0, int p1, int p2)
	{
		n_onSurfaceTextureSizeChanged (p0, p1, p2);
	}

	private native void n_onSurfaceTextureSizeChanged (android.graphics.SurfaceTexture p0, int p1, int p2);


	public void onSurfaceTextureUpdated (android.graphics.SurfaceTexture p0)
	{
		n_onSurfaceTextureUpdated (p0);
	}

	private native void n_onSurfaceTextureUpdated (android.graphics.SurfaceTexture p0);

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
