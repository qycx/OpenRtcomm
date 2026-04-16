

#ifndef  __imCommType_defs_h__
#define  __imCommType_defs_h__	//  {

//
#include	"ancCommProc_defs.h"

//  2017/08/27



//






//  mis系统的参数在下面定义，2007/05/07
//#define		CONST_imCommType_base									3000


//  下面为由第三方可以自定义的区间, 在qyCommProc_open.h中定义
//  #define		CONST_imCommType_custom_base						32000
//
//  #define		CONST_imCommType_custom_max							(  40000  -  1  )


//#define ORG_FILE_SEND_LOGIC 
//#define MAX_FILE_SEND_BLOCK	50
#define DEFAULT_MAX_FILE_SEND_BLOCK		5


/////////////////////////////////////////////////

//  qnmPcComm.h
//  #define		CONST_imCommType_base								3000
//  

    

#define		CONST_imCommType_htmlContent							(  CONST_imCommType_base  +  1  )		//  2007/05/07
#define		CONST_imCommType_simpleResp								(  CONST_imCommType_base  +  2  )		//  2007/05/07
//  #define		CONST_imCommType_streamContent						(  CONST_imCommType_base  +  3  )		//  2007/08/01	//  2011/01/29
#define		CONST_imCommType_msgRoute								CONST_ancCommType_msgRoute				//  (  CONST_imCommType_base  +  4  )		//  2007/11/29
//
#define		CONST_imCommType_dataContent							(  CONST_imCommType_base  +  5  )		//  2008/01/26, 
#define		CONST_imCommType_lStream								(  CONST_imCommType_base  +  6  )		//  2008/04/01, 



//  
#define		CONST_imCommType_auth									(  CONST_imCommType_base  +  100  )		//  2007/08/01
#define		CONST_imCommType_authResp								(  CONST_imCommType_base  +  101  )		//  

#define		CONST_imCommType_mem									CONST_ancCommType_mem					//  (  CONST_imCommType_base  +  102  )		//  

#define		CONST_imCommType_struct									(  CONST_imCommType_base  +  103  )		//  2014/11/09
//
#define		CONST_imCommType_getCfgsReq								(  CONST_imCommType_base  +  110  )		//  2011/01/30

//
#define		CONST_imCommType_qisCaReq								(  CONST_imCommType_base  +  120  )

//
#define		CONST_imCommType_chkLogonIdReq							(  CONST_imCommType_base  +  130  )


//  
//  
#define		CONST_imCommType_retrieveImGrpListReq					(  CONST_imCommType_base  +  200  )
#define		CONST_imCommType_retrieveImGrpListResp					(  CONST_imCommType_base  +  201  )		//  2007/08/27
#define		CONST_imCommType_retrieveImGrpMemListReq				(  CONST_imCommType_base  +  202  )
#define		CONST_imCommType_retrieveImGrpMemListResp				(  CONST_imCommType_base  +  203  )
#define		CONST_imCommType_retrieveContactListReq					(  CONST_imCommType_base  +  204  )
#define		CONST_imCommType_retrieveContactListResp				(  CONST_imCommType_base  +  205  )
#define		CONST_imCommType_retrieveImObjListEndReq				(  CONST_imCommType_base  +  206  )
#define		CONST_imCommType_retrieveImObjListEndResp				(  CONST_imCommType_base  +  207  )

//  
#define		CONST_imCommType_messengerRegInfo						(  CONST_imCommType_base  +  220  )
#define		CONST_imCommType_messengerPcInfo						(  CONST_imCommType_base  +  221  )
#define		CONST_imCommType_messengerAccount						(  CONST_imCommType_base  +  222  )		//  2010/01/06

	
//  
#define		CONST_imCommType_refreshRecentFriendsReq				(  CONST_imCommType_base  +  230  )  
#define		CONST_imCommType_refreshRecentFriendsResp				(  CONST_imCommType_base  +  231  )  

