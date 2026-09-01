

#include	"stdafx.h"
#include	<tchar.h>

#include	"myresource_main_ts.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"isCmdConst.h"


///////////////////////
 QY_DMITEM  CONST_menuTable_avCall_messenger_ts[]  =
{
	//  {	ID_stopAvCall,		},
	{	ID_startAvCall,		},
	{	-2,					},
	{	ID_MENU_selectRtsp,		},
	{	-1,					},
};



 QY_DMITEM  CONST_menuTable_avCall_imGrp_ts[]  =
{
	//  {	ID_stopAvCall,		},
	{	ID_startAvCall,		},
	{	-2,					},
	{	ID_MENU_selectRtsp,		},
	{	-1,					},
};

 QY_DMITEM  CONST_menuTable_share_ts[]  =
{
	{	ID_stopShareScreen,			},
	{	ID_stopShareScreen,			},
	{	-2,							},
	{	ID_startShareFullScreen,	},
	{	-2,							},
 	{	ID_startShareMediaFile,		},
	{	-2,							},
	{	ID_startShareMediaDevice,	},
	{	ID_startShareMediaDevice_unresizable,	},

	//
	{	-2,	},
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

 QY_DMITEM  CONST_menuTable_op_messenger_ts[]  =
{
	{	ID_stopRemoteAssist,			},
	{	ID_startRemoteAssist,			},
	{	ID_startFullScreenRemoteAssist,	},
	{	-1,								},
};

QY_DMITEM  CONST_menuTable_op_ptz_messenger_ts[]  =
{
	{	ID_remotePtzControl,				},
	{	-1,								},
};

  QY_DMITEM  CONST_menuTable_cfgAv_messenger_ts[]  =
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

 QY_DMITEM  CONST_menuTable_cfgAv_imGrp_ts[]  =
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
	{	-2,	},
	{	ID_about,				},
	{	-1,				},
};



///////////////
   QY_DMITEM  CONST_menuTable_op_scrollBar_ts[]  =
 {
	{	ID_stopScrollBar,		},
	{	ID_startScrollBar,		},
	 {	-1,	},
 };



   /////////////////

  QY_DMITEM  CONST_popupMenuTable_trayNotify_ts[]  =
{
	{	ID_qyShowWnd,			},
	//  {	-2,							},
	//  {	ID_APP_ABOUT,				},
	//  {	-2,							},
	//  {	ID_qyQuitMainWnd,			},
	{	-1,				},
};

 QY_DMITEM  CONST_menuTable_dlgTalk_messenger_ts[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_avCall,			(  TCHAR  *  )CONST_menuTable_avCall_messenger_ts,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_share,			(  TCHAR  *  )CONST_menuTable_share_ts,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,				(  TCHAR  *  )CONST_menuTable_op_messenger_ts,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op_ptz,			(  TCHAR  *  )CONST_menuTable_op_ptz_messenger_ts,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,			(  TCHAR  *  )CONST_menuTable_cfgAv_messenger_ts,	},
	//  {	ID_fullScreen,			},
	{	-1,				},
};


 QY_DMITEM  CONST_menuTable_dlgTalk_imGrp_ts[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_avCall,			(  TCHAR  *  )CONST_menuTable_avCall_imGrp_ts,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_share,			(  TCHAR  *  )CONST_menuTable_share_ts,	},
	{	ID_2dVWall_new,				},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,			(  TCHAR  *  )CONST_menuTable_cfgAv_imGrp_ts,	},
	//  {	ID_fullScreen,			},

	{	-1,							},
};

  QY_DMITEM  CONST_menuTable_dlgTalk_imGrp_msg_ts[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,			(  TCHAR  *  )CONST_menuTable_cfgAv_imGrp_ts,	},

	{	-1,							},
};


   //  2008/11/06
 QY_DMITEM  CONST_menuTable_dlgVideos_ts[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,				(  TCHAR  *  )CONST_menuTable_op_scrollBar_ts,	},
	{	ID_fullScreen,			},
	{	-1,							},	
};


  #if  0  //  2013/02/06

 QY_DMITEM  CONST_menuTable_runningStatus_ts[]  =
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
	{	-2,							},
	{	ID_qList,					},
	{	-2,	},
	{	ID_myDbStatus,			},
	{	-2,							},
	{	ID_imTaskList_unproced_test,	},
	{	ID_imTaskList_cur_test,			},
	{	-1,		},
};


 QY_DMITEM  CONST_menuTable_dlgTest_ts[]  =
 {
#if  0
	 {	-3,		(  TCHAR  *  )CONST_resId_menu_op,							(  TCHAR  *  )CONST_menuTable_op_scrollBar_ts,	},
	{	-2,			},
#endif
	{	-3,		(  TCHAR  *  )CONST_resId_menu_runningStatus,				(  TCHAR  *  )CONST_menuTable_runningStatus_ts,	},
	 {	-1,							},
 };
#endif


 QY_DMITEM  CONST_popupMenuTable_mis_ts[]  =
{

	//
	{	CONST_resId_popup_trayNotify,										0,		(  TCHAR  *  )CONST_popupMenuTable_trayNotify_ts,							},
	//
	{	CONST_resId_menu_dlgTalk_messenger,									0,		(  TCHAR  *  )CONST_menuTable_dlgTalk_messenger_ts,						},
	{	CONST_resId_menu_dlgTalk_imGrp,										0,		(  TCHAR  *  )CONST_menuTable_dlgTalk_imGrp_ts,							},
	{	CONST_resId_menu_dlgTalk_imGrp_msg,									0,		(  TCHAR  *  )CONST_menuTable_dlgTalk_imGrp_msg_ts,							},
	{	CONST_resId_menu_dlgVideos,											0,		(  TCHAR  *  )CONST_menuTable_dlgVideos_ts,	},
	//
	//  {	CONST_resId_menu_dlgTest,											0,		(  TCHAR  *  )CONST_menuTable_dlgTest_ts,								},
	//
	{	-1,		NULL,		},
};


