#include "CDlgSelectVideo.h"

//#include <QDesktopWidget>
#include	<qscreen.h>
//
#include	<tchar.h>
#include	"qyMcMainCommon_qt.h"
#include <ctxQmc.h>
#include	<ctxQmc_sm.h>

#include <regex>
#include <string>
#include <dshow.h>
#include <QMutex>


//bool validateRtspUrl(const std::string& url) {
//	std::regex rtspRegex(R"(^rtsp://([^:]+):([^@]+)@([^/]+)(/.*)?$)");
//	return std::regex_match(url, rtspRegex);
//}

QMutex selectVideoObjNameLock;
std::list<std::string> selectVideoObjName;


bool compareSpecalObjName(const QString& objName) {

	selectVideoObjNameLock.lock();
	for (auto& value : selectVideoObjName) {
		if (value == objName.toStdString()) {
			selectVideoObjNameLock.unlock();
			return true;
		}
	}
	selectVideoObjNameLock.unlock();
	return false;
}

void clearSpecalObjName() {
	selectVideoObjNameLock.lock();
	selectVideoObjName.clear();
	selectVideoObjNameLock.unlock();
}

bool validateRtspUrlnn(const std::string& url, bool& hasCredentials) {
	
	std::regex rtspRegex(R"(^rtsp://(?:([^:@/]+):([^@/]+)@)?([^:/]+)(?::(\d+))?(/.*)$)");
	std::smatch match;

	
	if (std::regex_search(url, match, rtspRegex)) {
		
		hasCredentials = match[1].length() > 0 && match[2].length() > 0;
		return true;
	}
	return false;
}


CDlgSelectVideo::CDlgSelectVideo(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::CDlgSelectVideoClass())
{
	ui->setupUi(this);

	clearSpecalObjName();

	int size = sizeof(videoMoniker) / sizeof(IMoniker);

	for (int i = 0; i < size; ++i) {
		videoMoniker[i] = nullptr;
	}


	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

	//connect(ui->boxEnableShare, SIGNAL(stateChanged(int)), this, SLOT(slot_boxEnableShare_change(int)));
	//connect(ui->boxRtsp, SIGNAL(stateChanged(int)), this, SLOT(slot_boxRtsp_change(int)));
	connect(this, SIGNAL(to_returnMain_selectVideo_signal()), parent, SLOT(on_closeSelectVideo_slots()));	
	connect(ui->boxRtsp, &QCheckBox::clicked, this, &CDlgSelectVideo::slot_mouse_boxRtsp_click);
	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(slot_btnOk_click()));
	connect(ui->btnCancle, SIGNAL(clicked()), this, SLOT(slot_btnCancle_click()));

	sheetBackgroundImage();

	Init();

	EnumerateVideoDevicesSave();

	//初始化复选框状态
	initBoxStatus();

	//InitVideoDev();

	

	//错误提示
	ui->err_widget->setVisible(false);
}


void CDlgSelectVideo::InitVideoDev() {

	//ui->widget_video_dev_list->setFixedWidth(300);
	//ui->widget_video_dev_list->resize(350, 60);

	//QHBoxLayout* layout = new QHBoxLayout(ui->widget_video_dev_list);

	QHBoxLayout* layout = ui->widget_video_dev_list->findChild<QHBoxLayout*>();
	if (!layout) {
		layout = new QHBoxLayout(ui->widget_video_dev_list);
	}

	QCheckBox* checkBox = new QCheckBox("video0", ui->widget_video_dev_list);
	checkBox->setObjectName("video0");
	QCheckBox* checkBox1 = new QCheckBox("video1", ui->widget_video_dev_list);
	checkBox1->setObjectName("video1");

	m_videoDevList.push_back(checkBox);
	m_videoDevList.push_back(checkBox1);

	//checkBox->setUserData()

	//layout->setSpacing(20);  
	//layout->setContentsMargins(20, 20, 20, 20);  


	layout->addWidget(checkBox);
	layout->addWidget(checkBox1);

	QRect rc = QApplication::primaryScreen()->geometry();

	if (rc.width() > 3500) {

		//checkBox->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		//checkBox1->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");

		checkBox->setStyleSheet("QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
		checkBox1->setStyleSheet("QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
	}
	else {
		//checkBox->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		//checkBox1->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");

		checkBox->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
		checkBox1->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
	}

	

	ui->widget_video_dev_list->show();

	
}


void CDlgSelectVideo::Init() {

	TCHAR	tBuf[255 + 1] = _T("");
	QY_REG	reg;


	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	lstrcpyn(reg.rootKey, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, mycountof(reg.rootKey));

	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, (TCHAR*)_T(CONST_regValName_camCapType), (char*)tBuf, sizeof(tBuf), 0)) {
		iCamCapType = _ttol(tBuf);
	}

	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_webcam_selected), (char*)tBuf, sizeof(tBuf), NULL)) {
		webcam_selected = tBuf;

	}

	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_rtspUrl_selected), (char*)tBuf, sizeof(tBuf), 0)) {
		RtspUrl_selected = tBuf;
	}

	if (iCamCapType == CONST_camCapType_rtsp) {
		ui->rtspUrl->setEnabled(TRUE);
	}
	else {
		ui->rtspUrl->setEnabled(FALSE);
	}

}

