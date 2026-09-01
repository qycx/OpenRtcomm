#include "CDlgPortSetting.h"
//
//#include <QDesktopWidget>
#include	<qscreen.h>
//
#include	<tchar.h>
#include	"qyMcMainCommon_qt.h"
#include <ctxQmc.h>
#include	<ctxQmc_sm.h>


//
CDlgPortSetting::CDlgPortSetting(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::CDlgPortSettingClass)
{
	ui->setupUi(this);

	
	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);


	sheetBackgroundImage();

	//初始化复选框状态
	initBoxStatus();


	connect(this, SIGNAL(to_returnMain_signal()), parent, SLOT(on_closePortSetting_slots()));

	connect(ui->boxVga, SIGNAL(stateChanged(int)), this, SLOT(slot_boxVga_change(int)));
	connect(ui->boxHdmi, SIGNAL(stateChanged(int)), this, SLOT(slot_boxHdmi_change(int)));
	connect(ui->boxDvi, SIGNAL(stateChanged(int)), this, SLOT(slot_boxDvi_change(int)));
	connect(ui->boxUsb1, SIGNAL(stateChanged(int)), this, SLOT(slot_boxUsb1_change(int)));
	connect(ui->boxUsb2, SIGNAL(stateChanged(int)), this, SLOT(slot_boxUsb2_change(int)));
	connect(ui->boxUsb3, SIGNAL(stateChanged(int)), this, SLOT(slot_boxUsb3_change(int)));
	connect(ui->boxLan, SIGNAL(stateChanged(int)), this, SLOT(slot_boxLan_change(int)));
	connect(ui->boxAudioOut, SIGNAL(stateChanged(int)), this, SLOT(slot_boxAudioOut_change(int)));

	ui->boxVga->setFocus();

}


// hdmi in
//监听vga复选框选中状态
void CDlgPortSetting::slot_boxVga_change(int box_change)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (box_change == 0)
	{
		//未选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_hdmiIn_vga = true;

	}
	else if (box_change == 2)
	{
		//已选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_hdmiIn_vga = false;
	}
}

// hdmi 2 out
//监听DVI复选框选中状态
void CDlgPortSetting::slot_boxDvi_change(int box_change)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (box_change == 0)
	{
		//未选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_hdmi2Out_dvi = true;

	}
	else if (box_change == 2)
	{
		//已选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_hdmi2Out_dvi = false;
	}
}

// hdmi 1 out
//监听HDMI复选框选中状态
void CDlgPortSetting::slot_boxHdmi_change(int box_change)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (box_change == 0)
	{
		//未选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_hdmi1Out_hdmi = true;

	}
	else if (box_change == 2)
	{
		//已选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_hdmi1Out_hdmi = false;
	}
}

//监听USB1复选框选中状态. usb 摄像头  
void CDlgPortSetting::slot_boxUsb1_change(int box_change)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (box_change == 0)
	{
		//未选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_usb_sxt_usb1 = true;

	}
	else if (box_change == 2)
	{
		//已选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_usb_sxt_usb1 = false;
	}
}

//监听音频输出复选框选中状态  
void CDlgPortSetting::slot_boxAudioOut_change(int box_change)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (box_change == 0)
	{
		//未选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_lb_out = true;

	}
	else if (box_change == 2)
	{
		//已选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_lb_out = false;
	}
}

//监听USB2复选框选中状态. usb 麦克风  现在叫音频输入了
void CDlgPortSetting::slot_boxUsb2_change(int box_change)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (box_change == 0)
	{
		//未选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_usb_mkf_usb2 = true;

	}
	else if (box_change == 2)
	{
		//已选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_usb_mkf_usb2 = false;
	}
}




//监听USB3复选框选中状态. use key
void CDlgPortSetting::slot_boxUsb3_change(int box_change)
{
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)QY_GET_procInfo_isCli();

	if (box_change == 0)
	{
		//未选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_usb_key_usb3 = true;

	}
	else if (box_change == 2)
	{
		//已选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_usb_key_usb3 = false;

	}

	//
	disableCa(pProcInfo->av.hk.portStatus.bDisable_usb_key_usb3);

}
//监听USB3复选框选中状态
void CDlgPortSetting::slot_boxLan_change(int box_change)
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (box_change == 0)
	{
		//未选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_network = true;

	}
	else if (box_change == 2)
	{
		//已选
		int aaa = 1;
		pProcInfo->av.hk.portStatus.bDisable_network = false;
	}
}


