using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Org.Aviran.Cookiebar2 {

	[Register ("org/aviran/cookiebar2/CookieBarDismissListener$DismissType", DoNotGenerateAcw=true)]
	public abstract class CookieBarDismissListenerDismissType : Java.Lang.Object {
		internal CookieBarDismissListenerDismissType ()
		{
		}

		// Metadata.xml XPath field reference: path="/api/package[@name='org.aviran.cookiebar2']/interface[@name='CookieBarDismissListener.DismissType']/field[@name='DURATION_COMPLETE']"
		[Register ("DURATION_COMPLETE")]
		public const int DurationComplete = (int) 0;

		// Metadata.xml XPath field reference: path="/api/package[@name='org.aviran.cookiebar2']/interface[@name='CookieBarDismissListener.DismissType']/field[@name='PROGRAMMATIC_DISMISS']"
		[Register ("PROGRAMMATIC_DISMISS")]
		public const int ProgrammaticDismiss = (int) 3;

		// Metadata.xml XPath field reference: path="/api/package[@name='org.aviran.cookiebar2']/interface[@name='CookieBarDismissListener.DismissType']/field[@name='REPLACE_DISMISS']"
		[Register ("REPLACE_DISMISS")]
		public const int ReplaceDismiss = (int) 4;

		// Metadata.xml XPath field reference: path="/api/package[@name='org.aviran.cookiebar2']/interface[@name='CookieBarDismissListener.DismissType']/field[@name='USER_ACTION_CLICK']"
		[Register ("USER_ACTION_CLICK")]
		public const int UserActionClick = (int) 2;

		// Metadata.xml XPath field reference: path="/api/package[@name='org.aviran.cookiebar2']/interface[@name='CookieBarDismissListener.DismissType']/field[@name='USER_DISMISS']"
		[Register ("USER_DISMISS")]
		public const int UserDismiss = (int) 1;

		// The following are fields from: java.lang.annotation.Annotation

		// The following are fields from: Android.Runtime.IJavaObject

		// The following are fields from: System.IDisposable

		// The following are fields from: Java.Interop.IJavaPeerable

	}

	[Register ("org/aviran/cookiebar2/CookieBarDismissListener$DismissType", DoNotGenerateAcw=true)]
	[global::System.Obsolete ("Use the 'CookieBarDismissListenerDismissType' type. This type will be removed in a future release.", error: true)]
	public abstract class CookieBarDismissListenerDismissTypeConsts : CookieBarDismissListenerDismissType {
		private CookieBarDismissListenerDismissTypeConsts ()
		{
		}

	}

	// Metadata.xml XPath interface reference: path="/api/package[@name='org.aviran.cookiebar2']/interface[@name='CookieBarDismissListener.DismissType']"
	[Register ("org/aviran/cookiebar2/CookieBarDismissListener$DismissType", "", "Org.Aviran.Cookiebar2.ICookieBarDismissListenerDismissTypeInvoker")]
	public partial interface ICookieBarDismissListenerDismissType : global::Java.Lang.Annotation.IAnnotation {
	}

	[global::Android.Runtime.Register ("org/aviran/cookiebar2/CookieBarDismissListener$DismissType", DoNotGenerateAcw=true)]
	internal partial class ICookieBarDismissListenerDismissTypeInvoker : global::Java.Lang.Object, ICookieBarDismissListenerDismissType {
		static readonly JniPeerMembers _members = new XAPeerMembers ("org/aviran/cookiebar2/CookieBarDismissListener$DismissType", typeof (ICookieBarDismissListenerDismissTypeInvoker));

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

		public static ICookieBarDismissListenerDismissType GetObject (IntPtr handle, JniHandleOwnership transfer)
		{
			return global::Java.Lang.Object.GetObject<ICookieBarDismissListenerDismissType> (handle, transfer);
		}

		static IntPtr Validate (IntPtr handle)
		{
			if (!JNIEnv.IsInstanceOf (handle, java_class_ref))
				throw new InvalidCastException ($"Unable to convert instance of type '{JNIEnv.GetClassNameFromInstance (handle)}' to type 'org.aviran.cookiebar2.CookieBarDismissListener.DismissType'.");
			return handle;
		}

		protected override void Dispose (bool disposing)
		{
			if (this.class_ref != IntPtr.Zero)
				JNIEnv.DeleteGlobalRef (this.class_ref);
			this.class_ref = IntPtr.Zero;
			base.Dispose (disposing);
		}

		public ICookieBarDismissListenerDismissTypeInvoker (IntPtr handle, JniHandleOwnership transfer) : base (Validate (handle), transfer)
		{
			IntPtr local_ref = JNIEnv.GetObjectClass (((global::Java.Lang.Object) this).Handle);
			this.class_ref = JNIEnv.NewGlobalRef (local_ref);
			JNIEnv.DeleteLocalRef (local_ref);
		}

		static Delegate cb_annotationType;
#pragma warning disable 0169
		static Delegate GetAnnotationTypeHandler ()
		{
			if (cb_annotationType == null)
				cb_annotationType = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_L) n_AnnotationType);
			return cb_annotationType;
		}

		static IntPtr n_AnnotationType (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.ICookieBarDismissListenerDismissType> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return JNIEnv.ToLocalJniHandle (__this.AnnotationType ());
		}
