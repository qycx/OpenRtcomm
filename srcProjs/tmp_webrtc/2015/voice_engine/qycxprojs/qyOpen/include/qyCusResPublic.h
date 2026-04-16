
#ifndef  __QYCUSRESPUBLIC_H__
#define  __QYCUSRESPUBLIC_H__		//  {

#if  0
	#define  __SUPPORT_sm__
	#define  __SUPPORT_wwwQm__
#endif

#if  0	//  2013/03/07
	#define		__SUPPORT_customerService__
#endif


//  2005/11/10

#ifndef __SQLUCODE							//  Õª×Ô<sqlucode.h>

	#define SQL_WCHAR		 	(-8)
	#define SQL_WVARCHAR	 	(-9)
	#define SQL_WLONGVARCHAR 	(-10)

#endif

#ifndef		__QYPRECUSTOM_H__				//  2008/12/17
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
#endif

#ifndef		__QYSQLFUNC_H__
#define		CONST_ucbDsnless_true							(  unsigned  char  )TRUE
#endif


#include	"qyDmItem.h"


#ifndef  __QYDEFS_H__
	
	#define		CONST_qyStatType_others				99999
	#define		CONST_qyStatType_all				999991

#endif

#ifndef  __QYCFG_H__
	
	#define		CONST_qyMaxLabelLen							256						//  2006/08/01ÐÞ¸Ä£¬ÔÝ¶¨ListView×î´óÁÐÃû³¤¶È

#endif


#define		CONST_qyColumnDisplayType_null						0			//  Ö±½ÓÏÔÊ¾
#define		CONST_qyColumnDisplayType_long						1			//  
#define		CONST_qyColumnDisplayType_str						2			//  Ö±½ÓÏÔÊ¾
#define		CONST_qyColumnDisplayType_time						3			//  Ê¹ÓÃÊ±¼ä¸ñÊ½×ª»»
#define		CONST_qyColumnDisplayType_ip12						4			//  ÒÔip12¸ñÊ½´æ´¢
#define		CONST_qyColumnDisplayType_bool						5			//  ÒÔ"0",  "1"´æ´¢
#define		CONST_qyColumnDisplayType_mac						6			//  ÒÔÐ¡Ð´ÏÔÊ¾
#define		CONST_qyColumnDisplayType_lwrStr					7			//  ÒÔÐ¡Ð´ÏÔÊ¾
#define		CONST_qyColumnDisplayType_uprStr					8			//  ÒÔ´óÐ´ÏÔÊ¾
#define		CONST_qyColumnDisplayType_pcSp						9			//  ÒÔ´óÐ´ÏÔÊ¾
#define		CONST_qyColumnDisplayType_platformId				10			//  ²Ù×÷ÏµÍ³ÀàÐÍ
#define		CONST_qyColumnDisplayType_langId					11			//  ÓïÑÔÀàÐÍ
#define		CONST_qyColumnDisplayType_jqlx						12			//  »úÆ÷ÀàÐÍ
#define		CONST_qyColumnDisplayType_snmpBool					13			//  snmpBool
#define		CONST_qyColumnDisplayType_iBool						14			//  ²¼¶ûÁ¿£¬ÒÔ·Ç0ºÍ0£¨°üÀ¨null)´æ´¢
#define		CONST_qyColumnDisplayType_niBool					15			//  ²¼¶ûÁ¿£¬ÒÔ·Ç0ºÍ0£¨°üÀ¨null)´æ´¢, ·´ÏÔÊ¾£¬1ÏÔÊ¾·ñ£¬0ÏÔÊ¾ÊÇ
#define		CONST_qyColumnDisplayType_uLong						16			//  unsigned  long  2005/10/04
#define		CONST_qyColumnDisplayType_dwRegVal					17			//  ×¢²á±í¶Á³öµÄÊýÖµ£¬2006/05/22
#define		CONST_qyColumnDisplayType_lTime						18			//  2008/09/06


#define		CONST_qyColumnDisplayType_rasCmd					2049									//	²¦ºÅÈ¨ÏÞ
#define		CONST_qyColumnDisplayType_eventType					2050									//  ÊÂ¼þÀàÐÍ
#define		CONST_qyColumnDisplayType_assetType					2051									//  ×Ê²úÀàÐÍ
#define		CONST_qyColumnDisplayType_devCmd					2052									//  Éè±¸¹ÜÀí²ßÂÔ
#define		CONST_qyColumnDisplayType_ruleCmd					2053									//  ¹æÔòÀàÐÍ
#define		CONST_qyColumnDisplayType_adapterType				2054									//  Íø¿¨ÀàÐÍ£¬2005/05/25
#define		CONST_qyColumnDisplayType_pcNetworkPropType			2055									//  ÍøÂçÁ¬½ÓÀàÐÍ£¬2005/05/25
#define		CONST_qyColumnDisplayType_pcAdapterStatus			2056									//  Íø¿¨×´Ì¬
#define		CONST_qyColumnDisplayType_pcEventLogType			2057									//  2005/09/01
#define		CONST_qyColumnDisplayType_pcEventId					2058									//  2005/09/01
#define		CONST_qyColumnDisplayType_pcCommType				2059									//  2005/09/17
#define		CONST_qyColumnDisplayType_tcpState					2060
//  #define		CONST_qyColumnDisplayType_pcProcessRuleType			2061									//  2005/10/10
#define		CONST_qyColumnDisplayType_withFactor				2062									//  2006/05/30
#define		CONST_qyColumnDisplayType_iRootKey					2063									//  2006/07/26
#define		CONST_qyColumnDisplayType_regType					2064									//  2006/07/26
#define		CONST_qyColumnDisplayType_qyStatus					2065									//  2006/08/08
#define		CONST_qyColumnDisplayType_bOnLine					2066									//  2006/08/13
#define		CONST_qyColumnDisplayType_netFlowRule				2067									//  2006/09/11
#define		CONST_qyColumnDisplayType_netShareType				2068									//  2007/02/16
#define		CONST_qyColumnDisplayType_qwmDevType				2069									//  2011/09/21

#define		CONST_qyColumnDisplayType_base_mis					10000
#define		CONST_qyColumnDisplayType_idStr						10001									//  2007/04/07
#define		CONST_qyColumnDisplayType_objType					10002									//  2007/07/29
#define		CONST_qyColumnDisplayType_imTaskType				10003									//  2007/08/10
#define		CONST_qyColumnDisplayType_imTaskStatus				CONST_qyColumnDisplayType_qyStatus		//  2007/08/10
#define		CONST_qyColumnDisplayType_usRunningStatus			10005									//  2007/08/20
#define		CONST_qyColumnDisplayType_ruleType					10006									//  2010/08/16
#define		CONST_qyColumnDisplayType_imGrpSubtype				10007									//  2014/01/31
#define		CONST_qyColumnDisplayType_imGrpMemRole				10008									//  2015/07/29


//
#ifndef  __QYGUIPUBLIC_H__


typedef  struct  __qyColumnInfo_t					{
				 int								type;
				 TCHAR								label[CONST_qyMaxLabelLen  +  1];
				 int								iDataType;
				 int								fmt;
				 unsigned	short					width;
				 unsigned	char					ucLevel;
				 unsigned	short					nMaxBytes;		//	×î´óµÄ×Ö½ÚÊý£¬0Îª²»ÏÞ
				 //
				 long								lParam;				//  2013/02/13
}		 QY_COLUMNINFO;



