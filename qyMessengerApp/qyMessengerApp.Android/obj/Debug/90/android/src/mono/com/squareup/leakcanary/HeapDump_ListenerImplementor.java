package mono.com.squareup.leakcanary;


public class HeapDump_ListenerImplementor
	extends java.lang.Object
	implements
		mono.android.IGCUserPeer,
		com.squareup.leakcanary.HeapDump.Listener
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_analyze:(Lcom/squareup/leakcanary/HeapDump;)V:GetAnalyze_Lcom_squareup_leakcanary_HeapDump_Handler:Square.LeakCanary.HeapDump/IListenerInvoker, LeakCanary.Watcher\n" +
			"";
		mono.android.Runtime.register ("Square.LeakCanary.HeapDump+IListenerImplementor, LeakCanary.Watcher", HeapDump_ListenerImplementor.class, __md_methods);
	}


	public HeapDump_ListenerImplementor ()
	{
		super ();
		if (getClass () == HeapDump_ListenerImplementor.class)
			mono.android.TypeManager.Activate ("Square.LeakCanary.HeapDump+IListenerImplementor, LeakCanary.Watcher", "", this, new java.lang.Object[] {  });
	}


	public void analyze (com.squareup.leakcanary.HeapDump p0)
	{
		n_analyze (p0);
	}

	private native void n_analyze (com.squareup.leakcanary.HeapDump p0);

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
