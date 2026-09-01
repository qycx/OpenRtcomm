#include "CloudDiskWidget.h"
#include	"stdafx.h"
#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc.h"
#include <help_getDlgTalkVar.h>
#include <dlgtalkproc.h>
#include	"qmcDynBmp.h"
#include	"funcsForIsCliHelp.h"
#include	"qyCusResTemp.h"
#include <QDateTime>
#include <QPainter>
#include <QtCore/qmath.h>
#include <QScroller>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include	"isCliD3dPublic.h"
#include <QStandardPaths>
#include <qapplication.h>
#include <QDesktopWidget>
#include <ctxQmc_qt.h>

#include "CPopUPWindow.h"

#include <fstream>



//
#if 0
namespace {
    //CloudDiskWidget* cloudDisk = nullptr;
}
#endif

//
#define SHADOW_WIDTH 6 // 阴影边框宽度;

//
__declspec(dllexport)  int  viewDlgOfflineRes_talk(HWND  hParent, HWND  hCurTalk, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phTool)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;

	//
	CloudDiskWidget* pDlg = NULL;
	RECT							rect;

	HWND* phWnd_lv = NULL;

	//
	HWND							hTool = NULL;

	//
	CHelp_getDlgTalkVar  help_getDlgTalkVar;
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;

	//
	DLG_TALK_var* pCurVar = NULL;
	DLG_TALK_var* pMgrVar = NULL;
	//
	HWND	hMgr = NULL;

	//
	showInfo_open0(0, 0, _T("viewDlgOfflineRes_talk called"));

	//
	pCurVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hCurTalk);
	if (!pCurVar)  goto  errLabel;
	if (isTalkerShadowMgr(pCurVar->addr))  hMgr = hCurTalk;
	else {
		TALKER_shadow* pShadow = (TALKER_shadow*)pCurVar->pShadowInfo;
		if (!pShadow)  goto  errLabel;
		hMgr = pShadow->hMgr;
	}
	//
	pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
	if (!pMgrVar)  goto  errLabel;
	TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
	if (!pShadowMgr)  goto  errLabel;

	//  2017/09/24
	if (pMgrVar->bShouldQuit1) {
		showInfo_open0(0, 0, _T("viewDlgOfflineRes_talk failed, pMgrVar->bShouldQuit true"));
		goto  errLabel;
	}

	//
	phWnd_lv = &pCurVar->offlineRes.hTool_offlineRes;	//  &pProcInfo->subtitles.hWnd_videoTagCfg;

	if (phWnd_lv) {
		if (IsWindow(*phWnd_lv)) {
			if (bActivateWnd) {
				MACRO_SetForegroundWindow(*phWnd_lv);
			}
			else {
				if (!bNeedNotShowWnd) {
					if (!IsWindowVisible(*phWnd_lv))  ShowWindow(*phWnd_lv, SW_SHOW);
				}
			}
			//
			hTool = *phWnd_lv;
			//
			iErr = 0;  goto  errLabel;
		}

		*phWnd_lv = NULL;
	}

	//
	if (pShadowMgr->offlineRes.hTool_offlineRes) {
		if (IsWindow(pShadowMgr->offlineRes.hTool_offlineRes)) {
			SendMessage(pShadowMgr->offlineRes.hTool_offlineRes, WM_CLOSE, 0, 0);
		}
		if (IsWindow(pShadowMgr->offlineRes.hTool_offlineRes))  goto  errLabel;
	}
	memset(&pMgrVar->offlineRes, 0, sizeof(pMgrVar->offlineRes));

	QWidget* pParent = QWidget::find((WId)hParent);
	//if (pParent == null)  goto  errLabel;


	//
	pDlg = new  CloudDiskWidget(pParent);
	if (!pDlg)  goto  errLabel;

	//
	if (!pDlg->bSetDlgInfo(0, 0, _T("offline Res")))  goto  errLabel;
	pDlg->m_var.idInfo.ui64Id = pMgrVar->addr.idInfo.ui64Id;
	
	pDlg->m_var.hCurTalk = hCurTalk;
	pDlg->m_var.hDlgTalk_mgr = hMgr;	//  hCurTalk;
		//
	if (pShadowMgr->av.ucbMeConfMgr && pMgrVar->addr.uiObjType == CONST_objType_imGrp)  pDlg->m_var.ucbConfMgr = TRUE;

	//
#if  0
	if (!pDlg->Create(rect))  goto  errLabel;
	if (!bNeedNotShowWnd) {
		pDlg->ShowWindow(SW_SHOW);
	}
#endif
	//
	if (pDlg->init())  goto  errLabel;
	//
	pDlg->hide();

	//
	HWND  m_hWnd = (HWND)pDlg->winId();
	//
	if (phWnd_lv)  *phWnd_lv = m_hWnd;
	pShadowMgr->offlineRes.hTool_offlineRes = m_hWnd;

	//
	hTool = m_hWnd;

	iErr = 0;

errLabel:

	if (iErr) {
		if (pDlg)  delete  pDlg;
	}
	if (!iErr) {
		if (phTool)  *phTool = hTool;
	}

	//
	TCHAR  tBuf[128];
	_sntprintf(tBuf, mycountof(tBuf), _T("viewDlgOfflineRes_talk leaves, iErr %d"), iErr);
	showInfo_open0(0, 0, tBuf);


	//
	return  iErr;
}


#include <stdio.h>
#include <tchar.h>
char* UnicodeToAnsi1(const wchar_t* szStr, int& nLen)
{
	nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
	return pResult;
}


#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>

#include <QTimer>


void splitW(const std::wstring& s, TCHAR delim, std::vector<std::wstring>& elems) {
	std::wstringstream ss;
	ss.str(s);
	std::wstring item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}
std::vector<std::wstring> splitW(const std::wstring& s, TCHAR delim) {
	std::vector<std::wstring> elems;
	splitW(s, delim, elems);
	return elems;
}


std::string getDT1() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	std::tm* now_tm = std::localtime(&now_time);

	std::stringstream ss;

	ss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S.");

	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
	ss << std::setw(3) << std::setfill('0') << millis.count();

	return ss.str();
}



int printLogChar1(const char* log) {
	//return 0;

	FILE* pf = fopen("D:/qycx/cloud.txt", "a+");
	if (pf == NULL)
	{
		perror("打开文件失败！");
		return 1;
	}

	//TCHAR* pp;


	//fprintf(pf, "%s:%s  - %s \n", __DATE__, __TIME__, log);
	fprintf(pf, "[%s]  - %s \n", getDT1().c_str(), log);

	fclose(pf);

	return 0;

}




int printLog1(const TCHAR* log) {
	//return 0;

	FILE* pf = fopen("D:\\qycx\\cloud.txt", "a+");
	if (pf == NULL)
	{
		perror("打开文件失败！");
		return 1;
	}

	//TCHAR* pp;

	char* pBuf = NULL;
	int nLen = 0;

	pBuf = UnicodeToAnsi1(log, nLen);

	if (pBuf) {
		fprintf(pf, "[%s]  - %s \n", getDT1().c_str(), pBuf);
		delete[] pBuf;
	}

	fclose(pf);

}

//  2015/08/06
__declspec(dllexport)  int  viewDlgOfflineRes_me(HWND  hParent, OfflineRes_var* pVar, PARAM_viewOfflineRes* pParam)
{
	
	int					iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	//  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );

	CloudDiskWidget* pDlg = NULL;
	RECT							rect;

	HWND* phWnd_lv = NULL;

	//
	PARAM_viewOfflineRes  param = { 0 };
	if (pParam)  param = *pParam;


	//
	phWnd_lv = &pVar->hTool_offlineRes;	//  &pProcInfo->subtitles.hWnd_videoTagCfg;

	if (phWnd_lv) {
		if (IsWindow(*phWnd_lv)) {
			MACRO_SetForegroundWindow(*phWnd_lv);
			iErr = 0;  goto  errLabel;
		}

		*phWnd_lv = NULL;
	}

	//
	QWidget* pParent = QWidget::find((WId)hParent);
	//if (pParent == null)goto  errLabel;


	//
	pDlg = new  CloudDiskWidget((pParent));
	if (!pDlg)  goto  errLabel;

	if (!pDlg->bSetDlgInfo(0, 0, _T("offline Res")))  goto  errLabel;
	pDlg->m_var.hDlgTalk_mgr = NULL;	//  hCurTalk;
	
	//
	if (pDlg->init())  goto  errLabel;

	//
	pDlg->show();

#if  0
	//
	if (!pDlg->Create(rect))  goto  errLabel;
	//
	if (param.bNoBorder) {
		makeWndNoBorder(pDlg->m_hWnd, FALSE, NULL, NULL);
	}
	//
	pDlg->ShowWindow(SW_SHOW);
#endif

	HWND  m_hWnd = (HWND)pDlg->winId();

	//
	if (phWnd_lv)  *phWnd_lv = m_hWnd;


	iErr = 0;

errLabel:

	if (iErr) {
		if (pDlg)  delete  pDlg;
	}



	return  iErr;
}