//  ÏÂÃæÊÇ¿Ø¼þµÄ×ÜÌåÊôÐÔ¿ØÖÆ
#define		CONST_qyIdcFlgChkNotNull				(  1		 )		//  ²»ÄÜÎª¿Õ
#define		CONST_qyIdcFlgSetLimitText				(  1  <<  1	 )
#define		CONST_qyIdcFlgChkFixedLen				(  1  <<  2	 )
#define		CONST_qyIdcFlgDisabled					(  1  <<  3	 )
#define		CONST_qyIdcFlgNotFocused				(  1  <<  4  )
#define		CONST_qyIdcFlgTrim						(  1  <<  5  )
#define		CONST_qyIdcFlgHide						(  1  <<  6  )		//  Òþ²Ø
#define		CONST_qyIdcFlgNeeded					(  1  <<  7  )		//  ¶ÔstaticÀ´Ëµ£¬±íÊ¾±ØÌîÏî; ¶ÔeditºÍcomboBoxÀ´Ëµ£¬¸Ã¿Ø¼þÎÞÂÛÊÇ·ñÒþ²Ø¶¼²ÉÓÃ
#define		CONST_qyIdcFlgUnused					(  1  <<  8  )		//  ¸Ã¿Ø¼þ²»Ê¹ÓÃ
#define		CONST_qyIdcFlgNotForEdit				(  1  <<  9  )		//  ÔÚ±à¼­ÉóºËÖÐ²»Ê¹ÓÃ£¬Òþ²Ø
#define		CONST_qyIdcFlgOnlyForEdit				(  1  <<  10  )		//  ½öÔÚ±à¼­ÉóºËÖÐÊ¹ÓÃºÍÏÔÊ¾
#define		CONST_qyIdcFlgAddNullItem				(  1  <<  11  )		//  ÔÚcomboÖÐ¼ÓÈëÒ»Ìõ¿ÕµÄ£¬ÒÔ·½±ãÌá¹©²»ÏÞÌõ¼þµÄÑ¡Ôñ£¬2005/02/12
#define		CONST_qyIdcFlgSearchUsingLike			(  1  <<  12  )		//  Ìá¹©Ä£ºý²éÑ¯£¬2006/05/03


//  ÏÂÃæÊÇ¿Ø¼þµÄÊäÈë·¶Î§ÏÞÖÆ
#define		CONST_qyIdcFlgPermitZw					(  1  <<  16  )		//  ÖÐÎÄ
#define		CONST_qyIdcFlgPermitAlpha				(  1  <<  17  )		//  Ó¢ÎÄ×Ö·û
#define		CONST_qyIdcFlgPermitXdigit				(  1  <<  18  )		//  16½øÖÆÊý×Ö
#define		CONST_qyIdcFlgPermitDigit				(  1  <<  19  )		//  10½øÖÆÊý×Ö
#define		CONST_qyIdcFlgPermitComma				(  1  <<  20  )		//  ','
#define		CONST_qyIdcFlgPermitSemicolon			(  1  <<  21  )		//  ';'
#define		CONST_qyIdcFlgPermitSpace				(  1  <<  22  )		//  space
#define		CONST_qyIdcFlgPermitMinus				(  1  <<  23  )		//  -
#define		CONST_qyIdcFlgPermitDot					(  1  <<  24  )		//  .
#define		CONST_qyIdcFlgPermitAll					(  0xffff0000  )	//  ²»¼ÓÏÞÖÆ

//  ¿Ø¼þÀàÐÍ
#define		CONST_qyIdcType_edit					1
#define		CONST_qyIdcType_combo					2
#define		CONST_qyIdcType_static					3
#define		CONST_qyIdcType_button					4
#define		CONST_qyIdcType_progress				5
#define		CONST_qyIdcType_ip						6
#define		CONST_qyIdcType_time					7
#define		CONST_qyIdcType_comboDesc				8		//  Ö¸ÏîÓÃÓÚ·ÖÀà£¬ÇÒ½µÐòÅÅÁÐ
#define		CONST_qyIdcType_chk						9		
#define		CONST_qyIdcType_listBox					10


#endif

#ifndef  __QNMCUSTOMGUI_H__

typedef  struct  __qnmQueryStruct_t  {
				 //  int							iQueryId;		//  ²éÑ¯µÄÖÖÀà£¬ÔÝÊ±²»ÓÃ
				 QY_COLUMNINFO		*				pSql;
				 QY_COLUMNINFO		*				pDisplay;
}		 QNM_QUERY_STRUCT;

	#define		CONST_jqlx_wj				0
	#define		CONST_jqlx_bxj				1
	#define		CONST_jqlx_fwq				2
	#define		CONST_jqlx_xxj				3
	#define		CONST_jqlx_qt				4

#endif

#ifndef  __QNMCOMMPROC_H__		//  {


#define		CONST_rasCmdStr_permitted						"7jkl"
#define		CONST_rasCmdStr_prohibited						"1000"
#define		CONST_rasCmdStr_offlinePermitted				"2cb4"

//  ×¢ÒârasCmd²»ÒªÈ¡Öµ0, ÒòÎªÒªÈë¿â
#define		CONST_rasCmd_default							1
#define		CONST_rasCmd_permitted							2
#define		CONST_rasCmd_prohibited							3
#define		CONST_rasCmd_offlinePermitted					4
#define		CONST_rasCmd_zdhmyx								5
//
#define		CONST_devCmd_permitted							CONST_rasCmd_permitted
#define		CONST_devCmd_prohibited							CONST_rasCmd_prohibited		//  只禁用设备。如果设备被锁住，那么也不重启操作系统
#define		CONST_devCmd_restartToProhibit					10							//  2005/06/22
#define		CONST_devCmd_permittedAndLog					11							//  2005/10/07, USB
#define		CONST_devCmd_prohibitedCanReboot				12							//  2011/08/28. 如果设备被锁住，那么可以重启操作系统
//
#define		CONST_devCmd_none								48							//  2007/02/13,	Î´ÅäÖÃ, ÓÃasciiµÄ'0'µÄÖµ£¬·½±ãÓÃÑÛ¾¦Ö±½Ó¿´²ßÂÔ

//

#define		CONST_fieldId_null								0
#define		CONST_fieldId_yhlx								100
#define		CONST_fieldId_syr								200
#define		CONST_fieldId_bm								201
#define		CONST_fieldId_dw								202
#define		CONST_fieldId_qtdw								203
#define		CONST_fieldId_bb								204
#define		CONST_fieldId_zb								205
//
#define		CONST_fieldId_zcbh0								220
#define		CONST_fieldId_zcbh1								221
#define		CONST_fieldId_zcbh2								222
//  #define		CONST_fieldId_zcsm0								223
#define		CONST_fieldId_zcsm1								224
#define		CONST_fieldId_zcsm2								225
#define		CONST_fieldId_jqlx								240
#define		CONST_fieldId_lxdh								241
#define		CONST_fieldId_sydd								242
#define		CONST_fieldId_zyyt								243
#define		CONST_fieldId_bz1								244
#define		CONST_fieldId_bz2								245


