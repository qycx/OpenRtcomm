#pragma once

#include <QWidget>
#include "ui_CDlgTalkInfo.h"
#include "WinObjUser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CDlgTalkInfo; }
QT_END_NAMESPACE

class CDlgTalkInfo : public QWidget
{
	Q_OBJECT

public:
	CDlgTalkInfo(QWidget *parent = Q_NULLPTR);
	~CDlgTalkInfo();
	void initControl();
	void setCDlgTalkInfo(WinObjUser user);

private slots:
	void doCDlgTalkInfo(WinObjUser user);

private:
	Ui::CDlgTalkInfo *ui;
	


};
