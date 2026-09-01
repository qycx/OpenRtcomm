

#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

#include	"DXUT/Core/DXUT.h"
#include	"DXUT/Optional/DXUTgui.h"
#include	"DXUT/Optional/SDKmisc.h"

//  2014/10/23
#include	"effects11\\inc\\D3dx11effect.h"


#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qySyncCommProc.h"
#include	"qmcVideoCapture_isCli.h"


#include	"isCliD3dCommon.h"
#include	"dlgD3dWall.h"

//
#include	"isCliHelpPublic.h"

//
#include	"cuboidTool.h"

#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
#include	"imgProcessPublic.h"
#include	"dlgTalkProc.h"
#include	"dynFuncs_d3dCall.h"
#include	"funcsForisCliHelp.h"
#include	"subtitlesCfg.h"

#include	"wallMemTmpl.h"




CWallMemTmpl::CWallMemTmpl(  )
{
	//memset(  &this->m_wallMemU,  0,  sizeof(  this->m_wallMemU  )  );
	return;
}

CWallMemTmpl::~CWallMemTmpl(  )
{
	return;
}
