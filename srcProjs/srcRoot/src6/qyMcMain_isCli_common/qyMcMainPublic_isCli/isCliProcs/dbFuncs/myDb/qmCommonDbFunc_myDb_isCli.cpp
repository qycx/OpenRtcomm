

#include	"stdafx.h"

#include	<stddef.h>
#include	<stdio.h>

//#include	<afxcmn.h>
#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
#include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>

#include	"qyMcMainCommon.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	"qyCusResTemp.h"		//  2013/02/17

//  #include	"qwmDynFunc.h"

#include	"qmcCmdProc.h"

#include	"tmpCeLib.h"
#include	"qySqlFunc.h"

#include	"myresource.h"
#include	"myDb.h"
#include	"qyOpenShellCommon.h"
//#include	"DlgObjs_ts.h"
#include	"dlgobjsproc.h"
#include	"dlgtalkproc.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"qmcCommFunc_isCli.h"
//
#include	"ctxMcThread.h"

//
__declspec(dllexport)  MIS_MSG_TASK* taskRcd2Msg(void* pMisCntParam, IM_TASK_RCD* pRcd, MIS_MSG_TASK* pMsg)
{
	int						iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MIS_CNT* pMisCnt = (MIS_CNT*)pMisCntParam;
	IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->data.buf;
	int						iDbType = pQyMc->cfg.db.iDbType;
	//	
	char					idStr_send[CONST_qyMessengerIdStrLen + 1] = "";
	char					idStr_recv[CONST_qyMessengerIdStrLen + 1] = "";
	char					sendTime[CONST_qyTimeLen + 1] = "";
	char					recvTime[CONST_qyTimeLen + 1] = "";
	char					endTime[CONST_qyTimeLen + 1] = "";
	char					lastModifiedTime[CONST_qyTimeLen + 1] = "";
	char					lastModifiedTime_req[CONST_qyTimeLen + 1] = "";
	//  CDBVariant				varVals[5];
	int						iTaskId = 0;
	TCHAR* pT;
	char					buf[255 + 1] = "";

	if (!pMisCnt || !pRcd || !pMsg)  return  NULL;

	MACRO_memset_misMsgTask(pMsg);

	pMsg->uiType = CONST_misMsgType_task;

	pMsg->pMisCnt = pMisCnt;
	//
	pMsg->usCode = pRcd->ibReply ? CONST_qyCmd_sendTask : CONST_qyCmd_sendTaskReply;

	pMsg->tStartTime = pRcd->tSendTime;
	pMsg->uiTranNo = pRcd->uiTranNo;

	pMsg->iTaskId = pRcd->id;			//  ×¢Òâ£¬ÕâÀïÒª°ÑÁ½¸öÄÚ²¿´¦Àí±äÁ¿¸³ÉÏ
	pMsg->uiTaskMode_unused = pRcd->uiMode;
	pMsg->uiTaskType = pRcd->uiType;
	pMsg->iStatus = pRcd->iStatus;

	//
	pMsg->idInfo_taskReceiver.ui64Id = pRcd->idInfo_recv.ui64Id;
	pMsg->idInfo_taskSender.ui64Id = pRcd->idInfo_send.ui64Id;

	switch (pRcd->uiContentType) {
	case  CONST_imCommType_transferFileReq:

		if (pRcd->uiType == CONST_imTaskType_recvFile) {				//  ÒòÎªÕâ¸ö×ª»»Ö÷ÒªÎªÏó¶Ô·½·¢ËÍÎªÖ÷
			pMsg->data.route.idInfo_from.ui64Id = pMsg->idInfo_taskReceiver.ui64Id;
			pMsg->data.route.idInfo_to.ui64Id = pMsg->idInfo_taskSender.ui64Id;
		}
		else  if (pRcd->uiType == CONST_imTaskType_sendFile) {
			pMsg->data.route.idInfo_from.ui64Id = pMsg->idInfo_taskSender.ui64Id;
			pMsg->data.route.idInfo_to.ui64Id = pMsg->idInfo_taskReceiver.ui64Id;
		}
		else {
			traceLogA("taskRcd2Msg: fileReq, taskType error");
			goto  errLabel;
		}

		pMsg->usCode = CONST_qyCmd_sendRobotTask;
		pMsg->uiChannelType = CONST_channelType_robot;						//  2008/05/30

		memset(&pContent->transferFileReq, 0, sizeof(pContent->transferFileReq));
		pContent->transferFileReq.uiType = CONST_imCommType_transferFileReq;

		lstrcpyn(pContent->transferFileReq.fileName, pRcd->subject, mycountof(pContent->transferFileReq.fileName));
		lstrcpyn(pContent->transferFileReq.fullFilePath, pRcd->content, mycountof(pContent->transferFileReq.fullFilePath));
		//
		pContent->transferFileReq.ui64FileLen = _tcstol(pRcd->propStrs[0], &pT, 10);

		pMsg->lenInBytes = offsetof(MIS_MSG_routeTalkData, buf) + sizeof(pContent->transferFileReq);		//  2009/10/17

		break;
	case  CONST_imCommType_rtcCallReq:
		traceLogA("rtc not supported");
		break;
	case  CONST_imCommType_transferAvInfo:

		if (pRcd->iStatus == CONST_imTaskStatus_resp) {
			pMsg->data.route.idInfo_from.ui64Id = pMsg->idInfo_taskReceiver.ui64Id;
			pMsg->data.route.idInfo_to.ui64Id = pMsg->idInfo_taskSender.ui64Id;
		}
		else  if (pRcd->iStatus == CONST_imTaskStatus_req) {
			pMsg->data.route.idInfo_from.ui64Id = pMsg->idInfo_taskSender.ui64Id;
			pMsg->data.route.idInfo_to.ui64Id = pMsg->idInfo_taskReceiver.ui64Id;
		}
		else {
			traceLogA("taskRcd2Msg: avInfo, iStatus error");
			//  goto  errLabel;						
		}

		pMsg->usCode = CONST_qyCmd_sendMedia;
		pMsg->uiChannelType = CONST_channelType_media;						//  2008/05/30

		memset(&pContent->transferAvInfo, 0, sizeof(pContent->transferAvInfo));
		pContent->transferAvInfo.uiType = CONST_imCommType_transferAvInfo;

		pMsg->lenInBytes = offsetof(MIS_MSG_routeTalkData, buf) + sizeof(pContent->transferAvInfo);		//  2009/10/17

		break;
	case  CONST_imCommType_transferGpsInfo:		//  2012/04/20

#if  10
		if (pRcd->iStatus == CONST_imTaskStatus_resp) {
			pMsg->data.route.idInfo_from.ui64Id = pMsg->idInfo_taskReceiver.ui64Id;
			pMsg->data.route.idInfo_to.ui64Id = pMsg->idInfo_taskSender.ui64Id;
		}
		else  if (pRcd->iStatus == CONST_imTaskStatus_req) {
			pMsg->data.route.idInfo_from.ui64Id = pMsg->idInfo_taskSender.ui64Id;
			pMsg->data.route.idInfo_to.ui64Id = pMsg->idInfo_taskReceiver.ui64Id;
		}
		else {
			traceLogA("taskRcd2Msg: gpsInfo, iStatus error");
			//  goto  errLabel;						
		}

		pMsg->usCode = CONST_qyCmd_sendMedia;
		pMsg->uiChannelType = CONST_channelType_media;						//  2008/05/30

		memset(&pContent->transferGpsInfo, 0, sizeof(pContent->transferGpsInfo));
		pContent->transferGpsInfo.uiType = CONST_imCommType_transferGpsInfo;

		pMsg->lenInBytes = offsetof(MIS_MSG_routeTalkData, buf) + sizeof(pContent->transferGpsInfo);		//  2009/10/17
#endif

		break;
	default:
		traceLog(_T("taskRcd2Msg failed, : unprocessed pRcd->uiContentType %d"), pRcd->uiContentType);
		goto  errLabel;
		break;
	}

	iErr = 0;
errLabel:
	return  iErr ? NULL : pMsg;

}



