

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyWmComm.h"
//#include	"myresource.h"
//#include	"qyRestrictEdit.h"



 int  getLvSelColContent(  HWND  hParent,  int  *  pCurnItem,  LPCTSTR  colName,  TCHAR  *  buf,  unsigned  int  size  )
{
	 int						iErr				=	-1;
	 LVITEM						lvItem;
	 unsigned  int				selectedCnt;
	 int						curnItem;
	 int						nCol;
	 
	 selectedCnt  =  ::SendMessage(  hParent,  LVM_GETSELECTEDCOUNT,  0,  0  );
	 if  (  !selectedCnt  )  goto  errLabel;
	 //
	 if  (  selectedCnt  >  1  )  goto  errLabel;	//  ÔÝÊ±²»Ö§³ÖÉ¾³ý¶àÏî¡£
	 
	 if  (  (  curnItem  =  ::SendMessage(  hParent,  LVM_GETSELECTIONMARK,  0,  0  )  )  <  0  )  goto  errLabel;

	 if  (  !buf  ||  !size  )  {		//  2004/08/07½«´ËÅÐ¶ÏÒÆµ½ÕâÀï£¬Ä¿µÄÊÇÔÊÐíÈ¡Ñ¡ÖÐµÄÐÐºÅcurnItem
		 iErr  =  0;  goto  errLabel;
	 }
	 
	 if  (  !colName  )  nCol  =  0;		//  Èç¹ûÃ»ÓÐÁÐÃû£¬ÔòÈ¡µÚÒ»¸ö×Ö¶Î
	 else  {
		    QY_WMBUF_COMM				tmpComm;

			memset(  &tmpComm,  0,  sizeof(  tmpComm  )  );
			tmpComm.uiType  =  CONST_qyWmParam_getnCol;
			lstrcpyn(  tmpComm.u.getnCol.colName,  colName,  mycountof(  tmpComm.u.getnCol.colName  )  );
			if  (  ::SendMessage(  hParent,  CONST_qyWm_comm,  0,  (  LPARAM  )&tmpComm  )  <  0  )  {
				#ifdef  __DEBUG__
						traceLogA(  (char*)  "getLvSelColContent´íÎó: Ã»ÓÐÀ¸Ä¿%s",  colName  );  
				#endif
				goto  errLabel;
			}
			nCol  =  tmpComm.u.getnCol.nCol;
	 }

	 memset(  &lvItem,  0,  sizeof(  lvItem  )  );
	 lvItem.mask			=  LVIF_TEXT;
	 lvItem.iItem			=  curnItem;
	 lvItem.iSubItem		=  nCol;			//  mac0ÏÔÊ¾µÄÁÐÎ»ÖÃ
	 lvItem.pszText			=  buf;
	 lvItem.cchTextMax		=  size;

	 if  (  !::SendMessage(  hParent,  LVM_GETITEM,  0,  (  LPARAM  )&lvItem  )  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "getLvSelColContent´íÎó: Ã»ÓÐÕÒµ½À¸Ä¿%sÏàÓ¦µÄÄÚÈÝ",  (  colName  ?  colName  :  _T(  ""  )  )  );  
		 #endif
		 goto  errLabel;
	 }

	 iErr  =  0;

errLabel:
	 
	 if  (  !iErr  )  {
		 if  (  pCurnItem  )  *pCurnItem  =  curnItem;
	 }

	 return  iErr;

}


 
 //  ´Ëº¯Êý¿ÉÔÊÐíÈ¡Ñ¡ÖÐµÄÐÐºÅcurnItemµÄÌØ¶¨ÁÐÃûµÄ×Ö¶ÎÄÚÈÝ.  Èç¹ûÃ»ÓÐÁÐÃû£¬ÔòÈ¡µÚÒ»¸ö×Ö¶Î
 int  getLvColContent(  HWND  hParent,  HWND  hList,  int  curnItem,  LPCTSTR  colName,  TCHAR  *  buf,  unsigned  int  size  )
{
	 int						iErr				=	-1;
	 LVITEM						lvItem;
	 int						nCol;

	 if  (  !buf  ||  !size  )  {		//  2004/08/07½«´ËÅÐ¶ÏÒÆµ½ÕâÀï£¬Ä¿µÄÊÇÔÊÐíÈ¡Ñ¡ÖÐµÄÐÐºÅcurnItem
		 iErr  =  0;  goto  errLabel;
	 }
	 
	 if  (  !colName  )  nCol  =  0;		//  Èç¹ûÃ»ÓÐÁÐÃû£¬ÔòÈ¡µÚÒ»¸ö×Ö¶Î
	 else  {
		    QY_WMBUF_COMM				tmpComm;

			memset(  &tmpComm,  0,  sizeof(  tmpComm  )  );
			tmpComm.uiType  =  CONST_qyWmParam_getnCol;
			tmpComm.u.getnCol.hList  =  hList;
			lstrcpyn(  tmpComm.u.getnCol.colName,  colName,  mycountof(  tmpComm.u.getnCol.colName  )  );
			if  (  ::SendMessage(  hParent,  CONST_qyWm_comm,  0,  (  LPARAM  )&tmpComm  )  <  0  )  {
				#ifdef  __DEBUG__
						traceLogA(  (char*)  "getLvSelColContent´íÎó: Ã»ÓÐÀ¸Ä¿%s",  colName  );  
				#endif
				goto  errLabel;
			}
			nCol  =  tmpComm.u.getnCol.nCol;
	 }

	 memset(  &lvItem,  0,  sizeof(  lvItem  )  );
	 lvItem.mask			=  LVIF_TEXT;
	 lvItem.iItem			=  curnItem;
	 lvItem.iSubItem		=  nCol;			//  mac0ÏÔÊ¾µÄÁÐÎ»ÖÃ
	 lvItem.pszText			=  buf;
	 lvItem.cchTextMax		=  size;

	 if  (  !::SendMessage(  hList  ?  hList  :  hParent,  LVM_GETITEM,  0,  (  LPARAM  )&lvItem  )  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "getLvSelColContent´íÎó: Ã»ÓÐÕÒµ½À¸Ä¿%sÏàÓ¦µÄÄÚÈÝ",  (  colName  ?  colName  :  _T(  ""  )  )  );  
		 #endif
		 goto  errLabel;
	 }

	 iErr  =  0;

errLabel:
	 
	 if  (  !iErr  )  {
	 }

	 return  iErr;

}