QString variantToQString(const VARIANT& var)
{
	if (var.vt == VT_BSTR && var.bstrVal != nullptr) {
		return QString::fromWCharArray(var.bstrVal);
	}
	return QString();
}

void CDlgSelectVideo::onCheckBoxClicked(bool checked)
{
	QCheckBox* clickedCheckBox = qobject_cast<QCheckBox*>(sender());

	//
	QRect rc = QApplication::primaryScreen()->geometry();
	//
	for (int i = 0; i < m_videoDevList.size(); ++i) {

		if (m_videoDevList[i] != clickedCheckBox) {

			m_videoDevList[i]->setCheckState(Qt::Unchecked);
			if (rc.width() > 3500) {
				m_videoDevList[i]->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			}
			else {
				m_videoDevList[i]->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			}
		}
		else {
			m_videoDevList[i]->setCheckState(Qt::Checked);
			if (rc.width() > 3500) {
				m_videoDevList[i]->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			}
			else {
				m_videoDevList[i]->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			}

			if (videoMoniker[i]) {
				WCHAR* wszDisplayName = NULL;

				wszDisplayName = 0;

				if (SUCCEEDED(videoMoniker[i]->GetDisplayName(0, 0, &wszDisplayName)) && wszDisplayName) {

					webcam_selected = wszDisplayName;
				}
			}


			
		}
	}

	iCamCapType = CONST_camCapType_directX;

	ui->boxRtsp->setCheckState(Qt::Unchecked);
	ui->rtspUrl->setEnabled(FALSE);
	

	if (rc.width() > 3500) {
		ui->boxRtsp->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
	}
	else {
		ui->boxRtsp->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
	}



}