void saveSelectDir(TCHAR  * tDir) {

	CCtxQyMc* pQyMc = g_pQyMc;
	TCHAR* pRegVal;
	QY_REG  reg;

	memset(&reg, 0, sizeof(reg));
	reg.hKeyRoot0 = HKEY_CURRENT_USER;

	//
	TCHAR  tBuf[128];
	int cnt;
	//
	


	 safeTcsnCpy( (TCHAR*)tDir , tBuf , mycountof(tBuf));

	qySetRegCfgT(HKEY_CURRENT_USER, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, _T(CONST_regFilePath_select), tBuf);
}

 int getSelectDir(TCHAR * tDir , int cnt) {

	CCtxQyMc* pQyMc = g_pQyMc;
	TCHAR  tBuf[128];
	char  buf[128];


	if (qyGetRegCfgT(HKEY_CURRENT_USER, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, _T(CONST_regFilePath_select), (char*)tBuf, sizeof(tBuf), NULL)) {
		tBuf[0] = 0;
	}
	safeTcsnCpy(tBuf, tDir, cnt);
	return 0;
}

#include <codecvt>

 // 将 string 转为 wstring
 inline std::wstring to_wstring(const std::string& input)
 {
	 std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	 return converter.from_bytes(input);
 }
 // 将 wstring 转为 string 
 inline std::string to_string(const std::wstring& input)
 {
	 std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	 return converter.to_bytes(input);
 }


 void test() {
	 //完成 完成 uploading D:/qycx/upload/tmInit - 副本.ini (0)
	 //std::wstring wstr(_T("完成 完成 uploading D:/qycx/log_srv.txt (0)"));
	 std::wstring wstr(_T("完成 完成 uploading D:/qycx/upload/tmInit-副本.ini (0)"));
	 //std::wstring wstr(_T("完成 完成 uploading D:/qycx/upload/tmInit - 副本.ini (0)"));


	 if (wstr.find(_T("完成 完成 uploading")) !=  std::wstring::npos) {
		 TCHAR ss = ' ';
		 std::vector<std::wstring> vecV = splitW(wstr, ss);

		 /*
		 if (vecV.size() >= 4) {
			 std::wstring fileName = vecV[3];

			 std::string strFileName = to_string(fileName);
		 }*/
		 std::wstring fileName;
		 for (int i = 3; i < vecV.size() - 1; ++i) {
			 if (!fileName.empty())
				 fileName += ss;

			 fileName += vecV[i];
		 }

		 std::string strFileName = to_string(fileName);
		 strFileName = strFileName;
	 }
 }

 void test2() {
	 
	 std::wstring wstr(_T("67%( 163800k ) 发送中 uploading D:/qycx/upload/test.data (0)"));


	 if (wstr.find(_T("发送中 uploading")) != std::wstring::npos) {
		 TCHAR ss = ' ';
		 std::vector<std::wstring> vecV = splitW(wstr, ss);

		 if (vecV.size() >= 4) {
			 std::wstring per = vecV[0];

			 int pos = per.find(_T("%"));

			 if (pos != std::wstring::npos) {
				 std::wstring per2 = per.substr(0, pos);

				 int per = _wtoi(per2.c_str());
				 per = per;
			 }

			 


			 std::wstring size = vecV[1];

			 //std::string strFileName = to_string(fileName);
		 }
	 }

 }

CloudDiskWidget::CloudDiskWidget(QWidget* parent)
    : WinBasic(true, parent),
	m_PopUPWindow(nullptr),
	m_RightPop(nullptr),
	m_AutoRightPop(nullptr)
{
    ui.setupUi(this);
	//QScroller* scroller = QScroller::scroller(ui.tableWidget);
	//scroller->grabGesture(ui.tableWidget,QScroller::LeftMouseButtonGesture);
    ui.tableWidget->setVerticalScrollMode(QTableWidget::ScrollPerPixel);
    ui.tableWidget->setFocusPolicy(Qt::NoFocus);
    ui.tableWidget->horizontalHeader()->setFixedHeight(30);
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui.tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
    //ui.tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
	ui.tableWidget->setStyleSheet("selection-background-color: rgba(82,115,204,50%)");
    ui.tableWidget->setShowGrid(false); //设置不显示格子线
    ui.tableWidget->verticalHeader()->setDefaultSectionSize(30); //设置行高
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeMode::Interactive);
	ui.tableWidget->setColumnWidth(0,100);
	
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeMode::Interactive);

	ui.tableWidget->setColumnWidth(1, 380);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeMode::Interactive);
	ui.tableWidget->setColumnWidth(2, 150);

	
	//
	
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeMode::Interactive );
	this->setAttribute(Qt::WA_DeleteOnClose);
	//ui.tableWidget->resizeColumnsToContents();
	//
	ui.btnSearch->setIcon(QIcon(":/Resources/Images/WinMain/search_icon.png"));
	memset(&m_var, 0, sizeof(m_var));
	connect(ui.tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(slot_onTableClicked(int, int)));
	this->setAcceptDrops(true);

	QRect rc = QApplication::desktop()->screenGeometry();
	int dis_height = COUNT_display_height_value;
	int dis_width = COUNT_display_width_value;
	if ( rc.height() < dis_height  &&  rc.width() > dis_width) {
		int rx = (rc.width() - 733) / 2;
		int ry = (rc.height() - 591) / 2;
		QRect rc1 = QRect(rx, ry, 733, 591);

		this->setGeometry(rc1);
	}



	//
    reloadFileList();

	//
	HWND  m_hWnd = (HWND)this->winId();
	int  ii = 0;

	//GetNewFile();
	test();
	//test2();

	m_timer = new QTimer(this);
	connect(m_timer, &QTimer::timeout, this, &CloudDiskWidget::onTimeout);

	LoadInitFile();

	ui.pushButton_auto->click();
}

#define UFILELISTNAME "d:\\qycx\\ufilelist.inf"

void CloudDiskWidget::LoadInitFile() {
	std::ifstream file(UFILELISTNAME);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			m_mapUploadFile[line] = 1;
		}
		file.close();
	}
}


void CloudDiskWidget::onTimeout()
{
	std::lock_guard<std::mutex> lck(m_lock);
	if (m_autoUpload && m_isFree) {

		if (m_isFree) {
			QString newFile;
			bool ret = GetNewFile(newFile);
			if (ret) {
				m_noFileCount = 0;

				dlgOfflineRes_upload_qt(newFile);
				m_isFree = false;	


				if (m_AutoRightPop) {
					//m_AutoRightPop->startClose();
					//delete m_AutoRightPop;
					if (!m_AutoRightPop->isVisible()) {
						m_AutoRightPop->show();
						m_AutoRightPop->showMessage();
					}
					m_AutoRightPop->SetTip(newFile);
					m_AutoRightPop->SetProgress(0);
					
				}
				else {
					m_AutoRightPop = new RightPop();
					m_AutoRightPop->SetTip(newFile);
					m_AutoRightPop->show();
					m_AutoRightPop->showMessage();
				}

			}
			else {
				m_noFileCount++;

				if (m_noFileCount > 5) {
					if (m_AutoRightPop) {
						m_AutoRightPop->startClose();
						m_AutoRightPop->hide();
					}
					//if (m_AutoRightPop->isVisible())
					//	m_AutoRightPop->hide();
				}
			}
		}
		

	}
	
}

void CloudDiskWidget::clearTableWidget(QTableWidget* table)
{
    while (table->rowCount() > 0)
    {
        table->removeRow(0);
    }
}

CloudDiskWidget::~CloudDiskWidget()
{
	HWND  m_hWnd = (HWND)this->winId();
	int  ii = 0;

}


//
BOOL  CloudDiskWidget::bSetDlgInfo(int  iWndContentType, int  iSubType, LPCTSTR  title)
{
	BOOL	bRet = FALSE;


	m_var.iWndContentType = iWndContentType;
	m_var.iWndContentSubType = iSubType;
	safeTcsnCpy(title, m_var.title, mycountof(m_var.title));

	bRet = TRUE;

	return  bRet;
}

