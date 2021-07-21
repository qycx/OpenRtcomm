using System;

[assembly:global::Android.Runtime.NamespaceMapping (Java = "org.aviran.cookiebar2", Managed="Org.Aviran.Cookiebar2")]

delegate int _JniMarshal_PP_I (IntPtr jnienv, IntPtr klass);
delegate IntPtr _JniMarshal_PP_L (IntPtr jnienv, IntPtr klass);
delegate void _JniMarshal_PP_V (IntPtr jnienv, IntPtr klass);
delegate IntPtr _JniMarshal_PPI_L (IntPtr jnienv, IntPtr klass, int p0);
delegate void _JniMarshal_PPI_V (IntPtr jnienv, IntPtr klass, int p0);
delegate IntPtr _JniMarshal_PPII_L (IntPtr jnienv, IntPtr klass, int p0, int p1);
delegate IntPtr _JniMarshal_PPIL_L (IntPtr jnienv, IntPtr klass, int p0, IntPtr p1);
delegate IntPtr _JniMarshal_PPJ_L (IntPtr jnienv, IntPtr klass, long p0);
delegate IntPtr _JniMarshal_PPL_L (IntPtr jnienv, IntPtr klass, IntPtr p0);
delegate void _JniMarshal_PPL_V (IntPtr jnienv, IntPtr klass, IntPtr p0);
delegate bool _JniMarshal_PPL_Z (IntPtr jnienv, IntPtr klass, IntPtr p0);
delegate IntPtr _JniMarshal_PPLL_L (IntPtr jnienv, IntPtr klass, IntPtr p0, IntPtr p1);
delegate IntPtr _JniMarshal_PPZ_L (IntPtr jnienv, IntPtr klass, bool p0);
