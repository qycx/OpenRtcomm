
#include	"stdafx.h"
#include	"myMapExt.h"
#include <mapFunc.h>
#include	"qyMcMainCommon.h"
#include <qyMcMainWndProc.h>
#include <qmcStruct_defs.h>
#include	"ctxQmc.h"


//
int  myMapExt::gui_onTimer(void* p0, void* pVar, void* p2)
{
	QY_MC_mainWndVar& var = *(QY_MC_mainWndVar*)pVar;
	CCtxQmc* pProcInfo = m_var.pProcInfo;
	if (!pProcInfo)  return  -1;
	CCtxQyMc* pQyMc = (CCtxQyMc*)pProcInfo->pQyMc;
	MIS_CNT* pMisCnt = (MIS_CNT*)pProcInfo->getMisCntByIndex(0);
	if (!pMisCnt)  return  -1;
		
	//
	if (MapExtTmpl::gui_onTimer(p0, pVar, p2))  return  -1;

	//
#ifdef  __DEBUG__
	
	if (!pProcInfo->cfg.pDebugStatusInfo->bTest_noLocData) {
		if (var.loopCtrl % 5) {
			char  buf[128];
			snprintf(buf, mycountof(buf), "x=%d,y=%d,z=%d", var.loopCtrl, var.loopCtrl, var.loopCtrl);
			QY_MESSENGER_ID  grp_idInfo; grp_idInfo.ui64Id = 107;
			//
			this->sendLocation(p0, buf, grp_idInfo.ui64Id);
		}
	}

	//



#endif 


	//
	return  0;
}



// 定位信息，一个字符串，关联一个组号，发送到 locServer_idInfo
int myMapExt::sendLocation(void* p0, char* locStr, __int64 imGrp_related_ui64Id)
{
	//

	ancSndLocation(0, locStr, imGrp_related_ui64Id);


	//
	return  0;
}


int myMapExt::onRecv_locations(CParam_onRecv_locations* pParam)
{
	if (!pParam) return  -1;
	TransferLocData* pTld = (TransferLocData*)pParam->m_var.pTransferLocData;
	if (!pTld)  return  -1;

	//
	traceLog((TCHAR*)_T("myMapExt.OnRecv_locations: cnt %d"), pTld->usCnt);


	//
	return  0;
}
