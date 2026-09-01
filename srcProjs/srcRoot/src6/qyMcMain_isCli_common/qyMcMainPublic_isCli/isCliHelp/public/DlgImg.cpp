// DlgImg.cpp : implementation file
//

#include "stdafx.h"
#include	<stdlib.h>
#include	<math.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"
#include	"qmcVWall.h"
#include	"WallTalkers.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"

#include	"qyCusResTemp.h"

#include	"qyAvRecordPublic.h"
#include	"imgProcessPublic.h"


#include	"sp.h"
#include	"isCliHelp.h"


#include	"DlgImg.h"
#include	"afxdialogex.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"qycusResTemp.h"

#include	"myDb.h"

#include	"DlgChromaKeyCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif





 __declspec(  dllexport  ) int  viewDlgImg(  HWND  hParent,  int  iSubType,  LPCTSTR  cusName  )
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
	CDlgImg			*	pDlg			=		NULL;
	RECT					rect;
	CWaitCursor				cur;

	int						i;
	int						iWndContentType	=		CONST_qyWndContentType_dlgImg;

	traceLogA(  "viewDlgImg enters"  );


	//
	switch  (  iSubType  )  {
			case  CONST_dlgImgSubtype_chromaKey:
				  if  (  IsWindow(  pProcInfo->chromaKey.hWnd_dlgImg  )  )  {
					  MACRO_SetForegroundWindow(  pProcInfo->chromaKey.hWnd_dlgImg  );
					  iErr  =  0;  goto  errLabel;	
				  }
				  break;
			default:
					goto  errLabel;
	}





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
		pDlg  =  new  CDlgImg(  CWnd::FromHandle(  hParent  )  );
		if  (  !pDlg  )  goto  errLabel;

		int  iResId_menu  =  CONST_resId_menu_dlgImg_chromaKey;

		if  (  !pDlg->bSetDlgInfo(  iWndContentType,  iSubType,  _T(  "Chroma Key"  ),  iResId_menu,  NULL,  usCnt_monPics_row,  usCnt_monPics_col,  uiInitW  +  32,  uiInitH  +  32  )  )  goto  errLabel;
		

		if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		
		//
		//  2009/08/06
		pDlg->bEnableScrollBar(  TRUE  );
		pDlg->doLayout(  );
		//
		pDlg->ShowWindow(  SW_SHOW  );
		
		//
		pDlg->doLayout(  );

		//
		pProcInfo->chromaKey.hWnd_dlgImg  =  pDlg->m_hWnd;
	}

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}

	traceLogA(  "viewDlgImg leaves with %s",  iErr  ?  "Failed"  :  "OK"  );

	return  iErr;
}




// CDlgImg dialog

IMPLEMENT_DYNAMIC(CDlgImg, CDlgDesktopsMon)

CDlgImg::CDlgImg(CWnd* pParent /*=NULL*/)
	: CDlgDesktopsMon( pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	//  2014/04/06
	m_var.ucbAutoClip  =  FALSE;

}

