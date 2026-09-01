#include "CDlgObjs_ts_qt.h"

#include "help_getDlgTalkVar.h"
#include "dlgtalkproc.h"
#include "objType_tmp.h"

#include "isCliExPublic.h"
#include "isCliD3dPublic.h"

#include "qmcCommFunc_isCli.h"

#include "qmcDynBmp.h"

#include <QListWidget>
#include <QListWidgetItem>


int  showDlgObjs(HINSTANCE  g_hInst, HWND  hParent, void* pDLG_guiDataParam_objs)
{

	DLG_guiDataParam_objs* pParam = (DLG_guiDataParam_objs*)pDLG_guiDataParam_objs;

	int		iErr = -1;
	CDlgObjs_ts_qt	dlg(hParent, nullptr);

	DLG_guiData_objs* p = (DLG_guiData_objs*)&dlg.m_var.guiData;
	if (!p)  goto  errLabel;

	if (pParam) {
		//  p->param.uiType  =  pParam->param.uiType;
		memcpy(&p->param, pParam, sizeof(p->param));
	}

	/*
	p->iIDC_LIST0 = IDC_LIST0;
#if  0  //  ndef  __DEBUG__
	p->iIDC_BUTTON_contact = IDC_BUTTON_contact;
	p->iIDC_BUTTON_group = IDC_BUTTON_group;
	p->iIDC_BUTTON_status = IDC_BUTTON_status;
#endif
	p->iIDCANCEL = IDCANCEL;
	p->iIDOK = IDOK;

	if (dlg.DoModal() != IDOK)  goto  errLabel;
	*/
	dlg.setModal(true);
	//dlg.setWindowModality(Qt::ApplicationModal);
	dlg.OnInitDialog();
	dlg.resize(400, 350);
	QY_MC* pQyMc; pQyMc = QY_GET_GBUF();
	dlg.setWindowTitle(QString::fromWCharArray(getResStr(0, &pQyMc->cusRes, CONST_resId_select)));
	dlg.setFixedSize(dlg.width(), dlg.height());
	if(dlg.exec() != QDialog::Accepted) goto  errLabel;

	if (pParam) {
		//  pParam->ui64Id_selected  =  p->param.ui64Id_selected;
		memcpy(&pParam->o, &p->param.o, sizeof(pParam->o));
		//
		memcpy(pParam->pObjBuf_selected, p->param.pObjBuf_selected, pParam->uiSize_pObjBuf_selected);
	}

	iErr = 0;
errLabel:
	return  iErr;

}

int  closeMoreIa(HWND  hDlgTalk)
{
	CHelp_getDlgTalkVar  help_getDlgTalkVar;
	DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk);
	if (!pCurVar)  return  -1;


	if (pCurVar->guiData.ucbShowMore) {
		pCurVar->guiData.ucbShowMore = false;
		PostMessage(pCurVar->hWnd_instantAssistant, WM_CLOSE, 0, 0);
	}

	return  0;
}

