using System;
using System.Collections.Generic;
using System.Text;

namespace qy
{
    partial class qyFuncs
    {
        public static QY_DMITEM[] CONST_channelTypeTable = new QY_DMITEM[8]
        {
            //new QY_DMITEM(0,"",""),
            //new QY_DMITEM(1,"kk",""),
            //new QY_DMITEM(-1,"","")
            new QY_DMITEM(Consts.CONST_channelType_null,                             (  ""  )),
            new QY_DMITEM(Consts.CONST_channelType_talking,                          (  "Talk"  ) ),
            new QY_DMITEM(Consts.CONST_channelType_robot,                            (  "Robot"  )),
            new QY_DMITEM(Consts.CONST_channelType_webSending,                       (  "WebTalk"  )),
            new QY_DMITEM(Consts.CONST_channelType_media,                            (  "Video"  ) ),
            new QY_DMITEM(Consts.CONST_channelType_realTimeMedia,                    (  "Audio"  ) ),
            new QY_DMITEM(Consts.CONST_channelType_rtOp,                             (  "Op"  )),
            new QY_DMITEM( -1                                                                            ),
           };


        //
        public static unsafe QY_MESSENGER_ID* idStr2Info(byte* idStr, QY_MESSENGER_ID* pIdInfo)
        {
            int iErr = -1;

            if (null==idStr || null==pIdInfo) return null;

            pIdInfo->ui64Id = (UInt64  )float.Parse(mytoString(idStr)); //  2007/04/03, 这里暂时只取低位的数。
            return pIdInfo;
        }

        public static unsafe byte* idInfo2Str(QY_MESSENGER_ID* pIdInfo, byte* idStr, uint size)
        {
            if (null==pIdInfo || null==idStr || size <= Consts.CONST_qyMessengerIdStrLen) return null;
            //_snprintf(idStr, size, "%018I64u", pIdInfo->ui64Id);
            string str = string.Format("{0:D18}", pIdInfo->ui64Id);
            myWChar2Utf8(str, idStr, size);
            return idStr;
        }



    };

    };


    