//
int CloudDiskWidget::init()
{
	
		// TODO:  Add extra initialization here
		int					iErr = -1;
		QY_MC* pQyMc = QY_GET_GBUF();
		MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
		RECT				rc;
		int  idc;
		RECT* pRc;

		//
		QY_MESSENGER_ID		idInfo_logicalPeer = { 0 };
		unsigned  char		ucbP2p = FALSE;
		QY_MESSENGER_ID		idInfo_req = { 0 };

		//
		FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
		if (!pFuncs)  goto  errLabel;

		HWND  m_hWnd = (HWND)this->winId();

		//
		//cusDlgRes(0, &pQyMc->cusRes, m_hWnd, IDD);

		DLG_guiData_offlineRes* p = &m_var.guiData;

		::GetClientRect(m_hWnd, &rc);

		//
		p->bInited = TRUE;



		MIS_CNT* pMisCnt = pProcInfo->getMisCntByName( _T(""));
		if (!pMisCnt)  goto  errLabel;
		//m_var.pMisCnt  =  pMisCnt;
		//
		HWND  hParent = m_hWnd;


		//
		unsigned  int  uiTranNo = 0;
		if (sndProcOfflineResReq_qmc(pMisCnt, TRUE, &uiTranNo)) {
			showInfo_open0(0, 0, _T("dlgOfflineRes.OnInitDialog failed, sndProcOfflineResReq failed"));
			goto  errLabel;
		}

		//
		TCHAR* hint = (TCHAR*)_T("Please waiting...");
		hint = (TCHAR*)_T("请等待...");
		//
		if (showProgress(&pQyMc->gui.progress, &pQyMc->cusRes, hParent, hint, NULL, 30, -1, uiTranNo) != IDOK) {
			//  2017/09/23
			showInfo_open0(0, 0, _T("dlgOfflineRes.OnInitDialog failed, showProgress failed"));
			goto  errLabel;
		}

		if (!pMisCnt->procOfflineRes.idInfo_resServ.ui64Id) {
			myMessageBox(hParent, getResStr(0, &pQyMc->cusRes, CONST_resId_cannotConnectFileServer), _T("www.qycx.com"), MB_OK);		//  _T(  "无法获取通知或文件，因为无法连接文件服务器！"  )
			goto  errLabel;
		}
		//
#ifdef  __DEBUG__

#endif

	//
		m_var.usIndex_page = 0;
		this->bDisplay_usIndex_page();

		//
		bRefresh();



		iErr = 0;

	errLabel:


		if (!m_var.guiData.bInited || iErr) {
			//  EndDialog(  -1  );
			PostMessage(m_hWnd,WM_CLOSE,0,0);
		}

		return  iErr;
	
}

//
BOOL  CloudDiskWidget::bDisplay_usIndex_page()
{
	//SetDlgItemInt(m_var.guiData.iIDC_EDIT_pageNo, m_var.usIndex_page + 1);
	return  TRUE;
}


BOOL  CloudDiskWidget::bRefresh()
{
	BOOL  bRet = FALSE;
	QString keyword;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	RECT				rc;
	//int  idc;
	//RECT			*	pRc;

	//
	QY_MESSENGER_ID		idInfo_logicalPeer = { 0 };
	unsigned  char		ucbP2p = FALSE;
	QY_MESSENGER_ID		idInfo_req = { 0 };

	//
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  goto  errLabel;

	//
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName( _T(""));
	if (!pMisCnt)  goto  errLabel;

	HWND  m_hWnd = (HWND)this->winId();
	HWND  hParent = m_hWnd;

	//
	HWND  hTalker_res = NULL;
	if (pFuncs->pf_talkToMessenger(pMisCnt->procOfflineRes.idInfo_resServ.ui64Id, 0, TRUE, FALSE, &hTalker_res)) {
		goto  errLabel;
	}



	//
	if (m_var.hDlgTalk_mgr)
	{
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var* pDlgTalkVar;
		pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(m_var.hDlgTalk_mgr);
		if (!pDlgTalkVar)  goto  errLabel;
		//
		if (!isTalkerShadowMgr(pDlgTalkVar->addr))  goto  errLabel;

		//
		idInfo_logicalPeer.ui64Id = pDlgTalkVar->addr.idInfo.ui64Id;
		if (pDlgTalkVar->addr.uiObjType != CONST_objType_imGrp
			&& pDlgTalkVar->addr.uiObjType != CONST_objType_tmpGrp)
		{
			ucbP2p = TRUE;
		}
		idInfo_req.ui64Id = pDlgTalkVar->addr.idInfo.ui64Id;

	}
	else {  //  me
	}



	//
	//
	PROC_offlineRes_retrieve	req;
	
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_procOfflineRes;
	req.usSubtype = CONST_procOfflineResSubtype_retrieve;
	req.hTool_offlineRes = m_hWnd;
	//
	req.req.idInfo_logicalPeer.ui64Id = idInfo_logicalPeer.ui64Id;
	req.req.ucbP2p = ucbP2p;
	//
	req.req.usIndex_page = m_var.usIndex_page;
	req.req.max_usCnt = mycountof(m_var.reses_retrieved.mems);
	//
	//GetDlgItemText(m_var.guiData.iIDC_EDIT_filterKeywords, req.req.keyword, mycountof(req.req.keyword));
	
	keyword = ui.lineEdit->text();

	safeTcsnCpy ( (TCHAR*)keyword.utf16() , req.req.keyword, mycountof(req.req.keyword));
	tTrim(req.req.keyword);
	//		
	unsigned  int  uiTranNo_wait = 0;
	{
		MACRO_prepareForTran();
		uiTranNo_wait = uiTranNo;
	}

	//
	startProgress(&pQyMc->gui.progress, uiTranNo_wait);

	//
	QY_WMBUF_COMM	wmBuf;
	memset(&wmBuf, 0, sizeof(wmBuf));
	wmBuf.uiType = CONST_qyWmParam_procOfflineRes;
	wmBuf.u.procOfflineRes.ui64Id_req = idInfo_req.ui64Id;
	wmBuf.u.procOfflineRes.pPROC_offlineRes_u = &req;
	wmBuf.u.procOfflineRes.uiTranNo_wait = uiTranNo_wait;
	if (!SendMessageTimeout(hTalker_res, CONST_qyWm_comm, 0, (LPARAM)&wmBuf, 0, 1000, NULL))  goto  errLabel;
	//
	TCHAR* hint = (TCHAR*)_T("Please waiting...");
	hint = (TCHAR*)_T("请等待...");
	//
	int  nStep_finished = 5;  //  30;
	if (showProgress(&pQyMc->gui.progress, &pQyMc->cusRes, hParent, hint, NULL, nStep_finished, -1, uiTranNo_wait) != IDOK) {
		goto  errLabel;
	}
	//


	bRefreshBtns();


	bRet = TRUE;

errLabel:

	return  bRet;
}



int  CloudDiskWidget::getDisplayStr_res_retrieved(RES_inProcess* pMem, TCHAR* tBuf, int  cnt)
{
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;

	_sntprintf(tBuf, cnt, _T("%s  ( size: %I64u ) ( %I64u )"), pMem->res.name, pMem->res.ui64FileLen, pMem->res.res.idInfo.ui64Id);

	//
	char  timeBuf[128];
	char  displayBuf[128];
	getTimeStr(pMem->res.tCreationTime, timeBuf, mycountof(timeBuf));
	qyDisplayTime(timeBuf, displayBuf, mycountof(displayBuf));
	_sntprintf(tBuf, cnt, _T("%s %S"), tBuf, displayBuf);


#if  0
	_sntprintf(tBuf, cnt, _T("%s  ( size: %I64u ) "), pMem->res.name, pMem->res.ui64FileLen);
	//
	int  leftBytes = 50;
	//
	int  len = lstrlen(tBuf);
	if (cnt > leftBytes && len < leftBytes) {
		int  i;
		for (i = len; i < leftBytes; i++) {
			tBuf[i] = ' ';
		}
		tBuf[leftBytes - 1] = 0;
	}
	//
	TCHAR  talkerDesc[128] = _T("");
	pFuncs->pf_getTalkerDesc(m_var.pMisCnt, &pMem->res.res.idInfo, talkerDesc, mycountof(talkerDesc), NULL, 0);
	_sntprintf(tBuf, cnt, _T("%s     %s ( %I64u )"), tBuf, talkerDesc, pMem->res.res.idInfo.ui64Id);

#endif

	return  0;

}


