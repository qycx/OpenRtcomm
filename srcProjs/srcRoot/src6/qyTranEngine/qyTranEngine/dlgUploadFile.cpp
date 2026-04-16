#include "dlgUploadFile.h"

#include <QPushButton>

#include <tchar.h>
#include <qmStruct_defs.h>
#include <qyMcMainCommon_qt.h>
//#include <qyMcMainCommon_qt.h>
#include <ctxQmc.h>
#include <QWidget>

#include <dlgOfflineResProc.h>
#include <funcsForIsCliHelp.h>

#include <dlgOfflineResProc.h>

#include <dlgtalkproc.h>

int  procSendFile4p(LPCTSTR  fullFilePath, LPCTSTR  fileName, void* pPROC_offlineRes_u, HWND  m_hWnd, void* pDLG_TALK_var, int* piTaskId)
{
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;

#if  0//ndef  __SUPPORT_HTMLEDIT__
	return  -1;
#else
	/*
	DLG_TALK_var* pm_var = (DLG_TALK_var*)pDLG_TALK_var;
	if (!pm_var)  return  -1;
	DLG_TALK_var& m_var = *pm_var;*/

	DlgOfflineRes_varEx* pm_var = (DlgOfflineRes_varEx*)pDLG_TALK_var;
	if (!pm_var)  return  -1;
	DlgOfflineRes_varEx& m_var = *pm_var;

	QY_MC* pQyMc = QY_GET_GBUF();
	//IHTMLDocument2* pDoc = NULL;
	TCHAR				tBuf[256] = _T("");
	DWORD64				ui64FileLen = 0;
	CQyMalloc			mallocObj;
	//  unsigned  char		ucFlg		=	0;


	if (!fullFilePath)  return  -1;
	if (GetFileAttributes(fullFilePath) == -1) {
		//traceLogA("procSendFile: file not exists, %S", fullFilePath);
		return  -1;
	}

	//  ÕâÀï£¬ÔÝÊ±²ÉÓÃ32Î»µÄÎÄ¼þ´óÐ¡¡£ÒÔºó¸ÄÎª64Î»µÄ£¬ÒÔÖ§³Ö´óÎÄ¼þ
	struct _stat64 statBuf;
	if (_tstat64(fullFilePath, &statBuf))  return  -1;
	ui64FileLen = statBuf.st_size;

	//
	if (ui64FileLen == 0) {
		//qyShowHint(_T("send failed, fileLen is 0"));
		return -1;
	}


	//
		//
	int  iTaskId = 0;
	//
	{
		void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
		CQnmDb		db;
		if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
		pDb = db.m_pDbMem->pDb;
#endif

		iTaskId = newTaskId(pDb, pQyMc->cfg.db.iDbType);
	}
	int  iTaskId_suggested = iTaskId;

	int  iIndex_taskInfo = -1;

	unsigned  int  uiTaskDataType = 0;
	uiTaskDataType = CONST_taskDataType_transferFile;
	iIndex_taskInfo = newTaskInfoIndex(pProcInfo, uiTaskDataType, m_hWnd, iTaskId_suggested, _T("procSendFile"));
	if (iIndex_taskInfo < 0) {
		//traceLogA("procSendAvInfoFunc faile, newTaskInfoIndex failed");
		goto  errLabel;
	}
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, iIndex_taskInfo);
	if (pTaskInfo == NULL)goto errLabel;




	//  ÏÈÉêÇëtStartTime, uiTranNo
	MACRO_prepareForTran();

	//  ÏÈ·ÅÈëÊý¾Ý¿âÖÐ£¬·¢±éÖØ·¢ºÍ¼ÇÂ¼×´Ì¬
	//MIS_MSG_TASK				*	pMsg	=	(  MIS_MSG_TASK  *  )mallocObj.mallocf(  sizeof(  MIS_MSG_TASK  )  );
	MIS_MSG_TASK* pMsg = &pTaskInfo->var.pTaskData->msgU.task;
	if (!pMsg)  goto  errLabel;
	TRANSFER_FILE_REQ* pContent;
	unsigned  int					lenInBytes;
	IM_TASK_RCD						rcd;
	//
	MACRO_memset_misMsgTask(pMsg);
	pMsg->uiType = CONST_misMsgType_task;
	//
	pMsg->pMisCnt = m_var.pMisCnt;
	//
	pMsg->ucFlg = CONST_commFlg_talkData;
	//
	pMsg->usCode = CONST_qyCmd_sendRobotTask;
	pMsg->tStartTime = tStartTran;
	pMsg->uiTranNo = uiTranNo;
	//
	pContent = (TRANSFER_FILE_REQ*)pMsg->data.buf;
	memset(pContent, 0, sizeof(pContent[0]));
	pContent->uiType = CONST_imCommType_transferFileReq;
	lstrcpyn(pContent->fullFilePath, fullFilePath, mycountof(pContent->fullFilePath));
	if (fileName && fileName[0]) {
		safeTcsnCpy(fileName, pContent->fileName, mycountof(pContent->fileName));
	}
	else {
		if (pProcInfo->getDirAndFinalName(pContent->fullFilePath, NULL, 0, pContent->fileName, mycountof(pContent->fileName)))  goto  errLabel;
	}
	pContent->ui64FileLen = ui64FileLen;
	//  2014/07/13
	unsigned  int  uiSizePerSnd_internal = 0;
	if (pProcInfo->processQ_media.isEmpty())  uiSizePerSnd_internal = pProcInfo->cfg.uiSizePerSnd_file_noAv;
	else  uiSizePerSnd_internal = pProcInfo->cfg.uiSizePerSnd_file_avExists;
	pContent->uiSizePerSnd_suggest = uiSizePerSnd_internal;

	//  2015/08/05
	if (pPROC_offlineRes_u) {
		PROC_offlineRes_u* pProcOfflineRes = (PROC_offlineRes_u*)pPROC_offlineRes_u;
		if (pProcOfflineRes->common.usSubtype == CONST_procOfflineResSubtype_upload) {
			pContent->usSubtype = pProcOfflineRes->common.usSubtype;
			pContent->idInfo_logicalPeer.ui64Id = pProcOfflineRes->upload.idInfo_logicalPeer.ui64Id;
			//
			pContent->hTool_offlineRes = pProcOfflineRes->upload.hTool_offlineRes;
		}
		else  if (pProcOfflineRes->common.usSubtype == CONST_procOfflineResSubtype_download) {
			pContent->usSubtype = pProcOfflineRes->common.usSubtype;
			pContent->idInfo_logicalPeer.ui64Id = pProcOfflineRes->download.idInfo_logicalPeer.ui64Id;
		}
	}



	TASK_transferFile  task;
	memset(&task, 0, sizeof(task));
	task.m_index_taskInfo = iIndex_taskInfo;

	PROC_TASK_FILE& pContent_myTask = task.myTask;



	//  2009/10/20
	pContent_myTask.hWnd_task = m_hWnd;

	//  2007/07/18
	pMsg->uiTaskType = CONST_imTaskType_sendFile;
	//
	pMsg->idInfo_taskSender.ui64Id = m_var.pMisCnt->idInfo.ui64Id;
	pMsg->idInfo_taskReceiver.ui64Id = m_var.addr.idInfo.ui64Id;
	//
	pMsg->iStatus = CONST_imTaskStatus_waitToSend;

	//
	pMsg->addr_logicalPeer.idInfo = m_var.addr.idInfo;


	//  ÕâÀïµÄ¸³ÖµËÆºõÓ¦ÔÚ·¢ËÍÊ±Ê¹ÓÃ, 2007/07/24
	pMsg->data.route.idInfo_from.ui64Id = pMsg->idInfo_taskSender.ui64Id;
	pMsg->data.route.idInfo_to.ui64Id = pMsg->idInfo_taskReceiver.ui64Id;
	//

	lenInBytes = sizeof(pContent[0]);
	pMsg->lenInBytes = offsetof(MIS_MSG_routeTalkData, buf) + lenInBytes;

	if (!pFuncs->pf_msg2TaskRcd(m_var.pMisCnt, pMsg, CONST_qyRc_unknown, &rcd))  goto  errLabel;

	{
		void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
		CQnmDb	db;
		//
		if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
		pDb = db.m_pDbMem->pDb;
#endif
		//
		if (pFuncs->pf_storeTaskInDb(pDb, pQyMc->cfg.db.iDbType, m_var.pMisCnt, iTaskId_suggested, &rcd, FALSE) < 0)  goto  errLabel;
	}

	//
		//  2013/02/13
	if (iTaskId_suggested) {		//  2014/10/29
		if (rcd.id != iTaskId_suggested) {
#ifdef  __DEBUG__
			//traceLog(_T("procSendFile failed, rcd.id != taskInfo.iTaskId"));
#endif
			goto  errLabel;
		}
	}

	//


