
#include	"stdafx.h"
#include	<time.h>
#include	<windowsx.h>
#include	<math.h>
#include	"qymcMainCommon.h"


#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"

#include	"qyOpenShellCommon.h"


#include	"tmpCeLib.h"

#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"

#include	"myresource.h"

#include	<assert.h>
#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
#include	"qmcConferenceWall.h"
#endif
#include	"qmcCmdProc.h"
#include	"dlgTalkProc.h"
#include	"isCliHelpPublic.h"
#include	"isCliD3dPublic.h"

#include	"qmcCommFunc_isCli.h"
//
#include	"funcsForIsCliHelp.h"
#include	"smLoginProc.h"




//
int  getConfKey(HWND  hDlgTalk, int  iTaskId, CONF_KEY* pStatus, LPCTSTR  hint)
{
	int								iErr = -1;
	CHelp_getDlgTalkVar				help_getDlgTalkVar;
	DLG_TALK_var* pm_var = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk);
	if (!pm_var)  return  -1;
	DLG_TALK_var& m_var = *pm_var;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if (!pStatus)  return  -1;
	CONF_KEY& status = *pStatus;

	int								i;
	int								lenInBytes;
	MIS_CNT* pMisCnt = m_var.pMisCnt;
	if (!hint)  hint = _T("");

	//
	TCHAR							tBuf[128];

	//
	//if  (  !pIdInfo_to  ||  !pIdInfo_to->ui64Id  )  return  -1;

	if (!m_var.av.taskInfo.bTaskExists)  return  -1;
	if (!m_var.av.taskInfo.ucbStarter)  return  -1;

	//
	if (m_var.av.taskInfo.iTaskId != iTaskId)  return  -1;

	//
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
	if (!pTaskInfo)  return  -1;
	if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  return  -1;
	QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;

	//		
	DLG_TALK_videoConference* pVc = &pTc->videoConference;

	//
	memset(&status, 0, sizeof(status));
	status.uiType = CONST_imCommType_confKey;
	if (m_var.av.taskInfo.ucbVideoConference)  status.idInfo_imGrp_related.ui64Id = m_var.addr.idInfo.ui64Id;

	//  2010/12/29
	if (m_var.av.taskInfo.bTaskExists && m_var.av.taskInfo.ucbStarter) {
		//
		//
		status.idInfo_compere.ui64Id = m_var.av.taskInfo.unused_idInfo_compere.ui64Id;
		//
		status.usLayoutType_starter = m_var.m_layout.usLayoutType_cur;//  dlgTalk_get_usLayoutType_local(  hDlgTalk  );	//  m_var.av.usLayoutType_local;
	}

	//
	_sntprintf(tBuf, mycountof(tBuf), _T("getConfKey: compere %I64u"), status.idInfo_compere.ui64Id);
	showInfo_open0(0, 0, tBuf);


	//
	if (m_var.av.taskInfo.ucbVideoConference
		&& m_var.av.taskInfo.ucbStarter)
	{
		QMC_mosaic_maker* pMosaicMaker = &m_var.av.taskInfo.mosaicMaker;
		MOSAIC_TRAN_INFO	mti;
		//
		switch (status.usLayoutType_starter) {
		case  CONST_usLayoutType_training:
			//
			status.mems[status.usCnt].avStream.idInfo = pMisCnt->idInfo;
			status.mems[status.usCnt].avStream.obj.resObj = pMosaicMaker->resource.resObj;
			getMosaicTranInfo(&pMosaicMaker->resource, &mti);
			status.mems[status.usCnt].avStream.obj.tranInfo.video = mti.video;
			//status.mems[status.usCnt].ucbActive  =  true;
			status.usCnt++;
			//
			if (pTc->ucb2Streams) {
				status.mems[status.usCnt].avStream.idInfo = pMisCnt->idInfo;
				status.mems[status.usCnt].avStream.obj.resObj = pMosaicMaker->video.resObj;
				getMosaicTranInfo(&pMosaicMaker->video, &mti);
				status.mems[status.usCnt].avStream.obj.tranInfo.video = mti.video;
				//status.mems[status.usCnt].ucbActive  =  true;
				status.usCnt++;
				//
			}
			//
			break;
		case  CONST_usLayoutType_dialog:
		default:
			//
			status.mems[status.usCnt].avStream.idInfo = pMisCnt->idInfo;
			status.mems[status.usCnt].avStream.obj.resObj = pMosaicMaker->video.resObj;
			getMosaicTranInfo(&pMosaicMaker->video, &mti);
			status.mems[status.usCnt].avStream.obj.tranInfo.video = mti.video;
			//status.mems[status.usCnt].ucbActive  =  true;
			status.usCnt++;
			//
			if (pTc->ucb2Streams) {
				//
				status.mems[status.usCnt].avStream.idInfo = pMisCnt->idInfo;
				status.mems[status.usCnt].avStream.obj.resObj = pMosaicMaker->resource.resObj;
				getMosaicTranInfo(&pMosaicMaker->resource, &mti);
				status.mems[status.usCnt].avStream.obj.tranInfo.video = mti.video;
				//status.mems[status.usCnt].ucbActive  =  true;
				status.usCnt++;
				//
			}
			//
			break;
		}
	}


	//
	for (i = 0; i < pVc->usCntLimit_activeMems_from; i++) {
		if (!pVc->activeMems_from[i].avStream.idInfo.ui64Id)  continue;
		//
		if (status.usCnt >= mycountof(status.mems)) {
			showInfo_open0(0, 0, _T("sendConfKey err: status too many mems, can't add a activeMem"));
			break;
		}
		//  status.mems[status.usCnt].idInfo.ui64Id  =  pVc->activeMems_from[i].mem.idInfo.ui64Id;
		//memcpy(  &status.mems[status.usCnt].avStream.idInfo,  &pVc->activeMems_from[i].avStream.idInfo,  sizeof(  status.mems[status.usCnt].avStream.idInfo  )  );
		//memcpy(  &status.mems[status.usCnt].avStream.obj.tranInfo,  &pVc->activeMems_from[i].avStream.obj.tranInfo,  sizeof(  status.mems[status.usCnt].avStream.obj.tranInfo  )  );	//  2009/05/31
		status.mems[status.usCnt].avStream = pVc->activeMems_from[i].avStream;
		//
		//status.mems[status.usCnt].ucbActive  =  TRUE;
		//
		//  2013/07/18. 需要将第几个话筒的属性传给所有的成员,以便协调显示格局
		status.mems[status.usCnt].usIndex_speaker = i;
		//
		status.usCnt++;
	}

	//
	CONF_requesting_mems& requestingMems = status.requestingMems;
	for (i = 0; i < mycountof(pVc->requestingMems_from); i++) {
		if (!pVc->requestingMems_from[i].avStream.idInfo.ui64Id)  continue;
		//
		if (requestingMems.usCnt >= mycountof(requestingMems.mems)) {
			showInfo_open0(0, 0, _T("sendConfKey err: status too many mems, can't add a requestingMem"));
			break;
		}
		//
		requestingMems.mems[requestingMems.usCnt].idInfo.ui64Id = pVc->requestingMems_from[i].avStream.idInfo.ui64Id;
		safeTcsnCpy(pVc->requestingMems_from[i].desc, requestingMems.mems[requestingMems.usCnt].desc, mycountof(requestingMems.mems[requestingMems.usCnt].desc));
		//
		requestingMems.usCnt++;
	}

