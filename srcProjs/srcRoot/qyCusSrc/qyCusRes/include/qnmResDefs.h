
#ifndef  __QNMRESDEFS_H__
#define	 __QNMRESDEFS_H__	//  {

//  ×¢Òâ£º´ËÎÄ¼þÔ­ÔòÉÏ²»ÒªÐÞ¸Ä

 enum  enumResTypes  
{
	CONST_resType_null,
	CONST_resType_str,
	CONST_resType_table,						//  
	CONST_resType_menu,							//  reserved
	CONST_resType_dlg,							//  ¶Ô»°¿ò
	CONST_resType_query,
	CONST_resType_search,
	CONST_resType_columnInfo,

	//
	//  ÉÏÃæµÄÖµ×îºÃ²»¸Ä
	CONST_resType_total,	//  Õâ¸öÓ¦¸ÃÊÇ×ÜÊý
};


 enum	enumResIds_internel							//  2005/1106
{
	CONST_resId_null_internel  =  70000,
	//
	CONST_resId_sys_bha,
	CONST_resId_sys_bhb_intraMon,
	CONST_resId_sys_bhb_interMon,
	CONST_resId_sys_netMc2,
	CONST_resId_sys_nms,
	CONST_resId_sys_secChk,
	CONST_resId_sys_assetMgr,
	CONST_resId_sys_isMgr,							//  2007/03/07
	CONST_resId_sys_isCli_default,					//  2007/03/07
	CONST_resId_sys_isCli_noMfc,					//  2013/07/30
	CONST_resId_sys_isCli_ts,						//  2011/03/20
	CONST_resId_sys_isCliHelp,						//  2013/06/15
	CONST_resId_sys_qyMessengerHelp,				//  2013/07/26
	CONST_resId_sys_qisGuiPublic,					//  2015/07/02
	CONST_resId_sys_qmdCliHelp,						//  2015/07/17
	//
	CONST_resId_app_daemon	=  71000,
	CONST_resId_app_resp,
	CONST_resId_app_statusTool,
	CONST_resId_app_warningTool,
	CONST_resId_app_rtcTool,						//  2007/10/07
	CONST_resId_app_vDevComs,						//  2008/01/01
	//
	CONST_resId_mainMenu	=	72000,				//  2007/10/07
	xxx_invalid_CONST_resId_mainMenu_mini,			//  2014/07/27
	CONST_resId_childFrmMenu,
	CONST_resId_popupMenu,
	CONST_resId_winceMenu,							//  2010/04/13
	//
	CONST_resId_qnmEventTypeTable0,
	CONST_resId_qnmEventTypeTable_pc,
	CONST_resId_qnmEventTypeTable_op,
	CONST_resId_qnmEventTypeTable_netDev,
	CONST_resId_qnmEventTypeTable_secChk,
	//
	CONST_resId_ipScanOfficeLevelTable,
	CONST_resId_zjgaYhlxTable,
	CONST_resId_gYhGrpTable,
	CONST_resId_gEventYhGrpTable,
	CONST_resId_secChkEventTypeTable,
	CONST_resId_qyNullTable,
	CONST_resId_jqlxTable,	
	CONST_resId_qnmStopMonTable,						//  2008/12/15
	CONST_resId_qnmCfgRasCmdTable,
	CONST_resId_qnmRasCmdTable,
	CONST_resId_ucWLanAdapterCmdTable,					//  2010/05/20
	CONST_resId_ucBlueToothCmdTable,					//  2010/08/18
	CONST_resId_ucInfraredCmdTable,						//  2010/08/18
	CONST_resId_uc1394CmdTable,							//  2010/08/18
	CONST_resId_ucWpdCmdTable,							//  2011/08/26
	CONST_resId_ucSdHostAdapterCmdTable,				//  2011/08/28
	CONST_resId_ucMobileDeviceCmdTable,					//  2011/08/28
	CONST_resId_ucUsbNetworkCardCmdTable,				//  2011/09/18
	//
	CONST_resId_qySystemIdTable,
	CONST_resId_ucbDsnlessTable,
	CONST_resId_myCONST_yhGrpTable_netMc,
	CONST_resId_myCONST_eventYhGrpTable_netMc,
	CONST_resId_myCONST_yhGrpTable_is,
	CONST_resId_myCONST_eventYhGrpTable_is,
	CONST_resId_imTaskTypeTable,						//  2008/12/30
	CONST_resId_qyStatusTable,							//	2009/01/01
	CONST_resId_imTaskStatusTable,						//  2009/01/01
	//
	CONST_resId_qyLangTable,							//  2008/12/20
	//
	CONST_resId_objTypeTable,							//  2008/12/16
	//
	CONST_resId_imGrpSubtypeTable,						//  2014/01/31
	CONST_resId_imGrpMemRoleTable,						//  2015/07/28
	CONST_resId_imObjRoleTable,							//  2017/08/14
	//
	CONST_resId_queryTypeTable,							//  2006/05/05
	//
	CONST_resId_fieldIdTable,							//  2008/12/28
	CONST_resId_qyCommTypeTable,						//  2009/01/01
	CONST_resId_pcCommTypeTable,						//  2009/01/01
	//  CONST_resId_pcProcessRuleTypeTable,
	CONST_resId_grpNameTable,							//  2009/01/02
	CONST_resId_usRunningStatusTable,					//  2009/01/08
	CONST_resId_AUOptionsTable,							//  2009/04/11
	CONST_resId_NoAutoUpdateTable,						//  2009/04/11
	CONST_resId_RescheduleWaitTimeEnabledTable,			//  2009/04/11
	CONST_resId_DetectionFrequencyEnabledTable,			//  2009/04/11
	CONST_resId_NoAutoRebootWithLoggedOnUsersTable,		//  2009/04/11	
	CONST_resId_ElevateNonAdminsTable,					//  2009/04/11
	CONST_resId_TargetGroupEnabledTable,				//  2009/04/11
	CONST_resId_qnmDevCmdTable,							//  2009/04/11	
	CONST_resId_qnmDevCmdTable0,						//  2009/04/11	
	CONST_resId_qnmUsbCmdTable,
	CONST_resId_qnmAutorunCmdTable,
	CONST_resId_pcAdapterStatusTable,					//  2009/04/19
	//  nms¶ÀÓÐµÄ×ÊÔ´
	CONST_resId_ruleCmdTable,
	CONST_resId_ruleCmdTable_autoAnswer,				//  2010/09/08
	CONST_resId_ruleCmdTable_autoAnswer_av,				//  2016/02/15
	//
	CONST_resId_dynBmpTypeTable,						//  2013/02/13
#if  0
	CONST_resId_selectScreen,
	CONST_resId_selectWebcam0,
	CONST_resId_selectWebcam1,
	CONST_resId_selectWebcam2,
#endif
	//
	CONST_resId_snmpBoolTable,							//  2008/12/27
	//
	CONST_resId_ruleTypeTable,							//  2010/08/16
	CONST_resId_usLayoutTypeTable,						//  2010/12/21
	CONST_resId_usLayoutTypeTable_resource,				//  2010/12/25
	//
	CONST_resId_gpPcListSearchTable0,					//  ²éÑ¯PCÁÐ±íµÄÌõ¼þÉèÖÃ		
	CONST_resId_gpPcListSearchCb0Tables,
	CONST_resId_gpPcListSearchCb1Tables,
	//
	CONST_resId_gpEventListSearchTable0,				//	²éÑ¯¼ÆËã»úÊÂ¼þÁÐ±íµÄÌõ¼þÉèÖÃ
	CONST_resId_gpEventListSearchCb0Tables,
	CONST_resId_gpEventListSearchCb1Tables,
	//
	CONST_resId_gpNetDevEventListSearchTable0,			//	²éÑ¯ÍøÂçÊÂ¼þÁÐ±íµÄÌõ¼þÉèÖÃ
	CONST_resId_gpNetDevEventListSearchCb0Tables,
	CONST_resId_gpNetDevEventListSearchCb1Tables,
	//
	CONST_resId_gpOpEventListSearchTable0,				//	²éÑ¯ÏµÍ³ÊÂ¼þÁÐ±íµÄÌõ¼þÉèÖÃ£¬2006/02/25
	CONST_resId_gpOpEventListSearchCb0Tables,
	CONST_resId_gpOpEventListSearchCb1Tables,
	//
	CONST_resId_gpSecChkEventListSearchTable0_netMc2,	//	²éÑ¯°²¼ìÊÂ¼þÁÐ±íµÄÌõ¼þÉèÖÃ£¬2006/05/05
	CONST_resId_gpSecChkEventListSearchTable0_secChk,	//	²éÑ¯°²¼ìÊÂ¼þÁÐ±íµÄÌõ¼þÉèÖÃ£¬2006/05/05
	CONST_resId_gpSecChkEventListSearchCb0Tables,
	CONST_resId_gpSecChkEventListSearchCb1Tables,
	//  2008/12/20,Í³¼Æ
	CONST_resId_gpStatIpScanTable0,
	CONST_resId_gpStatPcInfoTable0,
	CONST_resId_gpStatPcInfoCb0Tables,
	CONST_resId_gpStatUsrInfoTable0,
	CONST_resId_gpStatUsrInfoCb0Tables,
	CONST_resId_gpStatGeneralTable0,
	CONST_resId_gpStatGeneralCb0Tables,
	CONST_resId_gpStatOthersTable0,