// ÊÂ¼þID¶¨Òå		¾¯¸æ£ºÑÏ½ûÐÞ¸ÄÏÂÃæµÄ¶¨Òå£¬ÒòÎªÕâÊÇÒÑ´æ´¢ÔÚÊý¾Ý¿âÖÐµÄ¶¨Òå£¬ÐÞ¸Ä½«Ê¹ÏÖÓÐµÄÏµÍ³ÎÞ·¨¼æÈÝ
//
#define		CONST_qyEventType_null								0
//		¼ÆËã»úÊÂ¼þID¶¨Òå
#define		CONST_qyEventType_nm_newPc							100
#define		CONST_qyEventType_nm_macsModified					101
#define		CONST_qyEventType_nm_macsModifiedPc					102
#define		CONST_qyEventType_nm_newReg							200
#define		CONST_qyEventType_nm_reReg							201
#define		CONST_qyEventType_nm_qwmDel							300
#define		CONST_qyEventType_nm_qwmDelRecovery					301
#define		CONST_qyEventType_nm_qwmDelOffline					302
#define		CONST_qyEventType_nm_ipChanged						400
#define		CONST_qyEventType_nm_osChanged						401
#define		CONST_qyEventType_nm_rasStart						500
#define		CONST_qyEventType_nm_rasEnd							501
#define		CONST_qyEventType_nm_rasProhibited					502
#define		CONST_qyEventType_nm_onInternet						503
#define		CONST_qyEventType_nm_offInternet					504
#define		CONST_qyEventType_nm_wLanAdapterStart				505				//  2010/05/20
#define		CONST_qyEventType_nm_wLanAdapterEnd					506				//  2010/05/20
#define		CONST_qyEventType_nm_wLanAdapterProhibited			507				//  2010/05/20
//
#define		CONST_qyEventType_nm_usbStorOnFor9x					510				//	2005/01/08			
#define		CONST_qyEventType_nm_usbStorOffFor9x				511				//  2005/01/08
#define		CONST_qyEventType_nm_usbStorIn						512				//  2005/01/07
#define		CONST_qyEventType_nm_usbStorUnallowedIn				513				//  2005/01/07
#define		CONST_qyEventType_nm_usbStorOut						514				//  2005/01/07
#define		CONST_qyEventType_nm_usbStorProhibited				515				//  2005/01/07
#define		CONST_qyEventType_nm_usbRestartToProhibit			516				//  2005/06/26
//
#define		CONST_qyEventType_nm_floppyOn						520				//  2005/01/08
#define		CONST_qyEventType_nm_floppyOff						521				//  2005/01/08
#define		CONST_qyEventType_nm_cdromOn						522				//  2005/01/08
#define		CONST_qyEventType_nm_cdromOff						523				//  2005/01/08
#define		CONST_qyEventType_nm_safeModeOn						524				//  2005/06/25
#define		CONST_qyEventType_nm_safeModeOff					525				//  2005/06/25
#define		CONST_qyEventType_nm_netShareMgr					526				//  2007/02/17
//
#define		CONST_qyEventType_nm_ucBlueToothProhibited			540				//  2010/08/18
#define		CONST_qyEventType_nm_ucInfraredProhibited			543				//  2010/08/18
#define		CONST_qyEventType_nm_uc1394Prohibited				546				//  2010/08/18
#define		CONST_qyEventType_nm_sdHostAdapterProhibited		547				//  2011/08/28

//
#define		CONST_qwmDevType_null								0				//  2011/09/21
#define		CONST_qwmDevType_wpd								1
#define		CONST_qwmDevType_mobileDevice						2
#define		CONST_qwmDevType_usbNetworkCard						3

//
#define		CONST_qyEventType_nm_devIn							560				//  2011/08/25
#define		CONST_qyEventType_nm_devOut							561				//  2011/08/25
#define		CONST_qyEventType_nm_devProhibited					562				//  2011/08/25
#define		CONST_qyEventType_nm_devEnabled						563				//  2011/08/25


//
#define		CONST_qyEventType_nm_strangePc						600
#define		CONST_qyEventType_nm_strangePcUnderCtrl				601
#define		CONST_qyEventType_nm_strangePcOffline				602
#define		CONST_qyEventType_nm_pcUnchked						603
#define		CONST_qyEventType_nm_pcAttacked						604
#define		CONST_qyEventType_nm_strangeIp						605				//  Î´×¢²áIPÊÂ¼þ
#define		CONST_qyEventType_nm_delPc							700
#define		CONST_qyEventType_nm_proxyServerSet					800
#define		CONST_qyEventType_nm_proxyServerClear				801
//
#define		CONST_qyEventType_nm_printerJob						810
//  #define		CONST_qyEventType_nm_fileMon						820
#define		CONST_qyEventType_nm_fileAdded						821				//  2006/03/23, ½«ÉÏÃæµÄÊÂ¼þ·Ö³ÉËÄ¸öÊÂ¼þ
#define		CONST_qyEventType_nm_fileRemoved					822
#define		CONST_qyEventType_nm_fileModified					823
#define		CONST_qyEventType_nm_fileRenamed					824
//
#define		CONST_qyEventType_nm_processMgr						830				//  2005/10/10
//
#define		CONST_qyEventType_nm_registryAdded					835				//  2006/07/31
#define		CONST_qyEventType_nm_registryRemoved				836				//  2006/07/31
#define		CONST_qyEventType_nm_registryModified				837				//  2006/07/31
//
#define		CONST_qyEventType_nm_netFlowWarn					840				//  2006/09/12

//
//		°²¼ìÊÂ¼þID¶¨Òå
#define		CONST_qyEventType_secChk_recent						900				//  ¼ì²é×î½üÊ¹ÓÃµÄÎÄ¼þ
#define		CONST_qyEventType_secChk_cookie						901				//  ¼ì²écookie
#define		CONST_qyEventType_secChk_proxyCfg					902				//  ¼ì²é´úÀíÉèÖÃ
#define		CONST_qyEventType_secChk_ieHistory					903				//  ¼ì²éÉÏÍøÁÙÊ±ÎÄ¼þ	
#define		CONST_qyEventType_secChk_fileHistory				904				//  ¼ì²éÎÄ¼þ¼ÇÂ¼
#define		CONST_qyEventType_secChk_shareDirectory				905				//  ¼ì²é¹²Ïí×ÊÔ´
#define		CONST_qyEventType_secChk_sharePrinter				906				//  ¼ì²é¹²Ïí´òÓ¡»ú
#define		CONST_qyEventType_secChk_rasPhoneBk					907				//  ¼ì²é²¦ºÅºÅÂë
#define		CONST_qyEventType_secChk_diskFile					908				//  ¼ì²é´ÅÅÌÎÄ¼þ
#define		CONST_qyEventType_secChk_diskFileDel				909				//  ¼ì²éÒÑÉ¾³ýµÄ´ÅÅÌÎÄ¼þ

//		ÓÃ»§Ê¹ÓÃµçÄÔµÄÊÂ¼þ
#define		CONST_qyEventType_nm_usrMgr							1200			//  ÓÃ»§¼¶¹ÜÀí£¬2007/02/18

