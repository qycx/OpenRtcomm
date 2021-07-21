using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Org.Aviran.Cookiebar2 {

	// Metadata.xml XPath interface reference: path="/api/package[@name='org.aviran.cookiebar2']/interface[@name='OnActionClickListener']"
	[Register ("org/aviran/cookiebar2/OnActionClickListener", "", "Org.Aviran.Cookiebar2.IOnActionClickListenerInvoker")]
	public partial interface IOnActionClickListener : IJavaObject, IJavaPeerable {
		// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/interface[@name='OnActionClickListener']/method[@name='onClick' and count(parameter)=0]"
		[Register ("onClick", "()V", "GetOnClickHandler:Org.Aviran.Cookiebar2.IOnActionClickListenerInvoker, myBindingClassLibrary")]
		void OnClick ();

	}

	[global::Android.Runtime.Register ("org/aviran/cookiebar2/OnActionClickListener", DoNotGenerateAcw=true)]
	internal partial class IOnActionClickListenerInvoker : global::Java.Lang.Object, IOnActionClickListener {
		static readonly JniPeerMembers _members = new XAPeerMembers ("org/aviran/cookiebar2/OnActionClickListener", typeof (IOnActionClickListenerInvoker));

		static IntPtr java_class_ref {
			get { return _members.JniPeerType.PeerReference.Handle; }
		}

		[global::System.Diagnostics.DebuggerBrowsable (global::System.Diagnostics.DebuggerBrowsableState.Never)]
		[global::System.ComponentModel.EditorBrowsable (global::System.ComponentModel.EditorBrowsableState.Never)]
		public override global::Java.Interop.JniPeerMembers JniPeerMembers {
			get { return _members; }
		}

		[global::System.Diagnostics.DebuggerBrowsable (global::System.Diagnostics.DebuggerBrowsableState.Never)]
		[global::System.ComponentModel.EditorBrowsable (global::System.ComponentModel.EditorBrowsableState.Never)]
		protected override IntPtr ThresholdClass {
			get { return class_ref; }
		}

		[global::System.Diagnostics.DebuggerBrowsable (global::System.Diagnostics.DebuggerBrowsableState.Never)]
		[global::System.ComponentModel.EditorBrowsable (global::System.ComponentModel.EditorBrowsableState.Never)]
		protected override global::System.Type ThresholdType {
			get { return _members.ManagedPeerType; }
		}

		IntPtr class_ref;

		public static IOnActionClickListener GetObject (IntPtr handle, JniHandleOwnership transfer)
		{
			return global::Java.Lang.Object.GetObject<IOnActionClickListener> (handle, transfer);
		}

		static IntPtr Validate (IntPtr handle)
		{
			if (!JNIEnv.IsInstanceOf (handle, java_class_ref))
				throw new InvalidCastException ($"Unable to convert instance of type '{JNIEnv.GetClassNameFromInstance (handle)}' to type 'org.aviran.cookiebar2.OnActionClickListener'.");
			return handle;
		}

		protected override void Dispose (bool disposing)
		{
			if (this.class_ref != IntPtr.Zero)
				JNIEnv.DeleteGlobalRef (this.class_ref);
			this.class_ref = IntPtr.Zero;
			base.Dispose (disposing);
		}

		public IOnActionClickListenerInvoker (IntPtr handle, JniHandleOwnership transfer) : base (Validate (handle), transfer)
		{
			IntPtr local_ref = JNIEnv.GetObjectClass (((global::Java.Lang.Object) this).Handle);
			this.class_ref = JNIEnv.NewGlobalRef (local_ref);
			JNIEnv.DeleteLocalRef (local_ref);
		}

		static Delegate cb_onClick;
#pragma warning disable 0169
		static Delegate GetOnClickHandler ()
		{
			if (cb_onClick == null)
				cb_onClick = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_V) n_OnClick);
			return cb_onClick;
		}

		static void n_OnClick (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.IOnActionClickListener> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.OnClick ();
		}
#pragma warning restore 0169

		IntPtr id_onClick;
		public unsafe void OnClick ()
		{
			if (id_onClick == IntPtr.Zero)
				id_onClick = JNIEnv.GetMethodID (class_ref, "onClick", "()V");
			JNIEnv.CallVoidMethod (((global::Java.Lang.Object) this).Handle, id_onClick);
		}

	}

	[global::Android.Runtime.Register ("mono/org/aviran/cookiebar2/OnActionClickListenerImplementor")]
	internal sealed partial class IOnActionClickListenerImplementor : global::Java.Lang.Object, IOnActionClickListener {

		object sender;

		public IOnActionClickListenerImplementor (object sender) : base (global::Android.Runtime.JNIEnv.StartCreateInstance ("mono/org/aviran/cookiebar2/OnActionClickListenerImplementor", "()V"), JniHandleOwnership.TransferLocalRef)
		{
			global::Android.Runtime.JNIEnv.FinishCreateInstance (((global::Java.Lang.Object) this).Handle, "()V");
			this.sender = sender;
		}

		#pragma warning disable 0649
		public EventHandler Handler;
		#pragma warning restore 0649

		public void OnClick ()
		{
			var __h = Handler;
			if (__h != null)
				__h (sender, new EventArgs ());
		}

		internal static bool __IsEmpty (IOnActionClickListenerImplementor value)
		{
			return value.Handler == null;
		}

	}
}