//样式
void CDlgPortSetting::sheetBackgroundImage()
{
	QRect rc = QApplication::primaryScreen()->geometry();

	if (rc.width() > 3500) {
		resize(2000,1100);

		ui->widget->setStyleSheet("background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");
		ui->label_t1->setStyleSheet("border-bottom:5px solid  #fff;font-size:85px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t2->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t3->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t4->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t5->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t6->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t7->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t8->setStyleSheet("font-size:40px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t9->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t10->setStyleSheet("font-size:50px;color:#fff;font-family: Microsoft YaHei;");

		ui->boxVga->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxHdmi->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxDvi->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxUsb1->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxUsb2->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxUsb3->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxLan->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxAudioOut->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");

		ui->btnRet->setStyleSheet("QPushButton{font-size:64px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		ui->btnRet->setFixedHeight(140);
		ui->btnRet->setFixedWidth(430);
	}
	else {
		
		ui->widget->setStyleSheet("background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");
		ui->label_t1->setStyleSheet("border-bottom:5px solid  #fff;font-size:48px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t2->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t3->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t4->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t5->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t6->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t7->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t8->setStyleSheet("font-size:20px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t9->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");
		ui->label_t10->setStyleSheet("font-size:28px;color:#fff;font-family: Microsoft YaHei;");

		ui->boxVga->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxHdmi->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxDvi->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxUsb1->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxUsb2->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxUsb3->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxLan->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");
		ui->boxAudioOut->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:10px;padding:3px}");

		ui->btnRet->setStyleSheet("QPushButton{font-size:32px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		
		ui->btnRet->setFixedHeight(80);
		ui->btnRet->setFixedWidth(230);
	}

}


//
void CDlgPortSetting::initBoxStatus() 
{

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		//
		ui->boxVga->setStyleSheet("QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

		//
		ui->boxHdmi->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

		//
		ui->boxDvi->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

		//
		ui->boxUsb1->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

		//
		ui->boxUsb2->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

		//
		ui->boxUsb3->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
		
		//
		ui->boxLan->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
		
		//
		ui->boxAudioOut->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

	}
	else {
		//
		ui->boxVga->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

		//
		ui->boxHdmi->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

		//
		ui->boxDvi->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

		//
		ui->boxUsb1->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

		//
		ui->boxUsb2->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

		//
		ui->boxUsb3->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
		
		//
		ui->boxLan->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");
		
		//
		ui->boxAudioOut->setStyleSheet("QCheckBox::indicator:unchecked{image:url(':/Resources/Images/WinMain/checkbox_1080.png');}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')}QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px} ");

	}

	//
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	//
	Qt::CheckState state;
	state = pProcInfo->av.hk.portStatus.bDisable_hdmiIn_vga ? Qt::Unchecked : Qt::Checked;
	ui->boxVga->setCheckState(state);
	state = pProcInfo->av.hk.portStatus.bDisable_hdmi1Out_hdmi ? Qt::Unchecked : Qt::Checked;
	ui->boxHdmi->setCheckState(state);
	state = pProcInfo->av.hk.portStatus.bDisable_hdmi2Out_dvi ? Qt::Unchecked : Qt::Checked;
	ui->boxDvi->setCheckState(state);
	state = pProcInfo->av.hk.portStatus.bDisable_usb_sxt_usb1 ? Qt::Unchecked : Qt::Checked;
	ui->boxUsb1->setCheckState(state);
	state = pProcInfo->av.hk.portStatus.bDisable_usb_mkf_usb2 ? Qt::Unchecked : Qt::Checked;
	ui->boxUsb2->setCheckState(state);
	state = pProcInfo->av.hk.portStatus.bDisable_usb_key_usb3 ? Qt::Unchecked : Qt::Checked;
	ui->boxUsb3->setCheckState(state);
	state = pProcInfo->av.hk.portStatus.bDisable_network ? Qt::Unchecked : Qt::Checked;
	ui->boxLan->setCheckState(state);
	state = pProcInfo->av.hk.portStatus.bDisable_lb_out ? Qt::Unchecked : Qt::Checked;
	ui->boxAudioOut->setCheckState(state);

	
}

//遥控器按下 hdmi out勾选
void CDlgPortSetting::slot_boxVga_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";


	//
	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		if (ui->boxVga->isChecked())
		{
			ui->boxVga->setCheckState(Qt::Unchecked);
			ui->boxVga->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			
			//
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭HDMI IN 端口";
		}
		else {
			ui->boxVga->setCheckState(Qt::Checked);
			ui->boxVga->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启HDMI IN端口";
		}
	}
	else {
		if (ui->boxVga->isChecked())
		{
			ui->boxVga->setCheckState(Qt::Unchecked);
			ui->boxVga->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			//
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭HDMI IN 端口";
		}
		else {
			ui->boxVga->setCheckState(Qt::Checked);
			ui->boxVga->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//

			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启HDMI IN端口";
		}
	}


	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);
	
}

