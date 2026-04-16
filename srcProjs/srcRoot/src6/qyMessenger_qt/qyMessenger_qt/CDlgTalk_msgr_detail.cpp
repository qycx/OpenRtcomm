#include "CDlgTalk_msgr_detail.h"
#include <WinRuleSet.h>
#include	<qfile.h>

CDlgTalk_msgr_detail::CDlgTalk_msgr_detail(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::CDlgTalk_msgr_detail)
{
	ui->setupUi(this);
	this->setObjectName("ContactsInfo");
	initControl();
}

CDlgTalk_msgr_detail::~CDlgTalk_msgr_detail()
{
	delete ui;
}

//显示用户信息
void CDlgTalk_msgr_detail::ShowContactsListInfo(WinObjUser user)
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
			ui->labMsgrId->setText(user.idinfo);
			ui->labelName->setText(user.name);
			ui->labSyr->setText(user.name);
			ui->labelGroup->setText(user.dw + " " + user.bm);
			ui->label1->setText(user.dw);
			ui->label2->setText(user.bm);
			//
			m_curUser.idinfo = user.idinfo;
			m_curUser.name = user.name;
			m_curUser.bm = user.bm;
			m_curUser.dw = user.dw;
			m_curUser.dataType = user.dataType;

		}
	}
}

//初始化
void CDlgTalk_msgr_detail::initControl()
{
	QFile file(":/Resources/QSS/CDlgTalk_msgr_detail.css");
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
}

void CDlgTalk_msgr_detail::on_btnSendMsg_clicked()
{
	WinObjUser user;
	user.idinfo = ui->idinfo->text();
	user.name = ui->labelName->text();
	user.bm = ui->label2->text();
	user.dw = ui->label1->text();
	emit toSendMsg(user);
}

void CDlgTalk_msgr_detail::on_setBtn_clicked() {
	QY_MESSENGER_ID  idInfo;
	idInfo.ui64Id = this->m_curUser.idinfo.toInt();
	WinRuleSet::showDialog(this, idInfo.ui64Id);
}


void CDlgTalk_msgr_detail::on_benSendMeeting_clicked()
{
#if 0
	WinObjUser user;
	user.idinfo = ui->idinfo->text();
	user.name = ui->labelName->text();
	user.bm = ui->label2->text();
	user.dw = ui->label1->text();
	emit toSendMeeting(user);
#endif
	QY_MESSENGER_ID		idInfo;
	idInfo.ui64Id = m_curUser.idinfo.toInt();
	talk_doAv((HWND)this->winId(), idInfo,false);
}