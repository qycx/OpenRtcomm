
#include	"stdafx.h"

#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>


#include	"qmCommon.h"
#include	"qmCaProc.h"
#include <myCmdParams_open.h>
#include <hgCommProc.h>
#include	"qmHgProc.h"


//
int  getHgLogStr(unsigned  __int64  ui64Id_src,  long logType, TCHAR* tLogDesc, char* timeBuf, bool bWarn, char* content, int  cntof_content)
{
	//CCtxQyMc* pQyMc = g_pQyMc;
	//CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	//MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	char  respBuf[1024]  =  "";

	//
	if (!tLogDesc) tLogDesc = (TCHAR*)_T("");
	if (!timeBuf)timeBuf = (char*)"";


	//	
	_snprintf(respBuf, mycountof(respBuf), "[msgr=%I64u]", ui64Id_src);
	//_snprintf(respBuf, mycountof(respBuf), "%s [rc=%d] [org=%d]", respBuf, respCode, (int)org_cmd);
	_snprintf(respBuf, mycountof(respBuf), "%s [cmd=%d]", respBuf, CONST_hgCmd_log);
	//
	char logTypeBuf[32];
	_ltoa(logType, logTypeBuf, 10);
	char  logDescBuf[256];
	myTChar2Utf8(tLogDesc, logDescBuf, mycountof(logDescBuf));
	char warnBuf[32];
	_ltoa(bWarn, warnBuf, 10);
	//
	_snprintf(respBuf, mycountof(respBuf), "%s [obj=%d len=%d]%s [obj=%d len=%d]%s [obj=%d len=%d]%s [obj=%d len=%d]%s", respBuf,
		CONST_hgType_logType, strlen(logTypeBuf), logTypeBuf,
		CONST_hgType_logDesc, strlen(logDescBuf), logDescBuf,
		CONST_hgType_time, strlen(timeBuf), timeBuf,
		CONST_hgType_bWarn, strlen(warnBuf), warnBuf
	);

	safeStrnCpy(respBuf, content, cntof_content);

#ifdef  __DEBUG__
	traceLogA(content);
#endif

	return  0;
}



//
int getHgEndAvStr(unsigned  __int64  ui64Id_src , unsigned __int64 ui64Id_grp, char* content, int  cntof_content) {
	
		//CCtxQyMc* pQyMc = g_pQyMc;
		//CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
		//MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

		char  respBuf[1024] = "";

		//	
		_snprintf(respBuf, mycountof(respBuf), "[msgr=%I64u]", ui64Id_src);
		//_snprintf(respBuf, mycountof(respBuf), "%s [rc=%d] [org=%d]", respBuf, respCode, (int)org_cmd);
		_snprintf(respBuf, mycountof(respBuf), "%s [cmd=%d]", respBuf, CONST_hgCmd_p2pEndAv);
		
		char ui64IdStr[128];
		_snprintf(ui64IdStr, mycountof(ui64IdStr), "%I64u", ui64Id_grp);

		//
		_snprintf(respBuf, mycountof(respBuf), "%s [obj=%d len=%d]%s", respBuf,
			CONST_hgType_grpIdInfo, strlen(ui64IdStr), ui64IdStr);

		safeStrnCpy(respBuf, content, cntof_content);

#ifdef  __DEBUG__
		traceLogA(content);
#endif

		return  0;

}