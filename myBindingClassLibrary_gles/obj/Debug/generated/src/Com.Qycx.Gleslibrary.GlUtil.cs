using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace Com.Qycx.Gleslibrary {

	// Metadata.xml XPath class reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GlUtil']"
	[global::Android.Runtime.Register ("com/qycx/gleslibrary/GlUtil", DoNotGenerateAcw=true)]
	public partial class GlUtil : global::Java.Lang.Object {

		// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GlUtil']/field[@name='IDENTITY_MATRIX']"
		[Register ("IDENTITY_MATRIX")]
		public static IList<float> IdentityMatrix {
			get {
				const string __id = "IDENTITY_MATRIX.[F";

				var __v = _members.StaticFields.GetObjectValue (__id);
				return global::Android.Runtime.JavaArray<float>.FromJniHandle (__v.Handle, JniHandleOwnership.TransferLocalRef);
			}
		}

		// Metadata.xml XPath field reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GlUtil']/field[@name='TAG']"
		[Register ("TAG")]
		public const string Tag = (string) "Grafika";

		static readonly JniPeerMembers _members = new XAPeerMembers ("com/qycx/gleslibrary/GlUtil", typeof (GlUtil));

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

		protected GlUtil (IntPtr javaReference, JniHandleOwnership transfer) : base (javaReference, transfer)
		{
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GlUtil']/method[@name='checkGlError' and count(parameter)=1 and parameter[1][@type='java.lang.String']]"
		[Register ("checkGlError", "(Ljava/lang/String;)V", "")]
		public static unsafe void CheckGlError (string op)
		{
			const string __id = "checkGlError.(Ljava/lang/String;)V";
			IntPtr native_op = JNIEnv.NewString (op);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue (native_op);
				_members.StaticMethods.InvokeVoidMethod (__id, __args);
			} finally {
				JNIEnv.DeleteLocalRef (native_op);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GlUtil']/method[@name='checkLocation' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='java.lang.String']]"
		[Register ("checkLocation", "(ILjava/lang/String;)V", "")]
		public static unsafe void CheckLocation (int location, string label)
		{
			const string __id = "checkLocation.(ILjava/lang/String;)V";
			IntPtr native_label = JNIEnv.NewString (label);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (location);
				__args [1] = new JniArgumentValue (native_label);
				_members.StaticMethods.InvokeVoidMethod (__id, __args);
			} finally {
				JNIEnv.DeleteLocalRef (native_label);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GlUtil']/method[@name='createFloatBuffer' and count(parameter)=1 and parameter[1][@type='float[]']]"
		[Register ("createFloatBuffer", "([F)Ljava/nio/FloatBuffer;", "")]
		public static unsafe global::Java.Nio.FloatBuffer CreateFloatBuffer (float[] coords)
		{
			const string __id = "createFloatBuffer.([F)Ljava/nio/FloatBuffer;";
			IntPtr native_coords = JNIEnv.NewArray (coords);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [1];
				__args [0] = new JniArgumentValue (native_coords);
				var __rm = _members.StaticMethods.InvokeObjectMethod (__id, __args);
				return global::Java.Lang.Object.GetObject<global::Java.Nio.FloatBuffer> (__rm.Handle, JniHandleOwnership.TransferLocalRef);
			} finally {
				if (coords != null) {
					JNIEnv.CopyArray (native_coords, coords);
					JNIEnv.DeleteLocalRef (native_coords);
				}
				global::System.GC.KeepAlive (coords);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GlUtil']/method[@name='createImageTexture' and count(parameter)=4 and parameter[1][@type='java.nio.ByteBuffer'] and parameter[2][@type='int'] and parameter[3][@type='int'] and parameter[4][@type='int']]"
		[Register ("createImageTexture", "(Ljava/nio/ByteBuffer;III)I", "")]
		public static unsafe int CreateImageTexture (global::Java.Nio.ByteBuffer data, int width, int height, int format)
		{
			const string __id = "createImageTexture.(Ljava/nio/ByteBuffer;III)I";
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [4];
				__args [0] = new JniArgumentValue ((data == null) ? IntPtr.Zero : ((global::Java.Lang.Object) data).Handle);
				__args [1] = new JniArgumentValue (width);
				__args [2] = new JniArgumentValue (height);
				__args [3] = new JniArgumentValue (format);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				global::System.GC.KeepAlive (data);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GlUtil']/method[@name='createProgram' and count(parameter)=2 and parameter[1][@type='java.lang.String'] and parameter[2][@type='java.lang.String']]"
		[Register ("createProgram", "(Ljava/lang/String;Ljava/lang/String;)I", "")]
		public static unsafe int CreateProgram (string vertexSource, string fragmentSource)
		{
			const string __id = "createProgram.(Ljava/lang/String;Ljava/lang/String;)I";
			IntPtr native_vertexSource = JNIEnv.NewString (vertexSource);
			IntPtr native_fragmentSource = JNIEnv.NewString (fragmentSource);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (native_vertexSource);
				__args [1] = new JniArgumentValue (native_fragmentSource);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				JNIEnv.DeleteLocalRef (native_vertexSource);
				JNIEnv.DeleteLocalRef (native_fragmentSource);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GlUtil']/method[@name='loadShader' and count(parameter)=2 and parameter[1][@type='int'] and parameter[2][@type='java.lang.String']]"
		[Register ("loadShader", "(ILjava/lang/String;)I", "")]
		public static unsafe int LoadShader (int shaderType, string source)
		{
			const string __id = "loadShader.(ILjava/lang/String;)I";
			IntPtr native_source = JNIEnv.NewString (source);
			try {
				JniArgumentValue* __args = stackalloc JniArgumentValue [2];
				__args [0] = new JniArgumentValue (shaderType);
				__args [1] = new JniArgumentValue (native_source);
				var __rm = _members.StaticMethods.InvokeInt32Method (__id, __args);
				return __rm;
			} finally {
				JNIEnv.DeleteLocalRef (native_source);
			}
		}

		// Metadata.xml XPath method reference: path="/api/package[@name='com.qycx.gleslibrary']/class[@name='GlUtil']/method[@name='logVersionInfo' and count(parameter)=0]"
		[Register ("logVersionInfo", "()V", "")]
		public static unsafe void LogVersionInfo ()
		{
			const string __id = "logVersionInfo.()V";
			try {
				_members.StaticMethods.InvokeVoidMethod (__id, null);
			} finally {
			}
		}

	}
}
