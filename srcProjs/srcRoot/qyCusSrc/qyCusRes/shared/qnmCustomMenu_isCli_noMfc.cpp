

#include	"stdafx.h"
#include	<tchar.h>

#include	"myresource_main_isCli_noMfc.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"isCmdConst.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_is.h"

#if 10

 QY_DMITEM  CONST_menuTable_wenJian_isCli_noMfc[]  =	//  2006/12/17
{
#if  0
	{	ID_qyMgrSystems,		},
	{	-2,						},
	{	ID_qyCfgSystems,		},
	{	-2,						},
#endif
	{	ID_qySearch,			},
	//  {	ID_qyStat,				},
	{	-2,						},
	//  {	ID_qyImport,			},
	//  {	ID_qyExport,			},
	{	ID_qyClearUp,			},
	{	-2,						},
	//  {	ID_FILE_PRINT_SETUP,	},
	//  {	ID_FILE_PRINT,			},
	//  {	-2,						},
	//  {	ID_APP_EXIT,		},	//  2007/09/14, 因为OnClose(  )在客户端用来提供最小化，所以，需要用另一个菜单来使退出。
	{	ID_qyQuitMainWnd,		},
	{		-1,				},
};


 QY_DMITEM  CONST_menuTable_lianXiRenGuanLi_isCli_noMfc[]  =
{
#if  0
	{	ID_qyMessengerView,	},
	{	-2,					},
#endif
	{	ID_qyMessengerList,	},
	{	ID_qyPcUsrList,		},
	{	-2,					},
	{	ID_qyImGrpList,		},
	{	ID_qyImGrpMemList,	},
	//  {	-3,		(  TCHAR  *  )CONST_resId_menu_yongHuGuanLi,				(  TCHAR  *  )CONST_menuTable_yongHuGuanLi_netMc2,	},
	{	-2,					},
	{	ID_imObjRuleList,	},
	{	-1,		},
 };

  QY_DMITEM  CONST_menuTable_fenZuGuanLi_isCli_noMfc[]  =
{
	//  {	ID_qyNewImGrp,				},
	{	ID_qyImGrpList,				},
	{	ID_qyImGrpMemList,			},
	{	-1,		},
};


#ifdef  __SUPPORT_sm__
 QY_DMITEM  CONST_menuTable_phoneGuestGuanLi_isClient[]  =
{
	{	ID_qyPhoneGuestList,		},
	{	-1,		},
};
#endif


 QY_DMITEM  CONST_menuTable_share_isCli_noMfc[]  =
{
	{	ID_shareDynBmps,				},
	{	-1,		},
};

 QY_DMITEM  CONST_menuTable_3dWall_isCli_noMfc[]  =
{
	{	ID_3dVWall_console,			},
	//
	{	-2,		},
	{	ID_3dVWall_new,	},	
	{	-1,		},
};

 QY_DMITEM  CONST_menuTable_2dWall_isCli_noMfc[]  =
{
	{	ID_2dVWall_global,	},
	//
	{	ID_globalGpsVWall,	},
	{	ID_gpsVWall,	},
	{	-2,		},
	{	ID_2dVWall_new,	},
	//  {	ID_virtualWallList,	},
	{	-1,		},
};



