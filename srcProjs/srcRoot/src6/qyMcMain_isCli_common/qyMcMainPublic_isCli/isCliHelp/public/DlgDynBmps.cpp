// DlgDynBmp.cpp : implementation file
//

#include	"stdafx.h"
#include	<stdlib.h>
#include	<math.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"
#include	"qmcVWall.h"
#include	"WallTalkers.h"
#include	"DlgDynBmps.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"

#include	"qyCusResTemp.h"

#include	"qyAvRecordPublic.h"

#include	"sp.h"
#include	"qmcCommFunc_isCli.h"
#include	"qyMessengerHelpPublic.h"
#include	"qmcLayout.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#if  !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )  
	#ifndef  __DEBUG__
		#include	"DlgQnmSendHint.h"
		#include	"qyPs.h"
	#endif
#endif

#include	"dlgTalkProc.h"
#include	"DlgVideos.h"

//  #include	"DlgPolicyIsClient.h"
//  #include	"DlgPolicyAv.h"
//  #include	"DlgCfgVideoConference.h"
//  #include	"DlgMsgList.h"
#include	"qmcGpsProc.h"
//
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"dlgSelect_isCli_public.h"

#include	"myDb.h"

//
BOOL  m_bDraging  =  FALSE;


//
 int  addZone_talkers(  HWND  hDlgWalls,  BOOL  bFullWall,  int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH  );
 int  refreshRuleObjsPos(  CDlgDynBmps  *  pDlg  );
 //  int  doCmd_test(  int  iMenuId  );
  VW_ruleU  *  findRuleBySth(  CDlgDynBmps  *  pDlg,  unsigned  int  uiTranNo_spObj  );
 int  tmpHandler_bSameRule(  void  *  p0,  void  *  p1,  void  *  p2  );
int  mapSpPoint(  SUB_V_WALL  *  pSubWall,  POINT  pt_subwall,  POINT  *  pPt_sp  );


 //
 int  get_default_wh_wall(  unsigned  int  *  piInitW,  unsigned  int  *  piInitH  )
 {
	 int  cx  =  GetSystemMetrics(  SM_CXSCREEN  );
	 int  cy  =  GetSystemMetrics(  SM_CYSCREEN  );

	 if  (  cx  >  1366  &&  cy  >  768  )  {
		 *piInitW  =  DEFAULT_uiInitW_wall_1024;
		 *piInitH  =  DEFAULT_uiInitH_wall_768;
	 }
	 else  {
		 *piInitW  =  DEFAULT_uiInitW_wall_800;
		 *piInitH  =  DEFAULT_uiInitH_wall_600;

	 }

	 return  0;
 }


 //
 int  dynBmps_setOn_quickToRetrieveImg(  CDlgDynBmps  *  pDlg,    BOOL  bOn  )
 {
	 int  iErr  =  -1;

	 DLG_dynBmps_var  *  pm_var  =  pDlg->get_pm_var(  );
	 if  (  !pm_var  )  goto  errLabel;
	 DLG_dynBmps_var  &m_var  =  *pm_var;

	 //
	 if  (  bOn  )  {
		 m_var.quickToRetrieveImg.iTries  =  10;	//5;
		 m_var.quickToRetrieveImg.ucbOn  =  TRUE;
		 }
	 else  {
		   m_var.quickToRetrieveImg.ucbOn  =  FALSE;
	 }

	 iErr  =  0;
errLabel:

	 return  iErr;
 }


 //
 __declspec(  dllexport  ) int  viewDynBmp(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj,  LPCTSTR  cusName,  PARAM_viewDynBmp  *  pParam  ) 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr			=		-1;
	QY_MC				*	pQyMc			=		QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci			=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;	
	MC_VAR_isCli			*	pProcInfo		=		(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;
	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;
	//  
	CDlgDynBmps			*	pDlg			=		NULL;
	RECT					rect;
	CWaitCursor				cur;

	int						i;
	MIS_CNT				*	pMisCnt			=		getMisCntByName(  pProcInfo,  misServName  );
	if  (  !pMisCnt  )  return  -1;
	int						iWndContentType	=		CONST_qyWndContentType_vWall;

#ifdef  __DEBUG__
	traceLogA(  "viewDynBmp enters"  );
#endif

	//
	if  (  !pIdInfo  )  return  -1;
	if  (  !uiObjType  )  return  -1;
	if  (  !pParam  )  return  -1;
	
	//
	if  (  pParam->bValid_pos  )  {
		if  (  !pParam->w  ||  !pParam->h  )  return  -1;
	}
		
	//
	if  (  !pMisCnt->subWnds.usMaxCnt  ||  !pMisCnt->subWnds.pMems  )  {
		goto  errLabel;
	}
	for  (  i  =  0;  i  <  pMisCnt->subWnds.usMaxCnt;  i  ++  )  {
		 if  (  !IsWindow(  pMisCnt->subWnds.pMems[i].hWnd  )  )  continue;
		 //
		 if  (  pMisCnt->subWnds.pMems[i].iWndContentType  ==  iWndContentType
			 &&  pMisCnt->subWnds.pMems[i].idInfo.ui64Id  ==  pIdInfo->ui64Id
				 &&  pMisCnt->subWnds.pMems[i].uiObjType  ==  uiObjType  
					&&  pMisCnt->subWnds.pMems[i].usIndex_obj  ==  usIndex_obj  )  
		 {
			 MACRO_SetForegroundWindow(  pMisCnt->subWnds.pMems[i].hWnd  );
			 iErr  =  0;  goto  errLabel;
		 }
	}

	//  为了将对远程的申请能及时取消，在dlgTalk里建立一个数组，方便对监控任务的跟踪，当监控窗口被关闭时，及时发现是监控任务，于是发消息给对方，要求不需要对方发数据过来了。
	//  应该先起监控窗口，在监控窗口里如有需要，可以启动talk窗口。然后，将监控窗口句柄放在msg里，填入监控任务数组。然后发送监控请求
	//  在这个函数里，需要先在talkers队列里，靠talk的数组去检索是否有这样窗口在。如果在，则激活。如果不在，才启动。


	//
	{
		unsigned  short		usCnt_monPics_row	=	1;
		unsigned  short		usCnt_monPics_col	=	1;
		//
		//
		unsigned  int  uiInitW  =  640;;
		unsigned  int  uiInitH  =  480;
		//
		//  pDlg  =  new  CDlgTestWebcam(  CWnd::GetDesktopWindow(  )  );
		pDlg  =  new  CDlgDynBmps(  CWnd::FromHandle(  hParent  )  );
		if  (  !pDlg  )  goto  errLabel;

		TCHAR	talkerDesc[128]  =  _T(  ""  );
		QY_MESSENGER_REGINFO		regInfo;
		MY_REG_DESC					desc;
						
		if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  misServName,  pIdInfo,  0,  &regInfo  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		//
		regInfo2Desc(  0,  &regInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  );
		_sntprintf(  talkerDesc,  mycountof(  talkerDesc  ),  _T(  "%s.%s.%d %s"  ),  talkerDesc,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  uiObjType  ),  usIndex_obj,  cusName  ?  cusName  :  _T(  ""  )  );  

		//  2017/01/10
		if  (  pParam->bValid_pos  )  {
			uiInitW  =  pParam->w;
			uiInitH  =  pParam->h;
		}

		//
		if  (  !pDlg->bSetDlgInfo(  iWndContentType,  0,  talkerDesc,  0,  pMisCnt,  usCnt_monPics_row,  usCnt_monPics_col,  uiInitW,  uiInitH  )  )  goto  errLabel;
		DLG_dynBmps_var  *  pm_var  =  pDlg->get_pm_var(  );
		if  (  !pm_var  )  goto  errLabel;
		DLG_dynBmps_var  &m_var  =  *pm_var;
		//
		if  (  pParam->bAvConsole  )  m_var.bAvConsole  =  TRUE;
		//
		if  (  pParam->bValid_pos  )  {
			CDlgDesktopsMon  *  pBase  =  pDlg;
		//  20167/02/13
			pDlg->m_var.param_bValid_pos  =  TRUE;
			pDlg->m_var.param_bFullScreen  =  pParam->bFullScreen;
		}
		//
		//if  (  !pParam->bValid_pos  )  
		{
			m_var.ucbAutoSize1  =  TRUE;
		}
		
		//
		m_var.vWall.idInfo.ui64Id  =  pIdInfo->ui64Id;
		m_var.vWall.uiObjType  =  uiObjType;
		m_var.vWall.usIndex_obj  =  usIndex_obj;
		if  (  cusName  )  lstrcpyn(  m_var.vWall.cusName,  cusName,  mycountof(  m_var.vWall.cusName  )  );

		if  (  !pDlg->Create(  rect  )  )  goto  errLabel;				
		//
		if  (  pParam->bNoBorder  )  {
			makeWndNoBorder(  pDlg->m_hWnd,  FALSE,  NULL,  NULL  );
		}
		if  (  pParam->bValid_pos  )  {
			POINT  pnt;
			pnt.x  =  pParam->x;
			pnt.y  =  pParam->y;
			MapWindowPoints(  hParent,  NULL,  &pnt,  1  );
			SetWindowPos(  pDlg->m_hWnd,  NULL,  pnt.x,  pnt.y,  pParam->w,  pParam->h,  0  );  
		}
		//  2017/01/10
		if  (  pParam->bValid_pos  ||  pParam->bNoBorder  )  {
#if  0
			m_var.quickToRetrieveImg.iTries  =  5;
			m_var.quickToRetrieveImg.ucbOn  =  TRUE;
#endif
			//
			dynBmps_setOn_quickToRetrieveImg(  pDlg,  TRUE  );
			//
			m_var.ucbNoBar  =  TRUE;
		}
		//
		//  2009/08/06
		//if  (  !pParam->bValid_pos  )  
		{
			pDlg->bEnableScrollBar(  TRUE  );
		}
		pDlg->doLayout(  );
		
		//
		if  (  pParam->bFullScreen  )  {
			//SendMessage(  pDlg->m_hWnd,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );
		}		
		
		//
		pDlg->ShowWindow(  SW_SHOW  );
		
		//

	}

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}

	traceLogA(  "viewDynBmp leaves with %s",  iErr  ?  "Failed"  :  "OK"  );

	return  iErr;
}


//
__declspec(  dllexport  ) int  findDynBmp(   LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj,  HWND  *  phWnd  ) 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr			=		-1;
	QY_MC				*	pQyMc			=		QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci			=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;	
	MC_VAR_isCli			*	pProcInfo		=		(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;
	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;
	//  
	CDlgDynBmps			*	pDlg			=		NULL;
	RECT					rect;
	CWaitCursor				cur;

	int						i;
	MIS_CNT				*	pMisCnt			=		getMisCntByName(  pProcInfo,  misServName  );
	if  (  !pMisCnt  )  return  -1;
	int						iWndContentType	=		CONST_qyWndContentType_vWall;

	traceLogA(  "findDynBmp enters"  );

	if  (  !pIdInfo  )  return  -1;
	if  (  !uiObjType  )  return  -1;
	
		
	//
	if  (  !pMisCnt->subWnds.usMaxCnt  ||  !pMisCnt->subWnds.pMems  )  {
		goto  errLabel;
	}
	for  (  i  =  0;  i  <  pMisCnt->subWnds.usMaxCnt;  i  ++  )  {
		 if  (  !IsWindow(  pMisCnt->subWnds.pMems[i].hWnd  )  )  continue;
		 //
		 if  (  pMisCnt->subWnds.pMems[i].iWndContentType  ==  iWndContentType
			 &&  pMisCnt->subWnds.pMems[i].idInfo.ui64Id  ==  pIdInfo->ui64Id
				 &&  pMisCnt->subWnds.pMems[i].uiObjType  ==  uiObjType  
					&&  pMisCnt->subWnds.pMems[i].usIndex_obj  ==  usIndex_obj  )  
		 {
			 *phWnd  =  (  pMisCnt->subWnds.pMems[i].hWnd  );
			 iErr  =  0;  goto  errLabel;
		 }
	}

errLabel:
	return  iErr;
}


///////////////////////////////

__declspec(  dllexport  ) int  closeDynBmp(  HWND  hParent,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj  ) 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr			=		-1;
	QY_MC				*	pQyMc			=		QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci			=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;	
	MC_VAR_isCli			*	pProcInfo		=		(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;
	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;
	//  
	RECT					rect;
	CWaitCursor				cur;

	int						i;
	MIS_CNT				*	pMisCnt			=		getMisCntByName(  pProcInfo,  misServName  );
	if  (  !pMisCnt  )  return  -1;
	int						iWndContentType	=		CONST_qyWndContentType_vWall;

#ifdef  __DEBUG__
	traceLogA(  "closeDynBmp enters"  );
#endif

	//
	if  (  !pIdInfo  )  return  -1;
	if  (  !uiObjType  )  return  -1;
		
	//
	if  (  !pMisCnt->subWnds.usMaxCnt  ||  !pMisCnt->subWnds.pMems  )  {
		goto  errLabel;
	}
	for  (  i  =  0;  i  <  pMisCnt->subWnds.usMaxCnt;  i  ++  )  {
		 if  (  !IsWindow(  pMisCnt->subWnds.pMems[i].hWnd  )  )  continue;
		 //
		 if  (  pMisCnt->subWnds.pMems[i].iWndContentType  ==  iWndContentType
			 &&  pMisCnt->subWnds.pMems[i].idInfo.ui64Id  ==  pIdInfo->ui64Id
				 &&  pMisCnt->subWnds.pMems[i].uiObjType  ==  uiObjType  
					&&  pMisCnt->subWnds.pMems[i].usIndex_obj  ==  usIndex_obj  )  
		 {
			 //MACRO_SetForegroundWindow(  pMisCnt->subWnds.pMems[i].hWnd  );
			 PostMessage(  pMisCnt->subWnds.pMems[i].hWnd,  WM_CLOSE,  0,  0  );
			 iErr  =  0;  goto  errLabel;
		 }
	}

	

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
	}

#ifdef  __DEBUG__
	traceLogA(  "closeDynBmp leaves with %s",  iErr  ?  "Failed"  :  "OK"  );
#endif

	return  iErr;
}

//
__declspec(  dllexport  ) int  closeAllDynBmps(  HWND  hParent,  LPCTSTR  misServName  ) 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr			=		-1;
	QY_MC				*	pQyMc			=		QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci			=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;	
	MC_VAR_isCli			*	pProcInfo		=		(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;
	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;
	//  
	RECT					rect;
	CWaitCursor				cur;

	int						i;
	MIS_CNT				*	pMisCnt			=		getMisCntByName(  pProcInfo,  misServName  );
	if  (  !pMisCnt  )  return  -1;
	int						iWndContentType	=		CONST_qyWndContentType_vWall;

	traceLogA(  "closeAllDynBmps enters"  );

		
	//
	if  (  !pMisCnt->subWnds.usMaxCnt  ||  !pMisCnt->subWnds.pMems  )  {
		goto  errLabel;
	}
	for  (  i  =  0;  i  <  pMisCnt->subWnds.usMaxCnt;  i  ++  )  {
		 if  (  !IsWindow(  pMisCnt->subWnds.pMems[i].hWnd  )  )  continue;
		 //
		 if  (  pMisCnt->subWnds.pMems[i].iWndContentType  ==  iWndContentType
			 )  
		 {
			 //MACRO_SetForegroundWindow(  pMisCnt->subWnds.pMems[i].hWnd  );
			 PostMessage(  pMisCnt->subWnds.pMems[i].hWnd,  WM_CLOSE,  0,  0  );
		 }
	}

	

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
	}

	traceLogA(  "closeAllDynBmps leaves with %s",  iErr  ?  "Failed"  :  "OK"  );

	return  iErr;
}












////////////////


//  2015/05/09
__declspec(  dllexport  ) int  viewQvcf(  HWND  hParent,  LPCTSTR  fileName  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr			=		-1;
	QY_MC				*	pQyMc			=		QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci			=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;	
	MC_VAR_isCli			*	pProcInfo		=		(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;
	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;
	//  
	CDlgDynBmps			*	pDlg			=		NULL;
	RECT					rect;
	CWaitCursor				cur;

	int						i;
	MIS_CNT				*	pMisCnt			=		getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;
	int						iWndContentType	=		CONST_qyWndContentType_vWall;
	int						iVwSubType		=		CONST_vwSubtype_qvcf;	//  


#ifdef  __DEBUG__
	traceLogA(  "viewQvcf enters"  );
#endif
		

	//  为了将对远程的申请能及时取消，在dlgTalk里建立一个数组，方便对监控任务的跟踪，当监控窗口被关闭时，及时发现是监控任务，于是发消息给对方，要求不需要对方发数据过来了。
	//  应该先起监控窗口，在监控窗口里如有需要，可以启动talk窗口。然后，将监控窗口句柄放在msg里，填入监控任务数组。然后发送监控请求
	//  在这个函数里，需要先在talkers队列里，靠talk的数组去检索是否有这样窗口在。如果在，则激活。如果不在，才启动。


	//
	{
		unsigned  short		usCnt_monPics_row	=	1;
		unsigned  short		usCnt_monPics_col	=	1;
		//
		//
		unsigned  int  uiInitW  =  640  +  30;
		unsigned  int  uiInitH  =  480  +  30;
		//
		//  pDlg  =  new  CDlgTestWebcam(  CWnd::GetDesktopWindow(  )  );
		pDlg  =  new  CDlgDynBmps(  CWnd::FromHandle(  hParent  )  );
		if  (  !pDlg  )  goto  errLabel;

		TCHAR	talkerDesc[128]  =  _T(  ""  );
		QY_MESSENGER_REGINFO		regInfo;
		MY_REG_DESC					desc;
						

		if  (  !pDlg->bSetDlgInfo(  iWndContentType,  iVwSubType,  talkerDesc,  0,  pMisCnt,  usCnt_monPics_row,  usCnt_monPics_col,  uiInitW  +  32,  uiInitH  +  32  )  )  goto  errLabel;
		DLG_dynBmps_var  *  pm_var  =  pDlg->get_pm_var(  );
		if  (  !pm_var  )  goto  errLabel;
		DLG_dynBmps_var  &  m_var  =  *pm_var;
		//
		//m_var.bUseDirectX  =  FALSE;
		//
		m_var.ucbAutoSize1  =  TRUE;
		
		//if  (  cusName  )  lstrcpyn(  pDlg->m_var.u.vWall.cusName,  cusName,  mycountof(  pDlg->m_var.u.vWall.cusName  )  );
		lstrcpyn(  m_var.vWall.fileName,  fileName,  mycountof(  m_var.vWall.fileName  )  );

		if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		
		//
		//  2009/08/06
		pDlg->bEnableScrollBar(  FALSE  );
		pDlg->doLayout(  );
		//
		pDlg->ShowWindow(  SW_SHOW  );
		//

	}

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}

#ifdef  __DEBUG__
	traceLogA(  "viewDynBmp leaves with %s",  iErr  ?  "Failed"  :  "OK"  );
#endif

	return  iErr;
}



 //  2012/07/08
 __declspec(  dllexport  )  LRESULT  myGuiSendMessage(  HWND hWnd,  int  iWndContentType,  UINT uMsg,  WPARAM wParam,  LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	LRESULT		lRet	=	-1;

	if  (  uMsg  !=  CONST_qyWm_comm  )  return  SendMessage(  hWnd,  uMsg,  wParam,  lParam  );


	switch  (  iWndContentType  )  {
			case  CONST_qyWndContentType_vWall:  {
				  CDlgDynBmps  *  pDlg  =  (  CDlgDynBmps  *  )CWnd::FromHandlePermanent(  hWnd  );
				  if  (  !pDlg  )  goto  errLabel;
				  lRet  =  pDlg->OnQyComm(  wParam,  lParam  );
				  }
				  break;
			default:
				    lRet  =  SendMessage(  hWnd,  uMsg,  wParam,  lParam  );
					break;
	}


errLabel:
	return  lRet;
}


 //  2015/12/05
 __declspec(  dllexport  )  void  *  getZoneObjs_dynBmps(  HWND  hDlgWalls,  int  iWndContentType  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//
	MACRO_qyAssert(  iWndContentType,  _T(  "getDlgWallsVar_default: iWndcontentType err, 0"  )  );

	if  (  iWndContentType  !=  CONST_qyWndContentType_vWall  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "getDlgWallsVar_default: iWndContentType err, %d"  ),  iWndContentType  );
		#endif
		return  NULL;
	}

	//
	if  (  !IsWindow(  hDlgWalls  )  )  return  NULL;
	CDlgDynBmps  *  pDlgWalls  =  (  CDlgDynBmps  *  )CWnd::FromHandlePermanent(  hDlgWalls  );
	if  (  !pDlgWalls  )  return  NULL;

	DLG_dynBmps_var  *  pm_var  =  pDlgWalls->get_pm_var(  );
	if  (  !pm_var  )  return  NULL;

	return  pm_var->pZoneObjs;
}


#if  1	//  def  __APP_qyMc__
__declspec(  dllexport  )  void  *  getZoneObjsInfo_dynBmps(  HWND  hDlgWalls,  int  iWndContentType  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//
	MACRO_qyAssert(  iWndContentType,  _T(  "getDlgWallsVar_default: iWndcontentType err, 0"  )  );

	if  (  iWndContentType  !=  CONST_qyWndContentType_vWall  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "getDlgWallsVar_default: iWndContentType err, %d"  ),  iWndContentType  );
		#endif
		return  NULL;
	}

	//
	if  (  !IsWindow(  hDlgWalls  )  )  return  NULL;
	CDlgDynBmps  *  pDlgWalls  =  (  CDlgDynBmps  *  )CWnd::FromHandlePermanent(  hDlgWalls  );
	if  (  !pDlgWalls  )  return  NULL;

	DLG_dynBmps_var  *  pm_var  =  pDlgWalls->get_pm_var(  );
	if  (  !pm_var  )  return  NULL;

	return  pm_var->pZoneObjsInfo_talkers;
}

__declspec(  dllexport  )  int  getRect_talkers_default(  HWND  hDlgWalls,  RECT  *  pRc  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iErr	=	-1;
	CDlgDynBmps  *  pDlgWalls  =  (  CDlgDynBmps  *  )CWnd::FromHandle(  hDlgWalls  );
	if  (  !pDlgWalls  )  return  -1;
	DLG_dynBmps_var  *  pm_var  =  pDlgWalls->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	ZONE_PARAM	zoneParam;
	if  (  pDlgWalls->findZoneParam(  TRUE,  &zoneParam  )  )  goto  errLabel;

	SUB_V_WALL  *	pSubWall	=  NULL;
	myZONE		*	pZone		=	NULL;

	pSubWall  =  m_var.pWall->getSubWall(  zoneParam.index_subWall  );
	if  (  !pSubWall  )  goto  errLabel;
	if  (  zoneParam.index_zone  <  0  ||  zoneParam.index_zone  >=  pSubWall->usCnt  )  {
		//  traceLogA(  "dlgDynBmps::OnQyComm failed: index_zone %d, subWall.usCnt %d",  pPlayer->video.m_var.zoneParam.index_zone,  pSubWall->usCnt  );
		goto  errLabel;
	}
	pZone	=	&pSubWall->mems[zoneParam.index_zone];

	pRc->left  =  pZone->iX;
	pRc->top  =  pZone->iY;
	pRc->right  =  pZone->iX  +  pZone->iW;
	pRc->bottom  =  pZone->iY  +  pZone->iH;

	if  (  pSubWall->idc  )  {
		HWND	hCtrl  =  GetDlgItem(  hDlgWalls,  pSubWall->idc  );
		MapWindowPoints(  hCtrl,  hDlgWalls,  (  LPPOINT  )pRc,  2  );
	}
	//  

	iErr  =  0;

errLabel:

	if  (  iErr  )  {	//  如果错误的话,就覆盖到全窗口
	  GetClientRect(  hDlgWalls,  pRc  );
	}

	return  iErr;
}



//__declspec(  dllexport  )  BOOL  bFullScreen_walls_default(  HWND  hDlgWalls,  int  iWndContentType  )
__declspec(  dllexport  )  BOOL  bFullScreen_wnd_default(  HWND  hWnd,  int  iWndContentType  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	BOOL	bRet	=	FALSE;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp			*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;


	switch  (  iWndContentType  )  {
			case  CONST_qyWndContentType_talker:  {
				  CHelp_getDlgTalkVar	help_getDlgTalkVar;
				  DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hWnd  );
				  if  (  !pDlgTalkVar  )  goto  errLabel;
				  bRet  =  pDlgTalkVar->m_bFullScreen;
				  }
				  break;
			case  CONST_qyWndContentType_vWall:  {
				  //
				  CDlgDynBmps  *  pDlgWalls  =  (  CDlgDynBmps  *  )CWnd::FromHandle(  hWnd  );
				  if  (  !pDlgWalls  )  goto  errLabel;
				  
				  CDlgDesktopsMon  *  pBase  =  pDlgWalls;
				  bRet  =  pBase->m_var.m_bFullScreen;
				  }
				  break;

			case  CONST_qyWndContentType_consoleWall:  
			case  CONST_qyWndContentType_generalWall:
				{  //  2015/06/07
				  //
				  if  (  !pFuncs->isCliD3d.pf_bFullScreen_d3dWnd  )  goto  errLabel;
				  //
				  bRet  =  pFuncs->isCliD3d.pf_bFullScreen_d3dWnd(  hWnd  );
				  }
				  break;
			default:{
					ZONE_objs_info  *  pDlgWallVar  =  (  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  hWnd,  iWndContentType,  0  );
					if  (  !pDlgWallVar  )  goto  errLabel;

					bRet  =  pDlgWallVar->m_bFullScreen;
					break;					
					}

	}


errLabel:
	return  bRet;

}

#endif

 //
 __declspec(  dllexport  )  int  addToWallGpsMgr(  HWND  hDlgTalk,  int  iIndex_shadow,  void  *  pmyGPS_POSITION,  HWND  hDlgWall  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr		=	-1;

	myGPS_POSITION  *  pGpsPos  =  (  myGPS_POSITION  *  )pmyGPS_POSITION;

	if  (  !hDlgTalk  )  return  -1;
	if  (  !pGpsPos  )  return  -1;

	if  (  !IsWindow(  hDlgWall  )  )  return  -1;
	CDlgDynBmps  *  pDlg  =  (  CDlgDynBmps  *  )CWnd::FromHandle(  hDlgWall  );
	if  (  !pDlg  )  return  -1;	
	DLG_dynBmps_var	*	pWallVar  =  pDlg->get_pm_var(  );
	if  (  !pWallVar  )  return  -1;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pWallVar->wallGpsMgr.mems  );  i  ++  )  {
		 if  (  !pWallVar->wallGpsMgr.mems[i].hMem  )  break;
		 if  (  pWallVar->wallGpsMgr.mems[i].hMem  ==  hDlgTalk  )  break;
	}
	if  (  i  ==  mycountof(  pWallVar->wallGpsMgr.mems  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "addToWallGpsMgr failed, too many mems"  )  );

		goto  errLabel;
	}

	if  (  !pWallVar->wallGpsMgr.mems[i].hMem  )  {
		pWallVar->wallGpsMgr.mems[i].hMem  =  hDlgTalk;
	}


	pWallVar->wallGpsMgr.mems[i].iIndex_shadow  =  iIndex_shadow;
	memcpy(  &pWallVar->wallGpsMgr.mems[i].gpsPos,  pGpsPos,  sizeof(  pWallVar->wallGpsMgr.mems[i].gpsPos  )  );

	
	iErr  =  0;

errLabel:
	return  iErr;

}


//
__declspec(  dllexport  )  int  viewVWall(  HWND  hParent,  LPCTSTR  misServName,  int  iSubType,  BOOL  bNewVirtualWall,  LPCTSTR  init_qvwFile,  BOOL  bNeedNotShowWnd,  HWND  *  phWnd  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr			=		-1;
	QY_MC				*	pQyMc			=		QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci			=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;	
	MC_VAR_isCli			*	pProcInfo		=		(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;
	//  
	CDlgDynBmps			*	pDlg			=		NULL;
	RECT					rect;
	CWaitCursor				cur;

	//  int						i;
	MIS_CNT				*	pMisCnt			=		getMisCntByName(  pProcInfo,  misServName  );
	if  (  !pMisCnt  )  return  -1;
	int						iWndContentType	=		CONST_qyWndContentType_vWall;


#ifdef  __DEBUG__
	traceLogA(  "viewVirtualWall enters"  );
#endif

	//
	if  (  isVwSubtype_gps(  iSubType  )  )  {
		if  (  !bSupported_gps(  pQyMc  )  )  goto  errLabel;
	}
		
	/*
	for  (  i  =  0;  i  <  mycountof(  pMisCnt->subWnds.mems  );  i  ++  )  {
		 if  (  !IsWindow(  pMisCnt->subWnds.mems[i].hWnd  )  )  continue;
		 if  (  pMisCnt->subWnds.mems[i].iWndContentType  ==  iWndContentType
			 &&  pMisCnt->subWnds.mems[i].idInfo.ui64Id  ==  pIdInfo->ui64Id
				 &&  pMisCnt->subWnds.mems[i].uiObjType  ==  uiObjType  
					&&  pMisCnt->subWnds.mems[i].usIndex  ==  usIndex  )  
		 {
			 MACRO_SetForegroundWindow(  pMisCnt->subWnds.mems[i].hWnd  );
			 iErr  =  0;  goto  errLabel;
		 }
	}
	*/

	//
	{
		unsigned  short		usCnt_monPics_row	=	1;
		unsigned  short		usCnt_monPics_col	=	1;
		//
		//
		unsigned  int  uiInitW  =  640;	//DEFAULT_uiInitW_wall;
		unsigned  int  uiInitH  =  480;	//DEFAULT_uiInitH_wall;
		get_default_wh_wall(  &uiInitW,  &uiInitH  );
		//
#ifdef  __DEBUG__  //  2015/12/08
#if  0
		uiInitW  =  320;
		uiInitH  =  240;
#endif
#endif
		//
		pDlg  =  new  CDlgDynBmps(  CWnd::FromHandle(  hParent  )  );
		if  (  !pDlg  )  goto  errLabel;

		TCHAR	titleDesc[128]  =  _T(  "Virtual Wall"  );
		_sntprintf(  titleDesc,  mycountof(  titleDesc  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_vWall  )  );  
		

		//  if  (  bNewVirtualWall  )  _sntprintf(  talkerDesc,  mycountof(  talkerDesc  ),  _T(  "New Virtual Wall"  )  );
		//  if  (  bNewVirtualWall  )  _sntprintf(  titleDesc,  mycountof(  titleDesc  ),  _T(  "Wall"  )  );
		if  (  bNewVirtualWall  )  _sntprintf(  titleDesc,  mycountof(  titleDesc  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_vWall  )  );

		if  (  !pDlg->bSetDlgInfo(  iWndContentType,  iSubType,  titleDesc,  CONST_resId_menu_dlgVWall,  pMisCnt,  usCnt_monPics_row,  usCnt_monPics_col,  uiInitW,  uiInitH  )  )  goto  errLabel;
		DLG_dynBmps_var  *  pm_var  =  pDlg->get_pm_var(  );
		if  (  !pm_var  )  goto  errLabel;
		DLG_dynBmps_var  &m_var  =  *pm_var;

		//m_var.bUseDirectX  =  FALSE;
		
		//
		if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		
		//
		if  (  bFileExists(  init_qvwFile  )  )  {		
			pDlg->openFile(  init_qvwFile  );
		}
		//
		if  (  bNewVirtualWall  )  {
			pDlg->Onstarttoedit(  );
			pDlg->Onstarttoshowrules(  );
			}
		else  {
			  //
			  pDlg->Onstarttoedit(  );
			  pDlg->Onstopediting(  );
			  //
			  pDlg->bEnableScrollBar(  FALSE  );		//  2009/08/06
			  pDlg->doLayout(  );
			  //

		}

		//
		if  (  !bNeedNotShowWnd  )  {
			pDlg->ShowWindow(  SW_SHOW  );
		}
		//
		if  (  bNewVirtualWall  )  viewToolbox_sketchpad(  pDlg->m_hWnd,  &m_var  );	

	}

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
		if  (  phWnd  )  {
			if  (  pDlg  )  {
				*phWnd  =  pDlg->m_hWnd;
			}
		} 
	}

#ifdef  __DEBUG__
	traceLogA(  "viewVirtualWall leaves with %s",  iErr  ?  "Failed"  :  "OK"  );
#endif

	return  iErr;
}


