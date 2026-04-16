
#include	"stdafx.h"

#include	"qyPrecomp.h"

#include	<windows.h>
#include	<tchar.h>
#include	<stdlib.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyGuiCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qyLangCommProc.h"
#include	"qnmGuiCommProc.h"
#include	"qnmCustom.h"
#include	"qnmCustomGui.h"
#include	"qwmAllHints.h"

#include	<WtsApi32.h>

//#include	"qyGuiHelpPublic.h"		//  2013/06/09
#include	"qisGuiPublic_public.h"



int  WINAPI  myMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType  );



//
#ifndef  __WINCE__
 int  WINAPI  myMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType  )
{
	DWORD		toInS		=	10;
	TCHAR		title[64]	=	_T(  ""  );

#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "myMessageBox,  test_wince"  )  );
		
#endif

		//  2013/02/16
#ifdef  __isCli__
		return  qyMessageBox(  hWnd,  lpText,  lpCaption,  uType,  10,  NULL  );  
#endif

#ifndef  __APP_qyMc_touchscreen__

		 if  (  bExists_MessageBoxTimeout(  g_pEnv  )  )  {		//  MessageBoxTimeout是一个未公开的api, 如果这个api不支持了，那么就要自己做一个对话框来解决超时退出的问题. 2011/10/04
			 WORD		wLanguageId  =  0;

			 _sntprintf(  title,  mycountof(  title  ),  _T(  "Auto canceled  after %d seconds.."  ),  toInS  );

			 return  myMessageBoxTimeout(  g_pEnv,  hWnd,  lpText,  title,  uType,  wLanguageId,  toInS  *  1000  );
		 }

		 return  MessageBox(  hWnd ,  lpText,  lpCaption,  uType  );
		 //  return  MessageBox(  NULL,  lpText,  lpCaption,  uType  |  MB_TASKMODAL  );
#else
		//  QY_MC	*	pQyMc	=	
		//  _sntprintf(  title,  mycountof(  title  ),  _T(  "%s %d %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_after  ),  toInS,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_seconds  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_automaticallyCanceled  )  );
		_sntprintf(  title,  mycountof(  title  ),  _T(  "Auto canceled  after %d seconds..."  ),  toInS  );
		int			titleLen  =  lstrlen(  title  )  *  sizeof(  TCHAR  );
		TCHAR	*	hint		=	lpText  ?  lpText  :  _T(  ""  );
		int			msgLen		=	lstrlen(  hint  )  *  sizeof(  TCHAR  );
		DWORD		iResp		=	-1;
		
		if  (  myWTSSendMessage(  g_pEnv,  0,  WTS_CURRENT_SESSION,  title,  titleLen,  hint,  msgLen,  uType  |  MB_TOPMOST,  toInS,  &iResp,  TRUE  )  )  return  iResp;
		
		return  iResp;

#endif

}
#endif


