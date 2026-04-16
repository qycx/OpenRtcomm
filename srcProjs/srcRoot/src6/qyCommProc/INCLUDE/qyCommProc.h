

#ifndef  __QYCOMMPROC_H__
#define  __QYCOMMPROC_H__	/*  {  */




#define		CONST_qnmStatusToolWndClass							_T(  "QycxStatusToolCls"  )			//  2006/08/16
#define		CONST_qnmStatusToolWndClass_client					_T(  "QycxStatusToolCls_cli"  )		//  2006/08/16
#define		CONST_qnmStatusWndTitle								_T(  "Qycx Monitor"  )				//  _T(  "???? - ????"  )
#define		CONST_qnmStatusWndTitle_client						_T(  "Qycx Monitor - client"  )		//  _T(  "???? - ????"  )
#define		CONST_qnmWarningWndTitle							_T(  "Qycx Warning Tool"  )			//  
//
#define		CONST_qnmStopPcWndTitle								"qnmStopPc"


#define		CONST_statusPipeName_serv_pipeServ				_T(  "\\\\.\\pipe\\qyStatusPipe_serv"  )	//  2009/04/04
#define		CONST_statusPipeName_cli_pipeServ				_T(  "\\\\.\\pipe\\qyStatusPipe_cli"  )	//  2009/04/04
//
#define		CONST_statusPipeName_serv_pipeCli				_T(  "\\\\127.0.0.1\\pipe\\qyStatusPipe_serv"  )	//  2009/04/04
#define		CONST_statusPipeName_cli_pipeCli				_T(  "\\\\127.0.0.1\\pipe\\qyStatusPipe_cli"  )	//  2009/04/04

//
#define		MAX_pipeServ_idleInMs							10000
#define		MAX_pipeCli_idleInMs							5000



//  #define		CONST_shmName_qmdStatus_netMc					_T(  "QmdStatusShm_netMc"  )		//  2010/10/01
//  #define		CONST_shmName_qmdStatus_is						_T(  "Global\\QmdStatusShm_is"  )	//  2010/10/01

//
#define		DEFAULT_qwmMutexName								"qwmMutex"  						//  qwmSvr.exe???????mutex
#define		DEFAULT_qnmProxyMutexName							"qnmProxyMutex"  
#define		QY_INTERNET_MC_MUTEX_NAME							"qyInterMcMutex"  
//  #define		QY_MTSOCK_SUBTHREAD_MUTEX						"qwmMutex"  
//  #define		CONST_qyMtSockSubThreadMutex					"qwmMutex"  
#define		CONST_qyMtSockSubThreadMutexName					"qyMtMutex"  						//  mtSock????mutex, ?????qwmSvr?mutex??????
#define		CONST_qyMtSockSubThreadMutexName_mis				"qyMtMutex_mis"  					//  mis????mtSock????mutex, 2007/03/21
//  #define		CONST_qnmProxyShowStatusMutexName				"qnmProxyMtMutex"					//  qnmProxy?showStatus????mutex
#define		DEFAULT_qwmMutexName_syncNetShare					"qwmMutex_syncNetShare"  			//  ???????????2007/02/16
#define		DEFAULT_qwmMutexName_syncLogEvent					"qwmMutex_syncLogEvent"  			//  ???????????2007/02/18

//
#define		CONST_mutexPrefix_mcClientLogon						"mcClientLogon"						//  2010/07/21


//
#define		CONST_maxCnt_sema_syncQmObjQ						10									//  qmObjQ
//
#define		DEFAULT_mutexName_syncQmObjQ						_T(  "m_syncQmObjQ"  )
#define		DEFAULT_semaphoreName_syncQmObjQ					_T(  "sema_syncQmObjQ"  )
//
#define		DEFAULT_mutexName_syncQmObjQ_client					_T(  "m_syncQmObjQ_cli"  )			//  2007/06/03
#define		DEFAULT_semaphoreName_syncQmObjQ_client				_T(  "sema_syncQmObjQ_cli"  )		//  2007/06/03
//
#define		DEFAULT_mutexNamePrefix_syncTask					_T(  "m_syncTask"  )				//  2007/06/27, mutex, prefix + misServName  +  id_send

#define		CONST_mutexName_syncTmpMemroy_is					_T(  "syncTmpMem_is"  )				//	2010/09/16

#define		CONST_mutexNamePrefix_syncModifyQm					_T(  "syncModifyQm"  )				//  2011/04/17

//  
//  #define		CONST_uiMaxQNodes_showInfoQ_is						8000								//  
#define		CONST_uiMaxQNodes_showInfoQ_is_mgr					5000								//  2014/05/12
#define		CONST_uiMaxQNodes_showInfoQ_state_is_mgr			1000								//  2015/08/22

//
#define		CONST_uiMaxQNodes_showInfoQ_is_cli					3500								//  2014/05/12
#define		CONST_uiMaxQNodes_showInfoQ_state_is_cli			1000								//  2015/08/22


//
#define		DEFAULT_qyMc_minPasswdLen							8
#define		MIN_qyMc_passwdLen									8
#define		DEFAULT_qyMc_maxInvalidLogonAttempts				3
#define		MAX_qyMc_invalidLogonAttempts						5


//  2011/01/30
//  #define		CONST_dataBufSize_iocp							8192			//  
//  #define		CONST_dataBufSize_iocp							16384			//  
//  #define		CONST_dataBufSize_iocp							65  *  1024		//  2011/01/31
//#define		CONST_dataBufSize_iocp								129  *  1024	//  2011/02/13
#define		CONST_dataBufSize_iocp								513  *  1024	//  2022/03/08


//
#define		CONST_qyRootKey_qwpm								"Software\\Qycx\\Wpm"  
	#define		CONST_qwpmKey_list									"Software\\Qycx\\Wpm\\Lst"  
		#define		CONST_regValName_qwpmS10						  "S10"  
			#define		CONST_regValData_qwpmS10						  "Scheduler"  
		#define		CONST_regValName_qwpmS11						  "S11"  
			#define		CONST_regValData_qwpmS11						  "Daemon"  
		#define		CONST_regValName_qwpmS12						  "S12"  
			#define		CONST_regValData_qwpmS12						  "Resp"  
		#define		CONST_regValName_qwpmS13						  "S13"  
			#define		CONST_regValData_qwpmS13						  "HttpSvr"  
		#define		CONST_regValName_qwpmS14						  "S14"  
			#define		CONST_regValData_qwpmS14						  "intraMon"  
		#define		CONST_regValName_qwpmS15						  "S15"  						//  2004/06/18??
			#define		CONST_regValData_qwpmS15						  "interMon"  			//  2004/06/18??
		#define		CONST_regValName_qwpmS16						  "S16"  						//  2004/06/18??
			#define		CONST_regValData_qwpmS16						  "interMonTool"  		//  2004/06/18??
		#define		CONST_regValName_qwpmS17						  "S17"  						//  2007/06/13
			#define		CONST_regValData_qwpmS17						  "misDaemon"  			//  2007/06/13
		#define		CONST_regValName_qwpmS18						  "S18"  						//  2007/06/13
			#define		CONST_regValData_qwpmS18						  "misScheduler"  		//  2007/06/13


//  #define		CONST_qyRootKey_modulesSecChk				(  "Software\\Qycx\\qwm\\Modules\\secChk"  )
// 	#define		CONST_regValName_modulesSecChk_tomato		(  "tomato"  )


