
#include	"stdafx.h"
#include	"myTalkExt.h"
#include	"ctxQmc.h"


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