void showDlgObjs_ts(HWND hCurTalk, DLG_TALK_var* pMgrVar, QY_wmBuf_command* pWmBuf, TALKER_shadow_mgr* pShadowMgr, HWND	hMgr, HWND	hShow) {

	
	//HWND				hCurTalk	=	m_hWnd;
	//DLG_TALK_var  *		pCurVar		=  pm_var;
	////
	//HWND				hMgr		=	m_hWnd;
	//DLG_TALK_var  *		pMgrVar		=	pm_var;
	//if  (  !isTalkerShadowMgr(  pm_var->addr  )  )  {
	//	TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pm_var->pShadowInfo;
	//	if  (  !pTalkerShadow  )  goto  errLabel;
	//	if  (  !IsWindow(  pTalkerShadow->hMgr  )  )  goto  errLabel;
	//	hMgr  =  pTalkerShadow->hMgr;		//  2013/02/15
	//	pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr  );
	//	if  (  !pMgrVar  )  goto  errLabel;

	//}
	
	

	int					iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return;

	//CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;


	//if (!pm_var)  return;
	//if (!pWmBuf)  return;

	//TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)m_var.pShadowInfo;
	//if (!pShadowMgr)  goto  errLabel;


	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
	DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar_cur.getVar(hCurTalk);
	if (!pCurVar)  goto  errLabel;

	DLG_guiDataParam_objs		param;
	DYN_BMP_RULE				dynBmpRule_selected;

	//
	memset(&dynBmpRule_selected, 0, sizeof(dynBmpRule_selected));

	//
	memset(&param, 0, sizeof(param));
	param.uiType = CONST_objType_selectRemoteVideo;
	param.hCurTalk = hCurTalk;
	param.pCurVar = pCurVar;							//  2013/06/10
	param.pMgrVar = pMgrVar;
	param.pObjBuf_selected = &dynBmpRule_selected.dynBmp;			//  2014/05/15
	param.uiSize_pObjBuf_selected = sizeof(dynBmpRule_selected);

	//  2015/06/05
	HWND  hParent; hParent = hCurTalk;
	//  2016/05/24
	/*if (IsWindow(pWmBuf->hParent_expected)) {
		hParent = pWmBuf->hParent_expected;
	}*/

	if (hShow) {
		hParent = hShow;
	}


	//
	if (!bUse_imObjView_as_guiWnd()) {
		if (bApp_ts_3d(pQyMc)) {
			GBuf_d3d_isCli* pGBuf = (GBuf_d3d_isCli*)pQyMc->pGBuf_d3d;
			if (!pGBuf)  goto  errLabel;
			if (!IsWindow(pGBuf->hWall_d3d))  goto  errLabel;
			hParent = pGBuf->hWall_d3d;
		}
	}

	//
	if (showDlgObjs(pQyMc->g_hInst, hParent, &param)) {
		goto  errLabel;
	}



	//
	if (!dynBmpRule_selected.dynBmp.resObj.uiObjType) {
#ifdef  __DEBUG__
		//traceLog(_T("Select dynBmp failed, uiObjType is 0"));
#endif
		goto  errLabel;
	}

	//
	BOOL  bView; bView = FALSE;


	bView = tmpF_bViewRemoteVideo(&pShadowMgr->vwRuleCmd_manual, dynBmpRule_selected.dynBmp.resObj.uiObjType, 
		dynBmpRule_selected.dynBmp.resObj.usIndex_obj, dynBmpRule_selected.dynBmp.resObj.usHelp_subIndex);
	tmpF_setViewRemoteVideo(&dynBmpRule_selected, !bView, &pShadowMgr->vwRuleCmd_manual);


	BOOL  bCurView; bCurView = !bView;
	if (!bCurView) {
		/*if (IsWindow(pCurVar->ptzControl.hWnd_ptzControl)) {
			CDlgPtzControl* pDlgPtzControl = (CDlgPtzControl*)CWnd::FromHandlePermanent(pCurVar->ptzControl.hWnd_ptzControl);
			if (pDlgPtzControl) {
				if (pDlgPtzControl->m_var.bRemote
					&& isSame_resObj(&pDlgPtzControl->m_var.remote.remoteCamera.qisResObj.resObj, &dynBmpRule_selected.dynBmp.resObj))
				{
					PostMessage(pCurVar->ptzControl.hWnd_ptzControl, WM_CLOSE, 0, 0);
				}
			}
		}*/
	}


	//
	chkTalkerRules(hMgr, pMgrVar);

	//
	unsigned  int		uiObjType; uiObjType = 0;
	unsigned  short	usIndex_dynBmp; usIndex_dynBmp = 0;
	int				talkerRuleIndex; talkerRuleIndex = 0;
	int  i;


	for (i = 0; i < mycountof(pShadowMgr->vwRuleCmd.dynBmpRules); i++) {
		if (pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.uiObjType == dynBmpRule_selected.dynBmp.resObj.uiObjType
			&& pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.usIndex_obj == dynBmpRule_selected.dynBmp.resObj.usIndex_obj
			&& pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.usHelp_subIndex == dynBmpRule_selected.dynBmp.resObj.usHelp_subIndex
			)
		{
			break;
		}
	}
	if (i == mycountof(pShadowMgr->talkerDynBmps))  goto  errLabel;
	talkerRuleIndex = i;


	BOOL			bNeedProgress; bNeedProgress = TRUE;
	BOOL			bImgRestarted; bImgRestarted = FALSE;

	//				  	
	uiObjType = dynBmpRule_selected.dynBmp.resObj.uiObjType;
	usIndex_dynBmp = dynBmpRule_selected.dynBmp.resObj.usIndex_obj;
	unsigned  short  usHelp_subIndex; usHelp_subIndex = dynBmpRule_selected.dynBmp.resObj.usHelp_subIndex;
	if (tmpF_bViewRemoteVideo(&pShadowMgr->vwRuleCmd_manual, uiObjType, usIndex_dynBmp, usHelp_subIndex)) {
		if (tmpF_bViewRemoteVideo(&pShadowMgr->vwRuleCmd, uiObjType, usIndex_dynBmp, usHelp_subIndex)) {
			//
			chkToViewDynBmp(hMgr, pMgrVar, talkerRuleIndex, bNeedProgress, &bImgRestarted);
		}
	}


	if (bImgRestarted) {

		TALKER_dynBmp* pRule = NULL;
		unsigned  int		uiTranNo = 0;

		pRule = &pShadowMgr->talkerDynBmps[talkerRuleIndex];
		uiTranNo = pRule->taskInfo.uiTranNo;

		//
		if (showProgress(&pQyMc->gui.progress, &pQyMc->cusRes, hCurTalk, _T("Please waiting"), 
			NULL, 30, -1, uiTranNo) != IDOK) {
			goto  errLabel;
		}

		//
#ifdef  __DEBUG__
		int  ii;
		ii = 9;
#endif
	}

	//
	closeMoreIa(hCurTalk);


errLabel:
	return;
}

