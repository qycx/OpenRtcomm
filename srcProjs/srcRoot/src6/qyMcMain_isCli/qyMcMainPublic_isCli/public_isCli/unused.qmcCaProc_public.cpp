



#include	"stdafx.h"
#include	<Windows.h>
#include	"qyMcMainCommon.h"
//#include <ctxQmc_sm.h>
#include	"myCmdParams_open.h"
#include	"myTChar.h"
#include	"hgCommProc.h"
#include	"ctxQmc.h"
#include	<time.h>
#include	"qyMsgFunc.h"
#include	"qnmCommProc_mis.h"
#include	"smCommProc.h"
#include	"smLoginProc.h"


#include	"myCmdParams_open.h"
#include	"tmpRegFunc_open.h"
#include	"imCommType_defs.h"
#include	"qyMcMainCommon.h"
#include	"qnmCommProc.h"
#include <DlgMcClientLogon.h>
#include	"smLoginProc.h"
#include	"ctxQmc.h"
//#include <smProc.h>
//#include	"ctxQmc_sm.h"
#include	"qyCusResTemp.h"
#include <qmcCommFunc_isCli.h>
#include <dlgtalkproc.h>
#include <qmcStruct_defs.h>
#include <funcsForIsCliHelp.h>

extern int send_showInfo(int mainWnd_loopCtrl);

//
int  parseHgCmd_sxrz_servReply( char* dataBuf, int  dataBufLen, int parent_iHgType,  Param_sxrz_servReply* pParam)
{
	int  iErr = -1;
	char* pData = dataBuf;
	//
	//
	TCHAR  tBuf[128];
	char  buf[1024];

	//
	if (!parent_iHgType) {
		memset(pParam, 0, sizeof(pParam[0]));
	}

	//
	for (;; ) {

		//
		pData = strchr(pData, '[');
		if (!pData)  break;

		//
		char seg[1024];
		if (getSeg(pData, seg, mycountof(seg)))  break;

		//
		char* tag_msgr = (char*)"msgr=";
		QY_MESSENGER_ID  idInfo_msgr;
		//
		QY_MESSENGER_ID  idInfo;
		idInfo.ui64Id = geti64Val(seg, tag_msgr);
		if (idInfo.ui64Id) {
			//
			pParam->idInfo_msgr = idInfo;
		}

		//
		char* tag_rc = (char*)"rc=";
		int rc = geti64Val(seg, tag_rc);
		if (rc) {
			pParam->iRc = rc;
		}

		//
		char* tag_org = (char*)"org=";
		int cmd_org = geti64Val(seg, tag_org);
		if (cmd_org) {
			pParam->cmd_org = cmd_org;
		}

		//
		int objType = 0;
		char* tag_obj = (char*)"obj=";
		objType = geti64Val(seg, tag_obj);

		int len = 0;
		char* tag_len = (char*)"len=";
		len = geti64Val(seg, tag_len);

		//
		int  n;

		//
#ifdef  __DEBUG__
		if (pParam->cmd_org == CONST_hgCmd_retrievePlans) {
			int  ii = 0;
		}
		if (objType == 122) {
			int  ii = 0;
		}
		if (objType == 124) {
			int  ii = 0;
		}
		if (pParam->cmd_org == CONST_hgCmd_usrLogin) {
			int  ii = 0;
		}
		if (pParam->cmd_org == CONST_hgCmd_retrieveP2pList) {
			int  ii = 0;
		}
#endif


		//
		if (objType > 0 && len > 0) {
			char* pStart = pData + strlen(seg) + 2;
			
			//
			if (objType == 123) {
				int  ii = 0;
			}

			//
			if (parent_iHgType) {
				//
				if (parent_iHgType == CONST_hgType_p2pMem) {
					//
					if (pParam->index_p2pMem >= mycountof(pParam->p2pInfos)) {
						goto  errLabel;
					}
					P2pInfo* pMem = &pParam->p2pInfos[pParam->index_p2pMem];
					//
					switch (objType) {
					case  CONST_hgType_p2pMem_index:
						pParam->index_p2pMem = atol(pStart);
						if (pParam->index_p2pMem >= mycountof(pParam->p2pInfos)) {
							goto  errLabel;
						}
						break;
					case  CONST_hgType_login_terminalName:
						safeStrnCpy(pStart, buf, len + 1);
						myUtf82TChar(buf, pMem->termName, mycountof(pMem->termName));
						break;
					case  CONST_hgType_grpIdInfo:
						QY_MESSENGER_ID  tmpGrpId;
						idStr2Info(pStart, &tmpGrpId);
						pMem->grpInfo = tmpGrpId.ui64Id;
						break;
					case  CONST_hgType_termId:
						QY_MESSENGER_ID  tmpTermId;
						idStr2Info(pStart, &tmpTermId);
						pMem->idfo = tmpTermId.ui64Id;
						break;
					case  CONST_hgType_meeting_level:

						pMem->p2pLevel = atol(pStart);
						break;

					default:
						break;


					}
					//
					
				}
				else {
					//
					int  index = 0;
					switch (parent_iHgType) {
					case  CONST_hgType_waitMeeting_0:
						index = 0;
						break;
					case  CONST_hgType_waitMeeting_1:
						index = 1;
						break;
					case  CONST_hgType_waitMeeting_2:
						index = 2;
						break;
					case  CONST_hgType_waitMeeting_3:
						index = 3;
						break;
					case  CONST_hgType_waitMeeting_4:
						index = 4;
						break;
					default:
						break;

					}
					MeetingInfo* pMem = &pParam->meetingInfos[index];
					switch (objType) {
					case  CONST_hgType_meetingName:
						safeStrnCpy(pStart, buf, len + 1);
						myUtf82TChar(buf, pMem->meetingName, mycountof(pMem->meetingName));
						break;
					case  CONST_hgType_meetingId:
						QY_MESSENGER_ID  tmp;
						idStr2Info(pStart, &tmp);
						pMem->meetingId = tmp.ui64Id;
						break;
					case  CONST_hgType_meeting_level:
						pMem->meetingLevel = atol(pStart);
						break;
					case  CONST_hgType_meeting_date:
						safeStrnCpy(pStart, buf, len + 1);
						safeStrnCpy(buf, pMem->meetingData, mycountof(pMem->meetingData));
						break;
					case  CONST_hgType_meeting_time:
						safeStrnCpy(pStart, buf, len + 1);
						safeStrnCpy(buf, pMem->meetingTime, mycountof(pMem->meetingTime));
						break;
					case  CONST_hgType_meeting_department:
						safeStrnCpy(pStart, buf, len + 1);
						myUtf82TChar(buf, pMem->meetingDepartment, mycountof(pMem->meetingDepartment));
						break;
					case  CONST_hgType_meeting_convener:
						safeStrnCpy(pStart, buf, len + 1);
						myUtf82TChar(buf, pMem->meetingConvener, mycountof(pMem->meetingConvener));
						break;
					default:
						break;


					}
				}
			}
			else {

				//
				switch (objType) {
				case  CONST_hgType_sxrz_serv_random:
					if (len > sizeof(pParam->serv_random) - 1) {
						goto  errLabel;
					}
					safeStrnCpy(pStart, pParam->serv_random, len + 1);
					//
					n = strlen(pParam->serv_random);
					//
					break;

				case  CONST_hgType_sxrz_serv_cert:
					if (len > sizeof(pParam->serv_cert) - 1) {
						goto  errLabel;
					}
					safeStrnCpy(pStart, pParam->serv_cert, len + 1);
					//
					n = strlen(pParam->serv_cert);

					break;

				case  CONST_hgType_sxrz_serv_signData:

					if (len > sizeof(pParam->serv_signData) - 1) {
						goto  errLabel;
					}
					safeStrnCpy(pStart, pParam->serv_signData, len + 1);
					//
					n = strlen(pParam->serv_signData);

					break;
				case  CONST_hgType_grpIdInfo:
					idStr2Info(pStart, &pParam->idInfo_grp);
					break;
				case  CONST_hgType_hkStatus:
					pParam->iHkStatus = atol(pStart);
					break;
				case  CONST_hgType_meetingId:
					QY_MESSENGER_ID  tmp;
					idStr2Info(pStart, &tmp);
					pParam->ui64MeetingId = tmp.ui64Id;
					break;
				case  CONST_hgType_logType:
					pParam->iLogType = atol(pStart);
					break;
				case  CONST_hgType_logDesc:
					safeStrnCpy(pStart, buf, len + 1);
					myUtf82TChar(buf, pParam->tLogDesc, mycountof(pParam->tLogDesc));
					break;

				case CONST_hgType_debugIp:
					if (len > sizeof(pParam->debugIp) - 1) {
						goto  errLabel;
					}
					safeStrnCpy(pStart, pParam->debugIp, len + 1);
					break;
				case CONST_hgType_debugPort:
					safeStrnCpy(pStart, buf, len + 1);
					pParam->debugPort = atoi(buf);
					break;

					
				case  CONST_hgType_time:
					safeStrnCpy(pStart, pParam->timeBuf, mycountof(pParam->timeBuf));
					break;
				case  CONST_hgType_bWarn:
					pParam->bWarn = atol(pStart);
					break;
				case  CONST_hgType_waitMeeting_0:
				case  CONST_hgType_waitMeeting_1:
				case  CONST_hgType_waitMeeting_2:
				case  CONST_hgType_waitMeeting_3:
				case  CONST_hgType_waitMeeting_4:
					//
				case  CONST_hgType_p2pMem:
					//
					if (objType != CONST_hgType_waitMeeting_0) {
						int ii = 0;
					}
					//
					safeStrnCpy(pStart, buf, len + 1);
					//
					parseHgCmd_sxrz_servReply(buf, len, objType,  pParam);
					//
					break;

				case  CONST_hgType_login_terminalName:
					  safeStrnCpy(pStart, buf, len + 1);
					  myUtf82TChar(buf, pParam->login_terminalName, mycountof(pParam->login_terminalName));
					  break;
				case  CONST_hgType_login_userName:
					  safeStrnCpy(pStart, buf, len + 1);
					  myUtf82TChar(buf, pParam->login_userName, mycountof(pParam->login_userName));
					  break;
				case  CONST_hgType_login_rcDesc:
					  safeStrnCpy(pStart, buf, len + 1);
					  myUtf82TChar(buf, pParam->rcDesc,mycountof(pParam->rcDesc));
					  break;
				case  CONST_hgType_2ndMcuIp:
					  safeStrnCpy(pStart, pParam->str2ndMcuIp, min(mycountof(pParam->str2ndMcuIp),len + 1));
					  break;
				case  CONST_hgType_confMcuIp:
					  safeStrnCpy(pStart, pParam->confMcuIp, min(mycountof(pParam->confMcuIp), len + 1));
					  break;
				case  CONST_hgType_terminal_ip:
					safeStrnCpy(pStart, pParam->terminalIp , min(mycountof(pParam->terminalIp), len + 1));
					 break;
				case  CONST_hgType_hkOverTime:
					pParam->iOverTime = atol(pStart);
					break;
					  //
				case CONST_hgType_peerTermName:
					safeStrnCpy(pStart, buf, len + 1);
					myUtf82TChar(buf, pParam->peerTermName, mycountof(pParam->peerTermName));
					break;
				case CONST_hgType_fromTermName:
					safeStrnCpy(pStart, buf, len + 1);
					myUtf82TChar(buf, pParam->fromTermName, mycountof(pParam->fromTermName));
					break;
				case  CONST_hgType_meeting_level:
					pParam->p2pLevel = atol(pStart);
					break;
				case  CONST_hgType_system_level:
					pParam->systemLevel = atol(pStart);
					break;
				case  CONST_hgType_termXt_time:
					pParam->termXt_time = atol(pStart);
					break;
				case CONST_hgType_termOver_time:
					pParam->termOver_time = atol(pStart);
					break;
				case  CONST_hgType_termIsPortOpen:
					pParam->termIsPort_open = atol(pStart);
					break;
				case  CONST_hgType_bLegal:
					pParam->iLegal = atol(pStart);
					break;
				default:

					break;
				}

			}

		}


		//
		pData += strlen(seg) + 2;
		if (objType > 0 && len > 0) {
			pData += len;
		}
		//
		continue;
	}







	//
	iErr = 0;
errLabel:
	return  iErr;

}





