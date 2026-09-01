#include "WinRuleSet.h"
#include <QPainter>
#include <QtCore/qmath.h>
#include <qradiobutton.h>
#include <QWidget>

#include	"ctxQmc.h"
#include	"myDb.h"
#include	"funcsForIsCliHelp.h"

//
#define SHADOW_WIDTH 4 // 阴影边框宽度;

namespace {
	//WinRuleSet* dlg = nullptr;
}

WinRuleSet::WinRuleSet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(this->windowFlags() | Qt::Dialog);

	this->setWindowFlags(Qt::FramelessWindowHint);
	//this->setAttribute(Qt::WA_DeleteOnClose);


	av_radAuto = new QRadioButton(this);

	av_radAuto->setText(u8"自动接收");
	//radio1->setChecked(true);
	//radio->setEnabled(false);
	connect(av_radAuto, &QRadioButton::toggled, this, &WinRuleSet::onVideoRule);
	//dev_videos_ << radio;
	ui.horizontalLayout_2->addWidget(av_radAuto);

	av_radManual = new QRadioButton(this);
	av_radManual->setText(u8"手动接收");
	//radio->setEnabled(false);
	connect(av_radManual, &QRadioButton::toggled, this, &WinRuleSet::onVideoRule);
	//dev_videos_ << radio;
	ui.horizontalLayout_2->addWidget(av_radManual);

	//

}

WinRuleSet::~WinRuleSet()
{
	//dlg = nullptr;
	int  ii = 0;
}

int WinRuleSet::showDialog(QWidget* parent,  unsigned  __int64 ui64Id)
{
	int  iErr = -1;
	if (!ui64Id) return -1;

#if  0
	if (!dlg)
	{
		dlg = new WinRuleSet();

	}
	dlg->show();
	dlg->activateWindow();
#endif

	WinRuleSet  dlg;
	
	//
	dlg.m_var.idInfo.ui64Id = ui64Id;
	if (dlg.init())  goto  errLabel;
	
	//
	int tmpiRet = dlg.exec();

	iErr = 0;

errLabel:

	return  iErr;

}


int  WinRuleSet::init()
{
	int  iErr = -1;

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	QM_dbFuncs& g_dbFuncs = *(QM_dbFuncs*)pQyMc->p_g_dbFuncs;
	FUNCS_for_isCliHelp* pFuncs = (FUNCS_for_isCliHelp*)pProcInfo->get_pFuncs_for_isCliHelp();

	CQnmDb  db;
	if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;

	//
	REFRESH_imObjRules_req	req;
	QY_MESSENGER_ID			idInfo_related;

	//  先取全局策略
	idInfo_related.ui64Id = 0;
	if (g_dbFuncs.pf_bGetImObjRulesReq(db.m_pDbMem->pDb, pQyMc->cfg.db.iDbType, _T(""), 0, &idInfo_related, NULL, 0, &req)) {
		pFuncs->pf_imObjRulesReq2ImRules(&req, &m_var.imRules);
	}

	//  再取messenger的策略
	if (g_dbFuncs.pf_bGetImObjRulesReq(db.m_pDbMem->pDb, pQyMc->cfg.db.iDbType, _T(""), 0, &m_var.idInfo, NULL, 0, &req)) {
		pFuncs->pf_imObjRulesReq2Rules(&req, &m_var.idInfo, &m_var.rules);
	}

	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	if (memcmp(&pMisCnt->imRules, &m_var.imRules, sizeof(pMisCnt->imRules))) {
		memcpy(&pMisCnt->imRules, &m_var.imRules, sizeof(pMisCnt->imRules));
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("Warning: dlgImObjRule: imRules not correct"));
#endif
	}

	//  2010/09/24
	QM_OBJQ_MEM				mem;
	QMEM_MESSENGER_CLI* pQMem;
	if (!pFuncs->pf_findQMemByKey(0, pMisCnt->pObjQ, &m_var.idInfo, &mem)) {
		pQMem = (QMEM_MESSENGER_CLI*)mem.pQMemObj;
		if (pQMem) {
			if (memcmp(&pQMem->rules, &m_var.rules, sizeof(pQMem->rules))) {
				memcpy(&pQMem->rules, &m_var.rules, sizeof(pQMem->rules));
#ifdef  __DEBUG__
				traceLog((TCHAR*)_T("Warning: dlgImObjRule: rules is not correct"));
#endif
			}
		}
	}

	char	buf[128];
	if (!av_radManual) goto errLabel;
	if (!av_radAuto) goto errLabel;
	
	if (m_var.rules.uiCmd_autoAnswer_av == CONST_ruleCmd_permit) av_radAuto->setChecked(true);
	else av_radManual->setChecked(true);



