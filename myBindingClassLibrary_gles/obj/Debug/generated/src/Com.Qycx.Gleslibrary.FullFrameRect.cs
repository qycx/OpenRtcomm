using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Com.Qycx.Gleslibrary {

	// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='FullFrameRect']"
	[global::Android.Runtime.Register ("com/qycx/gleslibrary/FullFrameRect", DoNotGenerateAcw=true)]
	public partial class FullFrameRect : global::Java.Lang.Object {
		static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/gleslibrary/FullFrameRect", typeof (FullFrameRect));

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

		protected FullFrameRect (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
		{
		}

		// Metadata.xml XPath constructor reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='FullFrameRect']/constructor[@name='FullFrameRect' and count(parameter)=1 and parameter[1][@type='com.qycx.gleslibrary.Texture2dProgram']]"
		[Register (".ctor", "(Lcom/qycx/gleslibrary/Texture2dProgram;)V", "")]
		public unsafe FullFrameRect (global::Com.Qycx.Gleslibrary.Texture2dProgram program) : base (IntPtr.Zero, JniHandleOwnership.DoNotTransfer)
		{
			const string __id = "(Lcom/qycx/gleslibrary/Texture2dProgram;)V";

			if (((global::Java.Lang.Object) this).Handle != IntPtr.Zero)
				return;

			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((program == null) ? IntPtr.Zero : ((global::Java.Lang.Object) program).Handle);
				var __r = _members.InstanceMethods.StartCreateInstance (__id, ((object) this).GetType (), __args);
				SetHandle (__r.Handle, JniHandleOwnership.TransferLocalRef);
				_members.InstanceMethods.FinishCreateInstance (__id, this, __args);
			} finally {
				global::System.GC.KeepAlive (program);
			}
		}

		static Delegate cb_getProgram;
#pragma warning disable 0169
		static Delegate GetGetProgramHandler ()
		{
			if (cb_getProgram == null)
				cb_getProgram = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_L) n_GetProgram);
			return cb_getProgram;
		}

		static IntPtr n_GetProgram (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.FullFrameRect> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return JNIEnv.ToLocalJniHandle (__this.Program);
		}
#pragma warning restore 0169

		public virtual unsafe global::Com.Qycx.Gleslibrary.Texture2dProgram Program {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='FullFrameRect']/method[@name='getProgram' and count(parameter)=0]"
			[Register ("getProgram", "()Lcom/qycx/gleslibrary/Texture2dProgram;", "GetGetProgramHandler")]
			get {
				const string __id = "getProgram.()Lcom/qycx/gleslibrary/Texture2dProgram;";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, null);
					return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}
		}

		static Delegate cb_changeProgram_Lcom_qycx_gleslibrary_Texture2dProgram_;
#pragma warning disable 0169
		static Delegate GetChangeProgram_Lcom_qycx_gleslibrary_Texture2dProgram_Handler ()
		{
			if (cb_changeProgram_Lcom_qycx_gleslibrary_Texture2dProgram_ == null)
				cb_changeProgram_Lcom_qycx_gleslibrary_Texture2dProgram_ = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPL_V) n_ChangeProgram_Lcom_qycx_gleslibrary_Texture2dProgram_);
			return cb_changeProgram_Lcom_qycx_gleslibrary_Texture2dProgram_;
		}

		static void n_ChangeProgram_Lcom_qycx_gleslibrary_Texture2dProgram_ (IntPtr jnienv, IntPtr native__this, IntPtr native_program)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.FullFrameRect> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			var program = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram> (native_program, JniHandleOwnership.DoNotTransfer);
			__this.ChangeProgram (program);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='FullFrameRect']/method[@name='changeProgram' and count(parameter)=1 and parameter[1][@type='com.qycx.gleslibrary.Texture2dProgram']]"
		[Register ("changeProgram", "(Lcom/qycx/gleslibrary/Texture2dProgram;)V", "GetChangeProgram_Lcom_qycx_gleslibrary_Texture2dProgram_Handler")]
		public virtual unsafe void ChangeProgram (global::Com.Qycx.Gleslibrary.Texture2dProgram program)
		{
			const string __id = "changeProgram.(Lcom/qycx/gleslibrary/Texture2dProgram;)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((program == null) ? IntPtr.Zero : ((global::Java.Lang.Object) program).Handle);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
				global::System.GC.KeepAlive (program);
			}
		}

		static Delegate cb_createTextureObject;
#pragma warning disable 0169
		static Delegate GetCreateTextureObjectHandler ()
		{
			if (cb_createTextureObject == null)
				cb_createTextureObject = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_I) n_CreateTextureObject);
			return cb_createTextureObject;
		}

		static int n_CreateTextureObject (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.FullFrameRect> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.CreateTextureObject ();
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='FullFrameRect']/method[@name='createTextureObject' and count(parameter)=0]"
		[Register ("createTextureObject", "()I", "GetCreateTextureObjectHandler")]
		public virtual unsafe int CreateTextureObject ()
		{
			const string __id = "createTextureObject.()I";
			try {
				var __rm = _members.InstanceMethods.InvokeVirtualInt32Method (__id, this, null);
				return __rm;
			} finally {
			}
		}

		static Delegate cb_drawFrame_IarrayF;
#pragma warning disable 0169
		static Delegate GetDrawFrame_IarrayFHandler ()
		{
			if (cb_drawFrame_IarrayF == null)
				cb_drawFrame_IarrayF = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPIL_V) n_DrawFrame_IarrayF);
			return cb_drawFrame_IarrayF;
		}

		static void n_DrawFrame_IarrayF (IntPtr jnienv, IntPtr native__this, int textureId, IntPtr native_texMatrix)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.FullFrameRect> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			var texMatrix = (float[]) JNIEnv.GetArray (native_texMatrix, JniHandleOwnership.DoNotTransfer, typeof (float));
			__this.DrawFrame (textureId, texMatrix);
			if (texMatrix != null)
				JNIEnv.CopyArray (texMatrix, native_texMatrix);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='FullFrameRect']/method[@name='drawFrame' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='float[]']]"
		[Register ("drawFrame", "(I[F)V", "GetDrawFrame_IarrayFHandler")]
		public virtual unsafe void DrawFrame (int textureId, float[] texMatrix)
		{
			const string __id = "drawFrame.(I[F)V";
			IntPtr native_texMatrix = JNIEnv.NewArray (texMatrix);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (textureId);
				__args [1] = new JniArgumentValue (native_texMatrix);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
				if (texMatrix != null) {
					JNIEnv.CopyArray (native_texMatrix, texMatrix);
					JNIEnv.DeleteLocalRef (native_texMatrix);
				}
				global::System.GC.KeepAlive (texMatrix);
			}
		}

		static Delegate cb_release_Z;
#pragma warning disable 0169
		static Delegate GetRelease_ZHandler ()
		{
			if (cb_release_Z == null)
				cb_release_Z = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPZ_V) n_Release_Z);
			return cb_release_Z;
		}

		static void n_Release_Z (IntPtr jnienv, IntPtr native__this, bool doEglCleanup)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.FullFrameRect> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.Release (doEglCleanup);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='FullFrameRect']/method[@name='release' and count(parameter)=1 and parameter[1][@type='boolean']]"
		[Register ("release", "(Z)V", "GetRelease_ZHandler")]
		public virtual unsafe void Release (bool doEglCleanup)
		{
			const string __id = "release.(Z)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue (doEglCleanup);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
			}
		}

	}
}
