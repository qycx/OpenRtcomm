
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
#include	<fcntl.h>
#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__

	//  #include	<Qedit.h>
#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>

#include	"qmcDmoPublic.h"
#ifndef  __WINCE__
#include	"qmcVideoCapture_dx.h"
#endif
#include	"myfourcc.h"

#include	"qyCusResTemp.h"

//  #include	"qyMc.h"
#include	"qyGuiCommProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecordPublic.h"

#include	"myresource.h"

//#include	"DlgSelectAvDev.h"

//  #include	"DlgShareDynBmps.h"

#include	"qyOpenShellCommon.h"
#include	"dlgTalkProc.h"
#include	"qmcCmdProc.h"

//  #include	"DlgProgress.h"
#include	"tmpCeLib.h"
#include	"funcsForIsCliHelp.h"
#include	"isCliHelpPublic.h"
#include <smCommProc.h>


__declspec(dllexport)
int  selectAvDev(void  *  pCapStuffParam, LPCTSTR  aDev_expected,  LPCTSTR  vDev_expected)
{
	int  iErr = -1;
	CAP_STUFF* pCapStuff = (CAP_STUFF*)pCapStuffParam;

	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);

	if (!aDev_expected)  aDev_expected = _T("");

	//
	if (!vDev_expected || !vDev_expected[0]) return -1;

	//
	TCHAR  tName[256];
	int  i;


	//
	for (i = 0; i < mycountof(pCapStuff->rgpmVideoMenu); i++) {
		if (!pCapStuff->rgpmVideoMenu[i])  continue;
		tName[0] = 0;
		//  getMonikerFriendlyName(  pCapStuff->rgpmVideoMenu[i],  tName,  mycountof(  tName  )  );
		pFuncs->moniker.pf_getMonikerProp(pCapStuff->rgpmVideoMenu[i], CONST_moniker_FriendlyName, tName, mycountof(tName));
		//_sntprintf(tBuf, mycountof(tBuf), _T("%d: %s"), i + 1, tName);
		//((CComboBox*)GetDlgItem(idc))->InsertString(-1, tBuf);
		if (!_tcsnicmp(tName, vDev_expected, lstrlen(vDev_expected))) {

			pFuncs->pf_myChooseDevices(pCapStuff, pCapStuff->rgpmVideoMenu[i], pCapStuff->pmAudio);

			break;
		}
		//
		continue;
	}
	if (i == mycountof(pCapStuff->rgpmVideoMenu)) {
		goto  errLabel;
	}

	//
	if (aDev_expected[0]) {

		//
		for (i = 0; i < mycountof(pCapStuff->rgpmAudioMenu); i++) {
			if (!pCapStuff->rgpmAudioMenu[i])  continue;
			tName[0] = 0;
			//  getMonikerFriendlyName(  pCapStuff->rgpmVideoMenu[i],  tName,  mycountof(  tName  )  );
			pFuncs->moniker.pf_getMonikerProp(pCapStuff->rgpmAudioMenu[i], CONST_moniker_FriendlyName, tName, mycountof(tName));
			//_sntprintf(tBuf, mycountof(tBuf), _T("%d: %s"), i + 1, tName);
			//((CComboBox*)GetDlgItem(idc))->InsertString(-1, tBuf);
			if (!_tcsnicmp(tName, aDev_expected, lstrlen(aDev_expected))) {

				pFuncs->pf_myChooseDevices(pCapStuff, pCapStuff->pmVideo,  pCapStuff->rgpmAudioMenu[i]);

				break;
			}
			//
			continue;
		}

	}




	//
	iErr = 0;
	errLabel:
	return  iErr;
}


//
__declspec(dllexport)
int  printAvDevs(void* pCapStuffParam)
{
	int  iErr = -1;
	CAP_STUFF* pCapStuff = (CAP_STUFF*)pCapStuffParam;

	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);


	TCHAR  tName[256];
	int  i;
	for (i = 0; i < mycountof(pCapStuff->rgpmVideoMenu); i++) {
		if (!pCapStuff->rgpmVideoMenu[i])  continue;
		tName[0] = 0;
		//  getMonikerFriendlyName(  pCapStuff->rgpmVideoMenu[i],  tName,  mycountof(  tName  )  );
		pFuncs->moniker.pf_getMonikerProp(pCapStuff->rgpmVideoMenu[i], CONST_moniker_FriendlyName, tName, mycountof(tName));
		//_sntprintf(tBuf, mycountof(tBuf), _T("%d: %s"), i + 1, tName);
		//((CComboBox*)GetDlgItem(idc))->InsertString(-1, tBuf);

		//
		traceLog((TCHAR*)_T("[%s]"), tName);

		//
		continue;
	}

	iErr = 0;
errLabel:
	return  iErr;
}


//
__declspec(dllexport)
int  dumpAvDevs(void* pCapStuffParam)
{
	int  iErr = -1;
	CAP_STUFF* pCapStuff = (CAP_STUFF*)pCapStuffParam;

	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);

	FILE* fp = NULL;

	fp = fopen("d:\\qycx\\dumpAvDevs.ini", "w");
	if (!fp)  goto  errLabel;

	TCHAR  tName[256];
	int  i;
	for (i = 0; i < mycountof(pCapStuff->rgpmVideoMenu); i++) {
		if (!pCapStuff->rgpmVideoMenu[i])  continue;
		tName[0] = 0;
		//  getMonikerFriendlyName(  pCapStuff->rgpmVideoMenu[i],  tName,  mycountof(  tName  )  );
		pFuncs->moniker.pf_getMonikerProp(pCapStuff->rgpmVideoMenu[i], CONST_moniker_FriendlyName, tName, mycountof(tName));
		//_sntprintf(tBuf, mycountof(tBuf), _T("%d: %s"), i + 1, tName);
		//((CComboBox*)GetDlgItem(idc))->InsertString(-1, tBuf);

		//
		traceLog((TCHAR*)_T("[%s]"), tName);
		_ftprintf(fp, _T("[%s]\n"), tName);

		//
		continue;
	}

	iErr = 0;
