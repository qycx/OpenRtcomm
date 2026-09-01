// AssetMgrModuleDaemon.h: interface for the CAssetMgrModuleDaemon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSETMGRMODULEDAEMON_H__21822D2B_20D9_4933_ABEF_F78779F873B4__INCLUDED_)
#define AFX_ASSETMGRMODULEDAEMON_H__21822D2B_20D9_4933_ABEF_F78779F873B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include	"qyCommonEx.h"

#include	"qyPreCustom.h"
#include	"qyCustom.h"

#include	"qyWmComm.h"
#include	"qyCommCommon.h"

#include	"qyLicense.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmCommProc1.h"

//  #include	"traceLogA.h"

#include	"qyDaemonPublic.h"

#include	"qyImcCommProc.h"
#include	"qySnmpCommProc.h"
#include	"qnmsCommProc.h"

#include	"qyImcComm.h"
#include	"qyImcCommoncfg.h"
#include	"qyImcLogFunc.h"
#include	"qyImcSndObjs.h"
#include	"qyImcPublic.h"

#include	"qnmPrecomp.h"

#include	"qnmCustom.h"
#include	"qnmCustomComm.h"

#include	"qyDbCommon.h"

#include	"qyTCharCommProc.h"

class CAssetMgrModuleDaemon : public CQyGenericDaemon  
{
	#define		CONST_qyNmsMaxThreads		10



typedef  struct	 __assetMgrCfg_t			{
				
				 TCHAR					installDir[QY_MAXPATHLEN + 1];				//  °²×°Ä¿Â¼

				 QNM_DB_CFG				db;
				 		
				 SOCK_TIMEOUT			to;
				 
				 NMS_SCAN_STRUCT		scanStructs[1];

				 unsigned  char			ucbStartRegScan;
				 unsigned  char			ucbStartRespForUnreg;
				 	
				 //  
				 QNM_MODULES_LOADEDINFO	modulesLoadedInfo;

}		 ASSET_MGR_CFG;

typedef  struct  __assetMgrDaemon_t  {
					
					MACRO_qyModuleCommonMems
		 
					ASSET_MGR_CFG			cfg;
					
					QWM_MACS_INFO			macsInfo;

					HANDLE					hThreads[CONST_qyNmsMaxThreads];	
					QY_THREADPROC			threadProcs[CONST_qyNmsMaxThreads];
					void			*		pThreadParams[CONST_qyNmsMaxThreads];
													
					void			*		pModule;
					void			*		pDb;

					QY_ENC_CTX				encCtx,  commEncCtx;  
					unsigned  char			ucbEncInited;

					QY_LICENSE_CTX			licenseCtx;			//  2007/03/01

					QY_LOG_CTX				logCtx;

					struct					{
						unsigned  char		unused;
					}						status;
}	ASSET_MGR_DAEMON;

public:
	ASSET_MGR_DAEMON		var;

public:
	CAssetMgrModuleDaemon();
	virtual ~CAssetMgrModuleDaemon();

};

#endif // !defined(AFX_ASSETMGRMODULEDAEMON_H__21822D2B_20D9_4933_ABEF_F78779F873B4__INCLUDED_)
