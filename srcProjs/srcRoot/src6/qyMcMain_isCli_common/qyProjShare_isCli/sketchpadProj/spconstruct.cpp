
#include	"stdafx.h"
#include	"sp.h"


 int spConstructLine( SP_STRUCT *pSp )
{
	 Q_NODE *pQNode = NULL;
	 Q_NODE *tmppQNode = NULL;
	 SP_POINT *pSpPoint1 = NULL, *pSpPoint2 = NULL;
	 SP_LINE tmpSpLine;
	 int iErr = 0;
	 float k;

	 if ( !( pQNode = pSp->pSelectedSpObjQ->front.pNext ) ) {
			iErr = -1;goto err;
	 }
	 tmppQNode = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
	 if ( ( ( SP_OBJ * )tmppQNode->qElemMemory.m_pBuf )->type != SP_POINT_TYPE ) {
		 iErr = -1; goto err;
	 }
	
	 pSpPoint1 = ( SP_POINT * )( tmppQNode->qElemMemory.m_pBuf );
	 tmpSpLine.pQNode1 = tmppQNode;
	
	 if ( !( pQNode = pQNode->pNext ) ) {
		 iErr = -1; goto err;
	 }

	 if ( pQNode->pNext ) {
		 iErr = -1; goto err;
	 }

	 tmppQNode = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
	 if ( ( ( SP_OBJ * )tmppQNode->qElemMemory.m_pBuf )->type != SP_POINT_TYPE ) {
			iErr = -1; goto err;
	 }
	
	 pSpPoint2 = ( SP_POINT * )tmppQNode->qElemMemory.m_pBuf;	
	
	 tmpSpLine.pQNode2 = tmppQNode;


	 if ( pSpPoint1->point.rect.x == pSpPoint2->point.rect.x ) {

		 tmpSpLine.point1.rect.x = pSpPoint1->point.rect.x;
		 tmpSpLine.point1.rect.y = 0;
		 tmpSpLine.point2.rect.x = pSpPoint1->point.rect.x;
		 tmpSpLine.point2.rect.y = pSp->spHeight;

		}
	 else {

		 k = ( pSpPoint1->point.rect.y - pSpPoint2->point.rect.y ) / ( ( float )( pSpPoint1->point.rect.x - pSpPoint2->point.rect.x ) ); 
		 tmpSpLine.point1.rect.x = 0;
		 tmpSpLine.point1.rect.y = ( short )( k * ( tmpSpLine.point1.rect.x - pSpPoint1->point.rect.x ) + pSpPoint1->point.rect.y );
		 tmpSpLine.point2.rect.x = pSp->spWidth;
		 tmpSpLine.point2.rect.y = ( short )( k * ( tmpSpLine.point2.rect.x - pSpPoint1->point.rect.x ) + pSpPoint1->point.rect.y );
		 
	 }

	 tmpSpLine.type = SP_SEGMENT_TYPE;
	 tmpSpLine.subType = SP_LINE_TYPE;
	 tmpSpLine.status = 0;
	 tmpSpLine.op = OP_NULL;

	 if ( qPostMsg( &tmpSpLine, sizeof( SP_LINE ),  pSp->pSpObjQ,  _T(  "spConstructLine"  ))) {
			iErr = -1; goto err;
	 }


err:

	 return iErr;
	
}


 int spConstructPerpendicularLine( SP_STRUCT *pSp )
{
	 Q_NODE *pQNode = NULL;
	 Q_NODE *tmppQNode = NULL;
	 SP_POINT *pSpPoint = NULL;
	 SP_SEGMENT *pSpSegment = NULL;
	 SP_PERPENDICULAR_LINE tmpSpPerpendicularLine;
	 int iErr = 0;
	 float k;
	 SP_POINT *p1, *p2;

	 if ( !( pQNode = pSp->pSelectedSpObjQ->front.pNext ) ) {
			iErr = -1;goto err;
	 }
	 tmppQNode = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
	 if ( ( ( SP_OBJ * )tmppQNode->qElemMemory.m_pBuf )->type == SP_POINT_TYPE ) {
			pSpPoint = ( SP_POINT * )( tmppQNode->qElemMemory.m_pBuf );
			tmpSpPerpendicularLine.pSpPointQNode = tmppQNode;
		}
	 else if ( ( ( SP_OBJ * )tmppQNode->qElemMemory.m_pBuf )->type == SP_SEGMENT_TYPE ) {
			pSpSegment = ( SP_SEGMENT * )( tmppQNode->qElemMemory.m_pBuf );
			tmpSpPerpendicularLine.pSpSegmentQNode = tmppQNode;
		}
	 else { 
		 iErr = -1; goto err; 
	 }

	 if ( !( pQNode = pQNode->pNext ) ) {
		 iErr = -1; goto err;
	 }

	 if ( pQNode->pNext ) {
		 iErr = -1; goto err;
	 }

	 tmppQNode = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
	 if ( pSpPoint ) {
			if ( ( ( SP_OBJ * )tmppQNode->qElemMemory.m_pBuf )->type != SP_SEGMENT_TYPE ) {
					iErr = -1; goto err;
			}
			pSpSegment = ( SP_SEGMENT * )tmppQNode->qElemMemory.m_pBuf;
			tmpSpPerpendicularLine.pSpSegmentQNode = tmppQNode;
		}
	 else if ( ( ( SP_OBJ * )tmppQNode->qElemMemory.m_pBuf )->type == SP_POINT_TYPE ) {
			pSpPoint = ( SP_POINT * )tmppQNode->qElemMemory.m_pBuf;	
			tmpSpPerpendicularLine.pSpPointQNode = tmppQNode;
		}
	 else {
			iErr = -1; goto err;
	 }
	 
	 p1 = ( SP_POINT * )pSpSegment->pStartQNode->qElemMemory.m_pBuf;
	 p2 = ( SP_POINT * )pSpSegment->pEndQNode->qElemMemory.m_pBuf;
	
	 if ( p1->point.rect.x == p2->point.rect.x ) {
			 tmpSpPerpendicularLine.point1.rect.x = 0;
			 tmpSpPerpendicularLine.point1.rect.y = pSpPoint->point.rect.y;
			 tmpSpPerpendicularLine.point2.rect.x = pSp->spWidth;
			 tmpSpPerpendicularLine.point2.rect.y = pSpPoint->point.rect.y;
		}
	 else if ( p1->point.rect.y == p2->point.rect.y ) {
			 tmpSpPerpendicularLine.point1.rect.x = pSpPoint->point.rect.x;
			 tmpSpPerpendicularLine.point1.rect.y = 0;
			 tmpSpPerpendicularLine.point2.rect.x = pSpPoint->point.rect.x;
			 tmpSpPerpendicularLine.point2.rect.y = pSp->spHeight;
		}
	 else {
			 k = ( p1->point.rect.y - p2->point.rect.y ) / ( ( float )( p1->point.rect.x - p2->point.rect.x ) );
			 k = ( float )( -1. / k );
		
			 tmpSpPerpendicularLine.point1.rect.x = 0;
			 tmpSpPerpendicularLine.point1.rect.y = ( short )( k * ( tmpSpPerpendicularLine.point1.rect.x - pSpPoint->point.rect.x ) + pSpPoint->point.rect.y );
			 tmpSpPerpendicularLine.point2.rect.x = pSp->spWidth;
			 tmpSpPerpendicularLine.point2.rect.y = ( short )( k * ( tmpSpPerpendicularLine.point2.rect.x - pSpPoint->point.rect.x ) + pSpPoint->point.rect.y );
	 }

	 tmpSpPerpendicularLine.type = SP_SEGMENT_TYPE;
	 tmpSpPerpendicularLine.subType = SP_PERPENDICULAR_LINE_TYPE;
	 tmpSpPerpendicularLine.status = 0;
 	 tmpSpPerpendicularLine.op = OP_NULL;

	 if ( qPostMsg( &tmpSpPerpendicularLine, sizeof( SP_PERPENDICULAR_LINE ),  pSp->pSpObjQ,  _T(  "spConstructPerpendicularLine"  ))) {
			iErr = -1; goto err;
	 }

	
err:
	 return iErr;

}




 int spConstructAngleBisector( SP_STRUCT *pSp )
{
	 Q_NODE *pQNode;
	 SP_ANGLE_BISECTOR tmpSpAngleBisector;
	 int iErr = 0;
	

	 if ( !( pQNode = pSp->pSelectedSpObjQ->front.pNext ) ) return -1;
	 tmpSpAngleBisector.p1 = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
	 if ( !( pQNode = pQNode->pNext ) ) return -1;
	 tmpSpAngleBisector.p2 = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
	 if ( !( pQNode = pQNode->pNext ) ) return -1;
	 tmpSpAngleBisector.p3 = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
	 if ( ( pQNode = pQNode->pNext ) ) return -1;
	 		
	 tmpSpAngleBisector.type = SP_ANGLE_BISECTOR_TYPE;
	
	 tmpSpAngleBisector.subType = SP_GENERIC_ANGLE_BISECTOR_TYPE;
	
	 tmpSpAngleBisector.status = 0;
	
	 if ( getRayPointForAngleBisector( ( SP_POINT * )tmpSpAngleBisector.p1->qElemMemory.m_pBuf,
		 ( SP_POINT * )tmpSpAngleBisector.p2->qElemMemory.m_pBuf,
		 ( SP_POINT * )tmpSpAngleBisector.p3->qElemMemory.m_pBuf,
		 &tmpSpAngleBisector.rayPoint ) ) {
		 iErr = -1;
		 goto err;
	 }

	if ( qPostMsg( &tmpSpAngleBisector, sizeof( SP_ANGLE_BISECTOR ),  pSp->pSpObjQ,  _T(  "spConstructAngleBisector"  ))) {
		iErr = -1; goto err;
	}
	
err:
	 
	 return iErr;

}


 int spConstructHyperbola( SP_STRUCT *pSp )
{
	 int iErr = 0;
	 Q_NODE *pQNode = NULL;
	 Q_NODE *tmppQNode = NULL;
	 SP_POINT *pSpPoint1 = NULL, *pSpPoint2 = NULL, *pSpPoint3 = NULL;
	 SP_HYPERBOLA tmpSpHyperbola;
	 float c;
	 
	 if ( !( pQNode = pSp->pSelectedSpObjQ->front.pNext ) ) {
			iErr = -1;goto err;
	 }
	 tmppQNode = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
	 if ( ( ( SP_OBJ * )tmppQNode->qElemMemory.m_pBuf )->type != SP_POINT_TYPE ) {
			iErr = -1; goto err;
	 }
	
	 pSpPoint1 = ( SP_POINT * )tmppQNode->qElemMemory.m_pBuf;
	 tmpSpHyperbola.pFocus1 = tmppQNode;
	
	 if ( !( pQNode = pQNode->pNext ) ) {
		 iErr = -1; goto err;
	 }
	 tmppQNode = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
	 if ( ( ( SP_OBJ * )tmppQNode->qElemMemory.m_pBuf )->type != SP_POINT_TYPE ) {
			iErr = -1; goto err;
	 }

	 pSpPoint2 = ( SP_POINT * )tmppQNode->qElemMemory.m_pBuf;
	 tmpSpHyperbola.pFocus2 = tmppQNode;

	 if ( !( pQNode = pQNode->pNext ) ) {
		 iErr = -1; goto err;
	 }
	 
	 tmppQNode = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
	 if ( ( ( SP_OBJ * )tmppQNode->qElemMemory.m_pBuf )->type != SP_POINT_TYPE ) {
			iErr = -1; goto err;
	 }

	 pSpPoint3 = ( SP_POINT * )tmppQNode->qElemMemory.m_pBuf;
	 tmpSpHyperbola.p3 = tmppQNode;

	 if ( pQNode->pNext ) {
			iErr = -1; goto err;
	 }
	 
	 c = ( float )( getDOf2SpPoints( pSpPoint1, pSpPoint2 ) / 2.0 );
	 if ( getDOf2SpPoints( pSpPoint1, pSpPoint3 ) < SP_POINT_RANGE 
		 || getDOf2SpPoints( pSpPoint2, pSpPoint3 ) < SP_POINT_RANGE ) {
			iErr = -1; goto err;
	 }


// int getRAPI( float *pR, float *pA, int x, int y )


  

err:

	 return iErr;

}