//		ÍøÂçÉè±¸ÊÂ¼þID¶¨Òå
#define		CONST_qyEventType_nms_newDev						2000			//  ÐÂÔöÉè±¸
#define		CONST_qyEventType_nms_delDev						2001			//  É¾³ýÉè±¸
#define		CONST_qyEventType_nms_devOnline						2002			//  Éè±¸ÔÚÏß
#define		CONST_qyEventType_nms_devOffline					2003			//  Éè±¸ÀëÏß
#define		CONST_qyEventType_nms_willAttack					2004			//  Ö¸¶¨Éè±¸µÄÖ¸¶¨¶Ë¿Ú×è¶Ï
#define		CONST_qyEventType_nms_stopWillAttack				2005			//  Ö¸¶¨Éè±¸µÄÖ¸¶¨¶Ë¿ÚÍ£Ö¹×è¶Ï
#define		CONST_qyEventType_nms_newConnection					2006			//  ÐÂÔöÁª½Ó
#define		CONST_qyEventType_nms_connectionModified			2007			//  Áª½Ó±ä¸ü
//  #define		CONST_qyEventType_nms_newConnectionIp				2008			//  ÐÂÔöÁª½ÓIp
//  #define		CONST_qyEventType_nms_connectionIpModified			2009			//  Áª½ÓIP±ä¸ü
#define		CONST_qyEventType_nms_delConnection					2010			//  É¾³ýÒ»¸öÁª½Ó
#define		CONST_qyEventType_nms_warnSpeed						2011			//  Á÷Á¿±¨¾¯£¬2006/05/30
//  Ó¦ÓÃÏµÍ³Ê¹ÓÃÈËÔ±ÊÂ¼þID¶¨Òå
#define		CONST_qyEventType_nm_logon							3000			//  µÇÂ¼
#define		CONST_qyEventType_nm_logoff							3001			//  ÀëÂ¼
#define		CONST_qyEventType_nm_addUsr							3002			//  Ìí¼ÓÓÃ»§
#define		CONST_qyEventType_nm_delUsr							3003			//  É¾³ýÓÃ»§
#define		CONST_qyEventType_nm_modifyUsr						3004			//  ÐÞ¸ÄÓÃ»§
#define		CONST_qyEventType_nm_clearupEvent					3005			//  Çå¿ÕÊÂ¼þ
#define		CONST_qyEventType_nm_pzcz							3006			//  ÅäÖÃ²Ù×÷,  2005/10/01
#define		CONST_qyEventType_nm_sysWarn						3007			//  Ó¦ÓÃÏµÍ³×ÔÐÐ²úÉúµÄ¸æ¾¯£¬2005/10/03
#define		CONST_qyEventType_nm_viewRemoteDesktop				3008			//  Ê¹ÓÃÔ¶³Ì×ÀÃæ£¬2006/02/15
#define		CONST_qyEventType_nm_cancelRemoteDesktop			3009			//  È¡ÏûÔ¶³Ì×ÀÃæ£¬2006/02/15
#define		CONST_qyEventType_nm_denyRd							3010			//  Ô¶³Ì×ÀÃæ±»¾Ü¾ø£¬2006/02/15
#define		CONST_qyEventType_nm_autoAcceptRdAndRdStart			3011			//  ×Ô¶¯Æô¶¯Ô¶³Ì×ÀÃæ
#define		CONST_qyEventType_nm_promptToAcceptRdAndRdStart		3012			//  ÓÃ»§ÔÊÐíÆô¶¯Ô¶³Ì×ÀÃæ
#define		CONST_qyEventType_nm_logonFailed					3013			//  µÇÂ¼Ê§°Ü, 2006/02/25
#define		CONST_qyEventType_nm_export							3014			//  µ¼³ö
#define		CONST_qyEventType_nm_bak							3015			//  ±¸·Ý
#define		CONST_qyEventType_nm_import							3016			//  µ¼Èë
#define		CONST_qyEventType_nm_monDesktop						3017			//  ÊµÊ±¼à¿Ø×ÀÃæ£¬2006/02/15
#define		CONST_qyEventType_nm_cancelMonDesktop				3018			//  È¡ÏûÊµÊ±¼à¿Ø×ÀÃæ£¬2006/02/15
#define		CONST_qyEventType_nm_rdReqTimeout					3019			//  Ô¶³Ì×ÀÃæÎÞÈËÓ¦´ð£¬2006/06/15
#define		CONST_qyEventType_nm_clearupImMsg					3020			//  Çå¿ÕÏûÏ¢
#define		CONST_qyEventType_nm_clearupImHisTask				3021			//  Çå¿ÕÀúÊ·ÈÎÎñ


//  ×Ê²ú¹ÜÀíÊÂ¼þ¶¨Òå
#define		CONST_qyEventType_assetMgr_cpuAdd					3500			//  ÐÂÔöCPU
#define		CONST_qyEventType_assetMgr_cpuDel					3501			//  CPUÒÅÊ§
#define		CONST_qyEventType_assetMgr_memAdd					3502			//  ÐÂÔöÄÚ´æ
#define		CONST_qyEventType_assetMgr_memChanged				3503			//  ÄÚ´æ±ä¸ü
#define		CONST_qyEventType_assetMgr_biosAdd					3504			//  ÐÂÔöBIOS
#define		CONST_qyEventType_assetMgr_biosDel					3505			//  BIOSÒÅÊ§
#define		CONST_qyEventType_assetMgr_monitorAdd				3506			//  ÐÂÔö¼àÊÓÆ÷
#define		CONST_qyEventType_assetMgr_monitorDel				3507			//  ¼àÊÓÆ÷ÒÅÊ§
	//  
#define		CONST_qyEventType_assetMgr_ideDiskAdd				3520			//  ÐÂÔöIDEÓ²ÅÌ
#define		CONST_qyEventType_assetMgr_ideDiskDel				3521			//  IDEÓ²ÅÌÒÅÊ§
#define		CONST_qyEventType_assetMgr_ideCdromAdd				3522			//  ÐÂÔöDVD/CD-ROM
#define		CONST_qyEventType_assetMgr_ideCdromDel				3523			//  DVD/CD-ROMÒÅÊ§
#define		CONST_qyEventType_assetMgr_usbDiskAdd				3524			//  ÐÂÔöUSB´ÅÅÌ
#define		CONST_qyEventType_assetMgr_usbDiskDel				3525			//  USB´ÅÅÌÒÅÊ§
	//
#define		CONST_qyEventType_assetMgr_displayAdd				3550			//  ÐÂÔöÏÔ¿¨
#define		CONST_qyEventType_assetMgr_displayDel				3551			//  ÏÔ¿¨ÒÅÊ§
#define		CONST_qyEventType_assetMgr_networkCardAdd			3552			//  ÐÂÔöÍø¿¨
#define		CONST_qyEventType_assetMgr_networkCardDel			3553			//  Íø¿¨ÒÅÊ§
	//
#define		CONST_qyEventType_assetMgr_softwareAdd				3570			//  ÐÂ×°Èí¼þ
#define		CONST_qyEventType_assetMgr_softwareDel				3571			//  Èí¼þÐ¶ÔØ


////////////////////////////////
//
//

#define		CONST_qyEventType_is_base							20000			//  2007/05/08, misÏµÍ³µÄÊÂ¼þ»ùÊý
//
#define		CONST_qyEventType_is_newMessenger					(  CONST_qyEventType_is_base  +  100  )
//
#define		CONST_qyEventType_is_messengerLogon					(  CONST_qyEventType_is_base  +  110  )
#define		CONST_qyEventType_is_messengerLogoff				(  CONST_qyEventType_is_base  +  111  )
//
#define		CONST_qyEventType_is_connErr						(  CONST_qyEventType_is_base  +  115  )	//  Á¬½ÓÊ§°Ü
#define		CONST_qyEventType_is_memoryErr						(  CONST_qyEventType_is_base  +  116  )	//  2011/02/05

#if  0  //  2014/05/02. moved to qydefs_open.h