	CONST_resId_gpStatMessengerInfoTable0,
	CONST_resId_gpStatMessengerInfoCb0Tables,
#if  0
	CONST_resId_menu_shareFullScreen,					//  2012/11/03
	CONST_resId_menu_startShareMediaFile,				//  2012/11/03
	CONST_resId_menu_startShareMediaDevice,				//  2012/11/03
#endif
	//  2009/01/01
	CONST_resId_pcPropertiesTable0,
	CONST_resId_policyAvLevelTable_basic,				//  2011/08/08
	CONST_resId_policyAvLevelTable_standard,			//  2011/08/08
	CONST_resId_policyAvLevelTable_high,				//  2011/08/08
	CONST_resId_policyAvLevelTable_mosaic_video,		//  2014/11/15
	CONST_resId_policyAvLevelTable_mosaic_resource,		//  2014/12/01
	//
	CONST_resId_policyAvLevelTable_slave_video,			//  2016/04/06
	//  2012/02/16
	CONST_resId_policyAvLevelTable_screen_basic,
	CONST_resId_policyAvLevelTable_screen_standard,
	CONST_resId_policyAvLevelTable_screen_high,
	//
	CONST_resId_iTargetUsageTable,								//  2012/02/08
	CONST_resId_iAvgBitrateTable_h264_720p,						//  2012/06/27
	CONST_resId_iAvgBitrateTable_h264_1080p,					//  2012/06/27
	CONST_resId_iAvgBitrateTable_h265_720p,						//  2017/10/10
	CONST_resId_iAvgBitrateTable_h265_1080p,					//  2017/10/10

 


};


 enum  enumResIds               // Declare enum type Days
{
	CONST_resId_null	=	80000,	//  ÕâÀïÈ¡ÖµÊÇÎªÁË±ÜÃâ·ÖÅäÖµµ½Î¢ÈíµÄSTUDIO²úÉúµÄIDÖµÓòÀï
	//
	CONST_resId_seqNo,				//  ÐòºÅ
	//
	CONST_resId_logon_wndTitle,
	CONST_resId_logon_staticUsrName,
	CONST_resId_logon_staticPasswd,

