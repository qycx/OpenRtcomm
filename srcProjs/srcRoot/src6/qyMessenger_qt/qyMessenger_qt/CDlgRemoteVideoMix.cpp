#include "CDlgRemoteVideoMix.h"

#include <QFileSystemModel>
#include <QTableView>

#include "help_getDlgTalkVar.h"
#include "dlgtalkproc.h"
#include "objType_tmp.h"

#include "isCliExPublic.h"
#include "isCliD3dPublic.h"

#include "qmcCommFunc_isCli.h"

#include "qmcDynBmp.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QResizeEvent>
#include <QMessageBox>
#include <QDesktopServices>
#include <QProcess>
#include <QStandardItemModel>

#include "ZoomLabel.h"

#define BUTTON_AREA_WIDTH 200

#define BUTTON_INTERVAL 50
#define BUTTON_LEFT 150
#define BUTTON_WIDTH 120
#define BUTTON_HEIGHT 40


QString ChangeName(const QString& name) {

	if (name.indexOf("IC") >= 0)
		return QString(u8"工业相机");
	else if (name.indexOf("Rtsp") >= 0) {
		return QString(u8"监控");
	}

	return name;

}

// 处理文件更改通知
void HandleFileChange(CDlgRemoteVideoMix* mix, DWORD action, const std::wstring& filename) {
	if (action == FILE_ACTION_ADDED) {
		//std::wcout << L"New file added: " << filename << std::endl;
		mix->doNewFile(QString::fromWCharArray(filename.c_str()));
	}
}

// 监控目录更改
void MonitorDirectory(CDlgRemoteVideoMix* mix, const std::wstring& directory, bool& isRun, bool& isChangePath) {
	HANDLE hDir = CreateFileW(
		directory.c_str(),
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
		NULL
	);

	if (hDir == INVALID_HANDLE_VALUE) {
		//std::wcerr << L"Failed to open directory: " << directory << std::endl;
		return;
	}

	BYTE buffer[1024];
	DWORD bytesReturned;
	OVERLAPPED overlapped = { 0 };
	overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (ReadDirectoryChangesW(
		hDir,
		buffer,
		sizeof(buffer),
		TRUE,
		FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_CREATION,
		&bytesReturned,
		&overlapped,
		NULL
	) == FALSE) {
		//std::wcerr << L"Failed to start monitoring directory: " << directory << std::endl;
		CloseHandle(hDir);
		CloseHandle(overlapped.hEvent);
		return;
	}

	DWORD waitStatus;
	while (isRun && !isChangePath) {
		waitStatus = WaitForSingleObject(overlapped.hEvent, INFINITE);
		if (waitStatus == WAIT_OBJECT_0) {
			if (GetOverlappedResult(hDir, &overlapped, &bytesReturned, FALSE)) {
				FILE_NOTIFY_INFORMATION* fni = (FILE_NOTIFY_INFORMATION*)buffer;
				do {
					std::wstring filename(fni->FileName, fni->FileNameLength / sizeof(wchar_t));
					HandleFileChange(mix, fni->Action, filename);
					if (fni->NextEntryOffset == 0) {
						break;
					}
					fni = (FILE_NOTIFY_INFORMATION*)((BYTE*)fni + fni->NextEntryOffset);
				} while (true);
			}
			if (ReadDirectoryChangesW(
				hDir,
				buffer,
				sizeof(buffer),
				TRUE,
				FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_CREATION,
				&bytesReturned,
				&overlapped,
				NULL
			) == FALSE) {
				//std::wcerr << L"Failed to continue monitoring directory: " << directory << std::endl;
				break;
			}
		}
	}

	CloseHandle(hDir);
	CloseHandle(overlapped.hEvent);
}


bool compareByModificationTime(const QFileInfo& file1, const QFileInfo& file2)
{
	return file1.lastModified() > file2.lastModified();
}

QFileInfoList getNewestFiles(const QString& directoryPath, int maxCount)
{
	QDir directory(directoryPath);

	// 获取目录下所有文件（不包括子目录）
	QFileInfoList files = directory.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

	// 按修改时间排序（从新到旧）
	std::sort(files.begin(), files.end(), compareByModificationTime);

	// 返回前 maxCount 个文件
	return files.mid(0, maxCount);
}

Worker::Worker(CDlgRemoteVideoMix* mix, const std::wstring& path) {
	m_isRun = true;
	m_path = path;
	m_mix = mix;
}
Worker::~Worker() {
	m_isRun = m_isRun;
}

void Worker::stop()
{
	m_isRun = false;
}

void Worker::ChangePath(const std::wstring& path)
{
	m_path = path;
	m_isPathChange = true;
}

void Worker::doWork() {
	int i = 0;
	while (m_isRun) {
		i++;
		QThread::msleep(200);
		MonitorDirectory(m_mix, m_path.c_str(), m_isRun, m_isPathChange);
		//emit progress(i);
		m_isPathChange = false;
		Sleep(2);
	}
	emit workFinished();
}


CDlgRemoteVideoMix::CDlgRemoteVideoMix(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::CDlgRemoteVideoMixClass())
{
	ui->setupUi(this);

	memset(&m_var, 0, sizeof(m_var));

    InitControl();


	m_imgTimer = new QTimer(this);
	connect(m_imgTimer, &QTimer::timeout, this, &CDlgRemoteVideoMix::onTimeout);
	m_imgTimer->start(2000); 

	connect(this, &CDlgRemoteVideoMix::new_file, this, &CDlgRemoteVideoMix::onNewFile);
	
	/*m_timerReflash = new QTimer(this);
	connect(m_timerReflash, &QTimer::timeout, this, &CDlgRemoteVideoMix::onTimeoutReflash);
	m_timerReflash->start(3000);*/

	startWork();
}


void CDlgRemoteVideoMix::startWork() {
	if (m_thread)
		return;

	m_thread = new QThread();
	m_worker = new Worker(this, m_path.toStdWString());
	m_worker->moveToThread(m_thread);

	connect(m_thread, &QThread::started, m_worker, &Worker::doWork);
	connect(m_worker, &Worker::progress, this, &CDlgRemoteVideoMix::updateProgress);
	connect(m_worker, &Worker::workFinished, this, &CDlgRemoteVideoMix::onWorkFinished);
	connect(m_worker, &Worker::workFinished, m_thread, &QThread::quit);
	connect(m_worker, &Worker::workFinished, m_worker, &QObject::deleteLater);
	connect(m_thread, &QThread::finished, m_thread, &QObject::deleteLater);

	m_thread->start();
}

void CDlgRemoteVideoMix::onNewFile(const QString& fileName) {
	do {
		QAbstractItemModel* model = ui->listView_file->model();
		if (!model) break;

		// 检查是否是 FileSystemSortProxyModel 或类似的代理模型
		QStandardItemModel* viewModel = qobject_cast<QStandardItemModel*>(model);
		if (!viewModel) break;

		QStandardItem* item = new QStandardItem();

		item->setText(fileName);


		item->setIcon(QIcon::fromTheme("image-x-generic"));

		//item->setIcon(QIcon(":/images/custom_icon.png"));  // 自定义图标

		viewModel->insertRow(0, item);

		if (viewModel->rowCount() > 50) {
			
			viewModel->removeRow(viewModel->rowCount() - 1);
		}

	} while (0);
}

void CDlgRemoteVideoMix::onWorkFinished() 
{
	if (m_thread) {
		m_thread->quit();
		m_thread->wait();
		m_thread->sleep(1);
		delete m_thread;
		m_thread = nullptr;
	}

	if (m_worker) {
		m_worker->moveToThread(nullptr);

		delete m_worker;
		m_worker = nullptr;
	}

	

	

	

}

