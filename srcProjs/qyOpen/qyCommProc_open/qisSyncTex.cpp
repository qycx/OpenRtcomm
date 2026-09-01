
#include	"stdafx.h"
#include	<tchar.h>
#include	<stdio.h>
#include	"qisSyncTex.h"
#include <qysynccommproc.h>
#include <showInfo_open.h>
#include <tmpDefs_open.h>

//
bool  bDbg_syncTex = false;



//
int qisSharedTexInfos_init(int uiMaxCnt, QisSharedTexInfos** pp)
{
	if (!pp || *pp)  return  -1;

	int  iErr = -1;
	int  size = sizeof(QisSharedTexInfos);
	QisSharedTexInfos* p = nullptr;

	do {
		//
		if (!uiMaxCnt  ||  uiMaxCnt > MAX_sharedTexInfos) {
			break;
		}

		//
		p = (QisSharedTexInfos*)mymalloc(size);
		if (!p)  break;

		memset(p, 0, size);

		p->uiMaxCnt = uiMaxCnt;

		//
		*pp = p;

		//
		iErr = 0;
	} while (false);

	if (iErr) {
		if (p)  myfree(p);
	}

	return  iErr;
}

//
int qisSharedTexInfos_exit(QisSharedTexInfos** pp)
{
	if (!pp || !*pp)  return  0;

	myfree(*pp);
	*pp = nullptr;
	return  0;

}


//
int printQisSharedTexInfos(QisSharedTexInfos* pQisSharedTexInfos, LPCTSTR  hint)
{
	int i;
	TCHAR  tBuf[128];

	if (!hint) hint = _T("");

#ifdef  _DEBUG


	_sntprintf(tBuf, mycountof(tBuf), _T("%s, printQisSharedTexInfos: cnt %d"), hint,  pQisSharedTexInfos->uiCnt);
	OutputDebugString(tBuf);
	OutputDebugString(_T("\n"));


	for (i = 0; i < pQisSharedTexInfos->uiMaxCnt; i++)
	{
		QisSharedTexInfo* pMem = &pQisSharedTexInfos->mems[i];

		if (!pMem->dwProcessId
			&& !pMem->index_mosaic
			&& !pMem->tn_sharedTex)
		{
			continue;
		}

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("processId %d, index_mosaic %d, tn %d"), pMem->dwProcessId, pMem->index_mosaic, pMem->tn_sharedTex);
		OutputDebugString(tBuf);
		OutputDebugString(_T("\n"));

		continue;
	}

#endif

	//
	return  0;
}


//
int addToQisSharedTexInfos(int dwProcessId, int index_mosaic, int tn_sharedTex, int real_index, void* m_shared_pTex12, QisSharedTexInfos* pQisSharedTexInfos)
{
	int iErr = -1;

	//
	if (!dwProcessId) {
		showInfo_open0(0, 0, _T("addToQisSharedTexInfos failed, dwProcessId 0"));
		return  -1;
	}

	//
	TCHAR  tBuf[128];
	_sntprintf(tBuf, mycountof(tBuf), _T("addToQisSharedTexInfos: dwProcessId %d"), dwProcessId);
	showInfo_open0(0, 0, tBuf);

	//
	do {
		//
		int i;

		//		
		//
		CQySyncObj syncObj;
		if (syncObj.sync(CONST_mtxName_syncSharedTexs)) {
			showInfo_open0(0, 0, _T("addToQisSharedTexInfos failed, sync failed"));
			break;
		}

		//  0 做无效值，所以不用
		//
		QisSharedTexInfo* pMem = nullptr;
		for (i = 1; i < pQisSharedTexInfos->uiMaxCnt; i++) {
			pMem = &pQisSharedTexInfos->mems[i];
			if (pMem->dwProcessId == dwProcessId
				&& pMem->index_mosaic == index_mosaic
				&& pMem->tn_sharedTex == tn_sharedTex
				//&& pMem->real_index
				)
			{
				break;
			}
		}
		if (i < pQisSharedTexInfos->uiMaxCnt) {
			if  (  m_shared_pTex12  !=  pMem->m_shared_pTex12) {
				//
				showInfo_open0(0, 0, _T("addToQisSharedTexInfos failed, m_shared_pTex12 !=pMem->m_shared_pTex12"));
				//
				break;
			}
			iErr = 0;  break;
		}
		//
		for (i = 1; i < pQisSharedTexInfos->uiMaxCnt; i++) {
			pMem = &pQisSharedTexInfos->mems[i];
			if (!pMem->dwProcessId
				&& !pMem->index_mosaic
				&& !pMem->tn_sharedTex
				)
			{
				break;
			}
		}
		if (i == pQisSharedTexInfos->uiMaxCnt) {
			showInfo_open0(0, 0, _T("addToQisSharedTexInfos failed, full"));
			break;
		}

		if (pQisSharedTexInfos->uiCnt >= pQisSharedTexInfos->uiMaxCnt) {
			showInfo_open0(0, 0, _T("addToQisSharedTexInfos failed, uiCnt >= uiMaxCnt"));
			break;
		}

		//
		if (!pMem)break;
		pMem->dwProcessId = dwProcessId;
		pMem->index_mosaic = index_mosaic;
		pMem->tn_sharedTex = tn_sharedTex;
		//
		pMem->m_shared_pTex12 = m_shared_pTex12;
		
		//
		pQisSharedTexInfos->uiCnt++;
		
		//
		iErr = 0;
	} while (false);

	//
#ifdef  _DEBUG
	printQisSharedTexInfos(pQisSharedTexInfos,_T("addToQisSharedTexInfos"));
#endif


	//
	return  iErr;
}

