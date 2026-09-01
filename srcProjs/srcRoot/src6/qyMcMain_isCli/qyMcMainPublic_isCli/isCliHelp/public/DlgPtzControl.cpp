// DlgPtzControl.cpp : implementation file
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
extern  QY_DMITEM  CONST_ptzTypeTable[];


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
void  exitPtz(  CComPortEx  **  ppPort  );



//
QY_DMITEM  CONST_ptzCmdTable_en[]  =
{	
	{		CONST_ptzCmd_up,			_T(  "up"  ),	},
	{		CONST_ptzCmd_down,			_T(  "down"  ),	},
	{		CONST_ptzCmd_left,			_T(  "left"  ),	},
	{		CONST_ptzCmd_right,			_T(  "right"  ),	},
	{		CONST_ptzCmd_topLeft,		_T(  "topLeft"  ),	},
	{		CONST_ptzCmd_topRight,		_T(  "topRight"  ),	},
	{		CONST_ptzCmd_bottomLeft,	_T(  "bottomLeft"  ),	},
	{		CONST_ptzCmd_bottomRight,	_T(  "bottomRight"  ),	},
	{		CONST_ptzCmd_noop,			_T(  "noop"  ),			},
	{		CONST_ptzCmd_focusIn,		_T(  "focus in"  ),		},
	{		CONST_ptzCmd_focusOut,		_T(  "focus out"  ),	},
	{		CONST_ptzCmd_irisIn,		_T(  "iris in"  ),		},
	{		CONST_ptzCmd_irisOut,		_T(  "iris out"  ),		},
	{		CONST_ptzCmd_zoomIn,		_T(  "zoom in"  ),		},
	{		CONST_ptzCmd_zoomOut,		_T(  "zoom out"  ),		},
	{		-1,		},
};

//  2014/09/13
QY_DMITEM  CONST_ptzCmd2ButtonTable[]  =
{	
	{		CONST_ptzCmd_up,			(  TCHAR  *  )IDC_BUTTON_UP,	},
	{		CONST_ptzCmd_down,			(  TCHAR  *  )IDC_BUTTON_DOWN,	},
	{		CONST_ptzCmd_left,			(  TCHAR  *  )IDC_BUTTON_LEFT,	},
	{		CONST_ptzCmd_right,			(  TCHAR  *  )IDC_BUTTON_RIGHT,	},
	{		CONST_ptzCmd_topLeft,		(  TCHAR  *  )IDC_BUTTON_TOP_LEFT,	},
	{		CONST_ptzCmd_topRight,		(  TCHAR  *  )IDC_BUTTON_TOP_RIGHT,	},
	{		CONST_ptzCmd_bottomLeft,	(  TCHAR  *  )IDC_BUTTON_BOTTOM_LEFT,	},
	{		CONST_ptzCmd_bottomRight,	(  TCHAR  *  )IDC_BUTTON_BOTTOM_RIGHT,	},
	{		CONST_ptzCmd_noop,			(  TCHAR  *  )IDC_BUTTON_noop,	},
	{		CONST_ptzCmd_focusIn,		(  TCHAR  *  )IDC_BUTTON_FOCUS_IN,	},
	{		CONST_ptzCmd_focusOut,		(  TCHAR  *  )IDC_BUTTON_FOCUS_OUT,	},
	{		CONST_ptzCmd_irisIn,		(  TCHAR  *  )IDC_BUTTON_IRIS_IN,	},
	{		CONST_ptzCmd_irisOut,		(  TCHAR  *  )IDC_BUTTON_IRIS_OUT,	},
	{		CONST_ptzCmd_zoomIn,		(  TCHAR  *  )IDC_BUTTON_ZOOM_IN,	},
	{		CONST_ptzCmd_zoomOut,		(  TCHAR  *  )IDC_BUTTON_ZOOM_OUT,	},
	{		-1,		},
};



//
#if  0  //  2015/09/20
 BOOL  isActive_comPort_ptz(  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;

	if  (  !pProcInfo->ptz.pComPort  )  return  FALSE;

	CComPortEx  *  pPort  =  (  CComPortEx  *  )pProcInfo->ptz.pComPort;
	DWORD			dwTickCnt  =  GetTickCount(  );

	if  (  !pPort->bThreadAlive(  )  )  return  FALSE;
	if  (  dwTickCnt  -  pPort->m_var.dwTickCnt_lastWrite  >  30000  )  return  FALSE;

	return  TRUE;

}
#endif

 int  initPtz(  COM_PORT_cfg  *  pCfg,  PTZ_mem_var  *  pm_var,  CComPortEx  **  ppPort  )
{
	int					iErr	=	-1;

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
#if  0
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
#endif

	CComPortEx	*	pPort  =  NULL;


#ifdef  __DEBUG__
		traceLog(  _T(  "initPtz enters"  )  );
#endif

	if  (  !pm_var  )  return  -1;
	if  (  !ppPort  )  return  -1;
	if  (  *ppPort  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "comPort exists. initPtz leaves"  )  );
		#endif
		showInfo_open0(  0,  0,  _T(  "initPtz failed, comPort exists"  )  );
		return  -1;
	}


	//
	pPort  =  new  CComPortEx;
	if  (  !pPort  )  goto  errLabel;

	//
	memset(  pm_var,  0,  sizeof(  pm_var[0]  )  );
	if  (  memcmp(  pCfg,  &pm_var->cfg,  sizeof(  pCfg[0]  )  )  )  memcpy(  &pm_var->cfg,  pCfg,  sizeof(  pm_var->cfg  )  );

	//  pProcInfo->ptz.m_var.m_nSpeed  =  23;

	//
	if  (  !pPort->bInitPort(  pQyMc->gui.hMainWnd,  pm_var->cfg.portNo,  pm_var->cfg.m_rate,  pm_var->cfg.m_parity,  pm_var->cfg.m_dataBit,  pm_var->cfg.m_stopBit,  EV_RXCHAR  |  EV_CTS,  512,  CONST_iComPortType_ptz,  0  )  )  goto  errLabel;

	if  (  !pPort->bStartMonitoring(  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "port.bStartMonitoring failed"  )  );
		goto  errLabel;
	}
	//  m_var.share_gps.var.dwTickCnt_start  =  GetTickCount(  );



	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		exitPtz(  &pPort  );
	}
	if  (  !iErr  )  {
		if  (  ppPort  )  *ppPort  =  pPort;
	}
#ifdef  __DEBUG__
		traceLog(  _T(  "initPtz leaves"  )  );
#endif
		//  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initPtz %s"  ),  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  );

	return  iErr;
}

void  exitPtz(  CComPortEx  **  ppPort  )
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;

#ifdef  __DEBUG__
		traceLog(  _T(  "exitPtz enters"  )  );
#endif

	if  (  !ppPort  ||  !*ppPort  )  return;
	//
	//if  (  pProcInfo->ptz.pComPort  )  
	{
		CComPortEx  *  pPort  =  (  CComPortEx  *  )*ppPort;	//  pProcInfo->ptz.pComPort;

		delete  pPort;
		//pProcInfo->ptz.pComPort  =  NULL;
		*ppPort  =  NULL;
	}
	
#ifdef  __DEBUG__
		traceLog(  _T(  "exitPtz leaves"  )  );
#endif

	return;
}

 int myPtz_write(  void  *  pDlgPtzControlParam,  char  *  buf,  unsigned  int  iLen  )
{
	int		iErr	=	-1;

	if  (  !pDlgPtzControlParam  )  return  -1;
	CDlgPtzControl  *  pDlgPtzControl  =  (  CDlgPtzControl  *  )pDlgPtzControlParam;

	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );

	//  2014/09/13
	if  (  pDlgPtzControl->m_var.bRemote  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "myPtzWrite failed, bRemote err"  )  );
		#endif
		goto  errLabel;
	}

	//
	if  (  !pDlgPtzControl->m_var.bRemote  )  {

		if  (  !pDlgPtzControl->m_var.pComPort  )  goto  errLabel;

		CComPortEx  *  pPort  =  (  CComPortEx  *  )pDlgPtzControl->m_var.pComPort;

		if  (  !pPort->bThreadAlive(  )  )  goto  errLabel;

		if  (  pPort->WriteToPort(  (  BYTE  *  )buf,  iLen  )  )  goto  errLabel;

		}
#if  0  //  2014/09/13.
	else  {
		  //  2012/08/06
		  PTZ_control_cmd	req;
		  MACRO_prepareForTran(  );

		  MIS_CNT	*	pMisCnt  =  pFuncs->pf_getMisCntByName(  0,  0,  _T(  ""  )  );
		  if  (  !pMisCnt  )  goto  errLabel;

		unsigned  int			uiChannelType	=	CONST_channelType_media;

#ifdef  __DEBUG__
		uiChannelType  =  0;
		traceLog(  _T(  "Note: send ptz req through talking channel, just for debug"  )  );
#endif

		//
		memset(  &req,  0,  sizeof(  req  )  );
		req.uiType  =  CONST_imCommType_ptzControlCmd;

		if  (  iLen  >  sizeof(  req.v0260.cmdBuf  )  )  goto  errLabel;
		memcpy(  req.v0260.cmdBuf,  buf,  iLen  );
		req.v0260.uiLen  =  iLen;


		//
		if  (  pFuncs->pf_postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_outputTask,  0,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  (  char  *  )&req,  sizeof(  req  ),  0,  &pDlgPtzControl->m_var.idInfo_remote,  uiChannelType,  NULL,  FALSE  )  )  traceLogA(  "postMsg2Mgr_mc failed"  );
	}