CDlgImg::~CDlgImg()
{
	freeDatas(  );
}


 BOOL  CDlgImg::bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_menu,  MIS_CNT  *  pMisCnt,  unsigned  short  usCnt_row,  unsigned  short  usCnt_col,  unsigned  int  uiInitW_pc,  unsigned  int  uiInitH_pic  )
{
	BOOL							bRet		=	FALSE;
	QY_MC						*	pQyMc		=	QY_GET_GBUF(  );

#if  0
	if  (  !pMisCnt  )  {
		traceLogA(  "dlgDynBmps: bSetDlgInfo failed. pMisCnt is null"  );
		return  FALSE;
	}
#endif

	if  (  !iResId_menu  )  iResId_menu  =  CONST_resId_menu_dlgVideos;

	if  (  !::CDlgDesktopsMon::bSetDlgInfo(  iWndContentType,  iSubType,  iResId_menu,  usCnt_row,  usCnt_col,  uiInitW_pc,  uiInitH_pic  )  )  goto  errLabel;

	if  (  title  )  lstrcpyn(  m_var.title,  title,  mycountof(  m_var.title  )  );
	//  m_var.pMisCnt  =  pMisCnt;
	//

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 int  CDlgImg::sizeAllControls(  RECT  rcParam  )
{
	int					iErr	=	-1;
	int					i;
	int					idc;
	QY_DMITEM		*	pItem;
	CWnd			*	pCtrl;
	CDlgDesktopsMon	*	pBase	=	this;

	//
	CDlgDesktopsMon::sizeAllControls(  rcParam  );

	//
	for  (  i  =  0;  i  <  pBase->m_var.usCnt_row  *  pBase->m_var.usCnt_col;  i  ++  )  {
		 pItem  =  &pBase->m_var.pIdcTable[i];
		 idc  =  (  int  )pItem->des;		
		 pCtrl  =  GetDlgItem(  idc  );
		 if  (  !pCtrl  )  goto  errLabel;
		 pCtrl->Invalidate(  TRUE  );
		 //  pCtrl->UpdateWindow(  );

		 unsigned  char  ucbLocalAv  =  TRUE;

		 if  (  ucbLocalAv  )  {

			 RECT	rc;			 
			 ::GetClientRect(  pCtrl->m_hWnd,  &rc  );
			 int	iX,  iY,  iW,  iH;
			 iX  =  rc.left;
			 iY  =  rc.top;
			 iW  =  rc.right  -  rc.left;
			 iH  =  rc.bottom  -  rc.top;

			 //  
			 myGetImageInfo_2d(  TRUE,  m_var.ucbAutoClip,  m_var.images.mems[i].iW_org,  m_var.images.mems[i].iH_org,  0,  0,  iW,  iH,  (  unsigned  int  *  )&m_var.images.mems[i].iW_i,  (  unsigned  int  *  )&m_var.images.mems[i].iH_i,  &m_var.images.mems[i].iX_src_i,  &m_var.images.mems[i].iY_src_i,  &m_var.images.mems[i].iX_dst,  &m_var.images.mems[i].iY_dst,  &m_var.images.mems[i].iW_dst,  &m_var.images.mems[i].iH_dst  );
			 }
		 else  {
			   //  
			   RECT	rc;
			   ::GetClientRect(  pCtrl->m_hWnd,  &rc  );
			   int	iX,  iY,  iW,  iH;
			   iX  =  rc.left;
			   iY  =  rc.top;
			   iW  =  rc.right  -  rc.left;
			   iH  =  rc.bottom  -  rc.top;

			   //
			   getCapImages(  m_var.ucbAutoClip,  iX,  iY,  iW,  iH,  NULL,  &m_var.images  );
		 }


	}

	iErr  =  0;
errLabel:
	return  iErr;
}


 int  CDlgImg:: mallocDatas(  )
 {
	 int	iErr  =  -1;

	 if (  !m_var.msg.bih.biWidth  ||  !m_var.msg.bih.biHeight  )  return  -1;
	 if  (  m_var.msg.bih.biBitCount  !=  32  )  return  -1;

	 if  (  m_var.datas.pData_org  )  return  -1;

	 int  size  =  m_var.msg.bih.biWidth  *  m_var.msg.bih.biHeight  *  sizeof(  KEYING_pix_help  );
	 m_var.keyingCtx.pPixes  =  (  KEYING_pix_help  *  )mymalloc(  size  );
	 if  (  !m_var.keyingCtx.pPixes  )  goto  errLabel;

	 //	
	 m_var.datas.pData_org  =  (  BYTE  *  )mymalloc(  m_var.msg.bih.biSizeImage  );			
	 if  (  !m_var.datas.pData_org  )  goto  errLabel;
	 m_var.datas.pData  =  (  BYTE  *  )mymalloc(  m_var.msg.bih.biSizeImage  );
	 if  (  !m_var.datas.pData  )  goto  errLabel;
	 //
	 m_var.datas.pData_tmp  =  (  BYTE  *  )mymalloc(  m_var.msg.bih.biSizeImage  );
	 if  (  !m_var.datas.pData_tmp  )  goto  errLabel;
	 //
	 m_var.datas.pData_mask  =  (  BYTE  *  )mymalloc(  m_var.msg.bih.biSizeImage  );
	 if  (  !m_var.datas.pData_mask  )  goto  errLabel;
	 m_var.datas.pData_bg  =  (  BYTE  *  )mymalloc(  m_var.msg.bih.biSizeImage  );
	 if  (  !m_var.datas.pData_bg  )  goto  errLabel;
	 m_var.datas.pData_blend  =  (  BYTE  *  )mymalloc(  m_var.msg.bih.biSizeImage  );
	 if  (  !m_var.datas.pData_blend  )  goto  errLabel;



	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 freeDatas(  );
	 }

	 return  iErr;

 }
	
 void  CDlgImg::freeDatas(  )
 {
	 MACRO_safeFree(  m_var.keyingCtx.pPixes  );

	 MACRO_safeFree(  m_var.datas.pData_org  );
	 MACRO_safeFree(  m_var.datas.pData  );
	 MACRO_safeFree(  m_var.datas.pData_tmp  );
	 MACRO_safeFree(  m_var.datas.pData_mask  );
	 MACRO_safeFree(  m_var.datas.pData_bg  );
	 MACRO_safeFree(  m_var.datas.pData_blend  );

 }