//遥控器按下 hdmi out勾选
void CDlgPortSetting::slot_boxHdmi_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		if (ui->boxHdmi->isChecked())
		{
			ui->boxHdmi->setCheckState(Qt::Unchecked);
			ui->boxHdmi->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			//
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭HDMI1 OUT端口";
		}
		else {
			ui->boxHdmi->setCheckState(Qt::Checked);
			ui->boxHdmi->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭HDMI1 OUT端口"), false);

			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启HDMI1 OUT端口";
		}
	}
	else {
		if (ui->boxHdmi->isChecked())
		{
			ui->boxHdmi->setCheckState(Qt::Unchecked);
			ui->boxHdmi->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");

			//
			//qmcLogForHg(0, (TCHAR*)_T("终端开启HDMI1 OUT端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"关闭HDMI1 OUT端口";

		}
		else {
			ui->boxHdmi->setCheckState(Qt::Checked);
			ui->boxHdmi->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭HDMI1 OUT端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"开启HDMI1 OUT端口";
		}
	}
	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

}

//遥控器按下 hdmi in勾选
void CDlgPortSetting::slot_boxDvi_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		if (ui->boxDvi->isChecked())
		{
			ui->boxDvi->setCheckState(Qt::Unchecked);
			ui->boxDvi->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端开启HDMI2 OUT端口"), false);

			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"关闭HDMI2 OUT端口";
		}
		else {
			ui->boxDvi->setCheckState(Qt::Checked);
			ui->boxDvi->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭HDMI2 OUT端口"), false);

			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"开启HDMI2 OUT端口";
		}
	}
	else {
		if (ui->boxDvi->isChecked())
		{
			ui->boxDvi->setCheckState(Qt::Unchecked);
			ui->boxDvi->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端开启HDMI2 OUT端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"关闭HDMI2 OUT端口";
		}
		else {
			ui->boxDvi->setCheckState(Qt::Checked);
			ui->boxDvi->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭HDMI2 OUT端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"开启HDMI2 OUT端口";
		}	
	}
	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);
	
}

//遥控器按下 usb1勾选
void CDlgPortSetting::slot_boxUsb1_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		if (ui->boxUsb1->isChecked())
		{
			ui->boxUsb1->setCheckState(Qt::Unchecked);
			ui->boxUsb1->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端开启USB 摄像头端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"关闭USB 摄像头端口";
		}
		else {
			ui->boxUsb1->setCheckState(Qt::Checked);
			ui->boxUsb1->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭USB 摄像头端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"开启USB 摄像头端口";
		}
	}
	else {
		if (ui->boxUsb1->isChecked())
		{
			ui->boxUsb1->setCheckState(Qt::Unchecked);
			ui->boxUsb1->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端开启USB 摄像头端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"关闭USB 摄像头端口";
		}
		else {
			ui->boxUsb1->setCheckState(Qt::Checked);
			ui->boxUsb1->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭USB 摄像头端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"开启USB 摄像头端口";
		}
	}
	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);
	
}

//遥控器按下 usb2勾选  现在叫音频输入
void CDlgPortSetting::slot_boxUsb2_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		if (ui->boxUsb2->isChecked())
		{
			ui->boxUsb2->setCheckState(Qt::Unchecked);
			ui->boxUsb2->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端开启USB 麦克风端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"关闭音频输入";

		}
		else {
			ui->boxUsb2->setCheckState(Qt::Checked);
			ui->boxUsb2->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭USB 麦克风端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"开启音频输入";
		}
	}
	else {
		if (ui->boxUsb2->isChecked())
		{
			ui->boxUsb2->setCheckState(Qt::Unchecked);
			ui->boxUsb2->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");

			//
			//qmcLogForHg(0, (TCHAR*)_T("终端开启USB 麦克风端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"关闭音频输入";
		}
		else {
			ui->boxUsb2->setCheckState(Qt::Checked);
			ui->boxUsb2->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭USB 麦克风端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"开启音频输入";
		}
	}
	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);
	
}

