
#ifndef  __QYBTREE_H__
#define  __QYBTREE_H__		//  {

typedef  struct  __btNode_t			{
				 void			*	pData;
				 unsigned  int		uiSize_pData;
				 //
				 struct __btNode_t *lChild, *rChild;
}		 BT_node,  B_tree;


 B_tree  *  createBT(  void  *  array_pData,  unsigned  int  uiSize_pData,  int i,  int n  );
 void  freeBT(  B_tree  *  p  );
 BT_node  *  searchBT(  B_tree  *  p,  void  *  pData,  unsigned  int  uiSize_pData  );

#ifdef  __DEBUG__
 int  printBT(  B_tree  *  p,  int  level  );
#endif


#endif  //  }