void CDlgImg::DoDataExchange(CDataExchange* pDX)
{
	CDlgDesktopsMon::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImg, CDlgDesktopsMon)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_DRAWITEM()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CDlgImg message handlers

BOOL CDlgImg::OnInitDialog()
{

	CDlgDesktopsMon				*	pBase	=	this;
	QY_DMITEM					*	pItem	=	pBase->m_var.pIdcTable;

	m_var.idc  =  (  int  )pItem[0].des;

	CDlgDesktopsMon::OnInitDialog();

	// TODO:  Add extra initialization here
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );	
	if  (  !pFuncs  )  goto  errLabel;
	
	SetWindowText(  m_var.title  );



	//
	viewChromaKeyCfg(  m_hWnd,  m_hWnd,  this->getWndContentType(  ),  m_var.idc  );
	
	//
	CWnd  *  pCtrl  =  NULL;
	pCtrl  =  GetDlgItem(  m_var.idc  );
	if  (  pCtrl  )  {
		pCtrl->ModifyStyle(  SS_TYPEMASK,  SS_OWNERDRAW  );
	}
	//	

	//  2011/03/25
	m_var.guiData.bInited  =  TRUE;


errLabel:

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

 int  dlgImg_testKeying(  HWND  hDlgImg  )
{
	int			iErr	=	-1;

	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	CDlgImg  *  pDlgImg  =  (  CDlgImg  *  )CWnd::FromHandlePermanent(  hDlgImg  );
	if  (  !pDlgImg  )  return  -1;

	HWND			m_hWnd	=	hDlgImg;
	DLG_img_var  &  m_var  =  pDlgImg->m_var;

	CDlgDesktopsMon  * pBase  =  pDlgImg;

	DLG_desktopsMon_var  *  pBaseVar  =  &pBase->m_var;


	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );	
	if  (  !pFuncs  )  goto  errLabel;
	
	CDlgChromaKeyCfg  *  pTool  =  (  CDlgChromaKeyCfg  *  )CWnd::FromHandlePermanent(  m_var.hTool  );	
	if  (  !pTool  )  goto  errLabel;


	if  (  pFuncs->imgProcess.pf_bUseChromaKey(  )  )  goto  errLabel;	
	
	if  (  !pTool->m_var.bKeyingAFrame  )  goto  errLabel;						  
	
	if  (  !m_var.datas.pData_org  )  goto  errLabel;

	m_var.bKeyed  =  FALSE;	

	if  (  !pFuncs->imgProcess.pf_test_procChromaKey(  pProcInfo,  &m_var.keyingCtx,  &pTool->m_var.cfg,  &m_var.msg.bih,  &m_var.datas,  FALSE  )  )  {	
		m_var.bKeyed  =  TRUE;						  
	}


	//	
	::InvalidateRect(  ::GetDlgItem(  m_hWnd,  m_var.idc  ),  NULL,  TRUE  );


	iErr  =  0;
