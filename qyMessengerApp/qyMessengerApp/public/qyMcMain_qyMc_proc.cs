using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace qy
{
    public partial class qyFuncs
    {


		///////////////////
		///
public static bool InitInstance(IntPtr hInstance, int nCmdShow)
		{
			bool bRet = false;


			//
			//set_cur_iResId_sys(CONST_resId_sys_isCli_ts);


			//  2015/07/08
			g.g_pQyMc = new CCtxQyMc();
			if (g.g_pQyMc == null) goto errLabel;

			//

			//  2016/08/12
			PARAM_initQyMc param = new PARAM_initQyMc();
			//memset(&param, 0, sizeof(param));
			param.pfNewVar = CCtxQmc_gui.newVar_isCli_gui;
			param.pfFreeVar = CCtxQmc_gui.freeVar_isCli_gui;
			//
			if (initQyMc((IntPtr)null, param, g.g_pQyMc) != 0) goto errLabel;



			bRet = true;
		errLabel:

			return bRet;
		}

		public static int ExitInstance(IntPtr hInstance)
		{
			int iErr = -1;


			//
			exitQyMc(g.g_pQyMc);
			//  2015/07/08
			if (g.g_pQyMc != null)
			{
				//QY_MC* pQyMc = (QY_MC*)g_pQyMc;
				//MACRO_safeDelete(pQyMc);
				g.g_pQyMc = null;
			}


			//
			iErr = 0;
		errLabel:
			return iErr;
		}


	}
}