CDlgObjs_ts_qt::CDlgObjs_ts_qt(HWND hWndParent, QDialog* parent)
	: QDialog(parent)
	, ui(new Ui::CDlgObjs_ts_qtClass())
{
	ui->setupUi(this);

	m_var.m_hParent = hWndParent;

	memset(&m_var, 0, sizeof(m_var));

	ui->IDC_LIST0->setSelectionMode(QAbstractItemView::SingleSelection);

	connect(ui->IDC_LIST0, &QListWidget::itemSelectionChanged, this, &CDlgObjs_ts_qt::dlgObjs_OnLbnSelchangeList0);

	connect(ui->btnOK, &QPushButton::clicked, this, &CDlgObjs_ts_qt::onBtnOkClicked);
	connect(ui->btnCANCEL, &QPushButton::clicked, this, &CDlgObjs_ts_qt::OnBnClickedCancel);
}

void CDlgObjs_ts_qt::onBtnOkClicked() 
{
	dlgObjs_OnOK((HWND)this->winId(), &m_var);

	accept();
	//reject();
	//done(QDialog::Accepted); 
}

void CDlgObjs_ts_qt::OnBnClickedCancel() {
	reject();
}

CDlgObjs_ts_qt::~CDlgObjs_ts_qt()
{
	delete ui;

	if (m_var.pData_items)  free(m_var.pData_items);
	MACRO_safeFree(m_var.pData);	//  2014/05/13  
}

int  tmpHandler_getDynBmps(void* p0, void* p1, void* p2)
{
	int				iErr = -1;
	COMMON_PARAM* pCommonParam0 = (COMMON_PARAM*)p0;
	COMMON_PARAM* pCommonParam1 = (COMMON_PARAM*)p1;
	MIS_MSGU* pMsg = (MIS_MSGU*)p2;

	unsigned  int		uiTranNo = 0;
	BOOL				bRemove = FALSE;

	if (!pCommonParam0)  return  0;
	uiTranNo = (unsigned  int)pCommonParam0->p1;
	bRemove = (BOOL)pCommonParam0->p2;

	if (pMsg->uiType != CONST_misMsgType_input) {
		iErr = 0;  goto  errLabel;
	}
	if (!(isUcFlgRouteTalkData(pMsg->input.ucFlg) 
		//|| isUcFlgTalkData(pMsg->input.ucFlg)
		)) {
		iErr = 0;  goto  errLabel;
	}
	if (!isUcFlgResp(pMsg->input.ucFlg)) {
		iErr = 0;  goto  errLabel;
	}
	if (pMsg->input.uiTranNo != uiTranNo) {
		iErr = 0;  goto  errLabel;
	}
	IM_CONTENTU* pContent; pContent = M_getMsgContent(pMsg->input.ucFlg, &pMsg->input.data);
	if (pContent->uiType != CONST_imCommType_retrieveDynBmps) {
		iErr = 0;  goto  errLabel;
	}
	if (!bRemove) {
		QIS_dynBmp_info* pDynBmps = NULL;
		unsigned  int		maxCnt = 0;
		unsigned  int* puiCnt = NULL;

		if (!pCommonParam1)  goto  errLabel;
		pDynBmps = (QIS_dynBmp_info*)pCommonParam1->p0;
		maxCnt = (unsigned  int)pCommonParam1->p1;
		puiCnt = (unsigned  int*)pCommonParam1->p2;


		if (!pDynBmps)  goto  errLabel;
		//
		if (*puiCnt >= maxCnt) {
			iErr = 1;  goto  errLabel;
		}
		//
		int  n = min(maxCnt - *puiCnt, pContent->retrieveDynBmps.usCnt);
		memcpy(pDynBmps + *puiCnt, pContent->retrieveDynBmps.mems, n * sizeof(QIS_dynBmp_info));
		*puiCnt += n;
	}
	else {
		iErr = 1;  goto  errLabel;
	}


	iErr = 0;
errLabel:
	return  iErr;
}


