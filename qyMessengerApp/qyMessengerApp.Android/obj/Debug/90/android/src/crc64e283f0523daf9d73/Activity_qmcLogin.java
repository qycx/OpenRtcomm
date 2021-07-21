package crc64e283f0523daf9d73;


public class Activity_qmcLogin
	extends crc64e283f0523daf9d73.qmcBaseActivity
	implements
		mono.android.IGCUserPeer,
		android.view.View.OnClickListener,
		pub.devrel.easypermissions.EasyPermissions.PermissionCallbacks,
		androidx.core.app.ActivityCompat.OnRequestPermissionsResultCallback
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_onRequestPermissionsResult:(I[Ljava/lang/String;[I)V:GetOnRequestPermissionsResult_IarrayLjava_lang_String_arrayIHandler\n" +
			"n_onCreate:(Landroid/os/Bundle;)V:GetOnCreate_Landroid_os_Bundle_Handler\n" +
			"n_onDestroy:()V:GetOnDestroyHandler\n" +
			"n_onBackPressed:()V:GetOnBackPressedHandler\n" +
			"n_onClick:(Landroid/view/View;)V:GetOnClick_Landroid_view_View_Handler:Android.Views.View/IOnClickListenerInvoker, Mono.Android, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null\n" +
			"n_onPermissionsDenied:(ILjava/util/List;)V:GetOnPermissionsDenied_ILjava_util_List_Handler:Pub.Devrel.Easypermissions.EasyPermissions/IPermissionCallbacksInvoker, EasyPermissions.Xamarin.Android\n" +
			"n_onPermissionsGranted:(ILjava/util/List;)V:GetOnPermissionsGranted_ILjava_util_List_Handler:Pub.Devrel.Easypermissions.EasyPermissions/IPermissionCallbacksInvoker, EasyPermissions.Xamarin.Android\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.Activity_qmcLogin, qyMessengerApp.Android", Activity_qmcLogin.class, __md_methods);
	}


	public Activity_qmcLogin ()
	{
		super ();
		if (getClass () == Activity_qmcLogin.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Activity_qmcLogin, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public Activity_qmcLogin (int p0)
	{
		super (p0);
		if (getClass () == Activity_qmcLogin.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Activity_qmcLogin, qyMessengerApp.Android", "System.Int32, mscorlib", this, new java.lang.Object[] { p0 });
	}


	public void onRequestPermissionsResult (int p0, java.lang.String[] p1, int[] p2)
	{
		n_onRequestPermissionsResult (p0, p1, p2);
	}

	private native void n_onRequestPermissionsResult (int p0, java.lang.String[] p1, int[] p2);


	public void onCreate (android.os.Bundle p0)
	{
		n_onCreate (p0);
	}

	private native void n_onCreate (android.os.Bundle p0);


	public void onDestroy ()
	{
		n_onDestroy ();
	}

	private native void n_onDestroy ();


	public void onBackPressed ()
	{
		n_onBackPressed ();
	}

	private native void n_onBackPressed ();


	public void onClick (android.view.View p0)
	{
		n_onClick (p0);
	}

	private native void n_onClick (android.view.View p0);


	public void onPermissionsDenied (int p0, java.util.List p1)
	{
		n_onPermissionsDenied (p0, p1);
	}

	private native void n_onPermissionsDenied (int p0, java.util.List p1);


	public void onPermissionsGranted (int p0, java.util.List p1)
	{
		n_onPermissionsGranted (p0, p1);
	}

	private native void n_onPermissionsGranted (int p0, java.util.List p1);

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
