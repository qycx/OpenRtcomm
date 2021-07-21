using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Com.Qycx.Tmpffmpeglibrary {

	// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']"
	[global::Android.Runtime.Register ("com/qycx/tmpffmpeglibrary/TmpFfmpeg", DoNotGenerateAcw=true)]
	public partial class TmpFfmpeg : global::Java.Lang.Object {
		static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/tmpffmpeglibrary/TmpFfmpeg", typeof (TmpFfmpeg));

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

		protected TmpFfmpeg (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
		{
		}

		// Metadata.xml XPath constructor reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/constructor[@name='TmpFfmpeg' and count(parameter)=0]"
		[Register (".ctor", "()V", "")]
		public unsafe TmpFfmpeg () : base (IntPtr.Zero, JniHandleOwnership.DoNotTransfer)
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

		public static unsafe int Hello {
			// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='getHello' and count(parameter)=0]"
			[Register ("getHello", "()I", "")]
			get {
				const string __id = "getHello.()I";
				try {
					var __rm = _members.StaticMethods.InvokeInt32Method (__id, null);
					return __rm;
				} finally {
				}
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='avCodecInfo' and count(parameter)=0]"
		[Register ("avCodecInfo", "()Ljava/lang/String;", "")]
		public static unsafe string AvCodecInfo ()
		{
			const string __id = "avCodecInfo.()Ljava/lang/String;";
			try {
				var __rm = _members.StaticMethods.InvokeObjectMethod (__id, null);
				return JNIEnv.GetString (__rm.Handle, JniHandleOwnership.TransferLocalRef);
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='avFilterInfo' and count(parameter)=0]"
		[Register ("avFilterInfo", "()Ljava/lang/String;", "")]
		public static unsafe string AvFilterInfo ()
		{
			const string __id = "avFilterInfo.()Ljava/lang/String;";
			try {
				var __rm = _members.StaticMethods.InvokeObjectMethod (__id, null);
				return JNIEnv.GetString (__rm.Handle, JniHandleOwnership.TransferLocalRef);
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='avFormatInfo' and count(parameter)=0]"
		[Register ("avFormatInfo", "()Ljava/lang/String;", "")]
		public static unsafe string AvFormatInfo ()
		{
			const string __id = "avFormatInfo.()Ljava/lang/String;";
			try {
				var __rm = _members.StaticMethods.InvokeObjectMethod (__id, null);
				return JNIEnv.GetString (__rm.Handle, JniHandleOwnership.TransferLocalRef);
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='decA_data' and count(parameter)=7 and parameter[1][@type='int'] and parameter[2][@type='java.nio.ByteBuffer'] and parameter[3][@type='int'] and parameter[4][@type='int'] and parameter[5][@type='java.nio.ByteBuffer'] and parameter[6][@type='int'] and parameter[7][@type='boolean']]"
		[Register ("decA_data", "(ILjava/nio/ByteBuffer;IILjava/nio/ByteBuffer;IZ)I", "")]
		public static unsafe int DecA_data (int p0, global::Java.Nio.ByteBuffer p1, int p2, int p3, global::Java.Nio.ByteBuffer p4, int p5, bool p6)
		{
			const string __id = "decA_data.(ILjava/nio/ByteBuffer;IILjava/nio/ByteBuffer;IZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [7];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue ((p1 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p1).Handle);
				__args [2] = new JniArgumentValue (p2);
				__args [3] = new JniArgumentValue (p3);
				__args [4] = new JniArgumentValue ((p4 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p4).Handle);
				__args [5] = new JniArgumentValue (p5);
				__args [6] = new JniArgumentValue (p6);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				global::System.GC.KeepAlive (p1);
				global::System.GC.KeepAlive (p4);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='decA_exit' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='boolean']]"
		[Register ("decA_exit", "(IZ)I", "")]
		public static unsafe int DecA_exit (int p0, bool p1)
		{
			const string __id = "decA_exit.(IZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue (p1);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='decA_init' and count(parameter)=3 and parameter[1][@type='int'] and parameter[2][@type='short'] and parameter[3][@type='boolean']]"
		[Register ("decA_init", "(ISZ)I", "")]
		public static unsafe int DecA_init (int p0, short p1, bool p2)
		{
			const string __id = "decA_init.(ISZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [3];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue (p1);
				__args [2] = new JniArgumentValue (p2);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='decV_data' and count(parameter)=7 and parameter[1][@type='int'] and parameter[2][@type='java.nio.ByteBuffer'] and parameter[3][@type='int'] and parameter[4][@type='int'] and parameter[5][@type='java.nio.ByteBuffer'] and parameter[6][@type='int'] and parameter[7][@type='boolean']]"
		[Register ("decV_data", "(ILjava/nio/ByteBuffer;IILjava/nio/ByteBuffer;IZ)I", "")]
		public static unsafe int DecV_data (int p0, global::Java.Nio.ByteBuffer p1, int p2, int p3, global::Java.Nio.ByteBuffer p4, int p5, bool p6)
		{
			const string __id = "decV_data.(ILjava/nio/ByteBuffer;IILjava/nio/ByteBuffer;IZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [7];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue ((p1 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p1).Handle);
				__args [2] = new JniArgumentValue (p2);
				__args [3] = new JniArgumentValue (p3);
				__args [4] = new JniArgumentValue ((p4 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p4).Handle);
				__args [5] = new JniArgumentValue (p5);
				__args [6] = new JniArgumentValue (p6);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				global::System.GC.KeepAlive (p1);
				global::System.GC.KeepAlive (p4);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='decV_exit' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='boolean']]"
		[Register ("decV_exit", "(IZ)I", "")]
		public static unsafe int DecV_exit (int p0, bool p1)
		{
			const string __id = "decV_exit.(IZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue (p1);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='decV_init' and count(parameter)=3 and parameter[1][@type='int'] and parameter[2][@type='int'] and parameter[3][@type='boolean']]"
		[Register ("decV_init", "(IIZ)I", "")]
		public static unsafe int DecV_init (int p0, int p1, bool p2)
		{
			const string __id = "decV_init.(IIZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [3];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue (p1);
				__args [2] = new JniArgumentValue (p2);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='dec_clearOutputs' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='boolean']]"
		[Register ("dec_clearOutputs", "(IZ)I", "")]
		public static unsafe int Dec_clearOutputs (int p0, bool p1)
		{
			const string __id = "dec_clearOutputs.(IZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue (p1);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='dec_getOutputByIndex' and count(parameter)=5 and parameter[1][@type='int'] and parameter[2][@type='int'] and parameter[3][@type='java.nio.ByteBuffer'] and parameter[4][@type='int'] and parameter[5][@type='boolean']]"
		[Register ("dec_getOutputByIndex", "(IILjava/nio/ByteBuffer;IZ)I", "")]
		public static unsafe int Dec_getOutputByIndex (int p0, int p1, global::Java.Nio.ByteBuffer p2, int p3, bool p4)
		{
			const string __id = "dec_getOutputByIndex.(IILjava/nio/ByteBuffer;IZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [5];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue (p1);
				__args [2] = new JniArgumentValue ((p2 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p2).Handle);
				__args [3] = new JniArgumentValue (p3);
				__args [4] = new JniArgumentValue (p4);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				global::System.GC.KeepAlive (p2);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='doTest' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='java.lang.String']]"
		[Register ("doTest", "(ILjava/lang/String;)Ljava/lang/String;", "")]
		public static unsafe string DoTest (int p0, string p1)
		{
			const string __id = "doTest.(ILjava/lang/String;)Ljava/lang/String;";
			IntPtr native_p1 = JNIEnv.NewString (p1);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue (native_p1);
				var __rm = _members.StaticMethods.InvokeObjectMethod (__id, __args);
				return JNIEnv.GetString (__rm.Handle, JniHandleOwnership.TransferLocalRef);
			} finally {
				JNIEnv.DeleteLocalRef (native_p1);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='encA_data' and count(parameter)=6 and parameter[1][@type='int'] and parameter[2][@type='java.nio.ByteBuffer'] and parameter[3][@type='int'] and parameter[4][@type='java.nio.ByteBuffer'] and parameter[5][@type='int'] and parameter[6][@type='boolean']]"
		[Register ("encA_data", "(ILjava/nio/ByteBuffer;ILjava/nio/ByteBuffer;IZ)I", "")]
		public static unsafe int EncA_data (int p0, global::Java.Nio.ByteBuffer p1, int p2, global::Java.Nio.ByteBuffer p3, int p4, bool p5)
		{
			const string __id = "encA_data.(ILjava/nio/ByteBuffer;ILjava/nio/ByteBuffer;IZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [6];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue ((p1 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p1).Handle);
				__args [2] = new JniArgumentValue (p2);
				__args [3] = new JniArgumentValue ((p3 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p3).Handle);
				__args [4] = new JniArgumentValue (p4);
				__args [5] = new JniArgumentValue (p5);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				global::System.GC.KeepAlive (p1);
				global::System.GC.KeepAlive (p3);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='encA_exit' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='boolean']]"
		[Register ("encA_exit", "(IZ)I", "")]
		public static unsafe int EncA_exit (int p0, bool p1)
		{
			const string __id = "encA_exit.(IZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue (p1);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='encA_init' and count(parameter)=3 and parameter[1][@type='int'] and parameter[2][@type='short'] and parameter[3][@type='boolean']]"
		[Register ("encA_init", "(ISZ)I", "")]
		public static unsafe int EncA_init (int p0, short p1, bool p2)
		{
			const string __id = "encA_init.(ISZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [3];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue (p1);
				__args [2] = new JniArgumentValue (p2);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='encV_data' and count(parameter)=6 and parameter[1][@type='int'] and parameter[2][@type='java.nio.ByteBuffer'] and parameter[3][@type='int'] and parameter[4][@type='java.nio.ByteBuffer'] and parameter[5][@type='int'] and parameter[6][@type='boolean']]"
		[Register ("encV_data", "(ILjava/nio/ByteBuffer;ILjava/nio/ByteBuffer;IZ)I", "")]
		public static unsafe int EncV_data (int p0, global::Java.Nio.ByteBuffer p1, int p2, global::Java.Nio.ByteBuffer p3, int p4, bool p5)
		{
			const string __id = "encV_data.(ILjava/nio/ByteBuffer;ILjava/nio/ByteBuffer;IZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [6];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue ((p1 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p1).Handle);
				__args [2] = new JniArgumentValue (p2);
				__args [3] = new JniArgumentValue ((p3 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p3).Handle);
				__args [4] = new JniArgumentValue (p4);
				__args [5] = new JniArgumentValue (p5);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				global::System.GC.KeepAlive (p1);
				global::System.GC.KeepAlive (p3);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='encV_exit' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='boolean']]"
		[Register ("encV_exit", "(IZ)I", "")]
		public static unsafe int EncV_exit (int p0, bool p1)
		{
			const string __id = "encV_exit.(IZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue (p1);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='encV_getSpsPps' and count(parameter)=4 and parameter[1][@type='int'] and parameter[2][@type='java.nio.ByteBuffer'] and parameter[3][@type='int[]'] and parameter[4][@type='boolean']]"
		[Register ("encV_getSpsPps", "(ILjava/nio/ByteBuffer;[IZ)I", "")]
		public static unsafe int EncV_getSpsPps (int p0, global::Java.Nio.ByteBuffer p1, int[] p2, bool p3)
		{
			const string __id = "encV_getSpsPps.(ILjava/nio/ByteBuffer;[IZ)I";
			IntPtr native_p2 = JNIEnv.NewArray (p2);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [4];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue ((p1 == null) ? IntPtr.Zero : ((global::Java.Lang.Object) p1).Handle);
				__args [2] = new JniArgumentValue (native_p2);
				__args [3] = new JniArgumentValue (p3);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				if (p2 != null) {
					JNIEnv.CopyArray (native_p2, p2);
					JNIEnv.DeleteLocalRef (native_p2);
				}
				global::System.GC.KeepAlive (p1);
				global::System.GC.KeepAlive (p2);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='encV_init' and count(parameter)=5 and parameter[1][@type='int'] and parameter[2][@type='int'] and parameter[3][@type='int'] and parameter[4][@type='int'] and parameter[5][@type='boolean']]"
		[Register ("encV_init", "(IIIIZ)I", "")]
		public static unsafe int EncV_init (int p0, int p1, int p2, int p3, bool p4)
		{
			const string __id = "encV_init.(IIIIZ)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [5];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue (p1);
				__args [2] = new JniArgumentValue (p2);
				__args [3] = new JniArgumentValue (p3);
				__args [4] = new JniArgumentValue (p4);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='freeQdcUnitIndex' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='boolean']]"
		[Register ("freeQdcUnitIndex", "(IZ)V", "")]
		public static unsafe void FreeQdcUnitIndex (int p0, bool p1)
		{
			const string __id = "freeQdcUnitIndex.(IZ)V";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (p0);
				__args [1] = new JniArgumentValue (p1);
				_members.StaticMethods.InvokeVoidMethod (__id, __args);
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='newQdcUnitIndex' and count(parameter)=1 and parameter[1][@type='boolean']]"
		[Register ("newQdcUnitIndex", "(Z)I", "")]
		public static unsafe int NewQdcUnitIndex (bool p0)
		{
			const string __id = "newQdcUnitIndex.(Z)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue (p0);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='qdc_exit' and count(parameter)=0]"
		[Register ("qdc_exit", "()I", "")]
		public static unsafe int Qdc_exit ()
		{
			const string __id = "qdc_exit.()I";
			try {
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, null);
				return __rm;
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='qdc_init' and count(parameter)=0]"
		[Register ("qdc_init", "()I", "")]
		public static unsafe int Qdc_init ()
		{
			const string __id = "qdc_init.()I";
			try {
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, null);
				return __rm;
			} finally {
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.tmpffmpeglibrary']/class[@name='TmpFfmpeg']/method[@name='urlProtocolInfo' and count(parameter)=0]"
		[Register ("urlProtocolInfo", "()Ljava/lang/String;", "")]
		public static unsafe string UrlProtocolInfo ()
		{
			const string __id = "urlProtocolInfo.()Ljava/lang/String;";
			try {
				var __rm = _members.StaticMethods.InvokeObjectMethod (__id, null);
				return JNIEnv.GetString (__rm.Handle, JniHandleOwnership.TransferLocalRef);
			} finally {
			}
		}

	}
}
