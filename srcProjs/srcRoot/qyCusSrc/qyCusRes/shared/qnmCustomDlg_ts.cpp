
#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
#include	"myresource_main_ts.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

  QY_DMITEM  CONST_dlg_qnmCfgOptions_isCli_ts[]  =
{
	{	IDC_STATIC_cntName,		},
	{	IDC_STATIC_centerAddr,				(  TCHAR  *  )CONST_resId_STATIC_centerIp,		},
	{	IDC_STATIC_cntAddr0,	},
	{	IDC_STATIC_cntAddr1,	},
	{	IDC_STATIC_cntAddr2,	},
	{	IDC_STATIC_cntPort,		},
	{	IDC_CHECK_useDb,		},
	{	IDC_BUTTON_more,		},
	{	IDC_ADD,				},
	{	IDC_MODIFY,				},
	{	IDC_DEL,				},
	{	IDOK,													},
	{	IDCANCEL,											},
	{	-1,			},
};


#if  0
#ifndef  __WINCE__

 QY_DMITEM  CONST_dlg_aboutBox_ts[]  = 
{
	{	IDC_STATIC_ver,						(  TCHAR  *  )CONST_resId_ver,						},
	{	IDC_STATIC_qycxCopyRight,			(  TCHAR  *  )CONST_resId_qycxCopyRight,				},
	{	IDOK,														},
	{	-1,		},

};
#endif
#endif
#if  0
 QY_DMITEM  CONST_dlg_talk_ts[]  =
{
	{	IDC_STATIC_instantStatus,	},
#if 0
	{	IDC_BUTTON_font,			},
	{	IDC_STATIC_peerName,		},
#endif
	{	IDC_STATIC_peerDesc,		},
	{	IDCANCEL,		},
	{	-1,		},
};
#endif
#if  0
 QY_DMITEM  CONST_dlg_desktopsMon_ts[]  =
{
	{	IDC_STATIC30,		},
	{	IDC_STATIC31,		},
	{	IDC_STATIC32,		},
	{	IDC_STATIC33,		},
	{	IDC_STATIC34,		},
	{	IDC_STATIC35,		},
	{	IDC_STATIC36,		},
	{	IDC_STATIC37,		},
	{	IDC_STATIC38,		},
	{	IDC_STATIC39,		},
	{	IDC_STATIC40,		},
	{	IDC_STATIC41,		},
	{	IDC_STATIC42,		},
	{	IDC_STATIC43,		},
	{	IDC_STATIC44,		},
	{	IDC_STATIC45,		},
	{	IDOK,		},
	{	IDCANCEL,		},
	{	-1,		},
};
#endif

 QY_DMITEM  CONST_dlg_mcClientLogon_ts[]  =
{
	{	IDC_STATIC_logonServer,	},
	{	IDC_STATIC_usrName,		},
	{	IDC_STATIC_passwd,		},
	{	IDC_BUTTON_option,		},
	{	IDC_CHECK_savePasswd,	},
	{	IDC_CHECK_autoLogon,	},
	{	IDOK,					},
	{	IDCANCEL,				},
	{	-1,				},
};
#if  0
#ifndef  __WINCE__
 QY_DMITEM	CONST_dlg_messenger_ts[]	=
{
	{	IDC_STATIC_hint1,		 },
	{	IDC_STATIC_messengerName,},   //  IDC_STATIC_staticName
	{	IDC_STATIC_passwd0,		},
	{	IDC_STATIC_passwd1,		},
	{	IDOK,					 },
	{	IDCANCEL,				 },
	{	-1,				},
};

 QY_DMITEM	CONST_dlg_messengerIsClient_ts[]	=
{
	{	IDC_STATIC_hint1,		 },
	{	IDC_STATIC_messengerName,},   //  IDC_STATIC_staticName
	{	IDC_STATIC_passwd0,		},
	{	IDC_STATIC_passwd1,		},
	{	IDOK,					 },
	{	IDCANCEL,				 },
	{	-1,				},
};

 QY_DMITEM  CONST_dlg_imObjRule_ts[]  =
{
	{	IDC_STATIC_hint_imObjRule,  },
	{	IDC_STATIC_autoAnswer_av,	 },
	{	IDC_STATIC_autoAnswer_screen,	 },
	{	IDC_STATIC_autoAnswer_mediaFile,	 },
	{	IDOK,					 },
	{	IDCANCEL,				 },
	{	-1,				},
};