#if  10  //  2013/02/06
 QY_DMITEM  CONST_menuTable_renWuChaKan_isCli_noMfc[]  =
{
	{	ID_imTaskList_unproced,		},
	{	-2,							},
	{	ID_imTaskList_cur,				},
	//  {	-2,		},
	//  {	ID_imTaskList_his,				},
	{	-1,		},
};
#endif

 QY_DMITEM  CONST_menuTable_xiaoXiChaKan_misClient[]  =
{
	{		ID_qyMsgToday,		0,		0,	},
	{		ID_qyMsgList,		0,		0,	},
	{		-1,				},
};

 QY_DMITEM  CONST_menuTable_shiJianChaKan_isCli_noMfc[]  =
{
	{		ID_qyEventAll,		0,		0,	},
#if  0
	{		-2,									},
	{		ID_qyOpEventAll,	0,		0,	},
#endif
	{		-1,				NULL,			},
};



 QY_DMITEM  CONST_menuTable_modulesGuanLi_isCli_noMfc[]  =
{
	{		ID_cliModule1,	},
	{		-1,				},
};


 QY_DMITEM  CONST_menuTable_subtitles_isCli_noMfc[]  =
 {
	 //{	ID_subtitle_localVideoInConf,		},
	 {	ID_subtitle_webcam,		},
	 {	-1,	},
 };

 QY_DMITEM  CONST_menuTable_guanLi_misClient[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_lianXiRenGuanLi,				(  TCHAR  *  )CONST_menuTable_lianXiRenGuanLi_isCli_noMfc,	},
	{	ID_createTmpGrp,	},
	{	-2,		},
	//{	-3,		(  TCHAR  *  )CONST_resId_menu_sharedResources,				(  TCHAR  *  )CONST_menuTable_sharedResources_isCli_noMfc,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_3dWall,						(  TCHAR  *  )CONST_menuTable_3dWall_isCli_noMfc,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_2dWall,						(  TCHAR  *  )CONST_menuTable_2dWall_isCli_noMfc,	},
	{	-2,		},
#ifdef  __SUPPORT_sm__
	{	-3,		(  TCHAR  *  )CONST_resId_menu_phoneGuest,					(  TCHAR  *  )CONST_menuTable_phoneGuestGuanLi_isClient,	},			
	{	ID_qyVerifiedPhoneList,		},
	{	-2,		},
#endif
	{	ID_viewOfflineRes,  },		
	{	-2,		},
	{	ID_playQvcf,	},	//  2015/05/15
#if  0
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_modulesGuanLi_isClient,		(  TCHAR  *  )CONST_menuTable_modulesGuanLi_isCli_noMfc,	},
#endif
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_subtitles,					(  TCHAR  *  )CONST_menuTable_subtitles_isCli_noMfc,				},
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_setLocalSharing,				(  TCHAR  *  )CONST_menuTable_share_isCli_noMfc,			},
	{	-2,		},
	{	ID_qyStartLocalVideo,			},
	{	ID_localPtzControl,				},
#if  0
	{	ID_chromaKeyCfg,				},