errLabel:
	return  iErr;


}

 LRESULT  CDlgImg::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	long				lRet				=					-1;
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	//  int					iWndContentType		=					getWndContentType(  );
	MC_VAR_isCli		*	pProcInfo			=				QY_GET_procInfo_isCli(  );	//  	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	if  (  !pComm  )  return  -1;

	int					iErr	=	-1;
	CDlgDesktopsMon  * pBase  =  this;

	DLG_desktopsMon_var  *  pBaseVar  =  &pBase->m_var;

	switch  (  pComm->uiType  )  {
			case  CONST_misMsgType_procVideo_qmc:  {
				  MIS_MSG_procVideo_qmc		*	pMsg			=	(  MIS_MSG_procVideo_qmc  *  )pComm;
				  BOOL							bUseDxSurface	=	FALSE;	//  m_var.bUseDirectX;
				
				  #ifdef  __DEBUG__
						  //  bUseDxSurface  =  FALSE;
				  #endif

				  //				  				  
				  {
					  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
					  if  (  !pFuncs  )  goto  errLabel;

					  CDlgChromaKeyCfg  *  pTool  =  (  CDlgChromaKeyCfg  *  )CWnd::FromHandle(  m_var.hTool  );
					  if  (  !pTool  )  goto  errLabel;

					  if  (  !pFuncs->imgProcess.pf_bUseChromaKey(  )  )  {
						  if  (  pTool->m_var.bKeyingAFrame  )  {

							  //  2013/10/08
							  //  if  (  pMsg->ucbAlphaed  )  goto  errLabel;

							  //
							  if  (  m_var.datas.pData_org  )  {
								  iErr  =  0;  goto  errLabel;
							  }

							  //							  				
							  int  idc_dst  =  m_var.idc;
							  old_freeCapImages(  this->m_hWnd,  m_var.idc,  &m_var.images,  old_M_GetDlgItem(  m_hWnd,  idc_dst  ),  &m_var.hDc,  _T(  "dlgImg.OnQyComm.453"  ));
							  
							  //
							  //  memcpy(  &m_var.msg.bih,  &pMsg->bih,  sizeof(  m_var.msg.bih  )  );
							  makeBmpInfoHeader_rgb(  32,  pMsg->bih.biWidth,  pMsg->bih.biHeight,  &m_var.msg.bih  );
							  if  (  m_var.msg.bih.biSizeImage  <  M_sizeImage(  m_var.msg.bih.biBitCount,  m_var.msg.bih.biWidth,  m_var.msg.bih.biHeight  )  )  goto  errLabel;


							  //
							  if  (  mallocDatas(  )  )  goto  errLabel;							 			  

							  //
							  switch  (  pMsg->bih.biBitCount  )  {
									  case  24:
										      rgb24To32(  (  BYTE  *  )pMsg->pkt.memory.m_pBuf,  m_var.datas.pData_org,  m_var.msg.bih.biWidth,  m_var.msg.bih.biHeight  );
											  break;
									  default:
											 #ifdef  __DEBUG__
													 traceLog(  _T(  "dlgImg::OnQyComm failed, bih.bits err"  )  );
											 #endif
											 goto  errLabel;
							  }
							  //  memcpy(  m_var.pData_org,  pMsg->memory.m_pBuf,  m_var.msg.bih.biSizeImage  );						
							  m_var.bKeyed  =  FALSE;
							  
							  if  (  !pFuncs->imgProcess.pf_test_procChromaKey(  pProcInfo,  &m_var.keyingCtx,  &pTool->m_var.cfg,  &m_var.msg.bih,  &m_var.datas,  FALSE  )  )  {							  
								  m_var.bKeyed  =  TRUE;
							  }
					
							  //
							  ::InvalidateRect(  ::GetDlgItem(  m_hWnd,  m_var.idc  ),  NULL,  TRUE  );

							  //
							  iErr  =  0;  goto  errLabel;
						  }
					  }					  						
				  }


				  //
				  freeDatas(  );
					
				  //
				  if  (  m_var.msg.bih.biWidth  !=  pMsg->bih.biWidth
					  ||  m_var.msg.bih.biHeight  !=  pMsg->bih.biHeight
					  ||  m_var.msg.uiTranNo_openAvDev  !=  pMsg->uiTranNo_openAvDev  )
				  {
					  int  idc_dst  =  m_var.idc;
					  old_freeCapImages(  this->m_hWnd,  m_var.idc,  &m_var.images,  old_M_GetDlgItem(  m_hWnd,  idc_dst  ),  &m_var.hDc,  _T(  "dlgImg.OnQyComm.501"  ));
				  }

				  //
				  memcpy(  &m_var.msg,  pMsg,  sizeof(  m_var.msg  )  );
				  

				  //  2011/11/27. 在全高清视频时，在笔记本上显示不了了，不能使用dx.					
				  bUseDxSurface  =  FALSE;
				  
				  //					
				  //  if  (  drawCapImages(  this->m_hWnd,  m_var.idc,  &m_var.hDc,  NULL,  FALSE,  pMsg,  0,  0,  m_var.iW_pic,  m_var.iH_pic,  NULL,  NULL,  &m_var.images,  bUseDxSurface,  FALSE  )  )  goto  errLabel;

				  ZONE_PARAM  *  pZoneParam  =  &m_var.zoneParam;
				  //  if  (  drawCapImages(  m_hWnd,  m_var.idc,  &m_var.hDc,  NULL,  TRUE,  m_var.ucbAutoClip,  pMsg,  0,  0,  pBaseVar->mems[0].iW,  pBaseVar->mems[0].iH,  NULL,  pZoneParam,  &m_var.images,  bUseDxSurface,  FALSE  )  )  goto  errLabel;
				  HWND  hWnd_src  =  old_M_GetDlgItem(  m_hWnd,  m_var.idc  );
				  HWND  hWnd_dst  =  hWnd_src;
				  if  (  drawCapImages(  pProcInfo->pQyMc,  hWnd_src,  m_var.ucbAutoClip,  pMsg,  0,  0,  pBaseVar->mems[0].iW,  pBaseVar->mems[0].iH,  NULL,  pZoneParam,  &m_var.images,  hWnd_dst,  &m_var.hDc,  NULL  )  )  goto  errLabel;

				  }
												   
				  break;
			default:
					break;
	}

		lRet  =  QY_RC_WMOK;

