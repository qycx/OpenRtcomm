

#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyWnd.h"
#include	"qmcCmdProc.h"
#include	"qmcVWall.h"
#include	"dlgTalkPublic.h"
#include	"qmcVideoCapture_isCli.h"
#include	"myDb.h"


//
BOOL  tmpHandler_bDel_imGrpMem_byGrpIdInfo_isCli(void* p0, void* p1, void* p2)
{
	BOOL  bRet = FALSE;
	QY_MESSENGER_ID* pIdInfo_grp = (QY_MESSENGER_ID*)p1;
	IM_GRP_MEM* pQMem = (IM_GRP_MEM*)p2;

	//
	if (pQMem->idInfo_grp.ui64Id == pIdInfo_grp->ui64Id) {
		bRet = TRUE;
	}

errLabel:

	return  bRet;
}

//
BOOL  tmpHandler_bDel_imGrpInfo_byGrpIdInfo_isCli(void* p0, void* p1, void* p2)
{
	BOOL  bRet = FALSE;
	QY_MESSENGER_ID* pIdInfo_grp = (QY_MESSENGER_ID*)p1;
	IM_GRP_INFO* pQMem = (IM_GRP_INFO*)p2;

	//
	if (pQMem->idInfo.ui64Id == pIdInfo_grp->ui64Id) {
		bRet = TRUE;
	}

errLabel:

	return  bRet;
}

//
BOOL  tmpHandler_bDel_imObj_byIdInfo_isCli(void* p0, void* p1, void* p2)
{
	BOOL  bRet = FALSE;
	QY_MESSENGER_ID* pIdInfo = (QY_MESSENGER_ID*)p1;
	QMEM_qyImObj* pQMem = (QMEM_qyImObj*)p2;


	//
	if (pQMem->messengerInfo.idInfo.ui64Id == pIdInfo->ui64Id) {
		bRet = TRUE;
	}

errLabel:

	return  bRet;
}



//
//
int  del_imGrp_isCli(QY_MC  *  pQyMc,  QY_MESSENGER_ID* pIdInfo_grp)
{
	int  iErr = -1;
	//QY_MC* pQyMc = QY_GET_GBUF();
	QY_OBJ_DB* pObjDb = NULL;


	pObjDb = getProcedObjDb(pQyMc, 0, pQyMc->iDsnIndex_mainSys);	//  2007/01/02
	if (!bObjDbAvail(pObjDb))  goto  errLabel;

	CMyDb* pDb = (CMyDb*)pObjDb->pDb;

	//
	qRemoveMsg(pDb->m_var.pQ_qyImGrpMemTab, tmpHandler_bDel_imGrpMem_byGrpIdInfo_isCli, 0, pIdInfo_grp);
	//
	qRemoveMsg(pDb->m_var.pQ_qyImGrpInfoTab, tmpHandler_bDel_imGrpInfo_byGrpIdInfo_isCli, 0, pIdInfo_grp);
	//
	qRemoveMsg(pDb->m_var.pQ_qyImObjTab, tmpHandler_bDel_imObj_byIdInfo_isCli, 0, pIdInfo_grp);



	iErr = 0;

errLabel:
	return  iErr;
}



