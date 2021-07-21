using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Com.Qycx.Tmpjavalibrary {

	// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='TmpJniUtil']"
	[global::Android.Runtime.Register ("com/qycx/tmpjavalibrary/TmpJniUtil", DoNotGenerateAcw=true)]
	public partial class TmpJniUtil : global::Java.Lang.Object {
		static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/tmpjavalibrary/TmpJniUtil", typeof (TmpJniUtil));

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

		protected TmpJniUtil (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
		{
		}

		// Metadata.xml XPath constructor reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='TmpJniUtil']/constructor[@name='TmpJniUtil' and count(parameter)=0]"
		[Register (".ctor", "()V", "")]
		public unsafe TmpJniUtil () : base (IntPtr.Zero, JniHandleOwnership.DoNotTransfer)
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

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='TmpJniUtil']/method[@name='allocNativeByteBuffer' and count(parameter)=1 and parameter[1][@type='int']]"
		[Register ("allocNativeByteBuffer", "(I)Ljava/nio/ByteBuffer;", "")]
		public static unsafe global::Java.Nio.ByteBuffer AllocNativeByteBuffer (int p0)
		{
			const string __id = "allocNativeByteBuffer.(I)Ljava/nio/ByteBuffer;";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue (p0);
				var __rm = _members.StaticMethods.InvokeObjectMethod (__id, __args);
				return global::Java.Lang.Object.GetObject<global::Java.Nio.ByteBuffer> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='TmpJniUtil']/method[@name='freeNativeByteBuffer' and count(parameter)=1 and parameter[1][@type='java.nio.ByteBuffer']]"
		[Register ("freeNativeByteBuffer", "(Ljava/nio/ByteBuffer;)V", "")]
		public static unsafe void FreeNativeByteBuffer (global::Java.Nio.ByteBuffer p0)
		{
			const string __id = "freeNativeByteBuffer.(Ljava/nio/ByteBuffer;)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue ((p0 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p0).Handle);
				_members.StaticMethods.InvokeVoidMethod (__id, __args);
			} finally {
				global::System.GC.KeepAlive (p0);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='TmpJniUtil']/method[@name='hiFromJni' and count(parameter)=1 and parameter[1][@type='int[]']]"
		[Register ("hiFromJni", "([I)I", "")]
		public static unsafe int HiFromJni (int[] p0)
		{
			const string __id = "hiFromJni.([I)I";
			IntPtr native_p0 = JNIEnv.NewArray (p0);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue (native_p0);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				if (p0 != null) {
					JNIEnv.CopyArray (native_p0, p0);
					JNIEnv.DeleteLocalRef (native_p0);
				}
				global::System.GC.KeepAlive (p0);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='TmpJniUtil']/method[@name='i420ToRgb' and count(parameter)=7 and parameter[1][@type='java.nio.ByteBuffer'] and parameter[2][@type='java.nio.ByteBuffer'] and parameter[3][@type='int'] and parameter[4][@type='boolean'] and parameter[5][@type='int'] and parameter[6][@type='int'] and parameter[7][@type='boolean']]"
		[Register ("i420ToRgb", "(Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;IZIIZ)I", "")]
		public static unsafe int I420ToRgb (global::Java.Nio.ByteBuffer p0, global::Java.Nio.ByteBuffer p1, int p2, bool p3, int p4, int p5, bool p6)
		{
			const string __id = "i420ToRgb.(Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;IZIIZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [7];
				__args [0] = new JniArgumentValue ((p0 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p0).Handle);
				__args [1] = new JniArgumentValue ((p1 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p1).Handle);
				__args [2] = new JniArgumentValue (p2);
				__args [3] = new JniArgumentValue (p3);
				__args [4] = new JniArgumentValue (p4);
				__args [5] = new JniArgumentValue (p5);
				__args [6] = new JniArgumentValue (p6);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				global::System.GC.KeepAlive (p0);
				global::System.GC.KeepAlive (p1);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='TmpJniUtil']/method[@name='procByteArray' and count(parameter)=2 and parameter[1][@type='byte[]'] and parameter[2][@type='int']]"
		[Register ("procByteArray", "([BI)I", "")]
		public static unsafe int ProcByteArray (byte[] p0, int p1)
		{
			const string __id = "procByteArray.([BI)I";
			IntPtr native_p0 = JNIEnv.NewArray (p0);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (native_p0);
				__args [1] = new JniArgumentValue (p1);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				if (p0 != null) {
					JNIEnv.CopyArray (native_p0, p0);
					JNIEnv.DeleteLocalRef (native_p0);
				}
				global::System.GC.KeepAlive (p0);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='TmpJniUtil']/method[@name='rgb32To24' and count(parameter)=6 and parameter[1][@type='java.nio.ByteBuffer'] and parameter[2][@type='boolean'] and parameter[3][@type='java.nio.ByteBuffer'] and parameter[4][@type='boolean'] and parameter[5][@type='int'] and parameter[6][@type='int']]"
		[Register ("rgb32To24", "(Ljava/nio/ByteBuffer;ZLjava/nio/ByteBuffer;ZII)I", "")]
		public static unsafe int Rgb32To24 (global::Java.Nio.ByteBuffer p0, bool p1, global::Java.Nio.ByteBuffer p2, bool p3, int p4, int p5)
		{
			const string __id = "rgb32To24.(Ljava/nio/ByteBuffer;ZLjava/nio/ByteBuffer;ZII)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [6];
				__args [0] = new JniArgumentValue ((p0 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p0).Handle);
				__args [1] = new JniArgumentValue (p1);
				__args [2] = new JniArgumentValue ((p2 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p2).Handle);
				__args [3] = new JniArgumentValue (p3);
				__args [4] = new JniArgumentValue (p4);
				__args [5] = new JniArgumentValue (p5);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				global::System.GC.KeepAlive (p0);
				global::System.GC.KeepAlive (p2);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='TmpJniUtil']/method[@name='rgbToI420' and count(parameter)=7 and parameter[1][@type='java.nio.ByteBuffer'] and parameter[2][@type='int'] and parameter[3][@type='boolean'] and parameter[4][@type='java.nio.ByteBuffer'] and parameter[5][@type='int'] and parameter[6][@type='int'] and parameter[7][@type='boolean']]"
		[Register ("rgbToI420", "(Ljava/nio/ByteBuffer;IZLjava/nio/ByteBuffer;IIZ)I", "")]
		public static unsafe int RgbToI420 (global::Java.Nio.ByteBuffer p0, int p1, bool p2, global::Java.Nio.ByteBuffer p3, int p4, int p5, bool p6)
		{
			const string __id = "rgbToI420.(Ljava/nio/ByteBuffer;IZLjava/nio/ByteBuffer;IIZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [7];
				__args [0] = new JniArgumentValue ((p0 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p0).Handle);
				__args [1] = new JniArgumentValue (p1);
				__args [2] = new JniArgumentValue (p2);
				__args [3] = new JniArgumentValue ((p3 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p3).Handle);
				__args [4] = new JniArgumentValue (p4);
				__args [5] = new JniArgumentValue (p5);
				__args [6] = new JniArgumentValue (p6);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				global::System.GC.KeepAlive (p0);
				global::System.GC.KeepAlive (p3);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='TmpJniUtil']/method[@name='rotateI420' and count(parameter)=6 and parameter[1][@type='java.nio.ByteBuffer'] and parameter[2][@type='java.nio.ByteBuffer'] and parameter[3][@type='int'] and parameter[4][@type='int'] and parameter[5][@type='int'] and parameter[6][@type='boolean']]"
		[Register ("rotateI420", "(Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;IIIZ)I", "")]
		public static unsafe int RotateI420 (global::Java.Nio.ByteBuffer p0, global::Java.Nio.ByteBuffer p1, int p2, int p3, int p4, bool p5)
		{
			const string __id = "rotateI420.(Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;IIIZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [6];
				__args [0] = new JniArgumentValue ((p0 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p0).Handle);
				__args [1] = new JniArgumentValue ((p1 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p1).Handle);
				__args [2] = new JniArgumentValue (p2);
				__args [3] = new JniArgumentValue (p3);
				__args [4] = new JniArgumentValue (p4);
				__args [5] = new JniArgumentValue (p5);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				global::System.GC.KeepAlive (p0);
				global::System.GC.KeepAlive (p1);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='TmpJniUtil']/method[@name='sayHello' and count(parameter)=1 and parameter[1][@type='java.lang.String']]"
		[Register ("sayHello", "(Ljava/lang/String;)Ljava/lang/String;", "")]
		public static unsafe string SayHello (string p0)
		{
			const string __id = "sayHello.(Ljava/lang/String;)Ljava/lang/String;";
			IntPtr native_p0 = JNIEnv.NewString (p0);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue (native_p0);
				var __rm = _members.StaticMethods.InvokeObjectMethod (__id, __args);
				return JNIEnv.GetString (__rm.Handle, JniHandleOwnership.TransferLocalRef);
			} finally {
				JNIEnv.DeleteLocalRef (native_p0);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpjavalibrary']/class[@name='TmpJniUtil']/method[@name='sumAvg' and count(parameter)=1 and parameter[1][@type='int[]']]"
		[Register ("sumAvg", "([I)[D", "")]
		public static unsafe double[] SumAvg (int[] p0)
		{
			const string __id = "sumAvg.([I)[D";
			IntPtr native_p0 = JNIEnv.NewArray (p0);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue (native_p0);
				var __rm = _members.StaticMethods.InvokeObjectMethod (__id, __args);
				return (double[]) JNIEnv.GetArray (__rm.Handle, JniHandleOwnership.TransferLocalRef, typeof (double));
			} finally {
				if (p0 != null) {
					JNIEnv.CopyArray (native_p0, p0);
					JNIEnv.DeleteLocalRef (native_p0);
				}
				global::System.GC.KeepAlive (p0);
			}
		}

	}
}