//  
extern  "C"  LONG								gQyOldEditProc		=	0;



 extern  "C"  LPARAM  CALLBACK  qyRestrictEditProc(  HWND  hWnd,  UINT  msg,  WPARAM  wParam,  LPARAM  lParam  )
{
	 HWND	hParent		=	NULL;

	 /*
	 if  (  msg  ==  WM_CHAR  &&  wParam  !=  VK_BACK  &&  (  wParam  <  '0'  ||  wParam  >  '9'  )  )  {
		 MessageBeep(  -1  );
		 return  0;
	 }
	 */
	 
	 hParent  =  GetParent(  hWnd  );
	 if  (  !hParent  )  goto  errLabel;

	 if  (  msg  ==  WM_CHAR  )		{
		 UINT						nChar	=	wParam;
		 QY_WMBUF_GETIDCINFO		idcInfo;

		 memset(  &idcInfo,  0,  sizeof(  idcInfo  )  );
		 idcInfo.uiType  =  CONST_qyWmParam_getIdcInfo;
		 idcInfo.hCtrl  =  hWnd;
		 if  (  SendMessage(  hParent,  CONST_qyWm_comm,  0,  (  LPARAM  )&idcInfo  )  !=  CONST_qyWmRc_ok  )  {
			 traceLogA(  (char*)  "qyRestrictEditProc: Ã»ÓÐ´Ó¸¸´°¿ÚÈ¡µÃ¿Ø¼þÐÅÏ¢"  );
			 goto  errLabel;
		 }
		 
		 if  (  nChar  ==  8  )  goto  errLabel;
		 
		 if  (  !__isascii(  nChar  )  )  {
			 if  (  idcInfo.flg  &  CONST_qyIdcFlgPermitZw  )  goto  errLabel;
		 }
		 if  (  qyIsAlpha(  nChar  )  )  {
			 if  (  idcInfo.flg  &  CONST_qyIdcFlgPermitAlpha  )  goto  errLabel;
		 }
		 if  (  nChar  <=  '9'  &&  nChar  >=  '0'  )  {
			 if  (  idcInfo.flg  &  CONST_qyIdcFlgPermitDigit  )  goto  errLabel;
		 }
		 if  (  (  nChar  <=  '9'  &&  nChar  >=  '0'  )  
			 ||  (  nChar  >=  'a'  &&  nChar  <=  'f'  )  
				 ||  (  nChar  >=  'A'  &&  nChar  <=  'F'  )  )  
		 {
			 if  (  idcInfo.flg  &  CONST_qyIdcFlgPermitXdigit  )  goto  errLabel;
		 }
		 if  (  nChar  ==  ','  )  {
			 if  (  idcInfo.flg  &  CONST_qyIdcFlgPermitComma  )  goto  errLabel;
		 }
		 if  (  nChar  ==  ';'  )  {
			 if  (  idcInfo.flg  &  CONST_qyIdcFlgPermitSemicolon  )  goto  errLabel;
		 }
		 if  (  qyIsSpace(  nChar  )  )  {
			 if  (  idcInfo.flg  &  CONST_qyIdcFlgPermitSpace  )  goto  errLabel;
		 }
		 if  (  nChar  ==  '-'  )  {
			 if  (  idcInfo.flg  &  CONST_qyIdcFlgPermitMinus  )  goto  errLabel;
		 }
		 MessageBeep(  0xFFFFFFFF  );
	
		 return  0;
	
	}

	

errLabel:

	 return  CallWindowProc(  (  WNDPROC  )gQyOldEditProc,  hWnd,  msg,  wParam,  lParam  );

}


  extern  "C"  int  getnTables(  QY_IDCITEM  *  pTables[]  )
{
	 int			n		=	0;

	 for  (  ;  *pTables;  pTables  ++  )  {
		  n  ++  ;		  
	 }
	 return  n;
}


  //  ÏÂÃæµÄº¯ÊýÓ¦·ÅÈëqrtPublic¿âÖÐ
 extern  "C"  void  qnmSizeRegToolControls(  QNM_CUSRES_INFO  *  pCusRes,  HWND  hDlg,  QY_IDCITEM  *	 pTotalTable,  QY_IDCITEM  *  pCurTable,  BOOL  bEdit  )
{
	HDWP			hdwp; 
	HWND			hWnd,  prevhWnd		=  NULL;
	int				cnt					=  0;
	QY_IDCITEM	*	pItem				=  NULL;
	QY_IDCITEM  *	tmppItem			=  NULL;
	UINT			uFlags				=  0;
	TCHAR			tBuf[1024];

	
	if  (  !pCurTable  )  return;
	
	for  (  pItem  =  pCurTable;  pItem->idc  !=  -1;  pItem  ++  )  {

		 hWnd = ::GetDlgItem(  hDlg,  pItem->idc  );             
		 if  (  !hWnd  )  {
			 #ifdef  __DEBUG__
				//showIdcItem(  pItem,  "not exists"  );
			 #endif
			 continue;
		 }

		 tmppItem  =  qyGetIdcItemByIdc(  pTotalTable,  pItem->idc  );
		 if  (  tmppItem  )  tmppItem->flg  =  pItem->flg;
			 
		 switch  (  pItem->idcType  )  {
				 case  CONST_qyIdcType_static:	
					   if  (  pItem->des  &&  pItem->des[0]  )  {
						   char  buf[256]  =  "";

						   //  _snprintf(  buf,  sizeof(  buf  ),  "%s%s",  pItem->des,  (  pItem->flg  &  CONST_qyIdcFlgNeeded  )  ?  "*"  :  ""  );
						   myTChar2Str(  pItem->des,  buf  +  strlen(  buf  ),  sizeof(  buf  )  -  strlen(  buf  )  );
						   safeStrnCpy(  (char*)((  pItem->flg  &  CONST_qyIdcFlgNeeded  )  ?  "*"  :  ""),  buf  +  strlen(  buf  ),  sizeof(  buf  )  -  strlen(  buf  )  );
						   SetWindowText(  hWnd,  myStr2TChar1(  buf,  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  )  )  );
					   }
					   break;
				 case  CONST_qyIdcType_edit:  
					   if  (  pItem->des  &&  pItem->des[0]  )  SetWindowText(  hWnd,  pItem->des  );
					   break;
				 case  CONST_qyIdcType_combo:
					   if  (  pItem->iResIdTable  )  {
						   QY_DMITEM	*	pDm  =  NULL;
						   
						   for  (  pDm  =  getResTable(  0,  pCusRes,  pItem->iResIdTable  );  pDm->type  !=  -1;  pDm  ++  )  {
							    SendMessage(  hWnd,  CB_ADDSTRING,  0,  (  LPARAM  )(  pDm->des  ?  pDm->des  :  _T(  ""  )  )    );								    
						   }					
						   if  (  (  int  )pItem->des  !=  -1  )  SendMessage(  hWnd,  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  getResTable(  0,  pCusRes,  pItem->iResIdTable  ),  (  long  )pItem->des  )  );					   
					   }
					   break;
				 case  CONST_qyIdcType_button:
					   if  (  pItem->des  &&  pItem->des[0]  )  SetWindowText(  hWnd,  pItem->des  );
					   break;
				 default:
						break;
		 }
		 
		 #ifdef  __DEBUG__
				 //  showIdcItem(  pItem,  ""  );
		 #endif
	}


	QY_IDCITEM  *	tmppCurTable		=  pTotalTable;

	for  (  pItem  =  tmppCurTable;  pItem->idc  !=  -1;  pItem  ++  )  cnt  ++  ;
	
	// size the tree control accordingly
	hdwp  =  BeginDeferWindowPos(  cnt  ); 

	for  (  pItem  =  tmppCurTable;  pItem->idc  !=  -1;  pItem  ++  )  {

		 hWnd = ::GetDlgItem(  hDlg,  pItem->idc  );             
		 if  (  !hWnd  )  continue;

		 if  (  bEdit  &&  (  pItem->flg  &  CONST_qyIdcFlgOnlyForEdit  )  )  uFlags  =  SWP_SHOWWINDOW;
		 else  if  (  (  bEdit  &&  (  pItem->flg  &  CONST_qyIdcFlgNotForEdit  )  )  ||  (  pItem->flg  &  CONST_qyIdcFlgHide  )  )  uFlags  =  SWP_HIDEWINDOW;
		 else  uFlags  =  SWP_SHOWWINDOW;

		 ::DeferWindowPos(  hdwp, 
							hWnd,  prevhWnd  ?  prevhWnd  :  HWND_TOP, 
							myMulDiv(  pItem->x,  CONST_multiplierOfDlgUnit,  CONST_divisorOfDlgUnit  ),  
							myMulDiv(  pItem->y,  CONST_multiplierOfDlgUnit,  CONST_divisorOfDlgUnit  ),  
							myMulDiv(  pItem->w,  CONST_multiplierOfDlgUnit,  CONST_divisorOfDlgUnit  ),  
							myMulDiv(  pItem->h,  CONST_multiplierOfDlgUnit,  CONST_divisorOfDlgUnit  ),  
							uFlags  );  
		 //  traceLogA(  (char*)  "%s is %s",  pItem->des  ?  pItem->des  :  "",  (  pItem->flg  &  CONST_qyIdcFlgHide  )  ?  "hide"  :  "show"  );
		 prevhWnd  =  hWnd;

  }

	EndDeferWindowPos(  hdwp  );

	return;
}

 extern  "C"  int  procCbSelChange(  QNM_CUSRES_INFO  *  pCusRes,  QY_IDCITEM  *  pTotalTable,  QY_IDCITEM  **  ppTables,  HWND  hDlg,  int  idc,  BOOL  bEdit  )
{
	 int				iCurSel		=  -1;
	 int				nTables		=  0;	
	 QY_IDCITEM		*	pCurTable	=  NULL;

	 if  (  !pTotalTable  ||  !ppTables  )  return  0;
	 nTables  =  getnTables(  ppTables  );
	 if  (  (  iCurSel  =  SendMessage(  GetDlgItem(  hDlg,  idc  ),  CB_GETCURSEL,  0,  0  )  )  ==  CB_ERR  )  return  -1;
	 if  (  iCurSel  >=  nTables  )  return  0;
	 pCurTable  =  ppTables[iCurSel];
	 qnmSizeRegToolControls(  pCusRes,  hDlg,  pTotalTable,  pCurTable,  bEdit  );
	 return  0;
}


 //  if ucbUtf8Îªfalse, ÔòÒÔutf16´æ´¢
