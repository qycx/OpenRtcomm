#include "CDlgCheck.h"
//
//#include <QDesktopWidget>
#include	<qscreen.h>
//
#include	<tchar.h>
#include	"qyMcMainCommon_qt.h"
#include <ctxQmc.h>
#include	<ctxQmc_sm.h>

#include <QTimer>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#include "NetworkMonitor.h"

#include <locale> 
#include <codecvt> 

#pragma comment(lib, "ws2_32.lib")

bool isPortOpen(const std::string& host, int port, int timeoutSeconds = 5) {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "WSAStartup failed" << std::endl;
		return false;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		WSACleanup();
		return false;
	}

	// 设置超时
	DWORD timeout = timeoutSeconds * 1000;
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);

	// 解析主机名
	if (inet_pton(AF_INET, host.c_str(), &serverAddr.sin_addr) != 1) {
		// 如果IP地址解析失败，尝试作为主机名解析
		hostent* he = gethostbyname(host.c_str());
		if (he == nullptr) {
			closesocket(sock);
			WSACleanup();
			return false;
		}
		serverAddr.sin_addr = *((in_addr*)he->h_addr);
	}

	// 尝试连接
	bool result = (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == 0);

	closesocket(sock);
	WSACleanup();

	return result;
}

CDlgCheck::CDlgCheck(const std::string& terminalIp, const std::string& mcuIp, QWidget *parent)
	: QDialog(parent),
	ui(new Ui::CDlgCheckClass)
{

	ui->setupUi(this);

	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

	sheetBackgroundImage();

	ui->btnOk->setEnabled(false);

	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(slot_btnOk_click()));
	connect(this, SIGNAL(to_returnMain_check_signal()), parent, SLOT(on_closeCheck_slots()));

	ui->listWidget_result->addItem(u8"正在检测请等待....");

	m_IPConflictChecker = new IPConflictChecker();


	//QTimer::singleShot(1000, this, [this, terminalIp, mcuIp]() {
	//	this->CheckIp(terminalIp, mcuIp);
	//	});

	NetworkMonitor monitor;
	int count = monitor.GetAdapterStatus();


	if (count <= 0) {
		QString tip = u8"未检测到已连接的网络，请检查";
		
		ui->listWidget_result->addItem(tip);
	}
	else {		

		QTimer::singleShot(200, this, [this, terminalIp]() {
			this->CheckIpTerminal(terminalIp);
			});

		QTimer::singleShot(200, this, [this, mcuIp]() {
			this->CheckIpMcu(mcuIp);
			});

		QTimer::singleShot(200, this, [this]() {
			this->CheckIpNvr();
			});

	}
	ui->btnOk->setEnabled(true);

	//错误提示
	ui->err_widget->setVisible(false);
}


void CDlgCheck::CheckIpTerminal(const std::string& terminalIp) {

	

	if (m_IPConflictChecker == nullptr) {
		return;
	}


	if (m_IPConflictChecker->CheckSpecificIP(terminalIp)) {
		QString tip = u8"检测到终端ip(";
		tip.append(terminalIp.c_str());
		tip.append(u8")与网络中其他机器存在冲突");
		ui->listWidget_result->addItem(tip);
	}
	else {
		QString tip = u8"终端ip(";
		tip.append(terminalIp.c_str());
		tip.append(u8")正常");
		ui->listWidget_result->addItem(tip);
	}


	
}

//下箭头
void CDlgCheck::Infrared_down()
{
	if (m_pInfraredMenu) {
		m_pInfraredMenu->Infrared_down();
		return;
	}
	this->focusNextPrevChild(true);

}
//上箭头
void CDlgCheck::Infrared_up()
{
	if (m_pInfraredMenu) {
		m_pInfraredMenu->Infrared_up();
		return;
	}
	this->focusNextPrevChild(false);
;
}


std::wstring
CDlgCheck::to_wstring(
	const std::string& str)
{
	return std::wstring_convert<
		std::codecvt_utf8<WCHAR>, WCHAR>().from_bytes(str);
}