int  tmpHandler_bNeedRetrieveImGrpMems_myDb(void* p0, void* p1, void* p2)
{
	int	iErr = -1;
	//  p0
	//  p1
	QMEM_qyImObj* pMem = (QMEM_qyImObj*)p2;

	if (pMem->messengerInfo.uiType == CONST_objType_imGrp
		&& pMem->messengerInfo.iStatus != CONST_qyStatus_del)
	{
		iErr = 1;  goto  errLabel;
	}

	iErr = 0;
errLabel:
	return  iErr;
}

BOOL	bNeedRetrieveImGrpMems_myDb(void* pDbParam, int  iDbType, LPCTSTR  misServName)
{
	BOOL	bRet = FALSE;
	CMyDb* pDb = (CMyDb*)pDbParam;

#if  0
#ifndef  __NOTSUPPORT_DB__
	TCHAR								sqlBuf[1024];

	_sntprintf(sqlBuf, mycountof(sqlBuf), _T("select count(A.idStr) from qyImObjTab as A where A.misServName=%s and A.uiType in (%d) and A.iStatus<>%d"), getDbValStr(iDbType, CONST_iDataType_misServName, misServName), CONST_objType_imGrp, CONST_qyStatus_del);
	OutputDebugString(sqlBuf);  OutputDebugString(_T("\n"));
	if (bSqlObjExists(pDb, sqlBuf))  bRet = TRUE;
#else
	//  暂时在ce里不考虑处理分组成员信息
#endif
#endif

	BOOL	bImGrpExists = FALSE;
	if (qTraverse(pDb->m_var.pQ_qyImObjTab, tmpHandler_bNeedRetrieveImGrpMems_myDb, 0, 0) > 0)  bRet = TRUE;

	return  bRet;
}