	//
	CONST_resId_gpBhbLogQueryStruct,	
	CONST_resId_gpBhbOfflineLogQueryStruct,	
	CONST_resId_gpScannedIpListQueryStruct,	
	//
	CONST_resId_gpSimpleUsrQueryStruct,
	CONST_resId_gpPcListQueryStruct,	
	CONST_resId_gpPcListQueryStruct_netMc2,	
	CONST_resId_gpPcAssetListQueryStruct,				
	CONST_resId_gpPcAssetReportListQueryStruct,			
	CONST_resId_gpPcAssetReportListQueryStruct_en,		
	CONST_resId_gpPcSpListQueryStruct,					
	CONST_resId_gpPcSpSpecialListQueryStruct,			
	//  CONST_resId_gpUnchkedPcListQueryStruct,			
	//  CONST_resId_gpWillAttackPcListQueryStruct,		
	//
	CONST_resId_gpPcUsrListQueryStruct,				
	CONST_resId_gpPcUsrInTab1ListQueryStruct,		
	CONST_resId_gpClientListQueryStruct_netMc,			
	//
	CONST_resId_gpPcSecChkEventAllQueryStruct,
	//
	CONST_resId_gpPcRuleListQueryStruct0,			
	CONST_resId_gpPcRuleListQueryStruct1,			
	CONST_resId_gpPcAdapterListQueryStruct,			
	CONST_resId_gpPcProxyCfgListQueryStruct,		
	//  CONST_resId_gpPcComputerPropListQueryStruct,	
	//  CONST_resId_gpPcComputerRuleListQueryStruct,	
	CONST_resId_gpPcWindowsUpdatePolicyListQueryStruct,
	CONST_resId_gpPcPrinterPropListQueryStruct,		
	//
	CONST_resId_gpPcRegistryListQueryStruct,
	CONST_resId_gpPcRegistryRuleStatusListQueryStruct,
	CONST_resId_gpPcEventLogListQueryStruct,		
	CONST_resId_gpPcOsUsrListQueryStruct,			
	CONST_resId_gpPcNetStatListQueryStruct,			
	CONST_resId_gpPcProcessPropListQueryStruct,		
	CONST_resId_gpPcProcessModulePropListQueryStruct,		
	CONST_resId_gpPcProcessRuleListQueryStruct,		
	CONST_resId_gpPcProcessKnowledgeListQueryStruct,	
	CONST_resId_gpPcRegistryKnowledgeListQueryStruct,
	CONST_resId_gpPcNetFlowListQueryStruct,		
	CONST_resId_gpPcNetShareListQueryStruct,
	//  CONST_resId_gpPcAutoLogonListQueryStruct,
	//
	CONST_resId_gpSnmpObjRuleListQueryStruct,		
	CONST_resId_gpConflictConnListQueryStruct,		
	CONST_resId_gpDirectConnListQueryStruct,		
	CONST_resId_gpNetDevConnListQueryStruct,		
	CONST_resId_gpSearchListQueryStruct,			
	CONST_resId_gpOpEventListQueryStruct_netMc,			
	CONST_resId_gpPcEventAllQueryStruct,			
	CONST_resId_gpNetDevEventAllQueryStruct,		
	CONST_resId_gpPcRasEventQueryStruct,			
	//	CONST_resId_gpSecChkEventAllQueryStruct,		
	
