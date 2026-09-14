
#include	"stdafx.h"
//
#include	<WinSock2.h>
#include	"Windows.h"
//
#include	"qmOpenCommon.h"
#include	"isFwPublic.h"
#include	"showInfo_open.h"
#include	"IsFw.h"
#include <qmCommon.h>
#include	"CtxFw_and.h"
#include <hgCommProc.h>
#include <and_filter_msg_public.h>



//
extern  "C"  SMCA_API  int  hgFw_refeshCfg(CtxFw_and* pCtx)
{
	int  iErr = -1;
	IsFw* pFw = &pCtx->fw_hg;


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
			if (10) {
				pFw->m_var.cfg.cnt = MAX_hgs;
				//
				int size = sizeof(AndIsFwCfgItem) * pFw->m_var.cfg.cnt;
				pFw->m_var.cfg.pMems = (AndIsFwCfgItem*)mymalloc(size);
				if (!pFw->m_var.cfg.pMems)  break;
				memset(pFw->m_var.cfg.pMems, 0, size);
				//
				AndIsFwCfgItem* pMem;
				int  index;
				char  buf[128];
				char  cfgName[128];
				//
				//
				for (index = 0; index < pFw->m_var.cfg.cnt; index++) {
					pMem = &pFw->m_var.cfg.pMems[index];
					_snprintf(cfgName, mycountof(cfgName), "hgIp%d", index);
					if (!getCfgValByName(pCtx->m_smCfgFileName, (char*)cfgName, buf, sizeof(buf))) {
						safeStrnCpy((char*)buf, pMem->ip, mycountof(pMem->ip));
						if (pMem->ip[0]) {
							pMem->ulIp = inet_addr(pMem->ip);
							pMem->bWhitelisted = true;
						}
						//
						_snprintf(cfgName, mycountof(cfgName), "hpLocalIp%d", index);
						if (!getCfgValByName(pCtx->m_smCfgFileName, (char*)cfgName, buf, sizeof(buf))) {
							safeStrnCpy(buf, pMem->localIp, mycountof(pMem->localIp));
							if (pMem->localIp[0]) {
								pMem->ulLocalIp = inet_addr(pMem->localIp);
							}
						}
						else {
							pMem->localIp[0] = 0;
							pMem->ulLocalIp = 0;
						}
					}
					else {
						memset(pMem, 0, sizeof(pMem[0]));
					}
					//
				}
			}
		}

		//
		iErr = 0;
	} while (false);

	return  iErr;
}


//


extern  "C"  SMCA_API  int hgFw_filterIp(CtxFw_and* pCtx, Param_isFwFilterIp* pParam, void* p0, void* p1, IsFwCliInfo* pCliInfo)
{
	int  iErr = -1;
	TCHAR  tBuf[128];  tBuf[0] = 0;


	if (!pParam)  return  -1;
	if (!pCliInfo)  return  -1;

	//
	if (!pParam->pMtSockDbgStatus) {
		showInfo_open(0, 0, 0, _T("hgFw_filterIp failed, pParam->pMtSockDbgStatusInfo is null"));
		return  -1;
	}

	//
	do {
		IsFw* pFw = &pCtx->fw_hg;


		//
		CQySyncCnt	syncCnt;
		{
			CQySyncObj	syncObj;
			if (syncObj.sync((TCHAR*)pFw->m_var.mtxName))  return  -1;

			//
			if (syncCnt.sync(&pFw->m_var.lSyncCnt))  return  -1;

		}

		//
		int  i;
		bool  tmp_bErr = false;

		//
		if (pParam->nWhere == CONST_nWhere_hg_afterAccepted) {
			for (i = 0; i < pFw->m_var.cfg.cnt; i++) {
				AndIsFwCfgItem* pMem = &pFw->m_var.cfg.pMems[i];
				if (!pMem->bWhitelisted)  continue;
				if (!pMem->ulIp)  continue;

				if (pMem->ulIp) {

					//
					if (pCliInfo->ulCliIp != pMem->ulIp) {
						//
						if (pParam->pMtSockDbgStatus->bDbgDetail_hgFw) {
							_sntprintf(tBuf, mycountof(tBuf), _T("hgFwFilterIp failed: afterAccepted, %S is denyed. "), pCliInfo->cliIp);
							showInfo_open(0, 0, 0, tBuf);
						}
						//
						tmp_bErr = true;
						//
						break;
					}

				}

			}
			//
			if (tmp_bErr) {
				break;
			}

			}
		else {




			//
			if (pCliInfo->iHgServIndex < 0 || pCliInfo->iHgServIndex >= pFw->m_var.cfg.cnt) {
				showInfo_open(0, 0, 0, _T("hgFw_filterIp failed: iHgServIndex err"));
				return  -1;
			}
			//		
			AndIsFwCfgItem* pMem = &pFw->m_var.cfg.pMems[pCliInfo->iHgServIndex];
			if (pMem->bWhitelisted) {

				//
				if (pMem->ulIp) {

					//
					if (pCliInfo->ulCliIp != pMem->ulIp) {
						//
						if (pParam->pMtSockDbgStatus->bDbgDetail_hgFw) {
							_sntprintf(tBuf, mycountof(tBuf), _T("hgFwFilterIp failed: %S is denyed"), pCliInfo->cliIp);
							showInfo_open(0, 0, 0, tBuf);
						}
						//
						break;
					}

					//
					if (pMem->ulLocalIp) {
						if (pCliInfo->ulCliLocalIp != pMem->ulLocalIp) {
							if (pParam->pMtSockDbgStatus->bDbgDetail_hgFw) {
								_sntprintf(tBuf, mycountof(tBuf), _T("hgFwFilterIp failed: %S(%S) is denyed"), pCliInfo->cliIp, pCliInfo->cliLocalIp);
								showInfo_open(0, 0, 0, tBuf);
							}
						}
					}
				}
			}

		}

		//
		iErr = 0;
	} while (false);

	return  iErr;
}