//  2008/12/16 
#define		CONST_objType_null					0
#define		CONST_objType_qySwitch				1
#define		CONST_objType_qySwitchPort			2
#define		CONST_objType_col2					3
#define		CONST_objType_col3					4
#define		CONST_objType_col4					5
#define		CONST_objType_unRegGrp				6
#define		CONST_objType_othersGrp				7
#define		CONST_objType_unRegPc				8
#define		CONST_objType_pc					CONST_objType_unRegPc						//  2007/06/09£¬±íÃ÷ÊÇ¸öPC
#define		CONST_objType_otherPc				9
#define		CONST_objType_mac					CONST_objType_otherPc						//  2007/06/09, ±íÃ÷Ã»ÓÐÊ²Ã´ÍêÕûµÄPCÐÅÏ¢£¬Ö»±íÃ÷Ò»¸öMAC
#define		CONST_objType_os					10											//  PC»ú²Ù×÷ÏµÍ³
#define		CONST_objType_pcEnv					11											//  PC»úÈíÓ²¼þ»·¾³
#define		CONST_objType_cfgSpOs				12											//  ²¹¶¡ÅäÖÃÀïµÄ²Ù×÷ÏµÍ³, 2005/01/23
#define		CONST_objType_cfgSpServicePack		13											//  ²¹¶¡ÅäÖÃÀïµÄServicePack, 2005/01/23
#define		CONST_objType_zb					14
#define		CONST_objType_bb					15
#define		CONST_objType_dw					CONST_objType_col2
#define		CONST_objType_bm					CONST_objType_col3
#define		CONST_objType_syr					CONST_objType_col4
#define		CONST_objType_pcStatus				16											//  ×´Ì¬ÏÔÊ¾£¬			2006/08/14
#define		CONST_objType_pcUsrInfo				17											//  ¼ÆËã»úÓÃ»§ÐÅÏ¢,		2006/08/14
#define		CONST_objType_pcOsClass				18											//  ²Ù×÷ÏµÍ³£¨Àà±ð£©,	2006/08/14
#define		CONST_objType_pcOpNode				19											//  ²Ù×÷½Úµã£¬			2006/08/15
#define		CONST_objType_procedObj				20											//  ¶àÊý¾ÝÔ´£¬			2007/01/02


																							//  2007/11/24
																							//  ×¢£ºÍøÂç¹ÜÀíµÄobjType³£Êý×îºÃÊÇÁíÍâÆðÒ»¸ö·¶Î§À´¶¨Òå¡£1000ÒÔÄÚ×îºÃÁô¸ø¸üÖØÒªµÄÍ¨ÓÃ³£Êý¡£
																							//
#define		CONST_objType_browser				501											//  ÊôÓÚdevType, ±íÃ÷´Ë¿Í»§¶ËÔËÐÐÔÚbrowserÀï							
//  #define		CONST_objType_phone					502										//  µç»°£¨ÊÖ»ú£©.ÔÚqnmCommProc_open.hÎÄ¼þÀï
//  #define		CONST_objType_dev					503										//  Ò»°ãÍâÉè.ÔÚqnmCommProc_open.hÎÄ¼þÀï
#define		CONST_objType_toPath				504											//
#define		CONST_objType_webcam				505											//  2009/08/28
#define		CONST_objType_screen				506											//  2009/08/28
//
#define		CONST_objType_rtspStream			507											//  2014/05/02


//  2007/05/12, ÒÔÏÂÎªmisÏµÍ³µÄÀàÐÍ¶¨Òå
#define		CONST_objType_mis_base				1000
//
#define		CONST_objType_admin					(  CONST_objType_mis_base  +  10  )			//  2007/08/23, ÏµÍ³¹ÜÀíÔ±
//
#define		CONST_objType_me					(  CONST_objType_mis_base  +  20  )
//
#define		CONST_objType_messenger				(  CONST_objType_mis_base  +  21  )
//  
#define		CONST_objType_webGuest				(  CONST_objType_mis_base  +  22  )			//  2007/11/21, webGuest
//
#define		CONST_objType_phoneMessenger		(  CONST_objType_mis_base  +  23  )			//  2008/01/30, ÓÃÊÖ»ú×¢²á£¬µ«ÊÇÃ»ÓÐ¿Í»§¶ËµÄ
#define		CONST_objType_phoneGuest			(  CONST_objType_mis_base  +  24  )			//  2008/01/07
//
#define		CONST_objType_newDevGuest			(  CONST_objType_mis_base  +  50  )			//  2008/01/07, ¶ÔÓ¦ÓÚnewDev


//																							//  20-100Ö®¼äÁô¸ø¸÷ÖÖÓÃ»§¶ÔÏó£»100ÒÔÉÏÁô¸ø¸÷Àà×é
#define		CONST_objType_imGrps				(  CONST_objType_mis_base  +  100  )		//  2007/08/23
#define		CONST_objType_imGrp					(  CONST_objType_mis_base  +  101  )	
//
#define		CONST_objType_tmpGrp				(  CONST_objType_mis_base  +  102  )		//  2008/01/22, ÁÙÊ±×é¡£Í¨³£ÔÚÓÚÁÙÊ±×é³ÉÒ»¸öQ, È»ºó´«µÝ¸ødlgTalk
//

//  2014/01/31
#define		CONST_imGrpSubtype_null				0
#define		CONST_imGrpSubtype_av				1
#define		CONST_imGrpSubtype_msg				2

#endif


//
#define		CONST_grpName_admin					"adminGrp"  		//  °Ñ×éÃûºÍÏÔÊ¾·Ö¿ª£¬2005/09/30
#define		CONST_grpName_xtpz					"sysGrp"  
#define		CONST_grpName_rzsj					"logGrp"  



#endif		//  }


//
#define		CONST_pcAdapterStatus_null					0	//
#define		CONST_pcAdapterStatus_willBeLocked			1	//  ´ýËø¶¨
#define		CONST_pcAdapterStatus_locked				2	//  ÒÑËø¶¨
#define		CONST_pcAdapterStatus_cantBeLocked			3	//  ÎÞ·¨Ëø¶¨



#ifndef  __QYCOMMPROC_OPEN_H__		//  {


#define		CONST_objType_phone						502												//  µç»°£¨ÊÖ»ú£©.ÔÚqnmCommProc_open.hÎÄ¼þÀï
#define		CONST_objType_dev						503												//  Ò»°ãÍâÉè.ÔÚqnmCommProc_open.hÎÄ¼þÀï

//
//  ×Ô¶¨ÒåµÄÀàÐÍ£¬Ó¦ÔÚ[CONST_objType_custom_base, CONST_objType_custom_max]Ö®¼ä
//
#define		CONST_objType_custom_base				32000											//  ÔÚqnmCommProc_open.hÎÄ¼þÀï
#define		CONST_objType_newDev					(  CONST_objType_custom_base  +  1  )			//  ÐÂÉè±¸,ÔÚqnmCommProc_open.hÎÄ¼þÀï

#define		CONST_objType_custom_max				(  40000  -  1  )								//  


#endif		//	}


// ²éÑ¯ÀàÐÍ¶¨Òå
#define		CONST_qyQueryType_null						0
#define		CONST_qyQueryType_general					1
#define		CONST_qyQueryType_mcCfgUrlList				2
#define		CONST_qyQueryType_netMcPcList				3
#define		CONST_qyQueryType_netMcScannedIpList		4
#define		CONST_qyQueryType_pcNetDevConnList			5
#define		CONST_qyQueryType_switchNetDevConnList		6
#define		CONST_qyQueryType_othersNetDevConnList		7
#define		CONST_qyQueryType_netMcEventList			10
#define		CONST_qyQueryType_netDevEventList			11
#define		CONST_qyQueryType_netMcPcSpList				12
#define		CONST_qyQueryType_pcAssetList				13
#define		CONST_qyQueryType_pcAssetReport				14			//  2005/01/26
#define		CONST_qyQueryType_snmpObjRuleList			15			//  2005/03/05
#define		CONST_qyQueryType_conflictConnList			16			//  2005/03/07
#define		CONST_qyQueryType_directConnList			17			//  2005/03/11
//  #define		CONST_qyQueryType_others					20		
#define		CONST_qyQueryType_mac						21
#define		CONST_qyQueryType_ip						22
#define		CONST_qyQueryType_unusedConn				23
#define		CONST_qyQueryType_bhbLog					24
#define		CONST_qyQueryType_clientList_netMc			25			//  2005/05/10
#define		CONST_qyQueryType_pcEventLogList			26			//  2005/10/03
#define		CONST_qyQueryType_pcOsUsrList				27			//  2005/10/03
#define		CONST_qyQueryType_pcNetStatList				28			//  2005/10/03
#define		CONST_qyQueryType_pcPrinterList				29			//  2005/10/03
#define		CONST_qyQueryType_pcProcessList				30			//  2005/10/03
//  #define		CONST_qyQueryType_pcSp					31
#define		CONST_qyQueryType_pcProcessRuleList			32			//  2005/10/10
//  #define		CONST_qyQueryType_pcAutoLogonList			33			//  2006/01/08
#define		CONST_qyQueryType_opEventList				34			//  2006/02/25
#define		CONST_qyQueryType_pcSecChkEventList			35			//  2006/03/06
#define		CONST_qyQueryType_pcProcessModuleList		36			//  2006/04/14
#define		CONST_qyQueryType_pcProcessKnowledgeList	37			//  2006/04/16
#define		CONST_qyQueryType_secChkEventList			38			//  2006/05/05
#define		CONST_qyQueryType_pcRegistryList			39			//  2006/07/26
#define		CONST_qyQueryType_pcRegistryKnowledgeList	40			//  2006/08/10
#define		CONST_qyQueryType_pcNetFlowList				41			//  2006/09/10
#define		CONST_qyQueryType_pcNetShareList			42			//  2007/02/15