//
__declspec(  dllexport  )  int  viewVWall_hbwj(  HWND  hParent,  LPCTSTR  misServName,  int  iSubType,  BOOL  bNewVirtualWall,  QY_MESSENGER_ID  *  pIdInfo_grp_avStream,  LPCTSTR  init_qvwFile,  BOOL  bNeedNotShowWnd,  HWND  *  phWnd  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr			=		-1;
	QY_MC				*	pQyMc			=		QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci			=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;	
	MC_VAR_isCli			*	pProcInfo		=		(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;
	//  
	CDlgDynBmps			*	pDlg			=		NULL;
	RECT					rect;
	CWaitCursor				cur;

	//  int						i;
	MIS_CNT				*	pMisCnt			=		getMisCntByName(  pProcInfo,  misServName  );
	if  (  !pMisCnt  )  return  -1;
	int						iWndContentType	=		CONST_qyWndContentType_vWall;


#ifdef  __DEBUG__
	traceLogA(  "viewVirtualWall enters"  );
#endif

	//
	if  (  isVwSubtype_gps(  iSubType  )  )  {
		if  (  !bSupported_gps(  pQyMc  )  )  goto  errLabel;
	}
		
	/*
	for  (  i  =  0;  i  <  mycountof(  pMisCnt->subWnds.mems  );  i  ++  )  {
		 if  (  !IsWindow(  pMisCnt->subWnds.mems[i].hWnd  )  )  continue;
		 if  (  pMisCnt->subWnds.mems[i].iWndContentType  ==  iWndContentType
			 &&  pMisCnt->subWnds.mems[i].idInfo.ui64Id  ==  pIdInfo->ui64Id
				 &&  pMisCnt->subWnds.mems[i].uiObjType  ==  uiObjType  
					&&  pMisCnt->subWnds.mems[i].usIndex  ==  usIndex  )  
		 {
			 MACRO_SetForegroundWindow(  pMisCnt->subWnds.mems[i].hWnd  );
			 iErr  =  0;  goto  errLabel;
		 }
	}
	*/

	//
	{
		unsigned  short		usCnt_monPics_row	=	1;
		unsigned  short		usCnt_monPics_col	=	1;
		//
		//
		unsigned  int  uiInitW  =  640;	//DEFAULT_uiInitW_wall;
		unsigned  int  uiInitH  =  480;	//DEFAULT_uiInitH_wall;
		get_default_wh_wall(  &uiInitW,  &uiInitH  );
		//
#ifdef  __DEBUG__  //  2015/12/08
#if  0
		uiInitW  =  320;
		uiInitH  =  240;
#endif
#endif
		//
		pDlg  =  new  CDlgDynBmps(  CWnd::FromHandle(  hParent  )  );
		if  (  !pDlg  )  goto  errLabel;

		TCHAR	titleDesc[128]  =  _T(  "Virtual Wall"  );
		_sntprintf(  titleDesc,  mycountof(  titleDesc  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_vWall  )  );  
						
		//  if  (  bNewVirtualWall  )  _sntprintf(  talkerDesc,  mycountof(  talkerDesc  ),  _T(  "New Virtual Wall"  )  );
		if  (  bNewVirtualWall  )  _sntprintf(  titleDesc,  mycountof(  titleDesc  ),  _T(  "Wall"  )  );

		if  (  !pDlg->bSetDlgInfo(  iWndContentType,  iSubType,  titleDesc,  CONST_resId_menu_dlgVWall,  pMisCnt,  usCnt_monPics_row,  usCnt_monPics_col,  uiInitW,  uiInitH  )  )  goto  errLabel;
		DLG_dynBmps_var  *  pm_var  =  pDlg->get_pm_var(  );
		if  (  !pm_var  )  goto  errLabel;
		DLG_dynBmps_var  &m_var  =  *pm_var;

		//m_var.bUseDirectX  =  FALSE;
		//
		m_var.vWall.idInfo_grp_avStream.ui64Id  =  pIdInfo_grp_avStream->ui64Id;
		
		//
		if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		

		//
		if  (  bFileExists(  init_qvwFile  )  )  {		
			pDlg->openFile(  init_qvwFile  );
		}
		//
		if  (  bNewVirtualWall  )  {
			pDlg->Onstarttoedit(  );
			pDlg->Onstarttoshowrules(  );
			}
		else  {
			  //
			  pDlg->Onstarttoedit(  );
			  pDlg->Onstopediting(  );
			  //
			  pDlg->bEnableScrollBar(  FALSE  );		//  2009/08/06
			  pDlg->doLayout(  );
			  //

		}

		//
		if  (  !bNeedNotShowWnd  )  {
			pDlg->ShowWindow(  SW_SHOW  );
		}
		//
		if  (  bNewVirtualWall  )  viewToolbox_sketchpad(  pDlg->m_hWnd,  &m_var  );	

	}

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
		if  (  phWnd  )  {
			if  (  pDlg  )  {
				*phWnd  =  pDlg->m_hWnd;
			}
		} 
	}

#ifdef  __DEBUG__
	traceLogA(  "viewVirtualWall leaves with %s",  iErr  ?  "Failed"  :  "OK"  );
#endif

	return  iErr;
}


//
__declspec(  dllexport  )  int  viewBgWall(  HWND  hParent,  LPCTSTR  misServName,  int  iSubType,  HWND  hDlgTalk_mgr,  LPCTSTR  init_qvwFile,  BOOL  bNeedNotShowWnd,  HWND  *  phWnd  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr			=		-1;
	QY_MC				*	pQyMc			=		QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci			=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;	
	MC_VAR_isCli			*	pProcInfo		=		(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;
	//  
	CDlgDynBmps			*	pDlg			=		NULL;
	RECT					rect;
	CWaitCursor				cur;

	//  int						i;
	MIS_CNT				*	pMisCnt			=		getMisCntByName(  pProcInfo,  misServName  );
	if  (  !pMisCnt  )  return  -1;
	int						iWndContentType	=		CONST_qyWndContentType_vWall;


#ifdef  __DEBUG__
	traceLogA(  "viewBgWall enters"  );
#endif

	//
	if  (  isVwSubtype_gps(  iSubType  )  )  {
		if  (  !bSupported_gps(  pQyMc  )  )  goto  errLabel;
	}
		
	/*
	for  (  i  =  0;  i  <  mycountof(  pMisCnt->subWnds.mems  );  i  ++  )  {
		 if  (  !IsWindow(  pMisCnt->subWnds.mems[i].hWnd  )  )  continue;
		 if  (  pMisCnt->subWnds.mems[i].iWndContentType  ==  iWndContentType
			 &&  pMisCnt->subWnds.mems[i].idInfo.ui64Id  ==  pIdInfo->ui64Id
				 &&  pMisCnt->subWnds.mems[i].uiObjType  ==  uiObjType  
					&&  pMisCnt->subWnds.mems[i].usIndex  ==  usIndex  )  
		 {
			 MACRO_SetForegroundWindow(  pMisCnt->subWnds.mems[i].hWnd  );
			 iErr  =  0;  goto  errLabel;
		 }
	}
	*/

	//
	{
		unsigned  short		usCnt_monPics_row	=	1;
		unsigned  short		usCnt_monPics_col	=	1;
		//
		//
		unsigned  int  uiInitW  =  640;	//DEFAULT_uiInitW_wall;
		unsigned  int  uiInitH  =  480;	//DEFAULT_uiInitH_wall;
		get_default_wh_wall(  &uiInitW,  &uiInitH  );
		//
#ifdef  __DEBUG__  //  2015/12/08
#if  0
		uiInitW  =  320;
		uiInitH  =  240;
#endif
#endif
		//
		pDlg  =  new  CDlgDynBmps(  CWnd::FromHandle(  hParent  )  );
		if  (  !pDlg  )  goto  errLabel;

		TCHAR	titleDesc[128]  =  _T(  "Virtual Wall"  );
		_sntprintf(  titleDesc,  mycountof(  titleDesc  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_vWall  )  );  
						
		//  
		//
		if  (  !pDlg->bSetDlgInfo(  iWndContentType,  iSubType,  titleDesc,  CONST_resId_menu_dlgVWall,  pMisCnt,  usCnt_monPics_row,  usCnt_monPics_col,  uiInitW,  uiInitH  )  )  goto  errLabel;
		DLG_dynBmps_var  *  pm_var  =  pDlg->get_pm_var(  );
		if  (  !pm_var  )  goto  errLabel;
		DLG_dynBmps_var  &m_var  =  *pm_var;

		//
		m_var.vWall.hDlgTalk_mgr  =  hDlgTalk_mgr;
		
		//
		if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		
		//
		if  (  bFileExists(  init_qvwFile  )  )  {		
			pDlg->openFile(  init_qvwFile  );
		}
		//
		{
			  pDlg->bEnableScrollBar(  FALSE  );		//  2009/08/06
			  pDlg->doLayout(  );
		}

		//
		if  (  !bNeedNotShowWnd  )  {
			pDlg->ShowWindow(  SW_SHOW  );
		}
		//

	}

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
		if  (  phWnd  )  {
			if  (  pDlg  )  {
				*phWnd  =  pDlg->m_hWnd;
			}
		} 
	}

#ifdef  __DEBUG__
	traceLogA(  "viewBgWall leaves with %s",  iErr  ?  "Failed"  :  "OK"  );
#endif

	return  iErr;
}






//
//  2017/11/06
 __declspec(  dllexport  )  int  dynBmps_autoLayout(  HWND  hDlgDynBmps  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int   iErr  =  -1;
	if  (  !IsWindow(  hDlgDynBmps  )  )  return  -1;
	CDlgDynBmps  *  pDlgDynBmps  =  (  CDlgDynBmps  *  )CWnd::FromHandlePermanent(  hDlgDynBmps  );
	if  (  !pDlgDynBmps  )  return  -1;

	//
	//
	pDlgDynBmps->doAutoLayout_talker(  );
	

	iErr  =  0;
errLabel:
	return  iErr;

}



//  2017/11/06
__declspec(  dllexport  )  int  dynBmps_openFile(  LPCTSTR  fileName,  HWND  hDlgDynBmps  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int   iErr  =  -1;
	if  (  !IsWindow(  hDlgDynBmps  )  )  return  -1;
	CDlgDynBmps  *  pDlgDynBmps  =  (  CDlgDynBmps  *  )CWnd::FromHandlePermanent(  hDlgDynBmps  );
	if  (  !pDlgDynBmps  )  return  -1;

	//
	if  (  !bFileExists(  fileName  )  )  return  -1;
	//
	pDlgDynBmps->openFile(  fileName  );


	iErr  =  0;
errLabel:
	return  iErr;

}






//
  __declspec(  dllexport  )  void  *  getDlgDynBmpsVar(  HWND  hDlgDynBmps  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if  (  !IsWindow(  hDlgDynBmps  )  )  return  NULL;
	CDlgDynBmps  *  pDlg  =  (  CDlgDynBmps  *  )CDlgDynBmps::FromHandlePermanent(  hDlgDynBmps  );
	if  (  !pDlg  )  return  NULL;

	return  pDlg->get_pm_var();
}
 
// CDlgDynBmps dialog

//  IMPLEMENT_DYNAMIC(CDlgDynBmps, CDlgDesktopsMon)

CDlgDynBmps::CDlgDynBmps(CWnd* pParent /*=NULL*/)
	: CDlgDesktopsMon( pParent)
{
	//
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;

	//  2015/11/20
	//
	this->iIndex_objVarInfo  =  -1;

	//
	int  iTalkerDataType  =  CONST_objVarDataType_dlgDynBmps;
	this->iIndex_objVarInfo  =  newQmcObjVarInfoIndex(  pProcInfo,  iTalkerDataType,  0  );
	if  (  this->iIndex_objVarInfo  <  0  )  return;
	
	//
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &  m_var  =  *pm_var;


	//memset(  &m_var,  0,  sizeof(  m_var  )  );
	
	//  2015/11/15
	m_var.iIndex_objVarInfo  =  this->iIndex_objVarInfo;

	//
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	//m_var.bUseDirectX  =  pQyMc->cfg.bUseDxSurface;	//  2009/08/06

	//  2014/04/13
	m_var.ucbAutoClip  =  TRUE;
}

CDlgDynBmps::~CDlgDynBmps()
{
	//
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;

	//  2015/11/20	
	freeQmcObjVarInfoIndex(  pProcInfo,  this->iIndex_objVarInfo  );

	//
	qmcApplyForChkingTasks_gui(  pProcInfo->pQyMc  );	//  2009/09/10
}


//  2015/11/20
//  2015/11/13
DLG_dynBmps_var  *  CDlgDynBmps::get_pm_var()
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  NULL;

	DLG_dynBmps_var  *  pm_var  =  NULL;
	QMC_objVar_info  *  pTalkerInfo  =  getQmcObjVarInfoByIndex(  pProcInfo,  this->iIndex_objVarInfo  );
	if  (  !pTalkerInfo  )  return  NULL;
	if  (  !pTalkerInfo->bUsed  )  return  NULL;
	
	pm_var  =  (  DLG_dynBmps_var  *  )pTalkerInfo->var.pData;
	if  (  !pm_var  )  return  NULL;
	if  (  pm_var->uiType  !=  CONST_objVarDataType_dlgDynBmps  )  return  NULL;

	return  pm_var;
}




 //  
 BOOL  CDlgDynBmps::bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_menu,  MIS_CNT  *  pMisCnt,  unsigned  short  usCnt_row,  unsigned  short  usCnt_col,  unsigned  int  uiInitW_pc,  unsigned  int  uiInitH_pic  )
{
	BOOL							bRet		=	FALSE;
	QY_MC						*	pQyMc		=	QY_GET_GBUF(  );

	if  (  !pMisCnt  )  {
		#ifdef  __DEBUG__
				traceLogA(  "dlgDynBmps: bSetDlgInfo failed. pMisCnt is null"  );
		#endif
		return  FALSE;
	}

	if  (  !iResId_menu  )  iResId_menu  =  CONST_resId_menu_dlgVideos;

	if  (  !::CDlgDesktopsMon::bSetDlgInfo(  iWndContentType,  iSubType,  iResId_menu,  usCnt_row,  usCnt_col,  uiInitW_pc,  uiInitH_pic  )  )  goto  errLabel;

	//
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	if  (  title  )  lstrcpyn(  m_var.title,  title,  mycountof(  m_var.title  )  );
	m_var.pMisCnt  =  pMisCnt;
	//

	bRet  =  TRUE;
errLabel:
	return  bRet;
}



 int  CDlgDynBmps::toChkTask(  QY_WMBUF_COMM  *  pComm  )
{
	int		iErr	=	-1;
	BOOL	bFound  =  FALSE;

	if  (  !pComm  )  return  -1;
	if  (  pComm->uiType  !=  CONST_qyWmParam_chkTask  )  return  -1;

	//  2015/05/25
	if  (  getWndContentSubtype(  )  ==  CONST_vwSubtype_qvcf  )  {
		return  -1;
	}

#if  0
	switch  (  getWndContentType(  )  )  {
			case  CONST_qyWndContentType_vWall:
				  int  i;
				  for  (  i  =  0;  !bFound  &&  i  <  m_var.pWall->m_var.usCnt;  i  ++  )  {
					   qTraverse(  m_var.pWall->getSubWall(  i  )->pRuleQ,  tmpHandler_toChkTask_vw,  pComm,  &bFound  );
				  }
				  break;
			default:
					break;
	}
#endif
	if  (  !bFound  )  {
		pComm->u.chkTask.bNotExists  =  TRUE;
	}

	pComm->u.chkTask.bChked  =  TRUE;


	return  0;
}


  int  CDlgDynBmps::processKeyEvent(  UINT  nChar, DWORD  keyData  )
{
	int  iErr  =  -1;
	UINT nRepCnt	=	LOWORD(  keyData  );
	UINT nFlags		=	HIWORD(  keyData  );

		
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );	
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	//
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	//
	SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )m_var.pWall->getCurSp(  );
	if  (  pSp  )  {
		BOOL	bRedraw  =  TRUE;

		switch  (  nChar  )  {
			    case VK_DELETE:
					 if  (  pSp->tranType  !=  NO_TRAN  )  break;						
					 spProcKeyDelete( pSp, nFlags );
					 //
					 this->refreshWallBySp(  m_var.pWall->m_var.curSpIndex  );
					 qmcApplyForChkingTasks_gui(  pQyMc  );		//  2009/10/12										
					 break;
				default:
					    bRedraw  =  FALSE;
						break;
		}

		if  (  bRedraw  )  {
			Invalidate( FALSE );
			UpdateWindow();
		}
	}

	iErr  =  0;
errLabel:

	return  iErr;
}


  int  tmpHandler_bRuleSpUnmatched(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int		iErr	=	-1;
	//  p0
	SUB_V_WALL	*	pSubWall	=	(  SUB_V_WALL  *  )p1;
	VW_ruleU	*	pRuleElem	=	(  VW_ruleU  *  )p2;

	if  (  !findSpQNode(  (  SP_STRUCT  *  )pSubWall->pSp,  pRuleElem->common.uiTranNo_spObj  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;
}

  //
  QY_DMITEM  CONST_idcStaticDescTable[]  =
  {
	  {		IDC_STATIC60, },
	  {		IDC_STATIC61, },
	  {		IDC_STATIC62, },
	  {		IDC_STATIC63, },
	  {		IDC_STATIC64, },
	  {		IDC_STATIC65, },
	  {		IDC_STATIC66, },
	  {		IDC_STATIC67, },
	  {		IDC_STATIC68, },
	  {		IDC_STATIC69, },
	  //
	  {		IDC_STATIC70, },
	  {		IDC_STATIC71, },
	  {		IDC_STATIC72, },
	  {		IDC_STATIC73, },
	  {		IDC_STATIC74, },
	  {		IDC_STATIC75, },
	  {		IDC_STATIC76, },
	  {		IDC_STATIC77, },
	  {		IDC_STATIC78, },
	  {		IDC_STATIC79, },
	  //
  	  {		IDC_STATIC80, },
	  {		IDC_STATIC81, },
	  {		IDC_STATIC82, },
	  {		IDC_STATIC83, },
	  {		IDC_STATIC84, },
	  {		IDC_STATIC85, },
	  {		IDC_STATIC86, },
	  {		IDC_STATIC87, },
	  {		IDC_STATIC88, },
	  {		IDC_STATIC89, },
	  //
  	  {		IDC_STATIC90, },
	  {		IDC_STATIC91, },
	  {		IDC_STATIC92, },
	  {		IDC_STATIC93, },
	  {		IDC_STATIC94, },
	  {		IDC_STATIC95, },
	  {		IDC_STATIC96, },
	  {		IDC_STATIC97, },
	  {		IDC_STATIC98, },
	  {		IDC_STATIC99, },


  };


  //
 int  CDlgDynBmps::refreshWallBySp(  int  spIndex  )
{
	int				iErr		=		-1;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	//
	if  (  spIndex  <  0  ||  spIndex  >=  m_var.pWall->m_var.usCnt  )  return  -1;
	SUB_V_WALL	*	pSubWall	=		m_var.pWall->getSubWall(  spIndex  );
	if  (  !pSubWall  )  return  -1;
	MC_VAR_isCli	*	pProcInfo	=		QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	QY_MC		*	pQyMc		=		(  QY_MC  *  )pProcInfo->pQyMc;
	SP_STRUCT	*	pSp			=		(  SP_STRUCT  *  )pSubWall->pSp;
	Q_NODE		*	pQNode;
	SP_OBJ		*	pSpObj;
	int				nZones		=		0;
	myZONE		*	pZone		=		NULL;
	RECT			rect;

	for  (  pQNode  =  pSp->pSpObjQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf  &&  nZones  <  mycountof(  pSubWall->mems  );  pQNode  =  pQNode->pNext  )  {
		 pSpObj  =  (  SP_OBJ  *  )pQNode->qElemMemory.m_pBuf;
		 if  (  pSpObj->type  ==  SP_RECTANGLE_TYPE  )  {
			 if  (  getSpRect(  (  SP_RECTANGLE  *  )pSpObj,  &rect  )  )  goto  errLabel;
			 //  
			 pZone  =  &pSubWall->mems[nZones];
			 //
			 //  2019/01/23
			 if  (  nZones  <  mycountof(  CONST_idcStaticDescTable  )  )  {
				 pZone->idcStatic_desc  =  CONST_idcStaticDescTable[nZones].type;
			 }
			 //
			 if  (  pZone->iX_org  !=  rect.left  
				 ||  pZone->iY_org  !=  rect.top
				  ||  pZone->iW_org  !=  (  rect.right  -  rect.left  )
				   ||  pZone->iH_org  !=  (  rect.bottom  -  rect.top  )  
					||  pZone->uiTranNo_spObj  !=  pSpObj->uiTranNo  )
			 {
				 freeCapImages(  this->m_hWnd,  pSubWall->idc,  &pZone->images,  pSubWall->hWnd_dst,  NULL  );

				 pZone->iX_org  =  rect.left;
				 pZone->iY_org  =  rect.top;
				 pZone->iW_org  =  rect.right  -  rect.left;
				 pZone->iH_org  =  rect.bottom  -  rect.top;

				 pZone->uiTranNo_spObj  =  pSpObj->uiTranNo;

				 sizeZone(  pSubWall,  pZone  );
			 }
			 
			 //
			 nZones  ++  ;
			 continue;
		 }
	}
	int  i;
	for  (  i  =  nZones;  i  <  pSubWall->usCnt;  i  ++  )  {
		 pZone  =  &pSubWall->mems[i];
		 freeCapImages(  this->m_hWnd,  pSubWall->idc,  &pZone->images,  pSubWall->hWnd_dst,  NULL  );
	}
	pSubWall->usCnt  =  nZones;

	//
#if  10
	if  (  nZones  <  mycountof(  CONST_idcStaticDescTable  )  )  {
		QY_DMITEM  *  pItem;
		for  (  i  =  nZones;  i  <  mycountof(  CONST_idcStaticDescTable  );  i  ++  )  {
			 pItem  =  &CONST_idcStaticDescTable[i];
			 ::ShowWindow(  ::GetDlgItem(  m_hWnd,  pItem->type  ),  SW_HIDE  );
		}
	}
#endif

	//
	qRemoveMsg(  pSubWall->pRuleQ,  tmpHandler_bRuleSpUnmatched,  0,  pSubWall  );

	//
	if  (  m_var.ucbShowRules  )  showRules(  spIndex  );

	iErr  =  0;
errLabel:
	return  iErr;
}


 //
 int  CDlgDynBmps::refreshWallByRules(  int  spIndex  )
{
	int				iErr		=		-1;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	if  (  spIndex  <  0  ||  spIndex  >=  m_var.pWall->m_var.usCnt  )  return  -1;
	SUB_V_WALL	*	pSubWall	=		m_var.pWall->getSubWall(  spIndex  );
	if  (  !pSubWall  )  return  -1;
	MC_VAR_isCli	*	pProcInfo	=		QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	QY_MC		*	pQyMc		=		(  QY_MC  *  )pProcInfo->pQyMc;
	Q_NODE		*	pQNode;
	myZONE		*	pZone		=		NULL;
	CWnd	*	pWnd	=	pSubWall->idc  ?  GetDlgItem(  pSubWall->idc  )  :  this;
	if  (  !pWnd  )  return  -1;
	int				i;
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;


	//
	for  (  i  =  0;  i  <  pSubWall->usCnt;  i  ++  )  {
		 pZone  =  &pSubWall->mems[i];
		 if  (  !pZone->images.head.usCnt  )  continue;
		 //
		 freeCapImages(  this->m_hWnd,  pSubWall->idc,  &pZone->images,  pSubWall->hWnd_dst,  NULL  );
	}

	//  2015/11/24
	for  (  i  =  0;  i  <  pSubWall->usCnt;  i  ++  )  {
		 pZone  =  &pSubWall->mems[i];
		 //
		 if  (  !pZone->uiTranNo_spObj  )  continue;
		 
		 //
		 memset(  &pZone->rule,  0,  sizeof(  pZone->rule  )  );

		 //
		 for  (  pQNode  =  pSubWall->pRuleQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf;  pQNode  =  pQNode->pNext  )  {
			 //  2016/08/08
			 if  (  !pQNode->size  )  continue;
			 //
			 VW_ruleU	*	pRule	=	(  VW_ruleU  *  )pQNode->qElemMemory.m_pBuf;
			 if  (  !pRule  )  continue;
			 //
			 int				j;
			 if  (  pZone->uiTranNo_spObj  ==  pRule->common.uiTranNo_spObj  )  {
				 //pZone->rule  =  *pRule;
				 //  2016/08/08
				 memcpy(  &pZone->rule,  pRule,  min(  sizeof(  pZone->rule  ),  pQNode->size  )  );
				 //
				 break;			
			 }
		 }

		 //
		 TCHAR  tBuf[128];
		 tBuf[0]  =  0;
		 switch  (  pZone->rule.common.uiType  )  {
				 case  CONST_vwRuleType_dynBmp:
					   //_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pZone->rule.dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id  );
					   getTalkerDesc(  pMisCnt,  &pZone->rule.dynBmp.ruleDynBmp.dynBmp.idInfo,  tBuf,  mycountof(  tBuf  ),  NULL,  0  );
					   break;
				 default:
						break;
		 }
		 SetDlgItemText(  pZone->idcStatic_desc,  tBuf  );
					   

		 //  2017/10/31
		 timestamp_renew(  0,  &pZone->ts_zone  );

		 //
		 continue;
	}

	//
	iErr  =  0;
//  errLabel:

	return  iErr;
}




 //
 int  CDlgDynBmps::showRules(  int  spIndex  )
{
	int				iErr		=		-1;

	CDlgDesktopsMon  *  pBase  =  this;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	if  (  spIndex  <  0  ||  spIndex  >=  m_var.pWall->m_var.usCnt  )  return  -1;
	SUB_V_WALL	*	pSubWall	=		m_var.pWall->getSubWall(  spIndex  );
	if  (  !pSubWall  )  return  -1;
	MC_VAR_isCli	*	pProcInfo	=		QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	QY_MC		*	pQyMc		=		(  QY_MC  *  )pProcInfo->pQyMc;
	Q_NODE		*	pQNode;
	myZONE		*	pZone		=		NULL;
	HWND			hWnd_dst	=		pSubWall->hWnd_dst  ?  pSubWall->hWnd_dst  :  m_hWnd;
	if  (  !IsWindow(  hWnd_dst  )  )  return  -1;

	if  (  !m_var.ucbShowRules  )  return  -1;
	
	if  (  !pSubWall->usCnt  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "showRules: subWall.usCnt is 0"  )  );
		#endif
		return  0;
	}

	CClientDC	clientDC(  CWnd::FromHandle(  hWnd_dst  )  );
	TCHAR		tBuf[256];
	RECT		rc;
	
	//

	//
	for  (  pQNode  =  pSubWall->pRuleQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf;  pQNode  =  pQNode->pNext  )  {
		 VW_ruleU	*	pRule	=	(  VW_ruleU  *  )pQNode->qElemMemory.m_pBuf;
		 int				j;
		 for  (  j  =  0;  j  <  pSubWall->usCnt;  j  ++  )  {
			  if  (  pSubWall->mems[j].uiTranNo_spObj  ==  pRule->common.uiTranNo_spObj  )  break;			
		 }
		 if  (  j  ==  pSubWall->usCnt  )  {
			 #ifdef  __DEBUG__
					 traceLog(  _T(  "showRule: rule not matched with zone"  )  );
			 #endif
			 continue;
		 }
		 pZone  =  &pSubWall->mems[j];

		 SetRect(  &rc,  pZone->iX,  pZone->iY,  pZone->iX  +  pZone->iW,  pZone->iY  +  pZone->iH  );
		 ::MapWindowPoints(  old_M_GetDlgItem(  m_hWnd,  pSubWall->idc  ),  hWnd_dst,  (  LPPOINT  )&rc,  2  );
 
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,%d:"  ),  qyGetDesByType1(  CONST_vwRuleTypeTable,  pRule->common.uiType  ),  pRule->common.uiTranNo_spObj  );
		 switch  (  pRule->common.uiType  )  {
				 case  CONST_vwRuleType_dynBmp:
					 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u,%s,%d"  ),  tBuf,  pRule->dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  pRule->dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType  ),  pRule->dynBmp.ruleDynBmp.dynBmp.resObj.usIndex_obj  );
					   if  (  pRule->dynBmp.ruleDynBmp.ucbSaveVideo  )  {
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. save"  ),  tBuf  );		//  2014/08/03
					   }
					   break;
				 case  CONST_vwRuleType_conference_imGrp:
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u"  ),  tBuf,  pRule->conference_imGrp.idInfo.ui64Id  );
					   break;
				 case  CONST_vwRuleType_conference_imGrpMem:
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u"  ),  tBuf,  pRule->conference_imGrpMem.idInfo.ui64Id  );
					   break;
				 case  CONST_vwRuleType_bgMemVideo:  //  2017/09/21
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u"  ),  tBuf,  pRule->bgMemVideo.idInfo.ui64Id  );					 
					   break;
				 case  CONST_vwRuleType_talkers:					   
					   break;
				 case  CONST_vwRuleType_walls:  //  2016/06/01
					   break;
				 case  CONST_vwRuleType_messenger:
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u"  ),  tBuf,  pRule->messenger.idInfo.ui64Id  );
					   //  if  (  pRule->messenger.cmd.ucbViewScreen  )  
					   if  (  tmpF_bViewRemoteVideo(  &pRule->messenger.cmd,  CONST_objType_screen,  CONST_usIndex_screen0,  0  )  )  
					   {
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s s"  ),  tBuf  );
					   }
					   //  if  (  pRule->messenger.cmd.ucbViewWebcam0  )  
					   if  (  tmpF_bViewRemoteVideo(  &pRule->messenger.cmd,  CONST_objType_webcam,  CONST_usIndex_webcam0,  0  )  )  
					   {
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s w0"  ),  tBuf  );
					   }
					   //  if  (  pRule->messenger.cmd.ucbViewWebcam1  )  						   
					   if  (  tmpF_bViewRemoteVideo(  &pRule->messenger.cmd,  CONST_objType_webcam,  CONST_usIndex_webcam1,  0  )  )  					   
					   {
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s w1"  ),  tBuf  );
					   }
					   //  if  (  pRule->messenger.cmd.ucbViewWebcam2  )  						   
					   if  (  tmpF_bViewRemoteVideo(  &pRule->messenger.cmd,  CONST_objType_webcam,  CONST_usIndex_webcam2,  0  )  )  						   
					   {						
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s w2"  ),  tBuf  );
					   }
					   break;
				 default:
						 #ifdef  __DEBUG__
								 traceLogA(  "dlgDynBmps: unknown ruleType %d",  pRule->common.uiType  );
						 #endif
					     break;			
		 }		

#if  0
		 RECT  tmpRc  =  rc;
		 //  UINT uFormat  =  DT_CENTER  |  DT_SINGLELINE  |  DT_VCENTER;
		 //uFormat  =  DT_CENTER  |  DT_CALCRECT;
		 //uFormat  =  DT_WORDBREAK  |  DT_CALCRECT;
		 UINT uFormat  =  DT_CENTER  |  DT_WORDBREAK;
		 clientDC.DrawText(  tBuf,  lstrlen(  tBuf  ),  &tmpRc,  uFormat  |  DT_CALCRECT    );
		 int  iW_t  =  tmpRc.right  -  tmpRc.left;
		 int  iH_t  =  tmpRc.bottom  -  tmpRc.top;
		 int  iW  =  rc.right  -  rc.left;
		 int  iH  =  rc.bottom  -  rc.top;
		 int  iEdge_l  =  iW  >  iW_t  ?  (  iW  -  iW_t  )  /  2  :  0;
		 int  iEdge_t  =  iH  >  iH_t  ?  (  iH  -  iH_t  )  /  2  :  0;
		 tmpRc.left  =  rc.left  +  iEdge_l;
		 tmpRc.right  =  rc.right  -  iEdge_l;
		 tmpRc.top  =  rc.top  +  iEdge_t;
		 tmpRc.bottom  =  rc.bottom  -  iEdge_t;
		 //
		 clientDC.DrawText(  tBuf,  lstrlen(  tBuf  ),  &tmpRc,  uFormat    );
#endif


//
#define		CONST_fontColor_rule_fullScreen			RGB(  255,  255,  255  )
#define		CONST_fontColor_rule_normal				RGB(  0,  0,  0  )
//													RGB(  0,  64,  128  )  
#define		CONST_faceName_rule						"Arial"

		 //
		 COLORREF  color_pen  =  CONST_fontColor_rule_normal;
		 if  (  pBase->m_var.m_bFullScreen  )  color_pen  =  CONST_fontColor_rule_fullScreen;

		 //
		 myDrawTxt(  tBuf,  90,  _T(  CONST_faceName_rule  ),  color_pen,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  hWnd_dst,  clientDC.m_hDC  );  

		 

	}	

	iErr  =  0;
//  errLabel:
	return  iErr;
}







