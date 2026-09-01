

#include	"stdafx.h"
#include	<tchar.h>

#include	"myresource_main.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"isCmdConst.h"



 //  2007/05/16

 QY_DMITEM  CONST_popupMenuTable_viewMessengerAuthList_isMgr[]  =
{
	{	ID_qyEdit,						(  TCHAR  *  )CONST_resId_yongHuXinXiBianJiShenHe,        },
	{	ID_qyCfgStandardName,	},											//  20060904
	{	-2,						},
	{	ID_qyImGrpList,					(  TCHAR  *  )CONST_resId_viewOwnedImGrpList,		},
	{	ID_qyPhoneMessengerList,		(  TCHAR  *  )CONST_resId_viewOwnedPhoneList,		},
	{	-2,						},	
	{	ID_cfgVisitor,	},
	{	-2,						},
	{	ID_qyAddTo,				},
	{	-2,						},
	{	ID_notSuperAdmin,		},
	{	ID_setAsSuperAdmin,		},
	{	-2,						},
	{	ID_qyAddPhone,						},
	{	ID_qyDelPhone,						},
#ifdef  __SUPPORT_customerService__
	{	-2,						},
	{	ID_cfgCustomerService,	},
#endif
#ifdef  __SUPPORT_wwwQm__
	{	-2,						},
	{	ID_wwwQmCfg,			},
#endif
	{	-2,						},
	{	ID_setPasswd,			},
	{	-2,						},
	{	ID_qyModifyMessengerId,	},
	{	-2,						},
	{	ID_qyDel,				},
	{	-2,						},
	{	ID_qyProperties,		},
	{	-1,					NULL,	},
};

  QY_DMITEM  CONST_popupMenuTable_viewMessengerAuthList_multiSel_isMgr[]  =
{
	{	ID_qyAddTo,					},
	{	-2,						},
	{	ID_qyDel,				},
	{	-1,				NULL,	},
};
#if  0
 QY_DMITEM  CONST_popupMenuTable_viewMessengerAuthList_isMgr_mini[]  =
{
	{	ID_qyEdit,						(  TCHAR  *  )CONST_resId_yongHuXinXiBianJiShenHe,        },
	{	ID_qyCfgStandardName,	},											//  20060904
	{	-2,						},
	{	ID_qyImGrpList,					(  TCHAR  *  )CONST_resId_viewOwnedImGrpList,		},
	{	-2,						},	
	{	ID_qyAddTo,				},
	{	-2,						},
	{	ID_setPasswd,			},
	{	-2,						},
	{	ID_qyModifyMessengerId,	},
	{	-2,						},
	{	ID_qyDel,				},
	{	-2,						},
	{	ID_qyProperties,		},
	{	-1,					NULL,	},
};
#endif
#if  0
  QY_DMITEM  CONST_popupMenuTable_viewMessengerList_isMgr[]  =
{
	{	ID_qyEdit,						(  TCHAR  *  )CONST_resId_yongHuXinXiBianJiShenHe,        },
	{	ID_qyCfgStandardName,	},											//  20060904
	{	-2,						},
	{	ID_qyImGrpList,					(  TCHAR  *  )CONST_resId_viewOwnedImGrpList,		},
	{	ID_qyPhoneMessengerList,		(  TCHAR  *  )CONST_resId_viewOwnedPhoneList,		},
	{	-2,						},
	{	ID_qyAddTo,				},
	{	-2,						},
	{	ID_cfgCustomerService,	},
	{	-2,						},
	{	ID_wwwQmCfg,			},
	{	-2,						},
	{	ID_qyModifyMessengerId,	},
	{	-2,						},
	{	ID_qyDel,				},
	{	-2,						},
	{	ID_qyProperties,		},
	{	-1,					NULL,	},
};


 QY_DMITEM  CONST_popupMenuTable_viewMessengerList_multiSel_isMgr[]  =
{
	{	ID_qyAddTo,					},
	{	-2,						},
	{	ID_qyDel,				},
	{	-1,				NULL,	},
};
#endif



 QY_DMITEM  CONST_popupMenuTable_viewMessengerList_multiSel_isClient[]  =
{
#ifdef  __SUPPORT_sm__
	{	ID_qySendSm,			},
#endif
	{	-1,				NULL,	},
};


  QY_DMITEM  CONST_popupMenuTable_viewMessengerNeedAuditedList_isMgr[]  =
{
	{	ID_qyProperties,		},
	{	-1,				NULL,	},
};


 QY_DMITEM  CONST_popupMenuTable_imAmList_isMgr[]  =
{
	{	ID_setPasswd,			},
	{	-2,						},
	{	ID_qyProperties,		},
	{	-1,				NULL,	},
};

 ///////////////

 QY_DMITEM  CONST_popupMenuTable_viewPhoneMessengerList_isMgr[]  =
{
	{	ID_qyEdit,		(  TCHAR  *  )CONST_resId_yongHuXinXiBianJiShenHe,        },
	{	-2,						},
	{	ID_qyImObjAuthList,		},
	{	ID_qyImGrpList,	(  TCHAR  *  )CONST_resId_viewOwnedImGrpList,		},		
	{	-2,						},
	{	ID_qyAddTo,				},
	{	-2,						},
	{	ID_qyDel,				},
	{	-2,						},
	{	ID_qyProperties,		},
	{	-1,				NULL,	},
};

 QY_DMITEM  CONST_popupMenuTable_viewPhoneMessengerList_multiSel_isMgr[]  =
{
	{	ID_qyDel,				},
	{	-1,						},
};


  QY_DMITEM  CONST_popupMenuTable_viewPhoneMessengerList_notSel_isMgr[]  =
{
#if  0		//  2011/10/05. 不再允许添加只有手机号的phoneMessenger	
	{	ID_qyAdd,				},
#endif
	{	-1,				NULL,	},
};


   extern QY_DMITEM  CONST_menuTable_chaKan_isCli_noMfc[];

   QY_DMITEM  CONST_popupMenuTable_mcuList[]  =
{
	{	ID_viewMcuStatus,		},
	//{	-3,		(TCHAR *)CONST_resId_view,	(TCHAR *)CONST_menuTable_chaKan_isCli_noMfc,},
	{	-1,				NULL,	},
};

     QY_DMITEM  CONST_popupMenuTable_mcu[]  =
{
	{	-3,		(TCHAR *)CONST_resId_menu_chaKan,	(TCHAR *)CONST_menuTable_chaKan_isCli_noMfc,},
	{	-1,				NULL,	},
};








 ////////


 QY_DMITEM  CONST_popupMenuTable_viewImGrpList_isMgr[]  =
{
	{	ID_qyImGrpMemList,			},
	{	-2,						},
	{	ID_qyEdit,		        },
	{	-2,						},
#if  0
	{	ID_cfgCustomerService,	},
	{	-2,						},
#endif
	{	ID_qyModifyMessengerId,	},
	{	-2,						},
	{	ID_qyDel,				},
	{	-2,						},
	{	ID_qyProperties,		},
	{	-1,				NULL,	},
};

