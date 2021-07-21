using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Com.Qycx.Gleslibrary {

	// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']"
	[global::Android.Runtime.Register ("com/qycx/gleslibrary/Sprite2d", DoNotGenerateAcw=true)]
	public partial class Sprite2d : global::Java.Lang.Object {
		static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/gleslibrary/Sprite2d", typeof (Sprite2d));

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

		protected Sprite2d (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
		{
		}

		// Metadata.xml XPath constructor reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/constructor[@name='Sprite2d' and count(parameter)=1 and parameter[1][@type='com.qycx.gleslibrary.Drawable2d']]"
		[Register (".ctor", "(Lcom/qycx/gleslibrary/Drawable2d;)V", "")]
		public unsafe Sprite2d (global::Com.Qycx.Gleslibrary.Drawable2d drawable) : base (IntPtr.Zero, JniHandleOwnership.DoNotTransfer)
		{
			const string __id = "(Lcom/qycx/gleslibrary/Drawable2d;)V";

			if (((global::Java.Lang.Object) this).Handle != IntPtr.Zero)
				return;

			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((drawable == null) ? IntPtr.Zero : ((global::Java.Lang.Object) drawable).Handle);
				var __r = _members.InstanceMethods.StartCreateInstance (__id, ((object) this).GetType (), __args);
				SetHandle (__r.Handle, JniHandleOwnership.TransferLocalRef);
				_members.InstanceMethods.FinishCreateInstance (__id, this, __args);
			} finally {
				global::System.GC.KeepAlive (drawable);
			}
		}

		static Delegate cb_getPositionX;
#pragma warning disable 0169
		static Delegate GetGetPositionXHandler ()
		{
			if (cb_getPositionX == null)
				cb_getPositionX = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_F) n_GetPositionX);
			return cb_getPositionX;
		}

		static float n_GetPositionX (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Sprite2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.PositionX;
		}
#pragma warning restore 0169

		public virtual unsafe float PositionX {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/method[@name='getPositionX' and count(parameter)=0]"
			[Register ("getPositionX", "()F", "GetGetPositionXHandler")]
			get {
				const string __id = "getPositionX.()F";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualSingleMethod (__id, this, null);
					return __rm;
				} finally {
				}
			}
		}

		static Delegate cb_getPositionY;
#pragma warning disable 0169
		static Delegate GetGetPositionYHandler ()
		{
			if (cb_getPositionY == null)
				cb_getPositionY = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_F) n_GetPositionY);
			return cb_getPositionY;
		}

		static float n_GetPositionY (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Sprite2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.PositionY;
		}
#pragma warning restore 0169

		public virtual unsafe float PositionY {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/method[@name='getPositionY' and count(parameter)=0]"
			[Register ("getPositionY", "()F", "GetGetPositionYHandler")]
			get {
				const string __id = "getPositionY.()F";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualSingleMethod (__id, this, null);
					return __rm;
				} finally {
				}
			}
		}

		static Delegate cb_getRotation;
#pragma warning disable 0169
		static Delegate GetGetRotationHandler ()
		{
			if (cb_getRotation == null)
				cb_getRotation = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_F) n_GetRotation);
			return cb_getRotation;
		}

		static float n_GetRotation (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Sprite2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.Rotation;
		}
#pragma warning restore 0169

		static Delegate cb_setRotation_F;
#pragma warning disable 0169
		static Delegate GetSetRotation_FHandler ()
		{
			if (cb_setRotation_F == null)
				cb_setRotation_F = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPF_V) n_SetRotation_F);
			return cb_setRotation_F;
		}

		static void n_SetRotation_F (IntPtr jnienv, IntPtr native__this, float angle)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Sprite2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.Rotation = angle;
		}
#pragma warning restore 0169

		public virtual unsafe float Rotation {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/method[@name='getRotation' and count(parameter)=0]"
			[Register ("getRotation", "()F", "GetGetRotationHandler")]
			get {
				const string __id = "getRotation.()F";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualSingleMethod (__id, this, null);
					return __rm;
				} finally {
				}
			}
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/method[@name='setRotation' and count(parameter)=1 and parameter[1][@type='float']]"
			[Register ("setRotation", "(F)V", "GetSetRotation_FHandler")]
			set {
				const string __id = "setRotation.(F)V";
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (value);
					_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
				} finally {
				}
			}
		}

		static Delegate cb_getScaleX;
