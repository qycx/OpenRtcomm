#pragma once

#include <QWidget>
#include "ui_CDlg2ndScreen.h"

#include	<tchar.h>
#include <qscrollarea.h>
#include	"qyMcMainCommon_qt.h"
#include	"dlgVideosProc.h"
#include  "WinBasic.h"
#include "WinTitle.h"


//
class CDlg2ndScreen : public WinBasic
{
	Q_OBJECT

	//
	DLG_videos_var		m_var;

	struct {
		int					m_iW_scroll = 0;
		int					m_iH_scroll = 0;
		bool				m_bExists_stream = false;

		//

	}					m_streamInfo;

	//
public:
	CDlg2ndScreen(QWidget *parent = nullptr);
	~CDlg2ndScreen();

	//
	int  sizeAllControls(RECT  rcParam);

	//开始屏幕分享
	bool  bEnableScrollBar(bool  bEnable, int  iw_scroll, int  ih_scroll);
	void  clearScrollBar();

	void mouseDoubleClickEvent(QMouseEvent* e);


protected:
	bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result);
	//界面尺寸变化重绘
	virtual void resizeEvent(QResizeEvent* event) override;

	virtual void closeEvent(QCloseEvent* ev);

	virtual bool eventFilter(QObject* obj, QEvent* ev);


private slots:
	//
	void on_timer_winMethod();
	//最小化
	void onButtonMinClicked();
	//关闭窗体
	void onButtonCloseClicked();
	//还原
	void onButtonRestoreClicked();
	//最大化
	void onButtonMaxClicked();

private:
	Ui::CDlg2ndScreenClass ui;

	//
	QTimer* m_pWinTimer = nullptr;

	//
	int _double_i = 0;

	//
	QScrollArea* scrollArea_ = nullptr;
	WinTitle* m_pWinTitle = nullptr;


	//
	QPoint lastPt;
	bool pressed = false;

};