//  
#define		CONST_imCommType_transferFileReq						(  CONST_imCommType_base  +  350  )		//  2007/06/23
#define		CONST_imCommType_transferFileReplyReq					(  CONST_imCommType_base  +  351  )
#define		CONST_imCommType_transferFileDataReq					(  CONST_imCommType_base  +  352  )		//  2007/06/23,
#define		CONST_imCommType_transferFileDataResp					(  CONST_imCommType_base  +  353  )		//  2007/06/23,
#define		CONST_imCommType_transferFileEndReq						(  CONST_imCommType_base  +  354  )		//  2007/06/23,
#define		CONST_imCommType_transferFileEndResp					(  CONST_imCommType_base  +  355  )		//  2007/06/23,
//
#define		CONST_imCommType_taskProcReq							(  CONST_imCommType_base  +  356  )		//  2008/05/29
#define		CONST_imCommType_taskProcResp							(  CONST_imCommType_base  +  357  )		//  2008/05/29

//
#define		CONST_imCommType_rtcCallReq								(  CONST_imCommType_base  +  360  )		//  2007/10/07, rtcè??????ó

//  
#define		CONST_imCommType_transferAvInfo							(  CONST_imCommType_base  +  405  )		//  2008/03/15, 
#define		CONST_imCommType_transferAvReplyInfo					(  CONST_imCommType_base  +  406  )		//  2008/03/16, 
//
#define		CONST_imCommType_transferVideoData						CONST_ancCommType_transferVideoData			//  (  CONST_imCommType_base  +  407  )		//  2008/03/15, 
//
#define		CONST_imCommType_transferVideoDataResp					(  CONST_imCommType_base  +  408  )		//  2008/03/15, 
//
#define		CONST_imCommType_transferAudioData						CONST_ancCommType_transferAudioData		//  (  CONST_imCommType_base  +  411  )		//  2008/04/16, 
//
#define		CONST_imCommType_transferAudioDataResp					(  CONST_imCommType_base  +  412  )		//  2008/04/21, 

#define		CONST_imCommType_remoteAssistReq						(  CONST_imCommType_base  +  420  )		//  2008/11/15, 

//
#define		CONST_imCommType_taskInteractionReq						(  CONST_imCommType_base  +  430  )		//  2009/02/23
#define		CONST_imCommType_confKey								(  CONST_imCommType_base  +  431  )		//  2009/02/23
#define		CONST_imCommType_confLayout								(  CONST_imCommType_base  +  432  )		//  2010/12/27
#define		CONST_imCommType_confState								(  CONST_imCommType_base  +  433  )		//  2017/09/17
#define		CONST_imCommType_confCtrlState							(  CONST_imCommType_base  +  434  )		//  
#define		CONST_imCommType_confRequestingMems						(  CONST_imCommType_base  +  435  )
#define		CONST_imCommType_confLayoutParam						(  CONST_imCommType_base  +  436  )		//
#define		CONST_imCommType_confNvrInfo							(  CONST_imCommType_base  +  437  )
#define		CONST_imCommType_statusConfLayoutParam					(  CONST_imCommType_base  +  438  )		//  2023/12/30

//
#define		CONST_imCommType_confReq								(  CONST_imCommType_base  +  450  )
#define		CONST_imCommType_testSpeedReq							(  CONST_imCommType_base  +  451  )		//  2016/12/28
#define		CONST_imCommType_mcuCmd									(  CONST_imCommType_base  +  452  )				


//
#define		CONST_imCommType_transferGpsInfo						(  CONST_imCommType_base  +  600  )		//  2012/04/19
#define		CONST_imCommType_transferGpsReplyInfo					(  CONST_imCommType_base  +  601  )		//  2012/04/19
#define		CONST_imCommType_transferGpsData						(  CONST_imCommType_base  +  602  )		//  2012/04/20
#define		CONST_imCommType_transferGpsDataResp					(  CONST_imCommType_base  +  603  )		//  2012/04/20

//  2012/08/05
#define		CONST_imCommType_ptzControlReq							(  CONST_imCommType_base  +  710  )
#define		CONST_imCommType_ptzControlCmd							(  CONST_imCommType_base  +  711  )

