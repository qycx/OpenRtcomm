using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Org.Aviran.Cookiebar2 {

	// Metadata.xml XPath class reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar']"
	[global::Android.Runtime.Register ("org/aviran/cookiebar2/CookieBar", DoNotGenerateAcw=true)]
	public partial class CookieBar : global::Java.Lang.Object {
		// Metadata.xml XPath field reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar']/field[@name='BOTTOM']"
		[Register ("BOTTOM")]
		public const int Bottom = (int) 80;

		// Metadata.xml XPath field reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar']/field[@name='TOP']"
		[Register ("TOP")]
		public const int Top = (int) 48;

		// Metadata.xml XPath class reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']"
		[global::Android.Runtime.Register ("org/aviran/cookiebar2/CookieBar$Builder", DoNotGenerateAcw=true)]
		public partial class Builder : global::Java.Lang.Object {
			static readonly JniPeerMembers _members = new XAPeerMembers ("org/aviran/cookiebar2/CookieBar$Builder", typeof (Builder));

			internal static IntPtr class_ref {
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
				get { return _members.JniPeerType.PeerReference.Handle; }
			}

			[global::System.Diagnostics.DebuggerBrowsable (global::System.Diagnostics.DebuggerBrowsableState.Never)]
			[global::System.ComponentModel.EditorBrowsable (global::System.ComponentModel.EditorBrowsableState.Never)]
			protected override global::System.Type ThresholdType {
				get { return _members.ManagedPeerType; }
			}

			protected Builder (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
			{
			}

			static Delegate cb_create;
#pragma warning disable 0169
			static Delegate GetCreateHandler ()
			{
				if (cb_create == null)
					cb_create = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_L) n_Create);
				return cb_create;
			}

			static IntPtr n_Create (IntPtr jnienv, IntPtr native__this)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.Create ());
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='create' and count(parameter)=0]"
			[Register ("create", "()Lorg/aviran/cookiebar2/CookieBar;", "GetCreateHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar Create ()
			{
				const string __id = "create.()Lorg/aviran/cookiebar2/CookieBar;";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, null);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setAction_ILorg_aviran_cookiebar2_OnActionClickListener_;
#pragma warning disable 0169
			static Delegate GetSetAction_ILorg_aviran_cookiebar2_OnActionClickListener_Handler ()
			{
				if (cb_setAction_ILorg_aviran_cookiebar2_OnActionClickListener_ == null)
					cb_setAction_ILorg_aviran_cookiebar2_OnActionClickListener_ = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPIL_L) n_SetAction_ILorg_aviran_cookiebar2_OnActionClickListener_);
				return cb_setAction_ILorg_aviran_cookiebar2_OnActionClickListener_;
			}

			static IntPtr n_SetAction_ILorg_aviran_cookiebar2_OnActionClickListener_ (IntPtr jnienv, IntPtr native__this, int resId, IntPtr native_onActionClickListener)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				var onActionClickListener = (global::Org.Aviran.Cookiebar2.IOnActionClickListener)global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.IOnActionClickListener> (native_onActionClickListener, JniHandleOwnership.DoNotTransfer);
				IntPtr __ret = JNIEnv.ToLocalJniHandle (__this.SetAction (resId, onActionClickListener));
				return __ret;
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setAction' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='org.aviran.cookiebar2.OnActionClickListener']]"
			[Register ("setAction", "(ILorg/aviran/cookiebar2/OnActionClickListener;)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetAction_ILorg_aviran_cookiebar2_OnActionClickListener_Handler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetAction (int resId, global::Org.Aviran.Cookiebar2.IOnActionClickListener onActionClickListener)
			{
				const string __id = "setAction.(ILorg/aviran/cookiebar2/OnActionClickListener;)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [2];
					__args [0] = new JniArgumentValue (resId);
					__args [1] = new JniArgumentValue ((onActionClickListener == null) ? IntPtr.Zero : ((global::Java.Lang.Object) onActionClickListener).Handle);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
					global::System.GC.KeepAlive (onActionClickListener);
				}
			}

			static Delegate cb_setAction_Ljava_lang_String_Lorg_aviran_cookiebar2_OnActionClickListener_;
#pragma warning disable 0169
			static Delegate GetSetAction_Ljava_lang_String_Lorg_aviran_cookiebar2_OnActionClickListener_Handler ()
			{
				if (cb_setAction_Ljava_lang_String_Lorg_aviran_cookiebar2_OnActionClickListener_ == null)
					cb_setAction_Ljava_lang_String_Lorg_aviran_cookiebar2_OnActionClickListener_ = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPLL_L) n_SetAction_Ljava_lang_String_Lorg_aviran_cookiebar2_OnActionClickListener_);
				return cb_setAction_Ljava_lang_String_Lorg_aviran_cookiebar2_OnActionClickListener_;
			}

			static IntPtr n_SetAction_Ljava_lang_String_Lorg_aviran_cookiebar2_OnActionClickListener_ (IntPtr jnienv, IntPtr native__this, IntPtr native_action, IntPtr native_onActionClickListener)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				var action = JNIEnv.GetString (native_action, JniHandleOwnership.DoNotTransfer);
				var onActionClickListener = (global::Org.Aviran.Cookiebar2.IOnActionClickListener)global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.IOnActionClickListener> (native_onActionClickListener, JniHandleOwnership.DoNotTransfer);
				IntPtr __ret = JNIEnv.ToLocalJniHandle (__this.SetAction (action, onActionClickListener));
				return __ret;
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setAction' and count(parameter)=2 and parameter[1][@type='java.lang.String'] and parameter[2][@type='org.aviran.cookiebar2.OnActionClickListener']]"
			[Register ("setAction", "(Ljava/lang/String;Lorg/aviran/cookiebar2/OnActionClickListener;)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetAction_Ljava_lang_String_Lorg_aviran_cookiebar2_OnActionClickListener_Handler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetAction (string action, global::Org.Aviran.Cookiebar2.IOnActionClickListener onActionClickListener)
			{
				const string __id = "setAction.(Ljava/lang/String;Lorg/aviran/cookiebar2/OnActionClickListener;)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				IntPtr native_action = JNIEnv.NewString (action);
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [2];
					__args [0] = new JniArgumentValue (native_action);
					__args [1] = new JniArgumentValue ((onActionClickListener == null) ? IntPtr.Zero : ((global::Java.Lang.Object) onActionClickListener).Handle);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
					JNIEnv.DeleteLocalRef (native_action);
					global::System.GC.KeepAlive (onActionClickListener);
				}
			}

			static Delegate cb_setActionColor_I;
#pragma warning disable 0169
			static Delegate GetSetActionColor_IHandler ()
			{
				if (cb_setActionColor_I == null)
					cb_setActionColor_I = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPI_L) n_SetActionColor_I);
				return cb_setActionColor_I;
			}

			static IntPtr n_SetActionColor_I (IntPtr jnienv, IntPtr native__this, int actionColor)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetActionColor (actionColor));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setActionColor' and count(parameter)=1 and parameter[1][@type='int']]"
			[Register ("setActionColor", "(I)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetActionColor_IHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetActionColor (int actionColor)
			{
				const string __id = "setActionColor.(I)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (actionColor);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setAnimationIn_II;
#pragma warning disable 0169
			static Delegate GetSetAnimationIn_IIHandler ()
			{
				if (cb_setAnimationIn_II == null)
					cb_setAnimationIn_II = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPII_L) n_SetAnimationIn_II);
				return cb_setAnimationIn_II;
			}

			static IntPtr n_SetAnimationIn_II (IntPtr jnienv, IntPtr native__this, int topAnimation, int bottomAnimation)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetAnimationIn (topAnimation, bottomAnimation));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setAnimationIn' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='int']]"
			[Register ("setAnimationIn", "(II)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetAnimationIn_IIHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetAnimationIn (int topAnimation, int bottomAnimation)
			{
				const string __id = "setAnimationIn.(II)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [2];
					__args [0] = new JniArgumentValue (topAnimation);
					__args [1] = new JniArgumentValue (bottomAnimation);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setAnimationOut_II;
#pragma warning disable 0169
			static Delegate GetSetAnimationOut_IIHandler ()
			{
				if (cb_setAnimationOut_II == null)
					cb_setAnimationOut_II = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPII_L) n_SetAnimationOut_II);
				return cb_setAnimationOut_II;
			}

			static IntPtr n_SetAnimationOut_II (IntPtr jnienv, IntPtr native__this, int topAnimation, int bottomAnimation)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetAnimationOut (topAnimation, bottomAnimation));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setAnimationOut' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='int']]"
			[Register ("setAnimationOut", "(II)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetAnimationOut_IIHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetAnimationOut (int topAnimation, int bottomAnimation)
			{
				const string __id = "setAnimationOut.(II)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [2];
					__args [0] = new JniArgumentValue (topAnimation);
					__args [1] = new JniArgumentValue (bottomAnimation);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setBackgroundColor_I;
#pragma warning disable 0169
			static Delegate GetSetBackgroundColor_IHandler ()
			{
				if (cb_setBackgroundColor_I == null)
					cb_setBackgroundColor_I = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPI_L) n_SetBackgroundColor_I);
				return cb_setBackgroundColor_I;
			}

			static IntPtr n_SetBackgroundColor_I (IntPtr jnienv, IntPtr native__this, int backgroundColor)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetBackgroundColor (backgroundColor));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setBackgroundColor' and count(parameter)=1 and parameter[1][@type='int']]"
			[Register ("setBackgroundColor", "(I)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetBackgroundColor_IHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetBackgroundColor (int backgroundColor)
			{
				const string __id = "setBackgroundColor.(I)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (backgroundColor);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setCookieListener_Lorg_aviran_cookiebar2_CookieBarDismissListener_;
#pragma warning disable 0169
			static Delegate GetSetCookieListener_Lorg_aviran_cookiebar2_CookieBarDismissListener_Handler ()
			{
				if (cb_setCookieListener_Lorg_aviran_cookiebar2_CookieBarDismissListener_ == null)
					cb_setCookieListener_Lorg_aviran_cookiebar2_CookieBarDismissListener_ = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPL_L) n_SetCookieListener_Lorg_aviran_cookiebar2_CookieBarDismissListener_);
				return cb_setCookieListener_Lorg_aviran_cookiebar2_CookieBarDismissListener_;
			}

			static IntPtr n_SetCookieListener_Lorg_aviran_cookiebar2_CookieBarDismissListener_ (IntPtr jnienv, IntPtr native__this, IntPtr native_dismissListener)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				var dismissListener = (global::Org.Aviran.Cookiebar2.ICookieBarDismissListener)global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.ICookieBarDismissListener> (native_dismissListener, JniHandleOwnership.DoNotTransfer);
				IntPtr __ret = JNIEnv.ToLocalJniHandle (__this.SetCookieListener (dismissListener));
				return __ret;
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setCookieListener' and count(parameter)=1 and parameter[1][@type='org.aviran.cookiebar2.CookieBarDismissListener']]"
			[Register ("setCookieListener", "(Lorg/aviran/cookiebar2/CookieBarDismissListener;)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetCookieListener_Lorg_aviran_cookiebar2_CookieBarDismissListener_Handler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetCookieListener (global::Org.Aviran.Cookiebar2.ICookieBarDismissListener dismissListener)
			{
				const string __id = "setCookieListener.(Lorg/aviran/cookiebar2/CookieBarDismissListener;)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue ((dismissListener == null) ? IntPtr.Zero : ((global::Java.Lang.Object) dismissListener).Handle);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
					global::System.GC.KeepAlive (dismissListener);
				}
			}

			static Delegate cb_setCookiePosition_I;
#pragma warning disable 0169
			static Delegate GetSetCookiePosition_IHandler ()
			{
				if (cb_setCookiePosition_I == null)
					cb_setCookiePosition_I = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPI_L) n_SetCookiePosition_I);
				return cb_setCookiePosition_I;
			}

			static IntPtr n_SetCookiePosition_I (IntPtr jnienv, IntPtr native__this, int cookiePosition)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetCookiePosition (cookiePosition));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setCookiePosition' and count(parameter)=1 and parameter[1][@type='int']]"
			[Register ("setCookiePosition", "(I)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetCookiePosition_IHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetCookiePosition (int cookiePosition)
			{
				const string __id = "setCookiePosition.(I)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (cookiePosition);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setCustomView_I;
#pragma warning disable 0169
			static Delegate GetSetCustomView_IHandler ()
			{
				if (cb_setCustomView_I == null)
					cb_setCustomView_I = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPI_L) n_SetCustomView_I);
				return cb_setCustomView_I;
			}

			static IntPtr n_SetCustomView_I (IntPtr jnienv, IntPtr native__this, int customView)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetCustomView (customView));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setCustomView' and count(parameter)=1 and parameter[1][@type='int']]"
			[Register ("setCustomView", "(I)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetCustomView_IHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetCustomView (int customView)
			{
				const string __id = "setCustomView.(I)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (customView);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setCustomViewInitializer_Lorg_aviran_cookiebar2_CookieBar_CustomViewInitializer_;
#pragma warning disable 0169
			static Delegate GetSetCustomViewInitializer_Lorg_aviran_cookiebar2_CookieBar_CustomViewInitializer_Handler ()
			{
				if (cb_setCustomViewInitializer_Lorg_aviran_cookiebar2_CookieBar_CustomViewInitializer_ == null)
					cb_setCustomViewInitializer_Lorg_aviran_cookiebar2_CookieBar_CustomViewInitializer_ = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPL_L) n_SetCustomViewInitializer_Lorg_aviran_cookiebar2_CookieBar_CustomViewInitializer_);
				return cb_setCustomViewInitializer_Lorg_aviran_cookiebar2_CookieBar_CustomViewInitializer_;
			}

			static IntPtr n_SetCustomViewInitializer_Lorg_aviran_cookiebar2_CookieBar_CustomViewInitializer_ (IntPtr jnienv, IntPtr native__this, IntPtr native_viewInitializer)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				var viewInitializer = (global::Org.Aviran.Cookiebar2.CookieBar.ICustomViewInitializer)global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.ICustomViewInitializer> (native_viewInitializer, JniHandleOwnership.DoNotTransfer);
				IntPtr __ret = JNIEnv.ToLocalJniHandle (__this.SetCustomViewInitializer (viewInitializer));
				return __ret;
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setCustomViewInitializer' and count(parameter)=1 and parameter[1][@type='org.aviran.cookiebar2.CookieBar.CustomViewInitializer']]"
			[Register ("setCustomViewInitializer", "(Lorg/aviran/cookiebar2/CookieBar$CustomViewInitializer;)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetCustomViewInitializer_Lorg_aviran_cookiebar2_CookieBar_CustomViewInitializer_Handler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetCustomViewInitializer (global::Org.Aviran.Cookiebar2.CookieBar.ICustomViewInitializer viewInitializer)
			{
				const string __id = "setCustomViewInitializer.(Lorg/aviran/cookiebar2/CookieBar$CustomViewInitializer;)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue ((viewInitializer == null) ? IntPtr.Zero : ((global::Java.Lang.Object) viewInitializer).Handle);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
					global::System.GC.KeepAlive (viewInitializer);
				}
			}

			static Delegate cb_setDuration_J;
#pragma warning disable 0169
			static Delegate GetSetDuration_JHandler ()
			{
				if (cb_setDuration_J == null)
					cb_setDuration_J = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPJ_L) n_SetDuration_J);
				return cb_setDuration_J;
			}

			static IntPtr n_SetDuration_J (IntPtr jnienv, IntPtr native__this, long duration)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetDuration (duration));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setDuration' and count(parameter)=1 and parameter[1][@type='long']]"
			[Register ("setDuration", "(J)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetDuration_JHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetDuration (long duration)
			{
				const string __id = "setDuration.(J)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (duration);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setEnableAutoDismiss_Z;
#pragma warning disable 0169
			static Delegate GetSetEnableAutoDismiss_ZHandler ()
			{
				if (cb_setEnableAutoDismiss_Z == null)
					cb_setEnableAutoDismiss_Z = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPZ_L) n_SetEnableAutoDismiss_Z);
				return cb_setEnableAutoDismiss_Z;
			}

			static IntPtr n_SetEnableAutoDismiss_Z (IntPtr jnienv, IntPtr native__this, bool enableAutoDismiss)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetEnableAutoDismiss (enableAutoDismiss));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setEnableAutoDismiss' and count(parameter)=1 and parameter[1][@type='boolean']]"
			[Register ("setEnableAutoDismiss", "(Z)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetEnableAutoDismiss_ZHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetEnableAutoDismiss (bool enableAutoDismiss)
			{
				const string __id = "setEnableAutoDismiss.(Z)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (enableAutoDismiss);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setIcon_I;
#pragma warning disable 0169
			static Delegate GetSetIcon_IHandler ()
			{
				if (cb_setIcon_I == null)
					cb_setIcon_I = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPI_L) n_SetIcon_I);
				return cb_setIcon_I;
			}

			static IntPtr n_SetIcon_I (IntPtr jnienv, IntPtr native__this, int iconResId)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetIcon (iconResId));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setIcon' and count(parameter)=1 and parameter[1][@type='int']]"
			[Register ("setIcon", "(I)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetIcon_IHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetIcon (int iconResId)
			{
				const string __id = "setIcon.(I)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (iconResId);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setIconAnimation_I;
#pragma warning disable 0169
			static Delegate GetSetIconAnimation_IHandler ()
			{
				if (cb_setIconAnimation_I == null)
					cb_setIconAnimation_I = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPI_L) n_SetIconAnimation_I);
				return cb_setIconAnimation_I;
			}

			static IntPtr n_SetIconAnimation_I (IntPtr jnienv, IntPtr native__this, int iconAnimation)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetIconAnimation (iconAnimation));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setIconAnimation' and count(parameter)=1 and parameter[1][@type='int']]"
			[Register ("setIconAnimation", "(I)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetIconAnimation_IHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetIconAnimation (int iconAnimation)
			{
				const string __id = "setIconAnimation.(I)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (iconAnimation);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setLayoutGravity_I;
#pragma warning disable 0169
			[Obsolete]
			static Delegate GetSetLayoutGravity_IHandler ()
			{
				if (cb_setLayoutGravity_I == null)
					cb_setLayoutGravity_I = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPI_L) n_SetLayoutGravity_I);
				return cb_setLayoutGravity_I;
			}

			[Obsolete]
			static IntPtr n_SetLayoutGravity_I (IntPtr jnienv, IntPtr native__this, int layoutGravity)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetLayoutGravity (layoutGravity));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setLayoutGravity' and count(parameter)=1 and parameter[1][@type='int']]"
			[Obsolete (@"deprecated")]
			[Register ("setLayoutGravity", "(I)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetLayoutGravity_IHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetLayoutGravity (int layoutGravity)
			{
				const string __id = "setLayoutGravity.(I)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (layoutGravity);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setMessage_I;
#pragma warning disable 0169
			static Delegate GetSetMessage_IHandler ()
			{
				if (cb_setMessage_I == null)
					cb_setMessage_I = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPI_L) n_SetMessage_I);
				return cb_setMessage_I;
			}

			static IntPtr n_SetMessage_I (IntPtr jnienv, IntPtr native__this, int resId)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetMessage (resId));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setMessage' and count(parameter)=1 and parameter[1][@type='int']]"
			[Register ("setMessage", "(I)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetMessage_IHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetMessage (int resId)
			{
				const string __id = "setMessage.(I)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (resId);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setMessage_Ljava_lang_String_;
#pragma warning disable 0169
			static Delegate GetSetMessage_Ljava_lang_String_Handler ()
			{
				if (cb_setMessage_Ljava_lang_String_ == null)
					cb_setMessage_Ljava_lang_String_ = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPL_L) n_SetMessage_Ljava_lang_String_);
				return cb_setMessage_Ljava_lang_String_;
			}

			static IntPtr n_SetMessage_Ljava_lang_String_ (IntPtr jnienv, IntPtr native__this, IntPtr native_message)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				var message = JNIEnv.GetString (native_message, JniHandleOwnership.DoNotTransfer);
				IntPtr __ret = JNIEnv.ToLocalJniHandle (__this.SetMessage (message));
				return __ret;
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setMessage' and count(parameter)=1 and parameter[1][@type='java.lang.String']]"
			[Register ("setMessage", "(Ljava/lang/String;)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetMessage_Ljava_lang_String_Handler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetMessage (string message)
			{
				const string __id = "setMessage.(Ljava/lang/String;)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				IntPtr native_message = JNIEnv.NewString (message);
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (native_message);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
					JNIEnv.DeleteLocalRef (native_message);
				}
			}

			static Delegate cb_setMessageColor_I;
#pragma warning disable 0169
			static Delegate GetSetMessageColor_IHandler ()
			{
				if (cb_setMessageColor_I == null)
					cb_setMessageColor_I = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPI_L) n_SetMessageColor_I);
				return cb_setMessageColor_I;
			}

			static IntPtr n_SetMessageColor_I (IntPtr jnienv, IntPtr native__this, int messageColor)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetMessageColor (messageColor));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setMessageColor' and count(parameter)=1 and parameter[1][@type='int']]"
			[Register ("setMessageColor", "(I)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetMessageColor_IHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetMessageColor (int messageColor)
			{
				const string __id = "setMessageColor.(I)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (messageColor);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setSwipeToDismiss_Z;
#pragma warning disable 0169
			static Delegate GetSetSwipeToDismiss_ZHandler ()
			{
				if (cb_setSwipeToDismiss_Z == null)
					cb_setSwipeToDismiss_Z = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPZ_L) n_SetSwipeToDismiss_Z);
				return cb_setSwipeToDismiss_Z;
			}

			static IntPtr n_SetSwipeToDismiss_Z (IntPtr jnienv, IntPtr native__this, bool enableSwipeToDismiss)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetSwipeToDismiss (enableSwipeToDismiss));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setSwipeToDismiss' and count(parameter)=1 and parameter[1][@type='boolean']]"
			[Register ("setSwipeToDismiss", "(Z)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetSwipeToDismiss_ZHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetSwipeToDismiss (bool enableSwipeToDismiss)
			{
				const string __id = "setSwipeToDismiss.(Z)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (enableSwipeToDismiss);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setTitle_I;
#pragma warning disable 0169
			static Delegate GetSetTitle_IHandler ()
			{
				if (cb_setTitle_I == null)
					cb_setTitle_I = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPI_L) n_SetTitle_I);
				return cb_setTitle_I;
			}

			static IntPtr n_SetTitle_I (IntPtr jnienv, IntPtr native__this, int resId)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetTitle (resId));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setTitle' and count(parameter)=1 and parameter[1][@type='int']]"
			[Register ("setTitle", "(I)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetTitle_IHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetTitle (int resId)
			{
				const string __id = "setTitle.(I)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (resId);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_setTitle_Ljava_lang_String_;
#pragma warning disable 0169
			static Delegate GetSetTitle_Ljava_lang_String_Handler ()
			{
				if (cb_setTitle_Ljava_lang_String_ == null)
					cb_setTitle_Ljava_lang_String_ = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPL_L) n_SetTitle_Ljava_lang_String_);
				return cb_setTitle_Ljava_lang_String_;
			}

			static IntPtr n_SetTitle_Ljava_lang_String_ (IntPtr jnienv, IntPtr native__this, IntPtr native_title)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				var title = JNIEnv.GetString (native_title, JniHandleOwnership.DoNotTransfer);
				IntPtr __ret = JNIEnv.ToLocalJniHandle (__this.SetTitle (title));
				return __ret;
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setTitle' and count(parameter)=1 and parameter[1][@type='java.lang.String']]"
			[Register ("setTitle", "(Ljava/lang/String;)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetTitle_Ljava_lang_String_Handler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetTitle (string title)
			{
				const string __id = "setTitle.(Ljava/lang/String;)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				IntPtr native_title = JNIEnv.NewString (title);
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (native_title);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
					JNIEnv.DeleteLocalRef (native_title);
				}
			}

			static Delegate cb_setTitleColor_I;
#pragma warning disable 0169
			static Delegate GetSetTitleColor_IHandler ()
			{
				if (cb_setTitleColor_I == null)
					cb_setTitleColor_I = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPI_L) n_SetTitleColor_I);
				return cb_setTitleColor_I;
			}

			static IntPtr n_SetTitleColor_I (IntPtr jnienv, IntPtr native__this, int titleColor)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.SetTitleColor (titleColor));
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='setTitleColor' and count(parameter)=1 and parameter[1][@type='int']]"
			[Register ("setTitleColor", "(I)Lorg/aviran/cookiebar2/CookieBar$Builder;", "GetSetTitleColor_IHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder SetTitleColor (int titleColor)
			{
				const string __id = "setTitleColor.(I)Lorg/aviran/cookiebar2/CookieBar$Builder;";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (titleColor);
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, __args);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

			static Delegate cb_show;
#pragma warning disable 0169
			static Delegate GetShowHandler ()
			{
				if (cb_show == null)
					cb_show = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_L) n_Show);
				return cb_show;
			}

			static IntPtr n_Show (IntPtr jnienv, IntPtr native__this)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				return JNIEnv.ToLocalJniHandle (__this.Show ());
			}