#pragma warning disable 0169
		static Delegate GetGetScaleXHandler ()
		{
			if (cb_getScaleX == null)
				cb_getScaleX = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_F) n_GetScaleX);
			return cb_getScaleX;
		}

		static float n_GetScaleX (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Sprite2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.ScaleX;
		}
#pragma warning restore 0169

		public virtual unsafe float ScaleX {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/method[@name='getScaleX' and count(parameter)=0]"
			[Register ("getScaleX", "()F", "GetGetScaleXHandler")]
			get {
				const string __id = "getScaleX.()F";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualSingleMethod (__id, this, null);
					return __rm;
				} finally {
				}
			}
		}

		static Delegate cb_getScaleY;
#pragma warning disable 0169
		static Delegate GetGetScaleYHandler ()
		{
			if (cb_getScaleY == null)
				cb_getScaleY = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_F) n_GetScaleY);
			return cb_getScaleY;
		}

		static float n_GetScaleY (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Sprite2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.ScaleY;
		}
#pragma warning restore 0169

		public virtual unsafe float ScaleY {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/method[@name='getScaleY' and count(parameter)=0]"
			[Register ("getScaleY", "()F", "GetGetScaleYHandler")]
			get {
				const string __id = "getScaleY.()F";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualSingleMethod (__id, this, null);
					return __rm;
				} finally {
				}
			}
		}

		static Delegate cb_draw_Lcom_qycx_gleslibrary_FlatShadedProgram_arrayF;
#pragma warning disable 0169
		static Delegate GetDraw_Lcom_qycx_gleslibrary_FlatShadedProgram_arrayFHandler ()
		{
			if (cb_draw_Lcom_qycx_gleslibrary_FlatShadedProgram_arrayF == null)
				cb_draw_Lcom_qycx_gleslibrary_FlatShadedProgram_arrayF = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPLL_V) n_Draw_Lcom_qycx_gleslibrary_FlatShadedProgram_arrayF);
			return cb_draw_Lcom_qycx_gleslibrary_FlatShadedProgram_arrayF;
		}

		static void n_Draw_Lcom_qycx_gleslibrary_FlatShadedProgram_arrayF (IntPtr jnienv, IntPtr native__this, IntPtr native_program, IntPtr native_projectionMatrix)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Sprite2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			var program = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.FlatShadedProgram> (native_program, JniHandleOwnership.DoNotTransfer);
			var projectionMatrix = (float[]) JNIEnv.GetArray (native_projectionMatrix, JniHandleOwnership.DoNotTransfer, typeof (float));
			__this.Draw (program, projectionMatrix);
			if (projectionMatrix != null)
				JNIEnv.CopyArray (projectionMatrix, native_projectionMatrix);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/method[@name='draw' and count(parameter)=2 and parameter[1][@type='com.qycx.gleslibrary.FlatShadedProgram'] and parameter[2][@type='float[]']]"
		[Register ("draw", "(Lcom/qycx/gleslibrary/FlatShadedProgram;[F)V", "GetDraw_Lcom_qycx_gleslibrary_FlatShadedProgram_arrayFHandler")]
		public virtual unsafe void Draw (global::Com.Qycx.Gleslibrary.FlatShadedProgram program, float[] projectionMatrix)
		{
			const string __id = "draw.(Lcom/qycx/gleslibrary/FlatShadedProgram;[F)V";
			IntPtr native_projectionMatrix = JNIEnv.NewArray (projectionMatrix);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue ((program == null) ? IntPtr.Zero : ((global::Java.Lang.Object) program).Handle);
				__args [1] = new JniArgumentValue (native_projectionMatrix);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
				if (projectionMatrix != null) {
					JNIEnv.CopyArray (native_projectionMatrix, projectionMatrix);
					JNIEnv.DeleteLocalRef (native_projectionMatrix);
				}
				global::System.GC.KeepAlive (program);
				global::System.GC.KeepAlive (projectionMatrix);
			}
		}

		static Delegate cb_draw_Lcom_qycx_gleslibrary_Texture2dProgram_arrayF;