#if  0
	idc = IDC_CHECK_shareWebcamInConference;
	((CButton*)GetDlgItem(idc))->SetCheck(m_var.imRules.conferenceId_shareWebcam.ui64Id == m_var.idInfo.ui64Id ? 1 : 0);
	idc = IDC_EDIT_conferenceId_shareWebcam;
	_snprintf(buf, mycountof(buf), "%I64u", m_var.imRules.conferenceId_shareWebcam.ui64Id);
	SetDlgItemText(idc, CString(buf));
	idc = IDC_CHECK_noLocalVideoInThisConference;
	((CButton*)GetDlgItem(idc))->SetCheck(m_var.imRules.ucbNoLocalVideoInThisConference ? 1 : 0);
	idc = IDC_CHECK_distinguishSharedWebcams;
	((CButton*)GetDlgItem(idc))->SetCheck(m_var.imRules.ucbDistinguishSharedWebcams ? 1 : 0);

	idc = IDC_EDIT_conferenceId_shareWebcam;
	GetDlgItem(idc)->EnableWindow(FALSE);

	//
	QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_ruleCmdTable_autoAnswer);
	QY_DMITEM* pItem;
	CComboBox* pCombo;

	pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_autoAnswer_av);
	for (pItem = pTable; pItem->type != -1; pItem++) {
		pCombo->InsertString(-1, pItem->des);
	}
	pCombo->SelectString(-1, qyGetDesByType1(pTable, m_var.rules.uiCmd_autoAnswer_av));

	pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_autoAnswer_screen);
	for (pItem = pTable; pItem->type != -1; pItem++) {
		pCombo->InsertString(-1, pItem->des);
	}
	pCombo->SelectString(-1, qyGetDesByType1(pTable, m_var.rules.uiCmd_autoAnswer_screen));

	pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_autoAnswer_mediaFile);
	for (pItem = pTable; pItem->type != -1; pItem++) {
		pCombo->InsertString(-1, pItem->des);
	}
	pCombo->SelectString(-1, qyGetDesByType1(pTable, m_var.rules.uiCmd_autoAnswer_mediaFile));
#endif


	iErr = 0;
errLabel:

	return  iErr;
}

void WinRuleSet::closeEvent(QCloseEvent* ev)
{
	this->hide();
	ev->accept();
}

void WinRuleSet::onVideoRule(bool b)
{
	int  iErr = -1;

	if (!b)
	{
		return;
	}
	//TODO:选中了一个视频设备
	QRadioButton* button = (QRadioButton*)sender();
	QString str = button->text();
	int o = 1;
	
}

void WinRuleSet::on_btnAccept_clicked()
{
		int				iErr = -1;
		QY_MC* pQyMc = QY_GET_GBUF();
		MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
		FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);

		//CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_autoAnswer_av);
		QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_ruleCmdTable_autoAnswer);
		//  QY_DMITEM	*	pItem;
		//CString			str;
		QY_im_rules		imRules;
		QY_imObj_rules	rules;
		int				i;
		int				iRuleType = 0;
		unsigned  int	uiCmd = 0;
		int				idc;
		TCHAR			tBuf[256];
		char			buf[128];
		unsigned  char	ucbVal;

		memset(&imRules, 0, sizeof(imRules));
		memset(&rules, 0, sizeof(rules));

		//
#if  0
		idc = IDC_EDIT_conferenceId_shareWebcam;
		GetDlgItemText(idc, tBuf, mycountof(tBuf));  myTChar2Utf8(tBuf, buf, mycountof(buf));
		idStr2Info(buf, &imRules.conferenceId_shareWebcam);

		idc = IDC_CHECK_noLocalVideoInThisConference;
		ucbVal = FALSE;
		if (((CButton*)GetDlgItem(idc))->GetCheck() == BST_CHECKED) {
			ucbVal = TRUE;
		}
		imRules.ucbNoLocalVideoInThisConference = ucbVal;

		idc = IDC_CHECK_distinguishSharedWebcams;
		ucbVal = FALSE;
		if (((CButton*)GetDlgItem(idc))->GetCheck() == BST_CHECKED) {
			ucbVal = TRUE;
		}
		imRules.ucbDistinguishSharedWebcams = ucbVal;

		//
		idc = IDC_COMBO_autoAnswer_av;
		GetDlgItemText(idc, str);
		rules.uiCmd_autoAnswer_av = qyGetTypeByDes(pTable, str);

		idc = IDC_COMBO_autoAnswer_screen;
		GetDlgItemText(idc, str);
		rules.uiCmd_autoAnswer_screen = qyGetTypeByDes(pTable, str);

		idc = IDC_COMBO_autoAnswer_mediaFile;
		GetDlgItemText(idc, str);
		rules.uiCmd_autoAnswer_mediaFile = qyGetTypeByDes(pTable, str);