void CDlgRemoteVideoMix::stopWork() {

	if (m_worker) {
		m_worker->stop();
	    
		//m_thread->terminate();
	}

}

void CDlgRemoteVideoMix::doNewFile(const QString& fileName) {
	emit new_file(fileName);
}

void CDlgRemoteVideoMix::updateProgress(int value) {
	// 这个槽函数在主线程中执行，可以安全更新UI
	//m_label->setText(QString("Progress: %1").arg(value));
}

QString getFirstFilePath(QListView* listView) {
	QAbstractItemModel* model = listView->model();
	if (!model) return QString();

	// 检查是否是 FileSystemSortProxyModel 或类似的代理模型
	QStandardItemModel* stdModel = qobject_cast<QStandardItemModel*>(model);
	if (!stdModel) return QString();

	QStandardItem* firstItem = stdModel->item(0);
	if (firstItem) {
		return firstItem->text();
	}

	return QString();
	
}

QString getFirstFilePath_bak(QListView* listView) {
	// 获取视图的模型
	QAbstractItemModel* model = listView->model();
	if (!model) return QString();

	// 检查是否是 FileSystemSortProxyModel 或类似的代理模型
	QSortFilterProxyModel* proxyModel = qobject_cast<QSortFilterProxyModel*>(model);
	if (!proxyModel) return QString();

	// 获取源模型（应该是 QFileSystemModel）
	QFileSystemModel* fileSystemModel = qobject_cast<QFileSystemModel*>(proxyModel->sourceModel());
	if (!fileSystemModel) return QString();

	// 获取代理模型中第一个项的索引
	//QModelIndex firstIndex = proxyModel->index(0, 0);
	//if (!firstIndex.isValid()) return QString();

	// 映射回源模型的索引
	//QModelIndex sourceIndex = proxyModel->mapToSource(firstIndex);
	QString filePath;
	QModelIndex firstIndex = proxyModel->index(0, 0, listView->rootIndex());
	if (firstIndex.isValid()) {
		// 获取第一个文件的完整路径
		filePath = fileSystemModel->filePath(proxyModel->mapToSource(firstIndex));
		//qDebug() << "第一个文件的完整路径是:" << filePath;
	}


	// 从 QFileSystemModel 获取文件路径
	//return fileSystemModel->filePath(sourceIndex);

	return filePath;
}

std::string joinPath(const std::string& path, const std::string& filename) {
	if (path.empty()) {
		return filename;
	}

	char lastChar = path.back();

	bool needsSeparator = (lastChar != '/' && lastChar != '\\');


	std::string fullPath = path;
	if (needsSeparator) {

#ifdef _WIN32
		fullPath += '\\';
#else
		fullPath += '/';
#endif
	}

	fullPath += filename;
	return fullPath;
}

void CDlgRemoteVideoMix::onTimeoutReflash() {

	static int times = 0;

	times++;

	emit to_remotevideo_resize();

	if (times > 3) {
		times = 0;
		m_timerReflash->stop();
		delete m_timerReflash;
		m_timerReflash = nullptr;
	}
		
}

void CDlgRemoteVideoMix::InitListViewFile() {
	do {
		QAbstractItemModel* model = ui->listView_file->model();
		if (!model) break;

		// 检查是否是 FileSystemSortProxyModel 或类似的代理模型
		QStandardItemModel* viewModel = qobject_cast<QStandardItemModel*>(model);
		if (!viewModel) break;

		viewModel->clear();


		if (m_path.isEmpty()) break;

		QFileInfoList newestFiles = getNewestFiles(m_path, 50);
		for (const QFileInfo& fileInfo : newestFiles) {
			/*qDebug() << fileInfo.fileName()
				<< "Last modified:" << fileInfo.lastModified().toString(Qt::ISODate)
				<< "Size:" << fileInfo.size() << "bytes";*/

			QString fileName = fileInfo.fileName();

			QStandardItem* item = new QStandardItem();

			item->setText(fileName);


			item->setIcon(QIcon::fromTheme("image-x-generic"));

			//item->setIcon(QIcon(":/images/custom_icon.png"));  // 自定义图标

			viewModel->appendRow(item);
		}

	} while (0);
}

void CDlgRemoteVideoMix::onTimeout() {
	//ui->listView_file;
	
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();


	do {

		//
		DLG_objs_var* pVar = (DLG_objs_var*)&m_var;
		if (!IsWindow(pVar->guiData.param.hCurTalk))  break;
		HWND  hCur = pVar->guiData.param.hCurTalk;
		DLG_TALK_var* pCurVar = (DLG_TALK_var*)pVar->guiData.param.pCurVar;	//  getDlgTalkVar(  pVar->guiData.param.hCurTalk  );
		if (!pCurVar)  break;
		DLG_TALK_var* pMgrVar = (DLG_TALK_var*)pVar->guiData.param.pMgrVar;	//  pDlgTalkVar;
		if (!pMgrVar)  break;
		HWND  hMgr = hCur;
		if (!isTalkerShadowMgr(pCurVar->addr)) {
			TALKER_shadow* pShadow = (TALKER_shadow*)pCurVar->pShadowInfo;
			hMgr = pShadow->hMgr;
		}
		//
		myZONE* pZone = &pCurVar->av.remoteVideoZone;

		//
		int  i;
		CAP_IMAGES* pImgs = &pZone->images;
		int  cnt;
		cnt = 0;
		for (i = 0; i < mycountof(pImgs->mems); i++) {
			CAP_image* pImg;
			pImg = (CAP_IMAGE*)&pImgs->mems[i];	//  &pImages->mems[i];
			if (pImg->iW_org && pImg->iH_org
				&& pImg->iTaskId)
			{
				cnt++;
			}
		}

		//
		traceLog((TCHAR*)_T("remoteZone: cnt %d"), cnt);

		//
		int  nNeeded = 0;
		for (i = 0; i < mycountof(m_pShadowMgr->vwRuleCmd.dynBmpRules); i++) {
			if (m_pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.uiObjType)   nNeeded++;
		}
		//
		traceLog((TCHAR*)_T("dynBmpRules: nNeeded %d"), nNeeded);

		//
		if (nNeeded < cnt) {

			//
			chkTalkerRules(hMgr, pMgrVar);

			//
			for (i = 0; i < mycountof(pImgs->mems); i++) {
				CAP_image* pImg;
				pImg = (CAP_IMAGE*)&pImgs->mems[i];	//  &pImages->mems[i];
				if (pImg->iW_org && pImg->iH_org
					&& pImg->iTaskId)
				{
					dlgTalk_freeCapImageBySth_mgr(hMgr, pImg->iTaskId, &pImg->idInfo_sender);
				}

			}

		}



		//
	} while (0);






	//
	if (m_isSaveICFile != pProcInfo->cfg.policy.isSaveICFile) {
		m_isSaveICFile = pProcInfo->cfg.policy.isSaveICFile;
		SetIsSaveButtonText(m_isSaveICFile);
	}

	if (!pProcInfo->cfg.policy.isSaveICFile)
		return;

	QString path = QString::fromWCharArray(pProcInfo->cfg.policy.dirToSaveICFile);
	if (m_path != path) {
		m_path = path;
		InitListViewFile();
		m_worker->ChangePath(m_path.toStdWString());
	}

	

	//ReadData();



	
	/*FileSystemSortProxyModel* stringModel = qobject_cast<FileSystemSortProxyModel*>(ui->listView_file->model());
	if (stringModel && stringModel->rowCount() > 0) {
		QString firstItem = stringModel->stringList().first();
	}*/


	//QAbstractItemModel* model = ui->listView_file->model(); // 获取模型（可能是代理模型）

	//// 获取第一项的模型索引（行0，列0）
	//QModelIndex firstIndex = model->index(0, 0);

	//if (firstIndex.isValid()) {
	//	// 获取数据（显示文本）
	//	QString firstItemText = model->data(firstIndex, Qt::DisplayRole).toString();

	//	// 如果是文件系统模型，可以获取文件路径
	//	QVariant fileName = model->data(firstIndex, QFileSystemModel::FileNameRole);
	//	QVariant filePath = model->data(firstIndex, QFileSystemModel::FilePathRole);
	//	// 或者
	//	
	//}

	QString firstFile = getFirstFilePath(ui->listView_file);	

	if (!firstFile.isEmpty() && !m_path.isEmpty()) {
		std::string filePath = joinPath(m_path.toStdString(), firstFile.toStdString());
		//QPixmap pixmap(filePath.c_str()); // 支持常见格式如JPG, PNG, BMP等
		//ui->label_img->setPixmap(pixmap);
		m_ZoomLabelImg->setPixmap(filePath.c_str());

	}
	else {
		//ui->label_img->setPixmap(QPixmap());
		m_ZoomLabelImg->setPixmap("");
	}

}

