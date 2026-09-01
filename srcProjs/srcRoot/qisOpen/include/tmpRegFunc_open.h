

#ifndef  __tmpRegFunc_open_h__
#define  __tmpRegFunc_open_h__	//  {


//
extern  "C"  int  tmpGetRegCfg_open(HKEY  hKeyRoot0, LPCTSTR  rootKey, LPCTSTR  cfgName, unsigned  int* puiType, char* cfgVal, unsigned  int* pSize);
extern  "C"  int  tmpSetRegCfg_open(HKEY  hKeyRoot0, LPCTSTR  rootKey, LPCTSTR  cfgName, unsigned  int  uiType, char* cfgVal, unsigned  int  cb);


//
#define		CONST_rootKey_ca									"Software\\Qycx\\misClient\\Scheduler\\ca"  

//
#define		CONST_rootKey_sm_init								"HKEY_CURRENT_USER\\Software\\Qycx\\misClient\\Scheduler"

#define		CONST_rootKey_qt_av 								"HKEY_CURRENT_USER\\Software\\Qycx\\misClient\\Scheduler\\av.0.0"

//
#define		CONST_rootKey_ca_sys_win32							"SOFTWARE\\WOW6432Node\\Qycx\\misClient\\Scheduler\\ca"

//
#define		CONST_regValName_caRandom_prefix					"caRandom"
//
#define		CONST_regValName_ca_sendData_prefix					"ca_sendData"
#define		CONST_regValName_ca_sendDataResp_prefix				"ca_sendDataResp"

//
#define		CONST_regValName_ca_chkUsrKeyResp_prefix			"ca_chkUsrKeyResp"

//
#define		CONST_regValName_ca_pinRetryCountResp_prefix		"ca_pinRetryCountResp"


//
#define		CONST_regValName_serv_random_prefix					"serv_random"
#define		CONST_regValName_serv_cert_prefix					"serv_cert"
#define		CONST_regValName_serv_signData_prefix				"serv_signData"

//
#define		CONST_regValName_cli_cert_prefix					"cli_cert"
#define		CONST_regValName_cli_signData_prefix				"cli_signData"

//
#define		CONST_regValName_ca_getRandomResp_prefix			"caRandomResp"



//
#endif  //  }