errLabel:

	return  lRet;
 }


 void CDlgImg::OnDestroy()
{


	//
	int  idc_dst  =  m_var.idc;
	old_freeCapImages(  this->m_hWnd,  m_var.idc,  &m_var.images,  old_M_GetDlgItem(  m_hWnd,  idc_dst  ),  &m_var.hDc,  _T(  "dlgImg.OnDestroy.541"  ));

	CDlgDesktopsMon::OnDestroy();

	// TODO: Add your message handler code here
}


 void CDlgImg::OnPaint()
{
	
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDlgDesktopsMon::OnPaint() for painting messages
	//

#if  0
	CWnd  *  pCtrl  =  GetDlgItem(  IDC_STATIC_pic0  );
	if  (  pCtrl  )  {
		pCtrl->Invalidate(  FALSE  );
	}
#endif
	

	return;
}

 void CDlgImg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default

	if  (  nIDCtl  ==  m_var.idc  )  {
	
		//
		CDlgDesktopsMon  * pBase  =  this;
		
		DLG_desktopsMon_var  *  pBaseVar  =  &pBase->m_var;
		
		m_var.msg.pkt.memory.m_pBuf  =  (  char  *  )(  m_var.bKeyed  ?  m_var.datas.pData_blend  :  m_var.datas.pData_org  );
		

		//  2011/11/27. 在全高清视频时，在笔记本上显示不了了，不能使用dx.					
		BOOL			  bUseDxSurface  =  FALSE;
		
		HDC  *  phDc  =  &m_var.hDc;
		//  phDc  =  &lpDrawItemStruct->hDC;

		//  drawCapImages(  m_hWnd,  m_var.idc,  phDc,  NULL,  TRUE,  m_var.ucbAutoClip,  &m_var.msg,  0,  0,  pBaseVar->mems[0].iW,  pBaseVar->mems[0].iH,  NULL,  NULL,  &m_var.images,  bUseDxSurface,  FALSE  );
		HWND  hWnd_src  =  old_M_GetDlgItem(  m_hWnd,  m_var.idc  );
		HWND  hWnd_dst  =  hWnd_src;
		drawCapImages(  g_pQyMc,  hWnd_src,  m_var.ucbAutoClip,  &m_var.msg,  0,  0,  pBaseVar->mems[0].iW,  pBaseVar->mems[0].iH,  NULL,  NULL,  &m_var.images,  hWnd_dst,  &m_var.hDc,  NULL  );
		
	
		return;
	}
	
	CDlgDesktopsMon::OnDrawItem(nIDCtl, lpDrawItemStruct);

}



 int  dlgImg_pickColor(  HWND  hDlgImg  )
{
	// TODO: Add your message handler code here and/or call default

	int		iErr	=	-1;
	HWND  m_hWnd  =  hDlgImg;
	CDlgImg  *  pDlgImg  =  (  CDlgImg  *  )CWnd::FromHandlePermanent(  m_hWnd  );
	if  (  !pDlgImg  )  return  -1;

	DLG_img_var  &  m_var  =  pDlgImg->m_var;

	DWORD dwPos = GetMessagePos();

	/* Convert the co-ords into a CPoint structure */
	CPoint point1( GET_X_LPARAM( dwPos ), GET_Y_LPARAM( dwPos ) );
	CPoint spt;
	HWND	hCtrl;

	CAP_images	*	pImages;
	CAP_image	*	pImg;
	int  i;
				
	spt = point1;	
	hCtrl  =  ::GetDlgItem(  m_hWnd,  m_var.idc  );
	if  (  !hCtrl  )  goto  errLabel;
	::MapWindowPoints(  NULL,  hCtrl,  &spt,  1  );

	if  (  !m_var.datas.pData_org  )  goto  errLabel;

	//	
	pImages  =  &m_var.images;
			
	for  (  i  =  0;  i  <  mycountof(  pImages->mems  );  i  ++  )  {
			 pImg  =  &pImages->mems[i];
			 if  (  pImg->iW_org  &&  pImg->iH_org  )  {
				 if  (  pImg->iX_dst  <=  spt.x  
					 &&  (  int  )(  pImg->iX_dst  +  pImg->iW_dst  )  >=  spt.x
					 &&  pImg->iY_dst  <=  spt.y
					 &&  (  int  )(  pImg->iY_dst  +  pImg->iH_dst  )  >=  spt.y  )			  
				 {
					 break;			  
				 }		  
			 }	 	
	}
	

	if  (  i  >=  mycountof(  pImages->mems  )  )  goto  errLabel;
	
	
	
	pImg  =  &pImages->mems[i];
	
	//
		BITMAPINFOHEADER	*	pBih  =  &m_var.msg.bih;

		if  (  pBih->biBitCount  !=  32  )  goto  errLabel;

		//
		int				lineBytes_pic	=	M_lineBytes_rgb(  pBih->biBitCount,  pBih->biWidth  );
		int				rgbIncrement	=	pBih->biBitCount  /  8;

		//
		int  img_i  =  spt.x  -  pImg->iX_dst;
		int  img_j  =  spt.y  -  pImg->iY_dst;

		if  (  img_i  <  0  ||  img_i  >=  pBih->biWidth  )  goto  errLabel;
		if  (  img_j  <  0  ||  img_j  >=  pBih->biHeight  )  goto  errLabel;

		

		int  real_i  =  img_i;	//  (  bmpInfo.bmiHeader.biWidth  -  i  -  1  );			
		int  real_j  =  (  pBih->biHeight  -  img_j  -  1  );
		//
		int  pixIndex  =  pBih->biWidth  *  real_j  +  real_i;				
		int  rgbIndex  =  lineBytes_pic  *  real_j  +  real_i  *  rgbIncrement;

		TCHAR	tBuf[256]  =  _T(  ""  );


#ifdef  __DEBUG__
		traceLog(  _T(  "x %d, y %d,  i  %d. img %d,%d. real_i,real_j %d,%d"  ),  spt.x,  spt.y,  i,  spt.x  -  pImg->iX_dst,  spt.y  -  pImg->iY_dst,  real_i,  real_j  );	
#endif


		//
		CDlgChromaKeyCfg  *  pTool  =  (  CDlgChromaKeyCfg  *  )CWnd::FromHandle(  m_var.hTool  );
		if  (  !pTool  )  goto  errLabel;


		//
		BYTE  *  pBuf  =  m_var.datas.pData_org;
		BYTE  *  rgb;
		BYTE  r,  g,  b;
		BYTE  a;
		BYTE  h,  s,  l;
		unsigned char  ucKeyIndex;
		float dDistance;

		rgb  =  (  (  BYTE  *  )pBuf  )  +  rgbIndex;		
		r  =  rgb[2];
		g  =  rgb[1];				 
		b  =  rgb[0];
		
		pTool->m_var.color_org  =  RGB(  r,  g,  b  );
		::InvalidateRect(  pTool->m_static_color_org.m_hWnd,  NULL,  TRUE  );

		//  ColorRGBToHLS(      RGB(  r,  g,  b  ),  &h,  &l,  &s  );					  
		convert_rgb_to_key_pixel(  r,  g,  b,  &h,  &s,  &l  );
		
		MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
		if  (  !pProcInfo  )  goto  errLabel;
		FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
		if  (  !pFuncs  )  goto  errLabel;

		float  fd;
		pFuncs->imgProcess.pf_getColorDistance_keys(  h, s,  &pTool->m_var.cfg,  &ucKeyIndex,  &dDistance  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "   rgb(%d,%d,%d),hsl(%d,%d,%d),key%d,distance %.2f->"  ),  (  int  )r,  (  int  )g,  (  int  )b, (int)h,(int)s,(int)l,(int)(ucKeyIndex+1), dDistance   );

		if  (  m_var.bKeyed  )  {

			//
			pBuf  =  m_var.datas.pData_mask;
			
			rgb  =  (  (  BYTE  *  )pBuf  )  +  rgbIndex;	
			a  =  rgb[3];
			r  =  rgb[2];
			g  =  rgb[1];				 
			b  =  rgb[0];


			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s Mask (%d,%d,%d,%d)->"  ),  tBuf,  (  int  )a,  (  int  )r,  (  int  )g,  (  int  )b  );


			//
			pBuf  =  m_var.datas.pData;
			
			rgb  =  (  (  BYTE  *  )pBuf  )  +  rgbIndex;	
			a  =  rgb[3];
			r  =  rgb[2];
			g  =  rgb[1];				 
			b  =  rgb[0];


			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s Data (%d,%d,%d,%d)->"  ),  tBuf,  (  int  )a,  (  int  )r,  (  int  )g,  (  int  )b  );
			//
			pBuf  =  m_var.datas.pData_blend;
			
			rgb  =  (  (  BYTE  *  )pBuf  )  +  rgbIndex;	
			a  =  rgb[3];
			r  =  rgb[2];
			g  =  rgb[1];				 
			b  =  rgb[0];

			pTool->m_var.color_keyed  =  RGB(  r,  g,  b  );
			::InvalidateRect(  pTool->m_static_color_keyed.m_hWnd,  NULL,  TRUE  );
			//  ColorRGBToHLS(      RGB(  r,  g,  b  ),  &h,  &l,  &s  );					  
			convert_rgb_to_key_pixel(  r,  g,  b,  &h,  &s,  &l  );

			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s Blend (%d,%d,%d,%d)(%d,%d,%d)"  ),  tBuf,  (  int  )a,  (  int  )r,  (  int  )g,  (  int  )b,(int)h,(int)s,(int)l  );


		}
		