	CONST_resId_mis_base	=	90000,						//  2007/04/07
	
	//
	CONST_resId_is_qmStr_start	=	91000,				//  2011/08/14. //  这个区间专门定义一些daemon和gui共用的resId. 定义和qmStr.h要保持一致
	CONST_resId_is_qmStr_end  =  95000,

	//
	CONST_resId_servName,									//  2007/08/28
	CONST_resId_idStr,										//  2007/08/10
	CONST_resId_idStr_grp,
	//
	CONST_resId_gpSimpleUsrQueryStruct_is,					//  2007/09/15
	CONST_resId_gpMessengerAuthListQueryStruct,
	CONST_resId_gpMessengerAuthNeedAuditedListQueryStruct,	//  2007/09/12
	CONST_resId_gpImAmListQueryStruct,						//  2010/01/05
	CONST_resId_gpPhoneMessengerListQueryStruct,			//  2007/09/12
	CONST_resId_gpImGrpAuthListQueryStruct_isMgr,
	CONST_resId_gpImGrpAuthListQueryStruct_isClient,
	CONST_resId_gpImGrpListQueryStruct_isMgr,
	CONST_resId_gpImGrpListQueryStruct_isClient,
	CONST_resId_gpImGrpAuthMemListQueryStruct_isMgr,	
	CONST_resId_gpImGrpMemListQueryStruct_isMgr,
	CONST_resId_gpImGrpMemListQueryStruct_isClient,
	CONST_resId_gpImObjListQueryStruct_isMgr,				//  2007/07/29
	CONST_resId_gpImObjListQueryStruct_isClient,			//  2007/07/29
	CONST_resId_gpImObjUsrListQueryStruct_isMgr,			//  2007/07/30
	CONST_resId_gpImObjUsrInTab1ListQueryStruct_isMgr,	
	CONST_resId_gpImObjUsrListQueryStruct_isClient,			//  2007/07/30
	CONST_resId_gpImObjUsrInTab1ListQueryStruct_isClient,	
	CONST_resId_gpClientListQueryStruct_is,					//  2007/09/16	
	CONST_resId_gpCustomerServiceListQueryStruct_is,		//  2011/04/03
	CONST_resId_gpWebContactListQueryStruct_is,				//  2007/11/20
	CONST_resId_gpIpKnowledgeListQueryStruct_is,			//  2007/12/23
	CONST_resId_gpPhoneGuestListQueryStruct_is,				//  2007/12/23
	CONST_resId_gpGsmModemListQueryStruct_isMgr,			//  2008/01/27
	CONST_resId_gpSmContactListQueryStruct_isMgr,			//  2008/01/27
	CONST_resId_gpSharedDynBmpListQueryStruct_isMgr,		//  2009/08/31
	CONST_resId_gpSharedDynBmpRuleListQueryStruct_isMgr,	//  2009/09/17
	CONST_resId_gpImObjRuleListQueryStruct_isMgr,			//  2010/08/16
	CONST_resId_gpImObjRuleListQueryStruct_isClient,		//  2010/09/06