#endif
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_renWuChaKan,					(  TCHAR  *  )CONST_menuTable_renWuChaKan_isCli_noMfc,	},
	//  {	-3,		(  TCHAR  *  )CONST_resId_menu_xiaoXiChaKan,				(  TCHAR  *  )CONST_menuTable_xiaoXiChaKan_misClient,	},
	{	-2,		},
	//  {	-3,		(  TCHAR  *  )CONST_resId_menu_shiJianChaKan,				(  TCHAR  *  )CONST_menuTable_shiJianChaKan_isCli_noMfc,	},	
	//  {	ID_qySearch,			},		//  2014/04/19,联系人查询先不做了，要在菜单中先隐藏掉
	{	-2,		},
	{	ID_qyQuitMainWnd,		},
	{	-1,		NULL,			},

};


 //
 QY_DMITEM	CONST_menuTable_peiZhi_isCli_noMfc[]  =
{
	{	ID_cfgRasOptions,	(  TCHAR  *  )CONST_resId_policy_isClient,			},
	{	-2,							},
	{	ID_notPlayRemoteAudio,		},		//  2015/05/19
	{	ID_playRemoteAudio,			},		//  2015/05/19
	{	-2,							},
	{	ID_setPasswd,				},
	//  {	ID_CFGUSR					},
	{	-1,		NULL,		},
};
	
 QY_DMITEM  CONST_menuTable_onvif[] =
 {
	{   ID_notShowOnvifStatus,		},			//  2016/07/31
	{   ID_showOnvifStatus,			},			//  2016/07/31
	{	-2,							},
	{	ID_notPrintPtz,				},				//  2015/09/21
	{	ID_printPtz,				},
	{	-1,		NULL,		},
 };

 QY_DMITEM  CONST_menuTable_3dStatus[] =
 {
 	{	ID_notPrintD3d,				},				//  2014/11/27
	{	ID_printD3d,				},
	{	-2,	},
	{	ID_notPrintRtt,				},				//  2014/11/27
	{	ID_printRtt,				},
	{	-1,	},
 };

 //
 QY_DMITEM  CONST_menuTable_audioStatus[]  = 
 {
 	{	ID_notViewAudioStatus,	},
	{	ID_viewAudioStatus,		},
	{	-2,						},
	//
	{	ID_notPrintAudioMediaType,	},
	{	ID_printAudioMediaType,		},
	{	-2,						},
	{	ID_notShowAudioCapStatus,	},
	{	ID_showAudioCapStatus,		},


	{	-1,						},
};

 QY_DMITEM  CONST_menuTable_videoStatus[]  =  
 {
	{	ID_notViewVideoStatus,	},
	{	ID_viewVideoStatus,		},
	{	-2,						},

	{	ID_notShowVPktInputInfo,		},
	{	ID_showVPktInputInfo,		},
	{	-2,	},

	{	ID_notShowVideoCapStatus,	},				//  2012/11/11
	{	ID_showVideoCapStatus,		},
	{	-2,		},
	{	ID_notShowEncVStatus,		},				//  2014/06/23
	{	ID_showEncVStatus,			},				//  2014/06/23	


	{	-1,	},
};

 QY_DMITEM  CONST_menuTable_fileStatus[]  =  
 {
	{	ID_notViewFileStatus,	},
	{	ID_viewFileStatus,		},
	{	-1,	},
};


 QY_DMITEM  CONST_menuTable_ioStatus[]  =
 {
 	{	ID_notViewIoStatus,	},
	{	ID_viewIoStatus,		},
	{	-1,	},
 };

 QY_DMITEM  CONST_menuTable_mgrStatus[]  =
 {
	{	ID_notViewMgrStatus  },
	{	ID_viewMgrStatus  },
	{	-1,  },
 };

 //
 QY_DMITEM  CONST_menuTable_decStatus[]  =
 {
	{	ID_notShowDec_pipeStatus,		},
	{	ID_showDec_pipeStatus,		},
	{	-2,								},

 
	{	ID_notShowPreDecAStatus,		},			//  2015/09/11
	{	ID_showPreDecAStatus,			},			//  2015/09/11
	{	-2,		},
	//  {	ID_notShowPostDecAStatus,		},			//  
	//  {	ID_showPostDecAStatus,			},			//  
	//  {	-2,		},
 	{	ID_notShowPreDecV_pts,			},			//  2015/06/18
	{	ID_showPreDecV_pts,				},			//  2015/06/18
	{	-2,		},
	{	ID_notShowPreDecVStatus,		},			//  2014/06/29,2014/06/23
	{	ID_showPreDecVStatus,			},			//  2014/06/29,2014/06/23	
	{	-2,		},
	{	ID_notShowPostDecVStatus,		},			//  2014/06/29,2014/06/23
	{	ID_showPostDecVStatus,			},			//  2014/06/29,2014/06/23
	{	-2,								},
	{	ID_notShowDec_sharedTexStatus,		},	
	{	ID_showDec_sharedTexStatus,		},
	{	-1,								},			//  2015/06/18

 };

 QY_DMITEM  CONST_menuTable_playStatus[]  =
 {
 
	{	ID_notShowPlayAudioStatus,		},			//  2012/11/11
	{	ID_showPlayAudioStatus,			},
	{	-2,		},
	
	{	ID_notShowPreDrawStatus,		},
	{	ID_showPreDrawStatus,			},
	{	ID_notShowToDrawStatus,			},
	{	ID_showToDrawStatus,			}, 
	//
	{	ID_notShowRenderStatus,			},			//  2015/10/07
	{	ID_showRenderStatus,				},			//  2015/10/07

	 
	{	-1,								},			//  2015/06/18

 };

 //
 QY_DMITEM  CONST_menuTable_dlgTalkStatus[] =
 {
 	{	ID_notShowDlgTalkStatus,	},				//  2014/05/07
	{	ID_showDlgTalkStatus,	},					//  2014/05/07
	{	-1,	},
 };


 QY_DMITEM  CONST_menuTable_chaKan_isCli_noMfc[]  =
{
	//  {	ID_VIEW_TOOLBAR,		},		//  MENUITEM "工具栏(&T)",                  
	//  {	ID_VIEW_STATUS_BAR,		},		//  MENUITEM "状态栏(&S)",                  
	//  {	-2,						},		//  MENUITEM SEPARATOR
	{	ID_viewQnmStatus,		},		//  MENUITEM "系统状态窗(&Z)",    
	{	-2,						},

	{	-3,		(  TCHAR  *  )CONST_resId_menu_audioStatus,			(  TCHAR  *  )CONST_menuTable_audioStatus,	},		//  2015/06/18
	{	-3,		(  TCHAR  *  )CONST_resId_menu_videoStatus,			(  TCHAR  *  )CONST_menuTable_videoStatus,	},		//  2015/06/18
	{	-3,		(  TCHAR  *  )CONST_resId_menu_fileStatus,			(  TCHAR  *  )CONST_menuTable_fileStatus,	},		//  2015/06/18
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_ioStatus,			(  TCHAR  *  )CONST_menuTable_ioStatus,	},		//  2015/06/18
	{	-2,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_mgrStatus,			(  TCHAR  *  )CONST_menuTable_mgrStatus,	},		//  2015/06/18
	
	{	-2,						},		//  MENUITEM SEPARATOR

	{	-3,		(  TCHAR  *  )CONST_resId_menu_onvif,			(  TCHAR  *  )CONST_menuTable_onvif,  },			//  2016/07/31
	{	-2,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_3dStatus,			(  TCHAR  *  )CONST_menuTable_3dStatus,  },			//  2016/07/31

	{	-2,		},

	{	-3,		(  TCHAR  *  )CONST_resId_menu_decStatus,			(  TCHAR  *  )CONST_menuTable_decStatus,	},		//  2015/06/18

	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_playStatus,			(  TCHAR  *  )CONST_menuTable_playStatus,	},		//  2015/09/21
	{	-2,						},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_dlgTalkStatus,		(  TCHAR  *  )CONST_menuTable_dlgTalkStatus,	},		//  2015/09/21

	{	-2,		},