int  CloudDiskWidget::getDisplayStr_res_beingProced(RES_inProcess* pMem, TCHAR* tBuf, int  cnt)
{
	QY_MC* pQyMc = QY_GET_GBUF();


	tBuf[0] = 0;
	if (pMem->iStatus) {
		_sntprintf(tBuf, cnt, _T("%s"), qyGetDesByType1(getResTable(0, &pQyMc->cusRes, CONST_resId_imTaskStatusTable), pMem->iStatus));
		//
		if (pMem->iStatus == CONST_qyStatus_err) {
			if (pMem->usSubtype == CONST_procOfflineResSubtype_del) {
				_sntprintf(tBuf, cnt, _T("%s ( %s )"), tBuf, getResStr(0, &pQyMc->cusRes, CONST_resId_mayBeLocked));
			}
		}
	}
	//
	_sntprintf(tBuf, cnt, _T("%s %s %s (%I64u)"), tBuf, qyGetDesByType1(CONST_procOfflineResSubtypeTable, pMem->usSubtype), pMem->res.name, pMem->res.res.idInfo.ui64Id);
	//


	return  0;
}


BOOL CloudDiskWidget::ResesDisplay() {
	int  i;
	int  tmpiRet;

	TCHAR							tBuf[256] = _T("");
	int								nItems = 0;
	int								iCurSel = 0;

	//
#if  0
	LVITEM				lvItem;

	memset(&lvItem, 0, sizeof(lvItem));
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvItem.iItem = nItems;
	lvItem.pszText = tBuf;
	lvItem.cchTextMax = mycountof(tBuf);
#endif


	//
	int  index = 0;


	removeProessAll();
	for (i = 0; i < m_var.reses_beingProced.usCnt; i++) {

		//
		RES_inProcess* pMem = &m_var.reses_beingProced.mems[i];
		////
		getDisplayStr_res_beingProced(pMem, tBuf, mycountof(tBuf));

#if 0
		lvItem.pszText = tBuf;
		lvItem.cchTextMax = mycountof(tBuf);
		lvItem.iItem = i + m_var.reses_retrieved.usCnt;
		////
		// 
		
		if (ListView_InsertItem(m_var.listCtrl.hListCtrl, &lvItem) == -1)  goto  errLabel;
#endif

		//Item->setText(QString::fromStdWString(tBuf));

		this->updateProcessStatus(QString::number(i), QString::fromUtf16((char16_t*)tBuf));

		
		////
		//pMem->index = lvItem.iItem;

	}


#if  0
	//
	CListCtrl* pLv = (CListCtrl*)GetDlgItem(m_var.guiData.iIDC_LIST_offlineRes);
	if (!pLv)  goto  errLabel;
	pLv->DeleteAllItems();


	//
	LVITEM				lvItem;

	memset(&lvItem, 0, sizeof(lvItem));
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvItem.iItem = nItems;
	lvItem.pszText = tBuf;
	lvItem.cchTextMax = mycountof(tBuf);

	int  index = 0;
	//
	for (i = 0; i < m_var.reses_retrieved.usCnt; i++) {
		RES_inProcess* pMem = &m_var.reses_retrieved.mems[i];

		getDisplayStr_res_retrieved(pMem, tBuf, mycountof(tBuf));

		lvItem.pszText = tBuf;
		lvItem.cchTextMax = mycountof(tBuf);
		lvItem.iItem = i;

		//  tmpiRet  =  ::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )index,  (  LPARAM  )m_var.reses_retrieved.mems[i].res.name  );
		if (ListView_InsertItem(m_var.listCtrl.hListCtrl, &lvItem) == -1)  goto  errLabel;

		//
		pMem->index = lvItem.iItem;

	}




#endif


errLabel:

	return  TRUE;
}

BOOL  CloudDiskWidget::bDisplay()
{
	int  i;
	int  tmpiRet;

	TCHAR							tBuf[256] = _T("");
	int								nItems = 0;
	int								iCurSel = 0;
	unsigned  int  uiObjType = 0;
	TCHAR grpName_peer[125];
	TCHAR srcName_peer[125];
	getTalkerDesc(m_var.idInfo, &uiObjType, grpName_peer, mycountof(grpName_peer), null, null, 0, null, 0, srcName_peer, mycountof(srcName_peer));
	if (uiObjType == CONST_objType_imGrp) {
		ui.label->setText(u8"网盘 (" + QString::fromStdWString(grpName_peer) + ")");
	}
	else if(uiObjType == CONST_objType_messenger) {
		ui.label->setText(u8"网盘 (" + QString::fromStdWString(srcName_peer) + ")");
	}
	else {
		ui.label->setText(u8"我的网盘");
		ui.pushButton_7->setEnabled(false);
		ui.pushButton_7->setStyleSheet("color:#eee;");
	}
	
	

	clearTableWidget(ui.tableWidget);
	for (size_t i = 0; i < m_var.reses_retrieved.usCnt; i++)
	{
		int row = ui.tableWidget->rowCount();
		ui.tableWidget->insertRow(row);
		ui.tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(m_var.reses_retrieved.mems[i].res.res.idInfo.ui64Id)));
		ui.tableWidget->setItem(row, 1, new QTableWidgetItem( QString::fromStdWString(m_var.reses_retrieved.mems[i].res.name)));
		ui.tableWidget->setItem(row, 2, new QTableWidgetItem( QString::number(m_var.reses_retrieved.mems[i].res.ui64FileLen) ));
		ui.tableWidget->setItem(row, 3, new QTableWidgetItem( QDateTime::fromSecsSinceEpoch(m_var.reses_retrieved.mems[i].res.tCreationTime).toString("yyyy/MM/dd hh:mm:ss")));
	}


	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		for (int j = 0; j < ui.tableWidget->columnCount(); j++)
		{
			ui.tableWidget->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
	}


#if  0
	//
	CListCtrl* pLv = (CListCtrl*)GetDlgItem(m_var.guiData.iIDC_LIST_offlineRes);
	if (!pLv)  goto  errLabel;
	pLv->DeleteAllItems();


	//
	LVITEM				lvItem;

	memset(&lvItem, 0, sizeof(lvItem));
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvItem.iItem = nItems;
	lvItem.pszText = tBuf;
	lvItem.cchTextMax = mycountof(tBuf);

	int  index = 0;
	//
	for (i = 0; i < m_var.reses_retrieved.usCnt; i++) {
		RES_inProcess* pMem = &m_var.reses_retrieved.mems[i];

		getDisplayStr_res_retrieved(pMem, tBuf, mycountof(tBuf));

		lvItem.pszText = tBuf;
		lvItem.cchTextMax = mycountof(tBuf);
		lvItem.iItem = i;

		//  tmpiRet  =  ::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )index,  (  LPARAM  )m_var.reses_retrieved.mems[i].res.name  );
		if (ListView_InsertItem(m_var.listCtrl.hListCtrl, &lvItem) == -1)  goto  errLabel;

		//
		pMem->index = lvItem.iItem;

	}

	for (i = 0; i < m_var.reses_beingProced.usCnt; i++) {
		//
		ES_inProcess* pMem = &m_var.reses_beingProced.mems[i];
		//
		getDisplayStr_res_beingProced(pMem, tBuf, mycountof(tBuf));
		lvItem.pszText = tBuf;
		lvItem.cchTextMax = mycountof(tBuf);
		lvItem.iItem = i + m_var.reses_retrieved.usCnt;
		//
		//  tmpiRet  =  ::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )index,  (  LPARAM  )tBuf  );
		if (ListView_InsertItem(m_var.listCtrl.hListCtrl, &lvItem) == -1)  goto  errLabel;

		//
		pMem->index = lvItem.iItem;

	}


#endif


errLabel:

	return  TRUE;
}


BOOL  CloudDiskWidget::bRefreshBtns()
{
	return false;
}


#if 0
void CloudDiskWidget::ShowDialog(QWidget* parent)
{
    if (!cloudDisk)
    {
        cloudDisk = new CloudDiskWidget(parent);

    }
    cloudDisk->activateWindow();
    cloudDisk->show();
}
#endif


bool CloudDiskWidget::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	Q_UNUSED(eventType);
	MSG* msg = reinterpret_cast<MSG*>(message);
	UINT m = msg->message;
	if (m == WM_COMMAND || m == CONST_qyWm_comm || m == CONST_qyWm_postComm)
	{
		return postMessageQt(msg, result);
	}
	/*else if (m == WM_NCHITTEST)
	{
		return dealHTEvent((MSG*)message,result);
	}*/
	return QWidget::nativeEvent(eventType, message, result);

}

bool CloudDiskWidget::postMessageQt(MSG* message, long* result)
{
	//
	if (message->message == CONST_qyWm_comm)
	{
		//
		HWND  hMainWnd = (HWND)this->winId();
		//
		QY_WMBUF_COMM* pWmBuf = (QY_WMBUF_COMM*)message->lParam;
		if (message->wParam == CONST_qyWmParam_getObjAddr)
		{
			pWmBuf->u.getObjAddr.pObjAddr = this;
			*result = CONST_qyWmRc_ok;
			return  true;
		}
		//
		*result = OnQyComm(message->wParam, message->lParam);
		return true;
	}

	return  false;

}


