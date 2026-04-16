#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyCusResTemp.h"
#include	"qnmCommProc_mis.h"


int  getCountryCode(  char  *  countryCode,  unsigned  int  size  )
{
	safeStrnCpy(  (char*)"86",  countryCode,  mycountof(  countryCode  )  );
	return  0;
}


#if  10	//  2013/01/16
 //  ÒÔÏÂ2¸öº¯ÊýÔÚÃ¿¸öÊµÊ±Ë¢ÐÂµÄ´°¿ÚÖÐµ÷ÓÃ£¬ÒÔ½¨Á¢´°¿ÚÔªËØºÍmessengerµÄ¶ÔÓ¦¹ØÏµ
  int  initMcCtxDisplayedWnd(  CCtxQyMc  *  pQyMc,  HWND  hWnd,  LPCTSTR  wndName,  MC_CTX_DISPLAYEDWND  *  pCtx  )
 {
	 int		iErr	=	-1;
	 //QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	 int		len		=	0;
	 
	 if  (  !pCtx  ||  !hWnd  )  return  -1;

	 memset(  pCtx,  0,  sizeof(  pCtx[0]  )  );

	 if  (  pQyMc->cfg.usMaxDisplayedElemsPerWnd  &&  getDisplayQ(  pQyMc,  0,  0  )  )  {
		 if  (  initGenericQ(  _T(  "leftViewObjQ"  ),  0,  0,  pQyMc->cfg.usMaxDisplayedElemsPerWnd,  mymalloc,  myfree,  &pCtx->displayedElemQ  )  )  goto  errLabel;
		 pCtx->bQInited  =  TRUE;
		 //
		 len  =  pQyMc->cfg.usMaxDisplayedElemsPerWnd  *  sizeof(  void  *  );
		 //
		 //  m_var.ppSorted_byHandle  =  (  void  **  )mymalloc(  len  );
		 //  if  (  !m_var.ppSorted_byHandle  )  goto  errLabel;
		 //  memset(  m_var.ppSorted_byHandle,  0,  len  );
		 //
		 pCtx->ppDisplayedElems_sortedByKey  =  (  void  **  )mymalloc(  len  );
		 if  (  !pCtx->ppDisplayedElems_sortedByKey  )  goto  errLabel;
		 memset(  pCtx->ppDisplayedElems_sortedByKey,  0,  len  );

		 //
		 MIS_MSG_DISPLAYEDELEM_QMC	msg;
		 memset(  &msg,  0,  sizeof(  msg  )  );
		 msg.uiType  =  CONST_misMsgType_displayedElem_qmc;
		 msg.elemU.wndInfo.uiType  =  CONST_displayedElemType_wndInfo;
		 msg.elemU.wndInfo.hWnd  =  hWnd;
		 if  (  wndName  )  lstrcpyn(  msg.elemU.wndInfo.wndName, wndName,  mycountof(  msg.elemU.wndInfo.wndName  )  );
		 if  (  qPostMsg(  &msg,  sizeof(  msg  ),  getDisplayQ(  pQyMc,  0,  0  ),  _T(  "initMcCtxDisplayedWnd"  )  )  )  goto  errLabel;

	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 exitMcCtxDisplayedWnd(  pQyMc,  hWnd,  pCtx  );
	 }
	 return  iErr;
 }

  void  exitMcCtxDisplayedWnd(  CCtxQyMc  *  pQyMc,  HWND  hWnd,  MC_CTX_DISPLAYEDWND  *  pCtx )
{
	// QY_MC		*	pQyMc	=	QY_GET_GBUF(  );

	 if  (  !pCtx  ||  !hWnd  )  return;

	 if  (  getDisplayQ(  pQyMc,  0,  0  )  )  {
		//  ÏÈ·¢ËÍµ½displayQ½«displayedObjÊÍ·Åµô
		MIS_MSG_DISPLAYEDELEM_QMC	msg;
		memset(  &msg,  0,  sizeof(  msg  )  );
		msg.uiType  =  CONST_misMsgType_displayedElem_qmc;
		msg.elemU.wndInfo.uiType  =  CONST_displayedElemType_wndInfo;
		msg.elemU.wndInfo.hWnd  =  hWnd;
		msg.elemU.wndInfo.bClosed  =  TRUE;
		//
		if  (  qPostMsg(  &msg,  sizeof(  msg  ),  getDisplayQ(  pQyMc,  0,  0  ),  _T(  "exitMcCtxDisplayedWnd"  )  )  )  {
			traceLogA(  (char*)  "CLeftView::OnDestry: ·¢ËÍcloseµÄCONST_misMsgType_displayedElem_qmcÏûÏ¢ failed."  );
		}
	}

	//  ÕâÀïÒª¼Ç×¡ÊÍ·Å£¬2007/06/09
	//
	//  if  (  m_var.ppSorted_byHandle  )  {
	//  	free(  m_var.ppSorted_byHandle  );  m_var.ppSorted_byHandle  =  NULL;
	//  }
	if  (  pCtx->ppDisplayedElems_sortedByKey  )  {
		free(  pCtx->ppDisplayedElems_sortedByKey  );  pCtx->ppDisplayedElems_sortedByKey  =  NULL;
	}
	if  (  pCtx->bQInited  )  {
		exitGenericQ(  &pCtx->displayedElemQ  );  pCtx->bQInited  =  FALSE;
	}

	return;

}
 BOOL  mybSetColumns( CCtxQyMc  *  pQyMc, int  iObjType,  QY_COLUMNINFO  *  pColumns,  unsigned  int  maxCnt  )
{
	 BOOL  bRet  =  FALSE;
	 //QY_MC		*  pQyMc	=	QY_GET_GBUF(  );

	 if  (  maxCnt  <  2  )  return  FALSE;
	 pColumns[0].type	=	0;
	 pColumns[0].iDataType  =  0;
	 pColumns[0].fmt  =  LVCFMT_LEFT;
	 pColumns[0].width  =  120;
	 pColumns[1].type  =  -1;

	 switch  (  iObjType  )  {
			 case  CONST_objType_zb:  lstrcpyn(  pColumns[0].label,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pc0_zongBu  ),  sizeof(  pColumns[0].label  )  /  sizeof(  pColumns[0].label[0]  )  );  break;
			 case  CONST_objType_bb:  lstrcpyn(  pColumns[0].label,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pc2_benBu  ),  sizeof(  pColumns[0].label  )  /  sizeof(  pColumns[0].label[0]  )  );  break;
			 case  CONST_objType_dw:  lstrcpyn(  pColumns[0].label,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pc4_danWei  ),  sizeof(  pColumns[0].label  )  /  sizeof(  pColumns[0].label[0]  )  );  break;
			 case  CONST_objType_bm:  lstrcpyn(  pColumns[0].label,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pc8_buMen  ),  sizeof(  pColumns[0].label  )  /  sizeof(  pColumns[0].label[0]  )  );  break;
			 default:
					 goto  errLabel;				 
	 }

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}
#endif