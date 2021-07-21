using System;
using System.Collections.Generic;
using System.Text;

namespace qy
{
	//
	public struct PARAM_showInfo
	{
		public int iPos_toDisplay;
	};


	//
    partial class qyFuncs
{
		//
		public static unsafe int qyShowInfo(object pCtx_showInfo, int iShowType, uint* puiStep, string clientIp, string who_from, string who_to, string where, string doStr, string what  )
		{
			QY_SHOW_STRUCT showStruct;


# if  true
			if (iShowType == Consts.CONST_qyShowType_debug) return 0;
#endif


			mymemset((IntPtr)(byte*)&showStruct, 0, sizeof(QY_SHOW_STRUCT));
			showStruct.iType = iShowType;
			if (null!=clientIp && 0!=clientIp.Length) showStruct.ulClientIp = myinet_addr(clientIp);
			if (who_from!=null)
			{
				//_snwprintf_s(showStruct.who_from, mycountof(showStruct.who_from), _TRUNCATE, L"%s", who_from);
				mytcsncpy(showStruct.who_from, who_from, Consts.QyShowStruct_cntof_who_from);
			}
			if (who_to!=null)
			{
				//_snwprintf_s(showStruct.who_to, mycountof(showStruct.who_to), _TRUNCATE, L"%s", who_to);
				mytcsncpy(showStruct.who_to, who_to, Consts.QyShowStruct_cntof_who_to);
			}
			if (where!=null)
			{
				//_snwprintf_s(showStruct.whereBuf, mycountof(showStruct.whereBuf), _TRUNCATE, L"%s", where);
				mytcsncpy(showStruct.whereBuf, where,Consts.QyShowStruct_cntof_whereBuf);
			}
			//  when
			myGetLocalTime(out showStruct.when); //  2007/06/01
			if (null!=puiStep)
			{               //  2008/04/28
				(*puiStep)++;
				showStruct.uiStep = *puiStep;
			}
			//  201508/20
			showStruct.dwProcessId = myGetCurrentProcessId();  //  2015/08/30
			showStruct.dwThreadId = myGetCurrentThreadId();
			//
			if (null!=doStr)
			{
				//_snwprintf_s(showStruct.doStr, mycountof(showStruct.doStr), _TRUNCATE, L"%s", doStr);
				mytcsncpy(showStruct.doStr, doStr, Consts.QyShowStruct_cntof_doStr);
			}
			//_vsnwprintf_s(showStruct.what, mycountof(showStruct.what) - 1, _TRUNCATE, fmt, args);
			mytcsncpy(showStruct.what, what, Consts.QyShowStruct_cntof_what);

			//
			//  MACRO_qyAssert(  g_pShowInfoStruct,  _T(  "qyShowInfo1: g_pShowInfoStruct is null"  )  );
			//  if  (  !g_pShowInfoStruct  )  return  -1;
			if (null!=pCtx_showInfo)
			{
				ShowInfo_struct  sShowInfoStruct = (ShowInfo_struct)pCtx_showInfo;   //  g_pShowInfoStruct;

				//  调用显示信息用的汇调函数
				//if (sShowInfoStruct.errHintPf) sShowInfoStruct.errHintPf(&showStruct, 0);

				if (sShowInfoStruct.bInited)
				{

					switch (showStruct.iType)
					{
						case Consts.CONST_qyShowType_qmdState:
							if (!isQ2Warning(sShowInfoStruct.state_q2, 100))
							{
								q2PostMsg((IntPtr)(byte*)&showStruct, (uint)sizeof(QY_SHOW_STRUCT), sShowInfoStruct.state_q2);
								//
								q2PostMsgAndTrigger(IntPtr.Zero, 0, sShowInfoStruct.q2);
							}
							break;
						default:
							//  2014/05/11
							if (!isQ2Warning(sShowInfoStruct.q2, 100))
							{
								q2PostMsgAndTrigger((IntPtr)(byte*)&showStruct, (uint)sizeof(QY_SHOW_STRUCT), sShowInfoStruct.q2);
							}
							break;
					}

				}
				else
				{
					traceLog(_T("qyShowInfo failed: showInfoStruct not inited"));
				}

			}
			

			return 0;
		}


		public static unsafe int qyShowInfo1(int iShowType, string who_from, string who_to, string where, string doStr )
        {
            string str;

            if (where == null) where = "";
            if (doStr == null) doStr = "";

            //
            if (who_from == null)
            {
                if (who_to == null) who_to = "";
                str = string.Format("{0}:{1},{2}", who_to, where, doStr);
            }
            else if (who_to == null)
            {
                str = string.Format("{0}:{1},{2}", who_from, where, doStr);

            }
            else
            {
                str = string.Format("{0}->{1}:{2},{3}", who_from, who_to, where, doStr);
            }

			//
			qyShowInfo(g_pShowInfoStruct, iShowType, null, null, who_from, who_to, where, "", doStr);


            //Console.WriteLine(str);
            if(GuiShare.pf_logd!=null)
            {
                GuiShare.pf_logd("", str);
            }

            return 0;

        }


public static unsafe int qyShowInfo1(int iShowType, uint* puiStep, string clientIp, string who_from, string who_to, string where, string doStr, string fmtStr )
        {
            return qyShowInfo(g_pShowInfoStruct,iShowType, puiStep,"",who_from, who_to, where, "", doStr + fmtStr);

        }