//  BOOL  bGetRegInfoFromDlg(  QNM_CUSRES_INFO  *  pCusRes,  HWND  hWnd,  unsigned  char  ucbUtf8,  QNM_REG_INFO  *  pRegInfo  )
 BOOL  bGetRegInfoFromDlg(  QNM_CUSRES_INFO  *  pCusRes,  HWND  hWnd,  QY_IDCITEM  *  gpTable0,  unsigned  char  ucbUtf8,  QNM_REG_INFO  *  pRegInfo  )
{
	BOOL			bRet		=	FALSE;
	QY_IDCITEM	*	pItem		=  NULL;
	QY_IDCITEM	*	tmppItem	=  NULL;
	char			buf[1024];
	char			hint[1024];
	int				index;
	TCHAR			tBuf[2048];
	
	for  (  pItem  =  gpTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  !(  pItem->flg  &  CONST_qyIdcFlgChkNotNull  )  )  continue;
		 if  (  pItem->idcType  !=  CONST_qyIdcType_edit  &&  pItem->idcType  !=  CONST_qyIdcType_combo  )  continue;
		 GetDlgItemText(  hWnd,  pItem->idc,  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  )  );
		 myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );  trim(  buf  );
		 tmppItem  =  qyGetIdcItemByIdc(  gpTable0,  pItem->lIdc  );
		 MACRO_qyAssert(  tmppItem,  _T(  "bGetRegInfoFromDlg: idc is not in gTable0"  )  );
		 myTChar2Str(  tmppItem->des,  hint,  sizeof(  hint  )  );
		 myTChar2Str(  gAllHints.bt,  hint  +  strlen(  hint  ),  sizeof(  hint  )  -  strlen(  hint  )  );			 
		 //  MACRO_chkNotNull(  pItem->idc,  buf,  hint  );		//  ±»ÏÂÃæ´úÂëËùÌæ´ú	 
		 if  (  !buf[0]  )  {															
			 MessageBeep(  -1  );													
			 if  (  hint  &&  hint[0]  )  myMessageBox(  NULL,  myStr2TChar1(  hint,  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  )  ),  _T(  "Qycx"  ),  MB_OK  );						
			 SetFocus(  GetDlgItem( hWnd,  pItem->idc )  );
			 goto  errLabel;
		 }								
	}								 	
		
	SendMessage(  GetDlgItem(  hWnd,  IDOK  ),  WM_ENABLE,  FALSE,  0  );
	
	pRegInfo->iCustomId  =  qyGetCustomId(  );
	memset(  &pRegInfo->u,  0,  sizeof(  pRegInfo->u  )  );		 
	for  (  pItem  =  gpTable0,  index  =  0;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->idcType  !=  CONST_qyIdcType_combo  &&  pItem->idcType  !=  CONST_qyIdcType_edit  )  continue;
		 if  (  pItem->flg  &  CONST_qyIdcFlgUnused  )  continue;
		 if  (  pItem->uiCommSeqNo  ==  -1  )  continue;		//  µ±´«ÊäË³ÐòºÅÎª-1Ê±£¬²»×÷Îª×¢²áÐÅÏ¢´«Êäµ½·þÎñÆ÷ÉÏ£¬2003/11/15
		 							  
		 /*
		 if  (  pItem->flg  &  CONST_qyIdcFlgNeeded  ||  !(  pItem->flg  &  CONST_qyIdcFlgHide  )  )  {
		 	 //  GetDlgItemText(  hWnd,  pItem->idc,  pRegInfo->u.cols[index],  min(  sizeof(  pRegInfo->u.cols[index]  ),  pItem->maxBytes  +  1  )  );		 
			 //  trim(  pRegInfo->u.cols[index]  );
			 MACRO_qyAssert(  pItem->uiCommSeqNo  <  CONST_qnmMaxRegFields,  "´«ÊäË³ÐòºÅ²»ÄÜ³¬¹ýCONST_qnmMaxRegFields"  );
			 GetDlgItemText(  hWnd,  pItem->idc,  pRegInfo->u.cols[pItem->uiCommSeqNo],  min(  sizeof(  pRegInfo->u.cols[pItem->uiCommSeqNo]  ),  pItem->maxBytes  +  1  )  );		 
			 trim(  pRegInfo->u.cols[pItem->uiCommSeqNo]  );
			 if  (  pItem->idcType  ==  CONST_qyIdcType_combo  &&  pItem->pTable  )  {		//  2005/02/08½«comboµÄÊý¾ÝÓÉ¸ÄÎªÓÉÀàÐÍÀ´´ú±í£¬ÎªÁËÊ¹¶àÓïÑÔÄÜ¹»Ê¹ÓÃ
				 int	tmpiType  =  qyGetTypeByDes(  pItem->pTable,  pRegInfo->u.cols[pItem->uiCommSeqNo]  );
				 _snprintf(  pRegInfo->u.cols[pItem->uiCommSeqNo],  sizeof(  pRegInfo->u.cols[pItem->uiCommSeqNo]  ),  "%d",  tmpiType  );
			 }
			 pRegInfo->uiFieldIds[pItem->uiCommSeqNo]  =  pItem->uiFieldId;	//  2005/02/07
		 }
		 */  //  2005/09/24£¬ÎªÁË½«Êý¾Ý´Óchar±äÎªUnicode, ×öÒÔÏÂÐÞ¸Ä 

		 if  (  pItem->flg  &  CONST_qyIdcFlgNeeded  ||  !(  pItem->flg  &  CONST_qyIdcFlgHide  )  )  {
			 MACRO_qyAssert(  pItem->uiCommSeqNo  <  CONST_qnmMaxRegFields,  _T(  "bGetRegInfoFromDlg: uiCommSeqNo < CONST_qnmMaxRegFields"  )  );
			 GetDlgItemText(  hWnd,  pItem->idc,  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  )  );  
			 //  myMessageBox(  NULL,  tBuf,  _T(  ""  ),  MB_OK  );  //  ÎªdebugÐèÒª
			 if  (  ucbUtf8  )  {
				 myTChar2Utf8(  tBuf,  pRegInfo->u.cols[pItem->uiCommSeqNo],  min(  sizeof(  pRegInfo->u.cols[pItem->uiCommSeqNo]  ),  pItem->maxBytes  +  1  )  );		 
				 trim(  pRegInfo->u.cols[pItem->uiCommSeqNo]  );
				}
			 else  {
				   lstrcpyn(  (  TCHAR  *  )pRegInfo->u.cols[pItem->uiCommSeqNo],  tBuf,  min(  sizeof(  pRegInfo->u.cols[pItem->uiCommSeqNo]  ),  pItem->maxBytes  +  1  )  /  sizeof(  TCHAR  )  );		 
			 }
			 if  (  pItem->idcType  ==  CONST_qyIdcType_combo  &&  pItem->iResIdTable  )  {		//  2005/02/08½«comboµÄÊý¾ÝÓÉ¸ÄÎªÓÉÀàÐÍÀ´´ú±í£¬ÎªÁËÊ¹¶àÓïÑÔÄÜ¹»Ê¹ÓÃ
				 int	tmpiType;
				 if  (  ucbUtf8  )  {
					 safeStrnCpy(  pRegInfo->u.cols[pItem->uiCommSeqNo],  buf,  sizeof(  buf  )  );
				 	 myUtf82Str(  buf,  sizeof(  buf  )  );
				 	 tmpiType  =  qyGetTypeByDes(  getResTable(  0,  pCusRes,  pItem->iResIdTable  ),  myStr2TChar(  buf,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  )  );
					}
				 else  {
					   tmpiType  =  qyGetTypeByDes(  getResTable(  0,  pCusRes,  pItem->iResIdTable  ),  tBuf  );
				 }
				 if  (  ucbUtf8  )  _snprintf(  pRegInfo->u.cols[pItem->uiCommSeqNo],  sizeof(  pRegInfo->u.cols[pItem->uiCommSeqNo]  ),  "%d",  tmpiType  );
				 else  _sntprintf(  (  TCHAR  *  )pRegInfo->u.cols[pItem->uiCommSeqNo],  sizeof(  pRegInfo->u.cols[pItem->uiCommSeqNo]  )  /  sizeof(  TCHAR  ),  _T(  "%d"  ),  tmpiType  );
			 }
			 pRegInfo->uiFieldIds[pItem->uiCommSeqNo]  =  pItem->uiFieldId;	//  2005/02/07
		 }

		 index  ++  ;
	}
		
	bRet  =  TRUE;

