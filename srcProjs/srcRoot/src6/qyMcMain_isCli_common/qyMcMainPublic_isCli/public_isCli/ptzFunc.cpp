
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"ctxQmc.h"
#include	"funcsForIsCliHelp.h"
#include	"ptzFunc.h"
#include	"ptzCommProc.h"


//
//  2014/09/13
 //int  sendPtzReq(  void  *  pDlgPtzControlParam,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj, unsigned  short  usHelp_subIndex,  unsigned  char  ucCmd,  unsigned  char  ucParam,  unsigned  char  ucMouseStatus  )
__declspec(dllexport)  int  sendPtzReq(unsigned  int  uiObjType, unsigned  short  usIndex_obj, unsigned  short  usHelp_subIndex, QY_MESSENGER_ID  idInfo, int iChannel, unsigned  char  ucCmd, unsigned  char  ucParam, unsigned  char  ucMouseStatus, PTZ_cmdParamU* pParam, QY_MESSENGER_ID  idInfo_imGrp_related, QY_MESSENGER_ID idInfo_to)
{
	int		iErr = -1;

	//if  (  !pDlgPtzControlParam  )  return  -1;
	//CDlgPtzControl  *  pDlgPtzControl  =  (  CDlgPtzControl  *  )pDlgPtzControlParam;

	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;

	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);

	//
	PTZ_cmdParamU  tmpParam = { 0 };
	if (!pParam)  pParam = &tmpParam;


	//
#if  10  //  2014/09/13.
	{
		//  2012/08/06
		PTZ_control_cmd	req;
		MACRO_prepareForTran();

		MIS_CNT* pMisCnt = pFuncs->pf_getMisCntByName(pProcInfo, _T(""));
		if (!pMisCnt)  goto  errLabel;

		unsigned  int			uiChannelType = CONST_channelType_media;

#ifdef  __DEBUG__
		uiChannelType = 0;
		traceLog((TCHAR*)_T("Note: send ptz req through talking channel, just for debug"));
#endif

		//
		memset(&req, 0, sizeof(req));
		req.uiType = CONST_imCommType_ptzControlCmd;

#if  0
		if (iLen > sizeof(req.v0260.cmdBuf))  goto  errLabel;
		memcpy(req.v0260.cmdBuf, buf, iLen);
		req.v0260.uiLen = iLen;
#endif
		//
		req.idInfo_imGrp_related = idInfo_imGrp_related;

		//
		req.cmdInfo.obj.uiObjType = uiObjType;
		req.cmdInfo.obj.usIndex_obj = usIndex_obj;
		//  2016/07/24
		//req.cmdInfo.obj.usHelp_subIndex  =  pDlgPtzControl->m_var.remote.remoteCamera.qisResObj.resObj.usHelp_subIndex;
		req.cmdInfo.obj.usHelp_subIndex = usHelp_subIndex;
		//
		req.cmdInfo.idInfo = idInfo;
		req.cmdInfo.iChannel = iChannel;
		//
		req.cmdInfo.ucCmd = ucCmd;
		req.cmdInfo.ucParam = ucParam;
		req.cmdInfo.ucMouseStatus = ucMouseStatus;
		//
		req.paramU = *pParam;


		//
		//if  (  postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_outputTask,  0,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  (  char  *  )&req,  sizeof(  req  ),  0,  &pDlgPtzControl->m_var.remote.remoteCamera.qisResObj.idInfo,  uiChannelType,  NULL,  FALSE  )  )  traceLogA(  "postMsg2Mgr_mc failed"  );
		if (postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_outputTask, 0, CONST_qyCmd_sendMedia, tStartTran, uiTranNo, 0, (char*)&req, sizeof(req), 0, &idInfo_to, uiChannelType, NULL, FALSE))  traceLogA((char*)"postMsg2Mgr_mc failed");
	}
#endif

	iErr = 0;

errLabel:

	return  iErr;
}



int  getUi64IdFromReg(TCHAR* pBuf, QY_MESSENGER_ID* pIdInfos, int  maxCnt_pIdInfos)
{
	if (!pBuf)  return  -1;
	if (!pIdInfos)  return  -1;
	if (!maxCnt_pIdInfos)  return  -1;

	memset(pIdInfos, 0, sizeof(QY_MESSENGER_ID) * maxCnt_pIdInfos);

	int  len;
	TCHAR  tmpBuf[256] = _T("");
	TCHAR* p, * p1;
	int    tmp, i;
	p = pBuf;
	p1 = _tcschr(p, ',');

	if (!p1) {
		tmp = _ttol(pBuf);
		pIdInfos[0].ui64Id = tmp;
	}
	else {
		for (i = 0; i < maxCnt_pIdInfos; i++)
		{
			tmpBuf[0] = 0;
			len = min(p1 - p, mycountof(tmpBuf) - 1);
			_tcsncpy(tmpBuf, p, len);
			tmpBuf[len] = 0;
			tmp = _ttol(tmpBuf);
			pIdInfos[i].ui64Id = tmp;
			p = p1 + 1;
			p1 = _tcschr(p, ',');
			if (!p1) {
				if (i < maxCnt_pIdInfos - 1) {
					tmp = _ttol(p);
					pIdInfos[i + 1].ui64Id = tmp;
				}
				break;
			}
		}
	}

	return  0;
}


