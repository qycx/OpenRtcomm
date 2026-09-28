
#ifndef  __anCommProc_defs_h__
#define  __anCommProc_defs_h__		//  {

//
#include	"myTypes_basic.h"





#ifndef  __USE_atCommVer_1_old_proto__


//
// 普通的cfgId都定义在4100之后，重要的cfgId定义<4096之前(12bits).
//#define		CONST_anCfgId_base_common							4096		//  1000
#define		CONST_anCfgId_base_common								4100		//  1000


//
// 普通的commType定义在4000之后，重要的在之前。最重要的<256
#define		CONST_anCommType_base									4000


/////////////////  这里定义重要的cfgId. < 4096

#define		CONST_anCfgId_null										0		//  
//
#define		CONST_anCfgId_start										1		//  (  CONST_qnmCfgId_base_common  +  100  )
#define		CONST_anCfgId_mem										2		//  (  CONST_qnmCfgId_base_common  +  101  )				//  2007/08/05, 只用在小而快的数据包。一般的包的成员要使用CONST_imCommType_mem
//
#define		CONST_anCfgId_messengerId_from							3		//  (  CONST_qnmCfgId_base_common  +  2640  )				//  2007/11/29
#define		CONST_anCfgId_messengerId_to							4		//  (  CONST_qnmCfgId_base_common  +  2641  )				//  2007/11/29
#define		CONST_anCfgId_uiMsgRouteId								5		//  (  CONST_qnmCfgId_base_common  +  2650  )				//  2008/05/27
#define		CONST_anCfgId_messengerId								6		//  (  CONST_qnmCfgId_base_common  +  2500  )

//
#define		CONST_anCfgId_uiTranNo_openAudioDev					20		//  (  CONST_qnmCfgId_base_common  +  4051  )				//  
#define		CONST_anCfgId_usCnt									21		//  (  CONST_qnmCfgId_base_common  +  2101  )				//  2007/08/01
//
#define		CONST_anCfgId_uiSampleTimeInMs							22		//  (  CONST_qnmCfgId_base_common  +  4054  )				//  2009/05/04
#define		CONST_anCfgId_uiPts									23		//  (  CONST_qnmCfgId_base_common  +  4057  )				//  2015/01/15
#define		CONST_anCfgId_uiLen									24		//  (  CONST_qnmCfgId_base_common  +  2110  )				//  2008/10/30
#define		CONST_anCfgId_rawData									25		//  (  CONST_qnmCfgId_base_common  +  3508  )				//  2008/03/23
#define		CONST_anCfgId_usElapseInMs_fromLastPkt					26

//
#define		CONST_anCfgId_uiTranNo_openVideoDev					30		// 	(  CONST_qnmCfgId_base_common  +  4050  )				//  
#define		CONST_anCfgId_ucbKeyFrame								31		//  (  CONST_qnmCfgId_base_common  +  4058  )

//
#define		CONST_anCfgId_conf_ui64Id								40		

//
#define		CONST_anCfgId_lfcs_tn									50			//  2026/09/23
#define		CONST_anCfgId_mfcs_tn									51
#define		CONST_anCfgId_hfcs_tn									52
#define		CONST_anCfgId_hfcs_cliNetstats							53			//
#define		CONST_anCfgId_hfcs_cliPktLoss							54




/////这里定义普通的cfgId.  CONST_anCfgId_base_common  +  n



//
// communication data type
//////////////////////// 这里定义中最重要的anCommType. <256
//
#define		CONST_anCommType_msgRoute								1
#define		CONST_anCommType_mem									2		//  (  CONST_imCommType_base  +  102  )		//  
//
#define		CONST_anCommType_transferAudioData						4		//  (  CONST_imCommType_base  +  411  )		//  2008/04/16, 
#define		CONST_anCommType_transferVideoData						5		//  (  CONST_imCommType_base  +  407  )		//  2008/03/15, 
//
#define		CONST_anCommType_refreshRecentFriendsReq1				8		//  2026/09/18



//  这里定义重要的anCommType  < 4000


/////////////// 这里定义普通的ancCommType. CONST_anCommType_base  +  n

//
#else


//
#define		CONST_anCfgId_null										0		//  



//
#define		CONST_anCfgId_base_common								1000

#define		CONST_anCommType_base									3000







//////////////////////////////////////
#define		CONST_anCfgId_start								(  CONST_anCfgId_base_common  +  100  )
#define		CONST_anCfgId_mem									(  CONST_anCfgId_base_common  +  101  )				//  2007/08/05, 只用在小而快的数据包。一般的包的成员要使用CONST_imCommType_mem