int  deleteOldImObjRule_mcProcResp_refreshImObjRulesReq_myDb(void* pSubThreadInfoParam, void* pSciParam, void* pMisCntParam, MIS_MSG_INPUT* pMsgInput, void* pCtxParam)
{
	return  0;
}

int  tmpHandle_selectImObjRule_mcProcResp_refreshImObjRulesReq_myDb(void* p0, void* p1, void* p2)
{
	int								iErr = -1;
	QY_MESSENGER_ID* pIdInfo = (QY_MESSENGER_ID*)p0;
	//  p1
	REFRESH_imObjRule_reqMem* pQMem = (REFRESH_imObjRule_reqMem*)p2;
	//
#if  0
	MIS_MSG_INPUT* pMsgInput = (MIS_MSG_INPUT*)p1;
	IM_CONTENTU* pContent = NULL;
	int								i = 0, n = 0;
	pContent = M_getMsgContent(pMsgInput->ucFlg, &pMsgInput->data);
	n = pContent->refreshImObjRulesReq.usCnt;
#endif

	if (pQMem->idInfo_related.ui64Id > pIdInfo->ui64Id) {

		pIdInfo->ui64Id = pQMem->idInfo_related.ui64Id;
		iErr = 1;  goto  errLabel;

	}

	iErr = 0;

errLabel:
	return  iErr;

}

int  selectNextImObjRule_mcProcResp_refreshImObjRulesReq_myDb(void* pSubThreadInfoParam, void* pSciParam, void* pMisCntParam, MIS_MSG_INPUT* pMsgInput, void* pCtxParam, QY_MESSENGER_ID* pIdInfo_related)
{
	int								iErr = -1;
	MT_SUBTHREADINFO* pSubThreadInfo = (MT_SUBTHREADINFO*)pSubThreadInfoParam;
	QY_SERVICEGUI_INFO* pSci = (QY_SERVICEGUI_INFO*)pSciParam;
	MIS_CNT* pMisCnt = (MIS_CNT*)pMisCntParam;
	CTX_MC_scheduler* pCtx = (CTX_MC_scheduler*)pCtxParam;


	CMyDb* pMyDb = (CMyDb*)pSubThreadInfo->pDb;

	if (qTraverse(pMyDb->m_var.pQ_qyImObjRuleTab, tmpHandle_selectImObjRule_mcProcResp_refreshImObjRulesReq_myDb, pIdInfo_related, pMsgInput) <= 0)  goto  errLabel;

#if 0
	TCHAR								sqlBuf[CONST_maxSqlBufLen + 1] = _T("");
	char								timeBuf[128] = "";
	char								idStr[CONST_qyMessengerIdStrLen + 1];

	TCHAR								tBuf[255 + 1] = _T("");
	//
	int								len;
	//
	int								tmpiRet;
	//  
	CDBVariant							varVals[1];
	QY_MESSENGER_ID					idInfo_tmp;


	idInfo2Str(&idInfo_related, idStr, mycountof(idStr));
	_sntprintf(sqlBuf, mycountof(sqlBuf), _T("select idStr_related from %s where idStr_related>'%s' order by idStr_related"), CONST_tabName_qyImObjRuleTab, CString(idStr));
	if (!bQyGetRcdBySql(pSubThreadInfo->pDb, sqlBuf, mycountof(varVals), varVals))  goto  errLabel;
	MACRO_sqlStr(varVals[0], tBuf, mycountof(tBuf));  myTChar2Utf8(tBuf, idStr, mycountof(idStr));  idStr2Info(idStr, &idInfo_tmp);
	if (idInfo_tmp.ui64Id == idInfo_related.ui64Id) {
		//  err
		goto  errLabel;
	}
	idInfo_related.ui64Id = idInfo_tmp.ui64Id;
#endif

	iErr = 0;

errLabel:
	return  iErr;
}


