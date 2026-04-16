
#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	"qymcMainCommon.h"
#include	"myresource.h"


#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"

#ifdef  __SUPPORT_HTMLEDIT__
#include	"myHtmlEditCtrl.h"
#endif

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
//#include	"DlgTalk.h"
#include	"dlgtalkproc.h"
#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"
//#include	"DlgInstantAssistant.h"

#include	<assert.h>
#ifndef  __WINCE__
//#include	"qyPs.h"
#endif
#include	"qmcDxSurfacePublic.h"
#include	"qmcConferenceWall.h"
#include	"isCliHelpPublic.h"
#include	"qmcCmdProc.h"
#include	"isCmdConst.h"

//#include	"DlgMsgList.h"

#include	"remoteAssistPublic.h"
#include	"qyString.h"
#include	"funcsForIsCliHelp.h"




 int  dlgTalk_shareMediaDevice(HWND  hDlg, int  iMenuId, unsigned  int  uiSubCapType, LPCTSTR  dev_sel)
{
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;

	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	TCHAR		displayName_aDev[MAX_monikerDisplayNameLen + 1] = _T("");
	TCHAR		displayName_vDev[MAX_monikerDisplayNameLen + 1] = _T("");
	void* pCapStuff = NULL;


	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;


	pCapStuff = pFuncs->pf_CAP_STUFF_new();
	if (!pCapStuff)  goto  errLabel;
	pFuncs->moniker.pf_addDevicesToMenu(pCapStuff, TRUE, NULL);

	//  2012/11/04
	int	level = 0;

	//  if  (  iMenuId  !=  ID_startShareMediaDevice1  )  
	{
		//  这里要选择音频和视频设备
#if 0
		HWND  hParent = hDlg;
		//
#ifdef  __DEBUG__
		hParent = ::GetDesktopWindow();
#endif
		//
		if (pProcInfo->showDlgSelectAvDev(hParent, pCapStuff, 0, NULL) != IDOK) {
			goto  errLabel;
		}

		//
#else
		//
#ifdef  __DEBUG__
		printAvDevs(pCapStuff);
#endif
		//
		if (selectAvDev(pCapStuff, dev_sel,  dev_sel)) {
			goto  errLabel;
		}



#endif
	}


	TCHAR				tBuf[256] = _T("");
	QY_REG  reg;
	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	lstrcpyn(reg.rootKey, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, sizeof(reg.rootKey));
	_sntprintf(reg.rootKey, mycountof(reg.rootKey), _T("%s\\%s"), reg.rootKey, qyGetDesByType(CONST_capTypeTable, CONST_capType_mediaDevice));

	HWND	hMgr = NULL;
	DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar_cur.getVar(hDlg);
	if (!pCurVar)  goto  errLabel;
	if (isTalkerShadowMgr(pCurVar->addr))  hMgr = hDlg;
	else {
		TALKER_shadow* pShadow = (TALKER_shadow*)pCurVar->pShadowInfo;
		if (!pShadow)  goto  errLabel;
		hMgr = pShadow->hMgr;
	}

	DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
	if (!pMgrVar)  goto  errLabel;

	//
	BOOL				bNoPrompt = true;
	//bNoPrompt  =  bNoPrompt_selectAvCompressor(CONST_capType_mediaDevice, uiSubCapType);

	//
	if (!bNoPrompt) {
		if (pProcInfo->viewDlgSelectAvCompressor(hDlg, pMgrVar->addr.idInfo, CONST_capType_mediaDevice, uiSubCapType, FALSE, FALSE, 0) != IDOK)  goto  errLabel;
	}

	//
	level = CONST_policyAvLevel_1080p;

	//
	pFuncs->pf_doCmd_startShareMediaDevice(pQyMc,  hMgr, pMgrVar, uiSubCapType, level, &pCapStuff);

errLabel:

	if (pCapStuff)  pFuncs->pf_CAP_STUFF_free(pCapStuff);

	return  0;
}


