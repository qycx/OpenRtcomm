
#include	"stdafx.h"
#include	"shlobj.h"
#ifndef  __WINCE__
		 #include	"myresource.h"
#endif

#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCustom.h"
#include	"qyTCharCommProc.h"

#include	"qyWmComm.h"
#include	"qyCommCommon.h"


#include	"qnmCommProc.h"

#include	"qnmResDefs.h"


#if  10
 QNM_GUICFG_INFO  CONST_qnmGuiCfgInfoTable[]  =																																														//  Mgr,  System,  Cfg,  pcList,  eventList,  netDevEventList,  searchList,
{
	{	CONST_qySystemId_bhb,		CONST_qyAppType_null,			(char*)"qyMcForbhb.jpg",				(char*)"qyMcForbhb.ini",					(char*)"qnmSplashForBhb.bmp",				(char*)"DECT",			0,  0,  0,		CONST_resId_popup_viewProcedObj_bhb,				1,	0,  0,  0,		CONST_resId_sys_bhb_intraMon,		},
	{	CONST_qySystemId_bhb,		CONST_qyAppType_interMonOfBhb,	(char*)"qyMcForInterMonOfBhb.jpg",		(char*)"qyMcForInterMonOfBhb.ini",			(char*)"qnmSplashForInterMonOfBhb.bmp",	(char*)"DECT",			0,  0,  0,		CONST_resId_popup_viewProcedObj_bhb,				1,	0,  0,  0,		CONST_resId_sys_bhb_interMon,		},
	{	CONST_qySystemId_netMc2,	CONST_qyAppType_null,			(char*)"qyMcForNetMc2.jpg",			(char*)"qyMcForNetMc2.ini",				(char*)"qnmSplashForNetMc2.bmp",			(char*)"netMc2",		1,  0,	0,		CONST_resId_popup_viewProcedObj_netMc2,				8,	0,  0,  0,		CONST_resId_sys_netMc2,				},
	{	CONST_qySystemId_nms,		CONST_qyAppType_null,			(char*)"qyMcForNms.jpg",				(char*)"qyMcForNms.ini",					(char*)"qnmSplashForNms.bmp",				(char*)"nms",			0,  1,  1,		CONST_resId_popup_viewProcedObj_nms,				15,	16,	17, 18,		CONST_resId_sys_nms,				},
	{	CONST_qySystemId_secChk,	CONST_qyAppType_null,			(char*)"qyMcForSecChk.jpg",			(char*)"qyMcForSecChk.ini",				(char*)"qnmSplashForSecChk.bmp",			(char*)"secChk",		0,  0,  0,		CONST_resId_popup_viewProcedObj_secChk,				13,	0,	0,  0,		CONST_resId_sys_secChk,				},
	//  {	CONST_qySystemId_netMc4,	CONST_qyAppType_null,		"qyMcForNetMc4.jpg",			(char*)"qyMcForNetMc4.ini",				(char*)"qnmSplashForNetMc4.bmp",			"netMc4",		1,  0,  0,		CONST_resId_popup_viewProcedObj_netMc4,				13,	0,	0,  0,											},
	{	CONST_qySystemId_assetMgr,	CONST_qyAppType_null,			(char*)"qyMcForAssetMgr.jpg",			(char*)"qyMcForAssetMgr.ini",				(char*)"qnmSplashForAssetMgr.bmp",			(char*)"assetMgr",		0,  1,  0,		CONST_resId_popup_viewProcedObj_assetMgr,			20,	0,	0,  0,		CONST_resId_sys_assetMgr,			},
	//
	{	CONST_qySystemId_messenger,	CONST_qyAppType_null,			(char*)"qyMessengerMgr.jpg",			(char*)"qyMessengerMgr.ini",				(char*)"qnmSplashForMessengerMgr.bmp",		(char*)"msg",			1,  0,	0,		CONST_resId_popup_viewProcedObj_misMgr,				8,	0,  0,  0,		CONST_resId_sys_isMgr,			},
#if  1  //def  __APP_qyMc_touchscreen__
	{	CONST_qySystemId_messenger,	CONST_qyAppType_client,			(char*)"qyMessenger.jpg",				(char*)"qyMessenger.ini",					(char*)"qyMessengerSplash.bmp",			(char *)"msg",			1,  0,	0,		CONST_resId_popup_viewProcedObj_misClient,			8,	0,  0,  0,		CONST_resId_sys_isCli_ts,			},
#else
	/*
	#ifndef  __noMfc__
			 {	CONST_qySystemId_messenger,	CONST_qyAppType_client,			(char*)"qyMessenger.jpg",				(char*)"qyMessenger.ini",					(char*)"qyMessengerSplash.bmp",			(char*)"msg",			1,  0,	0,		CONST_resId_popup_viewProcedObj_misClient,			8,	0,  0,  0,		CONST_resId_sys_isCli_default,			},
	#else
			 {	CONST_qySystemId_messenger,	CONST_qyAppType_client,			(char*)"qyMessenger.jpg",				(char*)"qyMessenger.ini",					(char*)"qyMessengerSplash.bmp",			(char*)"msg",			1,  0,	0,		CONST_resId_popup_viewProcedObj_misClient,			8,	0,  0,  0,		CONST_resId_sys_isCli_noMfc,			},
	#endif
	*/
#endif

	{	-1,							NULL,																																					},
};




 QNM_GUICFG_INFO	*	getQnmGuiCfgInfo(  int  iSystemId,  int  iAppType  )
{
	 QNM_GUICFG_INFO	*	p	=	NULL;

	 for  (  p  =  CONST_qnmGuiCfgInfoTable;  p->iSystemId  !=  -1;  p  ++  )  {
		  if  (  p->iSystemId  ==  iSystemId  &&  iAppType  ==  p->iAppType  )  return  p;
	 }
	 //  
	 for  (  p  =  CONST_qnmGuiCfgInfoTable;  p->iSystemId  !=  -1;  p  ++  )  {
		  if  (  p->iSystemId  ==  iSystemId  )  return  p;
	 }
	 return  NULL;
}

#endif