//  2012/04/02
 int  tmpHandler_getZoneParam_talkers(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 int						iErr			=	-1;
	 //  MIS_MSG_procVideo_qmc	*	pMsg			=	(  MIS_MSG_procVideo_qmc  *  )p0;
	 COMMON_PARAM			*	pCommonParam	=	(  COMMON_PARAM  *  )p1;
	 VW_ruleU				*	pRuleElem		=	(  VW_ruleU  *  )p2;
	 //
	 //  pCommonParam->p0;
	 int						iTaskId_videoConference	=	(  int  )pCommonParam->p1;
	 ZONE_PARAM				*	pZoneParam		=	(  ZONE_PARAM  *  )pCommonParam->p2;

	 BOOL						bMatched		=	FALSE;
	 int						nRulePriority	=	0;

	 switch  (  pRuleElem->common.uiType  )  {
			 case  CONST_vwRuleType_talkers:  {
				   bMatched  =  TRUE;
				   }
				   break;
			 default:
				     traceLogA(  "tmpHandler_getZoneParam: unknown ruleType %d",  pRuleElem->common.uiType  );
					 break;
	 }

	 if  (  bMatched  )  {
		 nRulePriority  =  (  int  )qyGetDesByType(  CONST_rulePriorityTable,  pRuleElem->common.uiType  );
		 if  (  nRulePriority  <  0  )  {
			 traceLogA(  "tmphandle_getZoneparam: rulePriorityTable error"  );
			 goto  errLabel;
		 }
		 if  (  nRulePriority  >  pZoneParam->nRulePriority  )  {
			 memset(  pZoneParam,  0,  sizeof(  ZONE_PARAM  )  );
			 //  pZoneParam->uiTranNo_zone  =  pRuleElem->dynBmp.uiTranNo_spObj;
			 pZoneParam->uiTranNo_zone  =  pRuleElem->common.uiTranNo_spObj;		//  2012/04/03
			 pZoneParam->nRulePriority  =  nRulePriority;
		 }
	 }
	 iErr  =  0;
errLabel:

	 return  iErr;
}


//  2012/04/03
int  CDlgDynBmps::findZoneParam(  BOOL	bTalkers,  ZONE_PARAM  *  pParam  )
{
	int			iErr	=	-1;
	int			i;
	int			tmpiRet;
	ZONE_PARAM	zoneParam;
	

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  goto  errLabel;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	
	//
	COMMON_PARAM	commonParam;
	memset(  &zoneParam,  0,  sizeof(  zoneParam  )  );
	MACRO_makeCommonParam3(  0,  (  void  *  )0,  &zoneParam,  commonParam  );
	for  (  i  =  0;  i  <  m_var.pWall->m_var.usCnt;  i  ++  )  {
		 tmpiRet  =  qTraverse(  m_var.pWall->getSubWall(  i  )->pRuleQ,  tmpHandler_getZoneParam_talkers,  0,  &commonParam  );
		 if  (  tmpiRet  )  goto  errLabel;
		 if  (  zoneParam.uiTranNo_zone  )  {
			 zoneParam.index_subWall  =  i;
			 break;
		 }
	}
	if  (  i  ==  m_var.pWall->m_var.usCnt  )  goto  errLabel;

	//
	SUB_V_WALL	*	pSubWall	=	m_var.pWall->getSubWall(  zoneParam.index_subWall  );
	if  (  !pSubWall  )  goto  errLabel;
	for  (  i  =  0;  i  <  pSubWall->usCnt;  i  ++  )  {
		 if  (  pSubWall->mems[i].uiTranNo_spObj  ==  zoneParam.uiTranNo_zone  )  break;
	}
	if  (  i  ==  pSubWall->usCnt  )  goto  errLabel;
	zoneParam.index_zone  =  i;
	
	iErr  =  0;
errLabel:

	if  (  !iErr  )  {
		if  (  pParam  )  {
			memcpy(  pParam,  &zoneParam,  sizeof(  ZONE_PARAM  )  );
		}

	    #ifdef  __DEBUG__
		        //  traceLogA(  "getZoneParams: ( %I64u, %d, %d ) -> index_subWall %d, uiTranNo_spObj %d",  pMsg->idInfo_sender.ui64Id,  pMsg->uiTranNo_openAvDev,  pMsg->usIndex,  zoneParam.index_subWall,  zoneParam.uiTranNo_zone  );
		#endif
	}
	if  (  iErr  )  {
		#ifdef  __DEBUG__
			   //  traceLogA(  "getZoneParams failed: ( %I64u, %d, %d )",  pMsg->idInfo_sender.ui64Id,  pMsg->uiTranNo_openAvDev,  pMsg->usIndex  );
		#endif
	}

	return  iErr;
}


int  CDlgDynBmps::getZoneInfo(  POINT  point_dlg,  ZONE_PARAM  *  pParam,  VW_ruleU  *  pRuleParam  )
{
	int				iErr	=	-1;

	CDlgDynBmps  *  pDlg  =  this;

	int  iWndContentType  =  pDlg->getWndContentType(  );
	int					index_subWall		=		-1;		
	unsigned int		uiTranNo_spObj		=		0;
	int					index_zone			=		-1;
	VW_ruleU			rule;
	memset(  &rule,  0,  sizeof(  rule  )  );

		
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );	
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;



	//
	index_subWall  =  m_var.pWall->m_var.curSpIndex;
	SUB_V_WALL	*	pSubWall	=	m_var.pWall->getSubWall(  index_subWall  );
	if  (  !pSubWall  )  goto  errLabel;

	POINT	point;  point  =  point_dlg;
	::MapWindowPoints(  m_hWnd,  pSubWall->hWnd_subWall,  &point,  1  );

	if  (  iWndContentType  ==  CONST_qyWndContentType_vWall  )  {
		SP_STRUCT	*	pSp		=	(  SP_STRUCT  *  )pSubWall->pSp;
		Q_NODE		*	pQNode;
		SP_OBJ		*	pSpObj	=	NULL;
		RECT			rc;
		
		if  (  !pSp  )  goto  errLabel;

		//  nPos  =  CONST_resId_popup_vWall;	

		for  (  pQNode  =  pSp->pSpObjQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf;  pQNode  =  pQNode->pNext  )  {
			 pSpObj  =  (  SP_OBJ  *  )pQNode->qElemMemory.m_pBuf;
			 if  (  pSpObj->type  !=  SP_RECTANGLE_TYPE  )  continue;
			 if  (  pSpObj->subType  !=  SP_GENERIC_RECTANGLE_TYPE  )  continue;
			 SP_RECTANGLE	*	pRectangle  =  (  SP_RECTANGLE  *  )pSpObj;
			 SP_POINT		*	pPoint0		=	(  SP_POINT  *  )pRectangle->pQNode_points[0]->qElemMemory.m_pBuf;
			 SP_POINT		*	pPoint2		=	(  SP_POINT  *  )pRectangle->pQNode_points[2]->qElemMemory.m_pBuf;

			 memset(  &rc,  0,  sizeof(  rc  )  );
			 rc.left  =  min(  pPoint0->point.rect.x,  pPoint2->point.rect.x  );
			 rc.top  =  min(  pPoint0->point.rect.y,  pPoint2->point.rect.y  );
			 rc.right  =  max(  pPoint0->point.rect.x,  pPoint2->point.rect.x  );
			 rc.bottom  =  max(  pPoint0->point.rect.y,  pPoint2->point.rect.y  );

			 if  (  point.x  >=  rc.left  &&  point.x  <=  rc.right
				 &&  point.y  >=  rc.top  &&  point.y  <=  rc.bottom  )  
			 {
				 uiTranNo_spObj  =  pSpObj->uiTranNo;
				 //
				 //  nPos  =  CONST_resId_popup_zone;
				 //
				 break;
			 }
			 
		}

		//
		unsigned  uiTranNo_zone  =  uiTranNo_spObj;
		int  i;
		for  (  i  =  0;  i  <  pSubWall->usCnt;  i  ++  )  {
			 if  (  pSubWall->mems[i].uiTranNo_spObj  ==  uiTranNo_zone  )  break;
		}
		if  (  i  ==  pSubWall->usCnt  )  goto  errLabel;
		index_zone  =  i;

		//
		for  (  pQNode  =  pSubWall->pRuleQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf;  pQNode  =  pQNode->pNext  )  {
			 VW_ruleU	*	pRule	=	(  VW_ruleU  *  )pQNode->qElemMemory.m_pBuf;

			 if  (  uiTranNo_spObj  ==  pRule->common.uiTranNo_spObj  )  {
				 memcpy(  &rule,  pRule,  sizeof(  rule  )  );
				 break;			
			 }	
		}	


	}

	if  (  index_zone  <  0  )  goto  errLabel;

	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
		if  (  pParam  )  {
			pParam->index_subWall  =  m_var.pWall->m_var.curSpIndex;
			pParam->uiTranNo_zone  =  uiTranNo_spObj;
			pParam->index_zone  =  index_zone;
		}
		if  (  pRuleParam  )  {
			memcpy(  pRuleParam,  &rule,  sizeof(  VW_ruleU  )  );
		}
	}
	return  iErr;
}



   
BEGIN_MESSAGE_MAP(CDlgDynBmps, CDlgDesktopsMon)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_viewToolbox, &CDlgDynBmps::Onviewtoolbox)
	ON_UPDATE_COMMAND_UI(ID_viewToolbox, &CDlgDynBmps::OnUpdateviewtoolbox)
	ON_COMMAND(ID_stopEditing, &CDlgDynBmps::Onstopediting)
	ON_UPDATE_COMMAND_UI(ID_stopEditing, &CDlgDynBmps::OnUpdatestopediting)
	ON_COMMAND(ID_startToEdit, &CDlgDynBmps::Onstarttoedit)
	ON_UPDATE_COMMAND_UI(ID_startToEdit, &CDlgDynBmps::OnUpdatestarttoedit)
	ON_COMMAND(ID_stopShowingRules, &CDlgDynBmps::Onstopshowingrules)
	ON_UPDATE_COMMAND_UI(ID_stopShowingRules, &CDlgDynBmps::OnUpdatestopshowingrules)
	ON_COMMAND(ID_startToShowRules, &CDlgDynBmps::Onstarttoshowrules)
	ON_UPDATE_COMMAND_UI(ID_startToShowRules, &CDlgDynBmps::OnUpdatestarttoshowrules)
	ON_WM_DRAWITEM()
	ON_COMMAND(ID_open, &CDlgDynBmps::Onopen)
	ON_UPDATE_COMMAND_UI(ID_open, &CDlgDynBmps::OnUpdateopen)
	ON_COMMAND(ID_save, &CDlgDynBmps::Onsave)
	ON_UPDATE_COMMAND_UI(ID_save, &CDlgDynBmps::OnUpdatesave)
	ON_WM_MOVING()
	ON_WM_MOVE()
	ON_COMMAND_RANGE(  ID_MENU_isCmd_user,  ID_MENU_isCmd_max,  OnIsCmd  )
	ON_UPDATE_COMMAND_UI_RANGE(  ID_MENU_isCmd_user,  ID_MENU_isCmd_max,  OnUpdateIsCmd  )

	ON_MESSAGE(DROPM_DRAGOVER,OnDragOver)
	ON_MESSAGE(DROPM_DROPEX,OnDropEx)
	ON_MESSAGE(DROPM_DROP,OnDrop)

	ON_WM_WINDOWPOSCHANGED()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


 int  CDlgDynBmps::sizeZone(  SUB_V_WALL  *  pSubWall,  myZONE  *  pZone  )
{
	CAP_IMAGES	*	pImages	=	&pZone->images;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;
	CDlgDesktopsMon  *  pBase  =  this;


	if  (  !pSubWall->iW_org  ||  !pSubWall->iH_org  )  return  -1;

	int					iW_i,  iH_i;
	int					iX_src_i,  iY_src_i;
	int					iX_image,  iY_image;
	unsigned  int		iW_image,  iH_image;
	myGetImageInfo_2d(  FALSE,  m_var.ucbAutoClip,  pSubWall->iW_org,  pSubWall->iH_org,  0,  0,  pSubWall->iW,  pSubWall->iH,  (  unsigned  int  *  )&iW_i,  (  unsigned  int  *  )&iH_i,  &iX_src_i,  &iY_src_i,  &iX_image,  &iY_image,  &iW_image,  &iH_image  );

	pZone->iX  =  pZone->iX_org  *  iW_image  /  pSubWall->iW_org  +  iX_image  -  pSubWall->iX;
	pZone->iY  =  pZone->iY_org  *  iH_image  /  pSubWall->iH_org  +  iY_image  -  pSubWall->iY;
	pZone->iW  =  pZone->iW_org  *  iW_image  /  pSubWall->iW_org;
	pZone->iH  =  pZone->iH_org  *  iH_image  /  pSubWall->iH_org;
	
	//
	if  (  m_var.ucbLocalAv  )  myGetImageInfo_2d(  TRUE,  m_var.ucbAutoClip,  pImages->mems[0].iW_org,  pImages->mems[0].iH_org,  pZone->iX_org,  pZone->iY_org,  pZone->iW_org,  pZone->iH_org,  (  unsigned  int  *  )&pImages->mems[0].iW_i,  (  unsigned  int  *  )&pImages->mems[0].iH_i,  &pImages->mems[0].iX_src_i,  &pImages->mems[0].iY_src_i,  &pImages->mems[0].iX_dst,  &pImages->mems[0].iY_dst,  &pImages->mems[0].iW_dst,  &pImages->mems[0].iH_dst  );
	else  getCapImages(  m_var.ucbAutoClip,  pZone->iX,  pZone->iY,  pZone->iW,  pZone->iH,  NULL,  pImages  );

	//
	int  iEdge_l  =  2;
	int  iH_font  =  15;
	::SetWindowPos(  ::GetDlgItem(  m_hWnd,  pZone->idcStatic_desc  ),  HWND_TOP,  pZone->iX  +  iEdge_l ,  pZone->iY  +  pZone->iH  -  iH_font,  pZone->iW  -  2  *  iEdge_l,  iH_font,  SWP_SHOWWINDOW  );
	::InvalidateRect(  ::GetDlgItem(  m_hWnd,  pZone->idcStatic_desc  ),  NULL,  FALSE  );
		::UpdateWindow(  ::GetDlgItem(  m_hWnd,  pZone->idcStatic_desc  )  );
	//SetDlgItemText(  pZone->idcStatic_desc,  _T(  " 河北武警 二支队"  )  );



	//
#ifdef  __DEBUG__
		traceLog(  _T(  "sizeZone: subWall.iW %d, iH %d, iW_org %d, iH_org %d. zone.iW %d, iH %d, iW_org %d, iH_org %d"  ),  pSubWall->iW,  pSubWall->iH,  pSubWall->iW_org,  pSubWall->iH_org,  pZone->iW,  pZone->iH,  pZone->iW_org,  pZone->iH_org  );
#endif

	return  0;
}

  int  CDlgDynBmps::sizeAllControls(  RECT  rcParam  )
{
	int					iErr	=	-1;
	int					i,  j;
	CDlgDesktopsMon	*	pBase	=	this;

	//
	CDlgDesktopsMon::sizeAllControls(  rcParam  );


	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	//
	if  (  !m_var.pWall  )  return  -1;
	
	for  (  i  =  0;  i  <  m_var.pWall->m_var.usCnt;  i  ++  )  {
		 SUB_V_WALL	*	pSubWall  =  m_var.pWall->getSubWall(  i  );
		 CWnd		*	pCtrl		=	pSubWall->idc  ?  GetDlgItem(  pSubWall->idc  )  :  this;
		 if  (  !pCtrl  )  goto  errLabel;

		 RECT	rc;
		 pCtrl->GetClientRect(  &rc  );
		 if  (  !pSubWall->hBmp_background  )  {
			 pSubWall->iX  =  rc.left;
			 pSubWall->iY  =  rc.top;
			 pSubWall->iW  =  rc.right  -  rc.left;
			 pSubWall->iH  =  rc.bottom  -  rc.top;

			 if  (  pBase->m_var.bScrollBarEnabled  )  {
				 pSubWall->iX_org  =  pSubWall->iX;
				 pSubWall->iY_org  =  pSubWall->iY;
				 pSubWall->iW_org  =  pSubWall->iW;
				 pSubWall->iH_org  =  pSubWall->iH;
			 }
			}
		 else  {
			   if  (  pBase->m_var.bScrollBarEnabled  )  {
				   pSubWall->iX  =  pSubWall->iX_org;
				   pSubWall->iY  =  pSubWall->iY_org;
				   pSubWall->iW  =  pSubWall->iW_org;
				   pSubWall->iH  =  pSubWall->iH_org;
			   }
			   else  {
				     pSubWall->iX  =  rc.left;	
					 pSubWall->iY  =  rc.top;
					 pSubWall->iW  =  rc.right  -  rc.left;
					 pSubWall->iH  =  rc.bottom  -  rc.top;
			   }
		 }
		 if  (  !pSubWall->iW_org  ||  !pSubWall->iH_org  )  {	//  2009/10/14
			 pSubWall->iX_org  =  pSubWall->iX;
			 pSubWall->iY_org  =  pSubWall->iY;
			 pSubWall->iW_org  =  pSubWall->iW;
			 pSubWall->iH_org  =  pSubWall->iH;
		 }


		 //  pCtrl->Invalidate(  TRUE  );
		 //  pCtrl->UpdateWindow(  );
		 sizeSubWallBg(  i  );

		 //
		 if  (  m_var.ucbLocalAv  )  {
			 pSubWall->mems[0].iX_org  =  0;
			 pSubWall->mems[0].iY_org  =  0;
			 pSubWall->mems[0].iW_org  =  pBase->m_var.mems_org[0].iW;
			 pSubWall->mems[0].iH_org  =  pBase->m_var.mems_org[0].iH;
		 }			

		 for  (  j  =  0;  j  <  pSubWall->usCnt;  j  ++  )  {
			  sizeZone(  pSubWall,  &pSubWall->mems[j]  );
		 }
	}	

	iErr  =  0;
errLabel:
	return  iErr;
}







 


#define		CONST_vWall_bg_normal			RGB(202,225,242)	//RGB(  0,  255,  255  )
#define		CONST_vWall_bg_fullScreen		RGB(  0,  0,  0  )









 int  CDlgDynBmps::sizeSubWallBg(  int  spIndex  )
{
	 
	int					iErr				=	-1;
		DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	SUB_V_WALL		*	pSubWall			=	(  SUB_V_WALL  *  )m_var.pWall->getSubWall(  spIndex  );
	if  (  !pSubWall  )  return  -1;
	HBITMAP				hBmp_background		=	NULL;
	HBITMAP				hBmp_foreground		=	NULL;
	HBITMAP				oldhBmp_background	=	NULL;
	HBITMAP				oldhBmp_foreground	=	NULL;
	CDlgDesktopsMon	*	pBase				=	this;
	COLORREF			color_bg			=	pBase->m_var.m_bFullScreen  ?  CONST_vWall_bg_fullScreen  :  CONST_vWall_bg_normal;

#ifdef  __DEBUG__
		traceLog(  _T(  "dlgDynBmps: sizeSubWallBg enters"  )  );
#endif

	SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )pSubWall->pSp;
	if  (  pSp  )  {

		//  if ( !pSp->spWidth  ||  !pSp->spHeight ) 
		{
			RECT	rc;
			if  (  !getPicRect(  pSubWall->idc,  &rc  )  )  {
				pSp->spWidth  =  rc.right  -  rc.left;
				pSp->spHeight  =  rc.bottom  -  rc.top;
			}
		}


		int		iX_bg,  iY_bg;
		int		iW_bg,  iH_bg;

		iX_bg  =  pSubWall->iX;
		iY_bg  =  pSubWall->iY;
		iW_bg  =  pSubWall->iW;
		iH_bg  =  pSubWall->iH;

		assert(  iW_bg  ==  pSubWall->iW  );
		assert(  iH_bg  ==  pSubWall->iH  );


		int					iW_i,  iH_i;
		int					iX_src_i,  iY_src_i;
		int					iX_image,  iY_image;
		unsigned  int		iW_image,  iH_image;

		if  (  !pBase->m_var.bScrollBarEnabled  )  {
			myGetImageInfo_2d(  FALSE,  m_var.ucbAutoClip,  pSp->spWidth,  pSp->spHeight,  iX_bg,  iY_bg,  pSubWall->iW,  pSubWall->iH,  (  unsigned  int  *  )&iW_i,  (  unsigned  int  *  )&iH_i,  &iX_src_i,  &iY_src_i,  &iX_image,  &iY_image,  &iW_image,  &iH_image  );		
			}
		else  {		
			  iX_image  =  0;  iY_image  =  0;  iW_image  =  pSp->spWidth;  iH_image  =  pSp->spHeight;
		}	
		//
		if  (  pSubWall->iX_image  !=  iX_image  )  pSubWall->iX_image  =  iX_image;
		if  (  pSubWall->iY_image  !=  iY_image  )  pSubWall->iY_image  =  iY_image;
		if  (  pSubWall->iW_image  !=  iW_image  )  pSubWall->iW_image  =  iW_image;
		if  (  pSubWall->iH_image  !=  iH_image  )  pSubWall->iH_image  =  iH_image;

	}


	iErr  =  0;
errLabel:


#ifdef  __DEBUG__
		traceLog(  _T(  "dlgDynBmps: sizeSubWallBg leaves"  )  );
#endif


	return  iErr;


}



 //  2013/03/02
 int  CDlgDynBmps::drawSubWall(  int  spIndex,  HWND  hWnd_dst,  HDC  hDc_dst  )
{
	int					iErr				=	-1;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	SUB_V_WALL		*	pSubWall			=	(  SUB_V_WALL  *  )m_var.pWall->getSubWall(  spIndex  );
	if  (  !pSubWall  )  return  -1;
	DISPLAY_DEV			tmpDisplayDev;
	HDC					hDc_foreground		=	NULL;
	HDC					hDc_background		=	NULL;
	HBITMAP				hBmp_background		=	NULL;
	HBITMAP				hBmp_foreground		=	NULL;
	HBITMAP				oldhBmp_background	=	NULL;
	HBITMAP				oldhBmp_foreground	=	NULL;
	CDlgDesktopsMon	*	pBase				=	this;
	COLORREF			color_bg			=	pBase->m_var.m_bFullScreen  ?  CONST_vWall_bg_fullScreen  :  CONST_vWall_bg_normal;
	
	//
	RECT				rc;

	#ifdef  __DEBUG__
			//  traceLog(  _T(  "dlgDynBmps: drawSubWall enters"  )  );
	#endif

	if  (  !IsWindow(  hWnd_dst  )  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "dlgDynBmps: drawSubWall failed, hWnd_dst err"  )  );
		#endif
		return  -1;
	}


	SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )pSubWall->pSp;
	if  (  pSp  )  {

		if ( !pSp->spWidth  ||  !pSp->spHeight ) {
			if  (  !getPicRect(  pSubWall->idc,  &rc  )  )  {
				pSp->spWidth  =  rc.right  -  rc.left;
				pSp->spHeight  =  rc.bottom  -  rc.top;
			}
		}

		//  tmpDisplayDev.hDc = pDC->m_hDC;
		//  spDisplay( &tmpDisplayDev, &gSp ); 

		if  (  !(  hDc_foreground  =  CreateCompatibleDC( hDc_dst )  )  )  goto  errLabel;
		if  (  !(  hDc_background  =  CreateCompatibleDC(  hDc_dst  )  )  )  goto  errLabel;

		memset(  &tmpDisplayDev,  0,  sizeof(  tmpDisplayDev  )  );
		tmpDisplayDev.pSp  =  pSp;
		tmpDisplayDev.hDc  =  hDc_foreground;
		tmpDisplayDev.ucbFullScreen  =  pBase->m_var.m_bFullScreen;		//  2018/07/05
		
		//
		int		iX_bg,  iY_bg;
		int		iW_bg,  iH_bg;

		iX_bg  =  pSubWall->iX;
		iY_bg  =  pSubWall->iY;
		iW_bg  =  pSubWall->iW;
		iH_bg  =  pSubWall->iH;

		assert(  iW_bg  ==  pSubWall->iW  );
		assert(  iH_bg  ==  pSubWall->iH  );

		if  (  !(  hBmp_background = CreateCompatibleBitmap( hDc_dst, iW_bg, iH_bg )  )  )  goto  errLabel;		
		if  (  !(  hBmp_foreground = CreateCompatibleBitmap(  hDc_dst,  pSp->spWidth,  pSp->spHeight  )  )  )  goto  errLabel;

		oldhBmp_foreground = ( HBITMAP )SelectObject( tmpDisplayDev.hDc, hBmp_foreground );
		if  (  !isHandleValid(  oldhBmp_foreground  )  )  goto  errLabel;
		if  (  pSubWall->hBmp_background  )  {
			oldhBmp_background  =  (  HBITMAP  )SelectObject(  hDc_background,  pSubWall->hBmp_background  );
			if  (  !isHandleValid(  oldhBmp_background  )  )  goto  errLabel;
			if  (  !BitBlt( tmpDisplayDev.hDc, 0, 0, pSp->spWidth, pSp->spHeight, hDc_background, 0, 0, SRCCOPY )  )  goto  errLabel;
			SelectObject( hDc_background, oldhBmp_background );		oldhBmp_background  =  NULL;	// release pSubWall->hBmp_background
			  }
		else  {
			  brushDc(  color_bg,  tmpDisplayDev.hDc,  0,  0,  pSp->spWidth,  pSp->spHeight  );
		}

		spDisplay( &tmpDisplayDev, pSp );

		oldhBmp_background  =  (  HBITMAP  )SelectObject(  hDc_background,  hBmp_background  );
		if  (  !isHandleValid(  oldhBmp_background  )  )  goto  errLabel;
		brushDc(  color_bg,  hDc_background,  iX_bg,  iY_bg,  iW_bg,  iH_bg  );

		unsigned  int		iW_i,  iH_i;
		int					iX_src_i,  iY_src_i;
		int					iX_image,  iY_image;
		unsigned  int		iW_image,  iH_image;

		if  (  !pBase->m_var.bScrollBarEnabled  )  {
			myGetImageInfo_2d(  FALSE,  m_var.ucbAutoClip,  pSp->spWidth,  pSp->spHeight,  iX_bg,  iY_bg,  pSubWall->iW,  pSubWall->iH,  &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,  &iX_image,  &iY_image,  &iW_image,  &iH_image  );
		
			::StretchBlt(  hDc_background,  iX_image,  iY_image,  iW_image,  iH_image,  tmpDisplayDev.hDc,  0,  0,  pSubWall->iW_org,  pSubWall->iH_org,  SRCCOPY  );
			}
		else  {		
			  iX_image  =  0;  iY_image  =  0;  iW_image  =  pSp->spWidth;  iH_image  =  pSp->spHeight;
			  BitBlt( hDc_background, 0, 0, pSp->spWidth, pSp->spHeight, tmpDisplayDev.hDc, 0, 0, SRCCOPY );
		}	
		//
		if  (  pSubWall->iX_image  !=  iX_image  )  pSubWall->iX_image  =  iX_image;
		if  (  pSubWall->iY_image  !=  iY_image  )  pSubWall->iY_image  =  iY_image;
		if  (  pSubWall->iW_image  !=  iW_image  )  pSubWall->iW_image  =  iW_image;
		if  (  pSubWall->iH_image  !=  iH_image  )  pSubWall->iH_image  =  iH_image;

		//
		//  BitBlt( hDc_dst, iX_bg, iY_bg, iW_bg, iH_bg, hDc_background, 0, 0, SRCCOPY );
		SetRect(  &rc,  iX_bg,  iY_bg,  iX_bg  +  iW_bg,  iY_bg  +  iH_bg  );
		::MapWindowPoints(  pSubWall->hWnd_subWall,  hWnd_dst,  (  LPPOINT  )&rc,  2  );
		BitBlt( hDc_dst, rc.left, rc.top, rc.right  -  rc.left, rc.bottom  -  rc.top, hDc_background, 0, 0, SRCCOPY );
	}

	if  (  m_var.ucbShowRules  )  this->showRules(  m_var.pWall->m_var.curSpIndex  );

	iErr  =  0;
