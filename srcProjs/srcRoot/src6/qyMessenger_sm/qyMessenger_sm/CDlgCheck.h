#pragma once

#include <QDialog>
#include "ui_CDlgCheck.h"
#include <CInfraredDialogMenu.h>

#include "IPConflictChecker.h"

class CDlgCheck : public QDialog
{
	Q_OBJECT

public:
	CDlgCheck(const std::string& terminalIp, const std::string& mcuIp, QWidget *parent = nullptr);
	~CDlgCheck();


	void Infrared_down();  //下箭头
	void Infrared_up();    //上箭头
	void Infrared_ok(QString objname = nullptr);		//确认键
	//
	CInfraredDialogMenu* m_pInfraredMenu = nullptr;

	void sheetBackgroundImage();
	void CheckIp(const std::string& terminalIp, const std::string& mcuIp);

	void CheckIpTerminal(const std::string& terminalIp);
	void CheckIpMcu(const std::string& mcuIp);
	void CheckIpNvr();

	IPConflictChecker* m_IPConflictChecker;

	void infraredMenu_quit();
	//void on_infraredMenu();

protected:
	bool pingIP(const std::string& ipAddress);
	bool Ping(const std::wstring& ipAddress, int timeout = 1000);
	std::wstring to_wstring(const std::string& str);

public slots:
	//void slot_boxNvrEna_change(int box_change);
	//void slot_boxNvrDh_change(int box_change);
	void slot_btnOk_click();

signals:
	void to_returnMain_check_signal();



private:
	Ui::CDlgCheckClass *ui;

	bool _nvr_enable = false;
};
