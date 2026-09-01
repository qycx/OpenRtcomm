
#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
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


#include	<dvdmedia.h>


#include	"qmcDmo.h"
#include	"qmcVideoCapture_isCli.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif

#include	"qyDynLib.h"

#include	"mywmcodecconst.h"
#include	"mywmcodeciface.h"
#include	"myfourcc.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"

#include	"qyMcMainRealTimeMediaProc.h"
#include	"myfourcc.h"

#include	"funcsForIsCliHelp.h"


#ifdef  __DEBUG__  //  {




int  test_get_vc_camera(  MC_VAR_isCli  *  pProcInfo,  TCHAR  *  displayName,  unsigned  int  displayNameCnt  )
{
	int  iErr  =  -1;
	int  i;

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

 BOOL  bGetFilter(  IMoniker  **  ppMoniker,  IBaseFilter  **  ppFilter  )
{

	BOOL	bRet	=	FALSE;

	//  if  (  deviceIndex  <  0  )  return  FALSE;

	// enumerate all video capture devices
	ICreateDevEnum	*	pCreateDevEnum;

	HRESULT  hr  =  CoCreateInstance(CLSID_SystemDeviceEnum, NULL, 
					CLSCTX_INPROC_SERVER,
					IID_ICreateDevEnum,
					(void**)&pCreateDevEnum);
	if  (  SUCCEEDED(  hr  )  )  {
		IEnumMoniker *pEm;

		hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&pEm, 0);
		if  (  hr  ==  S_OK  )  {
			pEm->Reset();
			ULONG cFetched;
			IMoniker *pM;
			int index = 0;
			while  (  hr  =  pEm->Next(  1,  &pM,  &cFetched  ),  hr  ==  S_OK  )  {
				   IPropertyBag *pBag;
				   hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
				   if  (  SUCCEEDED(  hr  )  ) {
					   VARIANT var;
					   var.vt = VT_BSTR;
					   hr = pBag->Read(L"FriendlyName", &var, NULL);
					   if  (  hr  ==  NOERROR  )  {
						   if  (  !bRet  )  {
							   //  if  (  index  ==  deviceIndex  )  
							   //if  (  !pM_selected  ||  S_OK  ==  pM_selected->IsEqual(  pM  )  )  
							   if  (  _tcsstr(  var.bstrVal,  _T(  "LifeCam"  )  )  )
							   {
								   hr  =  pM->BindToObject(0, 0, IID_IBaseFilter, (void**)ppFilter);
								   if  (  !FAILED(  hr  )  )  {
									   *ppMoniker  =  pM;
									   pM->AddRef();
									   bRet  =  TRUE;
								   }
							   }
						   }
						   SysFreeString(var.bstrVal);
					   }			
					   pBag->Release();
				   }
				   pM->Release();
				   index++;
			}
			pEm->Release(  );
		}
		pCreateDevEnum->Release(  );
	}

	return  bRet;
}

 //
