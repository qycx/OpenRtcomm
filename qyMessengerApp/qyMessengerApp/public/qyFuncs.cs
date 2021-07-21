﻿using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Text;
using System.Threading;
using Xamarin.Forms.Markup;
using System.Net;

static partial class Consts
{
	public const double Pi = 3.14159;
	public const int SpeedOfLight = 300000; // km per sec.
	public const int CONST_qyMaxIpLen = 15;

}


namespace qy
{
	unsafe struct MyBuffer
	{
		public fixed byte fixedBuffer[128];
		public fixed byte fixedBuffer1[Consts.CONST_qyMaxIpLen];

	}

	




	//
	public class testCls
	{
		int i;
		QWM_DYN_CFG cnt;

		public testCls()
        {
			cnt.cnt.usCntPort = 0;

        }
	
		~testCls()
        {
			int i = 0;
        }
	
	};


	public class MyClass : IDisposable
	{
		private bool IsDisposed = false;

		//
		testCls a;
		//
		public int init()
        {
			a = new testCls();
			return 0;
        }

		public void Dispose()
		{
			Dispose(true);
			//GC.SuppressFinalize(this);
		}
		protected void Dispose(bool Disposing)
		{
			if (!IsDisposed)
			{
				if ( Disposing   )
				{
					//Clean Up managed resources
					a = null;
				}
				//Clean up unmanaged resources  
			}
			IsDisposed = true;
		}
		~MyClass()
		{
			Dispose(false);
		}
	}




	partial class qyFuncs
{
		internal static IntPtr ArrayToIntptr(byte[] source)
		{
			if (source == null)
				return IntPtr.Zero;
			unsafe
			{
				fixed (byte* point = source)
				{
					IntPtr ptr = new IntPtr(point);
					return ptr;
				}
			}
		}

		//
		unsafe struct testChar
		{
			public fixed char buf[128];

		};


		public static string CreateMD5(string input)
		{
			// Use input string to calculate MD5 hash
			using (System.Security.Cryptography.MD5 md5 = System.Security.Cryptography.MD5.Create())
			{
				byte[] inputBytes = System.Text.Encoding.ASCII.GetBytes(input);
				byte[] hashBytes = md5.ComputeHash(inputBytes);

				// Convert the byte array to hexadecimal string
				StringBuilder sb = new StringBuilder();
				for (int i = 0; i < hashBytes.Length; i++)
				{
					sb.Append(hashBytes[i].ToString("x2"));
				}
				return sb.ToString();
			}
		}

		public static string GetLocalIPAddress()
		{
			var host = Dns.GetHostEntry(Dns.GetHostName());
			foreach (var ip in host.AddressList)
			{
				if (ip.AddressFamily == System.Net.Sockets.AddressFamily.InterNetwork)
				{
					return ip.ToString();
				}
			}
			return null;
		}

		public static unsafe int test()
        {
			//MIS_MSG_routeTalkData kk;
			MIS_MSGU msg;

			//
			using (CQyMalloc_array mallocObj_array=new CQyMalloc_array(5))
            {
				mallocObj_array.mems[0].mallocf(20);
				mallocObj_array.mems[3].mallocf(30);

            }



			//
			int ii = sizeof(MyBuffer);
			int jj = sizeof(char);

			ii = sizeof(QY_CFGITEM_L32);

			IntPtr p = IntPtr.Zero;
			byte * pb = (byte * )p;
			bool b = pb == null;
			string s0 = CreateMD5("123");
			Console.WriteLine(s0);

			string str = "127.0.0.1";
			ii = (int)myinet_addr("127.0.0.1");
			Console.WriteLine("{0}", ii);

			str = GetLocalIPAddress();

			/*
			Mutex hMutex=new Mutex(false);

			Console.WriteLine("before 0");
			hMutex.WaitOne(1000000);
			Console.WriteLine("before 1");
			hMutex.WaitOne(100000);
			Console.WriteLine("before 2");
			*/
			GENERIC_Q test_q = new GENERIC_Q();
			initGenericQ("test", "test", 0, 100, mymalloc, myfree, test_q);
			int iii = 0;
			int* pi = &iii;
			IntPtr p_pi = (IntPtr)pi;
			qPostMsg(p_pi, sizeof(int), test_q);
			exitGenericQ(test_q);




			using (CQyQ2Help q2Help=new CQyQ2Help())
            {
				int immmm = 9;
            }



		QWM_DYN_CFG a;
			a.cnt.ucbAutoCntIp = true;
			a.cnt.usCntPort = 1;

			//ii = sizeof(testChar.buf);
			

			ulong offset = 0;

			int[] iis = { 1, 1 };
			int x = 100;
			int* pi1;
			//fixed int * pi = (int *)iis;
			//pi++;
			
			x = sizeof(QY_MEMORY);


			//b = sizeof(GENERIC_Q_cfgEx);
			x = sizeof(GENERIC_Q_CFG);

			GENERIC_Q mm;
			testCls nn = null;
			if (nn == null)
			{
			}
			nn  =  new testCls();
			nn.ToString();

			Q_NODE qn;
			
			string s = "kkkk";

			
			char []cs = s.ToCharArray();
			x = cs.Length;



		


			//
			using (MyClass objCls = new MyClass())
			{
				int tii = 0;
				objCls.init();

			}

			//
			MyClass obj = new MyClass();
			testChar tt;
			{
			}
			
			

			//testCls b = new testCls();
			goto errLabel;

			errLabel:




			return 0;
        }

		public static testCls  get_cls()
        {
			testCls b = new testCls();
			b = null;
			return b;

        }



}
}