#endif

	iErr  =  0;

errLabel:

	return  iErr;
}


 


 //
 __declspec(  dllexport  )  int  ptz_resourceId2Cmd(  int  nResourceID,  int  *  pnCmd  )
 {	 	
	int  iErr  =  -1;
	//	 
	int  nCmd  =  0;

	//
	QY_DMITEM  *  pItem;
	for  (  pItem  =  CONST_ptzCmd2ButtonTable;  pItem->type  !=  -1;  pItem  ++  )  {
		if  (  (  int  )pItem->des  ==  nResourceID  )  {
			nCmd  =  pItem->type;
		}
	}

	iErr  =  0;

errLabel:

	if  (  pnCmd  )  {
		*pnCmd  =  nCmd;
	}

	return  iErr;
 }






 //
__declspec(  dllexport  )  int doRemotePtzCmd(  void  *  p0,  PTZ_control_cmd  *  pReq,  PARAM_viewLocalPtzControl  *  pParam,  QIS_ptz_wnd  *  pPtzWnd  )  
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr	=	-1;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	TCHAR				tBuf[128]	=	_T(  ""  );
	if  (  !pProcInfo  )  return  -1;

	//
	unsigned  int  uiObjType_camera  =  pReq->cmdInfo.obj.uiObjType;
	//
	//QIS_ptz_wnd  *  pPtzWnd  =  &pProcInfo->ptzWnd;

#ifdef  __DEBUG__
		//
		traceLog(  _T(  "doRemotePtzCmd: cmd %d %s"  ),  (  int  )pReq->cmdInfo.ucCmd,  qyGetDesByType1(  CONST_ptzCmdTable_en,  pReq->cmdInfo.ucCmd  )  );
#endif
		//



		//
		if  (  !IsWindow(  pPtzWnd->hWnd_localPtzControl  )  )  {
			HWND hParent  =  pQyMc->gui.hMainWnd;
			BOOL  bManual  =  FALSE;					//  2014/10/14
			//
			viewLocalPtzControl(  hParent,  bManual,  uiObjType_camera,  pReq->cmdInfo.obj.usIndex_obj,  pReq->cmdInfo.obj.usHelp_subIndex,  pParam,  pPtzWnd  );
			if  (  !IsWindow(  pPtzWnd->hWnd_localPtzControl  )  )  goto  errLabel;
		}
		//
		HWND  hWnd_ptz  =  pPtzWnd->hWnd_localPtzControl;
		CDlgPtzControl			*		pDlg					=	NULL;
		pDlg  =  (  CDlgPtzControl  *  )CWnd::FromHandlePermanent(  hWnd_ptz  );
		if  (  !pDlg  )  goto  errLabel;
		//
		int  nID  =  0;
		nID  =  (  int  )qyGetDesByType(  CONST_ptzCmd2ButtonTable,  pReq->cmdInfo.ucCmd  );
		//
		//
		int  lStep_percent  =  0;
		//
		lStep_percent  =  pDlg->m_slider_speed.GetPos(  );
		//
#ifdef  __DEBUG__
		traceLog(  _T(  "Not finished: "  )  );
#endif
		//
		dlg_YTCmd(  hWnd_ptz,  nID,  lStep_percent,  pReq->cmdInfo.ucMouseStatus,  pReq->cmdInfo.iChannel,  pReq  );


	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doRemotePtzCmd failed"  )  );

	}
	return  iErr;
}


//
__declspec(  dllexport  ) int  viewRemotePtzControl(  HWND  hParent,  HWND  hCurTalk  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr	=	-1;

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	//  MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	//  if  (  !pProcInfo  )  return  -1;

	CDlgPtzControl			*		pDlg					=	NULL;
	RECT							rect;

	HWND					*		phWnd_lv				=	NULL;

	CHelp_getDlgTalkVar  help_getDlgTalkVar;
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;

	DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hCurTalk  );
	if  (  !pCurVar  )  return  -1;
	DLG_TALK_var  *  pMgrVar  =  NULL;
	HWND	hMgr	=	NULL;

	hMgr  =  hCurTalk;
	pMgrVar  =  pCurVar;
	if  (  !isTalkerShadowMgr(  pCurVar->addr  )  )  {
		  TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pCurVar->pShadowInfo;
		  if  (  !pShadow  )  goto  errLabel;
		  hMgr  =  pShadow->hMgr;
		  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
	}
	if  (  !pMgrVar  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;
		
	//
	phWnd_lv  =  &pCurVar->ptzControl.hWnd_ptzControl;

	//
	if  (  phWnd_lv  )  {
		if  (  IsWindow(  *phWnd_lv  )  )  {
			MACRO_SetForegroundWindow(  *phWnd_lv  );
			iErr  =  0;  goto  errLabel;
		}

		*phWnd_lv  =  NULL;
	}

	//
	if  (  pShadowMgr->ptz.hWnd_ptzControl  )  {
		if  (  IsWindow(  pShadowMgr->ptz.hWnd_ptzControl  )  )  {
			SendMessage(  pShadowMgr->ptz.hWnd_ptzControl,  WM_CLOSE,  0,  0  );
		}
		if  (  IsWindow(  pShadowMgr->ptz.hWnd_ptzControl  )  )  goto  errLabel;
	}
	memset(  &pMgrVar->ptzControl,  0,  sizeof(  pMgrVar->ptzControl  )  );

	//
	//		
	DYN_BMP_RULE				dynBmpRule_selected;		
	//			
	memset(  &dynBmpRule_selected,  0,  sizeof(  dynBmpRule_selected  )  );
	
	//
	{	
		//  2012/08/06
		PTZ_control_req	req;
		MACRO_prepareForTran(  );

		unsigned  int			uiChannelType	=	CONST_channelType_media;

		if  (  !canRemotePtzControl(  pProcInfo  )  )  {
			myMessageBox(  hParent,  _T(  "No video"  ),  _T(  "www.qycx.com"  ),  MB_OK  );
			goto  errLabel;
		}

		//  2016/07/19
		int  i;
		BOOL  bExists_rtsp  =  FALSE;
		for  (  i  =  0;  i  <  mycountof(  pShadowMgr->talkerDynBmps  );  i  ++  )  {
			TALKER_dynBmp  *  pMem  =  &pShadowMgr->talkerDynBmps[i];
			if  (  pMem->taskInfo.iTaskId  )  {
				if  (  pMem->dynBmpRule.dynBmp.resObj.uiObjType  ==  CONST_objType_rtspStream  )  {
					bExists_rtsp  =  TRUE;
					break;
				}
			}
		}

		//
		if  (  bExists_rtsp  )  {								
			DLG_guiDataParam_objs		param;
			
							
			//			
			memset(  &param,  0,  sizeof(  param  )  );				
			param.uiType  =  CONST_objType_selectRemotePtz;
			param.hCurTalk  =  hCurTalk;
			param.pCurVar  =  pCurVar;							//  2013/06/10
			param.pMgrVar  =  pMgrVar;
			param.pObjBuf_selected  =  &dynBmpRule_selected.dynBmp;			//  2014/05/15
			param.uiSize_pObjBuf_selected  =  sizeof(  dynBmpRule_selected  );
				  

			//  2015/06/05			
			HWND  hParent  =  hCurTalk;
			if  (  bApp_ts_3d(  pQyMc  )  )  {
				GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
				if  (  !pGBuf  )  goto  errLabel;
				if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  goto  errLabel;
				hParent  =  pGBuf->hWall_d3d;				  
			}


			//			
			if  (  showDlgObjs(  pQyMc->g_hInst,  hParent,  &param  )  )  {					
				goto  errLabel;				
			}

		}

		//
#ifdef  __DEBUG__
		uiChannelType  =  0;
		traceLog(  _T(  "Note: send ptz req through talking channel, just for debug"  )  );
#endif

#if 0
		if (0) {
			//
			memset(&req, 0, sizeof(req));
			req.uiType = CONST_imCommType_ptzControlReq;


			//  2010/08/14
			pFuncs->pf_startProgress(&pQyMc->gui.progress, uiTranNo);

			//
			if (postMsg2Mgr_mc(pMgrVar->pMisCnt, NULL, CONST_misMsgType_outputTask, 0, CONST_qyCmd_sendMedia, tStartTran, uiTranNo, 0, (char*)&req, sizeof(req), 0, &pMgrVar->addr.idInfo, uiChannelType, NULL, FALSE))  traceLogA("postMsg2Mgr_mc failed");

			//
			if (showProgress(&pQyMc->gui.progress, &pQyMc->cusRes, hParent, _T("Please waiting"), NULL, 30, -1, uiTranNo) != IDOK) {
				goto  errLabel;
			}
		}
#endif

	}


	
	//
	pDlg  =  new  CDlgPtzControl(  CWnd::FromHandle(  hParent  )  );
	if  (  !pDlg  )  goto  errLabel;

	//
	pDlg->m_var.bRemote   =  TRUE;
	pDlg->m_var.remote.hDlgTalk  =  hCurTalk;
	//
	//  pDlg->m_var.idInfo_remote.ui64Id  =  pMgrVar->addr.idInfo.ui64Id;
	pDlg->m_var.remote.remoteCamera.qisResObj.idInfo.ui64Id  =  pMgrVar->addr.idInfo.ui64Id;				//  2016/07/19
#if  0
	pDlg->m_var.remote.remoteCamera.qisResObj.resObj.uiObjType  =  dynBmpRule_selected.dynBmp.resObj.uiObjType;
	pDlg->m_var.remote.remoteCamera.qisResObj.resObj.usIndex_obj  =  dynBmpRule_selected.dynBmp.resObj.usIndex_obj;  
#endif
	//  2016/07/24
	pDlg->m_var.remote.remoteCamera.qisResObj.resObj  =  dynBmpRule_selected.dynBmp.resObj;
	//
	safeTcsnCpy(  dynBmpRule_selected.name,  pDlg->m_var.remote.remoteCamera.name,  mycountof(  pDlg->m_var.remote.remoteCamera.name  )  );
	safeTcsnCpy(  dynBmpRule_selected.cusName,  pDlg->m_var.remote.remoteCamera.cusName,  mycountof(  pDlg->m_var.remote.remoteCamera.cusName  )  );
	//
	pDlg->m_var.m_nAddr  =  pMgrVar->ptzControl.cfg.nAddr;
	pDlg->m_var.m_pelcoType  =  pMgrVar->ptzControl.cfg.nPelcoType;
	lstrcpyn(  pDlg->m_var.tHint,  pMgrVar->ptzControl.tHint,  mycountof(  pDlg->m_var.tHint  )  );
	

	//  2015/09/18
	pDlg->m_var.m_nID  =  IDD_ptzControl_remote;


	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	pDlg->ShowWindow(  SW_SHOW  );


	//
	if  (  phWnd_lv  )  *phWnd_lv  =  pDlg->m_hWnd;
	pShadowMgr->ptz.hWnd_ptzControl  =  pDlg->m_hWnd;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}



	return  iErr;
}