bool CDlgCheck::pingIP(const std::string& ipAddress) {
	/*std::string command = "ping -n 1 -w 1000 " + ipAddress + " >nul 2>&1";
	int result = system(command.c_str());
	return (result == 0);*/

	return Ping(to_wstring(ipAddress));
}

bool CDlgCheck::Ping(const std::wstring& ipAddress, int timeout) {
	//std::wstring command = _T("ping -n 1 -w ") + std::to_wstring(timeout) +
	//	_T(" ") + ipAddress + _T(" >nul 2>&1");

	TCHAR cmdLine[256] = { '\0' };
	_sntprintf(cmdLine, sizeof(cmdLine), _T("cmd /c \"ping -n 1 -w %d %s >nul 2>&1\""), timeout, ipAddress.c_str());

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	ZeroMemory(&pi, sizeof(pi));

	BOOL success = CreateProcess(
		NULL,
		/*const_cast<LPWSTR>(command.c_str())*/cmdLine,
		NULL,
		NULL,
		FALSE,
		CREATE_NO_WINDOW,
		NULL,
		NULL,
		&si,
		&pi
	);

	if (!success) {
		return false;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);

	DWORD exitCode;
	GetExitCodeProcess(pi.hProcess, &exitCode);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return (exitCode == 0);
}


void CDlgCheck::CheckIpMcu(const std::string& mcuIp) {


	if (m_IPConflictChecker == nullptr) {
		return;
	}
	
	if (m_IPConflictChecker->CheckSpecificIP(mcuIp)) {
		QString tip = u8"检测 MCU ip(";
		tip.append(mcuIp.c_str());
		tip.append(u8")正常");
		ui->listWidget_result->addItem(tip);

		if (pingIP(mcuIp)) {
			tip = u8"Ping MCU ip(";
			tip.append(mcuIp.c_str());
			tip.append(u8")是联通的");
			ui->listWidget_result->addItem(tip);

			if (isPortOpen(mcuIp, 8768)) {
				tip = u8"检测 MCU (";
				tip.append(mcuIp.c_str());
				tip.append(u8")服务已启动");
				ui->listWidget_result->addItem(tip);
			}
			else {
				tip = u8"检测 MCU (";
				tip.append(mcuIp.c_str());
				tip.append(u8")服务未启动");
				ui->listWidget_result->addItem(tip);
			}

		}
		else {
			tip = u8"Ping MCU ip(";
			tip.append(mcuIp.c_str());
			tip.append(u8")不联通");
			ui->listWidget_result->addItem(tip);
		}
	}
	else {
		QString tip = u8"检测 MCU ip(";
		tip.append(mcuIp.c_str());
		tip.append(u8")不存在或无法连通");
		ui->listWidget_result->addItem(tip);
	}

	
}


void CDlgCheck::CheckIpNvr() {

	if (m_IPConflictChecker == nullptr) {
		return;
	}


	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (pProcInfo) {
		if (pProcInfo->cfg.ipcProcInitCfg.m_bEnableIpc) {

			if (m_IPConflictChecker->CheckSpecificIP(pProcInfo->cfg.ipcProcInitCfg.nvrIp)) {
				QString tip = u8"检测 NVR ip(";
				tip.append(pProcInfo->cfg.ipcProcInitCfg.nvrIp);
				tip.append(u8")正常");
				ui->listWidget_result->addItem(tip);

				if (pingIP(pProcInfo->cfg.ipcProcInitCfg.nvrIp)) {
					tip = u8"Ping NVR ip(";
					tip.append(pProcInfo->cfg.ipcProcInitCfg.nvrIp);
					tip.append(u8")是联通的");
					ui->listWidget_result->addItem(tip);
				}
				else {
					tip = u8"Ping NVR ip(";
					tip.append(pProcInfo->cfg.ipcProcInitCfg.nvrIp);
					tip.append(u8")不联通");
					ui->listWidget_result->addItem(tip);
				}
			}
			else {
				QString tip = u8"检测 NVR ip(";
				tip.append(pProcInfo->cfg.ipcProcInitCfg.nvrIp);
				tip.append(u8")不存在或无法连通");
				ui->listWidget_result->addItem(tip);
			}

		}
		else {
			QString tip = u8"检测 NVR 未启用";
			ui->listWidget_result->addItem(tip);
		}

	}

	
}