//
	pMsg->iTaskId = rcd.id;
	pMsg->uiTaskMode_unused = rcd.uiMode;
	pMsg->uiChannelType = CONST_channelType_robot;	//  2009/10/17

	PARAM_PROC_ROW  param;
	memset(&param, 0, sizeof(param));
	param.bScrollIntoView = TRUE;
	param.bNewMsg = TRUE;
	if (pFuncs->pf_tmpHandler_showMsg(m_hWnd, &param, pMsg))  goto  errLabel;

	if (pFuncs->pf_dlgTalk_qPostMsg(m_hWnd, pMsg, offsetof(MIS_MSG_TASK, data) + pMsg->lenInBytes))  goto  errLabel;

	//	
	if (m_var.addr.uiObjType == CONST_objType_imGrp) {
		pContent->bGrpTask = TRUE; //  2007/09/05, ¸³ÉÏ×é±êÊ¶
	}


	//
	if (0 != pProcInfo->processQ_media.qPostMsg(&task, sizeof(task)))
	{
		//traceLogA("procMsgTask_mc_robot: 1. qPostMsg failed");
		goto errLabel;
	}



	//  mgr
	unsigned  int  uiChannelType = CONST_channelType_robot;
	//
	uiChannelType = 0;
	//
	if (postMsgTask2Mgr_mc(m_var.pMisCnt, CONST_misMsgType_task, 0, CONST_qyCmd_sendRobotTask, tStartTran, uiTranNo, 0, pMsg->iTaskId, pMsg->uiTaskType, (char*)pContent, lenInBytes, &m_var.addr.idInfo, &pMsg->idInfo_taskSender, &pMsg->idInfo_taskReceiver, &m_var.addr.idInfo, uiChannelType, NULL, 0))  goto  errLabel;

	//  2015/08/06
	if (piTaskId)  *piTaskId = rcd.id;

