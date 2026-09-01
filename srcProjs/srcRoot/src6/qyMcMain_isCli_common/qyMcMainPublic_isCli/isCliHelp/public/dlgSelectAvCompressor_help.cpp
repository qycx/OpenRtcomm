
#include "stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
//#include "DlgSelectAvCompressor.h"
//#include "afxdialogex.h"

#include	"qyOpenShellCommon.h"
#include	"dlgTalkProc.h"

#include	"isCliHelpPublic.h"
#include	"isCliD3dPublic.h"
//  #include	"funcsForIsCliHelp.h"

#include	"qyCusResTemp.h"
#include	"policyIsClientFunc.h"

#include	"dyn_isCliD3d_public.h"


int  my_getnGrpMems_isCli(QY_MESSENGER_ID* pIdInfo)
{
	int  n_grpMems = -1;

	QY_MC* pQyMc = QY_GET_GBUF();

	void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
	CQnmDb				db;
	if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
	pDb = db.m_pDbMem->pDb;
#endif

	//	
	QY_MESSENGER_ID* pIdInfo_grp = pIdInfo;
	n_grpMems = getnGrpMems_isCli(pDb, pQyMc->cfg.db.iDbType, pIdInfo_grp);
errLabel:

	return  n_grpMems;
}


__declspec(dllexport) int  getTalkerPolicy(QY_MESSENGER_ID* pIdInfo, TALKER_policy* pTALKER_policy)
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

	TALKER_policy* pPolicy = (TALKER_policy*)pTALKER_policy;
	if (!pPolicy)  goto  errLabel;
	memset(pPolicy, 0, sizeof(pPolicy[0]));

	reg.hKeyRoot0 = HKEY_CURRENT_USER;
#if  0
	_sntprintf(reg.rootKey, mycountof(reg.rootKey), _T("%s\\av"), pQyMc->cfg.pSysCfg->rootKey_qnmScheduler);
#endif
	getRegRootKey_qmc(uiCapType, uiSubCapType, iCapUsage, reg.rootKey, mycountof(reg.rootKey));

	//
	//
	//  2017/06/25
#define		DEFAULT_ucbConfMgr_starter		FALSE
	//
	usTmp1 = DEFAULT_ucbConfMgr_starter;
	pRegVal = CONST_regValName_ucbConfCtrl_starter;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		usTmp1 = _ttol(tBuf);
	}
	if (pPolicy->ucbConfCtrl_starter != usTmp1) {
		pPolicy->ucbConfCtrl_starter = usTmp1;
	}

	//
#define		DEFAULT_ucb2Streams				false
	//
	usTmp1 = DEFAULT_ucb2Streams;
	pRegVal = CONST_regValName_ucb2Streams;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		usTmp1 = _ttol(tBuf);
	}
#if 0
	if (pPolicy->ucb2Streams != usTmp1) {
		pPolicy->ucb2Streams = usTmp1;
	}
#endif

	//
#ifdef  __DEBUG__
		#if  0
			 pPolicy->ucb2Streams  =  true;
			 traceLog((TCHAR*)_T("for test: getTalkerPolicy: ucb2Streams set to true")  );
		#endif
#endif


	//
	iRet = 0;

errLabel:
	return  iRet;
}

//
__declspec(dllexport)  BOOL  bNoPrompt_selectAvCompressor(unsigned  int  uiCapType, unsigned  int  uiSubCapType)
{
	BOOL				bNoPrompt = FALSE;

	QY_MC* pQyMc = QY_GET_GBUF();


	TCHAR				tBuf[256] = _T("");
	QY_REG				reg;


	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	lstrcpyn(reg.rootKey, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, sizeof(reg.rootKey));

	//  2014/04/08
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_noPrompt_selAvCompressor, (char*)tBuf, sizeof(tBuf), 0) && _ttol(tBuf)) {
		bNoPrompt = TRUE;
	}

	return  bNoPrompt;
}


BOOL  bSetNoPrompt_selectAvCompressor(unsigned  int  uiCapType, unsigned  int  uiSubCapType, BOOL  bNoPrompt)
{

	QY_MC* pQyMc = QY_GET_GBUF();


	TCHAR				tBuf[256] = _T("");
	QY_REG				reg;


	TCHAR* pRegVal = NULL;


	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	lstrcpyn(reg.rootKey, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, sizeof(reg.rootKey));


	pRegVal = CONST_regValName_noPrompt_selAvCompressor;
	//
	if (bNoPrompt)  qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, _T("1"));
	else  qyDelRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal);

	return  0;
}


