
//
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
#include	"dlgTalkProc.h"
#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"

#include	"qyComPortEx.h"

#include	"StageLens.h"

#include	"BitmapBtn.h"

#include	"isCliHelpPublic.h"
#include	"FuncsforisCliHelp.h"
#include	"ptzFunc.h"
#include	"objType_tmp.h"
#include	"isCliD3dPublic.h"

//
#include	"dlgShareDynBmpsProc.h"


//
//
//
__declspec(  dllexport  )  int  dlg_YTCmd_shareDynBmps(  HWND  hDlg_ptz,  int  nResourceID,  void  *  p0,  void  *  p1  )
{
	//
	CDlgPtzControl  *  pDlgPtz  =  (  CDlgPtzControl  *  )CWnd::FromHandlePermanent(  hDlg_ptz  );
	if  (  !pDlgPtz  )  return  -1;

	//
	if  (  pDlgPtz->m_var.bRemote  )  return  -1;

	//
	unsigned  int  uiObjType  =  pDlgPtz->m_var.local.resObj_camera.uiObjType;
	unsigned  short  usIndex_obj  =  pDlgPtz->m_var.local.resObj_camera.usIndex_obj;
	unsigned  short  usHelp_subIndex  =  pDlgPtz->m_var.local.resObj_camera.usHelp_subIndex;

	//
	if  (  !usIndex_obj  )  {
		showInfo_open0(  0,  0,  _T(  "dlg_YTCmd_shareDynBmps failed, usIndex_obj is 0"  )  );
		return -1;
	}

	//
	if  (  !p0  )  return  -1;
	DLG_shareDynBmps_var		*	pDlgShareDynBmpsVar  =  (  DLG_shareDynBmps_var  *  )p0;
	ShareDynBmps_threadProcInfo  *  pSt  =  &pDlgShareDynBmpsVar->shareDynBmpsThreadInfo;
	//
	if  (  !pSt->bQInited  )  return  -1;
	
	//
	DlgShareDynBmps_onvif  *  pOnvif  =  &pDlgShareDynBmpsVar->onvif;
	ShareDynBmps_ipDevsInfo  *  pIpDevs  =  &pOnvif->ipDevsInfo;
	//
	int  i;
	for  (  i  =  0;  i  <  mycountof(  pIpDevs->mems  );  i  ++  )  {
		 IP_dev  *  pMem  =  &pIpDevs->mems[i];
		 if  (  !pMem->iType  )  continue;
		 //
		 if  (  pMem->rule.usIndex_obj  ==  usIndex_obj  
			 &&  pMem->usHelp_subIndex  ==  usHelp_subIndex  ) 			 
		 {
			 break;
		 }
	}
	if  (  i  ==  mycountof(  pIpDevs->mems  )  )  {
		return  -1;
	}
	IP_dev  *  pIpDev  =  &pIpDevs->mems[i];


	//
	int  nCmd  =  0;
	if  (  ptz_resourceId2Cmd(  nResourceID,  &nCmd  )  )  {
		return  -1;
	}



	//
	OnvifMsg_ptz  msg  =  {0};
	msg.uiType  =  CONST_qisMsgType_onvif;
	msg.iSubtype  =  CONST_onvifMsg_subtype_ptz;
	//
	safeStrnCpy(  pIpDev->deviceServiceAddr,  msg.deviceServiceAddr,  mycountof(  msg.deviceServiceAddr  )  );
	//
	msg.ucCmd  =  nCmd;

	//
	if  (  q2PostMsgAndTrigger(  &msg,  sizeof(  msg  ),  &pSt->q2,  _T(  "dlg_ytcmd_shareDynBmps"  ))) {
		return  -1;
	}

	return  0;
}



