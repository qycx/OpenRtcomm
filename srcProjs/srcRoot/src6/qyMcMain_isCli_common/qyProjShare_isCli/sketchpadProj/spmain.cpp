
#include	"stdafx.h"
#include	"include//sp.h"


#ifdef  __DEBUG__

 __declspec(dllexport ) int  testSp(  )
{
	traceLogA(  "opFlg_x %d",  CONST_opFlg_x  );
	traceLogA(  "opFlg_y %d",  CONST_opFlg_y  );
	traceLogA(  "n %d",  CONST_opFlg_x  |  CONST_opFlg_y  );

	return  0;
}

#endif


 
 __declspec(  dllexport  )  int initSp( void  ** ppSp )
{
	 int			iErr	=	-1;
	 SP_STRUCT	*	pSp		=	NULL;

	 if  (  !ppSp  ||  *ppSp  )  return  -1;

	 if  (  !(  pSp  =  (  SP_STRUCT  *  )mymalloc(  sizeof(  SP_STRUCT  )  )  )  )  goto  errLabel;
	 memset( pSp, 0, sizeof( SP_STRUCT ) );

	 if ( !( pSp->pSpObjQ = genericQNew(  _T(  "spObjQ"  ),  _T(  "spObjQ"  ),  0,  1000,  (  PF_qElemNew  )objNew,  (  PF_qElemFree  )objFree  )  )  )  goto  err;

	 if ( !( pSp->pNewSpObjQ = genericQNew(  _T(  "newSpObjQ"  ),  _T(  "newSpObjQ"  ),  0,  1000,  (  PF_qElemNew  )objNew,  (  PF_qElemFree  )objFree  )  )  )  goto  err;
	 
	 if ( !( pSp->pSelectedSpObjQ = genericQNew(  _T(  "selSpObjQ"  ),  _T(  "selSpObjQ"  ),  0,  1000,  (  PF_qElemNew  )objNew,  (  PF_qElemFree  )objFree  )  )  ) goto  err;

	 if ( !( pSp->pOpedSpObjQ = genericQNew(  _T(  "opedSpObjQ"  ),  _T(  "opedSpObjQ"  ),  0,  1000,  (  PF_qElemNew  )objNew,  (  PF_qElemFree  )objFree  )  )  )  goto  err;
	 
	 pSp->sysStatus = STATUS_SELECT;
	 pSp->errNo = ERR_NOTHING;
	 pSp->tranType = NO_TRAN;

	 pSp->spWidth = 0;
	 pSp->spHeight = 0;

	 pSp->curpProcQNode = NULL;

	 pSp->pCenterQNode = NULL;
	 pSp->pMirrorQNode = NULL;

	 pSp->op = OP_NULL;


	 memset( &pSp->tranParm, 0, sizeof( pSp->tranParm ) );

#ifdef  __DEBUG__
		testSp(  );
#endif

	 iErr  =  0;

err:
errLabel:

	 if  (  iErr  )  {
		 exitSp(  (  void  **  )&pSp  );
	 }
	 if  (  !iErr  )  {
		 *ppSp  =  pSp;
	 }	 
	 
	 return  iErr;
	 
}

    
 __declspec(  dllexport  )  void  exitSp(  void  **  ppSp  )
{
	 SP_STRUCT *pSp	=	NULL;

	 if  (  !ppSp  ||  !*ppSp  )  return;
	 
	 pSp  =  *(  SP_STRUCT  **  )ppSp;

	 exitTran( pSp );

	 if  (  pSp->pOpedSpObjQ  )  {
		 genericQFree( pSp->pOpedSpObjQ ); pSp->pOpedSpObjQ = NULL;
	 }

	 if ( pSp->pSelectedSpObjQ ) {
		 genericQFree( pSp->pSelectedSpObjQ ); pSp->pSelectedSpObjQ = NULL;
	 }

	 if ( pSp->pNewSpObjQ ) {
		 genericQFree( pSp->pNewSpObjQ ); pSp->pNewSpObjQ = NULL;
	 }

	 if ( pSp->pSpObjQ ) {
		genericQFree( pSp->pSpObjQ ); pSp->pSpObjQ = NULL;
	 }
	
	 free(  pSp  );
	 *ppSp  =  NULL;

	 return;
}

 __declspec(  dllexport  )  void  resetSp(  void  *  pSpParam  )
{
	 SP_STRUCT *pSp	=	(  SP_STRUCT  *  )pSpParam;

	 if  (  !pSp  )  return;

	 exitTran( pSp );

	 if  (  pSp->pOpedSpObjQ  )  {
		 emptyGenericQ( pSp->pOpedSpObjQ ); 
	 }

	 if ( pSp->pSelectedSpObjQ ) {
		 emptyGenericQ(  pSp->pSelectedSpObjQ ); 
	 }

	 if ( pSp->pNewSpObjQ ) {
		 emptyGenericQ(  pSp->pNewSpObjQ ); 
	 }

	 if ( pSp->pSpObjQ ) {
		 emptyGenericQ( pSp->pSpObjQ ); 
	 }

	return;
}

 __declspec(  dllexport  )  int  initTran(  SP_STRUCT  *  pSp,  BYTE  tranType  )
{
	 int	iErr	=	-1;

	 pSp->errNo  =  0;
	 resetOpSp(  pSp  );

	 if ( tranType == CONSTRUCT_TRAN ) {
		if ( preserveLastQNode( pSp->pSpObjQ ) ) goto err;	 	
	 }
	 
	 pSp->tranType = tranType;

	 pSp->isPreOped = 0;

	 iErr  =  0;

err:
	 return  iErr;

}

 __declspec(  dllexport  )  void exitTran( SP_STRUCT *pSp )
{	
	 if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  {
		 emptyGenericQ(  pSp->pOpedSpObjQ  );
	 }

	 resetOpSp( pSp );

	 if ( pSp->tranType == CREATE_OBJS_TRAN ) {
		 emptyGenericQ( pSp->pNewSpObjQ );		
	 	 }
	 else if ( pSp->tranType == DISCMD_ANIMATE_TRAN ) {
			restoreLastQNode( pSp->pSpObjQ );		
		}
	 else if ( pSp->tranType == CONSTRUCT_TRAN ) {
		 if ( pSp->errNo ) restoreLastQNode( pSp->pSpObjQ );		
		 else stopPreserveLastQNode( pSp->pSpObjQ );
		}
	 else if ( pSp->tranType == DELETE_TRAN ) 
	 	 emptyGenericQ( pSp->pSelectedSpObjQ );
	 	 
	 pSp->errNo = 0;
	 pSp->tranType = NO_TRAN;
	 
	 return;

}


 void resetOpSp( SP_STRUCT *pSp )
{
	 Q_NODE *pQNode;

	 for ( pQNode = pSp->pSpObjQ->front.pNext; pQNode; pQNode = pQNode->pNext ) 
		 ( ( SP_OBJ * )pQNode->qElemMemory.m_pBuf )->op = OP_NULL;

	 pSp->isPreOped = 0;

	 return;

}

 __declspec(  dllexport  )  BOOL  bHideSp(  SP_STRUCT  *  pSp,  BOOL  bHide  )
{
	pSp->bHideAll  =  bHide;
	return  TRUE;
}


 //  2018/07/05
 __declspec(  dllexport  )  BOOL  bEditSp(  SP_STRUCT  *  pSp,  BOOL  bEditable  )
 {
	 pSp->ucbEditable  =  bEditable;
	 return  TRUE;
 }


 //
 __declspec(  dllexport  )  int  getSpRect(  SP_RECTANGLE	*	pRectangle,  RECT  *  pRect  )
{
	if  (  !pRectangle  ||  !pRect  )  return  -1;
	if  (  pRectangle->type  !=  SP_RECTANGLE_TYPE  ||  pRectangle->subType  !=  SP_GENERIC_RECTANGLE_TYPE  )  return  -1;

	SP_POINT		*	pPoint0		=	(  SP_POINT  *  )pRectangle->pQNode_points[0]->qElemMemory.m_pBuf;
	SP_POINT		*	pPoint2		=	(  SP_POINT  *  )pRectangle->pQNode_points[2]->qElemMemory.m_pBuf;

	memset(  pRect,  0,  sizeof(  pRect[0]  )  );
	pRect->left  =  min(  pPoint0->point.rect.x,  pPoint2->point.rect.x  );
	pRect->top  =  min(  pPoint0->point.rect.y,  pPoint2->point.rect.y  );
	pRect->right  =  max(  pPoint0->point.rect.x,  pPoint2->point.rect.x  );
	pRect->bottom  =  max(  pPoint0->point.rect.y,  pPoint2->point.rect.y  );

	return  0;
 }


  __declspec(  dllexport  )  Q_NODE  *  findSpQNode(  SP_STRUCT  *  pSp,  unsigned  int  uiTranNo_spObj  )
{
	int			iErr	=	-1;
	Q_NODE	*	pQNode	=	NULL;
	
	for  (  pQNode  =  pSp->pSpObjQ->front.pNext;  pQNode;  pQNode  =  pQNode->pNext  )  {
		 SP_OBJ	*	pSpObj	=	(  SP_OBJ  *  )pQNode->qElemMemory.m_pBuf;
		 if  (  !pSpObj  )  goto  errLabel;
		 if  (  pSpObj->uiTranNo  ==  uiTranNo_spObj  )  break;
	}
	iErr  =  0;
errLabel:
	return  iErr  ?  NULL  :  pQNode;
}

