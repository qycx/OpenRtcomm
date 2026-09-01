

#include	"stdafx.h"

#include	<ShellAPI.h>
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qyCusResTemp.h"

#ifndef  __NOTSUPPORT_MULTIDOC__
#ifndef  __useQt__
	#include	"mainClient.h"
	#include	"mainFrm.h"
#endif
#endif
#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	"qmcVideoCapture_isCli.h"

#include	"myresource.h"



  int  getRect_talkers_ts(  HWND  hDlgWalls,  RECT  *  pRc  )
{

	int		iErr	=	-1;

	GetClientRect(  hDlgWalls,  pRc  );

	iErr  =  0;
//  errLabel:
	return  iErr;
}