#if  0
	lenInBytes = sizeof(status);
	//					
	MACRO_prepareForTran();
	//	
	if (postMsgTask2Mgr_mc(m_var.pMisCnt, CONST_misMsgType_task, 0, CONST_qyCmd_sendTask, tStartTran, uiTranNo, 0, 0, 0, (char*)&status, lenInBytes, NULL, NULL, NULL, pIdInfo_to, 0, NULL, FALSE))  goto  errLabel;
#endif

	//
	//status.confLayoutParam.respVideoStatus.bAmplification = m_var.m_bEnlarge ? 1 : 0;

	StatusConfLayoutParam statusConfLayoutParam = { 0 };
	getStatusConfLayoutParam(hDlgTalk, iTaskId, &statusConfLayoutParam, _T(""));
	status.confLayoutParam = statusConfLayoutParam.confLayoutParam;




	//
	iErr = 0;
errLabel:


	return  iErr;
}



//
int  getStatusConfLayoutParam(HWND  hDlgTalk, int  iTaskId, StatusConfLayoutParam* pStatus, LPCTSTR  hint)
{
	int								iErr = -1;
	CHelp_getDlgTalkVar				help_getDlgTalkVar;
	DLG_TALK_var* pm_var = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk);
	if (!pm_var)  return  -1;
	DLG_TALK_var& m_var = *pm_var;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if (!pStatus)  return  -1;
	StatusConfLayoutParam& status = *pStatus;

	int								i;
	int								lenInBytes;
	MIS_CNT* pMisCnt = m_var.pMisCnt;
	if (!hint)  hint = _T("");

	//
	TCHAR							tBuf[128];

	//
	//if  (  !pIdInfo_to  ||  !pIdInfo_to->ui64Id  )  return  -1;

	if (!m_var.av.taskInfo.bTaskExists)  return  -1;
	if (!m_var.av.taskInfo.ucbStarter)  return  -1;

	//
	if (m_var.av.taskInfo.iTaskId != iTaskId)  return  -1;

	//
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
	if (!pTaskInfo)  return  -1;
	if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  return  -1;
	QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;

	//		
	DLG_TALK_videoConference* pVc = &pTc->videoConference;

	//
	memset(&status, 0, sizeof(status));
	status.uiType = CONST_imCommType_statusConfLayoutParam;
	if (m_var.av.taskInfo.ucbVideoConference)  status.idInfo_imGrp_related.ui64Id = m_var.addr.idInfo.ui64Id;

	//  2010/12/29


	//
	status.confLayoutParam = pVc->confLayoutParam1;

	//
	if (m_var.m_bEnlarge1 && pVc->confLayoutParam1.enlargeParam.ui64Id) {
		//status.confLayoutParam.respVideoStatus.bAmplification = m_var.m_bEnlarge ? 1 : 0;
		status.confLayoutParam.respVideoStatus.bAmplification = 1;
	}
	else {
		status.confLayoutParam.respVideoStatus.bAmplification = 0;
	}

	//
	iErr = 0;
