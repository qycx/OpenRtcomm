

#ifndef  __ASRWMONCFG_H__
#define  __ASRWMONCFG_H__	/*  {  */


#define		CONST_qwmLogonScriptName					"qyWMonSvr.exe"
#define		CONST_qwmStartupScriptName					"qyWMonSvr2k.exe"
#define		CONST_qwmHideExeName						"mediaSc.exe"
#define		CONST_tmpQrtFileName						"regTool3.exe"
//
#define		CONST_qnmSym_cpcjb							_T(  "cpcjb"  )
//


#define		CONST_qwmMaxThreads							10									
#define		DEFAULT_nInterval_qwmCmdThreadProc			1000


#define		CONST_maxPermittedPhoneNums					20
#define		CONST_maxPhoneNumBytes						20

#define		CONST_qwmMaxnCopies							60		//  重复拷贝次数:  原为15，2005/07/30

#define		CONST_maxDetectedUsrs						4

#define		DEFAULT_AWM_RCV_MSG_PORT					8745


#define		ROOT_ASR_KEY								"Software\\Asr"
	#define		ASR_QUIT_KEY								"quit"
	#define		ASR_INSTALL_PATH_KEY						"installPath"
	#define		ASR_APP_NAME_KEY							"appName"
#define		ROOT_AWPM_KEY								"Software\\Asr\\Wpm"
#define		ROOT_AWPM_LST_KEY							"Software\\Asr\\Wpm\\lst"
	#define	  AWPM_S1_KEY									"S1"	
		#define		AWPM_S1_VAL									"chk"
	#define	  AWPM_S2_KEY									"S2"
		#define		AWPM_S2_VAL									"proxy"
	#define	AWPM_S3_KEY										"S3"
		#define   AWPM_S3_VAL									"docfg"
	#define	AWPM_S4_KEY										"S4"
		#define   AWPM_S4_VAL									"trans"
#define		ROOT_AWM_KEY								"Software\\Asr\\Awm" 
#define		ROOT_AWM_PROXY_KEY							"Software\\Asr\\Awm\\Proxy"
	#define	  AWM_PROXY_SERV_IP_KEY							"server"
	#define	  AWM_SERV_IP_KEY								"cnt"
#define		ROOT_AWM_CHK_KEY							"Software\\Asr\\Awm\\Chk"
	//  #define	  AWM_CHK_NT_LOGON_SCRIPT_PATH_KEY				"scriptsPath"
	//  #define	  AWM_CHK_NT_LOGON_SCRIPT_NAME_KEY				"script"
	//  #define	  AWM_CHK_WIN2K_STARTUP_SCRIPT_PATH_KEY			"scriptsPath"
	//  #define	  AWM_CHK_WIN2K_STARTUP_SCRIPT_NAME_KEY			"script"
	//  #define	  AWM_CHK_STOP_SCRIPT_KEY						"stopScript"
#define		ROOT_AWM_DOCFG_KEY							"Software\\asr\\awm\\doCfg"
	#define	  ASR_RAS_ROOT_SUB_KEY							ROOT_AWM_DOCFG_KEY
	#define	  ASR_RAS_REMOTE_ADM_IP							"remoteIp"
	#define	  AWM_GROUP_NAME_KEY							"groupName" 
	#define	  ASR_RAS_STOP_MONITOR_KEY						"stopMon"
#define		ROOT_AWM_TRANS_KEY							"Software\\asr\\awm\\trans"
#define		ASR_DIAL_MONITOR_QUIT_KEY					"dialQuit"
#define		AWM_MAX_DB_SIZE_CFG							"maxDbSize"
#define		AWM_LOOP_CTL_TIME							"loopCtlTime"


#define		ASR_QUIT_VAL								1
#define		ASR_STOP_VAL								ASR_QUIT_VAL



#define		CONST_qwmSvr_runtimePathName						"qwmSvr.exe"
#define		CONST_qwmSvr_serviceName							"Qycx Network Agent"
#define		CONST_qwmSvr_legacyServiceName						"LEGACY_QYCX_NETWORK_AGENT"			//  2006/08/31

#define		CONST_qnmProxy_runtimePathName						"qnmProxy.exe"
#define		CONST_qnmProxy_hostProcessName						"EXPLORER"
#define		CONST_qnmProxy_serviceName							"Qycx Network Proxy"
#define		CONST_qnmProxy_idleTimeout							60000

#define		CONST_qyRootKey_internetSettings	"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings"
	#define		CONST_regValName_enableAutodial		"EnableAutodial"
	#define		CONST_regValName_noNetAutodial		"NoNetAutodial"
	#define		CONST_regValName_proxyEnable		"ProxyEnable"
	#define		CONST_regValName_proxyServer		"ProxyServer"
	#define		CONST_regValName_proxyOverride		"ProxyOverride"
	#define		CONST_regValName_autoConfigUrl		"AutoConfigURL"								//  2006/11/25
	#define		CONST_qySubKey_connections			"Connections"								//  2005/06/17
		#define		CONST_regValName_defaultConnectionSettings		"DefaultConnectionSettings"
#define		CONST_qyRootKey_explorer			"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer"
	#define		CONST_regValName_logonUsrName		"Logon User Name"
#define		CONST_qyRootKey_shellFolders		"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders"
	#define		CONST_regValName_recent				"Recent"
	#define		CONST_regValName_sendTo				"SendTo"
	#define		CONST_regValName_cache				"Cache"
#define		CONST_qyRootKey_cacheContent		"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Cache\\Content"
	#define		CONST_regValName_cachePath			"CachePath"
#define		CONST_qyRootKey_cachePaths			"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Cache\\Paths"
	#define		CONST_regValName_directory			"Directory"
#define		CONST_qyRootKey_computerName	"SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName"
	#define		CONST_regValName_computerName	"ComputerName"
#define		CONST_subKey_volatileEnvironment	"Volatile Environment"
	#define		CONST_regCfgName_wUSERDNSDOMAIN		L"USERDNSDOMAIN"
	#define		CONST_regValName_userName			"USERNAME"




#endif  /*  }  */