CDlgRemoteVideoMix::~CDlgRemoteVideoMix()
{
	stopWork();
	DeleteAllButton();

	//
	if (m_var.pData) {
		MACRO_safeFree(m_var.pData);
	}

	//
	if (m_imgTimer) {
		m_imgTimer->stop();
		delete m_imgTimer;
		m_imgTimer = nullptr;		
	}

	if (m_timerReflash) {
		m_timerReflash->stop();
		delete m_timerReflash;
		m_timerReflash = nullptr;
	}

	if (m_ZoomLabelImg) {
		delete m_ZoomLabelImg;
		m_ZoomLabelImg = nullptr;
	}

	if (m_var.pData_items)  free(m_var.pData_items);
	MACRO_safeFree(m_var.pData);	

	delete ui;

	
}

void CDlgRemoteVideoMix::Init(HWND hCurTalk, DLG_TALK_var* pMgrVar, QY_wmBuf_command* pWmBuf, TALKER_shadow_mgr* pShadowMgr, HWND hMgr, HWND hShow)
{
	m_hCurTalk = hCurTalk;
	m_pMgrVar = pMgrVar;
	m_pWmBuf = pWmBuf;
	m_pShadowMgr = pShadowMgr;
	m_hMgr = hMgr;
	m_hShow = hShow;

}

int  tmpHandler_getDynBmpsMix(void* p0, void* p1, void* p2)
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


int  fillImObjs_selectRemoteVideo(HWND  hDlg, void* pVarParam, CDlgRemoteVideoMix* mix/*QListWidget* IDC_LIST0*/)
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
		int  nProgress = 30;
		nProgress = 8;
		//
		TCHAR* pHint = (TCHAR*)_T("正在寻找工业相机...");
		//
		if (showProgress(&pQyMc->gui.progress, &pQyMc->cusRes, (HWND)mix->winId()/*hParent*/, pHint, NULL, nProgress, -1, uiTranNo) != IDOK) {
			goto  errLabel;
		}

		COMMON_PARAM	commonParam3_i;
		COMMON_PARAM	commonParam3_o;
		BOOL			bRemove = FALSE;

		MACRO_makeCommonParam3(0, (void*)uiTranNo, (void*)bRemove, commonParam3_i);
		MACRO_makeCommonParam3((void*)pDynBmps, (void*)maxCnt, (void*)&cnt, commonParam3_o);
		qTraverse(pMgrVar->m_pProcessQ, tmpHandler_getDynBmpsMix, &commonParam3_i, &commonParam3_o);
		//
		bRemove = TRUE;
		MACRO_makeCommonParam3(0, (void*)uiTranNo, (void*)bRemove, commonParam3_i);
		qRemoveMsg(pMgrVar->m_pProcessQ, tmpHandler_getDynBmpsMix, &commonParam3_i, NULL);
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

		QRect rect = mix->geometry();

		//int interval = 50;
		//int left = 150;
		//int width = 120;

		for (n = 0; ; n++) {
			if (n >= cnt)  break;
			//
			QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);

			_sntprintf(pColumns[n].label, mycountof(pColumns[n].label), _T("%s %d"), qyGetDesByType1(pTable, pDynBmps[n].qisResObj.resObj.uiObjType), (int)pDynBmps[n].qisResObj.resObj.usIndex_obj);
			if (pDynBmps[n].qisResObj.resObj.usHelp_subIndex)  _sntprintf(pColumns[n].label, mycountof(pColumns[n].label), _T("%s.%d"), pColumns[n].label, (int)pDynBmps[n].qisResObj.resObj.usHelp_subIndex);
			_sntprintf(pColumns[n].label, mycountof(pColumns[n].label), _T("%s %s %s"), pColumns[n].label, pDynBmps[n].name, pDynBmps[n].cusName);
			//
			if (tmpF_bViewRemoteVideo(&pShadowMgr->vwRuleCmd_manual, pDynBmps[n].qisResObj.resObj.uiObjType, pDynBmps[n].qisResObj.resObj.usIndex_obj, pDynBmps[n].qisResObj.resObj.usHelp_subIndex))  pColumns[n].lParam = TRUE;
			//if (pColumns[n].lParam)  _sntprintf(pColumns[n].label, mycountof(pColumns[n].label), _T("%s ( %s )"), pColumns[n].label, getResStr(0, &pQyMc->cusRes, CONST_resId_manuallyStarted));
			// 

			//
			//tmpiRet = SendMessage(hCtl, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)pColumns[n].label);

			/*QListWidgetItem* item = new QListWidgetItem(QString::fromWCharArray(pColumns[n].label));
			IDC_LIST0->addItem(item);*/

			QString butLabel;
			if (pColumns[n].lParam) {
				//butLabel = QString::fromWCharArray(getResStr(0, &pQyMc->cusRes, CONST_resId_stop)) + "_" + QString::fromWCharArray(pColumns[n].label);
				butLabel = QString::fromWCharArray(getResStr(0, &pQyMc->cusRes, CONST_resId_stop)) + ChangeName(QString::fromWCharArray(pColumns[n].label));
			}		
			else {
				//butLabel = QString::fromWCharArray(getResStr(0, &pQyMc->cusRes, CONST_resId_start)) + "_" + QString::fromWCharArray(pColumns[n].label);
				butLabel = QString::fromWCharArray(getResStr(0, &pQyMc->cusRes, CONST_resId_start)) + ChangeName(QString::fromWCharArray(pColumns[n].label));
			}

			//QString butLabel = QString::fromWCharArray(pColumns[n].label);

			QPushButton* button = new QPushButton(butLabel, mix);
			button->setStyleSheet("btn");
			
			
			

			mix->InsertButton(n, button);
			

			QRect butRect;
			butRect.setX(rect.width() - BUTTON_LEFT);
			butRect.setY(BUTTON_INTERVAL * (n+1));
			butRect.setWidth(BUTTON_WIDTH);
			butRect.setHeight(40);

			button->setGeometry(butRect);

			QObject::connect(button, &QPushButton::clicked, [mix, n]() {
				mix->handleButtonClick(n); // 传递按钮编号
				});

			if (butLabel.indexOf("smallStream") >= 0) {
				button->setVisible(false);
			}
			else {
				button->show();
			}

		}

		QSize curSize = mix->size();
		mix->resize(curSize + QSize(1, 1));
		mix->resize(curSize);

	}


	iRet = 0;
