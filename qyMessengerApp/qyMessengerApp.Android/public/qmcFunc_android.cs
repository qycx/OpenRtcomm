using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


//
namespace qy.Droid
{
	partial class qyFuncs_Droid
{

#if true
		public static unsafe int stopQThread_android(QY_qThreadProcInfo_common pThread, string hint)
		{
			//TCHAR tBuf[256];

			if (null == hint) hint = ("");

			if (bIndexValid_myThread(pThread.obj_hThread ))
			{
				MyThread mt = getMyThread(pThread.obj_hThread);
				if ( mt != null) { 

					//
					pThread.bQuit = true;
					qyFuncs.myEventSet(pThread.q2.hEvent0);
					mt.Join();
				}
				freeMyThread(ref pThread.obj_hThread);
			}

			return 0;
		}
#endif

		//
		public static int startQThread_android(PF_threadProc lpStartAddress, object lpParameter, object pThreadClass, QY_qThreadProcInfo_common pQThread)
		{
			int iErr = -1;
			uint dwThreadDaemonId = 0;

			//
			if (null != lpStartAddress)
			{
				//
#if false
				pQThread.hThread = new System.Threading.Thread(new System.Threading.ParameterizedThreadStart(lpStartAddress));
				pQThread.hThread.Start(lpParameter);
#endif
				//
				int index_o = -1;
				if (0 != newMyThread(null, lpStartAddress, lpParameter, ref index_o)) goto errLabel;
				pQThread.obj_hThread = index_o;
				MyThread mt = getMyThread(pQThread.obj_hThread);
				if (mt == null) goto errLabel;
				mt.Start();
			}

			iErr = 0;

		errLabel:

			return iErr;
		}

		public static int doGC(string hint )
        {
			string str;

			if (hint == null) hint = "";

			str = string.Format("doGC enters, {0}", hint);
			qyFuncs.showInfo_open(0, null, str);

			//
			//Java.Lang.JavaSystem.Gc();
			//
			GC.Collect();

			//
			str = string.Format("doGC leaves, {0}", hint);
			qyFuncs.showInfo_open(0, null, str);

			//
			return 0;
		}


	}
}