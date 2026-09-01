

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyMcInputMgr.h"
#include	"tmpCeLib.h"


#if  0
 LRESULT  WINAPI  inputMgrWndProc(HWND hWnd, UINT wMessage, WPARAM wParam, LPARAM lParam)
{
	switch  (  wMessage  )  {
			case  WM_COPYDATA:  {
				  COPYDATASTRUCT  *  pCopyData  =  (  COPYDATASTRUCT  *  )lParam;
				  QVD_SM_REQ	*	pSmReq  =  (  QVD_SM_REQ  *  )pCopyData->lpData;

				  QY_MC						*		pQyMc				=	NULL;
				  int								iServiceId			=	CONST_qyServiceId_mis;
				  QY_SERVICEGUI_INFO		*		pSci				=	getServiceGuiInfo(  pQyMc,  iServiceId  );
				  //
				  MC_VAR_isCli				*		pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;
				  int								i;

				  //  在策略不允许或者未装载的前提下。不接受输入的处理。
				  if  (  !pProcInfo->cfg.policy.ucbPermitOtherSm  )  goto  errLabel;
				  for  (  i  =  0;  i  <  pQyMc->cusModules.usCnt;  i  ++  )  {
					   if  (  pQyMc->cusModules.mems[i].common.uiType  !=  CONST_moduleType_vDev  )  continue;
					   if  (  !pQyMc->cusModules.mems[i].common.hModule  )  continue;
					   break;
				  }
				  if  (  i  ==  pQyMc->cusModules.usCnt  )  goto  errLabel;

				  QVD_SM_REQ		smReq;
				  if  (  !pSmReq  )  goto  errLabel;
				  traceLogA(  "Recvd:  sm %S, phoneNo %s",  pSmReq->sm,  pSmReq->phoneNo  );				  
				  memcpy(  &smReq,  pSmReq,  sizeof(  smReq  )  );

				  //  这里要先过滤
				  filterStr2Display(  smReq.sm,  mycountof(  smReq.sm  )  );
				  fwReplaceChrInStr(  '\'',  smReq.phoneNo,  sizeof(  smReq.phoneNo  )  );

				  MACRO_prepareForTran(  );
				  TCHAR	wForwardPath[512];

				  _sntprintf(  wForwardPath,  mycountof(  wForwardPath  ),  _T(  "phone:%s"  ),  CQyString(  smReq.phoneNo  )  );
				  //  int  myVDev_postStr2Dev(  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  LPCTSTR  str,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  WCHAR  *  wForwardPath  )
				  myVDev_postStr2Dev(  NULL,  tStartTran,  uiTranNo,  0,  smReq.sm,  CONST_objType_dev,  _T(  ""  ),  wForwardPath,  smReq.hWnd_notify,  smReq.iUsrData  );

				  //
				  }
				  return  0;
			default:
					return DefWindowProc(hWnd, wMessage, wParam, lParam);    

	}
errLabel:
	return  0;
}

 int  initInputMgr(  HINSTANCE  g_hInst,  QM_INPUT_MGR  *  pInputMgr  )
{

	int			iErr		=	-1;


#if  0
	HINSTANCE	hInstance;
#ifndef  __WINCE__
	hInstance	=	AfxGetInstanceHandle( );
#else
	hInstance	=	g_hInst;
#endif
#endif
	WNDCLASS	wcx; 
	HWND		hWnd		=	NULL;
 
    // Fill in the window class structure with parameters 
    // that describe the main window. 
 
    wcx.style = 0;									// redraw if size changes 
    wcx.lpfnWndProc = inputMgrWndProc;				// points to window procedure 
    wcx.cbClsExtra = 0;								// no extra class memory 
    wcx.cbWndExtra = 0;								// no extra window memory 
    wcx.hInstance = g_hInst;	//  hInstance;						// handle to instance 
    wcx.hIcon = 0;									// predefined app. icon 
    wcx.hCursor = 0;								// predefined arrow 
    wcx.hbrBackground = 0;							// white background brush 
    wcx.lpszMenuName =  0;							// name of menu resource 
    wcx.lpszClassName = DEFAULT_qyMcInputWndCls;	// name of window class 
 
	// Register the window class. 
	if  (  !RegisterClass(  &wcx  )  )  goto  errLabel;

	hWnd = CreateWindow(  DEFAULT_qyMcInputWndCls,  _T(  ""  ),  WS_OVERLAPPEDWINDOW,0,0,0,0,NULL,NULL, g_hInst,  NULL);
	if  (  !hWnd  )  goto  errLabel;

	iErr  =  0;
errLabel:

	if  (  !iErr  )  {
		pInputMgr->hWnd  =  hWnd;
	}

	return  iErr;
}
#endif


 int  initInputMgr(  HINSTANCE  g_hInst,  QM_INPUT_MGR  *  pInputMgr  )
{
#ifdef  __DEBUG__
		traceLog(  (TCHAR*)_T(  "Not used: initInputMgr"  )  );
#endif
	return  0;
 }


 void  exitInputMgr(  QM_INPUT_MGR  *  pInputMgr  )
{
	if  (  IsWindow(  pInputMgr->hWnd  )  )  {
		DestroyWindow(  pInputMgr->hWnd  );  pInputMgr->hWnd  =  NULL;
	}

}