errLabel:

	return  bRet;

}

 QY_IDCITEM  *  tmp_gpCb0Tables[]	=	{  NULL,  };
 //
 extern  "C"  QY_IDCITEM  **  getCbxTables(  int  idc  )
{		
	return  tmp_gpCb0Tables;	 
 }


 //  extern  "C"  BOOL  bSetDlgRegInfo(  QNM_CUSRES_INFO  *  pCusRes,  QNM_REG_INFO  *  pRegInfo,  HWND  hWnd,  BOOL  bEdit  )
 BOOL  bSetDlgRegInfo(  QNM_CUSRES_INFO  *  pCusRes,  QNM_REG_INFO  *  pRegInfo,  HWND  hWnd,  QY_IDCITEM  *  gpTable0,  BOOL  bEdit  )
{
	BOOL			bRet		=	FALSE;
	QY_IDCITEM	*	pItem		=	NULL;
	QY_IDCITEM	*	tmppItem	=	NULL;
	int				index;
	int				iCurSel;
	QY_IDCITEM  **  ppTables	=	NULL;


	for  (  pItem  =  gpTable0,  index  =  0;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->idcType  !=  CONST_qyIdcType_combo  &&  pItem->idcType  !=  CONST_qyIdcType_edit  )  continue;
		 if  (  pItem->flg  &  CONST_qyIdcFlgUnused  )  continue;
		 if  (  pItem->uiCommSeqNo  ==  -1  )  continue;		//  µ±´«ÊäË³ÐòºÅÎª-1Ê±£¬²»×÷Îª×¢²áÐÅÏ¢´«Êäµ½·þÎñÆ÷ÉÏ£¬2003/11/15							  
		 
		 MACRO_qyAssert(  pItem->uiCommSeqNo  <  CONST_qnmMaxRegFields,  _T(  "bSetDlgRegInfo: uiCommSeqNo < CONST_qnmMaxRegFields"  )  );
		 if  (  pItem->idcType  ==  CONST_qyIdcType_combo  )  {
			 iCurSel  =  SendMessage(  GetDlgItem(  hWnd,  pItem->idc  ),  CB_FINDSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  getResTable(  0,  pCusRes,  pItem->iResIdTable  ),  atol(  pRegInfo->u.cols[pItem->uiCommSeqNo]  )  )  );
			 if  (  iCurSel  !=  CB_ERR  )  {

			 	 SendMessage(  GetDlgItem(  hWnd,  pItem->idc  ),  CB_SETCURSEL,  iCurSel,  0  );
				 ppTables  =  getCbxTables(  pItem->idc  );				
				 procCbSelChange(  pCusRes,  gpTable0,  ppTables,  hWnd,  pItem->idc,  bEdit  );									 

			 }
			}
		 else  
			 SetDlgItemText(  hWnd,  pItem->idc,  (  TCHAR  *  )pRegInfo->u.cols[pItem->uiCommSeqNo]  );
		 
		 index  ++  ;
	}
	
	bRet  =  TRUE;