int  fillImObjs_selectRemoteVideo(HWND  hDlg, void* pVarParam, QListWidget* IDC_LIST0)
{
	int  iRet = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = (MIS_CNT*)pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  return  -1;

	unsigned  int	maxCnt = 32;
	QIS_dynBmp_info* pDynBmps = NULL;
	int				size;
	unsigned  int	cnt = 0;

	DLG_objs_var* pVar = (DLG_objs_var*)pVarParam;
	if (!IsWindow(pVar->guiData.param.hCurTalk))  goto  errLabel;		//  2013/06/10
	DLG_TALK_var* pDlgTalkVar; pDlgTalkVar = (DLG_TALK_var*)pVar->guiData.param.pCurVar;	//  getDlgTalkVar(  pVar->guiData.param.hCurTalk  );
	if (!pDlgTalkVar)  goto  errLabel;
	DLG_TALK_var* pMgrVar; pMgrVar = (DLG_TALK_var*)pVar->guiData.param.pMgrVar;	//  pDlgTalkVar;
	if (!pMgrVar)  goto  errLabel;


	//  2014/05/30
	TALKER_shadow_mgr* pShadowMgr; pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
	if (!pShadowMgr)  goto  errLabel;


	//
	size = maxCnt * sizeof(QIS_dynBmp_info);
	pVar->uiSize_pData = size;
	pVar->iType_pData = CONST_iType_pData_dynBmps;
	pVar->pData = (QIS_dynBmp_info*)mymalloc(size);
	if (!pVar->pData)  goto  errLabel;
	memset(pVar->pData, 0, size);
	pDynBmps = (QIS_dynBmp_info*)pVar->pData;

	//
	//if  (  bSupported_queryRemoteVideo(  )  )  
	{
		//  2014/05/03
		unsigned  int  uiTranNo = 0;
		if (sndRetrieveDynBmpsReqToMsgr_qmc(pMisCnt, TRUE, 0, FALSE, NULL, FALSE, &pMgrVar->addr.idInfo, &uiTranNo))  goto  errLabel;
		pShadowMgr->selectRemoteVideo.uiTranNo = uiTranNo;	//  2014/09/04
		//
		HWND  hParent = pVar->guiData.param.hCurTalk;
		//  2016/08/09
		if (IsWindow(pVar->m_hParent))  hParent = pVar->m_hParent;
		//  2015/06/05
		if (!pProcInfo->bUse_imObjView_as_guiWnd()) {
			if (bApp_ts_3d(pQyMc)) {
				GBuf_d3d_isCli* pGBuf = (GBuf_d3d_isCli*)pQyMc->pGBuf_d3d;
				if (!pGBuf)  goto  errLabel;
				if (!IsWindow(pGBuf->hWall_d3d))  goto  errLabel;
				hParent = pGBuf->hWall_d3d;
			}
		}


		//
		if (showProgress(&pQyMc->gui.progress, &pQyMc->cusRes, hParent, _T("Please waiting"), NULL, 30, -1, uiTranNo) != IDOK) {
			goto  errLabel;
		}

		COMMON_PARAM	commonParam3_i;
		COMMON_PARAM	commonParam3_o;
		BOOL			bRemove = FALSE;

		MACRO_makeCommonParam3(0, (void*)uiTranNo, (void*)bRemove, commonParam3_i);
		MACRO_makeCommonParam3((void*)pDynBmps, (void*)maxCnt, (void*)&cnt, commonParam3_o);
		qTraverse(pMgrVar->m_pProcessQ, tmpHandler_getDynBmps, &commonParam3_i, &commonParam3_o);
		//
		bRemove = TRUE;
		MACRO_makeCommonParam3(0, (void*)uiTranNo, (void*)bRemove, commonParam3_i);
		qRemoveMsg(pMgrVar->m_pProcessQ, tmpHandler_getDynBmps, &commonParam3_i, NULL);
	}

	//
	//HWND	hCtl = GetDlgItem(hDlg, pVar->guiData.iIDC_LIST0);

	int		tmpiRet;

	//if  (  bSupported_queryRemoteVideo(  )  )  
	{
		int  n = cnt;
		if (n < 0)  goto  errLabel;
		pVar->uiSize_pData_items = n * sizeof(QY_COLUMNINFO);
		pVar->pData_items = mymalloc(pVar->uiSize_pData_items);
		if (!pVar->pData_items)  goto  errLabel;
		memset(pVar->pData_items, 0, pVar->uiSize_pData_items);

		pVar->nItems = n;
		QY_COLUMNINFO* pColumns = (QY_COLUMNINFO*)pVar->pData_items;
		for (n = 0; ; n++) {
			if (n >= cnt)  break;
			//
			QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);

			_sntprintf(pColumns[n].label, mycountof(pColumns[n].label), _T("%s %d"), qyGetDesByType1(pTable, pDynBmps[n].qisResObj.resObj.uiObjType), (int)pDynBmps[n].qisResObj.resObj.usIndex_obj);
			if (pDynBmps[n].qisResObj.resObj.usHelp_subIndex)  _sntprintf(pColumns[n].label, mycountof(pColumns[n].label), _T("%s.%d"), pColumns[n].label, (int)pDynBmps[n].qisResObj.resObj.usHelp_subIndex);
			_sntprintf(pColumns[n].label, mycountof(pColumns[n].label), _T("%s %s %s"), pColumns[n].label, pDynBmps[n].name, pDynBmps[n].cusName);
			//
			if (tmpF_bViewRemoteVideo(&pShadowMgr->vwRuleCmd_manual, pDynBmps[n].qisResObj.resObj.uiObjType, pDynBmps[n].qisResObj.resObj.usIndex_obj, pDynBmps[n].qisResObj.resObj.usHelp_subIndex))  pColumns[n].lParam = TRUE;
			if (pColumns[n].lParam)  _sntprintf(pColumns[n].label, mycountof(pColumns[n].label), _T("%s ( %s )"), pColumns[n].label, getResStr(0, &pQyMc->cusRes, CONST_resId_manuallyStarted));
			//
			//tmpiRet = SendMessage(hCtl, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)pColumns[n].label);

			QListWidgetItem* item = new QListWidgetItem(QString::fromWCharArray(pColumns[n].label));
	        IDC_LIST0->addItem(item);

		}


	}


	iRet = 0;