//
__declspec(  dllexport  ) int  viewLocalPtzControl(  HWND  hParent,  BOOL  bManual,  unsigned  int  uiObjType_camera,  unsigned  short  usIndex_obj,  unsigned  short  usHelp_subIndex,  PARAM_viewLocalPtzControl  *  pParam,  QIS_ptz_wnd  *  pPtzWnd  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr	=	-1;

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	CDlgPtzControl			*		pDlg					=	NULL;
	RECT							rect;

	HWND					*		phWnd_lv				=	NULL;

	//
	//QIS_ptz_wnd  *  pPtzWnd  =  &pProcInfo->ptzWnd;


	//
	phWnd_lv  =  &pPtzWnd->hWnd_localPtzControl;

	if  (  phWnd_lv  )  {
		if  (  IsWindow(  *phWnd_lv  )  )  {
			if  (  bManual  )  {
				//
				CDlgPtzControl  *  tmp_p  =  (  CDlgPtzControl  *  )CDlgPtzControl::FromHandlePermanent(  *phWnd_lv  );
				if  (  !tmp_p  )  {
					goto  errLabel;
				}
				if  (  !tmp_p->m_var.local.bManual  )  {
					tmp_p->m_var.local.bManual  =  bManual;
				}
				//
				MACRO_SetForegroundWindow(  *phWnd_lv  );
			}
			iErr  =  0;  goto  errLabel;
		}

		*phWnd_lv  =  NULL;
	}

		//
	pDlg  =  new  CDlgPtzControl(  CWnd::FromHandle(  hParent  )  );
	if  (  !pDlg  )  goto  errLabel;

	//  2014/10/14
	if  (  bManual  )  {
		pDlg->m_var.local.bManual  =  bManual;
	}
	//  2016/07.20
	pDlg->m_var.local.resObj_camera.uiObjType  =  uiObjType_camera;
	pDlg->m_var.local.resObj_camera.usIndex_obj  =  usIndex_obj;
	pDlg->m_var.local.resObj_camera.usHelp_subIndex  =  usHelp_subIndex;
	//
	if  (  pParam  )  pDlg->m_var.local.param  =  *pParam;
	//  2016/07/20
	pDlg->m_var.local.pPtzWnd  =  pPtzWnd;
	//
	//  2015/09/18
	pDlg->m_var.m_nID  =  IDD_ptzControl_local;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	if  (  bManual  )  {
		pDlg->ShowWindow(  SW_SHOW  );
	}


	//
	if  (  phWnd_lv  )  *phWnd_lv  =  pDlg->m_hWnd;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}



	return  iErr;
}


// CDlgPtzControl dialog

IMPLEMENT_DYNAMIC(CDlgPtzControl, CDialog)

CDlgPtzControl::CDlgPtzControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPtzControl::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.m_pParent = pParent;
	//m_var.m_nID = CDlgPtzControl::IDD;

	//  2015/09/18
	//m_var.iPtzType  =  DEFAULT_ptzType;

}

