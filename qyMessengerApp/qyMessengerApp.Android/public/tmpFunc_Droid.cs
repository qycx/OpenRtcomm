using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Util;
using Android.Views;
using Android.Widget;
using Java.IO;
using Java.Nio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace qy.Droid
{
	partial class qyFuncs_Droid
{

		public static uint myGetTickCount_android()
        {
			long lVal = Java.Lang.JavaSystem.NanoTime()	/ 1000000;
			return (uint)lVal;
		}

		public static int myGetPid()
        {
			return Android.OS.Process.MyPid();
        }

		public static int myGetTid()
        {
			return Android.OS.Process.MyTid();
        }



	public static void waitForThread1( ref Java.Lang.Thread ph, uint dwMilliseconds)
	{
		uint dwRet = 0;

		if (null == ph) return;

		/*
		dwRet = WaitForSingleObject(*ph, dwMilliseconds);
		if (dwRet != WAIT_TIMEOUT && dwRet != WAIT_FAILED)
		{

			CloseHandle(*ph); *ph = NULL;

		}
		*/

		if (ph != null)
		{
			if (dwMilliseconds == 0)
			{
				if (!ph.IsAlive)
				{
					ph = null;
					return;
				}
				return;
			}

			//			
			uint msPerStep = 100;
			msPerStep = 10;
			uint maxStep = dwMilliseconds / msPerStep;
			if (maxStep == 0) maxStep = 1;
			//
			for (int i = 0; i < maxStep; i++)
			{
				if (!ph.IsAlive)
				{
					ph = null;
					return;
				}
				System.Threading.Thread.Sleep((int)msPerStep);
				continue;
			}

		}


		return;

	}

		//

	// 
		public static int dumpData(byte[]data,int w, int h, bool bAppend, bool bFileName_haveTime, string pureFileName)
	{
			CCtxQyMc pQyMc = g.g_pQyMc;
			File path;
			Context context = Application.Context;
			bool bDbg = true;

			path = Android.OS.Environment.GetExternalStoragePublicDirectory(Android.OS.Environment.DirectoryDownloads);
			string str1 = path.AbsolutePath;

			//
			str1 = str1 + "/test" + w + "X" + h + ".";// + Java.Lang.JavaSystem.CurrentTimeMillis();
			if (bFileName_haveTime)
            {
				DateTime dt = DateTime.Now;
				//
				str1 = str1 + dt.ToString("yyyy_MM_dd_HH_mm_ss_") + dt.Millisecond;
            }


			//
			string fileName = str1 + pureFileName;

			//
			Com.Qycx.Tmpjavalibrary.FileUtil.SaveBytes(data, bAppend, fileName,bDbg);
			//Com.Qycx.Tmpjavalibrary.TmpJniUtil.SaveBytes(data, bAppend, fileName);

			//
			//if (data == null)
			{
				File file;
				Android.Net.Uri uri;

				file = new File(fileName);
				uri = Android.Net.Uri.FromFile(file);
				context.SendBroadcast(new Intent(Intent.ActionMediaScannerScanFile, uri));
			}

			//
			return 0;

		}

		public static unsafe int dumpData1(IntPtr data, int len, int w, int h, bool bAppend, bool bFileName_haveTime, string pureFileName)
		{
			
			byte[] data_array = null;

			if (data != null && len != 0)
			{
				data_array = new byte[len];
				System.Runtime.InteropServices.Marshal.Copy((IntPtr)data, data_array, 0, len);
			}

			dumpData(data_array, w, h, bAppend, bFileName_haveTime, pureFileName);

			return 0;
		}

		public static unsafe int dumpRgb32(byte[]data,int w,int h,string pureFileName)
        {
			/*
			int rgb24Size = w * h * 3;
			//byte[] rgb24 = new byte[rgb24Size];
			ByteBuffer bb_rgb24 = ByteBuffer.AllocateDirect(rgb24Size);
			int rgb32Size = w * h * 4;
			ByteBuffer bb_rgb32 = ByteBuffer.AllocateDirect(rgb32Size);
			bb_rgb32.Put(data);

			//qyFuncs.g_colorSpace.rgb32To24(data, true, rgb24, false, w, h);
			Com.Qycx.Tmpjavalibrary.TmpJniUtil.Rgb32To24(bb_rgb32, true, bb_rgb24, false, w, h);
			*/

			byte[] rgb32 = data;

			Android.Graphics.Bitmap bitmap = Android.Graphics.Bitmap.CreateBitmap(w, h, Android.Graphics.Bitmap.Config.Argb8888);

			//Java.Nio.Buffer buffer=Java.Nio.Buffer.
			ByteBuffer b = ByteBuffer.Wrap(rgb32);

			bitmap.CopyPixelsFromBuffer(b);

			//
			DateTime dt = DateTime.Now;


			//
			File path;
			path = Android.OS.Environment.GetExternalStoragePublicDirectory(Android.OS.Environment.DirectoryDownloads);
			string str = path.AbsolutePath;

			//
			//string str1 = str + "/rgb32." + w + "X" + h + "." + Java.Lang.JavaSystem.CurrentTimeMillis();
			string str1 = str + "/rgb32." + w + "X" + h + "." + dt.ToString("yyyy_MM_dd_HH_mm_ss_")+dt.Millisecond;

			//
			string fileName = str1 + pureFileName+".bmp";

			//
			Com.Qycx.Tmpjavalibrary.FileUtil.SaveBitmap(bitmap, fileName);

			File file;
			Android.Net.Uri uri;
			Context context = Application.Context;

			file = new File(fileName);
			uri = Android.Net.Uri.FromFile(file);
			context.SendBroadcast(new Intent(Intent.ActionMediaScannerScanFile, uri));



			return 0;
        }
		public static unsafe int dumpRgb32_1(IntPtr data, int w, int h, string pureFileName)
        {
			if (data == null) return -1;

			int rgb32Size = w * h * 4;
			byte[] rgb32 = new byte[rgb32Size];
			System.Runtime.InteropServices.Marshal.Copy((IntPtr)data, rgb32, 0, rgb32Size);
			dumpRgb32(rgb32, w, h, pureFileName);
			return 0;
        }

		public static unsafe int dumpBmp(object bmp,string pureFileName )
        {
			Android.Graphics.Bitmap bitmap = (Android.Graphics.Bitmap)bmp;

			int w = bitmap.Width;
			int h = bitmap.Height;

			File path;
			path = Android.OS.Environment.GetExternalStoragePublicDirectory(Android.OS.Environment.DirectoryDownloads);
			string str1 = path.AbsolutePath;

			//
			DateTime dt = DateTime.Now;

			//
			//str1 = str1 + "/tt." + w + "X" + h + "." + Java.Lang.JavaSystem.CurrentTimeMillis();
			str1 = str1 + "/test" + w + "X" + h + "." + dt.ToString("yyyy_MM_dd_HH_mm_ss_")+dt.Millisecond;


			//
			string fileName = str1 + pureFileName+ ".bmp";
			File file;
			Android.Net.Uri uri;
			Context context = Application.Context;



			Com.Qycx.Tmpjavalibrary.FileUtil.SaveBitmap(bitmap, fileName);

            file = new File(fileName);
            uri = Android.Net.Uri.FromFile(file);
            context.SendBroadcast(new Intent(Intent.ActionMediaScannerScanFile, uri));

			return 0;

		}

		//
		public static int logd(string tag, string str)
        {
			string str1;

			DateTime dt = DateTime.Now;
			//
			//str1 = dt.ToString("yyyy_MM_dd_HH_mm_ss_") + dt.Millisecond + " " + str;
			str1 = dt.ToString("HH:mm:ss_") + dt.Millisecond + " " + str;

			Android.Util.Log.Error(tag, str1);
			return 0;
        }
		public static string _T(string str)
		{
			if (str == null) str = "";
			return str;
		}

		//
		//
		public static float XMVectorGetX(System.Numerics.Vector4 V)
		{
			return V.X;
		}

		public static float XMVectorGetY(System.Numerics.Vector4 V)
		{
			return V.Y;
		}

		public static float XMVectorGetZ(System.Numerics.Vector4 V)
		{
			return V.Z;
		}

		//
#if DEBUG
		public static int printChoices(Size[] choices)
		{
			string str;
			int i;
			for (i = 0; i < choices.Length; i++)
			{
				Size option = choices[i];
				str = string.Format("choices[{0}]: {1}x{2}", i, option.Width, option.Height);
				qyFuncs.traceLog(str);
			}

			return 0;
		}
#endif


	}
}