#pragma warning disable 0169
		static Delegate GetDraw_Lcom_qycx_gleslibrary_Texture2dProgram_arrayFHandler ()
		{
			if (cb_draw_Lcom_qycx_gleslibrary_Texture2dProgram_arrayF == null)
				cb_draw_Lcom_qycx_gleslibrary_Texture2dProgram_arrayF = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPLL_V) n_Draw_Lcom_qycx_gleslibrary_Texture2dProgram_arrayF);
			return cb_draw_Lcom_qycx_gleslibrary_Texture2dProgram_arrayF;
		}

		static void n_Draw_Lcom_qycx_gleslibrary_Texture2dProgram_arrayF (IntPtr jnienv, IntPtr native__this, IntPtr native_program, IntPtr native_projectionMatrix)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Sprite2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			var program = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Texture2dProgram> (native_program, JniHandleOwnership.DoNotTransfer);
			var projectionMatrix = (float[]) JNIEnv.GetArray (native_projectionMatrix, JniHandleOwnership.DoNotTransfer, typeof (float));
			__this.Draw (program, projectionMatrix);
			if (projectionMatrix != null)
				JNIEnv.CopyArray (projectionMatrix, native_projectionMatrix);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/method[@name='draw' and count(parameter)=2 and parameter[1][@type='com.qycx.gleslibrary.Texture2dProgram'] and parameter[2][@type='float[]']]"
		[Register ("draw", "(Lcom/qycx/gleslibrary/Texture2dProgram;[F)V", "GetDraw_Lcom_qycx_gleslibrary_Texture2dProgram_arrayFHandler")]
		public virtual unsafe void Draw (global::Com.Qycx.Gleslibrary.Texture2dProgram program, float[] projectionMatrix)
		{
			const string __id = "draw.(Lcom/qycx/gleslibrary/Texture2dProgram;[F)V";
			IntPtr native_projectionMatrix = JNIEnv.NewArray (projectionMatrix);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue ((program == null) ? IntPtr.Zero : ((global::Java.Lang.Object) program).Handle);
				__args [1] = new JniArgumentValue (native_projectionMatrix);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
				if (projectionMatrix != null) {
					JNIEnv.CopyArray (native_projectionMatrix, projectionMatrix);
					JNIEnv.DeleteLocalRef (native_projectionMatrix);
				}
				global::System.GC.KeepAlive (program);
				global::System.GC.KeepAlive (projectionMatrix);
			}
		}

		static Delegate cb_getColor;
#pragma warning disable 0169
		static Delegate GetGetColorHandler ()
		{
			if (cb_getColor == null)
				cb_getColor = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_L) n_GetColor);
			return cb_getColor;
		}

		static IntPtr n_GetColor (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Sprite2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return JNIEnv.NewArray (__this.GetColor ());
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/method[@name='getColor' and count(parameter)=0]"
		[Register ("getColor", "()[F", "GetGetColorHandler")]
		public virtual unsafe float[] GetColor ()
		{
			const string __id = "getColor.()[F";
			try {
				var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, null);
				return (float[]) JNIEnv.GetArray (__rm.Handle, JniHandleOwnership.TransferLocalRef, typeof (float));
			} finally {
			}
		}

		static Delegate cb_getModelViewMatrix;
#pragma warning disable 0169
		static Delegate GetGetModelViewMatrixHandler ()
		{
			if (cb_getModelViewMatrix == null)
				cb_getModelViewMatrix = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_L) n_GetModelViewMatrix);
			return cb_getModelViewMatrix;
		}

		static IntPtr n_GetModelViewMatrix (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Sprite2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return JNIEnv.NewArray (__this.GetModelViewMatrix ());
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/method[@name='getModelViewMatrix' and count(parameter)=0]"
		[Register ("getModelViewMatrix", "()[F", "GetGetModelViewMatrixHandler")]
		public virtual unsafe float[] GetModelViewMatrix ()
		{
			const string __id = "getModelViewMatrix.()[F";
			try {
				var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, null);
				return (float[]) JNIEnv.GetArray (__rm.Handle, JniHandleOwnership.TransferLocalRef, typeof (float));
			} finally {
			}
		}

		static Delegate cb_setColor_FFF;