void CDlgSelectVideo::EnumerateVideoDevicesSave()
{
	

	QLayout* oldLayout = ui->widget_video_dev_list->layout();
	if (oldLayout) {
		QLayoutItem* item;
		while ((item = oldLayout->takeAt(0)) != nullptr) {
			if (item->widget()) {
				item->widget()->setParent(nullptr); 
			}
			delete item;
		}
		delete oldLayout;
	}


	int height = 60;
	

	QVBoxLayout* layout = ui->widget_video_dev_list->findChild<QVBoxLayout*>();
	if (!layout) {
		layout = new QVBoxLayout(ui->widget_video_dev_list);
	}

	//
	QRect rc = QApplication::primaryScreen()->geometry();

	ICreateDevEnum* pCreateDevEnum = NULL;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum, (void**)&pCreateDevEnum);

	int index = 0;

	if (SUCCEEDED(hr))
	{
		IEnumMoniker* pEm = NULL;
		hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);



		if (hr == S_OK)  
		{
			IMoniker* pM;
			ULONG cFetched;

			
			while (pEm->Next(1, &pM, &cFetched) == S_OK)
			{
				IPropertyBag* pPropBag;
				hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void**)&pPropBag);

				if (SUCCEEDED(hr))
				{
					VARIANT varName;
					VariantInit(&varName);

					
					hr = pPropBag->Read(L"FriendlyName", &varName, 0);

					WCHAR* wszDisplayName = NULL;
					wszDisplayName = 0;

					bool succGetDispName = SUCCEEDED(pM->GetDisplayName(0, 0, &wszDisplayName));

			

					if (SUCCEEDED(hr) && succGetDispName)
					{
						
						QString name;

						name = variantToQString(varName);

						//name.fromStdWString(varName.bstrVal);
						selectVideoObjNameLock.lock();
						selectVideoObjName.push_back(name.toStdString());
						selectVideoObjNameLock.unlock();
						
						QCheckBox* checkBox = new QCheckBox(name, ui->widget_video_dev_list);
						checkBox->setObjectName(name);

						m_videoDevList.push_back(checkBox);
						layout->addWidget(checkBox);

						connect(checkBox, &QCheckBox::clicked, this, &CDlgSelectVideo::onCheckBoxClicked);

											

						if (rc.width() > 3500) {

							if (iCamCapType == CONST_camCapType_directX  && webcam_selected == wszDisplayName) {

								checkBox->setCheckState(Qt::Checked);
								checkBox->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
							}
							else {
								checkBox->setCheckState(Qt::Unchecked);
								checkBox->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
							}

							
						}
						else {

							if (iCamCapType == CONST_camCapType_directX  && webcam_selected == wszDisplayName) {

								checkBox->setCheckState(Qt::Checked);
								checkBox->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
								
							}
							else {

								checkBox->setCheckState(Qt::Unchecked);
								checkBox->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
							}

							
						}

						//wprintf(L"Camera: %s\n", varName.bstrVal);
						VariantClear(&varName);
						height += 60;

						videoMoniker[index] = pM;
						pM->AddRef();
						index++;
					}					

					

					pPropBag->Release();
				}

				pM->Release();
			}
			pEm->Release();
		}
		pCreateDevEnum->Release();
	}

	ui->widget_video_dev_list->setFixedHeight(height);
}

void IMonRelease(IMoniker*& pm)
{
	if (pm)
	{
		pm->Release();
		pm = 0;
	}
}


CDlgSelectVideo::~CDlgSelectVideo()
{
	delete ui;

	if (m_pInfraredMenu)
	{
		delete m_pInfraredMenu;
		m_pInfraredMenu = nullptr;
	}

	int size = sizeof(videoMoniker) / sizeof(IMoniker);;
	for (int i = 0; i < size; ++i) {
		IMonRelease(videoMoniker[i]);
	}

	clearSpecalObjName();
}


void CDlgSelectVideo::slot_boxEnableShare_change(int box_change)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	//if (box_change == 0)
	//{
	//	//未选
	//	_enable_share = false;


	//}
	//else if (box_change == 2)
	//{
	//	//已选
	//	_enable_share = true;
	//}
}

void CDlgSelectVideo::slot_boxRtsp_change(int box_change)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	//if (box_change == 0)
	//{
	//	//未选
	//	int aaa = 1;
	//	_auto_share = false;


	//}
	//else if (box_change == 2)
	//{
	//	//已选
	//	int aaa = 1;
	//	_auto_share = true;
	//}
}

