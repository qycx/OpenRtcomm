using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Com.Qycx.Gleslibrary {

	// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Drawable2d']"
	[global::Android.Runtime.Register ("com/qycx/gleslibrary/Drawable2d", DoNotGenerateAcw=true)]
	public partial class Drawable2d : global::Java.Lang.Object {
		// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Drawable2d.Prefab']"
		[global::Android.Runtime.Register ("com/qycx/gleslibrary/Drawable2d$Prefab", DoNotGenerateAcw=true)]
		public sealed partial class Prefab : global::Java.Lang.Enum {

			// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Drawable2d.Prefab']/field[@name='FULL_RECTANGLE']"
			[Register ("FULL_RECTANGLE")]
			public static global::Com.Qycx.Gleslibrary.Drawable2d.Prefab FullRectangle {
				get {
					const string __id = "FULL_RECTANGLE.Lcom/qycx/gleslibrary/Drawable2d$Prefab;";

					var __v = _members.StaticFields.GetObjectValue (__id);
					return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Drawable2d.Prefab> (__v.Handle, JniHandleOwnership.TransferLocalRef);
				}
			}


			// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Drawable2d.Prefab']/field[@name='RECTANGLE']"
			[Register ("RECTANGLE")]
			public static global::Com.Qycx.Gleslibrary.Drawable2d.Prefab Rectangle {
				get {
					const string __id = "RECTANGLE.Lcom/qycx/gleslibrary/Drawable2d$Prefab;";

					var __v = _members.StaticFields.GetObjectValue (__id);
					return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Drawable2d.Prefab> (__v.Handle, JniHandleOwnership.TransferLocalRef);
				}
			}


			// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Drawable2d.Prefab']/field[@name='TRIANGLE']"
			[Register ("TRIANGLE")]
			public static global::Com.Qycx.Gleslibrary.Drawable2d.Prefab Triangle {
				get {
					const string __id = "TRIANGLE.Lcom/qycx/gleslibrary/Drawable2d$Prefab;";

					var __v = _members.StaticFields.GetObjectValue (__id);
					return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Drawable2d.Prefab> (__v.Handle, JniHandleOwnership.TransferLocalRef);
				}
			}

			static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/gleslibrary/Drawable2d$Prefab", typeof (Prefab));

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

			internal Prefab (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
			{
			}

			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Drawable2d.Prefab']/method[@name='valueOf' and count(parameter)=1 and parameter[1][@type='java.lang.String']]"
			[Register ("valueOf", "(Ljava/lang/String;)Lcom/qycx/gleslibrary/Drawable2d$Prefab;", "")]
			public static unsafe global::Com.Qycx.Gleslibrary.Drawable2d.Prefab ValueOf (string name)
			{
				const string __id = "valueOf.(Ljava/lang/String;)Lcom/qycx/gleslibrary/Drawable2d$Prefab;";
				IntPtr native_name = JNIEnv.NewString (name);
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (native_name);
					var __rm = _members.StaticMethods.InvokeObjectMethod (__id, __args);
					return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Drawable2d.Prefab> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
					JNIEnv.DeleteLocalRef (native_name);
				}
			}

			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Drawable2d.Prefab']/method[@name='values' and count(parameter)=0]"
			[Register ("values", "()[Lcom/qycx/gleslibrary/Drawable2d$Prefab;", "")]
			public static unsafe global::Com.Qycx.Gleslibrary.Drawable2d.Prefab[] Values ()
			{
				const string __id = "values.()[Lcom/qycx/gleslibrary/Drawable2d$Prefab;";
				try {
					var __rm = _members.StaticMethods.InvokeObjectMethod (__id, null);
					return (global::Com.Qycx.Gleslibrary.Drawable2d.Prefab[]) JNIEnv.GetArray (__rm.Handle, JniHandleOwnership.TransferLocalRef, typeof (global::Com.Qycx.Gleslibrary.Drawable2d.Prefab));
				} finally {
				}
			}

		}

		static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/gleslibrary/Drawable2d", typeof (Drawable2d));

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

		protected Drawable2d (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
		{
		}

		// Metadata.xml XPath constructor reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Drawable2d']/constructor[@name='Drawable2d' and count(parameter)=1 and parameter[1][@type='com.qycx.gleslibrary.Drawable2d.Prefab']]"
		[Register (".ctor", "(Lcom/qycx/gleslibrary/Drawable2d$Prefab;)V", "")]
		public unsafe Drawable2d (global::Com.Qycx.Gleslibrary.Drawable2d.Prefab shape) : base (IntPtr.Zero, JniHandleOwnership.DoNotTransfer)
		{
			const string __id = "(Lcom/qycx/gleslibrary/Drawable2d$Prefab;)V";

			if (((global::Java.Lang.Object) this).Handle != IntPtr.Zero)
				return;

			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((shape == null) ? IntPtr.Zero : ((global::Java.Lang.Object) shape).Handle);
				var __r = _members.InstanceMethods.StartCreateInstance (__id, ((object) this).GetType (), __args);
				SetHandle (__r.Handle, JniHandleOwnership.TransferLocalRef);
				_members.InstanceMethods.FinishCreateInstance (__id, this, __args);
			} finally {
				global::System.GC.KeepAlive (shape);
			}
		}

		static Delegate cb_getCoordsPerVertex;
#pragma warning disable 0169
		static Delegate GetGetCoordsPerVertexHandler ()
		{
			if (cb_getCoordsPerVertex == null)
				cb_getCoordsPerVertex = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_I) n_GetCoordsPerVertex);
			return cb_getCoordsPerVertex;
		}

		static int n_GetCoordsPerVertex (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Drawable2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.CoordsPerVertex;
		}