#pragma warning restore 0169

			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar.Builder']/method[@name='show' and count(parameter)=0]"
			[Register ("show", "()Lorg/aviran/cookiebar2/CookieBar;", "GetShowHandler")]
			public virtual unsafe global::Org.Aviran.Cookiebar2.CookieBar Show ()
			{
				const string __id = "show.()Lorg/aviran/cookiebar2/CookieBar;";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, null);
					return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}

		}

		// Metadata.xml XPath interface reference: path="/api/package[@name='org.aviran.cookiebar2']/interface[@name='CookieBar.CustomViewInitializer']"
		[Register ("org/aviran/cookiebar2/CookieBar$CustomViewInitializer", "", "Org.Aviran.Cookiebar2.CookieBar/ICustomViewInitializerInvoker")]
		public partial interface ICustomViewInitializer : IJavaObject, IJavaPeerable {
			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/interface[@name='CookieBar.CustomViewInitializer']/method[@name='initView' and count(parameter)=1 and parameter[1][@type='android.view.View']]"
			[Register ("initView", "(Landroid/view/View;)V", "GetInitView_Landroid_view_View_Handler:Org.Aviran.Cookiebar2.CookieBar/ICustomViewInitializerInvoker, myBindingClassLibrary")]
			void InitView (global::Android.Views.View p0);

		}

		[global::Android.Runtime.Register ("org/aviran/cookiebar2/CookieBar$CustomViewInitializer", DoNotGenerateAcw=true)]
		internal partial class ICustomViewInitializerInvoker : global::Java.Lang.Object, ICustomViewInitializer {
			static readonly JniPeerMembers _members = new XAPeerMembers ("org/aviran/cookiebar2/CookieBar$CustomViewInitializer", typeof (ICustomViewInitializerInvoker));

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

			public static ICustomViewInitializer GetObject (IntPtr handle, JniHandleOwnership transfer)
			{
				return global::Java.Lang.Object.GetObject<ICustomViewInitializer> (handle, transfer);
			}

			static IntPtr Validate (IntPtr handle)
			{
				if (!JNIEnv.IsInstanceOf (handle, java_class_ref))
					throw new InvalidCastException ($"Unable to convert instance of type '{JNIEnv.GetClassNameFromInstance (handle)}' to type 'org.aviran.cookiebar2.CookieBar.CustomViewInitializer'.");
				return handle;
			}

			protected override void Dispose (bool disposing)
			{
				if (this.class_ref != IntPtr.Zero)
					JNIEnv.DeleteGlobalRef (this.class_ref);
				this.class_ref = IntPtr.Zero;
				base.Dispose (disposing);
			}

			public ICustomViewInitializerInvoker (IntPtr handle, JniHandleOwnership transfer) : base (Validate (handle), transfer)
			{
				IntPtr local_ref = JNIEnv.GetObjectClass (((global::Java.Lang.Object) this).Handle);
				this.class_ref = JNIEnv.NewGlobalRef (local_ref);
				JNIEnv.DeleteLocalRef (local_ref);
			}

			static Delegate cb_initView_Landroid_view_View_;
#pragma warning disable 0169
			static Delegate GetInitView_Landroid_view_View_Handler ()
			{
				if (cb_initView_Landroid_view_View_ == null)
					cb_initView_Landroid_view_View_ = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPL_V) n_InitView_Landroid_view_View_);
				return cb_initView_Landroid_view_View_;
			}

			static void n_InitView_Landroid_view_View_ (IntPtr jnienv, IntPtr native__this, IntPtr native_p0)
			{
				var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.ICustomViewInitializer> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
				var p0 = global::Java.Lang.Object.GetObject<global::Android.Views.View> (native_p0, JniHandleOwnership.DoNotTransfer);
				__this.InitView (p0);
			}