#endif
#endif


#if  1  //  __APP_qyMc_touchscreen__
 QY_DMITEM  CONST_dlg_QYMC_TOUCHSCREEN_DIALOG[]  =
{
	{	IDC_BUTTON_contact,		},
	{	IDC_BUTTON_group,		},
	{	IDC_BUTTON_bar,		},
	{	IDCANCEL,				 },
	{	-1,						},
};

#if  0
 QY_DMITEM  CONST_dlg_menu_isCli_walls[]  =
{
	{	IDC_BUTTON_contact,				},
	{	IDC_BUTTON_group,				},
	{	IDC_BUTTON_fullScreen,			},
	{	IDC_BUTTON_testLocalAv,			},
	{	IDC_BUTTON_msg,					},
	{	IDC_BUTTON_policy,				},
	{	IDC_BUTTON_conferenceQuality,	},
	{	IDC_BUTTON_quit,				},
	{	IDC_BUTTON_about,				},
	{	IDCANCEL,						},
	{	-1,								},
};
#endif
#if  0
 QY_DMITEM  CONST_dlg_instantAssistant_ts[]  =
{
	{	IDC_BUTTON_msg,						},
	{	IDC_request,						},
	{	IDC_talkerList,						},
	{	IDC_COMBO_usLayoutType,				},
	{	IDC_BUTTON_av,						},
	{	IDC_BUTTON_av_accept,				},
	{	IDC_BUTTON_av_deny,					},
	{	IDC_BUTTON_shareScreen,				},
	{	IDC_BUTTON_msgBox,					},
	{	IDC_BUTTON_close,					},
	{	IDC_BUTTON_more,					},
	{	IDC_BUTTON_rule,					},
	{	IDC_STATIC_status,					},
	{	IDC_BUTTON_nonexclusive,			},
	{	-1,									},
};
#endif
#if  0
 QY_DMITEM  CONST_dlg_instantAssistant_start_ts[]  =
{
	{	IDC_BUTTON_av,						},
	{	IDC_BUTTON_av_accept,				},
	{	IDC_BUTTON_av_deny,					},
	{	IDC_BUTTON_shareScreen,				},
	{	IDC_BUTTON_msgBox,					},
	{	IDC_BUTTON_close,					},
	{	IDC_BUTTON_more,					},
	{	IDC_BUTTON_subtitles,				},		//  2013/04/05
	{	IDC_BUTTON_remoteVideo,				},		//  2013/02/15
	{	IDC_BUTTON_ptzPanel,				},		//  2013/02/15
	{	IDC_BUTTON_rule,					},
	{	IDC_BUTTON_msg,						},
	{	-1,									},
};

 QY_DMITEM	CONST_dlg_instantAssistant_av_ts[]  =
{
	{	IDC_request,						},
	{	IDC_talkerList,						},
	{	IDC_COMBO_usLayoutType,				},
	{	IDC_BUTTON_av,						},
	{	IDC_BUTTON_shareScreen,				},
	{	IDC_BUTTON_msgBox,					},
	{	IDC_BUTTON_close,					},
	{	IDC_BUTTON_more,					},
	{	IDC_BUTTON_subtitles,				},		//  2013/04/05
	{	IDC_BUTTON_remoteVideo,				},
	{	IDC_BUTTON_ptzPanel,				},		//  2013/02/15
	{	IDC_BUTTON_rule,					},
	{	IDC_STATIC_status,					},
	{	IDC_BUTTON_msg,						},
	{	IDC_BUTTON_nonexclusive,			},
	{	IDC_BUTTON_shareMediaFile,			},
	{	-1,									},
};


