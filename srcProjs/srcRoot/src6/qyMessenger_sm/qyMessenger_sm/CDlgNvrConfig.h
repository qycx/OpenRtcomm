#pragma once

#include <QDialog>
#include "ui_CDlgNvrConfig.h"
#include <CInfraredDialogMenu.h>

class CDlgNvrConfig : public QDialog
{
	Q_OBJECT

public:
	CDlgNvrConfig(QWidget *parent = nullptr);
	~CDlgNvrConfig();


	void sheetBackgroundImage();
	void initBoxStatus();

	void Infrared_down();  //下箭头
	void Infrared_up();    //上箭头
	void Infrared_ok(QString objname = nullptr);		//确认键
	//
	CInfraredDialogMenu* m_pInfraredMenu = nullptr;

	void Infrared_input(QString name, QString value); //表单输入

	void Infrared_input_leeter(QString name, QString value, bool is_replace); //表单输入字母

	void Infrared_input_left_right(QString name, bool isLeft); //左右箭头

	void Infrared_input_backspace(QString name);

	void slot_boxNvrEna_click(QString objname);
	void slot_boxNvrDh_click(QString objname);
	void slot_boxNvrHik_click(QString objname);
	void slot_boxNvrD4k_click(QString objname);

	void slot_mouse_boxNvrDh_click(bool checked);
	void slot_mouse_boxNvrHik_click(bool checked);
	void slot_mouse_boxNvrD4k_click(bool checked);
	void slot_mouse_boxNvrEna_click(bool checked); 

	void infraredMenu_quit();
	void on_infraredMenu();
public slots:
	void slot_boxNvrEna_change(int box_change);
	void slot_boxNvrDh_change(int box_change);
	void slot_btnOk_click();

signals:
	void to_returnMain_nvr_signal();
	



private:
	Ui::CDlgNvrConfigClass *ui;

	bool _nvr_enable = false;
};
