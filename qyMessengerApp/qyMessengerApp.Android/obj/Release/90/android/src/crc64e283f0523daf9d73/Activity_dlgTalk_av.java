package crc64e283f0523daf9d73;


public class Activity_dlgTalk_av
	extends crc64e283f0523daf9d73.BaseActivity
	implements
		mono.android.IGCUserPeer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_onCreate:(Landroid/os/Bundle;)V:GetOnCreate_Landroid_os_Bundle_Handler\n" +
			"n_onResume:()V:GetOnResumeHandler\n" +
			"n_onPause:()V:GetOnPauseHandler\n" +
			"n_onDestroy:()V:GetOnDestroyHandler\n" +
			"n_onSaveInstanceState:(Landroid/os/Bundle;)V:GetOnSaveInstanceState_Landroid_os_Bundle_Handler\n" +
			"n_onRestoreInstanceState:(Landroid/os/Bundle;)V:GetOnRestoreInstanceState_Landroid_os_Bundle_Handler\n" +
			"n_onBackPressed:()V:GetOnBackPressedHandler\n" +
			"n_onTouchEvent:(Landroid/view/MotionEvent;)Z:GetOnTouchEvent_Landroid_view_MotionEvent_Handler\n" +
			"n_onWindowFocusChanged:(Z)V:GetOnWindowFocusChanged_ZHandler\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.Activity_dlgTalk_av, qyMessengerApp.Android", Activity_dlgTalk_av.class, __md_methods);
	}


	public Activity_dlgTalk_av ()
	{
		super ();
		if (getClass () == Activity_dlgTalk_av.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Activity_dlgTalk_av, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public Activity_dlgTalk_av (int p0)
	{
		super (p0);
		if (getClass () == Activity_dlgTalk_av.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Activity_dlgTalk_av, qyMessengerApp.Android", "System.Int32, mscorlib", this, new java.lang.Object[] { p0 });
	}


	public void onCreate (android.os.Bundle p0)
	{
		n_onCreate (p0);
	}

	private native void n_onCreate (android.os.Bundle p0);


	public void onResume ()
	{
		n_onResume ();
	}

	private native void n_onResume ();


	public void onPause ()
	{
		n_onPause ();
	}

	private native void n_onPause ();


	public void onDestroy ()
	{
		n_onDestroy ();
	}

	private native void n_onDestroy ();


	public void onSaveInstanceState (android.os.Bundle p0)
	{
		n_onSaveInstanceState (p0);
	}

	private native void n_onSaveInstanceState (android.os.Bundle p0);


	public void onRestoreInstanceState (android.os.Bundle p0)
	{
		n_onRestoreInstanceState (p0);
	}

	private native void n_onRestoreInstanceState (android.os.Bundle p0);


	public void onBackPressed ()
	{
		n_onBackPressed ();
	}

	private native void n_onBackPressed ();


	public boolean onTouchEvent (android.view.MotionEvent p0)
	{
		return n_onTouchEvent (p0);
	}

	private native boolean n_onTouchEvent (android.view.MotionEvent p0);


	public void onWindowFocusChanged (boolean p0)
	{
		n_onWindowFocusChanged (p0);
	}

	private native void n_onWindowFocusChanged (boolean p0);

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