#pragma warning disable 0169
		static Delegate GetSetColor_FFFHandler ()
		{
			if (cb_setColor_FFF == null)
				cb_setColor_FFF = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPFFF_V) n_SetColor_FFF);
			return cb_setColor_FFF;
		}

		static void n_SetColor_FFF (IntPtr jnienv, IntPtr native__this, float red, float green, float blue)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Sprite2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.SetColor (red, green, blue);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/method[@name='setColor' and count(parameter)=3 and parameter[1][@type='float'] and parameter[2][@type='float'] and parameter[3][@type='float']]"
		[Register ("setColor", "(FFF)V", "GetSetColor_FFFHandler")]
		public virtual unsafe void SetColor (float red, float green, float blue)
		{
			const string __id = "setColor.(FFF)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [3];
				__args [0] = new JniArgumentValue (red);
				__args [1] = new JniArgumentValue (green);
				__args [2] = new JniArgumentValue (blue);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
			}
		}

		static Delegate cb_setPosition_FF;
#pragma warning disable 0169
		static Delegate GetSetPosition_FFHandler ()
		{
			if (cb_setPosition_FF == null)
				cb_setPosition_FF = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPFF_V) n_SetPosition_FF);
			return cb_setPosition_FF;
		}

		static void n_SetPosition_FF (IntPtr jnienv, IntPtr native__this, float posX, float posY)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Sprite2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.SetPosition (posX, posY);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/method[@name='setPosition' and count(parameter)=2 and parameter[1][@type='float'] and parameter[2][@type='float']]"
		[Register ("setPosition", "(FF)V", "GetSetPosition_FFHandler")]
		public virtual unsafe void SetPosition (float posX, float posY)
		{
			const string __id = "setPosition.(FF)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (posX);
				__args [1] = new JniArgumentValue (posY);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
			}
		}

		static Delegate cb_setScale_FF;
#pragma warning disable 0169
		static Delegate GetSetScale_FFHandler ()
		{
			if (cb_setScale_FF == null)
				cb_setScale_FF = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPFF_V) n_SetScale_FF);
			return cb_setScale_FF;
		}

		static void n_SetScale_FF (IntPtr jnienv, IntPtr native__this, float scaleX, float scaleY)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Sprite2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.SetScale (scaleX, scaleY);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/method[@name='setScale' and count(parameter)=2 and parameter[1][@type='float'] and parameter[2][@type='float']]"
		[Register ("setScale", "(FF)V", "GetSetScale_FFHandler")]
		public virtual unsafe void SetScale (float scaleX, float scaleY)
		{
			const string __id = "setScale.(FF)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (scaleX);
				__args [1] = new JniArgumentValue (scaleY);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
			}
		}

		static Delegate cb_setTexture_I;
#pragma warning disable 0169
		static Delegate GetSetTexture_IHandler ()
		{
			if (cb_setTexture_I == null)
				cb_setTexture_I = JNINativeWrapper.CreateDelegate ((_JniMarshal_PPI_V) n_SetTexture_I);
			return cb_setTexture_I;
		}

		static void n_SetTexture_I (IntPtr jnienv, IntPtr native__this, int textureId)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Sprite2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			__this.SetTexture (textureId);
		}
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Sprite2d']/method[@name='setTexture' and count(parameter)=1 and parameter[1][@type='int']]"
		[Register ("setTexture", "(I)V", "GetSetTexture_IHandler")]
		public virtual unsafe void SetTexture (int textureId)
		{
			const string __id = "setTexture.(I)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue (textureId);
				_members.InstanceMethods.InvokeVirtualVoidMethod (__id, this, __args);
			} finally {
			}
		}

	}
}