//
#define		CONST_anCfgId_usCnt								(  CONST_qnmCfgId_base_common  +  2101  )				//  2007/08/01

#define		CONST_anCfgId_uiLen									(  CONST_qnmCfgId_base_common  +  2110  )				//  2008/10/30

//
#define		CONST_anCfgId_messengerId_from						(  CONST_qnmCfgId_base_common  +  2640  )				//  2007/11/29
#define		CONST_anCfgId_messengerId_to						(  CONST_qnmCfgId_base_common  +  2641  )				//  2007/11/29
#define		CONST_anCfgId_uiMsgRouteId							(  CONST_qnmCfgId_base_common  +  2650  )				//  2008/05/27
#define		CONST_anCfgId_messengerId							(  CONST_qnmCfgId_base_common  +  2500  )


//
#define		CONST_anCfgId_uiTranNo_openAudioDev				(  CONST_qnmCfgId_base_common  +  4051  )				//  

#define		CONST_anCfgId_uiSampleTimeInMs						(  CONST_qnmCfgId_base_common  +  4054  )				//  2009/05/04
//
#define		CONST_anCfgId_uiTranNo_openVideoDev					(  CONST_qnmCfgId_base_common  +  4050  )				//  
#define		CONST_anCfgId_ucbKeyFrame								(  CONST_qnmCfgId_base_common  +  4058  )

#define		CONST_anCfgId_rawData									(  CONST_qnmCfgId_base_common  +  3508  )				//  2008/03/23

#define		CONST_anCfgId_uiPts									(  CONST_qnmCfgId_base_common  +  4057  )				//  2015/01/15





/////////////////////////
//
#define		CONST_anCommType_msgRoute								(  CONST_imCommType_base  +  4  )		//  2007/11/29
//
#define		CONST_anCommType_mem									(  CONST_imCommType_base  +  102  )		//  

//
#define		CONST_anCommType_transferAudioData						(  CONST_imCommType_base  +  411  )		//  2008/04/16, 
#define		CONST_anCommType_transferVideoData						(  CONST_imCommType_base  +  407  )		//  2008/03/15, 


//
#endif 


//  注意，这里是cfgId的定义. 是字段的定义
#define		CONST_qnmCfgId_base_common								CONST_anCfgId_base_common	


//  注意，这里是commType的定义，是小段数据流的定义
#define		CONST_imCommType_base									CONST_anCommType_base


//
#define		CONST_iWaitTimeInMs_rtMedia		1000
#define		CONST_iWaitTimeInMs_media		1000


 //  命令码
 //			 类型：unsigned  short

//
#ifndef  __USE_atCommVer_2_old_proto__
 //			 低端保留：
//#define		CONST_atCmd_null								0
//
#define		CONST_atCmd_tellService								1								//  "启动服务"
#define		CONST_atCmd_end										255								//  "结束会话"

//
#define		CONST_atCmd_getCfgs									(  2  )


//  
#define		CONST_qyCmd_showInfo								(  10  )	//  
#define		CONST_qyCmd_showInfo_small							(  11  )	// 
#define		CONST_qyCmd_showInfo_small_java						(  12  )

//
#define		CONST_qyCmd_refreshImObjListReq						(  13  )	//  
//
#define		CONST_qyCmd_refreshRecentFriendsReq					(  14  )	//  
//
#define		CONST_qyCmd_mcComm									(  15  )	//  2011/01/08
//
#define		CONST_qyCmd_sendReq									(  16  )

//
#define		CONST_qyCmd_ca										(  17  )	//  
//
#define		CONST_qyCmd_hg										(  18  )	//

//
#define		CONST_qyCmd_talkTo									(  19  )	//  

#define		CONST_qyCmd_sendTask								(  20  )	//  
#define		CONST_qyCmd_sendTaskReply							(  21  )	//  
#define		CONST_qyCmd_sendRobotTask							(  22  )	//  
#define		CONST_qyCmd_sendRobotTaskReply						(  23  )	//  
#define		CONST_qyCmd_sendRobotTaskData						(  24  )	//  
//
#define		CONST_qyCmd_sendMedia								(  25  )	//  ??????
//
#define		CONST_qyCmd_lastMsgInSession						(  26  )	//  webMessenger?cgi
//
#define		CONST_qyCmd_sendVDevReq								(  27  )	//  
//
#define		CONST_qyCmd_chkLogonId								(  28  )	//  2023/06/14


//
 //  
 //			 unsigned  short
 //			 
#define		CONST_qyRc_ok							(  (  unsigned  short  )0  )
#define		CONST_qyRc_err							(  (  unsigned  short  )255  )
 //			 
