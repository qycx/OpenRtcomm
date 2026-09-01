

#include	"stdafx.h"
#include	<tchar.h>

#include	"myresource_main_isCliHelp.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"isCmdConst.h"



#if  0
 QY_DMITEM  CONST_popupMenuTable_viewImGrpMemList_isCli[]  =
{
	{	ID_qyProperties,		},
	{	-1,				NULL,	},
};

#endif
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


#if  0
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
#endif


 QY_DMITEM  CONST_menuTable_avCall_messenger_isCliHelp[]  =
{
#if 0
	//  {	ID_stopAvCall,		},
	{	ID_startAvCall,		},
	{	-2,					},
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
	{	-1,					},
};



  QY_DMITEM  CONST_menuTable_avCall_imGrp_isCliHelp[]  =
{
#if 0
	//  {	ID_stopAvCall,		},
	{	ID_startAvCall,		},
	{	-2,					},
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
#if  0
	{	-3,		(  TCHAR  *  )CONST_resId_menu_conferenceWall,	(  TCHAR  *  )CONST_nullTable,	},
	{	-2,									},
#endif
#endif
	{	-1,					},
};

#if  0
 QY_DMITEM  CONST_table_shareFullScreen_isCliHelp[]  =
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
#endif

#if  0
 QY_DMITEM  CONST_table_startShareMediaFile_isCliHelp[]  =
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

 QY_DMITEM  CONST_table_startShareMediaDevice_isCliHelp[]  =
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

 QY_DMITEM  CONST_menuTable_share_isCliHelp[]  =
{
	{	ID_stopShareScreen,			},
	{	ID_startShareScreen,		},
	{	-2,							},
	//{	-3,	(  TCHAR  *  )CONST_resId_menu_shareFullScreen,		(  TCHAR  *  )CONST_table_shareFullScreen_isCliHelp,			},
#if  0	//  def  __DEBUG__
	{	ID_startShareScreen_dx,		},
	{	ID_startShareFullScreen_dx,	},
	{	-2,							},
#endif
	{	-2,							},
	//{	-3,	(  TCHAR  *  )CONST_resId_menu_startShareMediaFile,		(  TCHAR  *  )CONST_table_startShareMediaFile_isCliHelp,			},
	{	-2,							},
	//{	-3,	(  TCHAR  *  )CONST_resId_menu_startShareMediaDevice,		(  TCHAR  *  )CONST_table_startShareMediaDevice_isCliHelp,			},
#if  0
	{	ID_startShareMediaDevice1,	},
#endif

#ifdef  _DEBUG
	{	-2,							},
	{	ID_qyTest,					},
#endif

	{	-1,					},
};

 QY_DMITEM  CONST_menuTable_op_messenger_isCliHelp[]  =
{
#if 0
	{	ID_stopRemoteAssist,			},
	{	ID_startRemoteAssist,			},
	{	ID_startFullScreenRemoteAssist,	},
#endif
	{	-1,								},

};

QY_DMITEM  CONST_menuTable_op_yt_messenger_isCliHelp[]  =
{
	{	ID_remotePtzControl,				},
	{	-1,								},
};

#if  0
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
#endif

