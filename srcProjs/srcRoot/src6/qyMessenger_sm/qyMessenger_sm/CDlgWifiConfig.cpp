#include "CDlgWifiConfig.h"
//
//#include <QDesktopWidget>
#include	<qscreen.h>

//
#include	<tchar.h>
#include	"qyMcMainCommon_qt.h"
#include <ctxQmc.h>
#include	<ctxQmc_sm.h>
#include <QMessageBox>

#include <QTreeWidget>
#include <QDateTime>
#include <QTextCursor>

static CDlgWifiConfig* g_CDlgWifiConfig;

/*
void OnWlanConnectCallback(PWLAN_CONNECTION_NOTIFICATION_DATA pData, DWORD dwConnectCode)
{
	if (g_CDlgWifiConfig)
	{
		
		if (g_CDlgWifiConfig->getMsg()->toPlainText().length() > 300)
		{
			g_CDlgWifiConfig->getMsg()->setText("");
		}

		QDateTime currentDateTime = QDateTime::currentDateTime();
		QString cstrDate, cstrTime;


		cstrDate = currentDateTime.toString("yyyy-MM-dd");
		cstrTime = currentDateTime.toString("hh:mm:ss");


		if (pData)
		{
			std::wstring cstrSSID = pData->strProfileName;
			g_CDlgWifiConfig->getMsg()->append(cstrTime.append(QString::fromStdWString(cstrSSID)).append(":"));
			switch (dwConnectCode)
			{
			case wlan_notification_acm_connection_start:
				g_CDlgWifiConfig->getMsg()->append(QString(u8"开始连接\r\n"));
				break;
			case wlan_notification_acm_connection_complete:
			{
				if (pData->wlanReasonCode == WLAN_REASON_CODE_SUCCESS)
				{
					g_CDlgWifiConfig->getMsg()->append(QString(u8"连接成功\r\n"));
				}
				else
				{
					WCHAR wcReasonCode[100] = { 0 };
					WlanReasonCodeToString(pData->wlanReasonCode, 100, wcReasonCode, NULL);
					g_CDlgWifiConfig->getMsg()->append(QString(u8"连接失败，")); //以这个成功失败作为结果上传
					std::wstring cstrReason = wcReasonCode;
					g_CDlgWifiConfig->getMsg()->append(QString::fromStdWString(cstrReason).append("\r\n"));
				}
			}
			break;
			case wlan_notification_acm_connection_attempt_fail: //尝试连接失败后会，系统还会发送wlan_notification_acm_connection_complete，标注失败原因
				g_CDlgWifiConfig->getMsg()->append(QString(u8"尝试连接失败\r\n"));
				break;
			case wlan_notification_acm_disconnecting:
				g_CDlgWifiConfig->getMsg()->append(QString(u8"正在断开\r\n"));
				break;
			case wlan_notification_acm_disconnected:
				g_CDlgWifiConfig->getMsg()->append(QString(u8"已经断开\r\n"));
				break;
			default:
				break;
			}
		}
		else
		{
			g_CDlgWifiConfig->getMsg()->append(cstrTime);
			switch (dwConnectCode)
			{
			case wlan_notification_acm_scan_complete:
				g_CDlgWifiConfig->getMsg()->append(QString(u8"扫描完成\r\n"));
				break;
			case wlan_notification_acm_scan_fail:
				g_CDlgWifiConfig->getMsg()->append(QString(u8"扫描失败\r\n"));
				break;
			default:
				break;
			}
		}
		//g_CDlgWifiConfig->GetDlgItem(IDC_STATIC_LOG)->SetWindowText(g_CWiFiManagerToolsDlg->m_cstrLog);

	}
}
*/

