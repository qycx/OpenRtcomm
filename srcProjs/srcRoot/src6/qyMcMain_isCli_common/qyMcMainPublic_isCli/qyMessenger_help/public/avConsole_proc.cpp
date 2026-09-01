


#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>






#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qySyncCommProc.h"
#include	"qmcVideoCapture_isCli.h"


//
#include	"isCliHelpPublic.h"


//  2015/01/01
#include	"extOpenCommon.h"

//  2015/03/25
#include	"meshLoaderPublic.h"

//
#include	"funcsForIsCliHelp.h"

//
#include	"avConsole_open.h"
#include	"qnmResDefs.h"

#include	"dynFuncs.h"

#include	"qmcDynBmp.h"
#include	"help_getDlgTalkVar.h"
#include	"dlgTalkProc.h"
#include	"isCliD3dPublic.h"
#include	"isCmdConst.h"

//
//__declspec(  dllexport  )  int  do_avConsole_req_isCliHelp(  AvConsole_req_head  *  pReqHead  );
//__declspec(  dllexport  )  int  do_avConsole_req_d3d(  AvConsole_req_head  *  pReq  );
//int  doAvConsole_cmd_retrieveUsrs(  AvConsole_req_retrieveUsrs  *  pReq  );
//__declspec(  dllexport  )  int  doAvConsole_cmd_retrieveDynBmps(  AvConsole_req_retrieveDynBmps  *  pReq  );




