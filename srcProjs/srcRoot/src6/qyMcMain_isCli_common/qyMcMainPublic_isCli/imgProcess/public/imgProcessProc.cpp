
#include "stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

//  #include	"myresource.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#ifndef  __WINCE__
#include	"qmcVWall.h"
#endif
#include	"qmcCmdProc.h"

#include	"qyAvRecordPublic.h"
#include	"imgProcessPublic.h"
#include	"imgProcessCommon.h"
#include	"isCliHelpPublic.h"


__declspec(dllexport)  int   set_g_pQyMc_imgProcess(void* pQyMc)
{

#ifdef  __DEBUG__
	traceLog(_T("set_g_pQyMc called"));
#endif

	//  2013/07/31
//	set_g_pShowInfoStruct(  g_pQyMc->pShowInfoStruct  );


	return  0;
}



__declspec(dllexport)  int  init_imgProcess(QY_MC  *  pQyMc)
{
	int			iErr = -1;

	//
	CCtxImgProcess* pCtx = &gCtx_imgProcess;

	//
	getImgProcessCfg(pQyMc,  &pCtx->m_var.new_Cfg);
	pCtx->m_var.dwTickCnt_modified_new = GetTickCount();

	iErr = 0;
errLabel:

	return  iErr;
}

__declspec(dllexport)  int  exit_imgProcess()
{
	int			iErr = -1;

	iErr = 0;
errLabel:
	return  iErr;
}



