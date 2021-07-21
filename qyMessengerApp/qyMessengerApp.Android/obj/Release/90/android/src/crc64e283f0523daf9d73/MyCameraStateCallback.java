package crc64e283f0523daf9d73;


public class MyCameraStateCallback
	extends android.hardware.camera2.CameraDevice.StateCallback
	implements
		mono.android.IGCUserPeer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_onOpened:(Landroid/hardware/camera2/CameraDevice;)V:GetOnOpened_Landroid_hardware_camera2_CameraDevice_Handler\n" +
			"n_onDisconnected:(Landroid/hardware/camera2/CameraDevice;)V:GetOnDisconnected_Landroid_hardware_camera2_CameraDevice_Handler\n" +
			"n_onError:(Landroid/hardware/camera2/CameraDevice;I)V:GetOnError_Landroid_hardware_camera2_CameraDevice_IHandler\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.MyCameraStateCallback, qyMessengerApp.Android", MyCameraStateCallback.class, __md_methods);
	}


	public MyCameraStateCallback ()
	{
		super ();
		if (getClass () == MyCameraStateCallback.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MyCameraStateCallback, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}

	public MyCameraStateCallback (crc64e283f0523daf9d73.Fragment_dlgTalk_av p0)
	{
		super ();
		if (getClass () == MyCameraStateCallback.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.MyCameraStateCallback, qyMessengerApp.Android", "qyMessengerApp.Droid.Fragment_dlgTalk_av, qyMessengerApp.Android", this, new java.lang.Object[] { p0 });
	}


	public void onOpened (android.hardware.camera2.CameraDevice p0)
	{
		n_onOpened (p0);
	}

	private native void n_onOpened (android.hardware.camera2.CameraDevice p0);


	public void onDisconnected (android.hardware.camera2.CameraDevice p0)
	{
		n_onDisconnected (p0);
	}

	private native void n_onDisconnected (android.hardware.camera2.CameraDevice p0);


	public void onError (android.hardware.camera2.CameraDevice p0, int p1)
	{
		n_onError (p0, p1);
	}

	private native void n_onError (android.hardware.camera2.CameraDevice p0, int p1);

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
