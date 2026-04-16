

#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>

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

#ifndef  __WINCE__
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__
	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>
#include	<dsound.h>

#include	"qmcDmoPublic.h"

#include	"qmcVideoCapture_dx.h"

#include	"myfourcc.h"
#include	"mywmcodecconst.h"

#include	"qmcCmdProc.h"

#include	"cPropertyBag.h"

#include	"qyCusResTemp.h"
#include	"qmcDirectX.h"

//  #include	"myresource.h"
#ifdef  __SUPPORT_CUS_sampleGrabber__
		#include	"qySampleGrabberPublic.h"
#endif

#include	"myresource.h"
#include	"qmcShareMediaDevice.h"

//
int  get_vc_camera(  TCHAR  *  displayName,  unsigned  int  displayNameCnt  );

//
QY_DMITEM  CONST_cameraControlPropTable[]  =  {
	{	CameraControl_Pan,				_T(  "Pan"  ),	},
	{   CameraControl_Tilt,				_T(  "Tilt"  ),	},
	{	CameraControl_Roll,				_T(  "Roll"  ),	},
	{	CameraControl_Zoom,				_T(  "Zoom"  ),	},
	{	CameraControl_Exposure,			_T(  "Exposure"  ),	},
	{	CameraControl_Iris,				_T(  "Iris"  ),		},
	{	CameraControl_Focus,			_T(  "Focus"  ),	},
	{	-1,	},
};