        public static unsafe int qyShowInfo1(int iShowType, uint* puiStep, string clientIp, string who_from, string who_to, string where, string doStr, char* fmtStr)
        {
            string str = "";
            if ( fmtStr !=null ) str = new string(fmtStr);
            return qyShowInfo1(iShowType, who_from, who_to, where, doStr + str);

        }


		//
		public static unsafe int qyShowInfo2(PARAM_showInfo* pParam, int iShowType, uint* puiStep, string clientIp, string who_from, string who_to, string where, string doStrWhat)
		{
			QY_SHOW_STRUCT showStruct;
			//
			PARAM_showInfo param = new PARAM_showInfo();
			if (null!=pParam) param = *pParam;

			//
			mymemset((IntPtr)(byte*)&showStruct, 0, sizeof(QY_SHOW_STRUCT));
			showStruct.iType = iShowType;
			//
			showStruct.iPos_toDisplay = param.iPos_toDisplay;
			//
			if (null!=clientIp && 0!=clientIp.Length) showStruct.ulClientIp = myinet_addr(clientIp);
			if (null!=who_from)
			{
				//_snwprintf_s(showStruct.who_from, mycountof(showStruct.who_from), _TRUNCATE, L"%s", who_from);
				mytcsncpy(showStruct.who_from, who_from, Consts.QyShowStruct_cntof_who_from);
			}
			if (null!=who_to)
			{
				//_snwprintf_s(showStruct.who_to, mycountof(showStruct.who_to), _TRUNCATE, L"%s", who_to);
				mytcsncpy(showStruct.who_to, who_to, Consts.QyShowStruct_cntof_who_to);
			}
			if (null!=where)
			{
				//_snwprintf_s(showStruct.whereBuf, mycountof(showStruct.whereBuf), _TRUNCATE, L"%s", where);
				mytcsncpy(showStruct.whereBuf, where, Consts.QyShowStruct_cntof_whereBuf);
			}
			//  when
			myGetLocalTime(out showStruct.when); //  2007/06/01
			if (null!=puiStep)
			{               //  2008/04/28
				(*puiStep)++;
				showStruct.uiStep = *puiStep;
			}
			//  201508/20
			showStruct.dwProcessId = myGetCurrentProcessId();  //  2015/08/30
			showStruct.dwThreadId = myGetCurrentThreadId();
			//
			if (null!=doStrWhat)
			{
				//_snwprintf_s(showStruct.doStr, mycountof(showStruct.doStr), _TRUNCATE, L"%s", doStr);
				mytcsncpy(showStruct.what, doStrWhat, Consts.QyShowStruct_cntof_what);
			}
			//_vsnwprintf_s(showStruct.what, mycountof(showStruct.what) - 1, _TRUNCATE, fmt, args);


			//
			//  MACRO_qyAssert(  g_pShowInfoStruct,  _T(  "qyShowInfo1: g_pShowInfoStruct is null"  )  );
			if (null!=g_pShowInfoStruct)
			{
				ShowInfo_struct  sShowInfoStruct = g_pShowInfoStruct;

				//  调用显示信息用的汇调函数
				//if (sShowInfoStruct.errHintPf) sShowInfoStruct.errHintPf(&showStruct, 0);

				if (sShowInfoStruct.bInited)
				{

					switch (showStruct.iType)
					{
						case Consts.CONST_qyShowType_qmdState:
							if (!isQ2Warning(sShowInfoStruct.state_q2, 100))
							{
								q2PostMsg((IntPtr)(byte*)&showStruct, (uint)sizeof(QY_SHOW_STRUCT), sShowInfoStruct.state_q2);
								//
								q2PostMsgAndTrigger(IntPtr.Zero, 0, sShowInfoStruct.q2);
							}
							break;
						default:
							//  2014/05/11
							if (!isQ2Warning(sShowInfoStruct.q2, 100))
							{
								q2PostMsgAndTrigger((IntPtr)(byte*)&showStruct, (uint)sizeof(QY_SHOW_STRUCT), sShowInfoStruct.q2);
							}
							break;
					}

				}
				else
				{
					traceLog(_T("qyShowInfo1 failed: showInfoStruct not inited"));
				}
			}
			

			/*
			*/

			

			return 0;
		}



	}
}
