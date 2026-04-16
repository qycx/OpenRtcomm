#include "WinSystemRule.h"

#include	"stdafx.h"
#include	"qyMcMainCommon_qt.h"


//
WinSystemRule::WinSystemRule(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

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


	



	ui.labcp->setText( QString::fromUtf16((char16_t*)pQyMc->cfg.qyMcTitle) );
	ui.labver->setText(QString::fromUtf16((char16_t*)tBuf) );
}

WinSystemRule::~WinSystemRule()
{
}