CDlgPtzControl::~CDlgPtzControl()
{
}


 BOOL CDlgPtzControl::Create(const RECT& rect)
{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProc		=	NULL;

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): 在创建对话框之前应先设置初始数据"  );
		return  FALSE;
	}
	*/

	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	if  (  !m_var.m_nID  )  {
		#ifdef  __DEBUG__
				MACRO_qyAssert(  0,  _T(  "ptzControl Create failed, m_nID is 0"  )  );
		#endif
		return  FALSE;
	}
	

	//
	if  (  !CDialog::Create(  this->m_var.m_nID, m_var.m_pParent  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  CDlgPtzControl::bQuitDlg(  )		
{		
	traceLogA(  "CDlgListView_db(  )::bQuitDlg enters"  );


	//  2009/05/01
	DestroyWindow();				  
		
//  errLabel:

	traceLogA(  "CDlgListView_db(  )::bQuitDlg leaves"  );

	return  TRUE;
}

 void  CDlgPtzControl::InitBtn(  )
 {
	BOOL  bRet;
	QY_MC		*  pQyMc		=  QY_GET_GBUF(  );

	bRet  =  m_btnUp.SubclassDlgItem(  IDC_BUTTON_UP,  this  );
	//  bRet  =  m_btnUp.LoadBitmaps(  IDB_BITMAP_up,  IDB_BITMAP_up_sel  );
	//  m_btnUp.SizeToContent(  );
	m_btnUp.setToolTipText(  _T(  "Up"  )  );

	m_btnDown.SubclassDlgItem(  IDC_BUTTON_DOWN,  this  );
	//  m_btnDown.LoadBitmaps(  IDB_BITMAP_down,  IDB_BITMAP_down_sel  );
	//  m_btnDown.SizeToContent(  );
	m_btnDown.setToolTipText(  _T(  "Down"  )  );

	m_btnLeft.SubclassDlgItem(  IDC_BUTTON_LEFT,  this  );
	//  m_btnLeft.LoadBitmaps(  IDB_BITMAP_left,  IDB_BITMAP_left_sel  );
	//  m_btnLeft.SizeToContent(  );
	m_btnLeft.setToolTipText(  _T(  "Left" )  );

	m_btnRight.SubclassDlgItem(  IDC_BUTTON_RIGHT,  this  );
	//  m_btnRight.LoadBitmaps(  IDB_BITMAP_right,  IDB_BITMAP_right_sel  );
	//  m_btnRight.SizeToContent(  );
	m_btnRight.setToolTipText(  _T(  "right" )  );

	m_btnTopLeft.SubclassDlgItem(  IDC_BUTTON_TOP_LEFT,  this  );
	//  m_btnTopLeft.LoadBitmaps(  IDB_BITMAP_topLeft,  IDB_BITMAP_topLeft_sel  );
	//  m_btnTopLeft.SizeToContent(  );
	m_btnTopLeft.setToolTipText(  _T(  "topLeft" )  );

	m_btnTopRight.SubclassDlgItem(  IDC_BUTTON_TOP_RIGHT,  this  );
	//  m_btnTopRight.LoadBitmaps(  IDB_BITMAP_topRight,  IDB_BITMAP_topRight_sel  );
	//  m_btnTopRight.SizeToContent(  );
	m_btnTopRight.setToolTipText(  _T(  "topRight" )  );

	m_btnBottomLeft.SubclassDlgItem(  IDC_BUTTON_BOTTOM_LEFT,  this  );
	//  m_btnBottomLeft.LoadBitmaps(  IDB_BITMAP_bottomLeft,  IDB_BITMAP_bottomLeft_sel  );
	//  m_btnBottomLeft.SizeToContent(  );
	m_btnBottomLeft.setToolTipText(  _T(  "bottomLeft" )  );

	m_btnBottomRight.SubclassDlgItem(  IDC_BUTTON_BOTTOM_RIGHT,  this  );
	//  m_btnBottomRight.LoadBitmaps(  IDB_BITMAP_bottomRight,  IDB_BITMAP_bottomRight_sel  );
	//  m_btnBottomRight.SizeToContent(  );
	m_btnBottomRight.setToolTipText(  _T(  "bottomRight" )  );

	//  2013/04/07
	m_btnNoop.SubclassDlgItem(  IDC_BUTTON_noop,  this  );
	m_btnNoop.setToolTipText(  _T(  "no op"  )  );

	//
	m_btnIrisIn.SubclassDlgItem(  IDC_BUTTON_IRIS_IN,  this  );
	//  m_btnIrisIn.LoadBitmaps(  IDB_BITMAP_plus,  IDB_BITMAP_plus_sel  );
	//  m_btnIrisIn.SizeToContent(  );
	m_btnIrisIn.setToolTipText(  _T(  "iris (+) plus"  )  );

	m_btnIrisOut.SubclassDlgItem(  IDC_BUTTON_IRIS_OUT,  this  );
	//  m_btnIrisOut.LoadBitmaps(  IDB_BITMAP_minus,  IDB_BITMAP_minus_sel  );
	//  m_btnIrisOut.SizeToContent(  );
	m_btnIrisOut.setToolTipText(  _T(  "iris (-) minus"  )  );

	m_btnFocusIn.SubclassDlgItem(  IDC_BUTTON_FOCUS_IN,  this  );
	//  m_btnFocusIn.LoadBitmaps(  IDB_BITMAP_plus,  IDB_BITMAP_plus_sel  );
	//  m_btnFocusIn.SizeToContent(  );
	m_btnFocusIn.setToolTipText(  _T(  "focus (+)  plus "  )  );

	m_btnFocusOut.SubclassDlgItem(  IDC_BUTTON_FOCUS_OUT,  this  );
	//  m_btnFocusOut.LoadBitmaps(  IDB_BITMAP_minus,  IDB_BITMAP_minus_sel  );
	//  m_btnFocusOut.SizeToContent(  );
	m_btnFocusOut.setToolTipText(  _T(  "focus (-)  minus "  )  );

	m_btnZoomIn.SubclassDlgItem(  IDC_BUTTON_ZOOM_IN,  this  );
	//  m_btnZoomIn.LoadBitmaps(  IDB_BITMAP_plus,  IDB_BITMAP_plus_sel  );
	//  m_btnZoomIn.SizeToContent(  );
	m_btnZoomIn.setToolTipText(  _T(  "zoom (+) plus"  )  );

	m_btnZoomOut.SubclassDlgItem(  IDC_BUTTON_ZOOM_OUT,  this  );
	m_btnZoomOut.setToolTipText(  _T(  "zoom (-) minus"  )  );

#if  0
	m_cbtnAutoScan.SubclassDlgItem(  IDC_BUTTON_AUTO_SCAN,  this  );
	m_cbtnAutoScan.setBmpID(  IDB_BITMAP_autoScan,  IDB_BITMAP_autoScan_sel  );
	m_cbtnAutoScan.setToolTipText(  _T(  "autoscan "  )  );

	m_cbtnRainBrush.SubclassDlgItem(  IDC_BUTTON_RAIN_BRUSH,  this  );
	m_cbtnRainBrush.setBmpID(  IDB_BITMAP_rainBrush,  IDB_BITMAP_rainBrush_sel  );
	m_cbtnRainBrush.setToolTipText(  _T(  "rainBrush"  ) );

	m_cbtnSearchLight.SubclassDlgItem(  IDC_BUTTON_SEARCH_LIGHT,  this  );
	m_cbtnSearchLight.setBmpID(  IDB_BITMAP_searchLight,  IDB_BITMAP_searchLight_sel  );
	m_cbtnSearchLight.setToolTipText(  _T(  "searchLight"  )  );
#endif

	m_buStatus_autoScan.SubclassDlgItem(  IDC_BUTTON_AUTO_SCAN,  this  );
	m_buStatus_autoScan.m_text  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_autoScan  );

	m_buStatus_rainBrush.SubclassDlgItem(  IDC_BUTTON_RAIN_BRUSH,  this  );
	m_buStatus_rainBrush.m_text  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rainBrush  );

	m_buStatus_searchLight.SubclassDlgItem(  IDC_BUTTON_SEARCH_LIGHT,  this  );
	m_buStatus_searchLight.m_text  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_searchLight  );

 }


 int  CDlgPtzControl::refreshStatus(  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	TCHAR				tBuf[128]	=	_T(  ""  );
	TCHAR				comBuf[128]	=	_T(  ""  );
	TCHAR				memoBuf[128]	=	_T(  ""  );
	QY_MC	*	pQyMc		=	QY_GET_GBUF(  );
	CQyString			rootKeyStr;
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	rootKeyStr  =  CQyString(  tBuf  );

	if  (  !m_var.bRemote  )  {
		switch  (  m_var.iPtzType  )  {
				case  CONST_ptzType_usb:
					  _sntprintf(  comBuf,  mycountof(  comBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_ptzTypeTable,  m_var.iPtzType  )  );  
					  break;
				case  CONST_ptzType_serialPort:  {
					  if  (  !m_var.pComPort  )  _sntprintf(  comBuf,  mycountof(  comBuf  ),  _T(  "Com can't open"  )  );
					  else  {
						    CComPortEx  *  pPort  =  (  CComPortEx  *  )m_var.pComPort;
							_sntprintf(  comBuf,  mycountof(  comBuf  ),  _T(  "COM%d open"  ),  pPort->m_nPortNo  );		
					  }
					  }
					  break;
				default:
						break;
		}
		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. %s"  ),  comBuf,  _T(  ""  )  );  //  pProcInfo->ptz.m_var.cfg.tHint"  )  );
	}
	else  {
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  m_var.tHint  );
	}

	SetDlgItemText(  IDC_STATIC_hint,  tBuf  );

errLabel:
	return  0;
}

 int  CDlgPtzControl::sizeAllControls(  )
 {
	 int		iErr	=	-1;
	 RECT		rc, rcBtn;
	 HWND		hDlg	=	this->m_hWnd;
	 int		iw,ih;
	 float		fx,fy;
	 HWND		hBtn;


/*

	 ::GetClientRect(  hDlg,  &rc  );
	 iw  =  rc.right  -  rc.left;
	 ih  =  rc.bottom  -  rc.top;

	 if  ( !m_var.iw_org  ||  !m_var.ih_org  )  goto  errLabel;
	 fx  =  1.  *  iw  /  m_var.iw_org;
	 fy  =  1.  *  ih  /  m_var.ih_org;

	 hBtn  =  ::GetDlgItem(  hDlg,  IDC_BUTTON_UP );
	 ::GetWindowRect(  hBtn,  &rcBtn  );
	 ::MoveWindow(  hDlg,  rcBtn.right  -  rcBtn.left,  rcBtn.bottom  -  rcBtn.top,  (  rcBtn.right  -  rcBtn.left  )  *  fx,  (  rcBtn.bottom  -  rcBtn.top  )  *  fy,  TRUE  );
	 */

	iErr  =  0;
errLabel:
	return  iErr;
 }

void CDlgPtzControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_speed, m_slider_speed);
	DDX_Control(pDX, IDC_EDIT_PRE, m_edit_nPrePoint);
}

BOOL CDlgPtzControl::OnCommand(  WPARAM  wParam,  LPARAM  lParam  )
{
	UINT  nID  =  LOWORD(  wParam  );
	HWND  hWndCtrl  =  (  HWND  )lParam;
	int  nCode  =  HIWORD(  wParam  );

	if  (  (  nID  == IDC_BUTTON_AUTO_SCAN  )  ||  (  nID  ==  IDC_BUTTON_RAIN_BRUSH  )  ||  (  nID  ==  IDC_BUTTON_SEARCH_LIGHT  )  )
	{
		if  (  nCode  ==  BN_CLICKED  )
			OnChangeStatus(  nID  );
		//
		switch  (  nID  )  {
				case  IDC_BUTTON_AUTO_SCAN:
					  m_var.m_bnDown_autoScan  =  this->m_buStatus_autoScan.m_nFlag  ?  TRUE  :  FALSE;
					  break;
				case  IDC_BUTTON_RAIN_BRUSH:
					  m_var.m_bnDown_rainBrush  =  this->m_buStatus_rainBrush.m_nFlag  ?  TRUE  :  FALSE;
					  break;
				case  IDC_BUTTON_SEARCH_LIGHT:
					  m_var.m_bnDown_searchLight  =  this->m_buStatus_searchLight.m_nFlag  ?  TRUE  :  FALSE;
					  break;
				default:
						break;
		}
	
		
		OutputDebugString(  _T(  "OnCommand\n"  )  );


		//
		dlg_YTCHECKBtn(  m_hWnd,  nID  );
	}

	return  CDialog::OnCommand(  wParam,  lParam  );
}


BEGIN_MESSAGE_MAP(CDlgPtzControl, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_ptzSettings, &CDlgPtzControl::OnBnClickedButtonptzsettings)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_speed, &CDlgPtzControl::OnNMReleasedcaptureSliderspeed)
	ON_EN_CHANGE(IDC_EDIT_PRE, &CDlgPtzControl::OnEnChangeEditPre)
	ON_BN_CLICKED(IDC_BUTTON_PRE_GO, &CDlgPtzControl::OnBnClickedButtonPreGo)
	ON_BN_CLICKED(IDC_BUTTON_PRE_SET, &CDlgPtzControl::OnBnClickedButtonPreSet)
	ON_BN_CLICKED(IDC_BUTTON_PRE_CLEAR, &CDlgPtzControl::OnBnClickedButtonPreClear)
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()







// CDlgPtzControl message handlers

