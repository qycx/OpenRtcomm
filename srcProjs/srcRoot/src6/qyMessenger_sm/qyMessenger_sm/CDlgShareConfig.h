#pragma once

#include <QDialog>
#include "ui_CDlgShareConfig.h"

#include "CInfraredDialogMenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CDlgShareConfigClass; };
QT_END_NAMESPACE

class CDlgShareConfig : public QDialog
{
	Q_OBJECT

public:
	CDlgShareConfig(QWidget *parent = nullptr);
	~CDlgShareConfig();

	void sheetBackgroundImage();

	void initBoxStatus();

	void Infrared_down();  //下箭头
	void Infrared_up();    //上箭头
	//void Infrared_ok(QString objname = nullptr);		//确认键
	//
	CInfraredDialogMenu* m_pInfraredMenu = nullptr;

	void Infrared_input(QString name, QString value); //表单输入

	void Infrared_input_leeter(QString name, QString value, bool is_replace); //表单输入字母

	void Infrared_input_left_right(QString name, bool isLeft); //左右箭头

	void Infrared_input_backspace(QString name);

	void slot_boxAutoShare_click(QString objname);



	void slot_mouse_boxAutoShare_click(bool checked);
	void slot_boxEnableShare_click(QString objname);

	void infraredMenu_quit();
	//void on_infraredMenu();
public slots:
	void slot_boxEnableShare_change(int box_change);
	void slot_boxAutoShare_change(int box_change);
	void slot_btnOk_click();

signals:
	void to_returnMain_share_signal();

private:
	Ui::CDlgShareConfigClass *ui;

	bool _enable_share = false;
	bool _auto_share = false;
};
