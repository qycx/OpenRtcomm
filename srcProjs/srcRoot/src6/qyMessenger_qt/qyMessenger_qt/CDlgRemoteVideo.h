#pragma once

#include <QWidget>
#include "ui_CDlgRemoteVideo.h"

#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class CDlgRemoteVideoClass; };
QT_END_NAMESPACE

class CDlgRemoteVideo : public QWidget
{
	Q_OBJECT

public:
	CDlgRemoteVideo(QWidget *parent = nullptr);
	~CDlgRemoteVideo();

	void resizeEvent(QResizeEvent* event);

protected:
	void closeEvent(QCloseEvent* event) override {
		event->ignore();  
		hide();          
	}

signals:
	void to_remotevideo_resize();

private:
	Ui::CDlgRemoteVideoClass *ui;
};
