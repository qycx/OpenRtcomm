

#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<stddef.h>
#include	<assert.h>
#include	<tchar.h>
#ifndef  __WINCE__
#include	<vfw.h>
#else
#ifdef  __TEST__
#include	<vfw.h>
#endif

#include	<mmreg.h>
#include	<MSAcm.h>
#endif
#include	<Wincrypt.h>

#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qmOpenCommon.h"
#include	"qyMsgFunc.h"

#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"				//  2009/05/13

#include	"qnmCommProc_mis.h"
#include	"qnmPcComm.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmSpCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qnmCustom.h"
#include	"qySyncCommProc.h"
#include	"qmCrypt.h"
#include	"qnmFwCommProc.h"
#include	"qyString.h"
#include	"../atInclude/ancCorePublic.h"
#include	"ancCommProc.h"
#include	"qyTimestamp.h"



//
//#define		timestamp_renew(  p_ctx_qm_thread,  pTs  )			(  pTs  )->dwModifiedTickCnt  =  myGetTickCount(  p_ctx_qm_thread  );

int timestamp_renew(CTX_qm_thread* p_ctx_qm_thread, QY_timestamp* pTs,LPCTSTR  hint)
{
	if (!hint)  hint = _T("");

	//
	(pTs)->dwModifiedTickCnt = myGetTickCount(p_ctx_qm_thread);

	//
	if (pTs->dbg_iType == CONST_tsType_peerImgs
		||  pTs->dbg_iType  ==  CONST_tsType_layout) 
	{
		TCHAR tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("timestamp_renew. %s"), hint);
		showInfo_open0(0, 0, tBuf);
	}

	//
	return  0;
}

//
int  timestamp_assign(QY_timestamp src, QY_timestamp* pDst)
{
	if (!pDst)  return  -1;

	*pDst = src;

	return  0;
}

//
//#define		timestamp_reset(  pTs  )							{  memset(  pTs,  0,  sizeof(  QY_timestamp  )  );  }
int		timestamp_reset(  QY_timestamp*pTs, LPCTSTR  hint  )
{  
	if (!pTs)  return  -1;

	if (!hint)  hint = _T("");

	//memset(  pTs,  0,  sizeof(  QY_timestamp  )  );  
	pTs->dwModifiedTickCnt = 0;
	
	//
	if (pTs->dbg_iType == CONST_tsType_peerImgs) {
		TCHAR tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("timestamp_reset. %s"), hint);
		showInfo_open0(0, 0, tBuf);
	}
	
	//
	return  0;
}
