

#include	"stdafx.h"
#include	<tchar.h>

#include	"myresource_qmdCliHelp.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"

#include	"isCmdConst.h"
#include	"qmStr.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_is.h"


 QY_DMITEM  CONST_strTable_qmdCliHelp[]  =
{
	{	CONST_resId_null,					_T(  ""  ),				},
	//
	{	CONST_resId_IDD_ABOUTBOX,					CONST_IDD_ABOUTBOX,	},
		{	CONST_resId_ver,							CONST_ID_ver,	},
		{	CONST_resId_qycxCopyRight,					CONST_ID_qycxCopyRight,	},

		{	IDC_ADD,									CONST_str_Add,							},
		{	IDC_DEL,									CONST_str_Del,							},
		{	CONST_resId_play,							CONST_IDC_BUTTON_PLAY,	},
		{	CONST_resId_pause,							CONST_str_pause,		},
		{	IDCANCEL,									CONST_str_CANCEL,					},		
	//  CONST_dlg_messageBox
			{	CONST_resId_menu_xiaoXiChaKan,			CONST_ID_menu_xiaoXiChaKan,	},
			{	ID_qyMsgToday,							CONST_ID_qyMsgToday,	},
			{	ID_qyMsgList,							CONST_ID_qyMsgList,		},
			{	CONST_resId_logMsg,						CONST_str_logMsg,		},
			{	CONST_resId_saveMsgAsTextInDir,			CONST_str_saveMsgAsTextInDir,	},
			{	CONST_resId_saveMsgAsText,				CONST_str_saveMsgAsText,	},


		{	CONST_resId_fullScreenSharing,				CONST_IDC_STATIC_sharingScreen0,	},

		{	CONST_resId_running,						CONST_str_running,					},
		{	CONST_resId_started,						CONST_str_started,					},
		{	CONST_resId_manuallyStarted,				CONST_str_manuallyStarted,					},

		{	CONST_resId_start,							CONST_str_start,					},
		{	CONST_resId_stop,							CONST_str_stop,						},

		{	CONST_resId_importFile,						CONST_str_importFile,			},
		{	CONST_resId_hideList,						CONST_str_hideList,				},
		{	CONST_resId_utf8,							CONST_str_utf8,					},
		{	CONST_resId_conferencingSubtitles,			CONST_str_conferencingSubtitles,},
		{	CONST_resId_screensharingSubtitles,			CONST_str_screensharingSubtitles,},
		{	CONST_resId_webcamSharingSubtitles,			CONST_str_webcamSharingSubtitles,},
		{	CONST_resId_shadow,							CONST_str_shadow,				},
		{	CONST_resId_note,							CONST_str_note,					},
	//
	{	CONST_resId_seqNo,					CONST_str_xuHao,		},
	//
	{	CONST_resId_idStr,					CONST_str_idStr,		},
	{	CONST_resId_idStr_grp,				CONST_str_idStr_grp,	},
	//
	{	CONST_resId_imGrps_av,				CONST_str_imGrps_av,						},
	{	CONST_resId_imGrps_msg,				CONST_str_imGrps_msg,						},
	//
	{	CONST_resId_logon_wndTitle,			CONST_str_nm_logon,		},
	{	CONST_resId_logon_staticUsrName,	CONST_str_yongHuMing,	},
	{	CONST_resId_logon_staticPasswd,		CONST_str_password,		},
	//
	{	CONST_resId_y,						CONST_str_yes,			},		
	{	CONST_resId_n,						CONST_str_no,			},		
	{	IDOK,								CONST_str_OK,			},		
	{	IDCANCEL,							CONST_str_CANCEL,		},		

	//
	{	CONST_resId_leiXing,				CONST_str_leiXing,			},
	{	CONST_resId_likeSearch,				CONST_str_likeSearch,		},
	{	CONST_resId_mingChen,				CONST_str_mingChen,			},
	{	CONST_resId_idStr_related,			CONST_str_idStr_related,	},	//  2011/11/17
	//

	//  ÒÔÏÂÊÇ¹¤¾ßÀ¸
	{	ID_qyRefresh,						CONST_ID_Refresh,			CONST_str_Refresh,	},
	{	ID_APP_ABOUT,						CONST_str_ID_APP_ABOUT,		CONST_str_ID_APP_ABOUT_status,	},
	{	ID_about,							CONST_str_ID_APP_ABOUT,		CONST_str_ID_APP_ABOUT_status,	},

	{	ID_qyShowWnd,					CONST_ID_qyShowMainWnd,		CONST_str_qyShowMainWnd,	},
	{	ID_qyQuitMainWnd,					CONST_ID_qyQuitMainWnd,		CONST_str_qyQuitMainWnd,	},



	//  ÒÔÏÂÊÇÏÂÀ­ÆÕÍ¨²Ëµ¥
	{	CONST_resId_menu_wenJian,					CONST_ID_FILE,			},
	//
	{	CONST_resId_menu_guanLi,					CONST_ID_menu_guanLi,		},
		{	CONST_resId_menu_lianXiRenGuanLi,			CONST_ID_menu_lianXiRenGuanLi,			},
			{	ID_qyMessengerList,							CONST_ID_qyMessengerList,	},
		{	CONST_resId_menu_fenZuGuanLi,				CONST_ID_menu_fenZuGuanLi,			},
			{	ID_qyImGrpList,								CONST_ID_qyImGrpList,  },
			{	CONST_resId_viewOwnedImGrpList,				CONST_ID_viewOwnedImGrpList,	},

		{	ID_activeImObjList,							CONST_ID_activeImObjList,	},
		
		{	CONST_resId_menu_customerService,			CONST_ID_menu_customerService,	},
		{	CONST_resId_menu_wwwQm,						CONST_ID_menu_wwwQm,	},

		{	CONST_resId_menu_sharedResources,			CONST_ID_menu_sharedResources,	},
			{	ID_shareDynBmps,							CONST_ID_shareDynBmps,	},
			{	ID_retrieveAll,								CONST_ID_retrieveAll,	},
		{	CONST_resId_menu_phoneGuest,				CONST_ID_menu_phoneGuest,	},
		{	CONST_resId_menu_modulesGuanLi_isMgr,		CONST_ID_menu_modulesGuanLi,	},
		{	CONST_resId_menu_modulesGuanLi_isClient,	CONST_ID_menu_modulesGuanLi,	},
#if 10
		{	CONST_resId_menu_subtitles,					CONST_ID_menu_subtitles,		},
			//{	ID_subtitle_localVideoInConf,				CONST_ID_subtitle_localVideoInConf,	},
			{	ID_subtitle_webcam,							CONST_ID_subtitle_webcam,		},
#endif

		{	ID_playQvcf,									CONST_ID_playQvcf,				},

		{	ID_qyStartLocalVideo,							CONST_ID_qyStartLocalVideo,			},
		{	ID_localPtzControl,								CONST_ID_localPtzControl,			},
		//

		{	ID_chromaKeyCfg,								CONST_ID_chromaKeyCfg,					},

		//
			{	ID_sharedDynBmpList,							CONST_ID_sharedDynBmpList,		},

		{	CONST_resId_menu_setLocalSharing,				CONST_ID_menu_setLocalSharing,	},

		{	CONST_resId_menu_renWuChaKan,				CONST_ID_menu_renWuChaKan,	},
			{	ID_imTaskList_unproced,						CONST_ID_imTaskList_unproced,		},
			{	ID_imTaskList_cur,							CONST_ID_imTaskList_cur,			},
			{	ID_imTaskList_his,							CONST_ID_imTaskList_his,			},
#if  0
			{	ID_qyRealTimeTaskList,						CONST_ID_qyRealTimeTaskList,	},
			{	ID_taskInfoList,							CONST_ID_taskInfoList,			},
			{	ID_sharingObjectList,						CONST_ID_sharingObjectList,		},
			{	ID_playerList,								CONST_ID_playerList,		},
			{	ID_wallList,								CONST_ID_wallList,			},
			{	ID_imNetStatList,							CONST_ID_imNetStatList,			},
			{	ID_talkerList,								CONST_ID_talkerList,			},
			{	ID_messengerStatusList,						CONST_ID_messengerStatusList,	},
			{	ID_qList,									CONST_ID_qList,					},
			{	ID_myDbStatus,								CONST_ID_myDbStatus,			},
			{	ID_imTaskList_unproced_test,				CONST_ID_imTaskList_unproced,	},
			{	ID_imTaskList_cur_test,						CONST_ID_imTaskList_cur,	},
#endif
			{	CONST_resId_title,							CONST_str_title,			},
		{	CONST_resId_menu_xiaoXiChaKan,			CONST_ID_menu_xiaoXiChaKan,	},
			{	ID_qyMsgToday,							CONST_ID_qyMsgToday,	},
			{	ID_qyMsgList,							CONST_ID_qyMsgList,		},
		{	CONST_resId_menu_yongHuGuanLi,			CONST_ID_menu_yongHuGuanLi,			         },
			{	ID_qyPcUsrList,							CONST_ID_qyPcUsrList,			CONST_str_qyPcUsrList,         },		
			{	ID_qyPcUsrInTab1List,					CONST_ID_qyPcUsrInTab1List,                },		
		{	CONST_resId_menu_keHuDuanGuanLi,		CONST_ID_menu_keHuDuanGuanLi,			         },
			{	ID_qwmSvrList,							CONST_ID_qwmSvrList,			CONST_str_qwmSvrList,         },	
			{	ID_imObjRuleList,						CONST_ID_imObjRuleList,		CONST_str_imObjRuleList		},
		{	CONST_resId_imObjRuleList,		CONST_str_imObjRuleList,  },
		{	CONST_resId_menu_shiJianChaKan,			CONST_ID_menu_shiJianChaKan,															     },
			{	ID_qyEventAll,						CONST_ID_qyEventAll,							CONST_str_qyEventAll,         },					
			{	ID_qyOpEventAll,					CONST_ID_qyOpEventAll,							CONST_str_qyOpEventAll,         },							
		{	CONST_resId_menu_chaXun,				CONST_ID_Search,			         },
	{	 ID_qySearch,								CONST_ID_Search,								CONST_str_Search,          },		//  20130730,增加这行后,才补上查询
	{	ID_qyClearUp,								CONST_ID_Clear,			CONST_str_Clear,        },

	{	ID_FILE_PRINT_SETUP,						CONST_ID_PRINT_SETUP,	CONST_str_PRINT_SETUP,     },
	{	ID_FILE_PRINT,								CONST_ID_PRINT,			CONST_str_PRINT,   },
	{	ID_APP_EXIT,								CONST_ID_APP_EXIT,		CONST_str_APP_EXIT,     },
	//	{	CONST_resId_menu_yonghuGuanLi,			CONST_ID_menu_yongHuGuanLi,				},
	{	CONST_resId_menu_peiZhi,			CONST_ID_menu_peiZhi,					},
		{	ID_cfgRasOptions,					CONST_ID_cfgRasOptions,			CONST_str_cfgRasOptions,      },
		{	ID_cfgOptions,						CONST_ID_cfgOptions,      },
		{	ID_notPlayRemoteAudio,				CONST_ID_notPlayRemoteAudio,		},		//  2015/05/19
		{	ID_playRemoteAudio,					CONST_ID_playRemoteAudio,			},		//  2015/05/19
	{	CONST_resId_menu_chaKan,			CONST_ID_menu_chaKan,					},
		{	ID_VIEW_TOOLBAR,					CONST_ID_VIEW_TOOLBAR,					},
		{	ID_VIEW_STATUS_BAR,					CONST_ID_VIEW_STATUS_BAR,					},

		{	ID_viewQnmStatus,					CONST_ID_viewQnmStaus,				},
		{	ID_viewDaemonStatus0,				CONST_ID_viewDaemonStatus0,			},
		{	ID_viewDaemonStatus1,				CONST_ID_viewDaemonStatus1,			},
		{	ID_viewDaemonStatus2,				CONST_ID_viewDaemonStatus2,			},

		{	ID_notViewAudioStatus,				CONST_ID_notViewAudioStatus,		},
		{	ID_viewAudioStatus,					CONST_ID_viewAudioStatus,		},
		{	ID_notViewVideoStatus,				CONST_ID_notViewVideoStatus,		},
		{	ID_viewVideoStatus,					CONST_ID_viewVideoStatus,		},
		{	ID_notViewIoStatus,					CONST_ID_notViewIoStatus,		},
		{	ID_viewIoStatus,					CONST_ID_viewIoStatus,		},
#if  0
		{	ID_useDSound,						CONST_ID_useDSound,	},
		{	ID_useAudioCap,						CONST_ID_useAudioCap,	},
#endif
		{	ID_notPrintAudioMediaType,			CONST_ID_notPrintAudioMediaType,			},			//  2013/03/21
		{	ID_printAudioMediaType,				CONST_ID_printAudioMediaType,			},

		{	ID_notShowVideoCapStatus,			CONST_ID_notShowVideoCapStatus,			},				//  2012/11/11
		{	ID_showVideoCapStatus,				CONST_ID_showVideoCapStatus,			},
		{	ID_notShowAudioCapStatus,			CONST_ID_notShowAudioCapStatus,			},
		{	ID_showAudioCapStatus,				CONST_ID_showAudioCapStatus,			},
#if 0
		{	ID_notShowPreDrawStatus,			CONST_ID_notShowPreDrawStatus,				},
		{	ID_showPreDrawStatus,				CONST_ID_showPreDrawStatus,				},
		{	ID_notShowToDrawStatus,				CONST_ID_notShowToDrawStatus,				},
		{	ID_showToDrawStatus,				CONST_ID_showToDrawStatus,				},
		{	ID_notShowPlayAudioStatus,			CONST_ID_notShowPlayAudioStatus,		},				//  2012/11/11
		{	ID_showPlayAudioStatus,				CONST_ID_showPlayAudioStatus,			},
#endif
		{	ID_notShowDlgTalkStatus,			CONST_ID_notShowDlgTalkStatus,			},				//  2014/05/07
		{	ID_showDlgTalkStatus,				CONST_ID_showDlgTalkStatus,			},				//  2014/05/07

#if  0
		{	ID_notShowPktInputInfo,				CONST_ID_notShowPktInputInfo,			},
		{	ID_showPktInputInfo,				CONST_ID_showPktInputInfo,			},
#endif
		{	ID_notPrintRtt,						CONST_ID_notPrintRtt,			},
		{	ID_printRtt,						CONST_ID_printRtt,			},
#if 0
		{	ID_notPrintD3d,						CONST_ID_notPrintD3d,			},					//  2014/12/09
		{	ID_printD3d,						CONST_ID_printD3d,			},						//  2014/12/09
#endif

		{	ID_notShowEncVStatus,				CONST_ID_notShowEncVStatus,			},
		{	ID_showEncVStatus,					CONST_ID_showEncVStatus,			},
		//
		{	CONST_resId_menu_decStatus,			_T(  "Dec"  ),		},		//  2015/06/18
#if 0
			{	ID_notShowPreDecV_pts,			_T(  "Not show pts info"  ),		},
			{	ID_showPreDecV_pts,				_T(  "Show pts info"  ),			},
			{   ID_notShowPreDecAStatus,		_T(  "Not show PreDecA status"  ),	},	//
			{   ID_showPreDecAStatus,			_T(  "Show preDecA status"  ),		},
			{	ID_notShowPreDecVStatus,		_T(  "Not show PreDecV status"  ),	},
			{	ID_showPreDecVStatus,			_T(  "Show PreDecV status"  ),		},
			{	ID_notShowPostDecAStatus,		_T(  "Not show PostDecA status"  ),			},
			{	ID_showPostDecAStatus,			_T(  "Show PostDecA status"  ),			},
			{	ID_notShowPostDecVStatus,		_T(  "Not show PostDecV status"  ),			},
			{	ID_showPostDecVStatus,			_T(  "Show PostDecV status"  ),			},
#endif
		//
		{	ID_notTestGps,						CONST_ID_notTestGps,		},
		{	ID_testGps,							CONST_ID_testGps,		},
		{	ID_notTestStream,					CONST_ID_notTestStream,		},
		{	ID_testStream,						CONST_ID_testStream,		},


		{	ID_qyRefresh,						CONST_ID_Refresh,				},
	{	CONST_resId_menu_chuangKou,			CONST_ID_menu_chuangKou,		},
		{	ID_WINDOW_NEW,						CONST_ID_WINDOW_NEW,                },
		{	ID_WINDOW_CASCADE,					CONST_ID_WINDOW_CASCADE,			},
		{	ID_WINDOW_TILE_HORZ,				CONST_ID_WINDOW_TILE_HORZ,                    },
		{	ID_WINDOW_ARRANGE,					CONST_ID_WINDOW_ARRANGE,                },
	{	CONST_resId_menu_bangZhu,			CONST_ID_menu_bangZhu,		},
		{	ID_HELP,							CONST_ID_HELP,                },
		{	ID_APP_ABOUT,						CONST_str_ID_APP_ABOUT,		CONST_str_ID_APP_ABOUT_status,	},

	{	CONST_resId_menu_avCall,			CONST_ID_menu_avCall,						},
			{	ID_stopAvCall,					CONST_ID_stopAvCall,		},	
			{	ID_startAvCall,					CONST_ID_startAvCall,		},	

			{	ID_MENU_selectRtsp,				CONST_str_selectRtsp,		},
			{	ID_MENU_selectDefaultRecorder,	CONST_str_selectDefaultRecorder,	},
	//  {	ID_MENU_viewConference,					CONST_ID_MENU_viewConference,			},
	//  {	ID_MENU_viewConferenceResources,		CONST_ID_MENU_viewConferenceResources,	},

	{	CONST_resId_menu_share,				CONST_ID_menu_share,				},
			{	ID_stopShareScreen,					CONST_ID_stopShareScreen,	},
			{	ID_startShareScreen,				CONST_ID_startShareScreen,	},
		//{	CONST_resId_menu_shareFullScreen,		CONST_ID_startShareFullScreen,		},
			{	ID_startShareFullScreen,			CONST_ID_startShareFullScreen,	},

#if  0
			{	ID_startShareScreen_dx,				CONST_ID_startShareScreen_dx,	},
			{	ID_startShareFullScreen_dx,			CONST_ID_startShareFullScreen_dx,	},
#endif
		//{	CONST_resId_menu_startShareMediaFile,	CONST_ID_startShareMediaFile,		},
			{	ID_startShareMediaFile,				CONST_ID_startShareMediaFile,		},

			//{	CONST_resId_menu_startShareMediaDevice,	CONST_ID_startShareMediaDevice,		},
			{	ID_startShareMediaDevice,			CONST_ID_startShareMediaDevice,		},
			{	ID_startShareMediaDevice_unresizable,CONST_ID_startShareMediaDevice_unresizable,		},

	{	CONST_resId_menu_remoteAssist,		CONST_ID_menu_remoteAssist,			},
			{	ID_stopRemoteAssist,			CONST_ID_stopRemoteAssist,		},
			{	ID_startRemoteAssist,			CONST_ID_startRemoteAssist,	},
			{	ID_startFullScreenRemoteAssist,	CONST_ID_startFullScreenRemoteAssist,	},
	//
		//  {	ID_cfgVideoConference,				CONST_ID_cfgVideoConference,		},
		{	ID_ucbHideImGrpMems,				CONST_ID_ucbHideImGrpMems,				},
		{	ID_ucbShowImGrpMems,				CONST_ID_ucbShowImGrpMems,				},

#if  0
		{	ID_ucbNotAutoStopViewing,			CONST_ID_ucbNotAutoStopViewing,			},
		{	ID_ucbAutoStopViewing,				CONST_ID_ucbAutoStopViewing,			},

		{	ID_ucbNotViewScreen,				CONST_ID_ucbNotViewScreen,				},
		{	ID_ucbViewScreen,					CONST_ID_ucbViewScreen,				},
		{	ID_ucbNotViewWebcam0,				CONST_ID_ucbNotViewWebcam0,				},
		{	ID_ucbViewWebcam0,					CONST_ID_ucbViewWebcam0,				},
		{	ID_ucbNotViewWebcam1,				CONST_ID_ucbNotViewWebcam1,				},
		{	ID_ucbViewWebcam1,					CONST_ID_ucbViewWebcam1,				},
		{	ID_ucbNotViewWebcam2,				CONST_ID_ucbNotViewWebcam2,				},
		{	ID_ucbViewWebcam2,					CONST_ID_ucbViewWebcam2,				},
		
		{	ID_udbNotViewRtsp5,					CONST_ID_ucbNotViewRtsp5,				},	//  2014/05/15
		{	ID_udbViewRtsp5,					CONST_ID_ucbViewRtsp5,					},
#endif

		{	ID_ucbNotViewGps,					CONST_ID_ucbNotViewGps,					},
		{	ID_ucbViewGps,						CONST_ID_ucbViewGps,					},

		{	ID_notShowGpsData,					CONST_ID_notShowGpsData,				},
		{	ID_showGpsData,						CONST_ID_showGpsData,					},

	{	CONST_resId_menu_op,				CONST_ID_menu_op,					},
		{	ID_stopScrollBar,					CONST_ID_stopScrollBar,		},
		{	ID_startScrollBar,					CONST_ID_startScrollBar,		},
		{	ID_fullScreen,						CONST_ID_fullScreen,			},

		{	CONST_resId_endFullScreen,			CONST_str_endFullScreen,		},
		{	CONST_resId_fullScreen,				CONST_str_fullScreen,		},
		{	CONST_resId_closeWall,				CONST_str_closeWall,		},	//  2014/12/07
		{	CONST_resId_exit,					CONST_str_exit,				},	//  2014/12/12

	{	CONST_resId_menu_op_ptz,				CONST_ID_menu_op_ptz,			},
		{	ID_remotePtzControl,					CONST_ID_remotePtzControl,	},

	{	CONST_resId_menu_vWall,				CONST_ID_menu_vWall,		},
	{   CONST_resId_menu_3dWall,			CONST_ID_menu_3dWall,		},
	{   CONST_resId_menu_2dWall,			CONST_ID_menu_2dWall,		},
		{	ID_2dVWall_new,						CONST_ID_2dVWall_new,	},
		{	ID_2dVWall_global,					CONST_ID_2dVWall_global,		},
		//
		{	ID_globalGpsVWall,					CONST_ID_globalGpsVWall,		},
		{	ID_gpsVWall,						CONST_ID_gpsVWall,		},
		//
		{	ID_3dVWall_console,					CONST_ID_3dVWall_console,				},
		{	ID_3dVWall_new,						CONST_ID_3dVWall_new,				},


		{	ID_qySetDynBmp,						CONST_ID_qySetDynBmp,		},
		{	ID_setMessengerBmp,					CONST_ID_setMessengerBmp,	},
		{	ID_qySetImGrpMemBmp,				CONST_ID_qySetImGrpMemBmp,	},
		{	ID_selectMessenger,					CONST_ID_selectMessenger,	},

				
		//
		{	CONST_resId_menu_runningStatus,		CONST_ID_menu_runningStatus,	},		//  2013/02/06

		//
		{	CONST_resId_statusVWallEditRule,		CONST_str_statusVWallEditRule,		},
		{	CONST_resId_statusVWallRestart,			CONST_str_statusVWallRestart,		},
		{	CONST_resId_wallList,					CONST_str_wallList,					},
		{	CONST_resId_imNetStatList,				CONST_str_netStatList,	},
		{	CONST_resId_talkerList,					CONST_str_talkerList,	},
		{	CONST_resId_messengerStatusList,		CONST_str_messengerStatusList,	},
		{	CONST_resId_qList,						CONST_str_qList,		},

		{	CONST_resId_eConnTypeUnknown,			CONST_str_eConnTypeUnknown,		},
		{	CONST_resId_eConnType3Point5mm,			CONST_str_eConnType3Point5mm,		},
		{	CONST_resId_eConnTypeQuarter,			CONST_str_eConnTypeQuarter,		},
		{	CONST_resId_eConnTypeAtapiInternal,			CONST_str_eConnTypeAtapiInternal,		},
		{	CONST_resId_eConnTypeRCA,			CONST_str_eConnTypeRCA,		},
		{	CONST_resId_eConnTypeOptical,			CONST_str_eConnTypeOptical,		},
		{	CONST_resId_eConnTypeOtherDigital,			CONST_str_eConnTypeOtherDigital,		},
		{	CONST_resId_eConnTypeOtherAnalog,			CONST_str_eConnTypeOtherAnalog,		},
		{	CONST_resId_eConnTypeMultichannelAnalogDIN,			CONST_str_eConnTypeMultichannelAnalogDIN,		},
		{	CONST_resId_eConnTypeXlrProfessional,			CONST_str_eConnTypeXlrProfessional,		},
		{	CONST_resId_eConnTypeRJ11Modem,			CONST_str_eConnTypeRJ11Modem,		},
		{	CONST_resId_eConnTypeCombination,			CONST_str_eConnTypeCombination,		},
					
		{	CONST_resId_eGeoLocRear,			CONST_str_eGeoLocRear,		},
		{	CONST_resId_eGeoLocFront,			CONST_str_eGeoLocFront,		},
		{	CONST_resId_eGeoLocLeft,			CONST_str_eGeoLocLeft,		},
		{	CONST_resId_eGeoLocRight,			CONST_str_eGeoLocRight,		},
		{	CONST_resId_eGeoLocTop,			CONST_str_eGeoLocTop,		},
		{	CONST_resId_eGeoLocBottom,			CONST_str_eGeoLocBottom,		},
		{	CONST_resId_eGeoLocRearPanel,			CONST_str_eGeoLocRearPanel,		},
		{	CONST_resId_eGeoLocRiser,			CONST_str_eGeoLocRiser,		},
		{	CONST_resId_eGeoLocInsideMobileLid,			CONST_str_eGeoLocInsideMobileLid,		},
		{	CONST_resId_eGeoLocDrivebay,			CONST_str_eGeoLocDrivebay,		},
		{	CONST_resId_eGeoLocHDMI,			CONST_str_eGeoLocHDMI,		},
		{	CONST_resId_eGeoLocOutsideMobileLid,			CONST_str_eGeoLocOutsideMobileLid,		},
		{	CONST_resId_eGeoLocATAPI,			CONST_str_eGeoLocATAPI,		},

		//
		{	CONST_resId_channelType,				CONST_str_channelType,				},
		{	CONST_resId_inOctets,					CONST_str_inOctets,					},
		{	CONST_resId_outOctets,					CONST_str_outOctets,				},
		{	CONST_resId_inSpeed,					CONST_str_inSpeed,					},
		{	CONST_resId_outSpeed,					CONST_str_outSpeed,					},

	//  ListViewµÄÒ»Ð©×ÊÔ´
	{	CONST_resId_zuiJinJianCeShiJian,				CONST_str_zuiJinJianCeShiJian,		},
	//
	//  ¶Ô»°¿ò×ÊÔ´¶¼·ÅÏÂÃæ
	{	CONST_resId_dlgStatic,				},	
	//
		{	CONST_resId_dbNameOrDsnName,				CONST_ID_dbNameOrDsnName,	},
	//
	//	
	{	CONST_resId_STATIC_nDwLevels,					CONST_ID_STATIC_nDwLevels,			},
	{   CONST_resId_STATIC_nZcbhs,						CONST_ID_STATIC_nZcbhs,		},
	{	CONST_resId_STATIC_qrtTitle,					CONST_ID_STATIC_qrtTitle,				},
	{	CONST_resId_STATIC_hint,						CONST_ID_STATIC_hint,				},
	//
	{	CONST_resId_STATIC_type,						CONST_str_leiXing,							},
	{	CONST_resId_STATIC_name,						CONST_str_mingChen,								},
	{	CONST_resId_STATIC_cusName,						CONST_str_bieMing,								},
	{	CONST_resId_STATIC_des0,						CONST_ID_STATIC_des0,								},
	{	CONST_resId_STATIC_langId,						CONST_str_yuYan,								},
	{	CONST_resId_STATIC_supportedOs,					CONST_ID_STATIC_supportedOs,						},
	{	CONST_resId_STATIC_url,							CONST_ID_STATIC_url,							},

	//  IDD_qnmCfgOptions_isClient
	{	CONST_resId_STATIC_centerIp,					CONST_IDC_STATIC_centerIp,		},

	{	CONST_resId_STATIC_qyRegToolDir,				CONST_IDC_STATIC_qyRegToolDir,	},
	//

		{	CONST_resId_add,								CONST_str_Add,	},
		{	CONST_resId_del,								CONST_str_Del,	},

	//

	{	CONST_resId_IDD_qnmCfgPcRule,				CONST_IDD_qnmCfgPcRule,						},
	{	CONST_resId_IDD_qnmEditPcUsrInfo,			CONST_IDD_qnmCfgPcRule,			},
		{	CONST_resId_hint0,						CONST_ID_hint0,	},
		{	CONST_resId_hint1,						CONST_ID_hint1,	},
		{	CONST_resId_pc0_zongBu,					CONST_str_zongBu,	},		//  2009/01/04
		{	CONST_resId_pc2_benBu,					CONST_str_benBu,},
		{	CONST_resId_pc4_danWei,					CONST_str_danWei,},
		{	CONST_resId_pc8_buMen,					CONST_str_buMen,},
		{	CONST_resId_pc10_shiYongRen,			CONST_str_shiYongRen,},
		{	CONST_resId_pc12_jiQiLeiXing,			CONST_str_jiQiLeiXing,},
		{	CONST_resId_pc16_zhuYaoYongTu,			CONST_str_zhuYaoYongTu,},
		{	CONST_resId_pc18_lianXiDianHua,			CONST_str_lianXiDianHua,},
		{	CONST_resId_pc20_shiYongDiDian,			CONST_str_shiYongDiDian,},
		{	CONST_resId_pc14_ziChanBianHao,			CONST_str_ziChanBianHao,},
		{	CONST_resId_pc24_ziChanBianHao1,		CONST_str_ziChanBianHao1,},
		{	CONST_resId_pc26_ziChanShuoMing1,		CONST_str_ziChanShuoMing1,},
		{	CONST_resId_pc28_ziChanBianHao2,		CONST_str_ziChanBianHao2,},
		{	CONST_resId_pc30_ziChanShuoMing2,		CONST_str_ziChanShuoMing2,},





	//  2005/11/09
	{	CONST_resId_IDD_ABOUTBOX,					CONST_IDD_ABOUTBOX,	},
		{	CONST_resId_ver,							CONST_ID_ver,	},
		{	CONST_resId_qycxCopyRight,					CONST_ID_qycxCopyRight,	},
	{	CONST_resId_IDD_CFGUSR,						CONST_IDD_CFGUSR,		},
		{	CONST_resId_name,						CONST_ID_name,		},
	{	CONST_resId_IDD_CFGUSRS,					CONST_IDD_CFGUSRS,		},
		{	CONST_resId_HINT,							CONST_ID_HINT,		},
		{	CONST_resId_ADD,							CONST_str_Add,		},
		{	CONST_resId_MODIFY,							CONST_str_qyModify,		},
		{	CONST_resId_DEL,							CONST_str_Del,		},
	{	CONST_resId_IDD_CFGWARN,					CONST_ID_IDD_CFGWARN,							},
		{	CONST_resId_WARNON,							CONST_ID_WARNON,					},
		{	CONST_resId_STATIC_cfgWarn,					CONST_ID_STATIC_cfgWarn,						},
		{	CONST_resId_WARNUNTILUSRSTOPIT,				CONST_ID_WARNUNTILUSRSTOPIT,		},
		{	CONST_resId_STATIC_maxWarnElapse,			CONST_ID_STATIC_maxWarnElapse,			},
	{	CONST_resId_IDD_clearupEventCond,			CONST_IDD_clearupEventCond,		},

	{	CONST_resId_IDD_qnmSearch,					CONST_str_Search,				},
	//  2005/11/11
		{	CONST_resId_STATIC_bieMing,					CONST_ID_STATIC_bieMing,		},

		{	CONST_resId_STATIC_qiShiIP,					CONST_IDC_STATIC_qiShiIP,		},
		{	CONST_resId_STATIC_jieShuIP,				CONST_IDC_STATIC_jieShuIP,		},
		{	CONST_resId_STATIC_danWei,					CONST_IDC_STATIC_danWei,		},
		{	CONST_resId_STATIC_buMen,					CONST_IDC_STATIC_buMen,		},
		//
	{	CONST_resId_STATIC_shiYongRen,					CONST_STATIC_shiYongRen,		},
			//
	{	CONST_resId_IDD_shhgPcProperties,			CONST_IDD_shhgPcProperties,	},
		{	CONST_resId_pc0_zongBu,						CONST_IDC_CHECK_zb,	},
 		{	CONST_resId_pc2_benBu,						CONST_IDC_CHECK_bb,	},
 		{	CONST_resId_pc4_danWei,						CONST_IDC_CHECK_dw,	},
		{	CONST_resId_pc6_qiTaDanWei,					CONST_str_otherDepart,	},
		{	CONST_resId_pc8_buMen,						CONST_IDC_CHECK_bm,	},
		{	CONST_resId_pc10_shiYongRen,				CONST_IDC_CHECK_syr,	},
		{	CONST_resId_pc12_jiQiLeiXing,				COSNT_IDC_jiQiLeiXing,	},
		{	CONST_resId_pc14_ziChanBianHao,				CONST_IDC_ziChanBianHao,	},
		{	CONST_resId_pc16_zhuYaoYongTu,				CONST_IDC_zhuYaoYongTu,	},
		{	CONST_resId_pc18_lianXiDianHua,				CONST_IDC_lianXiDianHua,	},
		{	CONST_resId_pc20_shiYongDiDian,				CONST_IDC_shiYongDiDian,	},
		{	CONST_resId_pc22_shiYongDiDian,				CONST_IDC_shiYongDiDian,	},
		{	CONST_resId_pc24_ziChanBianHao1,			CONST_IDC_ziChanBianHao1,	},
		{	CONST_resId_pc26_ziChanShuoMing1,			CONST_IDC_ziChanShuoMing1,	},
		{	CONST_resId_pc28_ziChanBianHao2,			CONST_IDC_ziChanBianHao2,	},
		{	CONST_resId_pc30_ziChanShuoMing2,			CONST_IDC_ziChanShuoMing2,	},
		//
		{	CONST_resId_STATIC_usrInfoZone,				CONST_IDC_STATIC_usrInfoZone,	},	
		{	CONST_resId_STATIC_pcName,					CONST_IDC_STATIC_pcName,	},
		{	CONST_resId_STATIC_ip,						CONST_IDC_STATIC_ip,	},
		{	CONST_resId_STATIC_osName,					CONST_IDC_STATIC_osName,	},
		{	CONST_resId_STATIC_servicePack,				_T(  "ServicePack:"  ),	},
		{	CONST_resId_STATIC_mac0,					_T(  "MAC0:"  ),	},
		{	CONST_resId_STATIC_mac1,					_T(  "MAC1:"  ),	},
		{	CONST_resId_STATIC_mac2,					_T(  "MAC2:"  ),	},
		{	CONST_resId_STATIC_ip0,						_T(  "IP0:"  ),	},
		{	CONST_resId_STATIC_ip1,						_T(  "IP1:"  ),	},
		{	CONST_resId_STATIC_ip2,						_T(  "IP2:"  ),	},
		//
		{	CONST_resId_STATIC_qwmVer,					CONST_IDC_STATIC_qwmVer,		},
		{	CONST_resId_STATIC_regTime,					CONST_IDC_STATIC_regTime,		},
		{	CONST_resId_STATIC_auditTime,				CONST_IDC_STATIC_auditTime,		},
		{	CONST_resId_STATIC_clientStartTime,			CONST_IDC_STATIC_clientStartTime,		},
		{	CONST_resId_STATIC_lastCommTime,			CONST_IDC_STATIC_lastCommTime,		},
		//
		{	CONST_resId_imAuthCond_hint,				CONST_IDC_imAuthCond_hint,				},




	{	CONST_resId_IDD_qyExport,					CONST_IDD_qyExport,		},
		{	CONST_resId_RADIO_exportCurQuery,			CONST_IDC_RADIO_exportCurQuery,		},
		{	CONST_resId_RADIO_exportBakData,			CONST_IDC_RADIO_exportBakData,					},
		{	CONST_resId_RADIO_exportCfg,				CONST_IDC_RADIO_exportCfg,				},
		{	CONST_resId_STATIC_exportHint,				CONST_IDC_STATIC_exportHint,			},
		{	CONST_resId_RADIO_exportBhbCfg,				CONST_IDC_RADIO_exportBhbCfg,		},
		{	CONST_resId_RADIO_exportRegInfo,			CONST_IDC_RADIO_exportRegInfo,				},
	{	CONST_resId_IDD_qnmClearup,					CONST_IDD_qnmClearup,		},
		{	CONST_resId_STATIC_clearHint,				CONST_IDC_STATIC_clearHint,		},
		{	CONST_resId_RADIO_clearupEvent,				CONST_IDC_RADIO_clearupEvent,		},
	{	CONST_resId_IDD_pcAssetProperties,			CONST_str_Properties,		},			
		{	CONST_resId_STATIC_staticMac0,				_T(  "MAC:"  ),		},
	{	CONST_resId_IDD_qnmSearch,					CONST_str_Search,		},
		{	CONST_resId_STATIC_queryType,				CONST_IDC_STATIC_queryType,		},

		{	IDC_STATIC_hint,						CONST_IDC_STATIC_hint,	},

		{	CONST_resId_qnmCfgPcGrps_ADD,			CONST_str_Add,		},
		{	CONST_resId_qnmCfgPcGrps_MODIFY,		CONST_str_qyModify,		},
		{	CONST_resId_qnmCfgPcGrps_DEL,			CONST_str_Del,		},

	{	CONST_resId_STATIC_leiXing,					CONST_str_leiXing,		},
		{	CONST_resId_STATIC_jiSuanJiMing,			CONST_str_jiSuanJiMing,		},


#ifndef  __WINCE__
		//  {	SC_MINIMIZE,							CONST_str_SC_MINIMIZE,						},
		{	SC_CLOSE,									CONST_str_SC_CLOSE,							},
#endif
		{	ID_stopSpeaking,							CONST_str_stopSpeaking,						},
		{	ID_requestToSpeak,							CONST_str_speak,							},
		//
		{	CONST_resId_micOff,							CONST_str_micOff,						},
		//  {	CONST_resId_micOn,							CONST_str_micOn,						},
		//
		{	CONST_resId_fullScreenSharing,				CONST_IDC_STATIC_sharingScreen0,	},
		{	CONST_resId_startSharing,					CONST_str_startSharing,				},
		{	CONST_resId_stopSharing,					CONST_str_stopSharing,				},
		{	CONST_resId_running,						CONST_str_running,					},
		{	CONST_resId_started,						CONST_str_started,					},
		{	CONST_resId_start,							CONST_str_start,					},
		{	CONST_resId_stop,							CONST_str_stop,						},

		{	CONST_resId_setPassword,					CONST_str_setPassword,		},
		{	CONST_resId_newMessenger,					CONST_str_newMessenger,		},
		{	CONST_resId_renameMessenger,				CONST_str_renameMessenger,	},
		{	CONST_resId_sameMessenger,					CONST_str_sameMessenger,	},



	//
	//
	{	CONST_resId_startIp,						CONST_str_startIp,	},
	{	CONST_resId_endIp,							CONST_str_endIp,	},
	//
	{	CONST_resId_misServName,					CONST_str_servName,	},
	{	CONST_resId_uiDevType,						CONST_str_leiXing,	},
	{	CONST_resId_wDevIdStr,						CONST_str_phoneNo,	},

	//
	{	CONST_resId_status,							CONST_str_zhuangTai,		},

	//
	{	CONST_resId_pcMgrClass,						CONST_str_leiBie,			},
	{	CONST_resId_pcUsrInfo,						CONST_IDC_pcUsrInfo,		},
	{	CONST_resId_pcOpNode,						CONST_str_caozuo,			},
	//
	{	CONST_resId_pcOpNode_desc,					CONST_IDC_pcOpNode_desc,					},

	//  2008/12/14
	{	CONST_resId_objIdStr_unRegGrp,				CONST_objIdStr_unRegGrp,	},	//			_T(  "(Î´×¢²áÓÃ»§)"  )
	{	CONST_resId_objIdStr_othersGrp,				CONST_objIdStr_othersGrp,	},	//			_T(  "(ÆäËûÓÃ»§)"  )
	{	CONST_resId_objIdStr_me,					CONST_objIdStr_me,			},	//			_T(  "ÎÒ"  )
	{	CONST_resId_objIdStr_imGrps,				CONST_objIdStr_imGrps,		},	//			_T(  "×é¼¯ºÏ"  )


	//
	{	CONST_resId_statPcInfo,						CONST_IDC_statPcInfo,			},
	{	CONST_resId_statUsrInfo,					CONST_IDC_statUsrInfo,	},
	{	CONST_resId_statGeneral,					CONST_IDC_statGeneral,		},
	{	CONST_resId_statOthers,						CONST_IDC_statOthers,			},
	//
	{	CONST_resId_statMessengerInfo,				CONST_IDC_statMessengerInfo,	},


	//	³ÌÐòÌâÍ·£¬2005/11/16
	{	CONST_resId_sys_isCli_default,				_T(  "Qycx Messenger"  ),									},
	{	CONST_resId_sys_isCli_ts,					_T(  "Qycx Messenger"  ),									},
	{	CONST_resId_sys_isMgr,						CONST_sys_misMgr,			},

	//  ÔÓÏî
	//  2008/12/15
	{	CONST_resId_network,						CONST_str_network,							},
	{	CONST_resId_baseSystem,						CONST_str_baseSystem,						},
	{	CONST_resId_qyMessengerView,				CONST_str_qyMessengerView,					},		//_T(  "ÁªÏµÈËÊ÷×´Í¼"  )
	{	CONST_resId_qyMessengerList,				CONST_str_qyMessengerList,					},
	{	CONST_resId_qyMessengerAuthList,			CONST_str_qyMessengerAuthList,				},
	{	CONST_resId_qyImAmList,						CONST_str_qyImAmList,						},
	{	CONST_resId_qyPhoneMessengerList,			CONST_str_qyPhoneMessengerList,				},
	{	CONST_resId_qyPcUsrList2,					CONST_str_qyPcUsrList2,						},
	{	CONST_resId_qyMessengerAuthList_needAudited,CONST_str_qyMessengerAuthList_needAudited,	},	
	{	CONST_resId_qyImGrpAuthList,				CONST_str_qyImGrpAuthList,					},
	{	CONST_resId_qyImGrpList,					CONST_str_qyImGrpList,						},
	{	CONST_resId_qyImGrpMemList,					CONST_str_qyImGrpMemList,					},
	{	CONST_resId_customerServiceList,			CONST_str_customerServiceList,			},
	{	CONST_resId_wwwQmCfgList,					CONST_str_wwwQmCfgList,						},
	{	CONST_resId_sharedDynBmpList,				CONST_str_sharedDynBmpList,					},
	{	CONST_resId_sharedDynBmpRuleList,			CONST_str_sharedDynBmpRuleList,					},
	{	CONST_resId_procIpKnowledge,				CONST_str_procIpKnowledge,					},
	{	CONST_resId_qyGsmModemList,					CONST_str_qyGsmModemList,					},
	{	CONST_resId_qySmContactList,				CONST_str_qySmContactList,					},
	{	CONST_resId_qyPhoneGuestList,				CONST_str_qyPhoneGuestList,					},
	{	CONST_resId_qyClientList,					CONST_str_qyClientList,						},
	{	CONST_resId_loaded,							CONST_str_loaded,							},
	{	CONST_resId_dataSourceList,					CONST_str_dataSourceList,					},
	{	CONST_resId_loadDataSourceFailed,			CONST_str_loadDataSourceFailed,				},
	{	CONST_resId_unloadDataSourceFailed,			CONST_str_unloadDataSourceFailed,			},
	//
	{	CONST_resId_selectDbFile,					CONST_str_selectDbFile,						},	
	{	CONST_resId_cannotEmpty,					CONST_str_cannotEmpty,						},
	{	CONST_resId_systemTypeErr,					CONST_str_systemTypeErr,					},
	{	CONST_resId_systemNameExisted,				CONST_str_systemNameExisted,				},
	{	CONST_resId_addSystemErr,					CONST_str_addSystemErr,						},
	{	CONST_resId_maximumNumberOfObject,			CONST_str_maximumNumberOfObject,			},
	{	CONST_resId_systemCfgErr,					CONST_str_systemCfgErr,						},
	{	CONST_resId_databaseformat,					CONST_str_databaseformat,					},
	{	CONST_resId_cannotModifyIfLoaded,			CONST_str_cannotModifyIfLoaded,				},
	{	CONST_resId_cannotDeleteIfLoaded,			CONST_str_cannotDeleteIfLoaded,				},
	{	CONST_resId_askIfDelete,					CONST_str_askIfDelete,						},
	//
	//
	{	CONST_resId_qyRealTimeTaskList,				CONST_str_qyRealTimeTaskList,				},
	{	CONST_resId_sharingObjectList,				CONST_str_sharingObjectList,				},
	{	CONST_resId_playerList,						CONST_str_playerList,					},
	{	CONST_resId_qyTaskList,						CONST_str_qyTaskList,						},
	{	CONST_resId_qyTaskHisList,					CONST_str_qyTaskHisList,					},
	{	CONST_resId_msgList,						CONST_str_msgList,							},
	{	CONST_resId_qyMsgToday,						CONST_str_qyMsgToday,						},
	{	CONST_resId_today,							CONST_str_today,							},
	{	CONST_resId_logList,						CONST_str_logList,							},
	{	CONST_resId_unfinished,						CONST_str_unfinished,						},
	//
	{	CONST_resId_statUsrInfoList,				CONST_str_statUsrInfoList,					},
	{	CONST_resId_statGeneralList,				CONST_str_statGeneralList,					},
	{	CONST_resId_statOthersList,					CONST_str_statOthersList,					},
	{	CONST_resId_statMessengerInfoList,			CONST_str_statMessengerInfoList,			},
	//
	{	CONST_resId_statCondition,					CONST_str_statCondition,					},
	{	CONST_resId_askForContentOfStat,			CONST_str_askForContentOfStat,				},
	{	CONST_resId_ipCount,						CONST_str_ipCount,							},
	{	CONST_resId_pcCount,						CONST_str_pcCount,							},
	{	CONST_resId_computer,						CONST_str_computer,							},
	{	CONST_resId_otherOs,						CONST_str_otherOs,							},
	{	CONST_resId_networkCard,					CONST_str_networkCard,						},
	{	CONST_resId_multiNetworkCard,				CONST_str_multiNetworkCard,					},
	{	CONST_resId_userCount,						CONST_str_userCount,						},

	//  import
	{	CONST_resId_selectContentOfImport,			CONST_str_selectContentOfImport,			},
	{	CONST_resId_importBakData,					CONST_str_importBakData,					},
	{	CONST_resId_importRegInfo,					CONST_str_importRegInfo,					},
	{	CONST_resId_selectFilenameFormat,			CONST_str_selectFilenameFormat,				},
	{	CONST_resId_selectFolder,					CONST_str_selectFolder,						},
	{	CONST_resId_importOk,						CONST_str_importOk,							},
	{	CONST_resId_importWizard,					CONST_str_importWizard,						},
	{	CONST_resId_exportWizard,					CONST_str_exportWizard,						},
	{	CONST_resId_exportOk,						CONST_str_exportOk,							},
	{	CONST_resId_exportFailed,					CONST_str_exportFailed,						},
	{	CONST_resId_emptyWizard,					CONST_str_emptyWizard,						},
	{	CONST_resId_fileFormat,						CONST_str_fileFormat,						},
	{	CONST_resId_timeErr,						CONST_str_timeErr,							},
	{	CONST_resId_timeErr2,						CONST_str_timeErr2,							},
	{	CONST_resId_clearVerify,					CONST_str_clearVerify,						},
	//  mainfrm
	{	CONST_resId_pathErr,						CONST_str_pathErr,							},
	{	CONST_resId_current,						CONST_str_current,							},
	{	CONST_resId_history,						CONST_str_history,							},
	{	CONST_resId_paramErrMakeClientFailed,		CONST_str_paramErrMakeClientFailed,			},
	{	CONST_resId_folderErrMakeClientFailed,		CONST_str_folderErrMakeClientFailed,		},
	{	CONST_resId_makeClientOk,					CONST_str_makeClientOk,						},
	{	CONST_resId_makeClientFailed,				CONST_str_makeClientFailed,					},
	{	CONST_resId_err,							CONST_str_err,								},
	{	CONST_resId_stopServiceWarning,				CONST_str_stopServiceWarning,				},
	//	qyMcMainProc1.cpp
	{	CONST_resId_NoPrivilegesToOpenPcList,		CONST_str_NoPrivilegesToOpenPcList,			},
	{	CONST_resId_warning,						CONST_str_warning,							},
	{	CONST_resId_searchIp,						CONST_str_searchIp,							},
	{	CONST_resId_chaXun,							CONST_str_chaXun,							},
	{	CONST_resId_theOsIs,						CONST_str_theOsIs,							},
	{	CONST_resId_belongToPc,						CONST_str_belongToPc,						},	
	{	CONST_resId_searchResultBelongTo,			CONST_str_searchResultBelongTo,				},
	{	CONST_resId_port,							CONST_str_port,								},
	{	CONST_resId_belongToUnknownDevice,			CONST_str_belongToUnknownDevice,			},
	{	CONST_resId_searchOfResult,					CONST_str_searchOfResult,					},
	{	CONST_resId_communicationStatus,			CONST_str_communicationStatus,				},
	{	CONST_resId_communicationStatusWithFilters,	CONST_str_communicationStatusWithFilters,	},
	//
	{	CONST_resId_qySearch,						CONST_str_qySearch,							},
	{	CONST_resId_all,							CONST_str_all,								},
	{	CONST_resId_none,							CONST_str_none,								},
	{	CONST_resId_fieldCannotSame,				CONST_str_fieldCannotSame,					},
	{	CONST_resId_qnmHint_startIp0,				CONST_qnmHint_startIp0,						},
	{	CONST_resId_qnmHint_endIpLtStartIp,			CONST_qnmHint_endIpLtStartIp,				},
	//
	{	CONST_resId_grpNameCannotEmpty,				CONST_str_grpNameCannotEmpty,				},
	{	CONST_resId_messengerNameCannotEmpty,		CONST_str_messengerNameCannotEmpty,			},
	{	CONST_resId_passwdCannotEmpty,				CONST_str_passwdCannotEmpty,				},
	{	CONST_resId_passwdNotConfirmed,				CONST_str_passwdNotConfirmed,				},
	{	CONST_resId_nameExists,						CONST_str_nameExists,						},
	//
	{	CONST_resId_intervalBetween,				CONST_str_intervalBetween,					},
	{	CONST_resId_minuteAnd,						CONST_str_minuteAnd,						},
	{	CONST_resId_uptoMinute,						CONST_str_uptoMinute,						},
	{	CONST_resId_concurrentBetween,				CONST_str_concurrentBetween,				},
	{	CONST_resId_and,							CONST_str_and,								},
	{	CONST_resId_upto,							CONST_str_upto,								},
	{	CONST_resId_nMaxConns,						CONST_str_nMaxConns,						},
	{	CONST_resId_ipWrong,						CONST_str_ipWrong,							},
	{	CONST_resId_default_qrtTitle,				CONST_default_qrtTitle,						},
	//
	{	CONST_resId_afterStandard,					CONST_str_afterStandard,					},
	{	CONST_resId_cannotBeEmpty,					CONST_str_cannotBeEmpty,					},
	{	CONST_resId_ifStandard,						CONST_str_ifStandard,						},
	{	CONST_resId_standardFinished,				CONST_str_standardFinished,					},
	{	CONST_resId_standardFinished,				CONST_str_standardFinished,					},
	{	CONST_resId_ifSaveStandardPolicy,			CONST_str_ifSaveStandardPolicy,				},
	{	CONST_resId_standardPolicyCannotBeEmpty,	CONST_str_standardPolicyCannotBeEmpty,		},
	{	CONST_resId_cannotFindSendChannel,			CONST_str_cannotFindSendChannel,			},
	//
	{	CONST_resId_sendFile,						CONST_str_sendFile,							},
	{	CONST_resId_recvFile,						CONST_str_recvFile,							},
	//
	{	CONST_resId_qingqiu,						CONST_str_qingqiu,							},
	{	CONST_resId_tasks,							CONST_str_tasks,							},
	{	CONST_resId_tempGroup,						CONST_str_tempGroup,						},
	{	CONST_resId_ifStopScreenSharingRemoteAssist,CONST_str_ifStopScreenSharingRemoteAssist,	},
	{	CONST_resId_howToEnlarge,					CONST_str_howToEnlarge,						},
	{	CONST_resId_quXiao,							CONST_str_quXiao,							},
	{	CONST_resId_canceled,						CONST_str_canceled,							},
	{	CONST_resId_xiangYing,						CONST_str_xiangYing,						},
	//
	{	CONST_resId_pleaseSelect,					CONST_str_pleaseSelect,						},
	{	CONST_resId_canSelect,						CONST_str_canSelect,						},
	{	CONST_resId_select,							CONST_str_select,							},
	{	CONST_resId_toInterupt,						CONST_str_toInterupt,						},
	{	CONST_resId_toRequestAgain,					CONST_str_toRequestAgain,					},
	{	CONST_resId_sendAgain,						CONST_str_sendAgain,						},
	{	CONST_resId_faSong,							CONST_str_faSong,							},
	{	CONST_resId_jieShou,						CONST_str_jieShou,							},

	{	CONST_resId_reqToSend,						CONST_str_reqToSend,						},	
	{	CONST_resId_accept,							CONST_str_accept,							},
	{	CONST_resId_deny,							CONST_str_deny,							},
	{	CONST_resId_interupted,						CONST_str_interupted,						},
	{	CONST_resId_accepted,						CONST_str_accepted,							},
	{	CONST_resId_denied,							CONST_str_denied,							},

	{	CONST_resId_ifExitSession,					CONST_str_ifExitSession,					},
	{	CONST_resId_localVideo,						CONST_str_localVideo,						},
	{	CONST_resId_ifAcceptVideo,					CONST_str_ifAcceptVideo,					},
	{	CONST_resId_willSendFile,					CONST_str_willSendFile,						},
	{	CONST_resId_pleaseRecvFile,					CONST_str_pleaseRecvFile,					},
	{	CONST_resId_recvFinished,					CONST_str_recvFinished,						},
	{	CONST_resId_sendFinished,					CONST_str_sendFinished,						},
	{	CONST_resId_saveAs,							CONST_str_saveAs,							},
	{	CONST_resId_saved,							CONST_str_saved,							},
	{	CONST_resId_zhongDe,						CONST_str_zhongDe,							},
	{	CONST_resId_pcRegistration,					CONST_str_pcRegistration,					},
	{	CONST_resId_askIfDeleteInfo,				CONST_str_askIfDeleteInfo,					},
	{	CONST_resId_message,						CONST_str_message,							},
	{	CONST_resId_allSystemEvent,					CONST_str_allSystemEvent,					},
	{	CONST_resId_ifChangeDb,						CONST_str_ifChangeDb,						},
	{	CONST_resId_cannotConnectToDb,				CONST_str_cannotConnectToDb,				},
	{	CONST_resId_buildDbErr,						CONST_str_buildDbErr,						},
	{	CONST_resId_restart,						CONST_str_restart,							},
	{	CONST_resId_restoreAccess,					CONST_str_restoreAccess,					},
	{	CONST_resId_scope,							CONST_str_scope,							},
	//
	{	CONST_resId_desOfAdminGrp,					CONST_str_desOfAdminGrp,					},
	{	CONST_resId_desOfLogGrp,					CONST_str_desOfLogGrp,						},
	{	CONST_resId_desOfCfgGrp,					CONST_str_desOfCfgGrp,						},
	{	CONST_resId_clearupKnowledge,				CONST_str_clearupKnowledge,					},
	{	CONST_resId_clearupPhoneBook,				CONST_str_clearupPhoneBook,					},
	{	CONST_resId_importRecords,					CONST_str_importRecords,					},
	{	CONST_resId_countOfRecords,					CONST_str_countOfRecords,					},
	{	CONST_resId_importFinished,					CONST_str_importFinished,					},
	{	CONST_resId_deleteLogBetween,				CONST_str_deleteLogBetween,					},
	{	CONST_resId_cannotFindVideoDevice,			CONST_str_cannotFindVideoDevice,			},
	{	CONST_resId_rangeOfCorporateStructureLevel,	CONST_str_rangeOfCorporateStructureLevel,	},
	{	CONST_resId_rangeOfAssetNoNumber,			CONST_str_rangeOfAssetNoNumber,				},
	{	CONST_resId_reallyToDelete,					CONST_str_reallyToDelete,					},
	{	CONST_resId_rangeOfNumber,					CONST_str_rangeOfNumber,					},
	{	CONST_resId_whetherToModify,				CONST_str_whetherToModify,					},
	{	CONST_resId_hintToRestartProgram,			CONST_str_hintToRestartProgram,				},
	{	CONST_resId_needAuthCondition,				CONST_str_needAuthCondition,				},
	{	CONST_resId_createGroupFailed,				CONST_str_createGroupFailed,				},
	{	CONST_resId_hintToAddMember,				CONST_str_hintToAddMember,					},
	{	CONST_resId_modifyGroupNameFailed,			CONST_str_modifyGroupNameFailed,			},
	{	CONST_resId_hintToCreateGroup,				CONST_str_hintToCreateGroup,				},
	{	CONST_resId_hintToModifyGroup,				CONST_str_hintToModifyGroup,				},
	{	CONST_resId_askIfRemoveFromGroup,			CONST_str_askIfRemoveFromGroup,				},
	{	CONST_resId_numberIsWrong,					CONST_str_numberIsWrong,					},
	{	CONST_resId_selectGroup,					CONST_str_selectGroup,						},
	{	CONST_resId_selectMessenger,				CONST_str_selectMessenger,					},
	{	CONST_resId_askIfDeletePhoneNumber,			CONST_str_askIfDeletePhoneNumber,			},
	{	CONST_resId_needToSelect,					CONST_str_needToSelect,						},
	{	CONST_resId_online,							CONST_str_online,							},
	{	CONST_resId_offline,						CONST_str_offline,							},
	{	CONST_resId_hintOfModifyId,					CONST_str_hintOfModifyId,					},
	{	CONST_resId_newId,							CONST_str_newId,							},
	{	CONST_resId_hintOfReinput,					CONST_str_hintOfReinput,					},
	{	CONST_resId_hintOfPhoneReinput,				CONST_str_hintOfPhoneReinput,				},
	{	CONST_resId_hintOfRetype,					CONST_str_hintOfRetype,						},
	{	CONST_resId_modifyFailed,					CONST_str_modifyFailed,						},
	{	CONST_resId_askIfDeleteContact,				CONST_str_askIfDeleteContact,				},
	{	CONST_resId_askIfDeleteRegInfo,				CONST_str_askIfDeleteRegInfo,				},
	{	CONST_resId_askIfDeleteTmpRegInfo,			CONST_str_askIfDeleteTmpRegInfo,			},
	{	CONST_resId_whetherOnline,					CONST_str_whetherOnline,					},
	{	CONST_resId_standardUsrInfoFailed,			CONST_str_standardUsrInfoFailed,			},
	{	CONST_resId_whetherToSaveStandardRule,		CONST_str_whetherToSaveStandardRule,		},
	{	CONST_resId_saveStandardRuleFailed,			CONST_str_saveStandardRuleFailed,			},
	{	CONST_resId_invaildIp,						CONST_str_invaildIp,						},
	{	CONST_resId_invaildEndIp,					CONST_str_invaildEndIp,						},
	{	CONST_resId_phoneGuest,						CONST_str_phoneGuest,						},
	{	CONST_resId_errOfImportFmt,					CONST_str_errOfImportFmt,					},
	{	CONST_resId_unicodeImportFmt,				CONST_str_unicodeImportFmt,					},
	{	CONST_resId_tooMoreColumn,					CONST_str_tooMoreColumn,					},
	{	CONST_resId_needColumn,						CONST_str_needColumn,						},
	{	CONST_resId_passwordLength,					CONST_str_passwordLength,					},
	{	CONST_resId_passwordWrong,					CONST_str_passwordWrong,					},
	{	CONST_resId_passwordComposed,				CONST_str_passwordComposed,					},
	{	CONST_resId_passwordEmpty,					CONST_str_passwordEmpty,					},
	{	CONST_resId_passwordCannotMatch,			CONST_str_passwordCannotMatch,				},
	{	CONST_resId_passwordSaved,					CONST_str_passwordSaved,					},
	{	CONST_resId_userExisted,					CONST_str_userExisted,						},
	{	CONST_resId_userBelongToOtherGroup,			CONST_str_userBelongToOtherGroup,			},
	{	CONST_resId_dbErr,							CONST_str_dbErr,							},
	{	CONST_resId_dbErrHint,						CONST_str_dbErrHint,						},
	{	CONST_resId_addNewUser,						CONST_str_addNewUser,						},
	{	CONST_resId_userEmpty,						CONST_str_userEmpty,						},
	{	CONST_resId_invalidNumberAndMinIs,			CONST_str_invalidNumberAndMinIs,				},
	{	CONST_resId_invalidNumberAndMaxIs,			CONST_str_invalidNumberAndMaxIs,				},
	//  2009/01/27
	{	CONST_resId_runAsAdmin,						CONST_str_runAsAdmin,						},
	{	CONST_resId_installedProgramDb,				CONST_str_installedProgramDb,				},
	{	CONST_resId_verIs,							CONST_str_verIs,							},
	{	CONST_resId_updateProgramDbVer,				CONST_str_updateProgramDbVer,				},
	{	CONST_resId_renameDbIs,						CONST_str_renameDbIs,						},
	{	CONST_resId_whetherToUpdate,				CONST_str_whetherToUpdate,					},
	{	CONST_resId_isWrong,						CONST_str_isWrong,							},
	{	CONST_resId_mightBe,						CONST_str_mightBe,							},
	{	CONST_resId_updateTo,						CONST_str_updateTo,							},
	{	CONST_resId_Import,							CONST_str_Import,							},
	{	CONST_resId_Export,							CONST_str_Export,							},
	{	CONST_resId_completed,						CONST_str_completed,						},
	{	CONST_resId_folderDoesNotExist,				CONST_str_folderDoesNotExist,				},
	{	CONST_resId_pathIsNotAFolder,				CONST_str_pathIsNotAFolder,					},
	{	CONST_resId_beingProcessed,					CONST_str_beingProcessed,					},
	{	CONST_resId_interrupted,					CONST_str_interrupted,						},
	{	CONST_resId_incorrectUserOrPwd,				CONST_str_incorrectUserOrPwd,				},
	{	CONST_resId_limitedUserAccountCannotLogon,	CONST_str_limitedUserAccountCannotLogon,	},
	{	ID_MENU_cfgCaptureFilter_v,					CONST_str_videoCaptureFilter,				},
	{	ID_MENU_cfgCapturePin_v,					CONST_str_videoCapturePin,					},
	{	ID_MENU_cfgPreviewPin_v,					CONST_str_videoPreviewPin,					},
	{	ID_MENU_cfgCrossBar_v,						CONST_str_videoCrossBar,					},

	{	CONST_resId_whetherToSave,					CONST_str_whetherToSave,					},


	//  {	ID_MENU_notUseVfwWebcam,					CONST_str_ID_MENU_notUseVfwWebcam,			},
	//  {	ID_MENU_useVfwWebcam,						CONST_str_ID_MENU_useVfwWebcam,				},
	//
	{	ID_MENU_useWebcam_vfw,						CONST_str_ID_MENU_useWebcam_vfw,			},
	{	ID_MENU_useWebcam_directX,					CONST_str_ID_MENU_useWebcam_directX,		},
	{	ID_MENU_useWebcam_custom,					CONST_str_ID_MENU_useWebcam_custom,			},
	//
	{	CONST_resId_videoConference,				CONST_str_videoConference,					},
	{	CONST_resId_conferenceResources,			CONST_str_conferenceResources,				},
	{	CONST_resId_warn_tooManyVConferenceMems,	CONST_str_warn_tooManyVConferenceMems,		},
	{	CONST_resId_warn_onlyQuadCoreCanSupport,	CONST_str_warn_onlyQuadCoreCanSupport,		},

	//
	{	CONST_resId_licenseTimeout,					CONST_str_licenseTimeout,					},
	{	CONST_resId_trialPeriod,					CONST_str_trialPeriod,						},
	{	CONST_resId_days,							CONST_str_days,								},

	//  
	{	CONST_resId_overall,						CONST_str_overall,							},
	{	CONST_resId_disable,						CONST_str_disable,							},
	{	CONST_resId_useDefault,						CONST_str_useDefault,						},
	//

	{	CONST_resId_selectCompressor,					CONST_str_selectCompressor,	},
	{	CONST_resId_warning_restrictSharedDymBmps,		CONST_str_warning_restrictSharedDymBmps,	},
	{	CONST_resId_ucbUseDynBmpRule,					CONST_str_ucbUseDynBmpRule,					},
	{	CONST_resId_ucbUseDynBmpRule_demo,				CONST_str_ucbUseDynBmpRule_demo,			},
	{	CONST_resId_anotherLogon,						CONST_str_anotherLogon,						},
	{	CONST_resId_anotherLogonExists,					CONST_str_anotherLogonExists,				},
	{	CONST_resId_areYouSure,							CONST_str_areYouSure,						},
	{	CONST_resId_askIfUseDefault,					CONST_str_askIfUseDefault,					},
	{	CONST_resId_willYouClose,						CONST_str_willYouClose,						},
	{	CONST_resId_cancelAV,							CONST_str_cancelAV,							},
	{	CONST_resId_screenSharing,						CONST_str_shareScreen,						},
	{	CONST_resId_cancelScreenSharing,				CONST_str_cancelScreenSharing,				},
	{	CONST_resId_hideMsgBox,							CONST_str_hideMsgBox,						},
	{	CONST_resId_showMsgBox,							CONST_str_showMsgBox,						},
	{	CONST_resId_resetMsgBox,						CONST_str_resetMsgBox,						},
	{	CONST_resId_avExclusively,						CONST_str_avExclusively,					},
	{	CONST_resId_avNonExclusively,					CONST_str_avNonExclusively,					},
	{	CONST_resId_hideMore,							CONST_str_hideMore,							},
	{	CONST_resId_more,								CONST_str_more,								},
	{	CONST_resId_viewDlg,							CONST_str_dialog,							},				//  2013/09/08
	{	CONST_resId_closeDlgTalk,						CONST_str_closeDlgTalk,						},				//  2013/09/08
	{	CONST_resId_toggleFullScreen,					CONST_str_toggleFullScreen,					},
	{	CONST_resId_ptz,								CONST_str_ptz,								},				//  2013/02/16
	{	CONST_resId_hidePtz,							CONST_str_hidePtz,							},				//  2013/02/16
	{	CONST_resId_subtitles,							CONST_str_subtitles,						},				//  2013/04/05
	{	CONST_resId_hideSubtitles,						CONST_str_hideSubtitles,					},				//  2013/04/05
	{	CONST_resId_showMenu,							CONST_str_showMenu,							},
	{	CONST_resId_hideMenu,							CONST_str_hideMenu,							},
	{	CONST_resId_seconds,							CONST_str_seconds,							},
	{	CONST_resId_automaticallyCanceled,				CONST_str_automaticallyCanceled,			},
	{	CONST_resId_after,								CONST_str_after,							},
	{	CONST_resId_doYouWantToExit,					CONST_str_doYouWantToExit,					},
	{	CONST_resId_searchingServer,					CONST_str_searchingServer,					},
	{	CONST_resId_tryToConnect,						CONST_str_tryToConnect,						},
	{	CONST_resId_cannotFindServer,					CONST_str_cannotFindServer,					},
	{	CONST_resId_failedToLogon,						CONST_str_failedToLogon,					},
	{	CONST_resId_conferenceTimeout,					CONST_str_conferenceTimeout,				},
	{	CONST_resId_subtitleLimited,					CONST_str_subtitleLimited,				},

		

	//

	//  qmStr.h
#if  0
	{	CONST_resId_qyAppAvLevel_mini,				CONST_str_qyAppAvLevel_mini,		},
	{	CONST_resId_qyAppAvLevel_basic,				CONST_str_qyAppAvLevel_basic,		},
	{	CONST_resId_qyAppAvLevel_standard,			CONST_str_qyAppAvLevel_standard,		},
	{	CONST_resId_qyAppAvLevel_high,				CONST_str_qyAppAvLevel_high,		},
	{	CONST_resId_qyAppAvLevel_top,				CONST_str_qyAppAvLevel_top,		},
#endif

	//
	{	CONST_resId_name_isMgr_plus,				CONST_str_name_isMgr_plus,					},
	//
	{	CONST_resId_autoScan,						CONST_str_autoScan,					},
	{	CONST_resId_rainBrush,						CONST_str_rainBrush,				},
	{	CONST_resId_searchLight,					CONST_str_searchLight,				},

	{	CONST_resId_ok,								CONST_str_ok,						},
	{	CONST_resId_cancel,							CONST_str_cancel,					},

	//
	{	CONST_resId_sharingNotSupportFullScreen,	CONST_str_sharingNotSupportFullScreen,		},
	{	CONST_resId_sharingLetWinBeSmaller,			CONST_str_sharingLetWinBeSmaller,	},


	//
	{	CONST_resId_gotoMeeting,					CONST_str_gotoMeeting,				},	
	{	CONST_resId_wouldYouLikeToMeeting,			CONST_str_wouldYouLikeToMeeting,	},
	{	CONST_resId_speakingOrNotSpeaking,			CONST_str_speakingOrNotSpeaking,	},
	{	CONST_resId_useMeetingFunction,				CONST_str_useMeetingFunction,		},
	//
	{	CONST_resId_welcomeToUse,					CONST_str_welcomeToUse,				},
	{	CONST_resId_qycxVideoconference,			CONST_str_qycxVideoconference,		},
	{	CONST_resId_wizard_welcome,					CONST_str_wizard_welcome,			},
	//  3D  wall
	{	CONST_resId_viewDlgTalk_note,				CONST_str_viewDlgTalk_note,			},


	{	CONST_resId_3dFont,							CONST_str_3dFont,					},

	{	CONST_resId_total,							CONST_str_total,					},
	{	-1,											NULL,					},
};