//
extern  "C"  BOOL  bGetCaRandom(QY_ENV * pEnv, char* serverIp, unsigned  short  serverPort, MIS_CNT  *  pMisCnt,  QY_COMM_AUTHINFO_MIS  *  pAuthInfo, int  serviceId, char* ver, QY_ENC_CTX * pCommEncCtx, __int64  i64StartTime_base,  SOCK_TIMEOUT * pTo)
{
	BOOL						bRet = FALSE;
	//
	QY_SOCK					sock;
	QY_COMM_SESSION			session;
	BOOL						bSessionOpen = FALSE;
	char						buf[8192];
	int						len;
	char* ptr;
	AUTH_RESP_MIS				authResp;

	// traceLogA(  (char*)  "bServConntected_mis enters"  );
#ifdef  __DEBUG__
	showInfo_open0(0, mynull, _T("getRandom enters"));
#endif

	//
	unsigned  short  usAuthCmd = CONST_qnmAuthCmd_getCaRandom;


	//  ÏÈ·¢Ò»¸öhelloClient, 
	clearQySock(&sock);
	memset(&session, 0, sizeof(session));

	//
	Param_dbg  param;
	param.m_pHint = (TCHAR*)_T("bGetCaRandom.377");

	len = sizeof(buf);
	if (qnmOpenSession_mis(serverIp, serverPort, pAuthInfo, usAuthCmd, CONST_channelType_talking, NULL, serviceId, ver, NULL, i64StartTime_base,  &session, &sock, pTo, buf, (unsigned  int*)&len,  &param))  goto  errLabel;
	bSessionOpen = TRUE;
	if (!isRcOk(session.usLastRespCode_i))  goto  errLabel;
	qnmCloseSession_msg(mynull,&session, &sock, pTo, _T("bGetCaRandom.l444"));  bSessionOpen = FALSE;

	memset(&authResp, 0, sizeof(authResp));
	ptr = buf;
	if (stream2Data(&ptr, (unsigned  int*)&len, filterStream_is, tmpHandler_stream2AuthResp_mis, NULL, &authResp))  goto  errLabel;
	pMisCnt->commEncCtx.ucbCaRandomDownloaded = TRUE;

#ifdef  __DEBUG__
	traceLogA((char*)"authResp, random %d bytes, [%s]", strlen(authResp.caRandom), authResp.caRandom);
#endif

	{
		CQySyncObj	syncObj;

		traceLogA((char*)"ca_random verified");

		if (syncObj.sync(CONST_mutexName_syncKey_qmc))  goto  errLabel;

		//  
		if (strlen(authResp.caRandom) >= mycountof(pMisCnt->commEncCtx.caRandom))  goto  errLabel;
		safeStrnCpy(authResp.caRandom, pMisCnt->commEncCtx.caRandom, mycountof(pMisCnt->commEncCtx.caRandom));

		//
		//safeStrnCpy((char*)"7c20807c58eb4ad4a74c52247137dfdf", pMisCnt->commEncCtx.caRandom, mycountof(pMisCnt->commEncCtx.caRandom));
		//safeStrnCpy((char*)"72d1679041054a6fb102ef750acb76fd", pMisCnt->commEncCtx.caRandom, mycountof(pMisCnt->commEncCtx.caRandom));
		//cc560c0d28fd494b857f7e629d1b4bc2
		//72d1679041054a6fb102ef750acb76fd
		

		//
		pMisCnt->commEncCtx.ucbCaRandomOk = TRUE;
	}

	//  Èç¹ûÃ»ÓÐÑéÖ¤£¬¾Í²»Òª°ÑÑéÖ¤ÐÅÏ¢·¢ËÍµ½·þÎñÆ÷ÉÏ£¬ÕâÀïÍË³ö
	if (!pMisCnt->commEncCtx.ucbCaRandomDownloaded) {
		traceLogA((char*)"");
		goto  errLabel;
	}


	bRet = TRUE;

errLabel:

	if (bSessionOpen)  qnmCloseSession_msg(mynull,&session, &sock, pTo,_T("bGetCaRandom.l488"));

	if (!bRet) {
		pMisCnt->commEncCtx.ucbCaRandomDownloaded = false;
		pMisCnt->commEncCtx.ucbCaRandomOk = false;
	}

	//
	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsCli"), 0, _T(""), _T(""), _T("getRandom: Connecting to %s:%d %s"), CQyString(serverIp), (int)serverPort, bRet ? _T("OK") : _T("Failed"));

	//  traceLogA(  (char*)  "bServConntected_mis leaves"  );

	return  bRet;

}


