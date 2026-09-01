#include "CDlgNvrConfig.h"

//#include <QDesktopWidget>
#include	<qscreen.h>
#include	<tchar.h>
#include	"qyMcMainCommon_qt.h"
#include <ctxQmc.h>
#include	<ctxQmc_sm.h>



CDlgNvrConfig::CDlgNvrConfig(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::CDlgNvrConfigClass)
{

	ui->setupUi(this);


	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

	connect(ui->boxNvrEna, SIGNAL(stateChanged(int)), this, SLOT(slot_boxNvrEna_change(int)));
	connect(ui->boxNvrDh, SIGNAL(stateChanged(int)), this, SLOT(slot_boxNvrDh_click(int)));
	connect(ui->boxNvrHik, SIGNAL(stateChanged(int)), this, SLOT(slot_boxNvrHik_click(int)));
	connect(ui->boxNvrD4k, SIGNAL(stateChanged(int)), this, SLOT(slot_boxNvrD4k_click(int)));

	connect(this, SIGNAL(to_returnMain_nvr_signal()), parent, SLOT(on_closeNvr_slots()));
	
	connect(ui->boxNvrDh, &QRadioButton::clicked, this, &CDlgNvrConfig::slot_mouse_boxNvrDh_click);
	connect(ui->boxNvrHik, &QRadioButton::clicked, this, &CDlgNvrConfig::slot_mouse_boxNvrHik_click);
	connect(ui->boxNvrD4k, &QRadioButton::clicked, this, &CDlgNvrConfig::slot_mouse_boxNvrD4k_click);
	connect(ui->boxNvrEna, &QCheckBox::clicked, this,&CDlgNvrConfig::slot_mouse_boxNvrEna_click);

	//nvr按钮点击事件
	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(slot_btnOk_click()));


	sheetBackgroundImage();

	//初始化复选框状态
	initBoxStatus();

	//错误提示
	ui->err_widget->setVisible(false);
}

//样式
void CDlgNvrConfig::sheetBackgroundImage()
{
	QRect rc = QApplication::primaryScreen()->geometry();

	if (rc.width() > 3500) {
		resize(2000, 1100);

		ui->widget->setStyleSheet("background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");
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

	}
	else {
		ui->widget->setStyleSheet("background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");
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
		
	}

}



