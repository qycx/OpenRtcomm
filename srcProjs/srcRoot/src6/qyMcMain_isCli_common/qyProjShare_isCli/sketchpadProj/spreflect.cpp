
#include	"stdafx.h"
#include	"sp.h"

 int reflectSpObj( SP_STRUCT *pSp, Q_NODE *pQNode )
{
	 SP_OBJ *pSpObj;
	 int iErr = 0;

	 pSpObj = ( SP_OBJ * )pQNode->qElemMemory.m_pBuf;

	 switch ( pSpObj->type ) {

		case SP_POINT_TYPE:

			iErr = reflectSpPoint( pSp, pQNode );

			break;
		
		case SP_SEGMENT_TYPE:

			iErr = reflectSpSegment( pSp, pQNode );

			break;

		default:

			iErr = -1;
	
			break;

	 }


	 return iErr;

}


 int reflectSpPoint( SP_STRUCT *pSp, Q_NODE *pQNode )
{
	 SP_POINT *pSpPoint;
	 SP_REFLECT_POINT tmpSpReflectPoint;
	 SP_SEGMENT *pMirror;
	 int iErr = 0;

	 pSpPoint = ( SP_POINT * )pQNode->qElemMemory.m_pBuf;
	 pMirror = ( SP_SEGMENT * )pSp->pMirrorQNode->qElemMemory.m_pBuf;

	 if ( getReflectPoint( pMirror, &pSpPoint->point.rect, &tmpSpReflectPoint.point.rect ) ) {
		 iErr = -1; goto err;
	 }
	 
	 tmpSpReflectPoint.type = SP_POINT_TYPE;
	 tmpSpReflectPoint.subType = SP_REFLECT_POINT_TYPE;
	 tmpSpReflectPoint.status = 0;
	 tmpSpReflectPoint.op = OP_NULL;
	 tmpSpReflectPoint.pMirrorQNode = pSp->pMirrorQNode;
	 tmpSpReflectPoint.pReflectedQNode = pQNode;

	 if ( findNextpQNodeOfSamePlaceSpObj( pSp->pSpObjQ->front.pNext, ( SP_OBJ * )&tmpSpReflectPoint ) ) {
		 iErr = -1; goto err;
	 }

	 if ( qPostMsg( &tmpSpReflectPoint, sizeof( SP_REFLECT_POINT ),  pSp->pSpObjQ,  _T(  "reflectSpPoint"  ))) {
		 pSp->errNo = -1; goto err;
	 }
	 
err:	 

	 return iErr;

 
}

 int reflectSpSegment( SP_STRUCT *pSp, Q_NODE *pQNode )
{

 	 SP_SEGMENT *pMirror;
	 SP_REFLECT_SEGMENT tmpSpReflectSegment;
	 SP_SEGMENT *pSpSegment;
	 int iErr = 0;

	 pSpSegment = ( SP_SEGMENT * )pQNode->qElemMemory.m_pBuf;
	 pMirror = ( SP_SEGMENT * )pSp->pMirrorQNode->qElemMemory.m_pBuf;

	 if ( getReflectPoint( pMirror, &pSpSegment->point1.rect, &tmpSpReflectSegment.point1.rect ) ) {
		 iErr = -1; goto err;
	 }

	 if ( getReflectPoint( pMirror, &pSpSegment->point2.rect, &tmpSpReflectSegment.point2.rect ) ) {
		 iErr = -1; goto err;
	 }

	 tmpSpReflectSegment.type = SP_SEGMENT_TYPE;
	 if ( pSpSegment->subType == SP_GENERIC_SEGMENT_TYPE 
		 || pSpSegment->subType == SP_REFLECT_SEGMENT_TYPE ) 
			tmpSpReflectSegment.subType = SP_REFLECT_SEGMENT_TYPE;
	 else 
		 tmpSpReflectSegment.subType = SP_REFLECT_LINE_TYPE;
	 tmpSpReflectSegment.pMirrorQNode = pSp->pMirrorQNode;
	 tmpSpReflectSegment.pReflectedQNode = pQNode;
	 tmpSpReflectSegment.op = OP_NULL;
	 tmpSpReflectSegment.status = 0;


	 if ( qPostMsg( &tmpSpReflectSegment, sizeof( tmpSpReflectSegment ),  pSp->pSpObjQ,  _T(  "reflectSpSegment"  ))) {
		 iErr = -1; goto err;
	 }
	 

err:

	 return iErr;

}



