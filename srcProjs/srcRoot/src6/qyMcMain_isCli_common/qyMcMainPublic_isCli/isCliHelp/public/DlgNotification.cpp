// DlgNotification.cpp : implementation file
//

#include	"stdafx.h"
#include	<math.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"

#include	"qyStatic.h"
#include	"DlgNotification.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define		CONST_timerId_popWindow					1
//  #define		CONST_timerId_closeWindow			2

#define		CONST_nElapseInMs_popWindow				20

//
//  #define		CONST_bkColor_notification			RGB(  0,  0,  0  )
#define		CONST_bkColor_notification				RGB(  255,  255,  255  )
//  #define		CONST_bkColor_notification			RGB(  255,  0,  0  )

#if  0
#define		CONST_fontColor_notification			RGB(  0,  0,  0  )
#else
#define		CONST_fontColor_notification			RGB(  0,  0,  64  )
#endif
//													RGB(  0,  64,  128  )  
#define		CONST_faceName_notification				"Arial"



__declspec(  dllexport  )  int  popupNotificationWnd(  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int							iErr		=	-1;
	QY_MC				*		pQyMc		=	QY_GET_GBUF(  );
	
	//  if  (  isQmCmd(  )  )  return  -1;  
	//
	MC_VAR_isCli			*		pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	if  (  IsWindow(  pProcInfo->hWnd_notification  )  )  return  0;

	CDlgNotification	*	pDlg	=	NULL;
	RECT					rect;

	pDlg  =  new  CDlgNotification(  CWnd::GetDesktopWindow(  )  );
	if  (  !pDlg  )  goto  errLabel;

	CDlgDesktopsMon	*	pBase	=	pDlg;
	memset(  &pBase->m_var.layoutParam,  0,  sizeof(  pBase->m_var.layoutParam  )  );
	pBase->m_var.layoutParam.iH_static  =  pProcInfo->cfg.policy.notification.iH_static;
	//  pBase->m_var.ucbHideStatic  =  TRUE;

	int  iWndContentType  =  0;
	unsigned  int  uiInitW  =  pProcInfo->cfg.policy.notification.iW_pic;
	unsigned  int  uiInitH  =  pProcInfo->cfg.policy.notification.iH_pic;
	if  (  !pDlg->bSetDlgInfo(  iWndContentType,  0,  0,  1,  1,  uiInitW,  uiInitH  )  )  goto  errLabel;

	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		

	//  pDlg->ShowWindow(  SW_SHOWNOACTIVATE  );
	pDlg->ShowWindow(  SW_SHOWNA  );

	pDlg->EnableWindow(  TRUE  );

	//
	pProcInfo->hWnd_notification  =  pDlg->m_hWnd;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  {
			delete  pDlg;  pDlg  =  NULL;
		}
	}
	return  iErr;
}



__declspec(  dllexport  ) int  addNotification(  MIS_MSG_taskStatus  *  pStatus  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iErr	=	-1;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	if  (  !IsWindow(  pProcInfo->hWnd_notification  )  )  return  -1;

	CDlgNotification	*	pDlg	=	(  CDlgNotification  *  )CWnd::FromHandle(  pProcInfo->hWnd_notification  );

	if  (  !pDlg->bAddNotification(  pStatus  )  )  return  -1;

	iErr  =  0;

	return  iErr;
}


