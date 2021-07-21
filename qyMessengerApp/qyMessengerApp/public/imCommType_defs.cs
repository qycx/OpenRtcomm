﻿using System;
using System.Collections.Generic;
using System.Text;


partial class Consts
{
    public const int CONST_imCommType_base = 3000;






    /////////////////////////////////////////////////

    //  qnmPcComm.h
    //  public const int 		CONST_imCommType_base								3000

    //  
public const int  CONST_imCommType_htmlContent							=(  CONST_imCommType_base  +  1  );		//  2007/05/07
public const int  CONST_imCommType_simpleResp								=(  CONST_imCommType_base  +  2  );		//  2007/05/07
    //  public const int 		CONST_imCommType_streamContent						=(  CONST_imCommType_base  +  3  );		//  2007/08/01	//  2011/01/29
public const int  CONST_imCommType_msgRoute								=(  CONST_imCommType_base  +  4  );		//  2007/11/29
public const int  CONST_imCommType_dataContent							=(  CONST_imCommType_base  +  5  );		//  2008/01/26, 
public const int  CONST_imCommType_lStream								=(  CONST_imCommType_base  +  6  );		//  2008/04/01, 



    //  
public const int  CONST_imCommType_auth									=(  CONST_imCommType_base  +  100  );		//  2007/08/01
public const int  CONST_imCommType_authResp								=(  CONST_imCommType_base  +  101  );		//  
public const int  CONST_imCommType_mem									=(  CONST_imCommType_base  +  102  );		//  
public const int  CONST_imCommType_struct									=(  CONST_imCommType_base  +  103  );		//  2014/11/09
    //
public const int  CONST_imCommType_getCfgsReq								=(  CONST_imCommType_base  +  110  );		//  2011/01/30


    //  
    //  
public const int  CONST_imCommType_retrieveImGrpListReq					=(  CONST_imCommType_base  +  200  );
public const int  CONST_imCommType_retrieveImGrpListResp					=(  CONST_imCommType_base  +  201  );		//  2007/08/27
public const int  CONST_imCommType_retrieveImGrpMemListReq				=(  CONST_imCommType_base  +  202  );
public const int  CONST_imCommType_retrieveImGrpMemListResp				=(  CONST_imCommType_base  +  203  );
public const int  CONST_imCommType_retrieveContactListReq					=(  CONST_imCommType_base  +  204  );
public const int  CONST_imCommType_retrieveContactListResp				=(  CONST_imCommType_base  +  205  );
public const int  CONST_imCommType_retrieveImObjListEndReq				=(  CONST_imCommType_base  +  206  );
public const int  CONST_imCommType_retrieveImObjListEndResp				=(  CONST_imCommType_base  +  207  );

    //  
public const int  CONST_imCommType_messengerRegInfo						=(  CONST_imCommType_base  +  220  );
public const int  CONST_imCommType_messengerPcInfo						=(  CONST_imCommType_base  +  221  );
public const int  CONST_imCommType_messengerAccount						=(  CONST_imCommType_base  +  222  );		//  2010/01/06


    //  
public const int  CONST_imCommType_refreshRecentFriendsReq				=(  CONST_imCommType_base  +  230  );  
public const int  CONST_imCommType_refreshRecentFriendsResp				=(  CONST_imCommType_base  +  231  );  

    //  
public const int  CONST_imCommType_transferFileReq						=(  CONST_imCommType_base  +  350  );		//  2007/06/23
public const int  CONST_imCommType_transferFileReplyReq					=(  CONST_imCommType_base  +  351  );
public const int  CONST_imCommType_transferFileDataReq					=(  CONST_imCommType_base  +  352  );		//  2007/06/23,
public const int  CONST_imCommType_transferFileDataResp					=(  CONST_imCommType_base  +  353  );		//  2007/06/23,
public const int  CONST_imCommType_transferFileEndReq						=(  CONST_imCommType_base  +  354  );		//  2007/06/23,
public const int  CONST_imCommType_transferFileEndResp					=(  CONST_imCommType_base  +  355  );		//  2007/06/23,
    //
public const int  CONST_imCommType_taskProcReq							=(  CONST_imCommType_base  +  356  );		//  2008/05/29
public const int  CONST_imCommType_taskProcResp							=(  CONST_imCommType_base  +  357  );		//  2008/05/29

    //
public const int  CONST_imCommType_rtcCallReq								=(  CONST_imCommType_base  +  360  );		//  2007/10/07, rtcè??????ó

    //  
public const int  CONST_imCommType_transferAvInfo							=(  CONST_imCommType_base  +  405  );		//  2008/03/15, 
public const int  CONST_imCommType_transferAvReplyInfo					=(  CONST_imCommType_base  +  406  );		//  2008/03/16, 
public const int  CONST_imCommType_transferVideoData						=(  CONST_imCommType_base  +  407  );		//  2008/03/15, 
public const int  CONST_imCommType_transferVideoDataResp					=(  CONST_imCommType_base  +  408  );		//  2008/03/15, 
    //
public const int  CONST_imCommType_transferAudioData						=(  CONST_imCommType_base  +  411  );		//  2008/04/16, 
public const int  CONST_imCommType_transferAudioDataResp					=(  CONST_imCommType_base  +  412  );		//  2008/04/21, 

public const int  CONST_imCommType_remoteAssistReq						=(  CONST_imCommType_base  +  420  );		//  2008/11/15, 

public const int  CONST_imCommType_taskInteractionReq						=(  CONST_imCommType_base  +  430  );		//  2009/02/23
public const int  CONST_imCommType_confKey								=(  CONST_imCommType_base  +  431  );		//  2009/02/23
public const int  CONST_imCommType_confLayout								=(  CONST_imCommType_base  +  432  );		//  2010/12/27
public const int  CONST_imCommType_confState								=(  CONST_imCommType_base  +  433  );		//  2017/09/17