#pragma warning restore 0169

		IntPtr id_annotationType;
		public unsafe global::Java.Lang.Class AnnotationType ()
		{
			if (id_annotationType == IntPtr.Zero)
				id_annotationType = JNIEnv.GetMethodID (class_ref, "annotationType", "()Ljava/lang/Class;");
			return global::Java.Lang.Object.GetObject<global::Java.Lang.Class> (JNIEnv.CallObjectMethod (((global::Java.Lang.Object) this).Handle, id_annotationType), JniHandleOwnership.TransferLocalRef);
		}

		static Delegate cb_equals_Ljava_lang_Object_;
#pragma warning disable 0169
		static Delegate GetEquals_Ljava_lang_Object_Handler ()
		{
			if (cb_equals_Ljava_lang_Object_ == null)
				cb_equals_Ljava_lang_Object_ = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPL_Z) n_Equals_Ljava_lang_Object_);
			return cb_equals_Ljava_lang_Object_;
		}

		static bool n_Equals_Ljava_lang_Object_ (IntPtr jnienv, IntPtr native__this, IntPtr native_obj)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.ICookieBarDismissListenerDismissType> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			var obj = global::Java.Lang.Object.GetObject<global::Java.Lang.Object> (native_obj, JniHandleOwnership.DoNotTransfer);
			bool __ret = __this.Equals (obj);
			return __ret;
		}
#pragma warning restore 0169

		IntPtr id_equals_Ljava_lang_Object_;
		public unsafe global::System.Boolean Equals (global::Java.Lang.Object obj)
		{
			if (id_equals_Ljava_lang_Object_ == IntPtr.Zero)
				id_equals_Ljava_lang_Object_ = JNIEnv.GetMethodID (class_ref, "equals", "(Ljava/lang/Object;)Z");
			JValue* __args = stackalloc JValue [1];
			__args [0] = new JValue ((obj == null) ? IntPtr.Zero : ((global::Java.Lang.Object) obj).Handle);
			var __ret = JNIEnv.CallBooleanMethod (((global::Java.Lang.Object) this).Handle, id_equals_Ljava_lang_Object_, __args);
			return __ret;
		}

		static Delegate cb_hashCode;
#pragma warning disable 0169
		static Delegate GetGetHashCodeHandler ()
		{
			if (cb_hashCode == null)
				cb_hashCode = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_I) n_GetHashCode);
			return cb_hashCode;
		}

		static int n_GetHashCode (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.ICookieBarDismissListenerDismissType> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.GetHashCode ();
		}
#pragma warning restore 0169

		IntPtr id_hashCode;
		public unsafe global::System.Int32 GetHashCode ()
		{
			if (id_hashCode == IntPtr.Zero)
				id_hashCode = JNIEnv.GetMethodID (class_ref, "hashCode", "()I");
			return JNIEnv.CallIntMethod (((global::Java.Lang.Object) this).Handle, id_hashCode);
		}

		static Delegate cb_toString;
#pragma warning disable 0169
		static Delegate GetToStringHandler ()
		{
			if (cb_toString == null)
				cb_toString = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_L) n_ToString);
			return cb_toString;
		}

		static IntPtr n_ToString (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.ICookieBarDismissListenerDismissType> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return JNIEnv.NewString (__this.ToString ());
		}
