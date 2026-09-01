#pragma once

#include <QDialog>
#include "ui_CDlgWifiConfig.h"
#include <CInfraredDialogMenu.h>
#include "WiFiManager.h"
#include <QTimer>
#include <CInfraredDialogMenu.h>


class CDlgWifiConfig : public QDialog
{
	Q_OBJECT

public:
	CDlgWifiConfig(QWidget *parent = nullptr);
	~CDlgWifiConfig();

	void sheetBackgroundImage();

	std::mutex m_mutex;
	std::mutex m_mutexMsg;


	WiFiInfoList m_Wifilist;
	bool m_running;

	QString getMsg();
	void setMsg(const QString& msg);

	CInfraredDialogMenu* m_pInfraredMenu = nullptr;

	void infraredMenu_quit();
	void Infrared_down();
	void Infrared_up();
	void Infrared_input_left_right(QString name, bool isLeft);
	void Infrared_input(QString name, QString value);
	void Infrared_input_leeter(QString name, QString value, bool is_replace);
	void Infrared_input_backspace(QString name);

	void SetConnectButtonState(std::wstring cstrSSID, bool state);

	bool SetWlan();
	
public slots:
	//void slot_boxNvrEna_change(int box_change);
	void slot_btnOk_click();
	void doTimeout();
	void slot_pushButton_detect_click();
	void slot_pushButton_conn_click();
	void wifiDoubleClicked(QTreeWidgetItem* item, int column);
	void slot_update_wifi();
	void slot_wifi_enter();
	void slot_set_conn_button_text(QString text);
	void slot_set_msg(QString text);
	
	

signals:
	void to_returnMain_wifi_signal();
	void update_wifi_signal();
	void set_conn_button_text_sigle(QString text);
	void set_msg_sigle(QString text);


protected:
	void showWifi();


private:
	Ui::CDlgWifiConfigClass *ui;

	bool _nvr_enable = false;

	QString m_msg;

	std::thread* m_thread;
	QTimer* m_timer;
};