//
#if  0
__declspec(  dllexport  )  int  iido_avConsole_req(  AvConsole_req_head  *  pReqHead  )
{
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	//
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;
	//
	QY_OBJ_DB  *  pObjDb  =  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
	QY_MESSENGER_ID  idInfo  =  { 0 };	//  {104};
	unsigned  int  uiObjType  =  CONST_objType_webcam;
	unsigned  usIndex_obj  =  1;
	//
	TCHAR  tBuf[128];
	 
	
	//
	switch  (  pReqHead->usCmd  )  {
			case  CONST_avConsole_cmd_view:  	{
				  //
				  AvConsole_req_view  *  pReq  =  (  AvConsole_req_view  *  )pReqHead;
				  
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
				  param.bAvConsole  =  TRUE;
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
				  viewDynBmp(  hParent,  pObjDb,  _T(  ""  ),  &idInfo,  uiObjType,  usIndex_obj,  _T(  ""  ),  &param  );
				  }
				  break;
			case  CONST_avConsole_cmd_close:  {
				  AvConsole_req_close  *  pReq  =  (  AvConsole_req_close  *  )pReqHead;
				  //
				  idInfo.ui64Id  =  pReq->ui64Id;	
				  uiObjType  =  pReq->uiObjType;	
				  usIndex_obj  =  pReq->usIndex_obj;

				  QY_DMITEM  *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "close: %I64u, %s, %d. "  ),  idInfo.ui64Id,  qyGetDesByType1(  pTable,  uiObjType  ),  (  int  )usIndex_obj  );
				  showInfo_open0(  0,  _T(  "do_avConnsole_req"  ),  tBuf  );				
				  //
				  closeDynBmp(  NULL,  _T(  ""  ),  &idInfo,  uiObjType,  usIndex_obj  );
				  }
				  break;
			case  CONST_avConsole_cmd_closeAll:  {
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "closeAll. "  )  );
				  showInfo_open0(  0,  _T(  "do_avConnsole_req"  ),  tBuf  );				  
				  //
				  closeAllDynBmps(  NULL,  _T(  ""  )  );
				  }
				  break;
			case  CONST_avConsole_cmd_retrieveUsrs:
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "retrieveUsrs. "  )  );
				  showInfo_open0(  0,  _T(  "do_avConnsole_req"  ),  tBuf  );				  
				  //
				  doAvConsole_cmd_retrieveUsrs(  (  AvConsole_req_retrieveUsrs  *  )pReqHead  );
				  break;
			case  CONST_avConsole_cmd_retrieveDynBmps:
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "retrieveDynBmps. "  )  );
				  showInfo_open0(  0,  _T(  "do_avConnsole_req"  ),  tBuf  );				  
				  //
				  doAvConsole_cmd_retrieveDynBmps(  (  AvConsole_req_retrieveDynBmps  *  )pReqHead  );
				  
				  break;
			case  CONST_avConsole_cmd_move:
				  //
				  do_avConsole_req_isCliHelp(  pReqHead  );
				  
				  break;
			case  CONST_avConsole_cmd_avTalk:  {
				  //
				  AvConsole_req_avTalk  *  pReq  =  (  AvConsole_req_avTalk  *  )pReqHead;
				  //do_avConsole_av(  pReqHead  );
				  CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
				  CHelp_getDlgTalkVar  help_getDlgTalkVar;
				  
				  
				  HWND  hMgr  =  NULL;
				  //
				  pFuncs->pf_tryToTalkToMessenger_id(  pReq->ui64Id,  TRUE,  NULL,  0,  &hMgr  );

				  //
				  DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
				  if  (  !pMgrVar  )  goto  errLabel;
				  if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
				  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
				  //
				  int  i;
				  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
					  if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  break;
				  }
				  if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  goto  errLabel;
				  HWND  hCurTalk  =  pShadowMgr->shadows[i].hShadow;

				  //
				  DLG_TALK_var  *  pCurVar =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hCurTalk  );
				  if  (  !pCurVar  )  goto  errLabel;

				  if  (  IsWindow(  pCurVar->msgTool.hWnd_msgTool  )  ) 
				  {
					  SendMessageTimeout(  pCurVar->msgTool.hWnd_msgTool,  WM_CLOSE,  0,  0,   0,  1000,  NULL  ); 
					
				  }

				  //
				  makeWndNoBorder(  hCurTalk,  FALSE,  NULL,  NULL  );


				  //
				  HWND  hParent  =  NULL;
				  if  (  pReq->bDesktop  )  hParent  =  GetDesktopWindow(  );
				  else  hParent  =  FindWindow(  NULL,  pReq->unique_wndTitle_parent  );

				  //			
				  {
					  POINT  pnt;
					  pnt.x  =  pReq->x;
					  pnt.y  =  pReq->y;
					  MapWindowPoints(  hParent,  NULL,  &pnt,  1  );
					  SetWindowPos(  hCurTalk,  NULL,  pnt.x,  pnt.y,  pReq->w,  pReq->h,  0  );  
				  }
	

				  //
				  BOOL  b3D  =  FALSE;
				  unsigned  char  ucbAvConsole  =  TRUE;
				  //	
				  pFuncs->pf_doCmd_startAvCall(  hCurTalk,  hCurTalk,  0,  b3D,  ucbAvConsole,  null  );
	

					


				  }
				  //
				  break;
				  //

			case  CONST_avConsole_cmd_closeAvTalk:  {
				  //
				  AvConsole_req_closeAvTalk  *  pReq  =  (  AvConsole_req_closeAvTalk  *  )pReqHead;
				  //do_avConsole_av(  pReqHead  );
				  CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
				  CHelp_getDlgTalkVar  help_getDlgTalkVar;
				  
				  
				  HWND  hMgr  =  NULL;
				  //
				  QY_MESSENGER_ID  idInfo;  idInfo.ui64Id  =  pReq->ui64Id;
				  if  (  findTalker(  pQyMc,  pMisCnt,  &idInfo,  &hMgr  )  )  goto  errLabel;

				  //
				  DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
				  if  (  !pMgrVar  )  goto  errLabel;
				  if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
				  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
				  //
				  int  i;
				  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
					  if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  break;
				  }
				  if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  goto  errLabel;
				  HWND  hCurTalk  =  pShadowMgr->shadows[i].hShadow;

				  //
				  SendMessageTimeout(  hCurTalk,  WM_CLOSE,  0,  0,  0,  1000,  NULL  );			


				  }
				  //
				  break;

				  //
			case  CONST_avConsole_cmd_initMsg:{
				  //
				  AvConsole_req_initMsg  *  pReq  =  (  AvConsole_req_initMsg  *  )pReqHead;
				  
				  
				  //
				  if  (  _tcscmp(  pReq->unique_wndTitle_parent,  pProcInfo->avConsole.unique_wndTitle_parent  )  )  {
					  safeTcsnCpy(  pReq->unique_wndTitle_parent,  pProcInfo->avConsole.unique_wndTitle_parent,  mycountof(  pProcInfo->avConsole.unique_wndTitle_parent  )  );
				  }
				  if  (  pProcInfo->avConsole.unique_wndTitle_parent[0]  )  {
					  pProcInfo->avConsole.bGotMsg_avConsole  =  TRUE;
				  }
				  			  

				  }
				  //				  
				  break;
				  //

			case  CONST_avConsole_cmd_msg:{
				  //
				  AvConsole_req_msg  *  pReq  =  (  AvConsole_req_msg  *  )pReqHead;
				  
				  //
				  CQyMalloc				mallocObj_pMsgBuf;
				  MIS_MSGU			*	pMsgBuf				=	NULL;


				  QY_MESSENGER_ID  idInfo_dst;
				  
				  //
				  if  (  _tcscmp(  pReq->unique_wndTitle_parent,  pProcInfo->avConsole.unique_wndTitle_parent  )  )  {
					  safeTcsnCpy(  pReq->unique_wndTitle_parent,  pProcInfo->avConsole.unique_wndTitle_parent,  mycountof(  pProcInfo->avConsole.unique_wndTitle_parent  )  );
				  }
				  if  (  pProcInfo->avConsole.unique_wndTitle_parent[0]  )  {
					  pProcInfo->avConsole.bGotMsg_avConsole  =  TRUE;
				  }
				  


				  //
				  pMsgBuf  =  (  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  sizeof(  MIS_MSGU  )  );	
				  if  (  !pMsgBuf  )  return  -1;


				  //  Æä´ÎÔÙ·¢ÍùmgrÊ¹·¢ËÍ	
				  unsigned  char		ucFlg;
				  IM_HTML_CONTENT		content;
				  int					lenInBytes;
				  //
				  ucFlg  =  0;
				  //
				  memset(  &content,  0,  sizeof(  content  )  );
				  content.uiType  =  CONST_imCommType_htmlContent;
				  lstrcpyn(  content.wBuf,  pReq->tTxt,  mycountof(  content.wBuf  )  );
				  lenInBytes  =  offsetof(  IM_HTML_CONTENT,  wBuf  )  +  (  lstrlen(  content.wBuf  )  +  1  )  *  sizeof(  content.wBuf[0]  );
				  //
				  MSG_ROUTE	route;
				  memset(  &route,  0,  sizeof(  route  )  );
				  //
				  route.idInfo_from.ui64Id  =  pMisCnt->idInfo.ui64Id;
				  //
				  route.idInfo_to.ui64Id  =  pReq->ui64Id_dst;
				  //
				  {
					  MACRO_prepareForTran(  );
					
					  //
					  QY_MESSENGER_ID  idInfo_logicalPeer  =  {0};
					  QY_MESSENGER_ID  idInfo_dst  =  {0};
					  //
					  idInfo_dst.ui64Id  =  pReq->ui64Id_dst;

					  //
					  if  (  postMsg2Mgr_mc(  pMisCnt,  &route,  CONST_misMsgType_talk,  ucFlg,  CONST_qyCmd_talkTo,  tStartTran,  uiTranNo,  0,  (  char  *  )&content,  lenInBytes,  &idInfo_logicalPeer,  &idInfo_dst,  0,  pMsgBuf,  TRUE  )  )  goto  errLabel;
		
				  }



				  }
				  //				  
				  break;
				  //
			case  CONST_avConsole_cmd_view3dWall:{
				  //
				  AvConsole_req_view3dWall  *  pReq  =  (  AvConsole_req_view3dWall  *  )pReqHead;
				  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
				  
				  //
				  dyn_createConsoleWall(  pQyMc->pGBuf_d3d  );
				  
				  //
				  HWND  hWall  =  pGBuf->hWall_d3d;
				  //
				  SetForegroundWindow(  hWall  );
				  //
				  PostMessage(  hWall,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );

				  }
				  //
				  break;

				  //
			default:
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "unkown reqCmd: %d"  ),  pReqHead->usCmd  );
				  showInfo_open0(  0,  _T(  "do_avConnsole_req"  ),  tBuf  );				  
				  break;
	}


	iErr  =  0;
