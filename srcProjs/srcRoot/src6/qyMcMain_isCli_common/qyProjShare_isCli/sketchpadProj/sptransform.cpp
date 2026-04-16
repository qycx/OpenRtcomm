
#include	"stdafx.h"
#include	"sp.h"


 int spMarkCenter( SP_STRUCT *pSp )
{
	 int iErr = 0;
	 Q_NODE *pQNode;

	 if ( !( pQNode = pSp->pSelectedSpObjQ->front.pNext ) ) {
		 iErr = -1; goto err;
	 }

	 if ( pQNode->pNext ) {
		 iErr = -1; goto err;
	 }

	 pQNode = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
	 if ( ( ( SP_OBJ * )( pQNode->qElemMemory.m_pBuf ) )->type != SP_POINT_TYPE ) {
		 iErr = -1; goto err;
	 }

	 pSp->pCenterQNode = pQNode;

err:
	 
	 if ( iErr ) pSp->pCenterQNode = NULL;

	 return iErr;

}


 int spMarkMirror( SP_STRUCT *pSp )
{
	 int iErr = 0;
	 Q_NODE *pQNode;

	 if ( !( pQNode = pSp->pSelectedSpObjQ->front.pNext ) ) {
		 iErr = -1; goto err;
	 }

	 if ( pQNode->pNext ) {
		 iErr = -1; goto err;
	 }

	 pQNode = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
	 
	 if ( ( ( SP_OBJ * )( pQNode->qElemMemory.m_pBuf ) )->type != SP_SEGMENT_TYPE ) {
		 iErr = -1; goto err;
	 }

	 pSp->pMirrorQNode = pQNode;


err:

	 if ( iErr ) pSp->pMirrorQNode = NULL;

	 return iErr; 
 
}

 int spTranslateTransform( SP_STRUCT *pSp )
{
	 int iErr = 0;

	 return iErr;

}

 int spRotateTransform( SP_STRUCT *pSp )
{
	 int iErr = 0;
	 Q_NODE *pQNode, *tmppQNode;
	 short A180;


	 if ( !pSp->pCenterQNode ) return -1;

	 if ( ( ( SP_OBJ * )pSp->pCenterQNode->qElemMemory.m_pBuf )->status & ( STATUS_INVALID | STATUS_INVISIBLE ) ) {
			return -1;
	 }

	 if ( getRotateParm( &A180 ) ) {
			iErr = -1; goto err;
	 }

	 for ( pQNode = pSp->pSelectedSpObjQ->front.pNext; pQNode; pQNode = pQNode->pNext ) {
	 
		 tmppQNode = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
		 
		 rotateSpObj( pSp, tmppQNode, A180 );

	 }


err:

	 return iErr;

}

 

 int spDilateTransform( SP_STRUCT *pSp )
{
	 int iErr = 0;

	 return iErr;

}

 int spReflectTransform( SP_STRUCT *pSp )
{
	 int iErr = 0;
	 Q_NODE *pQNode, *tmppQNode;

	 if ( !pSp->pMirrorQNode ) {
		 return -1;
	 }

	 if ( ( ( SP_OBJ * )pSp->pMirrorQNode->qElemMemory.m_pBuf )->status & STATUS_INVALID 
		 || ( ( SP_OBJ * )pSp->pMirrorQNode->qElemMemory.m_pBuf )->status & STATUS_INVISIBLE ) {
		 return -1;
	 }

	 for ( pQNode = pSp->pSelectedSpObjQ->front.pNext; pQNode; pQNode = pQNode->pNext ) {
	 
		 tmppQNode = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
		 
		 reflectSpObj( pSp, tmppQNode );

	 }

	 


	 return iErr;


}



////////////

  extern "C" int getRotateParm( short *pA180 )
{
	int iErr = 0;
	/*
	CGetRotateParm getRotateParm;

	if ( getRotateParm.DoModal() == IDCANCEL ) {
			iErr = -1; goto err;
	}

	*pA180 = getRotateParm.A180;
	*/
	traceLogA(  "Not finished: for test"  );
	*pA180 = 180;

//  err:
	
	return iErr;

}