	//
	CONST_resId_gpImTaskListQueryStruct,
	CONST_resId_gpImMsgListQueryStruct_isMgr,
	CONST_resId_gpImMsgListQueryStruct_isClient,


	//
	CONST_resId_gpEventListQueryStruct_is,			
	CONST_resId_gpOpEventListQueryStruct_is,			


	//  ´°¿ÚÏÔÊ¾µÄÒ»Ð©¶ÔÏó  
	//
	CONST_resId_status,					//  ×´Ì¬£¬2008/01/23
	CONST_resId_ipAddr,						//  2016/07/30
	CONST_resId_deviceAddr,
	CONST_resId_ptzAddr,
	CONST_resId_rtspAddr,
	//
	CONST_resId_pcMgrClass,
	CONST_resId_pcUsrInfo,
	CONST_resId_pcOpNode,
	CONST_resId_pcOsClass,
	//
	CONST_resId_pcOpNode_desc,

	//  2008/12/14
	CONST_resId_objIdStr_unRegGrp,		//			_T(  "(Î´×¢²áÓÃ»§)"  )
	CONST_resId_objIdStr_othersGrp,		//			_T(  "(ÆäËûÓÃ»§)"  )
	CONST_resId_objIdStr_me,			//			_T(  "ÎÒ"  )
	CONST_resId_objIdStr_imGrps,		//			_T(  "×é¼¯ºÏ"  )
	CONST_resId_objIdStr_imGrps_av,		//			2014/01/31
	CONST_resId_objIdStr_imGrps_msg,	//			2014/01/31
	CONST_resId_objIdStr_imGrps_tmp,	//			2017/07/28




	//  Í³¼Æ
	CONST_resId_statIpScan,
	CONST_resId_statPcInfo,
	CONST_resId_statUsrInfo,
	CONST_resId_statGeneral,
	CONST_resId_statOthers,
	//
	CONST_resId_statMessengerInfo,	//  2007/09/22

	//  
	CONST_resId_COLUMNINFO_sQyMcRootListColumns,
	CONST_resId_COLUMNINFO_networkViewTable,
	CONST_resId_COLUMNINFO_switchViewTable,
	CONST_resId_COLUMNINFO_switchPortViewTable,					
	CONST_resId_COLUMNINFO_switchUsrConnectionViewTable,		
	CONST_resId_COLUMNINFO_switchPortUsrConnectionViewTable,	
	CONST_resId_COLUMNINFO_switchNetworkSpeedViewTable,			
	CONST_resId_COLUMNINFO_switchPortNetworkSpeedViewTable,	
	//
	CONST_resId_COLUMNINFO_col4ListColumns_netMc,			
	CONST_resId_COLUMNINFO_col4ListColumns_is,		
	//
	CONST_resId_COLUMNINFO_unRegGrpMemListColumns_netMc,		
	CONST_resId_COLUMNINFO_unRegGrpMemListColumns_is,		
	CONST_resId_COLUMNINFO_othersGrpMemListColumns,	
	CONST_resId_COLUMNINFO_pcMgrClassListColumns,
	CONST_resId_COLUMNINFO_pcOpNodeMemListColumns_netMc,
	CONST_resId_COLUMNINFO_pcOpNodeMemListColumns_is,
	CONST_resId_COLUMNINFO_pcEnvListColumns,		
	CONST_resId_COLUMNINFO_pcOsListColumns,		
	CONST_resId_COLUMNINFO_pcAssetListColumns,
	//
	CONST_resId_COLUMNINFO_qnmCfgIpScanColumns,
	CONST_resId_COLUMNINFO_qnmCfgPcGrpsColumns,
	CONST_resId_COLUMNINFO_pcRegistryColumns,
	//
	CONST_resId_COLUMNINFO_imGrpListColumns,
	CONST_resId_COLUMNINFO_imGrpMemListColumns_isMgr,
	CONST_resId_COLUMNINFO_imGrpMemListColumns_isCli,