errLabel:

	return  iRet;
}



int  fillImObjs(HWND  hDlg, void* pVar, CDlgRemoteVideoMix* mix/*QListWidget* IDC_LIST0*/)
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
		if (fillImObjs_selectRemoteVideo(hDlg, pVar, mix))  goto  errLabel;
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

BOOL  dlgObjs_bFillContent(HWND  hDlg, void* pVar, int  iObjType, CDlgRemoteVideoMix* mix/*QListWidget* IDC_LIST0*/)
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
		if (fillImObjs(hDlg, pVar, mix)) {
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

	/*idc = m_var.guiData.iIDC_BUTTON_contact;
	bHidden = idc_hidden == idc;
	ShowWindow(GetDlgItem(hDlg, idc), bHidden ? SW_HIDE : SW_SHOW);

	idc = m_var.guiData.iIDC_BUTTON_group;
	bHidden = idc_hidden == idc;
	ShowWindow(GetDlgItem(hDlg, idc), bHidden ? SW_HIDE : SW_SHOW);

	idc = m_var.guiData.iIDC_BUTTON_status;
	bHidden = idc_hidden == idc;
	ShowWindow(GetDlgItem(hDlg, idc), bHidden ? SW_HIDE : SW_SHOW);*/

	bRet = TRUE;

errLabel:

	return  bRet;
}

bool CDlgRemoteVideoMix::OnInitDialog()
{
	int		iErr = -1;


	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
	DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar_cur.getVar(m_hCurTalk);
	if (!pCurVar)  goto  errLabel;

	DLG_guiDataParam_objs		param;
	//
	memset(&m_dynBmpRule_selected, 0, sizeof(m_dynBmpRule_selected));

	//
	memset(&param, 0, sizeof(param));
	param.uiType = CONST_objType_selectRemoteVideo;
	param.hCurTalk = m_hCurTalk;
	param.pCurVar = pCurVar;							//  2013/06/10
	param.pMgrVar = m_pMgrVar;
	param.pObjBuf_selected = &m_dynBmpRule_selected.dynBmp;			//  2014/05/15
	param.uiSize_pObjBuf_selected = sizeof(m_dynBmpRule_selected);


	DLG_guiData_objs* p; p = (DLG_guiData_objs*)&m_var.guiData;
	if (!p)  goto  errLabel;

	memcpy(&p->param, &param, sizeof(p->param));
	

#ifdef  __APP_qyMc_touchscreen__
	//  2011/03/12
	makeDlgResizable(this->m_hWnd);
#endif

	//CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
#ifdef  __APP_qyMc_touchscreen__
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
#endif

	QY_MC* pQyMc; pQyMc = QY_GET_GBUF();
	HWND	hDlg; hDlg = (HWND)this->winId();
	//dlgLayout_objs(hDlg, &m_var.guiData);

	//if (setModalWnd(pQyMc, hDlg))  goto  errLabel;


	//  HWND	hDlg	=	this->m_hWnd;
//#ifdef  __APP_qyMc_touchscreen__
//	{
//		RECT	rc;
//		int		w, h;
//		HWND	hFrame = pQyMc->gui.hMainWnd;
//		if (!hFrame)  goto  errLabel;
//		::GetWindowRect(hFrame, &rc);
//		w = rc.right - rc.left;
//		h = rc.bottom - rc.top;
//		::MoveWindow(hDlg, rc.left, rc.top, w, h, TRUE);
//
//	}
//#else
//#if  10
//	{
//		RECT	rc;
//		int		w, h;
//		int		x;
//		::GetWindowRect(hDlg, &rc);
//		x = rc.left;
//		w = rc.right - rc.left;
//		h = rc.bottom - rc.top;
//#if  10
//		if (w < 640) {
//			x = rc.left;	//    -  (  640  -  w  )  /  2;
//			w = 640;
//		}
//		if (h < 480) {
//			h = 480;
//		}
//#endif
//		::MoveWindow(hDlg, x, rc.top, w, h, TRUE);
//	}
//#endif
//#endif

	//  sizeAllControls_dlgObjs(  hDlg,  &m_var.guiData  );

	//  SetWindowText(  _T(  "Select"  )  );
	//cusDlgRes(0, &pQyMc->cusRes, hDlg, IDD_objs);

	m_var.guiData.bInited = TRUE;


	// TODO:  Add extra initialization here
	DLG_guiData_objs* pGuiData; pGuiData = &m_var.guiData;
	if (!dlgObjs_bFillContent(hDlg, &m_var, pGuiData->param.uiType, this))  goto  errLabel;

	//QListWidgetItem* item = new QListWidgetItem("项目2");
	//ui->IDC_LIST0->addItem(item);


	iErr = 0;

errLabel:

	if (!m_var.guiData.bInited || iErr) {
		//  EndDialog(  -1  );
		//PostMessage(WM_CLOSE);
		//
		return false;
	}

	return true;
}

HWND CDlgRemoteVideoMix::GetVideoWindow()
{
	return (HWND)ui->widget_remoteVideo->winId();
}

QRect CDlgRemoteVideoMix::GetVideoGeometry()
{
	return ui->widget_remoteVideo->geometry();
}

void CDlgRemoteVideoMix::handleButtonClick(int buttonId)
{
	dlgObjs_OnOK((HWND)this->winId(), &m_var, buttonId);
	doButtonClick(buttonId);
}



