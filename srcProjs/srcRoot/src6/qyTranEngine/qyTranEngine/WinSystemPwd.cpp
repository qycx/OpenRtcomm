#include "WinSystemPwd.h"
#include	"stdafx.h"
#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc.h"
#include <qyCusResTemp.h>
#include	"funcsForIsCliHelp.h"

//
WinSystemPwd::WinSystemPwd(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	//
	ui.label_name->setText( QString::fromUtf16((char16_t*)pProcInfo->authInfo.messengerName));
	ui.label_hint->setText("");


}

WinSystemPwd::~WinSystemPwd()
{
}


void WinSystemPwd::on_pushButton_clicked()
{
	int						iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return;
	//CString					nameStr;
	static  BOOL			bFirstPrompted = FALSE;
	//CString					passwd0, passwd1;
	int						idc;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));



	QString qstr;
	qstr  =  ui.label_name->text();
	qstr.trimmed();

#if  0
	idc = IDC_EDIT_name;
	GetDlgItemText(idc, nameStr);
	MACRO_CStringTrim(nameStr);
	if (!nameStr.GetLength()) {
		AfxMessageBox(getResStr(0, &pQyMc->cusRes, CONST_resId_messengerNameCannotEmpty)/*_T(  "请输入组名以方便识别"  )*/);
		GetDlgItem(idc)->SetFocus();
		return;
	}
#endif

	QString  passwd0;
	QString passwd1;

	passwd0 = ui.lineEdit_passwd0->text();
	passwd0.trimmed();
	if (passwd0.length() == 0) {
		ui.label_hint->setText(u8"新设密码不能为空");
		ui.lineEdit_passwd0->setFocus();
		return;
	}

	passwd1 = ui.lineEdit_passwd1->text();
	passwd1.trimmed();
	if (passwd1.length() == 0) {
		ui.label_hint->setText(u8"新设密码不能为空");
		ui.lineEdit_passwd1->setFocus();
		return;

	}

	if (passwd0 != passwd1) {
		ui.label_hint->setText( QString::fromUtf16((char16_t*)getResStr(0, &pQyMc->cusRes, CONST_resId_passwdNotConfirmed)));
		ui.lineEdit_passwd0->setFocus();
		return;
	}

	MACRO_prepareForTran();

	{
		CQyMalloc					mallocObj;
		IM_L_STREAM* pStream = NULL;

		if (!(pStream = (IM_L_STREAM*)mallocObj.mallocf(sizeof(IM_L_STREAM)))) {
			traceLogA((char*)"sndDevInfo_qmc . malloc failed.");  goto  errLabel;
		}

		QY_MESSENGER_ACCOUNT	req;
		unsigned  int		len;
		char				buf[256];

		memset(&req, 0, sizeof(req));
		req.uiType = CONST_imCommType_messengerAccount;
		myTChar2Utf8((TCHAR*)passwd0.utf16(), buf, mycountof(buf));
		len = mycountof(req.messengerPasswd);
		if (!bQyGetStrMd5_x(buf, req.messengerPasswd, &len))  goto  errLabel;

		//  2010/08/14
		pFuncs->pf_startProgress(&pQyMc->gui.progress, uiTranNo);

		//
		MACRO_memset_imLStream(pStream);
		pStream->uiType = CONST_imCommType_lStream;
		pStream->uiContentType = req.uiType;
		len = sizeof(pStream->buf);
		if (messengerAccount2Stream(pStream->uiContentType, &req, pStream->buf, &len))  goto  errLabel;
		pStream->ulStreamLen = len;
		len += offsetof(IM_L_STREAM, buf);
		//
		postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_refreshImObjListReq, tStartTran, uiTranNo, 0, (char*)pStream, len, NULL, 0, 0, NULL, 0);
	}

	//  pProcInfo->bInProgress_toSetPasswd  =  TRUE;

	{
		if (showProgress(&pQyMc->gui.progress, &pQyMc->cusRes, (HWND)this->winId(), _T("请等待 ..."), NULL, 30, -1, uiTranNo) != IDOK) {
			goto  errLabel;
		}

		//
		ui.label_hint->setText(QString::fromUtf16((char16_t*)getResStr(0, &pQyMc->cusRes, CONST_resId_restart)));
	}

errLabel:

	return;
}