errLabel:
	return  0;
#endif
}


__declspec(dllexport)  void  dlgOfflineRes_upload4p(HWND  hParent, HWND  hDlg_offlineRes, LPCTSTR  fileName)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your control notification handler code here
	int					iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	RECT				rc;
	int  idc;
	RECT* pRc;

	//
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  goto  errLabel;

	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  goto  errLabel;

	//
	dlgUploadFile* pDlg = (dlgUploadFile*)QWidget::find((WId)hDlg_offlineRes);
	if (!pDlg)  goto  errLabel;

	HWND  m_hWnd = hDlg_offlineRes;
	DlgOfflineRes_varEx* m_var = pDlg->m_var;

	//
	HWND  hTalker_res = NULL;
	if (pFuncs->pf_talkToMessenger(pMisCnt->procOfflineRes.idInfo_resServ.ui64Id, 0, TRUE, FALSE, &hTalker_res)) {
		goto  errLabel;
	}

	//
	{
		/*
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var* pDlgTalkVar;
		pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(m_var.hDlgTalk_mgr);
		if (!pDlgTalkVar)  goto  errLabel;
		//
		if (!isTalkerShadowMgr(pDlgTalkVar->addr))  goto  errLabel;
		*/
		//
		//
		PROC_offlineRes_upload	req;
		memset(&req, 0, sizeof(req));
		req.uiType = CONST_imCommType_procOfflineRes;
		req.usSubtype = CONST_procOfflineResSubtype_upload;
		req.hTool_offlineRes = m_hWnd;
		//
		safeTcsnCpy(fileName, req.fullFileName, mycountof(req.fullFileName));
		//
		//req.idInfo_logicalPeer.ui64Id = pDlgTalkVar->addr.idInfo.ui64Id;
		//

		//
		if (m_var->reses_beingProced.usCnt >= mycountof(m_var->reses_beingProced.mems))  goto  errLabel;
		RES_inProcess* pMem = &m_var->reses_beingProced.mems[m_var->reses_beingProced.usCnt];
		memset(pMem, 0, sizeof(pMem[0]));
		safeTcsnCpy(req.fullFileName, pMem->res.name, mycountof(pMem->res.name));
		pMem->usSubtype = req.usSubtype;
		m_var->reses_beingProced.usCnt++;
		//
		int  index = m_var->reses_retrieved.usCnt + m_var->reses_beingProced.usCnt - 1;
		HWND  hCtrl = ::GetDlgItem(m_hWnd, m_var->guiData.iIDC_LIST_offlineRes);
		::SendMessage(hCtrl, LB_INSERTSTRING, (WPARAM)index, (LPARAM)pMem->res.name);

		//
		QY_WMBUF_COMM	wmBuf;
		memset(&wmBuf, 0, sizeof(wmBuf));
		wmBuf.uiType = CONST_qyWmParam_procOfflineRes;
		//wmBuf.u.procOfflineRes.ui64Id_req = pDlgTalkVar->addr.idInfo.ui64Id;
		wmBuf.u.procOfflineRes.pPROC_offlineRes_u = &req;
		wmBuf.u.procOfflineRes.uiTranNo_wait = 0;

		
		procSendFile4p(_T("D:\\qycx\\"), _T("tmInit.ini"), NULL, hParent, m_var, 0);
		

		if (!SendMessageTimeout(hParent/*hTalker_res*/, CONST_qyWm_comm, 0, (LPARAM)&wmBuf, 0, 1000, NULL))  goto  errLabel;
		//
		//pMem->iTaskId = wmBuf.u.procOfflineRes.iTaskId;
		//
		int  i;
		i = 0;


	}

	//
	//pDlg->ResesDisplay();

	//
	iErr = 0;