void CDlgRemoteVideoMix::doButtonClick(int buttonId)
{
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
	DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar_cur.getVar(m_hCurTalk);
	if (!pCurVar)  goto  errLabel;

	DLG_guiDataParam_objs		param;
	DYN_BMP_RULE				dynBmpRule_selected;

	//
	memset(&dynBmpRule_selected, 0, sizeof(dynBmpRule_selected));

	//
	memset(&param, 0, sizeof(param));
	param.uiType = CONST_objType_selectRemoteVideo;
	param.hCurTalk = m_hCurTalk;
	param.pCurVar = pCurVar;							//  2013/06/10
	param.pMgrVar = m_pMgrVar;
	param.pObjBuf_selected = &dynBmpRule_selected.dynBmp;			//  2014/05/15
	param.uiSize_pObjBuf_selected = sizeof(dynBmpRule_selected);

	//  2015/06/05
	HWND  hParent; hParent = m_hCurTalk;
	//  2016/05/24
	/*if (IsWindow(pWmBuf->hParent_expected)) {
		hParent = pWmBuf->hParent_expected;
	}*/

	if (m_hShow) {
		hParent = m_hShow;
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

	/*if (showDlgObjs(pQyMc->g_hInst, hParent, &param)) {
		goto  errLabel;
	}*/
	//DLG_guiDataParam_objs&	param = (DLG_guiDataParam_objs&)m_var.guiData.param;

	
	//dynBmp = param.pObjBuf_selected;

	DLG_guiData_objs* p; p = (DLG_guiData_objs*)&m_var.guiData;

	if (p) {

		memcpy(&param.o, &p->param.o, sizeof(param.o));
		//
		memcpy(param.pObjBuf_selected, p->param.pObjBuf_selected, param.uiSize_pObjBuf_selected);
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


	bView = tmpF_bViewRemoteVideo(&m_pShadowMgr->vwRuleCmd_manual, dynBmpRule_selected.dynBmp.resObj.uiObjType,
		dynBmpRule_selected.dynBmp.resObj.usIndex_obj, dynBmpRule_selected.dynBmp.resObj.usHelp_subIndex);
	tmpF_setViewRemoteVideo(&dynBmpRule_selected, !bView, &m_pShadowMgr->vwRuleCmd_manual);


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


	QY_COLUMNINFO* pColumns; pColumns = (QY_COLUMNINFO*)m_var.pData_items;

	


	//
	chkTalkerRules(m_hMgr, m_pMgrVar);

	//
	unsigned  int		uiObjType; uiObjType = 0;
	unsigned  short	usIndex_dynBmp; usIndex_dynBmp = 0;
	int				talkerRuleIndex; talkerRuleIndex = 0;
	int  i;


	for (i = 0; i < mycountof(m_pShadowMgr->vwRuleCmd.dynBmpRules); i++) {
		if (m_pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.uiObjType == dynBmpRule_selected.dynBmp.resObj.uiObjType
			&& m_pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.usIndex_obj == dynBmpRule_selected.dynBmp.resObj.usIndex_obj
			&& m_pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.usHelp_subIndex == dynBmpRule_selected.dynBmp.resObj.usHelp_subIndex
			)
		{
			break;
		}
	}



	if (i == mycountof(m_pShadowMgr->talkerDynBmps)) {
		if (bView) {

			pColumns[buttonId].lParam = 0;
			//QString butLabel = QString::fromWCharArray(getResStr(0, &pQyMc->cusRes, CONST_resId_start)) + "_" + QString::fromWCharArray(pColumns[buttonId].label);
			QString butLabel = QString::fromWCharArray(getResStr(0, &pQyMc->cusRes, CONST_resId_start)) + ChangeName(QString::fromWCharArray(pColumns[buttonId].label));

			this->SetButtonText(buttonId, butLabel);
		}
		goto  errLabel;
	}
	talkerRuleIndex = i;


	BOOL			bNeedProgress; bNeedProgress = TRUE;
	BOOL			bImgRestarted; bImgRestarted = FALSE;

	//				  	
	uiObjType = dynBmpRule_selected.dynBmp.resObj.uiObjType;
	usIndex_dynBmp = dynBmpRule_selected.dynBmp.resObj.usIndex_obj;
	unsigned  short  usHelp_subIndex; usHelp_subIndex = dynBmpRule_selected.dynBmp.resObj.usHelp_subIndex;
	if (tmpF_bViewRemoteVideo(&m_pShadowMgr->vwRuleCmd_manual, uiObjType, usIndex_dynBmp, usHelp_subIndex)) {
		if (tmpF_bViewRemoteVideo(&m_pShadowMgr->vwRuleCmd, uiObjType, usIndex_dynBmp, usHelp_subIndex)) {
			//
			chkToViewDynBmp(m_hMgr, m_pMgrVar, talkerRuleIndex, bNeedProgress, &bImgRestarted);
		}
	}


	if (bImgRestarted) {

		TALKER_dynBmp* pRule = NULL;
		unsigned  int		uiTranNo = 0;

		pRule = &m_pShadowMgr->talkerDynBmps[talkerRuleIndex];
		uiTranNo = pRule->taskInfo.uiTranNo;

		//
		if (showProgress(&pQyMc->gui.progress, &pQyMc->cusRes, /*(HWND)this->winId()*/m_hCurTalk, _T("Please waiting"),
			NULL, 30, -1, uiTranNo) != IDOK) 
		{
			goto  errLabel;
		}

		if (!bView) {

			pColumns[buttonId].lParam = 1;
			//QString butLabel = QString::fromWCharArray(getResStr(0, &pQyMc->cusRes, CONST_resId_stop)) + "_" + QString::fromWCharArray(pColumns[buttonId].label);
			QString butLabel = QString::fromWCharArray(getResStr(0, &pQyMc->cusRes, CONST_resId_stop)) + ChangeName(QString::fromWCharArray(pColumns[buttonId].label));
			this->SetButtonText(buttonId, butLabel);
		}
		

		//
#ifdef  __DEBUG__
		int  ii;
		ii = 9;
#endif
	}

	//
	closeMoreIa(m_hCurTalk);


errLabel:
	return;
}

void CDlgRemoteVideoMix::InsertButton(int buttonId, QPushButton* btn)
{
	if (m_mapButton.contains(buttonId)) {
		QPushButton* btnOld = m_mapButton[buttonId];
		delete btnOld;
	}

	m_mapButton[buttonId] = btn;
}

void CDlgRemoteVideoMix::DeleteButton(int buttonId)
{
	if (!m_mapButton.contains(buttonId))
		return;

	QPushButton* btnOld = m_mapButton[buttonId];
	delete btnOld;

	m_mapButton.remove(buttonId);
}

void CDlgRemoteVideoMix::DeleteAllButton()
{
	for (auto it = m_mapButton.begin(); it != m_mapButton.end(); ++it) {
		//qDebug() << "Key:" << it.key() << "Value:" << it.value();

		QPushButton* btn = it.value();
		delete btn;
	}

}

void CDlgRemoteVideoMix::SetButtonText(int buttonId, const QString& text)
{
	if (!m_mapButton.contains(buttonId))
		return;
	QPushButton* btn = m_mapButton[buttonId];

	btn->setText(text);
}

void traverseProxy(const QSortFilterProxyModel& proxyModel, const QModelIndex& parent) {
	int rowCount = proxyModel.rowCount(parent);
	QFileSystemModel* sourceModel = qobject_cast<QFileSystemModel*>(proxyModel.sourceModel());
	for (int row = 0; row < rowCount; ++row) {
		QModelIndex proxyIndex = proxyModel.index(row, 0, parent);
		QModelIndex sourceIndex = proxyModel.mapToSource(proxyIndex);

		// 通过源模型获取文件信息
		QString filePath = sourceModel->filePath(sourceIndex);
		QString fileName = sourceModel->fileName(sourceIndex);
		bool isDir = sourceModel->isDir(sourceIndex);

		//qDebug() << (isDir ? "Directory:" : "File:") << fileName << "at" << filePath;

		// 如果是目录，递归遍历
		if (isDir) {
			traverseProxy(proxyModel, proxyIndex);
		}
	}
}

void traverseModel(const QAbstractItemModel* model, const QModelIndex& parent = QModelIndex()) {
	for (int row = 0; row < model->rowCount(parent); ++row) {
		QModelIndex index = model->index(row, 0, parent);
		if (model->hasChildren(index)) {
			traverseModel(model, index);
		}
		QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
		//qDebug() << "File path:" << filePath;
	}
}


void CDlgRemoteVideoMix::ReadData() {

	QFileSystemModel* fileSystemModel = qobject_cast<QFileSystemModel*>(m_proxyModel->sourceModel());
	if (!fileSystemModel) return;

	QAbstractItemModel* model = ui->listView_file->model();
	if (!model) return;

	// 检查是否是 FileSystemSortProxyModel 或类似的代理模型
	QStandardItemModel* viewModel = qobject_cast<QStandardItemModel*>(model);
	if (!viewModel) return;

	QString filePath;

	for (int row = 0; row < 100 && row < m_proxyModel->rowCount(); ++row) {
		QModelIndex proxyIndex = m_proxyModel->index(row, 0, QModelIndex());

		if (proxyIndex.isValid()) {
			// 获取第一个文件的完整路径
			filePath = fileSystemModel->filePath(m_proxyModel->mapToSource(proxyIndex));
			//qDebug() << "第一个文件的完整路径是:" << filePath;
		}

		// 获取文件名
		QString fileName = m_proxyModel->data(proxyIndex, QFileSystemModel::FileNameRole).toString();

		// 获取文件路径（需要通过源模型获取）
		QModelIndex sourceIndex = m_proxyModel->mapToSource(proxyIndex);
		QString filePath = fileSystemModel->filePath(sourceIndex);

		// 获取其他信息...
		qint64 size = fileSystemModel->size(sourceIndex);
		QString type = fileSystemModel->type(sourceIndex);

		//qDebug() << "Row:" << row << "Name:" << fileName << "Path:" << filePath
		//	<< "Size:" << size << "Type:" << type;

		viewModel->appendRow(new QStandardItem(fileName));
	}
}

void CDlgRemoteVideoMix::traverseDirectory(const QModelIndex& parentIndex)
{
	// Get row count for the current directory
	int rowCount = m_proxyModel->rowCount(parentIndex);

	rowCount = rowCount < 100 ? rowCount : 100;

	QAbstractItemModel* model = ui->listView_file->model();
	if (!model) return;
	QStandardItemModel* viewModel = qobject_cast<QStandardItemModel*>(model);
	if (!viewModel) return;

	viewModel->clear();

	for (int row = 0; row < rowCount; ++row) {
		// Get the child index
		QModelIndex childIndex = m_proxyModel->index(row, 0, parentIndex);

		// Map back to source model to get file info
		QModelIndex sourceIndex = m_proxyModel->mapToSource(childIndex);

		// Get file info from source model
		QFileInfo fileInfo = m_fileSystemModel->fileInfo(sourceIndex);

		if (fileInfo.isDir() && !fileInfo.isSymLink()) {
			// If it's a directory, traverse it recursively
			//qDebug() << "Entering directory:" << fileInfo.filePath();
			//traverseDirectory(childIndex);
		}
		else {
			QString fileName = fileInfo.fileName();
			QString filePath = fileInfo.filePath();
			// Process the file
			/*qDebug() << "File:" << fileInfo.filePath()
				<< "Size:" << fileInfo.size()
				<< "Modified:" << fileInfo.lastModified();*/

			viewModel->appendRow(new QStandardItem(fileName));

		}
	}
}




void CDlgRemoteVideoMix::onDirectoryLoaded(const QString& path)
{
	//qDebug() << "Directory loaded:" << path;

	// Get the index for the loaded directory
	QModelIndex sourceIndex = m_fileSystemModel->index(path);
	if (!sourceIndex.isValid()) return;

	// Map to the proxy model's index
	QModelIndex proxyIndex = m_proxyModel->mapFromSource(sourceIndex);

	// Traverse all files recursively
	traverseDirectory(proxyIndex);
}

void CDlgRemoteVideoMix::onSaveClick() {
	m_isSaveICFile = !m_isSaveICFile;
	SetIsSaveButtonText(m_isSaveICFile);

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	
	QY_REG reg;
	TCHAR* pRegVal = NULL;

	memset(&reg, 0, sizeof(reg));
	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	lstrcpyn(reg.rootKey, CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), mycountof(reg.rootKey));

	pProcInfo->cfg.policy.isSaveICFile = m_isSaveICFile;
	qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_isSaveICFile), pProcInfo->cfg.policy.isSaveICFile ? _T("1") : _T(""));

}

