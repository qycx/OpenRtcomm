// isCliHelp_noMfc.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include	"qyMcMainCommon.h"
#include <subtitles.h>


//
__declspec(dllexport)  int   set_g_pQyMc_isCliHelp(void* pQyMc)
{

#ifdef  __DEBUG__
	traceLog(_T("set_g_pQyMc called"));
#endif

	//  2013/07/31
//	set_g_pShowInfoStruct(  g_pQyMc->pShowInfoStruct  );

	return  0;
}



__declspec(dllexport)  int   set_g_dbPool_isCliHelp(void* pPool)
{
	if (CQnmDb::useDbPool((QNM_db_pool*)pPool))  return  -1;
	return  0;
}

__declspec(dllexport)  int  subtitlesCfg_modify(SUBTITLES_cfg* pCfg, DWORD  dwTickCnt, BOOL  bForce, SUBTITLES_cfg* pCur, BOOL* pbModified)
{
	return -1;
}