LRESULT CloudDiskWidget::OnQyComm(WPARAM wParam, LPARAM  lParam)
{

	long							lRet = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();	//  (  MC_VAR_isCli  *  )pDlgTalkVar->pMisCnt->pProcInfoParam;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;


	QY_WMBUF_COMM* pComm = (QY_WMBUF_COMM*)lParam;
	TCHAR  tBuf_status[128] = _T("");


	if (!pComm)  return  -1;

	switch (pComm->uiType) {
	case  CONST_misMsgType_input: {
		MIS_MSG_INPUT* pMsg = (MIS_MSG_INPUT*)pComm;
		IM_CONTENTU* pContent = NULL;
		int								i;
		int								tmpiRet;

		//
		if (isUcFlgRouteTalkData(pMsg->ucFlg) || isUcFlgTalkData(pMsg->ucFlg))  pContent = (IM_CONTENTU*)pMsg->data.buf;
		else  pContent = (IM_CONTENTU*)&pMsg->data;

		//
		if (pContent->uiType != CONST_imCommType_procOfflineRes)  goto  errLabel;

		//
		if (pContent->procOfflineResU.common.usSubtype == CONST_procOfflineResSubtype_retrieve) {

			//
			m_var.reses_retrieved.usCnt = 0;
			int  n = std::min(pContent->procOfflineResU.retrieve.resp.usCnt, (unsigned short)mycountof(pContent->procOfflineResU.retrieve.resp.mems));
			for (i = 0; i < n; i++) {
				m_var.reses_retrieved.mems[i].res = pContent->procOfflineResU.retrieve.resp.mems[i];
			}
			m_var.reses_retrieved.usCnt = n;

			//				
			bDisplay();
			break;
		}
		if (pContent->procOfflineResU.common.usSubtype == CONST_procOfflineResSubtype_del) {
			//
			RES_inProcess* pMem_task = NULL;
			//
			if (!isUcFlgResp(pMsg->ucFlg)) {
#ifdef  __DEBUG__
				traceLog((TCHAR*)_T("CDlgOfflineRes_OnQyComm_msgInput_profOfflineRes_del failed, not resp"));
#endif
				goto  errLabel;
			}
			//
			for (i = 0; i < m_var.reses_beingProced.usCnt; i++) {
				pMem_task = &m_var.reses_beingProced.mems[i];
				//
				if (pMem_task->uiTranNo_real != pMsg->uiTranNo)  continue;
				//
				if (isRcOk(pMsg->usCode))  pMem_task->iStatus = CONST_imTaskStatus_sendFinished;
				else  pMem_task->iStatus = CONST_qyStatus_err;
				//
				break;
			}
			if (i == m_var.reses_beingProced.usCnt)  goto  errLabel;
			//					  		
			TCHAR  tBuf_mem[128] = _T("");
			this->getDisplayStr_res_beingProced(pMem_task, tBuf_mem, mycountof(tBuf_mem));
			//


			//
			updateProcessStatus(QString::number(i), QString::fromUtf16((char16_t*)tBuf_mem));


			break;
		}


	}
								break;
	case  CONST_misMsgType_taskStatus: {
		MIS_MSG_taskStatus* pMsgTaskStatus = (MIS_MSG_taskStatus*)pComm;
		//
		RES_inProcess* pMem;
		int  i;
		for (i = 0; i < m_var.reses_beingProced.usCnt; i++) {
			pMem = &m_var.reses_beingProced.mems[i];
			if (pMem->iTaskId == pMsgTaskStatus->iTaskId) {
				break;
			}
		}
		if (i == m_var.reses_beingProced.usCnt) {
			showInfo_open0(0, 0, _T("offlineRes: taskStatus err, not a being processed task"));
			goto  errLabel;
		}
		//
		pMem->iStatus = pMsgTaskStatus->iStatus;
		pMem->dwTickCnt_modified = GetTickCount();
		//
		switch (pMsgTaskStatus->iStatus) {
		case  CONST_imTaskStatus_sending:
		case  CONST_imTaskStatus_receiving:
			M_getTransferFileStatus_str(pMsgTaskStatus->u.transferFileStatus, tBuf_status, mycountof(tBuf_status));
			//
			pMem->transferFileStatus = pMsgTaskStatus->u.transferFileStatus;
			//
			break;
			//
		case  CONST_imTaskStatus_sendFinished:
		case  CONST_imTaskStatus_recvFinished:
		case  CONST_imTaskStatus_canceledBySender:
		case  CONST_imTaskStatus_canceledByReceiver:
		case  CONST_imTaskStatus_autoCanceledByReceiver:	//  2014/07/30
		default:
			//
			//
			_sntprintf(tBuf_status, mycountof(tBuf_status), _T("%s"), qyGetDesByType1(getResTable(0, &pQyMc->cusRes, CONST_resId_imTaskStatusTable), pMsgTaskStatus->iStatus));
			//
#ifdef   __DEBUG__
			showInfo_open0(0, _T("OfflineRes.Comm"), tBuf_status);
#endif
			//
			break;
		}
		//
		TCHAR  tBuf_mem[128] = _T("");
		this->getDisplayStr_res_beingProced(pMem, tBuf_mem, mycountof(tBuf_mem));
		//
		TCHAR  tBuf1[128];
		_sntprintf(tBuf1, mycountof(tBuf1), _T("%s %s"), tBuf_status, tBuf_mem);
		//

		updateProcessStatus(QString::number(i), QString::fromUtf16((char16_t*)tBuf1));

	}
									 break;
	case  CONST_misMsgType_task: {
		MIS_MSG_TASK* pMsgTask = (MIS_MSG_TASK*)pComm;
		//
		IM_CONTENTU* pContent = M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
		//
		if (pContent->uiType == CONST_imCommType_transferFileReq) {
			int  i;
			for (i = 0; i < m_var.reses_beingProced.usCnt; i++) {
				RES_inProcess* pMem = &m_var.reses_beingProced.mems[i];
				if (pMem->iTaskId)  continue;
				if (!lstrcmpi(pMem->res.name, pContent->transferFileReq.fileName)) {
					pMem->iTaskId = pMsgTask->iTaskId;
					//
					break;
				}
			}
			if (i == m_var.reses_beingProced.usCnt) {
				goto  errLabel;
			}
		}
		else {
			goto  errLabel;
		}

	}
							   break;
	default:
		break;

	}


	lRet = QY_RC_WMOK;

errLabel:

#ifdef  __DEBUG__
	if (lRet != QY_RC_WMOK) {
		int  ii = 0;
	}
	//
	traceLogA((char*)"CDlgOfflineRes::OnQyComm leaves with iErr %d", lRet);
#endif

	return  lRet;
}


//
void CloudDiskWidget::closeEvent(QCloseEvent* ev)
{
    this->hide();
    ev->accept();
}

void CloudDiskWidget::reloadFileList()
{
   
}

void CloudDiskWidget::slot_edit_return()
{
    //TODO:搜索
	//QString key =  ui.lineEdit->text();
	bRefresh();
}

void CloudDiskWidget::on_btnSearch_clicked() {

	bRefresh();
}


void CloudDiskWidget::slot_onTableClicked(int row, int col) {

	table_row = row;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	QString infoId = getCurrentId();

	//
	if (ui.label->text() == u8"我的网盘") {
		ui.pushButton_9->setEnabled(true);
		ui.pushButton_9->setCursor(Qt::PointingHandCursor);
		ui.pushButton_9->setStyleSheet("color:#000");
	}
	else {
		if (infoId == QString::number(pMisCnt->idInfo.ui64Id)) {
			ui.pushButton_9->setEnabled(true);
			ui.pushButton_9->setCursor(Qt::PointingHandCursor);
			ui.pushButton_9->setStyleSheet("color:#000");
		}
		else {
			ui.pushButton_9->setEnabled(false);
			ui.pushButton_9->setCursor(Qt::ForbiddenCursor);
			ui.pushButton_9->setStyleSheet("color:#eee");
		}
	}

	

	ui.pushButton_6->setEnabled(true);
	ui.pushButton_6->setStyleSheet("color:#000");

	
}

