
//
#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"ctxQmc.h"

#if 0
#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"

#ifdef  __SUPPORT_HTMLEDIT__
#include	"myHtmlEditCtrl.h"
#endif

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
//  #include	"DlgTalk.h"
#include	"dlgTalkProc.h"
#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"

#include	"qyComPortEx.h"

//  #include	"ptzSettings.h"

#include	"StageLens.h"

#include	"BitmapBtn.h"
//  #include	"CheckButton.h"

//  #include	"DlgProgress.h"
#include	"isCliHelpPublic.h"
#include	"FuncsforisCliHelp.h"
//#include	"qmcVideoCapture_dx.h"

///////////


#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
#include	<fcntl.h>
#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>


#include	"qmcDmoPublic.h"

#include	"qmcVideoCapture_dx.h"

#include	"myfourcc.h"
#include	"mywmcodecconst.h"

#include	"qmcCmdProc.h"

#include	"cPropertyBag.h"

#include	"qyCusResTemp.h"
#include	"qmcDirectX.h"


#include	"qmcShareMediaDevice.h"
#endif

//

void dlg_YTCmd_ipc(HWND  hDlg_ptz, int  iChannel,  int  ptzCmd,  unsigned  char  ucMouseStatus )
{
	CCtxQmc * pProcInfo = QY_GET_procInfo_isCli();

	switch (ptzCmd) {
	case  CONST_ptzCmd_left: 
	default:
	{
		//m_CStageLens.Left(m_nAddr);
		OnvifMsg_ptz  m = { 0 };
		m.uiType = CONST_qisMsgType_onvif;
		m.iSubtype = CONST_onvifMsg_subtype_ptz;
		m.iChannel = iChannel;
		m.ucCmd = ptzCmd;
		m.ucMouseStatus = ucMouseStatus;
		qisPipe_writeMsg(&m, sizeof(m), pProcInfo->m_ipcProc.pQisPipe);
		}
		break;


	}


}