#define		CONST_qyRootKey_mc								"Software\\Qycx\\Qwm"	 
#define		CONST_qyRootKey_mc_mis							"Software\\Qycx\\Mis"					//  2007/12
#define		QY_MC_ROOTKEY									CONST_qyRootKey_mc 
	#define		CONST_qyRootKey_mcGui_netMc						"Software\\Qycx\\Qwm\\Gui"
	#define		CONST_qyRootKey_mcGui_mis						"Software\\Qycx\\Mis\\Gui"  
	#define		CONST_qyRootKey_mcGui_misClient					"Software\\Qycx\\MisClient\\Gui"  
		#define		CONST_regValName_qrtTitle						"qrtTitle"
		#define		CONST_regValName_qrtHint						"qrtHint"
		#define		CONST_regValName_appType						"appType"  
		#define		CONST_regValName_bhbAppType						"bhbAppType"  
		//  2016/08/10
		#define		CONST_regValName_clientWelcomeMsg				"clientWelcomMsg"
		// 
	#define		CONST_qyRootKey_qmd_netMc						"Software\\Qycx\\Qwm\\Daemon"  
	#define		CONST_qyRootKey_qmd_mis							"Software\\Qycx\\Mis\\Daemon"  
	#define		QY_MCDAEMON_FORBAR_ROOTKEY						"Software\\Qycx\\Qwm\\DaemonForBar"  
		#define		QY_SERVIP_VALNAME						 		"server"  
		#define		QY_CNTIP_VALNAME						 	CONST_regValName_cntIp
		#define		QY_GLCNTIP_VALNAME								"glCnt"  
	#define		CONST_qyRootKey_qnmScheduler					"Software\\Qycx\\Qwm\\Scheduler"  
	#define		CONST_qyRootKey_qnmScheduler_misClient			"Software\\Qycx\\misClient\\Scheduler"  
	#define		CONST_qyRootKey_qnmScheduler_mis				"Software\\Qycx\\mis\\Scheduler"  
		#define		CONST_regValName_dbTypeName						"dbType"  
		#define		CONST_regValName_connectStr						"uuulj"  
		#define		CONST_regValName_procedSysStr					"qyProcedSys"  			//  2006/12/18
		#define		CONST_regValName_domainSvrIp				"domainSvrIp"
		#define	    AWM_CHK_NT_LOGON_SCRIPT_PATH_KEY				"scriptsPath"  
		#define	    AWM_CHK_NT_LOGON_SCRIPT_NAME_KEY				"script"  
		#define	    AWM_CHK_WIN2K_STARTUP_SCRIPT_PATH_KEY			"scriptsPath"  
		#define	    AWM_CHK_WIN2K_STARTUP_SCRIPT_NAME_KEY			"script"  
		#define		CONST_regValName_stopScripts				"stopScripts"				//  ????????
		#define	    AWM_CHK_STOP_SCRIPT_KEY						CONST_regValName_stopScripts
		#define		CONST_regValName_stopAutoReg				"stopAutoReg"				//  ??????
		#define		CONST_regValName_stopMon					"sangwang"				//  ???????
		#define		CONST_regValName_startIpScan				"startIpScan"				//  ??IP????
		#define		CONST_regValName_stopWatchIp				"stopWatchIp"				//  ????IP??
		#define		CONST_regValName_startRegScan				"startRegScan"			//  ??????
		#define		CONST_regValName_startRespForUnreg			"startRespForUnreg"		//  ????????????
		#define		CONST_regValName_stopDownPortIfMacChanged	"stopDownPortIfMacChanged"//  2005/03/06	
		#define		CONST_regValName_stopDownPortIfWarnSpeed	"stopDownPortIfWarnSpeed"	//  2006/05/29
		#define		CONST_regValName_stopFileMon				"stopFileMon"				//  2006/03/22
		#define		CONST_regValName_stopModuleMon				"stopModuleMon"			//  2006/04/17
		#define		CONST_regValName_stopPcRegistryMon			"stopPcRegistryMon"		//  2006/08/15
		#define		CONST_regValName_startUpdate				"startUpdate"             //  2003/09/13        
		#define		CONST_regValName_stopSnmpScan				"stopSnmpScan"
		#define		CONST_regValName_stopNbtScan				"stopMacScan"
		#define		CONST_regValName_stopSnmpNetFlow			"stopSnmpNetFlow"

		//  #define		CONST_regValName_cntIp						"cnt"  
		#define		CONST_regValName_cntIp						CONST_qyCfgName_cntIp						
		#define		CONST_regValName_cntPort					CONST_qyCfgName_cntPort			//  "cntPt"  
		#define		CONST_regValName_cntName					"cntName"						//  2010/02/17
		#define		CONST_regValName_bSelected					"bSelected"						//  2010/02/17
		#define		CONST_regValName_bNotAutoCntIp				"bNotAutoCntIp"  				//  ??????????IP, 2006/06/29
		//  #define		CONST_regValName_cntAddr1					"cntAddr1"						//  ??????1,  2006/06/29
		//  #define		CONST_regValName_cntAddr2					"cntAddr2"  					//  ??????2,  2006/06/29
		//  #define		CONST_regValName_cntAddr3					"cntAddr3"						//  ??????3,  2006/06/29
		#define		CONST_regValName_cntAddr					"cntAddr"
		#define		CONST_regValName_cntAddr1					CONST_qyCfgName_cntAddr1
		#define		CONST_regValName_cntAddr2					CONST_qyCfgName_cntAddr2
		#define		CONST_regValName_bNotUseDb					"bNotUseDb"						//  2013/02/21

		#define		CONST_regValName_usr						"usr"							//  2010/07/28
		#define		CONST_regValName_passwd						"passwd"
		//
		#define		CONST_regValName_ucbSavePasswd				"ucbSavePasswd"
		#define		CONST_regValName_ucbAutoLogon				"ucbAutoLogon"					//  2019/04/08

		//
		#define		CONST_regValName_caGwIp						"caGwIp"

		//
		#define		CONST_regValName_regToolDir					"regToolDir"  
		//  
		#define		CONST_regValName_interMonIp					"monIp"  
		#define		CONST_regValName_interMonPort				"monPt"  
		//
		#define		CONST_regValName_skippedMac0				"skippedMac0"  
		#define		CONST_regValName_skippedMac1				"skippedMac1"  
		#define		CONST_regValName_skippedMac2				"skippedMac2"  
		#define		CONST_regValName_skippedMac3				"skippedMac3"  
		#define		CONST_regValName_skippedMac4				"skippedMac4"  
		//
		#define		CONST_regValName_bNotAllAllowed				"bNotAllAllowed"  
		#define		CONST_regValName_rasCmd						"yx"  
		#define		CONST_regValName_ucWLanAdapterCmd			"ucWLanAdapterCmd"					//  2010/05/20
		#define		CONST_regValName_ucBlueToothCmd				"ucBlueToothCmd"					//  2010/08/18
		#define		CONST_regValName_ucInfraredCmd				"ucInfraredCmd"						//  2010/08/18
		#define		CONST_regValName_uc1394Cmd					"uc1394Cmd"							//  2010/08/18
		#define		CONST_regValName_ucWpdCmd					"ucWpdCmd"							//  2011/08/26
		#define		CONST_regValName_ucSdHostAdapterCmd			"ucSdHostAdapterCmd"				//  2011/08/26
		#define		CONST_regValName_ucMobileDeviceCmd			"ucMobileDeviceCmd"					//  2011/08/26
		#define		CONST_regValName_ucUsbNetworkCardCmd		"ucUsbNetworkCardCmd"				//  2011/09/18



		#define		CONST_regValName_floppyCmd					"floppyCmd"  
		#define		CONST_regValName_cdromCmd					"cdromCmd"  
		#define		CONST_regValName_usbStorCmd					"usbStorCmd"  
		#define		CONST_regValName_bNotChkOnInternet			"bNotChkOnInternet"  
		#define		CONST_regValName_autorunCmd					"autorunCmd"  						//  2007/02/12
		#define		CONST_regValName_netShareCmd				"netShareCmd"  						//  2007/02/12
		#define		CONST_regValName_safeModeCmd				"safeMode"  						//  2005/06/25
		#define		CONST_regValName_adminCmd					"adminCmd"  						//  2007/02/12
		#define		CONST_regValName_ucHideQwmCmd				"ucHideQwmCmd"  					//  2007/02/20

		//  2009/03/05
		#define		CONST_regValName_minPasswdLen				"minPasswdLen"  
		#define		CONST_regValName_maxInvalidLogonAttempts	"maxInvalidLogonAttempts"  

		//  is 
		//  Identify auth
		#define		CONST_regValName_ucbUseMac						"ucbUseMac"  						//  2007/9/19
		#define		CONST_regValName_ucbUsePcName					"ucbUsePcName"  
		#define		CONST_regValName_ucbUseDomainName				"ucbUseDomainName"  	
		#define		CONST_regValName_ucbUseOsUsrName				"ucbUseOsUsrName"  
	    //
		#define		CONST_regValName_ucbUseMessengerName			"ucbUseMessengerName"  
		//
		#define		CONST_regValName_ucbAutoVerification			"ucbAutoVerification"  			//  
		//
		#define		CONST_regValName_ucbNeedValidIpForDevice		"ucbNeedValidIpForDevice"
		#define		CONST_regValName_startIp_device					"startIp_device"
		#define		CONST_regValName_endIp_device					"endIp_device"

		//  manage rule
		//
		#define		CONST_regValName_ucbRunAsAdvertisingPlayer				"ucbRunAsAdvertisingPlayer"			//  2013/11/14
		#define		CONST_regValName_ucbUseGlobalVWall						"ucbUseGlobalVWall"					//  2012/04/02
		//
		#define		CONST_regValName_dlgShareDynBmps_autopopupandhideOnStartup		"_dlgShareDynBmps_ucbAutoPopupAndHideOnStartup"				//  2016/06/09

		//
		#define		CONST_regValName_ruleIfMsgArrive			"ruleIfMsgArrive"		 			//  2007/09/08
		#define		CONST_regValName_dirToSaveFile				"dirToSaveFile"  
        #define		CONST_regValName_dirToSaveICFile			"dirToSaveICFile"
        #define		CONST_regValName_isSaveICFile			    "isSaveICFile"
		#define		CONST_regValName_ucbSaveMsg					"ucbSaveMsg"						//  2014/04/27
		#define		CONST_regValName_dirToSaveMsg				"dirToSaveMsg"						//  2014/04/27

		//
		#define		CONST_regValName_sm_loopCtrl				"sm_loopCtrl"
        #define		CONST_regValName_sm_memOverTimes			"sm_memOverTimes"

		//
		#define		CONST_regValName_timeOfVideoFileInS			"timeOfVideoFileInS"					//  2014/08/03
		#define		CONST_regValName_dirToSaveVideo				"dirToSaveVideo"					//  2014/08/03

		//
		#define		CONST_regValName_ucbLogImMsg				"ucbLogImMsg"  						//  2007/09/12
		#define		CONST_regValName_ucbOnlyNetSm				"ucbOnlyNetSm"  					//  2008/02/11
		#define		CONST_regValName_ucbOnlyPhoneMsgr			"ucbOnlyPhoneMsgr"					//  2008/02/11
		//
		#define		CONST_regValName_ucHardwareAccl				"ucHardwareAccl"		 			//  2014/03/29
		#define		CONST_regValName_ucHardwareAccl_qt			"ucHardwareAccl_qt"		 			//  2014/03/29
		//
		#define		CONST_regValName_ucbNotUseDmo				"ucbNotUseDmo"							//  2012/02/23
		//
		#define		CONST_regValName_camCapDll					"camCapDll"							//  2010/08/03


		//
		#define		CONST_regValName_startMcuId					"startMcuId" 
		#define		CONST_regValName_cntofMcus					"cntofMcus"
		#define		CONST_regValName_mcuUsrName					"mcuUsrName"
		#define		CONST_regValName_mcuPasswd					"mcuPasswd"
		#define		CONST_regValName_mcuDomainName				"mcuDomainName"

		//
		#define		CONST_regValName_audioCompressors										"audioCompressors"					//  2009/03/16
		#define		CONST_regValName_audioCompressorName									"audioCompressorName"				//  2008/03/14
		//#define		CONST_regValName_audioCompressor									"audioCompressor"					//  2009/05/23

		#define		CONST_regValName_wfx_enc_wFormatTag										"wfx_enc_wFormatTag"  				//  2008/03/14
		#define		CONST_regValName_wfx_enc_nChannels										"wfx_enc_nChannels"  				//  2008/03/14
		#define		CONST_regValName_wfx_enc_nSamplesPerSec									"wfx_enc_nSamplesPerSec"			//  2008/03/14
		#define		CONST_regValName_wfx_enc_nAvgBytesPerSec								"wfx_enc_nAvgBytesPerSec"			//  2008/03/14
		#define		CONST_regValName_wfx_enc_wBitsPerSample									"wfx_enc_wBitsPerSample"			//  2008/03/14
		//  
		#define		CONST_regValName_uiMinTimeInMsOfAudioDataPlaying						_T(  "uiMinTimeInMsOfAudioDataPlaying"  )				//  2009/06/14
		#define		CONST_regValName_uiAudioDataAddedToPlayEveryTime						_T(  "uiAudioDataAddedToPlayEveryTime"  )				//  2009/06/14
		#define		CONST_regValName_uiNotifyIntervalInMs_needMoreAudioData					_T(  "uiNotifyIntervalInMs_needMoreAudioData"  )		//  2009/06/14. = CONST_notifyInterval
		#define		CONST_regValName_uiMinTimeInMsToPlay									_T(  "uiMinTimeInMsToPlay"  )							//  2012/01/27
		#define		CONST_regValName_uiMaxTimeInMsToPlay									_T(  "uiMaxTimeInMsToPlay"  )							//  2009/06/03
		#define		CONST_regValName_uiMaxTimeInMsToBeRemoved								_T(  "uiMaxTimeInMsToBeRemoved"  )						//  2009/06/03

		#define		CONST_regValName_noPrompt_selAvCompressor								_T(  "noPrompt_selAvCompressor"  )					//  2014/04/08
		#define		CONST_regValName_noPrompt_selConfCtrl									_T(  "noPrompt_selConfCtrl"  )						//  2017/07/19

		//
		#define		CONST_regValName_policyAvLevel_req										_T(  "policyAvLevel_req"  )			//  2011/08/07
		//  
		//
		#define		CONST_regValName_useBgWall												_T(  "useBgWall"  )
		#define		CONST_regValName_ucbAddBgWallToConf										_T(  "ucbAddBgWallToConf"  )
		#define		CONST_regValName_ucbJoinInBgWall										_T(  "ucbJoinInBgWall"  )
		#define		CONST_regValName_ucbAutoLayout											_T(  "ucbAutoLayout"  )
		#define		CONST_regValName_bgWallFileName											_T(  "bgWallFileName"  )
		//
		#define		CONST_regValName_ucbNeverJoinInBgWall 									_T(  "NeverJoinInBgWall"  )
		#define		CONST_regValName_usPollingIntervalInS									_T(  "pollingIntervalsInS"  )
		#define		CONST_regValName_layout													_T(  "layout"  )

		//  2017/06/25
		#define		CONST_regValName_ucbConfCtrl_starter									_T(  "ucbConfCtrl_starter"  )		//  2017/06/25

		//
		#define		CONST_regValName_ucb2Streams											_T(  "ucb2Streams")

		//
		#define		CONST_regValName_ucb100k												_T(  "ucb100k"  )

		//
		#define		CONST_regValName_bLyra													_T(  "bLyra"  )



		//
		#define		CONST_regValName_ucbSetDevResolution									"ucbSetDevResolution"				//  2014/04/26
		#define		CONST_regValName_iDevWidth												"iDevWidth"
		#define		CONST_regValName_iDevHeight												"iDevHeight"

		//
		#define		CONST_regValName_videoCompressors										"videoCompressors"  				//  2009/03/16
		#define		CONST_regValName_videoCompressorName									"videoCompressorName"				//  2008/03/14
		#define		CONST_regValName_v_fourccStr											"v_fourccStr"						//  2017/10/08

		//
		#define		CONST_regValName_videoEffect											"videoEffect"						//  2012/02/08
		#define		CONST_regValName_avgBitrate												"avgBitrate"						//  2012/06/27
		//
		#define		CONST_regValName_usMaxFps_toShareBmp									"usMaxFps_toShareBmp"				//  2008/12/06
		#define		CONST_regValName_usMinFps_toShareBmp									"usMinFps_toShareBmp"  				//  2009/12/06

		#define		CONST_regValName_ucSeconds_perFrame										"ucSeconds_perFrame"				//  2012/07/01

		//
		#define		CONST_regValName_conf_fourcc											"conf_fourcc"
		#define		CONST_regValName_conf_usMaxSpeakers										"conf_usMaxSpeakers"
		#define		CONST_regValName_conf_bitrateInKbps_dl									"conf_bitrateInKbps_dl"
		#define		CONST_regValName_conf_bitrateInKbps_ul									"conf_bitrateInKbps_ul"
		//
		#define		CONST_regValName_conf_usMaxFps_toShareBmp								"conf_usMaxFps_toShareBmp"
		#define		CONST_regValName_conf_ucb100k											"conf_usb100k"




		//
		//#define		CONST_regValName_2ndMcu													"str2ndMcu"

		//
		#define    CONST_regFilePath_select													"select_file_path"	
	
		//
		#define		CONST_regValName_installDate_show										"installDate"						//  2010/03/21

		#define		CONST_regValName_camCapType												"camCapType"						//  2010/07/28
		#define		CONST_regValName_recordType												"recordType"						//  2010/08/02

		//
		#define		CONST_regValName_ucbNot_selectDefaultRecorder							"ucbNot_selectDefaultRecorder"				//  2014/07/31

		#define		CONST_regValName_offlineResServDir										"offlineResServerDir"  

		//
		#define		CONST_regValName_bUseManuallySetResServId								"bUseManuallySetResServId" 
		#define		CONST_regValName_resServId												"resServId"

		//
		#define		CONST_regValName_usTimeoutInMsToSwitch									_T(  "usTimeoutInMsToSwitch"  )							//  2008/10/28
		#define		CONST_regValName_usTimeoutInMsToSwitch_rt								_T(  "usTimeoutInMsToSwitch_rt"  )						//  2008/10/28
		#define		CONST_regValName_usMaxMsgs_allowedToSwitchToTalkChannel_robot			_T(  "usMaxMsgs_allowedToSwitchToTalkChannel_robot"  )	//  2009/04/02
		#define		CONST_regValName_usMaxMsgs_allowedToSwitchToTalkChannel_media			_T(  "usMaxMsgs_allowedToSwitchToTalkChannel_media"  )	//  2009/04/02

		//
		#define		CONST_regValName_ucbUseDynBmpRule										"ucbUseDynBmpRule"										//  2009/09/17
	
		//
		#define		CONST_regValName_baud													_T(  "baud"  )
		//
		#define		CONST_regValName_ucbPermitOtherSm										_T(  "ucbPermitOtherSm"  )								//  2008/11/26, ???????localmachine??
		//

		//  #define		CONST_regValName_ucbUseDefault											_T(  "ucbUseDefault"  )								//  2013/03/10
		#define		CONST_regValName_ucbShowVideoHint										_T(  "ucbShowVideoHint"  )								//  2013/03/11,默认选中, 不选中就要写注册表
		#define		CONST_regValName_ucbEffectiveImmediately								_T(	 "ucbEffectiveImmediately"  )						//  2013/03/11,默认不选, 选了写注册表--实时生效
		#define		CONST_regValName_faceName												_T(  "faceName"  )										//  2013/03/11,默认Tahoma(不写), 变化了写注册表
		#define		CONST_regValName_fontSize												_T(  "fontSize"  )
		#define		CONST_regValName_fontHeight												_T(  "fontHeight"  )									//  2013/03/11,默认36(不写), 变化了写注册表
		#define		CONST_regValName_fontWeight												_T(  "fontWeight"  )									//  2013/03/24,默认400(FW_NORMAL)
		#define		CONST_regValName_fontItalic												_T(  "fontItalic"  )									//  2013/03/24
		#define		CONST_regValName_fontCharset											_T(  "fontCharset"  )									//  2013/03/24,默认就是本系统的字符集
		#define		CONST_regValName_fontColor												_T(  "fontColor"  )										//  2013/03/11,默认white(不写), 变化了写注册表
		#define		CONST_regValName_maskColor												_T(  "maskColor"  )										//  2013/03/11,默认black(不写), 变化了写注册表
		//
		#define		CONST_regValName_ucbUsePath												_T(  "ucbUsePath"  )
		#define		CONST_regValName_edgeColor												_T(  "edgeColor"  )
		#define		CONST_regValName_edgeWidth												_T(  "edgeWidth"  )
		#define		CONST_regValName_bFilled												_T(  "bFilled"  )
		//
		#define		CONST_regValName_xStart													_T(  "xStart"  )										//  2013/03/11,默认11(不写), 变化了写注册表
		#define		CONST_regValName_yStart													_T(  "yStart"  )										//  2013/03/11,默认1(不写), 变化了写注册表
		#define		CONST_regValName_subtitles												_T(  "txt"  )											//  2013/03/11,默认空(不写), 变化了写注册表
		#define		CONST_regValName_ucbHorizontalCenter									_T(  "ucbhorizontalCenter"  )							//  2014/12/22
		#define		CONST_regValName_ucbFromBottomUp										_T(  "ucbFromBottomUp"  )
		#define		CONST_regValName_ucbDisplayTime											_T(  "ucbDisplayTime"  )
		//  2013/10/03
		#define		CONST_regValName_keyCfg_usCnt											_T(  "usKeyCnt"  )
		#define		CONST_regValName_keyCfg_bUseKey											_T(  "bUseKey"  )
		#define		CONST_regValName_keyCfg_minRgb											_T(  "minRgb"  )
		#define		CONST_regValName_keyCfg_minS											_T(  "minS"  )
		#define		CONST_regValName_keyCfg_minL											_T(  "minL"  )
		#define		CONST_regValName_keyCfg_maxL											_T(  "maxL"  )
		//
		#define		CONST_regValName_keyCfg_preBlur											_T(  "preBlur" )		// 2013/10/27
		#define		CONST_regValName_keyCfg_postBlur										_T(  "postBlur" )		// 2013/10/27
		#define		CONST_regValName_keyCfg_gamma											_T(  "gamma"  )			// 2013/10/28
		#define		CONST_regValName_key_r													_T(  "r"  )
		#define		CONST_regValName_key_g													_T(  "g"  )
		#define		CONST_regValName_key_b													_T(  "b"  )
		#define		CONST_regValName_key_tola												_T(  "tola"  )
		#define		CONST_regValName_key_tolb												_T(  "tolb"  )

		//
		#define		CONST_regValName_snmpbShowMsgBox										_T(  "snmpbShowMsgBox"  )
		#define		CONST_regValName_ucbShowNotification									_T(  "ucbShowNotification"  )
		//
		#define		CONST_regValName_ucbPreferCuda											_T(  "ucbPreferCuda"  )									//  2012/06/25
		//
		#define		CONST_regValName_ucbLooping_mediaFile									_T(  "ucbLooping_mediaFile"  )							//  2012/11/06		
		//
		#define		CONST_regValName_ucSeconds_perFrame_videoConference						_T(  "ucSeconds_perFrame_videoConference"  )			//  ?????????. ????????????????????
		#define		CONST_regValName_usFps_videoConference									_T(  "usFps_videoConference"  )							//  ????
		//
		#define		CONST_regValName_usAutoAnswer_av											_T(  "usAutoAnswer_av"  )								//  2016/02/15

		#define		CONST_regValName_iWidth_pic												"iWidth_pic"
		#define		CONST_regValName_iHeight_pic											"iHeight_pic"

		#define		CONST_regValName_uiBytesRecorded_perBlockAlign							_T(  "uiBytesRecorded_perBlockAlign"  )					//  ????????????
		//
		#define		CONST_regValName_ucbOrgAudioFmt											_T(  "ucbOrgAudioFmt"  )								//  2014/05/24
		#define		CONST_regValName_uiChannel												_T(  "uiChannel"  )										//  2014/05/24
		#define		CONST_regValName_uiSample												_T(  "uiSample"  )										//  2014/05/24
		#define		CONST_regValName_uiBit													_T(  "uiBit"  )											//  2014/05/24

		
		#define		CONST_regValName_audio_avgBitrate										_T(  "audio_avgBitrate"  )

		//
		#define		CONST_regValName_usIntervalInS_refreshRecentFriends						"usIntervalInS_refreshRecentFriends"
		#define		CONST_regValName_usIntervalInS_refreshContactList						"usIntervalInS_refreshContactList"
		#define		CONST_regValName_usCliThreads											"usCliThreads"											//  2015/08/23
		#define		CONST_regValName_usMgrThreads_cs										"usMgrThreads_cs"										//  2015/08/21
		#define		CONST_regValName_usMgrThreads_route										"usMgrThreads_route"									//  2015/08/21
		#define		CONST_regValName_usMgrThreads_switch_route								"usMgrThreads_switch_route"								//  2015/08/21


		//  2011/10/15