void CDlgRemoteVideoMix::SetIsSaveButtonText(bool isSave) {
	if (!m_isSaveICFile)
		ui->pushButton_save->setText(u8"开启存储");
	else
		ui->pushButton_save->setText(u8"关闭存储");
}

void CDlgRemoteVideoMix::onSoundClick() {
	m_isPlaySound = !m_isPlaySound;
	SetSoundButtonText(m_isSaveICFile);

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	if (m_isPlaySound)
		pProcInfo->cfg.ucbPlayRemoteAudio_viewDynBmp = TRUE;
	else 
		pProcInfo->cfg.ucbPlayRemoteAudio_viewDynBmp = FALSE;
}

void CDlgRemoteVideoMix::SetSoundButtonText(bool isSave) {
	if (!m_isPlaySound)
		ui->pushButton_sound->setText(u8"打开声音");
	else
		ui->pushButton_sound->setText(u8"关闭声音");
}

void CDlgRemoteVideoMix::InitControl()
{
	

	ui->widget_remoteVideo->setStyleSheet("background-color: black;");

	ui->widget_remoteVideo->installEventFilter(this);

	QFile file(":/Resources/QSS/CDlgRemoteVideoMix.css");
	file.open(QFile::ReadOnly);
	if (file.isOpen())
	{
		this->setStyleSheet("");
		QString qsstyleSheet = QLatin1String(file.readAll());
		this->setStyleSheet(qsstyleSheet);
	}
	file.close();


	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();	

	QString title = QString::fromWCharArray(getResStr(0, &pQyMc->cusRes, CONST_resId_remoteVideo));

	this->setWindowTitle(u8"远程视频");

	m_path = QString::fromWCharArray(pProcInfo->cfg.policy.dirToSaveICFile);

	m_fileSystemModel = new QFileSystemModel();

	m_isSaveICFile = pProcInfo->cfg.policy.isSaveICFile;

	SetIsSaveButtonText(m_isSaveICFile);
	SetSoundButtonText(m_isPlaySound);


	connect(ui->pushButton_save, &QPushButton::clicked, this, &CDlgRemoteVideoMix::onSaveClick);
	connect(ui->pushButton_sound, &QPushButton::clicked, this, &CDlgRemoteVideoMix::onSoundClick);

	//model->setReadOnly(true);
	//model->setResolveSymlinks(false);

	/*
	if(!m_path.isEmpty())
		m_fileSystemModel->setRootPath(m_path);

	m_proxyModel = new FileSystemSortProxyModel;
	m_proxyModel->setSourceModel(m_fileSystemModel);
	//proxyModel->setSortRole(QFileSystemModel::fileInfo);
	m_proxyModel->sort(0, Qt::DescendingOrder);
	*/

	/*connect(m_fileSystemModel, &QFileSystemModel::directoryLoaded,
		this, &CDlgRemoteVideoMix::onDirectoryLoaded);*/

	//m_proxyModel->mapFromSource(model->index(m_path))

    //QListView listView;
    //ui->listView_file->setModel(model);

	//ui->listView_file->setModel(proxyModel);
	//if (!m_path.isEmpty())
	//	ui->listView_file->setRootIndex(proxyModel->mapFromSource(model->index(m_path)));

	//if (!path.isEmpty())
	//	ui->listView_file->setRootIndex(model->index(path));

	QStandardItemModel* viewModel = new QStandardItemModel(this);
	ui->listView_file->setModel(viewModel);

	//ReadData();

	//QModelIndex rootIndex = m_fileSystemModel->index(m_path);
	//QModelIndex proxyRootIndex = m_proxyModel->mapFromSource(rootIndex);

	//traverseProxy(*m_proxyModel, proxyRootIndex);

	//traverseModel(m_proxyModel, proxyRootIndex);

    ui->listView_file->setWindowTitle("文件列表");
    //ui->listView_file->resize(600, 400);

	connect(ui->listView_file, &QListView::doubleClicked, this, &CDlgRemoteVideoMix::onItemDoubleClicked);

    ui->listView_file->show();

	InitListViewFile();


	ui->listView_file->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //QFileSystemModel* model = new QFileSystemModel();
    ////model.setRootPath(QDir::currentPath());
    //model->setRootPath("d:/output");

    //
    //ui->tableView_file->setModel(model);
    ////ui->tableView_file->setRootIndex(model.index(QDir::currentPath()));
    //ui->tableView_file->setRootIndex(model->index("d:/output"));
    //ui->tableView_file->setWindowTitle("文件详细信息");
    ////ui->tableView_file->resize(800, 600);

    //// 设置列宽
    //ui->tableView_file->setColumnWidth(0, 200);  // 文件名
    //ui->tableView_file->setColumnWidth(1, 100);  // 大小
    //ui->tableView_file->setColumnWidth(2, 100);  // 类型
    //ui->tableView_file->setColumnWidth(3, 150);  // 修改日期

    //ui->tableView_file->show();


    //QFileSystemModel* model = new QFileSystemModel;
    //model->setRootPath(QDir::homePath()); // 设置根目录为当前用户的家目录
    //model->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries); // 过滤掉 . 和 .. 目录，并显示所有类型的文件和目录

    ////QTableView* tableView = new QTableView;
    //ui->tableView_file->setModel(model); // 设置模型为表格视图的数据源
    //ui->tableView_file->setColumnWidth(0, 200); // 设置第一列的宽度为200像素（可选）
    //ui->tableView_file->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents); // 根据内容调整第一列宽度（可选）
    //ui->tableView_file->horizontalHeader()->setStretchLastSection(true); // 拉伸最后一列以填满空间（可选）
    //ui->tableView_file->show(); // 显示表格视图

	/*
    QGraphicsScene* scene = new QGraphicsScene;

    QPixmap pixmap("d:\\output\\test.bmp"); 

    if (pixmap.isNull()) {
        scene->addText("Failed to load image!");
    }
    else {
        QGraphicsPixmapItem* item = scene->addPixmap(pixmap);

        scene->setSceneRect(pixmap.rect());
    }

	// 去掉滚动条
	ui->graphicsView_img->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView_img->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView_img->setScene(scene);
    ui->graphicsView_img->show();

	scene->setSceneRect(pixmap.rect());

	ui->graphicsView_img->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
	*/

	//QPixmap pixmap("d:\\output\\test.bmp"); // 支持常见格式如JPG, PNG, BMP等

	// 设置图片到QLabel
	//ui->label_img->setPixmap(pixmap);

	// 可选：保持图片比例缩放
	ui->label_img->setScaledContents(true);
	ui->label_img->setStyleSheet("QLabel { border: 1px solid black; }");

	QRect rect = this->geometry();

	layoutControl(QSize(rect.width(), rect.height()));

	m_ZoomLabelImg = new ZoomLabel("", this);
	m_ZoomLabelImg->setStyleSheet("QLabel { border: 1px solid black; }");
	m_ZoomLabelImg->show();

	emit to_remotevideo_resize();
}