	//
	CONST_resId_COLUMNINFO_confListColumns_isMgr,

	//  2008/12/16
	CONST_resId_COLUMNINFO_qyCfgSystemsColumns,
	CONST_resId_COLUMNINFO_procedObjsViewTable,
	//
	CONST_resId_COLUMNINFO_qnmCfgPcGrpsColumns_nms,
	CONST_resId_qnmCfgSwitchPolicyGrpsColumns,
	CONST_resId_qnmMgrSwitchPolicyColumns,
	CONST_resId_cfgStandardNameColumns,
	CONST_resId_realTimeImTaskListColumns,						//  2008/12/29
	CONST_resId_taskInfoListColumns,							//  2014/09/25
	CONST_resId_sharingObjectListColumns,						//  2009/09/13
	CONST_resId_playerListColumns,								//  2009/02/26		
	CONST_resId_wallListColumns,								//  2009/10/04
	CONST_resId_ipCamListColumns,								//  2016/07/30
	CONST_resId_imNetStatListColumns,							//  2009/10/11
	CONST_resId_talkerListColumns,								//  2009/10/18
	CONST_resId_messengerStatusColumns,							//  2010/08/17
	CONST_resId_qListColumns,									//  2009/12/18
	CONST_resId_imTaskListColumns,								//  2013/02/17
	CONST_resId_imObjListColumns,								//	2014/04/17
	CONST_resId_regInfoListColumns,								//  2014/04/18
	CONST_resId_imGrpListColumns,								//	2014/04/17
	CONST_resId_imGrpMemListColumns,								//	2014/04/17
	CONST_resId_imObjRuleListColumns,								//	2014/04/17
	CONST_resId_dynBmpListColumns,									//  2014/04/18

	CONST_resId_taskListColumns,								//  2008/12/31
	//  CONST_resId_taskListColumns_showMembers,					//  2008/12/31
	CONST_resId_instantAssistant_talkerListColumns,				//  2009/02/23
	CONST_resId_deamonStatus_listColumns,						//  2011/01/16
	CONST_resId_deamonStatus_listColumnsOfChannel,				//  2011/01/28

	CONST_resId_autoScan,										//  2012/08/14
	CONST_resId_rainBrush,										//  2012/08/14
	CONST_resId_searchLight,									//  2012/08/14

	CONST_resId_ok,												//  2013/09/08
	CONST_resId_cancel,											//  2013/09/08

	CONST_resId_versionErr,										//  2014/11/18

	//
	CONST_resId_sharingNotSupportFullScreen,					//  2014/11/18
	CONST_resId_sharingLetWinBeSmaller,									//  2014/11/18
	//
	CONST_resId_gotoMeeting,
	CONST_resId_wouldYouLikeToMeeting,
	CONST_resId_speakingOrNotSpeaking,
	CONST_resId_useMeetingFunction,

