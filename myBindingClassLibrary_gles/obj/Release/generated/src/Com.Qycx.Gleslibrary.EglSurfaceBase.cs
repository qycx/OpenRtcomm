using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Com.Qycx.Gleslibrary {

	// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglSurfaceBase']"
	[global::Android.Runtime.Register ("com/qycx/gleslibrary/EglSurfaceBase", DoNotGenerateAcw=true)]
	public partial class EglSurfaceBase : global::Java.Lang.Object {
		// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglSurfaceBase']/field[@name='TAG']"
		[Register ("TAG")]
		protected const string Tag = (string) "Grafika";


		// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglSurfaceBase']/field[@name='mEglCore']"
		[Register ("mEglCore")]
		public global::Com.Qycx.Gleslibrary.EglCore MEglCore {
			get {
				const string __id = "mEglCore.Lcom/qycx/gleslibrary/EglCore;";

				var __v = _members.InstanceFields.GetObjectValue (__id, this);
				return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.EglCore> (__v.Handle, JniHandleOwnership.TransferLocalRef);
			}
			set {
				const string __id = "mEglCore.Lcom/qycx/gleslibrary/EglCore;";

				IntPtr native_value = global::Android.Runtime.JNIEnv.ToLocalJniHandle (value);
				try {
					_members.InstanceFields.SetValue (__id, this, new JniObjectReference (native_value));
				} finally {
					global::Android.Runtime.JNIEnv.DeleteLocalRef (native_value);
				}
			}
		}

		static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/gleslibrary/EglSurfaceBase", typeof (EglSurfaceBase));

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

		protected EglSurfaceBase (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
		{
		}

		// Metadata.xml XPath constructor reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglSurfaceBase']/constructor[@name='EglSurfaceBase' and count(parameter)=1 and parameter[1][@type='com.qycx.gleslibrary.EglCore']]"
		[Register (".ctor", "(Lcom/qycx/gleslibrary/EglCore;)V", "")]
		protected unsafe EglSurfaceBase (global::Com.Qycx.Gleslibrary.EglCore eglCore) : base (IntPtr.Zero, JniHandleOwnership.DoNotTransfer)
		{
			const string __id = "(Lcom/qycx/gleslibrary/EglCore;)V";

			if (((global::Java.Lang.Object) this).Handle != IntPtr.Zero)
				return;

			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((eglCore == null) ? IntPtr.Zero : ((global::Java.Lang.Object) eglCore).Handle);
				var __r = _members.InstanceMethods.StartCreateInstance (__id, ((object) this).GetType (), __args);
				SetHandle (__r.Handle, JniHandleOwnership.TransferLocalRef);
				_members.InstanceMethods.FinishCreateInstance (__id, this, __args);
			} finally {
				global::System.GC.KeepAlive (eglCore);
			}
		}

		static Delegate cb_getHeight;
#pragma warning disable 0169
		static Delegate GetGetHeightHandler ()
		{
			if (cb_getHeight == null)
				cb_getHeight = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_I) n_GetHeight);
			return cb_getHeight;
		}

		static int n_GetHeight (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.EglSurfaceBase> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.Height;
		}
#pragma warning restore 0169

		public virtual unsafe int Height {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglSurfaceBase']/method[@name='getHeight' and count(parameter)=0]"
			[Register ("getHeight", "()I", "GetGetHeightHandler")]
			get {
				const string __id = "getHeight.()I";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualInt32Method (__id, this, null);
					return __rm;
				} finally {
				}
			}
		}

		static Delegate cb_getWidth;
#pragma warning disable 0169
		static Delegate GetGetWidthHandler ()
		{
			if (cb_getWidth == null)
				cb_getWidth = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_I) n_GetWidth);
			return cb_getWidth;
		}

		static int n_GetWidth (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.EglSurfaceBase> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.Width;
		}
#pragma warning restore 0169

		public virtual unsafe int Width {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglSurfaceBase']/method[@name='getWidth' and count(parameter)=0]"
			[Register ("getWidth", "()I", "GetGetWidthHandler")]
			get {
				const string __id = "getWidth.()I";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualInt32Method (__id, this, null);
					return __rm;
				} finally {
				}
			}
		}

		static Delegate cb_createOffscreenSurface_II;
