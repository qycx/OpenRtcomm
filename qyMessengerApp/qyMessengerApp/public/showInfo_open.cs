using System;
using System.Collections.Generic;
using System.Text;

namespace qy
{
    partial class qyFuncs
{
        //
        static string sWho_showInfo = _T("Gui");

        //
        public static int set_who_showInfo(string name)
        {
            if (null==name) return -1;
            //safeTcsnCpy(name, sWho_showInfo, mycountof(sWho_showInfo));
            sWho_showInfo = name;

            return 0;
        }

        public static unsafe int showInfo_open(object p0, string tWhere, string hint)
    {
#if false
            if (tWhere == null) tWhere = "";
            if (hint == null) hint = "";
            
            string who_from = sWho_showInfo;

            if (null==hint) return -1;
            if (null==tWhere) tWhere = _T("");
            
            qyShowInfo1(Consts.CONST_qyShowType_qwmComm, null, (""), who_from, null, tWhere, _T(""), hint);

            //Console.WriteLine("{0}:{1}", tWhere, hint);
#endif
            //
            showInfo_open(p0, null, tWhere, hint);

            return 0;
    }

        
        public static unsafe int showInfo_open(object p0, uint* puiStep,  string tWhere, string hint)
        {
            if (tWhere == null) tWhere = "";
            if (hint == null) hint = "";

            string who_from = sWho_showInfo;

            if (null == hint) return -1;
            if (null == tWhere) tWhere = _T("");

#if true //DEBUG
            Console.WriteLine("{0}:{1}", tWhere, hint);
#endif

            //
            qyShowInfo1(Consts.CONST_qyShowType_qwmComm, puiStep, (""), who_from, null, tWhere, _T(""), hint);

            //
            return 0;
        }





        //
        public static unsafe int showStatus_open(object p0, string tWhere, string hint, int iPos_toDisplay)
        {
            //MC_VAR_isCli	*	pProcInfo  =  QY_GET_procInfo_isCli(  );
            //if  (  !pProcInfo  )  return  -1;

            string who_from = sWho_showInfo;

            if (null==hint) return -1;
            if (null==tWhere) tWhere = _T("");

            PARAM_showInfo param = new PARAM_showInfo();
            param.iPos_toDisplay = iPos_toDisplay;

            qyShowInfo2(&param, Consts.CONST_qyShowType_qmdState, null, (""), who_from, null, tWhere, hint);

            return 0;
        }


    }
}