//遥控器按下 音频输出
void CDlgPortSetting::slot_boxAudioOut_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		if (ui->boxAudioOut->isChecked())
		{
			ui->boxAudioOut->setCheckState(Qt::Unchecked);
			ui->boxAudioOut->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端开启USB 麦克风端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"关闭音频输出";

		}
		else {
			ui->boxAudioOut->setCheckState(Qt::Checked);
			ui->boxAudioOut->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭USB 麦克风端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"开启音频输出";
		}
	}
	else {
		if (ui->boxAudioOut->isChecked())
		{
			ui->boxAudioOut->setCheckState(Qt::Unchecked);
			ui->boxAudioOut->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");

			//
			//qmcLogForHg(0, (TCHAR*)_T("终端开启USB 麦克风端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"关闭音频输出";
		}
		else {
			ui->boxAudioOut->setCheckState(Qt::Checked);
			ui->boxAudioOut->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭USB 麦克风端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"开启音频输出";
		}
	}
	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);
	
}

//遥控器按下 usb3勾选
void CDlgPortSetting::slot_boxUsb3_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		if (ui->boxUsb3->isChecked())
		{
			ui->boxUsb3->setCheckState(Qt::Unchecked);
			ui->boxUsb3->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");

			//
			//qmcLogForHg(0, (TCHAR*)_T("终端开启USB UKEY端口"), false);

			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"关闭USB UKEY端口";
		}
		else {
			ui->boxUsb3->setCheckState(Qt::Checked);
			ui->boxUsb3->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭USB UKEY端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"开启USB UKEY端口";
		}
	}
	else {
		if (ui->boxUsb3->isChecked())
		{
			ui->boxUsb3->setCheckState(Qt::Unchecked);
			ui->boxUsb3->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			//
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"关闭USB UKEY端口";
		}
		else {
			ui->boxUsb3->setCheckState(Qt::Checked);
			ui->boxUsb3->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭USB UKEY端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"开启USB UKEY端口";
		}
	}
	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);
}

//遥控器按下 网络接口勾选
void CDlgPortSetting::slot_boxLan_click(QString objname)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	if (!pQyMc) return;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return;
	QString log_txt = "";

	QRect rc = QApplication::primaryScreen()->geometry();
	if (rc.width() > 3500) {
		if (ui->boxLan->isChecked())
		{
			ui->boxLan->setCheckState(Qt::Unchecked);
			ui->boxLan->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端开启LAN端口"), false);

			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"关闭LAN端口";
		}
		else {
			ui->boxLan->setCheckState(Qt::Checked);
			ui->boxLan->setStyleSheet("QCheckBox{font-size:48px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			//qmcLogForHg(0, (TCHAR*)_T("终端关闭LAN端口"), false);
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：" + u8"开启LAN端口";
		}
	}
	else {
		if (ui->boxLan->isChecked())
		{
			ui->boxLan->setCheckState(Qt::Unchecked);
			ui->boxLan->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator{image: url(':/Resources/Images/WinMain/checkbox_1080.png')} ");
			//
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"关闭LAN端口";
		}
		else {
			ui->boxLan->setCheckState(Qt::Checked);
			ui->boxLan->setStyleSheet("QCheckBox{font-size:24px;color:#fff;font-family: Microsoft YaHei;}QCheckBox:focus{color:#fff;font-weight:bold;background:#1C56F1;border-radius:0px;padding:0px}QCheckBox::indicator:checked{image: url(':/Resources/Images/WinMain/checkboxed_1080.png')} ");
			//
			log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"："  + u8"开启LAN端口";
		}
	}
	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);
}

//遥控器按下 返回按钮
void CDlgPortSetting::on_btnRet_clicked(QString objname)
{
	emit to_returnMain_signal();
}

//红外菜单
void CDlgPortSetting::on_infraredMenu()
{

	//
//	if (!m_pInfraredMenu)
//	{
//		m_pInfraredMenu = new CInfraredDialogMenu(this, "CDlgPortSetting");
//	}
//
//	//
////	if  (  m_pInfraredMenu->winId()  !=  pQyMc)
//
//	//
//	if (!m_pInfraredMenu->isVisible())
//	{
//		//窗口只打开一次
//
//		m_pInfraredMenu->show();
//
//
//
//		return;
//
//	}
}

//菜单关闭
void CDlgPortSetting::infraredMenu_quit()
{
	if (!m_pInfraredMenu)
	{
		return;
	}

	//if (m_pInfraredMenu->isVisible()) 
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
void CDlgPortSetting::Infrared_down()
{

	
	this->focusNextPrevChild(true);
}

//上箭头
void CDlgPortSetting::Infrared_up()
{

	this->focusNextPrevChild(false);
}

CDlgPortSetting::~CDlgPortSetting()
{

	delete ui;

	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	CCtxQyMc* pQyMc = g_pQyMc;

	saveHkPortStatus(&pProcInfo->av.hk.portStatus, pQyMc->cfg.hkPortStatusFile);


}