BOOL CDlgPtzControl::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int			iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	RECT		rc;
	HWND		hDlg	=	this->m_hWnd;

	//::SetWindowPos(  m_hWnd,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOMOVE  |  SWP_NOSIZE  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	DLG_guiData_ptzControl		*  p	= &m_var.guiData;

	::GetClientRect(  hDlg,  &rc  );
	p->iw_org  =  rc.right  -  rc.left;
	p->ih_org  =  rc.bottom  -  rc.top;

	if  (  !p->iw_org  ||  !p->ih_org  )  goto  errLabel;

	//  header
	p->iIDC_BUTTON_ptzSettings  =  IDC_BUTTON_ptzSettings;
	p->iIDC_STATIC_hint  =  IDC_STATIC_hint;
	p->iIDC_STATIC_speed  =  IDC_STATIC_speed;
	p->iIDC_SLIDER_speed  =  IDC_SLIDER_speed;
	//  body
	p->iIDC_BUTTON_TOP_LEFT  =  IDC_BUTTON_TOP_LEFT;
	p->iIDC_BUTTON_UP  =  IDC_BUTTON_UP;
	p->iIDC_BUTTON_TOP_RIGHT  =  IDC_BUTTON_TOP_RIGHT;
				 
	p->iIDC_BUTTON_LEFT  =  IDC_BUTTON_LEFT;
	p->iIDC_BUTTON_AUTO_SCAN  =  IDC_BUTTON_AUTO_SCAN;
	p->iIDC_BUTTON_RIGHT  =  IDC_BUTTON_RIGHT;
					 
	p->iIDC_BUTTON_BOTTOM_LEFT  =  IDC_BUTTON_BOTTOM_LEFT;
	p->iIDC_BUTTON_DOWN  =  IDC_BUTTON_DOWN;
	p->iIDC_BUTTON_BOTTOM_RIGHT  =  IDC_BUTTON_BOTTOM_RIGHT;

	p->iIDC_BUTTON_noop  =  IDC_BUTTON_noop;					//  2013/04/07
	
	p->iIDC_BUTTON_FOCUS_OUT  =  IDC_BUTTON_FOCUS_OUT;
	p->iIDC_BUTTON_IRIS_OUT  =  IDC_BUTTON_IRIS_OUT;
	p->iIDC_BUTTON_ZOOM_OUT  =  IDC_BUTTON_ZOOM_OUT;
	
	p->iIDC_STATIC_focus  =  IDC_STATIC_focus;
	p->iIDC_STATIC_iris  =  IDC_STATIC_iris;
	p->iIDC_STATIC_zoom  =  IDC_STATIC_zoom;
	
	p->iIDC_BUTTON_FOCUS_IN  =  IDC_BUTTON_FOCUS_IN;
	p->iIDC_BUTTON_IRIS_IN  =  IDC_BUTTON_IRIS_IN;
	p->iIDC_BUTTON_ZOOM_IN  =  IDC_BUTTON_ZOOM_IN;

	p->iIDCANCEL  =  IDCANCEL;
	//  tailer
	p->iIDC_BUTTON_RAIN_BRUSH  =  IDC_BUTTON_RAIN_BRUSH;
	p->iIDC_BUTTON_SEARCH_LIGHT  =  IDC_BUTTON_SEARCH_LIGHT;
	p->iIDC_STATIC_preset  =  IDC_STATIC_preset;
	p->iIDC_EDIT_PRE  =  IDC_EDIT_PRE;
	p->iIDC_BUTTON_PRE_GO  =  IDC_BUTTON_PRE_GO;
	p->iIDC_BUTTON_PRE_SET  =  IDC_BUTTON_PRE_SET;
	p->iIDC_BUTTON_PRE_CLEAR  =  IDC_BUTTON_PRE_CLEAR;


	//  header
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_ptzSettings  ),  &p->rcIDC_BUTTON_ptzSettings  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_ptzSettings,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_hint  ),  &p->rcIDC_STATIC_hint  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_hint,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_speed  ),  &p->rcIDC_STATIC_speed  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_speed,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_SLIDER_speed  ),  &p->rcIDC_SLIDER_speed  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_SLIDER_speed,  2  );

	//  body
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_TOP_LEFT  ),  &p->rcIDC_BUTTON_TOP_LEFT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_TOP_LEFT,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_UP  ),  &p->rcIDC_BUTTON_UP  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_UP,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_TOP_RIGHT  ),  &p->rcIDC_BUTTON_TOP_RIGHT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_TOP_RIGHT,  2  );

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_LEFT  ),  &p->rcIDC_BUTTON_LEFT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_LEFT,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_AUTO_SCAN  ),  &p->rcIDC_BUTTON_AUTO_SCAN  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_AUTO_SCAN,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_RIGHT  ),  &p->rcIDC_BUTTON_RIGHT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_RIGHT,  2  );

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_BOTTOM_LEFT  ),  &p->rcIDC_BUTTON_BOTTOM_LEFT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_BOTTOM_LEFT,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_DOWN  ),  &p->rcIDC_BUTTON_DOWN  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_DOWN,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_BOTTOM_RIGHT  ),  &p->rcIDC_BUTTON_BOTTOM_RIGHT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_BOTTOM_RIGHT,  2  );

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_noop  ),  &p->rcIDC_BUTTON_noop  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_noop,  2  );

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_FOCUS_OUT  ),  &p->rcIDC_BUTTON_FOCUS_OUT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_FOCUS_OUT,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_IRIS_OUT  ),  &p->rcIDC_BUTTON_IRIS_OUT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_IRIS_OUT,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_ZOOM_OUT  ),  &p->rcIDC_BUTTON_ZOOM_OUT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_ZOOM_OUT,  2  );

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_focus  ),  &p->rcIDC_STATIC_focus  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_focus,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_iris  ),  &p->rcIDC_STATIC_iris  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_iris,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_zoom  ),  &p->rcIDC_STATIC_zoom  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_zoom,  2  );

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_FOCUS_IN  ),  &p->rcIDC_BUTTON_FOCUS_IN  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_FOCUS_IN,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_IRIS_IN  ),  &p->rcIDC_BUTTON_IRIS_IN  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_IRIS_IN,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_ZOOM_IN  ),  &p->rcIDC_BUTTON_ZOOM_IN  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_ZOOM_IN,  2  );

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDCANCEL  ),  &p->rcIDCANCEL  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDCANCEL,  2  );
	//  tailer
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_RAIN_BRUSH  ),  &p->rcIDC_BUTTON_RAIN_BRUSH  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_RAIN_BRUSH,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_SEARCH_LIGHT  ),  &p->rcIDC_BUTTON_SEARCH_LIGHT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_SEARCH_LIGHT,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_preset  ),  &p->rcIDC_STATIC_preset  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_preset,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_EDIT_PRE  ),  &p->rcIDC_EDIT_PRE  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_EDIT_PRE,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_PRE_GO  ),  &p->rcIDC_BUTTON_PRE_GO  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_PRE_GO,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_PRE_SET  ),  &p->rcIDC_BUTTON_PRE_SET  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_PRE_SET,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_PRE_CLEAR  ),  &p->rcIDC_BUTTON_PRE_CLEAR  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_PRE_CLEAR,  2  );

	p->bInited  =  TRUE;
	
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );

	if  (  !m_var.bRemote  )  {
		//
		if  (  m_var.local.resObj_camera.uiObjType  !=  CONST_objType_rtspStream  )  {
			//
			QIS_ptz_wnd  *  pPtzWnd  =  m_var.local.pPtzWnd;
			//		
			COM_PORT_cfg	cfg;
			if  (  getPtzSettings(  &cfg  )  )  goto  errLabel;
			//
			if  (  !m_var.pComPort  )  {
				initPtz(  &cfg,  &pPtzWnd->m_var,  (  CComPortEx  **  )&m_var.pComPort  );		
			}
			m_var.iPtzType  =  pPtzWnd->m_var.cfg.iPtzType;  //  2015/09/20
			//
			m_var.m_nAddr  =  pPtzWnd->m_var.cfg.m_nAddr;
			m_var.m_pelcoType  =  pPtzWnd->m_var.cfg.m_pelcoType;
			//  m_var.m_nSpeed  =  pProcInfo->ptz.m_var.m_nSpeed;
		}
		}
	else  {
		  //  viewRemotePtz里已经赋值了
		  makeWndNoBorder(  m_hWnd,  FALSE,  NULL,  NULL  );
	}

	//
	m_var.pStageLens  =  new  CStageLens;
	if  (  !m_var.pStageLens  )  goto  errLabel;

	CStageLens  *  pStageLens  =  (  CStageLens  *  )m_var.pStageLens;
	pStageLens->pDlgPtzControl  =  this;

	if  (  m_var.m_pelcoType ==  CONST_ptzProto_PELCO_D  )  {
		pStageLens->SetProtocol(  CStageLens::PELCO_D  );
		}
	else  if  (  m_var.m_pelcoType  ==  CONST_ptzProto_PELCO_P  )  {
			  pStageLens->SetProtocol(  CStageLens::PELCO_P  );
			  }
	else  {
		  showInfo_open0(  0,  0,  _T(  "dlgPtzControl: not peclo"  )  );
	}
	//
	m_var.m_nSpeed  =  23;
	pStageLens->SetSpeed(  m_var.m_nSpeed  );

	//
	InitBtn(  );

	//
	refreshStatus(  );

	//
	//  2015/09/18
	CComboBox  *  pCb  =  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_dev  );
	if  (  !pCb  )  goto  errLabel;

	TCHAR  tBuf[128]  =  _T(  ""  );	
	QY_DMITEM  *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
	if  (  !pTable  )  goto  errLabel;

	//
	if  (  !m_var.bRemote  )  {
		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %d"  ),  qyGetDesByType1(  pTable,  m_var.local.resObj_camera.uiObjType  ),  (  int  )m_var.local.resObj_camera.usIndex_obj  );
		if  (  m_var.local.resObj_camera.usHelp_subIndex  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.%d"  ),  tBuf,  m_var.local.resObj_camera.usHelp_subIndex  );
		//
		pCb->InsertString(  -1,  tBuf  );
		//
		pCb->SetCurSel(  0  );
		}
	else  {
				 
		  TCHAR  *  pName  =  _T(  ""  );		
		  TCHAR  *  cusName  =  _T(  ""  );		
		  //
		  cusName  =  m_var.remote.remoteCamera.cusName;
		  //
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %d"  ),  qyGetDesByType1(  pTable,  m_var.remote.remoteCamera.qisResObj.resObj.uiObjType  ),  (  int  )m_var.remote.remoteCamera.qisResObj.resObj.usIndex_obj  );
		  if  (  m_var.remote.remoteCamera.qisResObj.resObj.usHelp_subIndex  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.%d"  ),  tBuf,  (  int  )m_var.remote.remoteCamera.qisResObj.resObj.usHelp_subIndex  );  
		  pCb->InsertString(  -1,  tBuf  );
		  //
		  pCb->SetCurSel(  0  );
	}


	//
	int  iPos  =  0;
	switch  (  m_var.iPtzType  )  {
			case  CONST_ptzType_usb:
				  iPos  =  8;	//2;
				  break;
			case  CONST_ptzType_serialPort:  
				  iPos  =  m_var.m_nSpeed  *  100  /  0x3f;
				  break;
			default:
					break;
	}
	m_slider_speed.SetPos(  iPos  );


	//
	if  (  m_var.bRemote  )  {
		::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_ptzSettings  ),  SW_HIDE  );
	}

	//  2016/07/24
