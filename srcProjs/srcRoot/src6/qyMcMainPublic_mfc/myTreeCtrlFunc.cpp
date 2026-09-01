
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"
//  #include	"leftView.h"
//  #include	"qyMcView.h"
#include	"qyCusResTemp.h"

#include	"myTreeCtrlFunc.h"


//
 BOOL  bGetTopParams(  int  *piTopFieldId,  int  *piTopObjType  )
{
	 BOOL		bRet	=	FALSE;
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	 int		iTopFieldId,  iObjType;
	 
	 switch  (  pQyMc->cfg.custom.nDwLevels  )  {
			 case  5:  iTopFieldId  =  CONST_fieldId_zb;	iObjType  =  CONST_objType_zb;  break;
			 case  4:  iTopFieldId  =  CONST_fieldId_bb;	iObjType  =  CONST_objType_bb;	break;
			 case  3:  iTopFieldId  =  CONST_fieldId_dw;	iObjType  =  CONST_objType_col2;break;
			 default:	goto  errLabel;
	 }
	 bRet  =  TRUE;
errLabel:
	 if  (  bRet  )  {
		 if  (  piTopFieldId  )  *piTopFieldId  =  iTopFieldId;
		 if  (  piTopObjType  )  *piTopObjType  =  iObjType;
	 }
	 return  bRet;
}


 #if  0
  int  myTrimTree(  void  *  pDb,  void  *  pLeftViewParam,  HANDLE  htItemParam,  PF_bTvItemExists  pfbTvItemExists  )
{
	if  (  !pTreeCtrl  )  return  -1;
	 CLeftView  *	pLeftView	=	(  CLeftView  *  )pLeftViewParam;
	 HTREEITEM		htItem		=	(  HTREEITEM  )htItemParam;

	 if  (  !pfbTvItemExists  )  {
		 traceLogA(  "myTrimTree:  pfbTvItemExists没有设置"  );  return  -1;
	 }

	 if  (  pLeftView->m_TreeCtrl->ItemHasChildren(  htItem  )  )  {
		 HTREEITEM  tmphtItem	=	pLeftView->m_TreeCtrl->GetChildItem(  htItem  );
		 while  (  tmphtItem  )  {
			    if  (  !pfbTvItemExists(  pDb,  pLeftView,  tmphtItem  )  )  {
					HTREEITEM  tmphtItem1  =  pLeftView->m_TreeCtrl->GetNextSiblingItem(  tmphtItem  );
					pLeftView->m_TreeCtrl->DeleteItem(  tmphtItem  );  
					tmphtItem  =  tmphtItem1;  continue;
				}
				myTrimTree(  pDb,  pLeftView,  tmphtItem,  pfbTvItemExists  );
				tmphtItem  =  pLeftView->m_TreeCtrl->GetNextSiblingItem(  tmphtItem  );
		 }
	 }
	 return  0;
}
#endif


  int  myTrimTree(  QY_OBJ_DB  *  pObjDb,  CTreeCtrl  *  pTreeCtrl,  HANDLE  htItemParam,  PF_bTvItemExists  pfbTvItemExists  )
{
	if  (  !pTreeCtrl  )  return  -1;
	 //  CLeftView  *	pLeftView	=	(  CLeftView  *  )pLeftViewParam;
	CTreeCtrl    *  m_TreeCtrl  =  pTreeCtrl;
	 HTREEITEM		htItem		=	(  HTREEITEM  )htItemParam;

	 if  (  !pfbTvItemExists  )  {
		 traceLogA(  "myTrimTree:  pfbTvItemExists没有设置"  );  return  -1;
	 }

	 if  (  m_TreeCtrl->ItemHasChildren(  htItem  )  )  {
		 HTREEITEM  tmphtItem	=	m_TreeCtrl->GetChildItem(  htItem  );
		 while  (  tmphtItem  )  {
			    if  (  !pfbTvItemExists(  pObjDb,  m_TreeCtrl,  tmphtItem  )  )  {
					HTREEITEM  tmphtItem1  =  m_TreeCtrl->GetNextSiblingItem(  tmphtItem  );
					m_TreeCtrl->DeleteItem(  tmphtItem  );  
					tmphtItem  =  tmphtItem1;  continue;
				}
				myTrimTree(  pObjDb,  m_TreeCtrl,  tmphtItem,  pfbTvItemExists  );
				tmphtItem  =  m_TreeCtrl->GetNextSiblingItem(  tmphtItem  );
		 }
	 }
	 return  0;
}