#if  0
		#define		CONST_regValName_ucbShareWebcamInConference								_T(  "ucbShareWebcamInConference"  )
		#define		CONST_regValName_conferenceId_shareWebcam								_T(  "conferneceId_shareWebcam"  )
		#define		CONST_regValName_ucbNoLocalVideoInThisConference						_T(  "ucbNoLocalVideoInThisConference"  )
		#define		CONST_regValName_ucbDistinguishSharedWebcams							_T(  "ucbDistinguishSharedWebcams"  )
#endif
		//  2015/09/20
		#define		CONST_regValName_ptzType												_T(  "ptzType"  )							//  2015/09/20
		//  2012/08/02
		#define		CONST_regValName_ptzProtoType											_T(  "ptzProtoType"  )						//  2012/08/02	, m_combo_protocolType);
		#define		CONST_regValName_ptzAddr												_T(  "ptzAddr"  )							//  2012/08/02  ,
		#define		CONST_regValName_comName												_T(  "comName"  )							//  2012/08/02  
		#define		CONST_regValName_comBaud												_T(  "comBaud"  )							//  CONST_regValName_band 替换
		#define		CONST_regValName_comParity												_T(  "comParity"  )							//  2012/08/02
		#define		CONST_regValName_comData												_T(  "comData"  )							//  2012/08/02
		#define		CONST_regValName_comStopBit												_T(  "comStopBit"  )						//  2012/08/02
		//
		#define		CONST_regValName_remotePtzUsers											_T(  "remotePtzUsers"  )					//  2012/08/06
		#define		CONST_regValName_memoAppending											_T(  "memoAppending"  )						//  2012/08/11

		#define		CONST_regValName_remoteStorageUsers										_T(  "remoteStorageUsers"  )				//  2014/08/06

		//  2009/02/25
		#define		CONST_regValName_ucbManullyPermitToSpeakOnVideoConference				_T(  "ucbManullyPermitToSpeakOnVideoConference"  )
		//  2017/07/07
		#define		CONST_regValName_ucbLetConfMgrSetMicOn									_T(  "ucbLetConfMgrSetMicOn"  )

		

		//  2012/04/07
		#define		CONST_regValName_ucbScrollForEnlagedImg									_T(  "ucbScrollForEnlagedImg"  )
				
		#define		CONST_regValName_iTimeoutInMs_channelIdle_others						_T(  "iTimeoutInMs_channelIdle_others"  )

		#define		MIN_iTimeoutInMs_channelIdle											3000
		#define		MAX_iTimeoutInMs_channelIdle											3600000
		#define		DEFAULT_iTimeoutInMs_channelIdle_others									10000
		//  2012/03/30
		#define		CONST_regValName_usMax_nPlayers											"usMax_nPlayers"
		#define		CONST_regValName_usMax_nThreads_dec										"usMax_nThreads_dec"
		#define		CONST_regValName_uiMaxQNodes_vwRuleQ									"uiMaxQNodes_vwRuleQ"


		//  2011/10/25
		#define		CONST_regValName_recorder_selected										"Recorder_selected"
		#define		CONST_regValName_webcam_selected										"Webcam_selected"
		#define		CONST_regValName_capture_selected										"Capture_selected"
		#define		CONST_regValName_rtspUrl_selected										"RtspUrl_selected"
		#define		CONST_regValName_audio_out_selected										"Audio_out_selected"
		
		//  2014/05/01
		#define		CONST_regKeyName_rtspUrl												"RtspUrl"
		#define		CONST_regKeyName_webcam													"webcam"	//  2017/06/08
		#define		CONST_regKeyName_screen													"screen"
		#define		CONST_regKeyName_ic														"ic"


		//
		#define		CONST_regValName_aName													_T(  "aName"  )		//  20170608
		#define		CONST_regValName_vName													_T(  "vName"  )		//  20170608

		//
		#define		CONST_regValName_ucbUnresizable											_T(  "ucbUnresizable"  )
		#define		CONST_regValName_name													_T(  "name"  )
		#define		CONST_regValName_ucbAutoOpenOnStartup									_T(  "ucbAutoOpenOnStartup"  )

	    //  2017/08/30
		#define		CONST_regValName_ksName													_T(  "ksName"  )
		#define		CONST_regValName_ysName													_T(  "ysName"  ) 

		//
		#define		CONST_regValName_bMon													_T("bMon")



		//  2005/09/18
		#define		CONST_regValName_sndEventLogCmd								"sndEventLog"  
		#define		CONST_regValName_sndNetStatCmd								"sndNetStat"  			//  ?????????2005/09/17
		#define		CONST_regValName_sndModuleInfoCmd							"sndModuleInfo"  		//  2006/05/06
		#define		CONST_regValName_watchPrinterCmd							"watchPrinter"  		//  ???????????2005/09/18
		//  2006/08/15
		#define		CONST_regValName_sndPcRegistryValCmd						"sndPcRegistryValCmd"  	//  ?????????, 2006/08/15
		//  2005/03/05
		#define		CONST_regValName_capScreenCmd								"capScreenCmd"  
		#define		CONST_regValName_capScreenDir								"capScreenDir"  
		#define		CONST_regValName_capScreenInterval							"capScreenInterval"  
		#define		CONST_regValName_ucbSaveAsGif								"ucbSaveAsGif"  									//  2008/02/18
		//
		#define		CONST_regValName_monPics_row								"monPics_row"  										//  2008/02/18,	Maximun of spokesmans
		#define		CONST_regValName_monPics_col								"monPics_col"  										//  2008/02/18,	1
		#define		CONST_regValName_usMaxSpeakers								"usMaxSpeakers"				 						//  2009/02/25,	Maximun of microphone

		//  2013/05/25
		#define		CONST_regValName_bUseAec									"bUseAec"	
		#define		CONST_regValName_bFeatrModeOn								"bFeatrModeOn"	
		#define		CONST_regValName_bNoiseSup									"bNoiseSup"	
		#define		CONST_regValName_bAGC										"bAGC"	
		#define		CONST_regValName_bCntrClip									"bCntrClilp"

		//
		//#define		CONST_regValName_degreesToRotate							"degreesToRotate"

		//
		#define		CONST_qyRootKey_monPics										"Software\\Qycx\\Qwm\\Scheduler\\monPics"				//  2008/02/18

		//  2006/09/11
		#define		CONST_regValName_uiWarnPercentOfBandWithFactor_pc			"uiWarnPercentOfBandWithFactor_pc"  
		#define		CONST_regValName_ucWarnedNetworkCardCmd						"ucWarnedNetworkCardCmd"  
		#define		CONST_regValName_ucDetectTimesBeforeWarn					"ucDetectTimesBeforeWarn"  
		#define		CONST_regValName_ucbNotPopupToWarn							"ucbNotPopupToWarn"  					//  ????????
		#define		CONST_regValName_usStopNetworkCardTimeInSecond				"usStopNetworkCardTimeInSecond"  		//  ??????									

		//	2006/01/07
		#define		CONST_regValName_bAutoLogon									"bAutoLogon"  
		//
		#define		CONST_regValName_qwmDigest									"qwmDgt"  
		#define		CONST_regValName_qrtDigest									"qrtDgt"  
		#define		CONST_regValName_qnmMaxObjs									"qnmMaxObjs"

		//
		#define		CONST_regValName_warnOn						"warnOn"
		#define		CONST_regValName_warnUntilUsrStopIt			"warnUntilUsrStopIt"
		#define		CONST_regValName_maxWarnElapseInSecond		"maxWarnElapse"
		#define		CONST_regValName_emergencyTime				"emergencyTime"
		#define		CONST_regValName_newEmergency				"newEmergency"
		#define		CONST_regValName_popupToWarnStartTime		"popupToWarnStartTime"	//  2006/06/02
		//
		#define		CONST_regValName_board						"board"					//  2005/02/03
		#define		CONST_regValName_nDwLevels					"nDwLevels"				//  2005/02/09
		#define		CONST_regValName_nZcbhs						"nZcbhs"					//  2005/02/09
		//
		#define		CONST_regValName_wAdvertisement				"wAdvertisement"				//  2008/03/02
		#define		DEFAULT_str_wAdvertisement					_T(  "<br>&nbsp;&nbsp;&nbsp;<b>Welcome to <a href=\"http://www.qycx.com/\" target=\"_blank\">www.qycx.com!</a></b>"  ) 
		//
		#define		CONST_regValName_getCfgInterval				"getCfgInterval"			//  ??????
		#define		CONST_regValName_queryCfgsInterval			"queryCfgsInterval"			//  ????????, 2006/08/15
		#define		CONST_regValName_showPcNetworkInterval		"showPcNetworkInterval"		//  ????????
		#define		CONST_regValName_sndEventLogInterval		"sndEventLogInterval"		//  ????????
		#define		CONST_regValName_sndUsrInfoInterval			"sndUsrInfoInterval"		//  ???????????
		#define		CONST_regValName_sndNetStatInterval			"sndNetStatInterval"		//  ??????????
		#define		CONST_regValName_showProcessInterval		"showProcessInterval"
		#define		CONST_regValName_showModulesInterval		"showModulesInterval"		//  
		#define		CONST_regValName_showNetFlowInterval		"showNetFlowInterval"		//  2006/09/12
		#define		CONST_regValName_showWindowsUpdatePolicyInterval	"showWindowsUpdatePolicyInterval"	//  2006/05/24
		#define		CONST_regValName_sndPrintersInterval		"sndPrintersInterval"		//  2006/12/10
		#define		CONST_regValName_showPcNetShareInterval		"showPcNetShareInterval"	//  2007/02/20
		#define		CONST_regValName_showPcArpInterval			"showPcArpInterval"			//  2007/02/20
		//
		#define		CONST_regValName_getOpCmdInterval			"getOpCmdInterval"			//  ???????, 2006/03/23
		//
		#define		CONST_regValName_nProcessQmObjQInterval		"nProcessQmObjQInterval"	//  2006/12/10
		#define		CONST_regValName_nRefreshQmObjQStatusInDb	"nRefreshQmObjQStatusInDb"	//  2006/12/10
		#define		CONST_regValName_maxLogs					"maxLogs"					//  ???????2005/10/01
		#define		CONST_regValName_nMaxConns					"maxConns"					//  ??????2006/08/18
		
		//
		#define		CONST_regValName_autoLogonInterval			  "autoLogonInterval"  

		//
		#define		CONST_regValName_communityRo				"myLoc0"				//  2005/08/02  
		#define		CONST_regValName_communityRw				"myLoc1"