errLabel:
	if (fp) {
		fclose(fp);
	}
	return  iErr;
}




//
__declspec(dllexport)int getCurrentCameraName(HWND  hDlgTalk, TCHAR* name, int cntofName)
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	HWND  hCur = hDlgTalk;
	CHelp_getDlgTalkVar  help_getDlgTalkVar;
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hCur);
	if (!pCurVar)  goto  errLabel;

	HWND  hMgr = hCur;
	DLG_TALK_var* pMgrVar = pCurVar;

	if (!isTalkerShadowMgr(pCurVar->addr)) {
		TALKER_shadow* pShadow = (TALKER_shadow*)pCurVar->pShadowInfo;
		hMgr = pShadow->hMgr;
		pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
		if (!pMgrVar)  goto  errLabel;
	}

	if (!pMgrVar->av.taskInfo.bTaskExists) goto  errLabel;

	QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, pMgrVar->av.iIndex_sharedObj_localAv);
	if (!pSharedObj)  goto  errLabel;

	TCHAR  friendlyName[256];
	friendlyName[0] = 0;

	int i;
	for (i = 0; i < 1; i++)
	{
		CAP_procInfo_bmpU* pCapBmp = getCapBmpBySth(pProcInfo, i, 0);
		if (!pCapBmp)  continue;
		switch (pCapBmp->common.uiType) {
		case  CONST_capType_av: {
			CAP_procInfo_video* pVc;
			pVc = (CAP_procInfo_video*)getCapBmpBySth(pProcInfo, i, 0);
			if (!pVc)  continue;

			if (pVc->bCapDevConnected) {
				if (pVc->uiCamCapType == CONST_camCapType_directX) {
					VIDEO_capDev_dx* p;

					p = (VIDEO_capDev_dx*)pVc->capDev.pVideoCapDev;
					//
					if (p && p->p_gcap) {
						AV_capStuff& gcap = *(AV_capStuff*)p->p_gcap;
						if (gcap.pmVideo) {
							//if (S_OK == pM->IsEqual(gcap.pmVideo)) 
							{
								//
								getMonikerFriendlyName(gcap.pmVideo, friendlyName, mycountof(friendlyName));
								//
								break;
							}
						}
					}
				}
			}
		}
							  break;
		default:
			break;
		}
	}

	if (!friendlyName[0])  goto  errLabel;

	safeTcsnCpy(friendlyName, name, cntofName);

	iErr = 0;
errLabel:
	return  iErr;
}


//
__declspec(dllexport )  int  sm_getChosenCamera(TCHAR  *  webcam_sel, int cntof_webcam_sel)
{
	int  iErr = -1;

	CCtxQyMc* pQyMc = g_pQyMc;
	
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);

	CAP_STUFF* pCapStuff = mynull;

	pCapStuff = (CAP_STUFF*)pFuncs->pf_CAP_STUFF_new();
	if (!pCapStuff)  goto  errLabel;
	pFuncs->moniker.pf_addDevicesToMenu(pCapStuff, TRUE, NULL);

	//
	TCHAR  tDev[256];  tDev[0] = 0;
	getCfgValByNameT(pQyMc->cfg.smCfgFile, CONST_cfgName_sm_devAsScreen, tDev, mycountof(tDev));
	tTrim(tDev);
	//
	TCHAR  tBuf[128];
	_sntprintf(tBuf, mycountof(tBuf), _T("sm_devAsScreen is [%s]"), tDev);
	showInfo_open0(0, 0, tBuf);


	TCHAR  tName[256];
	tName[0] = 0;
	bool  bFound = false;

	int  i;
	for (i = 0; i < mycountof(pCapStuff->rgpmVideoMenu); i++) {
		if (!pCapStuff->rgpmVideoMenu[i])  continue;
		tName[0] = 0;
		//  getMonikerFriendlyName(  pCapStuff->rgpmVideoMenu[i],  tName,  mycountof(  tName  )  );
		pFuncs->moniker.pf_getMonikerProp(pCapStuff->rgpmVideoMenu[i], CONST_moniker_FriendlyName, tName, mycountof(tName));
		//_sntprintf(tBuf, mycountof(tBuf), _T("%d: %s"), i + 1, tName);
		//((CComboBox*)GetDlgItem(idc))->InsertString(-1, tBuf);

		//
		//traceLog((TCHAR*)_T("[%s]"), tName);

		//
		if (tDev[0]) {
			if (!_tcsnicmp(tDev, tName, lstrlen(tDev)))  continue;
		}

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("sel: camera[%d] [%s]"), i, tName);
		showInfo_open0(0, 0, tBuf);

		//
		getMonikerDisplayName(pCapStuff->rgpmVideoMenu[i], tName, mycountof(tName));
		safeTcsnCpy(tName, webcam_sel, cntof_webcam_sel);

		bFound = true;		

		break;


	}
	
	if (!bFound)  goto  errLabel;

	iErr = 0;

	
errLabel:

	if (pCapStuff)  pFuncs->pf_CAP_STUFF_free(pCapStuff);


	return  iErr;
}


