

#include	"stdafx.h"
//
#include	<WinSock2.h>
#include	"Windows.h"
//
#include	"qmOpenCommon.h"
#include	"isFwPublic.h"
#include	"showInfo_open.h"
#include	"CtxFw_and.h"
#include <qmCommon.h>
#include	"isFwPublic.h"

//
//
extern  "C"  SMCA_API  CtxFw_and* andFw_newCtx()
{
	return  new CtxFw_and();
}

extern  "C"  SMCA_API  void  andFw_freeCtx(CtxFw_and** pp)
{
	if (!pp)  return;
	if (!(*pp))  return;
	delete* pp;
	*pp = 0;
	return;
}

//
extern  "C"  SMCA_API  int  andFw_init(CtxFw_and* pCtx)
{
	IsFw* pFw = &pCtx->fw_and;

	//
	safeStrnCpy((char*)CONST_mtxName_andFw, pFw->m_var.mtxName, mycountof(pFw->m_var.mtxName));

	//
	return  0;

}

extern  "C"  SMCA_API  int  andFw_exit(CtxFw_and* pCtx)
{
	IsFw* pFw = &pCtx->fw_and;

	return  0;
}


extern  "C"  SMCA_API  int  andFw_refeshCfg(CtxFw_and* pCtx)
{
	int  iErr = -1;
	IsFw* pFw = &pCtx->fw_and;


	do {
		//
		CQySyncCnt	syncCnt;
		{
			CQySyncObj	syncObj;
			if (syncObj.sync((TCHAR*)pFw->m_var.mtxName))  return  -1;

			//
			if (syncCnt.sync(&pFw->m_var.lSyncCnt))  return  -1;

		}

		//
		if (!pFw->m_var.cfg.cnt) {
			//
			if (0) {
				pFw->m_var.cfg.cnt = 1;
				//
				int size = sizeof(AndIsFwCfgItem) * pFw->m_var.cfg.cnt;
				pFw->m_var.cfg.pMems = (AndIsFwCfgItem*)mymalloc(size);
				if (!pFw->m_var.cfg.pMems)  break;
				memset(pFw->m_var.cfg.pMems, 0, size);
				//
				AndIsFwCfgItem* pMem;
				pMem = &pFw->m_var.cfg.pMems[0];
				safeStrnCpy((char*)"168.63.129.16", pMem->ip, mycountof(pMem->ip));
			}
		}

		//
		iErr = 0;
	} while (false);

	return  iErr;
}




//
	//
extern  "C"  SMCA_API  int andFw_filterIp(CtxFw_and * pCtx, Param_isFwFilterIp* pParam, void* p0, void* p1, IsCliInfo* pCliInfo)
{
	int  iErr = -1;
	TCHAR  tBuf[128];  tBuf[0] = 0;


	if (!pParam)  return  -1;
	if (!pCliInfo)  return  -1;

	//
	if (!pParam->pMtSockDbgStatusInfo)  return  -1;

	//
	do {
		IsFw* pFw = &pCtx->fw_and;

		CQySyncCnt	syncCnt;
		{
			CQySyncObj	syncObj;
			if (syncObj.sync((TCHAR*)pFw->m_var.mtxName))  return  -1;

			//
			if (syncCnt.sync(&pFw->m_var.lSyncCnt))  return  -1;

		}

		//
		int  i;
		for (i = 0; i < pFw->m_var.cfg.cnt; i++) {
			AndIsFwCfgItem* pMem = &pFw->m_var.cfg.pMems[i];
			//
			if (_stricmp(pCliInfo->cliIp, pMem->ip) == 0) {
				//
				if (pParam->pMtSockDbgStatusInfo->m_var.bDbgDetail_andFw) {
					_sntprintf(tBuf, mycountof(tBuf), _T("andFwFilterIp failed: %S is denyed"), pCliInfo->cliIp);
					showInfo_open(0, 0, 0, tBuf);
				}
				//
				break;
			}
		}

		//
		iErr = 0;
	} while (false);

	return  iErr;
}