void OnWlanConnectCallback(PWLAN_CONNECTION_NOTIFICATION_DATA pData, DWORD dwConnectCode)
{
	if (g_CDlgWifiConfig)
	{
		QString msg = g_CDlgWifiConfig->getMsg();
		if (msg.length() > 300)	{
			msg = "";
		}

		QDateTime currentDateTime = QDateTime::currentDateTime();
		QString cstrDate, cstrTime;

		cstrDate = currentDateTime.toString("yyyy-MM-dd");
		cstrTime = currentDateTime.toString("hh:mm:ss");

		if (pData)
		{
			std::wstring cstrSSID = pData->strProfileName;
			msg.append(cstrTime.append(QString::fromStdWString(cstrSSID)).append(":"));
			switch (dwConnectCode)
			{
			case wlan_notification_acm_connection_start:
				msg.append(QString(u8"开始连接\r\n"));
				break;
			case wlan_notification_acm_connection_complete:
			{
				if (pData->wlanReasonCode == WLAN_REASON_CODE_SUCCESS)
				{
					msg.append(QString(u8"连接成功\r\n"));

					g_CDlgWifiConfig->SetWlan();

					g_CDlgWifiConfig->SetConnectButtonState(cstrSSID, true);
				}
				else
				{
					WCHAR wcReasonCode[100] = { 0 };
					WlanReasonCodeToString(pData->wlanReasonCode, 100, wcReasonCode, NULL);
					msg.append(QString(u8"连接失败，")); //以这个成功失败作为结果上传
					std::wstring cstrReason = wcReasonCode;
					msg.append(QString::fromStdWString(cstrReason).append("\r\n"));
				}
			}
			break;
			case wlan_notification_acm_connection_attempt_fail: //尝试连接失败后会，系统还会发送wlan_notification_acm_connection_complete，标注失败原因
				msg.append(QString(u8"尝试连接失败\r\n"));
				break;
			case wlan_notification_acm_disconnecting:
				msg.append(QString(u8"正在断开\r\n"));
				break;
			case wlan_notification_acm_disconnected:
				msg.append(QString(u8"已经断开\r\n"));
				g_CDlgWifiConfig->SetConnectButtonState(cstrSSID, false);
				break;
			default:
				break;
			}
		}
		else
		{
			msg.append(cstrTime);
			switch (dwConnectCode)
			{
			case wlan_notification_acm_scan_complete:
				msg.append(QString(u8"扫描完成\r\n"));
				break;
			case wlan_notification_acm_scan_fail:
				msg.append(QString(u8"扫描失败\r\n"));
				break;
			default:
				break;
			}
		}
		g_CDlgWifiConfig->setMsg(msg);


	}
}

#include <sstream>

std::string GetCommandOutput(const std::wstring& cmd) {
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
		return "";
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	if (!CreateProcess(NULL, (LPWSTR)cmd.c_str(), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi)) {
		CloseHandle(hWrite);
		CloseHandle(hRead);
		return "";
	}

	CloseHandle(hWrite);

	char buffer[4096];
	std::string result;
	DWORD bytesRead;

	while (true) {
		memset(buffer, 0, 4096);
		if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == NULL) break;
		if (bytesRead == 0) break;
		result.append(buffer, bytesRead);
	}

	CloseHandle(hRead);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return result;
}

/*
bool CDlgWifiConfig::SetWlan() {

	TCHAR szPath[MAX_PATH] = _T("netsh interface ip set address name=\"WLAN\" source=dhcp");

	std::wstring command = szPath;
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	if (!CreateProcess(NULL, const_cast<LPWSTR>(command.c_str()), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
		//std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
		std::stringstream ss;
		ss << "CreateProcess failed (" << GetLastError() << ").";
		
		return false;
	}

	// 等待进程结束
	WaitForSingleObject(pi.hProcess, INFINITE);

	// 关闭进程和线程句柄
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return true;
}
*/

/*

#include <iphlpapi.h>
#include <windows.h>
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "WS2_32.lib")

bool IsWirelessNetworkConnected() {
	PIP_ADAPTER_INFO pAdapterInfo = new IP_ADAPTER_INFO;
	DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);

	if (GetAdaptersInfo(pAdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) {
		delete pAdapterInfo;
		pAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[dwBufLen];
	}

	if (GetAdaptersInfo(pAdapterInfo, &dwBufLen) == NO_ERROR) {
		while (pAdapterInfo) {
			if (pAdapterInfo->Type == MIB_IF_TYPE_WIFI) {
				if (pAdapterInfo->DhcpEnabled) {
					if (pAdapterInfo->LeaseObtained) {
						delete[] pAdapterInfo;
						return true; // 无线网络已连接且获得了DHCP租约
					}
				}
				else {
					
					if (pAdapterInfo->GatewayList.dwNumEntries > 0) {
						delete[] pAdapterInfo;
						return true; // 无线网络已连接且静态IP配置有网关
					}
				}
			}
			pAdapterInfo = pAdapterInfo->Next;
		}
	}

	delete[] pAdapterInfo;
	return false; // 未检测到无线网络连接
}

#include <QNetworkConfigurationManager>
#include <QNetworkConfiguration>

bool isWirelessNetworkConnected() {
	QNetworkConfigurationManager manager;
	bool isWirelessAvailable = false;
	foreach(const QNetworkConfiguration & config, manager.allConfigurations()) {
		if (config.bearerType() == QNetworkConfiguration::BearerType::BearerWLAN) {
			isWirelessAvailable = true;
			QNetworkConfiguration::StateFlags flags = manager.state(config);
			manager.
			
			if (flags.testFlag(QNetworkConfiguration::Active)) {
				// 无线网络已连接
				return true;
			}
		}
	}
	return isWirelessAvailable && manager.isOnline();
}
*/


