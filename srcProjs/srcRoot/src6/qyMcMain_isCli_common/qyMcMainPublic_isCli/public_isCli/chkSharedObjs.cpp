

#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qyCusResTemp.h"

#ifndef  __NOTSUPPORT_MULTIDOC__
	//#include	"mainClient.h"
	//#include	"mainFrm.h"
#endif
#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	"qmcVideoCapture_isCli.h"

#include	"myresource.h"

#ifdef  __WINCE__
		#ifndef  __TEST__
				 #include	"ceMenuBar.h"
		#endif
		#include	"dlgTalk_ce.h"
#else
		#include	"dlgtalkproc.h"
#endif

#include	"QyPlaySound_wave.h"
#include	"qmcDxSurfacePublic.h"
#include	"qyWnd.h"

#include	"dlgMcClientLogon.h"
#ifdef  __WINCE__
		#include	"dlg_qyMc_winCe.h"
		#include	"dlgObjs.h"
#endif
#include	"DlgQnmCfgOptionsIsClient.h"
#include	"module_qisCamCap.h"

#ifndef  __NOTSUPPORT_MULTIDOC__
		 //#include	"dlgNotification.h"
#endif

//  
#include	"mmDeviceProc.h"
#include	"isCliHelpPublic.h"
#include	"wallTalkers.h"
#include	"isCliD3dPublic.h"
#include	"isCliCorePublic.h"
#include	"dyn_isCliD3d_public.h"
#include	"qmcCommFunc_isCli.h"

//
#include	"qisWebRtcPublic.h"
#include	"qmcFunc.h"


//
 int  chkSharedObjs(  MC_VAR_isCli  *  pProcInfo  )
 {
	 int  iErr  =  -1;

	 int  index_sharedObj  =  0;

	 //
	 for (int index = 0; index < pProcInfo->cfg.usMaxCnt_pSharedObjs; index++) {
		 QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, index);

		 if (!pSharedObj->bUsed)  continue;

		 //
		 index_sharedObj = index;

		 //
		 if (!bSharedObjActive(pProcInfo, index_sharedObj))  continue;// return  -1;

		 //
		 //QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, index_sharedObj);
		 //if (!pSharedObj)  goto  errLabel;

		 //
		 setFlg_forceKeyFrame(pProcInfo, index_sharedObj);
		 //
#ifdef  __DEBUG__
		 traceLog((TCHAR*)_T("chkSharedObjs: after setFlg_forceKeyFrame"));
#endif 

		 //
		 int  index_capBmp = pSharedObj->iIndex_capBmp;
		 CAP_procInfo_bmpU* pCapBmp = getCapBmpBySth(pProcInfo, index_capBmp, 0);
		 if (!pCapBmp)  goto  errLabel;
		 if (pCapBmp->common.uiType != CONST_capType_av)  goto  errLabel;
		 CAP_procInfo_video* pVc = (CAP_procInfo_video*)pCapBmp;

		 //  2017/09/14
		 unsigned  int  uiCamCapType = pVc->uiCamCapType;
		 //
		 switch (uiCamCapType) {
		 case  CONST_camCapType_directX:
			 break;
		 default:
			 goto  errLabel;
			 break;
		 }

		 //
		 if (!pVc->bCaptureStarted_openLocalVideo)  goto  errLabel;

		 //
#if 0
		 if (!bCameraRunning(pVc)) {
			 //
			 TCHAR  tBuf[128];
			 _sntprintf(tBuf, mycountof(tBuf), _T("%s chkSharedObjs: camera of index_sharedObj %d not running, try to resume it"), pProcInfo->who_showInfo, index_sharedObj);
			 showInfo_open0(0, 0, tBuf);
			 showNotification(0, 0, 0, 0, 0, 0, tBuf);
			 //
			 resumeLocalVideo(pProcInfo, index_sharedObj);
		 }
#endif

	 }

	 //
	 iErr  =  0;
errLabel:
	 return  iErr;
 }

