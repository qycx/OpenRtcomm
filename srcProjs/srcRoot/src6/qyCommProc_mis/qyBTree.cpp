

#include	"qyPrecomp.h"

#include	<windows.h>
#include	<assert.h>
#include	<tchar.h>

#include	"qyBTree.h"

 //  i为结点序号，比c数组下标大1
 B_tree  *  createBT(  void  *  array_pData,  unsigned  int  uiSize_pData,  int i,  int n  )
{		
	int			iErr	=	-1;
	B_tree  *	p		=	NULL;

	if  (  i  <  1  ||  i  >  n  )  return  NULL;
	else  {
		  p  =  (  B_tree  *  )malloc(  sizeof(   BT_node  )  );
		  if  (  !p  )  return  NULL;
		  memset(  p,  0,  sizeof(  BT_node  )  );
		  if  (  uiSize_pData  )  {
			  p->pData  =  malloc(  uiSize_pData  );
			  if  (  !p->pData  )  goto  errLabel;
			  memcpy(  p->pData,  (  char  *  )array_pData  +  (  i  -  1  )  *  uiSize_pData,  uiSize_pData  );
			  p->uiSize_pData  =  uiSize_pData;
		  }

		  p->lChild  =  createBT(  array_pData,  uiSize_pData,  2*i,  n  );			//  i : node;
		  p->rChild  =  createBT(  array_pData,  uiSize_pData,  2*i+1,  n  );
	}

	iErr  =  0;

errLabel:
	if  (  iErr  )  {
		freeBT(  p  );
	}
	return  iErr  ?  NULL  :  p;
}

 void  freeBT(  B_tree  *  p  )
{
	if  (  p  )  {
		if  (  p->lChild  )  freeBT(  p->lChild  );
		if  (  p->rChild  )  freeBT(  p->rChild  );
		if  (  p->pData  )  free(  p->pData  );
		free(  p  );
	}
}

 BT_node  *  searchBT(  B_tree  *  p,  void  *  pData,  unsigned  int  uiSize_pData  )
{
	BT_node	*	pNode	=	NULL;

	if  (  !p  )  return  NULL;
	if  (  !pData  ||  !uiSize_pData  )  return  NULL;

	if  (  uiSize_pData  ==  p->uiSize_pData  &&  !memcmp(  p->pData,  pData,  uiSize_pData  )  )  return  p;
	if  (  (  pNode  =  searchBT(  p->lChild,  pData,  uiSize_pData  )  )  )  return  pNode;
	if  (  (  pNode  =  searchBT(  p->rChild,  pData,  uiSize_pData  )  )  )  return  pNode;
	return  NULL;
}

#ifdef  __DEBUG__
	int  printBT(  B_tree  *  p,  int  level  )
{
	TCHAR	tBuf[128];

	if  (  !p  )  return  -1;
	int	iData;
	memcpy(  &iData,  p->pData,  min(  p->uiSize_pData,  sizeof(  iData  )  )  );
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "level %d, %d\n"  ),  level,  iData  );
	OutputDebugString(  tBuf  );
	printBT(  p->lChild,  level  +  1  );
	printBT(  p->rChild,  level  +  1  );

	return  0;
}

		int  testBt( )
	{
		int	a[]	=	{	0,	1,	2,	3,	4,	5,	6,	};

		B_tree  *  p  =  createBT(  a,  sizeof(  a[0]  ),  1,  sizeof(  a  )  /  sizeof(  a[0]  )  );

		printBT(  p,  1  );

		freeBT(  p  );

		return  0;
	}
#endif