#endif
		//
		if (av_radAuto->isChecked()) rules.uiCmd_autoAnswer_av = CONST_ruleCmd_permit;

		//
		if (memcmp(&imRules, &m_var.imRules, sizeof(imRules))
			|| memcmp(&rules, &m_var.rules, sizeof(rules)))
		{
			CQyMalloc					mallocObj_pStream;
			IM_L_STREAM* pStream = (IM_L_STREAM*)mallocObj_pStream.mallocf(sizeof(IM_L_STREAM));
			if (!pStream)  goto  errLabel;

			REFRESH_imObjRules_req	req;
			MACRO_prepareForTran();
			int					len;

#if  0
			if (!pFuncs->pf_bMessengerOnline((QY_MC*)pProcInfo->pQyMc)) {
				myMessageBox(m_hWnd, _T("Failed: Messenger is offline"), _T(""), MB_OK);
				return;
			}
#endif

			//
			memset(&req, 0, sizeof(req));
			req.uiType = CONST_imCommType_refreshImObjRulesReq;
			i = 0;

#if  0
			if (imRules.conferenceId_shareWebcam.ui64Id != m_var.imRules.conferenceId_shareWebcam.ui64Id) {
				if (i >= mycountof(req.mems)) {
					qyShowHint(getResStr(0, &pQyMc->cusRes, CONST_resId_autoAnswerlimited));
					goto  errLabel;
				}
				//
				iRuleType = CONST_ruleType_conferenceId_shareWebcam;
				uiCmd = imRules.conferenceId_shareWebcam.ui64Id ? CONST_ruleCmd_permit : 0;
				//
				req.mems[i].idInfo_related.ui64Id = 0;
				req.mems[i].uiRuleType = iRuleType;
				req.mems[i].uiCmd = uiCmd;
				//  req.mems[i].l64Val  =  imRules.conferenceId_shareWebcam.ui64Id;
				_sntprintf(req.mems[i].wDesc, mycountof(req.mems[i].wDesc), _T("%I64u"), imRules.conferenceId_shareWebcam.ui64Id);
				i++;
			}
			if (imRules.ucbNoLocalVideoInThisConference != m_var.imRules.ucbNoLocalVideoInThisConference) {
				if (i >= mycountof(req.mems)) {
					qyShowHint(getResStr(0, &pQyMc->cusRes, CONST_resId_autoAnswerlimited));
					goto  errLabel;
				}
				//
				iRuleType = CONST_ruleType_ucbNoLocalVideoInThisConference;
				uiCmd = imRules.ucbNoLocalVideoInThisConference ? CONST_ruleCmd_permit : 0;
				//
				req.mems[i].idInfo_related.ui64Id = 0;
				req.mems[i].uiRuleType = iRuleType;
				req.mems[i].uiCmd = uiCmd;
				i++;
			}
			if (imRules.ucbDistinguishSharedWebcams != m_var.imRules.ucbDistinguishSharedWebcams) {
				if (i >= mycountof(req.mems)) {
					qyShowHint(getResStr(0, &pQyMc->cusRes, CONST_resId_autoAnswerlimited));
					goto  errLabel;
				}
				//
				iRuleType = CONST_ruleType_ucbDistinguishSharedWebcams;
				uiCmd = imRules.ucbDistinguishSharedWebcams ? CONST_ruleCmd_permit : 0;
				//
				req.mems[i].idInfo_related.ui64Id = 0;
				req.mems[i].uiRuleType = iRuleType;
				req.mems[i].uiCmd = uiCmd;
				i++;
			}
#endif

			if (rules.uiCmd_autoAnswer_av != m_var.rules.uiCmd_autoAnswer_av) {

				if (i >= mycountof(req.mems)) {
					//qyShowHint(getResStr(0, &pQyMc->cusRes, CONST_resId_autoAnswerlimited));
					goto  errLabel;
				}

				//
				iRuleType = CONST_ruleType_autoAnswer_av;
				uiCmd = rules.uiCmd_autoAnswer_av;
				//
				req.mems[i].idInfo_related.ui64Id = m_var.idInfo.ui64Id;
				req.mems[i].uiRuleType = iRuleType;
				req.mems[i].uiCmd = uiCmd;
				i++;
			}

#if  0
			if (rules.uiCmd_autoAnswer_screen != m_var.rules.uiCmd_autoAnswer_screen) {

				if (i >= mycountof(req.mems)) {
					qyShowHint(getResStr(0, &pQyMc->cusRes, CONST_resId_autoAnswerlimited));
					goto  errLabel;
				}

				//
				iRuleType = CONST_ruleType_autoAnswer_screen;
				uiCmd = rules.uiCmd_autoAnswer_screen;
				//
				req.mems[i].idInfo_related.ui64Id = m_var.idInfo.ui64Id;
				req.mems[i].uiRuleType = iRuleType;
				req.mems[i].uiCmd = uiCmd;
				i++;
			}

			if (rules.uiCmd_autoAnswer_mediaFile != m_var.rules.uiCmd_autoAnswer_mediaFile) {

				if (i >= mycountof(req.mems)) {
					qyShowHint(getResStr(0, &pQyMc->cusRes, CONST_resId_autoAnswerlimited));
					goto  errLabel;
				}

				//
				iRuleType = CONST_ruleType_autoAnswer_mediaFile;
				uiCmd = rules.uiCmd_autoAnswer_mediaFile;
				//
				req.mems[i].idInfo_related.ui64Id = m_var.idInfo.ui64Id;
				req.mems[i].uiRuleType = iRuleType;
				req.mems[i].uiCmd = uiCmd;
				i++;
			}
#endif

			MACRO_qyAssert(i < mycountof(req.mems), _T("too many rules"));
			//
			req.usCnt = i;


			//  2010/08/14
			pFuncs->pf_startProgress(&pQyMc->gui.progress, uiTranNo);

			//
			MACRO_memset_imLStream(pStream);
			pStream->uiType = CONST_imCommType_lStream;
			pStream->uiContentType = req.uiType;
			len = sizeof(pStream->buf);
			if (refreshImObjRulesReq2Stream(pStream->uiContentType, &req, pStream->buf, (unsigned  int*)&len))  goto  errLabel;
			pStream->ulStreamLen = len;
			len += offsetof(IM_L_STREAM, buf);

			MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
			//
			postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_refreshImObjListReq, tStartTran, uiTranNo, 0, (char*)pStream, len, NULL, 0, 0, NULL, 0);