#pragma warning disable 0169
		static Delegate GetCreateOffscreenSurface_IIHandler ()
		{
			if (cb_createOffscreenSurface_II == null)
				cb_createOffscreenSurface_II = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPII_V) n_CreateOffscreenSurface_II);
			return cb_createOffscreenSurface_II;
		}

		static void n_CreateOffscreenSurface_II (IntPtr jnienv, IntPtr native__this, int width, int height)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.EglSurfaceBase> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.CreateOffscreenSurface (width, height);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglSurfaceBase']/method[@name='createOffscreenSurface' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='int']]"
		[Register ("createOffscreenSurface", "(II)V", "GetCreateOffscreenSurface_IIHandler")]
		public virtual unsafe void CreateOffscreenSurface (int width, int height)
		{
			const string __id = "createOffscreenSurface.(II)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (width);
				__args [1] = new JniArgumentValue (height);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
			}
		}

		static Delegate cb_createWindowSurface_Ljava_lang_Object_;
#pragma warning disable 0169
		static Delegate GetCreateWindowSurface_Ljava_lang_Object_Handler ()
		{
			if (cb_createWindowSurface_Ljava_lang_Object_ == null)
				cb_createWindowSurface_Ljava_lang_Object_ = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPL_V) n_CreateWindowSurface_Ljava_lang_Object_);
			return cb_createWindowSurface_Ljava_lang_Object_;
		}

		static void n_CreateWindowSurface_Ljava_lang_Object_ (IntPtr jnienv, IntPtr native__this, IntPtr native_surface)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.EglSurfaceBase> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			var surface = global::Java.Lang.Object.GetObject<global::Java.Lang.Object> (native_surface, JniHandleOwnership.DoNotTransfer);
			__this.CreateWindowSurface (surface);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglSurfaceBase']/method[@name='createWindowSurface' and count(parameter)=1 and parameter[1][@type='java.lang.Object']]"
		[Register ("createWindowSurface", "(Ljava/lang/Object;)V", "GetCreateWindowSurface_Ljava_lang_Object_Handler")]
		public virtual unsafe void CreateWindowSurface (global::Java.Lang.Object surface)
		{
			const string __id = "createWindowSurface.(Ljava/lang/Object;)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((surface == null) ? IntPtr.Zero : ((global::Java.Lang.Object) surface).Handle);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
				global::System.GC.KeepAlive (surface);
			}
		}

		static Delegate cb_makeCurrent;
#pragma warning disable 0169
		static Delegate GetMakeCurrentHandler ()
		{
			if (cb_makeCurrent == null)
				cb_makeCurrent = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_V) n_MakeCurrent);
			return cb_makeCurrent;
		}

		static void n_MakeCurrent (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.EglSurfaceBase> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.MakeCurrent ();
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglSurfaceBase']/method[@name='makeCurrent' and count(parameter)=0]"
		[Register ("makeCurrent", "()V", "GetMakeCurrentHandler")]
		public virtual unsafe void MakeCurrent ()
		{
			const string __id = "makeCurrent.()V";
			try {
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, null);
			} finally {
			}
		}

		static Delegate cb_makeCurrentReadFrom_Lcom_qycx_gleslibrary_EglSurfaceBase_;
#pragma warning disable 0169
		static Delegate GetMakeCurrentReadFrom_Lcom_qycx_gleslibrary_EglSurfaceBase_Handler ()
		{
			if (cb_makeCurrentReadFrom_Lcom_qycx_gleslibrary_EglSurfaceBase_ == null)
				cb_makeCurrentReadFrom_Lcom_qycx_gleslibrary_EglSurfaceBase_ = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPL_V) n_MakeCurrentReadFrom_Lcom_qycx_gleslibrary_EglSurfaceBase_);
			return cb_makeCurrentReadFrom_Lcom_qycx_gleslibrary_EglSurfaceBase_;
		}

		static void n_MakeCurrentReadFrom_Lcom_qycx_gleslibrary_EglSurfaceBase_ (IntPtr jnienv, IntPtr native__this, IntPtr native_readSurface)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.EglSurfaceBase> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			var readSurface = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.EglSurfaceBase> (native_readSurface, JniHandleOwnership.DoNotTransfer);
			__this.MakeCurrentReadFrom (readSurface);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglSurfaceBase']/method[@name='makeCurrentReadFrom' and count(parameter)=1 and parameter[1][@type='com.qycx.gleslibrary.EglSurfaceBase']]"
		[Register ("makeCurrentReadFrom", "(Lcom/qycx/gleslibrary/EglSurfaceBase;)V", "GetMakeCurrentReadFrom_Lcom_qycx_gleslibrary_EglSurfaceBase_Handler")]
		public virtual unsafe void MakeCurrentReadFrom (global::Com.Qycx.Gleslibrary.EglSurfaceBase readSurface)
		{
			const string __id = "makeCurrentReadFrom.(Lcom/qycx/gleslibrary/EglSurfaceBase;)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((readSurface == null) ? IntPtr.Zero : ((global::Java.Lang.Object) readSurface).Handle);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
				global::System.GC.KeepAlive (readSurface);
			}
		}

		static Delegate cb_releaseEglSurface;
