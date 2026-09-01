
#include	<tchar.h>


#include	<qwidget.h>
#include	"qyMcMainCommon_qt.h"
#include	"qmcFunc_qt.h"


//
int closeWnd_qt(QWidget* p,  LPCTSTR  hint )
{
	TCHAR  tBuf[128];

	if (!hint)  hint = _T("");
	if (!p)  return  -1;

	//
	_sntprintf(tBuf, mycountof(tBuf), _T("closeWnd_qt, %s"), hint);
	showInfo_open0(0, 0, tBuf);

	p->close();


	return  0;
}