//
#define		CONST_qyQueryType_imObjAuthList				101			//  2007/04/07
#define		CONST_qyQueryType_imGrpAuthList				102			//  2007/04/07
#define		CONST_qyQueryType_phoneMessengerList		103			//  2008/01/28
//
#define		CONST_qyQueryType_imObjAuthNeedAuditedList	106			//  2007/04/07
#define		CONST_qyQueryType_imGrpAuthNeedAuditedList	107			//  2007/04/07
#define		CONST_qyQueryType_imAmList					108			//  2010/01/05
//
#define		CONST_qyQueryType_imObjList					110			//  2007/04/07
#define		CONST_qyQueryType_imGrpList					111
#define		CONST_qyQueryType_imGrpMemList				112
#define		CONST_qyQueryType_imObjRegInfoList			113			//  2007/08/27
#define		CONST_qyQueryType_imObjRegInfoInTab1List	114			//  2007/08/27
#define		CONST_qyQueryType_clientList_is				115			//  2007/08/27
#define		CONST_qyQueryType_customerServiceList		116
#define		CONST_qyQueryType_wwwQmCfgList				117			//  2007/11/20
#define		CONST_qyQueryType_ipKnowledgeList			118			//  2007/12/23
#define		CONST_qyQueryType_phoneGuestList			119			//  2008/10/20
#define		CONST_qyQueryType_tmpGrpMemList				120
#define		CONST_qyQueryType_gsmModemList				121			//  2008/01/27
#define		CONST_qyQueryType_smContactList				122			//  2008/01/27
#define		CONST_qyQueryType_instantAssistantMemList	123			//  2009/02/24
#define		CONST_qyQueryType_sharedDynBmpList			124			//  2009/08/31
#define		CONST_qyQueryType_sharedDynBmpRuleList		125			//  2009/09/17
#define		CONST_qyQueryType_imObjRuleList				126			//  2010/08/16


//
#define		CONST_qyQueryType_imTaskList				320			//  2007/08/10
#define		CONST_qyQueryType_imTaskHisList				321			//  2007/08/11
#define		CONST_qyQueryType_imMsgList					325			//  2007/08/13
#define		CONST_qyQueryType_imEventList				326

//
#define		CONST_qyQueryType_max						512			//  2016/06/03





/////  2008/12/20,qylangcommproc.h
#define		CONST_langId_tw											0x0404			//  Chinese (Taiwan Region) 
#define		CONST_langId_PRC										0x0804			//  Chinese (PRC) 
#define		CONST_langId_hk											0x0c04			//  Chinese (Hong Kong SAR, PRC) 
#define		CONST_langId_Singapore									0x1004			//  Chinese (Singapore) 

#define		CONST_langId_US											0x0409			//  English (United States) 
#define		CONST_langId_UK											0x0809			//	English (United Kingdom) 
#define		CONST_langId_Australian									0x0c09			//  English (Australian) 
#define		CONST_langId_Candian									0x1009			//  English (Canadian) 
#define		CONST_langId_NewZealand									0x1409			//  English (New Zealand) 
#define		CONST_langId_Ireland									0x1809			//	English (Ireland) 
#define		CONST_langId_SouthAfrica								0x1c09			//  English (South Africa) 
#define		CONST_langId_Jamaica									0x2009			//  English (Jamaica) 
#define		CONST_langId_Caribbean									0x2409			//	English (Caribbean) 
#define		CONST_langId_Belize										0x2809			//  English (Belize) 
#define		CONST_langId_Trinidad									0x2c09			//  English (Trinidad) 

#define		CONST_langId_Japanese									0x0411			//	Japanese 
#define		CONST_langId_Korean										0x0412			//  Korean 
#define		CONST_langId_KoreanJohab								0x0812			//  Korean (Johab) 


/////////////////
//  qnmPcComm.h
#ifndef  __QNMPCCOMM_H__		//  {
//  #define		MACRO_qyPcCommHead			unsigned  int  uiType;  unsigned  int  uiSize;  unsigned  char  ucFlg;  char  reserved[7];	int  iPlatformId;  unsigned  int  uiLangId;  char  winDir[255  +  1];		
#define		MACRO_qyPcCommHead			unsigned  int  uiType;  unsigned  int  uiSize;  unsigned  char  ucFlg;  char  reserved[7];	int  iPlatformId;  unsigned  int  uiLangId;  char  winDir[255  +  1];  unsigned  int  cnt;		//  2005/08/31

#if 0
#define		CONST_pcCommType_null									0
#define		CONST_pcCommType_adapter								1
#define		CONST_pcCommType_proxy									2
#define		CONST_pcCommType_computer								3
#define		CONST_pcCommType_cleanNetworkProp						4		//  2006/05/07, ÓÃÀ´ÔÚÒÔÉÏÉõÖÁ¸ü¶àµÄÍøÂçÊôÐÔÉÏ´«ºó·¢±êÖ¾Î»ÒÔÇåÀíÏàÓ¦µÄÊôÐÔ
//
#define		CONST_pcCommType_process								11
#define		CONST_pcCommType_eventLog								12		//  2005/08/31
#define		CONST_pcCommType_usrInfo								13		//  2005/09/04
#define		CONST_pcCommType_tcpTable								14		//  2005/09/17
#define		CONST_pcCommType_udpTable								15		//  2005/09/17
#define		CONST_pcCommType_printers								16		//  2005/09/18
#define		CONST_pcCommType_processRule							17		//  2005/10/10
#define		CONST_pcCommType_processModule							18		//  2006/04/14
#define		CONST_pcCommType_windowsUpdatePolicy					19		//  2006/05/21
#define		CONST_pcCommType_registryVal							20		//  2006/07/16, Ö¸×¢²á±í»òÎÄ¼þµÈÌØÕ÷ÐÅÏ¢
#define		CONST_pcCommType_netFlow								21		//  2006/09/10
#define		CONST_pcCommType_netShare								22		//  2007/02/14
//
//
#define		CONST_pcCommType_switchRule								1000	//  2006/07/16, ½«ÕâÐ©²ÎÊý¶¼Í³Ò»ÆðÀ´
#define		CONST_pcCommType_switchPortRule							1001	//  2006/07/16, ½«ÕâÐ©²ÎÊý¶¼Í³Ò»ÆðÀ´
//
#define		CONST_pcCommType_pcFileMonRules							2		//  2006/07/16, ÀúÊ·ÒÅÁôÎÊÌâ£¬´Ë¶¨Òå²»ÄÜ¸Ä
#define		CONST_pcCommType_registryRule							2000	//  2006/07/16, Ö¸×¢²á±í»òÎÄ¼þµÈ¹æÔòÐÅÏ¢
#define		CONST_pcCommType_registryRuleStatus						2001	//  2006/08/02, ×¢²á±í¹æÔòµÄ×´Ì¬ÐÅÏ¢			
#define		CONST_pcCommType_queryCfgs								2002	//  2006/08/06, È¡ÅäÖÃµÄÇëÇóÐÅÏ¢
#define		CONST_pcCommType_pcProcessKnowledge						2003	//  2006/08/12, ½ø³ÌÖªÊ¶
#define		CONST_pcCommType_pcRegistryKnowledge					2004	//  2006/08/12, ×¢²á±íÖªÊ¶

