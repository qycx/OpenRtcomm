#include "CDlgTalkInfo.h"

CDlgTalkInfo::CDlgTalkInfo(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::CDlgTalkInfo)
{
	ui->setupUi(this);
	initControl();
}


void CDlgTalkInfo::initControl() 
{
	setAttribute(Qt::WA_DeleteOnClose);

	QPixmap headIcoBtnPixmap(":/Resources/Images/WinMain/headMax.png");
	ui->headIcoBtn->setIcon(headIcoBtnPixmap);
	ui->headIcoBtn->setIconSize(QSize(55, 55));

	ui->labelName->setText(u8"");
	ui->labelGroup->setText(u8"");
	ui->labelMsgID->setText(u8"Messenger ID:");  
	this->setStyleSheet("");
} 

void CDlgTalkInfo::setCDlgTalkInfo(WinObjUser user) {
	ui->labelName->setText(user.name);
	ui->labelGroup->setText(user.bm);
	ui->labelMsgID->setText(u8"Messenger ID:"+user.idinfo); 
}  

void CDlgTalkInfo::doCDlgTalkInfo(WinObjUser user) {
	ui->labelName->setText(user.name);
	ui->labelGroup->setText(user.bm);
	ui->labelMsgID->setText(u8"Messenger ID:" + user.idinfo);
}



CDlgTalkInfo::~CDlgTalkInfo()
{
	delete ui;
}
