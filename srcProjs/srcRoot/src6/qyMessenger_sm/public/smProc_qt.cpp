

#include	<qstring.h>


#include	"stdafx.h"

#define  __noDbg_new__



#include	<Windows.h>


#include	"qyMcMainCommon_qt.h"
#include <ctxQmc_sm.h>
#include	"myCmdParams_open.h"
#include	"myTChar.h"
#include	"hgCommProc.h"
#include	<qwidget.h>



//
int chkFocus(QWidget* pWnd)
{
	int  iErr = -1;

	//
	QWidget* pCtrl = pWnd->focusWidget();
	if (pCtrl) {
		int  iii = 0;
		if (!pCtrl->hasFocus()) {
			int  iiii = 0;
			//
			SetForegroundWindow((HWND)pWnd->winId());
			goto  errLabel;
		}
		else {
			int  jj = 0;
		}
	}
	else {
		int  ii = 0;
	}

	iErr = 0;
errLabel:

	//
	return  iErr;

}