errLabel:

	return  iErr;
}
#endif

//
int  tmpHandle_enumMessenger_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	QY_MC	*	pQyMc  =  QY_GET_GBUF(  );

	//
	COMMON_PARAM  *  pCommonParam0  =  (  COMMON_PARAM  *  )p0;
	int  *  pnTotal  =  (  int  *  )pCommonParam0->p2;
	//  p0;
	COMMON_PARAM		*	pCommonParam1	=		(  COMMON_PARAM  *  )p1;
	//
	int  *  piCnt  =  (  int  *  )pCommonParam1->p1;
	AvConsole_req_retrieveUsr  *  pUsrs  =  (  AvConsole_req_retrieveUsr  *  )pCommonParam1->p2;


#if  0
	CMyDb				*   pMyDb			=		(  CMyDb  *  )pCommonParam1->p2;
#endif
	//
	QMEM_qyImObj		*   pQMem			=		(  QMEM_qyImObj  *  )p2;

	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_DMITEM				*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

	memset(  &regInfo,  0,  sizeof(  regInfo  )  );

	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return  -1;//goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;
		TCHAR	talkerDesc[128]  =  _T(  ""  );


	if  (  pQMem->messengerInfo.iStatus  ==  CONST_qyStatus_ok
		&&  pQMem->messengerInfo.uiType  !=  CONST_objType_imGrp  )
	{

		if  (  *piCnt  >=  *pnTotal  )  goto  errLabel;
		pUsrs[*piCnt].ui64Id  =  pQMem->messengerInfo.idInfo.ui64Id;
		(*piCnt)  ++  ;
		//
#if  0
		//  2015/06/05
		if  (  pQMem->messengerInfo.uiType  ==  CONST_objType_me  )  {
			iRet  =  0;  goto  errLabel;
		}
	
		//
		if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pMyDb,  CONST_dbType_myDb,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  pQMem->messengerInfo.misServName, &pQMem->messengerInfo.idInfo,  0,  &regInfo  )  )  {
			memset(  &regInfo,  0,  sizeof(  regInfo  ) );
		}
		HWND	hCtl	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  );
		int		tmpiRet;
		regInfo2Desc(  0,  &regInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  ); 

		