errLabel:


	return  iErr;
}







//
int  sendConfKey(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint)
{
	int								iErr = -1;
	CHelp_getDlgTalkVar				help_getDlgTalkVar;
	DLG_TALK_var* pm_var = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk);
	if (!pm_var)  return  -1;
	DLG_TALK_var& m_var = *pm_var;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	CONF_KEY			status;
	int								i;
	int								lenInBytes;
	MIS_CNT* pMisCnt = m_var.pMisCnt;
	if (!hint)  hint = _T("");

	//
	TCHAR							tBuf[128];

	//
	QY_MESSENGER_ID* pIdInfo_to = &idInfo_to;
	if (!pIdInfo_to || !pIdInfo_to->ui64Id)  return  -1;

	if (!m_var.av.taskInfo.bTaskExists)  return  -1;
	if (!m_var.av.taskInfo.ucbStarter)  return  -1;

#if  0
	//
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
	if (!pTaskInfo)  return  -1;
	if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  return  -1;
	QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;

	//		
	DLG_TALK_videoConference* pVc = &pTc->videoConference;

	//
	memset(&status, 0, sizeof(status));
	status.uiType = CONST_imCommType_confKey;
	if (m_var.av.taskInfo.ucbVideoConference)  status.idInfo_imGrp_related.ui64Id = m_var.addr.idInfo.ui64Id;

	//  2010/12/29
	if (m_var.av.taskInfo.bTaskExists && m_var.av.taskInfo.ucbStarter) {
		status.usLayoutType_starter = m_var.m_layout.usLayoutType_cur;//  dlgTalk_get_usLayoutType_local(  hDlgTalk  );	//  m_var.av.usLayoutType_local;
	}

	//
	if (m_var.av.taskInfo.ucbVideoConference
		&& m_var.av.taskInfo.ucbStarter)
	{
		QMC_mosaic_maker* pMosaicMaker = &m_var.av.taskInfo.mosaicMaker;
		MOSAIC_TRAN_INFO	mti;
		switch (status.usLayoutType_starter) {
		case  CONST_usLayoutType_training:
			status.mems[status.usCnt].avStream.idInfo = pMisCnt->idInfo;
			status.mems[status.usCnt].avStream.obj.resObj = pMosaicMaker->resource.resObj;
			getMosaicTranInfo(&pMosaicMaker->resource, &mti);
			status.mems[status.usCnt].avStream.obj.tranInfo.video = mti.video;
			//status.mems[status.usCnt].ucbActive  =  true;
			status.usCnt++;
			break;
		case  CONST_usLayoutType_dialog:
		default:
			status.mems[status.usCnt].avStream.idInfo = pMisCnt->idInfo;
			status.mems[status.usCnt].avStream.obj.resObj = pMosaicMaker->video.resObj;
			getMosaicTranInfo(&pMosaicMaker->video, &mti);
			status.mems[status.usCnt].avStream.obj.tranInfo.video = mti.video;
			//status.mems[status.usCnt].ucbActive  =  true;
			status.usCnt++;
			break;
		}
	}


	//
	for (i = 0; i < pVc->usCntLimit_activeMems_from; i++) {
		if (!pVc->activeMems_from[i].avStream.idInfo.ui64Id)  continue;
		//
		if (status.usCnt >= mycountof(status.mems)) {
			showInfo_open0(0, 0, _T("sendConfKey err: status too many mems, can't add a activeMem"));
			break;
		}
		//  status.mems[status.usCnt].idInfo.ui64Id  =  pVc->activeMems_from[i].mem.idInfo.ui64Id;
		//memcpy(  &status.mems[status.usCnt].avStream.idInfo,  &pVc->activeMems_from[i].avStream.idInfo,  sizeof(  status.mems[status.usCnt].avStream.idInfo  )  );
		//memcpy(  &status.mems[status.usCnt].avStream.obj.tranInfo,  &pVc->activeMems_from[i].avStream.obj.tranInfo,  sizeof(  status.mems[status.usCnt].avStream.obj.tranInfo  )  );	//  2009/05/31
		status.mems[status.usCnt].avStream = pVc->activeMems_from[i].avStream;
		//
		//status.mems[status.usCnt].ucbActive  =  TRUE;
		//
		//  2013/07/18. 需要将第几个话筒的属性传给所有的成员,以便协调显示格局
		status.mems[status.usCnt].usIndex_speaker = i;
		//
		status.usCnt++;
	}

	//
	CONF_requesting_mems& requestingMems = status.requestingMems;
	for (i = 0; i < mycountof(pVc->requestingMems_from); i++) {
		if (!pVc->requestingMems_from[i].avStream.idInfo.ui64Id)  continue;
		//
		if (requestingMems.usCnt >= mycountof(requestingMems.mems)) {
			showInfo_open0(0, 0, _T("sendConfKey err: status too many mems, can't add a requestingMem"));
			break;
		}
		//
		requestingMems.mems[requestingMems.usCnt].idInfo.ui64Id = pVc->requestingMems_from[i].avStream.idInfo.ui64Id;
		//
		requestingMems.usCnt++;
	}
