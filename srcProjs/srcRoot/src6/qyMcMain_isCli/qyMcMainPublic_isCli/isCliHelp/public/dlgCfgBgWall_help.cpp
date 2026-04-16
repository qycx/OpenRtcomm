
//
#include	"stdafx.h"
#include	<stdlib.h>
#include	<math.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"
#include	"qmcVWall.h"
#include	"WallTalkers.h"
//#include	"DlgDynBmps.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"

#include	"qyCusResTemp.h"

#include	"qyAvRecordPublic.h"

#include	"sp.h"
#include	"qmcCommFunc_isCli.h"
#include	"qyMessengerHelpPublic.h"

//
//#include "DlgCfgBgWall.h"
//#include "afxdialogex.h"

//
#include	"isCliHelpPublic.h"


__declspec(dllexport) int  getBgWallCfg(QY_MESSENGER_ID* pIdInfo, BgWall_cfg* pCfg)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int  iRet = -1;

	unsigned int uiCapType = CONST_capType_av;
	unsigned int uiSubCapType = 0;
	int iCapUsage = 0;

	//
	QY_MC* pQyMc = QY_GET_GBUF();
	QY_REG				reg;
	TCHAR				tBuf[256] = _T("");
	TCHAR* pRegVal = NULL;
	TCHAR				regValBuf[256] = _T("");
	unsigned  short		usTmp1 = 0;
	unsigned  short		usTmp2 = 0;
	unsigned  short		usTmp_rows = 0;
	unsigned  short		usTmp_cols = 0;

	memset(&reg, 0, sizeof(reg));

	BgWall_cfg* pPolicy = (BgWall_cfg*)pCfg;
	if (!pPolicy)  goto  errLabel;
	memset(pPolicy, 0, sizeof(pPolicy[0]));

	reg.hKeyRoot0 = HKEY_CURRENT_USER;
#if  0
	_sntprintf(reg.rootKey, mycountof(reg.rootKey), _T("%s\\av"), pQyMc->cfg.pSysCfg->rootKey_qnmScheduler);
#endif
	get_idRegRootKey_qmc(pIdInfo, uiCapType, uiSubCapType, iCapUsage, reg.rootKey, mycountof(reg.rootKey));

	//
#if  10
	//  2014/10/16	
	usTmp1 = 0;
	pRegVal = CONST_regValName_useBgWall;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		usTmp1 = _ttol(tBuf);
	}
	if (pPolicy->useBgWall != usTmp1) {
		pPolicy->useBgWall = usTmp1;
	}
	//
	usTmp1 = 0;
	pRegVal = CONST_regValName_ucbAddBgWallToConf;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		usTmp1 = _ttol(tBuf);
	}
	if (pPolicy->ucbAddBgWallToConf != usTmp1) {
		pPolicy->ucbAddBgWallToConf = usTmp1;
	}
	//
	usTmp1 = 0;
	pRegVal = CONST_regValName_ucbJoinInBgWall;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		usTmp1 = _ttol(tBuf);
	}
	if (pPolicy->ucbJoinInBgWall != usTmp1) {
		pPolicy->ucbJoinInBgWall = usTmp1;
	}
	//
	usTmp1 = 0;
	pRegVal = CONST_regValName_ucbAutoLayout;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		usTmp1 = _ttol(tBuf);
	}
	if (pPolicy->ucbAutoLayout != usTmp1) {
		pPolicy->ucbAutoLayout = usTmp1;
	}
	//

	//
	pRegVal = CONST_regValName_bgWallFileName;
	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0))  tBuf[0] = 0;
	safeTcsnCpy(tBuf, pPolicy->bgWallFileName, mycountof(pPolicy->bgWallFileName));

	//
	usTmp1 = 0;
	pRegVal = CONST_regValName_ucbNeverJoinInBgWall;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		usTmp1 = _ttol(tBuf);
	}
	if (pPolicy->ucbNeverJoinInBgWall != usTmp1) {
		pPolicy->ucbNeverJoinInBgWall = usTmp1;
	}
#endif

	usTmp1 = DEFAULT_usPollingIntervalInS;
	pRegVal = CONST_regValName_usPollingIntervalInS;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)
		&& _ttol(tBuf))
	{
		usTmp1 = _ttol(tBuf);
	}
	if (pPolicy->usPollingIntervalInS != usTmp1) {
		pPolicy->usPollingIntervalInS = usTmp1;
	}


