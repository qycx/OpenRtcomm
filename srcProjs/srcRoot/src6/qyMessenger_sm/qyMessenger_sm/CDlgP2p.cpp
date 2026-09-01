#include	<tchar.h>

#define  __noDbg_new__

#include "CDlgP2p.h"

#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc_sm.h"
#include	"CMainFrame.h"
#include	"smProc_qt.h"

CDlgP2p::CDlgP2p(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::CDlgP2pClass)
{
	ui->setupUi(this);

	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);


	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setWindowOpacity(0.9);
	QCursor::setPos(0, 0);
	//ui->btnP2p_1->setVisible(false);
	//ui->btnP2p_2->setVisible(false);
	//ui->btnP2p_3->setVisible(false);
	//ui->btnP2p_4->setVisible(false);
	//ui->btnP2p_5->setVisible(false);
	//ui->btnP2p_6->setVisible(false);
	//ui->btnP2p_7->setVisible(false);
	//ui->btnP2p_8->setVisible(false);
	//ui->btnP2p_9->setVisible(false);
	//ui->btnP2p_10->setVisible(false);


	ui->btnP2p_up->setText(u8"（第1页）上一页");
	ui->btnP2p_2->setText("");
	ui->btnP2p_3->setText("");
	ui->btnP2p_4->setText("");
	ui->btnP2p_5->setText("");
	ui->btnP2p_6->setText("");
	ui->btnP2p_7->setText("");
	ui->btnP2p_8->setText("");
	ui->btnP2p_9->setText("");
	ui->btnP2p_down->setText(u8"（第1页）下一页");


	startToRetrieveP2pList();

	sheetBackgroundImage();


	



	m_pWinTimer = new QTimer(this);
	connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(on_timer_winMethod()));

	m_pWinTimer->setInterval(100);
	m_pWinTimer->start();


}

//布局
void CDlgP2p::sheetBackgroundImage() {

	QRect rc = QApplication::primaryScreen()->geometry();

	ui->lab_title->setAlignment(Qt::AlignCenter);

	if (rc.width() > 3500) {

		ui->lab_title->setStyleSheet("font-size:54px;font-weight:bold;color:#fff;font-family: Microsoft YaHei;");
		//ui->widget->setStyleSheet("QWidget#widget{background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30);}QPushButton{color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		int w_i = 1600;
		int h_i = 200;
		ui->lab_title->setFixedSize(w_i, h_i);
		ui->btnP2p_up->setFixedSize(w_i, h_i);
		ui->btnP2p_2->setFixedSize(w_i, h_i);
		ui->btnP2p_3->setFixedSize(w_i, h_i);
		ui->btnP2p_4->setFixedSize(w_i, h_i);
		ui->btnP2p_5->setFixedSize(w_i, h_i);
		ui->btnP2p_6->setFixedSize(w_i, h_i);
		ui->btnP2p_7->setFixedSize(w_i, h_i);
		ui->btnP2p_8->setFixedSize(w_i, h_i);
		ui->btnP2p_9->setFixedSize(w_i, h_i);
		ui->btnP2p_down->setFixedSize(w_i, h_i);
		ui->btnP2p_close->setFixedSize(w_i, h_i);

		ui->widget->setStyleSheet("QWidget#widget{border-radius:10px;} QPushButton{border-bottom:2px solid #000;background:#1E2747;font-size:68px;color:#fff;font-family: Microsoft YaHei;}QPushButton:focus {font-family: Microsoft YaHei;background:#1A54F1;color:#fff}");
		//ui->label_title->setStyleSheet("font-size:84px;color:#fff;font-weight:bold;background:none;font-family: Microsoft YaHei;");
		//ui->widget->setContentsMargins(20, 20, 20, 20);



	}
	else {
		//resize(500, 700);
		//ui->lab_title->setHeight(30);
		ui->lab_title->setStyleSheet("font-size:28px;font-weight:bold;color:#fff;background:#1E2747;font-family: Microsoft YaHei;");
		//ui->widget->setStyleSheet("QWidget#widget{background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30);}QPushButton{color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

	
		ui->widget->setStyleSheet("QWidget#widget{border-radius:10px;} QPushButton{border-bottom:2px solid #000;background:#1E2747;font-size:28px;color:#fff;font-family: Microsoft YaHei;}QPushButton:focus {font-family: Microsoft YaHei;background:#1A54F1;color:#fff}");
		//ui->label_title->setStyleSheet("font-size:42px;color:#fff;font-weight:bold;background:none;font-family: Microsoft YaHei;");

		

		int h_i = 60;
		int w_i = 700;
		ui->widget->setFixedWidth(w_i);
		ui->lab_title->setFixedSize(w_i, h_i);
		ui->btnP2p_up->setFixedSize(w_i, h_i);
		ui->btnP2p_2->setFixedSize(w_i, h_i);
		ui->btnP2p_3->setFixedSize(w_i, h_i);
		ui->btnP2p_4->setFixedSize(w_i, h_i);
		ui->btnP2p_5->setFixedSize(w_i, h_i);
		ui->btnP2p_6->setFixedSize(w_i, h_i);
		ui->btnP2p_7->setFixedSize(w_i, h_i);
		ui->btnP2p_8->setFixedSize(w_i, h_i);
		ui->btnP2p_9->setFixedSize(w_i, h_i);
		ui->btnP2p_down->setFixedSize(w_i, h_i);
		ui->btnP2p_close->setFixedSize(w_i, h_i);
	

	
	}
	
}