int removeFromQisSharedTexInfos(int dwProcessId, int index_mosaic, int tn_sharedTex, int real_index, QisSharedTexInfos* pQisSharedTexInfos)
{
	int  iErr = -1;

	//
	if (!dwProcessId) {
		showInfo_open0(0, 0, _T("removeFreomQisSharedTexInfos failed, dwProcessId is 0"));
		return  -1;
	}
	if (!pQisSharedTexInfos->uiCnt) {

		showInfo_open0(0, 0, _T("removeFreomQisSharedTexInfos failed, uiCnt is 0"));

		return  -1;
	}

	//
	do {
		int  i;
		int n;
		QisSharedTexInfo* pMem = nullptr;

		//
		bool  bContinue = false;

		//
		{
			//
			CQySyncObj syncObj;
			if (syncObj.sync(CONST_mtxName_syncSharedTexs)) {
				showInfo_open0(0, 0, _T("removeFromQisSharedTexInfos failed, sync failed"));
				break;
			}


			//
			for (i = 0, n = 0; n < pQisSharedTexInfos->uiCnt && i < pQisSharedTexInfos->uiMaxCnt; i++) {
				pMem = &pQisSharedTexInfos->mems[i];
				if (!pMem->dwProcessId
					&& !pMem->index_mosaic
					&& !pMem->tn_sharedTex)
				{
					continue;
				}
				if (pMem->dwProcessId == dwProcessId
					&& pMem->index_mosaic == index_mosaic
					&& pMem->tn_sharedTex == tn_sharedTex
					)
				{
					break;
				}
				n++;
				continue;
			}
			if (n == pQisSharedTexInfos->uiCnt) {
				break;
			}
			if (!pMem)break;

			//
			if (pMem->bLocked) {
				bContinue = true;
			}
			else {

				//
				memset(pMem, 0, sizeof(pMem[0]));
				pQisSharedTexInfos->uiCnt--;
			}
		}

		if (bContinue) {
			Sleep(50);
			continue;
		}


		//
		iErr = 0;
	} while (false);


	//
#ifdef  _DEBUG
	printQisSharedTexInfos(pQisSharedTexInfos,_T("removeFromQisSharedTexInfos"));
#endif

	return  iErr;

}


//
QisSyncTex::QisSyncTex()
{
	memset(&m_var, 0, sizeof(m_var));
}

//
QisSyncTex::~QisSyncTex()
{
	if (m_var.m_bSynced) {
		QisSharedTexInfo* pMem = &m_var.m_pQisSharedTexInfos->mems[m_var.m_index_mem];
		//
		pMem->bLocked = false;

		//
		showLock();
		
		//
	}

	return;
}

//
int QisSyncTex::getPtr(QisSharedTexInfos * pQisSharedTexInfos,  int processId, int index_mosaic, int tn, LPCTSTR  lockHint,  void** pptr)
{
	int  iErr = -1;

	if (!processId)  return  -1;
	if (!pptr || *pptr)  return  -1;

	do {
		CQySyncObj  syncObj;
		if (syncObj.sync(CONST_mtxName_syncSharedTexs))  break;
		//
		int i;
		int n;
		QisSharedTexInfo* pMem = nullptr;

		for (i = 0, n = 0; i < pQisSharedTexInfos->uiMaxCnt && n < pQisSharedTexInfos->uiCnt; i++) {
			pMem = &pQisSharedTexInfos->mems[i];
			if (isEmpty_qisSharedTexInfo(pMem))continue;
			if (processId == pMem->dwProcessId
				&& index_mosaic == pMem->index_mosaic
				&& tn == pMem->tn_sharedTex)
			{
				break;
			}
			n++;
			continue;
		}

		if (n >= pQisSharedTexInfos->uiCnt) {
			showInfo_open0(0, 0, _T("syncTex.getPtr failed, not found"));
			break;
		}

		//
		if (!pMem)break;
	
		if (pMem->bLocked) {
			//
			TCHAR  tBuf[256];
			_sntprintf(  tBuf,  mycountof(tBuf),  _T("syncTex.getPtr failed, bLocked already true. locked by [%d][%s]"),  i,  pMem->lockHint);
			showInfo_open0(0, 0, tBuf);
			//
			break;
		}

		//
		*pptr = pMem->m_shared_pTex12;
		pMem->bLocked = true;

		//
		if (lockHint) {
			lstrcpyn(pMem->lockHint, lockHint, mycountof(pMem->lockHint));
		}

		//
		m_var.m_index_mem = i;
		m_var.m_pQisSharedTexInfos = pQisSharedTexInfos;

		//
		m_var.m_bSynced = true;

		//
		showLock();


		//
		iErr = 0;
	} while (false);


	return  iErr;
}


int  QisSyncTex::showLock()
{
	if (!bDbg_syncTex)  return  0;

	//
	TCHAR  tBuf[128];
	if (m_var.m_index_mem < 0 || m_var.m_index_mem >= MAX_sharedTexInfos)  return  -1;
	QisSharedTexInfo* pMem = &m_var.m_pQisSharedTexInfos->mems[m_var.m_index_mem];

	_sntprintf(tBuf, mycountof(tBuf), _T("processId %d,index_mosaic %d,tn %d %s"), pMem->dwProcessId, pMem->index_mosaic, pMem->tn_sharedTex, pMem->bLocked ? _T("locked") : _T("unlocked"));
	showInfo_open0(0, 0, tBuf);

	return  0;
}


//