errLabel:


	if  (  isHandleValid(  oldhBmp_foreground  )  )  SelectObject( hDc_foreground, oldhBmp_foreground );	
	if  (  hBmp_foreground  )  DeleteObject( hBmp_foreground );	
	if  (  isHandleValid(  oldhBmp_background  )  )  SelectObject( hDc_background, oldhBmp_background );		// release pSubWall->hBmp_background
	if  (  hBmp_background  ) DeleteObject(  hBmp_background  );
	if  (  hDc_background  )  DeleteDC(  hDc_background  );
	if  (  hDc_foreground  )  DeleteDC(  hDc_foreground  );

#ifdef  __DEBUG__
		traceLog(  _T(  "dlgDynBmps: drawSubWall leaves"  )  );
#endif


	return  iErr;

}

//  fileName: 任意-lat_org-lng_org-zoom.bmp
int  parseBgFileName(  CDlgDynBmps  *  pDlg,  LPCTSTR  fileName1  )
{
	int	iErr	=	-1;
	int	iWndContentType  =  pDlg->getWndContentType(  );
	int  iSubType  =  pDlg->getWndContentSubtype(  );

	if  (  !pDlg  )  return  -1;
	if  (  iWndContentType  !=  CONST_qyWndContentType_vWall  )  return  -1;


	DLG_dynBmps_var  *  pm_var  =  pDlg->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;


	if  (  !fileName1  )  {
		memset(  &m_var.vWall.coord,  0,  sizeof(  m_var.vWall.coord  )  );
		return  0;
	}


	TCHAR		tmpFileName[MAX_PATH  +  1];
	safeTcsnCpy(  fileName1,  tmpFileName,  mycountof(  tmpFileName  )  );

	TCHAR	*	pT;
	TCHAR	*	pT1;
	TCHAR		tBuf[128];

	switch  (  iSubType  )  {
			case  CONST_vwSubtype_gps:
			case  CONST_vwSubtype_globalGps:
				  memset(  &m_var.vWall.coord,  0,  sizeof(  m_var.vWall.coord  )  );
				  double  lat;
				  double  lng;
				  int  zoom;

				  //
				  pT  =  (  TCHAR  *  )_tcsrchr(  tmpFileName,  _T(  '.'  )  );
				  if  (  !pT  )  goto  errLabel;
				  *pT  =  0;
				  pT1  =  _tcsrchr(  tmpFileName,  _T(  '_'  )  );
				  if  (  !pT1  )  goto  errLabel;
				  safeTcsnCpy(  pT1  +  1,  tBuf,  min(  pT1  +  1  -  pT,  mycountof(  tBuf  )  )  );
				  zoom  =  _ttol(  tBuf  );
				  //
				  pT  =  pT1;
				  *pT  =  0;
				  pT1  =  _tcsrchr(  tmpFileName,  _T(  '_'  )  );
				  if  (  !pT1  )  goto  errLabel;
				  safeTcsnCpy(  pT1  +  1,  tBuf,  min(  pT1  +  1  -  pT,  mycountof(  tBuf  )  )  );
				  lng  =  _tstof(  tBuf  );
				  //
				  pT  =  pT1;
				  *pT  =  0;
				  pT1  =  _tcsrchr(  tmpFileName,  _T(  '_'  )  );
				  if  (  !pT1  )  goto  errLabel;
				  safeTcsnCpy(  pT1  +  1,  tBuf,  min(  pT1  +  1  -  pT,  mycountof(  tBuf  )  )  );
				  lat  =  _tstof(  tBuf  );
				  //

				  myGPS_POSITION	gpsPos;
				  memset(  &gpsPos,  0,  sizeof(  gpsPos  )  );
				  gpsPos.dblLatitude  =  lat;
				  gpsPos.dblLongitude  =  lng;
				  gps2Pnt(  0,  &gpsPos,  zoom,  &m_var.vWall.coord.origin  );
				  m_var.vWall.coord.zoom  =  zoom;

				  break;
			default:
					break;
	}


	iErr  =  0;
errLabel:
	return  iErr;
}




//
int  CDlgDynBmps::storeSpRules(  )
{
	int			iErr  =  -1;

	//
	DLG_dynBmps_var  &  m_var =  *get_pm_var(  );
	
	//
	SUB_V_WALL	*	pSubWall	=		m_var.pWall->getCurSubWall(  );
	if  (  !pSubWall  )  return  -1;

	//		
	int  i;
	
	for  (  i  =  0;  i  <  pSubWall->usCnt;  i  ++  )  {
	
		 //if  (  pSubWall->mems[i].uiTranNo_spObj  ==  uiTranNo_zone  )  break;
		 myZONE  *  pZone  =  &pSubWall->mems[i];	 
		 //
		 if  (  this->csVector_rules.size(  )  >  i  )  {
			 this->csVector_rules[i]  =  pZone->rule;
		 }
		 else  {
			   this->csVector_rules.push_back(  pZone->rule  );
		 }
		 //
		
	}

	//
#ifdef  __DEBUG__
	int  kk  =  0;
	for  (  vector<VW_ruleU>::const_iterator it =csVector_rules.begin(); it < csVector_rules.end(); ++ it  )  {
	  
		 VW_ruleU  tmpRule  =  *it;
		 //
		 TCHAR  tBuf[128];
		 //
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "rule[%d]: type %d"  ),  kk,  tmpRule.common.uiType  );
		 if  (  tmpRule.common.uiType  ==  CONST_vwRuleType_dynBmp  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %I64u, obj %d"  ),  tBuf,  tmpRule.dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id,  tmpRule.dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType  );
		 }
		 traceLog(  tBuf  );
		 //
		 kk  ++  ;
		
	  }
#endif




	iErr  =  0;
errLabel:
	return  iErr;
}


int  CDlgDynBmps::restoreSpRules(  )
{
	int			iErr  =  -1;
	//
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli();
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	//
	DLG_dynBmps_var  &  m_var =  *get_pm_var(  );
	
	//
	SUB_V_WALL	*	pSubWall	=		m_var.pWall->getCurSubWall(  );
	if  (  !pSubWall  )  return  -1;

	//		
	int  i;
	
	if  (  !isQEmpty(  pSubWall->pRuleQ  )  )  {
	
		//  如果墙中存有规则，则以墙中规则优先
		iErr  =  0;  goto  errLabel;
	}

	//
	if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )  {
		if  (  !csVector_rules.size(  )  )  {
			VW_ruleU  tmpRule  =  {0};
			csVector_rules.push_back(  tmpRule  );
		}
	}

	//
	int  kk  =  0;
	for  (  vector<VW_ruleU>::const_iterator it =csVector_rules.begin(); it < csVector_rules.end(); ++ it,  kk  ++  )  {
	  
		 VW_ruleU  tmpRule  =  *it;
		 //
		 TCHAR  tBuf[128];
		 //
		 if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )  {  //  2018/11/12
			 //if  (  pMisCnt->idInfo.ui64Id  !=  
			 QY_MESSENGER_ID  idInfo_superAdmin  =  {0};
			 int  getIdInfo_superAdmin(  QY_MESSENGER_ID  *  pIdInfo  );

			 getIdInfo_superAdmin(  &idInfo_superAdmin  );
			 //
			 if  (  idInfo_superAdmin.ui64Id  )  {
				 if  (  pMisCnt->idInfo.ui64Id  !=  idInfo_superAdmin.ui64Id  )  {
					 tmpRule.common.uiType  =  CONST_vwRuleType_dynBmp;			 
					 tmpRule.dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id  =  idInfo_superAdmin.ui64Id;
					 tmpRule.dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType  =  CONST_objType_webcam;
				 }
			 }
		 }
		 //
#if 0  
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "rule[%d]: type %d"  ),  kk,  tmpRule.common.uiType  );
		 if  (  tmpRule.common.uiType  ==  CONST_vwRuleType_dynBmp  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %I64u, obj %d"  ),  tBuf,  tmpRule.dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id,  tmpRule.dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType  );
		 }
		 traceLog(  tBuf  );
#endif
		 //
		 if  (  !tmpRule.common.uiType  )  continue;

		 //
		SP_STRUCT	*	pSp		=	(  SP_STRUCT  *  )m_var.pWall->getCurSp(  );
		Q_NODE		*	pQNode;
		SP_OBJ		*	pSpObj	=	NULL;
		RECT			rc;
		
		if  (  !pSp  )  goto  errLabel;

		int  ii  =  0;
		for  (  pQNode  =  pSp->pSpObjQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf;  pQNode  =  pQNode->pNext  )  {
			 pSpObj  =  (  SP_OBJ  *  )pQNode->qElemMemory.m_pBuf;
			 if  (  pSpObj->type  !=  SP_RECTANGLE_TYPE  )  continue;
			 if  (  pSpObj->subType  !=  SP_GENERIC_RECTANGLE_TYPE  )  continue;
			 SP_RECTANGLE	*	pRectangle  =  (  SP_RECTANGLE  *  )pSpObj;

			 //
			 ii  ++  ;
			 //
			 if  (  kk  +  1  >  ii  )  continue;
		
			 //
			 unsigned  int  tn_spObj  =  pSpObj->uiTranNo;
			 //
			 tmpRule.common.uiTranNo_spObj  =  tn_spObj;
			 //
			 if  (  qPostMsg(  &tmpRule,  sizeof(  tmpRule  ),  pSubWall->pRuleQ  )  )  goto  errLabel;
			 //
			 break;
		}
		
	  
	}




	iErr  =  0;
errLabel:
	return  iErr;
}



//
 int  CDlgDynBmps::openFile(  LPCTSTR  fileName  )
{
	int				iErr		=	-1;
	// TODO: Add your command handler code here
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	QY_IMEXPORTINFO	importInfo;
	memset(  &importInfo, 0,  sizeof(  importInfo  )  );
	CString  csPath;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;


	if  (  !fileName  )  return  -1;





	csPath  =  fileName;
	if  (  csPath.GetLength(  )  >= mycountof(  importInfo.fileName  )  )  return  -1;
	lstrcpyn(  (LPWSTR)&importInfo.fileName,  csPath.GetBuffer(  0  ),  mycountof(  importInfo.fileName  )  );

/*
#ifdef  __DEBUG__
	_sntprintf(  importInfo.fileName,  mycountof(  importInfo.fileName  ),  _T(  "c:\\tttbbb\\kk.qvw"  )  );
#endif
*/
	CWaitCursor  cursor;

	//
	storeSpRules(  );

	//
	bQisImportVWall(  &importInfo,  m_var.pWall  );

	//  2018/09/08
	restoreSpRules(  );

	//
	lstrcpyn(  m_var.title,  m_var.pWall->m_var.title,  mycountof(  m_var.title  )  );
	SetWindowText(  m_var.title  );

	TCHAR		fileName_background[MAX_PATH]	=	_T(  ""  );
	TCHAR	*	pT;
	lstrcpyn(  fileName_background,  m_var.pWall->getCurSubWall(  )->fileName_background,  mycountof(  fileName_background  )  );
	if  (  !_tcschr(  fileName_background,  _T(  '\\'  )  )  )  {
		lstrcpyn(  fileName_background,  fileName,  mycountof(  fileName_background  )  );
		pT  =  _tcsrchr(  fileName_background,  _T(  '\\'  )  );
		if  (  !pT  )  fileName_background[0]  =  0;
		else  {
			  pT  ++  ;  *pT  =  0;
			  _sntprintf(  fileName_background,  mycountof(  fileName_background  ),  _T(  "%s%s"  ),  fileName_background,  m_var.pWall->getCurSubWall(  )->fileName_background  );
		}
	}
	m_var.pWall->setBitmap(  fileName_background,  m_var.pWall->m_var.curSpIndex  );
	//  2012/05/14
	parseBgFileName(  this,  fileName_background  );

	//
	SUB_V_WALL	*	pSubWall	=	m_var.pWall->getCurSubWall(  );
	if  (  !pSubWall  )  goto  errLabel;
	BOOL  bMoveWindow  =  FALSE;	//  TRUE
	this->SetPicRect(  pSubWall->iW_org,  pSubWall->iH_org,  bMoveWindow  );
	this->doLayout(  );

	this->refreshWallBySp(  m_var.pWall->m_var.curSpIndex  );

	//  2012/04/10. 如果加载的规则中没有talkers区,则加入一个
	int	iSubType  =  getWndContentSubtype(  );
	if  (  isVwSubtype_confWall(  iSubType  )  )  {
		if  (  findZoneParam(  TRUE,  NULL  )  )  {
			int  iW  =  pSubWall->iW;
			int  iH  =  pSubWall->iH;
			int  iX  =  pSubWall->iX  + iW  /  5;		
			int  iY  =  pSubWall->iY  +  iH  /  4;
			iW  =  iW  *  3  /  5;
			iH  =  iH  *  1  /  2;
			//
			if  (  addZone_talkers(  m_hWnd,  FALSE,  iX,  iY,  iW,  iH  )  )  {
				showNotification(  0,  0,  0,  0,  0,  0,  _T(  "addZone_talkers failed"  )  );
				goto  errLabel;
			}
			this->refreshWallBySp(  m_var.pWall->m_var.curSpIndex  );
		}
	}

	//  2015/11/27
	this->refreshWallByRules(  m_var.pWall->m_var.curSpIndex  );


	SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )m_var.pWall->getCurSp(  );
	if  (  pSp  )  {
		if  (  !initTran(  pSp,  0  )  )  {
			pSp->op  =  OP_MOVE;
			opSp(  pSp  );
			exitTran(  pSp  );
		}
	}

	this->Onstopscrollbar(  );
	this->Onstopediting(  );
	m_var.nCtrls  =  (  m_var.nCtrls  /  6  +  1  )  *  6;
	this->OnTimer(  m_var.nTimerId  );

	Invalidate(  FALSE  );
	UpdateWindow(  );

	//
	dynBmps_setOn_quickToRetrieveImg(  this,  TRUE  );

	//
	iErr  =  0;

errLabel:

	return  iErr;
}



//
#ifdef  __DEBUG__
int  print_sp_zones(  SUB_V_WALL  *  pSubWall  )
{
	SP_STRUCT	*	pSp			=		(  SP_STRUCT  *  )pSubWall->pSp;
	Q_NODE		*	pQNode;
	SP_OBJ		*	pSpObj;
	int				nZones		=		0;
	myZONE		*	pZone		=		NULL;
	RECT			rect;

	//
	traceLog(  _T(  "print_sp_zones starts..."  )  );
	
	//
	for  (  pQNode  =  pSp->pSpObjQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf  &&  nZones  <  mycountof(  pSubWall->mems  );  pQNode  =  pQNode->pNext  )  {
		 pSpObj  =  (  SP_OBJ  *  )pQNode->qElemMemory.m_pBuf;
		 if  (  pSpObj->type  ==  SP_RECTANGLE_TYPE  )  {
			 traceLog(  _T(  "rect [%d] tn %d"  ),  nZones,  pSpObj->uiTranNo  );
			 nZones  ++  ;
		 }
	}

	traceLog(  _T(  "print_sp_zones end, total %d"  ),  nZones  );

	return  0;

}

#endif

#if 10







//
int  CDlgDynBmps::doAutoLayout_talker(  )
{
	int  iErr  =  -1;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  FALSE;
	DLG_dynBmps_var  &m_var  =  *pm_var;
	int  i;
	int  j;

	//	
	//  2017/09/17
				  
	//			
	SUB_V_WALL	*	pSubWall  =  m_var.pWall->getCurSubWall(  );
	int				iX0, iY0,  iW0,  iH0;
	int				iX,  iY,  iW,  iH;
	
	//
	m_var.pWall->resetSubWall(  m_var.pWall->m_var.curSpIndex  );


	//
	iX0  =  pSubWall->iX;
	iY0  =  pSubWall->iY;
	iW0  =  pSubWall->iW;
	iH0  =  pSubWall->iH;

	//
	CHelp_getDlgTalkVar  help_mgrVar;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )help_mgrVar.getVar(  m_var.vWall.hDlgTalk_mgr,  _T(  ""  )  );
	if  (  !pMgrVar  )  goto  errLabel;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;
	

	//
	unsigned  short  usCnt_part  =  pShadowMgr->confCtrl.grpConfCtrl.usCnt  /  3;
	unsigned  short  usCnt_4thPart  =  pShadowMgr->confCtrl.grpConfCtrl.usCnt  %  3 + usCnt_part;
	if  (  usCnt_part  *  3  <  pShadowMgr->confCtrl.grpConfCtrl.usCnt  )  usCnt_part  ++  ;

	//
	int  iRows  =  0;

	iRows  =  (  int  )sqrt(  (  double  )usCnt_part  );	
	if  (  iRows  *  iRows  <  usCnt_part  )  iRows  ++  ;

				  

	//
#if 0
	for  (  i  =  0;  i  <  3;  i  ++  )  {
		 iX  =  iX0  +  iW0  /  4  *  i;
		 iY  =  iY0  +  iH0  /  4  *  i;
		 iW  =  iW0  /  4;
		 iH  =  iH0  /  4;				  				  

		 //  add a rectangle						  	   
		 SP_RECTANGLE	tmpRectangle;				  	 
		 if  (  newCadRectangle(  (  SP_STRUCT  *  )pSubWall->pSp,  iX,  iY,  iW,  iH,  tmpRectangle  )  )  goto  errLabel;				  	   
		 m_var.vWall.uiTranNo_spObj  =  tmpRectangle.uiTranNo;
							   
		 VW_ruleU	rule;		
		 memset(  &rule,  0,  sizeof(  rule  )  );				  	   
		 rule.common.uiTranNo_spObj  =  tmpRectangle.uiTranNo;				  	   
		 //				  	   
		 rule.common.uiType  =  CONST_vwRuleType_bgMemVideo;				
		 //					   
		 switch  (  i  )  {
							   case  0:
				  					 rule.bgMemVideo.idInfo.ui64Id  =  103;
									 break;
							   case  1:
				  					 rule.bgMemVideo.idInfo.ui64Id  =  104;
									 break;
							   case  2:
				  					 rule.bgMemVideo.idInfo.ui64Id  =  105;
									 break;
							   default:
									   break;			
		 }				  	   
		 //			
		 if  (  qPostMsg(  &rule,  sizeof(  rule  ),  pSubWall->pRuleQ  )  )  goto  errLabel;			
		 //					   
		 continue;			
	}
#endif

	//
	if  (  !iRows  )  goto  errLabel;

	//
	int  nTotal  =  0;

	//
	for  (  j  =  0;  j  <  iRows;  j  ++  )  {
		//
		 if  (  nTotal  >=  pShadowMgr->confCtrl.grpConfCtrl.usCnt  )  break;			 
		 
		 for  (  i  =  0;  i  <  iRows;  i  ++  )  {
			  			 		
			 //		 
			 if  (  nTotal  >=  pShadowMgr->confCtrl.grpConfCtrl.usCnt  )  break;			 

			  //
			  iW  =  iW0  /  2  /  iRows;		 
			  iH  =  iH0  /  2  /  iRows;				  				  		 
			  //
		 	  iX  =  iX0  +  iW0  /  2  +  iW  *  i;
		 	  iY  =  iY0  +  iH  *  j;
		 
			 //  add a rectangle						  	   
			 SP_RECTANGLE	tmpRectangle;				  	 
			 if  (  newCadRectangle(  (  SP_STRUCT  *  )pSubWall->pSp,  iX,  iY,  iW,  iH,  tmpRectangle  )  )  goto  errLabel;				  	   
			 //m_var.vWall.uiTranNo_spObj  =  tmpRectangle.uiTranNo;
							   
			 VW_ruleU	rule;		
			 memset(  &rule,  0,  sizeof(  rule  )  );				  	   
			 rule.common.uiTranNo_spObj  =  tmpRectangle.uiTranNo;				  	   
			 //				  	   
			 rule.common.uiType  =  CONST_vwRuleType_bgMemVideo;				
			 //					   
			 //
			 int  index  =  nTotal;	//    +  i  *  iRows  +  j;
			 if  (  index  >=  pShadowMgr->confCtrl.grpConfCtrl.usCnt  )  break;			 
			 rule.bgMemVideo.idInfo.ui64Id  =  pShadowMgr->confCtrl.grpConfCtrl.pMems[index].idInfo.ui64Id;
			 //			
			 if  (  qPostMsg(  &rule,  sizeof(  rule  ),  pSubWall->pRuleQ  )  )  goto  errLabel;			
		 
			 //
			 #ifdef  __DEBUG__
					 traceLog(  _T(  "[%d], %d,%d,%d,%d. tn %d"  ),  nTotal,  iX,  iY,  iX  +  iW,  iY  +  iH,  rule.common.uiTranNo_spObj  );
			 #endif
			 //
			 nTotal  ++  ;

		 //					   
		 continue;
		 //
		 }
	}

	//
	for  (  j  =  0;  j  <  iRows;  j  ++  )  {
		//
		 if  (  nTotal  >=  pShadowMgr->confCtrl.grpConfCtrl.usCnt  )  break;			 
		 
		 for  (  i  =  0;  i  <  iRows;  i  ++  )  {
			  //
			 
			 //
			 if  (  nTotal  >=  pShadowMgr->confCtrl.grpConfCtrl.usCnt  )  break;			 

			  //
			  iW  =  iW0  /  2  /  iRows;		 
			  iH  =  iH0  /  2  /  iRows;				  				  		 
			  //
		 	  iX  =  iX0  +  iW  *  i;
		 	  iY  =  iY0  +  iH0  /  2   +  iH  *  j;
		 
			 //  add a rectangle						  	   
			 SP_RECTANGLE	tmpRectangle;				  	 
			 if  (  newCadRectangle(  (  SP_STRUCT  *  )pSubWall->pSp,  iX,  iY,  iW,  iH,  tmpRectangle  )  )  goto  errLabel;				  	   
			 //m_var.vWall.uiTranNo_spObj  =  tmpRectangle.uiTranNo;
							   
			 VW_ruleU	rule;		
			 memset(  &rule,  0,  sizeof(  rule  )  );				  	   
			 rule.common.uiTranNo_spObj  =  tmpRectangle.uiTranNo;				  	   
			 //				  	   
			 rule.common.uiType  =  CONST_vwRuleType_bgMemVideo;				
			 //					   
			 //
			 int index  =  nTotal;	//    +  i  *  iRows  +  j;
			 if  (  index  >=  pShadowMgr->confCtrl.grpConfCtrl.usCnt  )  break;			 
			 rule.bgMemVideo.idInfo.ui64Id  =  pShadowMgr->confCtrl.grpConfCtrl.pMems[index].idInfo.ui64Id;
			 //			
			 if  (  qPostMsg(  &rule,  sizeof(  rule  ),  pSubWall->pRuleQ  )  )  goto  errLabel;			
			 
			 //
			 #ifdef  __DEBUG__
					 traceLog(  _T(  "[%d], %d,%d,%d,%d. tn %d"  ),  nTotal,  iX,  iY,  iX  +  iW,  iY  +  iH,  rule.common.uiTranNo_spObj  );
			 #endif

		 
			 //
			 nTotal  ++  ;

		 //					   
		 continue;
		 //
		 }
	}

			//
#ifdef  __DEBUG__
	//print_sp_zones(  pSubWall  );
#endif


#if 10
	//
	for  (  j  =  0;  j  <  iRows;  j  ++  )  {

		 //
		 if  (  nTotal  >=  pShadowMgr->confCtrl.grpConfCtrl.usCnt  )  break;			 

		 //
		 for  (  i  =  0;  i  <  iRows;  i  ++  )  {
			 
			  //		 
			  if  (  nTotal  >=  pShadowMgr->confCtrl.grpConfCtrl.usCnt  )  break;			 

			  //
			  iW  =  iW0  /  2  /  iRows;		 
			  iH  =  iH0  /  2  /  iRows;				  				  		 
			  //
		 	  iX  =  iX0  +  iW0  /  2  +  iW  *  i;
		 	  iY  =  iY0  +  iH0  /  2  +  iH  *  j;
		 
			 //  add a rectangle						  	   
			 SP_RECTANGLE	tmpRectangle;				  	 
			 if  (  newCadRectangle(  (  SP_STRUCT  *  )pSubWall->pSp,  iX,  iY,  iW,  iH,  tmpRectangle  )  )  goto  errLabel;				  	   
			 //m_var.vWall.uiTranNo_spObj  =  tmpRectangle.uiTranNo;
							   
			 VW_ruleU	rule;		
			 memset(  &rule,  0,  sizeof(  rule  )  );				  	   
			 rule.common.uiTranNo_spObj  =  tmpRectangle.uiTranNo;				  	   
			 //				  	   
			 rule.common.uiType  =  CONST_vwRuleType_bgMemVideo;				
			 //					   
			 //
			 int index  =  nTotal;	//    +  i  *  iRows  +  j;
			 if  (  index  >=  pShadowMgr->confCtrl.grpConfCtrl.usCnt  )  break;			 
			 rule.bgMemVideo.idInfo.ui64Id  =  pShadowMgr->confCtrl.grpConfCtrl.pMems[index].idInfo.ui64Id;
			 //			
			 if  (  qPostMsg(  &rule,  sizeof(  rule  ),  pSubWall->pRuleQ  )  )  goto  errLabel;			
		 
			 //
			 #ifdef  __DEBUG__
					 traceLog(  _T(  "[%d], %d,%d,%d,%d. tn %d"  ),  nTotal,  iX,  iY,  iX  +  iW,  iY  +  iH,  rule.common.uiTranNo_spObj  );
			 #endif

			 //
			 nTotal  ++  ;

		 //					   
		 continue;
		 //
		 }
	}
#endif

		//
#ifdef  __DEBUG__
	//print_sp_zones(  pSubWall  );
#endif

	//	
	if  (  findZoneParam(  TRUE,  NULL  )  )  {
					  int  iW  =  pSubWall->iW  /  2;
					  int  iH  =  pSubWall->iH  /  2;
					  int  iX  =  pSubWall->iX;//  +  iW;
					  int  iY  =  pSubWall->iY;
					  if  (  addZone_talkers(  m_hWnd,  FALSE,  iX,  iY,  iW,  iH  )  )  {
						  showNotification(  0,  0,  0,  0,  0,  0,  _T(  "addZone_talkers failed"  )  );
						  goto  errLabel;		
					  }		
	}

	//
#ifdef  __DEBUG__
	//print_sp_zones(  pSubWall  );
#endif
					  
	//	
	this->refreshWallBySp(  m_var.pWall->m_var.curSpIndex  );		
	this->refreshWallByRules(  m_var.pWall->m_var.curSpIndex  );
					  
	//	
	SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )m_var.pWall->getCurSp(  );		
	if  (  pSp  )  {
					  if  (  !initTran(  pSp,  0  )  )  {
						  pSp->op  =  OP_MOVE;
						  opSp(  pSp  );
						  exitTran(  pSp  );
					  }
				  
	}
			
	//  this->Onstopscrollbar(  );	
	this->Onstopediting(  );				  				  

	//
	iErr  =  0;
errLabel:

	return  iErr;
}
#endif