#pragma warning disable 0169
		static Delegate GetReleaseEglSurfaceHandler ()
		{
			if (cb_releaseEglSurface == null)
				cb_releaseEglSurface = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_V) n_ReleaseEglSurface);
			return cb_releaseEglSurface;
		}

		static void n_ReleaseEglSurface (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.EglSurfaceBase> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.ReleaseEglSurface ();
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglSurfaceBase']/method[@name='releaseEglSurface' and count(parameter)=0]"
		[Register ("releaseEglSurface", "()V", "GetReleaseEglSurfaceHandler")]
		public virtual unsafe void ReleaseEglSurface ()
		{
			const string __id = "releaseEglSurface.()V";
			try {
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, null);
			} finally {
			}
		}

		static Delegate cb_saveFrame_Ljava_io_File_;
#pragma warning disable 0169
		static Delegate GetSaveFrame_Ljava_io_File_Handler ()
		{
			if (cb_saveFrame_Ljava_io_File_ == null)
				cb_saveFrame_Ljava_io_File_ = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPL_V) n_SaveFrame_Ljava_io_File_);
			return cb_saveFrame_Ljava_io_File_;
		}

		static void n_SaveFrame_Ljava_io_File_ (IntPtr jnienv, IntPtr native__this, IntPtr native_file)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.EglSurfaceBase> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			var file = global::Java.Lang.Object.GetObject<global::Java.IO.File> (native_file, JniHandleOwnership.DoNotTransfer);
			__this.SaveFrame (file);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglSurfaceBase']/method[@name='saveFrame' and count(parameter)=1 and parameter[1][@type='java.io.File']]"
		[Register ("saveFrame", "(Ljava/io/File;)V", "GetSaveFrame_Ljava_io_File_Handler")]
		public virtual unsafe void SaveFrame (global::Java.IO.File file)
		{
			const string __id = "saveFrame.(Ljava/io/File;)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((file == null) ? IntPtr.Zero : ((global::Java.Lang.Object) file).Handle);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
				global::System.GC.KeepAlive (file);
			}
		}

		static Delegate cb_setPresentationTime_J;
#pragma warning disable 0169
		static Delegate GetSetPresentationTime_JHandler ()
		{
			if (cb_setPresentationTime_J == null)
				cb_setPresentationTime_J = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPJ_V) n_SetPresentationTime_J);
			return cb_setPresentationTime_J;
		}

		static void n_SetPresentationTime_J (IntPtr jnienv, IntPtr native__this, long nsecs)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.EglSurfaceBase> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.SetPresentationTime (nsecs);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglSurfaceBase']/method[@name='setPresentationTime' and count(parameter)=1 and parameter[1][@type='long']]"
		[Register ("setPresentationTime", "(J)V", "GetSetPresentationTime_JHandler")]
		public virtual unsafe void SetPresentationTime (long nsecs)
		{
			const string __id = "setPresentationTime.(J)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue (nsecs);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
			}
		}

		static Delegate cb_swapBuffers;
#pragma warning disable 0169
		static Delegate GetSwapBuffersHandler ()
		{
			if (cb_swapBuffers == null)
				cb_swapBuffers = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_Z) n_SwapBuffers);
			return cb_swapBuffers;
		}

		static bool n_SwapBuffers (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.EglSurfaceBase> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.SwapBuffers ();
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='EglSurfaceBase']/method[@name='swapBuffers' and count(parameter)=0]"
		[Register ("swapBuffers", "()Z", "GetSwapBuffersHandler")]
		public virtual unsafe bool SwapBuffers ()
		{
			const string __id = "swapBuffers.()Z";
			try {
				var __rm = _members.InstanceMethods.InvokeVirtualBooleanMethod (__id, this, null);
				return __rm;
			} finally {
			}
		}

	}
}