#endif
		//_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d,  %s, idInfo is %I64u, talkerDesc %s"  ),  m_var.usItemCount,  qyGetDesByType1(  pTable,  pQMem->messengerInfo.uiType  ),  regInfo.addr.idInfo.ui64Id,  talkerDesc  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\tidInfo is %I64u, talkerDesc %s"  ),  pQMem->messengerInfo.idInfo.ui64Id,  talkerDesc  );
		OutputDebugString(  tBuf  );
		OutputDebugString(  _T(  "\n"  )  );

	}


	iRet  =  0;
errLabel:
	return  iRet;

}

//
int cmp ( const void *a , const void *b )

{ return *(int *)a - *(int *)b; }


//
#if  0
int  doAvConsole_cmd_retrieveUsrs(  AvConsole_req_retrieveUsrs  *  pReq  )
{
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	//
	AvConsole_req_retrieveUsr  *  pUsrs  =  NULL;

	//
	HWND  hWnd_recv  =  FindWindow(  NULL,  pReq->unique_wndTitle_parent  );
	if  (  !hWnd_recv  )  return  -1;


	//
	AvConsole_req_retrieveUsrs  req  =  {0};
		
		//
		req.iType  =  CONST_qisMsgType_avConsole;		
		//
		req.usCmd  =  CONST_avConsole_cmd_retrieveUsrs;
		req.ucbReply  =  TRUE;
		
		
		//	
		QY_OBJ_DB		*	pObjDb	=	getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
		if  ( !pObjDb  )  goto  errLabel;
	
		//		
		CMyDb				*	pMyDb											=  (  CMyDb  *  )pObjDb->pDb;
		if  (  !pMyDb  )  goto  errLabel;
	
		QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_DMITEM				*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

	memset(  &regInfo,  0,  sizeof(  regInfo  )  );

	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;



		//
		int  nTotal  =  pMyDb->m_var.pQ_qyImObjTab->uiQNodes;
		int  size  =  nTotal  *  sizeof(  AvConsole_req_retrieveUsr  );
		pUsrs  =  (  AvConsole_req_retrieveUsr  *  )malloc(  size  );
		if  (  !pUsrs  )  goto errLabel;
		int  iCnt  =  0;
		//
		COMMON_PARAM  commonParam0;
		MACRO_makeCommonParam3(  0,  0,  &nTotal,  commonParam0  );
		//
		COMMON_PARAM  commonParam1;
		MACRO_makeCommonParam3(  0,  &iCnt,  pUsrs,  commonParam1  );
		//	
		if  (  qTraverse(  pMyDb->m_var.pQ_qyImObjTab,  tmpHandle_enumMessenger_myDb,  &commonParam0,  &commonParam1  )  <  0  )  goto  errLabel;

		//
		int  i;

#if  0
		for  (  i  =  0;  i  <  iCnt;  i  ++  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "before sorted: [%d] is %I64u\n"  ),  i,  pUsrs[i].ui64Id  );
			OutputDebugString(  tBuf  );
		}