#include <iostream>
#include <windows.h>
#include <string>

bool IsWirelessNetworkConnected() {
	// 使用系统命令netsh获取网络接口信息
	// 注意：这个命令可能会因操作系统的语言版本而有所不同
	// 如果你的系统是英文版，可能需要使用"netsh wlan show interfaces"
	std::string command = "netsh interface ipv4 show interfaces";
	FILE* pipe = _popen(command.c_str(), "r");
	if (!pipe) return false;

	char buffer[128];
	std::string result = "";
	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe) != NULL) {
			result += buffer;
		}
	}
	_pclose(pipe);

	// 检查结果中是否包含"Wireless"字样，这表明是无线接口
	// 同时检查是否显示"Connected"状态
	if (result.find("Wireless") != std::string::npos &&
		result.find("Connected") != std::string::npos) {
		return true;
	}
	return false;
}

bool CDlgWifiConfig::SetWlan() {

	TCHAR szPath[MAX_PATH] = _T("netsh interface ip set address name=\"WLAN\" source=dhcp");

	std::wstring command = szPath;
	std::string result = GetCommandOutput(command);

	return true;
}


UINT gfunc_getWiFiList(LPVOID pParam)
{
	CDlgWifiConfig* pDlg = (CDlgWifiConfig*)pParam;
	while (pDlg->m_running)
	{
		WiFiInfoList Wifilist;
		WiFiManager::GetInstance().GetWiFiList(Wifilist);//WlanScan会阻塞
		std::unique_lock<std::mutex> lock(pDlg->m_mutex);
		pDlg->m_Wifilist = Wifilist;
		Sleep(100);
	}
	return 0;
}


CDlgWifiConfig::CDlgWifiConfig(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::CDlgWifiConfigClass),
	m_thread(nullptr),
	m_running(false)
{

	ui->setupUi(this);

	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

	sheetBackgroundImage();

	//connect(ui->btnOk, SIGNAL(sigClicked()), this, SLOT(slot_btnOk_click()));

	
	connect(ui->btnOk, &QPushButton::clicked, [this] {
		//QMessageBox::information(0, tr("提示"), tr("槽函数！"));
		this->slot_btnOk_click();
		});

	connect(ui->pushButton_detect, &QPushButton::clicked, [this] {
		//QMessageBox::information(0, tr("提示"), tr("槽函数！"));
		this->slot_pushButton_detect_click();
		});

	connect(ui->pushButton_conn, &QPushButton::clicked, [this] {
		//QMessageBox::information(0, tr("提示"), tr("槽函数！"));
		this->slot_pushButton_conn_click();
		});

	connect(this, SIGNAL(to_returnMain_wifi_signal()), parent, SLOT(on_closeWifi_slots()));

	QObject::connect(ui->treeWidget_wifi, &QTreeWidget::itemDoubleClicked, [this](QTreeWidgetItem* item, int column) {
		//qDebug() << "Double clicked on:" << item->text(column);
		this->wifiDoubleClicked(item, column);
		});
		
	connect(this, SIGNAL(set_conn_button_text_sigle(QString)), this, SLOT(slot_set_conn_button_text(QString)));
	connect(this, SIGNAL(set_msg_sigle(QString)), this, SLOT(slot_set_msg(QString)));

	
	WiFiManager::GetInstance().RigisterConnectNotification(CONNECT_NOTIFICATION_CALLBACK(OnWlanConnectCallback));


	m_timer = new QTimer(this);

	connect(m_timer, &QTimer::timeout, this, &CDlgWifiConfig::doTimeout);
	m_timer->setInterval(3000);
	//m_timer->start(1000);
	m_timer->start();
	
	connect(this, SIGNAL(update_wifi_signal()), this, SLOT(slot_update_wifi()));

	 
	m_running = true;
	m_thread = new std::thread(gfunc_getWiFiList, this);
	//m_thread->detach();

	showWifi();

	g_CDlgWifiConfig = this;
}