//
extern  "C"  BOOL  bGetCaServCfg(QY_ENV * pEnv, char* serverIp, unsigned  short  serverPort, MIS_CNT * pMisCnt, QY_COMM_AUTHINFO_MIS * pAuthInfo, int  serviceId, char* ver, QY_ENC_CTX * pCommEncCtx, __int64  i64StartTime_base,  SOCK_TIMEOUT * pTo)
{
	BOOL						bRet = FALSE;
	//
	QY_SOCK					sock;
	QY_COMM_SESSION			session;
	BOOL						bSessionOpen = FALSE;
	char						buf[8192];
	int						len;
	char* ptr;
	AUTH_RESP_MIS				authResp;

	// traceLogA(  (char*)  "bServConntected_mis enters"  );
#ifdef  __DEBUG__
	showInfo_open0(0, mynull, _T("getCaServCfg enters"));
#endif

	//
	unsigned  short  usAuthCmd = CONST_qnmAuthCmd_getCaServCfg;


	//  ÏÈ·¢Ò»¸öhelloClient, 
	clearQySock(&sock);
	memset(&session, 0, sizeof(session));

	//
	Param_dbg  param;
	param.m_pHint = (TCHAR*)_T("bGetCaServCfg.472");

	//
	len = sizeof(buf);
	if (qnmOpenSession_mis(serverIp, serverPort, pAuthInfo, usAuthCmd, CONST_channelType_talking, NULL, serviceId, ver, NULL, i64StartTime_base,  &session, &sock, pTo, buf, (unsigned  int*)&len,  &param))  goto  errLabel;
	bSessionOpen = TRUE;
	if (!isRcOk(session.usLastRespCode_i))  goto  errLabel;
	qnmCloseSession_msg(mynull,&session, &sock, pTo,_T("bGetCaServCfg.l540"));  bSessionOpen = FALSE;

	memset(&authResp, 0, sizeof(authResp));
	ptr = buf;
	if (stream2Data(&ptr, (unsigned  int*)&len, filterStream_is, tmpHandler_stream2AuthResp_mis, NULL, &authResp))  goto  errLabel;
	pMisCnt->commEncCtx.caServCfg.ucbDownloaded = TRUE;

#ifdef  __DEBUG__
	traceLogA((char*)"authResp, random %d bytes, [%s]", strlen(authResp.caRandom), authResp.caRandom);
#endif

	{
		CQySyncObj	syncObj;

		traceLogA((char*)"ca_random verified");

		if (syncObj.sync(CONST_mutexName_syncKey_qmc))  goto  errLabel;

		//

		//  
		//safeStrnCpy(authResp.caGwIp, pMisCnt->commEncCtx.caServCfg.caGwIp, mycountof(pMisCnt->commEncCtx.caServCfg.caGwIp));
		//pMisCnt->commEncCtx.caServCfg.caGwPort = authResp.caGwPort;
		parseCaServCfg(authResp.caGwCfg, pMisCnt->commEncCtx.caServCfg.caGwIp, mycountof(pMisCnt->commEncCtx.caServCfg.caGwIp), &pMisCnt->commEncCtx.caServCfg.caGwPort, pMisCnt->commEncCtx.caServCfg.hgGwIp, mycountof(pMisCnt->commEncCtx.caServCfg.hgGwIp), &pMisCnt->commEncCtx.caServCfg.hgGwPort);
	
		safeStrnCpy(authResp.caYqServCfg, pMisCnt->commEncCtx.caServCfg.caYqServIp, mycountof(pMisCnt->commEncCtx.caServCfg.caYqServIp));


		//
		pMisCnt->commEncCtx.caServCfg.ucbOk = TRUE;
	}

	//  Èç¹ûÃ»ÓÐÑéÖ¤£¬¾Í²»Òª°ÑÑéÖ¤ÐÅÏ¢·¢ËÍµ½·þÎñÆ÷ÉÏ£¬ÕâÀïÍË³ö
	if (!pMisCnt->commEncCtx.caServCfg.ucbDownloaded) {
		traceLogA((char*)"");
		goto  errLabel;
	}


	bRet = TRUE;

errLabel:

	if (bSessionOpen)  qnmCloseSession_msg(mynull,&session, &sock, pTo,_T("bGetCaServCfg.l583"));

	if (!bRet) {
		memset(&pMisCnt->commEncCtx.caServCfg, 0, sizeof(pMisCnt->commEncCtx.caServCfg));
	}

	//
	qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsCli"), 0, _T(""), _T(""), _T("getCaServCfg: Connecting to %s:%d %s"), CQyString(serverIp), (int)serverPort, bRet ? _T("OK") : _T("Failed"));

	//  traceLogA(  (char*)  "bServConntected_mis leaves"  );

	return  bRet;

}





