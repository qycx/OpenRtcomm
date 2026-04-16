

#ifndef  __qmCaProc_h__
#define  __qmCaProc_h__	//  {



typedef  struct		{
	//
	bool			bNeedQuit;		//  set by qmcLogin

	//
	HANDLE			hProcess_ca;
	DWORD			dwProcessId_ca;
	//
	int				tn_process_ca;

	//
	bool			m_bDisableCa;

}					Tool_ca;


//
#define		CONST_caToolType_bjca				1
#define		CONST_caToolType_bjca1				2
//
#define		CONST_caToolType_jdzyServ			7
#define		CONST_caToolType_jdzyCli			8
#define		CONST_caToolType_jdzyCli_sx			9




//
typedef  struct {


	//
	Tool_ca			toolCa;

	//	
	struct {

		TCHAR		tUsrName[256];

	}				resp;


}		Var_ca_qmd;



//
__declspec(dllexport) int getUsrInfo_ca(LPCTSTR  installDir, LPCTSTR  statusLogFile, QY_COMM_AUTHINFO_MIS* pAuthInfo, Var_ca_qmd* pVcq);

//
typedef  struct  __param_ca_getRandom_t {

	//
	char					ca_random[256];

}		 Param_ca_getRandom;


//
__declspec(dllexport) int ca_getRandom_jdzy(LPCTSTR  installDir, LPCTSTR  statusLogFile, Param_ca_getRandom* pParam, Var_ca_qmd* pVcq);





//
int  createTool_ca(LPCTSTR  installDir, int caToolType, LPCTSTR  who_showInfo, int iCmd, bool bSys, TCHAR  *  devPrefix,  bool bDev, bool  bFullCmp,  char  *  caServIp,  int caServPort,  char  *  pwd,  LPCTSTR  logFile,  Tool_ca* pToolCa);
int  closeTool_ca(Tool_ca* pToolCa);

//
//int qmd_saveCaServCfg( int caToolType, char  *  caGwIp,  int  caGwPort  );
int qmd_saveCaServCfg(int caToolType, char* caGwCfg);
__declspec(dllexport)int  qmd_getCaServCfg(int caToolType,  char  *  caGwIp,  int sizeof_caGwIp,  int  *  piCaGwPort, char  *  hgIp,  int  sizeof_hgIp,  int  *  piHgPort  );


//
typedef  struct {
	
	//
	bool  bExists_usrKey;

	//
	TCHAR  tUsrName[128];


}  TMP_caTool_result;


//
int  parse_sendDataResp(  char  *  resp,  TMP_caTool_result  *  pResult  );


#endif  //  }


