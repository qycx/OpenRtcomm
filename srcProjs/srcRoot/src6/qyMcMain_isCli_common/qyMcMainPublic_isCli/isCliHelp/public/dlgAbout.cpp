

#include "stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"myresource.h"


#include	"isCliHelpPublic.h"
#include	"isCliExPublic.h"


 int  dlgAbout_OnInitDialog_qyMc(  HWND  hDlg,  int  iIDD  ) 
{
	//  CDialog::OnInitDialog();
	int			iErr					=	-1;
	QY_MC	*	pQyMc					=	QY_GET_GBUF(  );
	TCHAR		tBuf[128]				=  _T(  ""  );
	int			iVer;
	TCHAR		defaultAppName[128]		=  _T(  "QyMc"  );
	char		verBuf[128];
	TCHAR		maxPcsBuf[128];
	BOOL		bDebug					=	FALSE;
	TCHAR		appName[128]			=	_T(  "\"清扬\"软件"  );

	//  2011/03/30
	if  (  isIsCli(  pQyMc  )  )  {
		if  (  setModalWnd(  pQyMc,  hDlg  )  )  goto  errLabel;
	}

	if  (  bApp_ts(  pQyMc  )  )  {  //  #ifdef  __APP_qyMc_touchscreen__
			//  2011/03/12
			//::SetWindowPos(  hDlg,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOMOVE  |  SWP_NOSIZE  );
	}  //  	#endif


	cusDlgRes(  0,  &pQyMc->cusRes,  hDlg,  iIDD  );

	////////////////////////////////

	//  2004/04/24ÔÝÊ±ÆÁ±ÎÏÂÃæµÄ»°¡£
	if  (  pQyMc->cfg.qyMcTitle[0]  )  {
		SetWindowText(  hDlg,  pQyMc->cfg.qyMcTitle  );
	}
	//
	lstrcpyn(  appName,  getResStr(  0,  &pQyMc->cusRes,  pQyMc->cfg.pGuiCfg->iResId_sys  ),  mycountof(  appName  )  );
	//
	_sntprintf(  appName,  mycountof(  appName  ),  _T(  "%s %s"  ),  appName,  getTableResStr(  0,  CONST_subSystemIdTable_en,  &pQyMc->cusRes,  qyGetSubSystemId_isCli( pQyMc )  )  );
	//
	//_sntprintf(  appName,  mycountof(  appName  ),  _T(  "%s %s"  ),  appName,  getTableResStr(  0,  CONST_qyAppAvLevelTable_en,  &pQyMc->cusRes,  qyGetAppAvLevel_qyMc(  pQyMc  )  )  );  

	//
#if  0
	if  (  qyGetAppAvLevel_qyMc(  pQyMc  )  !=  pQyMc->usAppAvLevel_default  /*qyGetAppAvLevel_default(  )*/  )  {
		_sntprintf(  appName,  mycountof(  appName  ),  _T(  "%s ( %s  )"  ),  appName,  getTableResStr(  0,  CONST_qyAppAvLevelTable_en,  &pQyMc->cusRes,  pQyMc->usAppAvLevel_default  )  );
	}
#endif
#if  0
	if  (  qyGetAppAvLevel_qyMc(  pQyMc  )  ==  CONST_qyAppAvLevel_mini  )  {	//  2014/07/27
		_sntprintf(  appName,  mycountof(  appName  ),  _T(  "%s mini"  ),  appName  );
	}
#endif
	if  (  pQyMc->ucbDaemonDemo  )  {
		if  (  bQmFreeVer(  pQyMc  )  )  _sntprintf(  appName,  mycountof(  appName  ),  _T(  "%s FreeVer"  ),  appName  );
		else  _sntprintf(  appName,  mycountof(  appName  ),  _T(  "%s Beta"  ),  appName  );
	}
	//
	//  2015/08/08
	_sntprintf(  appName,  mycountof(  appName  ),  _T(  "%s Exts: ["  ),  appName  );
	if  (  bSupported_rtsp(  )  )  {
		_sntprintf(  appName,  mycountof(  appName  ),  _T(  "%s rtsp"  ),  appName  );
	}
	if  (  bSupported_remoteStorage_default(  )  )  {
		_sntprintf(  appName,  mycountof(  appName  ),  _T(  "%s remoteStorage"  ),  appName  );
	}
	if  (  bSupported_fileServer(  pQyMc  )  )  {
		_sntprintf(  appName,  mycountof(  appName  ),  _T(  "%s fileServer"  ),  appName  );
	}
	_sntprintf(  appName,  mycountof(  appName  ),  _T(  "%s ]"  ),  appName  );
	//
	SetDlgItemText(  hDlg,  IDC_STATIC_appName,  appName  );

	//
	_snprintf(  verBuf,  sizeof(  verBuf  ),  "%s",  qnmVerStr(  pQyMc->iServiceId  )  );
	if  (  verBuf[0]  &&  verBuf[strlen(  verBuf  )  -  1]  ==  'd'  )  bDebug  =  TRUE;
	iVer  =  atol(  verBuf  );
	//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s V%d.%02d.%02d%s"  ),  appName,  iVer  /  10000,  (  iVer  /  100  )  %  100,  iVer  %  100,  bDebug  ?  _T(  "Debug"  )  :  _T(  ""  )  );
	//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Ver: V%d.%02d.%02d%s"  ),  iVer  /  10000,  (  iVer  /  100  )  %  100,  iVer  %  100,  bDebug  ?  _T(  "Debug"  )  :  _T(  ""  )  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Ver: V%d.%02d.%02d.%02d%s"  ),  iVer  /  1000000,  (  iVer  /  10000  )  %  100,  (  iVer  /  100  )  %  100,  iVer  %  100,  bDebug  ?  _T(  "Debug"  )  :  _T(  ""  )  );
	//
	_snprintf(  verBuf,  sizeof(  verBuf  ),  "%s",  qnmDbVerStr(  pQyMc->iServiceId  )  );
	if  (  verBuf[0]  &&  verBuf[strlen(  verBuf  )  -  1]  ==  'd'  )  bDebug  =  TRUE;
	iVer  =  atol(  verBuf  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, DbVer: %d.%02d.%02d%s"  ),  tBuf,  iVer  /  10000,  (  iVer  /  100  )  %  100,  iVer  %  100,  bDebug  ?  _T(  "Debug"  )  :  _T(  ""  )  );
	SetDlgItemText(  hDlg,  IDC_STATIC_ver,  CQyString(  tBuf  )  );

	tBuf[0]  =  0;
	if  (  pQyMc->iAppType  !=  CONST_qyAppType_client  )  {
		if  (  !qyGetRegCfg(  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  _T(  CONST_regValName_qnmMaxObjs  ),  (  char  *  )maxPcsBuf,  sizeof(  maxPcsBuf  )  )  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s  %s"  ),  tBuf,  CQyString(  maxPcsBuf  )  );
		}
#ifndef  __WINCE__
		if  (  pQyMc->iSystemId  ==  CONST_qySystemId_messenger    )  {	//  2009/11/03
			#if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
			int			iAvUpperLimits  =  qnmAvUpperLimits(  &pQyMc->licenseCtx  );
			TCHAR	*	p;
			int			maxVideoConferenceMems	=	0;
			int			maxDynBmpMessengers	=	0;

			if  (  (  p  =  _tcsrchr(  maxPcsBuf,  ','  )  )  )  {
				*p  =  0;  p  ++  ;
				maxDynBmpMessengers  =  _ttol(  p  );
				if  (  (  p  =  _tcsrchr(  maxPcsBuf,  ','  )  )  )  {
					*p  =  0;  p  ++  ;
					maxVideoConferenceMems  =  _ttol(  p  );
				}
			}
			if  (  maxVideoConferenceMems  !=  LOWORD(  iAvUpperLimits  )  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsMgr"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "maxVideoConferenceMems %d != %d"  ),  maxVideoConferenceMems,  LOWORD(  iAvUpperLimits  )  );
			}
			if  (  maxDynBmpMessengers  !=  HIWORD(  iAvUpperLimits  )  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsMgr"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "maxDynBmpMessengers %d != %d"  ),  maxDynBmpMessengers,  HIWORD(  iAvUpperLimits  )  );
			}
			#endif
		}
#endif
		}
	else  {
		  if  (  pQyMc->iSystemId  ==  CONST_qySystemId_messenger  )  {
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %d"  ),  tBuf,  pQyMc->usMaxVideoConferenceMems  );
			  //
			  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
			  if  (  pProcInfo  )  {			  
				  MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
				  if  (  pMisCnt  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\tLogon: %d, ID: %I64u"  ),  tBuf,  pQyMc->appParams.iSeqNoSelected_appObjPrefix,  pMisCnt->idInfo.ui64Id  );
				  }
				  //
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\t%s"  ),  tBuf,  qyGetDesByType1(  CONST_customIdTable,  pQyMc->iCustomId  )  );
			  }
		  }
	}

	
	if  (  pQyMc->licenseCtx.uiSerialNo  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s    SN:  0x%x"  ),  tBuf,  pQyMc->licenseCtx.uiSerialNo  );
	}
	tTrim(  tBuf  );
	SetDlgItemText(  hDlg,  IDC_STATIC_sn,  tBuf  );

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		EndDialog(  hDlg,  -1  );
	}
	return iErr;  
}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		 dlgAbout_OnInitDialog_qyMc(  hDlg,  IDD_ABOUTBOX  );

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



__declspec(  dllexport  )  int  myOnAppAbout(  HWND  hParent  )
{
	HINSTANCE	hInst  =  get_my_hInst(  g_pQyMc  );
	DialogBox(  hInst,  MAKEINTRESOURCE(  IDD_ABOUTBOX  ),  hParent,  About  );
	return  0;
}
