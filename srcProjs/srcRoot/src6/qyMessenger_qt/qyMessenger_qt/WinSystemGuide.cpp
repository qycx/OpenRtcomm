#include "WinSystemGuide.h"

WinSystemGuide::WinSystemGuide(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.label->setText(u8"请访问https://bbs.qycx.com 网站来获取帮助");
}


WinSystemGuide::~WinSystemGuide()
{
}