//
#define			CONST_exeName_qyMessenger				"qyMessenger"


		//
		
		#define		CONST_qySubKey_qnmHttpSvr					(  "httpSvr"  )
			#define		CONST_regValName_qnmHttpSvrPort				(  "qnmHttpSvrPort"  )
	#define		CONST_qyRootKey_qnmResp						  "Software\\Qycx\\Qwm\\Resp"  	
	#define		QY_MCA_ROOTKEY								(  "Software\\Qycx\\Qwma"  )
		#define		QY_IMC_ROOTKEY								(  "Software\\Qycx\\Qwma\\Imc"  )
			#define	    QY_IMC_ALLCANCELBUT_VALNAME				    (  "acb"  )	
			#define	    QY_MAC_VALNAME							    (  "mm"  )
			#define	    CONST_regValName_policyFileDigest			(  "pfd"  )
			#define	    CONST_regValName_newPolicyFileDigest		(  "npfd"  )
			#define	    CONST_regValName_policyExecTime			    (  "pet"  )
	#define		CONST_qyRootKey_httpSvr						  "Software\\Qycx\\Qwm\\HttpSvr"  				
	#define		CONST_qyRootKey_qnmTemp						  "Software\\Qycx\\Qwm\\Temp"  				
#define		QY_PROXY_ROOTKEY							  "Software\\Qycx\\Proxy"  

	#define		CONST_qyHint_stopMon0				_T(  "This action would uninstall all client software,are you sure to continue ?"  )		//	_T(  "????????????????????????"  )
	#define		CONST_qyHint_stopMon1				_T(  "This uninstallation are dangerous,are you sure to continue "  )						//	_T(  "??????????????????????????????"  )
	#define		CONST_qyHint_stopMon2				_T(  "If uninstall the client software, you cannot restore. are you sure to continue "  )	//	_T(  "???????????????????????????"  )
	#define		CONST_qyHint_passwdForStopMon		"Please input password to uninstall the client software:  "							//  "??????????????:"