//初始化数据
void CDlgNvrConfig::initBoxStatus()
{

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		//
		ui->boxNvrEna->setStyleSheet("QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

		//
		ui->boxNvrDh->setStyleSheet("QRadioButton::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
		ui->boxNvrD4k->setStyleSheet("QRadioButton::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
		ui->boxNvrHik->setStyleSheet("QRadioButton::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

	}
	else {
		//
		ui->boxNvrEna->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

		//
		ui->boxNvrDh->setStyleSheet("QRadioButton::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
		ui->boxNvrD4k->setStyleSheet("QRadioButton::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
		ui->boxNvrHik->setStyleSheet("QRadioButton::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

		
	}

	//
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();


	//
	Qt::CheckState state;
	
	state = pProcInfo->cfg.ipcProcInitCfg.m_bEnableIpc ? Qt::Checked : Qt::Unchecked ;
	ui->boxNvrEna->setCheckState(state);


	_nvr_enable = pProcInfo->cfg.ipcProcInitCfg.m_bEnableIpc;

	IpcProcInitCfg ipic = { 0 };
	if (!bGetIpcProcInitCfg(pQyMc->cfg.ipcProcInitFile, &ipic)) {
		memset(&ipic, 0, sizeof(ipic));
	}




	//ui->boxNvrDh->setCheckState(Qt::Checked);
	if (ipic.m_iNvrType == Nvr_type_d4k) {
		//ui->boxNvrD4k->setChecked(true);
		//ui->boxNvrDh->setChecked(false);

		ui->boxNvrHik->setChecked(false);
		ui->boxNvrHik->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		ui->boxNvrDh->setChecked(false);
		ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		ui->boxNvrD4k->setChecked(true);
		ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
	}else if (ipic.m_iNvrType == Nvr_type_hik) {
		//ui->boxNvrD4k->setChecked(true);
		//ui->boxNvrDh->setChecked(false);
		ui->boxNvrD4k->setChecked(false);
		ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		ui->boxNvrDh->setChecked(false);
		ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		ui->boxNvrHik->setChecked(true);
		ui->boxNvrHik->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
	}
	else {
		//ui->boxNvrDh->setChecked(true);
		//ui->boxNvrD4k->setChecked(false);

		ui->boxNvrDh->setChecked(true);
		ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
		ui->boxNvrD4k->setChecked(false);
		ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		ui->boxNvrHik->setChecked(false);
		ui->boxNvrHik->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
	}

	//
	ui->NvrIp->setText(QString::fromUtf8((const char*)ipic.nvrIp));
	ui->NvrName->setText(QString::fromWCharArray(ipic.nvrUsr));
	ui->NvrPwd->setText(QString::fromUtf8((const char*)ipic.nvrPwd));
	

	//if (pProcInfo->cfg.ipcProcInitCfg.m_iNvrType == 1) {
	//	ui->boxNvrDh->setCheckState(Qt::Checked);
	//}
	//else {
	//	ui->boxNvrDh->setCheckState(Qt::Unchecked);
	//}
}


//监听nvr选项开启
void CDlgNvrConfig::slot_boxNvrEna_change(int box_change)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (box_change == 0)
	{
		//未选
		int aaa = 1;
		_nvr_enable = false;


	}
	else if (box_change == 2)
	{
		//已选
		int aaa = 1;
		_nvr_enable = true;
	}
}


//监听 boxNvrDh复选框选中状态
void CDlgNvrConfig::slot_boxNvrDh_change(int box_change)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (box_change == 0)
	{
		//未选
		int aaa = 1;

	}
	else if (box_change == 2)
	{
		//已选
		int aaa = 1;
	}
}


//遥控器按下 大华设备勾选
void CDlgNvrConfig::slot_boxNvrDh_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";


	//

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		ui->boxNvrDh->setChecked(true);
		ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
		ui->boxNvrD4k->setChecked(false);
		ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		ui->boxNvrHik->setChecked(false);
		ui->boxNvrHik->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");

		/*
		if (ui->boxNvrDh->isChecked())
		{
			//ui->boxNvrDh->setCheckState(Qt::Unchecked);
			ui->boxNvrDh->setChecked(false);			
			ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			ui->boxNvrD4k->setChecked(true);
			ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
}
		else {
			//ui->boxNvrDh->setCheckState(Qt::Checked);
			ui->boxNvrDh->setChecked(true);
			ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			ui->boxNvrD4k->setChecked(false);
			ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			}
			*/
	}
	else {
		ui->boxNvrDh->setChecked(true);
		ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
		ui->boxNvrD4k->setChecked(false);
		ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		ui->boxNvrHik->setChecked(false);
		ui->boxNvrHik->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");

		/*
		if (ui->boxNvrDh->isChecked())
		{
			//ui->boxNvrDh->setCheckState(Qt::Unchecked);
			ui->boxNvrDh->setChecked(false);
			ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			ui->boxNvrD4k->setChecked(true);			
			ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			
		}
		else {
			//ui->boxNvrDh->setCheckState(Qt::Checked);
			ui->boxNvrDh->setChecked(true);
			ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			ui->boxNvrD4k->setChecked(false);			
			ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			}
			*/
	}

}

//遥控器按下 Hik设备勾选
void CDlgNvrConfig::slot_boxNvrHik_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";
	
	//
	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {

		ui->boxNvrHik->setChecked(true);
		ui->boxNvrHik->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");

		ui->boxNvrD4k->setChecked(false);
		ui->boxNvrDh->setChecked(false);
		ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
	
	}
	else {
		ui->boxNvrHik->setChecked(true);
		ui->boxNvrHik->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");

		ui->boxNvrD4k->setChecked(false);
		ui->boxNvrDh->setChecked(false);
		ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");

		
	}

}

//遥控器按下 D4k设备勾选
void CDlgNvrConfig::slot_boxNvrD4k_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";


	//

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {

		ui->boxNvrD4k->setChecked(true);
		ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
		ui->boxNvrDh->setChecked(false);
		ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		ui->boxNvrHik->setChecked(false);
		ui->boxNvrHik->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		
		/*
		if (ui->boxNvrD4k->isChecked())
		{
			//ui->boxNvrD4k->setCheckState(Qt::Unchecked);
			ui->boxNvrD4k->setChecked(false);
			ui->boxNvrDh->setChecked(true);
			ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		}
		else {
			//ui->boxNvrD4k->setCheckState(Qt::Checked);
			ui->boxNvrD4k->setChecked(true);
			ui->boxNvrDh->setChecked(false);
			ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
		}
		*/
	}
	else {
		ui->boxNvrD4k->setChecked(true);
		ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
		ui->boxNvrDh->setChecked(false);
		ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		ui->boxNvrHik->setChecked(false);
		ui->boxNvrHik->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
		
		/*
		if (ui->boxNvrD4k->isChecked())
		{
			//ui->boxNvrD4k->setCheckState(Qt::Unchecked);
			ui->boxNvrD4k->setChecked(false);
			ui->boxNvrDh->setChecked(true);
			ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");

		}
		else {
			//ui->boxNvrD4k->setCheckState(Qt::Checked);
			ui->boxNvrD4k->setChecked(true);
			ui->boxNvrDh->setChecked(false);
			ui->boxNvrDh->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			ui->boxNvrD4k->setStyleSheet("QRadioButton{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QRadioButton:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QRadioButton::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
		}
		*/
	}

}

