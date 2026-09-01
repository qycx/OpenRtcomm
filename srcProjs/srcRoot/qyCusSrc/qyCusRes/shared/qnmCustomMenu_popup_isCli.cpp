

#include	"stdafx.h"
#include	<tchar.h>

#include	"myresource_main_isCli.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"isCmdConst.h"




 QY_DMITEM  CONST_popupMenuTable_viewImGrpMemList_isCli[]  =
{
	{	ID_qyProperties,		},
	{	-1,				NULL,	},
};


#ifdef  __SUPPORT_sm__
 QY_DMITEM  CONST_popupMenuTable_phoneGuestList[]  =
{
	{	ID_qySendSm,			},
	{	-2,						},
	{	ID_qyEdit,		        },
	{	-2,						},
	{	ID_qyDel,				},
	{	-2,						},
	{	ID_qyProperties,		},
	{	-1,						},
};

 QY_DMITEM  CONST_popupMenuTable_phoneGuestList_multiSel[]  =
{
	{	ID_qySendSm,			},
	{	-2,						},
	{	ID_qyDel,				},
	{	-1,						},
};


 QY_DMITEM  CONST_popupMenuTable_gsmModemList[]  =
{
	{	ID_qyViewSmContacts,				},
	{	-2,									},
	{	ID_qyCfgDefaultSmServer,			},
	{	-2,									},
	{	ID_qyCfgDefaultSmContact,			},
	{	-2,									},
	{	ID_qyCfgSmContact,					},
	{	-2,									},
	{	ID_qyDel,							},
	{	-2,									},
	{	ID_qyProperties,					},
	{	-1,									},
};
 #endif



 QY_DMITEM  CONST_popupMenuTable_sharedDynBmpList_isCli[]  =
{
	{	ID_viewDynBmp,	},
	{	-2,				},
	{	ID_retrieveAll,		},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_sharedDynBmpList_notSel_isCli[]  =
{
	{	ID_retrieveAll,		},
	{	-1,					},
};

 QY_DMITEM  CONST_popupMenuTable_viewImObjRuleList_isCli[]  =
{
	{	ID_qyRule,		},
	{	-1,				},
};

 QY_DMITEM  CONST_popupMenuTable_viewImTaskList_isCli[]  =
{
	{	ID_qyTalkToTaskPeer,	(  TCHAR  *  )ID_qyTalk,		},
	{	-2,				},
	{	ID_qyProp_imTask,	},
	{	-1,				},
};


 QY_DMITEM  CONST_menuTable_avCall_messenger_isCli[]  =
{
	//  {	ID_stopAvCall,		},
	{	ID_startAvCall,		},
	{	-2,					},
#if  0
	{	ID_startAvCall_ld,	},
	{	ID_startAvCall_ld1,	},
	{	ID_startAvCall_sd,	},
	{	ID_startAvCall_sd1,	},
	{	ID_startAvCall_sd2,	},
	{	ID_startAvCall_sd3,	},
	{	ID_startAvCall_hd,	},
	{	ID_startAvCall_hd1,	},
	{	ID_startAvCall_hd2,	},
	{	ID_startAvCall_hd3,	},
	{	ID_startAvCall_fullHd,	},
	{	ID_startAvCall_fullHd1,	},
	{	ID_startAvCall_fullHd2,	},
	{	ID_startAvCall_fullHd3,	},
	{	-2,					},
#endif
	{	ID_MENU_selectRtsp,		},
	{	-1,					},
};



  QY_DMITEM  CONST_menuTable_avCall_imGrp_isCli[]  =
{
	//  {	ID_stopAvCall,		},
	{	ID_startAvCall,		},
	{	-2,					},
#if  0
	{	ID_startAvCall_ld,	},
	{	ID_startAvCall_ld1,	},
	{	ID_startAvCall_sd,	},
	{	ID_startAvCall_sd1,	},
	{	ID_startAvCall_sd2,	},
	{	ID_startAvCall_sd3,	},
	{	ID_startAvCall_hd,	},
	{	ID_startAvCall_hd1,	},
	{	ID_startAvCall_hd2,	},
	{	ID_startAvCall_hd3,	},
	{	ID_startAvCall_fullHd,	},
	{	ID_startAvCall_fullHd1,	},
	{	ID_startAvCall_fullHd2,	},
	{	ID_startAvCall_fullHd3,	},
	{	-2,									},
#endif
	{	ID_MENU_selectRtsp,		},
#if  0
	{	-3,		(  TCHAR  *  )CONST_resId_menu_conferenceWall,	(  TCHAR  *  )CONST_nullTable,	},
	{	-2,									},
#endif
	{	-1,					},
};

#if  0
 QY_DMITEM  CONST_table_shareFullScreen[]  =
{
	{	ID_startShareFullScreen,	},
#if  0
	{	-2,							},
	{	ID_startShareFullScreen_300k,	},
	{	ID_startShareFullScreen_450k,		},
#endif
#if  0
	{	ID_startShareFullScreen_600k,		},
	{	ID_startShareFullScreen_900k,		},
	{	ID_startShareFullScreen_1500k,		},		//  2013/04/13
	{	ID_startShareFullScreen_1800k,		},
#endif
	{	-1,					},
};
#if  10
 QY_DMITEM  CONST_table_startShareMediaFile[]  =
{
 	{	ID_startShareMediaFile,		},
#if  0
	{	-2,							},
	{	ID_startShareMediaFile_dev2fps,			},
	{	ID_startShareMediaFile_dev5fps,			},
	{	ID_startShareMediaFile_dev10fps,		},
	{	ID_startShareMediaFile_dev5fps1,		},
#if  0
	{	ID_startShareMediaFile_dev5fps2,		},
	{	ID_startShareMediaFile_dev5fps3,		},
#endif
	{	ID_startShareMediaFile_devSd24fps,		},
	{	ID_startShareMediaFile_devSd25fps,		},
	{	ID_startShareMediaFile_devSd30fps,		},
	{	ID_startShareMediaFile_dev24fps,		},			//  2012/11/08
	{	ID_startShareMediaFile_dev25fps,		},			//  2012/11/08
	{	ID_startShareMediaFile_dev30fps,		},			//  2012/11/08
#endif
	{	-1,					},
};

 QY_DMITEM  CONST_table_startShareMediaDevice[]  =
{
 	{	ID_startShareMediaDevice,					},
#if  0
	{	-2,											},
	{	ID_startShareMediaDevice_dev2fps,			},
	{	ID_startShareMediaDevice_dev5fps1,			},
#if  0
	{	ID_startShareMediaDevice_dev5fps2,			},
	{	ID_startShareMediaDevice_dev5fps3,			},
#endif
	{	ID_startShareMediaDevice_devSd24fps,		},
	{	ID_startShareMediaDevice_devSd25fps,		},
	{	ID_startShareMediaDevice_devSd30fps,		},
	{	ID_startShareMediaDevice_dev24fps,			},
	{	ID_startShareMediaDevice_dev25fps,			},
	{	ID_startShareMediaDevice_dev30fps,			},
#endif
	{	-1,					},
};
#endif

#endif


 QY_DMITEM  CONST_menuTable_share_isCli[]  =
{
	{	ID_stopShareScreen,			},
	{	ID_startShareScreen,		},
	{	-2,							},
#if  0
	{	-3,	(  TCHAR  *  )CONST_resId_menu_shareFullScreen,		(  TCHAR  *  )CONST_table_shareFullScreen,			},
#endif
	{	ID_startShareFullScreen,	},
#if  0	//  def  __DEBUG__
	{	ID_startShareScreen_dx,		},
	{	ID_startShareFullScreen_dx,	},
	{	-2,							},
#endif
	{	-2,							},
#if 0
	{	-3,	(  TCHAR  *  )CONST_resId_menu_startShareMediaFile,		(  TCHAR  *  )CONST_table_startShareMediaFile,			},
#else
 	{	ID_startShareMediaFile,		},
#endif
	{	-2,							},
	{	ID_startShareMediaDevice,	},
	{	ID_startShareMediaDevice_unresizable,	},

	//
	{	-2,							},
	{	ID_shareDevice_grp1,	},
	{	ID_shareDevice_grp2,	},
	{	ID_shareDevice_grp3,	},
	{	ID_shareDevice_grp4,	},



#ifdef  _DEBUG
	{	-2,							},
	{	ID_qyTest,					},
#endif

	{	-1,					},
};

 QY_DMITEM  CONST_menuTable_op_messenger_isCli[]  =
{
	{	ID_stopRemoteAssist,			},
	{	ID_startRemoteAssist,			},
	{	ID_startFullScreenRemoteAssist,	},
	{	-1,								},
};

QY_DMITEM  CONST_menuTable_op_yt_messenger_isCli[]  =
{
	{	ID_remotePtzControl,				},
	{	-1,								},
};

 
 QY_DMITEM  CONST_popupMenuTable_commonList_notSel_isCli[]  =
{
	{	ID_qyAdd,		        },
	{	-2,						},
	{	ID_qyImport,			},
	{	ID_qyExport,			},
	{	ID_qyClearUp,		},
	{	-1,						},
};


 QY_DMITEM  CONST_popupMenuTable_commonList_isCli[]  =
{
	{	ID_qyEdit,		        },
	{	-2,						},
	{	ID_qyDel,				},
	{	-2,						},
	{	ID_qyProperties,		},
	{	-1,						},
};


  QY_DMITEM  CONST_menuTable_cfgAv_messenger_isCli[]  =
{
#if  0
	{	ID_stopScrollBar,		},
	{	ID_startScrollBar,		},
	{	-2,	},
#endif
	{	ID_cfgRasOptions,	(  TCHAR  *  )CONST_resId_policy_isClient,			},
	//  {	ID_cfgVideoConference,	},
	{	-2,						},
	{	ID_ucbNotViewGps,	},
	{	ID_ucbViewGps,	},
	{	-2,				},
	{	ID_notShowGpsData,	},
	{	ID_showGpsData,		},
	{	-2,						},
	{	ID_about,				},
	{	-1,				},
};

  QY_DMITEM  CONST_menuTable_cfgAv_messenger_mini_isCli[]  =
{
#if  0
	{	ID_stopScrollBar,		},
	{	ID_startScrollBar,		},
	{	-2,	},
#endif
	{	ID_cfgRasOptions,	(  TCHAR  *  )CONST_resId_policy_isClient,			},
	//  {	ID_cfgVideoConference,	},
	{	-1,				},
};


 QY_DMITEM  CONST_menuTable_cfgAv_imGrp_isCli[]  =
{
#if  0
	{	ID_stopScrollBar,		},
	{	ID_startScrollBar,		},
	{	-2,	},
#endif
	{	ID_cfgRasOptions,	(  TCHAR  *  )CONST_resId_policy_isClient,			},
	//  {	ID_cfgVideoConference,	},
	{	-2,						},
	{	ID_ucbHideImGrpMems,	},
	{	ID_ucbShowImGrpMems,	},
	{	-2,						},
	{	ID_about,				},
	{	-1,				},
};


 //  2007/10/04
 QY_DMITEM  CONST_menuTable_dlgTalk_messenger_isCli[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_avCall,			(  TCHAR  *  )CONST_menuTable_avCall_messenger_isCli,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_share,			(  TCHAR  *  )CONST_menuTable_share_isCli,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,				(  TCHAR  *  )CONST_menuTable_op_messenger_isCli,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op_ptz,			(  TCHAR  *  )CONST_menuTable_op_yt_messenger_isCli,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,			(  TCHAR  *  )CONST_menuTable_cfgAv_messenger_isCli,	},
	//  {	ID_fullScreen,			},
	{	-1,				},
};




 QY_DMITEM  CONST_menuTable_dlgTalk_imGrp_isCli[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_avCall,			(  TCHAR  *  )CONST_menuTable_avCall_imGrp_isCli,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_share,			(  TCHAR  *  )CONST_menuTable_share_isCli,	},
	{	ID_2dVWall_new,				},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,			(  TCHAR  *  )CONST_menuTable_cfgAv_imGrp_isCli,	},
	//  {	ID_fullScreen,			},
	{	-1,							},
};

 QY_DMITEM  CONST_menuTable_dlgTalk_imGrp_msg_isCli[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,			(  TCHAR  *  )CONST_menuTable_cfgAv_imGrp_isCli,	},

	{	-1,							},
};

  QY_DMITEM  CONST_menuTable_scrollBar_noFullScreen_isCli[]  =
{
	{	ID_stopScrollBar,		},
	{	ID_startScrollBar,		},
	{	-1,						},
};

 //  2008/11/06
 QY_DMITEM  CONST_menuTable_dlgRemoteAssist_isCli[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,				(  TCHAR  *  )CONST_menuTable_scrollBar_noFullScreen_isCli,	},
	{	-1,							},	
};

 ///////////////////
 #if  0  //  2013/02/06

 QY_DMITEM  CONST_menuTable_runningStatus_misClient[]  =
{
	{	ID_qyRealTimeTaskList,			},
	{	-2,								},
	{	ID_taskInfoList,				},
	{	-2,								},
	{	ID_sharingObjectList,			},
	{	-2,								},
	{	ID_playerList,				},
	{	-2,								},
	{	ID_wallList,				},
	{	-2,							},
	{	ID_imNetStatList,				},
	{	-2,							},
	{	ID_talkerList,				},
	{	ID_messengerStatusList,		},
	{	-2,		},
	{	ID_qList,					},
	{	-2,	},
	{	ID_myDbStatus,			},
	{	-2,	},		
	{	ID_imTaskList_unproced_test,	},
	{	ID_imTaskList_cur_test,			},
	{	-1,		},
};