void CloudDiskWidget::slot_button_page()
{
    //TODO:翻页相关
    if (sender() == ui.pushButton_2)
    {
        //首页
		m_var.usIndex_page = 0;
		ui.spinBox->setValue(1);

		//
		bRefresh();


    }
    else if (sender() == ui.pushButton_3)
    {
        //上一页

		if (m_var.usIndex_page == 0)  return;
		//
		m_var.usIndex_page--;

		QString page = ui.spinBox->text();

		ui.spinBox->setValue(page.toInt() - 1);

		//
		bRefresh();
    }
    else if (sender() == ui.pushButton_4)
    {
        //下一页
		m_var.usIndex_page++;

		QString page = ui.spinBox->text();
		
		ui.spinBox->setValue(page.toInt()+ 1 );

		
		//
		bRefresh();

    }
    else if (sender() == ui.pushButton_5)
    {
        //GO
       // int page = ui.spinBox->value();

		m_var.usIndex_page = ui.spinBox->value();
		if (m_var.usIndex_page)  m_var.usIndex_page--;
		//
		
		//
		this->bRefresh();

    }
}

QString CloudDiskWidget::getCurrentId()
{
    if (ui.tableWidget->rowCount() == 0)
    {
        return "";
    }
    int row = ui.tableWidget->currentRow();
	QString infoId = ui.tableWidget->item(row, 0)->text();



    return ui.tableWidget->item(row, 0)->text();
}



void CloudDiskWidget::updateProcessStatus(QString id, QString txt)
{

	//traceLogA((char*)"updateProcessStatus1111111111111111111111:%s %d", txt.toStdString().c_str(), id);

	//67%( 163800k ) 发送中 uploading D:/qycx/upload/test.data (0)

	std::wstring wstr(txt.toStdWString());
	printLog1(wstr.c_str());

	std::wstring wstr2(id.toStdWString());
	printLog1(wstr2.c_str());

	if (wstr.find(_T("完成 完成 uploading")) != std::wstring::npos) {
		TCHAR ss = ' ';
		std::vector<std::wstring> vecV = splitW(wstr, ss);

		//if (vecV.size() >= 4) {
		//	std::wstring fileName = vecV[3];
		//	std::lock_guard<std::mutex> lck(m_lock);
		//	std::string strFileName = to_string(fileName);

		//	m_mapUploadFile[strFileName] = 1;
		//	m_isFree = true;

		//	std::ofstream file(UFILELISTNAME, std::ios::app);
		//	if (file.is_open()) {
		//		file << strFileName << std::endl; 
		//		file.close(); 
		//	}			

		//	if (m_AutoRightPop) {
		//		m_AutoRightPop->SetProgress(100);				
		//		/*m_AutoRightPop->startClose();

		//		delete m_AutoRightPop;
		//		m_AutoRightPop = nullptr;*/
		//	}
		//}
		
		std::wstring fileName;
		for (int i = 3; i < vecV.size() - 1; ++i) {
			if (!fileName.empty())
				fileName += ss;

			fileName += vecV[i];
		}

		if (!fileName.empty()) {
			std::string strFileName = to_string(fileName);

			m_mapUploadFile[strFileName] = 1;
			m_isFree = true;

			std::ofstream file(UFILELISTNAME, std::ios::app);
			if (file.is_open()) {
				file << strFileName << std::endl;
				file.close();
			}

			if (m_AutoRightPop) {
				m_AutoRightPop->SetProgress(100);
			}
		}
	}
	else if (wstr.find(_T("发送中 uploading")) != std::wstring::npos) {
		TCHAR ss = ' ';
		std::vector<std::wstring> vecV = splitW(wstr, ss);

		if (vecV.size() >= 4) {
			std::wstring per = vecV[0];

			int pos = per.find(_T("%"));
			std::lock_guard<std::mutex> lck(m_lock);
			if (pos != std::wstring::npos) {
				std::wstring per2 = per.substr(0, pos);

				int per = _wtoi(per2.c_str());
				if (m_AutoRightPop)
					m_AutoRightPop->SetProgress(per);
			}


			std::wstring size = vecV[1];

			long sizeCur = atol(QString::fromStdWString(size.c_str()).toStdString().c_str());	

			if (sizeCur == 0) {
				m_start = std::chrono::steady_clock::now();
				m_lastSize = 0;
				if (m_AutoRightPop)
					m_AutoRightPop->SetSize("0 kb/s");
			}
			else {
				auto end = std::chrono::steady_clock::now();
				std::chrono::duration<double> elapsed_seconds = end - m_start;
				double second = elapsed_seconds.count();

				if(second > 0) {
					long speed = (sizeCur - m_lastSize) / second * 8;

					std::string str = std::to_string(speed);
					str.append(" kb/s");

					if (m_AutoRightPop)
						m_AutoRightPop->SetSize(str.c_str());
				}
				else {
					printLogChar1("second <= 0");
				}

				m_lastSize = sizeCur;
				m_start = std::chrono::steady_clock::now();

			}

			

			//std::string strFileName = to_string(fileName);
		}
	}

	

    for (int i = 0; i < ui.listWidget->count(); i++)
    {
        QListWidgetItem* item = ui.listWidget->item(i);
        if (item->data(Qt::UserRole).toString() == id)
        {
            item->setText(txt);
            return;
        }
    }
    QListWidgetItem* item = new QListWidgetItem(txt);
    item->setData(Qt::UserRole, id);
    QSize sz = item->sizeHint();
    sz.setHeight(24);
    item->setSizeHint(sz);//设置每个item的大小
    ui.listWidget->addItem(item);


}

void CloudDiskWidget::removeProcessStatus(QString id)
{
    for (int i = 0; i < ui.listWidget->count(); i++)
    {
        QListWidgetItem* item = ui.listWidget->item(i);
        if (item->data(Qt::UserRole).toString() == id)
        {
            ui.listWidget->takeItem(i);
            return;
        }
    }
}
void CloudDiskWidget::removeProessAll() {

	while (ui.listWidget->count() > 0)
	{
		QListWidgetItem* item = ui.listWidget->takeItem(0);
		delete item;
	}
}