	CONST_resId_preTotal,
   	//  
	CONST_resId_total  =  CONST_resId_preTotal  +  1000,
};  

 enum  enumResIds_popupMenu
{
	 CONST_resId_popup0													=	0,
	 CONST_resId_popup_viewPcList										=	1,
	 CONST_resId_popup_viewPcUsrList									=	2,
	 CONST_resId_popup_viewPcRuleList									=	3,
	 CONST_resId_popup_viewVlanMgrList									=	4,
	 CONST_resId_popup_viewUnchkedPcList								=	5,
	 CONST_resId_popup_viewWillAttackPcList								=	6,
	 CONST_resId_popup_viewPcUsrInTab1List								=	7,
	 CONST_resId_popup_viewPcList_netMc2								=	8,
	 CONST_resId_popup_tree_network										=	9,
	 CONST_resId_popup_tree_switch										=	10,
	 CONST_resId_popup_tree_switchPort									=	11,
	 CONST_resId_popup_rootList											=	12,
	 CONST_resId_popup_viewPcList_secChk								=	13,
	 CONST_resId_popup_viewNetDevConn									=	14,
	 CONST_resId_popup_viewPcList_nms									=	15,
	 CONST_resId_popup_viewPcEventList_nms								=	16,
	 CONST_resId_popup_viewNetDevEventList_nms							=	17,
	 CONST_resId_popup_viewSearchList_nms								=	18,
	 CONST_resId_popup_viewPcSpList										=	19,
	 CONST_resId_popup_viewPcList_assetMgr								=	20,
	 CONST_resId_popup_pc												=	21,
	 CONST_resId_popup_viewAssets_os									=	22,
	 CONST_resId_popup_cfgSp_os											=	23,
	 CONST_resId_popup_cfgSp_servicePack								=	24,
	 CONST_resId_popup_viewSp											=	25,
	 CONST_resId_popup_viewSnmpObjRuleList								=	26,
	 CONST_resId_popup_viewConflictConnList								=	27,
	 CONST_resId_popup_viewPcNetworkProp								=	28,
	 CONST_resId_popup_view_auditSth									=	29,
	 CONST_resId_popup_viewPcProcess									=	30,
	 CONST_resId_popup_cfgPcModuleKnowlege_notSel						=	31,
	 CONST_resId_popup_cfgPcModuleKnowlege								=	32,
	 CONST_resId_popup_viewPcRegistry									=	33,
	 CONST_resId_popup_viewPcList_multiSel								=	34,
	 //
	 CONST_resId_popup0_mis												=	100,
	 CONST_resId_popup_viewMessengerAuthList_isMgr						=	101,
	 CONST_resId_popup_viewMessengerAuthList_multiSel_isMgr				=	102,
	 CONST_resId_popup_viewMessengerAuthList_isMgr_mini					=   103,
	 CONST_resId_popup_viewMessengerList_isMgr							=	104,
	 CONST_resId_popup_viewMessengerList_multiSel_isMgr					=	105,
	 CONST_resId_popup_viewMessengerList_isClient						=	106,
	 CONST_resId_popup_viewMessengerList_multiSel_isClient				=	107,
	 //
	 CONST_resId_popup_viewMessengerNeedAuditedList_isMgr				=	108,
	 //
	 CONST_resId_popup_imAmList_isMgr									=	109,
	 //
	 CONST_resId_popup_viewPhoneMessengerList_isMgr						=	110,
	 CONST_resId_popup_viewPhoneMessengerList_multiSel_isMgr			=	111,
	 CONST_resId_popup_viewPhoneMessengerList_notSel_isMgr				=	112,
	 //
	 CONST_resId_popup_mcuList											=	113,
	 CONST_resId_popup_mcu												=	114,	


	 //
	 CONST_resId_popup_viewImGrpList_isMgr								=	130,
	 CONST_resId_popup_viewImGrpList_isClient							=	131,
	 //
	 CONST_resId_popup_viewImGrpMemList_isMgr							=	132,
	 CONST_resId_popup_viewImGrpMemList_multiSel_isMgr					=	133,
	 CONST_resId_popup_viewImGrpMemList_isClient						=	134,
	
	 //
	 //
	 //
	 CONST_resId_popup_viewImTaskList_isMgr								=	150,
	 CONST_resId_popup_viewImTaskList_isClient							=	151,
	 //
	 CONST_resId_popup_customerServiceList_isMgr						=	199,		//  2011/04/03
	 CONST_resId_popup_wwwQmCfgList_isMgr								=	200,
	 CONST_resId_popup_phoneGuestList									=	201,
	 CONST_resId_popup_phoneGuestList_multiSel							=	202,
	 //
	 CONST_resId_popup_gsmModemList										=	220,
	 CONST_resId_popup_sharedDynBmpList_isMgr							=	221,
	 CONST_resId_popup_sharedDynBmpList_multiSel_isMgr					=	222,

	 CONST_resId_popup_sharedDynBmpList_isClient						=	224,	
	 CONST_resId_popup_sharedDynBmpList_notSel_isClient					=	225,

	 CONST_resId_popup_sharedDynBmpRuleList_isMgr						=	228,

	 CONST_resId_popup_viewImObjRuleList_isClient						=	235,		//  2010/09/06

	 //
	 CONST_resId_popup_trayNotify										=	300,	 

	 //
	 CONST_resId_popup_viewProcedObj_load								=	334,
	 CONST_resId_popup_viewProcedObj_bhb								=	335,
	 CONST_resId_popup_viewProcedObj_netMc2								=	336,
	 CONST_resId_popup_viewProcedObj_nms								=	337,
	 CONST_resId_popup_viewProcedObj_secChk								=	338,
	 CONST_resId_popup_viewProcedObj_assetMgr							=	339,
	 CONST_resId_popup_viewProcedObj_misClient							=	340,
	 CONST_resId_popup_viewProcedObj_misMgr								=	341,