#endif

	//
	if (getConfKey(hDlgTalk, m_var.av.taskInfo.iTaskId, &status, _T("sendVideoConferenctStatus")))  goto  errLabel;

	//
#if  1 //def  __DEBUG__
#if 0
	for (i = 0; i < status.usCnt; i++) {
		_sntprintf(tBuf, mycountof(tBuf), _T("confKey: act[%d]: %I64u"), i, status.mems[i].avStream.idInfo.ui64Id);
		showInfo_open0(0, 0, tBuf);
	}
	for (i = 0; i < status.requestingMems.usCnt; i++) {
		_sntprintf(tBuf, mycountof(tBuf), _T("confKey: req[%d]: %I64u |%s|"), i, status.requestingMems.mems[i].idInfo.ui64Id, status.requestingMems.mems[i].desc);
		showInfo_open0(0, 0, tBuf);
	}
#endif
#endif

	//	
	lenInBytes = sizeof(status);
	//					
	MACRO_prepareForTran();
	//	
	if (postMsgTask2Mgr_mc(m_var.pMisCnt, CONST_misMsgType_task, 0, CONST_qyCmd_sendTask, tStartTran, uiTranNo, 0, 0, 0, (char*)&status, lenInBytes, NULL, NULL, NULL, pIdInfo_to, 0, NULL, FALSE))  goto  errLabel;

	iErr = 0;
