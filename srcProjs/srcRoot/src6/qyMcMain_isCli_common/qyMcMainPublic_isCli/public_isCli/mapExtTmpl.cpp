
#include	"stdafx.h"
#include	"mapExtTmpl.h"
//
#include	"qyMcMainCommon.h"
#include <qyMcMainWndProc.h>
#include	"ctxQmc.h"
#include	"qmcProc.h"
#include <mapFunc.h>

//
MapExtTmpl::MapExtTmpl()
{
	memset(&m_var, 0, sizeof(m_var));


	//
	return;
}


MapExtTmpl::~MapExtTmpl()
{
	//
	return;
}


//
int  MapExtTmpl::gui_onTimer(void* p0, void* pVar, void* p2)
{
	if (!pVar)  return  -1;
	QY_MC_mainWndVar& var = *(QY_MC_mainWndVar*)pVar;
	CCtxQmc* pProcInfo = m_var.pProcInfo;
	if (!pProcInfo)  return  -1;
	CCtxQyMc* pQyMc = pProcInfo->pQyMc;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByIndex(0);
	if (!pMisCnt)  return  -1;

	//
	if (!pQyMc->bLogon)  return  -1;
	//
	if (pProcInfo->getMcuType()==CONST_mcuType_locServ ) {  //  定位服务器不能使用以下功能
		return  -1;
	}

	//
	if (1) {
		//traceLog((TCHAR*)_T("map.timer: mainWnd.loopCtrl %d"), var.loopCtrl);
	}

	//
	if (bExists_locDataReq()) {
		//
		if (!m_var.locServIdInfo.ui64Id || !m_var.mapServCfgStr[0]) {
			if (var.loopCtrl % 5) {
				//
				ancSndProcLocReq(pMisCnt, mynull);
			}
		}
	}

	//
	return  0;
}




