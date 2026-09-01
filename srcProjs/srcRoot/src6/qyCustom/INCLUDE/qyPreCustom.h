

#ifndef		__QYPRECUSTOM_H__
#define		__QYPRECUSTOM_H__	/*  {  */


//  ÒÔÏÂÊÇÏµÍ³±êÊ¶
#define		CONST_qySystemId_null							0
#define		CONST_qySystemId_bha							1
#define		CONST_qySystemId_bhb							2
#define		CONST_qySystemId_netMc2							3		//  µÚ¶þ°æ£¬Ö÷ÒªÎªÉÏº£º£¹ØÓÃ
#define		CONST_qySystemId_nms							4		//  Íø¹ÜÏµÍ³
#define		CONST_qySystemId_secChk							5		//  °²¼ìÏµÍ³
#define		CONST_qySystemId_netMc4							6		//  µÚËÄ°æ£¬Îª²ÆÕþ²¿±£ÃÜ°ìÓÃ
#define		CONST_qySystemId_assetMgr						7		//  ×Ê²ú¹ÜÀí
#define		CONST_qySystemId_customerMgr					8		//  ¿Í»§¹ÜÀí
#define		CONST_qySystemId_messenger						9		//  qyMsg,		//  2007/03/03


//  2017/06/21
#define		CONST_subSystemId_null							0
#define		CONST_subSystemId_basic							1
//
#define		CONST_subSystemId_standard						10



//  
#define		CONST_qyAppType_null							0
//  #define		CONST_qyAppType_mcForBar						1
//  #define		CONST_qyAppType_mcForPolice						2
#define		CONST_qyAppType_mc								3			//  ¹ÜÀíÖÐÐÄ
//  #define		CONST_qyAppType_simpleMc						4		//  ¶ÀÁ¢·Ö·¢¶Ë
//  #define		CONST_qyAppType_distributeMc					5		//  ·Ö×é¹ÜÀí¶Ë
#define		CONST_qyAppType_client							6			//  ¿Í»§¶Ë
#define		CONST_qyAppType_qwmSvr							CONST_qyAppType_client		//  ¿Í»§¶Ë
//  #define		CONST_qyAppType_qnmProxy					7			//  ¹ÜÀí´úÀí
#define		CONST_qyAppType_qyRegTool						8			//  ×¢²á¹¤¾ß
#define		CONST_qyAppType_interMonOfBhb					9			//  ¼àÊÓ¶Ë
//
#define		CONST_qyAppType_client_ts						11

//  
#define		CONST_qyAppId_null								0
#define		CONST_qyAppId_mcMain							1
#define		CONST_qyAppId_mcDaemon							2
//  #define		CONST_qyAppId_qnmHttpSvr						3
#define		CONST_qyAppId_qnmResp							4
#define		CONST_qyAppId_qnmProxy							5


//
#define		CONST_terminalType_null							0
#define		CONST_terminalType_conf							1			//  会议终端
#define		CONST_terminalType_mon							2			//  视频监控终端


//  2011/08/14
#if  0
#define		CONST_qyAppAvLevel_null							0
#define		CONST_qyAppAvLevel_mini							1							//  

																						//  
	
//  
#define		CONST_qyAppAvLevel_sd							3							//  
//
//  
#define		CONST_qyAppAvLevel_hd							5							//  
//
//  
#define		CONST_qyAppAvLevel_fullHd						10							//  

//
#define		CONST_qyAppAvLevel_top							15							//  
#endif



//  
//  
#define		CONST_qyModuleName_gui							"gui"
#define		CONST_qyModuleName_daemon						"daemon"
#define		CONST_qyModuleName_resp							"resp"
#define		CONST_qyModuleName_bhb							"bhb"
#define		CONST_qyModuleName_netMc2						"netMc2"
#define		CONST_qyModuleName_nms							"qnms"
#define		CONST_qyModuleName_netFlow						"netFlow"
#define		CONST_qyModuleName_secChk						"secChk"
//  #define		CONST_qyModuleName_netMc4						"netMc4"
#define		CONST_qyModuleName_assetMgr						"assetMgr"
//
#define		CONST_qyModuleName_msgrMgr						"msgrMgr"						//  2007/03/12

							

// ÒÔÏÂÊÇÎÄµµÀàÐÍ
#define		CONST_qyDocType_null							0
#define		CONST_qyDocType_mcRootTree						1
#define		QY_DOCTYPE_MCROOT								CONST_qyDocType_mcRootTree		//  ¹ÜÀíµ¥Î»¸ù´°¿Ú
#define		QY_DOCTYPE_MC									10								//  Ã»É¶ÓÃ
#define		QY_DOCTYPE_MCSITE								60
#define		QY_DOCTYPE_MCWEB								100
#define		CONST_qyDocType_mcQuery							110
#define		QY_DOCTYPE_MCQUERY								CONST_qyDocType_mcQuery
#define		CONST_qyDocType_mcView							120
	



#endif  /*  }  __QYPRECUSTOM_H__	defined  */