#if  0
	{	ID_notTestGps,	},
	{	ID_testGps,	},
	{	ID_notTestStream,	},
	{	ID_testStream,		},
	{	-2,						},
	{	ID_qyRefresh,			},		//  MENUITEM "刷新(&R)  F5",     
	//
#ifdef  _DEBUG
	{	-2,						},
	{	ID_qyTest,				},
#endif
	//
#endif
	{	-1,		NULL,			},
};


 //
 QY_DMITEM  CONST_menuTable_bangZhu_noMfc[]  =
 {
	{	ID_HELP,				},
	{	-2,						},
	{	ID_about,				},
	{	-1,		NULL,			},
 };


 QY_DMITEM  CONST_mainMenuTable_isCli_noMfc[]  =
{
	//  {	-3,		(  TCHAR  *  )CONST_resId_menu_wenJian,		(  TCHAR  *  )CONST_menuTable_wenJian_isCli_noMfc,			},	//  2006/12/17
	{	-3,		(  TCHAR  *  )CONST_resId_menu_guanLi,		(  TCHAR  *  )CONST_menuTable_guanLi_misClient,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,		(  TCHAR  *  )CONST_menuTable_peiZhi_isCli_noMfc,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chaKan,		(  TCHAR  *  )CONST_menuTable_chaKan_isCli_noMfc,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_bangZhu,		(  TCHAR  *  )CONST_menuTable_bangZhu_noMfc,	},	
	{	-1,		NULL,			},
 };