int  tmpHandle_selectImTask_storeTaskInDb_myDb(void* p0, void* p1, void* p2)
{
	int  iRet = -1;

	//  p0
	IM_TASK_RCD* pRcd = (IM_TASK_RCD*)p1;
	IM_TASK_RCD* pQMem = (IM_TASK_RCD*)p2;

	//  2015/09/09
	//  在视频任务被自动中断，然后自动恢复时，初始的idInfo_recv可能是分组，但是后续重发的idInfo_recv是个人，所以，这里不能用idInfo_recv当判断任务的条件

	//
	if (pQMem->idInfo_send.ui64Id == pRcd->idInfo_send.ui64Id
		//&&  pQMem->idInfo_recv.ui64Id  ==  pRcd->idInfo_recv.ui64Id	//  2015/09/09. 
		&& pQMem->tSendTime == pRcd->tSendTime
		&& pQMem->uiTranNo == pRcd->uiTranNo)
	{
		pRcd->id = pQMem->id;
		pRcd->iStatus = pQMem->iStatus;

		iRet = 1;		goto  errLabel;
	}

	iRet = 0;
errLabel:
	return  iRet;
}

BOOL  bSelectImTask_storeTaskInDb_myDb(void* pDb, int  iDbType, void* pMisCntParam, IM_TASK_RCD* pRcd, BOOL  bInHis)
{
	BOOL					bRet = FALSE;
	CMyDb* pMyDb = (CMyDb*)pDb;

	if (bInHis)  goto  errLabel;

	if (qTraverse(pMyDb->m_var.pQ_qyImTaskTab, tmpHandle_selectImTask_storeTaskInDb_myDb, NULL, pRcd) <= 0)  goto  errLabel;

#if  0
	QY_MC* pQyMc = QY_GET_GBUF();
	MIS_CNT* pMisCnt = (MIS_CNT*)pMisCntParam;
	//
	TCHAR					sqlBuf[CONST_maxSqlBufLen + 1];
	char					idStr_send[CONST_qyMessengerIdStrLen + 1] = "";
	char					idStr_recv[CONST_qyMessengerIdStrLen + 1] = "";
	char					sendTime[CONST_qyTimeLen + 1] = "";
#if  0
	char					recvTime[CONST_qyTimeLen + 1] = "";
	char					tStartTime_serv[CONST_qyTimeLen + 1] = "";
	char					endTime[CONST_qyTimeLen + 1] = "";
	char					firstTime[CONST_qyTimeLen + 1] = "";
	char					lastTime[CONST_qyTimeLen + 1] = "";
	char					lastModifiedTime[CONST_qyTimeLen + 1] = "";
	char					lastModifiedTime_req[CONST_qyTimeLen + 1] = "";
	CQySyncObj				syncObj;
#endif
	CDBVariant				varVals[5];
	TCHAR* pTabName = bInHis ? CONST_tabName_qyImTaskHisTab : CONST_tabName_qyImTaskTab;


	if (!idInfo2Str(&pRcd->idInfo_send, idStr_send, mycountof(idStr_send)))  goto  errLabel;
	if (!idInfo2Str(&pRcd->idInfo_recv, idStr_recv, mycountof(idStr_recv)))  goto  errLabel;
	if (pRcd->tSendTime)  getTimeStr(pRcd->tSendTime, sendTime, mycountof(sendTime));
#if  0
	if (pRcd->tRecvTime)  getTimeStr(pRcd->tRecvTime, recvTime, mycountof(recvTime));
	if (pRcd->tEndTime)  getTimeStr(pRcd->tEndTime, endTime, mycountof(endTime));
	if (pRcd->tLastModifiedTime)  getTimeStr(pRcd->tLastModifiedTime, lastModifiedTime, mycountof(lastModifiedTime));
#endif


	//  +misServName;+idStr_send;+tSendTime;+uiTranNo;+idStr_recv
	_sntprintf(sqlBuf, mycountof(sqlBuf), _T("select id,iStatus from %s where misServName=%s and idStr_send='%s' and tSendTime='%s' and uiTranNo=%d and uiSerialNo=%d and idStr_recv='%s'"),
		pTabName,
		getDbValStr(iDbType, CONST_iDataType_misServName, pRcd->misServName),
		CString(idStr_send),
		CString(sendTime),
		pRcd->uiTranNo,
		pRcd->uiSerialNo,
		CString(idStr_recv));
	if (bQyGetRcdBySql(pDb, sqlBuf, mycountof(varVals), varVals)) {
		traceLogA("storeTaskInDb: ");
		MACRO_sqlLong(varVals[0], pRcd->id);		//  
		MACRO_sqlLong(varVals[1], pRcd->iStatus);
		iErr = 1;  goto  errLabel;
	}

#endif
	bRet = TRUE;
errLabel:

	return  bRet;
}