void CloudDiskWidget::OnBnClickedButtondelete()
{
	// TODO: Add your control notification handler code here
	int					iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	RECT				rc;
	int  idc;
	RECT* pRc;

	//
	QY_MESSENGER_ID		idInfo_logicalPeer = { 0 };
	unsigned  char		ucbP2p = FALSE;
	QY_MESSENGER_ID		idInfo_req = { 0 };


	//
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  goto  errLabel;

	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  goto  errLabel;
	//
	HWND  m_hWnd = (HWND)this->winId();
	HWND  hParent = m_hWnd;

	TCHAR							tBuf[128];
	int								nItems = 0;

	//
	HWND  hTalker_res = NULL;
	if (pFuncs->pf_talkToMessenger(pMisCnt->procOfflineRes.idInfo_resServ.ui64Id, 0, TRUE, FALSE, &hTalker_res)) {
		goto  errLabel;
	}



	//
	if (m_var.hDlgTalk_mgr)
	{
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var* pDlgTalkVar;
		pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(m_var.hDlgTalk_mgr);
		if (!pDlgTalkVar)  goto  errLabel;
		//
		if (!isTalkerShadowMgr(pDlgTalkVar->addr))  goto  errLabel;

		//
		idInfo_logicalPeer.ui64Id = pDlgTalkVar->addr.idInfo.ui64Id;
		if (pDlgTalkVar->addr.uiObjType != CONST_objType_imGrp)  ucbP2p = TRUE;
		idInfo_req.ui64Id = pDlgTalkVar->addr.idInfo.ui64Id;

	}
	else {  //  me
	}






	//
	LVITEM				lvItem;

	memset(&lvItem, 0, sizeof(lvItem));
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvItem.iItem = nItems;
	lvItem.pszText = tBuf;
	lvItem.cchTextMax = mycountof(tBuf);
	int iSelectItem = table_row;

	if (iSelectItem >= 0 && iSelectItem < m_var.reses_retrieved.usCnt) {
		RES_inProcess* pMem_res = &m_var.reses_retrieved.mems[iSelectItem];
		//
		QMessageBox MBox;
		MBox.setWindowTitle(u8"提示");
		MBox.setText(u8"确定要删除该文件吗？");
		MBox.setWindowIcon(QIcon(":/Resources/Images/Login/qmClient.png"));
		QPushButton* agreeBut = MBox.addButton(u8"确认", QMessageBox::AcceptRole);
		QPushButton* cancel = MBox.addButton(u8"取消", QMessageBox::AcceptRole);
		MBox.exec();
		if (MBox.clickedButton() == (QAbstractButton*)cancel) {
			//在 Qt Creator 的输出窗口中输出指定字符串
			goto  errLabel;
		}

		//if (myMessageBox(hParent, _T("Are you sure to delete?"), _T("www.qycx.com"), MB_YESNO) != IDYES)  goto  errLabel;
		//

				//
		//
		PROC_offlineRes_del	req;
		memset(&req, 0, sizeof(req));
		req.uiType = CONST_imCommType_procOfflineRes;
		req.usSubtype = CONST_procOfflineResSubtype_del;
		req.hTool_offlineRes = m_hWnd;
		//
		req.idInfo_logicalPeer.ui64Id = idInfo_logicalPeer.ui64Id;
		//
		safeTcsnCpy(pMem_res->res.name, req.fileName, mycountof(req.fileName));
		req.idInfo_sender.ui64Id = pMem_res->res.res.idInfo.ui64Id;
		req.tCreationTime = pMem_res->res.tCreationTime;


		//
		RES_inProcess* pMem_task = NULL;

		if (m_var.reses_beingProced.usCnt >= mycountof(m_var.reses_beingProced.mems))  goto  errLabel;
		pMem_task = &m_var.reses_beingProced.mems[m_var.reses_beingProced.usCnt];
		memset(pMem_task, 0, sizeof(pMem_task[0]));
		safeTcsnCpy(req.fileName, pMem_task->res.name, mycountof(pMem_task->res.name));
		pMem_task->res.res.idInfo.ui64Id = req.idInfo_sender.ui64Id;
		//
		pMem_task->usSubtype = CONST_procOfflineResSubtype_del;
		m_var.reses_beingProced.usCnt++;




		//		
		unsigned  int  uiTranNo_wait = 0;
		{
			MACRO_prepareForTran();
			uiTranNo_wait = uiTranNo;
		}

		//
		startProgress(&pQyMc->gui.progress, uiTranNo_wait);

		//
		QY_WMBUF_COMM	wmBuf;
		memset(&wmBuf, 0, sizeof(wmBuf));
		wmBuf.uiType = CONST_qyWmParam_procOfflineRes;
		wmBuf.u.procOfflineRes.ui64Id_req = idInfo_req.ui64Id;
		wmBuf.u.procOfflineRes.pPROC_offlineRes_u = &req;
		wmBuf.u.procOfflineRes.uiTranNo_wait = uiTranNo_wait;
		if (!SendMessageTimeout(hTalker_res, CONST_qyWm_comm, 0, (LPARAM)&wmBuf, 0, 1000, NULL))  goto  errLabel;
		//
		if (!wmBuf.u.procOfflineRes.uiTranNo_real)  goto  errLabel;
		pMem_task->uiTranNo_real = wmBuf.u.procOfflineRes.uiTranNo_real;
		//
		if (showProgress(&pQyMc->gui.progress, &pQyMc->cusRes, hParent, _T("Please waiting"), NULL, 30, -1, uiTranNo_wait) != IDOK) {
			goto  errLabel;
		}

	}
	else  if (m_var.listCtrl.iSelectItem >= m_var.reses_retrieved.usCnt && m_var.listCtrl.iSelectItem < m_var.reses_retrieved.usCnt + m_var.reses_beingProced.usCnt) {
		//
		
		


		if (myMessageBox(hParent, _T("Are you sure to cancel the task?"), _T("www.qycx.com"), MB_YESNO) != IDYES)  goto  errLabel;
		
		//
		int  i;
		i = m_var.listCtrl.iSelectItem - m_var.reses_retrieved.usCnt;
		for (; i < m_var.reses_beingProced.usCnt - 1; i++) {
			RES_inProcess* pMem = &m_var.reses_beingProced.mems[i];
			pMem[0] = pMem[1];
		}
		m_var.reses_beingProced.usCnt--;
		//

	}


	//
	if (m_var.listCtrl.iSelectItem < 0 || m_var.listCtrl.iSelectItem >= m_var.reses_retrieved.usCnt + m_var.reses_beingProced.usCnt) {
		m_var.listCtrl.iSelectItem = -1;
	}



	//
	bDisplay();





errLabel:
	return;
}

void CloudDiskWidget::OnBnClickedButtondownload()
{
	// TODO: Add your control notification handler code here
	int					iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	RECT				rc;
	int  idc;
	RECT* pRc;

	//
	QY_MESSENGER_ID		idInfo_logicalPeer = { 0 };
	unsigned  char		ucbP2p = FALSE;
	QY_MESSENGER_ID		idInfo_req = { 0 };


	//
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  goto  errLabel;

	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  goto  errLabel;
	//
	HWND  m_hWnd = (HWND)this->winId();
	HWND  hParent = m_hWnd;

	TCHAR							tBuf[128];
	int								nItems = 0;

	//
	LVITEM				lvItem;

	memset(&lvItem, 0, sizeof(lvItem));
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvItem.iItem = nItems;
	lvItem.pszText = tBuf;
	lvItem.cchTextMax = mycountof(tBuf);
	int iSelectItem = table_row;

	if (iSelectItem < 0 || iSelectItem >= m_var.reses_retrieved.usCnt)  goto  errLabel;
	RES_inProcess* pMem = &m_var.reses_retrieved.mems[iSelectItem];

	//
	HWND  hTalker_res = NULL;
	BOOL  bNeedNotShowWnd = TRUE;
#ifdef  __DEBUG__
	//bNeedNotShowWnd  =  FALSE;
#endif
	//
	if (pFuncs->pf_talkToMessenger(pMisCnt->procOfflineRes.idInfo_resServ.ui64Id, 0, bNeedNotShowWnd, FALSE, &hTalker_res)) {
		goto  errLabel;
	}



	//
	if (m_var.hDlgTalk_mgr)
	{
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var* pDlgTalkVar;
		pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(m_var.hDlgTalk_mgr);
		if (!pDlgTalkVar)  goto  errLabel;
		//
		if (!isTalkerShadowMgr(pDlgTalkVar->addr))  goto  errLabel;

		//
		idInfo_logicalPeer.ui64Id = pDlgTalkVar->addr.idInfo.ui64Id;
		if (pDlgTalkVar->addr.uiObjType != CONST_objType_imGrp)  ucbP2p = TRUE;
		idInfo_req.ui64Id = pDlgTalkVar->addr.idInfo.ui64Id;

	}
	else {
	}


	//
	//
	PROC_offlineRes_download	req;
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_procOfflineRes;
	req.usSubtype = CONST_procOfflineResSubtype_download;
	req.hTool_offlineRes = m_hWnd;
	//
	safeTcsnCpy(pMem->res.name, req.fileName, mycountof(req.fileName));
	req.idInfo_sender.ui64Id = pMem->res.res.idInfo.ui64Id;
	req.tCreationTime = pMem->res.tCreationTime;
	//
	req.idInfo_logicalPeer.ui64Id = idInfo_logicalPeer.ui64Id;

	//
	{
		if (m_var.reses_beingProced.usCnt >= mycountof(m_var.reses_beingProced.mems))  goto  errLabel;
		RES_inProcess* pMem = &m_var.reses_beingProced.mems[m_var.reses_beingProced.usCnt];
		memset(pMem, 0, sizeof(pMem[0]));
		safeTcsnCpy(req.fileName, pMem->res.name, mycountof(pMem->res.name));
		pMem->usSubtype = CONST_procOfflineResSubtype_download;
		m_var.reses_beingProced.usCnt++;
	}

	//
	QY_WMBUF_COMM	wmBuf;
	memset(&wmBuf, 0, sizeof(wmBuf));
	wmBuf.uiType = CONST_qyWmParam_procOfflineRes;
	wmBuf.u.procOfflineRes.ui64Id_req = idInfo_req.ui64Id;
	wmBuf.u.procOfflineRes.pPROC_offlineRes_u = &req;
	wmBuf.u.procOfflineRes.uiTranNo_wait = 0;
	if (!SendMessageTimeout(hTalker_res, CONST_qyWm_comm, 0, (LPARAM)&wmBuf, 0, 1000, NULL))  goto  errLabel;
	//
	int  i;
	i = 0;

	//
	ResesDisplay();



	//
	iErr = 0;

errLabel:
	return;

}



