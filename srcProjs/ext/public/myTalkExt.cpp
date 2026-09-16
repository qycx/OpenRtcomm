
#include	"stdafx.h"
#include	"myTalkExt.h"
#include	"ctxQmc.h"
#include <isCliHelpPublic.h>
#include <dlgtalkproc.h>



//
int myTalkExt::switchTransmissionMode(__int64 talkerId, int  iTaskId, atbool  bNoVDownloadVal)
{
	CCtxQyMc * pQyMc = g_pQyMc;
	CCtxQmc *pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (pMisCnt == mynull)  return  -1;

	//
	if (!iTaskId)  return  -1;

	HWND  hTalk = mynull;

	QY_MESSENGER_ID  idInfo;
	idInfo.ui64Id = talkerId;
	if (findTalker(pQyMc, &idInfo, &hTalk))  return -1;


	//
	m_var.confCtrl.iTaskId = iTaskId;

	//
	if (dlgTalk_bConfCompere(hTalk, pMisCnt->idInfo)) {
		m_var.confCtrl.bNoVDownload = 0;
	}
	else {
		m_var.confCtrl.bNoVDownload = bNoVDownloadVal;

	}

	return  0;
}




//

bool  myTalkExt::bNoVDownload(int  iTaskId)
{
	CCtxQmc* pProcInfo = m_var.pProcInfo;
	if (!pProcInfo)  return false;


	//
#ifdef  __DEBUG__
	//
	if (0) {

		//
		if (1) {

			if (m_var.confCtrl.iTaskId != iTaskId)  return  false;
			//
			return m_var.confCtrl.bNoVDownload;
		}

		//
		showInfo_open(0, 0, 0, _T("Test: bNoAvDownload returns true"));
		return  true;
	}
	//
#endif 

	//
	//if (pProcInfo->m_iCtxSubtype == CONST_ctxSubtype_qmcSm) 
	{
		//if (pProcInfo->uiTerminalType == CONST_terminalType_mon) 
		{
			//
			if (m_var.confCtrl.iTaskId != iTaskId)  return  false;
			//
			return m_var.confCtrl.bNoVDownload;
		}
	}
	//
	return false;
}


//
//
int myTalkExt::doOp_switchTransmissionMode(__int64  idInfo_imGrp_related, bool b_noVDownload)
{
	return  0;
}