#pragma warning restore 0169

		public virtual unsafe int CoordsPerVertex {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Drawable2d']/method[@name='getCoordsPerVertex' and count(parameter)=0]"
			[Register ("getCoordsPerVertex", "()I", "GetGetCoordsPerVertexHandler")]
			get {
				const string __id = "getCoordsPerVertex.()I";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualInt32Method (__id, this, null);
					return __rm;
				} finally {
				}
			}
		}

		static Delegate cb_getTexCoordArray;
#pragma warning disable 0169
		static Delegate GetGetTexCoordArrayHandler ()
		{
			if (cb_getTexCoordArray == null)
				cb_getTexCoordArray = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_L) n_GetTexCoordArray);
			return cb_getTexCoordArray;
		}

		static IntPtr n_GetTexCoordArray (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Drawable2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return JNIEnv.ToLocalJniHandle (__this.TexCoordArray);
		}
#pragma warning restore 0169

		public virtual unsafe global::Java.Nio.FloatBuffer TexCoordArray {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Drawable2d']/method[@name='getTexCoordArray' and count(parameter)=0]"
			[Register ("getTexCoordArray", "()Ljava/nio/FloatBuffer;", "GetGetTexCoordArrayHandler")]
			get {
				const string __id = "getTexCoordArray.()Ljava/nio/FloatBuffer;";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, null);
					return global::Java.Lang.Object.GetObject<global::Java.Nio.FloatBuffer> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}
		}

		static Delegate cb_getTexCoordStride;
#pragma warning disable 0169
		static Delegate GetGetTexCoordStrideHandler ()
		{
			if (cb_getTexCoordStride == null)
				cb_getTexCoordStride = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_I) n_GetTexCoordStride);
			return cb_getTexCoordStride;
		}

		static int n_GetTexCoordStride (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Drawable2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.TexCoordStride;
		}
#pragma warning restore 0169

		public virtual unsafe int TexCoordStride {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Drawable2d']/method[@name='getTexCoordStride' and count(parameter)=0]"
			[Register ("getTexCoordStride", "()I", "GetGetTexCoordStrideHandler")]
			get {
				const string __id = "getTexCoordStride.()I";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualInt32Method (__id, this, null);
					return __rm;
				} finally {
				}
			}
		}

		static Delegate cb_getVertexArray;
#pragma warning disable 0169
		static Delegate GetGetVertexArrayHandler ()
		{
			if (cb_getVertexArray == null)
				cb_getVertexArray = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_L) n_GetVertexArray);
			return cb_getVertexArray;
		}

		static IntPtr n_GetVertexArray (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Drawable2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return JNIEnv.ToLocalJniHandle (__this.VertexArray);
		}
#pragma warning restore 0169

		public virtual unsafe global::Java.Nio.FloatBuffer VertexArray {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Drawable2d']/method[@name='getVertexArray' and count(parameter)=0]"
			[Register ("getVertexArray", "()Ljava/nio/FloatBuffer;", "GetGetVertexArrayHandler")]
			get {
				const string __id = "getVertexArray.()Ljava/nio/FloatBuffer;";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualObjectMethod (__id, this, null);
					return global::Java.Lang.Object.GetObject<global::Java.Nio.FloatBuffer> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
				}
			}
		}

		static Delegate cb_getVertexCount;
#pragma warning disable 0169
		static Delegate GetGetVertexCountHandler ()
		{
			if (cb_getVertexCount == null)
				cb_getVertexCount = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_I) n_GetVertexCount);
			return cb_getVertexCount;
		}

		static int n_GetVertexCount (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Drawable2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.VertexCount;
		}
#pragma warning restore 0169

		public virtual unsafe int VertexCount {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Drawable2d']/method[@name='getVertexCount' and count(parameter)=0]"
			[Register ("getVertexCount", "()I", "GetGetVertexCountHandler")]
			get {
				const string __id = "getVertexCount.()I";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualInt32Method (__id, this, null);
					return __rm;
				} finally {
				}
			}
		}

		static Delegate cb_getVertexStride;
#pragma warning disable 0169
		static Delegate GetGetVertexStrideHandler ()
		{
			if (cb_getVertexStride == null)
				cb_getVertexStride = JNINativeWrapper.CreateDelegate ((_JniMarshal_PP_I) n_GetVertexStride);
			return cb_getVertexStride;
		}

		static int n_GetVertexStride (IntPtr jnienv, IntPtr native__this)
		{
			var __this = global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.Drawable2d> (jnienv, native__this, JniHandleOwnership.DoNotTransfer);
			return __this.VertexStride;
		}
#pragma warning restore 0169

		public virtual unsafe int VertexStride {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='Drawable2d']/method[@name='getVertexStride' and count(parameter)=0]"
			[Register ("getVertexStride", "()I", "GetGetVertexStrideHandler")]
			get {
				const string __id = "getVertexStride.()I";
				try {
					var __rm = _members.InstanceMethods.InvokeVirtualInt32Method (__id, this, null);
					return __rm;
				} finally {
				}
			}
		}

	}
}
