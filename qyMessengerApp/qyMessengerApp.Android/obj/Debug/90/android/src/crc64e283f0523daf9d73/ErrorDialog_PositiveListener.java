package crc64e283f0523daf9d73;


public class ErrorDialog_PositiveListener
	extends java.lang.Object
	implements
		mono.android.IGCUserPeer,
		android.content.DialogInterface.OnClickListener
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_onClick:(Landroid/content/DialogInterface;I)V:GetOnClick_Landroid_content_DialogInterface_IHandler:Android.Content.IDialogInterfaceOnClickListenerInvoker, Mono.Android, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.ErrorDialog+PositiveListener, qyMessengerApp.Android", ErrorDialog_PositiveListener.class, __md_methods);
	}


	public ErrorDialog_PositiveListener ()
	{
		super ();
		if (getClass () == ErrorDialog_PositiveListener.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.ErrorDialog+PositiveListener, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}

	public ErrorDialog_PositiveListener (crc64e283f0523daf9d73.ErrorDialog p0)
	{
		super ();
		if (getClass () == ErrorDialog_PositiveListener.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.ErrorDialog+PositiveListener, qyMessengerApp.Android", "qyMessengerApp.Droid.ErrorDialog, qyMessengerApp.Android", this, new java.lang.Object[] { p0 });
	}


	public void onClick (android.content.DialogInterface p0, int p1)
	{
		n_onClick (p0, p1);
	}

	private native void n_onClick (android.content.DialogInterface p0, int p1);

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
