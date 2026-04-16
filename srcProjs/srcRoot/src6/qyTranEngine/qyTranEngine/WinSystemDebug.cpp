#include "WinSystemDebug.h"
#include	"stdafx.h"
#include	"qyMcMainCommon_qt.h"



WinSystemDebug::WinSystemDebug(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

}

WinSystemDebug::~WinSystemDebug()
{
}


__declspec(dllexport) int viewQnmStatus();


void WinSystemDebug::on_pushButton_clicked() {
	//int i = 1;
	viewQnmStatus();

}
 