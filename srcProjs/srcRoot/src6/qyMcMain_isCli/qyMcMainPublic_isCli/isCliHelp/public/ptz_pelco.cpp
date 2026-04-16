

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include	"DlgPtzControl.h"

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



void dlg_YTCmd_pelco(  HWND  hDlg_ptz,  int  nResourceID  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
#if  0
	if  (  !pProcInfo->ptz.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pProcInfo->ptz.pStageLens;
#endif
	CDlgPtzControl  *  pDlg  =  (  CDlgPtzControl  *  )CWnd::FromHandlePermanent(  hDlg_ptz  );
	if  (  !pDlg  )  return;

	//  2014/09/13
	if  (  pDlg->m_var.bRemote  )  {
		return;
	}

	//  2014/10/14
	pDlg->m_var.dwTickCnt_lastPtzCmdRecvd  =  GetTickCount(  );

	//  2014/09/13
	if  (  !pDlg->m_var.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pDlg->m_var.pStageLens;
	
	int  m_nAddr  =  pDlg->m_var.m_nAddr;

	switch  (  nResourceID  )  {
			case  IDC_BUTTON_UP:
				  m_CStageLens.Up(  m_nAddr  );
				  break;
			case  IDC_BUTTON_DOWN:
				  m_CStageLens.Down(  m_nAddr  );
				  break;
			case  IDC_BUTTON_LEFT:
				  m_CStageLens.Left(  m_nAddr  );
				  break;
			case  IDC_BUTTON_RIGHT:
				  m_CStageLens.Right(  m_nAddr  );
				  break;
			case  IDC_BUTTON_TOP_LEFT:
				  m_CStageLens.TopLeft(  m_nAddr  );
				  break;
			case  IDC_BUTTON_TOP_RIGHT:
				  m_CStageLens.TopRight(  m_nAddr  );
				  break;
			case  IDC_BUTTON_BOTTOM_LEFT:
				  m_CStageLens.BottomLeft(  m_nAddr  );
				  break;
			case  IDC_BUTTON_BOTTOM_RIGHT:
				  m_CStageLens.BottomRight(  m_nAddr  );
				  break;

			//  2013/04/07
			case  IDC_BUTTON_noop:
				  m_CStageLens.Noop(  m_nAddr  );
				  break;

				  //
			case  IDC_BUTTON_ZOOM_IN:
				  m_CStageLens.ZoomMinus(  m_nAddr  );
				  break;
			case  IDC_BUTTON_ZOOM_OUT:
				  m_CStageLens.ZoomPlus(  m_nAddr  );
				  break;
				  
			//
			case  IDC_BUTTON_FOCUS_IN:
				  m_CStageLens.FocusMinus(  m_nAddr  );
				  break;
			case  IDC_BUTTON_FOCUS_OUT:
				  m_CStageLens.FocusPlus(  m_nAddr  );
				  break;

			case  IDC_BUTTON_IRIS_IN:
				  m_CStageLens.IrisMinus(  m_nAddr  );
				  break;
			case  IDC_BUTTON_IRIS_OUT:
				  m_CStageLens.IrisPlus(  m_nAddr  );
				  break;

			default:
					break;
		  
	}
}