//

 
 QY_DMITEM  CONST_childFrmMenuTable_isCli_noMfc[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_wenJian,		(  TCHAR  *  )CONST_menuTable_wenJian,			},	//  2006/12/17
	{	-3,		(  TCHAR  *  )CONST_resId_menu_guanLi,		(  TCHAR  *  )CONST_menuTable_guanLi_misClient,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,		(  TCHAR  *  )CONST_menuTable_peiZhi_isCli_noMfc,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chaKan,		(  TCHAR  *  )CONST_menuTable_chaKan_isCli_noMfc,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chuangKou,	(  TCHAR  *  )CONST_menuTable_chuangKou,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_bangZhu,		(  TCHAR  *  )CONST_menuTable_bangZhu,	},	
	{	-1,		NULL,		},
};
#endif
/////////////////////////////////////////////////////  2010/04/14, winCe
#ifdef  __WINCE__
QY_DMITEM  CONST_menuTable_winCeMain[]  =
{
	//  {	ID_retrieveAll,	},
	{	IDCANCEL,	},
	{	-1,		},
};

  QY_DMITEM  CONST_winCeMenuTable_misClient[]  =
{
	{	CONST_resId_popup0,													0,		(  TCHAR  *  )CONST_popupMenuTable_0,			},									//  -0
	{	CONST_resId_menu_winCeMain,											0,		(  TCHAR  *  )CONST_menuTable_winCeMain,		},
	{	-1,														}
 };

#endif

///////////////////////////////////  }

 QY_DMITEM  CONST_cusMenusTable_isCli_noMfc[]  =
{
	{	CONST_resId_mainMenu,				(  TCHAR  *  )CONST_mainMenuTable_isCli_noMfc,			},
	//{	CONST_resId_mainMenu_mini,			(  TCHAR  *  )CONST_mainMenuTable_isCli_mini,			},
	{	CONST_resId_childFrmMenu,			(  TCHAR  *  )CONST_childFrmMenuTable_isCli_noMfc,		},
	{	CONST_resId_popupMenu,				(  TCHAR  *  )CONST_popupMenuTable_isCli,					},
	//  {	CONST_resId_winceMenu,				(  TCHAR  *  )CONST_winCeMenuTable_misClient,			},			//  2010/04/13
	{	-1,		NULL,		},
};


  QY_DMITEM  CONST_queryTypeTable_isClient[]  =
{
	{	CONST_qyQueryType_imObjList,				CONST_str_imObjSearch,			},
#if 0
	{	CONST_qyQueryType_imMsgList,				CONST_str_imMsgChaXun,		},
	{	CONST_qyQueryType_opEventList,				CONST_str_xiTongShiJianChaXun,			},		//  2006/02/25
#endif
	{	-1,											NULL,					},
};

  //  2008/12/29
 QY_DMITEM  CONST_imTaskTypeTable[]  =
{
	{	CONST_imTaskType_sendFile,					CONST_str_sendFile,						},
	{	CONST_imTaskType_recvFile,					CONST_str_recvFile,						},
	//
	{	CONST_imTaskType_transferAvInfo,			CONST_str_av,							},
	{	CONST_imTaskType_shareScreen,				CONST_str_shareScreen,					},
	{	CONST_imTaskType_remoteAssist,				CONST_str_remoteAssist,					},
	{	CONST_imTaskType_shareMediaFile,			CONST_str_shareMediaFile,		},
	{	CONST_imTaskType_shareDynBmp,				CONST_str_shareDynBmp,			},
	{	CONST_imTaskType_viewDynBmp,				CONST_str_viewDynBmp,			},
	{	CONST_imTaskType_queryCustomerServiceOfficer,CONST_str_queryCustomerServiceOfficer,	},
	//
	{	CONST_imTaskType_shareGps,					CONST_str_shareGps,				},
	{	CONST_imTaskType_viewGps,					CONST_str_viewGps,				},

	//
	{	-1,											},
};

 //  2010/09/08
 QY_DMITEM	CONST_ruleCmdTable_autoAnswer[]  =
{
	{	CONST_ruleCmd_null,									_T(  ""  ),	},
	{	CONST_ruleCmd_permit,								CONST_str_permit,	},
	//  {	CONST_ruleCmd_permitAndFullscreen,					CONST_str_permitAndFullscreen,	},
	{	CONST_ruleCmd_manual,								CONST_str_manual,	},
	{	-1,			},
};
 //  2016/02/15
 QY_DMITEM	CONST_ruleCmdTable_autoAnswer_av[]  =
{
	//  {	CONST_ruleCmd_null,									CONST_str_permitted,	},
	{	CONST_ruleCmd_permit,								CONST_str_permit,	},
	{	CONST_ruleCmd_manual,								CONST_str_manual,	},
	{	-1,			},
};