    //
public const int  CONST_imCommType_confReq								=(  CONST_imCommType_base  +  450  );
public const int  CONST_imCommType_testSpeedReq							=(  CONST_imCommType_base  +  451  );		//  2016/12/28


    //
public const int  CONST_imCommType_transferGpsInfo						=(  CONST_imCommType_base  +  600  );		//  2012/04/19
public const int  CONST_imCommType_transferGpsReplyInfo					=(  CONST_imCommType_base  +  601  );		//  2012/04/19
public const int  CONST_imCommType_transferGpsData						=(  CONST_imCommType_base  +  602  );		//  2012/04/20
public const int  CONST_imCommType_transferGpsDataResp					=(  CONST_imCommType_base  +  603  );		//  2012/04/20

    //  2012/08/05
public const int  CONST_imCommType_ptzControlReq							=(  CONST_imCommType_base  +  710  );
public const int  CONST_imCommType_ptzControlCmd							=(  CONST_imCommType_base  +  711  );

    //
public const int  CONST_imCommType_imGrp									=(  CONST_imCommType_base  +  850  );		//  2017/07/29
public const int  CONST_imCommType_refreshImGrp							=(  CONST_imCommType_base  +  851  );		//  2007/08/23

    //  
public const int  CONST_imCommType_retrieveWebContactListReq				=(  CONST_imCommType_base  +  900  );		//  2007/11/25￡?2é?ˉí???áa?μè?μ????ó
public const int  CONST_imCommType_retrieveWebContactListResp				=(  CONST_imCommType_base  +  901  );		//  2007/11/25￡?2é?ˉí???áa?μè?μ??ìó|
    //
public const int  CONST_imCommType_refreshWebContactsInfo					=(  CONST_imCommType_base  +  902  );		//  2007/12/22
public const int  CONST_imCommType_ipKnowledge							=(  CONST_imCommType_base  +  903  );		//  2007/12/23, ipμ??aê??a.
    //

    //  
public const int  CONST_imCommType_retrieveCustomerServiceObjListReq		=(  CONST_imCommType_base  +  906  );		//  2011/04/04
public const int  CONST_imCommType_queryCustomerServiceOfficerReq			=(  CONST_imCommType_base  +  907  );		//  2011/04/04
public const int  CONST_imCommType_queryCustomerServiceOfficerReplyReq	=(  CONST_imCommType_base  +  908  );		//  2011/04/04

    //
public const int  CONST_imCommType_queryPeerStatus						=(  CONST_imCommType_base  +  920  );		//  2014/07/11



    //  gsmμ??ìD???ê?
public const int  CONST_imCommType_smPkt									=(  CONST_imCommType_base  +  1000  );		//  2008/01/05
public const int  CONST_imCommType_phoneGuest								=(  CONST_imCommType_base  +  1001  );		//  2008/01/20
public const int  CONST_imCommType_vDevComs								=(  CONST_imCommType_base  +  1002  );		//  2008/01/24, 3502, ìá??COM×′ì?
public const int  CONST_imCommType_retrieveSmPolicy						=(  CONST_imCommType_base  +  1003  );		//  2008/01/24, 3503, ??è?SM2????￡?÷òaê?smContacts
public const int  CONST_imCommType_retrievePhoneMsgrs						=(  CONST_imCommType_base  +  1004  );		//  2008/01/24, 3504, ??è?ê??úmessengeráD±í
public const int  CONST_imCommType_retrieveToPaths						=(  CONST_imCommType_base  +  1005  );		//  2008/01/24, 3505, ??è?·￠?íí¨μàáD±í
    //
public const int  CONST_imCommType_refreshDynBmps							=(  CONST_imCommType_base  +  1006  );		//  2009/08/24
public const int  CONST_imCommType_retrieveDynBmps						=(  CONST_imCommType_base  +  1007  );		//  2009/09/04
public const int  CONST_imCommType_refreshImObjRulesReq					=(  CONST_imCommType_base  +  1008  );		//  2010/08/14
public const int  CONST_imCommType_verifyViewDynBmp						=(  CONST_imCommType_base  +  1009  );		//  2011/10/31, 校验查看该共享源的请求是否有效
    //
public const int  CONST_imCommType_vDevData								=(  CONST_imCommType_base  +  1010  );		//  2008/01/24, 3503, 
    //
public const int  CONST_imCommType_procOfflineRes							=(  CONST_imCommType_base  +  1011  );		//  2015/08/01


    //  
public const int  CONST_imCommType_qmdStatus								=(  CONST_imCommType_base  +  1050  );		//  2011/01/08
    //
public const int  CONST_imCommType_qmdConfStatusList						=(  CONST_imCommType_base  +  1052  );
public const int  CONST_imCommType_qmdPolicy								=(  CONST_imCommType_base  +  1053  );

    //
public const int  CONST_imCommType_avStream								=(  CONST_imCommType_base  +  1200  );


    //  for internal use. 2015/08/24
public const int  CONST_imCommType_qyCommSession							=(  CONST_imCommType_base  +  1500  );	//  2015/08/24

    //
    //  é??T
    //public const int 		CONST_imCommType_max									=(  CONST_imCommType_base  +  1999  );	//  ????·t??á???2000???á11μ?ààDí

}


namespace qy
{
}