//
int  CDlgDynBmps::tryToSetRule(  POINT  screenPoint,  LPCTSTR  dropStr  )
{
	int  iErr  =  -1;

	int					nPos				=		0;					//  2006/12/31
	//
	QY_MC			*	pQyMc				=		QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
		FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	QY_DMITEM		*	pItem;
	//
	unsigned  int		uCmd				=		0;
	int					iWndContentType		=		getWndContentType(  );
	unsigned int		uiTranNo_spObj		=		0;

	//
	QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );
	if  (  !pResMem  )  return  -1;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;


		//
	if  (  iWndContentType  ==  CONST_qyWndContentType_vWall  )  {
		SUB_V_WALL	*	pSubWall	=	m_var.pWall->getCurSubWall();
		if  (  !pSubWall  )  goto  errLabel;

		POINT				point;
		point  =  screenPoint;
		::MapWindowPoints(  NULL,  pSubWall->hWnd_subWall,  &point,  1  );
		#ifdef  __DEBUG__
				traceLogA(  "OnContextMenu: subWall: %d,%d",  point.x,  point.y  );
		#endif

		//
		mapSpPoint(  pSubWall,  point,  &point  );

		//
		SP_STRUCT	*	pSp		=	(  SP_STRUCT  *  )m_var.pWall->getCurSp(  );
		Q_NODE		*	pQNode;
		SP_OBJ		*	pSpObj	=	NULL;
		RECT			rc;
		
		if  (  !pSp  )  goto  errLabel;

		nPos  =  CONST_resId_popup_vWall;	
		memset(  &m_var.rule_sel,  0,  sizeof(  m_var.rule_sel  )  );

		for  (  pQNode  =  pSp->pSpObjQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf;  pQNode  =  pQNode->pNext  )  {
			 pSpObj  =  (  SP_OBJ  *  )pQNode->qElemMemory.m_pBuf;
			 if  (  pSpObj->type  !=  SP_RECTANGLE_TYPE  )  continue;
			 if  (  pSpObj->subType  !=  SP_GENERIC_RECTANGLE_TYPE  )  continue;
			 SP_RECTANGLE	*	pRectangle  =  (  SP_RECTANGLE  *  )pSpObj;
			 SP_POINT		*	pPoint0		=	(  SP_POINT  *  )pRectangle->pQNode_points[0]->qElemMemory.m_pBuf;
			 SP_POINT		*	pPoint2		=	(  SP_POINT  *  )pRectangle->pQNode_points[2]->qElemMemory.m_pBuf;

			 memset(  &rc,  0,  sizeof(  rc  )  );
			 rc.left  =  min(  pPoint0->point.rect.x,  pPoint2->point.rect.x  );
			 rc.top  =  min(  pPoint0->point.rect.y,  pPoint2->point.rect.y  );
			 rc.right  =  max(  pPoint0->point.rect.x,  pPoint2->point.rect.x  );
			 rc.bottom  =  max(  pPoint0->point.rect.y,  pPoint2->point.rect.y  );

			 if  (  point.x  >=  rc.left  &&  point.x  <=  rc.right
				 &&  point.y  >=  rc.top  &&  point.y  <=  rc.bottom  )  
			 {
				 uiTranNo_spObj  =  pSpObj->uiTranNo;
				 //
				 nPos  =  CONST_resId_popup_zone;
				 //
				 VW_ruleU  *  pRule  =  findRuleBySth(  this,  uiTranNo_spObj  );
				 if  (  pRule  )  memcpy(  &m_var.rule_sel,  pRule,  sizeof(  m_var.rule_sel  )  );
				 //
				 break;
			 }
			 
		}
	}

	if  (  !nPos  )  goto  errLabel;

	//
	QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

	//
	QIS_res_obj  resObj  =  {0};
	TCHAR  tBuf[256]  =  _T(  ""  );
	lstrcpyn(  tBuf,  dropStr,  mycountof(  tBuf  )  );
	resObj.idInfo.ui64Id  = (  unsigned  __int64  )_ttof(  tBuf  );
	TCHAR  *  pT  =  _tcschr(  tBuf,  _T(  ','  )  );
	if  (  !pT  )  goto  errLabel;
	pT  ++  ;
	TCHAR  *  pT1  =  _tcschr(  pT,  _T(  ','  )  );
	if  (  !pT1  )  goto  errLabel;
	TCHAR  ttBuf[128];
	lstrcpyn(  ttBuf,  pT,  pT1  -  pT  +  1  );
	resObj.resObj.uiObjType   =  qyGetTypeByDes(  pTable,  ttBuf  );
	
	//
	if  (  getWndContentSubtype(  )  ==  CONST_vwSubtype_avStream  )  {
		if  (  resObj.resObj.uiObjType  ==  CONST_objType_webcam  )  {
			resObj.resObj.uiObjType  =  CONST_objType_smallStream;
		}
	}

	//
	{		//  2011/11/19
							#if  !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
								VW_rule_dynBmp	rule;

								memset(  &rule,  0,  sizeof(  rule  )  );
								rule.uiType  =  CONST_vwRuleType_dynBmp;

								//									
								//
								rule.ruleDynBmp.dynBmp  = resObj;
								//  2014/08/03
								//rule.ruleDynBmp.ucbSaveVideo  =  o_u.selectDynBmp.ucbSaveVideo;
								//
								rule.uiTranNo_spObj  =  uiTranNo_spObj;
								
								COMMON_PARAM	commonParam;
								MACRO_makeCommonParam3(  this,  m_var.pWall->getCurSubWall(  ),  0,  commonParam  );
								qRemoveMsg(  m_var.pWall->getCurSubWall(  )->pRuleQ,  tmpHandler_bSameRule,  &commonParam,  &rule  );

								//
								if  (  qPostMsg(  &rule,  sizeof(  rule  ),  m_var.pWall->getCurSubWall(  )->pRuleQ  )  )  goto  errLabel;
								
								//
								this->refreshWallByRules(  m_var.pWall->m_var.curSpIndex  );

								//
								if  (  m_var.ucbShowRules  )  this->showRules(  m_var.pWall->m_var.curSpIndex  );
								
								//
								Invalidate(  FALSE  );
								UpdateWindow(  );


								//
								qmcApplyForChkingTasks_gui(  pQyMc  );		//  2009/10/12			

								//
								dynBmps_setOn_quickToRetrieveImg(  this,  TRUE  );

							#endif
								}




	//
	iErr  =  0;
errLabel:
	return  iErr;
}




//
 int  addZone_talkers(  HWND  hDlgWalls,  BOOL  bFullWall,  int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH  )
{
	int				iErr	=	-1;
	CDlgDynBmps  *  pDlg	=  (  CDlgDynBmps  *  )CWnd::FromHandle(  hDlgWalls  );

	DLG_dynBmps_var  *  pm_var  =  pDlg->get_pm_var(  );
	if  (  !pm_var  )  return -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;


	SUB_V_WALL	*	pSubWall  =  m_var.pWall->getCurSubWall(  );
	int				tmp_iX,  tmp_iY,  tmp_iW,  tmp_iH;

	tmp_iX  =  pSubWall->iX;
	tmp_iY  =  pSubWall->iY;
	tmp_iW  =  pSubWall->iW;
	tmp_iH  =  pSubWall->iH;

	if  (  !bFullWall  )
	{		//  对话框不能无限制缩小,所以此区应稍微大一点.
		tmp_iX  =  iX;	//  +  iW  /  5;
		tmp_iY  =  iY;	//  +  iH  /  4;
		tmp_iW  =  iW;	//  *  3  /  5;
		tmp_iH  =  iH;	//  *  1  /  2;
	}

	//  add a rectangle		
	SP_RECTANGLE	tmpRectangle;
	if  (  newCadRectangle(  (  SP_STRUCT  *  )pSubWall->pSp,  tmp_iX,  tmp_iY,  tmp_iW,  tmp_iH,  tmpRectangle  )  )  goto  errLabel;
	m_var.vWall.uiTranNo_spObj  =  tmpRectangle.uiTranNo;

	VW_ruleU	rule;
	memset(  &rule,  0,  sizeof(  rule  )  );
	rule.common.uiTranNo_spObj  =  tmpRectangle.uiTranNo;
	//  if  (  m_var.u.vWall.ucbVideoConference  )  
	{
		rule.common.uiType  =  CONST_vwRuleType_talkers;
	}
	if  (  qPostMsg(  &rule,  sizeof(  rule  ),  pSubWall->pRuleQ  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	return  iErr;
 }



 //  2012/04/29
 BOOL  CDlgDynBmps::bPrepareToQuit(  )
 {
	 BOOL		bRet	=	FALSE;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  FALSE;
	DLG_dynBmps_var  &m_var  =  *pm_var;


	 //  2012/05/08
	 closeSubWnds(  &m_var.subWnds  );
	 if  (  bExists_capSubWnd(  &m_var.subWnds  )  )  {
		 goto  errLabel;
	 }
	 
	 //
	 int  iZoneObjsType  =  0;
	 //
	 ZONE_objs  *  pZoneObjs  =  (  ZONE_objs  *  )pFuncs->pf_getZoneObjs(  this->m_hWnd,  this->getWndContentType(  ),  iZoneObjsType  );
	 if  (  !pZoneObjs  )  goto  errLabel;
	 ZONE_objs_info	*	pVar	=	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  this->m_hWnd,  this->getWndContentType(  ),  iZoneObjsType  );	
	 if  (  pVar  )  {
		 int  i;
		 for  (  i  =  0;  i  <  mycountof(  pVar->mems  );  i  ++  )  {
			  if  (  IsWindow(  pZoneObjs->mems[i].hWndWallMem  )  )  {
				  ::SendMessage(  pZoneObjs->mems[i].hWndWallMem,  WM_CLOSE,  0,  0  );
			  }
		 }
		 for  (  i  =  0;  i  <  mycountof(  pVar->mems  );  i  ++  )  {
			  if  (  IsWindow(  pZoneObjs->mems[i].hWndWallMem  )  )  {
				  #ifdef  __DEBUG__
						  traceLog(  _T(  "dlgDynBmps::bPrepareToQuit failed, hWndWallMem still alive"  )  );
				  #endif
				  goto  errLabel;
			  }
		 }
	 }

	 //  2013/06/10.
	 ::SendMessage(  m_var.pWall->m_var.hWnd_spToolbox,  WM_CLOSE,  0,  0  );
	 if  (  IsWindow(  m_var.pWall->m_var.hWnd_spToolbox  )  )  {
		  #ifdef  __DEBUG__
				  traceLog(  _T(  "dlgDynBmps::bPrepareToQuit failed, hWnd_spToolbox still alive"  )  );
		  #endif
		  goto  errLabel;
	 }


	 bRet  =  TRUE;
errLabel:
	 return  bRet;
 }


 BOOL  CDlgDynBmps::bQuitDlg(  )
{
	BOOL	bRet  =  FALSE;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  FALSE;
	DLG_dynBmps_var  &m_var  =  *pm_var;


	HWND	tmph  =  m_hWnd;
	if  (  m_var.bLocked_toQuitDlg1  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgDynBmps::bQuitDlg failed, bLocked already."  )  );
		return  FALSE;
	}
	m_var.bLocked_toQuitDlg1  =  TRUE;

	if  (  !bPrepareToQuit(  )  )  goto  errLabel;

	bRet  =  CDlgDesktopsMon::bQuitDlg(  );
	
errLabel:
	
	//
	if  (  IsWindow(  tmph  )  )  {
		m_var.bLocked_toQuitDlg1  =  FALSE;
	}

	return  bRet;
}


 //
BOOL CDlgDynBmps::OnInitDialog()
{
	CDlgDesktopsMon::OnInitDialog();

	// TODO:  Add extra initialization here
	int						iErr				=	-1;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  FALSE;
	DLG_dynBmps_var  &m_var  =  *pm_var;


	if  (  !m_var.pMisCnt  )  goto  errLabel;
	MC_VAR_isCli			*	pProcInfo			=  QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  goto  errLabel;
	QY_MC				*	pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;
	//
	FUNCS_for_isCliHelp	*	pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;
	//
	CDlgDesktopsMon		*	pBase				=	this;
	int						iWndContentType		=	getWndContentType(  );
	int						iWndContentSubtype	=	getWndContentSubtype(  );
	SUB_V_WALL			*	pSubWall			=	NULL;
	//

	//
	this->m_brush_desc_normal.CreateSolidBrush(  CONST_vWall_bg_normal  );
	this->m_brush_desc_fullScreen.CreateSolidBrush(  CONST_vWall_bg_fullScreen  );




	//
	m_var.pWall  =  new  CQyVWall(  );
	if  (  !m_var.pWall  )  goto  errLabel;
	m_var.pWall->m_var.hWnd  =  this->m_hWnd;

	//  2012/04/02
	m_var.pZoneObjs  =  (  ZONE_objs  *  )mymalloc(  sizeof(  ZONE_objs  )  );
	if  (  !m_var.pZoneObjs  )  goto  errLabel;
	memset(  m_var.pZoneObjs,  0,  sizeof(  ZONE_objs  )  );
	m_var.pZoneObjsInfo_talkers  =  (  ZONE_objs_info  *  )mymalloc(  sizeof(  ZONE_objs_info  )  );
	if  (  !m_var.pZoneObjsInfo_talkers  )  goto  errLabel;
	memset(  m_var.pZoneObjsInfo_talkers,  0,  sizeof(  ZONE_objs_info  )  );

	//  2015/11/15
	QMC_objVar_info  *  pObjVarInfo  =  getQmcObjVarInfoByIndex(  pProcInfo,  m_var.iIndex_objVarInfo  );
	if  (  !pObjVarInfo  ||  !pObjVarInfo->bUsed  )  goto  errLabel;
	pObjVarInfo->var.hWnd  =  m_hWnd;
	
	//  2018/07/03
	m_drop.Register(  this  );


	//
	switch  (  iWndContentType  )  {


			case  CONST_qyWndContentType_vWall:  {
				  int  i;
				  
				  // TODO:  Add extra initialization here

				  for  (  i  =  0;  i  <  pBase->m_var.usCnt_row  *  pBase->m_var.usCnt_col;  i  ++  )  {
					   QY_DMITEM		*	pItem;
					   int					idc;
					   int					idcHint;

					   pItem  =  &pBase->m_var.pIdcTable[i];
					   idc  =  (  int  )pItem->des;	
					   idcHint  =  (  int  )pItem->pData;

					   if  (  m_var.pWall->addSubWall(  idc,  idcHint  )  )  goto  errLabel;

					   #ifdef  __DEBUG__
					   //	   m_var.pWall->setBitmap(  _T(  "c:\\tttbbb\\BACKGRND.bmp"  ),  i  );
					   #endif
				  }

				  m_var.pWall->m_var.curSpIndex  =  0;

				  //
				  if  (  registerSubWnd(  this->m_hWnd,  iWndContentType,  iWndContentSubtype,  0,  &m_var.vWall.idInfo,  m_var.vWall.uiObjType,  m_var.vWall.usIndex_obj,  &m_var.pMisCnt->subWnds,  NULL  )  )  goto  errLabel;

				  m_var.nElapseInMs  =  1000;

				  }
				  break;
			default:
					#ifdef  __DEBUG__
							traceLogA(  "DlgDynBmp: unprocessed wndContentType %d",  getWndContentType(  )  );
					#endif
				    break;
			
	}

	if  (  !m_var.pWall->m_var.usCnt  )  {		//  2009/10/02
		QY_DMITEM		*	pItem			=	pBase->m_var.pIdcTable;
		if  (  m_var.pWall->addSubWall(  (  int  )pItem[0].des,  (  int  )pItem[0].pData  )  )  goto  errLabel;

		pSubWall  =  m_var.pWall->getSubWall(  0  );
		if  (  !pSubWall  )  goto  errLabel;
		pSubWall->usCnt  =  1;
	}
	
	//
	int  i;
	for  (  i  =  0;  i  <  m_var.pWall->m_var.usCnt;  i  ++  )  {
		 SUB_V_WALL	*	pSubWall	=	m_var.pWall->getSubWall(  i  );
		 if  (  !pSubWall->idc  )  continue;
		 
		 if  (  pSubWall->hBmp_background  )  {
			 SetPicRect(  pSubWall->iW_org,  pSubWall->iH_org,  TRUE  );
			 doLayout(  );
		 }
		 
		 //  GetDlgItem(  pSubWall->idc  )->ModifyStyle(  SS_TYPEMASK,  SS_OWNERDRAW  );
	}

	//  2012/0408
	ZONE_objs_info  *  pWallTalkers  =  (  ZONE_objs_info  *  )m_var.pZoneObjsInfo_talkers;
	RECT	rc;
	pSubWall  =  m_var.pWall->getCurSubWall(  );
	if  (  !pSubWall  )  goto  errLabel;
	HWND	hCtrl  =  pSubWall->hWnd_subWall;
	::GetClientRect(  hCtrl,  &rc  );
	pWallTalkers->guiData.w_org  =  rc.right  -  rc.left;
	pWallTalkers->guiData.h_org  =  rc.bottom  -  rc.top;


	//
	//  this->sizeAllControls(  );
	this->doLayout(  );

	//
	BOOL  bNeedNewRect  =  FALSE;
	//
	if  (  m_var.vWall.idInfo.ui64Id  
		||  iWndContentSubtype  ==  CONST_vwSubtype_qvcf  )
	{
		bNeedNewRect  =  TRUE;
	}
	//
	//  if  (  m_var.u.vWall.idInfo.ui64Id  )  
	if  (  bNeedNewRect  )  
	{
		SUB_V_WALL	*	pSubWall  =  m_var.pWall->getCurSubWall(  );
		int				iX,  iY,  iW,  iH;

		iX  =  pSubWall->iX;
		iY  =  pSubWall->iY;
		iW  =  pSubWall->iW;
		iH  =  pSubWall->iH;
		if  (  m_var.vWall.ucbVideoConference  )  {
			iX  =  iX  +  iW  /  4;
			iY  =  iY  +  iH  /  4;
			iW  =  iW  /  2;
			iH  =  iH  /  2;
		}

		//  add a rectangle		
		SP_RECTANGLE	tmpRectangle;
		if  (  newCadRectangle(  (  SP_STRUCT  *  )pSubWall->pSp,  iX,  iY,  iW,  iH,  tmpRectangle  )  )  goto  errLabel;
		m_var.vWall.uiTranNo_spObj  =  tmpRectangle.uiTranNo;

		VW_ruleU	rule;
		memset(  &rule,  0,  sizeof(  rule  )  );
		rule.common.uiTranNo_spObj  =  tmpRectangle.uiTranNo;
		if  (  m_var.vWall.ucbVideoConference  )  {
			rule.common.uiType  =  CONST_vwRuleType_conference_imGrp;
			rule.conference_imGrp.idInfo.ui64Id  =  m_var.vWall.idInfo.ui64Id;
			}
		else  {
			  rule.common.uiType  =  CONST_vwRuleType_dynBmp;
			  rule.dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id  =  m_var.vWall.idInfo.ui64Id;
			  rule.dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType  =  m_var.vWall.uiObjType;
			  rule.dynBmp.ruleDynBmp.dynBmp.resObj.usIndex_obj  =  m_var.vWall.usIndex_obj;
		}
		if  (  qPostMsg(  &rule,  sizeof(  rule  ),  pSubWall->pRuleQ  )  )  goto  errLabel;

		this->refreshWallBySp(  m_var.pWall->m_var.curSpIndex  );

		SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )m_var.pWall->getCurSp(  );
		if  (  pSp  )  {
			if  (  !initTran(  pSp,  0  )  )  {
				pSp->op  =  OP_MOVE;
				opSp(  pSp  );
				exitTran(  pSp  );
			}
		}

		//  this->Onstopscrollbar(  );
		this->Onstopediting(  );
		
	}

	//  2012/04/02
	switch  (  iWndContentSubtype  )  {
			case  CONST_vwSubtype_confWall:  
			case  CONST_vwSubtype_globalGps:  {

				  if  (  addZone_talkers(  m_hWnd,  TRUE,  0,  0,  0,  0  )  )  goto  errLabel;

				  this->refreshWallBySp(  m_var.pWall->m_var.curSpIndex  );

				  SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )m_var.pWall->getCurSp(  );
				  if  (  pSp  )  {
					  if  (  !initTran(  pSp,  0  )  )  {
						  pSp->op  =  OP_MOVE;
						  opSp(  pSp  );
						  exitTran(  pSp  );
					  }
				  }

				  //  this->Onstopscrollbar(  );
				  this->Onstopediting(  );
		
				  }
				  //  
				  break;
			case  CONST_vwSubtype_bgWall:  {
				  }
				  break;
			case  CONST_vwSubtype_gps:		//  2012/04/22
				  break;
			case  CONST_vwSubtype_qvcf:  {	//  2015/05/09
				  //  not finished
				  int  len  =  sizeof(  SHARE_dyn_bmp  );
				  if  (  m_var.vWall.pShareDynBmp_toPlayFile  )  {
					  showInfo_open0(  0,  0,  _T(  "dynBmp failed: pSharedDynBmp_toPlayFile is not null"  )  );
					  goto  errLabel;	
				  }
				  m_var.vWall.pShareDynBmp_toPlayFile  =  (  SHARE_DYN_BMP  *  )mymalloc(  len  );
				  if  (  !m_var.vWall.pShareDynBmp_toPlayFile  )  goto  errLabel;	
				  memset(  m_var.vWall.pShareDynBmp_toPlayFile,  0,  len  );

				  //
				  unsigned  int  uiObjType  =  CONST_objType_qvcf;
				  //
				  SHARE_dyn_bmp  *  pShareDynBmp  =  m_var.vWall.pShareDynBmp_toPlayFile;
				  //	
				  pShareDynBmp->resObj.uiObjType  =  uiObjType;	
				  pShareDynBmp->resObj.usIndex_obj  =  0;
				  //
				  safeTcsnCpy(  m_var.vWall.fileName,  pShareDynBmp->name,  mycountof(  pShareDynBmp->name  )  );
				  //  2014/09/28
				  if  (  pFuncs->shareDynBmps.pf_toShareDynBmp(  pProcInfo,  m_hWnd,  NULL,  0,  NULL,  0,  NULL,  pShareDynBmp  )  )  goto  errLabel;
				  
				  //  2015/0
				  safeTcsnCpy(  m_var.vWall.fileName,  m_var.title,  mycountof(  m_var.title  )  );

				  }
				  break;
			default:
					break;
	}

	//  2012/05/08
	unsigned  short  usMaxCnt  =  DEFAULT_usMaxCnt_capSubWnds;
	if  (  iWndContentType  ==  CONST_qyWndContentType_vWall  )  usMaxCnt  =  350;
	if  (  initCapSubWnds(  usMaxCnt,  &m_var.subWnds  )  )  goto  errLabel;


	//
	m_var.pMsgBuf_doWnd_guiMsgArrive  =  (  MIS_MSGU  *  )mymalloc(  sizeof(  MIS_MSGU  )  );
	if  (  !m_var.pMsgBuf_doWnd_guiMsgArrive  )  goto  errLabel;

	//  2017/09/22
	int  iSize;	
	m_var.usCnt_zoneParams  =  pProcInfo->av.usCnt_players;
	iSize  =  m_var.usCnt_zoneParams  *  sizeof(  ZONE_PARAM  );
	m_var.pZoneParams  =  (  ZONE_PARAM  *  )mymalloc(  iSize  );
	if  (  !m_var.pZoneParams  )  goto  errLabel;
	memset(  m_var.pZoneParams,  0,  iSize  );

	//
	//if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )  
	{

		viewDlgAvRes(  m_hWnd,  getWndContentType(  ),  1,  0,  m_hWnd,  pFuncs->pf_getZoneObjsInfo(  pProcInfo,  m_hWnd,  this->getWndContentType(  ),  0  ),  FALSE  );

		ZONE_objs_info	*  pZoi  =	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  m_hWnd,  this->getWndContentType(  ),  0  );
					
		if  (  IsWindow(  pZoi->hBar  )  )  {		
			::PostMessage(  pZoi->hBar,  WM_CLOSE,  0,  0  );		
		}
	}

	//
	if  (  m_var.nElapseInMs  )  {
		m_var.nTimerId  =  SetTimer(  1,  m_var.nElapseInMs,  NULL  );
		if  (  !m_var.nTimerId  )  goto  errLabel;
	}

	SetWindowText(  m_var.title  );

	//
	m_var.bInited  =  TRUE;

	//
	iErr  =  0;

errLabel:
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

 BOOL CDlgDynBmps::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	//  2017/06/14
	DLG_dynBmps_var  *  pm_var  =  get_pm_var(  );
	if  (  pm_var->bAvConsole  )  {
		if  (  pMsg->message  ==  WM_KEYDOWN  )  {			  
			UINT	nChar  =  pMsg->wParam;
			if  (  nChar  ==  VK_ESCAPE  )  {				
				CDlgDesktopsMon  *  pBase  =  this;
#if  0
				if  (  pBase->m_var.m_bFullScreen  )  {
					endFullScreen(  );						   
					return  TRUE;					   
				}
#endif
				//
				if  (  IDOK  !=  qyMessageBox(  m_hWnd,  _T(  "Are you sure to close the window?"  ),  _T(  ""  ),  MB_OKCANCEL,  10000,  NULL  )  )  {
					return  TRUE;
				}
				//
				showInfo_open0(  0,  0,  _T(  "dlgDynBmps: avConsole, escape, to close"  )  );
				//
				PostMessage(  WM_CLOSE  );
				//
				return  TRUE;
			}
		}
	}

	//
	switch  (  pMsg->message  )  {
			case  WM_KEYDOWN:
			case  WM_KEYUP:
			case  WM_SYSKEYDOWN:
			case  WM_SYSKEYUP:
				  processKeyEvent(  pMsg->wParam,  pMsg->lParam  );
				  break;
			case  WM_CHAR:
			case  WM_SYSCHAR:
				  break;
			case  WM_KILLFOCUS:
				  //  resetKeyEvent(  );
				  break;
			default:
					break;
	}


	return CDlgDesktopsMon::PreTranslateMessage(pMsg);
}


 //
 //  2014/11/30
  ZONE_PARAM  *  dlgDynBmps_getZoneParam(  HWND  hDlg,  DLG_dynBmps_var  &  m_var,  MIS_MSG_procVideo_qmc  *  pMsg  )
 {
	 ZONE_PARAM  *  pZoneParam  =  NULL;
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 
	 if  (  pMsg->playerId.index_player  <  0  ||  pMsg->playerId.index_player  >=  m_var.usCnt_zoneParams  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_procVideo failed: index_player is < 0 or >= usCnt_zoneParams"  )  );
		goto  errLabel;
	}
	pZoneParam  =  &m_var.pZoneParams[pMsg->playerId.index_player];

errLabel:

	return  pZoneParam;
 }






  //
  LRESULT CDlgDynBmps::OnDropEx(WPARAM pDropInfoClass, LPARAM lParm)
{
	return (LRESULT)-1;
}


LRESULT CDlgDynBmps::OnDrop(WPARAM pDropInfoClass, LPARAM lParm)
{
	COleDropInfo* pInfo = (COleDropInfo* )pDropInfoClass;
	ASSERT(pInfo->IsKindOf(RUNTIME_CLASS(COleDropInfo)));

	if( pInfo->m_pDataObject->IsDataAvailable( CF_TEXT ) )
	{
		HGLOBAL hMem = pInfo->m_pDataObject->GetGlobalData( CF_TEXT );
		char* lp = (char *)GlobalLock((HGLOBAL) hMem);//lock source
		if (lp != NULL)
		{
			CString str = CString(  lp  );
			TCHAR  *  pT  =  (  TCHAR  *  )lp;
			//Set Windows title with Drop text
			//  SetWindowText(  pT  );
			//
			DWORD dwPos = ::GetMessagePos();
			CPoint pt(LOWORD(dwPos), HIWORD(dwPos));
			//ScreenToClient(&pt);    //得到树形视图客户区坐标
			//
			tryToSetRule(  pt,  pT  );
			//
			UpdateData(TRUE);
		}
		GlobalUnlock( hMem );//unlock source
		return TRUE;
	}
	else
		return FALSE;
}