void CDlgRemoteVideoMix::InitControl_bak()
{

	ui->widget_remoteVideo->setStyleSheet("background-color: black;");

	ui->widget_remoteVideo->installEventFilter(this);


	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	m_path = QString::fromWCharArray(pProcInfo->cfg.policy.dirToSaveICFile);

	QFileSystemModel* model = new QFileSystemModel();

	model->setReadOnly(true);
	model->setResolveSymlinks(false);

	if (!m_path.isEmpty())
		model->setRootPath(m_path);

	FileSystemSortProxyModel* proxyModel = new FileSystemSortProxyModel;
	proxyModel->setSourceModel(model);
	//proxyModel->setSortRole(QFileSystemModel::fileInfo);
	proxyModel->sort(0, Qt::DescendingOrder);

	//QListView listView;
	//ui->listView_file->setModel(model);

	ui->listView_file->setModel(proxyModel);
	if (!m_path.isEmpty())
		ui->listView_file->setRootIndex(proxyModel->mapFromSource(model->index(m_path)));

	//if (!path.isEmpty())
	//	ui->listView_file->setRootIndex(model->index(path));

	ui->listView_file->setWindowTitle("文件列表");
	//ui->listView_file->resize(600, 400);

	connect(ui->listView_file, &QListView::doubleClicked, this, &CDlgRemoteVideoMix::onItemDoubleClicked);

	ui->listView_file->show();





	//QFileSystemModel* model = new QFileSystemModel();
	////model.setRootPath(QDir::currentPath());
	//model->setRootPath("d:/output");

	//
	//ui->tableView_file->setModel(model);
	////ui->tableView_file->setRootIndex(model.index(QDir::currentPath()));
	//ui->tableView_file->setRootIndex(model->index("d:/output"));
	//ui->tableView_file->setWindowTitle("文件详细信息");
	////ui->tableView_file->resize(800, 600);

	//// 设置列宽
	//ui->tableView_file->setColumnWidth(0, 200);  // 文件名
	//ui->tableView_file->setColumnWidth(1, 100);  // 大小
	//ui->tableView_file->setColumnWidth(2, 100);  // 类型
	//ui->tableView_file->setColumnWidth(3, 150);  // 修改日期

	//ui->tableView_file->show();


	//QFileSystemModel* model = new QFileSystemModel;
	//model->setRootPath(QDir::homePath()); // 设置根目录为当前用户的家目录
	//model->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries); // 过滤掉 . 和 .. 目录，并显示所有类型的文件和目录

	////QTableView* tableView = new QTableView;
	//ui->tableView_file->setModel(model); // 设置模型为表格视图的数据源
	//ui->tableView_file->setColumnWidth(0, 200); // 设置第一列的宽度为200像素（可选）
	//ui->tableView_file->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents); // 根据内容调整第一列宽度（可选）
	//ui->tableView_file->horizontalHeader()->setStretchLastSection(true); // 拉伸最后一列以填满空间（可选）
	//ui->tableView_file->show(); // 显示表格视图

	/*
	QGraphicsScene* scene = new QGraphicsScene;

	QPixmap pixmap("d:\\output\\test.bmp");

	if (pixmap.isNull()) {
		scene->addText("Failed to load image!");
	}
	else {
		QGraphicsPixmapItem* item = scene->addPixmap(pixmap);

		scene->setSceneRect(pixmap.rect());
	}

	// 去掉滚动条
	ui->graphicsView_img->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView_img->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	ui->graphicsView_img->setScene(scene);
	ui->graphicsView_img->show();

	scene->setSceneRect(pixmap.rect());

	ui->graphicsView_img->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
	*/

	//QPixmap pixmap("d:\\output\\test.bmp"); // 支持常见格式如JPG, PNG, BMP等

	// 设置图片到QLabel
	//ui->label_img->setPixmap(pixmap);

	// 可选：保持图片比例缩放
	ui->label_img->setScaledContents(true);
	ui->label_img->setStyleSheet("QLabel { border: 1px solid black; }");

	QRect rect = this->geometry();

	layoutControl(QSize(rect.width(), rect.height()));;

	emit to_remotevideo_resize();
}
void CDlgRemoteVideoMix::onItemDoubleClicked(const QModelIndex& index) {
	if (index.isValid()) {
		//qDebug() << "Double clicked on row:" << index.row();
		// 获取对应的 QStandardItem
		QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->listView_file->model());
		if (model) {
			QStandardItem* item = model->itemFromIndex(index);
			//qDebug() << "Item text:" << item->text();

			QString fileName = item->text();

			if (fileName.isEmpty()) return;		

			std::string filePath = joinPath(m_path.toStdString(), fileName.toStdString());


			QFileInfo fileInfo(filePath.c_str());
			if (!fileInfo.exists()) {
				//qDebug() << "File does not exist:" << filePath;
				return;
			}

			// 首先尝试使用 QDesktopServices
			QUrl url = QUrl::fromLocalFile(filePath.c_str());
			if (QDesktopServices::openUrl(url)) {

				return;
			}

			QProcess::startDetached("cmd.exe", QStringList() << "/c" << "start" << QDir::toNativeSeparators(filePath.c_str()));
			

		}
	}
}