#if  1
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_TOP_LEFT  ),  SW_HIDE  );
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_TOP_RIGHT  ),  SW_HIDE  );
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_BOTTOM_LEFT  ),  SW_HIDE  );
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_BOTTOM_RIGHT  ),  SW_HIDE  );	
#endif

	//
#ifdef  __DEBUG__
	if  (  0  )
	{
		int  nMin,  nMax;
		this->m_slider_speed.GetRange(  nMin,  nMax  );
		int ii;
		ii  =  0;
	}
#endif


	//  2010/08/29
	m_var.dwTickCnt_lastPtzCmdRecvd  =  GetTickCount(  );
	m_var.wTimerID  =  ::SetTimer(  hDlg,  1,  1000,  NULL  );



	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPtzControl::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialog::OnClose();
	bQuitDlg(  );
}

void CDlgPtzControl::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();

	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	if  (  m_var.pStageLens  )  {
		CStageLens  *  pStageLens  =  (  CStageLens  *  )m_var.pStageLens;
		delete  pStageLens;
		m_var.pStageLens  =  NULL;
	}

	//  2015/09/20
	exitPtz(  &m_var.pComPort  );

	//  2012/09/05
	if  (  m_var.bRemote  &&  m_var.remote.hDlgTalk  )  {
		::PostMessage(  m_var.remote.hDlgTalk,  WM_SIZE,  0,  0  );
	}

	//
	delete  this;
}

void CDlgPtzControl::OnBnClickedButtonptzsettings()
{
	// TODO: Add your control notification handler code here
	if  (  m_var.bRemote  )  return;

	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );


	//
	if  (  showDlgPtzSettings(  m_hWnd  )  ==  IDOK  )	
	{
		//
		QIS_ptz_wnd  *  pPtzWnd  =  m_var.local.pPtzWnd;

		//
		exitPtz(  (  CComPortEx  **  )&m_var.pComPort  );
		//
		COM_PORT_cfg	cfg;
		getPtzSettings(  &cfg  );
		if  (  memcmp(  &cfg,  &pPtzWnd->m_var.cfg,  sizeof(  cfg  )  )  )  {
			pPtzWnd->m_var.cfg  =  cfg;
			//
		}
		//
		//  2016/08/12. 
		if  (  memcmp(  &pProcInfo->ptzWnd.m_var.cfg.idInfos_allowed,  &cfg.idInfos_allowed,  sizeof(  pProcInfo->ptzWnd.m_var.cfg.idInfos_allowed  )  )  )  {		
			memcpy(  &pProcInfo->ptzWnd.m_var.cfg.idInfos_allowed,  &cfg.idInfos_allowed,  sizeof(  pProcInfo->ptzWnd.m_var.cfg.idInfos_allowed  )  );
			showInfo_open0(  0,  0,  _T(  "update global procInfo.idInfos_allowed"  )  );
		}

		//
		initPtz(  &cfg,  &pPtzWnd->m_var,  &m_var.pComPort  );

		//
		m_var.iPtzType  =  pPtzWnd->m_var.cfg.iPtzType;  //  2015/09/20
		//
		m_var.m_nAddr  =  pPtzWnd->m_var.cfg.m_nAddr;
		m_var.m_pelcoType  =  pPtzWnd->m_var.cfg.m_pelcoType;
		//  m_var.m_nSpeed  =  pProcInfo->ptz.m_var.m_nSpeed;

		//
		CStageLens  *  pStageLens  =  (  CStageLens  *  )m_var.pStageLens;

		if  (  m_var.m_pelcoType ==  CONST_ptzProto_PELCO_D  )  {
			pStageLens->SetProtocol(  CStageLens::PELCO_D  );
			}	
		else  if  (  m_var.m_pelcoType  ==  CONST_ptzProto_PELCO_P  )  {
			  pStageLens->SetProtocol(  CStageLens::PELCO_P  );
			  }
		else  {
			  qyShowHint(  _T(  "ptz proto type error"  )  );
			  #ifdef  __DEBUG__
					  traceLog(  _T(  "Err"  )  );
			  #endif
		}

	}

	//
	refreshStatus(  );

}

void CDlgPtzControl::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//  CDialog::OnCancel();

	bQuitDlg(  );
}


//  2014/09/13
void dlg_YTBtn_remote(  HWND  hDlg,  int  nResourceID, unsigned  char  ucMouseStatus  )
{
	CDlgPtzControl  *  pDlg  =  (  CDlgPtzControl  *  )CWnd::FromHandlePermanent(  hDlg  );
	if  (  !pDlg  )  return;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	//
	unsigned  int  uiObjType  =  0;
	unsigned  short  usIndex_obj  =  0;
	unsigned  short  usHelp_subIndex = 0;
	//
	unsigned  char	ucCmd  =  0;
	unsigned  char  ucParam  =  0;
	//unsigned  char  ucMouseStatus = CONST_mouseStatus_lBtnDown;

	//  2016/07/19
	uiObjType  =  pDlg->m_var.remote.remoteCamera.qisResObj.resObj.uiObjType;
	usIndex_obj  =  pDlg->m_var.remote.remoteCamera.qisResObj.resObj.usIndex_obj;
	usHelp_subIndex  =  pDlg->m_var.remote.remoteCamera.qisResObj.resObj.usHelp_subIndex;

	//
	QY_MESSENGER_ID  idInfo; idInfo=pProcInfo->m_ipcProc.op.idInfo;
	int  iChannel = pProcInfo->m_ipcProc.op.iChannel;
	
	//
	QY_MESSENGER_ID  idInfo_imGrp_related = { 0 };

	//
	QY_MESSENGER_ID  idInfo_to = pDlg->m_var.remote.remoteCamera.qisResObj.idInfo;
	idInfo_to = pProcInfo->m_ipcProc.op.idInfo;

	do {

		//
		if (idInfo_to.ui64Id == pMisCnt->idInfo.ui64Id) {
			//  发送到mcu上去
			HWND  hCurTalk = pDlg->m_var.remote.hDlgTalk;
			CHelp_getDlgTalkVar help_getDlgTalkVar;
			DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hCurTalk);
			if (!pCurVar)  break;
			HWND  hMgr = nullptr;
			if (isTalkerShadowMgr(pCurVar->addr)) {
				hMgr = hCurTalk;
			}
			else {
				TALKER_shadow* pShadow = (TALKER_shadow*)pCurVar->pShadowInfo;
				if (!pShadow) break;
				hMgr = pShadow->hMgr;
			}
			CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
			DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
			if (!pMgrVar)  break;
			//
			if (!pMgrVar->av.taskInfo.bTaskExists)  break;
			if (!pMgrVar->av.taskInfo.ucbVideoConference)  break;
			//
			idInfo_imGrp_related.ui64Id = pMgrVar->addr.idInfo.ui64Id;
			//
			idInfo_to = pMgrVar->av.taskInfo.idInfo_starter;

			//
		}


		//
		switch (nResourceID) {
		case  IDC_BUTTON_UP:
			ucCmd = CONST_ptzCmd_up;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related,  idInfo_to);
			break;
		case  IDC_BUTTON_DOWN:
			ucCmd = CONST_ptzCmd_down;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_LEFT:
			ucCmd = CONST_ptzCmd_left;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_RIGHT:
			ucCmd = CONST_ptzCmd_right;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_TOP_LEFT:
			ucCmd = CONST_ptzCmd_topLeft;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_TOP_RIGHT:
			ucCmd = CONST_ptzCmd_topRight;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_BOTTOM_LEFT:
			ucCmd = CONST_ptzCmd_bottomLeft;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_BOTTOM_RIGHT:
			ucCmd = CONST_ptzCmd_bottomRight;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;

			//  2013/04/07
		case  IDC_BUTTON_noop:
			ucCmd = CONST_ptzCmd_noop;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;

			//
		case  IDC_BUTTON_FOCUS_IN:
			ucCmd = CONST_ptzCmd_focusIn;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_FOCUS_OUT:
			ucCmd = CONST_ptzCmd_focusOut;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;

		case  IDC_BUTTON_IRIS_IN:
			ucCmd = CONST_ptzCmd_irisIn;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_IRIS_OUT:
			ucCmd = CONST_ptzCmd_irisOut;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;

		case  IDC_BUTTON_ZOOM_IN:
			ucCmd = CONST_ptzCmd_zoomIn;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_ZOOM_OUT:
			ucCmd = CONST_ptzCmd_zoomOut;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;

		default:
			break;
		}

	} while (false);

	//
	return;
}