#ifdef  __DEBUG__
#if 0
		real_i_btnDown  =  real_i;
		real_j_btnDown  =  real_j;				
		img_i_btnDown  =  img_i;				
		img_j_btnDown  =  img_j;
#endif

		//		
		traceLog(  _T(  "real_i,real_j %d,%d. img_i,img_j %d,%d"  ),  real_i,  real_j,  img_i,  img_j  );
		traceLog(  _T(  "%s"  ),  tBuf  );
#endif

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  _T(  ""  )  );
	}
	::SetDlgItemInt(  m_var.hTool,  IDC_EDIT_x,  img_i,  FALSE  );
	::SetDlgItemInt(  m_var.hTool,  IDC_EDIT_y,  img_j,  FALSE  );
	::SetDlgItemText(  m_var.hTool,  IDC_STATIC_desc,  tBuf  );
	return  iErr;
}


 int  dlgImg_xyColor(  HWND  hDlgImg,  unsigned int img_x,  unsigned int img_y  )
{
	// TODO: Add your message handler code here and/or call default

	int		iErr	=	-1;
	HWND  m_hWnd  =  hDlgImg;
	CDlgImg  *  pDlgImg  =  (  CDlgImg  *  )CWnd::FromHandlePermanent(  m_hWnd  );
	if  (  !pDlgImg  )  return  -1;

	DLG_img_var  &  m_var  =  pDlgImg->m_var;


	CAP_images	*	pImages;
	CAP_image	*	pImg;
	int  i;

	if  (  !m_var.datas.pData_org  )  goto  errLabel;

	//	
	pImages  =  &m_var.images;
	//
		BITMAPINFOHEADER	*	pBih  =  &m_var.msg.bih;

		if  (  pBih->biBitCount  !=  32  )  goto  errLabel;

		//
		int				lineBytes_pic	=	M_lineBytes_rgb(  pBih->biBitCount,  pBih->biWidth  );
		int				rgbIncrement	=	pBih->biBitCount  /  8;

		//
		//  int  img_i  =  spt.x  -  pImg->iX;
		//  int  img_j  =  spt.y  -  pImg->iY;

		if  (  img_x  <  0  ||  img_x  >=  pBih->biWidth  )  goto  errLabel;
		if  (  img_y  <  0  ||  img_y  >=  pBih->biHeight  )  goto  errLabel;


		int  real_i  =  img_x;	//  (  bmpInfo.bmiHeader.biWidth  -  i  -  1  );			
		int  real_j  =  (  pBih->biHeight  -  img_y  -  1  );
		//
		int  pixIndex  =  pBih->biWidth  *  real_j  +  real_i;				
		int  rgbIndex  =  lineBytes_pic  *  real_j  +  real_i  *  rgbIncrement;

		TCHAR	tBuf[256]  =  _T(  ""  );


#ifdef  __DEBUG__
		//  traceLog(  _T(  "x %d, y %d,  i  %d. img %d,%d. real_i,real_j %d,%d"  ),  spt.x,  spt.y,  i,  spt.x  -  pImg->iX,  spt.y  -  pImg->iY,  real_i,  real_j  );	
#endif


		//
		CDlgChromaKeyCfg  *  pTool  =  (  CDlgChromaKeyCfg  *  )CWnd::FromHandle(  m_var.hTool  );
		if  (  !pTool  )  goto  errLabel;


		//
		BYTE  *  pBuf  =  m_var.datas.pData_org;
		BYTE  *  rgb;
		BYTE  r,  g,  b;
		BYTE  a;
		BYTE  h,  s,  l;
		unsigned char  ucKeyIndex;
		float dDistance;

		rgb  =  (  (  BYTE  *  )pBuf  )  +  rgbIndex;		
		r  =  rgb[2];
		g  =  rgb[1];				 
		b  =  rgb[0];
		
		pTool->m_var.color_org  =  RGB(  r,  g,  b  );
		::InvalidateRect(  pTool->m_static_color_org.m_hWnd,  NULL,  TRUE  );

		//  ColorRGBToHLS(      RGB(  r,  g,  b  ),  &h,  &l,  &s  );					  
		convert_rgb_to_key_pixel(  r,  g,  b,  &h,  &s,  &l  );
		
		MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );	
		if  (  !pProcInfo  )  goto  errLabel;	
		FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
		if  (  !pFuncs  )  goto  errLabel;

		pFuncs->imgProcess.pf_getColorDistance_keys(  h, s,  &pTool->m_var.cfg,  &ucKeyIndex,  &dDistance  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "   rgb(%d,%d,%d),hsl(%d,%d,%d),key%d,distance %.2f->"  ),  (  int  )r,  (  int  )g,  (  int  )b, (int)h,(int)s,(int)l,(int)(ucKeyIndex+1), dDistance   );

		if  (  m_var.bKeyed  )  {

			//
			pBuf  =  m_var.datas.pData_mask;
			
			rgb  =  (  (  BYTE  *  )pBuf  )  +  rgbIndex;	
			a  =  rgb[3];
			r  =  rgb[2];
			g  =  rgb[1];				 
			b  =  rgb[0];

			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s Mask (%d,%d,%d,%d)->"  ),  tBuf,  (  int  )a,  (  int  )r,  (  int  )g,  (  int  )b  );

			//
			pBuf  =  m_var.datas.pData;
			
			rgb  =  (  (  BYTE  *  )pBuf  )  +  rgbIndex;	
			a  =  rgb[3];
			r  =  rgb[2];
			g  =  rgb[1];				 
			b  =  rgb[0];


			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s Data (%d,%d,%d,%d)->"  ),  tBuf,  (  int  )a,  (  int  )r,  (  int  )g,  (  int  )b  );

			//
			pBuf  =  m_var.datas.pData_blend;
			
			rgb  =  (  (  BYTE  *  )pBuf  )  +  rgbIndex;	
			a  =  rgb[3];
			r  =  rgb[2];
			g  =  rgb[1];				 
			b  =  rgb[0];

			pTool->m_var.color_keyed  =  RGB(  r,  g,  b  );
			::InvalidateRect(  pTool->m_static_color_keyed.m_hWnd,  NULL,  TRUE  );
			//  ColorRGBToHLS(      RGB(  r,  g,  b  ),  &h,  &l,  &s  );					  
			convert_rgb_to_key_pixel(  r,  g,  b,  &h,  &s,  &l  );

			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s Blend (%d,%d,%d,%d)(%d,%d,%d)"  ),  tBuf,  (  int  )a,  (  int  )r,  (  int  )g,  (  int  )b,(int)h,(int)s,(int)l  );
			

		}
		
#ifdef  __DEBUG__
#if 0
		real_i_btnDown  =  real_i;
		real_j_btnDown  =  real_j;
		img_i_btnDown  =  img_x;
		img_j_btnDown  =  img_y;
#endif

		traceLog(  _T(  "real_i,real_j %d,%d"  ),  real_i,  real_j  );
		traceLog(  _T(  "%s"  ),  tBuf  );
#endif


	
		
	

	iErr  =  0;

errLabel:

	if  (  iErr  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  _T(  ""  )  );
	::SetDlgItemText(  m_var.hTool,  IDC_STATIC_desc,  tBuf  );
	return  iErr;
}

void CDlgImg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	dlgImg_pickColor(  m_hWnd  );

errLabel:

	CDlgDesktopsMon::OnLButtonDown(nFlags, point);
}
