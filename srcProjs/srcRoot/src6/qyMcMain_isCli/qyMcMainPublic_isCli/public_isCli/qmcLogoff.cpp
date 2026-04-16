

#include	"stdafx.h"

//#include	<qstring.h>


#include	"qyMcMainCommon.h"

//#include "CQmcLogin.h"

#include	"qyCusResTemp.h"

#include "ctxQmc.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliHelpPublic.h"
#include <qmcVideoCapture_isCli.h>
//#include	"ctxQmc_qt.h"






void qmcLogoff()
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	//
	showInfo_open0(0, mynull, _T("qyMcLogoff enters"));

	//
	pQyMc->bLogon = false;

	//
	CCtxQyMc* pQM = pQyMc;
	if (pQM->gui.hMutex_singleInstance) {
		CloseHandle(pQM->gui.hMutex_singleInstance);
		pQM->gui.hMutex_singleInstance = NULL;
	}

	//
	exitAllDaemonThreads(pQyMc);

	//
	pProcInfo->processQ_media.emptyQ();

	//
	//
	chkPlayers(pProcInfo);

	//
	freeAllSharedObjs(pProcInfo);


	//
	exitQyMcDb(mynull, mynull, &getProcedObjDbs(pQyMc)[pQyMc->iDsnIndex_mainSys]);

	//
	unloadCusModules(pQyMc);

	//
	showInfo_open0(0, mynull, _T("qyMcLogoff leaves"));


	return;
}


