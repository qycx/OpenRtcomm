

#include	"stdafx.h"
#include	<tchar.h>
#ifndef  __WINCE__
#include	<vfw.h>
#else
#ifdef  __TEST__
#include	<vfw.h>
#endif
#include	<mmreg.h>
#include	<msacm.h>
#endif

#include	<shlobj.h>

#include	"qyMcMainCommon.h"
#include	"myresource.h"

#include	"tmpCeLib.h"

//#include	"DlgPolicyIsClient.h"

#ifndef  __WINCE__
//  #include	"DlgVideoCompressors.h"
#endif

#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qyCusResTemp.h"
#ifndef  __WINCE__
//#include	"qyPs.h"
#endif
#include	"qmcDmoPublic.h"
#include	"myfourcc.h"

//  #include	"DlgPolicyAv.h"

#include	"policyAvParams.h"
#include	"policyIsClientFunc.h"


//
//#include	"msAecCommon.h"


//
#include	"isCliHelpPublic.h"
#include	"qycusResTemp.h"


//
__declspec(dllexport)  int  setSaveMsgFlg(CCtxQmc* pProcInfo1, BOOL  bEnable)
{

	int  iErr = -1;
	// TODO: Add your control notification handler code here
	int  idc;

	QY_REG	reg;
	QY_MC* pQyMc = QY_GET_GBUF();
	//MC_VAR_isCli* pProcInfo1 = QY_GET_procInfo_isCli();
	if (!pProcInfo1) {
		return  -1;
	}

	memset(&reg, 0, sizeof(reg));
	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	//  safeStrnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	lstrcpyn(reg.rootKey, CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), mycountof(reg.rootKey));

	TCHAR* pRegVal = (TCHAR*)_T(CONST_regValName_ucbSaveMsg);

	POLICY_isClient* pPolicy = &pProcInfo1->cfg.policy;

	if (bEnable) {

		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, _T("1"));
		pPolicy->ucbSaveMsg = TRUE;
		//
		if (pPolicy->dirToSaveMsg[0]) {
			if (!bDir(pPolicy->dirToSaveMsg)) {
				pRegVal = (TCHAR*)_T(CONST_regValName_dirToSaveMsg);
				qyDelRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal);
				pPolicy->dirToSaveMsg[0] = 0;
			}
		}
		if (!pPolicy->dirToSaveMsg[0]) {
			if (!SHGetSpecialFolderPath(NULL, pPolicy->dirToSaveMsg, CSIDL_PERSONAL, TRUE))  goto  errLabel;
			if (trailDir(pPolicy->dirToSaveMsg, mycountof(pPolicy->dirToSaveMsg)))  goto  errLabel;
			_sntprintf(pPolicy->dirToSaveMsg, mycountof(pPolicy->dirToSaveMsg), _T("%s%s"), pPolicy->dirToSaveMsg, _T(CONST_subDir_msg));
			if (!bDir(pPolicy->dirToSaveMsg)) {
				BOOL  bRet = CreateDirectory(pPolicy->dirToSaveMsg, NULL);
				if (!bRet && GetLastError() != ERROR_ALREADY_EXISTS) {
					//qyDisplayLastError(  "Creating msgDir"  );  
					goto  errLabel;
				}
			}
		}
		//
	}
	else {
		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, _T("0"));
		pPolicy->ucbSaveMsg = FALSE;
	}

	iErr = 0;

errLabel:
	return  iErr;
}