#if  0
 QY_DMITEM  CONST_popupMenuTable_viewImGrpList_isClient[]  =
{
	{	ID_qyImGrpMemList,			},
	{	-2,						},
	{	ID_qyRule,				},
	{	-2,	},
	{	ID_qyProperties,		},
	{	-1,				NULL,	},
};
#endif

 //
 QY_DMITEM  CONST_popupMenuTable_viewImGrpMemList_isMgr[]  =
{
	{	ID_qyImGrpList,	(  TCHAR  *  )CONST_resId_viewOwnedImGrpList,		},
	{	-2,						},
	{	ID_qyAddTo,				},
	{	-2,						},
	{	ID_qyDel,		(  TCHAR  *  )CONST_resId_removeFrom,				},
	{	-2,						},
	{	ID_notMgr,	},
	{	ID_setAsMgr,	},
	{	-1,				NULL,	},
};


 //
 QY_DMITEM  CONST_popupMenuTable_viewImGrpMemList_multiSel_isMgr[]  =
{
	{	ID_qyAddTo,				},
	{	-2,						},
	{	ID_qyDel,		(  TCHAR  *  )CONST_resId_removeFrom,			},
	{	-1,				NULL,	},
};

  QY_DMITEM  CONST_popupMenuTable_viewImGrpMemList_isClient[]  =
{
	{	ID_qyProperties,		},
	{	-1,				NULL,	},
};



 QY_DMITEM  CONST_popupMenuTable_customerServiceList_isMgr[]  =
{
	{	ID_cfgCustomerService,		        },
	{	-2,						},
	{	ID_qyDel,				},
	{	-2,						},
	{	ID_qyProperties,		},
	{	-1,						},

};

 QY_DMITEM  CONST_popupMenuTable_wwwQmCfgList_isMgr[]  =
{
	{	ID_wwwQmCfg,		        },
	{	-2,						},
	{	ID_qyDel,				},
	{	-2,						},
	{	ID_qyProperties,		},
	{	-1,						},

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


 QY_DMITEM  CONST_popupMenuTable_sharedDynBmpList_isMgr[]  =
{
	{	ID_cfgVisitor,	},
	{	-1,				},
};

 QY_DMITEM  CONST_popupMenuTable_sharedDynBmpList_multiSel_isMgr[]  =
{
	{	ID_cfgVisitor,	},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_sharedDynBmpRuleList_isMgr[]  =
{
	{	ID_qyDel,		},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_viewImObjRuleList_isClient[]  =
{
	{	ID_qyRule,		},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_viewImTaskList_isMgr[]  =
{
	{	ID_qyProp_imTask,	},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_viewImTaskList_isClient[]  =
{
	{	ID_qyTalkToTaskPeer,	(  TCHAR  *  )ID_qyTalk,		},
	{	-2,				},
	{	ID_qyProp_imTask,	},
	{	-1,				},
};


#if  0
 QY_DMITEM  CONST_menuTable_conferenceWall[]  =
 {
	 {	ID_conferenceWall_open,				},
	 {	-2,									},
	 {	ID_vWall0,							},
	 {	-2,									},
	 {	ID_conferenceWall_new,				},
	 {	ID_conferenceWall_reset,				},
	 {	-1,					},
 };
#endif
 

 QY_DMITEM  CONST_popupMenuTable_commonList[]  =
{
	{	ID_qyEdit,		        },
	{	-2,						},
	{	ID_qyDel,				},
	{	-2,						},
	{	ID_qyProperties,		},
	{	-1,						},
};


  QY_DMITEM  CONST_menuTable_cfgAv_messenger[]  =
{
	{	ID_cfgRasOptions,	(  TCHAR  *  )CONST_resId_policy_isClient,			},
	//  {	ID_cfgVideoConference,	},
	{	-2,						},
#if  0
	{	ID_ucbNotAutoStopViewing,	},
	{	ID_ucbAutoStopViewing,		},
	{	-2,				},
	{	ID_ucbNotViewScreen,	},
	{	ID_ucbViewScreen,	},
	{	-2,				},
	{	ID_ucbNotViewWebcam0,	},
	{	ID_ucbViewWebcam0,	},
	{	-2,				},
	{	ID_ucbNotViewWebcam1,	},
	{	ID_ucbViewWebcam1,	},
	{	-2,				},
	{	ID_ucbNotViewWebcam2,	},
	{	ID_ucbViewWebcam2,	},
	{	-2,					},
#endif
	{	ID_ucbNotViewGps,	},
	{	ID_ucbViewGps,	},
	{	-2,				},
	{	ID_notShowGpsData,	},
	{	ID_showGpsData,		},
	{	-1,				},
};

 QY_DMITEM  CONST_menuTable_cfgAv_imGrp[]  =
{
	{	ID_cfgRasOptions,	(  TCHAR  *  )CONST_resId_policy_isClient,			},
	//  {	ID_cfgVideoConference,	},
	{	-2,						},
	{	ID_ucbHideImGrpMems,	},
	{	ID_ucbShowImGrpMems,	},
	{	-1,				},
};


 //  2007/10/04
 QY_DMITEM  CONST_menuTable_dlgTalk_messenger[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,			(  TCHAR  *  )CONST_menuTable_cfgAv_messenger,	},
	//  {	ID_fullScreen,			},
	{	-1,				},
};

 QY_DMITEM  CONST_menuTable_dlgTalk_imGrp[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,			(  TCHAR  *  )CONST_menuTable_cfgAv_imGrp,	},
	//  {	ID_fullScreen,			},

	{	-1,							},
};


  QY_DMITEM  CONST_menuTable_scrollBar_noFullScreen[]  =
{
	{	ID_stopScrollBar,		},
	{	ID_startScrollBar,		},
	{	-1,						},
};

 //  2008/11/06
 QY_DMITEM  CONST_menuTable_dlgRemoteAssist[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,				(  TCHAR  *  )CONST_menuTable_scrollBar_noFullScreen,	},
	{	-1,							},	
};

#if  0
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
 QY_DMITEM  CONST_menuTable_dlgVideos[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,				(  TCHAR  *  )CONST_menuTable_scrollBar_noFullScreen,	},
	{	ID_fullScreen,			},
	{	-1,							},	
};


 QY_DMITEM  CONST_menuTable_avCall_sharedWebcams[]  =
 {
	 {	-1,					},
 };

 QY_DMITEM  CONST_menuTable_dlgSharedWebcams[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_avCall,			(  TCHAR  *  )CONST_menuTable_avCall_sharedWebcams,	},
	{	-1,			},
};

 QY_DMITEM  CONST_menuTable_op_dlgVWall[]  =
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


 QY_DMITEM  CONST_menuTable_dlgVWall[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,			(  TCHAR  *  )CONST_menuTable_op_dlgVWall,	},
	{	ID_fullScreen,			},
	{	-1,			},
};

  QY_DMITEM  CONST_popupMenuTable_trayNotify[]  =
{
	{	ID_qyShowWnd,			},
	{	-2,							},
	{	ID_APP_ABOUT,				},
	{	-2,							},
	{	ID_qyQuitMainWnd,			},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_me[]  =
{
#ifdef  __SUPPORT_sm__
	{	ID_qySendSm,					},
	{	-2,								},
#endif
#if  0
	{	ID_qyUnprocedNewTaskList,		},
#endif
	{	ID_qyRealTimeTaskList,			},
#if  0
	{	-2,								},
	{	ID_qyNewTaskList,				},
	{	-2,		},
	{	ID_qyTaskHisList,				},
#endif
	{	-2,		},
	{	-3,			(  TCHAR  *  )CONST_resId_menu_xiaoXiChaKan,				(  TCHAR  *  )CONST_menuTable_xiaoXiChaKan_misClient,	},
	{	-2,		},
	{	ID_qyEdit,	(  TCHAR  *  )CONST_resId_yongHuXinXiBianJiShenHe,	},	//  "ÓÃ»§ÐÅÏ¢±à¼­ÉóºË(&B)",        
	{	-2,		},
	{	ID_qyProperties,			},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_messenger_isClient[]  =
{
	{	ID_qyTalk,					},
	{	-2,							},
#ifdef  __SUPPORT_sm__
	{	ID_qySendSm,			},
	{	-2,							},
#endif
	{	ID_qyRule,					},
#if	  0
	{	-2,							},
	{	ID_qyUnprocedNewTaskList,		},
	{	-2,		},
	{	ID_qyNewTaskList,				},
	{	-2,		},
	{	ID_qyTaskHisList,				},
#endif
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_xiaoXiChaKan,				(  TCHAR  *  )CONST_menuTable_xiaoXiChaKan_misClient,	},
	{	-2,		},
	{	ID_qyProperties,			},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_messenger_isMgr[]  =
{
	{	ID_qyDel,	},
	{	-2,							},
	{	ID_qyProperties,			},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_imGrp_isMgr[]  =
{
	{	ID_qyDel,					},
	{	-2,							},
	{	ID_qyProperties,			},
	{	-1,				},
};

 QY_DMITEM  CONST_popupMenuTable_instantAssistantMem[]  =
{
	{	ID_stopSpeaking,		},
	{	ID_requestToSpeak,		},
	{	-1,					},
};


 QY_DMITEM  *	CONST_popupMenuTable_mis  =	CONST_popupMenuTable_netMc;