#if  0
			{
				CDlgProgress	dlg(this);
				dlg.bSetDlgInfo(_T("Please waiting"), NULL, 30, -1, uiTranNo);

				//  traceLogA(  "if task is not ready, cancel the task by clear shmCmd, and the subprocess will quit when it read the shmCmd."  );
				if (dlg.DoModal() != IDOK) {
					goto  errLabel;
				}
			}
#endif
			if (showProgress(&pQyMc->gui.progress, &pQyMc->cusRes, (HWND)this->winId(), _T("Please waiting"), NULL, 30, -1, uiTranNo) != IDOK) {
				goto  errLabel;
			}

			//
			CQnmDb				db;
			if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;

			recoverImObjRules(pQyMc->p_g_dbFuncs, db.m_pDbMem->pDb, pQyMc->cfg.db.iDbType, _T(""), &pMisCnt->idInfo, &req, 0);

			//  2011/11/17
			if (memcmp(&pMisCnt->imRules, &imRules, sizeof(pMisCnt->imRules))) {
				memcpy(&pMisCnt->imRules, &imRules, sizeof(pMisCnt->imRules));
			}

			QM_OBJQ_MEM				mem;
			QMEM_MESSENGER_CLI* pQMem;
			if (!pFuncs->pf_findQMemByKey(0, pMisCnt->pObjQ, &m_var.idInfo, &mem)) {
				pQMem = (QMEM_MESSENGER_CLI*)mem.pQMemObj;
				if (pQMem) {
					memcpy(&pQMem->rules, &rules, sizeof(pQMem->rules));
				}
			}
		}

	

	//
	accept();

	//
	iErr = 0;

errLabel:
	return;
}


void WinRuleSet::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QBrush(Qt::white));

	QColor color(0, 0, 0, 10);
	for (int i = 0; i < SHADOW_WIDTH; i++)
	{
		color.setAlpha(120 - qSqrt(i) * 40);
		painter.setPen(color);
		// 方角阴影边框;
		//painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
		// 圆角阴影边框;
		painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
	}
}