errLabel:

	return  iRet;
}

int  fillImObjs(HWND  hDlg, void* pVar, QListWidget* IDC_LIST0)
{
	int				iErr = -1;
	DLG_objs_var& m_var = *(DLG_objs_var*)pVar;
	QY_MC* pQyMc = QY_GET_GBUF();
	QM_dbFuncs& g_dbFuncs = *pQyMc->p_g_dbFuncs;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;
	QY_OBJ_DB* pObjDb = pFuncs->pf_getProcedObjDb(pQyMc, 0, pQyMc->iDsnIndex_mainSys);
	if (!pObjDb)  return  -1;
	//TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	//CDBVariant		varVals[10];

	switch (m_var.guiData.param.uiType) {
	/*case  CONST_objType_messenger:

		g_dbFuncs.pf_fillImObjs_msgr(hDlg, pVar, pObjDb->pDb);
		break;

	case  CONST_objType_imGrp:

		g_dbFuncs.pf_fillImObjs_grp(hDlg, pVar, pObjDb->pDb);
		break;*/

#ifdef  __isCli__
	case  CONST_objType_selectRemoteVideo:
		if (fillImObjs_selectRemoteVideo(hDlg, pVar, IDC_LIST0))  goto  errLabel;
		break;
	//case  CONST_objType_selectADev:
	//	fillImObjs_selectADev(hDlg, pVar);
	//	break;
	//case  CONST_objType_selectVDev:
	//	fillImObjs_selectVDev(hDlg, pVar);
	//	break;
	//case  CONST_objType_selectLayoutType:
	//	fillImObjs_selectLayoutType(hDlg, pVar);
	//	break;
	//case  CONST_objType_selectIpc:
	//	fillImObjs_selectIpc(hDlg, pVar);
	//	break;
	//case  CONST_objType_selOneBig:
	//	fillImObjs_selOneBig(hDlg, pVar);
	//	break;
	//case  CONST_objType_selectRemotePtz:  //  2016/07/19
	//	fillImObjs_selectRemotePtz(hDlg, pVar);
	//	break;
#endif
	default:
		break;
	}


	iErr = 0;
errLabel:
	return  iErr;
}


BOOL  dlgObjs_bFillContent(HWND  hDlg, void* pVar, int  iObjType, QListWidget* IDC_LIST0)
{
	BOOL	bRet = FALSE;

	if (!pVar)  return  FALSE;
	DLG_objs_var& m_var = *(DLG_objs_var*)pVar;


	/*HWND	hCtl = GetDlgItem(hDlg, m_var.guiData.iIDC_LIST0);

	SendMessage(hCtl, LB_RESETCONTENT, 0, 0);*/
	m_var.usItemCount = 0;

	int				iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	int				idc_hidden = 0;
	BOOL			bHidden;
	int				idc;
	MIS_CNT* pMisCnt = NULL;

	m_var.pMisCnt = getMisCntByName(pProcInfo, _T(""));
	pMisCnt = (MIS_CNT*)m_var.pMisCnt;

	m_var.guiData.param.uiType = iObjType;

	switch (m_var.guiData.param.uiType) {
	/*case  CONST_objType_messenger:
#ifdef  __NOTSUPPORT_DB__
		qmObjQTraverse(0, pMisCnt->pObjQ, (PF_commonHandler)tmpHandler_printQmObjQ, hDlg, &m_var);
#else
		fillImObjs(hDlg, pVar);
#endif
		idc_hidden = m_var.guiData.iIDC_BUTTON_contact;
		break;
	case  CONST_objType_imGrp:
#ifdef  __NOTSUPPORT_DB__
		qmObjQTraverse(0, pMisCnt->pObjQ, (PF_commonHandler)tmpHandler_printQmObjQ, hDlg, &m_var);
#else
		fillImObjs(hDlg, pVar);
#endif
		idc_hidden = m_var.guiData.iIDC_BUTTON_group;
		break;*/

	case  CONST_objType_selectRemoteVideo:
		if (fillImObjs(hDlg, pVar, IDC_LIST0)) {
			goto  errLabel;
		}
		break;

	//case  CONST_objType_selectADev:			//  2013/04/04
	//case  CONST_objType_selectVDev:			//  2013/04/04
	//	fillImObjs(hDlg, pVar);
	//	break;

	//case  CONST_objType_selectLayoutType:	//  2013/06/24
	//case  CONST_objType_selectRemotePtz:	//  2016/07/19
	//	fillImObjs(hDlg, pVar);
	//	break;
	//case  CONST_objType_selectIpc:
	//	fillImObjs(hDlg, pVar);
	//	break;
	//case  CONST_objType_selOneBig:
	//	fillImObjs(hDlg, pVar);
	//	break;
	default:
		//if (m_var.guiData.param.ucbActiveTalker) {		//  2012/04/21
		//	if (!pMisCnt)  goto  errLabel;
		//	qTraverse(&pMisCnt->talkingFriendQ, (PF_commonHandler)tmpHandler_showActiveTalker, hDlg, &m_var);

		//	break;
		//}

		//qTraverse(&pProcInfo->imMsgLogQ, (PF_commonHandler)tmpHandler_showImMsgLogQ, hDlg, &m_var);
		//idc_hidden = m_var.guiData.iIDC_BUTTON_status;
		break;
	}

	idc = m_var.guiData.iIDC_BUTTON_contact;
	bHidden = idc_hidden == idc;
	ShowWindow(GetDlgItem(hDlg, idc), bHidden ? SW_HIDE : SW_SHOW);

	idc = m_var.guiData.iIDC_BUTTON_group;
	bHidden = idc_hidden == idc;
	ShowWindow(GetDlgItem(hDlg, idc), bHidden ? SW_HIDE : SW_SHOW);

	idc = m_var.guiData.iIDC_BUTTON_status;
	bHidden = idc_hidden == idc;
	ShowWindow(GetDlgItem(hDlg, idc), bHidden ? SW_HIDE : SW_SHOW);

	bRet = TRUE;

errLabel:

	return  bRet;
}


