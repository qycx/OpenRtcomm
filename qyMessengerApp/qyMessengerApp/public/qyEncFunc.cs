using System;
using System.Collections.Generic;
using System.Text;

partial class Consts
{
    public const int CONST_qyEncType_null = 0;
    public const int CONST_qyEncType_des = 1;
    public const int CONST_qyEncType_qnm = 2;       //  不用
    public const int CONST_qyEncType_qwm = 3;       //  2004/01/02
    public const int CONST_qyEncType_rsa = 4;		//  2008/06/09


}

namespace qy
{
    public struct QY_ENC_CTX
    {

        public uint type;

        /*
        union  {
					 des_ctx des;
    }    u;
        */

};


partial class qyFuncs
{
}
}
