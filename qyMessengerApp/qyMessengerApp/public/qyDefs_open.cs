using System;
using System.Collections.Generic;
using System.Text;

public partial class Consts
{
    //
    public const int CONST_qyStatus_ok = 0;
    //  public const int		CONST_qyStatus_err									-1
    public const int CONST_qyStatus_err = 255;      //  2007/08/02, 
                                                    //
    public const int CONST_qyStatus_del = 32;       //  2007/05/12, 
    public const int CONST_qyStatus_update = 33;        //  2007/05/12

    //  		//  2009/01/01  

    public const int CONST_qyStatus_is_base = 500;      //  
                                                        //
    public const int CONST_imTaskStatus_null = 0;		//  
    //
public const int CONST_imTaskStatus_req									=(  CONST_qyStatus_is_base  +  11  );		//  
public const int CONST_imTaskStatus_resp									=(  CONST_qyStatus_is_base  +  12  );		//  same as applyToRecv
    //
public const int CONST_imTaskStatus_applyToSend							=(  CONST_qyStatus_is_base  +  21  );		//  
public const int CONST_imTaskStatus_waitToSend							=(  CONST_qyStatus_is_base  +  22  );		//  
public const int CONST_imTaskStatus_applyToRecv							=(  CONST_qyStatus_is_base  +  23  );		//  
public const int CONST_imTaskStatus_waitToRecv							=(  CONST_qyStatus_is_base  +  24  );		//  after accepted
    ///
public const int CONST_imTaskStatus_sending								=(  CONST_qyStatus_is_base  +  27  );		//  
public const int CONST_imTaskStatus_receiving							=(  CONST_qyStatus_is_base  +  28  );		//  
    //
public const int CONST_imTaskStatus_sendBreak							=(  CONST_qyStatus_is_base  +  31  );		//  
public const int CONST_imTaskStatus_recvBreak							=(  CONST_qyStatus_is_base  +  32  );		//  
    //
public const int CONST_imTaskStatus_recvFinished							=(  CONST_qyStatus_is_base  +  50  );		//  
public const int CONST_imTaskStatus_sendFinished							=(  CONST_qyStatus_is_base  +  51  );		//  
    //
public const int CONST_imTaskStatus_acceptedByReceiver					=(  CONST_qyStatus_is_base  +  60  );		//  2010/07/19
public const int CONST_imTaskStatus_dualByReceiver						=(  CONST_qyStatus_is_base  +  61  );		//  2010/07/19
    //
public const int CONST_imTaskStatus_err_missingOrgReq					=(  CONST_qyStatus_is_base  +  100  );  //  
    public const int CONST_imTaskStatus_err_cantGet_index_activeMems_from = (CONST_qyStatus_is_base + 101);	//  

    //
    public const int CONST_imTaskStatus_canceledBySender						=(  CONST_qyStatus_is_base  +  200  );	//  
public const int CONST_imTaskStatus_canceledByReceiver					=(  CONST_qyStatus_is_base  +  201  );	//  
public const int CONST_imTaskStatus_deniedByReceiver						=(  CONST_qyStatus_is_base  +  203  );	//  
public const int CONST_imTaskStatus_autoCanceledByReceiver				=(  CONST_qyStatus_is_base  +  204  );	//  2014/07/30


}

namespace qy
{
    //  2014/10/11
    public struct CAP_RECT
    {
        public int iX, iY;             //  
        public uint iW, iH;
    }
    ;

    partial class qyFuncs
{
        public static unsafe byte M_nalType_h264(byte* p)
        {
            return (byte)((p)[2] == 1 ? ((p)[3] & 0x1f) : ((p)[4] & 0x1f));
        }

        //
        public static void MACRO_safeFree(ref IntPtr x) {
            if ((null!=x)) { myfree(x); (x) = IntPtr.Zero; }
        }
        //
        public static void MACRO_mysafeFree(ref IntPtr x)
        {
            if ((null!=x)) { myfree(x); (x) = IntPtr.Zero; }
        }


    }
}