int  insertImTask_storeTaskInDb_myDb(void* pDb, int  iDbType, void* pMisCntParam, int  iTaskId_suggested, IM_TASK_RCD* pRcd, BOOL  bInHis)
{
	int						iErr = -1;
	CMyDb* pMyDb = (CMyDb*)pDb;

	if (bInHis)  return  0;
	if (!pRcd)  return  -1;

	//  2013/02/05
	if (iTaskId_suggested)  pRcd->id = iTaskId_suggested;
	else {
		//  pRcd->id  =  getuiNextTranNo(  0,  0,  0  );
		pRcd->id = newTaskId(pDb, iDbType);
	}

	//
	if (qPostMsg(pRcd, sizeof(pRcd[0]), pMyDb->m_var.pQ_qyImTaskTab,_T(  "insertImTask_storeTaskInDb"  )))  goto  errLabel;


#if  0
	QY_MC* pQyMc = QY_GET_GBUF();
	MIS_CNT* pMisCnt = (MIS_CNT*)pMisCntParam;
	//
	TCHAR					sqlBuf[CONST_maxSqlBufLen + 1];
	char					idStr_send[CONST_qyMessengerIdStrLen + 1] = "";
	char					idStr_recv[CONST_qyMessengerIdStrLen + 1] = "";
	char					sendTime[CONST_qyTimeLen + 1] = "";
	//
	char					recvTime[CONST_qyTimeLen + 1] = "";
	char					tStartTime_serv[CONST_qyTimeLen + 1] = "";
	char					endTime[CONST_qyTimeLen + 1] = "";
	char					firstTime[CONST_qyTimeLen + 1] = "";
	char					lastTime[CONST_qyTimeLen + 1] = "";
	char					lastModifiedTime[CONST_qyTimeLen + 1] = "";
	char					lastModifiedTime_req[CONST_qyTimeLen + 1] = "";

	CDBVariant				varVals[5];
	TCHAR* pTabName = bInHis ? CONST_tabName_qyImTaskHisTab : CONST_tabName_qyImTaskTab;

	if (!idInfo2Str(&pRcd->idInfo_send, idStr_send, mycountof(idStr_send)))  goto  errLabel;
	if (!idInfo2Str(&pRcd->idInfo_recv, idStr_recv, mycountof(idStr_recv)))  goto  errLabel;
	if (pRcd->tSendTime)  getTimeStr(pRcd->tSendTime, sendTime, mycountof(sendTime));
	if (pRcd->tRecvTime)  getTimeStr(pRcd->tRecvTime, recvTime, mycountof(recvTime));
	if (pRcd->tEndTime)  getTimeStr(pRcd->tEndTime, endTime, mycountof(endTime));
	if (pRcd->tLastModifiedTime)  getTimeStr(pRcd->tLastModifiedTime, lastModifiedTime, mycountof(lastModifiedTime));

	getTimeStr(pRcd->tStartTime_serv, tStartTime_serv, mycountof(tStartTime_serv));
	getTimeStr(pRcd->firstTime, firstTime, mycountof(firstTime));
	getTimeStr(pRcd->lastTime, lastTime, mycountof(lastTime));


	_sntprintf(sqlBuf, mycountof(sqlBuf), _T("insert into %s(misServName,idStr_send,senderDesc,tSendTime,uiTranNo,uiSeqNo,uiContentType,tStartTime_serv,uiSerialNo,idStr_recv,receiverDesc,iRole,tRecvTime,usRespCode,ibReply,uiType,uiMode,subTypeStr,subject,content0,ibNeedReply,tEndTime,firstTime,lastTime,iStatus,tLastModifiedTime,propStr0)")
		_T(" values(%s,        '%s',        %s,     '%s',     %d,        %d,     %d,          '%s',         %d,       '%s',       %s,        %d,     '%s',   %d,        %d,       %d,   %d,     %s,          %s,     %s,    %d,          '%s',   '%s',     '%s',     %d,     '%s',             '%s')"),
		pTabName,
		getDbValStr(iDbType, CONST_iDataType_misServName, pRcd->misServName),
		CString(idStr_send),
		getDbValStr(iDbType, CONST_iDataType_desc, pRcd->senderDesc),
		CString(sendTime),
		pRcd->uiTranNo,
		(int)pRcd->usSeqNo,
		pRcd->uiContentType,
		CString(tStartTime_serv),
		pRcd->uiSerialNo,
		CString(idStr_recv),
		getDbValStr(iDbType, CONST_iDataType_desc, pRcd->receiverDesc),
		pRcd->iRole,
		CString(recvTime),
		pRcd->usRespCode,
		pRcd->ibReply,
		pRcd->uiType,
		pRcd->uiMode,
		getDbValStr(iDbType, CONST_iDataType_subTypeStr, pRcd->subTypeStr),
		getDbValStr(iDbType, CONST_iDataType_subject, pRcd->subject),
		getDbValStr(iDbType, CONST_iDataType_content, pRcd->content),
		pRcd->ibNeedReply,
		CString(endTime),
		CString(firstTime),
		CString(lastTime),
		pRcd->iStatus,
		CString(lastModifiedTime),
		CString(pRcd->propStrs[0]));


	if (!bQyExecSql(pDb, sqlBuf))  goto  errLabel;
#endif
	iErr = 0;
errLabel:
	return  iErr;
}