//
int sendRespToHg(int respCode, short org_cmd,  unsigned  __int64  meetingId,  Param_hg_cliReply  *  pCliReply )
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	char respBuf[1024]  =  "";

	//
	_snprintf(respBuf, mycountof(respBuf), "[msgr=%I64u]", pMisCnt->idInfo.ui64Id);
	_snprintf(respBuf, mycountof(respBuf), "%s [rc=%d] [org=%d]", respBuf, respCode, (int)org_cmd  );
	char meetingIdStr[128];
	_snprintf(meetingIdStr, mycountof(meetingIdStr), "%I64u", meetingId);
	_snprintf(respBuf, mycountof(respBuf), "%s [obj=%d len=%d]%s", respBuf, CONST_hgType_meetingId, strlen(meetingIdStr), meetingIdStr);
	char hgStatus_oldStr[128];
	_snprintf(hgStatus_oldStr, mycountof(hgStatus_oldStr), "%d", pCliReply->iHkStatus_old);
	_snprintf(respBuf, mycountof(respBuf), "%s [obj=%d len=%d]%s", respBuf, CONST_hgType_hkStatus_old, strlen(hgStatus_oldStr), hgStatus_oldStr);


	//					
	//
	MACRO_prepareForTran();
	QIS_ca_req  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_qisCaReq;

	//
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s", respBuf);
	//
#ifdef  __DEBUG__
							//_snprintf(req.sxrz_cliData, mycountof(req.sxrz_cliData), "%s [obj=%d len=%d]%s", req.sxrz_cliData, CONST_sxrz_serv_random,  strlen(pVc->sxrz.serv.param_sxrz_servReply.serv_random), pVc->sxrz.serv.param_sxrz_servReply.serv_random);
#endif
							//
	req.ca_cliDataLen = strlen(req.ca_cliData);

	//
	int len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);



	//
	return  0;
}

int reportToHg_speakOn(unsigned  __int64  ui64MeetingId_hg, unsigned  __int64  ui64Id_grp, bool  bOn)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	char respBuf[1024] = "";

	//
	_snprintf(respBuf, mycountof(respBuf), "[msgr=%I64u]", pMisCnt->idInfo.ui64Id);
	//_snprintf(respBuf, mycountof(respBuf), "%s [rc=%d] [org=%d]", respBuf, respCode, (int)org_cmd);
	_snprintf(respBuf, mycountof(respBuf), "%s [cmd=%d]", respBuf, CONST_hgCmd_ReportSpeak);

	char meetingIdStr[128];
	_snprintf(meetingIdStr, mycountof(meetingIdStr), "%I64u", ui64MeetingId_hg);
	_snprintf(respBuf, mycountof(respBuf), "%s [obj=%d len=%d]%s", respBuf, CONST_hgType_meetingId, strlen(meetingIdStr), meetingIdStr);
	
	//
	char grpIdInfoStr[128];
	_snprintf(grpIdInfoStr, mycountof(grpIdInfoStr), "%I64u", ui64Id_grp);
	//CONST_hgType_grpIdInfo
	_snprintf(respBuf, mycountof(respBuf), ("%s [obj=%d len=%d]%s"), respBuf, CONST_hgType_grpIdInfo, strlen(grpIdInfoStr), grpIdInfoStr);

	char  speakStatusBuf[128];
	_snprintf(speakStatusBuf, mycountof(speakStatusBuf), "%d", pProcInfo->xt.bSpeak);
	_snprintf(respBuf, mycountof(respBuf), "%s [obj=%d len=%d]%s", respBuf, CONST_hgType_bSpeak, strlen(speakStatusBuf), speakStatusBuf);


	//
	if (1) {
		TCHAR  tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("reportToHg_speakOn: bOn %d, meetingId %I64u"), bOn, ui64MeetingId_hg);
		showInfo_open0(0, 0, tBuf);
	}



	//					
	//
	MACRO_prepareForTran();
	QIS_ca_req  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_qisCaReq;

	//
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s", respBuf);
	//
#ifdef  __DEBUG__
							//_snprintf(req.sxrz_cliData, mycountof(req.sxrz_cliData), "%s [obj=%d len=%d]%s", req.sxrz_cliData, CONST_sxrz_serv_random,  strlen(pVc->sxrz.serv.param_sxrz_servReply.serv_random), pVc->sxrz.serv.param_sxrz_servReply.serv_random);
#endif
							//
	req.ca_cliDataLen = strlen(req.ca_cliData);

	//
	int len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);




	//
	return  0;
}

//
int reportToHg_meetingOn(  unsigned  __int64  ui64MeetingId_hg,  int  iMeetingType,  unsigned  __int64  ui64Id_grp,  bool  bOn  )
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	char respBuf[1024] = "";

	//
	_snprintf(respBuf, mycountof(respBuf), "[msgr=%I64u]", pMisCnt->idInfo.ui64Id);
	//_snprintf(respBuf, mycountof(respBuf), "%s [rc=%d] [org=%d]", respBuf, respCode, (int)org_cmd);
	_snprintf(respBuf, mycountof(respBuf), "%s [cmd=%d]", respBuf, CONST_hgCmd_report);

	char meetingIdStr[128];
	_snprintf(meetingIdStr, mycountof(meetingIdStr), "%I64u", ui64MeetingId_hg);
	_snprintf(respBuf, mycountof(respBuf), "%s [obj=%d len=%d]%s", respBuf, CONST_hgType_meetingId, strlen(meetingIdStr), meetingIdStr);
	char statusBuf[128];
	_snprintf(statusBuf, mycountof(statusBuf), "%d", bOn);
	_snprintf(respBuf, mycountof(respBuf), "%s [obj=%d len=%d]%s", respBuf, CONST_hgType_meetingStatus, strlen(statusBuf), statusBuf);
	char  meetingTypeBuf[32];
	_snprintf(meetingTypeBuf, mycountof(meetingTypeBuf), "%d", iMeetingType);
	_snprintf(respBuf, mycountof(respBuf), "%s [obj=%d len=%d]%s", respBuf, CONST_hgType_meetingType, strlen(meetingTypeBuf), meetingTypeBuf);
	//
	char grpIdInfoStr[128];
	_snprintf(grpIdInfoStr, mycountof(grpIdInfoStr), "%I64u", ui64Id_grp);
	//CONST_hgType_grpIdInfo
	_snprintf(respBuf, mycountof(respBuf), ("%s [obj=%d len=%d]%s"), respBuf, CONST_hgType_grpIdInfo, strlen(grpIdInfoStr), grpIdInfoStr);

	char  speakStatusBuf[128];
	_snprintf(speakStatusBuf, mycountof(speakStatusBuf), "%d", pProcInfo->xt.bSpeak);
	_snprintf(respBuf, mycountof(respBuf), "%s [obj=%d len=%d]%s", respBuf, CONST_hgType_bSpeak, strlen(speakStatusBuf), speakStatusBuf);


	//
	if (1) {
		TCHAR  tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("reportToHg_meetingOn: bOn %d, meetingId %I64u"), bOn,  ui64MeetingId_hg);
		showInfo_open0(0, 0, tBuf);
	}



	//					
	//
	MACRO_prepareForTran();
	QIS_ca_req  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_qisCaReq;

	//
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s", respBuf);
	//
