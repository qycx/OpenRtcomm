package crc64e283f0523daf9d73;


public class Activity_dlgTalk
	extends crc64e283f0523daf9d73.qmcBaseActivity
	implements
		mono.android.IGCUserPeer,
		android.view.View.OnClickListener,
		androidx.viewpager.widget.ViewPager.OnPageChangeListener
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_onCreate:(Landroid/os/Bundle;)V:GetOnCreate_Landroid_os_Bundle_Handler\n" +
			"n_onResume:()V:GetOnResumeHandler\n" +
			"n_onPause:()V:GetOnPauseHandler\n" +
			"n_onBackPressed:()V:GetOnBackPressedHandler\n" +
			"n_onDestroy:()V:GetOnDestroyHandler\n" +
			"n_onClick:(Landroid/view/View;)V:GetOnClick_Landroid_view_View_Handler:Android.Views.View/IOnClickListenerInvoker, Mono.Android, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null\n" +
			"n_onPageScrollStateChanged:(I)V:GetOnPageScrollStateChanged_IHandler:AndroidX.ViewPager.Widget.ViewPager/IOnPageChangeListenerInvoker, Xamarin.AndroidX.ViewPager\n" +
			"n_onPageScrolled:(IFI)V:GetOnPageScrolled_IFIHandler:AndroidX.ViewPager.Widget.ViewPager/IOnPageChangeListenerInvoker, Xamarin.AndroidX.ViewPager\n" +
			"n_onPageSelected:(I)V:GetOnPageSelected_IHandler:AndroidX.ViewPager.Widget.ViewPager/IOnPageChangeListenerInvoker, Xamarin.AndroidX.ViewPager\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.Activity_dlgTalk, qyMessengerApp.Android", Activity_dlgTalk.class, __md_methods);
	}


	public Activity_dlgTalk ()
	{
		super ();
		if (getClass () == Activity_dlgTalk.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Activity_dlgTalk, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public Activity_dlgTalk (int p0)
	{
		super (p0);
		if (getClass () == Activity_dlgTalk.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Activity_dlgTalk, qyMessengerApp.Android", "System.Int32, mscorlib", this, new java.lang.Object[] { p0 });
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


	public void onBackPressed ()
	{
		n_onBackPressed ();
	}

	private native void n_onBackPressed ();


	public void onDestroy ()
	{
		n_onDestroy ();
	}

	private native void n_onDestroy ();


	public void onClick (android.view.View p0)
	{
		n_onClick (p0);
	}

	private native void n_onClick (android.view.View p0);


	public void onPageScrollStateChanged (int p0)
	{
		n_onPageScrollStateChanged (p0);
	}

	private native void n_onPageScrollStateChanged (int p0);


	public void onPageScrolled (int p0, float p1, int p2)
	{
		n_onPageScrolled (p0, p1, p2);
	}

	private native void n_onPageScrolled (int p0, float p1, int p2);


	public void onPageSelected (int p0)
	{
		n_onPageSelected (p0);
	}

	private native void n_onPageSelected (int p0);

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