//
void dlg_YTBtnDown_remote(HWND  hDlg, int  nResourceID)
{
	unsigned  char  ucMouseStatus = CONST_mouseStatus_lBtnDown;
	dlg_YTBtn_remote(hDlg, nResourceID, ucMouseStatus);
}



//
//void dlg_YTCmd(  HWND  hDlg_ptz,  int  nResourceID,  int  lStep_percent  )
void dlg_YTCmd(HWND  hDlg_ptz, int  nResourceID, int  lStep_percent, unsigned  char ucMouseStatus,  int iChannel,  PTZ_control_cmd  *  pPtzControlCmd )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	//
	CDlgPtzControl  *  pDlg  =  (  CDlgPtzControl  *  )CWnd::FromHandlePermanent(  hDlg_ptz  );
	if  (  !pDlg  )  return;

	//  2014/09/13
	if  (  pDlg->m_var.bRemote  )  {
		return;
	}

	//  2014/10/14
	pDlg->m_var.dwTickCnt_lastPtzCmdRecvd  =  GetTickCount(  );

	//
	if  (  pDlg->m_var.local.resObj_camera.uiObjType  ==  CONST_objType_rtspStream  )  {
		PARAM_viewLocalPtzControl  *  pParam  =  &pDlg->m_var.local.param;
		if  (  pParam->pf_dlg_YTCmd  )  {
			pParam->pf_dlg_YTCmd(  hDlg_ptz,  nResourceID,  pParam->p0,  pParam->p1  );
		}
		return;
	}

	//
	switch  (  pDlg->m_var.iPtzType  )  {
			case  CONST_ptzType_usb:
				  dlg_YTCmd_usb(  hDlg_ptz,  nResourceID  );
				  break;
			case  CONST_ptzType_serialPort:
				  dlg_YTCmd_pelco(  hDlg_ptz,  nResourceID  );
				  break;
			case  CONST_ptzType_ipc: {
				  //int iChannel = pProcInfo->m_ipcProc.op.iChannel;
				  int ptzCmd = getPtzCmdByResourceId(nResourceID);
				  dlg_YTCmd_ipc(hDlg_ptz, iChannel,  ptzCmd, ucMouseStatus);
				  }
				  break;
			default:
					break;
	}

	return;
}


//
 int getPtzCmdByResourceId(int nResourceID)
{
	int ucCmd = 0;

	switch (nResourceID) {
	case  IDC_BUTTON_UP:
		ucCmd = CONST_ptzCmd_up;
		break;
	case  IDC_BUTTON_DOWN:
		ucCmd = CONST_ptzCmd_down;
		break;
	case  IDC_BUTTON_LEFT:
		ucCmd = CONST_ptzCmd_left;
		break;
	case  IDC_BUTTON_RIGHT:
		ucCmd = CONST_ptzCmd_right;
		break;
	case  IDC_BUTTON_TOP_LEFT:
		ucCmd = CONST_ptzCmd_topLeft;
		break;
	case  IDC_BUTTON_TOP_RIGHT:
		ucCmd = CONST_ptzCmd_topRight;
		break;
	case  IDC_BUTTON_BOTTOM_LEFT:
		ucCmd = CONST_ptzCmd_bottomLeft;
		break;
	case  IDC_BUTTON_BOTTOM_RIGHT:
		ucCmd = CONST_ptzCmd_bottomRight;
		break;

		//  2013/04/07
	case  IDC_BUTTON_noop:
		ucCmd = CONST_ptzCmd_noop;
		break;

		//
	case  IDC_BUTTON_FOCUS_IN:
		ucCmd = CONST_ptzCmd_focusIn;
		break;
	case  IDC_BUTTON_FOCUS_OUT:
		ucCmd = CONST_ptzCmd_focusOut;
		break;

	case  IDC_BUTTON_IRIS_IN:
		ucCmd = CONST_ptzCmd_irisIn;
		break;
	case  IDC_BUTTON_IRIS_OUT:
		ucCmd = CONST_ptzCmd_irisOut;
		break;

	case  IDC_BUTTON_ZOOM_IN:
		ucCmd = CONST_ptzCmd_zoomIn;
		break;
	case  IDC_BUTTON_ZOOM_OUT:
		ucCmd = CONST_ptzCmd_zoomOut;
		break;

	default:
		break;
	}

	return  ucCmd;

}