//
LRESULT CDlgDynBmps::OnDragOver(WPARAM pDropInfoClass, LPARAM lParm)
{
	COleDropInfo* pInfo = (COleDropInfo* )pDropInfoClass;
	ASSERT(pInfo->IsKindOf(RUNTIME_CLASS(COleDropInfo)));

	if( pInfo->m_pDataObject->IsDataAvailable( CF_TEXT ) )
		return DROPEFFECT_COPY;
	else
		return DROPEFFECT_NONE;
}



 
// CDlgDynBmps message handlers

 LRESULT  CDlgDynBmps::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	long				lRet				=					-1;
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	CDlgDesktopsMon	*	pBase				=					this;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	CTX_qm_thread  *  pCqt  =  &pQyMc->gui.ctx_gui_thread;
	//
	int					iWndContentType		=					getWndContentType(  );
	int					iWndContentSubtype  =					getWndContentSubtype(  );	//  2017/09/22
	
	//
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	if  (  !pComm  )  return  -1;

	switch  (  pComm->uiType  )  {
			case  CONST_misMsgType_procVideo_qmc:  {
				  MIS_MSG_procVideo_qmc		*	pMsg			=	(  MIS_MSG_procVideo_qmc  *  )pComm;
				  //
				  //BOOL							bUseDxSurface	=	m_var.bUseDirectX;
				
#ifdef  __DEBUG__
	    //  bUseDxSurface  =  FALSE;
#endif

					  //
					  if  (  iWndContentType  ==  CONST_qyWndContentType_vWall  )  {

						  //  2015/05/15
						  if  (  iWndContentSubtype  ==  CONST_vwSubtype_qvcf  )  {
							  SUB_V_WALL	*	pSubWall	=	m_var.pWall->getSubWall(  0  );
							  if  (  !pSubWall  )  goto  errLabel;
							  myZONE		*	pZone		=	&pSubWall->mems[0];
							  

							  {
									if  (  pMsg->bih.biWidth  &&  pMsg->bih.biHeight  )  {
										if  (  pBase->m_var.uiInitW_pic  !=  pMsg->bih.biWidth  ||  pBase->m_var.uiInitH_pic  !=  pMsg->bih.biHeight  )  {
											pBase->m_var.uiInitW_pic  =  pMsg->bih.biWidth;
											pBase->m_var.uiInitH_pic  =  pMsg->bih.biHeight;
											//
											this->SetPicRect(  pMsg->bih.biWidth,  pMsg->bih.biHeight,  TRUE  );
											//
											this->doLayout(  );
											//
											switch  (  m_var.vWall.uiObjType  )  {	//  2010/09/12
													case  CONST_objType_screen:
														  //  PostMessage(  WM_COMMAND,  MAKEWPARAM(  ID_stopScrollBar,  0  ),  0  );
														  //  PostMessage(  WM_COMMAND,  MAKEWPARAM(  ID_startScrollBar,  0  ),  0  );													
														  break;
													default:
															//  this->bEnableScrollBar(  FALSE  );
														    PostMessage(  WM_COMMAND,  MAKEWPARAM(  ID_startScrollBar,  0  ),  0  );													
															PostMessage(  WM_COMMAND,  MAKEWPARAM(  ID_stopScrollBar,  0  ),  0  );
															break;
											}
											//
											//if  (  m_var.u.vWall.idInfo.ui64Id  &&  m_var.u.vWall.uiObjType  )  
											{
												Q_NODE	*	pQNode	=	findSpQNode(  (  SP_STRUCT  *  )m_var.pWall->getCurSp(  ),  m_var.vWall.uiTranNo_spObj  );
												if  (  !pQNode  )  goto  errLabel;
												SP_RECTANGLE	*	pRectangle  =  (  SP_RECTANGLE  *  )pQNode->qElemMemory.m_pBuf;
												//  int					i;
												if  (  pRectangle->type  !=  SP_RECTANGLE_TYPE  ||  pRectangle->subType  !=  SP_GENERIC_RECTANGLE_TYPE  )  goto  errLabel;
			
												SP_POINT	*	pPoint;

												pPoint  =  (  SP_POINT  *  )pRectangle->pQNode_points[0]->qElemMemory.m_pBuf;
												pPoint->point.rect.x  =  0;  
												pPoint->point.rect.y  =  0;
												pPoint  =  (  SP_POINT  *  )pRectangle->pQNode_points[1]->qElemMemory.m_pBuf;
												pPoint->point.rect.x  =  pMsg->bih.biWidth;  
												pPoint->point.rect.y  =  0;
												pPoint  =  (  SP_POINT  *  )pRectangle->pQNode_points[2]->qElemMemory.m_pBuf;
												pPoint->point.rect.x  =  pMsg->bih.biWidth;  
												pPoint->point.rect.y  =  pMsg->bih.biHeight;
												pPoint  =  (  SP_POINT  *  )pRectangle->pQNode_points[3]->qElemMemory.m_pBuf;
												pPoint->point.rect.x  =  0;  
												pPoint->point.rect.y  =  pMsg->bih.biHeight;

												this->refreshWallBySp(  m_var.pWall->m_var.curSpIndex  );

												SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )m_var.pWall->getCurSp(  );
												if  (  pSp  )  {
													if  (  !initTran(  pSp,  0  )  )  {
														pSp->op  =  OP_MOVE;
														opSp(  pSp  );
														exitTran(  pSp  );
													}
												}
												//
											}
										}
									}
								}



							  //  2011/11/27. 在全高清视频时，在笔记本上显示不了了，不能使用dx.
							  //bUseDxSurface  =  FALSE;
							  
							  //
							  //if  (  drawCapImages(  this->m_hWnd,  pSubWall->idc,  &pSubWall->hDc_dst,  NULL,  m_var.ucbLocalAv,  pMsg,  0,  0,  pBase->m_var.mems_org[0].iW,  pBase->m_var.mems_org[0].iH,  NULL,  NULL,  &pZone->images,  bUseDxSurface,  FALSE  )  )  goto  errLabel;					  			
							  pSubWall->hWnd_dst  =  m_hWnd;
							  if  (  drawCapImages(  old_M_GetDlgItem(  this->m_hWnd,  (  int  )pSubWall->idc  ),  m_var.ucbAutoClip,  pMsg,  pZone->iX,  pZone->iY,  pZone->iW,  pZone->iH,  NULL,  NULL,  &pZone->images,  pSubWall->hWnd_dst,  &pSubWall->hDc_dst,  NULL  )  )  goto  errLabel;
							  
							  break;				 
						  }

						  //
							ZONE_PARAM	*	pZoneParam	=	NULL;

							//
							pZoneParam  =  dlgDynBmps_getZoneParam(  m_hWnd,  m_var,  pMsg  );	//  (  ZONE_PARAM  *  )pMsg->paramMsgToShadow.pZoneParam;
							if  (  !pZoneParam  )  {
								goto  errLabel;
							}

							//
							SUB_V_WALL  *	pSubWall	=	NULL;
							myZONE		*	pZone		=	NULL;
							BOOL			bZoneOk		=	FALSE;
							if  (  pZoneParam->uiTranNo_zone  )  {
								pSubWall  =  m_var.pWall->getSubWall(  pZoneParam->index_subWall  );
								if  (  pSubWall  )  {
									if  (  pZoneParam->index_zone  >=  0  &&  pZoneParam->index_zone  <  pSubWall->usCnt  )  {
										pZone	=	&pSubWall->mems[pZoneParam->index_zone];
										//
										if  (  pZone->uiTranNo_spObj  ==  pZoneParam->uiTranNo_zone  )  {
											if  (  pZoneParam->index_capImage  >=  0  &&  pZoneParam->index_capImage  <  mycountof(  pZone->images.mems  )  )  {
												CAP_IMAGE	*	pImg	=	&pZone->images.mems[pZoneParam->index_capImage];
												if  (  pImg->idInfo_sender.ui64Id  ==  pMsg->idInfo_sender.ui64Id  
													&&  pImg->uiTranNo_openAvDev  ==  pMsg->uiTranNo_openAvDev
													&&  pImg->iTaskId  ==  pMsg->iTaskId  //  2017/12/31
													&&  pImg->usIndex_activeMems_from  ==  pMsg->usIndex  )  
												{
													bZoneOk  =  TRUE;
												}
											}
										}
										//
										if  (  !bZoneOk  )  {
											#ifdef  __DEBUG__
													traceLogA(  "dlgDynBmps::OnQyComm, zone is bad"  );
											#endif
											//  freeCapImages(  this,  pSubWall->idc,  NULL,  &pZone->images  );
										}
									}
								}
							}
							//  traceLogA(  "here"  );
							if  (  !bZoneOk  )  {
								memset(  pZoneParam,  0,  sizeof(  pZoneParam[0]  )  );
								//  if  (  this->getZoneParam(  pMsg,  pZoneParam  )  )  
								if  (  dlgDynBmps_findZoneParam(  m_hWnd,  pMsg,  pZoneParam  )  )  
								{
									#ifdef  __DEBUG__
											traceLogA(  "DlgDynBmps::OnQyComm failed: getZoneParam failed."  );
									#endif
									goto  errLabel;
								}
								if  (  !pZoneParam->uiTranNo_zone  )  {
									#ifdef  __DEBUG__
											traceLogA(  "dlgDynBmps::OnQyComm failed: getZoneParam: uiTranNo_zone is 0"  );
									#endif
									goto  errLabel;
								}
								pSubWall  =  m_var.pWall->getSubWall(  pZoneParam->index_subWall  );
								if  (  !pSubWall  )  goto  errLabel;
								if  (  pZoneParam->index_zone  <  0  ||  pZoneParam->index_zone  >=  pSubWall->usCnt  )  {
									//  traceLogA(  "dlgDynBmps::OnQyComm failed: index_zone %d, subWall.usCnt %d",  pPlayer->video.m_var.zoneParam.index_zone,  pSubWall->usCnt  );
									goto  errLabel;
								}
								pZone	=	&pSubWall->mems[pZoneParam->index_zone];
								
								//  2018/01/01
								if  (  pZone->rule.common.uiType  ==  CONST_vwRuleType_bgMemVideo  )  {
									freeCapImages(  m_hWnd,  pSubWall->idc,  &pZone->images,  pSubWall->hWnd_dst,  NULL  );
								}

								//  2017/01/10
							#if  0  //  2018/07/07
								if  (  m_var.quickToRetrieveImg.ucbOn  )  {
									if  (  pMsg->bih.biWidth  &&  pMsg->bih.biHeight  )  {
										m_var.quickToRetrieveImg.ucbOn  =  FALSE;
									}
								}
							#endif
								//								
								if  (  m_var.ucbAutoSize1  &&  m_var.pWall->m_var.usCnt  ==  1  &&  m_var.pWall->getSubWall(  0  )->usCnt  ==  1  )  {
									if  (  pMsg->bih.biWidth  &&  pMsg->bih.biHeight  )  {
										if  (  pBase->m_var.uiInitW_pic  !=  pMsg->bih.biWidth  ||  pBase->m_var.uiInitH_pic  !=  pMsg->bih.biHeight  )  {
											pBase->m_var.uiInitW_pic  =  pMsg->bih.biWidth;
											pBase->m_var.uiInitH_pic  =  pMsg->bih.biHeight;
											//
											BOOL  bMove  =  TRUE;
											//
											if  (  pBase->m_var.param_bValid_pos  )  {
												bMove  =  FALSE;
											}
											//
											this->SetPicRect(  pMsg->bih.biWidth,  pMsg->bih.biHeight,  bMove  );
											this->doLayout(  );
											//
											switch  (  m_var.vWall.uiObjType  )  {	//  2010/09/12
													case  CONST_objType_screen:
														  //  PostMessage(  WM_COMMAND,  MAKEWPARAM(  ID_stopScrollBar,  0  ),  0  );
														  //  PostMessage(  WM_COMMAND,  MAKEWPARAM(  ID_startScrollBar,  0  ),  0  );													
														  break;
													default:
															//  this->bEnableScrollBar(  FALSE  );
														    PostMessage(  WM_COMMAND,  MAKEWPARAM(  ID_startScrollBar,  0  ),  0  );													
															PostMessage(  WM_COMMAND,  MAKEWPARAM(  ID_stopScrollBar,  0  ),  0  );
															break;
											}
											//
											if  (  m_var.vWall.idInfo.ui64Id  &&  m_var.vWall.uiObjType  )  {
												Q_NODE	*	pQNode	=	findSpQNode(  (  SP_STRUCT  *  )m_var.pWall->getCurSp(  ),  m_var.vWall.uiTranNo_spObj  );
												if  (  !pQNode  )  goto  errLabel;
												SP_RECTANGLE	*	pRectangle  =  (  SP_RECTANGLE  *  )pQNode->qElemMemory.m_pBuf;
												//  int					i;
												if  (  pRectangle->type  !=  SP_RECTANGLE_TYPE  ||  pRectangle->subType  !=  SP_GENERIC_RECTANGLE_TYPE  )  goto  errLabel;
			
												SP_POINT	*	pPoint;

												pPoint  =  (  SP_POINT  *  )pRectangle->pQNode_points[0]->qElemMemory.m_pBuf;
												pPoint->point.rect.x  =  0;  
												pPoint->point.rect.y  =  0;
												pPoint  =  (  SP_POINT  *  )pRectangle->pQNode_points[1]->qElemMemory.m_pBuf;
												pPoint->point.rect.x  =  pMsg->bih.biWidth;  
												pPoint->point.rect.y  =  0;
												pPoint  =  (  SP_POINT  *  )pRectangle->pQNode_points[2]->qElemMemory.m_pBuf;
												pPoint->point.rect.x  =  pMsg->bih.biWidth;  
												pPoint->point.rect.y  =  pMsg->bih.biHeight;
												pPoint  =  (  SP_POINT  *  )pRectangle->pQNode_points[3]->qElemMemory.m_pBuf;
												pPoint->point.rect.x  =  0;  
												pPoint->point.rect.y  =  pMsg->bih.biHeight;

												this->refreshWallBySp(  m_var.pWall->m_var.curSpIndex  );

												SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )m_var.pWall->getCurSp(  );
												if  (  pSp  )  {
													if  (  !initTran(  pSp,  0  )  )  {
														pSp->op  =  OP_MOVE;
														opSp(  pSp  );
														exitTran(  pSp  );
													}
												}
												//
											}
											//
											//  2017/02/14
											if  (  pBase->m_var.param_bFullScreen  )  {
												PostMessage(  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );
											}

										}
									}
								}
							}
							//  traceLogA(  "here1"  );

							//  
							//  if  (  drawCapImages(  this->m_hWnd,  (  int  )pSubWall->idc,  &pSubWall->hDc,  NULL,  m_var.ucbLocalAv,  pMsg,  pZone->iX,  pZone->iY,  pZone->iW,  pZone->iH,  NULL,  pZoneParam,  &pZone->images,  bUseDxSurface,  FALSE  )  )  goto  errLabel;
							pSubWall->hWnd_dst  =  m_hWnd;
							if  (  drawCapImages(  old_M_GetDlgItem(  this->m_hWnd,  (  int  )pSubWall->idc  ),  m_var.ucbAutoClip,  pMsg,  pZone->iX,  pZone->iY,  pZone->iW,  pZone->iH,  NULL,  pZoneParam,  &pZone->images,  pSubWall->hWnd_dst,  &pSubWall->hDc_dst,  NULL  )  )  goto  errLabel;
				  }
#if  0  //  2016/12/27
				  if  (  pMsg->uiEventId_lastRecvd  )  {
					  //  m_var.uiEventId_lastRecvd  =  pMsg->uiEventId_lastRecvd;
				  }
#endif

				  }				  
				  break;

			case  CONST_qyWmParam_freeCapImage:	//  2010/09/12
				  int				i,  j;
				  QY_MESSENGER_ID	idInfo;
				  idInfo.ui64Id  =  pComm->u.freeCapImage.idInfo.ui64Id;
				  
				  //  freeCapImageBySth(  m_hWnd,  m_var.idc,  pComm->u.freeCapImage.iTaskId,  &idInfo,  &m_var.images  );	

				  for  (  i  =  0;  i  <  m_var.pWall->m_var.usCnt;  i  ++  )  {
					  SUB_V_WALL	*	pSubWall  =  m_var.pWall->getSubWall(  i  );
					  if  (  !pSubWall  )  continue;
					  for  (  j  =  0;  j  <  pSubWall->usCnt;  j  ++  )  {
						  freeCapImageBySth(  pCqt,  m_hWnd,  pSubWall->idc,  pComm->u.freeCapImage.iTaskId,  &idInfo,  &pSubWall->mems[j].images,  pSubWall->hWnd_dst  );
					  }
				  }
				  break;

			case  CONST_qyWmParam_chkTask:
				  if  (  toChkTask(  pComm  )  )  goto  errLabel;
				  break;

			case  CONST_misMsgType_applyForTalkerShadow_qmc:  {	//  2012/04/23
				  MIS_MSG_applyForTalkerShadow_qmc	*	pMsg  =  (  MIS_MSG_applyForTalkerShadow_qmc  *  )lParam;
				  //  
				  SUB_V_WALL	*	pSubWall	=	m_var.pWall->getCurSubWall(  );
				  if  (  !pSubWall  )  goto  errLabel;
				  for  (  i  =  0;  i  <  pSubWall->usCnt;  i  ++  )  {
					  if  (  pSubWall->mems[i].uiTranNo_spObj  ==  pMsg->uiTranNo_zone  )  break;
				  }
				  if  (  i  ==  pSubWall->usCnt  )  goto  errLabel;
				  myZONE  *  pZone  =  &pSubWall->mems[i];

				  unsigned  int  uiTranNo_spObj  =  pMsg->uiTranNo_zone;

				  Q_NODE	*	pQNode;
				  //
				  for  (  pQNode  =  pSubWall->pRuleQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf;  pQNode  =  pQNode->pNext  )  {
					   VW_ruleU	*	pRule	=	(  VW_ruleU  *  )pQNode->qElemMemory.m_pBuf;
			 
					   if  (  uiTranNo_spObj  ==  pRule->common.uiTranNo_spObj
						   &&  pRule->common.uiType  ==  CONST_vwRuleType_messenger  
						   &&  pRule->messenger.idInfo.ui64Id  ==  pMsg->idInfo.ui64Id
						   &&  !IsWindow(  pRule->messenger.hTalkerShadow  )  
						   )
					   {
						   if  (  registerSubWnd(  pMsg->hShadow,  0,  0,  0,  &pMsg->idInfo,  0,  0,  &m_var.subWnds,  NULL  )  )  goto  errLabel;

						   //
						   pRule->messenger.hTalkerShadow  =  pMsg->hShadow;
						   
						   //
						   RECT	rc;
						   rc.left  =  pZone->iX;
						   rc.right  =  pZone->iX  +  pZone->iW;
						   rc.top  =  pZone->iY;
						   rc.bottom  =  pZone->iY  +  pZone->iH;

						   HWND	hCtrl  =  m_hWnd;
						   if  (  pSubWall->idc  )  hCtrl  =  ::GetDlgItem(  m_hWnd,  pSubWall->idc  );
						   ::MapWindowPoints(  hCtrl,  NULL,  (  LPPOINT  )&rc,  2  );

						   int  iX,  iY,  iW,  iH;
						   iX  =  rc.left;
						   iY  =  rc.top;
						   iW  =  rc.right  -  rc.left;
						   iH  =  rc.bottom  -  rc.top;

						   //
						   ::SetWindowPos(  pRule->messenger.hTalkerShadow,  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  |  SWP_SHOWWINDOW  );						   

						   //
						   break;			
					   }	
				  }	


				  }
				  break;
			case  CONST_misMsgType_input:  {
				  MIS_MSGU  *  pMsg  =  (  MIS_MSGU  *  )lParam;
				  IM_CONTENTU			*	pContent	=	M_getMsgContent(  pMsg->input.ucFlg,  &pMsg->input.data  );									 
					
				  switch  (  pContent->uiType  )  {
					      case  CONST_imCommType_imGrp:  {
							    int  i  =  0;
								//
								ZONE_objs_info	*  pZoi  =	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  m_hWnd,  this->getWndContentType(  ),  0  );
								//
								if  (  pZoi->iBarType  ==  CONST_qyBarType_avRes  )  {
									if  (  IsWindow(  pZoi->hBar  )  )  {
										if  (  pContent->imGrpEx.usOp  ==  CONST_imOp_recv_applyForOrgReq  )  {
											avRes_proc_applyForOrgReq(  pZoi->hBar,  &pContent->imGrpEx,  &pMsg->input.data.route.idInfo_from  );
											break;
										}
										//
										refreshAvResGrpInfo(  pZoi->hBar,  &pContent->imGrpEx  );
									}
								}
								//
								}
								break;
						  default:
								  break;
				  }
				  //
				  }
				  break;

			default:
					break;
	}

	lRet  =  QY_RC_WMOK;

errLabel:

	return  lRet;
}


 LRESULT  CDlgDynBmps::OnQyPostComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	long				lRet			=		-1;


	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;

	switch  (  wParam  )  {
			case  CONST_qyWmParam_guiMsgArrive:  
				  //
				  #ifdef  __DEBUG__
						  traceLogA(  "dlgDynBmps: doWnd_guiMsgArrive"  );
				  #endif
				  //
				  doWnd_guiMsgArrive(  pProcInfo,  lParam,  this->m_hWnd,  TRUE,  m_var.pMsgBuf_doWnd_guiMsgArrive  );
				  break;
			case  CONST_qyWmParam_gps:  {
				  int  iWndContentType  =  getWndContentType(  );
				  int  iSubType  =  getWndContentSubtype(  );
				  if  (  iWndContentType  !=  CONST_qyWndContentType_vWall  )  goto  errLabel;
				  if  (  !isVwSubtype_gps(  iSubType  )  )  goto  errLabel;

				  DWORD	dwTickCnt  =  GetTickCount(  );
				  if  (  dwTickCnt  -  m_var.wallGpsMgr.dwTickCnt_lastRefreshed  <  2000  )  break;
				  m_var.wallGpsMgr.dwTickCnt_lastRefreshed  =  dwTickCnt;

				  //
				  int  i;
				  for  (  i  =  0;  i  <  mycountof(  m_var.wallGpsMgr.mems  );  i  ++  )  {
					   if  (  !m_var.wallGpsMgr.mems[i].hMem  )  break;
					   pFuncs->pf_talkerShadow_procGps(  pProcInfo,  m_var.wallGpsMgr.mems[i].hMem,  FALSE,  m_var.wallGpsMgr.mems[i].iIndex_shadow,  this->m_hWnd,  &m_var,  i  );
				  }

				  unsigned  short	usCnt;
				  usCnt  =  i;

				  #ifdef  __DEBUG__
						  traceLog(  _T(  "dlgDynBmps: gps %d. before bMoving"  ),  usCnt  );
				  #endif

				  if  (  !usCnt  )  {
					  //  没有需要移动的就退出
					  break;
				  }

				  {
					  CQySyncFlg	syncFlg;
					  if  (  syncFlg.sync(  &m_var.wallGpsMgr.bMoving  )  )  goto  errLabel;

					  HDWP			hDwp;

					  hDwp  =  M_BeginDeferWindowPos(  usCnt  );
					  if  (  hDwp  )  {		
				
						  //
						  for  (  i  =  0;  i  <  usCnt;  i  ++  )  {
							   WALL_gps_mgrMem  *  pMem  =  &m_var.wallGpsMgr.mems[i];

							   UINT	uFlags  =  pMem->uFlags;
							   if  (  !uFlags  )  uFlags  |=  SWP_NOMOVE  |  SWP_NOSIZE  |  SWP_NOACTIVATE  |  SWP_NOZORDER;
							   else  {
								     if  (  !pMem->iW  ||  !pMem->iH  )  uFlags  |=  SWP_NOSIZE; 									 
							   }

							   M_DeferWindowPos(  hDwp,  pMem->hMem,  NULL,  pMem->x,  pMem->y,  pMem->iW,  pMem->iH,  uFlags  );
						  }


						  //
						  M_EndDeferWindowPos(  hDwp  );
					  }
				  }

  				  #ifdef  __DEBUG__
						  traceLog(  _T(  "dlgDynBmps: after bMoving"  )  );
				  #endif


				  for  (  i  =  0;  i  <  mycountof(  m_var.wallGpsMgr.mems  );  i  ++  )  {
					   if  (  !m_var.wallGpsMgr.mems[i].hMem  )  break;
					   memset(  &m_var.wallGpsMgr.mems[i],  0,  sizeof(  m_var.wallGpsMgr.mems[i]  )  );
				  }

				  }
				  break;

#if  0
			case  CONST_qyWmParam_refreshRuleObjsPos:
				  refreshRuleObjsPos(  this  );
				  break;
#endif
			case  CONST_qyWmParam_confAccepted:  {
				  int  ii  =  0;

				  ZONE_objs_info	*  pZoi  =	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  m_hWnd,  this->getWndContentType(  ),  0  );
								//
								if  (  pZoi->iBarType  ==  CONST_qyBarType_avRes  )  {
									if  (  IsWindow(  pZoi->hBar  )  )  {
										refreshAvResConfAccepted(  pZoi->hBar  );
									}
								}
								

				  }
				  break;

			default:
					break;
	}
	
errLabel:

	return  lRet;
}



void CDlgDynBmps::OnDestroy()
{
	MC_VAR_isCli  *  pProcInfo	=  QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return;
	QY_MC		*	pQyMc		=	(  QY_MC  *  )pProcInfo->pQyMc;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	//  int				i,  j;
	SUB_V_WALL	*	pSubWall	=	NULL;
	
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;


	switch  (  this->getWndContentType(  )  )  {


			case  CONST_qyWndContentType_vWall:  {
				  if  (  !m_var.pWall  )  break;
				  
				  }
				  break;
			default:
					break;
	}							

	//  2012/05/08
	exitCapSubWnds(  &m_var.subWnds  );

	//  2015/05/09
	if  (  getWndContentSubtype(  )  ==  CONST_vwSubtype_qvcf  )  {
		SHARE_dyn_bmp  *  pShareDynBmp  =  m_var.vWall.pShareDynBmp_toPlayFile;
		//
		if  (  pShareDynBmp->var.ucbUsed_iIndex_sharedObj  )  {
			QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pShareDynBmp->var.iIndex_sharedObj  );
			askSharedObjToStop(  pProcInfo,  pSharedObj,  pQyMc->gui.hMainWnd,  _T(  "toShareDynBmp"  )  );
		}
	}				  
	MACRO_safeFree(  m_var.vWall.pShareDynBmp_toPlayFile  );

	//
	MACRO_safeFree(  m_var.pZoneParams  );							//  2017/09/21

	//
	MACRO_safeFree(  m_var.pMsgBuf_doWnd_guiMsgArrive  );			//  2009/12/08

	if  (  m_var.pWall  )  m_var.pWall->removeAllSubWalls(  );

	//
	//pFuncs->pf_CAP_STUFF_free(  m_var.pCapStuff1  );		//  2009/09/16

	//
	MACRO_safeFree(  m_var.pZoneObjs  );				//  2015/12/05
	MACRO_safeFree(  m_var.pZoneObjsInfo_talkers  );	//  2012/04/02

	//
	if  (  m_var.pWall  )  delete  m_var.pWall;
	
	CDlgDesktopsMon::OnDestroy();

	// TODO: Add your message handler code here
}



//  2015/08/30
#define		MAX_timeoutInS_dynBmp		10	//  20	//  15



 void  CDlgDynBmps::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	//  int					iErr				=	-1;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	if  (  !m_var.pMisCnt  )  return;
	MC_VAR_isCli		*	pProcInfo			=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return;
	QY_MC				*	pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	CDlgDesktopsMon		*	pBase				=	this;
	int						iWndContentType		=	getWndContentType(  );	
	SUB_V_WALL			*	pSubWall			=	NULL;
	
	if  (  !m_var.nElapseInMs  )  return;
	int					nTimes_vWall		=	15000  /  m_var.nElapseInMs;	//  30000  /  m_var.nElapseInMs;
	if  (  !nTimes_vWall  )  return;

	//  2017/01/10
	if  (  m_var.quickToRetrieveImg.ucbOn  )  {
		nTimes_vWall  =  1;
		//
		m_var.quickToRetrieveImg.iTries  --  ;
		if  (  m_var.quickToRetrieveImg.iTries  <=  0  )  {
			m_var.quickToRetrieveImg.ucbOn  =  FALSE;
		}
	}


	//
	unsigned  char			ucbNeedToChkRules	=	FALSE;
	if  (  m_var.ucbNeedToChkRules  )  {
		ucbNeedToChkRules  =  TRUE;
		m_var.ucbNeedToChkRules  =  FALSE;
	}

	if  (  !(  m_var.nCtrls  %  nTimes_vWall  )
		||  ucbNeedToChkRules  )  
	{
			DWORD			dwTickCnt			=					GetTickCount(  );
			int				i,  j,  k;
			QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

			for  (  i  =  0;  i  <  m_var.pWall->m_var.usCnt;  i  ++  )  {
				 pSubWall  =  m_var.pWall->getSubWall(  i  );
				 if  (  !pSubWall  )  continue;
				 for  (  j  =  0;  j  <  pSubWall->usCnt;  j  ++  )  {
					  for  (  k  =  0;  k  <  mycountof(  pSubWall->mems[j].images.mems  );  k  ++  )  {
						   CAP_IMAGE	*	pImg	=  &pSubWall->mems[j].images.mems[k];
						   if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;
  						   
						   //  is active
						   if  (  dwTickCnt  -  pImg->dwTickCnt_lastDrawing  <  MAX_timeoutInS_dynBmp  *  1000  )  continue;
						   
						   freeCapImageByTaskId(  this->m_hWnd,  (  int  )pSubWall->idc,  pImg->iTaskId,  &pSubWall->mems[j].images,  pSubWall->hWnd_dst  );

					  }
				 }
			}			
	}

	if  (  !m_var.ucbEditable  )  {

		if  (  iWndContentType  ==  CONST_qyWndContentType_vWall  )  {
			if  (  !(  m_var.nCtrls  %  nTimes_vWall  )  
				||  ucbNeedToChkRules  )  
			{

			    #ifdef  __DEBUG__
						traceLog(  _T(  "dlgDynBmp: start to chk vwRules"  )  );
				#endif

				//
				BOOL			bImgRestarted		=					FALSE;				
				int			i;

				//
				for  (  i  =  0;  i  <  m_var.pWall->m_var.usCnt;  i  ++  )  {
					 SUB_V_WALL	*	pSubWall	=	m_var.pWall->getSubWall(  i  );
					 COMMON_PARAM	commonParam;
					 MACRO_makeCommonParam3(  this->m_hWnd,  (  void  *  )i,  &bImgRestarted,  commonParam  );

					 if  (  qTraverse(  pSubWall->pRuleQ,  tmpHandler_chkVWallRule_dlgDynBmps,  0,  &commonParam  )  )  {
						 #ifdef  __DEBUG__
								 traceLog(  _T(  "dlgDynBmps: chkRules failed"  )  );
						 #endif
						 //
						 break;
					 }
				}	

				if  (  bImgRestarted  )  qmcApplyForChkingTasks_gui(  pQyMc  );				
	
				//
				#ifdef  __DEBUG__
						traceLog(  _T(  "dlgDynBmp: end chking vwRules"  )  );
				#endif
			}	
		}

		}
	else  {
		  if  (  m_var.ucbEditable  )  {
			  _sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_statusVWallEditRule  )  );
		  }
	}

	//  2012/04/22
	if  (  m_var.pWall  &&  m_var.pWall->getCurSubWall(  )  )  {
		TCHAR				tBuf[255];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s | CPU %d%%. IO: %d, %dkbps"  ),  m_var.tHint,  pProcInfo->status.cpu.iCpuUsage,  pProcInfo->status.netStat.ins.uiInSpeedInKbps,  pProcInfo->status.netStat.ins.uiOutSpeedInKbps  );
		SetDlgItemText(  m_var.pWall->getCurSubWall(  )->idcHint,  tBuf  );	
		
		//  2012/04/10
#ifndef  __APP_qyMc_touchscreen__
		int	iSubType  =  getWndContentSubtype(  );
		//  if  (  isVwSubType_global(  iSubType  )  )  
		{
			ZONE_objs_info  *  pDlgWallsVar  =  (  ZONE_objs_info  *  )m_var.pZoneObjsInfo_talkers;
			if  (  pDlgWallsVar  )  {
				if  (  pDlgWallsVar->hBar  )  {
					
						  //  ::SetDlgItemText(  pDlgWallsVar->hBar,  IDC_BUTTON_menu,  tBuf  );						
						  if  (  !qyBar_SetDlgItemText(  pDlgWallsVar->hBar,  pDlgWallsVar->iBarType,  tBuf  )  )  {
							  if  (  !IsWindow(  pDlgWallsVar->hBar  )  )  pDlgWallsVar->hBar  =  NULL;  
					
						  }			
				}					
			
			}
			
		}
#endif
	}

	//
	m_var.nCtrls   ++  ;

errLabel:
	return;
}



  int  tmpHandler_refreshRuleObjsPos(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int					iErr			=	-1;
	//  p0
	COMMON_PARAM	*	pCommonParam	=	(  COMMON_PARAM  *  )p1;
	VW_ruleU		*	pRuleElem		=	(  VW_ruleU  *  )p2;
	//
	CDlgDynBmps		*	pDlg			=	(  CDlgDynBmps  *  )pCommonParam->p0;
	int					subWallIndex	=	(  int  )pCommonParam->p1;
	BOOL			*	pbImgRestarted	=	(  BOOL  *  )pCommonParam->p2;
	//
	MC_VAR_isCli		*	pProcInfo	=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )pDlg->m_var.pMisCnt->pProcInfoParam;
	QY_MC			*	pQyMc			=	(  QY_MC  *  )pProcInfo->pQyMc;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	//
	DLG_dynBmps_var  *  pm_var  =  pDlg->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	SUB_V_WALL		*	pSubWall		=	m_var.pWall->getSubWall(  subWallIndex  );
	if  (  !pSubWall  )  return  -1;
	int					j,  k;
	int					i;

	int						iSubType			=	pDlg->getWndContentSubtype(  );

	
	if  (  pRuleElem->common.uiType  ==  CONST_vwRuleType_messenger  )  {		//  2012/04/22			  
			
		if  (  pRuleElem->messenger.hTalkerShadow  )  {
			if  (  !IsWindow(  pRuleElem->messenger.hTalkerShadow  )  )  pRuleElem->messenger.hTalkerShadow  =  NULL;
		}
		if  (  pRuleElem->messenger.hTalkerShadow  )  {
			switch  (  iSubType  )  {
					case  CONST_vwSubtype_gps:
					case  CONST_vwSubtype_globalGps:
						  pFuncs->pf_talkerShadow_procGps(  pProcInfo,  pRuleElem->messenger.hTalkerShadow,  TRUE,  0,  NULL,  NULL,  0  );
						  break;
					case  0:
					case  CONST_vwSubtype_confWall:  {
						  SUB_V_WALL	*	pSubWall	=	m_var.pWall->getCurSubWall(  );
						  if  (  !pSubWall  )  goto  errLabel;
						  for  (  i  =  0;  i  <  pSubWall->usCnt;  i  ++  )  {
							   if  (  pSubWall->mems[i].uiTranNo_spObj  ==  pRuleElem->messenger.uiTranNo_spObj  )  break;
						  }
						  if  (  i  ==  pSubWall->usCnt  )  goto  errLabel;
						  myZONE  *  pZone  =  &pSubWall->mems[i];

						  unsigned  int  uiTranNo_spObj  =  pRuleElem->messenger.uiTranNo_spObj;

						  
						   //
						   RECT	rc;
						   rc.left  =  pZone->iX;
						   rc.right  =  pZone->iX  +  pZone->iW;
						   rc.top  =  pZone->iY;
						   rc.bottom  =  pZone->iY  +  pZone->iH;

						   HWND	hCtrl  =  pDlg->m_hWnd;
						   if  (  pSubWall->idc  )  hCtrl  =  ::GetDlgItem(  pDlg->m_hWnd,  pSubWall->idc  );
						   ::MapWindowPoints(  hCtrl,  NULL,  (  LPPOINT  )&rc,  2  );

						   int  iX,  iY,  iW,  iH;
						   iX  =  rc.left;
						   iY  =  rc.top;
						   iW  =  rc.right  -  rc.left;
						   iH  =  rc.bottom  -  rc.top;

						   //
						   ::SetWindowPos(  pRuleElem->messenger.hTalkerShadow,  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  |  SWP_NOZORDER  );						   

						  }
						  break;
					default:
							#ifdef  __DEBUG__
								    traceLog(  _T(  "tmpHandler_refreshRuleObjsPos: unprocessed vwSubType %d"  ),  iSubType  );
							#endif
							break;
			}
		}
	}



	iErr  =  0;
