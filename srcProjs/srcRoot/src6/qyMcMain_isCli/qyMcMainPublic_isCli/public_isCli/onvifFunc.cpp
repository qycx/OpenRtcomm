
#include "stdafx.h"
//#include "myresource.h"
#include	"qyMcMainCommon.h"
#include	"dlgShareDynBmpsProc.h"



//
QY_DMITEM  CONST_onvifRuleTypeTable[]  =  
{
	{		CONST_onvifRuleType_rtspUrl,			(TCHAR*)_T(  "RTSP"  ),		},
	{		CONST_onvifRuleType_discovery,			(TCHAR*)_T(  "discovery"  ),	},
	{		CONST_onvifRuleType_probe,				(TCHAR*)_T(  "probe"  ),		},
	{		-1,		},
};


//
int  deleteCfg_rtspUrlList(  )
{
	int		iErr	=	-1;
	QY_REG	reg;

	memset(  &reg,  0,  sizeof(  reg  )  );
	TCHAR			tBuf[256];

	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//safeTcsnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	getRegRootKey_qmc(  CONST_capType_av,  CONST_subCapType_webcam,  0,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"   ),  reg.rootKey,  _T(  CONST_regKeyName_rtspUrl  )  );

	int  i;
	for  (  i  =  MIN_usIndex_obj_rtspUrl;  i  <=  MAX_usIndex_obj_rtspUrl;  i  ++  )  {
		TCHAR  tVal[256];
		 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _ltot(  i,  tBuf,  10  )  );
	}


	if  (  ERROR_SUCCESS  !=  RegDeleteKey(  reg.hKeyRoot0,  reg.rootKey  )  )  goto  errLabel;
	
	iErr  =  0;
errLabel:


	return  iErr;
}


