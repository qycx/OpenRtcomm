
#ifndef  __QYNMSMODULE_H__
#define  __QYNMSMODULE_H__	/*  {  */

#include	"qyCommonEx.h"

#include	"qyPreCustom.h"
#include	"qyCustom.h"

#include	"qyWmComm.h"
#include	"qyCommCommon.h"

#include	"qyLicense.h"
#include	"qyCommProc.h"
#include	"qyModuleFunc.h"
#include	"qnmCommProc.h"
#include	"qnmCommProc1.h"
#include	"qyImcCommProc.h"
#include	"qySnmpCommProc.h"
#include	"qnmsCommProc.h"

#include	"qyGenericDaemon.h"

#include	"qyImcComm.h"
#include	"qyImcCommoncfg.h"
#include	"qyImcLogFunc.h"
#include	"qyImcSndObjs.h"
#include	"qyImcPublic.h"

#include	"qnmPrecomp.h"

#include	"qnmCustom.h"
#include	"qnmCustomComm.h"

#include	"qyDbCommon.h"


#ifdef  __cplusplus
  extern  "C"  {
#endif
	
	  
#define		CONST_qyNmsMaxThreads		10



typedef  struct	 __qyNmsCfg_t			{
				
				 WCHAR					installDir[QY_MAXPATHLEN + 1];				//  °²×°Ä¿Â¼
				 		
				 SOCK_TIMEOUT			to;
				 
				 NMS_SCAN_STRUCT		scanStructs[3];

				 unsigned  char			ucbStartRegScan;
				 unsigned  char			ucbStartRespForUnreg;
				 				 
}		 QY_NMS_CFG;

typedef  struct  __qyNmsDaemon_t  {
					
					MACRO_qyModuleCommonMems
		 
					QY_NMS_CFG				cfg;
					
					QWM_MACS_INFO			macsInfo;

					HANDLE					hThreads[CONST_qyNmsMaxThreads];	
					QY_THREADPROC			threadProcs[CONST_qyNmsMaxThreads];
					void			*		pThreadParams[CONST_qyNmsMaxThreads];
													
					void			*		pModule;
					void			*		pDb;

					QY_ENC_CTX				encCtx,  commEncCtx;  
					unsigned  char			ucbEncInited;

					QY_LICENSE_CTX			licenseCtx;

					QY_LOG_CTX				logCtx;

					struct					{
						unsigned  char		unused;
					}						status;
}	QY_NMS_DAEMON;


#include	"qnmsModuleDaemon.h"

#ifdef  __cplusplus
  }
#endif


DWORD  WINAPI  qnmsAuditThreadProc(  LPVOID  lp  );





#endif  /*  }  */



