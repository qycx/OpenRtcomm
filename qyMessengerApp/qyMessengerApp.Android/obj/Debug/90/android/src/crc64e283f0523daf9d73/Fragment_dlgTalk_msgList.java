package crc64e283f0523daf9d73;


public class Fragment_dlgTalk_msgList
	extends androidx.fragment.app.Fragment
	implements
		mono.android.IGCUserPeer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_onCreate:(Landroid/os/Bundle;)V:GetOnCreate_Landroid_os_Bundle_Handler\n" +
			"n_onCreateView:(Landroid/view/LayoutInflater;Landroid/view/ViewGroup;Landroid/os/Bundle;)Landroid/view/View;:GetOnCreateView_Landroid_view_LayoutInflater_Landroid_view_ViewGroup_Landroid_os_Bundle_Handler\n" +
			"n_onDestroyView:()V:GetOnDestroyViewHandler\n" +
			"n_onDestroy:()V:GetOnDestroyHandler\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.Fragment_dlgTalk_msgList, qyMessengerApp.Android", Fragment_dlgTalk_msgList.class, __md_methods);
	}


	public Fragment_dlgTalk_msgList ()
	{
		super ();
		if (getClass () == Fragment_dlgTalk_msgList.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Fragment_dlgTalk_msgList, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public Fragment_dlgTalk_msgList (int p0)
	{
		super (p0);
		if (getClass () == Fragment_dlgTalk_msgList.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.Fragment_dlgTalk_msgList, qyMessengerApp.Android", "System.Int32, mscorlib", this, new java.lang.Object[] { p0 });
	}


	public void onCreate (android.os.Bundle p0)
	{
		n_onCreate (p0);
	}

	private native void n_onCreate (android.os.Bundle p0);


	public android.view.View onCreateView (android.view.LayoutInflater p0, android.view.ViewGroup p1, android.os.Bundle p2)
	{
		return n_onCreateView (p0, p1, p2);
	}

	private native android.view.View n_onCreateView (android.view.LayoutInflater p0, android.view.ViewGroup p1, android.os.Bundle p2);


	public void onDestroyView ()
	{
		n_onDestroyView ();
	}

	private native void n_onDestroyView ();


	public void onDestroy ()
	{
		n_onDestroy ();
	}

	private native void n_onDestroy ();

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