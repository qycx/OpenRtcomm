package crc64e283f0523daf9d73;


public class ConfirmationDialog
	extends android.app.DialogFragment
	implements
		mono.android.IGCUserPeer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_onCreateDialog:(Landroid/os/Bundle;)Landroid/app/Dialog;:GetOnCreateDialog_Landroid_os_Bundle_Handler\n" +
			"";
		mono.android.Runtime.register ("qyMessengerApp.Droid.ConfirmationDialog, qyMessengerApp.Android", ConfirmationDialog.class, __md_methods);
	}


	public ConfirmationDialog ()
	{
		super ();
		if (getClass () == ConfirmationDialog.class)
			mono.android.TypeManager.Activate ("qyMessengerApp.Droid.ConfirmationDialog, qyMessengerApp.Android", "", this, new java.lang.Object[] {  });
	}


	public android.app.Dialog onCreateDialog (android.os.Bundle p0)
	{
		return n_onCreateDialog (p0);
	}

	private native android.app.Dialog n_onCreateDialog (android.os.Bundle p0);

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
