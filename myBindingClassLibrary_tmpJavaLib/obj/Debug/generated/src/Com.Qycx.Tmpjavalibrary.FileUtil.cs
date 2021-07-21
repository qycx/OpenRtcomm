using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Com.Qycx.Tmpjavalibrary {

	// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='FileUtil']"
	[global::Android.Runtime.Register ("com/qycx/tmpjavalibrary/FileUtil", DoNotGenerateAcw=true)]
	public partial class FileUtil : global::Java.Lang.Object {
		// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='FileUtil']/field[@name='SAVE_DIR']"
		[Register ("SAVE_DIR")]
		public const string SaveDir = (string) "/sdcard/DCIM/Camera2GetPreview/";

		static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/tmpjavalibrary/FileUtil", typeof (FileUtil));

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

		protected FileUtil (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
		{
		}

		// Metadata.xml XPath constructor reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='FileUtil']/constructor[@name='FileUtil' and count(parameter)=0]"
		[Register (".ctor", "()V", "")]
		public unsafe FileUtil () : base (IntPtr.Zero, JniHandleOwnership.DoNotTransfer)
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

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='FileUtil']/method[@name='saveBitmap' and count(parameter)=2 and parameter[1][@type='android.graphics.Bitmap'] and parameter[2][@type='java.lang.String']]"
		[Register ("saveBitmap", "(Landroid/graphics/Bitmap;Ljava/lang/String;)Z", "")]
		public static unsafe bool SaveBitmap (global::Android.Graphics.Bitmap bitmap, string imagePath)
		{
			const string __id = "saveBitmap.(Landroid/graphics/Bitmap;Ljava/lang/String;)Z";
			IntPtr native_imagePath = JNIEnv.NewString (imagePath);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue ((bitmap == null) ? IntPtr.Zero : ((global::Java.Lang.Object) bitmap).Handle);
				__args [1] = new JniArgumentValue (native_imagePath);
				var __rm = _members.StaticMethods.InvokeBooleanMethod (__id, __args);
				return __rm;
			} finally {
				JNIEnv.DeleteLocalRef (native_imagePath);
				global::System.GC.KeepAlive (bitmap);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='FileUtil']/method[@name='saveBytes' and count(parameter)=4 and parameter[1][@type='byte[]'] and parameter[2][@type='boolean'] and parameter[3][@type='java.lang.String'] and parameter[4][@type='boolean']]"
		[Register ("saveBytes", "([BZLjava/lang/String;Z)Z", "")]
		public static unsafe bool SaveBytes (byte[] bytes, bool bAppend, string imagePath, bool bDbg)
		{
			const string __id = "saveBytes.([BZLjava/lang/String;Z)Z";
			IntPtr native_bytes = JNIEnv.NewArray (bytes);
			IntPtr native_imagePath = JNIEnv.NewString (imagePath);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [4];
				__args [0] = new JniArgumentValue (native_bytes);
				__args [1] = new JniArgumentValue (bAppend);
				__args [2] = new JniArgumentValue (native_imagePath);
				__args [3] = new JniArgumentValue (bDbg);
				var __rm = _members.StaticMethods.InvokeBooleanMethod (__id, __args);
				return __rm;
			} finally {
				if (bytes != null) {
					JNIEnv.CopyArray (native_bytes, bytes);
					JNIEnv.DeleteLocalRef (native_bytes);
				}
				JNIEnv.DeleteLocalRef (native_imagePath);
				global::System.GC.KeepAlive (bytes);
			}
		}

	}
}
