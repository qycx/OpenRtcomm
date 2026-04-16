

#ifndef  __myTreeCtrlFunc_h__
#define  __myTreeCtrlFunc_h__


//
typedef  BOOL  (  *PF_bTvItemExists  )(  QY_OBJ_DB  *  pObjDb,  CTreeCtrl  *  pTreeCtrl,  HTREEITEM  htItem  );
int  myTrimTree(  QY_OBJ_DB  *  pObjDb,  CTreeCtrl  *  pTreeCtrl,  HANDLE  htItem,  PF_bTvItemExists  pfbTvItemExists  );

//
BOOL  bItemExists_imObjs(  QY_OBJ_DB  *  pObjDb,  CTreeCtrl  *  pTreeCtrl,  HTREEITEM  htItem  );


#endif