//遥控器按下 开启NVR
void CDlgNvrConfig::slot_boxNvrEna_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		if (ui->boxNvrEna->isChecked())
		{
			ui->boxNvrEna->setCheckState(Qt::Unchecked);
			ui->boxNvrEna->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			//
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭HDMI1 OUT端口";
		}
		else {
			ui->boxNvrEna->setCheckState(Qt::Checked);
			ui->boxNvrEna->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭HDMI1 OUT端口"), false);

			//log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启HDMI1 OUT端口";
		}
	}
	else {
		if (ui->boxNvrEna->isChecked())
		{
			ui->boxNvrEna->setCheckState(Qt::Unchecked);
			ui->boxNvrEna->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");

			//
			//qmcLogForHg(0, (TCHAR*)_T("终端开启HDMI1 OUT端口"), false);
//			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭HDMI1 OUT端口";

		}
		else {
			ui->boxNvrEna->setCheckState(Qt::Checked);
			ui->boxNvrEna->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭HDMI1 OUT端口"), false);
			//log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启HDMI1 OUT端口";
		}
	}
	//qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

}

//鼠标按下 大华选项
void CDlgNvrConfig::slot_mouse_boxNvrDh_click(bool checked) {
	slot_boxNvrDh_click("boxNvrDh");
}
//鼠标按下 海康选项
void CDlgNvrConfig::slot_mouse_boxNvrHik_click(bool checked) {
	slot_boxNvrHik_click("boxNvrHik");
}
//鼠标按下 4k选项
void CDlgNvrConfig::slot_mouse_boxNvrD4k_click(bool checked) {
	slot_boxNvrD4k_click("boxNvrD4k");
}

//鼠标按下 是否开启nvr
void CDlgNvrConfig::slot_mouse_boxNvrEna_click(bool checked) {

	//slot_boxNvrEna_click("boxNvrEna");

}