#ifdef  __DEBUG__
							//_snprintf(req.sxrz_cliData, mycountof(req.sxrz_cliData), "%s [obj=%d len=%d]%s", req.sxrz_cliData, CONST_sxrz_serv_random,  strlen(pVc->sxrz.serv.param_sxrz_servReply.serv_random), pVc->sxrz.serv.param_sxrz_servReply.serv_random);
#endif
							//
	req.ca_cliDataLen = strlen(req.ca_cliData);

	//
	int len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);




	//
	return  0;
}



//
int reportToHg_saveAv(unsigned  __int64  ui64MeetingId_hg,  char* video_url, char* resource_url)

{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	char respBuf[1024] = "";

	if (!video_url || !resource_url)  return  -1;

	//
	_snprintf(respBuf, mycountof(respBuf), "[msgr=%I64u]", pMisCnt->idInfo.ui64Id);
	//_snprintf(respBuf, mycountof(respBuf), "%s [rc=%d] [org=%d]", respBuf, respCode, (int)org_cmd);
	_snprintf(respBuf, mycountof(respBuf), "%s [cmd=%d]", respBuf, CONST_hgCmd_report);

	//
	_snprintf(respBuf, mycountof(respBuf), "%s [obj=%d len=%d]%s", respBuf, CONST_hgType_video_url, strlen(video_url), video_url);
	_snprintf(respBuf, mycountof(respBuf), "%s [obj=%d len=%d]%s", respBuf, CONST_hgType_resource_url, strlen(resource_url), resource_url);
	//
	char meetingIdStr[128];
	_snprintf(meetingIdStr, mycountof(meetingIdStr), "%I64u", ui64MeetingId_hg);
	_snprintf(respBuf, mycountof(respBuf), "%s [obj=%d len=%d]%s", respBuf, CONST_hgType_meetingId, strlen(meetingIdStr), meetingIdStr);

	//
	if (1) {
		TCHAR  tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("reportToHg_saveAv: meetingId %I64u. lll"), ui64MeetingId_hg);
		showInfo_open0(0, 0, tBuf);
	}

	//
	MACRO_prepareForTran();
	QIS_ca_req  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_qisCaReq;

	//
	//req.sHgCmd  


	//
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s", respBuf);
	//
#ifdef  __DEBUG__
							//_snprintf(req.sxrz_cliData, mycountof(req.sxrz_cliData), "%s [obj=%d len=%d]%s", req.sxrz_cliData, CONST_sxrz_serv_random,  strlen(pVc->sxrz.serv.param_sxrz_servReply.serv_random), pVc->sxrz.serv.param_sxrz_servReply.serv_random);
#endif
							//
	req.ca_cliDataLen = strlen(req.ca_cliData);

	//
	int len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);




	//
	return  0;
}










//
int qmcLogForHg(  int  logType,  TCHAR  *  tLogDesc, bool bWarn)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	char  timeBuf[CONST_qyTimeLen + 1] = "";
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));


	getCurTime(timeBuf);




	//if (bMeOnline(pQyMc)) {
	//	qmcSendLogToHg(logType, tLogDesc, timeBuf,bWarn);
	//	return  0;
	//}

	//
	FILE* fp = _tfopen(pQyMc->cfg.smTmpLogFile, _T("a"));
	if (fp) {
		//
		char  content[1024]="";
		//
		getHgLogStr(pMisCnt->idInfo.ui64Id,  logType, tLogDesc, timeBuf, bWarn,  content, mycountof(content));

		//
		fprintf(fp, "%s\n", content);

		//
		fclose(fp);
	}



	return  0;
}

//
int qmcChkSmTmpLogFile()
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	if (!bMeOnline(pQyMc))  return  0;

	//
	if (!bFileExists(pQyMc->cfg.smTmpLogFile))  return  0;


	//
	bool bLogNotSend = false;
	//
	FILE* fp = _tfopen(pQyMc->cfg.smTmpLogFile, _T("r"));
	if (fp) {
		char  buf[1024];
		for (;;) {
			if (!fgets(buf, mycountof(buf), fp))  break;
			//
			Param_sxrz_servReply param = { 0 };
			parseHgCmd_sxrz_servReply(buf, strlen(buf), 0, &param);
			//
			//if (param.iLogType) {
			
				time_t log_time = gettTimeByStr(param.timeBuf);
				time_t curr_time;
				time(&curr_time);
				int e = curr_time - log_time;
				if (abs(e) < 15) {
					bLogNotSend = true;
				}
			//}
		}
		//
		fclose(fp);
	}

	//
	if (bLogNotSend) return 0;

	{
		FILE* fp = nullptr;
		fp = _tfopen(pQyMc->cfg.smTmpLogFile, _T("r"));
		if (fp) {

			char  buf[1024];
			for (;;) {
				if (!fgets(buf, mycountof(buf), fp))  break;
				//
				Param_sxrz_servReply param = { 0 };
				parseHgCmd_sxrz_servReply(buf, strlen(buf), 0, &param);
				//
				//if (param.iLogType) 
				{
					qmcSendLogToHg(param.iLogType, param.tLogDesc, param.timeBuf, param.bWarn);
				}



			}


			fclose(fp);
		}
	}
	//
	bool  bRet  =  DeleteFile(pQyMc->cfg.smTmpLogFile);
	if (!bRet) {
		int  ii = 0;
	}

	//
	return  0;
}


//
//
int qmcSendLogToHg(int logType, TCHAR  * tLogDesc,  char  *  timeBuf, bool  bWarn )
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	char respBuf[1024] = "";

	if (!tLogDesc)  tLogDesc = (TCHAR*)_T("");
	if (!timeBuf)  timeBuf = (char*)"";

	//