#if 0 
 QY_DMITEM	CONST_remoteVideoTable[]  =
{
	{	CONST_resId_selectScreen,	CONST_IDC_STATIC00,	},
	{	CONST_resId_selectWebcam0,	CONST_IDC_STATIC10,	},
	{	CONST_resId_selectWebcam1,	CONST_IDC_STATIC11,	},
	{	CONST_resId_selectWebcam2,	CONST_IDC_STATIC12,	},
	{	-1,			},
};
#endif


 //  2009/01/01
 QY_DMITEM  CONST_qyStatusTable[]  =
{
	{	CONST_qyStatus_ok,										_T(  "OK"  ),						},
	//	
	{	CONST_qyStatus_del,										_T(  "Del"  ),						},
	{	CONST_qyStatus_update,									_T(  "Update"  ),					},
	//
	{	CONST_qyStatus_err,										_T(  "Error"  ),					},		//  这里是-1，所以Error显示不了了
	//
	{	CONST_imTaskStatus_req,									CONST_str_qingqiu,					},		//  2007/10/07
	{	CONST_imTaskStatus_resp,								CONST_str_xiangYing,				},
	//
	{	CONST_imTaskStatus_applyToSend,							CONST_str_reqToSend,				},
	{	CONST_imTaskStatus_waitToSend,							CONST_str_waitToSend,				},
	{	CONST_imTaskStatus_applyToRecv,							CONST_str_reqToRecv,				},
	{	CONST_imTaskStatus_waitToRecv,							CONST_str_waitToRecv,				},
    //
	{	CONST_imTaskStatus_sending,								CONST_str_sending,					},
	{	CONST_imTaskStatus_receiving,							CONST_str_receiving,				},
	//
	{	CONST_imTaskStatus_sendBreak,							CONST_str_sendBreak,				},
	{	CONST_imTaskStatus_recvBreak,							CONST_str_recvBreak,				},
	//
	{	CONST_imTaskStatus_recvFinished,						CONST_str_finished,					},
	{	CONST_imTaskStatus_sendFinished,						CONST_str_finished,					},
	//
	{	CONST_imTaskStatus_acceptedByReceiver,					CONST_str_acceptedByReceiver,		},
	{	CONST_imTaskStatus_dualByReceiver,						CONST_str_dualByReceiver,		},
	//
	{	CONST_imTaskStatus_err_missingOrgReq,					CONST_str_err_missingOrgReq,		},
    //
	{	CONST_imTaskStatus_canceledBySender,					CONST_str_canceledBySender,			},
	{	CONST_imTaskStatus_canceledByReceiver,					CONST_str_canceledByReceiver,		},
	{	CONST_imTaskStatus_deniedByReceiver,					CONST_str_deniedByReceiver,			},
	{	CONST_imTaskStatus_autoCanceledByReceiver,				_T("autoCanceledByReceiver"),		},
	//
	//
	{	-1,																		},
};
 
