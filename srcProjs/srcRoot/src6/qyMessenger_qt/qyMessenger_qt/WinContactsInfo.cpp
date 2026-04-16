#include "WinContactsInfo.h"

WinContactsInfo::WinContactsInfo(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::WinContactsInfo)
{
	ui->setupUi(this);
	this->setObjectName("ContactsInfo");
	initControl();
}

WinContactsInfo::~WinContactsInfo()
{
	delete ui;
}

//显示用户信息
void WinContactsInfo::ShowContactsListInfo(WinObjUser user)
{
	if (user.dataType == 3)//联系人
	{
		if (user.name == "null")
		{
			ui->btnSendMsg->hide();
			ui->benSendMeeting->hide();
			ui->setBtn->hide();
			ui->centerWidget->hide();

		}
		else
		{
			ui->btnSendMsg->show();
			ui->benSendMeeting->show();
			ui->setBtn->show();
			ui->centerWidget->show();
			ui->idinfo->setText(user.idinfo);
			ui->labelName->setText(user.name);
			ui->labelGroup->setText(user.dw + " " + user.bm);
			ui->label1->setText(user.dw);
			ui->label2->setText(user.bm);
		}
	}
}

//初始化
void WinContactsInfo::initControl()
{
	QFile file(":/Resources/QSS/WinContactsInfo.css");
	file.open(QFile::ReadOnly);
	if (file.isOpen())
	{
		this->setStyleSheet("");
		QString qsstyleSheet = QLatin1String(file.readAll());
		this->setStyleSheet(qsstyleSheet);
	}
	file.close();

	ui->headIcoBtn->setIcon(QIcon(":/Resources/Images/WinMain/headMax.png"));
	ui->headIcoBtn->setIconSize(QSize(55, 55));
	ui->labelName->setText(u8"");
	ui->labelGroup->setText(u8"");
	ui->idinfo->setVisible(false);

	//ui->btnSendMsg->hide();
	//ui->benSendMeeting->hide();
	//ui->setBtn->hide();
	//ui->centerWidget->hide();
	//ui->bottomWidget->hide();
}

void WinContactsInfo::on_btnSendMsg_clicked()
{
	WinObjUser user;
	user.idinfo = ui->idinfo->text();
	user.name = ui->labelName->text();
	user.bm = ui->label2->text();
	user.dw = ui->label1->text();
	emit toSendMsg(user);
}

void WinContactsInfo::on_benSendMeeting_clicked()
{
	WinObjUser user;
	user.idinfo = ui->idinfo->text();
	user.name = ui->labelName->text();
	user.bm = ui->label2->text();
	user.dw = ui->label1->text();
	emit toSendMeeting(user);
}