int  tmpHandler_updateTaskStatus_myDb(void* p0, void* p1, void* p2)
{
	int  iRet = -1;

	int    iStatus = (int)p0;
	int    iTaskId = (int)p1;
	IM_TASK_RCD* pQMem = (IM_TASK_RCD*)p2;

	if (pQMem->id == iTaskId) {
		pQMem->iStatus = iStatus;
		//  2014/05/01
		mytime(&pQMem->tLastModifiedTime);
		//
		iRet = 1;  goto  errLabel;
	}

	iRet = 0;
errLabel:

	return  iRet;
}

//  2013/02/05
int  updateTaskStatus_myDb(void* pDb, int  iStatus, int  iTaskId)
{
	int			iErr = -1;
	CMyDb* pMyDb = (CMyDb*)pDb;

	if (qTraverse(pMyDb->m_var.pQ_qyImTaskTab, tmpHandler_updateTaskStatus_myDb, (void*)iStatus, (void*)iTaskId) < 0)  goto  errLabel;

#if  0
#ifdef  __NOTSUPPORT_DB__
	int			iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	QY_SERVICEGUI_INFO* pSci = NULL;
	pSci = getServiceGuiInfo(pQyMc, pQyMc->iServiceId);
	if (!pSci)  goto  errLabel;
	MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pSci->pVar;
	if (!pProcInfo)  goto  errLabel;

	int				tmpiRet = -1;

	tmpiRet = qTraverse(&pProcInfo->memTaskQ, (PF_commonHandler)tmpHandler_updateTaskStatus, (void*)iStatus, (void*)iTaskId);
	if (tmpiRet < 0)  goto  errLabel;
	iErr = 0;
errLabel:
	return  iErr;
#else
	TCHAR		sqlBuf[CONST_maxSqlBufLen + 1] = _T("");

	if (!pDb)  return  -1;

	_sntprintf(sqlBuf, mycountof(sqlBuf), _T("update %s set iStatus=%d where id=%d"), CONST_tabName_qyImTaskTab, iStatus, iTaskId);

	if (!bQyExecSql(pDb, sqlBuf))  return  -1;
	return  0;
#endif

#endif

	iErr = 0;
errLabel:

	return  iErr;
}



