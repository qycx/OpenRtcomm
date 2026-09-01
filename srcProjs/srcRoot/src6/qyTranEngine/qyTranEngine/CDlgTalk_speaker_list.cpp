#include "CDlgTalk_speaker_list.h"
#include	"stdafx.h"
#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc.h"
#include <isCliHelpPublic.h>
#include <help_getDlgTalkVar.h>
#include	"CDlgTalk_qt.h"
#include <QtCore/qmath.h>
#include <QIcon>


#define SHADOW_WIDTH 6 // 阴影边框宽度;
namespace {
	CDlgTalk_speaker_list* dlg = nullptr;
}

CDlgTalk_speaker_list::CDlgTalk_speaker_list(QWidget* parent)
	: WinBaseDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(this->windowFlags() | Qt::Dialog);
	this->setAttribute(Qt::WA_DeleteOnClose);

	//
	ui.label_staticInitiator->setText(u8"发起人:");


}

CDlgTalk_speaker_list::~CDlgTalk_speaker_list()
{
	dlg = nullptr;
}

void CDlgTalk_speaker_list::setContent(QString peerId) 
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	

	int i = 1;
	QY_MESSENGER_ID idInfo;
	idInfo.ui64Id = peerId.toInt();
	HWND  hTalk = null;
	if (findTalker(pQyMc, &idInfo, &hTalk)) goto  errLabel;
	CDlgTalk_qt* pTalk = (CDlgTalk_qt*)CDlgTalk_qt::find((WId)hTalk);
	if (pTalk == null)goto  errLabel;

	DLG_TALK_var* pm_var = pTalk->get_pm_var();
	if (pm_var == null)goto  errLabel;
	if (!isTalkerShadowMgr(pm_var->addr))  goto  errLabel;
	if (!pm_var->av.taskInfo.bTaskExists) goto  errLabel;
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo,pm_var->av.taskInfo.iIndex_taskInfo);
	QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
	if (pTc->common.uiType != CONST_taskDataType_conf)goto  errLabel;
	DLG_TALK_videoConference* videoConference = &pTc->videoConference;
	
	dlg->removeProessAll();
	for (i = 0; i < videoConference->usCntLimit_activeMems_from; i++) {
		DLG_TALK_videoConferenceActiveMemFrom* pActiveMem = &videoConference->activeMems_from[i];
		if (!pActiveMem->avStream.idInfo.ui64Id) continue;
		//
		traceLog((TCHAR*)_T("act[%d]: %I64u, %d,%d"), i, pActiveMem->avStream.idInfo.ui64Id,  pActiveMem->avStream.obj.resObj.uiObjType,pActiveMem->avStream.obj.resObj.usIndex_obj);

		QListWidgetItem* item = new QListWidgetItem( QString::number(i) + ": " + QString::fromStdWString(pActiveMem->desc) +  "  "+ QString::number(pActiveMem->avStream.idInfo.ui64Id) + "  " + QString::number(pActiveMem->avStream.obj.resObj.uiObjType) + "  " + QString::number(pActiveMem->avStream.obj.resObj.usIndex_obj));		
		
		QSize sz = item->sizeHint();
		sz.setHeight(24);
		item->setSizeHint(sz);//设置每个item的大小
		item->setIcon(QIcon(":/Resources/Images/WinMain/aio_spokes.png"));
		dlg->ui.listWidget->addItem(item);

	}
	//videoConference->
	//CONST_objType_mosaicStream_video

	//
	{
		QString qstr;
		qstr = QString::number(pm_var->av.taskInfo.idInfo_initiator.ui64Id);
		TCHAR dw[128];
		TCHAR bm[128];
		TCHAR syr[128];
		getTalkerDesc(pm_var->av.taskInfo.idInfo_initiator, null, null, 0, null, dw, mycountof(dw), bm, mycountof(bm), syr, mycountof(syr));
		qstr = QString::fromUtf16((char16_t*)dw) + QString::fromUtf16((char16_t*)bm) + QString::fromUtf16((char16_t*)syr) +  "("  +  QString::number(pm_var->av.taskInfo.idInfo_initiator.ui64Id)  +  ")";

		dlg->ui.label_initiator->setText(qstr);
	}


errLabel:
	return;

}

void CDlgTalk_speaker_list::getDialog(QWidget* parent) {
	if (!dlg)
	{
		dlg = new CDlgTalk_speaker_list(parent);
	}
}

void CDlgTalk_speaker_list::removeProessAll() {

	while (ui.listWidget->count() > 0)
	{
		QListWidgetItem* item = ui.listWidget->takeItem(0);
		delete item;
	}
}

void CDlgTalk_speaker_list::showWnd() {
	if (!dlg) return;
	dlg->show();
	dlg->activateWindow();

}

void CDlgTalk_speaker_list::closeDialog() {
	if (dlg) {
		dlg->close();
	}
}

void CDlgTalk_speaker_list::closeEvent(QCloseEvent* ev)
{
	this->hide();
	ev->accept();
}

void CDlgTalk_speaker_list::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QBrush(Qt::white));

	QColor color(0, 0, 0, 10);
	for (int i = 0; i < SHADOW_WIDTH; i++)
	{
		color.setAlpha(120 - qSqrt(i) * 40);
		painter.setPen(color);
		// 方角阴影边框;
		//painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
		// 圆角阴影边框;
		painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
	}
}