//按确认键
void CDlgNvrConfig::slot_btnOk_click() 
{
	//是否开启nvr
	_nvr_enable;
	//接收大华 先写死
	int nvr_type = Nvr_type_dh;

	if (ui->boxNvrD4k->isChecked()) {
		nvr_type = Nvr_type_d4k;
	}
	else if (ui->boxNvrHik->isChecked()) {
		nvr_type = Nvr_type_hik;
	}

	// 接收nvr IP
	QString nvrIp = ui->NvrIp->text();
	//接收 nvr  username
	QString nvrUsername = ui->NvrName->text();
	//接收 nvr password
	QString nvrPwd = ui->NvrPwd->text();
	

	//
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();


	IpcProcInitCfg ipic = { 0 };
	memset(&ipic, 0, sizeof(ipic));

	//
	char  buf[256];
	TCHAR  tBuf[256];
	
	
	//
	safeStrnCpy(nvrIp.toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (_nvr_enable) {
		if (!bIpValid(buf)) {

			//
			ui->err_txt->setText(u8"NVR IP地址输入无效，\n有效格式 xxx.xxx.xxx.xxx！");
			ui->err_widget->setVisible(true);
			//
			ui->NvrIp->setFocus();

			return;
		}
	}

	safeStrnCpy(buf, ipic.nvrIp, mycountof(ipic.nvrIp));
	
	
	//
	QByteArray ba = nvrUsername.toUtf8();
	char* data = ba.data(); //以上两步不能直接简化为“char *data = str.toUtf8().data();”
	int charLen = strlen(data);
	int len = MultiByteToWideChar(CP_ACP, 0, data, charLen, NULL, 0);
	TCHAR* tmp_buf = new TCHAR[len + 1];
	MultiByteToWideChar(CP_ACP, 0, data, charLen, tmp_buf, len);
	tmp_buf[len] = '\0';




	safeTcsnCpy(tmp_buf, tBuf, mycountof(tBuf));
	tTrim(tBuf);
	if (_nvr_enable) {
		if (!tBuf[0]) {

			//
			ui->err_txt->setText(u8"NVR用户名输入无效！");
			ui->err_widget->setVisible(true);
			//
			ui->NvrName->setFocus();

			return;
		}
	}
	

	//char char_fake_devLoginName[256];

	//myTChar2Utf8(char_fake_devLoginName, initCfg.fake_devLoginName, mycountof(initCfg.fake_devLoginName));

	safeTcsnCpy(tBuf, ipic.nvrUsr, mycountof(ipic.nvrUsr));

	//
	safeStrnCpy(nvrPwd.toUtf8().data(), buf, mycountof(buf));
	trim(buf);
	if (_nvr_enable) {
		if (!buf[0]) {

			//
			ui->err_txt->setText(u8"NVR密码输入无效！");
			ui->err_widget->setVisible(true);
			//
			ui->NvrPwd->setFocus();

			return;
		}
	}
	
	safeStrnCpy(buf, ipic.nvrPwd, mycountof(ipic.nvrPwd));







	//
	ipic.m_iNvrType = nvr_type;
	//
	ipic.m_bEnableIpc = _nvr_enable;


	//
	if (memcmp(&ipic, &pProcInfo->cfg.ipcProcInitCfg, sizeof(ipic))) {
		if (saveSmIpicInitCfg(&ipic, pQyMc->cfg.ipcProcInitFile)) {

			
			
			//
			ui->err_txt->setText(u8"保存失败");
			ui->err_widget->setVisible(true);
			//
			return;
		}
	}



	//
	bGetIpcProcInitCfg(pQyMc->cfg.ipcProcInitFile, &pProcInfo->cfg.ipcProcInitCfg);

	int ii = 0;

	emit to_returnMain_nvr_signal();
}


CDlgNvrConfig::~CDlgNvrConfig()
{
	if (m_pInfraredMenu)
	{
		delete m_pInfraredMenu;
		m_pInfraredMenu = nullptr;
	}


}

//菜单关闭
void CDlgNvrConfig::infraredMenu_quit()
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
void CDlgNvrConfig::Infrared_down()
{
	if (m_pInfraredMenu) {
		m_pInfraredMenu->Infrared_down();
		return;
	}
	this->focusNextPrevChild(true);
	ui->NvrIp->deselect();
	ui->NvrName->deselect();
	ui->NvrPwd->deselect();
}
//上箭头
void CDlgNvrConfig::Infrared_up()
{
	if (m_pInfraredMenu) {
		m_pInfraredMenu->Infrared_up();
		return;
	}
	this->focusNextPrevChild(false);
	ui->NvrIp->deselect();
	ui->NvrName->deselect();
	ui->NvrPwd->deselect();
}

//左右光标移动
void CDlgNvrConfig::Infrared_input_left_right(QString name, bool isLeft)
{


	if (isLeft) {
		if (name == "NvrIp") {
			int cur_index = ui->NvrIp->cursorPosition();
			ui->NvrIp->setCursorPosition(cur_index - 1);
			//ui->NvrPwd->cursorBackward(true);
		}
		else
			if (name == "NvrName") {
				int cur_index = ui->NvrName->cursorPosition();
				ui->NvrName->setCursorPosition(cur_index - 1);
				//ui->NvrPwd->cursorBackward(true);
			}
			else
				if (name == "NvrPwd") {
					int cur_index = ui->NvrPwd->cursorPosition();
					ui->NvrPwd->setCursorPosition(cur_index - 1);
					//ui->NvrPwd->cursorBackward(true);
				}
				else if (name == "boxNvrD4k") {
					//ui->boxNvrDh->focusWidget();
					ui->boxNvrHik->setFocus();
					ui->boxNvrDh->clearFocus();
					ui->boxNvrD4k->clearFocus();

				}
				else if (name == "boxNvrHik") {
					//ui->boxNvrDh->focusWidget();
					ui->boxNvrHik->clearFocus();
					ui->boxNvrDh->setFocus();
					ui->boxNvrD4k->clearFocus();

				}


	}
	else {
		if (name == "NvrIp") {
			int cur_index = ui->NvrIp->cursorPosition();
			ui->NvrIp->setCursorPosition(cur_index + 1);
			//ui->NvrPwd->cursorForward(true);
		}
		else
			if (name == "NvrName") {
				int cur_index = ui->NvrName->cursorPosition();
				ui->NvrName->setCursorPosition(cur_index + 1);
				//ui->NvrPwd->cursorForward(true);
			}
			else
		if (name == "NvrPwd") {
			int cur_index = ui->NvrPwd->cursorPosition();
			ui->NvrPwd->setCursorPosition(cur_index + 1);
			//ui->NvrPwd->cursorForward(true);
		}
		else if (name == "boxNvrDh") {
			//ui->boxNvrD4k->focusWidget();
			ui->boxNvrHik->setFocus();
			ui->boxNvrD4k->clearFocus();
			ui->boxNvrDh->clearFocus();

		}
		else if (name == "boxNvrHik") {
			//ui->boxNvrD4k->focusWidget();
			ui->boxNvrHik->clearFocus();
			ui->boxNvrD4k->setFocus();
			ui->boxNvrDh->clearFocus();

		}
	}
}


//表单输入
void CDlgNvrConfig::Infrared_input(QString name, QString value)
{
	if (name == "NvrIp") {
		//QString tmp_str = ui->NvrPwd->text();
		ui->NvrIp->insert(value);
	}
	else
		if (name == "NvrName") {
			//QString tmp_str = ui->NvrPwd->text();
			ui->NvrName->insert(value);
		}
		else
			if (name == "NvrPwd") {
				//QString tmp_str = ui->NvrPwd->text();
				ui->NvrPwd->insert(value);
			}
}

//表单输入字母
void CDlgNvrConfig::Infrared_input_leeter(QString name, QString value, bool is_replace)
{
	if (name == "NvrIp") {
		if (is_replace) {
			ui->NvrIp->backspace();
		}
		ui->NvrIp->insert(value);
	}
	else
		if (name == "NvrName") {
			if (is_replace) {
				ui->NvrName->backspace();
			}
			ui->NvrName->insert(value);
		}
		else
			if (name == "NvrPwd") {
				if (is_replace) {
					ui->NvrPwd->backspace();
				}
				ui->NvrPwd->insert(value);
			}
}

//退格键
void CDlgNvrConfig::Infrared_input_backspace(QString name)
{
	if (name == "NvrIp") {
		ui->NvrIp->backspace();
	}
	else
		if (name == "NvrName") {
			ui->NvrName->backspace();
		}
		else
			if (name == "NvrPwd") {
				ui->NvrPwd->backspace();
			}
}
