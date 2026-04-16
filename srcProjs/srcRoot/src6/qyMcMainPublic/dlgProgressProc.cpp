
#include	"stdafx.h"
#include	"qyMcMainCommon.h"

#include	"qisGuiPublic_public.h"


//  2010/08/14
__declspec(dllexport)  int  startProgress(QY_PROGRESS* pProgress, unsigned  int  uiTranNo)
{
	//MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	//if  (  !pProcInfo  )  return  -1;

#ifdef  __DEBUG__
	traceLog(_T("startProgress called, tn %d"), uiTranNo);
#endif
	if (!pProgress)  return  -1;
	QY_PROGRESS& progress = *pProgress;
	memset(&progress.var, 0, sizeof(progress.var));
	progress.var.uiTranNo = uiTranNo;

	return  0;
}

__declspec(dllexport) int  notifyProgressEnd(QY_PROGRESS* pProgress, unsigned  int  uiTranNo, int  nResult)
{
	//MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	//if  (  !pProcInfo  )  return  -1;
	if (!pProgress)  return  -1;
	QY_PROGRESS& progress = *pProgress;

#ifdef  __DEBUG__  //  2014/09/05
	traceLog(_T("notifyProgressEnd called, tn %d, cur_progress.tn %d"), uiTranNo, progress.var.uiTranNo);
#endif

	//
	if (progress.var.uiTranNo == uiTranNo) {
		progress.var.nResult = nResult;
		progress.var.ucbProgessEnd = TRUE;
		if (IsWindow(progress.var.hWnd)) {
			PostMessage(progress.var.hWnd, CONST_qyWm_postComm, CONST_qyWmParam_notifyProgressEnd, uiTranNo);
		}
	}

	return  0;
}