int CDlgObjs_ts_qt::dlgObjs_OnLbnSelchangeList0(/*HWND  hDlg, void* pVarParam*/)
{
	int  iErr = -1;

	DLG_objs_var* pVar = &this->m_var;
	QY_MC* pQyMc = QY_GET_GBUF();

	/*
	CQyMalloc	mallocObj;
	TCHAR* pT = NULL;

	HWND	hCtrl = GetDlgItem(hDlg, pVar->guiData.iIDC_LIST0);

	int  iItemSelected = SendMessage(hCtrl, LB_GETCURSEL, 0, 0);
	if (iItemSelected == LB_ERR)  goto  errLabel;

	int  len = SendMessage(hCtrl, LB_GETTEXTLEN, iItemSelected, 0);
	if (!len)  goto  errLabel;
	len++;

	pT = (TCHAR*)mallocObj.mallocf(sizeof(TCHAR) * len);
	if (!pT)  goto  errLabel;
	SendMessage(hCtrl, LB_GETTEXT, iItemSelected, (LPARAM)pT);
	*/
	QList<QListWidgetItem*> selectedItems = ui->IDC_LIST0->selectedItems();
	bool haveSelect = false;
	int iItemSelected = -1;
	foreach(QListWidgetItem * item, selectedItems) {

		haveSelect = true;
		iItemSelected = ui->IDC_LIST0->row(item);
	}

	if (!haveSelect) goto errLabel;


	switch (pVar->guiData.param.uiType) {
	case  CONST_objType_selectRemoteVideo: {
		//QY_DMITEM	   *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_remoteVideoTable  );
		QY_COLUMNINFO* pColumns = (QY_COLUMNINFO*)pVar->pData_items;
		int				  n;

		//if (iItemSelected < 0 || iItemSelected >= pVar->nItems)  goto  errLabel;

		if (pColumns[iItemSelected].lParam) {
			//SetDlgItemText(hDlg, pVar->guiData.iIDOK, getResStr(0, &pQyMc->cusRes, CONST_resId_stop));
			ui->btnOK->setText(QString::fromWCharArray(getResStr(0, &pQyMc->cusRes, CONST_resId_stop)));

		}
		else {
			//SetDlgItemText(hDlg, pVar->guiData.iIDOK, getResStr(0, &pQyMc->cusRes, CONST_resId_start));
			ui->btnOK->setText(QString::fromWCharArray(getResStr(0, &pQyMc->cusRes, CONST_resId_start)));
		}
	}break;
	default:
		break;
	}

	iErr = 0;
errLabel:
	return  iErr;
}


bool CDlgObjs_ts_qt::OnInitDialog()
{
	int		iErr = -1;

#ifdef  __APP_qyMc_touchscreen__
	//  2011/03/12
	makeDlgResizable(this->m_hWnd);
#endif

	//CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
#ifdef  __APP_qyMc_touchscreen__
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
#endif

	QY_MC* pQyMc = QY_GET_GBUF();
	HWND	hDlg = (HWND)this->winId();
	//dlgLayout_objs(hDlg, &m_var.guiData);

	//if (setModalWnd(pQyMc, hDlg))  goto  errLabel;


	//  HWND	hDlg	=	this->m_hWnd;
#ifdef  __APP_qyMc_touchscreen__
	{
		RECT	rc;
		int		w, h;
		HWND	hFrame = pQyMc->gui.hMainWnd;
		if (!hFrame)  goto  errLabel;
		::GetWindowRect(hFrame, &rc);
		w = rc.right - rc.left;
		h = rc.bottom - rc.top;
		::MoveWindow(hDlg, rc.left, rc.top, w, h, TRUE);

	}
#else
#if  10
	{
		RECT	rc;
		int		w, h;
		int		x;
		::GetWindowRect(hDlg, &rc);
		x = rc.left;
		w = rc.right - rc.left;
		h = rc.bottom - rc.top;
#if  10
		if (w < 640) {
			x = rc.left;	//    -  (  640  -  w  )  /  2;
			w = 640;
		}
		if (h < 480) {
			h = 480;
		}
#endif
		::MoveWindow(hDlg, x, rc.top, w, h, TRUE);
	}
#endif
#endif

	//  sizeAllControls_dlgObjs(  hDlg,  &m_var.guiData  );

	//  SetWindowText(  _T(  "Select"  )  );
	//cusDlgRes(0, &pQyMc->cusRes, hDlg, IDD_objs);

	m_var.guiData.bInited = TRUE;


	// TODO:  Add extra initialization here
	DLG_guiData_objs* pGuiData = &m_var.guiData;
	if (!dlgObjs_bFillContent(hDlg, &m_var, pGuiData->param.uiType, ui->IDC_LIST0))  goto  errLabel;

	//QListWidgetItem* item = new QListWidgetItem("ÏîÄ¿2");
	//ui->IDC_LIST0->addItem(item);


	iErr = 0;

errLabel:

	if (!m_var.guiData.bInited || iErr) {
		//  EndDialog(  -1  );
		//PostMessage(WM_CLOSE);
	}

	return true;
}