#if 0
	_snprintf(respBuf, mycountof(respBuf), "[msgr=%I64u]", pMisCnt->idInfo.ui64Id);
	//_snprintf(respBuf, mycountof(respBuf), "%s [rc=%d] [org=%d]", respBuf, respCode, (int)org_cmd);
	_snprintf(respBuf, mycountof(respBuf), "%s [cmd=%d]", respBuf, CONST_hgCmd_log);
	//
	char  logDescBuf[256];
	myTChar2Utf8(tLogDesc, logDescBuf, mycountof(logDescBuf));
	_snprintf(respBuf, mycountof(respBuf), "%s [log=%d] [obj=%d len=%d]%s", respBuf, logType, CONST_hgType_logDesc, strlen(logDescBuf), logDescBuf);
#endif
	char content[1024];
	getHgLogStr(pMisCnt->idInfo.ui64Id,  logType, tLogDesc, timeBuf, bWarn,  content, mycountof(content));
	safeStrnCpy(content, respBuf, mycountof(respBuf));

	//					
	//
	MACRO_prepareForTran();
	QIS_ca_req  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_qisCaReq;

	//
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s", respBuf);
	//
#ifdef  __DEBUG__
							//_snprintf(req.sxrz_cliData, mycountof(req.sxrz_cliData), "%s [obj=%d len=%d]%s", req.sxrz_cliData, CONST_sxrz_serv_random,  strlen(pVc->sxrz.serv.param_sxrz_servReply.serv_random), pVc->sxrz.serv.param_sxrz_servReply.serv_random);
#endif
							//
	req.ca_cliDataLen = strlen(req.ca_cliData);

	//
	int len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);




	//
	return  0;
}

//
int qmcSendEndAvToHg( unsigned __int64 ui64Id_grp) {
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	char respBuf[1024] = "";
	char content[1024];
	getHgEndAvStr(pMisCnt->idInfo.ui64Id, ui64Id_grp, content, mycountof(content));
	safeStrnCpy(content, respBuf, mycountof(respBuf));

	//					
	//
	MACRO_prepareForTran();
	QIS_ca_req  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_qisCaReq;

	//
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s", respBuf);
	//

	req.ca_cliDataLen = strlen(req.ca_cliData);

	//
	int len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);




	//
	return  0;
}

int applyFy(QY_MESSENGER_ID idInfo_grp, BOOL  bEnable) {
	int  iErr = -1;
	HWND  hTalk;
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	QY_MC* pQyMc = QY_GET_GBUF();
	
	if (findTalker(pQyMc, &idInfo_grp, &hTalk) != 0) {
		iErr = -1;  
		return iErr;// goto  errLabel;
	}

	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (pProcInfo == NULL) {
		iErr = -1;  goto  errLabel;
	}

	FUNCS_for_isCliHelp* pFuncs; pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (pFuncs == NULL) {
		iErr = -1;  goto  errLabel;
	}
	
	HWND				hMgrTalk; hMgrTalk = hTalk;

	DLG_TALK_var* pDlgTalkVar; pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgrTalk, _T("dlgIa::OnBnClickedrequest"));
	if (pDlgTalkVar == nullptr) {
		iErr = -1;  goto  errLabel;
	}

	pFuncs->pf_setCurSharedObjUsr_localAv(pProcInfo, pDlgTalkVar->av.iIndex_sharedObj_localAv, pDlgTalkVar->av.iIndex_usr_localAv);


	pFuncs->pf_dlgTalk_requestToSpeak(hMgrTalk, bEnable, false);

	iErr = 0;

errLabel:
	return  iErr;
}

int applyFyOp(QY_MESSENGER_ID idInfo_grp) {
	int  iErr = -1;
	HWND  hTalk;
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	QY_MC* pQyMc = QY_GET_GBUF();

	if (findTalker(pQyMc, &idInfo_grp, &hTalk) != 0) {
		iErr = -1;  goto  errLabel;
	}

	MC_VAR_isCli* pProcInfo; pProcInfo = QY_GET_procInfo_isCli();
	if (pProcInfo == NULL) {
		iErr = -1;  goto  errLabel;
	}

	FUNCS_for_isCliHelp* pFuncs; pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (pFuncs == NULL) {
		iErr = -1;  goto  errLabel;
	}

	HWND				hMgrTalk; hMgrTalk = hTalk;

	DLG_TALK_var* pDlgTalkVar; pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgrTalk, _T("dlgIa::OnBnClickedrequest"));
	if (pDlgTalkVar == nullptr) {
		iErr = -1;  goto  errLabel;
	}

	//pFuncs->pf_setCurSharedObjUsr_localAv(pProcInfo, pDlgTalkVar->av.iIndex_sharedObj_localAv, hMgrTalk);


	pFuncs->pf_dlgTalk_requestToOp(hMgrTalk, CONST_imOp_null, false);

	iErr = 0;

errLabel:
	return  iErr;
}


int send_fy(int mainWnd_loopCtrl)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	if (!pProcInfo)  return  -1;

	if (pProcInfo->xt.bSpeak && pProcInfo->uiTerminalType == CONST_terminalType_mon && mainWnd_loopCtrl % 900 == 0) {
		QY_MESSENGER_ID idInfo_grp;
		idInfo_grp.ui64Id = pProcInfo->av.localAv.idInfo_curConference.ui64Id;
		if (applyFyOp(idInfo_grp) == 0) {
			showInfo_open0(0, _T("applyFyOp"), _T("send_fy auto apply fy op success"));
			pProcInfo->bApplyFy = true;
		}
		else {
			showInfo_open0(0, _T("applyFyOp"), _T("send_fy auto apply fy op failed"));

		}
	}

}


//
int send_xt(int mainWnd_loopCtrl)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	bool  bSkip = false;

	//
	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return  -1;


#if 0
	Param_dbg param;
	param.m_bShowInfo = false;
	if (!bChannelOk(getChannelByType(pMisCnt, 0), &param))  return  -1;
#endif

	//
	bool bNeedXtNow = false;

	//
	int intervalInS = CONST_intervalInS_xt;
	//
	intervalInS = pCtxSm->hg.systemConfig.intervalInS_xt;
	if (intervalInS <= 0 || intervalInS >= 60)  intervalInS = 30;
	//
#if 0
	if (!pProcInfo->xt.bGotOnce_xtResp) {		//  第一次时，需要尽快得到xt_resp
		intervalInS = 3;
	}
	if (!pMisCnt->dualSystem.dwConfMcuIp) {		//  这表明需要尽快得到xt_resp, 以便于确定confMcu
		//if (pMisCnt->dualSystem.dw2ndMcuIp) 
		{
			intervalInS = 3;
		}
	}