//
#define		CONST_imCommType_imGrp									(  CONST_imCommType_base  +  850  )		//  2017/07/29
#define		CONST_imCommType_refreshImGrp							(  CONST_imCommType_base  +  851  )		//  2007/08/23


//  
#define		CONST_imCommType_retrieveWebContactListReq				(  CONST_imCommType_base  +  900  )		//  2007/11/25￡?2é?ˉí???áa?μè?μ????ó
#define		CONST_imCommType_retrieveWebContactListResp				(  CONST_imCommType_base  +  901  )		//  2007/11/25￡?2é?ˉí???áa?μè?μ??ìó|
//
#define		CONST_imCommType_refreshWebContactsInfo					(  CONST_imCommType_base  +  902  )		//  2007/12/22
#define		CONST_imCommType_ipKnowledge							(  CONST_imCommType_base  +  903  )		//  2007/12/23, ipμ??aê??a.
//

//  
#define		CONST_imCommType_retrieveCustomerServiceObjListReq		(  CONST_imCommType_base  +  906  )		//  2011/04/04
#define		CONST_imCommType_queryCustomerServiceOfficerReq			(  CONST_imCommType_base  +  907  )		//  2011/04/04
#define		CONST_imCommType_queryCustomerServiceOfficerReplyReq	(  CONST_imCommType_base  +  908  )		//  2011/04/04

//
#define		CONST_imCommType_queryPeerStatus						(  CONST_imCommType_base  +  920  )		//  2014/07/11



//  gsmμ??ìD???ê?
#define		CONST_imCommType_smPkt									(  CONST_imCommType_base  +  1000  )		//  2008/01/05
#define		CONST_imCommType_phoneGuest								(  CONST_imCommType_base  +  1001  )		//  2008/01/20
#define		CONST_imCommType_vDevComs								(  CONST_imCommType_base  +  1002  )		//  2008/01/24, 3502, ìá??COM×′ì?
#define		CONST_imCommType_retrieveSmPolicy						(  CONST_imCommType_base  +  1003  )		//  2008/01/24, 3503, ??è?SM2????￡?÷òaê?smContacts
#define		CONST_imCommType_retrievePhoneMsgrs						(  CONST_imCommType_base  +  1004  )		//  2008/01/24, 3504, ??è?ê??úmessengeráD±í
#define		CONST_imCommType_retrieveToPaths						(  CONST_imCommType_base  +  1005  )		//  2008/01/24, 3505, ??è?・￠?íí¨μàáD±í
//
#define		CONST_imCommType_refreshDynBmps							(  CONST_imCommType_base  +  1006  )		//  2009/08/24
#define		CONST_imCommType_retrieveDynBmps						(  CONST_imCommType_base  +  1007  )		//  2009/09/04
#define		CONST_imCommType_refreshImObjRulesReq					(  CONST_imCommType_base  +  1008  )		//  2010/08/14
#define		CONST_imCommType_verifyViewDynBmp						(  CONST_imCommType_base  +  1009  )		//  2011/10/31, 校验查看该共享源的请求是否有效
//
#define		CONST_imCommType_vDevData								(  CONST_imCommType_base  +  1010  )		//  2008/01/24, 3503, 
//
#define		CONST_imCommType_procOfflineRes							(  CONST_imCommType_base  +  1011  )		//  2015/08/01


//  
#define		CONST_imCommType_qmdStatus								(  CONST_imCommType_base  +  1050  )		//  2011/01/08
//
#define		CONST_imCommType_qmdMcuStatusList						(  CONST_imCommType_base  +  1052  )
#define		CONST_imCommType_qmdPolicy								(  CONST_imCommType_base  +  1053  )

//
#define		CONST_imCommType_refreshImObjMemInfo					(  CONST_imCommType_base  +  1100  )


//
#define		CONST_imCommType_avStream								(  CONST_imCommType_base  +  1200  )


//  for internal use. 2015/08/24
#define		CONST_imCommType_qyCommSession							(  CONST_imCommType_base  +  1500  )	//  2015/08/24

//
//  é??T
//#define		CONST_imCommType_max									(  CONST_imCommType_base  +  1999  )	//  ????・t??á???2000???á11μ?ààDí




#endif  //  }