#define		CONST_qyRc_user							(  10  )		// (  (  unsigned  short  )2048  )
#define		CONST_qyRc_redirect						(  11  )
#define		CONST_qyRc_needAutoReg					(  12  )  
//  #define		CONST_qyRc_notFound					(  13  )  		//  2005/02/01
#define		CONST_qyRc_needVerified					(  14  )		//  2007/04/22
#define		CONST_qyRc_anotherLogonExists			(  15  )		//  2011/02/02


#define		CONST_qyRc_peerOffline					(  16  )			//  2007/05/29
#define		CONST_qyRc_servBusy						(  17  )			//  2007/05/29
#define		CONST_qyRc_unknown						(  18  )			//  2007/07/01








//////////////////////////////


#else

//
#define		CONST_atCmd_tellService					0								//  "启动服务"
#define		CONST_atCmd_end							255								//  "结束会话"

//
#define		CONST_atCmd_getCfgs									(  CONST_qyCmd_base  +  2  )


//
#if  10

//  2007/04/23, mis
#define		CONST_qyCmd_showInfo								(  CONST_qyCmd_base  +  200  )	//  
#define		CONST_qyCmd_showInfo_small							(  CONST_qyCmd_base  +  201  )	// 
#define		CONST_qyCmd_showInfo_small_java						(  CONST_qyCmd_base  +  202  )

//
#define		CONST_qyCmd_refreshImObjListReq						(  CONST_qyCmd_base  +  205  )	//  
//
#define		CONST_qyCmd_refreshRecentFriendsReq					(  CONST_qyCmd_base  +  207  )	//  
//
#define		CONST_qyCmd_mcComm									(  CONST_qyCmd_base  +  210  )	//  2011/01/08
//
#define		CONST_qyCmd_sendReq									(  CONST_qyCmd_base  +  220  )

//
#define		CONST_qyCmd_ca										(  CONST_qyCmd_base  +  225  )	//  
//
#define		CONST_qyCmd_hg										(  CONST_qyCmd_base  +  226  )	//

//
#define		CONST_qyCmd_talkTo									(  CONST_qyCmd_base  +  300  )	//  

#define		CONST_qyCmd_sendTask								(  CONST_qyCmd_base  +  320  )	//  
#define		CONST_qyCmd_sendTaskReply							(  CONST_qyCmd_base  +  321  )	//  
#define		CONST_qyCmd_sendRobotTask							(  CONST_qyCmd_base  +  322  )	//  
#define		CONST_qyCmd_sendRobotTaskReply						(  CONST_qyCmd_base  +  323  )	//  
#define		CONST_qyCmd_sendRobotTaskData						(  CONST_qyCmd_base  +  324  )	//  
//
#define		CONST_qyCmd_sendMedia								(  CONST_qyCmd_base  +  330  )	//  ??????
//
#define		CONST_qyCmd_lastMsgInSession						(  CONST_qyCmd_base  +  340  )	//  webMessenger?cgi
//
#define		CONST_qyCmd_sendVDevReq								(  CONST_qyCmd_base  +  350  )	//  
//
#define		CONST_qyCmd_chkLogonId								(  CONST_qyCmd_base  +  360  )	//  2023/06/14


#endif 



///////////////////////////

#if  10
 //  
 //			 unsigned  short
 //			 
#define		CONST_qyRc_ok							(  (  unsigned  short  )0  )
#define		CONST_qyRc_err							(  (  unsigned  short  )255  )
 //			 
#define		CONST_qyRc_user							(  (  unsigned  short  )2000  )		// (  (  unsigned  short  )2048  )
#define		CONST_qyRc_redirect						(  (  unsigned  short  )(  CONST_qyRc_user  +  1  )  )
#define		CONST_qyRc_needAutoReg					(  (  unsigned  short  )(  CONST_qyRc_user  +  2  )  )
//  #define		CONST_qyRc_notFound						(  (  unsigned  short  )(  CONST_qyRc_user  +  3  )  )	//  2005/02/01
#define		CONST_qyRc_needVerified					(  (  unsigned  short  )(  CONST_qyRc_user  +  4  )  )		//  2007/04/22
#define		CONST_qyRc_anotherLogonExists			(  (  unsigned  short  )(  CONST_qyRc_user  +  5  )  )		//  2011/02/02


#define		CONST_qyRc_peerOffline					(  (  unsigned  short  )CONST_qyRc_user  +  100  )			//  2007/05/29
#define		CONST_qyRc_servBusy						(  (  unsigned  short  )CONST_qyRc_user  +  101  )			//  2007/05/29
#define		CONST_qyRc_unknown						(  (  unsigned  short  )CONST_qyRc_user  +  102  )			//  2007/07/01

#endif 



#endif 





//
#endif  //  }