void CDlgP2p::on_btnP2p_up_clicked() {

	//int index = 0;

	//send_askforP2p(index);

	pageLoadData(true);

	


}

void CDlgP2p::on_btnP2p_2_clicked() {

	int index = 0;

	
	send_askforP2p(index);

}

void CDlgP2p::on_btnP2p_3_clicked() {

	int index = 1;

	
	send_askforP2p(index);

}

void CDlgP2p::on_btnP2p_4_clicked() {

	int index = 2;

	
	send_askforP2p(index);

}

void CDlgP2p::on_btnP2p_5_clicked() {


	int index = 3;

	//askforP2p(pProcInfo->av.confLayout.login_termialName, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].grpInfo, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].termName, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].idfo, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].p2pLevel);
	send_askforP2p(index);

}

void CDlgP2p::on_btnP2p_6_clicked() {

	int index = 4;

	//askforP2p(pProcInfo->av.confLayout.login_termialName, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].grpInfo, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].termName, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].idfo, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].p2pLevel);
	send_askforP2p(index);

}

void CDlgP2p::on_btnP2p_7_clicked() {

	int index = 5;

	
	send_askforP2p(index);

}

void CDlgP2p::on_btnP2p_8_clicked() {

	int index = 6;

	//askforP2p(pProcInfo->av.confLayout.login_termialName, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].grpInfo, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].termName, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].idfo, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].p2pLevel);
	send_askforP2p(index);
	
}

void CDlgP2p::on_btnP2p_9_clicked() {

	int index = 7;

	//askforP2p(pProcInfo->av.confLayout.login_termialName, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].grpInfo, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].termName, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].idfo, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].p2pLevel);
	send_askforP2p(index);
	

}

void CDlgP2p::on_btnP2p_down_clicked() {

	//int index = 8;

	// send_askforP2p(index);
	pageLoadData(false);
	
}

void CDlgP2p::send_askforP2p(int index) 
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

	askforP2p(pProcInfo->av.confLayout.login_termialName, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].grpInfo, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].termName, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].idfo, pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].p2pLevel);
	
	QString log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"发起与" + QString::fromUtf16(((ushort*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].termName)) + u8"的点对点会议";

	qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

	if (pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[index].grpInfo != 0)
	{
		do_close();
	}
}

void CDlgP2p::do_close() {
	CCtxQyMc* pQyMc = g_pQyMc;

	CMainFrame* pMainWnd = (CMainFrame*)CMainFrame::find((WId)pQyMc->gui.hMainWnd);
	if (pMainWnd) {
		pMainWnd->on_P2pDlg_close();
	}

	return;
}

