
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"


#include	"myresource.h"

#include	"qyMcMainWndProc.h"




#include	"funcsForIsCliHelp.h"
#include	"isCliHelpPublic.h"
#include	"dlgtalkproc.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcCmdProc.h"
#include	"qyAvRecordPublic.h"
#include	"tmpCeLib.h"

#include	"myDb.h"

#include	"qyDynLib.h"
#include	"qyCusResTemp.h"
#include	"qmcSharePublic.h"
#include	"funcsForIsCliHelp.h"
#include	"isCliD3dPublic.h"
#include	"imgProcessPublic.h"
#include	"genericHash.h"
#include	"imObjHash.h"

#include	"qmcCommFunc_isCli.h"
#include	"qmcCopyData.h"
#include	"rtspUsrData.h"

#include	"qisPipe_open.h"


//
 __declspec(  dllexport  )  void  qyMcRefreshAll(  )
{
	QY_MC	*	pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	
	//  
#ifdef  __DEBUG__
	if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
		traceLog(_T("qyMcRefreshAll "));
	}
#endif
	if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsCli"), 0, _T(""), _T(""), _T("qyMcrefreshAll starts..."));
	}
	
	//  2012/07/18
	if  (  IsWindow(  pProcInfo->hWnd_imObjView  )  )  {
		PostMessage(  pProcInfo->hWnd_imObjView,  WM_COMMAND,  MAKEWPARAM(  ID_qyRefresh,  0  ),  0  );
	}

	//
	if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsCli"), 0, _T(""), _T(""), _T("qyMcrefreshAll ends."));
	}
	
	//
	return;
}



