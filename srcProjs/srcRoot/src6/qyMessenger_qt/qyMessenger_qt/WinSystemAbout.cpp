#include "WinSystemAbout.h"
#include <QIcon>
#include	"stdafx.h"
#include	"qyMcMainCommon_qt.h"


//
WinSystemAbout::WinSystemAbout(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint); \
		setWindowTitle(u8"关于");

	CCtxQyMc* pQyMc = g_pQyMc;
	bool  bDebug = false;
	int  iVer;
	TCHAR  tBuf[128];
	//
	char verBuf[128];

	_snprintf(verBuf, sizeof(verBuf), "%s", qnmVerStr(pQyMc->iServiceId));
	if (verBuf[0] && verBuf[strlen(verBuf) - 1] == 'd')  bDebug = TRUE;
	iVer = atol(verBuf);
	//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s V%d.%02d.%02d%s"  ),  appName,  iVer  /  10000,  (  iVer  /  100  )  %  100,  iVer  %  100,  bDebug  ?  _T(  "Debug"  )  :  _T(  ""  )  );
	//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Ver: V%d.%02d.%02d%s"  ),  iVer  /  10000,  (  iVer  /  100  )  %  100,  iVer  %  100,  bDebug  ?  _T(  "Debug"  )  :  _T(  ""  )  );
	_sntprintf(tBuf, mycountof(tBuf), _T("Ver: V%d.%02d.%02d.%02d%s"), iVer / 1000000, (iVer / 10000) % 100, (iVer / 100) % 100, iVer % 100, bDebug ? _T("Debug") : _T(""));
	//
	_snprintf(verBuf, sizeof(verBuf), "%s", qnmDbVerStr(pQyMc->iServiceId));
	if (verBuf[0] && verBuf[strlen(verBuf) - 1] == 'd')  bDebug = TRUE;
	iVer = atol(verBuf);
	_sntprintf(tBuf, mycountof(tBuf), _T("%s, DbVer: %d.%02d.%02d%s"), tBuf, iVer / 10000, (iVer / 100) % 100, iVer % 100, bDebug ? _T("Debug") : _T(""));
	//SetDlgItemText(hDlg, IDC_STATIC_ver, CQyString(tBuf));



	//
	ui.labLine1->setText(QString::fromUtf16((char16_t*)pQyMc->cfg.qyMcTitle));
	//
	ui.labLine2->setText(QString::fromUtf16((char16_t*)tBuf));
	//ui.labLine3->setText(u8"200  Logn:3,ID:134   business");
	ui.labLine4->setText(u8"版权所有(C)2002北京清扬创新网络科技有限公司 www.qycx.com");
	setWindowIcon(QIcon(":/Resources/Images/Title/qmClientTitle.png"));
	//ui.BtnIcon->setIcon(QIcon(":/Resources/Images/Title/qmClientTitle.png"));
	ui.BtnIcon->setIcon(QIcon(":/Resources/Images/Login/qmClient.png"));
}

WinSystemAbout::~WinSystemAbout()
{
}
