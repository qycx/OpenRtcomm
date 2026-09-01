
#include	"stdafx.h"
#include	"sp.h"

 int rotateSpObj( SP_STRUCT *pSp, Q_NODE *pQNode, short A180 )
{
	 int iErr = 0;
	 SP_OBJ *pSpObj;

	 pSpObj = ( SP_OBJ * )pQNode->qElemMemory.m_pBuf;

	 switch ( pSpObj->type ) {

		case SP_POINT_TYPE:

			iErr = rotateSpPoint( pSp, pQNode, A180 );

			break;

		case SP_SEGMENT_TYPE:

			iErr = rotateSpSegment( pSp, pQNode, A180 );

			break;

		case SP_CIRCLE_TYPE:

			iErr = rotateSpCircle( pSp, pQNode, A180 );

			break;

		default:

			iErr = -1;

			break;

	 }

	 return iErr;


}

 int rotateSpPoint( SP_STRUCT *pSp, Q_NODE *pQNode, short A180 )
{
	 SP_POINT *pSpPoint;
	 SP_ROTATE_POINT tmpSpRotatePoint;
	 SP_POINT *pCenter;
	 int iErr = 0;

	 pSpPoint = ( SP_POINT * )pQNode->qElemMemory.m_pBuf;
	 pCenter = ( SP_POINT * )pSp->pCenterQNode->qElemMemory.m_pBuf;

	 
	 if ( getRotatePoint( pCenter, &pSpPoint->point.rect, &tmpSpRotatePoint.point.rect, A180 ) ) {
		 iErr = -1; goto err;
	 }
	 
	 tmpSpRotatePoint.type = SP_POINT_TYPE;
	 tmpSpRotatePoint.subType = SP_ROTATE_POINT_TYPE;
	 tmpSpRotatePoint.status = 0;
	 tmpSpRotatePoint.op = OP_NULL;
	 tmpSpRotatePoint.pCenterQNode = pSp->pCenterQNode;
	 tmpSpRotatePoint.pRotatedQNode = pQNode;
	 tmpSpRotatePoint.A180 = A180;

	 if ( findNextpQNodeOfSamePlaceSpObj( pSp->pSpObjQ->front.pNext, ( SP_OBJ * )&tmpSpRotatePoint ) ) {
		 iErr = -1; goto err;
	 }

	 if ( qPostMsg( &tmpSpRotatePoint, sizeof( SP_ROTATE_POINT ),  pSp->pSpObjQ,  _T(  "rotateSpPoint"  ))) {
		 pSp->errNo = -1; goto err;
	 }

	
	 
err:	 

	 return iErr;


}

 int rotateSpSegment( SP_STRUCT *pSp, Q_NODE *pQNode, short A180 )
{
	 int iErr = 0;

	 return iErr;

}

 int rotateSpCircle( SP_STRUCT *pSp, Q_NODE *pQNode, short A180 )
{
	 int iErr = 0;

	 return iErr;

}



