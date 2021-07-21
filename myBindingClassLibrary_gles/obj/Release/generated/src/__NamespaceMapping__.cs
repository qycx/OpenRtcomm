using System;

[assembly:global::Android.Runtime.NamespaceMapping (Java = "com.qycx.gleslibrary", Managed="Com.Qycx.Gleslibrary")]

delegate float _JniMarshal_PP_F (IntPtr jnienv, IntPtr klass);
delegate int _JniMarshal_PP_I (IntPtr jnienv, IntPtr klass);
delegate IntPtr _JniMarshal_PP_L (IntPtr jnienv, IntPtr klass);
delegate void _JniMarshal_PP_V (IntPtr jnienv, IntPtr klass);
delegate bool _JniMarshal_PP_Z (IntPtr jnienv, IntPtr klass);
delegate void _JniMarshal_PPF_V (IntPtr jnienv, IntPtr klass, float p0);
delegate void _JniMarshal_PPFF_V (IntPtr jnienv, IntPtr klass, float p0, float p1);
delegate void _JniMarshal_PPFFF_V (IntPtr jnienv, IntPtr klass, float p0, float p1, float p2);
delegate void _JniMarshal_PPI_V (IntPtr jnienv, IntPtr klass, int p0);
delegate void _JniMarshal_PPII_V (IntPtr jnienv, IntPtr klass, int p0, int p1);
delegate void _JniMarshal_PPIL_V (IntPtr jnienv, IntPtr klass, int p0, IntPtr p1);
delegate void _JniMarshal_PPJ_V (IntPtr jnienv, IntPtr klass, long p0);
delegate void _JniMarshal_PPL_V (IntPtr jnienv, IntPtr klass, IntPtr p0);
delegate void _JniMarshal_PPLF_V (IntPtr jnienv, IntPtr klass, IntPtr p0, float p1);
delegate void _JniMarshal_PPLL_V (IntPtr jnienv, IntPtr klass, IntPtr p0, IntPtr p1);
delegate void _JniMarshal_PPLLIIIILLII_V (IntPtr jnienv, IntPtr klass, IntPtr p0, IntPtr p1, int p2, int p3, int p4, int p5, IntPtr p6, IntPtr p7, int p8, int p9);
delegate void _JniMarshal_PPLLLIIII_V (IntPtr jnienv, IntPtr klass, IntPtr p0, IntPtr p1, IntPtr p2, int p3, int p4, int p5, int p6);
delegate void _JniMarshal_PPZ_V (IntPtr jnienv, IntPtr klass, bool p0);