//分页装载数据
void  CDlgP2p::pageLoadData(bool is_up) 
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	QString termName1;
	QString termName2;
	QString termName3;
	QString termName4;
	QString termName5;
	QString termName6;
	QString termName7;
	QString termName8;


	if (is_up) {
		//
		if (_pageCur == 1) {
			return;
		}
		_pageCur--;
		int offset = (_pageCur - 1)* _pageCount;
		termName1 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[offset].termName);
		termName2 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[++offset].termName);
		termName3 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[++offset].termName);
		termName4 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[++offset].termName);
		termName5 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[++offset].termName);
		termName6 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[++offset].termName);
		termName7 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[++offset].termName);
		termName8 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[++offset].termName);
	}
	else {
		_pageCur++;
		int offset = (_pageCur - 1) * _pageCount;
		if (offset > pProcInfo->m_var.ctxSm.hg.p2pInfos.cnt) {
			_pageCur--;
			return;
		}
		 termName1 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[offset].termName);
		 termName2 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[++offset].termName);
		 termName3 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[++offset].termName);
		 termName4 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[++offset].termName);
		 termName5 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[++offset].termName);
		 termName6 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[++offset].termName);
		 termName7 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[++offset].termName);
		 termName8 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[++offset].termName);

	}

	ui->btnP2p_2->setText(termName1);
	ui->btnP2p_3->setText(termName2);
	ui->btnP2p_4->setText(termName3);
	ui->btnP2p_5->setText(termName4);
	ui->btnP2p_6->setText(termName5);
	ui->btnP2p_7->setText(termName6);
	ui->btnP2p_8->setText(termName7);
	ui->btnP2p_9->setText(termName8);

	ui->btnP2p_up->setText(u8"（第" +  QString::number(_pageCur)  + u8"页）上一页");
	ui->btnP2p_down->setText(u8"（第" + QString::number(_pageCur)  + u8"页）下一页");
	
		
}