errLabel:
	return  iErr;
 }




 int  refreshRuleObjsPos(  CDlgDynBmps  *  pDlg  )
{
	int						iErr				=	-1;

	DLG_dynBmps_var  *  pm_var  =  pDlg->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	int						iWndContentType		=	pDlg->getWndContentType(  );
	int						i;

	if  (  !m_var.bInited  )  return  -1;

	if  (  iWndContentType  !=  CONST_qyWndContentType_vWall  )  return  -1;
	if  (  !m_var.pWall  )  return  -1;

	for  (  i  =  0;  i  <  m_var.pWall->m_var.usCnt;  i  ++  )  {			
		 SUB_V_WALL	*	pSubWall	=	m_var.pWall->getSubWall(  i  );
		 COMMON_PARAM	commonParam;
		 MACRO_makeCommonParam3(  pDlg,  (  void  *  )i,  NULL,  commonParam  );

		 if  (  qTraverse(  pSubWall->pRuleQ,  tmpHandler_refreshRuleObjsPos,  0,  &commonParam  )  )  goto  errLabel;

	}				

	iErr  =  0;

errLabel:

	return  iErr;
}

void CDlgDynBmps::OnSize(UINT nType, int cx, int cy)
{
	CDlgDesktopsMon::OnSize(nType, cx, cy);
	
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	int						iWndContentType		=	getWndContentType(  );
	int						iSubType			=	getWndContentSubtype(  );

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;


	// TODO: Add your message handler code here
#if  0
	if  (  m_var.pWall  )  {
		SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )this->m_var.pWall->getCurSp(  );
		if  (  pSp  )  {

			SUB_V_WALL	*	pSubWall  =  m_var.pWall->getCurSubWall(  );
			if  (  pSubWall  )  {
				RECT	rc;
				if  (  !getPicRect(  pSubWall->idc,  &rc  )  )  {
					pSp->spWidth  =  rc.right  -  rc.left;
					pSp->spHeight  =  rc.bottom  -  rc.top;
				}
			}
		}
	}
#endif

	//  2011/10/16
	if  (  iWndContentType  ==  CONST_qyWndContentType_vWall  )  {	
		if  (  m_var.vWall.ucbVideoConference  )  {
			closeInstantAssistant(  m_var.vWall.hDlgTalk_mgr  );
		}

		//
		MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
		if  (  pProcInfo  )  {
			if  (  pProcInfo->g_hVWall  ==  m_hWnd  )  {
				layoutWalls(  pProcInfo->g_hVWall,  pProcInfo->iWndContentType_g_hVWall  );
				//
				}
			else  {
				  setWallsBarPos(  m_hWnd,  pFuncs->pf_getZoneObjsInfo(  pProcInfo,  m_hWnd,  this->getWndContentType(  ),  0  ),  NULL,  0  );
			}
			//  2012/04/25
			refreshRuleObjsPos(  this  );
			//  PostMessage(  CONST_qyWm_postComm,  CONST_qyWmParam_refreshRuleObjsPos,  0  );
		}
	}

	//
	Invalidate(  TRUE  );
	UpdateWindow(  );
}

void CDlgDynBmps::OnLButtonDown(UINT nFlags, CPoint dlgPoint)
{
	// TODO: Add your message handler code here and/or call default

	CDlgDesktopsMon::OnLButtonDown(nFlags, dlgPoint);

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	//
	if  (  m_var.bAvConsole  )  {
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(dlgPoint.x, dlgPoint.y));
		return;
	}



	//
	SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )m_var.pWall->getCurSp(  );
	if  (  pSp  )  {		
		POINT		point;

		point  =  dlgPoint;
		::MapWindowPoints(  this->m_hWnd,  m_var.pWall->getCurSubWall(  )->hWnd_subWall,  &point,  1  );

		#ifdef __DEBUG__
			   traceLogA( "MouseDown:mouse at (%d,%d)", point.x, point.y );
		#endif

	    if ( pSp->isCapturedForAnimation ) {
			KillTimer( SP_TIMER_ID );
			ReleaseCapture();
			pSp->isCapturedForAnimation = FALSE;
			spProcLButtonDown( pSp, NULL, nFlags );
			Invalidate( FALSE );
			UpdateWindow();
			return;
		}

		//  2014/09/03
		if  (  m_var.ucbEditable  )
		{
			
			//
			SP_RECT_COORD tmpPoint;
			tmpPoint.x = ( unsigned short )point.x;
			tmpPoint.y = ( unsigned short )point.y;

			SetCapture();
			pSp->isCaptured = TRUE;
	
			spProcLButtonDown( pSp, &tmpPoint, nFlags );

			Invalidate( FALSE );
			UpdateWindow();

			return;
		}

		//  2018/07/03
		CPoint posBefore,posAfter;//!判断是否为拖动选择文本
		::GetCursorPos( &posBefore );//!点击时鼠标位置
		Sleep(250);
		MSG msg;
		::PeekMessage(
			&msg,
			GetSafeHwnd(),
			WM_LBUTTONUP,
			WM_LBUTTONUP,
			PM_NOREMOVE
			);
		::GetCursorPos( &posAfter );//!判断时鼠标位置
		//随意点击而已或选择文本(鼠标位置改变),返回
		if( msg.message==WM_LBUTTONUP  )//增加判断
		{
			return;
		}
		//
		//  HTREEITEM tree = HitTest(point);
		//HTREEITEM tree = GetSelectedItem();	
		CString sContens = _T(  "Hello, nihao"  );
		//  GetItemText(tree);	
		//SelectItem(tree);

		//	
		int  lenInBytes  =  (  sContens.GetLength(  )  +  1  )  *  sizeof(  TCHAR  );
		HGLOBAL hData = GlobalAlloc(GHND|GMEM_SHARE, lenInBytes );	
		char *pS = (char *)GlobalLock( hData );	
		memcpy( pS, (LPCTSTR)sContens, lenInBytes );	
		GlobalUnlock( hData );

		//
		m_bDraging = TRUE;	//开始拖动
		{
		COleDataSource source;
		source.CacheGlobalData( CF_TEXT, hData );
		source.DoDragDrop( DROPEFFECT_COPY );
		}
		GlobalFree( hData );
		m_bDraging = FALSE;	//完成拖动


	}

}

void CDlgDynBmps::OnLButtonUp(UINT nFlags, CPoint dlgPoint)
{
	// TODO: Add your message handler code here and/or call default

	CDlgDesktopsMon::OnLButtonUp(nFlags, dlgPoint);

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;


	SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )m_var.pWall->getCurSp(  );
	if  (  pSp  )  {
		POINT		point;

		point  =  dlgPoint;
		::MapWindowPoints(  this->m_hWnd,  m_var.pWall->getCurSubWall(  )->hWnd_subWall,  &point,  1  );

		#ifdef __SP_DEBUG__
			   traceLogA( "MouseUp:mouse at (%d,%d)", point.x, point.y );
		#endif

	    if ( pSp->isCaptured == FALSE ) return;
		ReleaseCapture();
		pSp->isCaptured = FALSE;

		SP_RECT_COORD tmpPoint;
		tmpPoint.x = ( unsigned short )point.x;
		tmpPoint.y = ( unsigned short )point.y;

		spProcLButtonUp( pSp, &tmpPoint, nFlags );

		Invalidate( FALSE );
		UpdateWindow();


		//  if  (  !isQEmpty(  pSp->pSelectedSpObjQ  )  )  
		{		//  Not finished: need to judge whether rectangle is modified. 2009/10/02
			this->refreshWallBySp(  m_var.pWall->m_var.curSpIndex  );
		}

	}

}

void CDlgDynBmps::OnLButtonDblClk(UINT nFlags, CPoint dlgPoint)
{
	// TODO: Add your message handler code here and/or call default
	int					iErr			=	-1;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	int					iWndContentType	=	this->getWndContentType(  );
	POINT				point;
	unsigned  int		uiTranNo_spObj	=	0;
	Q_NODE			*	pQNode			=	NULL;
	SUB_V_WALL		*	pSubWall		=	m_var.pWall->getCurSubWall(  );

	//  2017/06/14
	if  (  m_var.bAvConsole  )  {

		::PostMessage(  m_hWnd,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );
		return;
	}


	//
	point  =  dlgPoint;
	::MapWindowPoints(  this->m_hWnd,  m_var.pWall->getCurSubWall(  )->hWnd_subWall,  &point,  1  );

	traceLogA(  "dblClk: %d,%d",  point.x,  point.y  );

	if  (  iWndContentType  ==  CONST_qyWndContentType_vWall  )  {
		//  RECT			rc;
		int				i;
		int				j;

		if  (  m_var.vWall.uiObjType  )  {	//  2011/01/31
			iErr  =  0;  goto  errLabel;
		}

		//  2015/05/24
		if  (  getWndContentSubtype(  )  ==  CONST_vwSubtype_qvcf  )  {
			iErr  =  0;  goto  errLabel;
		}


		//
		for  (  i  =  0;  i  <  pSubWall->usCnt;  i  ++  )  {
			 myZONE		*	pZone  =  &pSubWall->mems[i];
			 for  (  j  =  0;  j  <  mycountof(  pZone->images.mems  );  j  ++  )  {
				  CAP_IMAGE	*	pImg	=	&pZone->images.mems[j];
				  if  (  pImg->iX_dst  <=  point.x  &&  pImg->iX_dst  +  pImg->iW_dst  >=  point.x
					  &&  pImg->iY_dst  <=  point.y  &&  pImg->iY_dst  +  pImg->iH_dst  >=  point.y  )
				  {
					  unsigned  short			usCnt_monPics_row	=		1;
					  unsigned  short			usCnt_monPics_col	=		1;
					  unsigned  int				uiInitW				=		640;
					  unsigned  int				uiInitH				=		480;
					  BOOL						bScrollBarEnabled	=		TRUE;
					  BOOL						bVideoConference	=		FALSE;
					  BOOL						bRemoteAssist		=		FALSE;

					  //  2012/04/07
#if  0
					  if  (  !pProcInfo->cfg.policy.ucbScrollForEnlagedImg  )  {
						  bScrollBarEnabled  =  FALSE;
					  }
#endif
					  //  2015/11/10
					  if  (  !pImg->ucbUnresizable_srcInfo  )  {
						  bScrollBarEnabled  =  FALSE;
					  }

					  //  2018/12/27
					  bScrollBarEnabled  =  FALSE;

					  //
					  uiInitW  =  pImg->iW_org;
					  uiInitH  =  pImg->iH_org;

					  PARAM_dlgVideos	params  =  {0};
					  //
					  params.iTaskId  =  pImg->iTaskId;
					  params.pImgs  =  &pZone->images;
					  params.iIndex_capImage  =  j;
					  params.usCnt_monPics_row  =  usCnt_monPics_row;
					  params.usCnt_monPics_col  =  usCnt_monPics_col;
					  params.uiInitW  =  uiInitW;
					  params.uiInitH  =  uiInitH;
					  params.bScrollBarEnabled  =  bScrollBarEnabled;
					  params.bVideoConference  =  bVideoConference;
					  params.bRemoteAssist  =  bRemoteAssist;
					  params.bEnlageFromDynBmps  =  TRUE;		//  2018/07/07
	
					  //  2012/05/27
					  //params.hParent  =  m_hWnd;

					  showEnlargedWnd(  m_hWnd,  this->m_hWnd,  FALSE,  &params,  &m_var.pMisCnt->subWnds  );

					  iErr  =  0;  goto  errLabel;
				  }
			 }
		}

	}

errLabel:
	CDlgDesktopsMon::OnLButtonDblClk(nFlags, point);
}


void CDlgDynBmps::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDlgDesktopsMon::OnPaint() for painting messages

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

#if  0
	SUB_V_WALL	*	pSubWall	=	m_var.pWall->getCurSubWall(  );
	if  (  !pSubWall->idc  )  {
		drawSubWall(  &dc,  m_var.pWall->m_var.curSpIndex  );
	}
#endif
	//
	drawSubWall(  m_var.pWall->m_var.curSpIndex,  m_hWnd,  dc.m_hDC  );

		
	#ifdef  __DEBUG__
			//  SetDlgItemText(  IDC_STATIC30,  _T(  "kk"  )  );

	traceLogA(  "dlgDynBmps: OnPaint"  );

	#endif

}


//
int  mapSpPoint(  SUB_V_WALL  *  pSubWall,  POINT  pt_subwall,  POINT  *  pPt_sp  )
{
	SP_STRUCT  *  pSp  =  (  SP_STRUCT  *  )pSubWall->pSp;
	int  x,  y;

	//
	if  (  !pSubWall->iW_image    ||  !pSubWall->iH_image  )  {
		return  -1;
	}

	//
	x  =  pt_subwall.x  -  pSubWall->iX_image;
	y  =  pt_subwall.y  -  pSubWall->iY_image;
	//
	pPt_sp->x  =  (  float  )x  /  pSubWall->iW_image  *  pSp->spWidth;
	pPt_sp->y  =  (  float  )y  /  pSubWall->iH_image  *  pSp->spHeight;

	return  0;
}

//
void CDlgDynBmps::OnMouseMove(UINT nFlags, CPoint dlgPoint)
{
	// TODO: Add your message handler code here and/or call default

	CDlgDesktopsMon::OnMouseMove(nFlags, dlgPoint);

	//
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

		DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;


	int						iWndContentType		=	getWndContentType(  );

	SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )m_var.pWall->getCurSp(  );
	if  (  pSp  )  {
		POINT		point;

		point  =  dlgPoint;
		::MapWindowPoints(  this->m_hWnd,  m_var.pWall->getCurSubWall(  )->hWnd_subWall,  &point,  1  );

		//  2012/04/24					  
		if  (  m_var.pWall->m_var.hWnd_spToolbox  )  {
			TCHAR	tBuf[128];
			//
			POINT  pt_sp;
			mapSpPoint(  m_var.pWall->getCurSubWall(  ),  point,  &pt_sp  );
			//
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d,%d. (%d,%d  on wall %d,%d)"  ),  point.x,  point.y,  pt_sp.x,  pt_sp.y,  pSp->spWidth,  pSp->spHeight  );
			if  (  !::SetDlgItemText(  m_var.pWall->m_var.hWnd_spToolbox,  IDC_STATIC_hint,  tBuf  )  )  {
				if  (  !IsWindow(  m_var.pWall->m_var.hWnd_spToolbox  )  )  m_var.pWall->m_var.hWnd_spToolbox  =  NULL;
			}				
		}


		//
		if  (  pSp->isCaptured  )  {

			if  (  nFlags  &  MK_LBUTTON  )  {

				#ifdef __SP_DEBUG__
					   traceLogA( "MouseLButtonDownMove:mouse at (%d,%d)", point.x, point.y );
				#endif

				SP_RECT_COORD tmpPoint;

				tmpPoint.x = ( unsigned short )point.x;
				tmpPoint.y = ( unsigned short )point.y;

				spProcMouseMove( pSp, &tmpPoint, nFlags );

#if  10
				Invalidate( FALSE );
				UpdateWindow();
#endif
#if  0
				SUB_V_WALL	*	pSubWall  =  m_var.pWall->getCurSubWall(  );
				if  (  pSubWall  )  {
					::InvalidateRect(  pSubWall->hWnd_subWall,  NULL,  FALSE  );
					::UpdateWindow(  pSubWall->hWnd_subWall  );
				}
#endif

				if  (  !isQEmpty(  pSp->pSelectedSpObjQ  )  )  {		//  Not finished: need to judge whether rectangle is modified. 2009/10/02
					this->refreshWallBySp(  m_var.pWall->m_var.curSpIndex  );
				}

				}
			else {
				
			}		
		}

	}

	//  2010/08/30
	if  (  iWndContentType  ==  CONST_qyWndContentType_vWall  
		&&  !m_var.ucbNoBar  )  
	{	
		MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
		if  (  !pProcInfo  )  goto  errLabel;

		//
		POINT	point;
		point.x  =  dlgPoint.x;
		point.y  =  dlgPoint.y;
		::MapWindowPoints(  this->m_hWnd,  NULL,  &point,  1  );

		//
		if  (  m_var.vWall.ucbVideoConference  )  {
			viewInstantAssistant(  this->m_hWnd,  0,  point.x,  point.y,  m_var.vWall.hDlgTalk_mgr,  FALSE  );
		}

		//


		//  2012/04/06
		if  (  pProcInfo->g_hVWall  ==  m_hWnd  )  {

			#ifdef __DEBUG__
				   //  traceLogA( "MouseMovee:mouse at (%d,%d)", dlgPoint.x, dlgPoint.y );
			#endif

			ZONE_PARAM	zoneParam;
			VW_ruleU	rule;
			if  (  !this->getZoneInfo(  dlgPoint,  &zoneParam,  &rule  )  )  {
				SUB_V_WALL  *	pSubWall	=  NULL;
				myZONE		*	pZone		=	NULL;

				pSubWall  =  m_var.pWall->getSubWall(  zoneParam.index_subWall  );
				if  (  pSubWall  )  {
					if  (  zoneParam.index_zone  >=  0  &&  zoneParam.index_zone  <  pSubWall->usCnt  )  {
						pZone	=	&pSubWall->mems[zoneParam.index_zone];
					}
				}

				if  (  pZone  )  {

					#ifdef  __DEBUG__
							//  traceLog(  _T(  "mouseMove: zone, x %d, y %d, w %d, h %d"  ),  pZone->iX,  pZone->iY,  pZone->iW,  pZone->iH  );
					#endif


					RECT	rc;
					rc.left  =  pZone->iX;
					rc.top  =  pZone->iY;
					rc.right  =  pZone->iX  +  pZone->iW;
					rc.bottom  =  pZone->iY  +  pZone->iH;
					::MapWindowPoints(  pSubWall->hWnd_subWall,  NULL,  (  LPPOINT  )&rc,  2  );
					
					viewWallsMenu(  point.x,  point.y,  m_hWnd,  this->getWndContentType(  ),  FALSE,  &rc,  &rule  );
				}
			}

		}


		//  2018/06/23
		//viewWallsBar(  m_hWnd,  getWndContentType(  ),  point.x,  point.y,  m_hWnd,  pFuncs->pf_getZoneObjsInfo(  pProcInfo,  m_hWnd,  this->getWndContentType(  ),  0  ),  FALSE  );
		// 2018/06/22
		if  (  1  )  {
			//  2018/10/28
			if  (  !IsWindow(  pProcInfo->hWall_hzj  )  )  {
				pProcInfo->hWall_hzj  =  m_hWnd;
			}
			//
			RECT  rc;
			GetClientRect(  &rc  );
			int  iW  =  rc.right  -  rc.left;
			int  iH  =  rc.bottom  -  rc.top;
			int  iW_bar  =  iW  *  CONST_fw_bar;
			//
			if  (  dlgPoint.x  >  iW  -  iW_bar  
				&&  dlgPoint.x  <  iW  -  CONST_dynBmps_space_skip
				&&  dlgPoint.y  <  iH  -  CONST_dynBmps_space_skip
				&&  dlgPoint.y  >  CONST_dynBmps_space_skip  )  
			{
				//			
				viewDlgAvRes(  m_hWnd,  getWndContentType(  ),  point.x,  point.y,  m_hWnd,  pFuncs->pf_getZoneObjsInfo(  pProcInfo,  m_hWnd,  this->getWndContentType(  ),  0  ),  FALSE  );
			}
			else  {
				  ZONE_objs_info	*  pZoi  =	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  m_hWnd,  this->getWndContentType(  ),  0  );

				  if  (  IsWindow(  pZoi->hBar  )  )  {
					  hideDlgAvRes(  pZoi->hBar  );
				  }
			}
		}

	}

errLabel:
	return;
}


 int  tmpHandler_bSameRule(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int					iErr			=	-1;
	COMMON_PARAM	*	pCommonParam	=	(  COMMON_PARAM  *  )p0;
	VW_ruleU		*	pRule			=	(  VW_ruleU  *  )p1;
	VW_ruleU		*	pRuleElem		=	(  VW_ruleU  *  )p2;

	CDlgDynBmps		*	pDlg			=	(  CDlgDynBmps  *  )pCommonParam->p0;
	SUB_V_WALL		*	pSubWall		=	(  SUB_V_WALL  *  )pCommonParam->p1;
	//  pCommonParam->p2;


	if  (  pRule->common.uiTranNo_spObj  ==  pRuleElem->common.uiTranNo_spObj  )  {
		iErr  =  1;  goto  errLabel;
	}
	if  (  pRule->common.uiType  ==  pRuleElem->common.uiType  )  {
		switch  (  pRule->common.uiType  )  {
				case  CONST_vwRuleType_dynBmp:
					  if  (  pRule->dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id  ==  pRuleElem->dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id					
						  &&  pRule->dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType  ==  pRuleElem->dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType
						  &&  pRule->dynBmp.ruleDynBmp.dynBmp.resObj.usIndex_obj  ==  pRuleElem->dynBmp.ruleDynBmp.dynBmp.resObj.usIndex_obj  )						
					  {
						  iErr  =  1;  goto  errLabel;
					  }
					  break;
				case  CONST_vwRuleType_conference_imGrpMem:	//  2011/10/25
					  if  (  pRule->conference_imGrpMem.idInfo.ui64Id  ==  pRuleElem->conference_imGrpMem.idInfo.ui64Id  )  {
						  iErr  =  1;  goto  errLabel;
					  }
					  break;
				default:
					    traceLogA(  "tmpHandler_bSameRule: unknown ruleType %d",  pRule->common.uiType  );
						break;
		}
	}

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
	}
	return  iErr;
}

  int  getMenuStatus_vw(  QY_MC  *  pQyMc,  void  *  p0,  void  *  p1,  void  *  piStatusParam  )
{
	 int						iErr		=	-1;
	 CDlgDynBmps		*		pDlg		=	(  CDlgDynBmps  *  )p0;
	 int						iMenuId		=	(  int  )p1;
	 int				*		piStatus	=	(  int  *  )piStatusParam;

	 if  (  !pQyMc  )  return  -1;
	 if  (  !piStatus  )  return  -1;

 	DLG_dynBmps_var  *  pm_var  =  pDlg->get_pm_var(  );
	if  (  !pm_var  )  return  -1;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	 if  (  !m_var.ucbEditable  )  {
		 switch  (  iMenuId  )  {
				 case  ID_qySetBackground:
				 default:
					    *piStatus  =  -1;
						break;
		 }
		 goto  errLabel;
	 }

	 int  iType  =  pDlg->getWndContentType(  );
	 int  iSubType  =  pDlg->getWndContentSubtype(  );
	 if  (  iType  ==  CONST_qyWndContentType_vWall  )  {

		 //
		 if  (  !bSupported_vwRuleType_messenger(  pQyMc  )  )  {
			 switch  (  iMenuId  )  {								
					 case  ID_selectMessenger:					
#if  0
					 case  ID_ucbNotViewScreen:
					 case  ID_ucbViewScreen:
					 case  ID_ucbNotViewWebcam0:
					 case  ID_ucbViewWebcam0:
					 case  ID_ucbNotViewWebcam1:
					 case  ID_ucbViewWebcam1:
					 case  ID_ucbNotViewWebcam2:
					 case  ID_ucbViewWebcam2:
#endif
						   goto  errLabel;						
					 default:										
							break;							
			 }						
		 }

		 //
		 if  (  m_var.rule_sel.common.uiType  ==  CONST_vwRuleType_talkers  )  *piStatus  =  -1;

		 //
		 switch  (  iMenuId  )  {
				 case  ID_selectMessenger:				
					   break;								
					   //							 
					   //
				 default:
						break;		 
					   
		 }

		 //
		 switch  (  iSubType  )  {
				 case  CONST_vwSubtype_gps:  					   
				 case  CONST_vwSubtype_globalGps:
					   switch  (  iMenuId  )  {
							   case  ID_qyCusName:
							   case  ID_qySetBackground:
							   case  ID_qyResetBackground:
								     break;

							   case  ID_qySetDynBmp:
							   case  ID_setMessengerBmp:
							   case  ID_qySetImGrpMemBmp:
								     *piStatus  =  -1;
								     break;
							   case  ID_selectMessenger:
								     break;
									 //
									 //
							   default:
									   break;		 
					   }
					   break;
				 case  CONST_vwSubtype_confWall:
					   switch  (  iMenuId  )  {
								case  ID_selectMessenger:
									  break;
								default:
										break;
					   }
					   break;
				 default:
					    switch  (  iMenuId  )  {
								case  ID_qySetDynBmp:
								case  ID_setMessengerBmp:
									  break;
								case  ID_qySetImGrpMemBmp:
									  if  (  !m_var.vWall.ucbVideoConference  )  {
										  *piStatus  =  -1;
									  }									  
									  break;
									  				
							   case  ID_selectMessenger:
								     *piStatus  =  -1;
								     break;
									 //

								default:
										break;
						}
						break;
		 }
		 //
		 }
	 else  {  
		   *piStatus  =  -1;
	 }



	 iErr  =  0;
errLabel:
	 return  iErr;
}

  VW_ruleU  *  findRuleBySth(  CDlgDynBmps  *  pDlg,  unsigned  int  uiTranNo_spObj  )
{
	int				iErr	=	-1;
	int				iWndContentType	=	pDlg->getWndContentType(  );
	if  (  iWndContentType  !=  CONST_qyWndContentType_vWall  )  return  NULL;
	
	VW_ruleU	*	pRule	=	NULL;
	Q_NODE		*	pQNode;
	BOOL			bFound  =  FALSE;

	DLG_dynBmps_var  *  pm_var  =  pDlg->get_pm_var(  );
	if  (  !pm_var  )  return  NULL;
	DLG_dynBmps_var  &m_var  =  *pm_var;


	SUB_V_WALL	*	pSubWall  =  m_var.pWall->getCurSubWall(  );
	
	for  (  pQNode  =  pSubWall->pRuleQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf;  pQNode  =  pQNode->pNext  )  {
		 pRule	=	(  VW_ruleU  *  )pQNode->qElemMemory.m_pBuf;

		 if  (  uiTranNo_spObj  ==  pRule->common.uiTranNo_spObj  )  {
			 bFound  =  TRUE;  break;
		 }
	}

	if  (  !bFound  )  goto  errLabel;

	iErr  =  0;
	
errLabel:

	return  iErr  ?  NULL  :  pRule;
  }


 //
void CDlgDynBmps::OnContextMenu(CWnd* pWnd, CPoint screenPoint  )
{
	// TODO: Add your message handler code here
	CMenu				tmpMenu;
	CMenu			*	tmppPopupMenu		=		NULL;
	//
	int					nPos				=		0;					//  2006/12/31
	//
	QY_MC			*	pQyMc				=		QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
		FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	QY_DMITEM		*	pItem;
	//
	unsigned  int		uCmd				=		0;
	int					iWndContentType		=		getWndContentType(  );
	unsigned int		uiTranNo_spObj		=		0;

	//
	QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );
	if  (  !pResMem  )  return;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;


	//
	if  (  iWndContentType  ==  CONST_qyWndContentType_vWall  )  {
		SUB_V_WALL	*	pSubWall	=	m_var.pWall->getCurSubWall();
		if  (  !pSubWall  )  goto  errLabel;

		POINT				point;
		point  =  screenPoint;
		::MapWindowPoints(  NULL,  pSubWall->hWnd_subWall,  &point,  1  );
		#ifdef  __DEBUG__
				traceLogA(  "OnContextMenu: subWall: %d,%d",  point.x,  point.y  );
		#endif

		//
		SP_STRUCT	*	pSp		=	(  SP_STRUCT  *  )m_var.pWall->getCurSp(  );
		Q_NODE		*	pQNode;
		SP_OBJ		*	pSpObj	=	NULL;
		RECT			rc;
		
		if  (  !pSp  )  goto  errLabel;

		nPos  =  CONST_resId_popup_vWall;	
		memset(  &m_var.rule_sel,  0,  sizeof(  m_var.rule_sel  )  );

		for  (  pQNode  =  pSp->pSpObjQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf;  pQNode  =  pQNode->pNext  )  {
			 pSpObj  =  (  SP_OBJ  *  )pQNode->qElemMemory.m_pBuf;
			 if  (  pSpObj->type  !=  SP_RECTANGLE_TYPE  )  continue;
			 if  (  pSpObj->subType  !=  SP_GENERIC_RECTANGLE_TYPE  )  continue;
			 SP_RECTANGLE	*	pRectangle  =  (  SP_RECTANGLE  *  )pSpObj;
			 SP_POINT		*	pPoint0		=	(  SP_POINT  *  )pRectangle->pQNode_points[0]->qElemMemory.m_pBuf;
			 SP_POINT		*	pPoint2		=	(  SP_POINT  *  )pRectangle->pQNode_points[2]->qElemMemory.m_pBuf;

			 memset(  &rc,  0,  sizeof(  rc  )  );
			 rc.left  =  min(  pPoint0->point.rect.x,  pPoint2->point.rect.x  );
			 rc.top  =  min(  pPoint0->point.rect.y,  pPoint2->point.rect.y  );
			 rc.right  =  max(  pPoint0->point.rect.x,  pPoint2->point.rect.x  );
			 rc.bottom  =  max(  pPoint0->point.rect.y,  pPoint2->point.rect.y  );

			 if  (  point.x  >=  rc.left  &&  point.x  <=  rc.right
				 &&  point.y  >=  rc.top  &&  point.y  <=  rc.bottom  )  
			 {
				 uiTranNo_spObj  =  pSpObj->uiTranNo;
				 //
				 nPos  =  CONST_resId_popup_zone;
				 //
				 VW_ruleU  *  pRule  =  findRuleBySth(  this,  uiTranNo_spObj  );
				 if  (  pRule  )  memcpy(  &m_var.rule_sel,  pRule,  sizeof(  m_var.rule_sel  )  );
				 //
				 break;
			 }
			 
		}
	}

	if  (  !nPos  )  goto  errLabel;

	if  (  !(  tmpMenu.CreatePopupMenu(  )  )  )  goto  errLabel;
	if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_popupMenu  )  )  )  goto  errLabel;
	if  (  !(  pItem  =  qyGetDmItemByType(  pItem,  nPos,  sizeof(  QY_DMITEM  )  )  )  )  goto  errLabel;
	if  (	 makeDynaMenu(  &pQyMc->cusRes,  tmpMenu.m_hMenu,  (  QY_DMITEM  *  )pItem->pData,  getMenuStatus_vw,  pQyMc,  this  )  )  goto  errLabel;
	tmppPopupMenu  = &tmpMenu;

	if (tmppPopupMenu == NULL)  goto  errLabel;

	//  uCmd  =  ::TrackPopupMenu(  tmppPopupMenu->m_hMenu,  TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON  |  TPM_NONOTIFY,  screenPoint.x, screenPoint.y, 0,  this->m_hWnd, NULL);
	uCmd  =  ::TrackPopupMenuEx(  tmppPopupMenu->m_hMenu,  TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON  |  TPM_NONOTIFY,  screenPoint.x, screenPoint.y, this->m_hWnd, NULL);

	//