//  misÏµÍ³µÄ²ÎÊýÔÚÏÂÃæ¶¨Òå£¬2007/05/07
#define		CONST_imCommType_base									3000
#define		CONST_imCommType_max									(  CONST_imCommType_base  +  1999  )	//  Ã¿¸ö·þÎñÁô¸ö2000¸ö½á¹¹µÄÀàÐÍ

#endif



#endif   //  }




/////////////////
//  qnmCommProc_mis.h

#ifndef	 __QNMCOMMPROC_MIS_H__		//  2009/01/01,  {
//  qnmPcComm.h
//  #define		CONST_imCommType_base								3000

#if 0
//  
#define		CONST_imCommType_htmlContent							(  CONST_imCommType_base  +  1  )		//  2007/05/07
#define		CONST_imCommType_simpleResp								(  CONST_imCommType_base  +  2  )		//  2007/05/07
//  #define		CONST_imCommType_streamContent							(  CONST_imCommType_base  +  3  )		//  2007/08/01
#define		CONST_imCommType_msgRoute								(  CONST_imCommType_base  +  4  )		//  2007/11/29
#define		CONST_imCommType_dataContent							(  CONST_imCommType_base  +  5  )		//  2008/01/26 
#define		CONST_imCommType_lStream								(  CONST_imCommType_base  +  6  )		//  2008/04/01 


//  #define		CONST_imCommType_intervalParams						(  CONST_imCommType_base  +  110  )		//  
#define		CONST_imCommType_getCfgsReq								(  CONST_imCommType_base  +  110  )		//  2011/01/30


//
#define		COSNT_imCommType_qisCaReq								(  CONST_imCommType_base  +  120  )


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
#define		CONST_imCommType_transferFileReq						(  CONST_imCommType_base  +  250  )		//  2007/06/23£¬´«ËÍÎÄ¼þÐÅÏ¢£¬ÈçÎÄ¼þÃû£¬ÎÄ¼þ´óÐ¡
#define		CONST_imCommType_transferFileReplyReq					(  CONST_imCommType_base  +  251  )
#define		CONST_imCommType_transferFileDataReq					(  CONST_imCommType_base  +  252  )		//  2007/06/23, ´«ËÍÎÄ¼þÊý¾Ý
#define		CONST_imCommType_transferFileDataResp					(  CONST_imCommType_base  +  253  )		//  2007/06/23, ´«ËÍÎÄ¼þÊý¾Ý
#define		CONST_imCommType_transferFileEndReq						(  CONST_imCommType_base  +  254  )		//  2007/06/23, ´«ËÍÎÄ¼þÊý¾Ý½áÊøÇëÇó, 
#define		CONST_imCommType_transferFileEndResp					(  CONST_imCommType_base  +  255  )		//  2007/06/23, ´«ËÍÎÄ¼þÊý¾Ý½áÊøÏìÓ¦ 
//  #define		CONST_imCommType_transferFileProcReq				(  CONST_imCommType_base  +  256  )		//  2007/06/23, ´«ËÍÎÄ¼þµÄ´¦Àí£¬Í¨³£ÊÇÎªÁË´«Ò»¸öusOp
//  #define		CONST_imCommType_transferFileProcResp				(  CONST_imCommType_base  +  257  )		//  2007/06/23, ´«ËÍÎÄ¼þµÄ´¦Àí£¬Í¨³£ÊÇÎªÁË´«Ò»¸öusOp
#define		CONST_imCommType_taskProcReq							(  CONST_imCommType_base  +  256  )		//  2008/05/29
#define		CONST_imCommType_taskProcResp							(  CONST_imCommType_base  +  257  )		//  2008/05/29

//
#define		CONST_imCommType_rtcCallReq								(  CONST_imCommType_base  +  260  )		//  2007/10/07, rtcÈÎÎñÇëÇó

//  
#define		CONST_imCommType_transferAvInfo							(  CONST_imCommType_base  +  265  )		//  2008/03/15, ´«ËÍÊÓÆµÐÅÏ¢£¬ÈçÑ¹Ëõ±àÂë£¬ÊÇ·ñÏìÓ¦
#define		CONST_imCommType_transferAvReplyInfo					(  CONST_imCommType_base  +  266  )		//  2008/03/16, ´«ËÍÊÓÆµµÄ´¦Àí£®
#define		CONST_imCommType_transferVideoData						(  CONST_imCommType_base  +  267  )		//  2008/03/15, ´«ËÍÊÓÆµÊý¾Ý
#define		CONST_imCommType_transferVideoDataResp					(  CONST_imCommType_base  +  268  )		//  2008/03/15, ´«ËÍÊÓÆµÊý¾ÝµÄÏìÓ¦
//
#define		CONST_imCommType_transferAudioData						(  CONST_imCommType_base  +  271  )		//  2008/04/16, ´«µÝÒôÆµÊý¾Ý
#define		CONST_imCommType_transferAudioDataResp					(  CONST_imCommType_base  +  272  )		//  2008/04/21, ´«µÝÒôÆµÊý¾ÝµÄÏìÓ¦

#define		CONST_imCommType_remoteAssistReq						(  CONST_imCommType_base  +  280  )		//  2008/11/15, ´«µÝÔ¶³Ì²Ù×÷Ö¸Áî

//
#define		CONST_imCommType_taskInteractionReq						(  CONST_imCommType_base  +  290  )		//  2009/02/23

//
#define		CONST_imCommType_transferGpsInfo						(  CONST_imCommType_base  +  300  )		//  2012/04/19
#define		CONST_imCommType_transferGpsReplyInfo					(  CONST_imCommType_base  +  301  )		//  2012/04/19
#define		CONST_imCommType_transferGpsData						(  CONST_imCommType_base  +  302  )		//  2012/04/20
#define		CONST_imCommType_transferGpsDataResp					(  CONST_imCommType_base  +  303  )		//  2012/04/20

//  2012/08/05
#define		CONST_imCommType_ptzControlReq							(  CONST_imCommType_base  +  310  )
#define		CONST_imCommType_ptzControlCmd							(  CONST_imCommType_base  +  311  )

//
#define		CONST_imCommType_newImGrp								(  CONST_imCommType_base  +  350  )		//  2007/08/23
#define		CONST_imCommType_refreshImGrp							(  CONST_imCommType_base  +  351  )		//  2007/08/23

//  
#define		CONST_imCommType_retrieveWebContactListReq				(  CONST_imCommType_base  +  400  )		//  2007/11/25£¬²éÑ¯ÍøÕ¾ÁªÏµÈËµÄÇëÇó
#define		CONST_imCommType_retrieveWebContactListResp				(  CONST_imCommType_base  +  401  )		//  2007/11/25£¬²éÑ¯ÍøÕ¾ÁªÏµÈËµÄÏìÓ¦
//
#define		CONST_imCommType_refreshWebContactsInfo					(  CONST_imCommType_base  +  402  )		//  2007/12/22
#define		CONST_imCommType_ipKnowledge							(  CONST_imCommType_base  +  403  )		//  2007/12/23, ipµÄÖªÊ¶¿â.
//

//  
#define		CONST_imCommType_retrieveCustomerServiceObjListReq		(  CONST_imCommType_base  +  406  )		//  2011/04/04
#define		CONST_imCommType_queryCustomerServiceOfficerReq			(  CONST_imCommType_base  +  407  )		//  2011/04/04

