



#include	"stdafx.h"
#include	<time.h>
#include	<windowsx.h>
#include	<math.h>
#include	"qymcMainCommon.h"


#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"

#include	"qyOpenShellCommon.h"


#include	"tmpCeLib.h"

#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"

#include	"myresource.h"

#include	<assert.h>
#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
#include	"qmcConferenceWall.h"
#endif
#include	"qmcCmdProc.h"
#include	"dlgTalkProc.h"
#include	"isCliHelpPublic.h"
#include	"isCliD3dPublic.h"

#include	"qmcCommFunc_isCli.h"
//
#include	"funcsForIsCliHelp.h"

#include "smLoginProc.h"


//
QY_DMITEM  CONST_skippedTable_a[]  = 
{
	//{	0,		(TCHAR*)_T("麦克风阵列"),		},
	//
	{	0,		(TCHAR*)_T("Digital Audio Interface"),	},
	{	0,		(TCHAR*)_T("KT_USB_AUDIO"),				},
	{	0,		(TCHAR*)_T("Line In"),					},
	{	0,		(TCHAR*)_T("xAudio"),					},
	{	0,		(TCHAR*)_T("Microphone"),					},
	//
	{	-1,		},
};

//
QY_DMITEM  CONST_skippedTable_v[] =
{
	{	0,		(TCHAR*)_T("HP WIDE VISION"),			},
	{	0,		(TCHAR*)_T("xVideo"),			},
	//
	{	-1,		},
};




//
 //
int  conf_chkAvDev(HWND  hMgr, void* pDLG_TALK_var)
{
	DLG_TALK_var* pTalkVar = (DLG_TALK_var*)pDLG_TALK_var;

	//
	if (!isTalkerShadowMgr(pTalkVar->addr))  return  -1;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);


	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return  -1;
	Ctx_sm& ctxSm = *pCtxSm;



	//
	DLG_TALK_var* pMgrVar = (DLG_TALK_var*)pTalkVar;

	//
	if (pMgrVar->av.taskInfo.bTaskExists) {		//  2024/11/02. 会议进行时，不能调用此函数，否则画面会突然卡一下
		return  -1;
	}

	//
#ifndef  __DEBUG__
	if (!pMgrVar->av.taskInfo.bTaskExists) {

		pProcInfo->xt.bAudioDevOk = true;
		pProcInfo->xt.bVideoDevOk = true;

		return  -1;
	}
#endif

	//
	static  DWORD  sLoopCnt = 0;	//  
	sLoopCnt++;
	//  每10秒一次
	if (0 != (sLoopCnt % 10))  return  -1;



	//
	void* pCapStuff = nullptr;


	do {
		pCapStuff = pFuncs->pf_CAP_STUFF_new();
		if (!pCapStuff)  break;

		addDevicesToMenu(pCapStuff, false, nullptr);

		//
		bool  bPrint_a = false;
		bool  bPrint_v = false;
		//
		if (0) {
			bPrint_a = true;
			bPrint_v = true;
		}

		//
		int  n_a = get_iNumADevices(pCapStuff, CONST_skippedTable_a,  bPrint_a);
		int  n_v = get_iNumVCapDevices(pCapStuff,CONST_skippedTable_v,  bPrint_v);

		//
#ifdef  __DEBUG__
		TCHAR  tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("conf_chkAvDev: n_a %d, n_v %d"), n_a, n_v);
		showInfo_open0(0, 0, tBuf);
#endif

		//




		if (ctxSm.hg.avDev.n_a != n_a) {


			if (n_a == 1) {

				//正常
				TCHAR  tBuf[256];
				_sntprintf(tBuf, mycountof(tBuf), _T("%s：全向麦设备运行正常"), pProcInfo->av.confLayout.login_termialName);
				qmcLogForHg(0, tBuf, false);
			}
			else {

				//异常日志
				TCHAR  tBuf[256];
				_sntprintf(tBuf, mycountof(tBuf), _T("%s：全向麦设备异常"), pProcInfo->av.confLayout.login_termialName);
				qmcLogForHg(0, tBuf, true);
			}
			ctxSm.hg.avDev.n_a = n_a;

		}

		if (ctxSm.hg.avDev.n_a == 1) {

			pProcInfo->xt.bAudioDevOk = true;

		}
		else {

			pProcInfo->xt.bAudioDevOk = false;

		}


		//
		if (ctxSm.hg.avDev.n_v != n_v) {


			if (n_v == 1) {

				//正常
				TCHAR  tBuf[256];
				_sntprintf(tBuf, mycountof(tBuf), _T("%s：摄像头设备运行正常"), pProcInfo->av.confLayout.login_termialName);
				qmcLogForHg(0, tBuf, false);
			}
			else {

				//异常日志
				TCHAR  tBuf[256];
				_sntprintf(tBuf, mycountof(tBuf), _T("%s：摄像头设备异常"), pProcInfo->av.confLayout.login_termialName);
				qmcLogForHg(0, tBuf, true);
			}
			ctxSm.hg.avDev.n_v = n_v;

		}

		if (ctxSm.hg.avDev.n_v == 1) {

			pProcInfo->xt.bVideoDevOk = true;

		}
		else {

			pProcInfo->xt.bVideoDevOk = false;

		}

		//


		int  ii = 0;
	} while (false);


	//
	if (pCapStuff)  pFuncs->pf_CAP_STUFF_free(pCapStuff);




	//
	return  0;
}



