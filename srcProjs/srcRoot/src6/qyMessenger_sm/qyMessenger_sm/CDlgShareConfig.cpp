#include "CDlgShareConfig.h"

//#include <QDesktopWidget>
#include	<qscreen.h>
//
#include	<tchar.h>
#include	"qyMcMainCommon_qt.h"
#include <ctxQmc.h>
#include	<ctxQmc_sm.h>

#include <regex>
#include <string>

//bool validateRtspUrl(const std::string& url) {
//	std::regex rtspRegex(R"(^rtsp://([^:]+):([^@]+)@([^/]+)(/.*)?$)");
//	return std::regex_match(url, rtspRegex);
//}

bool validateRtspUrl(const std::string& url, bool& hasCredentials) {
	// 定义 RTSP URL 的正则表达式
	std::regex rtspRegex(R"(^rtsp://(?:([^:@/]+):([^@/]+)@)?([^:/]+)(?::(\d+))?(/.*)$)");
	std::smatch match;

	// 检查 URL 是否匹配正则表达式
	if (std::regex_search(url, match, rtspRegex)) {
		// 判断是否包含用户名和密码
		hasCredentials = match[1].length() > 0 && match[2].length() > 0;
		return true;
	}
	return false;
}


CDlgShareConfig::CDlgShareConfig(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::CDlgShareConfigClass())
{
	ui->setupUi(this);


	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

	connect(ui->boxEnableShare, SIGNAL(stateChanged(int)), this, SLOT(slot_boxEnableShare_change(int)));
	connect(ui->boxAutoShare, SIGNAL(stateChanged(int)), this, SLOT(slot_boxAutoShare_change(int)));
	connect(this, SIGNAL(to_returnMain_share_signal()), parent, SLOT(on_closeShare_slots()));	
	connect(ui->boxAutoShare, &QCheckBox::clicked, this, &CDlgShareConfig::slot_mouse_boxAutoShare_click);
	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(slot_btnOk_click()));

	sheetBackgroundImage();

	//初始化复选框状态
	initBoxStatus();

	//错误提示
	ui->err_widget->setVisible(false);
}

CDlgShareConfig::~CDlgShareConfig()
{
	delete ui;

	if (m_pInfraredMenu)
	{
		delete m_pInfraredMenu;
		m_pInfraredMenu = nullptr;
	}
}


void CDlgShareConfig::slot_boxEnableShare_change(int box_change)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (box_change == 0)
	{
		//未选
		_enable_share = false;


	}
	else if (box_change == 2)
	{
		//已选
		_enable_share = true;
	}
}

void CDlgShareConfig::slot_boxAutoShare_change(int box_change)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (box_change == 0)
	{
		//未选
		int aaa = 1;
		_auto_share = false;


	}
	else if (box_change == 2)
	{
		//已选
		int aaa = 1;
		_auto_share = true;
	}
}

