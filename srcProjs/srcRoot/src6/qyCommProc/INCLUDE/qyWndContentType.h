

#ifndef  __qyWndContentType_h__
#define  __qyWndContentType_h__		//  {



//  2016/06/03
#define		CONST_qyWndContentType_base							CONST_qyQueryType_max  +  1
//
#define		CONST_qyWndContentType_testLocalAv					2048		//  2009/09/07
#define		CONST_qyWndContentType_vWall						2049		//  2009/09/21
#define		CONST_qyWndContentType_mcClientLogon				2050		//  2010/07/14
#define		CONST_qyWndContentType_qyMc_winCe					2051		
#define		CONST_qyWndContentType_qnmCfgOptionsIsClient		2052
#define		CONST_qyWndContentType_talker						2053
#define		CONST_qyWndContentType_objs							2054
#define		CONST_qyWndContentType_instantAssistant				2055
//#define		CONST_qyWndContentType_conferenceResources			2056		//  2010/12/20
#define		CONST_qyWndContentType_dlgVideos					2057		//  2011/02/02
#define		CONST_qyWndContentType_menu_walls					2059
#define		CONST_qyWndContentType_ts_main						2060		//  2013/07/13
//
#define		CONST_qyWndContentType_imObjView_cli				2062		//  2013/07/26
//
#define		CONST_qyWndContentType_dlgImg						2063		//  2013/09/26
#define		CONST_qyWndContentType_dlgChromaKeyCfg				2064		//  2013/09/28
#define		CONST_qyWndContentType_dlgMsgTool					2065		//  2014/01/25
#define		CONST_qyWndContentType_shareDynBmps					2066		//  2014/09/22
#define		CONST_qyWndContentType_testSpeed					2067		//  2016/12/27

//
#define		CONST_qyWndContentType_consoleWall					2170		//  2061
#define		CONST_qyWndContentType_generalWall					2171		//  2016/06/03

//
#define		CONST_qyWndContentType_menu_d3dWnd					2180		//  2016/06/08

//
#define		CONST_qyLvType_realTimeImTaskList					3006		//  520			//  2008/05/30
#define		CONST_qyLvType_taskInfoList							3007		//  520			//  2008/05/30
#define		CONST_qyLvType_sharingObjectList					3008		//  2013/02/06
#define		CONST_qyLvType_playerList							3009		//  
#define		CONST_qyLvType_wallList								3010
#define		CONST_qyLvType_imNetStatList						3011
#define		CONST_qyLvType_talkerList							3012
#define		CONST_qyLvType_messengerStatusList					3013
#define		CONST_qyLvType_unprocedImTaskList					3014		//  2013/02/17
#define		CONST_qyLvType_currentImTaskList					3015		//  2013/02/17
//
#define		CONST_qyWndContentType_qList						3016		//  2011/01/20
//
#define		CONST_qyLvType_myDbStatus							3017		//  2013/02/22
//
#define		CONST_qyLvType_imObjList							3030		//	2014/04/17
#define		CONST_qyLvType_regInfoList							3031		//	2014/04/17
#define		CONST_qyLvType_imGrpList							3032		//	2014/04/17
#define		CONST_qyLvType_imGrpMemList							3033		//	2014/04/17
#define		CONST_qyLvType_imObjRuleList						3034		//	2014/04/17
#define		CONST_qyLvType_dynBmpList							3035		//	2014/04/18
//
#define		CONST_qyLvType_ipCamList							3036		//  2016/07/30


//
#define		CONST_qyLvType_procedObjList						4096		//  500			//  2006/12/24
#define		CONST_qyLvType_monIfFlow							4097		//  501			//  2007/01/01
//


//
#define		CONST_qyLvType_anyObjList							4200		//  600			//  2008/01/01


//
#define		CONST_qyBarType_bar										4300					//  2018/06/25
#define		CONST_qyBarType_avRes									4301



//  2012/04/02
#define		CONST_vwSubtype_null									0
//  #define		CONST_vwSubType_global								10
#define		CONST_vwSubtype_confWall								10
#define		CONST_vwSubtype_globalGps								11
//
#define		CONST_vwSubtype_gps										100

//
#define		CONST_vwSubtype_bgWall									150
#define		CONST_vwSubtype_avStream								151			//  2018/12/18

//  2015/05/09
#define		CONST_vwSubtype_qvcf									200

//
#define		isVwSubtype_gps(  vwSubtype  )							(  (  vwSubtype  )  ==  CONST_vwSubtype_gps  ||  (  vwSubtype  )  ==  CONST_vwSubtype_globalGps  )
#define		isVwSubtype_confWall(  vwSubtype  )						(  (  vwSubtype  )  ==  CONST_vwSubtype_confWall  ||  (  vwSubtype  )  ==  CONST_vwSubtype_globalGps  )


//  2017/10/02
#define		CONST_dlgVideosSubtype_null								0
#define		CONST_dlgVideosSubtype_view								10
#define		CONST_dlgVideosSubtype_enlargedWnd						20
#define		CONST_dlgVideosSubtype_remoteAssist						30



//
#define		CONST_talkUsage_null									0
#define		CONST_talkUsage_doConf									1



//  2012/04/30
#define		CONST_talkerSubtype_null								0
//
#define		CONST_talkerSubtype_video								10
//
#define		CONST_talkerSubtype_onVWall								100				//  ????messenger????
#define		CONST_talkerSubtype_onVWall_global						101				//  ?globalWall?talkers?????,2012/05/12
//2014/12/22
#define		CONST_talkerSubtype_3dTool								110				//  3dWall?????talker. 2014/12/22
//
#define		CONST_talkerSubtype_enlarged							200				//  
#define		CONST_talkerSubtype_enlarged_mgr						201				//  ????????

//  ??????????????????????????
//  #define		isTalkerSubtype_canInput(  iTalkerSubType  )			(  iTalkerSubType  ==  CONST_talkerSubType_enlarged  ||  iTalkerSubType  ==  CONST_talkerSubType_onVWall_global  ||  iTalkerSubType  ==  CONST_talkerSubType_enlarged_mgr  )    
#define		isTalkerSubtype_canInput(  iTalkerSubtype  )			(  iTalkerSubtype  !=  CONST_talkerSubtype_onVWall  )    //  2014/12/22


//  2013/09/26
#define		CONST_dlgImgSubtype_null								0
#define		CONST_dlgImgSubtype_chromaKey							100

//
#define		CONST_tvSubtype_null									0
#define		CONST_tvSubtype_avRes									100



#endif  //  }