//
int  tmpHandler_doYTCmd_usb(  IAMCameraControl  *  pCameraControl,  long  lProp,  BOOL  bInc,  long  lStep_percent_suggested,  BOOL  bValid_lStep_suggested  )
{
	int					iErr  =  -1;
	MC_VAR_isCli  *		pProcInfo  =  QY_GET_procInfo_isCli(  );

	long				lMin,  lMax,  lStep,  lDefault,  lFlags;
	long				lVal;
	long				tmp_lStep;
	HRESULT				hr;
	TCHAR				tBuf[128]  =  _T(  ""  );
	BOOL				bLessThanMin  =  FALSE;
	BOOL				bGreaterThanMax  =  FALSE;


	hr  =  pCameraControl->GetRange(  lProp,  &lMin,  &lMax,  &lStep,  &lDefault,  &lFlags  );
	if  (  SUCCEEDED(  hr  )  )  {						 
		//
		tmp_lStep  =  lStep;
		if  (  bValid_lStep_suggested  )  {
			int  iVal  =  lStep_percent_suggested  *  (  lMax  -  lMin  )  /  100;
			if  (  iVal  >  0  )  {
				tmp_lStep  =  iVal;
			}
		}
		if  (  !bInc  )  tmp_lStep  =  -1  *  tmp_lStep;
		//
		hr  =  pCameraControl->Get(  lProp,  &lVal,  &lFlags  );		
		if  (  SUCCEEDED(  hr  )  )  {		
			lVal  =  lVal  +  tmp_lStep;

			if  (  lVal  <  lMin  )  {
				lVal  =  lMin;		
				//
				bLessThanMin  =  TRUE;
			}
			if  (  lVal  >  lMax  )  {
				lVal  =  lMax;			
				//
				bGreaterThanMax  =  TRUE;
			}
			//
			hr  =  pCameraControl->Set(  lProp,  lVal,  lFlags  );				
			if  (  FAILED(  hr  )  )  {
				showInfo_open0(  0,  0,  _T(  "ptz: Pan left,  Set failed"  )  );							 
				}						 
			else  {
				  if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_ptz  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doYTCmd_usb: Set %s=%d ok"  ),  qyGetDesByType1(  CONST_cameraControlPropTable,  lProp  ),  lVal  );
					  if  (  bLessThanMin  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s min"  ),  tBuf  );
					  else  if  (  bGreaterThanMax  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s max"  ),  tBuf  );
					  else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s lStep %d"  ),  tBuf,  tmp_lStep  );
					  //
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. ( min %d, max %d, step %d, def %d, lFlags %d )"  ),  tBuf,  lMin,  lMax,  lStep,  lDefault,  lFlags  );
					  //
					  showInfo_open0(  0,  0,  tBuf  );
				  }
			}
		}			
	}
		
	iErr  =  0;

	return  iErr;

}


//
void dlg_YTCmd_usb(  HWND  hDlg_ptz,  int  nResourceID  )
{
	int  iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	CDlgPtzControl  *  pDlg  =  (  CDlgPtzControl  *  )CWnd::FromHandlePermanent(  hDlg_ptz  );
	if  (  !pDlg  )  return;

	//  2014/09/13
	if  (  pDlg->m_var.bRemote  )  {
		return;
	}

	//  2014/10/14
	pDlg->m_var.dwTickCnt_lastPtzCmdRecvd  =  GetTickCount(  );

	//  not finished
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	HRESULT		hr;
	//
	IMoniker  *  pMoniker_v  =  NULL;
	IBaseFilter  *  pBF  =  NULL;
	IAMCameraControl  *  pCameraControl  =  NULL;

#ifdef  __DEBUG__
		traceLog(  _T(  "dlg_YTCmd_usb: nResourceID: %d"  ),  nResourceID  );
#endif
		//
		TCHAR  displayName[256]  =  _T(  ""  );
		if  (  get_vc_camera(  displayName,  mycountof(  displayName  )  )  )  {
			goto  errLabel;
		}
		//
		TCHAR  *  displayName_selected  =  displayName;

		//
		if  (  pFuncs->moniker.pf_getMonikerByDisplayName(  displayName_selected,  (  void  **  )&pMoniker_v  )
			||  !pMoniker_v  )  
		{
			traceLogA(  "initAudioCapDev_dx failed:  pMoniker null"  );
			goto  errLabel;		 
		}

		//	
		hr = pMoniker_v->BindToObject(0, 0, IID_IBaseFilter, (void**)&pBF);
		if  (  FAILED(  hr  )  )  goto  errLabel;

		//
		//
		hr  =  pBF->QueryInterface(  IID_IAMCameraControl,  (  void  **  )&pCameraControl  );
		if  (  FAILED(  hr  )  )  goto  errLabel;
		//
		long  lMin,  lMax,  lStep,  lDefault,  lFlags;
		long  lVal;

		//
		BOOL  bValid_lStep_suggested  =  TRUE;
		int  lStep_percent  =  pDlg->m_slider_speed.GetPos(  );
		long  lProp  =  0;
		BOOL  bInc  =  FALSE;
		//
		switch  (  nResourceID  )  {
				case  IDC_BUTTON_UP:  {
					  lProp  =  CameraControl_Tilt;
					  bInc  =  TRUE;
					  tmpHandler_doYTCmd_usb(  pCameraControl,  lProp,  bInc,  lStep_percent,  bValid_lStep_suggested  );
					  }
					  break;
				case  IDC_BUTTON_DOWN:  {
					  lProp  =  CameraControl_Tilt;
					  bInc  =  FALSE;
					  tmpHandler_doYTCmd_usb(  pCameraControl,  lProp,  bInc,  lStep_percent,  bValid_lStep_suggested  );
					  }
					  break;
				case  IDC_BUTTON_LEFT:  {
					  lProp  =  CameraControl_Pan;
					  bInc  =  FALSE;
					  tmpHandler_doYTCmd_usb(  pCameraControl,  lProp,  bInc,  lStep_percent,  bValid_lStep_suggested  );
					  }
					  break;
				case  IDC_BUTTON_RIGHT:  {
					  lProp  =  CameraControl_Pan;
					  bInc  =  TRUE;
					  tmpHandler_doYTCmd_usb(  pCameraControl,  lProp,  bInc,  lStep_percent,  bValid_lStep_suggested  );
					  }
					  break;
					  //
				case  IDC_BUTTON_TOP_LEFT:  {
					  lProp  =  CameraControl_Tilt;
					  bInc  =  TRUE;
					  tmpHandler_doYTCmd_usb(  pCameraControl,  lProp,  bInc,  lStep_percent,  bValid_lStep_suggested  );
					  //
					  lProp  =  CameraControl_Pan;
					  bInc  =  FALSE;
					  tmpHandler_doYTCmd_usb(  pCameraControl,  lProp,  bInc,  lStep_percent,  bValid_lStep_suggested  );
					  }					   
					  break;
				case  IDC_BUTTON_TOP_RIGHT:  {
					  lProp  =  CameraControl_Tilt;
					  bInc  =  TRUE;
					  tmpHandler_doYTCmd_usb(  pCameraControl,  lProp,  bInc,  lStep_percent,  bValid_lStep_suggested  );
					  //
					  lProp  =  CameraControl_Pan;
					  bInc  =  TRUE;
					  tmpHandler_doYTCmd_usb(  pCameraControl,  lProp,  bInc,  lStep_percent,  bValid_lStep_suggested  );
					  }
					  break;
				case  IDC_BUTTON_BOTTOM_LEFT:  {
					  lProp  =  CameraControl_Tilt;
					  bInc  =  FALSE;
					  tmpHandler_doYTCmd_usb(  pCameraControl,  lProp,  bInc,  lStep_percent,  bValid_lStep_suggested  );
					  //
					  lProp  =  CameraControl_Pan;
					  bInc  =  FALSE;
					  tmpHandler_doYTCmd_usb(  pCameraControl,  lProp,  bInc,  lStep_percent,  bValid_lStep_suggested  );
					  }
					  break;
				case  IDC_BUTTON_BOTTOM_RIGHT:  {
					  lProp  =  CameraControl_Tilt;
					  bInc  =  FALSE;
					  tmpHandler_doYTCmd_usb(  pCameraControl,  lProp,  bInc,  lStep_percent,  bValid_lStep_suggested  );
					  //
					  lProp  =  CameraControl_Pan;
					  bInc  =  TRUE;
					  tmpHandler_doYTCmd_usb(  pCameraControl,  lProp,  bInc,  lStep_percent,  bValid_lStep_suggested  );
					  }				  
					  break;
					  
					  //  2013/04/07
				case  IDC_BUTTON_noop:				  
					  break;
					  
				case  IDC_BUTTON_ZOOM_IN:   {
					  long  lProp  =  	CameraControl_Zoom;					 
					  BOOL  bInc  =  TRUE;
					  tmpHandler_doYTCmd_usb(  pCameraControl,  lProp,  bInc,  lStep_percent,  bValid_lStep_suggested  );
					  }
					  break;		

				case  IDC_BUTTON_ZOOM_OUT:   {
					  long  lProp  =  	CameraControl_Zoom;
					  BOOL  bInc  =  FALSE;					 
					  tmpHandler_doYTCmd_usb(  pCameraControl,  lProp,  bInc,  lStep_percent,  bValid_lStep_suggested  );
					  }
					  break;		
					  
					  //
				case  IDC_BUTTON_FOCUS_IN:				  
					  break;
				case  IDC_BUTTON_FOCUS_OUT:				  
					  break;
				case  IDC_BUTTON_IRIS_IN:				  
					  break;
				case  IDC_BUTTON_IRIS_OUT:				  
					  break;				  

				default:
						break;
		}


		iErr  =  0;

errLabel:

		//
		MACRO_safeRelease(  pCameraControl  );
		//
		MACRO_safeRelease(  pBF  );
		//
		MACRO_safeRelease(  pMoniker_v  );
		//

	//
	return;

}


//
int  get_vc_camera(  TCHAR  *  displayName,  unsigned  int  displayNameCnt  )
{
	int  iErr  =  -1;
	int  i;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;


	i  =  getSharedObjIndex_localAv(  );

		//  for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_capProcInfoBmps;  i  ++  )  
	for  (  int  ii  =  0;  ii  <  1  ;  ii  ++  )
		{
			 CAP_procInfo_bmpU  *  pCapBmp  =  getCapBmpBySth(  pProcInfo,  i,  0  );
			 if  (  !pCapBmp  )  continue;
			 switch  (  pCapBmp->common.uiType  )  {
					  case  CONST_capType_av:  {  
						    CAP_procInfo_video  *  pVc;
							pVc  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  i,  0  );
							if  (  !pVc  )  continue;

							if  (  pVc->bCapDevConnected  )  {
								if  (  pVc->uiCamCapType  ==  CONST_camCapType_directX  )  {
									VIDEO_capDev_dx	*	p;

									p  =	(  VIDEO_capDev_dx  *  )pVc->capDev.pVideoCapDev;
									//
									if  (  p  &&  p->p_gcap  )  {
										AV_capStuff  &  gcap  =  *(  AV_capStuff  *  )p->p_gcap;
										if  (  gcap.pmVideo  )  {
#if  0
											if  (  S_OK   ==  pM->IsEqual(  gcap.pmVideo  )  )  {
												iIndex_capBmp  =  i;
												bRet  =  TRUE;  
												goto  errLabel;
											}
#endif
											//
											pFuncs->moniker.pf_getMonikerDisplayName(  gcap.pmVideo,  displayName,  displayNameCnt  );
											iErr  =  0;  goto  errLabel;

										}
									}
								}
							}
							}
							break;
					  default:
							  break;
			 }
		}



		iErr  =  0;
errLabel:
		return  iErr;
}