#if  0
  QY_DMITEM  CONST_menuTable_cfgAv_messenger_isCliHelp[]  =
{
#if  0
	{	ID_stopScrollBar,		},
	{	ID_startScrollBar,		},
	{	-2,	},
#endif
	{	ID_cfgRasOptions,	(  TCHAR  *  )CONST_resId_policy_isClient,			},
	//  {	ID_cfgVideoConference,	},
	{	-2,						},
	//
	{	ID_ucbNotViewGps,	},
	{	ID_ucbViewGps,	},
	{	-2,				},
	{	ID_notShowGpsData,	},
	{	ID_showGpsData,		},
	{	-1,				},
};

 QY_DMITEM  CONST_menuTable_cfgAv_imGrp_isCliHelp[]  =
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
	//
	{	-1,				},
};


 //  2007/10/04
 QY_DMITEM  CONST_menuTable_dlgTalk_messenger_isCliHelp[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_avCall,			(  TCHAR  *  )CONST_menuTable_avCall_messenger_isCliHelp,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_share,			(  TCHAR  *  )CONST_menuTable_share_isCliHelp,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,				(  TCHAR  *  )CONST_menuTable_op_messenger_isCliHelp,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op_ptz,			(  TCHAR  *  )CONST_menuTable_op_yt_messenger_isCliHelp,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,			(  TCHAR  *  )CONST_menuTable_cfgAv_messenger_isCliHelp,	},
	//  {	ID_fullScreen,			},
	{	-1,				},
};

 //  2013/09/13
  QY_DMITEM  CONST_menuTable_dlgTalk_messenger_mini_isCliHelp[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_avCall,			(  TCHAR  *  )CONST_menuTable_avCall_messenger_isCliHelp,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_share,			(  TCHAR  *  )CONST_menuTable_share_isCliHelp,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,				(  TCHAR  *  )CONST_menuTable_op_messenger_isCliHelp,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,			(  TCHAR  *  )CONST_menuTable_cfgAv_messenger_isCliHelp,	},
	//  {	ID_fullScreen,			},
	{	-1,				},
};


 QY_DMITEM  CONST_menuTable_dlgTalk_imGrp_isCliHelp[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_avCall,			(  TCHAR  *  )CONST_menuTable_avCall_imGrp_isCliHelp,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_share,			(  TCHAR  *  )CONST_menuTable_share_isCliHelp,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,			(  TCHAR  *  )CONST_menuTable_cfgAv_imGrp_isCliHelp,	},
	//  {	ID_fullScreen,			},

	{	-1,							},
};
#endif


  QY_DMITEM  CONST_menuTable_scrollBar_noFullScreen_isCliHelp[]  =
{
	{	ID_stopScrollBar,		},
	{	ID_startScrollBar,		},
	{	-1,						},
};

 //  2008/11/06
 QY_DMITEM  CONST_menuTable_dlgRemoteAssist_isCliHelp[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,				(  TCHAR  *  )CONST_menuTable_scrollBar_noFullScreen_isCliHelp,	},
	{	-1,							},	
};

 
  QY_DMITEM  CONST_menuTable_runningStatus_isCliHelp[]  =
{
	{	ID_activeImObjList,	},
	{	-2,					},
	//  
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
	{	ID_ipCamList,				},
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

  //extern  QY_DMITEM  CONST_menuTable_chaKan_isCli_noMfc[];

 QY_DMITEM  CONST_menuTable_dlgTest_isCliHelp[]  =
 {
	{	-3,		(  TCHAR  *  )CONST_resId_menu_runningStatus,				(  TCHAR  *  )CONST_menuTable_runningStatus_isCliHelp,	},
	//{	-2,	},		
	//{	-3,		(  TCHAR  *  )CONST_resId_menu_chaKan,						(  TCHAR  *  )CONST_menuTable_chaKan_isCli_noMfc,	},	
	{	-1,							},
 };



 ///////////////////



 //  2008/11/06
 QY_DMITEM  CONST_menuTable_dlgVideos_isCliHelp[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,				(  TCHAR  *  )CONST_menuTable_scrollBar_noFullScreen_isCliHelp,	},
	{	ID_fullScreen,			},
	{	-1,							},	
};



 QY_DMITEM  CONST_menuTable_op_dlgVWall_isCliHelp[]  =
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


 QY_DMITEM  CONST_menuTable_dlgVWall_isCliHelp[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,			(  TCHAR  *  )CONST_menuTable_op_dlgVWall_isCliHelp,	},
	{	ID_fullScreen,			},
	{	-1,			},
};

  QY_DMITEM  CONST_popupMenuTable_trayNotify_isCliHelp[]  =
{
	{	ID_qyShowWnd,			},
	{	-2,							},
	//  {	ID_APP_ABOUT,				},
	{	ID_about,					},
	{	-2,							},
	{	ID_qyQuitMainWnd,			},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_me_isCliHelp[]  =
{
	{	-1,				},
};

 QY_DMITEM  CONST_popupMenuTable_messenger_isCliHelp[]  =
{
	{	-1,				},
};

 QY_DMITEM  CONST_popupMenuTable_imGrp_isCliHelp[]  =
{
	{	ID_qyDiscuss,					},
	{	-2,								},
	//  {	ID_qyImGrpMemList,				},
	//  {	-2,								},
	{	ID_qyRule,						},
	//
	{	-2,			},
	{	ID_qyDel,	},
	{	-2,								},
	{	ID_qyProperties,				},
	{	-1,				},
};

#if  0
 QY_DMITEM  CONST_popupMenuTable_phoneGuest_isCli[]  =
{
	{	ID_qyProperties,			},
	{	-1,				},
};
#endif

 QY_DMITEM  CONST_popupMenuTable_instantAssistant_isCliHelp[]  =
{
#ifndef  __WINCE__
	{	SC_CLOSE,		},
#endif
	{	-1,					},
};

 QY_DMITEM  CONST_popupMenuTable_instantAssistantMem_isCliHelp[]  =
{
	{	ID_stopSpeaking,		},
	{	ID_requestToSpeak,		},
	{	-1,					},
};

 QY_DMITEM  CONST_popupMenuTable_htmlEdit_isCliHelp[]  =
 {
	 {	ID_qyCopy,					},
	 {	ID_qyPaste,					},
	 {	-1,							},
 };


 QY_DMITEM  CONST_popupMenuTable_vWall_isCliHelp[]  =
 {
	 //  {	ID_qyCusName,				},
	 //  {	-2,							},
	 {	ID_qySetBackground,			},
	 {	ID_qyResetBackground,			},
	 //  {	-2,							},
	 //  {	ID_setVWallResolution,		},
	 {	-1,							},
 };

  QY_DMITEM  CONST_popupMenuTable_zone_isCliHelp[]  =
 {
	 {	ID_qySetDynBmp,				},
	 {	ID_setMessengerBmp,				},
#if  0
	 {	ID_qySetImGrpMemBmp,			},
#endif
	 {	-2,								},
	 //{	ID_selectMessenger,				},
	 //
	 {	ID_setZone_walls,				},
	 //
#if  0  //  def  __DEBUG__
	 {	ID_setZone_container,			},		//  2016/08/16
#endif
	 //
	 {	-1,							},
 };


    QY_DMITEM  CONST_popupMenuTable_avRes_isCliHelp[]  =
 {
	 //
	 {	ID_cancelTonglian,				},
	 {	ID_tonglian,				},
	 //
	 //
	 {	-1,							},
 };





   //  2013/09/26
 QY_DMITEM  *  CONST_menuTable_dlgImg_chromaKey  =  CONST_menuTable_dlgVideos_isCliHelp;


 QY_DMITEM  CONST_popupMenuTable_isCliHelp[]  =
{
	{	CONST_resId_popup0,													0,		(  TCHAR  *  )CONST_popupMenuTable_0,			},									//  -0
	//
#if  0
	{	CONST_resId_popup_viewMessengerList_isClient,						0,		(  TCHAR  *  )CONST_popupMenuTable_messenger_isCli,					},	//  101


	{	CONST_resId_popup_viewImGrpList_isClient,							0,		(  TCHAR  *  )CONST_popupMenuTable_imGrp_isCli,					},
	{	CONST_resId_popup_viewImGrpMemList_isClient,						0,		(  TCHAR  *  )CONST_popupMenuTable_viewImGrpMemList_isCli,					},
	{	CONST_resId_popup_viewImTaskList_isClient,							0,		(  TCHAR  *  )CONST_popupMenuTable_viewImTaskList_isCli,						},


	{	CONST_resId_popup_sharedDynBmpList_isClient,						0,		(  TCHAR  *  )CONST_popupMenuTable_sharedDynBmpList_isCli,				},
	{	CONST_resId_popup_sharedDynBmpList_notSel_isClient,					0,		(  TCHAR  *  )CONST_popupMenuTable_sharedDynBmpList_notSel_isCli,				},


	//
	{	CONST_resId_popup_viewImObjRuleList_isClient,						0,		(  TCHAR  *  )CONST_popupMenuTable_viewImObjRuleList_isCli,			},
#endif	
	//
	//
	{	CONST_resId_popup_trayNotify,										0,		(  TCHAR  *  )CONST_popupMenuTable_trayNotify_isCliHelp,							},
	{	CONST_resId_popup_me,												0,		(  TCHAR  *  )CONST_popupMenuTable_me_isCliHelp,									},
	{	CONST_resId_popup_messenger_isClient,								0,		(  TCHAR  *  )CONST_popupMenuTable_messenger_isCliHelp,					},
	{	CONST_resId_popup_imGrp_isClient,									0,		(  TCHAR  *  )CONST_popupMenuTable_imGrp_isCliHelp,						},
	//  {	CONST_resId_popup_phoneGuest_isClient,								0,		(  TCHAR  *  )CONST_popupMenuTable_phoneGuest_isCli,					},
	{	CONST_resId_popup_instantAssistant,									0,		(  TCHAR  *  )CONST_popupMenuTable_instantAssistant_isCliHelp,					},
	{	CONST_resId_popup_instantAssistantMem,								0,		(  TCHAR  *  )CONST_popupMenuTable_instantAssistantMem_isCliHelp,					},
	{	CONST_resId_popup_htmlEdit,											0,		(  TCHAR  *  )CONST_popupMenuTable_htmlEdit_isCliHelp,							},
	{	CONST_resId_popup_vWall,											0,		(  TCHAR  *  )CONST_popupMenuTable_vWall_isCliHelp,							},
	{	CONST_resId_popup_zone,												0,		(  TCHAR  *  )CONST_popupMenuTable_zone_isCliHelp,							},

	{	CONST_resId_popup_avRes,											0,		(  TCHAR  *  )CONST_popupMenuTable_avRes_isCliHelp,							},

#if  0
	//
	{	CONST_resId_popup_commonList_notSel,								0,		(  TCHAR  *  )CONST_popupMenuTable_commonList_notSel_isCli,					},
	{	CONST_resId_popup_commonList,										0,		(  TCHAR  *  )CONST_popupMenuTable_commonList_isCli,							},
#endif
	//  2007/10/04
	//{	CONST_resId_menu_dlgTalk_messenger,									0,		(  TCHAR  *  )CONST_menuTable_dlgTalk_messenger_isCliHelp,						},
	//  {	CONST_resId_menu_dlgTalk_messenger_mini,							0,		(  TCHAR  *  )CONST_menuTable_dlgTalk_messenger_mini_isCliHelp,					},
	//{	CONST_resId_menu_dlgTalk_imGrp,										0,		(  TCHAR  *  )CONST_menuTable_dlgTalk_imGrp_isCliHelp,							},
	{	CONST_resId_menu_dlgVideos,											0,		(  TCHAR  *  )CONST_menuTable_dlgVideos_isCliHelp,								},
	//  {	CONST_resId_menu_dlgSharedWebcams,									0,		(  TCHAR  *  )CONST_menuTable_dlgSharedWebcams_isCli,							},
	{	CONST_resId_menu_dlgVWall,											0,		(  TCHAR  *  )CONST_menuTable_dlgVWall_isCliHelp,							},
	{	CONST_resId_menu_dlgRemoteAssist,									0,		(  TCHAR  *  )CONST_menuTable_dlgRemoteAssist_isCliHelp,						},
	{	CONST_resId_menu_dlgTest,											0,		(  TCHAR  *  )CONST_menuTable_dlgTest_isCliHelp,								},
	{	CONST_resId_menu_dlgImg_chromaKey,									0,		(  TCHAR  *  )CONST_menuTable_dlgImg_chromaKey,				},

	{	-1,		NULL,		},
};