#pragma warning restore 0169

		IntPtr id_toString;
		public unsafe global::System.String ToString ()
		{
			if (id_toString == IntPtr.Zero)
				id_toString = JNIEnv.GetMethodID (class_ref, "toString", "()Ljava/lang/String;");
			return JNIEnv.GetString (JNIEnv.CallObjectMethod (((global::Java.Lang.Object) this).Handle, id_toString), JniHandleOwnership.TransferLocalRef);
		}

	}

	// Metadata.xml XPath interface reference: path="/api/package[@name='org.aviran.cookiebar2']/interface[@name='CookieBarDismissListener']"
	[Register ("org/aviran/cookiebar2/CookieBarDismissListener", "", "Org.Aviran.Cookiebar2.ICookieBarDismissListenerInvoker")]
	public partial interface ICookieBarDismissListener : IJavaObject, IJavaPeerable {
		// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/interface[@name='CookieBarDismissListener']/method[@name='onDismiss' and count(parameter)=1 and parameter[1][@type='int']]"
		[Register ("onDismiss", "(I)V", "GetOnDismiss_IHandler:Org.Aviran.Cookiebar2.ICookieBarDismissListenerInvoker, myBindingClassLibrary")]
		void OnDismiss (int p0);

	}

	[global::Android.Runtime.Register ("org/aviran/cookiebar2/CookieBarDismissListener", DoNotGenerateAcw=true)]
	internal partial class ICookieBarDismissListenerInvoker : global::Java.Lang.Object, ICookieBarDismissListener {
		static readonly JniPeerMembers _members = new XAPeerMembers ("org/aviran/cookiebar2/CookieBarDismissListener", typeof (ICookieBarDismissListenerInvoker));

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

		public static ICookieBarDismissListener GetObject (IntPtr handle, JniHandleOwnership transfer)
		{
			return global::Java.Lang.Object.GetObject<ICookieBarDismissListener> (handle, transfer);
		}

		static IntPtr Validate (IntPtr handle)
		{
			if (!JNIEnv.IsInstanceOf (handle, java_class_ref))
				throw new InvalidCastException ($"Unable to convert instance of type '{JNIEnv.GetClassNameFromInstance (handle)}' to type 'org.aviran.cookiebar2.CookieBarDismissListener'.");
			return handle;
		}

		protected override void Dispose (bool disposing)
		{
			if (this.class_ref != IntPtr.Zero)
				JNIEnv.DeleteGlobalRef (this.class_ref);
			this.class_ref = IntPtr.Zero;
			base.Dispose (disposing);
		}

		public ICookieBarDismissListenerInvoker (IntPtr handle, JniHandleOwnership transfer) : base (Validate (handle), transfer)
		{
			IntPtr local_ref = JNIEnv.GetObjectClass (((global::Java.Lang.Object) this).Handle);
			this.class_ref = JNIEnv.NewGlobalRef (local_ref);
			JNIEnv.DeleteLocalRef (local_ref);
		}

		static Delegate cb_onDismiss_I;
#pragma warning disable 0169
		static Delegate GetOnDismiss_IHandler ()
		{
			if (cb_onDismiss_I == null)
				cb_onDismiss_I = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPI_V) n_OnDismiss_I);
			return cb_onDismiss_I;
		}

		static void n_OnDismiss_I (IntPtr jnienv, IntPtr native__this, int p0)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.ICookieBarDismissListener> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.OnDismiss (p0);
		}
#pragma warning restore 0169

		IntPtr id_onDismiss_I;
		public unsafe void OnDismiss (int p0)
		{
			if (id_onDismiss_I == IntPtr.Zero)
				id_onDismiss_I = JNIEnv.GetMethodID (class_ref, "onDismiss", "(I)V");
			JValue* __args = stackalloc JValue [1];
			__args [0] = new JValue (p0);
			JNIEnv.CallVoidMethod (((global::Java.Lang.Object) this).Handle, id_onDismiss_I, __args);
		}

	}

	// event args for org.aviran.cookiebar2.CookieBarDismissListener.onDismiss
	public partial class CookieBarDismissEventArgs : global::System.EventArgs {
		public CookieBarDismissEventArgs (int p0)
		{
			this.p0 = p0;
		}

		int p0;

		public int P0 {
			get { return p0; }
		}

	}

	[global::Android.Runtime.Register ("mono/org/aviran/cookiebar2/CookieBarDismissListenerImplementor")]
	internal sealed partial class ICookieBarDismissListenerImplementor : global::Java.Lang.Object, ICookieBarDismissListener {

		object sender;

		public ICookieBarDismissListenerImplementor (object sender) : base (global::Android.Runtime.JNIEnv.StartCreateInstance ("mono/org/aviran/cookiebar2/CookieBarDismissListenerImplementor", "()V"), JniHandleOwnership.TransferLocalRef)
		{
			global::Android.Runtime.JNIEnv.FinishCreateInstance (((global::Java.Lang.Object) this).Handle, "()V");
			this.sender = sender;
		}

		#pragma warning disable 0649
		public EventHandler<CookieBarDismissEventArgs> Handler;
		#pragma warning restore 0649

		public void OnDismiss (int p0)
		{
			var __h = Handler;
			if (__h != null)
				__h (sender, new CookieBarDismissEventArgs (p0));
		}

		internal static bool __IsEmpty (ICookieBarDismissListenerImplementor value)
		{
			return value.Handler == null;
		}

	}
}