#ifdef  __DEBUG__
		traceLogA(  "uCmd %d",  uCmd  );
#endif

	//
	switch  (  iWndContentType  )  {
			case  CONST_qyWndContentType_vWall:
				  if  (  !uiTranNo_spObj  )  {
					  switch  (  uCmd  )  {
							  case  ID_qyCusName:  {
								#if  !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )  &&  !defined(  __isCli__  )
								    CDlgQnmSendHint	dlg(  this  );
									lstrcpyn(  dlg.m_var.staticHint,  _T(  "to customize name"  ),  mycountof(  dlg.m_var.staticHint  )  );
									if  (  dlg.DoModal(  )  !=  IDOK  )  break;								
									if  (  !dlg.m_var.hint[0]  )  break;

									lstrcpyn(  m_var.title,  dlg.m_var.hint,  mycountof(  m_var.title  )  );
									SetWindowText(  m_var.title  );
								#endif
									}
								    break;
							  case  ID_qySetBackground:  {
								    CQyString				pathCStr;
									qyBrowseForFile(  m_hWnd,  TRUE,  _T(  "bmp\0"  ),  OFN_FILEMUSTEXIST,  _T(  "QY Background Files(*.bmp)\0*.bmp\0\0"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectFilenameFormat  ),  NULL,  pQyMc,  pathCStr  );
									if  (  !pathCStr.GetLength(  )  )  break;

									if  (  m_var.pWall->setBitmap(  pathCStr.GetBuffer(  0  ),  m_var.pWall->m_var.curSpIndex  )  )  goto  errLabel;
									//  2012/05/14
									parseBgFileName(  this,  pathCStr  );

									//
									SUB_V_WALL	*	pSubWall	=	m_var.pWall->getCurSubWall(  );
									if  (  !pSubWall  )  goto  errLabel;

									this->SetPicRect(  pSubWall->iW_org,  pSubWall->iH_org,  TRUE  );
									this->doLayout(  );

									//
									Invalidate(  TRUE  );
									UpdateWindow(  );

									}
								    break;
							  case  ID_qyResetBackground:  {
								    m_var.pWall->resetBitmap(  m_var.pWall->m_var.curSpIndex  );
									//  2012/05/14
									parseBgFileName(  this,  NULL  );

									//
									SUB_V_WALL	*	pSubWall	=	m_var.pWall->getCurSubWall(  );
									if  (  !pSubWall  )  goto  errLabel;

									//
									Invalidate(  TRUE  );
									UpdateWindow(  );

								    }
								    break;
							  case  ID_setVWallResolution:
								    break;
							  default:
									  break;
					  }
					  break;
				  }

				  //  to process zone
				  switch  (  uCmd  )  {
						  case  ID_qySetDynBmp:  {
							#if  !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
								VW_rule_dynBmp	rule;

								memset(  &rule,  0,  sizeof(  rule  )  );
								rule.uiType  =  CONST_vwRuleType_dynBmp;

								/*
								#ifdef  __DEBUG__
										rule.dynBmp.idInfo.ui64Id  =  435;
										rule.dynBmp.uiObjType  =  CONST_objType_webcam;									
										rule.dynBmp.usIndex  =  0;
								#endif
								*/

								//
								DlgSelect_isCli_o_U  o_u;
								//
								if  (  showDlgSelect_isCli(  m_hWnd,  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  0,  CONST_objType_webcam,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectMessenger  ),  _T(  ""  ),  0,  &o_u  )  !=  IDOK  )  goto  errLabel;

								//
								rule.ruleDynBmp.dynBmp.idInfo.ui64Id  =  o_u.selectDynBmp.dynBmp.qisResObj.idInfo.ui64Id;
								rule.ruleDynBmp.dynBmp.resObj.uiObjType  =  o_u.selectDynBmp.dynBmp.qisResObj.resObj.uiObjType;
								rule.ruleDynBmp.dynBmp.resObj.usIndex_obj  =  o_u.selectDynBmp.dynBmp.qisResObj.resObj.usIndex_obj;
																
								rule.uiTranNo_spObj  =  uiTranNo_spObj;
								
								COMMON_PARAM	commonParam;
								MACRO_makeCommonParam3(  this,  m_var.pWall->getCurSubWall(  ),  0,  commonParam  );
								qRemoveMsg(  m_var.pWall->getCurSubWall(  )->pRuleQ,  tmpHandler_bSameRule,  &commonParam,  &rule  );

								//
								if  (  qPostMsg(  &rule,  sizeof(  rule  ),  m_var.pWall->getCurSubWall(  )->pRuleQ  )  )  goto  errLabel;

								//									
								this->refreshWallByRules(  m_var.pWall->m_var.curSpIndex  );

								//
								if  (  m_var.ucbShowRules  )  this->showRules(  m_var.pWall->m_var.curSpIndex  );
								
								qmcApplyForChkingTasks_gui(  pQyMc  );		//  2009/10/12			
							#endif
								}
							    break;
									
						  case  ID_setMessengerBmp:{		//  2011/11/19
							#if  !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
								VW_rule_dynBmp	rule;

								memset(  &rule,  0,  sizeof(  rule  )  );
								rule.uiType  =  CONST_vwRuleType_dynBmp;

								//									
								DlgSelect_isCli_o_U  o_u;

								if  (  showDlgSelect_remoteVideo(  m_hWnd,  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  0,  CONST_objType_messenger,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectMessenger  ),  _T(  ""  ),  &m_var.vWall.idInfo,  &o_u  )  !=  IDOK  )  goto  errLabel;

								//
								rule.ruleDynBmp.dynBmp.idInfo.ui64Id  =  o_u.selectDynBmp.dynBmp.qisResObj.idInfo.ui64Id;
								rule.ruleDynBmp.dynBmp.resObj.uiObjType  =  o_u.selectDynBmp.dynBmp.qisResObj.resObj.uiObjType;
								rule.ruleDynBmp.dynBmp.resObj.usIndex_obj  =  o_u.selectDynBmp.dynBmp.qisResObj.resObj.usIndex_obj;
								//  2014/08/03
								rule.ruleDynBmp.ucbSaveVideo  =  o_u.selectDynBmp.ucbSaveVideo;
								//
								rule.uiTranNo_spObj  =  uiTranNo_spObj;
								
								COMMON_PARAM	commonParam;
								MACRO_makeCommonParam3(  this,  m_var.pWall->getCurSubWall(  ),  0,  commonParam  );
								qRemoveMsg(  m_var.pWall->getCurSubWall(  )->pRuleQ,  tmpHandler_bSameRule,  &commonParam,  &rule  );

								//
								if  (  qPostMsg(  &rule,  sizeof(  rule  ),  m_var.pWall->getCurSubWall(  )->pRuleQ  )  )  goto  errLabel;
								
								//
								this->refreshWallByRules(  m_var.pWall->m_var.curSpIndex  );

								//
								if  (  m_var.ucbShowRules  )  this->showRules(  m_var.pWall->m_var.curSpIndex  );
								
								qmcApplyForChkingTasks_gui(  pQyMc  );		//  2009/10/12			
							#endif
								}
							    break;

						  case  ID_qySetImGrpMemBmp:  {
							#if  !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
								VW_rule_messenger	rule;

								memset(  &rule,  0,  sizeof(  rule  )  );
								rule.uiType  =  CONST_vwRuleType_conference_imGrpMem;
								
								//									
								DlgSelect_isCli_o_U  o_u;

								//
								if  (  showDlgSelect_isCli(  m_hWnd,  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  CONST_qyQueryType_imGrpMemList,  CONST_objType_messenger,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectMessenger  ),  _T(  ""  ),  &m_var.vWall.idInfo,  &o_u  )  !=  IDOK  )  goto  errLabel;

								rule.idInfo.ui64Id  =  o_u.selectMessenger.idInfo_selected.ui64Id;
								
								rule.uiTranNo_spObj  =  uiTranNo_spObj;
								
								COMMON_PARAM	commonParam;
								MACRO_makeCommonParam3(  this,  m_var.pWall->getCurSubWall(  ),  0,  commonParam  );
								qRemoveMsg(  m_var.pWall->getCurSubWall(  )->pRuleQ,  tmpHandler_bSameRule,  &commonParam,  &rule  );
								
								//
								if  (  qPostMsg(  &rule,  sizeof(  rule  ),  m_var.pWall->getCurSubWall(  )->pRuleQ  )  )  goto  errLabel;
								
								//
								this->refreshWallByRules(  m_var.pWall->m_var.curSpIndex  );

								//
								if  (  m_var.ucbShowRules  )  this->showRules(  m_var.pWall->m_var.curSpIndex  );
								
								qmcApplyForChkingTasks_gui(  pQyMc  );		//  2009/10/12			
							#endif
								}							    
							    break;
						  case  ID_selectMessenger:	{		//  2012/04/22
								#if  !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
								VW_rule_messenger	rule;

								memset(  &rule,  0,  sizeof(  rule  )  );
								rule.uiType  =  CONST_vwRuleType_messenger;

								DlgSelect_isCli_o_U  o_u;
								//
								if  (  showDlgSelect_isCli(  m_hWnd,  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  0,  CONST_objType_messenger,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectMessenger  ),  _T(  ""  ),  &m_var.vWall.idInfo,  &o_u  )  !=  IDOK  )  goto  errLabel;

								rule.idInfo.ui64Id  =  o_u.selectMessenger.idInfo_selected.ui64Id;
								//
								rule.uiTranNo_spObj  =  uiTranNo_spObj;
								
								//
								COMMON_PARAM	commonParam;
								MACRO_makeCommonParam3(  this,  m_var.pWall->getCurSubWall(  ),  0,  commonParam  );
								qRemoveMsg(  m_var.pWall->getCurSubWall(  )->pRuleQ,  tmpHandler_bSameRule,  &commonParam,  &rule  );

								//
								if  (  qPostMsg(  &rule,  sizeof(  rule  ),  m_var.pWall->getCurSubWall(  )->pRuleQ  )  )  goto  errLabel;

								//									
								this->refreshWallByRules(  m_var.pWall->m_var.curSpIndex  );

								//
								if  (  m_var.ucbShowRules  )  this->showRules(  m_var.pWall->m_var.curSpIndex  );
								
								qmcApplyForChkingTasks_gui(  pQyMc  );		//  2009/10/12			
							#endif

								}
							    break;

								//  2016/06/01
						  case  ID_setZone_walls:  {  
							    VW_ruleU	rule  =  {0};
								rule.common.uiType  =  CONST_vwRuleType_walls;
								
								rule.common.uiTranNo_spObj  =  uiTranNo_spObj;

								//
								//
								COMMON_PARAM	commonParam;
								MACRO_makeCommonParam3(  this,  m_var.pWall->getCurSubWall(  ),  0,  commonParam  );
								qRemoveMsg(  m_var.pWall->getCurSubWall(  )->pRuleQ,  tmpHandler_bSameRule,  &commonParam,  &rule  );

								//
								if  (  qPostMsg(  &rule,  sizeof(  rule  ),  m_var.pWall->getCurSubWall(  )->pRuleQ  )  )  goto  errLabel;

								//									
								this->refreshWallByRules(  m_var.pWall->m_var.curSpIndex  );

								//
								if  (  m_var.ucbShowRules  )  this->showRules(  m_var.pWall->m_var.curSpIndex  );
								
								}
							    break;

								//  2016/08/16
						  case  ID_setZone_container:  {
								#ifdef  __DEBUG__
										traceLog(  _T(  "setZone_container"  )  );
								#endif

								}
							    break;

								//
						  default:
								  #ifdef __DEBUG__
										 traceLog(  _T(  "dlgDynBmps.OnContextMenu: unprocessed cmd %d"  ),  uCmd  );
								  #endif
								  break;
				  }
				  break;
			default:
					break;
	}


errLabel:
	return;
}


void CDlgDynBmps::Onviewtoolbox()
{
	// TODO: Add your command handler code here
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	//DLG_dynBmps_var  &m_var  =  *pm_var;

	viewToolbox_sketchpad(  this->m_hWnd,  pm_var  );
}

void CDlgDynBmps::OnUpdateviewtoolbox(CCmdUI *pCmdUI)
{
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	// TODO: Add your command update UI handler code here
	if  (  !m_var.ucbEditable  )  pCmdUI->Enable(  FALSE  );
	if  (  IsWindow(  m_var.pWall->m_var.hWnd_spToolbox  )  )  pCmdUI->Enable(  FALSE  );

	//  2018/07/05
#ifdef  __DEBUG__
		pCmdUI->Enable(  TRUE  );
#endif
}


void CDlgDynBmps::Onstopediting()
{
	int					i;
	CDlgDesktopsMon	*	pBase  =  this;

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	// TODO: Add your command handler code here
	m_var.ucbEditable  =  FALSE;
	//m_var.ucbShowRules  =  FALSE;

	//  2013/03/01
	pBase->m_var.ucbHideStatic_idc  =  TRUE;
	pBase->m_var.ucbHideStatic_idcHint  =  TRUE;
	
	//
	this->Onstopscrollbar(  );

	//
	pBase->m_var.notOnOffScrollBar  =  FALSE;

	::SendMessage(  m_var.pWall->m_var.hWnd_spToolbox,  WM_CLOSE,  0,  0  );

	for  (  i  =  0;  i  <  m_var.pWall->m_var.usCnt;  i  ++  )  {
		 SUB_V_WALL	*	pSubWall  =  m_var.pWall->getSubWall(  i  );
		 //bHideSp(  (  SP_STRUCT  *  )pSubWall->pSp,  TRUE  );
		 bEditSp(  (  SP_STRUCT  *  )pSubWall->pSp,  FALSE  );	//  2018/07/05

		 //  2013/03/01
		 if  (  IsWindow(  pSubWall->hWnd_subWall  )  )  {
			 #ifdef  __DEBUG__
					 if  (  ::GetDlgItem(  m_hWnd,  pSubWall->idc  )  ==  pSubWall->hWnd_subWall  )  {
						 //  traceLog(  _T(  "kk,,,,,,,,,,,,,,,,,,,,,,,"  )  );
					 }
					 BOOL  bb  =  ::IsWindowVisible(  pSubWall->hWnd_subWall  );
					 traceLog(  _T(  "bb"  )  );
			 #endif
		 }
	}
	
	//
	if  (  m_var.pWall->getCurSubWall(  )->idcHint  )  {
		m_var.tHint[0]  =  0;
		SetDlgItemText(  m_var.pWall->getCurSubWall(  )->idcHint,  _T(  ""  )  );
	}

	//  Invalidate(  FALSE  );		 
	Invalidate(  TRUE  );
	UpdateWindow(  );	

	//  2012/04/29
	m_var.ucbNeedToChkRules  =  TRUE;

}

void CDlgDynBmps::OnUpdatestopediting(CCmdUI *pCmdUI)
{
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	// TODO: Add your command update UI handler code here
	if  (  !m_var.ucbEditable  )  pCmdUI->Enable(  FALSE  );
}

void CDlgDynBmps::Onstarttoedit()
{
	// TODO: Add your command handler code here

	//
	CDlgDesktopsMon	*	pBase  =  this;
	
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	//
	closeSubWnds(  &m_var.subWnds  );
	if  (  bExists_capSubWnd(  &m_var.subWnds  )  )  {
		 myMessageBox(  m_hWnd,  _T(  "dlgDynBmps:startToEdit failed, closeSubWnds failed"  ),  _T(  "www.qycx.com"  ),  MB_OK  );
		 goto  errLabel;
	}

	//
	closeWallMems(  m_hWnd,  this->getWndContentType(  )  );
	if  (  bExists_wallMem(  m_hWnd,  this->getWndContentType(  )  )  )  {
		 myMessageBox(  m_hWnd,  _T(  "dlgDynBmps:startToEdit failed, closeWallMems failed"  ),  _T(  "www.qycx.com"  ),  MB_OK  );
		 goto  errLabel;
	}

	//
	m_var.ucbEditable  =  TRUE;
	
	//
	pBase->m_var.ucbHideStatic_idc  =  TRUE;
	pBase->m_var.ucbHideStatic_idcHint  =  TRUE;

	//
	this->Onstartscrollbar(  );
	pBase->m_var.notOnOffScrollBar  =  TRUE;

	viewToolbox_sketchpad(  m_hWnd,  &m_var  );

	int			i;
	for  (  i  =  0;  i  <  m_var.pWall->m_var.usCnt;  i  ++  )  {
		 SUB_V_WALL	*	pSubWall  =  m_var.pWall->getSubWall(  i  );
		 //bHideSp(  (  SP_STRUCT  *  )pSubWall->pSp,  FALSE  );
		 bEditSp(  (  SP_STRUCT  *  )pSubWall->pSp,  TRUE  );	//  2018/07/05
	}

	//
	m_var.ucbShowRules  =  TRUE;

	//
	//  Invalidate(  FALSE  );		 
	Invalidate(  TRUE  );
	UpdateWindow(  );	

errLabel:
	return;

}

void CDlgDynBmps::OnUpdatestarttoedit(CCmdUI *pCmdUI)
{
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	// TODO: Add your command update UI handler code here
	if  (  m_var.ucbEditable  )  pCmdUI->Enable(  FALSE  );
}

void CDlgDynBmps::Onstopshowingrules()
{
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	// TODO: Add your command handler code here
	m_var.ucbShowRules  =  FALSE;

	//
	Invalidate(  FALSE  );
	UpdateWindow(  );
}

void CDlgDynBmps::OnUpdatestopshowingrules(CCmdUI *pCmdUI)
{
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	// TODO: Add your command update UI handler code here
	if  (  !m_var.ucbEditable  )  pCmdUI->Enable(  FALSE  );
	if  (  !m_var.ucbShowRules  )  pCmdUI->Enable(  FALSE  );
}

void CDlgDynBmps::Onstarttoshowrules()
{
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	// TODO: Add your command handler code here
	m_var.ucbShowRules  =  TRUE;
	
	//
	Invalidate(  FALSE  );
	UpdateWindow(  );

}

void CDlgDynBmps::OnUpdatestarttoshowrules(CCmdUI *pCmdUI)
{
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	// TODO: Add your command update UI handler code here
	if  (  !m_var.ucbEditable  )  pCmdUI->Enable(  FALSE  );
	if  (  m_var.ucbShowRules  )  pCmdUI->Enable(  FALSE  );
}

void CDlgDynBmps::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	// TODO: Add your message handler code here and/or call default
	if  (  nIDCtl  ==  IDC_STATIC_pic0  )  {
		//  CDC  *  pDc  =  CDC::FromHandle(  lpDrawItemStruct->hDC  );

				
		int  i;

#if  0
		for  (  i  =  0;  i  <  m_var.pWall->m_var.usCnt;  i  ++  )  {
			 SUB_V_WALL	*	pSubWall	=	m_var.pWall->getSubWall(  i  );
			 if  (  pSubWall->idc  ==  nIDCtl  )  {
				 //  drawSubWall(  pDc,  i  );
				 drawSubWall(  i,  m_hWnd, lpDrawItemStruct->hDC  ); 
				 break;
			 }
		}
#endif

		#ifdef  __DEBUG__
				if  (  i  <  m_var.pWall->m_var.usCnt  )  {
					SUB_V_WALL  *  pSubWall  =  m_var.pWall->getSubWall(  i  );
					BOOL  bb  =  ::IsWindowVisible(  pSubWall->hWnd_subWall  );
					traceLog(  _T(  "bb"  )  );
				}
	

				//
				traceLogA(  "dlgDynBmps.OnDrawItem"  );
		#endif


		return;
	}

	CDlgDesktopsMon::OnDrawItem(nIDCtl, lpDrawItemStruct);
}



void CDlgDynBmps::Onopen()
{
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	// TODO: Add your command handler code here
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	QY_IMEXPORTINFO	importInfo;
	memset(  &importInfo, 0,  sizeof(  importInfo  )  );
	CQyString  csPath;

	qyBrowseForFile(  m_hWnd,  TRUE,  _T(  "qvw\0"  ),  OFN_FILEMUSTEXIST,  _T(  "QY V-Wall Module(&.qvw)\0*.qvw\0\0"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectFilenameFormat  ),  NULL,  pQyMc,  csPath  );
	if  (  !csPath.GetLength(  )  )  return;

	//
	closeSubWnds(  &m_var.subWnds  );
	 if  (  bExists_capSubWnd(  &m_var.subWnds  )  )  {
		 myMessageBox(  m_hWnd,  _T(  "dlgDynBmps:open failed, closeSubWnds failed"  ),  _T(  "www.qycx.com"  ),  MB_OK  );
		 goto  errLabel;
	 }

	 //
	this->openFile(  csPath.GetBuffer(  0  )  );

errLabel:
	return;
}


void CDlgDynBmps::OnUpdateopen(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here

}

void CDlgDynBmps::Onsave()
{
	// TODO: Add your command handler code here
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
		FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	QY_IMEXPORTINFO	exportInfo;
	memset(  &exportInfo,  0,  sizeof(  exportInfo  )  );

	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;


	CQyString  csPath;

	qyBrowseForFile(  m_hWnd,  FALSE,  _T(  "qvw\0"  ),  NULL,  _T(  "QY V-Wall Module(&.qvw)\0*.qvw\0\0"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectFilenameFormat  ),  NULL,  pQyMc,  csPath  );
	if  (  !csPath.GetLength(  )  )  return;
	if  (  csPath.GetLength(  )  >= mycountof(  exportInfo.fileName  )  )  return;
	lstrcpyn(  (LPWSTR)&exportInfo.fileName,  csPath.GetBuffer(  0  ),  mycountof(  exportInfo.fileName  )  );

	CWaitCursor  cursor;

	lstrcpyn(  m_var.pWall->m_var.title,  m_var.title,  mycountof(  m_var.pWall->m_var.title  )  );
	if  (  !bQisExportVWall(  m_var.pWall,  &exportInfo  )  )  goto  errLabel;

	if  (  m_var.vWall.ucbVideoConference  )  {
		QY_REG				reg;
		TCHAR				tBuf[256];

		memset(  &reg,  0,  sizeof(  reg  )  );
		reg.hKeyRoot0  =  HKEY_CURRENT_USER;
		//  safeStrnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
		lstrcpyn(  reg.rootKey,  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u.vWall0"  ),  m_var.vWall.idInfo.ui64Id  );

		qySetRegCfgT(  reg.hKeyRoot0,  CString(  reg.rootKey  ),  tBuf,  exportInfo.fileName  );
	}

errLabel:
	return;
}

void CDlgDynBmps::OnUpdatesave(CCmdUI *pCmdUI)
{
	DLG_dynBmps_var  *  pm_var  =  this->get_pm_var(  );
	if  (  !pm_var  )  return;
	DLG_dynBmps_var  &m_var  =  *pm_var;

	// TODO: Add your command update UI handler code here
	SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )m_var.pWall->getCurSp( );
	if  (  !pSp  ||  isQEmpty(  pSp->pSpObjQ  )  )  pCmdUI->Enable(  FALSE  );

}



void CDlgDynBmps::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDlgDesktopsMon::OnMoving(fwSide, pRect);
	
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	// TODO: Add your message handler code here
	if  (  pProcInfo  )  {
		if  (  pProcInfo->g_hVWall  ==  m_hWnd  )  {
			layoutWalls(  m_hWnd,  this->getWndContentType(  )  );
			}
		else  {
			  setWallsBarPos(  m_hWnd,  pFuncs->pf_getZoneObjsInfo(  pProcInfo,  m_hWnd,  this->getWndContentType(  ),  0  ),  NULL,  0  );
		}

		//  2012/04/25
		refreshRuleObjsPos(  this  );
	}

}

void CDlgDynBmps::OnMove(int x, int y)
{
	CDlgDesktopsMon::OnMove(x, y);

	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	// TODO: Add your message handler code here
	if  (  pProcInfo  )  {
		if  (  pProcInfo->g_hVWall  ==  m_hWnd  )  {
			layoutWalls(  m_hWnd,  this->getWndContentType(  )  );
			}
		else  {
			  setWallsBarPos(  m_hWnd,  pFuncs->pf_getZoneObjsInfo(  pProcInfo,  m_hWnd,  this->getWndContentType(  ),  0  ),  NULL,  0  );
		}

		//  2012/04/25
		refreshRuleObjsPos(  this  );
		//  PostMessage(  CONST_qyWm_postComm,  CONST_qyWmParam_refreshRuleObjsPos,  0  );
	}

}



void CDlgDynBmps::OnIsCmd(  UINT iMenuId  )
{
	int					iErr		=	-1;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	
	//  2013/02/06
#if  0
	if  (  iMenuId  >=  ID_dlgTest_min  &&  iMenuId  <=  ID_dlgTest_max  )  {
		doCmd_test(  iMenuId  );
		iErr  =  0;  goto  errLabel;
	}
#endif
		 	
	//
	BOOL				bNeedProcess=	FALSE;

	//
	switch  (  iMenuId  )  {
						  //				  	
			case  ID_fullScreen:  {
				  CDlgDesktopsMon  *  pBase  =  this;
				  if  (  pBase->m_var.m_bFullScreen  )  this->endFullScreen(  );
				  else  this->Onfullscreen(  );
				  }
				  break;
			default:
				    bNeedProcess  =  TRUE;
					break;
	}

	if  (  !bNeedProcess  )  {
		iErr  =  0;  goto  errLabel;
	}

	//
	//  if  (  pProcInfo->g_hVWall  !=  m_hWnd  )  goto  errLabel;

	switch  (  iMenuId  )  {
			case  ID_showMenu_wallsBar:  {

				  HWND				hDlgWall		=	m_hWnd;

#ifdef  __DEBUG__

				  ZONE_objs_info	*	pDlgWallsVar	=	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  hDlgWall,  this->getWndContentType(  ),  0  );
				  if  (  !pDlgWallsVar  )  goto  errLabel;

#endif
				  showMenu_wallsBar(  NULL,  hDlgWall,  this->getWndContentType(  ),  0  );
				  }
				  break;
			case  ID_about:
				  dyn_myOnAppAbout(  pProcInfo,  m_hWnd  );
				  break;

			case  ID_selectContact:  {
				  DLG_guiDataParam_objs		param;
				  memset(  &param,  0,  sizeof(  param  )  );
				  param.uiType  =  CONST_objType_messenger;
				  if  (  !showDlgObjs(  pQyMc->g_hInst,  m_hWnd,  &param  )  )  {
					  //
					  HWND  hVWall  =  m_hWnd;
					  int  iWndContentType  =  getWndContentType(  );
					  pFuncs->pf_tryToTalkToMessenger_id(  param.o.ui64Id_selected,  TRUE,  hVWall,  iWndContentType,  NULL  );					 
				  }
				  }
				  break;
			case  ID_selectGroup:  {
				  DLG_guiDataParam_objs	param;
				  memset(  &param,  0,  sizeof(  param  )  );
				  param.uiType  =  CONST_objType_imGrp;
				  if  (  !showDlgObjs(  pQyMc->g_hInst,  m_hWnd,  &param  )  )  {
					  //  
					  HWND  hVWall  =  m_hWnd;
					  int  iWndContentType  =  getWndContentType(  );
					  pFuncs->pf_tryToTalkToMessenger_id(  param.o.ui64Id_selected,  TRUE,  hVWall,  iWndContentType,  NULL  );					
				  }
				  }
				  break;
			case  ID_selectRemoteVideo:  {			//  2013/02/11
				  //  bViewSharedDynBmpList_isClient(  getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );				
				  traceLog(  _T(  "not finished: select remote video"  )  );
				  }
				  break;
			case  ID_testLocalAv:
				  pFuncs->pf_testLocalAv(  m_hWnd  );
				  break;
			case  ID_policy:  {
#if  0
				  CDlgPolicyIsClient	dlg(  this  );				
				  dlg.DoModal(  );
#endif
				  showDlgPolicyIsClient(  m_hWnd  );
				  }
				  break;
			case  ID_conferenceQuality:  {
				#if  0
				  CDlgPolicyAv		dlg(  this  );
				  dlg.bSetDlgInfo(  CONST_capType_av,  0,  TRUE  );
				  if  (  dlg.DoModal(  )  ==  IDOK  )  
				#endif
				  if  (  showDlgPolicyAv(  m_hWnd,  CONST_capType_av,  0,  CONST_capUsage_conf  )  ==  IDOK  ){
				  }
				  }
				  break;
			case  ID_msg:  {
#if  0
				  CDlgMsgList	dlg(  this  );
				  dlg.DoModal(  );
#endif
				  showDlgMsgList(  m_hWnd,  NULL,  NULL  );
				  }
				  break;


			default:
					break;
	}

errLabel:
	return;
}


void CDlgDynBmps::OnUpdateIsCmd(CCmdUI *pCmdUI)
{
}


void CDlgDynBmps::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDlgDesktopsMon::OnWindowPosChanged(lpwndpos);
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	// TODO: Add your message handler code here
	if  (  pProcInfo->g_hVWall  ==  m_hWnd  )  {

		if  (  pFuncs->pf_bMainWndAbove(  pProcInfo->g_hVWall  )  )  {

			HWND	hWnd  =  pProcInfo->g_hVWall;					  			    
			::SetWindowPos(  hWnd,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOSIZE  |  SWP_NOMOVE  |  SWP_NOACTIVATE    );
			::SetWindowPos(  hWnd,  HWND_NOTOPMOST,  0,  0,  0,  0,  SWP_NOSIZE  |  SWP_NOMOVE  |  SWP_NOACTIVATE  );
				  
		}

	}
}

BOOL CDlgDynBmps::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
#ifdef  __DEBUG__
	traceLog(  _T(  "dlgDynBmps: OnEraseBkgns"  )  );
#endif

	if  (  !CDlgDesktopsMon::OnEraseBkgnd(pDC)  )  return  FALSE;

		
	//
	//  drawSubWall(  m_var.pWall->m_var.curSpIndex,  m_hWnd,  pDC->m_hDC  );

	
	return  TRUE;

}
HBRUSH CDlgDynBmps::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDlgDesktopsMon::OnCtlColor(pDC, pWnd, nCtlColor);
	CDlgDesktopsMon  *  pBase  =  this;

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired


	if  (  nCtlColor  ==  CTLCOLOR_STATIC  )  {
		int	idc  =  pWnd->GetDlgCtrlID(  );
		//
		//  2014/11/18
		//if  (  idc  >=  IDC_STATIC60  &&  idc  <=  IDC_STATIC99  )  
		{

	
			if  (  pBase->m_var.m_bFullScreen  )  {
				pDC->SetBkMode(  TRANSPARENT  );
				pDC->SetTextColor(  RGB(  255,  255,  255  )  );
				return  this->m_brush_desc_fullScreen;
			}

				pDC->SetBkMode(  TRANSPARENT  );
			
			return  this->m_brush_desc_normal;
		}

	}

	return hbr;
}
