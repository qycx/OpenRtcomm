
#ifndef  __ipcProcCfg_h__
#define  __ipcProcCfg_h__		//  {





//
#define		CONST_cfgName_bEnableIpc				"bEnableIpc"
#define		CONST_cfgName_iNvrType					"iNvrType"

#define		CONST_cfgName_NvrLog					 _T("nvrLog")
#define		CONST_cfgName_devType					 _T("ipcType")

//
#define		CONST_cfgName_nvrIp						"nvrIp"
#define		CONST_cfgName_nvrUsr					"nvrUsr"
#define		CONST_cfgName_nvrPwd					"nvrPwd"

#define		CONST_cfgName_bEnableShare				"bEnableShare"
#define		CONST_cfgName_bAutoShare				"bAutoShare"
#define		CONST_cfgName_rtspUrl					"rtspUrl"



enum Nvr_type {
	Nvr_type_dh = 1,
	Nvr_type_hik = 2,
	Nvr_type_d4k = 3,
};

//
typedef  struct  __ipcProc_initCfg_t	{
				 
				 //
				 bool					m_bEnableIpc;

				 //
				 int					m_iNvrType;
				 int					m_iNvrLog;
				 int					m_iDevType;

				 //
				 char					nvrIp[CONST_qyMaxIpLen + 1];
				 TCHAR					nvrUsr[128];
				 char					nvrPwd[128];




				 //
}		 IpcProcInitCfg;


typedef  struct  __shareProc_initCfg_t {

	bool					m_bEnableShare;
	bool					m_bAutoShare;
	//
	char					rtspUrl[QY_MAXPATHLEN + 1];

	//
}		 ShareProcInitCfg;


#endif  //  }