#define		DEFAULT_bgWall_rows		1
#define		DEFAULT_bgWall_cols		5
	//
	usTmp_rows = DEFAULT_bgWall_rows;  //  rows;
	usTmp_cols = DEFAULT_bgWall_cols;	//  cols;
	pRegVal = CONST_regValName_layout;
	_sntprintf(regValBuf, mycountof(regValBuf), _T("%s%I64u"), pRegVal, pIdInfo->ui64Id);
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, regValBuf, (char*)tBuf, sizeof(tBuf), 0)) {
		TCHAR* p, * p1, tmpBuf[256] = _T("");
		p = tBuf;
		p1 = _tcschr(p, ',');
		_tcsncpy(tmpBuf, p, (p1 - p));
		usTmp_rows = _ttol(tmpBuf);
		p = p1 + 1;
		_tcscpy(tmpBuf, p);
		usTmp_cols = _ttol(tmpBuf);
	}
	//	
	if (fixBgWallPolicy(pIdInfo, &usTmp_rows, &usTmp_cols, NULL, 0)) {
		usTmp_rows = DEFAULT_bgWall_rows;
		usTmp_cols = DEFAULT_bgWall_cols;
		//
		int  n_wallMems = my_getnGrpMems_isCli(pIdInfo) - 1;
		if (n_wallMems > 0) {
			usTmp_cols = min(usTmp_cols, n_wallMems);
		}

	}
	//
	if (pPolicy->bgWallLayoutCfg.usRows_bg != usTmp_rows || pPolicy->bgWallLayoutCfg.usCols_bg != usTmp_cols) {

		//			
		pPolicy->bgWallLayoutCfg.usRows_bg = usTmp_rows;
		pPolicy->bgWallLayoutCfg.usCols_bg = usTmp_cols;

	}



	iRet = 0;

errLabel:
	return  iRet;
}


int  fixBgWallPolicy(QY_MESSENGER_ID* pIdInfo, unsigned  short* pusRows, unsigned  short* pusCols, TCHAR* tHint, unsigned  int  uiCnt_tHint)
{
	int  iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	TCHAR		tBuf[256] = _T("");

	//  2014/10/13

	BOOL  bValValid = TRUE;

	//
	int  n_wallMems = my_getnGrpMems_isCli(pIdInfo);	//    -  1;
	if (n_wallMems > 0) {
		if (*pusCols > n_wallMems)  *pusCols = min(n_wallMems, *pusCols);
	}

	if (!*pusRows || !*pusCols) {
		bValValid = FALSE;
		if (1) {
			_sntprintf(tBuf, mycountof(tBuf), _T("%s"), getResStr(0, &pQyMc->cusRes, CONST_resId_bgWallSettingsErr_0));
		}
	}
	//
#define		MAX_bgWall_videos				200	//  2017/09/28	CONST_maxCapImages
#define		MAX_bgWall_videos_win32			5

	int  max_nTotal = bAppX64() ? MAX_bgWall_videos : MAX_bgWall_videos_win32;
	if (max_nTotal < *pusRows * *pusCols) {
		bValValid = FALSE;
		if (1) {
			_sntprintf(tBuf, mycountof(tBuf), _T("%s %d"), getResStr(0, &pQyMc->cusRes, CONST_resId_bgWallSettingsErr_1), max_nTotal);
		}
	}


	if (!bValValid)  goto  errLabel;


	iErr = 0;
errLabel:

	if (tHint)  safeTcsnCpy(tBuf, tHint, uiCnt_tHint);

	return  iErr;

}

__declspec(dllexport) int  saveBgWallPolicy_neverJoinInBgWall(QY_MESSENGER_ID* pIdInfo, unsigned char ucbNeverShowBgWall)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int  iRet = -1;

	QY_MC* pQyMc = QY_GET_GBUF();
	QY_REG				reg;
	TCHAR				tBuf[256] = _T("");
	TCHAR* pRegVal = NULL;

	//
	unsigned int uiCapType = CONST_capType_av;
	unsigned int uiSubCapType = 0;
	int iCapUsage = 0;

	//
	memset(&reg, 0, sizeof(reg));

	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	get_idRegRootKey_qmc(pIdInfo, uiCapType, uiSubCapType, iCapUsage, reg.rootKey, mycountof(reg.rootKey));

	pRegVal = CONST_regValName_ucbNeverJoinInBgWall;
	_sntprintf(tBuf, mycountof(tBuf), _T("%d"), ucbNeverShowBgWall);
	qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, tBuf);

	return  0;
}

