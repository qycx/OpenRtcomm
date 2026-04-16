

#include	"stdafx.h"
#include <qyMcMainCommon.h>
#include	"ctxQmc.h"
#include	"dbgFunc_open.h"


//
 //
int qmcLogStatus(LPCTSTR  tWhere, int  logType, LPCTSTR  logDesc)
{
	int  iErr = -1;

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();


	//
	return  logStatus(pQyMc->cfg.qmcLogFile, pProcInfo->who_showInfo,  tWhere, logType, logDesc);

}




//
int qmcChkStatusLogFile()
{
	CCtxQyMc* pQyMc = g_pQyMc;

	TCHAR			tBuf[256];


	int maxFileLen_caTool = 5 * 1000 * 1000;

	//
	return  chkStatusLogFile(maxFileLen_caTool, pQyMc->cfg.qmcLogFile);

}
