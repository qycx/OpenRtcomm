package crc64e283f0523daf9d73;


public class camera_RenderThread_camera_RenderHandler
	extends android.os.Handler
	implements
		mono.android.IGCUserPeer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_handleMessage:(Landroid/os/Message;)V:GetHandleMessage_Landroid_os_Message_Handler\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.camera_RenderThread+camera_RenderHandler, qyMessengerApp.Android", camera_RenderThread_camera_RenderHandler.class, __md_methods);
	}


	public camera_RenderThread_camera_RenderHandler ()
	{
		super ();
		if (getClass () == camera_RenderThread_camera_RenderHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.camera_RenderThread+camera_RenderHandler, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public camera_RenderThread_camera_RenderHandler (android.os.Looper p0)
	{
		super (p0);
		if (getClass () == camera_RenderThread_camera_RenderHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.camera_RenderThread+camera_RenderHandler, qyMessengerApp.Android", "Android.OS.Looper, Mono.Android", this, new java.lang.Object[] { p0 });
	}

	public camera_RenderThread_camera_RenderHandler (crc64e283f0523daf9d73.camera_RenderThread p0)
	{
		super ();
		if (getClass () == camera_RenderThread_camera_RenderHandler.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.camera_RenderThread+camera_RenderHandler, qyMessengerApp.Android", "qyMessengerApp.Droid.camera_RenderThread, qyMessengerApp.Android", this, new java.lang.Object[] { p0 });
	}


	public void handleMessage (android.os.Message p0)
	{
		n_handleMessage (p0);
	}

	private native void n_handleMessage (android.os.Message p0);

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