typedef  struct  __qnmIntervalParams_t								{										//  2005/06/10, ??????????????????????????????
				 unsigned  short									usGetCfgInterval;
				 unsigned  short									usShowPcNetworkInterval;
				 unsigned  short									usSndEventLogInterval;
				 unsigned  short									usSndUsrInfoInterval;
				 unsigned  short									usSndNetStatInterval;
				 unsigned  short									usShowProcessInterval;					//  2005/10/02
				 unsigned  short									usGetOpCmdInterval;						//  2006/02/11
				 unsigned  short									usShowModulesInterval;					//  2006/04/14
				 unsigned  short									usShowWindowsUpdatePolicyInterval;		//  2006/05/24
				 unsigned  short									usQueryCfgsInterval;					//  2006/08/15
				 unsigned  short									usShowNetFlowInterval;					//  2006/09/12
				 unsigned  short									usSndPrintersInterval;					//  2006/12/10
				 unsigned  short									usShowPcNetShareInterval;				//  2007/02/14
				 unsigned  short									usShowPcArpInterval;					//  2007/02/14
				 //
				 
}		 QNM_INTERVAL_PARAMS;


typedef  struct  __imNetStat_t										{
				 //
				 unsigned  __int64									ui64MsgDataLenRecvd;							//  2009/10/10
				 unsigned  __int64									ui64MsgDataLenSent;
				 //
				 unsigned  int										uiInSpeedInKbps;								//  bps
				 unsigned  int										uiOutSpeedInKbps;
				 //
}		 IM_NET_STAT;

