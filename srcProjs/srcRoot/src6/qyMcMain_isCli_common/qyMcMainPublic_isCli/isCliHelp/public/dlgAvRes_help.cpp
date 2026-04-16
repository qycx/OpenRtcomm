
#include "stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"

#include	"myresource.h"
#include	"qmcVWall.h"
#include	"WallTalkers.h"
//#include	"DlgDynBmps.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"

#include	"qyCusResTemp.h"

#include	"qyAvRecordPublic.h"

#include	"sp.h"
#include	"qmcCommFunc_isCli.h"
#include	"qyMessengerHelpPublic.h"

#include	"myDb.h"
#include	"funcsForIsCliHelp.h"
#include	"qmcLayout.h"


__declspec(dllexport)  int  getRole_byIdInfo(QY_MESSENGER_ID* pIdInfo, int* piRole)
{
	int  iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	//
	QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return  -1;
	QM_dbFuncs& g_dbFuncs = *pDbFuncs;

	//
	void* pDb = NULL;
	QY_MESSENGER_INFO			messengerInfo;
	QY_MESSENGER_REGINFO		regInfo;
	IM_GRP_INFO					grpInfo;

	CQnmDb						db;
	if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
	pDb = db.m_pDbMem->pDb;
	//
	if (!g_dbFuncs.pf_bGetMessengerInfoBySth(pDbFuncs, pDb, pQyMc->cfg.db.iDbType, getResTable(0, &pQyMc->cusRes, CONST_resId_fieldIdTable), _T(""), pIdInfo, 0, &messengerInfo, &regInfo, NULL, NULL)) {
		memset(&messengerInfo, 0, sizeof(messengerInfo));
	}

	//
	if (piRole) {
		*piRole = messengerInfo.iRole;
	}

	//
	iErr = 0;

errLabel:

	return  iErr;
}