void CDlgSelectVideo::sheetBackgroundImage()
{
	QRect rc = QApplication::primaryScreen()->geometry();

	if (rc.width() > 3500) {
		resize(2000, 1100);

		ui->widget->setStyleSheet("background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");
		ui->label_t1->setStyleSheet("border-bottom:5px solid  #fff;font-size:85px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t2->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t3->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t4->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");

		//ui->boxEnableShare->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxRtsp->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");

		ui->err_txt->setStyleSheet("font-size:32px;color:red");

		ui->btnOk->setStyleSheet("QPushButton{font-size:64px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		ui->btnOk->setFixedHeight(140);
		ui->btnOk->setFixedWidth(430);

		ui->btnCancle->setStyleSheet("QPushButton{font-size:64px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		ui->btnCancle->setFixedHeight(140);
		ui->btnCancle->setFixedWidth(430);

	}
	else {
		ui->widget->setStyleSheet("background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");
		ui->label_t1->setStyleSheet("border-bottom:5px solid  #fff;font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t2->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t3->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t4->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");

		//ui->boxEnableShare->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxRtsp->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");

		ui->rtspUrl->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");

		ui->err_txt->setStyleSheet("font-size:18px;color:red");

		ui->btnOk->setStyleSheet("QPushButton{font-size:32px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		ui->btnOk->setFixedHeight(65);
		ui->btnOk->setFixedWidth(200);

		ui->btnCancle->setStyleSheet("QPushButton{font-size:32px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		ui->btnCancle->setFixedHeight(65);
		ui->btnCancle->setFixedWidth(200);

	}

}




//初始化数据
void CDlgSelectVideo::initBoxStatus()
{

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		//

		//ui->boxEnableShare->setStyleSheet("QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
		ui->boxRtsp->setStyleSheet("QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

			
	}
	else {
		//
		//ui->boxEnableShare->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
		ui->boxRtsp->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

	}

	//
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();


	Qt::CheckState state;

	//state = pProcInfo->cfg.shareProcInitCfg.m_bEnableShare ? Qt::Checked : Qt::Unchecked;
	//ui->boxEnableShare->setCheckState(state);



	//state = pProcInfo->cfg.shareProcInitCfg.m_bAutoShare ? Qt::Checked : Qt::Unchecked;
	state = iCamCapType == CONST_camCapType_rtsp ? Qt::Checked : Qt::Unchecked;
	ui->boxRtsp->setCheckState(state);

	//_auto_share = pProcInfo->cfg.shareProcInitCfg.m_bAutoShare;


	//state = pProcInfo->cfg.shareProcInitCfg.m_bEnableShare ? Qt::Checked : Qt::Unchecked;
	//ui->boxEnableShare->setCheckState(state);

	//_enable_share = pProcInfo->cfg.shareProcInitCfg.m_bEnableShare;



	/*ShareProcInitCfg ipic = { 0 };
	if (!bGetShareProcInitCfg(pQyMc->cfg.shareProcInitFile, &ipic)) {
		memset(&ipic, 0, sizeof(ipic));
	}	*/

	//
	ui->rtspUrl->setText(QString::fromStdWString(RtspUrl_selected));

}

void CDlgSelectVideo::slot_mouse_boxRtsp_click(bool checked) {

	slot_boxRtsp_click("boxAutoShare");

}

void CDlgSelectVideo::slot_boxEnableShare_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		//if (ui->boxEnableShare->isChecked())
		//{
		//	ui->boxEnableShare->setCheckState(Qt::Unchecked);
		//	ui->boxEnableShare->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		//	//
		//	log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭HDMI1 OUT端口";
		//}
		//else {
		//	ui->boxEnableShare->setCheckState(Qt::Checked);
		//	ui->boxEnableShare->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
		//	//
		//	//qmcLogForHg(0, (TCHAR*)_T("终端关闭HDMI1 OUT端口"), false);

		//	//log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启HDMI1 OUT端口";
		//}
	}
	else {
//		if (ui->boxEnableShare->isChecked())
//		{
//			ui->boxEnableShare->setCheckState(Qt::Unchecked);
//			ui->boxEnableShare->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
//
//			//
//			//qmcLogForHg(0, (TCHAR*)_T("终端开启HDMI1 OUT端口"), false);
////			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭HDMI1 OUT端口";
//
//		}
//		else {
//			ui->boxEnableShare->setCheckState(Qt::Checked);
//			ui->boxEnableShare->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
//			//
//			//qmcLogForHg(0, (TCHAR*)_T("终端关闭HDMI1 OUT端口"), false);
//			//log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启HDMI1 OUT端口";
//		}
	}
	//qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

}

//按确认键
void CDlgSelectVideo::slot_btnOk_click()
{

	//_auto_share;	
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	QString rtspUrl = ui->rtspUrl->text();
	QY_REG  reg;
	TCHAR  tBuf[256] = _T("");
	memset(&reg, 0, sizeof(reg));

	if (iCamCapType == CONST_camCapType_rtsp) {
		char  buf[256] = {'\0'};
		safeStrnCpy(rtspUrl.toUtf8().data(), buf, mycountof(buf));
		trim(buf);
		bool hasCredentials;

		RtspUrl_selected = ui->rtspUrl->text().toStdWString();

		if (!validateRtspUrlnn(buf, hasCredentials)) {

			//
			ui->err_txt->setText(u8"Rtsp Url输入无效，请输入有效格式！");
			ui->err_widget->setVisible(true);
			//
			ui->rtspUrl->setFocus();

			return;
		}

		reg.hKeyRoot0 = HKEY_CURRENT_USER;
		lstrcpyn(reg.rootKey, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, mycountof(reg.rootKey));

		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_camCapType), _ltot(CONST_camCapType_rtsp, tBuf, 10));

		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_rtspUrl_selected), RtspUrl_selected.c_str());
	}
	else if (iCamCapType == CONST_camCapType_directX) {


		reg.hKeyRoot0 = HKEY_CURRENT_USER;
		lstrcpyn(reg.rootKey, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, mycountof(reg.rootKey));

		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_camCapType), _ltot(CONST_camCapType_directX, tBuf, 10));

		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_webcam_selected), webcam_selected.c_str());

	}

	/*
	//
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();


	ShareProcInitCfg ipic = { 0 };
	memset(&ipic, 0, sizeof(ipic));

	//
	char  buf[256];
	TCHAR  tBuf[256];


	//
	safeStrnCpy(rtspUrl.toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (_enable_share) {
		bool hasCredentials;
		if (!validateRtspUrlnn(buf, hasCredentials)) {

			//
			ui->err_txt->setText(u8"Rtsp Url输入无效，\n有效格式！");
			ui->err_widget->setVisible(true);
			//
			ui->rtspUrl->setFocus();

			return;
		}
	}

	safeStrnCpy(buf, ipic.rtspUrl, mycountof(ipic.rtspUrl));


//
	ipic.m_bEnableShare = _enable_share;
	ipic.m_bAutoShare = _auto_share;


	//
	if (memcmp(&ipic, &pProcInfo->cfg.shareProcInitCfg, sizeof(ipic))) {
		if (saveSmShareInitCfg(&ipic, pQyMc->cfg.shareProcInitFile)) {
			//
			ui->err_txt->setText(u8"保存失败");
			ui->err_widget->setVisible(true);
			//
			return;
		}
	}

	//
	bGetShareProcInitCfg(pQyMc->cfg.shareProcInitFile, &pProcInfo->cfg.shareProcInitCfg);
	*/

	int ii = 0;

	emit to_returnMain_selectVideo_signal();
}

