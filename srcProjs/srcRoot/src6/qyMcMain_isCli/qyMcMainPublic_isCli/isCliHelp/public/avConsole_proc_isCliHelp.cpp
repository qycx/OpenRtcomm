


#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>







#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qySyncCommProc.h"
#include	"qmcVideoCapture_isCli.h"



//
#include	"isCliHelpPublic.h"


//
#include	"funcsForIsCliHelp.h"

//
#include	"avConsole_open.h"

#include	"myresource.h"

//#include	"DlgDynBmps.h"



//
#if  0
__declspec(  dllexport  )  int  do_avConsole_req_isCliHelp(  AvConsole_req_head  *  pReqHead  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	
	//QY_OBJ_DB  *  pObjDb  =  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
	QY_MESSENGER_ID  idInfo  =  { 0 };	//  {104};
	unsigned  int  uiObjType  =  CONST_objType_webcam;
	unsigned  usIndex_obj  =  1;
	//
	TCHAR  tBuf[128];


	//
	switch  (  pReqHead->usCmd  )  {
			case  0:  	
				  break;
			case  CONST_avConsole_cmd_move:
				  {
				  //
				  AvConsole_req_move  *  pReq  =  (  AvConsole_req_move  *  )pReqHead;
				  
				  //
				  idInfo.ui64Id  =  pReq->ui64Id;	
				  uiObjType  =  pReq->uiObjType;	
				  usIndex_obj  =  pReq->usIndex_obj;
				  
				  //
				  QY_DMITEM  *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "view: %I64u, %s, %d. x %d, y %d, w %d, h %d"  ),  idInfo.ui64Id,  qyGetDesByType1(  pTable,  uiObjType  ),  (  int  )usIndex_obj,  pReq->x,  pReq->y,  pReq->w,  pReq->h  );
				  showInfo_open0(  0,  _T(  "do_avConnsole_req"  ),  tBuf  );
				  //
				  
				  //
				  if  (  !pReq->w  ||  !pReq->h  )  {
					  showInfo_open0(  0,  0,  _T(  "do_avConsole_req failed, w or h is 0"  )  );
					  goto  errLabel;
				  }
				  
				  //
				  PARAM_viewDynBmp  param  =  {0};
				  //
				  param.bValid_pos  =  TRUE;
				  //
				  param.x  =  pReq->x;
				  param.y  =  pReq->y;
				  param.w  =  pReq->w;
				  param.h  =  pReq->h;
				  param.bFullScreen  =  pReq->bFullScreen;
				  //
				  param.bNoBorder  =  TRUE;
				  //
				  HWND  hParent  =  NULL;
				  if  (  pReq->bDesktop  )  hParent  =  GetDesktopWindow(  );
				  else  hParent  =  FindWindow(  NULL,  pReq->unique_wndTitle_parent  );
				  //
				  HWND  hDynBmp  =  NULL;
				  if  (  findDynBmp(  _T(  ""  ),  &idInfo,  uiObjType,  usIndex_obj,  &hDynBmp  )  )  goto  errLabel;
				  //
				  CDlgDynBmps  *  pDlgDynBmps  =  (  CDlgDynBmps  *  )CWnd::FromHandlePermanent(  hDynBmp  );
				  if  (  !pDlgDynBmps  )  goto  errLabel;
				  CDlgDesktopsMon  *  pBase  =  pDlgDynBmps;
				  //
				  if  (  pReq->bHide  )  {
					  pDlgDynBmps->ShowWindow(  SW_HIDE  );
					  break;
				  }
				  //
				  pDlgDynBmps->ShowWindow(  SW_SHOW  );
				  //
				  if  (  !pReq->bFullScreen  )  {
					  if  (  pBase->m_var.m_bFullScreen  )  pDlgDynBmps->endFullScreen(  );
					  //
					  MoveWindow(  hDynBmp,  param.x,  param.y,  param.w,  param.h,  TRUE  );
				  }
				  else  {
					    if  (  !pBase->m_var.m_bFullScreen  )  {
							PostMessage(  hDynBmp,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );
						}
				  }
				  }
				  break;
			default:
					break;
	}


	iErr  =  0;
errLabel:

	return  iErr;
}
#endif