#endif
	if (pMisCnt->dualSystem.bNeedXt_ifSessionOff) {
		bNeedXtNow = true;
		pMisCnt->dualSystem.bNeedXt_ifSessionOff = false;
	}

	

	//
	if (!bNeedXtNow) {
		if ((mainWnd_loopCtrl % intervalInS)) {
			return  -1;
		}
	}


	//
	MACRO_prepareForTran();
	QIS_ca_req  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_qisCaReq;



	//  将电话告知的设备授权码+证书的唯一标识，送到会管服务器
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "[cmd=%d]", CONST_hgCmd_xt);
	char  statusBuf[128];
	_snprintf(statusBuf, mycountof(statusBuf), "%d", pProcInfo->xt.bUsrLogined);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_bUsrLogin, strlen(statusBuf), statusBuf);

	char  ukeyStatusBuf[128];
	_snprintf(ukeyStatusBuf, mycountof(ukeyStatusBuf), "%d", pProcInfo->xt.bUsrUkeyed);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_bUsrUkey, strlen(ukeyStatusBuf), ukeyStatusBuf);
	char  videoStatusBuf[128];

#ifdef  __DEBUG__
	pProcInfo->xt.bVideoDevOk = true;
#endif


	_snprintf(videoStatusBuf, mycountof(videoStatusBuf), "%d", pProcInfo->xt.bVideoDevOk);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_bUsrVideo, strlen(videoStatusBuf), videoStatusBuf);
	char  audioStatusBuf[128];
	_snprintf(audioStatusBuf, mycountof(audioStatusBuf), "%d", pProcInfo->xt.bAudioDevOk);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_bUsrAudio, strlen(audioStatusBuf), audioStatusBuf);

	char  speakStatusBuf[128];
	_snprintf(speakStatusBuf, mycountof(speakStatusBuf), "%d", pProcInfo->xt.bSpeak);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_bSpeak, strlen(speakStatusBuf), speakStatusBuf);

	char  curConfBuf[128];
	_snprintf(curConfBuf, mycountof(curConfBuf), "%I64u", pProcInfo->av.localAv.idInfo_curConference.ui64Id);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_curConf, strlen(curConfBuf), curConfBuf);


	char buf_terminalType[10];
	safeStrnCpy(_ltoa(pProcInfo->uiTerminalType, buf_terminalType, 10), buf_terminalType, mycountof(buf_terminalType));

	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_terminal_type, strlen(buf_terminalType), buf_terminalType);




	//
#ifdef  __DEBUG__
#endif

	//
	req.ca_cliDataLen = strlen(req.ca_cliData);

	//
	int len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);

	//
	pProcInfo->xt.nTimes_waitForXtResp++;

	//
	TCHAR  tBuf[128];
	_sntprintf(tBuf, mycountof(tBuf), (TCHAR*)_T("send_xt, nTimes_waitForXtResp %d"), pProcInfo->xt.nTimes_waitForXtResp);
	showInfo_open0(0, 0, tBuf);

	send_showInfo(0);

	//
	return  0;

}


//
int send_showInfo(int mainWnd_loopCtrl)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	bool  bSkip = false;

	//
	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return  -1;

	//
	if (!pQyMc->bLogon)  return  -1;


#if 0
	Param_dbg param;
	param.m_bShowInfo = false;
	if (!bChannelOk(getChannelByType(pMisCnt, 0), &param))  return  -1;
#endif


	//
	MACRO_prepareForTran();
	QIS_ca_req  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_qisCaReq;

	req.sHgCmd = CONST_hgCmd_showInfo;


	//  将电话告知的设备授权码+证书的唯一标识，送到会管服务器
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "[cmd=%d]", CONST_hgCmd_showInfo);
	/*
	char  statusBuf[128];
	_snprintf(statusBuf, mycountof(statusBuf), "%d", pProcInfo->xt.bUsrLogined);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_bUsrLogin, strlen(statusBuf), statusBuf);

	char  ukeyStatusBuf[128];
	_snprintf(ukeyStatusBuf, mycountof(ukeyStatusBuf), "%d", pProcInfo->xt.bUsrUkeyed);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_bUsrUkey, strlen(ukeyStatusBuf), ukeyStatusBuf);
	char  videoStatusBuf[128];



	_snprintf(videoStatusBuf, mycountof(videoStatusBuf), "%d", pProcInfo->xt.bVideoDevOk);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_bUsrVideo, strlen(videoStatusBuf), videoStatusBuf);
	char  audioStatusBuf[128];
	_snprintf(audioStatusBuf, mycountof(audioStatusBuf), "%d", pProcInfo->xt.bAudioDevOk);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_bUsrAudio, strlen(audioStatusBuf), audioStatusBuf);

	char  speakStatusBuf[128];
	_snprintf(speakStatusBuf, mycountof(speakStatusBuf), "%d", pProcInfo->xt.bSpeak);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_bSpeak, strlen(speakStatusBuf), speakStatusBuf);

	char  curConfBuf[128];
	_snprintf(curConfBuf, mycountof(curConfBuf), "%I64u", pProcInfo->av.localAv.idInfo_curConference.ui64Id);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_curConf, strlen(curConfBuf), curConfBuf);

	*/
	//
#ifdef  __DEBUG__
#endif

	//
	req.ca_cliDataLen = strlen(req.ca_cliData);

	//
	int len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);
	//pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);
	//pProcInfo->xt.nTimes_waitForXtResp++;

	//
	TCHAR  tBuf[128];
	_sntprintf(tBuf, mycountof(tBuf), (TCHAR*)_T("send_xt, nTimes_waitForXtResp %d"), pProcInfo->xt.nTimes_waitForXtResp);
	showInfo_open0(0, 0, tBuf);

	//
	return  0;

}


//






//
int  startToRetrievePlans()
{
		CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
		MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
		char respBuf[1024] = "";


		//

		_snprintf(respBuf, mycountof(respBuf), "[msgr=%I64u]", pMisCnt->idInfo.ui64Id);
		//_snprintf(respBuf, mycountof(respBuf), "%s [rc=%d] [org=%d]", respBuf, respCode, (int)org_cmd);
		_snprintf(respBuf, mycountof(respBuf), "%s [cmd=%d]", respBuf, CONST_hgCmd_retrievePlans);
		//


		//					
		//
		MACRO_prepareForTran();
		QIS_ca_req  req;

		//
		memset(&req, 0, sizeof(req));
		req.uiType = CONST_imCommType_qisCaReq;

		//
		_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s", respBuf);
		//
#ifdef  __DEBUG__
							//_snprintf(req.sxrz_cliData, mycountof(req.sxrz_cliData), "%s [obj=%d len=%d]%s", req.sxrz_cliData, CONST_sxrz_serv_random,  strlen(pVc->sxrz.serv.param_sxrz_servReply.serv_random), pVc->sxrz.serv.param_sxrz_servReply.serv_random);
#endif
							//
		req.ca_cliDataLen = strlen(req.ca_cliData);



		//
		int len = sizeof(req);
		pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);




		//
		return  0;
	
}




