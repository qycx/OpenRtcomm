#pragma once

#include <QDialog>
#include "ui_CDlgSelectVideo.h"

#include "CInfraredDialogMenu.h"

#include <vector>

class IMoniker;

QT_BEGIN_NAMESPACE
namespace Ui { class CDlgSelectVideoClass; };
QT_END_NAMESPACE



class CDlgSelectVideo : public QDialog
{
	Q_OBJECT

public:
	CDlgSelectVideo(QWidget *parent = nullptr);
	~CDlgSelectVideo();

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

	void slot_boxRtsp_click(QString objname);
	void slot_checkBox_click(QString objname);



	void slot_mouse_boxRtsp_click(bool checked);
	void slot_boxEnableShare_click(QString objname);

	void infraredMenu_quit();
	//void on_infraredMenu();

protected:
	void Init();
	void InitVideoDev();
	void EnumerateVideoDevicesSave();

public slots:
	void slot_boxEnableShare_change(int box_change);
	void slot_boxRtsp_change(int box_change);
	void slot_btnOk_click();
	void slot_btnCancle_click();
	void onCheckBoxClicked(bool checked);

signals:
	void to_returnMain_selectVideo_signal();

private:
	Ui::CDlgSelectVideoClass *ui;

	bool _enable_share = false;
	bool _auto_share = false;


	std::vector<QCheckBox*> m_videoDevList;
	IMoniker* videoMoniker[10];
	int			iCamCapType = 0;
	std::wstring  webcam_selected;
	std::wstring  RtspUrl_selected;

};
