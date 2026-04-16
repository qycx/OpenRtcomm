
#ifndef		__QYCFG_H__
#define		__QYCFG_H__	 /*  {  */

#define		QY_TRAY_WINDOW_NAME							  "QYCX_Tray_Hidden_Window"  

#define		QY_INTERNET_MC_MAP_ID						  "2F53743E-2A82-4659-B9E0-EF044139AC42"  



//  以下是管理服务名
#define		CONST_qyMgrServiceName						  "qwpmService"  
#define		CONST_qyMgrServiceDisplayName				  "qwPMgr Service"  
//
#define		CONST_qyServiceName_is						  "qwpmMisService"  		//  2007/08/14
#define		CONST_qyServiceDisplayName_is				  "Qycx Mis Service"  
				

//  注册表项
#define		CONST_qyRootKey								  "Software\\Qycx"  
#define		QY_ROOTKEY									CONST_qyRootKey
	#define		CONST_regValName_installDir					"installDir"  
	#define		CONST_regValName_installPath				  "installPath"  
	#define		QY_INSTALLDIR_VALNAME						  CONST_regValName_installDir
	#define		CONST_regValName_appName					  "appName"  
	#define		QY_APPNAME_VALNAME							CONST_regValName_appName
	#define		CONST_regValName_cmdLine					  "cmdLine"  				//  2007/06/13
	//
	#define		CONST_regValName_quit						"quit"
	#define		QY_QUIT_VALNAME								CONST_regValName_quit
	#define		CONST_regValName_stop						"stop"
	#define		QY_STOP_VALNAME								CONST_regValName_stop
	#define		CONST_regValName_restart					"restart" 
	#define		CONST_qyModulesSubKey						"modules"  




#define		CONST_QYQUITVAL								1
#define		CONST_QYSTOPVAL								CONST_QYQUITVAL
#define		CONST_qyRestartVal							CONST_QYQUITVAL

#define		CONST_qyNameLen_dsn							64
#define		MAX_QY_DSNNAMELEN							CONST_qyNameLen_dsn				// dsn的名字最大长度
#define		CONST_maxConnectStrLen						256



#define		DEFAULT_qyPort_mis							8768							//  2007/03/21
#define		DEFAULT_qyRdPort							8767
#define		DEFAULT_qyMcServPort						8766
#define		DEFAULT_QY_MC_SERVPORT						DEFAULT_qyMcServPort
//
//#define		DEFAULT_qyPort_showInfo_cli					87657//7
#define		DEFAULT_qyPort_showInfo_serv				8764
//
#define		DEFAULT_qyPort_showInfo_cli					8762

//
//  #define		DEFAULT_qnmHttpSvrPort						8080
#define		DEFAULT_qyCfgVal_qnmProxyPort				8777

//
#define		DEFAULT_qyPort_hg							40001		//  9000
#define		DEFAULT_qyPort_hg_status					40002		//  

//
#define		DEFAULT_MCDAEMON_LCKFILENAME				"mkdl.lck"
#define		MCDAEMON_FORBAR_LCKFILENAME					"mkdlb.lck"
#define		MCAGENT_LCKFILENAME							"baj.lck"
#define		CONST_qyLckFileName_qnmResp					"qnr.lck"
#define		CONST_qyLckFileName_qyMc					"qbgM.lck"
#define		DEFAULT_qyLckFileName_qnmHttpSvr			"mkcd.lck"


#define		CONST_QY_nConnectRetries					3

#define		CONST_qyMaxThreads							128

//  #define		CONST_qyMaxLabelLen							512						//  暂定ListView最大列名长度
#define		CONST_qyMaxLabelLen							256						//  2006/08/01修改，暂定ListView最大列名长度
#define		CONST_qyMaxRegKeyLen						255						//  注册表键名的最大长度
#define		CONST_qyMaxRegValLen						1024					//  注册表键值的最大长度

#define		CONST_qnmPacketDrvName						"npf.sys"



#endif  /*  }  */