#pragma warning restore 0169

			IntPtr id_initView_Landroid_view_View_;
			public unsafe void InitView (global::Android.Views.View p0)
			{
				if (id_initView_Landroid_view_View_ == IntPtr.Zero)
					id_initView_Landroid_view_View_ = JNIEnv.GetMethodID (class_ref, "initView", "(Landroid/view/View;)V");
				JValue* __args = stackalloc JValue [1];
				__args [0] = new JValue ((p0 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p0).Handle);
				JNIEnv.CallVoidMethod (((global::Java.Lang.Object) this).Handle, id_initView_Landroid_view_View_, __args);
			}

		}

		static readonly JniPeerMembers _members = new XAPeerMembers ("org/aviran/cookiebar2/CookieBar", typeof (CookieBar));

		internal static IntPtr class_ref {
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
			get { return _members.JniPeerType.PeerReference.Handle; }
		}

		[global::System.Diagnostics.DebuggerBrowsable (global::System.Diagnostics.DebuggerBrowsableState.Never)]
		[global::System.ComponentModel.EditorBrowsable (global::System.ComponentModel.EditorBrowsableState.Never)]
		protected override global::System.Type ThresholdType {
			get { return _members.ManagedPeerType; }
		}

		protected CookieBar (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
		{
		}

		static Delegate cb_getView;
#pragma warning disable 0169
		static Delegate GetGetViewHandler ()
		{
			if (cb_getView == null)
				cb_getView = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_L) n_GetView);
			return cb_getView;
		}

		static IntPtr n_GetView (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return JNIEnv.ToLocalJniHandle (__this.View);
		}