void CDlgShareConfig::sheetBackgroundImage()
{
	QRect rc = QApplication::primaryScreen()->geometry();

	if (rc.width() > 3500) {
		resize(2000, 1100);

		ui->widget->setStyleSheet("background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");
		ui->label_t1->setStyleSheet("border-bottom:5px solid  #fff;font-size:85px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t2->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t3->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t4->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");

		ui->boxEnableShare->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxAutoShare->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");

		ui->err_txt->setStyleSheet("font-size:32px;color:red");

		ui->btnOk->setStyleSheet("QPushButton{font-size:64px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		ui->btnOk->setFixedHeight(140);
		ui->btnOk->setFixedWidth(430);

	}
	else {
		ui->widget->setStyleSheet("background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");
		ui->label_t1->setStyleSheet("border-bottom:5px solid  #fff;font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t2->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t3->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t4->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");

		ui->boxEnableShare->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxAutoShare->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");

		ui->rtspUrl->setStyleSheet("QLineEdit{padding-left:15px;font-family: Microsoft YaHei;background:#1E3C75;color:#fff;font-size:28px;border-radius:10px;}QLineEdit:focus{background:#102145;color:#fff;border-radius:10px;border:2px solid #fff;}");

		ui->err_txt->setStyleSheet("font-size:18px;color:red");

		ui->btnOk->setStyleSheet("QPushButton{font-size:32px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		ui->btnOk->setFixedHeight(65);
		ui->btnOk->setFixedWidth(200);

	}

}


//初始化数据
void CDlgShareConfig::initBoxStatus()
{

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		//

		ui->boxEnableShare->setStyleSheet("QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
		ui->boxAutoShare->setStyleSheet("QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

			
	}
	else {
		//
		ui->boxEnableShare->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
		ui->boxAutoShare->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

	}

	//
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();


	Qt::CheckState state;

	state = pProcInfo->cfg.shareProcInitCfg.m_bEnableShare ? Qt::Checked : Qt::Unchecked;
	ui->boxEnableShare->setCheckState(state);



	state = pProcInfo->cfg.shareProcInitCfg.m_bAutoShare ? Qt::Checked : Qt::Unchecked;
	ui->boxAutoShare->setCheckState(state);

	_auto_share = pProcInfo->cfg.shareProcInitCfg.m_bAutoShare;


	state = pProcInfo->cfg.shareProcInitCfg.m_bEnableShare ? Qt::Checked : Qt::Unchecked;
	ui->boxEnableShare->setCheckState(state);

	_enable_share = pProcInfo->cfg.shareProcInitCfg.m_bEnableShare;



	ShareProcInitCfg ipic = { 0 };
	if (!bGetShareProcInitCfg(pQyMc->cfg.shareProcInitFile, &ipic)) {
		memset(&ipic, 0, sizeof(ipic));
	}	

	//
	ui->rtspUrl->setText(QString::fromUtf8((const char*)ipic.rtspUrl));

}

void CDlgShareConfig::slot_mouse_boxAutoShare_click(bool checked) {

	//slot_boxAutoShare_click("boxAutoShare");

}

void CDlgShareConfig::slot_boxEnableShare_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		if (ui->boxEnableShare->isChecked())
		{
			ui->boxEnableShare->setCheckState(Qt::Unchecked);
			ui->boxEnableShare->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			//
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭HDMI1 OUT端口";
		}
		else {
			ui->boxEnableShare->setCheckState(Qt::Checked);
			ui->boxEnableShare->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭HDMI1 OUT端口"), false);

			//log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启HDMI1 OUT端口";
		}
	}
	else {
		if (ui->boxEnableShare->isChecked())
		{
			ui->boxEnableShare->setCheckState(Qt::Unchecked);
			ui->boxEnableShare->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");

			//
			//qmcLogForHg(0, (TCHAR*)_T("终端开启HDMI1 OUT端口"), false);
//			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭HDMI1 OUT端口";

		}
		else {
			ui->boxEnableShare->setCheckState(Qt::Checked);
			ui->boxEnableShare->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭HDMI1 OUT端口"), false);
			//log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启HDMI1 OUT端口";
		}
	}
	//qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

}

//按确认键
void CDlgShareConfig::slot_btnOk_click()
{

	//_auto_share;	

	
	QString rtspUrl = ui->rtspUrl->text();

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
		if (!validateRtspUrl(buf, hasCredentials)) {

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
	
	int ii = 0;

	emit to_returnMain_share_signal();
}




//菜单关闭
void CDlgShareConfig::infraredMenu_quit()
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
void CDlgShareConfig::Infrared_down()
{
	if (m_pInfraredMenu) {
		m_pInfraredMenu->Infrared_down();
		return;
	}
	this->focusNextPrevChild(true);
	ui->rtspUrl->deselect();
	
}
//上箭头
void CDlgShareConfig::Infrared_up()
{
	if (m_pInfraredMenu) {
		m_pInfraredMenu->Infrared_up();
		return;
	}
	this->focusNextPrevChild(false);
	ui->rtspUrl->deselect();

}

//左右光标移动
void CDlgShareConfig::Infrared_input_left_right(QString name, bool isLeft)
{


	if (isLeft) {
		if (name == "rtspUrl") {
			int cur_index = ui->rtspUrl->cursorPosition();
			ui->rtspUrl->setCursorPosition(cur_index - 1);
		
		}	


	}
	else {
		if (name == "rtspUrl") {
			int cur_index = ui->rtspUrl->cursorPosition();
			ui->rtspUrl->setCursorPosition(cur_index + 1);

		}
		
	}
}


//表单输入
void CDlgShareConfig::Infrared_input(QString name, QString value)
{
	if (name == "rtspUrl") {
		ui->rtspUrl->insert(value);
	}
	
}

//表单输入字母
void CDlgShareConfig::Infrared_input_leeter(QString name, QString value, bool is_replace)
{
	if (name == "rtspUrl") {
		if (is_replace) {
			ui->rtspUrl->backspace();
		}
		ui->rtspUrl->insert(value);
	}
	
}

//退格键
void CDlgShareConfig::Infrared_input_backspace(QString name)
{
	if (name == "rtspUrl") {
		ui->rtspUrl->backspace();
	}
	
}


void CDlgShareConfig::slot_boxAutoShare_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		if (ui->boxAutoShare->isChecked())
		{
			ui->boxAutoShare->setCheckState(Qt::Unchecked);
			ui->boxAutoShare->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			//
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭HDMI1 OUT端口";
		}
		else {
			ui->boxAutoShare->setCheckState(Qt::Checked);
			ui->boxAutoShare->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭HDMI1 OUT端口"), false);

			//log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启HDMI1 OUT端口";
		}
	}
	else {
		if (ui->boxAutoShare->isChecked())
		{
			ui->boxAutoShare->setCheckState(Qt::Unchecked);
			ui->boxAutoShare->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");

			//
			//qmcLogForHg(0, (TCHAR*)_T("终端开启HDMI1 OUT端口"), false);
//			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭HDMI1 OUT端口";

		}
		else {
			ui->boxAutoShare->setCheckState(Qt::Checked);
			ui->boxAutoShare->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭HDMI1 OUT端口"), false);
			//log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启HDMI1 OUT端口";
		}
	}
	//qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

}