//
typedef  struct  __qmcNetStat_t										{
				 IM_NET_STAT										ins;
				 //
				 unsigned  int										uiInSpeedInKbps_a;
				 unsigned  int										uiOutSpeedInKbps_a;
				 //
				 unsigned  int										uiInSpeedInKbps_v;
				 unsigned  int										uiOutSpeedInKbps_v;
				 //
				 unsigned  int										uiInSpeedInKbps_f;
				 unsigned  int										uiOutSpeedInKbps_f;

}		 QMC_net_stat;


//
typedef  struct  __channelStatus_io_t								{
					 unsigned  char									ucbReceiveing;
					 DWORD											dwTickCnt_recv_first;
					 unsigned  char									ucbSending;
					 DWORD											dwTickCnt_snd_start;				 
}		 CHANNEL_status_io;


//  
#define		CONST_qyRootKey_test						(  "Software\\Qycx\\Test"  )
	#define		CONST_regValName_testQwmCntIp				(  "qwmCnt"  )
	#define		CONST_regValName_testQwmSendTimes			(  "qwmSendTimes"  )



//
//
#define		QY_MC_PROFILENAME							"qycx@qycx.com"				// ????Bar???, LoadBarState( ).

#define		CONST_qyDsn_netMc							"qyNetMcDsn"  
#define		CONST_qyDbNamePrefix_netMc					"qyNetMc"  
//  
#define		CONST_qyDbNamePrefix_misClient				"qyMisClient"  					//  
#define		CONST_qyDbNamePrefix_mis					"qyMis"  

// objName
#define		CONST_qyObjName_mcPolicyTime				"mcPolicyTime"
#define		CONST_qyObjName_mcPolicyExecTime			"mcPolicyExecTime"
#define		CONST_qyObjName_mcPolicyFileDigest			"mcPolicyFileDigest"
#define		CONST_qyObjName_mcPolicyFile				"qmPol"
#define		CONST_qyObjName_fileEnd						"qmFEnd"
#define		CONST_qyObjName_mcKeyTypePolicy				"mkType"
#define		CONST_qyObjName_mcSite						"mcSite"


#define		CONST_qyRcdFmt_mcKeyTypePolicy				"%02s%02s%02s%08s"		//  ??: keyTypeCode,imPolicy,bmPolicy,keyTypeName
#define		CONST_qyRcdLen_mcKeyTypePolicy				14

#define		CONST_qyMaxNameLen							64
#define		CONST_qyMaxDesLen							64
#define		CONST_qyMaxArgvs							32

#define		CONST_qyNullDigest							"00000000"

/*
#define		CONST_qyKeyType_defaultCode					0
#define		CONST_qyKeyType_defaultName					"??"
#define		CONST_qyKeyType_startCode					1
*/


#define		CONST_bufSize_publicKeyBlob								2048
#define		CONST_bufSize_sessionKeyBlob							1024
#define		CONST_bufSize_sessionIv									32



//  ???????
#define		CONST_qyShowType_scanningNetworkSegment				1
#define		CONST_qyShowType_scanningIp							2
#define		CONST_qyShowType_serviceStatus						3
#define		CONST_qyShowType_refresh							4
#define		CONST_qyShowType_qwmComm							5
#define		CONST_qyShowType_qnmChking							6
#define		CONST_qyShowType_qwmState							7
//
#define		CONST_qyShowType_qmdState							CONST_qyShowType_qwmState
//
#define		CONST_qyShowType_qnmProxyChking						8
#define		CONST_qyShowType_bhbScanningNetworkSegment			9
#define		CONST_qyShowType_bhbScanningIp						10
#define		CONST_qyShowType_addChkingType						11
#define		CONST_qyShowType_sysInfo							12		//	2007/04/15
#define		CONST_qyShowType_debug								13		//
#define		CONST_qyShowType_debugWarning						14		//  2007/05/07
#define		CONST_qyShowType_warning							15		//  2007/05/07
#define		CONST_qyShowType_detail								16



#define		CONST_maxShowWhoLen									32



#define		CONST_showWho_all									(  L"(all)"  )				//  (  L"(??)"  )
#define		CONST_showWho_snmpScan								(  L"Snmp scan"  )			//  (  L"??????"  )
#define		CONST_showWho_nbtScan								(  L"Nbt scan"  )			//  (  L"?????"  )
#define		CONST_showWho_snmpNetFlow							(  L"Snmp netflow"  )		//  (  L"??????"  )
#define		CONST_showWho_interMon								(  L"Internet mon"  )		//  (  L"????"  )
#define		CONST_showWho_intraMon								(  L"Intranet mon"  )		//  (  L"????"  )
#define		CONST_showWho_clearTempFile							(  L"Clear temp file"  )	//  (  L"??????"  )


 //  ???, !!! ???????????????????????????????????
 //			 ???unsigned  short
 //			 ????
#define		CONST_qyCmd_getGlCntIp					(  CONST_qyCmd_base  +  1  )		//  ?????????????????????
#define		CONST_qyCmd_getCfgs						(  CONST_qyCmd_base  +  2  )
#define		CONST_qyCmd_sndLog						(  CONST_qyCmd_base  +  3  )
#define		CONST_qyCmd_reg							(  CONST_qyCmd_base  +  4  )
//  #define		CONST_qyCmd_commWithGlCnt				(  CONST_qyCmd_base  +  5  )		//  ?????????
#define		CONST_qyCmd_showQwmInfo					(  CONST_qyCmd_base  +  6  )
#define		CONST_qyCmd_queryReg					(  CONST_qyCmd_base  +  7  )		//  ??????
#define		CONST_qyCmd_getProxyCfgs				(  CONST_qyCmd_base  +  8  )		//  ?????,  ??????????????????????????????+????
#define		CONST_qyCmd_putProxyChkedPcsInfo		(  CONST_qyCmd_base  +  9  )		//  ????????????pc????
#define		CONST_qyCmd_getProxyChkedPcsInfo		(  CONST_qyCmd_base  +  10  )	//  ??????????PC??
#define		CONST_qyCmd_getMacByIp					(  CONST_qyCmd_base  +  11  )	//  ???????????????????MAC
#define		CONST_qyCmd_refreshProxyPolicy			(  CONST_qyCmd_base  +  12  )	//  ????????????????
#define		CONST_qyCmd_getProxyStatusParams		(  CONST_qyCmd_base  +  13  )	//  ???????????????????????????
#define		CONST_qyCmd_policyChanged				(  CONST_qyCmd_base  +  14  )	//  ????????????
#define		CONST_qyCmd_quit						(  CONST_qyCmd_base  +  15  )	//  qwm?????????
#define		CONST_qyCmd_sndSecChkLog				(  CONST_qyCmd_base  +  16  )	//  ???????2003/11/15
#define		CONST_qyCmd_secChkGetCfgs				(  CONST_qyCmd_base  +  17  )	//  ?????????????
#define		CONST_qyCmd_showQwmInfoEx				(  CONST_qyCmd_base  +  18  )	//  ?????????
#define		CONST_qyCmd_showQwmAssetsInfo			(  CONST_qyCmd_base  +  19  )	//  ?????????
#define		CONST_qyCmd_endShowQwmAssetsInfo		(  CONST_qyCmd_base  +  20  )	//  ???????????
#define		CONST_qyCmd_queryPcSp					(  CONST_qyCmd_base  +  21  )	//  ??????, 2005/02/01
#define		CONST_qyCmd_showQwmSvrStatus			(  CONST_qyCmd_base  +  22  )	//  ??qwmSvr???????, 2005/05/02
#define		CONST_qyCmd_showPcNetworkProp			(  CONST_qyCmd_base  +  23  )	//  ?????????????, 2005/05/24
#define		CONST_qyCmd_tryToConnectToServer		(  CONST_qyCmd_base  +  24  )	//  ???????, 2005/06/4
#define		CONST_qyCmd_showPcProcess				(  CONST_qyCmd_base  +  25  )	//  ??????, 2005/07/4
#define		CONST_qyCmd_sndEventLog					(  CONST_qyCmd_base  +  26  )	//  ???????2005/08/31
#define		CONST_qyCmd_sndUsrInfo					(  CONST_qyCmd_base  +  27  )	//  ?????????2005/09/04
#define		CONST_qyCmd_sndNetStat					(  CONST_qyCmd_base  +  28  )	//  ???????2005/09/17
#define		CONST_qyCmd_sndPrinters					(  CONST_qyCmd_base  +  29  )	//  ????????2005/09/18
#define		CONST_qyCmd_queryAutoLogon				(  CONST_qyCmd_base  +  30  )	//  ?????????2006/01/07
#define		CONST_qyCmd_sndAutoLogon				(  CONST_qyCmd_base  +  31  )	//  ?????????2006/01/07
#define		CONST_qyCmd_getOpCmd					(  CONST_qyCmd_base  +  32  )	//  ??????2006/02/11
#define		CONST_qyCmd_sndCapScreen				(  CONST_qyCmd_base  +  33  )	//  ???????2006/03/06
#define		CONST_qyCmd_queryCfgs					(  CONST_qyCmd_base  +  34  )	//  ????????, 2006/03/22
#define		CONST_qyCmd_showPcProcessModule			(  CONST_qyCmd_base  +  35  )	//  ???????2006/04/14
#define		CONST_qyCmd_retrieveWarningMsg			(  CONST_qyCmd_base  +  36  )	//  ??????2006/06/02
#define		CONST_qyCmd_sndRegistryVals				(  CONST_qyCmd_base  +  37  )	//  ????????2006/07/18
#define		CONST_qyCmd_showPcNetFlow				(  CONST_qyCmd_base  +  38  )	//  ???????2006/09/10
#define		CONST_qyCmd_showPcNetShare				(  CONST_qyCmd_base  +  39  )	//  ???????2007/02/14