#endif

#if 0
 QY_DMITEM  CONST_menuTable_dlgTest_isCli[]  =
 {
	{	-3,		(  TCHAR  *  )CONST_resId_menu_runningStatus,				(  TCHAR  *  )CONST_menuTable_runningStatus_misClient,	},
	 {	-1,							},
 };
 //
  QY_DMITEM  CONST_menuTable_scrollBar[]  =
{
	{	ID_stopScrollBar,		},
	{	ID_startScrollBar,		},
	{	-2,						},
	{	ID_fullScreen,			},
	{	-1,						},
};
#endif


 //  2008/11/06
 QY_DMITEM  CONST_menuTable_dlgVideos_isCli[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,				(  TCHAR  *  )CONST_menuTable_scrollBar_noFullScreen_isCli,	},
	{	ID_fullScreen,			},
	{	-1,							},	
};



 //
 QY_DMITEM  CONST_menuTable_avCall_sharedWebcams_isCli[]  =
 {
	 {	-1,					},
 };

 QY_DMITEM  CONST_menuTable_dlgSharedWebcams_isCli[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_avCall,			(  TCHAR  *  )CONST_menuTable_avCall_sharedWebcams_isCli,	},
	{	-1,			},
};

 QY_DMITEM  CONST_menuTable_op_dlgVWall_isCli[]  =
{
	{	ID_stopScrollBar,		},
	{	ID_startScrollBar,		},
	//  {	-2,					},
	//  {	ID_fullScreen,		},
	{	-2,						},
	{	ID_viewToolbox,	},
	{	-2,						},
	{	ID_stopEditing,			},
	{	ID_startToEdit,			},
	{	ID_stopShowingRules,	},
	{	ID_startToShowRules,	},
	{	-2,						},
	{	ID_open,				},
	{	-2,						},
	{	ID_save,				},
	{	-2,						},
	{	IDCANCEL,				},
	{	-1,			},
};


 QY_DMITEM  CONST_menuTable_dlgVWall_isCli[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,			(  TCHAR  *  )CONST_menuTable_op_dlgVWall_isCli,	},
	{	ID_fullScreen,			},
	{	-1,			},
};

  QY_DMITEM  CONST_popupMenuTable_trayNotify_isCli[]  =
{
	{	ID_qyShowWnd,			},
	{	-2,							},
	//{	ID_APP_ABOUT,				},
	{	ID_about,				},
	{	-2,							},
	{	ID_qyQuitMainWnd,			},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_me_isCli[]  =
{
#ifdef  __SUPPORT_sm__
	{	ID_qySendSm,					},
	{	-2,								},
#endif
	//  {	ID_imTaskList_his,				},
	//  {	-2,		},
	//  {	-3,			(  TCHAR  *  )CONST_resId_menu_xiaoXiChaKan,				(  TCHAR  *  )CONST_menuTable_xiaoXiChaKan_misClient,	},
	//  {	-2,		},
	//  {	ID_qyEdit,	(  TCHAR  *  )CONST_resId_yongHuXinXiBianJiShenHe,	},	//  "ÓÃ»§ÐÅÏ¢±à¼­ÉóºË(&B)",        
	//  {	-2,		},

	{	ID_viewOfflineRes,				},		// 2015/08/05
	{	-2,								},
	{	ID_qyProperties,			},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_messenger_isCli[]  =
{
	{	ID_qyTalk,					},
	{	-2,							},
#ifdef  __SUPPORT_sm__
	{	ID_qySendSm,			},
	{	-2,							},
#endif
	{	ID_qyRule,					},
	{	-2,							},
#if  0
	{	ID_imTaskList_unproced,		},
	{	-2,		},
	{	ID_imTaskList_cur,				},
	{	-2,		},
	{	ID_imTaskList_his,				},
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_xiaoXiChaKan,				(  TCHAR  *  )CONST_menuTable_xiaoXiChaKan_misClient,	},
	{	-2,		},
#endif
	{	ID_qyProperties,			},
	{	-1,				},
};


 //
 QY_DMITEM  CONST_popupMenuTable_imGrpMem_isCli_yz[]  =  
 {
	{	ID_yz_stopShareScreen,			},
	{	ID_yz_shareScreen,			},
	{	-2,		},
	{	ID_menuItemIdc_remotePtzControl,	},
	{	-2,			},
	{	ID_qyEdit,		        },
	{	-2,			},

	{	ID_qyProperties,			},
	{	-1,				},

 };


 //
 QY_DMITEM  CONST_popupMenuTable_imGrp_isCli[]  =
{
	{	ID_qyDiscuss,					},
	{	-2,								},
	//  {	ID_qyImGrpMemList,				},
	//  {	-2,								},
	{	ID_qyRule,						},
	{	-2,		},
	{	ID_qyDel,	},
	{	-2,								},
	{	ID_qyProperties,				},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_phoneGuest_isCli[]  =
{
	{	ID_qyProperties,			},
	{	-1,				},
};

 QY_DMITEM  CONST_popupMenuTable_instantAssistant_isCli[]  =
{
#ifndef  __WINCE__
	{	SC_CLOSE,		},
#endif
	{	-1,					},
};

 QY_DMITEM  CONST_popupMenuTable_instantAssistantMem_isCli[]  =
{
	{	ID_stopSpeaking,		},
	{	ID_requestToSpeak,		},
	{	-1,					},
};

 QY_DMITEM  CONST_popupMenuTable_htmlEdit_isCli[]  =
 {
	 {	ID_qyCopy,					},
	 {	ID_qyPaste,					},
	 {	-1,							},
 };


 QY_DMITEM  CONST_popupMenuTable_vWall_isCli[]  =
 {
	 //  {	ID_qyCusName,				},
	 //  {	-2,							},
	 {	ID_qySetBackground,			},
	 {	ID_qyResetBackground,			},
	 //  {	-2,							},
	 //  {	ID_setVWallResolution,		},
	 {	-1,							},
 };

  QY_DMITEM  CONST_popupMenuTable_zone_isCli[]  =
 {
	 {	ID_qySetDynBmp,				},
	 {	ID_setMessengerBmp,				},
#if  0
	 {	ID_qySetImGrpMemBmp,			},
#endif
	 {	-2,								},
	 {	ID_selectMessenger,				},
#if  0
	 {	-2,								},
	 {	ID_ucbNotViewScreen,			},
	 {	ID_ucbViewScreen,				},	 
	 {	-2,								},
	 {	ID_ucbNotViewWebcam0,			},
	 {	ID_ucbViewWebcam0,				},
	 {	-2,								},
	 {	ID_ucbNotViewWebcam1,			},
	 {	ID_ucbViewWebcam1,				},
	 {	-2,								},
	 {	ID_ucbNotViewWebcam2,			},
	 {	ID_ucbViewWebcam2,				},
#endif
	 	
	 {	-1,							},
 };


 QY_DMITEM  CONST_popupMenuTable_isCli[]  =
{
	{	CONST_resId_popup0,													0,		(  TCHAR  *  )CONST_popupMenuTable_0,			},									//  -0
	//
	{	CONST_resId_popup_viewMessengerList_isClient,						0,		(  TCHAR  *  )CONST_popupMenuTable_messenger_isCli,					},	//  101


	{	CONST_resId_popup_viewImGrpList_isClient,							0,		(  TCHAR  *  )CONST_popupMenuTable_imGrp_isCli,					},
	
	{	CONST_resId_popup_viewImGrpMemList_isClient,						0,		(  TCHAR  *  )CONST_popupMenuTable_viewImGrpMemList_isCli,					},
	{	CONST_resId_popup_viewImTaskList_isClient,							0,		(  TCHAR  *  )CONST_popupMenuTable_viewImTaskList_isCli,						},

#ifdef  __SUPPORT_sm__
	{	CONST_resId_popup_phoneGuestList,									0,		(  TCHAR  *  )CONST_popupMenuTable_phoneGuestList,								},
	{	CONST_resId_popup_phoneGuestList_multiSel,							0,		(  TCHAR  *  )CONST_popupMenuTable_phoneGuestList_multiSel,						},
	//
	{	CONST_resId_popup_gsmModemList,										0,		(  TCHAR  *  )CONST_popupMenuTable_gsmModemList,							},
#endif
	{	CONST_resId_popup_sharedDynBmpList_isClient,						0,		(  TCHAR  *  )CONST_popupMenuTable_sharedDynBmpList_isCli,				},
	{	CONST_resId_popup_sharedDynBmpList_notSel_isClient,					0,		(  TCHAR  *  )CONST_popupMenuTable_sharedDynBmpList_notSel_isCli,				},


	//
	{	CONST_resId_popup_viewImObjRuleList_isClient,						0,		(  TCHAR  *  )CONST_popupMenuTable_viewImObjRuleList_isCli,			},
	
	//
	//
	{	CONST_resId_popup_trayNotify,										0,		(  TCHAR  *  )CONST_popupMenuTable_trayNotify_isCli,							},
	{	CONST_resId_popup_me,												0,		(  TCHAR  *  )CONST_popupMenuTable_me_isCli,									},
	{	CONST_resId_popup_messenger_isClient,								0,		(  TCHAR  *  )CONST_popupMenuTable_messenger_isCli,					},
	{	CONST_resId_popup_imGrp_isClient,									0,		(  TCHAR  *  )CONST_popupMenuTable_imGrp_isCli,						},
	{	CONST_resId_popup_phoneGuest_isClient,								0,		(  TCHAR  *  )CONST_popupMenuTable_phoneGuest_isCli,					},
	{	CONST_resId_popup_instantAssistant,									0,		(  TCHAR  *  )CONST_popupMenuTable_instantAssistant_isCli,					},
	{	CONST_resId_popup_instantAssistantMem,								0,		(  TCHAR  *  )CONST_popupMenuTable_instantAssistantMem_isCli,					},
	{	CONST_resId_popup_htmlEdit,											0,		(  TCHAR  *  )CONST_popupMenuTable_htmlEdit_isCli,							},
	{	CONST_resId_popup_vWall,											0,		(  TCHAR  *  )CONST_popupMenuTable_vWall_isCli,							},
	{	CONST_resId_popup_zone,												0,		(  TCHAR  *  )CONST_popupMenuTable_zone_isCli,							},


	//
	{	CONST_resId_popup_commonList_notSel,								0,		(  TCHAR  *  )CONST_popupMenuTable_commonList_notSel_isCli,					},
	{	CONST_resId_popup_commonList,										0,		(  TCHAR  *  )CONST_popupMenuTable_commonList_isCli,							},

	//
	{	CONST_resId_popup_imGrpMem_isCli_yz,								0,		(  TCHAR  *  )CONST_popupMenuTable_imGrpMem_isCli_yz,					},


	//  2007/10/04
	{	CONST_resId_menu_dlgTalk_messenger,									0,		(  TCHAR  *  )CONST_menuTable_dlgTalk_messenger_isCli,						},

	{	CONST_resId_menu_dlgTalk_imGrp,										0,		(  TCHAR  *  )CONST_menuTable_dlgTalk_imGrp_isCli,							},
	{	CONST_resId_menu_dlgTalk_imGrp_msg,									0,		(  TCHAR  *  )CONST_menuTable_dlgTalk_imGrp_msg_isCli,							},
	{	CONST_resId_menu_dlgVideos,											0,		(  TCHAR  *  )CONST_menuTable_dlgVideos_isCli,								},
	{	CONST_resId_menu_dlgSharedWebcams,									0,		(  TCHAR  *  )CONST_menuTable_dlgSharedWebcams_isCli,							},
	{	CONST_resId_menu_dlgVWall,											0,		(  TCHAR  *  )CONST_menuTable_dlgVWall_isCli,							},
	{	CONST_resId_menu_dlgRemoteAssist,									0,		(  TCHAR  *  )CONST_menuTable_dlgRemoteAssist_isCli,						},
#if  0
	{	CONST_resId_menu_dlgTest,											0,		(  TCHAR  *  )CONST_menuTable_dlgTest_isCli,								},
#endif
	{	-1,		NULL,		},
};