#endif

		//
		qsort(  pUsrs,  iCnt,  sizeof(  pUsrs[0]  ),  cmp  );

		//
#if  0
		for  (  i  =  0;  i  <  iCnt;  i  ++  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "sorted: [%d] is %I64u\n"  ),  i,  pUsrs[i].ui64Id  );
			OutputDebugString(  tBuf  );
		}
#endif

		//
		unsigned  __int64  ui64Id_lastRecvd  =  pReq->ui64Id_lastRecvd;
		//
		for  (  i  =  0;  i  <  iCnt;  i  ++  )  {
			 if  (  pUsrs[i].ui64Id  <=  ui64Id_lastRecvd  )  continue;
			 //
			 if  (  req.usCnt  ==  mycountof(  req.mems  )  )  break;
			 //
			 req.mems[req.usCnt].ui64Id  =  pUsrs[i].ui64Id;
			 req.usCnt  ++  ;
			 continue;
		}
		//
		for  (  i  =  0;  i  <  req.usCnt;  i  ++  )  {
			 //
			 //	
			TCHAR  *  misServName  =  _T(  ""  );
			QY_MESSENGER_ID  idInfo;
			idInfo.ui64Id  =  req.mems[i].ui64Id;
			//
			if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pMyDb,  CONST_dbType_myDb,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  misServName, &idInfo,  0,  &regInfo  )  )  {
				memset(  &regInfo,  0,  sizeof(  regInfo  ) );
			}
					
			//
			TCHAR	talkerDesc[128]  =  _T(  ""  );		
			regInfo2Desc(  0,  &regInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  ); 

			//
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "[%d] %I64u, %s\n"  ),  i,  req.mems[i].ui64Id,  talkerDesc  );
			OutputDebugString(  tBuf  );

			//
			safeTcsnCpy(  desc.pDw,  req.mems[i].dw,  mycountof(  req.mems[i].dw  )  );
			safeTcsnCpy(  desc.pBm,  req.mems[i].bm,  mycountof(  req.mems[i].bm  )  );
			safeTcsnCpy(  desc.pSyr,  req.mems[i].syr,  mycountof(  req.mems[i].syr  )  );

			//
			continue;
		}

		//
		//for  (  i  =  0



		
		//
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData  =  &req;		 
		tmpCopyData.cbData  =  sizeof(  req  );
		int  iRet  =  ::SendMessage( hWnd_recv,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
		

	iErr  =  0;
errLabel:

	if  (  pUsrs  )  free(  pUsrs  );

	return  iErr;
}
#endif

