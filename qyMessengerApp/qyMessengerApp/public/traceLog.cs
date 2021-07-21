using System;
using System.Collections.Generic;
using System.Text;

namespace qy
{
    partial class qyFuncs
{
        public static unsafe int getCurTime(byte* timeBuf)
        {
            /*
            SYSTEMTIME when;

            GetSystemTime(&when);

            sprintf(timeBuf,
                        "%04d%02d%02d%02d%02d%02d",
                            when.wYear,
                                when.wMonth,
                                    when.wDay,
                                        when.wHour,
                                            when.wMinute,
                                                when.wSecond);
            */
            traceLog("Not finished: GetCurTime");

            return 0;

        }

        public static unsafe int getTimelStr(Int64 t, byte* timeBuf, uint size)
        {

            /*
     struct tm     *	p		=	NULL;
	 struct tm         when;
     
	 if  (  !(p  =  mylocaltime(  &t  )  )  )  return  -1;

     when  =  *p;		 
	 _snprintf(timeBuf, size,  "%04d%02d%02d%02d%02d%02d", when.tm_year  +  1900,
                when.tm_mon  +  1, when.tm_mday, when.tm_hour, when.tm_min,
                 when.tm_sec  );        
            */
   
	 return  0;

}



    public static int traceLog(string str  )
        {
            if (null!=GuiShare.pf_logd)
            {
                GuiShare.pf_logd("", str);
            }
            else
            {
                Console.WriteLine(str);
            }
            return 0;
        }

        public static int traceLog(string str0,string str1)
        {
            //Console.WriteLine("{0} {1}", str0, str1);
            if (null != GuiShare.pf_logd)
            {
                string str = string.Format("{0} {1}", str0, str1);
                GuiShare.pf_logd("",str);
            }
            return 0;
        }

        public static int traceLogA(string str)
        {
            //Console.WriteLine(str);
            if (null != GuiShare.pf_logd)
            {
                GuiShare.pf_logd("", str);
            }

            return 0;
        }

}
}