#endif

#endif

#if  0
  QY_DMITEM  CONST_dlg_policy_isClient_ts[]  =
{
	{	IDC_CHECK_ucbUseGlobalVWall,				},			//  2012/04/02
	//
	{	IDC_STATIC_staticRuleIfMsgArrive,			},
	{	IDC_STATIC_staticDirToSaveFile,				},
	{	IDC_BUTTON_browseDir,						},
#if  0
	{	IDC_CHECK_ucbOnlyNetSm,						},
	{	IDC_CHECK_ucbOnlyPhoneMsgr,					},
	{	IDC_STATIC_baud,							},
	{	IDC_CHECK_ucbPermitOtherSm,					},
#endif
	{	IDC_CHECK_showMsgBox,						},
	{	IDC_CHECK_showNotification,					},

	{	IDC_CHECK_ucbScrollForEnlagedImg,			},
	{	IDC_CHECK_ucbPreferCuda,					},					//  2012/06/25
	{	IDC_CHECK_ucbLooping_mediaFile,				},					//  2012/11/06

	{	IDC_STATIC_req,											},
	{	IDC_STATIC_reply,										},
/*
	{	IDC_STATIC_uiMinTimeInMsOfAudioDataPlaying,			},				//  2009/06/14
	{	IDC_STATIC_uiAudioDataAddedToPlayEveryTime,			},				//  2009/06/14
	{	IDC_STATIC_uiNotifyIntervalInMs_needMoreAudioData,	},				//  2009/06/14. = CONST_notifyInterval
	{	IDC_STATIC_uiMinTimeInMsToPlay,	},									//  2012/01/27
	{	IDC_STATIC_uiMaxTimeInMsToPlay,	},
	{	IDC_STATIC_uiMaxTimeInMsToBeRemoved,				},
*/
	
	{	IDC_STATIC_usTimeoutInMsToSwitch,	},
	{	IDC_STATIC_usTimeoutInMsToSwitch_rt,	},
	{	IDC_CHECK_ucbManullyPermitToSpeakOnVideoConference,		},
	{	IDC_BUTTON_videoConferenceCfg,							},
	{	IDC_STATIC_iTimeoutInMs_channelIdle,					},
	{	IDC_STATIC_usMax_nPlayers,					},			//  2012/03/30
	{	IDC_STATIC_usMax_nThreads_dec,				},			//  2012/03/30
	{	IDC_STATIC_uiMaxQNodes_vwRuleQ,				},			//  2012/03/30
	//
	{	IDC_BUTTON_avCompressor_req,						},	
	{	IDC_BUTTON_avCompressor_reply,						},	
	{	IDC_BUTTON_screenCompressor,						},	
	{	IDC_BUTTON_mediaFileCompressor,						},
	{	IDC_BUTTON_mediaDeviceCompressor,					},
	{	IDC_BUTTON_webcamCompressor,						},
	//
	{	IDC_BUTTON_restoreDefaultSettings,						},
	{	IDOK,													},
	{	IDCANCEL,												},
	{	-1,		},
};

   QY_DMITEM  CONST_dlg_policyAv_ts[]  =  
{
	{	IDC_STATIC_req,											},
	{	IDC_STATIC_reply,										},

	{	IDC_BUTTON_setLdSettings,							},
	{	IDC_BUTTON_setLd1Settings,							},			//  2012/03/16
	{	IDC_BUTTON_setSdSettings,							},
	{	IDC_BUTTON_setSd1Settings,							},
	{	IDC_BUTTON_setSd2Settings,							},			//  2012/03/16
	{	IDC_BUTTON_setSd3Settings,							},			//  2012/03/16
	{	IDC_BUTTON_setHdSettings,							},
	{	IDC_BUTTON_setHd1Settings,							},
	{	IDC_BUTTON_setHd2Settings,							},
	{	IDC_BUTTON_setHd3Settings,							},
	{	IDC_BUTTON_setFullHdSettings,							},
	{	IDC_BUTTON_setFullHd1Settings,							},
	{	IDC_BUTTON_setFullHd2Settings,							},
	{	IDC_BUTTON_setFullHd3Settings,							},
	{	IDC_BUTTON_setDev2fpsSettings,							},
	{	IDC_BUTTON_setDev5fpsSettings,							},
	{	IDC_BUTTON_setDev5fpsSettings1,							},
	{	IDC_BUTTON_setDev5fpsSettings2,							},
	{	IDC_BUTTON_setDev5fpsSettings3,							},
	{	IDC_BUTTON_setDev5fpsSettings4,							},			//  2013/04/13
	{	IDC_BUTTON_setDev5fpsSettings5,							},
	{	IDC_BUTTON_setDev10fpsSettings,							},			//  2012/11/03
	{	IDC_BUTTON_setDevSd24fpsSettings,						},			//  2012/11/03
	{	IDC_BUTTON_setDevSd25fpsSettings,						},			//  2012/11/03
	{	IDC_BUTTON_setDevSd30fpsSettings,						},			//  2012/11/03
	{	IDC_BUTTON_setDev24fpsSettings,							},
	{	IDC_BUTTON_setDev25fpsSettings,							},
	{	IDC_BUTTON_setDev30fpsSettings,							},
	//
	{	IDC_STATIC_iWidth,								},
	{	IDC_STATIC_iHeight,								},
	{	IDOK,													},
	{	IDCANCEL,												},
	{	-1,		},

};

 QY_DMITEM  CONST_dlg_videoCompressors_ts[]  =
{

	{	IDC_STATIC_audio,													},
	{	IDC_STATIC_defaultFmt,									},
	{	IDC_STATIC_uiBytesRecorded_perBlockAlign,	},
	{	IDC_STATIC_audioCompressor,								},
	{	IDC_STATIC_audioOutputType,									},

	{	IDC_STATIC_audioPlayCfg,							},
	{	IDC_STATIC_uiMinTimeInMsOfAudioDataPlaying,			},				//  2009/06/14
	{	IDC_STATIC_uiAudioDataAddedToPlayEveryTime,			},				//  2009/06/14
	{	IDC_STATIC_uiNotifyIntervalInMs_needMoreAudioData,	},				//  2009/06/14. = CONST_notifyInterval
	{	IDC_STATIC_uiMinTimeInMsToPlay,	},									//  2012/01/27
	{	IDC_STATIC_uiMaxTimeInMsToPlay,	},
	{	IDC_STATIC_uiMaxTimeInMsToBeRemoved,				},

	{	IDC_STATIC_video,													},
	{	IDC_STATIC_videoCompressor,								},
	{	IDC_STATIC_videoOutputType,									},
	{	IDC_STATIC_videoEffect,								},				//  2012/02/08
	{	IDC_STATIC_avgBitrate,								},				//  2012/06/27

	{	IDC_STATIC_ucSeconds_perFrame,						},
	{	IDC_STATIC_usMaxFPS_toShareBmp,						},
	{	IDC_STATIC_usMinFps_toShareBmp,						},
	{	IDC_STATIC_iWidth,									},
	{	IDC_STATIC_iHeight,									},
	{	IDC_BUTTON_cfgWmv,							},

	{	IDOK,									},
	{	IDCANCEL,								},
	{	-1,			},
};
#endif
#if  0
 QY_DMITEM  CONST_dlg_cfgVideoConference_ts[]  =
{
	{	IDC_STATIC_conference_row,				},
	{	IDC_STATIC_conference_col,				},
	{	IDC_STATIC_usCntLimit_activeMems_from,	},
	{	IDC_STATIC_iWidth,						},
	{	IDC_STATIC_iHeight,						},
	{	IDC_CHECK_bUseAec,						},
	{	IDOK,									},
	{	IDCANCEL,								},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_progress_ts[]  =
{

	{	IDC_STATIC_progress,	},
	{	IDOK,					},
	{	IDCANCEL,				},
	{	-1,				},
};

 QY_DMITEM  CONST_dlg_msgList_ts[]  =
{
	{	IDC_BUTTON_export,		},
	{	IDC_BUTTON_clear,		},
	{	IDCANCEL,				},
	{	-1,						},

};

 QY_DMITEM  CONST_dlg_objs_ts[]  =
{
	{	IDOK,					},
	{	IDCANCEL,				},
	{	-1,				},
};

 QY_DMITEM  CONST_dlg_test_ts[]  =
 {
	 {	IDC_BUTTON_aDev,		},
	 {	IDC_BUTTON_vDev,		},
	 {  IDC_BUTTON_cfgCapturePin_v,  },
	 {	IDC_BUTTON_testAv,	},
	 {	IDCANCEL,			},
	 {	-1,					},
 };

QY_DMITEM  CONST_dlg_ptzControl_ts[]  =
{
	{	IDC_BUTTON_ptzSettings,	},
	{	IDC_STATIC_speed,		},

	{	IDC_BUTTON_UP,			},	
	{	IDC_BUTTON_DOWN,		},	
	{	IDC_BUTTON_LEFT,		},	
	{	IDC_BUTTON_RIGHT,		},	
	{	IDC_BUTTON_TOP_LEFT,	},	
	{	IDC_BUTTON_TOP_RIGHT,	},	
	{	IDC_BUTTON_BOTTOM_LEFT,	},	
	{	IDC_BUTTON_BOTTOM_RIGHT,},	
	{	IDC_BUTTON_noop,		},
	{	IDC_BUTTON_FOCUS_IN,	},	
	{	IDC_STATIC_focus,		},	
	{	IDC_BUTTON_FOCUS_OUT,	},	
	{	IDC_BUTTON_IRIS_IN,		},	
	{	IDC_STATIC_iris,		},	
	{	IDC_BUTTON_IRIS_OUT,	},	
	{	IDC_BUTTON_ZOOM_IN,		},	
	{	IDC_STATIC_zoom,		},	
	{	IDC_BUTTON_ZOOM_OUT,	},	

	{	IDC_STATIC_preset,		},
	{	IDC_BUTTON_PRE_GO,		},
	{	IDC_BUTTON_PRE_SET,		},
	{	IDC_BUTTON_PRE_CLEAR,	},
	{	IDCANCEL,				},

	{	-1,						},
};

QY_DMITEM  CONST_dlg_ptzSettings_ts[]  =
{
	{	IDC_STATIC_comPtz,		},
	{	IDC_STATIC_comName,		},
	{	IDC_STATIC_comBaud,		},
	{	IDC_STATIC_comParity,	},
	{	IDC_STATIC_comData,		},
	{	IDC_STATIC_comStopBit,	},
	{	IDC_STATIC_ptzProtocal,	},
	{	IDC_STATIC_ptzAddr,		},
	{	IDC_STATIC_remotePtz,	},
	{	IDC_STATIC_remoter,		},
	{	IDC_STATIC_memoAppending,	},
	{	IDC_EDIT_memoAppending,	},

	{	IDOK,					},
	{	IDCANCEL,				},

	{	-1,						},
};

QY_DMITEM  CONST_dlg_videoSubtitlesCfg_ts[]  =
{

	{	IDC_CHECK_showVideoHint,				},
	{	IDC_CHECK_effectiveImmediately,			},

	{	IDC_BUTTON_useDefault,					},
	{	IDC_BUTTON_file,						},
	{	IDC_BUTTON_subtitlesSettings,			},

	{	IDC_STATIC_subtitle0,					},
	{	IDC_EDIT_subtitle0,						},

	{	IDC_EDIT_subtitle1,						},
	{	IDC_STATIC_subtitle1,					},

	{	IDC_EDIT_subtitle2,						},
	{	IDC_STATIC_subtitle2,					},

	{	IDC_EDIT_subtitle3,						},
	{	IDC_STATIC_subtitle3,					},

	{	IDC_EDIT_subtitle4,						},
	{	IDC_STATIC_subtitle4,					},

	{	IDC_EDIT_subtitle5,						},
	{	IDC_STATIC_subtitle5,					},

	{	IDC_EDIT_subtitle6,						},
	{	IDC_STATIC_subtitle6,					},

	{	IDC_EDIT_subtitle7,						},
	{	IDC_STATIC_subtitle7,					},

	{	IDC_EDIT_subtitle8,						},
	{	IDC_STATIC_subtitle8,					},
	
	{	IDC_EDIT_subtitle9,						},
	{	IDC_STATIC_subtitle9,					},
	
	{	IDC_EDIT_subtitle10,					},							
	{	IDC_STATIC_subtitle10,					},

	{	IDC_EDIT_subtitle11,					},
	{	IDC_STATIC_subtitle11,					},

	{	IDOK,									},
	{	IDC_BUTTON_emptyTxt,					},
	{	IDCANCEL,								},

	{	-1,						},
};

QY_DMITEM  CONST_dlg_subtitleSelect_ts[]  = 
{

	{	IDC_BUTTON_selectFont,					},
	{	IDC_CHECK_displayTime,					},
	{	IDC_CHECK_bottomUp,					},

	{	IDC_STATIC_staticMaskColor,				},	
	{	IDC_STATIC_xyStart,						},

	{	IDC_CHECK_3dShadow,					},
	{	IDC_STATIC_shadowOffset,			},

	{	IDOK,					},
	{	IDCANCEL,				},

	{	-1,						},

};
#endif

 QY_DMITEM  CONST_dlgTable_ts[]  =
{
#if  0
#ifndef  __WINCE__
	//  2005/11/09
	{	IDD_ABOUTBOX,						(  TCHAR  *  )CONST_dlg_aboutBox_ts,					(  TCHAR  *  )CONST_resId_IDD_ABOUTBOX,					},
#endif
#endif
#if  0
	//  {	IDD_policy_isClient,				(  TCHAR  *  )CONST_dlg_policy_isCli_ts,	},
	{	IDD_talk,							(  TCHAR  *  )CONST_dlg_talk_ts,						},
	{	IDD_desktopsMon,					(  TCHAR  *  )CONST_dlg_desktopsMon_ts,				},
	{	IDD_cfgVideoConference,				(  TCHAR  *  )CONST_dlg_cfgVideoConference_ts,			},
	{	IDD_videoCompressors,				(  TCHAR  *  )CONST_dlg_videoCompressors_ts,			},
	{	IDD_progress,						(  TCHAR  *  )CONST_dlg_progress_ts,					},
#ifndef  __WINCE__
	{	IDD_messenger_isClient,				(  TCHAR  *  )CONST_dlg_messenger_ts,					},
	{	IDD_imObjRule,						(  TCHAR  *  )CONST_dlg_imObjRule_ts,					},
#endif
#endif
	//

#if  1  //  __APP_qyMc_touchscreen__
	//  {	IDD_QYMC_TOUCHSCREEN_DIALOG,		(  TCHAR  *  )CONST_dlg_QYMC_TOUCHSCREEN_DIALOG,			},
	{	IDD_ts_main,						(  TCHAR  *  )CONST_dlg_QYMC_TOUCHSCREEN_DIALOG,			},

	{	IDD_mcClient_logon,					(  TCHAR  *  )CONST_dlg_mcClientLogon_ts,					},

	{	IDD_qnmCfgOptions_isClient,			(  TCHAR  *  )CONST_dlg_qnmCfgOptions_isCli_ts,		},


#endif  

	{	-1,		},
};