errLabel:

	return;
}

bool dlgUploadFile::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	Q_UNUSED(eventType);
	MSG* msg = reinterpret_cast<MSG*>(message);
	UINT m = msg->message;
	if (m == WM_COMMAND  || m == CONST_qyWm_postComm)
	{
	}
	else if (m == CONST_qyWm_comm) {
		int i = 5;
		i++;
	}

	return QWidget::nativeEvent(eventType, message, result);
}

dlgUploadFile::dlgUploadFile(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton_upload, &QPushButton::clicked, [this] {
		//QMessageBox::information(0, tr("提示"), tr("槽函数！"));
		this->slot_upload_click();
		});

	this->m_var = new DlgOfflineRes_varEx();

	if (this->m_var) {
		this->m_var->pMisCnt = new MIS_CNT();
	}
}

dlgUploadFile::~dlgUploadFile()
{}

extern void  dlgOfflineRes_upload(HWND  hParent, HWND  hDlg_offlineRes, LPCTSTR  fileName);
//extern int  procSendFile(LPCTSTR  fullFilePath, LPCTSTR  fileName, void* pPROC_offlineRes_u, HWND  m_hWnd, void* pDLG_TALK_var, int* piTaskId);



/*
void dlgUploadFile::SendFile(QString fullFileName, HWND hWnd)
{
	//CHelp_getDlgTalkVar	help_getDlgTalkVar;
	//
	TCHAR* pName = (TCHAR*)fullFileName.utf16();
	HWND  hMgr = hWnd;
	//
	TCHAR* finalName = null;
	if (pProcInfo->bAppQt()) {
		finalName = _tcsrchr(pName, _T('/'));
		if (finalName != null) {
			finalName++;
		}

	}
	//
	int  iTaskId = 0;
	procSendFile(pName, finalName, pReq, hMgr, (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgr), &iTaskId);
	//
	//pComm->u.procOfflineRes.iTaskId = iTaskId;
}*/

void dlgUploadFile::slot_upload_click()
{
	//emit to_returnMain_wifi_signal();

	QString strFileName = "d:\\qycx\\tmInit.ini";

	TCHAR* fileName = (TCHAR*)strFileName.utf16();

	//TCHAR* fileName;// = _T("c:\\test.cpp");

	//TCHAR  tDir[256];
	//int  CCtxQmc_gui::getDirAndFinalName(LPCTSTR  svFileName, TCHAR * dirName, unsigned  int  size, TCHAR * finalName, unsigned  int  finalNameSize)


	int  iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	//CQyString			pathCStr;
	HWND  m_hWnd = (HWND)this->winId();
	//
	HWND  hParent = m_hWnd;

	//  2015/06/06	
	// 
	/*
	if (!pProcInfo->bUse_imObjView_as_guiWnd()) {
		if (bApp_ts_3d(pQyMc)) {
			GBuf_d3d_isCli* pGBuf = (GBuf_d3d_isCli*)pQyMc->pGBuf_d3d;
			if (!IsWindow(pGBuf->hWall_d3d))  goto  errLabel;
			hParent = pGBuf->hWall_d3d;
		}
	}
	*/

	//
	//if (qyBrowseForFile(hParent, TRUE, lpszDefExt, dwFlags, CONST_FILE_FILTER_allFiles, title, NULL, pQyMc, pathCStr))  goto  errLabel;

	//
	dlgOfflineRes_upload4p(hParent, m_hWnd, fileName);

	iErr = 0;

errLabel:

	return;
}