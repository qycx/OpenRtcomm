
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"ctxQmc.h"
#include	"mapFunc.h"
#include	"mapExtTmpl.h"



//
__declspec(dllexport)  int  ancSndProcLocReq(MIS_CNT* pMisCnt,unsigned  int* puiTranNo)
{
	int				iErr = -1;
	if (!pMisCnt)  return  -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;

	ProcLocReq_u	req;
	MACRO_prepareForTran();
	int					len;



	//
	memset(&req, 0, sizeof(req));
	req.common.uiType = CONST_imCommType_procLocReq;
	req.common.usSubtype = CONST_procLocReqSubtype_getCfgs;
	//
	len = sizeof(ProcLocReq_u);  //offsetof(  PROC_offline_res,  mems  )  +  req.usCnt  *  sizeof(  req.mems[0]  );
	//
	postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_sendVDevReq, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, 0);

	//
	iErr = 0;
errLabel:


	if (!iErr) {
		if (puiTranNo)  *puiTranNo = uiTranNo;
	}


	return  iErr;
}


//
__declspec(dllexport) int ancSndLocation(void* p0, char* locStr, __int64 imGrp_related_ui64Id)
{
	 //
	int  iErr = -1;
	 CCtxQyMc* pQyMc = g_pQyMc;
	 CCtxQmc* pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();
	 MapExtTmpl* pMapExt = pProcInfo->m_pMapExt;
	 if (!pMapExt)  return  -1;
	 MIS_CNT* pMisCnt = pProcInfo->getMisCntByIndex(0);
	 if (!pMisCnt)  return  -1;


	 //
	 do {

		 //  
		 unsigned  char		ucFlg;
		 LocDataReq			content;
		 int					lenInBytes;
		 //
		 ucFlg = 0;
		 //
		 memset(&content, 0, sizeof(content));
		 content.uiType = CONST_imCommType_locDataReq;
		 content.idInfo_imGrp_related.ui64Id = imGrp_related_ui64Id;
		 safeStrnCpy(locStr, content.locData.locStr, mycountof(content.locData.locStr));
		 lenInBytes = sizeof(content);


		 //
		 MSG_ROUTE	route;
		 memset(&route, 0, sizeof(route));
		 //
		 route.idInfo_from.ui64Id = pMisCnt->idInfo.ui64Id;
		 //
		 route.idInfo_to.ui64Id = pMapExt->m_var.locServIdInfo.ui64Id;

		 //
		 QY_MESSENGER_ID  idInfo_peer;  idInfo_peer.ui64Id = pMapExt->m_var.locServIdInfo.ui64Id;
		 QY_MESSENGER_ID  idInfo_dst;  idInfo_dst.ui64Id = pMapExt->m_var.locServIdInfo.ui64Id;

		 //
		 int  channelType = 0;
		 channelType = CONST_channelType_robot;

		 {
			 MACRO_prepareForTran();

			 if (postMsg2Mgr_mc(pMisCnt, &route, CONST_misMsgType_outputTask, ucFlg, CONST_qyCmd_sendVDevReq, tStartTran, uiTranNo, 0, (char*)&content, lenInBytes, &idInfo_peer, &idInfo_dst, channelType, mynull, TRUE)) {
				 break;
			 }
		 }

		 iErr = 0;
	 } while (false);


	 //	
	 return  iErr;

}



//
__declspec(dllexport) int ancSndTransferLocData(void* p0, void* pTransferLocData, __int64 imGrp_related_ui64Id, __int64  ui64Id_dst)
{
	//
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MapExtTmpl* pMapExt = pProcInfo->m_pMapExt;
	if (!pMapExt)  return  -1;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByIndex(0);
	if (!pMisCnt)  return  -1;

	//
	if (!pTransferLocData)  return  -1;
	TransferLocData& content = *(TransferLocData*)pTransferLocData;


	//
	if (content.usCnt == 0)  return  -1;

	//
	do {

		//  
		unsigned  char		ucFlg;
		int					lenInBytes;
		//
		ucFlg = 0;
		//
		content.uiType = CONST_imCommType_transferLocData;
		content.idInfo_imGrp_related.ui64Id = imGrp_related_ui64Id;
		//
		lenInBytes = sizeof(content);


		//
		MSG_ROUTE	route;
		memset(&route, 0, sizeof(route));
		//
		route.idInfo_from.ui64Id = pMisCnt->idInfo.ui64Id;
		//
		route.idInfo_to.ui64Id = ui64Id_dst;

		//
		QY_MESSENGER_ID  idInfo_peer;  idInfo_peer.ui64Id = 0;// pMapExt->m_var.locServIdInfo.ui64Id;
		QY_MESSENGER_ID  idInfo_dst;  idInfo_dst.ui64Id = ui64Id_dst;

		//
		int  channelType = 0;
		channelType = CONST_channelType_robot;

		{
			MACRO_prepareForTran();

			if (postMsg2Mgr_mc(pMisCnt, &route, CONST_misMsgType_outputTask, ucFlg, CONST_qyCmd_sendVDevReq, tStartTran, uiTranNo, 0, (char*)&content, lenInBytes, &idInfo_peer, &idInfo_dst, channelType, mynull, TRUE)) {
				break;
			}
		}

		iErr = 0;
	} while (false);


	//	
	return  iErr;

}


//
DWORD  g_dwLastTickCnt_requestAFile = 0;

//
__declspec(dllexport)  int ancRequestAFile(int loopCtrl,int iSvcId)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	bool  bSkip = false;


	//
	g_dwLastTickCnt_requestAFile = myGetTickCount(mynull);
	


	//
	MACRO_prepareForTran();
	AnHgData  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_anHgData;
	//
	req.iSvcId = iSvcId;

	//
	req.sHgCmd = CONST_hgCmd_requestAFile;

	//  
	//_snprintf(req.hg_cliData, mycountof(req.hg_cliData), "[cmd=%d]", CONST_hgCmd_requestAFile);

	//
	req.hg_cliDataLen = strlen(req.hg_cliData);


	//
	int  channelType_o = CONST_channelType_robot;

	//
	int len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_hg, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, channelType_o, NULL, FALSE);

	//
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("ancRequestAFile called. loopCtrl %d. tn %d"), loopCtrl,  uiTranNo);
#endif


	//
	return  0;

}


//
__declspec(dllexport)  int ancSndMark(char  *  markStr)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	bool  bSkip = false;

	if (!markStr || !markStr[0])  return  -1;
	

	//
	MACRO_prepareForTran();
	AnHgData  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_anHgData;

	//
	req.sHgCmd = CONST_hgCmd_ulAnHgData;

	//  
	int len = strlen(markStr);
	_snprintf(req.hg_cliData, mycountof(req.hg_cliData), "[obj=%d len=%d]%s", CONST_hgType_markStr, len, markStr);

	//
	req.hg_cliDataLen = strlen(req.hg_cliData);


	//
	int  channelType_o = CONST_channelType_robot;

	//
	len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_hg, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, channelType_o, NULL, FALSE);

	//
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("ancSndMark called. tn %d"), uiTranNo);
#endif


	//
	return  0;

}





