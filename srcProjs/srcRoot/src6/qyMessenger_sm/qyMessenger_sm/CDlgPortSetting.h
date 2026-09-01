#pragma once

#include <QDialog>
#include "ui_CDlgPortSetting.h"
#include "CInfraredDialogMenu.h"

class CDlgPortSetting : public QDialog
{
	Q_OBJECT

public:
	CDlgPortSetting(QWidget *parent = nullptr);
	~CDlgPortSetting();

	void sheetBackgroundImage();
	void initBoxStatus();

	void Infrared_down();  //下箭头
	void Infrared_up();    //上箭头

	void Infrared_ok(QString objname = nullptr);		//确认键
	
	//
	CInfraredDialogMenu* m_pInfraredMenu = nullptr;

signals:
	void to_returnMain_signal();

public slots:
	void slot_boxVga_change(int box_change);
	void slot_boxHdmi_change(int box_change);
	void slot_boxDvi_change(int box_change);
	void slot_boxUsb1_change(int box_change);
	void slot_boxUsb2_change(int box_change);
	void slot_boxUsb3_change(int box_change);
	void slot_boxLan_change(int box_change);
	void slot_boxAudioOut_change(int box_change);

	void slot_boxVga_click(QString objname);
	void slot_boxHdmi_click(QString objname);
	void slot_boxDvi_click(QString objname);
	void slot_boxUsb1_click(QString objname);
	void slot_boxUsb2_click(QString objname);
	void slot_boxUsb3_click(QString objname);
	void slot_boxLan_click(QString objname);
	void slot_boxAudioOut_click(QString objname);

	void on_btnRet_clicked(QString objname = nullptr);

	void infraredMenu_quit();
	void on_infraredMenu();
	
	
public:
	Ui::CDlgPortSettingClass* ui;

};