int  getBufFromUi64Id(QY_MESSENGER_ID* idInfos, int  maxCnt_idInfos, TCHAR* pBuf, int  maxCnt_pBuf)
{
	if (!pBuf)  return  -1;
	pBuf[0] = 0;

	for (int i = 0; i < maxCnt_idInfos; i++)
	{
		if (!(idInfos[i].ui64Id))  continue;

		if (pBuf[0] == 0)_sntprintf(pBuf, maxCnt_pBuf, _T("%I64u"), idInfos[i].ui64Id);
		else
		{
			_sntprintf(pBuf, maxCnt_pBuf, _T("%s,%I64u"), pBuf, idInfos[i].ui64Id);
		}
	}
	return  0;
}

//  2012/08/09
#define		DEFAULT_ptzProto		CONST_ptzProto_PELCO_D;

__declspec(dllexport)  int  getPtzSettings(void* pCOM_PORT_cfg)
{
	COM_PORT_cfg* pCfg = (COM_PORT_cfg*)pCOM_PORT_cfg;

	int					iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	TCHAR* pRegVal = NULL;
	QY_REG				reg;
	TCHAR				tBuf[255 + 1] = _T("");
	TCHAR* pT;
	long				lVal;
	TCHAR				rootKeyStr[256] = _T("");

	memset(&reg, 0, sizeof(reg));
	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	lstrcpyn(reg.rootKey, CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), mycountof(reg.rootKey));

	memset(pCfg, 0, sizeof(pCfg));
	//
	//  2015/09/20
	pCfg->iPtzType = DEFAULT_ptzType;		//  2015/09/20
	//
	pCfg->m_pelcoType = DEFAULT_ptzProto;	//  0;
	pCfg->m_nAddr = 1;

	pCfg->portNo = 1;	//  0;
	pCfg->m_rate = 2400;	//  9600;
	pCfg->m_parity = NOPARITY;
	pCfg->m_dataBit = 8;
	pCfg->m_stopBit = ONESTOPBIT;

	//  2017/08/29
	if (pQyMc->iCustomId == CONST_qyCustomId_bjyz) {
		pCfg->iPtzType = CONST_ptzType_serialPort;
		pCfg->m_rate = 9600;
	}


	//  2015/09/20
	pRegVal = (TCHAR*)CONST_regValName_ptzType;
	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		tBuf[0] = 0;
	}
	lVal = _tcstol(tBuf, &pT, 10);
	if (lVal)  pCfg->iPtzType = lVal;

	//
	pRegVal = (TCHAR*)CONST_regValName_ptzProtoType;
	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		tBuf[0] = 0;
	}
	lVal = _tcstol(tBuf, &pT, 10);
	if (lVal)  pCfg->m_pelcoType = lVal;

	pRegVal = (TCHAR*)CONST_regValName_ptzAddr;
	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		tBuf[0] = 0;
	}
	lVal = _tcstol(tBuf, &pT, 10);
	if (lVal)  pCfg->m_nAddr = lVal;

	pRegVal = (TCHAR*)CONST_regValName_comName;
	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		tBuf[0] = 0;
	}
	lVal = _tcstol(tBuf, &pT, 10);
	if (lVal)  pCfg->portNo = lVal;

	pRegVal = (TCHAR*)CONST_regValName_comBaud;
	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		tBuf[0] = 0;
	}
	lVal = _tcstol(tBuf, &pT, 10);
	if (lVal)  pCfg->m_rate = lVal;

	pRegVal = (TCHAR*)CONST_regValName_comParity;
	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		tBuf[0] = 0;
	}
	lVal = _tcstol(tBuf, &pT, 10);
	if (lVal)  pCfg->m_parity = lVal;

	pRegVal = (TCHAR*)CONST_regValName_comData;
	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		tBuf[0] = 0;
	}
	lVal = _tcstol(tBuf, &pT, 10);
	if (lVal)  pCfg->m_dataBit = lVal;

	pRegVal = (TCHAR*)CONST_regValName_comStopBit;
	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		tBuf[0] = 0;
	}
	lVal = _tcstol(tBuf, &pT, 10);
	if (lVal)  pCfg->m_stopBit = lVal;

	pRegVal = (TCHAR*)CONST_regValName_remotePtzUsers;
	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		tBuf[0] = 0;
	}
	if (tBuf[0])
	{
		getUi64IdFromReg(tBuf, pCfg->idInfos_allowed, mycountof(pCfg->idInfos_allowed));
	}

	//
	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_memoAppending, (char*)tBuf, sizeof(tBuf), 0)) {
		tBuf[0] = 0;
	}
	lstrcpyn(pCfg->tHint, tBuf, mycountof(pCfg->tHint));

	//
	pCfg->bCfgInited = TRUE;

	return  0;

}