errLabel:

	_sntprintf(tBuf, mycountof(tBuf), _T("%s. sendVideoConfStatus to %I64u. %s"), hint, pIdInfo_to->ui64Id, iErr ? _T("failed") : _T(""));
	showInfo_open0(0, 0, tBuf);

	return  iErr;
}



//

//
int  sendStatusConfLayoutParam(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint)
{
	int								iErr = -1;
	CHelp_getDlgTalkVar				help_getDlgTalkVar;
	DLG_TALK_var* pm_var = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk);
	if (!pm_var)  return  -1;
	DLG_TALK_var& m_var = *pm_var;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	StatusConfLayoutParam			status;

	int								i;
	int								lenInBytes;
	MIS_CNT* pMisCnt = m_var.pMisCnt;
	if (!hint)  hint = _T("");

	//
	TCHAR							tBuf[128];

	//
	QY_MESSENGER_ID* pIdInfo_to = &idInfo_to;
	if (!pIdInfo_to || !pIdInfo_to->ui64Id)  return  -1;

	if (!m_var.av.taskInfo.bTaskExists)  return  -1;
	if (!m_var.av.taskInfo.ucbStarter)  return  -1;


	//
	if (getStatusConfLayoutParam(hDlgTalk, m_var.av.taskInfo.iTaskId, &status, _T("sendVideoConferenctStatus")))  goto  errLabel;

	//
#if  1 //def  __DEBUG__
#if 1

	_sntprintf(tBuf, mycountof(tBuf), _T("status.confLayoutParam: %I64u--------%d-------------iChannel:%d"), status.confLayoutParam.enlargeParam.ui64Id, status.confLayoutParam.respVideoStatus.bAmplification, status.confLayoutParam.ipcParam.iChannel);
	showInfo_open0(0, 0, tBuf);

#endif
#endif

	//	
	lenInBytes = sizeof(status);
	//					
	MACRO_prepareForTran();
	//	
	if (postMsgTask2Mgr_mc(m_var.pMisCnt, CONST_misMsgType_task, 0, CONST_qyCmd_sendTask, tStartTran, uiTranNo, 0, 0, 0, (char*)&status, lenInBytes, NULL, NULL, NULL, pIdInfo_to, 0, NULL, FALSE))  goto  errLabel;

	iErr = 0;
errLabel:

	_sntprintf(tBuf, mycountof(tBuf), _T("%s. sendVideoConfStatus to %I64u. %s"), hint, pIdInfo_to->ui64Id, iErr ? _T("failed") : _T(""));
	showInfo_open0(0, 0, tBuf);

	return  iErr;
}
