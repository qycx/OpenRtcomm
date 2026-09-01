
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"ctxQmc.h"


//
int  sendKeepaliveReq(CCtxQmc  *  pProcInfo, bool  bResp,  int channelType)
{
	int  len;
	MIS_CNT* pMisCnt;

	pMisCnt = pProcInfo->getMisCntByName(_T(""));


	MACRO_prepareForTran();
	AnKeepaliveReq						req;
	
	//	
#ifdef  __DEBUG__
		if  (  1  )  {
		}
#endif 
	
	
	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_anKeepaliveReq;
	req.ucbResp = bResp;



	//
	len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_outputReq, 0, CONST_qyCmd_sendReq, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, channelType, NULL, FALSE);
	//
	

	//
	if (pProcInfo->cfg.pDebugStatusInfo->bDbgDetail_keepAlive) {
		TCHAR  tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("sendKeepaliveReq called. channelType %d. tn %d"), channelType, uiTranNo);
		showInfo_open(0, 0, 0, tBuf);
	}


	//
	return  0;

}