__declspec(  dllexport  )  int  removeNotification(  QY_MESSENGER_ID  *  pIdInfo_logicalPeer  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iErr		=	-1;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	if  (  !IsWindow(  pProcInfo->hWnd_notification  )  )  {
		iErr  =  0;  goto  errLabel;
	}

	CDlgNotification	*	pDlg	=	(  CDlgNotification  *  )CWnd::FromHandle(  pProcInfo->hWnd_notification  );

	if  (  !pDlg->bRemoveNotification(  pIdInfo_logicalPeer  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;
}


  __declspec(  dllexport  )  int  clearNotification(  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iErr		=	-1;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	if  (  !IsWindow(  pProcInfo->hWnd_notification  )  )  {
		iErr  =  0;  goto  errLabel;
	}

	CDlgNotification	*	pDlg	=	(  CDlgNotification  *  )CWnd::FromHandle(  pProcInfo->hWnd_notification  );
	if  (  !pDlg  )  return  -1;

	if  (  pDlg->m_var.bInited_q  )  {
		emptyGenericQ(  &pDlg->m_var.q  );
	}

	QY_MESSENGER_ID	idInfo_logicalPeer;
	idInfo_logicalPeer.ui64Id  =  0;
	if  (  !pDlg->bRemoveNotification(  &idInfo_logicalPeer  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;
}




// CDlgNotification dialog


CDlgNotification::CDlgNotification(CWnd* pParent /*=NULL*/)
	: CDlgDesktopsMon( pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgNotification::~CDlgNotification()
{
}



BEGIN_MESSAGE_MAP(CDlgNotification, CDlgDesktopsMon)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


#ifdef  __DEBUG__

  int  tmpHandler_printQ_notification(  void  *  p0,  void  *  p1,  MIS_MSG_taskStatus  *  pMem  )
{
	traceLog(  _T(  "logicalPeer: %I64u, iContentType %d, hint %s"  ),  pMem->idInfo_logicalPeer.ui64Id,  pMem->uiContentType,  pMem->u.notification.tBuf  );

	return  0;
}

int  CDlgNotification::printQ(  )
{
	qTraverse(  &m_var.q,  0,  0,  tmpHandler_printQ_notification  );
	return  0;
}

#endif


BOOL  CDlgNotification::mybVideoExists(  )
{
	//  traceLog(  _T(  "Not finished: bVideoExists"  )  );
	return  TRUE;
}






 int  tmpHandler_findMsgr(  void  *  p0,  void  *  p1,  MIS_MSG_taskStatus  *  pMem  )
{
	int					iErr	=	-1;
	//  void			*	p0;
	QY_MESSENGER_ID	*	pIdInfo_logicalPeer	=	(  QY_MESSENGER_ID	*  )p1;

	if  (  pMem->idInfo_logicalPeer.ui64Id  ==  pIdInfo_logicalPeer->ui64Id  )  {
		iErr  =  1;  goto  errLabel;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}


 BOOL  CDlgNotification::bAddNotification(  MIS_MSG_taskStatus  *  pStatus  )
{
	BOOL			bRet		=	FALSE;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	
	if  (  !m_var.bInited_q  )  return  FALSE;

	qRemoveMsg(  &m_var.q,  (  PF_bCommonHandler  )tmpHandler_findMsgr,  0,  &pStatus->idInfo_logicalPeer  );

	if  (  qPostMsg(  pStatus,  sizeof(  pStatus[0]  ),  &m_var.q,  _T(  "dlgNotification.bAddNot"  )))  goto  errLabel;

#ifdef  __DEBUG__
		this->printQ(  );
#endif

	GetDlgItem(  m_var.idcHint  )->Invalidate(  );

	if  (  pProcInfo->cfg.policy.notification.ucbBeep  )  {
		MessageBeep(  MB_ICONASTERISK  );			///MB_ICONASTERISK,MB_ICONHAND,MB_OK
	}

	this->EnableWindow(  FALSE  );

	//SetTimer(  CONST_timerId_popWindow,  CONST_nElapseInMs_popWindow,  NULL  );  

	bRet  =  TRUE;

errLabel:

	return  bRet;
}
	
BOOL  CDlgNotification::bRemoveNotification(  QY_MESSENGER_ID	*	pIdInfo_logicalPeer  )
{
	BOOL	bRet	=	FALSE;

	if  (  !m_var.bInited_q  )  return  FALSE;

	qRemoveMsg(  &m_var.q,  (  PF_bCommonHandler  )tmpHandler_findMsgr,  0,  pIdInfo_logicalPeer  );

	GetDlgItem(  m_var.idcHint  )->Invalidate(  );

	this->EnableWindow(  FALSE  );

	//SetTimer(  CONST_timerId_popWindow,  CONST_nElapseInMs_popWindow,  NULL  );  

	bRet  =  TRUE;

	return  bRet;
}


 //  int  CDlgNotification::sizeAllControls_dlgDesktopsMon(  RECT  &rc  )
int  CDlgNotification::sizeAllControls(  RECT  rc  )
{ 

	 int					iErr							=	-1;
	 CDlgDesktopsMon  *		pDlg							=	this;  
	 HDWP					hDwp;
	 //
	 int					iW_pic							=	10;
	 int					iH_pic							=	10;
	 //
	 int					idc;
	 unsigned  int			nTotal							=	0;
	 //
	 int					i,  j;
	 QY_DMITEM			*	pItem;
	 int					x,y;
	 int					iH,  iW;
	 //
	 int					index;

	 if  (  !pDlg  )  return  -1;
	 if  (  !pDlg->m_var.bInfoSet  )  return  -1;
	 if  (  pDlg->m_var.usCnt_row  *  pDlg->m_var.usCnt_col  >  getnItems(  pDlg->m_var.pIdcTable  )  )  return  -1;
	 if  (  !pDlg->m_var.bDlgInited  )  return  -1;	 
     
	 //
	 iW_pic  =  (  rc.right  -  rc.left  -  pDlg->m_var.layoutParam.iEdge_l  -  pDlg->m_var.layoutParam.iEdge_r  -  (  pDlg->m_var.usCnt_col  -  1  )  *  pDlg->m_var.layoutParam.iX_spacing  )  /  pDlg->m_var.usCnt_col;
	 iH_pic  =  (  rc.bottom  -  rc.top  -  pDlg->m_var.layoutParam.iEdge_t  -  pDlg->m_var.layoutParam.iEdge_b  -  pDlg->m_var.layoutParam.iH_btn  -  pDlg->m_var.layoutParam.iY_spacing_static_btn  -  (  pDlg->m_var.usCnt_row  -  1  )  *  pDlg->m_var.layoutParam.iY_spacing_static_pic  )  /  pDlg->m_var.usCnt_row;

	 //
	 nTotal  =  pDlg->m_var.usCnt_row  *  pDlg->m_var.usCnt_col  *  2;

	 hDwp  =  BeginDeferWindowPos(  nTotal  );
	 if  (  hDwp  )  {		 

		 for  (  i  =  0;  i  <  pDlg->m_var.usCnt_row;  i  ++  )  {

			  for  (  j  =  0;  j  <  pDlg->m_var.usCnt_col;  j  ++  )  {
				   index  =  i  *  pDlg->m_var.usCnt_col  +  j;
				   //		 
				   pItem  =  &pDlg->m_var.pIdcTable[index];
				   idc  =  (  int  )pItem->des;
				   //
				   x  =  pDlg->m_var.layoutParam.iEdge_l  +  j  *  (  iW_pic  +  pDlg->m_var.layoutParam.iX_spacing  );
				   y  =  pDlg->m_var.layoutParam.iEdge_t  +  i  *  (  iH_pic  +  pDlg->m_var.layoutParam.iY_spacing_pic_static  +  pDlg->m_var.layoutParam.iH_static  +  pDlg->m_var.layoutParam.iY_spacing_static_pic  );
		 		   //
		 		   iW  =  iW_pic;  iH  =  iH_pic;
		 		   //  DeferWindowPos(  hDwp,  pDlg->GetDlgItem(  idc  )->m_hWnd,  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
				   DeferWindowPos(  hDwp,  pDlg->GetDlgItem(  idc  )->m_hWnd,  pDlg->GetDlgItem(  (  int  )pItem->pData  )->m_hWnd,  x,  y,  iW,  iH,  (  SWP_SHOWWINDOW  )  );
				   //
				   pDlg->m_var.mems_org[index].iX  =  x;
				   pDlg->m_var.mems_org[index].iY  =  y;
				   pDlg->m_var.mems_org[index].iW  =  iW;
				   pDlg->m_var.mems_org[index].iH  =  iH;
				   //
				   idc  =  (  int  )pItem->pData;
				   //
				   //  y  +=  iH  +  pDlg->m_var.layoutParam.iY_spacing_pic_static;
				   y  +=  iH  -  pDlg->m_var.layoutParam.iH_static;
				   //
				   m_var.rectHint.iX  =  x  +  1;
				   m_var.rectHint.iY  =  y;
				   m_var.rectHint.iW  =  iW_pic  -  2;
				   m_var.rectHint.iH  =  pDlg->m_var.layoutParam.iH_static;
				   //
				   DeferWindowPos(  hDwp,  pDlg->GetDlgItem(  idc  )->m_hWnd,  NULL,  m_var.rectHint.iX,  m_var.rectHint.iY,  m_var.rectHint.iW,  m_var.rectHint.iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );

			  }

		 }
		 
		 EndDeferWindowPos(  hDwp  );
	 }

#if  0
	 for  (  i  =  0;  i  <  pDlg->m_var.usCnt_row;  i  ++  )  {
		  for  (  j  =  0;  j  <  pDlg->m_var.usCnt_col;  j  ++  )  {
			   pItem  =  &pDlg->m_var.pIdcTable[i  *  pDlg->m_var.usCnt_col  +  j];

			   idc  =  (  int  )pItem->des;
			   ::ShowWindow(  ::GetDlgItem(  pDlg->GetSafeHwnd(  ),  idc  ),  SW_SHOW  );			   
			   
			   if  (  !pDlg->m_var.ucbHideStatic  )  {
				   idc  =  (  int  )pItem->pData;
				   ::ShowWindow(  ::GetDlgItem(  pDlg->GetSafeHwnd(  ),  idc  ),  SW_SHOW  );			   			   
			   }

			   continue;
		  }
	 }
#endif

	 iErr  =  0;
//  errLabel:
	return  iErr;
}


 int  OnPaint_hint_notification(  CDlgNotification  *  pParent,  CWnd  *  pCtrl,  CDC  *  pDc_idc  )
{
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	BOOL				bVideoExists	=	pParent->mybVideoExists(  );
	CDlgDesktopsMon	*	pBase			=	(  CDlgDesktopsMon  *  )pParent;
	int					iW_win			=	pBase->m_var.uiInitW_pic;
	//  int					iH_win			=	(  bVideoExists  ?  pBase->m_var.uiInitH_pic  :  0  )  +  pBase->m_var.layoutParam.iH_static;
	int					y_sep			=	0;
	int					y_bottom		=	y_sep  +  pBase->m_var.layoutParam.iH_static;

	CRect				rect;

	if  (  !pParent->m_var.bInited_q  )  return  -1;

	if  (  !isQEmpty(  &pParent->m_var.q  )  )  {
		MIS_MSG_taskStatus	*	pStatus	=	(  MIS_MSG_taskStatus  *  )pParent->m_var.q.pRear->qElemMemory.m_pBuf;

		if  (  pStatus  )  {
			pProcInfo->status.notification.tBuf[0]  =  0;	//  2011/02/02
			if  (  pStatus->u.notification.idInfo_from.ui64Id  )  {
				pFuncs->pf_getTalkerDesc(  pStatus->u.notification.idInfo_from,  NULL,  0,  pProcInfo->status.notification.tBuf,  mycountof(  pProcInfo->status.notification.tBuf  )  );
				_sntprintf(  pProcInfo->status.notification.tBuf,  mycountof(  pProcInfo->status.notification.tBuf  ),  _T(  "%s: "  ),  pProcInfo->status.notification.tBuf  );
			}
			if  (  pStatus->uiContentType  )  {
				switch  (  pStatus->uiContentType  )  {
						case  CONST_imCommType_htmlContent:
							  break;
						default:
								_sntprintf(  pProcInfo->status.notification.tBuf,  mycountof(  pProcInfo->status.notification.tBuf  ),  _T(  "%s%s, "  ),  pProcInfo->status.notification.tBuf,  qyGetDesByType1(  getResTable(  0,  &g_pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pStatus->uiContentType  )  );
								break;
				}
			}
			if  (  pStatus->u.notification.tBuf[0]  )  {
				_sntprintf(  pProcInfo->status.notification.tBuf,  mycountof(  pProcInfo->status.notification.tBuf  ),  _T(  "%s%s"  ),  pProcInfo->status.notification.tBuf,  pStatus->u.notification.tBuf  );
			}

			//  if  (  pInfo->idInfo_from
		}
	}


#if  10
	TRIVERTEX        vert[2] ;
	GRADIENT_RECT    gRect;
	vert [0] .x      = 0;
	vert [0] .y      = y_sep;
	vert [0] .Red    = 0x5100;
	vert [0] .Green  = 0xf500;
	vert [0] .Blue   = 0x0a00;
	vert [0] .Alpha  = 0x0000;

	vert [1] .x      = iW_win;
	vert [1] .y      = y_bottom; 
	vert [1] .Red    = 0x0700;
	vert [1] .Green  = 0xf800;
	vert [1] .Blue   = 0xf100;
	vert [1] .Alpha  = 0x0000;

	gRect.UpperLeft  = 0;
	gRect.LowerRight = 1;
	GradientFill(  pDc_idc->m_hDC,vert,2,&gRect,1,GRADIENT_FILL_RECT_H);
#endif

#if  0
	CFont	font;
	font.CreatePointFont(  90,  _T(  CONST_faceName_notification  )  );
	pDc_idc->SelectObject(  &font  );
	pDc_idc->SetTextColor(  CONST_fontColor_notification  );
	pDc_idc->SetBkMode(  TRANSPARENT  );

	//  rect.SetRect(  m_var.rectHint.iX,  m_var.rectHint.iY,  m_var.rectHint.iX  +  m_var.rectHint.iW,  m_var.rectHint.iY  +  m_var.rectHint.iH  );
	rect.SetRect(  0,  0,  pParent->m_var.rectHint.iW,  pParent->m_var.rectHint.iH  );

	//  
	//  pDc_idc->DrawText(  pProcInfo->status.notification.tBuf,  -1,  &rect,  DT_LEFT  |  DT_SINGLELINE  |  DT_VCENTER  );
	RECT  rc  =  rect;
	RECT  tmpRc  =  rect;
			 UINT uFormat  =  DT_CENTER  |  DT_WORDBREAK;
		 pDc_idc->DrawText(  pProcInfo->status.notification.tBuf,  lstrlen(  pProcInfo->status.notification.tBuf  ),  &tmpRc,  uFormat  |  DT_CALCRECT    );
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
		 pDc_idc->DrawText(  pProcInfo->status.notification.tBuf,  lstrlen(  pProcInfo->status.notification.tBuf  ),  &tmpRc,  uFormat    );




#endif

		 myDrawTxt(  pProcInfo->status.notification.tBuf,  90,  _T(  CONST_faceName_notification  ),  CONST_fontColor_notification,  0,  0,  pParent->m_var.rectHint.iW,  pParent->m_var.rectHint.iH,  pCtrl->m_hWnd,  pDc_idc->m_hDC  );  

	//  SetDlgItemText(  m_var.idcHint,  str  );
	//  应该用CQyStatic 将这个idcHint子类化，也许就可以解决这个问题。



	//  pDc->BitBlt(  0, y_sep,  iW_win, y_bottom  -  y_sep, &dcMemory, 0, y_sep, SRCCOPY );

	

	return  0;
}


// CDlgNotification message handlers

BOOL CDlgNotification::OnInitDialog()
{
	int						iErr		=	-1;
	MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	CDlgDesktopsMon		*	pBase		=	this;

	this->EnableWindow(  FALSE  );

	CDlgDesktopsMon::OnInitDialog();

	m_var.nTimerIntervalInMs  =  20;
	m_var.usTimeInMsToPop  =  pProcInfo->cfg.policy.notification.usTimeInMsToPop;
	if  (  m_var.usTimeInMsToPop  <  m_var.nTimerIntervalInMs  )  m_var.usTimeInMsToPop  =  m_var.nTimerIntervalInMs;

	m_var.pMisCnt  =  (  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );

	if  (  initGenericQ(  _T(  "notificationQ"  ),  _T(  "mtxNotification"  ),  0,  50,  mymalloc,  myfree,  &m_var.q  )  )  goto  errLabel;
	m_var.bInited_q  =  TRUE;


	int  i;
	for  (  i  =  0;  i  <  pBase->m_var.usCnt_row  *  pBase->m_var.usCnt_col;  i  ++  )  {
		 QY_DMITEM			*	pItem;
		 int					idc;
		 int					idcHint;

		 pItem  =  &pBase->m_var.pIdcTable[i];
		 idc  =  (  int  )pItem->des;	
		 idcHint  =  (  int  )pItem->pData;
		 //
		 m_var.idc  =  idc;
		 m_var.idcHint  =  idcHint;
		 break;
	}

	//
	m_brush_bk.CreateSolidBrush(  CONST_bkColor_notification  );
	
	//
	this->m_static_hint.SubclassDlgItem(  m_var.idcHint,  this  );
	this->m_static_hint.m_var.idc  =  m_var.idcHint;
	this->m_static_hint.m_var.pf_OnPaint  =  (  PF_commonHandler  )OnPaint_hint_notification;

	// TODO:  Add extra initialization here
	long  lStyle	=	0;
	lStyle  =  GetWindowLong(  this->m_hWnd,  GWL_STYLE  );
	lStyle  &=  ~(  WS_CAPTION  |  WS_THICKFRAME  );
	//  lStyle  |=  WS_BORDER;
	SetWindowLong(  this->m_hWnd,  GWL_STYLE,  lStyle  );

	//
	ModifyStyleEx(  WS_EX_APPWINDOW,  WS_EX_TOOLWINDOW  );
	
	//
	SetMenu(  NULL  );
	
	MoveWindow(  0,  0,  0,  0  );

	::SetWindowPos(  m_hWnd,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOSIZE  |  SWP_NOMOVE  |  SWP_NOACTIVATE  );

	m_var.dwTickCnt_initDialog  =  GetTickCount(  );
	m_var.bWaiting  =  TRUE;

	SetTimer(  CONST_timerId_popWindow,  CONST_nElapseInMs_popWindow,  NULL  );

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgNotification::OnTimer(UINT_PTR nIDEvent)
{
	int		cy  =  GetSystemMetrics(  SM_CYSCREEN  );
	int		cx  =  GetSystemMetrics(  SM_CXSCREEN  );
	RECT	rect;
	SystemParametersInfo(  SPI_GETWORKAREA,  0,  &rect,  0  );
	int		y	=	rect.bottom  -  rect.top;
	int		x   =   rect.right  -  rect.left;

	CDlgDesktopsMon	*	pBase			=	(  CDlgDesktopsMon  *  )this;
	int					iW_win			=	pBase->m_var.uiInitW_pic;
	//  int					iH_win			=	(  mybVideoExists(  )  ?  pBase->m_var.uiInitH_pic  :  0  )  +  pBase->m_var.layoutParam.iH_static;
	int					iH_win			=	max(  pBase->m_var.uiInitH_pic,  pBase->m_var.layoutParam.iH_static  );
	int					nH_oneTime		=	iH_win  *  m_var.nTimerIntervalInMs  /  m_var.usTimeInMsToPop;
	if  (  !nH_oneTime  )  nH_oneTime  =  1;
	int					nH_oneTime_toClose  =  nH_oneTime  /  3;
	if  (  !nH_oneTime_toClose  )  nH_oneTime_toClose  =  1;

	//
	BOOL				bCloseWindow	=	FALSE;

	if  (  !m_var.bInited_q  )  return;

	x  =  x  -  iW_win;

	this->EnableWindow(  FALSE  );

	// TODO: Add your message handler code here and/or call default
	switch  (  nIDEvent  )  {
			case  CONST_timerId_popWindow:
				  //
				  DWORD  dwTickCnt;
				  dwTickCnt  =  GetTickCount(  );
				  //
				  if  (  m_var.bWaiting  )  {
					  if  (  isQEmpty(  &m_var.q  )  )  {
						  if  (  GetTickCount(  )  -  m_var.dwTickCnt_initDialog  <  100  )  goto  errLabel;
						  bCloseWindow  =  TRUE;
						  goto  errLabel;
					  }
					  m_var.bWaiting  =  FALSE;
				  }

				  //
				  m_var.bClosing  =  isQEmpty(  &m_var.q  )  ?  TRUE  :  FALSE;
				  if  (  !m_var.bClosing  )  {
					  if  (  m_var.dwTickCnt_allDisplayed  )  {
						  int  iDiffInMs  =  dwTickCnt  -  m_var.dwTickCnt_allDisplayed;
						  iDiffInMs  =  abs(  iDiffInMs  );
						  if  (  iDiffInMs  >  1500  )  {
							  m_var.bClosing  =  TRUE;
						  }
					  }
				  }

				  if  (  !m_var.bClosing  )  {
					  if  (  m_var.nHeight  <  iH_win  )  {
						  //  m_var.nHeight  ++  ;
						  m_var.nHeight  =  min(  nH_oneTime  +  m_var.nHeight,  iH_win  );
						  MoveWindow(  x,  y  -  m_var.nHeight,  iW_win,  iH_win  );
						  Invalidate(  FALSE  );
						  //
						  }
					  else  {
						    if  (  !m_var.dwTickCnt_allDisplayed  )  {
								m_var.dwTickCnt_allDisplayed  =  GetTickCount(  );
							}
					  }
					  }
				  else  {
					    if  (  m_var.nHeight  >  0  )  {
							//  m_var.nHeight  --  ;
							m_var.nHeight  =  max(  0,  m_var.nHeight  -  nH_oneTime_toClose  );
							MoveWindow(  x,  y  -  m_var.nHeight,  iW_win,  iH_win  );
							Invalidate(  FALSE  );
							}
						else  {
							  //KillTimer(  nIDEvent  );
							  //
							  bCloseWindow  =  TRUE;
							  goto  errLabel;
						}
				  }
				  break;
			default:
					break;
	}


errLabel:

	this->EnableWindow(  TRUE  );

	if  (  bCloseWindow  )  {
		::SendMessage(  m_hWnd,  WM_CLOSE,  0,  0  );
	}
	return;
}



void CDlgNotification::OnPaint()
{
	//traceLog(  _T(  "OnPaint enters"  )  );

	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDlgDesktopsMon::OnPaint() for painting messages


	//  textOut(  &dc,  _T(  "Msg arrives"  )  );

	//traceLog(  _T(  "OnPaint leaves"  )  );


}

HBRUSH CDlgNotification::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//  traceLog(  _T(  "OnCtlColor"  )  );

#if  0
	  HBRUSH hbr = CDlgDesktopsMon::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	  return hbr;
#endif

	  if  (  m_var.idcHint  )  {
		  if  (  pWnd->GetDlgCtrlID(  )  ==  m_var.idcHint  )  {
			  pDC->SetBkMode(  TRANSPARENT  );
			  return  (  HBRUSH  )GetStockObject(  HOLLOW_BRUSH  );
		  }
	  }
	  if  (  m_var.idc  )  {
		  if  (  pWnd->GetDlgCtrlID(  )  ==  m_var.idc  )  {
			  pDC->SetBkMode(  TRANSPARENT  );
			  return  (  HBRUSH  )GetStockObject(  HOLLOW_BRUSH  );
		  }
	  }

	return  m_brush_bk;
}


void CDlgNotification::OnDestroy()
{
	this->m_brush_bk.DeleteObject(  );
	if  (  m_var.bInited_q  )  {
		exitGenericQ(  &m_var.q  );
		m_var.bInited_q  =  FALSE;
	}

	CDlgDesktopsMon::OnDestroy();

	// TODO: Add your message handler code here
}

void CDlgNotification::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	MC_VAR_isCli			*		pProcInfo				=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;

	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	traceLog(  _T(  "lBtn down"  )  );
	
	if  (  !m_var.bInited_q  )  return;

	if  (  !isQEmpty(  &m_var.q  )  )  {
		MIS_MSG_taskStatus	*	pStatus	=	(  MIS_MSG_taskStatus  *  )m_var.q.pRear->qElemMemory.m_pBuf;
		if  (  pStatus  )  {
			if  (  !pStatus->idInfo_logicalPeer.ui64Id  )  {
				this->bRemoveNotification(  &pStatus->idInfo_logicalPeer  );
			}
		}
	}
	if  (  !isQEmpty(  &m_var.q  )  )  {
		MIS_MSG_taskStatus	*	pStatus	=	(  MIS_MSG_taskStatus  *  )m_var.q.pRear->qElemMemory.m_pBuf;
		if  (  pStatus  )  {
			if  (  pStatus->idInfo_logicalPeer.ui64Id  )  {		
				//  
				BOOL  bNeedNotShowWnd  =  FALSE;
				pFuncs->pf_tryToTalkToMessenger_any( mynull, pStatus->idInfo_logicalPeer.ui64Id,  0,  bNeedNotShowWnd,  TRUE,  NULL  );
				//
				this->bRemoveNotification(  &pStatus->idInfo_logicalPeer  );
			}
		}
	}

	CDlgDesktopsMon::OnLButtonDown(nFlags, point);
}