void CDlgWifiConfig::wifiDoubleClicked(QTreeWidgetItem* item, int column) 
{
	if (item) {
		ui->lineEdit_ssid->setText(item->text(0));
		ui->lineEdit_pw->setText(item->text(3));

		QString state = item->text(2);

		if (state.compare(u8"已连接") == 0) {
			ui->pushButton_conn->setText(u8"断开");
		}
		else {
			ui->pushButton_conn->setText(u8"连接");
		}
	}
}

void CDlgWifiConfig::slot_wifi_enter() {
	QTreeWidgetItem* currentItem = ui->treeWidget_wifi->currentItem();

	if (currentItem) {
		ui->lineEdit_ssid->setText(currentItem->text(0));
		ui->lineEdit_pw->setText(currentItem->text(3));

		QString state = currentItem->text(2);

		if (state.compare(u8"已连接") == 0) {
			ui->pushButton_conn->setText(u8"断开");
		}
		else {
			ui->pushButton_conn->setText(u8"连接");
		}
	}
}

void CDlgWifiConfig::slot_set_conn_button_text(QString text)
{
	ui->pushButton_conn->setText(text);
}

void CDlgWifiConfig::slot_set_msg(QString text)
{
	ui->textEdit_msg->setText(text);
	ui->textEdit_msg->moveCursor(QTextCursor::End);
}

CDlgWifiConfig::~CDlgWifiConfig()
{
	
	if (m_thread) {
		m_running = false;
		m_thread->join();
		delete(m_thread);
	}

	g_CDlgWifiConfig = nullptr;

}

void CDlgWifiConfig::showWifi() {
	//QTreeWidget treeWidget;
	ui->treeWidget_wifi->setColumnCount(4);
	QTreeWidgetItem* headerItem = new QTreeWidgetItem();
	headerItem->setText(0, "ssid");
	headerItem->setText(1, QString::fromStdWString(L"信号"));
	headerItem->setText(2, QString::fromStdWString(L"连接状态"));
	headerItem->setText(3, QString::fromStdWString(L"密码"));
	ui->treeWidget_wifi->setHeaderItem(headerItem);

	ui->treeWidget_wifi->setColumnWidth(0, 140);
	ui->treeWidget_wifi->setColumnWidth(1, 40);
	ui->treeWidget_wifi->setColumnWidth(2, 80);

	/*
	QTreeWidgetItem* topLevelItem1 = new QTreeWidgetItem();
	topLevelItem1->setText(0, "test");
	topLevelItem1->setText(1, "88");
	ui->treeWidget_wifi->addTopLevelItem(topLevelItem1);



	QTreeWidgetItem* topLevelItem2 = new QTreeWidgetItem();
	topLevelItem2->setText(0, "test2");
	topLevelItem2->setText(1, "200");
	ui->treeWidget_wifi->addTopLevelItem(topLevelItem2);
	*/
}

void CDlgWifiConfig::slot_update_wifi()
{
	doTimeout();
}

void CDlgWifiConfig::doTimeout() {

	while (ui->treeWidget_wifi->topLevelItemCount() > 0) {
		delete ui->treeWidget_wifi->takeTopLevelItem(0);
	}

	std::unique_lock<std::mutex> lock(m_mutex);
	int count = 0;
	//for each (auto var in m_Wifilist) 
	for ( const auto &var : m_Wifilist )
	{
		if (var.cstrSSID.length() == 0) {
			continue;
		}

		QTreeWidgetItem* topLevelItem1 = new QTreeWidgetItem();
		topLevelItem1->setText(0, QString::fromStdWString(var.cstrSSID));
		topLevelItem1->setText(1, QString::number(var.nSignalValue));

		std::wstring cstrStatus;
		cstrStatus = var.bLinked ? _T("已连接") : _T("");
		topLevelItem1->setText(2, QString::fromStdWString(cstrStatus));
		topLevelItem1->setText(3, QString::fromStdWString(var.cstrPassword));
		//topLevelItem1->setStyleSheet("background-color: blue; color: white;");
		

		ui->treeWidget_wifi->addTopLevelItem(topLevelItem1);

		count++;

	}

	if (count > 0) {

		QTreeWidgetItem* nextItem = ui->treeWidget_wifi->topLevelItem(0);

		ui->treeWidget_wifi->setCurrentItem(nextItem);
	}
}