BOOL  bMoveTask2His_myDb(void* pMisCntParam, void* pDb, int  iDbType)
{
	return  FALSE;
}

BOOL  bClearupDeletedImObjs_isClient_myDb(void* pMisCntParam, void* pDb, int  iDbType)
{
	return  FALSE;
}


int  tmpHandle_bGetImTaskRcdBySth_myDb(void* p0, void* p1, void* p2)
{
	int  iRet = -1;

	COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
	//
	QY_MESSENGER_ID* pIdInfo = (QY_MESSENGER_ID*)pCommonParam->p0;
	unsigned int        uiTranNo = (unsigned int)pCommonParam->p1;
	int			     id = (int)pCommonParam->p2;
	//
	IM_TASK_RCD* pRcd = (IM_TASK_RCD*)p1;
	IM_TASK_RCD* pQMem = (IM_TASK_RCD*)p2;

	if (pIdInfo && pIdInfo->ui64Id) {
		if (pQMem->idInfo_send.ui64Id == pIdInfo->ui64Id
			&& pQMem->uiTranNo == uiTranNo)
		{
			if (pRcd)memcpy(pRcd, pQMem, sizeof(pRcd[0]));
			iRet = 1;  goto  errLabel;
		}
	}
	else  if (pQMem->id == id)
	{
		if (pRcd)memcpy(pRcd, pQMem, sizeof(pRcd[0]));
		iRet = 1;  goto  errLabel;
	}

	iRet = 0;
errLabel:
	return  iRet;
}

//  2013/02/06
BOOL  bGetImTaskRcdBySth_myDb(void* pDb, int  iDbType, BOOL  bHisTab, LPCTSTR  misServName, QY_MESSENGER_ID* pIdInfo, time_t  tSendTime, unsigned  int  uiTranNo, int  id, IM_TASK_RCD* pRcd)
{
	BOOL			bRet = FALSE;
	CMyDb* pMyDb = (CMyDb*)pDb;
	COMMON_PARAM		commonParam0;

	if (bHisTab)  goto  errLabel;
	MACRO_makeCommonParam3(pIdInfo, (void*)uiTranNo, (void*)id, commonParam0);


	if (qTraverse(pMyDb->m_var.pQ_qyImTaskTab, tmpHandle_bGetImTaskRcdBySth_myDb, &commonParam0, pRcd) <= 0)  goto  errLabel;

#if  0
	TCHAR			sqlBuf[CONST_maxSqlBufLen + 1] = _T("");
	TCHAR			whereClause[256] = _T("");
	unsigned  int	uiRcdCnt = 0;


	if (misServName && pIdInfo) {
		char	timeBuf[CONST_qyTimeLen + 1] = "";
		char	idStr[CONST_qyMessengerIdStrLen + 1] = "";
		//
		getTimeStr(tSendTime, timeBuf, mycountof(timeBuf));
		idInfo2Str(pIdInfo, idStr, mycountof(idStr));
		_sntprintf(whereClause, mycountof(whereClause), _T("misServName=%s and idStr_send='%s' and tSendTime='%s' and uiTranNo=%d"), getDbValStr(iDbType, CONST_iDataType_misServName, misServName), CString(idStr), CString(timeBuf), uiTranNo);
	}
	else {
		_sntprintf(whereClause, mycountof(whereClause), _T("id =%d"), id);
	}

	if (enumImTasks(pDb, iDbType, bHisTab, misServName, whereClause, NULL, 0, 0, &uiRcdCnt, pRcd))  goto  errLabel;
	if (!uiRcdCnt)  goto  errLabel;

#endif

	//
	bRet = TRUE;

errLabel:

	return  bRet;
}




