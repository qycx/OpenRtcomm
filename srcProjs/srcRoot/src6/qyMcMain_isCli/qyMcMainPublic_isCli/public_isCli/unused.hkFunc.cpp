
#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#include	"qmcCmdProc.h"


#include	"vppProc.h"
#include	"qmcCfg.h"
#include	"tmpFfmpegPublic.h"
#include <hgCommProc.h>
#include	"imgFunc_open.h"



//
bool  bNeedMute()
{
	bool  bRet = false;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	CCtxQyMc* pQyMc = g_pQyMc;


	if (isMkfOff(pProcInfo->av.hk.iHkStatus)) {
		bRet = true;
	}

	//
	if (isMkfOff(pProcInfo->av.confLayout.taskInfo.iHkStatus_local)) {
		bRet = true;
	}

	//
	if (pProcInfo->av.hk.portStatus.bDisable_usb_mkf_usb2) {
		bRet = true;
	}

	//
	return  bRet;
}



//
bool  bNeedFakePic()
{
	bool  bRet = false;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	CCtxQyMc* pQyMc = g_pQyMc;


	if (isSxtOff(pProcInfo->av.hk.iHkStatus)) {
		bRet = true;
	}

	//
	if (isSxtOff(pProcInfo->av.confLayout.taskInfo.iHkStatus_local)) {
		bRet = true;
	}

	//如果是非法用户   也需要关闭摄像头
	if (pQyMc->appParams.bSmZy) {


		if (
			pProcInfo->legal_info.isOk &&
			!pProcInfo->legal_info.bLegal)
		{
			//
			bRet = true;

		}
	}

	

	//
#ifdef  __DEBUG__
	if (pQyMc->appParams.bUse_forTest_fakePic) {
		bRet = true;
	}
#endif



	//
	return  bRet;
}


//
 int get_iHkStatus()
{
	int  cur_iHkStatus = 0;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	cur_iHkStatus = pProcInfo->av.hk.iHkStatus | pProcInfo->av.confLayout.taskInfo.iHkStatus_local;

	return  cur_iHkStatus;
}

 //
 bool  bNvr()
 {
	 CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	 if (pProcInfo->m_ipcProc.dev.nvrInfo.usCnt)  return true;
	 else return false;
 }