void CDlgSelectVideo::slot_btnCancle_click()
{
	emit to_returnMain_selectVideo_signal();

}




//菜单关闭
void CDlgSelectVideo::infraredMenu_quit()
{
	if (!m_pInfraredMenu)
	{
		return;
	}

	{

		m_pInfraredMenu->close();
		if (m_pInfraredMenu)
		{
			delete m_pInfraredMenu;
			m_pInfraredMenu = nullptr;
		}

	}

	return;

}


//下箭头
void CDlgSelectVideo::Infrared_down()
{
	if (m_pInfraredMenu) {
		m_pInfraredMenu->Infrared_down();
		return;
	}
	this->focusNextPrevChild(true);
	ui->rtspUrl->deselect();
	
}
//上箭头
void CDlgSelectVideo::Infrared_up()
{
	if (m_pInfraredMenu) {
		m_pInfraredMenu->Infrared_up();
		return;
	}
	this->focusNextPrevChild(false);
	ui->rtspUrl->deselect();

}

//左右光标移动
void CDlgSelectVideo::Infrared_input_left_right(QString name, bool isLeft)
{


	if (isLeft) {
		if (name == "rtspUrl") {
			int cur_index = ui->rtspUrl->cursorPosition();
			ui->rtspUrl->setCursorPosition(cur_index - 1);
		
		}	
		else {

			for (int i = 0; i < m_videoDevList.size(); ++i) {
				if (m_videoDevList[i]->objectName() == name) {
					if (i == 0) {
						if (m_videoDevList.size() > 1) {
							
						}

					}
					else if (i == m_videoDevList.size() - 1) {
						m_videoDevList[i]->clearFocus();
						m_videoDevList[i - 1]->setFocus();
					}
					else {
						m_videoDevList[i]->clearFocus();
						m_videoDevList[i - 1]->setFocus();
					}
					break;
				}

			}
		}

	}
	else {
		if (name == "rtspUrl") {
			int cur_index = ui->rtspUrl->cursorPosition();
			ui->rtspUrl->setCursorPosition(cur_index + 1);

		}
		else {

			for (int i = 0; i < m_videoDevList.size(); ++i) {
				if (m_videoDevList[i]->objectName() == name) {
					if (i == 0) {
						if (m_videoDevList.size() > 1) {
							m_videoDevList[0]->clearFocus();
							m_videoDevList[1]->setFocus();
						}

					}
					else if (i == m_videoDevList.size() - 1) {

					}
					else {
						m_videoDevList[i]->clearFocus();
						m_videoDevList[i + 1]->setFocus();
					}
					break;
				}

			}
		}
		
	}
}