#if  0
 QY_DMITEM  CONST_usLayoutTypeTable_dialog[]  =
{
	{		CONST_usLayoutType_null,							_T(  ""  ),					},
	{		CONST_usLayoutType_dialog,							CONST_str_dialog,			},
	{		-1,						},
};
#endif


  QY_DMITEM  CONST_tableTable_isCli_noMfc[]  =
{
	{ 	CONST_resId_qnmEventTypeTable0,			(  TCHAR  *  )CONST_qnmEventTypeTable0_is,		},
	{	CONST_resId_qnmEventTypeTable_pc,		(  TCHAR  *  )CONST_qnmEventTypeTable_assetMgr,		},
	{	CONST_resId_qnmEventTypeTable_op,		(  TCHAR  *  )CONST_qnmEventTypeTable_op_is,		},
	{	CONST_resId_ipScanOfficeLevelTable,		(  TCHAR  *  )CONST_ipScanOfficeLevelTable,	},
	{	CONST_resId_zjgaYhlxTable,				(  TCHAR  *  )CONST_zjgaYhlxTable,			},
	{	CONST_resId_gYhGrpTable,				(  TCHAR  *  )gYhGrpTable,					},
	{	CONST_resId_gEventYhGrpTable,			(  TCHAR  *  )gEventYhGrpTable,				},
	//  {	CONST_resId_qnmEventTypeTable_secChk,	(  TCHAR  *  )CONST_qnmEventTypeTable_secChk,	},
	{	CONST_resId_qyNullTable,				(  TCHAR  *  )CONST_nullTable,				},
	{	CONST_resId_jqlxTable,					(  TCHAR  *  )CONST_jqlxTable,					},
	{	CONST_resId_qySystemIdTable,			(  TCHAR  *  )CONST_qySystemIdTable,				},
	{	CONST_resId_ucbDsnlessTable,			(  TCHAR  *  )CONST_ucbDsnlessTable,				},
	{	CONST_resId_myCONST_yhGrpTable_netMc,	(  TCHAR  *  )myCONST_yhGrpTable_netMc,				},
	{	CONST_resId_myCONST_eventYhGrpTable_netMc,(  TCHAR  *  )myCONST_eventYhGrpTable_netMc,		},
	{	CONST_resId_myCONST_yhGrpTable_is,		(  TCHAR  *  )myCONST_yhGrpTable_is,				},
	{	CONST_resId_myCONST_eventYhGrpTable_is,	(  TCHAR  *  )myCONST_eventYhGrpTable_is,			},
	//
	{	CONST_resId_objTypeTable,				(  TCHAR  *  )CONST_objTypeTable,					},
	//
	{	CONST_resId_imGrpSubtypeTable,			(  TCHAR  *  )CONST_imGrpSubtypeTable,				},
	//
	{	CONST_resId_queryTypeTable,				(  TCHAR  *  )CONST_queryTypeTable_isClient,		},
	{	CONST_resId_fieldIdTable,				(  TCHAR  *  )CONST_fieldIdTable,					},
	//
	{	CONST_resId_imTaskTypeTable,			(  TCHAR  *  )CONST_imTaskTypeTable,	},
	{	CONST_resId_qyStatusTable,				(  TCHAR  *  )CONST_qyStatusTable,					},
	{	CONST_resId_imTaskStatusTable,				(  TCHAR  *  )CONST_imTaskStatusTable,				},
	//  2009/01/01
	{	CONST_resId_qyCommTypeTable,			(  TCHAR  *  )CONST_qyCommTypeTable,				},
	{	CONST_resId_pcCommTypeTable,			(  TCHAR  *  )CONST_pcCommTypeTable,				},
	{	CONST_resId_grpNameTable,				(  TCHAR  *  )CONST_grpNameTable,					},
	{	CONST_resId_usRunningStatusTable,		(  TCHAR  *  )CONST_usRunningStatusTable,			},

	//
	{	CONST_resId_ruleTypeTable,				(  TCHAR  *  )CONST_ruleTypeTable_is,				},
	{	CONST_resId_usLayoutTypeTable,			(  TCHAR  *  )CONST_usLayoutTypeTable,				},
	{	CONST_resId_usLayoutTypeTable_resource,	(  TCHAR  *  )CONST_usLayoutTypeTable_resource,		},
	{	CONST_resId_ruleCmdTable,				(  TCHAR  *  )CONST_ruleCmdTable,					},
	{	CONST_resId_ruleCmdTable_autoAnswer,	(  TCHAR  *  )CONST_ruleCmdTable_autoAnswer,		},
	{	CONST_resId_ruleCmdTable_autoAnswer_av,	(  TCHAR  *  )CONST_ruleCmdTable_autoAnswer_av,		},

	//  {	CONST_resId_remoteVideoTable,			(  TCHAR  *  )CONST_remoteVideoTable,				},

	//
	//  {	CONST_resId_menu_conferenceWall,				(  TCHAR  *  )CONST_menuTable_conferenceWall,		},
#if  0
	{	CONST_resId_menu_shareFullScreen,		(  TCHAR  *  )CONST_table_shareFullScreen,					},
	{	CONST_resId_menu_startShareMediaFile,	(  TCHAR  *  )CONST_table_startShareMediaFile,				},
	{	CONST_resId_menu_startShareMediaDevice,	(  TCHAR  *  )CONST_table_startShareMediaDevice,			},
#endif

	//
	{	CONST_resId_policyAvLevelTable_basic,				(  TCHAR  *  )CONST_policyAvLevelTable_basic,		},
	{	CONST_resId_policyAvLevelTable_standard,			(  TCHAR  *  )CONST_policyAvLevelTable_standard,	},
	{	CONST_resId_policyAvLevelTable_high,				(  TCHAR  *  )CONST_policyAvLevelTable_high,		},
	{	CONST_resId_policyAvLevelTable_mosaic_video,		(  TCHAR  *  )CONST_policyAvLevelTable_mosaic_video,},
	{	CONST_resId_policyAvLevelTable_mosaic_resource,		(  TCHAR  *  )CONST_policyAvLevelTable_mosaic_resource,},
	//  2016/04/06
	{	CONST_resId_policyAvLevelTable_slave_video,			(  TCHAR  *  )CONST_policyAvLevelTable_slave_video,},
	//
	{	CONST_resId_iTargetUsageTable,						(  TCHAR  *  )CONST_iTargetUsageTable,				},
	//{	CONST_resId_iAvgBitrateTable,						(  TCHAR  *  )CONST_iAvgBitrateTable,				},	

	{	-1,		NULL,		},
};


 QY_DMITEM  CONST_cusResTable_isCli_noMfc[]  =
{
 	{	CONST_resType_str,						(  TCHAR  *  )CONST_strTable_isCli_noMfc,						},
	{	CONST_resType_table,					(  TCHAR  *  )CONST_tableTable_isCli_noMfc,			},
	{	CONST_resType_dlg,						(  TCHAR  *  )CONST_dlgTable_isCli,						},
 	{	CONST_resType_menu,						(  TCHAR  *  )CONST_cusMenusTable_isCli_noMfc,				},
	{	CONST_resType_query,					(  TCHAR  *  )CONST_queryTable_mis,						},
	{	CONST_resType_search,					(  TCHAR  *  )CONST_searchTable,						},
	{	CONST_resType_columnInfo,				(  TCHAR  *  )CONST_columnInfoTable,				},
	{	-1,		NULL,		},
};