void testCameraControl(  QY_MC  *  pQyMc  )
{
	return;

	int  iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pQyMc->get_pProcInfo(  );
	if  (  !pProcInfo  )  return;
	if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  return;

	//  not finished
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	IMoniker  *  pMoniker_v  =  NULL;
	IBaseFilter  *  pBF  =  NULL;
	HRESULT		hr;
	IAMCameraControl  *  pCameraControl  =  NULL;
	ICaptureGraphBuilder2  *  pCaptureGraph  =  NULL;
	IGraphBuilder  *  pGraph  =  NULL;

	//
	IBaseFilter  *  pAviWriter  =  NULL;
	IFileSinkFilter  *  pSink  =  NULL;

	//
	IMediaControl  *  pControl  =  NULL;


#ifdef  __DEBUG__
		//  traceLog(  _T(  "dlg_YTCmd_usb: nResourceID: %d"  ),  nResourceID  );
		TCHAR  displayName[256]  =  _T(  ""  );
		if  (  test_get_vc_camera(  pProcInfo,  displayName,  mycountof(  displayName  )  )  )  {
			goto  errLabel;
		}
		//
		TCHAR  *  displayName_selected  =  displayName;

#if  0
		//
		if  (  pFuncs->moniker.pf_getMonikerByDisplayName(  displayName_selected,  (  void  **  )&pMoniker_v  )
			||  !pMoniker_v  )  
		{
			traceLogA(  "initAudioCapDev_dx failed:  pMoniker null"  );
			goto  errLabel;		 
		}
#endif
		
		//
		hr = CoCreateInstance(CLSID_CaptureGraphBuilder2 , NULL,
						CLSCTX_INPROC,
						IID_ICaptureGraphBuilder2, (void **)&pCaptureGraph);
		if  (  FAILED(  hr  )  )  goto  errLabel;
		
		// ´´½¨IGraphBuilder½Ó¿Ú
		hr = CoCreateInstance(CLSID_FilterGraph, NULL, 
						CLSCTX_INPROC_SERVER,
						IID_IGraphBuilder, (void **)&pGraph);
		if (  FAILED(  hr  )  )  goto  errLabel;
		
		// ³õÊ¼»¯ÂË²¨Æ÷Á´±í¹ÜÀíÆ÷IGraphBuilder
		hr  =  pCaptureGraph->SetFiltergraph(  pGraph  );
		if  (  FAILED(  hr  )  )  goto  errLabel;
		
		//
		hr  =  pCaptureGraph->SetOutputFileName(  &MEDIASUBTYPE_Avi,  _T(  "c:\\tttbbb\\kk.avi"  ),  &pAviWriter,  &pSink  );
		if  (  FAILED(  hr  )  )  goto  errLabel;

#if  0
		//	
		hr = pMoniker_v->BindToObject(0, 0, IID_IBaseFilter, (void**)&pBF);
		if  (  FAILED(  hr  )  )  goto  errLabel;
#endif
		IMoniker  *  tmppMoniker  =  NULL;
		bGetFilter(  &tmppMoniker,  &pBF  );
		//
		hr  =  pGraph->AddFilter(  pBF,  _T(  "webcam"  )  );
		if  (  FAILED(  hr  )  )  goto  errLabel;

		//
		hr  =  pGraph->QueryInterface(  IID_IMediaControl,  (  void  **  )&pControl  );
		if  (  FAILED(  hr  )  )  goto  errLabel;

		//
		//
		hr  =  pBF->QueryInterface(  IID_IAMCameraControl,  (  void  **  )&pCameraControl  );
		if  (  FAILED(  hr  )  )  goto  errLabel;
		//
		long  lMin,  lMax,  lStep,  lDefault,  lFlags;
		long  lVal;
		hr  =  pCameraControl->GetRange(  CameraControl_Pan,  &lMin,  &lMax,  &lStep,  &lDefault,  &lFlags  );
		if  (  SUCCEEDED(  hr  )  )  {
		}
		hr  =  pCameraControl->Get(  CameraControl_Pan,  &lVal,  &lFlags  );
		if  (  SUCCEEDED(  hr  )  )  {
		}


		hr  =  pCameraControl->GetRange(  CameraControl_Zoom,  &lMin,  &lMax,  &lStep,  &lDefault,  &lFlags  );
		if  (  SUCCEEDED(  hr  )  )  {
		}
		
		hr  =  pCameraControl->GetRange(  CameraControl_Exposure,  &lMin,  &lMax,  &lStep,  &lDefault,  &lFlags  );
		if  (  SUCCEEDED(  hr  )  )  {
		}

		

		//
#endif

		iErr  =  0;

errLabel:

		//
		MACRO_safeRelease(  pCameraControl  );
		//
		MACRO_safeRelease(  pBF  );
		//
		MACRO_safeRelease(  pMoniker_v  );
		//
		MACRO_safeRelease(  pCaptureGraph  );
		MACRO_safeRelease(  pGraph  );
		//
		MACRO_safeRelease(  pAviWriter  );
		MACRO_safeRelease(  pSink  );

	//
	return;

}





#endif  //  }