__declspec(dllexport)  void  dlgOfflineRes_upload(HWND  hParent, HWND  hDlg_offlineRes, LPCTSTR  fileName)
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
	CloudDiskWidget* pDlg = (CloudDiskWidget*)QWidget::find((WId)hDlg_offlineRes);
	if (!pDlg)  goto  errLabel;

	HWND  m_hWnd = hDlg_offlineRes;
	DlgOfflineRes_var& m_var = pDlg->m_var;

	//
	HWND  hTalker_res = NULL;
	if (pFuncs->pf_talkToMessenger(pMisCnt->procOfflineRes.idInfo_resServ.ui64Id, 0, TRUE, FALSE, &hTalker_res)) {
		goto  errLabel;
	}

	//
	{
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var* pDlgTalkVar;
		pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(m_var.hDlgTalk_mgr);
		if (!pDlgTalkVar)  goto  errLabel;
		//
		if (!isTalkerShadowMgr(pDlgTalkVar->addr))  goto  errLabel;
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
		req.idInfo_logicalPeer.ui64Id = pDlgTalkVar->addr.idInfo.ui64Id;
		//

		//
		if (m_var.reses_beingProced.usCnt >= mycountof(m_var.reses_beingProced.mems))  goto  errLabel;
		RES_inProcess* pMem = &m_var.reses_beingProced.mems[m_var.reses_beingProced.usCnt];
		memset(pMem, 0, sizeof(pMem[0]));
		safeTcsnCpy(req.fullFileName, pMem->res.name, mycountof(pMem->res.name));
		pMem->usSubtype = req.usSubtype;
		m_var.reses_beingProced.usCnt++;
		//
		int  index = m_var.reses_retrieved.usCnt + m_var.reses_beingProced.usCnt - 1;
		HWND  hCtrl = ::GetDlgItem(m_hWnd, m_var.guiData.iIDC_LIST_offlineRes);
		::SendMessage(hCtrl, LB_INSERTSTRING, (WPARAM)index, (LPARAM)pMem->res.name);

		//
		QY_WMBUF_COMM	wmBuf;
		memset(&wmBuf, 0, sizeof(wmBuf));
		wmBuf.uiType = CONST_qyWmParam_procOfflineRes;
		wmBuf.u.procOfflineRes.ui64Id_req = pDlgTalkVar->addr.idInfo.ui64Id;
		wmBuf.u.procOfflineRes.pPROC_offlineRes_u = &req;
		wmBuf.u.procOfflineRes.uiTranNo_wait = 0;
		if (!SendMessageTimeout(hTalker_res, CONST_qyWm_comm, 0, (LPARAM)&wmBuf, 0, 1000, NULL))  goto  errLabel;
		//
		pMem->iTaskId = wmBuf.u.procOfflineRes.iTaskId;
		//
		int  i;
		i = 0;


	}

	//
	pDlg->ResesDisplay();

	//
	iErr = 0;

errLabel:

	return;
}

bool CloudDiskWidget::GetNewFile(QString& newFile) {
	CCtxQyMc* pQyMc = g_pQyMc;
	//QString rootPath = "d:\\qycx\\upload\\";
	QString rootPath = pQyMc->cfg.uploadPath;
	QDir dir(rootPath);
	dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot); 
	QFileInfoList fileInfos = dir.entryInfoList(); 

	foreach(const QFileInfo & fileInfo, fileInfos) {
		QString filePath = fileInfo.absoluteFilePath();

		if (m_mapUploadFile.find(filePath.toStdString()) != m_mapUploadFile.end()) {
			continue;
		}
		newFile = filePath;
		return true;
		//printLogChar1(filePath.toStdString().c_str());
	}

	return false;
}

void CloudDiskWidget::slot_button_file()
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

    //TODO:文件相关
    if (sender() == ui.pushButton_6)
    {
        //下载

		OnBnClickedButtondownload();

    }
	else if (sender() == ui.pushButton_auto)
	{
		if (m_autoUpload) {
			m_autoUpload = false;
			ui.pushButton_auto->setText(u8"开始自动上传");
			m_isFree = true;
			m_timer->stop();
			
			
		}
		else {
			
			m_timer->start(2000);
			m_autoUpload = true;
			ui.pushButton_auto->setText(u8"停止自动上传");
			m_isFree = true;

			
		}	
		

	}
    else if (sender() == ui.pushButton_7)
    {


		LPCTSTR							lpszDefExt = TEXT("*\0");
		LPCTSTR							lpszFilter = CONST_FILE_FILTER_allFiles;
		LPCTSTR							title = TEXT("Send File...\0");
		DWORD								dwFlags = OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;
		TCHAR   tDir[256];
		int cntt;
		QString document_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        //上传
		QString strFileName;
		QFileDialog* pFilename = new QFileDialog(this, Qt::Dialog);
		if (pFilename == NULL) return;

		getSelectDir(tDir ,mycountof( tDir));
		if (!bDir(tDir)) {
			safeTcsnCpy((TCHAR*)(document_path).utf16(), tDir , mycountof(tDir));
		}


		pFilename->setDirectory(QString::fromStdWString(tDir) );//设置打开的默认目录.       ////////  需要修改
		pFilename->setNameFilter(tr("*"));//设置限定文件类型
		pFilename->setOption(QFileDialog::DontResolveSymlinks);//可以加载链接路径而不会跳转

		if (pFilename->exec() == QFileDialog::Accepted)
		{
			strFileName = pFilename->selectedFiles().first();
		}

		delete pFilename;

		if (strFileName.isEmpty())
		{
			QMessageBox::information(this, u8"提示", u8"未选中文件");
			return;
		}
		TCHAR* fileName = (TCHAR*)strFileName.utf16();

		if (!pProcInfo->getDirAndFinalName(fileName, tDir, mycountof(tDir), null, 0)) {
			saveSelectDir(tDir);
		}

		qDebug() << "----------------------" << strFileName;

		
		dlgOfflineRes_upload_qt(strFileName);

    }
    else if (sender() == ui.pushButton_8)
    {
        //刷新
		//bRefresh();
		/*
		if (!m_PopUPWindow) {
			m_PopUPWindow = new CPopUPWindow();
			m_PopUPWindow->show();
			m_PopUPWindow->showAnimation();
		}
		else {
			//m_PopUPWindow->clearAll();
			
			//m_PopUPWindow->show();

			delete m_PopUPWindow;
			

			m_PopUPWindow = new CPopUPWindow();
			m_PopUPWindow->show();
			m_PopUPWindow->showAnimation();
			
		}
		*/

		if (!m_RightPop) {
			m_RightPop = new RightPop();
			m_RightPop->show();
			
		}
		else {
			//m_PopUPWindow->clearAll();

			//m_PopUPWindow->show();
			/*
			delete m_RightPop;


			m_RightPop = new RightPop();
			m_RightPop->show();
			*/


			m_RightPop->startClose();
			delete m_RightPop;
			m_RightPop = nullptr;


		}
		
		 
    }
    else if (sender() == ui.pushButton_9)
    {
        //删除
		OnBnClickedButtondelete();
    }
    else if (sender() == ui.pushButton_10)
    {
        //显示所有下载
			// TODO: Add your control notification handler code here
		int  iErr = -1;
		MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
		if (!pProcInfo) return ;

		//
		TCHAR* pDir = pProcInfo->cfg.policy.dirToSaveFile;

		if (bDir(pDir)) {		//  
			ShellExecute(NULL, _T("open"), pDir, _T(""), NULL, SW_SHOW);
		}


    }
    else if (sender() == ui.pushButton_11)
    {
        //取消
		this->close();
    }
}


void CloudDiskWidget::dlgOfflineRes_upload_qt(QString strFileName) {
	TCHAR* fileName = (TCHAR*)strFileName.utf16();

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
	if (!pProcInfo->bUse_imObjView_as_guiWnd()) {
		if (bApp_ts_3d(pQyMc)) {
			GBuf_d3d_isCli* pGBuf = (GBuf_d3d_isCli*)pQyMc->pGBuf_d3d;
			if (!IsWindow(pGBuf->hWall_d3d))  goto  errLabel;
			hParent = pGBuf->hWall_d3d;
		}
	}

	//
	//if (qyBrowseForFile(hParent, TRUE, lpszDefExt, dwFlags, CONST_FILE_FILTER_allFiles, title, NULL, pQyMc, pathCStr))  goto  errLabel;

	//
	dlgOfflineRes_upload(hParent, m_hWnd, fileName);

	iErr = 0;

errLabel:

	return;

}


void CloudDiskWidget::paintEvent(QPaintEvent* event)
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
		painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
		// 圆角阴影边框;
		//painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
	}
}

void CloudDiskWidget::dragEnterEvent(QDragEnterEvent* event) //拖动文件到窗口，触发
{
	if (event->mimeData()->hasUrls())
	{
		event->acceptProposedAction(); //事件数据中存在路径，方向事件
	}
	else
	{
		event->ignore();
	}
}

void CloudDiskWidget::dragMoveEvent(QDragMoveEvent* event) //拖动文件到窗口移动文件，触发
{

}

void CloudDiskWidget::dropEvent(QDropEvent* event) //拖动文件到窗口释放文件，触发
{
	const QMimeData* mimeData = event->mimeData();
	if (mimeData->hasUrls())
	{
		QList<QUrl> urls = mimeData->urls();
		QString fileName = urls.at(0).toLocalFile();
		//
		if  (  m_var.idInfo.ui64Id)
		//
		{
			dlgOfflineRes_upload_qt(fileName);
		}
		
	//	lineEdit->setText(fileName);
	}
}