int CDlgObjs_ts_qt::dlgObjs_OnOK(HWND  hDlg, void* pVarParam)
{
	int		iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();

	if (!pVarParam)  return  -1;
	DLG_objs_var& m_var = *(DLG_objs_var*)pVarParam;
	MIS_CNT* pMisCnt = (MIS_CNT*)m_var.pMisCnt;

	// TODO: Add your specialized code here and/or call the base class
	//
	/*
	CQyMalloc	mallocObj;
	TCHAR* pT = NULL;

	HWND	hCtrl = GetDlgItem(hDlg, m_var.guiData.iIDC_LIST0);

	int			iItemSelected = SendMessage(hCtrl, LB_GETCURSEL, 0, 0);
	if (iItemSelected < 0)  goto  errLabel;

	int		len = SendMessage(hCtrl, LB_GETTEXTLEN, iItemSelected, 0);
	if (len < 0)  goto  errLabel;
	len++;

	pT = (TCHAR*)mallocObj.mallocf(sizeof(TCHAR) * len);
	if (!pT)  goto  errLabel;
	SendMessage(hCtrl, LB_GETTEXT, iItemSelected, (LPARAM)pT);
	*/

	QList<QListWidgetItem*> selectedItems = ui->IDC_LIST0->selectedItems();
	bool haveSelect = false;
	int iItemSelected = -1;
	foreach(QListWidgetItem * item, selectedItems) {

		haveSelect = true;
		iItemSelected = ui->IDC_LIST0->row(item);
	}

	if (!haveSelect) goto errLabel;

	char						buf[32];
	QY_MESSENGER_ID				idInfo_selected;
	TCHAR* pT1;


	switch (m_var.guiData.param.uiType) {
	//case  CONST_objType_messenger:
	//case  CONST_objType_imGrp:
	//	pT1 = _tcschr(pT, _T(' '));
	//	if (!pT1)  goto  errLabel;
	//	*pT1 = 0;

	//	myTChar2Str(pT, buf, mycountof(buf));
	//	idStr2Info(buf, &idInfo_selected);
	//	//
	//	if (idInfo_selected.ui64Id == pMisCnt->idInfo.ui64Id)  goto  errLabel;
	//	//
	//	m_var.guiData.param.o.ui64Id_selected = idInfo_selected.ui64Id;
	//	break;
	case  CONST_objType_selectRemoteVideo: {
		//  2013/02/13
		QY_COLUMNINFO* pColumns = (QY_COLUMNINFO*)m_var.pData_items;
		if (iItemSelected < 0 || iItemSelected >= m_var.nItems)  goto  errLabel;

		m_var.guiData.param.o.iVal_selected = pColumns[iItemSelected].type;
		m_var.guiData.param.o.iSel = iItemSelected;	//  2014/05/13

		//
		if (!m_var.guiData.param.pObjBuf_selected)  goto  errLabel;
		if (m_var.guiData.param.uiSize_pObjBuf_selected < sizeof(DYN_BMP_RULE))  goto  errLabel;

		QIS_dynBmp_info* pDynBmps = (QIS_dynBmp_info*)m_var.pData;
		DYN_BMP_RULE* pDynBmpRule_selected = (DYN_BMP_RULE*)m_var.guiData.param.pObjBuf_selected;
		//  memcpy(  m_var.guiData.param.pObjBuf_selected,   &pDynBmps[iItemSelected],  sizeof(  QIS_dynBmp_info  )  );
		memcpy(&pDynBmpRule_selected->dynBmp, &pDynBmps[iItemSelected], sizeof(QIS_res_obj));
		safeTcsnCpy(pDynBmps[iItemSelected].name, pDynBmpRule_selected->name, mycountof(pDynBmpRule_selected->name));
		safeTcsnCpy(pDynBmps[iItemSelected].cusName, pDynBmpRule_selected->cusName, mycountof(pDynBmpRule_selected->cusName));

	}
	break;
	//case  CONST_objType_selectLayoutType:
	//case  CONST_objType_selOneBig: {
	//	//
	//	pT1 = _tcschr(pT, ',');
	//	if (!pT1)  goto  errLabel;
	//	*pT1 = 0;
	//	myTChar2Utf8(pT, buf, mycountof(buf));
	//	QY_MESSENGER_ID idInfo;
	//	idStr2Info(buf, &idInfo);
	//	m_var.guiData.param.o.ui64Id_selected = idInfo.ui64Id;
	//	pT1++;
	//	m_var.guiData.param.o.iVal_selected = _ttol(pT1);

	//	//
	//}
	//							 break;

	//case  CONST_objType_selectIpc: {
	//	//
	//	pT1 = _tcschr(pT, ',');
	//	if (!pT1)  goto  errLabel;
	//	*pT1 = 0;
	//	//myTChar2Utf8(pT, buf, mycountof(buf));
	//	m_var.guiData.param.o.iVal_selected = _ttol(pT);

	//	//
	//}
	//							 break;

	//case  CONST_objType_selectRemotePtz: {
	//	//  2013/06/24
	//	QY_COLUMNINFO* pColumns = (QY_COLUMNINFO*)m_var.pData_items;
	//	if (iItemSelected < 0 || iItemSelected >= m_var.nItems)  goto  errLabel;

	//	m_var.guiData.param.o.iVal_selected = pColumns[iItemSelected].type;
	//	//
	//	//
	//	if (!m_var.guiData.param.pObjBuf_selected)  goto  errLabel;
	//	if (m_var.guiData.param.uiSize_pObjBuf_selected < sizeof(DYN_BMP_RULE))  goto  errLabel;

	//	//
	//	QIS_dynBmp_info* pDynBmps = (QIS_dynBmp_info*)m_var.pData;
	//	DYN_BMP_RULE* pDynBmpRule_selected = (DYN_BMP_RULE*)m_var.guiData.param.pObjBuf_selected;
	//	//
	//	pDynBmpRule_selected->dynBmp.resObj.uiObjType = pColumns[iItemSelected].type;
	//	//  2016/07/24
	//	if (pDynBmpRule_selected->dynBmp.resObj.uiObjType == CONST_objType_rtspStream) {
	//		pDynBmpRule_selected->dynBmp.resObj = pDynBmps[iItemSelected].qisResObj.resObj;
	//	}


	//}
	//								   break;

	//case  CONST_objType_selectADev: {
	//	if (!m_var.guiData.param.p0)  goto  errLabel;
	//	CAP_STUFF& gcap = *(CAP_STUFF*)m_var.guiData.param.p0;
	//	if (iItemSelected < 0 || iItemSelected >= mycountof(gcap.old_audioDevices.mems))  goto  errLabel;
	//	m_var.guiData.param.o.iSel = iItemSelected;
	//}
	//							  break;
	//case  CONST_objType_selectVDev: {
	//	if (!m_var.guiData.param.p0)  goto  errLabel;
	//	CAP_STUFF& gcap = *(CAP_STUFF*)m_var.guiData.param.p0;
	//	if (iItemSelected < 0 || iItemSelected >= mycountof(gcap.rgpmVideoMenu))  goto  errLabel;
	//	m_var.guiData.param.o.iSel = iItemSelected;
	//}
	//							  break;
	default:

		//  2012/04/21
		//if (m_var.guiData.param.ucbActiveTalker) {
		//	pT1 = _tcschr(pT, _T(' '));
		//	if (!pT1)  goto  errLabel;
		//	*pT1 = 0;

		//	myTChar2Str(pT, buf, mycountof(buf));
		//	idStr2Info(buf, &idInfo_selected);
		//	//
		//	if (idInfo_selected.ui64Id == pMisCnt->idInfo.ui64Id)  goto  errLabel;
		//	//
		//	m_var.guiData.param.o.ui64Id_selected = idInfo_selected.ui64Id;
		//	break;
		//}

		//pT1 = _tcschr(pT, _T(' '));
		//if (!pT1)  goto  errLabel;
		//pT1++;
		//pT = pT1;

		//pT1 = _tcschr(pT, _T('>'));
		//if (!pT1)  goto  errLabel;
		//*pT1 = 0;  pT1++;

		//tTrim(pT);
		//myTChar2Str(pT, buf, mycountof(buf));
		//idStr2Info(buf, &idInfo_selected);
		//if (idInfo_selected.ui64Id == pMisCnt->idInfo.ui64Id) {
		//	pT = pT1;
		//	pT1 = _tcschr(pT, _T(':'));
		//	if (!pT1)  goto  errLabel;
		//	*pT1 = 0;

		//	myTChar2Str(pT, buf, mycountof(buf));

		//	idStr2Info(buf, &idInfo_selected);
		//}
		//m_var.guiData.param.o.ui64Id_selected = idInfo_selected.ui64Id;
		break;
	}

	iErr = 0;
errLabel:
	return  iErr;

}