//zhuang
void CDlgP2p::loadData() {

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

	/*QString termName1 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[0].termName) + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[0].grpInfo) + ")" + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[0].idfo) + ")";
	QString termName2 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[1].termName) + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[1].grpInfo) + ")" + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[1].idfo) + ")";
	QString termName3 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[2].termName) + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[2].grpInfo) + ")" + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[2].idfo) + ")";
	QString termName4 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[3].termName) + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[3].grpInfo) + ")" + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[3].idfo) + ")";
	QString termName5 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[4].termName) + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[4].grpInfo) + ")" + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[4].idfo) + ")";
	QString termName6 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[5].termName) + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[5].grpInfo) + ")" + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[5].idfo) + ")";
	QString termName7 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[6].termName) + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[6].grpInfo) + ")" + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[6].idfo) + ")";
	QString termName8 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[7].termName) + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[7].grpInfo) + ")" + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[7].idfo) + ")";
	QString termName9 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[8].termName) + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[8].grpInfo) + ")" + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[8].idfo) + ")";
	QString termName10 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[9].termName) + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[9].grpInfo) + ")" + u8"(" + QString::number(pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[9].idfo) + ")";*/


	QString termName1 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[0].termName);
	QString termName2 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[1].termName);
	QString termName3 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[2].termName);
	QString termName4 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[3].termName);
	QString termName5 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[4].termName);
	QString termName6 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[5].termName);
	QString termName7 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[6].termName);
	QString termName8 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[7].termName);
	/*QString termName9 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[8].termName);
	QString termName10 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[9].termName);*/


	//ui->btnP2p_1->setText(termName1);
	ui->btnP2p_2->setText(termName1);
	ui->btnP2p_3->setText(termName2);
	ui->btnP2p_4->setText(termName3);
	ui->btnP2p_5->setText(termName4);
	ui->btnP2p_6->setText(termName5);
	ui->btnP2p_7->setText(termName6);
	ui->btnP2p_8->setText(termName7);
	ui->btnP2p_9->setText(termName8);
	//ui->btnP2p_10->setText(termName10);

	//switch (pProcInfo->m_var.ctxSm.hg.p2pInfos.cnt)
	//{
	//case 1:
	//	ui->btnP2p_1->setVisible(true);
	//	
	//	break;
	//case 2:
	//	ui->btnP2p_1->setVisible(true);
	//	ui->btnP2p_2->setVisible(true);

	//	break;
	//case 3:
	//	ui->btnP2p_1->setVisible(true);
	//	ui->btnP2p_2->setVisible(true);
	//	ui->btnP2p_3->setVisible(true);

	//	break;
	//case 4:
	//	ui->btnP2p_1->setVisible(true);
	//	ui->btnP2p_2->setVisible(true);
	//	ui->btnP2p_3->setVisible(true);
	//	ui->btnP2p_4->setVisible(true);

	//	break;
	//case 5:
	//	ui->btnP2p_1->setVisible(true);
	//	ui->btnP2p_2->setVisible(true);
	//	ui->btnP2p_3->setVisible(true);
	//	ui->btnP2p_4->setVisible(true);
	//	ui->btnP2p_5->setVisible(true);

	//	break;
	//case 6:
	//	ui->btnP2p_1->setVisible(true);
	//	ui->btnP2p_2->setVisible(true);
	//	ui->btnP2p_3->setVisible(true);
	//	ui->btnP2p_4->setVisible(true);
	//	ui->btnP2p_5->setVisible(true);
	//	ui->btnP2p_6->setVisible(true);

	//	break;
	//case 7:
	//	ui->btnP2p_1->setVisible(true);
	//	ui->btnP2p_2->setVisible(true);
	//	ui->btnP2p_3->setVisible(true);
	//	ui->btnP2p_4->setVisible(true);
	//	ui->btnP2p_5->setVisible(true);
	//	ui->btnP2p_6->setVisible(true);
	//	ui->btnP2p_7->setVisible(true);

	//	break;
	//case 8:
	//	ui->btnP2p_1->setVisible(true);
	//	ui->btnP2p_2->setVisible(true);
	//	ui->btnP2p_3->setVisible(true);
	//	ui->btnP2p_4->setVisible(true);
	//	ui->btnP2p_5->setVisible(true);
	//	ui->btnP2p_6->setVisible(true);
	//	ui->btnP2p_7->setVisible(true);
	//	ui->btnP2p_8->setVisible(true);

	//	break;
	//case 9:
	//	ui->btnP2p_1->setVisible(true);
	//	ui->btnP2p_2->setVisible(true);
	//	ui->btnP2p_3->setVisible(true);
	//	ui->btnP2p_4->setVisible(true);
	//	ui->btnP2p_5->setVisible(true);
	//	ui->btnP2p_6->setVisible(true);
	//	ui->btnP2p_7->setVisible(true);
	//	ui->btnP2p_8->setVisible(true);
	//	ui->btnP2p_9->setVisible(true);

	//	break;
	//case 10:
	//	ui->btnP2p_1->setVisible(true);
	//	ui->btnP2p_2->setVisible(true);
	//	ui->btnP2p_3->setVisible(true);
	//	ui->btnP2p_4->setVisible(true);
	//	ui->btnP2p_5->setVisible(true);
	//	ui->btnP2p_6->setVisible(true);
	//	ui->btnP2p_7->setVisible(true);
	//	ui->btnP2p_8->setVisible(true);
	//	ui->btnP2p_9->setVisible(true);
	//	ui->btnP2p_10->setVisible(true);

	//	break;
	//default:
	//	break;
	//}


	if (pProcInfo->m_var.ctxSm.hg.p2pInfos.cnt > 1) {
		ui->btnP2p_2->setFocus();
	}

}


void CDlgP2p::on_timer_winMethod() {
	
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	if (pProcInfo->m_var.ctxSm.hg.bDone_p2p) {

		if (!_bLoad) {
			loadData();
		}
		_bLoad = true;
	}
}

//下箭头
void CDlgP2p::Infrared_down()
{

	if (chkFocus(this))return;
	this->focusNextPrevChild(true);
}

//上箭头
void CDlgP2p::Infrared_up()
{
	if (chkFocus(this))return;
	this->focusNextPrevChild(false);
}





CDlgP2p::~CDlgP2p()
{

	delete ui;
	if (m_pWinTimer)
	{
		delete m_pWinTimer;
		m_pWinTimer = nullptr;
	}

}