//  2007/04/23, mis
#define		CONST_qyCmd_showInfo								(  CONST_qyCmd_base  +  200  )	//  
#define		CONST_qyCmd_showInfo_small							(  CONST_qyCmd_base  +  201  )	// 
#define		CONST_qyCmd_showInfo_small_java						(  CONST_qyCmd_base  +  202  )

//
#define		CONST_qyCmd_refreshImObjListReq						(  CONST_qyCmd_base  +  205  )	//  
//
#define		CONST_qyCmd_refreshRecentFriendsReq					(  CONST_qyCmd_base  +  207  )	//  
//
#define		CONST_qyCmd_mcComm									(  CONST_qyCmd_base  +  210  )	//  2011/01/08
//
#define		CONST_qyCmd_sendReq									(  CONST_qyCmd_base  +  220  )

//
#define		CONST_qyCmd_ca										(  CONST_qyCmd_base  +  225  )	//  

//
#define		CONST_qyCmd_talkTo									(  CONST_qyCmd_base  +  300  )	//  

#define		CONST_qyCmd_sendTask								(  CONST_qyCmd_base  +  320  )	//  
#define		CONST_qyCmd_sendTaskReply							(  CONST_qyCmd_base  +  321  )	//  
#define		CONST_qyCmd_sendRobotTask							(  CONST_qyCmd_base  +  322  )	//  
#define		CONST_qyCmd_sendRobotTaskReply						(  CONST_qyCmd_base  +  323  )	//  
#define		CONST_qyCmd_sendRobotTaskData						(  CONST_qyCmd_base  +  324  )	//  
//
#define		CONST_qyCmd_sendMedia								(  CONST_qyCmd_base  +  330  )	//  ??????
//
#define		CONST_qyCmd_lastMsgInSession						(  CONST_qyCmd_base  +  340  )	//  webMessenger?cgi
//
#define		CONST_qyCmd_sendVDevReq								(  CONST_qyCmd_base  +  350  )	//  
//
#define		CONST_qyCmd_chkLogonId								(  CONST_qyCmd_base  +  360  )	//  2023/06/14


//  2007/07/08???robot????????
//  1????CONST_qyCmd_sendTask??talking???????????????????OK???
//  2????????????CONST_qyCmd_sendTaskReply??robot?????????
//  3?????CONST_qyCmd_sendTaskReply??talking????????; ( ????sendTaskReply??????channelType?????????????????????????????? )
//  4????????????????robot??????????????robot??????
//  5??????????robot???CONST_qyCmd_sendTaskData??????



extern  QY_DMITEM	CONST_qyServiceIdTable[];
//	extern  QY_DMITEM	CONST_qySystemIdTable[];
extern  QY_DMITEM	CONST_qyAppTypeTable[];			//  

extern  QY_DMITEM	CONST_qyCmdTable[];
extern  QY_DMITEM  CONST_qyCmdTable_cn[];
extern  QY_DMITEM	CONST_qyRcTable[];
extern  QY_DMITEM	CONST_qyRetTable[];


#define		CONST_qyRootKey_tcpParameters				"SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters"
	#define		CONST_regValName_nvHostname					"NV Hostname"
#define		CONST_qyRootKey_tcpIpInterfaces				"SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\"
	#define		CONST_regValName_enableDhcp					"EnableDHCP"
	#define		CONST_regValName_ipAddress					"IPAddress"
	#define		CONST_regValName_subnetMask					"SubnetMask"
	#define		CONST_regValName_defaultGateway				"DefaultGateway"
	#define		CONST_regValName_defaultGatewayMetric		"DefaultGatewayMetric"
	#define		CONST_regValName_dns						"NameServer"
	#define		CONST_regValName_dhcpIpAddress				"DhcpIPAddress"
	#define		CONST_regValName_dhcpSubnetMask				"DhcpSubnetMask"
	#define		CONST_regValName_addressType				"AddressType"



////////////////////  2009/03/28



//  2013/10/16
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif


//  2010/03/26
#define		myMulDiv(  a, b, c  )	(  (  a  *  b  )  /  c  )
#ifndef	WINCE
	#define		myGetProcAddress(  hModule,  lpProcName  )	GetProcAddress(  hModule,  (  lpProcName  )  )
#else
	#define		myGetProcAddress(  hModule,  lpProcName  )	GetProcAddress(  hModule,  _T(  lpProcName  )  )
#endif

#ifdef	WINCE
	#ifndef  HIC
		DECLARE_HANDLE(HIC);     /* Handle to a Installable Compressor */	
	#endif
	#ifndef  HDRAWDIB
		typedef HANDLE HDRAWDIB; /* hdd */
	#endif
#endif

#ifdef  __WINCE__

	#ifndef  SQL_WVARCHAR
		#define SQL_WVARCHAR        (-9)
	#endif

#endif

//  Globals
#ifdef  __cplusplus
  
		#ifdef  __QYPUBLIC_EXPORTS__
				extern  "C"  __declspec(  dllexport  )  QY_ENV	*	g_pEnv;
		#else
				extern  "C"  __declspec(  dllimport  )  QY_ENV	*	g_pEnv;
		#endif

#else

		#ifdef  __QYPUBLIC_EXPORTS__
				extern  __declspec(  dllexport  )  QY_ENV	*	g_pEnv;
		#else
				extern  __declspec(  dllimport  )  QY_ENV	*	g_pEnv;
		#endif

#endif