void CDlgRemoteVideoMix::onItemDoubleClicked_bak(const QModelIndex& index) {
	// 获取双击的项目数据
	//QString itemText = index.data(Qt::DisplayRole).toString();
	//QMessageBox::information(this, "Item Double Clicked",
	//	QString("You double clicked: %1").arg(itemText));

	QAbstractItemModel* model = ui->listView_file->model();
	if (!model) return;

	QSortFilterProxyModel* proxyModel = qobject_cast<QSortFilterProxyModel*>(model);
	if (!proxyModel) return;


	QFileSystemModel* fileSystemModel = qobject_cast<QFileSystemModel*>(proxyModel->sourceModel());
	if (!fileSystemModel) return;
	

	QString filePath;

	if (index.isValid()) {
		filePath = fileSystemModel->filePath(proxyModel->mapToSource(index));
	}

	if (filePath.isEmpty()) return;

	QFileInfo fileInfo(filePath);
	if (!fileInfo.exists()) {
		//qDebug() << "File does not exist:" << filePath;
		return;
	}

	// 首先尝试使用 QDesktopServices
	QUrl url = QUrl::fromLocalFile(filePath);
	if (QDesktopServices::openUrl(url)) {

		return;
	}

	QProcess::startDetached("cmd.exe", QStringList() << "/c" << "start" << QDir::toNativeSeparators(filePath));
}

int CDlgRemoteVideoMix::dlgObjs_OnOK(HWND  hDlg, void* pVarParam, int iItemSelected)
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

	

	char						buf[32];
	QY_MESSENGER_ID				idInfo_selected;
	TCHAR* pT1;
	QString butLabel;

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

			
		/*if (pColumns[iItemSelected].lParam)  
			_sntprintf(pColumns[iItemSelected].label, mycountof(pColumns[iItemSelected].label), _T("%s ( %s )"), 
				pColumns[iItemSelected].label, getResStr(0, &pQyMc->cusRes, CONST_resId_manuallyStarted));
		butLabel = QString::fromWCharArray(pColumns[iItemSelected].label);
		this->SetButtonText(iItemSelected, butLabel);*/

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

void CDlgRemoteVideoMix::layoutControl(const QSize& size) {

	QRect rectVideo;
	rectVideo.setX(0);
	rectVideo.setY(0);
	rectVideo.setWidth(size.width() - BUTTON_AREA_WIDTH);
	rectVideo.setHeight(size.height() / 2);
	ui->widget_remoteVideo->setGeometry(rectVideo);


	QRect rectFile;
	rectFile.setX(0);
	rectFile.setY(size.height() / 2);
	rectFile.setWidth((size.width() - BUTTON_AREA_WIDTH) / 2);
	rectFile.setHeight(size.height() / 2);
	ui->listView_file->setGeometry(rectFile);

	QRect rectImg;
	rectImg.setX((size.width() - BUTTON_AREA_WIDTH) / 2 - 1);
	rectImg.setY(size.height() / 2);
	rectImg.setWidth((size.width() - BUTTON_AREA_WIDTH) / 2 + 1);
	rectImg.setHeight(size.height() / 2);
	//ui->graphicsView_img->setGeometry(rectImg);
	ui->label_img->setGeometry(rectImg);

	int n = 0;

	for (auto it = m_mapButton.begin(); it != m_mapButton.end(); ++it) {
		//qDebug() << "Key:" << it.key() << "Value:" << it.value();		

		QRect butRect;
		butRect.setX(size.width() - BUTTON_LEFT);
		butRect.setY(BUTTON_INTERVAL * (n + 1));
		butRect.setWidth(BUTTON_WIDTH);
		butRect.setHeight(40);

		QPushButton* btn = it.value();
		btn->setGeometry(butRect);
		
		n++;
	}

	QRect butRect;
	butRect.setX(size.width() - BUTTON_LEFT);
	butRect.setY(BUTTON_INTERVAL * (++ n));
	butRect.setWidth(BUTTON_WIDTH);
	butRect.setHeight(40);

	ui->pushButton_save->setGeometry(butRect);

	butRect;
	butRect.setX(size.width() - BUTTON_LEFT);
	butRect.setY(BUTTON_INTERVAL * (++n));
	butRect.setWidth(BUTTON_WIDTH);
	butRect.setHeight(40);

	ui->pushButton_sound->setGeometry(butRect);
	

	if (this->m_ZoomLabelImg) {
		ui->label_img->setVisible(false);
		QRect rect = ui->label_img->geometry();
		this->m_ZoomLabelImg->setGeometry(rect);
	}

	;
}


void CDlgRemoteVideoMix::resizeEvent(QResizeEvent* event) 
{
	QWidget::resizeEvent(event);

	QSize size = event->size();

	layoutControl(size);

	emit to_remotevideo_resize();
}

void CDlgRemoteVideoMix::closeEvent(QCloseEvent* event) 
{
	event->ignore();
	emit to_remotevideo_close();
	return;

	QMessageBox msgBox(this);
	msgBox.setWindowTitle(u8"确认关闭");
	msgBox.setText(u8"您确定要关闭窗口吗?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);


	int ret = msgBox.exec();

	if (ret == QMessageBox::Yes) {
		//event->accept();  
		event->ignore();
		emit to_remotevideo_close();
	}
	else {
		event->ignore();  
	}
}

void CDlgRemoteVideoMix::SetControlVisable(bool visible) {

	if (visible) {
		ui->listView_file->setVisible(true);
		//ui->label_img->setVisible(true);
		m_ZoomLabelImg->setVisible(true);

		ui->pushButton_save->setVisible(true);
		ui->pushButton_sound->setVisible(true);

		for (auto it = m_mapButton.begin(); it != m_mapButton.end(); ++it) {
			if (it.key() == 0)
				continue;
			QPushButton* btn = it.value();
			btn->setVisible(true);
		}
	}
	else {
		ui->listView_file->setVisible(false);
		//ui->label_img->setVisible(false);
		m_ZoomLabelImg->setVisible(false);
		ui->pushButton_save->setVisible(false);
		ui->pushButton_sound->setVisible(false);

		for (auto it = m_mapButton.begin(); it != m_mapButton.end(); ++it) {
			if (it.key() == 0)
				continue;

			QPushButton* btn = it.value();
			btn->setVisible(false);
		}
	}
}

bool CDlgRemoteVideoMix::eventFilter(QObject* obj, QEvent* event) 
{
	if (obj == ui->widget_remoteVideo && event->type() == QEvent::MouseButtonDblClick) {
		QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
		if (mouseEvent->button() == Qt::LeftButton) {
			if (!m_isFullscreen) {
				m_normalGeometry = ui->widget_remoteVideo->geometry();
				showFullScreen();
				ui->widget_remoteVideo->setGeometry(geometry());

				SetControlVisable(false);
				emit to_remotevideo_resize();
			}
			else {
				showNormal();
				ui->widget_remoteVideo->setGeometry(m_normalGeometry);
				SetControlVisable(true);
				QRect rect = this->geometry();
				layoutControl(QSize(rect.width(), rect.height()));
				emit to_remotevideo_resize();
			}
			m_isFullscreen = !m_isFullscreen;
			return true;
		}
	}
	return QWidget::eventFilter(obj, event);
}