#pragma warning restore 0169

		public virtual unsafe global::Android.Views.View View {
			// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar']/method[@name='getView' and count(parameter)=0]"
			[Register ("getView", "()Landroid/view/View;", "GetGetViewHandler")]
			get {
				const string __id = "getView.()Landroid/view/View;";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, null);
					return global::Java.Lang.Object.GetObject<global::Android.Views.View> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar']/method[@name='build' and count(parameter)=1 and parameter[1][@type='android.app.Activity']]"
		[Register ("build", "(Landroid/app/Activity;)Lorg/aviran/cookiebar2/CookieBar$Builder;", "")]
		public static unsafe global::Org.Aviran.Cookiebar2.CookieBar.Builder Build (global::Android.App.Activity activity)
		{
			const string __id = "build.(Landroid/app/Activity;)Lorg/aviran/cookiebar2/CookieBar$Builder;";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((activity == null) ? IntPtr.Zero : ((global::Java.Lang.Object) activity).Handle);
				var __rm = _members.StaticMethods.InvokeObjectMethod (__id, __args);
				return global::Java.Lang.Object.GetObject<global::Org.Aviran.Cookiebar2.CookieBar.Builder> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
			} finally {
				global::System.GC.KeepAlive (activity);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='org.aviran.cookiebar2']/class[@name='CookieBar']/method[@name='dismiss' and count(parameter)=1 and parameter[1][@type='android.app.Activity']]"
		[Register ("dismiss", "(Landroid/app/Activity;)V", "")]
		public static unsafe void Dismiss (global::Android.App.Activity activity)
		{
			const string __id = "dismiss.(Landroid/app/Activity;)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((activity == null) ? IntPtr.Zero : ((global::Java.Lang.Object) activity).Handle);
				_members.StaticMethods.InvokeVoidMethod (__id, __args);
			} finally {
				global::System.GC.KeepAlive (activity);
			}
		}

	}
}
