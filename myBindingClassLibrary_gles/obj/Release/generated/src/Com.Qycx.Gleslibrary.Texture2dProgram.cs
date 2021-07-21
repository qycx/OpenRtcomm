using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Com.Qycx.Gleslibrary {

	// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram']"
	[global::Android.Runtime.Register ("com/qycx/gleslibrary/Texture2dProgram", DoNotGenerateAcw=true)]
	public partial class Texture2dProgram : global::Java.Lang.Object {
		// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram']/field[@name='KERNEL_SIZE']"
		[Register ("KERNEL_SIZE")]
		public const int KernelSize = (int) 9;

		// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram.ProgramType']"
		[global::Android.Runtime.Register ("com/qycx/gleslibrary/Texture2dProgram$ProgramType", DoNotGenerateAcw=true)]
		public sealed partial class ProgramType : global::Java.Lang.Enum {

			// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram.ProgramType']/field[@name='TEXTURE_2D']"
			[Register ("TEXTURE_2D")]
			public static global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType Texture2d {
				get {
					const string __id = "TEXTURE_2D.Lcom/qycx/gleslibrary/Texture2dProgram$ProgramType;";

					var __v = _members.StaticFields.GetObjectValue (__id);
					return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType> (__v.Handle, JniHandleOwnership.TransferLocalRef);
				}
			}


			// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram.ProgramType']/field[@name='TEXTURE_EXT']"
			[Register ("TEXTURE_EXT")]
			public static global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType TextureExt {
				get {
					const string __id = "TEXTURE_EXT.Lcom/qycx/gleslibrary/Texture2dProgram$ProgramType;";

					var __v = _members.StaticFields.GetObjectValue (__id);
					return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType> (__v.Handle, JniHandleOwnership.TransferLocalRef);
				}
			}


			// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram.ProgramType']/field[@name='TEXTURE_EXT_BW']"
			[Register ("TEXTURE_EXT_BW")]
			public static global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType TextureExtBw {
				get {
					const string __id = "TEXTURE_EXT_BW.Lcom/qycx/gleslibrary/Texture2dProgram$ProgramType;";

					var __v = _members.StaticFields.GetObjectValue (__id);
					return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType> (__v.Handle, JniHandleOwnership.TransferLocalRef);
				}
			}


			// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram.ProgramType']/field[@name='TEXTURE_EXT_FILT']"
			[Register ("TEXTURE_EXT_FILT")]
			public static global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType TextureExtFilt {
				get {
					const string __id = "TEXTURE_EXT_FILT.Lcom/qycx/gleslibrary/Texture2dProgram$ProgramType;";

					var __v = _members.StaticFields.GetObjectValue (__id);
					return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType> (__v.Handle, JniHandleOwnership.TransferLocalRef);
				}
			}

			static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/gleslibrary/Texture2dProgram$ProgramType", typeof (ProgramType));

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

			internal ProgramType (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
			{
			}

			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram.ProgramType']/method[@name='valueOf' and count(parameter)=1 and parameter[1][@type='java.lang.String']]"
			[Register ("valueOf", "(Ljava/lang/String;)Lcom/qycx/gleslibrary/Texture2dProgram$ProgramType;", "")]
			public static unsafe global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType ValueOf (string name)
			{
				const string __id = "valueOf.(Ljava/lang/String;)Lcom/qycx/gleslibrary/Texture2dProgram$ProgramType;";
				IntPtr native_name = JNIEnv.NewString (name);
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (native_name);
					var __rm = _members.StaticMethods.InvokeObjectMethod (__id, __args);
					return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
					JNIEnv.DeleteLocalRef (native_name);
				}
			}

			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram.ProgramType']/method[@name='values' and count(parameter)=0]"
			[Register ("values", "()[Lcom/qycx/gleslibrary/Texture2dProgram$ProgramType;", "")]
			public static unsafe global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType[] Values ()
			{
				const string __id = "values.()[Lcom/qycx/gleslibrary/Texture2dProgram$ProgramType;";
				try {
					var __rm = _members.StaticMethods.InvokeObjectMethod (__id, null);
					return (global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType[]) JNIEnv.GetArray (__rm.Handle, JniHandleOwnership.TransferLocalRef, typeof (global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType));
				} finally {
				}
			}

		}

		static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/gleslibrary/Texture2dProgram", typeof (Texture2dProgram));

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

		protected Texture2dProgram (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
		{
		}

		// Metadata.xml XPath constructor reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram']/constructor[@name='Texture2dProgram' and count(parameter)=1 and parameter[1][@type='com.qycx.gleslibrary.Texture2dProgram.ProgramType']]"
		[Register (".ctor", "(Lcom/qycx/gleslibrary/Texture2dProgram$ProgramType;)V", "")]
		public unsafe Texture2dProgram (global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType programType) : base (IntPtr.Zero, JniHandleOwnership.DoNotTransfer)
		{
			const string __id = "(Lcom/qycx/gleslibrary/Texture2dProgram$ProgramType;)V";

			if (((global::Java.Lang.Object) this).Handle != IntPtr.Zero)
				return;

			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((programType == null) ? IntPtr.Zero : ((global::Java.Lang.Object) programType).Handle);
				var __r = _members.InstanceMethods.StartCreateInstance (__id, ((object) this).GetType (), __args);
				SetHandle (__r.Handle, JniHandleOwnership.TransferLocalRef);
				_members.InstanceMethods.FinishCreateInstance (__id, this, __args);
			} finally {
				global::System.GC.KeepAlive (programType);
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
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.CreateTextureObject ();
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram']/method[@name='createTextureObject' and count(parameter)=0]"
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

		static Delegate cb_draw_arrayFLjava_nio_FloatBuffer_IIIIarrayFLjava_nio_FloatBuffer_II;
#pragma warning disable 0169
		static Delegate GetDraw_arrayFLjava_nio_FloatBuffer_IIIIarrayFLjava_nio_FloatBuffer_IIHandler ()
		{
			if (cb_draw_arrayFLjava_nio_FloatBuffer_IIIIarrayFLjava_nio_FloatBuffer_II == null)
				cb_draw_arrayFLjava_nio_FloatBuffer_IIIIarrayFLjava_nio_FloatBuffer_II = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPLLIIIILLII_V) n_Draw_arrayFLjava_nio_FloatBuffer_IIIIarrayFLjava_nio_FloatBuffer_II);
			return cb_draw_arrayFLjava_nio_FloatBuffer_IIIIarrayFLjava_nio_FloatBuffer_II;
		}

		static void n_Draw_arrayFLjava_nio_FloatBuffer_IIIIarrayFLjava_nio_FloatBuffer_II (IntPtr jnienv, IntPtr native__this, IntPtr native_mvpMatrix, IntPtr native_vertexBuffer, int firstVertex, int vertexCount, int coordsPerVertex, int vertexStride, IntPtr native_texMatrix, IntPtr native_texBuffer, int textureId, int texStride)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			var mvpMatrix = (float[]) JNIEnv.GetArray (native_mvpMatrix, JniHandleOwnership.DoNotTransfer, typeof (float));
			var vertexBuffer = global::Java.Lang.Object.GetObject<global::Java.Nio.FloatBuffer> (native_vertexBuffer, JniHandleOwnership.DoNotTransfer);
			var texMatrix = (float[]) JNIEnv.GetArray (native_texMatrix, JniHandleOwnership.DoNotTransfer, typeof (float));
			var texBuffer = global::Java.Lang.Object.GetObject<global::Java.Nio.FloatBuffer> (native_texBuffer, JniHandleOwnership.DoNotTransfer);
			__this.Draw (mvpMatrix, vertexBuffer, firstVertex, vertexCount, coordsPerVertex, vertexStride, texMatrix, texBuffer, textureId, texStride);
			if (mvpMatrix != null)
				JNIEnv.CopyArray (mvpMatrix, native_mvpMatrix);
			if (texMatrix != null)
				JNIEnv.CopyArray (texMatrix, native_texMatrix);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram']/method[@name='draw' and count(parameter)=10 and parameter[1][@type='float[]'] and parameter[2][@type='java.nio.FloatBuffer'] and parameter[3][@type='int'] and parameter[4][@type='int'] and parameter[5][@type='int'] and parameter[6][@type='int'] and parameter[7][@type='float[]'] and parameter[8][@type='java.nio.FloatBuffer'] and parameter[9][@type='int'] and parameter[10][@type='int']]"
		[Register ("draw", "([FLjava/nio/FloatBuffer;IIII[FLjava/nio/FloatBuffer;II)V", "GetDraw_arrayFLjava_nio_FloatBuffer_IIIIarrayFLjava_nio_FloatBuffer_IIHandler")]
		public virtual unsafe void Draw (float[] mvpMatrix, global::Java.Nio.FloatBuffer vertexBuffer, int firstVertex, int vertexCount, int coordsPerVertex, int vertexStride, float[] texMatrix, global::Java.Nio.FloatBuffer texBuffer, int textureId, int texStride)
		{
			const string __id = "draw.([FLjava/nio/FloatBuffer;IIII[FLjava/nio/FloatBuffer;II)V";
			IntPtr native_mvpMatrix = JNIEnv.NewArray (mvpMatrix);
			IntPtr native_texMatrix = JNIEnv.NewArray (texMatrix);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [10];
				__args [0] = new JniArgumentValue (native_mvpMatrix);
				__args [1] = new JniArgumentValue ((vertexBuffer == null) ? IntPtr.Zero : ((global::Java.Lang.Object) vertexBuffer).Handle);
				__args [2] = new JniArgumentValue (firstVertex);
				__args [3] = new JniArgumentValue (vertexCount);
				__args [4] = new JniArgumentValue (coordsPerVertex);
				__args [5] = new JniArgumentValue (vertexStride);
				__args [6] = new JniArgumentValue (native_texMatrix);
				__args [7] = new JniArgumentValue ((texBuffer == null) ? IntPtr.Zero : ((global::Java.Lang.Object) texBuffer).Handle);
				__args [8] = new JniArgumentValue (textureId);
				__args [9] = new JniArgumentValue (texStride);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
				if (mvpMatrix != null) {
					JNIEnv.CopyArray (native_mvpMatrix, mvpMatrix);
					JNIEnv.DeleteLocalRef (native_mvpMatrix);
				}
				if (texMatrix != null) {
					JNIEnv.CopyArray (native_texMatrix, texMatrix);
					JNIEnv.DeleteLocalRef (native_texMatrix);
				}
				global::System.GC.KeepAlive (mvpMatrix);
				global::System.GC.KeepAlive (vertexBuffer);
				global::System.GC.KeepAlive (texMatrix);
				global::System.GC.KeepAlive (texBuffer);
			}
		}

		static Delegate cb_getProgramType;
#pragma warning disable 0169
		static Delegate GetGetProgramTypeHandler ()
		{
			if (cb_getProgramType == null)
				cb_getProgramType = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_L) n_GetProgramType);
			return cb_getProgramType;
		}

		static IntPtr n_GetProgramType (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return JNIEnv.ToLocalJniHandle (__this.GetProgramType ());
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram']/method[@name='getProgramType' and count(parameter)=0]"
		[Register ("getProgramType", "()Lcom/qycx/gleslibrary/Texture2dProgram$ProgramType;", "GetGetProgramTypeHandler")]
		public virtual unsafe global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType GetProgramType ()
		{
			const string __id = "getProgramType.()Lcom/qycx/gleslibrary/Texture2dProgram$ProgramType;";
			try {
				var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, null);
				return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram.ProgramType> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
			} finally {
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
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.Release ();
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram']/method[@name='release' and count(parameter)=0]"
		[Register ("release", "()V", "GetReleaseHandler")]
		public virtual unsafe void Release ()
		{
			const string __id = "release.()V";
			try {
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, null);
			} finally {
			}
		}

		static Delegate cb_setKernel_arrayFF;
#pragma warning disable 0169
		static Delegate GetSetKernel_arrayFFHandler ()
		{
			if (cb_setKernel_arrayFF == null)
				cb_setKernel_arrayFF = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPLF_V) n_SetKernel_arrayFF);
			return cb_setKernel_arrayFF;
		}

		static void n_SetKernel_arrayFF (IntPtr jnienv, IntPtr native__this, IntPtr native_values, float colorAdj)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			var values = (float[]) JNIEnv.GetArray (native_values, JniHandleOwnership.DoNotTransfer, typeof (float));
			__this.SetKernel (values, colorAdj);
			if (values != null)
				JNIEnv.CopyArray (values, native_values);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram']/method[@name='setKernel' and count(parameter)=2 and parameter[1][@type='float[]'] and parameter[2][@type='float']]"
		[Register ("setKernel", "([FF)V", "GetSetKernel_arrayFFHandler")]
		public virtual unsafe void SetKernel (float[] values, float colorAdj)
		{
			const string __id = "setKernel.([FF)V";
			IntPtr native_values = JNIEnv.NewArray (values);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (native_values);
				__args [1] = new JniArgumentValue (colorAdj);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
				if (values != null) {
					JNIEnv.CopyArray (native_values, values);
					JNIEnv.DeleteLocalRef (native_values);
				}
				global::System.GC.KeepAlive (values);
			}
		}

		static Delegate cb_setTexSize_II;
#pragma warning disable 0169
		static Delegate GetSetTexSize_IIHandler ()
		{
			if (cb_setTexSize_II == null)
				cb_setTexSize_II = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPII_V) n_SetTexSize_II);
			return cb_setTexSize_II;
		}

		static void n_SetTexSize_II (IntPtr jnienv, IntPtr native__this, int width, int height)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.SetTexSize (width, height);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Texture2dProgram']/method[@name='setTexSize' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='int']]"
		[Register ("setTexSize", "(II)V", "GetSetTexSize_IIHandler")]
		public virtual unsafe void SetTexSize (int width, int height)
		{
			const string __id = "setTexSize.(II)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (width);
				__args [1] = new JniArgumentValue (height);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
			}
		}

	}
}