//
int  startToRetrieveP2pList()
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	char respBuf[1024] = "";


	//
	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return  -1;
	pCtxSm->hg.bDone_p2p = false;



	//

	_snprintf(respBuf, mycountof(respBuf), "[msgr=%I64u]", pMisCnt->idInfo.ui64Id);
	//_snprintf(respBuf, mycountof(respBuf), "%s [rc=%d] [org=%d]", respBuf, respCode, (int)org_cmd);
	_snprintf(respBuf, mycountof(respBuf), "%s [cmd=%d]", respBuf, CONST_hgCmd_retrieveP2pList);
	//


	//					
	//
	MACRO_prepareForTran();
	QIS_ca_req  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_qisCaReq;

	//
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s", respBuf);
	//
#ifdef  __DEBUG__
							//_snprintf(req.sxrz_cliData, mycountof(req.sxrz_cliData), "%s [obj=%d len=%d]%s", req.sxrz_cliData, CONST_sxrz_serv_random,  strlen(pVc->sxrz.serv.param_sxrz_servReply.serv_random), pVc->sxrz.serv.param_sxrz_servReply.serv_random);
#endif
							//
	req.ca_cliDataLen = strlen(req.ca_cliData);

	//
	int len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);




	//
	return  0;

}


//
int  askforP2p(TCHAR * fromTermName , unsigned  __int64 grpId, TCHAR * peerTermName ,unsigned  __int64  peerId ,int p2pLevel)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	char respBuf[1024] = "";


	//
	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return  -1;
	pCtxSm->hg.bDone_p2p = false;



	//

	_snprintf(respBuf, mycountof(respBuf), "[msgr=%I64u]", pMisCnt->idInfo.ui64Id);
	//_snprintf(respBuf, mycountof(respBuf), "%s [rc=%d] [org=%d]", respBuf, respCode, (int)org_cmd);
	_snprintf(respBuf, mycountof(respBuf), "%s [cmd=%d]", respBuf, CONST_hgCmd_askforP2p);
	//


	//					
	//
	MACRO_prepareForTran();
	QIS_ca_req  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_qisCaReq;

	//
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s", respBuf);
	//
#ifdef  __DEBUG__
							//_snprintf(req.sxrz_cliData, mycountof(req.sxrz_cliData), "%s [obj=%d len=%d]%s", req.sxrz_cliData, CONST_sxrz_serv_random,  strlen(pVc->sxrz.serv.param_sxrz_servReply.serv_random), pVc->sxrz.serv.param_sxrz_servReply.serv_random);
#endif
							
	char  grpIdBuf[128];
	_snprintf(grpIdBuf, mycountof(grpIdBuf), "%I64u", grpId);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_grpIdInfo, strlen(grpIdBuf), grpIdBuf);


	char  peerIdBuf[128];
	_snprintf(peerIdBuf, mycountof(peerIdBuf), "%I64u", peerId);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_peerId, strlen(peerIdBuf), peerIdBuf);


	char  fromTemNameBuf[128];
	
	myTChar2Utf8(fromTermName, fromTemNameBuf, mycountof(fromTemNameBuf));
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_fromTermName, strlen(fromTemNameBuf), fromTemNameBuf);

	char  peerTemNameBuf[128];

	myTChar2Utf8(peerTermName, peerTemNameBuf, mycountof(peerTemNameBuf));
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_peerTermName, strlen(peerTemNameBuf), peerTemNameBuf);

	char  p2pLevelBuf[128];
	_snprintf(p2pLevelBuf, mycountof(p2pLevelBuf), "%d", p2pLevel);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_meeting_level, strlen(p2pLevelBuf), p2pLevelBuf);


	req.ca_cliDataLen = strlen(req.ca_cliData);


	//
	int len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);

	//
	return  0;

}


//
int  askforP2p_do()
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	char respBuf[1024] = "";


	//
	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return  -1;
	pCtxSm->hg.bDone_p2p = false;



	//

	_snprintf(respBuf, mycountof(respBuf), "[msgr=%I64u]", pMisCnt->idInfo.ui64Id);
	//_snprintf(respBuf, mycountof(respBuf), "%s [rc=%d] [org=%d]", respBuf, respCode, (int)org_cmd);
	_snprintf(respBuf, mycountof(respBuf), "%s [cmd=%d]", respBuf, CONST_hgCmd_askforP2p_do);
	//


	//					
	//
	MACRO_prepareForTran();
	QIS_ca_req  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_qisCaReq;

	//
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s", respBuf);
	//
#ifdef  __DEBUG__
							//_snprintf(req.sxrz_cliData, mycountof(req.sxrz_cliData), "%s [obj=%d len=%d]%s", req.sxrz_cliData, CONST_sxrz_serv_random,  strlen(pVc->sxrz.serv.param_sxrz_servReply.serv_random), pVc->sxrz.serv.param_sxrz_servReply.serv_random);
#endif

	char  grpIdBuf[128];
	_snprintf(grpIdBuf, mycountof(grpIdBuf), "%I64u", pCtxSm->hg.p2pMsg.idInfo_grp);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_grpIdInfo, strlen(grpIdBuf), grpIdBuf);

	char  p2pLevelBuf[128];
	_snprintf(p2pLevelBuf, mycountof(p2pLevelBuf), "%d", pCtxSm->hg.p2pMsg.p2pLevel);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_meeting_level, strlen(p2pLevelBuf), p2pLevelBuf);


	//char  peerTemNameBuf[128];
	//myTChar2Utf8(pCtxSm->hg.p2pMsg.formTermName, peerTemNameBuf, mycountof(peerTemNameBuf));
	//_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_peerTermName, strlen(peerTemNameBuf), peerTemNameBuf);

	req.ca_cliDataLen = strlen(req.ca_cliData);


	//
	int len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);

	//
	return  0;

}


//询问会管入会是否合法
int	legal_initiation(unsigned  __int64 grpId) {
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	char respBuf[1024] = "";


	//
	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return  -1;


	//

	_snprintf(respBuf, mycountof(respBuf), "[msgr=%I64u]", pMisCnt->idInfo.ui64Id);
	//_snprintf(respBuf, mycountof(respBuf), "%s [rc=%d] [org=%d]", respBuf, respCode, (int)org_cmd);
	_snprintf(respBuf, mycountof(respBuf), "%s [cmd=%d]", respBuf, CONST_hgCmd_legal);
	
	//

	MACRO_prepareForTran();
	QIS_ca_req  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_qisCaReq;

	//
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s", respBuf);
	//
#ifdef  __DEBUG__
							//_snprintf(req.sxrz_cliData, mycountof(req.sxrz_cliData), "%s [obj=%d len=%d]%s", req.sxrz_cliData, CONST_sxrz_serv_random,  strlen(pVc->sxrz.serv.param_sxrz_servReply.serv_random), pVc->sxrz.serv.param_sxrz_servReply.serv_random);
#endif

	char  grpIdBuf[128];
	_snprintf(grpIdBuf, mycountof(grpIdBuf), "%I64u", grpId);
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_grpIdInfo, strlen(grpIdBuf), grpIdBuf);



	req.ca_cliDataLen = strlen(req.ca_cliData);


	//
	int len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);


	//
	return 0;
}