//表单输入
void CDlgSelectVideo::Infrared_input(QString name, QString value)
{
	if (name == "rtspUrl") {
		ui->rtspUrl->insert(value);
	}
	
}

//表单输入字母
void CDlgSelectVideo::Infrared_input_leeter(QString name, QString value, bool is_replace)
{
	if (name == "rtspUrl") {
		if (is_replace) {
			ui->rtspUrl->backspace();
		}
		ui->rtspUrl->insert(value);
	}
	
}

//退格键
void CDlgSelectVideo::Infrared_input_backspace(QString name)
{
	if (name == "rtspUrl") {
		ui->rtspUrl->backspace();
	}
	
}


void CDlgSelectVideo::slot_boxRtsp_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	ui->boxRtsp->setCheckState(Qt::Checked);
	QRect rc = QApplication::primaryScreen()->geometry();

	

	if (rc.width() > 3500) {
		ui->boxRtsp->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
	}
	else {
		ui->boxRtsp->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
	}

	for (int i = 0; i < m_videoDevList.size(); ++i) {
		m_videoDevList[i]->setCheckState(Qt::Unchecked);
		if (rc.width() > 3500) {
			m_videoDevList[i]->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		}
		else {
			m_videoDevList[i]->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		}
	}

	iCamCapType = CONST_camCapType_rtsp;
	ui->rtspUrl->setEnabled(TRUE);

//	QRect rc = QApplication::desktop()->screenGeometry();
//	if (rc.width() > 3500) {
//		if (ui->boxRtsp->isChecked())
//		{
//			ui->boxRtsp->setCheckState(Qt::Unchecked);
//			ui->boxRtsp->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
//			//
//			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭HDMI1 OUT端口";
//		}
//		else {
//			ui->boxRtsp->setCheckState(Qt::Checked);
//			ui->boxRtsp->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
//			//
//			//qmcLogForHg(0, (TCHAR*)_T("终端关闭HDMI1 OUT端口"), false);
//
//			//log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启HDMI1 OUT端口";
//		}
//	}
//	else {
//		if (ui->boxRtsp->isChecked())
//		{
//			ui->boxRtsp->setCheckState(Qt::Unchecked);
//			ui->boxRtsp->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
//
//			//
//			//qmcLogForHg(0, (TCHAR*)_T("终端开启HDMI1 OUT端口"), false);
////			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭HDMI1 OUT端口";
//
//		}
//		else {
//			ui->boxRtsp->setCheckState(Qt::Checked);
//			ui->boxRtsp->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
//			//
//			//qmcLogForHg(0, (TCHAR*)_T("终端关闭HDMI1 OUT端口"), false);
//			//log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启HDMI1 OUT端口";
//		}
//	}
	//qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

}

void CDlgSelectVideo::slot_checkBox_click(QString objname)
{

	QRect rc = QApplication::primaryScreen()->geometry();

	for (int i = 0; i < m_videoDevList.size(); ++i) {

		if (m_videoDevList[i]->objectName() != objname) {

			m_videoDevList[i]->setCheckState(Qt::Unchecked);
			if (rc.width() > 3500) {
				m_videoDevList[i]->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			}
			else {
				m_videoDevList[i]->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			}
		}
		else {
			m_videoDevList[i]->setCheckState(Qt::Checked);
			if (rc.width() > 3500) {
				m_videoDevList[i]->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			}
			else {
				m_videoDevList[i]->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			}

			if (videoMoniker[i]) {
				WCHAR* wszDisplayName = NULL;
				wszDisplayName = 0;

				if (SUCCEEDED(videoMoniker[i]->GetDisplayName(0, 0, &wszDisplayName)) && wszDisplayName) {

					webcam_selected = wszDisplayName;
				}
			}

		}
	}

	iCamCapType = CONST_camCapType_directX;

	ui->boxRtsp->setCheckState(Qt::Unchecked);
	ui->rtspUrl->setEnabled(FALSE);


	if (rc.width() > 3500) {
		ui->boxRtsp->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
	}
	else {
		ui->boxRtsp->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
	}
}