//
void dlg_YTBtnDown(  HWND  hDlg,  int  nResourceID  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
#if  0
	if  (  !pProcInfo->ptz.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pProcInfo->ptz.pStageLens;
#endif
	CDlgPtzControl  *  pDlg  =  (  CDlgPtzControl  *  )CWnd::FromHandlePermanent(  hDlg  );
	if  (  !pDlg  )  return;

	//  2014/09/13
	if  (  pDlg->m_var.bRemote  )  {
		dlg_YTBtnDown_remote(  hDlg,  nResourceID  );
		return;
	}

	//
	long  lStep_percent  =  0;
	lStep_percent  =  pDlg->m_slider_speed.GetPos(  );

	unsigned  char  ucMouseStatus = CONST_mouseStatus_lBtnDown;
	int  iChannel = pProcInfo->m_ipcProc.op.iChannel;

	//
	dlg_YTCmd(  hDlg,  nResourceID,  lStep_percent,  ucMouseStatus,  iChannel,  mynull  );

	return;
}


void dlg_YTBtnUp_remote(  HWND  hDlg,  int  nResourceID  )
{
#if 0
	CDlgPtzControl  *  pDlg  =  (  CDlgPtzControl  *  )CWnd::FromHandlePermanent(  hDlg  );
	if  (  !pDlg  )  return;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	//
	unsigned  int  uiObjType  =  0;
	unsigned  short  usIndex_obj  =  0;
	unsigned  short  usHelp_subIndex  =  0;
	//
	unsigned  char	ucCmd  =  0;
	unsigned  char  ucParam  =  0;

	//  2016/07/19
	uiObjType  =  pDlg->m_var.remote.remoteCamera.qisResObj.resObj.uiObjType;
	usIndex_obj  =  pDlg->m_var.remote.remoteCamera.qisResObj.resObj.usIndex_obj;
	usHelp_subIndex = pDlg->m_var.remote.remoteCamera.qisResObj.resObj.usHelp_subIndex;

		//
		QY_MESSENGER_ID idInfo_to = pDlg->m_var.remote.remoteCamera.qisResObj.idInfo;

		//
		int  iChannel = pProcInfo->m_ipcProc.op.iChannel;

	//
	ucCmd  =  CONST_ptzCmd_noop;		
	sendPtzReq(  uiObjType,  usIndex_obj,  usHelp_subIndex,  iChannel,  ucCmd,  ucParam,  CONST_mouseStatus_lBtnUp, idInfo_to  );  
#endif

	//
	unsigned  char  ucMouseStatus = CONST_mouseStatus_lBtnUp;

	//
	dlg_YTBtn_remote(hDlg, nResourceID, ucMouseStatus);

	//
	return;
}

void dlg_YTBtnUp(  HWND  hDlg,  int  nResourceID  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
#if  0
	if  (  !pProcInfo->ptz.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pProcInfo->ptz.pStageLens;
#endif
	
	CDlgPtzControl  *  pDlg  =  (  CDlgPtzControl  *  )CWnd::FromHandlePermanent(  hDlg  );
	if  (  !pDlg  )  return;


	//  2014/09/13
	if  (  pDlg->m_var.bRemote  )  {
		dlg_YTBtnUp_remote(  hDlg,  nResourceID  );
		return;
	}


#if  0  //  2015/09/18
	//
	if  (  !pDlg->m_var.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pDlg->m_var.pStageLens;


	int  m_nAddr  =  pDlg->m_var.m_nAddr;

	m_CStageLens.Noop(  m_nAddr  );
#endif

	//
	long  lStep_percent  =  0;
	lStep_percent  =  pDlg->m_slider_speed.GetPos(  );

	//
	int  iChannel = pProcInfo->m_ipcProc.op.iChannel;

	//  2015/09/18
	//dlg_YTCmd(  hDlg,  IDC_BUTTON_noop,  lStep_percent,  CONST_mouseStatus_lBtnUp  );
	dlg_YTCmd(hDlg, nResourceID, lStep_percent, CONST_mouseStatus_lBtnUp,  iChannel,mynull);

}

void dlg_YTCHECKBtn(  HWND  hDlg,  int  nResourceID  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
#if  0
	if  (  !pProcInfo->ptz.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pProcInfo->ptz.pStageLens;
#endif

	CDlgPtzControl  *  pDlg  =  (  CDlgPtzControl  *  )CWnd::FromHandlePermanent(  hDlg  );
	if  (  !pDlg  )  return;

	if  (  !pDlg->m_var.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pDlg->m_var.pStageLens;


	int  m_nAddr  =  pDlg->m_var.m_nAddr;  

	switch  (  nResourceID  )  {
			case  IDC_BUTTON_AUTO_SCAN:
				  if  (  pDlg->m_var.m_bnDown_autoScan )  {
					  m_CStageLens.AutoScan(  m_nAddr  );
					  m_CStageLens.PreSet(  m_nAddr,  99,  CStageLens::PresetAction_Goto  );
				  }
				  else  
				  {
					  m_CStageLens.Noop(  m_nAddr  );
				  }
				  break;			
			case  IDC_BUTTON_RAIN_BRUSH:
				  if  (  pDlg->m_var.m_bnDown_rainBrush  )
				  {
					  m_CStageLens.RainBrushOn(  m_nAddr  );
				  }
				  else  
				  {
					  m_CStageLens.RainBrushOff(  m_nAddr  );
				  }
				  break;
			case  IDC_BUTTON_SEARCH_LIGHT:
				  if  (  pDlg->m_var.m_bnDown_searchLight  )
				  {
					  m_CStageLens.SearchLightOn(  m_nAddr  );
				  }
				  else
				  {
					  m_CStageLens.SearchLightOff(  m_nAddr  );
				  }
				  break;
			default:
				break;
	}
}

void CDlgPtzControl::OnNMReleasedcaptureSliderspeed(NMHDR *pNMHDR, LRESULT *pResult)
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
#if  0
	if  (  !pProcInfo->ptz.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pProcInfo->ptz.pStageLens;
#endif

	if  (  !m_var.pStageLens  )  return;
	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )m_var.pStageLens;

	//
	UpdateData(  );
	int  iTest  =  m_slider_speed.GetPos(  );
	m_var.m_nSpeed  =  m_slider_speed.GetPos(  )  *  0x3f  /  100;
	m_CStageLens.SetSpeed(  m_var.m_nSpeed  );

	*pResult = 0;
}

void CDlgPtzControl::OnChangeStatus(  UINT  nID  )
{
	switch(  nID  )  {
		case  IDC_BUTTON_AUTO_SCAN:
			  m_buStatus_autoScan.m_nFlag  =  1 - m_buStatus_autoScan.m_nFlag;
			  m_byStatus_autoScan  =  m_buStatus_autoScan.m_nFlag;
			  m_buStatus_autoScan.RedrawWindow(  );
			  break;
		case  IDC_BUTTON_RAIN_BRUSH:
			  m_buStatus_rainBrush.m_nFlag  =  1 - m_buStatus_rainBrush.m_nFlag;
			  m_byStatus_rainBrush  =  m_buStatus_rainBrush.m_nFlag;
			  m_buStatus_rainBrush.RedrawWindow(  );
			  break;
		case  IDC_BUTTON_SEARCH_LIGHT:
			  m_buStatus_searchLight.m_nFlag  =  1 - m_buStatus_searchLight.m_nFlag;
			  m_byStatus_searchLight  =  m_buStatus_searchLight.m_nFlag;
			  m_buStatus_searchLight.RedrawWindow(  );
			  break;
		default:
			break;
	}
}

void CDlgPtzControl::OnEnChangeEditPre()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(  TRUE  );
	CString  str;
	m_edit_nPrePoint.GetWindowText(  str  );
	m_var.m_nPre  =  _tstoi(  str  );
}

void CDlgPtzControl::OnBnClickedButtonPreGo()
{

	if  (  m_var.m_nPre  >  255  )  {
		AfxMessageBox(  _T(  "Preset ID cannot be more than 255!"  )  );
		SetDlgItemInt(  IDC_EDIT_PRE,  0  );
		return;
	}
	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )m_var.pStageLens;
	int  m_nAddr  =  m_var.m_nAddr;
	int  m_nPre  =  m_var.m_nPre;

	m_CStageLens.PreSet(  m_nAddr,  m_nPre,  CStageLens::PresetAction_Goto  );
}

void CDlgPtzControl::OnBnClickedButtonPreSet()
{
	if  (  m_var.m_nPre  >  255  )  {
		AfxMessageBox(  _T(  "Preset ID cannot be more than 255!"  )  );
		SetDlgItemInt(  IDC_EDIT_PRE,  0  );
		return;
	}
	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )m_var.pStageLens;
	int  m_nAddr  =  m_var.m_nAddr;
	int  m_nPre  =  m_var.m_nPre;

	m_CStageLens.PreSet(  m_nAddr,  m_nPre,  CStageLens::PresetAction_Set  );
}

void CDlgPtzControl::OnBnClickedButtonPreClear()
{
	if  (  m_var.m_nPre  >  255  )  {
		AfxMessageBox(  _T(  "Preset ID cannot be more than 255!"  )  );
		SetDlgItemInt(  IDC_EDIT_PRE,  0  );
		return;
	}
	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )m_var.pStageLens;
	int  m_nAddr  =  m_var.m_nAddr;
	int  m_nPre  =  m_var.m_nPre;

	SetDlgItemInt(  IDC_EDIT_PRE,  0  );
	m_CStageLens.PreSet(  m_nAddr,  m_nPre,  CStageLens::PresetAction_Clear  );
}



void CDlgPtzControl::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	DLG_guiData_ptzControl	*	p	=	&m_var.guiData;

	if  (  !p->iw_org  ||  !p->ih_org  )  return;

	RECT	rc;
	GetClientRect(  &rc  );
	int  w,  h;
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;


	//  
	int	idc;
	int  iX,  iY,  iW,  iH;
	float  fx,  fy;
	fx  =  1.  *  w  /  p->iw_org;
	fy  =  1.  *  h  /  p->ih_org;

	 //  header
	idc  =  p->iIDC_BUTTON_ptzSettings;
	rc  =  p->rcIDC_BUTTON_ptzSettings;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_hint;
	rc  =  p->rcIDC_STATIC_hint;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_speed;
	rc  =  p->rcIDC_STATIC_speed;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_SLIDER_speed;
	rc  =  p->rcIDC_SLIDER_speed;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  
	//	 body
	idc  =  p->iIDC_BUTTON_TOP_LEFT;
	rc  =  p->rcIDC_BUTTON_TOP_LEFT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_UP;
	rc  =  p->rcIDC_BUTTON_UP;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_TOP_RIGHT;
	rc  =  p->rcIDC_BUTTON_TOP_RIGHT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_LEFT;
	rc  =  p->rcIDC_BUTTON_LEFT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_AUTO_SCAN;
	rc  =  p->rcIDC_BUTTON_AUTO_SCAN;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_RIGHT;
	rc  =  p->rcIDC_BUTTON_RIGHT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_BOTTOM_LEFT;
	rc  =  p->rcIDC_BUTTON_BOTTOM_LEFT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_DOWN;
	rc  =  p->rcIDC_BUTTON_DOWN;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_BOTTOM_RIGHT;
	rc  =  p->rcIDC_BUTTON_BOTTOM_RIGHT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_BOTTOM_LEFT;
	rc  =  p->rcIDC_BUTTON_BOTTOM_LEFT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_noop;
	rc  =  p->rcIDC_BUTTON_noop;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_FOCUS_OUT;
	rc  =  p->rcIDC_BUTTON_FOCUS_OUT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_IRIS_OUT;
	rc  =  p->rcIDC_BUTTON_IRIS_OUT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_ZOOM_OUT;
	rc  =  p->rcIDC_BUTTON_ZOOM_OUT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  
	
	idc  =  p->iIDC_STATIC_focus;
	rc  =  p->rcIDC_STATIC_focus;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_iris;
	rc  =  p->rcIDC_STATIC_iris;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_zoom;
	rc  =  p->rcIDC_STATIC_zoom;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_FOCUS_IN;
	rc  =  p->rcIDC_BUTTON_FOCUS_IN;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_IRIS_IN;
	rc  =  p->rcIDC_BUTTON_IRIS_IN;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_ZOOM_IN;
	rc  =  p->rcIDC_BUTTON_ZOOM_IN;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_RAIN_BRUSH;
	rc  =  p->rcIDC_BUTTON_RAIN_BRUSH;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_SEARCH_LIGHT;
	rc  =  p->rcIDC_BUTTON_SEARCH_LIGHT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_preset;
	rc  =  p->rcIDC_STATIC_preset;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_EDIT_PRE;
	rc  =  p->rcIDC_EDIT_PRE;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_PRE_GO;
	rc  =  p->rcIDC_BUTTON_PRE_GO;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_PRE_SET;
	rc  =  p->rcIDC_BUTTON_PRE_SET;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_PRE_CLEAR;
	rc  =  p->rcIDC_BUTTON_PRE_CLEAR;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDCANCEL;
	rc  =  p->rcIDCANCEL;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	return;

	//  sizeAllControls(  );

}

void CDlgPtzControl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

#ifdef  __DEBUG__
		//traceLog(  _T(  "ptzControl timer called"  )  );
#endif

	//
	if  (  !m_var.bRemote  )  {
		if  (  !m_var.local.bManual  )  {
			if  (  GetTickCount(  )  -  m_var.dwTickCnt_lastPtzCmdRecvd  >  10000  )  {
				#ifdef  __DEBUG__
						traceLog(  _T(  "dlgPtzControl: OnTimer: before close"  )  );
				#endif
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgPtzControl: OnTimer, close"  )  );
				::PostMessage(  m_hWnd,  WM_CLOSE,  0,  0  );
				#ifdef  __DEBUG__
						traceLog(  _T(  "dlgPtzControl: OnTimer: after close"  )  );
				#endif
				return;	  
		
			}	
		}
	}



	CDialog::OnTimer(nIDEvent);
}


