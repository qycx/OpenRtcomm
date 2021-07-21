using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Com.Qycx.Gleslibrary {

	// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='FlatShadedProgram']"
	[global::Android.Runtime.Register ("com/qycx/gleslibrary/FlatShadedProgram", DoNotGenerateAcw=true)]
	public partial class FlatShadedProgram : global::Java.Lang.Object {
		static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/gleslibrary/FlatShadedProgram", typeof (FlatShadedProgram));

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

		protected FlatShadedProgram (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
		{
		}

		// Metadata.xml XPath constructor reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='FlatShadedProgram']/constructor[@name='FlatShadedProgram' and count(parameter)=0]"
		[Register (".ctor", "()V", "")]
		public unsafe FlatShadedProgram () : base (IntPtr.Zero, JniHandleOwnership.DoNotTransfer)
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

		static Delegate cb_draw_arrayFarrayFLjava_nio_FloatBuffer_IIII;
#pragma warning disable 0169
		static Delegate GetDraw_arrayFarrayFLjava_nio_FloatBuffer_IIIIHandler ()
		{
			if (cb_draw_arrayFarrayFLjava_nio_FloatBuffer_IIII == null)
				cb_draw_arrayFarrayFLjava_nio_FloatBuffer_IIII = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPLLLIIII_V) n_Draw_arrayFarrayFLjava_nio_FloatBuffer_IIII);
			return cb_draw_arrayFarrayFLjava_nio_FloatBuffer_IIII;
		}

		static void n_Draw_arrayFarrayFLjava_nio_FloatBuffer_IIII (IntPtr jnienv, IntPtr native__this, IntPtr native_mvpMatrix, IntPtr native_color, IntPtr native_vertexBuffer, int firstVertex, int vertexCount, int coordsPerVertex, int vertexStride)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.FlatShadedProgram> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			var mvpMatrix = (float[]) JNIEnv.GetArray (native_mvpMatrix, JniHandleOwnership.DoNotTransfer, typeof (float));
			var color = (float[]) JNIEnv.GetArray (native_color, JniHandleOwnership.DoNotTransfer, typeof (float));
			var vertexBuffer = global::Java.Lang.Object.GetObject<global::Java.Nio.FloatBuffer> (native_vertexBuffer, JniHandleOwnership.DoNotTransfer);
			__this.Draw (mvpMatrix, color, vertexBuffer, firstVertex, vertexCount, coordsPerVertex, vertexStride);
			if (mvpMatrix != null)
				JNIEnv.CopyArray (mvpMatrix, native_mvpMatrix);
			if (color != null)
				JNIEnv.CopyArray (color, native_color);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='FlatShadedProgram']/method[@name='draw' and count(parameter)=7 and parameter[1][@type='float[]'] and parameter[2][@type='float[]'] and parameter[3][@type='java.nio.FloatBuffer'] and parameter[4][@type='int'] and parameter[5][@type='int'] and parameter[6][@type='int'] and parameter[7][@type='int']]"
		[Register ("draw", "([F[FLjava/nio/FloatBuffer;IIII)V", "GetDraw_arrayFarrayFLjava_nio_FloatBuffer_IIIIHandler")]
		public virtual unsafe void Draw (float[] mvpMatrix, float[] color, global::Java.Nio.FloatBuffer vertexBuffer, int firstVertex, int vertexCount, int coordsPerVertex, int vertexStride)
		{
			const string __id = "draw.([F[FLjava/nio/FloatBuffer;IIII)V";
			IntPtr native_mvpMatrix = JNIEnv.NewArray (mvpMatrix);
			IntPtr native_color = JNIEnv.NewArray (color);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [7];
				__args [0] = new JniArgumentValue (native_mvpMatrix);
				__args [1] = new JniArgumentValue (native_color);
				__args [2] = new JniArgumentValue ((vertexBuffer == null) ? IntPtr.Zero : ((global::Java.Lang.Object) vertexBuffer).Handle);
				__args [3] = new JniArgumentValue (firstVertex);
				__args [4] = new JniArgumentValue (vertexCount);
				__args [5] = new JniArgumentValue (coordsPerVertex);
				__args [6] = new JniArgumentValue (vertexStride);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
				if (mvpMatrix != null) {
					JNIEnv.CopyArray (native_mvpMatrix, mvpMatrix);
					JNIEnv.DeleteLocalRef (native_mvpMatrix);
				}
				if (color != null) {
					JNIEnv.CopyArray (native_color, color);
					JNIEnv.DeleteLocalRef (native_color);
				}
				global::System.GC.KeepAlive (mvpMatrix);
				global::System.GC.KeepAlive (color);
				global::System.GC.KeepAlive (vertexBuffer);
			}
		}

		static Delegate cb_release;
#pragma warning disable 0169
		static Delegate GetReleaseHandler ()
		{
			if (cb_release == null)
				cb_release = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_V) n_Release);
			return cb_release;
		}

		static void n_Release (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.FlatShadedProgram> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.Release ();
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='FlatShadedProgram']/method[@name='release' and count(parameter)=0]"
		[Register ("release", "()V", "GetReleaseHandler")]
		public virtual unsafe void Release ()
		{
			const string __id = "release.()V";
			try {
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, null);
			} finally {
			}
		}

	}
}