//  errLabel:
	return  bRet;
}

 
 //  2005/02/06		
 extern  "C"  int  setDlgIdcParams(  QRT_LAYOUT_CFG  *  pIdc  )
{
	 //
	 pIdc->bj				=  24;			//  ×óÓÒÁ½²à±ß¾à
	 pIdc->staticW			=  65;
	 pIdc->staticEditHjg	=  11;			//  static Óë editË®Æ½¼ä¸ô
	 pIdc->editW			=  77;
	 pIdc->midHjg			=  13;
	 pIdc->idcH				=  16;			//  14;  2005/10/04¸Ä
	 pIdc->comboH			=  12;
	 pIdc->idcVjg			=  4;
	 pIdc->staticHint1Vjg	=  13;			//  Óëhint1Ö®¼äµÄ´¹Ö±¼ä¸ô
	 pIdc->hint1ProgressVjg	=  12;			
	 pIdc->dlgTitleHeight	=  20;			//  È·¶¨<->µØÏß
	 pIdc->titleW			=  192;
	 pIdc->titleH			=  18;
	 pIdc->hint0H			=  28;			//  2005/07/27Ôö¼ÓÁË¶Ôhint0µÄ¸ß¶ÈÉèÖÃ	
	 pIdc->okW				=  50;	
	 pIdc->okCancelHjg		=  74;
	 pIdc->bbj				=  25;
	 
	 return  0;
}
 
 
 

 extern  "C"  int  setDlgIdcSize(  int  iIDC_title,  int  iIDC_hint0,  int  iIDC_hint1,  int  iIDC_PROGRESS_reg,  QNM_CUSTOM_COMM  *  pCustom,  QRT_LAYOUT_CFG  *  pIdcCfg,  QY_IDCITEM  *  pTable0  )
{
	 int					IDC_title			=	iIDC_title;
	 int					IDC_hint0			=	iIDC_hint0;
	 int					IDC_hint1			=	iIDC_hint1;
	 int					IDC_PROGRESS_reg	=	iIDC_PROGRESS_reg;
	 QY_IDCITEM		*		pItem				=	NULL;
	 unsigned  long			i,  ulTop,  ulBottom;
	 unsigned  char			ucbMustBeLeft		=	FALSE;

	 pIdcCfg->ulDlgWidth  =  2  *  (  pIdcCfg->bj  +  pIdcCfg->staticW  +  pIdcCfg->staticEditHjg  +  pIdcCfg->editW  )  +  pIdcCfg->midHjg;
	 
	 for  (  i  =  0,  pItem  =  pTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
		  if  (  bFieldLikeDw(  pItem->uiFieldId  )  )  {
			  if  (  pItem->ucLevel  <  pCustom->nDwLevels  )  {  
				  pItem->flg  |=  (  CONST_qyIdcFlgNeeded  |  CONST_qyIdcFlgChkNotNull  );
				  pItem->flg  &=  ~CONST_qyIdcFlgHide;
					}
			  else  {
				    pItem->flg  |=  CONST_qyIdcFlgHide;
					pItem->flg  &=  ~(  CONST_qyIdcFlgNeeded  |  CONST_qyIdcFlgChkNotNull  );
			  }
		  }
		  if  (  bFieldLikeZcbh(  pItem->uiFieldId,  0  )  )  {
			  if  (  pItem->ucLevel  <  pCustom->nZcbhs  )  {
				  if  (  !pItem->ucLevel  )  pItem->flg  |=  (  CONST_qyIdcFlgNeeded  |  CONST_qyIdcFlgChkNotNull  );    
				  pItem->flg  &=  ~CONST_qyIdcFlgHide;
					}
			  else  {
				    pItem->flg  |=  CONST_qyIdcFlgHide;
				    pItem->flg  &=  ~(  CONST_qyIdcFlgNeeded  |  CONST_qyIdcFlgChkNotNull  );
			  }
			  
		  }
		  if  (  pItem->idc  ==  IDC_title  ||  pItem->idc  ==  IDC_hint0  )  {
			  if  (  pItem->idc  ==  IDC_title  )  pItem->x  =  (  pIdcCfg->ulDlgWidth  -  pIdcCfg->titleW  )  /  2;
			  if  (  pItem->idc  ==  IDC_hint0  )  ulBottom  =  pItem->y  +  pIdcCfg->hint0H;  
			  continue;
		  }
		  if  (  pItem->idc  ==  IDC_hint1  )  {
			  ulTop  =  ulBottom  +  pIdcCfg->staticHint1Vjg;  ulBottom  =  ulTop  +  pIdcCfg->idcH;
			  pItem->y  =  ulTop;
			  continue;
		  }
		  if  (  pItem->idc  ==  IDC_PROGRESS_reg  )  {
			  ulTop  =  ulTop  +  pIdcCfg->hint1ProgressVjg;  ulBottom  =  ulTop  +  pIdcCfg->idcH;
			  pItem->y  =  ulTop;
			  continue;
		  }
		  if  (  pItem->idc  ==  IDOK  ||  pItem->idc  ==  IDCANCEL  )  {
			  pItem->w  =  pIdcCfg->okW;	pItem->h  =  pIdcCfg->idcH;
			  if  (  pItem->idc  ==  IDOK  )  pItem->x  =  (  pIdcCfg->ulDlgWidth  -  pIdcCfg->okCancelHjg  )  /  2  -  pItem->w;
			  else  if  (  pItem->idc  ==  IDCANCEL  )  pItem->x  =  (  pIdcCfg->ulDlgWidth  +  pIdcCfg->okCancelHjg  )  /  2;    
			  pItem->y  =  ulBottom  +  pIdcCfg->idcVjg;
			  continue;
		  }
		  if  (  pItem->flg  &  CONST_qyIdcFlgHide  )  continue;
		  //  ÏÂÃæ¿¼ÂÇÓÐÊ±ºîÓÐ¶ÔÆëµÄÐèÒª
		  ucbMustBeLeft  =  FALSE;
		  if  (  pItem->idcType  ==  CONST_qyIdcType_static  &&  (  pItem->uiFieldId  ==  CONST_fieldId_zcbh1  ||  pItem->uiFieldId  ==  CONST_fieldId_zcbh2  )  )  ucbMustBeLeft  =  TRUE;
		  if  (  ucbMustBeLeft  )  i  =  0;
		  //  ÏÂÃæ¼ÆËã¸÷¸ö¿Ø¼þµÄ³ß´ç
		  if  (  !(  i  %  4  )  )  {
			  ulTop  =  ulBottom  +  pIdcCfg->idcVjg;  ulBottom  =  ulTop  +  pIdcCfg->idcH;
		  }
		  pItem->y  =  ulTop;  pItem->h  =  (  (  pItem->idcType  ==  CONST_qyIdcType_combo  )  ?  pIdcCfg->comboH  :  pIdcCfg->idcH  );
		  switch  (  i  %  4  )  {
				  case  0:  pItem->w  =  pIdcCfg->staticW;	pItem->x  =  pIdcCfg->bj;    break;
				  case  1:  pItem->w  =  pIdcCfg->editW;	pItem->x  =  pIdcCfg->bj  +  pIdcCfg->staticW  +  pIdcCfg->staticEditHjg;  break;
				  case  2:  pItem->w  =  pIdcCfg->staticW;	pItem->x  =  pIdcCfg->bj  +  pIdcCfg->staticW  +  pIdcCfg->staticEditHjg  +  pIdcCfg->editW  +  pIdcCfg->midHjg;  break;
				  case  3:  pItem->w  =  pIdcCfg->editW;	pItem->x  =  pIdcCfg->bj  +  pIdcCfg->staticW  +  pIdcCfg->staticEditHjg  +  pIdcCfg->editW  +  pIdcCfg->midHjg  +  pIdcCfg->staticW  +  pIdcCfg->staticEditHjg;  break;
				  default:	break;
		  }
		  i  ++  ;
	 }

	 pIdcCfg->ulDlgHeight  =  ulBottom  +  pIdcCfg->idcH  +  pIdcCfg->bbj  +  pIdcCfg->dlgTitleHeight;

	 return  0;
}