void CDlgCheck::CheckIp(const std::string& terminalIp, const std::string& mcuIp) {

	m_IPConflictChecker = new IPConflictChecker();

	if (m_IPConflictChecker == nullptr) {
		return;
	}

	//QListWidget* listWidget = new QListWidget(this);

	

	if (m_IPConflictChecker->CheckSpecificIP(terminalIp)) {
		QString tip = u8"检测终端ip(";
		tip.append(terminalIp.c_str());
		tip.append(u8")冲突");
		ui->listWidget_result->addItem(tip);
	}
	else {
		QString tip = u8"检测终端ip(";
		tip.append(terminalIp.c_str());
		tip.append(u8")正常");
		ui->listWidget_result->addItem(tip);
	}

	if (m_IPConflictChecker->CheckSpecificIP(mcuIp)) {
		QString tip = u8"检测 MCU ip(";
		tip.append(mcuIp.c_str());
		tip.append(u8")正常");
		ui->listWidget_result->addItem(tip);
	}
	else {
		QString tip = u8"检测 MCU ip(";
		tip.append(mcuIp.c_str());
		tip.append(u8")不存在或无法连通");
		ui->listWidget_result->addItem(tip);
	}

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (pProcInfo) {
		if (pProcInfo->cfg.ipcProcInitCfg.m_bEnableIpc) {

			if (m_IPConflictChecker->CheckSpecificIP(pProcInfo->cfg.ipcProcInitCfg.nvrIp)) {
				QString tip = u8"检测 NVR ip(";
				tip.append(pProcInfo->cfg.ipcProcInitCfg.nvrIp);
				tip.append(u8")正常");
				ui->listWidget_result->addItem(tip);
			}
			else {
				QString tip = u8"检测 NVR ip(";
				tip.append(pProcInfo->cfg.ipcProcInitCfg.nvrIp);
				tip.append(u8")不存在或无法连通");
				ui->listWidget_result->addItem(tip);
			}

		}
		else {
			QString tip = u8"检测 NVR 未启用";
			ui->listWidget_result->addItem(tip);
		}

	}


}

//样式

void CDlgCheck::sheetBackgroundImage()
{
	QRect rc = QApplication::primaryScreen()->geometry();

	if (rc.width() > 3500) {
		resize(2000, 1100);

		ui->widget->setStyleSheet("background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");
		ui->label_t1->setStyleSheet("border-bottom:5px solid  #fff;font-size:85px;color:#fff;font-family: Microsoft YaHei;");
	
		ui->err_txt->setStyleSheet("font-size:32px;color:red");

		ui->btnOk->setStyleSheet("QPushButton{font-size:64px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		ui->btnOk->setFixedHeight(140);
		ui->btnOk->setFixedWidth(430);

	}
	else {
		ui->widget->setStyleSheet("background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");
		ui->label_t1->setStyleSheet("border-bottom:5px solid  #fff;font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		
		ui->err_txt->setStyleSheet("font-size:18px;color:red");

		ui->btnOk->setStyleSheet("QPushButton{font-size:32px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		ui->btnOk->setFixedHeight(65);
		ui->btnOk->setFixedWidth(200);

	}

}

void CDlgCheck::infraredMenu_quit()
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

//按确认键
void CDlgCheck::slot_btnOk_click() 
{
	emit to_returnMain_check_signal();
}


CDlgCheck::~CDlgCheck()
{
	if (m_pInfraredMenu)
	{
		delete m_pInfraredMenu;
		m_pInfraredMenu = nullptr;
	}


}