	 //
	 CONST_resId_popup_me												=	501,
	 CONST_resId_popup_messenger_isClient								=	502,
	 CONST_resId_popup_messenger_isMgr									=	503,
	 CONST_resId_popup_imGrp_isClient									=	504,
	 CONST_resId_popup_imGrp_isMgr										=	505,
	 CONST_resId_popup_phoneGuest_isClient								=	506,
	 CONST_resId_popup_instantAssistant									=	507,
	 CONST_resId_popup_instantAssistantMem								=	508,
	 CONST_resId_popup_htmlEdit											=	509,
	 CONST_resId_popup_vWall											=	510,
	 CONST_resId_popup_zone												=	511,
	 CONST_resId_popup_avRes											=	512,	//  2018/11/15

	 //
	 CONST_resId_popup_commonList_notSel								=	600,
	 CONST_resId_popup_commonList										=	601,

	 //
	 CONST_resId_popup_imGrpMem_isCli_yz								=	630,	//  2017/08/26

	 //  2007/10/04
	 CONST_resId_menu_dlgTalk_messenger									=	700,
	 CONST_resId_menu_dlgTalk_imGrp										=	701,
	 CONST_resId_menu_dlgVideos											=	702,
	 CONST_resId_menu_dlgSharedWebcams									=	703,
	 CONST_resId_menu_dlgVWall											=	704,
	 CONST_resId_menu_dlgRemoteAssist									=	705,
	 CONST_resId_menu_dlgTest											=	706,	//  2013/02/06
	 CONST_resId_menu_dlgImg_chromaKey									=	707,	//  2013/09/26
	 CONST_resId_menu_dlgTalk_imGrp_msg									=	711,	//  2014/02/01


	 //  
	 CONST_resId_popup0_vDevComs										=	900,
	 CONST_resId_popup_vDevCom											=	901,


	 //  2010/04/14
	 CONST_resId_menu_winCeMain											=	2001,


	 //

};

 #define		CONST_maxnYhGrpTable			10

//  2006/03/07£¬ÎªÁË·½±ã¸ü¶àµÄ±í
#define		MACRO_simpleUsrSqlColumnsEx(  tabName  )													\
						/*  {	CONST_fieldId_yhlx,  _T(  tabName  )_T(  "qyPcRegInfoTab.col0"  ),		SQL_CHAR,	0,	0,	0,	0,	},	//	0  */	\
						{	CONST_fieldId_zb,		_T(  tabName  ) _T(  ".col11"  ),	SQL_CHAR,	0,	0,	4,	0,	},		/*	1  */	\
						{	CONST_fieldId_bb,		_T(  tabName  ) _T(  ".col12"  ),	SQL_CHAR,	0,	0,	3,	0,	},		/*	1  */	\
						{	CONST_fieldId_dw,		_T(  tabName  ) _T(  ".col2"  ),		SQL_CHAR,	0,	0,	2,	0,	},		/*	1  */	\
						{	CONST_fieldId_bm,		_T(  tabName  ) _T(  ".col3"  ),		SQL_CHAR,	0,	0,	1,	0,	},		/*	3  */	\
						{	CONST_fieldId_syr,		_T(  tabName  ) _T(  ".col4"  ),		SQL_CHAR,	0,	0,	0,	0,	},		/*	4  */	

#define		MACRO_eventSimpleUsrSqlColumnsEx(  tabName  )											\
						/*	{	CONST_fieldId_yhlx,	_T(  tabName  )_T(  "qyPcEventTab.col0"  ),		SQL_CHAR,	0,	0,	0,	0,	},	//  1  */	\
						{	CONST_fieldId_zb,	_T(  tabName  ) _T(  ".col5"  ),			SQL_CHAR,	0,	0,	4,	0,	},				\
						{	CONST_fieldId_bb,	_T(  tabName  ) _T(  ".col6"  ),			SQL_CHAR,	0,	0,	3,	0,	},				\
						{	CONST_fieldId_dw,	_T(  tabName  ) _T(  ".col2"  ),			SQL_CHAR,	0,	0,	2,	0,	},	/*	2  */	\
						{	CONST_fieldId_bm,	_T(  tabName  ) _T(  ".col3"  ),			SQL_CHAR,	0,	0,	1,	0,	},	/*	4  */	\
						{	CONST_fieldId_syr,	_T(  tabName  ) _T(  ".col4"  ),			SQL_CHAR,	0,	0,	0,	0,	},	/*	5  */



#endif  //  }


