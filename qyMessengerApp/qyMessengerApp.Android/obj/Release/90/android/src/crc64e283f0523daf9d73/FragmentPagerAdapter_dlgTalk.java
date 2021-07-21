package crc64e283f0523daf9d73;


public class FragmentPagerAdapter_dlgTalk
	extends androidx.fragment.app.FragmentPagerAdapter
	implements
		mono.android.IGCUserPeer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_getCount:()I:GetGetCountHandler\n" +
			"n_getItem:(I)Landroidx/fragment/app/Fragment;:GetGetItem_IHandler\n" +
			"n_getItemId:(I)J:GetGetItemId_IHandler\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.FragmentPagerAdapter_dlgTalk, qyMessengerApp.Android", FragmentPagerAdapter_dlgTalk.class, __md_methods);
	}


	public FragmentPagerAdapter_dlgTalk (androidx.fragment.app.FragmentManager p0)
	{
		super (p0);
		if (getClass () == FragmentPagerAdapter_dlgTalk.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.FragmentPagerAdapter_dlgTalk, qyMessengerApp.Android", "AndroidX.Fragment.App.FragmentManager, Xamarin.AndroidX.Fragment", this, new java.lang.Object[] { p0 });
	}


	public FragmentPagerAdapter_dlgTalk (androidx.fragment.app.FragmentManager p0, int p1)
	{
		super (p0, p1);
		if (getClass () == FragmentPagerAdapter_dlgTalk.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.FragmentPagerAdapter_dlgTalk, qyMessengerApp.Android", "AndroidX.Fragment.App.FragmentManager, Xamarin.AndroidX.Fragment:System.Int32, mscorlib", this, new java.lang.Object[] { p0, p1 });
	}


	public int getCount ()
	{
		return n_getCount ();
	}

	private native int n_getCount ();


	public androidx.fragment.app.Fragment getItem (int p0)
	{
		return n_getItem (p0);
	}

	private native androidx.fragment.app.Fragment n_getItem (int p0);


	public long getItemId (int p0)
	{
		return n_getItemId (p0);
	}

	private native long n_getItemId (int p0);

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
