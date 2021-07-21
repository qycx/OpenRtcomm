using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Com.Qycx.Gleslibrary {

	// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']"
	[global::Android.Runtime.Register ("com/qycx/gleslibrary/EglCore", DoNotGenerateAcw=true)]
	public sealed partial class EglCore : global::Java.Lang.Object {
		// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/field[@name='FLAG_RECORDABLE']"
		[Register ("FLAG_RECORDABLE")]
		public const int FlagRecordable = (int) 1;

		// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/field[@name='FLAG_TRY_GLES3']"
		[Register ("FLAG_TRY_GLES3")]
		public const int FlagTryGles3 = (int) 2;


		// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/field[@name='mEGLConfig']"
		[Register ("mEGLConfig")]
		public global::Android.Opengl.EGLConfig MEGLConfig {
			get {
				const string __id = "mEGLConfig.Landroid/opengl/EGLConfig;";

				var __v = _members.InstanceFields.GetObjectValue (__id, this);
				return global::Java.Lang.Object.GetObject<global::Android.Opengl.EGLConfig> (__v.Handle, JniHandleOwnership.TransferLocalRef);
			}
			set {
				const string __id = "mEGLConfig.Landroid/opengl/EGLConfig;";

				IntPtr native_value = global::Android.Runtime.JNIEnv.ToLocalJniHandle (value);
				try {
					_members.InstanceFields.SetValue (__id, this, new JniObjectReference (native_value));
				} finally {
					global::Android.Runtime.JNIEnv.DeleteLocalRef (native_value);
				}
			}
		}


		// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/field[@name='mEGLContext']"
		[Register ("mEGLContext")]
		public global::Android.Opengl.EGLContext MEGLContext {
			get {
				const string __id = "mEGLContext.Landroid/opengl/EGLContext;";

				var __v = _members.InstanceFields.GetObjectValue (__id, this);
				return global::Java.Lang.Object.GetObject<global::Android.Opengl.EGLContext> (__v.Handle, JniHandleOwnership.TransferLocalRef);
			}
			set {
				const string __id = "mEGLContext.Landroid/opengl/EGLContext;";

				IntPtr native_value = global::Android.Runtime.JNIEnv.ToLocalJniHandle (value);
				try {
					_members.InstanceFields.SetValue (__id, this, new JniObjectReference (native_value));
				} finally {
					global::Android.Runtime.JNIEnv.DeleteLocalRef (native_value);
				}
			}
		}


		// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/field[@name='mEGLDisplay']"
		[Register ("mEGLDisplay")]
		public global::Android.Opengl.EGLDisplay MEGLDisplay {
			get {
				const string __id = "mEGLDisplay.Landroid/opengl/EGLDisplay;";

				var __v = _members.InstanceFields.GetObjectValue (__id, this);
				return global::Java.Lang.Object.GetObject<global::Android.Opengl.EGLDisplay> (__v.Handle, JniHandleOwnership.TransferLocalRef);
			}
			set {
				const string __id = "mEGLDisplay.Landroid/opengl/EGLDisplay;";

				IntPtr native_value = global::Android.Runtime.JNIEnv.ToLocalJniHandle (value);
				try {
					_members.InstanceFields.SetValue (__id, this, new JniObjectReference (native_value));
				} finally {
					global::Android.Runtime.JNIEnv.DeleteLocalRef (native_value);
				}
			}
		}

		static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/gleslibrary/EglCore", typeof (EglCore));

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

		internal EglCore (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
		{
		}

		// Metadata.xml XPath constructor reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/constructor[@name='EglCore' and count(parameter)=0]"
		[Register (".ctor", "()V", "")]
		public unsafe EglCore () : base (IntPtr.Zero, JniHandleOwnership.DoNotTransfer)
		{
			const string __id = "()V";

			if (((global::Java.Lang.Object) this).Handle != IntPtr.Zero)
				return;

			try {
				var __r = _members.InstanceMethods.StartCreateInstance (__id, ((object) this).GetType (), null);
				SetHandle (__r.Handle, JniHandleOwnership.TransferLocalRef);
				_members.InstanceMethods.FinishCreateInstance (__id, this, null);
			} finally {
			}
		}

		// Metadata.xml XPath constructor reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/constructor[@name='EglCore' and count(parameter)=2 and parameter[1][@type='android.opengl.EGLContext'] and parameter[2][@type='int']]"
		[Register (".ctor", "(Landroid/opengl/EGLContext;I)V", "")]
		public unsafe EglCore (global::Android.Opengl.EGLContext sharedContext, int flags) : base (IntPtr.Zero, JniHandleOwnership.DoNotTransfer)
		{
			const string __id = "(Landroid/opengl/EGLContext;I)V";

			if (((global::Java.Lang.Object) this).Handle != IntPtr.Zero)
				return;

			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue ((sharedContext == null) ? IntPtr.Zero : ((global::Java.Lang.Object) sharedContext).Handle);
				__args [1] = new JniArgumentValue (flags);
				var __r = _members.InstanceMethods.StartCreateInstance (__id, ((object) this).GetType (), __args);
				SetHandle (__r.Handle, JniHandleOwnership.TransferLocalRef);
				_members.InstanceMethods.FinishCreateInstance (__id, this, __args);
			} finally {
				global::System.GC.KeepAlive (sharedContext);
			}
		}

		public unsafe int GlVersion {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/method[@name='getGlVersion' and count(parameter)=0]"
			[Register ("getGlVersion", "()I", "")]
			get {
				const string __id = "getGlVersion.()I";
				try {
					var __rm = _members.InstanceMethods.InvokeAbstractInt32Method (__id, this, null);
					return __rm;
				} finally {
				}
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/method[@name='createOffscreenSurface' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='int']]"
		[Register ("createOffscreenSurface", "(II)Landroid/opengl/EGLSurface;", "")]
		public unsafe global::Android.Opengl.EGLSurface CreateOffscreenSurface (int width, int height)
		{
			const string __id = "createOffscreenSurface.(II)Landroid/opengl/EGLSurface;";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (width);
				__args [1] = new JniArgumentValue (height);
				var __rm = _members.InstanceMethods.InvokeAbstractObjectMethod (__id, this, __args);
				return global::Java.Lang.Object.GetObject<global::Android.Opengl.EGLSurface> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/method[@name='createWindowSurface' and count(parameter)=1 and parameter[1][@type='java.lang.Object']]"
		[Register ("createWindowSurface", "(Ljava/lang/Object;)Landroid/opengl/EGLSurface;", "")]
		public unsafe global::Android.Opengl.EGLSurface CreateWindowSurface (global::Java.Lang.Object surface)
		{
			const string __id = "createWindowSurface.(Ljava/lang/Object;)Landroid/opengl/EGLSurface;";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((surface == null) ? IntPtr.Zero : ((global::Java.Lang.Object) surface).Handle);
				var __rm = _members.InstanceMethods.InvokeAbstractObjectMethod (__id, this, __args);
				return global::Java.Lang.Object.GetObject<global::Android.Opengl.EGLSurface> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
			} finally {
				global::System.GC.KeepAlive (surface);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/method[@name='isCurrent' and count(parameter)=1 and parameter[1][@type='android.opengl.EGLSurface']]"
		[Register ("isCurrent", "(Landroid/opengl/EGLSurface;)Z", "")]
		public unsafe bool IsCurrent (global::Android.Opengl.EGLSurface eglSurface)
		{
			const string __id = "isCurrent.(Landroid/opengl/EGLSurface;)Z";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((eglSurface == null) ? IntPtr.Zero : ((global::Java.Lang.Object) eglSurface).Handle);
				var __rm = _members.InstanceMethods.InvokeAbstractBooleanMethod (__id, this, __args);
				return __rm;
			} finally {
				global::System.GC.KeepAlive (eglSurface);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/method[@name='logCurrent' and count(parameter)=1 and parameter[1][@type='java.lang.String']]"
		[Register ("logCurrent", "(Ljava/lang/String;)V", "")]
		public static unsafe void LogCurrent (string msg)
		{
			const string __id = "logCurrent.(Ljava/lang/String;)V";
			IntPtr native_msg = JNIEnv.NewString (msg);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue (native_msg);
				_members.StaticMethods.InvokeVoidMethod (__id, __args);
			} finally {
				JNIEnv.DeleteLocalRef (native_msg);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/method[@name='makeCurrent' and count(parameter)=1 and parameter[1][@type='android.opengl.EGLSurface']]"
		[Register ("makeCurrent", "(Landroid/opengl/EGLSurface;)V", "")]
		public unsafe void MakeCurrent (global::Android.Opengl.EGLSurface eglSurface)
		{
			const string __id = "makeCurrent.(Landroid/opengl/EGLSurface;)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((eglSurface == null) ? IntPtr.Zero : ((global::Java.Lang.Object) eglSurface).Handle);
				_members.InstanceMethods.InvokeAbstractVoidMethod (__id, this, __args);
			} finally {
				global::System.GC.KeepAlive (eglSurface);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/method[@name='makeCurrent' and count(parameter)=2 and parameter[1][@type='android.opengl.EGLSurface'] and parameter[2][@type='android.opengl.EGLSurface']]"
		[Register ("makeCurrent", "(Landroid/opengl/EGLSurface;Landroid/opengl/EGLSurface;)V", "")]
		public unsafe void MakeCurrent (global::Android.Opengl.EGLSurface drawSurface, global::Android.Opengl.EGLSurface readSurface)
		{
			const string __id = "makeCurrent.(Landroid/opengl/EGLSurface;Landroid/opengl/EGLSurface;)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue ((drawSurface == null) ? IntPtr.Zero : ((global::Java.Lang.Object) drawSurface).Handle);
				__args [1] = new JniArgumentValue ((readSurface == null) ? IntPtr.Zero : ((global::Java.Lang.Object) readSurface).Handle);
				_members.InstanceMethods.InvokeAbstractVoidMethod (__id, this, __args);
			} finally {
				global::System.GC.KeepAlive (drawSurface);
				global::System.GC.KeepAlive (readSurface);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/method[@name='makeNothingCurrent' and count(parameter)=0]"
		[Register ("makeNothingCurrent", "()V", "")]
		public unsafe void MakeNothingCurrent ()
		{
			const string __id = "makeNothingCurrent.()V";
			try {
				_members.InstanceMethods.InvokeAbstractVoidMethod (__id, this, null);
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/method[@name='queryString' and count(parameter)=1 and parameter[1][@type='int']]"
		[Register ("queryString", "(I)Ljava/lang/String;", "")]
		public unsafe string QueryString (int what)
		{
			const string __id = "queryString.(I)Ljava/lang/String;";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue (what);
				var __rm = _members.InstanceMethods.InvokeAbstractObjectMethod (__id, this, __args);
				return JNIEnv.GetString (__rm.Handle, JniHandleOwnership.TransferLocalRef);
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/method[@name='querySurface' and count(parameter)=2 and parameter[1][@type='android.opengl.EGLSurface'] and parameter[2][@type='int']]"
		[Register ("querySurface", "(Landroid/opengl/EGLSurface;I)I", "")]
		public unsafe int QuerySurface (global::Android.Opengl.EGLSurface eglSurface, int what)
		{
			const string __id = "querySurface.(Landroid/opengl/EGLSurface;I)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue ((eglSurface == null) ? IntPtr.Zero : ((global::Java.Lang.Object) eglSurface).Handle);
				__args [1] = new JniArgumentValue (what);
				var __rm = _members.InstanceMethods.InvokeAbstractInt32Method (__id, this, __args);
				return __rm;
			} finally {
				global::System.GC.KeepAlive (eglSurface);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/method[@name='release' and count(parameter)=0]"
		[Register ("release", "()V", "")]
		public unsafe void Release ()
		{
			const string __id = "release.()V";
			try {
				_members.InstanceMethods.InvokeAbstractVoidMethod (__id, this, null);
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/method[@name='releaseSurface' and count(parameter)=1 and parameter[1][@type='android.opengl.EGLSurface']]"
		[Register ("releaseSurface", "(Landroid/opengl/EGLSurface;)V", "")]
		public unsafe void ReleaseSurface (global::Android.Opengl.EGLSurface eglSurface)
		{
			const string __id = "releaseSurface.(Landroid/opengl/EGLSurface;)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((eglSurface == null) ? IntPtr.Zero : ((global::Java.Lang.Object) eglSurface).Handle);
				_members.InstanceMethods.InvokeAbstractVoidMethod (__id, this, __args);
			} finally {
				global::System.GC.KeepAlive (eglSurface);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/method[@name='setPresentationTime' and count(parameter)=2 and parameter[1][@type='android.opengl.EGLSurface'] and parameter[2][@type='long']]"
		[Register ("setPresentationTime", "(Landroid/opengl/EGLSurface;J)V", "")]
		public unsafe void SetPresentationTime (global::Android.Opengl.EGLSurface eglSurface, long nsecs)
		{
			const string __id = "setPresentationTime.(Landroid/opengl/EGLSurface;J)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue ((eglSurface == null) ? IntPtr.Zero : ((global::Java.Lang.Object) eglSurface).Handle);
				__args [1] = new JniArgumentValue (nsecs);
				_members.InstanceMethods.InvokeAbstractVoidMethod (__id, this, __args);
			} finally {
				global::System.GC.KeepAlive (eglSurface);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglCore']/method[@name='swapBuffers' and count(parameter)=1 and parameter[1][@type='android.opengl.EGLSurface']]"
		[Register ("swapBuffers", "(Landroid/opengl/EGLSurface;)Z", "")]
		public unsafe bool SwapBuffers (global::Android.Opengl.EGLSurface eglSurface)
		{
			const string __id = "swapBuffers.(Landroid/opengl/EGLSurface;)Z";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((eglSurface == null) ? IntPtr.Zero : ((global::Java.Lang.Object) eglSurface).Handle);
				var __rm = _members.InstanceMethods.InvokeAbstractBooleanMethod (__id, this, __args);
				return __rm;
			} finally {
				global::System.GC.KeepAlive (eglSurface);
			}
		}

	}
}