void CDlgWifiConfig::sheetBackgroundImage()
{
	QRect rc = QApplication::primaryScreen()->geometry();

	if (rc.width() > 3500) {
		resize(2000, 1100);

		ui->widget->setStyleSheet("background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");

		ui->label_title->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_ssid->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_pw->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");

		ui->pushButton_detect->setStyleSheet("QPushButton{font-size:64px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->pushButton_detect->setFixedHeight(140);
		ui->pushButton_detect->setFixedWidth(430);

		ui->pushButton_conn->setStyleSheet("QPushButton{font-size:64px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->pushButton_conn->setFixedHeight(140);
		ui->pushButton_conn->setFixedWidth(430);

		ui->btnOk->setStyleSheet("QPushButton{font-size:64px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->btnOk->setFixedHeight(140);
		ui->btnOk->setFixedWidth(430);

		/*
		ui->label_t1->setStyleSheet("border-bottom:5px solid  #fff;font-size:85px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t2->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t3->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t4->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t5->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t6->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");

		ui->boxNvrEna->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxNvrHik->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");

		ui->err_txt->setStyleSheet("font-size:32px;color:red");

		ui->btnOk->setStyleSheet("QPushButton{font-size:64px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		ui->btnOk->setFixedHeight(140);
		ui->btnOk->setFixedWidth(430);
		*/

	}
	else {
		ui->widget->setStyleSheet("background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");

		ui->label_title->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_ssid->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_pw->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->lineEdit_ssid->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->lineEdit_pw->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");

		ui->pushButton_detect->setStyleSheet("QPushButton{font-size:28px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->pushButton_detect->setFixedHeight(41);
		ui->pushButton_detect->setFixedWidth(93);

		ui->pushButton_conn->setStyleSheet("QPushButton{font-size:28px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->pushButton_conn->setFixedHeight(41);
		ui->pushButton_conn->setFixedWidth(93);

		ui->btnOk->setStyleSheet("QPushButton{font-size:28px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		ui->btnOk->setFixedHeight(41);
		ui->btnOk->setFixedWidth(93);

		ui->treeWidget_wifi->setStyleSheet("QTreeView::item{height: 30px; color: white;}");

		ui->textEdit_msg->setStyleSheet("QTextEdit{color:white;}");

		/*
		ui->label_t1->setStyleSheet("border-bottom:5px solid  #fff;font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t2->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t3->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t4->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t5->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t6->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");

		ui->boxNvrEna->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxNvrHik->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");

		ui->NvrIp->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->NvrName->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");
		ui->NvrPwd->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");

		ui->err_txt->setStyleSheet("font-size:18px;color:red");

		ui->btnOk->setStyleSheet("QPushButton{font-size:32px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		ui->btnOk->setFixedHeight(65);
		ui->btnOk->setFixedWidth(200);
		*/

	}

}


void CDlgWifiConfig::slot_btnOk_click()
{
	emit to_returnMain_wifi_signal();
}

void CDlgWifiConfig::slot_pushButton_detect_click()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	WiFiManager::GetInstance().ScanWiFi();
}

void CDlgWifiConfig::slot_pushButton_conn_click()
{
	QString curSSID, targetKey;

	curSSID = ui->lineEdit_ssid->text();

	if (curSSID.length() <= 0) {
		//ui->textEdit_msg->setText(QString(u8"ssid不能为空\r\n"));
		setMsg(QString(u8"ssid不能为空\r\n"));
		return;
	}

	targetKey = ui->lineEdit_pw->text();


	if (targetKey.length() < 8) {
		//ui->textEdit_msg->setText(QString(u8"密码长度不能小于8\r\n"));
		setMsg(QString(QString(u8"密码长度不能小于8\r\n")));
		return;
	}

	//m_cstrLog = L"";
	//GetDlgItem(IDC_STATIC_LOG)->SetWindowText(m_cstrLog);
	//m_mutexMsg.lock();
	//ui->textEdit_msg->setText("");
	setMsg("");
	//m_mutexMsg.unlock();
	

	std::unique_lock<std::mutex> lock(m_mutex);

	QString state = ui->pushButton_conn->text();
	if(state.compare(u8"连接") == 0) 
	    WiFiManager::GetInstance().ConnectWiFi(curSSID.toStdWString(), targetKey.toStdWString());
	else
		WiFiManager::GetInstance().ConnectWiFi(curSSID.toStdWString(), targetKey.toStdWString(), false);

	this->setFocus();
}

/*
QTextEdit* CDlgWifiConfig::getMsg() {
	return ui->textEdit_msg;
}
*/

QString CDlgWifiConfig::getMsg() {
	//std::unique_lock<std::mutex> lock(m_mutexMsg);
	//return ui->textEdit_msg->toPlainText();

	/*
	QString text;
	QMetaObject::invokeMethod(ui->textEdit_msg, "getText", Qt::QueuedConnection, Q_RETURN_ARG(QString, text));
	return text;
	*/

	return m_msg;
}

void CDlgWifiConfig::setMsg(const QString& msg) {
	//std::unique_lock<std::mutex> lock(m_mutexMsg);
	//ui->textEdit_msg->setText(msg);

	m_msg = msg;

	//QMetaObject::invokeMethod(ui->textEdit_msg, "setText", Q_ARG(QString, msg));
	//emit update_wifi_signal();
	emit set_msg_sigle(msg);
}


//菜单关闭
void CDlgWifiConfig::infraredMenu_quit()
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
void CDlgWifiConfig::Infrared_down()
{
	if (m_pInfraredMenu) {
		m_pInfraredMenu->Infrared_down();
		return;
	}
	this->focusNextPrevChild(true);
	//ui->NvrIp->deselect();
	//ui->NvrName->deselect();
	//ui->NvrPwd->deselect();
}
//上箭头
void CDlgWifiConfig::Infrared_up()
{
	if (m_pInfraredMenu) {
		m_pInfraredMenu->Infrared_up();
		return;
	}
	this->focusNextPrevChild(false);
	//ui->NvrIp->deselect();
	//ui->NvrName->deselect();
	//ui->NvrPwd->deselect();
}

#include <QTextLayout>
#include <QTextBlock>

//左右光标移动
void CDlgWifiConfig::Infrared_input_left_right(QString name, bool isLeft)
{

	if (isLeft) {
		if (name == "lineEdit_ssid") {
			int cur_index = ui->lineEdit_ssid->cursorPosition();
			ui->lineEdit_ssid->setCursorPosition(cur_index - 1);
			//ui->NvrPwd->cursorBackward(true);
		}
		else
			if (name == "lineEdit_pw") {
				int cur_index = ui->lineEdit_pw->cursorPosition();
				ui->lineEdit_pw->setCursorPosition(cur_index - 1);
				//ui->NvrPwd->cursorBackward(true);
			}
			else
				if (name == "treeWidget_wifi") {
				
					m_timer->stop();
					
					QList<QTreeWidgetItem*> selectedItems = ui->treeWidget_wifi->selectedItems();

					if (selectedItems.count() > 1) {
						ui->treeWidget_wifi->clearSelection();
					}

					if (selectedItems.count() == 1) {
					
						int itemCount = ui->treeWidget_wifi->topLevelItemCount();
						if (itemCount == 1) {

						}
						else {
							QTreeWidgetItem* currentItem = ui->treeWidget_wifi->currentItem();
							if (currentItem) {
								int index = ui->treeWidget_wifi->indexOfTopLevelItem(currentItem);
								//qDebug() << "当前选中项的位置：" << index;

								

								QTreeWidgetItem* nextItem = ui->treeWidget_wifi->topLevelItem(index == 0 ? itemCount - 1 : index - 1);

								ui->treeWidget_wifi->setCurrentItem(nextItem);
							}
						}
					}
					else {
						QTreeWidgetItem* nextItem = ui->treeWidget_wifi->topLevelItem(0);

						ui->treeWidget_wifi->setCurrentItem(nextItem);
					}
					
					m_timer->start();

				}
				else if (name == "textEdit_msg") {
					QTextCursor tc = ui->textEdit_msg->textCursor();
					QTextLayout* pLayout = tc.block().layout();
					int nCurpos = tc.position() - tc.block().position();
					int nTextline = pLayout->lineForTextPosition(nCurpos).lineNumber() + tc.block().firstLineNumber();


					QTextBlock block = ui->textEdit_msg->document()->findBlockByNumber(nTextline - 1);
					ui->textEdit_msg->setTextCursor(QTextCursor(block));
				}


	}
	else {
		if (name == "lineEdit_ssid") {
			int cur_index = ui->lineEdit_ssid->cursorPosition();
			ui->lineEdit_ssid->setCursorPosition(cur_index + 1);
			//ui->NvrPwd->cursorForward(true);
		}
		else
			if (name == "lineEdit_pw") {
				int cur_index = ui->lineEdit_pw->cursorPosition();
				ui->lineEdit_pw->setCursorPosition(cur_index + 1);
				//ui->NvrPwd->cursorForward(true);
			}
			else
				 if (name == "treeWidget_wifi") {
					
					 m_timer->stop();

					 QList<QTreeWidgetItem*> selectedItems = ui->treeWidget_wifi->selectedItems();

					 if (selectedItems.count() > 1) {
						 ui->treeWidget_wifi->clearSelection();
					 }

					 if (selectedItems.count() == 1) {

						 int itemCount = ui->treeWidget_wifi->topLevelItemCount();
						 if (itemCount == 1) {

						 }
						 else {
							 QTreeWidgetItem* currentItem = ui->treeWidget_wifi->currentItem();
							 if (currentItem) {
								 int index = ui->treeWidget_wifi->indexOfTopLevelItem(currentItem);
								 //qDebug() << "当前选中项的位置：" << index;

								 QTreeWidgetItem* nextItem = ui->treeWidget_wifi->topLevelItem((index + 1) % itemCount);

								 ui->treeWidget_wifi->setCurrentItem(nextItem);
							 }
						 }
					 }
					 else {
						 QTreeWidgetItem* nextItem = ui->treeWidget_wifi->topLevelItem(0);

						 ui->treeWidget_wifi->setCurrentItem(nextItem);
					 }
					 
					 m_timer->start();
				}
				 else if (name == "textEdit_msg") {

					 QTextCursor tc = ui->textEdit_msg->textCursor();
					 QTextLayout* pLayout = tc.block().layout();
					 int nCurpos = tc.position() - tc.block().position();
					 int nTextline = pLayout->lineForTextPosition(nCurpos).lineNumber() + tc.block().firstLineNumber();


					 QTextBlock block = ui->textEdit_msg->document()->findBlockByNumber(nTextline + 1);
					 ui->textEdit_msg->setTextCursor(QTextCursor(block));

				 }
	}	
	
	
}


//表单输入
void CDlgWifiConfig::Infrared_input(QString name, QString value)
{
	if (name == "lineEdit_ssid") {
		//QString tmp_str = ui->NvrPwd->text();
		ui->lineEdit_ssid->insert(value);
	}
	else
		if (name == "lineEdit_pw") {
			//QString tmp_str = ui->NvrPwd->text();
			ui->lineEdit_pw->insert(value);
		}

		
}

//表单输入字母
void CDlgWifiConfig::Infrared_input_leeter(QString name, QString value, bool is_replace)
{
	if (name == "lineEdit_ssid") {
		if (is_replace) {
			ui->lineEdit_ssid->backspace();
		}
		ui->lineEdit_ssid->insert(value);
	}
	else
		if (name == "lineEdit_pw") {
			if (is_replace) {
				ui->lineEdit_pw->backspace();
			}
			ui->lineEdit_pw->insert(value);
		}
		
}

//退格键
void CDlgWifiConfig::Infrared_input_backspace(QString name)
{
	if (name == "lineEdit_ssid") {
		ui->lineEdit_ssid->backspace();
	}
	else
		if (name == "lineEdit_pw") {
			ui->lineEdit_pw->backspace();
		}
		
}

void CDlgWifiConfig::SetConnectButtonState(std::wstring cstrSSID, bool state)
{
	QString msg;

	if (state) {
		msg = u8"断开";
	}
	else {
		msg = u8"连接";
	}

	//QMetaObject::invokeMethod(ui->pushButton_conn, "setText", Q_ARG(QString, msg));
	emit set_conn_button_text_sigle(msg);
}