//
#ifdef  __cplusplus
  extern  "C"  {
#endif
  

int  qyGetSystemId(  );
//
int  qyGetSubSystemId_mgr(  );  //  2017/06/21
//
int  qyGetAppType(  int  iSystemId,  LPCTSTR  guiRootKey  );
BOOL  bAppClient(  int  iAppType  );


//
int  qyGetTerminalType(LPCTSTR  cfgFile);



//
BOOL  bSupported_devAuth(  );


//  2014/09/23
BOOL  bSupported_sendVhDec(  );



#ifdef  __DEBUG__
 BOOL  dbg_bNoRefreshRecentFriends(  );
#endif
BOOL  bTEST_shareScreen(  unsigned  int  *  piW_test,  unsigned  int  *  piH_test  );



//
extern  QY_DMITEM  CONST_customIdTable[];


//
int  qyGetCustomId(  );
int  qyGetServiceId(  int  iSystemId  );
int  qyGetEncType(  int  iSystemId  );


//  int  qyGetRegCfgW(  QY_ENV  *  pEnv,  LPCWSTR  rootKey,  LPCWSTR  cfgName,  WCHAR  *  cfgVal,  int  size  );
int  qyGetRegCfg1W(  QY_ENV  *  pEnv,  HKEY  hKeyRoot0,  LPCWSTR  rootKey,  LPCWSTR  cfgName,  WCHAR  *  cfgVal,  int  size,  unsigned  int  *  puiType  );

HRESULT WINAPI  mySHGetFolderPathW(  QY_ENV  *  pEnv,  HWND  hwnd,  int  csidl,  HANDLE  hToken,  DWORD  dwFlags,  LPWSTR  pszPath  );
BOOL  WINAPI  myGetSystemTimes(  QY_ENV  *  pEnv,  LPFILETIME lpIdleTime,  LPFILETIME lpKernelTime,  LPFILETIME lpUserTime  );
BOOL WINAPI myIsWow64Process(  QY_ENV  *  pEnv,  HANDLE hProcess,  PBOOL Wow64Process  );
BOOL  WINAPI  myWTSSendMessage(  QY_ENV  *  pEnv,  IN HANDLE hServer,  IN DWORD SessionId,  __in_bcount(TitleLength) LPWSTR pTitle,  IN DWORD TitleLength,  __in_bcount(MessageLength) LPWSTR pMessage,  IN DWORD MessageLength,  IN DWORD Style,  IN DWORD Timeout,  __out DWORD * pResponse,  IN BOOL bWait  );

//  2011/10/04
BOOL  bExists_MessageBoxTimeout(  QY_ENV  *  pEnv  );
int  WINAPI  myMessageBoxTimeout(  QY_ENV  *  pEnv,  __in_opt HWND hWnd,  __in_opt LPCWSTR lpText,  __in_opt LPCWSTR lpCaption,  __in UINT uType,  __in  WORD  wLanguageId,  __in  DWORD  dwMilliseconds  );


//  2010/05/15
UINT  WINAPI  qwmGetSystemDirectory(  QY_ENV  *  pEnv,  LPTSTR lpBuffer,  UINT uSize  );

int  getProcessUsrAndDomain(  void  *  pEnv,  DWORD  processId,  WCHAR  *  wAccountNameBuf,  unsigned  int  uiAccountNameBufSize,  WCHAR  *  wDomainNameBuf,  unsigned  int  uiDomainNameBufSize  );


#if  0
unsigned  int	getuiNextTranNo(  void  *  p0,  void  *  p1,  long  *  puiTranNo  );
#endif
__declspec(  dllexport  )  unsigned  int	getuiNextTranNo(  void  *  p0,  long  val,  long  *  puiTranNo  );		//  2010/09/04



//  2014/06/24
#if 0
typedef  struct  __qyShowStruct_t			{
				 int						iType;
				 //
				 unsigned  short			usStateType;						//  2022/01/27
				 unsigned  short			usStateSubtype;						//  2022/01/27
				 //
				 int						iPos_toDisplay;
				 //
				 int						iTaskId;							//  2022/01/27
				 //
				 unsigned  long				ulClientIp;							//  2007/08/21 socket clientIp
				 WCHAR						who_from[32];						//  2015/05/23. WCHAR						who_from[16];
				 WCHAR						who_to[16];
				 WCHAR						whereBuf[16];
				 SYSTEMTIME					when;								//  2007/06/01, 
				 unsigned  int				uiStep;								//  2008/04/28, 
				 //
				 DWORD						dwProcessId;						//  2015/08/30
				 DWORD						dwThreadId;							//  2015/08/20
				 //
				 WCHAR						doStr[16];
				 WCHAR						what[256];
#ifdef  __DEBUG__
				 char						testBytes;							//  2010/09/06. 这个字节是为了发现一个大小为424字节数的内存泄露。故意增加了一个测试字节。
																				//  等问题解决了后，应该去除。
#endif
}		 old_QY_SHOW_STRUCT;
#endif

//
typedef  struct  __qyShowStruct_t {
	int						iType;
	//
	unsigned  short			usStateType;						//  2022/01/27
	unsigned  short			usStateSubtype;						//  2022/01/27
	//
	int						iPos_toDisplay;
	//
	int						iTaskId;							//  2022/01/27
	//
	unsigned  long				ulClientIp;							//  2007/08/21 socket clientIp
	WCHAR						who_from[16];						//  2015/05/23. WCHAR						who_from[16];
	WCHAR						who_to[16];
	WCHAR						whereBuf[16];
	SYSTEMTIME					when;								//  2007/06/01, 
	//
	unsigned  short				usStep;								//  2008/04/28, 
	unsigned  char				ucPercent_showInfoQ;
	unsigned  char				uc_reserved;
	//
	DWORD						dwProcessId;						//  2015/08/30
	DWORD						dwThreadId;							//  2015/08/20
	//
	WCHAR						doStr[16];
	WCHAR						what[128];
#ifdef  __DEBUG__
	char						testBytes;							//  2010/09/06. 这个字节是为了发现一个大小为424字节数的内存泄露。故意增加了一个测试字节。
																   //  等问题解决了后，应该去除。
#endif
}		 QY_SHOW_STRUCT;



//
typedef  struct  __qyShowSmall_t {
	int						iType;
	//
	unsigned  short			usStateType;						//  2022/01/27
	unsigned  short			usStateSubtype;						//  2022/01/27
	//
	int						iPos_toDisplay;
	//
	int						iTaskId;							//  2022/01/27
	//
	unsigned  long				ulClientIp;							//  2007/08/21 socket clientIp
	unsigned  __int64			who_from;							//  2015/05/23. WCHAR						who_from[16];
	unsigned  __int64			who_to;
	WCHAR						whereBuf[8];						// utf8
	SYSTEMTIME					when;								//  2007/06/01, 
	//
	unsigned  short				usStep;								//  2008/04/28, 
	unsigned  char				ucPercent_showInfoQ;
	unsigned  char				uc_reserved;
	//
	DWORD						dwProcessId;						//  2015/08/30
	DWORD						dwThreadId;							//  2015/08/20
	//
	WCHAR						doStr[8];							// utf8
	WCHAR						what[96];							// utf8
#ifdef  __DEBUG__
	char						testBytes;							//  2010/09/06. 这个字节是为了发现一个大小为424字节数的内存泄露。故意增加了一个测试字节。
																   //  等问题解决了后，应该去除。
#endif
}		 QY_SHOW_SMALL;

//
//
typedef  struct  __qyShowSmall_java_t {
	int						iType;
	//
	unsigned  short			usStateType;						//  2022/01/27
	unsigned  short			usStateSubtype;						//  2022/01/27
	//
	int						iPos_toDisplay;
	//
	int						iTaskId;							//  2022/01/27
	//
	unsigned  long				ulClientIp;							//  2007/08/21 socket clientIp
	//unsigned  __int64			who_from;							//  2015/05/23. WCHAR						who_from[16];
	char						who_from[8];
	//unsigned  __int64			who_to;
	char						who_to[8];
	char						whereBuf[8  *  2];						// utf8
	SYSTEMTIME					when;								//  2007/06/01, 
	//
	unsigned  short				usStep;								//  2008/04/28, 
	unsigned  char				ucPercent_showInfoQ;
	unsigned  char				uc_reserved;
	//
	DWORD						dwProcessId;						//  2015/08/30
	DWORD						dwThreadId;							//  2015/08/20
	//
	char						doStr[8*2];							// utf8
	char						what[96  *  2];							// utf8
#ifdef  __DEBUG__
	char						testBytes;							//  2010/09/06. 这个字节是为了发现一个大小为424字节数的内存泄露。故意增加了一个测试字节。
	//  等问题解决了后，应该去除。
#endif
}		 QY_SHOW_SMALL_java;



//
typedef  int  (  *  PF_qyShowInfo0  )(  void  *  pShowStructParam,  void  *  pReserved  );
int  setErrHintPf(  PF_qyShowInfo0  pf  );
__declspec(  dllexport  )  int  setErrHintWndCls(  LPCTSTR  cls  );
//
int  setShowMoreOn(  BOOL  bShowMore  );
__declspec(  dllexport  )  BOOL  bShowMore(  );
//
__declspec(  dllexport  )  int  initShowInfo(  void  *  p0,  LPCTSTR  mutexName_syncQ,  LPCTSTR  errHintWndCls,  BOOL  bUsePipe,   BOOL  bCli,  void  **  ppCtx_showInfo   );
__declspec(  dllexport  )  int  initShowInfo_cli(  void  *  p0,  LPCTSTR  mutexName_syncQ,  char  *  servIp,  void  **  ppCtx_showInfo   );
//
__declspec(dllexport ) int  initShowInfo_func(  void  *  p0,  LPCTSTR  mutexName_syncQ,  LPCTSTR  errHintWndCls,  BOOL  bUsePipe,   BOOL  bUseSock,  char  *  servIp,  BOOL  bCli,  void  **  ppCtx_showInfo   );

//
__declspec(  dllexport  )  void  exitShowInfo(  void  **  ppCtx_showInfo  );
//

//
//__declspec(  dllexport  )  void  *  get_pShowInfoStruct(  );
//
//__declspec(  dllexport  )  int  set_g_pShowInfoStruct(  void  *  pShowInfoStruct  );

//
__declspec(  dllexport  )  int  qyShowInfo(  void  *  pCtx_showInfo,  int  iShowType,  unsigned  int  *  puiStep,  char  *  clientIp,  LPCWSTR  who_from,  LPCWSTR  who_to,  LPCWSTR  where,  LPCWSTR  doStr,  LPCWSTR  fmt,  ...  );
//
__declspec(  dllexport  )  int  qyShowInfo1(  int  iShowType,  unsigned  int  *  puiStep,  char  *  clientIp,  LPCWSTR  who_from,  LPCWSTR  who_to,  LPCWSTR  where,  LPCWSTR  doStr,  LPCWSTR  fmt,  ...  );

//
#if  0
typedef  struct  __param_showInfo_t		{
				 int					iPos_toDisplay;
}		 PARAM_showInfo;
#endif


typedef  struct  __param_showInfo_t		{
				 unsigned short usStateType;
				 unsigned short usStateSubtype;
				 //
				 SYSTEMTIME when;
				 //
				 int iPos_toDisplay;
				 //
				 int iTaskId;
}		 PARAM_showInfo;


//
__declspec(  dllexport  )  int  qyShowInfo2(  PARAM_showInfo  *  pParam,  int  iShowType,  unsigned  int  *  puiStep,  char  *  clientIp,  LPCWSTR  who_from,  LPCWSTR  who_to,  LPCWSTR  where,  LPCWSTR  doStr,  LPCWSTR  fmt,  ...  );


//
#include	"ctx_q_showInfo.h"

//
int  qyShowInfo_internal(  CTX_q_showInfo  *  pCtx,  int  iShowType,  unsigned  int  *  puiStep,  char  *  clientIp,  LPCWSTR  who_from,  LPCWSTR  who_to,  LPCWSTR  where,  LPCWSTR  doStr,  LPCWSTR  fmt,  ...  );



//  2016/06/29
#include	"showInfo_open.h"


//
 int  myProtectData(  char  *  pbDataInput, int  cbDataInput,  char  *  pbDataOutput,  int  *  pcbDataOutput  );
 int myUnprotectData(char  *  pbDataInput,  int  cbDataInput,  char  *  pbDataOutput,  int  *  pcbDataOutput );
 //
 int  mySaveSecret(  HKEY  hKeyRoot,  LPCTSTR  rootKey,  LPCTSTR  cfgName,  char  *  cfgVal,  int  cb   );
 int  myGetSecret(  HKEY  hKeyRoot,  LPCTSTR  rootKey,  LPCTSTR  cfgName,  char  *  cfgVal,  int  *pcb   );

 //
 //
char  *  displayShortTime(  time_t  t,  char  *  timeBuf,  unsigned  int  len  );



//
#ifdef  __cplusplus
  }
#endif


int  getWtsSessionId(  QY_ENV  *  pEnv,  DWORD  *  pCurSessionId,  DWORD  *  pActiveSessionId  );


#endif  /*  }  */

