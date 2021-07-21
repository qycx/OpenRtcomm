using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Com.Qycx.Gleslibrary {

	// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GeneratedTexture']"
	[global::Android.Runtime.Register ("com/qycx/gleslibrary/GeneratedTexture", DoNotGenerateAcw=true)]
	public partial class GeneratedTexture : global::Java.Lang.Object {
		// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GeneratedTexture.Image']"
		[global::Android.Runtime.Register ("com/qycx/gleslibrary/GeneratedTexture$Image", DoNotGenerateAcw=true)]
		public sealed partial class Image : global::Java.Lang.Enum {

			// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GeneratedTexture.Image']/field[@name='COARSE']"
			[Register ("COARSE")]
			public static global::Com.Qycx.Gleslibrary.GeneratedTexture.Image Coarse {
				get {
					const string __id = "COARSE.Lcom/qycx/gleslibrary/GeneratedTexture$Image;";

					var __v = _members.StaticFields.GetObjectValue (__id);
					return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.GeneratedTexture.Image> (__v.Handle, JniHandleOwnership.TransferLocalRef);
				}
			}


			// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GeneratedTexture.Image']/field[@name='FINE']"
			[Register ("FINE")]
			public static global::Com.Qycx.Gleslibrary.GeneratedTexture.Image Fine {
				get {
					const string __id = "FINE.Lcom/qycx/gleslibrary/GeneratedTexture$Image;";

					var __v = _members.StaticFields.GetObjectValue (__id);
					return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.GeneratedTexture.Image> (__v.Handle, JniHandleOwnership.TransferLocalRef);
				}
			}

			static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/gleslibrary/GeneratedTexture$Image", typeof (Image));

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

			internal Image (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
			{
			}

			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GeneratedTexture.Image']/method[@name='valueOf' and count(parameter)=1 and parameter[1][@type='java.lang.String']]"
			[Register ("valueOf", "(Ljava/lang/String;)Lcom/qycx/gleslibrary/GeneratedTexture$Image;", "")]
			public static unsafe global::Com.Qycx.Gleslibrary.GeneratedTexture.Image ValueOf (string name)
			{
				const string __id = "valueOf.(Ljava/lang/String;)Lcom/qycx/gleslibrary/GeneratedTexture$Image;";
				IntPtr native_name = JNIEnv.NewString (name);
				try {
					JniArgumentValue* __args = stackalloc JniArgumentValue [1];
					__args [0] = new JniArgumentValue (native_name);
					var __rm = _members.StaticMethods.InvokeObjectMethod (__id, __args);
					return global::Java.Lang.Object.GetObject<global::Com.Qycx.Gleslibrary.GeneratedTexture.Image> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
				} finally {
					JNIEnv.DeleteLocalRef (native_name);
				}
			}

			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GeneratedTexture.Image']/method[@name='values' and count(parameter)=0]"
			[Register ("values", "()[Lcom/qycx/gleslibrary/GeneratedTexture$Image;", "")]
			public static unsafe global::Com.Qycx.Gleslibrary.GeneratedTexture.Image[] Values ()
			{
				const string __id = "values.()[Lcom/qycx/gleslibrary/GeneratedTexture$Image;";
				try {
					var __rm = _members.StaticMethods.InvokeObjectMethod (__id, null);
					return (global::Com.Qycx.Gleslibrary.GeneratedTexture.Image[]) JNIEnv.GetArray (__rm.Handle, JniHandleOwnership.TransferLocalRef, typeof (global::Com.Qycx.Gleslibrary.GeneratedTexture.Image));
				} finally {
				}
			}

		}

		static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/gleslibrary/GeneratedTexture", typeof (GeneratedTexture));

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

		protected GeneratedTexture (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
		{
		}

		// Metadata.xml XPath constructor reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GeneratedTexture']/constructor[@name='GeneratedTexture' and count(parameter)=0]"
		[Register (".ctor", "()V", "")]
		public unsafe GeneratedTexture () : base (IntPtr.Zero, JniHandleOwnership.DoNotTransfer)
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

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GeneratedTexture']/method[@name='createTestTexture' and count(parameter)=1 and parameter[1][@type='com.qycx.gleslibrary.GeneratedTexture.Image']]"
		[Register ("createTestTexture", "(Lcom/qycx/gleslibrary/GeneratedTexture$Image;)I", "")]
		public static unsafe int CreateTestTexture (global::Com.Qycx.Gleslibrary.GeneratedTexture.Image which)
		{
			const string __id = "createTestTexture.(Lcom/qycx/gleslibrary/GeneratedTexture$Image;)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((which == null) ? IntPtr.Zero : ((global::Java.Lang.Object) which).Handle);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				global::System.GC.KeepAlive (which);
			}
		}

	}
}
