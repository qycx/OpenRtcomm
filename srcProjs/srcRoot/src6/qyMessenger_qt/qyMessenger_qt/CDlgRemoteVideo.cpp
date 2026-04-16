#include "CDlgRemoteVideo.h"

CDlgRemoteVideo::CDlgRemoteVideo(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::CDlgRemoteVideoClass())
{
	ui->setupUi(this);
}

CDlgRemoteVideo::~CDlgRemoteVideo()
{
	delete ui;
}


void CDlgRemoteVideo::resizeEvent(QResizeEvent* event)
{
	emit to_remotevideo_resize();
}