//
TCHAR									g_unique_wndTitle_parent[64];			//  必须是独一无二的窗口题头。
unsigned  __int64						g_ui64Id_toBeRetrieved;


//
#if  0
__declspec(  dllexport  )  int  doAvConsole_cmd_retrieveDynBmps(  AvConsole_req_retrieveDynBmps  *  pReq  )
{
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;
	
	//
	if  (  pReq->ucbReply  )  {
		//
		pReq->ui64Id_toBeRetrieved  =  g_ui64Id_toBeRetrieved;
		//
		HWND  hWnd_recv  =  FindWindow(  NULL,  g_unique_wndTitle_parent  );	
		if  (  !hWnd_recv  )  return  -1;
		//
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData  =  pReq;		 
		tmpCopyData.cbData  =  sizeof(  pReq[0]  );
		int  iRet  =  ::SendMessage( hWnd_recv,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
		//
		iErr  =  0;  goto  errLabel;
	}

	//
	HWND  hWnd_recv  =  FindWindow(  NULL,  pReq->unique_wndTitle_parent  );
	if  (  !hWnd_recv  )  return  -1;

	//
	safeTcsnCpy(  pReq->unique_wndTitle_parent,  g_unique_wndTitle_parent,  mycountof(  g_unique_wndTitle_parent  )  );
	g_ui64Id_toBeRetrieved  =  pReq->ui64Id_toBeRetrieved;

	//
	AvConsole_req_retrieveDynBmps  req  =  {0};
		
		//
		req.iType  =  CONST_qisMsgType_avConsole;		
		//
		req.usCmd  =  CONST_avConsole_cmd_retrieveDynBmps;
		req.ucbReply  =  TRUE;
		
		
		
		//
		//for  (  i  =  0

		//  __declspec(  dllexport  )  int  sndRetrieveDynBmpsReqToMsgr_qmc(  MIS_CNT  *  pMisCnt,  BOOL  bNeedProgress,  unsigned  int  uiObjType,  BOOL  bRetrieveOne,  QY_MESSENGER_ID  *  pIdInfo_imGrp_conf,  BOOL  bAvConsole,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  *puiTranNo  );

		//
		QY_MESSENGER_ID  idInfo_dst;
		idInfo_dst.ui64Id  =  pReq->ui64Id_toBeRetrieved;
		//
		unsigned  int  uiTranNo  =  0;
		if  (  sndRetrieveDynBmpsReqToMsgr_qmc(  pMisCnt,  FALSE,  0,  FALSE,  NULL,  TRUE,  &idInfo_dst,  &uiTranNo  )  )  {
			goto  errLabel;
		}


#if  0
		//
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData  =  &req;		 
		tmpCopyData.cbData  =  sizeof(  req  );
		int  iRet  =  ::SendMessage( hWnd_recv,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
#endif

	iErr  =  0;
errLabel:


	return  iErr;
}
#endif



//  2017/07/17
#if  0
__declspec(  dllexport  )  int  doAvConsole_cmd_recvMsg(  __int64  ui64Id_from,  __int64  ui64Id_to,  TCHAR  *  tTxt  )
{
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;
	
	//
	AvConsole_req_msg  req  =  {0};

		//
		req.iType  =  CONST_qisMsgType_avConsole;		
		//
		req.usCmd  =  CONST_avConsole_cmd_msg;

	//
	{
		//
		req.ui64Id_from  =  ui64Id_from;
		req.ui64Id_dst  =  ui64Id_to;

		//
		safeTcsnCpy(  tTxt,  req.tTxt,  mycountof(  req.tTxt  )  );


		//
		HWND  hWnd_recv  =  FindWindow(  NULL,  pProcInfo->avConsole.unique_wndTitle_parent  );	
		if  (  !hWnd_recv  )  return  -1;
		//
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData  =  &req;		 
		tmpCopyData.cbData  =  sizeof(  req  );
		int  iRet  =  ::SendMessage( hWnd_recv,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
		//
		iErr  =  0;  goto  errLabel;
	}


	iErr  =  0;
errLabel:


	return  iErr;
}
#endif