//
#define		CONST_imCommType_queryPeerStatus						(  CONST_imCommType_base  +  420  )		//  2014/07/11


//  gsm
#define		CONST_imCommType_smPkt									(  CONST_imCommType_base  +  500  )		//  2008/01/05
#define		CONST_imCommType_phoneGuest								(  CONST_imCommType_base  +  501  )		//  2008/01/20
#define		CONST_imCommType_vDevComs								(  CONST_imCommType_base  +  502  )		//  2008/01/24, 3502, Ìá½»COM×´Ì¬
#define		CONST_imCommType_retrieveSmPolicy						(  CONST_imCommType_base  +  503  )		//  2008/01/24, 3503, »ñÈ¡SM²ßÂÔ¡£Ö÷ÒªÊÇsmContacts
#define		CONST_imCommType_retrievePhoneMsgrs						(  CONST_imCommType_base  +  504  )		//  2008/01/24, 3504, »ñÈ¡ÊÖ»úmessengerÁÐ±í
#define		CONST_imCommType_retrieveToPaths						(  CONST_imCommType_base  +  505  )		//  2008/01/24, 3505, »ñÈ¡·¢ËÍÍ¨µÀÁÐ±í
//
#define		CONST_imCommType_refreshDynBmps							(  CONST_imCommType_base  +  506  )		//  2009/08/24
#define		CONST_imCommType_retrieveDynBmps						(  CONST_imCommType_base  +  507  )		//  2009/09/04
#define		CONST_imCommType_refreshImObjRules						(  CONST_imCommType_base  +  508  )		//  2010/08/14
#define		CONST_imCommType_verifyViewDynBmp						(  CONST_imCommType_base  +  509  )		//  2011/10/31
//
#define		CONST_imCommType_vDevData								(  CONST_imCommType_base  +  510  )		//  2008/01/24, 3503, 
//
#define		CONST_imCommType_procOfflineRes							(  CONST_imCommType_base  +  511  )		//  2015/08/01



//  
#define		CONST_imCommType_getDaemonStatusReq						(  CONST_imCommType_base  +  550  )		//  2011/01/08
#define		CONST_imCommType_testSpeedReq							(  CONST_imCommType_base  +  551  )		//  2016/12/28



//  
#define		CONST_imCommType_max									(  CONST_imCommType_base  +  1999  )	//  2000
//
///////////////////

#endif



#endif   //  }



// qwmNetworkStatusCommProc.h
#ifndef		__QWMNETWORKSTATUSCOMMPROC_H__    //  2009/01/01,  {
	#define		CONST_pcNetworkPropType_null				CONST_pcCommType_null
	#define		CONST_pcNetworkPropType_adapter				CONST_pcCommType_adapter	//  1
	#define		CONST_pcNetworkPropType_proxy				CONST_pcCommType_proxy		//  2
	#define		CONST_pcNetworkPropType_computer			CONST_pcCommType_computer	//  3
#endif  //  }


//qnmsCommProc.h
//  ×¢£º2006/07/16£¬½«ÉÏÃæµÄ¶¨ÒåÖØÐÂ¸ÄÎªÒÔÏÂµÄ¶¨Òå£¬´Ó¶ø½«ÕâÐ©²ÎÊýÍ³Ò»ÆðÀ´
//
#define		CONST_ruleType_switch									CONST_pcCommType_switchRule
#define		CONST_ruleType_switchPort								CONST_pcCommType_switchPortRule


 //qySnmpCommProc.h
#ifndef  __QYSNMPCOMMPROC_H__		//  {// 2008/12/27, 
		 #define		CONST_snmpTrue												1
		 #define		CONST_snmpFalse												2
#endif  //  }



#ifndef  __QNMCOMMPROC_MIS_H__		//  {

//
#define		CONST_usRunningStatus_null								0
#define		CONST_usRunningStatus_online							1
#define		CONST_usRunningStatus_offline							2
#define		CONST_usRunningStatus_away								3
#define		CONST_usRunningStatus_hide								4								//  2007/06/07, ÔÚÏß£¬ÀëÏß£¬Àë¿ª£¬ÒþÉíµÈ
#define		CONST_usRunningStatus_neverLogon						5								//  Î´ÉÏÏß¡£Ö¸´Ó·þÎñÆ÷¿ª»úºóÃ»ÓÐÉÏ¹ýÏß

//  
#define		CONST_imTaskType_null									0
//
#define		CONST_imTaskType_sendFile								11
#define		CONST_imTaskType_recvFile								12
//
#define		CONST_imTaskType_avSetup								15
//  #define		CONST_imTaskType_listening							16
//  #define		CONST_imTaskType_avCall								17			//  ºóÃæÓ¦¸Ã¸úÒ»¸öÄ¿µÄIP
//  #define		CONST_imTaskType_whiteboard							18			//  
//  #define		CONST_imTaskType_appCall							19			//  
//
#define		CONST_imTaskType_transferAvInfo							25			//  
#define		CONST_imTaskType_shareScreen							26			//  2008/10/06
#define		CONST_imTaskType_remoteAssist							27			//  2008/11/10
#define		CONST_imTaskType_shareMediaFile							28			//  2009/04/23
#define		CONST_imTaskType_shareDynBmp							29			//  2009/08/21
#define		CONST_imTaskType_viewDynBmp								30			//  2009/09/07
#define		CONST_imTaskType_queryCustomerServiceOfficer			31			//  2011/04/06

//  2012/04/19
#define		CONST_imTaskType_shareGps								40			//  2012/04/19
#define		CONST_imTaskType_viewGps								41			//  2012/04/19


//
//
//  2011/08/06

	//
	#define		CONST_policyAvLevel_240p							10			//  2014/04/23
	//
	#define		CONST_policyAvLevel_480p							21
	#define		CONST_policyAvLevel_848x480							22
	#define		CONST_policyAvLevel_576p							23

	//
	#define		CONST_policyAvLevel_720p							32			//  2014/04/23
	//
	#define		CONST_policyAvLevel_1080p							42			//  2014/04/23

	//  2012/02/14
	#define		CONST_policyAvLevel_dev_2fps						110			//  2fps, dmo.		screen
	#define		CONST_policyAvLevel_dev_5fps						112			//  5fps-300k, ipp. screen
	//  2012/10/29
	#define		CONST_policyAvLevel_dev_5fps1						113			//  5fps-450k, ipp. screen
	//  2015/11/06
	#define		CONST_policyAvLevel_dev_5fps2						114			//  5fps-700k, screen
	//  2012/11/3



//
#define		CONST_iTargetUsage_null									0
#define		CONST_iTargetUsage_bestQuality							10									
#define		CONST_iTargetUsage_balanced								20
#define		CONST_iTargetUsage_bestSpeed							30


#define		CONST_iAvgBitrate_null									0
#define		CONST_iAvgBitrate_1_5m									1500000
#define		CONST_iAvgBitrate_2m									2000000
#define		CONST_iAvgBitrate_2_5m									2500000
//#define		CONST_iAvgBitrate_3m									3000000
//
#define		CONST_iAvgBitrate_3_5m									3500000
#define		CONST_iAvgBitrate_4m									4000000
#define		CONST_iAvgBitrate_4_5m									4500000
#define		CONST_iAvgBitrate_5m									5000000



#define		DEFAULT_iAvgBitrate_1080p								CONST_iAvgBitrate_4m
#define		DEFAULT_iAvgBitrate_720p								CONST_iAvgBitrate_2m


#endif		//  }




/////////////////


#ifndef  __QYCUSTOM_H__
#define  __OTHER__									//  Õã½­Ê¡ÆäËû¹«°²
#endif


















#include	"qnmResDefs.h"






#endif  //  }



