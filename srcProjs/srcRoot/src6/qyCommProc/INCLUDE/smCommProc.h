

#ifndef  __smCommProc_h__
#define  __smCommProc_h__	//  {

//
//
#define		CONST_cfgName_sm_devAsScreen				_T(  "sm_devAsScreen")


//
#define		DEFAULT_smCfgDir							_T(  "d:\\qycx\\")
//
#define		CONST_cfgFileName_tmInit					_T(  "tmInit.ini")
#define		CONST_logFileName_smTmp						_T(  "smTmp.log"  )
//
#define		CONST_cfgFileName_hkPortStatus				_T(  "hkPortStatus.ini")

//
#define		CONST_cfgFileName_ipcProcInit				_T(  "ipcProcInit.ini"  )
#define		CONST_cfgFileName_shareProcInit				_T(  "shareProcInit.ini"  )


//
#define		CONST_logFileName_qmcStatus					_T(  "qmc_status.log")

//
#define		CONST_cfgFileName_cli_smCfg					_T(  "cli_smCfg.ini")

//
#define		CONST_cfgFileName_mcu_smCfg					_T(  "mcu_smCfg.ini")

//
#define		CONST_cfgFileName_mgr_smCfg					_T(  "mgr_smCfg.ini")
#define		CONST_cfgFileName_mgr_hgMcuCfg				_T(  "mgr_hgMcuCfg.ini"  )

//
#define		CONST_subDir_log							_T(  "log\\"  )

//
#define		CONST_cfgFileName_qmd_status				_T(  "qmd_status.ini"  )
#define		CONST_cfgFileName_qmd_statusLog				_T(  "qmd_status.log"  )

#define		CONST_cfgFileName_qmd_hgPolicy				_T(  "qmd_hgPolicy.ini"  )

#define		CONST_cfgFileName_qmd_rdFile				_T(  "qm_rd.ini"  )


//
int parseCaServCfg(char* caServCfg, char* ip, int cntof_ip, int* piPort, char* hg_ip, int cntof_hg_ip, int* hgPort);




#endif  //  }


